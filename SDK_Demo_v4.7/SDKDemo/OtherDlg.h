#if !defined(AFX_OTHERDLG_H__4E987E14_D5D6_4518_9307_E9E0B5BCC5A1__INCLUDED_)
#define AFX_OTHERDLG_H__4E987E14_D5D6_4518_9307_E9E0B5BCC5A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherDlg dialog

class COtherDlg : public CDialog
{
// Construction
public:
	COtherDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COtherDlg)
	enum { IDD = IDD_OTHER_DLG };
	CComboBox	m_WhiteBalance;
	CComboBox	m_combNightVision;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnReboot();
	afx_msg void OnBtnReset();
	afx_msg void OnBtnSetdisp();
	afx_msg void OnBtnNight();
	afx_msg void OnCheckMirror();
	afx_msg void OnCheckFlip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetHandle(long lHandle, HI_S_SUPPORT *pSupport);
	
private:
	HI_HANDLE m_lHandle;
	HI_S_SUPPORT m_sSupport;
	HI_S_Display_Ext m_DisplayExt;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERDLG_H__4E987E14_D5D6_4518_9307_E9E0B5BCC5A1__INCLUDED_)
