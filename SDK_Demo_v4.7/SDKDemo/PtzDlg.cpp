// PtzDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdkdemo.h"
#include "PtzDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtzDlg dialog


CPtzDlg::CPtzDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPtzDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPtzDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CPtzDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPtzDlg)
	DDX_Control(pDX, IDC_COMBO_PARITY, m_combParity);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_combStopBit);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_combDataBit);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_combBaud);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_combProtocol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPtzDlg, CDialog)
	//{{AFX_MSG_MAP(CPtzDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtzDlg message handlers

BOOL CPtzDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CString strBuf = "";
	m_combProtocol.InsertString(0, "PELCO-D");
	m_combProtocol.InsertString(1, "PELCO-P");
	m_combProtocol.SetCurSel(0);
	
	m_combBaud.InsertString(0, "110");
	m_combBaud.InsertString(1, "300");
	m_combBaud.InsertString(2, "1200");
	m_combBaud.InsertString(3, "2400");
	m_combBaud.InsertString(4, "4800");
	m_combBaud.InsertString(5, "9600");
	m_combBaud.InsertString(6, "19200");
	m_combBaud.InsertString(7, "38400");
	m_combBaud.InsertString(8, "57600");
	m_combBaud.SetCurSel(0);
	
	m_combDataBit.InsertString(0, "5");
	m_combDataBit.InsertString(1, "6");
	m_combDataBit.InsertString(2, "7");
	m_combDataBit.InsertString(3, "8");
	m_combDataBit.SetCurSel(0);
	
	m_combStopBit.InsertString(0, "1");
	m_combStopBit.InsertString(1, "2");
	m_combStopBit.SetCurSel(0);
	
	m_combParity.InsertString(0, ConvertString("None"));
	m_combParity.InsertString(1, ConvertString("Odd"));
	m_combParity.InsertString(2, ConvertString("Even"));
	m_combParity.SetCurSel(0);

	if(m_lHandle != 0)
	{
		HI_S_PTZ sPtz;
		HI_SDK_GetConfig(m_lHandle, HI_CMD_PTZ_PARAM, &sPtz, sizeof(HI_S_PTZ));

		strBuf.Format("%d", sPtz.u32Address);
		SetDlgItemText(IDC_EDIT_ADDRESS, strBuf);

		int nProtocol = 0;
		switch(sPtz.u32Protocol)
		{
		case HI_PTZ_PRO_PELCOD:
			break;
		case HI_PTZ_PRO_PELCOP:
			nProtocol = 1;
			break;
		default:
			break;
		}
		m_combProtocol.SetCurSel(nProtocol);
		
		int nBaud = 0;
		switch(sPtz.u32Baud)
		{
		case HI_PTZ_B110:
			nBaud = 0;
			break;
		case HI_PTZ_B300:
			nBaud = 1;
			break;
		case HI_PTZ_B1200:
			nBaud = 2;
			break;
		case HI_PTZ_B2400:
			nBaud = 3;
			break;
		case HI_PTZ_B4800:
			nBaud = 4;
			break;
		case HI_PTZ_B9600:
			nBaud = 5;
			break;
		case HI_PTZ_B19200:
			nBaud = 6;
			break;
		case HI_PTZ_B38400:
			nBaud = 7;
			break;
		case HI_PTZ_B57600:
			nBaud = 8;
			break;
		default:
			break;
		}
		m_combBaud.SetCurSel(nBaud);
		
		int nDataBit = 0;
		switch(sPtz.u32DataBit)
		{
		case HI_PTZ_DATA_5:
			nDataBit = 0;
			break;
		case HI_PTZ_DATA_6:
			nDataBit = 1;
			break;
		case HI_PTZ_DATA_7:
			nDataBit = 2;
			break;
		case HI_PTZ_DATA_8:
			nDataBit = 3;
			break;
		default:
			break;
		}
		m_combDataBit.SetCurSel(nDataBit);
		
		int nStopBit = 0;
		switch(sPtz.u32StopBit)
		{
		case HI_PTZ_STOP_1:
			nStopBit = 0;
			break;
		case HI_PTZ_STOP_2:
			nStopBit = 1;
			break;
		default:
			break;
		}
		m_combStopBit.SetCurSel(nStopBit);
		
		int nParity = 0;
		switch(sPtz.u32Parity)
		{
		case HI_PTZ_PARITY_NONE:
			nParity = 0;
			break;
		case HI_PTZ_PARITY_ODD:
			nParity = 1;
			break;
		case HI_PTZ_PARITY_EVEN:
			nParity = 2;
			break;
		default:
			break;
		}
		m_combParity.SetCurSel(nParity);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPtzDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}

void CPtzDlg::OnOK() 
{
	// TODO: Add extra validation here
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 u32Index = 0;
	
	if(0 == m_lHandle)
	{
		MessageBox(ConvertString("No connection!"));
		return;
	}
	
	HI_U32 u32Protocol[2]	= {HI_PTZ_PRO_PELCOD, HI_PTZ_PRO_PELCOP};
	HI_U32 u32Baud[9]		= {	HI_PTZ_B110, HI_PTZ_B300, HI_PTZ_B1200,
								HI_PTZ_B2400, HI_PTZ_B4800, HI_PTZ_B9600,
								HI_PTZ_B19200, HI_PTZ_B38400, HI_PTZ_B57600};
	HI_U32 u32DataBit[4]	= {HI_PTZ_DATA_5, HI_PTZ_DATA_6, HI_PTZ_DATA_7, HI_PTZ_DATA_8};
	HI_U32 u32StopBit[2]	= {HI_PTZ_STOP_1, HI_PTZ_STOP_2};
	HI_U32 u32Parity[3]		= {HI_PTZ_PARITY_NONE, HI_PTZ_PARITY_ODD, HI_PTZ_PARITY_EVEN};
	
	int nValue = 0;
	CString strBuf;
	HI_S_PTZ sPtz;
	
	GetDlgItemText(IDC_EDIT_ADDRESS, strBuf);
	nValue = atoi(strBuf);
	if(nValue<0 || nValue>255){
		MessageBox(ConvertString("Address range is 0 to 255!"));
		return;
	}
	
	sPtz.u32Address = nValue;
	
	nValue = m_combProtocol.GetCurSel();
	sPtz.u32Protocol = u32Protocol[nValue];
	nValue = m_combBaud.GetCurSel();
	sPtz.u32Baud = u32Baud[nValue];
	nValue = m_combDataBit.GetCurSel();
	sPtz.u32DataBit = u32DataBit[nValue];
	nValue = m_combStopBit.GetCurSel();
	sPtz.u32StopBit = u32StopBit[nValue];
	nValue = m_combParity.GetCurSel();
	sPtz.u32Parity = u32Parity[nValue];
	
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_PTZ_PARAM, &sPtz, sizeof(HI_S_PTZ));
	if(HI_SUCCESS == s32Ret)
		MessageBox(ConvertString("Settings Success!"));
	else
		MessageBox(ConvertString("Setting Failure!"));
}
