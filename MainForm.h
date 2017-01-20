//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "oGame.h"
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlGame;
	TButton *btnReset;
	TMainMenu *menuMain;
	TMenuItem *menuFile;
	TMenuItem *menuReset;
	TMenuItem *menuExit;
	TMenuItem *fileOptions;
	TMenuItem *fileColors;
	TMenuItem *fileBoard;
	TMenuItem *fileP1;
	TMenuItem *fileP2;
	TMenuItem *fileAbout;
	TColorDialog *clrDialog;
	TMenuItem *fileDefaults;
	TCheckBox *cbHints;
	TShape *shCurrentPlayer;
	TLabel *lblCurrentPlayer;
	TShape *shP1Points;
	TLabel *lblP1Points;
	TShape *shP2Points;
	TLabel *lblP2Points;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnResetClick(TObject *Sender);
	void __fastcall fileBoardClick(TObject *Sender);
	void __fastcall fileP1Click(TObject *Sender);
	void __fastcall fileP2Click(TObject *Sender);
	void __fastcall fileDefaultsClick(TObject *Sender);
	void __fastcall cbHintsClick(TObject *Sender);
	void __fastcall menuResetClick(TObject *Sender);
	void __fastcall menuExitClick(TObject *Sender);
	void __fastcall fileAboutClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
extern PACKAGE oTile *board[8][8];
//---------------------------------------------------------------------------
#endif
