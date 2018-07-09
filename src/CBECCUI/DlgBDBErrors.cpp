// DlgBDBErrors.cpp : implementation file
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
#include "ComplianceUIDoc.h"
#include "CUIGlobl.h"
#include "DlgBDBErrors.h"
#include "..\BEMProc\BEMProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBDBErrors dialog


CDlgBDBErrors::CDlgBDBErrors(const char* pszLblTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBDBErrors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBDBErrors)
	m_sLabel = _T("");
	//}}AFX_DATA_INIT

   m_bResetScrollWidth = FALSE;
   if (pszLblTemplate)
	   m_sLabelTemplate = pszLblTemplate;
   else
	   m_sLabelTemplate = "The following %d building database anomalies were found:";
}


void CDlgBDBErrors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBDBErrors)
	DDX_Text(pDX, IDC_BDBERRLABEL, m_sLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBDBErrors, CDialog)
	//{{AFX_MSG_MAP(CDlgBDBErrors)
	ON_BN_CLICKED(IDC_RESOLVENOTINPUTS, OnResolveNotInputs)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBDBErrors message handlers

BOOL CDlgBDBErrors::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   m_bResetScrollWidth = TRUE;

//    PUSHBUTTON      "&Resolve NotInput Issues",IDC_RESOLVENOTINPUTS,240,141,100,14,WS_DISABLED

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgBDBErrors::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

   if (m_bResetScrollWidth)
   {
      m_bResetScrollWidth = FALSE;
		BOOL bHaveNotInputs = FALSE;	// SAC 5/5/14
      CListBox* pErrList = (CListBox*) GetDlgItem( IDC_BDBERRLIST );
      if (pErrList)
      {
         int iHorizExtent = 0;
         int iNumErrors = BEMPX_GetNumErrors();
         pErrList->ResetContent();
         for (int i=0; i<iNumErrors; i++)
         {
            const BEMError* pErr = BEMPX_GetErrorPtr( i );
            if (pErr)
            {
               pErrList->AddString( pErr->m_sMessage.toLatin1().constData()  );
					if (!bHaveNotInputs && pErr->m_sMessage.indexOf("NotInput should not be") > 0)
						bHaveNotInputs = TRUE;
               CSize size = dc.GetTextExtent( pErr->m_sMessage.toLatin1().constData()  );
               if (size.cx > iHorizExtent)
                  iHorizExtent = size.cx;
            }
         }
         pErrList->SetHorizontalExtent( iHorizExtent );

	      m_sLabel.Format( m_sLabelTemplate, iNumErrors );
         UpdateData( FALSE );
      }

		if (bHaveNotInputs)
		{	CWnd* pRNI = GetDlgItem( IDC_RESOLVENOTINPUTS );
			if (pRNI)
				pRNI->EnableWindow( TRUE );
		}
   }
}

void CDlgBDBErrors::OnResolveNotInputs() 
{
	if (MessageBox( _T("Choose 'Yes' to remove user input from all properties classified by the compliance ruleset as NotInput."),
			eszWarning, MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
	{
		int iNumUserInpMods = BEMPX_BlastInvalidUserInputs( BEM_UserInpFix_NotInput );			ASSERT( iNumUserInpMods > 0 );
		if (iNumUserInpMods > 0)
		{
			SetDataModifiedFlag( TRUE );
			// execute compliance rulelist #1
			GetParentFrame()->SendMessage( WM_EVALPROPOSED, DefaultAction_InitAnalysis );
		}

		CWnd* pRNI = GetDlgItem( IDC_RESOLVENOTINPUTS );
		if (pRNI)
			pRNI->EnableWindow( FALSE );
	}
}
