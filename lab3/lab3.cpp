// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameBase.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	try {
		GameBase* game = GameBase::start(argv, argc);
		if (game != 0) {
			return game->play();
		}
		else {
			cout << "NOT RIGHT PTR" << endl;
			cout << "U SENT ZEORORORO" << endl;
		}
	}
	catch (result r) {
		cout << r;
		cout << "caught some sort of rerrorrrr" << endl;
	}
    return 0;
}

