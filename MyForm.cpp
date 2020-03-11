#include "MyForm.h"
//#include "Filters.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

int main(array<String^>^ args)
{
	//FreeConsole();
	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, 0);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Final::MyForm form;
	Application::Run(%form);
	return 0;
}