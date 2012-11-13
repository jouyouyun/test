// MYQQDlg.h : header file
//

#if !defined(AFX_MYQQDLG_H__B397C977_0B7B_49C5_9B1C_9B5A5336C574__INCLUDED_)
#define AFX_MYQQDLG_H__B397C977_0B7B_49C5_9B1C_9B5A5336C574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//自定义接受数据的消息
#define WM_RECVDATA WM_USER+1

/////////////////////////////////////////////////////////////////////////////
// CMYQQDlg dialog

class CMYQQDlg : public CDialog
{
// Construction
public:
	CString m_strFontName;
	CFont m_font;
	COLORREF m_clr;
	//线程调用函数不能为类的成员函数
	static DWORD WINAPI RecvProc(LPVOID lpParmeter);

	CMYQQDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMYQQDlg)
	enum { IDD = IDD_MYQQ_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMYQQDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMYQQDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnButtonfont();
	afx_msg void OnButtoncolor();
	//}}AFX_MSG
	afx_msg void OnRecvData(WPARAM	wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_socket;
	bool InitSocket();
};

struct RECVPARAM
{
	SOCKET	sock;
	HWND	hwnd;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYQQDLG_H__B397C977_0B7B_49C5_9B1C_9B5A5336C574__INCLUDED_)
