/*
	ReversiGame.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	ReversiGame class definitions
*/

#include "stdafx.h"
#include "ReversiGame.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "game_piece.h"
#include "piece_color.h"
#include "error_codes.h"

using namespace std;

ostream& operator<< (ostream &os, const ReversiGame & game){
	bool b=false;
	int j = game.y_-1;
	for(j; j>=0; --j){
		os<<endl;
		os<<j; //printing the numbers on the left
		for(unsigned int i = 0; i<game.x_; ++i){
			for(vector<game_piece>::const_iterator it = game.v.begin(); it != game.v.end(); it++){ 
				game_piece gp = *it;
					if(gp.x_ == i && gp.y_ == j){
						os<<setw(game.maxLength); //make sure each print is a certain length
						if(gp.name.compare("black")==0)
							os<<game.blackPiece;
						else
							os<<game.whitePiece;
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
	os<<"X" << "0" << setw(game.maxLength) << "1" << setw(game.maxLength)<<"2"<<setw(game.maxLength)<<"3" << setw(game.maxLength)<<
		"4"<< setw(game.maxLength)<<"5"<< setw(game.maxLength)<<"6" << setw(game.maxLength)<<"7"<<endl; //printing the numbers on the bottom
	return os;
} 

ReversiGame::ReversiGame(ifstream ifs, string first, string second){
	x_ = 8;
	y_ = 8;
	blackPiece = "X";
	whitePiece = "O";
	maxLength = length;
	firstName = first;
	secondName = second;
	currentPlayer = first;

	string s = "";
	string s2 = "";
	string s3 = "";
	bool a = false;
	bool failed = false;
	int x=0;
	int y=0;
	ifs.open("Reversi.txt");
	if(ifs.is_open()){
		getline(ifs, s);
		if(s.compare("Reversi")==0){
			getline(ifs, s);
			currentPlayer=s;
			getline(ifs,s);
			firstName=s;
			getline(ifs,s);
			secondName=s;

			//if we have a save file, the save file is structured to remember turn order and previous names
			
			while(!ifs.eof()){
				getline(ifs, s);
				istringstream iss(s);
				bool one = (iss >> s)!=0; 
				bool two = (iss >> s2)!=0; 
				bool three = (iss >> s3)!=0;
			if(one&&two&&three){
				stringstream convert (s);
				stringstream convert2 (s2);
				if(s.compare("")==0)
					continue;
				if((convert>>x) && convert2>>y)
				{
					if(s3.compare("black")==0)
						v.push_back(game_piece(black, "black", x, y));
					else
						v.push_back(game_piece(white, "white", x, y));
				}
				else{
					failed=true; //once again, if we failed to load we want to clear the vector later
					cout << "Failed to load"<<endl;
				}
			}
		}
			if(!failed) //if no failure, we have loaded successfully
				return;
		}
	}
	v.clear();
	v.push_back(game_piece(black, "black", 3, 3));
	v.push_back(game_piece(black, "black", 4, 4));
	v.push_back(game_piece(white, "white", 3, 4));
	v.push_back(game_piece(white, "white", 4, 3));
}

bool ReversiGame::done(){
	int blacks = 0;
	int whites = 0;
	for(vector<game_piece>::iterator iter = v.begin(); iter!=v.end(); ++iter){ //how many black pieces and white pieces are on the board?
		if((*iter).name.compare("black")==0){
			++blacks;
		}
		else{
			++whites;
		}
	}
	if((blacks==0 && whites > 0)|| (blacks > 0 && whites==0)){ //if no pieces of one color, we are done
		ofstream ofs("Reversi.txt");
		ofs<<"NODATA"<<endl;
		if(blacks>whites){
			cout<<firstName<<" wins!"<<endl;
		}
		else if(whites>blacks){
			cout<<secondName<<" wins!"<<endl;
		}
		else{
			cout<<"It's a tie!"<<endl;
		}
		return true;
	}
	else{
		if(v.size()>=64){ //easy way to check if all spaces have been filled, we are done again
			ofstream ofs("Reversi.txt");
			ofs<<"NODATA"<<endl;

			if(blacks>whites){
				cout<<firstName<<" wins!"<<endl;
			}
			else if(whites>blacks){
				cout<<secondName<<" wins!"<<endl;
			}
			else{
				cout<<"It's a tie!"<<endl;
			}

			return true;
		}
		else{
			vector<pair<int,int>> blackMoves = checkMoves(firstName);
			vector<pair<int,int>> whiteMoves = checkMoves(secondName); //if neither player has a move, we are also done
			if(blackMoves.size() == 0 && whiteMoves.size() == 0){
				ofstream ofs("Reversi.txt");
				ofs<<"NODATA"<<endl;

				if(blacks>whites){
					cout<<firstName<<" wins!"<<endl;
				}
				else if(whites>blacks){
					cout<<secondName<<" wins!"<<endl;
				}
				else{
					cout<<"It's a tie!"<<endl;
				}

				return true;
			}
		}
	}
	return false;
}

void ReversiGame::prompt(int &a, int &b){
	//same as before
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

void ReversiGame::turn(){
	cout<<currentPlayer<<" it is your turn!"<<endl<<endl; 
	vector<pair<int,int>> moves = checkMoves(currentPlayer); //check if the player has moves
	if(moves.size()==0){
		cout<< "Sorry "<< currentPlayer << " but there are no moves available for you!"<<endl<<endl;
		if(currentPlayer.compare(firstName)==0)
			currentPlayer=secondName;
		else
		currentPlayer=firstName;

		cout<<*this<<endl;
		return;
	}
	int x1 = 0;
	int y1 = 0;
	bool goodLoc = false;
	while(!goodLoc){
		cout << "Please enter the location of a valid move location (X,Y) or quit to end" << endl;
		try{
			prompt(x1, y1);
		}
		catch (error_codes & e){
			if(e==quit){
				save();
				throw quit;
			}
		}

		if(x1<0 || x1>(int(x_)-1) || y1<0 || y1>(int(y_)-1)){
			cout<<"This XY location is outside the scope of this board! Please enter a valid location or enter quit!"<<endl;
			continue;
		}
		for(unsigned int i = 0; i < moves.size(); ++i){
			if(moves[i].first==x1 && moves[i].second == y1){
				goodLoc=true; //the x,y coordinates match a location in moves, so it is good
				break;
			}
		}
		if(!goodLoc){
			cout<<"This location is not a valid move location!"<<endl;
		}
	}
	string newPiece = "";
	if(currentPlayer.compare(firstName)==0){
		v.push_back(game_piece(black, "black", x1, y1)); //push back appropriate color piece
		newPiece = "black";
	}
	else{
		v.push_back(game_piece(white, "white", x1, y1));
		newPiece = "white";
	}
	flip(x1,y1,newPiece); //flips pieces that are now "flanked" by the color placed

	if(currentPlayer.compare(firstName)==0) //switch players
		currentPlayer=secondName;
	else
		currentPlayer=firstName;

	cout<<*this<<endl;
}

void ReversiGame::print(){
	cout << (*this);
}

void ReversiGame::save(){
	ofstream ofs("Reversi.txt");
	cout << "Would you like to save? (yes/no)" << endl;
	string s1;
	bool one = false;
	bool finished = false;
	getline(cin, s1); 
	istringstream iss(s1);
	one = (iss >> s1)!=0; 
	if(one){
		if(s1.compare("yes")==0){
			ofs<<"Reversi"<<endl;
			ofs<<currentPlayer<<endl; //stores player names here
			ofs<<firstName<<endl;
			ofs<<secondName<<endl;
			
			for(unsigned int i = 0; i < v.size(); ++i){
				ofs << v[i].x_ << " " << v[i].y_ <<" " << v[i].name<<endl; //store pieces
			}
			return;
		}
		else{
			ofs<<"NODATA"<<endl; //if not yes, clear anyway
			return;
		}
	}
}

vector<pair<int,int>> ReversiGame::checkMoves(string s){ //returns a vector of pairs that contains all moves playerName s can make
	vector<pair<int,int>> moves;
	int x=0;
	int y=0;
	int deltaX=0;
	int deltaY=0;
	bool notDone = true;

	if(s.compare(firstName)==0)
		s="black";
	else
		s="white";

	game_piece temp;
	vector<game_piece>::iterator iter = v.begin();

	for(unsigned int i=0; i <v.size(); ++i){
		if(v[i].name.compare(s)==0){
			x = v[i].x_;
			y = v[i].y_;
			for(int j = x-1; j < x+2; ++j)
				for(int k = y-1; k<y+2; ++k){ //check the squares around a piece, but not itself
					if(!(j==x && k==y)){
						if(findPiece(iter,v.end(), j, k)){ //if we find a piece
							temp = *iter;
							deltaX = temp.x_ - x;
							deltaY = temp.y_ - y;
							if(temp.name.compare(s)!=0){ //and the piece isn't our color
								while(notDone){
									int pieceX = temp.x_ + deltaX; //keep looking to try and find a same color piece on the other side
									int pieceY = temp.y_ + deltaY;
									iter = v.begin();
									if(temp.x_ + deltaX < 0 || temp.x_ + deltaX > 7 ||temp.y_ + deltaY < 0 || temp.y_ + deltaY > 7){
										break; //if we are outside the board range, there is no possible move with this piece
									} 
									if(findPiece(iter,v.end(), pieceX, pieceY)){
										temp = (*iter);
										if(temp.name.compare(s)==0)
											break; //if we find our own piece, this direction no longer works
									}
									else{//empty space!, add it to moves
										pair<int,int> p;
										p.first = pieceX;
										p.second = pieceY;
										moves.push_back(p);
										break;
									}
								}
							}
						}
					}
					iter = v.begin();
				}
				iter = v.begin(); //these are resets for the findPiece method
		}
		iter=v.begin();
	}
	return moves;
}

bool ReversiGame::findPiece(vector<game_piece>::iterator & begin, vector<game_piece>::iterator & end, int a, int b){
	//simple method, iterates beginning to end, and begin is stored as a reference to be dereferenced in other methods
	while(begin!=end){
		if((*begin).x_==a && (*begin).y_==b){
			return true;
		}
		++begin;
	}
	return false;
}

void ReversiGame::flip(int x, int y, string s){
	//similar to checkMoves, but works from the location specified by the player and fans out, flipping pieces as necessary
	game_piece temp;
	vector<game_piece>::iterator iter = v.begin();
	int deltaX = 0;
	int deltaY = 0;
	for(int i = x-1; i < x+2; ++i)
		for(int j = y-1; j<y+2; ++j){ //check squares around the new piece location
			if(!(i==x && j==y)){
				iter=v.begin();
				if(findPiece(iter,v.end(), i, j)){
					temp = *iter;
					deltaX = temp.x_ - x;
					deltaY = temp.y_ - y;
					if(temp.name.compare(s)!=0){
						if(!checkOpposite(x, y, deltaX, deltaY, s)){ //if we can't find a piece that completes the "flank" with our new piece in this direction, we cannot flip
							continue;
						}
						(*iter).name = s;
						int pieceX = temp.x_;
						int pieceY = temp.y_;
						while(true){
							pieceX+=deltaX;
							pieceY+=deltaY;
							iter = v.begin();

							if(temp.x_ + deltaX < 0 || temp.x_ + deltaX > 7 ||temp.y_ + deltaY < 0 || temp.y_ + deltaY > 7){
								break;
							} 
							if(findPiece(iter,v.end(), pieceX, pieceY)){
								if((*iter).name.compare(s)==0){
									break; //if we hit our own piece we stop
								}
								else{
									(*iter).name = s; //flip!
								}
							}
							else{
								continue;
								}
							}
					}
			}
		}
			iter=v.begin();
	}
		iter=v.begin(); //reset for findPiece
}

bool ReversiGame::checkOpposite(int x, int y, int deltaX, int deltaY, string s){
	//starts at a location, takes a direction (deltaX and deltaY) and tries to find a piece in
	//the appropriate direction that completes a "flank" with the piece the player just added
	vector<game_piece>::iterator iter = v.begin();
	game_piece gp;
	while(true){
		iter=v.begin();
		x+=deltaX;
		y+=deltaY;
		if(x < 0 || x > 7 ||y< 0 ||y > 7){
			return false;
		}
		if(findPiece(iter, v.end(), x, y)){
			gp = *iter;
			if(gp.name.compare(s)==0){
				return true;
			}
		}
		else{
			return false;
		}
	}
	return false;
}