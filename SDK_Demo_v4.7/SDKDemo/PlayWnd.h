#if !defined(AFX_PLAYWND_H__9156FF14_F1F1_41EC_9875_4EEC32CC77FA__INCLUDED_)
#define AFX_PLAYWND_H__9156FF14_F1F1_41EC_9875_4EEC32CC77FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayWnd.h : header file
//
//#include "VideoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// PlayWnd window
#define WM_WND_LBUTTONDBLCLK	WM_USER+100
#define WM_WND_LBUTTONDOWN		WM_USER+102
#define WM_WND_RBUTTONDOWN		WM_USER+103
#define WM_WND_MOUSEMOVE		WM_USER+104

class CPlayWnd : public CWnd
{
// Construction
public:
	CPlayWnd();
	void HI_SetScreenID(int index);

// Attributes
private:
	int		m_nScreenID;
	HWND	hWndParent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PlayWnd)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPlayWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(PlayWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYWND_H__9156FF14_F1F1_41EC_9875_4EEC32CC77FA__INCLUDED_)
