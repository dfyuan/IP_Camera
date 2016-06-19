#if !defined(AFX_PTZDLG_H__69F0439E_4F4C_4FD3_A73E_6D589984941C__INCLUDED_)
#define AFX_PTZDLG_H__69F0439E_4F4C_4FD3_A73E_6D589984941C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PtzDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPtzDlg dialog

class CPtzDlg : public CDialog
{
// Construction
public:
	CPtzDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPtzDlg)
	enum { IDD = IDD_PTZ_DLG };
	CComboBox	m_combParity;
	CComboBox	m_combStopBit;
	CComboBox	m_combDataBit;
	CComboBox	m_combBaud;
	CComboBox	m_combProtocol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtzDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPtzDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetHandle(long lHandle);
	
private:
	BOOL CheckData();
	HI_HANDLE m_lHandle;
	HI_S_NET_EXT m_sNetInfo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZDLG_H__69F0439E_4F4C_4FD3_A73E_6D589984941C__INCLUDED_)
