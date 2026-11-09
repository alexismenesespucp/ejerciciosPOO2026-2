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

	Dictionary<int, Laberinto^>^ Database::CargarDatosDB() {
		Dictionary<int, Laberinto^>^ mapas = gcnew Dictionary<int, Laberinto^>();
		Laberinto^ nuevoLaberinto;
		SqlConnection^ conexion = obtenerConexion();
		Point puntoInicio;
		Point puntoLlegada;
		try {
			conexion->Open();
			String^ query = "SELECT * FROM Mapa";
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			SqlDataReader^ reader = command->ExecuteReader();
			while (reader->Read()) {
				int idMapa = reader->GetInt32(reader->GetOrdinal("IdMapa"));
				String^ fechaCreacion = reader->GetDateTime(reader->GetOrdinal("FechaCreacion")).ToString("yyyy-MM-dd HH:mm");
				int filas = reader->GetInt32(reader->GetOrdinal("TotalFilas"));
				int columnas = reader->GetInt32(reader->GetOrdinal("TotalColumnas"));
				int inicioFila = reader->GetInt32(reader->GetOrdinal("InicioFila"));
				int inicioColumna = reader->GetInt32(reader->GetOrdinal("InicioColumna"));
				int finFila = reader->GetInt32(reader->GetOrdinal("FinFila"));
				int  finColumna = reader->GetInt32(reader->GetOrdinal("FinColumna"));
				String^ heuristica = reader->GetString(reader->GetOrdinal("TipoDistancia"));
				int pesoH = reader->GetInt32(reader->GetOrdinal("MovimientoCeldaHorizontal"));
				int pesoV = reader->GetInt32(reader->GetOrdinal("MovimientoCeldaVertical"));
				int pesoD = reader->GetInt32(reader->GetOrdinal("MovimientoCeldaDiagonal"));
				puntoInicio = Point(inicioFila, inicioColumna);
				puntoLlegada = Point(finFila, finColumna);
				nuevoLaberinto = gcnew Laberinto(filas, columnas, width, height, heuristica, pesoH, pesoV, pesoD);
				nuevoLaberinto->SetPuntoInicio(puntoInicio);
				nuevoLaberinto->SetPuntoLlegada(puntoLlegada);
				mapas->Add(idMapa, nuevoLaberinto);
			}
			reader->Close();


			for each (int clave in gcnew List<int>(mapas->Keys)) {

				Laberinto^ laberinto = mapas[clave];
				String^ query = String::Format("SELECT * FROM MapaCelda WHERE IdMapa = {0}", clave);
				SqlCommand^ command = gcnew SqlCommand(query, conexion);
				SqlDataReader^ reader = command->ExecuteReader();
				while (reader->Read()) {
					int fila = reader->GetInt32(reader->GetOrdinal("Fila"));
					int columna = reader->GetInt32(reader->GetOrdinal("Columna"));
					bool esMuro = reader->GetBoolean(reader->GetOrdinal("EsMuro"));
					laberinto->setCelda(fila, columna, esMuro ? 1 : 0);
				}
				reader->Close();
			}
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al cargar el mapa desde la base de datos: {0}", ex->Message);
		}
		finally {
			if (conexion->State == ConnectionState::Open) {
				conexion->Close();
			}
		}		

		return mapas;

	}
}
