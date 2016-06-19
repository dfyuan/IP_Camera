// InputAlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdkdemo.h"
#include "InputAlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputAlarmDlg dialog


CInputAlarmDlg::CInputAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputAlarmDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CInputAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputAlarmDlg)
	DDX_Control(pDX, IDC_COMBO_EAM, m_combEAM);
	DDX_Control(pDX, IDC_COMBO_EA, m_combEA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CInputAlarmDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputAlarmDlg message handlers

BOOL CInputAlarmDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&sAttrExt, 0, sizeof(HI_S_ATTR_EXT));

	HI_S32 s32Ret = HI_FAILURE;
	CString strBuf = "";

	m_combEA.InsertString(0, ConvertString("Disable"));
	m_combEA.InsertString(1, ConvertString("Enable"));
	m_combEA.SetCurSel(0);
	
	m_combEAM.InsertString(0, ConvertString("Normally close"));
	m_combEAM.InsertString(1, ConvertString("Normally Open"));
	m_combEAM.SetCurSel(0);
	
	if(m_lHandle != 0)
	{
		s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_ATTR_EXT, &sAttrExt, sizeof(HI_S_ATTR_EXT));
		if(s32Ret == HI_SUCCESS)
		{
			m_combEA.SetCurSel(sAttrExt.u32Enable);
			m_combEAM.SetCurSel(sAttrExt.u32Flag);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputAlarmDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}

void CInputAlarmDlg::OnOK() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(m_lHandle == 0)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S_ATTR_EXT sAttrExt;
	sAttrExt.u32Enable = m_combEA.GetCurSel();
	sAttrExt.u32Flag = m_combEAM.GetCurSel();
	
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_ATTR_EXT, &sAttrExt, sizeof(HI_S_ATTR_EXT));
	if(HI_SUCCESS == s32Ret)
		MessageBox(ConvertString("Settings Success!"));
	else
		MessageBox(ConvertString("Setting Failure!"));
}
