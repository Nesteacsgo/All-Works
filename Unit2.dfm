object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 781
  ClientWidth = 978
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object Image1: TImage
    Left = 264
    Top = 32
    Width = 400
    Height = 600
  end
  object Label1: TLabel
    Left = 64
    Top = 88
    Width = 34
    Height = 15
    Caption = 'Label1'
  end
  object Button1: TButton
    Left = 776
    Top = 72
    Width = 153
    Height = 65
    Caption = #1053#1072#1095#1072#1090#1100
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 776
    Top = 168
    Width = 153
    Height = 73
    Caption = #1055#1072#1091#1079#1072
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 296
    Top = 696
    Width = 176
    Height = 65
    Caption = 'Button3'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 520
    Top = 696
    Width = 176
    Height = 65
    Caption = 'Button4'
    TabOrder = 3
    OnClick = Button4Click
  end
  object MediaPlayer1: TMediaPlayer
    Left = 344
    Top = 660
    Width = 253
    Height = 30
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 4
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 250
    OnTimer = Timer1Timer
    Left = 832
    Top = 8
  end
end
