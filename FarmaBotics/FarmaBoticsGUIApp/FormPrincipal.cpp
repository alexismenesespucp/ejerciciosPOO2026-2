#include "FormPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace FarmaBoticsGUIApp;

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FormPrincipal form;
	Application::Run(%form);
	return 0;
}