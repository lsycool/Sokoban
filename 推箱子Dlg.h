// 推箱子Dlg.h : header file
//

#if !defined(AFX_DLG_H__671C9C0E_CCC5_4500_8A1E_CDA3775D7363__INCLUDED_)
#define AFX_DLG_H__671C9C0E_CCC5_4500_8A1E_CDA3775D7363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	void LoadPicture(CDC* pDC);
	void DrawManBall(int x,int y,CDC* pDC);
	void DrawMan(int x,int y,CDC* pDC);
	void DrawRedBox(int x,int y,CDC* pDC);
	void DrawBox(int x,int y,CDC* pDC);
	void DrawDestination(int x, int y, CDC *pDC);
	void DrawPassage(int x,int y,CDC *pDC);
	void DrawGrayWall(int x,int y,CDC *pDC);
	void DrawBackground(int x, int y, CDC *pDC);
	void DrawMap(CDC *pDC);
	void UpdateMap(UINT nChar);
	void ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3);
	BOOL IsSucceed();
	CPoint GetManPosition();
	CMyDlg OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	void Playmusic(BOOL bCheck);
	void LoadMap(int);
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL Check;//用于控制音乐播放
	char m_cMap[20][20];//用来存放地图文件的
	CPoint m_ManPosition;//记录人的位置

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMusic();
	afx_msg void OnExitGame();
	afx_msg void OnStartGame();
	afx_msg void OnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__671C9C0E_CCC5_4500_8A1E_CDA3775D7363__INCLUDED_)
