#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BIAS 1
#define dimension 2
#define learning_rate 0.5
#define EPSILON 0.001

namespace SingleLayerFeedForward {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			weigths  = nullptr;
			y = nullptr;
			target = (double**)malloc(1 * sizeof(double*));
			classes = (double**)malloc(1 * sizeof(double*));
			exampleSize = 0;
			classSize = 0;
			scale = 0;
			isTrained = false;
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
				free(classes);
				free(target);
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ labelX;
	private: System::Windows::Forms::Label^ labelY;


	protected:

	private:
		double** classes;
		double** weigths;
		double** target;
		int exampleSize;
		int classSize;
		int* y;
		int scale;
		Boolean isTrained;

	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ trainButton1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::CheckBox^ checkBoxBatchNorm;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::RadioButton^ radioButtonContinuous;
	private: System::Windows::Forms::RadioButton^ radioButtonDiscrete;


	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Panel^ panelError;

	private: System::Windows::Forms::Label^ label8;

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->labelX = (gcnew System::Windows::Forms::Label());
			this->labelY = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->trainButton1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panelError = (gcnew System::Windows::Forms::Panel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonDiscrete = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonContinuous = (gcnew System::Windows::Forms::RadioButton());
			this->checkBoxBatchNorm = (gcnew System::Windows::Forms::CheckBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panelError->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(38, 30);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(539, 490);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// labelX
			// 
			this->labelX->AutoSize = true;
			this->labelX->Location = System::Drawing::Point(63, 16);
			this->labelX->Name = L"labelX";
			this->labelX->Size = System::Drawing::Size(0, 19);
			this->labelX->TabIndex = 1;
			// 
			// labelY
			// 
			this->labelY->AutoSize = true;
			this->labelY->Location = System::Drawing::Point(63, 49);
			this->labelY->Name = L"labelY";
			this->labelY->Size = System::Drawing::Size(0, 19);
			this->labelY->TabIndex = 2;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown1->Location = System::Drawing::Point(129, 3);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(84, 27);
			this->numericUpDown1->TabIndex = 5;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(129, 42);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(84, 27);
			this->comboBox1->TabIndex = 6;
			// 
			// trainButton1
			// 
			this->trainButton1->BackColor = System::Drawing::SystemColors::Control;
			this->trainButton1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->trainButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->trainButton1->Location = System::Drawing::Point(38, 452);
			this->trainButton1->Name = L"trainButton1";
			this->trainButton1->Size = System::Drawing::Size(157, 31);
			this->trainButton1->TabIndex = 7;
			this->trainButton1->Text = L"Train";
			this->trainButton1->UseVisualStyleBackColor = false;
			this->trainButton1->Click += gcnew System::EventHandler(this, &MyForm::trainButton1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(94, 19);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 19);
			this->label4->TabIndex = 8;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->labelX);
			this->panel1->Controls->Add(this->labelY);
			this->panel1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel1->Location = System::Drawing::Point(37, 211);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(158, 133);
			this->panel1->TabIndex = 9;
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->label4);
			this->panel3->Location = System::Drawing::Point(-1, 81);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(157, 50);
			this->panel3->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 17);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(85, 19);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Iteration =";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 19);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Y = ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 19);
			this->label1->TabIndex = 3;
			this->label1->Text = L"X =";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlDark;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->panelError);
			this->panel2->Controls->Add(this->groupBox1);
			this->panel2->Controls->Add(this->checkBoxBatchNorm);
			this->panel2->Controls->Add(this->panel4);
			this->panel2->Controls->Add(this->panel1);
			this->panel2->Controls->Add(this->trainButton1);
			this->panel2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel2->Location = System::Drawing::Point(592, 30);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(241, 490);
			this->panel2->TabIndex = 10;
			// 
			// panelError
			// 
			this->panelError->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panelError->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panelError->Controls->Add(this->label8);
			this->panelError->Controls->Add(this->label7);
			this->panelError->Location = System::Drawing::Point(38, 350);
			this->panelError->Name = L"panelError";
			this->panelError->Size = System::Drawing::Size(157, 38);
			this->panelError->TabIndex = 17;
			this->panelError->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 10);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(59, 19);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Error =";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(69, 10);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(0, 19);
			this->label7->TabIndex = 14;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ControlDark;
			this->groupBox1->Controls->Add(this->radioButtonDiscrete);
			this->groupBox1->Controls->Add(this->radioButtonContinuous);
			this->groupBox1->Location = System::Drawing::Point(3, 88);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(231, 60);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Functions";
			// 
			// radioButtonDiscrete
			// 
			this->radioButtonDiscrete->AutoSize = true;
			this->radioButtonDiscrete->Location = System::Drawing::Point(6, 26);
			this->radioButtonDiscrete->Name = L"radioButtonDiscrete";
			this->radioButtonDiscrete->Size = System::Drawing::Size(87, 23);
			this->radioButtonDiscrete->TabIndex = 12;
			this->radioButtonDiscrete->TabStop = true;
			this->radioButtonDiscrete->Text = L"Discrete";
			this->radioButtonDiscrete->UseVisualStyleBackColor = true;
			// 
			// radioButtonContinuous
			// 
			this->radioButtonContinuous->AutoSize = true;
			this->radioButtonContinuous->Location = System::Drawing::Point(105, 26);
			this->radioButtonContinuous->Name = L"radioButtonContinuous";
			this->radioButtonContinuous->Size = System::Drawing::Size(110, 23);
			this->radioButtonContinuous->TabIndex = 13;
			this->radioButtonContinuous->TabStop = true;
			this->radioButtonContinuous->Text = L"Continuous";
			this->radioButtonContinuous->UseVisualStyleBackColor = true;
			// 
			// checkBoxBatchNorm
			// 
			this->checkBoxBatchNorm->AutoSize = true;
			this->checkBoxBatchNorm->Location = System::Drawing::Point(9, 165);
			this->checkBoxBatchNorm->Name = L"checkBoxBatchNorm";
			this->checkBoxBatchNorm->Size = System::Drawing::Size(175, 23);
			this->checkBoxBatchNorm->TabIndex = 11;
			this->checkBoxBatchNorm->Text = L"Batch Normalization";
			this->checkBoxBatchNorm->UseVisualStyleBackColor = true;
			this->checkBoxBatchNorm->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxBatchNorm_CheckedChanged);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::SystemColors::ControlDark;
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel4->Controls->Add(this->label3);
			this->panel4->Controls->Add(this->numericUpDown1);
			this->panel4->Controls->Add(this->comboBox1);
			this->panel4->Controls->Add(this->label5);
			this->panel4->Location = System::Drawing::Point(3, 3);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(231, 79);
			this->panel4->TabIndex = 16;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 11);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(102, 19);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Class Size    =";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(19, 50);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(104, 19);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Select Class =";
			// 
			// trackBar1
			// 
			this->trackBar1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->trackBar1->Location = System::Drawing::Point(38, 526);
			this->trackBar1->Maximum = 50;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->RightToLeftLayout = true;
			this->trackBar1->Size = System::Drawing::Size(795, 56);
			this->trackBar1->TabIndex = 11;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(845, 575);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MyForm";
			this->Text = L"SingleLayerFeedForward";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panelError->ResumeLayout(false);
			this->panelError->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Pen^ p = gcnew Pen(Color::Black);
		e->Graphics->DrawLine(p, 0, pictureBox1->Height / 2, pictureBox1->Width, pictureBox1->Height / 2);
		e->Graphics->DrawLine(p, pictureBox1->Width / 2, 0, pictureBox1->Width / 2, pictureBox1->Height);

		if (isTrained == true) {
			for (int i = 0; i < classSize; i++) {
				y[2 * i] = -((float)(pictureBox1->Width / -2) * weigths[i][0] + BIAS * weigths[i][2]) / weigths[i][1];
				y[2 * i + 1] = -((float)(pictureBox1->Width / 2) * weigths[i][0] + BIAS * weigths[i][2]) / weigths[i][1];
			}
		}
		
		if (classSize == 1) {
			for (int i = 0; i < exampleSize; i++){
				(target[i][0] == 1 ? p->Color = Color::Red : p->Color = Color::Green);
				e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
				p->Color = Color::Blue;
				e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[0]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[1]) - pictureBox1->Height / 2);
			}
		}
		else {
			for (int i = 0; i < exampleSize; i++) {
				if (target[i][0] == 1) {
					p->Color = Color::Red;
					e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
					e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[0]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[1]) - pictureBox1->Height / 2);
				}
				else if (target[i][1] == 1) {
					p->Color = Color::Green;
					e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
					e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[2]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[3]) - pictureBox1->Height / 2);
				}
				else if (target[i][2] == 1) {
					p->Color = Color::Blue;
					e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
					e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[4]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[5]) - pictureBox1->Height / 2);
				}
				else if (target[i][3] == 1) {
					p->Color = Color::Orange;
					e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
					e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[6]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[7]) - pictureBox1->Height / 2);
				}
				else {
					p->Color = Color::Purple;
					e->Graphics->DrawRectangle(p, classes[i][0] + (pictureBox1->Width / 2), (pictureBox1->Height / 2) - classes[i][1], 2, 2);
					e->Graphics->DrawLine(p, 0, (pictureBox1->Height - y[8]) - pictureBox1->Height / 2, (pictureBox1->Width), (pictureBox1->Height - y[9]) - pictureBox1->Height / 2);
				}
			}
		}
	}
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (comboBox1->SelectedIndex != -1) {
			Pen^ p = gcnew Pen(Color::Red);
			Graphics^ g = pictureBox1->CreateGraphics();

			int x = e->X - (pictureBox1->Width / 2);
			int y = (pictureBox1->Height / 2) - e->Y;

			classes[exampleSize] = (double*)malloc((dimension+1) * sizeof(double));
			target[exampleSize] = (double*)malloc((classSize) * sizeof(double));

			for (int i = exampleSize; i < exampleSize + 1; i++) {
				for (int j = 0; j < classSize; j++) {
					target[i][j] = -1;
				}
			}

			classes[exampleSize][0] = x;
			classes[exampleSize][1] = y;
			classes[exampleSize][2] = BIAS;

			switch (comboBox1->SelectedIndex)
			{
			case 0: //class1
				g->DrawRectangle(p, e->X, e->Y, 2, 2);
				target[exampleSize][0] = 1;
				break;
			case 1: //class2
				p->Color = Color::Green;
				g->DrawRectangle(p, e->X, e->Y, 2, 2);
				if (classSize != 1) target[exampleSize][1] = 1;
				break;
			case 2: //class3
				p->Color = Color::Blue;
				g->DrawRectangle(p, e->X, e->Y, 2, 2);
				target[exampleSize][2] = 1;
				break;
			case 3: //class4
				p->Color = Color::Orange;
				g->DrawRectangle(p, e->X, e->Y, 2, 2);
				target[exampleSize][3] = 1;
				break;
			case 4: //class5
				p->Color = Color::Purple;
				g->DrawRectangle(p, e->X, e->Y, 2, 2);
				target[exampleSize][4] = 1;
				break;
			}
			exampleSize++;

			target = (double**)realloc(target, (exampleSize + 1) * sizeof(double*));
			classes = (double**)realloc(classes, (exampleSize + 1) * sizeof(double*));
		}
	}
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		labelX->Text = (e->X - (pictureBox1->Width / 2)).ToString();
		labelY->Text = ((pictureBox1->Height / 2) - e->Y).ToString();
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		comboBox1->Items->Clear();
		classSize = (int)numericUpDown1->Value;

		for (int i = 0; i < classSize; i++)
			comboBox1->Items->Add("Class " + (i + 1));

		if (classSize == 2) // Two classes can be seperate with a line. 
			classSize = 1;

		weigths = new double* [classSize];
		y = new int[classSize * 2];
	
		for (int i = 0; i < classSize; i++)
			weigths[i] = new double[dimension + 1];
		srand((unsigned int)time(NULL));

		for (int i = 0; i < classSize; i++)
			for (int j = 0; j < dimension + 1; j++)
				weigths[i][j] = (float)rand() / RAND_MAX;
	}
	private: System::Void trainButton1_Click(System::Object^ sender, System::EventArgs^ e) {
		isTrained = true;
		double* NET = new double[classSize];
		double* output = new double[classSize];
		double error=0.0;
		int iteration=0;
		if (radioButtonDiscrete->Checked == true) {
			int error_counter = classSize * exampleSize;
			while (error_counter > 0) {
				label4->Refresh();
				error_counter = classSize * exampleSize;
				for (int e_s = 0; e_s < exampleSize; e_s++) {
					for (int i = 0; i < classSize; i++) {
						NET[i] = weigths[i][0] * classes[e_s][0] + weigths[i][1] * classes[e_s][1] + weigths[i][2] * BIAS;
						(NET[i] > 0) ? output[i] = 1 : output[i] = -1;
						if (output[i] != target[e_s][i]) {
							error = target[e_s][i] - output[i];
							for (int j = 0; j < dimension + 1; j++)
								weigths[i][j] += learning_rate * error * classes[e_s][j];
						}
						else
							error_counter--;
					}
				}
				pictureBox1->Refresh();
				label4->Text = iteration.ToString();
				iteration++;
			}
		}
		else if (radioButtonContinuous->Checked == true) {
			panelError->Visible = true;
			label8->Refresh();
			double derivate;
			double totalError;
			do {
				label4->Refresh();
				label7->Refresh();
				totalError = 0.0;
				for (int e_s = 0; e_s < exampleSize; e_s++) {
					for (int i = 0; i < classSize; i++) {
						NET[i] = weigths[i][0] * classes[e_s][0] + weigths[i][1] * classes[e_s][1] + weigths[i][2] * BIAS;
						output[i] = 2.0 / (1.0 + exp(-NET[i])) - 1.0; // Bipolar Sigmoid Activation Function.
						derivate = 0.5 * (1.0 - pow(output[i], 2));	  // f'(net)
						error = target[e_s][i] - output[i];				
						totalError += 0.5 * pow(error, 2);
						for(int j=0;j<dimension+1;j++)
							weigths[i][j] = weigths[i][j] + learning_rate * (target[e_s][i] - output[i]) * derivate * classes[e_s][j];
					}
					pictureBox1->Refresh();
				}
				label4->Text = iteration.ToString();
				label7->Text = error.ToString();
				iteration++;
			} while (totalError > EPSILON);
		}
	}
	private: System::Void checkBoxBatchNorm_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		int total_x = 0, total_y = 0;
		int batch_mean_x = 0, batch_mean_y = 0;
		int batch_variance_x = 0, batch_variance_y = 0;

		//Batch Mean
		for (int i = 0; i < exampleSize; i++) {
			total_x += classes[i][0];
			total_y += classes[i][1];
		}
		batch_mean_x /= exampleSize;
		batch_mean_y /= exampleSize;

		//Batch Variance
		for (int i = 0; i < exampleSize; i++) {
			total_x += pow(classes[i][0] - batch_mean_x, 2);
			total_y += pow(classes[i][1] - batch_mean_y, 2);
		}
		batch_variance_x = total_x / exampleSize;
		batch_variance_y = total_y / exampleSize;

		//Batch Normalization
		for (int i = 0; i < exampleSize; i++) {
			classes[i][0] = (classes[i][0] - batch_mean_x) / sqrt(batch_variance_x);
			classes[i][1] = (classes[i][1] - batch_mean_y) / sqrt(batch_variance_y);
		}
		pictureBox1->Refresh();
	}
	private: System::Void trackBar1_Scroll_1(System::Object^ sender, System::EventArgs^ e) {
		if (trackBar1->Value > scale) {
			for (int i = 0; i < exampleSize; i++) {
				classes[i][0] *= 1.1;
				classes[i][1] *= 1.1;
			}
			for (int i = 0; i < classSize; i++) {
				weigths[i][2] *= 1.1;
			}
		}
		else {
			for (int i = 0; i < exampleSize; i++) {
				classes[i][0] /= 1.1;
				classes[i][1] /= 1.1;
			}
			for (int i = 0; i < classSize; i++) {
				weigths[i][2] /= 1.1;
			}
		}
		pictureBox1->Refresh();
		scale = trackBar1->Value;
	}
};
}
