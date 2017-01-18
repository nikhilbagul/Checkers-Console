// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int const Cols = 10;
int const Rows = 10;
#define EMPTY 1
#define PlayerX 2
#define PlayerO 3
#define Xking 4
#define Yking 5

void DisplayBoard(int board[Rows-2][Cols-2]);
bool CheckIfTurnisValid(int player, int c_1x, int c_1y, int c_2x, int c_2y, int board[Rows - 2][Cols - 2]);
int charConvert(char charToConv);
char intConvert(int intToConv);
void updateBoard(int board[Rows - 2][Cols - 2], int c_1x, int c_1y, int c_2x, int c_2y);

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
			string playerInp;
			int numberOfValidChars = 0;
			
			GOTOFLAG:
			cout << "\n" << "player 'x' > ";
			getline(cin, playerInp);
			char *playerInpCharacters = new char[playerInp.length()];

			if (playerInp.length() == 5 || playerInp.length() == 8)
			{
				
				strcpy(playerInpCharacters, playerInp.c_str());
				//playerInp.copy(playerInpCharacters, playerInpArraysize);
				for (int i = 0; i < playerInp.length(); i++)
				{
					if (i==2 || i==5)
					{
						if (!isspace(playerInpCharacters[i]))
						{
							cout << "\nInValid Input ! PLease enter the co-ordinates in the correct format !";
							goto GOTOFLAG;
						}
					}
					
					else
					{
						playerInpCharacters[numberOfValidChars] = playerInpCharacters[i];
						//cout << playerInpCharacters[validchars] << endl;
						numberOfValidChars++;
					}					
				}				
			}


			else
			{
				cout << "\nInvalid Input !  PLease enter the co-ordinates in the correct format !";
				goto GOTOFLAG;
			}

			
			int coord_1x, coord_1y, coord_2x, coord_2y;
			for (int i = 0; i < numberOfValidChars / 2; i = i+2)							//check for bounds of board
			{
				if ((int)playerInpCharacters[i] < 97 || (int)playerInpCharacters[i] > 104)
				{
					cout << "\nInvalid Input1 !";
					goto GOTOFLAG;
				}

				if ((int)playerInpCharacters[i+1] < 48 || (int)playerInpCharacters[i+1] > 57)
				{
					cout << "\nInvalid Input2 !";					
					goto GOTOFLAG;
				}

				if ((int)playerInpCharacters[i+2] < 97 || (int)playerInpCharacters[i+2] > 104)
				{
					cout << "\nInvalid Input3 !";
					goto GOTOFLAG;
				}

				if ((int)playerInpCharacters[i+3] < 48 || (int)playerInpCharacters[i+3] > 57)
				{
					cout << "\nInvalid Input4 !";
					goto GOTOFLAG;
				}
				
				else
				{
					coord_1x = (int)playerInpCharacters[i];
					coord_1y = (int)playerInpCharacters[i+1];
					coord_2x = (int)playerInpCharacters[i+2];
					coord_2y = (int)playerInpCharacters[i+3];

					if (CheckIfTurnisValid(PlayerX, coord_1x, coord_1y, coord_2x, coord_2y, board_2Darray))
					{
						isXTurnValid = true;
					}
					else
					{
						cout << "\n Invalid X move !";
					}
				}
			}			
		}	

		DisplayBoard(board_2Darray);
		//Disp board
		//Check Win 
		

		while (!isOTurnValid) // re write for player 'o'
		{
			int coord_1x, coord_1y, coord_2x, coord_2y;
			cout << "\n" << "Player O's turn to move from > ";
			cin >> coord_1x;
			cout << ", ";
			cin >> coord_1y;
			cout << " to ";
			cin >> coord_2x;
			cout << ", ";
			cin >> coord_2y;
			
			if (CheckIfTurnisValid(PlayerO, coord_1x, coord_1y, coord_2x, coord_2y, board_2Darray))
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
				cout << " " << intConvert(board[i-1][j]);
			}
			cout << "  "<<(Rows - 1 - i) <<"\n";
		}
	
	}
}

bool CheckIfTurnisValid(int player, int c_1x, int c_1y, int c_2x, int c_2y, int board [Rows-2][Cols-2])
{
	if (player == 2 || player == 3)
	{

		//check if the player is moving his/her own token
		if (player == 2)
		{
			if (board[8 - (c_1y - 48)][c_1x - 97] != charConvert('x'))
				return false;			
		}

		if (player == 3)
		{
			if (board[8 - (c_1y - 48)][c_1x - 97] != charConvert('o'))
			return false;			
		}

		//check if player is moving to an Empty block
		if (board[8 - (c_2y - 48)][c_2x - 97] != charConvert('.'))
		{
			return false;
		}


		// make sure the vertical direction of the move is not illegal
		if (player == PlayerX) 
		{
			//make sure he moves down
			if (c_1x >= c_2x)
			{
				cout << "Player X must move down\n";
				return false;
			}
		}
		if (player == PlayerO)
		{ 
			// make sure player moves up
			if (c_1x <= c_2y) 
			{
				cout << "Player O must move up\n";
				return false;
			}
		}

		// check if it's a regular move
		if (c_1x - c_2x == -1 || c_1x - c_2x == 1)
		{
			if (c_1y - c_2y == 1 || c_1y - c_2y == -1)
			{
				updateBoard(board, c_1x, c_1y, c_2x, c_2y);
				return true;
			}
		}
		else
			cout << "\n Valid move !";




	}
	else
	{
		cout << "end of func";
		return false;			//If the player is not X and not O
	}
		
}


void updateBoard(int board[Rows - 2][Cols - 2], int c_1x, int c_1y, int c_2x, int c_2y)
{
	int temp;
	//printf("SWAP: %d,%d to %d,%d\n", i, j, k, l);

	temp = board[8 - (c_1y - 48)][c_1x - 97];
	board[8 - (c_1y - 48)][c_1x - 97] = board[8 - (c_2y - 48)][c_2x - 97];
	board[8 - (c_2y - 48)][c_2x - 97] = temp;		
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

char intConvert(int intToConv)
{
	if (intToConv == 2)
		return 'x';
	if (intToConv == 1)
		return '.';
	if (intToConv == 3)
		return 'o';
	if (intToConv == 0)
		return ' ';
}

