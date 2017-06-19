// DlgRTFDisplay.cpp : implementation file
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
#include "CUIGlobl.h"
#include "DlgRTFDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRTFDisplay dialog


CDlgRTFDisplay::CDlgRTFDisplay( CWnd* pParent /*=NULL*/, const char* pszRTFFileName /*=NULL*/ )
	: CResizableDialog(CDlgRTFDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRTFDisplay)
	m_bShowHelp = TRUE;
	//}}AFX_DATA_INIT

   m_sRTFFileName = pszRTFFileName;
}


void CDlgRTFDisplay::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRTFDisplay)
	DDX_Control(pDX, IDC_WHATNOW_RTF, m_RTFCtrl);
	DDX_Check(pDX, IDC_WHATNOW_SHOWHELP, m_bShowHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRTFDisplay, CResizableDialog)
	//{{AFX_MSG_MAP(CDlgRTFDisplay)
	ON_BN_CLICKED(IDOK, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRTFDisplay message handlers

static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CFile* pFile = (CFile*) dwCookie;
   *pcb = pFile->Read(pbBuff, cb);
   return 0;
}

BOOL CDlgRTFDisplay::OnInitDialog() 
{
	CResizableDialog::OnInitDialog();

   // set dialog icon to the same as the wizard icon	
   CWinApp* pApp = AfxGetApp();
   if (pApp)
   {
      HICON hIcon = pApp->LoadIcon( IDI_WIZARD );
      if (hIcon)
         SetIcon( hIcon, FALSE );
   }

	// Anchor Various Controls to dialog positions
   AddAnchor( IDOK, BOTTOM_RIGHT );
   AddAnchor( IDC_WHATNOW_SHOWHELP, BOTTOM_LEFT );
   AddAnchor( IDC_WHATNOW_RTF, TOP_LEFT, BOTTOM_RIGHT );

   // The file from which to load the contents of the rich edit control.
   ASSERT( !m_sRTFFileName.IsEmpty() );
   ASSERT( FileExists( m_sRTFFileName ) );
   CFile cFile( m_sRTFFileName, CFile::modeRead | CFile::shareDenyWrite );
   EDITSTREAM es;
   es.dwCookie = (DWORD) &cFile;
   es.pfnCallback = MyStreamInCallback; 
   m_RTFCtrl.StreamIn(SF_RTF, es);

   // Enable save/restore of help dialog size/position
   EnableSaveRestore( "options", "WizHelp" );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRTFDisplay::OnClose() 
{
	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed in OnCopyOffCDROM().\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

   if (!m_bShowHelp)	
      WriteProgInt( "options", "ShowHelpFollowingWizard", 0 );

   OnOK();
}
