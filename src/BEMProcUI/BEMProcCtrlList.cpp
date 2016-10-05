// BEMProcCtrlList.cpp : implementation file
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
#include "..\BEMProc\BEMClass.h"
#include "Screens.h"
#include "BEMProcCtrlList.h"
#include "BEMProcUIX.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CBEMProcCtrlList, CListCtrl )


/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlList

CBEMProcCtrlList::CBEMProcCtrlList()
{
   m_bUpdatingList = FALSE;
   m_bSettingHighlight = FALSE;
   m_iNumColumns = 0;

   m_lDBID           = 0;
   m_iDBClass        = 0;
   m_iDBParentClass  = 0;
   m_iFont        	= 0;
   m_bCalledCreate 	= FALSE;
   m_sStatusMsg 		= "";
   m_iItemHelpID     = 0;
   m_iTopicHelpID    = 0;

   m_iListCtrlMode = -1;  // SAC 7/13/00

   m_iNavigationID = 0;  // SAC 3/31/02
}

CBEMProcCtrlList::~CBEMProcCtrlList()
{
}


BEGIN_MESSAGE_MAP(CBEMProcCtrlList, CListCtrl)
	//{{AFX_MSG_MAP(CBEMProcCtrlList)
	ON_WM_HELPINFO()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemChanged)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlList message handlers

BOOL CBEMProcCtrlList::Create( CWnd* pParentWnd, CBEMPUIControl* pControl )
{
   BOOL temp = FALSE;

   // SAC 7/13/00 - added mode enum value for measures CheckList box functionality
   m_iListCtrlMode = pControl->m_lValue;
   ASSERT( (m_iListCtrlMode >= 0 && m_iListCtrlMode < BEMPCLM_NumModes) );

   DWORD winStyle = ((m_iListCtrlMode == BEMPCLM_Active || m_iListCtrlMode == BEMPCLM_ActiveChild) ?
                         WS_CHILD|WS_TABSTOP|WS_BORDER | LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_NOCOLUMNHEADER :
                                                        0 );  // no other modes for now

   double xScale = 1.0;  // (scale ? appXRatio : 1.0);
   double yScale = 1.0;  // (scale ? appYRatio : 1.0);
   CSize size( FontX( (int) (((double) pControl->m_iWidth ) * xScale) ),
               FontY( (int) (((double) pControl->m_iHeight) * yScale) ) );
   CPoint pos( FontX( (int) (((double) pControl->m_iX     ) * xScale) ),
               FontY( (int) (((double) pControl->m_iY     ) * yScale) ) );

//   if (bTabbedDlgShift)
//   {  // shift for Win95 tabbed dialog class
//      pos.x += eiTabDlgCtrlMarg;
//      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
//   }

// SAC 6/8/00 - This is what is done in the normal CListCtrl::Create() - need we figure out how to get the control registered BEFORE calling CreateEx()??
//	// initialize common controls
//	VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTL_LISTVIEW_REG));

   // SAC - 1/6/98 - Call CreateEx() in order to specify extended style "WS_EX_CLIENTEDGE" which
   //                draws the border as 3D (rather than boring 2D black line)
   //         was -> temp = CEdit::Create( winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
//   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "EDIT", "", winStyle, CRect(pos, size),
//                          pParentWnd, pControl->m_uiCtrlID );
//   temp = CListCtrl::Create( winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "SysListView32", "", winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (temp)
   {
      m_lDBID           = pControl->m_lDBID;  // + lDBIDOffset;
      m_iDBClass        = BEMPX_GetClassID( m_lDBID );
      m_iDBParentClass  = (m_iListCtrlMode == BEMPCLM_ActiveChild ? BEMPX_GetParentComponentType( m_iDBClass ) : 0);  // SAC 3/30/02
      m_iFont        	= pControl->m_iFont;
      m_bCalledCreate 	= TRUE;
//      m_lValue          = 
      m_sStatusMsg 		= pControl->m_sStatusMsg;
      
      m_iNavigationID   = pControl->m_iUnitDX;  // SAC 3/31/02

      m_iItemHelpID     = BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID    = BEMPX_GetTopicHelpID( m_lDBID );

      SetFont( GetWizFont(m_iFont), TRUE );

      InsertColumn( 0, "Name" );
      m_iNumColumns = 1;
   }
   return temp;
}

BOOL CBEMProcCtrlList::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CBEMProcCtrlList::PostNcDestroy() 
{
//	// TODO: Add your specialized code here and/or call the base class
//	
//	CListCtrl::PostNcDestroy();
	if (m_bCalledCreate)
		delete this;
}

BOOL CBEMProcCtrlList::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );  // SAC 10/16/02 - added based on other UI control implementations
	
	return CListCtrl::OnHelpInfo(pHelpInfo);
}


LONG CBEMProcCtrlList::OnDisplayData(UINT, LONG)
{
   if (!m_bUpdatingList  &&  !m_bSettingHighlight  &&  m_iDBClass > 0)
   {
      BOOL bActiveCompReset = FALSE;
      m_bUpdatingList = TRUE;

      SetRedraw( FALSE );

//      int nCount = GetItemCount();
//      // Delete all of the items from the list view control.
//      for (int i=0; i < nCount; i++)
//         DeleteItem(0);

      if (DeleteAllItems())
      {
         int iError;
         BEMClass* pClass = BEMPX_GetClass( m_iDBClass, iError );
         ASSERT( pClass != NULL );
         ASSERT( pClass->getCurrentBEMObjType() == BEMO_User );
         int iActiveObjIdx = pClass->getCurrentBEM0ObjIdx();

         int iStatus, iSV;
         QString sData;
         int iListIdx = 0;
         int iActiveListIdx = -1;
         if (m_iListCtrlMode == BEMPCLM_ActiveChild)  // SAC 3/30/02 - added to facilitate listing only children of the first valid PARENT component type
         {
            ASSERT( m_iDBParentClass > 0 );
            BEMClass* pParentClass = BEMPX_GetClass( m_iDBParentClass, iError );
            ASSERT( pParentClass != NULL );
            ASSERT( pParentClass->getCurrentBEMObjType() == BEMO_User );
            //int iActiveParentObjIdx = pParentClass->getCurrentBEM0ObjIdx();

            int iNumChildren = (int) BEMPX_GetNumChildren( m_iDBParentClass, -1, BEMO_User, m_iDBClass );
            int iFirstChildObjIdx = -1;
            for (int idx=0; idx<iNumChildren; idx++)
            {
               BEM_ObjType eChildObjType = BEMO_User;
               int i0ChildObjIdx = BEMPX_GetChildObjectIndex( m_iDBParentClass, m_iDBClass, iError, eChildObjType, idx+1 );
               ASSERT( (i0ChildObjIdx >= 0) );
               ASSERT( (eChildObjType == BEMO_User) );
               if (i0ChildObjIdx >= 0)
               {
               //   if (BEMPX_SetDataStringAndStatus( m_lDBID, sData, iStatus, TRUE, 0 /*m_lValue*/, -1, i0ChildObjIdx ))
               	sData = BEMPX_GetStringAndStatus( m_lDBID, iStatus, iSV, iError, i0ChildObjIdx );
               	if (iStatus > 0 && !sData.isEmpty())
                  {
                     if (InsertItem( iListIdx, sData.toLatin1().constData() ) > -1  &&  SetItemData( iListIdx, (DWORD) i0ChildObjIdx ))
                     {
                        if (iFirstChildObjIdx == -1)
                           iFirstChildObjIdx = i0ChildObjIdx;
                        if (i0ChildObjIdx == iActiveObjIdx)
                           iActiveListIdx = iListIdx;
                        iListIdx++;
                     }
                  }
               }
            }
            SetColumnWidth( 0, LVSCW_AUTOSIZE );

            if (iActiveListIdx == -1 && iFirstChildObjIdx > -1)
            {  // if active component not in list, then set the first list item to the active component
               BEMPX_SetActiveObjectIndex( m_iDBClass, iFirstChildObjIdx );
               bActiveCompReset = TRUE;
               iActiveListIdx = 0;
            }

            if (iActiveListIdx > -1)
            {
               SetItemState( iActiveListIdx, LVIS_SELECTED, LVIS_SELECTED );
               EnsureVisible( iActiveListIdx, FALSE );
            }
         }
         else
         {
            int iNumObjs = BEMPX_GetNumObjects( m_iDBClass );
//            ASSERT( (iActiveObjIdx >= 0 && iActiveObjIdx < iNumObjs) );
            for (int idx=0; idx<iNumObjs; idx++)
            {
            //   if (BEMPX_SetDataStringAndStatus( m_lDBID, sData, iStatus, TRUE, 0 /*m_lValue*/, -1, idx ))
               sData = BEMPX_GetStringAndStatus( m_lDBID, iStatus, iSV, iError, idx );
               if (iStatus > 0 && !sData.isEmpty())
               {
                  if (InsertItem( iListIdx, sData.toLatin1().constData() ) > -1  &&  SetItemData( iListIdx, (DWORD) idx ))
                  {
                     if (idx == iActiveObjIdx)
                        iActiveListIdx = iListIdx;
                     iListIdx++;
                  }
               }
            }
            SetColumnWidth( 0, LVSCW_AUTOSIZE );

            if (iActiveListIdx > -1)
            {
               SetItemState( iActiveListIdx, LVIS_SELECTED, LVIS_SELECTED );
               EnsureVisible( iActiveListIdx, FALSE );
            }
         }
      }
      m_bUpdatingList = FALSE;

      SetRedraw();
      Invalidate();

      if (bActiveCompReset)
      {
         // Post-processing following mods
         m_bSettingHighlight = TRUE;
         GetParent()->SendMessage( WM_DATAMODIFIED );
         m_bSettingHighlight = FALSE;
      }
   }

   return 1;
}


// SAC 6/13/00 - added to process changes in the "currently active item"
void CBEMProcCtrlList::OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
   if (!m_bUpdatingList  &&  pNMListView->uChanged & LVIF_STATE  &&  pNMListView->uNewState & LVIS_SELECTED)
   {
      // items are loaded into list in iObjIdx order, so the list index should map directly to iObjIdx values
//      BEMPX_SetActiveObjectIndex( m_iDBClass, pNMListView->iItem );
// SAC 3/30/02 - With the addition of lists of child objects, we can no longer rely on the index of the item in the list corresponding with that items BEMProc object index
      BEMPX_SetActiveObjectIndex( m_iDBClass, (int) GetItemData( pNMListView->iItem ) );

      // Post-processing following mods
      m_bSettingHighlight = TRUE;
      GetParent()->SendMessage( WM_DATAMODIFIED );
      m_bSettingHighlight = FALSE;
   }

	*pResult = 0;
}


void CBEMProcCtrlList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   BOOL bKeyProcessed = FALSE;
   POSITION pos = GetFirstSelectedItemPosition();
   if (pos)
   {
      int iCurSelItemIdx = GetNextSelectedItem(pos);
      int iNumItems      = GetItemCount();
      int iNewSelItem    = -1;

      switch (nChar)
      {
         case VK_DOWN   :  iNewSelItem = iCurSelItemIdx + 1;
                           break;
         case VK_UP     :  iNewSelItem = iCurSelItemIdx - 1;
                           break;
         case VK_RIGHT  :  if (m_iNumColumns == 1)
                              iNewSelItem = iCurSelItemIdx + 1;
                           break;
         case VK_LEFT   :  if (m_iNumColumns == 1)
                              iNewSelItem = iCurSelItemIdx - 1;
                           break;
         case VK_HOME   :  iNewSelItem = 0;
                           break;
         case VK_END    :  iNewSelItem = iNumItems - 1;
                           break;
      }

      if (iNewSelItem != iCurSelItemIdx  &&  iNewSelItem >= 0  &&  iNewSelItem < iNumItems)
      {
         bKeyProcessed = TRUE;
         EnsureVisible( iNewSelItem, FALSE );
         SetItemState(  iNewSelItem, LVIS_SELECTED, LVIS_SELECTED );
      }
   }

   if (!bKeyProcessed)
      CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CBEMProcCtrlList::OnLButtonDown( UINT /*nFlags*/, CPoint point ) 
{
   SetFocus();
   UINT uiFlags;
   int iHitItem = HitTest( point, &uiFlags );
   if (uiFlags & LVHT_ONITEM)
   {
      POSITION pos = GetFirstSelectedItemPosition();
      if (pos)
      {
         int iCurSelItemIdx = GetNextSelectedItem(pos);
         if (iHitItem != iCurSelItemIdx)
         {
            EnsureVisible( iHitItem, FALSE );
            SetItemState(  iHitItem, LVIS_SELECTED, LVIS_SELECTED );
         }
      }      
   }
	
//	CListCtrl::OnLButtonDown(nFlags, point);
}

// SAC 3/31/02 - added double click processing to streamline navigation
void CBEMProcCtrlList::OnLButtonDblClk( UINT /*nFlags*/, CPoint point )
{
   if (m_iNavigationID > 0)
   {
      UINT uiFlags;
      int iHitItem = HitTest( point, &uiFlags );
      if (uiFlags & LVHT_ONITEM)
      {
         int iSelItemObjIdx = (int) GetItemData( iHitItem );

         int iError;
         BEMClass* pClass = BEMPX_GetClass( m_iDBClass, iError );
         ASSERT( pClass != NULL );
         ASSERT( pClass->getCurrentBEMObjType() == BEMO_User );
         if (pClass)
         {
            int iActiveObjIdx = pClass->getCurrentBEM0ObjIdx();
            if (iSelItemObjIdx == iActiveObjIdx)
            {
// testing
//               CString sMsg;
//               sMsg.Format( "Double clicked on item #%d => navigation ID %d.", iHitItem, m_iNavigationID );
//               MessageBox( sMsg );

               int iBtnPressRetVal = GetParentFrame()->SendMessage( WM_BUTTONPRESSED, MAKEWPARAM( (WORD) m_iNavigationID, 0 ), (long) GetParent() );
               if (iBtnPressRetVal > 0)
               {
                  // Post-processing following mods
//                  m_bUpdatingData = TRUE;  // SAC 2/5/99
//                  GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lDBID );
//                  m_bUpdatingData = FALSE;  // SAC 2/5/99
                  m_bSettingHighlight = TRUE;
                  GetParent()->SendMessage( WM_DATAMODIFIED );
                  m_bSettingHighlight = FALSE;
               }
            }
         }
      }
   }
}
