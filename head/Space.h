#pragma once

#include <iostream>
#include "targetver.h"

#define SPACE_SIZE 25

#define Cell_State bool
#define Live_Cell true
#define Dead_Cell false

#define Lonely_Condition 0.25
#define Crowded_Condition 0.375

#define init_Posibility 30

#define Cell_Size 30

struct Cell
{
	Cell_State cell_state;
	bool permanent;
};

class Space
{
public:
	bool Game_Status;
	bool auto_growing_enable_flag;
	bool auto_trans_moving_enable_flag;
	bool Game_Over_flag;
	bool Game_End_flag;
private:
	Cell ** space = new Cell*[SPACE_SIZE];
public:
	Space() {
		for (int i = 0; i < SPACE_SIZE; i++)
			space[i] = new Cell[SPACE_SIZE];

		for (int i = 0; i < SPACE_SIZE; i++)
			for (int j = 0; j < SPACE_SIZE; j++) {
				space[i][j].cell_state = Dead_Cell;
				space[i][j].permanent = false;
			}

		space[SPACE_SIZE / 2][SPACE_SIZE / 2].permanent = true;
				
		Game_Status = false;
		auto_growing_enable_flag = false;
		auto_trans_moving_enable_flag = false;
		Game_Over_flag = false;
		Game_End_flag = false;
	};

	bool Cell_Random_Jumping() {
		srand(1);
		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				int posibility = rand() % 100;
				if (posibility < init_Posibility)
					space[i][j].cell_state = Live_Cell;
				else
					space[i][j].cell_state = Dead_Cell;
			}
		}
		space[SPACE_SIZE / 2][SPACE_SIZE / 2].cell_state = Live_Cell;
		return true;
	}

	Cell_State Get_Cell_State(int x, int y) {
		return space[x][y].cell_state;
	};

	bool Change_Cell_State(int x, int y) {
		if (space[x][y].permanent == false) {
			if (space[x][y].cell_state = !space[x][y].cell_state)
				return true;
			else
				return false;
		}
		return true;
	}
	bool Change_Cell_State(int x, int y, Cell_State state) {
		if (space[x][y].permanent == false) {
			if (space[x][y].cell_state = state)
				return true;
			else
				return false;
		}
		return true;
	}
	bool Change_Cell_State(int x, int y, Cell_State state, char * flag ) {
		if (space[x][y].cell_state = state && flag == "system")
			return true;
		else
			return false;
	}

	Cell_State Living_Condition_Perceiving(int x, int y) {
		float surrounding_Cell_Number = 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int x0 = i + x;
				int y0 = j + y;

				if (x0 == x && y0 == y)
					continue;
				if (x0 < 0 || y0 < 0)
					continue;
				if (x0 >= SPACE_SIZE || y0 >= SPACE_SIZE)
					continue;

				if (
					space[x0][y0].cell_state == Live_Cell
					)
					surrounding_Cell_Number++;
			}
		}

		if (surrounding_Cell_Number == 2)
			return space[x][y].cell_state;
		else if (surrounding_Cell_Number == 3)
			return Live_Cell;
		else
			return Dead_Cell;
	}

	Space * Cell_Growing() {
		Space * New_Space = new Space();

		New_Space->auto_growing_enable_flag = this->auto_growing_enable_flag;
		New_Space->auto_trans_moving_enable_flag = this->auto_trans_moving_enable_flag;
		New_Space->Game_Status = this->Game_Status;

		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				New_Space->space[i][j] = this->space[i][j];
			}
		}

		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				New_Space->Change_Cell_State(i, j, Living_Condition_Perceiving(i, j), "system");
			}
		}

		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				this->space[i][j] = New_Space->space[i][j];
			}
		}

		delete New_Space;

		return this;
	}

	bool Draw_Space_Consolo_Window() {
		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				if (space[i][j].cell_state == Live_Cell)
					std::cout << "¡ö";
				else if (space[i][j].cell_state == Dead_Cell)
					std::cout << "  ";
			}
			std::cout << std::endl;
		}
		return true;
	}
	bool Draw_Space_Windows_Application(HDC hDC) {
		HDC mdc;
		HBITMAP hbmp_Black;
		HBITMAP hbmp_White;
		mdc = CreateCompatibleDC(hDC);

		hbmp_Black = (HBITMAP)LoadImage(NULL, _T("Cell_Black.bmp"), IMAGE_BITMAP, Cell_Size, Cell_Size, LR_LOADFROMFILE);
		hbmp_White = (HBITMAP)LoadImage(NULL, _T("Cell_White.bmp"), IMAGE_BITMAP, Cell_Size, Cell_Size, LR_LOADFROMFILE);
		

		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				if (space[i][j].cell_state == true) {
					SelectObject(mdc, hbmp_Black);
					BitBlt(hDC, i * Cell_Size, j * Cell_Size, Cell_Size, Cell_Size, mdc, 0, 0, SRCCOPY);
				}
				else {
					SelectObject(mdc, hbmp_White);
					BitBlt(hDC, i * Cell_Size, j * Cell_Size, Cell_Size, Cell_Size, mdc, 0, 0, SRCCOPY);
				}
					
			}
		}
		DeleteObject(hbmp_Black);
		DeleteObject(hbmp_White);
		return true;
	}
	bool Re_Draw_Cell_Windows_Application(HDC hDC, int x, int y) {
		HDC mdc;
		HBITMAP hbmp_Black;
		HBITMAP hbmp_White;
		mdc = CreateCompatibleDC(hDC);

		hbmp_Black = (HBITMAP)LoadImage(NULL, _T("Cell_Black.bmp"), IMAGE_BITMAP, Cell_Size, Cell_Size, LR_LOADFROMFILE);
		hbmp_White = (HBITMAP)LoadImage(NULL, _T("Cell_White.bmp"), IMAGE_BITMAP, Cell_Size, Cell_Size, LR_LOADFROMFILE);

		if (space[x][y].cell_state == Live_Cell) {
			SelectObject(mdc, hbmp_Black);
			BitBlt(hDC, x * Cell_Size, y * Cell_Size, Cell_Size, Cell_Size, mdc, 0, 0, SRCCOPY);
		}
		else {
			SelectObject(mdc, hbmp_White);
			BitBlt(hDC, x * Cell_Size, y * Cell_Size, Cell_Size, Cell_Size, mdc, 0, 0, SRCCOPY);
		}
		DeleteObject(hbmp_Black);
		DeleteObject(hbmp_White);
		return true;
	}
	bool Draw_Space_MFC(CDC * pDC) {
		CBitmap bitmap_Cell_Black;
		CBitmap bitmap_Cell_White;
		CBitmap bitmap_Cell_Red;

		bitmap_Cell_Black.LoadBitmapW(IDB_Cell_Black);
		bitmap_Cell_White.LoadBitmapW(IDB_Cell_White);
		bitmap_Cell_Red.LoadBitmapW(IDB_Cell_Red);

		BITMAP tmp_Cell_Black;
		BITMAP tmp_Cell_White;
		BITMAP tmp_Cell_Red;
		bitmap_Cell_Black.GetBitmap(&tmp_Cell_Black);
		bitmap_Cell_White.GetBitmap(&tmp_Cell_White);
		bitmap_Cell_Red.GetBitmap(&tmp_Cell_Red);

		CDC MemDC_Cell_Black;
		MemDC_Cell_Black.CreateCompatibleDC(pDC);
		MemDC_Cell_Black.SelectObject(&bitmap_Cell_Black);
		CDC MemDC_Cell_White;
		MemDC_Cell_White.CreateCompatibleDC(pDC);
		MemDC_Cell_White.SelectObject(&bitmap_Cell_White);
		CDC MemDC_Cell_Red;
		MemDC_Cell_Red.CreateCompatibleDC(pDC);
		MemDC_Cell_Red.SelectObject(&bitmap_Cell_Red);

		for (int i = 0; i < SPACE_SIZE; i++) {
			for (int j = 0; j < SPACE_SIZE; j++) {
				if ( space[i][j].cell_state == Live_Cell && space[i][j].permanent == true ) {
					pDC->StretchBlt(i * Cell_Size, j * Cell_Size, Cell_Size, Cell_Size,
						&MemDC_Cell_Red, 0, 0, tmp_Cell_Red.bmWidth, tmp_Cell_Red.bmHeight, SRCCOPY);
				}
				if (space[i][j].cell_state == Live_Cell && space[i][j].permanent == false) {
					pDC->StretchBlt(i * Cell_Size, j * Cell_Size, Cell_Size, Cell_Size,
						&MemDC_Cell_Black, 0, 0, tmp_Cell_Black.bmWidth, tmp_Cell_Black.bmHeight,SRCCOPY);
				}
				else if (space[i][j].cell_state == Dead_Cell) {
					pDC->StretchBlt(i * Cell_Size, j * Cell_Size, Cell_Size, Cell_Size,
						&MemDC_Cell_White, 0, 0, tmp_Cell_White.bmWidth, tmp_Cell_White.bmHeight, SRCCOPY);
				}
			}
		}

		bitmap_Cell_Black.DeleteObject();
		bitmap_Cell_White.DeleteObject();
		bitmap_Cell_Red.DeleteObject();

		DeleteDC(MemDC_Cell_Black);
		DeleteDC(MemDC_Cell_White);
		DeleteDC(MemDC_Cell_Red);
		return true;
	}
	bool Re_Draw_Space_MFC(CDC * pDC, int x, int y) {
		CBitmap bitmap_Cell_Black;
		CBitmap bitmap_Cell_White;
		CBitmap bitmap_Cell_Red;

		bitmap_Cell_Black.LoadBitmapW(IDB_Cell_Black);
		bitmap_Cell_White.LoadBitmapW(IDB_Cell_White);
		bitmap_Cell_Red.LoadBitmapW(IDB_Cell_Red);

		BITMAP tmp_Cell_Black;
		BITMAP tmp_Cell_White;
		BITMAP tmp_Cell_Red;
		bitmap_Cell_Black.GetBitmap(&tmp_Cell_Black);
		bitmap_Cell_White.GetBitmap(&tmp_Cell_White);
		bitmap_Cell_Red.GetBitmap(&tmp_Cell_Red);

		CDC MemDC_Cell_Black;
		MemDC_Cell_Black.CreateCompatibleDC(pDC);
		MemDC_Cell_Black.SelectObject(&bitmap_Cell_Black);
		CDC MemDC_Cell_White;
		MemDC_Cell_White.CreateCompatibleDC(pDC);
		MemDC_Cell_White.SelectObject(&bitmap_Cell_White);
		CDC MemDC_Cell_Red;
		MemDC_Cell_Red.CreateCompatibleDC(pDC);
		MemDC_Cell_Red.SelectObject(&bitmap_Cell_Red);

		if (space[x][y].cell_state == Live_Cell && space[x][y].permanent == true) {
			pDC->StretchBlt(x * Cell_Size, y * Cell_Size, Cell_Size, Cell_Size,
				&MemDC_Cell_Red, 0, 0, tmp_Cell_Red.bmWidth, tmp_Cell_Red.bmHeight, SRCCOPY);
		}
		else if (space[x][y].cell_state == Live_Cell && space[x][y].permanent == false) {
			pDC->StretchBlt(x * Cell_Size, y * Cell_Size, Cell_Size, Cell_Size,
				&MemDC_Cell_Black, 0, 0, tmp_Cell_Black.bmWidth, tmp_Cell_Black.bmHeight, SRCCOPY);
		}
		else if (space[x][y].cell_state == Dead_Cell) {
			pDC->StretchBlt(x * Cell_Size, y * Cell_Size, Cell_Size, Cell_Size,
				&MemDC_Cell_White, 0, 0, tmp_Cell_White.bmWidth, tmp_Cell_White.bmHeight, SRCCOPY);
		}

		bitmap_Cell_Black.DeleteObject();
		bitmap_Cell_White.DeleteObject();
		bitmap_Cell_Red.DeleteObject();

		DeleteDC(MemDC_Cell_Black);
		DeleteDC(MemDC_Cell_White);
		DeleteDC(MemDC_Cell_Red);
		return true;
	}
};