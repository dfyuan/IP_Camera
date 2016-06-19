// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2F8355D3_24C2_11D6_9DF5_70D757C10000__INCLUDED_)
#define AFX_STDAFX_H__2F8355D3_24C2_11D6_9DF5_70D757C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>

#include "hi_DataType.h"

#define UPDATE_DEVDATA WM_USER+1001

#pragma comment(lib, "SearchLib.lib")
#pragma comment(lib, "IPHlpApi.Lib")
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2F8355D3_24C2_11D6_9DF5_70D757C10000__INCLUDED_)
