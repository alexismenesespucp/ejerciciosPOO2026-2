#include "robots.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace View;

int Main(array<System::String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	robots form;
	Application::Run(% form);
	return 0;
}
