Reversi-Game
============
This project was the final lab in my Object-Oriented Programming Class
We had already made NineAlmonds (a puzzle game) and Magic Square (another puzzle game)
This lab's task was to extract the common features of each game into a "GameBase" class
and create the game Reversi (or Othello).



Kyle Wanzek (kwanzek@gmail.com)
Lab 5 - Single-Player and Multi-Player Board Games

How to use:
Build project in Visual Studio 2010
Run Lab5.exe
Follow instructions to play whichever the chosen game is

Files:
Lab5.cpp:
	main file, runs all the functions
piece_color.h:
	file for containing the piece_color enum
error_codes.h:
	file for the error codes enum (for catching exceptions)
game_piece.h:
	header file for game_piece struct
game_piece.cpp:
	cpp file for game_piece struct
NineAlmondsGame.h
	declarations for everything in the NineAlmondsGame class
NineAlmondsGame.cpp
	definitions for everything in the NineAlmondsGame class
GameBase.h
	declarations for the GameBase base class
GameBase.cpp
	definitions for two GameBase methods
NumberedGamePiece.h
	header file for said struct
NumberedGamePiece.cpp
	cpp file for said struct
MagicSquareGame.h
	declarations for the derived class MagicSquareGame
MagicSquareGame.cpp
	definitions for the derived class MagicSquareGame
ReversiGame.h
	declarations for the derived class ReversiGame
ReversiGame.cpp
	definitions for the derived class ReversiGame

Design Decision:
For Reversi, if a player saves a game, and tries to load a new game with different names, the names from the save are preserved
This is in order to maintain turn order, plus it would be somewhat jarring if both players suddenly changed name after the save.
A prompt might be warranted in the future to confirm that the players want to change names or something of the sort.

NineAlmonds and MagicSquare work properly, and now any time quit is entered, the user is asked to save.
They can type yes or no but if any string other than yes is entered, the save file is cleared.

If at any time a user enters a string that is quit, the game immediately ends.
If a player asks to quit, they must enter yes or no about saving. Entering anything other than yes clears the save file.
If a user enters an X,Y location that isn't a proper move, they are informed
If the user enters a string that doesn't have an integer, they are asked to enter a string that has an integer
Players can quit at any time.
