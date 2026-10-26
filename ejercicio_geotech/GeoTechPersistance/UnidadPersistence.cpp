#include "pch.h"
#include "UnidadPersistence.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

namespace GeoTechPersistance {
	SqlConnection^ UnidadPersistence::obtenerConexion() {
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


	void UnidadPersistence::GuardarEstacionEnBD(UnidadInspeccion^ unidad) {
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			String^ query;
			Console::WriteLine("La unidad es: {0}", unidad->GetType()->ToString());
			if (unidad->GetType() == DronAereo::typeid) {
				DronAereo^ dron = dynamic_cast<DronAereo^>(unidad);
				query = String::Format("INSERT INTO UnidadesInspecciones (TipoVehiculo, CodigoSerie, BateriaRestante, CantidadHelices) VALUES ('{0}', '{1}', {2}, {3})",
					"DRONE", dron->CodigoSerie, dron->BateriaRestante, dron->CantidadHelices);

			}
			else if (unidad->GetType()== RoverTerrestre::typeid) {
				RoverTerrestre^ rover = dynamic_cast<RoverTerrestre^>(unidad);
				query = String::Format("INSERT INTO UnidadesInspecciones (TipoVehiculo, CodigoSerie, BateriaRestante, PesoCargaUtil) VALUES ('{0}', '{1}', {2}, {3})",
					"ROVER", rover->CodigoSerie, rover->BateriaRestante, rover->PesoCargaUtilKg);
			}
			else {
				throw gcnew ArgumentException("Tipo de unidad no reconocido.");
			}
			Console::WriteLine(query);
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			command->ExecuteNonQuery();

		}
		catch (Exception^ e) {
			Console::WriteLine("Error al conectar a la base de datos: {0}", e->Message);
		}
		finally {
			if (conexion->State == System::Data::ConnectionState::Open) conexion->Close();
		}
		//
		//for each (EstacionEnlace ^ estacion in estaciones) {
		//	String^ query = String::Format("INSERT INTO Estaciones (NumeroEstacion, NombreUbicacion, CapacidadUnidades, UnidadesConectadas) VALUES ({0}, '{1}', {2}, {3})",
		//		estacion->NumeroEstacion, estacion->NombreUbicacion, estacion->CapacidadUnidades, estacion->UnidadesConectadas);
		//	SqlCommand^ command = gcnew SqlCommand(query, conexion);
		//	command->ExecuteNonQuery();
		//}
		//conexion->Close();
	}

	void UnidadPersistence::ModificarEstacionEnBD(UnidadInspeccion^ unidad) {
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			String^ query;
			if (unidad->GetType() == DronAereo::typeid) {
				DronAereo^ dron = dynamic_cast<DronAereo^>(unidad);
				query = String::Format("UPDATE UnidadesInspecciones SET TipoVehiculo = '{0}', CodigoSerie = '{1}', BateriaRestante = {2}, CantidadHelices = {3}, PesoCargaUtil={4} WHERE Id = {5}",
					"DRONE", dron->CodigoSerie, dron->BateriaRestante, dron->CantidadHelices, "NULL", dron->Id);

			}
			else if (unidad->GetType() == RoverTerrestre::typeid) {
				RoverTerrestre^ rover = dynamic_cast<RoverTerrestre^>(unidad);
				query = String::Format("UPDATE UnidadesInspecciones SET TipoVehiculo = '{0}', CodigoSerie = '{1}', BateriaRestante = {2}, PesoCargaUtil = {3}, CantidadHelices={4} WHERE Id = {5}",
					"ROVER", rover->CodigoSerie, rover->BateriaRestante, rover->PesoCargaUtilKg, "NULL", rover->Id);
			}
			else {
				throw gcnew ArgumentException("Tipo de unidad no reconocido.");
			}
			Console::WriteLine(query);
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			command->ExecuteNonQuery();

		}
		catch (Exception^ e) {
			Console::WriteLine("Error al conectar a la base de datos: {0}", e->Message);
		}
		finally {
			if (conexion->State == System::Data::ConnectionState::Open) conexion->Close();
		}
		
	}

	void UnidadPersistence::EliminarEstacionEnBD(int idUnidad) {
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			String^ query = String::Format("DELETE FROM UnidadesInspecciones WHERE Id = {0}", idUnidad);
			Console::WriteLine(query);
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			command->ExecuteNonQuery();
		}
		catch (Exception^ e) {
			Console::WriteLine("Error al conectar a la base de datos: {0}", e->Message);
		}
		finally {
			if (conexion->State == System::Data::ConnectionState::Open) conexion->Close();
		}
	}

	List<UnidadInspeccion^>^ UnidadPersistence::CargarEstacionesDesdeBD() {
		List<UnidadInspeccion^>^ unidades = gcnew List<UnidadInspeccion^>();
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			String^ query = "SELECT * FROM UnidadesInspecciones";
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			SqlDataReader^ reader = command->ExecuteReader();
			while (reader->Read()) {
				int  id = reader->GetInt32(0);
				String^ tipo = reader->GetString(1);
				String^ codigoSerie = reader->GetString(2);
				double bateriaRestante = reader->GetDouble(3);
				double pesoCargaUtil = reader->IsDBNull(4) ? 0.0 : reader->GetDouble(4);
				int cantidadHelices = reader->IsDBNull(5) ? 0.0 : reader->GetInt32(5);
				
				if (tipo == "DRONE") {
					unidades->Add(gcnew DronAereo(id, codigoSerie, bateriaRestante, cantidadHelices));
				}
				else if (tipo == "ROVER") {
					unidades->Add(gcnew RoverTerrestre(id, codigoSerie, bateriaRestante, pesoCargaUtil));
				}
				Console::WriteLine("El tipo es {0}", tipo);
			}
			reader->Close();
		}
		catch (Exception^ e) {
			Console::WriteLine("Error al conectar a la base de datos: {0}", e->Message);
		}
		finally {
			if (conexion->State == System::Data::ConnectionState::Open) {
				conexion->Close();
				Console::WriteLine("Conexión a la base de datos cerrada.");
			}
		}
		return unidades;

	}


	void UnidadPersistence::GuardarEnCSV(List<UnidadInspeccion^>^ unidades) {
		StreamWriter^ writer = gcnew StreamWriter(RUTA_CSV, false);
		writer->WriteLine("TIPO,ID,CODIGO,BATERIA,PARAMETRO_EXTRA");
		for each (UnidadInspeccion ^ unidad in unidades) {
			if (DronAereo^ dron = dynamic_cast<DronAereo^>(unidad)) {
				String^ linea = String::Format("DRON,{0},{1},{2},{3}", dron->Id, dron->CodigoSerie, dron->BateriaRestante, dron->CantidadHelices);
				writer->WriteLine(linea);
			}
			else if (RoverTerrestre^ rover = dynamic_cast<RoverTerrestre^>(unidad)) {
				String^ linea = String::Format("ROVER,{0},{1},{2},{3}", rover->Id, rover->CodigoSerie, rover->BateriaRestante, rover->PesoCargaUtilKg);
				writer->WriteLine(linea);
			}
			else {
				// Handle unknown unit type if necessary
			}
		}
		writer->Close();
	}

	List<UnidadInspeccion^>^ UnidadPersistence::CargarDesdeCSV() {
		List<UnidadInspeccion^>^ unidades = gcnew List<UnidadInspeccion^>();
		if (!File::Exists(RUTA_CSV)) {
			return unidades;
		}
		StreamReader^ reader = gcnew StreamReader(RUTA_CSV);
		String^ linea;
		while ((linea = reader->ReadLine()) != nullptr) {
			array<String^>^ campos = linea->Split(',');
			String^ tipo = campos[0];
			int id = Convert::ToInt32(campos[1]);
			String^ codigoSerie = campos[2];
			double bateriaRestante = Convert::ToDouble(campos[3]);

			if (tipo == "DRON") {
				int cantidadHelices = Convert::ToInt32(campos[4]);
				unidades->Add(gcnew DronAereo(id, codigoSerie, bateriaRestante, cantidadHelices));
			}
			else if (tipo == "ROVER") {
				double peso = Convert::ToDouble(campos[4]);
				unidades->Add(gcnew RoverTerrestre(id, codigoSerie, bateriaRestante, 10.0));
			}
		}
		reader->Close();
		return unidades;
	}
}