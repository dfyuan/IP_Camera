#if !defined(AFX_NETDLG_H__57D7AE66_B48F_47E7_B0A9_6BC92CCC9E3D__INCLUDED_)
#define AFX_NETDLG_H__57D7AE66_B48F_47E7_B0A9_6BC92CCC9E3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog

class CNetDlg : public CDialog
{
// Construction
public:
	CNetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetDlg)
	enum { IDD = IDD_NET_DLG };
	CComboBox	m_comboDns;
	CComboBox	m_comboDHCP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetDlg)
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

#endif // !defined(AFX_NETDLG_H__57D7AE66_B48F_47E7_B0A9_6BC92CCC9E3D__INCLUDED_)
