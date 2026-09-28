#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace agvModel;
using namespace agvPersistance;

namespace agvController {
	public ref class manager
	{
	public:
		static List<vehiculoAgv^>^ flota;
		static void agregarVehiculo(vehiculoAgv^ vehiculo);
		static void listarVehiculo();
		static void eliminarVehiculo(int id);
		static void leerVehiculos();
		static void guardarVehiculos();
		static void mostrarGuardados();

	};
}
