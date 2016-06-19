// SDKDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "SDKDemoDlg.h"
#include "PlaybackDlg.h"
#include "TimeDlg.h"
#include "OsdDlg.h"
#include "NetDlg.h"
#include "WifiDlg.h"
#include "InputAlarmDlg.h"
#include "OtherDlg.h"
#include "PtzDlg.h"
#include "AudioDlg.h"
#include "VideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void CreateDirectoryEx(CString strDir);
extern CString	g_strPath;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		//::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)"C:\\Program Files");   //传递默认打开路径 （方法一）
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);        //传递默认打开路径 （方法二，前提是lpData提前设置好）
		break;
	case BFFM_SELCHANGED:
		char curr[MAX_PATH];   
		SHGetPathFromIDList((LPCITEMIDLIST)lParam,curr);   
		::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)curr);
		break;
	default:
		break;
	} 
	
	return 0;   
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDKDemoDlg dialog

CSDKDemoDlg::CSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSDKDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSDKDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSDKDemoDlg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_combChannel);
	DDX_Control(pDX, IDC_COMBO_RECTYPE, m_combRecType);
	DDX_Control(pDX, IDC_COMBO_PTZTYPE, m_combPtzType);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_combSpeed);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_combServer);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_combType);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY4, m_slideSensitivity4);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY3, m_slideSensitivity3);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY2, m_slideSensitivity2);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY1, m_slideSensitivity1);
	DDX_Control(pDX, IDC_LIST_MDINFO, m_listMDInfo);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_slideVolume);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_slideHue);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_slideSaturation);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_slideContrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_slideBright);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSDKDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSDKDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(IDC_BTN_PTZSTOP, OnBtnPtzstop)
	ON_BN_CLICKED(IDC_BTN_PTZZOOMIN, OnBtnPtzZoomIn)
	ON_BN_CLICKED(IDC_BTN_PTZZOOMOUT, OnBtnPtzZoomOut)
	ON_BN_CLICKED(IDC_BTN_PHOTO, OnBtnPhoto)
	ON_BN_CLICKED(IDC_BTN_RECORD, OnBtnRecord)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK, OnBtnPlayback)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_PTZTrans, OnBTNPTZTrans)
	ON_BN_CLICKED(IDC_BTN_PRECALL, OnBtnPrecall)
	ON_BN_CLICKED(IDC_BTN_PRESET, OnBtnPreset)
	ON_BN_CLICKED(IDC_BTN_CLEARMD, OnBtnClearMD)
	ON_BN_CLICKED(IDC_BTN_SETMD, OnBtnSetMD)
	ON_BN_CLICKED(IDC_BTN_VIDEO, OnBtnVideo)
	ON_BN_CLICKED(IDC_BTN_AUDIO, OnBtnAudio)
	ON_BN_CLICKED(IDC_BTN_PTZ, OnBtnPtz)
	ON_BN_CLICKED(IDC_BTN_MD, OnBtnMd)
	ON_BN_CLICKED(IDC_BTN_OTHER, OnBtnOther)
	ON_BN_CLICKED(IDC_BTN_TALK, OnBtnTalk)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_SETMUTE, OnBtnSetMute)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, OnSelchangeComboServer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SHOWINFO, OnCheckShowinfo)
	ON_BN_CLICKED(IDC_CHECK_SHOWALARM, OnCheckShowAlarm)
	ON_BN_CLICKED(IDC_CHECK_EDITALARM, OnCheckEditAlarm)
	ON_BN_CLICKED(IDC_CHECK_MD1, OnCheckMd1)
	ON_BN_CLICKED(IDC_CHECK_MD2, OnCheckMd2)
	ON_BN_CLICKED(IDC_CHECK_MD3, OnCheckMd3)
	ON_BN_CLICKED(IDC_CHECK_MD4, OnCheckMd4)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, OnBtnDefault)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BTN_PTZHOME, OnBtnPtzHome)
	ON_BN_CLICKED(IDC_BTN_PTZCRUISE_V, OnBtnPtzCruiseV)
	ON_BN_CLICKED(IDC_BTN_PTZCRUISE_H, OnBtnPtzCruiseH)
	ON_BN_CLICKED(IDC_BTN_PTZCTRL, OnBtnPtzCtrl)
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	ON_BN_CLICKED(IDC_BTN_SETTIME, OnBtnSettime)
	ON_BN_CLICKED(IDC_BTN_OSD, OnBtnOsd)
	ON_BN_CLICKED(IDC_BTN_IRISBIG, OnBtnIrisbig)
	ON_BN_CLICKED(IDC_BTN_IRISSMALL, OnBtnIrissmall)
	ON_BN_CLICKED(IDC_BTN_FOCUSIN, OnBtnFocusin)
	ON_BN_CLICKED(IDC_BTN_FOCUSOUT, OnBtnFocusout)
	ON_BN_CLICKED(IDC_BTN_NET, OnBtnNet)
	ON_BN_CLICKED(IDC_BTN_WIFI, OnBtnWifi)
	ON_BN_CLICKED(IDC_BTN_SEL, OnBtnSel)
	ON_BN_CLICKED(IDC_BTN_NET_SNAP, OnBtnNetSnap)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_WND_LBUTTONDOWN, OnSetCurScreen)
	ON_MESSAGE(WM_WND_RBUTTONDOWN, OnShowMenu)
	ON_MESSAGE(WM_EVENT_MSG, EventMsgPross)
	ON_MESSAGE(WM_ALARM_MSG, ShowAlarmInfo)
	ON_MESSAGE(WM_WND_MOUSEMOVE, OnChangePicSize)
	ON_MESSAGE(WM_UPDATE_DEVDATA, GetDevMsg)
	ON_COMMAND_RANGE(WM_MENU_FULLSCREEN, WM_MENU_CLOSE, OnMenuCommand)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDKDemoDlg message handlers

BOOL CSDKDemoDlg::OnInitDialog()
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int i = 0;

	m_sPath[0] = '\0';
	CString strPath = g_strPath + "\\config.ini";
	GetPrivateProfileString("CONFIG", "sFilePath", NULL, m_sPath, 64, strPath);

	m_ScreenPannel.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 2000-1);
	m_ScreenPannel.ShowWindow(SW_SHOW);
	m_ScreenPannel.HI_PANNEL_InitScreen(2);
	
	m_ScreenPannel.MoveWindow(10, 10, 720, 590);//540

	m_pScHandle = NULL;
	m_u32CurScr = 0;
	memset(&m_sCamInfo, 0, sizeof(m_sCamInfo));
	memset(&m_alarmInfo, 0, sizeof(ALARM_INFO_S));
	memset(&m_PannelRect, 0, sizeof(CRect));
	memset(&m_mdParam, 0, sizeof(m_mdParam));
	m_nPage = -1;

	m_s32TalkOSD = IDB_TALK;

	SetWindowText(SDKDEOME_VERSION);
#ifdef _DEBUG
	SetDlgItemText(IDC_COMBO_SERVER, "192.168.1.89");
	//SetWindowText(SDKDEOME_VERSION+"-Debug");
#endif
	//SetDlgItemText(IDC_COMBO_SERVER, "192.168.1.21");
	SetDlgItemText(IDC_EDIT_USERNAME, "admin");
	SetDlgItemText(IDC_EDIT_PASSWORD, "admin");
	SetDlgItemText(IDC_EDIT_PORT, "80");

	m_combRecType.InsertString(0, "ASF");
	m_combRecType.InsertString(1, "AVI");
	m_combRecType.InsertString(2, ConvertString("Custom"));
	m_combRecType.SetCurSel(1);

	m_combType.InsertString(0, ConvertString("First Stream"));
	m_combType.InsertString(1, ConvertString("Second Stream"));
	m_combType.InsertString(2, ConvertString("Third Stream"));
	m_combType.SetCurSel(0);

	m_combPtzType.InsertString(0, ConvertString("Continuous"));
	m_combPtzType.InsertString(1, ConvertString("Step"));
	m_combPtzType.SetCurSel(0);

	m_slideBright.SetRange(0, 255);
	m_slideHue.SetRange(0, 255);
	m_slideSaturation.SetRange(0, 255);
	m_slideContrast.SetRange(0, 255);
	
	m_slideVolume.SetRange(0, 100);
	
	

	CString strBuf;
	m_nMaxFrame = 30;

	for(i=0; i<64; i++)
	{
		strBuf.Format("%d", i);
		m_combSpeed.InsertString(i, strBuf);
	}
	m_combSpeed.SetCurSel(40);

	for(i=0; i<128; i++)
	{
		strBuf.Format("通道 %03d", i);
		m_combChannel.InsertString(i, strBuf);
	}
	m_combChannel.SetCurSel(1);

	m_slideSensitivity1.SetRange(0, 100);
	m_slideSensitivity2.SetRange(0, 100);
	m_slideSensitivity3.SetRange(0, 100);
	m_slideSensitivity4.SetRange(0, 100);

	SetDlgItemText(IDC_EDIT_PTZDATA, "FF010008001F28");

	SetCtlPos();
	ShowConfigPage(3);
	ShowCtlPage(0);

	SetTimer(1, 1000, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSDKDemoDlg::SetCtlPos()
{
	/*GetDlgItem(IDC_SLIDER_SENSITIVITY1)->MoveWindow(810, 500, 100, 15);
	GetDlgItem(IDC_SLIDER_SENSITIVITY2)->MoveWindow(810, 525, 100, 15);
	GetDlgItem(IDC_SLIDER_SENSITIVITY3)->MoveWindow(810, 550, 100, 15);
	GetDlgItem(IDC_SLIDER_SENSITIVITY4)->MoveWindow(810, 575, 100, 15);
	GetDlgItem(IDC_CHECK_MD1)->MoveWindow(930, 495, 45, 20);
	GetDlgItem(IDC_CHECK_MD2)->MoveWindow(930, 520, 45, 20);
	GetDlgItem(IDC_CHECK_MD3)->MoveWindow(930, 545, 45, 20);
	GetDlgItem(IDC_CHECK_MD4)->MoveWindow(930, 570, 45, 20);
	GetDlgItem(IDC_BTN_SETMD)->MoveWindow(910, 600, 60, 20);
	GetDlgItem(IDC_CHECK_EDITALARM)->MoveWindow(770, 600, 110, 20);
	GetDlgItem(IDC_T_AERA1)->MoveWindow(770, 500, 40, 20);
	GetDlgItem(IDC_T_AERA2)->MoveWindow(770, 525, 40, 20);
	GetDlgItem(IDC_T_AERA3)->MoveWindow(770, 550, 40, 20);
	GetDlgItem(IDC_T_AERA4)->MoveWindow(770, 575, 40, 20);
	GetDlgItem(IDC_T_MD1)->MoveWindow(910, 500, 20, 20);
	GetDlgItem(IDC_T_MD2)->MoveWindow(910, 525, 20, 20);
	GetDlgItem(IDC_T_MD3)->MoveWindow(910, 550, 20, 20);
	GetDlgItem(IDC_T_MD4)->MoveWindow(910, 575, 20, 20);*/


	int x = 20;
	GetDlgItem(IDC_SLIDER_BRIGHT)->MoveWindow(830, 275+x, 150, 20);
	GetDlgItem(IDC_SLIDER_SATURATION)->MoveWindow(830, 300+x, 150, 20);
	GetDlgItem(IDC_SLIDER_CONTRAST)->MoveWindow(830, 325+x, 150, 20);
	GetDlgItem(IDC_SLIDER_HUE)->MoveWindow(830, 350+x, 150, 20);
	GetDlgItem(IDC_BTN_DEFAULT)->MoveWindow(915, 375+x, 60, 20);
	GetDlgItem(IDC_T_BRIGHT)->MoveWindow(760, 278+x, 70, 20);
	GetDlgItem(IDC_T_SATURATION)->MoveWindow(760, 303+x, 70, 20);
	GetDlgItem(IDC_T_CONTRAST)->MoveWindow(760, 328+x, 70, 20);
	GetDlgItem(IDC_T_HUE)->MoveWindow(760, 353+x, 70, 20);
	GetDlgItem(IDC_T_HDHUE)->MoveWindow(750, 380+x, 150, 20);
}

void CSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSDKDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSDKDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSDKDemoDlg::UpdataLoginInfo(HI_U32 u32Chn)
{
	CString strBuf;
	if(strcmp(m_sCamInfo[u32Chn].sHost, "") == 0)
	{
		SetDlgItemText(IDC_COMBO_SERVER, "");
	}else{
		strBuf.Format("%s", m_sCamInfo[u32Chn].sHost);//, m_sCamInfo[u32Chn].u32Stream);
		SetDlgItemText(IDC_COMBO_SERVER, strBuf);
		m_combChannel.SetCurSel(m_sCamInfo[u32Chn].s32Channel);
	}


	/*strBuf.Format("%d", m_sCamInfo[u32Chn].u16Port);
	SetDlgItemText(IDC_EDIT_PORT, strBuf);

	SetDlgItemText(IDC_EDIT_USERNAME, m_sCamInfo[u32Chn].sUser);
	SetDlgItemText(IDC_EDIT_PASSWORD, m_sCamInfo[u32Chn].sPass);*/
}

void CSDKDemoDlg::UpdateCotrl(HI_U32 u32Chn)
{
	//UpdateData();
	CString strBuf;
	int i = 0;

	if(m_sCamInfo[u32Chn].lHandle == 0)
		m_combType.SetCurSel(0);
	else
	{
	}

	EnableCtrl(u32Chn);

	int videoType = m_combType.GetCurSel();

	if(m_sCamInfo[u32Chn].lHandle != 0)
		SetDlgItemText(IDC_CONNECT, ConvertString("Disconnect"));
	else
		SetDlgItemText(IDC_CONNECT, ConvertString("Connect"));

	if(m_sCamInfo[u32Chn].bRecord == HI_TRUE)
		SetDlgItemText(IDC_BTN_RECORD, ConvertString("Stop Record"));
	else
		SetDlgItemText(IDC_BTN_RECORD, ConvertString("Record"));

	if(m_sCamInfo[u32Chn].bTalk == HI_TRUE)
		SetDlgItemText(IDC_BTN_TALK, ConvertString("Stop Talk"));
	else
		SetDlgItemText(IDC_BTN_TALK, ConvertString("Talk"));

	if(m_sCamInfo[u32Chn].eMute == AUDIO_MUTE_ON)
		SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Listen"));
	else
		SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Mute"));

	((CButton *)GetDlgItem(IDC_CHECK_SHOWINFO))->SetCheck(m_sCamInfo[u32Chn].bShowInfo);
	((CButton *)GetDlgItem(IDC_CHECK_SHOWALARM))->SetCheck(m_sCamInfo[u32Chn].bAlarmArea);

	SetDlgItemText(IDC_EDIT_DEVTYPE, m_sCamInfo[u32Chn].product.sProduct);
	SetDlgItemText(IDC_EDIT_VENDOR, m_sCamInfo[u32Chn].product.sVendor);
	SetDlgItemText(IDC_ST_SHOWINFO, "");

	m_slideBright.SetPos(m_sCamInfo[u32Chn].display.u32Brightness);
	m_slideSaturation.SetPos(m_sCamInfo[u32Chn].display.u32Saturation);
	m_slideHue.SetPos(m_sCamInfo[u32Chn].display.u32Hue);	
	m_slideContrast.SetPos(m_sCamInfo[u32Chn].display.u32Contrast);

	m_slideVolume.SetPos(m_sCamInfo[u32Chn].s32Volume);

	//m_combResolution.EnableWindow();

	//========================MD==========================
	m_slideSensitivity1.SetPos(m_sCamInfo[u32Chn].mdParam[0].u32Sensitivity);
	m_slideSensitivity2.SetPos(m_sCamInfo[u32Chn].mdParam[1].u32Sensitivity);
	m_slideSensitivity3.SetPos(m_sCamInfo[u32Chn].mdParam[2].u32Sensitivity);
	m_slideSensitivity4.SetPos(m_sCamInfo[u32Chn].mdParam[3].u32Sensitivity);

	strBuf.Format("%d", m_sCamInfo[u32Chn].mdParam[0].u32Sensitivity);
	SetDlgItemText(IDC_T_MD1, strBuf);
	strBuf.Format("%d", m_sCamInfo[u32Chn].mdParam[1].u32Sensitivity);
	SetDlgItemText(IDC_T_MD2, strBuf);
	strBuf.Format("%d", m_sCamInfo[u32Chn].mdParam[2].u32Sensitivity);
	SetDlgItemText(IDC_T_MD3, strBuf);
	strBuf.Format("%d", m_sCamInfo[u32Chn].mdParam[3].u32Sensitivity);
	SetDlgItemText(IDC_T_MD4, strBuf);

	((CButton *)GetDlgItem(IDC_CHECK_MD1))->SetCheck(m_sCamInfo[u32Chn].mdParam[0].blEnable);
	((CButton *)GetDlgItem(IDC_CHECK_MD2))->SetCheck(m_sCamInfo[u32Chn].mdParam[1].blEnable);
	((CButton *)GetDlgItem(IDC_CHECK_MD3))->SetCheck(m_sCamInfo[u32Chn].mdParam[2].blEnable);
	((CButton *)GetDlgItem(IDC_CHECK_MD4))->SetCheck(m_sCamInfo[u32Chn].mdParam[3].blEnable);

	((CButton *)GetDlgItem(IDC_CHECK_EDITALARM))->SetCheck(m_sCamInfo[u32Chn].bEditArea);
}


void CSDKDemoDlg::EnableCtrl(HI_U32 u32Chn)
{
	HI_S32 s32Enable = m_sCamInfo[u32Chn].pSupport.u32Operation;

	if(!(s32Enable & SUPPORTATTR_BRIGHTNESS_FLAG))
		m_slideBright.EnableWindow(FALSE);
	else
		m_slideBright.EnableWindow(TRUE);

	if(!(s32Enable & SUPPORTATTR_CONTRAST_FLAG))
		m_slideContrast.EnableWindow(FALSE);
	else
		m_slideContrast.EnableWindow(TRUE);

	if(!(s32Enable & SUPPORTATTR_SATURATION_FLAG))
		m_slideSaturation.EnableWindow(FALSE);
	else
		m_slideSaturation.EnableWindow(TRUE);

	if(!(s32Enable & SUPPORTATTR_HUE_FLAG))
		m_slideHue.EnableWindow(FALSE);
	else
		m_slideHue.EnableWindow(TRUE);



	int videoType = m_combType.GetCurSel();
	if(m_sCamInfo[u32Chn].u32Stream == HI_STREAM_1)
	{
		GetDlgItem(IDC_CHECK_EDITALARM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SETMD)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_EDITALARM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SETMD)->EnableWindow(FALSE);
	}

	int i = 0;
	CString strBuf;
	if(strstr(m_sCamInfo[u32Chn].product.sProduct, "S3") != NULL)//TD
	{
		m_slideBright.SetRange(0, 255);
		m_slideContrast.SetRange(0, 6);
		m_slideSaturation.SetRange(0, 255);
	}
	if(strstr(m_sCamInfo[u32Chn].product.sProduct, "S6") != NULL)
	{
		m_slideBright.SetRange(0, 4);
		m_slideContrast.SetRange(0, 4);
		m_slideSaturation.SetRange(0, 2);
	}
	else if(strstr(m_sCamInfo[u32Chn].product.sProduct, "S5") != NULL || 
			strstr(m_sCamInfo[u32Chn].product.sProduct, "S8") != NULL)
	{
		m_slideBright.SetRange(0, 6);
		m_slideContrast.SetRange(0, 8);
		m_slideSaturation.SetRange(0, 6);
	}
	else if(strstr(m_sCamInfo[u32Chn].product.sProduct, "S7") != NULL ||
			strstr(m_sCamInfo[u32Chn].product.sProduct, "S9") != NULL)
	{
		m_slideBright.SetRange(0, 255);
		m_slideContrast.SetRange(0, 7);
		m_slideSaturation.SetRange(0, 255);
	}
	else if(strstr(m_sCamInfo[u32Chn].product.sProduct, "Sc") != NULL ||
		strstr(m_sCamInfo[u32Chn].product.sProduct, "Sd") != NULL)
	{
		m_slideBright.SetRange(0, 100);
		m_slideContrast.SetRange(0, 100);
		m_slideSaturation.SetRange(0, 100);
	}
	else if(strstr(m_sCamInfo[u32Chn].product.sProduct, "Se") != NULL ||
		strstr(m_sCamInfo[u32Chn].product.sProduct, "Sf") != NULL)
	{
		m_slideBright.SetRange(0, 100);
		m_slideContrast.SetRange(0, 100);
		m_slideSaturation.SetRange(0, 255);
		m_slideHue.SetRange(0, 100);
	}
	else
	{
		m_slideBright.SetRange(0, 255);
		m_slideContrast.SetRange(0, 255);
		m_slideSaturation.SetRange(0, 255);
	}

	if (strstr(m_sCamInfo[u32Chn].product.sProduct, "Z0") != NULL ||
		strstr(m_sCamInfo[u32Chn].product.sProduct, "NV530") != NULL)
	{
		//GetDlgItem(IDC_BTN_PTZCRUISE_V)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_PTZCRUISE_H)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_PTZHOME)->EnableWindow(TRUE);
	}
	else
	{
		//GetDlgItem(IDC_BTN_PTZCRUISE_V)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_PTZCRUISE_H)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_PTZHOME)->EnableWindow(FALSE);
	}
}

void CSDKDemoDlg::GetVideoInfo(HI_U32 u32Chn)
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[u32Chn].lHandle)
	{
		//MessageBox("没有连接");
		return;
	}

	s32Ret = HI_SDK_GetSupportAttr(m_sCamInfo[u32Chn].lHandle,
								   &m_sCamInfo[u32Chn].pSupport);

	/*printf("%x, %x, %d, %d, %d\n", m_sCamInfo[u32Chn].pSupport.u32Operation,
									m_sCamInfo[u32Chn].pSupport.u32Reslution,
									m_sCamInfo[u32Chn].pSupport.u32FrameMax,
									m_sCamInfo[u32Chn].pSupport.u32BitRateMin,
									m_sCamInfo[u32Chn].pSupport.u32BitRateMax);*/
	//product
	memset(&m_sCamInfo[u32Chn].product, 0, sizeof(HI_S_ProductVendor));
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[u32Chn].lHandle, 
							  HI_GET_PRODUCT_VENDOR, 
							  &m_sCamInfo[u32Chn].product, 
							  sizeof(HI_S_ProductVendor));
	//display
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[u32Chn].lHandle, 
							  HI_CMD_DISPLAY, 
							  &m_sCamInfo[u32Chn].display, 
							  sizeof(HI_S_Display));

	//md
	int i = 0;
	for(i=0; i<MAX_MD_NUMBER; i++)
	{
		m_sCamInfo[u32Chn].mdParam[i].u32Area = HI_MOTION_AREA_1 + i;
		s32Ret = HI_SDK_GetConfig(m_sCamInfo[u32Chn].lHandle, 
								HI_CMD_MD_PARAM, 
								&m_sCamInfo[u32Chn].mdParam[i], 
								sizeof(HI_S_MD_PARAM));

		//printf("%d, %d, %d, %d, %d\n", m_sCamInfo[u32Chn].mdParam[i].u32X, m_sCamInfo[u32Chn].mdParam[i].u32Y,
		//	m_sCamInfo[u32Chn].mdParam[i].u32Width, m_sCamInfo[u32Chn].mdParam[i].u32Height, m_sCamInfo[u32Chn].mdParam[i].blEnable);

	}

	s32Ret = HI_SDK_GetVolume(m_sCamInfo[u32Chn].lHandle, AUDIO_OUT, &m_sCamInfo[u32Chn].s32Volume);
	s32Ret = HI_SDK_GetMute(m_sCamInfo[u32Chn].lHandle, AUDIO_OUT, &m_sCamInfo[u32Chn].eMute);

	if(m_sCamInfo[u32Chn].u32Stream == HI_STREAM_1)
		m_combType.SetCurSel(0);
	else if(m_sCamInfo[u32Chn].u32Stream == HI_STREAM_2)
		m_combType.SetCurSel(1);
	else
		m_combType.SetCurSel(2);
	UpdateCotrl(u32Chn);
}


void CSDKDemoDlg::OnSelchangeComboServer() 
{
	CString strComboText = "";
	CString strBuf = "";
	HI_U32 u32Change = MAXCAM;
	HI_U32 u32Chn=0;
	
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_SERVER);
	pCombo->GetLBText(pCombo->GetCurSel(), strComboText);
	//GetDlgItemText(IDC_COMBO_SERVER, strComboText);

	for(int i=0; i<100; i++)
	{
		if(strcmp(m_IpInfo[i].sIp, "") == 0)
			break;

		if(strcmp(m_IpInfo[i].sIp, strComboText.GetBuffer(0)) == 0)
		{
			strBuf.Format("%d", m_IpInfo[i].u32Port);
			SetDlgItemText(IDC_EDIT_PORT, strBuf);
			break;
		}
	}
	
	for(u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(0 != m_sCamInfo[u32Chn].lHandle)
		{
			//strBuf.Format("%s:%d", m_sCamInfo[u32Chn].sHost, m_sCamInfo[u32Chn].u32Stream);
			if(m_sCamInfo[u32Chn].sHost == strComboText.GetBuffer(0))
			{
				u32Change = u32Chn;
				break;
			}
		}else{
			if(u32Change == MAXCAM)
				u32Change = u32Chn;
		}
	}
	
	//printf("%d\n", u32Change);
	if(u32Change >= MAXCAM)
		return;
	
	UpdataLoginInfo(u32Change);
	if(m_sCamInfo[u32Chn].u32Stream == HI_STREAM_1)
		m_combType.SetCurSel(0);
	else if(m_sCamInfo[u32Chn].u32Stream == HI_STREAM_2)
		m_combType.SetCurSel(1);
	else
		m_combType.SetCurSel(2);
	UpdateCotrl(u32Change);
	m_u32CurScr = u32Change;
}

bool CSDKDemoDlg::IsPublicIP(HI_CHAR *strIp)
{
	//10.x.x.x
	if ((ntohl(inet_addr("10.0.0.0")) <= ntohl(inet_addr(strIp))) &&
		(ntohl(inet_addr("10.255.255.255")) >= ntohl(inet_addr(strIp))))
	{
		return false;
	}
	//172.16.x.x---172.31.x.x
	if ((ntohl(inet_addr("172.16.0.0")) <= ntohl(inet_addr(strIp))) &&
		(ntohl(inet_addr("172.31.255.255")) >= ntohl(inet_addr(strIp))))
	{
		return false;
	}
	//192.168.x.x
	if ((ntohl(inet_addr("192.168.0.0")) <= ntohl(inet_addr(strIp))) &&
		(ntohl(inet_addr("192.168.255.255")) >= ntohl(inet_addr(strIp))))
	{
		return false;
	}
	
	return true;
}
HI_S32 CSDKDemoDlg::CouterBufNumber(HI_VEDIO_INFO m_sCamInfo)
{
	HI_S32 s32Ret = HI_SUCCESS;
	HI_S32 s32Value = 0;
	HI_S32 s32Frame = 3;
	//2014/08/24
	//if(!IsPublicIP(m_sCamInfo.sHost))
	//{
	if(strstr(m_sCamInfo.product.sProduct, "Se") != NULL || strstr(m_sCamInfo.product.sProduct, "S7") != NULL)
	{
		//[720P] 广域网还4帧，局域网不缓帧
		if(IsPublicIP(m_sCamInfo.sHost))
			s32Frame = 4;//[720P]缓3帧
		else
			s32Frame = 0;
	}
	else if(strstr(m_sCamInfo.product.sProduct, "Sf") != NULL|| strstr(m_sCamInfo.product.sProduct, "Sc") != NULL)
		s32Frame=6;//[960P]缓6帧
	else if(strstr(m_sCamInfo.product.sProduct, "Sg") != NULL || strstr(m_sCamInfo.product.sProduct, "Si") != NULL||
		strstr(m_sCamInfo.product.sProduct, "Sj") != NULL|| strstr(m_sCamInfo.product.sProduct, "Sd") != NULL)
		s32Frame=8;//[1080P]缓8帧
	else
		s32Frame=0;

	return HI_SDK_SetPlayerBufNumber(m_sCamInfo.lHandle,s32Frame);
	//}
	//return HI_SDK_SetPlayerBufNumber(m_sCamInfo.lHandle, 0);
}

void CSDKDemoDlg::OnBtnConnect() 
{
	HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 u32Stream = HI_STREAM_1;
	HI_U32 u32Chn = -1;
	HI_CHAR sHost[64] = {0};
	CString strHost = "";
	int i = 0;
	HI_S32 s32Channel = m_combChannel.GetCurSel();
	
	GetDlgItemText(IDC_COMBO_SERVER, strHost);
	if(strHost == "")
	{
		MessageBox(ConvertString("Address can't for empty!"), ConvertString("Msg"));
		return;
	}

	int videoType = m_combType.GetCurSel();
	if(videoType == 0)
		u32Stream = HI_STREAM_1;
	else if(videoType == 1)
		u32Stream = HI_STREAM_2;
	else
		u32Stream = HI_STREAM_3;

	memcpy(sHost, strHost, strlen(strHost));

	for(i=0; i<MAXCAM; i++)
	{
		if(0 != m_sCamInfo[i].lHandle)
		{
			if(strcmp(m_sCamInfo[i].sHost, sHost) == 0 && m_sCamInfo[i].s32Channel == s32Channel)// && (m_sCamInfo[i].u32Stream == u32Stream))
			{
				LoginOut(i);
				return;
			}
		}else{
			if(u32Chn == -1)
			{
				u32Chn = i;
			}
		}
	}

	if(u32Chn == -1)
	{
		MessageBox(ConvertString("Most can also connected 4 Camera!"));
		return;
	}


	HI_HANDLE lHandle = 0;
	HI_CHAR sUser[32] = {0};
	HI_CHAR sPass[32] = {0};
	HI_U16  u16Port = 0; 
	
	CString strUser = "";
	CString strPass = "";
	CString strPort = "";
	
	GetDlgItemText(IDC_EDIT_USERNAME, strUser);
	GetDlgItemText(IDC_EDIT_PASSWORD, strPass);
	GetDlgItemText(IDC_EDIT_PORT, strPort);
	
	memcpy(sUser, strUser, strlen(strUser));
	memcpy(sPass, strPass, strlen(strPass));
	u16Port = atoi(strPort);

	HI_S32 s32ErrInfo = 0;
	lHandle = HI_SDK_LoginExt(sHost, sUser, sPass, u16Port, 10000, &s32ErrInfo);
	if(0 == lHandle)
	{
		MessageBox(ConvertString("Login Failure!"));
		return;
	}

	m_sCamInfo[u32Chn].lHandle = lHandle;
	m_sCamInfo[u32Chn].u16Port = u16Port;
	m_sCamInfo[u32Chn].u32Stream = videoType;
	memcpy(m_sCamInfo[u32Chn].sHost, sHost, strlen(sHost));
	memcpy(m_sCamInfo[u32Chn].sUser, sUser, strlen(sUser));
	memcpy(m_sCamInfo[u32Chn].sPass, sPass, strlen(sPass));
	for(i=0; i<MAX_MD_NUMBER; i++)
	{
		m_sCamInfo[u32Chn].mdParam[i].u32Channel = HI_CHANNEL_1;
	}

	m_sCamInfo[u32Chn].u32Stream = u32Stream;
	m_sCamInfo[u32Chn].s32Channel = s32Channel;

	//s32Ret = HI_SDK_SetConnectTime(lHandle, 2000);

	s32Ret = HI_SDK_SetEventCallBack(lHandle, (HI_U32)lHandle, OnEventCallBack, this);
	s32Ret = HI_SDK_SetMessageCallBack(lHandle, (HI_U32)lHandle, OnMessageCallBack, this);
	s32Ret = HI_SDK_SetDrawCallBack(lHandle, (HI_U32)lHandle, OnDrawCallBack, this);
	//s32Ret = HI_SDK_SetDecCallBack(lHandle, u32Chn, OnDecCallBack, this);
	HI_SDK_SetDisplayCallback(lHandle, HI_TRUE);
	
	HI_S_STREAM_INFO_EXT struStreamInfo;
	struStreamInfo.u32Channel = s32Channel;
	struStreamInfo.u32Stream = u32Stream;
	struStreamInfo.u32Mode = HI_STREAM_MODE_TCP;
	struStreamInfo.u8Type = HI_STREAM_ALL;

	//UINT uWndID[4] = {IDC_VIEW1, IDC_VIEW2, IDC_VIEW3, IDC_VIEW4};
	if(0 != lHandle){
		s32Ret = HI_SDK_RealPlayExt(lHandle, m_ScreenPannel.m_PlayWnd[u32Chn].GetSafeHwnd(), &struStreamInfo);
		if(HI_SUCCESS != s32Ret)
		{
			//printf("HI_SDK_RealPlayExt: %x\n", s32Ret);
			memset(&m_sCamInfo[u32Chn], 0, sizeof(HI_VEDIO_INFO));
			HI_SDK_Logout(lHandle);
			lHandle = 0;
			MessageBox(ConvertString("Connect Failure!"));
			return;
		}
	}

	GetVideoInfo(u32Chn);

	SetDlgItemText(IDC_CONNECT, ConvertString("Disconnect"));
	m_bRecord[u32Chn] = HI_FALSE;
}

void CSDKDemoDlg::LoginOut(HI_U32 u32Chn)
{
	HI_S32 s32Ret = HI_SUCCESS;

	if(0 != m_sCamInfo[u32Chn].lHandle)
	{
		HI_HANDLE lHandle = m_sCamInfo[u32Chn].lHandle;
		s32Ret = HI_SDK_StopRealPlay(lHandle);
		s32Ret = HI_SDK_Logout(lHandle);
		m_sCamInfo[u32Chn].lHandle = 0;
	}

	m_ScreenPannel.m_PlayWnd[u32Chn].Invalidate();
	memset(&m_sCamInfo[u32Chn], 0, sizeof(HI_VEDIO_INFO));
	SetDlgItemText(IDC_CONNECT, ConvertString("Connect"));
}

HI_S32 CSDKDemoDlg::StopPlay(HI_HANDLE lHandle)
{
	HI_S32 s32Ret = HI_SUCCESS;

	for(HI_U32 u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(lHandle == m_sCamInfo[u32Chn].lHandle)
		{
			if(HI_TRUE == m_bRecord[u32Chn])
			{
				HI_SDK_StopRecord(m_sCamInfo[u32Chn].lHandle);
				m_bRecord[u32Chn] = HI_FALSE;
			}
			
			s32Ret = HI_SDK_StopRealPlay(m_sCamInfo[u32Chn].lHandle);
			return s32Ret;
		}
	}

	return HI_FAILURE;
}

HI_S32 CSDKDemoDlg::Logout(HI_HANDLE lHandle)
{
	HI_S32 s32Ret = HI_SUCCESS;

	for(HI_U32 u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(lHandle == m_sCamInfo[u32Chn].lHandle)
		{
			s32Ret = HI_SDK_Logout(m_sCamInfo[u32Chn].lHandle);
			if(s32Ret == HI_SUCCESS)
			{
				memset(&m_sCamInfo[u32Chn], 0, sizeof(HI_VEDIO_INFO));
				SetDlgItemText(IDC_CONNECT, ConvertString("Connect"));
				m_sCamInfo[u32Chn].lHandle = 0;
				m_ScreenPannel.m_PlayWnd[u32Chn].Invalidate();
				return HI_SUCCESS;
			}
			break;
		}
	}

	return HI_FAILURE;
}

void CSDKDemoDlg::OnBtnPhoto() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	CString csFileName = CTime::GetCurrentTime().Format("SnapRt_%y_%m_%d_%H_%M_%S.jpg");
	char strPath[256];

	if(m_sPath[0] == '\0')
	{
		sprintf(strPath, "D:\\Sdk_file\\");
	}
	else
	{
		if(m_sPath[strlen(m_sPath)] != '\\')
			sprintf(strPath, "%s\\Sdk_file\\", m_sPath);
		else
			sprintf(strPath, "%sSdk_file\\", m_sPath);
	}

	if(!SetCurrentDirectory(strPath))
		CreateDirectoryEx(strPath);

	strcat(strPath, csFileName.GetBuffer(0));
	//HI_S32 s32Ret = HI_SDK_CapturePicture(m_sCamInfo[m_u32CurScr].lHandle, strPath);
	HI_S32 s32Ret = HI_SDK_CaptureJPEGPicture(m_sCamInfo[m_u32CurScr].lHandle, strPath);
	/*HI_S32 s32Ret = 0;
	char *sData = (char*)malloc(1024*1024);
	int nSize = 0;
	s32Ret = HI_SDK_SnapJpeg(m_sCamInfo[m_u32CurScr].lHandle, (HI_U8*)sData, 1024*1024, &nSize);
	if(s32Ret == HI_SUCCESS)
	{
		FILE *fp = fopen("D:\\photo.jpg", "wb+");
		if( !fp )
			free(sData);
		
		fwrite((const char*)sData, 1, nSize, fp);
		fclose( fp );
	}
	free(sData);
	sData = NULL;*/
}

void CSDKDemoDlg::OnBtnRecord() 
{
	// TODO: Add your control notification handler code here
	HI_S32 s32Ret = HI_SUCCESS;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	//录像 ASF 格式
	if(HI_TRUE == m_sCamInfo[m_u32CurScr].bRecord)
	{
		s32Ret = HI_SDK_StopRecord(m_sCamInfo[m_u32CurScr].lHandle);
		if(HI_SUCCESS != s32Ret)
		{
			MessageBox(ConvertString("Stop Record Failure!"));
			return;
		}

		SetDrawPic(m_sCamInfo[m_u32CurScr].lHandle, EVENT_REC_STOP);
		m_sCamInfo[m_u32CurScr].bRecord = HI_FALSE;
		SetDlgItemText(IDC_BTN_RECORD, ConvertString("Record"));
	}
	else
	{
		char strPath[256] = {0};
		CString csFileName = "";

		csFileName = CTime::GetCurrentTime().Format("RecordAt_%y_%m_%d_%H_%M_%S");
		if(m_sPath[0] == '\0')
		{
			sprintf(strPath, "D:\\Sdk_file\\");
		}
		else
		{
			if(m_sPath[strlen(m_sPath)] != '\\')
				sprintf(strPath, "%s\\Sdk_file\\", m_sPath);
			else
				sprintf(strPath, "%sSdk_file\\", m_sPath);
		}
		
		if(!SetCurrentDirectory(strPath))
			CreateDirectoryEx(strPath);
		
		strcat(strPath, csFileName.GetBuffer(0));

		int type = m_combRecType.GetCurSel();
		if(type == 0)
		{
			strcat(strPath, ".asf");
			s32Ret = HI_SDK_StartRecord(m_sCamInfo[m_u32CurScr].lHandle, strPath, FILE_FORMAT_ASF, MEDIA_VIDEO_AUDIO, 0);
		}
		else if(type == 1)
		{
			strcat(strPath, ".avi");
			s32Ret = HI_SDK_StartRecord(m_sCamInfo[m_u32CurScr].lHandle, strPath, FILE_FORMAT_AVI, MEDIA_VIDEO_AUDIO, 0);
		}
		else
		{
			strcat(strPath, ".264");
			s32Ret = HI_SDK_StartRecord(m_sCamInfo[m_u32CurScr].lHandle, strPath, FILE_FORMAT_NUDE_STREAM, MEDIA_VIDEO_AUDIO, 0);
		}

		if(HI_SUCCESS != s32Ret)
		{
			MessageBox(ConvertString("Record Failure!"));
			return;
		}

		SetDrawPic(m_sCamInfo[m_u32CurScr].lHandle, EVENT_REC_PLAY);
		m_sCamInfo[m_u32CurScr].bRecord = HI_TRUE;
		SetDlgItemText(IDC_BTN_RECORD, ConvertString("Stop Record"));
	}
}


void CSDKDemoDlg::OnBtnPlayback() 
{
	CPlaybackDlg PB;
	PB.DoModal();
}


HRESULT CSDKDemoDlg::OnDecCallBack(HI_U32 u32Chn,
								   const FRAME_INFO_S *pFrameInfo,
								   HI_VOID *pUserData)
{
	//CSDKDemoDlg *pSDKDemo = (CSDKDemoDlg*)pUserData;
	printf("%d, %d, %d\n", u32Chn, pFrameInfo->nHeight, pFrameInfo->nWidth);
	
	return 0;
}


//===============================================云台==================================================
void CSDKDemoDlg::OnBtnUp() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_UP);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_UP, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnDown() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_DOWN);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_DOWN, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnLeft() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_LEFT);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_LEFT, m_combSpeed.GetCurSel());//速度最大0x3F，最小0x00
}

void CSDKDemoDlg::OnBtnRight() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_RIGHT);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_RIGHT, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnPtzstop() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	s32Ret = HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_STOP, 5);
}

void CSDKDemoDlg::OnBtnPtzZoomIn() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_ZOOMIN);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_ZOOMIN, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnPtzZoomOut() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_ZOOMOUT);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_ZOOMOUT, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBTNPTZTrans() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	CString strPtzData="";
	
	GetDlgItemText(IDC_EDIT_PTZDATA, strPtzData);
	
	s32Ret = HI_SDK_TransPTZ(m_sCamInfo[m_u32CurScr].lHandle, strPtzData.GetBuffer(0), strlen(strPtzData));
}

void CSDKDemoDlg::OnBtnPrecall() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	CString strPresetNum = "";
	DWORD dwPresetNum=0;
	
	GetDlgItemText(IDC_EDIT_PRESET, strPresetNum);
	if(strPresetNum == "")
		dwPresetNum = 1;
	else
		dwPresetNum=atoi(strPresetNum);
	
	if ((dwPresetNum<0) || (dwPresetNum>256))
	{
		MessageBox(ConvertString("Preset point range is 0 to 255!"));
		return;
	}
	
	s32Ret = HI_SDK_PTZPreset(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_GOTO_PRESET, dwPresetNum);
}

void CSDKDemoDlg::OnBtnPreset() 
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	CString strPresetNum = "";
	DWORD dwPresetNum=0;
	
	GetDlgItemText(IDC_EDIT_PRESET,strPresetNum);
	dwPresetNum=atoi(strPresetNum);
	if ((dwPresetNum<0) || (dwPresetNum>256))
	{
		MessageBox(ConvertString("Preset point range is 0 to 255!"));
		return;
	}
	
	s32Ret = HI_SDK_PTZPreset(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_SET_PRESET, dwPresetNum);
}
//===============================================PTZ END==================================================




void CSDKDemoDlg::OnCancel() 
{
	KillTimer(1);
	CDialog::OnCancel();

	for(HI_U32 u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(0 != m_sCamInfo[u32Chn].lHandle)
		{
			if(HI_TRUE == m_bRecord[u32Chn])
			{
				HI_SDK_StopRecord(m_sCamInfo[u32Chn].lHandle);
				m_bRecord[u32Chn] = HI_FALSE;
			}

			//m_listMDInfo.ResetContent();
			HI_SDK_StopRealPlay(m_sCamInfo[u32Chn].lHandle);
			HI_SDK_Logout(m_sCamInfo[u32Chn].lHandle);
			m_sCamInfo[u32Chn].lHandle = 0;
		}
	}

	if(NULL != m_pScHandle)
	{
		HI_VSCP_DEVSCLI_Deinit(m_pScHandle);
		m_pScHandle = NULL;
	}
}


//===============================================搜索==================================================
HI_S32 SEARCH_APICALL funDevRProc(const HI_VOID* pvHandle,
                   HI_CHAR* pszRNPCode,
                   HI_S_VSCP_DEVINFO* pstruDevInfo,
                   HI_VOID* pvUserData)
{
	CSDKDemoDlg* pDlg = (CSDKDemoDlg*)pvUserData;
	pDlg->SendMessage(WM_UPDATE_DEVDATA, (UINT)pstruDevInfo, NULL);
	
    return HI_SUCCESS;
}

LRESULT CSDKDemoDlg::GetDevMsg(WPARAM wparm, LPARAM lparm)
{
	HI_S_VSCP_DEVINFO* pDev = (HI_S_VSCP_DEVINFO*)wparm;

	int i = 0;
	for(i=0; i<100; i++)
	{
		if(strcmp(m_IpInfo[i].sIp, "") == 0)
			break;

		if(strcmp(m_IpInfo[i].sIp, pDev->struNetInfo.aszIP) == 0)
			return 0;
	}

	if(i > 99)
		return 0;

	strcpy(m_IpInfo[i].sIp, pDev->struNetInfo.aszIP);
	m_IpInfo[i].u32Port = atoi(pDev->aszHttpPort);
	m_combServer.AddString(pDev->struNetInfo.aszIP);
	
	return 0;
}

CString GetPcAddress(int &ipNum)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    ULONG uBufLen = 0;
    DWORD dwRetVal = 0;
    CString strIP;

    ipNum = 0;

    GetAdaptersInfo(NULL, &uBufLen);
    pAdapterInfo = (PIP_ADAPTER_INFO) new char[uBufLen];

    dwRetVal = GetAdaptersInfo(pAdapterInfo, &uBufLen);
    if (ERROR_BUFFER_OVERFLOW == dwRetVal)
    {
        delete[] pAdapterInfo;
        pAdapterInfo = NULL;
        return "";
    }
    else if (ERROR_SUCCESS == dwRetVal)
    {
        PIP_ADAPTER_INFO pAdapterInfoTemp = pAdapterInfo;

        //循环查找网卡
        CString strTmp;
        while (pAdapterInfoTemp)
        {
            strTmp = pAdapterInfoTemp->IpAddressList.IpAddress.String; //get ip address
            strIP += strTmp;

            ipNum ++;
            if (pAdapterInfoTemp = pAdapterInfoTemp->Next)
            {
                strIP = strIP + ",";	  //partition every IP address with ','
            }
        }

        delete[] pAdapterInfo;	//release memory
        pAdapterInfo = NULL;
    }
    else
    {
        delete[] pAdapterInfo;	//release memory
        pAdapterInfo = NULL;
        return "";
    }

    if (pAdapterInfo != NULL)
    {
        delete (pAdapterInfo);
        pAdapterInfo = NULL;
    }

    return strIP;
}

void CSDKDemoDlg::GetIpArray(char ipA[][HI_VSCP_IP_STRSIZE + 1], int &num)
{
    CString str;
    int iIpNum = 0;
    int ipLen = HI_VSCP_IP_STRSIZE + 1;

    str = GetPcAddress(iIpNum);
    if (iIpNum < 1)
    {
        return ;
    }

    num = iIpNum;

    int index = 0;
    CString strIp;
    for (int i = 0; i < iIpNum; i++)
    {
        index = str.Find(',');
        if (index == -1 && str.GetLength() > 0)
        {
            strncpy(ipA[i], str.GetBuffer(0), ipLen);
        }
        if (index > -1)
        {
            strIp = str.Left(index);
            strncpy(ipA[i], strIp.GetBuffer(0), ipLen);
            str = str.Mid(index + 1);
        }
    }
}

void CSDKDemoDlg::OnBtnSearch() 
{
	HI_S32 s32Ret = HI_SUCCESS;
	
	char ip[10][16];
	int ipNum = 0;
	
	if(NULL == m_pScHandle)
	{
		s32Ret = HI_VSCP_DEVSCLI_INIT(DEVSEARCH_MULIP, DEVSEARCH_PORT, 2, &m_pScHandle);
		if ((s32Ret != HI_SUCCESS) || (m_pScHandle == HI_NULL))
		{
			MessageBox(ConvertString("Initialize search service failed!"));
			return;
		}
	}
	
	s32Ret = HI_VSCP_DEVSCLI_RegistSearchProc(m_pScHandle, funDevRProc, this);
	if (s32Ret != HI_SUCCESS)
	{
		HI_VSCP_DEVSCLI_Deinit(m_pScHandle);
		m_pScHandle = NULL;
		MessageBox(ConvertString("Registered search function failure!"));
		return;
	}

	m_combServer.ResetContent();
	memset(&m_IpInfo, 0, sizeof(m_IpInfo));
	GetIpArray(ip, ipNum);
    HI_VSCP_DEVSCLI_Register_IP(ip, ipNum);
	
    s32Ret = HI_VSCP_DEVSCLI_Search(m_pScHandle);
	if (s32Ret != HI_SUCCESS)
	{
		HI_VSCP_DEVSCLI_Deinit(m_pScHandle);
		m_pScHandle = NULL;
		MessageBox(ConvertString("Start search failed!"));
		return;
	}
}
//===============================================END==================================================



void CSDKDemoDlg::OnBtnClearMD() 
{
	// TODO: Add your control notification handler code here
	m_listMDInfo.ResetContent();
}

void CSDKDemoDlg::OnBtnSetMD() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_S32 s32Index = 0;

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	HI_S_MD_PARAM mdParam[MAX_MD_NUMBER];
	memcpy(&mdParam, &m_sCamInfo[m_u32CurScr].mdParam, sizeof(HI_S_MD_PARAM)*MAX_MD_NUMBER);

	HI_BOOL bCheck = HI_FALSE;
	if(TRUE == ((CButton *)GetDlgItem(IDC_CHECK_MD1))->GetCheck())
		bCheck = HI_TRUE;
	else
		bCheck = HI_FALSE;
	mdParam[0].blEnable = bCheck;
	mdParam[0].u32Sensitivity = m_slideSensitivity1.GetPos();

	if(TRUE == ((CButton *)GetDlgItem(IDC_CHECK_MD2))->GetCheck())
		bCheck = HI_TRUE;
	else
		bCheck = HI_FALSE;
	mdParam[1].blEnable = bCheck;
	mdParam[1].u32Sensitivity = m_slideSensitivity2.GetPos();

	if(TRUE == ((CButton *)GetDlgItem(IDC_CHECK_MD3))->GetCheck())
		bCheck = HI_TRUE;
	else
		bCheck = HI_FALSE;
	mdParam[2].blEnable = bCheck;
	mdParam[2].u32Sensitivity = m_slideSensitivity3.GetPos();

	if(TRUE == ((CButton *)GetDlgItem(IDC_CHECK_MD4))->GetCheck())
		bCheck = HI_TRUE;
	else
		bCheck = HI_FALSE;
	mdParam[3].blEnable = bCheck;
	mdParam[3].u32Sensitivity = m_slideSensitivity4.GetPos();

	/*int nValue = 0;
	CString strBuf;
	GetDlgItemText(IDC_EDIT_X, strBuf);
	nValue = atoi(strBuf);
	mdParam.u32X = nValue;
	GetDlgItemText(IDC_EDIT_Y, strBuf);
	nValue = atoi(strBuf);
	mdParam.u32Y = nValue;
	GetDlgItemText(IDC_EDIT_WIDTH, strBuf);
	nValue = atoi(strBuf);
	if(nValue < 0)
	{
		MessageBox("宽度不能小于0!");
		return;
	}
	mdParam.u32Width = nValue;
	GetDlgItemText(IDC_EDIT_HEIGHT, strBuf);
	nValue = atoi(strBuf);
	if(nValue < 0)
	{
		MessageBox("高度不能小于0!");
		return;
	}
	mdParam.u32Height = nValue;*/

	for(s32Index=0; s32Index<MAX_MD_NUMBER; s32Index++)
	{
		mdParam[s32Index].u32X = m_mdParam[m_u32CurScr][s32Index].u32X;
		mdParam[s32Index].u32Y = m_mdParam[m_u32CurScr][s32Index].u32Y;
		mdParam[s32Index].u32Width = m_mdParam[m_u32CurScr][s32Index].u32Width;
		mdParam[s32Index].u32Height = m_mdParam[m_u32CurScr][s32Index].u32Height;
		s32Ret = HI_SDK_SetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_MD_PARAM, &mdParam[s32Index], sizeof(HI_S_MD_PARAM));
		if(HI_SUCCESS == s32Ret)
		{
			memcpy(&m_sCamInfo[m_u32CurScr].mdParam[s32Index], &mdParam[s32Index], sizeof(HI_S_MD_PARAM));
		}
	}

	if(HI_TRUE == m_sCamInfo[m_u32CurScr].bEditArea)
	{
		m_sCamInfo[m_u32CurScr].bEditArea = HI_FALSE;
		HideEditAlarm(m_u32CurScr);
		((CButton *)GetDlgItem(IDC_CHECK_EDITALARM))->SetCheck(m_sCamInfo[m_u32CurScr].bEditArea);
	}

	if(HI_SUCCESS == s32Ret)
	{
		for(s32Index=0; s32Index<MAXCAM; s32Index++)
		{
			if(s32Index != (HI_S32)m_u32CurScr)
			{
				if(strcmp(m_sCamInfo[s32Index].sHost, m_sCamInfo[m_u32CurScr].sHost) == 0)
					memcpy(&m_sCamInfo[s32Index].mdParam, &m_sCamInfo[m_u32CurScr].mdParam, sizeof(m_sCamInfo[m_u32CurScr].mdParam));
			}
		}
	}
}

LONG CSDKDemoDlg::OnDrawCallBack(HI_U32 u32Chn,
								 RECT rcDrawRect,
								 HI_CHAR* pszName, 
								 HI_VOID* pUserData)
{	
	CSDKDemoDlg *pDlg = (CSDKDemoDlg*)pUserData;
	pDlg->UpdateDrawData((HI_HANDLE)u32Chn, rcDrawRect, pszName);
	return 0;
}

HI_S32 CSDKDemoDlg::UpdateDrawData(HI_HANDLE lHandle, RECT rcDrawRect, CString csDrawName)
{
	if(!::IsWindow(m_hWnd))
		return HI_FAILURE;
	
	HI_U32 u32Chn=0;
    HI_S32 s32Num = 0;
    CString strMdName = "";
    HI_S32 s32Ret = HI_FAILURE;
	
	for(u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(lHandle == m_sCamInfo[u32Chn].lHandle)
			break;
	}
    //鼠标信息对MD坐标位置进行修改后，更新MD设置模块的坐标位置信息
    for (s32Num = 0; s32Num < MAX_MD_NUMBER; s32Num++)
    {
        strMdName.Format("%d", m_mdParam[u32Chn][s32Num].u32Area);
        if (csDrawName == strMdName)
        {
            m_mdParam[u32Chn][s32Num].u32X = rcDrawRect.left;
			m_mdParam[u32Chn][s32Num].u32Width = rcDrawRect.right - rcDrawRect.left;
			m_mdParam[u32Chn][s32Num].u32Y = rcDrawRect.top;
			m_mdParam[u32Chn][s32Num].u32Height = rcDrawRect.bottom - rcDrawRect.top;
            s32Ret = HI_SUCCESS;
        }
    }
	
    return s32Ret;
}

LRESULT CSDKDemoDlg::OnChangePicSize(WPARAM wParam, LPARAM lParam)
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
		return 0;
	
	if(HI_FALSE == m_sCamInfo[m_u32CurScr].bEditArea)
		return 0;
	
	UINT nFlags = (UINT)wParam;
	CPoint pt = (CPoint)lParam;
	
    HI_SDK_MouseMove(m_sCamInfo[m_u32CurScr].lHandle, nFlags, pt, m_PannelRect);

	return 0;
}


HRESULT CSDKDemoDlg::OnEventCallBack(HI_U32 u32Chn, 
									 EVENT_TYPE_E eEventType,
									 HI_VOID* pEventData, 
									 HI_S32 s32DataNum, 
									 HI_VOID* pUserData)
{
	CSDKDemoDlg *pSDKDemo = (CSDKDemoDlg*)pUserData;

	pSDKDemo->PostMessage(WM_EVENT_MSG, (WPARAM)u32Chn, (LPARAM)eEventType);
	//pSDKDemo->EventMsgPross(u32Chn, eEventType, pEventData, s32DataNum);
	return 0;
}


LRESULT CSDKDemoDlg::EventMsgPross(WPARAM wParam, LPARAM lParam)
{
	if(!::IsWindow(m_hWnd))
		return 0;

	HI_U32 u32Chn=0;
	HI_HANDLE lHandle = (HI_HANDLE)wParam;
	for(u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(lHandle == m_sCamInfo[u32Chn].lHandle)
			break;
	}

	if(u32Chn >= MAXCAM)
		return 0;

	EVENT_TYPE_E eEventType = (EVENT_TYPE_E)lParam;

	switch(eEventType)
	{
	case EVENT_LIVE_STOP:
		break;
	case EVENT_LIVE_PLAY:
		CouterBufNumber(m_sCamInfo[u32Chn]);
		break;
	case EVENT_TALK_STOP:
		break;
	case EVENT_TALK_PLAY:
		break;
	case EVENT_REC_STOP:
		break;
	case EVENT_REC_PLAY:
		break;
	case EVENT_NET_CONNECTING:
		break;
	case EVENT_NET_CONNECTED:
		break;
	case EVENT_NET_DISCONNECT:
		break;
	case EVENT_NET_ABNORMAL:
		HI_SDK_StopRecord(m_sCamInfo[u32Chn].lHandle);
		break;
	case EVENT_NET_RECONNECT:
		break;
	case EVENT_NET_CONNECTFAIL:
		break;
	default:
		break;
	}

	return 0;
}

HRESULT CSDKDemoDlg::OnMessageCallBack(HI_U32 u32Chn,
									   MD_TYPE_E eDataType,
									   HI_U8*  pu8Buffer,
									   HI_U32 u32Length,
									   HI_VOID* pUserData)
{	
	CSDKDemoDlg *pSDKDemoDlg = (CSDKDemoDlg*)pUserData;
	//pSDKDemoDlg->ShowAlarmInfo(u32Chn, eDataType, pu8Buffer, u32Length);
	pSDKDemoDlg->SetAlarmInfo((HI_HANDLE)u32Chn, u32Length, eDataType);
	pSDKDemoDlg->PostMessage(WM_ALARM_MSG, (WPARAM)pu8Buffer, 0);

	return 0;
}

void CSDKDemoDlg::SetAlarmInfo(HI_HANDLE lHandle, HI_U32 u32Len, MD_TYPE_E eDataType)
{
	m_alarmInfo.lHandle = lHandle;
	m_alarmInfo.u32Length = u32Len;
	m_alarmInfo.eDataType = eDataType;
}

LRESULT CSDKDemoDlg::ShowAlarmInfo(WPARAM wParam, LPARAM lParam)
{
	if(!::IsWindow(m_hWnd))
		return 0;

	HI_U8* pu8Buffer = (HI_U8*)wParam;

    HI_U32 u32Len = 0;
	HI_S_ALARM_MD alarmMD;
	CString strBuf;
	CString strInfo;

	HI_HANDLE lHandle = m_alarmInfo.lHandle;
	HI_U32 u32Length = m_alarmInfo.u32Length;
	MD_TYPE_E eDataType = m_alarmInfo.eDataType;

	if(lHandle <= 0)
		return 0;

	HI_U32 u32Chn=0;
	for(u32Chn=0; u32Chn<MAXCAM; u32Chn++)
	{
		if(lHandle == m_sCamInfo[u32Chn].lHandle)
			break;
	}

	if(HI_TRUE == m_sCamInfo[u32Chn].bAlarmArea)
		DrawAlarmInfo(u32Chn, eDataType, pu8Buffer, u32Length);

	strInfo = m_sCamInfo[u32Chn].sHost;

	strInfo += CTime::GetCurrentTime().Format(" [%y-%m-%d %H:%M:%S]");

    if(eDataType == HI_MOTION_DETECTION)
    {
		strInfo += " " + ConvertString("Motion Alarm,Area:");
        for(u32Len=0; u32Len<u32Length; u32Len+=sizeof(HI_S_ALARM_MD))
        {
            memcpy(&alarmMD, pu8Buffer+u32Len, sizeof(HI_S_ALARM_MD));
			strBuf.Format("%d;", alarmMD.u32Area);
			strInfo += strBuf;
        }
    }
	else if(eDataType == HI_INPUT_ALARM)
	{
		strInfo += ConvertString("IO Alarm!");
    }
	else if(eDataType == HI_AUDIO_ALARM)
	{
		strInfo += ConvertString("Audio Alarm!");
	}
	else
		return 0;

	m_listMDInfo.AddString(strInfo);
	if(m_listMDInfo.GetTopIndex() > (m_listMDInfo.GetCount()-10))
		m_listMDInfo.SetTopIndex(m_listMDInfo.GetCount()-1); 

	return 0;
}


void CSDKDemoDlg::DrawAlarmInfo(HI_U32 u32Chn,
								MD_TYPE_E eDataType,
								HI_U8*  pu8Buffer,
								HI_U32 u32Length)
{
	if(!::IsWindow(m_hWnd))
		return;

	if(DATA_MOTION_DETECTION != eDataType)
		return;

	if(u32Chn > MAXCAM)
		return;
	
	if(0 == m_sCamInfo[u32Chn].lHandle)
		return;
	
	HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Len = 0;
	HI_S32 s32DataNum = 0;
	HI_S_ALARM_MD alarmMD;
	CString strBuf;
	
	HI_S32 i = 0;
    HI_S32 j = 0;
	
    DRAW_INFO_S struMDDrawData[MAX_MD_NUMBER];
    ZeroMemory(struMDDrawData, sizeof(DRAW_INFO_S) * MAX_MD_NUMBER);
	
	
    for (i = 0; i < MAX_MD_NUMBER; i++)
    {
        struMDDrawData[i].pDrawContant = new DRAW_GRAPH_S;
        if (NULL != struMDDrawData[i].pDrawContant)
        {
            ZeroMemory(struMDDrawData[i].pDrawContant, sizeof(DRAW_GRAPH_S));
        }
    }
	
	
	for(u32Len=0; u32Len<u32Length; u32Len+=sizeof(HI_S_ALARM_MD))
	{
		memcpy(&alarmMD, pu8Buffer+u32Len, sizeof(HI_S_ALARM_MD));
		
		sprintf(struMDDrawData[s32DataNum].szDrawName, "%d", alarmMD.u32Area);
        struMDDrawData[s32DataNum].rcDrawPos.left = alarmMD.u32X;
        struMDDrawData[s32DataNum].rcDrawPos.right = alarmMD.u32X + alarmMD.u32Width;
        struMDDrawData[s32DataNum].rcDrawPos.top = alarmMD.u32Y;
        struMDDrawData[s32DataNum].rcDrawPos.bottom = alarmMD.u32Y + alarmMD.u32Height;
		
        //绘图类型，显示类型，闪烁间隔
        struMDDrawData[s32DataNum].s32DrawFlag = GRAPH_RECTANGLE;
        struMDDrawData[s32DataNum].s32FlashType = (FLASH_WITH_RATE | FLASH_WITH_DURATION);
        struMDDrawData[s32DataNum].s32FlashRate = 4;
        struMDDrawData[s32DataNum].s32FlashDuration = 24;
        struMDDrawData[s32DataNum].s32EnableValue = HI_TRUE;
		
        ((DRAW_GRAPH_S*)struMDDrawData[s32DataNum].pDrawContant)->dwBrushColor = 0;
        ((DRAW_GRAPH_S*)struMDDrawData[s32DataNum].pDrawContant)->dwPenColor = DEFAULT_ALARM_COLOR;
        ((DRAW_GRAPH_S*)struMDDrawData[s32DataNum].pDrawContant)->u32BrushStyle = BS_HOLLOW;
		
		s32DataNum++;
	}
	
	s32Ret = HI_SDK_InputDrawData(m_sCamInfo[u32Chn].lHandle, struMDDrawData, s32DataNum, EVENT_STATE);
	
    for (j = 0; j < MAX_MD_NUMBER; j++)
    {
        if (NULL != struMDDrawData[j].pDrawContant)
        {
            SAFE_DELETE(struMDDrawData[j].pDrawContant);
        }
    }
}


HI_S32 CSDKDemoDlg::ShowEditAlarm(HI_S32 u32Chn)
{
	if(!::IsWindow(m_hWnd))
		return HI_FAILURE;

    HI_S32 s32Num = 0;
    HI_S32 s32Ret = HI_SUCCESS;
	
    if (NULL == m_sCamInfo[u32Chn].lHandle)
    {
        return HI_FAILURE;
    }
	
	//存储MD绘图数据
	DRAW_INFO_S astruMdArea[MAX_MD_NUMBER];
	ZeroMemory(astruMdArea, sizeof(DRAW_INFO_S) * MAX_MD_NUMBER);
	CRect rc;
	HI_S32 i;
	
	for (i = 0; i < MAX_MD_NUMBER; i++)
	{
		astruMdArea[i].pDrawContant = new DRAW_GRAPH_S;
		if (NULL != astruMdArea[i].pDrawContant)
		{
			ZeroMemory(astruMdArea[i].pDrawContant, sizeof(DRAW_GRAPH_S));
		}
	}
	for (s32Num = 0; s32Num<MAX_MD_NUMBER; s32Num++)
	{
		if ((HI_MOTION_AREA_1 != m_sCamInfo[u32Chn].mdParam[s32Num].u32Area)
			&&(HI_MOTION_AREA_2 != m_sCamInfo[u32Chn].mdParam[s32Num].u32Area)
			&&(HI_MOTION_AREA_3 != m_sCamInfo[u32Chn].mdParam[s32Num].u32Area)
			&&(HI_MOTION_AREA_4 != m_sCamInfo[u32Chn].mdParam[s32Num].u32Area))
		{
			continue;
		}
		if ((m_sCamInfo[u32Chn].mdParam[s32Num].u32Width <= 0)
			||(m_sCamInfo[u32Chn].mdParam[s32Num].u32Height <= 0))
		{
			continue;
		}
		
		rc.left = m_sCamInfo[u32Chn].mdParam[s32Num].u32X;
		rc.right = rc.left + m_sCamInfo[u32Chn].mdParam[s32Num].u32Width;
		rc.top = m_sCamInfo[u32Chn].mdParam[s32Num].u32Y;
		rc.bottom = rc.top + m_sCamInfo[u32Chn].mdParam[s32Num].u32Height;

		{
			sprintf(astruMdArea[s32Num].szDrawName, "%d", m_sCamInfo[u32Chn].mdParam[s32Num].u32Area);
			astruMdArea[s32Num].rcDrawPos = rc;
			astruMdArea[s32Num].s32EnableValue = m_sCamInfo[u32Chn].mdParam[s32Num].blEnable;
			//绘制矩形
			astruMdArea[s32Num].s32DrawFlag = GRAPH_RECTANGLE;
			
			((DRAW_GRAPH_S*)astruMdArea[s32Num].pDrawContant)->dwBrushColor = 0;
			((DRAW_GRAPH_S*)astruMdArea[s32Num].pDrawContant)->dwPenColor = DEFAULT_MD_COLOR;
			((DRAW_GRAPH_S*)astruMdArea[s32Num].pDrawContant)->u32BrushStyle = BS_HOLLOW;
		}
	}
	
	//将MD区域坐标信息传递到PcDraw模块
	s32Ret = HI_SDK_InputDrawData(m_sCamInfo[u32Chn].lHandle, astruMdArea, MAX_MD_NUMBER, DRAW_STATE);
	if (HI_SUCCESS == s32Ret)
	{
		memcpy(&m_mdParam[u32Chn], &m_sCamInfo[u32Chn].mdParam, sizeof(HI_S_MD_PARAM)*MAX_MD_NUMBER);
	}
	
	//释放绘图数据
	for (s32Num = 0; s32Num < MAX_MD_NUMBER; s32Num++)
	{
		if (NULL != astruMdArea[s32Num].pDrawContant)
		{
			SAFE_DELETE(astruMdArea[s32Num].pDrawContant);
		}
	}
	
	return HI_SUCCESS;
}


HI_S32 CSDKDemoDlg::HideEditAlarm(HI_S32 u32Chn)
{
	HI_S32 s32Ret = HI_FAILURE;

	if(0 == m_sCamInfo[u32Chn].lHandle)
		return s32Ret;

	HI_CHAR szDrawName[MAX_NAME_LEN] = {0};
	for (HI_S32 s32Num = 0; s32Num<MAX_MD_NUMBER; s32Num++)
	{
		sprintf(szDrawName, "%d", m_sCamInfo[u32Chn].mdParam[s32Num].u32Area);
		s32Ret = HI_SDK_EnablePic(m_sCamInfo[u32Chn].lHandle, 
								  szDrawName, 
								  HI_FALSE, 
								  DRAW_STATE);
	}
	
	return s32Ret;
}

LRESULT CSDKDemoDlg::OnSetCurScreen(WPARAM wParam, LPARAM lParam)
{
	HI_U32 u32CurScreen = wParam;

	if(u32CurScreen < 0)
		u32CurScreen = 0;
	
	if(u32CurScreen >= MAXCAM)
		u32CurScreen = MAXCAM - 1;
	
	if(m_u32CurScr != u32CurScreen)
	{
		m_u32CurScr = u32CurScreen;
		UpdataLoginInfo(u32CurScreen);
		if(m_sCamInfo[u32CurScreen].u32Stream == HI_STREAM_1)
			m_combType.SetCurSel(0);
		else if(m_sCamInfo[u32CurScreen].u32Stream == HI_STREAM_2)
			m_combType.SetCurSel(1);
		else
			m_combType.SetCurSel(2);
		UpdateCotrl(u32CurScreen);
	}

	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
		return 0;
	
	if(HI_FALSE == m_sCamInfo[m_u32CurScr].bEditArea)
		return 0;

	CRect rc;
	m_ScreenPannel.m_PlayWnd[m_u32CurScr].GetWindowRect(&rc);
	m_PannelRect.left = 0;
	m_PannelRect.top = 0;
	m_PannelRect.right = rc.right-rc.left;
	m_PannelRect.bottom = rc.bottom-rc.top;
	
	CPoint pt = (CPoint)lParam;
	HI_SDK_SelectPic(m_sCamInfo[m_u32CurScr].lHandle, pt);

	return 0;
}

LRESULT CSDKDemoDlg::OnShowMenu(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING | m_ScreenPannel.HI_PANNEL_GetFullScreen()?MF_CHECKED:MF_UNCHECKED, WM_MENU_FULLSCREEN, ConvertString("Fullscreen"));
	menu.AppendMenu(MF_STRING | HI_SDK_GetAutoAdjust(m_sCamInfo[wParam].lHandle)?MF_CHECKED:MF_UNCHECKED, WM_MENU_AUTOADJUST, ConvertString("Auto Adjust"));
	menu.AppendMenu(MF_STRING, WM_MENU_PHOTO, ConvertString("Photo"));
	menu.AppendMenu(MF_STRING, WM_MENU_CLOSE, ConvertString("Disconnect"));

	TrackPopupMenu( 
		menu.m_hMenu, 
		TPM_LEFTALIGN, 
		point.x, 
		point.y,
		0,
		m_hWnd,
		NULL);

	return 0;
}

void CSDKDemoDlg::OnMenuCommand(UINT nID)
{
	switch(nID)
	{
	case WM_MENU_FULLSCREEN:
		m_ScreenPannel.HI_PANNEL_SetFullScreen();
		break;
	case WM_MENU_AUTOADJUST:
		HI_SDK_SetAutoAdjust(m_sCamInfo[m_u32CurScr].lHandle);
		break;
	case WM_MENU_PHOTO:
		OnBtnPhoto();
		break;
	case WM_MENU_CLOSE:
		LoginOut(m_u32CurScr);
		break;
	default:
		break;
	}
}


void CSDKDemoDlg::ShowConfigPage(int nPageIndex)
{
	int nPage[5];
	int i = 0;

	if(m_nPage == nPageIndex)
		return;

	m_nPage = nPageIndex;
	for(i=0; i<5; i++)
	{
		if(i == nPageIndex)
		{
			nPage[i] = SW_SHOW;
		}
		else
		{
			nPage[i] = SW_HIDE;
		}
	}

	GetDlgItem(IDC_SLIDER_SENSITIVITY1)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_SLIDER_SENSITIVITY2)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_SLIDER_SENSITIVITY3)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_SLIDER_SENSITIVITY4)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_CHECK_MD1)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_CHECK_MD2)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_CHECK_MD3)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_CHECK_MD4)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_BTN_SETMD)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_CHECK_EDITALARM)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_AERA1)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_AERA2)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_AERA3)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_AERA4)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_MD1)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_MD2)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_MD3)->ShowWindow(nPage[3]);
	GetDlgItem(IDC_T_MD4)->ShowWindow(nPage[3]);
	
}


void CSDKDemoDlg::OnBtnVideo() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CVideoDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle, 
				m_sCamInfo[m_u32CurScr].product.sProduct, 
				&m_sCamInfo[m_u32CurScr].pSupport);
	memcpy(&m_sCamInfo[m_u32CurScr].pSupport, &dlg.m_sSupport, sizeof(HI_S_SUPPORT));
	dlg.DoModal();
}

void CSDKDemoDlg::OnBtnAudio() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CAudioDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle, m_sCamInfo[m_u32CurScr].product.sProduct);
	dlg.DoModal();
}

void CSDKDemoDlg::OnBtnPtz() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CPtzDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();
}

void CSDKDemoDlg::OnBtnMd() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CInputAlarmDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();
}

void CSDKDemoDlg::OnBtnOther() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	COtherDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle, &m_sCamInfo[m_u32CurScr].pSupport);
	dlg.DoModal();
}

HRESULT CSDKDemoDlg::OnVoiceDataCallBack(HI_U32 u32Chn,
										 HI_U8*  pu8Buf,
										 HI_S32 s32Len,
										 HI_U32 u32Pts,
										 HI_VOID* pUserData)
{	
	printf("%d, %u, %u\n", u32Chn, s32Len, u32Pts);
	return 0;
}

void CSDKDemoDlg::OnBtnTalk() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	if(m_sCamInfo[m_u32CurScr].bTalk == HI_TRUE)
	{
		s32Ret = HI_SDK_StopVoiceCom(m_sCamInfo[m_u32CurScr].lHandle);
		if(HI_SUCCESS != s32Ret)
		{
			MessageBox(ConvertString("Close Talk Failure!"));
			return;
		}

		SetDrawPic(m_sCamInfo[m_u32CurScr].lHandle, EVENT_TALK_STOP);
		m_sCamInfo[m_u32CurScr].bTalk = HI_FALSE;
		SetDlgItemText(IDC_BTN_TALK, ConvertString("Talk"));
	}
	else
	{
		//s32Ret = HI_SDK_StartVoiceCom(m_sCamInfo[m_u32CurScr].lHandle, 2, OnVoiceDataCallBack, this);
		s32Ret = HI_SDK_StartVoiceCom(m_sCamInfo[m_u32CurScr].lHandle);
		if(HI_SUCCESS != s32Ret)
		{
			MessageBox(ConvertString("Open Talk Failure!"));
			return;
		}

		SetDrawPic(m_sCamInfo[m_u32CurScr].lHandle, EVENT_TALK_PLAY);
		m_sCamInfo[m_u32CurScr].bTalk = HI_TRUE;
		SetDlgItemText(IDC_BTN_TALK, ConvertString("Stop Talk"));
	}
}

void CSDKDemoDlg::OnBtnSetMute() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	if(m_sCamInfo[m_u32CurScr].eMute == AUDIO_MUTE_ON)
	{
		s32Ret = HI_SDK_SetMute(m_sCamInfo[m_u32CurScr].lHandle, AUDIO_OUT, AUDIO_MUTE_OFF);
		if(HI_SUCCESS == s32Ret)
		{
			m_sCamInfo[m_u32CurScr].eMute = AUDIO_MUTE_OFF;
			SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Mute"));
		}else{
			MessageBox(ConvertString("Mute Failure!"));
		}
	}
	else
	{
		s32Ret = HI_SDK_SetMute(m_sCamInfo[m_u32CurScr].lHandle, AUDIO_OUT, AUDIO_MUTE_ON);
		if(HI_SUCCESS == s32Ret)
		{
			m_sCamInfo[m_u32CurScr].eMute = AUDIO_MUTE_ON;
			SetDlgItemText(IDC_BTN_SETMUTE, ConvertString("Listen"));
		}else{
			MessageBox(ConvertString("Listen Failure!"));
		}
	}
}

void CSDKDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_S32 s32Value = 0;
	int iVol = 0;
	CString strBuf = "";
	int nID = pScrollBar->GetDlgCtrlID();

	if(m_sCamInfo[m_u32CurScr].lHandle == 0)
	{
		return;
	}

	switch (nID)
    {
	case IDC_SLIDER_VOLUME: 
		iVol = m_slideVolume.GetPos();
		s32Ret = HI_SDK_SetVolume(m_sCamInfo[m_u32CurScr].lHandle, AUDIO_OUT, iVol);
		if(HI_SUCCESS == s32Ret)
		{
			m_sCamInfo[m_u32CurScr].s32Volume = iVol;
		}
		break;
	case IDC_SLIDER_SENSITIVITY1:
		s32Value = m_slideSensitivity1.GetPos();
		strBuf.Format("%d", s32Value);
		SetDlgItemText(IDC_T_MD1, strBuf);
		break;
	case IDC_SLIDER_SENSITIVITY2:
		s32Value = m_slideSensitivity2.GetPos();
		strBuf.Format("%d", s32Value);
		SetDlgItemText(IDC_T_MD2, strBuf);
		break;
	case IDC_SLIDER_SENSITIVITY3:
		s32Value = m_slideSensitivity3.GetPos();
		strBuf.Format("%d", s32Value);
		SetDlgItemText(IDC_T_MD3, strBuf);
		break;
	case IDC_SLIDER_SENSITIVITY4:
		s32Value = m_slideSensitivity4.GetPos();
		strBuf.Format("%d", s32Value);
		SetDlgItemText(IDC_T_MD4, strBuf);
		break;
	default:
		ProcessVideoScroll(nSBCode,nPos,pScrollBar);
		break;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSDKDemoDlg::ProcessVideoScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int s32Ret=0;
	int iVol = 0;
	int nID = pScrollBar->GetDlgCtrlID();
	HI_S_Display display;
	memcpy(&display, &m_sCamInfo[m_u32CurScr].display, sizeof(HI_S_Display));

	switch(nID)
	{
	case IDC_SLIDER_BRIGHT:
		iVol = m_slideBright.GetPos();
		display.u32Brightness = iVol;
		break;
	case IDC_SLIDER_SATURATION:
		iVol = m_slideSaturation.GetPos();
		display.u32Saturation = iVol;
		break;
	case IDC_SLIDER_CONTRAST:
		iVol = m_slideContrast.GetPos();
		display.u32Contrast = iVol;
	    break;
	case IDC_SLIDER_HUE:
		iVol = m_slideHue.GetPos();
		display.u32Hue = iVol;
	    break;
	default:
	    break;
	}

	s32Ret = HI_SDK_SetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_DISPLAY, &display, sizeof(HI_S_Display));
	if(HI_SUCCESS == s32Ret)
	{
		memcpy(&m_sCamInfo[m_u32CurScr].display, &display, sizeof(HI_S_Display));
	}
}

void CSDKDemoDlg::OnBtnDefault() 
{
	int s32Ret=0;
	HI_S_Display display;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	display.u32Brightness = -1;
	
	s32Ret = HI_SDK_SetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_DISPLAY, &display, sizeof(HI_S_Display));
	if(HI_SUCCESS == s32Ret)
	{
		s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, 
								  HI_CMD_DISPLAY, 
								  &m_sCamInfo[m_u32CurScr].display, 
								  sizeof(HI_S_Display));
		if(HI_SUCCESS == s32Ret)
		{
			m_slideBright.SetPos(m_sCamInfo[m_u32CurScr].display.u32Brightness);
			m_slideContrast.SetPos(m_sCamInfo[m_u32CurScr].display.u32Contrast);
			m_slideHue.SetPos(m_sCamInfo[m_u32CurScr].display.u32Hue);
			m_slideSaturation.SetPos(m_sCamInfo[m_u32CurScr].display.u32Saturation);
		}
	}

	/*HI_CHAR sID[64] = {0};
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_PRODUCTID, sID, sizeof(sID));
	MessageBox(sID);*/

	/*int s32UserNum = 0;
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_USERNUM, &s32UserNum, sizeof(int));
	CString strBuf;
	strBuf.Format("%d", s32UserNum);
	MessageBox(strBuf);*/
	/*HI_DEVICE_INFO deviceInfo;
	memset(&deviceInfo, 0, sizeof(HI_DEVICE_INFO));
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_DEVICE_INFO, &deviceInfo, sizeof(HI_DEVICE_INFO));
	
	printf("%s\n%s\n%s\n%s\n%s\n",
		deviceInfo.aszServerSerialNumber,
		deviceInfo.aszServerModel,
		deviceInfo.aszServerSoftVersion,
		deviceInfo.aszServerName,
		deviceInfo.aszStartDate);*/

	/*HI_S_NETINFO netInfo;
	memset(&netInfo, 0, sizeof(HI_S_NETINFO));
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_NET_INFO, &netInfo, sizeof(HI_S_NETINFO));
	
	printf("%s\n%s\n%s\n%s\n%s\n%s\n",
		netInfo.aszServerIP,
		netInfo.aszNetMask,
		netInfo.aszGateWay,
		netInfo.aszFDNSIP,
		netInfo.aszSDNSIP,
		netInfo.aszMacAddr);*/

	/*HI_S_HTTPPORT port;
	s32Ret = HI_SDK_GetConfig(m_sCamInfo[m_u32CurScr].lHandle, HI_CMD_HTTP_PORT, &port, sizeof(HI_S_HTTPPORT));
	printf("%d\n", port.u32HttpPort);*/
}


HI_S32 CSDKDemoDlg::SetDrawPic(HI_HANDLE lHandle, EVENT_TYPE_E eDraw)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Width = 0;
    HI_S32 s32Height = 0;
	HI_U32 u32Type = 0;
	HI_BOOL bDrawPic = HI_FALSE;
	
    if (lHandle == 0)
    {
        return HI_FALSE;
    }
	
    DRAW_INFO_S drawInfo;
    ZeroMemory(&drawInfo, sizeof(DRAW_INFO_S));

	switch(eDraw)
	{
	case EVENT_TALK_PLAY:
		sprintf(drawInfo.szDrawName, OSD_TALK);
		u32Type = IDB_TALK;
		bDrawPic = HI_TRUE;
		break;
	case EVENT_TALK_STOP:
		sprintf(drawInfo.szDrawName, OSD_TALK);
		bDrawPic = HI_FALSE;
		break;
	case EVENT_REC_PLAY:
		sprintf(drawInfo.szDrawName, OSD_REC);
		u32Type = IDB_REC;
		bDrawPic = HI_TRUE;
	    break;
	case EVENT_REC_STOP:
		sprintf(drawInfo.szDrawName, OSD_REC);
		bDrawPic = HI_FALSE;
	    break;
	default:
	    break;
	}
	
    if (HI_TRUE == bDrawPic)
    {
        s32Ret = HI_SDK_GetPicInfo(lHandle, &s32Width, &s32Height);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
		
        //composite draw data
        drawInfo.s32DrawFlag = GRAPH_PIC;
		drawInfo.u32IDBitmapRes = u32Type;

		if(IDB_TALK == u32Type)
		{
			drawInfo.rcDrawPos.left = s32Width / 2 - 24;
			drawInfo.rcDrawPos.right = s32Width / 2;
		}
		else
		{
			drawInfo.rcDrawPos.left = s32Width / 2 + 2;
			drawInfo.rcDrawPos.right = s32Width / 2 + 26;
		}

        drawInfo.rcDrawPos.top = 2;
        drawInfo.rcDrawPos.bottom = 26;

        //enable value
        drawInfo.s32EnableValue = TRUE;
        drawInfo.s32FlashType = (FLASH_WITHOUT_RATE | FLASH_WITHOUT_DURATION);

        s32Ret = HI_SDK_InputDrawData(lHandle, &drawInfo, 1, EVENT_STATE);
    }
    else if (HI_FALSE == bDrawPic)
    {
        s32Ret = HI_SDK_EnablePic(lHandle, drawInfo.szDrawName, FALSE, EVENT_STATE);
    }

    return s32Ret;
}



void CSDKDemoDlg::OnTimer(UINT nIDEvent) 
{
	HI_S32 s32Ret = HI_SUCCESS;
	HI_S32 s32BitRate = 0;
	HI_S32 s32FrameRate = 0;
	CString strInfo = "";

	switch(nIDEvent)
	{
	case 1:
		if(0 != m_sCamInfo[m_u32CurScr].lHandle)
		{
			if(m_sCamInfo[m_u32CurScr].bShowInfo == HI_TRUE)
			{
				s32Ret = HI_SDK_GetPlayRate(m_sCamInfo[m_u32CurScr].lHandle, &s32FrameRate, &s32BitRate);
				if(HI_SUCCESS == s32Ret)
				{
					strInfo.Format("%dkbps, %dfps", s32BitRate, s32FrameRate);
					SetDlgItemText(IDC_ST_SHOWINFO, strInfo);
				}
				else
				{
					SetDlgItemText(IDC_ST_SHOWINFO, "");
				}
			}
			else
			{
				SetDlgItemText(IDC_ST_SHOWINFO, "");
			}
		}

		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CSDKDemoDlg::OnCheckShowinfo() 
{
	BOOL bCheck = FALSE;

	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_SHOWINFO))->GetCheck();
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(bCheck)
			m_sCamInfo[m_u32CurScr].bShowInfo = HI_TRUE;
		else
			m_sCamInfo[m_u32CurScr].bShowInfo = HI_FALSE;
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_SHOWINFO))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckShowAlarm() 
{
	BOOL bCheck = FALSE;
	
	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_SHOWALARM))->GetCheck();
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(bCheck)
			m_sCamInfo[m_u32CurScr].bAlarmArea = HI_TRUE;
		else
			m_sCamInfo[m_u32CurScr].bAlarmArea = HI_FALSE;
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_SHOWALARM))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckEditAlarm() 
{
	BOOL bCheck = FALSE;
	
	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_EDITALARM))->GetCheck();
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(bCheck){
			m_sCamInfo[m_u32CurScr].bEditArea = HI_TRUE;
			ShowEditAlarm(m_u32CurScr);
		}
		else
		{
			m_sCamInfo[m_u32CurScr].bEditArea = HI_FALSE;
			HideEditAlarm(m_u32CurScr);
		}

		memcpy(&m_mdParam[m_u32CurScr], &m_sCamInfo[m_u32CurScr].mdParam, sizeof(m_mdParam[0]));
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_EDITALARM))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckMd1() 
{
	BOOL bCheck = FALSE;
	HI_CHAR szDrawName[MAX_NAME_LEN] = {0};

	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_MD1))->GetCheck();
	
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(HI_TRUE == m_sCamInfo[m_u32CurScr].bEditArea){
			sprintf(szDrawName, "%d", m_sCamInfo[m_u32CurScr].mdParam[0].u32Area);
			if(bCheck){
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_TRUE, DRAW_STATE);
			}
			else
			{
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_FALSE, DRAW_STATE);
			}
		}
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_MD1))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckMd2() 
{
	BOOL bCheck = FALSE;
	HI_CHAR szDrawName[MAX_NAME_LEN] = {0};
	
	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_MD2))->GetCheck();
	
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(HI_TRUE == m_sCamInfo[m_u32CurScr].bEditArea){
			sprintf(szDrawName, "%d", m_sCamInfo[m_u32CurScr].mdParam[1].u32Area);
			if(bCheck){
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_TRUE, DRAW_STATE);
			}
			else
			{
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_FALSE, DRAW_STATE);
			}
		}
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_MD2))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckMd3() 
{
	BOOL bCheck = FALSE;
	HI_CHAR szDrawName[MAX_NAME_LEN] = {0};
	
	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_MD3))->GetCheck();
	
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(HI_TRUE == m_sCamInfo[m_u32CurScr].bEditArea){
			sprintf(szDrawName, "%d", m_sCamInfo[m_u32CurScr].mdParam[2].u32Area);
			if(bCheck){
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_TRUE, DRAW_STATE);
			}
			else
			{
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_FALSE, DRAW_STATE);
			}
		}
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_MD3))->SetCheck(FALSE);
	}
}

void CSDKDemoDlg::OnCheckMd4() 
{
	BOOL bCheck = FALSE;
	HI_CHAR szDrawName[MAX_NAME_LEN] = {0};
	
	bCheck = ((CButton *)GetDlgItem(IDC_CHECK_MD4))->GetCheck();
	
	if(0 != m_sCamInfo[m_u32CurScr].lHandle)
	{
		if(HI_TRUE == m_sCamInfo[m_u32CurScr].bEditArea){
			sprintf(szDrawName, "%d", m_sCamInfo[m_u32CurScr].mdParam[3].u32Area);
			if(bCheck){
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_TRUE, DRAW_STATE);
			}
			else
			{
				HI_SDK_EnablePic(m_sCamInfo[m_u32CurScr].lHandle, szDrawName, HI_FALSE, DRAW_STATE);
			}
		}
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_MD4))->SetCheck(FALSE);
	}
}


void CSDKDemoDlg::OnSelchangeComboType() 
{
	//HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		return;
	}

	UpdateCotrl(m_u32CurScr);
}

void CSDKDemoDlg::OnBtnPtzHome() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	s32Ret = HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_HOME, 0);
}

void CSDKDemoDlg::OnBtnPtzCruiseV() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	s32Ret = HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_CRUISE_V, 0);
}

void CSDKDemoDlg::OnBtnPtzCruiseH() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	s32Ret = HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_CRUISE_H, 0);
}


void CSDKDemoDlg::ShowCtlPage(int nPageIndex)
{
	int nPage[2];
	int i = 0;

	if(nPageIndex > 2)
		return;

	for(i=0; i<2; i++)
	{
		if(i == nPageIndex)
		{
			nPage[i] = SW_SHOW;
		}
		else
		{
			nPage[i] = SW_HIDE;
		}
	}

	GetDlgItem(IDC_BTN_UP)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_LEFT)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_RIGHT)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_DOWN)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PTZSTOP)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PTZZOOMIN)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PTZZOOMOUT)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PRESET)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PRECALL)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_EDIT_PRESET)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_EDIT_PTZDATA)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_PTZTrans)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_COMBO_SPEED)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_COMBO_PTZTYPE)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_FOCUSIN)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_FOCUSOUT)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_IRISBIG)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_BTN_IRISSMALL)->ShowWindow(nPage[0]);
	//GetDlgItem(IDC_BTN_PTZCRUISE_V)->ShowWindow(nPage[0]);
	//GetDlgItem(IDC_BTN_PTZCRUISE_H)->ShowWindow(nPage[0]);
	//GetDlgItem(IDC_BTN_PTZHOME)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_T_ZOOM)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_T_SPEED)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_T_TYPE)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_T_IRIS)->ShowWindow(nPage[0]);
	GetDlgItem(IDC_T_FOCUS)->ShowWindow(nPage[0]);
	
	
	GetDlgItem(IDC_SLIDER_BRIGHT)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_SLIDER_SATURATION)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_SLIDER_CONTRAST)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_SLIDER_HUE)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_BTN_DEFAULT)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_T_BRIGHT)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_T_SATURATION)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_T_CONTRAST)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_T_HUE)->ShowWindow(nPage[1]);
	GetDlgItem(IDC_T_HDHUE)->ShowWindow(nPage[1]);
}

void CSDKDemoDlg::OnBtnPtzCtrl() 
{
	ShowCtlPage(0);
}

void CSDKDemoDlg::OnBtnColor() 
{
	ShowCtlPage(1);
}

void CSDKDemoDlg::OnBtnSettime() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}

	CTimeDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();
}

void CSDKDemoDlg::OnBtnOsd() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	COsdDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();
}



void CSDKDemoDlg::OnBtnIrisbig() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_APERTUREOUT);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_APERTUREOUT, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnIrissmall() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_APERTUREIN);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_APERTUREIN, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnFocusin() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_FOCUSIN);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_FOCUSIN, m_combSpeed.GetCurSel());
}

void CSDKDemoDlg::OnBtnFocusout() 
{
	HI_S32 s32Ret = HI_FAILURE;
	
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_S32 s32Type = m_combPtzType.GetCurSel();
	if(s32Type == 1)
		HI_SDK_PTZControlEx(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_FOCUSOUT);
	else
		HI_SDK_PTZControl(m_sCamInfo[m_u32CurScr].lHandle, HI_CTRL_PTZ_FOCUSOUT, m_combSpeed.GetCurSel());
}


void CSDKDemoDlg::OnBtnNet() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CNetDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();

	/*CInputAlarmDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();*/

	/*COtherDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();*/

	/*CPtzDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();*/

	/*CAudioDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();*/

	/*CVideoDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();*/
}



void CSDKDemoDlg::OnBtnWifi() 
{
	if(0 == m_sCamInfo[m_u32CurScr].lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	CWifiDlg dlg;
	dlg.SetHandle(m_sCamInfo[m_u32CurScr].lHandle);
	dlg.DoModal();
}
/*
void CSDKDemoDlg::OnBtnSel() 
{
	TCHAR szDir[MAX_PATH];	
	TCHAR szDirOld[MAX_PATH];
	BROWSEINFO bi;	
	ITEMIDLIST *pidl;
	
	bi.hwndOwner = this->m_hWnd;	
	bi.pidlRoot = NULL;	
	bi.pszDisplayName = NULL;	
	bi.lpszTitle = ConvertString("Connect");//ConvertString("Select a video and capture storage path");	
	bi.ulFlags = BIF_RETURNONLYFSDIRS;	
	bi.lpfn = BrowseCallbackProc ;	
	sprintf(szDirOld, "%s", m_sPath);
	bi.lParam = (LPARAM)szDirOld;	
	bi.iImage = 0;
	
	pidl = SHBrowseForFolder(&bi);
	
	if(pidl == NULL)  
	{
		return;
	}
	
	if(!SHGetPathFromIDList(pidl, szDir)) 
	{
		return;
	}
	
	m_sPath[0] = '\0';
	sprintf(m_sPath, "%s", szDir);
	CString strPath = g_strPath + "\\config.ini";
	WritePrivateProfileString("CONFIG", "sFilePath", m_sPath, strPath);
}
*/
void CSDKDemoDlg::OnBtnSel() 
{
	TCHAR szDir[MAX_PATH];	
	TCHAR szDirOld[MAX_PATH];
	BROWSEINFO bi;	
	ITEMIDLIST *pidl;
	
	bi.hwndOwner = this->m_hWnd;	
	bi.pidlRoot = NULL;	
	bi.pszDisplayName = NULL;	
	bi.lpszTitle = ConvertString("Select a video and capture storage path");	
	bi.ulFlags = BIF_RETURNONLYFSDIRS;	
	bi.lpfn = BrowseCallbackProc ;	
	sprintf(szDirOld, "%s", m_sPath);
	bi.lParam = (LPARAM)szDirOld;	
	bi.iImage = 0;
	
	pidl = SHBrowseForFolder(&bi);
	
	if(pidl == NULL)  
	{
		return;
	}
	
	if(!SHGetPathFromIDList(pidl, szDir)) 
	{
		return;
	}
	
	m_sPath[0] = '\0';
	sprintf(m_sPath, "%s", szDir);
	CString strPath = g_strPath + "\\config.ini";
	WritePrivateProfileString("CONFIG", "sFilePath", m_sPath, strPath);
}

void CSDKDemoDlg::OnBtnNetSnap() 
{
}
