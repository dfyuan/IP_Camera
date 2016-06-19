// TimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "TimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString strTimeZone[74] = {
		"Etc/GMT-12",
		"Pacific/Apia",
		"Pacific/Honolulu",
		"America/Anchorage",
		"America/Los_Angeles",
		"America/Denver",
		"America/Tegucigalpa",
		"America/Phoenix",
		"America/Winnipeg",
		"America/Mexico_City",
		"America/Chicago",
		"America/Costa_Rica",
		"America/Indianapolis",
		"America/New_York",
		"America/Bogota",
		"America/Santiago",
		"America/Caracas",
		"America/Montreal",
		"America/St_Johns",
		"America/Thule",
		"America/Buenos_Aires",
		"America/Sao_Paulo",
		"Atlantic/South_Georgia",
		"Atlantic/Cape_Verde",
		"Atlantic/Azores",
		"Europe/Dublin",
		"Africa/Casablanca",
		"Europe/Amsterdam",
		"Europe/Belgrade",
		"Europe/Brussels",
		"Europe/Warsaw",
		"Africa/Lagos",
		"Europe/Athens",
		"Europe/Bucharest",
		"Africa/Cairo",
		"Africa/Harare",
		"Europe/Helsinki",
		"Asia/Jerusalem",
		"Asia/Baghdad",
		"Asia/Kuwait",
		"Europe/Moscow",
		"Africa/Nairobi",
		"Asia/Tehran",
		"Asia/Dubai",
		"Asia/Baku",
		"Asia/Kabul",
		"Asia/Yekaterinburg",
		"Asia/Karachi",
		"Asia/Calcutta",
		"Asia/Katmandu",
		"Asia/Almaty",
		"Asia/Dhaka",
		"Asia/Colombo",
		"Asia/Rangoon",
		"Asia/Bangkok",
		"Asia/Krasnoyarsk",
		"Asia/Hong_Kong",
		"Asia/Irkutsk",
		"Asia/Kuala_Lumpur",
		"Australia/Perth",
		"Asia/Taipei",
		"Asia/Tokyo",
		"Asia/Seoul",
		"Asia/Yakutsk",
		"Australia/Adelaide",
		"Australia/Brisbane",
		"Australia/Sydney",
		"Pacific/Guam",
		"Australia/Hobart",
		"Asia/Vladivostok",
		"Asia/Magadan",
		"Pacific/Auckland",
		"Pacific/Fiji",
		"Pacific/Tongatapu"
};

int nState[74] = {	0, 0, 0, 1, 1, 1, 1, 0, 0,
					1, 1, 0, 0, 1, 0, 1, 0, 1,
					1, 1, 0, 1, 1, 0, 1, 1, 0,
					1, 1, 1, 1, 0, 1, 1, 1, 0,
					1, 0, 1, 0, 1, 0, 1, 0, 1,
					0, 1, 0, 0, 0, 1, 0, 0, 0,
					0, 1, 0, 1, 0, 0, 0, 0, 0,
					1, 1, 0, 1, 0, 1, 1, 0, 1,
					0, 0};

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog


CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeDlg)
	m_lHandle = 0;
	//}}AFX_DATA_INIT
}


void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeDlg)
	DDX_Control(pDX, IDC_DT_TIME, m_dtTime);
	DDX_Control(pDX, IDC_DT_DATE, m_dtDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeDlg)
	ON_BN_CLICKED(IDC_CHECK_SYNC, OnCheckSync)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers

BOOL CTimeDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i=0;
	CString strBuf = "";

	/*for(i=0; i<74; i++)
	{
		m_comboZone.InsertString(i, strTimeZone[i]);
	}
	m_comboZone.SetCurSel(56);*/

	m_dtDate.SetFormat("yyyy-MM-dd");
	m_dtTime.SetFormat("H:mm:ss");
	
	HI_S32 s32Ret = HI_FAILURE;
	HI_S_SERVERTIME sServerTime;
	memset(&sServerTime, 0, sizeof(HI_S_SERVERTIME));
	if(m_lHandle != 0)
	{
		printf("%d\n", sizeof(HI_S_SERVERTIME));
		s32Ret = HI_SDK_GetConfig(m_lHandle, HI_CMD_SERVER_TIME, &sServerTime, sizeof(HI_S_SERVERTIME));
		
		int nYear, nMon, nDay, nHour, nMin, nSec;
		strBuf.Format("%c%c%c%c", sServerTime.sTime[0], sServerTime.sTime[1], sServerTime.sTime[2], sServerTime.sTime[3]);
		nYear = atoi(strBuf);
		strBuf.Format("%c%c", sServerTime.sTime[4], sServerTime.sTime[5]);
		nMon = atoi(strBuf);
		strBuf.Format("%c%c", sServerTime.sTime[6], sServerTime.sTime[7]);
		nDay = atoi(strBuf);
		strBuf.Format("%c%c", sServerTime.sTime[8], sServerTime.sTime[9]);
		nHour = atoi(strBuf);
		strBuf.Format("%c%c", sServerTime.sTime[10], sServerTime.sTime[11]);
		nMin = atoi(strBuf);
		strBuf.Format("%c%c", sServerTime.sTime[12], sServerTime.sTime[13]);
		nSec = atoi(strBuf);

		CTime tmTime(nYear, nMon, nDay, nHour, nMin, nSec);
		m_dtDate.SetTime(&tmTime);
		m_dtTime.SetTime(&tmTime);

		/*for(i=0; i<74; i++)
		{
			if(strcmp(sServerTime.sTimezone, strTimeZone[i].GetBuffer(0)) == 0)
			{
				m_comboZone.SetCurSel(i);
				if(nState[i] == 1)
					GetDlgItem(IDC_CHECK_AUTO)->EnableWindow();
				break;
			}
		}*/
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimeDlg::SetHandle(long lHandle)
{
	m_lHandle = lHandle;
}

void CTimeDlg::OnCheckSync() 
{
	if(0 == ((CButton *)GetDlgItem(IDC_CHECK_SYNC))->GetCheck())
	{
		GetDlgItem(IDC_DT_DATE)->EnableWindow();
		GetDlgItem(IDC_DT_TIME)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_DT_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DT_TIME)->EnableWindow(FALSE);
	}
}

void CTimeDlg::OnBtnSet() 
{
	CString strBuf;
	HI_S32 s32Ret = HI_FAILURE;
	HI_S_SERVERTIME sServerTime;

	if(1 == ((CButton *)GetDlgItem(IDC_CHECK_SYNC))->GetCheck())
	{
		time_t tmNow;
		time(&tmNow);
		struct tm *localtm;
		localtm = localtime(&tmNow);
		
		//printf("%04d\n", localtm->tm_year);
		strBuf.Format("%04d.%02d.%02d.%02d.%02d.%02d", 
						localtm->tm_year+1900, localtm->tm_mon+1, localtm->tm_mday, 
						localtm->tm_hour, localtm->tm_min, localtm->tm_sec);
	}
	else
	{
		CTime tmDate, tmTime;
		m_dtDate.GetTime(tmDate);
		m_dtTime.GetTime(tmTime);

		strBuf.Format("%04d.%02d.%02d.%02d.%02d.%02d", 
						tmDate.GetYear(), tmDate.GetMonth(), tmDate.GetDay(),
						tmTime.GetHour(), tmTime.GetMinute(), tmTime.GetSecond());
	}

	memcpy(sServerTime.sTime, strBuf.GetBuffer(0), sizeof(sServerTime.sTime));

	//sServerTime.u32Dstmode = 0;
	s32Ret = HI_SDK_SetConfig(m_lHandle, HI_CMD_SERVER_TIME, &sServerTime, sizeof(HI_S_SERVERTIME));
	if(s32Ret != HI_SUCCESS)
		MessageBox(ConvertString("Setting Time Failure!"));
}
