#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace GeoTechModel;
using namespace GeoTechPersistance;

namespace GeoTechController {
	public ref class EstacionController
	{
	private: 
		List<EstacionEnlace^>^ estaciones;
	public:
		EstacionController() {
			this->estaciones = EstacionPersistence::CargarEstaciones();
		}
		void RegistrarEstacion(int num, String^ ubicacion, int capacidad);
		void ConectarUnidadAEstacion(int numEstacion);
		List<EstacionEnlace^>^ ObtenerEstaciones();

	};
}