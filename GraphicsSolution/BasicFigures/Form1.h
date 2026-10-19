#pragma once

namespace BasicFigures {

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
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(787, 518);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;

		// Dibuja una línea desde (20, 20) hasta (200, 20)
		g->DrawLine(Pens::Black, 20, 20, 200, 20);

		// Dibuja un rectángulo con posición (30, 40), ancho 100 y alto 50
		g->DrawRectangle(Pens::Blue, 30, 40, 100, 50);

		// Dibuja un círculo usando un rectángulo delimitador
		g->DrawEllipse(Pens::Red, 50, 100, 50, 50);

		Pen^ customPen = gcnew Pen(Color::Green, 3); // Color Verde, grosor 3
		g->DrawLine(customPen, 10, 10, 150, 10);

		array<Point>^ bezierPoints = { Point(50, 150), Point(80, 40), Point(200, 200), Point(250, 50) };
		g->DrawBezier(Pens::Purple, bezierPoints[0], bezierPoints[1], bezierPoints[2], bezierPoints[3]);

		SolidBrush^ redBrush = gcnew SolidBrush(Color::Red);
		g->FillRectangle(redBrush, 30, 40, 100, 50);
	}
	};
}
