#pragma once

namespace SimuladorGUIApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace SimuladorController;

	public ref class FormLaberinto : public System::Windows::Forms::Form
	{
	public:
		FormLaberinto(void)
		{
			isGenerationEnabled = false;
			pasoActualVisualizacion = 0;
			InitializeComponent();
			CargarListaMapas();
			SimuladorLaberintoController::CargarDatosDB();

			for (int i = 0; i < SimuladorLaberintoController::idsMapas()->Count; i++) {
				int idMapa = SimuladorLaberintoController::idsMapas()[i];
				this->cboMapasDB->Items->Add(idMapa);
			}
		}

	protected:
		~FormLaberinto()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// Variables de estado
		bool isGenerationEnabled;
		int pasoActualVisualizacion;

		// Controles de Visualización Gráfica y Temporizador
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Timer^ timerPasoPaso;

		// 1. Grupo: Historial y Mantenimiento de BD (CRUD)
		System::Windows::Forms::GroupBox^ grpHistorial;
		System::Windows::Forms::ComboBox^ cboMapasDB;
		System::Windows::Forms::Button^ btnCargarMapa;
		System::Windows::Forms::Button^ btnGuardarNuevo;
		System::Windows::Forms::Button^ btnActualizarPesos;
		System::Windows::Forms::Button^ btnEliminarMapa;

		// 2. Grupo: Configuración y Características del Mapa Actual
		System::Windows::Forms::GroupBox^ grpParametros;
		System::Windows::Forms::Label^ lblFilas;
		System::Windows::Forms::NumericUpDown^ numFilas;
		System::Windows::Forms::Label^ lblColumnas;
		System::Windows::Forms::NumericUpDown^ numColumnas;
		System::Windows::Forms::Label^ lblHeuristica;
		System::Windows::Forms::ComboBox^ cboHeuristica;

		System::Windows::Forms::Label^ lblPesoH;
		System::Windows::Forms::NumericUpDown^ numPesoH;
		System::Windows::Forms::Label^ lblPesoV;
		System::Windows::Forms::NumericUpDown^ numPesoV;
		System::Windows::Forms::Label^ lblPesoD;
		System::Windows::Forms::NumericUpDown^ numPesoD;

		System::Windows::Forms::Label^ lblInicio;
		System::Windows::Forms::TextBox^ txtInicio;
		System::Windows::Forms::Label^ lblFin;
		System::Windows::Forms::TextBox^ txtFin;

		// 3. Grupo: Acciones de Ejecución y Algoritmo A*
		System::Windows::Forms::GroupBox^ grpAcciones;
		System::Windows::Forms::Button^ btnGenerarNuevoMapa;
		System::Windows::Forms::Button^ btnReejecutarAStar;
		System::Windows::Forms::Button^ btnAnimarPasoPaso;

		// 4. Grupo: Grilla de Solución A* Paso por Paso
		System::Windows::Forms::GroupBox^ grpSolucion;
		System::Windows::Forms::DataGridView^ dgvPasosAStar;
		System::Windows::Forms::Label^ lblEstadoSolucion;

		System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timerPasoPaso = (gcnew System::Windows::Forms::Timer(this->components));

			// Instanciación de Contenedores y Controles
			this->grpHistorial = (gcnew System::Windows::Forms::GroupBox());
			this->cboMapasDB = (gcnew System::Windows::Forms::ComboBox());
			this->btnCargarMapa = (gcnew System::Windows::Forms::Button());
			this->btnGuardarNuevo = (gcnew System::Windows::Forms::Button());
			this->btnActualizarPesos = (gcnew System::Windows::Forms::Button());
			this->btnEliminarMapa = (gcnew System::Windows::Forms::Button());

			this->grpParametros = (gcnew System::Windows::Forms::GroupBox());
			this->lblFilas = (gcnew System::Windows::Forms::Label());
			this->numFilas = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblColumnas = (gcnew System::Windows::Forms::Label());
			this->numColumnas = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblHeuristica = (gcnew System::Windows::Forms::Label());
			this->cboHeuristica = (gcnew System::Windows::Forms::ComboBox());
			this->lblPesoH = (gcnew System::Windows::Forms::Label());
			this->numPesoH = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblPesoV = (gcnew System::Windows::Forms::Label());
			this->numPesoV = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblPesoD = (gcnew System::Windows::Forms::Label());
			this->numPesoD = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblInicio = (gcnew System::Windows::Forms::Label());
			this->txtInicio = (gcnew System::Windows::Forms::TextBox());
			this->lblFin = (gcnew System::Windows::Forms::Label());
			this->txtFin = (gcnew System::Windows::Forms::TextBox());

			this->grpAcciones = (gcnew System::Windows::Forms::GroupBox());
			this->btnGenerarNuevoMapa = (gcnew System::Windows::Forms::Button());
			this->btnReejecutarAStar = (gcnew System::Windows::Forms::Button());
			this->btnAnimarPasoPaso = (gcnew System::Windows::Forms::Button());

			this->grpSolucion = (gcnew System::Windows::Forms::GroupBox());
			this->dgvPasosAStar = (gcnew System::Windows::Forms::DataGridView());
			this->lblEstadoSolucion = (gcnew System::Windows::Forms::Label());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->grpHistorial->SuspendLayout();
			this->grpParametros->SuspendLayout();
			this->grpAcciones->SuspendLayout();
			this->grpSolucion->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPasosAStar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFilas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numColumnas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoH))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoV))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoD))->BeginInit();
			this->SuspendLayout();

			// 
			// pictureBox1 (Lienzo del Laberinto)
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(460, 15);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(620, 480);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormLaberinto::laberinto_Paint);

			// 
			// timerPasoPaso
			// 
			this->timerPasoPaso->Interval = 250;
			this->timerPasoPaso->Tick += gcnew System::EventHandler(this, &FormLaberinto::timerPasoPaso_Tick);

			// 
			// GroupBox 1: Historial BD (CRUD)
			// 
			this->grpHistorial->Controls->Add(this->cboMapasDB);
			this->grpHistorial->Controls->Add(this->btnCargarMapa);
			this->grpHistorial->Controls->Add(this->btnGuardarNuevo);
			this->grpHistorial->Controls->Add(this->btnActualizarPesos);
			this->grpHistorial->Controls->Add(this->btnEliminarMapa);
			this->grpHistorial->Location = System::Drawing::Point(12, 12);
			this->grpHistorial->Name = L"grpHistorial";
			this->grpHistorial->Size = System::Drawing::Size(430, 105);
			this->grpHistorial->TabIndex = 1;
			this->grpHistorial->TabStop = false;
			this->grpHistorial->Text = L"Historial de Mapas en Base de Datos (CRUD)";

			this->cboMapasDB->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboMapasDB->FormattingEnabled = true;
			this->cboMapasDB->Location = System::Drawing::Point(15, 24);
			this->cboMapasDB->Size = System::Drawing::Size(290, 21);

			this->btnCargarMapa->Location = System::Drawing::Point(315, 22);
			this->btnCargarMapa->Size = System::Drawing::Size(100, 25);
			this->btnCargarMapa->Text = L"Cargar BD";
			this->btnCargarMapa->Click += gcnew System::EventHandler(this, &FormLaberinto::btnCargarMapa_Click);

			this->btnGuardarNuevo->Location = System::Drawing::Point(15, 60);
			this->btnGuardarNuevo->Size = System::Drawing::Size(95, 28);
			this->btnGuardarNuevo->Text = L"Guardar Nuevo";
			this->btnGuardarNuevo->Click += gcnew System::EventHandler(this, &FormLaberinto::btnGuardarNuevo_Click);

			this->btnActualizarPesos->Location = System::Drawing::Point(118, 60);
			this->btnActualizarPesos->Size = System::Drawing::Size(120, 28);
			this->btnActualizarPesos->Text = L"Actualizar Pesos BD";
			this->btnActualizarPesos->Click += gcnew System::EventHandler(this, &FormLaberinto::btnActualizarPesos_Click);

			this->btnEliminarMapa->ForeColor = System::Drawing::Color::Maroon;
			this->btnEliminarMapa->Location = System::Drawing::Point(246, 60);
			this->btnEliminarMapa->Size = System::Drawing::Size(95, 28);
			this->btnEliminarMapa->Text = L"Eliminar BD";
			this->btnEliminarMapa->Click += gcnew System::EventHandler(this, &FormLaberinto::btnEliminarMapa_Click);

			// 
			// GroupBox 2: Parámetros del Mapa
			// 
			this->grpParametros->Controls->Add(this->lblFilas);
			this->grpParametros->Controls->Add(this->numFilas);
			this->grpParametros->Controls->Add(this->lblColumnas);
			this->grpParametros->Controls->Add(this->numColumnas);
			this->grpParametros->Controls->Add(this->lblHeuristica);
			this->grpParametros->Controls->Add(this->cboHeuristica);
			this->grpParametros->Controls->Add(this->lblPesoH);
			this->grpParametros->Controls->Add(this->numPesoH);
			this->grpParametros->Controls->Add(this->lblPesoV);
			this->grpParametros->Controls->Add(this->numPesoV);
			this->grpParametros->Controls->Add(this->lblPesoD);
			this->grpParametros->Controls->Add(this->numPesoD);
			this->grpParametros->Controls->Add(this->lblInicio);
			this->grpParametros->Controls->Add(this->txtInicio);
			this->grpParametros->Controls->Add(this->lblFin);
			this->grpParametros->Controls->Add(this->txtFin);
			this->grpParametros->Location = System::Drawing::Point(12, 125);
			this->grpParametros->Name = L"grpParametros";
			this->grpParametros->Size = System::Drawing::Size(430, 160);
			this->grpParametros->TabIndex = 2;
			this->grpParametros->TabStop = false;
			this->grpParametros->Text = L"Caracteristicas y Pesos Operativos";

			// Filas y Columnas
			this->lblFilas->Location = System::Drawing::Point(15, 25);
			this->lblFilas->Size = System::Drawing::Size(40, 20);
			this->lblFilas->Text = L"Filas:";
			this->numFilas->Location = System::Drawing::Point(60, 22);
			this->numFilas->Size = System::Drawing::Size(50, 20);
			this->numFilas->Minimum = 5;
			this->numFilas->Maximum = 50;
			this->numFilas->Value = 15;

			this->lblColumnas->Location = System::Drawing::Point(125, 25);
			this->lblColumnas->Size = System::Drawing::Size(40, 20);
			this->lblColumnas->Text = L"Cols:";
			this->numColumnas->Location = System::Drawing::Point(165, 22);
			this->numColumnas->Size = System::Drawing::Size(50, 20);
			this->numColumnas->Minimum = 5;
			this->numColumnas->Maximum = 50;
			this->numColumnas->Value = 15;

			this->lblHeuristica->Location = System::Drawing::Point(230, 25);
			this->lblHeuristica->Size = System::Drawing::Size(65, 20);
			this->lblHeuristica->Text = L"Heuristica:";
			this->cboHeuristica->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboHeuristica->Items->AddRange(gcnew array<Object^> { "manhattan", "euclidiana", "chebyshev" });
			this->cboHeuristica->SelectedIndex = 0;
			this->cboHeuristica->Location = System::Drawing::Point(295, 22);
			this->cboHeuristica->Size = System::Drawing::Size(120, 21);

			// Pesos
			this->lblPesoH->Location = System::Drawing::Point(15, 60);
			this->lblPesoH->Size = System::Drawing::Size(80, 20);
			this->lblPesoH->Text = L"Peso Horiz:";
			this->numPesoH->Location = System::Drawing::Point(95, 58);
			this->numPesoH->Size = System::Drawing::Size(45, 20);
			this->numPesoH->Value = 10;

			this->lblPesoV->Location = System::Drawing::Point(150, 60);
			this->lblPesoV->Size = System::Drawing::Size(80, 20);
			this->lblPesoV->Text = L"Peso Vert:";
			this->numPesoV->Location = System::Drawing::Point(230, 58);
			this->numPesoV->Size = System::Drawing::Size(45, 20);
			this->numPesoV->Value = 10;

			this->lblPesoD->Location = System::Drawing::Point(285, 60);
			this->lblPesoD->Size = System::Drawing::Size(85, 20);
			this->lblPesoD->Text = L"Peso Diag:";
			this->numPesoD->Location = System::Drawing::Point(370, 58);
			this->numPesoD->Size = System::Drawing::Size(45, 20);
			this->numPesoD->Value = 14;

			// Coordenadas Inicio y Fin (Read-Only)
			this->lblInicio->Location = System::Drawing::Point(15, 105);
			this->lblInicio->Size = System::Drawing::Size(80, 20);
			this->lblInicio->Text = L"Inicio [F, C]:";
			this->txtInicio->ReadOnly = true;
			this->txtInicio->Location = System::Drawing::Point(95, 102);
			this->txtInicio->Size = System::Drawing::Size(80, 20);

			this->lblFin->Location = System::Drawing::Point(225, 105);
			this->lblFin->Size = System::Drawing::Size(70, 20);
			this->lblFin->Text = L"Fin [F, C]:";
			this->txtFin->ReadOnly = true;
			this->txtFin->Location = System::Drawing::Point(295, 102);
			this->txtFin->Size = System::Drawing::Size(80, 20);

			// 
			// GroupBox 3: Acciones
			// 
			this->grpAcciones->Controls->Add(this->btnGenerarNuevoMapa);
			this->grpAcciones->Controls->Add(this->btnReejecutarAStar);
			this->grpAcciones->Controls->Add(this->btnAnimarPasoPaso);
			this->grpAcciones->Location = System::Drawing::Point(12, 295);
			this->grpAcciones->Name = L"grpAcciones";
			this->grpAcciones->Size = System::Drawing::Size(430, 75);
			this->grpAcciones->TabIndex = 3;
			this->grpAcciones->TabStop = false;
			this->grpAcciones->Text = L"Acciones de Navegacion";

			this->btnGenerarNuevoMapa->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold);
			this->btnGenerarNuevoMapa->Location = System::Drawing::Point(15, 25);
			this->btnGenerarNuevoMapa->Size = System::Drawing::Size(125, 36);
			this->btnGenerarNuevoMapa->Text = L"Generar Nuevo";
			this->btnGenerarNuevoMapa->Click += gcnew System::EventHandler(this, &FormLaberinto::btnGenerarNuevoMapa_Click);

			this->btnReejecutarAStar->Location = System::Drawing::Point(150, 25);
			this->btnReejecutarAStar->Size = System::Drawing::Size(125, 36);
			this->btnReejecutarAStar->Text = L"Recalcular A*";
			this->btnReejecutarAStar->Click += gcnew System::EventHandler(this, &FormLaberinto::btnReejecutarAStar_Click);

			this->btnAnimarPasoPaso->Location = System::Drawing::Point(285, 25);
			this->btnAnimarPasoPaso->Size = System::Drawing::Size(130, 36);
			this->btnAnimarPasoPaso->Text = L"Ver Paso a Paso";
			this->btnAnimarPasoPaso->Click += gcnew System::EventHandler(this, &FormLaberinto::btnAnimarPasoPaso_Click);

			// 
			// GroupBox 4: Traza A* Paso por Paso (DataGridView)
			// 
			this->grpSolucion->Controls->Add(this->dgvPasosAStar);
			this->grpSolucion->Controls->Add(this->lblEstadoSolucion);
			this->grpSolucion->Location = System::Drawing::Point(12, 380);
			this->grpSolucion->Name = L"grpSolucion";
			this->grpSolucion->Size = System::Drawing::Size(430, 380);
			this->grpSolucion->TabIndex = 4;
			this->grpSolucion->TabStop = false;
			this->grpSolucion->Text = L"Desglose de Ruta y Costes A*";

			this->lblEstadoSolucion->Font = gcnew System::Drawing::Font("Consolas", 8.25F, System::Drawing::FontStyle::Bold);
			this->lblEstadoSolucion->ForeColor = System::Drawing::Color::Navy;
			this->lblEstadoSolucion->Location = System::Drawing::Point(15, 22);
			this->lblEstadoSolucion->Size = System::Drawing::Size(400, 20);
			this->lblEstadoSolucion->Text = L"Estado: Sin resolver";

			this->dgvPasosAStar->Location = System::Drawing::Point(15, 50);
			this->dgvPasosAStar->Size = System::Drawing::Size(400, 315);
			this->dgvPasosAStar->ReadOnly = true;
			this->dgvPasosAStar->AllowUserToAddRows = false;
			this->dgvPasosAStar->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvPasosAStar->ColumnCount = 5;
			this->dgvPasosAStar->Columns[0]->Name = L"Paso";
			this->dgvPasosAStar->Columns[0]->Width = 50;
			this->dgvPasosAStar->Columns[1]->Name = L"Celda [F,C]";
			this->dgvPasosAStar->Columns[1]->Width = 85;
			this->dgvPasosAStar->Columns[2]->Name = L"Coste G";
			this->dgvPasosAStar->Columns[2]->Width = 80;
			this->dgvPasosAStar->Columns[3]->Name = L"Heuristica H";
			this->dgvPasosAStar->Columns[3]->Width = 85;
			this->dgvPasosAStar->Columns[4]->Name = L"F Total";
			this->dgvPasosAStar->Columns[4]->Width = 80;
			this->dgvPasosAStar->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &FormLaberinto::dgvPasosAStar_CellClick);

			// 
			// FormLaberinto
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1100, 780);
			this->Controls->Add(this->grpHistorial);
			this->Controls->Add(this->grpParametros);
			this->Controls->Add(this->grpAcciones);
			this->Controls->Add(this->grpSolucion);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"FormLaberinto";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Simulador de Navegacion A* y Gestion Relacional de Mapas";

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->grpHistorial->ResumeLayout(false);
			this->grpParametros->ResumeLayout(false);
			this->grpParametros->PerformLayout();
			this->grpAcciones->ResumeLayout(false);
			this->grpSolucion->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPasosAStar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFilas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numColumnas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoH))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoV))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPesoD))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion

		// =========================================================================
		// MÉTODOS DE INTEGRACIÓN Y EVENTOS
		// =========================================================================

	private:
		// Actualiza los controles del formulario según el estado del mapa actual
		void SincronizarCamposConModelo()
		{
			// Ejemplo de lectura desde el controlador:
			// this->txtInicio->Text = String::Format("[{0}, {1}]", SimuladorLaberintoController::InicioFila, SimuladorLaberintoController::InicioColumna);
			// this->txtFin->Text = String::Format("[{0}, {1}]", SimuladorLaberintoController::FinFila, SimuladorLaberintoController::FinColumna);
		}

		// Poblado del ComboBox de mapas existentes en BD
		void CargarListaMapas()
		{
			//try {
			//	this->cboMapasDB->Items->Clear();
			//	DataTable^ dt = SimuladorLaberintoController::ListarMapasResumen();
			//	for each(DataRow ^ row in dt->Rows) {
			//		String^ item = String::Format("ID: {0} | {1}x{2} | {3} | {4:yyyy-MM-dd HH:mm}",
			//			row["IdMapa"], row["TotalFilas"], row["TotalColumnas"],
			//			row["TipoDistancia"], row["FechaCreacion"]);
			//		this->cboMapasDB->Items->Add(item);
			//	}
			//	if (this->cboMapasDB->Items->Count > 0)
			//		this->cboMapasDB->SelectedIndex = 0;
			//}
			//catch (Exception^ ex) {
			//	// Manejo en caso la BD aún no esté conectada o vacía
			//}
		}

		// Volcar los pasos del camino A* al DataGridView
		void CargarTablaSolucion()
		{
			//this->dgvPasosAStar->Rows->Clear();
			//DataTable^ dt = SimuladorLaberintoController::ObtenerPasosSolucion();

			//if (dt != nullptr && dt->Rows->Count > 0) {
			//	this->lblEstadoSolucion->Text = String::Format("Solución encontrada: {0} pasos", dt->Rows->Count);
			//	for each(DataRow ^ r in dt->Rows) {
			//		double g = Convert::ToDouble(r["CosteG"]);
			//		double h = Convert::ToDouble(r["CosteH"]);
			//		double f = g + h;
			//		this->dgvPasosAStar->Rows->Add(
			//			r["Secuencia"],
			//			String::Format("[{0}, {1}]", r["Fila"], r["Columna"]),
			//			g.ToString("F2"),
			//			h.ToString("F2"),
			//			f.ToString("F2")
			//		);
			//	}
			//}
			//else {
			//	this->lblEstadoSolucion->Text = L"Estado: Sin ruta alcanzable";
			//}
		}

		// Evento Paint del PictureBox
		System::Void laberinto_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{
			if (!this->isGenerationEnabled) {
				//e->Graphics->Clear(Color::FromArgb(35, 39, 46));
				//SolidBrush^ brushTxt = gcnew SolidBrush(Color::White);
				//e->Graphics->DrawString(L"Presione 'Generar Nuevo' o 'Cargar BD' para iniciar.",
				//	gcnew System::Drawing::Font("Arial", 10), brushTxt, 80.0f, 220.0f);
				return;
			}

			// Renderiza el laberinto, puntos A/B y el camino (o el tramo animado)
			SimuladorLaberintoController::Renderizar(e->Graphics);
			//SimuladorLaberintoController::Renderizar(e->Graphics, this->pictureBox1->Width, this->pictureBox1->Height, this->pasoActualVisualizacion);
		}

		// 1. Generar nuevo mapa aleatorio con características seleccionadas
		System::Void btnGenerarNuevoMapa_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//this->timerPasoPaso->Stop();
			
			int filas = Convert::ToInt32(this->numFilas->Value);
			int cols = Convert::ToInt32(this->numColumnas->Value);
			String^ heuristica = this->cboHeuristica->SelectedItem->ToString();

			int wH = Convert::ToInt32(this->numPesoH->Value);
			int wV = Convert::ToInt32(this->numPesoV->Value);
			int wD = Convert::ToInt32(this->numPesoD->Value);

			SimuladorLaberintoController::GenerarNuevoMapa(filas, cols, heuristica, wH, wV, wD, this->pictureBox1->Width, this->pictureBox1->Height);
			Point inicio = SimuladorLaberintoController::ObetenerLaberinto()->PuntoInicio;
			Point llegada = SimuladorLaberintoController::ObetenerLaberinto()->PuntoLlegada;

			this->txtInicio->Text = String::Format("[{0}, {1}]", inicio.X, inicio.Y);
			this->txtFin->Text = String::Format("[{0}, {1}]", llegada.X, llegada.Y);

			this->isGenerationEnabled = true;
			//this->pasoActualVisualizacion = -1; // -1 indica dibujar la ruta completa
			//SincronizarCamposConModelo();
			//CargarTablaSolucion();
			this->pictureBox1->Invalidate();
		}

		// 2. Volver a correr A* (recalcula si se modificaron los pesos o heurística sin destruir el laberinto)
		System::Void btnReejecutarAStar_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//if (!this->isGenerationEnabled) return;

			//this->timerPasoPaso->Stop();
			//String^ heuristica = this->cboHeuristica->SelectedItem->ToString();
			//int wH = Convert::ToInt32(this->numPesoH->Value);
			//int wV = Convert::ToInt32(this->numPesoV->Value);
			//int wD = Convert::ToInt32(this->numPesoD->Value);

			//SimuladorLaberintoController::RecalcularAStar(heuristica, wH, wV, wD);

			//this->pasoActualVisualizacion = -1;
			//CargarTablaSolucion();
			//this->pictureBox1->Invalidate();
		}

		// 3. Modificar/Actualizar únicamente los pesos del mapa actual en la BD
		System::Void btnActualizarPesos_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//try {
			//	int idMapa = SimuladorLaberintoController::IdMapaActual;
			//	if (idMapa <= 0) {
			//		MessageBox::Show(L"El mapa en visualización aún no existe en BD o no ha sido guardado.",
			//			L"Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			//		return;
			//	}

			//	String^ heuristica = this->cboHeuristica->SelectedItem->ToString();
			//	int wH = Convert::ToInt32(this->numPesoH->Value);
			//	int wV = Convert::ToInt32(this->numPesoV->Value);
			//	int wD = Convert::ToInt32(this->numPesoD->Value);

			//	SimuladorLaberintoController::ActualizarPesosMapaDB(idMapa, heuristica, wH, wV, wD);
			//	MessageBox::Show(L"Pesos y heurística actualizados con éxito en SQL Server.",
			//		L"Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			//	CargarListaMapas();
			//}
			//catch (Exception^ ex) {
			//	MessageBox::Show(ex->Message, L"Error al actualizar pesos", MessageBoxButtons::OK, MessageBoxIcon::Error);
			//}
		}

		// 4. Guardar el mapa actual y su solución como un nuevo registro en BD
		System::Void btnGuardarNuevo_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!this->isGenerationEnabled) return;

			try {
				int nuevoId = SimuladorLaberintoController::GuardarMapaActualEnDB();
			//	MessageBox::Show(String::Format("Mapa guardado exitosamente con ID: {0}", nuevoId),
			//		L"Persistencia", MessageBoxButtons::OK, MessageBoxIcon::Information);
			//	CargarListaMapas();
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, L"Error al persistir", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		// 5. Cargar un mapa histórico desde BD
		System::Void btnCargarMapa_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//if (this->cboMapasDB->SelectedIndex < 0) return;

			//try {
			//	this->timerPasoPaso->Stop();
			//	String^ textoSeleccionado = this->cboMapasDB->SelectedItem->ToString();
			//	// Extrae el ID del formato "ID: X | ..."
			//	int idMapa = Convert::ToInt32(textoSeleccionado->Split('|')[0]->Replace("ID:", "")->Trim());

			//	SimuladorLaberintoController::CargarMapaDesdeDB(idMapa);

			//	// Actualiza controles de la vista con la metadata leída
			//	this->numFilas->Value = SimuladorLaberintoController::TotalFilas;
			//	this->numColumnas->Value = SimuladorLaberintoController::TotalColumnas;
			//	this->cboHeuristica->SelectedItem = SimuladorLaberintoController::TipoDistancia;
			//	this->numPesoH->Value = SimuladorLaberintoController::PesoH;
			//	this->numPesoV->Value = SimuladorLaberintoController::PesoV;
			//	this->numPesoD->Value = SimuladorLaberintoController::PesoD;

			//	this->isGenerationEnabled = true;
			//	this->pasoActualVisualizacion = -1;
			//	SincronizarCamposConModelo();
			//	CargarTablaSolucion();
			//	this->pictureBox1->Invalidate();
			//}
			//catch (Exception^ ex) {
			//	MessageBox::Show(ex->Message, L"Error al cargar mapa", MessageBoxButtons::OK, MessageBoxIcon::Error);
			//}
		}

		// 6. Eliminar el mapa seleccionado en BD
		System::Void btnEliminarMapa_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//if (this->cboMapasDB->SelectedIndex < 0) return;

			//if (MessageBox::Show(L"¿Está seguro de eliminar este mapa de la base de datos?",
			//	L"Confirmar Eliminación", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			//	try {
			//		String^ texto = this->cboMapasDB->SelectedItem->ToString();
			//		int idMapa = Convert::ToInt32(texto->Split('|')[0]->Replace("ID:", "")->Trim());

			//		SimuladorLaberintoController::EliminarMapaDB(idMapa);
			//		CargarListaMapas();
			//		MessageBox::Show(L"Mapa eliminado de la base de datos.", L"Operación exitosa", MessageBoxButtons::OK, MessageBoxIcon::Information);
			//	}
			//	catch (Exception^ ex) {
			//		MessageBox::Show(ex->Message, L"Error al eliminar", MessageBoxButtons::OK, MessageBoxIcon::Error);
			//	}
			//}
		}

		// 7. Visualización animada paso a paso
		System::Void btnAnimarPasoPaso_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->dgvPasosAStar->Rows->Count == 0) return;

			this->pasoActualVisualizacion = 0;
			this->timerPasoPaso->Start();
		}

		System::Void timerPasoPaso_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->pasoActualVisualizacion < this->dgvPasosAStar->Rows->Count) {
				this->dgvPasosAStar->ClearSelection();
				this->dgvPasosAStar->Rows[this->pasoActualVisualizacion]->Selected = true;
				this->dgvPasosAStar->FirstDisplayedScrollingRowIndex = this->pasoActualVisualizacion;

				this->pasoActualVisualizacion++;
				this->pictureBox1->Invalidate();
			}
			else {
				this->timerPasoPaso->Stop();
			}
		}

		// Sincronizar selección de la tabla con el lienzo
		System::Void dgvPasosAStar_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
		{
			if (e->RowIndex >= 0) {
				this->timerPasoPaso->Stop();
				this->pasoActualVisualizacion = e->RowIndex + 1;
				this->pictureBox1->Invalidate();
			}
		}
	};
}