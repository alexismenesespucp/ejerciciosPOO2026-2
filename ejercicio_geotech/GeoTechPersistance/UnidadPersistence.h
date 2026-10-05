#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

namespace GeoTechPersistance {
	public ref class UnidadPersistence abstract sealed
	{
	private:
		static String^ RUTA_CSV = "flota_inspeccion.csv";

	public:

		static void GuardarEnCSV(List<UnidadInspeccion^>^ unidades);
		static List<UnidadInspeccion^>^ CargarDesdeCSV();
	};

}