#include "pch.h"

#include "JuegoController.h"

namespace  JuegoController {
	void Controller::DibujarTablero(Graphics^ g)
	{
		if (tableroActual == nullptr) {
			tableroActual = gcnew tablero();
		}
		tableroActual->DibujarTablero(g);

	}
	void Controller::PintarCelda(int x, int y)
	{
		if (tableroActual == nullptr) {
			tableroActual = gcnew tablero();
		}
		tableroActual->PintarCelda(x, y);
	}
}
