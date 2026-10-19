#pragma once

using namespace System;
using namespace System::Drawing;
using namespace SimuladorModel;

namespace SimuladorController {
	public ref class SimuladorLaberintoController abstract sealed
	{
	private:
		static Laberinto^ laberinto;
	public:
		static SimuladorLaberintoController() {
			laberinto = gcnew Laberinto(11, 11, 30);
		}

		static Laberinto^ ObetenerLaberinto() { return laberinto; };
		static void Renderizar(Graphics^ g) {
			laberinto->Dibujar(g);
		}
	};
}
