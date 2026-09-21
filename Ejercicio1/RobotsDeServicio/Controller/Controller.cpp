#include "pch.h"

#include "Controller.h"
using namespace Model;

int Controller::Controller::add_robot(String^ name, String^ state, String^ speed) {
	int id = Controller::Controller::robots->Count;
	robot^ new_robot = gcnew robot(id, name, state, speed);

	Controller::Controller::robots->Add(new_robot);
	Console::WriteLine("Robot added: {0}, {1}, {2}, {3}", new_robot->id, new_robot->name, new_robot->state, new_robot->speed);
	return id;
}

robot^ Controller::Controller::read_robot(int id) {
	for (int i = 0; i < Controller::Controller::robots->Count; i++) {
		if (Controller::Controller::robots[i]->id == id) {
			robot^ r = Controller::Controller::robots[i];
			Console::WriteLine("Robot read: {0}, {1}, {2}, {3}", r->id, r->name, r->state, r->speed);
			return r;
		}
	}
	return nullptr;
}

bool Controller::Controller::update_robot(int id, String^ name, String^ state, String^ speed) {
	for (int i = 0; i < Controller::Controller::robots->Count; i++) {
		if (Controller::Controller::robots[i]->id == id) {
			Controller::Controller::robots[i]->name = name;
			Controller::Controller::robots[i]->state = state;
			Controller::Controller::robots[i]->speed = speed;
			return true;
		}
	}
	return false;

}

bool Controller::Controller::delete_robot(int id) {
	for (int i = 0; i < Controller::Controller::robots->Count; i++) {
		if (Controller::Controller::robots[i]->id == id) {
			Controller::Controller::robots->RemoveAt(i);
			return true;
		}
	}
	return false;
}