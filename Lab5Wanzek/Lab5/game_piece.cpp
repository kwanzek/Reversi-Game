/*
	game_piece.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	struct that contains the values of pieces, colors and their location on a board.
	Also contains operators to enable sorting and comparisons.
*/
#include "stdafx.h"
#include "game_piece.h"
#include "piece_color.h"
#include <string>

using namespace std;

game_piece::game_piece(){}

game_piece::game_piece(piece_color c, string n, int x, int y)
	:color(c), name(n), x_(x), y_(y) {}

bool
	game_piece::operator<(const game_piece &  gp) const{
		return (color < gp.color)
			|| ((color == gp.color) && (name.compare(gp.name) < 0));
	}

bool
	game_piece::operator==(const game_piece &  gp) const{
		return (color == gp.color) && (name.compare(gp.name)==0);
	}