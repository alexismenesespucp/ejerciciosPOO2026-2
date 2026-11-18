#pragma once

using namespace System;
using namespace UnidadRoboticaPersistence;

namespace UnidadRoboticaController {
	public ref class controller abstract sealed
	{
	public:
		static void inicializar() {
			UnidadRoboticaPersistence::Database::inicializar();
		}
		// TODO: Add your methods for this class here.
	};
}
