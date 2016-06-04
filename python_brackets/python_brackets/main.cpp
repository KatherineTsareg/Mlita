// python_brackets.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "PythonCode.h"

using namespace std;


int main(int argc, char * argv[])
{
	if (argc == 2)
	{
		ifstream inputFile(argv[1]);
		CPythonCode pythonText(inputFile);
		if (pythonText.CodeVerification())
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO\n" << pythonText.m_stringCount << ", " << pythonText.m_letterCount << endl;
		}
		return 0;
	}
	cout << "Error! Invalid count of input arguments!" << endl;
	return 1;
}

