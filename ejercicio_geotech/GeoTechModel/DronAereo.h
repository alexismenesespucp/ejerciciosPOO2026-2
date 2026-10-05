#pragma once
#include "UnidadInspeccion.h"
using namespace System;

namespace GeoTechModel {
	public ref class DronAereo : public UnidadInspeccion
	{
	public:
		property int CantidadHelices;

		DronAereo() {};

		DronAereo(int id, String^ codigoSerie, double bateriaRestante, int cantidadHelices)
			: UnidadInspeccion(id, codigoSerie, bateriaRestante)
		{
			Console::WriteLine("Creando DronAereo con ID: {0}, CodigoSerie: {1}, BateriaRestante: {2}, CantidadHelices: {3}", id, codigoSerie, bateriaRestante, cantidadHelices);	
			this->CantidadHelices = cantidadHelices;	
		}
			
		virtual double CalcularAutonomiaHoras() override
		{
			return (this->BateriaRestante / 100.0)* (3.5 - (this->CantidadHelices * 0.2));
		}
	};
}