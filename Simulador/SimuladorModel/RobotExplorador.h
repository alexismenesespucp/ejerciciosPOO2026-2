#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace SimuladorModel {
	public ref class RobotExplorador {
	public:
		property Point posicion;
		property String^ Alias;
		property int tamanoCeldaWidth;
		property int tamanoCeldaHeight;
		RobotExplorador(Point posicionInicial, String^ alias, int tamanoCeldaWidth, int tamanoCeldaHeight) {
			this->posicion = posicionInicial;
			this->Alias = alias;
			this->tamanoCeldaWidth = tamanoCeldaWidth;
			this->tamanoCeldaHeight = tamanoCeldaHeight;
		}

		void mover(Point nuevaPosicion) {
			this->posicion = nuevaPosicion;
		}

		void Dibujar(Graphics^ g) {
			int px = this->posicion.Y * this->tamanoCeldaWidth;
			int py = this->posicion.X * this->tamanoCeldaHeight;
			int margen = 6;
			int diametro = this->tamanoCeldaHeight - (margen * 2);
			SolidBrush^ brochaCuerpo = gcnew SolidBrush(Color::DodgerBlue);
			g->FillEllipse(brochaCuerpo, px + margen, py + margen, diametro, diametro);
			g->DrawEllipse(gcnew Pen(Color::Navy, 2), px + margen, py + margen, diametro, diametro);

			// Núcleo central
			SolidBrush^ brochaCentro = gcnew SolidBrush(Color::Yellow);
			g->FillEllipse(brochaCentro, px + (this->tamanoCeldaWidth / 2) - 4, py + (this->tamanoCeldaHeight / 2) - 4, 8, 8);
		}
	};
}