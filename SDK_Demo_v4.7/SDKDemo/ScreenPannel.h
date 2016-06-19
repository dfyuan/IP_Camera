#if !defined(AFX_SCREENPANNEL_H__02697435_2EEB_4799_9465_6DA588866564__INCLUDED_)
#define AFX_SCREENPANNEL_H__02697435_2EEB_4799_9465_6DA588866564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenPannel.h : header file
//
#include "StdAfx.h"
#include "PlayWnd.h"

#ifndef MAXSCREEN
#define MAXSCREEN 16
#endif
/////////////////////////////////////////////////////////////////////////////
// CScreenPannel window

class CScreenPannel : public CWnd
{
// Construction
public:
	CScreenPannel();

// Attributes
public:

// Operations
public:

	bool		m_bRotate;
	int			m_rotaID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenPannel)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScreenPannel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CScreenPannel)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnSetCurScreen(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowMenu(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetZoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseMoveEx(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void HI_PANNEL_InitScreen(int mode);
	void HI_PANNEL_ShowScreen(int showMode);
	int	 HI_PANNEL_GetCurScreen();
	bool HI_PANNEL_GetFullScreen();
	void HI_PANNEL_SetFullScreen();
	int  HI_PANNEL_GetShowMode();
	
private:
	void ShowScreen(int showMode);
	void DrawLine();
	void DrawRect();
	void SetViewPos(int index, int left, int top, int right, int bottom);

public:
	CPlayWnd	m_PlayWnd[25];

private:
	CRect		m_ScreenRect[MAXSCREEN];
	int			m_ShowMode;
	int			m_nCurScreen;
	int			m_nWidth, m_nHeight;
	int			m_tWidth, m_tHeight;

	bool		m_bZoom;
	bool		m_bFullScreen;

	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent
	HWND		hWndParent;

	CRITICAL_SECTION      m_cs;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENPANNEL_H__02697435_2EEB_4799_9465_6DA588866564__INCLUDED_)
