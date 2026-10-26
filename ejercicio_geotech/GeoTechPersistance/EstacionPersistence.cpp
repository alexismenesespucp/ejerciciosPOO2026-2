#include "pch.h"
#include "EstacionPersistence.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

namespace GeoTechPersistance {
	SqlConnection^ EstacionPersistence::obtenerConexion() {
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
	

	void EstacionPersistence::GuardarEstacionEnBD(EstacionEnlace^ estacion) {
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
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
	
	List<EstacionEnlace^>^ EstacionPersistence::CargarEstacionesDesdeBD() {
		List<EstacionEnlace^>^ estaciones = gcnew List<EstacionEnlace^>();
		SqlConnection^ conexion = obtenerConexion();
		try {
			conexion->Open();
			String^ query = "SELECT * FROM UnidadesInspecciones";
			SqlCommand^ command = gcnew SqlCommand(query, conexion);
			SqlDataReader^ reader = command->ExecuteReader();
			while (reader->Read()) {

			}
			reader->Close();
			
			//String^ query = "SELECT NumeroEstacion, NombreUbicacion, CapacidadUnidades, UnidadesConectadas FROM Estaciones";
			//SqlCommand^ command = gcnew SqlCommand(query, conexion);
			//SqlDataReader^ reader = command->ExecuteReader();
			//while (reader->Read()) {
			//	int numeroEstacion = reader->GetInt32(0);
			//	String^ nombreUbicacion = reader->GetString(1);
			//	int capacidadUnidades = reader->GetInt32(2);
			//	int unidadesConectadas = reader->GetInt32(3);
			//	EstacionEnlace^ estacion = gcnew EstacionEnlace(numeroEstacion, nombreUbicacion, capacidadUnidades);
			//	estacion->UnidadesConectadas = unidadesConectadas;
			//	estaciones->Add(estacion);
			//}
			//reader->Close();
				
			
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
		return estaciones;
		
	}

	void EstacionPersistence::GuardarEstaciones(List<EstacionEnlace^>^ estaciones) {
		StreamWriter^ writer = gcnew StreamWriter(RUTA_TXT, false);
		for each (EstacionEnlace ^ estacion in estaciones) {
			String^ linea = String::Format("{0},{1},{2},{3}", estacion->NumeroEstacion, estacion->NombreUbicacion, estacion->CapacidadUnidades, estacion->UnidadesConectadas);
			writer->WriteLine(linea);
		}
		writer->Close();
	}
	List<EstacionEnlace^>^ EstacionPersistence::CargarEstaciones() {
		List<EstacionEnlace^>^ estaciones = gcnew List<EstacionEnlace^>();
		if (!File::Exists(RUTA_TXT)) {
			return estaciones;
		}
		StreamReader^ reader = gcnew StreamReader(RUTA_TXT);
		String^ linea;
		while ((linea = reader->ReadLine()) != nullptr) {
			array<String^>^ campos = linea->Split(',');
			int numeroEstacion = Convert::ToInt32(campos[0]);
			String^ nombreUbicacion = campos[1];
			int capacidadUnidades = Convert::ToInt32(campos[2]);
			int unidadesConectadas = Convert::ToInt32(campos[3]);
			EstacionEnlace^ estacion = gcnew EstacionEnlace(numeroEstacion, nombreUbicacion, capacidadUnidades);
			estacion->UnidadesConectadas = unidadesConectadas;
			estaciones->Add(estacion);
		}
		reader->Close();
		return estaciones;
	}
}