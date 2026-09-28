#pragma once

namespace agvModel {
	public ref class EstacionCarga
	{
		property int NumeroEstacion;
		property int BahiasTotales;
		property int BahiasOcupadas;

		EstacionCarga() {};

		EstacionCarga(int numeroEstacion, int bahiasTotales) {
			this->NumeroEstacion = numeroEstacion;
			this->BahiasTotales = bahiasTotales;
			this->BahiasOcupadas = 0;
		}

		bool TieneBahiaDisponible() {
			return this->BahiasOcupadas < this->BahiasTotales;
		}
	};
}

