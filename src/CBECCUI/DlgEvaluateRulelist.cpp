// DlgEvaluateRulelist.cpp : implementation file
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
#include "ComplianceUIDoc.h"
#include "DlgEvaluateRulelist.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMCmpMgr\BEMCmpMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEvaluateRulelist dialog


CDlgEvaluateRulelist::CDlgEvaluateRulelist(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEvaluateRulelist::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEvaluateRulelist)
	m_sRulelist = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEvaluateRulelist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEvaluateRulelist)
	DDX_Control(pDX, IDC_RULELISTS, m_lbRulelist);
	DDX_LBString(pDX, IDC_RULELISTS, m_sRulelist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEvaluateRulelist, CDialog)
	//{{AFX_MSG_MAP(CDlgEvaluateRulelist)
	ON_LBN_DBLCLK(IDC_RULELISTS, OnDblClkOnRulelist)
	ON_LBN_SELCHANGE(IDC_RULELISTS, OnSelChangeRulelist)
	ON_BN_CLICKED(IDC_EVALRULELIST, OnEvalRulelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEvaluateRulelist message handlers

BOOL CDlgEvaluateRulelist::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   CWaitCursor wait;

   QVector<QString> sRulelistNames;
   int iNumLists = CMX_GetRulelistNames( sRulelistNames );
   for (int i=0; i<iNumLists; i++)
      m_lbRulelist.AddString( sRulelistNames[i].toLatin1().constData() );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEvaluateRulelist::OnDblClkOnRulelist() 
{
   EvaluateSelectedRulelist();
}

void CDlgEvaluateRulelist::OnSelChangeRulelist() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgEvaluateRulelist::OnEvalRulelist() 
{
   EvaluateSelectedRulelist();
}

void CDlgEvaluateRulelist::EvaluateSelectedRulelist()
{
   UpdateData();

//   CString sMsg = "Evaluate '";
//   sMsg += m_sRulelist;
//   sMsg += "' Rulelist";
//   MessageBox( sMsg );

   if (this)	// always true
   {
		BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);   // SAC 8/22/11

      CWaitCursor wait;

      CTime tStart = CTime::GetCurrentTime();

		BOOL bMarkRuleDataUserDefined = (ReadProgInt( "options", "MarkRuleDataUserDefined", 0 /*default*/ ) > 0);  // SAC 3/17/13
      BOOL bEvalSuccessful = CMX_EvaluateRuleset( m_sRulelist, bLogRuleEvaluation, bMarkRuleDataUserDefined /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/, NULL, NULL, NULL, epInpRuleDebugInfo );

      CTime tEnd = CTime::GetCurrentTime();

      // Construct message to display
      int iDeltaT = (int) (tEnd.GetTime() - tStart.GetTime());
      CString sDeltaT;
      sDeltaT.Format( "\n\nTime Elapsed (min:sec):  %2d:%s%d", iDeltaT/60, (iDeltaT%60 < 10 ? "0" : ""), iDeltaT%60 );
      CString sMsg = (bEvalSuccessful ? "Rulelist Evaluated Successfully." : "Rulelist Evaluation Failed.");
      sMsg += sDeltaT;
      MessageBox( sMsg );

	// SAC 7/16/12 - added code to store IBD 7 XML details files following File Open operation
		if (ReadProgInt( "options", "StoreBEMDetails", 0) > 0)
	   {	CWnd* pMainWnd = AfxGetMainWnd();
		   if (pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
			{	CDocument* pDoc = ((CFrameWnd*)pMainWnd)->GetActiveDocument();
			   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CDocument)))
				{	CString sInputFile = pDoc->GetPathName();
					if (sInputFile.ReverseFind('.') > 0)
					{	CString sDbgFileName;
						sDbgFileName.Format( "%s - %s.ibd-Detail", sInputFile.Left( sInputFile.ReverseFind('.') ), m_sRulelist );
						BEMPX_WriteProjectFile( sDbgFileName, BEMFM_DETAIL /*FALSE*/ );
						sDbgFileName.Format( "%s - %s.xml", sInputFile.Left( sInputFile.ReverseFind('.') ), m_sRulelist );
						VERIFY( BEMPX_WriteProjectFile( sDbgFileName, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, TRUE /*bWriteAllProperties*/,
																	FALSE /*bSupressAllMessageBoxes*/, BEMFT_XML /*iFileType*/ ) );
					// SAC 3/17/13 - added writing of file immediately following rule evaluation that includes ALL data and COULD be imported back into -Com/-Res program
					   CString sProjExt = ReadProgString( "options", "ProjectFileExt", "" );		// SAC 3/8/20
					   if (sProjExt.IsEmpty())
							sDbgFileName.Format( "%s - %s.%s", sInputFile.Left( sInputFile.ReverseFind('.') ), m_sRulelist, pszCUIFileExt[0] );
						else
							sDbgFileName.Format( "%s - %s.%s", sInputFile.Left( sInputFile.ReverseFind('.') ), m_sRulelist, sProjExt );
						BEMPX_WriteProjectFile( sDbgFileName, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, TRUE /*bWriteAllProperties*/ );
					}
				}
			}
		}
   }

   return;
}
