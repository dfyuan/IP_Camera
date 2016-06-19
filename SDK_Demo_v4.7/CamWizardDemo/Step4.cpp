// Step4.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWizard.h"
#include "Step4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep4 dialog


CStep4::CStep4(CWnd* pParent /*=NULL*/)
	: CDialog(CStep4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStep4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep4, CDialog)
	//{{AFX_MSG_MAP(CStep4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep4 message handlers

BOOL CStep4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    GetDlgItem(IDC_TEXT)->SetWindowText(_T("The guide have finished.\
        \r\n\r\nPress \"Finish\" button to exit the program, or press \"Back\" button to set another."));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
