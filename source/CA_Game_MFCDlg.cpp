
// CA_Game_MFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CA_Game_MFC.h"
#include "CA_Game_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCAGameMFCDlg 对话框



CCAGameMFCDlg::CCAGameMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CA_GAME_MFC_DIALOG, pParent)
	, Unit_Growing_Times(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCAGameMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Unit_Growing_Times);
}

BEGIN_MESSAGE_MAP(CCAGameMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CCAGameMFCDlg::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_StartGame, &CCAGameMFCDlg::OnBnClickedStartgame)
	ON_BN_CLICKED(IDC_EndGame, &CCAGameMFCDlg::OnBnClickedEndgame)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCAGameMFCDlg 消息处理程序

BOOL CCAGameMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UpdateData(true);
	Unit_Growing_Times = 1;
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCAGameMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCAGameMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCAGameMFCDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);

	if (pNMUpDown->iDelta == -1) {
		Unit_Growing_Times++;
	}
	else if (pNMUpDown->iDelta == 1) {
		Unit_Growing_Times--;
	}

	if (Unit_Growing_Times < 0)
		Unit_Growing_Times = 0;

	UpdateData(false);

	*pResult = 0;
}


void CCAGameMFCDlg::OnBnClickedStartgame()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(ID_Listening_GameBody, Gap_Listening_GameBody, NULL);

	Game_Start_Movement = true;

	MDlg_GameBody * game_body;
	game_body = new MDlg_GameBody;

	game_body->Init_Serface();
	game_body->Gaming(&world, Unit_Growing_Times);

	//ShowWindow(SW_HIDE);
	this->SetWindowPos(NULL, -100, -100, -100, -100, NULL);

	//EndDialog(IDC_StartGame);
}


void CCAGameMFCDlg::OnBnClickedEndgame()
{
	// TODO: 在此添加控件通知处理程序代码
	Game_Start_Movement = false;
	EndDialog(IDC_StartGame);
}


void CCAGameMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case ID_Listening_GameBody: {
		if (world.Game_Status == false)
			EndDialog(IDC_StartGame);
		if (world.Get_Cell_State(SPACE_SIZE / 2, SPACE_SIZE / 2) == Dead_Cell && world.Game_Over_flag == false) {
			world.Game_Over_flag = true;
			MessageBox(_T("游戏结束"));
			Sleep(2000);
			EndDialog(IDD_GameBody);
		}
		if (world.Game_End_flag == true) {
			world.Game_End_flag = false;
			EndDialog(IDD_GameBody);
		}
	}
								break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
