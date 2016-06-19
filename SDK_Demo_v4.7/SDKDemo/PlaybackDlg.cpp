// PlaybackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "PlaybackDlg.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaybackDlg dialog
extern void CreateDirectoryEx(CString strDir);
extern CString	g_strPath;

CPlaybackDlg::CPlaybackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaybackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaybackDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlaybackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaybackDlg)
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_slideVolume);
	DDX_Control(pDX, IDC_COMBO_RATE, m_comboRate);
	DDX_Control(pDX, IDC_SLIDER_POS, m_sliderPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaybackDlg, CDialog)
	//{{AFX_MSG_MAP(CPlaybackDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_FRAME, OnBtnFrame)
	ON_BN_CLICKED(IDC_BTN_PHOTO, OnBtnPhoto)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE, OnSelchangeComboRate)
	ON_BN_CLICKED(IDC_BTN_SETMUTE, OnBtnSetmute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaybackDlg message handlers
BOOL CPlaybackDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lHandle = 0;

	m_sliderPos.SetRange(0, 100);
	m_comboRate.InsertString(0, "X-2");
	m_comboRate.InsertString(1, "X-1");
	m_comboRate.InsertString(2, ConvertString("Normal"));
	m_comboRate.InsertString(3, "X2");
	m_comboRate.InsertString(4, "X4");
	m_comboRate.InsertString(5, "X8");
	m_comboRate.InsertString(6, ConvertString("Fast Browse"));
	m_comboRate.SetCurSel(2);

	m_slideVolume.SetRange(0, 100);

	m_nRate = 2;
	m_nVolume = 100;

	TIMECAPS tcaps;
	const int TIMER_ACCURACY = 1;
    if(timeGetDevCaps(&tcaps, sizeof(TIMECAPS)) == TIMERR_NOERROR)     
    {
        m_wAccuracy = min(max(tcaps.wPeriodMin, TIMER_ACCURACY), tcaps.wPeriodMax);
        timeBeginPeriod(m_wAccuracy); 
    }

    m_TilerID_GetPos = 0;
	//InitializeCriticalSection(&m_critSection);

	m_PlayWnd.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 3000-1);
	m_PlayWnd.ShowWindow(SW_SHOW);
	
	CRect rc;
	GetDlgItem(IDC_VIEW)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_PlayWnd.MoveWindow(rc);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPlaybackDlg::OnOpen() 
{
	char strPath[256];
	GetCurrentDirectory(256, strPath);

	CString strExt =   "AVI Files (*.AVI;*.ASF;*.264)|*.avi;*.asf;*.264|All Files (*.*)|*.*||" ;  
    CString sFileName;
    CFileDialog *mFileDlg = new CFileDialog(TRUE, "", NULL, OFN_OVERWRITEPROMPT, strExt, NULL);    
    if(NULL == mFileDlg)
    {
		SetCurrentDirectory(strPath);
        return;
    }
    if ( IDOK != mFileDlg->DoModal() )
    {
        delete mFileDlg ;
		mFileDlg = NULL ;
		SetCurrentDirectory(strPath);
        return;
    }
    else
    { 
        sFileName = mFileDlg->GetPathName();
        delete mFileDlg ;
        mFileDlg = NULL ;
    }

	SetCurrentDirectory(strPath);

	HI_S32 s32Ret = HI_SUCCESS;

	if(0 != m_lHandle)
	{
		HI_SDK_StopPlayback(m_lHandle);
		m_lHandle = 0;
	}

	m_lHandle = HI_SDK_Playback(sFileName.GetBuffer(0), m_PlayWnd.GetSafeHwnd());
	if(m_lHandle != 0)
	{
		if(HI_SDK_GetAutoAdjust(m_lHandle) == 0)
			HI_SDK_SetAutoAdjust(m_lHandle);
		s32Ret = HI_SDK_SetEventCallBack(m_lHandle, (HI_U32)m_lHandle, OnEventCallBack, this);
		if(HI_SUCCESS != s32Ret)
		{
			HI_SDK_StopPlayback(m_lHandle);
			m_lHandle = 0;
			return;
		}

		s32Ret = HI_SDK_GetVolume(m_lHandle, AUDIO_OUT, &m_nVolume);;
	}

	m_sliderPos.SetPos(0);
	m_bPlayState = PB_STATE_BUTT;
}

void CPlaybackDlg::OnCancel() 
{
	(HI_VOID)timeEndPeriod(m_wAccuracy);
	if(0 != m_lHandle)
	{
		int ret = HI_SDK_StopPlayback(m_lHandle);
		if(ret == HI_SUCCESS)
		{
			m_lHandle = 0;
		}
	}
	//DeleteCriticalSection(&m_critSection);
	
	CDialog::OnCancel();
}

HRESULT CPlaybackDlg::OnEventCallBack(HI_U32 u32Chn,
									 EVENT_TYPE_E eEventType,
									 HI_VOID* pEventData, 
									 HI_S32 s32DataNum, 
									 HI_VOID* pUserData)
{
	CPlaybackDlg *pPlaybackDlg = (CPlaybackDlg*)pUserData;
	pPlaybackDlg->SetPlayState(eEventType);
	return 0;
}

void CPlaybackDlg::OpenSliderListener()
{
    if (0 != m_TilerID_GetPos)
    {
		timeKillEvent(m_TilerID_GetPos);
		m_TilerID_GetPos = 0 ;
    }
	
    m_TilerID_GetPos =  timeSetEvent(500, m_wAccuracy, (LPTIMECALLBACK)PlayFileThread, 
		(DWORD)this, TIME_PERIODIC);
}

void CPlaybackDlg::CloseSliderListener()
{
    if (0 != m_TilerID_GetPos)
    {
		timeKillEvent(m_TilerID_GetPos);
		m_TilerID_GetPos = 0 ;
    }
}

HRESULT CPlaybackDlg::UpdataPlayPos()
{
    HI_S32 s32Pos = 0;
	HI_S32 s32CurTime = 0;
	CString strTime = "";

	if(m_lHandle == 0)
	{
		return HI_FAILURE;
	}
    //if (HI_TRUE == m_bMouseMoving)
    //{
    //    return HI_SUCCESS;
    //}

    HI_S32 s32TotalTime = HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_GETTIME, 0, &s32CurTime);
	if(s32TotalTime <= 0)
		return HI_SUCCESS;

	s32Pos = s32CurTime*100/s32TotalTime;

	//EnterCriticalSection(&m_critSection);
    m_sliderPos.SetPos(s32Pos);
	//LeaveCriticalSection(&m_critSection);

	strTime.Format("%02d:%02d:%02d/%02d:%02d:%02d", s32CurTime/3600, s32CurTime%3600/60, s32CurTime%60,
													s32TotalTime/3600, s32TotalTime%3600/60, s32TotalTime%60);

	SetDlgItemText(IDC_SHOW_TIME, strTime);

    return HI_SUCCESS;
}

HI_VOID PASCAL CPlaybackDlg::PlayFileThread(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2)
{
    CPlaybackDlg* pdlg = (CPlaybackDlg*)dwUser;
    (HI_VOID)pdlg->UpdataPlayPos();
    return;
}

void CPlaybackDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_S32 s32Value = 0;
	int iVol = 0;
	int nValue = 0;
	switch(pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_POS:
		//EnterCriticalSection(&m_critSection);
		nValue = m_sliderPos.GetPos();
		//LeaveCriticalSection(&m_critSection);
		if(m_lHandle != 0)
		{
			HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_SETPOS, nValue, 0);
		}
		break;
	case IDC_SLIDER_VOLUME: 
		iVol = m_slideVolume.GetPos();
		s32Ret = HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_VOLUME, iVol, 0);
		if(HI_SUCCESS == s32Ret)
		{
			m_nVolume = iVol;
		}
		break;
	default:
		break;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

HI_VOID CPlaybackDlg::SetPlayState(EVENT_TYPE_E eEventType)
{
	switch(eEventType)
	{
	case EVENT_PLAYBACK_PLAY:
		OpenSliderListener();
		m_bPlayState = PB_STATE_PLAY;
		SetDlgItemText(IDC_BTN_PLAY, ConvertString("Pause"));
		break;
	case EVENT_PLAYBACK_STOP:
		CloseSliderListener();
		m_sliderPos.SetPos(0);
		Invalidate();
		m_bPlayState = PB_STATE_STOP;
		SetDlgItemText(IDC_BTN_PLAY, ConvertString("Play"));
		break;
	case EVENT_PLAYBACK_PAUSE:
		CloseSliderListener();
		m_bPlayState = PB_STATE_PAUSE;
		SetDlgItemText(IDC_BTN_PLAY, ConvertString("Play"));
		break;
	case EVENT_PLAYBACK_READ:
		break;
	default:
		break;
	}
}

void CPlaybackDlg::OnPlay() 
{
	if(0 == m_lHandle)
		return;
	
	printf("%d\n", m_bPlayState);
	if(m_bPlayState == PB_STATE_PLAY)
		HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_PAUSE, 0, 0);
	else
		HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_PLAY, 0, 0);

	m_slideVolume.SetPos(m_nVolume);
}


void CPlaybackDlg::OnBtnStop() 
{
	if(0 == m_lHandle)
		return;
	
	HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_STOP, 0, 0);
}

void CPlaybackDlg::OnBtnFrame() 
{
	if(0 == m_lHandle)
		return;
	
	HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_FRAME, 0, 0);
}

void CPlaybackDlg::OnBtnPhoto() 
{
	CString csFileName = CTime::GetCurrentTime().Format("SnapPt_%y_%m_%d_%H_%M_%S.jpg");
	char strPath[256] = {0};
	CString sPath = g_strPath + "\\config.ini";
	GetPrivateProfileString("CONFIG", "sFilePath", NULL, strPath, 64, sPath);

	if(strPath[0] == '\0')
	{
		sprintf(strPath, "D:\\Sdk_file\\");
	}
	else
	{
		if(strPath[strlen(strPath)] != '\\')
			strcat(strPath, "\\Sdk_file\\");
		else
			strcat(strPath, "Sdk_file\\");
	}
	
	if(!SetCurrentDirectory(strPath))
		CreateDirectoryEx(strPath);
	
	strcat(strPath, csFileName.GetBuffer(0));
	//HI_S32 s32Ret = HI_SDK_CapturePicture(m_lHandle, strPath);//bmp
	HI_S32 s32Ret = HI_SDK_CaptureJPEGPicture(m_lHandle, strPath);//jpg
}

void CPlaybackDlg::OnSelchangeComboRate() 
{
	int index = m_comboRate.GetCurSel();
	if(m_nRate == index)
	{
		return;
	}
	
	int speed;
	switch(index)
	{
	case 0:
		speed = -2;
		break;
	case 1:
		speed = -1;
		break;
	case 2:
		speed = 0;
		break;
	case 3:
		speed = 1;
		break;
	case 4:
		speed = 3;
		break;
	case 5:
		speed = 7;
		break;
	case 6:
		speed = 9;
		break;
	default:
		speed = 0;
		break;
	}
	
	int ret = HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_RATE, speed, 0);
	if(ret != 0)
	{
		m_comboRate.SetCurSel(m_nRate);
	}else{
		m_nRate = index;
	}
}

void CPlaybackDlg::OnBtnSetmute() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_lHandle)
		return;
	
	if(m_eMute == AUDIO_MUTE_ON)
	{
		s32Ret = HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_MUTE, AUDIO_MUTE_OFF, 0);
		if(HI_SUCCESS == s32Ret)
		{
			m_eMute = AUDIO_MUTE_OFF;
			SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Mute"));
		}else{
			MessageBox(ConvertString("Mute Failure!"));
		}
	}
	else
	{
		s32Ret = HI_SDK_PlayBackControl(m_lHandle, PB_CTRL_MUTE, AUDIO_MUTE_ON, 0);
		if(HI_SUCCESS == s32Ret)
		{
			m_eMute = AUDIO_MUTE_ON;
			SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Listen"));
		}else{
			MessageBox(ConvertString("Listen Failure!"));
		}
	}
}
