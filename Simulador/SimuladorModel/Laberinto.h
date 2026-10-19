#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace SimuladorModel {
	public ref class Laberinto
	{
	private:
		int filas;
		int columnas;
		int tamanoCelda;
		array<int, 2>^ mapa;

	public:
		Laberinto(int filas, int columnas, int tamanoCelda) {
			this->filas = filas;
			this->columnas = columnas;
			this->tamanoCelda = tamanoCelda;
			this->mapa = gcnew array<int, 2>(filas, columnas);
			InicializarMapaParametrico();
		}

		property int Filas { int get() { return filas; } };
		property int Columnas { int get() { return columnas; } };
		property int TamanoCelda { int get() { return tamanoCelda; } };

		void InicializarMapaParametrico() {
			for (int i = 0; i < this->filas; i++) {
				for (int j = 0; j < this->columnas; j++) {
					if (i == 0 || i == this->filas - 1 || j == 0 || j == columnas - 1) {
						this->mapa[i, j] = 1;
					}
					else if (i % 2 == 0 && j % 3 == 0) {
						this->mapa[i, j] = 1;
					}
					else {
						this->mapa[i, j] = 0;
					}
				}
			}

		}

		bool EsPasoValido(int fila, int columna) {
			if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
				return false;
			}
			return mapa[fila, columna] == 0;
		};

		void Dibujar(Graphics^ g) {
			for (int i = 0; i < this->filas; i++) {
				for (int j = 0; j < this->columnas; j++) {
					int x = j * tamanoCelda;
					int y = i * tamanoCelda;
					if (mapa[i, j] == 1) {
						SolidBrush^ brochaPared = gcnew SolidBrush(Color::FromArgb(45, 52, 64));
						g->FillRectangle(brochaPared, x, y, tamanoCelda, tamanoCelda);
						g->DrawRectangle(gcnew Pen(Color::FromArgb(30, 36, 46), 1), x, y, tamanoCelda, tamanoCelda);
					}
					else {
						SolidBrush^ brochaPiso = gcnew SolidBrush(Color::FromArgb(240, 243, 246));
						g->FillRectangle(brochaPiso, x, y, tamanoCelda, tamanoCelda);
						g->DrawRectangle(gcnew Pen(Color::FromArgb(215, 220, 226), 1), x, y, tamanoCelda, tamanoCelda);
					}

				}
			}

		};
	};
}