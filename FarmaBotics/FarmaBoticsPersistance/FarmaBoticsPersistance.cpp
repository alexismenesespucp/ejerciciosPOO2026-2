#include "pch.h"

#include "FarmaBoticsPersistance.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Xml::Serialization;
using namespace FarmaBoticsModel;

namespace FarmaBoticsPersistance {

	void Persistance::GuardarEnTxt(List<RobotMovil^>^ robots) {
		StreamWriter^ writer = gcnew StreamWriter(rutaArchivoTXT);
		for each (RobotMovil ^ robot in robots) {
			String^ tipo = robot->GetType()->Name;
			String^ linea = String::Format("{0},{1},{2},{3},{4}", tipo, robot->SerialId, robot->Alias, robot->ZonaAsignada, robot->NivelBateria, robot->HorasOperacion);
			if (tipo == "RobotDispensador") {
				RobotDispensador^ dispensador = safe_cast<RobotDispensador^>(robot);
				linea += String::Format(",{0},{1}", dispensador->CapacidadBandejas, dispensador->CargaActualKg);
			}
			else if (tipo == "RobotSanitizador") {
				RobotSanitizador^ sanitizador = safe_cast<RobotSanitizador^>(robot);
				linea += String::Format(",{0},{1}", sanitizador->PotenciaLamparaWatts, sanitizador->VolumenDesinfectanteLitros);
			}
			writer->WriteLine(linea);
		}
		writer->Close();

	}
	List<RobotMovil^>^ Persistance::CargarDesdeTxt() {
		List<RobotMovil^>^ robots = gcnew List<RobotMovil^>();
		if (!File::Exists(rutaArchivoTXT)) {
			return robots;
		}
		StreamReader^ reader = gcnew StreamReader(rutaArchivoTXT);
		String^ linea;
		while ((linea = reader->ReadLine()) != nullptr) {
			array<String^>^ partes = linea->Split(',');
			String^ tipo = partes[0];
			int serialId = Convert::ToInt32(partes[1]);
			String^ alias = partes[2];
			String^ zonaAsignada = partes[3];
			double nivelBateria = Convert::ToDouble(partes[4]);
			double horasOperacion = Convert::ToDouble(partes[5]);
			if (tipo == "RobotDispensador") {
				int capacidadBandejas = Convert::ToInt32(partes[6]);
				double cargaActualKg = Convert::ToDouble(partes[7]);
				RobotDispensador^ dispensador = gcnew RobotDispensador(serialId, alias, zonaAsignada, nivelBateria, horasOperacion, capacidadBandejas, cargaActualKg);
				robots->Add(dispensador);
			}
			else if (tipo == "RobotSanitizador") {
				double potenciaLamparaWatts = Convert::ToDouble(partes[6]);
				double volumenDesinfectanteLitros = Convert::ToDouble(partes[7]);
				RobotSanitizador^ sanitizador = gcnew RobotSanitizador(serialId, alias, zonaAsignada, nivelBateria, horasOperacion, potenciaLamparaWatts, volumenDesinfectanteLitros);
				robots->Add(sanitizador);
			}
		}
		reader->Close();
		return robots;
	}

	void Persistance::GuardarEnXML(List<RobotMovil^>^ robots) {
		StreamWriter^ writer = gcnew StreamWriter(rutaArchivoXML);
		XmlSerializer^ serializer = gcnew XmlSerializer(List<RobotMovil^>::typeid);
		serializer->Serialize(writer, robots);
		writer->Close();
	}

	List<RobotMovil^>^ Persistance::CargarDesdeXML() {
		if (!File::Exists(rutaArchivoXML)) {
			return gcnew List<RobotMovil^>();
		}
		StreamReader^ reader = gcnew StreamReader(rutaArchivoXML);
		XmlSerializer^ serializer = gcnew XmlSerializer(List<RobotMovil^>::typeid);
		List<RobotMovil^>^ robots = safe_cast<List<RobotMovil^>^>(serializer->Deserialize(reader));
		reader->Close();
		return robots;
	}

}
