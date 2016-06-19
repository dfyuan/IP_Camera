#if !defined(AFX_STEP2_H__D712A101_E87A_4898_B6C3_B4715E177CEC__INCLUDED_)
#define AFX_STEP2_H__D712A101_E87A_4898_B6C3_B4715E177CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step2.h : header file
//

#include <vector>
#include "hi_vscp_devs_cli.h"

/////////////////////////////////////////////////////////////////////////////
// CStep2 dialog

class CStep2 : public CDialog
{
// Construction
public:

// Dialog Data
	//{{AFX_DATA(CStep2)
	enum { IDD = IDD_STEP2 };
	CIPAddressCtrl	m_ctrIpAddress;
	CListCtrl	m_ctrDevList;
	//}}AFX_DATA

    CStep2(CWnd* pParent = NULL);   // standard constructor

public:
	void GetNetHandle(HANDLE hand);

	static int SEARCH_APICALL CallBackSearch(const HI_VOID* pvHandle,HI_CHAR* pszRNPCode,
		HI_S_VSCP_DEVINFO* pstruDevInfo,HI_VOID* pvUserData);

	LRESULT GetDevMsg(WPARAM wparm, LPARAM lparm);

    //Insert a device information to list
    void InsertData(HI_S_VSCP_DEVINFO &devInfo);
    
    //Index of the current device
    int m_iCurSelection;

private:
    //Object of search device
	//Device list
    std::vector<HI_S_VSCP_DEVINFO> m_aDevList;  

	HANDLE m_pHandle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStep2)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRefresh();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP2_H__D712A101_E87A_4898_B6C3_B4715E177CEC__INCLUDED_)
