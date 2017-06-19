// DlgRangeError.cpp : implementation file
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
#include "DlgRangeError.h"
#include "BEMProcUIX.h"
#include "BEMProcUI_Globals.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRangeError dialog


CDlgRangeError::CDlgRangeError( const char* pszErrMsg /*=NULL*/, int iDialogMode /*=SWDM_Default*/,
                                CWnd* pParent /*=NULL*/, const char* pszRangeLabel /*=NULL*/,
                                const char* pszRangePrompt /*=NULL*/, BOOL bAllowContinue /*=TRUE*/,
                                const char* pszDlgCaption /*=NULL*/ )
	: CDialog(CDlgRangeError::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRangeError)
	m_sErrMsg = pszErrMsg;
	//}}AFX_DATA_INIT

   m_bContinue   = TRUE;  // default action = Continue
   m_iDialogMode = iDialogMode;

   m_bInitializeDialog = TRUE;

   m_sRangeLabel  = pszRangeLabel;   // IDC_RANGE_LABEL
   m_sRangePrompt = pszRangePrompt;  // IDC_RANGE_PROMPT
   m_bAllowContinue = bAllowContinue;
   m_sDlgCaption = pszDlgCaption;   // SAC 6/4/01
}


void CDlgRangeError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRangeError)
	DDX_Text(pDX, IDC_RANGE_ERRMSG, m_sErrMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRangeError, CDialog)
	//{{AFX_MSG_MAP(CDlgRangeError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRangeError message handlers

BOOL CDlgRangeError::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   if (m_bInitializeDialog)
   {
      if (!m_sDlgCaption.IsEmpty())  // SAC 6/4/01
         SetWindowText( m_sDlgCaption );

      if (!m_bAllowContinue)
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

      m_bInitializeDialog = FALSE;
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRangeError::OnCancel() 
{
   m_bContinue = FALSE;
	
	CDialog::OnCancel();
}

