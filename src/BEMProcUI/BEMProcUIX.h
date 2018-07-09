// BEMProcUIX.H - 
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
/*  (c) Copyright 1999, SAC Software                                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#ifndef __BEMPROCUIX_H__
#define __BEMPROCUIX_H__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/////////////////////////////////////////////////////////////////////////////
// Exports for managing CSACWizardDlg dialog data

BOOL __declspec(dllexport) __cdecl BEMPUIX_InitBEMProcUI(CWinApp* pApp, HINSTANCE hInst);

BOOL __declspec(dllexport) __cdecl BEMPUIX_ScreenData( CWnd* pParentWnd, const char* psScreenFN, const char* psToolTipFN,
                                                    const char* psGraphicsPN, const char* psScreensPN=NULL,
                                                    const char* psRTFPN=NULL );  // SAC 2/10/01 - Added sepaate RTF path name
BOOL __declspec(dllexport) __cdecl BEMPUIX_ResetScreenData( const char* psScreenFN, const char* psToolTipFN,
                                                         BOOL bReportResults=FALSE );

int  __declspec(dllexport) __cdecl BEMPUIX_GetMainScreenInfo();

int  __declspec(dllexport) __cdecl BEMPUIX_GetNumConsecutiveDialogTabIDs( int iBEMClass, int iUIMode );
int  __declspec(dllexport) __cdecl BEMPUIX_GetFirstDialogTabID( int iBEMClass, int iUIMode );	// SAC 1/5/17

//void __declspec(dllexport) __cdecl BEMPUIX_SetWMFDatabaseIDs( long lDBID_FootprintWMF, long lDBID_FPOrientXFrac,
//                                                           long lDBID_FPOrientYFrac, long lDBID_Orientation );

void __declspec(dllexport) __cdecl BEMPUIX_SetFloorPlanDatabaseIDs( long lDBID_Footprint, long lDBID_X, long lDBID_Y,
                                                                 long lDBID_Orientation );

void __declspec(dllexport) __cdecl BEMPUIX_SetEEMDatabaseIDs( long lDBID_Name, long lDBID_Measure, long lDBID_BaselineEEMName );   // SAC 7/29/02 - added baseline run DBID

void __declspec(dllexport) __cdecl BEMPUIX_SetScreenScalePercent( int iScreenScalePercent );
void __declspec(dllexport) __cdecl BEMPUIX_SetTextColors( COLORREF* craTextColors, int iNumColors=9 );

void __declspec(dllexport) __cdecl BEMPUIX_GetToolTipMessage( CString& sMsg, long lDBID );

void __declspec(dllexport) __cdecl BEMPUIX_SetExtCmbDatabaseIDs( int iNumDBIDPairs, long* laDBID_Combo, long* laDBID_Compatability,
                                                              long* laDBID_CompatError, const char** pszCompatRuleLists );
void __declspec(dllexport) __cdecl BEMPUIX_SetAutoCompleteComboboxDBIDs( int iNumDBIDs, long* laAutoCompleteDBIDs );

BOOL __declspec(dllexport) __cdecl BEMPUIX_SetCharsNotAllowedInObjectNames( char* pcNotAllowedInObjNames );		// SAC 8/20/14 - last char in pcNotAllowedInObjNames array must be 0/NULL

BOOL __declspec(dllexport) __cdecl BEMPUIX_AddPasswordDBIDPair( long lDBID_Password, long lDBID_ShowPassword, BOOL bResetArrays=FALSE );   // SAC 1/9/17

// SAC 7/30/02 - Added in the process of implementing new EEM run mechansim - causes resetting of BEMProc symbol list upon each refresh of combobox
void __declspec(dllexport) __cdecl BEMPUIX_AddAutoSymbolListRefreshDBIDs( long lDBID_Prop, long lDBID_NumItems, long lDBID_Strings,
                                                                       long lDBID_Allow=0, long lDBID_Values=0 );

int  __declspec(dllexport) __cdecl BEMPUIX_GetHelpGroupItemInfo( CDWordArray& dwaHelpItemIDs, CStringArray& saHelpItemStrings, int iHelpGroupIdx );

BOOL __declspec(dllexport) __cdecl BEMPUIX_BEMConditionMissingOrTrue( void* pBEMCondition, int iClass, int iOccur );   // SAC 3/9/18

BOOL __declspec(dllexport) __cdecl BEMPUIX_GetUIControlDataByDBID( long lDBID, int& iWd, int& iHt, long& lVal, QString& sLabel, QString& sToolTip,
																						 void*& pBEMEditableCondition, void*& pBEMDisplayCondition );
BOOL __declspec(dllexport) __cdecl BEMPUIX_GetUIControlDataByIndex( int iCtrlIdx, int& iCtrlType, long& lDBID, int& iWd, int& iHt, long& lVal, QString& sLabel,
																						  QString& sToolTip, void*& pBEMEditableCondition, void*& pBEMDisplayCondition );

BOOL __declspec(dllexport) __cdecl BEMPUIX_GetUIPageData( int iClass, int iClassTabIdx, int iUIMode, BOOL bOnlyIfActiveControls,
																			 QString& qsCaption, int& iPageID, int& iModules, int& iNumControls,
																			 int& iFirstCtrlIdx, int& iLastCtrlIdx );

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// Quick Menu Structure

#define  QMI_DBASETYPE_BEMPROC 0
#define  QMIF_DELETE_ROW       0x1

struct QuickMenuInfo
{
   int   m_iLeft;
   int   m_iTop;
   int   m_iRight;
   UINT  m_uiItemHelpID;
   UINT  m_uiTopicHelpID;
   long  m_lDBID;
   int   m_iDBInstance;
   BOOL  m_bEditable;
   BOOL  m_bObjectAssign;
   int   m_iDBaseType;
// RW ADDED
   CString m_sStatusMessage;
   int   m_iDecPrec;
   DWORD m_dwFlags;
};


/////////////////////////////////////////////////////////////////////////////
// Building Component Creation Info Structure

struct CreateComponentInfo
{
   int   m_i1BEMClass;
   long  m_lAssignmentDBID;
   BOOL  m_bEditNewComponent;
   CWnd* m_pParentWnd;
   long  m_lObjTypeDBID;
   long  m_lObjTypeValue;
};


/////////////////////////////////////////////////////////////////////////////
// Screen Control Type definitions

enum TDCtrlType
{
   TDCT_Edit,
   TDCT_Combo,
   TDCT_Button,
   TDCT_Check,
   TDCT_RadioG,
   TDCT_Radio,
   TDCT_Date,
   TDCT_Time,
   TDCT_WMF,
   TDCT_Floor,
   TDCT_Line,
   TDCT_Label, 
   TDCT_Spread,  // SAC  6/ 5/00
   TDCT_List,    // SAC  6/ 8/00
   TDCT_Rect,    // SAC  6/17/00
   TDCT_ChkLst,  // SAC  7/14/00
   TDCT_RTF,     // SAC  7/15/00
   TDCT_ExtCmb,  // SAC  6/ 4/01
   TDCT_ClrBar,  // SAC  5/ 1/02 - color bar for defining TOU periods by hour of day
   TDCT_HlpBtn,  // SAC 10/18/02 - added to enable small iconic help buttons throughout interface
   TDCT_NumTypes
};


/////////////////////////////////////////////////////////////////////////////
// Dialog Mode Enum

enum SACWizDlgMode
{
   SWDM_Default,
   SWDM_NumModes
};


////////////////////////////////////////////////////////////

#endif // __BEMPROCUIX_H__
