// DlgCreate.cpp : implementation file
//
/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2017, Wrightsoft Corporation
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
#include "DlgCreate.h"

#include "CUIGlobl.h"
#include "MainFrm.h"
#include "ComplianceUIDoc.h"
#include "DlgPrimData.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// misc. dialog and control dimensions & locations
#define  CR8DLG_WD  660		// SAC 12/23/18 - increased 525->575 // SAC 1/5/19 - 575->600 // SAC 1/24/19 - 600->660
#define  CR8DLG_HT  215		// SAC 12/9/14 - increased 210->215

#define  CR8DLG_OPTN_L   390
#define  CR8DLG_OPTN_R   635
#define  CR8DLG_OPTN_T    15

#define  CR8DLG_NAME_L   390
#define  CR8DLG_NAME_T    45
#define  CR8DLG_NAME_R   635
//#define  CR8DLG_NAME_B    40

#define  CR8DLG_NEXT_Y    75
#define  CR8DLG_NEXT_DY   30

#define  CR8DLG_COMBO_L  390
#define  CR8DLG_COMBO_R  635

// item/topic and ctrl IDs
#define  IDD_CR8_DLG     1006
#define  IDC_CR8_NAME    1007
#define  IDC_CR8_PARENT  1008
#define  IDC_CR8_COPY    1009
#define  IDC_CR8_OPTION  1010
#define  IDC_CR8_USERLIB 1011
#define  IDC_CR8_RULELIB 1012

// static location & dimension variables
static int siDlgWidth  = 0;
static int siDlgHeight = 0;

// Object type strings
static char BASED_CODE szCaption[] = "Create ";
static char BASED_CODE szCr8Opt[]  = " Creation Option:";
static char BASED_CODE szName[]    = " Name:";
static char BASED_CODE szParent[]  = "Parent Component:";
static char BASED_CODE szCopy[]    = "Copy Data From:";
static char BASED_CODE szUserLib[] = "Library Object to Import:";
static char BASED_CODE szRuleLib[] = "Library Object to Import:";

static char BASED_CODE szOKMsg[]   = "Press OK to create building component.";
static char BASED_CODE szCanMsg[]  = "Press Cancel to return without creating component.";
static char BASED_CODE szOptMsg[]  = "Choose how you wish to go about creating the object.";
static char BASED_CODE szNamMsg[]  = "Enter the name of the building component to create.";
static char BASED_CODE szParMsg[]  = "Select parent building component.";
static char BASED_CODE szCopMsg[]  = "Select an object to copy data from (if desired).";
static char BASED_CODE szULibMsg[] = "Select the user library object to import.";
static char BASED_CODE szRLibMsg[] = "Select the rule library object to import.";


/////////////////////////////////////////////////////////////////////////////
// CDlgCreate dialog


CDlgCreate::CDlgCreate( int i1Class, long lObjTypeDBID, long lObjTypeValue, CWnd* pParent /*=NULL*/, int iDefaultCr8Option /*=Cr8DlgOpt_New*/,
								BEMObject* pParentBEMObject /*=NULL*/ )
	: CDialog(CDlgCreate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreate)

	m_iCr8Option = iDefaultCr8Option;
   m_i1Class       = i1Class;
   m_lObjTypeDBID  = lObjTypeDBID;
   m_lObjTypeValue = lObjTypeValue;

	m_pParentBEMObject = pParentBEMObject;	// SAC 5/29/14

   m_bCreateControls = TRUE;

   m_pOption = NULL;	// SAC 9/18/13
   m_pName   = NULL;
   m_pParent = NULL;
   m_pCopy   = NULL;
   m_pUserLib = NULL;	// SAC 9/18/13
   m_pRuleLib = NULL;	// SAC 9/18/13
   m_pOK     = NULL;
   m_pCancel = NULL;

		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreate)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreate, CDialog)
	//{{AFX_MSG_MAP(CDlgCreate)
	ON_WM_PAINT()
   ON_BN_CLICKED( IDOK, OnOK )
   ON_MESSAGE(WM_DISPLAYMODS, DisplayMods)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreate message handlers

BOOL CDlgCreate::OnInitDialog() 
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

		// Create Option combobox
      m_pOption = new CComboBoxCtl();
      m_pOption->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                       CRect( CR8DLG_OPTN_L, CR8DLG_OPTN_T, CR8DLG_OPTN_R, CR8DLG_OPTN_T+220 ), this, IDC_CR8_OPTION, FNT_STD, FontY( 25 ),
                       szOptMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_CR8OPT ), -1,
                       TRUE, FALSE, IDC_CR8_OPTION, IDD_CR8_DLG );
      m_pOption->OnDisplayData(0,0);
		switch (m_iCr8Option)
		{	case Cr8DlgOpt_New		:		m_pOption->SetCurSel( 0 );
													break;
			case Cr8DlgOpt_UserLib	:	if (m_pOption->GetCount() > 1 && m_pOption->GetItemData(1) == Cr8DlgOpt_UserLib)
													m_pOption->SetCurSel( 1 );
												else
												{	m_pOption->SetCurSel( 0 );
													m_iCr8Option = Cr8DlgOpt_New;
												}	break;
			case Cr8DlgOpt_RuleLib	:	if (m_pOption->GetCount() > 1 && m_pOption->GetItemData(1) == Cr8DlgOpt_RuleLib)
													m_pOption->SetCurSel( 1 );
												else if (m_pOption->GetCount() > 2 && m_pOption->GetItemData(2) == Cr8DlgOpt_RuleLib)
													m_pOption->SetCurSel( 2 );
												else
												{	m_pOption->SetCurSel( 0 );
													m_iCr8Option = Cr8DlgOpt_New;
												}	break;
		}

      // Name edit control
      int iLen = 60;  // SAC 3/24/99 - eased name length restriction, was: = (m_i1Class != 1) ? 15 : 60;
      m_pName = new CEditCtl();
      m_pName->Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL,
                     CRect( FontX( CR8DLG_NAME_L ), FontY( CR8DLG_NAME_T ), FontX( CR8DLG_NAME_R ), FontY( (CR8DLG_NAME_T+25) ) ),
                     this, IDC_CR8_NAME, FNT_STD, iLen, szNamMsg, 0, BEMP_Str, IDC_CR8_NAME, IDD_CR8_DLG, FALSE );
      // Construct and paste default component name
      if (m_pName != NULL)
      {
// SAC 8/7/00 - Manually set the m_bNameDBID flag to ensure double quotes NOT entered into component name string
         m_pName->m_bNameDBID = TRUE;

         CString sDefName;
         if (m_i1Class != eiBDBCID_Proj)
         {	QString qsDN;
         	BEMPX_GetDefaultComponentName( m_i1Class, qsDN );
            sDefName = qsDN.toLatin1().constData();
         }
//         {
//            sDefName.Format( " %d", BEMPX_GetFirstUniqueNameIndex( m_i1Class ) );
//            sDefName = m_sDefaultNameHdr + sDefName;
//         }
         else
            DefaultProjectName( sDefName );
         m_pName->SetWindowText( sDefName );
      }
      int iNextT = CR8DLG_NEXT_Y;

      // Parent Object ComboBox
      if (pClass != NULL && pClass->getParentType(0) >= 0 && m_pParentBEMObject == NULL)
      {
         m_pParent = new CComboBoxCtl();
         m_pParent->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+220 ), this, IDC_CR8_PARENT, FNT_STD, FontY( 25 ),
                          szParMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_NEWPAR ), -1,
                          TRUE, FALSE, IDC_CR8_PARENT, IDD_CR8_DLG );
         m_pParent->OnDisplayData(0,0);
         iNextT += CR8DLG_NEXT_DY;
      }

      // Object to copy data from ComboBox
      //if (BEMPX_GetNumObjects( m_i1Class, BEMO_User ) > 0)		// was: BEMO_NumTypes ) > 0)
      if (CompatibleObjectExists( BEMO_User ))		// SAC 9/19/13
      {
         m_pCopy = new CComboBoxCtl();
         m_pCopy->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+220 ), this, IDC_CR8_COPY, FNT_STD, FontY( 25 ),
                          szCopMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_NEWCOPY ), -1,
                          TRUE, FALSE, IDC_CR8_COPY, IDD_CR8_DLG, m_lObjTypeDBID, m_lObjTypeValue );
         m_pCopy->OnDisplayData(0,0);
	      m_pCopy->SetCurSel( 0 );		// prevent default selection of ACTIVE object (instead, default to '- none -') - SAC 9/18/13
//         iNextT += CR8DLG_NEXT_DY;
      }
		if (CompatibleObjectExists( BEMO_UserLib ))
      {  m_pUserLib = new CComboBoxCtl();
         m_pUserLib->Create( WS_CHILD|/*WS_VISIBLE|*/WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+320 ), this, IDC_CR8_USERLIB, FNT_STD, FontY( 25 ),
                          szULibMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_USERLIB ), -1,
                          TRUE, FALSE, IDC_CR8_USERLIB, IDD_CR8_DLG, m_lObjTypeDBID, m_lObjTypeValue );
         m_pUserLib->OnDisplayData(0,0);
	      m_pUserLib->SetCurSel( 0 );
		}
		if (CompatibleObjectExists( BEMO_RuleLib ))
		{  m_pRuleLib = new CComboBoxCtl();
         m_pRuleLib->Create( WS_CHILD|/*WS_VISIBLE|*/WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                          CRect( CR8DLG_COMBO_L, iNextT, CR8DLG_COMBO_R, iNextT+320 ), this, IDC_CR8_RULELIB, FNT_STD, FontY( 25 ),
                          szRLibMsg, BEMPX_GetDBID( m_i1Class, 0, BEM_PARAM0_RULELIB ), -1,
                          TRUE, FALSE, IDC_CR8_RULELIB, IDD_CR8_DLG, m_lObjTypeDBID, m_lObjTypeValue );
         m_pRuleLib->OnDisplayData(0,0);
	      m_pRuleLib->SetCurSel( 0 );
		}

		// SAC 12/9/14 - added adjustments that are specific to individual computer resource size settings (iDlgWdAdj was a static value of 20 & iDlgHtAdj was 38)
		int iDlgWdAdj = 16 + InvFontX(  (GetSystemMetrics(SM_CXPADDEDBORDER) * 2) );
		int iDlgHtAdj = 16 + InvFontY( ((GetSystemMetrics(SM_CXPADDEDBORDER) * 2) + GetSystemMetrics(SM_CYCAPTION)) );

      // OK and Cancel buttons
      m_pOK = new CButtonCtl();
      m_pCancel = new CButtonCtl();
      m_pOK->Create( "OK", BS_DEFPUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                   //    CRect( CR8DLG_WD-190, CR8DLG_HT-61, CR8DLG_WD-110, CR8DLG_HT-38 ),
                         CRect(CR8DLG_WD - iDlgWdAdj - 170, CR8DLG_HT - iDlgHtAdj - 23, CR8DLG_WD - iDlgWdAdj - 90, CR8DLG_HT - iDlgHtAdj),
								 this, IDOK, TDCT_Button, FNT_STD, szOKMsg, 0, TRUE, TRUE, FALSE, 0);
      m_pCancel->Create( "Cancel", BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                   //    CRect( CR8DLG_WD-100, CR8DLG_HT-61, CR8DLG_WD- 20, CR8DLG_HT-38 ),
                         CRect(CR8DLG_WD - iDlgWdAdj - 80, CR8DLG_HT - iDlgHtAdj - 23, CR8DLG_WD - iDlgWdAdj, CR8DLG_HT - iDlgHtAdj),
								 this, IDCANCEL, TDCT_Button, FNT_STD, szCanMsg, 0, TRUE, TRUE, FALSE, 0);

      m_bCreateControls = FALSE;
   }

	return CDialog::OnInitDialog();  // return TRUE unless you set the focus to a control
                                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreate::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   CDC* pDC = &dc;

   pDC->SetBkMode( TRANSPARENT );
   pDC->SetTextAlign( TA_RIGHT | TA_TOP );
   pDC->SelectObject( GetCUIFont(FNT_STD) );

   if (m_pOption != NULL)
	{
      CString sLbl = m_sLongClassName;
      sLbl += szCr8Opt;
		pDC->TextOut( FontX((CR8DLG_OPTN_L-5)), FontY((CR8DLG_OPTN_T+4)), sLbl );
		m_iCr8Option = (int) m_pOption->GetItemData( m_pOption->GetCurSel() );
	}

   if (m_pName != NULL && m_pName->IsWindowVisible())
   {
      CString sLbl = m_sLongClassName;
      sLbl += szName;
      pDC->TextOut( FontX((CR8DLG_NAME_L-5)), FontY((CR8DLG_NAME_T+4)), sLbl );
   }

   if (m_pParent != NULL)
		pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), FontY((CR8DLG_NEXT_Y+4)), szParent );

   int iTop = FontY((CR8DLG_NEXT_Y+4));
   if (m_pParent != NULL)
      iTop += FontY(CR8DLG_NEXT_DY);
   if (m_pCopy != NULL && m_iCr8Option == Cr8DlgOpt_New)
   	pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), iTop, szCopy );
   else if (m_pUserLib != NULL && m_iCr8Option == Cr8DlgOpt_UserLib)
   	pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), iTop, szUserLib );
   else if (m_pRuleLib != NULL && m_iCr8Option == Cr8DlgOpt_RuleLib)
   	pDC->TextOut( FontX((CR8DLG_COMBO_L-5)), iTop, szRuleLib );
}

LRESULT CDlgCreate::DisplayMods( WPARAM, LPARAM )
{
   if (m_pOption != NULL)
	{	m_iCr8Option = (int) m_pOption->GetItemData( m_pOption->GetCurSel() );

	   if (m_pName != NULL)
		{	if (m_iCr8Option == Cr8DlgOpt_New && !m_pName->IsWindowVisible())
				m_pName->ShowWindow( SW_SHOW );
			else if (m_iCr8Option != Cr8DlgOpt_New && m_pName->IsWindowVisible())
				m_pName->ShowWindow( SW_HIDE );
		}

	   if (m_pCopy != NULL)
		{	if (m_iCr8Option == Cr8DlgOpt_New && !m_pCopy->IsWindowVisible())
				m_pCopy->ShowWindow( SW_SHOW );
			else if (m_iCr8Option != Cr8DlgOpt_New && m_pCopy->IsWindowVisible())
				m_pCopy->ShowWindow( SW_HIDE );
		}

	   if (m_pUserLib != NULL)
		{	if (m_iCr8Option == Cr8DlgOpt_UserLib && !m_pUserLib->IsWindowVisible())
				m_pUserLib->ShowWindow( SW_SHOW );
			else if (m_iCr8Option != Cr8DlgOpt_UserLib && m_pUserLib->IsWindowVisible())
				m_pUserLib->ShowWindow( SW_HIDE );
		}

	   if (m_pRuleLib != NULL)
		{	if (m_iCr8Option == Cr8DlgOpt_RuleLib && !m_pRuleLib->IsWindowVisible())
				m_pRuleLib->ShowWindow( SW_SHOW );
			else if (m_iCr8Option != Cr8DlgOpt_RuleLib && m_pRuleLib->IsWindowVisible())
				m_pRuleLib->ShowWindow( SW_HIDE );
		}
      RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
	}
//   CWnd *pChild = GetWindow( GW_CHILD );
//   while ( pChild != NULL )
//   {
//      pChild->SendMessage( WM_DISPLAYDATA );
//      pChild = pChild->GetNextWindow( GW_HWNDNEXT );
//   }
   return 1;
}


static char BASED_CODE szErrNoName[]  = "You must enter a name in the name field before selecting OK.";
static char BASED_CODE szErrNotUnq[]  = "This name is already in use, enter a unique name for the component being created.";
static char BASED_CODE szErrBadPar[]  = "Error retrieving parent component.  Choose another parent or '- none -'.";
static char BASED_CODE szErrBadCop[]  = "Error retrieving component to copy data from.  Choose another component or '- none -'.";
static char BASED_CODE szErrCr8ing[]  = "An error occurred while attempting to create the building component.";
static char BASED_CODE szErrCoping[]  = "An error occurred while attempting to copy data into the new building component.";
static char BASED_CODE szErrBadRLibObj[]  = "Error retrieving rule library object.  Choose another object to import.";
static char BASED_CODE szErrRLibImp[]  = "An error occurred while attempting to import the rule library object.";

void CDlgCreate::OnOK()
{
   BOOL bOK = TRUE;

   if (m_pName == NULL || m_pOption == NULL)
      CDialog::OnCancel();
   else
   {
      BOOL bDataCopied = FALSE;
      BEMObject* pNewObj = NULL;
      CString sName;
      int iError;

      BEMObject* pParObj = m_pParentBEMObject;		// SAC 5/29/14
      CString sParName;
		if (m_pParentBEMObject)
			sParName = m_pParentBEMObject->getName().toLatin1().constData();

		m_iCr8Option = (int) m_pOption->GetItemData( m_pOption->GetCurSel() );
		if (m_iCr8Option == Cr8DlgOpt_UserLib && m_pUserLib)
		{	ASSERT( FALSE );
         	      MessageBox( "Not yet implemented." );
		}
		else if (m_iCr8Option == Cr8DlgOpt_RuleLib && m_pRuleLib)
		{
			if (m_pParent)
         {	m_pParent->GetLBText( m_pParent->GetCurSel(), sParName );
         	if ( (sParName.GetLength() > 0) &&
         	     (sParName.Compare( "- none -" ) != 0) )
         	{
         	   pParObj = BEMPX_GetParentObjectByName( m_i1Class, iError, sParName );
         	   if ( (iError < 0) || (pParObj == NULL) )
         	   {
         	      MessageBox( szErrBadPar );
         	      m_pParent->SetFocus();
         	      bOK = FALSE;
      				pParObj = NULL;
						sParName.Empty();
         	   }
         	}
				else if (sParName.Compare( "- none -" ) == 0)
					sParName.Empty();
			}

			BEMObject* pLibObj = NULL;
			if (bOK)
			{
	         CString sLibObjName;
         	m_pRuleLib->GetLBText( m_pRuleLib->GetCurSel(), sLibObjName );
				if (sLibObjName.IsEmpty())
         	   bOK = FALSE;
				else
				{	pLibObj = BEMPX_GetObjectByName( m_i1Class, iError, sLibObjName, BEMO_RuleLib );
					bOK = (pLibObj != NULL);
				}

				if (!bOK)
         	{
         	   MessageBox( szErrBadRLibObj );
         	   m_pRuleLib->SetFocus();
         	}
				else
				{	BOOL bImportUniqueRuleLibObjects = FALSE;
 					if (!sParName.IsEmpty() && pLibObj->getClass() && pLibObj->getClass()->getParentType(0) > 0)  // getParentType(*) is 0-based
 						bImportUniqueRuleLibObjects = TRUE;
 			      pNewObj = BEMPX_ImportLibraryObjectToUserModel( pLibObj, bImportUniqueRuleLibObjects /*=FALSE*/,
 																					sParName /*pszImportRuleLibParentName=NULL*/ );  //, int iBEMProcIdx=-1 );
 					if (pNewObj == NULL)
 	            {	MessageBox( szErrRLibImp );
 	            	bOK = FALSE;
 					}
 					else
 					{	sName = pNewObj->getName().toLatin1().constData();
       				bDataCopied = TRUE;  // assumption is that librayr object includes all Compulsory data...
 					}
				}
			}
		}
		else
		{
	      // new object name checking
	      m_pName->GetWindowText( sName );
	
	      if (m_pName->GetWindowTextLength() == 0)
	      {
	         MessageBox( szErrNoName );
	         m_pName->SetFocus();
	         bOK = FALSE;
	      }
	      else if (m_i1Class != eiBDBCID_Proj && BEMPX_GetComponentByName( sName ) != NULL)
	      {
	         MessageBox( szErrNotUnq );
	         m_pName->SetFocus();
	         bOK = FALSE;
	      }
	
	      // parent object retrieval
	      //BEMObject* pParObj = NULL;
	      if ( bOK && (m_pParent != NULL) && (m_pParent->GetCurSel() >= 0) )
	      {
	         //CString sParName;
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
	            if (BEMPX_CopyComponent( pNewObj, pCopyObj, -1, true /*bCopyPrimaryDefaultDataAsUserDefined*/ ))		// SAC 6/8/15 - CBECC issue 1061
	               bDataCopied = TRUE;
	            else
	            {
	               MessageBox( szErrCoping );
	               bOK = FALSE;
	            }
	         }
	      }
	
	      if (m_lObjTypeDBID > 0)
	      {	// SAC 12/1/16 - PREVENT setting object type if the property is not classified as a user input
				int iPropDataType = BEMPX_GetCompDataType( m_lObjTypeDBID );
				if (iPropDataType < BEMD_Prescribed)
		         // INSTALL Object Type value (if necessary)
		         BEMPX_SetBEMData( m_lObjTypeDBID, BEMP_Int, (void*) &m_lObjTypeValue );
			}
		}

#ifdef UI_CANRES
// SAC 2/28/14 - for CANRES2013 - only allow creation of Proj objects w/ GeometryInpType = "Simplified"
		if (m_i1Class == eiBDBCID_Proj)
		{	VERIFY( BEMPX_SetBEMData( BEMPX_GetDatabaseID( "GeometryInpType", eiBDBCID_Proj ), BEMP_Str, (void*) "Simplified" ) >= 0 );
			AdjustDataModelForGeometryInpType();  // AFTER setting GeometryInpType, revise data model settings to ensure that UI prevents access to certain objects and collects properties required for simplified geom projects
		}
#endif

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
            CDlgPrimData primDlg( m_i1Class, iObjIdx, iNumPrimProps, (const char*) sName, this );
            bOK = (primDlg.DoModal() == IDOK);
         }
      }

	// SAC 5/16/18 - moved up into MainFrm to evaluate rules only once after both creation AND assigning of new object to another object/property
   //   if ( bOK && pNewObj )
   //   {  // execute compliance rulelist #1
   //      // must do this even if primary data entered because some of the 
   //      // primary data may have been user defaulted
	//		BEMPX_IncrementModsSinceModelDefaulted();		// SAC 4/12/18
   //      GetParentFrame()->SendMessage( WM_EVALPROPOSED, DefaultAction_InitAnalysis, m_i1Class );		// SAC 5/16/18 - switched from DefaultAction_OpenDialog to DefaultAction_InitAnalysis to ensure evaluation
   //   }

      // finish up
      if (bOK)
      {
         SetDataModifiedFlag( TRUE );

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


BOOL CDlgCreate::CompatibleObjectExists( int iObjType )	// SAC 9/19/13
{	BOOL bRetVal = FALSE;
	int iNumObjs = BEMPX_GetNumObjects( m_i1Class, (BEM_ObjType) iObjType );
	if (iNumObjs > 0)
	{	if (m_lObjTypeDBID < 1)
			bRetVal = TRUE;
		else
		{	int iError, iSV;
			for (int iObjIdx=0; (!bRetVal && iObjIdx < iNumObjs); iObjIdx++)
			{	long lObjType = BEMPX_GetInteger( m_lObjTypeDBID, iSV, iError, iObjIdx, (BEM_ObjType) iObjType );
				if (iError >= 0 && lObjType == m_lObjTypeValue)
					bRetVal = TRUE;
			}
		}
	}
	return bRetVal;
}
