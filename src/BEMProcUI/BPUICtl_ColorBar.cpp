// BPUICtl_ColorBar.CPP  :  Contains CColorBarCtl routines
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
/*  (c) Copyright 2002, SAC Software Solutions, Inc.                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "Screens.h"
#include "BPUICtl_ColorBar.h" 
#include "BEMProcUIX.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNAMIC( CColorBarCtl, CWnd )

/////////////////////////////////////////////////////////////////////////////
// CColorBarCtl

BEGIN_MESSAGE_MAP(CColorBarCtl, CWnd)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_WM_PAINT()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_TIMER()
   ON_WM_RBUTTONDOWN()  // SAC 12/9/02

	ON_WM_HELPINFO()

END_MESSAGE_MAP()


CColorBarCtl::CColorBarCtl()
	: CWnd()
{
	//{{AFX_DATA_INIT(CColorBarCtl)
	//}}AFX_DATA_INIT
   m_bCalledNew = FALSE;

   m_iNumSections  = 1;    // SAC 5/1/02 - Added ColorBar-specific properties
   m_iSectionWidth = 0;

   m_iMouseMoveDelta = 100;  // SAC 5/2/02 - mods to facilitate click-drag processing
   m_bMouseDown      = FALSE;
   m_iLastMouseX     = -1;
   m_iLastSectionSet = -1;
}


CColorBarCtl::~CColorBarCtl()
{
}


void CColorBarCtl::SizeAndPos( int iX, int iY, int iWd, int iHt, int winHt, int winWd, int iMode,
                                BOOL scaleToSysFont, BOOL scaleToScreenRes, CSize& size, CPoint& pos )
{
   if (iMode == 0)   // SAC 5/1/02
      m_iNumSections = 24;
   else
   {  ASSERT( FALSE );  }

   double dScale = (scaleToScreenRes ? __min(appXRatio,appYRatio) : 1.0);
   
   int sizeX = (int)((double) iWd * dScale);
   int sizeY = (int)((double) iHt * dScale);
   
   int x = (int)((double) iX * dScale);
   int y = (int)((double) iY * dScale);
   
   if (iWd < 0)
   {
      sizeX = abs( sizeX );
      x += ((winWd - sizeX) / 2);
   }
   if (iHt < 0)
   {
      sizeY = abs( sizeY );
      y += ((winHt - sizeY) / 2);
   }
   
   if (scaleToSysFont)
   {
      sizeX = FontX( sizeX );
      sizeY = FontY( sizeY );
      x     = FontX( x );
      y     = FontY( y );
   }

   x = __max( 2, x );
   y = __max( 2, y );

   if ( ((x + sizeX) > (winWd-2)) ||   // if picture is going to exceed window
        ((y + sizeY) > (winHt-2)) )    // dimensions, then scale it until it won't
   {
      double d2XScale = ((double) (winWd-2 - x)) / ((double) sizeX);
      double d2YScale = ((double) (winHt-2 - y)) / ((double) sizeY);

      double d2Scale = __min( d2XScale, d2YScale );

      sizeX = (int) ((double) sizeX * d2Scale);
      sizeY = (int) ((double) sizeY * d2Scale);
   }

   size.cx = sizeX;
   size.cy = sizeY;
   pos.x   = x;
   pos.y   = y;

   m_iSectionWidth = (sizeX - (2 * GetSystemMetrics(SM_CXEDGE))) / m_iNumSections;   // SAC 5/1/02
   size.cx = (m_iSectionWidth * m_iNumSections) + (2 * GetSystemMetrics(SM_CXEDGE)) + 1;
   m_iMouseMoveDelta = m_iSectionWidth / 4;  // SAC 5/2/02 - mods to facilitate click-drag processing
}


BOOL CColorBarCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl,
                            int winHt, int winWd, DWORD dwBckColor, BOOL bTabbedDlgShift,
                            BOOL scaleToSysFont, BOOL scaleToScreenRes,
                            BOOL /*bUseVerdanaFonts*/, UINT uiTopicHelp, UINT uiItemHelp )
{
   DWORD winStyle = WS_CHILD|WS_BORDER;

   CSize size;
   CPoint pos;
   SizeAndPos( pControl->m_iX, pControl->m_iY, pControl->m_iWidth, pControl->m_iHeight,
               winHt, winWd, pControl->m_lValue, scaleToSysFont, scaleToScreenRes, size, pos );

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

   BOOL retVal = CWnd::CreateEx( WS_EX_CLIENTEDGE, NULL, pControl->m_sLbl, winStyle, CRect(pos, size),
                                 pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
      m_lDBID      	= pControl->m_lDBID;
      m_sStatusMsg 	= pControl->m_sStatusMsg;

      ASSERT( pControl->m_iDBInstance < 0 );  // SAC 3/3/99 - not yet implemented for this control type

      m_iMode        = pControl->m_lValue;

      m_iDataType   	= BEMPX_GetDataType(  m_lDBID );
      m_iItemHelpID  = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lDBID ) : uiItemHelp);  // SAC 12/9/02
      m_iTopicHelpID = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lDBID ) : uiTopicHelp);

      m_dwBckgrndColor = dwBckColor;
      m_bCalledNew = TRUE;
   }

   return retVal;
}


void CColorBarCtl::PostNcDestroy()
{
	if (m_bCalledNew)
		delete this;
}


/////////////////////////////////////////////////////////////////////////////
// CColorBarCtl diagnostics

#ifdef _DEBUG
void CColorBarCtl::AssertValid() const
{
	CWnd::AssertValid();
}

void CColorBarCtl::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CColorBarCtl OnDisplayData()

LONG CColorBarCtl::OnDisplayData(UINT, LONG)
{
   RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CColorBarCtl Painting

void CColorBarCtl::OnPaint()
{
	CWaitCursor wait;

	CPaintDC dc(this);

   CRect rect;
   GetClientRect( &rect );
   dc.SetBkColor( m_dwBckgrndColor );
   dc.ExtTextOut( 8, 0, ETO_OPAQUE, rect, " ", 1, NULL);

   CPen penSecDiv;
   penSecDiv.CreatePen( PS_SOLID, 1, ::GetSysColor( COLOR_BTNSHADOW ) );
   CPen*   pPrevPen   = dc.SelectObject( &penSecDiv );
   CBrush* pPrevBrush = dc.SelectObject( &buttonBrush );

   CPtrArray paSectionBrushes;
   long lMaxNumDBID = m_lDBID - (m_lDBID % BEM_PARAM_MULT) + 2;
   long lNumBrushes;
   VERIFY( BEMPX_SetDataInteger( lMaxNumDBID, lNumBrushes ) );
   int i=0;
   for (; i<lNumBrushes; i++)
   {
      CBrush* pSectionBrush = new CBrush();
      if (pSectionBrush)
      {
         long lR, lG, lB;
         long lColorDBID = lMaxNumDBID + 2 + (3 * i);
         if ( !BEMPX_SetDataInteger( lColorDBID  , lR )  ||
              !BEMPX_SetDataInteger( lColorDBID+1, lG )  ||
              !BEMPX_SetDataInteger( lColorDBID+2, lB ) )
         {
            lR = lG = lB = 0;
            ASSERT( FALSE );
         }
         pSectionBrush->CreateSolidBrush( RGB( lR, lG, lB ) );
      }
      else
      {  ASSERT( FALSE );  }

      paSectionBrushes.Add( pSectionBrush );
   }

   for (i=0; i<m_iNumSections; i++)
   {
      int iLt =  m_iSectionWidth *  i        ;
      int iRt = (m_iSectionWidth * (i+1)) - 1;

      // COLOR THIS SECTION
      CBrush* pSectionBrush = &blackBrush;
      long lVal;
      if (BEMPX_SetDataInteger( m_lDBID + i, lVal ) && lVal > 0 && lVal <= paSectionBrushes.GetSize() && paSectionBrushes[ lVal-1 ] != NULL)
         pSectionBrush = (CBrush*) paSectionBrushes[ lVal-1 ];
//      dc.SelectObject( pSectionBrush );
      dc.FillRect( CRect( iLt, 0, iRt, rect.Height() ), pSectionBrush );

      // draw border separating sections
      if (i > 0)
      {
         dc.MoveTo( iLt-1, 0 );
         dc.LineTo( iLt-1, rect.Height() );
      }
   }

   // Restore original pen, brush and font
   dc.SelectObject( pPrevPen );
   dc.SelectObject( pPrevBrush );

   for (i=0; i<lNumBrushes; i++)  // delete brushes
   {
      CBrush* pSectionBrush = (CBrush*) paSectionBrushes[i];
      if (pSectionBrush)
         delete pSectionBrush;
   }
}


//////////////////////////////////////////////////////////////////////
// Mouse Actions

void CColorBarCtl::OnLButtonDown( UINT nFlags, CPoint point )
{
   ProcessMouseAction( nFlags, point, CCB_LMOUSE_DOWN );
//   long iSection = (point.x / m_iSectionWidth) + 1;
//
////   CString sMsg;
////   if (iSection > 0 && iSection <= m_iNumSections)
////      sMsg.Format( "Clicked on section #%d.", iSection );
////   else
////      sMsg.Format( "Invalid section (%d).", iSection );
////   MessageBox( sMsg );
//
//   if (iSection > 0 && iSection <= m_iNumSections)
//   {
//      long lActiveDBID = m_lDBID - (m_lDBID % BEM_PARAM_MULT) + 1;
//      long lActiveValue;
//      if (BEMPX_SetDataInteger( lActiveDBID, lActiveValue ))
//      {
//         int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID + (iSection-1), BEMP_Int, (void*) &lActiveValue );
//         if (iSetDataRetVal >= 0)
//         {
//            // Post-processing following mods
////            m_bUpdatingData = TRUE;
//            GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lDBID + (iSection-1) );
////            m_bUpdatingData = FALSE;
//
//            // redisplay status bar strings
//            CFrameWnd* pFrame = GetParentFrame();
//            if (pFrame)
//               pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
//         }
//      }
//      else
//      {  ASSERT( FALSE );  }
//   }
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CColorBarCtl::OnLButtonUp( UINT nFlags, CPoint point )
{
   ProcessMouseAction( nFlags, point, CCB_LMOUSE_UP );
	CWnd::OnLButtonUp(nFlags, point);
}

void CColorBarCtl::OnMouseMove( UINT nFlags, CPoint point )
{
   if (m_bMouseDown)
      ProcessMouseAction( nFlags, point, CCB_MOUSE_MOVE );
   else if (::GetAsyncKeyState( VK_LBUTTON ) & 0xFFFE)  // Check for left mouse button down (ignoring low order bit)
      ProcessMouseAction( nFlags, point, CCB_LMOUSE_DOWN );

	CWnd::OnMouseMove(nFlags, point);
}


// #define  CCB_LMOUSE_DOWN  0
// #define  CCB_LMOUSE_UP    1
// #define  CCB_MOUSE_MOVE   2

void CColorBarCtl::ProcessMouseAction( UINT& /*nFlags*/, CPoint& point, int iClickType )
{
   if (iClickType == CCB_LMOUSE_DOWN)
      m_bMouseDown = TRUE;

   BOOL bProcess = ( iClickType != CCB_MOUSE_MOVE  ||    // automatically process anytime for mouse up or down processing
                     abs( point.x - m_iLastMouseX ) >= m_iMouseMoveDelta );  // process mouse moves only if mouse has moved sufficient distance
   if (bProcess)
   {
      m_iLastMouseX = point.x;
      
      long iSection = (point.x / m_iSectionWidth) + 1;
      if ( iSection > 0  &&  iSection <= m_iNumSections  &&
           (iClickType == CCB_LMOUSE_DOWN  ||  iSection != m_iLastSectionSet) )
      {
         long lActiveDBID = m_lDBID - (m_lDBID % BEM_PARAM_MULT) + 1;
         long lActiveValue;
         if (BEMPX_SetDataInteger( lActiveDBID, lActiveValue ))
         {
            int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID + (iSection-1), BEMP_Int, (void*) &lActiveValue );
            if (iSetDataRetVal >= 0)
            {  
               m_iLastSectionSet = iSection;
            
               // manually redraw bar prior to ruleset processing, etc.
               RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
            }
         }
      }

      if (m_iLastSectionSet >= 0)
      {
         KillTimer(1);
         // set timer to initiate ruleset processing following ALL mouse settings
         if (iClickType == CCB_LMOUSE_UP)
            PostProcessMouseMods();
         else
            SetTimer( 1, 300, NULL );  // pause 1/3 of second before initiating post-processing
      }
   }

   if (iClickType == CCB_LMOUSE_UP)
      m_bMouseDown = FALSE;
}


static BOOL sbPostProcessingMouseMods = FALSE;

void CColorBarCtl::PostProcessMouseMods()
{
   if (sbPostProcessingMouseMods)
   {  // reset timer to re-initiate post processing again once this round is completed
      KillTimer(1);
      SetTimer( 1, 300, NULL );
   }
   else
   {
      // reset various flags used during mouse movement & processing
      long iSection     = m_iLastSectionSet;
      m_iLastMouseX     = -1;
      m_iLastSectionSet = -1;

      // Post-processing following mods
      sbPostProcessingMouseMods = TRUE;
      GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lDBID + (iSection-1) );
      sbPostProcessingMouseMods = FALSE;

      // redisplay status bar strings
      CFrameWnd* pFrame = GetParentFrame();
      if (pFrame)
         pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
   }
}


void CColorBarCtl::OnTimer(UINT nIDEvent)
{
   if (nIDEvent == 1)
   {
      POINT pt;
      GetCursorPos(&pt);
      CRect rect;
      GetWindowRect(rect);

      KillTimer(1);
      if (m_bMouseDown  &&  rect.PtInRect(pt))
         // don't post process mouse input yet - until user releases mouse within bar or leaves bar 
         SetTimer( 1, 300, NULL );
      else if (!rect.PtInRect(pt))
         PostProcessMouseMods();
   }

   CWnd::OnTimer(nIDEvent);
}


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CColorBarCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CWnd::OnHelpInfo(pHelpInfo);
}


void CColorBarCtl::OnRButtonDown( UINT /*nFlags*/, CPoint /*point*/ )  // SAC 12/9/02
{
//   SetFocus();
   DoQuickMenu();
}


void CColorBarCtl::DoQuickMenu()  // SAC 12/9/02
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
      qmInfo.m_lDBID  = m_lDBID;
      qmInfo.m_iDBInstance = -1;   // m_iDBInstance;
      qmInfo.m_bEditable = TRUE;   // m_bEditable;
      qmInfo.m_bObjectAssign = FALSE;
      qmInfo.m_iDBaseType = QMI_DBASETYPE_BEMPROC;
      qmInfo.m_dwFlags = 0;

      pFrame->SendMessage( WM_QUICKMENU, NULL, (LPARAM) &qmInfo );
   }
}
