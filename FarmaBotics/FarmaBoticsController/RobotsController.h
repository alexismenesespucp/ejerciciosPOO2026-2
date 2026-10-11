#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace FarmaBoticsModel;
using namespace FarmaBoticsPersistance;
namespace FarmaBoticsController {
	public ref class RobotsController abstract sealed
	{
	private:
		static List < RobotMovil^>^ robots;
	public:
		static RobotsController() {
			robots = Persistance::CargarDesdeTxt();
		}

		void RegistrarRobot(RobotMovil^ robot);
		void ModificarRobot(int serialId, RobotMovil^ robot);
		void ElminarRobot(int serialId);
		RobotMovil^ ObtenerRobot(int serialId);

	};
}