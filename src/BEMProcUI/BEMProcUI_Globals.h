// BEMProcUI_Globals.H - 
//
/**********************************************************************
 *  Copyright (c) 2012-2016, California Energy Commission
 *  Copyright (c) 2012-2016, Wrightsoft Corporation
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

#ifndef __BEMPROCUI_GLOBALS_H__
#define __BEMPROCUI_GLOBALS_H__


extern BOOL FileExists( const char* pszFileName );

extern void SetExternals( CWnd* pWnd );


extern int eiTabDlgCtrlDY;
extern int eiTabDlgCtrlMarg;

extern const char* szErrNotEditable;
extern const char* szErrEditsNotAllowed;

extern CString esGraphicsPath;
extern CString esScreensPath;  // SAC 7/15/00
extern CString esRTFFilePath;  // SAC 2/10/01 - Added separate RTF file path


/////////////////////////////////////////////////////////////////////////////
// X,Y Conversion Functions for System Font Size

extern int appCXFullScreen, appCYFullScreen,
           appXScreenBase, appYScreenBase;

extern float appXRatio, appYRatio;

extern int fntHtBase, fntWdBase, fntHtSys, fntWdSys;  
extern int sysFntSize;												// in tenths of a point.
extern int eiFontScalePct;

//#define FontX(x) ( (x*fntWdSys)/fntWdBase )
//#define FontY(y) ( (y*fntHtSys)/fntHtBase )
#define FontX(x)    ( (x*fntWdSys *eiFontScalePct)/(fntWdBase*100) )
#define FontY(y)    ( (y*fntHtSys *eiFontScalePct)/(fntHtBase*100) )


/////////////////////////////////////////////////////////////////////////////
// External Pens

extern CPen windowPen;
extern CPen dialogPen;
extern CPen blackDotPen;
extern CPen blackPen;
extern CPen btnHighlightPen;
extern CPen btnShadowPen;


/////////////////////////////////////////////////////////////////////////////
// External Brushes

extern CBrush buttonBrush;
extern CBrush whiteBrush;
extern CBrush blackBrush;
extern CBrush greyBrush;
extern CBrush darkGreyBrush;
extern CBrush windowBrush;
extern CBrush selZoneBrush;
extern CBrush glassBrush;
extern CBrush unassignedZoneBrush;


/////////////////////////////////////////////////////////////////////////////
// External Fonts

extern CFont menuFont;
extern CFont toolBarFont;
extern CFont vSmallFont;
extern CFont stdFont;
extern CFont boldFont;
extern CFont unitsFont;
extern CFont dataTypeFont;
extern CFont vDataTypeFont;
extern CFont underlineFont;
extern CFont italicFont;
extern CFont italicUndFont;
extern CFont dialogFont;
extern CFont vdStdFont;
extern CFont vdBoldFont;

enum WizFontType
{
   FNT_MENU,
   FNT_TOOLBAR,
   FNT_VSMALL,
   FNT_STD,
   FNT_BOLD,
   FNT_UNITS,
   FNT_DATATYPE,
   FNT_VDATATYPE,
   FNT_UNDERLINE,
   FNT_ITALIC,
   FNT_ITALUNDER,
   FNT_DIALOG,
   FNT_VD_STD,
   FNT_VD_BOLD,
   FNT_NUMFONTS
};

extern CFont* GetWizFont( int fontType );

extern int    GetWizFontHeight( int fontType );


/////////////////////////////////////////////////////////////////////////////
// Routines to facilitate migration to new open source compliance engine libraries

#include "..\BEMProc\BEMProc.h"

extern BOOL BEMPX_SetDataString(  long lDBID, CStringA& sStr, BOOL bAddCommas=TRUE, int iPrecision=0,
                                        int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                        const char* pszDefault=NULL, long lDBID2=0, int iBEMProcIdx=-1 );
 extern BOOL BEMPX_SetDataInteger( long lDBID, long& lData, long lDefault=0,
                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                         int iBEMProcIdx=-1 );
// extern BOOL BEMPX_SetDataFloat(   long lDBID, float& fData, float fDefault=0,
//                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//                                         int iBEMProcIdx=-1 );
// extern int BEMPX_SetDataFloatArray( long lDBID, float* pfData, int iMaxValues, float fDefault=0,
//                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//                                         int iBEMProcIdx=-1 );
// extern BOOL BEMPX_SetDataObject(  long lDBID, BEMObject*& pObj,
//                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//                                         int iBEMProcIdx=-1 );

extern long BEMPX_GetDatabaseID(    const char* psDBCompParam, long iCompID=0, BOOL bTreatParentAsObject=FALSE,
																				int* piRefCompID=NULL, int* piNumRefComps=NULL );

// END OF - Routines to facilitate migration to new open source compliance engine libraries
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Numeric String Comma insertion and removal

//extern void  AddCommaToStringLong(  CString& string, long lNum );
//extern void  AddCommaToStringFloat( CString& string, float fNum, int nRtOfDec );

// SAC 1/7/01 - moved to BEMProc (BEMPX_StringToLong() & BEMPX_StringToFloat())
//extern long  RemoveCommasAndConvertToLong(  CString sLong );
//extern float RemoveCommasAndConvertToFloat( CString sFlt );


/////////////////////////////////////////////////////////////////////////////
// BEMProc-related functions

extern BOOL CtrlDataIsNumber( int iDataType );

extern BOOL IsValidPathCharacter( char c );	// SAC 12/19/14

//extern void SetBEMProcDataString( long lDBID, int iPrecOrLen, CString& sStr, int iDispDataType=-1,
//                              int iOccur=-1, int iObjType=0 );

extern const char* GetDataStatusString(  long lDBID, int iDBInstance=-1, int iDlgMode=0 );  // SAC 8/7/00 - Added iDlgMode argument
extern const char* GetCompDataTypeString( long lDBID, int iDlgMode=0 );  // SAC 8/7/00 - Added iDlgMode argument

extern BOOL ObjectIsFromLibrary( long lDBID, int iDBInstance=-1 );

/////////////////////////////////////////////////////////////////////////////

//extern int eiBEMCID_Wizard;
//extern int eiBEMCID_AreaWiz;
//extern int eiBEMCID_HVACWiz;
//extern int eiBEMCID_PrimWiz;
//extern int eiBEMCID_PostWiz;

//extern long elDBID_Wiz_ScreenIdx;
//extern long elDBID_Wiz_ScreenID;
//extern long elDBID_Wiz_PrevScreenID;
//extern long elDBID_Wiz_NextScreenID;
//extern long elDBID_Wiz_Ruleset;
//extern long	elDBID_Wiz_FootprintWMF;
//extern long	elDBID_Wiz_FPOrientXFrac;
//extern long	elDBID_Wiz_FPOrientYFrac;
//extern long	elDBID_Wiz_Orientation;

/////////////////////////////////////////////////////////////////////////////


void OurDrawLine( CDC* pDC, CPen* pPen, int startX, int startY, int endX, int endY);

void OurDrawArrowHead( CDC* pDC, COLORREF color, int thickness, int baseX, int baseY, float height, float width,
                       float angle);

void OurDrawArrow( CDC* pDC, CPen* pPen, COLORREF color, int thickness, int startX, int startY,
                   int endX, int endY, double xRatio, double yRatio, BOOL bFontScaleHead=FALSE );


/////////////////////////////////////////////////////////////////////////////
// Text Color stuff

COLORREF GetBEMPUITextColor( int iStatus );

/////////////////////////////////////////////////////////////////////////////

extern BOOL  GetCompatabilityData( long lModifiedDBID, long& lCompatErrorDBID, CString& sCompatRulelist );
extern int   GetCompatObjectIndex( long lModDBID, long lCompatDBID, int iDefaultInstance );
extern void  ReportCompatibilityIssue( long lCompatErrorDBID, long lCompatVal, int iCompatObjInstance, CString& sCompatRulelist, CWnd* pWnd );

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMPROCUI_GLOBALS_H__
