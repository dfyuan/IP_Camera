// AudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdkdemo.h"
#include "AudioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg dialog


CAudioDlg::CAudioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudioDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioDlg)
	DDX_Control(pDX, IDC_COMBO_STREAM, m_combStream);
	DDX_Control(pDX, IDC_COMBO_AUSWITCH, m_combAuSwitch);
	DDX_Control(pDX, IDC_COMBO_AUFORMAT, m_combFormat);
	DDX_Control(pDX, IDC_COMBO_AUINPUT, m_combInput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudioDlg, CDialog)
	//{{AFX_MSG_MAP(CAudioDlg)
	ON_BN_CLICKED(IDC_BTN_SETAUDIO, OnBtnSetaudio)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM, OnSelchangeComboStream)
	ON_BN_CLICKED(IDC_BTN_SETINPUT, OnBtnSetinput)
	ON_BN_CLICKED(IDC_BTN_SETOUTPUT, OnBtnSetoutput)
	ON_BN_CLICKED(IDC_BTN_SETINPUTMODE, OnBtnSetinputmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg message handlers

BOOL CAudioDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_sAudioInfo, 0, sizeof(m_sAudioInfo));
	HI_S32 i = 0;
	CString strBuf = "";

	m_combStream.InsertString(0, ConvertString("First Stream"));
	m_combStream.InsertString(1, ConvertString("Second Stream"));
	m_combStream.InsertString(2, ConvertString("Third Stream"));
	m_combStream.SetCurSel(0);

	m_combFormat.InsertString(0, "G711");
	m_combFormat.InsertString(1, "G726");
	//m_combFormat.InsertString(2, "AMR");
	m_combFormat.SetCurSel(0);
	
	m_combAuSwitch.InsertString(0, ConvertString("OFF"));
	m_combAuSwitch.InsertString(1, ConvertString("ON"));
	m_combAuSwitch.SetCurSel(0);

	
	m_combInput.InsertString(0, ConvertString("Line in"));
	m_combInput.InsertString(1, ConvertString("MIC"));
	m_combInput.SetCurSel(0);
	HI_S32 s32Stream = 3;
	if(m_lHandle != 0)
	{
		for(i=0; i<s32Stream; i++)
		{
			m_sAudioInfo[i].u32Channel = HI_CHANNEL_1;
			m_sAudioInfo[i].u32Stream = HI_STREAM_1 + i;
			HI_SDK_GetConfig(m_lHandle, HI_CMD_AUDIO_PARAM_EXT, &m_sAudioInfo[i], sizeof(HI_S_Audio_Ext));
		}

		HI_S_AudioVolume u32AInput;
		HI_SDK_GetConfig(m_lHandle, HI_CMD_AUDIO_VOLUME_IN, &u32AInput, sizeof(HI_S_AudioVolume));

		HI_S_AudioVolume u32AOutput;
		HI_SDK_GetConfig(m_lHandle, HI_CMD_AUDIO_VOLUME_OUT, &u32AOutput, sizeof(HI_S_AudioVolume));
		
		HI_S32 audioInput = AUDIO_INPUT_MIC;
		HI_SDK_GetConfig(m_lHandle, HI_CMD_AUDIO_INPUT, &audioInput, sizeof(HI_S32));

		
		int nAuType = 0;
		m_combAuSwitch.SetCurSel(m_sAudioInfo[0].blEnable);
		switch(m_sAudioInfo[0].u32Type)
		{
		case HI_AUDIO_TYPE_G711:
			break;
		case HI_AUDIO_TYPE_G726:
			nAuType = 1;
			break;
		//case HI_AUDIO_TYPE_AMR:
		//	nAuType = 2;
		//	break;
		default:
			break;
		}
		m_combFormat.SetCurSel(nAuType);
		
		int nInput = 0;
		switch(audioInput)
		{
		case AUDIO_INPUT_MIC:
			nInput = 1;
			break;
		case AUDIO_INPUT_LINE:	
			break;
		default:
			break;
		}
		m_combInput.SetCurSel(nInput);

		strBuf.Format("%d", u32AInput.u32AudioVolume);
		SetDlgItemText(IDC_EDIT_AUINPUT, strBuf);

		strBuf.Format("%d", u32AOutput.u32AudioVolume);
		SetDlgItemText(IDC_EDIT_AUOUTPUT, strBuf);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAudioDlg::SetHandle(long lHandle, HI_CHAR *psProduct)
{
	if(psProduct == NULL)
		return;

	m_lHandle = lHandle;
	strcpy(m_sProduct, psProduct);
}

void CAudioDlg::OnBtnSetaudio() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	int nStream = m_combStream.GetCurSel();
	
	HI_U32 u32Format[3] = {HI_AUDIO_TYPE_G711, HI_AUDIO_TYPE_G726, HI_AUDIO_TYPE_AMR};
	
	int nValue = 0;
	HI_S_Audio_Ext sAudio;
	memcpy(&sAudio, &m_sAudioInfo[nStream], sizeof(HI_S_Audio_Ext));
	
	nValue = m_combFormat.GetCurSel();
	sAudio.u32Type = u32Format[nValue];
	HI_BOOL bEnable = HI_FALSE;
	if(1 == m_combAuSwitch.GetCurSel())
		bEnable = HI_TRUE;
	sAudio.blEnable = bEnable;
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_AUDIO_PARAM_EXT, &sAudio, sizeof(HI_S_Audio_Ext));
	if(HI_SUCCESS == s32Ret)
	{
		memcpy(&m_sAudioInfo[nStream], &sAudio, sizeof(HI_S_Audio_Ext));
		MessageBox(ConvertString("Settings Success,Must reboot before enable it!"));
	}else{
		MessageBox(ConvertString("Setting Failure!"));
	}
}

void CAudioDlg::OnSelchangeComboStream() 
{
	if(m_lHandle != 0)
	{
		int index = m_combStream.GetCurSel();
		int nAuType = 0;

		m_combFormat.ResetContent();
		m_combFormat.InsertString(0, "G711");
		m_combFormat.InsertString(1, "G726");
		//if(index != 0)
		//	m_combFormat.InsertString(2, "AMR");

		m_combAuSwitch.SetCurSel(m_sAudioInfo[index].blEnable);
		switch(m_sAudioInfo[index].u32Type)
		{
		case HI_AUDIO_TYPE_G711:
			break;
		case HI_AUDIO_TYPE_G726:
			nAuType = 1;
			break;
		//case HI_AUDIO_TYPE_AMR:
		//	nAuType = 2;
		//	break;
		default:
			break;
		}

		m_combFormat.SetCurSel(nAuType);
	}
}

void CAudioDlg::OnBtnSetinput() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	HI_S_AudioVolume sAuInput;
	CString strBuf = "";
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	GetDlgItemText(IDC_EDIT_AUINPUT, strBuf);
	sAuInput.u32AudioVolume = atoi(strBuf);
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_AUDIO_VOLUME_IN, &sAuInput, sizeof(HI_S_AudioVolume));
	if(HI_SUCCESS == s32Ret)
		MessageBox(ConvertString("Settings Success!"));
	else
		MessageBox(ConvertString("Setting Failure!"));
}

void CAudioDlg::OnBtnSetoutput() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	HI_S_AudioVolume sAuOutput;
	CString strBuf = "";
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	GetDlgItemText(IDC_EDIT_AUOUTPUT, strBuf);
	sAuOutput.u32AudioVolume = atoi(strBuf);
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_AUDIO_VOLUME_OUT, &sAuOutput, sizeof(HI_S_AudioVolume));
	if(HI_SUCCESS == s32Ret)
		MessageBox(ConvertString("Settings Success!"));
	else
		MessageBox(ConvertString("Setting Failure!"));
}

void CAudioDlg::OnBtnSetinputmode() 
{
	HI_S32 s32Ret = HI_FAILURE; 
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	HI_U32 u32Input[2] = {AUDIO_INPUT_MIC, AUDIO_INPUT_LINE};
	int nInput = m_combInput.GetCurSel();
	s32Ret = HI_SDK_SetConfig(m_lHandle,HI_CMD_AUDIO_INPUT,&nInput,sizeof(HI_U32));
	if(HI_SUCCESS != s32Ret)
		MessageBox(ConvertString("Setting Audio Input Failure!"));
	else
		MessageBox(ConvertString("Settings Success!"));
}
