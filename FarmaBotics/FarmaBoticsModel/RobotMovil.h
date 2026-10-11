#pragma once
using namespace System;
using namespace System::Xml::Serialization;
using namespace System::Collections::Generic;

namespace FarmaBoticsModel {
	ref class RobotDispensador;
	ref class RobotSanitizador;
	[XmlInclude(RobotDispensador::typeid)]
	[XmlInclude(RobotSanitizador::typeid)]
	public ref class RobotMovil abstract
	{
	public:
		property int SerialId;
		property String^ Alias;
		property String^ ZonaAsignada;
		property double NivelBateria;
		property double HorasOperacion;

		RobotMovil(){}
		

		RobotMovil(int serialId, String^ alias, String^ zonaAsignada, double nivelBateria, double horasOperacion)
		{
			this->SerialId = serialId;
			this->Alias = alias;
			this->ZonaAsignada = zonaAsignada;
			this->NivelBateria = nivelBateria;
			this->HorasOperacion = horasOperacion;
		};

		virtual double CalcularConsumoEnergeticoKWh() abstract;
	};

}