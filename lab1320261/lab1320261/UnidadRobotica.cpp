#include "UnidadRobotica.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace UnidadRoboticaView;

int main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UnidadRobotica form;
	Application::Run(% form);
	return 0;

}
