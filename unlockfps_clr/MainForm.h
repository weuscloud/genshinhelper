#pragma once
#include "Settings.h"
#include "SetupForm.h"
#include "SettingsForm.h"
#include <algorithm>
#include <mutex>

namespace unlockfpsclr {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			
			InitializeComponent();
			
			settings = Settings::Load();
			settingsForm = gcnew SettingsForm(settings);

			this->Load += gcnew EventHandler(this, &MainForm::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);
			this->Resize += gcnew EventHandler(this, &MainForm::OnResize);
			this->notifyIcon->DoubleClick += gcnew EventHandler(this, &MainForm::OnDoubleClick);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	System::Threading::Mutex^ mutex;
	private: Settings^ settings;
	private: BackgroundWorker^ backgroundWorker;
	private: SettingsForm^ settingsForm;
	private: System::Windows::Forms::Button^ btnStartGame;
	private: System::Windows::Forms::CheckBox^ ckbAutoStart;
	private: System::Windows::Forms::ToolTip^ ttAutoStart;
	private: System::Windows::Forms::TrackBar^ tbFPS;
	private: System::Windows::Forms::Label^ labelFPS;

	private: System::Windows::Forms::NumericUpDown^ inputFPS;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem;





	private: System::Windows::Forms::ToolTip^ ttGamePath;
	private: System::Windows::Forms::ToolStripMenuItem^ menuItemSetup;

	private: System::Windows::Forms::NotifyIcon^ notifyIcon;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuNotify;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuExit;

	private: System::Windows::Forms::ComboBox^ DropDownBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnSaveAccount;
	private: System::Windows::Forms::Button^ btnClearAccount;
	private: System::Windows::Forms::CheckBox^ btnAutoSave;
	private: System::Windows::Forms::ToolStripMenuItem^ openWorkDirectoryToolStripMenuItem;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::CheckBox^ cbxQuickSwitch;
	private: System::Windows::Forms::TextBox^ bottomTextBox;
	private: System::Windows::Forms::ToolStripMenuItem^ 设置ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ 关于ToolStripMenuItem;

















	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->btnStartGame = (gcnew System::Windows::Forms::Button());
			this->ckbAutoStart = (gcnew System::Windows::Forms::CheckBox());
			this->ttAutoStart = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnAutoSave = (gcnew System::Windows::Forms::CheckBox());
			this->tbFPS = (gcnew System::Windows::Forms::TrackBar());
			this->labelFPS = (gcnew System::Windows::Forms::Label());
			this->inputFPS = (gcnew System::Windows::Forms::NumericUpDown());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openWorkDirectoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSetup = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->设置ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->关于ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ttGamePath = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuNotify = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DropDownBox = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnSaveAccount = (gcnew System::Windows::Forms::Button());
			this->btnClearAccount = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->cbxQuickSwitch = (gcnew System::Windows::Forms::CheckBox());
			this->bottomTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->contextMenuNotify->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnStartGame
			// 
			this->btnStartGame->BackColor = System::Drawing::SystemColors::Window;
			this->btnStartGame->Font = (gcnew System::Drawing::Font(L"宋体", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnStartGame->ForeColor = System::Drawing::Color::DodgerBlue;
			this->btnStartGame->Location = System::Drawing::Point(16, 229);
			this->btnStartGame->Name = L"btnStartGame";
			this->btnStartGame->Size = System::Drawing::Size(256, 30);
			this->btnStartGame->TabIndex = 0;
			this->btnStartGame->TabStop = false;
			this->btnStartGame->Text = L"开始游戏";
			this->btnStartGame->UseVisualStyleBackColor = false;
			this->btnStartGame->Click += gcnew System::EventHandler(this, &MainForm::btnStartGame_Click);
			// 
			// ckbAutoStart
			// 
			this->ckbAutoStart->AutoSize = true;
			this->ckbAutoStart->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->ckbAutoStart->Location = System::Drawing::Point(16, 205);
			this->ckbAutoStart->Name = L"ckbAutoStart";
			this->ckbAutoStart->Size = System::Drawing::Size(110, 18);
			this->ckbAutoStart->TabIndex = 1;
			this->ckbAutoStart->TabStop = false;
			this->ckbAutoStart->Text = L"自动启动原神";
			this->ttAutoStart->SetToolTip(this->ckbAutoStart, L"This will take effect on subsequent launch");
			this->ckbAutoStart->UseVisualStyleBackColor = true;
			// 
			// ttAutoStart
			// 
			this->ttAutoStart->AutoPopDelay = 5000;
			this->ttAutoStart->InitialDelay = 1;
			this->ttAutoStart->ReshowDelay = 100;
			// 
			// btnAutoSave
			// 
			this->btnAutoSave->AutoSize = true;
			this->btnAutoSave->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnAutoSave->Location = System::Drawing::Point(16, 120);
			this->btnAutoSave->Name = L"btnAutoSave";
			this->btnAutoSave->Size = System::Drawing::Size(82, 18);
			this->btnAutoSave->TabIndex = 11;
			this->btnAutoSave->Text = L"自动保存";
			this->ttAutoStart->SetToolTip(this->btnAutoSave, L" Save Account Automatically ,after game exited.");
			this->btnAutoSave->UseVisualStyleBackColor = true;
			this->btnAutoSave->CheckedChanged += gcnew System::EventHandler(this, &MainForm::btnAutoSave_CheckedChanged);
			// 
			// tbFPS
			// 
			this->tbFPS->AutoSize = false;
			this->tbFPS->Cursor = System::Windows::Forms::Cursors::Hand;
			this->tbFPS->Location = System::Drawing::Point(12, 53);
			this->tbFPS->Maximum = 360;
			this->tbFPS->Minimum = 10;
			this->tbFPS->Name = L"tbFPS";
			this->tbFPS->Size = System::Drawing::Size(265, 19);
			this->tbFPS->TabIndex = 2;
			this->tbFPS->TabStop = false;
			this->tbFPS->TickStyle = System::Windows::Forms::TickStyle::None;
			this->tbFPS->Value = 120;
			// 
			// labelFPS
			// 
			this->labelFPS->AutoSize = true;
			this->labelFPS->Location = System::Drawing::Point(12, 30);
			this->labelFPS->Name = L"labelFPS";
			this->labelFPS->Size = System::Drawing::Size(35, 12);
			this->labelFPS->TabIndex = 3;
			this->labelFPS->Text = L"FPS: ";
			// 
			// inputFPS
			// 
			this->inputFPS->Location = System::Drawing::Point(48, 29);
			this->inputFPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->inputFPS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->inputFPS->Name = L"inputFPS";
			this->inputFPS->Size = System::Drawing::Size(224, 21);
			this->inputFPS->TabIndex = 4;
			this->inputFPS->TabStop = false;
			this->inputFPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem,
					this->设置ToolStripMenuItem, this->关于ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(286, 25);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem
			// 
			this->toolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openWorkDirectoryToolStripMenuItem,
					this->menuItemSetup
			});
			this->toolStripMenuItem->Name = L"toolStripMenuItem";
			this->toolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->toolStripMenuItem->Text = L"选项";
			// 
			// openWorkDirectoryToolStripMenuItem
			// 
			this->openWorkDirectoryToolStripMenuItem->Name = L"openWorkDirectoryToolStripMenuItem";
			this->openWorkDirectoryToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->openWorkDirectoryToolStripMenuItem->Text = L"打开工作目录";
			this->openWorkDirectoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openWorkDirectoryToolStripMenuItem_Click);
			// 
			// menuItemSetup
			// 
			this->menuItemSetup->Name = L"menuItemSetup";
			this->menuItemSetup->Size = System::Drawing::Size(184, 22);
			this->menuItemSetup->Text = L"查找或设置原神目录";
			this->menuItemSetup->Click += gcnew System::EventHandler(this, &MainForm::setupMenuItem_Click);
			// 
			// 设置ToolStripMenuItem
			// 
			this->设置ToolStripMenuItem->Name = L"设置ToolStripMenuItem";
			this->设置ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->设置ToolStripMenuItem->Text = L"设置";
			this->设置ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::settingsMenuItem_Click);
			// 
			// 关于ToolStripMenuItem
			// 
			this->关于ToolStripMenuItem->Name = L"关于ToolStripMenuItem";
			this->关于ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->关于ToolStripMenuItem->Text = L"关于";
			this->关于ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::menuItemAbout_Click);
			// 
			// ttGamePath
			// 
			this->ttGamePath->AutoPopDelay = 5000;
			this->ttGamePath->InitialDelay = 2;
			this->ttGamePath->ReshowDelay = 100;
			// 
			// notifyIcon
			// 
			this->notifyIcon->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			this->notifyIcon->BalloonTipText = L"Minimized to tray";
			this->notifyIcon->BalloonTipTitle = L"FPS Unlocker";
			this->notifyIcon->ContextMenuStrip = this->contextMenuNotify;
			this->notifyIcon->Text = L"Hello";
			this->notifyIcon->Visible = true;
			// 
			// contextMenuNotify
			// 
			this->contextMenuNotify->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuExit });
			this->contextMenuNotify->Name = L"contextMenuNotify";
			this->contextMenuNotify->ShowItemToolTips = false;
			this->contextMenuNotify->Size = System::Drawing::Size(97, 26);
			// 
			// toolStripMenuExit
			// 
			this->toolStripMenuExit->Name = L"toolStripMenuExit";
			this->toolStripMenuExit->Size = System::Drawing::Size(96, 22);
			this->toolStripMenuExit->Text = L"Exit";
			this->toolStripMenuExit->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuExit_Click);
			// 
			// DropDownBox
			// 
			this->DropDownBox->DropDownHeight = 200;
			this->DropDownBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DropDownBox->Font = (gcnew System::Drawing::Font(L"宋体", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->DropDownBox->FormattingEnabled = true;
			this->DropDownBox->IntegralHeight = false;
			this->DropDownBox->ItemHeight = 15;
			this->DropDownBox->Location = System::Drawing::Point(16, 90);
			this->DropDownBox->MaxDropDownItems = 30;
			this->DropDownBox->Name = L"DropDownBox";
			this->DropDownBox->Size = System::Drawing::Size(257, 23);
			this->DropDownBox->TabIndex = 0;
			this->DropDownBox->TabStop = false;
			this->DropDownBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::DropDownBox_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(16, 72);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(112, 14);
			this->label1->TabIndex = 7;
			this->label1->Text = L"请选择登录账号:";
			// 
			// btnSaveAccount
			// 
			this->btnSaveAccount->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnSaveAccount->Location = System::Drawing::Point(16, 140);
			this->btnSaveAccount->Name = L"btnSaveAccount";
			this->btnSaveAccount->Size = System::Drawing::Size(256, 25);
			this->btnSaveAccount->TabIndex = 8;
			this->btnSaveAccount->Text = L"保存";
			this->btnSaveAccount->UseVisualStyleBackColor = true;
			this->btnSaveAccount->Click += gcnew System::EventHandler(this, &MainForm::btnSaveAccount_Click);
			// 
			// btnClearAccount
			// 
			this->btnClearAccount->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btnClearAccount->Location = System::Drawing::Point(16, 175);
			this->btnClearAccount->Name = L"btnClearAccount";
			this->btnClearAccount->Size = System::Drawing::Size(256, 25);
			this->btnClearAccount->TabIndex = 9;
			this->btnClearAccount->Text = L"清除";
			this->btnClearAccount->UseVisualStyleBackColor = true;
			this->btnClearAccount->Click += gcnew System::EventHandler(this, &MainForm::btnClearAccount_Click);
			// 
			// cbxQuickSwitch
			// 
			this->cbxQuickSwitch->AutoSize = true;
			this->cbxQuickSwitch->Font = (gcnew System::Drawing::Font(L"宋体", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->cbxQuickSwitch->Location = System::Drawing::Point(190, 119);
			this->cbxQuickSwitch->Name = L"cbxQuickSwitch";
			this->cbxQuickSwitch->Size = System::Drawing::Size(82, 18);
			this->cbxQuickSwitch->TabIndex = 12;
			this->cbxQuickSwitch->Text = L"快速切换";
			this->cbxQuickSwitch->UseVisualStyleBackColor = true;
			// 
			// bottomTextBox
			// 
			this->bottomTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->bottomTextBox->Font = (gcnew System::Drawing::Font(L"宋体", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->bottomTextBox->Location = System::Drawing::Point(0, 272);
			this->bottomTextBox->Name = L"bottomTextBox";
			this->bottomTextBox->Size = System::Drawing::Size(286, 17);
			this->bottomTextBox->TabIndex = 13;
			this->bottomTextBox->Text = L"就绪";
			this->bottomTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(286, 291);
			this->Controls->Add(this->bottomTextBox);
			this->Controls->Add(this->cbxQuickSwitch);
			this->Controls->Add(this->btnAutoSave);
			this->Controls->Add(this->btnClearAccount);
			this->Controls->Add(this->btnSaveAccount);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->DropDownBox);
			this->Controls->Add(this->inputFPS);
			this->Controls->Add(this->labelFPS);
			this->Controls->Add(this->tbFPS);
			this->Controls->Add(this->ckbAutoStart);
			this->Controls->Add(this->btnStartGame);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"原神超帧多账号小助手";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->contextMenuNotify->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void btnStartGame_Click(Object^ sender, EventArgs^ e);
	private: Void settingsMenuItem_Click(Object^ sender, EventArgs^ e);
	private: Void OnLoad(Object^ sender, EventArgs^ e);
	private: Void setupMenuItem_Click(Object^ sender, EventArgs^ e);
	private: Void OnDoWork(Object^ sender, DoWorkEventArgs^ e);
	private: Void OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e);
	private: Void OnResize(Object^ sender, EventArgs^ e);
	private: Void OnDoubleClick(Object^ sender, EventArgs^ e);
	private: Void toolStripMenuExit_Click(Object^ sender, EventArgs^ e);
	private: Void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
	private: Void menuItemAbout_Click(Object^ sender, EventArgs^ e);
private: System::Void btnSaveAccount_Click(System::Object^ sender, System::EventArgs^ e);
	   String^ GetDataDir();
private: System::Void DropDownBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	   Void ImportReg();
	   String^ GetUID();
	   Void CmdCommit(String^ cmd);
	   Void SetDropDownBoxItems();
private: System::Void btnClearAccount_Click(System::Object^ sender, System::EventArgs^ e);

	  String^ GetUIDFile();

private: Void SetCurrentUID();

	   Void SetCurrentUID(String^ text);
	   Void ClearReg();
	   Void SaveAccount();
	   BOOL IsRegExists();
	   Void doQuickSwitch();
private: System::Void btnAutoSave_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void openWorkDirectoryToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}