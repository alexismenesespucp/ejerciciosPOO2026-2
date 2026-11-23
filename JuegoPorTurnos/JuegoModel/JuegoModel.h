#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace JuegoModel {
	public ref class tablero
	{
	private:
		int filas = 3;
		int columnas = 3;
		int tamanoCelda = 50;

		List<Point>^ jugador1;
		List<Point>^ jugador2;

	public:

		void DibujarTablero(Graphics^ g) {
			if (jugador1 == nullptr) {
				jugador1 = gcnew List<Point>();
			}
			if (jugador2 == nullptr) {
				jugador2 = gcnew List<Point>();
			}

			for (int i = 0; i < this->filas; i++) {
				for (int j = 0; j < this->columnas; j++) {
					int x = j * tamanoCelda;
					int y = i * tamanoCelda;
					SolidBrush^ brochaPared = gcnew SolidBrush(Color::FromArgb(255, 255, 255));
					g->FillRectangle(brochaPared, x, y, tamanoCelda, tamanoCelda);
					g->DrawRectangle(gcnew Pen(Color::FromArgb(0,0, 0), 1), x, y, tamanoCelda, tamanoCelda);
				}
			}
			Console::WriteLine("Dibujando tablero + " + jugador1->Count);
			for each(Point p in jugador1) {
				int x = p.X * tamanoCelda;
				int y = p.Y * tamanoCelda;
				SolidBrush^ brochaPared = gcnew SolidBrush(Color::FromArgb(255, 0, 0));
				g->FillRectangle(brochaPared, x, y, tamanoCelda, tamanoCelda);
				g->DrawRectangle(gcnew Pen(Color::FromArgb(0, 0, 0), 1), x, y, tamanoCelda, tamanoCelda);
			}
			for each (Point p in jugador2) {
				int x = p.X * tamanoCelda;
				int y = p.Y * tamanoCelda;
				SolidBrush^ brochaPared = gcnew SolidBrush(Color::FromArgb(0, 255, 0));
				g->FillRectangle(brochaPared, x, y, tamanoCelda, tamanoCelda);
				g->DrawRectangle(gcnew Pen(Color::FromArgb(0, 0, 0), 1), x, y, tamanoCelda, tamanoCelda);
			}


		}

		void PintarCelda(int _x, int _y) {
			int i = _x / this->tamanoCelda;
			int j = _y / this->tamanoCelda;
			if (i < 0 || i >= this->columnas || j < 0 || j >= this->filas) {
				return;
			}
			this->jugador1->Add(Point(i, j));
		}

		void PintarCeldaOpenente(int _x, int _y) {
			int i = _x / this->tamanoCelda;
			int j = _y / this->tamanoCelda;
			if (i < 0 || i >= this->columnas || j < 0 || j >= this->filas) {
				return;
			}
			this->jugador2->Add(Point(i, j));
		}
	};
}
