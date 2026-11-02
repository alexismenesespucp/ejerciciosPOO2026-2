#include "pch.h"

#include "SimuladorPersistence.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace SimuladorModel;

namespace SimuladorPersistence {
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
	int Database::GuardarMapaEnBD(Laberinto^ laberinto) {
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			SqlTransaction^ transaccion = conexion->BeginTransaction();
			SqlCommand^ cmdInsertMapa = gcnew SqlCommand("usp_InsertarMapa", conexion, transaccion);
			cmdInsertMapa->CommandType = CommandType::StoredProcedure;

			cmdInsertMapa->Parameters->AddWithValue("@TotalFilas", laberinto->Filas);
			cmdInsertMapa->Parameters->AddWithValue("@TotalColumnas", laberinto->Columnas);
			cmdInsertMapa->Parameters->AddWithValue("@TipoDistancia", laberinto->Heuristica);
			cmdInsertMapa->Parameters->AddWithValue("@InicioFila", laberinto->PuntoInicio.X);
			cmdInsertMapa->Parameters->AddWithValue("@InicioColumna", laberinto->PuntoInicio.Y);
			cmdInsertMapa->Parameters->AddWithValue("@FinFila", laberinto->PuntoLlegada.X);
			cmdInsertMapa->Parameters->AddWithValue("@FinColumna", laberinto->PuntoLlegada.Y);
			cmdInsertMapa->Parameters->AddWithValue("@MovimientoCeldaHorizontal", laberinto->PesoH);
			cmdInsertMapa->Parameters->AddWithValue("@MovimientoCeldaVertical", laberinto->PesoV);
			cmdInsertMapa->Parameters->AddWithValue("@MovimientoCeldaDiagonal", laberinto->PesoD);

			SqlParameter^ outputId = gcnew SqlParameter("@IdMapaGenerado", SqlDbType::Int);
			outputId->Direction = ParameterDirection::Output;
			cmdInsertMapa->Parameters->Add(outputId);

			cmdInsertMapa->ExecuteNonQuery();
			
			int idMapaGenerado = Convert::ToInt32(outputId->Value);
			Console::WriteLine("Mapagenerado {0}", idMapaGenerado);
			SqlCommand^ cmdInsertCelda = gcnew SqlCommand("usp_InsertarCeldaMapa", conexion, transaccion);
			cmdInsertCelda->CommandType = CommandType::StoredProcedure;

			cmdInsertCelda->Parameters->AddWithValue("@IdMapa", idMapaGenerado);
			SqlParameter^ paramFila = cmdInsertCelda->Parameters->Add("@Fila", SqlDbType::Int);
			SqlParameter^ paramColumna = cmdInsertCelda->Parameters->Add("@Columna", SqlDbType::Int);
			SqlParameter^ paramEsMuro = cmdInsertCelda->Parameters->Add("@EsMuro", SqlDbType::Bit);

			for (int i = 0; i < laberinto->Filas; i++) {
				for (int j = 0; j < laberinto->Columnas; j++) {
					bool EsMuro = !laberinto->EsCeldaLibre(Point(i, j));
					paramFila->Value = i;
					paramColumna->Value = j;
					paramEsMuro->Value = EsMuro;
					cmdInsertCelda->ExecuteNonQuery();
				}
			}
			transaccion->Commit();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al guardar el mapa en la base de datos: {0}", ex->Message);
		}
		finally {
			if (conexion->State == ConnectionState::Open) {
				conexion->Close();
			}
		}
		return 0;
	}
}
