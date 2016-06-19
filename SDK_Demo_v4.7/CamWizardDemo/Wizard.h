#if !defined(AFX_WIZARD_H__1778A141_2519_11D6_9DF5_70D757C10000__INCLUDED_)
#define AFX_WIZARD_H__1778A141_2519_11D6_9DF5_70D757C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizard dialog
#include "hi_vscp_devs_cli.h"

CString GetPcAddress(int &ipNum);

class CWizard : public CDialog
{
// Construction
public:

// Dialog Data
	//{{AFX_DATA(CWizard)
	enum { IDD = IDD_WIZARD };
	CButton	m_btnNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void GetIpArray(char ipA[][HI_VSCP_IP_STRSIZE + 1], int &num);

    CWizard(CWnd* pParent = NULL);   // standard constructor
    
    //Set net handle 
    HANDLE SetHandle();
    
    //Set wizard button of back,next,cancel
    void SetWizButton(UINT uFlag);
    
    //Show ervery child page
    void ShowPage(UINT nPos);
    
    //Add a new child page to parent
    void AddPage(CDialog* pDialog, UINT nID);
    
    //The range of child page
    CRect m_rectPage;    
    
    //All child page number
    UINT m_iPageCount; 
    
    //The index of current chile page
    UINT m_iCurrentPage; 
    
    //The device information of which be selected
    HI_S_VSCP_DEVINFO m_struSeletedDevinfo;

	//User info
	CString m_strUsername;
	CString m_strUserpwd;

	int m_iIfMem;


protected:

    //Struct to store child page pointer
	typedef struct PAGELINK
    {
		UINT nNum;
		CDialog* pDialog;
		struct PAGELINK* Next;
	};

    //Pages link header 
	PAGELINK* m_pPageLink; //用来链接所有的页

    HICON m_hIcon;

private:
    
    //Release net
    int ReleaseNet();
    
    //Initialize net
    int InitNet();
    
    //Net handle
    HANDLE m_pvHandle;

protected:

	// Generated message map functions
	//{{AFX_MSG(CWizard)
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnFinish();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARD_H__1778A141_2519_11D6_9DF5_70D757C10000__INCLUDED_)
