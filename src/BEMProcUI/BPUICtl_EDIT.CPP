// BPUICtl_EDIT.CPP  :  Contains CEditCtl routines
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
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\expRanges.h"
#include "Screens.h"
#include "BPUICtl_Edit.h" 
#include "BEMProcUIX.h"
#include "memLkRpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

static char BASED_CODE szNoEntries[] = "---";

static char BASED_CODE szErrorCaption[] = "Edit Control Error";

static long slProjNameDBID = 0;

/////////////////////////////////////////////////////////////////////////////

#define  MAX_NUMCHARSNotAllowedInObjNames  40
static char spcNotAllowedInObjNames[ MAX_NUMCHARSNotAllowedInObjNames ];
static int siNumCharsNotAllowedInObjNames = 0;

BOOL BEMPUIX_SetCharsNotAllowedInObjectNames( char* pcNotAllowedInObjNames )		// SAC 8/20/14
{	siNumCharsNotAllowedInObjNames = 0;
	int idx=-1;
	if (pcNotAllowedInObjNames)
	{	while (pcNotAllowedInObjNames[++idx] != NULL)
		{	if (idx < MAX_NUMCHARSNotAllowedInObjNames)
			{	siNumCharsNotAllowedInObjNames++;
				spcNotAllowedInObjNames[idx] = pcNotAllowedInObjNames[idx];
		}	}
		ASSERT( idx <= MAX_NUMCHARSNotAllowedInObjNames );		// must increase limit to support more chars in this array
	}
	return (siNumCharsNotAllowedInObjNames > 0 && idx <= MAX_NUMCHARSNotAllowedInObjNames);
}

static BOOL EditCtlCharacterNotAllowedInObjectname( char c )
{	if (siNumCharsNotAllowedInObjNames < 1)
		return (c == '"');		// prevent double quote in object names even if this array not initialized
	else
	{	for (int i=0; i<siNumCharsNotAllowedInObjNames; i++)
		{	if (c == spcNotAllowedInObjNames[i])
				return TRUE;
	}	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CEditCtl, CEdit )

/////////////////////////////////////////////////////////////////////////////
// CEditCtl

BEGIN_MESSAGE_MAP(CEditCtl, CEdit)
   ON_WM_CREATE()
   ON_WM_CHAR()
   ON_WM_SYSKEYDOWN()
   ON_WM_RBUTTONDOWN()
   ON_WM_KILLFOCUS()
   ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR_REFLECT()

   ON_MESSAGE(WM_GETDATASTATUS, OnGetDataStatus)
//   ON_MESSAGE(WM_GETTEXTCOLOR,  OnGetTextColor)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)

	ON_WM_HELPINFO()
END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////

// SAC 8/4/02 - Added new DBID & Instance to support referenced components (lDBID2)
void CEditCtl::ResolveUseDBValues()
{
   if (m_lDBID2 < BEM_COMP_MULT)
   {
      m_lUseDBID       = m_lDBID      ;
      m_iUseDBInstance = m_iDBInstance;

		if (m_iDBInstance < 0 && m_lDBID > BEM_COMP_MULT && m_i1ChildIdx > 0 && m_lDBID2 > 0)		// SAC 5/29/14 - resolve child object index between EACH display, to catch child creation/deletion
		{	int iError=0;
			BEM_ObjType eChildObjType=BEMO_User;
			int iChildObjIdx = BEMPX_GetChildObjectIndex( m_lDBID2, BEMPX_GetClassID( m_lDBID ), iError, eChildObjType, m_i1ChildIdx );
			if (iChildObjIdx >= 0)
				m_iUseDBInstance = iChildObjIdx;
		}
   }
   else
   {
      m_lUseDBID       = 0;
      m_iUseDBInstance = 0;

		int iDT = BEMPX_GetDataType( m_lDBID );
		BEMObject* pObj = NULL;
		if (iDT == BEMP_Obj && BEMPX_GetObject( m_lDBID, pObj, -1, m_iDBInstance ) &&
				pObj && pObj->getClass())
		{	
         m_iUseDBInstance = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
         if (m_iUseDBInstance >= 0)
            m_lUseDBID = m_lDBID2;
		}
   }
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Create Functions

BOOL CEditCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits, long lDBIDOffset,
                       BOOL bTabbedDlgShift, BOOL scale, BOOL chkChr,
                       UINT uiTopicHelp, UINT uiItemHelp )
{
   ASSERT( pControl );

// SAC 8/4/02 - Moved setting of m_lDBID & m_iDBInstance up here from below, added setting of m_lDBID2 and func call to resolve these to UseDB* values
   m_lDBID          = pControl->m_lDBID + lDBIDOffset;
   m_iDBInstance    = pControl->m_iDBInstance;  // SAC 3/3/99
   m_lDBID2         = pControl->m_lDBID2;
	m_i1ChildIdx     = pControl->m_i1ChildIdx;	// SAC 5/29/14
   ResolveUseDBValues();

   BOOL temp = FALSE;

   double xScale = (scale ? appXRatio : 1.0);
   double yScale = (scale ? appYRatio : 1.0);
   CSize size( FontX( (int) (((double) pControl->m_iWidth ) * xScale) ),
               FontY( (int) (((double) pControl->m_iHeight) * yScale) ) );
   CPoint pos( FontX( (int) (((double) pControl->m_iX     ) * xScale) ),
               FontY( (int) (((double) pControl->m_iY     ) * yScale) ) );

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

   // SAC - 1/6/98 - make adjustments to align w/ adjacent combos
   pos.x   -= 1;   pos.y   -= 1;
   size.cx += 2;   size.cy += (fntHtBase == fntHtSys ? 1 : -2);

   m_bAcceptCarriageReturns = (size.cy >= (GetWizFontHeight( pControl->m_iFont ) * 2));  // SAC 6/17/01

   DWORD winStyle = 0;
   int iDataType = BEMPX_GetDataType( m_lUseDBID );
   BOOL bDataIsNumber = CtrlDataIsNumber( iDataType );
   if ( bDataIsNumber && pControl->m_lValue >= 0 )
// SAC - 8/25/98
//      winStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL|ES_MULTILINE|ES_RIGHT;
      winStyle = WS_CHILD|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL|ES_MULTILINE|ES_RIGHT;
   else if (m_bAcceptCarriageReturns)  // SAC 6/17/01
      winStyle = WS_CHILD|WS_TABSTOP|WS_BORDER|WS_VSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN;
   else
//      winStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL|ES_MULTILINE;
      winStyle = WS_CHILD|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL|ES_MULTILINE;

   // SAC - 1/6/98 - Call CreateEx() in order to specify extended style "WS_EX_CLIENTEDGE" which
   //                draws the border as 3D (rather than boring 2D black line)
   //         was -> temp = CEdit::Create( winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "EDIT", "", winStyle, CRect(pos, size),
                          pParentWnd, pControl->m_uiCtrlID );
   if (temp)
   {
      m_iFont        	= pControl->m_iFont;
      m_iPrecOrLen      = (int) ((!bDataIsNumber && pControl->m_lValue == -1) ? _MAX_PATH : pControl->m_lValue);	// SAC 12/19/14
//      m_lDBID        	= pControl->m_lDBID + lDBIDOffset;
//      m_iDBInstance     = pControl->m_iDBInstance;  // SAC 3/3/99
      m_iDataType     	= iDataType;  //BEMPX_GetDataType( m_lUseDBID );
      m_bChkChr      	= chkChr;
      m_bCalledCreate 	= TRUE;
      m_sStatusMsg 		= pControl->m_sStatusMsg;
      
      m_iItemHelpID     = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lUseDBID ) : uiItemHelp);
      m_iTopicHelpID    = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lUseDBID ) : uiTopicHelp);

      SetFont( GetWizFont(m_iFont), TRUE );

      m_bUnused   = FALSE;

      m_cEditableCondition = pControl->m_cEditableCondition;
      m_bEditable = (BEMPX_GetCompIsEditable( m_lUseDBID ) && m_cEditableCondition.MissingOrTrue());
      m_bAllowEdits = bAllowEdits;

// SAC 8/7/00 - added following m_bNoDoubleQuote stuff
// SAC 11/28/00 - Expanded use of this flag to include all properties of type BEMP_Str
      m_bNoDoubleQuote = (m_lUseDBID > 0  &&  ( iDataType == BEMP_Str  ||
                                                (BEMPX_GetPropertyID(m_lUseDBID) == 0 && BEMPX_GetArrayID(m_lUseDBID) == BEM_PARAM0_NAME) ) );
      m_bValidPath = (!bDataIsNumber && pControl->m_lValue == -1);	// SAC 12/19/14

// SAC - 8/25/98
//      BOOL dispOK = (OnDisplayData(0,0)!=0);
   }
   return temp;
}


BOOL CEditCtl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                       int iFont, int iPrecOrLen, const char FAR* lpMsg, long lDBID, 
                       int iDT, UINT uiIHelpID, UINT uiTHelpID, BOOL chkChr, int iDBInstance )
{
   BOOL temp = FALSE;
   // SAC - 1/6/98 - Call CreateEx() in order to specify extended style "WS_EX_CLIENTEDGE" which
   //                draws the border as 3D (rather than boring 2D black line)
   //         was -> temp = CEdit::Create( dwStyle, rect, pParentWnd, nID );
   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "EDIT", "", dwStyle, rect, pParentWnd, nID );
   if (temp)
   {
      m_iFont        	= iFont;
      m_iPrecOrLen     	= iPrecOrLen;
      m_lDBID        	= lDBID;
      m_iDBInstance     = iDBInstance;  // SAC 3/3/99

      m_lDBID2         = 0;  // SAC 8/4/02
		m_i1ChildIdx = -1;	// SAC 5/29/14
      ResolveUseDBValues();

      m_iDataType     	= (iDT >= 0) ? iDT : BEMPX_GetDataType( m_lUseDBID );
      m_bChkChr      	= chkChr;
      m_bCalledCreate 	= TRUE;
      m_sStatusMsg 		= lpMsg;
      
      m_iItemHelpID     = (uiIHelpID > 0) ? uiIHelpID : BEMPX_GetItemHelpID(  m_lUseDBID );
      m_iTopicHelpID    = (uiTHelpID > 0) ? uiTHelpID : BEMPX_GetTopicHelpID( m_lUseDBID );

      SetFont( GetWizFont(m_iFont), TRUE );

      m_bUnused   = FALSE;

      m_bEditable = BEMPX_GetCompIsEditable( m_lUseDBID );
      m_bAllowEdits = TRUE;

// SAC 8/7/00 - added following m_bNoDoubleQuote stuff
// SAC 11/28/00 - Expanded use of this flag to include all properties of type BEMP_Str
      m_bNoDoubleQuote = (m_lUseDBID > 0  &&  ( m_iDataType == BEMP_Str  ||
                                                (BEMPX_GetPropertyID(m_lUseDBID) == 0 && BEMPX_GetArrayID(m_lUseDBID) == BEM_PARAM0_NAME) ) );
      m_bValidPath = FALSE;	// SAC 12/19/14

      m_bAcceptCarriageReturns = ((rect.bottom - rect.top) >= (GetWizFontHeight(m_iFont) * 2));  // SAC 6/17/01

// SAC - 8/25/98
//      BOOL dispOK = (OnDisplayData(0,0)!=0);
   }
   return temp;
}


int CEditCtl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   int temp = CEdit::OnCreate( lpCreateStruct );

   if (temp == 0)
   {
      m_iFont       = FNT_STD;
      m_iPrecOrLen  = 0;
      m_lDBID       = 0;
      m_iDBInstance = -1;  // SAC 3/3/99
      m_lDBID2         = 0;  // SAC 8/4/02
		m_i1ChildIdx = -1;	// SAC 5/29/14
      ResolveUseDBValues();
      m_iDataType   = -1;
      m_bCalledCreate = FALSE;
      m_bUnused     = FALSE;
      m_bEditable   = TRUE;
      m_bAllowEdits = TRUE;
      
      SetFont( GetWizFont(FNT_STD), TRUE );

// SAC 8/7/00 - added following m_bNoDoubleQuote stuff
      m_bNoDoubleQuote = FALSE;
      m_bValidPath = FALSE;	// SAC 12/19/14

      m_bAcceptCarriageReturns = FALSE;  // SAC 6/17/01

// SAC - 8/25/98
//      BOOL dispOK = (OnDisplayData(0,0)!=0);
   }
   return temp;
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Grey out control background when the data is not editable

HBRUSH CEditCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
//   pDC->SetTextColor( GetBEMPUITextColor( BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance ) ) );
// SAC 6/17/01 - Write text in Black if data has been edited
   pDC->SetTextColor( GetBEMPUITextColor( (GetModify() ? BEMS_UserDefined : BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance )) ) );

	// TODO: Change any attributes of the DC here
	if (!m_bEditable)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
      return buttonBrush;
   }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	return NULL;
	return windowBrush;
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - OnChar

// Input character filter
void CEditCtl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( (nChar == VK_TAB) || (nChar == VK_ESCAPE) )
      CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
   else if (!m_bEditable)
   {
      MessageBeep( MB_OK );
      MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
   }
   else if (!m_bAllowEdits)
   {
      MessageBeep( MB_OK );
      MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
   }
//   else if (eiCurAnalysisStep != AS_None)
//   {
//      MessageBeep( MB_OK );
//      MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
//   }
   else if (ObjectIsFromLibrary( m_lUseDBID, m_iUseDBInstance ))
   {
   }
   else if (m_bUnused)
      MessageBeep( MB_OK );
//   else if (bCtrlDown && (nChar == 'c' || nChar == 'C' || nChar == 'v' || nChar == 'V' || nChar == 'x' || nChar == 'X'))
   else if (nChar == 3 || nChar == 22 || nChar == 24)
      CEdit::OnChar(nChar, nRepCnt, nFlags);  // SAC 11/19/01 - permit clipboard copy/paste/cut
   else if ( (m_bChkChr) && 
             ((nChar == '*') || (nChar == '?')  || (nChar == '|') ||
              (nChar == '/') || (nChar == '\\') || (nChar == ':') ||
              (nChar == '<') || (nChar == '>')  || (nChar == '"') ||
              (nChar == '.')) )
//             ((nChar == ' ') || (nChar == '(')  || (nChar == ')') ||
//              (nChar == '@') || (nChar == '#')  || (nChar == '%') ||
//              (nChar == '^') || (nChar == '&')  || (nChar == '*') ||
//              (nChar == '=') || (nChar == '+')  || (nChar == '?') ||
//              (nChar == '[') || (nChar == ']')  || (nChar == '|') ||
//              (nChar == '`') || (nChar == '\'') || (nChar == '/') ||
//              (nChar == ',') || (nChar == '\\') || (nChar == ':') ||
//              (nChar == '<') || (nChar == '>')  || (nChar == '"') ||
//              (nChar == '{') || (nChar == '}')  || (nChar == '$') ||
//              (nChar == '!') || (nChar == ';')) )
      MessageBeep( MB_OK );
	else if (m_bValidPath && !IsValidPathCharacter( (char) nChar ))	// SAC 12/19/14
      MessageBeep( MB_OK );
// SAC 8/7/00 - added following m_bNoDoubleQuote stuff
//   else if ( m_bNoDoubleQuote && ( nChar == '"' || nChar == ',' || nChar == '\'' || nChar == '!' || nChar == ';' ) )  // SAC 8/19/14 - expand limits on object name characters
   else if ( m_bNoDoubleQuote && EditCtlCharacterNotAllowedInObjectname( (char) nChar ) )  // SAC 8/20/14 - enabled product-specific object name character restrictions
      MessageBeep( MB_OK );
   else if ( (nChar == VK_END   ) ||
             (nChar == VK_HOME  ) ||
             (nChar == VK_LEFT  ) ||
             (nChar == VK_UP    ) ||
             (nChar == VK_RIGHT ) ||
             (nChar == VK_DOWN  ) ||
             (nChar == VK_BACK) || (nChar == VK_DELETE) )
      CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
//   else if (nChar == VK_RETURN) 
   else if (nChar == VK_RETURN && !m_bAcceptCarriageReturns)  // SAC 6/17/01
   {
      if (GetModify())
         OnUpdateData(0,0);
   }
   else 
   {
      if ( (m_iDataType == BEMP_Sym) || (m_iDataType == BEMP_Obj) )
         MessageBeep( MB_OK );
      else if ( ( (CtrlDataIsNumber(m_iDataType)) && (m_iPrecOrLen == 0) ) &&
                ( ((nChar < '0') && (nChar != '-')) || (nChar > '9') ) )
         MessageBeep( MB_OK );
      else if ( (m_iDataType == BEMP_Flt) &&
                ( ((nChar < '0') && (nChar != '.') && (nChar != '-')) ||
                  ((nChar > '9') && (nChar != 'E') && (nChar != 'e')) ) )
         MessageBeep( MB_OK );
//      // SAC 3/19/01 - Replaced old numeric char checking stuff (above) w/ new version that takes into account Windows Locale settings (below)
//      else if ( CtrlDataIsNumber(m_iDataType)  &&  !BEMPX_IsNumericChar( (char) nChar, (m_iDataType == BEMP_Flt ? 2 : 0) ) )
//         MessageBeep( MB_OK );
      else if ( (m_iDataType == BEMP_Str) &&
                (m_iPrecOrLen >= 0 && GetWindowTextLength() >= m_iPrecOrLen) ) // RW 10/4/02 - Added check for m_iPrecOrLen to be less than 0 to indicate no max length limit
      {
         int iSt, iEnd;
         GetSel( iSt, iEnd );
         if (iEnd > iSt)  // => some chars highlighted
            CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
         else
            MessageBeep( MB_OK );
      }
      else
         CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
   }
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Focus Stuff

void CEditCtl::OnKillFocus( CWnd* pNewWnd )
{
   if (GetModify())
      OnUpdateData(0,0);
      
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, NULL, 0 );
//   GetMainFrame()->SetStatusBarStrings("", 0);
      
   CEdit::OnKillFocus( pNewWnd );
}

void CEditCtl::OnSetFocus( CWnd* pOldWnd )
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//   GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lUseDBID);

   CEdit::OnSetFocus( pOldWnd );

   // SAC 4/20/00 - added to ensure contents of edit control are ALWAYS highlighted upon the control gaining focus
   SetSel( 0, -1 );  // Highlight();
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Display & Update Data Stuff

LONG CEditCtl::OnGetDataStatus(UINT, LONG)
{
   return (long) BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
}

int CEditCtl::RangeCheckViolation( BOOL bSilent, CString* psMsg )
{
   double fData = 0;
   BOOL bCheckValue = FALSE;
   if (m_iDataType == BEMP_Int || m_iDataType == BEMP_Flt)
   {
      CString newStr;
      GetWindowText( newStr );
      // SAC 7/3/00 - added check for newStr NOT blank to avoid some invalid range checks
      if (!newStr.IsEmpty())
      {
         fData = BEMPX_StringToFloat( newStr );  // SAC 1/7/01 - was: RemoveCommasAndConvertToFloat( newStr );
         bCheckValue = TRUE;
      }
   }
   else if (m_iDataType == BEMP_Sym)  // SAC 5/2/02 - Added check of BEMP_Sym data
   {
      long lData;
      if (BEMPX_SetDataInteger( m_lUseDBID, lData, 0, -1, m_iUseDBInstance ))
      {
         fData = (double) lData;
         bCheckValue = TRUE;
      }
   }

//   return (bCheckValue ? BEMPX_PerformRangeCheck( m_lUseDBID, fData, bSilent, psMsg, m_iUseDBInstance ) : 0);  // SAC 8/4/02 - Added m_iUseDBInstance argument
	int iRetVal = 0;
	if (bCheckValue)
	{	QString qsMsg;
		iRetVal = BEMPX_PerformRangeCheck( m_lUseDBID, fData, bSilent, (psMsg==NULL ? NULL : &qsMsg), m_iUseDBInstance );  // SAC 8/4/02 - Added m_iUseDBInstance argument
		if (psMsg && !qsMsg.isEmpty())
			*psMsg = qsMsg.toLatin1().constData();
	}
   return iRetVal;
}

//LONG CEditCtl::OnGetTextColor(UINT, LONG)
//{
//   int iDataStatus = BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
//
//   // Check for range check error
//   if ( (iDataStatus > BEMS_Undefined && iDataStatus < BEMS_NumTypes) &&
//        (m_iDataType == BEMP_Int || m_iDataType == BEMP_Flt) )
//   {
//      if (RangeCheckViolation( TRUE ) == RANGE_ERROR)
//         return RANGEERROR_TEXT_COLOR_IDX;
//   }
//
//   return (long) (iDataStatus + NUM_RESERVED_TEXT_COLORS);
//}


LONG CEditCtl::OnGetDBID(UINT, LONG)
{
   return m_lUseDBID;
}

LONG CEditCtl::OnGetDBInstance(UINT, LONG)
{
   return m_iUseDBInstance;
}


LONG CEditCtl::OnDisplayData(UINT, LONG)
{
   ResolveUseDBValues();  // SAC 8/4/02 - reset UseDB* values upon each display in case referenced component has changed

   // reset editable flag
   m_bEditable = (BEMPX_GetCompIsEditable( m_lUseDBID ) && m_cEditableCondition.MissingOrTrue());

   if (m_lUseDBID > 0 && m_iDataType >= 0)
   {
      int i1Class = BEMPX_GetClassID( m_lUseDBID );
      BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iUseDBInstance );
      if (eObjType != BEMO_NumTypes && BEMPX_GetNumObjects( i1Class, eObjType ) > 0)
      {
         BEMPX_SetDataString( m_lUseDBID, m_sCurrStr, (m_iPrecOrLen >= 0), m_iPrecOrLen, m_iDataType, m_iUseDBInstance );

         Invalidate();
         SetWindowText( m_sCurrStr );
         SetModify( FALSE );

         if (GetFocus() == this)
            SetSel( 0, -1 );  // Highlight();
      }
   }

   return 1;
}


static char BASED_CODE szErrZeroLengthName[] = "Component names must contain at least one character.";
static char BASED_CODE szErrNameNotUnique[]  = "This name is already in use, enter a unique name for this component.";

LONG CEditCtl::OnUpdateData( UINT, LONG)
{
   int iRangeViolation = 0;
   int i1Class = BEMPX_GetClassID( m_lUseDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iUseDBInstance );
   if ( m_lUseDBID > 0 && m_iDataType >= 0 && eObjType == BEMO_User &&
        BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
   {
		int iSetDataRetVal = -1;
		BOOL bUpdateFrameTitle = FALSE;
		CString newStr;		// SAC 5/29/14 - moved string retrieval up from below and added code to RESTORE DEFAULT if updating control left blank
		GetWindowText( newStr );
		if (newStr.IsEmpty())
		{
			// SAC 4/28/00 - added to prevent storage of 0-length names or names which are not unique within user and userlib components
			int iArray = BEMPX_GetArrayID( m_lUseDBID );
			if (iArray == BEM_PARAM0_NAME)
			{
				MessageBeep( MB_OK );
				MessageBox( szErrZeroLengthName, szErrorCaption, MB_ICONSTOP );
				OnDisplayData(0,0);
			}
			else
			{	int iError;
				if (m_iUseDBInstance >= 0)
					BEMPX_SetActiveObjectIndex( i1Class, m_iUseDBInstance );
				BEMPX_DefaultProperty( m_lUseDBID, iError );  //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
				iSetDataRetVal = 0;
				SetModify( FALSE );
			}
		}
		else
		{
	      iRangeViolation = RangeCheckViolation();  // will display error/warning/message

	      // prevent setting values which cause RANGE_ERRORs
	      if (iRangeViolation == RANGE_ERROR)
	         OnDisplayData(0,0);
	      else
	      {
	      //   CString newStr;
	      //   GetWindowText( newStr );

	         void* pData = NULL;
	         long lData;
	         double fData;
	         int iDataType = m_iDataType;
	         if (m_iDataType == BEMP_Int)
	         {
	            lData = BEMPX_StringToLong( newStr );  // SAC 1/7/01 - was: RemoveCommasAndConvertToLong( newStr );
	            pData = &lData;
	         }
	         else if (m_iDataType == BEMP_Flt)
	         {
	            fData = BEMPX_StringToFloat( newStr );  // SAC 1/7/01 - was: RemoveCommasAndConvertToFloat( newStr );
	            pData = &fData;
	         }
	         else
	         {
	            iDataType = BEMP_Str;
	            pData = (void*) ((const char*) newStr);

	            // set flag to update frame title if project name modified
	            if (slProjNameDBID == 0)
	               slProjNameDBID = BEMPX_GetDatabaseID( "Proj:Name" );
	            if (m_lUseDBID == slProjNameDBID)
	               bUpdateFrameTitle = TRUE;

	            // SAC 4/28/00 - added to prevent storage of 0-length names or names which are not unique within user and userlib components
	            int iArray = BEMPX_GetArrayID( m_lUseDBID );
	            if (iArray == BEM_PARAM0_NAME)
	            {
	            //   if (newStr.GetLength() == 0)
	            //   {
	            //      pData = NULL;
	            //      MessageBeep( MB_OK );
	            //      MessageBox( szErrZeroLengthName, szErrorCaption, MB_ICONSTOP );
	            //   }
	            //   else if (newStr != m_sCurrStr  &&  BEMPX_GetComponentByName( newStr, FALSE, 0, TRUE ) != NULL)
	               if (newStr != m_sCurrStr  &&  BEMPX_GetComponentByName( newStr, FALSE, 0, TRUE ) != NULL)
	               {
	                  pData = NULL;
	                  MessageBeep( MB_OK );
	                  MessageBox( szErrNameNotUnique, szErrorCaption, MB_ICONSTOP );
	               }
	            }
	         }

	         if (pData != NULL)
	         {
	            if (m_iUseDBInstance >= 0)
	               BEMPX_SetActiveObjectIndex( i1Class, m_iUseDBInstance );

	            iSetDataRetVal = BEMPX_SetBEMData( m_lUseDBID, iDataType, pData );

	            SetModify( FALSE );
	         }
	         else
	            OnDisplayData(0,0);
		}	}

		if (iSetDataRetVal >= 0)
		{	// Post-processing following mods
			GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );

			CFrameWnd* pFrame = GetParentFrame();
			if (pFrame)
			{	// redisplay status bar strings
				pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );

				if (bUpdateFrameTitle)
					pFrame->OnUpdateFrameTitle(TRUE);
			}
		}
   }

   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - NavEdit-related functions


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Quick Menu Stuff

void CEditCtl::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      DoQuickMenu();
   else
      CEdit::OnSysChar(nChar, nRepCnt, nFlags);
}

void CEditCtl::OnRButtonDown( UINT /*nFlags*/, CPoint /*point*/ )
{
   SetSel( 0, -1 );  // Highlight();
   DoQuickMenu();
}

// SAC 4/20/00 - function replaced by call to: SetSel( 0, -1 )
// void CEditCtl::Highlight()
// {
//    CRect field;
//    GetRect( field );
//    int delta = (field.bottom - field.top) / 2;
//    SendMessage( WM_LBUTTONDOWN, NULL,     MAKELPARAM(               0, delta ) );
//    SendMessage( WM_LBUTTONDOWN, MK_SHIFT, MAKELPARAM( field.Width()+1, delta ) );
//    SendMessage( WM_LBUTTONUP,   MK_SHIFT, MAKELPARAM( field.Width()+1, delta ) );
// }

CWnd* CEditCtl::SetFocus()
{
   CWnd* retVal = CEdit::SetFocus();
   SetSel( 0, -1 );  // Highlight();
   return retVal;
}

// Process Quick Menu
void CEditCtl::DoQuickMenu()
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
   {
      CRect winRect;
      GetWindowRect( winRect );
      QuickMenuInfo qmInfo;
      qmInfo.m_iLeft  = winRect.left;
      qmInfo.m_iTop   = winRect.top;
      qmInfo.m_iRight = winRect.right;
      qmInfo.m_uiItemHelpID  = m_iItemHelpID;
      qmInfo.m_uiTopicHelpID = m_iTopicHelpID;
      qmInfo.m_lDBID  = m_lUseDBID;
      qmInfo.m_iDBInstance = m_iUseDBInstance;
      qmInfo.m_bEditable = m_bEditable;
      qmInfo.m_bObjectAssign = FALSE;
      qmInfo.m_iDBaseType = QMI_DBASETYPE_BEMPROC;
      qmInfo.m_dwFlags = 0;

      pFrame->SendMessage( WM_QUICKMENU, NULL, (LPARAM) &qmInfo );
   }
//   UINT uiQuickMask = QMI_ITEMHELP | QMI_TOPICHELP;
//   int iStatus = BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
//   int iPropID = BEMPX_GetPropertyID( m_lUseDBID );
//   if ( (iStatus == BEMS_UserDefined) && (iPropID > 0) )
//      uiQuickMask |= QMI_DEFAULT;
//
//   CRect winRect;
//   GetWindowRect( winRect );
//   GetMainFrame()->DoQuickMenu( winRect.left, winRect.right, winRect.top, uiQuickMask,
//                                m_iItemHelpID, m_iTopicHelpID, m_lUseDBID );
}


void CEditCtl::PostNcDestroy()
{
	if ( (m_bCreatedByClassName) || (m_bCalledCreate) )
   {
		delete this;
   }
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Diagnostics

#ifdef _DEBUG
void CEditCtl::AssertValid() const
{
	CEdit::AssertValid();
}

void CEditCtl::Dump(CDumpContext& dc) const
{
	CEdit::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CEditCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CEdit::OnHelpInfo(pHelpInfo);
}
