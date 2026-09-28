#include "MainForm.h"

using namespace System;
using namespace agvVista;
using namespace System::Windows::Forms;


int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Form^ mainForm = gcnew MainForm();
	Application::Run(mainForm);
	return 0;
}