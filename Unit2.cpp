//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TForm2 *Form2;

int FieldForFigure[30][20];
bool FigureIsCreate = false;

int Tetranoids[4][4][4] = {
							{
							{1,0,0,0},
							{1,0,0,0},
							{1,0,0,0},
							{1,0,0,0}
							},

							{
							{0,0,0,0},
							{2,0,0,0},
							{2,0,0,0},
							{2,2,0,0}
							},

							{
							{0,0,0,0},
							{0,0,0,0},
							{0,3,0,0},
							{3,3,3,0}
							}
};

//-------------------------------------------------------------------------------------------------

class Figure {
public:
	int x = 9, y = 0;
	int znac = 0;
	void MoveFigure(int (*FieldForFigure)[20]) {	// Движение фигуры вниз
		y += 1;
		FieldForFigure[y - 1][x] = 0;
		FieldForFigure[y][x] = 1;

	}
	void CreateFigure(int (*FieldForFigure)[20]) {	// Появление фигуры в начале
		FieldForFigure[y][x] = 1;
	}
	void MoveRight(int(*FieldForFigure)[20]) {	// Движение квадрата вправо
		x += 1;
		FieldForFigure[y][x - 1] = 0;
		FieldForFigure[y][x] = 1;
	}

	void MoveLeft(int(*FieldForFigure)[20]) {	// Движение квадрата влево
		x -= 1;
		FieldForFigure[y][x +1] = 0;
		FieldForFigure[y][x] = 1;
	}
};

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------

class TetranoidAction {
public:
	Figure ComplexFigure[4][4];
	TColor color = clGreen;
	int IdTetr;
	TetranoidAction(int id = 2) {
		IdTetr = id;
	}

	void FillTetranoid(int(*Tetranoids)[4][4], int IndexOfTetranoid) { // Заполнение тетраноида
		for (int i = 0; i < 4; i++) {								   // Далее этот тетроноид будет двигаться по полю
			for (int j = 0; j < 4; j++) {
			ComplexFigure[i][j].znac = Tetranoids[IndexOfTetranoid][i][j];
			ComplexFigure[i][j].x = j+8;
			ComplexFigure[i][j].y = i;
			}
		}
	}

	bool CheckUnderFigure(int(*FieldForFigure)[20]) {
		int count = 0;
		for (int i = 0; i < 3; i++){
			if (FieldForFigure[ComplexFigure[3][i].y][ComplexFigure[3][i].x] != 0) {
				if (FieldForFigure[ComplexFigure[3][i].y+1][ComplexFigure[3][i].x] != 0) {
					count += 1;
				}
			}
		}
		if (count != 0) {
			return false;
		}
		return true;
	}



	void MoveTetranoid(int(*FieldForFigure)[20]) { // Двигает тетраноид вниз
		for (int i = 3; i > -1; i--){
			for (int j = 3; j > -1; j--){
					if (ComplexFigure[i][j].znac != 0) {
						ComplexFigure[i][j].y += 1;
						FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x] = ComplexFigure[i][j].znac;
						FieldForFigure[ComplexFigure[i][j].y-1][ComplexFigure[i][j].x] = 0;
					}

			}

		}
	}

	void CreateTetranoid(int(*FieldForFigure)[20]) { // Создает тетраноид сверху в центре
		int x = 9; // Середина Поля сверху
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){

				FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x] = ComplexFigure[i][j].znac;
				Form2->Label1->Caption = "00000";
			}
		}
	}

	void MoveRight(int(*FieldForFigure)[20]) {
		bool FigureNearBorder = false;
		Form2->Button3->Visible = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (ComplexFigure[i][j].znac != 0) {
					if (ComplexFigure[i][j].x == 19) {
						FigureNearBorder = true;
						break;
					}
				}

			}
		}

		for (int i = 0; i < 4; i++){
			for (int j = 3; j > -1; j--) {
				if (FigureNearBorder) {
					Form2->Button4->Visible = false;
					return;
				}
				else {
					ComplexFigure[i][j].x += 1;
					FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x] = ComplexFigure[i][j].znac;
					FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x - 1] = 0;
				}
			}
		}

	}

	void MoveLeft(int(*FieldForFigure)[20]) {
		bool FigureNearBorder = false;
		Form2->Button4->Visible = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (ComplexFigure[i][j].znac != 0) {
					if (ComplexFigure[i][j].x == 0) {
						FigureNearBorder = true;
						break;
					}
				}

			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (FigureNearBorder) {
					Form2->Button3->Visible = false;
					return;
				}
				else {
					ComplexFigure[i][j].x -= 1;
					FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x] = ComplexFigure[i][j].znac;
					FieldForFigure[ComplexFigure[i][j].y][ComplexFigure[i][j].x + 1] = 0;
				}
			}
		}
	}

	bool CheckBottomBorder(int (*FieldForFigure)[20]) {
		for (int i = 3; i > -1; i--){
			for (int j = 3; j > -1; j--){
				if (ComplexFigure[i][j].y == 29) {
					return false;
				}
			}

		}
		return true;
	}
	bool CheckRightFigures(int (*FieldForFigure)[20]) {
		for (int i = 3; i > -1; i--) {
			for (int j = 3; j > -1; j--) {
			  if (ComplexFigure[j][i].znac != 0) {
				  if (FieldForFigure[ComplexFigure[j][i].y][ComplexFigure[j][i].x+1] != 0) {
					return true;
				  }
				  else return false;
			  }
			}
		}
		return false;
	}
	bool CheckLeftFigures(int (*FieldForFigure)[20]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
			  if (ComplexFigure[j][i].znac != 0) {
				  if (FieldForFigure[ComplexFigure[j][i].y][ComplexFigure[j][i].x-1] != 0) {
					return true;
				  }
				  else return false;
			  }
			}
		}
		return false;
	}

};

void DrawField(int (*FieldForFigure)[20]) {
	int x = 0;
	int y = 0;
	int idf = 0;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {

			idf = FieldForFigure[i][j];
			switch (idf) {
				case 2 : {
					Form2->Image1->Canvas->Brush->Color = clGreen;
					Form2->Image1->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
					break;
				}
				case 3 : {
					Form2->Image1->Canvas->Brush->Color = clRed;
					Form2->Image1->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
					break;
				}
				case 1 : {
					Form2->Image1->Canvas->Brush->Color = clBlue;
					Form2->Image1->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
					break;
				}
				default:
					Form2->Image1->Canvas->Brush->Color = clWhite;
					Form2->Image1->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
				}
				x += 1;
		}
		y += 1;
		x = 0;
	}
}
TetranoidAction MassOfFigure[3] = {TetranoidAction(0),TetranoidAction(1),TetranoidAction(2)};
int count = 0;
int id = rand()%3;



//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	MediaPlayer1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{

	//MediaPlayer1->FileName = "C:/Users/romab/Documents/Embarcadero/Studio/Projects/Tetris/1.mp3";
	//MediaPlayer1->Open();
	//MediaPlayer1->Play();
	Timer1->Enabled = true;



}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm2::Timer1Timer(TObject *Sender)
{

	if (FigureIsCreate == false) {
		Button4->Visible = false;
		Button3->Visible = false;
		id = rand()%3;
		MassOfFigure[id].FillTetranoid(Tetranoids, id);
		MassOfFigure[id].CreateTetranoid(FieldForFigure);
		FigureIsCreate = true;
		Button4->Visible = true;
		Button3->Visible = true;
	}
	else {

		if (MassOfFigure[id].CheckBottomBorder(FieldForFigure) and (MassOfFigure[id].CheckUnderFigure(FieldForFigure))) {
			MassOfFigure[id].MoveTetranoid(FieldForFigure);
		}
		else {
			FigureIsCreate = false;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
						MassOfFigure[id].ComplexFigure[i][j].x = 9+j-1;
						MassOfFigure[id].ComplexFigure[i][j].y = i;
			}
		}
		}
	}
	DrawField(FieldForFigure);

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
	if (MassOfFigure[id].CheckLeftFigures(FieldForFigure)) Label1->Caption = "налево нельзя!!!!";
	else MassOfFigure[id].MoveLeft(FieldForFigure);

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
	if (MassOfFigure[id].CheckRightFigures(FieldForFigure)) Label1->Caption = "направо нельзя!!";
	else MassOfFigure[id].MoveRight(FieldForFigure);



}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Timer1->Enabled=false;
}
//---------------------------------------------------------------------------

