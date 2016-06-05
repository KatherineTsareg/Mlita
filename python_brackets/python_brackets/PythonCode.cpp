#include "stdafx.h"
#include "PythonCode.h"

using namespace std;

CPythonCode::CPythonCode(std::ifstream & inputFile)
	:m_inputFile(inputFile)
{
}

bool CPythonCode::CodeVerification()
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

void CPythonCode::SetState()
{
	if ((m_quotesCount == 3) && (m_commentState == STATE::MILTILINE))
	{
		m_commentState = STATE::NOTHING;
		m_quotesCount = 0;
	}
	else if ((m_quotesCount == 1) && (m_commentState == STATE::NOTHING))
	{
		m_commentState = STATE::LITERAL;
	}
	else if ((m_quotesCount == 1) && (m_commentState == STATE::LITERAL))
	{
		m_commentState = STATE::NOTHING;
		m_quotesCount = 0;
	}
	else if ((m_quotesCount == 3) && (m_commentState == STATE::LITERAL))
	{
		m_commentState = STATE::MILTILINE;
		m_quotesCount = 0;
	}
	else if ((m_quotesCount == 3) && (m_commentState == STATE::MILTILINE))
	{
		m_commentState = STATE::NOTHING;
		m_quotesCount = 0;
	}
}

void CPythonCode::SetStateAfterSomeLetter()
{
	if ((m_quotesCount == 2) && (m_commentState == STATE::LITERAL))
	{
		m_commentState = STATE::NOTHING;
		m_quotesCount = 0;
	}
	else if ((m_commentState == STATE::MILTILINE) && (m_quotesCount == 1))
	{
		m_quotesCount = 0;
	}
}

bool CPythonCode::BracketsChecking(string const& inputStr)
{
	m_letterCount = 1;
	for (char sign : inputStr)
	{
		auto it = find(begin(m_closing_brackets), end(m_closing_brackets), sign);
		if (sign == '"')
		{
			++m_quotesCount;
			SetState();
		}
		else if ((sign == '#') && (m_commentState == STATE::NOTHING))
		{
			break;
		}
		else if ((find(begin(m_opening_brackets), end(m_opening_brackets), sign) != end(m_opening_brackets)) && (m_commentState == STATE::NOTHING))
		{
			m_brackets.push(sign);
		}
		else if ((it != end(m_closing_brackets)) && ((m_commentState == STATE::NOTHING) || (m_quotesCount == 2) && (m_commentState == STATE::LITERAL)))
		{
			if (m_opening_brackets[it - begin(m_closing_brackets)] == m_brackets.top())
			{
				m_brackets.pop();
				SetStateAfterSomeLetter();
			}
			else
			{
				return false; //Error in bracket sequence
			}
		}
		else
		{
			SetStateAfterSomeLetter();
		}
		++m_letterCount;
	}
	return true;
}


CPythonCode::~CPythonCode()
{
}
