#pragma once

#include "Space.h"
// MDlg_GameBody 对话框

class MDlg_GameBody : public CDialogEx
{
	DECLARE_DYNAMIC(MDlg_GameBody)

public:
	MDlg_GameBody(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MDlg_GameBody();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GameBody };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
private:
	POINT last_Position;
	POINT curr_Position;

public:
	Space * world;
	int Unit_Growing_Times;

	void Init_Serface();
	void Gaming(Space *, int);
	void Set_LeftRound();

	bool Change_Constant_trans_State();
	bool Constant_trans();

	bool Single_trans();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedUnittime1();
	afx_msg void OnBnClickedUnittime2();
	afx_msg void OnBnClickedUnittime3();
	afx_msg void OnBnClickedEndgame();
	int score;
	int Left_Round;
};
