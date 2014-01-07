/*
	NineAlmondsGame.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	NineAlmondsGame class declarations
*/

#ifndef NineAlmondsGame_h
#define NineAlmondsGame_h

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

class NineAlmondsGame : public GameBase{

friend ostream &operator<<(ostream &os, const NineAlmondsGame & game); 
//allows the operator << to access private variables in this class

public:
	NineAlmondsGame(ifstream);
	virtual bool done();
	virtual void prompt(int &, int &);
	virtual void turn();
	virtual void print();
	virtual void save();

protected:
	static const int almondLength = 1;
	string piece; 

private:
	NineAlmondsGame(const NineAlmondsGame &);
	NineAlmondsGame & operator=(const NineAlmondsGame &);
	
};

#endif