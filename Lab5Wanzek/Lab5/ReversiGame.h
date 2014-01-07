/*
	ReversiGame.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	ReversiGame class declarations
*/

#ifndef ReversiGame_h
#define ReversiGame_h

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

using namespace std;

class ReversiGame : public GameBase{

friend ostream &operator<<(ostream &os, const ReversiGame & game); 
//allows the operator << to access private variables in this class

public:
	ReversiGame(ifstream, string, string);
	virtual bool done();
	virtual void prompt(int &, int &);
	virtual void turn();
	virtual void print();
	virtual void save();
	virtual vector<pair<int,int>> checkMoves(string);
	virtual bool findPiece(vector<game_piece>::iterator &, vector<game_piece>::iterator &, int, int);
	virtual void flip(int, int, string);
	virtual bool checkOpposite(int, int, int, int, string);
	//additional methods unique to Reversi are checkMoves, findPiece, flip and checkOpposite

protected:
	static const int length = 1;
	string blackPiece;
	string whitePiece;
	string firstName;
	string secondName;
	string currentPlayer;

private:
	ReversiGame(const ReversiGame &);
	ReversiGame & operator=(const ReversiGame &);
};

#endif