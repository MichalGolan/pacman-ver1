#include "Board.h"
#include"Board.h"



Board::Board()
{
	_currBCNum = 0;
	_maxBCnum = countMaxBC();
}

void Board::print()
{
	int i;
	for (i = 0; i < ROW; i++)
	{
		cout << _board[i] << endl;
	}
}

int Board:: countMaxBC()
{
	int i, j, ret = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (_board[i][j] == ' ')
			{
				ret++;
			}
		}
	}
	return ret;
}