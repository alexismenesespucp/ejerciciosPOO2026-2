#include "pch.h"
#include "EstacionController.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace GeoTechController {
	void EstacionController::RegistrarEstacion(int num, String^ ubicacion, int capacidad) {
		if (capacidad <= 0) {
			throw gcnew ArgumentException("La capacidad debe ser mayor a cero.");
		}

		if (String::IsNullOrWhiteSpace(ubicacion)) {
			throw gcnew ArgumentException("La ubicación no puede estar vacía.");
		}

		if (capacidad < 1 || capacidad > 6) {
			throw gcnew ArgumentException("La capacidad debe estar entre 1 y 6.");
		}

		for each (EstacionEnlace ^ estacion in this->estaciones) {
			if (estacion->NumeroEstacion == num) {
				throw gcnew ArgumentException("Ya existe una estación con el mismo número.");
			}
		}
		EstacionEnlace^ nuevaEstacion = gcnew EstacionEnlace(num, ubicacion, capacidad);
		this->estaciones->Add(nuevaEstacion);
		EstacionPersistence::GuardarEstaciones(this->estaciones);
	}
	void EstacionController::ConectarUnidadAEstacion(int numEstacion) {
		for each (EstacionEnlace ^ estacion in this->estaciones) {
			if (estacion->NumeroEstacion == numEstacion) {
				if (!estacion->TieneEspacioDisponible()) {
					throw gcnew InvalidOperationException("La estación no tiene espacio disponible para conectar más unidades.");
				}
				estacion->UnidadesConectadas++;
				EstacionPersistence::GuardarEstaciones(this->estaciones);
				return;
			}
		}
		throw gcnew ArgumentException("No se encontró una estación con el número proporcionado.");
	}
	List<EstacionEnlace^>^ EstacionController::ObtenerEstaciones() {
		return this->estaciones;
	}
}