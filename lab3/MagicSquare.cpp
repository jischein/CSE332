#include "stdafx.h"
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include "FileParser.h"
#include "game_piece.h"
#include "game_board.h"
#include "FileParser.h"
#include "GameBase.h"
#include "MagicSquare.h"

using namespace std;

//default constructor
MagicSquareGame::MagicSquareGame() : GameBase(MAGIC_ROWS, MAGIC_COLS), numbers(vector<int>()) {
	for (int i = 1; i <= rows_*cols_; ++i) {
		numbers.push_back(i);
	}

	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			game_piece pie = game_piece();
			pieces.push_back(pie);

			if (int(pie.representation.size()) > longestPiece) {
				longestPiece = pie.representation.size();
			}
		}
	}

}

void MagicSquareGame::prompt(unsigned &piece) {
	bool valid_input = false;
	cout << "Please enter a piece to move, or type 'quit' to exit the game '\n' " << endl;
	int pieceVal = 0;
	while (!valid_input) {
		string input;
		getline(cin, input);

		if (input == "quit") {
			throw quitEntered;
		}
		try {
			pieceVal = stringToNum(input);
		}

		catch (result) {
			cout << "please enter in a valid, available piece" << endl;
			continue;
		}

		if (pieceVal <= rows_*cols_ && numbers[pieceVal - 1] == pieceVal) {

			valid_input = true;

		}
		else {
			cout << "please enter in a valid, available piece" << endl;
			cout << numbers[pieceVal - 1] << endl;
			continue;
		}

	}
	piece = pieceVal; 
}

//run one game turn
void MagicSquareGame::turn() {
	bool curSelect = false;
	bool totalSelect = false;

	unsigned piece;
	unsigned xPos;
	unsigned yPos;
	int ind;

	while (!totalSelect) {
		curSelect = false;
		cout << '\n' << endl;
		try {
			print();
		}
		catch (result) {
			throw;
		}

		//acces piece to move

		piece = 0;
		try {
			prompt(piece);
		}
		//only exception thrown in prompt is quit
		catch (result) {
			throw quitEntered;
		}

		while (!curSelect) {
			//get coords for spot to move piece
			xPos = 0;
			yPos = 0;

			try {
				GameBase::prompt(xPos, yPos);
			}
			catch (result) {
				throw quitEntered;
			}

			ind = yPos*cols_ + xPos;

			if (pieces[ind].representation != MAGIC_EMPTY) {
				curSelect = false;
				cout << "\nPlease select an empty destination square" << endl;
				continue;
			}
			else {
				curSelect = true;
				totalSelect = true;
			}
		}
	}
	string toDisplay = numToString(piece);

	if (int(toDisplay.size()) > longestPiece) {
		longestPiece = toDisplay.size();
	}

	game_piece num = game_piece(no_color, toDisplay, toDisplay);

	pieces[ind] = num;
	numbers[piece - 1] = 0; // remove piece from list
}

bool MagicSquareGame::done() {

		for (game_piece piece : pieces) {
			//if an empty piece exists on the board, then u r not done
			if (piece.representation == MAGIC_EMPTY) {
				return false;
			}
		}

		int targetSum = rows_*(rows_*cols_ + 1) / 2;

		//check rows

		for (int i = 0; i < rows_*cols_; i += cols_) {
			int sum = 0;
			for (int j = i; j < i + cols_; ++j) {
				
				try {
					sum += stringToNum(pieces[j].representation);
				}

				catch (result) { // if piece displayed is empty // not positive number
					throw;
				}

			}
			if (sum != targetSum) {
				return false;
			}
		}

		//check cols

		for (int i = 0; i < cols_; ++i) {
			int sum = 0;
			for (int j = i; j < cols_*rows_; j += rows_) {

					try {
						sum += stringToNum(pieces[j].representation);
					}

					catch (result) { // if piece displayed is empty // not positive number
						throw;
					}

				}

			if (sum != targetSum) {
				return false;
			}
		}

		//CHECK DIAGONALS
		int sum = 0;
		for (int i = 0; i < rows_*cols_; i += cols_ + 1) {
			try {
				sum += stringToNum(pieces[i].representation);
			}

			catch (result) { // if piece displayed is empty // not positive number
				throw;
			}
		}
		if (sum != targetSum) {
			return false;
		}

		sum = 0; 

		for (int i = rows_*(cols_ - 1); i > 0; i = i - cols_ + 1) {
			try {
				sum += stringToNum(pieces[i].representation);
			}

			catch (result) { // if piece displayed is empty // not positive number
				throw;
			}
		}

		if (sum != targetSum) {
			return false;
		}

		else {
			return true; 
		}
}

bool MagicSquareGame::stalemate() {

	for (game_piece piece : pieces) {
		//if an empty piece exists on the board, then u r not done
		if (piece.representation == MAGIC_EMPTY) {
			return false;
		}
	}

	return (!done());

}

ostream& operator << (ostream& os, const MagicSquareGame& game) {
	try {
		print_board(os, game.longestPiece, game.pieces, game.cols_, game.rows_);
	}
	catch (result) {
		throw;
	}
	return os;
}

void MagicSquareGame::print() {
	try {
		cout << *this << endl;
	}
	catch (result) {
		throw;
	}
	printRestOfPieces(numbers);
}

int stringToNum(string s){
	istringstream iss(s);
	int result;
	if (!(iss >> result))	//attempt conversion from string to int.
	{
		throw nonNumberInput;
	}
	if (result <= 0)
	{
		throw invalidNum;
	}
	return result;
}
string numToString(unsigned i) {
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << i;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result;
}
//print available pieces 
void printRestOfPieces(vector<int> numbers) {
	ostringstream oss;
	oss << "Available pieces: ";
	for (int i : numbers) {
		if (i != 0) {
			oss << i << " ";
		}
	}
	cout << oss.str();
}
