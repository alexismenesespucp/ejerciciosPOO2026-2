#include "FormLaberinto.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace SimuladorGUIApp;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FormLaberinto form;
	Application::Run(% form);
	return 0;
}