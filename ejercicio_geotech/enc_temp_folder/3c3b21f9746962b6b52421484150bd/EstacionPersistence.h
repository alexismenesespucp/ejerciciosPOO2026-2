#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;
using namespace System::Data::SqlClient;

namespace GeoTechPersistance {
	public ref class EstacionPersistence abstract sealed
	{
	private:
		static String^ RUTA_TXT = "estaciones_enlace.txt";
		static String^ RUTA_CONFIGURACION_DB = "configuracion_db.txt"; 
		static SqlConnection^ obtenerConexion();
	public:
		static void GuardarEstacionesEnBD(List<EstacionEnlace^>^ estaciones);
		static List<EstacionEnlace^>^ CargarEstacionesDesdeBD();
		static void GuardarEstaciones(List<EstacionEnlace^>^ estaciones);
		static List<EstacionEnlace^>^ CargarEstaciones();
	};

}