#if !defined(AFX_TIMEDLG_H__E7A3A34B_327E_420D_A668_A16420450769__INCLUDED_)
#define AFX_TIMEDLG_H__E7A3A34B_327E_420D_A668_A16420450769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

class CTimeDlg : public CDialog
{
// Construction
public:
	CTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeDlg)
	enum { IDD = IDD_TIME_DIALOG };
	CComboBox	m_comboZone;
	CDateTimeCtrl	m_dtTime;
	CDateTimeCtrl	m_dtDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSync();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	long m_lHandle;

public:
	void SetHandle(long lHandle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__E7A3A34B_327E_420D_A668_A16420450769__INCLUDED_)
