// SelectLever.cpp : implementation file
//

#include "stdafx.h"
#include "推箱子.h"
#include "SelectLever.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSelectLever dialog


CSelectLever::CSelectLever(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectLever::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectLever)
	m_lever = 1;
	//}}AFX_DATA_INIT
}


void CSelectLever::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectLever)
	DDX_Text(pDX, IDC_EDIT1, m_lever);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectLever, CDialog)
	//{{AFX_MSG_MAP(CSelectLever)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectLever message handlers

void CSelectLever::OnOK() 
{
	// TODO: Add extra validation here
	CString string1;
	CString string2;

	UpdateData(TRUE);
//	g_level=m_lever;
	string1.Format("欢迎进入第 %u 关",m_lever);
	string2.Format("请输入一个小于 %u 的数",g_maxlevel);
	if(m_lever<=g_maxlevel)
	{
	   g_level=m_lever;
	   MessageBox(string1);
	}
	else
	{
		MessageBox(string2);
	}


	CDialog::OnOK();
}

int CSelectLever::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_lever = g_level;
	return CDialog::DoModal();

}

BOOL CSelectLever::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lever = g_level;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
