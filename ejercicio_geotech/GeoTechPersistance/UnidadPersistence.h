#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;
using namespace System::Data::SqlClient;

namespace GeoTechPersistance {
	public ref class UnidadPersistence abstract sealed
	{
	private:
		static String^ RUTA_CSV = "flota_inspeccion.csv";
		static String^ RUTA_CONFIGURACION_DB = "configuracion_db.txt";
		static SqlConnection^ obtenerConexion();
	public:
		static void GuardarEstacionEnBD(UnidadInspeccion^ unidad);
		static void ModificarEstacionEnBD(UnidadInspeccion^ unidad);
		static void EliminarEstacionEnBD(int idUnidad);
		static List<UnidadInspeccion^>^ CargarEstacionesDesdeBD();
		static void GuardarEnCSV(List<UnidadInspeccion^>^ unidades);
		static List<UnidadInspeccion^>^ CargarDesdeCSV();
	};

}