#pragma once
#include "RobotMovil.h"

using namespace System;
using namespace System::Collections::Generic;

namespace FarmaBoticsModel {
	public ref class RobotDispensador : public RobotMovil
	{
	public:
		property int CapacidadBandejas;
		property double CargaActualKg;
		RobotDispensador() {}
		RobotDispensador(int serialId, String^ alias, String^ zonaAsignada, double nivelBateria, double horasOperacion, int CapacidadBandejas, int CargaActualKg)
			: RobotMovil(serialId, alias, zonaAsignada, nivelBateria, horasOperacion)
		{
			this->CapacidadBandejas = CapacidadBandejas;
			this->CargaActualKg = CargaActualKg;
		};
		virtual double CalcularConsumoEnergeticoKWh() override
		{
			return 1.20 + (0.15 * this->CapacidadBandejas) + (0.05 * this->CargaActualKg);
		}
	};
}