#pragma once
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


struct Field
{
	int mark = 0;
	char state;
};

struct Cell {
	int x, y, previousStep;
	Cell(int x, int y, int prevStep)
		:x(x)
		,y(y)
		,previousStep(prevStep)
	{
	}
};

pair<int, int> ReadInputParameters(ifstream & file);

bool ReadingAndCheckingInputData(ifstream & inputFile, int & fieldSize, int & shipSize);

void FillingAnArray(ifstream & inputFile, int fieldSize, vector<vector<Field>> & field);

bool IsMoveExist(vector<vector<Field>> const& field, int x, int y, int pred, int shipSize);

int CalculateTheSteps(vector<vector<Field>> & field, int fieldSize, int shipSize);

void RecordResultInOutputFile(int steps);

void FindingPath(ifstream & inputFile, int fieldSize, int shipSize);