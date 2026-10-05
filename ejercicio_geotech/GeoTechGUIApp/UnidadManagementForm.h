#pragma once

namespace GeoTechGUIApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace GeoTechModel;
	using namespace GeoTechController;

	/// <summary>
	/// Summary for UnidadManagementForm
	/// </summary>
	public ref class UnidadManagementForm : public System::Windows::Forms::Form
	{
	public:

		UnidadManagementForm(void)
		{
			//InitializeComponent();
			InicializarComponentesManual();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UnidadManagementForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		TextBox^ txtId;
		TextBox^ txtCodigo;
		TextBox^ txtBateria;
		ComboBox^ cboTipo;
		Label^ lblParametroExtra;
		NumericUpDown^ numParametroExtra;
		DataGridView^ dgvFlota;
		Button^ btnRegistrar;
		Button^ btnMayorAutonomia;
		void InicializarComponentesManual() {
			this->Text = "Telemetria y Control de flota - GeoTech SCADA";
			this->Size = System::Drawing::Size(850, 480);
			this->StartPosition = FormStartPosition::CenterScreen;

			GroupBox^ grpDatos = gcnew GroupBox();
			grpDatos->Text = "Parametors de la unidad";
			grpDatos->Location = Point(15, 15);
			grpDatos->Size = System::Drawing::Size(280, 400);

			Label^ lblId = gcnew Label();
			lblId->Text = "ID:";
			lblId->Location = Point(15, 30);
			lblId->Size = System::Drawing::Size(100, 20);
			txtId = gcnew TextBox();
			txtId->Location = Point(120, 27);
			txtId->Size = System::Drawing::Size(140, 20);
			Label^ lblCod = gcnew Label();
			lblCod->Text = "Código Serie:";
			lblCod->Location = Point(15, 65);
			lblCod->Size = System::Drawing::Size(100, 20);
			txtCodigo = gcnew TextBox();
			txtCodigo->Location = Point(120, 62);
			txtCodigo->Size = System::Drawing::Size(140, 20);

			Label^ lblBat = gcnew Label();
			lblBat->Text = "Batería (%):";
			lblBat->Location = Point(15, 100);
			lblBat->Size = System::Drawing::Size(100, 20);
			txtBateria = gcnew TextBox();
			txtBateria->Location = Point(120, 97);
			txtBateria->Size = System::Drawing::Size(140, 20);

			Label^ lblTipo = gcnew Label();
			lblTipo->Text = "Tipo Unidad:";
			lblTipo->Location = Point(15, 135);
			lblTipo->Size = System::Drawing::Size(100, 20);
			cboTipo = gcnew ComboBox();
			cboTipo->Location = Point(120, 132);
			cboTipo->Size = System::Drawing::Size(140, 20);
			cboTipo->DropDownStyle = ComboBoxStyle::DropDownList;
			cboTipo->Items->Add("Dron Aereo");
			cboTipo->Items->Add("Rover Terrestre");
			cboTipo->SelectedIndex = 0;
			cboTipo->SelectedIndexChanged += gcnew EventHandler(this, &UnidadManagementForm::cboTipo_SelectedIndexChanged);

			lblParametroExtra = gcnew Label();
			lblParametroExtra->Text = "Hélices (4-8):";
			lblParametroExtra->Location = Point(15, 170);
			lblParametroExtra->Size = System::Drawing::Size(100, 20);
			numParametroExtra = gcnew NumericUpDown();
			numParametroExtra->Location = Point(120, 167);
			numParametroExtra->Size = System::Drawing::Size(140, 20);
			numParametroExtra->Minimum = 4;
			numParametroExtra->Maximum = 8;
			numParametroExtra->DecimalPlaces = 0;

			btnRegistrar = gcnew Button();
			btnRegistrar->Text = "Registrar Unidad";
			btnRegistrar->Location = Point(15, 220);
			btnRegistrar->Size = System::Drawing::Size(245, 35);
			btnRegistrar->Click += gcnew EventHandler(this, &UnidadManagementForm::btnRegistrar_Click);

			btnMayorAutonomia = gcnew Button();
			btnMayorAutonomia->Text = "Buscar Máxima Autonomía";
			btnMayorAutonomia->Location = Point(15, 270);
			btnMayorAutonomia->Size = System::Drawing::Size(245, 35);
			btnMayorAutonomia->Click += gcnew EventHandler(this, &UnidadManagementForm::btnMayorAutonomia_Click);

			grpDatos->Controls->Add(lblId);
			grpDatos->Controls->Add(txtId);
			grpDatos->Controls->Add(lblCod);
			grpDatos->Controls->Add(txtCodigo);
			grpDatos->Controls->Add(lblBat);
			grpDatos->Controls->Add(txtBateria);
			grpDatos->Controls->Add(lblTipo);
			grpDatos->Controls->Add(cboTipo);
			grpDatos->Controls->Add(lblParametroExtra);
			grpDatos->Controls->Add(numParametroExtra);
			grpDatos->Controls->Add(btnRegistrar);
			grpDatos->Controls->Add(btnMayorAutonomia);

			// DataGridView de Flota
			dgvFlota = gcnew DataGridView();
			dgvFlota->Location = Point(310, 20);
			dgvFlota->Size = System::Drawing::Size(505, 395);
			dgvFlota->ReadOnly = true;
			dgvFlota->AllowUserToAddRows = false;
			dgvFlota->RowHeadersVisible = false;
			dgvFlota->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			dgvFlota->ColumnCount = 6;
			dgvFlota->Columns[0]->Name = "ID";
			dgvFlota->Columns[0]->Width = 50;
			dgvFlota->Columns[1]->Name = "Código";
			dgvFlota->Columns[1]->Width = 90;
			dgvFlota->Columns[2]->Name = "Tipo";
			dgvFlota->Columns[2]->Width = 85;
			dgvFlota->Columns[3]->Name = "Batería";
			dgvFlota->Columns[3]->Width = 65;
			dgvFlota->Columns[4]->Name = "Autonomía";
			dgvFlota->Columns[4]->Width = 85;
			dgvFlota->Columns[5]->Name = "Especificación";
			dgvFlota->Columns[5]->Width = 110;

			this->Controls->Add(grpDatos);
			this->Controls->Add(dgvFlota);

		}
		void RefrescarGrilla() {
			dgvFlota->Rows->Clear();
			for each (UnidadInspeccion ^ u in UnidadController::ObtenerUnidades()) {
				String^ tipo = "Desconocido";
				String^ extra = "";

				if (DronAereo^ d = dynamic_cast<DronAereo^>(u)) {
					tipo = "Dron";
					extra = d->CantidadHelices + " hélices";
				}
				else if (RoverTerrestre^ r = dynamic_cast<RoverTerrestre^>(u)) {
					tipo = "Rover";
					extra = r->PesoCargaUtilKg.ToString("F1") + " kg carga";
				}

				dgvFlota->Rows->Add(
					u->Id,
					u->CodigoSerie,
					tipo,
					u->BateriaRestante.ToString("F1") + "%",
					u->CalcularAutonomiaHoras().ToString("F2") + " h",
					extra
				);
			}
		}

		void cboTipo_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
			if (cboTipo->Text == "Dron Aéreo") {
				lblParametroExtra->Text = "Hélices (4-8):";
				numParametroExtra->Minimum = 4;
				numParametroExtra->Maximum = 8;
				numParametroExtra->DecimalPlaces = 0;
				numParametroExtra->Value = 4;
			}
			else {
				lblParametroExtra->Text = "Carga LiDAR (kg):";
				numParametroExtra->Minimum = 0;
				numParametroExtra->Maximum = 15;
				numParametroExtra->DecimalPlaces = 1;
				numParametroExtra->Value = 3;
			}
		}

		void btnRegistrar_Click(Object^ sender, EventArgs^ e) {
			try {
				int id = Convert::ToInt32(txtId->Text);
				String^ cod = txtCodigo->Text;
				double bateria = Convert::ToDouble(txtBateria->Text);

				if (String::IsNullOrWhiteSpace(cod))
					throw gcnew ArgumentException("Debe ingresar un código de serie válido.");

				UnidadInspeccion^ nuevaUnidad;

				if (cboTipo->Text == "Dron Aereo") {
					int helices = Convert::ToInt32(numParametroExtra->Value);
					nuevaUnidad = gcnew DronAereo(id, cod, bateria, helices);
				}
				else {
					double peso = Convert::ToDouble(numParametroExtra->Value);
					nuevaUnidad = gcnew RoverTerrestre(id, cod, bateria, peso);
				}

				////// Delegación pura al controlador
				UnidadController::RegistrarUnidad(nuevaUnidad);
				RefrescarGrilla();

				txtId->Clear();
				txtCodigo->Clear();
				txtBateria->Clear();
				MessageBox::Show("Unidad registrada exitosamente y sincronizada en archivo CSV.",
					"GeoTech Telemetría", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, "Validación de Flota",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}

		void btnMayorAutonomia_Click(Object^ sender, EventArgs^ e) {
			try {
				UnidadInspeccion^ mayor = UnidadController::ObtenerUnidadMayorAutonomia();
				if (mayor == nullptr) {
					MessageBox::Show("No hay unidades registradas en la flota.", "Aviso",
						MessageBoxButtons::OK, MessageBoxIcon::Information);
					return;
				}

				String^ info = String::Format(
					"UNIDAD CON MAYOR TIEMPO DE OPERACIÓN:\n\n" +
					"ID: {0}\nCódigo Serie: {1}\nBatería: {2}%\nAutonomía Estimada: {3:F2} horas",
					mayor->Id, mayor->CodigoSerie, mayor->BateriaRestante, mayor->CalcularAutonomiaHoras()
				);

				MessageBox::Show(info, "Máxima Autonomía Polimórfica",
					MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// UnidadManagementForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(671, 406);
			this->Name = L"UnidadManagementForm";
			this->Text = L"UnidadManagementForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
