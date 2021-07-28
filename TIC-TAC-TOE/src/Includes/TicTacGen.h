#pragma once

#include<vector>

struct Field {

	int row, col;
};

enum class WinType
{
	None,
	Horizontal,
	Vertical,
	Diagonal_1,
	Diagonal_2,
	Stalemate
};

class TicTacGen
{

public:

	static constexpr char MaxSize = 3;

	char gameMap[MaxSize][MaxSize] = {
									{' ',' ',' '},
									{' ',' ',' '},
									{' ',' ',' '},
	};

	std::vector<Field>GetWin(char player);
	Field ComputeAI();
	WinType GetWinType{ WinType::None };

private:
	Field HorizontalCheck(char player, char playyer2);
	Field VerticalCheck(char player, char player2);
	Field DiagonalCheck(char player);
};

