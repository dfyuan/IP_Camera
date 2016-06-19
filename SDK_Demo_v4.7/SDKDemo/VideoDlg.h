#if !defined(AFX_VIDEODLG_H__414FFD80_024B_4015_9480_3721878DA344__INCLUDED_)
#define AFX_VIDEODLG_H__414FFD80_024B_4015_9480_3721878DA344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoDlg dialog

class CVideoDlg : public CDialog
{
// Construction
public:
	CVideoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoDlg)
	enum { IDD = IDD_VIDEO_DLG };
	CComboBox	m_combStream;
	CComboBox	m_combResolution;
	CComboBox	m_combFrequency;
	CComboBox	m_combLcbr;
	CComboBox	m_combFrameRate;
	CComboBox	m_combQuality;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetsize();
	afx_msg void OnBtnSetfq();
	afx_msg void OnBtnSetvideo();
	afx_msg void OnSelchangeComboStream();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HI_S_SUPPORT m_sSupport;
	void SetHandle(long lHandle, HI_CHAR *psProduct, HI_S_SUPPORT *pSupport);
	
private:
	BOOL CheckData();
	HI_HANDLE m_lHandle;
	HI_CHAR m_sProduct[64];
	HI_S_Video_Ext m_sVideo[3];
	HI_S32 m_nMaxFrame;
	HI_S_Resolution_Ext m_sResolutio[3];
	HI_U32 m_u32Frequency;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEODLG_H__414FFD80_024B_4015_9480_3721878DA344__INCLUDED_)
