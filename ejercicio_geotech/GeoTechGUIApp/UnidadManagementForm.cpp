#include "UnidadManagementForm.h"

using namespace System;
using namespace GeoTechGUIApp;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UnidadManagementForm formulario;
	Application::Run(%formulario);
	return 0;
}