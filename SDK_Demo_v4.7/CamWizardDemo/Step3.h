#if !defined(AFX_STEP3_H__C57721E4_2BB5_4F8C_A079_E2DA343A3F8E__INCLUDED_)
#define AFX_STEP3_H__C57721E4_2BB5_4F8C_A079_E2DA343A3F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step3.h : header file
//
#include "hi_vscp_devs_cli.h"

/////////////////////////////////////////////////////////////////////////////
// CStep3 dialog

class CStep3 : public CDialog
{
// Construction
public:

// Dialog Data
	//{{AFX_DATA(CStep3)
	enum { IDD = IDD_STEP3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    CStep3(CWnd* pParent = NULL);   // standard constructor

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStep3)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnReset();
	afx_msg void OnModify();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCheckDhcp();
	afx_msg void OnModifyPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

    //Get net handle
    void GetHandle(HANDLE hdl);
    
    //Show device detail info 
    void ShowDevInfo();
    
    //Get local Ip
    CString GetLocalIp();
    
    //Callback function to set parameter to board
	static int SEARCH_APICALL CallBackSet(const HI_VOID* pvHandle, HI_CHAR* pszRNPCode, 
        HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo* pstruResponseInfo, HI_VOID* pvUserData);
    
    //User info
    HI_S_VSCP_DEVSCLI_DevInfo m_stuUserInfo;
    
    //The information of device which to set
    HI_S_VSCP_DEVINFO m_stuSetDevInfo;
    
    //If keep the user information to next
    int m_iIfRem;

private:

    //Set the device parameter

    //The handle of net
    HANDLE m_pvHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP3_H__C57721E4_2BB5_4F8C_A079_E2DA343A3F8E__INCLUDED_)
