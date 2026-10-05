#include "pch.h"
#include "UnidadController.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace  GeoTechController {
	void UnidadController::RegistrarUnidad(UnidadInspeccion^ unidad) {
		if (unidad == nullptr) {
			throw gcnew ArgumentNullException("unidad","La unidad no puede ser nula.");
		}
		if (unidad->BateriaRestante < 0.0 || unidad->BateriaRestante > 100.0) {
			throw gcnew ArgumentOutOfRangeException("unidad", "La batería restante debe estar entre 0 y 100.");
		}
		for each (UnidadInspeccion ^ u in this->unidades) {
			if (u->Id == unidad->Id) {
				throw gcnew ArgumentException("Ya existe una unidad con el mismo ID.");
			}
		}
		this->unidades->Add(unidad);
		UnidadPersistence::GuardarEnCSV(this->unidades);
	}

	List<UnidadInspeccion^>^ UnidadController::ObtenerUnidades() {
		return this->unidades;
	}
	UnidadInspeccion^ UnidadController::ObtenerUnidadMayorAutonomoia(int id) {
		if (this->unidades->Count == 0) return nullptr;
		
		UnidadInspeccion^ unidadMayorAutonomia = this->unidades[0];
		for each (UnidadInspeccion ^ unidad in this->unidades) {
			if (unidadMayorAutonomia->CalcularAutonomiaHoras() < unidad->CalcularAutonomiaHoras()) {
				unidadMayorAutonomia = unidad;
			}
		}
		return unidadMayorAutonomia;
	}
}