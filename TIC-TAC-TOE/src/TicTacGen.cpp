#include "Includes/TicTacGen.h"
#include<ctime>
#include<iostream>

std::vector<Field>TicTacGen::GetWin(char player) {

	auto foundPattern = false;
	std::vector<Field> patternPoints;

#pragma region HorizontalCheck

	for (int i = 0; i < this->MaxSize; ++i) {
		for (int j = 0; j < this->MaxSize; ++j) {

			if (this->gameMap[i][j] != player) {
				foundPattern = false;
				patternPoints.clear();
				break;
			}

			else if (this->gameMap[i][j] == player) {
				foundPattern = true;
				patternPoints.push_back({ i,j });
			}
		}

		if (foundPattern) {
			this->GetWinType = WinType::Horizontal;
			return patternPoints;
		}
	}//

#pragma endregion

#pragma region VerticalCheck

	for (int i = 0; i < this->MaxSize; ++i) {
		for (int j = 0; j < this->MaxSize; ++j) {

			if (this->gameMap[j][i] != player) {
				foundPattern = false;
				patternPoints.clear();
				break;
			}

			else if (this->gameMap[j][i] == player) {
				foundPattern = true;
				patternPoints.push_back({ j,i });
			}
		}

		if (foundPattern) {
			this->GetWinType = WinType::Vertical;
			return patternPoints;
		}
	}//

#pragma endregion

#pragma region DiagonalCheck

	if (this->gameMap[0][0] == player && this->gameMap[1][1] == player && this->gameMap[2][2] == player) {

		patternPoints.push_back({ 0,0 });
		patternPoints.push_back({ 1,1 });
		patternPoints.push_back({ 2,2 });
		this->GetWinType = WinType::Diagonal_1;
		return patternPoints;
	}

	else if (this->gameMap[2][0] == player && this->gameMap[1][1] == player && this->gameMap[0][2] == player) {

		patternPoints.push_back({ 2,0 });
		patternPoints.push_back({ 1,1 });
		patternPoints.push_back({ 0,2 });
		this->GetWinType = WinType::Diagonal_2;
		return patternPoints;
	}
#pragma endregion

	bool stalemateCheck = true;

	for (int i = 0; i < this->MaxSize; ++i) {
		for (int j = 0; j < this->MaxSize; ++j) {

			if (this->gameMap[i][j] == ' ') {
				stalemateCheck = false;
				break;
			}
		}
	}

	if (stalemateCheck == true)
		this->GetWinType = WinType::Stalemate;

	return patternPoints;
}

Field TicTacGen::ComputeAI() {

	Field tempField{ -1,-1 };
	bool FoundPattern = false;
	auto count = 0;
	Field tempFieldVec;

#pragma region CheckWin

	tempField = this->HorizontalCheck('O', 'X');
	if (tempField.row != -1)
		return tempField;

	tempField = this->VerticalCheck('O', 'X');
	if (tempField.row != -1)
		return tempField;

	tempField = this->DiagonalCheck('O');
	if (tempField.row != -1)
		return tempField;

#pragma endregion

#pragma region CounterAttack

	tempField = this->HorizontalCheck('X', 'O');
	if (tempField.row != -1)
		return tempField;

	tempField = this->VerticalCheck('X', 'O');
	if (tempField.row != -1)
		return tempField;

	tempField = this->DiagonalCheck('X');
	if (tempField.row != -1)
		return tempField;

#pragma endregion

#pragma region PlayMoves

	srand(static_cast<unsigned>(time(NULL)));

	if (tempField.row == -1) {

		bool proceed = true;

		while (proceed)
		{
			auto rol = rand() % 3;
			auto col = rand() % 3;

			//std::cout << "row: " << rol << "\t" << "col: " << col << std::endl;

			if (this->gameMap[rol][col] == ' ') {

				tempField.row = rol;
				tempField.col = col;
				proceed = false;
				break;
			}
		}
	}

#pragma endregion

	return tempField;
}


Field TicTacGen::HorizontalCheck(char player, char player2) {

	Field tempField{ -1,-1 };
	bool FoundPattern = false;
	auto count = 0;
	Field tempFieldVec;

	for (int i = 0; i < this->MaxSize; ++i)
	{
		count = 0;
		tempFieldVec = { -1,-1 };
		if (FoundPattern)
			break;

		for (int j = 0; j < this->MaxSize; ++j)
		{
			if (this->gameMap[i][j] == player)
				count += 1;

			else if (this->gameMap[i][j] == player2)
				break;

			else if (this->gameMap[i][j] == ' ')
			{
				tempFieldVec.row = i;
				tempFieldVec.col = j;
			}

			if (count >= 2)
			{
				if (tempFieldVec.row != -1)
				{
					tempField.row = tempFieldVec.row;
					tempField.col = tempFieldVec.col;
					FoundPattern = true;
					return tempField;
				}

				else
				{
					if (this->gameMap[i][2] == ' ')
					{
						tempField.row = i;
						tempField.col = 2;
						FoundPattern = true;
						return tempField;
					}
				}
				break;
			}
		}
	}

	return tempField;
}


Field TicTacGen::VerticalCheck(char player, char player2) {

	Field tempField{ -1,-1 };
	bool FoundPattern = false;
	auto count = 0;
	Field tempFieldVec;

	for (int i = 0; i < this->MaxSize; ++i)
	{
		count = 0;
		tempFieldVec = { -1,-1 };
		if (FoundPattern)
			break;

		for (int j = 0; j < this->MaxSize; ++j)
		{
			if (this->gameMap[j][i] == player)
				count += 1;

			else if (this->gameMap[j][i] == player2)
				break;

			else if (this->gameMap[j][i] == ' ')
			{
				tempFieldVec.row = j;
				tempFieldVec.col = i;
			}

			if (count >= 2)
			{
				if (tempFieldVec.row != -1)
				{
					tempField.row = tempFieldVec.row;
					tempField.col = tempFieldVec.col;
					FoundPattern = true;
					return tempField;
				}

				else
				{
					if (this->gameMap[2][i] == ' ') {
						tempField.row = 2;
						tempField.col = i;
						FoundPattern = true;
						return tempField;
					}
				}
				break;
			}
		}
	}

	return tempField;
}


Field TicTacGen::DiagonalCheck(char player)
{

	Field tempField{ -1,-1 };
	bool FoundPattern = false;
	auto count = 0;
	Field tempFieldVec;

	bool check1, check2, check3 = false;

	if (check1 = this->gameMap[0][0] == player)
		count++;

	if (check2 = this->gameMap[1][1] == player)
		count++;

	if (check3 = this->gameMap[2][2] == player)
		count++;

	if (count == 2)
	{
		if (!check1)
		{
			if (this->gameMap[0][0] == ' ')
				return { 0,0 };
		}

		if (!check2)
		{
			if (this->gameMap[1][1] == ' ')
				return { 1,1 };
		}

		if (!check3)
		{
			if (this->gameMap[2][2] == ' ')
				return { 2,2 };
		}
	}

	count = 0;
	check1 = check2 = check3 = false;

	if (check1 = this->gameMap[2][0] == player)
		count++;

	if (check2 = this->gameMap[1][1] == player)
		count++;

	if (check3 = this->gameMap[0][2] == player)
		count++;

	if (count == 2)
	{
		if (!check1)
		{
			if (this->gameMap[2][0] == ' ')
				return { 2,0 };
		}
		if (!check2)
		{
			if (this->gameMap[1][1] == ' ')
				return { 1,1 };
		}
		if (!check3)
		{
			if (this->gameMap[0][2] == ' ')
				return { 0,2 };
		}
	}

	return tempField;
}