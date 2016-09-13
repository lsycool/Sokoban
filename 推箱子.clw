; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelectLever
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "推箱子.h"

ClassCount=4
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG1
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_MY_DIALOG
Class4=CSelectLever
Resource5=IDR_MENU1

[CLS:CMyApp]
Type=0
HeaderFile=推箱子.h
ImplementationFile=推箱子.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=推箱子Dlg.h
ImplementationFile=推箱子Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_SELECT

[CLS:CAboutDlg]
Type=0
HeaderFile=推箱子Dlg.h
ImplementationFile=推箱子Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_START_GAME
Command2=ID_EXIT_GAME
Command3=ID_MUSIC
Command4=ID_SELECT
CommandCount=4

[DLG:IDD_DIALOG1]
Type=1
Class=CSelectLever
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEVER,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CSelectLever]
Type=0
HeaderFile=SelectLever.h
ImplementationFile=SelectLever.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

