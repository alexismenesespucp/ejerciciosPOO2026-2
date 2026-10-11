#pragma once
#include "RobotMovil.h"

using namespace System;
using namespace System::Collections::Generic;

namespace FarmaBoticsModel {
	public ref class RobotSanitizador : public RobotMovil
	{
	public:
		property double PotenciaLamparaWatts;
		property double VolumenDesinfectanteLitros;
		RobotSanitizador() {}
		RobotSanitizador(int serialId, String^ alias, String^ zonaAsignada, double nivelBateria, double horasOperacion, double PotenciaLamparaWatts, double VolumenDesinfectanteLitros)
			: RobotMovil(serialId, alias, zonaAsignada, nivelBateria, horasOperacion)
		{
			this->PotenciaLamparaWatts = PotenciaLamparaWatts;
			this->VolumenDesinfectanteLitros = VolumenDesinfectanteLitros;
		};
		virtual double CalcularConsumoEnergeticoKWh() override
		{
			return 0.85 + (this->PotenciaLamparaWatts  * 0.008) + (this->VolumenDesinfectanteLitros * 0.04);
		}
	};
}