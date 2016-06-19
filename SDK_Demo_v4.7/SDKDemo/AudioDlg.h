#if !defined(AFX_AUDIODLG_H__8B0711A4_0E77_4AF3_A157_71A2AB1F34C2__INCLUDED_)
#define AFX_AUDIODLG_H__8B0711A4_0E77_4AF3_A157_71A2AB1F34C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg dialog

class CAudioDlg : public CDialog
{
// Construction
public:
	CAudioDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAudioDlg)
	enum { IDD = IDD_AUDIO_DLG };
	CComboBox	m_combStream;
	CComboBox	m_combAuSwitch;
	CComboBox	m_combFormat;
	CComboBox   m_combInput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetaudio();
	afx_msg void OnSelchangeComboStream();
	afx_msg void OnBtnSetinput();
	afx_msg void OnBtnSetoutput();
	afx_msg void OnBtnSetinputmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetHandle(long lHandle, HI_CHAR *psProduct);
	
private:
	BOOL CheckData();
	HI_HANDLE m_lHandle;
	HI_CHAR m_sProduct[64];
	HI_S_Audio_Ext m_sAudioInfo[3];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIODLG_H__8B0711A4_0E77_4AF3_A157_71A2AB1F34C2__INCLUDED_)
