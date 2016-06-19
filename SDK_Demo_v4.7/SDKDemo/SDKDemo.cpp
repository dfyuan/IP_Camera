// SDKDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SDKDemo.h"
#include "SDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
/////////////////////////////////////////////////////////////////////////////
// CSDKDemoApp

BEGIN_MESSAGE_MAP(CSDKDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CSDKDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDKDemoApp construction

CSDKDemoApp::CSDKDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSDKDemoApp object

CSDKDemoApp theApp;
CString	g_strPath = "";

/////////////////////////////////////////////////////////////////////////////
// CSDKDemoApp initialization

BOOL CSDKDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	GetModuleFileName(NULL, g_strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
	g_strPath.ReleaseBuffer();
	int pos = g_strPath.ReverseFind('\\');
	g_strPath = g_strPath.Left(pos);

	HI_SDK_Init();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSDKDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

//��Ӣ���ַ�����ת��Ϊ����ǰ�������͵��ַ�����
CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath,strRet;
	
	if(g_strPath != "")
		strIniPath = g_strPath + "\\langchn.ini";
	else
		strIniPath = "./langchn.ini";
	memset(val,0,200);
	GetPrivateProfileString("String", strText, "",
		val, 200, strIniPath);
	//printf("%s\n", val);
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//���ini�ļ��в����ڶ�Ӧ���ַ���������ΪĬ��ֵ��Ӣ�ģ�
		strRet=strText;
	}
	delete[] val;
	return strRet;
}
//���öԻ����еľ�̬�ı�(Ӣ��-->��ǰ����)   
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//���������ڵı���
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//�����Ӵ��ڵı���
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//��һ���Ӵ���
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//�����Ӵ��ڵĵ�ǰ�����ı�
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//��һ���Ӵ���
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}

int CSDKDemoApp::ExitInstance() 
{
	HI_SDK_Cleanup();
	
	return CWinApp::ExitInstance();
}

void CreateDirectoryEx(CString strDir) 
{ 
	if(strDir.GetLength()!=0) 
	{ 
		if(strDir.Right(1)== "\\") 
			strDir=strDir.Left(strDir.GetLength()-1);   
		
		if(GetFileAttributes(strDir)!=-1)   
			return; 
		
		int nFound = strDir.ReverseFind('\\'); 
		CreateDirectoryEx(strDir.Left(nFound));
		CreateDirectory(strDir,NULL); 
	} 
	else 
		return;   
}
