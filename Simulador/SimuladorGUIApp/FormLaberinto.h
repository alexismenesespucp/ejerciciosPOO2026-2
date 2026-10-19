#pragma once

namespace SimuladorGUIApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace SimuladorController;

	/// <summary>
	/// Summary for FormLaberinto
	/// </summary>
	public ref class FormLaberinto : public System::Windows::Forms::Form
	{
	public:
		FormLaberinto(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormLaberinto()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(56, 40);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(486, 439);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &FormLaberinto::s);
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormLaberinto::laberinto_Paint);
			// 
			// FormLaberinto
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(681, 547);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"FormLaberinto";
			this->Text = L"FormLaberinto";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void laberinto_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		SimuladorLaberintoController::Renderizar(e->Graphics);
	}
	private: System::Void s(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
