#include "Unmanaged.h"
#include "MainForm.h"
#include "SettingsForm.h"
#include "AboutForm.h"
#include "Managed.h"
#include "resource.h"
#include <unordered_map>

#define MUTEX_NAME "GenshinFPSUnlocker"

using namespace System;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Text::Json;
using namespace System::IO;
using namespace System::Threading;


static const std::unordered_map<std::string, LPCSTR> dependencies = {
	{"Microsoft.Bcl.AsyncInterfaces.dll", MAKEINTRESOURCEA(IDR_DLL1)},
	{"System.Buffers.dll", MAKEINTRESOURCEA(IDR_DLL2)},
	{"System.Memory.dll", MAKEINTRESOURCEA(IDR_DLL3)},
	{"System.Numerics.Vectors.dll", MAKEINTRESOURCEA(IDR_DLL4)},
	{"System.Runtime.CompilerServices.Unsafe.dll", MAKEINTRESOURCEA(IDR_DLL5)},
	{"System.Text.Encodings.Web.dll", MAKEINTRESOURCEA(IDR_DLL6)},
	{"System.Text.Json.dll", MAKEINTRESOURCEA(IDR_DLL7)},
	{"System.Threading.Tasks.Extensions.dll", MAKEINTRESOURCEA(IDR_DLL8)}
};

void Run()
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	unlockfpsclr::MainForm mainForm;
	Application::Run(% mainForm);
}


Assembly^ OnAssemblyResolve(Object^ sender, ResolveEventArgs^ args)
{
	/*
		resolve dependencies through cpp resource
		the goal is to have a single file application
		kinda ugly but it works idc

		an easier way is to use vmprotect to bundle
		dependency assemblies, but ppl be skeptical about
		binaries processed through vmp, so I didn't use that

		for some reason vmprotect adds significant amount of il code
		even if there aren't any protection enabled

		ILMerge and ILRepack doesn't want to work with c++/cli
		if anyone knows an easier way to bundle assemblies, lmk
	*/

	Assembly^ assembly = nullptr;
	auto assemblyName = gcnew AssemblyName(args->Name);
	auto nativeString = static_cast<LPSTR>(static_cast<PVOID>(Marshal::StringToHGlobalAnsi(assemblyName->Name + ".dll")));

	auto resId = dependencies.find(nativeString);
	if (resId != dependencies.end())
	{
		auto rsrc = FindResourceA(nullptr, resId->second, "DLL");
		auto size = SizeofResource(nullptr, rsrc);
		auto rsrcData = LoadResource(nullptr, rsrc);
		auto pData = LockResource(rsrcData);
		if (pData)
		{
			array<BYTE>^ rawBytes = gcnew array<BYTE>(size);
			Marshal::Copy(static_cast<IntPtr>(pData), rawBytes, 0, size);
			assembly = Assembly::Load(rawBytes);
		}
	}

	Marshal::FreeHGlobal(static_cast<IntPtr>(nativeString));

	return assembly;
}

int main(array<String^>^ args)
{
	HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
	if (hMutex)
		return 0;

	hMutex = CreateMutexA(nullptr, FALSE, MUTEX_NAME);

	AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&OnAssemblyResolve);

	// check to see if the unlocker is placed with the game
	if (File::Exists("UnityPlayer.dll") && (File::Exists("GenshinImpact.exe") || File::Exists("YuanShen.exe")))
	{
		MessageBox::Show("Do not place unlocker in the same folder as the game", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		goto Exit;
	}

	auto thread = gcnew Thread(gcnew ThreadStart(Run));
	thread->SetApartmentState(ApartmentState::STA); // Single-Threaded Apartment required for file browse
	thread->Start();
	thread->Join();

Exit:
	ReleaseMutex(hMutex);
	return 0;
}

namespace unlockfpsclr
{

	Void MainForm::btnStartGame_Click(Object^ sender, EventArgs^ e)
	{
		// minimize the unlocker if create process was successful
		if (Managed::StartGame(settings))
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	Void MainForm::settingsMenuItem_Click(Object^ sender, EventArgs^ e)
	{
		// open settings page
		settingsForm->ShowDialog();
	}

	Void MainForm::OnLoad(Object^ sender, EventArgs^ e)
	{
		auto hIcon = (HICON)LoadImageA(GetModuleHandleA(nullptr), MAKEINTRESOURCEA(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
		notifyIcon->Icon = this->Icon;
		// start setup dialog if game path is invalid in config
		if (String::IsNullOrWhiteSpace(settings->GamePath) || !File::Exists(settings->GamePath))
			(gcnew SetupForm(settings))->ShowDialog();

		settings->FPSTarget = std::clamp(settings->FPSTarget, tbFPS->Minimum, tbFPS->Maximum); // sanitize

		ckbAutoStart->DataBindings->Add("Checked", settings, "AutoStart");
		btnAutoSave->DataBindings->Add("Checked", settings, "AutoSave");
		tbFPS->DataBindings->Add("Value", settings, "FPSTarget", false, DataSourceUpdateMode::OnPropertyChanged);
		inputFPS->DataBindings->Add("Value", settings, "FPSTarget", false, DataSourceUpdateMode::OnPropertyChanged);

		if (settings->StartMinimized)
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;

		if (settings->AutoStart)
			Managed::StartGame(settings);



		// create a thread for applying fps value
		backgroundWorker = gcnew BackgroundWorker();
		backgroundWorker->WorkerReportsProgress = true;
		backgroundWorker->WorkerSupportsCancellation = true;
		backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &MainForm::OnDoWork);
		backgroundWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::OnProgressChanged);
		backgroundWorker->RunWorkerAsync();

		SetDropDownBoxItems();
	}

	Void MainForm::setupMenuItem_Click(Object^ sender, EventArgs^ e)
	{
		auto form = gcnew SetupForm(settings);
		form->ShowDialog();
	}

	Void MainForm::OnDoWork(Object^ sender, DoWorkEventArgs^ e)
	{
		auto worker = safe_cast<BackgroundWorker^>(sender);
		while (!worker->CancellationPending)
		{
			Thread::Sleep(200);
			if (!Unmanaged::IsGameRunning())
				continue;

			// setup pointer to fps value and vsync value
			if (!Unmanaged::SetupData())
				continue;

			Managed::InjectDLLs(settings->DllList);

			while (!worker->CancellationPending)
			{
				Unmanaged::ApplyFPS(settings->FPSTarget, settings->UsePowerSave);
				Unmanaged::ApplyVSync(settings->AutoDisableVSync);

				if (!Unmanaged::IsGameRunning())
					break;

				Thread::Sleep(1000);
			}

			// ProgressChangedEvent will be dispatched on call to ReportProgress
			// this is needed because any changes to form control need to be done on the thread created it
			// and this method runs on a seperate thread
			if (settings->AutoClose)
				worker->ReportProgress(100);
			else
			worker->ReportProgress(200);
		}

	}

	Void MainForm::OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e)
	{
		auto progress = e->ProgressPercentage; 
		if (progress == 100) {
			Application::Exit();
			return;
		}
		OnDoubleClick(nullptr, nullptr); // restore window
		bool isSaveAccountExcuted = false;
		if (this->btnAutoSave->Checked) {
			SaveAccount();
			isSaveAccountExcuted = true;
		}
		else {
			isSaveAccountExcuted = true;
		}
		if (this->cbxQuickSwitch->Checked&& isSaveAccountExcuted)doQuickSwitch();
		
	}


	Void MainForm::OnResize(Object^ sender, EventArgs^ e)
	{
		if (this->WindowState == FormWindowState::Minimized)
		{
			// tray icon visibility and tooltip
			notifyIcon->Visible = true;
			bottomTextBox->Text = String::Format("FPS: {0}", settings->FPSTarget);

			// only show wintoast notification once
			static bool once = false;
			if (!once)
			{
				notifyIcon->ShowBalloonTip(200);
				once = true;
			}
			this->ShowInTaskbar = false;
			this->Hide();

		}
	}

	Void MainForm::OnDoubleClick(Object^ sender, EventArgs^ e)
	{
		// restores window and taskbar icon
		this->WindowState = FormWindowState::Normal;
		this->ShowInTaskbar = true;
		this->Show();
		this->Focus();
		//notifyIcon->Visible = false;
	}

	Void MainForm::toolStripMenuExit_Click(Object^ sender, EventArgs^ e)
	{
		Application::Exit();
	}

	Void MainForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
	{
		settings->Save();
		notifyIcon->Visible = false;
	}

	Void MainForm::menuItemAbout_Click(Object^ sender, EventArgs^ e)
	{
		auto form = gcnew AboutForm();
		form->ShowDialog();
	}

	Void MainForm::btnSaveAccount_Click(System::Object^ sender, System::EventArgs^ e)
	{

		String^ uidRegFile = GetDataDir() + "\\" + GetUID() + ".reg";
		SaveAccount();
		SetDropDownBoxItems();
		SetCurrentUID();
		return System::Void();
	}
	String^ MainForm::GetDataDir() {
		String^ WorkPath = Settings::WorkPath;
		String^ dir = WorkPath + "\\account_data";
		return dir;
	}
	Void MainForm::DropDownBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ClearReg();
		ImportReg();
		return Void();
	}
	Void MainForm::ImportReg() {
		String^ Uid = this->DropDownBox->Text;
		String^ cmd = "reg import " + GetDataDir() + "\\" + Uid + ".reg";
		String^ file = GetDataDir() + "\\" + Uid + ".reg";
		if (!File::Exists(file)) {
			return;
		}
		CmdCommit(cmd);
	}
	String^ MainForm::GetUID() {

		String^ fileName = GetUIDFile();
		String^ uid = "uid";
		if (!File::Exists(fileName))return uid;
		StreamReader^ din = File::OpenText(fileName);
		uid = din->ReadLine();
		din->Close();
		return uid;
	}
	Void MainForm::CmdCommit(String^ cmd) {
		System::Diagnostics::Process^ p = gcnew System::Diagnostics::Process();
		p->StartInfo->FileName = "cmd.exe";
		p->StartInfo->UseShellExecute = false;    //�Ƿ�ʹ�ò���ϵͳshell����
		p->StartInfo->RedirectStandardInput = true;//�������Ե��ó����������Ϣ
		p->StartInfo->RedirectStandardOutput = true;//�ɵ��ó����ȡ�����Ϣ
		p->StartInfo->RedirectStandardError = true;//�ض����׼�������
		p->StartInfo->CreateNoWindow = true;//����ʾ���򴰿�
		p->Start();//��������

		//��cmd���ڷ���������Ϣ
		p->StandardInput->WriteLine(cmd + "&exit");

		p->StandardInput->AutoFlush = true;
		p->StandardInput->WriteLine("exit");
		p->WaitForExit();
		p->Close();
	}
	Void MainForm::SetDropDownBoxItems() {
		this->DropDownBox->Items->Clear();
		if (!File::Exists(GetDataDir()))
			Directory::CreateDirectory(GetDataDir());
		auto files = Directory::GetFiles(GetDataDir(), "*.reg");
		int count = 0;
		array<System::Object^>^ items = gcnew cli::array< System::Object^  >(50);
		for each (auto file in files)
		{
			if (count < 50) {
				items[count] = Path::GetFileNameWithoutExtension(file);
				count++;
			}

		};

		if (count > 0) {
			array<System::Object^>^ res = gcnew cli::array< System::Object^  >(count);
			for (int i = 0; i < count; ++i) {
				res[i] = items[i];
			}
			this->DropDownBox->Items->AddRange(res);
		}
		this->btnClearAccount->Text
			= "����˺�(���� " + count + " ���˺�)";
	}
	System::Void MainForm::btnClearAccount_Click(System::Object^ sender, System::EventArgs^ e)
	{
		RegistryKey^ rk;
		rk = Registry::CurrentUser->OpenSubKey("Software\\miHoYo", true);
		if (rk && rk->OpenSubKey("ԭ��")) {
			rk->DeleteSubKeyTree("ԭ��");
			rk->Close();
			this->bottomTextBox->Text = "����˺ųɹ�!";
		}
		return System::Void();
	}



	String^ MainForm::GetUIDFile() {
		String^ fileName = Environment::GetFolderPath(Environment::SpecialFolder::UserProfile) + "\\AppData\\LocalLow\\miHoYo\\ԭ��\\UidInfo.txt";
		return fileName;
	}
	Void MainForm::SetCurrentUID() {
		this->btnSaveAccount->Text = "�����˺�:(" + GetUID() + ")";
	}
	Void MainForm::SetCurrentUID(String^ text) {
		this->btnSaveAccount->Text = text;
	}
	Void MainForm::ClearReg() {
		RegistryKey^ rk;
		rk = Registry::CurrentUser->OpenSubKey("Software\\miHoYo", true);
		if (rk->OpenSubKey("ԭ��")) {
			rk->DeleteSubKeyTree("ԭ��");
		}
		rk->Close();
	}
	Void MainForm::SaveAccount() {
		String^ uid = GetUID();
		if (uid == "uid")return;
		if (!IsRegExists())return;
		String^ uidRegFile = GetDataDir() + "\\" + uid + ".reg";
		bool exists = File::Exists(uidRegFile);
		if (exists) File::Delete(uidRegFile);
		String^ cmd = "reg export HKCU\\Software\\miHoYo\\ԭ�� " + uidRegFile;
		CmdCommit(cmd);
		if (!exists)SetDropDownBoxItems();
		this->bottomTextBox->Text = "�����˺�"+ uid +"�ɹ�!";
	}
	
	BOOL MainForm::IsRegExists() {
		RegistryKey^ rk;
		rk = Registry::CurrentUser->OpenSubKey("Software\\miHoYo", true);
		if (!rk->OpenSubKey("ԭ��")) {
			return FALSE;
		}
		rk = Registry::CurrentUser->OpenSubKey("Software\\miHoYo\\ԭ��", true);
		auto val1 = rk->GetValue("GENERAL_DATA_h2389025596");
		auto val2 = rk->GetValue("MIHOYOSDK_ADL_PROD_CN_h3123967166");
		rk->Close();
		if (val1 && val2) {
			return TRUE;
		}
		return FALSE;
	}
	Void MainForm::doQuickSwitch()
	{
		if ((this->DropDownBox->SelectedIndex + 1) < this->DropDownBox->Items->Count)
		{
			this->DropDownBox->SelectedIndex++;
		}
		else {
			this->bottomTextBox->Text = "�����л���ɣ�";
		}

		return Void();
	}
	System::Void MainForm::btnAutoSave_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		return System::Void();
	}
	System::Void MainForm::openWorkDirectoryToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		System::Diagnostics::Process::Start(Settings::WorkPath);
	}
}
