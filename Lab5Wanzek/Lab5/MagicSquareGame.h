/*
	MagicSquareGame.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	MagicSquareGame class declarations
*/

#ifndef MagicSquareGame_h
#define MagicSquareGame_h

#include <string>
#include "piece_color.h"
#include "game_piece.h"
#include "error_codes.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GameBase.h"

#include "NumberedGamePiece.h" // new

using namespace std;

class MagicSquareGame : public GameBase{

friend ostream &operator<<(ostream &os, const MagicSquareGame & game); //allows the operator << to access private variables in this class

public:
	MagicSquareGame(ifstream);
	virtual bool done();
	virtual void prompt(int &, int &);
	virtual void prompt(int &);
	virtual void turn();
	virtual void print();
	virtual void save();
	vector<NumberedGamePiece> numbers;

protected:
	static const int length = 1;

private:
	MagicSquareGame(const MagicSquareGame &);
	MagicSquareGame & operator=(const MagicSquareGame &);
};

#endif