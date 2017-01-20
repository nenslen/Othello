//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "oGame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
TShape *bgTiles[8][8];
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	// Creates an 8x8 grid of background tiles
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			bgTiles[i][j] = new TShape(pnlGame);
			bgTiles[i][j]->Parent = pnlGame;

			bgTiles[i][j]->Height = 60;
			bgTiles[i][j]->Width = 60;

			bgTiles[i][j]->Brush->Color = clGreen;
			bgTiles[i][j]->Top = i * 60;
			bgTiles[i][j]->Left = j * 60;
		}
	}


	// Creates the game object
	game = new oGame(pnlGame);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnResetClick(TObject *Sender)
{
	// Resets the game
	game->reset();
    shCurrentPlayer->Brush->Color = game->getP1Color();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::fileBoardClick(TObject *Sender)
{
	// Changes the color of the background tiles
	if(clrDialog->Execute())
	{
		TColor clBoard = clrDialog->Color;

		game->setBoardColor(clBoard);
		game->refreshBoard();

		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				bgTiles[i][j]->Brush->Color = clBoard;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::fileP1Click(TObject *Sender)
{
	if(clrDialog->Execute())
	{
		// Sets player color in game object
		game->setP1Color(clrDialog->Color);
		game->refreshBoard();

		// Changes UI colors
		shP1Points->Brush->Color = clrDialog->Color;
		if(game->getCurrentPlayer() == 1) { shCurrentPlayer->Brush->Color = clrDialog->Color; }
		else { shCurrentPlayer->Brush->Color = game->getP2Color(); }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::fileP2Click(TObject *Sender)
{
	if(clrDialog->Execute())
	{
		// Sets player color in game object
		game->setP2Color(clrDialog->Color);
		game->refreshBoard();

		// Changes UI colors
		shP2Points->Brush->Color = clrDialog->Color;
		if(game->getCurrentPlayer() == 2) { shCurrentPlayer->Brush->Color = clrDialog->Color; }
		else { shCurrentPlayer->Brush->Color = game->getP1Color(); }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::fileDefaultsClick(TObject *Sender)
{
	// Changes background tile colors
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			bgTiles[i][j]->Brush->Color = clGreen;
		}
	}


	// Resets game colors
	game->setBoardColor(clGreen);
	game->setP1Color(clWhite);
	game->setP2Color(clBlack);
	game->refreshBoard();


	// Resets UI colors
	if(game->getCurrentPlayer() == 2) { shCurrentPlayer->Brush->Color = game->getP2Color(); }
	else { shCurrentPlayer->Brush->Color = game->getP1Color(); }
	shP1Points->Brush->Color = game->getP1Color();
	shP2Points->Brush->Color = game->getP2Color();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbHintsClick(TObject *Sender)
{
	// Turns on/off display of hints
	game->setShowHints(cbHints->Checked);
	game->refreshBoard();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuResetClick(TObject *Sender)
{
	// Resets the game
	game->reset();
	shCurrentPlayer->Brush->Color = game->getP1Color();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuExitClick(TObject *Sender)
{
	// Exits the game
    exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::fileAboutClick(TObject *Sender)
{
	// Shows a message about the game
	ShowMessage("During your turn, put a piece onto the grid so that it aligns with another piece of yours on a straight line. Opponent pieces between the new tile and your other tiles will become yours.\n\nYou cannot move without capturing opponent pieces.\n\nWhen both players cannot move, the game ends. The player with the most pieces wins!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Deletes all of the dynamically created objects
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			delete board[i][j];
			delete bgTiles[i][j];
		}
	}

	delete game;
}
//---------------------------------------------------------------------------

