#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace UnidadRoboticaModel;

namespace UnidadRoboticaPersistence {
	public ref class Database abstract sealed
	{
	private:
		static String^ RUTA_CONFIGURACION_DB = "configuracion_db.txt";
		static SqlConnection^ obtenerConexion();
	public:
		static void inicializar();
		static int crear_inspeccion(InspeccionCabecera^ inspeccion);
		static int crear_inspeccion_detail(InspeccionDetail^ detalle);
		// TODO: Add your methods for this class here.
	};
}
