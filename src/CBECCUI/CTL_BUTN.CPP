// CTL_BUTN.CPP  :  Contains CButtonCtl routines
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
#include "mainfrm.h"
#include "ctl_butn.h" 
//16 #include "quick.h" 
#include "ComplianceUIDoc.h"
#include "..\BEMProcUI\BEMProcUIX.h"

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
//	ON_WM_CTLCOLOR_REFLECT()

   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_WM_SYSKEYDOWN()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_RBUTTONDOWN()
   ON_WM_KILLFOCUS()
   ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BOOL CButtonCtl::Create( const char FAR* lpCaption, DWORD dwStyle, const RECT& rect,
                          CWnd* pParentWnd, UINT nID, UINT uiCtrlType, int iFont,
                          const char FAR* lpMsg, long lDBID, BOOL calledNew, 
                          BOOL scaleToSysFont, BOOL scaleToScreenRes, long lNavOrVal ) 
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

//   // shift for Win95 tabbed dialog class
//   pos.x += eiTabDlgCtrlMarg;
//   pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;

   BOOL temp = CButton::Create( lpCaption, dwStyle, CRect(pos, size), pParentWnd, nID );
   if (temp)
   {
      m_uiCtrlType   = uiCtrlType;
      m_iFont        = iFont;
      m_lDBID        = lDBID;
      m_iDataType    = BEMPX_GetDataType( m_lDBID );
      m_lNavOrVal    = lNavOrVal;             // Add to Create() parameters for full implementation
      m_sStatusMsg   = lpMsg;

      m_bPressed   = FALSE;
      m_bCalledNew = calledNew;
      m_bCreatedByClassName = FALSE;

      m_bScaleFontToScreenRes = FALSE;

      m_iItemHelpID  = BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID = BEMPX_GetTopicHelpID( m_lDBID );

      m_bEditable = BEMPX_GetCompIsEditable( m_lDBID );

      SetFont( GetCUIFont(m_iFont), TRUE );

      if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
           (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
         SetInitialState();
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
      m_lNavOrVal    = -1;

      m_bPressed = FALSE;
      m_bCalledNew = FALSE;

      m_bEditable = TRUE;

      SetFont( GetCUIFont(m_iFont), TRUE );
   }

   return temp;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Grey out control background when the data is not editable

// SAC - 1/30/98 - Only affects the text background, not the background of the
//                 checkbox or radio button itself
//HBRUSH CButtonCtl::CtlColor(CDC* pDC, UINT nCtlColor) 
//{
//	// TODO: Change any attributes of the DC here
//	if ( ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
//          (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) &&
//	     (!m_bEditable) )
//   {
//      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
//      return buttonBrush;
////      pDC->SetBkColor( RGB(192,192,192) );
////      return greyBrush;
//   }
//	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	return NULL;
//}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl Class Registration Stuff

void CButtonCtl::SetInitialState()
{
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class );
   if ( (m_lDBID > 0) && (m_iDataType >= 0) &&
        (eObjType != BEMO_NumTypes) &&
        (BEMPX_GetNumObjects( i1Class, eObjType ) > 0) )
   {
      int iError, iSpecialVal;
      int iStatus = BEMPX_GetDataStatus( m_lDBID );
      if ( (iStatus > BEMS_Undefined) && (iStatus < BEMS_NumTypes) )
      {
         if ( (m_iDataType == BEMP_Int) || (m_iDataType == BEMP_Sym) )
         {
            long lNewVal = BEMPX_GetInteger( m_lDBID, iSpecialVal, iError );
            if (iError >= 0)
            {
               // DEAL WITH SPECIALVAL ??

               if (GetButtonStyle() == BS_AUTORADIOBUTTON)  // Plus check datatype??
               {
                  if ( (lNewVal) ==  m_lNavOrVal)
                     SetCheck( 1 );
               }
               else if (GetButtonStyle() == BS_AUTOCHECKBOX)  // Plus check datatype??
               {
                  if (lNewVal)
                     SetCheck( 1 );
               }
            }
         }   
      }
   }   
}


BOOL CButtonCtl::ButtonSelected()
{
   BOOL bRetVal = TRUE;
   int   iSetDataRetVal = -1; 
   int   iDataType = m_iDataType;

   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX) )
   {
      if (!m_bEditable)
      {
         MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
//         ::MessageBox( NULL, szErrNotEditable, szErrorCaption, MB_ICONSTOP );
         bRetVal = FALSE;
      }
      else if (eInterfaceMode != IM_INPUT)
      {
         MessageBox( szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
//         ::MessageBox( NULL, szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
         bRetVal = FALSE;
      }
      else if (eiCurAnalysisStep != AS_None)
      {
         MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
//         ::MessageBox( NULL, szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
         bRetVal = FALSE;
      }
      else if (ObjectIsFromLibrary( m_lDBID ))
      {
         bRetVal = FALSE;
      }
      else
      {
         if (GetButtonStyle() == BS_AUTORADIOBUTTON)  // Plus check datatype??
         {
            iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*)&m_lNavOrVal );
         }
         else if (GetButtonStyle() == BS_AUTOCHECKBOX)  // Plus check datatype??
         {
            long newVal = (GetCheck() == 0) ? TRUE : FALSE;
            iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*)&newVal );
         }

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
	//            GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);
         }
      }
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl Class Registration Stuff

//32// Define statics
//32WNDPROC CButtonCtl::pfnSuperWndProc = NULL ;
//32
//32
//32LONG CALLBACK __export
//32CButtonCtl::FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
//32{
//32    //
//32    // Construct the object and then attach the hWnd to it.
//32    //
//32    CButtonCtl* pNumEdit = new CButtonCtl;
//32    pNumEdit->Attach(hWnd);
//32
//32    pNumEdit->m_bCreatedByClassName = TRUE;
//32
//32    //
//32    // Subclass the window by changing the window procedure to AfxWndProc
//32    // and pass the current message to it.
//32    //
//32    ::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);
//32
//32#ifdef STRICT
//32    return ::CallWindowProc((WNDPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//32#else
//32    return ::CallWindowProc((FARPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//32#endif
//32    //DER
//32}
//32
//32
//32BOOL CButtonCtl::RegisterMyClass()
//32{
//32    WNDCLASS wcls;
//32
//32    if(!::GetClassInfo(NULL, "button", &wcls) )
//32    {
//32        return FALSE;
//32    }
//32
//32    if (pfnSuperWndProc == NULL) 
//32        pfnSuperWndProc = wcls.lpfnWndProc;
//32
//32    ASSERT( pfnSuperWndProc == wcls.lpfnWndProc);
//32
//32    static const char szClassName[] = "rerbutton";
//32    if(::GetClassInfo(AfxGetInstanceHandle(), szClassName, &wcls))
//32    {
//32        return (wcls.lpfnWndProc == CButtonCtl::FirstMsgOnlyWndProc);
//32    }
//32
//32    wcls.lpfnWndProc = CButtonCtl::FirstMsgOnlyWndProc;
//32    wcls.hInstance = AfxGetInstanceHandle();
//32    wcls.lpszClassName = szClassName;
//32
//32    return (RegisterClass(&wcls) !=0);
//32}


void CButtonCtl::PostNcDestroy()
{
    if ( (m_bCreatedByClassName) || (m_bCalledNew) )
        delete this;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

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
   else if ( (nChar == VK_SPACE) &&
             ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
               (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) &&
             (!m_bEditable) )
      ::MessageBox( NULL, szErrNotEditable, szErrorCaption, MB_ICONSTOP );
   else if ( (nChar == VK_SPACE) &&
             ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
               (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) &&
             (eInterfaceMode != IM_INPUT) )
      ::MessageBox( NULL, szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
   else if ( (nChar == VK_SPACE) &&
             ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
               (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) &&
             (eiCurAnalysisStep != AS_None) )
      ::MessageBox( NULL, szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
   else
      CButton::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CButtonCtl::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   //CWnd* pPar = GetParent();
   if ( (nChar == VK_SPACE) &&
        ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
          (GetButtonStyle() == BS_AUTOCHECKBOX   ) ) )
   {
      ////////////////////////////////////////////////////
      // Update PowerDOE/BDL data
      ////////////////////////////////////////////////////
      if (ButtonSelected())
         CButton::OnKeyUp( nChar, nRepCnt, nFlags );
   }
   else
      CButton::OnKeyUp( nChar, nRepCnt, nFlags );
}



void CButtonCtl::OnKillFocus( CWnd* pNewWnd )
{
   if (GetButtonStyle() == BS_DEFPUSHBUTTON)
   {
      SetButtonStyle( BS_PUSHBUTTON, FALSE );
      SetFont( GetCUIFont(m_iFont), TRUE );
   }
   
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings("", 0);
   
   CButton::OnKillFocus( pNewWnd );
}


void CButtonCtl::OnSetFocus( CWnd* pOldWnd )
{
   if ( (GetButtonStyle() != BS_AUTORADIOBUTTON) &&
        (GetButtonStyle() != BS_AUTOCHECKBOX   ) )
   {
      SetButtonStyle( BS_DEFPUSHBUTTON, FALSE );
      SetFont( GetCUIFont(m_iFont), TRUE );
   }
      
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);
   
   CButton::OnSetFocus( pOldWnd );
}


/////////////////////////////////////////////////////////////////////////////
// CButtonCtl - Display & Update Data Stuff

LONG CButtonCtl::OnGetDBID(UINT, LONG)
{
   return m_lDBID;
}

LONG CButtonCtl::OnGetDBInstance(UINT, LONG)
{
   return -1;
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
   //CWnd* pPar = GetParent();
   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
   {
//      if (ButtonSelected())
//         CButton::OnLButtonUp( nFlags, point );
   //   BOOL bSelectionOK = (m_bPressed ? ButtonSelected() : FALSE);		// SAC 12/17/14 - prevent processing ButtonUp when ButtonDown not first pressed
      if (m_bPressed)		// SAC 12/17/14 - prevent processing ButtonUp when ButtonDown not first pressed
      	ButtonSelected();
      CButton::OnLButtonUp( nFlags, point );
      //if (!bSelectionOK)
      //   OnDisplayData(0,0);
		m_bPressed = FALSE;		// SAC 12/17/14
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
      SetFont( GetCUIFont(m_iFont), TRUE );
   }

   DoQuickMenu();
}


// Process Quick Menu
void CButtonCtl::DoQuickMenu()
{
   UINT uiQuickMask = QMI_ITEMHELP | QMI_TOPICHELP;
   if ( (GetButtonStyle() == BS_AUTORADIOBUTTON) ||
        (GetButtonStyle() == BS_AUTOCHECKBOX   ) )
   {
      int iStatus = BEMPX_GetDataStatus( m_lDBID );
      int iPropID = BEMPX_GetPropertyID( m_lDBID );
      if ( (iStatus == BEMS_UserDefined) && (iPropID > 0) )
         uiQuickMask |= QMI_DEFAULT;

//      int iError = 0;
//      int iCritDefIdx = BEMPX_GetCriticalDefaultIndex( m_lDBID, iError );
//      if ( (iError >= 0) && (iCritDefIdx > 0) )
//         uiQuickMask |= QMI_COMMENT;
   }

   CRect winRect;
   GetWindowRect( winRect );
   GetMainFrame()->DoQuickMenu( winRect.left, winRect.right, winRect.top, uiQuickMask,
                                m_iItemHelpID, m_iTopicHelpID, m_lDBID );
}

