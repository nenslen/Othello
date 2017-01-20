//---------------------------------------------------------------------------

#pragma hdrstop

#include "oGame.h"
#include "oTile.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

oGame *game;


__fastcall oGame::oGame(TPanel* pnl)
{
	// Sets initial variables
	currentPlayer = 1;
	possibleMoves = 0;
	hints = true;

	// Sets initial colors
	clP1 = clWhite;
	clP2 = clBlack;
	clBoard = clGreen;

	// Creates the pieces and gets game ready for player 1
	initializeBoard(pnl);
	setPossibleMoves();
	refreshBoard();
}


/*
- Creates the 8x8 grid of game pieces
- Sets the initial 4 pieces
*/
void oGame::initializeBoard(TPanel* pnl)
{
	int tileIndex = 0;


	// Initializes the 8x8 grid of tiles
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			board[i][j] = new oTile(pnl);
			board[i][j]->Parent = pnl;

			board[i][j]->setID(tileIndex);
			board[i][j]->setPossibleMove(false);
			board[i][j]->setPosition(i, j);

			tileIndex++;
		}
	}


	// Sets initial 4 tiles
	board[3][3]->setStatus(1);
	board[4][4]->setStatus(1);

	board[3][4]->setStatus(2);
	board[4][3]->setStatus(2);
}


/*
	- Checks each tile to see if it is a possible move for a given player
	- Sets possibleMove to true/false on each tile
*/
void oGame::setPossibleMoves()
{
	bool enemyFound = false; // If enemy piece is detected
	possibleMoves = 0; // How many possible moves can be made


	// Sets number of the opposing player
	int enemy;
	if (currentPlayer == 1) { enemy = 2; }
	else { enemy = 1; }

	int currTileStatus;


	// Clears previous possible move locations
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j]->setPossibleMove(false);
		}
	}


	// Each tile is checked to see if it is a valid move
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			enemyFound = false;


			/*This block of code finds the next empty tile
				- Checks the next columns in the row until it finds an empty tile
				- If all cols in the row have been checked and there were no empty tiles,
				  it will jump down to the next row using break;
				- The next row is checked the same way as above until a valid tile is found
				- If no valid tiles are found, the game is over.
			*/
			currTileStatus = board[i][j]->getStatus();
			while (currTileStatus != 0)
			{
				j++;
				if (j < size)
				{
					currTileStatus = board[i][j]->getStatus();
				}
				else
				{
					j = 0;
					i++;
					if (i >= size) { return; }
					else { currTileStatus = board[i][j]->getStatus(); }
				}
			}


			// Now that an empty tile has been found, all directions are checked to see
			// if it is a valid move


			// LEFT TILES
			for (int k = j - 1; k >= 0; k--)
			{
				if (board[i][k]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					// 1 or more enemy pieces are between the current tile and this tile
					if (enemyFound && board[i][k]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
			}
			enemyFound = false;


			// RIGHT TILES
			for (int k = j + 1; k < size; k++)
			{
				if (board[i][k]->getStatus() == enemy) {
					enemyFound = true; }
				else
				{
					if (enemyFound && board[i][k]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
			}
			enemyFound = false;


			// TOP TILES
			for (int k = i - 1; k >= 0; k--)
			{
				if (board[k][j]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[k][j]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
			}
			enemyFound = false;


			// BOTTOM TILES
			for (int k = i + 1; k < size; k++)
			{
				if (board[k][j]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[k][j]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
			}
			enemyFound = false;


			int r, c;


			// TOP LEFT DIAGONAL
			r = i - 1;
			c = j - 1;
			while (r >= 0 && c >= 0)
			{
				if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[r][c]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
				r--;
				c--;
			}
			enemyFound = false;


			// TOP RIGHT DIAGONAL
			r = i - 1;
			c = j + 1;
			while (r >= 0 && c < size)
			{
				if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[r][c]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
				r--;
				c++;
			}
			enemyFound = false;


			// BOTTOM LEFT DIAGONAL
			r = i + 1;
			c = j - 1;
			while (r < size && c >= 0)
			{
				if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[r][c]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
				r++;
				c--;
			}
			enemyFound = false;


			// BOTTOM RIGHT DIAGONAL
			r = i + 1;
			c = j + 1;
			while (r < size && c < size)
			{
				if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
				else
				{
					if (enemyFound && board[r][c]->getStatus() == currentPlayer)
					{
						board[i][j]->setPossibleMove(true);
						possibleMoves++;
					}
					enemyFound = false;
					break;
				}
				r++;
				c++;
			}
		}
	}
}


/*
- Updates each tile to reflect the current status
- Colors P1/P2 tiles and hides the empty tiles
*/
void oGame::refreshBoard()
{
	p1Points = p2Points = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j]->Pen->Color = clBlack;
			board[i][j]->Pen->Style = psDot;


			// Colors pieces based on their status
			switch (board[i][j]->getStatus())
			{
			case 0: // No pieces on tile
				board[i][j]->Visible = false;
				board[i][j]->Brush->Color = clBoard;
				break;
			case 1: // Player 1
				board[i][j]->Brush->Color = clP1;
				board[i][j]->Pen->Color = clP1;
				p1Points++;
				break;
			case 2: // Player 2
				board[i][j]->Brush->Color = clP2;
				board[i][j]->Pen->Color = clP2;
				p2Points++;
				break;
			}


			// Allows possible move tiles to be clicked
			if(board[i][j]->isPossibleMove())
			{
				board[i][j]->Visible = true;
				board[i][j]->Brush->Color = clBoard;

				// Shows/Hides possible moves
				if (hints)
				{
					board[i][j]->Pen->Color = clRed;
					board[i][j]->Pen->Style = psDot;
				}
				else
				{
					board[i][j]->Pen->Color = clBoard;
				}
			}
		}
	}

	// Updates player point counts
	frmMain->lblP1Points->Caption = p1Points;
	frmMain->lblP2Points->Caption = p2Points;
}


/*
- Resets all variables
- Resets all tile statuses to 0
- Sets initial 4 pieces
*/
void oGame::reset()
{
	// Sets values of tiles to defaults
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j]->setPossibleMove(false);
			board[i][j]->setStatus(0);
			board[i][j]->setPosition(i, j);
		}
	}


	// Resets variables
	p1Points = p2Points = 0;
	currentPlayer = 1;
	possibleMoves = 0;


	// Sets initial 4 tiles
	board[3][3]->setStatus(1);
	board[4][4]->setStatus(1);

	board[3][4]->setStatus(2);
	board[4][3]->setStatus(2);


	// Refreshes board
	setPossibleMoves();
	refreshBoard();
}


/*
- Swaps whose turn it is
- Updates the main form to show whose turn it is
*/
void oGame::swapTurns()
{
	if (currentPlayer == 1)
	{
		currentPlayer = 2;
		frmMain->shCurrentPlayer->Brush->Color = clP2;
	}
	else
	{
		currentPlayer = 1;
		frmMain->shCurrentPlayer->Brush->Color = clP1;
	}
}


/*
- Performs a turn based on a given tile
- Changes enemy tiles to player tiles if they're between another player tile and the given tile
*/
void oGame::turn(int row, int col)
{
	bool enemyFound = false; // If enemy piece is detected


	// Sets number of the opposing player
	int enemy;
	if (currentPlayer == 1) { enemy = 2; }
	else { enemy = 1; }

	enemyFound = false;


	// LEFT TILES
	for (int k = col - 1; k >= 0; k--)
	{
		if (board[row][k]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			// 1 or more enemy pieces are between the current tile and this tile
			if (enemyFound && board[row][k]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while(k + 1 < col)
				{
					k++;
					board[row][k]->setStatus(currentPlayer);
				}
			}
			break;
		}
	}
	enemyFound = false;


	// RIGHT TILES
	for (int k = col + 1; k < size; k++)
	{
		if (board[row][k]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			// 1 or more enemy pieces are between the current tile and this tile
			if (enemyFound && board[row][k]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while(k - 1 > col)
				{
					k--;
					board[row][k]->setStatus(currentPlayer);
				}
			}
			break;
		}
	}
	enemyFound = false;


	// TOP TILES
	for (int k = row - 1; k >= 0; k--)
	{
		if (board[k][col]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			// 1 or more enemy pieces are between the current tile and this tile
			if (enemyFound && board[k][col]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while (k + 1 < row)
				{
					k++;
					board[k][col]->setStatus(currentPlayer);
				}
			}
			break;
		}
	}
	enemyFound = false;



	// BOTTOM TILES
	for (int k = row + 1; k < size; k++)
	{
		if (board[k][col]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			// 1 or more enemy pieces are between the current tile and this tile
			if (enemyFound && board[k][col]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while (k - 1 > row)
				{
					k--;
					board[k][col]->setStatus(currentPlayer);
				}
			}
			break;
		}
	}
	enemyFound = false;


	int r, c;


	// TOP LEFT DIAGONAL
	r = row - 1;
	c = col - 1;
	while (r >= 0 && c >= 0)
	{
		if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			if (enemyFound && board[r][c]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while ((r + 1) < row && (c + 1) < col)
				{
					r++;
					c++;
					board[r][c]->setStatus(currentPlayer);
				}
			}
			break;
		}
		r--;
		c--;
	}
	enemyFound = false;


	// TOP RIGHT DIAGONAL
	r = row - 1;
	c = col + 1;
	while (r >= 0 && c < size)
	{
		if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			if (enemyFound && board[r][c]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while ((r + 1) < row && (c - 1) > col)
				{
					r++;
					c--;
					board[r][c]->setStatus(currentPlayer);
				}
			}
			break;
		}
		r--;
		c++;
	}
	enemyFound = false;


	// BOTTOM LEFT DIAGONAL
	r = row + 1;
	c = col - 1;
	while (r < size && c >= 0)
	{
		if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			if (enemyFound && board[r][c]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while ((r - 1) > row && (c + 1) < col)
				{
					r--;
					c++;
					board[r][c]->setStatus(currentPlayer);
				}
			}
			break;
		}
		r++;
		c--;
	}


	// BOTTOM RIGHT DIAGONAL
	r = row + 1;
	c = col + 1;
	while (r < size && c < size)
	{
		if (board[r][c]->getStatus() == enemy) { enemyFound = true; }
		else
		{
			if (enemyFound && board[r][c]->getStatus() == currentPlayer)
			{
				// Change all tiles between the current tile and the given tile to the player's color
				while ((r - 1) > row && (c - 1) > col)
				{
					r--;
					c--;
					board[r][c]->setStatus(currentPlayer);
				}
			}
			break;
		}
		r++;
		c++;
	}
}
