#if !defined(AFX_PLAYBACKDLG_H__9B3BCBB1_80AA_40D6_905B_A32EF3BEEB05__INCLUDED_)
#define AFX_PLAYBACKDLG_H__9B3BCBB1_80AA_40D6_905B_A32EF3BEEB05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaybackDlg.h : header file

#include "PlayWnd.h"
//
typedef enum hiPB_TYPE_E
{
	PB_STATE_PLAY = 0,
	PB_STATE_STOP,
	PB_STATE_PAUSE,
	PB_STATE_BUTT
}PB_STATE_E;
/////////////////////////////////////////////////////////////////////////////
// CPlaybackDlg dialog

class CPlaybackDlg : public CDialog
{
// Construction
public:
	CPlaybackDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlaybackDlg)
	enum { IDD = IDD_PLAYBACK_DIALOG };
	CSliderCtrl	m_slideVolume;
	CComboBox	m_comboRate;
	CSliderCtrl	m_sliderPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaybackDlg)
	afx_msg void OnOpen();
	afx_msg void OnPlay();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStop();
	virtual void OnCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnFrame();
	afx_msg void OnBtnPhoto();
	afx_msg void OnSelchangeComboRate();
	afx_msg void OnBtnSetmute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HRESULT UpdataPlayPos();
	static HI_VOID PASCAL PlayFileThread(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2);
	HI_HANDLE m_lHandle;
	UINT m_TilerID_GetPos;
	UINT m_wAccuracy;
	CRITICAL_SECTION m_critSection;
	PB_STATE_E m_bPlayState;
	int m_nRate;
	AUDIO_MUTE_E m_eMute;
	int m_nVolume;
	CPlayWnd m_PlayWnd;

public:
	HI_VOID OpenSliderListener();
	HI_VOID CloseSliderListener();
	HI_VOID SetPlayState(EVENT_TYPE_E eEventType);
	static HRESULT HISDK_APICALL OnEventCallBack(
					HI_U32 u32Chn, 
					EVENT_TYPE_E eEventType,
					HI_VOID* pEventData, 
					HI_S32 s32DataNum, 
					HI_VOID* pUserData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKDLG_H__9B3BCBB1_80AA_40D6_905B_A32EF3BEEB05__INCLUDED_)
