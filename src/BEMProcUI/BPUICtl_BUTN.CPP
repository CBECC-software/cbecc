// BPUIBPUICtl_BUTN.CPP  :  Contains CButtonCtl routines
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
#include "screens.h"
#include "BPUICtl_butn.h" 
#include "BEMProcUIX.h"
#include "BEMProcDlgCreate.h"
#include "memLkRpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


static char BASED_CODE szErrorCaption[] = "Button Control Error";

IMPLEMENT_DYNAMIC( CButtonCtl, CButton )

/////////////////////////////////////////////////////////////////////////////
// CButtonCtl

BEGIN_MESSAGE_MAP(CButtonCtl, CButton)
   ON_WM_CREATE()
   ON_WM_GETDLGCODE()
   ON_WM_KEYDOWN()
   ON_WM_KEYUP()

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

	ON_WM_CTLCOLOR_REFLECT()
   ON_WM_SYSKEYDOWN()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_RBUTTONDOWN()
   ON_WM_KILLFOCUS()
   ON_WM_SETFOCUS()

	ON_WM_HELPINFO()
END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////

// SAC 8/4/02 - Added new DBID & Instance to support referenced components (lDBID2)
void CButtonCtl::ResolveUseDBValues()
{
   if (m_lDBID2 < BEM_COMP_MULT)
   {
      m_lUseDBID       = m_lDBID      ;
      m_iUseDBInstance = m_iDBInstance;
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


////////////////////////////////////////////////////////////////

BOOL CButtonCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits, long lDBIDOffset,
                         BOOL bTabbedDlgShift, BOOL calledNew, BOOL scaleToSysFont, BOOL scaleToScreenRes,
                         UINT uiTopicHelp, UINT uiItemHelp )
{
   ASSERT( pControl );

   DWORD winStyle = 0;
// SAC - 1/21/98 - removed SW_CLIPSIBLINGS from styles in order to get buttons to display
//                 on the Win95 tabbed dialogs.
   if (pControl->m_uiCtrlType == TDCT_Button)
// SAC - 8/25/98
//      winStyle = BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP;  //|WS_CLIPSIBLINGS;
      winStyle = BS_PUSHBUTTON|WS_CHILD|WS_TABSTOP;  //|WS_CLIPSIBLINGS;
   else if (pControl->m_uiCtrlType == TDCT_Check)
//      winStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTOCHECKBOX;  //|WS_CLIPSIBLINGS;
      winStyle = WS_CHILD|WS_TABSTOP|BS_AUTOCHECKBOX;  //|WS_CLIPSIBLINGS;
   else if (pControl->m_uiCtrlType == TDCT_RadioG)
//      winStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTORADIOBUTTON|WS_GROUP;  //|WS_CLIPSIBLINGS;
      winStyle = WS_CHILD|WS_TABSTOP|BS_AUTORADIOBUTTON|WS_GROUP;  //|WS_CLIPSIBLINGS;
   else if (pControl->m_uiCtrlType == TDCT_Radio)
//      winStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTORADIOBUTTON;  //|WS_CLIPSIBLINGS;
      winStyle = WS_CHILD|WS_TABSTOP|BS_AUTORADIOBUTTON;  //|WS_CLIPSIBLINGS;

   double xScale = (scaleToScreenRes ? appXRatio : 1.0);
   double yScale = (scaleToScreenRes ? appYRatio : 1.0);
   CSize size( (int) (((double) pControl->m_iWidth ) * xScale),
               (int) (((double) pControl->m_iHeight) * yScale) );
   CPoint pos( (int) (((double) pControl->m_iX     ) * xScale),
               (int) (((double) pControl->m_iY     ) * yScale) );
   if (scaleToSysFont)
   {
      size.cx = FontX( size.cx );
      size.cy = FontY( size.cy );
      pos.x   = FontX( pos.x );
      pos.y   = FontY( pos.y );
   }

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

   BOOL retVal = CButton::Create( pControl->m_sLbl, winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
// SAC 8/4/02 - Moved setting of m_lDBID & m_iDBInstance up here from below, added setting of m_lDBID2 and func call to resolve these to UseDB* values
      m_lDBID          = pControl->m_lDBID + lDBIDOffset;
      m_iDBInstance    = pControl->m_iDBInstance;  // SAC 3/3/99
      m_lDBID2         = pControl->m_lDBID2;
      ResolveUseDBValues();

      m_uiCtrlType   = pControl->m_uiCtrlType;
      m_iFont        = pControl->m_iFont;
//      m_lDBID        = pControl->m_lDBID + lDBIDOffset;
//      m_iDBInstance  = pControl->m_iDBInstance;
      m_iDataType    = BEMPX_GetDataType( m_lUseDBID );
      m_lNavOrVal    = pControl->m_lValue;
      m_wSecNavID    = (WORD) pControl->m_iLblDX;  // SAC 6/22/00 - added to enable more flexible pushbutton processing
      m_sStatusMsg   = pControl->m_sStatusMsg;

      m_bPressed   = FALSE;
      m_bCalledNew = calledNew;
      m_bCreatedByClassName = FALSE;

      m_bScaleFontToScreenRes = scaleToScreenRes;

      m_iItemHelpID  = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lUseDBID ) : uiItemHelp);
      m_iTopicHelpID = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lUseDBID ) : uiTopicHelp);

      m_cEditableCondition = pControl->m_cEditableCondition;
      m_bEditable = (BEMPX_GetCompIsEditable( m_lUseDBID ) && m_cEditableCondition.MissingOrTrue());
      m_bAllowEdits = bAllowEdits;

      m_bUpdatingData = FALSE;  // SAC 2/5/99

      m_iActionCode = BAC_None;  // SAC 6/13/00
      if (BEMPX_GetClassID( m_lUseDBID ) > 0  &&  BEMPX_GetPropertyID( m_lUseDBID ) == 0)
      {
         int iArrIdx = BEMPX_GetArrayID( m_lUseDBID );
         if (iArrIdx == BEM_PARAM0_CREATE)
            m_iActionCode = BAC_CreateComponent;
         else if (iArrIdx == BEM_PARAM0_DELETE)
            m_iActionCode = BAC_DeleteComponent;
      }

      SetFont( GetWizFont(m_iFont), TRUE );

// SAC - 8/25/98
//      if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//           (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
//         SetInitialState();
   }
   return retVal;
}

BOOL CButtonCtl::Create( const char FAR* lpCaption, DWORD dwStyle, const RECT& rect,
                          CWnd* pParentWnd, UINT nID, UINT uiCtrlType, int iFont,
                          const char FAR* lpMsg, long lDBID, BOOL calledNew, 
                          BOOL scaleToSysFont, BOOL scaleToScreenRes, long lNavOrVal, int iDBInstance ) 
{
   double xScale = (scaleToScreenRes ? appXRatio : 1.0);
   double yScale = (scaleToScreenRes ? appYRatio : 1.0);
   CSize size( (int) (((double) rect.right-rect.left) * xScale),
               (int) (((double) rect.bottom-rect.top) * yScale) );
   CPoint pos( (int) (((double) rect.left           ) * xScale),
               (int) (((double) rect.top            ) * yScale) );
   if (scaleToSysFont)
   {
      size.cx = FontX( size.cx );
      size.cy = FontY( size.cy );
      pos.x   = FontX( pos.x );
      pos.y   = FontY( pos.y );
   }

   BOOL temp = CButton::Create( lpCaption, dwStyle, CRect(pos, size), pParentWnd, nID );
   if (temp)
   {
      m_uiCtrlType   = uiCtrlType;
      m_iFont        = iFont;
      m_lDBID        = lDBID;
      m_iDBInstance  = iDBInstance;

      m_lDBID2         = 0;  // SAC 8/4/02
      ResolveUseDBValues();

      m_iDataType    = BEMPX_GetDataType( m_lUseDBID );
      m_lNavOrVal    = lNavOrVal;             // Add to Create() parameters for full implementation
      m_wSecNavID    = 0;  // SAC 6/22/00 - added to enable more flexible pushbutton processing
      m_sStatusMsg   = lpMsg;

      m_bPressed   = FALSE;
      m_bCalledNew = calledNew;
      m_bCreatedByClassName = FALSE;

      m_bScaleFontToScreenRes = FALSE;

      m_iItemHelpID  = BEMPX_GetItemHelpID(  m_lUseDBID );
      m_iTopicHelpID = BEMPX_GetTopicHelpID( m_lUseDBID );

      m_bEditable = BEMPX_GetCompIsEditable( m_lUseDBID );
      m_bAllowEdits = TRUE;

      m_bUpdatingData = FALSE;  // SAC 2/5/99

      m_iActionCode = BAC_None;  // SAC 6/13/00
      if (BEMPX_GetClassID( m_lUseDBID ) > 0  &&  BEMPX_GetPropertyID( m_lUseDBID ) == 0)
      {
         int iArrIdx = BEMPX_GetArrayID( m_lUseDBID );
         if (iArrIdx == BEM_PARAM0_CREATE)
            m_iActionCode = BAC_CreateComponent;
         else if (iArrIdx == BEM_PARAM0_DELETE)
            m_iActionCode = BAC_DeleteComponent;
      }

      SetFont( GetWizFont(m_iFont), TRUE );

// SAC - 8/25/98
//      if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//           (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
//         SetInitialState();
   }

   return temp;
}


int CButtonCtl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   int temp = CButton::OnCreate( lpCreateStruct );

   if (temp == 0)
   {
      m_uiCtrlType   = TDCT_Button;
      m_iDataType    = 0;
      m_iFont        = FNT_STD;
      m_lDBID        =  0;
      m_iDBInstance  = -1;

      m_lDBID2         =  0;  // SAC 8/4/02
      m_lUseDBID       =  0;
      m_iUseDBInstance = -1;

      m_lNavOrVal    = -1;
      m_wSecNavID    =  0;  // SAC 6/22/00 - added to enable more flexible pushbutton processing

      m_bPressed = FALSE;
      m_bCalledNew = FALSE;

      m_bEditable = TRUE;
      m_bAllowEdits = TRUE;

      m_bUpdatingData = FALSE;  // SAC 2/5/99

      SetFont( GetWizFont(m_iFont), TRUE );
   }

   return temp;
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl Class Registration Stuff

void CButtonCtl::SetInitialState()
{
   int i1Class = BEMPX_GetClassID( m_lUseDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iUseDBInstance );
   if ( m_lUseDBID > 0 && m_iDataType >= 0 && eObjType != BEMO_NumTypes &&
        BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
   {
      int iError, iSpecialVal;

      int iStatus = BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
      if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
      {
         if (m_iDataType == BEMP_Int || m_iDataType == BEMP_Sym)
         {
				long lNewVal = BEMPX_GetInteger( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );
				if (iError >= 0)
				{
               // DEAL WITH SPECIALVAL ??

               if (GetButtonStyle() == BS_AUTORADIOBUTTON)  // Plus check datatype??
//               {
//                  if (lNewVal == m_lNavOrVal)
//                     SetCheck( 1 );
                  SetCheck( (lNewVal == m_lNavOrVal) );
//               }
               else if (GetButtonStyle() == BS_AUTOCHECKBOX)  // Plus check datatype??
                  SetCheck( (lNewVal ? 1 : 0) );
            }
         }   
      }
      // SAC 3/18/99 - added to reset button to not checked if data status = undefined
      else if ( iStatus == BEMS_Undefined &&
                (GetButtonStyle() == BS_AUTORADIOBUTTON || GetButtonStyle() == BS_AUTOCHECKBOX) )
         SetCheck( 0 );
   }   
}


LONG CButtonCtl::OnDisplayData(UINT, LONG)
{
   ResolveUseDBValues();  // SAC 8/4/02 - reset UseDB* values upon each display in case referenced component has changed

   BOOL bLastEditable = m_bEditable;
   m_bEditable = (BEMPX_GetCompIsEditable( m_lUseDBID ) && m_cEditableCondition.MissingOrTrue());
// SAC 2/5/99
//   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
   if (GetButtonStyle() == BS_AUTORADIOBUTTON ||
       (GetButtonStyle() == BS_AUTOCHECKBOX && !m_bUpdatingData))
      SetInitialState();
// SAC 2/25/02 - Added code to use m_lUseDBID to label push button controls
   else if ( (GetButtonStyle() == BS_PUSHBUTTON || GetButtonStyle() == BS_DEFPUSHBUTTON)  &&
             m_lUseDBID > 0  &&  m_iActionCode == BAC_None  &&  m_lNavOrVal != 999)		// SAC 10/29/14 - added condition that nav ID != 999 - reserved for nav to objects referenced by active object
   {
      CString sBtnLbl;
      if (BEMPX_SetDataString( m_lUseDBID, sBtnLbl )  &&  !sBtnLbl.IsEmpty())
         SetWindowText( sBtnLbl );
   }
// SAC 3/5/02 - Added code to disable push buttons based on m_cEditableCondition
   if (GetButtonStyle() == BS_PUSHBUTTON || GetButtonStyle() == BS_DEFPUSHBUTTON)		// SAC 10/29/14 - switched from 'else if' to 'if' so that it is executed even if preceding 'if' is processed
   {
      BOOL bActive = m_cEditableCondition.MissingOrTrue();
      if ( ( bActive && !IsWindowEnabled()) ||
           (!bActive &&  IsWindowEnabled()) )
         EnableWindow( bActive );
   }

   if (bLastEditable != m_bEditable && IsWindowVisible())
      RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
      // ShowWindow( SW_SHOW );

   return 1;
}


BOOL CButtonCtl::ButtonSelected()
{
   BOOL bRetVal = TRUE;
   //int   dataUpdated = FALSE;
   //BOOL  bSendUpdateData = FALSE;
   int   iSetDataRetVal = -1; 
   int   iDataType = m_iDataType;

   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX) )
   {
      if (!m_bEditable)
      {
         MessageBeep( MB_OK );
         MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
         bRetVal = FALSE;
      }
      else if (!m_bAllowEdits)
      {
         MessageBeep( MB_OK );
         MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
         bRetVal = FALSE;
      }
//      else if (eiCurAnalysisStep != AS_None)
//      {
//         MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
//         bRetVal = FALSE;
//      }
      else if (ObjectIsFromLibrary( m_lUseDBID, m_iUseDBInstance ))
      {
         bRetVal = FALSE;
      }
      else
      {
         if (GetButtonStyle() == BS_AUTORADIOBUTTON)  // Plus check datatype??
         {
            if (m_iUseDBInstance >= 0)
               BEMPX_SetActiveObjectIndex( BEMPX_GetClassID( m_lUseDBID ), m_iUseDBInstance );

            iSetDataRetVal = BEMPX_SetBEMData( m_lUseDBID, iDataType, (void*)&m_lNavOrVal );
         }
         else if (GetButtonStyle() == BS_AUTOCHECKBOX)  // Plus check datatype??
         {
            if (m_iUseDBInstance >= 0)
               BEMPX_SetActiveObjectIndex( BEMPX_GetClassID( m_lUseDBID ), m_iUseDBInstance );

            long newVal = (GetCheck() == 0) ? TRUE : FALSE;
            iSetDataRetVal = BEMPX_SetBEMData( m_lUseDBID, iDataType, (void*)&newVal );
         }

         if (iSetDataRetVal >= 0)
         {
            // Post-processing following mods
            m_bUpdatingData = TRUE;  // SAC 2/5/99
            GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );
            m_bUpdatingData = FALSE;  // SAC 2/5/99
// SAC 1/27/99 - Replaced w/ above
////            SetDataModifiedFlag( TRUE );
//
//            // execute compliance rulelist #1
////            GetParentFrame()->SendMessage( WM_EVALPROPOSED );
//            GetParent()->SendMessage( WM_EVALPROPOSED );
//
//            // redisplay all currently displayed database data
//            GetParent()->PostMessage( WM_DISPLAYMODS );

            // redisplay status bar strings
            CFrameWnd* pFrame = GetParentFrame();
            if (pFrame)
               pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//            GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lUseDBID);
         }
      }
   }
   return bRetVal;
}


void CButtonCtl::CreateComponent()  // SAC 6/13/00
{
   // Present Create Component dialog box
   CBEMProcDlgCreate cr8Dlg( BEMPX_GetClassID( m_lUseDBID ), 0, 0, /*this*/ GetParent(), SWDM_Default );
   if (cr8Dlg.DoModal() == IDOK  &&  cr8Dlg.m_pNewObj != NULL)
   {
      // Post-processing following mods
      GetParent()->SendMessage( WM_DATAMODIFIED, 1 );
   }
}


static char BASED_CODE szDelStd1[] = "The building component being deleted ";
static char BASED_CODE szDelRef1[] = "is referenced ";
static char BASED_CODE szDelRef2[] = " times by other";
static char BASED_CODE szDelChl1[] = "has ";
static char BASED_CODE szDelChl2[] = " child";
static char BASED_CODE szDelChl3[] = " component(s) and has ";
static char BASED_CODE szDelStd2[] = " component(s).  If this component is deleted, then all ";
static char BASED_CODE szDelChl4[] = "its children will also be deleted and all references to the ";
static char BASED_CODE szDelChl5[] = "component being deleted or any of its children";
static char BASED_CODE szDelRef3[] = " references to it";
static char BASED_CODE szDelStd3[] = " will be reinitialized.  ";
static char BASED_CODE szDelStd4[] = "Are you sure you want to delete the ";

void CButtonCtl::DeleteComponent() 
{
   int iError;
   BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( m_lUseDBID ), iError );
   if (pObj)
   {
      int iNumObjRefs  = BEMPX_CountOrResetObjectRefs( pObj, TRUE );
      int iNumChildren = pObj->getChildCount();

      // Assemble component deletion confirmation message
      CString sMsg;
      if ( (iNumObjRefs > 0) || (iNumChildren > 0) )
      {
         CString sTemp;
         sMsg = szDelStd1;
         if (iNumObjRefs > 0)
         {
            sMsg += szDelRef1;
            sTemp.Format( "%d", iNumObjRefs );
            sMsg += sTemp;
            sMsg += szDelRef2;
         }

         if (iNumChildren > 0)
         {
            if (iNumObjRefs > 0)
               sMsg += szDelChl3;
            else
               sMsg += szDelChl1;
            sTemp.Format( "%d", iNumChildren );
            sMsg += sTemp;
            sMsg += szDelChl2;
         }

         sMsg += szDelStd2;

         if (iNumChildren > 0)
         {
            sMsg += szDelChl4;
            sMsg += szDelChl5;
         }
         else  // refs only
            sMsg += szDelRef3;

         sMsg += szDelStd3;
      }

      sMsg += szDelStd4;
      int iClass = 0;
      if (pObj->getClass() != NULL)
      {
         sMsg += pObj->getClass()->getLongName().toLatin1().constData();
         iClass = pObj->getClass()->get1BEMClassIdx();
      }
      else
         sMsg += "building component";

      if (pObj->getName().length() > 0)
      {
         sMsg += " '";
         sMsg += pObj->getName().toLatin1().constData();
         sMsg += "'";
      }
      sMsg += "?";

      if (GetParent()->MessageBox( sMsg, "Delete Building Component",
                                   MB_ICONSTOP | MB_YESNO | MB_DEFBUTTON2 ) == IDYES)
      {
         BEMPX_DeleteObject( pObj );

         // Post-processing following mods
         GetParent()->SendMessage( WM_DATAMODIFIED, 1 );
      }
   }
}


void CButtonCtl::PostNcDestroy()
{
    if ( (m_bCreatedByClassName) || (m_bCalledNew) )
        delete this;
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl - Grey out control background when the data is not editable

HBRUSH CButtonCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
	// TODO: Change any attributes of the DC here
   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON ||
         GetButtonStyle() == BS_AUTOCHECKBOX   ) && !m_bEditable )
      pDC->SetTextColor( ::GetSysColor( COLOR_GRAYTEXT ) );
   else
      pDC->SetTextColor( ::GetSysColor( COLOR_BTNTEXT ) );
//      pDC->SetTextColor( GetBEMPUITextColor( BEMS_Undefined ) );
//   else
//      pDC->SetTextColor( GetBEMPUITextColor( BEMPX_GetDataStatus( m_lUseDBID ) ) );

	// TODO: Return a non-NULL brush if the parent's handler should not be called
   pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
	return buttonBrush;
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl diagnostics

#ifdef _DEBUG
void CButtonCtl::AssertValid() const
{
    CButton::AssertValid();
}

void CButtonCtl::Dump(CDumpContext& dc) const
{
    CButton::Dump(dc);
}

#endif //_DEBUG


void CButtonCtl::ResetFocus( BOOL prev )
{
   CWnd* pFocus = GetParent()->GetNextDlgTabItem( this, prev );
   if (pFocus != NULL)
      pFocus->SetFocus();
}

UINT CButtonCtl::OnGetDlgCode()
{
   UINT retVal = DLGC_WANTMESSAGE;
   if (GetButtonStyle() == BS_AUTORADIOBUTTON)
      retVal = DLGC_RADIOBUTTON;
   else if (GetButtonStyle() == BS_AUTOCHECKBOX)
      retVal = DLGC_BUTTON;
   return retVal;
}

void CButtonCtl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   //CWnd* pPar = GetParent();
   if (nChar == VK_TAB)
      ResetFocus( (GetKeyState(VK_SHIFT) < 0) );
   else if ( (nChar == VK_LEFT) || (nChar == VK_UP) )
      ResetFocus( TRUE );
   else if ( (nChar == VK_RIGHT) || (nChar == VK_DOWN) )
      ResetFocus( FALSE );
   else if ( !m_bEditable && nChar == VK_SPACE &&
             ( GetButtonStyle() == BS_AUTORADIOBUTTON ||
               GetButtonStyle() == BS_AUTOCHECKBOX    ) )
   {
      MessageBeep( MB_OK );
      MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
   }
   else if ( !m_bAllowEdits && nChar == VK_SPACE &&
             ( GetButtonStyle() == BS_AUTORADIOBUTTON ||
               GetButtonStyle() == BS_AUTOCHECKBOX    ) )
   {
      MessageBeep( MB_OK );
      MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
   }
//   else if ( (nChar == VK_SPACE) &&
//             ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//               (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) &&
//             (eiCurAnalysisStep != AS_None) )
//      MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
   else
      CButton::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CButtonCtl::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   CWnd* pPar = GetParent();
   if ( (nChar == VK_SPACE) &&
        ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
          (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) )
   {
      // Update data
// SAC 6/17/01 - Modified to call base class OnKeyUp() even when ButtonSelected() returns FALSE
      BOOL bSelectionOK = ButtonSelected();
      CButton::OnKeyUp( nChar, nRepCnt, nFlags );
      if (!bSelectionOK)
         OnDisplayData(0,0);
   }
// SAC 6/13/00
   else if (nChar == VK_SPACE  &&  m_iActionCode == BAC_CreateComponent)
      CreateComponent();
   else if (nChar == VK_SPACE  &&  m_iActionCode == BAC_DeleteComponent)
      DeleteComponent();
//SAC 2/25/99
   else if (nChar == VK_SPACE  &&  m_lNavOrVal > 0)
   {
// SAC 6/27/01 - added call to pass message on to base class so that button can be returned to its default state
      CButton::OnKeyUp( nChar, nRepCnt, nFlags );

//      GetParentFrame()->PostMessage( WM_BUTTONPRESSED, m_lNavOrVal, (long) pPar );
// SAC 6/22/00 - replaced above w/ below to enable more flexible pushbutton processing
//      GetParentFrame()->PostMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lNavOrVal, m_wSecNavID ), (long) pPar );
// SAC 6/27/01 - revised button press message to return value indicating whether or not data was changed
      int iBtnPressRetVal = GetParentFrame()->SendMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lNavOrVal, m_wSecNavID ), (long) pPar );
      if (iBtnPressRetVal > 0)
      {
         // Post-processing following mods
         m_bUpdatingData = TRUE;  // SAC 2/5/99
         GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );
         m_bUpdatingData = FALSE;  // SAC 2/5/99
      }
   }
   else
      CButton::OnKeyUp( nChar, nRepCnt, nFlags );
}



void CButtonCtl::OnKillFocus( CWnd* pNewWnd )
{
   if (GetButtonStyle() == BS_DEFPUSHBUTTON)
   {
      SetButtonStyle( BS_PUSHBUTTON, FALSE );
      SetFont( GetWizFont(m_iFont), TRUE );
   }
   
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, NULL, 0 );
//   GetMainFrame()->SetStatusBarStrings("", 0);
   
   CButton::OnKillFocus( pNewWnd );
}


void CButtonCtl::OnSetFocus( CWnd* pOldWnd )
{
   if ( (GetButtonStyle() != BS_AUTORADIOBUTTON) &&
        (GetButtonStyle() != BS_AUTOCHECKBOX   ) )
   {
      SetButtonStyle( BS_DEFPUSHBUTTON, FALSE );
      SetFont( GetWizFont(m_iFont), TRUE );
   }
      
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//   GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lUseDBID);
   
   CButton::OnSetFocus( pOldWnd );
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl - Display & Update Data Stuff

LONG CButtonCtl::OnGetDBID(UINT, LONG)
{
   return m_lUseDBID;
}

LONG CButtonCtl::OnGetDBInstance(UINT, LONG)
{
   return m_iUseDBInstance;
}


//////////////////////////////////////////
// Mouse Click Navigation
//////////////////////////////////////////

void CButtonCtl::OnLButtonDown( UINT nFlags, CPoint point )
{
   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
		m_bPressed = TRUE;		// SAC 12/17/14 - prevent processing ButtonUp when ButtonDown not first pressed
   CButton::OnLButtonDown( nFlags, point );
}

void CButtonCtl::OnLButtonUp( UINT nFlags, CPoint point )
{
   CWnd* pPar = GetParent();
   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
   {
//      if (ButtonSelected())
//         CButton::OnLButtonUp( nFlags, point );
// SAC 6/17/01 - Modified to call base class OnKeyUp() even when ButtonSelected() returns FALSE
      BOOL bSelectionOK = (m_bPressed ? ButtonSelected() : FALSE);		// SAC 12/17/14 - prevent processing ButtonUp when ButtonDown not first pressed
      CButton::OnLButtonUp( nFlags, point );
      if (!bSelectionOK)
         OnDisplayData(0,0);
		m_bPressed = FALSE;		// SAC 12/17/14
   }
// SAC 6/13/00
   else if (m_iActionCode == BAC_CreateComponent)
      CreateComponent();
   else if (m_iActionCode == BAC_DeleteComponent)
      DeleteComponent();
//SAC 2/25/99
   else if (m_lNavOrVal > 0)
   {
// SAC 6/27/01 - added call to pass message on to base class so that button can be returned to its default state
      CButton::OnLButtonUp( nFlags, point );

//      GetParentFrame()->PostMessage( WM_BUTTONPRESSED, m_lNavOrVal, (long) pPar );
// SAC 6/22/00 - replaced above w/ below to enable more flexible pushbutton processing
//      GetParentFrame()->PostMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lNavOrVal, m_wSecNavID ), (long) pPar );
// SAC 6/27/01 - revised button press message to return value indicating whether or not data was changed
      int iBtnPressRetVal = GetParentFrame()->SendMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lNavOrVal, m_wSecNavID ), (long) pPar );
      if (iBtnPressRetVal > 0)
      {
         // Post-processing following mods
         m_bUpdatingData = TRUE;  // SAC 2/5/99
         GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );
         m_bUpdatingData = FALSE;  // SAC 2/5/99
      }
   }
   else
      CButton::OnLButtonUp( nFlags, point );
}


//////////////////////////////////////////
// Quick Menu Stuff
//////////////////////////////////////////

void CButtonCtl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      DoQuickMenu();
   else
      CButton::OnSysChar(nChar, nRepCnt, nFlags);
}


void CButtonCtl::OnRButtonDown( UINT /*nFlags*/, CPoint /*point*/ )
{
   SetFocus();
   if (GetButtonStyle() == BS_PUSHBUTTON)
   {
      SetButtonStyle( BS_DEFPUSHBUTTON, FALSE );
      SetFont( GetWizFont(m_iFont), TRUE );
   }

   DoQuickMenu();
}


// Process Quick Menu
void CButtonCtl::DoQuickMenu()
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
//   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
//   {
//      int iStatus = BEMPX_GetDataStatus( m_lUseDBID );
//      int iPropID = BEMPX_GetPropertyID( m_lUseDBID );
//      if ( (iStatus == BEMS_UserDefined) && (iPropID > 0) )
//         uiQuickMask |= QMI_DEFAULT;
//   }
//
//   CRect winRect;
//   GetWindowRect( winRect );
//   GetMainFrame()->DoQuickMenu( winRect.left, winRect.right, winRect.top, uiQuickMask,
//                                m_iItemHelpID, m_iTopicHelpID, m_lUseDBID );
}


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CButtonCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CButton::OnHelpInfo(pHelpInfo);
}

