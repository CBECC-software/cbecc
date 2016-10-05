// BEMProcCtrlCheckListBox.cpp : implementation file
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
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMSymbols.h"
#include "Screens.h"
#include "BEMProcCtrlCheckListBox.h"
#include "BEMProcUIX.h"
#include "BEMProcCtrlRTF.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CBEMProcCtrlCheckListBox, CCheckListBox )

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlCheckListBox

BEGIN_MESSAGE_MAP(CBEMProcCtrlCheckListBox, CCheckListBox)
	//{{AFX_MSG_MAP(CBEMProcCtrlCheckListBox)
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelChange)
	ON_CONTROL_REFLECT(LBN_SETFOCUS, OnSetFocus)
	ON_CONTROL_REFLECT(CLBN_CHKCHANGE, OnCheckChange)
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)

	ON_WM_HELPINFO()   // SAC 10/16/02 - added for F1 and Shift-F1 (arrow) context help functionality

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlCheckListBox message handlers

CBEMProcCtrlCheckListBox::CBEMProcCtrlCheckListBox()
{
   m_bUpdatingList = FALSE;
   m_bSettingHighlight = FALSE;
   m_lRTFCtrlID = 0;
}


BOOL CBEMProcCtrlCheckListBox::Create( CWnd* pParentWnd, CBEMPUIControl* pControl )
{
   BOOL temp = FALSE;

   DWORD dwStyle = WS_CHILD|WS_TABSTOP|WS_BORDER | WS_VSCROLL | LBS_NOTIFY | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS;
//    LISTBOX         IDC_LIST,4,2,272,150,NOT LBS_NOTIFY | LBS_SORT | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS | LBS_EXTENDEDSEL | WS_VSCROLL | WS_TABSTOP

   double xScale = 1.0;  // (scale ? appXRatio : 1.0);
   double yScale = 1.0;  // (scale ? appYRatio : 1.0);
   CSize size( FontX( (int) (((double) pControl->m_iWidth ) * xScale) ),
               FontY( (int) (((double) pControl->m_iHeight) * yScale) ) );
   CPoint pos( FontX( (int) (((double) pControl->m_iX     ) * xScale) ),
               FontY( (int) (((double) pControl->m_iY     ) * yScale) ) );

//   temp = CListBox::Create( dwStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "LISTBOX", "", dwStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (temp)
   {
      m_lDBID           = pControl->m_lDBID;
      m_iDBClass        = BEMPX_GetClassID( m_lDBID );
      m_iFont        	= pControl->m_iFont;
      m_bCalledCreate 	= TRUE;
      m_sStatusMsg 		= pControl->m_sStatusMsg;
      
      m_iItemHelpID     = BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID    = BEMPX_GetTopicHelpID( m_lDBID );

      SetFont( GetWizFont(m_iFont), TRUE );

      int iMarginVal = (pControl->m_lValue <= 10 ? pControl->m_lValue : 5);  // SAC 5/30/01
      m_iMarginX = FontX( (iMarginVal*2) );
      m_iMarginY = FontY(  iMarginVal    );

      m_lRTFCtrlID = (pControl->m_lValue > 10 ? pControl->m_lValue : 0);  // SAC 7/15/00 & 5/30/01
      m_sRuleListName = pControl->m_sLbl;  // SAC 7/15/00

      // SAC 7/14/00 - Some extra stuff specific to the "Measures" implementation
      int iPropID = BEMPX_GetPropertyID( m_lDBID );
      int iArrID  = BEMPX_GetArrayID( m_lDBID );
      m_lMsrIsAvailableDBID = BEMPX_GetDBID( m_iDBClass, (iPropID+1), iArrID );  // SAC 7/18/01
      m_lMsrIsCheckedDBID   = BEMPX_GetDBID( m_iDBClass, (iPropID+2), iArrID );  // SAC 7/18/01
      m_lMsrOrderDBID       = BEMPX_GetDBID( m_iDBClass, (iPropID+3), iArrID );  // SAC 7/18/01
      m_iTotNumMeasures = 0;
   }

	return temp;
}

void CBEMProcCtrlCheckListBox::PostNcDestroy() 
{
//	CListCtrl::PostNcDestroy();
	if (m_bCalledCreate)
		delete this;
}


LONG CBEMProcCtrlCheckListBox::OnDisplayData(UINT, LONG)
{
   if (!m_bUpdatingList  &&  !m_bSettingHighlight  &&  m_iDBClass > 0)
   {
      m_bUpdatingList = TRUE;

      SetRedraw( FALSE );

      ResetContent();

      m_iTotNumMeasures = 0;
      int iCurSelItem = 0;
      int iCurItemIdx = -1;
      long lActiveMsr;
      if (BEMPX_SetDataInteger( m_lDBID, lActiveMsr ))
      {
         int iNumSyms;
//         CArray<BEMSymbol*, BEMSymbol*>* pSymArray = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID );
			BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID );
         if (!pSymDepSet)
            BEMMessageBox( "CBEMProcCtrlCheckListBox::OnDisplayData():  Error loading symbol data" );
         else
         {
            m_iTotNumMeasures = iNumSyms;
            for (int iSym=0; iSym < iNumSyms; iSym++)
            {
               long lOrder;
               VERIFY( BEMPX_SetDataInteger( m_lMsrOrderDBID+iSym, lOrder ) );
               ASSERT( lOrder >= 0 );
               ASSERT( lOrder <= iNumSyms );
               long lIsAvailable;
               if ( lOrder > 0  &&  BEMPX_SetDataInteger( m_lMsrIsAvailableDBID + lOrder - 1, lIsAvailable )  &&
                    lIsAvailable > 0 )
               {
                  // We are assuming at this point that the symbol table index == (lOrder-1)
                  long iSymValue;
                  QString qstr;
                  BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet /*pSymList*/, lOrder-1 );   // SAC 3/23/07
                  if (qstr.length() > 0)
                  {
                     ASSERT( iSymValue == lOrder );
                     iCurItemIdx = AddString( qstr.toLatin1().constData() );
                     SetItemData( iCurItemIdx, (DWORD) iSymValue );

                     long lChecked;
                     if ( BEMPX_SetDataInteger( m_lMsrIsCheckedDBID + lOrder - 1, lChecked )  &&  lChecked > 0 )
                        SetCheck( iCurItemIdx, 1 );

                     if (lActiveMsr == lOrder)
                        iCurSelItem = iCurItemIdx;
                  }
               }
            }
         }
      }

// TEMPORARY vvvvv
//      iCurItemIdx = AddString( "Item # 1" );
//      SetItemData( iCurItemIdx, (DWORD) 5 );
//      SetCheck( iCurItemIdx, 0 );
//
//      iCurItemIdx = AddString( "Item # 2" );
//      SetItemData( iCurItemIdx, (DWORD) 6 );
//      SetCheck( iCurItemIdx, 1 );
//
//      iCurItemIdx = AddString( "Item # 3" );
//      SetItemData( iCurItemIdx, (DWORD) 7 );
//      SetCheck( iCurItemIdx, 0 );
// TEMPORARY ^^^^^

      if (iCurSelItem <= iCurItemIdx)
         SetCurSel( iCurSelItem );

      m_bUpdatingList = FALSE;

      SetRedraw();
      Invalidate();
   }
   return 1;
}


// SAC 7/14/00 - Tried implementing this to shift check box in from left edge but it asserts immediately after returning
//               to where it was called from due to the fact that the returned rect intersects with the itemrect!
// CRect CBEMProcCtrlCheckListBox::OnGetCheckPosition(CRect rectItem, CRect rectCheckBox)
// {
// // this example implementation positions the checkbox on the RIGHT side of the item
// //   CRect rectMyCheckBox;
// //   rectMyCheckBox.top = rectItem.top -1;
// //   rectMyCheckBox.bottom = rectItem.bottom -1;
// //   rectMyCheckBox.right = rectItem.right -1;
// //   rectMyCheckBox.left = rectItem.right -1 - rectCheckBox.Width();
// 
//    CRect rectMyCheckBox = rectCheckBox;
//    rectMyCheckBox.right += FontX( 3 );
//    rectMyCheckBox.left  += FontX( 3 );
// 
//    return rectMyCheckBox;
// }
// // the following code is from where MFC prepares for and calls the above Virtual function
// //			int nCheck = GetCheck(drawItem.itemID);
// //			HBITMAP hOldBitmap = (HBITMAP)::SelectObject(bitmapDC.m_hDC, pChecklistState->m_hbitmapCheck);
// //
// //			CRect rectCheck = drawItem.rcItem;
// //			rectCheck.left += 1;
// //			rectCheck.top += 1 + max(0, (cyItem - pChecklistState->m_sizeCheck.cy) / 2);
// //			rectCheck.right = rectCheck.left + pChecklistState->m_sizeCheck.cx;
// //			rectCheck.bottom = rectCheck.top + pChecklistState->m_sizeCheck.cy;
// //
// //			CRect rectItem = drawItem.rcItem;
// //			rectItem.right = rectItem.left + pChecklistState->m_sizeCheck.cx + 2;
// //
// //			CRect rectCheckBox = OnGetCheckPosition(rectItem, rectCheck);
// //
// //			ASSERT(rectCheck.IntersectRect(rectItem, rectCheckBox));
// //			ASSERT((rectCheck == rectCheckBox) && (rectCheckBox.Size() == pChecklistState->m_sizeCheck));


void CBEMProcCtrlCheckListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
// all items are of fixed size
// must use LBS_OWNERDRAWVARIABLE for this to work

	int nItem = lpMIS->itemID;
	CPaintDC dc(this);
	CString sLabel;
	CRect rcLabel;

	GetText( nItem, sLabel );
	GetItemRect(nItem, rcLabel);

   // SAC 7/14/00 - Make sure the calculation of item height is based on the actual font being used
   dc.SelectObject( GetWizFont(m_iFont) );

   // SAC 7/14/00 - Adjust rcLabel rect by 2*m_iMarginX
   rcLabel.right -= (2 * m_iMarginX);

// Using the flags below, calculate the required rectangle for 
// the text and set the item height for this specific item based
// on the return value (new height).

	int itemHeight = dc.DrawText( sLabel, -1, rcLabel, DT_WORDBREAK | DT_CALCRECT );
   // SAC 7/14/00 - Increase allocated height by 2*m_iMarginY
	lpMIS->itemHeight = itemHeight + (2 * m_iMarginY);
}

void CBEMProcCtrlCheckListBox::AdjustTextRect( RECT* pRect )
{
   pRect->left   += m_iMarginX;
   pRect->top    += m_iMarginY;
   pRect->right  -= m_iMarginX;
   pRect->bottom -= m_iMarginY;
}

void CBEMProcCtrlCheckListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

//	COLORREF rColor = (COLORREF)lpDIS->itemData; // RGB in item data
// SAC
	COLORREF rColor = (COLORREF) ::GetSysColor(COLOR_WINDOW); // RGB in item data

	CString sLabel;
   if (((long) lpDIS->itemID) != -1)
   	GetText(lpDIS->itemID, sLabel);

	// item selected
	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
//		// draw color box
//		CBrush colorBrush(rColor);
//		CRect colorRect = lpDIS->rcItem;

		// draw label background
// SAC 7/14/00 - switch selection color to COLOR_SCROLLBAR ?? if the control does not have the input focus
// didn't work out
//		CBrush labelBrush( ((lpDIS->itemState & ODS_FOCUS) ? ::GetSysColor(COLOR_HIGHLIGHT) : ::GetSysColor(COLOR_SCROLLBAR)) );
		CBrush labelBrush( ::GetSysColor(COLOR_HIGHLIGHT) );
		CRect labelRect = lpDIS->rcItem;
		pDC->FillRect(&labelRect,&labelBrush);

		// draw label text
		COLORREF colorTextSave;
		COLORREF colorBkSave;

		colorTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		colorBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      AdjustTextRect( &lpDIS->rcItem );  // SAC 7/14/00
		pDC->DrawText( sLabel, -1, &lpDIS->rcItem, DT_WORDBREAK );

		pDC->SetTextColor(colorTextSave);
		pDC->SetBkColor(colorBkSave);

		return;
	}

	// item brought into box
	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		CBrush brush(rColor);
		CRect rect = lpDIS->rcItem;
		pDC->SetBkColor(rColor);
		pDC->FillRect(&rect,&brush);

      AdjustTextRect( &lpDIS->rcItem );  // SAC 7/14/00
		pDC->DrawText( sLabel, -1, &lpDIS->rcItem, DT_WORDBREAK );

		return;
	}

	// item deselected
	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		CRect rect = lpDIS->rcItem;
		CBrush brush(rColor);
		pDC->SetBkColor(rColor);
		pDC->FillRect(&rect,&brush);

      AdjustTextRect( &lpDIS->rcItem );  // SAC 7/14/00
		pDC->DrawText( sLabel, -1, &lpDIS->rcItem, DT_WORDBREAK );

		return;
	}

// SAC
   // draw focus rect
   if (lpDIS->itemAction & ODA_FOCUS)
      pDC->DrawFocusRect( &lpDIS->rcItem );
}


void CBEMProcCtrlCheckListBox::SwitchActive() 
{
   int iCurSel = GetCurSel();
   if (iCurSel != LB_ERR)
   {
      long lMeasureItem = (long) GetItemData( iCurSel );
      if ( lMeasureItem >= 1  &&  lMeasureItem <= m_iTotNumMeasures  &&
           BEMPX_SetBEMData( m_lDBID, BEMP_Int, (void*) &lMeasureItem ) >= 0  &&
           !m_sRuleListName.IsEmpty()  &&  m_lRTFCtrlID > 0  &&
           BEMPX_EvaluateRuleList( m_sRuleListName ) )  // this rule eval should set RTF filename based on new active selection
      {
         // update the RTF control directly (rather than updating it via evaluation of ENTIRE wizard rulelist and updating ALL controls)
         CWnd* pParent = GetParent();
         if (pParent)
         {
            CWnd* pLinkCtrl = pParent->GetDlgItem( m_lRTFCtrlID );
            if (pLinkCtrl  &&  pLinkCtrl->IsKindOf(RUNTIME_CLASS( CBEMProcCtrlRTF )))
               ((CBEMProcCtrlRTF*)pLinkCtrl)->OnDisplayData(0,0);
         }
      }
   }
}

void CBEMProcCtrlCheckListBox::OnSelChange() 
{
   SwitchActive();
}

void CBEMProcCtrlCheckListBox::OnSetFocus() 
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );

   SwitchActive();
}


void CBEMProcCtrlCheckListBox::OnCheckChange() 
{
   int iCurSel = GetCurSel();
   if (iCurSel != LB_ERR)
   {
      long lCheck = GetCheck( iCurSel );
      long lMeasureItem = (long) GetItemData( iCurSel );
      if (lCheck != 2  &&  lMeasureItem >= 1  &&  lMeasureItem <= m_iTotNumMeasures)
      {
         long lDBID = m_lMsrIsCheckedDBID + lMeasureItem - 1;
         int iSetDataRetVal = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lCheck );
         if (iSetDataRetVal >= 0)
         {
            // Post-processing following mods
// ???
// ??? SHOULD WE EVALUATE RULES FOLLOWING THESE CHECKs/UNCHECKs ???
// ???
            m_bSettingHighlight = TRUE;  // SAC 7/14/00 - this prevents list from getting refreshed (which also causes selection to jump to top)
            WORD wEval = 0;  // (bEvalRules ? 1 : 0);
            GetParent()->SendMessage( WM_DATAMODIFIED, wEval, lDBID );
            m_bSettingHighlight = FALSE;

            // redisplay status bar strings
            CFrameWnd* pFrame = GetParentFrame();
            if (pFrame)
               pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
         }
      }
   }
}


// SAC 10/16/02 - added for F1 and Shift-F1 (arrow) context help functionality
BOOL CBEMProcCtrlCheckListBox::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
	return CCheckListBox::OnHelpInfo(pHelpInfo);
}


