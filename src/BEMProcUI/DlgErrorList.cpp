// DlgErrorList.cpp: implementation of the CDlgErrorList class.
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

#include "BEMProcUIX.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\expRanges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//IMPLEMENT_DYNAMIC( CDlgErrorList, CResizableDialog )


// Un-adjusted coordinates/positions/sizes
#define  DPRS_COORD_DLGWD    795
#define  DPRS_COORD_DLGHT    590
#define  DPRS_COORD_SMDLGWD  635
#define  DPRS_COORD_SMDLGHT  470
#define  DPRS_COORD_CTRLTOP   20

// Resource-size-adjusted coordinates/positions/sizes
static int siDlgWd = 0;
static int siDlgHt = 0;

static UINT uiFloorPlanCtrlID = 203;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgErrorList::CDlgErrorList( CPoint ptTopLeftOffset, CPoint ptBottomRightOffset,
                              CString sTitle, int iParentCID, CRect* pRect, CWnd* pParent /*=NULL*/, const char* pszRangeLabel,
                              const char* pszRangePrompt, BOOL bAllowContinue, int iDlgMode /*=SWDM_Default*/, UINT uiIconResourceID /*=0*/ )
	: CResizableDialog( CDlgErrorList::IDD, pParent )
{
   m_sSection = sTitle;
	//{{AFX_DATA_INIT(CDlgErrorList)
   m_bCreateControls = TRUE;
	//}}AFX_DATA_INIT
   if( pRect != NULL )
   {
      m_wndRect.CopyRect(pRect);
      m_wndRect.NormalizeRect();
   }
   else
      m_wndRect.SetRectEmpty();

   m_sKey = _T("Window Size");
   m_pViewClass = RUNTIME_CLASS( CViewErrorList );
   m_pDoc = NULL;
   m_pView = NULL;
   m_ptTopLeftViewOffset = ptTopLeftOffset;
   m_ptBottomRightViewOffset = ptBottomRightOffset;

   m_bContinue   = TRUE;  // default action = Continue

   m_sRangeLabel  = pszRangeLabel;   // IDC_RANGE_LABEL
   m_sRangePrompt = pszRangePrompt;  // IDC_RANGE_PROMPT
   m_bAllowContinue = bAllowContinue;
   m_iParentCID = iParentCID;

   m_iDialogMode = iDlgMode;

   m_uiIconResourceID = uiIconResourceID;   // SAC 7/31/03 - Added Icon resource ID to enable display of program icon vs. generic Windows default
}


CDlgErrorList::~CDlgErrorList()
{
}

void CDlgErrorList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgErrorList)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgErrorList, CResizableDialog)
	//{{AFX_MSG_MAP(CDlgErrorList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED( IDOK,     OnOK )
   ON_BN_CLICKED( IDCANCEL, OnCancel )
   ON_BN_CLICKED( IDC_BTN_APPLY_DEFAULT, OnApplyDefault )
END_MESSAGE_MAP()

BOOL CDlgErrorList::OnInitDialog()
{
   CResizableDialog::OnInitDialog();
//	CDialog::OnInitDialog();
   ModifyStyle(0, WS_CLIPCHILDREN);
   // RW 11/26/02 New routines to determine if errors and/or warnings are being displayed
   BOOL bWarningsPresent = WarningsPresent();
   BOOL bErrorsPresent = ErrorsPresent();

   if (m_bCreateControls)
   {
      siDlgWd = GetSystemMetrics(SM_CXFULLSCREEN) - 20;
      siDlgHt = GetSystemMetrics(SM_CYFULLSCREEN) - 40;
      if( !m_wndRect.IsRectEmpty() && siDlgWd > m_wndRect.Width() && siDlgHt > m_wndRect.Height())
      {
         siDlgWd = m_wndRect.Width();
         siDlgHt = m_wndRect.Height();
      }

      MoveWindow( (GetSystemMetrics(SM_CXFULLSCREEN)/2) - (siDlgWd/2), (GetSystemMetrics(SM_CYFULLSCREEN)/2) + FontY(20) - (siDlgHt/2),
                  siDlgWd, siDlgHt, FALSE );

      // RW 11/26/02 Need to keep the m_sSection member the same value as it is used to store the dialog saved width and height in the registry
      if( bErrorsPresent )
      {
         if( bWarningsPresent )
            SetWindowText( _T("Error(s) and Warning(s)") );
         else
            SetWindowText( _T("Error(s)") );
      }
      else
         SetWindowText( m_sSection );

// SAC 7/31/03 - Added Icon resource ID to enable display of program icon vs. generic Windows default
      // Set dialog caption icon (if resource ID defined)
      if (m_uiIconResourceID > 0)
      {
         CWinApp* pApp = AfxGetApp();
         if (pApp)
         {
            HICON hIcon = pApp->LoadIcon( m_uiIconResourceID );
            if (hIcon)
               SetIcon( hIcon, FALSE );
         }
      }

      // SAC 8/16/01 - stuff to provide more intelligent (system font size independent) sizes and positions
      //int iCaptionHt= ::GetSystemMetrics( SM_CYCAPTION );
      CSize edgeSize( ::GetSystemMetrics( SM_CXEDGE ), ::GetSystemMetrics( SM_CYEDGE ) );

      // SAC 12/17/02 - Added adjustment for WinXP taller window captions (pre-WinXP caption heights were ~1.19 x system font height)
      int iOSDY = (int) ( GetSystemMetrics(SM_CYCAPTION) - (fntHtSys * 1.19) + 0.49 );

// SAC 12/17/02 - Reset font of all children (various statics and buttons)
      CFont* pUICtrlFont = GetWizFont( FNT_STD );
      ASSERT( pUICtrlFont );
      if (pUICtrlFont)
      {
         GetDlgItem(IDCANCEL             )->SetFont( pUICtrlFont, FALSE );
         GetDlgItem(IDOK                 )->SetFont( pUICtrlFont, FALSE );
         GetDlgItem(IDC_RANGE_PROMPT     )->SetFont( pUICtrlFont, FALSE );
         GetDlgItem(IDC_RANGE_LABEL      )->SetFont( pUICtrlFont, FALSE );
         GetDlgItem(IDC_BTN_APPLY_DEFAULT)->SetFont( pUICtrlFont, FALSE );
      }

      // Continue button
      GetDlgItem(IDCANCEL)->SetWindowPos( NULL, siDlgWd-FontX(100), siDlgHt-FontY(60)-iOSDY, -1, -1, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER );  // SAC 12/18/02 - Tweak control sizes & positions
      GetDlgItem(IDOK)->SetWindowPos(     NULL, siDlgWd-FontX(180), siDlgHt-FontY(60)-iOSDY, -1, -1, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER );  // SAC 12/18/02 - Tweak control sizes & positions

      // RW 11/26/02 Did some adjustment of the placement for the Static control with the prompt if there are no warnings present
      if( !bWarningsPresent )
         GetDlgItem(IDC_RANGE_PROMPT)->SetWindowPos(   NULL, FontX(22), siDlgHt-FontY(55) -iOSDY, -1, -1, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER );  // SAC 12/18/02 - Tweak control sizes & positions
      else
         GetDlgItem(IDC_RANGE_PROMPT)->SetWindowPos(   NULL, FontX(22), siDlgHt-FontY(128)-iOSDY, -1, -1, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER );  // SAC 12/18/02 - Tweak control sizes & positions

      GetDlgItem(IDC_BTN_APPLY_DEFAULT)->SetWindowPos( NULL, FontX(22), siDlgHt-FontY(60) -iOSDY, -1, -1, SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER );  // SAC 12/18/02 - Tweak control sizes & positions

      if (!m_sRangeLabel.IsEmpty())
         GetDlgItem(IDC_RANGE_LABEL)->SetWindowText( m_sRangeLabel );
      
      if (!m_sRangePrompt.IsEmpty())
         GetDlgItem(IDC_RANGE_PROMPT)->SetWindowText( m_sRangePrompt );

      // RW 11/26/02 - Added an additional check to make sure that the Continue button does not get displayed if any Errors are present
      if (!m_bAllowContinue || bErrorsPresent )
      {
         CWnd* pWnd = GetDlgItem( IDOK );
         if (pWnd)
         {
            pWnd->ShowWindow( SW_HIDE );
            pWnd->EnableWindow( FALSE );
         }

         pWnd = GetDlgItem( IDCANCEL );
         if (pWnd)
         {
            pWnd->SetWindowText( "Return" );
            pWnd->SetFocus();
         }
      }

      ClearDefaults();

      AddAnchor(IDOK, BOTTOM_RIGHT);
      AddAnchor(IDCANCEL, BOTTOM_RIGHT);
      AddAnchor(IDC_RANGE_PROMPT, BOTTOM_LEFT);
      AddAnchor(IDC_BTN_APPLY_DEFAULT, BOTTOM_LEFT);
      
      // RW - The view class being imported is for displaying the exterior facet of the selected zone with the windows and doors
      // in their geometric locations
#ifdef _DEBUG
	   ASSERT_VALID(this);
	   ASSERT(m_pViewClass != NULL);
	   ASSERT(m_pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	   ASSERT(AfxIsValidAddress(m_pViewClass, sizeof(CRuntimeClass), FALSE));
#endif
	   
      CCreateContext context;
		context.m_pCurrentDoc		= GetParentFrame()->GetActiveDocument();
//		context.m_pCurrentDoc		= m_pDoc;
		context.m_pCurrentFrame		= GetParentFrame();
		context.m_pLastView			= NULL;
		context.m_pNewDocTemplate	= NULL;
		context.m_pNewViewClass		= m_pViewClass;
	   
	   CWnd* pWnd;
	   try	{
		   pWnd = (CWnd*)m_pViewClass->CreateObject();
		   if (pWnd == NULL)
			   AfxThrowMemoryException();
	   }
      catch (CException* e) 
      { 
         ASSERT(e->IsKindOf(RUNTIME_CLASS(CException))); 
         UNUSED(e);
		   TRACE0(_T("Out of memory creating a view.\n"));
		   // Note: DELETE_EXCEPTION(e) not required
		   return FALSE;
	   }
		   
	   ASSERT_KINDOF(CWnd, pWnd);
	   ASSERT(pWnd->m_hWnd == NULL);       // not yet created
	   
	   DWORD dwStyle = WS_BORDER|WS_CHILD|WS_VISIBLE; 
      // RW set up the rectangle to be some initially dummy values. These don't matter as we re-size the window immediately following creation
	   CRect rect(0,0,1,1); 

	   // Create with the right size and position
	   if (!pWnd->Create(NULL, NULL, dwStyle, rect, this, 0, &context)) {
		   TRACE0(_T("Warning: couldn't create client pane for view.\n"));
		   // pWnd will be cleaned up by PostNcDestroy
		   return FALSE;
	   }
      // Cast the created window to the custom door/win view
	   m_pView = (CViewErrorList*) pWnd;
      m_pView->m_iParentCID = m_iParentCID;

      CRect wndRect;
   	GetClientRect(&wndRect);
      // RW 11/26/02 Did some adjustment of the size of the error list view if there are no warnings present
	   CRect rcChild( m_ptTopLeftViewOffset.x, m_ptTopLeftViewOffset.y,
                     wndRect.Width()-m_ptBottomRightViewOffset.x,
                     wndRect.Height()-m_ptBottomRightViewOffset.y + (bWarningsPresent ? 0 : FontY(55)));  // SAC 12/18/02 - Tweak control sizes & positions
	   m_pView->MoveWindow(rcChild);

		m_pView->SendMessage(WM_INITIALUPDATE);
	   m_pView->SetScrollSizes(MM_TEXT, rcChild.Size());
		m_pView->EnableWindow(TRUE);
		m_pView->ShowWindow(SW_SHOW);
		m_pView->SetFocus();

   	AddAnchor(m_pView->GetSafeHwnd(), TOP_LEFT, BOTTOM_RIGHT, TRUE);

      m_bCreateControls = FALSE;
   }

	// get desktop size
	CRect rc;
	GetDesktopWindow()->GetClientRect(&rc);

	// set max tracking size to within 15 pixels from the screen
	SetMaxTrackSize(CSize(rc.Width()-15, rc.Height()-15));
   SetMinTrackSize(CSize(560,400));

	// maximized position and size on top of the screen
//	rc.bottom = 100;
	SetMaximizedRect(rc);

   LoadWindowRect();

   // RW 11/26/02 Made it so that the Apply User Default button is only displayed if there are Warnings present.
   if( !bWarningsPresent )
   {
      GetDlgItem( IDC_BTN_APPLY_DEFAULT )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_BTN_APPLY_DEFAULT )->EnableWindow( FALSE );
   }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// used to save/restore window's size and position
// either in the registry or a private .INI file
// depending on your application settings

#define PROFILE_FMT 	_T("%d,%d,%d,%d,%d,%d")

void CDlgErrorList::SaveWindowRect()
{
	CString data;
	WINDOWPLACEMENT wp;

	ZeroMemory(&wp, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wp);
	
	RECT& rc = wp.rcNormalPosition;	// alias

	data.Format(PROFILE_FMT, rc.left, rc.top,
		rc.right, rc.bottom, wp.showCmd, wp.flags);

//   WriteINIString( m_sSection, m_sKey, data);
	AfxGetApp()->WriteProfileString(m_sSection, m_sKey, data);
}

void CDlgErrorList::LoadWindowRect()
{
	CString data;
	WINDOWPLACEMENT wp;

	CRect rect;
	GetDesktopWindow()->GetClientRect(&rect);

	data = AfxGetApp()->GetProfileString(m_sSection, m_sKey);
//   data = ReadINIString(  m_sSection, m_sKey );
	
	if (data.IsEmpty())	// never saved before
		return;
	
	ZeroMemory(&wp, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);

	RECT& rc = wp.rcNormalPosition;	// alias

	if( _stscanf(data, PROFILE_FMT, &rc.left, &rc.top, &rc.right, &rc.bottom, &wp.showCmd, &wp.flags) == 6) 
	{
      // check to make sure that the stored position will fit on the screen to cover the
      // case where the user has changed to a smaller screen resolution from when the dialog size 
      // and position was previously stored.
      if( rc.left <= rect.left || rc.right >= rect.right || 
          rc.top <= rect.top || rc.bottom >= rect.bottom )
      {
         int iDlgWidth = rc.right-rc.left;
         int iDlgHeight = rc.bottom-rc.top;
         if( ( iDlgWidth > rect.Width()) || (iDlgHeight > rect.Height()) )
         {
            rc.left = rect.left + 10;
            rc.right = rect.right - 10;
            rc.top = rect.top + 10;
            rc.bottom = rect.bottom - 40;
         }
         else
         {
            // Move the window position to the center of the screen
            int iWidthOffset = (rect.Width() - iDlgWidth) / 2;
            int iHeightOffset = (rect.Height() - iDlgHeight) / 2;
            rc.left = iWidthOffset;
            rc.right = iDlgWidth + rc.left;
            rc.top = iHeightOffset;
            rc.bottom = iDlgHeight + rc.top;
         }
      }

		SetWindowPlacement(&wp);
	}
}

void CDlgErrorList::OnDestroy() 
{
	CDialog::OnDestroy();
   SaveWindowRect();
}

void CDlgErrorList::OnOK()
{
   if( !AllWarningsCommented() )
   {
      BEMMessageBox(_T("Please enter in a comment for every warning that has occurred."), _T(""));
      return;
   }

   CResizableDialog::OnOK();
}

void CDlgErrorList::OnCancel()
{
   m_bContinue = FALSE;
   CResizableDialog::OnCancel();
}


BOOL CDlgErrorList::AllWarningsCommented()
{
   BOOL bRetVal = TRUE;

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

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
            CString sWarnComment;
            BEMPX_SetDataString( lDBIDWarnComment,    sWarnComment, FALSE, 0, BEMP_Str, i0WarnIdx );
            if( sWarnComment.GetLength() == 0)
            {
               bRetVal = FALSE;
               m_pView->SetCommentFocus(iWarningNum);
            }
            iWarningNum++;
         }
      }
   }


   return bRetVal;
}

// RW 11/26/02 New routine to determine if Warnings are being displayed in the dialog
BOOL CDlgErrorList::WarningsPresent()
{
   BOOL bRetVal = FALSE;

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   //long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

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
            bRetVal = TRUE;
      }
   }

   return bRetVal;
}

// RW 11/26/02 New routine to determine if Errors are being displayed in the dialog
BOOL CDlgErrorList::ErrorsPresent()
{
   BOOL bRetVal = FALSE;

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   //long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

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

         if( !sWarnType.CompareNoCase(_T("Error")) )
            bRetVal = TRUE;
      }
   }

   return bRetVal;
}

void CDlgErrorList::AllowContinue(BOOL bAllow)
{
// RW 11/26/02 Just an additional check to make sure that the Continue button does not get displayed if errors are present
   if (bAllow && !ErrorsPresent() )
   {
      CWnd* pWnd = GetDlgItem( IDOK );
      if (pWnd)
         pWnd->EnableWindow( TRUE );
   }
   else
   {
      CWnd* pWnd = GetDlgItem( IDOK );
      if (pWnd)
         pWnd->EnableWindow( FALSE );

      pWnd = GetDlgItem( IDCANCEL );
      if (pWnd)
         pWnd->SetWindowText( "Return" );
   }
}

void CDlgErrorList::OnApplyDefault()
{
   if( m_pView != NULL )
      m_pView->ApplyDefault();

   AllowContinue(AllWarningsCommented());
}

void CDlgErrorList::ClearDefaults()
{
   // Only perform the clearing if we are looking at a specific object and not all objects
   if( m_iParentCID < 0 ) 
      return;

   int iProjCompID       = BEMPX_GetDBComponentID( "Proj" );
   long lDBIDDfltExpln   = BEMPX_GetDatabaseID("DfltExplanation",   iProjCompID );

   int iWarnCompID       = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnType    = BEMPX_GetDatabaseID("WarnType",   iWarnCompID );
   long lDBIDWarnComment = BEMPX_GetDatabaseID("WarnComment",   iWarnCompID );

   CString sDefault;
   BEMPX_SetDataString( lDBIDDfltExpln,    sDefault, FALSE, 0, BEMP_Str );

   int iNumWarningObjs = (int) BEMPX_GetNumChildren( m_iParentCID, -1, BEMO_User, iWarnCompID);
   int iWarningNum = 0;

   for (int iWarn=0; iWarn<iNumWarningObjs; iWarn++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0WarnIdx = BEMPX_GetChildObjectIndex( m_iParentCID, iWarnCompID, iError, eChildObjType, iWarn+1);

      if (i0WarnIdx >= 0)
      {
         CString sWarnType;
         BEMPX_SetDataString( lDBIDWarnType,    sWarnType, FALSE, 0, BEMP_Sym, i0WarnIdx );

         if( !sWarnType.CompareNoCase(_T("Warning")) )
         {
            CString sWarnComment;
            BEMPX_SetDataString( lDBIDWarnComment,    sWarnComment, FALSE, 0, BEMP_Str, i0WarnIdx );
            if( !sWarnComment.CompareNoCase(sDefault) )
            {
               CString sEmpty = _T("");
               BEMPX_SetBEMData( lDBIDWarnComment, BEMP_Str, (void*) ((const char*)sEmpty), BEMO_User, i0WarnIdx );
            }
            iWarningNum++;
         }
      }
   }
}
