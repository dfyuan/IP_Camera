// OtherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdkdemo.h"
#include "OtherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherDlg dialog


COtherDlg::COtherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtherDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void COtherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherDlg)
	DDX_Control(pDX, IDC_COMBO_WHITEBALANCE, m_WhiteBalance);
	DDX_Control(pDX, IDC_COMBO_NIGHTVISION, m_combNightVision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherDlg, CDialog)
	//{{AFX_MSG_MAP(COtherDlg)
	ON_BN_CLICKED(IDC_BTN_REBOOT, OnBtnReboot)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_SETDISP, OnBtnSetdisp)
	ON_BN_CLICKED(IDC_BTN_NIGHT, OnBtnNight)
	ON_BN_CLICKED(IDC_CHECK_MIRROR, OnCheckMirror)
	ON_BN_CLICKED(IDC_CHECK_FLIP, OnCheckFlip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherDlg message handlers

BOOL COtherDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_DisplayExt, 0, sizeof(HI_S_Display_Ext));
	m_combNightVision.InsertString(0, ConvertString("Auto"));
	m_combNightVision.InsertString(1, ConvertString("ON"));
	m_combNightVision.InsertString(2, ConvertString("OFF"));
	m_combNightVision.SetCurSel(0);
	m_WhiteBalance.InsertString(0, ConvertString("Auto"));
	m_WhiteBalance.InsertString(1, ConvertString("Indoor"));
	m_WhiteBalance.InsertString(2, ConvertString("Outdoor"));
	m_WhiteBalance.SetCurSel(0);

	if(m_lHandle != 0)
	{
		HI_SDK_GetConfig(m_lHandle, HI_CMD_DISPLAY_EXT, &m_DisplayExt, sizeof(HI_S_Display_Ext));
		
		((CButton *)GetDlgItem(IDC_CHECK_FLIP))->SetCheck(m_DisplayExt.blFlip);
		((CButton *)GetDlgItem(IDC_CHECK_MIRROR))->SetCheck(m_DisplayExt.blMirror);

		int nScene = m_DisplayExt.s32Scene;
		if(nScene < HI_SCENE_AUTO || nScene > HI_SCENE_OUTDOOR)
			nScene = 0;
		m_WhiteBalance.SetCurSel(nScene);
		
		//infrared
		HI_S_Infrared sInfrared;
		HI_SDK_GetConfig(m_lHandle, HI_CMD_INFRARED, &sInfrared, sizeof(HI_S_Infrared));
		int nInfrared = 0;
		switch(sInfrared.s32Infrared)
		{
		case HI_INFRARED_AUTO:
			break;
		case HI_INFRARED_ON:
			nInfrared = 1;
			break;
		case HI_INFRARED_OFF:
			nInfrared = 2;
			break;
		default:
			break;
		}

		m_combNightVision.SetCurSel(nInfrared);

		HI_S32 s32Enable = m_sSupport.u32Operation;

		if(!(s32Enable & SUPPORTATTR_WHITEBALANCE_FLAG))
		{
			m_WhiteBalance.EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SETDISP)->EnableWindow(FALSE);
		}
		else
		{
			m_WhiteBalance.EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SETDISP)->EnableWindow(TRUE);
		}
		
		if(!(s32Enable & SUPPORTATTR_NIGHTVISION_SET_FLAG))
		{
			m_combNightVision.EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_NIGHT)->EnableWindow(FALSE);
		}
		else
		{
			m_combNightVision.EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NIGHT)->EnableWindow(TRUE);
		}

		if(!(s32Enable & SUPPORTATTR_FLIP_FLAG))
			GetDlgItem(IDC_CHECK_FLIP)->EnableWindow(FALSE);
		else
			GetDlgItem(IDC_CHECK_FLIP)->EnableWindow(TRUE);
		
		if(!(s32Enable & SUPPORTATTR_MIRROR_FLAG))
			GetDlgItem(IDC_CHECK_MIRROR)->EnableWindow(FALSE);
		else
			GetDlgItem(IDC_CHECK_MIRROR)->EnableWindow(TRUE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COtherDlg::SetHandle(long lHandle, HI_S_SUPPORT *pSupport)
{
	m_lHandle = lHandle;
	memcpy(&m_sSupport, pSupport, sizeof(HI_S_SUPPORT));
}

void COtherDlg::OnBtnReboot() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_REBOOT, NULL, 0);
}

void COtherDlg::OnBtnReset() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_RESET, NULL, 0);
}

void COtherDlg::OnBtnSetdisp() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S32 s32Scene[3] = {HI_SCENE_AUTO, HI_SCENE_INDOOR, HI_SCENE_OUTDOOR};
	
	int nValue = 0;
	nValue = m_WhiteBalance.GetCurSel();
	m_DisplayExt.s32Scene = s32Scene[nValue];
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_DISPLAY_EXT, &m_DisplayExt, sizeof(HI_S_Display_Ext));
	if(HI_SUCCESS != s32Ret)
		MessageBox(ConvertString("Setting Failure!"));
	else
		MessageBox(ConvertString("Settings Success!"));
}

void COtherDlg::OnBtnNight() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	int nValue = 0;
	HI_S32 s32Infrared[3] = {HI_INFRARED_AUTO, HI_INFRARED_ON, HI_INFRARED_OFF};
	nValue = m_combNightVision.GetCurSel();
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_INFRARED, &s32Infrared[nValue], sizeof(HI_S_Infrared));
	if(HI_SUCCESS != s32Ret)
		MessageBox(ConvertString("Setting Failure!"));
	else
		MessageBox(ConvertString("Settings Success!"));
}

void COtherDlg::OnCheckMirror() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_BOOL bEnable = HI_TRUE;
	
	if(0 == ((CButton *)GetDlgItem(IDC_CHECK_MIRROR))->GetCheck())
	{
		bEnable = HI_FALSE;
	}
	
	m_DisplayExt.blMirror = bEnable;
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_DISPLAY_EXT, &m_DisplayExt, sizeof(HI_S_Display_Ext));
	if(HI_SUCCESS != s32Ret)
		MessageBox(ConvertString("Setting Failure!"));
}

void COtherDlg::OnCheckFlip() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_BOOL bEnable = HI_TRUE;
	
	if(0 == ((CButton *)GetDlgItem(IDC_CHECK_FLIP))->GetCheck())
	{
		bEnable = HI_FALSE;
	}
	
	m_DisplayExt.blFlip = bEnable;
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_DISPLAY_EXT, &m_DisplayExt, sizeof(HI_S_Display_Ext));
	if(HI_SUCCESS != s32Ret)
		MessageBox(ConvertString("Setting Failure!"));
}
