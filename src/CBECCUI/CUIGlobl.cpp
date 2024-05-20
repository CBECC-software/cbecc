// CUIGlobl.cpp : Defines the PNL Comply External Objects
//
/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2017, Wrightsoft Corporation
 *  All rights reserved.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the California Energy Commission nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION,
 *  WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF
 *  THIS SOFTWARE (COLLECTIVELY, THE "AUTHORS") BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE
 *  SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING TO
 *  THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES,
 *  STRICT LIABILITY OR OTHERWISE.
 **********************************************************************/

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "CUIGlobl.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "ComplianceUI.h"
#include "mainfrm.h"
// #include "Screens.h"
#include "ctl_edit.h"
//32 #include "ctl_cmbb.h"

#ifdef UI_CANRES
#include "..\BEMCmpMgr\BEMCmpMgrCom.h"
#elif UI_CARES
#include "..\BEMCmpMgr\BEMCmpMgrRes.h"
#else
#include "..\BEMCmpMgr\BEMCmpMgrRes.h"
#endif

#include "ComplianceUIDoc.h"

#include "..\BEMProcUI\BEMProcUIX.h"

#include <stdio.h>
#include <io.h>
#include "Shlwapi.h"

#include <QtWidgets/qapplication.h>
#include <QtGui/QBrush>


/////////////////////////////////////////////////////////////////////////////
// Application wide externals

//static char BASED_CODE szStaticCUIVersion[] = "CBECC, Version 1.1, Release 1";
//const char* szCUIVersion = szStaticCUIVersion;

HINSTANCE ehCBECCInstance = NULL;
int       eiDeveloperMenu = 0;
int       eiAllowDisplayOfDetailedInputs = 0;

int appCXFullScreen;
int appCYFullScreen;
int appXScreenBase;
int appYScreenBase;

float appXRatio;
float appYRatio;

BOOL ebAppInitialized = FALSE;
BOOL ebInitiateProjectCreation = TRUE;
BOOL ebInitiateBatchProcViaStartDlg = FALSE;	// SAC 11/14/17
BOOL ebDisplayAllUIControls = FALSE;
BOOL ebAnalysisRangeChecks = TRUE;
BOOL ebShowHelpFollowingWizard = TRUE;  // SAC 2/14/01
BOOL ebIncludeCompParamStrInToolTip = FALSE;   // SAC 1/19/12
BOOL ebIncludeLongCompParamStrInToolTip = FALSE;   // SAC 8/13/13
BOOL ebIncludeStatusStrInToolTip = TRUE;       // SAC 1/19/12
BOOL ebVerboseInputLogging = FALSE;       // SAC 3/5/12
BOOL ebLogProjectOpen = FALSE;		// SAC 4/15/18

int eiCurrentTab = 0;

int eiTabDlgCtrlDY;
int eiTabDlgCtrlMarg;

int fntHtBase, fntWdBase, fntHtSys, fntWdSys;
int sysFntSize;
int eiFontScalePct = 100;

BOOL ebOpeningCommandLineFile = FALSE;  // SAC 1/1/01
CRecentFileList* epMRU = NULL;  // SAC 1/2/01

InterfaceMode eInterfaceMode = IM_INPUT;
CString esOverviewPDF;
CString esUserManualPDF;	// SAC 7/8/13
#ifdef UI_CANRES
	#ifdef UI_PROGYEAR2016
   CString esProgramName = "CBECC-Com";    // SAC 9/2/14
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "cibd16", "cpbd16", "cbbd16" };
	#elif  UI_PROGYEAR2019
   CString esProgramName = "CBECC-Com";    // SAC 9/2/14
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "cibd19", "cpbd19", "cbbd19" };
	#elif  UI_PROGYEAR2022
   CString esProgramName = "CBECC";        // SAC 05/19/22
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "cibd22", "cpbd22", "cbbd22" };
	#else
   CString esProgramName = "CBECC-Com";    // SAC 9/2/14
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "cibd", "cpbd", "cbbd" };
	#endif
CString esDataModRulelist = "rl_DEFAULT";  // SAC 10/24/12
const char pcCharsNotAllowedInObjNames[] = { '"', ',', '\'', '!', ';', NULL };	// SAC 8/20/14
#elif UI_CARES
CString esProgramName = "CBECC-Res";    // SAC 9/2/14
	#ifdef UI_PROGYEAR2016
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "ribd16", "rpbd16", "rbbd16" };
	#elif  UI_PROGYEAR2019
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "ribd19", "rpbd19", "rbbd19" };
	#elif  UI_PROGYEAR2022
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "ribd22", "rpbd22", "rbbd22" };
	#else
	const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "ribd", "rpbd", "rbbd" };
	#endif
CString esDataModRulelist = "ProposedInput";  // SAC 10/24/12
const char pcCharsNotAllowedInObjNames[] = { '"', NULL };	// SAC 8/20/14
#else
CString esProgramName = "CBECC";    // SAC 9/2/14
const char* pszCUIFileExt[ NUM_INTERFACE_MODES ] = { "ibd", "pbd", "bbd" };
CString esDataModRulelist = "ProposedInput";  // SAC 10/24/12
const char pcCharsNotAllowedInObjNames[] = { '"', NULL };	// SAC 8/20/14
#endif

static char BASED_CODE szIntModeNotInp[] = "View Mode must be set to 'User Input' in order to edit building data.";
const char* szErrIntModeNotInp = szIntModeNotInp;

static char BASED_CODE szNotEditable[] = "The compliance ruleset has defined this data as not user editable.";
const char* szErrNotEditable = szNotEditable;


int eiCurAnalysisStep = AS_None;

static char BASED_CODE szSelRestore[] = "The Analysis option 'Restore User Design' must be selected before the building data can be edited.";
const char* szErrRestoreInp = szSelRestore;

UINT euiBDBObjClipFormat = 0;


//	// the names of each valid rulelist
//	static char BASED_CODE szRL1[] = "ProposedInput";
//	static char BASED_CODE szRL2[] = "PostProposedInput";
//	static char BASED_CODE szRL3[] = "ProposedHVACSizing";
//	static char BASED_CODE szRL4[] = "ProposedFinal";
//	static char BASED_CODE szRL5[] = "BudgetConversion";
//	static char BASED_CODE szRL6[] = "BudgetHVACSizing";
//	static char BASED_CODE szRL7[] = "BudgetFinal";
//	static char BASED_CODE szRL8[] = "FinalCompliance";
//	const char* epszRLs[] = { szRL1, szRL2, szRL3, szRL4, szRL5, szRL6, szRL7, szRL8 };
//	
//	// the names of each WIZARD rulelist
//	static char BASED_CODE szWRL1[] = "WizardInput";
//	static char BASED_CODE szWRL2[] = "PostWizardInput";
//	const char* epszWRLs[] = { szWRL1, szWRL2 };


/////////////////////////////////////////////////////////////////////////////
// External Pens

CPen windowPen;
CPen dialogPen;
CPen blackDotPen;
CPen blackPen;
//CPen greyPen;
CPen btnHighlightPen;
CPen btnShadowPen;

/////////////////////////////////////////////////////////////////////////////
// External Brushes

CBrush buttonBrush;
CBrush whiteBrush;
CBrush blackBrush;
CBrush greyBrush;
CBrush darkGreyBrush;

/////////////////////////////////////////////////////////////////////////////
// External Fonts

CFont menuFont;
CFont toolBarFont;
CFont vSmallFont;
CFont stdFont;
CFont boldFont;
CFont unitsFont;
CFont dataTypeFont;
CFont vDataTypeFont;
CFont underlineFont;
CFont italicFont;
CFont italicUndFont;

static char BASED_CODE arial[]   = "Arial";
static char BASED_CODE arialB[]  = "Arial Bold";
static char BASED_CODE arialBI[] = "Arial Bold Italic";
static char BASED_CODE arialI[]  = "Arial Italic";
static char BASED_CODE timesB[]  = "Times New Roman Bold";

/////////////////////////////////////////////////////////////////////////////
// Static Font Sizes

static int stdFontHt;
static int boldFontHt;
static int menuFontHt;
static int toolBarFontHt;
static int vSmallFontHt;
static int unitsFontHt;
static int dataTypeFontHt;


/////////////////////////////////////////////////////////////////////////////
// Misc Character Strings
                  
CString esProgramPath = "";
CString esDataPath = "";
CString esAltWeatherPath = "";	// SAC 6/3/20
CString esProjectsPath = "";
CString esProgramFName = "";   // SAC 8/19/11
CString iniFileName = "";
CString esProgINIPathFile = "";
CString esDataINIPathFile = "";
CString esProxyINIPathFile = "";		// SAC 1/4/17
CString esCUIVersion = "";


/////////////////////////////////////////////////////////////////////////////
// Functions to initialize externals

//16 extern void RegisterControls()
//16 {
//16    BOOL regOK = FALSE;
//16 
//16    regOK = CEditCtl::RegisterMyClass();
//16  
//16    regOK = CComboBoxCtl::RegisterMyClass();
//16 
//16    return;
//16 }

static void LoadDefaultTextColors();

static CWnd* spMainWnd = NULL;


void SetExternals( CWnd* pWnd )
{
   ASSERT( pWnd );
   spMainWnd = pWnd;

   euiBDBObjClipFormat = ::RegisterClipboardFormat("BEMProc Object");

	ebLogProjectOpen = (ReadProgInt( "options", "LogProjectOpen", 0 ) > 0);		// SAC 4/15/18

   appXScreenBase = 640;
   appYScreenBase = 480;

   appCXFullScreen = GetSystemMetrics(SM_CXFULLSCREEN);
   appCYFullScreen = GetSystemMetrics(SM_CYFULLSCREEN) - GetSystemMetrics(SM_CYMENU);

   appXRatio = ((float) appCXFullScreen)/((float) appXScreenBase);
   appYRatio = ((float) appCYFullScreen)/((float) appYScreenBase);

   fntHtBase = 16;
   fntWdBase =  7;
	eiFontScalePct = ReadProgInt( "options", "ScreenScalePercent", 100 );
	BEMPUIX_SetScreenScalePercent( eiFontScalePct );

	CDC* pDC = pWnd->GetDC();
   
   TEXTMETRIC tm;
   pDC->GetTextMetrics(&tm);
   fntHtSys = tm.tmHeight;
   fntWdSys = tm.tmAveCharWidth;
   
   // Compute the System Font size, in tenths of a point.
   const int TenthsOfAPointPerInch = 720;
	int yDPI = pDC->GetDeviceCaps(LOGPIXELSY);
   sysFntSize = MulDiv(fntHtSys, TenthsOfAPointPerInch, yDPI);
   
   pWnd->ReleaseDC(pDC);

   int toolBtnHt    = ( 20 *fntHtSys)/fntHtBase;

   eiTabDlgCtrlDY   = FontY( 30 );
   eiTabDlgCtrlMarg = FontY(  7 );

   InitBEMDBIDs();

   //////////////////////////////////////////////////////////////////////////
   // External Fonts

   stdFontHt        = (16*fntHtSys)/fntHtBase;
   boldFontHt       = (16*fntHtSys)/fntHtBase;
   menuFontHt       = int (36.0*appYRatio);
   toolBarFontHt    = int (toolBtnHt*0.78*eiFontScalePct/100);
   vSmallFontHt     = (15*fntHtSys)/fntHtBase;
   unitsFontHt      = (13*fntHtSys)/fntHtBase;
//   unitsFontHt      = (15*fntHtSys)/fntHtBase;
   dataTypeFontHt   = (12*fntHtSys)/fntHtBase;

   menuFont.CreateFont( menuFontHt,   // height
                          0, 0, 0,              // width, escapement, orientation
                          700, 0, 0, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arialB );                    // font name
   toolBarFont.CreateFont( toolBarFontHt,      // height
                          0, 0, 0,              // width, escapement, orientation
                          0, 0, 0, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arial );                    // font name
   vSmallFont.CreateFont( vSmallFontHt,   // height
                           0, 900, 900,      // width, escapement, orientation
                           0, 0,   0,   0,   // weight, italic, underline, strike-out
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          DEFAULT_QUALITY,           // quality
                          DEFAULT_PITCH | FF_SWISS,  // pitch & family
                          arial );                    // font name

   stdFont.CreateFont( stdFontHt,  // height
                          0, 0, 0,              // width, escapement, orientation
                          0, 0, 0, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arial );                    // font name
   boldFont.CreateFont( boldFontHt,  // height
                          0, 0, 0,              // width, escapement, orientation
                          650, 0, 0, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arial );                    // font name
   unitsFont.CreateFont( unitsFontHt,   // height
                          0, 0, 0,      // width, escapement, orientation
                          0, 0, 0, 0,   // weight, italic, underline, strike-out
                         ANSI_CHARSET,              // char set
                         OUT_DEFAULT_PRECIS,        // out precision
                         CLIP_DEFAULT_PRECIS,       // clip precision
                         DEFAULT_QUALITY,           // quality
                         DEFAULT_PITCH | FF_SWISS,  // pitch & family
                         arial );                    // font name
   dataTypeFont.CreateFont( dataTypeFontHt,   // height
                          0, 0, 0,      // width, escapement, orientation
                          0, 0, 0, 0,   // weight, italic, underline, strike-out
                         ANSI_CHARSET,              // char set
                         OUT_DEFAULT_PRECIS,        // out precision
                         CLIP_DEFAULT_PRECIS,       // clip precision
                         DEFAULT_QUALITY,           // quality
                         DEFAULT_PITCH | FF_SWISS,  // pitch & family
                         arial );                    // font name
   vDataTypeFont.CreateFont( dataTypeFontHt,   // height
                          0, 900, 900,      // width, escapement, orientation
                          0, 0, 0, 0,   // weight, italic, underline, strike-out
                         ANSI_CHARSET,              // char set
                         OUT_DEFAULT_PRECIS,        // out precision
                         CLIP_DEFAULT_PRECIS,       // clip precision
                         DEFAULT_QUALITY,           // quality
                         DEFAULT_PITCH | FF_SWISS,  // pitch & family
                         arial );                    // font name
   underlineFont.CreateFont( stdFontHt,  // height
                          0, 0, 0,              // width, escapement, orientation
                          0, 0, 1, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arial );                    // font name
   italicFont.CreateFont( stdFontHt,  // height
                          0, 0, 0,              // width, escapement, orientation
                          0, 1, 0, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arialI );                    // font name
   italicUndFont.CreateFont( stdFontHt,  // height
                          0, 0, 0,              // width, escapement, orientation
                          0, 1, 1, 0,         // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_DEFAULT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          FF_SWISS,                  // pitch & family
                          arialI );                  // font name

   //////////////////////////////////////////////////////////////////////////
   // External Pens

   windowPen.CreatePen(       PS_SOLID, 1, ::GetSysColor( COLOR_WINDOW ) );
   dialogPen.CreatePen(       PS_SOLID, 1, ::GetSysColor( COLOR_BTNFACE ) );
   blackDotPen.CreatePen(     PS_DOT  , 1, RGB(0,0,0) );
   blackPen.CreatePen(        PS_SOLID, 1, RGB(0,0,0) );
//   greyPen.CreatePen(         PS_SOLID, 1, RGB(192,192,192) );
   btnHighlightPen.CreatePen( PS_SOLID, 1, ::GetSysColor( COLOR_BTNHIGHLIGHT ) ); // RGB(255,255,255) );
   btnShadowPen.CreatePen(    PS_SOLID, 1, ::GetSysColor( COLOR_BTNSHADOW    ) ); // RGB(128,128,128) );


   //////////////////////////////////////////////////////////////////////////
   // External Brushes

   buttonBrush.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
   whiteBrush.CreateSolidBrush(    RGB(255,255,255) );
   blackBrush.CreateSolidBrush(    RGB(  0,  0,  0) );
   greyBrush.CreateSolidBrush(     RGB(192,192,192) );
   darkGreyBrush.CreateSolidBrush( RGB(128,128,128) );

   // read in default text display colors from .INI file
   LoadDefaultTextColors();
}

/////////////////////////////////////////////////////////////////////////////

BOOL LoadVersionInfoString( CString& sReturnString, const char* pszInfoID, const char* pszPre, const char* pszPost )
{
   sReturnString.Empty();

   // get the .exe path
   char    szFullPath[256];
   GetModuleFileName ( NULL, szFullPath, sizeof(szFullPath) );
   // Now lets dive in and pull out the version information:
   DWORD dwVerHnd;
   DWORD dwVerInfoSize = GetFileVersionInfoSize( szFullPath, &dwVerHnd );
   if (dwVerInfoSize)
   {
      LPSTR   lpstrVffInfo;
      HANDLE  hMem;
      hMem = GlobalAlloc( GMEM_MOVEABLE, dwVerInfoSize );
      lpstrVffInfo = (char*) GlobalLock( hMem );
      GetFileVersionInfo( szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo );

      // Set the title of the dialog:
      LPSTR lpVersion;         // String pointer to 'version' text
      char  szGetName[256];
      UINT  uVersionLen;
      lstrcpy( szGetName, GetStringResource(IDS_VER_INFO_LANG) );
      //WORD wRootLen = (WORD) lstrlen( szGetName ); // Save this position
      lstrcat( szGetName, pszInfoID );
      if (VerQueryValue( (LPVOID)  lpstrVffInfo,
                         (LPSTR)   szGetName,
                         (LPVOID*) &lpVersion,
                         (UINT *)  &uVersionLen))
      {
         if (pszPre)
            sReturnString = pszPre;

         sReturnString += lpVersion;

         if (pszPost)
            sReturnString += pszPost;

         return TRUE;
      }
   }
   return FALSE;
}


//void DrawWin95Shadow( CDC* pDC, int left, int top, int right, int bottom )
//{
//   int tempDC = pDC->SaveDC();
//
//   // draw Win95-like shadow around block
//   pDC->SelectObject( &darkGreyPen );
//   pDC->MoveTo( left -2, bottom   );
//   pDC->LineTo( left -2, top   -2 );
//   pDC->LineTo( right+1, top   -2 );
//
//   pDC->SelectObject( &btnHighlightPen );
//   pDC->MoveTo( right+1, top   -2 );
//   pDC->LineTo( right+1, bottom+1 );
//   pDC->LineTo( left -3, bottom+1 );
//
//   pDC->SelectObject( &blackPen );
//   pDC->MoveTo( left -1, bottom-1 );
//   pDC->LineTo( left -1, top   -1 );
//   pDC->LineTo( right  , top   -1 );
//
//   pDC->SelectObject( &greyPen );
//   pDC->MoveTo( right  , top   -1 );
//   pDC->LineTo( right  , bottom   );
//   pDC->LineTo( left -2, bottom   );
//
//   pDC->RestoreDC( tempDC );
//}


/////////////////////////////////////////////////////////////////////////////
// QT UI initialization

QApplication* sq_app = NULL;	// SAC 3/8/18
bool sbQtAppInited = false;

bool QAppInitialized()
{
	if (!sbQtAppInited)
	{
		int argc = 0;
		sq_app = new QApplication( argc, NULL );
		if (sq_app)
			sbQtAppInited = true;
		ASSERT( sbQtAppInited );
	}
	return sbQtAppInited;
}

void BlastQApp()
{
	if (sbQtAppInited)
	{	delete sq_app;
		sq_app = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Font Related Functions

CFont* GetCUIFont( int fontType )
{
   CFont* fontPtr = &stdFont;
   if (fontType == FNT_STD)
      fontPtr = &stdFont;
   else if (fontType == FNT_BOLD)
      fontPtr = &boldFont;
   else if (fontType == FNT_UNITS)
      fontPtr = &unitsFont;
   else if (fontType == FNT_MENU)
      fontPtr = &menuFont;
   else if (fontType == FNT_TOOLBAR)
      fontPtr = &toolBarFont;
   else if (fontType == FNT_VSMALL)
      fontPtr = &vSmallFont;
   else if (fontType == FNT_DATATYPE)
      fontPtr = &dataTypeFont;
   else if (fontType == FNT_VDATATYPE)
      fontPtr = &vDataTypeFont;
   else if (fontType == FNT_UNDERLINE)
      fontPtr = &underlineFont;
   else if (fontType == FNT_ITALIC)
      fontPtr = &italicFont;
   else if (fontType == FNT_ITALUNDER)
      fontPtr = &italicUndFont;

   return fontPtr;
}

int GetCUIFontHeight( int fontType )
{
   int retVal = 0;
   if (fontType == FNT_STD)
      retVal = stdFontHt;
   else if (fontType == FNT_BOLD)
      retVal = boldFontHt;
   else if (fontType == FNT_UNITS)
      retVal = unitsFontHt;
   else if (fontType == FNT_MENU)
      retVal = menuFontHt;
   else if (fontType == FNT_TOOLBAR)
      retVal = toolBarFontHt;
   else if (fontType == FNT_VSMALL)
      retVal = vSmallFontHt;
   else if ( (fontType == FNT_DATATYPE) || (fontType == FNT_VDATATYPE) )
      retVal = dataTypeFontHt;
   else if (fontType == FNT_UNDERLINE)
      retVal = stdFontHt;
   else if (fontType == FNT_ITALIC)
      retVal = stdFontHt;
   else if (fontType == FNT_ITALUNDER)
      retVal = stdFontHt;

   return retVal;
}


/////////////////////////////////////////////////////////////////////////////
// Misc INI File Stuff

void GetProgramPath()
{
   char 		path[_MAX_PATH];
   CString  drive;
   CString  dir;
	CString  fName;   // SAC 8/19/11 - added to enable multiple EXE names
   if(::GetModuleFileName(AfxGetResourceHandle(), path, _MAX_PATH))
   {
      _splitpath(path, drive.GetBuffer(_MAX_DRIVE), dir.GetBuffer(_MAX_DIR), fName.GetBuffer(_MAX_FNAME), NULL);
      drive.ReleaseBuffer();
      dir.ReleaseBuffer();
      fName.ReleaseBuffer();
   }
   esProgramPath = drive + dir;
   esProgramFName = fName;

#ifdef UI_CANRES
 #ifdef UI_PROGYEAR2016
	esOverviewPDF   = esProgramPath + "CBECC-Com16_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + "CBECC-Com16_UserManual.pdf";			// SAC 7/8/13
 #elif  UI_PROGYEAR2019
	esOverviewPDF   = esProgramPath + "CBECC-Com19_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + "CBECC-Com19_UserManual.pdf";			// SAC 4/26/17
 #elif  UI_PROGYEAR2022
	esOverviewPDF   = esProgramPath + "CBECC-22_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + "CBECC-22_UserManual.pdf";			// SAC 6/19/19
 #else
 	esOverviewPDF   = esProgramPath + "CBECC-Com_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + "CBECC-Com_UserManual.pdf";			// SAC 7/8/13
 #endif
#elif UI_CARES
	esOverviewPDF   = esProgramPath + "CBECC-Res_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + "CBECC-Res_UserManual.pdf";			// SAC 7/8/13
#else
	esOverviewPDF   = esProgramPath + esProgramFName + "_QuickStartGuide.pdf";
	esUserManualPDF = esProgramPath + esProgramFName + "_UserManual.pdf";			// SAC 7/8/13
#endif

//   return (drive + dir);
}

BOOL ResolvePathIndirections( CString& sPath )  // SAC 10/23/12
{	BOOL bRetVal = TRUE;
	int iFirstDotDot = sPath.Find("\\..");
	while (bRetVal && iFirstDotDot >= 0)
	{	CString sTemp = sPath.Left( iFirstDotDot );
		int iPrevSlash = sTemp.ReverseFind('\\');
		if (iPrevSlash < 0)
		{	ASSERT( FALSE );
			bRetVal = FALSE;  // # '..'s moving up path exceed depth of path
		}
		else
		{	sTemp = sTemp.Left( iPrevSlash ) + sPath.Right( sPath.GetLength() - iFirstDotDot - 3 );
			sPath = sTemp;								ASSERT( !sPath.IsEmpty() );
			bRetVal = (!sPath.IsEmpty());
		}
		iFirstDotDot = sPath.Find("\\..");
	}
	return bRetVal;
}

inline const char* GetINIFilePtr( const char* szSection, const char* szKey )
{  BOOL bProgINI  = (strcmp( szSection, "paths" ) == 0 && strcmp( szKey, "DataPath" ) == 0);
	BOOL bProxyINI = (strcmp( szSection, "proxy" ) == 0);		// SAC 1/4/17
   return (const char*) (bProgINI ? esProgINIPathFile : (bProxyINI ? esProxyINIPathFile : esDataINIPathFile));
}

UINT ReadProgInt(LPCSTR section, LPCSTR entry, int def)
{
//   CString fileName = esProgramPath + iniFileName;
   return ::GetPrivateProfileInt( section, entry, def, GetINIFilePtr( section, entry ) /*fileName*/ );
}

CString ReadProgString(LPCSTR section, LPCSTR entry, LPCSTR def, BOOL bGetPath)
{
//   CString fileName = esProgramPath + iniFileName;
	char buffer[_MAX_PATH];
   ::GetPrivateProfileString(section, entry, "", buffer, _MAX_PATH, GetINIFilePtr( section, entry ) /*fileName*/ );

   // If not loaded, try grabbing default for section
   if (strlen(buffer) == 0)
      ::GetPrivateProfileString(section, "default", def, buffer, _MAX_PATH, GetINIFilePtr( section, entry ) /*fileName*/ );
//   return CString(buffer);

   CString sPath = buffer;
// SAC 1/6/13 - added code to ensure that ALL "paths" retrieved from INI file include a trailing '\'
	CString sSection = section;
	if (bGetPath && !sSection.Compare("paths") && sPath.GetLength() && sPath[sPath.GetLength()-1] != '\\')
		sPath += '\\';
   //if (bGetPath && sPath.Find(':'))    - SAC 9/26/13 - revised code to PREVENT program or data path from being prepended if current path begins w/ '\' or '/'
   if (bGetPath && sPath.Find(':') < 0 && sPath.Find('\\') != 0 && sPath.Find('/') != 0) 
//      sPath = esProgramPath + sPath;
	{  CString sEntry = entry;
		if (sEntry.Find( "Prog" ) >= 0 || sEntry.Find( "Data" ) >= 0 || sEntry.Find( "Proj" ) >= 0)
//		if (sEntry.Find( "DataPath" ) >= 0)
         sPath = esProgramPath + sPath;
		else
         sPath = esDataPath + sPath;
         // sPath = esProjectsPath + sPath;  - any case where we want Projects path here?
	}
	if (bGetPath && sPath.Find("\\..") >= 0)
		VERIFY( ResolvePathIndirections( sPath ) );  // SAC 10/23/12

   return sPath;
}

BOOL WriteProgInt(LPCSTR section, LPCSTR entry, int value)
{
	CString valString;
	valString.Format("%d", value);
	return WriteProgString( section, entry, valString );
}

BOOL WriteProgString(LPCSTR section, LPCSTR entry, LPCSTR string)
{
//   CString fileName = esProgramPath + iniFileName;
	return WritePrivateProfileString( section, entry, string, GetINIFilePtr( section, entry ) /*fileName*/ );
}


/////////////////////////////////////////////////////////////////////////////

// transfer Proxy settings from Data INI file into Proxy-specific file (w/ encryption) - SAC 1/4/17
void TransferProxyINISettings()
{
		// no longer used:
		// ; NetComLibrary - network communications software library - options include:
		// ;    QT      (new default)
		// ;    CURL    (used in past releases)
		// ;NetComLibrary=CURL
	int iUseProxyServerSettings;
	CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
	iUseProxyServerSettings = ReadProgInt(    "options", "UseProxyServerSettings", -1 /*invalid setting*/ );
	sProxyServerAddress		= ReadProgString( "options", "ProxyServerAddress"    , "", FALSE );
	sProxyServerCredentials	= ReadProgString( "options", "ProxyServerCredentials", "", FALSE );
	sProxyServerType      	= ReadProgString( "options", "ProxyServerType"       , "", FALSE );
	if (iUseProxyServerSettings < 1 && sProxyServerAddress.IsEmpty() &&
			sProxyServerCredentials.IsEmpty() && sProxyServerType.IsEmpty())
	{	// OLD INI settings not present (or active) so IGNORE INI switch
	}
	else
	{	// TRANSFER proxy settings from old INI to Proxy INI
		if (iUseProxyServerSettings < 0)
			iUseProxyServerSettings = 1;  // default in this case
		VERIFY( WriteProgInt( "proxy"  , "UseProxyServerSettings", iUseProxyServerSettings ) );
		WritePrivateProfileString( "options", "UseProxyServerSettings", NULL, GetINIFilePtr( "options", "UseProxyServerSettings" ) /*fileName*/ );  // REMOVES old INI item

		if (!sProxyServerType.IsEmpty())
		{	VERIFY( WriteProgString( "proxy", "ProxyServerType", sProxyServerType ) );
			WritePrivateProfileString(  "options", "ProxyServerType", NULL, GetINIFilePtr( "options", "ProxyServerType" ) /*fileName*/ );  // REMOVES old INI item
		}
		if (!sProxyServerAddress.IsEmpty())
		{	VERIFY( WriteProgString( "proxy", "ProxyServerAddress", sProxyServerAddress ) );
			WritePrivateProfileString(  "options", "ProxyServerAddress", NULL, GetINIFilePtr( "options", "ProxyServerAddress" ) /*fileName*/ );  // REMOVES old INI item
		}
		if (!sProxyServerCredentials.IsEmpty())
		{
			bool bCMSecure = CMX_SecureExecutable();
			CString sNewINIOptName = (bCMSecure ? "SecProxyServerCredentials" : "InsProxyServerCredentials");  // secure vs. insecure (documenting encoding)
			char strEncoded[1024];
			memset( strEncoded, 0, sizeof(char)*1024 );
			long lEncdRet = CMX_EncodeBase64( (const unsigned char*) ((const char*) sProxyServerCredentials), sProxyServerCredentials.GetLength(), strEncoded, 1024, true );
			ASSERT( lEncdRet > 0 );
			if (lEncdRet > 0)
			{	
				VERIFY( WriteProgString( "proxy", sNewINIOptName, strEncoded ) );
				WritePrivateProfileString( "options", "ProxyServerCredentials", NULL, GetINIFilePtr( "options", "ProxyServerCredentials" ) /*fileName*/ );  // REMOVES old INI item
			}
		}
				// ; Proxy Server Settings
				// ;UseProxyServerSettings=1
				// ;ProxyServerAddress=site.site:port
				// ;ProxyServerCredentials=username:password
				// ; Proxy Server Type - options include:
				// ;    Socks5     (Qt default)
				// ;    Default
				// ;    No
				// ;    Http     (CBECC default)
				// ;    HttpCaching
				// ;    FtpCaching
				// ProxyServerType=Http
	}
}


BOOL GetEncodedSetting( LPCSTR section, LPCSTR entry, CString& sOption )
{	sOption.Empty();
	bool bCMSecure = CMX_SecureExecutable();
	CString sSecININame = "Sec";		sSecININame += entry;
	CString sInsININame = "Ins";		sInsININame += entry;
	CString sSettingFromINI;
	char strDecoded[1024];
	if (bCMSecure)
	{	sSettingFromINI = ReadProgString( section, sSecININame, "" /*default*/ /*, BOOL bGetPath*/ );
		if (!sSettingFromINI.IsEmpty())
		{	// secure EXEs and secure option present and retrieved - so return that
			memset( strDecoded, 0, sizeof(char)*1024 );
			int iDecdRet = CMX_DecodeBase64( strDecoded, sSettingFromINI, true );
			ASSERT( iDecdRet > 0 );
			if (iDecdRet > 0)
				sOption = strDecoded;
	}	}
	if (sOption.IsEmpty())
	{	// if sOption not defined above...
		sSettingFromINI = ReadProgString( section, sInsININame, "" /*default*/ /*, BOOL bGetPath*/ );
		if (!sSettingFromINI.IsEmpty())
		{	// secure EXEs and secure option present and retrieved - so return that
			memset( strDecoded, 0, sizeof(char)*1024 );
			int iDecdRet = CMX_DecodeBase64( strDecoded, sSettingFromINI, false );
			ASSERT( iDecdRet > 0 );
			if (iDecdRet > 0)
				sOption = strDecoded;
	}	}
	return (!sOption.IsEmpty());
}


// SAC 10/16/20 - based on BEMCmpMgr -- SAC 5/22/13 - Based on BEMTextIO::ParseCSVRecord()
int ParseCSVRecord( const char* pszParseStr, CStringArray& saCSVFields )
{
	int iRetVal = 0;
	int iParseLen = (int) strlen( pszParseStr );			assert( iParseLen > 0 );
	if (iParseLen > 0)
	{	CString string;
		saCSVFields.RemoveAll();
		int iChrIdx = 0;
   	char chr;
		BOOL bQuoteOpen=FALSE, bQuoteClosed=FALSE;
		while (iChrIdx <= (iParseLen-1))
		{
		   chr = pszParseStr[iChrIdx++];
			if (chr == '\"')
			{	if (!bQuoteOpen)
				{	// at beginning of quoted field
					bQuoteOpen = TRUE;
					bQuoteClosed = FALSE;
					if (!string.IsEmpty())
					{	assert( FALSE );		// string should be empty if/when we encounter an opening quote
						string.Empty();		// blast data loaded into string prior to encountering an opening quote ???
					}
				}
				else if (!bQuoteClosed)
				{	// at the end of quoted field
					bQuoteClosed = TRUE;
					saCSVFields.Add( string );
					string.Empty();
				}
				else
				{	assert( FALSE );	// quote found after end of quoted field but before following delimiter!!!
				}
			}
   		else if (chr == ',')
			{	if (bQuoteOpen && !bQuoteClosed)
					string += chr;		// delimeter included in quoted string...
				else if (bQuoteOpen && bQuoteClosed)
				{	// string already added to arry (@ closing quote), so all we need do here is reset to the quote BOOLs
					bQuoteOpen   = FALSE;
					bQuoteClosed = FALSE;
				}
				else if (!bQuoteOpen && !bQuoteClosed)
				{	// add unquoted string to array
					saCSVFields.Add( string );
					string.Empty();
				}
				else
				{	assert( FALSE );			// invalid condition where:  !bQuoteOpen && bQuoteClosed
				}
			}
			else if (bQuoteOpen && bQuoteClosed)
			{	assert( chr == ' ' );		// allow for space chars to follow a quoted string (and preceding a delimeter or EOL)??
			}
			else
				string += chr;		// add character to string...
		}

		if (!string.IsEmpty())	// add trailing field (numeric, not followed by comma)
			saCSVFields.Add( string );

		iRetVal = (saCSVFields.GetSize() > 0 ? saCSVFields.GetSize() : 0);
	}
	
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// Change Program Directory

void ChangeProgDir(CString& mtrDir)
{
   CString drive;
   CString dir;
   _splitpath( (const char *) mtrDir, drive.GetBuffer( _MAX_DRIVE ), dir.GetBuffer( _MAX_DIR ), NULL, NULL );
   drive.ReleaseBuffer();
   dir.ReleaseBuffer();

   if (drive.GetLength() != 0)
   {
      int nDrive = drive[0] - ( (drive[0] <= 'Z') ? 'A' : 'a' ) + 1;			ASSERT( nDrive > 0 && nDrive < 27 );
      if ( (_chdrive( nDrive ) == 0) && (dir.GetLength() > 0) )
      {
         int nChars = dir.GetLength();
         if ( (nChars > 1) && (dir[ nChars-1 ] == '\\') )
            nChars--;
         _chdir( dir.Left(nChars).GetBuffer(0) );
      }
   }
}

void ChangeProgDir(LPCSTR section, LPCSTR entry)
{
   CString mtrDir = ReadProgString( section, entry, "");
   if(mtrDir.GetLength() != 0)
   {
      if (mtrDir.Find(':') < 0) 
//         mtrDir = esProgramPath + mtrDir;
		{  CString sEntry = entry;
			if (sEntry.Find( "Prog" ) >= 0)
	         mtrDir = esProgramPath + mtrDir;
			else if (sEntry.Find( "Data" ) >= 0)
	         mtrDir = esDataPath + mtrDir;
			else if (sEntry.Compare( "ProjectsPath" ) == 0 && !esProjectsPath.IsEmpty())	// SAC 9/2/14 - added to prevent return of bogus proj dir
				mtrDir = esProjectsPath;
			else
	         mtrDir = esProjectsPath + mtrDir;
		}
      ChangeProgDir( mtrDir );
   }
}


/////////////////////////////////////////////////////////////////////////////
// Get program version ID

BOOL GetProgramVersion(CString& sProgVer, BOOL bPrependName, BOOL bLongVer)
{
	BOOL bRetVal = FALSE;
	sProgVer.Empty();

	CString sProgPathFile = esProgramPath + esProgramFName;
	sProgPathFile += ".exe";
	DWORD  verHandle = NULL;
	UINT   size	  = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = GetFileVersionInfoSize( sProgPathFile, &verHandle);
	int major=0, minor=0, build=0;
	if (verSize != NULL)
	{	LPSTR verData = new char[verSize];
		if (GetFileVersionInfo( sProgPathFile, verHandle, verSize, verData))
		{	if (VerQueryValue(verData,"\\",(VOID FAR* FAR*)&lpBuffer,&size))
			{	if (size)
				{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{	major = HIWORD(verInfo->dwFileVersionMS);
						minor = LOWORD(verInfo->dwFileVersionMS);
						build = verInfo->dwFileVersionLS;
						bRetVal = TRUE;
					}
				}
			}
		}
		delete[] verData;
	}
	if (bRetVal)
	{
	//{	CString sVerLetter;
	//	while (minor > 26)
	//	{	sVerLetter += 'z';
	//		minor -= 26;
	//	}
	//	sVerLetter += char('a' + minor - 1);
	// SAC 9/10/13 - revised minor labeling scheme above (a-z, za-zz, zza-zzz...) to below (a-z, aa-az, ba-bz...) (per Bruce's request)
//		if (minor == 100)		// SAC 8/7/14 - added special minor ver ID values 100 & 101 => alpha & beta
//			sVerLetter = "-alpha";
//		else if (minor == 101)
//			sVerLetter = "-beta";
//		else if (minor > 0)
//		{	minorLead = (minor-1) / 26;
//			if (minorLead > 0)
//				sVerLetter += char('a' + (minorLead-1));
//			sVerLetter += char('a' + (minor % 26) - 1);
//		}
//
//		if (bLongVer)
//			sProgVer.Format( "2013-%d%s (%d)", major, sVerLetter, build );
//		else
//			sProgVer.Format( "2013-%d%s", major, sVerLetter );


#ifdef UI_PROGYEAR2016
		//CString sCodeYr = "2016";
	// SAC 10/29/15 - implemented new numbering scheme - defined in CEC LF e-mail 10/2/15
		int iMiddleNum = (int) floor( minor / 100.0 );
		int iMinorNum = (int) floor( minor / 10.0 ) - (iMiddleNum * 10);
		int iAlphBeta = minor % 10;
		CString sAlphBeta;
		switch (iAlphBeta)
		{	case  0 :	break;
			case  1 :	sAlphBeta = " Alpha";		break;
			case  2 :	sAlphBeta = " Alpha 2";		break;
			case  3 :	sAlphBeta = " Alpha 3";		break;
			case  4 :	sAlphBeta = " Beta";			break;
			case  5 :	sAlphBeta = " Beta 2";		break;
			case  6 :	sAlphBeta = " RV";			break;	// SAC 12/22/17
			case  7 :	sAlphBeta = " RC";			break;
			case  8 :	sAlphBeta = " SP1";			break;
			case  9 :	sAlphBeta = " SP2";			break;
			default :	sAlphBeta = " ????" ;		break;
		}
		if (bLongVer)
			sProgVer.Format( "%d.%d.%d%s (%d)", major, iMiddleNum, iMinorNum, sAlphBeta, build );
		else
			sProgVer.Format( "%d.%d.%d%s", major, iMiddleNum, iMinorNum, sAlphBeta );
#elif  UI_PROGYEAR2019
		//CString sCodeYr = "2019";
	// SAC 10/29/15 - implemented new numbering scheme - defined in CEC LF e-mail 10/2/15
	// SAC 11/27/18 - altered to allow 2-digit iMinorNum (by increasing iMiddleNum multiplier *10)
		int iMiddleNum = (int) floor( minor / 1000.0 );
		int iMinorNum = (int) floor( minor / 10.0 ) - (iMiddleNum * 100);
		int iAlphBeta = minor % 10;
		CString sAlphBeta;
		switch (iAlphBeta)
		{	case  0 :	break;
			case  1 :	sAlphBeta = " Alpha";		break;
			case  2 :	sAlphBeta = " Alpha 2";		break;
			case  3 :	sAlphBeta = " Alpha 3";		break;
			case  4 :	sAlphBeta = " Beta";			break;
			case  5 :	sAlphBeta = " Beta 2";		break;
			case  6 :	sAlphBeta = " RV";			break;	// SAC 12/22/17
			case  7 :	sAlphBeta = " RC";			break;
			case  8 :	sAlphBeta = " SP1";			break;
			case  9 :	sAlphBeta = " SP2";			break;
			default :	sAlphBeta = " ????" ;		break;
		}
		if (bLongVer)
			sProgVer.Format( "%d.%d.%d%s (%d)", major, iMiddleNum, iMinorNum, sAlphBeta, build );
		else
			sProgVer.Format( "%d.%d.%d%s", major, iMiddleNum, iMinorNum, sAlphBeta );
#elif  UI_PROGYEAR2022
		//CString sCodeYr = "2022";
	// SAC 10/29/15 - implemented new numbering scheme - defined in CEC LF e-mail 10/2/15
	// SAC 11/27/18 - altered to allow 2-digit iMinorNum (by increasing iMiddleNum multiplier *10)
		int iMiddleNum = (int) floor( minor / 1000.0 );
		int iMinorNum = (int) floor( minor / 10.0 ) - (iMiddleNum * 100);
		int iAlphBeta = minor % 10;
		CString sAlphBeta;
		switch (iAlphBeta)
		{	case  0 :	break;
			case  1 :	sAlphBeta = " Alpha";		break;
			case  2 :	sAlphBeta = " Alpha 2";		break;
			case  3 :	sAlphBeta = " Alpha 3";		break;
			case  4 :	sAlphBeta = " Beta";			break;
			case  5 :	sAlphBeta = " Beta 2";		break;
			case  6 :	sAlphBeta = " RV";			break;	// SAC 12/22/17
			case  7 :	sAlphBeta = " RC";			break;
			case  8 :	sAlphBeta = " SP1";			break;
			case  9 :	sAlphBeta = " SP2";			break;
			default :	sAlphBeta = " ????" ;		break;
		}
		if (bLongVer)
			sProgVer.Format( "%d.%d.%d%s (%d)", major, iMiddleNum, iMinorNum, sAlphBeta, build );
		else
			sProgVer.Format( "%d.%d.%d%s", major, iMiddleNum, iMinorNum, sAlphBeta );
#else	// 2013
		CString sCodeYr = "2013";
		CString sVerLetter;
	// SAC 1/27/15 - revision to enable more flexible minor-minor number & '-beta'
		//	Minor Encoding:  XXYYZ -> XX is minor LETTER (1-a, 2-b...) | YY is minor NUMber | Z is test release (0-'', 1-alpha, 2-alpha 2, 3-alph3, 4-alph4, 5-beta, 6-beta 2, ...)
		int iMinorLtr = (int) floor( minor / 1000.0 );
		int iMinorNum = (int) floor( minor / 10.0 ) - (iMinorLtr * 100);
		int iAlphBeta = minor % 10;
		CString sMnrNum, sAlphBeta;
		if (iMinorLtr > 0)
		{	int minorLead = (iMinorLtr-1) / 26;
			if (minorLead > 0)
				sVerLetter += char('a' + (minorLead-1));
			sVerLetter += char('a' + (iMinorLtr % 26) - 1);
		}
		if (iMinorNum > 0)
			sMnrNum.Format( "%d", iMinorNum );
		switch (iAlphBeta)
		{	case  0 :	break;
			case  1 :	sAlphBeta = "-alpha";		break;
			case  2 :	sAlphBeta = "-alpha 2";		break;	// SAC 9/24/15 - updated from alpha/beta/gamma... to alpha/alpha2/alpha3...
			case  3 :	sAlphBeta = "-alpha 3";		break;
			case  4 :	sAlphBeta = "-alpha 4";		break;
			case  5 :	sAlphBeta = "-beta";			break;
			case  6 :	sAlphBeta = "-beta 2";		break;
			case  7 :	sAlphBeta = "-beta 3";		break;
			case  8 :	sAlphBeta = "-beta 4";		break;
			case  9 :	sAlphBeta = "-beta 5";		break;
			default :	sAlphBeta = "-????" ;		break;
		}
		if (bLongVer)
		{	if (major < 2 && iMinorLtr < 1 && iAlphBeta > 0)
				sProgVer.Format( "%s%s (%d)", sCodeYr, sAlphBeta, build );
			else
				sProgVer.Format( "%s-%d%s%s%s (%d)", sCodeYr, major, sVerLetter, sMnrNum, sAlphBeta, build );
		}
		else
		{	if (major < 2 && iMinorLtr < 1 && iAlphBeta > 0)
				sProgVer.Format( "%s%s", sCodeYr, sAlphBeta );
			else
				sProgVer.Format( "%s-%d%s%s%s", sCodeYr, major, sVerLetter, sMnrNum, sAlphBeta );
		}
#endif

		if (bPrependName)
		{
			sProgVer = esProgramName + CString(" ") + sProgVer;
		}
	}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// String Resource Retrieval
//
// FUNCTION:    GetStringRes (int id INPUT ONLY)
//
// COMMENTS:    Load the resource string with the ID given, and return a
//              pointer to it.  Notice that the buffer is common memory so
//              the string must be used before this call is made a second time.
/////////////////////////////////////////////////////////////////////////////

LPTSTR GetStringResource( int id )
{
  static TCHAR buffer[MAX_PATH];

  buffer[0]=0;
  LoadString (GetModuleHandle (NULL), id, buffer, MAX_PATH);
  return buffer;
}


/////////////////////////////////////////////////////////////////////////////
// Check for file existence

BOOL FileExists( QString& qsFileName )
{	return FileExists( qsFileName.toLatin1().constData() );
}

BOOL FileExists( const char* pszFileName )
{
	return (PathFileExists( (LPCTSTR) pszFileName ) != FALSE);
//   BOOL retVal = FALSE;
//   if (pszFileName && strlen(pszFileName) > 0)
//   {
//      FILE *pfTempFile = fopen( pszFileName, "r" );
//      if (pfTempFile != NULL)
//      {
//         fclose( pfTempFile );
//         retVal = TRUE;
//      }
//   }
//   return retVal;
}

BOOL DirectoryExists( const char* pszDirName )
{
   CString sDirName = pszDirName;
   int len = sDirName.GetLength();
   if (len > 0)
   {
      if (sDirName[len-1] != '\\')
         sDirName += '\\';
      sDirName += '.';

      struct _finddata_t c_file;
      long hFile = _findfirst( sDirName, &c_file );
      if (hFile != -1)
      {
         _findclose( hFile );
         return TRUE;
      }
   }
   return FALSE;
}

void CreateAndChangeDirectory( const char* pszDirName, BOOL bRemoveDir /*=FALSE*/ )  // SAC 2/12/07 - added argument to facilitate directory deletion
{
   CString mtrDir = pszDirName;
   if(mtrDir.GetLength() != 0)
   {
      CString drive;
      CString dir;

      _splitpath( (const char *) mtrDir, drive.GetBuffer( _MAX_DRIVE ), dir.GetBuffer( _MAX_DIR ), NULL, NULL );
      drive.ReleaseBuffer();
      dir.ReleaseBuffer();

		BOOL bDriveOK = drive.IsEmpty();		// SAC 9/2/14 - modified code the ALLOW for drive to be blank (network drive paths)
      if (!bDriveOK)
      {
         int nDrive = drive[0] - ( (drive[0] <= 'Z') ? 'A' : 'a' ) + 1;			ASSERT( nDrive > 0 && nDrive < 27 );
         if (_chdrive( nDrive ) == 0)
				bDriveOK = TRUE;
		}
      if (bDriveOK && dir.GetLength() > 0)
      {
         int nChars = dir.GetLength();
         if ( (nChars > 1) && (dir[ nChars-1 ] == '\\') )
            nChars--;

         if (bRemoveDir && DirectoryExists( dir ))   // SAC 2/12/07 - added code to facilitate directory deletion
         {
            if (_rmdir( dir.Left(nChars).GetBuffer(0) ) != 0)
            {
               CString sMsg;
               sMsg.Format( "Error removing directory: %s", pszDirName );
               AfxMessageBox( sMsg );
            }
            dir.ReleaseBuffer();
         }
         else if (!bRemoveDir)
         {
            if (!DirectoryExists( dir ))
            {
// SAC 9/8/01 - Note:  the following call is capable of making only ONE new directory (per call)
               if (_mkdir( dir.Left(nChars).GetBuffer(0) ) != 0)
               {
                  CString sMsg;
                  sMsg.Format( "Error creating directory: %s", pszDirName );
                  AfxMessageBox( sMsg );
               }
               dir.ReleaseBuffer();
            }

            _chdir( dir.Left(nChars).GetBuffer(0) );
            dir.ReleaseBuffer();
         }
      }
   }
}

// SAC 3/23/09 - added to handle prompting of user to close file needing to be written
BOOL OKToWriteOrDeleteFile( const char* pszFileName, const char* pszUserMsg, bool bSilent /*=false*/ )
{
   BOOL bRetVal = (!FileExists( pszFileName ));  // if file doesn't yet exist -> return TRUE

   BOOL bAbort = FALSE;
   while (!bRetVal && !bAbort)
   {
      if (!FileExists( pszFileName ))  // SAC 8/17/06
         bRetVal = TRUE;  // user deleted or renamed file since last check -> return TRUE
      else
      {
//AfxMessageBox( "About to try opening file..." );
         FILE *pfTempFile = fopen( pszFileName, "r+" );
         if (pfTempFile != NULL)
         {
//AfxMessageBox( "File opened OK." );
            fclose( pfTempFile );
            bRetVal = TRUE;
         }

			if (bSilent)
			   bAbort = TRUE;
         if (!bRetVal)
         {
            // CString sMsg = "The ";
            // sMsg += szFileDescription;
            // sMsg += " file '";
            // sMsg += sFileName;
            // sMsg += "' is opened in another application.  This file must be closed in that application before an updated file can be written.";
            // sMsg += "\n\nSelect 'Retry' to update the file (once the file is closed), or \n'Cancel' to abort the file writing process.";
            // bAbort = (AfxMessageBox( sMsg, MB_RETRYCANCEL | MB_ICONSTOP ) == IDCANCEL);
            bAbort = (AfxMessageBox( pszUserMsg, MB_RETRYCANCEL | MB_ICONSTOP ) == IDCANCEL);
         }
      }
   }

   return bRetVal;
}

// based on bool BEMPX_WriteLogFile()
bool AppendToTextFile(	const char* output, const char* psFileName, const char* psFileType, const char* psWriteAction,
								const char** ppCSVColumnLabels /*=NULL*/, bool bBlankFile /*=false*/, BOOL bSupressAllMessageBoxes /*=FALSE*/ )
{
   bool ok = TRUE;
	if (psFileName && strlen( psFileName ))
	{	CString sMsg;
		sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to abort the %s.", psFileType, psFileName, psWriteAction );
		if (OKToWriteOrDeleteFile( psFileName, sMsg ))
	   {
	      CStdioFile outFile;
	      // open file
	      if (bBlankFile || !FileExists( psFileName ))
	      {
	         ok = (outFile.Open( psFileName, CFile::modeCreate | CFile::modeWrite ) != 0);
				if (ppCSVColumnLabels)
				{	int idx=-1;
					while (ppCSVColumnLabels[++idx])
		         	outFile.WriteString( (CString)ppCSVColumnLabels[idx] );
				}
	      }
	      else
	      {
	         ok = (outFile.Open( psFileName, CFile::modeWrite ) != 0);
	         if (ok)  // get to end of file so as not to add to the beginning of the file
	            outFile.SeekToEnd();
	      }
	
	      if ( !ok )
	      {  if (!bSupressAllMessageBoxes)  // SAC 4/27/03
	         {  // post error message
	            sMsg = CString( "Error opening file: " ) + psFileName;
	            ::MessageBox( NULL, sMsg, NULL, MB_ICONEXCLAMATION );
	         }
	      }
	      else if (strlen(output) > 1 && output[strlen(output)-1] == '\n')	// SAC 5/19/14 - prevent double line spacing
	        	outFile.WriteString( output );
			else
	        	outFile.WriteString((CString)output + "\n");
	   }
	}
	return ok;
}


/////////////////////////////////////////////////////////////////////////////
// Numeric String Comma insertion and removal

//void AddCommaToStringLong( CString& string, long lNum )
//{
//   if (labs(lNum) >= 1000)
//   {
//      char comma = ',';
//      CString left, right;
//      for (float f=1.0; labs(lNum) >= pow(1000.0, f); f++)
//      {
//         int nLeft  = string.GetLength() - 3 - (int) ((f-1.0)*4.0);
//         int nRight = string.GetLength() - nLeft;
//         left  = string.Left(  nLeft );
//         right = string.Right( nRight );
//         string = left + comma + right;
//      }
//   }
//}
//
//void AddCommaToStringFloat( CString& string, float fNum, int nRtOfDec )
//{
//   if (fabs(fNum) >= 1000.0)
//   {
//      char comma = ',';
//      CString left, right;
//      if (nRtOfDec > 0)
//         nRtOfDec++;
//      for (float f=1.0; fabs(fNum) >= pow(1000.0, f); f++)
//      {
//         int nLeft  = string.GetLength() - nRtOfDec - 3 - (int) ((f-1.0)*4.0);
//         int nRight = string.GetLength() - nLeft;
//         left  = string.Left(  nLeft );
//         right = string.Right( nRight );
//         string = left + comma + right;
//      }
//   }
//}


// SAC 1/7/01 - moved to BEMProc (BEMPX_StringToLong() & BEMPX_StringToFloat())
// void RemoveCommas( CString& sNum )
// {
//    CString sTemp;
//    for( int i = 0; i < sNum.GetLength(); i++ )
//    {
//       if( sNum[i] != ',' )
//          sTemp += sNum[i];
//    }
//    sNum = sTemp;
// }
// 
// long RemoveCommasAndConvertToLong( CString sLong )
// {
//    RemoveCommas( sLong );
//    return( atol( sLong ) );
// }
// 
// float RemoveCommasAndConvertToFloat( CString sFlt )
// {
//    RemoveCommas( sFlt );
//    return( (float)atof( sFlt ) );
// }


/////////////////////////////////////////////////////////////////////////////
// String Manipulation

void RemoveIncompatibleFileNameCharacters( CString& sFileName )
{
   int iLen = sFileName.GetLength();
   for (int i=0; i<iLen; )
   {
      if ((sFileName[i] == '*') || (sFileName[i] == '?') ||
          (sFileName[i] == '|') || (sFileName[i] == ':') ||
          (sFileName[i] == '/') || (sFileName[i] == '\\') ||
          (sFileName[i] == '<') || (sFileName[i] == '>') ||
          (sFileName[i] == '"') )
      {
// unnecessary if .Left() & .Right() can deal with arguments of value '0'
//         CString sTemp = sPath;
//         sPath.Empty();
//         if (i > 0)
//            sPath = sTemp.Left();
//         if (i < iLen-1)
//            sPath += sTemp.Right();
         sFileName = sFileName.Left( i ) + sFileName.Right( iLen-i-1 );
         iLen--;
      }
      else
         i++;
   }
}


// SAC 8/20/14 - data & routines to enable product-specific illegal object name characters
bool CharacterNotAllowedInObjectname( char c )
{	int idx=-1;
	while (pcCharsNotAllowedInObjNames[++idx] != NULL)
	{	if (c == pcCharsNotAllowedInObjNames[idx])
			return true;
	}
	return false;
}

bool SetCharsNotAllowedInObjNamesToBEMProcUI()
{	return (BEMPUIX_SetCharsNotAllowedInObjectNames( (char*) pcCharsNotAllowedInObjNames ) != FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// Routines to facilitate migration to new open source compliance engine libraries

BOOL BEMPX_SetDataString(  long lDBID, CStringA& sStr, BOOL bAddCommas /*=TRUE*/, int iPrecision /*=0*/,
                                        int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
                                        const char* pszDefault /*=NULL*/, long lDBID2 /*=0*/, int iBEMProcIdx /*=-1*/ )
{	QString qsStr;
	BOOL bRetVal = BEMPX_GetString(  lDBID, qsStr, bAddCommas /*=TRUE*/, iPrecision /*=0*/,
                                        iDispDataType /*=-1*/, iOccur /*=-1*/, iObjType /*=BEMO_User*/,
                                        pszDefault /*=NULL*/, lDBID2 /*=0*/, iBEMProcIdx /*=-1*/ );
	sStr = qsStr.toLatin1().constData();
	return bRetVal;
}

BOOL BEMPX_SetDataInteger( long lDBID, long& lData, long lDefault /*=0*/,
                                         int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
                                         int iBEMProcIdx /*=-1*/ )
{	return BEMPX_GetInteger( lDBID, lData, lDefault, iDispDataType, iOccur, iObjType, iBEMProcIdx );
}

// extern BOOL BEMPX_SetDataFloat(   long lDBID, float& fData, float fDefault /*=0*/,
//                                         int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
//                                         int iBEMProcIdx /*=-1*/ )
		// BOOL    BEMPROC_API __cdecl BEMPX_GetFloat(      long lDBID, double& fData, double fDefault=0, int iDispDataType=-1,		// for backward compatibility with BEMPX_SetDataFloat
		// 																	int iOccur=-1, int iObjType=BEMO_User, int iBEMProcIdx=-1 );

int BEMPX_SetDataFloatArray( long lDBID, double* pfData, int iMaxValues, double fDefault /*=0*/,
                                 int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
                                 int iBEMProcIdx /*=-1*/ )
{	return BEMPX_GetFloatArray( lDBID, pfData, iMaxValues, fDefault, iDispDataType, iOccur, iObjType, iBEMProcIdx );
}

BOOL BEMPX_SetDataObject(  long lDBID, BEMObject*& pObj, int iDispDataType /*=-1*/,
									int iOccur /*=-1*/, int iObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{	return BEMPX_GetObject( lDBID, pObj, iDispDataType, iOccur,	iObjType, iBEMProcIdx );
}


long BEMPX_GetDatabaseID(    const char* psDBCompParam, long iCompID /*=0*/, BOOL bTreatParentAsObject /*=FALSE*/,
									int* piRefCompID /*=NULL*/, int* piNumRefComps /*=NULL*/ )
{	QString qStr = psDBCompParam;
	return BEMPX_GetDatabaseID( qStr, iCompID, bTreatParentAsObject, piRefCompID, piNumRefComps );
}

// END OF - Routines to facilitate migration to new open source compliance engine libraries
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// BEMProc-related functions

BOOL CtrlDataIsNumber( int iDataType )
{
   return ((iDataType == BEMP_Int) || (iDataType == BEMP_Flt));
}


// Compliance Data Type Strings
static int iNumCompDataTypeStrings = 8;
static char BASED_CODE szCDTCompuls[]   = "Input is compulsory";
static char BASED_CODE szCDTRequire[]   = "Input is required";
static char BASED_CODE szCDTCondReq[]   = "Input is cond. reqrd.";
static char BASED_CODE szCDTOptiona[]   = "Input is optional";
static char BASED_CODE szCDTDefault[]   = "Input is optional";
static char BASED_CODE szCDTCritica[]   = "Input is crit. default";
static char BASED_CODE szCDTPrescri[]   = "Field not editable";
static char BASED_CODE szCDTNotInpu[]   = "Field not editable";
static const char* pszCDT[] = {  szCDTCompuls, szCDTRequire, szCDTCondReq, szCDTOptiona,
                                 szCDTDefault, szCDTCritica, szCDTPrescri, szCDTNotInpu };
static char BASED_CODE szCDTNav[]  = "Navigation input";
static char BASED_CODE szCDTNone[] = "No field selected";

const char* GetCompDataTypeString( long lDBID )
{
   int iCDT = BEMPX_GetCompDataType( lDBID );

   if ( (iCDT == -1) && (lDBID > 0) )
   {
      int iClass = BEMPX_GetClassID(    lDBID );
      int iProp  = BEMPX_GetPropertyID( lDBID );
      int iArr   = BEMPX_GetArrayID(    lDBID );

      if ( (iClass > 0) && (iProp == 0) )
      {
         if ( (iArr == 2) || (iArr == 3) )
            return szCDTRequire;
         else if (iArr == 1)
            return szCDTNav;
      }
   }
   else
      return ((iCDT < 0) || (iCDT >= iNumCompDataTypeStrings)) ? szCDTNone : pszCDT[ iCDT ];

   return szCDTNone;
}


//static int siCDT_RGB[ 8 ][ 3 ] = {
//                       //  R    G    B
//                        {   0,   0,   0 },   // Compulsory
//                        {   0,   0,   0 },   // Required
//                        {   0,   0,   0 },   // Optional
//                        {   0,   0,   0 },   // Default
//                        {   0,   0,   0 },   // Crit. Default
//                        { 128, 128, 128 },   // Prescribed
//                        {   0,   0,   0 },   // Not Input
//                        {   0,   0,   0 } }; // (invalid data type)
//
//COLORREF GetCompDataTypeTextColor( long lDBID )
//{
//   int iCDT = BEMPX_GetCompDataType( lDBID );
//
//   if ( (iCDT < 0) || (iCDT > 7) )
//      iCDT = 7;
//
//   return RGB( siCDT_RGB[iCDT][0], siCDT_RGB[iCDT][1], siCDT_RGB[iCDT][2] );
//}


// Data Status Strings
static int iNumDataStatusStrings = 9;
//   static char BASED_CODE szDSUndefined[] = "Undefined";
//   static char BASED_CODE szDSProgDefau[] = "Prog. Default";
//   static char BASED_CODE szDSRuleDefau[] = "Rule Default";
//   static char BASED_CODE szDSRuleLibra[] = "Rule Library";
//   static char BASED_CODE szDSRuleDefin[] = "Rule Defined";
//   static char BASED_CODE szDSUserDefau[] = "User Default";
//   static char BASED_CODE szDSUserLibra[] = "User Library";
//   static char BASED_CODE szDSUserDefin[] = "User Defined";
//   static char BASED_CODE szDSSimResult[] = "Sim Result";
// SAC 8/7/00 - Replaced character strings per RSB's request
static char BASED_CODE szDSUndefined[] = "Value undefined";
static char BASED_CODE szDSProgDefau[] = "Value from program";
static char BASED_CODE szDSRuleDefau[] = "Value from program";
static char BASED_CODE szDSRuleLibra[] = "Value from program";
static char BASED_CODE szDSRuleDefin[] = "Value from program";
static char BASED_CODE szDSUserDefau[] = "Value from user";
static char BASED_CODE szDSUserLibra[] = "Value from user";
static char BASED_CODE szDSUserDefin[] = "Value from user";
static char BASED_CODE szDSSimResult[] = "Value from simulation";
static const char* pszDS[] = {  szDSUndefined, szDSProgDefau, szDSRuleDefau,
                                szDSRuleLibra, szDSRuleDefin, szDSUserDefau,
                                szDSUserLibra, szDSUserDefin, szDSSimResult };

const char* GetDataStatusString(  long lDBID, int iDBInstance )
{
   int iDS = BEMPX_GetDataStatus( lDBID, iDBInstance );

   if ( (iDS < 0) || (iDS >= iNumDataStatusStrings) )
      iDS = 0;

   return pszDS[ iDS ];
}


// Data Status Strings - Used To Retrieve Display Text Colors from .INI file
#define NUM_DS_TEXT_COLORS    9
#define NUM_INI_TEXT_COLORS  (NUM_DS_TEXT_COLORS + NUM_RESERVED_TEXT_COLORS)

static char BASED_CODE szTextColors[]     = "TextColors";

static char BASED_CODE szTCRangeError[]  = "RangeError%s";
static char BASED_CODE szDSTCUndefined[] = "Undefined%s";
static char BASED_CODE szDSTCProgDefau[] = "ProgDefault%s";
static char BASED_CODE szDSTCRuleDefau[] = "RuleDefault%s";
static char BASED_CODE szDSTCRuleLibra[] = "RuleLibrary%s";
static char BASED_CODE szDSTCRuleDefin[] = "RuleDefined%s";
static char BASED_CODE szDSTCUserDefau[] = "UserDefault%s";
static char BASED_CODE szDSTCUserLibra[] = "UserLibrary%s";
static char BASED_CODE szDSTCUserDefin[] = "UserDefined%s";
static char BASED_CODE szDSTCSimResult[] = "SimResult%s";
static const char* pszTC[] = {  szTCRangeError,		// NUM_RESERVED_TEXT_COLORS listed before those that map to BEMBase data status values
                                szDSTCUndefined, szDSTCProgDefau, szDSTCRuleDefau,
                                szDSTCRuleLibra, szDSTCRuleDefin, szDSTCUserDefau,
                                szDSTCUserLibra, szDSTCUserDefin, szDSTCSimResult };

static char BASED_CODE szR[] = "R";
static char BASED_CODE szG[] = "G";
static char BASED_CODE szB[] = "B";
const char FAR* szRGB[] = { szR, szG, szB }; 

static int iaTextR[ NUM_INI_TEXT_COLORS ];
static int iaTextG[ NUM_INI_TEXT_COLORS ];
static int iaTextB[ NUM_INI_TEXT_COLORS ];
static int* iaTextColors[3] = { iaTextR, iaTextG, iaTextB };
static COLORREF iaTextRGB[ NUM_INI_TEXT_COLORS ];
static QBrush qbaBEMText[  NUM_INI_TEXT_COLORS ];		// SAC 3/23/18 - for grid text colors
static QBrush qbBlack;

void LoadDefaultTextColors()
{
   for (int i = 0; i < NUM_INI_TEXT_COLORS; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         CString entry;
         entry.Format(pszTC[i], szRGB[j]);         
         iaTextColors[j][i] = ReadProgInt(szTextColors, entry, 0);
      }
      iaTextRGB[i] = RGB( iaTextColors[0][i], iaTextColors[1][i], iaTextColors[2][i] );
      qbaBEMText[i].setColor( QColor( iaTextColors[0][i], iaTextColors[1][i], iaTextColors[2][i] ) );
   }
   qbBlack.setColor( QColor(0,0,0) );
}

COLORREF GetCUITextColor( int iDS )
{
   if (iDS >= 0 && iDS < NUM_INI_TEXT_COLORS)
//      return RGB( iaTextR[iDS], iaTextG[iDS], iaTextB[iDS] );
      return iaTextRGB[iDS];
   return RGB(0,0,0);
}

int GetCUITextRGB( int iDS, int idxRGB )
{
	if (iDS >= 0 && iDS < NUM_INI_TEXT_COLORS && idxRGB >= 0 && idxRGB < 3)
		return iaTextColors[idxRGB][iDS];
	return 0;
}

QBrush* BEMTextQBrush( int iDS )
{
   if (iDS >= 0 && iDS < NUM_INI_TEXT_COLORS)
      return &qbaBEMText[iDS];
   return &qbBlack;
}

void SetBDBWTextColors()
{
   BEMPUIX_SetTextColors( &iaTextRGB[NUM_RESERVED_TEXT_COLORS], NUM_DS_TEXT_COLORS );
}


// Function to determine if an object is from the library
static char BASED_CODE szErrGetObj[]   = "ObjectIsFromLibrary(): Error retrieving current object.";
static char BASED_CODE szObjFromLib[]  = "Library Data Not Editable";
static char BASED_CODE szObjFromLib1[] = "This building component is defined in a library and therefore ";
static char BASED_CODE szObjFromLib2[] = "data which describes it is NOT editable.  Renaming this component ";
static char BASED_CODE szObjFromLib3[] = "will automatically copy the data out of the library and into a user ";
static char BASED_CODE szObjFromLib4[] = "defined component which IS editable.  To rename this component, ";
static char BASED_CODE szObjFromLib5[] = "return to the 'Navigate' dialog tab, click on the component with ";
static char BASED_CODE szObjFromLib6[] = "the right mouse button and select 'Rename' from the quick menu.";

// function called before data set to BEMProc to prevent setting Rule or User Library data
BOOL ObjectIsFromLibrary( long lDBID )
{
   BOOL bRetVal = TRUE;

   if (lDBID == 0)  // allow edit of data w/ 0 DBID (during creation...)
      bRetVal = FALSE;
   else
   {
      int iError;
      BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError );
      if ( (iError < 0) || (pObj == NULL) )
         ::MessageBox( NULL, szErrGetObj, "Error", MB_ICONSTOP );
      else
      {
         if ( (pObj->getObjectType() == BEMO_RuleLib) || 
              (pObj->getObjectType() == BEMO_UserLib) )
         {
            CString sMsg = szObjFromLib1;
            sMsg += szObjFromLib2;
            sMsg += szObjFromLib3;
            sMsg += szObjFromLib4;
            sMsg += szObjFromLib5;
            sMsg += szObjFromLib6;
            ::MessageBox( NULL, sMsg, szObjFromLib, MB_ICONSTOP );
         }
         else
            bRetVal = FALSE;  // object is user-defined => editable
      }
   }

   return bRetVal;
}


void DefaultProjectName( CString& sProjName )
{
   CString sLeft = ReadProgString( "paths", "ProjectsPath", "", TRUE );
   CString sProjExt = ReadProgString( "options", "ProjectFileExt", "" );		// SAC 3/8/20
//   CString sRight = ".ibd";
   CString sRight;
   if (sProjExt.IsEmpty())
		sRight.Format( ".%s", pszCUIFileExt[0] );
	else
		sRight.Format( ".%s", sProjExt );
   long lProjIdx = 1;
   sProjName.Format( "Project %ld", lProjIdx );
   CString sTest = sLeft + sProjName + sRight;
   while ( FileExists( sTest ) && (lProjIdx < 10000) )
   {
      sProjName.Format( "Project %ld", ++lProjIdx );
      sTest = sLeft + sProjName + sRight;
   }
}


/////////////////////////////////////////////////////////////////////////////
// Ruleset Report Generation stuff     - SAC 6/9/13

std::vector<std::string> saReportRulelistNames;
std::vector<std::string> saReportRulelistSelections;

static BOOL RefreshRulesetReportList()
{	BOOL bRetVal = TRUE;
	saReportRulelistNames.clear();
	saReportRulelistSelections.clear();
	QVector<QString> sRulelistNames;		CString sTemp, sReportSelection;
	int iNumRulelists = BEMPX_GetRulelistNames( sRulelistNames );
	for (int i=0; (bRetVal && i < iNumRulelists); i++)
		if (sRulelistNames[i].left(13).compare( "ReportMaster_" ) == 0)
		{	sTemp = sRulelistNames[i].right( sRulelistNames[i].length() - 13 ).toLatin1().constData();
			int iLastUnderscore = sTemp.ReverseFind('_');											ASSERT( iLastUnderscore > 0 );
			if (iLastUnderscore > 0)
			{	sReportSelection  = sTemp.Left( iLastUnderscore ) + CString( " (" );
				sReportSelection += sTemp.Right( sTemp.GetLength() - iLastUnderscore - 1 ) + CString( ")" );
				sReportSelection.Replace( '_', ' ' );
				if (!sReportSelection.IsEmpty())
				{	saReportRulelistNames.push_back( sRulelistNames[i].toLatin1().constData() );
					saReportRulelistSelections.push_back( ((const char*) sReportSelection)  );
//sTemp.Format( "Report  '%s'  /  Rulelist  '%s'", sReportSelection, sRulelistNames[i] );
//AfxMessageBox( sTemp );
				}
			}
		} 

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// ruleset code year  - SAC 6/12/19
long elRulesetCodeYear = 0;
void SetRulesetCodeYear()
{
#ifdef UI_CANRES
	BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" ), elRulesetCodeYear );
#elif UI_CARES
	BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), elRulesetCodeYear );
#else
	elRulesetCodeYear = 0;
#endif
}


/////////////////////////////////////////////////////////////////////////////
// Ruleset Switching/Loading stuff

char BASED_CODE eszWarning[] = "Warning";
char BASED_CODE eszRulesetSwitch[] = "Warning:  Switching compliance rulesets may cause certain user inputs to be"
                                     " overwritten by the new ruleset.  We recommend that you save and/or rename your "
                                     "project prior to switching rulesets in order to ensure that you do not loose"
                                     " any data.\n\nSelect 'Yes' to switch rulesets or 'No' to cancel your ruleset"
                                     " selection.";
//char BASED_CODE eszRulesetDefault[] = "Would you like to make the selected ruleset the new default ruleset?";
char BASED_CODE eszPostRulesetSwitch[] = "Ruleset switch has changed project file data and as a result it is recommended that you perform a File-Save or Save As action.";

// we have to define the symbol strings such that they remain in memory after
// this function terminates or future symbol list references will fail
#define  MAX_RULESETS_IN_DIRECTORY  25
int eiNumRulesetsAvailable = 0;
static CString ssaRulesetSymString[  MAX_RULESETS_IN_DIRECTORY ];
static CString ssaRulesetFileString[ MAX_RULESETS_IN_DIRECTORY ];
static int siCheckedRulesetIdx = -1;
static CString ssCurrentRuleFile;

int RulesetFilenameToIndex( const char* pszRulesetFN )	// SAC 4/10/19 - added to facilitate resetting of Proj:Ruleset when switching rulesets
{	for (int i=0; i<eiNumRulesetsAvailable; i++)
	{	if (ssaRulesetFileString[i].CompareNoCase( pszRulesetFN )==0)
			return i;
	}
	return -1;
}

// Based on MFC function: CRecentFileList::UpdateMenu()
void UpdateRulesetMenu(CCmdUI* pCmdUI)
{
   CString strOriginal = "Compliance Ruleset";

	if (eiNumRulesetsAvailable == 0)
	{
		// no MRU files
		if (!strOriginal.IsEmpty())
			pCmdUI->SetText(strOriginal);
		pCmdUI->Enable(FALSE);
		return;
	}

	if (pCmdUI->m_pMenu == NULL)
		return;

	int iMRU = 0;
	for (; iMRU < MAX_RULESETS_IN_DIRECTORY; iMRU++)
		pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID + iMRU, MF_BYCOMMAND);

   // Added to get current ruleset in order to put a check mark by the active ruleset
   siCheckedRulesetIdx = -1;

   bool bEnableRulesetSwitching = (ReadProgInt( "options", "EnableRulesetSwitching", 0 ) > 0);	// SAC 8/25/14
	CString strName, strTemp;
	int iMIIdx=0;
	for (iMRU = 0; iMRU < eiNumRulesetsAvailable; iMRU++)
	{
		// double up any '&' characters so they are not underlined
		LPCTSTR lpszSrc = ssaRulesetSymString[iMRU];
		LPTSTR lpszDest = strTemp.GetBuffer(ssaRulesetSymString[iMRU].GetLength()*2);
#pragma warning(disable:4127)
		while (*lpszSrc != 0)
		{
			if (*lpszSrc == '&')
				*lpszDest++ = '&';
			if (_istlead(*lpszSrc))
				*lpszDest++ = *lpszSrc++;
			*lpszDest++ = *lpszSrc++;
		}
#pragma warning(default:4127)
		*lpszDest = 0;
		strTemp.ReleaseBuffer();

      if (ssCurrentRuleFile.CompareNoCase(ssaRulesetFileString[iMRU]) == 0 || bEnableRulesetSwitching)
		{	// insert mnemonic + the file name
			TCHAR buf[10];
			wsprintf(buf, _T("&%d "), (iMIIdx/*iMRU*/+1) % 10);
			pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex++,
				MF_STRING | MF_BYPOSITION, pCmdUI->m_nID++,
				CString(buf) + strTemp);

      	// Added code to disable all entries if no 'Project' exists OR to put a check mark by the active ruleset
      	if (ssCurrentRuleFile.CompareNoCase(ssaRulesetFileString[iMRU]) == 0)
      	{
      	   pCmdUI->m_pMenu->CheckMenuItem( pCmdUI->m_nID-1, MF_CHECKED );
      	   siCheckedRulesetIdx = iMIIdx/*iMRU*/;
      	}
			iMIIdx++;
		}
	}

	// update end menu count
	pCmdUI->m_nIndex--; // point to last menu added
	pCmdUI->m_nIndexMax = pCmdUI->m_pMenu->GetMenuItemCount();

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
}


BOOL MenuRulesetSelectionAllowed( int idx, CString& sRuleSwitchDisallowedMsg )
{	BOOL bRetVal = FALSE;
	if (idx == siCheckedRulesetIdx)
	{	// do nothing
	}
	else if (idx < 0 || siCheckedRulesetIdx < 0)
		sRuleSwitchDisallowedMsg.Format( "Ruleset switch indices invalid - both must be >= 0 - switching from %d to %d.", siCheckedRulesetIdx, idx );
	else if (idx >= eiNumRulesetsAvailable || siCheckedRulesetIdx >= eiNumRulesetsAvailable)
		sRuleSwitchDisallowedMsg.Format( "Ruleset switch indices invalid - both must be < the number of available rulesets (%d) - switching from %d to %d.", eiNumRulesetsAvailable, siCheckedRulesetIdx, idx );
	else
	{
#ifdef UI_CANRES
		if (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA " ) == 0 && ssaRulesetSymString[idx].Find( "Nonresidential" ) > 0 &&
			 !ssaRulesetSymString[siCheckedRulesetIdx].IsEmpty() && ssaRulesetSymString[siCheckedRulesetIdx].Find( "CA " ) == 0 && ssaRulesetSymString[siCheckedRulesetIdx].Find( "Nonresidential" ) > 0)
			bRetVal = TRUE;
		else
			sRuleSwitchDisallowedMsg.Format( "Ruleset switch from '%s' to '%s' is not allowed.\nCBECC only allows for switching between 'CA 20xx Nonresidential' rulesets.",
															ssaRulesetSymString[siCheckedRulesetIdx], ssaRulesetSymString[idx] );
#endif   // UI_CANRES
#ifdef UI_CARES
	//	if (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA Residential" ) == 0 &&
	//		 !ssaRulesetSymString[siCheckedRulesetIdx].IsEmpty() && ssaRulesetSymString[siCheckedRulesetIdx].Find( "CA Residential" ) == 0)
		if (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA Res" ) == 0 &&
			 !ssaRulesetSymString[siCheckedRulesetIdx].IsEmpty() && ssaRulesetSymString[siCheckedRulesetIdx].Find( "CA Res" ) == 0)
			bRetVal = TRUE;
		else
			sRuleSwitchDisallowedMsg.Format( "Ruleset switch from '%s' to '%s' is not allowed.\nCBECC-Res only allows for switching between 'CA Residential' rulesets.",
															ssaRulesetSymString[siCheckedRulesetIdx], ssaRulesetSymString[idx] );
#endif   // UI_CARES
		if (!bRetVal && sRuleSwitchDisallowedMsg.IsEmpty())
			sRuleSwitchDisallowedMsg.Format( "Ruleset switch from '%s' to '%s' is not allowed by this product.",
															ssaRulesetSymString[siCheckedRulesetIdx], ssaRulesetSymString[idx] );
	}
	return bRetVal;
}

BOOL CodeYearRulesetAvailable( CString sCodeYear )		// SAC 10/30/15
{	BOOL bRetVal = FALSE;
	for (int idx=0; (!bRetVal && idx < eiNumRulesetsAvailable); idx++)
		if (ssaRulesetSymString[idx].Find( sCodeYear ) >= 0)
		{
#ifdef UI_CANRES
			bRetVal = (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA " ) == 0 && ssaRulesetSymString[idx].Find( "Nonresidential" ) > 0);
#elif UI_CARES
		//	bRetVal = (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA Residential" ) == 0);
			bRetVal = (!ssaRulesetSymString[idx].IsEmpty() && ssaRulesetSymString[idx].Find( "CA Res" ) == 0);
#endif
		}
	return bRetVal;
}

BOOL MenuRulesetSelection( CWnd* pWnd, int idx, CString& sRulesetFileString )
{
   if ( pWnd && (idx != siCheckedRulesetIdx) &&
		//	(::MessageBox( pWnd->GetSafeHwnd(), eszRulesetSwitch, eszWarning, MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES) )
		// SAC 8/15/14 - bail on warning message PRIOR to ruleset switch
			TRUE )
   {
// SAC 11/17/15 - REMOVED code that modifies default ruleset (defined in INI) - as this should remain constant or ruleset switch enabling & forcing user to install default ruleset will not work properly
//// SAC 2/1/99 - added code to prompt user to switch default ruleset in .INI file (if the selected ruleset is not already the default)
//      CString sINIRulesetFile = ReadProgString( "files", "RulesetFile", "" );
//      if (sINIRulesetFile.CompareNoCase( ssaRulesetFileString[idx] ) != 0 &&
//          ::MessageBox( pWnd->GetSafeHwnd(), eszRulesetDefault, "Switching Compliance Rulesets", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2 ) == IDYES)
//         WriteProgString( "files", "RulesetFile", ssaRulesetFileString[idx] ); 

      // User switched compliance rulesets
      sRulesetFileString = ssaRulesetFileString[idx];
      return TRUE;
   }
   return FALSE;

// SAC 8/14/14 - move & revise remaining logic to include full database reset and re-opening of project file as part of a ruleset switch
//      // reset the project's and wizard's ruleset symbolic values (iff these components exist)
//      long lNewVal = (long) idx;
//      if (BEMPX_GetNumObjects( (int) eiBDBCID_Proj ) > 0)
//         BEMPX_SetBEMData( elDBID_Proj_Ruleset, BEMP_Sym, (void*) &lNewVal );
//      else
//         // set this string to be the default which will be installed into the next created 'Project' component
//         BEMPX_SetRulesetFilename( sRulesetSymbol );
//
//      LoadRuleset( sRulesetSymbol, FALSE );
//
//	// SAC 6/18/14 - added RE-load of BEM CIDs & DBIDs to account for special conditions, such as UI_CANRES 2D/simplified geometry
//		InitBEMDBIDs();
//
//      // set data modified flag & execute compliance rulelist #1
//      SetDataModifiedFlag( TRUE );
//      pWnd->SendMessage( WM_EVALPROPOSED );
//
//      // send a message to the main view's tree control via CMainFrame in case the tree requires updating
//      pWnd->SendMessage( WM_UPDATETREE, 0, elDBID_Proj_Ruleset );
//
//      return TRUE;
//   }
//   return FALSE;
}


// Replace existing BEMProc 'Proj:Ruleset' symbol info with data corresponding
// to the current contents of the files contained in the Ruleset directory.
static BOOL LoadRulesetList( CString& sINIRulesetFile )
{
   BOOL bINIRulesetFileFound = FALSE;
   eiNumRulesetsAvailable = 0;

   // store current drive/directory so that we can return @ end of function
   int prevDrive = _getdrive();
   static char szDir[ _MAX_PATH+1 ];
   _getcwd( szDir, _MAX_PATH );
   CString prevDir = szDir;

   CString sFileFilter = "*.bin";

   CString sDir = ReadProgString( "paths", "RulesetPath", "", TRUE );
   sDir = sDir.Left( sDir.GetLength()-1 );  // remove trailing '\'

   CString sCompatRulesetVerKey = ReadProgString( "options", "CompatRulesetVerKey", "" );		// SAC 3/3/20 - added filter to prevent any/all rulesets from appearing in Ruleset listing

   struct _finddata_t c_file;
   BOOL bChangedDrive = FALSE;
   CString sRulesetFile;

   if (_chdir( sDir ) == 0)
   {
      TRY
      {
         if (!bChangedDrive && sDir[0] != '\\')		// SAC 9/2/14 - prevent calling _chdrive() on network path
         {
            sDir.MakeUpper();
            int number = sDir[0] - 'A' + 1;
            _chdrive( number );
            bChangedDrive = TRUE;
         }

         long hFile = _findfirst( sFileFilter, &c_file );
         if (hFile != -1)
         {
            QString sRulesetID, sRulesetVer;
            CString sRulePath = ReadProgString( "paths", "RulesetPath", "", TRUE );
            do
            {
               if (!bINIRulesetFileFound && sINIRulesetFile.CompareNoCase( c_file.name ) == 0)
                  bINIRulesetFileFound = TRUE;

               sRulesetFile = sRulePath + c_file.name;
               if (CMX_ReadRulesetID( sRulesetFile, sRulesetID, sRulesetVer ) &&
               	 (sCompatRulesetVerKey.IsEmpty() || sRulesetVer.indexOf( (const char*) sCompatRulesetVerKey ) >= 0))	// SAC 3/3/20
               {
//                  ssaRulesetSymString[eiNumRulesetsAvailable++].Format( "%s, %s (%s)", sRulesetID, sRulesetVer, c_file.name );
                  ssaRulesetSymString[ eiNumRulesetsAvailable  ].Format( "%s (%s)", sRulesetVer.toLatin1().constData(), c_file.name );
// SAC 2/1/99 - added to track all valid ruleset filenames
                  ssaRulesetFileString[eiNumRulesetsAvailable++] = c_file.name;
               }

            } while ( eiNumRulesetsAvailable < MAX_RULESETS_IN_DIRECTORY &&
                      _findnext( hFile, &c_file ) == 0 );
            _findclose( hFile );
         }
      }
      CATCH(CException, e)
      {
         CString sErr = "Unexpected error loading installed ruleset file \n'";
         sErr += sRulesetFile;
         sErr += "'.  Remove this file from the the Rulesets directory before attempting this operation again.";
         AfxMessageBox( sErr );
      }
      END_CATCH
   }

   // return to original drive/directory
   if (bChangedDrive)
		_chdrive( prevDrive );
   _chdir(   prevDir );

   return bINIRulesetFileFound;
}

void LoadRulesetListIfNotLoaded()	// SAC 10/30/15
{	if (eiNumRulesetsAvailable < 1)
	{	CString sTemp = "invalid ruleset name";
		LoadRulesetList( sTemp );
	}
}

static BOOL ResetRulesetSymbols()
{
   int iNumReset = 0;
   void* pBDBSL = BEMPX_OverwriteSymbolList( elDBID_Proj_Ruleset );
   if (pBDBSL)
	{
      void* pBDBSDL = BEMPX_AddSymbolDepList( pBDBSL, 0, 0, -1.0, 0, -1.0 );
      if (pBDBSDL)
         for (int i=0; i<eiNumRulesetsAvailable; i++)
         {
            if (BEMPX_AddSymbol( pBDBSDL , iNumReset, ssaRulesetSymString[i] ))
               iNumReset++;
         }
	}
#ifdef UI_ASHRAE901E
   void* pWBDBSL = BEMPX_OverwriteSymbolList( elDBID_Wiz_Ruleset );
   if (pBDBSL && pWBDBSL)
   {
      void* pWBDBSDL = BEMPX_AddSymbolDepList( pWBDBSL, 0, 0, -1.0, 0, -1.0 );
      if (pWBDBSDL)
         for (int i=0; i<eiNumRulesetsAvailable; i++)
            VERIFY( BEMPX_AddSymbol( pWBDBSDL, iNumReset, ssaRulesetSymString[i] ) );
   }
#endif  // UI_ASHRAE901E
   return (iNumReset == eiNumRulesetsAvailable);
}


BOOL LoadDataModel(	const char* psBEMProcFileName /*=NULL*/, int iBEMType /*=BEMT_Other*/,
							const char* psInitLogFileName /*=NULL*/, BOOL bMsgBox /*=TRUE*/ )
{
	int iChkDMBin = BEMPX_CheckDataModelBin( psBEMProcFileName );		// SAC 1/3/17
	if (iChkDMBin > 0)
	{	if (bMsgBox)
		{	QString sErrMsg;
			switch (iChkDMBin)
			{	case  1 :  sErrMsg = "Data model binary filename not specified";   break;
				case  2 :  sErrMsg = QString( "File not found:  '%1'" ).arg( psBEMProcFileName );   break;
				case  3 :  sErrMsg = QString( "Unable to open file:  '%1'" ).arg( psBEMProcFileName );   break;
				case  4 :  sErrMsg = QString( "Cannot open insecure data model binary file in secure program:  '%1'\n\nRecompile the data model with current executables." ).arg( psBEMProcFileName );   break;
				case  5 :  sErrMsg = QString( "Cannot open secure data model binary in insecure program:  '%1'\n\nRecompile the data model with current executables." ).arg( psBEMProcFileName );   break;
				case  6 :  sErrMsg = QString( "Data model binary compiled with prior software version:  '%1'" ).arg( psBEMProcFileName );   break;
				case  7 :  sErrMsg = QString( "Data model binary compiled with newer software than this:  '%1'" ).arg( psBEMProcFileName );   break;
				default :  sErrMsg = QString( "Unknown error (code: %1)" ).arg( QString::number(iChkDMBin) );   break;
			}
			sErrMsg = "Error loading data model binary file.\n\n" + sErrMsg;
			AfxMessageBox( sErrMsg.toLatin1().constData() );
		}
	}
	else
		BEMPX_LoadDataModel( psBEMProcFileName, iBEMType, psInitLogFileName );
	return (iChkDMBin==0);
}


static char BASED_CODE szDefErr[] = "Default ";
static char BASED_CODE szErr[]    = "Compliance Ruleset File \n'";
static char BASED_CODE szErr1[]   = "' Not Found.";
static char BASED_CODE szErr2[]   = "' Version Compatibility Error.";
static char BASED_CODE szResErr[] = "Error resetting Proj:Ruleset symbol list.";
static char BASED_CODE szResDef1[] = "\nReset the 'RulesetFile' string in the [files] section of the ";
static char BASED_CODE szResDef2[] = " file to remedy this error.";
static char BASED_CODE szResProj[] = "\nEdit the Project component and select a valid compliance ruleset before"
                                     " making any changes to or performing analysis on this project.";
static char BASED_CODE szNoRule1[] = "No valid rulesets were found in the ruleset directory \n'";
static char BASED_CODE szNoRule2[] = "'.\nTo remedy this error either reset the 'RulesetPath' string in the [paths] "
                                     "section of the .INI file or copy valid ruleset files into the specified directory.";

BOOL LoadRuleset( const char* pszRulesetFileName, BOOL bDeleteAllObjects )
{
   CWaitCursor wait;  // causes cursor to become hourglass until messagebox displayed or function terminates

   int iError = 0;
   BOOL bLoadDefault = (pszRulesetFileName == NULL);
   CString sRuleName = ReadProgString( "paths", "RulesetPath", "", TRUE );
   CString sINIRulesetFile = ReadProgString( "files", "RulesetFile", "" );
   BOOL bLoadFoundDefault = LoadRulesetList( sINIRulesetFile );

   if (eiNumRulesetsAvailable <= 0)
      // ERROR: No compliance ruleset files are available in the ruleset directory
      iError = 3;
   else if (!bLoadFoundDefault)
      // ERROR: The default ruleset file was not found
      iError = 1;
   else
   {
//      if (bLoadDefault)
//         sRuleName += sINIRulesetFile;
//      else
//         sRuleName += pszRulesetFileName;
      CString sRuleFile = (bLoadDefault ? sINIRulesetFile : pszRulesetFileName);
      sRuleName += sRuleFile;

      if (!FileExists( sRuleName ))
         iError = 1;
		else
		{
ASSERT( bDeleteAllObjects ); // BEMBase reinitialization now a part of ruleset loading, so retaining BEMBase objects not possible (??)
			// SAC 7/11/12 - added RE-initialization of BEMBase (to clear out all ruleset variable data)
		//	CString sInitBDBFileName = ReadProgString( "files", "BEMFile", "", TRUE );
		// SAC 8/15/14 - revised to first check to see if rulest binary includes BEMBase definitions file
			QString sInitBDBFileName;
			if (CMX_GetRulesetBEMBaseFile( sRuleName, sInitBDBFileName ) && !sInitBDBFileName.isEmpty())
			{	CString sRulePN = ReadProgString( "paths", "RulesetPath", "", TRUE );
				sInitBDBFileName = sRulePN + sInitBDBFileName;												ASSERT( FileExists( sInitBDBFileName ) );
			}
			if (sInitBDBFileName.isEmpty() || !FileExists( sInitBDBFileName ))
				sInitBDBFileName = ReadProgString( "files", "BEMFile", "", TRUE );

			CString sInitLogFileName = ReadProgString( "paths", "ProjectsPath", "", TRUE );
			sInitLogFileName += "untitled.log";
			if (!LoadDataModel(	sInitBDBFileName.toLatin1().constData(), BEMT_CBECC, sInitLogFileName ))
//			BEMPX_LoadDataModel( sInitBDBFileName.toLatin1().constData(), BEMT_CBECC, sInitLogFileName );
      	   iError = 4;
      	else if (!CMX_LoadRuleset( sRuleName, bDeleteAllObjects ))  // ruleset file exists, so now try to load it
      	   iError = 2;
      	else
      	{  // Ruleset loaded OK, so now reset Ruleset symbols to reflect the ruleset
      	   // files currently available in the Ruleset directory
      	   if (!ResetRulesetSymbols())
      	      // post error message if one or more symbols not reset, but still continue on
      	      AfxMessageBox( szResErr );
      	
      	   VERIFY( RefreshRulesetReportList() );  // SAC 6/9/13

      	   // store currently selected ruleset filename (without path)
      	   ssCurrentRuleFile = sRuleFile;
      	
      	   if (bLoadDefault)
      	      // set this string to be the default which will be installed into the next created 'Project' component
      	      BEMPX_SetRulesetFilename( sRuleFile );
      	
      	   // SAC 2/1/99 - screen data resetting stuff
      	   CWnd* pMainWnd = AfxGetMainWnd();
      	   if (pMainWnd == NULL)
      	      pMainWnd = spMainWnd;
      	   if (pMainWnd)
      	      pMainWnd->SendMessage( WM_LOADSCREENFILES );
      	}
		}
   }

   if (iError > 0 && iError != 4)
   {  // Display error message
      CString sErr;
      if (iError == 3)
      {
         sErr = szNoRule1;
         sErr += sRuleName;
         sErr += szNoRule2;
      }
      else  // == 1 or 2
      {
         sErr = szErr;
         if (bLoadDefault)
            sErr = szDefErr + sErr;

         sErr += sRuleName;

         if (iError == 1)
            sErr += szErr1;
         else if (iError == 2)
            sErr += szErr2;

         if (iError == 1)
         {
            if (bLoadDefault)
            {
               sErr += szResDef1;
               sErr += iniFileName;
               sErr += szResDef2;
            }
            else
               sErr += szResProj;
         }
      }

      AfxMessageBox( sErr );
   }

   return (iError == 0);
}


/////////////////////////////////////////////////////////////////////////////
// Global Data and Routine to enable targeted rule evaluation logging when evaluating input/defaulting rules

static BEMCompNameTypePropArray inpRuleDebugInfo;
extern void* epInpRuleDebugInfo = NULL;

void LoadTargetedInputRuleDebugInfo()
{	epInpRuleDebugInfo = NULL;
	CString sLogMsg, sInputRuleEvalCSV = ReadProgString( "options", "InputRuleEvalCSV", "", TRUE ),
				  sInputRuleEvalCSVNoPath = ReadProgString( "options", "InputRuleEvalCSV", "", FALSE );
	if (!sInputRuleEvalCSV.IsEmpty() && !sInputRuleEvalCSVNoPath.IsEmpty() && FileExists( sInputRuleEvalCSV ))
	{	BOOL bIsUIActive = (BEMPX_GetUIActiveFlag());		
		sLogMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to ignore this file.", "rule evaluation debug", sInputRuleEvalCSV );
		if (!OKToWriteOrDeleteFile( sInputRuleEvalCSV, sLogMsg, (!bIsUIActive) ))
		{	if (!bIsUIActive)
				sLogMsg.Format( "ERROR:  Unable to open %s file:  %s", "rule evaluation debug", sInputRuleEvalCSV );
			else
				sLogMsg.Format( "ERROR:  User chose not to use/reference %s file:  %s", "rule evaluation debug", sInputRuleEvalCSV );
			BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
		}
      else
		{	int iDbgVerboseFlag=0, iDbgLogRuleListEval=0;
			if (inpRuleDebugInfo.ReadData( sInputRuleEvalCSV, iDbgVerboseFlag, iDbgLogRuleListEval ))
			{
				int iVerboseInputLogging = ReadProgInt( "options", "VerboseInputLogging", 0 );
				if (iDbgLogRuleListEval != iVerboseInputLogging)
					ebVerboseInputLogging = (iDbgLogRuleListEval > 0);
				epInpRuleDebugInfo = &inpRuleDebugInfo;
			}
			else
			{	ASSERT( FALSE );	// error reading rule debug info CSV
	}	}	}
}


/////////////////////////////////////////////////////////////////////////////
// Global BDB Class Index stuff

int eiBDBCID_Proj = 0;
long elDBID_Proj_Ruleset = 0;
long elDBID_Wiz_Ruleset = 999;
int eiBDBCID_BEMVersion = 0;			// SAC 9/17/12
long elDBID_Proj_BEMVersion = 0;		// SAC 9/17/12
int eiBDBCID_INISettings = 0;			// SAC 5/31/14
long elDBID_Proj_StdsVersion = 0;	// SAC 8/15/14
long elDBID_Proj_DefaultOptionInp = 0;		// SAC 4/11/18
long elDBID_Proj_DefaultOptionObj = 0;
long elDBID_Proj_DefaultOptionDone = 0;

long elDBID_Proj_AnalysisVersion = 0;     // SAC 05/30/22
long elProjAnalysisVersion = 0;  

// BEM Defaulting Options...
long elDefaultOptionInp = DefaultOption_Model;
long elDefaultOptionObj = DefaultOption_Model;
long elDefaultOptionDone = DefaultOption_Model;

#ifdef UI_ASHRAE901E
int eiBDBCID_Run = 0;
int eiBDBCID_Site = 0;
int eiBDBCID_Bldg = 0;
int eiBDBCID_Bshade = 0;
int eiBDBCID_Block = 0;
int eiBDBCID_Floor = 0;
int eiBDBCID_Space = 0;
int eiBDBCID_ActArea = 0;
int eiBDBCID_LtSys = 0;
int eiBDBCID_LtFix = 0;
int eiBDBCID_ExtWall = 0;
int eiBDBCID_ExtRoof = 0;
int eiBDBCID_IntWall = 0;
int eiBDBCID_IntCeil = 0;
int eiBDBCID_UndWall = 0;
int eiBDBCID_FlrWall = 0;
int eiBDBCID_Win = 0;
int eiBDBCID_Skylt = 0;
int eiBDBCID_Door = 0;
int eiBDBCID_Cons = 0;
int eiBDBCID_Layers = 0;
int eiBDBCID_Mat = 0;
int eiBDBCID_HVACSys = 0;
int eiBDBCID_Size = 0;
int eiBDBCID_HtPump = 0;
int eiBDBCID_AirCond = 0;
int eiBDBCID_Furn = 0;
int eiBDBCID_Econ = 0;
int eiBDBCID_Plant = 0;
int eiBDBCID_Fan = 0;
int eiBDBCID_ClTower = 0;
int eiBDBCID_Chiller = 0;
int eiBDBCID_Boiler = 0;
int eiBDBCID_Pump = 0;
int eiBDBCID_Curve = 0;
int eiBDBCID_Sched = 0;
int eiBDBCID_WkSch = 0;
int eiBDBCID_DaySch = 0;
int eiBDBCID_ResSch = 0;
int eiBDBCID_DResSch = 0;
int eiBDBCID_Wizard = 0;
int eiBDBCID_AreaWiz = 0;
int eiBDBCID_HVACWiz = 0;
int eiBDBCID_PlantWiz = 0;  // SAC 5/26/00 - added

long elDBID_Proj_Name = 0;
long elDBID_Proj_ArchTreeOption = 0;
long elDBID_Proj_FinalResult = 0;
long elDBID_Proj_RunDate = 0;
long elDBID_Proj_RulesetName = 0;
long elDBID_Proj_RulesetVersion = 0;
long elDBID_Proj_SoftwareVersion = 0;   // SAC 8/19/11 - revised name

long elDBID_Site_WeatherFile = 0;

//long elDBID_Spc_OccType = 0;
//long elDBID_Spc_Area = 0;
long elDBID_Spc_HVACSystem = 0;
long elDBID_Spc_Fan = 0;          // SAC 6/30/00
long elDBID_Spc_ExhaustFan = 0;   // SAC 6/30/00

long elDBID_FWall_Type = 0;

long elDBID_LtSys_Fixture1 = 0;
long elDBID_LtSys_Fixture2 = 0;
long elDBID_LtSys_Fixture3 = 0;
long elDBID_LtSys_Fixture4 = 0;

long elDBID_Sys_HtPump = 0;
long elDBID_Sys_AirCond = 0;
long elDBID_Sys_Furnace = 0;
long elDBID_Sys_AirEcon = 0;
long elDBID_Sys_SupplyFan = 0;
long elDBID_Sys_ReturnFan = 0;

long elDBID_CTwr_TowerPump = 0;

long elDBID_Chlr_CHWPump = 0;
long elDBID_Chlr_CWPump = 0;   // SAC 6/20/00 - added

long elDBID_Boil_HWPump = 0;

long elDBID_Plant_CHWPump = 0;     // SAC 6/20/00 - added
long elDBID_Plant_CWPump = 0;      // SAC 6/20/00 - added
long elDBID_Plant_HPCircPump = 0;  // SAC 6/20/00 - added
long elDBID_Plant_HWPump = 0;      // SAC 6/20/00 - added

long elDBID_Wiz_ScreenIdx = 0;
long elDBID_Wiz_ScreenID = 0;
long elDBID_Wiz_PrevScreenID = 0;
long elDBID_Wiz_NextScreenID = 0;
long	elDBID_Wiz_FootprintWMF = 0;
long	elDBID_Wiz_FPOrientXFrac = 0;
long	elDBID_Wiz_FPOrientYFrac = 0;
long	elDBID_Wiz_Orientation = 0;
long	elDBID_Wiz_EnableFinishBtn = 0;  // SAC 1/2/01

BOOL GetDialogTabDimensions( int iBDBClass, int& iTabCtrlWd, int& iTabCtrlHt )
{
	iTabCtrlWd = 600;
	iTabCtrlHt = 350;
	return TRUE;
}

void GetDialogCaption( int iBDBClass, CString& sDialogCaption )
{
	sDialogCaption = "Building Model Data";
}

void GetObjectConversionInfo( int /*iBEMClassFrom*/, int /*iBEMClassTo*/, int& iDlgID, int& iDlgWd, int& iDlgHt, CString& /*sNewNameAppend*/, 
										long& /*lNewObjAssignDBID*/, long& /*lNewConsAssmAssignDBID*/, CString& /*sDlgCaption*/, CStringArray& /*saFromProps*/, CStringArray& /*saToProps*/ )  // SAC 10/14/15
{	iDlgID = iDlgWd = iDlgHt-1;
}
#endif   // UI_ASHRAE901E

#ifdef UI_CANRES
int eiBDBCID_Project = 0;
int eiBDBCID_SchDay = 0;
int eiBDBCID_ThrmlEngyStorModeSchDay = 0;  // SAC 2/27/17
int eiBDBCID_SchWeek = 0;
int eiBDBCID_Schedule = 0;
int eiBDBCID_ConsAssm = 0;
int eiBDBCID_Mat = 0;
int eiBDBCID_FenCons = 0;
int eiBDBCID_DrCons = 0;
int eiBDBCID_SpcFuncDefaults = 0;
int eiBDBCID_Lum = 0;
int eiBDBCID_CrvLin = 0;
int eiBDBCID_CrvQuad = 0;
int eiBDBCID_CrvCubic = 0;
int eiBDBCID_CrvDblQuad = 0;
int eiBDBCID_EUseSummary = 0;
int eiBDBCID_PVArray = 0;
int eiBDBCID_PVArrayGeom = 0;
int eiBDBCID_PVArrayShade = 0;
int eiBDBCID_Battery = 0;

int eiBDBCID_ResProj = 0;     // SAC 10/20/21 (MFam)
int eiBDBCID_Building = 0;
int eiBDBCID_Story = 0;
int eiBDBCID_Space = 0;
int eiBDBCID_IntLtgSys = 0;
int eiBDBCID_DayltgCtrl = 0;
int eiBDBCID_Ceiling = 0;
int eiBDBCID_CeilingBelowAttic = 0;
int eiBDBCID_ExtFlr = 0;
int eiBDBCID_ExtWall = 0;
int eiBDBCID_FlrAboveCrawlSpc = 0;
int eiBDBCID_IntFlr = 0;
int eiBDBCID_IntWall = 0;
int eiBDBCID_Roof = 0;
int eiBDBCID_UndgrFlr = 0;
int eiBDBCID_UndgrWall = 0;
int eiBDBCID_Window = 0;
int eiBDBCID_Skylight = 0;
int eiBDBCID_Door = 0;
int eiBDBCID_PolyLp = 0;
int eiBDBCID_CartesianPt = 0;
int eiBDBCID_ExtShdgObj = 0;

int eiBDBCID_ThrmlZn = 0;
int eiBDBCID_AirSys = 0;
int eiBDBCID_VRFSys = 0;
int eiBDBCID_ZnSys = 0;
int eiBDBCID_AirSeg = 0;
int eiBDBCID_EvapClr = 0;
int eiBDBCID_CoilClg = 0;
int eiBDBCID_CoilHtg = 0;
int eiBDBCID_Fan = 0;
int eiBDBCID_TrmlUnit = 0;
int eiBDBCID_OACtrl = 0;

int eiBDBCID_FluidSys = 0;
int eiBDBCID_FluidSeg = 0;
int eiBDBCID_Chiller = 0;
int eiBDBCID_Boiler = 0;
int eiBDBCID_HtRej = 0;
int eiBDBCID_Pump = 0;
int eiBDBCID_RfrgEqp = 0;
int eiBDBCID_HtRcvry = 0;
int eiBDBCID_PrehtCoil = 0;
int eiBDBCID_ThrmlEngyStor = 0;
int eiBDBCID_HX = 0;
int eiBDBCID_ResDHWSys = 0;
int eiBDBCID_ResDWHRSys = 0;
int eiBDBCID_ResWtrHtr = 0;
int eiBDBCID_ResLpTankHtr = 0;	// SAC 1/12/20 (Com tic #3156)
int eiBDBCID_DHWSolarSys = 0;		// SAC 1/31/20 (Com tic #3157)
int eiBDBCID_ResSpcDHWFeatures = 0;
int eiBDBCID_ProcLd = 0;
int eiBDBCID_StorTank = 0;
int eiBDBCID_WtrHtr = 0;
//int eiBDBCID_BlrHtPump = 0;			// SAC 10/23/20      // removed BlrHtPump... - SAC 05/14/21


long elDBID_Proj_Name = 0;
long elDBID_Proj_RunDate = 0;
long elDBID_Proj_SoftwareVersion = 0;
long elDBID_Proj_WeatherPath = 0;       
long elDBID_Proj_WeatherStation = 0;    
long elDBID_Proj_DDWeatherFile = 0;     
long elDBID_Proj_AnnualWeatherFile = 0; 
long elDBID_Proj_ExcptDsgnModelFile = 0; 
long elDBID_PolyLp_Area = 0;
long elDBID_CartesianPt_Coord = 0;
long elDBID_Spc_ResSpcDHWFeaturesRef = 0;		// SAC 1/23/19
long elDBID_ThrmlZn_ClgSys = 0;             // "AirSys", 
long elDBID_ThrmlZn_SuppClgSys = 0;         // "AirSys", 
long elDBID_ThrmlZn_HtgSys = 0;             // "AirSys", 
long elDBID_ThrmlZn_SuppHtgSys = 0;         // "AirSys", 
long elDBID_ThrmlZn_VentSys = 0;            // "AirSys", 
long elDBID_ThrmlZn_ExhSys = 0;             // "AirSys", 
long elDBID_AirSeg_MakeupAirSys = 0;        // "AirSys",        
long elDBID_AirSeg_MakeupThrmlZn = 0;       // "ThrmlZn",       
long elDBID_CoilClg_FluidSegInRef = 0;      // "FluidSeg", 
long elDBID_CoilClg_FluidSegOutRef = 0;     // "FluidSeg", 
long elDBID_CoilHtg_FluidSegInRef = 0;      // "FluidSeg", 
long elDBID_CoilHtg_FluidSegOutRef = 0;     // "FluidSeg", 
long elDBID_TrmlUnit_ZnServedRef = 0;       // "ThrmlZn", 
long elDBID_TrmlUnit_PriFlowSegRef = 0;     // "AirSeg",  
long elDBID_TrmlUnit_HotDuctFlowSegRef = 0; // "AirSeg",  
long elDBID_TrmlUnit_InducedAirZnRef = 0;   // "ThrmlZn", 
long elDBID_OACtrl_AirSegSupRef = 0;        // "AirSeg",                 
long elDBID_OACtrl_AirSegRetRef = 0;        // "AirSeg",                 
long elDBID_FluidSeg_PriSegRef = 0;		     // "FluidSeg"
long elDBID_Chiller_CndsrInRef = 0;         // "FluidSeg"
long elDBID_Chiller_CndsrOutRef = 0;        // "FluidSeg"
long elDBID_Chiller_EvapInRef = 0;          // "FluidSeg"
long elDBID_Chiller_EvapOutRef = 0;         // "FluidSeg"
long elDBID_Boiler_FluidFlowInRef = 0;      // "FluidSeg"
long elDBID_Boiler_FluidFlowOutRef = 0;     // "FluidSeg"
//long elDBID_BlrHtPump_FluidSegInRef = 0;        // "FluidSeg"	SAC 10/23/20
//long elDBID_BlrHtPump_FluidSegOutRef = 0;       // "FluidSeg"

long elDBID_ResDHWSys_CentralSysType = 0;						// SAC 1/31/20 (Com tic #3156)
long elDBID_ResDHWSys_DHWSolarSysRef = 0;						// SAC 1/31/20 (Com tic #3157)
long elDBID_ResDHWSys_DHWHeater1 = 0;           // SAC 10/12/21 (MFam)
long elDBID_ResDHWSys_DHWHeater2 = 0;
long elDBID_ResDHWSys_DHWHeater3 = 0;
long elDBID_ResDHWSys_DHWHeater4 = 0;
long elDBID_ResDHWSys_DHWHeater5 = 0;
long elDBID_ResDHWSys_DHWHeater6 = 0;

long elDBID_INISettings_ProxyServerCredentials = 0;		// SAC 1/9/17
long elDBID_INISettings_ShowProxyServerCredentials = 0;	// SAC 1/9/17

int eiBDBCID_BatchRuns = 0;		// SAC 11/10/17
long elDBID_BatchRuns_BatchDefsCSV = 0;       
long elDBID_BatchRuns_BatchName = 0;          
long elDBID_BatchRuns_ProjDirectory = 0;     
long elDBID_BatchRuns_IncludeSubdirs = 0;     
long elDBID_BatchRuns_ProjFileNames = 0;     
long elDBID_BatchRuns_StoreProjToSepDir = 0; 
long elDBID_BatchRuns_OutputProjDir = 0;     
long elDBID_BatchRuns_RunsSpanClimates = 0;    // SAC 1/4/19 
long elDBID_BatchRuns_RunSetFile = 0;          // SAC 10/06/20
long elDBID_BatchRuns_RunSetFileStatus = 0;  
long elDBID_BatchRuns_RunSetDescrip = 0;   

// integration of CBECC-Res into CBECC-Com - SAC 04/27/21
int eiBDBCID_ResZnGrp = 0;
int eiBDBCID_ResConsAssm = 0;
int eiBDBCID_ResMat = 0;
int eiBDBCID_ResWinType = 0;
int eiBDBCID_ResZn = 0;
int eiBDBCID_DwellUnitType = 0;
int eiBDBCID_DwellUnit = 0;
int eiBDBCID_ResOtherZn = 0;
int eiBDBCID_ResAttic = 0;
//int eiBDBCID_ResGarage = 0;    - removed from UI - SAC 2/4/22
int eiBDBCID_ResCrawlSpc = 0;
int eiBDBCID_ResExtWall = 0;
int eiBDBCID_ResIntWall = 0;
int eiBDBCID_ResUndgrWall = 0;
int eiBDBCID_ResCathedralCeiling = 0;
int eiBDBCID_ResCeilingBelowAttic = 0;
int eiBDBCID_ResIntCeiling = 0;
int eiBDBCID_ResSlabFlr = 0;
int eiBDBCID_ResExtFlr = 0;
int eiBDBCID_ResFlrOverCrawlSpc = 0;
int eiBDBCID_ResIntFlr = 0;
int eiBDBCID_ResUndgrFlr = 0;
int eiBDBCID_ResOpening = 0;
int eiBDBCID_ResWin = 0;
int eiBDBCID_ResSkylt = 0;
int eiBDBCID_ResDr = 0;
int eiBDBCID_ResHVACSys = 0;     // SAC 11/02/21
int eiBDBCID_ResHtgSys = 0;      // SAC 08/18/21
int eiBDBCID_ResClgSys = 0;
int eiBDBCID_ResHtPumpSys = 0;
int eiBDBCID_ResCentralHtgClgSys = 0;  // SAC 12/31/21 (MFam)
int eiBDBCID_ResDistSys = 0;
int eiBDBCID_ResDuctSeg = 0;
int eiBDBCID_ResFanSys = 0;
int eiBDBCID_ResIAQFan = 0;
int eiBDBCID_ResCentralVentSys = 0;    // SAC 12/31/21 (MFam)
int eiBDBCID_ResClVentFan = 0;

BOOL GetDialogTabDimensions( int iBDBClass, int& iTabCtrlWd, int& iTabCtrlHt )
{
	     if (iBDBClass == eiBDBCID_Proj    )				{  iTabCtrlWd = 1010;    iTabCtrlHt = 580;   }	// SAC 11/8/14  // wd 900->1010 - SAC 04/21/22
	else if (iBDBClass == eiBDBCID_ResProj)         	{  iTabCtrlWd =  960;    iTabCtrlHt = 460;   }	// SAC 10/20/21 (MFam)
	else if (iBDBClass == eiBDBCID_EUseSummary)			{  iTabCtrlWd =  900;    iTabCtrlHt = 555;   }	// SAC 12/28/17  // SAC 9/15/20 - ht 495->515  // wd: 810->900 - SAC 12/08/21  // wd: 515->555 - SAC 12/12/21
	else if (iBDBClass == eiBDBCID_AirSys  )				{  iTabCtrlWd =  910;    iTabCtrlHt = 580;   }  // added - SAC 05/17/22
	else if (iBDBClass == eiBDBCID_AirSeg  )				{  iTabCtrlWd =  520;    iTabCtrlHt = 530;   }  // wider - SAC 05/17/22
	else if (iBDBClass == eiBDBCID_FluidSeg)				{  iTabCtrlWd =  470;    iTabCtrlHt = 530;   }	// SAC 4/30/14
	else if (iBDBClass == eiBDBCID_Space   )				{  iTabCtrlWd = 1010;    iTabCtrlHt = 580;   }	// SAC 3/4/14 - reduced ht for lower-res screens/projectors
   else if (iBDBClass == eiBDBCID_SpcFuncDefaults)    {  iTabCtrlWd =  950;    iTabCtrlHt = 640;   }
	else if (iBDBClass == eiBDBCID_IntLtgSys)				{  iTabCtrlWd =  900;    iTabCtrlHt = 580;   }	// SAC SAC 1/31/15
	else if (iBDBClass == eiBDBCID_Schedule)				{  iTabCtrlWd = 1010;    iTabCtrlHt = 690;   }	// SAC 3/4/14 - reduced ht for lower-res screens/projectors
	else if (iBDBClass == eiBDBCID_SchWeek )				{  iTabCtrlWd =  550;    iTabCtrlHt = 620;   }
	else if (iBDBClass == eiBDBCID_SchDay  )				{  iTabCtrlWd =  530;    iTabCtrlHt = 560;   }
	else if (iBDBClass == eiBDBCID_ThrmlEngyStorModeSchDay )	{  iTabCtrlWd =  530;    iTabCtrlHt = 560;   }
	else if (iBDBClass == eiBDBCID_PolyLp  )				{  iTabCtrlWd =  730;    iTabCtrlHt = 535;   }
	else if (iBDBClass == eiBDBCID_ThrmlZn )				{  iTabCtrlWd =  900;    iTabCtrlHt = 570;   }	// SAC 10/29/14
	else if (iBDBClass == eiBDBCID_HtRcvry )				{  iTabCtrlWd =  900;    iTabCtrlHt = 580;   }  // SAC 05/17/22
	else if (iBDBClass == eiBDBCID_Fan     )				{  iTabCtrlWd =  900;    iTabCtrlHt = 580;   }  // SAC 05/17/22
	else if (iBDBClass == eiBDBCID_CoilHtg )				{  iTabCtrlWd =  900;    iTabCtrlHt = 590;   }  // SAC 05/17/22
//	else if (iBDBClass == eiBDBCID_CoilClg )				{  iTabCtrlWd =  900;    iTabCtrlHt = 550;   }
	else if (iBDBClass == eiBDBCID_PVArray      )		{  iTabCtrlWd =  770;    iTabCtrlHt = 620;   }	// SAC 7/13/18
	else if (iBDBClass == eiBDBCID_PVArrayGeom  )		{  iTabCtrlWd =  350;    iTabCtrlHt = 250;   }
	else if (iBDBClass == eiBDBCID_PVArrayShade )		{  iTabCtrlWd =  350;    iTabCtrlHt = 250;   }
	else if (iBDBClass == eiBDBCID_Battery      )		{  iTabCtrlWd =  730;    iTabCtrlHt = 550;   }	// SAC 7/16/18
	else if (iBDBClass == eiBDBCID_ResDWHRSys   && elRulesetCodeYear < 2022)      // restored previous Com dialog sizes for 2019 and earlier code vintages - SAC 10/15/21
                                             	  		{  iTabCtrlWd =  500;    iTabCtrlHt = 250;   }	// SAC 12/23/18
	else if (iBDBClass == eiBDBCID_ResDHWSys    && elRulesetCodeYear < 2022)
                                             	  		{  iTabCtrlWd =  900;    iTabCtrlHt = 610;   }	// SAC 1/12/20 (Com tic #3156)
	else if (iBDBClass == eiBDBCID_DHWSolarSys  && elRulesetCodeYear < 2022)
                                             	  		{  iTabCtrlWd =  600;    iTabCtrlHt = 480;   }	// SAC 1/31/20 (Com tic #3157)
	else if (iBDBClass == eiBDBCID_ResWtrHtr    && elRulesetCodeYear < 2022)
                                             	  		{  iTabCtrlWd = 900;    iTabCtrlHt = 550;   }
	else if (iBDBClass == eiBDBCID_ResLpTankHtr && elRulesetCodeYear < 2022)
                                             	  		{  iTabCtrlWd = 900;    iTabCtrlHt = 550;   }
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
	else if (iBDBClass == eiBDBCID_ResZnGrp)           {  iTabCtrlWd = 900;    iTabCtrlHt = 550;   }
	else if (iBDBClass == eiBDBCID_ResConsAssm)        {  iTabCtrlWd = 670;    iTabCtrlHt = 610;   }
	else if (iBDBClass == eiBDBCID_ResWinType)     	   {	iTabCtrlWd = 600;		iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_ResZn)     	      {  iTabCtrlWd = 750;    iTabCtrlHt = 450;   }
	else if (iBDBClass == eiBDBCID_DwellUnitType)     	{  iTabCtrlWd = 820;    iTabCtrlHt = 670;   }
	else if (iBDBClass == eiBDBCID_DwellUnit)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 450;   }
	else if (iBDBClass == eiBDBCID_ResOtherZn)     	   {  iTabCtrlWd = 820;    iTabCtrlHt = 670;   }	// SAC 9/3/19 - MFamProto
	else if (iBDBClass == eiBDBCID_ResAttic)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
//	else if (iBDBClass == eiBDBCID_ResGarage)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResCrawlSpc)        {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResExtWall)     	   {  iTabCtrlWd = 500;    iTabCtrlHt = 480;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 420;   }
	else if (iBDBClass == eiBDBCID_ResIntWall)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResUndgrWall)     	{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResCathedralCeiling)     	{  iTabCtrlWd = 550;    iTabCtrlHt = 480;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 420;   }
	else if (iBDBClass == eiBDBCID_ResCeilingBelowAttic)     	{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResIntCeiling)     	{  iTabCtrlWd = 500;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_ResSlabFlr)     	   {  iTabCtrlWd = 700;    iTabCtrlHt = 460;   }
	else if (iBDBClass == eiBDBCID_ResExtFlr)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResFlrOverCrawlSpc)     	{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResIntFlr)     	   {  iTabCtrlWd = 500;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_ResUndgrFlr)     	{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResOpening)       	{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }	// SAC 7/30/20 - MFamProto
	else if (iBDBClass == eiBDBCID_ResWin)     	      {	iTabCtrlWd = 650;		iTabCtrlHt = 610;   }	// was: iTabCtrlWd = 600;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_ResSkylt)     	   {  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResDr)     	      {  iTabCtrlWd = 550;    iTabCtrlHt = 360;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 300;   }
	else if (iBDBClass == eiBDBCID_ResHVACSys)			{	iTabCtrlWd = 750;		iTabCtrlHt = 540;   }
	else if (iBDBClass == eiBDBCID_ResHtgSys)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 510;   }      // SAC 08/18/21
	else if (iBDBClass == eiBDBCID_ResClgSys)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResHtPumpSys)   		{  iTabCtrlWd = 600;    iTabCtrlHt = 660;   }	// SAC 11/10/20 - Ht 580 -> 640   // Ht 640->660 - SAC 07/24/21
	else if (iBDBClass == eiBDBCID_ResCentralHtgClgSys) { iTabCtrlWd = 600;    iTabCtrlHt = 660;   }	// SAC 12/31/21 (MFam)
	else if (iBDBClass == eiBDBCID_ResDistSys)	   	{  iTabCtrlWd = 600;    iTabCtrlHt = 510;   }	// was: iTabCtrlWd = 600;    iTabCtrlHt = 430;
	else if (iBDBClass == eiBDBCID_ResFanSys)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
	else if (iBDBClass == eiBDBCID_ResIAQFan)	  			{  iTabCtrlWd = 660;    iTabCtrlHt = 510;   }	// SAC 2/7/20 (Res tic #1174)
	else if (iBDBClass == eiBDBCID_ResCentralVentSys)	{  iTabCtrlWd = 660;    iTabCtrlHt = 510;   }	// SAC 12/31/21 (MFam)
	else if (iBDBClass == eiBDBCID_ResClVentFan)	  		{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }
   // integrated Res DHW UI into Com - SAC 10/12/21 (MFam)
	else if (iBDBClass == eiBDBCID_ResDHWSys)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 670;   }	// increased ht from 510 to 540 - SAC 2/16/18 (tic #978)   - ht 540 -> 610 SAC 12/5/18 (tic #975)   - ht 610 -> 640 SAC 12/2/19   - ht 640->670 SAC 5/12/20
	else if (iBDBClass == eiBDBCID_DHWSolarSys)			{  iTabCtrlWd = 600;    iTabCtrlHt = 480;   }	// SAC 1/12/20 (Res tic #1013)  - SAC 6/11/20 (tic #1210)
	else if (iBDBClass == eiBDBCID_ResDWHRSys)	   	{  iTabCtrlWd = 400;    iTabCtrlHt = 250;   }	// SAC 12/23/18
	else if (iBDBClass == eiBDBCID_ResWtrHtr)	  			{  iTabCtrlWd = 600;    iTabCtrlHt = 600;   }	// Ht was 440 - increased to allow for UEF water heater labels   // ht 540->600 - SAC 01/31/21
	else if (iBDBClass == eiBDBCID_ResLpTankHtr)	      {  iTabCtrlWd = 600;    iTabCtrlHt = 500;   }

	else                                					{  iTabCtrlWd =  900;    iTabCtrlHt = 550;   }
	return TRUE;
}

void GetDialogCaption( int /*iBDBClass*/, CString& sDialogCaption )
{
	sDialogCaption = "Building Model Data";
}

void GetObjectConversionInfo( int iBEMClassFrom, int iBEMClassTo, int& iDlgID, int& iDlgWd, int& iDlgHt, CString& sNewNameAppend,
										long& lNewObjAssignDBID, long& lNewConsAssmAssignDBID, CString& sDlgCaption, CStringArray& saFromProps, CStringArray& saToProps )  // SAC 10/14/15
{	bool bWallConversion = false;
	if (     iBEMClassFrom == eiBDBCID_ExtWall && iBEMClassTo == eiBDBCID_IntWall)
	{	iDlgID =  810;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-iw";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToIntWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToIntWallConsRef", iBEMClassFrom );
	}
	else if (iBEMClassFrom == eiBDBCID_ExtWall && iBEMClassTo == eiBDBCID_UndgrWall)
	{	iDlgID =  812;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-uw";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToUndgrWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToUndgrWallConsRef", iBEMClassFrom );
	}
	else if (iBEMClassFrom == eiBDBCID_IntWall && iBEMClassTo == eiBDBCID_ExtWall)
	{	iDlgID = 1110;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-ew";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToExtWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToExtWallConsRef", iBEMClassFrom );
	}
	else if (iBEMClassFrom == eiBDBCID_IntWall && iBEMClassTo == eiBDBCID_UndgrWall)
	{	iDlgID = 1112;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-uw";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToUndgrWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToUndgrWallConsRef", iBEMClassFrom );
	}
	else if (iBEMClassFrom == eiBDBCID_UndgrWall && iBEMClassTo == eiBDBCID_ExtWall)
	{	iDlgID = 1410;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-ew";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToExtWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToExtWallConsRef", iBEMClassFrom );
	}
	else if (iBEMClassFrom == eiBDBCID_UndgrWall && iBEMClassTo == eiBDBCID_IntWall)
	{	iDlgID = 1412;   iDlgWd = 900;   iDlgHt = 550;		sNewNameAppend = "-iw";		bWallConversion = true;
		lNewObjAssignDBID      = BEMPX_GetDatabaseID( "ConvToIntWallRef",     iBEMClassFrom );
		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToIntWallConsRef", iBEMClassFrom );
	}
	else
	{	iDlgID = iDlgWd = iDlgHt = lNewObjAssignDBID = lNewConsAssmAssignDBID = -1;
	}

	if (iDlgID > 0 && bWallConversion)
	{			saFromProps.Add( "Status" );			saToProps.Add( "Status" );
				saFromProps.Add( "ConsAssmRef" );	saToProps.Add( "ConsAssmRef" );
		CString sGeometryInpType;
		if (BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:GeometryInpType" ), sGeometryInpType ) &&
			!sGeometryInpType.IsEmpty() && sGeometryInpType.CompareNoCase("Simplified") == 0)
		{		saFromProps.Add( "Area" );				saToProps.Add( "Area" );
		}
		if ( (iBEMClassFrom == eiBDBCID_ExtWall || iBEMClassFrom == eiBDBCID_UndgrWall) &&
			  (iBEMClassTo   == eiBDBCID_ExtWall || iBEMClassTo   == eiBDBCID_UndgrWall) )
		{		saFromProps.Add( "Hgt" );				saToProps.Add( "Hgt" );
		}
	}
	sDlgCaption = "Building Model Data";
}

#endif   // UI_CANRES

#ifdef UI_CARES
int eiBDBCID_RESNETBldg = 0;		// SAC 9/27/20
int eiBDBCID_DwellUnitType = 0;	// SAC 6/18/14
int eiBDBCID_DwellUnit     = 0;
int eiBDBCID_Zone       = 0;
int eiBDBCID_OtherZone  = 0;	// SAC 9/3/19 - MFamProto
int eiBDBCID_Garage     = 0;
int eiBDBCID_Attic      = 0;
int eiBDBCID_CrawlSpace = 0;
int eiBDBCID_ExtWall    = 0;
int eiBDBCID_IntWall    = 0;
int eiBDBCID_UndWall    = 0;
int eiBDBCID_UndFloor   = 0;
//int eiBDBCID_AtticRoof  = 0;
int eiBDBCID_CathedralCeiling = 0;
int eiBDBCID_CeilingBelowAttic = 0;
int eiBDBCID_SlabFloor  = 0;
int eiBDBCID_ExteriorFloor = 0;
int eiBDBCID_FloorOverCrawl = 0;
int eiBDBCID_InteriorFloor = 0;
int eiBDBCID_InteriorCeiling = 0;
int eiBDBCID_Opening    = 0;	// SAC 7/30/20 - MFamProto
int eiBDBCID_Win        = 0;
int eiBDBCID_Skylt      = 0;
int eiBDBCID_Door       = 0;
int eiBDBCID_Cons       = 0;
int eiBDBCID_Mat        = 0;
int eiBDBCID_WindowType = 0;  // SAC 8/27/13
int eiBDBCID_PVArrayGeom = 0;
int eiBDBCID_Shade      = 0;
int eiBDBCID_PolyLp     = 0;
int eiBDBCID_CartesianPt = 0;
int eiBDBCID_HVACSys    = 0;
int eiBDBCID_HVACHeat   = 0;
int eiBDBCID_HVACCool   = 0;
int eiBDBCID_HVACHtPump = 0;
int eiBDBCID_HVACDist   = 0;
int eiBDBCID_HVACFan    = 0;
int eiBDBCID_IAQFan     = 0;
int eiBDBCID_ClVentFan  = 0;
int eiBDBCID_DHWSys     = 0;
int eiBDBCID_DHWSolarSys= 0;	// SAC 1/12/20 (Res tic #1013)
int eiBDBCID_DWHRSys    = 0;	// SAC 12/23/18
int eiBDBCID_DHWHeater  = 0;
int eiBDBCID_DHWLoopTankHeater  = 0;
int eiBDBCID_SCSysRpt   = 0;
int eiBDBCID_DHWSysRpt  = 0;
int eiBDBCID_IAQVentRpt = 0;
int eiBDBCID_EUseSummary = 0;

long elDBID_Proj_Name = 0;
long elDBID_Proj_RunDate = 0;
long elDBID_Proj_SoftwareVersion = 0;
long elDBID_Proj_SoftwareVersionDetail = 0;
long elDBID_Proj_AnalysisType = 0;    // SAC 9/12/11
long elDBID_Proj_IsMultiFamily = 0;   // SAC 7/29/16
long elDBID_Proj_RunTitle = 0;    // SAC 1/8/12
long elDBID_Proj_ElecMETER = 0;			// SAC 6/19/12
long elDBID_Proj_NatGasMETER = 0;		// SAC 6/19/12
long elDBID_Proj_OtherFuelMETER = 0;	// SAC 6/19/12
long elDBID_Proj_RHERSEnabled = 0;		// SAC 9/28/20
//extern long elDBID_Site_WeatherFile;
	// SAC 12/9/13 - added several Zone properties to enhance tree display to confirm to E+A+A assignments
long elDBID_Zone_HVACSysStatus = 0;			//	BEMP_Sym,   0,                            3008, "Status of HVAC System - New, Altered or Existing"                                      
long elDBID_Zone_HVACSysVerified = 0;		// BEMP_Int,   0,                            3008, "existing HVAC System will be HERS verified"
long elDBID_Zone_HVACSystem = 0;				// BEMP_Obj,   1, "HVACSys",  3, "Status",   3006, "New HVAC system assignment" 
long elDBID_Zone_AltHVACSystem = 0;			// BEMP_Obj,   1, "HVACSys",  2, "Status",   3006, "Altered HVAC system assignment" 
long elDBID_Zone_exHVACSystem = 0;			// BEMP_Obj,   1, "HVACSys",  1, "Status",   3006, "Existing HVAC system assignment" 
long elDBID_Zone_DHWSys1Status = 0;			// BEMP_Sym,   0,                            3008, "Status of DHW System 1 - New, Altered or Existing"                                      
long elDBID_Zone_DHWSys1Verified = 0;		// BEMP_Int,   0,                            3008, "existing DHW System 1 will be HERS verified"
long elDBID_Zone_DHWSys1 = 0;					// BEMP_Obj,   1, "DHWSys",  3, "Status",    1003, "DHW System 1 assignment" 
long elDBID_Zone_AltDHWSys1 = 0;				// BEMP_Obj,   1, "DHWSys",  2, "Status",    3006, "Altered DHW1 system assignment" 
long elDBID_Zone_exDHWSys1 = 0;				// BEMP_Obj,   1, "DHWSys",  1, "Status",    3006, "Existing DHW1 system assignment" 
long elDBID_Zone_DHWSys2Status = 0;			// BEMP_Sym,   0,                            3008, "Status of DHW System 2 - New, Altered or Existing"                                      
long elDBID_Zone_DHWSys2Verified = 0;		// BEMP_Int,   0,                            3008, "existing DHW System 2 conditions will be HERS verified"
long elDBID_Zone_DHWSys2 = 0;					// BEMP_Obj,   1, "DHWSys",  3, "Status",    1003, "DHW System 2 assignment" 
long elDBID_Zone_AltDHWSys2 = 0;				// BEMP_Obj,   1, "DHWSys",  2, "Status",    3006, "Altered DHW2 system assignment" 
long elDBID_Zone_exDHWSys2 = 0;				// BEMP_Obj,   1, "DHWSys",  1, "Status",    3006, "Existing DHW2 system assignment" 
//long elDBID_SURFACE_sfType = 0;
long elDBID_Attic_Construction = 0;
long elDBID_ExtWall_Construction = 0;
long elDBID_IntWall_Construction = 0;
long elDBID_UndWall_Construction = 0;
//long elDBID_AtticRoof_Construction = 0;
long elDBID_CathedralCeiling_Construction = 0;
long elDBID_CeilingBelowAttic_Construction = 0;
long elDBID_ExteriorFloor_Construction = 0;
long elDBID_FloorOverCrawl_Construction = 0;
long elDBID_InteriorFloor_Construction = 0;
long elDBID_InteriorCeiling_Construction = 0;
long elDBID_PVArrayGeom_IsBldgAttached = 0;     // BEMP_Int   - SAC 3/2/17
long elDBID_Shade_Type = 0;            // BEMP_Sym ->  0:"- select type -"  1:"Site Shade"  2:"Building Shade"   - SAC 2/21/17
long elDBID_PolyLp_Area = 0;
long elDBID_CartesianPt_Coord = 0;       // BEMP_Flt,  3,  0,  1, "ft",  "X, Y, Z coordinates of polyloop vertex"   - SAC 2/21/17
long elDBID_Cons_Materials1  = 0;
long elDBID_Cons_Materials2  = 0;
long elDBID_Cons_Materials3  = 0;
long elDBID_Cons_Materials4  = 0;
long elDBID_Cons_Materials5  = 0;
long elDBID_Cons_Materials6  = 0;
long elDBID_Cons_Materials7  = 0;
long elDBID_Cons_Materials8  = 0;
long elDBID_Cons_Materials9  = 0;
long elDBID_Cons_Materials10 = 0;
long elDBID_HVAC_HeatSystem1 = 0; 
long elDBID_HVAC_HeatSystem2 = 0; 
long elDBID_HVAC_HeatSystem3 = 0; 
long elDBID_HVAC_HeatSystem4 = 0; 
long elDBID_HVAC_HeatSystem5 = 0; 
long elDBID_HVAC_HeatSystem6 = 0; 
long elDBID_HVAC_HeatSystem7 = 0; 
long elDBID_HVAC_HeatSystem8 = 0; 
long elDBID_HVAC_HeatSystem9 = 0; 
long elDBID_HVAC_HeatSystem10 = 0;
long elDBID_HVAC_CoolSystem1 = 0; 
long elDBID_HVAC_CoolSystem2 = 0; 
long elDBID_HVAC_CoolSystem3 = 0; 
long elDBID_HVAC_CoolSystem4 = 0; 
long elDBID_HVAC_CoolSystem5 = 0; 
long elDBID_HVAC_CoolSystem6 = 0; 
long elDBID_HVAC_CoolSystem7 = 0; 
long elDBID_HVAC_CoolSystem8 = 0; 
long elDBID_HVAC_CoolSystem9 = 0; 
long elDBID_HVAC_CoolSystem10 = 0;
long elDBID_HVAC_HtPumpSystem1 = 0; 
long elDBID_HVAC_HtPumpSystem2 = 0; 
long elDBID_HVAC_HtPumpSystem3 = 0; 
long elDBID_HVAC_HtPumpSystem4 = 0; 
long elDBID_HVAC_HtPumpSystem5 = 0; 
long elDBID_HVAC_HtPumpSystem6 = 0; 
long elDBID_HVAC_HtPumpSystem7 = 0; 
long elDBID_HVAC_HtPumpSystem8 = 0; 
long elDBID_HVAC_HtPumpSystem9 = 0; 
long elDBID_HVAC_HtPumpSystem10 = 0;
long elDBID_HVAC_DistribSystem = 0;
long elDBID_HVAC_Fan = 0;
long elDBID_HVACHeat_CHWHeater = 0;
long elDBID_DHWSys_DHWSolarSysRef = 0;	// SAC 1/12/20 (Res tic #1013)
long elDBID_DHWSys_DHWHeater1 = 0;
long elDBID_DHWSys_DHWHeater2 = 0;
long elDBID_DHWSys_DHWHeater3 = 0;
long elDBID_DHWSys_DHWHeater4 = 0;
long elDBID_DHWSys_DHWHeater5 = 0;
long elDBID_DHWSys_DHWHeater6 = 0;
long elDBID_DHWSys_LoopHeater	= 0;	// SAC 11/19/19
long elDBID_DHWSys_CentralDHWType = 0;	// SAC 1/21/20
long elDBID_INISettings_ProxyServerCredentials = 0;		// SAC 1/9/17
long elDBID_INISettings_ShowProxyServerCredentials = 0;	// SAC 1/9/17

int eiBDBCID_BatchRuns = 0;		// SAC 11/10/17
long elDBID_BatchRuns_BatchDefsCSV = 0;       
long elDBID_BatchRuns_BatchName = 0;          
long elDBID_BatchRuns_ProjDirectory = 0;     
long elDBID_BatchRuns_IncludeSubdirs = 0;     
long elDBID_BatchRuns_ProjFileNames = 0;     
long elDBID_BatchRuns_StoreProjToSepDir = 0; 
long elDBID_BatchRuns_OutputProjDir = 0;     
long elDBID_BatchRuns_RunsSpanClimates = 0;    // SAC 1/4/19 
long elDBID_BatchRuns_RunSetFile = 0;          // SAC 10/21/20
long elDBID_BatchRuns_RunSetFileStatus = 0;  
long elDBID_BatchRuns_RunSetDescrip = 0;   

BOOL GetDialogTabDimensions( int iBDBClass, int& iTabCtrlWd, int& iTabCtrlHt )
{
	     if (iBDBClass == eiBDBCID_Proj)      			{  iTabCtrlWd = 960;    iTabCtrlHt = 460;   }	// was: iTabCtrlHt = 370;   - SAC 3/21/19 wd: 850->890   - SAC 11/9/19 wd: 890->960   - SAC 4/24/20 ht: 400->460
	else if (iBDBClass == eiBDBCID_EUseSummary)			{  if (elRulesetCodeYear >= 2022)
																			{	iTabCtrlWd = 1080;    iTabCtrlHt = 570;		}		// SAC 6/12/19 - accommodate additional columns in 2022 results   // SAC 12/02/20 - Ht 520->570
																			else
																			{	iTabCtrlWd =  810;    iTabCtrlHt = 520;		}  }	// SAC 12/28/17
	else if (iBDBClass == eiBDBCID_RESNETBldg)			{  iTabCtrlWd = 960;    iTabCtrlHt = 460;   }	// SAC 9/27/20
	else if (iBDBClass == eiBDBCID_DwellUnitType)		{  iTabCtrlWd = 820;    iTabCtrlHt = 670;   }
	else if (iBDBClass == eiBDBCID_DwellUnit)				{  iTabCtrlWd = 600;    iTabCtrlHt = 450;   }
	else if (iBDBClass == eiBDBCID_Zone)      			{  iTabCtrlWd = 750;    iTabCtrlHt = 450;   }
	else if (iBDBClass == eiBDBCID_OtherZone)   			{  iTabCtrlWd = 820;    iTabCtrlHt = 670;   }	// SAC 9/3/19 - MFamProto
	else if (iBDBClass == eiBDBCID_ExtWall)      		{  iTabCtrlWd = 500;    iTabCtrlHt = 480;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 420;   }
	else if (iBDBClass == eiBDBCID_InteriorFloor)  		{  iTabCtrlWd = 500;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_InteriorCeiling)		{  iTabCtrlWd = 500;    iTabCtrlHt = 510;   }
//	else if (iBDBClass == eiBDBCID_AtticRoof)    		{  iTabCtrlWd = 450;    iTabCtrlHt = 420;   }
	else if (iBDBClass == eiBDBCID_CathedralCeiling)	{  iTabCtrlWd = 550;    iTabCtrlHt = 480;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 420;   }
	else if (iBDBClass == eiBDBCID_SlabFloor)				{  iTabCtrlWd = 700;    iTabCtrlHt = 460;   }
	else if (iBDBClass == eiBDBCID_Opening)   			{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }	// SAC 7/30/20 - MFamProto
	else if (iBDBClass == eiBDBCID_Win    )				{	iTabCtrlWd = 650;		iTabCtrlHt = 610;   }	// was: iTabCtrlWd = 600;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_WindowType)			{	iTabCtrlWd = 600;		iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_Door   )	   		{  iTabCtrlWd = 550;    iTabCtrlHt = 360;   }	// was: iTabCtrlWd = 450;    iTabCtrlHt = 300;   }
	else if (iBDBClass == eiBDBCID_Cons   )	   		{  iTabCtrlWd = 670;    iTabCtrlHt = 610;   }
	else if (iBDBClass == eiBDBCID_PVArrayGeom )			{  iTabCtrlWd = 350;    iTabCtrlHt = 250;   }	// SAC 3/2/17
	else if (iBDBClass == eiBDBCID_Shade  )				{  iTabCtrlWd = 350;    iTabCtrlHt = 250;   }	// SAC 2/22/17
	else if (iBDBClass == eiBDBCID_PolyLp  )				{  iTabCtrlWd = 730;    iTabCtrlHt = 535;   }	// SAC 2/21/17
	else if (iBDBClass == eiBDBCID_HVACSys)				{	iTabCtrlWd = 750;		iTabCtrlHt = 540;   }
	else if (iBDBClass == eiBDBCID_HVACHeat)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 510;   }
	else if (iBDBClass == eiBDBCID_HVACHtPump)   		{  iTabCtrlWd = 600;    iTabCtrlHt = 660;   }	// SAC 11/10/20 - Ht 580 -> 640   // Ht 640->660 - SAC 07/24/21
	else if (iBDBClass == eiBDBCID_HVACDist)	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 510;   }	// was: iTabCtrlWd = 600;    iTabCtrlHt = 430;
	else if (iBDBClass == eiBDBCID_IAQFan)	   			{  iTabCtrlWd = 660;    iTabCtrlHt = 510;   }	// SAC 2/7/20 (Res tic #1174)
	else if (iBDBClass == eiBDBCID_DHWSys)	   			{  iTabCtrlWd = 600;    iTabCtrlHt = 670;   }	// increased ht from 510 to 540 - SAC 2/16/18 (tic #978)   - ht 540 -> 610 SAC 12/5/18 (tic #975)   - ht 610 -> 640 SAC 12/2/19   - ht 640->670 SAC 5/12/20
	else if (iBDBClass == eiBDBCID_DHWSolarSys)			{  iTabCtrlWd = 600;    iTabCtrlHt = 480;   }	// SAC 1/12/20 (Res tic #1013)  - SAC 6/11/20 (tic #1210)
	else if (iBDBClass == eiBDBCID_DWHRSys)	   		{  iTabCtrlWd = 400;    iTabCtrlHt = 250;   }	// SAC 12/23/18
	else if (iBDBClass == eiBDBCID_DHWHeater)	  			{  iTabCtrlWd = 600;    iTabCtrlHt = 600;   }	// Ht was 440 - increased to allow for UEF water heater labels   // ht 540->600 - SAC 01/31/21
	else if (iBDBClass == eiBDBCID_DHWLoopTankHeater)	{  iTabCtrlWd = 600;    iTabCtrlHt = 500;   }
	else if (iBDBClass == eiBDBCID_SCSysRpt)				{	iTabCtrlWd = 750;		iTabCtrlHt = 540;   }
	else if (iBDBClass == eiBDBCID_DHWSysRpt)				{	iTabCtrlWd = 750;		iTabCtrlHt = 540;   }
	else if (iBDBClass == eiBDBCID_IAQVentRpt)			{	iTabCtrlWd = 750;		iTabCtrlHt = 540;   }
	else if (iBDBClass == eiBDBCID_INISettings)			{  iTabCtrlWd = 900;    iTabCtrlHt = 550;   }
	else                                   	   		{  iTabCtrlWd = 600;    iTabCtrlHt = 410;   }	// was: iTabCtrlWd = 600;    iTabCtrlHt = 350;   }
	return TRUE;
}

void GetDialogCaption( int iBDBClass, CString& sDialogCaption )
{
	sDialogCaption.Empty();

	if (iBDBClass <= eiBDBCID_Proj || iBDBClass == eiBDBCID_EUseSummary) // SAC 12/20/18 - revised to use project file naming for EUSummary dialog (per KN request)
	{	// first portion of caption = project filename (excluding path & file extension)
		CWnd* pMainWnd = AfxGetMainWnd();
	   if (pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
		{	CDocument* pDoc = ((CFrameWnd*)pMainWnd)->GetActiveDocument();
		   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CDocument)))
			{	CString sProjFile = pDoc->GetPathName();
				if (!sProjFile.IsEmpty() && sProjFile.ReverseFind('\\') > 0)
				{	sProjFile = sProjFile.Right( sProjFile.GetLength() - sProjFile.ReverseFind('\\') - 1 );
					if (!sProjFile.IsEmpty() && sProjFile.ReverseFind('.') > 0)
						sProjFile = sProjFile.Left( sProjFile.ReverseFind('.') );
					sDialogCaption = sProjFile;
				}
			}
		}
		// second portion of caption = Proj:RunTitle
		CString sRunTitle;
	   BEMPX_SetDataString( elDBID_Proj_RunTitle, sRunTitle );
		if (!sRunTitle.IsEmpty())
		{	if (!sDialogCaption.IsEmpty())
				sDialogCaption += " - ";
			sDialogCaption += sRunTitle;
		}
	}
	else	// SAC 12/5/18 - revised routine to label non-Proj dialogs using object type and name data
	{	int iErr;
		BEMClass* pBEMClass = BEMPX_GetClass( iBDBClass, iErr );
		if (pBEMClass)
		{	QString qsObjName;
			VERIFY( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iBDBClass ), qsObjName, FALSE, 0, -1 ) && !qsObjName.isEmpty() );
			sDialogCaption.Format( "%s:  %s", pBEMClass->getLongName().toLatin1().constData(), qsObjName.toLatin1().constData() );
	}	}

	// default string if neither project filename nor RunTitle are defined
	if (sDialogCaption.IsEmpty())
		sDialogCaption = "Building Model Data";
}

void GetObjectConversionInfo( int /*iBEMClassFrom*/, int /*iBEMClassTo*/, int& iDlgID, int& iDlgWd, int& iDlgHt, CString& /*sNewNameAppend*/, 
										long& /*lNewObjAssignDBID*/, long& /*lNewConsAssmAssignDBID*/, CString& /*sDlgCaption*/, CStringArray& /*saFromProps*/, CStringArray& /*saToProps*/ )  // SAC 10/14/15
{	iDlgID = iDlgWd = iDlgHt-1;
}
#endif   // UI_CARES


#ifdef UI_CANRES
void AdjustDataModelForGeometryInpType()
{
	if (!ebAppInitialized)
		return;	// if the application has not been initialized yet, then 

// SAC 2/27/14 - added new code to determine if project is in "Simplified" (2D) geometry mode, in which case we make various accomodations
//	long lIsDetailedGeometry = 1;
//	BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "IsDetailedGeometry", eiBDBCID_Proj ), lIsDetailedGeometry, 1 /*default*/ );
	CString sGeometryInpType;
	long lIsDetailedGeometry = (BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:GeometryInpType" ), sGeometryInpType ) &&
											!sGeometryInpType.IsEmpty() && sGeometryInpType.CompareNoCase("Simplified") == 0) ? 0 : 1;
	if (lIsDetailedGeometry == 0)
	{	// set certain CIDs to 0 that we do NOT want the user to create/access/etc. when in simplified geometry mode
		eiBDBCID_PolyLp      = 0;
		eiBDBCID_CartesianPt = 0;
		eiBDBCID_ExtShdgObj  = 0;
	}

	CMX_AdjustDataModelForGeometryInpType_CECNonRes();  // ported remaining logic to BEMCmpMgr.dll
}
#endif   // UI_CANRES


void InitBEMDBIDs()
{
#ifdef UI_ASHRAE901E
   eiBDBCID_Proj     = BEMPX_GetDBComponentID( "Proj" );
   elDBID_Proj_Ruleset        = BEMPX_GetDatabaseID( "Ruleset",        eiBDBCID_Proj );
	elDBID_Proj_StdsVersion = 0;	// SAC 8/15/14

   eiBDBCID_Run      = BEMPX_GetDBComponentID( "Run" );
   eiBDBCID_Site     = BEMPX_GetDBComponentID( "Site" );
   eiBDBCID_Bldg     = BEMPX_GetDBComponentID( "Bldg" );
   eiBDBCID_Bshade   = BEMPX_GetDBComponentID( "Bshade" );
   eiBDBCID_Block    = BEMPX_GetDBComponentID( "Block" );
   eiBDBCID_Floor    = BEMPX_GetDBComponentID( "Floor" );
   eiBDBCID_Space    = BEMPX_GetDBComponentID( "Space" );
   eiBDBCID_ActArea  = BEMPX_GetDBComponentID( "ActArea" );
   eiBDBCID_LtSys    = BEMPX_GetDBComponentID( "LtSys" );
   eiBDBCID_LtFix    = BEMPX_GetDBComponentID( "LtFix" );
   eiBDBCID_ExtWall  = BEMPX_GetDBComponentID( "ExtWall" );
   eiBDBCID_ExtRoof  = BEMPX_GetDBComponentID( "ExtRoof" );
   eiBDBCID_IntWall  = BEMPX_GetDBComponentID( "IntWall" );
   eiBDBCID_IntCeil  = BEMPX_GetDBComponentID( "IntCeil" );
   eiBDBCID_UndWall  = BEMPX_GetDBComponentID( "UndWall" );
   eiBDBCID_FlrWall  = BEMPX_GetDBComponentID( "FlrWall" );
   eiBDBCID_Win      = BEMPX_GetDBComponentID( "Win" );
   eiBDBCID_Skylt    = BEMPX_GetDBComponentID( "Skylt" );
   eiBDBCID_Door     = BEMPX_GetDBComponentID( "Door" );
   eiBDBCID_Cons     = BEMPX_GetDBComponentID( "Cons" );
   eiBDBCID_Layers   = BEMPX_GetDBComponentID( "Layers" );
   eiBDBCID_Mat      = BEMPX_GetDBComponentID( "Mat" );
   eiBDBCID_HVACSys  = BEMPX_GetDBComponentID( "HVACSys" );
   eiBDBCID_Size     = BEMPX_GetDBComponentID( "Size" );
   eiBDBCID_HtPump   = BEMPX_GetDBComponentID( "HtPump" );
   eiBDBCID_AirCond  = BEMPX_GetDBComponentID( "AirCond" );
   eiBDBCID_Furn     = BEMPX_GetDBComponentID( "Furn" );
   eiBDBCID_Econ     = BEMPX_GetDBComponentID( "Econ" );
   eiBDBCID_Plant    = BEMPX_GetDBComponentID( "Plant" );
   eiBDBCID_Fan      = BEMPX_GetDBComponentID( "Fan" );
   eiBDBCID_ClTower  = BEMPX_GetDBComponentID( "ClTower" );
   eiBDBCID_Chiller  = BEMPX_GetDBComponentID( "Chiller" );
   eiBDBCID_Boiler   = BEMPX_GetDBComponentID( "Boiler" );
   eiBDBCID_Pump     = BEMPX_GetDBComponentID( "Pump" );
   eiBDBCID_Curve    = BEMPX_GetDBComponentID( "Curve" );
   eiBDBCID_Sched    = BEMPX_GetDBComponentID( "Sched" );
   eiBDBCID_WkSch    = BEMPX_GetDBComponentID( "WkSch" );
   eiBDBCID_DaySch   = BEMPX_GetDBComponentID( "DaySch" );
   eiBDBCID_ResSch   = BEMPX_GetDBComponentID( "ResSch" );
   eiBDBCID_DResSch  = BEMPX_GetDBComponentID( "DResSch" );
   eiBDBCID_Wizard   = BEMPX_GetDBComponentID( "Wizard" );
   eiBDBCID_AreaWiz  = BEMPX_GetDBComponentID( "AreaWiz" );
   eiBDBCID_HVACWiz  = BEMPX_GetDBComponentID( "HVACWiz" );
   eiBDBCID_PlantWiz = BEMPX_GetDBComponentID( "PlantWiz" );  // SAC 5/26/00 - added

   elDBID_Proj_Name           = BEMPX_GetDatabaseID( "Name",           eiBDBCID_Proj );
   elDBID_Proj_ArchTreeOption = BEMPX_GetDatabaseID( "ArchTreeOption", eiBDBCID_Proj );
   elDBID_Proj_FinalResult    = BEMPX_GetDatabaseID( "FinalResult",    eiBDBCID_Proj );
   elDBID_Proj_RunDate        = BEMPX_GetDatabaseID( "RunDate",        eiBDBCID_Proj );
   elDBID_Proj_RulesetName    = BEMPX_GetDatabaseID( "RulesetName",    eiBDBCID_Proj );
   elDBID_Proj_RulesetVersion = BEMPX_GetDatabaseID( "RulesetVersion", eiBDBCID_Proj );
   elDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "CCPVersion",     eiBDBCID_Proj );  // SAC 8/19/11

   elDBID_Site_WeatherFile    = BEMPX_GetDatabaseID( "WeatherFile",    eiBDBCID_Site );

//   elDBID_Spc_OccType    = BEMPX_GetDatabaseID( "OccType",    eiBDBCID_Space );
//   elDBID_Spc_Area       = BEMPX_GetDatabaseID( "Area",       eiBDBCID_Space );
   elDBID_Spc_HVACSystem = BEMPX_GetDatabaseID( "HVACSystem", eiBDBCID_Space );
   elDBID_Spc_Fan        = BEMPX_GetDatabaseID( "Fan",        eiBDBCID_Space );   // SAC 6/30/00
   elDBID_Spc_ExhaustFan = BEMPX_GetDatabaseID( "ExhaustFan", eiBDBCID_Space );   // SAC 6/30/00

   elDBID_FWall_Type     = BEMPX_GetDatabaseID( "Type", eiBDBCID_FlrWall );

   elDBID_LtSys_Fixture1 = BEMPX_GetDatabaseID( "Fixture[1]", eiBDBCID_LtSys );
   elDBID_LtSys_Fixture2 = BEMPX_GetDatabaseID( "Fixture[2]", eiBDBCID_LtSys );
   elDBID_LtSys_Fixture3 = BEMPX_GetDatabaseID( "Fixture[3]", eiBDBCID_LtSys );
   elDBID_LtSys_Fixture4 = BEMPX_GetDatabaseID( "Fixture[4]", eiBDBCID_LtSys );

   elDBID_Sys_HtPump    = BEMPX_GetDatabaseID( "HtPump",    eiBDBCID_HVACSys );
   elDBID_Sys_AirCond   = BEMPX_GetDatabaseID( "AirCond",   eiBDBCID_HVACSys );
   elDBID_Sys_Furnace   = BEMPX_GetDatabaseID( "Furnace",   eiBDBCID_HVACSys );
   elDBID_Sys_AirEcon   = BEMPX_GetDatabaseID( "AirEcon",   eiBDBCID_HVACSys );
   elDBID_Sys_SupplyFan = BEMPX_GetDatabaseID( "SupplyFan", eiBDBCID_HVACSys );
   elDBID_Sys_ReturnFan = BEMPX_GetDatabaseID( "ReturnFan", eiBDBCID_HVACSys );

   elDBID_CTwr_TowerPump = BEMPX_GetDatabaseID( "TowerPump", eiBDBCID_ClTower );

   elDBID_Chlr_CHWPump   = BEMPX_GetDatabaseID( "CHWPump",   eiBDBCID_Chiller );
   elDBID_Chlr_CWPump    = BEMPX_GetDatabaseID( "CWPump",    eiBDBCID_Chiller );

   elDBID_Boil_HWPump    = BEMPX_GetDatabaseID( "HWPump",    eiBDBCID_Boiler );

   elDBID_Plant_CHWPump    = BEMPX_GetDatabaseID( "CHWPump",    eiBDBCID_Plant );
   elDBID_Plant_CWPump     = BEMPX_GetDatabaseID( "CWPump",     eiBDBCID_Plant );
   elDBID_Plant_HPCircPump = BEMPX_GetDatabaseID( "HPCircPump", eiBDBCID_Plant );
   elDBID_Plant_HWPump     = BEMPX_GetDatabaseID( "HWPump",     eiBDBCID_Plant );

   elDBID_Wiz_ScreenIdx       = BEMPX_GetDatabaseID( "ScreenIdx",       eiBDBCID_Wizard );
   elDBID_Wiz_ScreenID        = BEMPX_GetDatabaseID( "ScreenID",        eiBDBCID_Wizard );
   elDBID_Wiz_PrevScreenID    = BEMPX_GetDatabaseID( "PrevScreenID",    eiBDBCID_Wizard );
   elDBID_Wiz_NextScreenID    = BEMPX_GetDatabaseID( "NextScreenID",    eiBDBCID_Wizard );
   elDBID_Wiz_Ruleset         = BEMPX_GetDatabaseID( "Ruleset",         eiBDBCID_Wizard );
   elDBID_Wiz_FootprintWMF    = BEMPX_GetDatabaseID( "FootprintWMF",    eiBDBCID_Wizard );
   elDBID_Wiz_FPOrientXFrac   = BEMPX_GetDatabaseID( "FPOrientXFrac",   eiBDBCID_Wizard );
   elDBID_Wiz_FPOrientYFrac   = BEMPX_GetDatabaseID( "FPOrientYFrac",   eiBDBCID_Wizard );
   elDBID_Wiz_Orientation     = BEMPX_GetDatabaseID( "Orientation",     eiBDBCID_Wizard );
   elDBID_Wiz_EnableFinishBtn = BEMPX_GetDatabaseID( "EnableFinishBtn", eiBDBCID_Wizard );  // SAC 1/2/01
#endif   // UI_ASHRAE901E

#ifdef UI_CANRES
   eiBDBCID_Proj        = BEMPX_GetDBComponentID( "Project" );
   elDBID_Proj_Ruleset  = BEMPX_GetDatabaseID( "Ruleset", eiBDBCID_Proj );
	eiBDBCID_BEMVersion		= BEMPX_GetDBComponentID( "BEMVersion" );						// SAC 9/17/12
	elDBID_Proj_BEMVersion	= BEMPX_GetDatabaseID( "BldgEngyModelVersion", eiBDBCID_Proj );		// SAC 9/17/12
	eiBDBCID_INISettings		= BEMPX_GetDBComponentID( "INISettings" );					// SAC 5/31/14
	elDBID_Proj_StdsVersion = BEMPX_GetDatabaseID( "StdsVersion", eiBDBCID_Proj );	// SAC 8/15/14		// SAC 11/22/15
	elDBID_Proj_DefaultOptionInp  = BEMPX_GetDatabaseID( "DefaultOptionInp",  eiBDBCID_Proj );	// SAC 4/11/18
	elDBID_Proj_DefaultOptionObj  = BEMPX_GetDatabaseID( "DefaultOptionObj",  eiBDBCID_Proj );
	elDBID_Proj_DefaultOptionDone = BEMPX_GetDatabaseID( "DefaultOptionDone", eiBDBCID_Proj );
	elDBID_Proj_AnalysisVersion   = BEMPX_GetDatabaseID( "AnalysisVersion",   eiBDBCID_Proj );   // SAC 05/30/22

   eiBDBCID_Project            = BEMPX_GetDBComponentID( "Project" );
   eiBDBCID_SchDay             = BEMPX_GetDBComponentID( "SchDay" );
   eiBDBCID_ThrmlEngyStorModeSchDay = BEMPX_GetDBComponentID( "ThrmlEngyStorModeSchDay" );
   eiBDBCID_SchWeek            = BEMPX_GetDBComponentID( "SchWeek" );
   eiBDBCID_Schedule           = BEMPX_GetDBComponentID( "Schedule" );
   eiBDBCID_ConsAssm           = BEMPX_GetDBComponentID( "ConsAssm" );
   eiBDBCID_Mat                = BEMPX_GetDBComponentID( "Mat" );
   eiBDBCID_FenCons            = BEMPX_GetDBComponentID( "FenCons" );
   eiBDBCID_DrCons             = BEMPX_GetDBComponentID( "DrCons" );
   eiBDBCID_SpcFuncDefaults    = BEMPX_GetDBComponentID( "SpcFuncDefaults" );
   eiBDBCID_Lum                = BEMPX_GetDBComponentID( "Lum" );
   eiBDBCID_CrvLin             = BEMPX_GetDBComponentID( "CrvLin" );
   eiBDBCID_CrvQuad            = BEMPX_GetDBComponentID( "CrvQuad" );
   eiBDBCID_CrvCubic           = BEMPX_GetDBComponentID( "CrvCubic" );
   eiBDBCID_CrvDblQuad         = BEMPX_GetDBComponentID( "CrvDblQuad" );
	eiBDBCID_EUseSummary        = BEMPX_GetDBComponentID( "EUseSummary" );
	eiBDBCID_PVArray            = BEMPX_GetDBComponentID( "PVArray"      );
	eiBDBCID_PVArrayGeom        = BEMPX_GetDBComponentID( "PVArrayGeom"  );
	eiBDBCID_PVArrayShade       = BEMPX_GetDBComponentID( "PVArrayShade" );
	eiBDBCID_Battery            = BEMPX_GetDBComponentID( "Battery"      );

   eiBDBCID_ResProj            = BEMPX_GetDBComponentID( "ResProj" );         // SAC 10/20/21 (MFam)
   eiBDBCID_Building           = BEMPX_GetDBComponentID( "Building" );
   eiBDBCID_Story              = BEMPX_GetDBComponentID( "Story" );
   eiBDBCID_Space              = BEMPX_GetDBComponentID( "Space" );
   eiBDBCID_IntLtgSys          = BEMPX_GetDBComponentID( "IntLtgSys" );
   eiBDBCID_DayltgCtrl         = BEMPX_GetDBComponentID( "DayltgCtrl" );
   eiBDBCID_Ceiling            = BEMPX_GetDBComponentID( "Ceiling" );
   eiBDBCID_CeilingBelowAttic  = BEMPX_GetDBComponentID( "CeilingBelowAttic" );
   eiBDBCID_ExtFlr             = BEMPX_GetDBComponentID( "ExtFlr" );
   eiBDBCID_ExtWall            = BEMPX_GetDBComponentID( "ExtWall" );
   eiBDBCID_FlrAboveCrawlSpc   = BEMPX_GetDBComponentID( "FlrAboveCrawlSpc" );
   eiBDBCID_IntFlr             = BEMPX_GetDBComponentID( "IntFlr" );
   eiBDBCID_IntWall            = BEMPX_GetDBComponentID( "IntWall" );
   eiBDBCID_Roof               = BEMPX_GetDBComponentID( "Roof" );
   eiBDBCID_UndgrFlr           = BEMPX_GetDBComponentID( "UndgrFlr" );
   eiBDBCID_UndgrWall          = BEMPX_GetDBComponentID( "UndgrWall" );
   eiBDBCID_Window             = BEMPX_GetDBComponentID( "Window" );
   eiBDBCID_Skylight           = BEMPX_GetDBComponentID( "Skylight" );
   eiBDBCID_Door               = BEMPX_GetDBComponentID( "Door" );
   eiBDBCID_PolyLp             = BEMPX_GetDBComponentID( "PolyLp" );
   eiBDBCID_CartesianPt        = BEMPX_GetDBComponentID( "CartesianPt" );
	eiBDBCID_ExtShdgObj         = BEMPX_GetDBComponentID( "ExtShdgObj" );
   
   eiBDBCID_ThrmlZn            = BEMPX_GetDBComponentID( "ThrmlZn" );
   eiBDBCID_AirSys             = BEMPX_GetDBComponentID( "AirSys" );
   eiBDBCID_VRFSys             = BEMPX_GetDBComponentID( "VRFSys" );     // SAC 6/28/18 - comment out VRFSys for Com 16.3.0 SP2 - restored 7/13/18
   eiBDBCID_ZnSys              = BEMPX_GetDBComponentID( "ZnSys" );
   eiBDBCID_AirSeg             = BEMPX_GetDBComponentID( "AirSeg" );
   eiBDBCID_EvapClr            = BEMPX_GetDBComponentID( "EvapClr" );
   eiBDBCID_CoilClg            = BEMPX_GetDBComponentID( "CoilClg" );
   eiBDBCID_CoilHtg            = BEMPX_GetDBComponentID( "CoilHtg" );
   eiBDBCID_Fan                = BEMPX_GetDBComponentID( "Fan" );
   eiBDBCID_TrmlUnit           = BEMPX_GetDBComponentID( "TrmlUnit" );
   eiBDBCID_OACtrl             = BEMPX_GetDBComponentID( "OACtrl" );

	eiBDBCID_FluidSys           = BEMPX_GetDBComponentID( "FluidSys" ); 
	eiBDBCID_FluidSeg           = BEMPX_GetDBComponentID( "FluidSeg" ); 
	eiBDBCID_Chiller            = BEMPX_GetDBComponentID( "Chiller" );  
	eiBDBCID_Boiler             = BEMPX_GetDBComponentID( "Boiler" );   
	eiBDBCID_HtRej              = BEMPX_GetDBComponentID( "HtRej" );    
	eiBDBCID_Pump               = BEMPX_GetDBComponentID( "Pump" );     
	eiBDBCID_RfrgEqp            = BEMPX_GetDBComponentID( "RfrgEqp" );       
	eiBDBCID_HtRcvry            = BEMPX_GetDBComponentID( "HtRcvry" );     
	eiBDBCID_PrehtCoil          = BEMPX_GetDBComponentID( "PrehtCoil" );     
	eiBDBCID_ThrmlEngyStor      = BEMPX_GetDBComponentID( "ThrmlEngyStor" );		// SAC 2/21/17
	eiBDBCID_HX                 = BEMPX_GetDBComponentID( "HX" );            
	eiBDBCID_ResDHWSys          = BEMPX_GetDBComponentID( "ResDHWSys" );
	eiBDBCID_ResDWHRSys         = BEMPX_GetDBComponentID( "ResDWHRSys" );	// SAC 1/24/19
	eiBDBCID_ResWtrHtr          = BEMPX_GetDBComponentID( "ResWtrHtr" );
	eiBDBCID_ResLpTankHtr       = BEMPX_GetDBComponentID( "ResLpTankHtr" );	// SAC 1/12/20 (Com tic #3156)
	eiBDBCID_DHWSolarSys        = BEMPX_GetDBComponentID( "DHWSolarSys" );	// SAC 1/31/20 (Com tic #3157)
      if (eiBDBCID_DHWSolarSys < 1)
         eiBDBCID_DHWSolarSys  = BEMPX_GetDBComponentID( "DHWSolSys" );    // address rename of DHWSolarSys to DHWSolSys between 2019 & 2022 rulesets - SAC 10/12/21 (MFam)
	eiBDBCID_ResSpcDHWFeatures  = BEMPX_GetDBComponentID( "ResSpcDHWFeatures" );
	eiBDBCID_ProcLd             = BEMPX_GetDBComponentID( "ProcLd" );        
	eiBDBCID_StorTank           = BEMPX_GetDBComponentID( "StorTank" );      
	eiBDBCID_WtrHtr             = BEMPX_GetDBComponentID( "WtrHtr" );        
//	eiBDBCID_BlrHtPump          = BEMPX_GetDBComponentID( "BlrHtPump" );        // removed BlrHtPump... - SAC 05/14/21

   elDBID_Proj_Name               = BEMPX_GetDatabaseID( "Name",               eiBDBCID_Project );
   elDBID_Proj_RunDate            = BEMPX_GetDatabaseID( "RunDate",            eiBDBCID_Project );
   elDBID_Proj_SoftwareVersion    = BEMPX_GetDatabaseID( "SoftwareVersion",    eiBDBCID_Project );
	elDBID_Proj_WeatherPath        = BEMPX_GetDatabaseID( "WeatherPath",        eiBDBCID_Project );       
	elDBID_Proj_WeatherStation     = BEMPX_GetDatabaseID( "WeatherStation",     eiBDBCID_Project );    
	elDBID_Proj_DDWeatherFile      = BEMPX_GetDatabaseID( "DDWeatherFile",      eiBDBCID_Project );     
	elDBID_Proj_AnnualWeatherFile  = BEMPX_GetDatabaseID( "AnnualWeatherFile",  eiBDBCID_Project ); 
	elDBID_Proj_ExcptDsgnModelFile = BEMPX_GetDatabaseID( "ExcptDsgnModelFile", eiBDBCID_Project ); 

	elDBID_PolyLp_Area            = BEMPX_GetDatabaseID( "Area",  eiBDBCID_PolyLp );			// SAC 5/29/14 
	elDBID_CartesianPt_Coord      = BEMPX_GetDatabaseID( "Coord", eiBDBCID_CartesianPt );	// SAC 5/29/14 

	elDBID_Spc_ResSpcDHWFeaturesRef    = BEMPX_GetDatabaseID( "ResSpcDHWFeaturesRef", eiBDBCID_Space );	// SAC 1/23/19

	elDBID_ThrmlZn_ClgSys              = BEMPX_GetDatabaseID( "ClgSys",             eiBDBCID_ThrmlZn  ); 
	elDBID_ThrmlZn_SuppClgSys          = BEMPX_GetDatabaseID( "SuppClgSys",         eiBDBCID_ThrmlZn  ); 
	elDBID_ThrmlZn_HtgSys              = BEMPX_GetDatabaseID( "HtgSys",             eiBDBCID_ThrmlZn  ); 
	elDBID_ThrmlZn_SuppHtgSys          = BEMPX_GetDatabaseID( "SuppHtgSys",         eiBDBCID_ThrmlZn  ); 
	elDBID_ThrmlZn_VentSys             = BEMPX_GetDatabaseID( "VentSys",            eiBDBCID_ThrmlZn  ); 
	elDBID_ThrmlZn_ExhSys              = BEMPX_GetDatabaseID( "ExhSys",             eiBDBCID_ThrmlZn  ); 
	elDBID_AirSeg_MakeupAirSys         = BEMPX_GetDatabaseID( "MakeupAirSys",       eiBDBCID_AirSeg   ); 
	elDBID_AirSeg_MakeupThrmlZn        = BEMPX_GetDatabaseID( "MakeupThrmlZn",      eiBDBCID_AirSeg   ); 
	elDBID_CoilClg_FluidSegInRef       = BEMPX_GetDatabaseID( "FluidSegInRef",      eiBDBCID_CoilClg );
	elDBID_CoilClg_FluidSegOutRef      = BEMPX_GetDatabaseID( "FluidSegOutRef",     eiBDBCID_CoilClg );
	elDBID_CoilHtg_FluidSegInRef       = BEMPX_GetDatabaseID( "FluidSegInRef",      eiBDBCID_CoilHtg );
	elDBID_CoilHtg_FluidSegOutRef      = BEMPX_GetDatabaseID( "FluidSegOutRef",     eiBDBCID_CoilHtg );
	elDBID_TrmlUnit_ZnServedRef        = BEMPX_GetDatabaseID( "ZnServedRef",        eiBDBCID_TrmlUnit ); 
	elDBID_TrmlUnit_PriFlowSegRef      = BEMPX_GetDatabaseID( "PriFlowSegRef",      eiBDBCID_TrmlUnit ); 
	elDBID_TrmlUnit_HotDuctFlowSegRef  = BEMPX_GetDatabaseID( "HotDuctFlowSegRef",  eiBDBCID_TrmlUnit ); 
	elDBID_TrmlUnit_InducedAirZnRef    = BEMPX_GetDatabaseID( "InducedAirZnRef",    eiBDBCID_TrmlUnit ); 
	elDBID_OACtrl_AirSegSupRef         = BEMPX_GetDatabaseID( "AirSegSupRef",       eiBDBCID_OACtrl   ); 
	elDBID_OACtrl_AirSegRetRef         = BEMPX_GetDatabaseID( "AirSegRetRef",       eiBDBCID_OACtrl   ); 

	elDBID_FluidSeg_PriSegRef    		  = BEMPX_GetDatabaseID( "PriSegRef",          eiBDBCID_FluidSeg );
	elDBID_Chiller_CndsrInRef          = BEMPX_GetDatabaseID( "CndsrInRef",         eiBDBCID_Chiller  );
	elDBID_Chiller_CndsrOutRef         = BEMPX_GetDatabaseID( "CndsrOutRef",        eiBDBCID_Chiller  );
	elDBID_Chiller_EvapInRef           = BEMPX_GetDatabaseID( "EvapInRef",          eiBDBCID_Chiller  );
	elDBID_Chiller_EvapOutRef          = BEMPX_GetDatabaseID( "EvapOutRef",         eiBDBCID_Chiller  );
	elDBID_Boiler_FluidFlowInRef       = BEMPX_GetDatabaseID( "FluidFlowInRef",     eiBDBCID_Boiler   );
	elDBID_Boiler_FluidFlowOutRef      = BEMPX_GetDatabaseID( "FluidFlowOutRef",    eiBDBCID_Boiler   );
//	elDBID_BlrHtPump_FluidSegInRef     = BEMPX_GetDatabaseID( "FluidSegInRef",      eiBDBCID_BlrHtPump   );     // removed BlrHtPump... - SAC 05/14/21
//	elDBID_BlrHtPump_FluidSegOutRef    = BEMPX_GetDatabaseID( "FluidSegOutRef",     eiBDBCID_BlrHtPump   );

	elDBID_ResDHWSys_CentralSysType    = BEMPX_GetDatabaseID( "CentralSysType",     eiBDBCID_ResDHWSys );	// SAC 1/31/20 (Com tic #3156)
	elDBID_ResDHWSys_DHWSolarSysRef    = BEMPX_GetDatabaseID( "DHWSolarSysRef",     eiBDBCID_ResDHWSys );	// SAC 1/31/20 (Com tic #3157)
	elDBID_ResDHWSys_DHWHeater1	     = BEMPX_GetDatabaseID( "DHWHeater", eiBDBCID_ResDHWSys );    // SAC 10/12/21 (MFam)
	elDBID_ResDHWSys_DHWHeater2	     = elDBID_ResDHWSys_DHWHeater1 + 1;
	elDBID_ResDHWSys_DHWHeater3	     = elDBID_ResDHWSys_DHWHeater2 + 1;
	elDBID_ResDHWSys_DHWHeater4	     = elDBID_ResDHWSys_DHWHeater3 + 1;
	elDBID_ResDHWSys_DHWHeater5	     = elDBID_ResDHWSys_DHWHeater4 + 1;
	elDBID_ResDHWSys_DHWHeater6	     = elDBID_ResDHWSys_DHWHeater5 + 1;

	elDBID_INISettings_ProxyServerCredentials      = BEMPX_GetDatabaseID( "ProxyServerCredentials",      eiBDBCID_INISettings  );		// SAC 1/9/17
	elDBID_INISettings_ShowProxyServerCredentials  = BEMPX_GetDatabaseID( "ShowProxyServerCredentials",  eiBDBCID_INISettings  ); 

	eiBDBCID_BatchRuns = BEMPX_GetDBComponentID( "BatchRuns" );
	elDBID_BatchRuns_BatchDefsCSV       = BEMPX_GetDatabaseID( "BatchDefsCSV",       eiBDBCID_BatchRuns );       
	elDBID_BatchRuns_BatchName          = BEMPX_GetDatabaseID( "BatchName",          eiBDBCID_BatchRuns );          
	elDBID_BatchRuns_ProjDirectory      = BEMPX_GetDatabaseID( "ProjDirectory",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_IncludeSubdirs     = BEMPX_GetDatabaseID( "IncludeSubdirs",     eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_ProjFileNames      = BEMPX_GetDatabaseID( "ProjFileNames",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_StoreProjToSepDir  = BEMPX_GetDatabaseID( "StoreProjToSepDir",  eiBDBCID_BatchRuns ); 
	elDBID_BatchRuns_OutputProjDir      = BEMPX_GetDatabaseID( "OutputProjDir",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_RunsSpanClimates   = BEMPX_GetDatabaseID( "RunsSpanClimates",   eiBDBCID_BatchRuns );    // SAC 1/4/19 
   elDBID_BatchRuns_RunSetFile         = BEMPX_GetDatabaseID( "RunSetFile",         eiBDBCID_BatchRuns );    // SAC 10/06/20
   elDBID_BatchRuns_RunSetFileStatus   = BEMPX_GetDatabaseID( "RunSetFileStatus",   eiBDBCID_BatchRuns );  
   elDBID_BatchRuns_RunSetDescrip      = BEMPX_GetDatabaseID( "RunSetDescrip",      eiBDBCID_BatchRuns );   

   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   eiBDBCID_ResZnGrp              = BEMPX_GetDBComponentID( "ResZnGrp" );
   eiBDBCID_ResConsAssm           = BEMPX_GetDBComponentID( "ResConsAssm" );                    
   eiBDBCID_ResMat                = BEMPX_GetDBComponentID( "ResMat" );                    
   eiBDBCID_ResWinType            = BEMPX_GetDBComponentID( "ResWinType" );                    
   eiBDBCID_ResZn                 = BEMPX_GetDBComponentID( "ResZn" );                    
   eiBDBCID_DwellUnitType         = BEMPX_GetDBComponentID( "DwellUnitType" );                    
   eiBDBCID_DwellUnit             = BEMPX_GetDBComponentID( "DwellUnit" );                    
   eiBDBCID_ResOtherZn            = BEMPX_GetDBComponentID( "ResOtherZn" );                    
   eiBDBCID_ResAttic              = BEMPX_GetDBComponentID( "ResAttic" );                    
//   eiBDBCID_ResGarage             = BEMPX_GetDBComponentID( "ResGarage" );                    
   eiBDBCID_ResCrawlSpc           = BEMPX_GetDBComponentID( "ResCrawlSpc" );                    
   eiBDBCID_ResExtWall            = BEMPX_GetDBComponentID( "ResExtWall" );                    
   eiBDBCID_ResIntWall            = BEMPX_GetDBComponentID( "ResIntWall" );                    
   eiBDBCID_ResUndgrWall          = BEMPX_GetDBComponentID( "ResUndgrWall" );                    
   eiBDBCID_ResCathedralCeiling   = BEMPX_GetDBComponentID( "ResCathedralCeiling" );                    
   eiBDBCID_ResCeilingBelowAttic  = BEMPX_GetDBComponentID( "ResCeilingBelowAttic" );                    
   eiBDBCID_ResIntCeiling         = BEMPX_GetDBComponentID( "ResIntCeiling" );                    
   eiBDBCID_ResSlabFlr            = BEMPX_GetDBComponentID( "ResSlabFlr" );                    
   eiBDBCID_ResExtFlr             = BEMPX_GetDBComponentID( "ResExtFlr" );                    
   eiBDBCID_ResFlrOverCrawlSpc    = BEMPX_GetDBComponentID( "ResFlrOverCrawlSpc" );                    
   eiBDBCID_ResIntFlr             = BEMPX_GetDBComponentID( "ResIntFlr" );                    
   eiBDBCID_ResUndgrFlr           = BEMPX_GetDBComponentID( "ResUndgrFlr" );                    
   eiBDBCID_ResOpening            = BEMPX_GetDBComponentID( "ResOpening" );                    
   eiBDBCID_ResWin                = BEMPX_GetDBComponentID( "ResWin" );                    
   eiBDBCID_ResSkylt              = BEMPX_GetDBComponentID( "ResSkylt" );                    
   eiBDBCID_ResDr                 = BEMPX_GetDBComponentID( "ResDr" );                 
   eiBDBCID_ResHVACSys            = BEMPX_GetDBComponentID( "ResHVACSys" );     // SAC 11/02/21
   eiBDBCID_ResHtgSys             = BEMPX_GetDBComponentID( "ResHtgSys" );      // SAC 08/18/21
   eiBDBCID_ResClgSys             = BEMPX_GetDBComponentID( "ResClgSys" );
   eiBDBCID_ResHtPumpSys          = BEMPX_GetDBComponentID( "ResHtPumpSys" );
   eiBDBCID_ResCentralHtgClgSys   = BEMPX_GetDBComponentID( "ResCentralHtgClgSys" );   // SAC 12/31/21 (MFam)
   eiBDBCID_ResDistSys            = BEMPX_GetDBComponentID( "ResDistSys" );
   eiBDBCID_ResDuctSeg            = BEMPX_GetDBComponentID( "ResDuctSeg" );
   eiBDBCID_ResFanSys             = BEMPX_GetDBComponentID( "ResFanSys" );
   eiBDBCID_ResIAQFan             = BEMPX_GetDBComponentID( "ResIAQFan" );
   eiBDBCID_ResCentralVentSys     = BEMPX_GetDBComponentID( "ResCentralVentSys" );     // SAC 12/31/21 (MFam)
   eiBDBCID_ResClVentFan          = BEMPX_GetDBComponentID( "ResClVentFan" );

// SAC 5/13/14 - revised to keep this property characterized as Required (but still marked as Primary)
	// make adjustments to the InputClass of certain properties to ensure proper UI functionality
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "ConsAssm:CompatibleSurfType" ), BEMD_Required, true /*bPrimary*/, true /*bEditable*/, false /*bUserDefaultable*/, true /*bDispInp*/, true /*bDispProp*/,
																															true /*bDispBudg*/, DTNotInp_AllowUIReset /*iNotInputMode*/, NULL /*pszNotInputMsg*/ );		// SAC 8/13/15

	AdjustDataModelForGeometryInpType();	// SAC 2/27/14

	BEMPUIX_AddPasswordDBIDPair( elDBID_INISettings_ProxyServerCredentials, elDBID_INISettings_ShowProxyServerCredentials, TRUE );	// SAC 1/9/17
#endif   // UI_CANRES

#ifdef UI_CARES
   eiBDBCID_Proj       = BEMPX_GetDBComponentID( "Proj" );
   elDBID_Proj_Ruleset        = BEMPX_GetDatabaseID( "Ruleset",        eiBDBCID_Proj );
	eiBDBCID_BEMVersion		= BEMPX_GetDBComponentID( "BEMVersion" );						// SAC 9/17/12
	elDBID_Proj_BEMVersion	= BEMPX_GetDatabaseID( "BEMVersion", eiBDBCID_Proj );		// SAC 9/17/12
	eiBDBCID_INISettings		= BEMPX_GetDBComponentID( "INISettings" );					// SAC 5/31/14
	elDBID_Proj_StdsVersion = BEMPX_GetDatabaseID( "StandardsVersion", eiBDBCID_Proj );;	// SAC 8/15/14
	elDBID_Proj_AnalysisVersion = BEMPX_GetDatabaseID( "AnalysisVersion", eiBDBCID_Proj );    // SAC 05/30/22

   eiBDBCID_RESNETBldg    = BEMPX_GetDBComponentID( "RESNETBldg" );		// SAC 9/27/20
   eiBDBCID_DwellUnitType = BEMPX_GetDBComponentID( "DwellUnitType" );	// SAC 6/18/14
   eiBDBCID_DwellUnit     = BEMPX_GetDBComponentID( "DwellUnit" );
   eiBDBCID_Zone       = BEMPX_GetDBComponentID( "Zone" );
   eiBDBCID_OtherZone  = (eiDeveloperMenu == 0 ? 0 : BEMPX_GetDBComponentID( "OtherZone" ));	// SAC 9/3/19 - MFamProto   // hide from tree when eiDeveloperMenu = 0 - SAC 03/30/21
   eiBDBCID_Garage     = BEMPX_GetDBComponentID( "Garage" );
   eiBDBCID_Attic      = BEMPX_GetDBComponentID( "Attic" );
   eiBDBCID_CrawlSpace = BEMPX_GetDBComponentID( "CrawlSpace" );
   eiBDBCID_ExtWall    = BEMPX_GetDBComponentID( "ExtWall" );
   eiBDBCID_IntWall    = BEMPX_GetDBComponentID( "IntWall" );
   eiBDBCID_UndWall    = BEMPX_GetDBComponentID( "UndWall" );
   eiBDBCID_UndFloor   = BEMPX_GetDBComponentID( "UndFloor" );
//	eiBDBCID_AtticRoof         = BEMPX_GetDBComponentID( "AtticRoof" );       
	eiBDBCID_CathedralCeiling  = BEMPX_GetDBComponentID( "CathedralCeiling" );       
	eiBDBCID_CeilingBelowAttic = BEMPX_GetDBComponentID( "CeilingBelowAttic" ); 
	eiBDBCID_SlabFloor         = BEMPX_GetDBComponentID( "SlabFloor" );         
	eiBDBCID_ExteriorFloor     = BEMPX_GetDBComponentID( "ExteriorFloor" );     
	eiBDBCID_FloorOverCrawl    = BEMPX_GetDBComponentID( "FloorOverCrawl" );     
	eiBDBCID_InteriorFloor     = BEMPX_GetDBComponentID( "InteriorFloor" );     
	eiBDBCID_InteriorCeiling   = BEMPX_GetDBComponentID( "InteriorCeiling" );     
   eiBDBCID_Opening    = BEMPX_GetDBComponentID( "Opening" );	// SAC 7/30/20 - MFamProto
	eiBDBCID_Win        = BEMPX_GetDBComponentID( "Win" );
	eiBDBCID_Skylt      = BEMPX_GetDBComponentID( "Skylt" );
	eiBDBCID_Door       = BEMPX_GetDBComponentID( "Door" );
	eiBDBCID_Cons       = BEMPX_GetDBComponentID( "Cons" );
	eiBDBCID_Mat        = BEMPX_GetDBComponentID( "Mat" );
	eiBDBCID_WindowType = BEMPX_GetDBComponentID( "WindowType" );  // SAC 8/27/13
	eiBDBCID_PVArrayGeom = BEMPX_GetDBComponentID( "PVArrayGeom" );	// SAC 3/2/17
	eiBDBCID_Shade      = BEMPX_GetDBComponentID( "Shade" );				// SAC 2/22/17
	eiBDBCID_PolyLp     = BEMPX_GetDBComponentID( "PolyLp" );			// SAC 2/21/17
	eiBDBCID_CartesianPt = BEMPX_GetDBComponentID( "CartesianPt" );	// SAC 2/21/17
	eiBDBCID_HVACSys    = BEMPX_GetDBComponentID( "HVACSys" );
   eiBDBCID_HVACHeat   = BEMPX_GetDBComponentID( "HVACHeat" );
   eiBDBCID_HVACCool   = BEMPX_GetDBComponentID( "HVACCool" );
   eiBDBCID_HVACHtPump = BEMPX_GetDBComponentID( "HVACHtPump" );
   eiBDBCID_HVACDist   = BEMPX_GetDBComponentID( "HVACDist" );
   eiBDBCID_HVACFan    = BEMPX_GetDBComponentID( "HVACFan" );
   eiBDBCID_IAQFan     = BEMPX_GetDBComponentID( "IAQFan" );
   eiBDBCID_ClVentFan  = BEMPX_GetDBComponentID( "ClVentFan" );
	eiBDBCID_DHWSys     = BEMPX_GetDBComponentID( "DHWSys" );
	eiBDBCID_DHWSolarSys= BEMPX_GetDBComponentID( "DHWSolarSys" );		// SAC 1/12/20 (Res tic #1013)
      if (eiBDBCID_DHWSolarSys < 1)
         eiBDBCID_DHWSolarSys  = BEMPX_GetDBComponentID( "DHWSolSys" );    // address rename of DHWSolarSys to DHWSolSys between 2019 & 2022 rulesets - SAC 10/12/21 (MFam)
	eiBDBCID_DWHRSys    = BEMPX_GetDBComponentID( "DWHRSys" );			// SAC 12/23/18
	eiBDBCID_DHWHeater  = BEMPX_GetDBComponentID( "DHWHeater" );
	eiBDBCID_DHWLoopTankHeater  = BEMPX_GetDBComponentID( "DHWLoopTankHeater" );	// SAC 11/14/19
	eiBDBCID_SCSysRpt   = BEMPX_GetDBComponentID( "SCSysRpt" );
	eiBDBCID_DHWSysRpt  = BEMPX_GetDBComponentID( "DHWSysRpt" );
	eiBDBCID_IAQVentRpt = BEMPX_GetDBComponentID( "IAQVentRpt" );
	eiBDBCID_EUseSummary        = BEMPX_GetDBComponentID( "EUseSummary" );

   elDBID_Proj_Name            = BEMPX_GetDatabaseID( "Name",            eiBDBCID_Proj );
   elDBID_Proj_RunDate         = BEMPX_GetDatabaseID( "RunDate",         eiBDBCID_Proj );
   elDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "SoftwareVersion", eiBDBCID_Proj );
   elDBID_Proj_SoftwareVersionDetail = BEMPX_GetDatabaseID( "SoftwareVersionDetail", eiBDBCID_Proj );
   elDBID_Proj_AnalysisType    = BEMPX_GetDatabaseID( "AnalysisType",    eiBDBCID_Proj );    // SAC 9/12/11
   elDBID_Proj_IsMultiFamily   = BEMPX_GetDatabaseID( "IsMultiFamily",   eiBDBCID_Proj );    // SAC 7/29/16
   elDBID_Proj_RunTitle        = BEMPX_GetDatabaseID( "RunTitle",		    eiBDBCID_Proj );    // SAC 1/8/12
   elDBID_Proj_ElecMETER       = BEMPX_GetDatabaseID( "ElecMETER",		 eiBDBCID_Proj );    // SAC 6/19/12
   elDBID_Proj_NatGasMETER     = BEMPX_GetDatabaseID( "NatGasMETER",		 eiBDBCID_Proj );    // SAC 6/19/12
   elDBID_Proj_OtherFuelMETER  = BEMPX_GetDatabaseID( "OtherFuelMETER",	 eiBDBCID_Proj );    // SAC 6/19/12
   elDBID_Proj_RHERSEnabled    = BEMPX_GetDatabaseID( "RHERSEnabled",	 eiBDBCID_Proj );    // SAC 9/28/20
   if (elDBID_Proj_RHERSEnabled < BEM_COMP_MULT)
		eiBDBCID_RESNETBldg = 0;

//   elDBID_SURFACE_sfType   = BEMPX_GetDatabaseID( "sfType",     eiBDBCID_SURFACE );

		// SAC 12/9/13 - added several Zone properties to enhance tree display to confirm to E+A+A assignments
	elDBID_Zone_HVACSysStatus		= BEMPX_GetDatabaseID( "HVACSysStatus",   eiBDBCID_Zone );
	elDBID_Zone_HVACSysVerified	= BEMPX_GetDatabaseID( "HVACSysVerified", eiBDBCID_Zone );
	elDBID_Zone_HVACSystem			= BEMPX_GetDatabaseID( "HVACSystem",      eiBDBCID_Zone );
	elDBID_Zone_AltHVACSystem		= BEMPX_GetDatabaseID( "AltHVACSystem",   eiBDBCID_Zone );
	elDBID_Zone_exHVACSystem		= BEMPX_GetDatabaseID( "exHVACSystem",    eiBDBCID_Zone );
	elDBID_Zone_DHWSys1Status		= BEMPX_GetDatabaseID( "DHWSys1Status",   eiBDBCID_Zone ); 
	elDBID_Zone_DHWSys1Verified	= BEMPX_GetDatabaseID( "DHWSys1Verified", eiBDBCID_Zone );
	elDBID_Zone_DHWSys1				= BEMPX_GetDatabaseID( "DHWSys1",         eiBDBCID_Zone );
	elDBID_Zone_AltDHWSys1			= BEMPX_GetDatabaseID( "AltDHWSys1",      eiBDBCID_Zone );
	elDBID_Zone_exDHWSys1			= BEMPX_GetDatabaseID( "exDHWSys1",       eiBDBCID_Zone );
	elDBID_Zone_DHWSys2Status		= BEMPX_GetDatabaseID( "DHWSys2Status",   eiBDBCID_Zone ); 
	elDBID_Zone_DHWSys2Verified	= BEMPX_GetDatabaseID( "DHWSys2Verified", eiBDBCID_Zone );
	elDBID_Zone_DHWSys2				= BEMPX_GetDatabaseID( "DHWSys2",         eiBDBCID_Zone );
	elDBID_Zone_AltDHWSys2			= BEMPX_GetDatabaseID( "AltDHWSys2",      eiBDBCID_Zone );
	elDBID_Zone_exDHWSys2			= BEMPX_GetDatabaseID( "exDHWSys2",       eiBDBCID_Zone );

	elDBID_Attic_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_Attic );

	elDBID_ExtWall_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_ExtWall );

	elDBID_IntWall_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_IntWall );

	elDBID_UndWall_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_UndWall );

//	elDBID_AtticRoof_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_AtticRoof );
	elDBID_CathedralCeiling_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_CathedralCeiling );
	elDBID_CeilingBelowAttic_Construction = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_CeilingBelowAttic );
	elDBID_ExteriorFloor_Construction     = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_ExteriorFloor     );
	elDBID_FloorOverCrawl_Construction    = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_FloorOverCrawl    );
	elDBID_InteriorFloor_Construction     = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_InteriorFloor     );
	elDBID_InteriorCeiling_Construction   = BEMPX_GetDatabaseID( "Construction",   eiBDBCID_InteriorCeiling   );

	elDBID_Cons_Materials1  = BEMPX_GetDatabaseID( "Materials[1]",  eiBDBCID_Cons );
	elDBID_Cons_Materials2  = BEMPX_GetDatabaseID( "Materials[2]",  eiBDBCID_Cons );
	elDBID_Cons_Materials3  = BEMPX_GetDatabaseID( "Materials[3]",  eiBDBCID_Cons );
	elDBID_Cons_Materials4  = BEMPX_GetDatabaseID( "Materials[4]",  eiBDBCID_Cons );
	elDBID_Cons_Materials5  = BEMPX_GetDatabaseID( "Materials[5]",  eiBDBCID_Cons );
	elDBID_Cons_Materials6  = BEMPX_GetDatabaseID( "Materials[6]",  eiBDBCID_Cons );
	elDBID_Cons_Materials7  = BEMPX_GetDatabaseID( "Materials[7]",  eiBDBCID_Cons );
	elDBID_Cons_Materials8  = BEMPX_GetDatabaseID( "Materials[8]",  eiBDBCID_Cons );
	elDBID_Cons_Materials9  = BEMPX_GetDatabaseID( "Materials[9]",  eiBDBCID_Cons );
	elDBID_Cons_Materials10 = BEMPX_GetDatabaseID( "Materials[10]", eiBDBCID_Cons );

	elDBID_PVArrayGeom_IsBldgAttached = BEMPX_GetDatabaseID( "IsBldgAttached", eiBDBCID_PVArrayGeom );     // BEMP_Int   - SAC 2/22/17

	elDBID_Shade_Type         = BEMPX_GetDatabaseID( "Type",       eiBDBCID_Shade );     // BEMP_Sym ->  0:"- select type -"  1:"Site Shade"  2:"Building Shade"   - SAC 2/21/17

	elDBID_PolyLp_Area        = BEMPX_GetDatabaseID( "Area",     eiBDBCID_PolyLp );			// SAC 2/24/17
	elDBID_CartesianPt_Coord  = BEMPX_GetDatabaseID( "Coord",    eiBDBCID_CartesianPt );       // BEMP_Flt,  3,  0,  1, "ft",  "X, Y, Z coordinates of polyloop vertex"   - SAC 2/21/17

	elDBID_HVAC_HeatSystem1     = BEMPX_GetDatabaseID( "HeatSystem[1]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem2     = BEMPX_GetDatabaseID( "HeatSystem[2]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem3     = BEMPX_GetDatabaseID( "HeatSystem[3]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem4     = BEMPX_GetDatabaseID( "HeatSystem[4]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem5     = BEMPX_GetDatabaseID( "HeatSystem[5]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem6     = BEMPX_GetDatabaseID( "HeatSystem[6]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem7     = BEMPX_GetDatabaseID( "HeatSystem[7]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem8     = BEMPX_GetDatabaseID( "HeatSystem[8]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem9     = BEMPX_GetDatabaseID( "HeatSystem[9]",    eiBDBCID_HVACSys );
	elDBID_HVAC_HeatSystem10    = BEMPX_GetDatabaseID( "HeatSystem[10]",   eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem1     = BEMPX_GetDatabaseID( "CoolSystem[1]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem2     = BEMPX_GetDatabaseID( "CoolSystem[2]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem3     = BEMPX_GetDatabaseID( "CoolSystem[3]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem4     = BEMPX_GetDatabaseID( "CoolSystem[4]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem5     = BEMPX_GetDatabaseID( "CoolSystem[5]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem6     = BEMPX_GetDatabaseID( "CoolSystem[6]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem7     = BEMPX_GetDatabaseID( "CoolSystem[7]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem8     = BEMPX_GetDatabaseID( "CoolSystem[8]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem9     = BEMPX_GetDatabaseID( "CoolSystem[9]",    eiBDBCID_HVACSys );
	elDBID_HVAC_CoolSystem10    = BEMPX_GetDatabaseID( "CoolSystem[10]",   eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem1   = BEMPX_GetDatabaseID( "HtPumpSystem[1]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem2   = BEMPX_GetDatabaseID( "HtPumpSystem[2]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem3   = BEMPX_GetDatabaseID( "HtPumpSystem[3]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem4   = BEMPX_GetDatabaseID( "HtPumpSystem[4]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem5   = BEMPX_GetDatabaseID( "HtPumpSystem[5]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem6   = BEMPX_GetDatabaseID( "HtPumpSystem[6]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem7   = BEMPX_GetDatabaseID( "HtPumpSystem[7]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem8   = BEMPX_GetDatabaseID( "HtPumpSystem[8]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem9   = BEMPX_GetDatabaseID( "HtPumpSystem[9]",  eiBDBCID_HVACSys );
	elDBID_HVAC_HtPumpSystem10  = BEMPX_GetDatabaseID( "HtPumpSystem[10]", eiBDBCID_HVACSys );
	elDBID_HVAC_DistribSystem   = BEMPX_GetDatabaseID( "DistribSystem",    eiBDBCID_HVACSys );
	elDBID_HVAC_Fan             = BEMPX_GetDatabaseID( "Fan",              eiBDBCID_HVACSys );

	elDBID_HVACHeat_CHWHeater   = BEMPX_GetDatabaseID( "CHWHeater",        eiBDBCID_HVACHeat );

	elDBID_DHWSys_DHWSolarSysRef = BEMPX_GetDatabaseID( "DHWSolarSysRef", eiBDBCID_DHWSys );	// SAC 1/12/20 (Res tic #1013)
	elDBID_DHWSys_DHWHeater1	= BEMPX_GetDatabaseID( "DHWHeater", eiBDBCID_DHWSys );
	elDBID_DHWSys_DHWHeater2	= elDBID_DHWSys_DHWHeater1 + 1;
	elDBID_DHWSys_DHWHeater3	= elDBID_DHWSys_DHWHeater2 + 1;
	elDBID_DHWSys_DHWHeater4	= elDBID_DHWSys_DHWHeater3 + 1;
	elDBID_DHWSys_DHWHeater5	= elDBID_DHWSys_DHWHeater4 + 1;
	elDBID_DHWSys_DHWHeater6	= elDBID_DHWSys_DHWHeater5 + 1;
	elDBID_DHWSys_LoopHeater	= BEMPX_GetDatabaseID( "LoopHeater", eiBDBCID_DHWSys );
	elDBID_DHWSys_CentralDHWType = BEMPX_GetDatabaseID( "CentralDHWType", eiBDBCID_DHWSys );

	elDBID_INISettings_ProxyServerCredentials      = BEMPX_GetDatabaseID( "ProxyServerCredentials",      eiBDBCID_INISettings  );		// SAC 1/9/17
	elDBID_INISettings_ShowProxyServerCredentials  = BEMPX_GetDatabaseID( "ShowProxyServerCredentials",  eiBDBCID_INISettings  ); 

	eiBDBCID_BatchRuns = BEMPX_GetDBComponentID( "BatchRuns" );
	elDBID_BatchRuns_BatchDefsCSV       = BEMPX_GetDatabaseID( "BatchDefsCSV",       eiBDBCID_BatchRuns );       
	elDBID_BatchRuns_BatchName          = BEMPX_GetDatabaseID( "BatchName",          eiBDBCID_BatchRuns );          
	elDBID_BatchRuns_ProjDirectory      = BEMPX_GetDatabaseID( "ProjDirectory",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_IncludeSubdirs     = BEMPX_GetDatabaseID( "IncludeSubdirs",     eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_ProjFileNames      = BEMPX_GetDatabaseID( "ProjFileNames",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_StoreProjToSepDir  = BEMPX_GetDatabaseID( "StoreProjToSepDir",  eiBDBCID_BatchRuns ); 
	elDBID_BatchRuns_OutputProjDir      = BEMPX_GetDatabaseID( "OutputProjDir",      eiBDBCID_BatchRuns );     
	elDBID_BatchRuns_RunsSpanClimates   = BEMPX_GetDatabaseID( "RunsSpanClimates",   eiBDBCID_BatchRuns );    // SAC 1/4/19 
   elDBID_BatchRuns_RunSetFile         = BEMPX_GetDatabaseID( "RunSetFile",         eiBDBCID_BatchRuns );    // SAC 10/21/20
   elDBID_BatchRuns_RunSetFileStatus   = BEMPX_GetDatabaseID( "RunSetFileStatus",   eiBDBCID_BatchRuns );  
   elDBID_BatchRuns_RunSetDescrip      = BEMPX_GetDatabaseID( "RunSetDescrip",      eiBDBCID_BatchRuns );   

	BEMPUIX_AddPasswordDBIDPair( elDBID_INISettings_ProxyServerCredentials, elDBID_INISettings_ShowProxyServerCredentials, TRUE );	// SAC 1/9/17
#endif   // UI_CARES
}



