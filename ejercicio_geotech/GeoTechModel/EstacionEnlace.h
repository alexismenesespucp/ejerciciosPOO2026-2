#pragma once

using namespace System;

namespace GeoTechModel {
	public ref class EstacionEnlace
	{
	public:
		property int NumeroEstacion;
		property String^ NombreUbicacion;
		property int CapacidadUnidades;
		property int UnidadesConectadas;
		EstacionEnlace() {};
		EstacionEnlace(int numeroEstacion, String^ nombreUbicacion, int capacidadUnidades)
		{
			this->NumeroEstacion = numeroEstacion;
			this->NombreUbicacion = nombreUbicacion;
			this->CapacidadUnidades = capacidadUnidades;
			this->UnidadesConectadas = 0;
		};

		bool TieneEspacioDisponible()
		{
			return this->UnidadesConectadas < this->CapacidadUnidades;
		}

	};
}