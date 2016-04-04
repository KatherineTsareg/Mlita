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
	int x, y, pred;
	Cell(int input_x, int input_y, int input_pred)
	{
		x = input_x;
		y = input_y;
		pred = input_pred;
	}
	
};

pair<int, int> ReadInputParameters(ifstream & file);

bool ReadingAndCheckingInputData(ifstream & inputFile, int & fieldSize, int & shipSize);

void FillingAnArray(ifstream & inputFile, int fieldSize, vector<vector<Field>> & field);

bool PossibleToMove(vector<vector<Field>> & field, int x, int y, int pred, int shipSize);

int CountOfMoves(vector<vector<Field>> & field, int fieldSize, int shipSize);

void RecordResultInOutputFile(int steps);

void Pathfinding_f(ifstream & inputFile, int fieldSize, int shipSize);