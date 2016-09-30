// BEMProcDialog.cpp : implementation file
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
#include "resource.h"
#include "BEMProcDialog.h"
#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProperty.h"
#include "..\BEMProc\expRanges.h"
#include "BPUICtl_Edit.h"
#include "BPUICtl_Cmbb.h"
#include "BPUICtl_Butn.h"
#include "BPUICtl_WMF.h"
#include "DateTimeCtl.h"
#include "BEMProcUIX.h"
#include "BEMProcCtrlList.h"
#include "BEMProcCtrlCheckListBox.h"
#include "BEMProcCtrlRTF.h"

//#include "..\BEMProc\BEMRulPrcX.h"
#include "DlgRangeError.h"

#ifdef _INC_SPREAD      // SAC 6/17/01
#include "FPSpread\BEMProcCtrlSpread.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char BASED_CODE szErrorCaption[] = "BEMProc Dialog Error";


/////////////////////////////////////////////////////////////////////////////
// Stuff to track & report number of dialog instances

static int siCBEMProcDialogInstances = 0;

int BEMPUIX_NumBEMProcDialogInstances()
{  return siCBEMProcDialogInstances;  }


/////////////////////////////////////////////////////////////////////////////
// Special Ruleset DBID stuff

#define  MAX_RULESET_DBIDS  10
static int  siNumRulesetDBIDs = 0;
static long slaRulesetDBIDs[ MAX_RULESET_DBIDS ] = {0,0,0,0,0,0,0,0,0,0};

void BEMPUIX_SetRulesetDBIDs( long* plRulesetDBIDs, int iNumRulesetDBIDs )
{
   siNumRulesetDBIDs = min( iNumRulesetDBIDs, MAX_RULESET_DBIDS );
   for (int i=0; i<siNumRulesetDBIDs; i++)
      slaRulesetDBIDs[i] = plRulesetDBIDs[i];
}

static BOOL IsRulesetDBID( long lDBID )
{
   for (int i=0; i<siNumRulesetDBIDs; i++)
   {
      if (lDBID == slaRulesetDBIDs[i])
         return TRUE;
   }
   return FALSE;
}

int BEMPUIX_DoBEMProcDialog(
	int iBEMClass/*=0*/, int iUIMode/*=0*/, BOOL bDisplayAllUIControls/*=FALSE*/, BOOL bAllowEdits/*=TRUE*/,
	CWnd* pParent/*=NULL*/, int iDlgMode/*=0*/, int iTabCtrlWd/*=600*/, int iTabCtrlHt/*=350*/, int iMaxTabs/*=99*/,
	const char* pszCaptionText/*=NULL*/, const char* pszCloseBtnText/*=NULL*/,
	DWORD* dwaNonEditableDBIDs/*=NULL*/, int iNumNonEditableDBIDs/*=0*/,
	const char* pszExitingRulelist/*=NULL*/, const char* pszDataModRulelist/*=NULL*/,
	BOOL bPostHelpMessageToParent/*=FALSE*/,
	BOOL bIncludeCompParamStrInToolTip/*=FALSE*/, BOOL bIncludeStatusStrInToolTip/*=TRUE*/, BOOL bIncludeLongCompParamStrInToolTip/*=FALSE*/ )
{
	CSACBEMProcDialog dlg(
		iBEMClass, iUIMode, bDisplayAllUIControls, bAllowEdits,
		pParent, iDlgMode, iTabCtrlWd, iTabCtrlHt, iMaxTabs,
		pszCaptionText, pszCloseBtnText,
		dwaNonEditableDBIDs, iNumNonEditableDBIDs, pszExitingRulelist,
		pszDataModRulelist, bPostHelpMessageToParent,
		bIncludeCompParamStrInToolTip, bIncludeStatusStrInToolTip, bIncludeLongCompParamStrInToolTip );
	return dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// Misc Statics

// SAC 8/22/00
// static int siTabCtrlWd = 600;
// static int siTabCtrlHt = 350;

/////////////////////////////////////////////////////////////////////////////
// CSACBEMProcDialog dialog


CSACBEMProcDialog::CSACBEMProcDialog(int iBEMClass, int iUIMode, BOOL bDisplayAllUIControls, BOOL bAllowEdits, CWnd* pParent /*=NULL*/,
                             int iDlgMode /*=0*/, int iTabCtrlWd /*=600*/, int iTabCtrlHt /*=350*/, int iMaxTabs /*=99*/,
                             const char* pszCaptionText /*=NULL*/, const char* pszCloseBtnText /*=NULL*/,
                             DWORD* dwaNonEditableDBIDs /*=NULL*/, int iNumNonEditableDBIDs /*=0*/,
                             const char* pszExitingRulelist /*=NULL*/, const char* pszDataModRulelist /*=NULL*/,
                             BOOL bPostHelpMessageToParent /*=FALSE*/,
                             BOOL bIncludeCompParamStrInToolTip /*=FALSE*/, BOOL bIncludeStatusStrInToolTip /*=TRUE*/,    // SAC 1/19/12
									  BOOL bIncludeLongCompParamStrInToolTip /*=FALSE*/ )   // SAC 8/13/13
	: CDialog(CSACBEMProcDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSACBEMProcDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

   siCBEMProcDialogInstances++;

   m_iBEMClass = iBEMClass;
   m_iUIMode   = iUIMode;
   m_bDisplayAllUIControls = bDisplayAllUIControls;
   m_bAllowEdits = bAllowEdits;

   m_pTDPage   = NULL;

   m_lContextHelpID = 0;

   m_iDialogMode = iDlgMode;  // SAC 8/7/00 - added

   m_iTabCtrlWd = iTabCtrlWd;   // SAC 8/22/00
   m_iTabCtrlHt = iTabCtrlHt;   // SAC 8/22/00
   m_iMaxTabs   = iMaxTabs;     // SAC 8/22/00

   if (pszCaptionText)
      m_sCaptionString = pszCaptionText;   // SAC 8/22/00
   else
      m_sCaptionString.Empty();
   if (pszCloseBtnText)
      m_sCloseBtnString = pszCloseBtnText;  // SAC 8/22/00
   else
      m_sCloseBtnString.Empty();

   // SAC 9/10/00 - added non-editable DBID stuff
   ASSERT( (iNumNonEditableDBIDs == 0 || dwaNonEditableDBIDs != NULL) );
   for (int i=0; i<iNumNonEditableDBIDs; i++)
      m_dwaNonEditableDBIDs.Add( dwaNonEditableDBIDs[i] );

   if (pszExitingRulelist)
      m_sExitingRulelist = pszExitingRulelist;  // SAC 6/17/01

   if (pszDataModRulelist)
      m_sDataModRulelist = pszDataModRulelist;  // SAC 6/17/01

   m_bPostHelpMessageToParent = bPostHelpMessageToParent;   // SAC 7/6/01

   m_bIncludeCompParamStrInToolTip = bIncludeCompParamStrInToolTip;   // SAC 1/19/12
   m_bIncludeLongCompParamStrInToolTip = bIncludeLongCompParamStrInToolTip;   // SAC 8/13/13
   m_bIncludeStatusStrInToolTip = bIncludeStatusStrInToolTip;   // SAC 1/19/12

}


void CSACBEMProcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSACBEMProcDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSACBEMProcDialog, CDialog)
	//{{AFX_MSG_MAP(CSACBEMProcDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SACBEMPROCTABCTRL, OnSelchangeTab)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP

   ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )

   ON_MESSAGE( WM_DISPLAYMODS, DisplayMods )

   ON_MESSAGE( WM_DATAMODIFIED, OnDataModified )

   ON_MESSAGE( WM_QMRESTOREDEFAULT, OnQMRestoreDefault )

   ON_MESSAGE( WM_SETCONTEXTHELPID, OnSetContextHelpID )
   ON_MESSAGE( WM_COMMANDHELP, OnCommandHelp )

#ifdef _INC_SPREAD    // SAC 6/17/01
   ON_MESSAGE( SSM_TEXTTIPFETCH, OnSpreadTextTipFetch )   // SAC 6/7/00 - Spreadsheet control tooltip message processing
#endif

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSACBEMProcDialog message handlers

HBRUSH CSACBEMProcDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

//   if ( ( (nCtlColor == CTLCOLOR_EDIT   ) ||
//          (nCtlColor == CTLCOLOR_LISTBOX) )  &&
//        ( (pWnd->IsKindOf(RUNTIME_CLASS(CEditCtl    ))) ||
//          (pWnd->IsKindOf(RUNTIME_CLASS(CComboBoxCtl))) )  )
//      pDC->SetTextColor( GetBEMTextColor( (int) pWnd->SendMessage(WM_GETTEXTCOLOR) ) );
   
	return hbr;
}


BOOL CSACBEMProcDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Get pointer to Close button, then get its dimensions
   int iBtnWd, iBtnHt;
	RECT btnRect = {0,0,0,0};
   CWnd* pClose = GetDlgItem( IDOK );
   if (pClose)
   {
      pClose->GetWindowRect( &btnRect );
      iBtnWd = btnRect.right - btnRect.left;
      iBtnHt = btnRect.bottom - btnRect.top;
   }
   else
      iBtnWd = iBtnHt = 0;

	// Calc and set dialog dimensions
	int iPaddedBorderWd = GetSystemMetrics(SM_CXPADDEDBORDER);	// SAC 10/29/14 - added to adjust for wider Win8 borders
   int iDlgWd = FontX(m_iTabCtrlWd) + (eiTabDlgCtrlMarg * 2) + (iPaddedBorderWd * 2) + 8;
   int iDlgHt = FontY(m_iTabCtrlHt) + (eiTabDlgCtrlMarg * 3) + (iPaddedBorderWd * 2) + GetSystemMetrics(SM_CYCAPTION) + iBtnHt + 8;
   SetWindowPos( NULL, 0, 0, iDlgWd, iDlgHt, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

   if (m_sCaptionString.GetLength() > 0)  // SAC 8/22/00
      SetWindowText( m_sCaptionString );

   // get dialog client rect to be referenced when repositioning bottom right button(s)
   RECT dlgRect;
   GetClientRect( &dlgRect );

   // Reposition Close button
   if (pClose)
   {
      int iDX = dlgRect.right  - btnRect.right  - eiTabDlgCtrlMarg;
      int iDY = dlgRect.bottom - btnRect.bottom - eiTabDlgCtrlMarg;
      pClose->SetWindowPos( NULL, btnRect.left + iDX, btnRect.top + iDY, iBtnWd, iBtnHt, SWP_NOZORDER | SWP_NOACTIVATE );

      if (m_sCloseBtnString.GetLength() > 0)  // SAC 8/22/00
         pClose->SetWindowText( m_sCloseBtnString );
   }

	// Create, set font for & populate TabCtrl
   BOOL bTCOK = m_BEMProcTabCtrl.Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP | TCS_TABS|TCS_SINGLELINE|TCS_RAGGEDRIGHT, //|TCS_TOOLTIPS,
                                     CRect( eiTabDlgCtrlMarg, eiTabDlgCtrlMarg, FontX(m_iTabCtrlWd) + eiTabDlgCtrlMarg,
                                            FontY(m_iTabCtrlHt) + eiTabDlgCtrlMarg ), this, IDC_SACBEMPROCTABCTRL );				bTCOK;
   m_BEMProcTabCtrl.SetFont( GetWizFont( FNT_STD ), FALSE );

   // Create subtabs
   m_waValidPageIdxs.RemoveAll();  // SAC 6/29/00
   m_BEMProcTabCtrl.m_iBEMClass = m_iBEMClass;
	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
   int iNumPages = eScreenData.GetNumPagesByClass( m_iBEMClass, m_iUIMode );
   int iPg = 0;
   for (int i=0; (i<iNumPages && i<m_iMaxTabs); i++)
   {
      CBEMPUIPage* pPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, i, m_iUIMode );
      if (pPage && (m_bDisplayAllUIControls || eScreenData.PageHasActiveControls( pPage )))
      {
         TabCtrlItem.pszText = pPage->m_sCaption.GetBuffer( 0 );
      	m_BEMProcTabCtrl.InsertItem( iPg++, &TabCtrlItem );
         pPage->m_sCaption.ReleaseBuffer();
         // SAC 6/29/00 - added to provide map from actual tab index to index of tab in screen data.
         //               This is necessary since middle screen data tabs may NOT be present while later ones are.
         m_waValidPageIdxs.Add( (WORD) i );
      }
   }

   InitControls();

   EnableToolTips(TRUE);

   m_BEMProcTabCtrl.SetFocus();


   BOOL bSetOK = SetWindowContextHelpId( 1000 );
   bSetOK = m_BEMProcTabCtrl.SetWindowContextHelpId( 1000 );
   

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSACBEMProcDialog::OnSelchangeTab(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
   DeleteControls();  // Delete controls from previous tab
   InitControls();    // Create controls for the new tab

	*pResult = 0;
}


void CSACBEMProcDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

   PaintTabCtrlStuff();
}


//BOOL CSACBEMProcDialog::ToggleControlIfNecessary( CBEMPUIControl* pCtrl, BOOL bEraseLabels )
BOOL CSACBEMProcDialog::ToggleControlIfNecessary( void* pVoidCtrl, BOOL bEraseLabels )
{
   CBEMPUIControl* pCtrl = (CBEMPUIControl*) pVoidCtrl;
   BOOL bRetVal = FALSE;
   if (pCtrl && pCtrl->HaveDisplayCondition() && pCtrl->ToggleControl())
   {
// SAC 6/23/99 - old way
//      pCtrl->m_bActive = !pCtrl->m_bActive;
      if (pCtrl->m_bActive)
         pCtrl->m_bActive = FALSE;
      else
         pCtrl->m_bActive = TRUE;

      CWnd* pWnd = GetDlgItem( pCtrl->m_uiCtrlID );
      if (pWnd)
      {
         pWnd->EnableWindow( pCtrl->m_bActive );
         pWnd->ShowWindow( (pCtrl->m_bActive ? SW_SHOW : SW_HIDE) );

         // Erase control labels
         if (bEraseLabels)
         {
            CDC* pDC = GetDC();
            if (pDC)   // && (pCtrl->m_iLeftEraseX != 0 || pCtrl->m_iRightEraseX != 0))	// SAC 1/3/12 - added check to make sure there is some erasure area specified - else line drawn into control below!
            {
               pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
               pDC->SelectObject( GetWizFont( FNT_STD )/*&stdFont*/ );

               CRect rc;
               pWnd->GetClientRect( &rc );
               rc.left   += FontX( (pCtrl->m_iX + pCtrl->m_iLeftEraseX ) ) + eiTabDlgCtrlMarg;
               rc.right  += FontX( (pCtrl->m_iX + pCtrl->m_iRightEraseX) ) + eiTabDlgCtrlMarg;
               rc.top    += FontY( pCtrl->m_iY )   + eiTabDlgCtrlMarg + eiTabDlgCtrlDY;
					// SAC 6/20/03 - Added small margin to bottom position to ensure sliver of labels not left following refresh
               rc.bottom += FontY( pCtrl->m_iY )+2 + eiTabDlgCtrlMarg + eiTabDlgCtrlDY;
							ASSERT( (rc.right - rc.left) > 5 );  // check to confirm that we have a reasonable width area to erase
               pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);

               ReleaseDC( pDC );
            }
         }

         bRetVal = TRUE;
      }
      else if (bEraseLabels && !pCtrl->m_bActive &&  // not a control => line or label
               (pCtrl->m_uiCtrlType == TDCT_Label || pCtrl->m_uiCtrlType == TDCT_Line))
      {
         CDC* pDC = m_BEMProcTabCtrl.GetDC();
         if (pDC)
         {
            if (pCtrl->m_uiCtrlType == TDCT_Label)
            {
               pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
               pDC->SelectObject( GetWizFont( FNT_STD )/*&stdFont*/ );

					int iDXLeft = 0, iDXRight = 0;	// SAC 1/3/12 - added adjustments to account for WIDTH of label controls when defining erasure area
					if (pCtrl->m_iWidth > 0)
					{	switch (pCtrl->m_uiLblJust)
						{	case TA_LEFT   :  iDXRight += pCtrl->m_iWidth;   break;
							case TA_RIGHT  :  iDXLeft  -= pCtrl->m_iWidth;   break;
							case TA_CENTER :  iDXLeft  -= (int) ((((double) pCtrl->m_iWidth) + 0.5) / 2.0);
													iDXRight += (int) ((((double) pCtrl->m_iWidth) + 0.5) / 2.0);   break;
						}
					}		ASSERT( ((iDXRight + pCtrl->m_iRightEraseX) - (iDXLeft + pCtrl->m_iLeftEraseX) > 5) );
               CRect rc( FontX( (pCtrl->m_iX + iDXLeft + pCtrl->m_iLeftEraseX ) ),
                         FontY( pCtrl->m_iY ) + eiTabDlgCtrlDY,
                         FontX( (pCtrl->m_iX + iDXRight + pCtrl->m_iRightEraseX) ), 
                         FontY( pCtrl->m_iY ) + eiTabDlgCtrlDY + GetWizFontHeight( pCtrl->m_iFont ) + 2 );
							ASSERT( (rc.right - rc.left) > 5 );  // check to confirm that we have a reasonable width area to erase
               pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);
            }
            else  // Line
            {
               if (pCtrl->m_lValue == -1)
               {  // => Shadow Line
                  pDC->SelectObject( &dialogPen );
                  int fromX = FontX( pCtrl->m_iX );
                  int fromY = FontY( pCtrl->m_iY )     + eiTabDlgCtrlDY;
                  int toX   = FontX( pCtrl->m_iHeight);
                  int toY   = FontY( pCtrl->m_iWidth ) + eiTabDlgCtrlDY;
                  pDC->MoveTo( fromX, fromY );
                  pDC->LineTo( toX  , toY   );
                  pDC->MoveTo( fromX, fromY+1 );
                  pDC->LineTo( toX  , toY  +1 );
               }
               else
               {  // => Standard Line where m_lValue == Line Thickness
                  CPen pen;
                  pen.CreatePen( PS_SOLID, (int)pCtrl->m_lValue, ::GetSysColor( COLOR_BTNFACE ) );
                  pDC->SelectObject( &pen );

                  int fromX = FontX( pCtrl->m_iX );
                  int fromY = FontY( pCtrl->m_iY )      + eiTabDlgCtrlDY;
                  int toX   = FontX( pCtrl->m_iHeight );
                  int toY   = FontY( pCtrl->m_iWidth  ) + eiTabDlgCtrlDY;
                  pDC->MoveTo( fromX, fromY );
                  pDC->LineTo( toX  , toY   );
                  pDC->SelectObject( &blackPen );
               }
            }
            m_BEMProcTabCtrl.ReleaseDC( pDC );
         }

         bRetVal = TRUE;
      }
   }
   return bRetVal;
}


LONG CSACBEMProcDialog::OnQMRestoreDefault( UINT uiDBInstP1, LONG lDBID )
{
   if (!m_bAllowEdits)
   {
      MessageBeep( MB_OK );
      MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
   }
   else
   {
      int iError;
      int iDBInst =  uiDBInstP1 - 1;
      BEMPX_DefaultProperty( lDBID, iError, iDBInst );
      if (iError >= 0)
         OnDataModified( 1, lDBID );
   }

   return 0;
}


// DEBUGGING
//static int siNumDataModCalls = 0;
//static int siNumPaintCalls = 0;
//static CString ssDbgMsg;
//static CRect srDbgRect;
// DEBUGGING


LONG CSACBEMProcDialog::OnDataModified( UINT wEval, LONG lDBID )
{
// DEBUGGING
//   siNumDataModCalls++;
// DEBUGGING

   if (wEval == 1)
   {
//      SetDataModifiedFlag( TRUE );
      GetParentFrame()->SendMessage( WM_DATAMODIFIED, 0, lDBID );

      // execute compliance rulelist #1
      GetParentFrame()->SendMessage( WM_EVALPROPOSED );
   }

   // send a message to the main view's tree control via CMainFrame in case the tree requires updating
   GetParentFrame()->SendMessage( WM_UPDATETREE, 0, lDBID );

   // redisplay all currently displayed database data
   DisplayMods(0,0);

   return 0;
}


LONG CSACBEMProcDialog::DisplayMods( UINT, LONG )
{
   // Loop over all controls, toggling them on or off based on current BEMProc data
   if (m_pTDPage)
   {
      for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         ToggleControlIfNecessary( eScreenData.GetControlByIndex(i), TRUE );
   }

   CWnd *pChild = GetWindow( GW_CHILD );
   while ( pChild != NULL )
   {
      pChild->SendMessage( WM_DISPLAYDATA );
      pChild = pChild->GetNextWindow( GW_HWNDNEXT );
   }

// SAC 6/23/99 - added this call based on contents of SACWizardDlg
   // Now loop over all controls and re-display labels that display data that may have been updated
   PaintTabCtrlStuff( TRUE, FALSE );

   return 1;
}


void CSACBEMProcDialog::DeleteControls()
{
   CWnd *pWnd = GetWindow( GW_CHILD );
   CWnd *pNext = NULL;
   while ( pWnd != NULL )
   {
      pNext = pWnd->GetNextWindow( GW_HWNDNEXT );

      if (    (pWnd->IsKindOf(RUNTIME_CLASS(CEditCtl     )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CComboBoxCtl )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CButtonCtl   )))
#ifdef _INC_SPREAD  // SAC 6/17/01
           || (pWnd->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlSpread)))
#endif
           || (pWnd->IsKindOf(RUNTIME_CLASS(CWMFCtl      )))
//           || (pWnd->IsKindOf(RUNTIME_CLASS(CFloorPlanCtl)))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CDateTimeCtl )))
           )
         pWnd->DestroyWindow();
         
      pWnd = pNext;
   }

   CDC* pDC = m_BEMProcTabCtrl.GetDC();
   if (pDC)
   {
      CRect rc;
      m_BEMProcTabCtrl.GetClientRect(rc);
      rc.top    += eiTabDlgCtrlDY;
      rc.bottom -= 2;
      rc.left   += 1;
      rc.right  -= 2;
      pDC->SetBkColor(   ::GetSysColor( COLOR_BTNFACE ) );
      pDC->SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
							ASSERT( (rc.right - rc.left) > 5 );  // check to confirm that we have a reasonable width area to erase
      pDC->ExtTextOut(8, 8 + eiTabDlgCtrlDY, ETO_OPAQUE, rc, " ", 1, NULL);
      m_BEMProcTabCtrl.ReleaseDC( pDC );
   }
}


BOOL CSACBEMProcDialog::InitControls()
{
   int iPage = m_BEMProcTabCtrl.GetCurSel();

   // SAC 6/29/00 - added to provide map from actual tab index to index of tab in screen data.
   //               This is necessary since middle screen data tabs may NOT be present while later ones are.
   ASSERT( m_waValidPageIdxs.GetSize() > iPage && iPage >= 0 );

   // Create controls for one of the component-specific pages
   m_pTDPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, m_waValidPageIdxs[ iPage ], m_iUIMode );
   if (m_pTDPage)
   {
      CWaitCursor wait;
      m_lContextHelpID = 0;
	  int i=m_pTDPage->m_iFirstCtrlIdx;
      for (; i<=m_pTDPage->m_iLastCtrlIdx; i++)
      {
         CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
         if ( pCtrl && (m_bDisplayAllUIControls || BEMPX_GetCompDisplay( pCtrl->m_lDBID, 0 )) )
         {
            // SAC 9/10/00 - added non-editable DBID stuff
            BOOL bAllowEdits = m_bAllowEdits;
            for (int j=0; (bAllowEdits && j < m_dwaNonEditableDBIDs.GetSize()); j++)
            {
               if ((DWORD) pCtrl->m_lDBID == m_dwaNonEditableDBIDs[j])
                  bAllowEdits = FALSE;
            }

            pCtrl->m_bActive = TRUE;
            if (pCtrl->m_uiCtrlType == TDCT_Edit)
            {
               CEditCtl* pEdit = new CEditCtl();
               pEdit->Create( this, pCtrl, bAllowEdits );
            }
            else if (pCtrl->m_uiCtrlType == TDCT_Combo)
            {
               CComboBoxCtl* pCmbb = new CComboBoxCtl();
               pCmbb->Create( this, pCtrl, bAllowEdits );
            }
            else if ( (pCtrl->m_uiCtrlType == TDCT_Button) ||
                      (pCtrl->m_uiCtrlType == TDCT_Check)  || 
                      (pCtrl->m_uiCtrlType == TDCT_RadioG) ||
                      (pCtrl->m_uiCtrlType == TDCT_Radio)  )
            {
               CButtonCtl* pBtn = new CButtonCtl();
               pBtn->Create( this, pCtrl, bAllowEdits );
            }
            else if (pCtrl->m_uiCtrlType == TDCT_WMF)
            {
               CWMFCtl* pWMF = new CWMFCtl();
               pWMF->Create( this, pCtrl, 0, m_iTabCtrlHt /*m_iFrmHeight*/, m_iTabCtrlWd /*m_iFrmWidth*/, ::GetSysColor( COLOR_WINDOW ), TRUE );
            }
//            else if (pCtrl->m_uiCtrlType == TDCT_Floor)
//            {
//               CFloorPlanCtl* pFlr = new CFloorPlanCtl();
//               pFlr->Create( this, pCtrl, m_iFrmHeight, m_iFrmWidth, ::GetSysColor( COLOR_WINDOW ), FALSE );
//            }
            else if (pCtrl->m_uiCtrlType == TDCT_Date)
            {
                CDateTimeCtl* pDate = new CDateTimeCtl();
                pDate->Create( this, pCtrl, bAllowEdits );
            }
            else if (pCtrl->m_uiCtrlType == TDCT_Spread)  // SAC 6/17/01
            {
#ifdef _INC_SPREAD
               CBEMProcCtrlSpread* pSpread = new CBEMProcCtrlSpread();
               if (pSpread)
                  pSpread->Create( this, pCtrl, bIncludeCompParamStrInToolTip, bIncludeStatusStrInToolTip,
                                   0, 0, 0 /*(m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0)*/, TRUE );
#else
               MessageBox( "CSACDlg Error:  Spreadsheet control not available." );
               pCtrl->m_bActive = FALSE;
#endif
            }
            else if (pCtrl->m_uiCtrlType == TDCT_List)   // SAC 1/19/12
            {
                CBEMProcCtrlList* pList = new CBEMProcCtrlList();
                pList->Create( this, pCtrl );
            }
            else if (pCtrl->m_uiCtrlType == TDCT_ChkLst)   // SAC 1/19/12
            {
                CBEMProcCtrlCheckListBox* pChkList = new CBEMProcCtrlCheckListBox();
                pChkList->Create( this, pCtrl );
            }
            else if (pCtrl->m_uiCtrlType == TDCT_RTF)   // SAC 1/19/12
            {
                CBEMProcCtrlRTF* pRTF = new CBEMProcCtrlRTF();
                pRTF->Create( this, pCtrl, TRUE /*bTabbedDlgShift*/ );
            }
            else
//               pCtrl->m_bActive = pCtrl->ConditionMissingOrTrue();
               pCtrl->m_bActive = FALSE;

//            ToggleControlIfNecessary( pCtrl, FALSE );
         }
         // SAC 6/30/00 - added to prevent access of unintialized m_bActive below for non-displayed controls
         else if (pCtrl)
            pCtrl->m_bActive = FALSE;
      }
      // Now go through controls AGAIN, this time displaying them
      CWnd* pFirstActiveCtrl = NULL;
      for (i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
      {
         CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
         if ( pCtrl && pCtrl->m_bActive )
         {
            CWnd* pWnd = GetDlgItem( pCtrl->m_uiCtrlID );
            if (pWnd)
            {
               if (pCtrl->CanDisplay())
               {
                  pWnd->EnableWindow( TRUE );

//                  pWnd->ShowWindow( SW_SHOW );
// SAC 6/17/00 - added if statement to prevent spreadsheet from being displayed prior to it getting all setup
                  if (pCtrl->m_uiCtrlType != TDCT_Spread)
                     pWnd->ShowWindow( SW_SHOW );

                  pWnd->PostMessage( WM_DISPLAYDATA );  //SendMessage( WM_DISPLAYDATA );

                  // get pointer to first active UI control to later set focus
                  if ( pFirstActiveCtrl == NULL &&
                       ( pCtrl->m_uiCtrlType == TDCT_Edit   ||
                         pCtrl->m_uiCtrlType == TDCT_Combo  ||
                         pCtrl->m_uiCtrlType == TDCT_Button ||
#ifdef _INC_SPREAD  // SAC 6/17/01
                          pCtrl->m_uiCtrlType == TDCT_Spread ||
#endif
                         pCtrl->m_uiCtrlType == TDCT_Check  || 
                         pCtrl->m_uiCtrlType == TDCT_RadioG ||
                         pCtrl->m_uiCtrlType == TDCT_Radio  ||
                         pCtrl->m_uiCtrlType == TDCT_Date   ||
                         pCtrl->m_uiCtrlType == TDCT_List   ||
                         pCtrl->m_uiCtrlType == TDCT_ChkLst ||
                         pCtrl->m_uiCtrlType == TDCT_RTF    ) )
                     pFirstActiveCtrl = pWnd;
               }
               else
                  pCtrl->m_bActive = FALSE;
            }
         }
         else if (pCtrl && (pCtrl->m_uiCtrlType == TDCT_Label || pCtrl->m_uiCtrlType == TDCT_Line))
            pCtrl->m_bActive = pCtrl->CanDisplay();
      }

//???
//      PaintTabCtrlStuff();
   }

   return TRUE;
}


void CSACBEMProcDialog::PaintTabCtrlStuff( BOOL bUpdateLabelsOnly, BOOL bCallDisplayMods )
{
//   int iPage = m_BEMProcTabCtrl.GetCurSel();
//   CDC* pDC = m_BEMProcTabCtrl.GetDC();
//   if (pDC && (iPage >= 0))
//   {
//      if (m_pTDPage)
// SAC 6/29/00 - replaced above w/ below to ensure DC ALWAYS released once gotten, regardless of GetCurSel() return value
   CDC* pDC = IsWindow(m_BEMProcTabCtrl.m_hWnd) ? m_BEMProcTabCtrl.GetDC() : NULL;
   if (pDC)
   {
      if (m_BEMProcTabCtrl.GetCurSel() >= 0  &&  m_pTDPage)
      {
         CRect rc;
         m_BEMProcTabCtrl.GetClientRect(rc);
         rc.top    += eiTabDlgCtrlDY;
         rc.bottom -= 2;
         rc.left   += 1;
         rc.right  -= 2;

// SAC 6/23/99 - all this does is cause the NEXT round of mods to get painted (every other opportunity)
//         // ensures labels everywhere (even under other previously overlapping apps) are written
//         m_BEMProcTabCtrl.InvalidateRect( &rc, FALSE );

         pDC->SetBkColor(   ::GetSysColor( COLOR_BTNFACE ) );
         pDC->SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
         pDC->SetBkMode( TRANSPARENT );

// DEBUGGING
//   srDbgRect.SetRect( rc.left+1, rc.top, rc.left+FontX(70), rc.top+FontY(20) );
//   ssDbgMsg.Format( "%d-%d", siNumDataModCalls, ++siNumPaintCalls );
//   pDC->SelectObject( GetWizFont(FNT_STD) );
//   pDC->ExtTextOut( srDbgRect.left+1, srDbgRect.top+1, ETO_OPAQUE, srDbgRect, ssDbgMsg, NULL);
// DEBUGGING

         for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if (pCtrl != NULL)
            {
               // SAC 6/23/99 - Moved out from if-else to ensure it gets called EVERY time
               if ( ( (pCtrl->m_uiCtrlType == TDCT_Edit ) || 
                      (pCtrl->m_uiCtrlType == TDCT_Combo) || 
                      (pCtrl->m_uiCtrlType == TDCT_Date ) ) &&   // SAC 6/12/01
                    GetDlgItem( pCtrl->m_uiCtrlID ) != NULL && pCtrl->m_bActive ) 
               {
                  pDC->SelectObject( GetWizFont( FNT_STD )/*&stdFont*/ );
//                  pDC->SetTextAlign( pCtrl->m_uiLblJust );
//                  pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iLblDX) ), 
//                                FontY( (pCtrl->m_iY + pCtrl->m_iLblDY) ) + eiTabDlgCtrlDY, pCtrl->m_sLbl );
		   			if (!pCtrl->m_sLbl.IsEmpty())		// SAC 1/3/12 - replaced above w/ following to write text labels as opaque blocks
							WriteOpaqueTextToDC( pDC, FontX( (pCtrl->m_iX + pCtrl->m_iLblDX) ),
                     	                       FontY( (pCtrl->m_iY + pCtrl->m_iLblDY) ) + eiTabDlgCtrlDY, pCtrl->m_uiLblJust, pCtrl->m_sLbl );

                  if (pCtrl->m_bUnitDisp)     
                  {
                     //pDC->SetTextAlign( pCtrl->m_uiUnitJust );
                     //pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iWidth + pCtrl->m_iUnitDX) ), 
                     //              FontY( (pCtrl->m_iY + pCtrl->m_iUnitDY) ) + eiTabDlgCtrlDY, 
                     //              BEMPX_GetBEMUnitsLabel(pCtrl->m_lDBID) );  // GetUnitsString(pCtrl->m_lDBID) );
							QString qsUnitLbl = BEMPX_GetBEMUnitsLabel(pCtrl->m_lDBID);
							if (!qsUnitLbl.isEmpty())		// SAC 1/3/12 - replaced above w/ following to write text labels as opaque blocks
							{	CString sUnitLbl = qsUnitLbl.toLatin1().constData();
								WriteOpaqueTextToDC( pDC, FontX( (pCtrl->m_iX + pCtrl->m_iWidth + pCtrl->m_iUnitDX) ),
					                                   FontY( (pCtrl->m_iY + pCtrl->m_iUnitDY) ) + eiTabDlgCtrlDY, pCtrl->m_uiUnitJust, sUnitLbl );
                  }	}
               }

               if (bUpdateLabelsOnly)
               {
//                  if (pCtrl->m_bLabelRequiringRefresh)
                  if (pCtrl->m_bLabelRequiringRefresh &&
                      // SAC 7/15/00 - added check to ensure one of the label offset values is non-zero
                      //               if they are both zero, then this label is likely a rulelist name to be evaluated (ChkList control)
                      // SAC 5/14/01 - added leading condition to ensure Label controls always refreshed when m_bLabelRequiringRefresh == TRUE
                      (pCtrl->m_uiCtrlType == TDCT_Label || pCtrl->m_iLblDX != 0 || pCtrl->m_iLblDY != 0))
                  {
                     // Erase previous label and replace it with an updated label
                     CRect rc;
                     rc.top    = FontY(pCtrl->m_iY) + eiTabDlgCtrlDY - 1;
// SAC 6/20/03 - Add "max()" call to ensure bottom sliver of labels not left following refresh
//                     rc.bottom = rc.top + FontY(GetWizFontHeight(pCtrl->m_iFont)) + eiTabDlgCtrlDY + 2;
                     rc.bottom = rc.top + FontY( max( pCtrl->m_iHeight, GetWizFontHeight(pCtrl->m_iFont) ) ) + /*eiTabDlgCtrlDY +*/ 2;
                     if (pCtrl->m_uiLblJust == TA_LEFT)
                     {
                        rc.left  = FontX(pCtrl->m_iX) - 1;
// SAC 1/3/12 - revisions to left/right to use label's WIDTH when erasing label (as opposed to erasing a label associated with another type of UI control)
//                        rc.right = rc.left + FontX(pCtrl->m_iLblDX) + 2;
                        rc.right = rc.left + (pCtrl->m_uiCtrlType == TDCT_Label ? FontX(pCtrl->m_iWidth) : FontX(pCtrl->m_iLblDX)) + 2;
                     }
                     else if (pCtrl->m_uiLblJust == TA_RIGHT)
                     {
                        rc.right = FontX(pCtrl->m_iX) + 1;
//                        rc.left  = rc.right - FontX(pCtrl->m_iLblDX) - 2;
                        rc.left  = rc.right - (pCtrl->m_uiCtrlType == TDCT_Label ? FontX(pCtrl->m_iWidth) : FontX(pCtrl->m_iLblDX)) - 2;
                     }
                     else if (pCtrl->m_uiLblJust == TA_CENTER)
                     {
//                        int iDX = (int) (0.5 * FontX(pCtrl->m_iLblDX));
                        int iDX = (int) (0.5 * (pCtrl->m_uiCtrlType == TDCT_Label ? FontX(pCtrl->m_iWidth) : FontX(pCtrl->m_iLblDX)));
                        rc.left  = FontX(pCtrl->m_iX) - iDX - 1;
                        rc.right = FontX(pCtrl->m_iX) + iDX + 1;
                     }
                     pDC->SelectObject( GetWizFont( FNT_STD ) );
                     // SAC 7/3/00 - DON'T erase label rect when iUnitsDX == -1 (=> no erasure of label)
                     if (pCtrl->m_iUnitDX != -1 && rc.right > (rc.left+2))
							{	//ASSERT( (rc.right - rc.left) > 5 );  // check to confirm that we have a reasonable width area to erase
                        pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);
							}
                     
                     WriteLabelToDC( pDC, pCtrl, 0 /*m_lCtrlDBIDOffset*/, eiTabDlgCtrlDY );
                  }
                  else if (pCtrl->m_uiCtrlType == TDCT_Line)
                     WriteLineCtrlToDC( pDC, pCtrl, eiTabDlgCtrlDY );
                  else if (pCtrl->m_uiCtrlType == TDCT_Rect)   // SAC 6/21/00
                     WriteRectToDC( pDC, pCtrl );
               }
               else
               {
                  if ( ( (pCtrl->m_uiCtrlType == TDCT_Edit ) || 
                         (pCtrl->m_uiCtrlType == TDCT_Combo) || 
                         (pCtrl->m_uiCtrlType == TDCT_Date ) ) &&
                       GetDlgItem( pCtrl->m_uiCtrlID ) != NULL && pCtrl->m_bActive ) 
                  {
// SAC 6/23/99 - moved up (outside of if-else)
//                     pDC->SelectObject( GetWizFont( FNT_STD )/*&stdFont*/ );
//                     pDC->SetTextAlign( pCtrl->m_uiLblJust );
//                     pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iLblDX) ), 
//                                   FontY( (pCtrl->m_iY + pCtrl->m_iLblDY) ) + eiTabDlgCtrlDY, pCtrl->m_sLbl );
//                                   
//                     if (pCtrl->m_bUnitDisp)     
//                     {
//                        pDC->SetTextAlign( pCtrl->m_uiUnitJust );
//                        pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iWidth + pCtrl->m_iUnitDX) ), 
//                                      FontY( (pCtrl->m_iY + pCtrl->m_iUnitDY) ) + eiTabDlgCtrlDY, 
//                                      BEMPX_GetBEMUnitsLabel(pCtrl->m_lDBID) );  // GetUnitsString(pCtrl->m_lDBID) );
//                     }
                  }
                  else if (pCtrl->m_uiCtrlType == TDCT_Line && pCtrl->m_bActive)
                  {
                     // SAC 6/23/99 - replaced line drawing code w/ equivalent function
                     WriteLineCtrlToDC( pDC, pCtrl, eiTabDlgCtrlDY );
//                     if (pCtrl->m_lValue == -1)
//                     {  // => Shadow Line
//                        pDC->SelectObject( &btnShadowPen );
//                        int fromX = FontX( pCtrl->m_iX );
//                        int fromY = FontY( pCtrl->m_iY )     + eiTabDlgCtrlDY;
//                        int toX   = FontX( pCtrl->m_iHeight);
//                        int toY   = FontY( pCtrl->m_iWidth ) + eiTabDlgCtrlDY;
//                        pDC->MoveTo( fromX, fromY );
//                        pDC->LineTo( toX  , toY   );
//
//                        pDC->SelectObject( &btnHighlightPen );
//                        pDC->MoveTo( fromX, fromY+1 );
//                        pDC->LineTo( toX  , toY  +1 );
//                     }
//                     else
//                     {  // => Standard Line where m_lValue == Line Thickness
//                        CPen pen;
//                        pen.CreatePen( PS_SOLID, (int)pCtrl->m_lValue, RGB( 0, 0, 0) );
//                        pDC->SelectObject( &pen );
//
//                        int fromX = FontX( pCtrl->m_iX );
//                        int fromY = FontY( pCtrl->m_iY )     + eiTabDlgCtrlDY;
//                        int toX   = FontX( pCtrl->m_iHeight);
//                        int toY   = FontY( pCtrl->m_iWidth ) + eiTabDlgCtrlDY;
//                        pDC->MoveTo( fromX, fromY );
//                        pDC->LineTo( toX  , toY   );
//                        pDC->SelectObject( &blackPen );
//                     }
                  }
                  else if (pCtrl->m_uiCtrlType == TDCT_Label && pCtrl->m_bActive)
                  {
                     // SAC 6/23/99 - replaced line drawing code w/ equivalent function
                     WriteLabelToDC( pDC, pCtrl, 0 /*m_lCtrlDBIDOffset*/, eiTabDlgCtrlDY );
//                     CString sLabel = pCtrl->m_sLbl;
//
//                     if (pCtrl->m_lDBID > 0)
//                     {
//                        CString sData;
//                        BEMPX_SetDataString( pCtrl->m_lDBID, sData, (pCtrl->m_lValue >= 0),
//                                           (int) pCtrl->m_lValue, -1, pCtrl->m_iDBInstance );
//                        sLabel += sData;
//                     }
//                     sLabel += pCtrl->m_sStatusMsg;
//
//                     pDC->SetBkMode( TRANSPARENT );
//                     pDC->SelectObject( GetWizFont(pCtrl->m_iFont) );
//                     pDC->SetTextAlign( pCtrl->m_uiLblJust );
//                     if ( sLabel.GetLength() > 0)
//                        pDC->TextOut( FontX(pCtrl->m_iX), FontY(pCtrl->m_iY) + eiTabDlgCtrlDY, sLabel );
                  }                                                    
               }
            }
         }

         if (bCallDisplayMods)
            DisplayMods(0,0);
      }

      m_BEMProcTabCtrl.ReleaseDC( pDC );
   }
}


void CSACBEMProcDialog::PostNcDestroy() 
{
   siCBEMProcDialogInstances--;
	
	CDialog::PostNcDestroy();
}


BOOL CSACBEMProcDialog::OnToolTipNotify( UINT /*id*/, NMHDR* pNMHDR, LRESULT* /*pResult*/ )
{
   TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*) pNMHDR;
   UINT nID = pNMHDR->idFrom;
   if ((pTTT->uFlags & TTF_IDISHWND) && m_pTDPage)
   {  // idFrom is actually the HWND of the tool
      CBEMPUIControl* pTDCtrl = eScreenData.GetControlByPageAndID( m_pTDPage, ::GetDlgCtrlID((HWND)nID) );
//      if (pTDCtrl)
// SAC 6/17/01 - added to if statement such that we don't display ToolTips for the spreadsheet from here
      if (pTDCtrl  &&  pTDCtrl->m_uiCtrlType != TDCT_Spread)
      {
// SAC 1/10/03 - Added line of code to blast any text leftover from previous displays
//               (string gets longer & longer if no tooltip text or range message exists but flag set to display component:property info)
         m_sToolStr.Empty();

         if( !pTDCtrl->m_sStatusMsg.IsEmpty() )
            m_sToolStr = pTDCtrl->m_sStatusMsg;
// RW 10/29/02 - Made changes below to allow for the tooltip message to be generated via a rulelist evaluation
         else if( !pTDCtrl->m_sTooltipRulelistName.IsEmpty() )
         {
            // Here we need to execute the rulelist and then retrieve the generated string
            // from the corresponding tooltip parameter (for now, that is set up as ToolTipText)
            // We are going to call the same routine that is called for normal error checking
            // and the rule should post one error message which will be the generated tooltip message
            QStringList saErrors, saWarnings;
            int iEvalOnlyClass = 0;
            int iEvalOnlyOccur = -1;
            if (pTDCtrl->m_lDBID > 0)
            {
               iEvalOnlyClass = BEMPX_GetClassID( pTDCtrl->m_lDBID );
               if (iEvalOnlyClass > 0)
               {
                  int iError;
                  iEvalOnlyOccur = BEMPX_GetObjectIndex( BEMPX_GetClass( iEvalOnlyClass, iError ) );
               }
            }

            VERIFY( BEMPX_EvalErrorCheckList( pTDCtrl->m_sTooltipRulelistName, saErrors, saWarnings, iEvalOnlyClass, iEvalOnlyOccur) );
            if( saErrors.size() )
               m_sToolStr = saErrors[0].toLatin1().constData();
         }
         else
            BEMPUIX_GetToolTipMessage( m_sToolStr, pTDCtrl->m_lDBID );	// SAC 5/11/14 - added

         QString sRangeMsg;
// RW 11/02/02 - We only want to generate a range message if there is no rule-based generation
         if( pTDCtrl->m_sTooltipRulelistName.IsEmpty() )
            BEMPX_GenerateRangeMessage( pTDCtrl->m_lDBID, &sRangeMsg );

         if( sRangeMsg.length() > 0 )
         {
            m_sToolStr += "\r\n";
            m_sToolStr += sRangeMsg.toLatin1().constData();
         }
         //if (m_bIncludeStatusStrInToolTip || m_bIncludeCompParamStrInToolTip)  // SAC 11/29/02 - Prevent ending up w/ tool tip with only a CR/LF
     //    if (m_sToolStr.GetLength() > 0 && (m_bIncludeStatusStrInToolTip || m_bIncludeCompParamStrInToolTip))
     //       m_sToolStr += "\r\n";
	  // SAC 5/28/14 - prevent echoing of data status & CompParam strings when control's DBID invalid

         if (m_bIncludeStatusStrInToolTip && pTDCtrl->m_lDBID > 0)  // SAC 1/19/12
         {
	         m_sToolStr += "\r\n(";
	         m_sToolStr += GetCompDataTypeString( pTDCtrl->m_lDBID, m_iDialogMode );
	         m_sToolStr += " data status: ";
	         m_sToolStr += GetDataStatusString( pTDCtrl->m_lDBID, pTDCtrl->m_iDBInstance, m_iDialogMode );
	         m_sToolStr += ")";
         }

         if (m_bIncludeCompParamStrInToolTip && pTDCtrl->m_lDBID > 0)  // SAC 6/3/00
         {  QString sTemp;
            BEMPX_DBIDToDBCompParamString( pTDCtrl->m_lDBID, sTemp );
            m_sToolStr += " - ";
            m_sToolStr += sTemp.toLatin1().constData();
         }
         if (m_bIncludeLongCompParamStrInToolTip && pTDCtrl->m_lDBID > 0)  // SAC 8/13/13
         {  QString sTemp;
            BEMPX_DBIDToDBCompParamString( pTDCtrl->m_lDBID, sTemp, true /*bLongName*/ );
            m_sToolStr += (m_bIncludeCompParamStrInToolTip ? " / " : " - ");
            m_sToolStr += sTemp.toLatin1().constData();
         }

         pTTT->lpszText = (LPTSTR)(LPCTSTR)m_sToolStr;
         pTTT->hinst = AfxGetResourceHandle();

         // RW 10/31/02 Force the tooltip to be multiline
         ::SendMessage(pNMHDR->hwndFrom, TTM_SETMAXTIPWIDTH, 0, 300);

// TESTING
//			long lDelayMSecs = (::SendMessage( pNMHDR->hwndFrom, TTM_GETDELAYTIME, TTDT_AUTOPOP, 0 ) * 4);
			long lDelayMSecs = 32767;
			::SendMessage( pNMHDR->hwndFrom, TTM_SETDELAYTIME, TTDT_AUTOPOP, lDelayMSecs );

         return(TRUE);
      }
   }
   return(FALSE);
}

int CSACBEMProcDialog::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// find child window which hits the point
	// (don't use WindowFromPoint, because it ignores disabled windows)
   if (m_pTDPage)
   {
      for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
      {
         int iCtrlID = (int) eScreenData.GetControlIDByIndex( i );
         if (iCtrlID > 0)
         {
            CWnd* pChildWnd = GetDlgItem( iCtrlID );
            // SAC 6/23/99 - modified code to only catch visible UI controls
            if (pChildWnd && pChildWnd->IsWindowVisible())
            {
               CRect rect;
               pChildWnd->GetWindowRect( &rect );
               ScreenToClient( &rect );
               if (rect.PtInRect( point ))
               {
                  HWND hWndChild = pChildWnd->GetSafeHwnd();
         			pTI->hwnd = m_hWnd;
         			pTI->uId = (UINT)hWndChild;
         			pTI->uFlags |= TTF_IDISHWND;
         			pTI->lpszText = LPSTR_TEXTCALLBACK;

         			// set TTF_NOTBUTTON and TTF_CENTERTIP if it isn't a button
         			if (!(::SendMessage(hWndChild, WM_GETDLGCODE, 0, 0) & DLGC_BUTTON))
         				pTI->uFlags |= TTF_NOTBUTTON|TTF_CENTERTIP;

            		return iCtrlID;
               }
            }
         }
      }
   }
   return -1;  // not found
}



// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
LRESULT CSACBEMProcDialog::OnSetContextHelpID( WPARAM wHelpID, LPARAM )
{
   m_lContextHelpID = wHelpID;
   return 1;
}

// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
LRESULT CSACBEMProcDialog::OnCommandHelp( WPARAM, LPARAM /*lParam*/ )
{
   if (m_lContextHelpID > 0)
   {
      // SAC 7/6/01 - added if statement to enable parent window to handle help system calls (HTML help)
      if (m_bPostHelpMessageToParent)
      {
         CWnd* pParent = GetParent();
         CFrameWnd* pFrame = GetParentFrame();
         // SAC 9/6/00 - Added trailing ", 1" argument to PostMessage calls in order to cause resulting help to be presented in a secondary window
//         if (pParent  &&  pParent->IsKindOf(RUNTIME_CLASS( CSACBEMProcDialog ))  &&  pFrame)
         if (pParent  &&  pParent == this  &&  pFrame)
            pFrame->PostMessage( WM_PARENTHELP, m_lContextHelpID, 1 );
         else if (pParent)
            pParent->PostMessage( WM_PARENTHELP, m_lContextHelpID, 1 );
      }
      else
      {
         CWinApp* pApp = AfxGetApp();
         if (pApp != NULL)
            pApp->WinHelp( m_lContextHelpID );
      }
      m_lContextHelpID = 0;
      return TRUE;
   }
   return FALSE;
}



BOOL CSACBEMProcDialog::RuleBasedErrorCheck()
{
   BOOL bRetVal = TRUE;

   if (!m_sExitingRulelist.IsEmpty())
   {
      CString sCumErr, sCumWarn;
      BOOL bErrorsFound = FALSE;
      BOOL bWarningsFound = FALSE;
//      CWnd* pFocusCtrl = NULL;
      if (bRetVal)	// always true
      {
         CWaitCursor busyCursor;
         QStringList saErrors, saWarnings;
//         for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
//         {
//            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
//            if (pCtrl && !pCtrl->m_sErrorCheckRulelistName.IsEmpty())
//            {
//               CWnd* pWnd = GetDlgItem( pCtrl->m_uiCtrlID );
//               if (pWnd && pWnd->IsWindowVisible())
//               {
//                  int iEvalOnlyClass = 0;
                  int iEvalOnlyClass = m_iBEMClass;
                  int iEvalOnlyOccur = -1;
//                  if (pCtrl->m_lDBID > 0)
//                  {
//                     iEvalOnlyClass = BEMPX_GetClassID( pCtrl->m_lDBID );
                     if (iEvalOnlyClass > 0)
                     {
                        int iError;
                        iEvalOnlyOccur = BEMPX_GetObjectIndex( BEMPX_GetClass( iEvalOnlyClass, iError ) );
                     }
//                  }
//                  VERIFY( BEMPX_EvalErrorCheckList( pCtrl->m_sErrorCheckRulelistName, saErrors, saWarnings, iEvalOnlyClass, iEvalOnlyOccur ) );
                  VERIFY( BEMPX_EvalErrorCheckList( m_sExitingRulelist, saErrors, saWarnings, iEvalOnlyClass, iEvalOnlyOccur ) );

                  if (!bErrorsFound  &&  saErrors.size() > 0)
                  {
                     bErrorsFound = TRUE;
//                     pFocusCtrl = pWnd;
                  }
//                  else if (pFocusCtrl == NULL  &&  saWarnings.GetSize() > 0)
//                     pFocusCtrl = pWnd;
//               }
//            }
//         }
         bWarningsFound = (saWarnings.size() > 0);

		 int i=0;
//         for (i=0; i<saErrors.GetSize(); i++)
         for (; i<saErrors.size(); i++)
         {
            if (i > 0)
               sCumErr += "\r\n\r\n";
            sCumErr += "ERROR:  ";
            sCumErr += saErrors[i].toLatin1().constData();
         }
         for (i=0; i<saWarnings.size(); i++)
         {
            if (i > 0  ||  !sCumErr.IsEmpty())
               sCumErr += "\r\n\r\n";
            sCumErr += "Warning:  ";
            sCumErr += saWarnings[i].toLatin1().constData();
         }
      }

      if (!sCumErr.IsEmpty() || !sCumWarn.IsEmpty())
      {
         CString sLabel, sPrompt;
         if (bErrorsFound  &&  bWarningsFound)
            sLabel = "User input error(s) and warning(s):";
         else if (bErrorsFound)
            sLabel = "User input error(s):";
         else
            sLabel = "User input warning(s):";
         sPrompt = (bErrorsFound ? " " : "");

         CDlgRangeError dlgErr( sCumErr, m_iDialogMode, this, sLabel, sPrompt, (!bErrorsFound) );
         dlgErr.DoModal();
         bRetVal = dlgErr.m_bContinue;

//         if (!bRetVal && pFocusCtrl)
//            pFocusCtrl->SetFocus();
      }
   }

   return bRetVal;
}


void CSACBEMProcDialog::OnOK() 
{
   if (RuleBasedErrorCheck())
   {
//      EvaluateRules( 1 );
      CDialog::OnOK();	
   }
}

void CSACBEMProcDialog::OnCancel() 
{
//   if (!m_bBypassChecksOnCancel)
//   {
//      if ( !EditControlValuesInRange( 3 ) )
//         return;

      if (!RuleBasedErrorCheck())
         return;
      
//      if ( !OKToExit() &&
//           MessageBox( "Do you wish to leave this dialog without fixing the error(s)?",
//                       "Cancel Error", MB_ICONQUESTION | MB_YESNO ) != IDYES )
//         return;
//   }
//      
//   EvaluateRules( 1 );
   CDialog::OnCancel();
}



#ifdef _INC_SPREAD
// SAC 6/7/00 - Spreadsheet control tooltip message processing
LRESULT CSACBEMProcDialog::OnSpreadTextTipFetch(WPARAM wParam, LPARAM lParam)
{
   CWnd* pSpread = GetDlgItem( wParam );
   if (pSpread && lParam && pSpread->IsKindOf(RUNTIME_CLASS( CBEMProcCtrlSpread )))
      ((CBEMProcCtrlSpread*)pSpread)->OnTextTipFetch( (LPSS_TEXTTIPFETCH) lParam );

   return 1;
}
#endif

BOOL CSACBEMProcDialog::CheckData( CString& sMsg, CArray<long,long>* plErrDBIDs, CArray<long,long>* plWarnDBIDs )
{
   BOOL bRetVal = TRUE;
   // Create subtabs
   m_waValidPageIdxs.RemoveAll();  // SAC 6/29/00
   m_BEMProcTabCtrl.m_iBEMClass = m_iBEMClass;
	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
   int iNumPages = eScreenData.GetNumPagesByClass( m_iBEMClass, m_iUIMode );
   //int iPg = 0;
   for (int i=0; (i<iNumPages && i<m_iMaxTabs); i++)
   {
      CBEMPUIPage* pPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, i, m_iUIMode );
      if (pPage && (m_bDisplayAllUIControls || eScreenData.PageHasActiveControls( pPage )))
      {
         // SAC 6/29/00 - added to provide map from actual tab index to index of tab in screen data.
         //               This is necessary since middle screen data tabs may NOT be present while later ones are.
         m_waValidPageIdxs.Add( (WORD) i );
      }
   }

   for( int iTab = 0; iTab < m_iMaxTabs; iTab++ )
   {
      m_pTDPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, m_waValidPageIdxs[ iTab ], m_iUIMode );
      if (m_pTDPage)
      {
         int iNumViolations = 0;
         for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if ( pCtrl && (m_bDisplayAllUIControls || BEMPX_GetCompDisplay( pCtrl->m_lDBID, 0 )) )
            {
               QString sCtrlMsg;
               BOOL bCtrlErrAdded = FALSE;
               BOOL bCtrlWarnAdded = FALSE;
               // get the lDBID from the pCtrl and perform the range check with it and the data for the control's instance
// Unless I am mistaken, we are only performing basic range checks for Edit and Date controls. All others are done via rulelist checks
               if( pCtrl->m_uiCtrlType == TDCT_Edit || pCtrl->m_uiCtrlType == TDCT_Date )
               {
                  // all other controls only have on DBID and therefore one DBID value assigned to them
                  // We need to get the current value of this DBID and perform a range check on it
                  int iDataType;
                  int iSpecialVal;
                  int iError;

                  BEMProperty* pProp = BEMPX_GetProperty( pCtrl->m_lDBID, iError );
                  if (iError >= 0 && pProp)
                  {
                     iDataType = pProp->getType()->getPropType();
                     iSpecialVal = pProp->getSpecialValue();

                     if( iDataType == BEMP_Flt || BEMP_Int || BEMP_Sym )
                     {
                        double fData;
                        if( iDataType == BEMP_Flt )
                           fData = pProp->getDouble();
                        else
                           fData = (double)pProp->getInt();

                        int iRangeVal = BEMPX_PerformRangeCheck( pCtrl->m_lDBID, fData, TRUE, &sCtrlMsg );
                        if (iRangeVal == RANGE_ERROR  ||  iRangeVal == RANGE_WARNING  ) // || iRangeVal == RANGE_MESSAGE)
                        {
                           // Add the range violation message to the user message
                           if (iNumViolations > 0)
                              sMsg += "\r\n\r\n";
                           if (iRangeVal == RANGE_ERROR)
                           {
                              bCtrlErrAdded = TRUE;
                              sMsg += "ERROR:  ";
                              plErrDBIDs->Add(pCtrl->m_lDBID);
                           }
                           else if (iRangeVal == RANGE_WARNING)
                           {
                              sMsg += "Warning:  ";
                              bCtrlWarnAdded = TRUE;
                              plWarnDBIDs->Add(pCtrl->m_lDBID);
                           }
//                           else // if (iRangeVal == RANGE_MESSAGE)
//                              sMsg += "Message:  ";
									if (!sCtrlMsg.isEmpty())
                           	sMsg += sCtrlMsg.toLatin1().constData();

                           iNumViolations++;
                           bRetVal = FALSE;
                        }
                     }
                  }
               }
               // For all other control types we are going to want to do a rulelist check if one exists for the current control
               if (!pCtrl->m_sErrorCheckRulelistName.IsEmpty())
               {
                  QStringList saErrors, saWarnings;
                  CString sCumErr;
                  int iEvalOnlyClass = 0;
                  int iEvalOnlyOccur = -1;
                  if (pCtrl->m_lDBID > 0)
                  {
                     iEvalOnlyClass = BEMPX_GetClassID( pCtrl->m_lDBID );
                     if (iEvalOnlyClass > 0)
                     {
                        int iError;
                        iEvalOnlyOccur = BEMPX_GetObjectIndex( BEMPX_GetClass( iEvalOnlyClass, iError ) );
                     }
                  }
                  VERIFY( BEMPX_EvalErrorCheckList( pCtrl->m_sErrorCheckRulelistName, saErrors, saWarnings, iEvalOnlyClass, iEvalOnlyOccur ) );

                  for (int iErr=0; iErr<saErrors.size(); iErr++)
                  {
                     if( !bCtrlErrAdded )
                     {
                         bCtrlErrAdded = TRUE;
                         plErrDBIDs->Add(pCtrl->m_lDBID);
                     }
                     if (iErr > 0 || iNumViolations > 0)
                        sCumErr += "\r\n\r\n";
                     sCumErr += "ERROR:  ";
                     sCumErr += saErrors[iErr].toLatin1().constData();
                     bRetVal = FALSE;
                     iNumViolations++;
                  }
                  for (int iWarn=0; iWarn<saWarnings.size(); iWarn++)
                  {
                     if( !bCtrlWarnAdded )
                     {
                         bCtrlWarnAdded = TRUE;
                         plWarnDBIDs->Add(pCtrl->m_lDBID);
                     }
                     if (iWarn > 0  ||  !sCumErr.IsEmpty() || iNumViolations > 0)
                        sCumErr += "\r\n\r\n";
                     sCumErr += "Warning:  ";
                     sCumErr += saWarnings[iWarn].toLatin1().constData();
                     bRetVal = FALSE;
                     iNumViolations++;
                  }
                  sMsg += sCumErr;
               }
            }
         }
      }
   }

   return bRetVal;
}
