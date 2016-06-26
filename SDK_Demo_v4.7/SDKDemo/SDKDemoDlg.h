// SDKDemoDlg.h : header file
//

#if !defined(AFX_SDKDEMODLG_H__76909D30_7B97_4138_B923_BB888BCFFEC1__INCLUDED_)
#define AFX_SDKDEMODLG_H__76909D30_7B97_4138_B923_BB888BCFFEC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stdafx.h"
#include "hi_vscp_devs_cli.h"
#include "ScreenPannel.h"

#include "opencv2/opencv.hpp" 
#include "yuvToRgb.h"
// extern "C" {
// #include "yuv2rgb.h"
// }

/////////////////////////////////////////////////////////////////////////////
// CSDKDemoDlg dialog
#define LISTENTIME 2

//OSD name
#define INVALIDE_OSD_ID			-1
#define OSD_TALK				"Talk OSD"
#define OSD_REC					"Rec OSD"
#define OSD_PLAYBACK			"PlayBack OSD"
#define DEFAULT_MD_COLOR		RGB(0, 255, 0)
#define DEFAULT_ALARM_COLOR		RGB(255, 0, 0)  

#define WM_MENU_FULLSCREEN	WM_USER+201
#define WM_MENU_AUTOADJUST	WM_USER+202
#define WM_MENU_PHOTO		WM_USER+203
#define WM_MENU_CLOSE		WM_USER+204

#define WM_EVENT_MSG		WM_USER+205
#define WM_ALARM_MSG		WM_USER+206
#define WM_UPDATE_DEVDATA	WM_USER+1001

#define WM_EVENT_DISCONNECT WM_USER+10

typedef struct hiVEDIO_INFO
{
	HI_HANDLE			lHandle;	//SDK句柄
	HI_CHAR				sHost[64];	//IPC地址
	HI_CHAR				sUser[32];	//用户名
	HI_CHAR				sPass[32];	//密码
	HI_BOOL				bTalk;		//对讲状态
	HI_BOOL				bRecord;	//录像状态
	HI_BOOL				bShowInfo;	//播放时显示码率、帧率
	HI_BOOL				bAlarmArea;	//发生移动侦测时显示红色报警框
	HI_BOOL				bEditArea;	//编译报警区域
	HI_U16				u16Port;	//端口
	HI_U32				u32Stream;	//码流
	HI_S32				s32Volume;	//音量
	HI_S32				s32Channel;	//通道
	AUDIO_MUTE_E		eMute;		//声音状态
	HI_S_ProductVendor	product;	//产品类型
	HI_S_Display		display;	//色彩
	HI_S_MD_PARAM		mdParam[MAX_MD_NUMBER];	//移动侦测区域
	HI_S_SUPPORT		pSupport;	//设备能力，包括分辨率，最大码率
}HI_VEDIO_INFO;

typedef struct hiALARM_INFO 
{
	HI_HANDLE lHandle;
	HI_U32 u32Length;
	MD_TYPE_E eDataType;
}ALARM_INFO_S;

typedef struct hiIP_INFO 
{
	HI_CHAR sIp[16];
	HI_U32 u32Port;
}IP_INFO_S;

class CSDKDemoDlg : public CDialog
{
// Construction
public:
	CSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor
	//~CSDKDemoDlg();

// Dialog Data
	//{{AFX_DATA(CSDKDemoDlg)
	enum { IDD = IDD_SDKDEMO_DIALOG };
	CComboBox	m_combChannel;
	CComboBox	m_combRecType;
	CComboBox	m_combPtzType;
	CComboBox	m_combSpeed;
	CComboBox	m_combServer;
	CComboBox	m_combType;
	CSliderCtrl	m_slideSensitivity4;
	CSliderCtrl	m_slideSensitivity3;
	CSliderCtrl	m_slideSensitivity2;
	CSliderCtrl	m_slideSensitivity1;
	CListBox	m_listMDInfo;
	CSliderCtrl	m_slideVolume;
	CSliderCtrl	m_slideHue;
	CSliderCtrl	m_slideSaturation;
	CSliderCtrl	m_slideContrast;
	CSliderCtrl	m_slideBright;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDKDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSDKDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnLeft();
	afx_msg void OnBtnRight();
	afx_msg void OnBtnPtzstop();
	afx_msg void OnBtnPtzZoomIn();
	afx_msg void OnBtnPtzZoomOut();
	afx_msg void OnBtnPhoto();
	afx_msg void OnBtnRecord();
	virtual void OnCancel();
	afx_msg void OnBtnPlayback();
	afx_msg void OnBtnSearch();
	afx_msg void OnBTNPTZTrans();
	afx_msg void OnBtnPrecall();
	afx_msg void OnBtnPreset();
	afx_msg void OnBtnClearMD();
	afx_msg void OnBtnSetMD();
	afx_msg void OnSelchangeComboAera();
	afx_msg void OnBtnVideo();
	afx_msg void OnBtnAudio();
	afx_msg void OnBtnPtz();
	afx_msg void OnBtnMd();
	afx_msg void OnBtnOther();
	afx_msg void OnBtnTalk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnSetMute();
	afx_msg void OnSelchangeComboServer();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckShowinfo();
	afx_msg void OnCheckShowAlarm();
	afx_msg void OnCheckEditAlarm();
	afx_msg void OnCheckMd1();
	afx_msg void OnCheckMd2();
	afx_msg void OnCheckMd3();
	afx_msg void OnCheckMd4();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnDefault();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnBtnPtzHome();
	afx_msg void OnBtnPtzCruiseV();
	afx_msg void OnBtnPtzCruiseH();
	afx_msg void OnBtnPtzCtrl();
	afx_msg void OnBtnColor();
	afx_msg void OnBtnSettime();
	afx_msg void OnBtnOsd();
	afx_msg void OnBtnIrisbig();
	afx_msg void OnBtnIrissmall();
	afx_msg void OnBtnFocusin();
	afx_msg void OnBtnFocusout();
	afx_msg void OnBtnNet();
	afx_msg void OnBtnWifi();
	afx_msg void OnBtnSel();
	afx_msg void OnBtnNetSnap();
	//}}AFX_MSG
	afx_msg LRESULT OnSetCurScreen(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowMenu(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT EventMsgPross(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ShowAlarmInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangePicSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT GetDevMsg(WPARAM wparm, LPARAM lparm);
	DECLARE_MESSAGE_MAP()

private:
	HI_BOOL m_bRecord[MAXCAM];
	HI_VOID *m_pScHandle;

public:
	void OnMenuCommand(UINT nID);
	void ShowCtlPage(int nPageIndex);
	void ShowConfigPage(int nPageIndex);
	void SetCtlPos();
	void ShowWindowCtl(HI_S32 s32Page);
	void UpdataLoginInfo(HI_U32 u32Chn);
	void LoginOut(HI_U32 u32Chn);
	void UpdateCotrl(HI_U32 u32Chn);
	void EnableCtrl(HI_U32 u32Chn);
	void GetVideoInfo(HI_U32 u32Chn);
	void SetAlarmInfo(HI_HANDLE lHandle, HI_U32 u32Len, MD_TYPE_E eDataType);
	HI_S32 ShowEditAlarm(HI_S32 u32Chn);
	HI_S32 HideEditAlarm(HI_S32 u32Chn);
	HI_S32 SetDrawPic(HI_HANDLE lHandle, EVENT_TYPE_E eDraw);
	void ProcessVideoScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	HI_S32 UpdateDrawData(HI_HANDLE lHandle, RECT rcDrawRect, CString csDrawName);
	void DrawAlarmInfo(HI_U32 u32Chn, MD_TYPE_E eDataType, HI_U8*  pu8Buffer, HI_U32 u32Length);
	static HRESULT HISDK_APICALL OnEventCallBack(
					HI_U32 u32Chn,
					EVENT_TYPE_E eEventType,
					HI_VOID* pEventData, 
					HI_S32 s32DataNum, 
					HI_VOID* pUserData);
	static HRESULT HISDK_APICALL OnMessageCallBack(
					HI_U32 u32Chn,
					MD_TYPE_E eDataType,
					HI_U8*  pu8Buffer,
					HI_U32 u32Length,
					HI_VOID* pUserData);
	static HRESULT HISDK_APICALL OnVoiceDataCallBack(
					HI_U32 u32Chn,
					HI_U8*  pu8Buf,
					HI_S32 s32Len,
					HI_U32 u32Pts,
					HI_VOID* pUserData);
	static HRESULT HISDK_APICALL OnDecCallBack(
					HI_U32 u32Chn,
					const FRAME_INFO_S *pFrameInfo,
					HI_VOID *pUserData);
	static LONG HISDK_APICALL OnDrawCallBack(
					HI_U32 u32Chn, 
					RECT rcDrawRect,
					HI_CHAR* pszName, 
					HI_VOID *pUserData);

public:
	void GetIpArray(char ipA[][HI_VSCP_IP_STRSIZE + 1], int &num);
	HI_S32 StopPlay(HI_HANDLE lHandle);
	HI_S32 Logout(HI_HANDLE lHandle);
	bool IsPublicIP(HI_CHAR *strIp);
	HI_S32 CouterBufNumber(HI_VEDIO_INFO m_sCamInfo);
	HI_U32  m_u32CurScr;
	HI_VEDIO_INFO m_sCamInfo[MAXCAM];
	HI_S_MD_PARAM m_mdParam[MAXCAM][MAX_MD_NUMBER];

public:
	CScreenPannel m_ScreenPannel;
	int m_nCurScreen;
	int m_nPage;
	int m_nMaxFrame;
	HI_S32 m_s32TalkOSD;
	ALARM_INFO_S m_alarmInfo;
	IP_INFO_S m_IpInfo[100];
	
	CRect m_PannelRect;
	HI_CHAR m_sPath[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDKDEMODLG_H__76909D30_7B97_4138_B923_BB888BCFFEC1__INCLUDED_)
