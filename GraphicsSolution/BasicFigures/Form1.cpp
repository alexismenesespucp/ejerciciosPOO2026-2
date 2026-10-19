#include "Form1.h"
using namespace BasicFigures;

int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Form1^ form = gcnew Form1();
    form->Text = "Ejemplo de Dibujo de Líneas y Formas Básicas";
    Application::Run(form);
    return 0;
}
