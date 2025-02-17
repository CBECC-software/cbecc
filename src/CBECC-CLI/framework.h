#pragma once

#define _HAS_AUTO_PTR_ETC 1      // ISO C++ 17 std compatibility - SAC 09/14/23

#include "targetver.h"
#include <stdio.h>
#include <process.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <ctype.h>
#include <assert.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs

#define NOMINMAX                 // prevent:  warning C4003: not enough actual parameters for macro 'min'   w/ inclusion of QtCore\QDateTime.h  - SAC 2/20/17  - SAC 02/13/25

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Control
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#pragma warning(disable : 4100 4996)
#include <boost/algorithm/string.hpp>
#pragma warning(default : 4100 4996)
#include <boost/algorithm/string/compare.hpp>
#include <boost/format.hpp>

#pragma warning(disable : 4127)
#include <QtCore/QString.h>
#include <QtCore/QStringList.h>
#include <QtCore/QDateTime.h>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QVector>
#pragma warning(default : 4127)
