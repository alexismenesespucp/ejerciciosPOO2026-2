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
			Console::WriteLine("Cargando estaciones y unidades desde la base de datos y CSV...");
			unidades = UnidadPersistence::CargarEstacionesDesdeBD();
			Console::WriteLine("Las unidades son: {0}", unidades->Count);
			//unidades = UnidadPersistence::CargarDesdeCSV();
		}
		static void RegistrarUnidad(UnidadInspeccion^ unidad);
		static void ModificarUnidad(UnidadInspeccion^ unidad);
		static void EliminarUnidad(int idUnidad);
		static List<UnidadInspeccion^>^ ObtenerUnidades();
		static UnidadInspeccion^ ObtenerUnidadMayorAutonomia();
	};
}