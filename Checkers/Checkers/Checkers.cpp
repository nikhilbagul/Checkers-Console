// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int const Cols = 10;
int const Rows = 10;
void DisplayBoard(int board[Rows-2][Cols-2]);
bool CheckIfTurnisValid(char player, char c_1x, int c_1y, char c_2x, int c_2y, int board[Rows - 2][Cols - 2]);
int charConvert(char charToConv);

int main()
{
	int board_2Darray[Rows-2][Cols-2] = 
	{
		{ 0,2,0,2,0,2,0,2 },
		{ 2,0,2,0,2,0,2,0 },
		{ 0,2,0,2,0,2,0,2 },
		{ 1,0,1,0,1,0,1,0 },
		{ 0,1,0,1,0,1,0,1 },
		{ 3,0,3,0,3,0,3,0 },
		{ 0,3,0,3,0,3,0,3 },
		{ 3,0,3,0,3,0,3,0 } 
	};
	
	bool quitGame = false;
	bool isXTurnValid = false;
	bool isOTurnValid = false;
	char choice;

	cout << "Welcome to checkers !! \n\n";
	cout << "Hit P to play: ";
	cin >> choice;
	cin.ignore();

	if ((choice == 'p' || choice == 'P'))
	{
		DisplayBoard(board_2Darray);
		cin.ignore();
		//while (isGameOver)
		

		while (!isXTurnValid)
		{
			int delimPos = 0;
			string playerInp, token, delimiter = " ";
			
			cout << "\n" << "player 'x' > ";
			getline(cin, playerInp);
			//cout << playerInp.length();	

			int playerInpArraysize = (playerInp.length() + 1)/ 3;
			string *playerInpArray = new string[playerInpArraysize];
			
			int i = 0;
			stringstream ssin(playerInp);
			while (ssin.good() && i < playerInpArraysize)
				{
					ssin >> playerInpArray[i];
					++i;
				}
			for (i = 0; i < playerInpArraysize; i++) {
				cout << playerInpArray[i] << endl;
			}

			char coord_1x, coord_2x;
			int coord_1y, coord_2y;		

			/*
			if (CheckIfTurnisValid('x', coord_1x, coord_1y, coord_2x, coord_2y, board_2Darray))
			{
				isXTurnValid = true;
			}
			else
			{
				cout << "\n Invalid X move !";
			}
			*/
		}
		
		//Check Win 
		//Disp board

		while (!isOTurnValid)
		{
			char coord_1x, coord_2x;
			int coord_1y, coord_2y;
			cout << "\n" << "Player O's turn to move from > ";
			cin >> coord_1x;
			cout << ", ";
			cin >> coord_1y;
			cout << " to ";
			cin >> coord_2x;
			cout << ", ";
			cin >> coord_2y;
			if (CheckIfTurnisValid('x', coord_1x, coord_1y, coord_2x, coord_2y, board_2Darray))
			{
				isOTurnValid = true;
			}
			else
			{
				cout << "\n Invalid O move !";
			}
		}
	}
	
	system("PAUSE");
	return 0;
}

void DisplayBoard (int board[Rows-2][Cols-2])
{
	int i, j;

	for (i = 0; i < Rows; i++)
	{
		if (i == 0 || i == Cols-1)
		{
			if(i==0)
				cout << "   a b c d e f g h \n\n";
			else
				cout << "\n   a b c d e f g h \n\n";
		}
		else
		{
			cout << (Rows - 1 - i) <<" ";
			for (j = 0; j < Cols-2; j++)
			{
				cout << " " << board[i-1][j];
			}
			cout << "  "<<(Rows - 1 - i) <<"\n";
		}
	
	}
}

bool CheckIfTurnisValid(char player, char c_1x, int c_1y, char c_2x, int c_2y, int board [Rows-2][Cols-2])
{
	if ((player == 'x' || player == 'X') || (player == 'O' || player == 'o'))
	{
		//check for Bounds of board
		if (c_1x - 'a' < 0 && c_1x - 'a' >= Rows-2)				
			return false;
		if (c_1y - 1 < 0 && c_1y - 1 >= Cols - 2)
			return false;
		if (c_2x - 'a' < 0 && c_2x - 'a' >= Rows - 2)
			return false;
		if (c_2y - 1 < 0 && c_2y - 1 >= Cols - 2)
			return false;
		
		//check if the player is moving his/her own token
		if ((player == 'x' || player == 'X'))
		{
			if (board[c_1x - 'a'][c_1y - 1] != charConvert('x'))
				return false;
		}
		
		if ((player == 'o' || player == 'O'))
		{
			if (board[c_1x - 'a'][c_1y - 1] != charConvert('o'))
				return false;
		}

		//check if player is moving to an Empty block
		if (board[c_2x - 'a'][c_2y - 1] != charConvert('.'))
		{
			return false;
		}



				
	}
	
	else
		return false;			//If the player is not X and not O
}

int charConvert(char charToConv)
{
	if (charToConv == 'x')
		return 2;
	if (charToConv == '.')
		return 1;
	if (charToConv == 'o')
		return 3;
	if (charToConv == ' ')
		return 0;
}

