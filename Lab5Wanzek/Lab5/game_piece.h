/*
	game_piece.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	header for game_piece struct.
*/

#ifndef game_piece_h
#define game_piece_h

#include <string>
#include "piece_color.h"

using namespace std;

struct game_piece{
	game_piece();
	game_piece(piece_color c, string n, int x, int y);
	bool operator< (const game_piece &) const;
	bool operator== (const game_piece &) const;
	piece_color color;
	string name;
	int x_;
	int y_;

};

#endif