/*
	Lab5.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	Main class that handles all the major functions.
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameBase.h"
#include "error_codes.h"

using namespace std;

int usage(char name[], string &s);

int main(int argc, char * argv[])
{
	try{
		GameBase::create(argc, argv);
	}
	catch(error_codes & e){
		if(e==badname || e==notcorrectarguments){
			string s = "and then NineAlmonds or MagicSquare or Reversi. If using Reversi, please also provide the names of both players seperated by a space.";
			return usage(argv[0], s);		
		}
		
		return e;
	}
	int x = 0;
	try{
		GameBase::instance();
	}
	catch(error_codes & e){
		return e;
	}
		try{
			x = GameBase::instance()->play();
		}
		catch(error_codes & e){
			delete GameBase::instance();
			return e;
		}
	
	delete GameBase::instance();
	return x;
}

int usage(char name[], string &s){
	cout << "To use this program, type "<< name << " " << s << endl;
	return helpcode;
}
