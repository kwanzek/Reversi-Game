/*
	MagicSquareGame.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	MagicSquareGame class definitions
*/

#include "stdafx.h"
#include "MagicSquareGame.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "game_piece.h"
#include "piece_color.h"
#include "error_codes.h"
#include "NumberedGamePiece.h"

using namespace std;

ostream& operator<< (ostream &os, const MagicSquareGame & game){
	//Simple print method, similar to the last lab

	bool b=false;
	int j = game.y_-1;
	for(j; j>=0; --j){
		os<<endl;
		os<<j<<":"; //printing the numbers on the left
		for(unsigned int i = 0; i<game.x_; ++i){
			for(vector<NumberedGamePiece>::const_iterator it = game.numbers.begin(); it != game.numbers.end(); it++){  //switched to numbers
				NumberedGamePiece gp = *it;
					if(gp.x_ == i && gp.y_ == j){
						os<<setw(game.maxLength); //make sure each print is a certain length
						os<<gp.number;
						b = true;
					}
			}
			if(!b){ //no piece could be found at i,j
				
				os<<setw(game.maxLength);
				os << " "; //print a space
			}
			b=false; //reset b so we can use it again in the next loop
		}
	}

	os << endl;
	os<<"X:" << "0" << setw(game.maxLength) << "1" << setw(game.maxLength)<<"2"<<endl<<endl; //printing the numbers on the bottom
	os<<"Available pieces: ";
	for(vector<NumberedGamePiece>::const_iterator it = game.numbers.begin(); it != game.numbers.end(); it++){  //switched to numbers
				NumberedGamePiece gp = *it;
					if(gp.x_ == -1 && gp.y_ == -1){
						os<<gp.number << " ";
					}
			}
	os<<endl;
	return os;
} 

MagicSquareGame::MagicSquareGame(ifstream ifs){
	x_ = 3;
	y_ = 3;
	maxLength = length;

	string s = "";
	string s2 = "";
	string s3 = "";
	bool a = false;
	bool failed = false;
	int x=0;
	int y=0;
	int z=0;
	ifs.open("MagicSquare.txt"); //attempt to load
	if(ifs.is_open()){
		getline(ifs, s);
		if(s.compare("MagicSquare")==0){
			while(!ifs.eof()){
				getline(ifs, s);
				istringstream iss(s);
				bool one = (iss >> s)!=0; 
				bool two = (iss >> s2)!=0; 
				bool three =(iss >> s3)!=0;
			if(one&&two&&three){
				stringstream convert (s);
				stringstream convert2 (s2);
				stringstream convert3 (s3);
				if(s.compare("")==0)
					continue;
				if((convert>>x) && convert2>>y && convert3>>z)
				{
					numbers.push_back(NumberedGamePiece(white, "number", x, y, z)); //push the values we got from the file as new pieces into the vector
				}
				else{
					failed=true; //any failures, we need to start from scratch
					cout << "Failed to load"<<endl;
				}
			}
		}
			if(!failed) //no failures, loaded successfully
				return;
		}
	}
	numbers.clear(); //clear the vector if we failed to load successfully
	for(int i = 1; i < 10; ++i){
		numbers.push_back(NumberedGamePiece(white, "number", -1, -1, i)); //add all these pieces to the game, but not the board
	}
}
bool MagicSquareGame::done(){
	//hard coded to check a 3 by 3 square for columns and rows summing to 15
	//switch on x to get the three cases and switch on y each time to get the 3 cases for y
	int columnZero = 0;
	int columnOne = 0;
	int columnTwo = 0;
	int rowZero = 0;
	int rowOne = 0;
	int rowTwo = 0;
	int diagDownRight = 0;
	int diagUpLeft = 0;
	
	for(vector<NumberedGamePiece>::const_iterator it = (*this).numbers.begin(); it != (*this).numbers.end(); it++){  //switched to numbers
		NumberedGamePiece gp = *it;
		int x = gp.x_;
		int y = gp.y_;
		int num = gp.number;
		switch(x){
		case 0:
				switch(y){
				case 0:
					
					columnZero+=num;
					rowZero+=num;
					diagUpLeft+=num;
					break;
				case 1:
					columnZero+=num;
					rowOne+=num;
					break;
				case 2:
					columnZero+=num;
					rowTwo+=num;
					diagDownRight+=num;
					break;
				default:
					cout<<"This piece is number " << num << endl;
				}
				break;
		case 1:
			switch(y){
				case 0:
					columnOne+=num;
					rowZero+=num;
					break;
				case 1:
					columnOne+=num;
					rowOne+=num;
					diagDownRight+=num;
					diagUpLeft+=num;
					break;
				case 2:
					columnOne+=num;
					rowTwo+=num;
					break;
				default:
					cout<<"This piece is number " << num << endl;
				}
			break;
		case 2:
			switch(y){
				case 0:
					columnTwo+=num;
					rowZero+=num;
					diagDownRight+=num;
					break;
				case 1:
					columnTwo+=num;
					rowOne+=num;
					break;
				case 2:
					columnTwo+=num;
					rowTwo+=num;
					diagUpLeft+=num;
					break;
				default:
					cout<<"This piece is number " << num << endl;
				}
		break;
		}
	}
	//if all are equal to 15, we are done so return true
	if(columnZero==15 && columnOne==15 && columnTwo==15 && rowZero==15 && 
		rowOne==15 && rowTwo==15 && diagDownRight==15 && diagUpLeft==15){
		ofstream ofs("MagicSquare.txt");
		ofs<<"NODATA"<<endl;
		return true;
	}
	else
		return false;
}

void MagicSquareGame::prompt(int &a, int &b){
	//old prompt
	string s1;
	string s2;
	bool one = false;
	bool two = false;
	bool finished = false;
	while(!finished){
		getline(cin, s1); 
		replace(s1.begin(), s1.end(), ',', ' ');
		istringstream iss(s1);
		bool one = (iss >> s1)!=0; 
		bool two = (iss >> s2)!=0; 

		if(one){
			if(s1.compare("quit")==0){
				throw quit; //if string received is quit, throw quit exception
			}
			else if(s1.compare("done")==0){
				throw turnover; //otherwise throw the turnover exception if the string is "done"
			}
			
			//try to extract numbers			
			else{
				stringstream convert (s1);
				if(!(convert>>a))
				{
					cout<<"Please enter a either 'quit' or a xy coordinates in the form 'x, y'"<<endl;
					continue; //try to get the user to enter correct information again
				}
				else{
					if(two){
						stringstream convert2 (s2);
						if(!(convert2>>b)){
							cout<<"Please enter a either 'quit' or a xy coordinates in the form 'x, y'"<<endl;
							continue; //please enter the correct info!
						}
						else{
							finished = true; //got both numbers, we are done here
						}
					}
					else{
						cout<<"Please enter a either 'quit' or a xy coordinates in the form 'x, y'"<<endl;
						continue; //second value wasn't a number, please enter a number there!
					}
				}
			}
		}
	}
}

void MagicSquareGame::prompt(int & in){
	//new prompt, per lab spec asks for one digit at a time for the coordinate and then the number
	string s1;
	bool one = false;
	bool finished = false;
	while(!finished){
		getline(cin, s1); 	
		istringstream iss(s1);
		bool one = (iss >> s1)!=0; 
		if(one){
			if(s1.compare("quit")==0){
				throw quit; //if string received is quit, throw quit exception
			}
			else{
				stringstream convert (s1);
					if(!(convert>>in))
					{
						cout<<"Please enter quit or a proper input"<<endl<<endl;
						continue; //try to get the user to enter correct information again
					}
					else{
						finished = true;
						break;
					}
			}
		}
	}
}

void MagicSquareGame::turn(){
	//remade turn method
	//asks for single digits at a time as per lab spec to 
	//construct XY coordinates and then find the piece the user wants

	int x1 = 0, y1=0, num=0;
	int x=x_; //for checking bounds without hard coded constants
	int y=y_;

	bool goodLoc=false;
	while(!goodLoc){ //all this is for ensuring X is available
		cout << "Please enter the X coordinate of the space you wish to place a piece on (or enter quit to end)." << endl;
		try{
			prompt(x1);
		}
		catch(error_codes & e){
			if(e==quit){
				save();
				throw quit;
			}
		}
		if(x1<0 || x1>(x-1)){
			cout<<"This X location is outside the scope of this board! Please enter a location inside the board!"<<endl;
			continue;
		}
		else{
			goodLoc=true;
		}
	}
	goodLoc = false;

	while(!goodLoc){ //this all grabs the Y locations, giving us an X/Y location
		cout << "Please enter the Y location you want to place a piece at (or enter quit to end)!" << endl;
		try{
			prompt(y1);
		}
		catch(error_codes & e){
			if(e==quit){
				save();
				throw quit;
			}
		}
		if(y1<0 || y1>(y-1)){
			cout<<"This Y location is outside the scope of this board! Please enter a location inside the board!"<<endl;
			continue;
		}
		else{
			goodLoc=true;
		}
	}

	goodLoc=false;

	for(vector<NumberedGamePiece>::const_iterator it = (*this).numbers.begin(); it != (*this).numbers.end(); it++){
		NumberedGamePiece gp = *it;
			if(gp.x_ == x1 && gp.y_ == y1){
				cout<<"A piece already occupies this location!"<<endl;
				return;
			}
	}

	while(!goodLoc){ //next loop is to grab the piece the player wants
		cout << "Please enter the number of an available piece you wish to move (or enter quit to end)" << endl;
		try{
			prompt(num);
		}
		catch(error_codes & e){
			if(e==quit){
				save();
				throw quit;
			}
		}
			for(unsigned int j=0; j < numbers.size(); ++j){
						if(numbers[j].number==num && numbers[j].x_==-1 && numbers[j].y_ ==-1){ //if it's not on the board, put it on the board
							numbers[j].x_=x1;
							numbers[j].y_=y1;	
							goodLoc=true;
						}
					}
				if(!goodLoc){
					cout<<"This piece is unavailable for movement!"<<endl<<endl;
				}
				continue;
		if(!goodLoc)
			cout<<"This piece is not available!"<<endl;
	}

	print();
}

void MagicSquareGame::print(){
	cout << (*this);
}

void MagicSquareGame::save(){ //called whenever a player would quit, or when done() is true
	ofstream ofs("MagicSquare.txt");
	cout << "Would you like to save? (yes/no)" << endl;
	string s1;
	bool one = false;
	getline(cin, s1); 
	istringstream iss(s1);
	one = (iss >> s1)!=0; 
	if(one){
		if(s1.compare("yes")==0){ //player wants to save
			ofs<<"MagicSquare"<<endl; 
			for(unsigned int i = 0; i < numbers.size(); ++i){
				ofs << numbers[i].x_ << " " << numbers[i].y_ << " " << numbers[i].number<< endl; //store each piece after MagicSquare
			}
			return;
		}
		else{
			ofs<<"NODATA"<<endl; //clear data if not yes, in all cases
			return;
		}
	}
	
}