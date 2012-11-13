// MYQQ.h : main header file for the MYQQ application
//

#if !defined(AFX_MYQQ_H__8F819FC1_FA6B_44EC_B7ED_BC232EDB4859__INCLUDED_)
#define AFX_MYQQ_H__8F819FC1_FA6B_44EC_B7ED_BC232EDB4859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMYQQApp:
// See MYQQ.cpp for the implementation of this class
//

class CMYQQApp : public CWinApp
{
public:
	CMYQQApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMYQQApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMYQQApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYQQ_H__8F819FC1_FA6B_44EC_B7ED_BC232EDB4859__INCLUDED_)
