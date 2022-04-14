#pragma once
#include <vector>
#include <string>
using namespace std;

class Board
{
	private:
		char checkWin();
		vector<vector<int>> eachRowOfSpaces;
		const int numberOfRows = 6; // init rows
		const int numberOfIntsInRow = 7; //init columns
		char winnerXorO;
	public:
		Board();
		bool doMove(int columnNumber, char playerXorO);
		char getWinnerXorO() { return winnerXorO; };
		string displayBoard();
};

