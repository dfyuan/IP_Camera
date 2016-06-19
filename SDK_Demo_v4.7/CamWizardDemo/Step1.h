#if !defined(AFX_STEP1_H__3DA84FC9_258F_11D6_9DF5_50D757C10000__INCLUDED_)
#define AFX_STEP1_H__3DA84FC9_258F_11D6_9DF5_50D757C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStep1 dialog

class CStep1 : public CDialog
{
// Construction
public:
	CStep1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStep1)
	enum { IDD = IDD_STEP1 };
	CComboBox	m_ctrLangugeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStep1)
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP1_H__3DA84FC9_258F_11D6_9DF5_50D757C10000__INCLUDED_)
