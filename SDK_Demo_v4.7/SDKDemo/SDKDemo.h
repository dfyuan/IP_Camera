// SDKDemo.h : main header file for the SDKDEMO application
//

#if !defined(AFX_SDKDEMO_H__DEFF602C_2F5F_4DAC_8FE1_D0A23ACE5778__INCLUDED_)
#define AFX_SDKDEMO_H__DEFF602C_2F5F_4DAC_8FE1_D0A23ACE5778__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

extern void g_SetWndStaticText(CWnd * pWnd);
extern CString ConvertString(CString strText);
/////////////////////////////////////////////////////////////////////////////
// CSDKDemoApp:
// See SDKDemo.cpp for the implementation of this class
//

class CSDKDemoApp : public CWinApp
{
public:
	CSDKDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDKDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSDKDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDKDEMO_H__DEFF602C_2F5F_4DAC_8FE1_D0A23ACE5778__INCLUDED_)
