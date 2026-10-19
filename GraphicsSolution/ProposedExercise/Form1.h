#pragma once

namespace ProposedExercise {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			this->DoubleBuffered = true; // Evita el parpadeo en la animación
			xPosition = 0;
			timer1->Enabled = true;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::IContainer^ components;
		int xPosition; // Posición X del rectángulo en movimiento
		System::Windows::Forms::Timer^ timer1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1386, 947);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion

		private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			Pen^ wavePen = gcnew Pen(Color::Blue, 2); // Pen para la onda
			SolidBrush^ rectBrush = gcnew SolidBrush(Color::Red); // Brocha para el rectángulo

			// Parámetros de la onda
			double amplitude = 50;
			double frequency = 0.05; // Cambiar este valor cambia la longitud de onda
			double offsetY = 200; // Posición vertical de la onda

			// Dibuja la onda cosenoidal
			for (int x = 0; x < this->ClientSize.Width; ++x) {
				double y = offsetY + amplitude * Math::Cos(frequency * x);
				g->DrawRectangle(Pens::Blue, x, y, 1, 1); // Punto para la onda
			}

			// Dibuja el rectángulo en movimiento siguiendo la onda cosenoidal
			double yRect = offsetY + amplitude * Math::Cos(frequency * xPosition);
			g->FillRectangle(rectBrush, xPosition, yRect - 10, 20, 20); // Rectángulo de 20x20
		}

		private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			xPosition += 5; // Incrementa la posición X para mover el rectángulo
			if (xPosition > this->ClientSize.Width) 
				xPosition = 0; // Repetir movimiento
			this->Invalidate(); // Refresca la pantalla
		}
	};
}
