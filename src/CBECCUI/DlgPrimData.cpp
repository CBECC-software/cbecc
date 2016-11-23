// DlgPrimData.cpp : implementation file
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
#include "..\BEMProc\BEMPropertyType.h"
#include "DlgPrimData.h"

#include "CUIGlobl.h"
#include "MainFrm.h"
#include "ComplianceUIDoc.h"
// #include "ToolTips.h"

#include "..\BEMProcUI\BEMProcUIX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// defines for control & help IDs
#define  IDC_PRIM_1   1010
#define  IDC_PRIM_2   1011
#define  IDC_PRIM_3   1012
#define  IDC_PRIM_4   1013
#define  IDC_PRIM_5   1014
#define  IDC_PRIM_6   1015
#define  IDC_PRIM_7   1016
#define  IDC_PRIM_8   1017
#define  IDC_PRIM_9   1018
#define  IDC_PRIM_10  1019
#define  IDC_PRIM_11  1020
#define  IDC_PRIM_12  1021
#define  IDC_PRIM_13  1022
#define  IDC_PRIM_14  1023
#define  IDC_PRIM_15  1024

// misc. dialog and control dimensions & locations
#define  PRIMDLG_WD  550		// SAC 11/21/16 - increased from 475 to accommodate units labels
#define  PRIMDLG_HT   90

#define  PRIMDLG_CTRL_L  255
#define  PRIMDLG_CTRL_R  450

// static location & dimension variables
static int siDlgWidth  = 0;
static int siDlgHeight = 0;

// Object type strings
static char BASED_CODE szCaption[] = "' Primary Data";

static char BASED_CODE szOKMsg[]   = "Press OK to create building component.";
static char BASED_CODE szCanMsg[]  = "Press Cancel to return without creating component.";
static char BASED_CODE szEdtMsg[]  = "Enter the desired value for this primary variable.";
static char BASED_CODE szCmbMsg[]  = "Select the desired value for this primary variable.";


/////////////////////////////////////////////////////////////////////////////
// CDlgPrimData dialog


CDlgPrimData::CDlgPrimData( int i1Class, int iObjIdx, int iNumPrimProps,
                            const char* psObjName, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrimData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPrimData)
   m_i1Class = i1Class;
   m_iObjIdx = iObjIdx;
   m_iNumPrimProps = iNumPrimProps;
   m_sObjName = psObjName;

   m_bCreateControls = TRUE;

   m_pOK     = NULL;
   m_pCancel = NULL;

		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

   for (int i=0; i<MAX_PRIMARY_VARIABLES; i++)
   {
      m_iaPropType[ i ] = -1;
      m_paCtrl[     i ] = NULL;
   }
}


void CDlgPrimData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrimData)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrimData, CDialog)
	//{{AFX_MSG_MAP(CDlgPrimData)
	ON_WM_PAINT()
   ON_MESSAGE(WM_DISPLAYMODS, DisplayMods)

   ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrimData message handlers

BOOL CDlgPrimData::OnInitDialog() 
{
	CDialog::OnInitDialog();

   if (m_bCreateControls)
   {
      // get long class name
      int iError;
      BEMClass* pClass = BEMPX_GetClass( m_i1Class, iError );
      if ( (iError >= 0) && (pClass != NULL) )
         m_sLongClassName = pClass->getLongName().toLatin1().constData();
      else
         m_sLongClassName = "Component";

//      int iDlgHt = PRIMDLG_HT + (m_iNumPrimProps * 30);
//      siDlgWidth  = FontX( PRIMDLG_WD );
//      siDlgHeight = FontY( iDlgHt );
		// Calc and set dialog dimensions  - SAC 11/21/16 - adjust more effectively to varying Windows versions
      int iDlgHt = PRIMDLG_HT + (m_iNumPrimProps * 30);
		int iPaddedBorderWd = GetSystemMetrics(SM_CXPADDEDBORDER);	// added to adjust for wider Win8 borders
	   siDlgWidth  = FontX( PRIMDLG_WD ) + (iPaddedBorderWd * 2);
	   siDlgHeight = FontY(   iDlgHt   ) + (iPaddedBorderWd * 2) + GetSystemMetrics(SM_CYCAPTION) - FontY( 30 );
      MoveWindow( (appCXFullScreen/2) - (siDlgWidth/2), (appCYFullScreen/2) + FontY(20) - (siDlgHeight/2),
                  siDlgWidth, siDlgHeight, FALSE );

      // Set dialog caption
      CString sCaption = "'";
      sCaption += m_sObjName;
      sCaption += szCaption;
      SetWindowText( sCaption );

      int iCtrlIdx = 0;
      int iCtrlTop = 15;
      for (int i=0; i<m_iNumPrimProps; i++)
      {
         long lPropDBID = BEMPX_GetPrimaryPropertyDBID( m_i1Class, i );
         int iError = 0;
         BEMProperty* pProp = BEMPX_GetProperty( lPropDBID, iError, m_iObjIdx );
         if ( (iError >= 0) && (pProp != NULL) )
         {
         	BEMPropertyType* pPropType = pProp->getType();
            m_iaPropType[ iCtrlIdx ] = pPropType->getPropType();

            if ( (m_iaPropType[ iCtrlIdx ] == BEMP_Sym) || (m_iaPropType[ iCtrlIdx ] == BEMP_Obj) )
            {
               CComboBoxCtl* pCombo = new CComboBoxCtl();
               // SAC 7/30/99 - revised call to set final (new) bForceEditable flag to TRUE
               pCombo->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                            CRect( PRIMDLG_CTRL_L, iCtrlTop, PRIMDLG_CTRL_R, iCtrlTop+220 ), this, IDC_PRIM_1+iCtrlIdx, FNT_STD,
                            FontY( 25 ), szCmbMsg, lPropDBID, -1, TRUE, FALSE, 0, 0, 0, 0, TRUE );
               pCombo->OnDisplayData(0,0);
               m_paCtrl[ iCtrlIdx ] = (CWnd*) pCombo;
            }
            else
            {
               DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL|ES_MULTILINE|ES_RIGHT;
               int   iExt    = 0;
               if (m_iaPropType[ iCtrlIdx ] == BEMP_Flt)
                  iExt = 11;  // SAC 11/21/16 - switched from fixed default of 2 to variable (11 -> decimal precision based on entered value)
               else if (m_iaPropType[ iCtrlIdx ] == BEMP_Str)
               {
                  dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL;
               }

               CEditCtl* pEdit = new CEditCtl();
               // SAC 7/30/99 - revised call to set final (new) bForceEditable flag to TRUE
               pEdit->Create( dwStyle, CRect( FontX(PRIMDLG_CTRL_L), FontY(iCtrlTop), FontX(PRIMDLG_CTRL_R), FontY((iCtrlTop+25)) ),
                            this, IDC_PRIM_1+iCtrlIdx, FNT_STD, iExt, szEdtMsg, lPropDBID, -1, 0, 0, FALSE, TRUE );
               m_paCtrl[ iCtrlIdx ] = (CWnd*) pEdit;
            }

            iCtrlIdx++;
            iCtrlTop += 30;
         }
      }

      // OK and Cancel buttons
      m_pOK = new CButtonCtl();
      m_pCancel = new CButtonCtl();

      m_pOK->Create( "OK", BS_DEFPUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                     //    CRect( PRIMDLG_WD-190, iDlgHt-61, PRIMDLG_WD-110, iDlgHt-38 ),
                         CRect( PRIMDLG_WD-185, iDlgHt-66, PRIMDLG_WD-105, iDlgHt-43 ),
                         this, IDOK, TDCT_Button, FNT_STD, szOKMsg, 0, TRUE, TRUE, FALSE, 0 );
      m_pCancel->Create( "Cancel", BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
                     //    CRect( PRIMDLG_WD-100, iDlgHt-61, PRIMDLG_WD- 20, iDlgHt-38 ),
                         CRect( PRIMDLG_WD-95, iDlgHt-66, PRIMDLG_WD- 15, iDlgHt-43 ),
                         this, IDCANCEL, TDCT_Button, FNT_STD, szCanMsg, 0, TRUE, TRUE, FALSE, 0 );

      m_bCreateControls = FALSE;
   }

   EnableToolTips(TRUE);

//	return CDialog::OnInitDialog();
	return TRUE;

// MFC default implementation
//   CDialog::OnInitDialog();
//	
//   // TODO: Add extra initialization here
//	
//   return TRUE;  // return TRUE unless you set the focus to a control
//	                // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrimData::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   CDC* pDC = &dc;

   pDC->SetBkMode( TRANSPARENT );
   pDC->SelectObject( GetCUIFont(FNT_STD) );

   // Draw label for each primary value control
   for (int i=0; i<m_iNumPrimProps; i++)
   {
      if (m_paCtrl[i] != NULL)
      {
         long lDBID = 0;
         if (m_paCtrl[i]->IsKindOf(RUNTIME_CLASS(CEditCtl)))
            lDBID = ((CEditCtl*)m_paCtrl[i])->m_lDBID;
         else if (m_paCtrl[i]->IsKindOf(RUNTIME_CLASS(CComboBoxCtl)))
            lDBID = ((CComboBoxCtl*)m_paCtrl[i])->m_lDBID;
         
         if (lDBID > 0)
         {
            int iError;
            BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
            if ((iError >= 0) && (pPropType != NULL))
            {
//               CWinRect ctrlRect( m_paCtrl[i], CWinRect::WINDOW );
//               ScreenToClient( &ctrlRect );
               CRect ctrlRect;
               m_paCtrl[i]->GetWindowRect( ctrlRect );
               ScreenToClient( &ctrlRect );

               CString sLabel = pPropType->getDescription().toLatin1().constData();
               if (sLabel.GetLength() > 0)
               {
                  if (pPropType->getNumValues() > 1)
                  {
                     CString sIdx;
                     sIdx.Format( "%d", BEMPX_GetArrayID( lDBID ) );
                     sLabel += ' ';
                     sLabel += sIdx;
                  }
                  sLabel += ':';
					   pDC->SetTextAlign( TA_RIGHT | TA_TOP );
                  pDC->TextOut( ctrlRect.left-FontX(5), ctrlRect.top+FontY(5), sLabel );
               }
				// SAC 11/21/16 - added units labels
               CString sUnitsLabel = pPropType->getUnitsLabel().toLatin1().constData();
               if (sUnitsLabel.GetLength() > 0)
               {
					   pDC->SetTextAlign( TA_LEFT | TA_TOP );
                  pDC->TextOut( ctrlRect.right+FontX(5), ctrlRect.top+FontY(5), sUnitsLabel );
					}
            }
         }
      }
   }
}


LONG CDlgPrimData::DisplayMods( UINT, LONG )
{
   CWnd *pChild = GetWindow( GW_CHILD );
   while ( pChild != NULL )
   {
      pChild->SendMessage( WM_DISPLAYDATA );
      pChild = pChild->GetNextWindow( GW_HWNDNEXT );
   }
   return 1;
}


BOOL CDlgPrimData::OnToolTipNotify( UINT /*id*/, NMHDR* pNMHDR, LRESULT* /*pResult*/ )
{
   TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*) pNMHDR;
   UINT nID = pNMHDR->idFrom;
   if (pTTT->uFlags & TTF_IDISHWND)
   {  // idFrom is actually the HWND of the tool
      CWnd* pCtrl = GetDlgItem( ::GetDlgCtrlID((HWND)nID) );
      if (pCtrl)
      {
         long lDBID = pCtrl->SendMessage( WM_GETCTRLDBID );
         if (lDBID > 0)
         {
            int iDBInst = (int) pCtrl->SendMessage( WM_GETCTRLDBINST );
            BEMPUIX_GetToolTipMessage( m_sToolStr, lDBID );
            m_sToolStr += "  (";
            m_sToolStr += GetCompDataTypeString( lDBID );
            m_sToolStr += " data status: ";
            m_sToolStr += GetDataStatusString( lDBID, iDBInst );
            m_sToolStr += ")";
            pTTT->lpszText = (LPTSTR)(LPCTSTR)m_sToolStr;
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
         }
      }
   }
   return(FALSE);
}


