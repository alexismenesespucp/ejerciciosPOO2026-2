#include "VistaDelJuego.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	Application::Run(gcnew GUIView::VistaDelJuego());
	return 0;
}