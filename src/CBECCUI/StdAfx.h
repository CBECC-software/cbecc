// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__245352C7_5683_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_STDAFX_H__245352C7_5683_11D1_9002_0080C732DDC2__INCLUDED_

#define _HAS_AUTO_PTR_ETC 1      // ISO C++ 17 std compatibility - SAC 09/14/23

#include <string>
#include <vector>
#include <ctype.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define NOMINMAX                 // prevent:  warning C4003: not enough actual parameters for macro 'min'   w/ inclusion of QtCore\QDateTime.h  - SAC 2/20/17
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>      // SAC 1/14/03 - Added for CArray support

#include <afxole.h>			// 

//#include <afximpl.h>			// 

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#include <math.h>	
#include <direct.h>  			// Directory related system routines
#include <limits.h>     		// for UINT_MAX

#include <afxmt.h>
#include <afxpriv.h>
#include <urlmon.h>

#include "pathname.h"

#include <assert.h> 

#include <stdexcept>    // SAC 10/13/20

#pragma warning(disable : 4127)
#include <QtCore/QString.h>
#include <QtCore/QStringList.h>
#include <QtCore/QDateTime.h>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QVector>
#pragma warning(default : 4127)


/////////////////////////////////////////////////////////////////////////////
// Program Inline Functions
//

inline double degtorad(double d) 
{ return d/180.0*3.141592; }

inline double radtodeg(double d) 
{ return d/3.141592*180.0; }

inline float Divide(float n,float d)
{ return (d != 0) ? n/d : 0; }


/////////////////////////////////////////////////////////////////////////////
// Program Private Messages
//

#define WM_APP             0x8000

#define WM_GETDATASTATUS   WM_APP+4
#define WM_GETTEXTCOLOR    WM_APP+5

// Message to cause the mainfrm to reset the status bar message
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_SETSTATUSMESSAGE   WM_APP+6

// Messages to initiate the compliance analysis (handled by CDlgAnalysis)
#define WM_INITANALYSIS    WM_APP+7

// Messages to prompt BDB Ctrls to display and update data
#define WM_DISPLAYDATA     WM_APP+8
#define WM_DISPLAYMODS     WM_APP+9
#define WM_UPDATEDATA      WM_APP+10

// Message indicating that UI control data has been modified and post processing should occur
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_DATAMODIFIED    WM_APP+11

// Message indicating that a building database component is to be created
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_CREATECOMPONENT WM_APP+12

// Messages to spawn evaluation of compliance rules
#define WM_EVALPROPOSED    WM_APP+13

// Messages to spawn compliance analysis (handled by CMainFrame)
#define WM_COMPANALYSIS    WM_APP+14

// Message indicating log file has been updated
#define WM_LOGUPDATED      WM_APP+15

// Message passed to UI control parents when WM_HELPINFO passed to UI control
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_SETCONTEXTHELPID  WM_APP+16

// Message passed to main screen's view to update tabs once screen data has been read
#define WM_UPDATETABS        WM_APP+17

// Message passed to main frame to have screen data read
#define WM_LOADSCREENFILES   WM_APP+18

// Messages to spawn compliance analysis (via API mechanism) (handled by CMainFrame) - SAC 3/19/20
#define WM_APICOMPANALYSIS    WM_APP+19

//32 // Message indicating log file has been updated
//32 #define WM_SETTOSUMMODE    WM_APP+16
//32 #define WM_SETTOLOGMODE    WM_APP+17
//32 #define WM_SETTOREPMODE    WM_APP+18
//32 #define WM_SETTODETMODE    WM_APP+19

// Message to retrieve the DBID of the parameter displayed in a control
#define WM_GETCTRLDBID     WM_APP+20

// Message to cause any possible tree control updates
#define WM_UPDATETREE      WM_APP+21
#define WM_POPLIBTREE      WM_APP+22

// Message to cause a tree item to be edited via the corresponding component tabbed dialog
#define WM_EDITTREEITEM    WM_APP+23

// Message sent to the reporting application to reload report w/ current BEMProc contents
// THIS VALUE MUST MATCH IDENTICAL MESSAGE IN REPORT APP'S STDAFX.H
#define WM_RELOADREPORT    WM_APP+24

// Message to cause the mainfrm to present a quickmenu
// THESE VALUES MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_QUICKMENU         WM_APP+25
#define WM_QMRESTOREDEFAULT  WM_APP+26
#define WM_QM_DELETE_ROW     WM_APP+27

// Message to handle push button processing
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_BUTTONPRESSED     WM_APP+28

// Message to retrieve the DBInstance of the parameter displayed in a control
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN BEMProcUI's STDAFX.H
#define WM_GETCTRLDBINST     WM_APP+29

// Messages to manage FTP downloads (handled by CDlgFTPProgress)
#define WM_INITFTPDOWNLOAD   WM_APP+30
#define WM_ENDFTPDOWNLOAD    WM_APP+31
#define WM_DISPLAYFTPSTATUS  WM_APP+32

// Message to initiate batch compliance analysis (handled by CMainFrame) - SAC 07/15/23 (CalPRM)
#define WM_CMDLINE_BATCH     WM_APP+33

// Message sent from UI Control to Parent Dialog to retrieve DBID based on control ID
// THIS VALUE MUST MATCH IDENTICAL MESSAGES IN application's STDAFX.H & PD2'S MESSAGES.H
#define WM_CTRLIDTODBID      WM_APP+52   // SAC 2/19/01

// Message sent from UI Control to Parent Frame to confirm/report compatibility issues
#define WM_CHECKCOMPAT       WM_APP+53   // SAC 6/7/01

// Message to handle help button processing
// THIS VALUES MUST MATCH IDENTICAL MESSAGES IN application's STDAFX.H & PD2'S MESSAGES.H
#define WM_HELP_BTN_PRESSED  WM_APP+54   // SAC 10/19/02

// Messages sent between MainFrame & GridDialog - SAC 3/15/18
#define WM_BEMGRID_OPEN      WM_APP+55
#define WM_BEMGRID_CLOSE     WM_APP+56
#define WM_BEMGRID_UPDATE    WM_APP+57

// Message to initiate an automatic Save As process - SAC 9/29/20
#define WM_AUTOSAVEAS        WM_APP+58

// Message sent from ButtonClick to initiate dialog close + MainFrm action - SAC 08/19/22 (CUAC)
#define WM_DLGCLOSEACTION    WM_APP+59

#endif // !defined(AFX_STDAFX_H__245352C7_5683_11D1_9002_0080C732DDC2__INCLUDED_)
