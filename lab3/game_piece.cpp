#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream> 
#include <sstream>
#include <fstream>
#include "FileParser.h"
#include "game_piece.h"

using namespace std;

string piece_color_toString(piece_color color) {

	switch (color) {

	case red:
		return "red";

	case black:
		return "black";

	case white:
		return "white";

	case brown:
		return "brown";

	case no_color:
		return "no color";

	case invalid_color:
		return "invalid color";

	default:
		break;
	}
}

piece_color string_to_pieceColor(string &color) {
	make_lowercase(color);

	if (color == "red") {
		return piece_color::red;
	}

	else if (color == "black") {
		return piece_color::black;
	}

	else if (color == "white") {
		return piece_color::white;
	}

	else if (color == "brown") {
		return piece_color::brown;
	}

	else if (color == " " || color == "	" || color == "no_color") {
		return piece_color::no_color;
	}

	else {
		return piece_color::invalid_color;
	}
}

game_piece::game_piece()
	:color(no_color), name(""), representation(" ")
{}

game_piece::game_piece(piece_color the_color, string the_name, string the_representation)
	: color(the_color), name(the_name), representation(the_representation)
{}

