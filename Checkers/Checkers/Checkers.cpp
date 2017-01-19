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
int jumps=0;
int bufferBoard[Rows - 2][Cols - 2];

void DisplayBoard(int board[Rows-2][Cols-2]);
bool CheckIfTurnisValid(int player, int c_1x, int c_1y, int c_2x, int c_2y, int board[Rows - 2][Cols - 2], int numberOfValidInpChars);
int charConvert(char charToConv);
char intConvert(int intToConv);
void updateBoard(int board[Rows - 2][Cols - 2], int c_1x, int c_1y, int c_2x, int c_2y);
bool InputCheck(int player, int board[Rows - 2][Cols - 2]);

int main()
{
	int board_2Darray[Rows-2][Cols-2] = 
	{
		{ 0,2,0,2,0,2,0,2 },
		{ 2,0,2,0,2,0,2,0 },
		{ 0,2,0,2,0,2,0,2 },
		{ 1,0,3,0,1,0,1,0 },
		{ 0,1,0,1,0,1,0,1 },
		{ 3,0,3,0,1,0,3,0 },
		{ 0,1,0,3,0,3,0,3 },
		{ 3,0,3,0,3,0,3,0 } 
	};

	for (int i = 0; i < Rows - 2; i++)
	{
		for (int j = 0; j < Cols - 2; j++)
		{
			bufferBoard[i][j] = board_2Darray[i][j];
		}
	}

	bool quitGame = false;
	bool isXTurnValid = false;
	bool isOTurnValid = false;
	bool isGameOver = false;
	char choice;

	cout << "Welcome to checkers !! \n\n";
	cout << "Hit P to play: ";
	cin >> choice;
	cin.ignore();

	if ((choice == 'p' || choice == 'P'))
	{
		DisplayBoard(board_2Darray);
		cin.ignore();
		while (!isGameOver)
		{
			//Player X's turn
			while (!isXTurnValid)
			{
				cout << "\n" << "player 'x' > ";
				if (InputCheck(PlayerX, board_2Darray))
				{
					isXTurnValid = true;
				}
				else
				{
					//If wrong input, reset board to original/previous locked state
					for (int i = 0; i < Rows - 2; i++)			
					{
						for (int j = 0; j < Cols - 2; j++)
						{
							board_2Darray[i][j] = bufferBoard[i][j];
						}
					}				
				}
			}
			//Display updated board
			DisplayBoard(board_2Darray);	
			//Check Win condition

			//Player O's turn
			while (!isOTurnValid)
			{			
				cout << "\n" << "player 'o' > ";
				if (InputCheck(PlayerO, board_2Darray))
				{
					isOTurnValid = true;
				}
				else
				{
					//If wrong input, reset board to original/previous locked state
					for (int i = 0; i < Rows - 2; i++)			//reset board to original state
					{
						for (int j = 0; j < Cols - 2; j++)
						{
							board_2Darray[i][j] = bufferBoard[i][j];
						}
					}			
				}
			}
			//Display updated board
			DisplayBoard(board_2Darray);
			isXTurnValid = false;
			isOTurnValid = false;
			//Check Win Condition
		}
		
	}
	
	system("PAUSE");
	return 0;
} 
// end of main

bool InputCheck(int player, int board[Rows - 2][Cols - 2])
{
	int delimPos = 0;
	string playerInp;
	int numberOfValidChars = 0;
	getline(cin, playerInp);									// get string input of MOVE co-ordinates from user/players
	char *playerInpCharacters = new char[playerInp.length()];

	if (playerInp.length() == 5 || playerInp.length() == 8)		//check if the player has entered 2 or 3 MOVE cordinates 
	{
		strcpy(playerInpCharacters, playerInp.c_str());
		//playerInp.copy(playerInpCharacters, playerInpArraysize);
		for (int i = 0; i < playerInp.length(); i++)
		{
			if (i == 2 || i == 5)			//check for space on 3rd and 6th positions
			{
				if (!isspace(playerInpCharacters[i]))
				{
					cout << "\n InValid Input ! PLease enter the co-ordinates in the correct format !";
					return false;
				}
			}

			else
			{
				playerInpCharacters[numberOfValidChars] = playerInpCharacters[i];    //parse input string into a char[] array
				numberOfValidChars++;
			}
		}

		//cout << numberOfValidChars;
	}


	else
	{
		cout << "\nInvalid Input !  PLease enter the co-ordinates in the correct format !";
		return false;
	}

	int coord_1x, coord_1y, coord_2x, coord_2y;
	for (int i = 0; i < numberOfValidChars / 2; i = i + 2)										//check the input against bounds of the board a-h, 8-1
	{
		if ((int)playerInpCharacters[i] < 97 || (int)playerInpCharacters[i] > 104)
		{
			cout << "\nInvalid Input1 !";
			return false;
		}

		if ((int)playerInpCharacters[i + 1] < 49 || (int)playerInpCharacters[i + 1] > 56)
		{
			cout << "\nInvalid Input2 !";
			return false;
		}

		if ((int)playerInpCharacters[i + 2] < 97 || (int)playerInpCharacters[i + 2] > 104)
		{
			cout << "\nInvalid Input3 !";
			return false;
		}

		if ((int)playerInpCharacters[i + 3] < 49 || (int)playerInpCharacters[i + 3] > 56)
		{
			cout << "\nInvalid Input4 !";
			return false;
		}

		else
		{
			coord_1x = (int)playerInpCharacters[i];
			coord_1y = (int)playerInpCharacters[i + 1];
			coord_2x = (int)playerInpCharacters[i + 2];
			coord_2y = (int)playerInpCharacters[i + 3];

			if (CheckIfTurnisValid(player, coord_1x, coord_1y, coord_2x, coord_2y, board, numberOfValidChars))
			{
				//cout << "\n Valid move !";
				continue;
			}
			else
			{
				cout << "\nInvalid "<<intConvert(player)<<" MOVE !";
				jumps = 0; //reset the number of Jumps
				return false;
			}
		}
	}
	
	return true;
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

bool CheckIfTurnisValid(int player, int c_1x, int c_1y, int c_2x, int c_2y, int boardArray [Rows-2][Cols-2], int numberOfValidInpChars)
{
	if (player == 2 || player == 3)
	{

		//check if the player is moving his/her own token
		if (player == 2)
		{
			if (boardArray[8 - (c_1y - 48)][c_1x - 97] != charConvert('x'))
				return false;			
		}

		if (player == 3)
		{
			if (boardArray[8 - (c_1y - 48)][c_1x - 97] != charConvert('o'))
			return false;			
		}

		//check if player is moving to an Empty block
		if (boardArray[8 - (c_2y - 48)][c_2x - 97] != charConvert('.'))
		{
			return false;
		}

		cout << numberOfValidInpChars;
		//check if its a double jump move
		bool isMultipleJumpTurn = false;
		if (numberOfValidInpChars > 4)
		{
			if ((c_1x - c_2x == -2 || c_1x - c_2x == 2))			//single jump always has to be diagonal
			{
				if (c_1y - c_2y == 2 || c_1y - c_2y == -2)
					isMultipleJumpTurn = true;
				else
					return false;
			}
			else
				return false;
		}

		// make sure the vertical direction of the move is not illegal
		if (player == PlayerX)
		{
			//make sure he moves down
			if (c_1y <= c_2y)
			{
				cout << "Player X must MOVE down\n";
				return false;
			}	
			if (c_1x == c_2x)
			{
				cout << "Player X must MOVE diagonally !\n";
			}
		}

		if (player == PlayerO)
		{
			// make sure player moves up
			if (c_1y >= c_2y)
			{
				cout << "Player O must MOVE up\n";
				return false;
			}
			if (c_1x == c_2x)
			{
				cout << "Player O must MOVE diagonally !\n";
			}
		}

		// check if it's a regular move
		if ((c_1x - c_2x == -1 || c_1x - c_2x == 1))
		{
			if (c_1y - c_2y == -1 || c_1y - c_2y == 1)
			{
				updateBoard(boardArray, c_1x, c_1y, c_2x, c_2y);
				return true;
			}
		}		

		//check if it's a jump move
		int jumpR, jumpC;
		if (c_1x - c_2x == -2 || c_1x - c_2x == 2) 
		{
			if (c_1y - c_2y == 2 || c_1y - c_2y == -2) 
			{
				// check if the jump position is enemy
				if (c_1x < c_2x) 
				{ // move to right
					jumpC = (c_1x - 97)+1;
				}
				else 
				{ // move to left
					jumpC = (c_1x - 97)-1;
				}
				if (c_1y < c_2y) 
				{ // move up 
					jumpR = (8 - (c_1y - 48))-1;
				}
				else 
				{ // move down
					jumpR = (8 - (c_1y - 48))+1;
				}

				//cout << board[jumpR+1][jumpC+1];

				
				if (player == PlayerX && boardArray[jumpR][jumpC] != PlayerO)
				{
					cout << "No enemy to jump over !";
					return false;
				}
				if (player == PlayerO && boardArray[jumpR][jumpC] != PlayerX)
				{
					cout << "No enemy to jump over !";
					return false;
				}

				// Hence, we are sure the move is valid		

				if (isMultipleJumpTurn)
				{
					boardArray[jumpC][jumpR] = 1;	//make the enemy position jumped to be an EMPTY(.) space

					if (jumps >= 2)
					{
						updateBoard(boardArray, c_1x, c_1y, c_2x, c_2y);
						//memcpy(bufferBoard, boardArray, sizeof(boardArray));		//copy final CORRECT result into buffer array
						for (int i = 0; i < Rows - 2; i++)							//copy final CORRECT result into buffer array
						{
							for (int j = 0; j < Cols - 2; j++)
							{
								bufferBoard[i][j] = boardArray[i][j];
							}
						}
						cout << "\nValid Double Jump 2 MOVE !\n\n";	
						return true;
					}	
					else
					{
						updateBoard(boardArray, c_1x, c_1y, c_2x, c_2y);		
						cout << "\nValid Double Jump 1 MOVE !\n";
						jumps = 1;
						jumps++;
						return true;
					}					
				}

				else
				{
					boardArray[jumpC][jumpR] = 1;					//make the enemy position jumped to be an EMPTY(.) space
					updateBoard(boardArray, c_1x, c_1y, c_2x, c_2y);
					for (int i = 0; i < Rows - 2; i++)				//copy final CORRECT result into buffer array
					{
						for (int j = 0; j < Cols - 2; j++)
						{
							bufferBoard[i][j] = boardArray[i][j];
						}
					}

					cout << "\n Valid Single Jump move !\n\n";
					return true;
				}
				
				
			}
		}

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

