#include "pch.h"
#include "EstacionPersistence.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

namespace GeoTechPersistance {
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