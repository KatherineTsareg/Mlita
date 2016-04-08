#include "stdafx.h"
#include "Pathfinding.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

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
	if (!inputFile.is_open())
	{
		return false;
	}
	auto sizesFieldAndShip = ReadInputParameters(inputFile);
	fieldSize = sizesFieldAndShip.first;
	shipSize = sizesFieldAndShip.second;
	if (!(shipSize < fieldSize) || !(fieldSize <= 300) || !(shipSize >= 1) || !(fieldSize >= 1))
	{
		return false;
	}
	return true;
}

void FillingAnArray(ifstream & inputFile, int fieldSize, vector<vector<Field>> & field)
{
	for (auto & it : field[0])
	{
		it.state = '@';
	}
	for (auto & it : field[fieldSize + 1])
	{
		it.state = '@';
	}
	for (auto & it : field)
	{
		it[0].state = '@';
		it[fieldSize + 1].state = '@';
	}
	
	string str;
	size_t i = 1;
	while ((inputFile >> str) && (i <= unsigned(fieldSize) + 1))
	{
		for (size_t j = 1; j < unsigned(fieldSize) + 1; ++j)
		{
			field[i][j].state = str[j - 1];
		}
		++i;
	}
}

bool IsMoveExist(vector<vector<Field>> const& field, int x, int y, int pred, int shipSize)
{
	bool move = true;
	for (size_t i = y; i < unsigned(shipSize) + y; ++i)
	{
		for (size_t j = x; j < unsigned(shipSize) + x; ++j)
		{
			if ((field[i][j].state == '@') || ((field[i][j].mark < pred + 1) && (field[i][j].mark != 0)))
			{
				move = false;
			}
		}
	}
	return move;
}

int CalculateTheSteps(vector<vector<Field>> & field, int fieldSize, int shipSize)
{
	vector<Cell> listOfCellsForChecking;//список для хранения ячеек, которые будем "закрашивать" числами
	listOfCellsForChecking.push_back(Cell(1, 1, 0));
	while ((listOfCellsForChecking.size() > 0) && (field[fieldSize - shipSize + 1][fieldSize - shipSize + 1].mark == 0))
	{
		Cell cell = listOfCellsForChecking.back();//берем ячейку
		listOfCellsForChecking.pop_back();//удаляем ее из списка
		field[cell.y][cell.x].mark = cell.previousStep + 1;//записываем в ячеку номер хода
		///просматриваем ячеки рядом, на возможность хода
		if (IsMoveExist(field, cell.x, (cell.y - shipSize < 0 ? 0 : cell.y - shipSize), cell.previousStep, shipSize)) //если ход вверх свободен
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x, cell.y - 1, cell.previousStep + 1)); //добавляем верзнюю ячейку в список
		}
		if (IsMoveExist(field, (cell.x - shipSize < 0 ? 0 : cell.x - shipSize), cell.y, cell.previousStep, shipSize)) // если ход влево свободен
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x - 1, cell.y, cell.previousStep + 1));
		}
		if (IsMoveExist(field, cell.x, cell.y + 1, cell.previousStep, shipSize)) //если ход вправо свободен
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x, cell.y + 1, cell.previousStep + 1));
		}
		if (IsMoveExist(field, cell.x + 1, cell.y, cell.previousStep, shipSize)) //если ход вниз свободен
		{ 
			listOfCellsForChecking.push_back(Cell(cell.x + 1, cell.y, cell.previousStep + 1));
		}
	}
	return field[fieldSize - shipSize + 1][fieldSize - shipSize + 1].mark - 1; //возвращаем номер хода в конечной ячейке -1, так как начинали индексацию ходов с 1
}

void RecordResultInOutputFile(int steps)
{
	ofstream outputFile("output.txt");
	outputFile << (steps < 0 ? "No" : to_string(steps));
	outputFile.close();
}

void FindingPath(ifstream & inputFile, int fieldSize, int shipSize)
{
	vector<vector<Field>> field(302);
	for (auto & row : field)
	{
		row.resize(302);
	}
	FillingAnArray(inputFile, fieldSize, field);
	RecordResultInOutputFile(CalculateTheSteps(field, fieldSize, shipSize));
}
