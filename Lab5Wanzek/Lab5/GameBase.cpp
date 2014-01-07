/*
	GameBase.h
	by: Kyle Wanzek (kwanzek@gmail.com)

	GameBase class definitions
*/


#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"
#include "ReversiGame.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <vector>
#include "game_piece.h"
#include "piece_color.h"
#include "error_codes.h"


using namespace std;

GameBase * GameBase::game = 0;

int GameBase:: play(){
	//simple method that prints the board each turn
	//calls a turn and checks if a quit error is thrown out, throwing it to main
	//if no error gets thrown and the user wins, prints the number of turns needed!

		print();
		while(!done()){
			try{
				turn();
			}
			catch(error_codes & e){
				if(e==quit){
					throw quit;
				}
			}
		}
		return 0;
	}

void GameBase::create(int argc, char * argv[]){
	if(game!=0){
		throw gamealreadycreated; //changed in accordance with singleton pattern
	}
	else{
		if(argc == 2){
			if(string(argv[1]).compare("NineAlmonds")==0){
				try{
					GameBase * g = new NineAlmondsGame(ifstream(string(argv[1])));
					game = g;
				}
				catch(bad_alloc ba){
					throw couldntalloc;
				}
			}
			else if(string(argv[1]).compare("MagicSquare")==0){
				try{
					GameBase * g = new MagicSquareGame(ifstream(string(argv[1])));
					game=g;
				}
				catch(bad_alloc ba){
					throw couldntalloc;
				}
			}
			else{
				throw badname;
			}
		}
		else if(argc == 4){
			if(string(argv[1]).compare("Reversi")==0){
				try{
					GameBase * g = new ReversiGame(ifstream(string(argv[1])), string(argv[2]), string(argv[3]));
					game=g;
				}
				catch(bad_alloc ba){
					throw couldntalloc;
				}
			}
			else{
				throw badname;
			}
		}
		else{
			throw notcorrectarguments;
		}
	}
}


GameBase * GameBase::instance(){ //added, in accordance with Singleton pattern
	if(game!=0)
		return game;
	else
		throw nogame;
}