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
		
		Point puntoInicio;
		Point puntoLlegada;

		Random^ rng;

	public:
		Laberinto(int filas, int columnas, int tamanoCelda) {
			this->filas = filas;
			this->columnas = columnas;
			this->tamanoCelda = tamanoCelda;
			this->rng = gcnew Random();
			this->mapa = gcnew array<int, 2>(filas, columnas);
			//InicializarMapaParametrico();
			GenerarLaberintoAleatorio();
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

		void GenerarLaberintoAleatorio() {
			for (int i = 0; i < this->filas; i++) {
				for (int j = 0; j < this->columnas; j++) {
					if (i == 0 || i == this->filas - 1 || j == 0 || j == columnas - 1) {
						this->mapa[i, j] = 1;
					}
					else {
						if (rng->Next(100) < 28) {
							this->mapa[i, j] = 1;
						}
						else {
							this->mapa[i, j] = 0;
						}
					}
				}
			}

			int fIni = rng->Next(1, this->filas - 1);
			int cIni = rng->Next(1, this->columnas - 1);
			this->mapa[fIni, cIni] = 0;

			this->puntoInicio = Point(fIni, cIni);

			int fFin, cFin;

			do {
				fFin = rng->Next(1, this->filas - 1);
				cFin = rng->Next(1, this->columnas - 1);
			} while (fFin == fIni && cFin == cIni);
			this->mapa[fFin, cFin] = 0;
			this->puntoLlegada = Point(fFin, cFin);


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

			int xIni = puntoInicio.Y * tamanoCelda;
			int yIni = puntoInicio.X * tamanoCelda;
			SolidBrush^ brochaIni = gcnew SolidBrush(Color::LimeGreen);
			g->FillRectangle(brochaIni, xIni+3, yIni+3, tamanoCelda-6, tamanoCelda-6);
			g->DrawString("A", gcnew Font("Arial", 8, FontStyle::Bold), Brushes::White, (float)(xIni + 5), (float)(yIni + 4));
				
			int xFin = puntoLlegada.Y * tamanoCelda;
			int yFin = puntoLlegada.X * tamanoCelda;
			SolidBrush^ brochaFin = gcnew SolidBrush(Color::Crimson);
			g->FillRectangle(brochaFin, xFin + 3, yFin + 3, tamanoCelda - 6, tamanoCelda - 6);
			g->DrawString("B", gcnew Font("Arial", 8, FontStyle::Bold), Brushes::White, (float)(xFin + 5), (float)(yFin + 4));

		};
	};
}