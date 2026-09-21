#pragma once

namespace View {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Controller;
	using namespace Model;
	/// <summary>
	/// Summary for robots
	/// </summary>
	public ref class robots : public System::Windows::Forms::Form
	{
	public:
		robots(void)
		{
			InitializeComponent();

			::Controller::Controller::robots = gcnew List<robot^>();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~robots()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ speed;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ state;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;



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
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->speed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->state = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(71, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Nombre:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(126, 42);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(78, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(253, 37);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(87, 24);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Crear";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &robots::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(126, 105);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(78, 20);
			this->textBox2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(71, 112);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(43, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Estado:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(126, 68);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(78, 20);
			this->textBox3->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(71, 75);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Velocidad:";
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->id, this->name,
					this->speed, this->state
			});
			this->dataGridView1->Location = System::Drawing::Point(33, 156);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(437, 118);
			this->dataGridView1->TabIndex = 6;
			this->dataGridView1->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &robots::dataGridView1_CellClick);
			// 
			// id
			// 
			this->id->HeaderText = L"id";
			this->id->Name = L"id";
			// 
			// name
			// 
			this->name->HeaderText = L"nombre";
			this->name->Name = L"name";
			// 
			// speed
			// 
			this->speed->HeaderText = L"velocidad";
			this->speed->Name = L"speed";
			// 
			// state
			// 
			this->state->HeaderText = L"Estado";
			this->state->Name = L"state";
			// 
			// textBox4
			// 
			this->textBox4->CausesValidation = false;
			this->textBox4->Enabled = false;
			this->textBox4->Location = System::Drawing::Point(126, 16);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 7;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(256, 72);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(83, 24);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Actualizar";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &robots::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(257, 102);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(83, 24);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Eliminar";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &robots::button3_Click);
			// 
			// robots
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(482, 422);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"robots";
			this->Text = L"robots";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nombre = textBox1->Text;
		String^ velocidad = textBox3->Text;
		String^ estado = textBox2->Text;
		int new_robot_id = ::Controller::Controller::add_robot(nombre, estado, velocidad);

		robot^ new_robot = ::Controller::Controller::read_robot(new_robot_id);
		if (new_robot != nullptr) {
			dataGridView1->Rows->Add(new_robot->id, new_robot->name, new_robot->speed, new_robot->state);
		}
	}


	private: System::Void dataGridView1_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		textBox1->Text = dataGridView1->Rows[e->RowIndex]->Cells[1]->Value->ToString();
		textBox2->Text = dataGridView1->Rows[e->RowIndex]->Cells[3]->Value->ToString();
		textBox3->Text = dataGridView1->Rows[e->RowIndex]->Cells[2]->Value->ToString();
		textBox4->Text = dataGridView1->Rows[e->RowIndex]->Cells[0]->Value->ToString();

	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (textBox4->Text == "") {
		MessageBox::Show("Seleccione un robot para actualizar");
		return;
	}
	int id = Int32::Parse(textBox4->Text);
	String^ name = textBox1->Text;
	String^ state = textBox2->Text;
	String^ speed = textBox3->Text;
	::Controller::Controller::update_robot(id, name, state, speed);

	DataGridViewRow^ row = dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex];
	row->Cells[1]->Value = name;
	row->Cells[2]->Value = speed;
	row->Cells[3]->Value = state;

	textBox4->Text = "";
	textBox1->Text = "";
	textBox2->Text = "";
	textBox3->Text = "";
	
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (textBox4->Text == "") {
		MessageBox::Show("Seleccione un robot para eliminar");
		return;
	}
	int id = Int32::Parse(textBox4->Text);
	::Controller::Controller::delete_robot(id);
	dataGridView1->Rows->RemoveAt(dataGridView1->CurrentCell->RowIndex);
	textBox4->Text = "";
	textBox1->Text = "";	
	textBox2->Text = "";
	textBox3->Text = "";

}
};
}
