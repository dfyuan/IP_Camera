#if !defined(AFX_CHECKUSER_H__5FF314C6_E6BB_4F70_A25B_1543F35E54AD__INCLUDED_)
#define AFX_CHECKUSER_H__5FF314C6_E6BB_4F70_A25B_1543F35E54AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckUser dialog

class CCheckUser : public CDialog
{
// Construction
public:
	CCheckUser(CWnd* pParent = NULL);   // standard constructor
    ~CCheckUser();

public:
	void GetMainFrame(HANDLE wnd);
    
    //Get the old account from parent
	void GetAccount(CString name, CString pwd, int rem);
    
    //Name
    CString m_strName;
    
    //Password
    CString m_strPwd;
    
    //If remember the name and password for next
    int m_iSelect;

// Dialog Data
	//{{AFX_DATA(CCheckUser)
	enum { IDD = IDD_CHECK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckUser)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKUSER_H__5FF314C6_E6BB_4F70_A25B_1543F35E54AD__INCLUDED_)
