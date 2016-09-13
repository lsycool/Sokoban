// 推箱子Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "推箱子.h"
#include "推箱子Dlg.h"
#include <mmsystem.h>
#include "SelectLever.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT g_level = 1;//当前关数
UINT g_maxlevel =42;


#define MAP_BACKGROUND 0x30//黑色的背景
#define MAP_GRAYWALL   0x31//白灰的砖墙
#define MAP_PASSAGE    0x32//蓝色可以行走的路
#define MAP_DESTINATION       0x33//箱子应该推倒的地方
#define MAP_BOX		   0x34//箱子
#define MAP_REDBOX     0x35//红色的箱子，箱子推到目的地后变成红色
#define MAP_MAN		   0x36//人
#define MAP_MANBALL    0x37//人走到目的地后的变化

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Check=TRUE;
	LoadMap(g_level);//预加载第一关
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MUSIC, OnMusic)
	ON_COMMAND(ID_EXIT_GAME, OnExitGame)
	ON_COMMAND(ID_START_GAME, OnStartGame)
	ON_COMMAND(ID_SELECT, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	CMenu menu;//声明菜单对象
	menu.LoadMenu(IDR_MENU1);//加载用户自定义菜单
	this->SetMenu(&menu);//设置自定义菜单替换现有菜单 

	menu.CheckMenuItem(ID_MUSIC,MF_BYCOMMAND | MF_UNCHECKED);//菜单项打开了一个子菜单，该函数也返回子菜单里的菜单项数
	
	Playmusic(TRUE);

	OnStartGame();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		DrawMap(&dc);
		LoadPicture(&dc);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnMusic() 
{
	// TODO: Add your command handler code here
	Check=!Check;
	Playmusic(Check);			//调用播放背景音乐功能函数
    
}

void CMyDlg::Playmusic(BOOL bCheck)
{
	CString strFileName;
    strFileName.Format("无颜女.mp3");
    CString strCommond;
    strCommond.Format("play %s repeat", strFileName );
    if(bCheck)
	{
       mciSendString(strCommond,NULL,0,NULL);//播放音乐
	}
	else
	{
	   strCommond.Format("pause %s ", strFileName );//暂停播放
	   mciSendString(strCommond,NULL,0,NULL);
	}
}

void CMyDlg::OnExitGame() 
{
	// TODO: Add your command handler code here
	CDialog::OnCancel();
	
}


void CMyDlg::LoadMap(int iMissionNum)
{
	CString str;
    str.Format("[%d]", iMissionNum);
	
	FILE *pFile = fopen("map.txt", "rb");//读取二进制文件
	if (pFile == NULL)
        return;
	
    char cTmp[20];
    fgets(cTmp, 20, pFile);//从文件中读取19个字符存到数组cTmp中
    while (strncmp(cTmp, str, 3) != 0)//比较两字符串前三个字符是否相等，即用来选择关卡
    {
        fgets(cTmp, 20, pFile);
    }
	
    for (int i = 0; i < 14; i++)//将该关的的地图载入到数组中
        fgets(m_cMap[i], 20, pFile);//读取n-1个字符，存到以s为起始地址的空间里，直到读完一行，如果成功则返回s的指针，否则返回NULL。
	
    fclose(pFile);

}

void CMyDlg::OnStartGame() 
{
	// TODO: Add your command handler code here
	LoadMap(g_level);//加载地图
	m_ManPosition=GetManPosition();//获取初始状态人的位置
	Invalidate();//该函数的作用是使整个窗口客户区无效。窗口的客户区无效意味着需要重绘,参数为TRUE时，重绘区域内的背景将被擦除，否则，背景将保持不变。
}

CPoint CMyDlg::GetManPosition()
{
	CPoint manPosition(0, 0);
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (m_cMap[i][j] == MAP_MAN || m_cMap[i][j] == MAP_MANBALL)//在地图中找到人的位置，即给人的位置赋初值
            {
                manPosition.x = j;
                manPosition.y = i;
            }
        }
    }
    return manPosition;
}

BOOL CMyDlg::IsSucceed()
{
	for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (m_cMap[i][j] == MAP_DESTINATION || m_cMap[i][j] == MAP_MANBALL)//是否还存目的地（即目的地还没有被箱子覆盖）
			{
                return FALSE;
			}
        }
    }
    return TRUE;

}

void CMyDlg::ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
	switch (m_cMap[y2][x2])
    {
    case MAP_BACKGROUND:           //根据操作步骤判断，和重绘地图
        MessageBox("地图有问题");
        break;
    case MAP_GRAYWALL:          
        break;
    case MAP_PASSAGE:           
        m_cMap[y2][x2] = MAP_MAN;
        if (m_cMap[y1][x1] == MAP_MAN)
            m_cMap[y1][x1] = MAP_PASSAGE;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_DESTINATION;
        m_ManPosition.x = x2;
        m_ManPosition.y = y2;
        break;
    case MAP_DESTINATION:            
        m_cMap[y2][x2] = MAP_MANBALL;
        if (m_cMap[y1][x1] == MAP_MAN)
            m_cMap[y1][x1] = MAP_PASSAGE;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_DESTINATION;        
        m_ManPosition.x = x2;
        m_ManPosition.y = y2;
        break;
    case MAP_BOX:         
        if (m_cMap[y3][x3] == MAP_DESTINATION) 
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MAN;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_PASSAGE;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_DESTINATION;
            m_ManPosition.x = x2;
            m_ManPosition.y = y2;
        }
        else if (m_cMap[y3][x3] == MAP_PASSAGE) 
        {
            m_cMap[y3][x3] = MAP_BOX;
            m_cMap[y2][x2] = MAP_MAN;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_PASSAGE;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_DESTINATION;
            m_ManPosition.x = x2;
            m_ManPosition.y = y2;
        }
        break;
    case MAP_REDBOX:             
        if (m_cMap[y3][x3] == MAP_DESTINATION)
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_PASSAGE;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_DESTINATION;
            m_ManPosition.x = x2;
            m_ManPosition.y = y2;
        }
        else if (m_cMap[y3][x3] == MAP_PASSAGE)
        {
            m_cMap[y3][x3] = MAP_BOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_PASSAGE;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_DESTINATION;
            m_ManPosition.x = x2;
            m_ManPosition.y = y2;
        }        
        break;
    case MAP_MAN:            //地图有问题
        MessageBox("地图有问题");
        break;
    case MAP_MANBALL:            //地图有问题
        MessageBox("地图有问题");
        break;
    }

}

void CMyDlg::UpdateMap(UINT nChar)
{
	int x1, y1, x2, y2, x3, y3;
	
    x1 = m_ManPosition.x;
    y1 = m_ManPosition.y;
	
    switch (nChar)//针对人走的不同方式，分别重绘地图
    {
    case VK_UP:
        x2 = x1;
        y2 = y1 - 1;
        x3 = x1;
        y3 = y1 - 2;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_DOWN:
        x2 = x1;
        y2 = y1 + 1;
        x3 = x1;
        y3 = y1 + 2;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_LEFT:
        x2 = x1 - 1;
        y2 = y1;
        x3 = x1 - 2;
        y3 = y1;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_RIGHT:
        x2 = x1 + 1;
        y2 = y1;
        x3 = x1 + 2;
        y3 = y1;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
	default:
		break;
    }
}

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) //截获你的按键消息，并触发函数
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) 
	{ 
		UpdateMap(pMsg->wParam);//记录按下的方向键
		Invalidate(false);
		if (IsSucceed())
		{
			AfxMessageBox("哈哈，您获得胜利,将进入下一关，加油哦!");
			g_level = g_level +1;
			if (g_level > g_maxlevel)
				g_level = 1;
			OnStartGame();
			
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMyDlg::DrawMap(CDC *pDC)
{
	int i, j, x, y;
    for (i = 0; i < 14; i++)
    {
        for (j = 0; j < 16; j++)
        {
			x = j * 20;
            y = i * 20;
            switch (m_cMap[i][j])
            {
            case MAP_BACKGROUND://0
                DrawBackground(x, y, pDC);
                break;
            case MAP_GRAYWALL://1
                DrawGrayWall(x, y, pDC);
                break;
            case MAP_PASSAGE://2
                DrawPassage(x, y, pDC);
                break;
            case MAP_DESTINATION://3
                DrawDestination(x, y, pDC);
                break;
            case MAP_BOX://4
                DrawBox(x, y, pDC);
                break;
            case MAP_REDBOX://5
                DrawRedBox(x, y, pDC);
                break;
            case MAP_MAN://6
                DrawMan(x, y, pDC);
                break;
            case MAP_MANBALL://7
                DrawManBall(x, y, pDC);
                break;
            }
        }
	}
}

void CMyDlg::DrawBackground(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);//用指定的固体色黑色填充矩形，即预设每个方格大小都是20*20，颜色为黑色
}

void CMyDlg::DrawGrayWall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(80, 80, 80);//重新设定墙的颜色
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 20);//给每两个墙之间划边界线
    pDC->LineTo(x + 20, y + 20);
    pDC->MoveTo(x + 20, y );
    pDC->LineTo(x + 20, y + 20);
}

void CMyDlg::DrawPassage(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 255);//设置过道颜色为白色
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 20);//划两过道边界线
    pDC->LineTo(x + 20, y + 20);
    pDC->MoveTo(x + 20, y + 20);
    pDC->LineTo(x , y + 20);

}

void CMyDlg::DrawDestination(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 255);
	COLORREF clr1 = RGB(0,0,0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
	CPen pen;
	CPen* oldpen;
	pen.CreatePen(PS_SOLID,1,clr1);
	oldpen = pDC->SelectObject(&pen);
    pDC->MoveTo(x + 10, y);
    pDC->LineTo(x + 10, y + 20);
    pDC->MoveTo(x ,  y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->Ellipse(x, y, x + 20, y + 20); 
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);
	pDC->SelectObject(oldpen);

}

void CMyDlg::DrawBox(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 0);//黄色的边框
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 192, 0);//橙色的箱子
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);//各个角为黑色
    pDC->SetPixel(x + 3, y + 3, clr3);
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);

}

void CMyDlg::DrawRedBox(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 0);//黄色边框
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 0, 0);//红色箱子
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);//四个角为黑色
    pDC->SetPixel(x + 3, y + 3, clr3);//画像素点
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);
}

void CMyDlg::DrawMan(int x, int y, CDC *pDC)
{
	/*自己画的人
	COLORREF clr = RGB(255, 0,0 );       //红色的人
	pDC->FillSolidRect(x,y,20,20,RGB(255,255,255));
	CPen pen;
	CPen* OldPen;
	pen.CreatePen(PS_SOLID,3,clr);
	OldPen = pDC->SelectObject(&pen);
	
    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //画人头，Ellipse（左上角坐标，右下角）椭圆函数
	
    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);
	
    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 13);
	
    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10,y + 13);
	pDC->MoveTo(x + 10,y + 13);
    pDC->LineTo(x + 18, y +20);
	pDC->SelectObject(OldPen);
*/

//愤怒的小鸟
	CDC dcCompatible;//创建一个兼容DC，用于显示屏幕
	dcCompatible.CreateCompatibleDC(pDC);//创建及装入位图资源
	CBitmap bmp;
	CBitmap* oldbmp;
	bmp.LoadBitmap(IDB_BITMAP7);//载入位图
	oldbmp=dcCompatible.SelectObject(&bmp);//将位图选入兼容DC
	BITMAP bitmap;//对象包含
	bmp.GetBitmap(&bitmap);
    pDC->StretchBlt(x,y,20,20,&dcCompatible,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	bmp.DeleteObject();
	dcCompatible.SelectObject(oldbmp);
	dcCompatible.DeleteDC();
}

void CMyDlg::DrawManBall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 0,0 ); //红色的人
	pDC->FillSolidRect(x,y,20,20,RGB(255,255,255));
	CPen pen;
	CPen* OldPen;
	pen.CreatePen(PS_SOLID,3,clr);
	OldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y);
    pDC->LineTo(x + 10, y + 20);

	pDC->Ellipse(x, y, x + 20, y + 20);//画目的地标志
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);

    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //画人头，Ellipse（左上角坐标，右下角）椭圆函数
	
    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);
	
    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 12);
	
    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
	pDC->SelectObject(OldPen);


}

void CMyDlg::LoadPicture(CDC *pDC)
{
	CDC dcCompatible;//创建一个兼容DC，用于显示屏幕
	dcCompatible.CreateCompatibleDC(pDC);//创建及装入位图资源
	CBitmap bmp;
	CBitmap* oldbmp;
	bmp.LoadBitmap(IDB_BITMAP5);//载入位图
	oldbmp=dcCompatible.SelectObject(&bmp);//将位图选入兼容DC
	BITMAP bitmap;//对象包含
	bmp.GetBitmap(&bitmap);
    pDC->StretchBlt(330,0,300,300,&dcCompatible,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	bmp.DeleteObject();
	dcCompatible.SelectObject(oldbmp);
	dcCompatible.DeleteDC();

}

void CMyDlg::OnSelect() 
{
	// TODO: Add your command handler code here
	CSelectLever select;
	select.DoModal();
}
