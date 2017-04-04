#pragma once
#include <iostream>
#include <fstream>
#include "game_piece.h"
#include "game_board.h"
#include "FileParser.h"
#include "GameBase.h"
#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

const string MAGIC_EMPTY = " ";

class MagicSquareGame : public GameBase {
public:
	friend ostream& operator<< (ostream&, const MagicSquareGame&);
	//Constructors: Default, fed to main method, second is used inside of NineAlmondsGame Class to alter game board
	MagicSquareGame();

	virtual bool done();

	virtual bool stalemate();
	//helper method to tell whether a valid move exists between two points on the board
	bool validMove(int, int, int, int);

	virtual void prompt(unsigned &);

	//turn method - executes at beginning of turn and grabs piece to move
	virtual void turn();

	//helper method to turn - grabs the location that piece wants to move to and checks if it is valid move
	void turnHelper(unsigned, unsigned, string);

	//helper method that handles transition between turns - ie. if user continues on same turn or switches to a different almond
	void turnChangeHelper(unsigned, unsigned, string);

	//play method as described in writeup

	virtual void print() override;

private:
	vector<int> numbers;
};

void printRestOfPieces(vector<int>);

int stringToNum(string);

ostream & operator<< (ostream&, const MagicSquareGame&);

bool hasPiece(game_piece);

string numToString(unsigned);

#endif