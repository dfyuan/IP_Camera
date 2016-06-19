// Step2.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWizard.h"
#include "Step2.h"
#include "Wizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep2 dialog


CStep2::CStep2(CWnd* pParent /*=NULL*/)
	: CDialog(CStep2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStep2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep2)
	DDX_Control(pDX, IDC_LIST1, m_ctrDevList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep2, CDialog)
	//{{AFX_MSG_MAP(CStep2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UPDATE_DEVDATA, GetDevMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep2 message handlers

BOOL CStep2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    GetDlgItem(IDC_TITLE)->SetWindowText(_T("Device list in local network"));
    GetDlgItem(IDC_TEXT)->SetWindowText(_T("Please select a device from list, and press \"Next\" button to modify the setting."));
    GetDlgItem(IDC_REFRESH)->SetWindowText(_T("Refresh"));

    CImageList imgList;
    imgList.Create(1, 17, ILC_COLOR16|ILC_MASK, 18, 1);
    m_ctrDevList.SetImageList(&imgList, LVSIL_SMALL);

    m_ctrDevList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_ctrDevList.InsertColumn(1, _T("No."), LVCFMT_CENTER, 40);
    m_ctrDevList.InsertColumn(2, _T("IP"), LVCFMT_CENTER, 115);
    m_ctrDevList.InsertColumn(3, _T("Name"), LVCFMT_CENTER, 100);
    m_ctrDevList.InsertColumn(4, _T("SubMask"), LVCFMT_CENTER, 115);
    m_ctrDevList.InsertColumn(5, _T("GateWay"), LVCFMT_CENTER, 105);
	m_ctrDevList.InsertColumn(5, _T("Http Port"), LVCFMT_CENTER, 40);

    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//DEL void CStep2::OnSearchByHand() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL     DWORD dwIpAddr;
//DEL     CString strIp;
//DEL     int fd[4];
//DEL 
//DEL 	m_ctrIpAddress.GetAddress(dwIpAddr);
//DEL 
//DEL     fd[0] = dwIpAddr >> 24;
//DEL     fd[1] = (dwIpAddr >> 16) & 0xFF;
//DEL     fd[2] = (dwIpAddr >> 8) & 0xFF;
//DEL     fd[3] = dwIpAddr & 0xFF;
//DEL     strIp.Format("%d.%d.%d.%d", fd[0],fd[1],fd[2],fd[3]);
//DEL 
//DEL     AfxMessageBox(strIp);
//DEL }


void CStep2::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_iCurSelection = m_ctrDevList.GetSelectionMark();
    if (m_iCurSelection == -1)
    {
        return;
    }
    ((CWizard*)GetParent())->m_struSeletedDevinfo = m_aDevList.at(m_iCurSelection);
    GetParent()->GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);

	*pResult = 0;
}


void CStep2::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if (bShow==TRUE)
    {
		OnRefresh();
        m_iCurSelection = -1;
        memset(&((CWizard*)GetParent())->m_struSeletedDevinfo, 0, sizeof(HI_S_VSCP_DEVINFO));
    }       
}

void CStep2::OnRefresh() 
{
	// TODO: Add your control notification handler code here
//     GetDlgItem(IDC_INFO)->SetWindowText(_T("Now is refreshing, please waiting..."));
    m_aDevList.clear();
	m_ctrDevList.DeleteAllItems();
	int s32Ret = HI_VSCP_DEVSCLI_Search(m_pHandle);
}

HBRUSH CStep2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    
    if (pWnd->GetDlgCtrlID() == IDC_INFO)
    {
        GetParent()->GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
        GetParent()->GetDlgItem(IDC_PREV)->SetFocus();
        pDC->SetTextColor(RGB(0,0,255));
    }
	
    // TODO: Return a different brush if the default is not desired
    return hbr;
}

void CStep2::InsertData(HI_S_VSCP_DEVINFO &devInfo)
{
	int i = 0;
	int index = 0;
	CString str;
	int devNum=0;
	int k = 0;

    for (int j=0; j<m_aDevList.size(); j++)
    {
        if (HI_VSCP_DEVID_STRSIZE < strlen(devInfo.aszDevID))
        {
			//goto RELEASE;
			return;
        }

        //compare devID
        for (k = 0; k < strlen(devInfo.aszDevID); k++)
        {
            if ((m_aDevList.at(j).aszDevID)[k] == (devInfo.aszDevID)[k])
            {
                continue;
            }

            break;
        }

        if (k == strlen(devInfo.aszDevID))
        {
			//goto RELEASE;
            return ;
        }
    }

	//ÅÅÐò²åÈë
	devNum = m_aDevList.size();
	for (index = 0; index < devNum; index++)
	{
		
		if (strcmp(m_aDevList.at(index).struNetInfo.aszIP, devInfo.struNetInfo.aszIP) > 0)
		{
			m_aDevList.insert(m_aDevList.begin()+index, devInfo);
			break;
		}
	}
	if (index == devNum)
	{
		m_aDevList.push_back(devInfo);
	}

 	m_ctrDevList.DeleteAllItems();
    
    for (i=m_aDevList.size()-1; i >=0; i--)
    {
        str.Format(_T("%d"), i+1);
        m_ctrDevList.InsertItem(0, str);
        m_ctrDevList.SetItemText(0, 1, m_aDevList.at(i).struNetInfo.aszIP);
        m_ctrDevList.SetItemText(0, 2, m_aDevList.at(i).aszDevName);
        m_ctrDevList.SetItemText(0, 3, m_aDevList.at(i).struNetInfo.aszMASK);
        m_ctrDevList.SetItemText(0, 4, m_aDevList.at(i).struNetInfo.aszGTW);
        m_ctrDevList.SetItemText(0, 5, m_aDevList.at(i).aszHttpPort);
    }
/*RELEASE:
	if(devInfo.pstruChnInfo)
	{
		int nchn = devInfo.u32ChnCnt;
		for (i=0;i<nchn;i++)
		{
			if(devInfo.pstruChnInfo[i].pstruStreamInfo)
				free(devInfo.pstruChnInfo[i].pstruStreamInfo);
		}
		free(devInfo.pstruChnInfo);
	}*/
}

void CStep2::GetNetHandle(HANDLE hand)
{
	m_pHandle = hand;
    
	if (m_pHandle == NULL)
    {
        return;
    }
    
	int s32Ret;
    s32Ret = HI_VSCP_DEVSCLI_RegistSearchProc(m_pHandle, CallBackSearch, this);
    if ((HI_SUCCESS != s32Ret))
    {
        return;
    }

	s32Ret = HI_VSCP_DEVSCLI_Search(m_pHandle);
	if (HI_SUCCESS != s32Ret)
	{
		return;
	}
	//OnRefresh();
}

int SEARCH_APICALL CStep2::CallBackSearch(const HI_VOID* pvHandle,HI_CHAR* pszRNPCode,HI_S_VSCP_DEVINFO* pstruDevInfo,HI_VOID* pvUserData)
{
	CStep2 *pSearch = (CStep2*)pvUserData;
//	pSearch->InsertData(*pstruDevInfo);
 	pSearch->SendMessage(UPDATE_DEVDATA,(UINT)pstruDevInfo, NULL);
	
    return 0;
}

BOOL CStep2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_ESCAPE)
	{
		return FALSE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CStep2::GetDevMsg(WPARAM wparm, LPARAM lparm)
{
	HI_S_VSCP_DEVINFO* pDev = (HI_S_VSCP_DEVINFO*)wparm;
	InsertData(*pDev);

	return 0;
}
