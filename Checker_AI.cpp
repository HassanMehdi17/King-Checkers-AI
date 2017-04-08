// Hassan Mehdi
// 09/27/2016

/*The program is designed to read in the positions of both your checkers, and your opponents checkers onto an 8x8 board,
and then using recursion, find the most number of jumps of your king piece which will allow it to to eliminate a piece of the opponents checkers */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const char you = 'y', yourking = 'k', opp = 'o', empty = 'e'; // used for defining a position on the board as being occupied by your piece, your king, or the opponenets piece

class Board {
public:
	void reset(); // clears the board
	void addchecker(char who, int yourcheckers, int oppcheckers, int row, int col);
	int kingrow = 0, kingcol = 0, jumps = 0, testcasejumps[1000];
	int numjumps(int kingrow, int kingcol, int jumps);// number of jumps possible for row and column
	void print(char who, int yourcheckers, int oppcheckers, int row, int col); // print board for debugging
	int yourcheckers, oppcheckers; // keeps track of how many checkers each player will have in a testcase
private:
	char board[8][8];
};

int main()
{

	Board Testcase;
	int row, col; // represents the row and column on the board
	char who; // represents whos checker is on each position of the board

	int n; // number of test cases
	int nc; // nc -> ncounter :: counts test cases
	cin >> n;

	for (nc = 1; nc <= n; nc++) {
		Testcase.reset();
		cin >> Testcase.yourcheckers >> Testcase.oppcheckers;

		who = yourking;
		cin >> row >> col;
		Testcase.addchecker(who, Testcase.yourcheckers, Testcase.oppcheckers, row, col);

		for (int q = 2; q <= Testcase.yourcheckers; q++) {
			who = you;
			cin >> row >> col;
			Testcase.addchecker(who, Testcase.yourcheckers, Testcase.oppcheckers, row, col);
		}

		for (int q = 1; q <= Testcase.oppcheckers; q++) {
			who = opp;
			cin >> row >> col;
			Testcase.addchecker(who, Testcase.yourcheckers, Testcase.oppcheckers, row, col);
		}
		Testcase.print(who, Testcase.yourcheckers, Testcase.oppcheckers, row, col);
		Testcase.testcasejumps[nc] = Testcase.numjumps(Testcase.kingrow, Testcase.kingcol, Testcase.jumps);
		Testcase.reset();
	}
	cout << endl;

	for (nc = 1; nc <= n; nc++) {
		cout << "the number of jumps is " << Testcase.testcasejumps[nc] << endl;
	}
	return 0;
}

void Board::reset()
{
	for (int r = 7; r >= 0; r--) {
		for (int c = 0; c <= 7; c++)
		{
			board[r][c] = 'e';
		}
	}
}

void Board::addchecker(char who, int yourcheckers, int oppcheckers, int row, int col)
{
	board[row][col] = who;
}


int Board::numjumps(int kingrow, int kingcol, int jumps) {
	for (int r = 0; r <= 7; r++) {
		for (int c = 0; c <= 7; c++) { // this for loop statement is used to detect where the king piece is located before moving it
			if (board[r][c] == yourking) {
				kingrow = r;
				kingcol = c;
			}
		}
	}

	if (kingrow - 2 >= 0 && kingcol + 2 <= 7) { // up left
		if (board[kingrow - 2][kingcol + 2] == 'e') {
			if (board[kingrow - 1][kingcol + 1] == 'o') {
				board[kingrow][kingcol] = 'e';
				board[kingrow - 1][kingcol + 1] = 'e';
				board[kingrow - 2][kingcol + 2] = 'k';
				jumps = max(jumps, numjumps(kingrow - 2, kingcol + 2, jumps + 1));
				if (jumps < numjumps(kingrow - 2, kingcol + 2, jumps + 1)) {
					board[kingrow][kingcol] = 'k';
					board[kingrow - 1][kingcol + 1] = 'o';
					board[kingrow - 2][kingcol + 2] = 'e';
				}
			}
		}
	}
	if (kingrow + 2 <= 7 && kingcol + 2 <= 7) { // up right
		if (board[kingrow + 2][kingcol + 2] == 'e') {
			if (board[kingrow + 1][kingcol + 1] == 'o') {
				board[kingrow][kingcol] = 'e';
				board[kingrow + 1][kingcol + 1] = 'e';
				board[kingrow + 2][kingcol + 2] = 'k';
				jumps = max(jumps, numjumps(kingrow + 2, kingcol + 2, jumps + 1));
				if (jumps > numjumps(kingrow + 2, kingcol + 2, jumps + 1)) {
					board[kingrow][kingcol] = 'k';
					board[kingrow + 1][kingcol + 1] = 'o';
					board[kingrow + 2][kingcol + 2] = 'e';
				}


			}
		}
	}
	if (kingrow + 2 <= 7 && kingcol - 2 >= 0) { // down right
		if (board[kingrow + 2][kingcol - 2] == 'e') {
			if (board[kingrow + 1][kingcol - 1] == 'o') {
				board[kingrow][kingcol] = 'e';
				board[kingrow + 1][kingcol - 1] = 'e';
				board[kingrow + 2][kingcol - 2] = 'k';
				jumps = max(jumps, numjumps(kingrow + 2, kingcol - 2, jumps + 1));
				if (jumps > numjumps(kingrow + 2, kingcol - 2, jumps + 1) ){
					board[kingrow][kingcol] = 'k';
					board[kingrow + 1][kingcol - 1] = 'o';
					board[kingrow + 2][kingcol - 2] = 'e';
				}
			}
		}
	}
	 if ((kingrow - 2) >= 0 && (kingcol - 2) >= 0) { // down left
		if (board[kingrow - 2][kingcol - 2] == 'e') {
			if (board[kingrow - 1][kingcol - 1] == 'o') {
				board[kingrow][kingcol] = 'e';
				board[kingrow - 1][kingcol - 1] = 'e';
				board[kingrow - 2][kingcol - 2] = 'k';
				jumps = max(jumps, numjumps(kingrow - 2, kingcol - 2, jumps + 1));
				if (jumps > numjumps(kingrow - 2, kingcol - 2, jumps + 1)) {
					board[kingrow][kingcol] = 'k';
					board[kingrow - 1][kingcol - 1] = 'o';
					board[kingrow - 2][kingcol - 2] = 'e';
				}
			}
		}
	}
	 if (board[kingrow - 1][kingcol - 1] != 'o' && board[kingrow - 1][kingcol + 1] != 'o' && board[kingrow + 1][kingcol + 1] != 'o' && board[kingrow + 1][kingcol - 1] != 'o') 
	{ return jumps;}

	else return 0;
}


void Board::print(char who, int yourcheckers, int oppcheckers, int row, int col) // 'r' is representative of which row is being evaluated, while 'c' is representative of which column
{
	for (int r = 7; r >= 0; r--) {
		for (int c = 0; c <= 7; c++) {
			if (board[r][c] == yourking)
			{
				cout << " K " << " ";
			}

			else if (board[r][c] == you)
			{
				cout << " @ " << " ";
			}

			else if (board[r][c] == opp)
			{
				cout << " O " << " ";
			}

			if (board[r][c] == 'e')
			{
				cout << "[ ]" << " ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
};
