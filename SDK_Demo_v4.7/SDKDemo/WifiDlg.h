#if !defined(AFX_WIFIDLG_H__62BF36D3_BFBE_42C6_8406_59E3D734C5B1__INCLUDED_)
#define AFX_WIFIDLG_H__62BF36D3_BFBE_42C6_8406_59E3D734C5B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WifiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWifiDlg dialog

class CWifiDlg : public CDialog
{
// Construction
public:
	CWifiDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWifiDlg)
	enum { IDD = IDD_WIFI_DLG };
	CProgressCtrl	m_ProgressS;
	CProgressCtrl	m_ProgressC;
	CComboBox	m_combMode;
	CComboBox	m_combEnc;
	CComboBox	m_combAuth;
	CListCtrl	m_listWifi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWifiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWifiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearch();
	afx_msg void OnCheckEnable();
	virtual void OnOK();
	afx_msg void OnClickListWifi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnCheck();
	afx_msg void OnSelchangeComboAuth();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	long m_lHandle;
	int m_nPos;
	int m_nProgress; //0-search, 1-check
	HANDLE m_hThreadHandle;
	HI_S_WIFI_INFO m_sWifiInfo;

private:
	void EnableContrl();
	void SetEnableCtrl(bool bEnable);
	int GetWifiParam(HI_S_WIFI_PARAM *psWifiParam);
	
public:
	void SetHandle(long lHandle);
	void SearchPross();
	void CheckPross();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIFIDLG_H__62BF36D3_BFBE_42C6_8406_59E3D734C5B1__INCLUDED_)
