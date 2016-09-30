// CTL_EDIT.CPP  :  Contains CEditCtl routines
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
#include "CUIGlobl.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\expRanges.h"
#include "mainfrm.h"
// #include "Screens.h"
#include "ctl_edit.h" 
// #include "quick.h" 
#include "ComplianceUIDoc.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

static char BASED_CODE szNoEntries[] = "---";

static char BASED_CODE szErrorCaption[] = "Edit Control Error";

static long slProjNameDBID = 0;

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
   ON_MESSAGE(WM_GETTEXTCOLOR,  OnGetTextColor)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Create Functions

BOOL CEditCtl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                       int iFont, int iPrecOrLen, const char FAR* lpMsg, long lDBID, 
                       int iDT, UINT uiIHelpID, UINT uiTHelpID, BOOL chkChr,
                       BOOL bForceEditable )
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
      m_iDataType     	= (iDT >= 0) ? iDT : BEMPX_GetDataType( m_lDBID );
      m_bChkChr      	= chkChr;
      m_bCalledCreate 	= TRUE;
      m_sStatusMsg 		= lpMsg;
      
      m_iItemHelpID     = (uiIHelpID > 0) ? uiIHelpID : BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID    = (uiTHelpID > 0) ? uiTHelpID : BEMPX_GetTopicHelpID( m_lDBID );
      
      SetFont( GetCUIFont(m_iFont), TRUE );

      m_bUnused   = FALSE;

      m_bEditable = (bForceEditable || BEMPX_GetCompIsEditable( m_lDBID ));
//      if (!m_bEditable)
//      {
//      	CDC* pDC = GetDC();
//         if (pDC)
//         {
//            pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
////            pDC->SetBkColor( RGB(192,192,192) );
//            ReleaseDC(pDC);
//         }
//      }

// SAC 8/7/00 - added following m_bNameDBID stuff
      m_bNameDBID = (m_lDBID > 0 && BEMPX_GetPropertyID(m_lDBID) == 0 && BEMPX_GetArrayID(m_lDBID) == BEM_PARAM0_NAME);

      BOOL dispOK = (OnDisplayData(0,0)!=0);			dispOK;
   }
   return temp;
}


int CEditCtl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   int temp = CEdit::OnCreate( lpCreateStruct );

   if (temp == 0)
   {
      m_iFont      = FNT_STD;
      m_iPrecOrLen = 0;
      m_lDBID      = 0;
      m_iDataType  = -1;
      m_bCalledCreate = FALSE;
      m_bUnused    = FALSE;
      m_bEditable  = TRUE;
      
      SetFont( GetCUIFont(FNT_STD), TRUE );

// SAC 8/7/00 - added following m_bNameDBID stuff
      m_bNameDBID = FALSE;

      BOOL dispOK = (OnDisplayData(0,0)!=0);			dispOK;
   }
   return temp;
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Grey out control background when the data is not editable

HBRUSH CEditCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
	// TODO: Change any attributes of the DC here
	if (!m_bEditable)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
      return buttonBrush;
//      pDC->SetBkColor( RGB(192,192,192) );
//      return greyBrush;
   }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Data Segment Stuff

//16 // Borrowed from Microsoft's Global Edit Control Sample
//16 BOOL CEditCtl::PreCreateWindow(CREATESTRUCT &cs)
//16 {
//16    // Allocate a shareable, moveable, zero initialized memory
//16    // block of size SEGMENT_SIZE
//16    m_ghEditDS = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE | GMEM_ZEROINIT, SEGMENT_SIZE);;
//16    
//16    // If the allocation was successful
//16    if (m_ghEditDS != NULL)
//16    {
//16       // Get a pointer to the memory
//16       LPVOID lpPtr = ::GlobalLock(m_ghEditDS);
//16       
//16       // Set up system information so that the memory can be
//16       // managed like a heap
//16       ::LocalInit(HIWORD((LONG)lpPtr), 0, (WORD)(::GlobalSize(m_ghEditDS) - 16));
//16       
//16       // Unlock the memory so that the system has control
//16       ::UnlockSegment(HIWORD((LONG)lpPtr));
//16       
//16       // Set the instance handle to the segment of the memory block.
//16       // Edit controls use the hInstance variable as their data segment
//16       // since the instance handle is also the application's DS. In this
//16       // case we have allocated a completely different segment and
//16       // used that DS instead.
//16       cs.hInstance = (HINSTANCE) HIWORD((LONG)lpPtr);
//16       return TRUE;
//16    }
//16    else
//16       return FALSE;
//16 }


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
//      ::MessageBox( NULL, szErrNotEditable, szErrorCaption, MB_ICONSTOP );
      MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
   }
   else if (eInterfaceMode != IM_INPUT)
   {
      MessageBeep( MB_OK );
//      ::MessageBox( NULL, szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
      MessageBox( szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
   }
   else if (eiCurAnalysisStep != AS_None)
   {
      MessageBeep( MB_OK );
//      ::MessageBox( NULL, szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
      MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
   }
   else if (ObjectIsFromLibrary( m_lDBID ))
   {
   }
   else if (m_bUnused)
      MessageBeep( MB_OK );
   else if ( (m_bChkChr) && 
             ((nChar == '*') || (nChar == '?')  || (nChar == '|') ||
              (nChar == '/') || (nChar == '\\') || (nChar == ':') ||
              (nChar == '<') || (nChar == '>')  || (nChar == '"') ||
              (nChar == '.')) )
// SAC 8/7/00 - replaced old set of "illegal" characters (below) with new set (above)
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
// SAC 8/7/00 - added following m_bNameDBID stuff
//   else if ( m_bNameDBID && ( nChar == '"' || nChar == ',' || nChar == '\'' || nChar == '!' || nChar == ';' ) )  // SAC 8/19/14 - expand limits on object name characters
   else if ( m_bNameDBID && CharacterNotAllowedInObjectname( (char) nChar ) )  // SAC 8/20/14 - enable product-specific restrictions on object name characters
      MessageBeep( MB_OK );
   else if ( (nChar == VK_END   ) ||
             (nChar == VK_HOME  ) ||
             (nChar == VK_LEFT  ) ||
             (nChar == VK_UP    ) ||
             (nChar == VK_RIGHT ) ||
             (nChar == VK_DOWN  ) ||
             (nChar == VK_BACK) || (nChar == VK_DELETE) )
      CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
   else if (nChar == VK_RETURN) 
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
      else if ( (m_iDataType == BEMP_Str) &&
                (GetWindowTextLength() >= m_iPrecOrLen) )
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
      
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings("", 0);
      
   CEdit::OnKillFocus( pNewWnd );
}

void CEditCtl::OnSetFocus( CWnd* pOldWnd )
{
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);

   CEdit::OnSetFocus( pOldWnd );

   // SAC 4/20/00 - added to ensure contents of edit control are ALWAYS highlighted upon the control gaining focus
   SetSel( 0, -1 );  // Highlight();
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Display & Update Data Stuff

LONG CEditCtl::OnGetDataStatus(UINT, LONG)
{
   return (long) BEMPX_GetDataStatus( m_lDBID );
}

int CEditCtl::RangeCheckViolation( BOOL bSilent, CString* psMsg )
{
	int iRetVal = 0;
   if (m_iDataType == BEMP_Int || m_iDataType == BEMP_Flt)
   {
      CString newStr;
      GetWindowText( newStr );

      double fData = BEMPX_StringToFloat( newStr);  // SAC 1/7/01 - was: RemoveCommasAndConvertToFloat( newStr );

		QString qsMsg;
		iRetVal = BEMPX_PerformRangeCheck( m_lDBID, fData, bSilent, (psMsg==NULL ? NULL : &qsMsg) );
		if (psMsg && !qsMsg.isEmpty())
			*psMsg = qsMsg.toLatin1().constData();
   }
   return iRetVal;
}

LONG CEditCtl::OnGetTextColor(UINT, LONG)
{
   int iDataStatus = BEMPX_GetDataStatus( m_lDBID );

   // Check for range check error
   if ( (iDataStatus > BEMS_Undefined && iDataStatus < BEMS_NumTypes) &&
        (m_iDataType == BEMP_Int || m_iDataType == BEMP_Flt) )
   {
      if (RangeCheckViolation( TRUE ) == RANGE_ERROR)
         return RANGEERROR_TEXT_COLOR_IDX;

//      CString newStr;
//      GetWindowText( newStr );
//
//      if (m_iDataType == BEMP_Int)
//      {
//         long lData = BEMPX_StringToLong( newStr);  // SAC 1/7/01 - was: RemoveCommasAndConvertToLong( newStr );
//
//         if (BEMPX_PerformRangeCheck( m_lDBID, (double) lData, TRUE ) > 0)
//            return RANGEERROR_TEXT_COLOR_IDX;
//      }
//      else if (m_iDataType == BEMP_Flt)
//      {
//         double fData = BEMPX_StringToFloat( newStr);  // SAC 1/7/01 - was: RemoveCommasAndConvertToFloat( newStr );
//
//         if (BEMPX_PerformRangeCheck( m_lDBID, fData, TRUE ) > 0)
//            return RANGEERROR_TEXT_COLOR_IDX;
//      }
   }

   return (long) (iDataStatus + NUM_RESERVED_TEXT_COLORS);
}


LONG CEditCtl::OnGetDBID(UINT, LONG)
{
   return m_lDBID;
}

LONG CEditCtl::OnGetDBInstance(UINT, LONG)
{
   return -1;
}


LONG CEditCtl::OnDisplayData(UINT, LONG)
{
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class );
   if ( (m_lDBID > 0) && (m_iDataType >= 0) &&
        (eObjType != BEMO_NumTypes) &&
        (BEMPX_GetNumObjects( i1Class, eObjType ) > 0) )
   {
      BEMPX_SetDataString( m_lDBID, m_sCurrStr, (m_iPrecOrLen >= 0), m_iPrecOrLen, m_iDataType );

      Invalidate();
      SetWindowText( m_sCurrStr );
      SetModify( FALSE );

      if (GetFocus() == this)
         SetSel( 0, -1 );  // Highlight();
   }

   return 1;
}


LONG CEditCtl::OnUpdateData( UINT, LONG)
{
   int iRangeViolation = 0;
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class );
   if ( (m_lDBID > 0) && (m_iDataType >= 0) &&
        (eObjType == BEMO_User) &&
        (BEMPX_GetNumObjects( i1Class, eObjType ) > 0) )
   {
      iRangeViolation = RangeCheckViolation();  // will display error/warning/message

      // prevent setting values which cause RANGE_ERRORs
      if (iRangeViolation == RANGE_ERROR)
         OnDisplayData(0,0);
      else
      {
         CString newStr;
         GetWindowText( newStr );

         void* pData = NULL;
         long lData;
         double fData;

         int iDataType = m_iDataType;
         BOOL bUpdateFrameTitle = FALSE;

         if (m_iDataType == BEMP_Int)
         {
            lData = BEMPX_StringToLong( newStr);  // SAC 1/7/01 - was: RemoveCommasAndConvertToLong( newStr );

//            if (BEMPX_PerformRangeCheck( m_lDBID, (double) lData ) == 0)
               pData = &lData;
         }
         else if (m_iDataType == BEMP_Flt)
         {
            fData = BEMPX_StringToFloat( newStr);  // SAC 1/7/01 - was: RemoveCommasAndConvertToFloat( newStr );

//            if (BEMPX_PerformRangeCheck( m_lDBID, fData ) == 0)
               pData = &fData;
         }
         else
         {
            iDataType = BEMP_Str;
            pData = (void*) ((const char*) newStr);

            // set flag to update frame title if project name modified
            if (slProjNameDBID == 0)
               slProjNameDBID = BEMPX_GetDatabaseID( "Proj:Name" );
            if (m_lDBID == slProjNameDBID)
               bUpdateFrameTitle = TRUE;
         }

         if (pData != NULL)
         {
            int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, pData );

            if (iSetDataRetVal >= 0)
            {
               SetDataModifiedFlag( TRUE );

               // execute compliance rulelist #1
               GetParentFrame()->SendMessage( WM_EVALPROPOSED );

               // send a message to the main view's tree control via CMainFrame in case the tree requires updating
               GetParentFrame()->SendMessage( WM_UPDATETREE, 0, m_lDBID );

               // redisplay all currently displayed database data
               GetParent()->PostMessage( WM_DISPLAYMODS );

               // redisplay status bar strings
	// SAC 10/29/15 - status bar no longer used to display property info
	//               GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);

               if (bUpdateFrameTitle)
                  GetMainFrame()->OnUpdateFrameTitle(TRUE);
            }

            SetModify( FALSE );
         }
         else
            OnDisplayData(0,0);
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
   UINT uiQuickMask = QMI_ITEMHELP | QMI_TOPICHELP;
   int iStatus = BEMPX_GetDataStatus( m_lDBID );
   int iPropID = BEMPX_GetPropertyID( m_lDBID );
   if ( (iStatus == BEMS_UserDefined) && (iPropID > 0) )
      uiQuickMask |= QMI_DEFAULT;

//   int iError = 0;
//   int iCritDefIdx = BEMPX_GetCriticalDefaultIndex( m_lDBID, iError );
//   if ( (iError >= 0) && (iCritDefIdx > 0) )
//      uiQuickMask |= QMI_COMMENT;

   CRect winRect;
   GetWindowRect( winRect );
   GetMainFrame()->DoQuickMenu( winRect.left, winRect.right, winRect.top, uiQuickMask,
                                m_iItemHelpID, m_iTopicHelpID, m_lDBID );
}


/////////////////////////////////////////////////////////////////////////////
// CEditCtl - Class Registration Stuff

//16 // Define statics
//16 WNDPROC CEditCtl::pfnSuperWndProc = NULL ;
//16 
//16 
//16 LONG CALLBACK EXPORT
//16 CEditCtl::FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
//16 {
//16 	//
//16 	// Construct the object and then attach the hWnd to it.
//16 	//
//16 	CEditCtl* pWnd = new CEditCtl;
//16 	pWnd->Attach(hWnd);
//16 
//16 	pWnd->m_bCreatedByClassName = TRUE;
//16 
//16 	//
//16 	// Subclass the window by changing the window procedure to AfxWndProc
//16 	// and pass the current message to it.
//16 	//
//16 	::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);
//16 
//16 #ifdef STRICT
//16 	return ::CallWindowProc((WNDPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//16 #else
//16 	return ::CallWindowProc((FARPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//16 #endif
//16 	//DER
//16 }
//16 
//16 
//16 BOOL CEditCtl::RegisterMyClass()
//16 {
//16 	WNDCLASS wcls;
//16 
//16 	if(!::GetClassInfo(NULL, "edit", &wcls) )
//16 	{
//16 		return FALSE;
//16 	}
//16 
//16 	if (pfnSuperWndProc == NULL) 
//16 		pfnSuperWndProc = wcls.lpfnWndProc;
//16 
//16 	ASSERT( pfnSuperWndProc == wcls.lpfnWndProc);
//16 
//16 	static const char szClassName[] = "ctledit";
//16 	if(::GetClassInfo(AfxGetInstanceHandle(), szClassName, &wcls))
//16 	{
//16 		return (wcls.lpfnWndProc == CEditCtl::FirstMsgOnlyWndProc);
//16 	}
//16 
//16 	wcls.lpfnWndProc = CEditCtl::FirstMsgOnlyWndProc;
//16 	wcls.hInstance = AfxGetInstanceHandle();
//16 	wcls.lpszClassName = szClassName;
//16 
//16 	return (RegisterClass(&wcls) !=0);
//16 }


void CEditCtl::PostNcDestroy()
{
	if ( (m_bCreatedByClassName) || (m_bCalledCreate) )
   {
//16       if (m_ghEditDS != NULL)
//16       {
//16          ::GlobalUnlock( m_ghEditDS );
//16          ::GlobalFree(   m_ghEditDS );
//16       }

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

