// OsdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "OsdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COsdDlg dialog


COsdDlg::COsdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COsdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COsdDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void COsdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COsdDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COsdDlg, CDialog)
	//{{AFX_MSG_MAP(COsdDlg)
	ON_BN_CLICKED(IDC_BTN_SETOSD, OnBtnSetosd)
	ON_BN_CLICKED(IDC_CHECK_NAMEOSD, OnCheckNameosd)
	ON_BN_CLICKED(IDC_CHECK_TIMEOSD, OnCheckTimeosd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COsdDlg message handlers

BOOL COsdDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	memset(&m_sOsdInfo, 0, sizeof(HI_S_OSD));
	// TODO: Add extra initialization here
	HI_S32 s32Ret = HI_FAILURE;
	CString strBuf = "";

	if(m_lHandle != 0)
	{
		s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_OSD_PARAM, &m_sOsdInfo, sizeof(HI_S_OSD));
		if(s32Ret == HI_SUCCESS)
		{
			SetDlgItemText(IDC_EDIT_OSDNAME, m_sOsdInfo.sName);
			((CButton *)GetDlgItem(IDC_CHECK_NAMEOSD))->SetCheck(m_sOsdInfo.blEnName);
			((CButton *)GetDlgItem(IDC_CHECK_TIMEOSD))->SetCheck(m_sOsdInfo.blEnTime);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COsdDlg::OnBtnSetosd() 
{
	HI_S32 s32Ret = HI_FAILURE;

	HI_S_OSD sOSDInfo;
	memcpy(&sOSDInfo, &m_sOsdInfo, sizeof(HI_S_OSD));
	
	CString strOSDName = "";
	GetDlgItemText(IDC_EDIT_OSDNAME, strOSDName);
	strcpy(sOSDInfo.sName, strOSDName.GetBuffer(0));
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_OSD_PARAM, &sOSDInfo, sizeof(HI_S_OSD));
	if(HI_SUCCESS != s32Ret)
	{
		MessageBox(ConvertString("Setting OSD Failure!"));
		return;
	}

	memcpy(&m_sOsdInfo, &sOSDInfo, sizeof(HI_S_OSD));
}

void COsdDlg::OnCheckNameosd() 
{
	HI_S32 s32Ret = HI_FAILURE;

	HI_BOOL bEnable = HI_TRUE;
	if(0 == ((CButton *)GetDlgItem(IDC_CHECK_NAMEOSD))->GetCheck())
	{
		bEnable = HI_FALSE;
	}
	
	HI_S_OSD sOSDInfo;
	memcpy(&sOSDInfo, &m_sOsdInfo, sizeof(HI_S_OSD));
	sOSDInfo.blEnName = bEnable;
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_OSD_PARAM, &sOSDInfo, sizeof(HI_S_OSD));
	if(HI_SUCCESS != s32Ret)
	{
		MessageBox(ConvertString("Setting OSD Failure!"));
		return;
	}

	memcpy(&m_sOsdInfo, &sOSDInfo, sizeof(HI_S_OSD));
}

void COsdDlg::OnCheckTimeosd() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	HI_BOOL bEnable = HI_TRUE;
	if(0 == ((CButton *)GetDlgItem(IDC_CHECK_TIMEOSD))->GetCheck())
	{
		bEnable = HI_FALSE;
	}
	
	HI_S_OSD sOSDInfo;
	memcpy(&sOSDInfo, &m_sOsdInfo, sizeof(HI_S_OSD));
	sOSDInfo.blEnTime = bEnable;
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_OSD_PARAM, &sOSDInfo, sizeof(HI_S_OSD));
	if(HI_SUCCESS != s32Ret)
	{
		MessageBox(ConvertString("Setting OSD Failure!"));
		return;
	}
	
	memcpy(&m_sOsdInfo, &sOSDInfo, sizeof(HI_S_OSD));
}

void COsdDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}
