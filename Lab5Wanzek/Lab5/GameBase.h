/*
	GameBase.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	GameBase class definitions
*/

#ifndef GameBase_h
#define GameBase_h

#include <iostream>
#include <string>
#include <vector>
#include "game_piece.h"
#include "piece_color.h"
#include "error_codes.h"


using namespace std;

class GameBase{

public:
	GameBase(){};
	virtual bool done() = 0;
	virtual void prompt(int &, int &) = 0;
	virtual void turn() = 0; 
	int play();
	virtual void print() = 0;
	virtual void save() = 0;

	static GameBase * instance();
	static void create(int argc, char * argv[]);

protected:
	unsigned int x_;
	unsigned int y_;
	vector<game_piece> v;
	int maxLength;
	static GameBase * game;
};

#endif