// NetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "NetDlg.h"
#include "SDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog


CNetDlg::CNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetDlg)
	DDX_Control(pDX, IDC_DNSMODE_COMBO, m_comboDns);
	DDX_Control(pDX, IDC_DHCP_COMBO, m_comboDHCP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetDlg, CDialog)
	//{{AFX_MSG_MAP(CNetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetDlg message handlers

BOOL CNetDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();

	m_comboDHCP.InsertString(0, ConvertString("DHCP Manual"));
	m_comboDHCP.InsertString(1, ConvertString("DHCP Auto"));
	m_comboDHCP.SetCurSel(0);
	
	m_comboDns.InsertString(0, ConvertString("DNS Manual"));
	m_comboDns.InsertString(1, ConvertString("DNS Auto"));
	m_comboDns.SetCurSel(0);

	HI_S32 s32Ret = 0;
	memset((void*)&m_sNetInfo, 0, sizeof(HI_S_NET_EXT));
	
	if(m_lHandle == 0)
		return TRUE;

	s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_NET_EXT, &m_sNetInfo, sizeof(HI_S_NET_EXT));
	if(s32Ret != HI_SUCCESS)
	{
		MessageBox(ConvertString("Read network settings failed!"));
		return TRUE;
	}

	CString str;
	m_comboDHCP.SetCurSel(m_sNetInfo.sNetInfo.s32DhcpFlag);
	m_comboDns.SetCurSel(m_sNetInfo.sNetInfo.s32DnsDynFlag);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszServerIP);
	SetDlgItemText(IDC_IP_IPADDRESS, str);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszNetMask);
	SetDlgItemText(IDC_SUBNET_IPADDRESS, str);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszGateWay);
	SetDlgItemText(IDC_GATEWAY_IPADDRESS, str);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszMacAddr);
	SetDlgItemText(IDC_MAC_EDIT, str);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszFDNSIP);
	SetDlgItemText(IDC_PDNS_IPADDRESS, str);
	
	str.Format("%s",m_sNetInfo.sNetInfo.aszSDNSIP);
	SetDlgItemText(IDC_SDNS_IPADDRESS, str);

	str.Format("%d", m_sNetInfo.sHttpPort.u32HttpPort);
	SetDlgItemText(IDC_HTTP_PORT_EDIT, str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}

void CNetDlg::OnOK() 
{
	CString strBuf;
	CString strHost = "";
	HI_S32 s32Ret = HI_FAILURE;
	HI_S32 s32Port = 80;
	bool bPortChange = FALSE;
	if(0 == m_lHandle)
	{
		return;
	}
	
	BOOL bCheck = TRUE;
	bCheck = CheckData();
	if (!bCheck)
	{
		return;
	}

	GetDlgItemText(IDC_HTTP_PORT_EDIT, strBuf);
	s32Port = atoi(strBuf);
	if((s32Port < 80)||(s32Port > 65535))
	{
		MessageBox(ConvertString("HTTP port error! Must be between 80 and 65535."));
		return;
	}

	//Network settings
	HI_S_NET_EXT sNetInfo;
	memcpy((void*)&sNetInfo, (void*)&m_sNetInfo, sizeof(HI_S_NET_EXT));
	sNetInfo.sHttpPort.u32HttpPort = s32Port;
	if (0 == m_comboDHCP.GetCurSel())
		sNetInfo.sNetInfo.s32DhcpFlag = HI_FALSE;
	else
		sNetInfo.sNetInfo.s32DhcpFlag = HI_TRUE;
	
	if (0 == m_comboDns.GetCurSel())
		sNetInfo.sNetInfo.s32DnsDynFlag = HI_FALSE;
	else
		sNetInfo.sNetInfo.s32DnsDynFlag = HI_TRUE;
	
	GetDlgItem(IDC_IP_IPADDRESS)->GetWindowText(strHost);
	strcpy(sNetInfo.sNetInfo.aszServerIP, strHost);
	
	GetDlgItem(IDC_SUBNET_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.sNetInfo.aszNetMask,strBuf);
	
	GetDlgItem(IDC_GATEWAY_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.sNetInfo.aszGateWay,strBuf);
	
	GetDlgItem(IDC_PDNS_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.sNetInfo.aszFDNSIP,strBuf);
	
	GetDlgItem(IDC_SDNS_IPADDRESS)->GetWindowText(strBuf);
	if (0 != strcmp(strBuf,"0.0.0.0"))	strcpy(sNetInfo.sNetInfo.aszSDNSIP, strBuf);
	
	CSDKDemoDlg *dlg = (CSDKDemoDlg*)GetParent();
	if(0 != memcmp((void*)&m_sNetInfo,(void*)&sNetInfo,sizeof(HI_S_NET_EXT)))
	{
		//s32Ret = dlg->StopPlay(m_lHandle);
		//if(HI_SUCCESS != s32Ret)
		//{
		//	MessageBox(ConvertString("Setting Network Failure!"));
		//	return;
		//}
		
		s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_NET_EXT, &sNetInfo, sizeof(HI_S_NET_EXT));
		if(HI_SUCCESS == s32Ret)
		{
			memcpy(&m_sNetInfo, &sNetInfo, sizeof(HI_S_HTTPPORT));
			MessageBox(ConvertString("Setting Network Succeed!"));
		}
		else
		{
			MessageBox(ConvertString("Setting Network Failure!"));
		}

		dlg->Logout(m_lHandle);
		m_lHandle = 0;
		CDialog::OnCancel();
	}

	/*HI_S_NETINFO sNetInfo;
	memcpy((void*)&sNetInfo, (void*)&m_sNetInfo, sizeof(HI_S_NETINFO));
	if (0 == m_comboDHCP.GetCurSel())
		sNetInfo.s32DhcpFlag = HI_FALSE;
	else
		sNetInfo.s32DhcpFlag = HI_TRUE;
	
	if (0 == m_comboDns.GetCurSel())
		sNetInfo.s32DnsDynFlag = HI_FALSE;
	else
		sNetInfo.s32DnsDynFlag = HI_TRUE;
	
	GetDlgItem(IDC_IP_IPADDRESS)->GetWindowText(strHost);
	strcpy(sNetInfo.aszServerIP, strHost);
	
	GetDlgItem(IDC_SUBNET_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.aszNetMask,strBuf);
	
	GetDlgItem(IDC_GATEWAY_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.aszGateWay,strBuf);
	
	GetDlgItem(IDC_PDNS_IPADDRESS)->GetWindowText(strBuf);
	strcpy(sNetInfo.aszFDNSIP,strBuf);
	
	GetDlgItem(IDC_SDNS_IPADDRESS)->GetWindowText(strBuf);
	if (0 != strcmp(strBuf,"0.0.0.0"))	strcpy(sNetInfo.aszSDNSIP, strBuf);
	
	CSDKDemoDlg *dlg = (CSDKDemoDlg*)GetParent();
	if(0 != memcmp((void*)&m_sNetInfo,(void*)&sNetInfo,sizeof(HI_S_NETINFO)))
	{
		//s32Ret = dlg->StopPlay(m_lHandle);
		//if(HI_SUCCESS != s32Ret)
		//{
		//	MessageBox(ConvertString("Setting Network Failure!"));
		//	return;
		//}
		
		s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_NET_INFO, &sNetInfo, sizeof(HI_S_NETINFO));
		if(HI_SUCCESS == s32Ret)
		{
			//memcpy(&m_sNetInfo, &sNetInfo, sizeof(HI_S_HTTPPORT));
			MessageBox(ConvertString("Setting Network Succeed!"));
		}
		else
		{
			MessageBox(ConvertString("Setting Network Failure!"));
		}
		
		dlg->Logout(m_lHandle);
		m_lHandle = 0;
		CDialog::OnCancel();
	}*/
}

BOOL CNetDlg::CheckData()
{
	CString strBuf;
	UpdateData(TRUE);
	
	GetDlgItem(IDC_IP_IPADDRESS)->GetWindowText(strBuf);
	if(strBuf.IsEmpty() || 0 == strcmp(strBuf,"0.0.0.0"))
	{
		MessageBox(ConvertString("The IP Address is invalid!"));
		return FALSE;
	}
	
	GetDlgItem(IDC_SUBNET_IPADDRESS)->GetWindowText(strBuf);
	if(strBuf.IsEmpty() || 0 == strcmp(strBuf,"0.0.0.0"))
	{
		MessageBox(ConvertString("The subnetwork is invalid!"));
		return FALSE;
	}
	
	GetDlgItem(IDC_GATEWAY_IPADDRESS)->GetWindowText(strBuf);
	if(strBuf.IsEmpty() || 0 == strcmp(strBuf,"0.0.0.0"))
	{
		MessageBox(ConvertString("The gateway is invalid!"));
		return FALSE;
	}
	
	GetDlgItem(IDC_PDNS_IPADDRESS)->GetWindowText(strBuf);
	if(strBuf.IsEmpty() || 0 == strcmp(strBuf,"0.0.0.0"))
	{
		MessageBox(ConvertString("The Primary DNS is invalid!"));
		return FALSE;
	}
	
	//GetDlgItem(IDC_SDNS_IPADDRESS)->GetWindowText(strBuf);
	//if(strBuf.IsEmpty() && 0 == strcmp(strBuf,"0.0.0.0"))
	//{
	//	MessageBox(ConvertString("The Second DNS is invalid!"));
	//	return FALSE;
	//}
	
	return TRUE;
}
