#pragma once

using namespace System;
using namespace System::Drawing;
using namespace SimuladorModel;
using namespace SimuladorPersistence;

namespace SimuladorController {
	public ref class SimuladorLaberintoController abstract sealed
	{
	private:
		static Laberinto^ laberinto;
		static bool isLaberintoInialized = false;
		static RobotExplorador^ robot;
		static Random^ rDirection;
	public:
		static SimuladorLaberintoController() {
			rDirection = gcnew Random();
		}

		static void GenerarNuevoMapa(int filas, int columnas, String^ heuristica, int pesoH, int pesoV, int pesoD, int canvasWidth, int canvasHeight) {
			laberinto = gcnew Laberinto(filas, columnas, canvasWidth, canvasHeight, heuristica, pesoH, pesoV, pesoD);
			robot = gcnew RobotExplorador(laberinto->PuntoInicio, "RoboExplorador");
			isLaberintoInialized = true;
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

		static int GuardarMapaActualEnDB() {

			return Database::GuardarMapaEnBD(laberinto);
		}

		static void Renderizar(Graphics^ g) {
			if(isLaberintoInialized) laberinto->Dibujar(g);
			robot->Dibujar(g, 30);
		}
	};
}
