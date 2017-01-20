//---------------------------------------------------------------------------

#ifndef oGameH
#define oGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "oTile.h"
const int size = 8; // The size of the game board

class oGame
{
	private:
		int p1Points; // Player 1's point count
		int p2Points; // Player 2's point count
		TColor clP1;    // Player 1's color
		TColor clP2;    // Player 2's color
		TColor clBoard; // The board's background color
		int currentPlayer; // Whose turn it is
		int possibleMoves; // How many possible moves there are for the current player
		bool hints;        // Display hints on/off

		void initializeBoard(TPanel* pnl);
	public:
		__fastcall oGame(TPanel* pnl);  // Constructor

		void setPossibleMoves();
		void refreshBoard();
		void reset();
		void swapTurns();
		void turn(int row, int col);

		// Getters and setters
		int getP1Points() { return p1Points; }
		int getP2Points() { return p2Points; }

		void setP1Color(TColor clr) { clP1 = clr; }
		void setP2Color(TColor clr) { clP2 = clr; }
		void setBoardColor(TColor clr) { clBoard = clr; }
		TColor getP1Color() { return clP1; }
		TColor getP2Color() { return clP2; }
		TColor getBoardColor() { return clBoard; }

		int getCurrentPlayer() { return currentPlayer; }
		int numPossibleMoves() { return possibleMoves; }

		void setShowHints(bool show) { hints = show; }
		bool getShowHints() { return hints; }
};

extern PACKAGE oGame *game;

#endif
