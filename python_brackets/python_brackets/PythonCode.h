#pragma once
#include "stdafx.h"

class CPythonCode
{
public:
	CPythonCode(std::ifstream & inputFile);
	
	bool ReadInputData();
	bool BracketsChecking(std::string const& inputStr);
	
	~CPythonCode();
private:
	const char m_opening_brackets[3] = { '(', '[', '{' };
	const char m_closing_brackets[3] = { ')', ']', '}' };
	std::ifstream & m_inputFile;
	std::stack<char> m_brackets;
	bool m_commentState = false;
public:
	unsigned m_letterCount;
	unsigned m_stringCount = 0;
};

