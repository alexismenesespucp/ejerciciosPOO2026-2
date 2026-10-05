#include "pch.h"
#include "UnidadPersistence.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace GeoTechModel;

void GeotechPersistance::UnidadPersistence::GuardarEnCSV(List<UnidadInspeccion^>^ unidades) {
	StreamWriter^ writer = gcnew StreamWriter(RUTA_CSV,false);
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

List<UnidadInspeccion^>^ GeotechPersistance::UnidadPersistence::CargarDesdeCSV() {
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
			unidades->Add(gcnew DronAereo(id, codigoSerie, bateriaRestante,cantidadHelices ));
		}
		else if (tipo == "ROVER") {
			double peso = Convert::ToDouble(campos[4]);
			unidades->Add(gcnew RoverTerrestre(id, codigoSerie, bateriaRestante, 10.0));
		}
	}
	reader->Close();
	return unidades;
}