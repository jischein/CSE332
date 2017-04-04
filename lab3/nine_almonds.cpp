#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "FileParser.h"
#include "game_piece.h"
#include "game_board.h"
#include "nine_almonds.h"
#include "FileParser.h"
#include "GameBase.h"

using namespace std;
//using a modified print_board method from lab 1, we will overload the ostream operator as to utilize that method when we wish to print out our board
ostream& operator << (ostream& os, const NineAlmondsGame& game) {
	try {
		print_board(os, game.longestPiece, game.pieces, game.cols_, game.rows_);
	}
	catch (result) {
		throw;
	}
	return os;
}

bool NineAlmondsGame::done()
{
	for (int i = 0; i < 25; i++) {
		if (i == 12) {

			if (pieces[i].name != "almond") {
				return false;
			}

		}
		else {

			if (pieces[i].name == "almond") {
				return false;
			}

		}
	}
	return true;
}

//stalemate iterates through every spot on the board and if an almond exists at a given spot, tests all possible moves and sees if any are valid.

bool NineAlmondsGame::stalemate()
{
	if (done()) {
		return false;
	}

	for (int i = 0; i < 25; ++i) {
		//almond found check to see if any valid moves exist between this almond and all other pieces that are empty
		if (pieces[i].name == "almond") {

			for (int j = 0; j < 25; ++j) {

				if (pieces[j].name != "almond") {
					int startRow = i / (int)cols_;
					int startCol = i % (int)cols_;
					int endRow = j / (int)cols_;
					int endCol = j % (int)cols_;

					if (validMove(startCol, startRow, endCol, endRow)) {
						return false;
					}
				}

			}

		}
	}
	return true;
}
//this is a method that executes at the beginning of the turn-where we grab the piece that we want to move
void NineAlmondsGame::turn()
{
	cout << '\n' << endl;
	try {
		print();
	}
	catch (result) {
		throw;
	}

	unsigned selectColumn;
	unsigned selectRow;

	try {
		cout << "Select the piece that you would like to move" << endl;
		prompt(selectColumn, selectRow);
	}
	catch (result quitInput) {
		throw quitInput;
	}

	ostringstream movesStream;

	int pieceInd = selectRow * cols_ + selectColumn;

	if (pieces[pieceInd].name != "almond") {
		cout << "an almond was not found at this location - please reselect" << endl;
		return turn();
	}

	movesStream << selectColumn << "," << selectRow;

	string moves = movesStream.str();

	return turnHelper(selectColumn, selectRow, moves);
}

void NineAlmondsGame::turnHelper(unsigned startCol, unsigned startRow, string moves)
{
	unsigned endCol;
	unsigned endRow;

	try {
		cout << "Select the space that you would like to move to" << endl;
		prompt(endCol, endRow);
	}
	catch (result quitInput) {
		throw quitInput;
	}

	//check if end piece is empty
	int startInd = startRow * cols_ + startCol;
	int endInd = endRow * cols_ + endCol;

	//though this check exists in validMove - it is important that we include it here as to alert the user why they cannot move to the selected location (wheras valid move checks for a stalemate & provides no error message)
	if (pieces[endInd].name == "almond") {
		cout << "you cannot move to the selected space because it already has an almond on it" << endl;
		return turnHelper(startCol, startRow, moves);
	}

	// check if valid move

	if (!validMove(startCol, startRow, endCol, endRow)) {
		cout << "move was invalid, try again" << endl;
		return turnHelper(startCol, startRow, moves);
	}

	// move is valid - make starting piece empty ending piece almond and empty midpiece
	int midRow = (startRow + endRow) / 2;
	int midCol = (startCol + endCol) / 2;

	int midInd = midRow * cols_ + midCol;

	pieces[endInd] = game_piece(brown, "almond", "A");
	pieces[startInd] = game_piece();
	pieces[midInd] = game_piece();

	//update list of moves 

	ostringstream movesStream;

	movesStream << moves << " to " << endCol << "," << endRow;

	moves = movesStream.str();

	//print board

	try {
		print();
	}
	catch (result) {
		throw;
	}

	return turnChangeHelper(endCol, endRow, moves);

}

void NineAlmondsGame::turnChangeHelper(unsigned startCol, unsigned startRow, string moves)
{
	string input;

	cout << "moves so far: " << moves << endl;

	cout << "continue this turn ('y' or 'n')? " << endl;
	getline(cin, input);

	if (input == "y") {
		return turnHelper(startCol, startRow, moves);
	}

	else if (input == "n") {
		cout << "next turn will now begin" << endl;
		return;
	}

	else {
		cout << "invalid input - please enter 'y' for yes or 'n'for no (without single quotation marks) in regards to continuing this turn" << endl;
		return turnChangeHelper(startCol, startRow, moves);
	}
}
/*
void NineAlmondsGame::prompt(unsigned & column, unsigned & row)
{
	string input;
	cout << "Enter your desired position in the form of 'x, y' or type 'quit' to exit" << '\n';
	getline(cin, input);

	if (input == "quit") {
		throw quitEntered;
	}

	auto pos = input.find(',');

	if (pos == -1) {
		cout << "NO COMMA found within input please enter according to desired format" << endl;
		return prompt(column, row);
	}

	input.replace(pos, 1, " ");

	//make sure space is in the middle and the size of the string is 3

	if (input.size() == 3) {
		istringstream iss(input);
		iss >> column;
		iss >> row;

		if (column < 0 || column > 4 || row < 0 || row > 4) {
			cout << " input was out of bounds, range for x and y is [0,4]. Please enter input accordingly." << endl;
			return prompt(column, row);
		}
	}

	else {
		cout << "INPUT WAS NOT OF DESIRED FORMAT- please enter according to instructions" << endl;
		return prompt(column, row);
	}
}
*/

bool NineAlmondsGame::validMove(int startCol, int startRow, int endCol, int endRow) {
	//check if startSpot has an almond and check if endSpot is empty first

	if (pieces[startRow * cols_ + startCol].name != "almond") {
		return false;
	}

	if (pieces[endRow * cols_ + endCol].name == "almond") {
		return false;
	}

	//look at middle position - check if it is an almond

	int midRow = (startRow + endRow) / 2;
	int midCol = (startCol + endCol) / 2;

	if (pieces[midRow * cols_ + midCol].name != "almond") {
		return false;
	}

	//make sure positions are not adjacent and positions are not seperated by more than 2 spaces

	if (abs(startRow - endRow) > 2 || abs(startCol - endCol) > 2 || abs(startCol - endCol) == 1 || abs(startRow - endRow) == 1) {
		return false;
	}

	//if the move is diagonal make sure that the spaces are seperated by 2 spots
	if (abs(startRow - endRow) != 0 && abs(startCol - endCol) != 0) {
		if (abs(startRow - endRow) != 2 || abs(startCol - endCol) != 2) {
			return false;
		}
	}
	return true;

}

//prints current board using ostreamoperator defined above
void NineAlmondsGame::print() {
	try {
		cout << *this << endl;
	}
	catch (result) {
		throw;
	}
}

//default constructor
NineAlmondsGame::NineAlmondsGame(): GameBase(5,5) {
	for (int i = 0; i < 25; i++) {
		pieces.push_back(game_piece(no_color, "", " "));
	}

	for (int j = 6; j < 9; j++) {
		pieces[j] = game_piece(brown, "almond", "A");
	}

	for (int k = 11; k <= 13; k++) {
		pieces[k] = game_piece(brown, "almond", "A");
	}

	for (int l = 16; l <= 18; l++) {
		pieces[l] = game_piece(brown, "almond", "A");
	}
	//arbitrary selection of piece that is an almond for longest displaying piece
	longestPiece = pieces[17].representation.size();

}
