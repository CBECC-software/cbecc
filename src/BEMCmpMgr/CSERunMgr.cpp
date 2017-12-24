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
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "exec-stream.h"
#include "CSERunMgr.h"
#include "memLkRpt.h"

const char* pszRunAbbrev_u  = "u";
const char* pszRunAbbrev_pmf  = "pmf";  
const char* pszRunAbbrev_pmfN = "pmf-N";
const char* pszRunAbbrev_pmfE = "pmf-E";
const char* pszRunAbbrev_pmfS = "pmf-S";
const char* pszRunAbbrev_pmfW = "pmf-W";
const char* pszRunAbbrev_p  = "p";
const char* pszRunAbbrev_pN = "p-N";
const char* pszRunAbbrev_pE = "p-E";
const char* pszRunAbbrev_pS = "p-S";
const char* pszRunAbbrev_pW = "p-W";
const char* pszRunAbbrev_s    = "s";    
const char* pszRunAbbrev_pfx  = "pfx";  
const char* pszRunAbbrev_pfxN = "pfx-N";
const char* pszRunAbbrev_pfxE = "pfx-E";
const char* pszRunAbbrev_pfxS = "pfx-S";
const char* pszRunAbbrev_pfxW = "pfx-W";
const char* pszRunAbbrev_dr   = "dr";   


int StringInArray( QVector<QString>& saStrs, QString& sStr )
{	int iSize = (int) saStrs.size();
	for (int i=0; i<iSize; i++)
	{	if (saStrs[i].compare( sStr, Qt::CaseInsensitive ) == 0)
			return i;
	}
	return -1;
}

CSERun::CSERun() :
	m_lRunNumber( 0),
	m_bLastRun( FALSE),
	m_bIsStdDesign( FALSE),
	m_iExitCode( 0),
	m_pES( NULL)
{
	m_sTDVFName.clear();		// SAC 4/16/17
}

CSERun::~CSERun()
{
	delete m_pES;
}

CSERunMgr::CSERunMgr(
	QString sCSEexe,
	QString sCSEWthr,
	QString sModelPathOnly,
	QString sModelFileOnlyNoExt,
	QString sProcessPath,
	bool bFullComplianceAnalysis,
	bool bInitHourlyResults,
	long lAllOrientations,
	long lAnalysisType,
	long lStdDesignBaseID,
	long lDesignRatingRunID,
	bool bVerbose,
	bool bStoreBEMProcDetails,
	bool bPerformSimulations,
	bool bBypassCSE,
	bool bSilent,
	void* pCompRuleDebugInfo,
	const char* pszUIVersionString,
	int iSimReportOpt,
	int iSimErrorOpt,
	long lPropMixedFuelRunReqd,
	long lPropFlexRunReqd,
	int iNumRuns) :

	m_sCSEexe( sCSEexe),
	m_sCSEWthr( sCSEWthr),
	m_sModelPathOnly( sModelPathOnly),
	m_sModelFileOnlyNoExt( sModelFileOnlyNoExt),
	m_sProcessPath( sProcessPath),
	m_bFullComplianceAnalysis( bFullComplianceAnalysis),
	m_bInitHourlyResults( bInitHourlyResults),
	m_lAllOrientations( lAllOrientations),
	m_lAnalysisType( lAnalysisType),
	m_lStdDesignBaseID( lStdDesignBaseID),
	m_lDesignRatingRunID( lDesignRatingRunID),
	m_bVerbose( bVerbose),
	m_bStoreBEMProcDetails( bStoreBEMProcDetails),
	m_bPerformSimulations( bPerformSimulations),
	m_bBypassCSE( bBypassCSE),
	m_bSilent( bSilent),
	m_pCompRuleDebugInfo( pCompRuleDebugInfo),
	m_pszUIVersionString( pszUIVersionString),
	m_iError( 0),
	m_iSimReportOpt(iSimReportOpt),
	m_iSimErrorOpt(iSimErrorOpt),
	m_lPropMixedFuelRunReqd(lPropMixedFuelRunReqd),
	m_lPropFlexRunReqd(lPropFlexRunReqd),
	m_iNumOpenGLErrors(0),
	m_iNumProgressRuns(-1)
{
	if (iNumRuns > 0)
		m_iNumRuns = iNumRuns;
	else
	{	m_iNumRuns = (bFullComplianceAnalysis ? (lAllOrientations > 0 ? 5 : 2) : 1);
		if (m_lPropFlexRunReqd > 0)		// SAC 8/3/17
			m_iNumRuns++;
		if (lAnalysisType > 0 /*bFullComplianceAnalysis*/ && m_lDesignRatingRunID > 0)		// SAC 3/27/15
		{	m_iNumRuns++;
			if (m_lPropMixedFuelRunReqd > 0)		// SAC 4/5/17
				m_iNumRuns++;
	}	}
}		// CSERunMgr::CSERunMgr

CSERunMgr::~CSERunMgr()
{	DeleteRuns();
}

void CSERunMgr::DeleteRuns()
{	CSERun* pCSERun = NULL;
	while (!m_vCSERun.empty())
	{	pCSERun = m_vCSERun.back();
		m_vCSERun.pop_back();
		delete pCSERun;
	}
}

static int ExecuteNow( CSERunMgr* pRunMgr, QString sEXEFN, QString sEXEParams )
{
			int iExitCode = -99;
			bool bRunOK = true;
			exec_stream_t* pES=NULL;
			try
			{	
				pES = new exec_stream_t( sEXEFN.toLocal8Bit().constData(), sEXEParams.toLocal8Bit().constData(), CREATE_NO_WINDOW );
				//cseRun.SetExecStream( pES);
			}
			catch(exec_stream_t::error_t &e)
			{	std::string sLogMsg=e.what();
				BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
				bRunOK = false;
			}
			if (pES && bRunOK)
			{
				bool bEXEDone=false, bFirstException=true;
				while (!bEXEDone)
				{	try
					{	if (pES->running())
						{	pRunMgr->ProcessRunOutput( pES, 0/*iRun*/, bFirstException);
							Sleep(100);
						}
						else
						{	bEXEDone = true;
							bool bFirstExceptionX=true;
							while( pRunMgr->ProcessRunOutput( pES, 0/*iRun*/, bFirstExceptionX));
							pES->close();
							iExitCode = pES->exit_code();
						}
					}
		//			{	if (pES->running())
		//				{	//ProcessRunOutput( pES, iRun, bFirstException);
		//					Sleep(100);
		//				}
		//				else
		//				{	bEXEDone = true;
		//					//while( ProcessRunOutput( pES, iRun, bFirstExceptionX));
		//					pES->close();
		//					iExitCode = pES->exit_code();
		//				}
		//			}
					catch(exec_stream_t::error_t &e2)
					{	if (bFirstException)
						{	std::string sLogMsg=e2.what();
							BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
							bFirstException = false;
						}
				}	}
			}
			if (pES)
				delete pES;
					//      QString sMsg = QString( "BTPreRun CSE exit code: %1" ).arg( QString::number(iExitCode) );
					//      BEMMessageBox( sMsg );

	return iExitCode;
}


int CSERunMgr::SetupRun(
	int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile /*=true*/,		// SAC 4/29/15 - add argument to DISABLE report include files
	const char* pszRunAbbrev /*=NULL*/ )
{
	int iRetVal = 0;
	CSERun* pCSERun = new CSERun;
	m_vCSERun.push_back( pCSERun);
	QString sMsg, sLogMsg;
	BOOL bLastRun = (iRunIdx == (m_iNumRuns-1));
	BOOL bIsStdDesign = (iRunType == CRM_StdDesign);	// SAC 3/27/15 - was:  (iRunIdx > 0 && bLastRun);  // SAC 7/3/13 - consolidated some logic to identify 
	pCSERun->SetRunType( iRunType);							// SAC 3/27/15
	pCSERun->SetLastRun( bLastRun);
	pCSERun->SetIsStdDesign( bIsStdDesign);
	if (m_bStoreBEMProcDetails)	// SAC 1/20/13 - added export of additional "detail" file to help isolate unnecessary object creation issues
	{	QString sDbgFileName;
		sDbgFileName = QString( "%1%2 - run %3.ibd-b4Evals" ).arg( m_sProcessPath, m_sModelFileOnlyNoExt, QString::number(iRunIdx+1) );
		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
	}

	long lRunNumber = (iRunType == CRM_User ? 0 : iRunIdx+1 );		// SAC 4/21/15 - mods to set RunNumber in source code - necessary since we are now starting EACH run's BEMComp database w/ the Proposed Model's
	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunNumber" ), BEMP_Int, (void*) &lRunNumber );
	if (pszRunAbbrev && strlen( pszRunAbbrev ) > 0)
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunAbbrev" ), BEMP_Str, (void*) pszRunAbbrev );

	QString sOrientLtr, sOrientName;
	if (iRunType >= CRM_PropMixedFuel && iRunType <= CRM_WPropMixedFuel)		// SAC 12/20/17 - reorder if statement to be consistent w/ new PMF run order
	{	iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropCompError, "ProposedCompliance", m_bVerbose, m_pCompRuleDebugInfo );
		if (iRetVal == 0)
			iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalSetupPMFError, "SetupRun_ProposedMixedFuel", m_bVerbose, m_pCompRuleDebugInfo );	// SAC 4/5/17
	}
	else if (iRunType < CRM_StdDesign /*!bIsStdDesign*/ && m_lAnalysisType > 0)
		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropCompError, "ProposedCompliance", m_bVerbose, m_pCompRuleDebugInfo );
	else if (iRunType >= CRM_PropFlex && iRunType <= CRM_WPropFlex)
		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalSetupPFlxError, "SetupRun_ProposedFlexibility", m_bVerbose, m_pCompRuleDebugInfo );	// SAC 8/3/17
	else if (iRunType >= CRM_StdDesign)	// SAC 3/27/15 - was:  bIsStdDesign)
	{	// SAC 3/27/15 - SET 
		if (iRunType == CRM_DesignRating)
      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:StdDesignBase" ), BEMP_Int, (void*) &m_lDesignRatingRunID );
		// may at some point need to specifically set  StandardsVersion  if/when multiple standard vintages is supported by a single ruleset

		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalStdConvError, "BudgetConversion", m_bVerbose, m_pCompRuleDebugInfo );
	}
	if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
		iRetVal = BEMAnal_CECRes_RuleProcAbort;

//	long lRunNumber;
	QString sRunID, sRunIDProcFile, sRunAbbrev;
//	BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunNumber"     ),  lRunNumber     );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunID"         ),  sRunID         );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunIDProcFile" ),  sRunIDProcFile );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunAbbrev"     ),  sRunAbbrev     );

	pCSERun->SetRunNumber( lRunNumber);
	pCSERun->SetRunID( sRunID);
	pCSERun->SetRunIDProcFile( sRunIDProcFile);
	pCSERun->SetRunAbbrev( sRunAbbrev);

	if (iRetVal == 0 && iRunType >= CRM_NOrientProp && iRunType <= CRM_WOrientProp)		// SAC 3/27/15 - was:  m_bFullComplianceAnalysis && m_lAllOrientations > 0 && !bLastRun)
	{  // Set Orientation for this particular run
		BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:OrientAbbrev" ),  sOrientLtr  );
		BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:OrientName"   ),  sOrientName );
	}

	QString sMissing;
	if (sRunID.isEmpty())
		sMissing += "RunID, ";
	if (sRunAbbrev.isEmpty())
		sMissing += "RunAbbrev ";
	if (iRetVal == 0 && !sMissing.isEmpty())
	{	sMissing = sMissing.left( sMissing.length()-2 );
		sErrorMsg = "ERROR:  The following Proj properties not set:" + sMissing;
		iRetVal = BEMAnal_CECRes_GetReqdDataError;
	}
	assert( iRunIdx == (lRunNumber-1) );

	if (iRetVal == 0 && (m_sProcessPath.length() + m_sModelFileOnlyNoExt.length() + sRunIDProcFile.length() + 12) > _MAX_PATH)
	{	sErrorMsg = QString( "ERROR:  CSE processing path too long:  %1%2%3.*" ).arg( m_sProcessPath, m_sModelFileOnlyNoExt, sRunIDProcFile );
		iRetVal = BEMAnal_CECRes_ProcPathTooLong;
	}

	if (iRetVal == 0 && iRunIdx == 0 && m_bInitHourlyResults)  // only initialize hourly results for first simulation??
		BEMPX_InitializeHourlyResults();

	QString sProjFileAlone = m_sModelFileOnlyNoExt + sRunIDProcFile;
	if (iRetVal == 0)
	{	// try evaluating prop & postprop rulelists EVERY time
		iRetVal = LocalEvaluateRuleset(		sErrorMsg, BEMAnal_CECRes_EvalPropInp3Error, "ProposedInput", m_bVerbose, m_pCompRuleDebugInfo );		// generic project defaulting
		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		// ??? perform simulation check on BUDGET model as well ???
		if (iRetVal == 0) // && iRunIdx == 0)
			iRetVal = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalSimChkError, "ProposedModelSimulationCheck", m_bVerbose, m_pCompRuleDebugInfo );		// check user input model for simulation-related errors
		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		if (iRetVal == 0)
			iRetVal = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalPostPropError, "PostProposedInput", m_bVerbose, m_pCompRuleDebugInfo );		// setup for Proposed run
		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		if (iRetVal == 0)
			iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalSimPrepError, "CSE_SimulationPrep", m_bVerbose, m_pCompRuleDebugInfo );
		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		BEMPX_RefreshLogFile();	// SAC 5/19/14
		
		if (iRetVal == 0 && iRunIdx == 0)  // Store various software & ruleset versions prior to first run - SAC 12/19/12
		{	// SAC 4/24/15 - now done PRIOR to CSE run setup
			//if (m_pszUIVersionString && strlen( m_pszUIVersionString ) > 0)
			//	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), BEMP_Str, (void*) m_pszUIVersionString );
			//else
			//	BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), m_iError );

			QString sVerTemp, sVerStr;
			BEMPX_GetRulesetID( sVerTemp, sVerStr );
			if (!sVerStr.isEmpty())
				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RulesetVersion" ), BEMP_QStr, (void*) &sVerStr );
			else
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:RulesetVersion" ), m_iError );

			QString sCSEVersion = GetVersionInfo();
			if (!sCSEVersion.isEmpty())
				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ), BEMP_QStr, (void*) &sCSEVersion );
			else
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ), m_iError );

			// SAC 1/8/13 - DHW engine version stored to BEMBase DURING DHW simulation (immediately following the ...Init() call)
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:SecSimEngingVer" ), m_iError );
		}

		// Purge user-defined non-parent/child components which are not referenced  - SAC 1/20/13 - added to prevent simulation of objects that are not referenced in the building model
		// Purge performed HERE, before objects are cross-referenced (Cons <-> cseCONS & Mat <-> cseMATERIAL), w/ those cross-references preventing any useful purging
		BEMPX_PurgeUnreferencedComponents();

		QString sOutFiles[CSERun::OutFileCOUNT];
		if (iRetVal == 0)
		{	sOutFiles[CSERun::OutFileCSV] = m_sProcessPath + sProjFileAlone + ".csv";
			sOutFiles[CSERun::OutFileREP] = m_sProcessPath + sProjFileAlone + ".rep";
			sOutFiles[CSERun::OutFileERR] = m_sProcessPath + sProjFileAlone + ".err";
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileCSV], CSERun::OutFileCSV);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileREP], CSERun::OutFileREP);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileERR], CSERun::OutFileERR);

			static const char* pszOutFileDescs[] = { "CSV output", "REP output", "Error output" };
			int i=0;
			for (; (i<CSERun::OutFileCOUNT && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
							"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
								 "(once the file is closed), or \n'Abort' to abort the analysis." ).arg( pszOutFileDescs[i], sOutFiles[i] );
				if (!OKToWriteOrDeleteFile( sOutFiles[i].toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
					iRetVal = BEMAnal_CECRes_SimOutWriteError;
				}
				// code to DELETE existing results files prior to simulation
				else if (FileExists( sOutFiles[i].toLocal8Bit().constData() ))
					DeleteFile( sOutFiles[i].toLocal8Bit().constData() );
			}
		}
		
		QString sRptIncFile, sProcRptIncFile, sZoneIncFile, sProcZoneIncFile;		QVector<QString> saZoneIncFiles, saProcZoneIncFiles, saZoneNameIncFiles;
		if (iRetVal == 0)
		{	// Write Report Include file statement
			long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:ReportIncludeFile" );
			if (lProjReportIncludeFileDBID > 0)
				BEMPX_GetString( lProjReportIncludeFileDBID, sRptIncFile );
			if (bAllowReportIncludeFile && !sRptIncFile.isEmpty())
			{	QString sOrigRptIncFile = sRptIncFile;
				BOOL bOrigRptIncFileLastSlashIdx = sRptIncFile.lastIndexOf('\\');
				if (sRptIncFile.indexOf(':') < 0 && sRptIncFile.indexOf('\\') != 0)
				{	// report file does not include a FULL path, so expected to be a path relative to the project file - so prepend project path...
					sRptIncFile = m_sModelPathOnly + sRptIncFile;
					if (!FileExists( sRptIncFile.toLocal8Bit().constData() ))
					{	// if rpt incl file not found in model path, it might have been located elsewhere and already copied into processing directory - SAC 10/27/17
						QString sChkRptIncFile = m_sProcessPath + sOrigRptIncFile;
						if (FileExists( sChkRptIncFile.toLocal8Bit().constData() ))
							sRptIncFile = sChkRptIncFile;
				}	}
				if (!FileExists( sRptIncFile.toLocal8Bit().constData() ))
				{	sLogMsg = QString( "CSE report include file not found '%1'" ).arg( sRptIncFile );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					//WriteToLogFile( WM_LOGUPDATED, sRptFileErr );
					BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
					sRptIncFile.clear();
				}
				else
				{	QString sRptIncFileNoPath = sRptIncFile.right( sRptIncFile.length() - sRptIncFile.lastIndexOf('\\') - 1 );
					if (bOrigRptIncFileLastSlashIdx >= 0)
						// need to CHANGE report include file setting to reference only the filename (no path info)
						BEMPX_SetBEMData( lProjReportIncludeFileDBID, BEMP_QStr, (void*) &sRptIncFileNoPath );
					sProcRptIncFile = m_sProcessPath + sRptIncFileNoPath;
				}
				if (!sRptIncFile.isEmpty() && sRptIncFile.compare( sProcRptIncFile, Qt::CaseInsensitive ) == 0)
				{	// if we have a valid report include file but both the source and destination path\filenames are identical, then empty them, as no copying is required
					sRptIncFile.clear();
					sProcRptIncFile.clear();
				}
			}
			else if (!bAllowReportIncludeFile && !sRptIncFile.isEmpty())
			{	// SAC 9/4/17 - force re-default of Proj:ReportIncludeFile if it is specified but this run should not have it
				BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
				sRptIncFile.clear();
			}

			// SAC 7/2/15 - added logic here to check for and address usage of Zone:TstatIncludeFile
			long lUseTstatIncFile, lDBID_Zone_UseTstatIncFile = BEMPX_GetDatabaseID( "Zone:UseTstatIncFile" ), lDBID_Zone_TstatIncludeFile = BEMPX_GetDatabaseID( "Zone:TstatIncludeFile" );
			int iNumZones = (lDBID_Zone_UseTstatIncFile < 1 ? 0 : BEMPX_GetNumObjects( BEMPX_GetClassID( lDBID_Zone_UseTstatIncFile ) ));
			for (int iZnIdx=0; (iRetVal == 0 && iZnIdx < iNumZones); iZnIdx++)
			{	if (BEMPX_GetInteger( lDBID_Zone_UseTstatIncFile,  lUseTstatIncFile,    0, -1, iZnIdx ) && lUseTstatIncFile > 0 &&
					 BEMPX_GetString(  lDBID_Zone_TstatIncludeFile, sZoneIncFile, FALSE, 0, -1, iZnIdx ) && !sZoneIncFile.isEmpty() && StringInArray( saZoneIncFiles, sZoneIncFile ) < 0)
				{	//BOOL bOrigZoneIncFileLastSlashIdx = sZoneIncFile.lastIndexOf('\\');
					if (sZoneIncFile.indexOf(':') < 0 && sZoneIncFile.indexOf('\\') != 0)
						// include file does not include a FULL path, so expected to be a path relative to the project file - so prepend project path...
						sZoneIncFile = m_sModelPathOnly + sZoneIncFile;
					if (!FileExists( sZoneIncFile.toLocal8Bit().constData() ))
					{	if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Zone:Name" ), sProcZoneIncFile, FALSE, 0, -1, iZnIdx ) || sProcZoneIncFile.isEmpty())
					 		sProcZoneIncFile = "<unknown>";
						sLogMsg = QString( "ERROR:  CSE zone '%1' include file not found '%2'" ).arg( sProcZoneIncFile, sZoneIncFile );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						iRetVal = BEMAnal_CECRes_MissingZnCSEIncFile;
						//BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
						sZoneIncFile.clear();
					}
					else
					{	QString sZoneIncFileNoPath = sZoneIncFile.right( sZoneIncFile.length() - sZoneIncFile.lastIndexOf('\\') - 1 );
					//	if (bOrigZoneIncFileLastSlashIdx >= 0)
					//		// need to CHANGE report include file setting to reference only the filename (no path info)
					//		BEMPX_SetBEMData( lProjReportIncludeFileDBID, BEMP_QStr, (void*) &sZoneIncFileNoPath );
						sProcZoneIncFile = m_sProcessPath + sZoneIncFileNoPath;
					}
					if (!sZoneIncFile.isEmpty() && sZoneIncFile.compare( sProcZoneIncFile, Qt::CaseInsensitive ) == 0)
					{	// if we have a valid report include file but both the source and destination path\filenames are identical, then empty them, as no copying is required
						sZoneIncFile.clear();
						sProcZoneIncFile.clear();
					}
					if (!sZoneIncFile.isEmpty() && !sProcZoneIncFile.isEmpty())
					{	saZoneIncFiles.push_back( sZoneIncFile );
						saProcZoneIncFiles.push_back( sProcZoneIncFile );
					 	if (BEMPX_GetString( BEMPX_GetDatabaseID( "Zone:Name" ), sProcZoneIncFile, FALSE, 0, -1, iZnIdx ) && !sProcZoneIncFile.isEmpty())
					 		saZoneNameIncFiles.push_back( sProcZoneIncFile );
					 	else
					 		saZoneNameIncFiles.push_back( "<unknown>" );
				}	}
			}
		}

		if (iRetVal == 0)
		{	// Copy weather & report include files into processing directory
			// ??? do this for each & every run ???
			QString sDestWthr;	int i;
			sDestWthr     = m_sProcessPath + m_sCSEWthr.right( m_sCSEWthr.length() - m_sCSEWthr.lastIndexOf('\\') - 1 ); // "CTZ12S13.CSW";
			const char* pszFileDescs[] = {	"CSE weather", 							"CSE report include" 												};
			QString* psaCopySrc[ ] = { 		&m_sCSEWthr,  								(sRptIncFile.isEmpty() ? NULL : &sRptIncFile), 		NULL	};
			QString* psaCopyDest[] = {			&sDestWthr, 								&sProcRptIncFile														};
			int      iaCopyError[] = {			BEMAnal_CECRes_SimWthrWriteError, 	BEMAnal_CECRes_CSEIncFIleWriteError								};
			for (i=0; (psaCopySrc[i] != NULL && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
									"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
									"(once the file is closed), or \n'Abort' to abort the analysis." ).arg( pszFileDescs[i], *psaCopyDest[i] );
				if (!OKToWriteOrDeleteFile( psaCopyDest[i]->toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( pszFileDescs[i], *psaCopyDest[i] );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( pszFileDescs[i], *psaCopyDest[i] );
					iRetVal = iaCopyError[i];
				}
				else if (!CopyFile( psaCopySrc[i]->toLocal8Bit().constData(), psaCopyDest[i]->toLocal8Bit().constData(), FALSE ))
				{	sErrorMsg = QString( "ERROR:  Unable to copy %1 file:  '%2'  to:  '%3'" ).arg( pszFileDescs[i], *psaCopySrc[i], *psaCopyDest[i] );
					iRetVal = iaCopyError[i]+1;
				}
			}
		// similar loop as above but for Zone include files
			for (i=0; (i < saZoneIncFiles.size() && iRetVal == 0); i++)
			{	sMsg = QString( "The zone '%1' CSE include file '%2' is opened in another application.  This file must be closed in that "
									"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
									"(once the file is closed), or \n'Abort' to abort the analysis." ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
				if (!OKToWriteOrDeleteFile( saProcZoneIncFiles[i].toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite zone '%1' CSE include file:  %2" ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite zone '%1' CSE include file:  %2" ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
					iRetVal = BEMAnal_CECRes_CSEIncFIleWriteError;
				}
				else if (!CopyFile( saZoneIncFiles[i].toLocal8Bit().constData(), saProcZoneIncFiles[i].toLocal8Bit().constData(), FALSE ))
				{	sErrorMsg = QString( "ERROR:  Unable to copy %1 file:  '%2'  to:  '%3'" ).arg( "CSE include", saZoneIncFiles[i], saProcZoneIncFiles[i] );
					iRetVal = BEMAnal_CECRes_CSEIncFileCopyError;
				}
			}
		}

		// SAC 3/18/17 - storage of TDV CSV file to be made available to the CSE input file
		pCSERun->SetTDVFName( "" );		// SAC 4/16/17
		QString sTDVFile;
		if (iRetVal == 0)
		{	long lCSE_WriteTDV;
			if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CSE_WriteTDV" ), lCSE_WriteTDV ) && lCSE_WriteTDV > 0)
			{	sTDVFile = sProjFileAlone + "-tdv.csv";
				QString sFullTDVFile = m_sProcessPath + sTDVFile;
				sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
				             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
								 "(once the file is closed), or \n'Abort' to abort the %3." ).arg( "TDV", sFullTDVFile, "compliance report generation" );
				if (!OKToWriteOrDeleteFile( sFullTDVFile.toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file (required for CSE simulation):  %2" ).arg( "TDV", sFullTDVFile );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file (required for CSE simulation):  %2" ).arg( "TDV", sFullTDVFile );
					iRetVal = BEMAnal_CECRes_TDVFileWriteError;	//  Error writing CSV file w/ TDV data (required for CSE simulation)
				}
				else
				{	double daTDVElec[8760], daTDVFuel[8760], daTDVSecElec[8760], daTDVSecFuel[8760];		long lCZ=0, lGas=0;
					bool bHaveSecTDVElec=false, bHaveSecTDVFuel=false;
					if (	!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ClimateZone" ), lCZ  ) || lCZ  < 1 || lCZ > 16 ||
							!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:GasType"     ), lGas ) || lGas < 1 || lGas > 2 ||
							BEMPX_GetTableColumn( &daTDVElec[0], 8760, "TDVTable", ((lCZ-1) * 3) + 1       , NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0 ||
							BEMPX_GetTableColumn( &daTDVFuel[0], 8760, "TDVTable", ((lCZ-1) * 3) + 1 + lGas, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( false );
						sErrorMsg = QString( "ERROR:  Unable to retrieve TDV data for CZ %1, Gas Type %2 (required for CSE simulation)" ).arg( QString::number(lCZ), QString::number(lGas) );
						iRetVal = BEMAnal_CECRes_TDVFileWriteError;	//  Error writing CSV file w/ TDV data (required for CSE simulation)
					}
					else
					{	QDateTime locTime = QDateTime::currentDateTime();
						QString timeStamp = locTime.toString("ddd dd-MMM-yy  hh:mm:ss ap");   // "Wed 14-Dec-16  12:30:29 pm"

						// SAC 9/23/17 - added code to summ GHG TDV adders to TDV data stored to 
						QString qsTDVSecTblElec, qsTDVSecTblFuel;
						bHaveSecTDVElec = ( BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVSecTbl_Elec" ), qsTDVSecTblElec ) && 
												  qsTDVSecTblElec.length() > 0 && qsTDVSecTblElec.compare( "none", Qt::CaseInsensitive ) && 
												  BEMPX_GetTableColumn( &daTDVSecElec[0], 8760, qsTDVSecTblElec.toLocal8Bit().constData(), lCZ, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) == 0 );
						if (lGas == 1)
							BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVSecTbl_NGas" ), qsTDVSecTblFuel );
						else
							BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVSecTbl_Othr" ), qsTDVSecTblFuel );
						bHaveSecTDVFuel = ( qsTDVSecTblFuel.length() > 0 && qsTDVSecTblFuel.compare( "none", Qt::CaseInsensitive ) && 
												  BEMPX_GetTableColumn( &daTDVSecFuel[0], 8760, qsTDVSecTblFuel.toLocal8Bit().constData(), lCZ, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) == 0 );
		      		QString qsVer, qsGas;
						if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMgrVersion" ), qsVer ) || qsVer.length() < 1)
							qsVer = "(unknown version)";
						switch (lGas)
						{	case  1 :	qsGas = "NatGas";   break;
							case  2 :	qsGas = "Propane";  break;
							default :	qsGas = "(unknown)";  break;
						}

						FILE *fp_CSV;
						int iErrorCode;
						try
						{	iErrorCode = fopen_s( &fp_CSV, sFullTDVFile.toLocal8Bit().constData(), "wb" );
							if (iErrorCode != 0 || fp_CSV == NULL)
							{	assert( false );
								sErrorMsg = QString( "ERROR:  Unable to write TDV data file (required for CSE simulation):  %1" ).arg( sFullTDVFile );
								iRetVal = BEMAnal_CECRes_TDVFileWriteError;	//  Error writing CSV file w/ TDV data (required for CSE simulation)
							}
							else
							{	fprintf( fp_CSV, "\"TDV Data (TDV/Btu)\",\"001\"\n" );
								fprintf( fp_CSV, "\"%s\"\n", timeStamp.toLocal8Bit().constData() );
								fprintf( fp_CSV, "\"%s, CZ%ld, Fuel %s\",\"Hour\"\n", qsVer.toLocal8Bit().constData(), lCZ, qsGas.toLocal8Bit().constData() );
								fprintf( fp_CSV, "\"tdvElec\",\"tdvFuel\"\n" );
								for (int hr=0; hr<8760; hr++)
								{	if (bHaveSecTDVElec)
										daTDVElec[hr] += (daTDVSecElec[hr] / 3.413);
									if (bHaveSecTDVFuel)
										daTDVFuel[hr] += (daTDVSecFuel[hr] / 100);
									fprintf( fp_CSV, "%g,%g\n", daTDVElec[hr], daTDVFuel[hr] );
								}
								fflush( fp_CSV );
								fclose( fp_CSV );
							}
						}
						catch( ... )
						{	assert( false );
							sErrorMsg = QString( "ERROR:  Exception thrown writing TDV data file (required for CSE simulation):  %1" ).arg( sFullTDVFile );
							iRetVal = BEMAnal_CECRes_TDVFileWriteError;	//  Error writing CSV file w/ TDV data (required for CSE simulation)
					// how to handle error writing to TDV CSV file ??
						}
				}	}
				if (iRetVal == 0)
					pCSERun->SetTDVFName( sTDVFile );		// SAC 4/16/17
		}	}

		if (iRetVal == 0)
			iRetVal = SetupRunFinish( iRunIdx, sErrorMsg );
	}
	return iRetVal;
}		// CSERunMgr::SetupRun

int CSERunMgr::SetupRunFinish(
	int iRunIdx, QString& sErrorMsg, const char* sCSEFileCopy /*=NULL*/ )
{
	int iRetVal = 0;
	QString sMsg, sLogMsg;

	CSERun* pCSERun = (iRunIdx < (int) m_vCSERun.size() ? m_vCSERun[iRunIdx] : NULL);
	if (pCSERun == NULL)
	{	assert( false );
		return BEMAnal_CECRes_SimInputWriteError;
	}

//	long lRunNumber;
	QString sRunID, sRunIDProcFile, sRunAbbrev;
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunID"         ),  sRunID         );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunIDProcFile" ),  sRunIDProcFile );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunAbbrev"     ),  sRunAbbrev     );

	QString sProjFileAlone = m_sModelFileOnlyNoExt + sRunIDProcFile;

		QString sTDVFName = pCSERun->GetTDVFName();		// SAC 4/16/17
		if (sTDVFName.length() > 0)
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "cseTOP:tdvfName" ), BEMP_QStr, (void*) &sTDVFName );
		else
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "cseTOP:tdvfName" ), m_iError );

// SAC 12/14/16 - code to confirm need for CSE Battery PRE-RUN
		QString sProjCSEBattFile, sCSEBattCtrlCSVFile;
		BEMObject* pBattCtrlImpFileObj = NULL;
		if (iRetVal == 0)
		{	long lSecondBattSimReqd;
			if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:SecondBattSimReqd" ), lSecondBattSimReqd ) && lSecondBattSimReqd > 0)
			{	// modify name of CSV file referenced by Proj:BattCtrlImportFile
				if (BEMPX_GetObject( BEMPX_GetDatabaseID( "Proj:BattCtrlImportFile" ), pBattCtrlImpFileObj ) && pBattCtrlImpFileObj && pBattCtrlImpFileObj->getClass())
				{	int iBCIFObjIdx = BEMPX_GetObjectIndex( pBattCtrlImpFileObj->getClass(), pBattCtrlImpFileObj );		assert( iBCIFObjIdx >= 0 );
					sCSEBattCtrlCSVFile = sProjFileAlone + "-BTCtrl.csv";
					if (iBCIFObjIdx < 0)
					{	assert( false );	// Proj:BattCtrlImportFile object not found 
					}
					else if (BEMPX_SetBEMData( BEMPX_GetDatabaseID( "cseIMPORTFILE:imFileName" ), BEMP_QStr, (void*) &sCSEBattCtrlCSVFile, BEMO_User, iBCIFObjIdx ) < 0)
					{	assert( false );	// error setting Proj:BattCtrlImportFile:imFileName string
					}
					else
						sProjCSEBattFile = m_sProcessPath + sProjFileAlone + "-BTPreRun.cse";
			}	}
		}

		double btMaxCap, btMaxChgPwr, btMaxDschgPwr, btChgEff, btDschgEff;	// SAC 1/23/17 - moved up from below to ensure BATTERY inputs retrieved from BEMBase BEFORE battery is blasted for pre-run CSE writing
		if (!sProjCSEBattFile.isEmpty())
		{	// then need to feed BTPreRun results & TDV data into calc_bt_control.exe to produce ...BTCtrl.csv battery control CSV which the second/final simulation will read
			if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxCap"      ), btMaxCap ))
				btMaxCap      = 16;	// CSE default
			if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxChgPwr"   ), btMaxChgPwr ))
				btMaxChgPwr   = 4;	// CSE default
			if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxDschgPwr" ), btMaxDschgPwr ))
				btMaxDschgPwr = 4;	// CSE default
			if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btChgEff"      ), btChgEff ))
				btChgEff      = 0.975;	// CSE default
			if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btDschgEff"    ), btDschgEff ))
				btDschgEff    = 0.975;	// CSE default
		}

		QString sProjCSEFile;
		if (iRetVal == 0)
		{	sProjCSEFile = m_sProcessPath + sProjFileAlone + ".cse";
			int iLastCSEIdx = (sProjCSEBattFile.isEmpty() ? 0 : 1);	// SAC 12/15/16
			for (int iFLp=0; (iRetVal == 0 && iFLp <= iLastCSEIdx); iFLp++)
			{
				if (iFLp==1)	// SAC 12/15/16
				{	// Have already written the FINAL CSE input (including Battery) - now we are writing the Battery PRE-RUN CSE input, so delete the battery stuff before continuing
					if (pBattCtrlImpFileObj)
						BEMPX_DeleteObject( pBattCtrlImpFileObj );
         		int iBattObjErr;
            	BEMObject* pBattObj = BEMPX_GetObjectByClass( BEMPX_GetDBComponentID( "cseBATTERY" ), iBattObjErr, 0 );
            	if (pBattObj)
						BEMPX_DeleteObject( pBattObj );

				// SAC 9/4/17 - toggle OFF ReportIncludeFile for BTPreRun CSE run - in this case defaulting to '1' (prevent in BTPreRun)
					long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:ReportIncludeFile" ), lReportInclPropOnly = 1;
					QString sChkRptIncFile;
					if (lProjReportIncludeFileDBID > 0 && BEMPX_GetString( lProjReportIncludeFileDBID, sChkRptIncFile ) && !sChkRptIncFile.isEmpty() &&
						 !BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ReportInclPropOnly" ), lReportInclPropOnly ))
						lReportInclPropOnly = 1;
					if (!sChkRptIncFile.isEmpty() && lReportInclPropOnly > 0)
						BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
				}

				QString sLpCSEFile = (iFLp==0 ? sProjCSEFile : sProjCSEBattFile);
				// Write CSE input file  (and store BEM details file)
				sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
							 "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
								 "(once the file is closed), or \n'Abort' to abort the analysis." ).arg( "CSE input", sLpCSEFile );
				if (!OKToWriteOrDeleteFile( sLpCSEFile.toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( "CSE input", sLpCSEFile );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( "CSE input", sLpCSEFile );
					iRetVal = BEMAnal_CECRes_SimInputOpenError;
				}
				else if (!BEMPX_WriteProjectFile( sLpCSEFile.toLocal8Bit().constData(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/,
											FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, BEMFT_CSE /*iFileType*/, false /*bAppend*/,
											NULL /*ModelName*/, true /*WriteTerminator*/, -1 /*BEMProcIdx*/, -1 /*ModDate*/, false /*OnlyValidInputs*/,
											true /*AllowCreateDateReset*/, 1 /*PropertyCommentOption*/ ))			// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
				{	sErrorMsg = QString( "ERROR:  Unable to write %1 file:  %2" ).arg( "CSE input", sLpCSEFile );
					iRetVal = BEMAnal_CECRes_SimInputWriteError;
				}
				else
				{	SetCurrentDirectory( m_sProcessPath.toLocal8Bit().constData() );
					if (sCSEFileCopy && strlen( sCSEFileCopy ) > 0)
					{	QString sCSECopyFileName = sLpCSEFile.left( sLpCSEFile.length()-4 );
						sCSECopyFileName += sCSEFileCopy;		sCSECopyFileName += ".cse";
						CopyFile( sLpCSEFile.toLocal8Bit().constData(), sCSECopyFileName.toLocal8Bit().constData(), FALSE );
					}
					if (m_bStoreBEMProcDetails)
					{	QString sDbgFileName = sLpCSEFile.left( sLpCSEFile.length()-3 );
						sDbgFileName += "ibd-Detail";
						BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
					}
				}
				BEMPX_RefreshLogFile();	// SAC 5/19/14
			}	// end of iFLp loop
		}

	// Perform TDV export and Battery simulation PRE-RUN
		if (iRetVal == 0 && m_bPerformSimulations && !m_bBypassCSE && !sProjCSEBattFile.isEmpty())	// SAC 12/15/16
		{	bool bBattCtrlSetup = false;
#ifdef CM_QTGUI
				if (sqt_win && sqt_progress)
					sqt_win->repaint();
#endif

		// First need to simulate the BTPreRun CSE input...
			QString sCSEParams, sProjCSEFileForArg = sProjCSEBattFile;
			if (!sProjCSEFileForArg.right(4).compare(".CSE", Qt::CaseInsensitive))
				sProjCSEFileForArg = sProjCSEFileForArg.left( sProjCSEFileForArg.length()-4 );
			sCSEParams = QString( "-b \"%1\"" ).arg( sProjCSEFileForArg );
			int iCSEExitCode = ExecuteNow( this, m_sCSEexe, sCSEParams );
			if (iCSEExitCode != 0)
			{	assert( false );
// how to handle errant BTPreRun simulation ??
			}
			else
			{			
		// then need to write CSV of selected TDV series
				double daTDVData[8760], daTDVSecData[8760];		long lClimateZone=0;		bool bHaveSecTDV=false;
				if (	!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ClimateZone" ), lClimateZone ) ||
						BEMPX_GetTableColumn( &daTDVData[0], 8760, "TDVTable", ((lClimateZone-1) * 3) + 1, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
				{	assert( false );
// how to handle error retrieving climate zone or TDV data ??
				}
				else
				{	// SAC 9/23/17 - added code to summ GHG TDV adders to TDV data stored to 
					QString qsTDVSecTblElec;
					bHaveSecTDV = ( BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVSecTbl_Elec" ), qsTDVSecTblElec ) && 
										 qsTDVSecTblElec.length() > 0 && qsTDVSecTblElec.compare( "none", Qt::CaseInsensitive ) && 
										 BEMPX_GetTableColumn( &daTDVSecData[0], 8760, qsTDVSecTblElec.toLocal8Bit().constData(), lClimateZone, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) == 0 );
					bool bTDVDataOK = true;
					QString sTDVCSVFile = m_sProcessPath + sProjFileAlone + "-tdvelec.csv";  // switched TDV filename here to "tdvelec" to not conflict w/ new 2-col CSV above - SAC 3/18/17
					FILE *fp_CSV;
					int iErrorCode;
					try
					{	iErrorCode = fopen_s( &fp_CSV, sTDVCSVFile.toLocal8Bit().constData(), "wb" );
						if (iErrorCode != 0 || fp_CSV == NULL)
						{	assert( false );
							bTDVDataOK = false;
// how to handle error TDV CSV file ??
						}
						else
						{	fprintf( fp_CSV, "\"TDV Data\",001\n" );
							fprintf( fp_CSV, "\"Wed 14-Dec-16   9:39:00 am\",\n" );
							fprintf( fp_CSV, "\"TDV [TDV/Btu]\",\"Hour\"\n" );		// SAC 3/10/17 - fixed incorrect units label, was: TDV [kBtu/kWh]
							fprintf( fp_CSV, "\"tdv\"\n" );
							if (bHaveSecTDV)	// SAC 9/23/17
							{	for (int hr=0; hr<8760; hr++)
									fprintf( fp_CSV, "%g\n", (daTDVData[hr] + (daTDVSecData[hr]/3.413)) );
							}
							else
							{	for (int hr=0; hr<8760; hr++)
									fprintf( fp_CSV, "%g\n", daTDVData[hr] );
							}
							fflush( fp_CSV );
							fclose( fp_CSV );
						}
					}
					catch( ... )
					{	assert( false );
						bTDVDataOK = false;
// how to handle error writing to TDV CSV file ??
					}

					if (bTDVDataOK)
					{
		// then need to feed BTPreRun results & TDV data into calc_bt_control.exe to produce ...BTCtrl.csv battery control CSV which the second/final simulation will read
						// SAC 1/23/17 - now done above, since at this point cseBATTERY obejct has been deleted from BEMBase (to write the BTPreRun CSE input)
						//double btMaxCap, btMaxChgPwr, btMaxDschgPwr, btChgEff, btDschgEff;
						//if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxCap"      ), btMaxCap ))
						//	btMaxCap      = 16;	// CSE default
						//if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxChgPwr"   ), btMaxChgPwr ))
						//	btMaxChgPwr   = 4;	// CSE default
						//if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btMaxDschgPwr" ), btMaxDschgPwr ))
						//	btMaxDschgPwr = 4;	// CSE default
						//if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btChgEff"      ), btChgEff ))
						//	btChgEff      = 0.975;	// CSE default
						//if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "cseBATTERY:btDschgEff"    ), btDschgEff ))
						//	btDschgEff    = 0.975;	// CSE default

						QString sCBCexe = m_sCSEexe.left( std::max( m_sCSEexe.lastIndexOf('/'), m_sCSEexe.lastIndexOf('\\') )+1 );
						sCBCexe += "calc_bt_control.exe";
						QString sCBCParams = QString( "\"%1.csv\" \"%2\" \"%3\" %4 %5 %6 %7 %8" ).arg( sProjCSEBattFile.left( sProjCSEBattFile.length()-4 ), sCSEBattCtrlCSVFile, sTDVCSVFile,
														QString::number( btMaxCap ), QString::number( btMaxChgPwr ), QString::number( btMaxDschgPwr ), QString::number( btChgEff ), QString::number( btDschgEff ) );
											//  dist\calc_bt_control.exe test\1STORY.CSV test\BT_CONTROL.CSV test\tdv.csv 16.320 4.08 4.08 0.9747 0.9747
											//  Arguments:
											//  (1) path to input meter CSV file
											//  (2) path to output control CSV file
											//  (3) path to input TDV CSV file
											//  (4) Battery maximum usable capacity (kWh)
											//  (5) Battery maximum charging power (kW)
											//  (6) Battery maximum discharging power (kW)
											//  (7) Battery charge efficiency (0 < eff <= 1)
											//  (8) Battery discharge efficiency (0 < eff <= 1)
							// if verbose logging only ??
									QString sCBCLogMsg = QString( "   Processing BTPreRun results (via calc_bt_control):  %1" ).arg( sCBCParams );
									BEMPX_WriteLogFile( sCBCLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//	QString sDbgMsg = QString( "about to run calc_bt_control:\n%1" ).arg( sCBCParams );
//	BEMMessageBox( sDbgMsg );

						int iCBCExitCode = ExecuteNow( this, sCBCexe, sCBCParams );
						if (iCBCExitCode != 0)
						{	assert( false );
// how to handle error running calc_bt_control ??
						}
						else
							bBattCtrlSetup = true;
//	sDbgMsg = QString( "calc_bt_control exit code: %1" ).arg( QString::number(iCBCExitCode) );
//	BEMMessageBox( sDbgMsg );
					}
				}
			}

			if (!bBattCtrlSetup)
				iRetVal = BEMAnal_CECRes_CSEBattCtrlSetupErr;
		}

		if (iRetVal == 0 && m_bPerformSimulations && !m_bBypassCSE)
		{
			// remove trailing '.cse' file extension from path/file passed into CSE
			QString sProjCSEFileForArg = sProjCSEFile;
			if (!sProjCSEFileForArg.right(4).compare(".CSE", Qt::CaseInsensitive))
				sProjCSEFileForArg = sProjCSEFileForArg.left( sProjCSEFileForArg.length()-4 );

			// CSE SIMULATION
			QString sParams;
			//	sParams = QString( "-b \"%s.cse\"" ).arg( sProjFileAlone );		// SAC 8/20/12 - added '-b' (batch) option to prevent user prompt in the event of sim error
			sParams = QString( "-b \"%1\"" ).arg( sProjCSEFileForArg );
	#ifdef _DEBUG
			sLogMsg = QString( "   CSE exePath:  %1" ).arg( m_sCSEexe );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			sLogMsg = QString( "   CSE cmdLine:  %1" ).arg( sParams );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	#endif
			pCSERun->SetArgs( sParams);
		}

	return iRetVal;
}		// CSERunMgr::SetupRunFinish

int CSERunMgr::SetupRun_NonRes(int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile /*=true*/,		// SAC 5/24/16
											const char* pszRunID /*=NULL*/, const char* pszRunAbbrev /*=NULL*/, QString* psCSEVer /*=NULL*/ )
{
	int iRetVal = 0;
	CSERun* pCSERun = new CSERun;
	m_vCSERun.push_back( pCSERun);
	QString sMsg, sLogMsg;
	m_iNumRuns = 1;		// SAC 5/24/16 - not running parallel DHW simulations for non-res (for now)
	BOOL bLastRun = (iRunIdx == (m_iNumRuns-1));						assert( bLastRun );	// remove if/when we do parallel runs in -Com...
	BOOL bIsStdDesign = (iRunType == CRM_StdDesign);
	pCSERun->SetRunType( iRunType);
	pCSERun->SetLastRun( bLastRun);
	pCSERun->SetIsStdDesign( bIsStdDesign);

	QString sRunID			= pszRunID;
	QString sRunAbbrev	= pszRunAbbrev;
	QString sRunIDProcFile = " - " + sRunAbbrev + QString("-cse");		// add '-cse' to ensure no conflicts w/ files to/from other engines
	QString sProjFileAlone = m_sModelFileOnlyNoExt + sRunIDProcFile;

	if (m_bStoreBEMProcDetails)
	{	QString sDbgFileName;
		sDbgFileName = QString( "%1.ibd-b4Evals" ).arg( sProjFileAlone );
		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
	}

// -Com:
//		; Analysis Data
//           "RunTitle",                          BEMP_Str,  1,  0,  0,   Opt,  "",                 0,  0,                           1044, "RunTitle",  "" 
//           "AnalysisType",                      BEMP_Sym,  1,  0,  0,   Req,  "",                 0,  0,                           1003, "AnalysisType",  ""   
//           "CompType",                          BEMP_Sym,  1,  0,  0,   Req,  "",                 0,  0,                           1003, "ComplianceType",  ""

	long lRunNumber = (iRunType == CRM_User ? 0 : iRunIdx+1 );
//	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunNumber" ), BEMP_Int, (void*) &lRunNumber );
//
//	QString sOrientLtr, sOrientName;
//	if (iRunType < CRM_StdDesign /*!bIsStdDesign*/ && m_lAnalysisType > 0)
//		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropCompError, "ProposedCompliance", m_bVerbose, m_pCompRuleDebugInfo );
//	else if (iRunType >= CRM_StdDesign)	// SAC 3/27/15 - was:  bIsStdDesign)
//	{	// SAC 3/27/15 - SET 
//		if (iRunType == CRM_DesignRating)
//      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:StdDesignBase" ), BEMP_Int, (void*) &m_lDesignRatingRunID );
//		// may at some point need to specifically set  StandardsVersion  if/when multiple standard vintages is supported by a single ruleset
//
//		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalStdConvError, "BudgetConversion", m_bVerbose, m_pCompRuleDebugInfo );
//	}
//	if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
//		iRetVal = BEMAnal_CECRes_RuleProcAbort;

	pCSERun->SetRunNumber( lRunNumber);
	pCSERun->SetRunID( sRunID);
	pCSERun->SetRunIDProcFile( sRunIDProcFile);
	pCSERun->SetRunAbbrev( sRunAbbrev);

//	if (iRetVal == 0 && iRunType >= CRM_NOrientProp && iRunType <= CRM_WOrientProp)		// SAC 3/27/15 - was:  m_bFullComplianceAnalysis && m_lAllOrientations > 0 && !bLastRun)
//	{  // Set Orientation for this particular run
//		BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:OrientAbbrev" ),  sOrientLtr  );
//		BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:OrientName"   ),  sOrientName );
//	}
//
//	QString sMissing;
//	if (sRunID.isEmpty())
//		sMissing += "RunID, ";
//	if (sRunAbbrev.isEmpty())
//		sMissing += "RunAbbrev ";
//	if (iRetVal == 0 && !sMissing.isEmpty())
//	{	sMissing = sMissing.left( sMissing.length()-2 );
//		sErrorMsg = "ERROR:  The following Proj properties not set:" + sMissing;
//		iRetVal = BEMAnal_CECRes_GetReqdDataError;
//	}
//	assert( iRunIdx == (lRunNumber-1) );
//
//	if (iRetVal == 0 && (m_sProcessPath.length() + m_sModelFileOnlyNoExt.length() + sRunIDProcFile.length() + 12) > _MAX_PATH)
//	{	sErrorMsg = QString( "ERROR:  CSE processing path too long:  %1%2%3.*" ).arg( m_sProcessPath, m_sModelFileOnlyNoExt, sRunIDProcFile );
//		iRetVal = BEMAnal_CECRes_ProcPathTooLong;
//	}
//
//	if (iRetVal == 0 && iRunIdx == 0 && m_bInitHourlyResults)  // only initialize hourly results for first simulation??
//		BEMPX_InitializeHourlyResults();

	if (iRetVal == 0)
	{
//		// try evaluating prop & postprop rulelists EVERY time
//		iRetVal = LocalEvaluateRuleset(		sErrorMsg, BEMAnal_CECRes_EvalPropInp3Error, "ProposedInput", m_bVerbose, m_pCompRuleDebugInfo );		// generic project defaulting
//		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
//			iRetVal = BEMAnal_CECRes_RuleProcAbort;
//
//		if (iRetVal == 0) // && iRunIdx == 0)
//			iRetVal = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalSimChkError, "ProposedModelSimulationCheck", m_bVerbose, m_pCompRuleDebugInfo );		// check user input model for simulation-related errors
//		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
//			iRetVal = BEMAnal_CECRes_RuleProcAbort;
//
//		if (iRetVal == 0)
//			iRetVal = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalPostPropError, "PostProposedInput", m_bVerbose, m_pCompRuleDebugInfo );		// setup for Proposed run
//		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
//			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		if (iRetVal == 0)
			iRetVal = LocalEvaluateRuleset( sErrorMsg, 63, "CSE_SimulationPrep", m_bVerbose, m_pCompRuleDebugInfo );
//											63 : Error evaluating CSE_SimulationPrep rules
		if (iRetVal == 0 && BEMPX_AbortRuleEvaluation())
			iRetVal = 63;

		BEMPX_RefreshLogFile();	// SAC 5/19/14

		if (iRetVal == 0 && psCSEVer)
		{
//		if (iRetVal == 0 && iRunIdx == 0)  // Store various software & ruleset versions prior to first run - SAC 12/19/12
//		{	QString sVerTemp, sVerStr;
//			BEMPX_GetRulesetID( sVerTemp, sVerStr );
//			if (!sVerStr.isEmpty())
//				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RulesetVersion" ), BEMP_QStr, (void*) &sVerStr );
//			else
//				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:RulesetVersion" ), m_iError );
//
			QString sCSEVersion = GetVersionInfo();
			if (!sCSEVersion.isEmpty())
			{	*psCSEVer = sCSEVersion;
				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:DHWSimEngVersion" ), BEMP_QStr, (void*) &sCSEVersion );	// SAC 8/23/17 - added storage of CSE sim ver (in place of old T24DHW engine)
			}
			else
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:DHWSimEngVersion" ), m_iError );

//			// SAC 1/8/13 - DHW engine version stored to BEMBase DURING DHW simulation (immediately following the ...Init() call)
//			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:SecSimEngingVer" ), m_iError );
		}

//		// Purge user-defined non-parent/child components which are not referenced  - SAC 1/20/13 - added to prevent simulation of objects that are not referenced in the building model
//		// Purge performed HERE, before objects are cross-referenced (Cons <-> cseCONS & Mat <-> cseMATERIAL), w/ those cross-references preventing any useful purging
//		BEMPX_PurgeUnreferencedComponents();

		QString sOutFiles[CSERun::OutFileCOUNT];
		if (iRetVal == 0)
		{	sOutFiles[CSERun::OutFileCSV] = m_sProcessPath + sProjFileAlone + ".csv";
			sOutFiles[CSERun::OutFileREP] = m_sProcessPath + sProjFileAlone + ".rep";
			sOutFiles[CSERun::OutFileERR] = m_sProcessPath + sProjFileAlone + ".err";
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileCSV], CSERun::OutFileCSV);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileREP], CSERun::OutFileREP);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileERR], CSERun::OutFileERR);

			static const char* pszOutFileDescs[] = { "CSV output", "REP output", "Error output" };
			int i=0;
			for (; (i<CSERun::OutFileCOUNT && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
								"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
								"(once the file is closed), or \n'Abort' to abort the analysis." ).arg( pszOutFileDescs[i], sOutFiles[i] );
				if (!OKToWriteOrDeleteFile( sOutFiles[i].toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
					iRetVal = 62;		//  Unable to open/delete/write simulation output file (.csv or .rep)
				}
				// code to DELETE existing results files prior to simulation
				else if (FileExists( sOutFiles[i].toLocal8Bit().constData() ))
					DeleteFile( sOutFiles[i].toLocal8Bit().constData() );
			}
		}

		QString sRptIncFile, sProcRptIncFile, sZoneIncFile, sProcZoneIncFile;		QVector<QString> saZoneIncFiles, saProcZoneIncFiles, saZoneNameIncFiles;
		if (iRetVal == 0)
		{	// Write Report Include file statement
			long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:CSE_RptIncFile" );
			if (bAllowReportIncludeFile && lProjReportIncludeFileDBID > 0 && BEMPX_GetString( lProjReportIncludeFileDBID, sRptIncFile ) && !sRptIncFile.isEmpty())
			{	BOOL bOrigRptIncFileLastSlashIdx = sRptIncFile.lastIndexOf('\\');
				if (sRptIncFile.indexOf(':') < 0 && sRptIncFile.indexOf('\\') != 0)
					// report file does not include a FULL path, so expected to be a path relative to the project file - so prepend project path...
					sRptIncFile = m_sModelPathOnly + sRptIncFile;
				if (!FileExists( sRptIncFile.toLocal8Bit().constData() ))
				{	sLogMsg = QString( "CSE report include file not found '%1'" ).arg( sRptIncFile );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					//WriteToLogFile( WM_LOGUPDATED, sRptFileErr );
					BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
					sRptIncFile.clear();
				}
				else
				{	QString sRptIncFileNoPath = sRptIncFile.right( sRptIncFile.length() - sRptIncFile.lastIndexOf('\\') - 1 );
					if (bOrigRptIncFileLastSlashIdx >= 0)
						// need to CHANGE report include file setting to reference only the filename (no path info)
						BEMPX_SetBEMData( lProjReportIncludeFileDBID, BEMP_QStr, (void*) &sRptIncFileNoPath );
					sProcRptIncFile = m_sProcessPath + sRptIncFileNoPath;
				}
				if (!sRptIncFile.isEmpty() && sRptIncFile.compare( sProcRptIncFile, Qt::CaseInsensitive ) == 0)
				{	// if we have a valid report include file but both the source and destination path\filenames are identical, then empty them, as no copying is required
					sRptIncFile.clear();
					sProcRptIncFile.clear();
				}
			}

//			// SAC 7/2/15 - added logic here to check for and address usage of Zone:TstatIncludeFile
//			long lUseTstatIncFile, lDBID_Zone_UseTstatIncFile = BEMPX_GetDatabaseID( "Zone:UseTstatIncFile" ), lDBID_Zone_TstatIncludeFile = BEMPX_GetDatabaseID( "Zone:TstatIncludeFile" );
//			int iNumZones = (lDBID_Zone_UseTstatIncFile < 1 ? 0 : BEMPX_GetNumObjects( BEMPX_GetClassID( lDBID_Zone_UseTstatIncFile ) ));
//			for (int iZnIdx=0; (iRetVal == 0 && iZnIdx < iNumZones); iZnIdx++)
//			{	if (BEMPX_GetInteger( lDBID_Zone_UseTstatIncFile,  lUseTstatIncFile,    0, -1, iZnIdx ) && lUseTstatIncFile > 0 &&
//					 BEMPX_GetString(  lDBID_Zone_TstatIncludeFile, sZoneIncFile, FALSE, 0, -1, iZnIdx ) && !sZoneIncFile.isEmpty() && StringInArray( saZoneIncFiles, sZoneIncFile ) < 0)
//				{	//BOOL bOrigZoneIncFileLastSlashIdx = sZoneIncFile.lastIndexOf('\\');
//					if (sZoneIncFile.indexOf(':') < 0 && sZoneIncFile.indexOf('\\') != 0)
//						// include file does not include a FULL path, so expected to be a path relative to the project file - so prepend project path...
//						sZoneIncFile = m_sModelPathOnly + sZoneIncFile;
//					if (!FileExists( sZoneIncFile ))
//					{	if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Zone:Name" ), sProcZoneIncFile, FALSE, 0, -1, iZnIdx ) || sProcZoneIncFile.isEmpty())
//					 		sProcZoneIncFile = "<unknown>";
//						sLogMsg = QString( "ERROR:  CSE zone '%1' include file not found '%2'" ).arg( sProcZoneIncFile, sZoneIncFile );
//						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//						iRetVal = BEMAnal_CECRes_MissingZnCSEIncFile;
//						//BEMPX_DefaultProperty( lProjReportIncludeFileDBID, m_iError );
//						sZoneIncFile.clear();
//					}
//					else
//					{	QString sZoneIncFileNoPath = sZoneIncFile.right( sZoneIncFile.length() - sZoneIncFile.lastIndexOf('\\') - 1 );
//						sProcZoneIncFile = m_sProcessPath + sZoneIncFileNoPath;
//					}
//					if (!sZoneIncFile.isEmpty() && sZoneIncFile.compare( sProcZoneIncFile, Qt::CaseInsensitive ) == 0)
//					{	// if we have a valid report include file but both the source and destination path\filenames are identical, then empty them, as no copying is required
//						sZoneIncFile.clear();
//						sProcZoneIncFile.clear();
//					}
//					if (!sZoneIncFile.isEmpty() && !sProcZoneIncFile.isEmpty())
//					{	saZoneIncFiles.push_back( sZoneIncFile );
//						saProcZoneIncFiles.push_back( sProcZoneIncFile );
//					 	if (BEMPX_GetString( BEMPX_GetDatabaseID( "Zone:Name" ), sProcZoneIncFile, FALSE, 0, -1, iZnIdx ) && !sProcZoneIncFile.isEmpty())
//					 		saZoneNameIncFiles.push_back( sProcZoneIncFile );
//					 	else
//					 		saZoneNameIncFiles.push_back( "<unknown>" );
//				}	}
//			}
		}

		if (iRetVal == 0)
		{	// Copy weather & report include files into processing directory
			// ??? do this for each & every run ???
			QString sDestWthr;	int i;
			int iLastSlashIdx = m_sCSEWthr.lastIndexOf('\\');
			if (m_sCSEWthr.lastIndexOf('/') > iLastSlashIdx)	// SAC 5/27/16 - compatibility w/ paths having etiher forward or back slashes
				iLastSlashIdx = m_sCSEWthr.lastIndexOf('/');
			sDestWthr     = m_sProcessPath + m_sCSEWthr.right( m_sCSEWthr.length() - iLastSlashIdx - 1 ); // "CTZ12S13.CSW";
			const char* pszFileDescs[] = {	"CSE weather", 	"CSE report include" 												};
			QString* psaCopySrc[ ] = { 		&m_sCSEWthr,  		(sRptIncFile.isEmpty() ? NULL : &sRptIncFile), 		NULL	};
			QString* psaCopyDest[] = {			&sDestWthr, 		&sProcRptIncFile														};
			int      iaCopyError[] = {			 60,					64																			};
			for (i=0; (psaCopySrc[i] != NULL && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
									"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
									"(once the file is closed), or \n'Abort' to abort the analysis." ).arg( pszFileDescs[i], *psaCopyDest[i] );
				if (!OKToWriteOrDeleteFile( psaCopyDest[i]->toLocal8Bit().constData(), sMsg, m_bSilent ))
				{	if (m_bSilent)
						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( pszFileDescs[i], *psaCopyDest[i] );
					else
						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( pszFileDescs[i], *psaCopyDest[i] );
					iRetVal = iaCopyError[i];
				}
				else if (!CopyFile( psaCopySrc[i]->toLocal8Bit().constData(), psaCopyDest[i]->toLocal8Bit().constData(), FALSE ))
				{	sErrorMsg = QString( "ERROR:  Unable to copy %1 file:  '%2'  to:  '%3'" ).arg( pszFileDescs[i], *psaCopySrc[i], *psaCopyDest[i] );
					iRetVal = iaCopyError[i]+1;
				}
			}
//		// similar loop as above but for Zone include files
//			for (i=0; (i < saZoneIncFiles.size() && iRetVal == 0); i++)
//			{	sMsg = QString( "The zone '%1' CSE include file '%2' is opened in another application.  This file must be closed in that "
//									"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
//									"(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
//				if (!OKToWriteOrDeleteFile( saProcZoneIncFiles[i], sMsg, m_bSilent ))
//				{	if (m_bSilent)
//						sErrorMsg = QString( "ERROR:  Unable to overwrite zone '%1' CSE include file:  %2" ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
//					else
//						sErrorMsg = QString( "ERROR:  User chose not to overwrite zone '%1' CSE include file:  %2" ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
//					iRetVal = BEMAnal_CECRes_CSEIncFIleWriteError;
//				}
//				else if (!CopyFile( saZoneIncFiles[i], saProcZoneIncFiles[i], FALSE ))
//				{	sErrorMsg = QString( "ERROR:  Unable to copy %1 file:  '%2'  to:  '%3'" ).arg( "CSE include", saZoneIncFiles[i], saProcZoneIncFiles[i] );
//					iRetVal = BEMAnal_CECRes_CSEIncFileCopyError;
//				}
//			}
		}

		if (iRetVal == 0)
		{	// remove path portion of weather filename (to be written to CSE input file) - SAC 5/27/16
			QString sWthrFN;
			long lDBID_CSEwfName = BEMPX_GetDatabaseID( "cseTOP:wfName" );
		 	if (lDBID_CSEwfName > 0 && BEMPX_GetString( lDBID_CSEwfName, sWthrFN ) && !sWthrFN.isEmpty())
		 	{	int iLastSlashIdx = sWthrFN.lastIndexOf('\\');
				if (sWthrFN.lastIndexOf('/') > iLastSlashIdx)	// SAC 5/27/16 - compatibility w/ paths having etiher forward or back slashes
					iLastSlashIdx = sWthrFN.lastIndexOf('/');
				if (iLastSlashIdx >= 0)
				{	sWthrFN = sWthrFN.right( sWthrFN.length() - iLastSlashIdx - 1 );
					BEMPX_SetBEMData( lDBID_CSEwfName, BEMP_QStr, (void*) &sWthrFN );
		}	}	}

		QString sProjCSEFile;
		if (iRetVal == 0)
		{	// Write CSE input file  (and store BEM details file)
			sProjCSEFile = m_sProcessPath + sProjFileAlone + ".cse";
			sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
							 "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
							 "(once the file is closed), or \n'Abort' to abort the analysis." ).arg( "CSE input", sProjCSEFile );
			if (!OKToWriteOrDeleteFile( sProjCSEFile.toLocal8Bit().constData(), sMsg, m_bSilent ))
			{	if (m_bSilent)
					sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				else
					sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				iRetVal = 58;		//	58 : Unable to open/delete/write simulation input (.cse) file
			}
			else if (!BEMPX_WriteProjectFile( sProjCSEFile.toLocal8Bit().constData(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/,
										FALSE /*bSupressAllMessageBoxes*/, BEMFT_CSE /*iFileType*/, false /*bAppend*/,
										NULL /*ModelName*/, true /*WriteTerminator*/, -1 /*BEMProcIdx*/, -1 /*ModDate*/, false /*OnlyValidInputs*/,
										true /*AllowCreateDateReset*/, 1 /*PropertyCommentOption*/ ))			// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
			{	sErrorMsg = QString( "ERROR:  Unable to write %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				iRetVal = 59;		//	59 : Error writing simulation input (.cse) file
			}
			else
			{	SetCurrentDirectory( m_sProcessPath.toLocal8Bit().constData() );
				if (m_bStoreBEMProcDetails)
				{	QString sDbgFileName = sProjCSEFile.left( sProjCSEFile.length()-3 );
					sDbgFileName += "ibd-Detail";
					BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
				}
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}

		if (iRetVal == 0 && m_bPerformSimulations && !m_bBypassCSE)
		{
			// remove trailing '.cse' file extension from path/file passed into CSE
			QString sProjCSEFileForArg = sProjCSEFile;
			if (!sProjCSEFileForArg.right(4).compare(".CSE", Qt::CaseInsensitive))
				sProjCSEFileForArg = sProjCSEFileForArg.left( sProjCSEFileForArg.length()-4 );

			// CSE SIMULATION
			QString sParams;
			//	sParams = QString( "-b \"%1.cse\"" ).arg( sProjFileAlone );		// SAC 8/20/12 - added '-b' (batch) option to prevent user prompt in the event of sim error
			sParams = QString( "-b \"%1\"" ).arg( sProjCSEFileForArg );
	#ifdef _DEBUG
			sLogMsg = QString( "   CSE exePath:  %1" ).arg( m_sCSEexe );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			sLogMsg = QString( "   CSE cmdLine:  %1" ).arg( sParams );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	#endif
			pCSERun->SetArgs( sParams);
		}
	}
	return iRetVal;
}

void CSERunMgr::DoRuns()
{
	CSERun* pCSERun = NULL;
	for(size_t iRun = 0; iRun < m_vCSERun.size(); ++iRun)
	{	pCSERun = m_vCSERun[iRun];
		StartRun( *pCSERun);
		m_vCSEActiveRun.push_back( pCSERun);
	}
	MonitorRuns();
}		// CSERunMgr::DoRuns

void CSERunMgr::DoRun( int iRunIdx )
{
	CSERun* pCSERun = (iRunIdx < (int) m_vCSERun.size() ? m_vCSERun[iRunIdx] : NULL);
	if (pCSERun)
	{	m_iNumProgressRuns = 1;
		StartRun( *pCSERun);
		m_vCSEActiveRun.push_back( pCSERun);
	}
	MonitorRuns();
	m_iNumProgressRuns = -1;
}		// CSERunMgr::DoRun

void CSERunMgr::MonitorRuns()
{
	CSERun* pCSERun;
	exec_stream_t* pES = NULL;
	std::string sOut;
	bool bFirstException = true;
	while(m_vCSEActiveRun.size() > 0)
	{	for(size_t iRun = 0; iRun < m_vCSEActiveRun.size(); ++iRun)
		{	pCSERun = m_vCSEActiveRun[iRun];
			pES = pCSERun->GetExecStream();
			try
			{	if (pES->running())
				{	ProcessRunOutput( pES, iRun, bFirstException);
					Sleep(10);
				}
				else
				{	bool bFirstExceptionX = true;
					while( ProcessRunOutput( pES, iRun, bFirstExceptionX));
					pES->close();
					pCSERun->SetExitCode( pES->exit_code());
					m_vCSEActiveRun.erase(m_vCSEActiveRun.begin()+iRun);
				}
			}
			catch(exec_stream_t::error_t &e)
			{	if (bFirstException)
				{	std::string sLogMsg=e.what();
					BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
					bFirstException = false;
				}
			}
		}
	}
}		// CSERunMgr::DoRuns

bool CSERunMgr::ProcessRunOutput(exec_stream_t* pES, size_t iRun, bool &bFirstException)
{
	assert( pES);
	std::string sOut;
	try
	{	std::istream& is = pES->out();
		is >> sOut;
		if (!is.good())
			is.clear();
		if (!sOut.empty())
		{	sOut = " " + sOut;
			if (CSE_ProcessMessage( 0, sOut.c_str(), iRun, this) == CSE_ABORT)
				pES->kill(255);
			else if (sOut.find("OpenGL") != std::string::npos)
				IncNumOpenGLErrors();
//			if (pCSERunMgr && (strstr( msg, "OpenGL" ) != NULL))
//				pCSERunMgr->IncNumOpenGLErrors();
		}
	}
	catch(exec_stream_t::error_t &e)
	{	if (bFirstException)
		{	std::string sLogMsg=e.what();
			BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
			bFirstException = FALSE;
		}
	}
	return !sOut.empty();
}		// CSERunMgr::ProcessRunOutput

void CSERunMgr::StartRun(CSERun& cseRun)
{
	try
	{	exec_stream_t* pES = new exec_stream_t( m_sCSEexe.toLocal8Bit().constData(), cseRun.GetArgs().toLocal8Bit().constData(), CREATE_NO_WINDOW);
		cseRun.SetExecStream( pES);
	}
	catch(exec_stream_t::error_t &e)
	{	std::string sLogMsg=e.what();
		BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
	}
}		// CSERunMgr::DoRun

QString CSERunMgr::GetVersionInfo()
{	QString sVersion;
	DWORD verHandle = NULL;
	UINT size = 0;
	LPBYTE lpBuffer = NULL;
	DWORD verSize = GetFileVersionInfoSize( m_sCSEexe.toLocal8Bit().constData(), &verHandle);
	if (verSize != NULL)
	{	LPSTR verData = new char[verSize];
		if (GetFileVersionInfo( m_sCSEexe.toLocal8Bit().constData(), verHandle, verSize, verData))
		{	if (VerQueryValue(verData,"\\",(VOID FAR* FAR*)&lpBuffer,&size))
			{	int iLastSlash = std::max( m_sCSEexe.lastIndexOf('\\'), m_sCSEexe.lastIndexOf('/') );
				int iLastDot   =           m_sCSEexe.lastIndexOf('.');
				QString qsCSEName = "CSE";
				if (iLastSlash > 0 && iLastDot > (iLastSlash+1))		// SAC 12/4/17 - report CSEs w/ different executable filenames
					qsCSEName = m_sCSEexe.mid( iLastSlash+1, (iLastDot-iLastSlash-1) );
				if (size)
				{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{	int major = HIWORD(verInfo->dwFileVersionMS);
						int minor = LOWORD(verInfo->dwFileVersionMS);
						sVersion = QString( "%1 %2.%3" ).arg( qsCSEName, QString::number(major), QString::number(minor));
						int pathLen = m_sCSEexe.length();
						if (pathLen >=4)
						{	if (_stricmp( m_sCSEexe.right(4).toLocal8Bit().constData(), ".exe") == 0)
								sVersion += " EXE";
							else if (_stricmp( m_sCSEexe.right(4).toLocal8Bit().constData(), ".dll") == 0)
								sVersion += " DLL";
						}
					}
				}
			}
		}
		delete[] verData;
	}
	return sVersion;
}


static const char pszDashes[] = "--------------------------------------------------------------------------------\n";

// process CSE errors and/or reports into file for user review - SAC 11/7/16
bool CSERunMgr::ArchiveSimOutput( int iRunIdx, QString sSimOutputPathFile, int iOutFileType )
{	bool bRetVal = ((int) m_vCSERun.size() > iRunIdx ? true : false);

	if (bRetVal)
	{	const CSERun& cseRun = GetRun(iRunIdx);
		QString sTemp, sCSEOutFile = cseRun.GetOutFile( (CSERun::OutFile) iOutFileType );		assert( !sCSEOutFile.isEmpty() );
		QStringList slErrors;
		if (iOutFileType == CSERun::OutFileERR && m_iSimErrorOpt == 1)
		{	// make sure Errors exist in the error output file BEFORE 
			QFile errFile( sCSEOutFile );
			if (errFile.open( QIODevice::Text | QIODevice::ReadOnly ))
			{
	         char buff[ 300 ];
	         // read each line from the prev file into the log file
	         int iReadRetVal;   bool bSavingErr = false;   int iErrIdx = -1;
	         while (iReadRetVal = errFile.readLine( buff, 299 ) > 0)
	         {	sTemp = buff;
	         	if (bSavingErr)
	         	{	if (sTemp.left(4).compare("----"))
	         			slErrors[iErrIdx] += sTemp;
	        			else  // end of error
	        				bSavingErr = false;
	         	}
	         	else
	         	{	bool bCSELineErr  = (!sTemp.right(8).compare("Error: \n"));
	         		bool bOtherCSEErr = (!sTemp.left( 5).compare("Error"));
	         		if (bCSELineErr || bOtherCSEErr)
		         	{	// start of new error message
		         		if (bCSELineErr)
		         		{	int iStartParen = sTemp.lastIndexOf('('), iEndParen = sTemp.lastIndexOf(')');		assert( iEndParen > (iStartParen+1) && iStartParen > 0 );
			         		if (iEndParen > (iStartParen+1) && iStartParen > 0)
			         			slErrors.push_back( QString("\nError on line %1: ").arg( sTemp.mid( iStartParen+1, (iEndParen-iStartParen-1) ) ) );
			         		else
			         			slErrors.push_back( QString("\n%1").arg( sTemp ) );
			         	}
		         		else	// added else condition for those errors that don;t track directly back to CSE input line numbers
		         			slErrors.push_back( QString("\n%1").arg( sTemp ) );
		        			iErrIdx++;
		     				bSavingErr = true;
	         	}	}
	         }
	         assert( iReadRetVal==0 );	// if -1, then error reading
				if (iReadRetVal < 0)
					bRetVal = false;
//---------------
// Error: C:\WSF\DEVLIBS\COMPMGR\SRC\BEM-OPEN\BIN\RES\PROJECTS\SAMPLES-2016\1STORYEXAMPLE3-SMATTIC2 - COMP16\1STORYEXAMPLE3-SMATTIC2 - PROP.CSE(1935): Error: 
//  RSYS 'rsys-HVAC System 1': 
//    S0497: 'rsSEER' missing: required when rsType=ACFurnace (cooling is available)
//---------------
// Error: C:\WSF\DEVLIBS\COMPMGR\SRC\BEM-OPEN\BIN\RES\PROJECTS\SAMPLES-2016\1STORYEXAMPLE3-SMATTIC2 - COMP16\1STORYEXAMPLE3-SMATTIC2 - PROP.CSE(1935): Error: 
//  RSYS 'rsys-HVAC System 1': rsSEER (0) must be > rsEER (0.34)
//---------------
// Info: C:\WSF\DEVLIBS\COMPMGR\SRC\BEM-OPEN\BIN\RES\PROJECTS\SAMPLES-2016\1STORYEXAMPLE3-SMATTIC2 - COMP16\1STORYEXAMPLE3-SMATTIC2 - PROP.CSE(1983): Info: 
//  S0214: No run due to error(s) above
//---------------
		}	}

//if (iOutFileType == CSERun::OutFileERR)
//{QString sDbgMsg = QString( "%1 errors found listed in CSE error file: %2" ).arg( QString::number(slErrors.size()), sCSEOutFile );
//BEMMessageBox( sDbgMsg );
//}

		if (bRetVal && (iOutFileType != CSERun::OutFileERR || slErrors.size() > 0) &&
							(iOutFileType != CSERun::OutFileREP || FileExists( sCSEOutFile )))
		{
		try
		{	bool bOutFileAlreadyExists = FileExists( sSimOutputPathFile );
			QFile outFile( sSimOutputPathFile );
			if (!bOutFileAlreadyExists)
				bRetVal = outFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
			else
				bRetVal = outFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
																																			assert( bRetVal );
			if (bRetVal)
			{
				if (bOutFileAlreadyExists)
					outFile.write( "\n\n" );

				QString sCSEInpFile = cseRun.GetArgs();
				sCSEInpFile = sCSEInpFile.left( sCSEInpFile.length()-1 );
				int iLastSlash    = std::max( sCSEInpFile.lastIndexOf('\\'),               sCSEInpFile.lastIndexOf('/') );
				int i2ndLastSlash = std::max( sCSEInpFile.lastIndexOf('\\', iLastSlash-1), sCSEInpFile.lastIndexOf('/', iLastSlash-1) );

//--------------------------------------------------------------------------------
//--  PROPOSED model:  Dir\File.cse
//--------------------------------------------------------------------------------
				outFile.write( pszDashes );
				outFile.write( QString("--  %1 model:  %2\n").arg( cseRun.GetRunID().toUpper(), sCSEInpFile.right( (sCSEInpFile.length()-i2ndLastSlash-1) ) ).toLocal8Bit().constData() );
				outFile.write( pszDashes );

				if (iOutFileType == CSERun::OutFileERR)
					for (int i=0; i<slErrors.size(); i++)
					{	outFile.write( slErrors[i].toLocal8Bit().constData() );
						//outFile.write( "\n" );
					}
				else	// report (not error) file
				{
					QFile repFile( sCSEOutFile );
					if (repFile.open( QIODevice::Text | QIODevice::ReadOnly ))
					{
			         char buff[ 300 ];
			         // read each line from the prev file into the log file
			         int iReadRetVal;
			         while (iReadRetVal = repFile.readLine( buff, 299 ) > 0)
			// at some point 
						{	outFile.write( buff );
							//outFile.write( "\n" );
						}
			         assert( iReadRetVal==0 );	// if -1, then error reading
						if (iReadRetVal < 0)
							bRetVal = false;
					}
					else
						bRetVal = false;
				}

//	int m_iSimReportOpt;		// SAC 11/5/16 - 0: no CSE reports / 1: user-specified reports / 2: entire .rpt file
//	int m_iSimErrorOpt;		// SAC 11/5/16 - 0: no CSE errors / 1: always list CSE errors
//	int  iSimReportDetailsOption	=	GetCSVOptionValue( "SimReportDetailsOption",   1,  saCSVOptions );		// SAC 11/5/16 - 0: no CSE reports / 1: user-specified reports / 2: entire .rpt file
//	int  iSimErrorDetailsOption	=	GetCSVOptionValue( "SimErrorDetailsOption" ,   1,  saCSVOptions );		// SAC 11/5/16 - 0: no CSE errors / 1: always list CSE errors

				outFile.close();
			}
		}
		catch( ... )
		{	assert( false );
			bRetVal = false;
		}
	}	}	// end of if (bRetVal)

	return bRetVal;
}