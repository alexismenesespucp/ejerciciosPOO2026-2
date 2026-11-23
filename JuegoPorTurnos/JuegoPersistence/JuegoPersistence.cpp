#include "pch.h"

#include "JuegoPersistence.h"

namespace JuegoPersistence {
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

	void Database::GuardarConexion(String^ IP) {
		try {
			SqlConnection^ connection = obtenerConexion();
			connection->Open();
			String^ query = "IF NOT EXISTS (SELECT 1 FROM UsuariosConectados WHERE IP = @IP) "
				"BEGIN "
				"    INSERT INTO UsuariosConectados (IP) VALUES (@IP) "
				"END";			SqlCommand^ command = gcnew SqlCommand(query, connection);
			command->Parameters->AddWithValue("@IP", IP);
			command->ExecuteNonQuery();
			connection->Close();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al guardar la conexión: " + ex->Message);
		}
	}

	void Database::UpdateConexion(String^ IP) {
		try {
			SqlConnection^ connection = obtenerConexion();
			connection->Open();
			String^ query = "UPDATE UsuariosConectados SET lastUpdate = GETDATE() WHERE IP = @IP";
			SqlCommand^ command = gcnew SqlCommand(query, connection);
			command->Parameters->AddWithValue("@IP", IP);
			command->ExecuteNonQuery();
			connection->Close();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al actualizar la conexión: " + ex->Message);
		}
	}

	List<String^>^ Database::ObtenerConexionActivas() {
		List<String^>^ conexiones = gcnew List<String^>();
		try {
			SqlConnection^ connection = obtenerConexion();
			connection->Open();
			String^ query = "SELECT COUNT(1) FROM UsuariosConectados "
				"WHERE IP = @IP AND DATEDIFF(SECOND, lastUpdate, GETDATE()) <= 5";
			SqlCommand^ command = gcnew SqlCommand(query, connection);
			SqlDataReader^ reader = command->ExecuteReader();
			while (reader->Read()) {
				conexiones->Add(reader->GetString(0));
			}
			reader->Close();
			connection->Close();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error al obtener conexiones activas: " + ex->Message);
		}
		return conexiones;
	}
}