// CUILibView.cpp : implementation file
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

#include "ComplianceUIDoc.h"
#include "CUILibView.h"

#include "CUIGlobl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCUILibView

IMPLEMENT_DYNCREATE(CCUILibView, CView)

CCUILibView::CCUILibView()
{
   m_bTreeInitialized = FALSE;

   // Create font for messages and button text
   m_fntViewFont.CreateFont( 17,  // height
                             0, 0, 0,              // width, escapement, orientation
                             650, 0, 0, 0,         // weight, ital, undrln, strike
                             ANSI_CHARSET,              // char set
                             OUT_DEFAULT_PRECIS,        // out precision
                             CLIP_DEFAULT_PRECIS,       // clip precision
                             PROOF_QUALITY,             // quality
                             FF_SWISS,                  // pitch & family
                             "Arial" );                    // font name
//                             "Verdana" );                    // font name
}

CCUILibView::~CCUILibView()
{
}


BEGIN_MESSAGE_MAP(CCUILibView, CView)
	//{{AFX_MSG_MAP(CCUILibView)
	ON_WM_SIZE()
   ON_MESSAGE( WM_POPLIBTREE,  OnPopulateLibraryTree )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCUILibView drawing

void CCUILibView::OnDraw(CDC* pDC)
{
	CComplianceUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   CRect rc;
   GetClientRect(rc);
   pDC->SetBkColor(   ::GetSysColor( COLOR_BTNFACE ) );
   pDC->SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
   //   if (!m_bControlsCreated)
   pDC->ExtTextOut(8, 0, ETO_OPAQUE, rc, " ", 1, NULL);
   pDC->SetBkMode( TRANSPARENT );

   CFont* pPrevFont = pDC->SelectObject( &m_fntViewFont );
   pDC->TextOut( 10, 5, m_sViewTitle );
   pDC->SelectObject( pPrevFont );

//   if ( (rc.Width() > 40) && (rc.Height() > 80) )
//   {
//      pDC->SelectObject( &btnHighlightPen );
//      pDC->SelectObject( &whiteBrush );
//      pDC->Rectangle( 15, 32, rc.Width() - 15, rc.Height() - 15 );
//      DrawWin95Shadow( pDC, 15, 32, rc.Width() - 15, rc.Height() - 15 );
//   }
}

/////////////////////////////////////////////////////////////////////////////
// CCUILibView diagnostics

#ifdef _DEBUG
void CCUILibView::AssertValid() const
{
	CView::AssertValid();
}

void CCUILibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComplianceUIDoc* CCUILibView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)));
	return (CComplianceUIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCUILibView message handlers

void CCUILibView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnBeginPrinting(pDC, pInfo);
}

void CCUILibView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnEndPrinting(pDC, pInfo);
}

BOOL CCUILibView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	
	return CView::OnPreparePrinting(pInfo);
}

void CCUILibView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
   if (!m_bTreeInitialized)
   {
      m_bTreeInitialized = TRUE;

      // create tree and set its font
      m_BDBTree.Create( CRect(30, 30, 70, 70), this, IDC_LIBTREE, FALSE );
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
      m_BDBTree.PopulateBDBTree( TM_Project );
   }
}

void CCUILibView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
   if (m_bTreeInitialized)
   {
      if ( (cx > 40) && (cy > 80) )
      {
         // resize tree control
         m_BDBTree.SetWindowPos( NULL, 15, 25, cx-30, cy-40, SWP_NOZORDER );
   //      m_BDBTree.PopulateBDBTree( m_TabCtrl.GetCurSel() );
   //      m_BDBTree.RedrawWindow( NULL, NULL, RDW_UPDATENOW );
         m_BDBTree.ShowWindow( SW_SHOW );

         // resize tab control
   //      m_TabCtrl.SetWindowPos( NULL, 15, 15, cx-30, cy-30, SWP_NOACTIVATE | SWP_NOZORDER );
      }
      else
         m_BDBTree.ShowWindow( SW_HIDE );
   }
}


afx_msg LONG CCUILibView::OnPopulateLibraryTree(UINT uiTreeMode, LONG lOnlyIfRequired)
{
   // populate tree
   m_BDBTree.PopulateBDBTree( (int) uiTreeMode, (lOnlyIfRequired > 0) );
   return 1;
}

BOOL CCUILibView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   if (m_BDBTree.OnCmdMsg( nID, nCode, pExtra, pHandlerInfo)) 
   {
      return TRUE;
   }
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
