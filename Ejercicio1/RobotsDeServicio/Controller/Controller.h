#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace Model;
namespace Controller {
	public ref class Controller
	{
	public:
		static List< robot^ > ^ robots;
		static int add_robot(String^ name, String^ state, String^ speed);
		static robot^ read_robot(int id);
		static bool update_robot(int id, String^ name, String^ state, String^ speed);
		static bool delete_robot(int id);

		// TODO: Add your methods for this class here.
	};
}
