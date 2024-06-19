// BEMProcUI_Globals.cpp : Defines global routines for the DLL.
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
/*  (c) Copyright 1998, SAC Software                                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/


#include "stdafx.h"
#include "..\BEMProc\BEMClass.h"
#include "BEMProcUI_Globals.h"

#include "BEMProcUIX.h"
#include "Screens.h"
#include "memLkRpt.h"


int appCXFullScreen;
int appCYFullScreen;
int appXScreenBase;
int appYScreenBase;

float appXRatio;
float appYRatio;

int eiTabDlgCtrlDY;
int eiTabDlgCtrlMarg;

int fntHtBase, fntWdBase, fntHtSys, fntWdSys;
int sysFntSize;
int eiFontScalePct = 100;

static char BASED_CODE szNotEditable[] = "This data is not user editable.";
const char* szErrNotEditable = szNotEditable;

static char BASED_CODE szEditsNotAllowed[] = "Current user interface mode does not allow data to be modified.";
const char* szErrEditsNotAllowed = szEditsNotAllowed;

CString esGraphicsPath;
CString esScreensPath;  // SAC 7/15/00
CString esRTFFilePath;  // SAC 2/10/01 - Added separate RTF file path


/////////////////////////////////////////////////////////////////////////////
// External Pens

CPen windowPen;
CPen dialogPen;
CPen blackDotPen;
CPen blackPen;
CPen btnHighlightPen;
CPen btnShadowPen;

/////////////////////////////////////////////////////////////////////////////
// External Brushes

CBrush buttonBrush;
CBrush whiteBrush;
CBrush blackBrush;
CBrush greyBrush;
CBrush darkGreyBrush;
CBrush windowBrush;
CBrush selZoneBrush;
CBrush glassBrush;
CBrush unassignedZoneBrush;

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
CFont dialogFont;
CFont vdStdFont;
CFont vdBoldFont;

static char BASED_CODE arial[]   = "Arial";
static char BASED_CODE arialB[]  = "Arial Bold";
static char BASED_CODE arialI[]  = "Arial Italic";
//static char BASED_CODE arialBI[] = "Arial Bold Italic";
//static char BASED_CODE timesB[]  = "Times New Roman Bold";
static char BASED_CODE fntVerdana[]  = "Verdana";

/////////////////////////////////////////////////////////////////////////////
// Static Font Sizes

static int stdFontHt;
static int boldFontHt;
static int menuFontHt;
static int toolBarFontHt;
static int vSmallFontHt;
static int unitsFontHt;
static int dataTypeFontHt;
static int dialogFontHt;
static int vdStdFontHt;

//static void InitBEMCIDs();

void SetExternals( CWnd* pWnd )
{
   appXScreenBase = 800;
   appYScreenBase = 600;

   appCXFullScreen = GetSystemMetrics(SM_CXFULLSCREEN);
   appCYFullScreen = GetSystemMetrics(SM_CYFULLSCREEN) - GetSystemMetrics(SM_CYMENU);

   appXRatio = ((float) appCXFullScreen)/((float) appXScreenBase);
   appYRatio = ((float) appCYFullScreen)/((float) appYScreenBase);

   fntHtBase = 16;
   fntWdBase =  7;

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

//   InitBEMCIDs();

   //////////////////////////////////////////////////////////////////////////
   // External Fonts

   stdFontHt        = (16*fntHtSys)/fntHtBase;
   boldFontHt       = (16*fntHtSys)/fntHtBase;
//   menuFontHt       = int (36.0*appYRatio);
   menuFontHt       = (36*fntHtSys)/fntHtBase;
   toolBarFontHt    = int (toolBtnHt*0.78);
   vSmallFontHt     = (15*fntHtSys)/fntHtBase;
   unitsFontHt      = (13*fntHtSys)/fntHtBase;
   dataTypeFontHt   = (12*fntHtSys)/fntHtBase;
   vdStdFontHt      = (13*fntHtSys)/fntHtBase;

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

// SAC 11/29/99 - New Verdana and system dialog fonts added
   vdStdFont.CreateFont(  vdStdFontHt,                 // height
                          0, 0, 0,                   // width, escapement, orientation
                          FW_THIN, 0, 0, 0,          // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_TT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          VARIABLE_PITCH | 0x04 | FF_SWISS,                  // pitch & family
                          fntVerdana );              // font name
   vdBoldFont.CreateFont( vdStdFontHt,                 // height
                          0, 0, 0,                   // width, escapement, orientation
                          FW_BOLD, 0, 0, 0,          // weight, ital, undrln, strike
                          ANSI_CHARSET,              // char set
                          OUT_TT_PRECIS,        // out precision
                          CLIP_DEFAULT_PRECIS,       // clip precision
                          PROOF_QUALITY,             // quality
                          VARIABLE_PITCH | 0x04 | FF_SWISS,                  // pitch & family
                          fntVerdana );              // font name

   // Get the system window message (dialog) font
   NONCLIENTMETRICS ncm;
   ncm.cbSize = sizeof(NONCLIENTMETRICS);
   VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
   dialogFont.CreateFontIndirect(&(ncm.lfMessageFont)); 
   dialogFontHt = ncm.lfMessageFont.lfHeight;


   //////////////////////////////////////////////////////////////////////////
   // External Pens

   windowPen.CreatePen(       PS_SOLID, 1, ::GetSysColor( COLOR_WINDOW ) );
   dialogPen.CreatePen(       PS_SOLID, 1, ::GetSysColor( COLOR_BTNFACE ) );
   blackDotPen.CreatePen(     PS_DOT  , 1, RGB(0,0,0) );
   blackPen.CreatePen(        PS_SOLID, 1, RGB(0,0,0) );
   btnHighlightPen.CreatePen( PS_SOLID, 1, ::GetSysColor( COLOR_BTNHIGHLIGHT ) ); // RGB(255,255,255) );
   btnShadowPen.CreatePen(    PS_SOLID, 1, ::GetSysColor( COLOR_BTNSHADOW    ) ); // RGB(128,128,128) );

   //////////////////////////////////////////////////////////////////////////
   // External Brushes

   buttonBrush.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
   whiteBrush.CreateSolidBrush(          RGB(255,255,255) );
   blackBrush.CreateSolidBrush(          RGB(  0,  0,  0) );
   greyBrush.CreateSolidBrush(           RGB(192,192,192) );
   darkGreyBrush.CreateSolidBrush(       RGB(128,128,128) );
   windowBrush.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
   selZoneBrush.CreateSolidBrush(        RGB(  0,128,128) );
   glassBrush.CreateSolidBrush(          RGB(  0,255,255) );
   unassignedZoneBrush.CreateSolidBrush( RGB(255,128,128) );

   // initialize text colors to all black
   BEMPUIX_SetTextColors( NULL, 0 );
}


/////////////////////////////////////////////////////////////////////////////
// Check for file existence

BOOL FileExists( const char* pszFileName )
{
   BOOL retVal = FALSE;
   FILE *pfTempFile;
	int iErrorCode = fopen_s( &pfTempFile, pszFileName, "r" );
   if (pfTempFile != NULL)
   {
      fclose( pfTempFile );
      retVal = (iErrorCode==0);
   }
   return retVal;
}


/////////////////////////////////////////////////////////////////////////////
// Font Related Functions

CFont* GetWizFont( int fontType )
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
   else if (fontType == FNT_DIALOG)
      fontPtr = &dialogFont;
   else if (fontType == FNT_VD_STD)
      fontPtr = &vdStdFont;
   else if (fontType == FNT_VD_BOLD)
      fontPtr = &vdBoldFont;

   return fontPtr;
}

int GetWizFontHeight( int fontType )
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
   else if (fontType == FNT_DIALOG)
      retVal = dialogFontHt;
   else if (fontType == FNT_VD_STD || fontType == FNT_VD_BOLD)
      retVal = vdStdFontHt;

   return retVal;
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
// BEMProc-related functions

BOOL CtrlDataIsNumber( int iDataType )
{
   return ((iDataType == BEMP_Int) || (iDataType == BEMP_Flt));
}

BOOL IsValidPathCharacter( char c )	// SAC 12/19/14
{	return ( c != '*' && c != '?' && c != '"' && 
				c != '<' && c != '>' && c != '|' );
}


// Compliance Data Type Strings
static int iNumCompDataTypeStrings = 8;
static char BASED_CODE szCDTCompuls[]   = "Compulsory";
static char BASED_CODE szCDTRequire[]   = "Required";
static char BASED_CODE szCDTCondReq[]   = "Cond. Required";
static char BASED_CODE szCDTOptiona[]   = "Optional";
static char BASED_CODE szCDTDefault[]   = "Default";
static char BASED_CODE szCDTCritica[]   = "Crit. Default";
static char BASED_CODE szCDTPrescri[]   = "Prescribed";
static char BASED_CODE szCDTNotInpu[]   = "Not Input";
static const char* pszCDT[] = {  szCDTCompuls, szCDTRequire, szCDTCondReq, szCDTOptiona,
                                 szCDTDefault, szCDTCritica, szCDTPrescri, szCDTNotInpu };
static char BASED_CODE szCDTNav[] = "Navigation";
// SAC 8/7/00 - Added separate set of data type labels to handle new BEM strings
static char BASED_CODE szBEMCDTCompuls[]   = "Input is compulsory";
static char BASED_CODE szBEMCDTRequire[]   = "Input is required";
static char BASED_CODE szBEMCDTCondReq[]   = "Input is cond. reqrd.";
static char BASED_CODE szBEMCDTOptiona[]   = "Input is optional";
static char BASED_CODE szBEMCDTDefault[]   = "Input is optional";
static char BASED_CODE szBEMCDTCritica[]   = "Input is crit. default";
static char BASED_CODE szBEMCDTPrescri[]   = "Field not editable";
static char BASED_CODE szBEMCDTNotInpu[]   = "Field not editable";
static const char* pszBEMCDT[] = {  szBEMCDTCompuls, szBEMCDTRequire, szBEMCDTCondReq, szBEMCDTOptiona,
                                    szBEMCDTDefault, szBEMCDTCritica, szBEMCDTPrescri, szBEMCDTNotInpu };
static char BASED_CODE szBEMCDTNav[]  = "Navigation input";
static char BASED_CODE szBEMCDTNone[] = "No field selected";

const char* GetCompDataTypeString( long lDBID, int iDlgMode /*=0*/ )
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
            return (iDlgMode==0 ? szBEMCDTRequire : szCDTRequire);
         else if (iArr == 1)
            return (iDlgMode==0 ? szBEMCDTNav : szCDTNav);
      }
   }
   else
      return ((iCDT < 0) || (iCDT >= iNumCompDataTypeStrings)) ?
                   (iDlgMode==0 ? szBEMCDTNone : NULL) :
                   (iDlgMode==0 ? pszBEMCDT[ iCDT ] : pszCDT[ iCDT ]);

   return (iDlgMode==0 ? szBEMCDTNone : NULL);
}


// Data Status Strings
static int iNumDataStatusStrings = 9;
static char BASED_CODE szDSUndefined[] = "Undefined";
static char BASED_CODE szDSProgDefau[] = "Prog. Default";
static char BASED_CODE szDSRuleDefau[] = "Rule Default";
static char BASED_CODE szDSRuleLibra[] = "Rule Library";
static char BASED_CODE szDSRuleDefin[] = "Rule Defined";
static char BASED_CODE szDSUserDefau[] = "User Default";
static char BASED_CODE szDSUserLibra[] = "User Library";
static char BASED_CODE szDSUserDefin[] = "User Defined";
static char BASED_CODE szDSSimResult[] = "Sim Result";
static const char* pszDS[] = {  szDSUndefined, szDSProgDefau, szDSRuleDefau,
                                szDSRuleLibra, szDSRuleDefin, szDSUserDefau,
                                szDSUserLibra, szDSUserDefin, szDSSimResult };
// SAC 8/7/00 - Added separate set of data status labels to handle new BEM strings
static char BASED_CODE szBEMDSUndefined[] = "Value undefined";
static char BASED_CODE szBEMDSProgDefau[] = "Value from program";
static char BASED_CODE szBEMDSRuleDefau[] = "Value from program";
static char BASED_CODE szBEMDSRuleLibra[] = "Value from program";
static char BASED_CODE szBEMDSRuleDefin[] = "Value from program";
static char BASED_CODE szBEMDSUserDefau[] = "Value from user";
static char BASED_CODE szBEMDSUserLibra[] = "Value from user";
static char BASED_CODE szBEMDSUserDefin[] = "Value from user";
static char BASED_CODE szBEMDSSimResult[] = "Value from simulation";
static const char* pszBEMDS[] = {  szBEMDSUndefined, szBEMDSProgDefau, szBEMDSRuleDefau,
                                   szBEMDSRuleLibra, szBEMDSRuleDefin, szBEMDSUserDefau,
                                   szBEMDSUserLibra, szBEMDSUserDefin, szBEMDSSimResult };

const char* GetDataStatusString(  long lDBID, int iDBInstance, int iDlgMode /*=0*/ )
{
   int iDS = BEMPX_GetDataStatus( lDBID, iDBInstance );

   if ( (iDS < 0) || (iDS >= iNumDataStatusStrings) )
      iDS = 0;

   return (iDlgMode==0 ? pszBEMDS[ iDS ] : pszDS[ iDS ]);
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
BOOL ObjectIsFromLibrary( long lDBID, int iDBInstance )
{
   BOOL bRetVal = TRUE;

   if (lDBID == 0)  // allow edit of data w/ 0 DBID (during creation...)
      bRetVal = FALSE;
   else
   {
      int iError;
      BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError, iDBInstance );
      if ( iError < 0 || pObj == NULL )
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


/////////////////////////////////////////////////////////////////////////////
// Global BEM Class Index stuff

//int eiBEMCID_Wizard = 0;
//int eiBEMCID_AreaWiz = 0;
//int eiBEMCID_HVACWiz = 0;
//int eiBEMCID_PrimWiz = 0;
//int eiBEMCID_PostWiz = 0;

//long elDBID_Wiz_ScreenIdx = 0;
//long elDBID_Wiz_ScreenID = 0;
//long elDBID_Wiz_PrevScreenID = 0;
//long elDBID_Wiz_NextScreenID = 0;
//long elDBID_Wiz_Ruleset = 0;
//long elDBID_Wiz_FootprintWMF = 0;
//long elDBID_Wiz_FPOrientXFrac = 0;
//long elDBID_Wiz_FPOrientYFrac = 0;
//long elDBID_Wiz_Orientation = 0;

//void InitBEMCIDs()
//{
//   eiBEMCID_Wizard  = BEMPX_GetDBComponentID( "Wizard" );
//   eiBEMCID_AreaWiz = BEMPX_GetDBComponentID( "AreaWiz" );
//   eiBEMCID_HVACWiz = BEMPX_GetDBComponentID( "HVACWiz" );
//   eiBEMCID_PrimWiz = BEMPX_GetDBComponentID( "PrimWiz" );
//   eiBEMCID_PostWiz = BEMPX_GetDBComponentID( "PostWiz" );
//
//   elDBID_Wiz_ScreenIdx     = BEMPX_GetDatabaseID( "ScreenIdx",      eiBEMCID_Wizard );
//   elDBID_Wiz_ScreenID      = BEMPX_GetDatabaseID( "ScreenID",       eiBEMCID_Wizard );
//   elDBID_Wiz_PrevScreenID  = BEMPX_GetDatabaseID( "PrevScreenID",   eiBEMCID_Wizard );
//   elDBID_Wiz_NextScreenID  = BEMPX_GetDatabaseID( "NextScreenID",   eiBEMCID_Wizard );
//   elDBID_Wiz_Ruleset       = BEMPX_GetDatabaseID( "Ruleset",        eiBEMCID_Wizard );
//   elDBID_Wiz_FootprintWMF  = BEMPX_GetDatabaseID( "FootprintWMF",   eiBEMCID_Wizard );
//   elDBID_Wiz_FPOrientXFrac = BEMPX_GetDatabaseID( "FPOrientXFrac",  eiBEMCID_Wizard );
//   elDBID_Wiz_FPOrientYFrac = BEMPX_GetDatabaseID( "FPOrientYFrac",  eiBEMCID_Wizard );
//   elDBID_Wiz_Orientation   = BEMPX_GetDatabaseID( "Orientation",    eiBEMCID_Wizard );
//}


#define THIN  1
#define THICK 2

void OurDrawLine( CDC* pDC, CPen* pPen, int startX, int startY, int endX, int endY)
{
   pDC->SelectObject( pPen );
   pDC->MoveTo( startX, startY );
   pDC->LineTo(   endX,   endY );
}

void OurDrawArrowHead( CDC* pDC, COLORREF color, int /*thickness*/, int baseX, int baseY, float height, float width,
                              float angle)
{
   int temppDC = pDC->SaveDC();

   CPoint polyPoints[4] = {
         CPoint( (baseX + (int (width * (float)cos(degtorad(angle+90))))),
                 (baseY - (int (width * (float)sin(degtorad(angle+90))))) ),
         CPoint( (baseX + (int (height* (float)cos(degtorad(angle   ))))),
                 (baseY - (int (height* (float)sin(degtorad(angle   ))))) ),
         CPoint( (baseX + (int (width * (float)cos(degtorad(angle-90))))),
                 (baseY - (int (width * (float)sin(degtorad(angle-90))))) ),
         CPoint( (baseX + (int (width * (float)cos(degtorad(angle+90))))),
                 (baseY - (int (width * (float)sin(degtorad(angle+90))))) ) };
   CPen pArrow;
   CBrush pBrush;
   pArrow.CreatePen( PS_SOLID, 1, color );
   pDC->SelectObject( &pArrow );
   pBrush.CreateSolidBrush(color);
   pDC->SelectObject(&pBrush);
   pDC->Polygon( polyPoints, 4 );

   pDC->SelectObject( &blackPen );
   pDC->SelectObject( &whiteBrush );

   pDC->RestoreDC( temppDC );
}

void OurDrawArrow( CDC* pDC, CPen* pPen, COLORREF color, int thickness, int startX, int startY,
                   int endX, int endY, double xRatio, double yRatio, BOOL bFontScaleHead )
{
   if (thickness == THIN || thickness == THICK)
   {
      float angle;
      int height;
      int width;
      if (thickness == THIN)
      {
         height = (int)(5.0 * xRatio);
         width  = (int)(3.5 * yRatio);
      }
      else
      {
         height = (int)(8.5 * xRatio);
         width  = (int)(5.0 * yRatio);
      }

      if (bFontScaleHead)
      {
         height = FontY( height );
         width  = FontY( width );
      }
      
      if (startX != endX)
      {
         angle = (float) radtodeg( atan( (double (startY-endY))/(double (endX-startX)) ) );
         if (startX > endX)
            angle = angle + 180;
      }
      else if (endY >= startY)
      {
         angle = 270.0;
         endY  = endY + 2;
      }
      else
      {
         angle =  90.0;
         endY = endY - 2 ;
      }

      int x1 = endX - (int (height * cos(degtorad(angle))));
      int y1 = endY + (int (height * sin(degtorad(angle))));
      OurDrawLine( pDC, pPen, startX, startY, x1, y1 );
      OurDrawArrowHead( pDC, color, thickness, x1, y1, (float) height, (float) width, angle );
   }
   else
      OurDrawLine( pDC, pPen, startX, startY, endX, endY );
}


/////////////////////////////////////////////////////////////////////////////

void WriteLineToDC( CDC* pDC, BOOL bColor, int fromX, int fromY, int toX, int toY, int iThickness )
{
   if (iThickness == -1)
   {  // => Shadow Line
      pDC->SelectObject( (bColor ? &btnShadowPen : &dialogPen) );
      pDC->MoveTo( fromX, fromY );
      pDC->LineTo( toX  , toY   );

      pDC->SelectObject( (bColor ? &btnHighlightPen : &dialogPen) );
      if (fromX != toX)
      {
         pDC->MoveTo( fromX, fromY+1 );
         pDC->LineTo( toX  , toY  +1 );
      }
      else
      {
         pDC->MoveTo( fromX+1, fromY );
         pDC->LineTo( toX  +1, toY   );
      }
   }
   else
   {  // => Standard Line
      CPen pen;
// SAC 5/1/02 - Added code to facilitate single thickness dark gray lines
      COLORREF lineColor;
      if (iThickness == -2)
      {
         lineColor = (bColor ? ::GetSysColor( COLOR_BTNSHADOW ) : ::GetSysColor( COLOR_BTNFACE ));
         iThickness = 1;
      }
      else
         lineColor = (bColor ? RGB(0,0,0) : ::GetSysColor( COLOR_BTNFACE ));

      pen.CreatePen( PS_SOLID, iThickness, lineColor );
      pDC->SelectObject( &pen );

      pDC->MoveTo( fromX, fromY );
      pDC->LineTo( toX  , toY   );
      pDC->SelectObject( &blackPen );
   }
}

void WriteLineCtrlToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset )
{
   // Line w/ units DX = -1 => Don't Erase via writing w/ gray line - same logic as w/ labels - SAC 11/28/22
   if (pCtrl->m_iUnitDX != -1 || pCtrl->CanDisplay())
      WriteLineToDC( pDC, pCtrl->CanDisplay(), FontX( pCtrl->m_iX ), FontY( pCtrl->m_iY ) + iYOffset,
                     FontX( pCtrl->m_iHeight), FontY( pCtrl->m_iWidth ) + iYOffset, pCtrl->m_lValue );
}

void WriteLabelToDC( CDC* pDC, CBEMPUIControl* pCtrl, long lCtrlDBIDOffset, int iYOffset )
{
   // Label w/ units DX = -1 => Don't Erase via writing w/ gray text
   if (pCtrl->m_iUnitDX != -1 || pCtrl->CanDisplay())
   {
      CString sLabel = pCtrl->m_sLbl;

      if (pCtrl->m_lDBID > 0)
      {
         CString sData;
         BEMPX_SetDataString( pCtrl->m_lDBID + lCtrlDBIDOffset, sData, (pCtrl->m_lValue >= 0),
                            (int) pCtrl->m_lValue, -1, pCtrl->m_iDBInstance, BEMO_User, NULL, pCtrl->m_lDBID2 );
         sLabel += sData;
      }
// RW 11/4/02 Not sure ifwe want to insert the new tooltip rulelist-generate message here or not.
      sLabel += pCtrl->m_sStatusMsg;

      pDC->SetBkMode( TRANSPARENT );
      pDC->SelectObject( GetWizFont(pCtrl->m_iFont) );
//      pDC->SetTextAlign( pCtrl->m_uiLblJust );     - SAC 1/3/12 - now done in WriteOpaqueTextToDC()

      COLORREF crPrevTextColor = 0;
      if (!pCtrl->CanDisplay())
         crPrevTextColor = pDC->SetTextColor( ::GetSysColor( COLOR_BTNFACE ) );
// SAC 2/8/05 - added code to use non-editable condition to result in label being written in "gray" text
      else if (!pCtrl->IsEditable())
         crPrevTextColor = pDC->SetTextColor( ::GetSysColor( COLOR_GRAYTEXT ) );

      // Trim label to fit into the available m_iWidth (iff m_iWidth > 0)
      // (also add trailing '...' if any characters are trimmed)
      if (pCtrl->m_iWidth > 0)
      {
         int iWidth = FontX(pCtrl->m_iWidth);
         CSize size = pDC->GetTextExtent( sLabel );
         if (size.cx > iWidth)
         {
            CString sTrail = "...";
            CString sTemp = sLabel;
            if (pCtrl->m_uiLblJust == TA_RIGHT)  // SAC 7/7/09 - added code to trim characters off the LEFT portion of string for labels that are RIGHT justified
               sLabel  = sTrail + sLabel;
            else
               sLabel += sTrail;
            while (size.cx > iWidth)
            {
               if (sTemp.GetLength() > 1)
               {
                  if (pCtrl->m_uiLblJust == TA_RIGHT)  // SAC 7/7/09 - added code to trim characters off the LEFT portion of string for labels that are RIGHT justified
                  {
                     sTemp  = sTemp.Right( sTemp.GetLength()-1 );
                     sLabel = sTrail + sTemp;
                  }
                  else
                  {
                     sTemp  = sTemp.Left( sTemp.GetLength()-1 );
                     sLabel = sTemp + sTrail;
                  }
                  size = pDC->GetTextExtent( sLabel );
               }
               else
                  break;
            }
         }
      }

      if ( sLabel.GetLength() > 0)
         //pDC->TextOut( FontX(pCtrl->m_iX), FontY(pCtrl->m_iY) + iYOffset, sLabel );
		   // SAC 1/3/12 - replaced above w/ following to write text labels as opaque blocks
			WriteOpaqueTextToDC( pDC, FontX(pCtrl->m_iX), FontY(pCtrl->m_iY) + iYOffset, pCtrl->m_uiLblJust, sLabel );

      // If Unit DX > 0 then draw a horizontal shadow line from the end of the text to the UnitDX position
      if (pCtrl->m_iUnitDX > 0 && pCtrl->m_uiLblJust == TA_LEFT)
      {
         CSize size = pDC->GetTextExtent( sLabel );
         int iLeftX = FontX(pCtrl->m_iX) + size.cx + FontX(6);
         int iRightX = FontX(pCtrl->m_iUnitDX);
         int iMidY = FontY(pCtrl->m_iY) + iYOffset + (GetWizFontHeight(pCtrl->m_iFont) / 2);
         if (iRightX > iLeftX)
            WriteLineToDC( pDC, pCtrl->CanDisplay(), iLeftX, iMidY, iRightX, iMidY, -1 );
      }

      // reset text color to original setting
      if (!pCtrl->CanDisplay() || !pCtrl->IsEditable())  // SAC 2/8/05
         pDC->SetTextColor( crPrevTextColor );
   }
}

// SAC 1/3/12 - added new routine to facilitate writing of opaque (blocked-out) string labels (to avoid fuzziness caused by labels overwriting themselves)
void WriteOpaqueTextToDC( CDC* pDC, int iX, int iY, UINT uiJustify, CString& sLabel )
{	CSize size = pDC->GetTextExtent( sLabel );
	CRect rc;
	rc.top    = std::max( 0, iY - 1 );
	rc.bottom = iY + size.cy + 1;
	switch (uiJustify)
	{	case TA_RIGHT  :	rc.left   = std::max( 0, iX - ((int)size.cx) - 1 );
								rc.right  = iX + 1;																	break; 
		case TA_CENTER :	rc.left   = std::max( 0, iX - ((int) ((double) size.cx / 2.0)) - 1 );
								rc.right  = iX + ((int) ((double) size.cx / 2.0)) + 2; 					break;
		default        :	rc.left   = std::max( 0, iX - 1 );
								rc.right  = iX + size.cx + 2; 													break;
	}
			ASSERT( (rc.right - rc.left) > 5 );  // check to confirm that we have a reasonable width area to erase
	pDC->SetTextAlign( uiJustify );
	pDC->ExtTextOut( iX, iY, ETO_OPAQUE, rc, sLabel, sLabel.GetLength(), NULL );
}

// SAC 6/21/00 - added
void WriteRectToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset )
{
   ASSERT( pDC );
   ASSERT( pCtrl );
   if (pCtrl->CanDisplay())
   {
      int left    = FontX( pCtrl->m_iX );
      int top     = FontY( pCtrl->m_iY ) + iYOffset;
      int right   = left + FontX( pCtrl->m_iWidth  );
      int bottom  = top  + FontY( pCtrl->m_iHeight ) + iYOffset;
//      int roundWd = pRect->m_iRoundWd;
//      int roundHt = pRect->m_iRoundHt;
//      int thick   = pRect->m_iBoundThick;
      BOOL bShadowOutline = (pCtrl->m_iBoundThickness == -1);

      CRgn tempRgn;
//      if ( (pRect->m_iRoundWd < 1) && (pRect->m_iRoundHt < 1) )
         tempRgn.CreateRectRgn( left, top, right, bottom );
//      else
//         tempRgn.CreateRoundRectRgn( left, top, right, bottom, roundWd, roundHt );

      CBrush brushF;
      BOOL bFill = TRUE;
// SAC 5/1/02 - Added code to enable BEMProc-defined colors
      long lFillR = pCtrl->m_iFillRed;
      long lFillG = pCtrl->m_iFillGreen;
      long lFillB = pCtrl->m_iFillBlue;
      if (pCtrl->m_lDBID > 0)
      {
         VERIFY( BEMPX_SetDataInteger( pCtrl->m_lDBID,   lFillR ) );
         VERIFY( BEMPX_SetDataInteger( pCtrl->m_lDBID+1, lFillG ) );
         VERIFY( BEMPX_SetDataInteger( pCtrl->m_lDBID+2, lFillB ) );
      }

      CPen* pPrevPen = NULL;  // SAC 6/25/04
      int iLastBkMode = -1;
      COLORREF clrSaveBkClr = ::GetSysColor( COLOR_BTNFACE );
      if ( (lFillR >= 0) && (lFillG >= 0) && (lFillB >= 0) )
         brushF.CreateSolidBrush( RGB( lFillR, lFillG, lFillB) );
      else if ( (lFillR == -2) && (lFillG == -2) && (lFillB == -2) )
         brushF.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
      else if ( (lFillR == -3) && (lFillG == -3) && (lFillB == -3) )  // SAC 6/25/04 - Added code to write cross-hatched rectangle
      {
         brushF.CreateHatchBrush( HS_DIAGCROSS, RGB(64,64,64) );  // RGB(0,0,0) );
         clrSaveBkClr = pDC->SetBkColor( ::GetSysColor( COLOR_WINDOW ) );  // RGB(255,255,255) );
         iLastBkMode  = pDC->SetBkMode( OPAQUE );
      }
      else if ( (lFillR == -4) && (lFillG == -4) && (lFillB == -4) )  // SAC 6/25/04 - Added code to write window colored rectangle w/ Red box
         brushF.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
      else
         bFill = FALSE;
      if (bFill)
         pDC->FillRgn( &tempRgn, &brushF );

      if ( (lFillR == -3) && (lFillG == -3) && (lFillB == -3) )  // SAC 6/25/04
         pDC->SetBkColor( clrSaveBkClr );
//      else if ( (lFillR == -4) && (lFillG == -4) && (lFillB == -4) )  // SAC 6/25/04 - Added code to write window colored rectangle w/ Red box
//      {
//         pPrevPen = pDC->SelectObject( &penThickRed );
//         pDC->SelectObject( &windowBrush );
//         pDC->Rectangle( left + FontY(5), top + FontY(5), right - FontY(4), bottom - FontY(4) );
//      }

      if (pPrevPen)  // SAC 6/25/04
         pDC->SelectObject( pPrevPen );
      if (iLastBkMode != -1)
         pDC->SetBkMode( iLastBkMode );

      if (bShadowOutline)
      {
         pDC->DrawEdge( CRect( left, top, right, bottom ), EDGE_SUNKEN, BF_RECT );
//         pDC->Draw3dRect( int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight );
      }
      else if (pCtrl->m_iBoundThickness > 0)
      {
         int thick = FontY( pCtrl->m_iBoundThickness );
         CBrush brushB;
         BOOL bBound = TRUE;
         if( pDC->IsPrinting() )
            brushB.CreateSolidBrush( RGB(0,0,0) );
         else if ( (pCtrl->m_iBoundRed >= 0) && (pCtrl->m_iBoundGreen >= 0) && (pCtrl->m_iBoundBlue >= 0) )
            brushB.CreateSolidBrush( RGB( pCtrl->m_iBoundRed, pCtrl->m_iBoundGreen, pCtrl->m_iBoundBlue) );
         else if ( (pCtrl->m_iBoundRed >= -2) && (pCtrl->m_iBoundGreen >= -2) && (pCtrl->m_iBoundBlue >= -2) )
            brushB.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
         else
            bBound = FALSE;

         if (bBound)
            pDC->FrameRgn( &tempRgn, &brushB, thick, thick );
      }

// SAC 5/1/02 - Added code to draw a dashed line around rectangle to denote active state
      if (pCtrl->m_lDBID > 0)
      {
         long lActiveDBID = pCtrl->m_lDBID - (pCtrl->m_lDBID % BEM_PARAM_MULT) + 1;
         long lActiveValue;
         VERIFY( BEMPX_SetDataInteger( lActiveDBID, lActiveValue ) );

         if (bShadowOutline && lActiveValue == pCtrl->m_lValue)
            pDC->DrawEdge( CRect( left-3, top-3, right+3, bottom+3 ), EDGE_ETCHED, BF_RECT );
         else
         {
            CPen pen;
            pen.CreatePen( PS_SOLID, 1, (lActiveValue == pCtrl->m_lValue ? RGB(0,0,0) : ::GetSysColor( COLOR_BTNFACE )) );
            pDC->SelectObject( &pen );
            pDC->MoveTo( left-3  , top-3    );
            pDC->LineTo( left-3  , bottom+2 );
            pDC->LineTo( right+2 , bottom+2 );
            pDC->LineTo( right+2 , top-3    );
            pDC->LineTo( left-3  , top-3    );

            if (bShadowOutline && lActiveValue != pCtrl->m_lValue)
            {  // make sure BOTH lines of a previous shadow outline are erased
               pDC->MoveTo( left-2  , top-2    );
               pDC->LineTo( left-2  , bottom+1 );
               pDC->LineTo( right+1 , bottom+1 );
               pDC->LineTo( right+1 , top-2    );
               pDC->LineTo( left-2  , top-2    );
            }

            pDC->SelectObject( &blackPen );
         }
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
// Text Color stuff

static COLORREF iaTextRGB[ BEMS_NumTypes ];

void BEMPUIX_SetTextColors( COLORREF* craTextColors, int iNumColors )
{
   if (iNumColors > BEMS_NumTypes)
      iNumColors = BEMS_NumTypes;

   int i=0;
   for (; i<iNumColors; i++)
      iaTextRGB[i] = craTextColors[i];
   for (i=iNumColors; i<BEMS_NumTypes; i++)
      iaTextRGB[i] = RGB(0,0,0);
}


COLORREF GetBEMPUITextColor( int iStatus )
{
   if (iStatus >= 0 && iStatus < BEMS_NumTypes)
      return iaTextRGB[iStatus];
   return RGB(0,0,0);
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
// extern int BEMPX_SetDataFloatArray( long lDBID, float* pfData, int iMaxValues, float fDefault /*=0*/,
//                                         int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
//                                         int iBEMProcIdx /*=-1*/ )
		// int     BEMPROC_API __cdecl BEMPX_GetFloatArray( long lDBID, double* pdData, int iMaxValues, double dDefault=0,
		// 																	int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User, int iBEMProcIdx=-1 );
// extern BOOL BEMPX_SetDataObject(  long lDBID, BEMObject*& pObj,
//                                         int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
//                                         int iBEMProcIdx /*=-1*/ )
		// BOOL    BEMPROC_API __cdecl BEMPX_GetObject(  long lDBID, BEMObject*& pObj, int iDispDataType=-1, int iOccur=-1,		// for backward compatibility with BEMPX_SetDataObject
		// 																	int iObjType=BEMO_User, int iBEMProcIdx=-1 );


long BEMPX_GetDatabaseID(    const char* psDBCompParam, long iCompID /*=0*/, BOOL bTreatParentAsObject /*=FALSE*/,
									int* piRefCompID /*=NULL*/, int* piNumRefComps /*=NULL*/ )
{	QString qStr = psDBCompParam;
	return BEMPX_GetDatabaseID( qStr, iCompID, bTreatParentAsObject, piRefCompID, piNumRefComps );
}

// END OF - Routines to facilitate migration to new open source compliance engine libraries
/////////////////////////////////////////////////////////////////////////////

