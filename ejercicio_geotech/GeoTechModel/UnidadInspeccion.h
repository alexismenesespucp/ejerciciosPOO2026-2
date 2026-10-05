#pragma once

using namespace System;

namespace GeoTechModel {
	public ref class UnidadInspeccion abstract
	{
	public:
		property int Id;
		property String^ CodigoSerie;
		property double BateriaRestante;

		UnidadInspeccion() {};

		UnidadInspeccion(int id, String^ codigoSerie, double bateriaRestante)
		{
			this->Id = id;
			this->CodigoSerie = codigoSerie;
			this->BateriaRestante = bateriaRestante;
		}

		virtual double CalcularAutonomiaHoras() abstract;
	};
}