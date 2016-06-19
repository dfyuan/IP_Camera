// CPlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PlayWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PlayWnd

CPlayWnd::CPlayWnd()
{
	m_nScreenID		= -1;
}

CPlayWnd::~CPlayWnd()
{
}


BEGIN_MESSAGE_MAP(CPlayWnd, CWnd)
	//{{AFX_MSG_MAP(PlayWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPlayWnd message handlers

int CPlayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	hWndParent = lpCreateStruct->hwndParent;

	return 0;
}

BOOL CPlayWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rt;
	GetClientRect(&rt);
	CBrush br;
	br.CreateSolidBrush(RGB(0, 0, 0));
	pDC->FillRect(&rt,&br);
	CClientDC dc(this);
	
	return TRUE;
}

LRESULT CPlayWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_MOUSEMOVE:
		::PostMessage(hWndParent, WM_WND_MOUSEMOVE, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		::PostMessage(hWndParent, WM_WND_RBUTTONDOWN, m_nScreenID, lParam);
		break;
	case WM_LBUTTONDOWN:
		::PostMessage(hWndParent, WM_WND_LBUTTONDOWN, m_nScreenID, lParam);
		break;
	case WM_LBUTTONDBLCLK:
		::PostMessage(hWndParent, WM_WND_LBUTTONDBLCLK, m_nScreenID, 0);
		break;
	default:
		break;
	}
	return CWnd::DefWindowProc(message, wParam, lParam);
}

void CPlayWnd::HI_SetScreenID(int index)
{
	m_nScreenID = index;
}
