// BEMProcDlgCreate.cpp : implementation file
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
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "resource.h"
#include "BEMProcDlgCreate.h"
#include "BEMProcDlgPrimData.h"
#include "BEMProcUIX.h"
//#include "memLkRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// misc. dialog and control dimensions & locations
#define  CR8DLG_WD  425
#define  CR8DLG_HT  180

#define  CR8DLG_NAME_L   180
#define  CR8DLG_NAME_T    15
#define  CR8DLG_NAME_R   400
#define  CR8DLG_NAME_B    37  // 40

#define  CR8DLG_NEXT_Y    45
#define  CR8DLG_NEXT_DY   30

#define  CR8DLG_COMBO_L  180
#define  CR8DLG_COMBO_R  400

// item/topic and ctrl IDs
#define  IDD_CR8_DLG     1006
#define  IDC_CR8_NAME    1007
#define  IDC_CR8_PARENT  1008
#define  IDC_CR8_COPY    1009

// static location & dimension variables
static int siDlgWidth  = 0;
static int siDlgHeight = 0;

// Object type strings
static char BASED_CODE szCaption[] = "Create ";
static char BASED_CODE szName[]    = " Name:";
static char BASED_CODE szParent[]  = "Parent Component:";
static char BASED_CODE szCopy[]    = "Copy Data From:";

static char BASED_CODE szOKMsg[]   = "Press OK to create building component.";
static char BASED_CODE szCanMsg[]  = "Press Cancel to return without creating component.";
static char BASED_CODE szNamMsg[]  = "Enter the name of the building component to create.";
static char BASED_CODE szParMsg[]  = "Select parent building component.";
static char BASED_CODE szCopMsg[]  = "Select a component to copy data from if desired.";


/////////////////////////////////////////////////////////////////////////////
// CBEMProcDlgCreate dialog


CBEMProcDlgCreate::CBEMProcDlgCreate( int i1Class, long lObjTypeDBID, long lObjTypeValue, CWnd* pParent /*=NULL*/, int iDlgMode /*=0*/)
	: CDialog(CBEMProcDlgCreate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBEMProcDlgCreate)

   m_i1Class       = i1Class;
   m_lObjTypeDBID  = lObjTypeDBID;
   m_lObjTypeValue = lObjTypeValue;

   m_bCreateControls = TRUE;

   m_pName   = NULL;
   m_pParent = NULL;
   m_pCopy   = NULL;
   m_pOK     = NULL;
   m_pCancel = NULL;

   m_iDialogMode = iDlgMode;
   m_pNewObj = NULL;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBEMProcDlgCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBEMProcDlgCreate)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBEMProcDlgCreate, CDialog)
	//{{AFX_MSG_MAP(CBEMProcDlgCreate)
	ON_WM_PAINT()
   ON_BN_CLICKED( IDOK, OnOK )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBEMProcDlgCreate message handlers

BOOL CBEMProcDlgCreate::OnInitDialog() 
{
   if (m_bCreateControls)
   {
      // Size and center dialog
      siDlgWidth  = FontX( CR8DLG_WD );
      siDlgHeight = FontY( CR8DLG_HT );
      MoveWindow( (appCXFullScreen/2) - (siDlgWidth/2), (appCYFullScreen/2) + FontY(20) - (siDlgHeight/2),
                  siDlgWidth, siDlgHeight, FALSE );

      // Get long class name for later use in creating label for component name control
      int iError;
      BEMClass* pClass = BEMPX_GetClass( m_i1Class, iError );
      if ( (iError >= 0) && (pClass != NULL) )
         m_sLongClassName = pClass->getLongName().toLatin1().constData();
      else
         m_sLongClassName = "Component";

      // Set dialog caption
      CString sCaption = szCaption;
      sCaption += pClass->getLongName().toLatin1().constData();
      SetWindowText( sCaption );

      // Name edit control
      int iLen = 60;  // SAC 3/24/99 - eased name length restriction, was: = (m_i1Class != 1) ? 15 : 60;
      m_pName = new CEditCtl();
      m_pName->Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL,
                       CRect( FontX( CR8DLG_NAME_L ), FontY( CR8DLG_NAME_T ), FontX( CR8DLG_NAME_R ), FontY( CR8DLG_NAME_B ) ),
                       this, IDC_CR8_NAME, FNT_STD, iLen, szNamMsg, 0, BEMP_Str,
                       IDC_CR8_NAME, IDD_CR8_DLG, FALSE );
      // Construct and paste default component name
      if (m_pName != NULL)
      {
// SAC 8/7/00 - Manually set the m_bNoDoubleQuote flag to ensure double quotes NOT entered into component name string
         m_pName->m_bNoDoubleQuote = TRUE;

         QString sDefName;
// SAC 6/12/00 - assume this is not ever the Project component
//         if (m_i1Class != eiBEMCID_Proj)
            BEMPX_GetDefaultComponentName( m_i1Class, sDefName );
//         else
//            DefaultProjectName( sDefName );
         m_pName->SetWindowText( sDefName.toLatin1().constData() );
      }

      int iNextT = CR8DLG_NEXT_Y;

      // Parent Object ComboBox
      if ( (pClass != NULL) && (pClass->getParentType(0) >= 0) )
      {
         m_pParent = new CComboBoxCtl();
         m_pParent->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+220 ), this, IDC_CR8_PARENT,
                          FNT_STD, FontY( 25 ), szParMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_NEWPAR ),
                          -1, TRUE, FALSE, IDC_CR8_PARENT, IDD_CR8_DLG );
         m_pParent->OnDisplayData(0,0);
         iNextT += CR8DLG_NEXT_DY;
      }

      // Object to copy data from ComboBox
      if (BEMPX_GetNumObjects( m_i1Class, BEMO_NumTypes ) > 0)
      {
         m_pCopy = new CComboBoxCtl();
         m_pCopy->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+220 ), this, IDC_CR8_COPY,
                          FNT_STD, FontY( 25 ), szCopMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_NEWCOPY ),
                          -1, TRUE, FALSE, IDC_CR8_COPY, IDD_CR8_DLG, m_lObjTypeDBID, m_lObjTypeValue );
         m_pCopy->OnDisplayData(0,0);
         iNextT += CR8DLG_NEXT_DY;
      }

      // OK and Cancel buttons
      m_pOK = new CButtonCtl();
      m_pCancel = new CButtonCtl();

      m_pOK->Create( "OK", BS_DEFPUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                         CRect( CR8DLG_WD-190, CR8DLG_HT-61, CR8DLG_WD-110, CR8DLG_HT-38 ),
                         this, IDOK, TDCT_Button, FNT_STD,
                         szOKMsg, 0, TRUE, TRUE, FALSE, 0 );
      m_pCancel->Create( "Cancel", BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                         CRect( CR8DLG_WD-100, CR8DLG_HT-61, CR8DLG_WD- 20, CR8DLG_HT-38 ),
                         this, IDCANCEL, TDCT_Button, FNT_STD,
                         szCanMsg, 0, TRUE, TRUE, FALSE, 0 );

      m_bCreateControls = FALSE;
   }

	return CDialog::OnInitDialog();  // return TRUE unless you set the focus to a control
                                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CBEMProcDlgCreate::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   CDC* pDC = &dc;

   pDC->SetBkMode( TRANSPARENT );
   pDC->SetTextAlign( TA_RIGHT | TA_TOP );
   pDC->SelectObject( GetWizFont( FNT_STD ) );

   if (m_pName != NULL)
   {
      CString sLbl = m_sLongClassName;
      sLbl += szName;
      pDC->TextOut( FontX((CR8DLG_NAME_L-5)), FontY((CR8DLG_NAME_T+4)), sLbl );
   }

   if (m_pParent != NULL)
      pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), FontY((CR8DLG_NEXT_Y+4)), szParent );

   if (m_pCopy != NULL)
   {
      int iTop = FontY((CR8DLG_NEXT_Y+4));
      if (m_pParent != NULL)
         iTop += FontY(CR8DLG_NEXT_DY);
      pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), iTop, szCopy );
   }
}


static char BASED_CODE szErrNoName[]  = "You must enter a name in the name field before selecting OK.";
static char BASED_CODE szErrNotUnq[]  = "This name is already in use, enter a unique name for the component being created.";
static char BASED_CODE szErrBadPar[]  = "Error retrieving parent component.  Choose another parent or '- none -'.";
static char BASED_CODE szErrBadCop[]  = "Error retrieving component to copy data from.  Choose another component or '- none -'.";
static char BASED_CODE szErrCr8ing[]  = "An error occurred while attempting to create the building component.";
static char BASED_CODE szErrCoping[]  = "An error occurred while attempting to copy data into the new building component.";

void CBEMProcDlgCreate::OnOK()
{
   BOOL bOK = TRUE;

   if (m_pName == NULL)
      CDialog::OnCancel();
   else
   {
      // new object name checking
      CString sName;
      m_pName->GetWindowText( sName );

      if (m_pName->GetWindowTextLength() == 0)
      {
         MessageBox( szErrNoName );
         m_pName->SetFocus();
         bOK = FALSE;
      }
      else if (/*m_i1Class != eiBEMCID_Proj &&*/ BEMPX_GetComponentByName( sName ) != NULL)
      {
         MessageBox( szErrNotUnq );
         m_pName->SetFocus();
         bOK = FALSE;
      }

      int iError;
      // parent object retrieval
      BEMObject* pParObj = NULL;
      if ( bOK && (m_pParent != NULL) && (m_pParent->GetCurSel() >= 0) )
      {
         CString sParName;
         m_pParent->GetLBText( m_pParent->GetCurSel(), sParName );
         if ( (sParName.GetLength() > 0) &&
              (sParName.Compare( "- none -" ) != 0) )
         {
            pParObj = BEMPX_GetParentObjectByName( m_i1Class, iError, sParName );
            if ( (iError < 0) || (pParObj == NULL) )
            {
               MessageBox( szErrBadPar );
               m_pParent->SetFocus();
               bOK = FALSE;
            }
         }
      }

      // copy object retrieval
      BEMObject* pCopyObj = NULL;
      if ( bOK && (m_pCopy != NULL) && (m_pCopy->GetCurSel() >= 0) )
      {
         CString sCopyName;
         m_pCopy->GetLBText( m_pCopy->GetCurSel(), sCopyName );
         if ( (sCopyName.GetLength() > 0) &&
              (sCopyName.Compare( "- none -" ) != 0) )
         {
            CString sRightPortion = sCopyName.Right( 12 );
            if ( sCopyName.GetLength() > 12 &&
                 (sRightPortion == "  (rule lib)" || sRightPortion == "  (user lib)") )
               sCopyName = sCopyName.Left( sCopyName.GetLength()-12 );

//            pCopyObj = BEMPX_GetObjectByName( m_i1Class, iError, sCopyName );
            // get copy from object from ANY object list
            iError = -1;
            for (int i=0; (pCopyObj == NULL && i < BEMO_NumTypes); i++)
               pCopyObj = BEMPX_GetObjectByName( m_i1Class, iError, sCopyName, (BEM_ObjType) i );

            if (iError < 0 || pCopyObj == NULL)
            {
               MessageBox( szErrBadCop );
               m_pCopy->SetFocus();
               bOK = FALSE;
            }
         }
      }

      // create object (and copy data if that is selected)
      BOOL bDataCopied = FALSE;
      BEMObject* pNewObj = NULL;
      if (bOK)
      {
         pNewObj = BEMPX_CreateObject( m_i1Class, sName, pParObj, BEMO_User, FALSE );
         if (pNewObj == NULL)
         {
            MessageBox( szErrCr8ing );
            bOK = FALSE;
         }
         else if (pCopyObj != NULL)
         {
            if (BEMPX_CopyComponent( pNewObj, pCopyObj ))
               bDataCopied = TRUE;
            else
            {
               MessageBox( szErrCoping );
               bOK = FALSE;
            }
         }
      }

      if (m_lObjTypeDBID > 0)
         // INSTALL Object Type value (if necessary)
         BEMPX_SetBEMData( m_lObjTypeDBID, BEMP_Int, (void*) &m_lObjTypeValue );

      // Gather primary parameter data
      if ( bOK && !bDataCopied && pNewObj )
      {
         int iNumPrimProps = BEMPX_GetNumberOfPrimaryProperties( m_i1Class );

         if (m_lObjTypeDBID > 0 && iNumPrimProps == 1)
         {  // IF ONLY ONE PrimProp EXISTS, SEE IF IT IS THE ObjType ONE AND IF SO, DON'T DISPLAY DIALOG
            long lPropDBID = BEMPX_GetPrimaryPropertyDBID( m_i1Class, 0 );
            if (m_lObjTypeDBID == lPropDBID)
               iNumPrimProps = 0;  // reset iNumPrimProps to prevent display of primary data dialog
         }

         if (iNumPrimProps > 0)
         {
            int iError = 0;
            int iObjIdx = BEMPX_GetObjectIndex(  BEMPX_GetClass( m_i1Class, iError ), pNewObj );
         
            // Create new building component
            CBEMProcDlgPrimData primDlg( m_i1Class, iObjIdx, iNumPrimProps, (const char*) sName, this, m_iDialogMode );
            bOK = (primDlg.DoModal() == IDOK);
         }
      }

      if ( bOK && pNewObj )
      {  // execute compliance rulelist #1
         // must do this even if primary data entered because some of the 
         // primary data may have been user defaulted
// SAC 6/12/00 - handled later in WM_DATAMODIFIED message sent to parent
//         GetParentFrame()->SendMessage( WM_EVALPROPOSED );

         // SAC 6/12/00
         m_pNewObj = pNewObj;
      }

      // finish up
      if (bOK)
      {
//         SetDataModifiedFlag( TRUE );
// SAC 6/12/00 - replaced above w/ below
         // pass message on to parent dialog to cause rulelist evaluation and then to pass on to parent frame
         GetParent()->SendMessage( WM_DATAMODIFIED, 1 );

//         // Update frame title if project component just created
//         if (m_i1Class == 1)
//         {
//            CWnd* pMainWnd = GetParentFrame();
//            if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
//               ((CMainFrame*)pMainWnd)->OnUpdateFrameTitle(TRUE);
//         }

         CDialog::OnOK();
      }
      else if (pNewObj != NULL)
      {
         // DELETE object if it has already been created
         BEMPX_DeleteObject( pNewObj );
      }
   }
}
