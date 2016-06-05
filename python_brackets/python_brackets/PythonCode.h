#pragma once
#include "stdafx.h"

class CPythonCode
{
public:
	CPythonCode(std::ifstream & inputFile);
	bool CodeVerification();
	~CPythonCode();
	size_t m_letterCount;
	size_t m_stringCount = 0;
private:
	bool BracketsChecking(std::string const& inputStr);
	void SetState();
	void SetStateAfterSomeLetter();
	const char m_opening_brackets[3] = { '(', '[', '{' };
	const char m_closing_brackets[3] = { ')', ']', '}' };
	std::ifstream & m_inputFile;
	std::stack<char> m_brackets;
	int m_quotesCount = 0;
	const enum STATE { NOTHING, LITERAL, MILTILINE };
	int m_commentState = STATE::NOTHING;
};

