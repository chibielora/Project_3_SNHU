/* Elorha Newcomb
16 October 2021
Southern New Hampshire University
CS210 - Project 3
Instructor Ethan Rondeau */

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void printHistogram() {
	/* Open frequency.dat */
	ifstream fin("frequency.dat");
	string item;
	int count;
	/* Read line by line, and print results */
	fin >> item >> count;
	while (!fin.eof()) {
		cout << item << " ";
		for (int i = 0; i < count; i++) {
			cout << "*";
		}
		cout << endl;
		fin >> item >> count;
	}
	
}

/* Functions interacting with python file */
void displayMenu() {
	cout << "**************************************************" << endl;
	cout << "*************   M A I N   M E N U   **************" << endl;
	cout << "**************************************************" << endl;
	cout << "***                                            ***" << endl;
	cout << "***        1. Total Purchase Quantity          ***" << endl;
	cout << "***        2. Single Item Amount Purchased     ***" << endl;
	cout << "***        3. Print Histogram                  ***" << endl;
	cout << "***        4. Exit                             ***" << endl;
	cout << "***                                            ***" << endl;
	cout << "**************************************************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

int getUserInt(int min, int max) {
	int input;
	cin >> input;
	// Handles errors in case input isn't valid
	while (!cin || isdigit(input) != false || input < min || input > max) {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "Retry with a valid number: ";
		cin >> input;
	}
	return input;
}

string getUserString() {
	string input;
	cin >> input;

	while (!cin) {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "Please input a valid answer: ";
		cin >> input;
	}
	return input;
}

// Validates input for y/n prompts
bool getUserConfirmation() {
	char input;
	cin >> input;
	input = tolower(input);
	while (input != 'y' && input != 'n') {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "Please input 'y' or 'n': ";
		cin >> input;
		input = tolower(input);
	}
	return input == 'y';
}

void userInput() {
	string item;
	int input = getUserInt(1, 4);

	// Iterates through menu options
	switch (input) {
	case 1:
		CallProcedure("get_frequency_all");
		break;
	case 2:
		cout << "Enter Product Name: " << endl;
		item = getUserString();
		cout << callIntFunc("get_frequency_one", item) << endl;
		break;
	case 3:
		CallProcedure("write_dictionary_to_file");
		printHistogram();
		break;
	case 4:
		cout << "Program report has ended." << endl;
		exit(0);
	}
}

int main()
{
	bool cont;
	// Loop to go through Menu Options again after reports are done
	do {
		// Clears graphic dumps from screen
		system("CLS");
		displayMenu();
		userInput();

		cout << "Would you like to redo reports? (y/n) ";
		cont = getUserConfirmation();
		cout << endl;
	} while (cont);
	
	return 0;
}