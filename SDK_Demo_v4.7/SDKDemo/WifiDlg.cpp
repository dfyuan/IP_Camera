// WifiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "WifiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWifiDlg dialog

DWORD WINAPI SearchThread(LPVOID pParam)
{
	CWifiDlg *dlg = (CWifiDlg*)pParam;
	dlg->SearchPross();
	return 0;
}

DWORD WINAPI CheckThread(LPVOID pParam)
{
	CWifiDlg *dlg = (CWifiDlg*)pParam;
	dlg->CheckPross();
	return 0;
}


CWifiDlg::CWifiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWifiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWifiDlg)
	m_lHandle = 0;
	m_nPos = 0;
	m_nProgress = 0;
	m_hThreadHandle = NULL;
	//}}AFX_DATA_INIT
}


void CWifiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWifiDlg)
	DDX_Control(pDX, IDC_PROGRESS_S, m_ProgressS);
	DDX_Control(pDX, IDC_PROGRESS_C, m_ProgressC);
	DDX_Control(pDX, IDC_COMBO_MODE, m_combMode);
	DDX_Control(pDX, IDC_COMBO_ENC, m_combEnc);
	DDX_Control(pDX, IDC_COMBO_AUTH, m_combAuth);
	DDX_Control(pDX, IDC_LIST_WIFI, m_listWifi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWifiDlg, CDialog)
	//{{AFX_MSG_MAP(CWifiDlg)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_NOTIFY(NM_CLICK, IDC_LIST_WIFI, OnClickListWifi)
	ON_BN_CLICKED(IDC_BTN_CHECK, OnBtnCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTH, OnSelchangeComboAuth)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWifiDlg message handlers

BOOL CWifiDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	m_listWifi.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_listWifi.InsertColumn(0, _T("RSSI"), LVCFMT_CENTER, 40);
    m_listWifi.InsertColumn(1, _T("SSID"), LVCFMT_CENTER, 115);
    m_listWifi.InsertColumn(2, ConvertString("WPA Algorithm"), LVCFMT_CENTER, 60);
    m_listWifi.InsertColumn(3, ConvertString("Securty Mode"), LVCFMT_CENTER, 60);
	m_listWifi.InsertColumn(4, ConvertString("Wifi Mode"), LVCFMT_CENTER, 60);
	m_listWifi.InsertColumn(5, ConvertString("Channel"), LVCFMT_CENTER, 60);

	m_combAuth.InsertString(0, ConvertString("None"));
	m_combAuth.InsertString(1, "WEP");
	m_combAuth.InsertString(2, "WPA-PSK");
	m_combAuth.InsertString(3, "WPA2-PSK");
	m_combAuth.SetCurSel(0);

	m_combEnc.InsertString(0, "TKIP");
	m_combEnc.InsertString(1, "AES");
	m_combEnc.SetCurSel(0);

	m_combMode.InsertString(0, ConvertString("Infrastructure"));
	m_combMode.InsertString(1, ConvertString("Point To Point"));
	m_combMode.SetCurSel(0);

	//SetDlgItemText(IDC_EDIT_SSID, "SSID");
	//SetDlgItemText(IDC_EDIT_KEY, "admin");
	//SetDlgItemText(IDC_EDIT_KEYCK, "admin");
	m_ProgressS.SetRange(0, 100);
	m_ProgressC.SetRange(0, 100);

	memset(&m_sWifiInfo, 0, sizeof(HI_S_WIFI_INFO));
	HI_S32 s32Ret = HI_FAILURE;
	CString strBuf = "";
	HI_S_WIFI_PARAM sWfParam;
	
	if(m_lHandle != 0)
	{
		s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_WIFI_PARAM, &sWfParam, sizeof(HI_S_WIFI_PARAM));
		if(s32Ret == HI_SUCCESS)
		{
			if(sWfParam.u32Enable == 1)
			{
				((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->SetCheck(TRUE);
				GetDlgItem(IDC_EDIT_SSID)->EnableWindow(TRUE);
				GetDlgItem(IDC_COMBO_MODE)->EnableWindow(TRUE);
				GetDlgItem(IDC_COMBO_AUTH)->EnableWindow(TRUE);
				GetDlgItem(IDC_LIST_WIFI)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_CHECK)->EnableWindow(TRUE);

				SetDlgItemText(IDC_EDIT_SSID, sWfParam.sSsID);
				SetDlgItemText(IDC_EDIT_KEY, sWfParam.sKey);
				SetDlgItemText(IDC_EDIT_KEYCK, sWfParam.sKey);
				m_combAuth.SetCurSel(sWfParam.u32Auth);
				m_combEnc.SetCurSel(sWfParam.u32Enc);
				m_combMode.SetCurSel(sWfParam.u32Mode);
				EnableContrl();
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWifiDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}

void CWifiDlg::OnBtnSearch() 
{
	if(m_lHandle == 0)
		return;

	if(m_hThreadHandle != NULL)
	{
		WaitForSingleObject(m_hThreadHandle, INFINITE);
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}

	m_hThreadHandle = CreateThread(NULL, 0, SearchThread, this, 0, NULL);
}

void CWifiDlg::OnCheckEnable() 
{
	if(((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT_SSID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_AUTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_WIFI)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CHECK)->EnableWindow(TRUE);
		EnableContrl();
	}
	else
	{
		GetDlgItem(IDC_EDIT_SSID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_AUTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ENC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_KEYCK)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_WIFI)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CHECK)->EnableWindow(FALSE);
	}
}

void CWifiDlg::OnOK() 
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_S_WIFI_PARAM sWfParam;
	s32Ret = GetWifiParam(&sWfParam);
	if(s32Ret != HI_SUCCESS)
		return;

	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_WIFI_PARAM, &sWfParam, sizeof(HI_S_WIFI_PARAM));
	if(s32Ret != HI_SUCCESS)
		MessageBox(ConvertString("Setting Failure!"));
	else
		MessageBox(ConvertString("Setting Success!"));
}

void CWifiDlg::OnClickListWifi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int index = m_listWifi.GetSelectionMark();
	if(index < 0 || index >= MAX_WFPT)
		return;

	SetDlgItemText(IDC_EDIT_SSID, m_sWifiInfo.sWfPt[index].sEssID);
	m_combEnc.SetCurSel(m_sWifiInfo.sWfPt[index].u32Enc);
	m_combAuth.SetCurSel(m_sWifiInfo.sWfPt[index].u32Auth);
	m_combMode.SetCurSel(m_sWifiInfo.sWfPt[index].u32Net);
	EnableContrl();
	
	*pResult = 0;
}

void CWifiDlg::OnBtnCheck() 
{
	if(m_lHandle == 0)
		return;
	
	if(m_hThreadHandle != NULL)
	{
		WaitForSingleObject(m_hThreadHandle, INFINITE);
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}
	
	m_hThreadHandle = CreateThread(NULL, 0, CheckThread, this, 0, NULL);
}


void CWifiDlg::EnableContrl()
{
	int nType = m_combAuth.GetCurSel();
	
	if(nType == WIFI_AUTH_NONE)
	{
		GetDlgItem(IDC_COMBO_ENC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_KEYCK)->EnableWindow(FALSE);
	}
	else if(nType == WIFI_AUTH_WEP)
	{
		GetDlgItem(IDC_COMBO_ENC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_KEYCK)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_ENC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_KEYCK)->EnableWindow(TRUE);
	}
}

void CWifiDlg::OnSelchangeComboAuth() 
{
	EnableContrl();
}

int CWifiDlg::GetWifiParam(HI_S_WIFI_PARAM *psWifiParam)
{
	if(m_lHandle == 0)
		return HI_FAILURE;
	
	memset(psWifiParam, 0, sizeof(HI_S_WIFI_PARAM));
	HI_S32 s32Ret = HI_FAILURE;
	CString strSsid = "";
	CString strKey = "";
	CString strKeyCk = "";
	int nEnable = ((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->GetCheck();
	
	GetDlgItemText(IDC_EDIT_SSID, strSsid);
	if(strSsid == "")
	{
		MessageBox(ConvertString("SSID can't for empty!"));
		return HI_FAILURE;
	}
	
	GetDlgItemText(IDC_EDIT_KEY, strKey);
	GetDlgItemText(IDC_EDIT_KEYCK, strKeyCk);
	if(strKey != strKeyCk)
	{
		MessageBox(ConvertString("Two input keys inconsistency!"));
		return HI_FAILURE;
	}
	
	if(nEnable == 1)
	{
		psWifiParam->u32Enable = nEnable;
		strcpy(psWifiParam->sSsID, strSsid.GetBuffer(0));
		strcpy(psWifiParam->sKey, strKey.GetBuffer(0));
		psWifiParam->u32Auth = m_combAuth.GetCurSel();
		psWifiParam->u32Enc = m_combEnc.GetCurSel();
		psWifiParam->u32Mode = m_combMode.GetCurSel();

		if(psWifiParam->u32Auth != WIFI_AUTH_NONE)
		{
			if(strKey == "")
			{
				MessageBox(ConvertString("Please enter the key!"));
				return HI_FAILURE;
			}
		}
	}

	return HI_SUCCESS;
}


void CWifiDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		m_nPos++;
		int nPos = m_nPos*100/60;
		if(m_nProgress == 0)
		{
			m_ProgressS.SetPos(nPos);
		}
		else
		{
			m_ProgressC.SetPos(nPos);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CWifiDlg::SearchPross()
{
	if(m_lHandle == 0)
		return;
	
	HI_S32 s32Ret = HI_FAILURE;
	HI_S_WIFI_INFO sWifiInfo;
	
	CString strBuf = "";
	
	memset(&sWifiInfo, 0, sizeof(HI_S_WIFI_INFO));
	memset(&m_sWifiInfo, 0, sizeof(HI_S_WIFI_INFO));
	m_nProgress = 0;
	SetEnableCtrl(FALSE);
	m_listWifi.DeleteAllItems();
	s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_WIFI_SEARCH, &sWifiInfo, sizeof(HI_S_WIFI_INFO));
	if(s32Ret != HI_SUCCESS)
	{
		SetEnableCtrl(TRUE);
		MessageBox(ConvertString("Search wifi failure!"));
		return;
	}
	//strBuf.Format("%d", sWifiInfo.s32Num);
	//MessageBox(strBuf);
	if(sWifiInfo.s32Num == 0)
	{
		SetEnableCtrl(TRUE);
		MessageBox(ConvertString("Search wifi failure!"));
		return;
	}
	
	for(HI_S32 i=0; i<sWifiInfo.s32Num; i++)
	{
		strBuf.Format("%d", sWifiInfo.sWfPt[i].s32Rssi);
		m_listWifi.InsertItem(i, strBuf);
		m_listWifi.SetItemText(i, 1, sWifiInfo.sWfPt[i].sEssID);
		if(sWifiInfo.sWfPt[i].u32Enc == 0)
			strBuf = "TKIP";
		else
			strBuf = "AES";
		m_listWifi.SetItemText(i, 2, strBuf);
		strBuf.Format("%d", sWifiInfo.sWfPt[i].u32Auth);
		if(sWifiInfo.sWfPt[i].u32Auth == 0)
			strBuf = ConvertString("None");
		else if(sWifiInfo.sWfPt[i].u32Auth == 1)
			strBuf = "WEP";
		else if(sWifiInfo.sWfPt[i].u32Auth == 2)
			strBuf = "WPA-PSK";
		else
			strBuf = "WPA2-PSK";
		m_listWifi.SetItemText(i, 3, strBuf);
		if(sWifiInfo.sWfPt[i].u32Net == 0)
			strBuf = ConvertString("Infrastructure");
		else
			strBuf = ConvertString("Point To Point");
		m_listWifi.SetItemText(i, 4, strBuf);
		strBuf.Format("%d", sWifiInfo.sWfPt[i].s32Chn);
		m_listWifi.SetItemText(i, 5, strBuf);
	}

	memcpy(&m_sWifiInfo, &sWifiInfo, sizeof(HI_S_WIFI_INFO));
	SetEnableCtrl(TRUE);
}

void CWifiDlg::CheckPross()
{
	HI_S32 s32Ret = HI_FAILURE;
	HI_S_WIFI_PARAM sWfParam;
	s32Ret = GetWifiParam(&sWfParam);
	if(s32Ret != HI_SUCCESS)
		return;
	
	m_nProgress = 1;
	SetEnableCtrl(FALSE);
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_WIFI_CHECK, &sWfParam, sizeof(HI_S_WIFI_PARAM));
	if(HI_SUCCESS != s32Ret)
	{
		SetEnableCtrl(TRUE);
		MessageBox(ConvertString("Set wifi cheak failure!"));
		return;
	}
	
	//Sleep(10);
	HI_S32 s32Enable = 0;
	s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_WIFI_CHECK, &s32Enable, sizeof(HI_S32));
	if(HI_SUCCESS != s32Ret)
	{
		SetEnableCtrl(TRUE);
		MessageBox(ConvertString("Obtain Info Failure!"));
		return;
	}
	
	SetEnableCtrl(TRUE);
	if(s32Enable == 1)
		MessageBox(ConvertString("Wifi check success!"));
	else
		MessageBox(ConvertString("Wifi check failure!"));
}

void CWifiDlg::SetEnableCtrl(bool bEnable)
{
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_CHECK)->EnableWindow(bEnable);
	GetDlgItem(IDOK)->EnableWindow(bEnable);
	GetDlgItem(IDCANCEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(bEnable);

	if(!bEnable)
	{
		m_nPos = 0;
		SetTimer(1, 500, NULL);
	}
	else
	{
		KillTimer(1);
		m_nPos = 0;
		m_ProgressS.SetPos(0);
		m_ProgressC.SetPos(0);
	}
}

void CWifiDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();

	if(m_hThreadHandle != NULL)
	{
		WaitForSingleObject(m_hThreadHandle, INFINITE);
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}
}
