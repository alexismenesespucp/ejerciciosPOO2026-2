#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

using namespace SimuladorModel;
using namespace SimuladorPersistence;

namespace SimuladorController {
	public ref class SimuladorLaberintoController abstract sealed
	{
	private:
		static Laberinto^ laberinto;
		static String^ tipoDistancia;
		static double valorHorizontal;
		static double valorVertical;
		static double valorDiagonal;

		static int width = 800;
		static int height = 600;
		static Dictionary<int, Laberinto^>^ laberintos;
		static bool isLaberintoInialized = false;
		static RobotExplorador^ robot;
		static Random^ rDirection;

		static Dictionary<Point, NodoAEstrella^>^ mapaNodos;
		static NodoAEstrella^ nodoActual;
		static List<NodoAEstrella^>^ openSet;

	public:
		static SimuladorLaberintoController() {
			rDirection = gcnew Random();
		}

		static void SetWidthHeight(int w, int h) {
			width = w;
			height = h;
			Database::setWidthHeight(w, h);
		}

		static void setTipoDistancia(String^ tipo) {
			tipoDistancia = tipo;
		}

		static void setValoresMovimiento(double horizontal, double vertical, double diagonal) {
			valorHorizontal = horizontal;
			valorVertical = vertical;
			valorDiagonal = diagonal;
		}

		static void IniciarBusqueda() {
			if (!isLaberintoInialized) return;
			openSet = gcnew List<NodoAEstrella^>();
			mapaNodos = gcnew Dictionary<Point, NodoAEstrella^>();

			Point posicionActual = robot->posicion;
			double hInicio = CalcularHeuristica(posicionActual, laberinto->PuntoLlegada);

			NodoAEstrella^ nodoRaiz = gcnew NodoAEstrella(posicionActual, 0, hInicio, hInicio, nullptr);

			openSet->Add(nodoRaiz);
			mapaNodos[posicionActual] = nodoRaiz;
		}

		static void ActualizarBusqueda() {
			if (openSet->Count == 0) return;

			int mejorIdx = 0;
			for (int i = 0; i < openSet->Count; i++) {
				NodoAEstrella^ nodo = openSet[i];
				
				if(nodo->f < openSet[mejorIdx]->f || nodo->f == openSet[mejorIdx]->f && nodo->h < openSet[mejorIdx]->h)
					mejorIdx = i;
			}
			NodoAEstrella^ seleccionado = openSet[mejorIdx];
			openSet->RemoveAt(mejorIdx);

			seleccionado->cerrado = true;

			if (seleccionado->punto == laberinto->PuntoLlegada) {
				NodoAEstrella^ p = seleccionado;
				while (p != nullptr) {
					Console::WriteLine("Camino: [{0}, {1}]", p->punto.X, p->punto.Y);
					p = p->padre;
				}

				return;
			}

			for(int dx = -1; dx <= 1; dx++) {
				for(int dy = -1; dy <= 1; dy++) {
					if(dx == 0 && dy == 0) continue;

					Point vecino = Point(seleccionado->punto.X + dx, seleccionado->punto.Y + dy);
					if(!laberinto->EsCeldaLibre(vecino)) continue;

					double g = seleccionado->g + CalcularCosto(seleccionado->punto, vecino);
					double h = CalcularHeuristica(vecino, laberinto->PuntoLlegada);
					double f = g + h;

					if(mapaNodos->ContainsKey(vecino)) {
						NodoAEstrella^ nodoExistente = mapaNodos[vecino];
						if(f < nodoExistente->f) {
							nodoExistente->g = g;
							nodoExistente->f = f;
							nodoExistente->padre = seleccionado;
						}
					} else {
						NodoAEstrella^ nuevoNodo = gcnew NodoAEstrella(vecino, g, h, f, seleccionado);
						mapaNodos[vecino] = nuevoNodo;
						openSet->Add(nuevoNodo);
					}
				}
			}
		}

		static double CalcularHeuristica(Point puntoA, Point puntoB) {
			if (tipoDistancia == "manhattan") {
				return Math::Abs(puntoA.X - puntoB.X) + Math::Abs(puntoA.Y - puntoB.Y);
			}
			else if (tipoDistancia == "euclidiana") {
				return Math::Sqrt(Math::Pow(puntoA.X - puntoB.X, 2) + Math::Pow(puntoA.Y - puntoB.Y, 2));
			}
			else if (tipoDistancia == "chebyshev") {
				return Math::Max(Math::Abs(puntoA.X - puntoB.X), Math::Abs(puntoA.Y - puntoB.Y));
			}
			return 0;
		}

		static double CalcularCosto(Point puntoA, Point puntoB) {
			if (tipoDistancia == "manhattan") {
				return Math::Abs(puntoA.X - puntoB.X) * valorHorizontal + Math::Abs(puntoA.Y - puntoB.Y) * valorVertical;
			}
			else if (tipoDistancia == "euclidiana") {
				if (puntoA.X - puntoB.X == 0 || puntoA.Y - puntoB.Y == 0)
					return Math::Abs(puntoA.X - puntoB.X) * valorHorizontal + Math::Abs(puntoA.Y - puntoB.Y) * valorVertical;
				else
					return valorDiagonal;
			}
			else if (tipoDistancia == "chebyshev") {
				return Math::Abs(puntoA.X - puntoB.X) * valorHorizontal + Math::Abs(puntoA.Y - puntoB.Y) * valorVertical;
			}
			return 0;
		}

		static void calcular_caminos() {
			Point posicionActual = robot->posicion;
			for (int movimiento_x = -1; movimiento_x < 2; movimiento_x++)
			{
				for (int movimiento_y = -1; movimiento_y < 2; movimiento_y++) {
					if (movimiento_x == 0 && movimiento_y == 0) continue;
					if (movimiento_x + posicionActual.X < 0) continue;
					if (movimiento_y + posicionActual.Y < 0) continue;

					Point posible_camino = Point(movimiento_x + posicionActual.X, movimiento_y + posicionActual.Y);

					bool esCeldaLibre = laberinto->EsCeldaLibre(posible_camino);

					if (!esCeldaLibre) continue;
					double heuristica = 0;
					double costo = 0;


					heuristica = CalcularHeuristica(posible_camino, laberinto->PuntoLlegada);
					costo = CalcularCosto(posicionActual, posible_camino);

					double valor = heuristica + costo;

					openSet->Add(gcnew NodoAEstrella(posible_camino, costo, heuristica, valor, nullptr));
					
					Console::WriteLine("Es celda libre x({0}) y({1})= {2}", posible_camino.X, posible_camino.Y, valor);


				}

			}
		}

		static void SeleccionarLaberinto(int seleccion) {
			laberinto = laberintos[seleccion];
			robot = gcnew RobotExplorador(laberinto->PuntoInicio, "RoboExplorador", laberinto->TamanoCeldaHorizontal, laberinto->TamanoCeldaVertical);
			isLaberintoInialized = true;
		}


		static void GenerarNuevoMapa(int filas, int columnas, String^ heuristica, int pesoH, int pesoV, int pesoD, int canvasWidth, int canvasHeight) {
			laberinto = gcnew Laberinto(filas, columnas, canvasWidth, canvasHeight, heuristica, pesoH, pesoV, pesoD);
			robot = gcnew RobotExplorador(laberinto->PuntoInicio, "RoboExplorador", laberinto->TamanoCeldaHorizontal, laberinto->TamanoCeldaVertical);
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

		static void CargarDatosDB() {
			laberintos =  Database::CargarDatosDB();
		}

		static Dictionary<int, Laberinto^>^ ObtenerMapasDB() {
			return laberintos;
		}

		static List<int>^ idsMapas() {
			List<int>^ ids = gcnew List<int>();
			for each (int id in laberintos->Keys) {
				ids->Add(id);
			}
			return ids;
		}



		static void Renderizar(Graphics^ g) {
			if(isLaberintoInialized) laberinto->Dibujar(g);
			robot->Dibujar(g);
		}
	};
}
