#pragma once
#include <cstdlib>
#include <ctime>

namespace HollandFlag {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
		int amountOfElements = 9; // tha default amount of squares in line
		array<Panel^>^ panels = gcnew array<System::Windows::Forms::Panel^>(amountOfElements * 3);//array of rectangles
		System::Windows::Forms::Panel^ clickedOne;
		System::Windows::Forms::Panel^ clickedTwo;
		bool initialisation;
		bool readyToSwap;
		int reds;
		int blues;
		int whites;
		int counter = 0;
		
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::TextBox^  textBox1;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Button^  button2;

			 int genRandInt(int min, int max)//function for random colors
			 {
				 return min + (rand() % static_cast<int>(max - min + 1));
			 }
			 void loadPanels()//loading panels on the screen
			 {
				 if (!initialisation && textBox1->Text != "")
				 {
					 try
					 {
						 amountOfElements = int::Parse(textBox1->Text);
					 }
					 catch (...)
					 {
						 MessageBox::Show(textBox1->Text + " is not int.");
						 return;
					 }
					 if (amountOfElements > 10)//the amount of squares can't be more than 10
					 {
						 MessageBox::Show("The max amount of squares is 10.");
						 amountOfElements = 10;
					 }
					 else if (amountOfElements < 2)
					 {
						 MessageBox::Show("The min amount is 2.");
						 amountOfElements = 2;
					 }
					 for (int i = 0; i < panels->Length; ++i)
					 {
						 this->Controls->Remove(panels[i]);
					 }
					 panels = gcnew array<System::Windows::Forms::Panel^>(amountOfElements * 3);
					 initialisation = true;
				 }
				 
				 reds = 0;
				 blues = 0;
				 whites = 0;
				 for (int i = 0, a = 0, b = 0, c = 0; i < panels->Length; ++i)
				 {
					 if (initialisation)
					 {
						 panels[i] = (gcnew System::Windows::Forms::Panel());
					 }
					 bool colorIsSet = false;
					 while (!colorIsSet)//checking the amount of elements of each color and drawing them
					 {
						 int newColor = genRandInt(0, 2);  
						 if (newColor == 0 && reds < amountOfElements)
						 {
							 panels[i]->BackColor = System::Drawing::Color::Red;
							 reds++;
							 colorIsSet = true;
						 }
						 else if (newColor == 1 && blues < amountOfElements)
						 {
							 panels[i]->BackColor = System::Drawing::Color::Blue;
							 blues++;
							 colorIsSet = true;
						 }
						 else if (newColor == 2 && whites < amountOfElements)
						 {
							 panels[i]->BackColor = System::Drawing::Color::White;
							 whites++;
							 colorIsSet = true;
						 }
					 }
					 if (initialisation)
					 {
						 panels[i]->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
						 if (i < panels->Length / 3)
						 {
							 panels[i]->Location = System::Drawing::Point(50 * (a + 1), 20);
							 a++;
						 }
						 else if (i < 2 * panels->Length / 3)
						 {
							 panels[i]->Location = System::Drawing::Point(50 * (b + 1), 70);
							 b++;
						 }
						 else
						 {
							 panels[i]->Location = System::Drawing::Point(50 * (c + 1), 120);
							 c++;
						 }
						 panels[i]->Size = System::Drawing::Size(40, 40);
						 panels[i]->Click += gcnew System::EventHandler(this, &MainForm::panelClick);
						
						 this->Controls->Add(panels[i]);
					 }
				 }
				 if (initialisation)
				 {
					 initialisation = false;
				 }
			 }
	public:
		MainForm(void)
		{
			srand(time(0));
			readyToSwap = false;
			initialisation = true;
			loadPanels();
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;
		//creating buttons and textbox
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)//initialization of the buttons and textboxes
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			this->button1->Location = System::Drawing::Point(531, 396);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Reset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
 
			// button2
			this->button2->Location = System::Drawing::Point(450, 396);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Rules";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
 
			// textBox1
			this->textBox1->Location = System::Drawing::Point(344, 398);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"9";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(250, 398);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 30);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Clicks: "+ counter;
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);

			// MainForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(629, 445);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panelClick(System::Object^  sender, System::EventArgs^  e) {

		if (!readyToSwap)//choosing tha first rectangle
		{
			
			this->clickedOne = safe_cast<System::Windows::Forms::Panel^>(sender);
			readyToSwap = true;
		}
		else
		{

			this->clickedTwo = safe_cast<System::Windows::Forms::Panel^>(sender);//chosing the second rectangle and changing colors
			auto tempColor = this->clickedOne->BackColor;
			
			this->clickedOne->BackColor = this->clickedTwo->BackColor;
			this->clickedTwo->BackColor = tempColor;
			counter++;
			this->label1->Text = L"Clicks: " + counter;
			readyToSwap = false;

			bool firstRowSameColor = true;
			bool secondRowSameColor = true;
			bool thirdRowSameColor = true;
			for (int i = 0; i < (panels->Length / 3 - 1); ++i)//checking if the all three rows are with right color squares
			{
				if (panels[i]->BackColor != panels[i + 1]->BackColor || panels[i]->BackColor != System::Drawing::Color::Red)
				{
					firstRowSameColor = false;
					return;
				}
			}
			for (int i = panels->Length / 3; i < 2 * (panels->Length / 3) - 1; ++i)
			{
				if (panels[i]->BackColor != panels[i + 1]->BackColor || panels[i]->BackColor != System::Drawing::Color::White)
				{
					secondRowSameColor = false;
					return;
				}
			}
			for (int i = 2 * (panels->Length / 3); i < (panels->Length - 1); ++i)
			{
				if (panels[i]->BackColor != panels[i + 1]->BackColor || panels[i]->BackColor != System::Drawing::Color::Blue)
				{
					thirdRowSameColor = false;
					return;
				}
			}
			if (firstRowSameColor && secondRowSameColor && thirdRowSameColor&&counter < 3*(amountOfElements - 1))//the condition of the victory
			{
				MessageBox::Show("You win!");
			}
			else
			{
				MessageBox::Show("Game over. You have to many swaps");
			}
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		readyToSwap = false;
		counter = 0;
		this->label1->Text = L"Clicks: " + counter;
		loadPanels();
	}
	private: System::Void panelPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show("Click on two rectangles to swap them.\nFirst row must consist of red rectangles, second - of white, third - of blue.\nIf you wanna change the complexity of the level from 2 to 10 - enter the right number in the box and press Reset");
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

};

}