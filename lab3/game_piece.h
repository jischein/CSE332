#pragma once
#include <vector>
#include <string>
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

using namespace std;

enum piece_color { red, black, white, brown, invalid_color, no_color };



struct game_piece {

public:

	piece_color color;
	string name;
	string representation;

	game_piece();
	game_piece(piece_color color, string name, string look);



};

#endif
