#pragma once
#include "UnidadInspeccion.h"
using namespace System;

namespace GeoTechModel {
	public ref class RoverTerrestre : public UnidadInspeccion
	{
	public:
		property double PesoCargaUtilKg;

		RoverTerrestre() {};

		RoverTerrestre(int id, String^ codigoSerie, double bateriaRestante, double pesoCargaUtilKg)
			: UnidadInspeccion(id, codigoSerie, bateriaRestante)
		{
			this->PesoCargaUtilKg = pesoCargaUtilKg;
		};

		virtual double CalcularAutonomiaHoras() override
		{
			return (this->BateriaRestante / 100.0) * (8.0 - (this->PesoCargaUtilKg * 0.5));
		}
	};

}
