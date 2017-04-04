#pragma once
#include <iostream>
#include <fstream>
#include "game_piece.h"
#ifndef GAMEBOARD_H
#define GAMEBOARD_H


int read_dimension(ifstream &, unsigned &, unsigned &);

int read_board(ifstream &, vector<game_piece> &, unsigned, unsigned);

ostream& print_board(ostream&, int, const vector<game_piece> &, unsigned int, unsigned int);


#endif
