#include "stdafx.h"
#include "..\python_brackets\PythonCode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(PythonBrackets)
	BOOST_AUTO_TEST_CASE(find_no_errors_in_empty_text)
	{
		ifstream file("empty.txt");
		CPythonCode code(file);
		BOOST_CHECK(code.CodeVerification());
	}
	BOOST_AUTO_TEST_CASE(check_different_brackets)
	{
		ifstream file("first_test_passed.txt");
		CPythonCode code(file);
		BOOST_CHECK(code.CodeVerification());
	}
	BOOST_AUTO_TEST_CASE(failed_when_bracket_sequence_is_fail)
	{
		ifstream file("second_test_failed.txt");
		CPythonCode code(file);
		BOOST_CHECK(!code.CodeVerification());
		BOOST_CHECK_EQUAL(code.m_stringCount, 2);
		BOOST_CHECK_EQUAL(code.m_letterCount, 23);
	}
	BOOST_AUTO_TEST_CASE(processing_single_line_and_multiline_comments)
	{
		ifstream file("third_test_passed.txt");
		CPythonCode code(file);
		BOOST_CHECK(code.CodeVerification());
	}
	BOOST_AUTO_TEST_CASE(processing_literals_and_literals_in_comments)
	{
		ifstream file("fourth_test_passed.txt");
		CPythonCode code(file);
		BOOST_CHECK(code.CodeVerification());
	}
BOOST_AUTO_TEST_SUITE_END()
