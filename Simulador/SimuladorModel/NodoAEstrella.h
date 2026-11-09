#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace SimuladorModel {
	public ref class NodoAEstrella {
	public:
		Point punto;
		double g;
		double h;
		double f;
		NodoAEstrella^ padre;
		bool cerrado;
		NodoAEstrella(Point p, double g, double h, double f, NodoAEstrella^ padre) {
			this->punto = p;
			this->g = g;
			this->h = h;
			this->f = f;
			this->padre = padre;
			this->cerrado = false;

		}
	};

}