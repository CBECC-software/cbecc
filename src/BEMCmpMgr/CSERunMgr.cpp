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
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include "..\BEMProc\BEMProc.h"
#include "exec-stream.h"
#include "CSERunMgr.h"
#include "memLkRpt.h"

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
	const char* pszUIVersionString) :

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
	m_iError( 0)
{
	m_iNumRuns = (bFullComplianceAnalysis ? (lAllOrientations > 0 ? 5 : 2) : 1);
	if (lAnalysisType > 0 /*bFullComplianceAnalysis*/ && m_lDesignRatingRunID > 0)		// SAC 3/27/15
		m_iNumRuns++;
}		// CSERunMgr::CSERunMgr

CSERunMgr::~CSERunMgr()
{
	CSERun* pCSERun = NULL;
	while (!m_vCSERun.empty())
	{	pCSERun = m_vCSERun.back();
		m_vCSERun.pop_back();
		delete pCSERun;
	}
}

int CSERunMgr::SetupRun(
	int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile /*=true*/ )	// SAC 4/29/15 - add argument to DISABLE report include files
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

	QString sOrientLtr, sOrientName;
	if (iRunType < CRM_StdDesign /*!bIsStdDesign*/ && m_lAnalysisType > 0)
		iRetVal = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropCompError, "ProposedCompliance", m_bVerbose, m_pCompRuleDebugInfo );
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
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileCSV], CSERun::OutFileCSV);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileREP], CSERun::OutFileREP);

			static const char* pszOutFileDescs[] = { "CSV output", "REP output" };
			int i=0;
			for (; (i<CSERun::OutFileCOUNT && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
							"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
								 "(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( pszOutFileDescs[i], sOutFiles[i] );
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
									"(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( pszFileDescs[i], *psaCopyDest[i] );
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
									"(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( saZoneNameIncFiles[i], saProcZoneIncFiles[i] );
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

		QString sProjCSEFile;
		if (iRetVal == 0)
		{	// Write CSE input file  (and store BEM details file)
			sProjCSEFile = m_sProcessPath + sProjFileAlone + ".cse";
			sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
						 "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
							 "(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( "CSE input", sProjCSEFile );
			if (!OKToWriteOrDeleteFile( sProjCSEFile.toLocal8Bit().constData(), sMsg, m_bSilent ))
			{	if (m_bSilent)
					sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				else
					sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				iRetVal = BEMAnal_CECRes_SimInputOpenError;
			}
			else if (!BEMPX_WriteProjectFile( sProjCSEFile.toLocal8Bit().constData(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/,
										FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, BEMFT_CSE /*iFileType*/ ))
			{	sErrorMsg = QString( "ERROR:  Unable to write %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				iRetVal = BEMAnal_CECRes_SimInputWriteError;
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
	}
	return iRetVal;
}		// CSERunMgr::SetupRun

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
				*psCSEVer = sCSEVersion;
//				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ), BEMP_QStr, (void*) &sCSEVersion );
//			else
//				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ), m_iError );
//
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
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileCSV], CSERun::OutFileCSV);
			pCSERun->SetOutFile( sOutFiles[CSERun::OutFileREP], CSERun::OutFileREP);

			static const char* pszOutFileDescs[] = { "CSV output", "REP output" };
			int i=0;
			for (; (i<CSERun::OutFileCOUNT && iRetVal == 0); i++)
			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
								"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
								"(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( pszOutFileDescs[i], sOutFiles[i] );
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
									"(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( pszFileDescs[i], *psaCopyDest[i] );
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
							 "(once the file is closed), or \n'Cancel' to abort the analysis." ).arg( "CSE input", sProjCSEFile );
			if (!OKToWriteOrDeleteFile( sProjCSEFile.toLocal8Bit().constData(), sMsg, m_bSilent ))
			{	if (m_bSilent)
					sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				else
					sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( "CSE input", sProjCSEFile );
				iRetVal = 58;		//	58 : Unable to open/delete/write simulation input (.cse) file
			}
			else if (!BEMPX_WriteProjectFile( sProjCSEFile.toLocal8Bit().constData(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/,
										FALSE /*bSupressAllMessageBoxes*/, BEMFT_CSE /*iFileType*/ ))
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
			{	if (size)
				{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{	int major = HIWORD(verInfo->dwFileVersionMS);
						int minor = LOWORD(verInfo->dwFileVersionMS);
						sVersion = QString( "CSE %1.%2" ).arg( QString::number(major), QString::number(minor));
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
