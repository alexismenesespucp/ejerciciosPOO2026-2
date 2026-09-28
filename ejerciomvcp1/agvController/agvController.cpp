#include "pch.h"

#include "agvController.h"
using namespace agvController;
using namespace agvModel;
using namespace agvPersistance;

void manager::agregarVehiculo(vehiculoAgv^ vehiculo) {
	if (flota == nullptr) {
		flota = gcnew List<vehiculoAgv^>();
	}
	flota->Add(vehiculo);
}

void manager::listarVehiculo() {
	if (flota == nullptr || flota->Count == 0) {
		Console::WriteLine("No hay vehículos en la flota.");
		return;
	}
	for each (vehiculoAgv ^ vehiculo in flota) {
		Console::WriteLine("Tipo: {0}", vehiculo->GetType()->Name);
		Console::WriteLine("ID: {0}, Código: {1}, Batería: {2}%", vehiculo->id, vehiculo->Codigo, vehiculo->Bateria);
	}
}

void manager::eliminarVehiculo(int id) {
	if (flota == nullptr || flota->Count == 0) {
		Console::WriteLine("No hay vehículos en la flota.");
		return;
	}
	for (int i = 0; i < flota->Count; i++) {
		if (flota[i]->id == id) {
			flota->RemoveAt(i);
			Console::WriteLine("Vehículo con ID {0} eliminado.", id);
			return;
		}
	}
	Console::WriteLine("No se encontró un vehículo con ID {0}.", id);
}

void manager::guardarVehiculos() {
	//persistance::guardarVehiculoTxt(flota);	
	//persistance::guardarVehiculoCsv(flota);
	//persistance::guardarVehiculoXml(flota);
	//persistance::guardarVehiculoJson(flota);
	persistance::guardarVehiculoBinario(flota);
}

void manager::leerVehiculos() {
	List<vehiculoAgv^>^ vehiculosLeidos = persistance::leerVehiculosJson();
	if (vehiculosLeidos == nullptr || vehiculosLeidos->Count == 0) {
		Console::WriteLine("No se encontraron vehículos guardados.");
		return;
	}

	flota = vehiculosLeidos;


	for each (vehiculoAgv ^ vehiculo in vehiculosLeidos) {
		Console::WriteLine("Tipo: {0}", vehiculo->GetType()->Name);
		Console::WriteLine("ID: {0}, Código: {1}, Batería: {2}%", vehiculo->id, vehiculo->Codigo, vehiculo->Bateria);
	}
}

void manager::mostrarGuardados() {
	for each(vehiculoAgv^ vehiculo in persistance::leerVehiculosTxt()){
		Console::WriteLine("Tipo: {0}", vehiculo->GetType()->Name);
		Console::WriteLine("ID: {0}, Código: {1}, Batería: {2}%", vehiculo->id, vehiculo->Codigo, vehiculo->Bateria);
	};
}