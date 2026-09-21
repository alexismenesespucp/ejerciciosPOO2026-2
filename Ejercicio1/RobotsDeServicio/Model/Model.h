#pragma once

using namespace System;

namespace Model {
	public ref class robot
	{
	public:
		int id;
		String^ name;
		String^ state;
		String^ speed;
		robot(int id, String^ name, String^ state, String^ speed) {
			this->id = id;
			this->name = name;
			this->state = state;
			this->speed = speed;
		}
	};
}
