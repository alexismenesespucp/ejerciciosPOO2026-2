#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

namespace GeoTechPersistance {
	public ref class EstacionPersistence abstract sealed
	{
	private:
		static String^ RUTA_TXT = "estaciones_enlace.txt";
	public:
		static void GuardarEstaciones(List<EstacionEnlace^>^ estaciones);
		static List<EstacionEnlace^>^ CargarEstaciones();
	};

}