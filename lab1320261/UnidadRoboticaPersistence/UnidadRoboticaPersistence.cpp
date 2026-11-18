#include "pch.h"

#include "UnidadRoboticaPersistence.h"
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::IO;

namespace UnidadRoboticaPersistence {
	SqlConnection^ Database::obtenerConexion() {
		if (!File::Exists(RUTA_CONFIGURACION_DB)) {
			Console::WriteLine("Archivo de configuración de base de datos no encontrado. Creando uno con valores predeterminados.");
			StreamWriter^ writer = gcnew StreamWriter(RUTA_CONFIGURACION_DB, false);
			writer->WriteLine("Server=localhost;Database=default;User ID=True;Password=password;");
			writer->Close();
		}
		StreamReader^ reader = gcnew StreamReader(RUTA_CONFIGURACION_DB);
		String^ connectionString = reader->ReadLine();

		reader->Close();
		return gcnew SqlConnection(connectionString);
	}

	void Database::inicializar() {
		SqlConnection^ connection = obtenerConexion();
		try {
			connection->Open();
			Console::WriteLine("Conexión a la base de datos establecida correctamente.");
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al conectar a la base de datos: " + ex->Message);
		}
		finally {
			connection->Close();
		}
	}

	int Database::crear_inspeccion(InspeccionCabecera^ inspeccion) {
		SqlConnection^ connection = obtenerConexion();
		connection->Open();
		SqlTransaction^ transaccion = connection->BeginTransaction();
		try {
			
			SqlCommand^ cmdInsertMapa = gcnew SqlCommand("usp_CreateInspeccion", connection, transaccion);
			cmdInsertMapa->CommandType = CommandType::StoredProcedure;

			cmdInsertMapa->Parameters->AddWithValue("@CodigoLote", inspeccion->codigoLote);
			cmdInsertMapa->Parameters->AddWithValue("@RobotId", inspeccion->robotId);
			cmdInsertMapa->Parameters->AddWithValue("@Inspector", inspeccion->inspector);
			cmdInsertMapa->Parameters->AddWithValue("@ResultadoGeneral", inspeccion->resultadoGeneral);

			//int insertedId = (int)cmdInsertMapa->ExecuteScalar();
			SqlParameter^ insertedIdParam = gcnew SqlParameter("@InsertedId", SqlDbType::Int);
			insertedIdParam->Direction = ParameterDirection::Output;
			cmdInsertMapa->Parameters->Add(insertedIdParam);

			cmdInsertMapa->ExecuteNonQuery();

			transaccion->Commit();

			return (int)insertedIdParam->Value;
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al crear la inspección: " + ex->Message);
			transaccion->Rollback();
			return -1; // Indicar error
		}
		finally {
			connection->Close();
		}
	}

	int Database::crear_inspeccion_detail(InspeccionDetail^ detalle) {
		SqlConnection^ connection = obtenerConexion();
		try {
			connection->Open();
			SqlTransaction^ transaccion = connection->BeginTransaction();
			SqlCommand^ cmdInsertMapa = gcnew SqlCommand("usp_CreateInspeccionDetail", connection, transaccion);
			cmdInsertMapa->CommandType = CommandType::StoredProcedure;
			cmdInsertMapa->Parameters->AddWithValue("@Parametro", detalle->parametro);
			cmdInsertMapa->Parameters->AddWithValue("@ResultadoParametro", detalle->resultadoParametro);
			cmdInsertMapa->Parameters->AddWithValue("@Notas", detalle->notas);
			int insertedId = (int)cmdInsertMapa->ExecuteScalar();
			return insertedId;
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al crear el detalle de inspección: " + ex->Message);
			return -1; // Indicar error
		}
		finally {
			connection->Close();
		}
	}

}