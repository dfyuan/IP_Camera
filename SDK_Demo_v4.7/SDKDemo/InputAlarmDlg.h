#if !defined(AFX_INPUTALARMDLG_H__AE0DFD86_7A92_4654_A04C_63999B15DD57__INCLUDED_)
#define AFX_INPUTALARMDLG_H__AE0DFD86_7A92_4654_A04C_63999B15DD57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputAlarmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputAlarmDlg dialog

class CInputAlarmDlg : public CDialog
{
// Construction
public:
	CInputAlarmDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputAlarmDlg)
	enum { IDD = IDD_INPUT_DLG };
	CComboBox	m_combEAM;
	CComboBox	m_combEA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputAlarmDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetHandle(long lHandle);
	
private:
	HI_HANDLE m_lHandle;
	HI_S_ATTR_EXT sAttrExt;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTALARMDLG_H__AE0DFD86_7A92_4654_A04C_63999B15DD57__INCLUDED_)
