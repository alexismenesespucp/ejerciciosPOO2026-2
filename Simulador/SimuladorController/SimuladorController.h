#pragma once

using namespace System;
using namespace System::Drawing;
using namespace SimuladorModel;

namespace SimuladorController {
	public ref class SimuladorLaberintoController abstract sealed
	{
	private:
		static Laberinto^ laberinto;
		static RobotExplorador^ robot;
		static Random^ rDirection;
	public:
		static SimuladorLaberintoController() {
			laberinto = gcnew Laberinto(11, 11, 30);
			robot = gcnew RobotExplorador(laberinto->PuntoInicio, "RoboExplorador");
			rDirection = gcnew Random();
		}

		static Laberinto^ ObetenerLaberinto() { return laberinto; };
		static void actualizarRobot() {
			Point posicionActual = robot->posicion;

			array<int>^ df = { -1,1,0,0 };
			array<int>^ dc = { 0,0,-1,1 };
			Point nuevaPosicion;
			do{
				int dir = rDirection->Next(4);
				nuevaPosicion.X = posicionActual.X + dc[dir];
				nuevaPosicion.Y = posicionActual.Y + df[dir];
				Console::WriteLine("Posicion actual {0} {1}", nuevaPosicion.X, nuevaPosicion.Y);
			} while (!laberinto->EsCeldaLibre(nuevaPosicion));
			robot->mover(nuevaPosicion);
		}
		static void Renderizar(Graphics^ g) {
			laberinto->Dibujar(g);
			robot->Dibujar(g, 30);
		}
	};
}
