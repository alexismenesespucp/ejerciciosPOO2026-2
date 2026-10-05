#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace GeoTechController {
	public ref class UnidadController
	{
	private:
		List<UnidadInspeccion^>^ unidades;
	public:
		UnidadController() {
			this->unidades = UnidadPersistence::CargarDesdeCSV();
		}
		void RegistrarUnidad(UnidadInspeccion^ unidad);
		List<UnidadInspeccion^>^ ObtenerUnidades();
		UnidadInspeccion^ ObtenerUnidadMayorAutonomoia(int id);
	};
}