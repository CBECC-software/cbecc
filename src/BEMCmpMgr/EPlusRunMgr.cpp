/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2019, SAC Software Solutions, LLC
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
#include "EPlusRunMgr.h"
#include "memLkRpt.h"
#include "BEMCmpMgrCom.h"
#ifdef OSWRAPPER
#include "OpenStudioInterface.h"
#endif
#include "BEMCmpMgrProgress.h"   // SAC 06/20/22

using namespace std;
#include <string>
#include <vector>
#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf

EPlusRun::EPlusRun() :
	m_lRunNumber( 0),
	m_iSimMonth( 0),
//	m_bLastRun( FALSE),
//	m_bIsStdDesign( FALSE),
	m_iExitCode( 0),
	m_pES( NULL),
	fp_stdout( NULL),
	m_bStdoutWritten( false)
{
//	m_sTDVFName.clear();		// SAC 4/16/17
}

EPlusRun::~EPlusRun()
{
	delete m_pES;
}

void EPlusRun::OpenStdoutFile( QString sStdoutFN )
{
						int iErrorCode;
						try
						{	iErrorCode = fopen_s( &fp_stdout, sStdoutFN.toLocal8Bit().constData(), "wb" );
							if (iErrorCode != 0 || fp_stdout == NULL)
							{	assert( false );
								fp_stdout = NULL;
								m_bStdoutWritten = true; // prevent re-attempting stdout opening
								//sErrorMsg = QString( "ERROR:  Unable to open stdout file:  %1" ).arg( sFullTDVFile );
						}	}
						catch( ... )
						{	assert( false );
							fp_stdout = NULL;
							m_bStdoutWritten = true; // prevent re-attempting stdout opening
							//sErrorMsg = QString( "ERROR:  Exception thrown writing TDV data file (required for CSE simulation):  %1" ).arg( sFullTDVFile );
						}
}
void EPlusRun::WriteStdoutString( std::string str )
{
						try
						{	fprintf( fp_stdout, "%s\n", str.c_str() );
						//{	fprintf( fp_stdout, "%s", str.c_str() );
							if (str.find("EnergyPlus Run Time") != std::string::npos)
							{	fflush( fp_stdout );
								fclose( fp_stdout );
								m_bStdoutWritten = true; // prevent re-attempting stdout opening
						}	}
						catch( ... )
						{	assert( false );
							//fp_stdout = NULL;
							m_bStdoutWritten = true; // prevent re-attempting stdout opening
							//sErrorMsg = QString( "ERROR:  Exception thrown writing TDV data file (required for CSE simulation):  %1" ).arg( sFullTDVFile );
						}
}


EPlusRunMgr::EPlusRunMgr(
	QString sEPlusPath,
//	QString sEPlusWthr,
	QString sModelPathOnly,
//	QString sModelFileOnlyNoExt,
//	QString sProcessPath,
//	bool bFullComplianceAnalysis,
//	bool bInitHourlyResults,
//	long lAllOrientations,
//	long lAnalysisType,
//	long lStdDesignBaseID,
//	long lDesignRatingRunID,
	int iCodeType,
	int iProgressType,
	bool bVerbose,
//	bool bStoreBEMProcDetails,
//	bool bPerformSimulations,
//	bool bBypassEPlus,
	bool bSilent,
//	void* pCompRuleDebugInfo,
//	const char* pszUIVersionString,
//	int iSimReportOpt,
//	int iSimErrorOpt,
//	long lStdMixedFuelRunReqd,
//	long lPrelimPropRunReqd,
//	long lPropFlexRunReqd,
	int iNumRuns) :
	m_sEPlusPath( sEPlusPath),
//	m_sEPlusWthr( sEPlusWthr),
	m_sModelPathOnly( sModelPathOnly),
//	m_sModelFileOnlyNoExt( sModelFileOnlyNoExt),
//	m_sProcessPath( sProcessPath),
//	m_bFullComplianceAnalysis( true),  // bFullComplianceAnalysis),
//	m_bInitHourlyResults( false),  // bInitHourlyResults),
//	m_lAllOrientations( 0),  // lAllOrientations),
//	m_lAnalysisType( 0),  // lAnalysisType),
//	m_lStdDesignBaseID( 0),  // lStdDesignBaseID),
//	m_lDesignRatingRunID( 0),  // lDesignRatingRunID),
	m_iCodeType( iCodeType),
	m_iProgressType( iProgressType),
	m_bAbortingSims( false),
	m_bVerbose( bVerbose),
	m_bStoreBEMProcDetails( true),  // bStoreBEMProcDetails),
	m_bPerformSimulations( true),  // bPerformSimulations),
	m_bBypassEPlus( false),  // bBypassEPlus),
	m_bSilent( bSilent),
//	m_pCompRuleDebugInfo( NULL),  // pCompRuleDebugInfo),
//	m_pszUIVersionString( NULL),  // pszUIVersionString),
	m_iError( 0),
	m_iSimReportOpt( 0),  // iSimReportOpt),
	m_iSimErrorOpt( 0),  // iSimErrorOpt),
//	m_lStdMixedFuelRunReqd( 0),  // lStdMixedFuelRunReqd),
//	m_lPrelimPropRunReqd( 0),  // lPrelimPropRunReqd),
//	m_lPropFlexRunReqd( 0),  // lPropFlexRunReqd),
	m_iNumOpenGLErrors(0),
	m_iNumProgressRuns(-1),
	m_iSimProgressMonth( 0),	// SAC 2/17/19
	m_dEPlusVersion( -1)		// SAC 3/1/19
{
	if (iNumRuns > 0)
		m_iNumRuns = iNumRuns;
	else
		m_iNumRuns = 1;
//	{	m_iNumRuns = (bFullComplianceAnalysis ? (lAllOrientations > 0 ? 5 : 2) : 1);
//		if (m_lPropFlexRunReqd > 0)		// SAC 8/3/17
//			m_iNumRuns++;
//		if (m_lPrelimPropRunReqd > 0)		// SAC 12/29/17
//			m_iNumRuns += (lAllOrientations > 0 ? 4 : 1);
//		if (lAnalysisType > 0 /*bFullComplianceAnalysis*/ && m_lDesignRatingRunID > 0)		// SAC 3/27/15
//			m_iNumRuns++;
//		if (m_lStdMixedFuelRunReqd > 0)		// SAC 4/5/17
//			m_iNumRuns++;  //+= (lAllOrientations > 0 ? 4 : 1);
//	}
}		// EPlusRunMgr::EPlusRunMgr

EPlusRunMgr::~EPlusRunMgr()
{	DeleteRuns();
}

void EPlusRunMgr::DeleteRuns()
{	EPlusRun* pEPlusRun = NULL;
	while (!m_vEPlusRun.empty())
	{	pEPlusRun = m_vEPlusRun.back();
		m_vEPlusRun.pop_back();
		delete pEPlusRun;
	}
}

static int ExecuteNow( EPlusRunMgr* pRunMgr, QString sEXEFN, QString sEXEParams )
{
			int iExitCode = -99;
			bool bRunOK = true;
			exec_stream_t* pES=NULL;
			try
			{	
				pES = new exec_stream_t( sEXEFN.toLocal8Bit().constData(), sEXEParams.toLocal8Bit().constData(), CREATE_NO_WINDOW );
				//EPlusRun.SetExecStream( pES);
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


int EPlusRunMgr::SetupRun(
	int iRunIdx, QString sRunAbbrev, QString sIDFPathFile, QString sEPlusWthr,
	bool bHourlySim, long lProgressModel, QString& sErrorMsg, const char* pszEPlusIDDFN /*=NULL*/ )      // SAC 10/04/21
//	int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile /*=true*/,		// SAC 4/29/15 - add argument to DISABLE report include files
//	const char* pszRunAbbrev /*=NULL*/ )
{
	int iRetVal = 0;
	EPlusRun* pEPlusRun = new EPlusRun;
	m_vEPlusRun.push_back( pEPlusRun);
	QString sMsg, sLogMsg;
//	BOOL bLastRun = (iRunIdx == (m_iNumRuns-1));
//	BOOL bIsStdDesign = (iRunType == CRM_StdDesign);	// SAC 3/27/15 - was:  (iRunIdx > 0 && bLastRun);  // SAC 7/3/13 - consolidated some logic to identify 
//	pEPlusRun->SetRunType( iRunType);							// SAC 3/27/15
//	pEPlusRun->SetLastRun( bLastRun);
//	pEPlusRun->SetIsStdDesign( bIsStdDesign);

//	QString sRunID, sRunIDProcFile, sRunAbbrev;
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunID"         ),  sRunID         );
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunIDProcFile" ),  sRunIDProcFile );
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunAbbrev"     ),  sRunAbbrev     );

	pEPlusRun->SetRunNumber( iRunIdx );  // lRunNumber);
//	pEPlusRun->SetRunID( sRunID);
//	pEPlusRun->SetRunIDProcFile( sRunIDProcFile);
	pEPlusRun->SetRunAbbrev( sRunAbbrev );
	pEPlusRun->SetHourlySimulation( bHourlySim );
	pEPlusRun->SetProgressModel( lProgressModel );

	if (iRetVal == 0 && (m_sModelPathOnly.length() + sRunAbbrev.length() + 26) > _MAX_PATH)
	{	sErrorMsg = QString( "ERROR:  EPlus processing path too long:  %1%2\\EnergyPlus\\*.*" ).arg( m_sModelPathOnly, sRunAbbrev );
		iRetVal = 73;		// EnergyPlus processing path/filename too long
	}
	else if (!FileExists( sIDFPathFile ))
	{	sErrorMsg = QString( "ERROR:  EPlus IDF file not found:  %1" ).arg( sIDFPathFile );
		iRetVal = 74;		// Error copying EnergyPlus simulation input file to processing directory
	}

//	if (iRetVal == 0 && iRunIdx == 0 && m_bInitHourlyResults)  // only initialize hourly results for first simulation??
//		BEMPX_InitializeHourlyResults();

//	QString sProjFileAlone = m_sModelFileOnlyNoExt + sRunIDProcFile;
	if (iRetVal == 0)
	{
//		QString sOutFiles[EPlusRun::OutFileCOUNT];
//		if (iRetVal == 0)
//		{	sOutFiles[EPlusRun::OutFileCSV] = m_sModelPathOnly + sRunAbbrev + ".csv";
//			sOutFiles[EPlusRun::OutFileREP] = m_sModelPathOnly + sRunAbbrev + ".rep";
//			sOutFiles[EPlusRun::OutFileERR] = m_sModelPathOnly + sRunAbbrev + ".err";
//			pEPlusRun->SetOutFile( sOutFiles[EPlusRun::OutFileCSV], EPlusRun::OutFileCSV);
//			pEPlusRun->SetOutFile( sOutFiles[EPlusRun::OutFileREP], EPlusRun::OutFileREP);
//			pEPlusRun->SetOutFile( sOutFiles[EPlusRun::OutFileERR], EPlusRun::OutFileERR);
//
//			static const char* pszOutFileDescs[] = { "CSV output", "REP output", "Error output" };
//			int i=0;
//			for (; (i<EPlusRun::OutFileCOUNT && iRetVal == 0); i++)
//			{	sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
//							"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
//								 "(once the file is closed), or \n'Abort' to abort the analysis." ).arg( pszOutFileDescs[i], sOutFiles[i] );
//				if (!OKToWriteOrDeleteFile( sOutFiles[i].toLocal8Bit().constData(), sMsg, m_bSilent ))
//				{	if (m_bSilent)
//						sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
//					else
//						sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( pszOutFileDescs[i], sOutFiles[i] );
//					iRetVal = BEMAnal_CECRes_SimOutWriteError;
//				}
//				// code to DELETE existing results files prior to simulation
//				else if (FileExists( sOutFiles[i].toLocal8Bit().constData() ))
//					DeleteFile( sOutFiles[i].toLocal8Bit().constData() );
//			}
//		}

		QString sEPlusProcPath = m_sModelPathOnly;
// TEMPORARY - while testing
//				sEPlusProcPath += "-";
		sEPlusProcPath += QString( "%1\\" ).arg( sRunAbbrev );
		if (!DirectoryExists( sEPlusProcPath ))
			CreateAndChangeDirectory( sEPlusProcPath.toLocal8Bit().constData(), FALSE );
		if (!DirectoryExists( sEPlusProcPath ))
		{	// ERROR
		}
		else
		{	sEPlusProcPath += "EnergyPlus\\";
			if (!DirectoryExists( sEPlusProcPath ))
				CreateAndChangeDirectory( sEPlusProcPath.toLocal8Bit().constData(), FALSE );
			if (!DirectoryExists( sEPlusProcPath ))
			{	// ERROR
			}
			else
			{	// Copy IDF & weather files into processing directory
				QString sDestIDF, sDestWthr;	int i;
				sDestIDF		= QString( "%1in.idf" ).arg( sEPlusProcPath );
				sDestWthr	= QString( "%1in.epw" ).arg( sEPlusProcPath );
				//sDestWthr	= m_sModelPathOnly + sEPlusWthr.right( sEPlusWthr.length() - sEPlusWthr.lastIndexOf('\\') - 1 ); // "CTZ12S13.CSW";
				pEPlusRun->SetProcessPath( sEPlusProcPath );
				const char* pszFileDescs[] = {	"EPlus input", 	"EPlus weather", 	};
				QString* psaCopySrc[ ] = { 		&sIDFPathFile,  	&sEPlusWthr,  		NULL	};
				QString* psaCopyDest[] = {			&sDestIDF, 			&sDestWthr, 		};
				int      iaCopyError[] = {			74, 					75, 					};
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
						iRetVal = iaCopyError[i];
					}
				}
		}	}

		if (iRetVal == 0)
			iRetVal = SetupRunFinish( iRunIdx, sErrorMsg, pszEPlusIDDFN );
	}
	return iRetVal;
}		// EPlusRunMgr::SetupRun

//-----------------------------------------------------------------------------
int EPlusRunMgr::SetupRunFinish(
	int iRunIdx, QString& sErrorMsg, const char* pszEPlusIDDFN /*=NULL*/ )
{
	int iRetVal = 0;
	QString sMsg, sLogMsg;

	EPlusRun* pEPlusRun = (iRunIdx < (int) m_vEPlusRun.size() ? m_vEPlusRun[iRunIdx] : NULL);
	if (pEPlusRun == NULL)
	{	assert( false );
		return BEMAnal_CECRes_SimInputWriteError;
	}

////	long lRunNumber;
//	QString sRunID, sRunIDProcFile, sRunAbbrev;
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunID"         ),  sRunID         );
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunIDProcFile" ),  sRunIDProcFile );
//	BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunAbbrev"     ),  sRunAbbrev     );
//
//	QString sProjFileAlone = m_sModelFileOnlyNoExt + sRunIDProcFile;

		if (iRetVal == 0 && m_bPerformSimulations && !m_bBypassEPlus)
		{
         char pszIDDFN[64];
         if (pszEPlusIDDFN && strlen( pszEPlusIDDFN ) > 0)     // SAC 10/04/21
            strcpy_s( pszIDDFN, 64, pszEPlusIDDFN );
         else
            strcpy_s( pszIDDFN, 64, "Energy+.idd" );
//			// remove trailing '.cse' file extension from path/file passed into CSE
//			QString sProjCSEFileForArg = sProjCSEFile;
//			if (!sProjCSEFileForArg.right(4).compare(".CSE", Qt::CaseInsensitive))
//				sProjCSEFileForArg = sProjCSEFileForArg.left( sProjCSEFileForArg.length()-4 );

//			// EPlus SIMULATION
//			QString sParams;
//			//	sParams = QString( "-b \"%s.cse\"" ).arg( sProjFileAlone );		// SAC 8/20/12 - added '-b' (batch) option to prevent user prompt in the event of sim error
//			sParams = QString( "-b \"%1\"" ).arg( sProjCSEFileForArg );
			QString sProcessPath = pEPlusRun->GetProcessPath();
			sProcessPath = sProcessPath.left( sProcessPath.length()-1 );
			sProcessPath.replace( '\\', '/' );
			QString sParams;
			//sParams = QString( "-d \"%1\" -i \"%2Energy+.idd\" -w \"%3/in.epw\" \"%4/in.idf\"" ).arg(
			sParams = QString( "-d \"%1\" -i \"%2%3\" -w \"%4/in.epw\" \"%5/in.idf\"" ).arg(
											sProcessPath, m_sEPlusPath, pszIDDFN, sProcessPath, sProcessPath );
// C:\dev\CBECC-dev\bin\Release_VC12\EPlus\energyplus -d "C:/dev/CBECC-dev/bin/Com/Projects/test/CmdLine/5" -i "C:\dev\CBECC-dev\bin\Release_VC12\EPlus\Energy+.idd" -w "C:/dev/CBECC-dev/bin/Com/Projects/test/CmdLine/5/in.epw" "C:/dev/CBECC-dev/bin/Com/Projects/test/CmdLine/5/in.idf" >>epout.txt

#ifdef _DEBUG  //VS19
			sLogMsg = QString( "   EPlus exePath:  %1" ).arg( m_sEPlusPath );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			sLogMsg = QString( "   EPlus cmdLine:  %1" ).arg( sParams );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
#endif  //VS19
			pEPlusRun->SetArgs( sParams);
		}

	return iRetVal;
}		// EPlusRunMgr::SetupRunFinish

//-----------------------------------------------------------------------------
void EPlusRunMgr::DoRuns()
{
	EPlusRun* pEPlusRun = NULL;
	for(size_t iRun = 0; iRun < m_vEPlusRun.size(); ++iRun)
	{	pEPlusRun = m_vEPlusRun[iRun];
		StartRun( *pEPlusRun);
		m_vEPlusActiveRun.push_back( pEPlusRun);
	}
	MonitorRuns();
}		// EPlusRunMgr::DoRuns

void EPlusRunMgr::DoRunRange( int iFirstRunIdx, int iLastRunIdx )
{
	EPlusRun* pEPlusRun = NULL;		int iNumRuns=0;
	for(size_t iRun = (size_t) iFirstRunIdx; iRun < m_vEPlusRun.size() && iRun <= (size_t) iLastRunIdx; ++iRun)
	{	pEPlusRun = m_vEPlusRun[iRun];
		if (pEPlusRun)
		{	StartRun( *pEPlusRun);
			m_vEPlusActiveRun.push_back( pEPlusRun);
			iNumRuns++;
	}	}		assert( iNumRuns > 0 );
	if (iNumRuns > 0)
		m_iNumProgressRuns = 1;
	MonitorRuns();
	m_iNumProgressRuns = -1;
}		// EPlusRunMgr::DoRunRange

void EPlusRunMgr::MonitorRuns()
{
	EPlusRun* pEPlusRun;
	exec_stream_t* pES = NULL;
	std::string sOut;
	bool bFirstException = true;
	while(m_vEPlusActiveRun.size() > 0)
	{	for(size_t iRun = 0; iRun < m_vEPlusActiveRun.size(); ++iRun)
		{	pEPlusRun = m_vEPlusActiveRun[iRun];
			pES = pEPlusRun->GetExecStream();
			try
			{	if (pES->running())
				{	ProcessRunOutput( pES, iRun, bFirstException);
					Sleep(10);
				}
				else
				{	bool bFirstExceptionX = true;
					while( ProcessRunOutput( pES, iRun, bFirstExceptionX));
					pES->close();
					pEPlusRun->SetExitCode( pES->exit_code());
					m_vEPlusActiveRun.erase(m_vEPlusActiveRun.begin()+iRun);
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
}		// EPlusRunMgr::MonitorRuns

bool EPlusRunMgr::ProcessRunOutput(exec_stream_t* pES, size_t iRun, bool &bFirstException)
{
	assert( pES);
	std::string sOut;
	if (m_bAbortingSims || (sqt_progress && sqt_progress->wasCanceled()))      // check for sqt_progress != NULL - SAC 01/19/25
	{	m_bAbortingSims = true;
		pES->kill(255);
	}
	else
	{	char outLine[256];
		try
		{	std::istream& is = pES->out();

//			is >> sOut;
			is.getline( outLine, 256 );
			if (strlen(outLine) > 0)
				sOut = outLine;

			if (!is.good())
				is.clear();
			if (!sOut.empty())
			{								assert( iRun < m_vEPlusActiveRun.size() );
				if (iRun < m_vEPlusActiveRun.size())
				{	EPlusRun* pEPlusRun = m_vEPlusActiveRun[iRun];
					if (pEPlusRun)
					{
						if (pEPlusRun->StdoutFileNeedingOpen())
							pEPlusRun->OpenStdoutFile( QString( "%1stdout" ).arg( pEPlusRun->GetProcessPath() ) );
						if (pEPlusRun->StdoutFileWriteable())
							pEPlusRun->WriteStdoutString( sOut );

						bool bLogOut = m_bVerbose;
#ifdef _DEBUG  //VS19
						bLogOut = true;  // always log when in debug mode ...?
#endif  //VS19
						if (bLogOut)
						{	QString sLog = QString( "run %1:  %2" ).arg( pEPlusRun->GetRunAbbrev(), sOut.c_str() );
							BEMPX_WriteLogFile( sLog, NULL, FALSE, TRUE, FALSE );
						}

						//sOut = " " + sOut;
						if (sOut.find("EnergyPlus, Version ") != std::string::npos)
						{	if (m_sEPlusVersion.isEmpty())
							{	int iVerStart = (int) sOut.find("EnergyPlus, Version ") + 20;
								int iVerEnd   = (int) sOut.rfind( "," );			assert( iVerEnd > iVerStart );
								if (iVerEnd > iVerStart)
								{	m_sEPlusVersion = sOut.substr( iVerStart, (iVerEnd-iVerStart) ).c_str();
									double dVer[3] = {0.0,0.0,0.0};
									int iFirstDot  = (int) m_sEPlusVersion.indexOf(".");
									int iSecondDot = (int) m_sEPlusVersion.indexOf(".", std::max( iFirstDot+1, 1 ));		assert( iFirstDot < iSecondDot );
									int iHyphen    = (int) m_sEPlusVersion.indexOf("-");			assert( iSecondDot < iHyphen );
									dVer[0] = atof( m_sEPlusVersion.left(iFirstDot).toLocal8Bit().constData() );
									dVer[1] = atof( m_sEPlusVersion.mid(iFirstDot +1, (iSecondDot-iFirstDot-1)).toLocal8Bit().constData() );
									dVer[2] = atof( m_sEPlusVersion.mid(iSecondDot+1, (iHyphen-iSecondDot-1)).toLocal8Bit().constData() );
									if (dVer[1] > 9)
									{	dVer[1] /= 100;
										if (dVer[2] > 9)
											dVer[2] /= 10000;
										else
											dVer[2] /= 1000;
									}
									else
									{	dVer[1] /= 10;
										if (dVer[2] > 9)
											dVer[2] /= 1000;
										else
											dVer[2] /= 100;
									}
									m_dEPlusVersion = dVer[0] + dVer[1] + dVer[2];
		// testing
//		QString sLogTest = QString( "run %1 EPlusVer %2 / %3" ).arg( pEPlusRun->GetRunAbbrev(), m_sEPlusVersion, QString::number(m_dEPlusVersion) );
//		BEMPX_WriteLogFile( sLogTest, NULL, FALSE, TRUE, FALSE );

						}	}	}
						else if (pEPlusRun->GetHourlySimulation() && sOut.find(" Simulation at ") != std::string::npos)
						{	int iMo=0;
							if (     sOut.find(" Simulation at 01") != std::string::npos)	iMo=1;
							else if (sOut.find(" Simulation at 02") != std::string::npos)	iMo=2;
							else if (sOut.find(" Simulation at 03") != std::string::npos)	iMo=3;
							else if (sOut.find(" Simulation at 04") != std::string::npos)	iMo=4;
							else if (sOut.find(" Simulation at 05") != std::string::npos)	iMo=5;
							else if (sOut.find(" Simulation at 06") != std::string::npos)	iMo=6;
							else if (sOut.find(" Simulation at 07") != std::string::npos)	iMo=7;
							else if (sOut.find(" Simulation at 08") != std::string::npos)	iMo=8;
							else if (sOut.find(" Simulation at 09") != std::string::npos)	iMo=9;
							else if (sOut.find(" Simulation at 10") != std::string::npos)	iMo=10;
							else if (sOut.find(" Simulation at 11") != std::string::npos)	iMo=11;
							else if (sOut.find(" Simulation at 12") != std::string::npos)	iMo=12;
							if (iMo > 0)
							{	pEPlusRun->SetSimulationMonth( iMo );
								IncrementSimulationProgress();
						}	}

					//	if (EPlus_ProcessMessage( 0, sOut.c_str(), iRun, this) == EPlus_ABORT)
					//		pES->kill(255);
					//	else if (sOut.find("OpenGL") != std::string::npos)
					//		IncNumOpenGLErrors();
			}	}	}
		}
		catch(exec_stream_t::error_t &e)
		{	if (bFirstException)
			{	std::string sLogMsg=e.what();
				BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
				bFirstException = FALSE;
			}
	}	}
	return !sOut.empty();
}		// EPlusRunMgr::ProcessRunOutput

void EPlusRunMgr::IncrementSimulationProgress()		// SAC 2/17/19
{	int iMinSimMonth=999;
	long lProgModelSum=0;
	for(size_t iRun = 0; iRun < m_vEPlusActiveRun.size(); ++iRun)
	{	EPlusRun* pEPlusRun = m_vEPlusActiveRun[iRun];
		if (pEPlusRun)
		{	lProgModelSum += pEPlusRun->GetProgressModel();
			if (pEPlusRun->GetSimulationMonth() < iMinSimMonth)
				iMinSimMonth = pEPlusRun->GetSimulationMonth();
	}	}
	if (iMinSimMonth < 999 && iMinSimMonth > m_iSimProgressMonth)
	{	m_iSimProgressMonth = iMinSimMonth;

//						QString sLog = QString( "      Increment Sim Progress (%1 models, sum: %2) to month:  %3" ).arg( QString::number(m_vEPlusActiveRun.size()), QString::number(lProgModelSum), QString::number(m_iSimProgressMonth) );
//						BEMPX_WriteLogFile( sLog, NULL, FALSE, TRUE, FALSE );

	//	int iProgressRetVal = NRes_ProgressIncrement( m_iCodeType, BCM_NRP_ComplianceProgressID( m_iProgressType, OSW_NRP_Step_MSim, lProgModelSum /*lModels*/, BCM_NRP_Prog_Jan+iMinSimMonth-1 /*lSimProg*/ ) );
		int iProgressRetVal = (m_iCodeType == CT_T24N ?	CECNRes_ProgressIncrement( BCM_NRP_ComplianceProgressID( m_iProgressType, OSW_NRP_Step_MSim, lProgModelSum /*lModels*/, BCM_NRP_Prog_Jan+iMinSimMonth-1 /*lSimProg*/ ) ) :
																		S901G_ProgressIncrement( 	BCM_NRP_ComplianceProgressID( m_iProgressType, OSW_NRP_Step_MSim, lProgModelSum /*lModels*/, BCM_NRP_Prog_Jan+iMinSimMonth-1 /*lSimProg*/ ) ) );
	//	if (iProgressRetVal == 0)
	//	{	pES->kill(255);
	//	//	ProcessNonResAnalysisAbort( m_iCodeType, OSW_NRP_Step_MSim, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
	//	}
	}
}

void EPlusRunMgr::StartRun(EPlusRun& EPlusRun)
{
	try
	{	QString qsEPlusExe = QString( "%1energyplus.exe" ).arg( m_sEPlusPath );
		exec_stream_t* pES = new exec_stream_t( qsEPlusExe.toLocal8Bit().constData(), EPlusRun.GetArgs().toLocal8Bit().constData(), CREATE_NO_WINDOW);
		EPlusRun.SetExecStream( pES);
	}
	catch(exec_stream_t::error_t &e)
	{	std::string sLogMsg=e.what();
		BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE, TRUE, FALSE );
	}
}		// EPlusRunMgr::StartRun

QString EPlusRunMgr::GetVersionInfo()
{
	QString sVersion;
	if (!m_sEPlusVersion.isEmpty())
		return m_sEPlusVersion;
	else
	{
	DWORD verHandle = NULL;
	UINT size = 0;
	LPBYTE lpBuffer = NULL;
	QString qsEPlusExe = QString( "%1energyplus.exe" ).arg( m_sEPlusPath );
	DWORD verSize = GetFileVersionInfoSize( qsEPlusExe.toLocal8Bit().constData(), &verHandle);
	if (verSize != NULL)
	{
		LPSTR verData = new char[verSize];
		QString qsEPlusName = "energyplus";
		int iLastSlash = std::max( qsEPlusExe.lastIndexOf('\\'), qsEPlusExe.lastIndexOf('/') );
		int iLastDot   =           qsEPlusExe.lastIndexOf('.');
		if (iLastSlash > 0 && iLastDot > (iLastSlash+1))		// SAC 12/4/17 - report EPluss w/ different executable filenames
			qsEPlusName = qsEPlusExe.mid( iLastSlash+1, (iLastDot-iLastSlash-1) );
		if (GetFileVersionInfo( qsEPlusExe.toLocal8Bit().constData(), verHandle, verSize, verData))
		{
			QString sVerNum;  // SAC 11/26/18 - mods to use Product Version STRING if available
			BYTE* lpb;
			if (VerQueryValue( verData, "\\VarFileInfo\\Translation", (void**)&lpb, &size ))
			{	WORD* lpw = (WORD*)lpb;
				std::string sProcVerQuery = boost::str( boost::format( "\\StringFileInfo\\%04x%04x\\ProductVersion" ) % lpw[ 0 ] % lpw[ 1 ] );
				if (VerQueryValue( verData, sProcVerQuery.c_str(), (void**)&lpb, &size ) && size > 0)
				{	sVerNum = (LPCSTR)lpb;
													// testing
													//QString sVerInfo = QString( "   %1 ProductVersion=%2" ).arg( qsEPlusName, (LPCSTR)lpb );
													//BEMPX_WriteLogFile( sVerInfo, NULL, false, TRUE, false );
			}	}
			if (sVerNum.isEmpty() && VerQueryValue( verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size ) && size)
			{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
				if (verInfo->dwSignature == 0xfeef04bd)
				{	int major = HIWORD(verInfo->dwFileVersionMS);
					int minor = LOWORD(verInfo->dwFileVersionMS);
					sVerNum = QString( "%1.%2" ).arg( QString::number(major), QString::number(minor));
													// testing
													//QString sVerInfo = QString( "   %1 VS_FIXEDFILEINFO:  dwFileVersionMS=%2  dwFileVersionLS=%3  dwProductVersionMS=%4  dwProductVersionLS=%5  dwFileDateMS=%6  dwFileDateLS=%7" ).arg( 
													//		qsEPlusName, QString::number( verInfo->dwFileVersionMS ), QString::number( verInfo->dwFileVersionLS ), QString::number( verInfo->dwProductVersionMS ), QString::number( verInfo->dwProductVersionLS ), QString::number( verInfo->dwFileDateMS ), QString::number( verInfo->dwFileDateLS ) );
													//BEMPX_WriteLogFile( sVerInfo, NULL, false, TRUE, false );
			}	}

			if (!sVerNum.isEmpty())
			{	sVersion = QString( "%1 %2" ).arg( qsEPlusName, sVerNum );
				int pathLen = qsEPlusExe.length();
				if (pathLen >=4)
				{	if (_stricmp( qsEPlusExe.right(4).toLocal8Bit().constData(), ".exe") == 0)
						sVersion += " EXE";
					else if (_stricmp( qsEPlusExe.right(4).toLocal8Bit().constData(), ".dll") == 0)
						sVersion += " DLL";
			}	}
		}
		delete[] verData;
	}
	}
	return sVersion;
}

