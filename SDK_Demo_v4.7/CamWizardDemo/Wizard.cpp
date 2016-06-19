// Wizard.cpp : implementation file
//

#include "stdafx.h"
#include "CustomWizard.h"
#include "Wizard.h"
#include "Step1.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"
#include "Iphlpapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CMyAboutDlg : public CDialog
{
public:
    CMyAboutDlg();
    
    // Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA
    
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CMyAboutDlg::CMyAboutDlg() : CDialog(CMyAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CMyAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard dialog


CWizard::CWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pPageLink=NULL;
	m_iPageCount=0;
	m_iCurrentPage=0;
}


void CWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizard)
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizard, CDialog)
	//{{AFX_MSG_MAP(CWizard)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_FINISH, OnFinish)
	ON_WM_DESTROY()
	ON_WM_PAINT()
    ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CWizard message handlers
void CWizard::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CMyAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

void CWizard::AddPage(CDialog* pDialog, UINT nID)
{
	struct PAGELINK* pTemp = m_pPageLink;

	//插入新生成的结点
	struct PAGELINK* pNewPage = new PAGELINK;
    if (pNewPage == NULL)
    {
        return;
    }

    pNewPage->pDialog = pDialog;
    pNewPage->pDialog->Create(nID,this);
	
	// Is window created
	ASSERT(::IsWindow(pNewPage->pDialog->m_hWnd));

    // 检查每页的样式
	DWORD dwStyle = pNewPage->pDialog->GetStyle();
	ASSERT((dwStyle & WS_CHILD) != 0); //子窗体
	ASSERT((dwStyle & WS_BORDER) == 0); //无边界

	//显示
	pNewPage->pDialog->ShowWindow(SW_HIDE);
	pNewPage->pDialog->MoveWindow(m_rectPage);

	pNewPage->Next=NULL;
	pNewPage->nNum=++m_iPageCount; //计数器加1

	if (pTemp)
	{
		while (pTemp->Next)
        {
            pTemp=pTemp->Next; //移动链表末尾
        }
		pTemp->Next=pNewPage;
	}
	else
    {
		m_pPageLink=pNewPage; //若是第一个接点
    }
}

void CWizard::OnPrev() 
{
	ShowPage(--m_iCurrentPage);
}

void CWizard::OnNext() 
{
	ShowPage(++m_iCurrentPage);
}

void CWizard::OnFinish() 
{
    if (m_iCurrentPage == m_iPageCount)
    {
        if (AfxMessageBox(IDS_FINISH, MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL)
        {
            return;
        }
    }
    else
    {
        if (AfxMessageBox(IDS_QUIT, MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
        {
            return;
        }
    }

    CDialog::OnOK();
}



void CWizard::ShowPage(UINT nPos)
{
	struct PAGELINK* pTemp=m_pPageLink;
	while(pTemp)
	{
		if (pTemp->nNum==nPos)
		{
			pTemp->pDialog->ShowWindow(SW_SHOW);
		}
		else
        {
		    //不显示
			pTemp->pDialog->ShowWindow(SW_HIDE);
        }

		pTemp=pTemp->Next;
	}

	if (nPos>=m_iPageCount)  //最后一页
	{
		m_iCurrentPage=m_iPageCount;
		SetWizButton(2);
		return;
	}

	if (nPos<=1) //首页 
	{
		m_iCurrentPage=1;
		SetWizButton(0);
		return;
	}

	//中间步
	SetWizButton(1);
}

void CWizard::SetWizButton(UINT uFlag)
{
	GetDlgItem(IDC_PREV)->EnableWindow(TRUE);
	GetDlgItem(IDC_NEXT)->EnableWindow(TRUE); 
    GetDlgItem(IDC_FINISH)->EnableWindow(TRUE);

    GetDlgItem(IDC_PREV)->SetWindowText(_T("&Back"));
	GetDlgItem(IDC_NEXT)->SetWindowText(_T("&Next")); 

	switch(uFlag)
	{
	case 0: //第一步
		GetDlgItem(IDC_PREV)->EnableWindow(FALSE);
        GetDlgItem(IDC_NEXT)->SetFocus();
        GetDlgItem(IDC_FINISH)->SetWindowText(_T("&Cancel"));
		break;
	case 1: //中间步
        GetDlgItem(IDC_FINISH)->EnableWindow(TRUE);
        GetDlgItem(IDC_FINISH)->SetWindowText(_T("&Cancel"));
		break;
	case 2://最后一步
		GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
        GetDlgItem(IDC_PREV)->SetFocus();
        GetDlgItem(IDC_FINISH)->SetWindowText(_T("&Finish"));
		break;
	default:
		break;
	}
}

BOOL CWizard::OnInitDialog() 
{
	CDialog::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }
    
    SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    //////////////////////////////////////////////////////////////////////////
    if (InitNet() != 0)
    {
        AfxMessageBox(_T("Initialize net error!"));
        exit(0);
    }
	
    SetWindowText(_T("Setting Guide"));

    //获得每页显示的范围
	CRect Rect1;
	GetWindowRect(&Rect1); //获得主窗口的位置

	int nCaption    = ::GetSystemMetrics(SM_CYCAPTION);
	int nXEdge      = ::GetSystemMetrics(SM_CXEDGE);
	int nYEdge      = ::GetSystemMetrics(SM_CYEDGE);

	CRect Rect2;
	GetDlgItem(IDC_POS)->GetWindowRect(&Rect2); //获得框架的位置
	Rect1.top=Rect1.top+nCaption+nYEdge; //相对坐标
	Rect1.left=Rect1.left+2*nXEdge;

	//计算机位置
	m_rectPage.top=Rect2.top-Rect1.top;
	m_rectPage.left=Rect2.left-Rect1.left;
	m_rectPage.bottom=Rect2.bottom-Rect1.top;
	m_rectPage.right=Rect2.right-Rect1.left;

	//添加要显示的页
    CStep1* pStep1 = new CStep1;
    CStep2* pStep2 = new CStep2;
    CStep3* pStep3 = new CStep3;
    CStep4* pStep4 = new CStep4;

    if (pStep1 == NULL || pStep2 == NULL || pStep3 == NULL || pStep4 == NULL)
    {
        return FALSE;
    }

    AddPage(pStep1, IDD_STEP1);
    AddPage(pStep2, IDD_STEP2);
    AddPage(pStep3, IDD_STEP3);
    AddPage(pStep4, IDD_STEP4);

	pStep2->GetNetHandle(m_pvHandle);

	//显示第一页
    ShowPage(1);

    return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWizard::OnDestroy() 
{
	ReleaseNet();

	//依次消除每页
	struct PAGELINK* pTemp = m_pPageLink;
	while(pTemp)
	{
		struct PAGELINK* pNextTemp = pTemp->Next;
		pTemp->pDialog->DestroyWindow();
		delete pTemp->pDialog;
		delete pTemp;
		pTemp = pNextTemp;
	}

	CDialog::OnDestroy();
}


BOOL CWizard::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class	
    switch(pMsg->wParam)
    {
    case VK_ESCAPE:
        return TRUE; //直接返回TRUE
    	break;
    default:
        break;
    }

	return CDialog::PreTranslateMessage(pMsg);
}

int CWizard::InitNet()
{
    int s32Ret;
    HI_VOID* pvHandle = NULL;
    char ip[10][16];

    memset(ip, 0, sizeof(char)*10*(HI_VSCP_IP_STRSIZE + 1));

    //s32Ret = HI_VSCP_DEVSCLI_INIT(DEVSEARCH_MULIP, DEVSEARCH_PORT, 4, &pvHandle);
    s32Ret = HI_VSCP_DEVSCLI_INIT(SEARCH_BROADIP, SEARCH_BROADPORT, 4, &pvHandle);
    if ((HI_SUCCESS != s32Ret) || (NULL == pvHandle))
    {
        return -1;
    }

    m_pvHandle = pvHandle;

    //Get local ip
    int ipNum = 0;
    GetIpArray(ip, ipNum);
    HI_VSCP_DEVSCLI_Register_IP(ip, ipNum);
    
    return 0;
}


int CWizard::ReleaseNet()
{
    int ret = HI_VSCP_DEVSCLI_Deinit(m_pvHandle);

	return ret;
}

HANDLE CWizard::SetHandle()
{
    return m_pvHandle;
}

void CWizard::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting
        
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
        
        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        
        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
	}
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CWizard::OnClose() 
{
    if (AfxMessageBox(IDS_QUIT, MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
    {
        return;
    }
	
    CDialog::OnClose();
}

CString GetPcAddress(int &ipNum)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    ULONG uBufLen = 0;
    DWORD dwRetVal = 0;
    CString strIP;

    ipNum = 0;
    
    GetAdaptersInfo(NULL, &uBufLen);
    pAdapterInfo = (PIP_ADAPTER_INFO) new char[uBufLen];
    
    dwRetVal = GetAdaptersInfo(pAdapterInfo, &uBufLen);
    if (ERROR_BUFFER_OVERFLOW == dwRetVal)
    {
        delete[] pAdapterInfo;
        pAdapterInfo = NULL;
        return "";
    }
    else if (ERROR_SUCCESS == dwRetVal)
    {
        PIP_ADAPTER_INFO pAdapterInfoTemp = pAdapterInfo;
        
        //循环查找网卡
		CString strTmp;
        while (pAdapterInfoTemp)
        {
            strTmp = pAdapterInfoTemp->IpAddressList.IpAddress.String;//get ip address
			strIP += strTmp;
            
            ipNum ++;
            if (pAdapterInfoTemp = pAdapterInfoTemp->Next)
			{
                strIP = strIP + ",";	  //partition every IP address with ','
            }
        }
        
        delete[] pAdapterInfo;	//release memory
        pAdapterInfo = NULL;
    }
    else
    {
        delete[] pAdapterInfo;	//release memory
        pAdapterInfo = NULL;
        return "";
    }	
    
    if (pAdapterInfo != NULL)
    {
        delete (pAdapterInfo);
        pAdapterInfo = NULL;
    }

    return strIP;
}

void CWizard::GetIpArray(char ipA[][HI_VSCP_IP_STRSIZE + 1], int &num)
{
    CString str;
    int iIpNum = 0;
    int ipLen = HI_VSCP_IP_STRSIZE + 1;

    str = GetPcAddress(iIpNum);
    if (iIpNum < 1)
    {
        return;
    }

    num = iIpNum;

    //*ipA = (char*)malloc((HI_VSCP_IP_STRSIZE + 1) * iIpNum);
    int index=0;
    CString strIp;
    for (int i=0; i<iIpNum; i++)
    {
        index = str.Find(',');
        if (index == -1 && str.GetLength() > 0)
        {
            strncpy(ipA[i], str.GetBuffer(0), ipLen);
        }
        if (index > -1)
        {
            strIp = str.Left(index);
            strncpy(ipA[i], strIp.GetBuffer(0), ipLen);
            str = str.Mid(index+1);
        }
        //ipA[i][HI_VSCP_IP_STRSIZE] = '\0';
    }
}
