// DlgStartLoad.cpp : implementation file
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 2000, SAC Software Solutions, Inc.                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "ComplianceUI.h"
#include "..\BEMProc\BEMProc.h"
#include "DlgStartLoad.h"
#include "CUIGlobl.h"
#include "MainFrm.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int CalcMaxStringWidth( CComboBox* pCMBB )
{
   int nWidth = -1;
   if (pCMBB)
   {
   	CWindowDC dc( pCMBB );

   	// Make sure we use the correct font.
   	CFont* pOldFont = dc.SelectObject( pCMBB->GetFont() );
   	
   	CRect rectText;
   	CString strLBText;

   	const int cyVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
   	const int cxPadding = ::GetSystemMetrics(SM_CXFIXEDFRAME);

   	const int nCount = pCMBB->GetCount();

   	for (int i=0; i < nCount; i++)
   	{
   		pCMBB->GetLBText(i, strLBText);

   		rectText.SetRectEmpty();
   		dc.DrawText(strLBText, rectText, DT_CALCRECT);
   	
   		nWidth = std::max(nWidth, rectText.Width() + (cxPadding * 2));
   	}

   	// Add the scroll bar.
   	//
   	// TODO: Save the fact that we have a vertical scroll
   	// bar in PreCreateWindow or PreSubclassWindow and use
   	// that here.
   	nWidth += cyVScroll;

   	dc.SelectObject(pOldFont);
   }

	return nWidth;
}

int ResizeToFitContent( CComboBox* pCMBB, int nDropDownHeight )
{
   int nWidth = -1;
   if (pCMBB)
   {
   	CRect rcDropDown;
   	pCMBB->GetDroppedControlRect(rcDropDown);
   	nDropDownHeight = (nDropDownHeight > 0) ? nDropDownHeight : rcDropDown.Height();

   	nWidth = CalcMaxStringWidth( pCMBB );

      // Only resize if new width is WIDER than initial one
   	if ((nWidth > 0) && (nDropDownHeight > 0) && (nWidth > rcDropDown.Width()))
   	{
         pCMBB->SetDroppedWidth( nWidth );
   //		VERIFY(SetWindowPos(NULL, 0, 0, nWidth, nDropDownHeight,
   //			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER));
   	}
   }

	return nWidth;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgStartLoad dialog

CDlgStartLoad::CDlgStartLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStartLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStartLoad)
	//}}AFX_DATA_INIT
   m_iOption = 0;
}


void CDlgStartLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStartLoad)
	DDX_Control(pDX, IDC_START_FILELIST, m_cmbbFileList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStartLoad, CDialog)
	//{{AFX_MSG_MAP(CDlgStartLoad)
	ON_BN_CLICKED(IDC_START_BATCH, OnStartBatchProcessing)
	ON_BN_CLICKED(IDC_START_BLANK, OnStartBlankSlate)
	ON_BN_CLICKED(IDC_START_EXISTING, OnStartExistingProject)
#ifdef UI_CANRES
	ON_BN_CLICKED(IDC_START_NEW, OnStartNewProject)
#endif   // UI_CANRES
	ON_BN_CLICKED(IDC_START_RECENT, OnStartRecentProject)
	ON_CBN_SELCHANGE(IDC_START_FILELIST, OnSelChangeStartFilelist)
	ON_BN_CLICKED(IDC_START_OVERVIEW, OnStartViewOverview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgStartLoad message handlers

BOOL CDlgStartLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();

   // Load MRU file list into combobox
   if (epMRU && epMRU->GetSize() > 0)
   {
      // SAC 7/31/99 - reset maximum # characters allowed in display string
      int iSaveMRUMaxDisplayLength = epMRU->m_nMaxDisplayLength;
      epMRU->m_nMaxDisplayLength = 55;

      char pszCurDir[_MAX_PATH];   /* Get the current working directory: */
      _getcwd( pszCurDir, _MAX_PATH );
      int iCurDirLen = strlen( pszCurDir );

      int iSize = epMRU->GetSize();
      int iCmbbIdx = 0;
      for (int i=0; i<iSize; i++)
      {
         CString sRecentFile = (*epMRU)[i];
         if (sRecentFile.GetLength() > 0 && FileExists( sRecentFile ))
         {
            CString sCopy = sRecentFile;
            if (!epMRU->GetDisplayName( sCopy, i, pszCurDir, iCurDirLen ) ||
                sCopy.IsEmpty())
               sCopy = sRecentFile;

            m_cmbbFileList.AddString( sCopy );
            m_cmbbFileList.SetItemData( iCmbbIdx++, i );
         }
      }

      // SAC 7/31/99 - restore original maximum # characters allowed in display string
      epMRU->m_nMaxDisplayLength = iSaveMRUMaxDisplayLength;
   }

   if (m_cmbbFileList.GetCount() > 0)
   {
      m_cmbbFileList.SetCurSel( 0 );
      ResizeToFitContent( &m_cmbbFileList, 0 );
   }
   else
   {
      // disable recent file radio button and combobox
      m_cmbbFileList.EnableWindow( FALSE );
      CWnd* pWnd = GetDlgItem( IDC_START_RECENT );
      if (pWnd)
         pWnd->EnableWindow( FALSE );

      // reset default option to existing project (if set to recent file)
      if (m_iOption >= 0)
         m_iOption = -1;  // SAC 2/5/14 - was: -3
   }

	int iAllowBlankSlateDefault = 1;		// SAC 2/5/14 - added option to turn OFF access to blank slate
#ifdef UI_CANRES
	iAllowBlankSlateDefault = 0;
#endif
	bool bAllowBlankSlate = (ReadProgInt( "options", "AllowBlankSlate", iAllowBlankSlateDefault ) > 0);
	if (!bAllowBlankSlate && m_iOption == -3)
		m_iOption = -1;
	if (!bAllowBlankSlate)
	{	CWnd* pWnd = GetDlgItem( IDC_START_BLANK );
		if (pWnd)
			pWnd->ShowWindow( SW_HIDE );
	}

// SAC 11/20/17 - removed code to hide batch processing option when developer menu option not set
	int iEnableBatchProc = 1;
#ifdef UI_CANRES
	iEnableBatchProc = 0;		// SAC 12/3/17 - default to toggling OFF batch processing option for NRes
#endif
	bool bEnableBatchProc = (ReadProgInt( "options", "EnableBatchProcessing", iEnableBatchProc ) > 0 ||
									 ReadProgInt( "options", "DeveloperMenu", 0 ) > 0);
	if (!bEnableBatchProc && m_iOption == -4)
		m_iOption = -1;
	if (!bEnableBatchProc)
	{	CWnd* pWnd = GetDlgItem( IDC_START_BATCH );
		if (pWnd)
			pWnd->ShowWindow( SW_HIDE );
	}

   UINT uiSelRadioID;
   switch (m_iOption)
   {
      case -1 : uiSelRadioID = IDC_START_EXISTING;   break;
      case -3 : uiSelRadioID = IDC_START_BLANK;      break;
      case -4 : uiSelRadioID = IDC_START_BATCH;      break;
      default : uiSelRadioID = IDC_START_RECENT;     break;
   }
   CButton* pBtn = (CButton*) GetDlgItem( uiSelRadioID );
   if (pBtn)
      pBtn->SetCheck( 1 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStartLoad::OnStartRecentProject() 
{   m_iOption =  0;   }
void CDlgStartLoad::OnStartExistingProject() 
{   m_iOption = -1;   }
void CDlgStartLoad::OnStartNewProject() 
{   m_iOption = -2;   }
void CDlgStartLoad::OnStartBlankSlate() 
{   m_iOption = -3;   }
void CDlgStartLoad::OnStartBatchProcessing() 
{   m_iOption = -4;   }

void CDlgStartLoad::OnSelChangeStartFilelist() 
{
   if (m_iOption < 0)
   {
      UINT uiSelRadioID;
      switch (m_iOption)
      {
         case -1 : uiSelRadioID = IDC_START_EXISTING;   break;
         case -2 : uiSelRadioID = IDC_START_NEW;        break;
         case -3 : uiSelRadioID = IDC_START_BLANK;      break;
         case -4 : uiSelRadioID = IDC_START_BATCH;      break;
         default : uiSelRadioID = 0;                    break;
      }
      CButton* pBtn = (CButton*) GetDlgItem( uiSelRadioID );
      if (pBtn)
         pBtn->SetCheck( 0 );

      pBtn = (CButton*) GetDlgItem( IDC_START_RECENT );
      if (pBtn)
         pBtn->SetCheck( 1 );
      m_iOption = 0;
   }
}

void CDlgStartLoad::OnCancel() 
{
   m_iOption = -5;
	CDialog::OnCancel();
}

void CDlgStartLoad::OnOK() 
{
   if (m_iOption >= 0)
      m_iOption = (int) m_cmbbFileList.GetItemData( m_cmbbFileList.GetCurSel() );

	CDialog::OnOK();
}

void CDlgStartLoad::OnStartViewOverview() 
{
//   CFrameWnd* pFrame = GetParentFrame();
//   if (pFrame  &&  pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
//      ((CMainFrame*)pFrame)->WinHelp( (DWORD) ReadProgInt( "options", "QuickTourHelpID", 100953 ) );
	if (!esOverviewPDF.IsEmpty() && FileExists( esOverviewPDF ))
	{	int idx = esOverviewPDF.ReverseFind('\\');
		CString sOverviewPath = (idx > 0 ? esOverviewPDF.Left( idx ) : "");
		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", esOverviewPDF, NULL, sOverviewPath, SW_SHOWNORMAL );		hinstShellExec;
	}
	else
	{	CString sPDFNotFound = CString("Program overview documentation not found:\n   ") + esOverviewPDF;
		AfxMessageBox( sPDFNotFound );
	}
}
