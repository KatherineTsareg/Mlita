#include "stdafx.h"
#include "Pathfinding.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


pair<int, int> ReadInputParameters(ifstream & file)
{
	pair<int, int> sizes = { 0, 0 };
	int size;
	if (file >> size)
	{
		sizes.first = size;
	}
	if (file >> size)
	{
		sizes.second = size;
	}
	return sizes;
}

bool ReadingAndCheckingInputData(ifstream & inputFile, int & fieldSize, int & shipSize)
{
	if (inputFile.is_open())
	{
		auto sizesFieldAndShip = ReadInputParameters(inputFile);
		fieldSize = sizesFieldAndShip.first;
		shipSize = sizesFieldAndShip.second;
		if (!(shipSize < fieldSize) || !(fieldSize <= 300) || !(shipSize >= 1) || !(fieldSize >= 1))
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void FillingAnArray(ifstream & inputFile, int fieldSize, vector<vector<Field>> & field)
{
	string str;
	size_t i = 1;
	for (auto & j : field[0])
	{
		j.state = '@';
	}
	for (auto & j : field[fieldSize + 1])
	{
		j.state = '@';
	}
	for (auto & i : field)
	{
		i[0].state = '@';
		i[fieldSize + 1].state = '@';
	}
	
	while ((inputFile >> str) && (i <= fieldSize + 1))
	{
		for (size_t j = 1; j < fieldSize + 1; ++j)
		{
			field[i][j].state = str[j - 1];
		}
		++i;
	}
}

bool PossibleToMove(vector<vector<Field>> & field, int x, int y, int pred, int shipSize)
{
	bool move = true;
	for (size_t i = y; i < shipSize + y; ++i)
	{
		for (size_t j = x; j < shipSize + x; ++j)
		{
			if ((field[i][j].state == '@') || ((field[i][j].mark < pred + 1) && (field[i][j].mark != 0)))
			{
				move = false;
			}
		}
	}
	return move;
}

int CountOfMoves(vector<vector<Field>> & field, int fieldSize, int shipSize)
{
	vector<Cell> listOfCellsForChecking;
	listOfCellsForChecking.push_back(Cell(1, 1, 0));
	while ((listOfCellsForChecking.size() > 0) && (field[fieldSize - shipSize + 1][fieldSize - shipSize + 1].mark == 0))
	{
		Cell cell = listOfCellsForChecking.back();
		listOfCellsForChecking.pop_back();
		field[cell.y][cell.x].mark = cell.pred + 1;
		if (PossibleToMove(field, cell.x, (cell.y - shipSize < 0 ? 0 : cell.y - shipSize), cell.pred, shipSize))
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x, cell.y - 1, cell.pred + 1)); 
		}
		if (PossibleToMove(field, (cell.x - shipSize < 0 ? 0 : cell.x - shipSize), cell.y, cell.pred, shipSize))
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x - 1, cell.y, cell.pred + 1)); 
		}
		if (PossibleToMove(field, cell.x, cell.y + 1, cell.pred, shipSize)) 
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x, cell.y + 1, cell.pred + 1)); 
		}
		if (PossibleToMove(field, cell.x + 1, cell.y, cell.pred, shipSize)) 
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x + 1, cell.y, cell.pred + 1)); 
		}
	}
	return field[fieldSize - shipSize + 1][fieldSize - shipSize + 1].mark - 1;
}

void RecordResultInOutputFile(int steps)
{
	ofstream outputFile("output.txt");
	if (steps > 0)
	{
		outputFile << steps;
	}
	else
	{
		outputFile << "No";
	}
	outputFile.close();
}

void Pathfinding_f(ifstream & inputFile, int fieldSize, int shipSize)
{
	vector<vector<Field>> field(302);
	for (auto & row : field)
	{
		row.resize(302);
	}
	FillingAnArray(inputFile, fieldSize, field);
	RecordResultInOutputFile(CountOfMoves(field, fieldSize, shipSize));
}
