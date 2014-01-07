/*
	NineAlmondsGame.cpp
	by: Kyle Wanzek (kwanzek@gmail.com)

	NineAlmondsGame class definitions
*/

#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "game_piece.h"
#include "piece_color.h"
#include "error_codes.h"

using namespace std;

ostream& operator<< (ostream &os, const NineAlmondsGame & game){
	//Simple print method, similar to the last lab
	//difference lies in using the ostream as opposed to strictly cout so this can be chained.
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
						os<<game.piece;
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
	os<<"X" << "0" << setw(game.maxLength) << "1" << setw(game.maxLength)<<"2"<<setw(game.maxLength)<<"3" << setw(game.maxLength)<<"4"<<endl; //printing the numbers on the bottom
	return os;
} 

NineAlmondsGame::NineAlmondsGame(ifstream ifs){
	x_ = 5;
	y_ = 5;
	piece = "A";
	maxLength = almondLength;

	string s = "";
	string s2 = "";
	bool a = false;
	bool failed = false;
	int x=0;
	int y=0;
	ifs.open("NineAlmonds.txt"); //new code that tries to load from the save file
	if(ifs.is_open()){
		getline(ifs, s);
		if(s.compare("NineAlmonds")==0){
			while(!ifs.eof()){
				getline(ifs, s);
				istringstream iss(s);
				bool one = (iss >> s)!=0; 
				bool two = (iss >> s2)!=0;
			if(one && two){
				stringstream convert (s);
				stringstream convert2 (s2);
				if(s.compare("")==0)
					continue;
				if((convert>>x) && convert2>>y)
				{
					v.push_back(game_piece(brown, "almond", x, y));
				}
				else{
					failed=true; //if something goes wrong, we will start from scratch below
					cout << "Failed to load"<<endl;
				}
			}
		}
			if(!failed) //no failures, we have successfully loaded
				return;
		}
	}
	v.clear(); //clear the vector of all saved pieces if we failed to load and add the normal beginning pieces
	for(int i = 1; i < 4; ++i){
		for(int j = 1; j < 4; ++j){
			v.push_back(game_piece(brown, "almond", i, j)); //add all these pieces to the board
		}
	}
}
bool NineAlmondsGame::done(){
		
	if(v[0].x_ == 2 && v[0].y_ == 2 && v.size()==1){
		ofstream ofs("NineAlmonds.txt");
		ofs<<"NODATA"<<endl;
		return true;
	}
	else{	
		return false; //simple check, to win only one almond should remain at 2,2
	}
}

void NineAlmondsGame::prompt(int &a, int &b){
	
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

void NineAlmondsGame::turn(){
	int x1 = 0, y1=0, x2=0, y2=0;
	int x=x_; //for checking bounds without hard coded constants
	int y=y_;
	vector<int> m; //add moves to a vector
	vector<int> n;
	bool goodLoc = false;
	bool goodPiece = false;
	while(!goodLoc){
		cout << "Please enter the location of the piece you wish to move!" << endl;
		try{
			prompt(x1, y1);
		}
		catch (error_codes & e){ //catching quit codes, if we catch a turnover, keep trying
			if(e==quit){
				save();
				throw quit;
			}
		}

		if(x1<0 || x1>(x-1) || y1<0 || y1>(y-1)){
			cout<<"This XY location is outside the scope of this board! Please enter a location of an almond piece!"<<endl;
			continue;
		}
		for(unsigned int i = 0; i < v.size(); ++i){
			if(v[i].x_==x1 && v[i].y_ == y1){
				goodLoc=true; //the x,y coordinates match the location of a piece on the board!
				//break;
			}
		}
		if(goodLoc){
			m.push_back(x1); //store the turn into the two vectors
			n.push_back(y1);
		}
		else{
			cout<<"This location is not a piece on the game board!"<<endl;
		}
	}

	goodLoc = false;

	while(true){
		cout<<*this<<endl;
		cout<<"Enter a valid move. (Enter 'done' to end your turn or quit to end the game)"<<endl;
		try{
			prompt(x2, y2);
		}
		catch(error_codes & e){
			if(e==quit){
				save();
				throw quit; 
			}
			else{
				//print the turns it took
				if(goodLoc){	//this if statement checks to make sure that at least one move is made
								//frankly I don't think it makes sense to force them to make a move, for example if they
								//entered the location of a piece that has no adjacent pieces.
								//If this if statement and its other bracket are removed it will print out
								//just the location the user entered should no move be made
								//and allow the user to continue on should they choose
					for(unsigned int i = 0; i < m.size()-1; ++i){
						cout<<m[i]<<", "<<n[i]<<" to ";
					}
					cout<<m[m.size()-1]<<", "<<n[m.size()-1]<<endl;
					m.erase(m.begin(),m.end());
					n.erase(n.begin(),n.end());
					return;
				}
				else{
					cout<<"Please enter at least one valid move and if you can't, please type quit!"<<endl; 
					continue; //as said above, if the user can enter done without making a move
							  //this else can be removed with the corresponding if.
				}
			}
		}
		if(x1==x2 && y1==y2){
			cout << "You entered the same location, please enter a valid move!"<<endl;
			continue;
		}
		if(x2<0 || x2>(x-1) || y2<0 || y2>(y-1)){
			cout << "You entered XY coordinates outside of this board!"<<endl;
			continue;
		}
		if((abs(x2-x1) == 2 || abs(x2-x1)==0) &&(abs(y2-y1) == 2 || abs(y2-y1)==0) && x2>=0 && x2<=4 && y2>=0 && y2<=4){
			int lowX=0, lowY=0;		//this section is to grab the proper location for where the piece-to-be-jumped is
									//we take the lower x and y and add half the distance between them
									//I could simply add 1 to both X and Y (as you can only jump 1 space at a time)
									//but I feel this method is more robust should another type of jumping game be used
			if(x1<x2)
				lowX=x1+abs(x2-x1)/2;
			else
				lowX=x2+abs(x2-x1)/2;
			if(y1<y2)
				lowY=y1+abs(y2-y1)/2;
			else
				lowY=y2+abs(y2-y1)/2;

			for(vector<game_piece>::iterator it = v.begin(); it != v.end(); it++){
				game_piece gp = *it;
				if(gp.x_==lowX && gp.y_==lowY){
					v.erase(it); //if we find a piece with the x/y between the two inputs, delete it
					goodPiece=true; //found the piece so we can confirm it is an acceptable move
					for(unsigned int j=0; j < v.size(); ++j){
						if(v[j].x_==x1 && v[j].y_==y1){
							v[j].x_=x2;
							v[j].y_=y2;
							x1=x2;
							y1=y2; //update the game_piece and the values we are using to store them
							m.push_back(x1); //and add this move to the vectors that are storing the turns
							n.push_back(y1);
						}
					}
					goodLoc=true; //made at least one good move this turn
					break;
				}
			}
			if(!goodPiece){	
				cout << "There is no piece in between the coordinates you supplied!"<<endl;
			}
			goodPiece=false;
			if(done()){
				cout<<*this<<endl;
				return;
			}
		}
		else{
			cout<<"That location is too or too close to the piece you are trying to move!"<<endl;
		}
	}
	return;
}

void NineAlmondsGame::print(){
	cout << (*this);
}

void NineAlmondsGame::save(){ //new method that is called whenever a player enters quit or when done() is true
	ofstream ofs("NineAlmonds.txt");
	cout << "Would you like to save? (yes/no)" << endl;
	string s1;
	bool one = false;
	bool finished = false;
	getline(cin, s1); 
	istringstream iss(s1);
	one = (iss >> s1)!=0; 
	if(one){
		if(s1.compare("yes")==0){ //player wants to save
			ofs<<"NineAlmonds"<<endl; 
			for(unsigned int i = 0; i < v.size(); ++i){
				ofs << v[i].x_ << " " << v[i].y_ << endl; //write each piece into the file after NineAlmonds as the first line
			}
			return;
		}
		else{
			ofs<<"NODATA"<<endl; //if not yes, simply clear the file
			return;
		}
	}

}