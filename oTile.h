//---------------------------------------------------------------------------

#ifndef oTileH
#define oTileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
class oTile : public TShape
{
	private:
		int id;            // The tile's ID
		bool possibleMove; // If the tile is a possible move for a player
		int status;        // 0 = none, 1 = p1, 2 = p2
		int row;           // The tile's row
		int col;           // The tile's column
	public:
		__fastcall oTile(TComponent* pnl);  // Constructor

		void __fastcall mouseEnter(TObject *Sender); // Mouse enter event
		void __fastcall mouseLeave(TObject *Sender); // Mouse leave event
		void __fastcall tileClick(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y); // Mouse click event


		// Getters and setters
		void setID(int x) { id = x; }
		int getID() { return id; }

		void setPossibleMove(bool isPossible) { possibleMove = isPossible; }
		bool isPossibleMove() { return possibleMove; }

		void setStatus(int x) { status = x; }
		int getStatus() { return status; }

		void setPosition(int row, int col);
		int getRow() { return row; }
		int getCol() { return col; }

};

extern PACKAGE oTile *board[8][8];

#endif
