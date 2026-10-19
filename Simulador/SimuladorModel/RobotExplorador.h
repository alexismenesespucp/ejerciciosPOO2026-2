#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace SimuladorModel {
	public ref class RobotExplorador {
	public:
		property Point posicion;
		property String^ Alias;
		RobotExplorador(Point posicionInicial, String^ alias) {
			this->posicion = posicionInicial;
			this->Alias = alias;
		}

		void mover(Point nuevaPosicion) {
			this->posicion = nuevaPosicion;
		}

		void Dibujar(Graphics^ g, int tamanoCelda) {
			int px = this->posicion.Y * tamanoCelda;
			int py = this->posicion.X * tamanoCelda;
			int margen = 6;
			int diametro = tamanoCelda - (margen * 2);

			SolidBrush^ brochaCuerpo = gcnew SolidBrush(Color::DodgerBlue);
			g->FillEllipse(brochaCuerpo, px + margen, py + margen, diametro, diametro);
			g->DrawEllipse(gcnew Pen(Color::Navy, 2), px + margen, py + margen, diametro, diametro);

			// Núcleo central
			SolidBrush^ brochaCentro = gcnew SolidBrush(Color::Yellow);
			g->FillEllipse(brochaCentro, px + (tamanoCelda / 2) - 4, py + (tamanoCelda / 2) - 4, 8, 8);
		}
	};
}