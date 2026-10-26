#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace GeoTechController {
	public ref class EstacionController
	{
	private: 
		static List<EstacionEnlace^>^ estaciones;
	public:
		static EstacionController() {
			estaciones = EstacionPersistence::CargarEstaciones();
		}
		static void RegistrarEstacion(int num, String^ ubicacion, int capacidad);
		static void ConectarUnidadAEstacion(int numEstacion);
		static List<EstacionEnlace^>^ ObtenerEstaciones();

	};
}