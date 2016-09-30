// DlgRename.cpp : implementation file
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
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "DlgRename.h"

#include "CUIGlobl.h"
#include "MainFrm.h"
#include "ComplianceUIDoc.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define  IDD_REN_DLG   1025
#define  IDC_REN_NAME  1026

// misc. dialog and control dimensions & locations
#define  RENDLG_WD  375
#define  RENDLG_HT  130

#define  NAMEEDIT_L  205
#define  NAMEEDIT_T   15
#define  NAMEEDIT_R  350
#define  NAMEEDIT_B   40

// static location & dimension variables
static int siDlgWidth  = 0;
static int siDlgHeight = 0;

// Object type strings
static char BASED_CODE szDoneMsg[] = "Press Done when you are finished renaming this building component.";
static char BASED_CODE szNamMsg[]  = "Enter the new name for the building component.";


/////////////////////////////////////////////////////////////////////////////
// CDlgRename dialog


CDlgRename::CDlgRename( int i1Class, int i0Occur, BEM_ObjType eObjType, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRename::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRename)

   m_i1Class  = i1Class;
   m_i0Occur  = i0Occur;
   m_eObjType = eObjType;

   m_bCreateControls = TRUE;

   m_pName   = NULL;
   m_pDone   = NULL;

		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRename)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRename, CDialog)
	//{{AFX_MSG_MAP(CDlgRename)
	ON_WM_PAINT()
   ON_BN_CLICKED( IDOK, OnOK )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRename message handlers

BOOL CDlgRename::OnInitDialog() 
{
   if (m_bCreateControls)
   {
      siDlgWidth  = FontX( RENDLG_WD );
      siDlgHeight = FontY( RENDLG_HT );
      MoveWindow( (appCXFullScreen/2) - (siDlgWidth/2), (appCYFullScreen/2) + FontY(20) - (siDlgHeight/2), siDlgWidth, siDlgHeight, FALSE );

      // get object
      int iError;
   	BEMObject* pObj = BEMPX_GetObjectByClass( m_i1Class, iError, m_i0Occur, m_eObjType );

      // Set dialog caption
      CString sCaption = "Rename ";
      m_sLabel = "New ";
      if ( (iError >= 0) && (pObj != NULL) )
      {
         if (pObj->getClass() != NULL)
         {
            sCaption += pObj->getClass()->getLongName().toLatin1().constData();
            m_sLabel += pObj->getClass()->getLongName().toLatin1().constData();
         }
         else
         {
            sCaption += "Component";
            m_sLabel += "Component";
         }
         m_sLabel += " Name:";

         m_sOrigName = pObj->getName().toLatin1().constData() ;
         sCaption += ": '";
         sCaption += pObj->getName().toLatin1().constData() ;
         sCaption += "'";
      }
      SetWindowText( sCaption );

      // Name edit control
      int iLen = 60;  // SAC 8/7/00 - eased name length restriction, was: = (m_i1Class != 1) ? 15 : 60;
      m_pName = new CEditCtl();
      m_pName->Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL,
//                     CRect( FontX( 155 ), FontY( 15 ), FontX( 300 ), FontY( 40 ) ), this,
                     CRect( FontX( NAMEEDIT_L ), FontY( NAMEEDIT_T ), FontX( NAMEEDIT_R ), FontY( NAMEEDIT_B ) ), this,
                     IDC_REN_NAME, FNT_STD, iLen, szNamMsg, 0, BEMP_Str, IDC_REN_NAME, IDD_REN_DLG, FALSE );
// SAC 8/7/00 - Manually set the m_bNameDBID flag to ensure double quotes NOT entered into component name string
      if (m_pName)
         m_pName->m_bNameDBID = TRUE;
      // Construct and paste default component name
      if ( (m_pName != NULL) && (iError >= 0) && (pObj != NULL) )
         m_pName->SetWindowText( m_sOrigName );

      // OK and Cancel buttons
      m_pDone = new CButtonCtl();
      m_pDone->Create( "Done", BS_DEFPUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                         CRect( RENDLG_WD-100, RENDLG_HT-61, RENDLG_WD- 20, RENDLG_HT-38 ),
                         this, IDOK, TDCT_Button, FNT_STD, szDoneMsg, 0, TRUE, TRUE, FALSE, 0 );

      m_bCreateControls = FALSE;
   }

	return CDialog::OnInitDialog();  // return TRUE unless you set the focus to a control
	                                 // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRename::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   CDC* pDC = &dc;

   pDC->SetBkMode( TRANSPARENT );
   pDC->SetTextAlign( TA_RIGHT | TA_TOP );
   pDC->SelectObject( GetCUIFont(FNT_STD) );

   if (m_pName != NULL)
   {
//      CRect editRect;
//      m_pName->GetWindowRect( editRect );
//      ScreenToClient( editRect );
//      pDC->TextOut( FontX((NAMEEDIT_L-5)), FontY((NAMEEDIT_T+4)), szName );
      pDC->TextOut( FontX((NAMEEDIT_L-5)), FontY((NAMEEDIT_T+4)), m_sLabel );
   }
}


static char BASED_CODE szErrNoName[]  = "You must enter a name in the name field before selecting Done.";
static char BASED_CODE szErrNotUnq[]  = "This name is already in use, enter a unique name for the component being created.";
static char BASED_CODE szErrGetObj[]  = "Error retrieving object.  Aborting rename procedure.";
static char BASED_CODE szErrCr8ing[]  = "An error occurred while attempting to create the building component copy.";
static char BASED_CODE szErrCoping[]  = "An error occurred while attempting to copy data into the new building component.";

void CDlgRename::OnOK()
{
   BOOL bOK = TRUE;

   if (m_pName == NULL)
      CDialog::OnCancel();
   else
   {
      BOOL bCancel = FALSE;

      // new object name checking
      CString sName;
      m_pName->GetWindowText( sName );

      int iError;
      BEMObject* pObj = BEMPX_GetObjectByClass( m_i1Class, iError, m_i0Occur, m_eObjType );

      if (m_pName->GetWindowTextLength() == 0)
      {
         MessageBox( szErrNoName );
         m_pName->SetFocus();
         bOK = FALSE;
      }
      else if ( (sName != m_sOrigName) && (BEMPX_GetComponentByName( sName ) != NULL) )
      {
         MessageBox( szErrNotUnq );
         m_pName->SetFocus();
         bOK = FALSE;
      }
      else if ( (iError < 0) || (pObj == NULL) )
      {
         MessageBox( szErrGetObj );
         bOK = FALSE;
         bCancel = TRUE;
      }

      if (bOK)
      {
         if (m_eObjType == BEMO_User)
         {  // simply rename object and we're done
            pObj->setName( QString(sName) );
         }
         else
         {  // must create new comp and copy pObj into it
            BEMObject* pNewObj = BEMPX_CreateObject( m_i1Class, sName, pObj->getParent(), BEMO_User, FALSE );
            if (pNewObj == NULL)
            {
               MessageBox( szErrCr8ing );
               bOK = FALSE;
            }
            else
            {
               if (BEMPX_CopyComponent( pNewObj, pObj, -1, true /*bCopyPrimaryDefaultDataAsUserDefined*/ ))		// SAC 6/8/15 - CBECC issue 1061
               {  // execute compliance rulelist #1
                  GetParentFrame()->SendMessage( WM_EVALPROPOSED );
               }
               else
               {
                  MessageBox( szErrCoping );
                  bOK = FALSE;

                  // DELETE object if it has already been created
                  if (pNewObj != NULL)
                     BEMPX_DeleteObject( pNewObj );
               }
            }
         }
      }

      // finish up
      if (bOK)
      {
         SetDataModifiedFlag( TRUE );

         // send a message to the main view's tree control via CMainFrame in case the tree requires updating
         long lDBID = BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_NAME );
         GetParentFrame()->SendMessage( WM_UPDATETREE, 0, lDBID );

         // Update frame title if project component just created
         if (m_i1Class == 1)
         {
            CWnd* pMainWnd = GetParentFrame();
            if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
               ((CMainFrame*)pMainWnd)->OnUpdateFrameTitle(TRUE);
         }

         CDialog::OnOK();
      }
      else if (bCancel)
         CDialog::OnCancel();
   }
}
