// MYQQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MYQQ.h"
#include "MYQQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CMYQQDlg dialog

CMYQQDlg::CMYQQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMYQQDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMYQQDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMYQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMYQQDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMYQQDlg, CDialog)
	//{{AFX_MSG_MAP(CMYQQDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSEND, OnSend)
	ON_BN_CLICKED(IDC_BUTTONFONT, OnButtonfont)
	ON_BN_CLICKED(IDC_BUTTONCOLOR, OnButtoncolor)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECVDATA, OnRecvData)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMYQQDlg message handlers

BOOL CMYQQDlg::OnInitDialog()
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
	/***********************************************************************
	**file:         MYQQ.cpp
	**Author:       Freeking
	**Created:      Oct 9th 2009
	**Description:  socket  编程实现QQ的聊天界面
	*************************************************************************/
	// 网络编程初始化
	InitSocket();
	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socket;
	pRecvParam->hwnd = m_hWnd;
	
	HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	CloseHandle(hThread);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMYQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMYQQDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMYQQDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//创建并初始化套接字
bool CMYQQDlg::InitSocket()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		AfxMessageBox("套接字创建失败！");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	int retval;
	// tie to socket
	retval = bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == retval)
	{
		closesocket(m_socket);
		MessageBox("绑定失败！");
		return FALSE;
	}
	return 0;
}

DWORD WINAPI CMYQQDlg::RecvProc(LPVOID lpParmeter)
{
	SOCKET sock = ((RECVPARAM*)lpParmeter)->sock;
	HWND hwnd = ((RECVPARAM*)lpParmeter)->hwnd;
	delete lpParmeter;
	
	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	
	char recvBuf[200];
	char tempBuf[300];
	int retval;
	while (TRUE)
	{
		// receive data
		retval = recvfrom(sock, recvBuf, 200, 0, (SOCKADDR*)&addrFrom, &len);
		if (SOCKET_ERROR == retval)
			break;
		sprintf(tempBuf, "%s 说：%s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		::PostMessage(hwnd, WM_RECVDATA, 0, (LPARAM)tempBuf);
	}
	return 0;
}
void CMYQQDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	CString str = (char *)lParam;
	CString tempstr;
	GetDlgItemText(IDC_EDITRECV, tempstr);
	str += "\r\n";
	str += tempstr;
	SetDlgItemText(IDC_EDITRECV, str);
}

void CMYQQDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	DWORD dwIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESSQQ))->GetAddress(dwIP);
	SOCKADDR_IN addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6000);
	addrTo.sin_addr.S_un.S_addr = htonl(dwIP);
	
	CString strSend;
	GetDlgItemText(IDC_EDITSEND, strSend);
	
	sendto(m_socket, strSend, strSend.GetLength() + 1, 0, 
		(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
	
	SetDlgItemText(IDC_EDITSEND, "");
}

void CMYQQDlg::OnButtonfont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
	if(IDOK==dlg.DoModal())
	{
		if(m_font.m_hObject)
			m_font.DeleteObject();
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName=dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();
	}
}

void CMYQQDlg::OnButtoncolor() 
{

	CColorDialog dlg;
	dlg.m_cc.Flags|=CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult=m_clr;
	if(IDOK==dlg.DoModal())
	{
		m_clr=dlg.m_cc.rgbResult;
	}
}
