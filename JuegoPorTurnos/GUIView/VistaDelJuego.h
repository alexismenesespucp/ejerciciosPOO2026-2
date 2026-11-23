#pragma once

namespace GUIView {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace JuegoController;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for VistaDelJuego
	/// </summary>
	public ref class VistaDelJuego : public System::Windows::Forms::Form
	{
	public:
		Thread^ threadConexion;
		delegate void ActualizarConexion();
		delegate void ObtenerConexionActivas();

		VistaDelJuego(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			Controller::ObtenerIps();
			for each (String ^ ipAddress in Controller::ips) {
				Controller::GuardarConexion(ipAddress);
			}
			threadConexion = gcnew Thread(gcnew ThreadStart(this, &VistaDelJuego::ObtenerInformacionBaseDeDatos));
			threadConexion->Start();
		}

		void ObtenerInformacionBaseDeDatos() {
			while (true) {
				Thread::Sleep(5000);
				ActualizarConexion^ actualizar = gcnew ActualizarConexion(this, &VistaDelJuego::ActualizarConexiones);
				ObtenerConexionActivas^ obtener = gcnew ObtenerConexionActivas(this, &VistaDelJuego::ObtenerConexionesActivas);
				this->Invoke(obtener);
				this->Invoke(actualizar);
			}
		}

		void ActualizarConexiones() {
			for each (String ^ ipAddress in Controller::ips) {
				Controller::UpdateConexion(ipAddress);
			}
		}

		void  ObtenerConexionesActivas() {
			List<String^>^ conexiones = Controller::ObtenerConexionActivas();
			

			for each (String^ conexion in conexiones) {
				if (Controller::ips->Contains(conexion)) {
					Console::WriteLine("Conexión activa propia: " + conexion);
				}
				else {
					if (this->comboBox1->Items->Contains(conexion)) {
						continue;
					}
					this->comboBox1->Items->Add(conexion);
				}
				Console::WriteLine("Conexión activa: " + conexion);
			}

			Console::WriteLine("Conexiones activas: " + conexiones->Count);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~VistaDelJuego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ turno;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ play;

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
			this->turno = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->play = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(120, 172);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(266, 205);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &VistaDelJuego::pictureBox1_Click);
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VistaDelJuego::pictureBox1_Paint);
			// 
			// turno
			// 
			this->turno->AutoSize = true;
			this->turno->Location = System::Drawing::Point(451, 172);
			this->turno->Name = L"turno";
			this->turno->Size = System::Drawing::Size(47, 13);
			this->turno->TabIndex = 1;
			this->turno->Text = L"Tu turno";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(120, 93);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(266, 21);
			this->comboBox1->TabIndex = 2;
			// 
			// play
			// 
			this->play->Location = System::Drawing::Point(454, 93);
			this->play->Name = L"play";
			this->play->Size = System::Drawing::Size(91, 23);
			this->play->TabIndex = 3;
			this->play->Text = L"Jugar";
			this->play->UseVisualStyleBackColor = true;
			// 
			// VistaDelJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(695, 485);
			this->Controls->Add(this->play);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->turno);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"VistaDelJuego";
			this->Text = L"VistaDelJuego";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Controller::DibujarTablero(e->Graphics);
		
	}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	int x = pictureBox1->PointToClient(Cursor->Position).X;
	int y = pictureBox1->PointToClient(Cursor->Position).Y;
	
	Controller::PintarCelda(x, y);

	this->pictureBox1->Invalidate();

	Console::WriteLine("X: " + x + " Y: " + y);
}
};
}
