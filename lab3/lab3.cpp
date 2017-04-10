// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameBase.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	try {

		GameBase::start(argv, argc);
		return GameBase::instance()->play();

	}

	catch (result r) {
		if (r == wrongNumArgs) {
			return usageMessage("Lab3", " You have supplied the wrong Number of Arguments\nInput must be as follows: '<input-file> GameName' ", wrongNumArgs);
		}
		else if (r == wrongGameName) {
			return usageMessage("Lab3", " Input must be as follows: '<input-file> GameName' You have supplied an incorrect GameName\nCurrently available games: 'NineAlmonds, MagicSquare'\n", wrongGameName);
		}
		else if (r == invalidGamePiece) {
			return usageMessage("Lab3", " Invalid GamePiece found. Try again ", invalidGamePiece);
		}
		else if (r == tooManyPieces) {
			return usageMessage("Lab3", " Too many GamePieces given board dimensions. ERR ", tooManyPieces);
		}
		else if (r == nonNumberInput) {
			return usageMessage("Lab3", " NonNumeric input submitted when Numeric input required. ERR ", tooManyPieces);
		}
		else if (r == invalidNum) {
			return usageMessage("Lab3", " Value less than or equal to 0 inputted when positive value required. ERR ", tooManyPieces);
		}
		else if (r == pointerAlreadyInit) {
			return usageMessage("Lab3", " GameBase pointer already initialized. ", pointerAlreadyInit);

		}
	}

	catch (bad_alloc b)
	{
		return usageMessage("Lab3", "Memory could not be allocated.", noMemory);
	}

    return 0;
}

