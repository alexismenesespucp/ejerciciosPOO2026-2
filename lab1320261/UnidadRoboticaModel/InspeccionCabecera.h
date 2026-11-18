#include "pch.h"
#include "InspeccionDetail.h"

using namespace System;
using namespace System::Collections::Generic;

namespace UnidadRoboticaModel {
	public ref class InspeccionCabecera
	{
	public:
		property int inspeccionId;
		property String^ codigoLote;
		property int robotId;
		property String^ inspector;
		property String^ resultadoGeneral;
		property DateTime fechaInspeccion;
		property List<InspeccionDetail^>^ detalles;
	};
		
}
