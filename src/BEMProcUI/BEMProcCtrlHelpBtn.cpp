// BEMProcCtrlHelpBtn.cpp : implementation file
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

#include "stdafx.h"
#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "BEMProcCtrlHelpBtn.h"
#include "BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define IDI_EQ_HELP32      574
// #define IDI_EQ_HELP32G     575
// #define IDI_EQ_HELP16      576
// #define IDI_EQ_HELP16G     577
#define IDB_EQ_HELP20      578
#define IDB_EQ_HELP20G     579
#define IDB_EQ_HELP24      590
#define IDB_EQ_HELP24G     591

IMPLEMENT_DYNAMIC( CBEMProcCtrlHelpBtn, CButtonST )

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlHelpBtn

CBEMProcCtrlHelpBtn::CBEMProcCtrlHelpBtn()
{
}

CBEMProcCtrlHelpBtn::~CBEMProcCtrlHelpBtn()
{
}


BEGIN_MESSAGE_MAP(CBEMProcCtrlHelpBtn, CButtonST)
	//{{AFX_MSG_MAP(CBEMProcCtrlHelpBtn)
		// NOTE - the ClassWizard will add and remove mapping macros here.
   ON_WM_LBUTTONUP()
   ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlHelpBtn message handlers


BOOL CBEMProcCtrlHelpBtn::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bTabbedDlgShift, BOOL calledNew,
                              BOOL scaleToSysFont, BOOL scaleToScreenRes )
{
   ASSERT( pControl );

   DWORD winStyle = WS_CHILD|WS_TABSTOP;

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

//   BOOL retVal = CButtonST::Create( pControl->m_sLbl, winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   BOOL retVal = CButtonST::Create( "", winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
      m_sStatusMsg   = pControl->m_sStatusMsg;

      m_bCalledNew = calledNew;

      m_iHelpGroupIdx = pControl->m_iHelpGroupIdx;

//      SetFont( GetWizFont(m_iFont), TRUE );

      int iBmpID = (FontY(20) > 22 ? IDB_EQ_HELP24 : IDB_EQ_HELP20);  // SAC 10/27/02
      SetBitmaps( iBmpID, RGB(255,0,0), iBmpID+1, RGB(255,0,0) );
      SizeToContent();
      DrawBorder( FALSE );

      if (!m_sStatusMsg.IsEmpty())
         SetTooltipText( m_sStatusMsg );
   }
   return retVal;
}


void CBEMProcCtrlHelpBtn::PostNcDestroy()
{
    if (m_bCalledNew)
        delete this;
}



void CBEMProcCtrlHelpBtn::OnLButtonUp( UINT nFlags, CPoint point )
{
//   CWnd* pPar = GetParent();
   CButtonST::OnLButtonUp( nFlags, point );

   if (m_iHelpGroupIdx >= 0)
      GetParentFrame()->SendMessage( WM_HELP_BTN_PRESSED, m_iHelpGroupIdx, (long) this );  // pPar );
}

void CBEMProcCtrlHelpBtn::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
//   CWnd* pPar = GetParent();
   CButtonST::OnKeyUp( nChar, nRepCnt, nFlags );

   if (nChar == VK_SPACE  &&  m_iHelpGroupIdx >= 0)
      GetParentFrame()->SendMessage( WM_HELP_BTN_PRESSED, m_iHelpGroupIdx, (long) this );  // pPar );
}
