// MDlg_GameBody.cpp: 实现文件
//

#include "pch.h"
#include "CA_Game_MFC.h"
#include "MDlg_GameBody.h"
#include "afxdialogex.h"
#include "MDlg_GameBody.h"


// MDlg_GameBody 对话框

IMPLEMENT_DYNAMIC(MDlg_GameBody, CDialogEx)

MDlg_GameBody::MDlg_GameBody(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GameBody, pParent)
	, score(0)
	, Left_Round(0)
{

}

MDlg_GameBody::~MDlg_GameBody()
{
}

void MDlg_GameBody::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Score, score);
	DDX_Text(pDX, IDC_LeftRound, Left_Round);
}


BEGIN_MESSAGE_MAP(MDlg_GameBody, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	//ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Unittime_1, &MDlg_GameBody::OnBnClickedUnittime1)
	ON_BN_CLICKED(IDC_Unittime_2, &MDlg_GameBody::OnBnClickedUnittime2)
	ON_BN_CLICKED(IDC_Unittime_3, &MDlg_GameBody::OnBnClickedUnittime3)
	ON_BN_CLICKED(IDC_EndGame, &MDlg_GameBody::OnBnClickedEndgame)
END_MESSAGE_MAP()


// MDlg_GameBody 消息处理程序

void MDlg_GameBody::Init_Serface() {
	this->Create(IDD_GameBody);

	int ButtonSize_High = 25;
	int ButtonSize_Width = 75;
	int StaticSize_High = 50;
	int StaticSize_Width = 100;
	int EditSize_High = 25;
	int EditSize_Width = 50;

	int space_size_width = (SPACE_SIZE)* Cell_Size + Cell_Size * 2 / 3;
	int space_size_high = (SPACE_SIZE)* Cell_Size + Cell_Size * 5 / 3;

	CWnd * pWnd;

	int IDC_Score_High = EditSize_High;
	int IDC_Score_Width = EditSize_Width;
	int IDC_Score_x = space_size_width + 20;
	int IDC_Score_y = 30;

	pWnd = GetDlgItem(IDC_Score);
	pWnd->MoveWindow(IDC_Score_x, IDC_Score_y,
		IDC_Score_Width, IDC_Score_High);

	int IDC_GameBody_Unittime_Tips_High = IDC_Score_High;
	int IDC_GameBody_Unittime_Tips_Width = IDC_Score_Width;
	int IDC_GameBody_Unittime_Tips_x = IDC_Score_x;
	int IDC_GameBody_Unittime_Tips_y = 30;
	
	pWnd = GetDlgItem(IDC_GameBody_Unittime_Tips);
	pWnd->MoveWindow(IDC_GameBody_Unittime_Tips_x, IDC_GameBody_Unittime_Tips_y,
		IDC_GameBody_Unittime_Tips_Width, IDC_GameBody_Unittime_Tips_High);

	int IDC_Unittime_1_High = ButtonSize_High;
	int IDC_Unittime_1_Width = ButtonSize_Width;
	int IDC_Unittime_1_x = IDC_Score_x;
	int IDC_Unittime_1_y = IDC_GameBody_Unittime_Tips_y + IDC_GameBody_Unittime_Tips_High + 20;


	pWnd = GetDlgItem(IDC_Unittime_1);
	pWnd->MoveWindow(IDC_Unittime_1_x, IDC_Unittime_1_y,
		IDC_Unittime_1_Width, IDC_Unittime_1_High);

	int IDC_Unittime_2_High = ButtonSize_High;
	int IDC_Unittime_2_Width = ButtonSize_Width;
	int IDC_Unittime_2_x = IDC_Score_x;
	int IDC_Unittime_2_y = IDC_Unittime_1_y + IDC_Unittime_1_High + 20;

	pWnd = GetDlgItem(IDC_Unittime_2);
	pWnd->MoveWindow(IDC_Unittime_2_x, IDC_Unittime_2_y,
		IDC_Unittime_2_Width, IDC_Unittime_2_High);

	int IDC_Unittime_3_High = ButtonSize_High;
	int IDC_Unittime_3_Width = ButtonSize_Width;
	int IDC_Unittime_3_x = IDC_Score_x;
	int IDC_Unittime_3_y = IDC_Unittime_2_y + IDC_Unittime_2_High + 20;

	pWnd = GetDlgItem(IDC_Unittime_3);
	pWnd->MoveWindow(IDC_Unittime_3_x, IDC_Unittime_3_y,
		IDC_Unittime_3_Width, IDC_Unittime_3_High);

	int IDC_EndGame_High = ButtonSize_High;
	int IDC_EndGame_Width = ButtonSize_Width;
	int IDC_EndGame_x = IDC_Score_x;
	int IDC_EndGame_y = space_size_high - IDC_EndGame_High - 60;
	
	pWnd = GetDlgItem(IDC_EndGame);
	pWnd->MoveWindow(IDC_EndGame_x, IDC_EndGame_y,
		IDC_EndGame_Width, IDC_EndGame_High);

	

	this->SetWindowPos(NULL,
		0, //x
		0, //y
		space_size_width + IDC_Unittime_1_Width + 60, //宽
		space_size_high, //高
		SWP_NOZORDER | SWP_NOMOVE);

	this->ShowWindow(SW_SHOW);
}

void MDlg_GameBody::Gaming(Space * _world, int _Unit_Growing_Times) {
	world = _world;

	CDC * pDC = GetDC();

	world->Cell_Random_Jumping();
	world->Draw_Space_MFC(pDC);

	world->Game_Status = true;

	Unit_Growing_Times = _Unit_Growing_Times;
}

void MDlg_GameBody::Set_LeftRound() {
	UpdateData(true);
	score = 20;
	UpdateData(false);
}

bool MDlg_GameBody::Change_Constant_trans_State() {
	world->auto_trans_moving_enable_flag = !world->auto_trans_moving_enable_flag;
	return true;
}
bool MDlg_GameBody::Constant_trans() {
	if (world->auto_trans_moving_enable_flag == true) {
		CDC * cdc = GetDC();

		POINT init_Point_Position = { 0,0 };
		LPPOINT mouse_Position = &init_Point_Position;
		GetCursorPos(mouse_Position);

		ScreenToClient(mouse_Position);

		int Cell_changing_state_x = (mouse_Position->x) / Cell_Size;
		int Cell_changing_state_y = (mouse_Position->y) / Cell_Size;

		curr_Position.x = Cell_changing_state_x;
		curr_Position.y = Cell_changing_state_y;

		if (curr_Position.x != last_Position.x || curr_Position.y != last_Position.y) {
			if (Cell_changing_state_x < SPACE_SIZE
				&& Cell_changing_state_x >= 0
				&& Cell_changing_state_y < SPACE_SIZE
				&& Cell_changing_state_y >= 0) {
				world->Change_Cell_State(Cell_changing_state_x, Cell_changing_state_y);
				world->Re_Draw_Space_MFC(cdc, Cell_changing_state_x, Cell_changing_state_y);
			}

		}
		last_Position = curr_Position;

		ReleaseDC(cdc);
	}
	return true;
}

bool MDlg_GameBody::Single_trans() {
	CDC * cdc = GetDC();

	cdc->SetViewportOrg(0, 0);

	POINT init_Point_Position = { 0,0 };
	LPPOINT mouse_Position = &init_Point_Position;
	GetCursorPos(mouse_Position);

	ScreenToClient(mouse_Position);

	int Cell_changing_state_x = (mouse_Position->x) / Cell_Size;
	int Cell_changing_state_y = (mouse_Position->y) / Cell_Size;

	if (Cell_changing_state_x < SPACE_SIZE
		&& Cell_changing_state_x >= 0
		&& Cell_changing_state_y < SPACE_SIZE
		&& Cell_changing_state_y >= 0) {
		world->Change_Cell_State(Cell_changing_state_x, Cell_changing_state_y);
		world->Re_Draw_Space_MFC(cdc, Cell_changing_state_x, Cell_changing_state_y);
	}
	last_Position = curr_Position;

	ReleaseDC(cdc);

	return true;
}

void MDlg_GameBody::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC * pDC = GetDC();

	if (world->Game_Status == true && world->auto_growing_enable_flag == false) {
		Single_trans();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void MDlg_GameBody::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC * pDC = GetDC();

	if (Unit_Growing_Times > 1) {
		for (int i = 0; i < Unit_Growing_Times; i++) {
			world = world->Cell_Growing();
			world->Draw_Space_MFC(pDC);
			Left_Round--;
			Sleep(400);
		}
	}
	else {
		world = world->Cell_Growing();
		world->Draw_Space_MFC(pDC);
		Left_Round--;
	}
	
	if (Left_Round == 0) {
		world->Game_End_flag = true;
	}

	ReleaseDC(pDC);

	CDialogEx::OnRButtonDown(nFlags, point);
}


void MDlg_GameBody::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	Constant_trans();

	CDialogEx::OnMouseMove(nFlags, point);
}


void MDlg_GameBody::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
		//按M启用自动翻转
	case 77: {
		if (world->Game_Status == true)
			Change_Constant_trans_State();
	}
			 break;
		//按L调试用
	/*case 76: {
		CDC * cdc = GetDC();
		world->Re_Draw_Space_MFC(cdc, SPACE_SIZE / 2, SPACE_SIZE / 2);
		ReleaseDC(cdc);
	}
			 break;*/
	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


//void MDlg_GameBody::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//
//	world->Game_Status = false;
//
//	// TODO: 在此处添加消息处理程序代码
//}


void MDlg_GameBody::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	world->Game_Status = false;

	CDialogEx::OnClose();
}


void MDlg_GameBody::OnBnClickedUnittime1()
{
	// TODO: 在此添加控件通知处理程序代码
	Unit_Growing_Times = 1;
}


void MDlg_GameBody::OnBnClickedUnittime2()
{
	// TODO: 在此添加控件通知处理程序代码
	Unit_Growing_Times = 2;
}


void MDlg_GameBody::OnBnClickedUnittime3()
{
	// TODO: 在此添加控件通知处理程序代码
	Unit_Growing_Times = 3;
}


void MDlg_GameBody::OnBnClickedEndgame()
{
	// TODO: 在此添加控件通知处理程序代码
	world->Game_End_flag = true;
	EndDialog(IDD_GameBody);
}
