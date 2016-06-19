// VideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdkdemo.h"
#include "VideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoDlg dialog


CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoDlg)
	DDX_Control(pDX, IDC_COMBO_STREAM, m_combStream);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_combResolution);
	DDX_Control(pDX, IDC_COMBO_FREQUENCY, m_combFrequency);
	DDX_Control(pDX, IDC_COMBO_LCBR, m_combLcbr);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_combFrameRate);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_combQuality);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoDlg)
	ON_BN_CLICKED(IDC_BTN_SETSIZE, OnBtnSetsize)
	ON_BN_CLICKED(IDC_BTN_SETFQ, OnBtnSetfq)
	ON_BN_CLICKED(IDC_BTN_SETVIDEO, OnBtnSetvideo)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM, OnSelchangeComboStream)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoDlg message handlers

BOOL CVideoDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_sVideo, 0, sizeof(m_sVideo));
	int i;
	CString strBuf;
	//m_nMaxFrame = 30;
	for(i=0; i<30; i++)
	{
		strBuf.Format("%d", i+1);
		if(i < 6)
		{
			m_combQuality.InsertString(i, strBuf);
		}
		
		m_combFrameRate.InsertString(i, strBuf);
	}

	m_combLcbr.InsertString(0, ConvertString("VBR"));//"¿É±äÂëÂÊ"
	m_combLcbr.InsertString(1, ConvertString("CBR"));
	m_combLcbr.SetCurSel(0);

	m_combFrequency.InsertString(0, "50");
	m_combFrequency.InsertString(1, "60");
	m_combFrequency.SetCurSel(0);

	m_combStream.InsertString(0, ConvertString("First Stream"));
	m_combStream.InsertString(1, ConvertString("Second Stream"));
	m_combStream.InsertString(2, ConvertString("Third Stream"));
	m_combStream.SetCurSel(0);

	HI_S32 s32Stream = 3;
	if(m_lHandle != 0)
	{
		HI_S32 s32Enable = m_sSupport.u32Operation;
		if(!(s32Enable & SUPPORTATTR_POWERFREQ_FLAG))
		{
			m_combFrequency.EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SETFQ)->EnableWindow(FALSE);
		}
		else
		{
			m_combFrequency.EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SETFQ)->EnableWindow(TRUE);
		}

		int i = 0;
		CString strBuf;
		if(m_nMaxFrame != (HI_S32)m_sSupport.u32FrameMax)
		{
			m_nMaxFrame = m_sSupport.u32FrameMax;
			m_combFrameRate.ResetContent();
			for(i=0; i<m_nMaxFrame; i++)
			{
				strBuf.Format("%d", i+1);
				m_combFrameRate.InsertString(i, strBuf);
			}
		}

		CString strReslution[15] = {"VGA", "QVGA", "QQVGA", "D1", "CIF", "QCIF", "720P", "Q720", "QQ720", "UXQA", "960H", "Q960H", "QQ960H", "1080P", "960P"};
		int index = 0;
		
		s32Enable = m_sSupport.u32Reslution;
		m_combResolution.ResetContent();
		int nItem = 0;
		if(strstr(m_sProduct, "Sc") != NULL || strstr(m_sProduct, "Sf") != NULL)
		{
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_960P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_960P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_VGA]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_VGA);
			}
			else if(index == 1)
			{
				if(m_sResolutio[0].u32Resolution == HI_RESOLUTION_960P||m_sResolutio[0].u32Resolution == HI_RESOLUTION_VGA)
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_VGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_VGA);
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QVGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QVGA);
					
				}
				else
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
				}
			}
			else
			{
				if(m_sResolutio[0].u32Resolution == HI_RESOLUTION_960P||m_sResolutio[0].u32Resolution == HI_RESOLUTION_VGA)
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QVGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QVGA);
				}
				else
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
				}
			}
		}
		/************************************************************************/
		/* 1080P-720P IMX122-Sg,OV2715-Si,MN34041-Sj                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Sg") != NULL||strstr(m_sProduct, "Si") != NULL||strstr(m_sProduct, "Sj") != NULL)
		{
			
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_1080P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_1080P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
			}
			else if(index == 1)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}	
		}
		/************************************************************************/
		/* 720P OV8712-Se,OV10633-Sh				                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Se") != NULL||strstr(m_sProduct, "Sh") != NULL)
		{
			
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
			}
			else if(index == 1)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}	
		}
		/************************************************************************/
		/* TVP5150 |Sk| -D1/CIF						                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Sk") != NULL)
		{
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_D1]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_D1);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
			else if(index == 1)
			{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
		}
		else
		{
		for(i=0; i<15; i++)
		{
			if(s32Enable & (0x00000001<<i))
			{
				index = m_combResolution.AddString(strReslution[i]);
				m_combResolution.SetItemData(index, i);
			}
		}
		}
		for(i=0; i<s32Stream; i++)
		{
			m_sVideo[i].u32Channel = HI_CHANNEL_1;
			m_sVideo[i].u32Stream = HI_STREAM_1 + i;
			m_sResolutio[i].u32Channel = HI_CHANNEL_1;
			m_sResolutio[i].u32Stream = HI_STREAM_1 + i;
			HI_SDK_GetConfig(m_lHandle, HI_CMD_VIDEO_PARAM_EXT, &m_sVideo[i], sizeof(HI_S_Video_Ext));
			HI_SDK_GetConfig(m_lHandle, HI_CMD_RESOLUTION_EXT, &m_sResolutio[i], sizeof(HI_S_Resolution_Ext));
		}

		HI_SDK_GetConfig(m_lHandle, HI_CMD_FREQUENCY, &m_u32Frequency, sizeof(HI_U32));
		
		strBuf.Format("%d", m_sVideo[0].u32Bitrate);
		SetDlgItemText(IDC_EDIT_BITRATE, strBuf);
		
		HI_U32 u32Frame = m_sVideo[0].u32Frame;
		if(u32Frame <= 0) u32Frame = 1;
		//else if(u32Frame > 0) u32Frame = 1;
		m_combFrameRate.SetCurSel(u32Frame-1);
		
		strBuf.Format("%d", m_sVideo[0].u32Iframe);
		SetDlgItemText(IDC_EDIT_IFRAME, strBuf);
		
		m_combLcbr.SetCurSel(m_sVideo[0].blCbr);
		
		HI_U32 u32Quality = m_sVideo[0].u32ImgQuality;
		if(u32Quality <= 0) u32Quality = 1;
		m_combQuality.SetCurSel(u32Quality-1);
		
		int nFrequency = 0;
		switch(m_u32Frequency)
		{
		case FREQ_50HZ_PAL:
			break;
		case FREQ_60HZ_NTSC:
			nFrequency = 1;
			break;
		default:
			break;
		}
		m_combFrequency.SetCurSel(nFrequency);

		int iCnt = m_combResolution.GetCount();
		for(i = 0; i < iCnt; i++)
		{
			if(m_sResolutio[0].u32Resolution == m_combResolution.GetItemData(i))
			{
				m_combResolution.SetCurSel(i);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoDlg::SetHandle(long lHandle, HI_CHAR *psProduct, HI_S_SUPPORT *pSupport)
{
	m_lHandle = lHandle;
	strcpy(m_sProduct, psProduct);
	memcpy(&m_sSupport, pSupport, sizeof(HI_S_SUPPORT));
}

void CVideoDlg::OnBtnSetsize() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	int videoType = m_combStream.GetCurSel();
	//HI_U32 u32Resolution[7]	= {	HI_RESOLUTION_VGA, HI_RESOLUTION_QVGA, HI_RESOLUTION_QQVGA,
	//							HI_RESOLUTION_D1, HI_RESOLUTION_CIF, HI_RESOLUTION_QCIF,
	//							HI_RESOLUTION_720P};
	
	HI_S_Resolution sResolution;
	if(videoType == 0)
		sResolution.blFlag = HI_TRUE;
	else if(videoType == 1&&strstr(m_sProduct, "Sk") == NULL)
		sResolution.blFlag = HI_FALSE;
	else
		return;
	sResolution.u32Channel = m_sResolutio[videoType].u32Channel;
	sResolution.u32Resolution = m_combResolution.GetItemData(m_combResolution.GetCurSel());
	//sResolution.u32Resolution = u32Resolution[nValue];
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_RESOLUTION, &sResolution, sizeof(HI_S_Resolution));
	if(HI_SUCCESS == s32Ret)
	{
		{
			if((m_sResolutio[videoType].u32Resolution != HI_RESOLUTION_UXGA && sResolution.u32Resolution == HI_RESOLUTION_UXGA))
			{
				MessageBox(ConvertString("Will automatically restart the IP camera!"));
			}
		}
		
		memcpy(&m_sResolutio[videoType], &sResolution, sizeof(HI_S_Resolution));
		MessageBox(ConvertString("Settings Success!"));
	}else{
		MessageBox(ConvertString("Setting Failure!"));
		return;
	}
}

void CVideoDlg::OnBtnSetfq() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	HI_S32 i = 0;
	CString strBuf = "";
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_U32 u32Frequency[2]	= {FREQ_50HZ_PAL, FREQ_60HZ_NTSC};
	
	int nValue = 0;
	int nCurStream = m_combStream.GetCurSel();
	nValue = m_combFrequency.GetCurSel();
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_FREQUENCY, &u32Frequency[nValue], sizeof(HI_U32));
	if(HI_SUCCESS == s32Ret)
	{
		m_u32Frequency = u32Frequency[nValue];

		HI_S32 s32Stream = 3;
		for(i=0; i<s32Stream; i++)
		{
			m_sVideo[i].u32Channel = HI_CHANNEL_1;
			m_sVideo[i].u32Stream = HI_STREAM_1 + i;
			HI_SDK_GetConfig(m_lHandle, HI_CMD_VIDEO_PARAM_EXT, &m_sVideo[i], sizeof(HI_S_Video_Ext));
		}

		HI_SDK_GetSupportAttr(m_lHandle, &m_sSupport);
		m_nMaxFrame = m_sSupport.u32FrameMax;
		m_combFrameRate.ResetContent();
		for(i=0; i<m_nMaxFrame; i++)
		{
			strBuf.Format("%d", i+1);
			m_combFrameRate.InsertString(i, strBuf);
		}
		m_combFrameRate.SetCurSel(m_sVideo[nCurStream].u32Frame-1);
		MessageBox(ConvertString("Settings Success!"));
	}else{
		MessageBox(ConvertString("Setting Failure!"));
		return;
	}
}

void CVideoDlg::OnBtnSetvideo() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	int nStream = m_combStream.GetCurSel();
	
	CString strBuf;
	int nValue = 0;
	HI_S_Video_Ext sVideo;
	memcpy(&sVideo, &m_sVideo[nStream], sizeof(HI_S_Video_Ext));
	
	GetDlgItemText(IDC_EDIT_BITRATE, strBuf);
	nValue = atoi(strBuf);
	sVideo.u32Bitrate = nValue;
	
	GetDlgItemText(IDC_EDIT_IFRAME, strBuf);
	nValue = atoi(strBuf);
	sVideo.u32Iframe = nValue;
	
	sVideo.u32Frame = m_combFrameRate.GetCurSel()+1;
	sVideo.u32ImgQuality = m_combQuality.GetCurSel()+1;
	
	HI_BOOL bLcbr = HI_FALSE;
	if(1 == m_combLcbr.GetCurSel())
		bLcbr = HI_TRUE;
	sVideo.blCbr = bLcbr;
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_VIDEO_PARAM_EXT, &sVideo, sizeof(HI_S_Video_Ext));
	if(HI_SUCCESS == s32Ret)
	{
		memcpy(&m_sVideo[nStream], &sVideo, sizeof(HI_S_Video_Ext));
		MessageBox(ConvertString("Settings Success!"));
	}else{
		MessageBox(ConvertString("Setting Failure!"));
	}
}

void CVideoDlg::OnSelchangeComboStream() 
{
	if(m_lHandle != 0)
	{
		int i = 0;
		CString strBuf = "";
		HI_S32 s32Enable = 0;
		int index = m_combStream.GetCurSel();

		CString strReslution[15] = {"VGA", "QVGA", "QQVGA", "D1", "CIF", "QCIF", "720P", "Q720", "QQ720", "UXQA", "960H", "Q960H", "QQ960H", "1080P", "960P"};
		int nItem = 0;
		
		if(index == 0)
			s32Enable = m_sSupport.u32Reslution;
		else if(index == 1)
			s32Enable = m_sSupport.u32Reslution1;
		else
			s32Enable |= (0x00000001<<HI_RESOLUTION_QQ720);

		m_combResolution.ResetContent();

		if(strstr(m_sProduct, "Sc") != NULL || strstr(m_sProduct, "Sf") != NULL)
		{
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_960P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_960P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_VGA]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_VGA);
			}
			else if(index == 1)
			{
				if(m_sResolutio[0].u32Resolution == HI_RESOLUTION_960P||m_sResolutio[0].u32Resolution == HI_RESOLUTION_VGA)
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_VGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_VGA);
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QVGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QVGA);

				}
				else
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
				}
			}
			else
			{
				if(m_sResolutio[0].u32Resolution == HI_RESOLUTION_960P||m_sResolutio[0].u32Resolution == HI_RESOLUTION_VGA)
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QVGA]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QVGA);
				}
				else
				{
					nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
					m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
				}
			}
		}
		/************************************************************************/
		/* 1080P-720P IMX122-Sg,OV2715-Si,MN34041-Sj                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Sg") != NULL||strstr(m_sProduct, "Si") != NULL||strstr(m_sProduct, "Sj") != NULL)
		{
			
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_1080P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_1080P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
			}
			else if(index == 1)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}	
		}
		/************************************************************************/
		/* 720P OV8712-Se,OV10633-Sh				                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Se") != NULL||strstr(m_sProduct, "Sh") != NULL)
		{
			
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_720P]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_720P);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
			}
			else if(index == 1)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_Q720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_Q720);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_QQ720]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_QQ720);
			}	
		}
		/************************************************************************/
		/* TVP5150 |Sk| -D1/CIF						                            */
		/************************************************************************/
		else if(strstr(m_sProduct, "Sk") != NULL)
		{
			if(index == 0)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_D1]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_D1);
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
			else if(index == 1)
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
			else
			{
				nItem = m_combResolution.AddString(strReslution[HI_RESOLUTION_CIF]);
				m_combResolution.SetItemData(nItem, HI_RESOLUTION_CIF);
			}
		}
		else
		{
			for(i=0; i<15; i++)
			{
				if(s32Enable & (0x00000001<<i))
				{
					nItem = m_combResolution.AddString(strReslution[i]);
					m_combResolution.SetItemData(nItem, i);
				}
			}
		}

		strBuf.Format("%d", m_sVideo[index].u32Bitrate);
		SetDlgItemText(IDC_EDIT_BITRATE, strBuf);
		
		HI_U32 u32Frame = m_sVideo[index].u32Frame;
		if(u32Frame <= 0) u32Frame = 1;
		//else if(u32Frame > 0) u32Frame = 1;
		m_combFrameRate.SetCurSel(u32Frame-1);
		
		strBuf.Format("%d", m_sVideo[index].u32Iframe);
		SetDlgItemText(IDC_EDIT_IFRAME, strBuf);
		
		m_combLcbr.SetCurSel(m_sVideo[index].blCbr);
		
		HI_U32 u32Quality = m_sVideo[index].u32ImgQuality;
		if(u32Quality <= 0) u32Quality = 1;
		m_combQuality.SetCurSel(u32Quality-1);

		int nFrequency = 0;
		switch(m_u32Frequency)
		{
		case FREQ_50HZ_PAL:
			break;
		case FREQ_60HZ_NTSC:
			nFrequency = 1;
			break;
		default:
			break;
		}
		m_combFrequency.SetCurSel(nFrequency);
		
		int iCnt = m_combResolution.GetCount();
		for(i = 0; i < iCnt; i++)
		{
			if(m_sResolutio[index].u32Resolution == m_combResolution.GetItemData(i))
			{
				m_combResolution.SetCurSel(i);
			}
		}
	}
}
