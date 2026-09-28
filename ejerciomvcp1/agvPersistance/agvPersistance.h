#pragma once

using namespace System;
using namespace agvModel;
using namespace System::Collections::Generic;

namespace agvPersistance {
	public ref class persistance
	{
		public:
			String^ rutaArchivoTxt = "vehiculos.txt";
			String^ rutaArchivoCsv = "vehiculos.csv";
			static void guardarVehiculoTxt(List<vehiculoAgv^>^ flota);
			static List<vehiculoAgv^>^ leerVehiculosTxt();
			static void guardarVehiculoCsv(List<vehiculoAgv^>^ flota);
			static List<vehiculoAgv^>^ leerVehiculosCsv();
			static void guardarVehiculoXml(List<vehiculoAgv^>^ flota);
			static List<vehiculoAgv^>^ leerVehiculosXml();
			static void guardarVehiculoJson(List<vehiculoAgv^>^ flota);
			static List<vehiculoAgv^>^ leerVehiculosJson();
			static void guardarVehiculoBinario(List<vehiculoAgv^>^ flota);
			static List<vehiculoAgv^>^ leerVehiculosBinario();

	};
}
