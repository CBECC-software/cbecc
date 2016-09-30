// SACDlg.cpp : implementation file
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

//    Based on SACWizardDlg only controls are recreated following the edit of a specified DBID
//    in order to prevent a LARGE number of controls from being created but hidden
//

#include "stdafx.h"
#include "SACDlg.h"
#include "BEMProcUIX.h"

#include "resource.h"
#include "Screens.h"

#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProperty.h"
#include "..\BEMProc\expRanges.h"
#include "ToolTips.h"

#include "BPUICtl_Edit.h"
#include "BPUICtl_Cmbb.h"
#include "BPUICtl_Butn.h"
#include "BPUICtl_WMF.h"
// #include "BPUICtl_Date.h"
#include "DateTimeCtl.h"
#include "BEMProcCtrlList.h"
#include "BEMProcCtrlCheckListBox.h"
#include "BEMProcCtrlRTF.h"
#include "ExtendedComboBox.h"

#include "DlgRangeError.h"
#include "DlgErrorList.h"
#include "ViewErrorList.h"

#ifdef _INC_SPREAD
#include "FPSpread\BEMProcCtrlSpread.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSACDlg dialog

IMPLEMENT_DYNAMIC( CSACDlg, CDialog )

CSACDlg::CSACDlg( CWnd* pParent /*=NULL*/, int iBEMCID_Wizard /*=0*/, long lDBID_ScreenIdx /*=0*/,
                              long lDBID_ScreenID /*=0*/, long lDBID_PrevScreenID /*=0*/, long lDBID_NextScreenID /*=0*/,
                              long lDBID_EnableFinish /*=0*/, const char* pszMidProcRulelist /*=NULL*/,
                              const char* pszPostProcRulelist /*=NULL*/, const char* pszDialogCaption /*=NULL*/,
                              int iBaseHt /*=400*/, int iBaseWd /*=620*/, int iBaseMarg /*=10*/,
                              UINT uiIconResourceID /*=0*/, BOOL bEnableToolTips /*=TRUE*/,
                              BOOL bShowPrevNextButtons /*=TRUE*/, int iSACWizDlgMode /*=SWDM_Default*/,
                              long lDBID_CtrlDBIDOffset /*=0*/, const char* pszFinishButtonText /*=NULL*/,
                              long* plCheckCharDBIDs /*=NULL*/, int iNumCheckCharDBIDs /*=0*/,
                              long lDBID_ScreenIDArray /*=0*/, BOOL bPostHelpMessageToParent /*=FALSE*/,
                              BOOL bIncludeCompParamStrInToolTip /*=FALSE*/, BOOL bIncludeStatusStrInToolTip /*=TRUE*/,
                              BOOL bUsePageIDForCtrlTopicHelp /*=FALSE*/, int iHelpIDOffset /*=100000*/,
                              long lDBID_DialogHeight /*=0*/, BOOL bBypassChecksOnCancel /*=FALSE*/, BOOL bEnableCancelBtn /*=FALSE*/,
                              BOOL bGraphicalButtons /*=FALSE*/, int iFinishBtnWd /*=60*/, BOOL bIncludeLongCompParamStrInToolTip /*=FALSE*/ )
	: CDialog(CSACDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSACDlg)
		// NOTE: the ClassWizard will add member initialization here
   m_bInitializeDialog = TRUE;
   m_pTDPage   = NULL;
   m_iCurrentScreenID = 0;

   m_sCaption = pszDialogCaption;

   m_uiIconResourceID = uiIconResourceID;

   // location & dimension variables
   m_iBaseWidth  = iBaseWd;
   m_iBaseHeight = iBaseHt;
   m_iBaseMargin = iBaseMarg;
   m_iDlgWidth  = 0;
   m_iDlgHeight = 0;
   m_iDlgMargin = 0;
   m_iFrmWidth  = 0;
   m_iFrmHeight = 0;
   m_iFrmBottom = 0;
   m_iLeftButtonX = 0;

   // BEMProc IDs
   m_iBEMCID_Wizard     = iBEMCID_Wizard;
   m_lDBID_ScreenIdx    = lDBID_ScreenIdx;    // SAC 1/31/00 - actually maps to ScreenIDArrIdx when using new ScreenIDArray method
   m_lDBID_ScreenID     = lDBID_ScreenID;     // SAC 1/31/00 - actually maps to ScreenIDArrID  when using new ScreenIDArray method
                                              // SAC 1/31/01 - modified to enable this to hold a fixed screen ID value (iff < BEMPX_GetDBID(1,0,0))
   m_lDBID_PrevScreenID = lDBID_PrevScreenID;
   m_lDBID_NextScreenID = lDBID_NextScreenID;
   m_lDBID_EnableFinish = lDBID_EnableFinish;

   m_lDBID_CtrlDBIDOffset = lDBID_CtrlDBIDOffset;   // SAC 2/25/99
   m_lCtrlDBIDOffset = 0;

   m_lDBID_ScreenIDArray = lDBID_ScreenIDArray;    // SAC 1/31/00

   // Rules Processing Rulelist Names
   m_sMidProcRulelist  = pszMidProcRulelist;
   m_sPostProcRulelist = pszPostProcRulelist;

   m_lContextHelpID = 0;

   m_bEnableToolTips = bEnableToolTips;

   m_bShowPrevNextButtons = bShowPrevNextButtons;

   m_iDialogMode = iSACWizDlgMode;  // enum SACWizDlgMode

   m_sFinishButtonText = pszFinishButtonText;   // SAC 2/25/99

   m_plCheckCharDBIDs   = plCheckCharDBIDs;   // SAC 3/8/99 - added to enable edit control filename entry character checking
   m_iNumCheckCharDBIDs = iNumCheckCharDBIDs;

   m_bPostHelpMessageToParent = bPostHelpMessageToParent;   // SAC 2/7/00

   m_bIncludeCompParamStrInToolTip = bIncludeCompParamStrInToolTip;   // SAC 6/3/00
   m_bIncludeLongCompParamStrInToolTip = bIncludeLongCompParamStrInToolTip;   // SAC 8/13/13
   m_bIncludeStatusStrInToolTip = bIncludeStatusStrInToolTip;   // SAC 9/2/00

   m_bUsePageIDForTopicHelp = bUsePageIDForCtrlTopicHelp;  // SAC 9/4/00
   m_iHelpIDOffset = iHelpIDOffset;   // SAC 9/4/00

   m_lDBID_DialogHeight = lDBID_DialogHeight;  // SAC 2/10/01

   m_bBypassChecksOnCancel = bBypassChecksOnCancel;  // SAC 6/11/01
   m_bEnableCancelBtn = bEnableCancelBtn;            // SAC 6/12/01

   m_bGraphicalButtons = bGraphicalButtons;      // SAC 10/27/02
   m_iFinishBtnWd      = iFinishBtnWd;
	//}}AFX_DATA_INIT
}


void CSACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSACDlg)
	DDX_Control(pDX, IDC_SACWIZFRAME, m_bWizardFrame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSACDlg, CDialog)
	//{{AFX_MSG_MAP(CSACDlg)
	ON_BN_CLICKED(IDC_PREVSCREEN, OnPreviousScreen)
	ON_BN_CLICKED(IDC_WIZHELP, OnWizardHelp)
	ON_BN_CLICKED(IDC_NEXTTOPIC, OnNextScreen)
	ON_BN_CLICKED(IDOK, OnFinishWizard)
	ON_BN_CLICKED(IDCANCEL, OnCancelWizard)
	ON_BN_CLICKED(IDCANCELBTN, OnCancelWizard)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

   ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )

   ON_MESSAGE( WM_DISPLAYMODS, DisplayMods)
   ON_MESSAGE( WM_DATAMODIFIED, OnDataModified )

   ON_MESSAGE( WM_QMRESTOREDEFAULT, OnQMRestoreDefault )

   ON_MESSAGE( WM_SETCONTEXTHELPID, OnSetContextHelpID )
   ON_MESSAGE( WM_COMMANDHELP, OnCommandHelp )

#ifdef _INC_SPREAD
   ON_MESSAGE( SSM_TEXTTIPFETCH, OnSpreadTextTipFetch )   // SAC 6/7/00 - Spreadsheet control tooltip message processing
   ON_MESSAGE( WM_QM_DELETE_ROW, OnQMDeleteRow)
#endif

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSACDlg message handlers

HBRUSH CSACDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}


BOOL CSACDlg::OnInitDialog() 
{
   BOOL bRetVal = TRUE;
	CDialog::OnInitDialog();

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

   m_bWizardFrame.SetFont( GetWizFont( FNT_STD ), FALSE );

   if (m_bInitializeDialog)
   {
      // first set the dialog's caption
      SetWindowText( m_sCaption );

//      // then size & position dialog
//      m_iDlgWidth  = FontX( m_iBaseWidth );  //WIZDLG_WD   );
//      m_iDlgHeight = FontY( m_iBaseHeight );  //WIZDLG_HT   );
//      MoveWindow( (appCXFullScreen/2) - (m_iDlgWidth/2), (appCYFullScreen/2) + FontY(20) - (m_iDlgHeight/2), m_iDlgWidth, m_iDlgHeight, FALSE );
//
//      // accounts for dialog borders & caption bar height
//      int iDlgClientWidth  = m_iDlgWidth  - 6;
//      int iDlgClientHeight = m_iDlgHeight - 6 - GetSystemMetrics(SM_CYCAPTION);
//
//      // then size & position frame
//      m_iDlgMargin = FontY( m_iBaseMargin );  //WIZDLG_MARG );
//      int iBtnHt = FontY(23);
//      m_iFrmWidth  = iDlgClientWidth  - (2 * m_iDlgMargin);
//      m_iFrmHeight = iDlgClientHeight - (3 * m_iDlgMargin) - iBtnHt + 3;
//      m_iFrmBottom = m_iFrmHeight + m_iDlgMargin - 3;
//      m_bWizardFrame.MoveWindow( m_iDlgMargin, m_iDlgMargin - 3, m_iFrmWidth, m_iFrmHeight, FALSE );

// SAC 10/27/02 - Added code to setup new graphical button stuff
      if (m_bGraphicalButtons)
      {
         m_btnHelp.SubclassDlgItem( IDC_WIZHELP, this );
         m_btnHelp.SetBitmaps(      IDB_EQ_HELP32, RGB(0,0,0), IDB_EQ_HELP32G, RGB(0,0,0) );
			BYTE bHlpAlign;
			if (m_bShowPrevNextButtons)
				bHlpAlign = CBEMProcCtrlBtnST::ST_ALIGN_HORIZ;
			else
				bHlpAlign = CBEMProcCtrlBtnST::ST_ALIGN_HORIZ_RIGHT;
         m_btnHelp.SetAlign(        bHlpAlign );

         m_btnPrev.SubclassDlgItem( IDC_PREVSCREEN, this );
         m_btnPrev.SetBitmaps(      IDB_EQ_PREV32, RGB(0,0,0), IDB_EQ_PREV32G, RGB(0,0,0) );
         m_btnPrev.SetAlign(        CBEMProcCtrlBtnST::ST_ALIGN_HORIZ );
         m_btnPrev.SetWindowText(   "&Previous\nScreen" );

         m_btnNext.SubclassDlgItem( IDC_NEXTTOPIC, this );
         m_btnNext.SetBitmaps(      IDB_EQ_NEXT32, RGB(0,0,0), IDB_EQ_NEXT32G, RGB(0,0,0) );
         m_btnNext.SetAlign(        CBEMProcCtrlBtnST::ST_ALIGN_HORIZ_RIGHT );
         m_btnNext.SetWindowText(   "&Next\nScreen" );

         m_btnOK.SubclassDlgItem(   IDOK, this );
         m_btnOK.SetBitmaps(        IDB_EQ_STAR32, RGB(0,0,0), IDB_EQ_STAR32G, RGB(0,0,0) );
         m_btnOK.SetAlign(          CBEMProcCtrlBtnST::ST_ALIGN_HORIZ_RIGHT );

         if (m_bEnableCancelBtn)
         {
            m_btnCancel.SubclassDlgItem( IDCANCELBTN, this );
            m_btnCancel.SetBitmaps(      IDB_EQ_CANC32, RGB(0,0,0), IDB_EQ_CANC32G, RGB(0,0,0) );
            m_btnCancel.SetAlign(        CBEMProcCtrlBtnST::ST_ALIGN_HORIZ_RIGHT );
         }
      }

	// SAC 2/10/01 - dynamic dialog height feature
      m_iMaxHeight = FontY( m_iBaseHeight );
      m_iDlgHeight = -1;
      ResetHeight( FALSE );

      // SAC 2/25/99 - install alternative Finish button caption
      if (m_sFinishButtonText.GetLength() > 0)
      {
         CWnd* pWnd = GetDlgItem( IDOK );
         if (pWnd)
            pWnd->SetWindowText( m_sFinishButtonText );
      }

      m_bInitializeDialog = FALSE;

      CreateUIControls( FALSE );
      bRetVal = FALSE;  // return FALSE if WE set the focus already
   }
	
   if (m_bEnableToolTips)
      EnableToolTips(TRUE);

	return bRetVal;  // return TRUE unless you set the focus to a control
	                 // EXCEPTION: OCX Property Pages should return FALSE
}


// SAC 2/10/01 - added this function to handle dynamic (ruleset-defined) dialog height resetting
void CSACDlg::ResetHeight( BOOL bRePaint ) 
{
   int iNewDlgHt = FontY( m_iBaseHeight );
// SAC 10/27/02 - Added adjustment for WinXP taller window captions (pre-WinXP caption heights were ~1.19 x system font height)
   iNewDlgHt += (int) ( GetSystemMetrics(SM_CYCAPTION) - (fntHtSys * 1.19) + 0.49 );
   if (m_lDBID_DialogHeight > 0)
   {
      long lDlgHt;
      if (BEMPX_SetDataInteger( m_lDBID_DialogHeight, lDlgHt ))
      {
         m_iBaseHeight = lDlgHt;
         iNewDlgHt = FontY( lDlgHt );
      }
   }

// SAC 10/27/02 - Added height offset to accomodate new graphical buttons
   int iBtnHtOffset = (m_bGraphicalButtons ? FontY(11) : 0);
   iNewDlgHt += iBtnHtOffset;

   if (iNewDlgHt != m_iDlgHeight)
   {
      // then size & position dialog
      m_iDlgWidth  = FontX( m_iBaseWidth );  //WIZDLG_WD   );
      m_iDlgHeight = iNewDlgHt;  // FontY( m_iBaseHeight );  //WIZDLG_HT   );
      MoveWindow( (appCXFullScreen/2) - (m_iDlgWidth/2), (appCYFullScreen/2) + FontY(20) - (m_iMaxHeight/2), m_iDlgWidth, m_iDlgHeight, bRePaint );

      // accounts for dialog borders & caption bar height
		int iPaddedBorderWd = GetSystemMetrics(SM_CXPADDEDBORDER);	// SAC 10/29/14 - added to adjust for wider Win8 borders
      int iDlgClientWidth  = m_iDlgWidth  - 6 - (iPaddedBorderWd * 2);
      int iDlgClientHeight = m_iDlgHeight - 6 - (iPaddedBorderWd * 2) - GetSystemMetrics(SM_CYCAPTION);

      // then size & position frame
      m_iDlgMargin = FontY( m_iBaseMargin );  //WIZDLG_MARG );
      int iBtnHt = FontY(23) + iBtnHtOffset;  // SAC 10/27/02
      m_iFrmWidth  = iDlgClientWidth  - (2 * m_iDlgMargin);
      m_iFrmHeight = iDlgClientHeight - (3 * m_iDlgMargin) - iBtnHt + 3;
      m_iFrmBottom = m_iFrmHeight + m_iDlgMargin - 3;
      m_bWizardFrame.MoveWindow( m_iDlgMargin, m_iDlgMargin - 3, m_iFrmWidth, m_iFrmHeight, bRePaint );

      // then size & position buttons
      int iIDs[]  = { IDCANCELBTN,  IDOK,  IDC_NEXTTOPIC,  IDC_PREVSCREEN,  IDC_WIZHELP,  -1 };
      int iWds[]  = { (m_bEnableCancelBtn     ? FontX( 60) : -1),  FontX(m_iFinishBtnWd),  (m_bShowPrevNextButtons ? FontX(80) : -1),
                      (m_bShowPrevNextButtons ? FontX( 80) : -1),  FontX(60)  };
      int iGWds[] = { (m_bEnableCancelBtn     ? FontX( 85) : -1),  FontX(m_iFinishBtnWd),  (m_bShowPrevNextButtons ? FontX(90) : -1),   // SAC 10/27/02
                      (m_bShowPrevNextButtons ? FontX(100) : -1),  FontX(75)  };
      m_iLeftButtonX = iDlgClientWidth;
      int iY = iDlgClientHeight - m_iDlgMargin - iBtnHt;
      int i = -1;
      while (iIDs[++i] >= 0)
      {
         CWnd* pWnd = GetDlgItem( iIDs[i] );
         ASSERT( pWnd );
         if (pWnd)
         {
            if (iWds[i] == -1)
            {  // Hide it
               pWnd->EnableWindow( FALSE );
               pWnd->ShowWindow( SW_HIDE );
            }
            else
            {
               int iBtnWd = (m_bGraphicalButtons ? iGWds[i] : iWds[i]);  // SAC 10/27/02
               m_iLeftButtonX -= (m_iDlgMargin + iBtnWd);
               pWnd->MoveWindow( m_iLeftButtonX, iY, iBtnWd, iBtnHt, bRePaint );
            }
         }
      }
// SAC 6/12/01 - Replaced following code w/ preceding that includes Cancel button and performs both repos & hiding in one loop
//      if (m_bShowPrevNextButtons)
//      {
//         int iIDs[] = { IDOK, IDC_NEXTTOPIC, IDC_PREVSCREEN, IDC_WIZHELP };
//         int iWds[] = { FontX(60), FontX(80), FontX(80), FontX(60) };
//         m_iLeftButtonX = iDlgClientWidth;
//         int iY = iDlgClientHeight - m_iDlgMargin - iBtnHt;
//         for (int i=0; i<4; i++)
//         {
//            CWnd* pWnd = GetDlgItem( iIDs[i] );
//            if (pWnd)
//            {
//               m_iLeftButtonX -= (m_iDlgMargin + iWds[i]);
//               pWnd->MoveWindow( m_iLeftButtonX, iY, iWds[i], iBtnHt, bRePaint );
//            }
//         }
//      }
//      else
//      {
//         int iIDs[] = { IDOK, IDC_WIZHELP };
//         int iWds[] = { FontX(60), FontX(60) };
//         m_iLeftButtonX = iDlgClientWidth;
//         int iY = iDlgClientHeight - m_iDlgMargin - iBtnHt;
//         for (int i=0; i<2; i++)
//         {
//            CWnd* pWnd = GetDlgItem( iIDs[i] );
//            if (pWnd)
//            {
//               m_iLeftButtonX -= (m_iDlgMargin + iWds[i]);
//               pWnd->MoveWindow( m_iLeftButtonX, iY, iWds[i], iBtnHt, bRePaint );
//            }
//         }
//
//         int iHideIDs[] = { IDC_NEXTTOPIC, IDC_PREVSCREEN };
//         for (i=0; i<2; i++)
//         {
//            CWnd* pWnd = GetDlgItem( iHideIDs[i] );
//            if (pWnd)
//            {
//               pWnd->EnableWindow( FALSE );
//               pWnd->ShowWindow( SW_HIDE );
//            }
//         }
//      }
   }
}


// SAC 3/8/99 - added to enable edit control filename entry character checking
BOOL CSACDlg::CheckEditCtrlCharacters( long lDBID )
{
   if (m_plCheckCharDBIDs)
   {
      for (int i=0; i<m_iNumCheckCharDBIDs; i++)
         if (m_plCheckCharDBIDs[i] == lDBID)
            return TRUE;
   }
   return FALSE;
}


// SAC 7/3/00 - added to ensure that the original screen ID is VALID - otherwise, bring up the first valid screen
long CSACDlg::GetCurrentScreenID( BOOL bVerifyIDInArray )
{
   long iRetVal = 0;
// SAC 1/31/01 - Added this first if statement to enable m_lDBID_ScreenID to equal a static screen ID value (vs. a DBID)
   if (m_lDBID_ScreenID < BEMPX_GetDBID(1,0,0))
      iRetVal = m_lDBID_ScreenID;
   else if (!BEMPX_SetDataInteger( m_lDBID_ScreenID, iRetVal ))
      iRetVal = 0;
   else
   {
      ASSERT( iRetVal > 0 );

      if (bVerifyIDInArray  &&  m_lDBID_ScreenIDArray > 0)
      {  // make sure that the returned ScreenID is valid, and if not, return the FIRST available screen ID
         long iFirstAvailableID = 0, iFirstAvailableIdx = 0, iThisScreenID = 0, i0ScreenIdx = 0;
         do
         {
            if (BEMPX_SetDataInteger( m_lDBID_ScreenIDArray + i0ScreenIdx++, iThisScreenID ))
            {
               if (iThisScreenID > 0  &&  iFirstAvailableID == 0)
               {
                  iFirstAvailableID  = iThisScreenID;
                  iFirstAvailableIdx = i0ScreenIdx - 1;
               }
            }
            else
               iThisScreenID = 0;
         } while (iThisScreenID != 0  &&  iThisScreenID != iRetVal);

         if (iThisScreenID == iRetVal)
         {
            // Set ScreenIdx
            i0ScreenIdx--;
            BEMPX_SetBEMData( m_lDBID_ScreenIdx, BEMP_Int, (void*) &i0ScreenIdx );
         }
         else if (iFirstAvailableID > 0)
         {  // original ID no good, so select the first valid ID
            BEMPX_SetBEMData( m_lDBID_ScreenID,  BEMP_Int, (void*) &iFirstAvailableID );
            BEMPX_SetBEMData( m_lDBID_ScreenIdx, BEMP_Int, (void*) &iFirstAvailableIdx );
            iRetVal = iFirstAvailableID;
         }
         else
         {
            ASSERT( FALSE );
         }
      }
   }

   return iRetVal;
}


void CSACDlg::CreateUIControls( BOOL bResetEntireScreen, long lFocusDBID )
{
   CWaitCursor busyCursor;

   if (bResetEntireScreen)
   {
      // First delete all UI controls
      DeleteUIControls();

      // then erase the frame contents
      EraseControlArea();

      // then evaluate the wizard rulelist
      EvaluateRules();
   }

//   int iDT, iSV, iError;
//   long* pScrnID = (long*) BEMPX_GetBEMData( m_lDBID_ScreenID, iDT, iSV, iError );
//   if ( (iError >= 0) && pScrnID && (*pScrnID > 0) )
//   {
//      m_iCurrentScreenID = (int) *pScrnID;
// SAC 7/3/00 - replace above w/ below to ensure original screen ID is valid!
   long iScrnID = GetCurrentScreenID( !bResetEntireScreen );
   if (iScrnID > 0)
   {
      m_iCurrentScreenID = iScrnID;
      m_pTDPage = eScreenData.GetPageByID( m_iCurrentScreenID );
      if (m_pTDPage)
      {
         // First set frame name based on screen label
// SAC 2/8/01 - Added code to hide frame when caption == " "
         if (m_pTDPage->m_sCaption.Compare( " " ) == 0)
            m_bWizardFrame.ShowWindow( SW_HIDE );
         else
         {
            m_bWizardFrame.SetWindowText( m_pTDPage->m_sCaption );
            if (!m_bWizardFrame.IsWindowVisible())
               m_bWizardFrame.ShowWindow( SW_SHOW );
         }

         CWaitCursor wait;
         m_lContextHelpID = 0;

         // SAC 2/25/99 - add code to grab UI control DBID offset from BEMProc
         m_lCtrlDBIDOffset = 0;
         if (m_lDBID_CtrlDBIDOffset > 0)
         {
            if (!BEMPX_SetDataInteger( m_lDBID_CtrlDBIDOffset, m_lCtrlDBIDOffset ))
               MessageBox( "CSACDlg Error:  CtrlDBIDOffset retrieval failed." );

            // SAC 3/2/99 - added call to setup DBID offsets for all UI ctrl condition DBIDs corresponding
            //              to the same class as the main dlg page's class
            eScreenData.SetupControlConditionDBIDOffsets( m_pTDPage, m_lCtrlDBIDOffset );
         }

         // Then create the various UI controls
		 int i=m_pTDPage->m_iFirstCtrlIdx;
         for (; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if ( pCtrl && BEMPX_GetCompDisplay( pCtrl->m_lDBID + m_lCtrlDBIDOffset, 0 ) )
            {
               pCtrl->m_bActive = TRUE;  // for now, m_bActive simply means the control was created
               if (pCtrl->m_uiCtrlType == TDCT_Edit)
               {
                  CEditCtl* pEdit = new CEditCtl();
                  pEdit->Create( this, pCtrl, TRUE, m_lCtrlDBIDOffset, FALSE, FALSE, CheckEditCtrlCharacters( pCtrl->m_lDBID ),
                                 (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_Combo || pCtrl->m_uiCtrlType == TDCT_ExtCmb)   // SAC 6/4/01
               {
                  // SAC 1/31/00 - modified call to handle special case where combo is to present list of all possible screens to visit
                  long lDBIDScrnIDArr = ( (pCtrl->m_lDBID == m_lDBID_ScreenIdx  &&  m_lDBID_ScreenIDArray > 0) ?
                                          m_lDBID_ScreenIDArray : 0 );
                  if (pCtrl->m_uiCtrlType == TDCT_Combo)
                  {
                     CComboBoxCtl* pCmbb = new CComboBoxCtl();
                     pCmbb->Create( this, pCtrl, TRUE, m_lCtrlDBIDOffset, FALSE, TRUE, FALSE, lDBIDScrnIDArr,
                                    (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
                  }
                  else  // pCtrl->m_uiCtrlType == TDCT_ExtCmb
                  {
                     CExtendedComboBox* pExtCmb = new CExtendedComboBox();
                     pExtCmb->Create( this, pCtrl, TRUE, m_lCtrlDBIDOffset, FALSE, TRUE, FALSE, lDBIDScrnIDArr,
                                      (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
                  }
               }
               else if ( (pCtrl->m_uiCtrlType == TDCT_Button) ||
                         (pCtrl->m_uiCtrlType == TDCT_Check)  || 
                         (pCtrl->m_uiCtrlType == TDCT_RadioG) ||
                         (pCtrl->m_uiCtrlType == TDCT_Radio)  )
               {
                  CButtonCtl* pBtn = new CButtonCtl();
                  pBtn->Create( this, pCtrl, TRUE, m_lCtrlDBIDOffset, FALSE, TRUE, TRUE, FALSE,
                                (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_WMF)
               {
                  CWMFCtl* pWMF = new CWMFCtl();
                  pWMF->Create( this, pCtrl, m_lCtrlDBIDOffset, m_iFrmHeight, m_iFrmWidth, ::GetSysColor( COLOR_WINDOW ), FALSE );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_Floor)
               {
				   ASSERT( FALSE );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_Date)
               {
                   CDateTimeCtl* pDate = new CDateTimeCtl();
                   pDate->Create( this, pCtrl, TRUE, m_lCtrlDBIDOffset, FALSE, TRUE, TRUE, FALSE,
                                  (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_Spread)
               {
#ifdef _INC_SPREAD
                  CBEMProcCtrlSpread* pSpread = new CBEMProcCtrlSpread();
                  if (pSpread)
                     pSpread->Create( this, pCtrl, m_bIncludeCompParamStrInToolTip, m_bIncludeStatusStrInToolTip,
                                      0, 0, (m_bUsePageIDForTopicHelp ? (m_pTDPage->m_iPageId + m_iHelpIDOffset) : 0) );
//                   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, int iDX = 0, int iDY = 0, UINT uiTopicHelpID = 0 );
#else
                  MessageBox( "CSACDlg Error:  Spreadsheet control not available." );
                  pCtrl->m_bActive = FALSE;
#endif
               }
               else if (pCtrl->m_uiCtrlType == TDCT_List)
               {
                   CBEMProcCtrlList* pList = new CBEMProcCtrlList();
                   pList->Create( this, pCtrl );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_ChkLst)  // SAC 7/14/00
               {
                   CBEMProcCtrlCheckListBox* pChkList = new CBEMProcCtrlCheckListBox();
                   pChkList->Create( this, pCtrl );
               }
               else if (pCtrl->m_uiCtrlType == TDCT_RTF)  // SAC 7/15/00
               {
                   CBEMProcCtrlRTF* pRTF = new CBEMProcCtrlRTF();
                   pRTF->Create( this, pCtrl );
               }
               else
                  pCtrl->m_bActive = FALSE;
            }
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
// SAC 6/12/00 - added if statement to prevent spreadsheet from being displayed prior to it getting all setup
                     if (pCtrl->m_uiCtrlType != TDCT_Spread)
                        pWnd->ShowWindow( SW_SHOW );

// SAC 6/12/00 - no need to call DISPLAYDATA here, since it is called automatically upon the first call to OnPaint() -> PaintScreenStuff() -> DisplayMods()
//                     pWnd->PostMessage( WM_DISPLAYDATA );  //SendMessage( WM_DISPLAYDATA );

                     // get pointer to first active UI control to later set focus
                     if ( pCtrl->m_uiCtrlType == TDCT_Edit   ||
                          pCtrl->m_uiCtrlType == TDCT_Combo  ||
                          pCtrl->m_uiCtrlType == TDCT_ExtCmb ||   // SAC 6/4/01
                          pCtrl->m_uiCtrlType == TDCT_Button ||
#ifdef _INC_SPREAD
                          pCtrl->m_uiCtrlType == TDCT_Spread ||
#endif
                          pCtrl->m_uiCtrlType == TDCT_List   ||
                          pCtrl->m_uiCtrlType == TDCT_ChkLst ||
                          pCtrl->m_uiCtrlType == TDCT_Check  || 
                          pCtrl->m_uiCtrlType == TDCT_RadioG ||
                          pCtrl->m_uiCtrlType == TDCT_Radio  ||
                          pCtrl->m_uiCtrlType == TDCT_RTF    )
                     {
                        if (pFirstActiveCtrl == NULL)
                           pFirstActiveCtrl = pWnd;
                        else if (lFocusDBID > 0  &&  pCtrl->m_lDBID == lFocusDBID)
                           pFirstActiveCtrl = pWnd;
                     }
                  }
                  else
                     pCtrl->m_bActive = FALSE;
               }
            }
         }

         if (pFirstActiveCtrl)
            pFirstActiveCtrl->SetFocus();

         ActivateButtons();
      }
   }
}


// SAC 1/31/00 - added
int CSACDlg::GetScreenID( BOOL bPrevious, BOOL bSetBEMData )
{
   ASSERT( m_lDBID_ScreenIDArray > 0 );
   long l0ScreenIdx;
   if (BEMPX_SetDataInteger( m_lDBID_ScreenIdx, l0ScreenIdx ))
   {
      long lScreenID = 1;
      int iDelta = (bPrevious ? -1 : 1);
      l0ScreenIdx += iDelta;
      while (l0ScreenIdx >= 0 && lScreenID != 0)
      {
         if (BEMPX_SetDataInteger( m_lDBID_ScreenIDArray + l0ScreenIdx, lScreenID ))
         {
            if (lScreenID > 0)
            {
               if (bSetBEMData)
               {
                  // Set ScreenID
                  int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenID, BEMP_Int, (void*) &lScreenID );
                  // Set ScreenIdx
                  iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenIdx, BEMP_Int, (void*) &l0ScreenIdx );
               }

               return lScreenID;
            }
         }
         else
            lScreenID = 0;

         l0ScreenIdx += iDelta;
      }
   }
   return 0;
}


void CSACDlg::ActivateButtons()
{
   int iSV, iError;
   CWnd* pFocusWnd = GetFocus();

   CWnd* pPrevBtn = NULL;
   CWnd* pNextBtn = NULL;
   if (m_bShowPrevNextButtons)
   {
      // enable/disable Previous button
      pPrevBtn = GetDlgItem( IDC_PREVSCREEN );
      if (pPrevBtn && m_lDBID_ScreenIdx > 0)
      {
         // SAC 1/31/00 - new ScreenIDArray-based version
         if (m_lDBID_ScreenIDArray > 0)
            pPrevBtn->EnableWindow( (GetScreenID( TRUE, FALSE ) > 0) );
         else
         {  // old version (non-ScreenIDArray-based)
//            long* pScrnIdx = (long*) BEMPX_GetBEMData( m_lDBID_ScreenIdx, iDT, iSV, iError );
				long lScrnIdx = BEMPX_GetInteger( m_lDBID_ScreenIdx, iSV, iError );
            if (iError >= 0)
               pPrevBtn->EnableWindow( (lScrnIdx > 0) );
         }
      }

      // enable/disable Next button
      pNextBtn = GetDlgItem( IDC_NEXTTOPIC );
      if (pNextBtn)
      {
         // SAC 1/31/00 - new ScreenIDArray-based version
         if (m_lDBID_ScreenIDArray > 0)
            pNextBtn->EnableWindow( (GetScreenID( FALSE, FALSE ) > 0) );
         else if (m_lDBID_NextScreenID > 0)
         {  // old version (non-ScreenIDArray-based)
//            long* pNextScrnID = (long*) BEMPX_GetBEMData( m_lDBID_NextScreenID, iDT, iSV, iError );
				long lNextScrnID = BEMPX_GetInteger( m_lDBID_NextScreenID, iSV, iError );
            if (iError >= 0)
               pNextBtn->EnableWindow( (lNextScrnID > 0) );
         }
      }
   }

   // enable/disable Finish button
   CWnd* pFinBtn = GetDlgItem( IDOK );
   if (pFinBtn && m_lDBID_EnableFinish > 0)
   {
//      long* pEnableFin = (long*) BEMPX_GetBEMData( m_lDBID_EnableFinish, iDT, iSV, iError );
		long lEnableFin = BEMPX_GetInteger( m_lDBID_EnableFinish, iSV, iError );
      if (iError >= 0)
         pFinBtn->EnableWindow( (lEnableFin > 0) );
   }

   // reset focus if we just disabled the button with the focus
   if ( (pFocusWnd == pPrevBtn && pPrevBtn && !pPrevBtn->IsWindowEnabled()) ||
        (pFocusWnd == pNextBtn && pNextBtn && !pNextBtn->IsWindowEnabled()) ||
        (pFocusWnd == pFinBtn  && pFinBtn  && !pFinBtn->IsWindowEnabled( )) )
   {
      if (pNextBtn && pNextBtn->IsWindowEnabled())
         pNextBtn->SetFocus();
      else if (pFinBtn && pFinBtn->IsWindowEnabled())
         pFinBtn->SetFocus();
      else if (pPrevBtn && pPrevBtn->IsWindowEnabled())
         pPrevBtn->SetFocus();
      // else ????
   }
}


LONG CSACDlg::OnDataModified( UINT wEval, LONG lDBID )
{
   if (wEval == 1)
      // execute compliance rulelist #1
      EvaluateRules();

   // SAC 2/1/00 - Special handling for m_lDBID_ScreenIDArrIdx
   if (lDBID == m_lDBID_ScreenIdx  &&  m_lDBID_ScreenIDArray > 0)
   {
      // Grab new ScreenIdx
      long l0ScreenIdx;
      VERIFY( BEMPX_SetDataInteger( m_lDBID_ScreenIdx, l0ScreenIdx ) );

      // Grab new ScreenID from ScreenIDArray
      long lScreenID;
      VERIFY( BEMPX_SetDataInteger( m_lDBID_ScreenIDArray + l0ScreenIdx, lScreenID ) );

      // Set new ScreenID
      int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenID, BEMP_Int, (void*) &lScreenID );		iSetDataRetVal;

      // Reset entire dialog
      CreateUIControls( TRUE, m_lDBID_ScreenIdx );
   }
   else
      // redisplay all currently displayed database data
      DisplayMods(0,0);

// SAC 9/25/01 - Capture retrun value and use to enable re-evaluation and display for special cases like custom footprint & zoning
   // pass message on to MainFrame in order to tag Doc data as modified
   int iFrameRetVal = GetParentFrame()->SendMessage( WM_DATAMODIFIED, 2 /*PDCS_BEM*/, lDBID );
   // perform re-defaulting and display to support custom footprint shapes & zoning patterns
   if (iFrameRetVal > 0)
   {  // re-evaluate ruleset and display mods
      EvaluateRules();
      DisplayMods(0,0);
   }

   return 0;
}


void CSACDlg::EvaluateRules(UINT uiList)
{
   CWaitCursor wait;
   BOOL bEvalOK = ( uiList == 0 ? (m_sMidProcRulelist.GetLength()  > 0 && BEMPX_EvaluateRuleList( m_sMidProcRulelist  ))
                                : (m_sPostProcRulelist.GetLength() > 0 && BEMPX_EvaluateRuleList( m_sPostProcRulelist )) );
   if (bEvalOK && uiList == 0)
   {
      ActivateButtons();
   }
}


LONG CSACDlg::OnQMRestoreDefault( UINT uiDBInstP1, LONG lDBID )
{
   int iError;
   int iDBInst = uiDBInstP1 - 1;
   BEMPX_DefaultProperty( lDBID, iError, iDBInst );
   if (iError >= 0)
   {
      // execute compliance rulelist #1
      EvaluateRules();

      // redisplay all currently displayed database data
      DisplayMods(0,0);

// SAC 9/25/01 - Added additional processing to handle special cases, like re-defaulting custom footprint & zoning settings
      // pass message on to MainFrame in order to tag Doc data as modified
      int iFrameRetVal = GetParentFrame()->SendMessage( WM_DATAMODIFIED, 2 /*PDCS_BEM*/, lDBID );
      // perform re-defaulting and display to support custom footprint shapes & zoning patterns
      if (iFrameRetVal > 0)
      {  // re-evaluate ruleset and display mods
         EvaluateRules();
         DisplayMods(0,0);
      }
   }

   return 0;
}


void CSACDlg::DeleteUIControls()
{
   CWnd *pWnd = GetWindow( GW_CHILD );
   CWnd *pNext = NULL;
   while ( pWnd != NULL )
   {
      pNext = pWnd->GetNextWindow( GW_HWNDNEXT );

      if (    (pWnd->IsKindOf(RUNTIME_CLASS(CEditCtl     )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CComboBoxCtl )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CExtendedComboBox)))  // SAC 6/4/01
           || (pWnd->IsKindOf(RUNTIME_CLASS(CButtonCtl   )))
#ifdef _INC_SPREAD
           || (pWnd->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlSpread)))
#endif
           || (pWnd->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlList )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CWMFCtl      )))
//           || (pWnd->IsKindOf(RUNTIME_CLASS(CFloorPlanCtl)))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CDateTimeCtl )))
           || (pWnd->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlCheckListBox )))  // SAC 7/14/00
           || (pWnd->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlRTF  )))  // SAC 7/15/00
           )
         pWnd->DestroyWindow();
         
      pWnd = pNext;
   }
}


void CSACDlg::EraseControlArea()
{
   CDC* pDC = GetDC();
   if (pDC)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );

      CRect rc;
      // define rectangle to lie just inside Frame
      GetClientRect(rc);
      rc.top    += (m_iDlgMargin + FontY(13));
      rc.bottom  = m_iFrmBottom - 2;
      rc.left   += (m_iDlgMargin + 2);
      rc.right  -= (m_iDlgMargin + 2);
      pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);

      // 2nd round to erase area below frame and to the left of the buttons
      GetClientRect(rc);
      rc.top     = m_iFrmBottom + 3;
      rc.bottom -= 2;
      rc.left   += 2;
      rc.right   = m_iLeftButtonX - 2;
      pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);

      ReleaseDC( pDC );
   }
}


// Externs defined in SACWizardDlg.cpp
//
//void WriteLineToDC( CDC* pDC, BOOL bColor, int fromX, int fromY, int toX, int toY, int iThickness )
//{
//   if (iThickness == -1)
//   {  // => Shadow Line
//      pDC->SelectObject( (bColor ? &btnShadowPen : &dialogPen) );
//      pDC->MoveTo( fromX, fromY );
//      pDC->LineTo( toX  , toY   );
//
//      pDC->SelectObject( (bColor ? &btnHighlightPen : &dialogPen) );
//      if (fromX != toX)
//      {
//         pDC->MoveTo( fromX, fromY+1 );
//         pDC->LineTo( toX  , toY  +1 );
//      }
//      else
//      {
//         pDC->MoveTo( fromX+1, fromY );
//         pDC->LineTo( toX  +1, toY   );
//      }
//   }
//   else
//   {  // => Standard Line
//      CPen pen;
//      pen.CreatePen( PS_SOLID, iThickness,
//                     (bColor ? RGB(0,0,0) : ::GetSysColor( COLOR_BTNFACE )) );
//      pDC->SelectObject( &pen );
//
//      pDC->MoveTo( fromX, fromY );
//      pDC->LineTo( toX  , toY   );
//      pDC->SelectObject( &blackPen );
//   }
//}
//
//void WriteLineCtrlToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset )
//{
//   WriteLineToDC( pDC, pCtrl->CanDisplay(), FontX( pCtrl->m_iX ), FontY( pCtrl->m_iY ) + iYOffset,
//                  FontX( pCtrl->m_iHeight), FontY( pCtrl->m_iWidth ) + iYOffset, pCtrl->m_lValue );
//}
//
//
//void WriteLabelToDC( CDC* pDC, CBEMPUIControl* pCtrl, long lCtrlDBIDOffset, int iYOffset )
//{
//   // Label w/ units DX = -1 => Don't Erase via writing w/ gray text
//   if (pCtrl->m_iUnitDX != -1 || pCtrl->CanDisplay())
//   {
//      CString sLabel = pCtrl->m_sLbl;
//
//      if (pCtrl->m_lDBID > 0)
//      {
//         CString sData;
//         BEMPX_SetDataString( pCtrl->m_lDBID + lCtrlDBIDOffset, sData, (pCtrl->m_lValue >= 0),
//                            (int) pCtrl->m_lValue, -1, pCtrl->m_iDBInstance, BEMO_User, NULL, pCtrl->m_lDBID2 );
//         sLabel += sData;
//      }
//      sLabel += pCtrl->m_sStatusMsg;
//
//      pDC->SetBkMode( TRANSPARENT );
//      pDC->SelectObject( GetWizFont(pCtrl->m_iFont) );
//      pDC->SetTextAlign( pCtrl->m_uiLblJust );
//
//      COLORREF crPrevTextColor;
//      if (!pCtrl->CanDisplay())
//         crPrevTextColor = pDC->SetTextColor( ::GetSysColor( COLOR_BTNFACE ) );
//
//      // Trim label to fit into the available m_iWidth (iff m_iWidth > 0)
//      // (also add trailing '...' if any characters are trimmed)
//      if (pCtrl->m_iWidth > 0)
//      {
//         int iWidth = FontX(pCtrl->m_iWidth);
//         CSize size = pDC->GetTextExtent( sLabel );
//         if (size.cx > iWidth)
//         {
//            CString sTrail = "...";
//            CString sTemp = sLabel;
//            sLabel += sTrail;
//            while (size.cx > iWidth)
//            {
//               if (sTemp.GetLength() > 1)
//               {
//                  sTemp = sTemp.Left( sTemp.GetLength()-1 );
//                  sLabel = sTemp + sTrail;
//                  size = pDC->GetTextExtent( sLabel );
//               }
//               else
//                  break;
//            }
//         }
//      }
//
//      if ( sLabel.GetLength() > 0)
//         pDC->TextOut( FontX(pCtrl->m_iX), FontY(pCtrl->m_iY) + iYOffset, sLabel );
//
//      // If Unit DX > 0 then draw a horizontal shadow line from the end of the text to the UnitDX position
//      if (pCtrl->m_iUnitDX > 0 && pCtrl->m_uiLblJust == TA_LEFT)
//      {
//         CSize size = pDC->GetTextExtent( sLabel );
//         int iLeftX = FontX(pCtrl->m_iX) + size.cx + FontX(6);
//         int iRightX = FontX(pCtrl->m_iUnitDX);
//         int iMidY = FontY(pCtrl->m_iY) + iYOffset + (GetWizFontHeight(pCtrl->m_iFont) / 2);
//         if (iRightX > iLeftX)
//            WriteLineToDC( pDC, pCtrl->CanDisplay(), iLeftX, iMidY, iRightX, iMidY, -1 );
//      }
//
//      // reset text color to original setting
//      if (!pCtrl->CanDisplay())
//         pDC->SetTextColor( crPrevTextColor );
//   }
//}
//
//
//// SAC 6/21/00 - added
//void WriteRectToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset )
//{
//   ASSERT( pDC );
//   ASSERT( pCtrl );
//   if (pCtrl->CanDisplay())
//   {
//      int left    = FontX( pCtrl->m_iX );
//      int top     = FontY( pCtrl->m_iY ) + iYOffset;
//      int right   = left + FontX( pCtrl->m_iWidth  );
//      int bottom  = top  + FontY( pCtrl->m_iHeight ) + iYOffset;
////      int roundWd = pRect->m_iRoundWd;
////      int roundHt = pRect->m_iRoundHt;
////      int thick   = pRect->m_iBoundThick;
//      BOOL bShadowOutline = (pCtrl->m_iBoundThickness == -1);
//
//      CRgn tempRgn;
////      if ( (pRect->m_iRoundWd < 1) && (pRect->m_iRoundHt < 1) )
//         tempRgn.CreateRectRgn( left, top, right, bottom );
////      else
////         tempRgn.CreateRoundRectRgn( left, top, right, bottom, roundWd, roundHt );
//
//      CBrush brushF;
//      BOOL bFill = TRUE;
//      if ( (pCtrl->m_iFillRed >= 0) && (pCtrl->m_iFillGreen >= 0) && (pCtrl->m_iFillBlue >= 0) )
//         brushF.CreateSolidBrush( RGB( pCtrl->m_iFillRed, pCtrl->m_iFillGreen, pCtrl->m_iFillBlue) );
//      else if ( (pCtrl->m_iFillRed == -2) && (pCtrl->m_iFillGreen == -2) && (pCtrl->m_iFillBlue == -2) )
//         brushF.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
//      else
//         bFill = FALSE;
//      if (bFill)
//         pDC->FillRgn( &tempRgn, &brushF );
//
//      if (bShadowOutline)
//      {
//         pDC->DrawEdge( CRect( left, top, right, bottom ), EDGE_SUNKEN, BF_RECT );
////         pDC->Draw3dRect( int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight );
//      }
//      else if (pCtrl->m_iBoundThickness > 0)
//      {
//         int thick = FontY( pCtrl->m_iBoundThickness );
//         CBrush brushB;
//         BOOL bBound = TRUE;
//         if( pDC->IsPrinting() )
//            brushB.CreateSolidBrush( RGB(0,0,0) );
//         else if ( (pCtrl->m_iBoundRed >= 0) && (pCtrl->m_iBoundGreen >= 0) && (pCtrl->m_iBoundBlue >= 0) )
//            brushB.CreateSolidBrush( RGB( pCtrl->m_iBoundRed, pCtrl->m_iBoundGreen, pCtrl->m_iBoundBlue) );
//         else if ( (pCtrl->m_iBoundRed >= -2) && (pCtrl->m_iBoundGreen >= -2) && (pCtrl->m_iBoundBlue >= -2) )
//            brushB.CreateSolidBrush( ::GetSysColor( COLOR_BTNFACE ) );
//         else
//            bBound = FALSE;
//
//         if (bBound)
//            pDC->FrameRgn( &tempRgn, &brushB, thick, thick );
//      }
//   }
//}


void CSACDlg::PaintScreenStuff( BOOL bUpdateLabelsOnly, BOOL bCallDisplayMods )
{
   CDC* pDC = GetDC();
   if (pDC)
   {
      if (m_pTDPage != NULL)
      {
         pDC->SetBkColor(   ::GetSysColor( COLOR_BTNFACE ) );
         pDC->SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
         pDC->SetBkMode( TRANSPARENT );

         for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if (pCtrl != NULL)
            {
               if (bUpdateLabelsOnly)
               {
                  if (pCtrl->m_bLabelRequiringRefresh  &&
                      // SAC 7/15/00 - added check to ensure one of the label offset values is non-zero
                      //               if they are both zero, then this label is likely a rulelist name to be evaluated (ChkList control)
                      // SAC 5/14/01 - added leading condition to ensure Label controls always refreshed when m_bLabelRequiringRefresh == TRUE
                      (pCtrl->m_uiCtrlType == TDCT_Label || pCtrl->m_iLblDX != 0 || pCtrl->m_iLblDY != 0))
                  {
                     // Erase previous label and replace it with an updated label
                     CRect rc;
                     rc.top    = FontY(pCtrl->m_iY) - 1;
                     rc.bottom = rc.top + FontY(GetWizFontHeight(pCtrl->m_iFont)) + 2;
                     if (pCtrl->m_uiLblJust == TA_LEFT)
                     {
                        rc.left  = FontX(pCtrl->m_iX) - 1;
                        rc.right = rc.left + FontX(pCtrl->m_iLblDX) + 2;
                     }
                     else if (pCtrl->m_uiLblJust == TA_RIGHT)
                     {
                        rc.right = FontX(pCtrl->m_iX) + 1;
                        rc.left  = rc.right - FontX(pCtrl->m_iLblDX) - 2;
                     }
                     else if (pCtrl->m_uiLblJust == TA_CENTER)
                     {
                        int iDX = (int) (0.5 * FontX(pCtrl->m_iLblDX));
                        rc.left  = FontX(pCtrl->m_iX) - iDX - 1;
                        rc.right = FontX(pCtrl->m_iX) + iDX + 1;
                     }
                     pDC->SelectObject( GetWizFont(pCtrl->m_iFont /*FNT_STD*/) );
                     // SAC 7/3/00 - DON'T erase label rect when iUnitsDX == -1 (=> no erasure of label)
                     if (pCtrl->m_iUnitDX != -1)
                        pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);
                     
                     WriteLabelToDC( pDC, pCtrl, m_lCtrlDBIDOffset );
                  }
                  else if (pCtrl->m_uiCtrlType == TDCT_Line)
                     WriteLineCtrlToDC( pDC, pCtrl );
                  else if (pCtrl->m_uiCtrlType == TDCT_Rect)   // SAC 6/21/00
                     WriteRectToDC( pDC, pCtrl );
               }
               else
               {
                  if ( ( (pCtrl->m_uiCtrlType == TDCT_Edit  ) || 
                         (pCtrl->m_uiCtrlType == TDCT_Combo ) || 
                         (pCtrl->m_uiCtrlType == TDCT_ExtCmb) ||   // SAC 6/4/01
                         (pCtrl->m_uiCtrlType == TDCT_Date  ) || 
                         (pCtrl->m_uiCtrlType == TDCT_Floor ) ) &&
                       (pCtrl->m_bActive) &&
                       (GetDlgItem( pCtrl->m_uiCtrlID ) != NULL) ) 
                  {
                     pDC->SelectObject( GetWizFont(pCtrl->m_iFont) /*&stdFont*/ );
                     if (pCtrl->m_sLbl.GetLength() > 0  &&
                         // SAC 7/15/00 - added check to ensure one of the label offset values is non-zero
                         //               if they are both zero, then this label is likely a rulelist name to be evaluated (ChkList control)
                         (pCtrl->m_iLblDX != 0 || pCtrl->m_iLblDY != 0))
                     {
                        pDC->SetTextAlign( pCtrl->m_uiLblJust );
                        pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iLblDX) ), 
                                      FontY( (pCtrl->m_iY + pCtrl->m_iLblDY) ), pCtrl->m_sLbl );
                     }
                     if (pCtrl->m_bUnitDisp)     
                     {
                        pDC->SetTextAlign( pCtrl->m_uiUnitJust );
                        QString qsUnitLbl = BEMPX_GetBEMUnitsLabel( (pCtrl->m_lDBID2 < BEM_COMP_MULT ? pCtrl->m_lDBID : pCtrl->m_lDBID2) );
                        pDC->TextOut( FontX( (pCtrl->m_iX + pCtrl->m_iWidth + pCtrl->m_iUnitDX) ), 
                                      FontY( (pCtrl->m_iY + pCtrl->m_iUnitDY) ), qsUnitLbl.toLatin1().constData() );  // SAC 10/5/02 - Revised to reference m_lDBID2 when valid
                     }
                  }
                  else if (pCtrl->m_uiCtrlType == TDCT_Line)
                     WriteLineCtrlToDC( pDC, pCtrl );
                  else if (pCtrl->m_uiCtrlType == TDCT_Label)
                     WriteLabelToDC( pDC, pCtrl, m_lCtrlDBIDOffset );
                  else if (pCtrl->m_uiCtrlType == TDCT_Rect)   // SAC 6/21/00
                     WriteRectToDC( pDC, pCtrl );
               }
            }
         }

         if (bCallDisplayMods)
            DisplayMods(0,0);
      }

      ReleaseDC( pDC );
   }
}


void CSACDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
   PaintScreenStuff();
}


// BOOL CSACDlg::ToggleControlIfNecessary( CBEMPUIControl* pCtrl, BOOL bEraseLabels )
BOOL CSACDlg::ToggleControlIfNecessary( void* pVoidCtrl, BOOL bEraseLabels )
{
   CBEMPUIControl* pCtrl = (CBEMPUIControl*) pVoidCtrl;
   if (pCtrl && pCtrl->HaveDisplayCondition() && pCtrl->ToggleControl())
   {
      CWnd* pWnd = GetDlgItem( pCtrl->m_uiCtrlID );
      if (pWnd)
      {
         if (pCtrl->m_bActive)
            pCtrl->m_bActive = FALSE;
         else
            pCtrl->m_bActive = TRUE;

         pWnd->EnableWindow( pCtrl->m_bActive );
         pWnd->ShowWindow( (pCtrl->m_bActive ? SW_SHOW : SW_HIDE) );

         // Erase control labels
         if (bEraseLabels)
         {
            CDC* pDC = GetDC();
            if (pDC)
            {
               pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
               pDC->SelectObject( GetWizFont(pCtrl->m_iFont) /*&stdFont*/ );

               CRect rc;
               pWnd->GetClientRect( &rc );
               rc.left   += FontX( (pCtrl->m_iX + pCtrl->m_iLeftEraseX) );
               rc.right  += FontX( (pCtrl->m_iX + pCtrl->m_iRightEraseX) );
               rc.top    += FontY( pCtrl->m_iY );
					// SAC 6/20/03 - Added small margin to bottom position to ensure sliver of labels not left following refresh
               rc.bottom += FontY( pCtrl->m_iY )+2;
               pDC->ExtTextOut( rc.left+1, rc.top+1, ETO_OPAQUE, rc, " ", 1, NULL);

               ReleaseDC( pDC );
            }
         }

         return TRUE;
      }
   }
   return FALSE;
}


BOOL ControlIsActive( CBEMPUIPage* pPage, UINT uiCtrlID )
{
   if (pPage != NULL)
      for (int i=pPage->m_iFirstCtrlIdx; i<=pPage->m_iLastCtrlIdx; i++)
      {
         CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex(i);
         if (pCtrl && pCtrl->m_uiCtrlID == uiCtrlID)
            return pCtrl->m_bActive;
      }
   return TRUE;  // default
}

LONG CSACDlg::DisplayMods( UINT, LONG )
{
   CWaitCursor wait;

   // Loop over all controls, toggling them on or off based on current BEMProc data
   if (m_pTDPage != NULL)
      for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         ToggleControlIfNecessary( eScreenData.GetControlByIndex(i), TRUE );

// SAC 2/10/01 - facilitate dynamic dialog height feature
   ResetHeight();

   // refresh data displayed in each control
   CWnd *pChild = GetWindow( GW_CHILD );
   while ( pChild != NULL )
   {
      // SAC 3/9/01 - DON't send DisplayData message to hidden spreadsheets, as it will unhide them
//      if (!pChild->IsKindOf(RUNTIME_CLASS(CBEMProcCtrlSpread)) || pChild->IsWindowVisible())
//      if (pChild->IsWindowVisible())
      // SAC 3/9/01 - Only update visible children ??
      if (ControlIsActive( m_pTDPage, pChild->GetDlgCtrlID() ))
         pChild->SendMessage( WM_DISPLAYDATA );
      pChild = pChild->GetNextWindow( GW_HWNDNEXT );
   }

   // Now loop over all controls and re-display labels that display data that may have been updated
   PaintScreenStuff( TRUE, FALSE );

   ActivateButtons();

   return 1;
}


BOOL CSACDlg::OnToolTipNotify( UINT /*id*/, NMHDR* pNMHDR, LRESULT* /*pResult*/ )
{
   TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*) pNMHDR;
   UINT nID = pNMHDR->idFrom;
   if ( (pTTT->uFlags & TTF_IDISHWND) && (m_pTDPage != NULL) )
   {  // idFrom is actually the HWND of the tool
      // Convert it to its actual control ID
      nID = ::GetDlgCtrlID((HWND)nID);
      CBEMPUIControl* pTDCtrl = eScreenData.GetControlByPageAndID( m_pTDPage, nID );
// SAC 6/7/00 - added to if statement such that we don't display ToolTips for the spreadsheet from here
      if (pTDCtrl  &&  pTDCtrl->m_uiCtrlType != TDCT_Spread)
      {
         long lDBID = pTDCtrl->m_lDBID + m_lCtrlDBIDOffset;
         int iDBInstance = pTDCtrl->m_iDBInstance;

// SAC 1/10/03 - Added line of code to blast any text leftover from previous displays
//               (string gets longer & longer if no tooltip text or range message exists but flag set to display component:property info)
         m_sToolStr.Empty();

         // Use message in screen data unless not present, then default to ToolTip message
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
            BEMPUIX_GetToolTipMessage( m_sToolStr, lDBID );

         QString sRangeMsg;
		// RW 11/02/02 - We only want to generate a range message if there is no rule-based generation
         if( pTDCtrl->m_sTooltipRulelistName.IsEmpty() )
            BEMPX_GenerateRangeMessage( pTDCtrl->m_lDBID, &sRangeMsg );

         if( sRangeMsg.length() > 0 )
         {
            m_sToolStr += "\r\n";
            m_sToolStr += sRangeMsg.toLatin1().constData();
         }
         // SAC 12/18/02 - Re-integrated from RW's mods
         if (m_sToolStr.GetLength() > 0 && (m_bIncludeStatusStrInToolTip || m_bIncludeCompParamStrInToolTip))  // SAC 11/29/02 - Prevent ending up w/ tool tip with only a CR/LF
            m_sToolStr += "\r\n";

         if (m_bIncludeStatusStrInToolTip)  // SAC 9/2/00
         {
            m_sToolStr += "  (";
            m_sToolStr += GetCompDataTypeString( lDBID, m_iDialogMode );
            m_sToolStr += " data status: ";
            m_sToolStr += GetDataStatusString( lDBID, iDBInstance, m_iDialogMode );
            m_sToolStr += ")";
         }

         if (m_bIncludeCompParamStrInToolTip)  // SAC 6/3/00
         {  QString sTemp;
            BEMPX_DBIDToDBCompParamString( lDBID, sTemp );
            m_sToolStr += " - ";
            m_sToolStr += sTemp.toLatin1().constData();
         }
         if (m_bIncludeLongCompParamStrInToolTip)  // SAC 8/13/13
         {  QString sTemp;
            BEMPX_DBIDToDBCompParamString( lDBID, sTemp, true /*bLongName*/ );
            m_sToolStr += (m_bIncludeCompParamStrInToolTip ? " / " : " - ");
            m_sToolStr += sTemp.toLatin1().constData();
         }

         pTTT->lpszText = (LPTSTR)(LPCTSTR)m_sToolStr;
         pTTT->hinst = AfxGetResourceHandle();

         // RW 10/31/02 Force the tooltip to be multiline
         ::SendMessage(pNMHDR->hwndFrom, TTM_SETMAXTIPWIDTH, 0, 300);

         return(TRUE);
      }
   }
   return(FALSE);
}

int CSACDlg::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// find child window which hits the point
	// (don't use WindowFromPoint, because it ignores disabled windows)
   if (m_pTDPage != NULL)
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


/////////////////////////////////////////////////////////////////////////////
// CSACDlg Button message handlers

// SAC 8/8/00 - added iUserAction argument (0=>Prev, 1=>Next, 2=>Finish, 3=>Cancel)
BOOL CSACDlg::EditControlValuesInRange( int /*iUserAction*/ )
{
   BOOL bRetVal = TRUE;

   // loop over all child windows - verifying range checks for all edit controls
   CWnd *pChild = GetWindow( GW_CHILD );
   CWnd *pRangeErrorChild = NULL;
   CWnd *pRangeWarningChild = NULL; // RW 9/24/02 - Changed warning to be stored in a separate CWnd*
   BOOL bErrorEncountered = FALSE;
   BOOL bWarningsFound = FALSE;
   int iNumViolations = 0;
   CString sUserMsg;
   while (pChild != NULL)
   {
      long lCtrlDBID = 0;
      CString sMsg;
      int iRangeCheckReturn = 0;  // SAC 10/25/00 - Moved here form above to ensure it gets reset EVERY time
      if ( (pChild->IsKindOf(RUNTIME_CLASS(CEditCtl))) && pChild->IsWindowVisible() )
      {
         iRangeCheckReturn = ((CEditCtl*) pChild)->RangeCheckViolation( TRUE, &sMsg );  // check in silent mode first
         lCtrlDBID = ((CEditCtl*) pChild)->m_lDBID;
      }
      else if ( pChild->IsKindOf(RUNTIME_CLASS(CDateTimeCtl)) && pChild->IsWindowVisible() )
      {
         iRangeCheckReturn = ((CDateTimeCtl*) pChild)->RangeCheckViolation( TRUE, &sMsg );  // check in silent mode first
         lCtrlDBID = ((CDateTimeCtl*) pChild)->m_lDBID;
      }

      if (iRangeCheckReturn == RANGE_ERROR  ||  iRangeCheckReturn == RANGE_WARNING  ||
          iRangeCheckReturn == RANGE_MESSAGE)
      {
         if (iRangeCheckReturn == RANGE_ERROR && !bErrorEncountered)
         {
            bErrorEncountered = TRUE;
            pRangeErrorChild = pChild;  // store first ERROR as control to get focus
         }
         else if( pRangeWarningChild == NULL ) // RW 9/24/02 - Changed warning to be stored in a separate CWnd*
            pRangeWarningChild = pChild;  // store first violation as control to get focus

         // Add the range violation message to the user message
         if (iNumViolations > 0)
            sUserMsg += "\r\n\r\n";
         if (iRangeCheckReturn == RANGE_ERROR)
            sUserMsg += "ERROR:  ";
         else if (iRangeCheckReturn == RANGE_WARNING)
         {
            sUserMsg += "Warning:  ";
            bWarningsFound = TRUE;
         }
         else // if (iRangeCheckReturn == RANGE_MESSAGE)
            sUserMsg += "Message:  ";
         sUserMsg += sMsg;

         iNumViolations++;
      }

      pChild = pChild->GetNextWindow( GW_HWNDNEXT );
   }

// RW 9/24/02 - Changed the conditional to check if there is any text in the sUserMsg as it will also be populated with text if
//              errors/warnings have occurred in the RuleBasedErrorCheck routine.
//   if (iNumViolations > 0)
   if (sUserMsg.GetLength())
   {
//      sUserMsg += "\n\nDo you wish to leave this screen without addressing the above range check message(s)?";
//      sUserMsg += "\n\nSelect 'Yes' to leave this screen, or 'No' to return.";
//      bRetVal = (MessageBox( sUserMsg, "Resume Navigation?", MB_ICONQUESTION | MB_YESNO ) == IDYES);
// SAC 10/25/00 - Replaced former error message prompt via MessageBox with custom dialog
// RW 9/24/02 - Moved this label and prompt stuff from RuleBasedErrorCheck
      CString sLabel, sPrompt;
      if (bErrorEncountered &&  bWarningsFound)
         sLabel = "User input error(s) and warning(s):";
      else if (bErrorEncountered)
         sLabel = "User input error(s):";
      else
         sLabel = "User input warning(s):";

      // RW 11/26/02 - Changed how the prompt is populated depending on if errors and/or warnings are found
      if( bErrorEncountered )
      {
// SAC 12/18/02 - Minor revisions to messages for readability
         if( bWarningsFound )
            sPrompt = "You must enter an explanation for every warning message that has occurred.\n"
                      "Press 'Return' to return to the input screen.";
         else
            sPrompt = "Press 'Return' to return to the input screen.";
      }
      else // Use the string that is already in the dialog resource
         sPrompt = "";

      if (sUserMsg.GetLength())		// always true
      {
         CDlgRangeError dlgErr( sUserMsg, m_iDialogMode, this );
         dlgErr.DoModal();
         bRetVal = dlgErr.m_bContinue;
      }

      if( pRangeErrorChild == NULL )
         pRangeErrorChild = pRangeWarningChild;

      if (!bRetVal && pRangeErrorChild)
      {
         if (pRangeErrorChild->IsKindOf(RUNTIME_CLASS(CEditCtl))) // Use the specialized SetFocus routine for CEditCtl
            ((CEditCtl*) pRangeErrorChild)->SetFocus();
         else // Use the default CWnd SetFocus routine
            pRangeErrorChild->SetFocus();
//         if (pRangeErrorChild->IsKindOf(RUNTIME_CLASS(CEditCtl)))
//            ((CEditCtl*) pRangeErrorChild)->SetFocus();
//         else if (pRangeErrorChild->IsKindOf(RUNTIME_CLASS(CDateTimeCtl)))
//            ((CDateTimeCtl*) pRangeErrorChild)->SetFocus();
      }
   }

   return bRetVal;
}


void CSACDlg::OnWizardHelp() 
{
   if (m_pTDPage)
   {
      // SAC 2/7/00 - added if statement to enable parent window to handle help system call (HTML help)
      if (m_bPostHelpMessageToParent)
      {
         CWnd* pParent = GetParent();
         CFrameWnd* pFrame = GetParentFrame();
         if (pFrame  &&  pParent  &&  ( pParent->IsKindOf(RUNTIME_CLASS( CSACDlg       )) ))
            pFrame->PostMessage( WM_PARENTHELP, m_pTDPage->m_iPageId + m_iHelpIDOffset );
         else if (pParent)
            pParent->PostMessage( WM_PARENTHELP, m_pTDPage->m_iPageId + m_iHelpIDOffset );
      }
      else
      {
         CWinApp* pApp = AfxGetApp();
         if (pApp)
            pApp->WinHelp( m_pTDPage->m_iPageId + m_iHelpIDOffset );  // tested w/ '1010'
      }
   }
}

void CSACDlg::OnPreviousScreen() 
{
   if (EditControlValuesInRange( 0 ))
   {
      CWaitCursor busyCursor;

      BOOL bScreenSwitched = FALSE;
      // SAC 1/31/00 - new ScreenIDArray-based version
      if (m_lDBID_ScreenIDArray > 0)
      {
         int iScrnID = GetScreenID( TRUE, TRUE );
         if (iScrnID > 0)
            bScreenSwitched = TRUE;
      }
      else
      {
         int iSV, iError;
         long lScrnIdx = BEMPX_GetInteger( m_lDBID_ScreenIdx, iSV, iError );
         if (iError >= 0 && lScrnIdx > 0)
         {
            // Get the current PrevScreenID[ lScrnIdx ]
            long lPrevScrnIDDBID = BEMPX_GetDBID( m_iBEMCID_Wizard, BEMPX_GetPropertyID( m_lDBID_PrevScreenID ), (lScrnIdx+1) );  // SAC 7/18/01
            long lPrevScrnID = BEMPX_GetInteger( lPrevScrnIDDBID, iSV, iError );
            if (iError >= 0 && lPrevScrnID > 0)
            {
               // Set ScreenID to the current PrevScreenID[ lScrnIdx ]
               int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenID, BEMP_Int, (void*) &lPrevScrnID );

               // Decrement and set ScreenIdx
               lScrnIdx--;
               iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenIdx, BEMP_Int, (void*) &lScrnIdx );

               // Note: the NEW NextScreenID needs to be set by the Wizard Rulelist
            }

            bScreenSwitched = TRUE;
         }
      }

      if (bScreenSwitched)
         // Reset entire dialog
         CreateUIControls( TRUE );
   }
}

void CSACDlg::OnNextScreen() 
{
   if (EditControlValuesInRange( 1 ))
   {
      CWaitCursor busyCursor;

      BOOL bScreenSwitched = FALSE;
      // SAC 1/31/00 - new ScreenIDArray-based version
      if (m_lDBID_ScreenIDArray > 0)
      {
         int iScrnID = GetScreenID( FALSE, TRUE );
         if (iScrnID > 0)
            bScreenSwitched = TRUE;
      }
      else
      {
         int iSV, iError;
         // Get ScreenIdx
         long lScrnIdx = BEMPX_GetInteger( m_lDBID_ScreenIdx, iSV, iError );
         if (iError >= 0 && lScrnIdx >= 0)
         {
            // Increment and set ScreenIdx
            lScrnIdx++;
            int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenIdx, BEMP_Int, (void*) &lScrnIdx );

            // Get the current ScreenID
	         long lScrnID = BEMPX_GetInteger( m_lDBID_ScreenID, iSV, iError );
            if (iError >= 0)
            {
               // Set the NEW PrevScreenID[ ScreenIdx ] to the CURRENT ScreenID
               long lPrevScrnIDDBID = BEMPX_GetDBID( m_iBEMCID_Wizard, BEMPX_GetPropertyID( m_lDBID_PrevScreenID ), (lScrnIdx+1) );  // SAC 7/18/01
               iSetDataRetVal = BEMPX_SetBEMData( lPrevScrnIDDBID, BEMP_Int, (void*) &lScrnID );

               // Get the NextScreenID
		         long lNextScrnID = BEMPX_GetInteger( m_lDBID_NextScreenID, iSV, iError );
               if (iError >= 0 && lNextScrnID > 0)
               {
                  // Set the NEW ScreenID to the current NextScreenID
                  iSetDataRetVal = BEMPX_SetBEMData( m_lDBID_ScreenID, BEMP_Int, (void*) &lNextScrnID );

                  // Note: the NEW NextScreenID needs to be set by the Wizard Rulelist
               }
            }

            bScreenSwitched = TRUE;
         }
      }

      if (bScreenSwitched)
         // Reset entire dialog
         CreateUIControls( TRUE );
   }
}

BOOL CSACDlg::OKToExit()
{
   return TRUE;
}


// RW 9/24/02 - Changed to accept 2 parameters, the passed in Error message from the calling routine, and also the ability
//              to report back the CWnd of the control where the rulebased error has occurred (if no previously found error exists).
// RW 11/26/02 - Added reference parameters to determine if any errors or warnings were discovered via the rules based checking
BOOL CSACDlg::RuleBasedErrorCheck(CString& sErrMsg, CWnd* &pFocusCtrl, BOOL& bErrorsFound, BOOL& bWarningsFound)
{
   BOOL bRetVal = TRUE;

// SAC 5/22/01 - Added code to loop over all controls in screen and perform rule-based req'd property input and range checking
   if (m_iDialogMode == 999  &&  m_pTDPage)
   {
// RW 9/24/02 - Changed the initial value of bErrorsFound to be dependent on if there was an existing error as indicated in pFocusCtrl not being NULL
// RW 11/26/02 - Commented out the below variables as their values are now being passed in by reference
//      BOOL bErrorsFound = (pFocusCtrl != NULL);
//      BOOL bWarningsFound = FALSE;
// RW 9/24/02 value is now passed in
//      CWnd* pFocusCtrl = NULL;
      if (bRetVal)	// always true
      {
         CWaitCursor busyCursor;
         QStringList saErrors, saWarnings;
		 int i=m_pTDPage->m_iFirstCtrlIdx;
         for (; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if (pCtrl && !pCtrl->m_sErrorCheckRulelistName.IsEmpty())
            {
               CWnd* pWnd = GetDlgItem( pCtrl->m_uiCtrlID );
               if (pWnd && pWnd->IsWindowVisible())
               {
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
// RW 9/23/02 - getting the length of the array before the RuleProc eval call so we can get the starting index for this particular control
                  int iStartWarnIdx = saWarnings.size();
                  int iStartErrorIdx = saErrors.size();

                  VERIFY( BEMPX_EvalErrorCheckList( pCtrl->m_sErrorCheckRulelistName, saErrors, saWarnings, iEvalOnlyClass, iEvalOnlyOccur ) );

                  if (!bErrorsFound  &&  saErrors.size() > 0)
                  {
                     bErrorsFound = TRUE;
                     pFocusCtrl = pWnd;
                  }
                  else if (pFocusCtrl == NULL  &&  saWarnings.size() > 0)
                     pFocusCtrl = pWnd;

                  for( int iErr = iStartErrorIdx; iErr < saErrors.size(); iErr++ )
                     AddWarningObject( pCtrl->m_lDBID, saErrors[iErr].toLatin1().constData(), RANGE_ERROR);

                  for( int iWarn = iStartWarnIdx; iWarn < saWarnings.size(); iWarn++ )
                     AddWarningObject( pCtrl->m_lDBID, saWarnings[iWarn].toLatin1().constData(), RANGE_WARNING);
               }
            }
         }
         bWarningsFound = (saWarnings.size() > 0);

         for (i=0; i<saErrors.size(); i++)
         {
            if (sErrMsg.GetLength() > 0)
               sErrMsg += "\r\n\r\n";
            sErrMsg += "ERROR:  ";
            sErrMsg += saErrors[i].toLatin1().constData();
         }
         for (i=0; i<saWarnings.size(); i++)
         {
            if (i > 0  ||  !sErrMsg.IsEmpty())
               sErrMsg += "\r\n\r\n";
            sErrMsg += "Warning:  ";
            sErrMsg += saWarnings[i].toLatin1().constData();
         }
      }
   }

   return bRetVal;
}


void CSACDlg::OnFinishWizard() 
{
// RW 9/24/02 - Put the RuleBaseErrorCheck inside EditControlValueInRange() routine
   if (EditControlValuesInRange( 2 ) && OKToExit())
//   if (EditControlValuesInRange( 2 ) && RuleBasedErrorCheck() && OKToExit())
   {
      EvaluateRules( 1 );
      CDialog::OnOK();	
   }
}

void CSACDlg::OnCancelWizard() 
{
   if (!m_bBypassChecksOnCancel)
   {
      if ( !EditControlValuesInRange( 3 ) )
         return;

// RW 9/24/02 - Put the RuleBaseErrorCheck inside EditControlValueInRange() routine
//      if (!RuleBasedErrorCheck())
//         return;
      
      if ( !OKToExit() &&
           MessageBox( "Do you wish to leave this dialog without fixing the error(s)?",
                       "Cancel Error", MB_ICONQUESTION | MB_YESNO ) != IDYES )
         return;
   }
      
   EvaluateRules( 1 );
   CDialog::OnCancel();
}



// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
LRESULT CSACDlg::OnSetContextHelpID( WPARAM wHelpID, LPARAM )
{
   m_lContextHelpID = wHelpID;
   return 1;
}

// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
LRESULT CSACDlg::OnCommandHelp( WPARAM, LPARAM /*lParam*/ )
{
   if (m_lContextHelpID > 0)
   {
      // SAC 2/7/00 - added if statement to enable parent window to handle help system calls (HTML help)
      if (m_bPostHelpMessageToParent)
      {
         CWnd* pParent = GetParent();
         CFrameWnd* pFrame = GetParentFrame();
         // SAC 9/6/00 - Added trailing ", 1" argument to PostMessage calls in order to cause resulting help to be presented in a secondary window
         if (pFrame  &&  pParent  &&  ( pParent->IsKindOf(RUNTIME_CLASS( CSACDlg       )) ))
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


#ifdef _INC_SPREAD
// SAC 6/7/00 - Spreadsheet control tooltip message processing
LRESULT CSACDlg::OnSpreadTextTipFetch(WPARAM wParam, LPARAM lParam)
{
   CWnd* pSpread = GetDlgItem( wParam );
   if (pSpread && lParam && pSpread->IsKindOf(RUNTIME_CLASS( CBEMProcCtrlSpread )))
      ((CBEMProcCtrlSpread*)pSpread)->OnTextTipFetch( (LPSS_TEXTTIPFETCH) lParam );

   return 1;
}

// SAC 6/7/00 - Spreadsheet control tooltip message processing
LONG CSACDlg::OnQMDeleteRow(UINT uiCtrlID, LONG lDBID)
{
   CWnd* pSpread = GetDlgItem( (int)uiCtrlID );
   if (pSpread && lDBID && pSpread->IsKindOf(RUNTIME_CLASS( CBEMProcCtrlSpread )))
      ((CBEMProcCtrlSpread*)pSpread)->DeleteRow( lDBID );

   return 1;
}

#endif

BOOL CSACDlg::CheckData( CString& sMsg, CArray<long,long>* plErrDBIDs, CArray<long,long>* plWarnDBIDs )
{
   BOOL bRetVal = TRUE;
   long iScrnID = GetCurrentScreenID( TRUE );
   if (iScrnID > 0)
   {
      m_iCurrentScreenID = iScrnID;
      m_pTDPage = eScreenData.GetPageByID( m_iCurrentScreenID );
      if (m_pTDPage)
      {
         m_lCtrlDBIDOffset = 0;
         if (m_lDBID_CtrlDBIDOffset > 0)
         {
            if (!BEMPX_SetDataInteger( m_lDBID_CtrlDBIDOffset, m_lCtrlDBIDOffset ))
               MessageBox( "CSACDlg Error:  CtrlDBIDOffset retrieval failed." );

            // SAC 3/2/99 - added call to setup DBID offsets for all UI ctrl condition DBIDs corresponding
            //              to the same class as the main dlg page's class
            eScreenData.SetupControlConditionDBIDOffsets( m_pTDPage, m_lCtrlDBIDOffset );
         }

         int iNumViolations = 0;
// RW 9/24/02 - Added below routine to reset the current flag of existing Warning objects that are children to this dialogs parent object
         ResetWarningCurrentFlag();
         BOOL bOrigMsgEmpty = sMsg.IsEmpty();  // SAC 8/20/02 - Added BOOL to enable insertion of newline when previous error message exists already
         for (int i=m_pTDPage->m_iFirstCtrlIdx; i<=m_pTDPage->m_iLastCtrlIdx; i++)
         {
            CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
            if ( pCtrl  &&  BEMPX_GetCompDisplay( pCtrl->m_lDBID + m_lCtrlDBIDOffset, 0 )  &&  pCtrl->CanDisplay() )  // SAC 8/20/02 - Added CanDisplay() call
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
                           if (iNumViolations > 0 || !bOrigMsgEmpty)  // SAC 8/20/02
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
                     if (iErr > 0 || iNumViolations > 0 || !bOrigMsgEmpty)  // SAC 8/20/02
                        sCumErr += "\r\n\r\n";
                     sCumErr += "ERROR:  ";
                     sCumErr += saErrors[iErr].toLatin1().constData();
                     bRetVal = FALSE;
                  }
                  for (int iWarn=0; iWarn<saWarnings.size(); iWarn++)
                  {
                     if( !bCtrlWarnAdded )
                     {
                         bCtrlWarnAdded = TRUE;
                         plWarnDBIDs->Add(pCtrl->m_lDBID);
                     }
                     if (iWarn > 0  ||  !sCumErr.IsEmpty() || iNumViolations > 0 || !bOrigMsgEmpty)  // SAC 8/20/02
                        sCumErr += "\r\n\r\n";
                     sCumErr += "Warning:  ";
                     sCumErr += saWarnings[iWarn].toLatin1().constData();
                     bRetVal = FALSE;
                  }
                  sMsg += sCumErr;
               }
            }
         }
// RW 9/24/02 - Added below routine to remove any of Warning child objects that are no longer current
         RemoveNonCurrentWarnings();
      }
   }

   return bRetVal;
}


void CSACDlg::ResetWarningCurrentFlag()
{
   int iWarnCompID = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnCurrent  = BEMPX_GetDatabaseID("WarnCurrent",   iWarnCompID );
   long lCurrent = 0;

   int iNumChildren = (int) BEMPX_GetNumChildren( m_iBEMCID_Wizard, -1, BEMO_User, iWarnCompID);
   for (int i1Child=1; i1Child<=iNumChildren; i1Child++)
   {
      int iError;
      BEM_ObjType eChildObjType;
      int i0ChildIdx = BEMPX_GetChildObjectIndex( m_iBEMCID_Wizard, iWarnCompID, iError, eChildObjType, i1Child );
      if (i0ChildIdx >= 0)
      {
         void* pData = NULL;
         pData = &lCurrent;
         int iDataToSetType = BEMP_Int;
         int iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnCurrent, iDataToSetType, pData, BEMO_User, i0ChildIdx );		iSetDataRetVal;
      }
   }
}

void CSACDlg::RemoveNonCurrentWarnings()
{
   int iWarnCompID = BEMPX_GetDBComponentID( "Warn" );
   long lDBIDWarnCurrent  = BEMPX_GetDatabaseID("WarnCurrent",   iWarnCompID );
   //long lCurrent = 0;

// RW 12/17/02 - Fix where the number of children is changed after a warning objec tis deleted, and the current list of children is too many
   BOOL bDeletedObject = TRUE;
   while ( bDeletedObject )
   {
      bDeletedObject = FALSE;

      int iNumChildren = (int) BEMPX_GetNumChildren( m_iBEMCID_Wizard, -1, BEMO_User, iWarnCompID);
// RW 12/17/02 - go through this loop until we hit an object to delete, then break out of the loop and recompute the number of children and 
//             - their corresponding indicies.
      for (int i1Child=1; !bDeletedObject && i1Child<=iNumChildren; i1Child++)
      {
         int iError;
         BEM_ObjType eChildObjType;
         int i0ChildIdx = BEMPX_GetChildObjectIndex( m_iBEMCID_Wizard, iWarnCompID, iError, eChildObjType, i1Child );
         if (i0ChildIdx >= 0)
         {
            long lCurrent;
            BEMPX_SetDataInteger( lDBIDWarnCurrent,    lCurrent,    0, BEMP_Int, i0ChildIdx );
            BEMObject* pOldWarning = NULL;
            if( lCurrent < 1 && ((pOldWarning = BEMPX_GetObjectByClass(iWarnCompID, iError, i0ChildIdx)) != NULL) )
            {
               BEMPX_DeleteObject(pOldWarning);
               bDeletedObject = TRUE;
            }
         }
      }
   }
}

// as seperate object with the currently active m_iBEMCID_Wizard class object
void CSACDlg::AddWarningObject( long /*lCtrlDBID*/, CString /*sMsg*/, long /*lRangeVal*/ )
{
   return;

// not currently implemented
//   void* pData = NULL;
//   long lCurrent = 1;
//   int iError;
//   CString sWarnName;
//   // Create a Warnings object and make it a child of the currently active m_iBEMCID_Wizard class object
//   BEMObject* pParent = BEMPX_GetObjectByClass( m_iBEMCID_Wizard , iError );
//   int iDataToSetType;
//   int iSetDataRetVal;
//   int iWarnCompID = BEMPX_GetDBComponentID( "Warn" );
//   long lDBIDWarnType      = BEMPX_GetDatabaseID("WarnType",     iWarnCompID );
//   long lDBIDWarnCurrent   = BEMPX_GetDatabaseID("WarnCurrent",  iWarnCompID );
//   long lDBIDWarnMsg       = BEMPX_GetDatabaseID("WarnMsg",      iWarnCompID );
//   long lDBIDWarnDBID      = BEMPX_GetDatabaseID("WarnDBID",     iWarnCompID );
//   ASSERT( pParent != NULL && iWarnCompID > 0 && lDBIDWarnDBID > 0 && lDBIDWarnMsg > 0);
//
//   // Since we may be going through this multiple times we need to go through any existing children of this 
//   // currently active m_iBEMCID_Wizard class object and run a string comparison to look for the same message.
//   // This is making the assumption that a specific m_iBEMCID_Wizard class object cannot have two warnings that 
//   // are exactly the same.  If this is not the case then we need to come up with some different strategy for
//   // determining whether or not a warning has been previously encountered and stored to BEMProc.
//   BOOL bNotFound = TRUE;
//   int iNumChildren = (int) BEMPX_GetNumChildren( m_iBEMCID_Wizard, -1, BEMO_User, iWarnCompID);
//   for (int i1Child=1; bNotFound && i1Child<=iNumChildren; i1Child++)
//   {
//      int iError;
//      BEM_ObjType eChildObjType;
//      int i0ChildIdx = BEMPX_GetChildObjectIndex( m_iBEMCID_Wizard, iWarnCompID, iError, eChildObjType, i1Child );
//      if (i0ChildIdx >= 0)
//      {
//         CString sWarnMsg;
//         BEMPX_SetDataString( lDBIDWarnMsg,       sWarnMsg,       FALSE, 0, BEMP_Str, i0ChildIdx );
//         if( !sMsg.CompareNoCase(sWarnMsg) )
//         {
//            pData = &lCurrent;
//            iDataToSetType = BEMP_Int;
//            iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnCurrent, iDataToSetType, pData, BEMO_User, i0ChildIdx );
//            bNotFound = FALSE;
//         }
//      }
//   }
//
//   if (bNotFound )
//   {
//      int iWarnIdx = BEMPX_GetNumObjects( iWarnCompID );
//      do
//      {
//         sWarnName.Format( "Warning %d", ++iWarnIdx );
//      } while (BEMPX_GetComponentByName( sWarnName ) != NULL);
//
//      if( BEMPX_CreateObject( iWarnCompID, sWarnName, pParent, BEMO_User, TRUE, TRUE, 0, FALSE, 0 ) == NULL)  // SAC 5/29/14 - replaced final BOOL bMakeFirstChild argument w/ int i0ChildIdx
//         MessageBox( "BEMProcUI CSACDlg::AddWarningObject() Error:  Unable to create warning component." );
//      else
//      {
//         pData = (void*) ((const char*) sMsg);
//         iDataToSetType = BEMP_Str;
//         iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnMsg, iDataToSetType, pData );
//
//         pData = &lCtrlDBID;
//         iDataToSetType = BEMP_Int;
//         iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnDBID, iDataToSetType, pData );
//
//         pData = &lCurrent;
//         iDataToSetType = BEMP_Int;
//         iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnCurrent, iDataToSetType, pData );
//
//         pData = &lRangeVal;
//         iDataToSetType = BEMP_Sym;
//         iSetDataRetVal = BEMPX_SetBEMData( lDBIDWarnType, iDataToSetType, pData );
//      }
//   }
}
