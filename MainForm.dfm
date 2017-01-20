object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Othello - Nic Enslen'
  ClientHeight = 496
  ClientWidth = 714
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = menuMain
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object shCurrentPlayer: TShape
    Left = 494
    Top = 8
    Width = 65
    Height = 65
    Shape = stCircle
  end
  object lblCurrentPlayer: TLabel
    Left = 565
    Top = 32
    Width = 135
    Height = 25
    Caption = 'Current Player'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object shP1Points: TShape
    Left = 494
    Top = 112
    Width = 27
    Height = 25
    Shape = stCircle
  end
  object lblP1Points: TLabel
    Left = 527
    Top = 112
    Width = 11
    Height = 25
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object shP2Points: TShape
    Left = 590
    Top = 112
    Width = 27
    Height = 25
    Brush.Color = clBlack
    Shape = stCircle
  end
  object lblP2Points: TLabel
    Left = 623
    Top = 112
    Width = 11
    Height = 25
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object pnlGame: TPanel
    Left = 8
    Top = 8
    Width = 480
    Height = 480
    TabOrder = 0
  end
  object btnReset: TButton
    Left = 494
    Top = 448
    Width = 213
    Height = 40
    Caption = 'Reset'
    TabOrder = 1
    OnClick = btnResetClick
  end
  object cbHints: TCheckBox
    Left = 494
    Top = 425
    Width = 97
    Height = 17
    Caption = 'Show Hints'
    Checked = True
    State = cbChecked
    TabOrder = 2
    OnClick = cbHintsClick
  end
  object menuMain: TMainMenu
    Left = 552
    Top = 288
    object menuFile: TMenuItem
      Caption = 'File'
      object menuReset: TMenuItem
        Caption = 'Reset'
        OnClick = menuResetClick
      end
      object menuExit: TMenuItem
        Caption = 'Exit'
        OnClick = menuExitClick
      end
    end
    object fileOptions: TMenuItem
      Caption = 'Options'
      object fileColors: TMenuItem
        Caption = 'Colors'
        object fileBoard: TMenuItem
          Caption = 'Board'
          OnClick = fileBoardClick
        end
        object fileP1: TMenuItem
          Caption = 'Player 1'
          OnClick = fileP1Click
        end
        object fileP2: TMenuItem
          Caption = 'Player 2'
          OnClick = fileP2Click
        end
        object fileDefaults: TMenuItem
          Caption = 'Reset to Defaults'
          OnClick = fileDefaultsClick
        end
      end
    end
    object fileAbout: TMenuItem
      Caption = 'About'
      OnClick = fileAboutClick
    end
  end
  object clrDialog: TColorDialog
    Left = 496
    Top = 288
  end
end
