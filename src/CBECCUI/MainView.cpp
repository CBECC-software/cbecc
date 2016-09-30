// MainView.cpp : implementation file
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
#include "ComplianceUI.h"
#include "MainView.h"
#include "CUIGlobl.h"
#include "Resource.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
   : CFormView(CMainView::IDD)
{
   //{{AFX_DATA_INIT(CMainView)
      // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT

   m_bTabInitialized = FALSE;
   eiCurrentTab = 0;
   m_iTabData = 0;  // value indicating which tabs are present based on which bits are set
}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
   CFormView::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMainView)
   DDX_Control(pDX, IDC_MAINTAB, m_TabCtrl);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainView, CFormView)
   //{{AFX_MSG_MAP(CMainView)
   ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnSelchangeMaintab)
   ON_WM_SIZE()
   ON_MESSAGE( WM_UPDATETREE,  OnUpdateTree )
   ON_MESSAGE( WM_DISPLAYDATA, OnDisplayData )
   ON_MESSAGE( WM_UPDATETABS,  OnUpdateTabs )
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
   CFormView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
   CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

#ifdef UI_ASHRAE901E
static int siNumTabs = 4;
static char* pszTabLabels[] = { "  Project  " , "  Architecture  ", "  Lighting  ", "  Mechanical  " };
#elif UI_CARES
static int siNumTabs = 2;
static char* pszTabLabels[] = { "  Envelope  ", "  Mechanical  " };
#elif UI_CANRES
static int siNumTabs = 2;
static char* pszTabLabels[] = { "  Envelope  ", "  Mechanical  " };
#endif

LONG CMainView::OnUpdateTabs( UINT, LONG )
{
   int iRetVal = 0;
   if (m_bTabInitialized)
   {
      int iTabData = BEMPUIX_GetMainScreenInfo();
      ASSERT( iTabData > 0 );

      if (m_iTabData != iTabData)
      {
         m_iTabData = iTabData;

         // first switch the active tab if it is about to be deleted
         int iCurTabIdx  = m_TabCtrl.GetCurSel();
         int iCurTabID   = GetTabID( iCurTabIdx );
         int iCurTabData = (int) pow( (double) 2, iCurTabID );
         int iNewCurTabIdx = -1;
         if (!(iCurTabData & iTabData))
         {  // switch active tab to previous which will still be around
            for (int i=iCurTabIdx-1; (iNewCurTabIdx < 0 && i >= 0); i--)
            {
               int iNewTabID   = GetTabID( i );
               int iNewTabData = (int) pow( (double) 2, iNewTabID );
               if (iNewTabData & iTabData)
                  iNewCurTabIdx = i;
            }
            ASSERT( iNewCurTabIdx >= 0 );
            m_TabCtrl.SetCurSel( iNewCurTabIdx );
         }

         // now loop over all possible tabs, adding those which need adding and removing those which require removing
         int iTempTabIdx = 0;
         int iNumTabs = m_TabCtrl.GetItemCount();
         TC_ITEM TabCtrlItem;
         for (int i=0; i<siNumTabs; i++)
         {
            int iTempTabID   = (iTempTabIdx < iNumTabs ? GetTabID( iTempTabIdx )    : -1);
            int iTempTabData = (iTempTabIdx < iNumTabs ? (int) pow( (double) 2, iTempTabID ) : -1);
            int iThisTabData = (int) pow( (double) 2, i );

            // first handle new tab additions
            if ((iTempTabIdx >= iNumTabs || iTempTabID > i) && (iThisTabData & iTabData))
            {  // add new tab, incrament iNumTabs and iTempTabIdx
               TabCtrlItem.mask = TCIF_TEXT | TCIF_PARAM;
               TabCtrlItem.pszText = pszTabLabels[i];
               TabCtrlItem.lParam  = i;
               m_TabCtrl.InsertItem( iTempTabIdx, &TabCtrlItem );
               iNumTabs++;
               iTempTabIdx++;
            }
            // then deal with tab deletions
            else if (iTempTabID >= 0 && !(iTempTabData & iTabData))
            {  // delete tab, decrement iNumTabs and leave iTempTabIdx as is
               m_TabCtrl.DeleteItem( iTempTabIdx );
               iNumTabs--;
            }
            else if (iTempTabID <= i)
               iTempTabIdx++;
         }
         iRetVal = iNumTabs;

         // finally, if we switched the active tab, then reset other portions of main screen as if the user clicked the new active tab
         if (iNewCurTabIdx >= 0)
         {
            eiCurrentTab = iNewCurTabIdx;
            m_BDBTree.PopulateBDBTree( eiCurrentTab );
            GetParentFrame()->SendMessage( WM_POPLIBTREE, eiCurrentTab );
         }
      }
   }

   return iRetVal;
}


int CMainView::GetTabID( int iTabIdx )
{
   int iRetVal = -1;
//   eiCurrentTab = m_TabCtrl.GetCurSel();
   // SAC 1/31/99 - replaced above with below to utilize TabCtrlItem data rather than relying on tab's index
   TC_ITEM TabCtrlItem;
   TabCtrlItem.mask = TCIF_PARAM;
   if (iTabIdx < 0)
      iTabIdx = m_TabCtrl.GetCurSel();
   if (m_TabCtrl.GetItem( iTabIdx, &TabCtrlItem ))
      iRetVal = TabCtrlItem.lParam;
   ASSERT( iRetVal >= 0 );
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

void CMainView::OnSelchangeMaintab(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
   eiCurrentTab = GetTabID();
   m_BDBTree.PopulateBDBTree( eiCurrentTab );
   GetParentFrame()->SendMessage( WM_POPLIBTREE, eiCurrentTab );
   
   *pResult = 0;
}

void CMainView::OnInitialUpdate() 
{
   CFormView::OnInitialUpdate();
   
   if (!m_bTabInitialized)
   {
      m_iTabData = BEMPUIX_GetMainScreenInfo();  // value indicating which tabs are present based on which bits are set
      ASSERT( m_iTabData > 0 );

      m_TabCtrl.SetFont( GetCUIFont(FNT_STD), FALSE );
      TC_ITEM TabCtrlItem;
      TabCtrlItem.mask = TCIF_TEXT | TCIF_PARAM;
      int iTabIdx = 0;
      for (int i=0; i<siNumTabs; i++)
      {
         int iThisTabData = (int) pow( (double) 2, i );
         if (iThisTabData & m_iTabData)
         {
            TabCtrlItem.pszText = pszTabLabels[i];
            TabCtrlItem.lParam  = i;
            m_TabCtrl.InsertItem( iTabIdx++, &TabCtrlItem );
         }
      }
//      TabCtrlItem.pszText = "  Project  ";
//      TabCtrlItem.lParam  = 0;
//      m_TabCtrl.InsertItem( 0, &TabCtrlItem );
//      TabCtrlItem.pszText = "  Architecture  ";
//      TabCtrlItem.lParam  = 1;
//      m_TabCtrl.InsertItem( 1, &TabCtrlItem );
//      TabCtrlItem.pszText = "  Lighting  ";
//      TabCtrlItem.lParam  = 2;
//      m_TabCtrl.InsertItem( 2, &TabCtrlItem );
//      TabCtrlItem.pszText = "  Mechanical  ";
//      TabCtrlItem.lParam  = 3;
//      m_TabCtrl.InsertItem( 3, &TabCtrlItem );

      m_bTabInitialized = TRUE;

      // create tree and set its font
      m_BDBTree.Create( CRect(30, 30, 70, 70), this, IDC_BDBTREE );
      m_BDBTree.SetFont( GetCUIFont(FNT_STD), FALSE );

      // create imagelist for the tree control and load bitmaps into the image list
      CImageList* pimagelist = new CImageList();
      pimagelist->Create( 16, 16, ILC_MASK, (IDB_TREELAST-IDB_TREEFIRST+1), 4 );
      CBitmap bitmap;
      for (UINT nID = IDB_TREEFIRST; nID <= IDB_TREELAST; nID++)  // load bitmaps
      {
         bitmap.LoadBitmap(nID);
         pimagelist->Add(&bitmap, (COLORREF)0xFFFFFF);
         bitmap.DeleteObject();
      }
      m_BDBTree.SetImageList(pimagelist, TVSIL_NORMAL);

      // populate tree
      eiCurrentTab = GetTabID();
//      eiCurrentTab = m_TabCtrl.GetCurSel();
      m_BDBTree.PopulateBDBTree( eiCurrentTab );
   }
}

void CMainView::OnSize(UINT nType, int cx, int cy) 
{
   CFormView::OnSize(nType, cx, cy);
   
   if (m_bTabInitialized)
   {
      // resize tab control
      m_TabCtrl.SetWindowPos( NULL, 10, 10, cx-20, cy-20, SWP_NOACTIVATE | SWP_NOZORDER );

      // resize tree control
//      m_BDBTree.SetWindowPos( &m_TabCtrl, 20, 15+eiTabDlgCtrlDY, cx-40, cy-35-eiTabDlgCtrlDY,
//                              SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW );
//                              SWP_NOZORDER | SWP_SHOWWINDOW );
//                              SWP_NOACTIVATE | SWP_NOZORDER );
// Last Version:
//                              SWP_NOZORDER );
//                              SWP_NOACTIVATE | SWP_SHOWWINDOW );
      m_BDBTree.SetWindowPos( &wndTop, 20, 15+eiTabDlgCtrlDY, cx-40, cy-35-eiTabDlgCtrlDY, SWP_SHOWWINDOW );

//      m_BDBTree.PopulateBDBTree( m_TabCtrl.GetCurSel() );
//      m_BDBTree.RedrawWindow( NULL, NULL, RDW_UPDATENOW );

//      // resize tab control
//      m_TabCtrl.SetWindowPos( NULL, 10, 10, cx-20, cy-20, SWP_NOACTIVATE | SWP_NOZORDER );
   }
}

LONG CMainView::OnUpdateTree(UINT, LONG lDBIDModified)
{
   m_BDBTree.CheckAndUpdateTree( lDBIDModified );
   return 1;
}

LONG CMainView::OnDisplayData(UINT uiBDBClass, LONG lOnlyIfRequired)
{
   if (m_bTabInitialized)
   {
      eiCurrentTab = GetTabID();
//      eiCurrentTab = m_TabCtrl.GetCurSel();
      m_BDBTree.PopulateBDBTree( eiCurrentTab, (int) uiBDBClass, (lOnlyIfRequired > 0) );
      m_BDBTree.RedrawWindow( NULL, NULL, RDW_UPDATENOW );
   }

   return 1;
}

// RFH Route command messages to the tree. This allowed me to handle
// OnEditCopy in the tree.
BOOL CMainView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   if (m_BDBTree.OnCmdMsg( nID, nCode, pExtra, pHandlerInfo)) 
   {
      return TRUE;
   }
   return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
