#include "stdafx.h"
#include "GameBase.h"
#include "nine_almonds.h"
#include "MagicSquare.h"
#include "FileParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int GameBase::numTurns = 0;
string GameBase::game_name = "";
shared_ptr<GameBase> GameBase::ptr = nullptr;


GameBase::GameBase(int rows, int cols) : rows_(rows), cols_(cols), longestPiece(0), pieces(vector<game_piece>()) {};

 GameBase* GameBase::start(char* args[], int argsCount) {

	//check if we've already initialized the ptr to a game 
	if (ptr != nullptr)
	 {
		 throw pointerAlreadyInit;
	 }

	if (argsCount != numArgs) {
		throw wrongNumArgs;
	}

	else {
		if (string(args[gameName]) == "NineAlmonds") {

			try {
				game_name = args[gameName];
				ptr = make_shared<NineAlmondsGame>();
			}

			catch (bad_alloc)
			{
				throw;
			}

		}

		else if (string(args[gameName]) == "MagicSquare") {

			try {
				game_name = args[gameName];
				ptr = make_shared<MagicSquareGame>();
			}

			catch (bad_alloc)
			{
				throw;
			}

		}

		else {
			throw wrongGameName;
		}


	}


}

 void GameBase::prompt(unsigned int & column, unsigned int & row)
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

		 if (int(column) < 0 || int(column) > cols_ || int(row) < 0 || int(row) > rows_) {
			 cout << " input was out of bounds, range for x and y is [0,4]. Please enter input accordingly." << endl;
			 return prompt(column, row);
		 }
	 }

	 else {
		 cout << "INPUT WAS NOT OF DESIRED FORMAT- please enter according to instructions" << endl;
		 return prompt(column, row);
	 }
 }
int GameBase::play() {

	while (!done() && !stalemate()) {
		try {
			numTurns++;
			turn();
		}
		catch (result quitEntered) {
			cout << '\n' << "You have quit the game. The game was played for " << numTurns << " turns." << endl;
			cerr << quitEntered << endl;
			return quitEntered;
		}
	}

	if (done()) {
		try {
			print();
		}
		catch (result) {
			throw;
		}
		cout << '\n' << "You have won the game after " << numTurns << " turns. Congrats!" << endl;
		return success;
	}

	if (stalemate()) {
		cout << '\n' << "You have lost this game due to a stalemate after " << numTurns << " turns. Sorry :(" << endl;
		cerr << stalemateErr << endl;
		return stalemateErr;
	}

	return success;

}

shared_ptr<GameBase> GameBase::instance()
{
	if (ptr == nullptr)
	{
		throw nullPtr;
	}
	else
	{
		return ptr;
	}
}
