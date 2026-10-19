#include "Form1.h"
using namespace SinusoidalSignal;

int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Form1^ form = gcnew Form1();
    form->Text = "Ejemplo de Dibujo en Pantalla con la Clase Graphics";
    Application::Run(form);
    return 0;
}