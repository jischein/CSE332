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
int read_dimension(ifstream & file, unsigned & dim_x, unsigned & dim_y) {

	string line;
	//counter to tell how many extractions were successfull 
	int num_success = 0;

	if (file.is_open()) {

		if (getline(file, line)) {

			istringstream iss(line);

			if (iss >> dim_x) {
				num_success++;
			}

			if (iss >> dim_y) {
				num_success++;
			}

		}
		else {
			cout << "FAILED TO READ LINE" << endl;
			cerr << failToReadLine << endl;
			return failToReadLine;
		}

	}

	else {
		cout << "FAILED TO OPEN FILE" << endl;
		cerr << failToOpen << endl;
		return failToOpen;
	}
	//if both board dimensions were extracted, success
	if (num_success == 2) {
		return success;
	}

	else if (num_success == 1) {
		cout << "FAILED TO EXTRACT BOTH DIMENSIONS" << endl;
		cerr << failToGrabDimensions << endl;
		return failToGrabDimensions;
	}

	else {
		cout << "LINE WAS READ BUT FAILED TO EXTRACT DIMENSIONS" << endl;
		cerr << failToGrabDimensions << endl;
		return failToGrabDimensions;
	}

}

int read_board(ifstream & file, vector<game_piece> & pieces, unsigned dim_x, unsigned dim_y) {
	string line;
	//counter to tell how many extractions were successfull 
	int successful_pieces = 0;

	if (file.is_open()) {

		while (getline(file, line)) {
			string name;
			string representation;
			string color;
			unsigned pos_x = 0;
			unsigned pos_y = 0;

			istringstream iss(line);

			if (iss >> color) {

				if (iss >> name) {

					if (iss >> representation) {

						if (iss >> pos_x) {

							if (iss >> pos_y) {

								piece_color color_transform = string_to_pieceColor(color);

								if (pos_x < dim_x) {

									if (pos_y < dim_y) {

										int index = (dim_x)* pos_y + pos_x;

										game_piece piece = game_piece(color_transform, name, representation);

										pieces[index] = piece;

										successful_pieces++;

									}
								}
							}
						}
					}
				}
			}
		}
	}

	else {
		cout << "FAILED TO OPEN FILE" << endl;
		cerr << failToOpen << endl;
		return failToOpen;
	}

	//if at least one piece was read successfully, success
	if (successful_pieces >= 1) {
		return success;
	}

	else {
		cout << "LINE WAS READ BUT NO PIECES WERE GRABBED SUCCESSFULLY" << endl;
		cerr << failToGrabPieces << endl;
		return failToGrabPieces;
	}

}

ostream& print_board(ostream &o, int spacing, const vector<game_piece> & board, unsigned int dim_x, unsigned int dim_y) {

	unsigned int ind;
	ostringstream board_disp;
	board_disp << left;

	//int length = board.size()
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