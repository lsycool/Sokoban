#if !defined(AFX_SELECTLEVER_H__4D0CC6FA_5FCE_4372_AE09_1FAF85D419A0__INCLUDED_)
#define AFX_SELECTLEVER_H__4D0CC6FA_5FCE_4372_AE09_1FAF85D419A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectLever.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectLever dialog

class CSelectLever : public CDialog
{
// Construction
public:
	CSelectLever(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectLever)
	enum { IDD = IDD_DIALOG1 };
	UINT	m_lever;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectLever)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectLever)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTLEVER_H__4D0CC6FA_5FCE_4372_AE09_1FAF85D419A0__INCLUDED_)
