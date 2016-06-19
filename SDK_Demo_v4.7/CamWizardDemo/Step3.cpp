// Step3.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWizard.h"
#include "Step3.h"
#include "hi_vscp_devs_cli.h"
#include "Wizard.h"
#include "CheckUser.h"
//#include "hi_authmng.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep3 dialog


CStep3::CStep3(CWnd* pParent /*=NULL*/)
	: CDialog(CStep3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStep3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep3, CDialog)
	//{{AFX_MSG_MAP(CStep3)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_DHCP, OnCheckDhcp)
	ON_BN_CLICKED(IDC_MODIFY_PORT, OnModifyPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep3 message handlers


CString CStep3::GetLocalIp()
{
    PHOSTENT hostinfo; 
    char name[255];
    char *ip;
    memset(name, 0, sizeof(name));
    
    gethostname(name, sizeof(name));
    if (name[0] == '\0')
    {
        return _T("0.0.0.0");
    }
    else
    {
        if ((hostinfo = gethostbyname(name))==NULL)
        {
            return _T("0.0.0.0");
        }
        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
    }
    
    return ip;
}

BOOL CStep3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Set static name
    GetDlgItem(IDC_TITLE1)->SetWindowText(_T("Device Information"));
    GetDlgItem(IDC_TITLE2)->SetWindowText(_T("Local IP"));
    GetDlgItem(IDC_TEXT)->SetWindowText(_T("Modify the device setting if you want.Input the new value and press \"Modify\"\
        button, or press \"Reset\" to resume the value."));
    
    GetDlgItem(IDC_RESET)->SetWindowText(_T("Reset"));
    GetDlgItem(IDC_MODIFY)->SetWindowText(_T("Modify"));

    GetDlgItem(IDC_T_NAME)->SetWindowText(_T("Name"));
    GetDlgItem(IDC_T_IP)->SetWindowText(_T("IP Address"));
    GetDlgItem(IDC_T_MASK)->SetWindowText(_T("SubMask"));
    GetDlgItem(IDC_T_GATEWAY)->SetWindowText(_T("Gateway"));
    GetDlgItem(IDC_T_MAC)->SetWindowText(_T("MAC"));
    GetDlgItem(IDC_T_TYPE)->SetWindowText(_T("Type"));
    GetDlgItem(IDC_T_SWVER)->SetWindowText(_T("Software Ver."));

    //
    CString str;
    str = GetLocalIp();
    GetDlgItem(IDC_LOCAL_IP)->SetWindowText(str);
    ((CEdit*)GetDlgItem(IDC_NAME))->SetLimitText(HI_VSCP_DEVNAME_STRSIZE-1);

    GetHandle(((CWizard*)GetParent())->SetHandle());
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStep3::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    ShowDevInfo();
}

void CStep3::OnReset() 
{
    ShowDevInfo();
}

void CStep3::ShowDevInfo()
{
    HI_S_VSCP_DEVINFO devInfo;
    devInfo = ((CWizard*)(AfxGetApp()->GetMainWnd()))->m_struSeletedDevinfo;
    
    GetDlgItem(IDC_NAME)->SetWindowText(devInfo.aszDevName);
    GetDlgItem(IDC_IP)->SetWindowText(devInfo.struNetInfo.aszIP);
    GetDlgItem(IDC_SUBMASK)->SetWindowText(devInfo.struNetInfo.aszMASK);
    GetDlgItem(IDC_MAC)->SetWindowText(devInfo.struNetInfo.aszMAC);
    GetDlgItem(IDC_GATEWAY)->SetWindowText(devInfo.struNetInfo.aszGTW);
    GetDlgItem(IDC_VER)->SetWindowText(devInfo.aszSwVersion);
    GetDlgItem(IDC_TYPE)->SetWindowText(devInfo.aszDevMDL);
	GetDlgItem(IDC_PORT)->SetWindowText(devInfo.aszHttpPort);
#if 1
	if (devInfo.struNetInfo.s32Dhcp)
	{
		((CButton *)GetDlgItem(IDC_CHECK_DHCP))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_IP))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_SUBMASK))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_GATEWAY))->EnableWindow(FALSE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_DHCP))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_IP))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_SUBMASK))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_GATEWAY))->EnableWindow(TRUE);
	}

	if (devInfo.struNetInfo.s32DnsFlag)
	{
		((CButton *)GetDlgItem(IDC_CHECK_DDNS))->SetCheck(TRUE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_CHECK_DDNS))->SetCheck(FALSE);
	}

    GetDlgItem(IDC_IP_FDNS)->SetWindowText(devInfo.struNetInfo.aszFdns);
    GetDlgItem(IDC_IP_SDNS)->SetWindowText(devInfo.struNetInfo.aszSdns);
#endif
}

void CStep3::OnModify() 
{
    HI_S_VSCP_DEVINFO devInfo;
    CString str;
	CString strCommand;
	int rt = HI_FAILURE;

	//用户验证
	CCheckUser dlg;
    dlg.GetAccount(((CWizard*)AfxGetMainWnd())->m_strUsername, ((CWizard*)AfxGetMainWnd())->m_strUserpwd, ((CWizard*)AfxGetMainWnd())->m_iIfMem);
    if (dlg.DoModal()==IDCANCEL)
    {
        return;
    }
	
    //
    GetDlgItem(IDC_INFO)->SetWindowText(_T("Now is modify the device setting, please waiting..."));
	
	HI_S_VSCP_DEVSCLI_DevInfo stuUser;
	stuUser.pszPasswd = ((CWizard*)AfxGetMainWnd())->m_strUserpwd.GetBuffer(0);
	stuUser.pszUserName = ((CWizard*)AfxGetMainWnd())->m_strUsername.GetBuffer(0);
	stuUser.pszDevID = ((CWizard*)AfxGetMainWnd())->m_struSeletedDevinfo.aszDevID;
    
	//获取修改值
    memset(&devInfo, 0, sizeof(HI_S_VSCP_DEVINFO));
    
    GetDlgItem(IDC_NAME)->GetWindowText(str);
    strncpy(devInfo.aszDevName, str.GetBuffer(0), HI_VSCP_DEVNAME_STRSIZE+1);
    // ip地址
    GetDlgItem(IDC_IP)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszIP, str.GetBuffer(0), HI_VSCP_IP_STRSIZE+1);
    // 子网掩码
    GetDlgItem(IDC_SUBMASK)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszMASK, str.GetBuffer(0), HI_VSCP_IP_STRSIZE+1);
    // 网关
    GetDlgItem(IDC_GATEWAY)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszGTW, str.GetBuffer(0), HI_VSCP_IP_STRSIZE+1);
        
	if (strcmp(devInfo.struNetInfo.aszIP, "") == 0 || strcmp(devInfo.struNetInfo.aszMASK, "") == 0)
    {
        GetDlgItem(IDC_INFO)->SetWindowText(_T("Error! Please input the right value"));
        return;
    }
	
	// fdns
	GetDlgItem(IDC_IP_FDNS)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszFdns, str.GetBuffer(0), HI_VSCP_IP_STRSIZE+1);
	
	// sdns
	GetDlgItem(IDC_IP_SDNS)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszSdns, str.GetBuffer(0), HI_VSCP_IP_STRSIZE+1);

    m_stuSetDevInfo = devInfo;

    GetDlgItem(IDC_INFO)->SetWindowText(_T(""));
    
	devInfo.struNetInfo.s32Dhcp = ((CButton *)GetDlgItem(IDC_CHECK_DHCP))->GetCheck()?1:0;
	devInfo.struNetInfo.s32DnsFlag = ((CButton *)GetDlgItem(IDC_CHECK_DDNS))->GetCheck()?1:0;

	//2014/03/26
	GetDlgItem(IDC_MAC)->GetWindowText(str);
    if (str == "0.0.0.0")
    {
        str = "";
    }
    strncpy(devInfo.struNetInfo.aszMAC, str.GetBuffer(0), HI_VSCP_MAC_STRSIZE+1);
	
	rt = HI_VSCP_DEVSCLI_Cmd(m_pvHandle, &stuUser, HI_VSCP_CMD_NET, &devInfo.struNetInfo);

    GetDlgItem(IDC_INFO)->SetWindowText(_T(""));








	/*HI_S32 s32Ret;
	HI_S_VSCP_NETINFO struNetInfo;
	HI_S_VSCP_DEVSCLI_DevInfo struDevInfo;
	
	if (m_pSchHandle != NULL)
	{
		UpdateData(TRUE);
		memset(&struNetInfo, 0, sizeof(HI_S_VSCP_NETINFO));
		memset(&struDevInfo, 0, sizeof(HI_S_VSCP_DEVSCLI_DevInfo));
		struDevInfo.pszDevID = m_strDevID.GetBuffer(0);
		struDevInfo.pszUserName = m_strUser.GetBuffer(0);
		struDevInfo.pszPasswd = m_strWord.GetBuffer(0);
		strcpy(struNetInfo.aszMAC, m_strMAC.GetBuffer(0));
		strcpy(struNetInfo.aszIP, m_strIP.GetBuffer(0));
		strcpy(struNetInfo.aszMASK, m_strMask.GetBuffer(0));
		strcpy(struNetInfo.aszGTW, m_strGateway.GetBuffer(0));
		strcpy(struNetInfo.aszFdns, m_strFdns.GetBuffer(0));
		strcpy(struNetInfo.aszSdns, m_strSdns.GetBuffer(0));
		if (m_iDhcp == 0)
			struNetInfo.s32Dhcp = 1;
		else struNetInfo.s32Dhcp = 0;
		if (this->m_iDns == 0)
			struNetInfo.s32DnsFlag = 1;
		else struNetInfo.s32DnsFlag = 0;
		
		s32Ret = HI_VSCP_DEVSCLI_Cmd(m_pSchHandle, &struDevInfo, HI_VSCP_CMD_NET, &struNetInfo);
		if (s32Ret == HI_SUCCESS)
		{
			MessageBox("Network setup success!");	
		}
		else
		{
			MessageBox("Network setup failure!");
		}
	}*/


	/*HI_S32 s32Ret;
	HI_CHAR pstrName[32];
	HI_S_VSCP_DEVSCLI_DevInfo struDevInfo;
	
	if (m_pSchHandle == NULL)
		return;
	
	memset(&struDevInfo, 0, sizeof(HI_S_VSCP_DEVSCLI_DevInfo));
	memset(pstrName, 0, 32);
	UpdateData(TRUE);
	struDevInfo.pszDevID = m_strDevID.GetBuffer(0);
	struDevInfo.pszUserName = m_strUser.GetBuffer(0);
	struDevInfo.pszPasswd = m_strWord.GetBuffer(0);
	
	strcpy(pstrName, m_strName.GetBuffer(0));
	s32Ret = HI_VSCP_DEVSCLI_Cmd(m_pSchHandle, &struDevInfo, HI_VSCP_CMD_NAME, pstrName);
	if (s32Ret == HI_SUCCESS)
	{
		MessageBox("Name setup success!");	
	}
	else
	{
		MessageBox("Name setup failure!");
	}*/
}

HBRUSH CStep3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
    // TODO: Change any attributes of the DC here
    if (pWnd->GetDlgCtrlID() == IDC_INFO)
    {
        pDC->SetTextColor(RGB(0,0,255));
    }
	
    // TODO: Return a different brush if the default is not desired
    return hbr;
}


int SEARCH_APICALL CStep3::CallBackSet(const HI_VOID* pvHandle,  HI_CHAR* pszRNPCode, 
        HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo* pstruResponseInfo, HI_VOID* pvUserData)
{
    if (pvUserData == NULL || pvHandle == NULL)
    {
        return -1;
    }

	CString strRtn;
	strRtn = pszRNPCode;

	if (strRtn.Find("200") > -1)
	{
		CStep3* pSteps = (CStep3*) pvUserData;
		CWizard* pWizard = (CWizard*)(AfxGetMainWnd());

		strncpy(pWizard->m_struSeletedDevinfo.struNetInfo.aszIP, pSteps->m_stuSetDevInfo.struNetInfo.aszIP, HI_VSCP_IP_STRSIZE +1);
		strncpy(pWizard->m_struSeletedDevinfo.struNetInfo.aszMASK, pSteps->m_stuSetDevInfo.struNetInfo.aszMASK, HI_VSCP_IP_STRSIZE +1);
		strncpy(pWizard->m_struSeletedDevinfo.struNetInfo.aszGTW, pSteps->m_stuSetDevInfo.struNetInfo.aszGTW, HI_VSCP_IP_STRSIZE +1);
		strncpy(pWizard->m_struSeletedDevinfo.struNetInfo.aszMAC, pSteps->m_stuSetDevInfo.struNetInfo.aszMAC, HI_VSCP_MAC_STRSIZE +1);

		AfxMessageBox("Successful !");
		return 0;
	}

	if (strRtn.Find("401") > -1)
	{
		AfxMessageBox("Account or Password Error!");
		return -1;
	}

    return 0;
}

void CStep3::GetHandle(HANDLE hdl)
{
    m_pvHandle = hdl;

    if (m_pvHandle == NULL)
    {
        return;
    }

    int s32Ret;
    
    s32Ret = HI_VSCP_DEVSCLI_RegistCmdProc(m_pvHandle, CallBackSet, this);
    
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }  
}

BOOL CStep3::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_ESCAPE)
	{
		return FALSE;
	}
	
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'P' && (GetKeyState(VK_CONTROL) & 0x8000))
	{
		GetDlgItem(IDC_MAC)->EnableWindow( ! GetDlgItem(IDC_MAC)->IsWindowEnabled() );
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CStep3::OnCheckDhcp() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK_DHCP))->GetCheck())
	{// 禁止
		((CButton *)GetDlgItem(IDC_IP))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_SUBMASK))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_GATEWAY))->EnableWindow(FALSE);
	}
	else
	{// 使能
		((CButton *)GetDlgItem(IDC_IP))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_SUBMASK))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_GATEWAY))->EnableWindow(TRUE);
	}
}

void CStep3::OnModifyPort() 
{
	// TODO: Add your control notification handler code here
//	HI_S_VSCP_DEVINFO devInfo;
    CString str;
	CString strCommand;
	int rt = HI_FAILURE;

	//用户验证
	CCheckUser dlg;
    dlg.GetAccount(((CWizard*)AfxGetMainWnd())->m_strUsername, ((CWizard*)AfxGetMainWnd())->m_strUserpwd, ((CWizard*)AfxGetMainWnd())->m_iIfMem);
    if (dlg.DoModal()==IDCANCEL)
    {
        return;
    }
	
    //
    GetDlgItem(IDC_INFO)->SetWindowText(_T("Now is modify the device setting, please waiting..."));
	
	HI_S_VSCP_DEVSCLI_DevInfo struDevInfo;
	struDevInfo.pszPasswd = ((CWizard*)AfxGetMainWnd())->m_strUserpwd.GetBuffer(0);
	struDevInfo.pszUserName = ((CWizard*)AfxGetMainWnd())->m_strUsername.GetBuffer(0);
	struDevInfo.pszDevID = ((CWizard*)AfxGetMainWnd())->m_struSeletedDevinfo.aszDevID;
    
	//获取修改值
    CString strPort="";
	GetDlgItemText(IDC_PORT,strPort);

	rt = HI_VSCP_DEVSCLI_Cmd(m_pvHandle, &struDevInfo, HI_VSCP_CMD_PORT, strPort.GetBuffer(0));

    GetDlgItem(IDC_INFO)->SetWindowText(_T(""));
	AfxMessageBox("The IP Camera will be restart!it can not be searched while restarting!");
}
