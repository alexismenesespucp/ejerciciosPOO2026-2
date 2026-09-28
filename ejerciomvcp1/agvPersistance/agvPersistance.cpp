#include "pch.h"

#include "agvPersistance.h"
#using <System.Runtime.Serialization.dll>

using namespace System;
using namespace System::IO;
using namespace agvPersistance;
using namespace System::Collections::Generic;
using namespace agvModel;
using namespace System::Xml::Serialization;
using namespace System::Runtime::Serialization::Json;
using namespace System::Runtime::Serialization::Formatters::Binary;


void persistance::guardarVehiculoTxt(List<vehiculoAgv^> ^ flota) {
	StreamWriter^ sw = gcnew StreamWriter("vehiculos.txt", false);
	for each (vehiculoAgv ^ vehiculo in flota) {
		if (AGVTractorArrastre^ agv = dynamic_cast<AGVTractorArrastre^>(vehiculo)) {
			Console::WriteLine("Guardando 1");
			sw->WriteLine("AGVTractorArrastre|{0}|{1}|{2}|{3}", agv->id, agv->Codigo, agv->Bateria, agv->CantidadVagones);
		}
		else if (AGVTrasnpaleta^ agv = dynamic_cast<AGVTrasnpaleta^>(vehiculo)) {
			Console::WriteLine("Guardando 2");

			sw->WriteLine("AGVTrasnpaleta|{0}|{1}|{2}|{3}", agv->id, agv->Codigo, agv->Bateria, agv->AlturaMaximaHorquilla);
		}
	}
	sw->Close();
}

List<vehiculoAgv^>^ persistance::leerVehiculosTxt() {
	List<vehiculoAgv^>^ flota = gcnew List<vehiculoAgv^>();
	if (!File::Exists("vehiculos.txt")) {
		Console::WriteLine("El archivo no existe.");
		return flota;
	}
	StreamReader^ sr = gcnew StreamReader("vehiculos.txt");
	String^ linea;
	while ((linea = sr->ReadLine()) != nullptr) {
		array<String^>^ partes = linea->Split('|');
		String^ tipo = partes[0];
		int id = Convert::ToInt32(partes[1]);
		String^ codigo = partes[2];
		double bateria = Convert::ToDouble(partes[3]);
		if (tipo == "AGVTractorArrastre") {
			int cantidadVagones = Convert::ToInt32(partes[4]);
			AGVTractorArrastre^ agv = gcnew AGVTractorArrastre(id, codigo, bateria, cantidadVagones);
			flota->Add(agv);
		}
		else if (tipo == "AGVTrasnpaleta") {
			double alturaMaximaHorquilla = Convert::ToDouble(partes[4]);
			AGVTrasnpaleta^ agv = gcnew AGVTrasnpaleta(id, codigo, bateria, alturaMaximaHorquilla);
			flota->Add(agv);
		}
	}
	sr->Close();
	return flota;
}

void persistance::guardarVehiculoCsv(List<vehiculoAgv^>^ flota) {
	StreamWriter^ sw = gcnew StreamWriter("vehiculos.csv", false);
	if(flota == nullptr || flota->Count == 0) {
		Console::WriteLine("No hay vehículos en la flota para guardar.");
		return;
	}
	for each (vehiculoAgv ^ vehiculo in flota) {
		if (AGVTractorArrastre^ agv = dynamic_cast<AGVTractorArrastre^>(vehiculo)) {
			sw->WriteLine("AGVTractorArrastre,{0},{1},{2},{3}", agv->id, agv->Codigo, agv->Bateria, agv->CantidadVagones);
		}
		else if (AGVTrasnpaleta^ agv = dynamic_cast<AGVTrasnpaleta^>(vehiculo)) {
			sw->WriteLine("AGVTrasnpaleta,{0},{1},{2},{3}", agv->id, agv->Codigo, agv->Bateria, agv->AlturaMaximaHorquilla);
		}
	}
	sw->Close();
}


List<vehiculoAgv^>^ persistance::leerVehiculosCsv() {
	List<vehiculoAgv^>^ flota = gcnew List<vehiculoAgv^>();
	if (!File::Exists("vehiculos.csv")) {
		Console::WriteLine("El archivo no existe.");
		return flota;
	}
	StreamReader^ sr = gcnew StreamReader("vehiculos.csv");
	String^ linea;
	while ((linea = sr->ReadLine()) != nullptr) {
		array<String^>^ partes = linea->Split(',');
		String^ tipo = partes[0];
		int id = Convert::ToInt32(partes[1]);
		String^ codigo = partes[2];
		double bateria = Convert::ToDouble(partes[3]);
		if (tipo == "AGVTractorArrastre") {
			int cantidadVagones = Convert::ToInt32(partes[4]);
			AGVTractorArrastre^ agv = gcnew AGVTractorArrastre(id, codigo, bateria, cantidadVagones);
			flota->Add(agv);
		}
		else if (tipo == "AGVTrasnpaleta") {
			double alturaMaximaHorquilla = Convert::ToDouble(partes[4]);
			AGVTrasnpaleta^ agv = gcnew AGVTrasnpaleta(id, codigo, bateria, alturaMaximaHorquilla);
			flota->Add(agv);
		}
	}
	sr->Close();
	return flota;
}

void persistance::guardarVehiculoXml(List<vehiculoAgv^>^ flota) {
	XmlSerializer^ serializer = gcnew XmlSerializer(List<vehiculoAgv^>::typeid);
	StreamWriter^ sw = gcnew StreamWriter("vehiculos.xml", false);
	serializer->Serialize(sw, flota);
	sw->Close();
}

List<vehiculoAgv^>^ persistance::leerVehiculosXml() {
	XmlSerializer^ serializer = gcnew XmlSerializer(List<vehiculoAgv^>::typeid);
	StreamReader^ sr = gcnew StreamReader("vehiculos.xml");
	List<vehiculoAgv^>^ flota = (List<vehiculoAgv^>^)serializer->Deserialize(sr);
	sr->Close();
	return flota;
}

void persistance::guardarVehiculoJson(List<vehiculoAgv^>^ flota) {
	FileStream^ fs = gcnew FileStream("vehiculos.json", FileMode::Create);
	DataContractJsonSerializer^ serializer = gcnew DataContractJsonSerializer(List<vehiculoAgv^>::typeid);
	serializer->WriteObject(fs, flota);
	fs->Close();
}

List<vehiculoAgv^>^ persistance::leerVehiculosJson() {
	if (!File::Exists("vehiculos.json")) {
		Console::WriteLine("El archivo no existe.");
		return nullptr;
	}
	FileStream^ fs = gcnew FileStream("vehiculos.json", FileMode::Open);
	DataContractJsonSerializer^ serializer = gcnew DataContractJsonSerializer(List<vehiculoAgv^>::typeid);
	List<vehiculoAgv^>^ flota = (List<vehiculoAgv^>^)serializer->ReadObject(fs);
	fs->Close();
	return flota;
}

void persistance::guardarVehiculoBinario(List<vehiculoAgv^>^ flota) {
	FileStream^ fs = gcnew FileStream("vehiculos.bin", FileMode::Create);
	BinaryFormatter^ formatter = gcnew BinaryFormatter();
	formatter->Serialize(fs, flota);
	fs->Close();
}

List<vehiculoAgv^>^ persistance::leerVehiculosBinario() {
	FileStream^ fs = gcnew FileStream("vehiculos.bin", FileMode::Open);
	BinaryFormatter^ formatter = gcnew BinaryFormatter();
	List<vehiculoAgv^>^ flota = (List<vehiculoAgv^>^)formatter->Deserialize(fs);
	fs->Close();
	return flota;
}