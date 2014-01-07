/*
	game_piece.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	header for NumberedGamePieceStruct struct.
*/

#ifndef NumberedGamePiece_h
#define NumberedGamePiece_h

#include <string>
#include "piece_color.h"
#include "game_piece.h"

using namespace std;

struct NumberedGamePiece: public game_piece{
	NumberedGamePiece(piece_color c, string n, int x, int y, int num);
	int number;

};

#endif