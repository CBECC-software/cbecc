// ComplianceUIDoc.cpp : implementation of the CComplianceUIDoc class
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

#include "ComplianceUIDoc.h"
#include "CUIGlobl.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMCmpMgr\BEMCmpMgr.h"
#include "mainfrm.h"
#include "MainView.h"
#include "CUILibView.h"
#include <io.h>

#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
using namespace boost::posix_time;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Global Access to the Document
// This works because this is an SDI app

void SetDataModifiedFlag( BOOL bMod )
{
   CWnd* mainWnd = AfxGetMainWnd();
   ASSERT(mainWnd != NULL);
   ASSERT(mainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)));
   
   CDocument* pDoc = ((CFrameWnd*)mainWnd)->GetActiveDocument();
   if (pDoc == NULL)
   {  // we have main frame but no document - try getting doc from active view
      CView* pView = ((CFrameWnd*)mainWnd)->GetActiveView();
      ASSERT(pView != NULL);
      pDoc = pView->GetDocument();
   }
   ASSERT(pDoc != NULL);
   ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)));
   
   pDoc->SetModifiedFlag( bMod );
}


/////////////////////////////////////////////////////////////////////////////
// CComplianceUIDoc

IMPLEMENT_DYNCREATE(CComplianceUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CComplianceUIDoc, CDocument)
	//{{AFX_MSG_MAP(CComplianceUIDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplianceUIDoc construction/destruction

CComplianceUIDoc::CComplianceUIDoc()
{
	// TODO: add one-time construction code here

}

CComplianceUIDoc::~CComplianceUIDoc()
{
}

BOOL CComplianceUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (ebAppInitialized)
	{
// SAC 2/28/14 - experiment w/ NOT loading ruleset until/unless app already LOADED
	// SAC - 3/3/98 - now done in the process of loading new ruleset
	//   // Building Database initialization code
	//   BEMPX_DeleteAllObjects();
	   LoadRuleset();
	
	   CString sInitLogFileName = ReadProgString( "paths", "ProjectsPath", "", TRUE );
	   sInitLogFileName += "untitled.log";
	   BEMPX_WriteLogFile( "File / New Selected", sInitLogFileName, TRUE );
	
	   // MainFrame initialization code
	   CWnd* pMainWnd = AfxGetMainWnd();
	   if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
	   {
	// SAC - 3/9/98
	//      ((CMainFrame*)pMainWnd)->m_sCurrentFileName.Empty();
	      
	      ((CMainFrame*)pMainWnd)->OnUpdateFrameTitle(TRUE);
	
	//      CView* pView = ((CMainFrame*)pMainWnd)->GetActiveView();
	      CView* pView = (CView*) ((CMainFrame*)pMainWnd)->m_wndSplitter.GetPane(0,0);
	      if (pView != NULL)            // update main view's tree control(s)
	         pView->SendMessage( WM_DISPLAYDATA );
	   }
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CComplianceUIDoc serialization

void CComplianceUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CComplianceUIDoc diagnostics

#ifdef _DEBUG
void CComplianceUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CComplianceUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComplianceUIDoc commands

void CComplianceUIDoc::OnFileSave()
{
   CWnd* pMainWnd = AfxGetMainWnd();
   if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
      ((CMainFrame*)pMainWnd)->OnFileSave();
}

void CComplianceUIDoc::OnFileSaveAs()
{
   CWnd* pMainWnd = AfxGetMainWnd();
   if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
      ((CMainFrame*)pMainWnd)->OnFileSaveAs();
}


BOOL CComplianceUIDoc::OnSaveDocument(const char* pszPathName)
{
   CWnd* pMainWnd = AfxGetMainWnd();
   if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
      ((CMainFrame*)pMainWnd)->SaveFile( pszPathName );

   return TRUE;                  // success
}


static char BASED_CODE szSave[] = "The user input building design must be saved before performing %s.  "  // compliance analysis.  "
                                  "Press OK to save the user design to the current project file name.  If you would like to "
                                  "save the user design as a new project, press Cancel, then select File - Save As to create "
                                  "the new project file and then re-initiate %s.";		// compliance analysis again.";

BOOL CComplianceUIDoc::CUISaveModified( const char* pszUserAction /*=NULL*/ )		// SAC 8/15/14 - switched from BOOL bPreAnalysis to char string describing action user initiated
{
	if (!IsModified())
		return TRUE;        // ok to continue

	// get name/title of document
	CString name = m_strPathName;
	if (name.IsEmpty())
	{
		name = m_strTitle;
		if (name.IsEmpty())
			VERIFY(name.LoadString(AFX_IDS_UNTITLED));
	}

   int iUserAction = IDCANCEL;
	if (pszUserAction && strlen( pszUserAction ) > 0)
	{	if (!BEMPX_GetUIActiveFlag())
			iUserAction = IDOK;
		else
		{	CString sSaveMsg;		sSaveMsg.Format( szSave, pszUserAction, pszUserAction );
			iUserAction = AfxMessageBox( sSaveMsg, MB_OKCANCEL );
	}	}
	else
	{	CString prompt;
		AfxFormatString1(prompt, AFX_IDP_ASK_TO_SAVE, name);
		iUserAction = AfxMessageBox(prompt, MB_YESNOCANCEL, AFX_IDP_ASK_TO_SAVE);
	}

	switch (iUserAction)
	{
	case IDCANCEL:
		return FALSE;       // don't continue

	case IDYES:
	case IDOK:
		// If so, either Save or Update, as appropriate
		if (_access(m_strPathName, 6) != 0)
		{
         OnFileSaveAs();
//			if (!DoSave(NULL))
//				return FALSE;   // don't continue
		}
		else
		{
         OnFileSave();
//			if (!DoSave(m_strPathName))
//				return FALSE;   // don't continue
		}
		break;

	case IDNO:
		// If not saving changes, revert the document
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going
}


BOOL CComplianceUIDoc::SaveModified()
{
   return CUISaveModified();
}


BOOL CComplianceUIDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
   // This call attempts to load the file as a CArchive, calling the above Serialize() function
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// Now that the default Open.. is done, really load the file via CMainFrame's OpenTheFile()
   OpenTheFile( lpszPathName );
	
	return TRUE;
}


//static char BASED_CODE szFiles[]   = "files";
//static char BASED_CODE szDefRule[] = "RulesetFile";

#define  MAX_BEMBASE_DATA_SET_ERRORS  100

bool IsXMLFileExt( CString sExt )	// SAC 10/29/15
{	bool bRetVal = false;
#ifdef UI_CANRES
	bRetVal = (!sExt.CompareNoCase(".cibdx") || !sExt.CompareNoCase(".cibd16x") || !sExt.CompareNoCase(".xml"));
#elif UI_CARES
	bRetVal = (!sExt.CompareNoCase(".ribdx") || !sExt.CompareNoCase(".ribd16x") || !sExt.CompareNoCase(".xml"));
#endif
	bRetVal = (bRetVal || !sExt.CompareNoCase(".xml"));
	return bRetVal;
}

bool IsRecognizedFileExt( CString sExt )	// SAC 10/29/15
{
#ifdef UI_CANRES
	bool bRetVal = (!sExt.CompareNoCase(".cibdx") || !sExt.CompareNoCase(".cibd") || !sExt.CompareNoCase(".cibd16x") || !sExt.CompareNoCase(".cibd16"));
#elif UI_CARES
	bool bRetVal = (!sExt.CompareNoCase(".ribdx") || !sExt.CompareNoCase(".ribd") || !sExt.CompareNoCase(".ribd16x") || !sExt.CompareNoCase(".ribd16"));
#else
	bool bRetVal = (!sExt.CompareNoCase(".ibd"));
#endif
	return bRetVal;
}

void BaseFileExt( CString& sExt )	// SAC 10/29/15
{
#ifdef UI_CANRES
	sExt = "cibd";
#elif UI_CARES
	sExt = "ribd";
#else
	sExt = "ibd";
#endif
	return;
}

void LoadFileExtensionString( CString& sSaveAsExt, bool bUseProjectData, bool bXML /*=false*/ )	// SAC 10/29/15
{	CString sBaseExt, sCodeYr, sXML;
	BaseFileExt( sBaseExt );
	if (bXML)
		sXML = "x";
	if (bUseProjectData)
		CodeYearAbbrev( sCodeYr );	
	else
	{
#ifdef UI_PROGYEAR2016
		sCodeYr = "16";
#endif
	}
	sSaveAsExt.Format( "%s%s%s", sBaseExt, sCodeYr, sXML );
}

bool FileExtensionAllowsSave( CString sSaveAsExt )
{	bool bRetVal = false;
	if (sSaveAsExt.GetLength() > 2)
	{	if (sSaveAsExt[0] == '.')
			sSaveAsExt = sSaveAsExt.Right( sSaveAsExt.GetLength()-1 );
		CString sDfltExt, sDfltXMLExt;
		LoadFileExtensionString( sDfltExt   , true /*bUseProjectData*/, false /*bXML*/ );
		LoadFileExtensionString( sDfltXMLExt, true /*bUseProjectData*/, true  /*bXML*/ );
		bRetVal = (	!sSaveAsExt.CompareNoCase( sDfltExt    ) ||
						!sSaveAsExt.CompareNoCase( sDfltXMLExt ) ||
						!sSaveAsExt.CompareNoCase( "xml" ) );
	}
	return bRetVal;
}

void LoadFileOptionString( CString& sSaveAs, bool bUseProjectData )	// SAC 10/29/15
{	CString sBaseExt, sCodeYr;
	BaseFileExt( sBaseExt );
	CString sFileDescrip;
	if (bUseProjectData)
		CodeYearAbbrev( sCodeYr );	
	else
	{
#ifdef UI_PROGYEAR2016
		sCodeYr = "16";
#endif
	}
#ifdef UI_CANRES
		sFileDescrip = "SDD ";
#elif UI_CARES
		sFileDescrip = "Res ";
#endif

	CString sInsertFileType;
	if (!bUseProjectData)  // SAC 11/17/15 - allow selection of other types even when ruleset switching toggled OFF - was:  && ReadProgInt( "options", "EnableRulesetSwitching", 0 ) > 0)	// SAC 10/30/15 - enable selection of other recognized and selectable file types
	{
		LoadRulesetListIfNotLoaded();
		if ((sCodeYr.IsEmpty() || !sCodeYr.Compare("13")) && CodeYearRulesetAvailable( "2016" ))
			sInsertFileType.Format( "2016 %sProject Files (*.%s16)|*.%s16|2016 %sXML Project Files (*.%s16x)|*.%s16x|", sFileDescrip, sBaseExt,  sBaseExt, sFileDescrip, sBaseExt,  sBaseExt );
		else if (!sCodeYr.Compare("16") && CodeYearRulesetAvailable( "2013" ))
			sInsertFileType.Format( "2013 %sProject Files (*.%s)|*.%s|2013 %sXML Project Files (*.%sx)|*.%sx|", sFileDescrip, sBaseExt,  sBaseExt, sFileDescrip, sBaseExt,  sBaseExt );
	}

	sSaveAs.Format( "%sProject Files (*.%s%s)|*.%s%s|%sXML Project Files (*.%s%sx)|*.%s%sx|%sXML Files (*.xml)|*.xml|All Files (*.*)|*.*||",
							sFileDescrip, sBaseExt, sCodeYr, sBaseExt, sCodeYr, sFileDescrip, sBaseExt, sCodeYr, sBaseExt, sCodeYr, sInsertFileType );
}

void CodeYearAbbrev( CString& sCodeYearAbbrev, bool bForFileExtension /*=true*/ )		// SAC 10/29/15
{	sCodeYearAbbrev.Empty();
#ifdef UI_CANRES
		BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:EngyCodeYear"   ), sCodeYearAbbrev );
#elif UI_CARES
		BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:EnergyCodeYear" ), sCodeYearAbbrev );
#endif

	if (bForFileExtension && !sCodeYearAbbrev.Compare("2013"))
		sCodeYearAbbrev.Empty();
	else if (bForFileExtension && !sCodeYearAbbrev.Compare("2010"))	// S901G
		sCodeYearAbbrev.Empty();
	else if (sCodeYearAbbrev.GetLength() == 4)
		sCodeYearAbbrev = sCodeYearAbbrev.Right(2);
	return;
}

BOOL CComplianceUIDoc::OpenTheFile( CPathName sInputFile, BOOL bWriteToLog, BOOL bRestore,
												const char* pszNewRulesetFile /*=NULL*/, long lRulesetSymVal /*=-1*/, BOOL bNormalRulesetUpdates /*=TRUE*/ )
{
   BOOL bRetVal = FALSE;

	CWaitCursor wait;

   if ( sInputFile.IsEmpty() )
      return FALSE;

   CString sExt;
//   sInputFile.MakeUpper();
   sInputFile.GetExt( sExt );
//   if ( sExt.CompareNoCase( ".RIBD" ) == 0 || sExt.CompareNoCase( ".CIBD" ) == 0 )
//      eInterfaceMode = IM_INPUT;
//   else if ( sExt.CompareNoCase( ".RPBD" ) == 0 || sExt.CompareNoCase( ".CPBD" ) == 0 )
//      eInterfaceMode = IM_PROPOSED;
//   else if ( sExt.CompareNoCase( ".RBBD" ) == 0 || sExt.CompareNoCase( ".CBBD" ) == 0 )
//      eInterfaceMode = IM_BUDGET;
   sExt.MakeUpper();
   if ( sExt.Find( "PBD" ) > 0 || sExt.Find( "PXML" ) > 0 )
      eInterfaceMode = IM_PROPOSED;
   else if ( sExt.Find( "BBD" ) > 0 || sExt.Find( "BXML" ) > 0 )
      eInterfaceMode = IM_BUDGET;
   else if ( sExt.Find( "IBD" ) > 0 || sExt.Find( "XML" ) > 0 )
      eInterfaceMode = IM_INPUT;
   else
   {	CString sBadExtMsg;		sBadExtMsg.Format( "Unrecognized file extension '%s'", sExt );
      AfxMessageBox( sBadExtMsg );
   }

//	bool bExtIsXML = IsXMLFileExt( sExt );		// SAC 10/29/15
	bool bLogProjectOpen = (ReadProgInt( "options", "LogProjectOpen", 0) > 0);		// SAC 10/22/13
	CString sLogMsg;
	ptime t1(microsec_clock::local_time());

   int i;
	// enable the UI reporting of all (up to MAX_BEMBASE_DATA_SET_ERRORS) BEMBase project file data setting errors
   int iaFailedBEMBaseDBIDs[   MAX_BEMBASE_DATA_SET_ERRORS ];
   int iaFailedBEMBaseObjIdxs[ MAX_BEMBASE_DATA_SET_ERRORS ];  // facilitate more informative error reporting
   for (i=0; i<MAX_BEMBASE_DATA_SET_ERRORS; i++)
   {
      iaFailedBEMBaseDBIDs[i] = 0;
      iaFailedBEMBaseObjIdxs[i] = -1;
   }
   QStringList saFailedBEMBaseData;  // facilitate more informative error reporting

// SAC 11/17/15 - code relating to automatically updating past project files to the latest program
	bool bRuleSwitchingAllowed = (ReadProgInt( "options", "EnableRulesetSwitching", 0 ) > 0);
	CString sRulesetPath = ReadProgString( "paths", "RulesetPath", "", TRUE );
	CString sDefaultRulesetFN = ReadProgString( "files", "RulesetFile", NULL );
	CString sChkRulePathFile, sDefaultRulesetPathFile = sRulesetPath + sDefaultRulesetFN;
	bool bDefaultRulesetExists = (!sDefaultRulesetFN.IsEmpty() && FileExists( sDefaultRulesetPathFile ));
	bool bDefaultRulesetIsCA = false;
	CString sDfltRulesFNAllCaps = sDefaultRulesetFN;		sDfltRulesFNAllCaps.MakeUpper();
#ifdef UI_CARES
	bDefaultRulesetIsCA = (bDefaultRulesetExists && sDfltRulesFNAllCaps.Find( "CA RES" ) == 0);
#elif UI_CANRES
	bDefaultRulesetIsCA = (bDefaultRulesetExists && sDfltRulesFNAllCaps.Find( "CEC" ) == 0 && sDfltRulesFNAllCaps.Find( "NONRES" ) > 0);
#endif
	// note - no check to ensure that sDefaultRulesetFN is consistent w/ UI_PROGYEARxxxx

	bool bRulesetExists = false;
	CString sRulesetFN, sRuleFNGetError, sRulesetFNToSet;
	if (pszNewRulesetFile && strlen( pszNewRulesetFile ) > 0)
	{	sRulesetFN = pszNewRulesetFile;
		sChkRulePathFile = sRulesetPath + sRulesetFN;
		if (FileExists( sChkRulePathFile ))
			bRulesetExists = true;
		else	// shouldn't ever happen unless rule FN removed/misplaced following program initialization
		{	if (bDefaultRulesetExists)
			{	sRulesetFN = sDefaultRulesetFN;
				sRuleFNGetError.Format( "The selected ruleset '%s' was not found.\n\nPress OK to use the default ruleset '%s' in its place, or\nCancel to abort the file load.", sRulesetFN, sDefaultRulesetFN );
			}
			else
				sRuleFNGetError.Format( "Cannot load project:  Neither the selected ruleset '%s' nor the default ruleset '%s' was found.", sRulesetFN, sDefaultRulesetFN );
	}	}
	else
   {	// SAC - 3/3/98 - get ruleset filename from project file and load the ruleset
		sRulesetFN = BEMPX_GetRulesetFilenameFromProjectFile( sInputFile );
		sChkRulePathFile = sRulesetPath + sRulesetFN;
		if (!sRulesetFN.IsEmpty() && FileExists( sChkRulePathFile ))	// SAC 3/26/16 - add check for sRulesetFN being empty before continuing on
		{	if (bNormalRulesetUpdates && bDefaultRulesetIsCA && !bRuleSwitchingAllowed && sDefaultRulesetFN.CompareNoCase( sRulesetFN ) != 0)
			{	// CA is default ruleset, ruleset switching is toggled OFF and Project ruleset != program default ruleset
				int iProjRuleVint=0, iDfltRuleVint=0;
				int iRuleNumCharIdx = sRulesetFN.Find( " 20" ) + 1;
				if (iRuleNumCharIdx > 0)
					iProjRuleVint = atoi( sRulesetFN.Mid( iRuleNumCharIdx, 4 ) );
				iRuleNumCharIdx = sDefaultRulesetFN.Find( " 20" ) + 1;
				if (iRuleNumCharIdx > 0)
					iDfltRuleVint = atoi( sDefaultRulesetFN.Mid( iRuleNumCharIdx, 4 ) );
				if (iProjRuleVint < 1 || iDfltRuleVint < 1)
					sRuleFNGetError.Format( "Cannot load project:  Error determining the code vintage of project or default rulesets ('%s' & '%s' respectively).", sRulesetFN, sDefaultRulesetFN );
				else if (iProjRuleVint == iDfltRuleVint)
				{	ASSERT( FALSE );	// error ?? if code vints are ==, why aren't the ruleset filenames equivalent ?
					bRulesetExists = true;
				}
				else 	// should we ALLOW auto switching of rulesets going BACKWARD ?? -> if (iProjRuleVint < iDfltRuleVint)
				{	sRulesetFN = sDefaultRulesetFN;
					bRulesetExists = true;
					sRuleFNGetError.Format( "This version of CBECC cannot load the %d ruleset referenced by this project.\n\nPress OK to switch to the default ruleset (%d), or\nCancel to abort the file load.", iProjRuleVint, iDfltRuleVint );
			}	}
			else
				// NOT doing bNormalRulesetUpdates - meaning force load of Project ruleset
				// or default ruleset is not CA(lifornia) - so go ahead and allow any (existing) project ruleset
				// or ruleset switching is toggled on (so allow any existing project ruleset)
				// or project ruleset = default ruleset
				bRulesetExists = true;
		}
		else	// happens when the ruleset referenced in the project file doesn't exist (in the proper location) on the user's machine
		{	if (bDefaultRulesetExists)
			{	if (sRulesetFN.IsEmpty())
					sRuleFNGetError.Format( "There is no compliance ruleset referenced by this project.\n\nPress OK to use the default ruleset '%s' in its place, or\nCancel to abort the file load.", sDefaultRulesetFN );
				else
					sRuleFNGetError.Format( "The ruleset referenced by this project '%s' was not found.\n\nPress OK to use the default ruleset '%s' in its place, or\nCancel to abort the file load.", sRulesetFN, sDefaultRulesetFN );
				sRulesetFN = sDefaultRulesetFN;
			}
			else
				sRuleFNGetError.Format( "Cannot load project:  Neither the ruleset referenced by this project '%s' nor the default ruleset '%s' was found.", sRulesetFN, sDefaultRulesetFN );
//		if ( (sRulesetFN.IsEmpty() && bExtIsXML) ||
//				sRulesetFN.CompareNoCase("unknown") == 0 )	// SAC 5/30/14
//		{	// assume ruleset file is the default from the INI file
//			sRulesetFN = sDefaultRulesetFN;
//			sRulesetFNToSet = sRulesetFN;
//			if (sRulesetFN.IsEmpty() && bExtIsXML)
//				sRuleFNGetError.Format( "Warning:  'RulesetFilename' not defined in XML file header, defaulting to '%s' from INI file.  XML file:  '%s'", sRulesetFN, sInputFile );
//			else
//				sRuleFNGetError.Format( "Warning:  'RulesetFilename' not valid in project file, defaulting to '%s' from INI file.  Project file:  '%s'", sRulesetFN, sInputFile );
	}	}

// SAC 11/17/15 - code to force reset of ruleset in certain cases (CA ruleset in file & EnableRulesetSwitching OFF
	bool bRulesetBeingSwitched = false;
	BOOL bContinue = (sRuleFNGetError.IsEmpty());
	if (sRuleFNGetError.Find( "Press OK" ) > 0)
	{	bContinue = (AfxMessageBox( sRuleFNGetError, MB_OKCANCEL ) == IDOK);
		if (bContinue)
		{	bRulesetBeingSwitched = true;
			sRulesetFNToSet = sRulesetFN;
			sLogMsg.Format( "   Project switched to compliance ruleset:  %s", sRulesetFN );
	}	}
	else if (!bContinue)
		AfxMessageBox( sRuleFNGetError );
	if (!bContinue)
		return FALSE;

   BOOL bRulesetOK = LoadRuleset( sRulesetFN );

	if (!bRulesetOK)	// SAC 5/30/14 - if ruleset load unsuccessful, then make sure NOT to store default Rulesetfilename in place of bogus one following project file read
		sRulesetFNToSet.Empty();

	LoadTargetedInputRuleDebugInfo();	// SAC 11/22/14 - enable input rule eval targeted debug logging

//	   if ( BEMPX_ReadProjectFile( sInputFile, (eInterfaceMode == IM_INPUT ? BEMFM_INPUT : BEMFM_DETAIL), (bRestore != FALSE), FALSE /*bResultsOnly*/,
//												NULL /*pszLogFileExt*/, 0 /*iBEMProcIdx*/, elDBID_Proj_BEMVersion,  		// SAC 9/17/12 - added BEMVersion DBID
//												MAX_BEMBASE_DATA_SET_ERRORS, iaFailedBEMBaseDBIDs, NULL /*BEMStraightMap* pStraightMap*/, NULL /*BEMComponentMap* pCompMap*/,
//												NULL /*BEMPropertyMap* pPropMap*/, FALSE /*bSupressAllMsgBoxes*/, iaFailedBEMBaseObjIdxs, &saFailedBEMBaseData, (bLogProjectOpen) ) )
//	   {
//	      bRetVal = TRUE;
//		}
// SAC 1/27/14 - replaced above w/ the following call, moving more logic/processing into CompMgr
   bRestore;
	bool bKeepLogFileOpen = false;
	switch (ReadProgInt( "options", "LogWritingMode", 2 /*default*/ ))
	{	case  0 :	bKeepLogFileOpen = false;		break;
		case  1 :	bKeepLogFileOpen = true;		break;
		default :	bKeepLogFileOpen = (ebVerboseInputLogging || ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);		// SAC 5/19/14
						if (!bKeepLogFileOpen)
						{	CString sDebugRuleEvalCSV = ReadProgString( "options", "DebugRuleEvalCSV", "", TRUE );
							bKeepLogFileOpen = (!sDebugRuleEvalCSV.IsEmpty() && FileExists( sDebugRuleEvalCSV ));
						}	break;
	}
	QStringList saWarningsForUser;	// SAC 7/8/14 - added to track issues (not designated as read failures, but worthy of logging)
	int iLoadModelRetVal = CMX_LoadModel( NULL /*pszBEMBinPathFile*/, NULL /*pszRulesetPathFile*/, sInputFile, MAX_BEMBASE_DATA_SET_ERRORS, iaFailedBEMBaseDBIDs,
														true /*bSupressAllMsgBoxes*/, iaFailedBEMBaseObjIdxs, &saFailedBEMBaseData, (bLogProjectOpen), NULL /*pszLogPathFile*/,
														bKeepLogFileOpen, &saWarningsForUser, true /*bCalledFromUI*/ );	// SAC 5/1/14 - supress msgboxes		// SAC 5/19/14 - option to keep log file OPEN  - SAC 4/6/16 - added bCalledFromUI
	bRetVal = (iLoadModelRetVal == 0);

	ptime t2(microsec_clock::local_time());		// SAC 10/22/13
	time_duration td = t2-t1;

	if (!sLogMsg.IsEmpty())		// SAC 11/17/15
	   BEMPX_WriteLogFile( sLogMsg );

// SAC 9/5/14 - added logging of program name/version to log immediately following LoadModel
		CString sVersionString;
		GetProgramVersion( sVersionString );		ASSERT( !sVersionString.IsEmpty() );
		if (iLoadModelRetVal == 0)
			sLogMsg.Format( "   Model load successful into %s", sVersionString );
		else
			sLogMsg.Format( "   Model load failed (return code %d) into %s", iLoadModelRetVal, sVersionString );
	   BEMPX_WriteLogFile( sLogMsg );
	if (bLogProjectOpen)
	{	sLogMsg.Format( "   CComplianceUIDoc::OpenTheFile() - LoadRuleset() + ReadProjectFile() elapsed time: %s", to_simple_string(td).c_str() );
	   BEMPX_WriteLogFile( sLogMsg );
	}

	long lBEMBaseDBIDErrorToIgnore[2] = {-1,-1};	// SAC 8/15/14 - added to ensure that error in reading Proj:StandardsVersion (which is expected) will not be reported in the UI
	if ((bRulesetBeingSwitched || (pszNewRulesetFile && strlen( pszNewRulesetFile ) > 0 && lRulesetSymVal >= 0)) &&
			eiBDBCID_Proj > 0 && elDBID_Proj_Ruleset > 0 && BEMPX_GetNumObjects( (int) eiBDBCID_Proj ) > 0)
	{
		long lDBID_Proj_StdDesignBase = -1;
#ifdef UI_CARES
		// SAC 4/23/15 - if we loaded a new ruleset prior to reading the project file, then default certain properties that should be consistent w/ newly selected ruleset
		int iError;
		     lDBID_Proj_StdDesignBase    = BEMPX_GetDatabaseID( "StdDesignBase"   , eiBDBCID_Proj );		ASSERT( lDBID_Proj_StdDesignBase    > 0 );
		long lDBID_Proj_StandardsVersion = BEMPX_GetDatabaseID( "StandardsVersion", eiBDBCID_Proj );		ASSERT( lDBID_Proj_StandardsVersion > 0 );
		if (lDBID_Proj_StdDesignBase > 0)
			BEMPX_DefaultProperty( lDBID_Proj_StdDesignBase, iError );
		if (lDBID_Proj_StandardsVersion > 0)
			BEMPX_DefaultProperty( lDBID_Proj_StandardsVersion, iError );
#elif UI_CANRES
		int iError;
		long lDBID_Proj_StdsVersion = BEMPX_GetDatabaseID( "StdsVersion", eiBDBCID_Proj );		ASSERT( lDBID_Proj_StdsVersion > 0 );
		if (lDBID_Proj_StdsVersion > 0)
			BEMPX_DefaultProperty( lDBID_Proj_StdsVersion, iError );
#endif
		// SAC 8/14/14 - moved from MenuRulesetSelection()
		BEMPX_SetBEMData( elDBID_Proj_Ruleset, BEMP_Sym, (void*) &lRulesetSymVal );  // must be UserDefined or won't stick!...  , BEMO_User, -1, BEMS_ProgDefault );	// SAC 4/23/15 - modified to specify ProgDefault as data status to avoid having it written to project files
		lBEMBaseDBIDErrorToIgnore[0] = elDBID_Proj_StdsVersion;
		lBEMBaseDBIDErrorToIgnore[1] = lDBID_Proj_StdDesignBase;
		SetDataModifiedFlag( TRUE );
	}

	int iNumBEMBaseErrors = 0, iNumBEMBaseErrMsgs = 0;
	CString sRdProjErr;
   for (i=0; i<MAX_BEMBASE_DATA_SET_ERRORS; i++)
	{	if (iaFailedBEMBaseDBIDs[i] > 0 && iaFailedBEMBaseDBIDs[i] != lBEMBaseDBIDErrorToIgnore[0] && iaFailedBEMBaseDBIDs[i] != lBEMBaseDBIDErrorToIgnore[1])
			iNumBEMBaseErrors++;
		if (saFailedBEMBaseData.size() > i && saFailedBEMBaseData[i].length() > 3)
			iNumBEMBaseErrMsgs++;
	}
	int iNumErrsInclInRdProjErr = 0;		CString sLoadModelErr;
	if (iNumBEMBaseErrors > 0 || iLoadModelRetVal != 0)
	{	switch (iLoadModelRetVal)
		{	case  1 :	sLoadModelErr = "Input file not found";													break;
			case  2 :	sLoadModelErr = "Building energy data model (BEMBin) file not found";			break;
			case  3 :	sLoadModelErr = "Ruleset file not found";													break;
			case  4 :	sLoadModelErr = "Initialization of building energy model database failed";		break;
			case  5 :	sLoadModelErr = "Unable to load ruleset file";											break;
			case  6 :	sLoadModelErr = "Unable to read/parse building energy model file";				break;
			default :	sLoadModelErr = "(unrecognized error code)";												break;
		}
		if (iNumBEMBaseErrors > 0 && iLoadModelRetVal != 0)
			sRdProjErr.Format( "%d error(s) encountered (return code %d: %s) reading project file:  %s", iNumBEMBaseErrors, iLoadModelRetVal, sLoadModelErr, sInputFile );
		else if (iNumBEMBaseErrors > 0)
			sRdProjErr.Format( "%d error(s) encountered reading project file:  %s", iNumBEMBaseErrors, sInputFile );
		else
			sRdProjErr.Format( "Error(s) encountered (return code %d: %s) reading project file:  %s", iLoadModelRetVal, sLoadModelErr, sInputFile );
	   BEMPX_WriteLogFile( sRdProjErr );

	// SAC 6/30/16 - included echo of first 6 error messages in the string presented to the user in a messagebox
		int iMaxErrsToIncl = 6;
		int iErrMsgIdx=-1, iFindIdx;
		while (iNumErrsInclInRdProjErr < iMaxErrsToIncl && ++iErrMsgIdx < saFailedBEMBaseData.size())
			if (saFailedBEMBaseData[iErrMsgIdx].length() > 3)
			{	iNumErrsInclInRdProjErr++;
				if ((iFindIdx = saFailedBEMBaseData[iErrMsgIdx].indexOf( "ERROR - reading file: " )) >= 0)
					sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx].right( saFailedBEMBaseData[iErrMsgIdx].length()-iFindIdx-22 ).toLatin1().constData() );
				else if ((iFindIdx = saFailedBEMBaseData[iErrMsgIdx].indexOf( "ERROR - " )) >= 0)
					sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx].right( saFailedBEMBaseData[iErrMsgIdx].length()-iFindIdx-8 ).toLatin1().constData() );
				else
					sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx].toLatin1().constData() );
				sRdProjErr += sLoadModelErr;
			}

		CString sLogFN = BEMPX_GetLogFilename();
		if (!sLogFN.IsEmpty())
		{	sRdProjErr += "\n\nFor more information, refer to the project log file";
			if (iNumErrsInclInRdProjErr > 0)
			{	if (iNumErrsInclInRdProjErr < iNumBEMBaseErrMsgs)
					sLoadModelErr.Format( " to review the above (and %d additional) error messages", iNumBEMBaseErrMsgs-iNumErrsInclInRdProjErr );
				else
					sLoadModelErr = " which echoes the above listed error(s)";
				sRdProjErr += sLoadModelErr;
			}
			sRdProjErr += ":  ";
			sRdProjErr += sLogFN;
		}
      // AfxMessageBox( sRdProjErr );  - moved down to ensure that ALL messages (incl. new warnings) are written before user alerted to log message errors
	}
	bool bUIActive = (BEMPX_GetUIActiveFlag());
	if (saWarningsForUser.size() > 0)	// SAC 7/8/14 - log file-read issues not designated as failures, but worthy of logging
	{	bool bPrevErrsLogged = (!sRdProjErr.IsEmpty());
		if (bPrevErrsLogged)
			sRdProjErr += "\n";
		int iMaxWarnMsgs = (bPrevErrsLogged ? 6-iNumErrsInclInRdProjErr : 8);
		for (int iFRWIdx=0; iFRWIdx < saWarningsForUser.size(); iFRWIdx++)
		{	VERIFY( BEMPX_WriteLogFile( saWarningsForUser[iFRWIdx].toLatin1().constData(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
			sLoadModelErr.Empty();
			if (iFRWIdx == 0 && iMaxWarnMsgs <= 0)
				sLoadModelErr.Format( "\n%d warning message(s) also written to project log file.", saWarningsForUser.size() );
			else if (iFRWIdx == iMaxWarnMsgs)
				sLoadModelErr = "\n(additional warning message(s) written to project log file)";
			else if (iFRWIdx < iMaxWarnMsgs)
				sLoadModelErr.Format( "\n%s", saWarningsForUser[iFRWIdx].toLatin1().constData() );
			if (!sLoadModelErr.IsEmpty())
				sRdProjErr += sLoadModelErr;
		}
		if (!bPrevErrsLogged)
		{	if (bUIActive)
		      AfxMessageBox( sRdProjErr );
			sRdProjErr.Empty();
	}	}
	if (!sRdProjErr.IsEmpty() && bUIActive)		// SAC 7/8/14 - moved down here to ensure that ALL messages (incl. new warnings) are written before user alerted to log message errors
		AfxMessageBox( sRdProjErr );

// SAC 6/5/13 - moved all this stuff OUTSIDE the above if statement, so it gets evaluated even if errors occurred during project file read
	//	if (!sRuleFNGetError.IsEmpty())		- SAC 11/17/15 - this string is now a user prompt/message, not a log message
	//	   BEMPX_WriteLogFile( sRuleFNGetError );

      SetPathName( sInputFile );
      SetModifiedFlag( FALSE );

		if (!sRulesetFNToSet.IsEmpty())	// SAC 5/30/14
		{	BEMPX_SetRulesetFilename( sRulesetFNToSet );
			long lRuleFileDBID = BEMPX_GetDatabaseID( "Proj:RuleFile" );
			if (lRuleFileDBID <= 0)
				lRuleFileDBID = BEMPX_GetDatabaseID( "Project:RuleFile" );   // try alternative spelling
			if (lRuleFileDBID > 0)
				BEMPX_SetBEMData( lRuleFileDBID, BEMP_Str, (void*) ((const char*) sRulesetFNToSet), BEMO_User, 0, BEMS_ProgDefault );
			SetModifiedFlag( TRUE );
		}

	// SAC 5/11/14 - added code to reset screen data - which in turn will pull all tooltips from ruleset into screen data
      CWnd* pMainWnd = AfxGetMainWnd();
		if (pMainWnd)
		{	if (!CheckAndDefaultModel( sRdProjErr.IsEmpty(), bWriteToLog ))		// SAC 9/5/14 - MOVED code that performs model checking & defaulting to separate routine to ensure consistent operation for models that are opened via command line specification
				bRetVal = FALSE;
		}

	return bRetVal;
}


// SAC 9/5/14 - MOVED code from OpenTheFile() to here to ensure consistent checking and defaulting for models that are opened via command line specification
BOOL CComplianceUIDoc::CheckAndDefaultModel( BOOL bCheckModel, BOOL bWriteToLog )
{	BOOL bRetVal = TRUE;
	bool bLogProjectOpen = (ReadProgInt( "options", "LogProjectOpen", 0) > 0);
	CString sLogMsg;
	ptime t1, t2;
	time_duration td;

      CWnd* pMainWnd = AfxGetMainWnd();
		if (pMainWnd)
			pMainWnd->SendMessage( WM_LOADSCREENFILES );

	// SAC 2/27/14 - added RE-load of BEM CIDs & DBIDs to account for special conditions, such as UI_CANRES 2D/simplified geometry
		InitBEMDBIDs();

      if (pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)) &&
				bCheckModel && ReadProgInt( "options", "BypassInputChecks", 0 ) == 0)
			((CMainFrame*)pMainWnd)->CheckBuildingModel( FALSE /*bReportModelOK*/, FALSE /*bPerformRangeChecks*/ ) ;

// SAC 4/14/13 - added code to address access to Research mode analysis
// SAC 10/7/13 - modified storage of these flags to be default so that they are not stored in project (RIBD) files
#ifdef UI_CARES
	   long lEnableResearchMode = ReadProgInt( "options", "EnableResearchMode", 0 );
		long lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_EnableResearchMode > 0 );
		long lDBID_Proj_AnalysisType       = BEMPX_GetDatabaseID( "AnalysisType"      , BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_AnalysisType       > 0 );
		if (lDBID_Proj_EnableResearchMode > 0 && lDBID_Proj_AnalysisType > 0)
		{	long lERM, lAT;
			if (!BEMPX_SetDataInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ))
				lERM = -1;
			if (!BEMPX_SetDataInteger( lDBID_Proj_AnalysisType      , lAT , -1 ))
				lAT  = -1;
	//		if (lEnableResearchMode == 0 && lERM > 0.5 && lAT == 0)
	//		{	// This file was last SAVED IN RESEARCH MODE, but current INI file does not include research mode enabling setting
	//	      AfxMessageBox( "Research mode is selected in this project file but not available in the current software installation." );  // then do what ??
	//		}
	// SAC 2/4/16 - retain 
			if (lEnableResearchMode == 0 && lERM < 0.5 && lAT == 0)
			{	// This file was last SAVED IN RESEARCH MODE, but current INI file does not include research mode enabling setting
		      AfxMessageBox( "Research mode is selected in this project file but not available in the current software installation." );  // then do what ??
		   }
			else if (lERM < -0.5)	// SAC 2/4/16 - only reset EnableResearchMode to INI setting if NOT specified in input file
		      BEMPX_SetBEMData( lDBID_Proj_EnableResearchMode, BEMP_Int, (void*) &lEnableResearchMode, BEMO_User, -1, BEMS_ProgDefault );
		}
	// SAC 10/7/13 - additional flags to toggle on/off INI-controlled features
	// SAC 8/7/14 - change INI default for EnableVarFlowOAV & EnableFixedFlowOAV from 0 -> 1
		long lEnableRptIncFile    = ReadProgInt( "options", "EnableRptIncFile"  , 0 ),	lDBID_Proj_EnableRptIncFile   = BEMPX_GetDatabaseID( "EnableRptIncFile"  , BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_EnableRptIncFile   > 0 );
		long lEnableVarFlowOAV    = ReadProgInt( "options", "EnableVarFlowOAV"  , 1 ),	lDBID_Proj_EnableVarFlowOAV   = BEMPX_GetDatabaseID( "EnableVarFlowOAV"  , BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_EnableVarFlowOAV   > 0 );
		long lEnableFixedFlowOAV  = ReadProgInt( "options", "EnableFixedFlowOAV", 1 ),	lDBID_Proj_EnableFixedFlowOAV = BEMPX_GetDatabaseID( "EnableFixedFlowOAV", BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_EnableFixedFlowOAV > 0 );
		long lBypassRuleLimits    = ReadProgInt( "options", "BypassRuleLimits"  , 0 ),	lDBID_Proj_BypassRuleLimits   = BEMPX_GetDatabaseID( "BypassRuleLimits"  , BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_BypassRuleLimits   > 0 );  // SAC 6/2/14 - added
		if (lEnableRptIncFile > 0 &&		lDBID_Proj_EnableRptIncFile   > 0)
	      				BEMPX_SetBEMData( lDBID_Proj_EnableRptIncFile  , BEMP_Int, (void*) &lEnableRptIncFile  , BEMO_User, -1, BEMS_ProgDefault );
		if (lEnableVarFlowOAV > 0 &&		lDBID_Proj_EnableVarFlowOAV   > 0)
	      				BEMPX_SetBEMData( lDBID_Proj_EnableVarFlowOAV  , BEMP_Int, (void*) &lEnableVarFlowOAV  , BEMO_User, -1, BEMS_ProgDefault );
		if (lEnableFixedFlowOAV > 0 &&	lDBID_Proj_EnableFixedFlowOAV > 0)
	      				BEMPX_SetBEMData( lDBID_Proj_EnableFixedFlowOAV, BEMP_Int, (void*) &lEnableFixedFlowOAV, BEMO_User, -1, BEMS_ProgDefault );
		if (lBypassRuleLimits > 0 &&	   lDBID_Proj_BypassRuleLimits > 0)
	      				BEMPX_SetBEMData( lDBID_Proj_BypassRuleLimits  , BEMP_Int, (void*) &lBypassRuleLimits  , BEMO_User, -1, BEMS_ProgDefault );

		long lSimSpeedOption = ReadProgInt( "options", "SimSpeedOption", -1 ),		lDBID_Proj_SimSpeedOption = BEMPX_GetDatabaseID( "SimSpeedOption", BEMPX_GetDBComponentID( "Proj" ) );			ASSERT( lDBID_Proj_SimSpeedOption > 0 );  // SAC 1/14/15 - added
		if (lSimSpeedOption >= 0 &&	lDBID_Proj_SimSpeedOption > 0)
	   	BEMPX_SetBEMData( lDBID_Proj_SimSpeedOption, BEMP_Int, (void*) &lSimSpeedOption, BEMO_User, -1, BEMS_ProgDefault );

#endif

      if (pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
      {
         if (eInterfaceMode == IM_INPUT)  // execute compliance rulelist #1
         {
								if (bLogProjectOpen)     // SAC 10/22/13
								{	t1 = microsec_clock::local_time();
					   			BEMPX_SetDurationMark( 4 );
								}
				pMainWnd->SendMessage( WM_EVALPROPOSED, (!bWriteToLog) );
								if (bLogProjectOpen)     // SAC 10/22/13
								{	t2 = microsec_clock::local_time();
									td = t2-t1;
									sLogMsg.Format( "   CComplianceUIDoc::CheckAndDefaultModel() - Project defaulting round 1 elapsed time: %s", to_simple_string(td).c_str() );
								   BEMPX_WriteLogFile( sLogMsg );
					   			BEMPX_SetDurationMark( 4 );
								}
         	pMainWnd->SendMessage( WM_EVALPROPOSED, (!bWriteToLog) );	// SAC 4/16/13 - triple eval DEFAULT rules to overcome rule order issues -- TEMPORARILY - TO DO
								if (bLogProjectOpen)     // SAC 10/22/13
								{	t1 = microsec_clock::local_time();
									td = t1-t2;
									sLogMsg.Format( "   CComplianceUIDoc::CheckAndDefaultModel() - Project defaulting round 2 elapsed time: %s", to_simple_string(td).c_str() );
								   BEMPX_WriteLogFile( sLogMsg );
					   			BEMPX_SetDurationMark( 4 );
								}
         	pMainWnd->SendMessage( WM_EVALPROPOSED, (!bWriteToLog) );
								if (bLogProjectOpen)     // SAC 10/22/13
								{	t2 = microsec_clock::local_time();
									td = t2-t1;
									sLogMsg.Format( "   CComplianceUIDoc::CheckAndDefaultModel() - Project defaulting round 3 elapsed time: %s", to_simple_string(td).c_str() );
								   BEMPX_WriteLogFile( sLogMsg );
								}
			}

			((CMainFrame*)pMainWnd)->SetStatusBarStrings( "", 2 );		// SAC 10/29/15 - display ruleset ID in third status bar pane

         CMainView* pMainView = (CMainView*) ((CMainFrame*)pMainWnd)->m_wndSplitter.GetPane(0,0);
         if (pMainView != NULL)            // update main view's tree control(s)
         {
#ifdef UI_CARES
				pMainView->SendMessage( WM_UPDATETREE, 0, elDBID_Proj_IsMultiFamily );		// SAC 7/29/16 - ensure access/non-access to DwellUnit* objects based on whether model is multifamily
#endif
            pMainView->SendMessage( WM_DISPLAYDATA );

            CView* pLibView = (CView*) ((CMainFrame*)pMainWnd)->m_wndSplitter.GetPane(1,0);
            if (pLibView != NULL)            // update main view's tree control(s)
               pLibView->SendMessage( WM_POPLIBTREE, eiCurrentTab );
         }
      }
      else
         // even if frame is not available, still evaluate proposed rulelist
         CMX_EvaluateRuleset( esDataModRulelist, ebVerboseInputLogging, FALSE, ebVerboseInputLogging, NULL, NULL, NULL, epInpRuleDebugInfo );  // epszRLs[0] );

		BEMPX_RefreshLogFile();	// SAC 5/19/14

      eiCurAnalysisStep = AS_None;
		CString sInputFile = GetPathName();

	// SAC 7/16/12 - added code to store *IBD & XML details files following File Open operation
		if (ReadProgInt( "options", "StoreBEMDetails", 0) > 0 && sInputFile.ReverseFind('.') > 0)
		{  // SAC 6/26/13 - added code to PREVENT ModDate from getting incremented each time project file is written in non-input mode
			long lModDate;
			if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
				lModDate = -1;

			CString sDbgFileName = sInputFile.Left( sInputFile.ReverseFind('.') );
			sDbgFileName += " - post open.ibd-Detail";
			BEMPX_WriteProjectFile( sDbgFileName, BEMFM_DETAIL /*FALSE*/, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
												false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lModDate, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );

			CString sXMLFileName = sInputFile.Left( sInputFile.ReverseFind('.') );
			sXMLFileName += " - post open.xml";
			VERIFY( BEMPX_WriteProjectFile( sXMLFileName, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, BEMFT_XML /*iFileType*/,
														false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lModDate, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ ) );
		}


//	else	// SAC 10/29/12 - added else to ensure tree view is updated even if errors occurred during project open
//	{  CWnd* pMainWnd = AfxGetMainWnd();
//      if ( (pMainWnd != NULL) && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) )
//      {
//         //if (eInterfaceMode == IM_INPUT)  // execute compliance rulelist #1
//         //   pMainWnd->SendMessage( WM_EVALPROPOSED, (!bWriteToLog) );
//
//         CMainView* pMainView = (CMainView*) ((CMainFrame*)pMainWnd)->m_wndSplitter.GetPane(0,0);
//         if (pMainView != NULL)            // update main view's tree control(s)
//         {
//            pMainView->SendMessage( WM_DISPLAYDATA );
//
//            CView* pLibView = (CView*) ((CMainFrame*)pMainWnd)->m_wndSplitter.GetPane(1,0);
//            if (pLibView != NULL)            // update main view's tree control(s)
//               pLibView->SendMessage( WM_POPLIBTREE, eiCurrentTab );
//         }
//      }
//	}

   return bRetVal;
}
