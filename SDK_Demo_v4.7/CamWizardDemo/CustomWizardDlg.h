// CustomWizardDlg.h : header file
//

#if !defined(AFX_CUSTOMWIZARDDLG_H__2F8355D1_24C2_11D6_9DF5_70D757C10000__INCLUDED_)
#define AFX_CUSTOMWIZARDDLG_H__2F8355D1_24C2_11D6_9DF5_70D757C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCustomWizardDlg dialog

class CCustomWizardDlg : public CDialog
{
// Construction
public:
	CCustomWizardDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomWizardDlg)
	enum { IDD = IDD_CUSTOMWIZARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomWizardDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CCustomWizardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBeginwiz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMWIZARDDLG_H__2F8355D1_24C2_11D6_9DF5_70D757C10000__INCLUDED_)
