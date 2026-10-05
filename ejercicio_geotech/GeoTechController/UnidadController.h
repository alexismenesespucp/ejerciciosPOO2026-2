#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace GeoTechController {
	public ref class UnidadController
	{
	private:
		static List<UnidadInspeccion^>^ unidades;
	public:
		static UnidadController() {
			unidades = UnidadPersistence::CargarDesdeCSV();
		}
		static void RegistrarUnidad(UnidadInspeccion^ unidad);
		static List<UnidadInspeccion^>^ ObtenerUnidades();
		static UnidadInspeccion^ ObtenerUnidadMayorAutonomia();
	};
}