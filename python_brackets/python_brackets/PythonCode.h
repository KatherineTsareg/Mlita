#pragma once
#include "stdafx.h"

class CPythonCode
{
public:
	CPythonCode(std::ifstream & inputFile);
	bool CodeVerification();
	~CPythonCode();
public:
	unsigned m_letterCount;
	unsigned m_stringCount = 0;
private:
	bool BracketsChecking(std::string const& inputStr);
	void SetState();
	void SetStateAfterSomeLetter();
private:
	const char m_opening_brackets[3] = { '(', '[', '{' };
	const char m_closing_brackets[3] = { ')', ']', '}' };
	std::ifstream & m_inputFile;
	std::stack<char> m_brackets;
	int m_quotesCount = 0;
	int m_commentState = 0;//0 - nothing; 1 - literal, 2 - multiline comment
};

