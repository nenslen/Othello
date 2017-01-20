//---------------------------------------------------------------------------

#pragma hdrstop

#include <vcl.h> // For ShowMessage()

#include "oTile.h"
#include "oGame.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

oTile *board[8][8];

// Constructor
__fastcall oTile::oTile(TComponent* pnl) : TShape(pnl)
{
	// Sets values and links event handlers
	Height = 58;
	Width = 58;
	Shape = stCircle;
	OnMouseEnter = mouseEnter;
	OnMouseLeave = mouseLeave;
	OnMouseDown = tileClick;
}


/*
- Highlights the tile yellow if it's a possible move
*/
void __fastcall oTile::mouseEnter(TObject *Sender)
{
	if(possibleMove)
	{
		Pen->Color = clYellow;
	}
}


/*
- De-highlights the tile if it's a possible move
*/
void __fastcall oTile::mouseLeave(TObject *Sender)
{
	if(possibleMove)
	{
		if(game->getShowHints()) { Pen->Color = clRed; }
		else { Pen->Color = game->getBoardColor(); }
	}
}


/*
- Performs a turn on a tile if it's a valid move
*/
void __fastcall oTile::tileClick(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
	// Tile was not a valid move
	if (!possibleMove) { return; }
	//Brush->Color = clBlue;

	setStatus(game->getCurrentPlayer()); // The clicked tile now belongs to the player who clicked it
	setPossibleMove(false);              // This tile is no longer clickable
	game->turn(row, col);                // Performs a turn based on this tile


	// Swaps turns and makes sure there are possible moves
	game->swapTurns();
	game->setPossibleMoves();
	game->refreshBoard();


	// Checks if next player has any valid moves
	if (game->numPossibleMoves() == 0)
	{
		// This player's turn is skipped b/c they had no valid moves
		game->swapTurns();
		game->setPossibleMoves();
		game->refreshBoard();


		// Checks if next player has any valid moves
		if (game->numPossibleMoves() == 0)
		{
			// No valid moves. Game is over and winner/tie is declared
			if(game->getP1Points() > game->getP2Points())
			{
				ShowMessage("No valid moves left for either player.\n\nPlayer 1 wins!");
			}
			else if(game->getP1Points() < game->getP2Points())
			{
				ShowMessage("No valid moves left for either player.\n\nPlayer 2 wins!");
			}
			else
			{
				ShowMessage("No valid moves left for either player.\n\nIt's a tie!");
            }
		}
		else
		{
			// Current player has no moves, their turn is skipped
			ShowMessage("No moves for current player. Swapping turns.");
        }
	}
}


/*
- Sets the row/col of a tile
*/
void oTile::setPosition(int _row, int _col)
{
	row = _row;
	col = _col;

	Top = row * (Height + 2) + 1;
	Left = col * (Width + 2) + 1;
}

