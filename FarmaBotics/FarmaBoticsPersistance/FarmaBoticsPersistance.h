#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace FarmaBoticsModel;

namespace FarmaBoticsPersistance {
	public ref class Persistance abstract sealed
	{
	private: 
		static String^ rutaArchivoTXT = "robots.txt";
		static String^ rutaArchivoXML = "robots.xml";
	public:
		static void GuardarEnTxt(List<RobotMovil^>^ robots);
		static List<RobotMovil^>^ CargarDesdeTxt();
		static void GuardarEnXML(List<RobotMovil^>^ robots);
		static List<RobotMovil^>^ CargarDesdeXML();
		// TODO: Add your methods for this class here.
	};
}
