#if !defined(AFX_STEP4_H__99B0441F_4D5E_4FA2_A0D8_0E81C498A1A4__INCLUDED_)
#define AFX_STEP4_H__99B0441F_4D5E_4FA2_A0D8_0E81C498A1A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStep4 dialog

class CStep4 : public CDialog
{
// Construction
public:
	CStep4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStep4)
	enum { IDD = IDD_STEP4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStep4)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP4_H__99B0441F_4D5E_4FA2_A0D8_0E81C498A1A4__INCLUDED_)
