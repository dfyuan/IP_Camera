// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A814EEDB_A949_4D81_BCBD_94794A346E37__INCLUDED_)
#define AFX_STDAFX_H__A814EEDB_A949_4D81_BCBD_94794A346E37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXSCREEN 4
#define MAXCAM 4
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define SDKDEOME_VERSION "SDK-v4.6[S]"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "hi_dataType.h"
#include "hi_vscp_devs_cli.h"
#include "hi_vscp_devs_cli_error.h"
#include "IPHlpApi.h"
#include "hi_sdk_api.h"

#pragma comment(lib, "HISDK.lib")


#pragma comment(lib, "SearchLib.lib")
#pragma comment(lib, "IPHlpApi.Lib")


#pragma comment(lib, "WINMM.LIB")

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A814EEDB_A949_4D81_BCBD_94794A346E37__INCLUDED_)
