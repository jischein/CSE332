#pragma once
#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "game_piece.h"
#include "FileParser.h"
#include <vector>
#include <memory>

using namespace std;

enum sideLengthError {BAD_SIDE_LENGTH = 2};

class GameBase {

public:
	GameBase(int, int);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual void prompt(unsigned int&, unsigned int&);
	virtual void turn() = 0;

	virtual int play();

	static void start(char*[], int);

	static shared_ptr<GameBase> instance();


protected:
	static string game_name;
	static int numTurns;
	static shared_ptr<GameBase> ptr;

	int rows_;
	int cols_;
	int longestPiece;
	vector<game_piece> pieces;
};

#endif
