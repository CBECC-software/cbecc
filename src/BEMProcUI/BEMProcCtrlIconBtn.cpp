// BEMProcCtrlIconBtn.cpp : implementation file
//
/**********************************************************************
 *  Copyright (c) 2012-2018, California Energy Commission
 *  Copyright (c) 2018, SAC Software Solutions, LLC
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

#include "stdafx.h"
#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "BEMProcCtrlIconBtn.h"
#include "BEMProcUIX.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDB_BPUI_DFLT_SM     328
#define IDB_BPUI_DFLT_SMG    329
#define IDB_BPUI_DFLT_LG     330
#define IDB_BPUI_DFLT_LGG    331


IMPLEMENT_DYNAMIC( CBEMProcCtrlIconBtn, CButtonST )

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlIconBtn

CBEMProcCtrlIconBtn::CBEMProcCtrlIconBtn()
{
   m_iIconID   = 0;
   m_lActionID = 0;
   m_wSecNavID = 0;

   m_bEditable = TRUE;  // SAC 3/2/06
}

CBEMProcCtrlIconBtn::~CBEMProcCtrlIconBtn()
{
}


BEGIN_MESSAGE_MAP(CBEMProcCtrlIconBtn, CButtonST)
	//{{AFX_MSG_MAP(CBEMProcCtrlIconBtn)
		// NOTE - the ClassWizard will add and remove mapping macros here.
   ON_WM_LBUTTONUP()
   ON_WM_KEYUP()
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlIconBtn message handlers

BOOL CBEMProcCtrlIconBtn::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bTabbedDlgShift, BOOL calledNew,
                             BOOL scaleToSysFont, BOOL scaleToScreenRes )
{
   ASSERT( pControl );
	return (pControl ? Create( pParentWnd, pControl->m_iX, pControl->m_iY, pControl->m_iHeight, pControl->m_iWidth, pControl->m_uiCtrlID, pControl->m_sStatusMsg,
										pControl->m_iUnitDX, pControl->m_lValue, (WORD) pControl->m_iLblDX, &pControl->m_cEditableCondition, (pControl->m_iUnitDY > 0),
										bTabbedDlgShift, calledNew, scaleToSysFont, scaleToScreenRes ) : FALSE);
}

BOOL CBEMProcCtrlIconBtn::Create( CWnd* pParentWnd, int iX, int iY, int iHeight, int iWidth, UINT uiCtrlID, const char* sStatusMsg,
												int iIconID, long lActionID, WORD wSecNavID, CBEMCondition* pEditableCondition, BOOL bDrawFlatFocus,
												BOOL bTabbedDlgShift, BOOL calledNew, BOOL scaleToSysFont, BOOL scaleToScreenRes )
{
   DWORD winStyle = WS_CHILD|WS_TABSTOP;

   double xScale = (scaleToScreenRes ? appXRatio : 1.0);
   double yScale = (scaleToScreenRes ? appYRatio : 1.0);
   CSize size( (int) (((double) iWidth ) * xScale),
               (int) (((double) iHeight) * yScale) );
   CPoint pos( (int) (((double) iX     ) * xScale),
               (int) (((double) iY     ) * yScale) );
   if (scaleToSysFont)
   {
      size.cx = FontX( size.cx );
      size.cy = FontY( size.cy );
      pos.x   = FontX( pos.x );
      pos.y   = FontY( pos.y );
   }

// CString sDbgMsg, sDbg2;
// sDbgMsg.Format( "CBEMProcCtrlIconBtn scaled position: %d, %d  -  and size: %d, %d\n", pos.x, pos.y, size.cx, size.cy );

   if (pos.x < 0)
   {  // for negative X positions - position control that far in from the right edge of the parent window
      if (pParentWnd)
      {  
         CRect rect;
	      pParentWnd->GetClientRect(&rect);

// sDbg2.Format( "Positioning in from right edge - parent (t%d, b%d, l%d, r%d) - %d in from right.", rect.top, rect.bottom, rect.left, rect.right, (-1*pos.x) );
// sDbgMsg += sDbg2;

         if (rect.right > (-1 * pos.x))
            pos.x = rect.right + pos.x;
      }
//       else
//       {
// sDbgMsg += "ERROR invalid parent window pointer";
//       }
   }

// AfxMessageBox( sDbgMsg );

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

//   BOOL retVal = CButtonST::Create( pControl->m_sLbl, winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   BOOL retVal = CButtonST::Create( "", winStyle, CRect(pos, size), pParentWnd, uiCtrlID );
   if (retVal)
   {
      m_sStatusMsg   = sStatusMsg;

      m_bCalledNew = calledNew;

      m_iIconID   = iIconID;
      m_lActionID = lActionID;
      m_wSecNavID = wSecNavID;

//      SetFont( GetWizFont(pControl->m_iFont), TRUE );

      if (pEditableCondition)
      {	m_cEditableCondition = *pEditableCondition;    // SAC 3/2/06
      	m_bEditable = m_cEditableCondition.MissingOrTrue();
      }
      else
      	m_bEditable = TRUE;

      int iBmpID = 0;
      switch (m_iIconID)
      {
         case 10 :  iBmpID = (FontY(20) > 22 ? IDB_BPUI_DFLT_LG : IDB_BPUI_DFLT_SM);   break;
         default :  ASSERT( FALSE );   break;
      }
      SetBitmaps( iBmpID, RGB(255,0,0), iBmpID+1, RGB(255,0,0) );
//      DWORD dwSBRetVal = SetBitmaps( iBmpID, RGB(255,0,0), iBmpID+1, RGB(255,0,0) );
//CString sDbgMsg;
//sDbgMsg.Format( "SetBitmaps( %d, -, %d, - ) returned %ld.", iBmpID, iBmpID+1, dwSBRetVal  );
//AfxMessageBox( sDbgMsg );

// SAC 1/3/04 - Test out effect of using focus rect
      if (bDrawFlatFocus)
         DrawFlatFocus( /*bDrawFlatFocus*/ TRUE, /*bRepaint*/ FALSE );

      SizeToContent();
      DrawBorder( FALSE );

      if (!m_sStatusMsg.IsEmpty())
         SetTooltipText( m_sStatusMsg );
   }
   return retVal;
}


void CBEMProcCtrlIconBtn::PostNcDestroy()
{
    if (m_bCalledNew)
        delete this;
}



void CBEMProcCtrlIconBtn::OnLButtonUp( UINT nFlags, CPoint point )
{
   //CWnd* pPar = GetParent();
   CButtonST::OnLButtonUp( nFlags, point );

   if (m_lActionID >= 0)
   {
      if (!m_bEditable)  // SAC 3/2/06
         MessageBeep( MB_OK );
      else
      {
         int iBtnPressRetVal = (int) GetParentFrame()->SendMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lActionID, m_wSecNavID ), (long) this );  // PtrToLong( pPar ) );
         if (iBtnPressRetVal > 0)   // SAC 3/3/06
            // Post-processing following button press
            GetParent()->PostMessage( WM_DATAMODIFIED, iBtnPressRetVal, 0 );
      }
   }
   else if (m_lActionID < -1)   // SAC 10/1/09 - new mechanism to facilitate BEMBase message boxes
      GetParent()->PostMessage( WM_BUTTONPRESSED, 0, -m_lActionID );
}

void CBEMProcCtrlIconBtn::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   //CWnd* pPar = GetParent();
   CButtonST::OnKeyUp( nChar, nRepCnt, nFlags );

   if (nChar == VK_SPACE  &&  m_lActionID >= 0)
   {
      if (!m_bEditable)  // SAC 3/2/06
         MessageBeep( MB_OK );
      else
      {
         int iBtnPressRetVal = (int) GetParentFrame()->SendMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_lActionID, m_wSecNavID ), (long) this );  // PtrToLong( pPar ) );
         if (iBtnPressRetVal > 0)   // SAC 3/3/06
            // Post-processing following button press
            GetParent()->PostMessage( WM_DATAMODIFIED, iBtnPressRetVal, 0 );
      }
   }
   else if (nChar == VK_SPACE  &&  m_lActionID < -1)   // SAC 10/1/09 - new mechanism to facilitate BEMBase message boxes
      GetParent()->PostMessage( WM_BUTTONPRESSED, 0, -m_lActionID );
}


LONG CBEMProcCtrlIconBtn::OnDisplayData(UINT, LONG)
{
   BOOL bLastEditable = m_bEditable;
   m_bEditable = m_cEditableCondition.MissingOrTrue();

//   if (GetButtonStyle() == BS_AUTORADIOBUTTON ||
//       (GetButtonStyle() == BS_AUTOCHECKBOX && !m_bUpdatingData))
//      SetInitialState();
//   else if ( (GetButtonStyle() == BS_PUSHBUTTON || GetButtonStyle() == BS_DEFPUSHBUTTON)  &&
//             m_lUseDBID > 0  &&  m_iActionCode == BAC_None)
//   {
//      CString sBtnLbl;
//      if (BDX_SetDataString( m_lUseDBID, sBtnLbl )  &&  !sBtnLbl.IsEmpty())
//         SetWindowText( sBtnLbl );
//   }

//   if (GetButtonStyle() == BS_PUSHBUTTON || GetButtonStyle() == BS_DEFPUSHBUTTON)
//   {
//      BOOL bActive = m_cEditableCondition.MissingOrTrue();
//      if ( ( bActive && !IsWindowEnabled()) ||
//           (!bActive &&  IsWindowEnabled()) )
//         EnableWindow( bActive );
      if ( ( m_bEditable && !IsWindowEnabled()) ||
           (!m_bEditable &&  IsWindowEnabled()) )
         EnableWindow( m_bEditable );
//   }

   if (bLastEditable != m_bEditable && IsWindowVisible())
      RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

   return 1;
}
