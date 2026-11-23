#pragma once

using namespace System;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace JuegoPersistence {
	public ref class Database
	{
	private:
		static String^ RUTA_CONFIGURACION_DB = "configuracion_db.txt";
		static SqlConnection^ obtenerConexion();
	public:
		static void GuardarConexion(String^ IP);
		static void UpdateConexion(String^ IP);
		static List<String^>^ ObtenerConexionActivas();
		// TODO: Add your methods for this class here.
	};
}
