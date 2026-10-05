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
		for each (UnidadInspeccion ^ u in UnidadController::unidades) {
			if (u->Id == unidad->Id) {
				throw gcnew ArgumentException("Ya existe una unidad con el mismo ID.");
			}
		}
		UnidadController::unidades->Add(unidad);
		UnidadPersistence::GuardarEnCSV(UnidadController::unidades);
	}

	List<UnidadInspeccion^>^ UnidadController::ObtenerUnidades() {
		return UnidadController::unidades;
	}
	UnidadInspeccion^ UnidadController::ObtenerUnidadMayorAutonomia() {
		if (UnidadController::unidades->Count == 0) return nullptr;
		
		UnidadInspeccion^ unidadMayorAutonomia = UnidadController::unidades[0];
		for each (UnidadInspeccion ^ unidad in UnidadController::unidades) {
			if (unidadMayorAutonomia->CalcularAutonomiaHoras() < unidad->CalcularAutonomiaHoras()) {
				unidadMayorAutonomia = unidad;
			}
		}
		return unidadMayorAutonomia;
	}
}