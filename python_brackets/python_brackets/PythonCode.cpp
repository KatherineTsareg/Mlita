#include "stdafx.h"
#include "PythonCode.h"

using namespace std;

CPythonCode::CPythonCode(std::ifstream & inputFile)
	:m_inputFile(inputFile)
{
}

bool CPythonCode::ReadInputData()
{
	if (m_inputFile.is_open())
	{
		string inputStr;
		while (getline(m_inputFile, inputStr))
		{
			++m_stringCount;
			if (!BracketsChecking(inputStr))
			{
				return false;
			}
		}
		return (m_brackets.size() ? false : true);
	}
	return false;
}

bool CPythonCode::BracketsChecking(string const& inputStr)
{
	m_letterCount = 1;
	for (char letter : inputStr)
	{
		auto it = find(begin(m_closing_brackets), end(m_closing_brackets), letter);
		
		if ((letter == '"') || (letter == '"""'))
		{
			m_commentState = m_commentState ? false : true;
		}
		else if ((letter == '#') && !m_commentState)
		{
			break;
		}
		else if ((find(begin(m_opening_brackets), end(m_opening_brackets), letter) != end(m_opening_brackets)) && !m_commentState)
		{
			m_brackets.push(letter);
		}
		else if ((it != end(m_closing_brackets)) && !m_commentState)
		{
			if (m_opening_brackets[it - begin(m_closing_brackets)] == m_brackets.top())
			{
				m_brackets.pop();
			}
			else
			{
				return false; //Error in bracket sequence
			}
		}
		++m_letterCount;
	}
	return true;
}

CPythonCode::~CPythonCode()
{
}
