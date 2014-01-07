/*
	game_piece.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	struct that contains the values of pieces, colors and their location on a board.
	Also contains operators to enable sorting and comparisons.
*/
#include "stdafx.h"
#include "game_piece.h"
#include "NumberedGamePiece.h"
#include "piece_color.h"
#include <string>

using namespace std;

NumberedGamePiece::NumberedGamePiece(piece_color c, string n, int x, int y, int num)
	:game_piece(c,n,x,y), number(num) {}
