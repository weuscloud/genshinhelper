#pragma once
#include "Settings.h"
#include <algorithm>

namespace unlockfpsclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for SettingsForm
	/// </summary>
	public ref class SettingsForm : public Form
	{
	public:
		SettingsForm(Settings^ settings)
		{
			InitializeComponent();

			this->ckbVSync->DataBindings->Add("Checked", settings, "AutoDisableVSync", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbPopupWnd->DataBindings->Add("Checked", settings, "PopupWindow", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbFullscreen->DataBindings->Add("Checked", settings, "Fullscreen", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbCustomRes->DataBindings->Add("Checked", settings, "UseCustomRes", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbStartMinimized->DataBindings->Add("Checked", settings, "StartMinimized", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbAutoClose->DataBindings->Add("Checked", settings, "AutoClose", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbPowerSave->DataBindings->Add("Checked", settings, "UsePowerSave", false, DataSourceUpdateMode::OnPropertyChanged);

			//this->customResX->DataBindings->Add("Value", settings, "CustomResX");
			//this->customResY->DataBindings->Add("Value", settings, "CustomResY");
			//this->monitorNum->DataBindings->Add("Value", settings, "MonitorNum");
			//this->comboWindowMode->DataBindings->Add("SelectedIndex", settings, "IsExclusiveFullscreen");
			//this->comboPriority->DataBindings->Add("SelectedIndex", settings, "Priority");

			/*auto bindingSource = gcnew BindingSource();
			bindingSource->DataSource = settings->DllList;
			bindingSource->AllowNew = true;
			this->lbDllList->DataSource = bindingSource;*/
			this->lbDllList->Format += gcnew ListControlConvertEventHandler(this, &SettingsForm::OnFormat);

			this->settings = settings;
			this->Load += gcnew EventHandler(this, &SettingsForm::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::UpdateSettings);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Settings^ settings;
	private: System::Windows::Forms::Label^ labelAutoSave;
	private: System::Windows::Forms::TabControl^ tabControl;
	private: System::Windows::Forms::TabPage^ tabPageGeneral;
	private: System::Windows::Forms::CheckBox^ ckbVSync;
	private: System::Windows::Forms::TabPage^ tabPageLaunchOptions;
	private: System::Windows::Forms::NumericUpDown^ customResX;

	private: System::Windows::Forms::Label^ labelCustomRes;
	private: System::Windows::Forms::CheckBox^ ckbCustomRes;
	private: System::Windows::Forms::CheckBox^ ckbFullscreen;
	private: System::Windows::Forms::CheckBox^ ckbPopupWnd;
	private: System::Windows::Forms::NumericUpDown^ customResY;
	private: System::Windows::Forms::Label^ labelDummy;
	private: System::Windows::Forms::ComboBox^ comboWindowMode;
	private: System::Windows::Forms::Label^ labelWindowMode;
	private: System::Windows::Forms::ToolTip^ toolTip;


	private: System::Windows::Forms::CheckBox^ ckbStartMinimized;
	private: System::Windows::Forms::CheckBox^ ckbAutoClose;

	private: System::Windows::Forms::NumericUpDown^ monitorNum;

	private: System::Windows::Forms::Label^ labelMonitorNum;
	private: System::Windows::Forms::TabPage^ tabPageDLLs;
	private: System::Windows::Forms::Button^ btnDllRemove;
	private: System::Windows::Forms::Button^ btnDllAdd;
	private: System::Windows::Forms::ListBox^ lbDllList;
	private: System::Windows::Forms::Label^ labelDLLMessage;

	private: System::Windows::Forms::ComboBox^ comboPriority;

	private: System::Windows::Forms::Label^ labelPriority;
	private: System::Windows::Forms::CheckBox^ ckbPowerSave;





	private: System::ComponentModel::IContainer^ components;


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
			this->labelAutoSave = (gcnew System::Windows::Forms::Label());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPageGeneral = (gcnew System::Windows::Forms::TabPage());
			this->comboPriority = (gcnew System::Windows::Forms::ComboBox());
			this->labelPriority = (gcnew System::Windows::Forms::Label());
			this->ckbPowerSave = (gcnew System::Windows::Forms::CheckBox());
			this->ckbAutoClose = (gcnew System::Windows::Forms::CheckBox());
			this->ckbStartMinimized = (gcnew System::Windows::Forms::CheckBox());
			this->ckbVSync = (gcnew System::Windows::Forms::CheckBox());
			this->tabPageLaunchOptions = (gcnew System::Windows::Forms::TabPage());
			this->monitorNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelMonitorNum = (gcnew System::Windows::Forms::Label());
			this->comboWindowMode = (gcnew System::Windows::Forms::ComboBox());
			this->labelWindowMode = (gcnew System::Windows::Forms::Label());
			this->labelDummy = (gcnew System::Windows::Forms::Label());
			this->customResY = (gcnew System::Windows::Forms::NumericUpDown());
			this->customResX = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelCustomRes = (gcnew System::Windows::Forms::Label());
			this->ckbCustomRes = (gcnew System::Windows::Forms::CheckBox());
			this->ckbFullscreen = (gcnew System::Windows::Forms::CheckBox());
			this->ckbPopupWnd = (gcnew System::Windows::Forms::CheckBox());
			this->tabPageDLLs = (gcnew System::Windows::Forms::TabPage());
			this->btnDllRemove = (gcnew System::Windows::Forms::Button());
			this->btnDllAdd = (gcnew System::Windows::Forms::Button());
			this->lbDllList = (gcnew System::Windows::Forms::ListBox());
			this->labelDLLMessage = (gcnew System::Windows::Forms::Label());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->tabControl->SuspendLayout();
			this->tabPageGeneral->SuspendLayout();
			this->tabPageLaunchOptions->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monitorNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResX))->BeginInit();
			this->tabPageDLLs->SuspendLayout();
			this->SuspendLayout();
			// 
			// labelAutoSave
			// 
			this->labelAutoSave->AutoSize = true;
			this->labelAutoSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->labelAutoSave->Location = System::Drawing::Point(12, 8);
			this->labelAutoSave->Name = L"labelAutoSave";
			this->labelAutoSave->Size = System::Drawing::Size(225, 13);
			this->labelAutoSave->TabIndex = 0;
			this->labelAutoSave->Text = L"All settings will be automatically saved";
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPageGeneral);
			this->tabControl->Controls->Add(this->tabPageLaunchOptions);
			this->tabControl->Controls->Add(this->tabPageDLLs);
			this->tabControl->Location = System::Drawing::Point(15, 24);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(257, 206);
			this->tabControl->TabIndex = 1;
			// 
			// tabPageGeneral
			// 
			this->tabPageGeneral->Controls->Add(this->comboPriority);
			this->tabPageGeneral->Controls->Add(this->labelPriority);
			this->tabPageGeneral->Controls->Add(this->ckbPowerSave);
			this->tabPageGeneral->Controls->Add(this->ckbAutoClose);
			this->tabPageGeneral->Controls->Add(this->ckbStartMinimized);
			this->tabPageGeneral->Controls->Add(this->ckbVSync);
			this->tabPageGeneral->Location = System::Drawing::Point(4, 22);
			this->tabPageGeneral->Name = L"tabPageGeneral";
			this->tabPageGeneral->Padding = System::Windows::Forms::Padding(3);
			this->tabPageGeneral->Size = System::Drawing::Size(249, 180);
			this->tabPageGeneral->TabIndex = 0;
			this->tabPageGeneral->Text = L"通用";
			this->tabPageGeneral->UseVisualStyleBackColor = true;
			// 
			// comboPriority
			// 
			this->comboPriority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboPriority->FormattingEnabled = true;
			this->comboPriority->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Realtime", L"High", L"Above Normal", L"Normal",
					L"Below Normal", L"Low"
			});
			this->comboPriority->Location = System::Drawing::Point(123, 92);
			this->comboPriority->Name = L"comboPriority";
			this->comboPriority->Size = System::Drawing::Size(120, 20);
			this->comboPriority->TabIndex = 5;
			this->comboPriority->TabStop = false;
			// 
			// labelPriority
			// 
			this->labelPriority->AutoSize = true;
			this->labelPriority->Location = System::Drawing::Point(7, 95);
			this->labelPriority->Name = L"labelPriority";
			this->labelPriority->Size = System::Drawing::Size(89, 12);
			this->labelPriority->TabIndex = 4;
			this->labelPriority->Text = L"游戏进程优先级";
			// 
			// ckbPowerSave
			// 
			this->ckbPowerSave->AutoSize = true;
			this->ckbPowerSave->Location = System::Drawing::Point(7, 73);
			this->ckbPowerSave->Name = L"ckbPowerSave";
			this->ckbPowerSave->Size = System::Drawing::Size(72, 16);
			this->ckbPowerSave->TabIndex = 3;
			this->ckbPowerSave->TabStop = false;
			this->ckbPowerSave->Text = L"节能模式";
			this->toolTip->SetToolTip(this->ckbPowerSave, L"Sets fps to 10 and low process priority upon losing focus (e.g. tabbing out of ga"
				L"me)");
			this->ckbPowerSave->UseVisualStyleBackColor = true;
			// 
			// ckbAutoClose
			// 
			this->ckbAutoClose->AutoSize = true;
			this->ckbAutoClose->Location = System::Drawing::Point(7, 51);
			this->ckbAutoClose->Name = L"ckbAutoClose";
			this->ckbAutoClose->Size = System::Drawing::Size(108, 16);
			this->ckbAutoClose->TabIndex = 2;
			this->ckbAutoClose->TabStop = false;
			this->ckbAutoClose->Text = L"游戏结束时退出";
			this->toolTip->SetToolTip(this->ckbAutoClose, L"Automatically close unlocker after game exits");
			this->ckbAutoClose->UseVisualStyleBackColor = true;
			// 
			// ckbStartMinimized
			// 
			this->ckbStartMinimized->AutoSize = true;
			this->ckbStartMinimized->Location = System::Drawing::Point(7, 29);
			this->ckbStartMinimized->Name = L"ckbStartMinimized";
			this->ckbStartMinimized->Size = System::Drawing::Size(132, 16);
			this->ckbStartMinimized->TabIndex = 1;
			this->ckbStartMinimized->TabStop = false;
			this->ckbStartMinimized->Text = L"最托盘化启动本程序";
			this->ckbStartMinimized->UseVisualStyleBackColor = true;
			// 
			// ckbVSync
			// 
			this->ckbVSync->AutoSize = true;
			this->ckbVSync->Location = System::Drawing::Point(7, 6);
			this->ckbVSync->Name = L"ckbVSync";
			this->ckbVSync->Size = System::Drawing::Size(138, 16);
			this->ckbVSync->TabIndex = 0;
			this->ckbVSync->TabStop = false;
			this->ckbVSync->Text = L"禁止垂直同步(VSync)";
			this->ckbVSync->UseVisualStyleBackColor = true;
			// 
			// tabPageLaunchOptions
			// 
			this->tabPageLaunchOptions->Controls->Add(this->monitorNum);
			this->tabPageLaunchOptions->Controls->Add(this->labelMonitorNum);
			this->tabPageLaunchOptions->Controls->Add(this->comboWindowMode);
			this->tabPageLaunchOptions->Controls->Add(this->labelWindowMode);
			this->tabPageLaunchOptions->Controls->Add(this->labelDummy);
			this->tabPageLaunchOptions->Controls->Add(this->customResY);
			this->tabPageLaunchOptions->Controls->Add(this->customResX);
			this->tabPageLaunchOptions->Controls->Add(this->labelCustomRes);
			this->tabPageLaunchOptions->Controls->Add(this->ckbCustomRes);
			this->tabPageLaunchOptions->Controls->Add(this->ckbFullscreen);
			this->tabPageLaunchOptions->Controls->Add(this->ckbPopupWnd);
			this->tabPageLaunchOptions->Location = System::Drawing::Point(4, 22);
			this->tabPageLaunchOptions->Name = L"tabPageLaunchOptions";
			this->tabPageLaunchOptions->Padding = System::Windows::Forms::Padding(3);
			this->tabPageLaunchOptions->Size = System::Drawing::Size(249, 180);
			this->tabPageLaunchOptions->TabIndex = 1;
			this->tabPageLaunchOptions->Text = L"登录选项";
			this->tabPageLaunchOptions->UseVisualStyleBackColor = true;
			// 
			// monitorNum
			// 
			this->monitorNum->Location = System::Drawing::Point(111, 122);
			this->monitorNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->monitorNum->Name = L"monitorNum";
			this->monitorNum->Size = System::Drawing::Size(126, 21);
			this->monitorNum->TabIndex = 10;
			this->monitorNum->TabStop = false;
			this->monitorNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// labelMonitorNum
			// 
			this->labelMonitorNum->AutoSize = true;
			this->labelMonitorNum->Location = System::Drawing::Point(7, 124);
			this->labelMonitorNum->Name = L"labelMonitorNum";
			this->labelMonitorNum->Size = System::Drawing::Size(101, 12);
			this->labelMonitorNum->TabIndex = 9;
			this->labelMonitorNum->Text = L"在那个显示器打开";
			// 
			// comboWindowMode
			// 
			this->comboWindowMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboWindowMode->FormattingEnabled = true;
			this->comboWindowMode->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Borderless", L"Exclusive" });
			this->comboWindowMode->Location = System::Drawing::Point(111, 96);
			this->comboWindowMode->Name = L"comboWindowMode";
			this->comboWindowMode->Size = System::Drawing::Size(126, 20);
			this->comboWindowMode->TabIndex = 8;
			this->comboWindowMode->TabStop = false;
			this->toolTip->SetToolTip(this->comboWindowMode, L"Fullscreen Window Mode\r\nThis will only apply if the game is running fullscreen");
			// 
			// labelWindowMode
			// 
			this->labelWindowMode->AutoSize = true;
			this->labelWindowMode->Location = System::Drawing::Point(7, 99);
			this->labelWindowMode->Name = L"labelWindowMode";
			this->labelWindowMode->Size = System::Drawing::Size(53, 12);
			this->labelWindowMode->TabIndex = 7;
			this->labelWindowMode->Text = L"窗口模式";
			// 
			// labelDummy
			// 
			this->labelDummy->AutoSize = true;
			this->labelDummy->Location = System::Drawing::Point(169, 73);
			this->labelDummy->Name = L"labelDummy";
			this->labelDummy->Size = System::Drawing::Size(11, 12);
			this->labelDummy->TabIndex = 6;
			this->labelDummy->Text = L"x";
			// 
			// customResY
			// 
			this->customResY->Location = System::Drawing::Point(182, 71);
			this->customResY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4320, 0, 0, 0 });
			this->customResY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->customResY->Name = L"customResY";
			this->customResY->Size = System::Drawing::Size(55, 21);
			this->customResY->TabIndex = 5;
			this->customResY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1080, 0, 0, 0 });
			// 
			// customResX
			// 
			this->customResX->Location = System::Drawing::Point(111, 71);
			this->customResX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7680, 0, 0, 0 });
			this->customResX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->customResX->Name = L"customResX";
			this->customResX->Size = System::Drawing::Size(55, 21);
			this->customResX->TabIndex = 4;
			this->customResX->TabStop = false;
			this->customResX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1920, 0, 0, 0 });
			// 
			// labelCustomRes
			// 
			this->labelCustomRes->AutoSize = true;
			this->labelCustomRes->Location = System::Drawing::Point(7, 73);
			this->labelCustomRes->Name = L"labelCustomRes";
			this->labelCustomRes->Size = System::Drawing::Size(77, 12);
			this->labelCustomRes->TabIndex = 3;
			this->labelCustomRes->Text = L"请输入分辨率";
			// 
			// ckbCustomRes
			// 
			this->ckbCustomRes->AutoSize = true;
			this->ckbCustomRes->Location = System::Drawing::Point(7, 51);
			this->ckbCustomRes->Name = L"ckbCustomRes";
			this->ckbCustomRes->Size = System::Drawing::Size(144, 16);
			this->ckbCustomRes->TabIndex = 2;
			this->ckbCustomRes->TabStop = false;
			this->ckbCustomRes->Text = L"自定义原神窗口分辨率";
			this->ckbCustomRes->UseVisualStyleBackColor = true;
			// 
			// ckbFullscreen
			// 
			this->ckbFullscreen->AutoSize = true;
			this->ckbFullscreen->Location = System::Drawing::Point(7, 29);
			this->ckbFullscreen->Name = L"ckbFullscreen";
			this->ckbFullscreen->Size = System::Drawing::Size(48, 16);
			this->ckbFullscreen->TabIndex = 1;
			this->ckbFullscreen->TabStop = false;
			this->ckbFullscreen->Text = L"全屏";
			this->ckbFullscreen->UseVisualStyleBackColor = true;
			// 
			// ckbPopupWnd
			// 
			this->ckbPopupWnd->AutoSize = true;
			this->ckbPopupWnd->Location = System::Drawing::Point(7, 6);
			this->ckbPopupWnd->Name = L"ckbPopupWnd";
			this->ckbPopupWnd->Size = System::Drawing::Size(84, 16);
			this->ckbPopupWnd->TabIndex = 0;
			this->ckbPopupWnd->TabStop = false;
			this->ckbPopupWnd->Text = L"弹出式窗口";
			this->toolTip->SetToolTip(this->ckbPopupWnd, L"Launch the game in borderless windowed mode");
			this->ckbPopupWnd->UseVisualStyleBackColor = true;
			// 
			// tabPageDLLs
			// 
			this->tabPageDLLs->Controls->Add(this->btnDllRemove);
			this->tabPageDLLs->Controls->Add(this->btnDllAdd);
			this->tabPageDLLs->Controls->Add(this->lbDllList);
			this->tabPageDLLs->Controls->Add(this->labelDLLMessage);
			this->tabPageDLLs->Location = System::Drawing::Point(4, 22);
			this->tabPageDLLs->Name = L"tabPageDLLs";
			this->tabPageDLLs->Padding = System::Windows::Forms::Padding(3);
			this->tabPageDLLs->Size = System::Drawing::Size(249, 180);
			this->tabPageDLLs->TabIndex = 2;
			this->tabPageDLLs->Text = L"DLLs";
			this->tabPageDLLs->UseVisualStyleBackColor = true;
			// 
			// btnDllRemove
			// 
			this->btnDllRemove->Location = System::Drawing::Point(136, 48);
			this->btnDllRemove->Name = L"btnDllRemove";
			this->btnDllRemove->Size = System::Drawing::Size(107, 21);
			this->btnDllRemove->TabIndex = 3;
			this->btnDllRemove->TabStop = false;
			this->btnDllRemove->Text = L"Remove";
			this->btnDllRemove->UseVisualStyleBackColor = true;
			this->btnDllRemove->Click += gcnew System::EventHandler(this, &SettingsForm::btnDllRemove_Click);
			// 
			// btnDllAdd
			// 
			this->btnDllAdd->Location = System::Drawing::Point(136, 21);
			this->btnDllAdd->Name = L"btnDllAdd";
			this->btnDllAdd->Size = System::Drawing::Size(107, 21);
			this->btnDllAdd->TabIndex = 2;
			this->btnDllAdd->TabStop = false;
			this->btnDllAdd->Text = L"Add";
			this->btnDllAdd->UseVisualStyleBackColor = true;
			this->btnDllAdd->Click += gcnew System::EventHandler(this, &SettingsForm::btnDllAdd_Click);
			// 
			// lbDllList
			// 
			this->lbDllList->FormattingEnabled = true;
			this->lbDllList->ItemHeight = 12;
			this->lbDllList->Location = System::Drawing::Point(10, 22);
			this->lbDllList->Name = L"lbDllList";
			this->lbDllList->Size = System::Drawing::Size(120, 148);
			this->lbDllList->TabIndex = 1;
			this->lbDllList->TabStop = false;
			// 
			// labelDLLMessage
			// 
			this->labelDLLMessage->AutoSize = true;
			this->labelDLLMessage->Location = System::Drawing::Point(7, 6);
			this->labelDLLMessage->Name = L"labelDLLMessage";
			this->labelDLLMessage->Size = System::Drawing::Size(287, 12);
			this->labelDLLMessage->TabIndex = 0;
			this->labelDLLMessage->Text = L"DLLs will be injected in the order of this list";
			// 
			// toolTip
			// 
			this->toolTip->AutoPopDelay = 5000;
			this->toolTip->InitialDelay = 1;
			this->toolTip->ReshowDelay = 100;
			// 
			// SettingsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 241);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->labelAutoSave);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"SettingsForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings";
			this->tabControl->ResumeLayout(false);
			this->tabPageGeneral->ResumeLayout(false);
			this->tabPageGeneral->PerformLayout();
			this->tabPageLaunchOptions->ResumeLayout(false);
			this->tabPageLaunchOptions->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monitorNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResX))->EndInit();
			this->tabPageDLLs->ResumeLayout(false);
			this->tabPageDLLs->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void UpdateSettings(Object^ sender, FormClosingEventArgs^ e);
	private: Void btnDllRemove_Click(Object^ sender, EventArgs^ e);
	private: Void OnLoad(Object^ sender, EventArgs^ e);
	private: Void btnDllAdd_Click(Object^ sender, EventArgs^ e);
	private: Void OnFormat(Object^ sender, ListControlConvertEventArgs^ e);
	};
}