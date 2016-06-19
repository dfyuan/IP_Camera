// Step1.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWizard.h"
#include "Step1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep1 dialog


CStep1::CStep1(CWnd* pParent /*=NULL*/)
	: CDialog(CStep1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep1)
	//}}AFX_DATA_INIT
}


void CStep1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep1)
	DDX_Control(pDX, IDC_COMBO1, m_ctrLangugeList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep1, CDialog)
	//{{AFX_MSG_MAP(CStep1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep1 message handlers

void CStep1::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


BOOL CStep1::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
    GetDlgItem(IDC_LANGUAGE)->SetWindowText(_T("Please select a language:"));
    GetDlgItem(IDC_TEXT)->SetWindowText(_T("This guide will lead you to set the Ipcamera device easily, and press \"Next\" button to continue."));
	
    m_ctrLangugeList.AddString(_T("English"));
	m_ctrLangugeList.EnableWindow(FALSE);
 //   m_ctrLangugeList.AddString(_T("ÖÐÎÄ"));

    m_ctrLangugeList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStep1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if (bShow == TRUE)
    {
        GetParent()->GetDlgItem(IDC_NEXT)->ShowWindow(TRUE);
    }    
}

BOOL CStep1::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_ESCAPE)
	{
		return FALSE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
