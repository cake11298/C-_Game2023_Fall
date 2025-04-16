#pragma once
#include <math.h>
#include <iostream>

struct vw
{
	float V;
	float W;
};

struct points
{
	float HP;
	float SP;
	float MP;
};

struct posi
{
	float X;
	float Y;
	float Theta = 1.57;
};

struct bits
{
	unsigned char hit : 1;
	unsigned char speedup : 1;
	unsigned char sp_disable : 1;
	unsigned char mp_disbale : 1;
	unsigned char freeze : 1;
	unsigned char sp_up : 1;
	unsigned char mp_up : 1;
	unsigned char hp_up : 1;
};

union byte_bits
{
	bits b;
	unsigned char B;
};

struct profile
{
	char name[20] = "456"; struct posi pos; struct vw vel; struct points point; int t;
	union byte_bits status;
};

struct enemy_profile {
	char name[20]= "123"; struct posi pos; struct points point; union byte_bits status;
};

struct profile tank_profile;
struct enemy_profile obs;
int system_counter = 0;
float dt = 0.1;



namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::ProgressBar^ progressBar3;
	private: System::Windows::Forms::ProgressBar^ progressBar2;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->progressBar3 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::Color::Black;
			this->button1->Location = System::Drawing::Point(526, 191);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 39);
			this->button1->TabIndex = 0;
			this->button1->Text = L"front";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(526, 236);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 33);
			this->button2->TabIndex = 1;
			this->button2->Text = L"stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->ForeColor = System::Drawing::Color::Black;
			this->button3->Location = System::Drawing::Point(526, 275);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 30);
			this->button3->TabIndex = 2;
			this->button3->Text = L"back";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->ForeColor = System::Drawing::Color::Black;
			this->button4->Location = System::Drawing::Point(445, 236);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 33);
			this->button4->TabIndex = 3;
			this->button4->Text = L"left";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->ForeColor = System::Drawing::Color::Black;
			this->button5->Location = System::Drawing::Point(607, 236);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 32);
			this->button5->TabIndex = 4;
			this->button5->Text = L"right";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->progressBar3);
			this->panel1->Controls->Add(this->progressBar2);
			this->panel1->Controls->Add(this->progressBar1);
			this->panel1->Location = System::Drawing::Point(646, 355);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(286, 193);
			this->panel1->TabIndex = 5;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label4->Location = System::Drawing::Point(137, 48);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(41, 15);
			this->label4->TabIndex = 6;
			this->label4->Text = L"label4";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label3->Location = System::Drawing::Point(140, 141);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 15);
			this->label3->TabIndex = 5;
			this->label3->Text = L"label3";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label2->Location = System::Drawing::Point(137, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 15);
			this->label2->TabIndex = 4;
			this->label2->Text = L"label2";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label1->Location = System::Drawing::Point(20, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
			// 
			// progressBar3
			// 
			this->progressBar3->Location = System::Drawing::Point(14, 134);
			this->progressBar3->Name = L"progressBar3";
			this->progressBar3->Size = System::Drawing::Size(100, 23);
			this->progressBar3->TabIndex = 2;
			this->progressBar3->Click += gcnew System::EventHandler(this, &Form1::progressBar3_Click);
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(14, 91);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(100, 23);
			this->progressBar2->TabIndex = 1;
			this->progressBar2->Click += gcnew System::EventHandler(this, &Form1::progressBar2_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(14, 48);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(100, 23);
			this->progressBar1->TabIndex = 0;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Form1::progressBar1_Click);
			// 
			// Form1
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(982, 953);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->ForeColor = System::Drawing::Color::Cornsilk;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		void Load_profile(void)
		{
			FILE* pFile;
			pFile = fopen("profile.txt", "r");
			fscanf(pFile, "%s", tank_profile.name);
			fscanf(pFile, "%f", &tank_profile.pos.X);
			fscanf(pFile, "%f", &tank_profile.pos.Y);
			fscanf(pFile, "%f",
				&tank_profile.pos.Theta);
			fscanf(pFile, "%f", &tank_profile.t);
			fscanf(pFile, "%f",
				&tank_profile.point.HP);
			fscanf(pFile, "%f",
				&tank_profile.point.SP);
			fscanf(pFile, "%f",
				&tank_profile.point.MP);
			fclose(pFile);
		};
		void text_displayer(void)
		{
			String^ str = gcnew String(tank_profile.name);
			this->label1->Text = str;
			this->progressBar1->Value = tank_profile.point.HP;
			this->label2->Text = ("HP:" + Convert::ToString(tank_profile.point.HP) + "/100"); this->progressBar2->Value = tank_profile.point.SP;
			this->label3->Text = ("SP:" + Convert::ToString(tank_profile.point.SP) + "/100"); this->progressBar3->Value = tank_profile.point.MP;
			this->label4->Text = ("MP:" + Convert::ToString(tank_profile.point.MP) + "/100");
		};
		void plot_HMI(void)
		{
			Graphics^ e1 = this->CreateGraphics();
			e1->Clear(Color::WhiteSmoke);
			Pen^ pen_B = gcnew Pen(Color::Blue, 2);
			Pen^ pen_k = gcnew Pen(Color::Black, 1);
			int R_size = 20;
			int grid_width = 400;
			int grid_height = 400;
			int grid_resolution = 1;
			int shift_x = (grid_width / 2); //
			int shift_y = (grid_height)+0;
			int Y_shift = 0; int x1 = (tank_profile.pos.X) / grid_resolution;
			int y1 = (tank_profile.pos.Y + Y_shift) / grid_resolution;
			e1->DrawEllipse(pen_B, shift_x + x1 - R_size / 2, shift_y - y1 - R_size / 2, R_size, R_size); int dir_x = 15 * cos(tank_profile.pos.Theta);
			int dir_y = 15 * sin(tank_profile.pos.Theta);
			e1->DrawLine(pen_B, shift_x + 0 + x1, shift_y - y1, shift_x + x1 + 0 + dir_x, shift_y - y1 - dir_y);
			x1 = (obs.pos.X) / grid_resolution;
			y1 = (obs.pos.Y + Y_shift) / grid_resolution;
			e1->DrawRectangle(pen_k, shift_x + 0 + x1, shift_y - y1, 20, 20);
		};
		void Motion_model(void)
		{
			tank_profile.pos.X = tank_profile.pos.X +
				tank_profile.vel.V * cos(tank_profile.pos.Theta) * dt;
			tank_profile.pos.Y = tank_profile.pos.Y +
				tank_profile.vel.V * sin(tank_profile.pos.Theta) * dt;
			tank_profile.pos.Theta = tank_profile.pos.Theta +
				tank_profile.vel.W * dt;
			obs.pos.X = obs.pos.X + 35 * dt;
			obs.pos.Y = obs.pos.Y + 35 * dt;
			obs.pos.X = int(obs.pos.X) % 300;
			obs.pos.Y = int(obs.pos.Y) % 300;
		};
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		tank_profile.vel.V = 5 * 5;
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (system_counter == 0)
		{
			Load_profile();
		}
		Motion_model();
		plot_HMI();
		text_displayer();
		system_counter++;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		tank_profile.vel.V = 0;
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			tank_profile.vel.V = -5 * 5;
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		//left
		tank_profile.vel.W = 0.174 * 5;
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		//right
		tank_profile.vel.W = -0.174 * 5;
	}

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void progressBar1_Click(System::Object^ sender, System::EventArgs^ e) {
	
	}
	private: System::Void progressBar2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void progressBar3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
