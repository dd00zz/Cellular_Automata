
// CA_Game_MFCDlg.h: 头文件
//

#pragma once

#include "MDlg_GameBody.h"
#include "Space.h"

#define ID_Listening_GameBody 2020
#define Gap_Listening_GameBody 1000

// CCAGameMFCDlg 对话框
class CCAGameMFCDlg : public CDialogEx
{
// 构造
public:
	CCAGameMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CA_GAME_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Space world;

	int Unit_Growing_Times;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnBnClickedEndgame();

	bool Game_Start_Movement;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
