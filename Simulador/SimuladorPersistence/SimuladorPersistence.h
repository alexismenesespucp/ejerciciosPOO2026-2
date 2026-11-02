#pragma once

using namespace System;
using namespace SimuladorModel;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;
namespace SimuladorPersistence {
	public ref class Database abstract sealed
	{
	private:
		static String^ RUTA_CONFIGURACION_DB = "configuracion_db.txt";
		static SqlConnection^ obtenerConexion();
	public:
		static int GuardarMapaEnBD(Laberinto^ laberinto);
		static Dictionary<int, Laberinto^>^ CargarDatosDB();
		// TODO: Add your methods for this class here.
	};
}
