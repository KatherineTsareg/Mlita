#include "stdafx.h"
#include "../Pathfinding/Pathfinding.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <cstdio>

using namespace std;

string GetResultFromOutputFile()
{
	string result;
	ifstream fout("output.txt");
	if (fout.is_open())
	{
		fout >> result;
	}
	return result;
}

void ResultOfProgram(ifstream  & fin)
{
	int fieldSize, shipSize;
	if (ReadingAndCheckingInputData(fin, fieldSize, shipSize))
	{
		FindingPath(fin, fieldSize, shipSize);
	}
}

BOOST_AUTO_TEST_SUITE(Pathfinding_function)

	BOOST_AUTO_TEST_CASE(should_not_make_output_file_from_wrong_input_data)
	{
		ifstream fin("input_err.txt");
		ResultOfProgram(fin);
		ifstream outputFile("output.txt");
		BOOST_CHECK(!outputFile.is_open());
	}
	
	BOOST_AUTO_TEST_CASE(should_not_make_output_file_from_nonexisten_input_file)
	{
		ifstream fin("input.txt");
		ResultOfProgram(fin);
		ifstream outputFile("output.txt");
		BOOST_CHECK(!outputFile.is_open());
	}

	BOOST_AUTO_TEST_CASE(should_make_not_empty_file_from_correct_input_data)
	{
		ifstream fin("input_correct_1.txt");
		ResultOfProgram(fin);
		string result = GetResultFromOutputFile();
		std::remove("output.txt");
		BOOST_CHECK_EQUAL(result,"8");
	}

	BOOST_AUTO_TEST_CASE(should_make_not_empty_file_with_negative_result_from_correct_input_data)
	{
		ifstream fin("input_correct_2.txt");
		ResultOfProgram(fin);
		string result = GetResultFromOutputFile();
		std::remove("output.txt");
		BOOST_CHECK_EQUAL(result, "No");
	}

	BOOST_AUTO_TEST_CASE(should_make_not_empty_file_with_correct_result_from_uncorrect_input_symbol_of_field)
	{
		ifstream fin("input_symb.txt");
		ResultOfProgram(fin);
		string result = GetResultFromOutputFile();
		std::remove("output.txt");
		BOOST_CHECK_EQUAL(result, "10");
	}

	BOOST_AUTO_TEST_CASE(should_not_make_output_file_from_empty_input_data)
	{
		ifstream fin("input_empty.txt");
		ResultOfProgram(fin);
		ifstream outputFile("output.txt");
		BOOST_CHECK(!outputFile.is_open());
	}

	BOOST_AUTO_TEST_CASE(should_make_output_file_from_maximum_input_data)
	{
		ifstream fin("input_max.txt");
		ResultOfProgram(fin);
		string result = GetResultFromOutputFile();
		std::remove("output.txt");
		BOOST_CHECK_EQUAL(result, "598");
	}

BOOST_AUTO_TEST_SUITE_END()