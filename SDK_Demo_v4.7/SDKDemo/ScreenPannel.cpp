// ScreenPannel.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenPannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenPannel

CScreenPannel::CScreenPannel()
{
	m_ShowMode		= 0;
	m_nCurScreen	= 0;
	m_ShowMode		= -1;

	m_bZoom			= FALSE;
	m_bFullScreen	= FALSE;

	InitializeCriticalSection( &m_cs );
}

CScreenPannel::~CScreenPannel()
{
	DeleteCriticalSection( &m_cs );
}


BEGIN_MESSAGE_MAP(CScreenPannel, CWnd)
	//{{AFX_MSG_MAP(CScreenPannel)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_WND_LBUTTONDOWN, OnSetCurScreen)
	ON_MESSAGE(WM_WND_RBUTTONDOWN, OnShowMenu)
	ON_MESSAGE(WM_WND_LBUTTONDBLCLK, OnSetZoom)
	ON_MESSAGE(WM_WND_MOUSEMOVE, OnMouseMoveEx)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScreenPannel message handlers

BOOL CScreenPannel::OnEraseBkgnd(CDC* pDC) 
{
	CRect rt;
	GetClientRect(&rt);
	CBrush br;
	br.CreateSolidBrush(RGB(192, 192, 192));
	pDC->FillRect(&rt,&br);

	DrawLine();
	DrawRect();
	
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

int CScreenPannel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPlayWndID = 1900;
	int i = 0;

	hWndParent = lpCreateStruct->hwndParent;
	for(i=0; i<MAXSCREEN; i++){
		m_PlayWnd[i].Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, nPlayWndID+i);
		m_PlayWnd[i].ShowWindow(SW_HIDE);
		m_PlayWnd[i].HI_SetScreenID(i);
	}
	
	return 0;
}

void CScreenPannel::HI_PANNEL_InitScreen(int mode)
{
	HI_PANNEL_ShowScreen(mode);
}

void CScreenPannel::ShowScreen(int showMode)
{
	int i, w, h;

	for(i=0; i<MAXSCREEN; i++){
		m_PlayWnd[i].ShowWindow(SW_HIDE);
	}

	if(showMode == 6){
		w=(m_nWidth-2)/3;
		h=(m_nHeight-2)/3;

		SetViewPos(0, 2, 2, w*2, h*2);
		SetViewPos(1, w*2+2, 2, w*3, h);
		SetViewPos(2, w*2+2, h+2, w*3, h*2);
		SetViewPos(3, 2, h*2+2, w, h*3);
		SetViewPos(4, w+2, h*2+2, w*2, h*3);
		SetViewPos(5, w*2+2, h*2+2, w*3, h*3);
	}else if(showMode == 8){
		w=(m_nWidth-2)/4;
		h=(m_nHeight-2)/4;

		SetViewPos(0, 2, 2, w*3, h*3);
		SetViewPos(1, w*3+2, 2, w*4, h);
		SetViewPos(2, w*3+2, h+2, w*4, h*2);
		SetViewPos(3, w*3+2, h*2+2, w*4, h*3);
		SetViewPos(4, 2, h*3+2, w, h*4);
		SetViewPos(5, w+2, h*3+2, w*2, h*4);
		SetViewPos(6, w*2+2, h*3+2, w*3, h*4);
		SetViewPos(7, w*3+2, h*3+2, w*4, h*4);
	}else{
		w=(m_nWidth-2)/showMode;
		h=(m_nHeight-2)/showMode;
		
		for(i=0; i<MAXSCREEN; i++){
			if(showMode==1 && i==m_nCurScreen){
				m_ScreenRect[i].left = 1;
				m_ScreenRect[i].top = 1;
				m_ScreenRect[i].right = m_nWidth-1;
				m_ScreenRect[i].bottom = m_nHeight-1;
				m_PlayWnd[i].MoveWindow(m_ScreenRect[i]);
				m_PlayWnd[i].ShowWindow(SW_SHOW);
			}else if(showMode!=1 && i<showMode*showMode){
				m_ScreenRect[i].left = w*(i%showMode)+2;
				m_ScreenRect[i].top = h*(i/showMode)+2;
				m_ScreenRect[i].right = w*(i%showMode+1);
				m_ScreenRect[i].bottom = h*(i/showMode+1);
				m_PlayWnd[i].MoveWindow(m_ScreenRect[i]);
				m_PlayWnd[i].ShowWindow(SW_SHOW);
			}	
		}
	}

	Invalidate();
}

void CScreenPannel::HI_PANNEL_ShowScreen(int showMode)
{
	if(m_ShowMode == showMode) return;

	ShowScreen(showMode);

	m_ShowMode = showMode;

	DrawLine();
	DrawRect();
}


LRESULT CScreenPannel::OnSetCurScreen(WPARAM wParam, LPARAM lParam)
{
	m_nCurScreen = (int)wParam;
	::PostMessage(hWndParent, WM_WND_LBUTTONDOWN, wParam, lParam);

	DrawLine();
	DrawRect();

	return 0;
}

LRESULT CScreenPannel::OnShowMenu(WPARAM wParam, LPARAM lParam)
{
	OnSetCurScreen(wParam, lParam);

	::PostMessage(hWndParent, WM_WND_RBUTTONDOWN, wParam, lParam);

	return 0;
}

LRESULT CScreenPannel::OnMouseMoveEx(WPARAM wParam, LPARAM lParam)
{
	::PostMessage(hWndParent, WM_WND_MOUSEMOVE, wParam, lParam);

	return 0;
}

LRESULT CScreenPannel::OnSetZoom(WPARAM wParam, LPARAM lParam)
{
	//::PostMessage(hWndParent, WM_WND_LBUTTONDBLCLK, wParam, lParam);
	OnSetCurScreen(wParam, lParam);

	if(m_bZoom){
		ShowScreen(m_ShowMode);
		m_bZoom = FALSE;
	}else{
		ShowScreen(1);
		m_bZoom = TRUE;
	}

	return 0;
}

int CScreenPannel::HI_PANNEL_GetCurScreen()
{
	return m_nCurScreen;
}

bool CScreenPannel::HI_PANNEL_GetFullScreen()
{
	return m_bFullScreen;
}

void CScreenPannel::HI_PANNEL_SetFullScreen()
{
	if(m_bFullScreen){
		m_nWidth = m_tWidth;
		m_nHeight = m_tHeight;
		_tempparent->ShowWindow(SW_SHOW);
		SetParent(_tempparent);
		ModifyStyle(WS_POPUP,WS_CHILD);//还原风格
		SetWindowPlacement(&_temppl);//还原位置
		m_bFullScreen = FALSE;
	}else{
		m_tWidth = m_nWidth;
		m_tHeight = m_nHeight;
		m_nWidth = GetSystemMetrics(SM_CXSCREEN);
		m_nHeight = GetSystemMetrics(SM_CYSCREEN);

		GetWindowPlacement(&_temppl);//保存位置信息
		ModifyStyle(WS_CHILD,WS_POPUP);//修改风格
		
		_tempparent=SetParent(NULL);//修改父窗口
		_tempparent->ShowWindow(SW_HIDE);

		MoveWindow(0, 0, m_nWidth, m_nHeight);//移动窗口
		m_bFullScreen = TRUE;
	}

	if(m_bZoom){
		ShowScreen(1);
	}else{
		ShowScreen(m_ShowMode);
	}
	
}

int CScreenPannel::HI_PANNEL_GetShowMode()
{
	return m_ShowMode;
}

void CScreenPannel::DrawLine()
{
	if(m_bZoom) return;

	int showMode;
	if(m_ShowMode == 6){
		showMode = 3;
	}else if(m_ShowMode == 8){
		showMode = 4;
	}else{
		showMode = m_ShowMode;
	}
	CPen *old, pen;
	CClientDC dc(this);
	CDC* pDC = CDC::FromHandle(dc.m_hDC);
	pen.CreatePen(PS_SOLID, 2, RGB(100, 128, 200));
	old=pDC->SelectObject(&pen);

	int i = 0;
	int w=(m_nWidth-2)/showMode;
	int h=(m_nHeight-2)/showMode;
	for(i=0; i<=m_nHeight; i++){//横条
		if(m_ShowMode == 6){
			if(i == 1){
				pDC->MoveTo(w*2, h*i+1);
			}else{
				pDC->MoveTo(0, h*i+1);
			}
		}else if(m_ShowMode == 8){
			if(i>0 && i<3){
				pDC->MoveTo(w*3, h*i+1);
			}else{
				pDC->MoveTo(0, h*i+1);
			}
		}else{
			pDC->MoveTo(0, h*i+1);
		}
		pDC->LineTo(w*showMode, h*i+1); 
	}

	for(i=0; i<=m_nWidth; i++){//竖条
		if(m_ShowMode == 6){
			if(i == 1){
				pDC->MoveTo(w*i+1, h*2);
			}else{
				pDC->MoveTo(w*i+1, 0);
			}
		}else if(m_ShowMode == 8){
			if(i>0 && i<3){
				pDC->MoveTo(w*i+1, h*3);
			}else{
				pDC->MoveTo(w*i+1, 0);
			}
		}else{
			pDC->MoveTo(w*i+1, 0);
		}
		pDC->LineTo(w*i+1, h*showMode); 
	}

	pDC->SelectObject(old);
	DeleteObject(&pen);
}

void CScreenPannel::DrawRect()
{
	CPen *old, pen;
	CClientDC dc(this);
	CDC* pDC = CDC::FromHandle(dc.m_hDC);
	pen.CreatePen(PS_SOLID, 1, RGB(255,0,255));	//小地图中的方格画笔0x0,0xf0,0xf0
	old=pDC->SelectObject(&pen);//调白色画笔
	
	int index = m_nCurScreen;
	pDC->MoveTo(m_ScreenRect[index].left-1, m_ScreenRect[index].top-1);		//左上点
	pDC->LineTo(m_ScreenRect[index].right, m_ScreenRect[index].top-1);	//右上点
	pDC->LineTo(m_ScreenRect[index].right, m_ScreenRect[index].bottom);//右下点
	pDC->LineTo(m_ScreenRect[index].left-1,m_ScreenRect[index].bottom);	//左下点
	pDC->LineTo(m_ScreenRect[index].left-1, m_ScreenRect[index].top-1);		//左上点
	
	pDC->SelectObject(old);
	DeleteObject(&pen);
}

void CScreenPannel::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	m_nWidth = cx;
	m_nHeight = cy;
	
	if(m_nWidth%2 == 1)
		m_nWidth = m_nWidth-1;
	
	if(m_nHeight%2 == 1)
		m_nHeight = m_nHeight-1;
	
	ShowScreen(m_ShowMode);
}

void CScreenPannel::SetViewPos(int index, int left, int top, int right, int bottom)
{
	m_ScreenRect[index].left = left;
	m_ScreenRect[index].top = top;
	m_ScreenRect[index].right = right;
	m_ScreenRect[index].bottom = bottom;
	m_PlayWnd[index].MoveWindow(m_ScreenRect[index]);
	m_PlayWnd[index].ShowWindow(SW_SHOW);
}

