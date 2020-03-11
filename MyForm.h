#pragma once

#include "Filters.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <msclr\marshal_cppstd.h>
#include <string>

namespace Final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	using applyFilter = std::function<void()>;
	using applyFilterType = applyFilter(*)();
	using MyMap = std::map<std::string, /*applyFilterType*/void(*)()>;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyMap *filters;
		MyForm(void)
		{
			InitializeComponent();
			filters = new MyMap{
			  { "Eroding", &showWebCamVid<doEroding> },
			  /* {"Brightness and contrast",&showWebCamVid<do> },*/
			   { "HistogramEqualization",&showWebCamVid<doHistogramEqual> },
			   { "HomogenousBlur",&showWebCamVid<doHomogenBlur> },
			   { "GaussianBlur",&showWebCamVid<doGaussianBlur> },
			   { "MedianBlur",&showWebCamVid<doMedianBlur> },
			   { "Dilating",&showWebCamVid<doDilating> },
			   { "Negative",&showWebCamVid<doNegative> },
			   { "CannyEdges",&showWebCamVid<doCannyEdgeDetection> },
			   { "Contouring",&showWebCamVid<doContours> }
			};
			// filters->emplace("Eroding", &el);
			array<String^>^ arr = { "HistogramEqualization", "HomogenousBlur", "GaussianBlur", "MedianBlur",
			  "Eroding", "Dilating", "Negative", "CannyEdges", "Contouring" }; //"Brightness and contrast",
			comboBox1->Items->AddRange(arr);

		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

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
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(21, 104);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(140, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(177, 104);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(65, 21);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Submit";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(21, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(96, 74);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Launch";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(146, 13);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(96, 74);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Finish";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(269, 152);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ comboBoxText = comboBox1->Text;
		interrupted = false;
		std::string filterName = msclr::interop::marshal_as<std::string>(comboBoxText);
		auto element = filters->find(filterName);

		if (element != filters->end())
		{
			element->second();
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		interrupted = false;
		showWebCamVid<doNothing>();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		interrupted = true;
	}
	};
}


//	public ref class MyForm : public System::Windows::Forms::Form
//	{
//	public:
//		MyForm(void)
//		{
//			InitializeComponent();
//			//
//			//TODO: добавьте код конструктора
//			//
//		}
//
//	protected:
//		/// <summary>
//		/// ќсвободить все используемые ресурсы.
//		/// </summary>
//		~MyForm()
//		{
//			if (components)
//			{
//				delete components;
//			}
//		}
//	private: System::Windows::Forms::ComboBox^  comboBox1;
//	protected:
//	private: System::Windows::Forms::Button^  button1;
//	private: System::Windows::Forms::Button^  button2;
//	private: System::Windows::Forms::Button^  button3;
//
//	private:
//		/// <summary>
//		/// ќб€зательна€ переменна€ конструктора.
//		/// </summary>
//		System::ComponentModel::Container ^components;
//
//#pragma region Windows Form Designer generated code
//		/// <summary>
//		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
//		/// содержимое этого метода с помощью редактора кода.
//		/// </summary>
//		void InitializeComponent(void)
//		{
//			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
//			this->button1 = (gcnew System::Windows::Forms::Button());
//			this->button2 = (gcnew System::Windows::Forms::Button());
//			this->button3 = (gcnew System::Windows::Forms::Button());
//			this->SuspendLayout();
//			// 
//			// comboBox1
//			// 
//			this->comboBox1->FormattingEnabled = true;
//			this->comboBox1->Location = System::Drawing::Point(133, 229);
//			this->comboBox1->Name = L"comboBox1";
//			this->comboBox1->Size = System::Drawing::Size(191, 28);
//			this->comboBox1->TabIndex = 0;
//			// 
//			// button1
//			// 
//			this->button1->Location = System::Drawing::Point(92, 84);
//			this->button1->Name = L"button1";
//			this->button1->Size = System::Drawing::Size(75, 45);
//			this->button1->TabIndex = 1;
//			this->button1->Text = L"button1";
//			this->button1->UseVisualStyleBackColor = true;
//			// 
//			// button2
//			// 
//			this->button2->Location = System::Drawing::Point(237, 84);
//			this->button2->Name = L"button2";
//			this->button2->Size = System::Drawing::Size(75, 45);
//			this->button2->TabIndex = 2;
//			this->button2->Text = L"button2";
//			this->button2->UseVisualStyleBackColor = true;
//			// 
//			// button3
//			// 
//			this->button3->Location = System::Drawing::Point(412, 84);
//			this->button3->Name = L"button3";
//			this->button3->Size = System::Drawing::Size(75, 45);
//			this->button3->TabIndex = 3;
//			this->button3->Text = L"button3";
//			this->button3->UseVisualStyleBackColor = true;
//			// 
//			// MyForm
//			// 
//			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
//			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
//			this->ClientSize = System::Drawing::Size(981, 573);
//			this->Controls->Add(this->button3);
//			this->Controls->Add(this->button2);
//			this->Controls->Add(this->button1);
//			this->Controls->Add(this->comboBox1);
//			this->Name = L"MyForm";
//			this->Text = L"MyForm";
//			this->ResumeLayout(false);
//
//		}
//#pragma endregion
//	};
//}
