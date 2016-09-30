// ViewErrorList.cpp : implementation file
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

#include "ViewErrorList.h"
#include "DlgErrorList.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "Screens.h"
#include "BPUICtl_edit.h"

#include "BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Initialize the static variable that has the starting ID for all of the edit controls to be created
UINT CViewErrorList::editStartID = 1000;

/////////////////////////////////////////////////////////////////////////////
// CViewErrorList

IMPLEMENT_DYNCREATE(CViewErrorList, CFormView)
//IMPLEMENT_DYNCREATE(CViewErrorList, CScrollView)

CViewErrorList::CViewErrorList() 
	: CFormView(CViewErrorList::IDD)
{
	//{{AFX_DATA_INIT(CViewErrorList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
   m_iParentCID = -1;  // If this member is set to -1 then we do all of the 

   // CRect that contains the current size of the CEditCtls (in FontX() and FontY() converted units)
   m_szEdit.cx = FontX(550); // Initially set to the minimum view size allowable from the minimum size restriction of CDlgErrorList
   m_szEdit.cy = FontY(60);
}

CViewErrorList::~CViewErrorList()
{
}

void CViewErrorList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewErrorList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewErrorList, CFormView)
	//{{AFX_MSG_MAP(CViewErrorList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
// RW 12/18/02 - Changed the Range macro to include all controls that send an EN_CHANGE message, cleaner this way
//             - since it is technically possible for there to be more than 100 created, I suppose...
	//ON_CONTROL_RANGE(EN_CHANGE, 0, 0xFFFFFFFF, OnChangeComment)
	ON_CONTROL_RANGE(EN_CHANGE, 0, 0xFFFF, OnChangeComment)
//	ON_CONTROL_RANGE(EN_CHANGE, CViewErrorList::editStartID, CViewErrorList::editStartID+100, OnChangeComment)
// RW 12/18/02 - Quick fix possibility below where we individually setup a macro for each possible control
//	ON_EN_CHANGE(CViewErrorList::editStartID, OnChangeComment)
//	ON_EN_CHANGE(CViewErrorList::editStartID+1, OnChangeComment)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewErrorList drawing

void CViewErrorList::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// Remove WS_EX_CLIENTEDGE in order to eliminate depressed border around view inside tab
//	ModifyStyleEx( WS_EX_CLIENTEDGE, 0 );

// Here we want to get all of the error/warning messages and output them to the screen as CStatic objects.
// In addition, we also want to get all of the user warning comments and put them on the screen as CEdit objects.
   
   CRect winRect;
   GetClientRect( winRect );
   CSize sz = winRect.Size();
   CSize szPage((int)(sz.cx*0.85), (int)(sz.cy*0.85));
   CSize szLine;
   szLine.cx = (sz.cx/10 > 0)? sz.cx / 10 : 1;
   szLine.cy = (sz.cy/10 > 0)? sz.cy / 10 : 1;
   SetScrollSizes(MM_TEXT, GetTotalSize(), szPage, szLine);

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

   BOOL bAllowContinue = TRUE;

   int iNumWarningObjs = BEMPX_GetNumObjects( iWarnCompID );
   if( m_iParentCID > 0 )
      iNumWarningObjs = (int) BEMPX_GetNumChildren( m_iParentCID, -1, BEMO_User, iWarnCompID);

   for (int iWarn=0; iWarn<iNumWarningObjs; iWarn++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0WarnIdx = iWarn;

      if( m_iParentCID > 0 )
         i0WarnIdx = BEMPX_GetChildObjectIndex( m_iParentCID, iWarnCompID, iError, eChildObjType, iWarn+1);

      if (i0WarnIdx >= 0)
      {
         CString sWarnType;
         BEMPX_SetDataString( lDBIDWarnType,    sWarnType, FALSE, 0, BEMP_Sym, i0WarnIdx );

         if( !sWarnType.CompareNoCase(_T("Warning")) )
         {
            // the user needs to enter in an explanation for the warning so lets create an CEditCtrl control in which
            // we are going to contain the user comment.  The location does not matter at this point as it will be moved 
            // during the OnDraw process to its correct location.
            CEditCtl* pCtrl = new CEditCtl();
            if( !pCtrl->Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN,
                       CRect( CPoint(FontX(5), FontY(5)), m_szEdit ),
                       this, CViewErrorList::editStartID+iWarn, FNT_VD_STD, -1, 
                       _T("User Explanation/Comment: "), lDBIDWarnComment, BEMP_Str, 0, 0, FALSE, i0WarnIdx ) )
            {
               CString sMsg;
               sMsg.Format( "Unable to create an edit control for warning comment #%d", i0WarnIdx+1);
               TRACE( sMsg );
            }
            m_aWarningComments.Add(pCtrl);

            CString sWarnComment;
            BEMPX_SetDataString( lDBIDWarnComment,    sWarnComment, FALSE, 0, BEMP_Str, i0WarnIdx );
            if( sWarnComment.GetLength() == 0)
               bAllowContinue = FALSE;
         }
      }
   }
   ((CDlgErrorList*)GetParent())->AllowContinue(bAllowContinue);
}

void CViewErrorList::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
   CRect clientRect;
   GetClientRect(&clientRect);

	CFont* pTempFont = (CFont*)pDC->SelectObject( GetWizFont( FNT_VD_STD ) );
   CFont oldFont;
   oldFont.FromHandle( (HFONT)pTempFont );
   COLORREF crfProject = ::GetSysColor( COLOR_WINDOWTEXT );
   pDC->SetTextColor(crfProject);                           
   pDC->SetBkMode(TRANSPARENT);

	// TODO: add draw code here
   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   long lDBIDWarnMessage = BEMPX_GetDatabaseID("WarnMsg",   iWarnCompID );
   long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

   int iNumWarningObjs = BEMPX_GetNumObjects( iWarnCompID );
   if( m_iParentCID > 0 )
      iNumWarningObjs = (int) BEMPX_GetNumChildren( m_iParentCID, -1, BEMO_User, iWarnCompID);

   int iNumWarnings = 0;
   CRect outputRect( 20, 5, clientRect.Width()-FontX(40), 25);
   //int iCommentOffset = FontX(20);

   for (int iWarn=0; iWarn<iNumWarningObjs; iWarn++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0WarnIdx = iWarn;

      if( m_iParentCID > 0 )
         i0WarnIdx = BEMPX_GetChildObjectIndex( m_iParentCID, iWarnCompID, iError, eChildObjType, iWarn+1);

      if (i0WarnIdx >= 0)
      {
         CString sWarnType;
         BEMPX_SetDataString( lDBIDWarnType,    sWarnType, FALSE, 0, BEMP_Sym, i0WarnIdx );

         CString sWarnMessage;
         BEMPX_SetDataString( lDBIDWarnMessage,    sWarnMessage, FALSE, 0, BEMP_Str, i0WarnIdx );
         sWarnMessage = sWarnType + _T(": ") + sWarnMessage;

         // Draw the warning message here, change the width of the outputRect to correspond with the client window
         DrawMessage( pDC, sWarnMessage, outputRect, DT_LEFT|DT_WORDBREAK);
         outputRect.right = clientRect.Width()-FontX(40);
         if( iWarn < iNumWarningObjs-1 || !sWarnType.CompareNoCase(_T("Warning")) )
         {
            if( outputRect.Height() < 20 )
               outputRect.bottom = outputRect.top + FontY(20);
            outputRect.OffsetRect(0, outputRect.Height() ); // +FontY(20));
         }

         if( !sWarnType.CompareNoCase(_T("Warning")) )
         {
            CEditCtl* pComment = (iNumWarnings < m_aWarningComments.GetSize()) ? m_aWarningComments[iNumWarnings] : NULL;

            if( pComment )
            {
               CRect rctComment(outputRect);
               rctComment.OffsetRect(FontX(20),0);
               DrawMessage( pDC, _T("User Explanation/Comment:"), rctComment);
               outputRect.OffsetRect(0, rctComment.Height() );

               CString sWarnComment;
               BEMPX_SetDataString( lDBIDWarnComment,    sWarnComment, FALSE, 0, BEMP_Str, i0WarnIdx );
               CPoint ptOffset = GetDeviceScrollPosition();
               pComment->MoveWindow(outputRect.left+FontX(40), outputRect.top - ptOffset.y, clientRect.Width()-FontX(80), FontY(60));
               pComment->SendMessage(WM_DISPLAYDATA);

               if( iWarn < iNumWarningObjs-1 )
                  outputRect.OffsetRect(0, FontY(90));
            }

            iNumWarnings++;
         }
      }
   }

// TO DO - Fix the setting of the scroll sizes
   CRect rect(0,0,clientRect.Width(), outputRect.bottom + FontY(40));
	CSize sizeTotal(rect.Size());

	SetScrollSizes(MM_TEXT, sizeTotal);
   pDC->SelectObject( oldFont );
}

void CViewErrorList::DrawMessage( CDC* pDC, CString sText, CRect& outputRect, UINT nFormat)
{
   int iBottomSave = outputRect.bottom;
   int iCenterShift = 0;
   if( (nFormat & DT_CENTER) )
   {
	   pDC->DrawText(sText, outputRect, nFormat|DT_CALCRECT);
      iCenterShift = outputRect.Width() / 2;
      outputRect.bottom = iBottomSave;
   }
   else if( !(nFormat & DT_WORDBREAK) )
      outputRect.right = outputRect.left + pDC->GetTextExtent(sText).cx;
   else
   {
	   pDC->DrawText(sText, outputRect, nFormat|DT_CALCRECT);
   }

   int iNonSingleLineShift = 0;
   if( !(nFormat&DT_SINGLELINE) )
      iNonSingleLineShift = 4;

   outputRect.OffsetRect(-iCenterShift, iNonSingleLineShift);

	pDC->DrawText(sText, outputRect, nFormat);
   outputRect.OffsetRect(iCenterShift, -iNonSingleLineShift);
}

/////////////////////////////////////////////////////////////////////////////
// CViewErrorList diagnostics

#ifdef _DEBUG
void CViewErrorList::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewErrorList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewErrorList message handlers

int CViewErrorList::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int nResult = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
		return nResult;   // frame does not want to activate

	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame != NULL)
	{
		// eat it if this will cause activation
//		ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

		// either re-activate the current view, or set this view to be active
		CView* pView = pParentFrame->GetActiveView();
		HWND hWndFocus = ::GetFocus();
		if (pView == this &&
			m_hWnd != hWndFocus && !::IsChild(m_hWnd, hWndFocus))
		{
			// re-activate this view
			OnActivateView(TRUE, this, this);
		}
//		else
//		{
//			// activate this view
//			   pParentFrame->SetActiveView(this);
//		}
	}
	return nResult;
}


void CViewErrorList::SetCommentFocus(int iCtrlIdx)
{
   CEditCtl* pComment = (iCtrlIdx < m_aWarningComments.GetSize()) ? m_aWarningComments[iCtrlIdx] : NULL;

   if( pComment )
      pComment->SetFocus();
}

void CViewErrorList::OnChangeComment(UINT nID)
{
// RW 12/18/02 - Here is the fix to the release mode bomb... apparently, the range was being called for controls
// other than CEditCtl, since control notifications are unique only to a particular kind of control. Buttons 
// or combo boxes or flibbertiwidgets are free to use the same numeric values for their notifications as those 
// used by other controls.  To prevent this, we pass in the control ID and then confirm that it is, in fact,
// a CEditCtl before continuing on with the routine.
   if( !((GetDlgItem(nID))->IsKindOf( RUNTIME_CLASS(CEditCtl))) )
      return;

   BOOL bAllow = TRUE;

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   //long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

   int iNumWarningObjs = BEMPX_GetNumObjects( iWarnCompID );
   if( m_iParentCID > 0 )
      iNumWarningObjs = (int) BEMPX_GetNumChildren( m_iParentCID, -1, BEMO_User, iWarnCompID);

   int iWarningNum = 0;

   for (int iWarn=0; iWarn<iNumWarningObjs; iWarn++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0WarnIdx = iWarn;

      if( m_iParentCID > 0 )
         i0WarnIdx = BEMPX_GetChildObjectIndex( m_iParentCID, iWarnCompID, iError, eChildObjType, iWarn+1);

      if (i0WarnIdx >= 0)
      {
         CString sWarnType;
         BEMPX_SetDataString( lDBIDWarnType,    sWarnType, FALSE, 0, BEMP_Sym, i0WarnIdx );

         if( !sWarnType.CompareNoCase(_T("Warning")) )
         {
            CEditCtl* pComment = (iWarningNum < m_aWarningComments.GetSize()) ? m_aWarningComments[iWarningNum] : NULL;
            ASSERT(pComment != NULL);
            CString sNewComment = _T("");
            if (pComment != NULL)
               pComment->GetWindowText(sNewComment);

            if( sNewComment.GetLength() == 0)
               bAllow = FALSE;

            iWarningNum++;
         }
      }
   }
   ((CDlgErrorList*)GetParent())->AllowContinue(bAllow);
}

void CViewErrorList::ApplyDefault()
{
   int iProjCompID       = BEMPX_GetDBComponentID( "Proj" );
   long lDBIDDfltExpln   = BEMPX_GetDatabaseID("DfltExplanation",   iProjCompID );
   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

   CString sDefault;
   BEMPX_SetDataString( lDBIDDfltExpln,    sDefault, FALSE, 0, BEMP_Str );

   int iNumWarningObjs = BEMPX_GetNumObjects( iWarnCompID );
   if( m_iParentCID > 0 )
      iNumWarningObjs = (int) BEMPX_GetNumChildren( m_iParentCID, -1, BEMO_User, iWarnCompID);

   int iWarningNum = 0;

   for (int iWarn=0; iWarn<iNumWarningObjs; iWarn++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0WarnIdx = iWarn;

      if( m_iParentCID > 0 )
         i0WarnIdx = BEMPX_GetChildObjectIndex( m_iParentCID, iWarnCompID, iError, eChildObjType, iWarn+1);

      if (i0WarnIdx >= 0)
      {
         CString sWarnType;
         BEMPX_SetDataString( lDBIDWarnType,    sWarnType, FALSE, 0, BEMP_Sym, i0WarnIdx );

         if( !sWarnType.CompareNoCase(_T("Warning")) )
         {
            CEditCtl* pComment = (iWarningNum < m_aWarningComments.GetSize()) ? m_aWarningComments[iWarningNum] : NULL;
            ASSERT(pComment != NULL);
            CString sNewComment = _T("");
            if (pComment != NULL)
               pComment->GetWindowText(sNewComment);

            if( sNewComment.GetLength() == 0)
            {
               pComment->SetWindowText(sDefault);
               BEMPX_SetBEMData( lDBIDWarnComment, BEMP_Str, (void*) ((const char*)sDefault), BEMO_User, i0WarnIdx );
            }

            iWarningNum++;
         }
      }
   }
}
