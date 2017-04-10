#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileParser.h"
#include "game_piece.h"
#include "game_board.h"


using namespace std;
//function that reads board game dimensions


ostream& print_board(ostream &o, int spacing, const vector<game_piece> & board, unsigned int dim_x, unsigned int dim_y) {

	unsigned int ind;
	ostringstream board_disp;
	board_disp << left;

	if (board.size() != dim_x * dim_y) {

		cout << "BOARD MAINTAINS MORE PIECES THAN SPACE AVAILABLE" << endl;
		cerr << tooManyPieces << endl;
		throw tooManyPieces;

	}


	else {
		cout << endl;
		for (unsigned int row = dim_y ; row > 0; --row) {
			board_disp << row - 1; //display indeces
			
			for (unsigned int col = 0; col < dim_x; ++col) {
				ind = (dim_x * (row - 1)) + col;
					if (!board[ind].representation.empty()) {
						board_disp.width(spacing + 2);
						board_disp << board[ind].representation;
					}
					else {
						throw invalidGamePiece;
					}
			}
			board_disp << '\n';
	}
		board_disp << " ";

		//display col indeces
		
		for (unsigned int k = 0; k < dim_x; ++k) {
			board_disp.width(spacing + 2);
			board_disp << k;
		}

		o << board_disp.str() << endl;
		return o;
	}
}
