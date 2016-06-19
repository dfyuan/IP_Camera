#if !defined(AFX_OSDDLG_H__278033C5_7C8B_4C64_AEA9_81D494B02DC9__INCLUDED_)
#define AFX_OSDDLG_H__278033C5_7C8B_4C64_AEA9_81D494B02DC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OsdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COsdDlg dialog

class COsdDlg : public CDialog
{
// Construction
public:
	COsdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COsdDlg)
	enum { IDD = IDD_OSD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COsdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COsdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetosd();
	afx_msg void OnCheckNameosd();
	afx_msg void OnCheckTimeosd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	long m_lHandle;
	HI_S_OSD m_sOsdInfo;
	
public:
	void SetHandle(long lHandle);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDDLG_H__278033C5_7C8B_4C64_AEA9_81D494B02DC9__INCLUDED_)
