// python_brackets.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

const vector<char> OPENING_BRACKET_LIST = {'(', '[', '{'};
const vector<char> CLOSING_BRACKETS_LIST = { ')', ']', '}'};

int GetIndexOfLetterInVector(char const& letter, vector<char> list)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i] == letter)
		{
			return i;
		}
	}
	return -1;
}

bool BracketsChecking(ifstream & inputFile)
{
	int stringCount = 1;
	int letterCount = 1;
	if (inputFile.is_open())
	{
		stack<char> inputBrackets;
		string inputStr;
		int index;
		while (getline(inputFile, inputStr))
		{
			for (auto letter : inputStr)
			{
				if (GetIndexOfLetterInVector(letter, OPENING_BRACKET_LIST) >= 0)
				{
					inputBrackets.push(letter);
				}
				else if ((index = GetIndexOfLetterInVector(letter, CLOSING_BRACKETS_LIST)) >= 0)
				{
					if (OPENING_BRACKET_LIST[index] == inputBrackets.top())
					{
						inputBrackets.pop();
					}
					else
					{
						cout << "NO\n" << stringCount << ", " << letterCount;
						return false;
					}
				}
				++letterCount;
			}
			++stringCount;
		}
		return true;
	}
}

int main(int argc, char * argv[])
{
	if (argc == 2)
	{
		ifstream inputFile(argv[1]);
		cout << (BracketsChecking(inputFile) ? "YES" : "") << endl;
		return 0;
	}
	cout << "Error! Invalid count of input arguments!" << endl;
	return 1;
}

