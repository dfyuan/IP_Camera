// CheckUser.cpp : implementation file
//

#include "stdafx.h"
#include "customwizard.h"
#include "CheckUser.h"
#include "Wizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckUser dialog


CCheckUser::CCheckUser(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckUser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCheckUser::~CCheckUser()
{
}


void CCheckUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckUser)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckUser, CDialog)
	//{{AFX_MSG_MAP(CCheckUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckUser message handlers

void CCheckUser::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(TRUE);

    GetDlgItem(IDC_NAME)->GetWindowText(m_strName);
    GetDlgItem(IDC_PWD)->GetWindowText(m_strPwd);

    if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1)
    {
        m_iSelect = 1;
    }
    else
    {
        m_iSelect = 0;
    }

    m_strName.TrimLeft();
    m_strName.TrimRight();
    if (m_strName == "")
    {
        AfxMessageBox(_T("Please input account"));
        return;
    }
	CWizard *p = (CWizard*)(AfxGetApp()->GetMainWnd());
	p->m_strUsername = m_strName;
	p->m_strUserpwd = m_strPwd;
	p->m_iIfMem = m_iSelect;
	
    CDialog::OnOK();
}


BOOL CCheckUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ((CEdit*)GetDlgItem(IDC_NAME))->SetLimitText(31);
    ((CEdit*)GetDlgItem(IDC_PWD))->SetLimitText(31);

    if (m_iSelect == 1)
    {
        GetDlgItem(IDC_NAME)->SetWindowText(m_strName);
        GetDlgItem(IDC_PWD)->SetWindowText(m_strPwd);
        ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
    }
	
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckUser::GetAccount(CString name, CString pwd, int rem)
{
    m_strName = name;
    m_strPwd = pwd;

    m_iSelect = rem;
}

void CCheckUser::GetMainFrame(HANDLE wnd)
{

}
