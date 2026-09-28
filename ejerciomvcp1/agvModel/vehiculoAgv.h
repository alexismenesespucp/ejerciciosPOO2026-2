#pragma once
#using <System.Runtime.Serialization.dll>

using namespace System;
using namespace System::Xml::Serialization;
using namespace System::Runtime::Serialization;
namespace agvModel {

	ref class AGVTrasnpaleta;
	ref class AGVTractorArrastre;
	[Serializable]
	[DataContract]
	[KnownType(AGVTrasnpaleta::typeid)]
	[KnownType(AGVTractorArrastre::typeid)]
	[XmlInclude(AGVTrasnpaleta::typeid)]
	[XmlInclude(AGVTractorArrastre::typeid)]

	public ref class vehiculoAgv abstract
	{
	public:
		[DataMember]
		property int id;
		[DataMember]
		property String^ Codigo;
		[DataMember]
		property double Bateria;

		vehiculoAgv() {};

		vehiculoAgv(int id, String^ codigo, double bateria) {
			this->id = id;
			this->Codigo = codigo;
			this->Bateria = bateria;
		}

		virtual double CalcularCapacidadCargaMaxima() abstract;

	};
	[Serializable]
	[DataContract]
	public ref class AGVTrasnpaleta : public vehiculoAgv {
	public:
		[DataMember]	
		property double AlturaMaximaHorquilla;

		AGVTrasnpaleta() {};
		AGVTrasnpaleta(int id, String^ codigo, double bateria, double altura) : vehiculoAgv(id, codigo, bateria) {
			this->AlturaMaximaHorquilla = altura;
		}

		virtual double CalcularCapacidadCargaMaxima() override {
			return 1200-this->AlturaMaximaHorquilla * 50; // Example calculation
		}
	};
	[Serializable]
	[DataContract]
	public ref class AGVTractorArrastre : public vehiculoAgv {
	public:
		[DataMember]	
		property int CantidadVagones;
		AGVTractorArrastre() {};

		AGVTractorArrastre(int id, String^ codigo, double bateria, int cantidadVagones) : vehiculoAgv(id, codigo, bateria) {
			this->CantidadVagones = cantidadVagones;
		}

		virtual double CalcularCapacidadCargaMaxima() override {
			return this->CantidadVagones * 800; // Example calculation
		}
	};
	

}
