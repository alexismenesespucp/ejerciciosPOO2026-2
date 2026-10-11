#include "pch.h"
#include "RobotsController.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace FarmaBoticsModel;
using namespace FarmaBoticsPersistance;

namespace FarmaBoticsController {
	void RobotsController::RegistrarRobot(RobotMovil^ robot) {
		robots->Add(robot);
		Persistance::GuardarEnTxt(robots);
	}
	void RobotsController::ModificarRobot(int serialId, RobotMovil^ robot) {
		for (int i = 0; i < robots->Count; i++) {
			if (robots[i]->SerialId == serialId) {
				robots[i] = robot;
				Persistance::GuardarEnTxt(robots);
				return;
			}
		}
	}
	void RobotsController::ElminarRobot(int serialId) {
		for (int i = 0; i < robots->Count; i++) {
			if (robots[i]->SerialId == serialId) {
				robots->RemoveAt(i);
				Persistance::GuardarEnTxt(robots);
				return;
			}
		}
	}
	RobotMovil^ RobotsController::ObtenerRobot(int serialId) {
		for each (RobotMovil ^ robot in robots) {
			if (robot->SerialId == serialId) {
				return robot;
			}
		}
		return nullptr;
	}
}