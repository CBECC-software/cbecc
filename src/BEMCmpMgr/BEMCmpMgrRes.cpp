// BEMCmpMgrRes.cpp : Defines the residential model analysis routines
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

//#include <direct.h>  			// Directory related system routines
//#include <stdio.h>
//#include <io.h>

//#include <QtGui>
// TO DO  #include <openssl/crypto.h>	// SAC 10/16/13

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CSERunMgr.h"
#include "BEMCmpMgrRes.h"
#include "BEMCM_I.h"
#include <fstream>      // fstream
#include "memLkRpt.h"

#define CSE_MULTI_RUN


////////////////////////////////////////////////////////////////////////////////

static int iNumDaysInMonth[12] = {  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };

static int ExportCSVHourlyResultsComparison( const char* pszHourlyResultsPathFile, const char* pszModelName, const char* pszEnduseLabel, 
											const char** apszCompareLabels, const char** apszResEnduses1, const char** apszResEnduses2,
											char* pszErrMsgBuffer/*=NULL*/, int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ );

static inline bool ResRetVal_ContinueProcessing( int iRetVal )		// SAC 12/12/16 - ensure processing not terminated when errors occur that should not jeopardize analysis
{	return (iRetVal == 0 || iRetVal >= BEMAnal_CECRes_MinErrorWithResults);
}

////////////////////////////////////////////////////////////////////////////////
// SAC 9/18/12 - created
// SAC 6/19/13 - 
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:  (refer to list below describing return values from CMX_PerformAnalysis_CECRes()
int CMX_PerformSimulation_CECRes(	const char* pszBEMBasePathFile,
	 											const char* pszRulesetPathFile,
	 											const char* pszCSEEXEPath,
	 											const char* pszCSEWeatherPath,	// required - Proj:WeatherFileName must contain CSE weather filename
	 											const char* pszDHWDLLPath,
	 											const char* pszDHWWeatherPath,    // NULL for CA DLL-based wthr / if specified, Proj:DHWWthrFileName should contain weather filename
	 											const char* pszProcessPath,
	 											const char* pszModelPathFile,
	 											const char* pszLogPathFile,
												HWND hWnd /*=NULL*/,
												BOOL bFullComplianceAnalysis /*=FALSE */,
												const char* pszUIVersionString /*=NULL*/,		// SAC 12/19/12
												BOOL bDisplayProgress /*=FALSE*/,				// SAC 1/15/13
	 											BOOL bLoadModelFile /*=TRUE*/,
	 											BOOL bInitHourlyResults /*=TRUE*/,		// whether or not to initialize hourly results (only for first run of mulitple compliance runs)
	 											BOOL bStoreBEMProcDetails /*=FALSE*/, BOOL bVerbose /*=FALSE*/,
	 											BOOL bPerformRangeChecks /*=TRUE*/, 
												BOOL bPerformSimulations /*=TRUE*/,		// SAC 1/15/13
												BOOL bDurationStats /*=FALSE*/ )
{	QString sAnalysisOptions;
	// add option specification to Options string only if they are not set to the (analysis routine) default value
	if (!bFullComplianceAnalysis)		// default in ...Analysis...() routine switched to TRUE
		sAnalysisOptions = "FullComplianceAnalysis,0,";
	if (!bInitHourlyResults)
		sAnalysisOptions += "InitHourlyResults,0,";
	if (bStoreBEMProcDetails)
		sAnalysisOptions += "StoreBEMProcDetails,1,";
	if (bVerbose)
		sAnalysisOptions += "Verbose,1,";
	if (!bPerformRangeChecks)
		sAnalysisOptions += "PerformRangeChecks,0,";
	if (!bPerformSimulations)
		sAnalysisOptions += "PerformSimulations,0,";
	if (bDurationStats)
		sAnalysisOptions += "DurationStats,1,";

	int iRetVal = CMX_PerformAnalysis_CECRes(	pszBEMBasePathFile, pszRulesetPathFile, pszCSEEXEPath, pszCSEWeatherPath, pszDHWDLLPath, pszDHWWeatherPath,
												pszProcessPath, pszModelPathFile, pszLogPathFile, pszUIVersionString, (bLoadModelFile), 
												(!sAnalysisOptions.isEmpty() ? sAnalysisOptions.toLocal8Bit().constData() : NULL),
												NULL /*pszErrorMsg*/, 0 /*iErrorMsgLen*/, (bDisplayProgress), hWnd );
	return iRetVal;
}


////////////////////////////////////////////////////////////////////////////////
// SAC 6/19/13 - revised calling arguments and function name to be more consistent w/ non-res routine, while adding flexibility to add analysis options w/out updating arguments
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:  (refer to header file for details)
int CMX_PerformAnalysis_CECRes(		const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
												const char* pszProcessingPath, const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString,
												bool bLoadModelFile /*=true*/, const char* pszOptionsCSV /*=NULL*/, char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/,
												bool bDisplayProgress /*=false*/, HWND /*hWnd=NULL*/ )
{	return CMX_PerformAnalysisCB_CECRes(	pszBEMBasePathFile, pszRulesetPathFile, pszCSEEXEPath, pszCSEWeatherPath, pszDHWDLLPath, pszDHWWeatherPath, pszProcessingPath,
												pszModelPathFile, pszLogPathFile, pszUIVersionString, bLoadModelFile, pszOptionsCSV, pszErrorMsg, iErrorMsgLen, bDisplayProgress );
}

const char pcCharsNotAllowedInObjNames_CECRes[] = { '"', NULL };	// SAC 8/20/14

////////////////////////////////////////////////////////////////////////////////
// SAC 6/5/14 - replaced previous analysis routine w/ one that accepts a callback function pointer
int CMX_PerformAnalysisCB_CECRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
												const char* pszProcessingPath, const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString,
												bool bLoadModelFile /*=true*/, const char* pszOptionsCSV /*=NULL*/, char* /*pszErrorMsg=NULL*/, int /*iErrorMsgLen=0*/,
												bool bDisplayProgress /*=false*/, PAnalysisProgressCallbackFunc pAnalProgCallbackFunc /*=NULL*/ )
{	int iRetVal = 0, iRV2=0;
	QString sErrorMsg, sLogMsg;
	char pszAnalErrMsg[512];	// SAC 2/23/15

// SAC 1/12/15 - added duration logic and corresponding logging (based on what we do in NonRes analysis)
	boost::posix_time::ptime	tmAnalStartTime = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::ptime	tmMark = tmAnalStartTime;
#define  MAX_TimeArray_Res  6
	double dTimeToPrepModel[]   = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
	double dTimeToProcResults[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
	double dTimeToLoadModel=0.0, dTimeToModelAndSecurityChecks=0.0, dTimeToWriteResultsXML=0.0, dTimeToWriteModelAndHrlyCSVs=0.0, dTimeCSESim=0.0, dTimeDHWSim=0.0, dTimeToReport=0.0, dTimeToOther = 0.0, dTimeOverall=0.0; 

// Parse OptionsCSV string
	QVector<QString> saCSVOptions;
	if (pszOptionsCSV && strlen( pszOptionsCSV ) > 0)
	{	if (ParseCSVRecord( pszOptionsCSV, &saCSVOptions ) < 2)
		{	assert( false );
	}	}
	// original analysis options
	int iVerbose = GetCSVOptionValue( "Verbose", 0,  saCSVOptions );
	bool bVerbose						= (iVerbose > 0);
	bool bFullComplianceAnalysis	= (GetCSVOptionValue( "FullComplianceAnalysis",   1,  saCSVOptions ) > 0);
	bool bFullCompAnalSpecified	= (GetCSVOptionValue( "FullComplianceAnalysis", -10,  saCSVOptions ) != -10);
	bool bInitHourlyResults			= (GetCSVOptionValue( "InitHourlyResults"     ,   1,  saCSVOptions ) > 0);
	bool bStoreBEMProcDetails		= (GetCSVOptionValue( "StoreBEMProcDetails"   ,   0,  saCSVOptions ) > 0);
	bool bPerformRangeChecks		= (GetCSVOptionValue( "PerformRangeChecks"    ,   1,  saCSVOptions ) > 0);
	bool bPerformDupObjNameCheck	= (GetCSVOptionValue( "PerformDupObjNameCheck",   1,  saCSVOptions ) > 0); // SAC 2/23/15
	bool bPerformSimulations		= (GetCSVOptionValue( "PerformSimulations"    ,   1,  saCSVOptions ) > 0);
//	bool bDurationStats				= (GetCSVOptionValue( "DurationStats"         ,   0,  saCSVOptions ) > 0);
	bool bBypassCSE					= (GetCSVOptionValue( "BypassCSE"             ,   0,  saCSVOptions ) > 0);	// options added 6/19/13
	bool bBypassDHW					= (GetCSVOptionValue( "BypassDHW"             ,   0,  saCSVOptions ) > 0);
	bool bIgnoreFileReadErrors		= (GetCSVOptionValue( "IgnoreFileReadErrors"  ,   0,  saCSVOptions ) > 0);	// option added 6/28/13
	bool bComplianceReportPDF		= (GetCSVOptionValue( "ComplianceReportPDF"   ,   0,  saCSVOptions ) > 0);	// options added 8/14/13
	bool bComplianceReportXML		= (GetCSVOptionValue( "ComplianceReportXML"   ,   0,  saCSVOptions ) > 0);
	bool bSilent						= (GetCSVOptionValue( "Silent"                ,   0,  saCSVOptions ) > 0);
	bool bSendRptSignature			= (GetCSVOptionValue( "SendRptSignature"      ,   1,  saCSVOptions ) > 0);
	long lBypassRuleLimits			=  GetCSVOptionValue( "BypassRuleLimits"      ,   0,  saCSVOptions );		// SAC 3/11/14  | SAC 4/20/15 - switched from bool to integer
	bool bBypassValidFileChecks	= (GetCSVOptionValue( "BypassValidFileChecks" ,   0,  saCSVOptions ) > 0);	// SAC 5/3/14
	long iSimSpeedOption  			=	GetCSVOptionValue( "SimSpeedOption"        ,  -1,  saCSVOptions );		// SAC 1/14/15
	int iEnableRptGenStatusChecks =	GetCSVOptionValue( "EnableRptGenStatusChecks", 1,  saCSVOptions );		// SAC 2/20/15
	bool bAllowAnalysisAbort	   = (GetCSVOptionValue( "AllowAnalysisAbort"    ,   1,  saCSVOptions ) > 0);	// SAC 4/5/15
	bool bStoreResultsToModelInput= (GetCSVOptionValue( "StoreResultsToModelInput", 0,  saCSVOptions ) > 0);	// SAC 5/11/15
	bool bStoreDetailedResultsToModelInput= (GetCSVOptionValue( "StoreDetailedResultsToModelInput", 0,  saCSVOptions ) > 0);	// SAC 5/11/15
   long iDHWCalcMethodAnalOpt		=  GetCSVOptionValue( "DHWCalcMethod"         ,  -1,  saCSVOptions );		// SAC 7/15/15
   long lEnableResearchMode		=  GetCSVOptionValue( "EnableResearchMode"    ,   0,  saCSVOptions );		// SAC 5/14/16

	int  iLogWritingMode  			=	GetCSVOptionValue( "LogWritingMode"        , 100,  saCSVOptions );		// SAC 5/20/14
	int  iSimLoggingOption			=	GetCSVOptionValue( "SimLoggingOption"      ,   0,  saCSVOptions );		// SAC 1/12/15
	sbLogCSECallbacks = (iSimLoggingOption == 1 || iSimLoggingOption == 3 || bVerbose);
	bool bLogDHWSim	= (iSimLoggingOption > 1 || bVerbose);
	bool bLogEachFileHashError = (bVerbose || sbLogCSECallbacks || bLogDHWSim);
	int  iSimReportDetailsOption	=	GetCSVOptionValue( "SimReportDetailsOption",   1,  saCSVOptions );		// SAC 11/5/16 - 0: no CSE reports / 1: user-specified reports / 2: entire .rpt file
	int  iSimErrorDetailsOption	=	GetCSVOptionValue( "SimErrorDetailsOption" ,   1,  saCSVOptions );		// SAC 11/5/16 - 0: no CSE errors / 1: always list CSE errors

	bool bCSEIncludeFileUsed = false;	// SAC 12/23/14

	QString sProxyServerAddress, sProxyServerCredentials, sProxyServerType, sNetComLibrary;
	GetCSVOptionString( "ProxyServerAddress"    , sProxyServerAddress    , saCSVOptions );
	GetCSVOptionString( "ProxyServerCredentials", sProxyServerCredentials, saCSVOptions );
	GetCSVOptionString( "ProxyServerType"       , sProxyServerType       , saCSVOptions );
	GetCSVOptionString( "NetComLibrary"         , sNetComLibrary         , saCSVOptions );

	char pszFullPath[_MAX_PATH];	// SAC 2/10/14
	//sLogMsg = QString( "   ProcessingPath = %1 || ModelPathFile = %1" ).arg( pszProcessingPath, pszModelPathFile );	BEMPX_WriteLogFile( sLogMsg );
	//if (_getcwd( pszFullPath, _MAX_PATH ))
	//{	sLogMsg = QString( "   Init working directory: %1" ).arg( pszFullPath );		BEMPX_WriteLogFile( sLogMsg );
	//}
	// SAC 2/10/14 - added code to expand relative path to full/absolute path, since opening of file via relative path in BEMPX_WriteFileFromRulelist() is failing
	if (_fullpath( pszFullPath, pszModelPathFile, _MAX_PATH ) == NULL)
	{	assert( false );
	}
	QString sFullModelPathFile = pszFullPath;

	QString sDebugRuleEvalCSV;		// SAC 12/12/13 - added ability to specify targeted rule eval debug info
	GetCSVOptionString( "DebugRuleEvalCSV", sDebugRuleEvalCSV, saCSVOptions );
	BEMCompNameTypePropArray compRuleDebugInfo;
	void* pCompRuleDebugInfo = NULL;
	if (!sDebugRuleEvalCSV.isEmpty() && FileExists( sDebugRuleEvalCSV.toLocal8Bit().constData() ))
	{	sLogMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to ignore this file." ).arg( "rule evaluation debug", sDebugRuleEvalCSV );
		if (!OKToWriteOrDeleteFile( sDebugRuleEvalCSV.toLocal8Bit().constData(), sLogMsg, bSilent ))
		{	if (bSilent)
				sLogMsg = QString( "ERROR:  Unable to open %1 file:  %2" ).arg( "rule evaluation debug", sDebugRuleEvalCSV );
			else
				sLogMsg = QString( "ERROR:  User chose not to use/reference %1 file:  %2" ).arg( "rule evaluation debug", sDebugRuleEvalCSV );
			BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
		}
      else
		{	int iDbgVerboseFlag=0, iDbgLogRuleListEval=0;
			if (compRuleDebugInfo.ReadData( sDebugRuleEvalCSV.toLocal8Bit().constData(), iDbgVerboseFlag, iDbgLogRuleListEval ))
			{	if (iDbgLogRuleListEval != iVerbose)
				{	iVerbose = iDbgLogRuleListEval;
					bVerbose = (iVerbose > 0);
				}
				pCompRuleDebugInfo = &compRuleDebugInfo;
			}
			else
			{	assert( FALSE );	// error reading rule debug info CSV
	}	}	}

//	BOOL bRuleEvalOK;
	QString sCSEexe, sCSEWthr, sMissing;
	siCallbackCount = 0;		// SAC 11/17/13 - reset CSE message callback counter between each analysis run
	bool bStoreAllowCallbackAbort = sbAllowCallbackAbort;		// SAC 4/5/15
	sbAllowCallbackAbort = bAllowAnalysisAbort;
	mapCSECallback.clear();
	for(int i=0; pszCSEProgressMsgs[i]; i++)
		mapCSECallback[pszCSEProgressMsgs[i]] = 0;
	QString sDHWWthr;
	bool bBEMLogFileSet = false;
	bool bDHWSimViaWthrFile = false;

	bool bRestoreBEMProcLogTimeStampSetting = false;  // SAC 11/17/13
	bool bInitialBEMProcLogTimeStamp = BEMPX_GetLogTimeStamps();
	if ( ( bInitialBEMProcLogTimeStamp && iVerbose == 2) ||
		  (!bInitialBEMProcLogTimeStamp && iVerbose != 2) )		// SAC 11/17/13 - switch log timestamp setting depending on iVerbose setting (if needed)
	{	bRestoreBEMProcLogTimeStampSetting = true;
		BEMPX_EnableLogTimeStamps( (iVerbose != 2) );
	}

	slCurrentProgress = 0;
	// SAC 6/5/14 - new callback mechanism - initialize static function pointer
	assert( spAnalProgCallbackFunc == NULL && slAnalysisProgressCallbackRetVal == 0 );
	if (pAnalProgCallbackFunc)
	{	spAnalProgCallbackFunc = pAnalProgCallbackFunc;
		slAnalysisProgressCallbackRetVal = 0;
	}

// QT Progress Dialog stuff
#ifdef CM_QTGUI
	bool bQtAppInitHere = false;	// SAC 11/11/15
	QVBoxLayout* pqt_layout = NULL;
	QWidget* pqt_win = NULL;
	QProgressDialog* pqt_progress = NULL;
	if (bDisplayProgress)
	{
		sfPctDoneFollowingSimulations = 98;  // SAC 8/19/13 - re-initialize value added to enable slower progress reporting when generating reports

		pqt_layout = new QVBoxLayout;
	//	QVBoxLayout qt_layout();
		//QWidget*  win = new QWidget;
		//QProgressDialog* progress = new QProgressDialog("Fetching data...", "Cancel", 0, 100);
		assert( /*sq_app == NULL &&*/ sqt_win == NULL && sqt_progress == NULL );
		if (sq_app == NULL)
		{	int argc = 0;
			sq_app = new QApplication( argc, NULL );
			bQtAppInitHere = true;
			if (sq_app)
				ssEXEPath = sq_app->applicationDirPath();
		}
		pqt_win = new QWidget;
		siNumProgressErrors = 0;
		SetProgressMessage( " Initializing", false /*bBatchMode*/ );
		pqt_progress = new QProgressDialog( sqProgressMsg, "Abort Analysis", 0, 100 );
		// functions setLabelText() and setCancelButtonText() set the texts shown.
	 
	// QProgressBar {
	//     border: 2px solid grey;
	//     border-radius: 5px;
	// }
	//
	// QProgressBar::chunk {
	//     background-color: #05B8CC;
	//     width: 20px;
	// }
	 
	//	QWidget qt_win();
	//	QProgressDialog qt_progress( "Performing Analysis...", "Cancel", 0, 100 );
		pqt_progress->setWindowModality( Qt::WindowModal );
		pqt_layout->addWidget( pqt_progress, Qt::AlignCenter );
		pqt_win->setLayout( pqt_layout );
	// TESTING
		pqt_win->setAttribute(Qt::WA_DeleteOnClose);
	// TESTING
		pqt_progress->setValue( 0 );
		pqt_win->show();
		sqt_progress = pqt_progress;
		sqt_win = pqt_win;
	}
#else
	bDisplayProgress;
#endif

	QString sBEMBasePathFile	= pszBEMBasePathFile;
	QString sRulesetPathFile	= pszRulesetPathFile;
	QString sCSEEXEPath			= pszCSEEXEPath;
	QString sCSEWeatherPath		= pszCSEWeatherPath;
	QString sDHWDLLPath			= pszDHWDLLPath;
	QString sDHWWeatherPath		= pszDHWWeatherPath;
	QString sProcessPath			= pszProcessingPath;
	QString sModelPathFile		= pszModelPathFile;
	QString sLogPathFile			= pszLogPathFile;
	RelativeToCompletePath_IfNeeded( sBEMBasePathFile );		// revise EACH path to be relative to EXE path (if the path is specified but not complete)
	RelativeToCompletePath_IfNeeded( sRulesetPathFile );
	RelativeToCompletePath_IfNeeded( sCSEEXEPath      );
	RelativeToCompletePath_IfNeeded( sCSEWeatherPath  );
	RelativeToCompletePath_IfNeeded( sDHWDLLPath      );
	RelativeToCompletePath_IfNeeded( sDHWWeatherPath  );
	RelativeToCompletePath_IfNeeded( sProcessPath     );
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	RelativeToCompletePath_IfNeeded( sLogPathFile     );

	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");

	QString sXMLResultsFileName = sModelPathFile;
	if (sXMLResultsFileName.lastIndexOf('.'))
	{	sXMLResultsFileName  = sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') );
		//sXMLResultsFileName += " - following analysis.xml";
		sXMLResultsFileName += " - AnalysisResults.xml";
	}

	QString sCSESimRptOutputFileName, sCSESimErrOutputFileName;	// SAC 11/7/16
	if (iSimReportDetailsOption > 0)
	{	sCSESimRptOutputFileName = sModelPathFile;
		if (sCSESimRptOutputFileName.lastIndexOf('.'))
		{	sCSESimRptOutputFileName  = sCSESimRptOutputFileName.left( sCSESimRptOutputFileName.lastIndexOf('.') );
			sCSESimRptOutputFileName += " - CSE Reports.txt";
		}
		// make sure file writeable, and if it is and present, delete it before continuing analysis
		sLogMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to ignore this file." ).arg( "CSE report output", sCSESimRptOutputFileName );
		if ( !OKToWriteOrDeleteFile( sCSESimRptOutputFileName.toLocal8Bit().constData(), sLogMsg, bSilent ) ||
			  (FileExists( sCSESimRptOutputFileName ) && !DeleteFile( sCSESimRptOutputFileName.toLocal8Bit().constData() )) )
		{	sLogMsg = QString( "Warning:  CSE report output cannot be overwritten and will not be updated for this analysis:  %1" ).arg( sCSESimRptOutputFileName );
			BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
			sCSESimRptOutputFileName.clear();
		}
	}
	if (iSimErrorDetailsOption > 0)
	{	sCSESimErrOutputFileName = sModelPathFile;
		if (sCSESimErrOutputFileName.lastIndexOf('.'))
		{	sCSESimErrOutputFileName  = sCSESimErrOutputFileName.left( sCSESimErrOutputFileName.lastIndexOf('.') );
			sCSESimErrOutputFileName += " - CSE Errors.txt";
		}
		// make sure file writeable, and if it is and present, delete it before continuing analysis
		sLogMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to ignore this file." ).arg( "CSE error output", sCSESimErrOutputFileName );
		if ( !OKToWriteOrDeleteFile( sCSESimErrOutputFileName.toLocal8Bit().constData(), sLogMsg, bSilent ) ||
			  (FileExists( sCSESimErrOutputFileName ) && !DeleteFile( sCSESimErrOutputFileName.toLocal8Bit().constData() )) )
		{	sLogMsg = QString( "Warning:  CSE error output cannot be overwritten and will not be updated for this analysis:  %1" ).arg( sCSESimErrOutputFileName );
			BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
			sCSESimErrOutputFileName.clear();
		}
	}

//	BEMPX_GetRulesetErrorCount();  // SAC 1/9/13
	BEMPX_ClearRulesetErrors();  // SAC 1/9/13

// debugging
//sLogMsg = QString( "File paths being checked:\n   EXE: %1\n   CSE EXE: %2" ).arg( ssEXEPath, sCSEEXEPath );
//BEMMessageBox( sLogMsg , "Res File Path check");

   if (!DirectoryExists( sCSEEXEPath ))
	{	if (sCSEEXEPath.isEmpty())
			sErrorMsg = "ERROR:  CSE (California simulation engine) path not specified";
		else
			sErrorMsg = QString( "ERROR:  Path to CSE (California simulation engine) not found:  %1" ).arg( sCSEEXEPath );
		iRetVal = BEMAnal_CECRes_EXEPathInvalid;
	}
   else if (!DirectoryExists( sCSEWeatherPath ))
	{	if (sCSEWeatherPath.isEmpty())
			sErrorMsg = "ERROR:  CSE weather file path not specified";
		else
			sErrorMsg = QString( "ERROR:  Path to CSE weather file not found:  %1" ).arg( sCSEWeatherPath );
		iRetVal = BEMAnal_CECRes_WthrPathInvalid;
	}
// SAC 9/25/16 - remove dependence on Title-24 DHW DLLs
//   else if (!DirectoryExists( sDHWDLLPath ))
//	{	if (sDHWDLLPath.isEmpty())
//			sErrorMsg = "ERROR:  CEC Title-24 DHW simulation engine DLL path not specified";
//		else
//			sErrorMsg = QString( "ERROR:  Path to the CEC Title-24 DHW simulation engine DLLs not found:  %1" ).arg( sDHWDLLPath );
//		iRetVal = BEMAnal_CECRes_DHWPathInvalid;
//	}
	else
	{
#if defined( CSE_MULTI_RUN)
#ifdef _DEBUG
		sCSEexe      = sCSEEXEPath + "csed.exe";
#else
		sCSEexe      = sCSEEXEPath + "cse.exe";
#endif
//#else
//#ifdef _DEBUG
//		sCSEexe      = sCSEEXEPath + "csed.dll";
//#else
//		sCSEexe      = sCSEEXEPath + "cse.dll";
//#endif
#endif
//		sCSEashwat   = sCSEEXEPath + "ashwat.dll";
//		sT24DHWdll   = sDHWDLLPath + "T24DHW.dll";
//		sT24ASM32dll = sDHWDLLPath + "T24ASM32.dll";
//		sT24TDVdll   = sDHWDLLPath + "T24TDV.dll";
//		sT24UNZIPdll = sDHWDLLPath + "T24UNZIP.dll";
//		sT24WTHRdll  = sDHWDLLPath + "T24WTHR.dll";
		if (!FileExists( sCSEexe.toLocal8Bit().constData() ))
			sMissing += "\n   " + sCSEexe;
//		if (!FileExists( sCSEashwat.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sCSEashwat;
//		if (!FileExists( sT24DHWdll.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sT24DHWdll;
//		if (!FileExists( sT24ASM32dll.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sT24ASM32dll;
//		if (!FileExists( sT24TDVdll.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sT24TDVdll;
//		if (!FileExists( sT24UNZIPdll.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sT24UNZIPdll;
//		if (!FileExists( sT24WTHRdll.toLocal8Bit().constData() ))
//			sMissing += "\n   " + sT24WTHRdll;
		if (!sMissing.isEmpty())
		{	sErrorMsg = "ERROR:  The following required file(s) were not found:" + sMissing;
			iRetVal = BEMAnal_CECRes_MissingFiles;
		}
	}

//#ifndef CSE_MULTI_RUN
//	if (ResRetVal_ContinueProcessing( iRetVal ) && !LoadCSEDLLs( sCSEexe, sCSEashwat ))
//	{	sErrorMsg = QString( "ERROR:  Unable to load CSE DLL: %1" ).arg( sCSEexe );
//		iRetVal = BEMAnal_CECRes_ErrorLoadingCSE;
//	}
//#endif
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

	if (ResRetVal_ContinueProcessing( iRetVal ) && !sBEMBasePathFile.isEmpty())
	{	assert( !sRulesetPathFile.isEmpty() );  // if (re)loading BEMBase, we must also reload ruleset
		if (!FileExists( sBEMBasePathFile.toLocal8Bit().constData() ))
		{	sErrorMsg = QString( "ERROR:  BEMBase (building data model) definitions file not found:  %1" ).arg( sBEMBasePathFile );
			iRetVal = BEMAnal_CECRes_BEMBaseNotFound;
		}
		else if (sRulesetPathFile.isEmpty() || !FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
		{	sErrorMsg = QString( "ERROR:  BEM ruleset file not found:  %1" ).arg( (!sRulesetPathFile.isEmpty() ? sRulesetPathFile : "(not specified)") );
			iRetVal = BEMAnal_CECRes_RulesetNotFound;
		}
		else if (!CMX_LoadDataModel( sBEMBasePathFile.toLocal8Bit().constData(), BEMT_CBECC ))	// was: CMX__ReInitBEMProc( sBEMBasePathFile, BEMT_CBECC ))
		{	sErrorMsg = QString( "ERROR:  BEMBase (building data model) (re)initialization:  %1" ).arg( sBEMBasePathFile );
			iRetVal = BEMAnal_CECRes_BEMProcInitError;
		}
	}

	if (ResRetVal_ContinueProcessing( iRetVal ) && !sRulesetPathFile.isEmpty())
	{	if (!FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
		{	sErrorMsg = QString( "ERROR:  BEM ruleset file not found:  %1" ).arg( sRulesetPathFile );
			iRetVal = BEMAnal_CECRes_RulesetNotFound;
		}
		else if (!CMX_LoadRuleset( sRulesetPathFile.toLocal8Bit().constData() ))
		{	sErrorMsg = QString( "ERROR:  Ruleset loading error encountered:  %1" ).arg( sRulesetPathFile );
			iRetVal = BEMAnal_CECRes_RulesetInitError;
		}
	}

	int iDLLCodeYear = 2013;		// SAC 11/19/15
#ifdef CODEYEAR2016
	    iDLLCodeYear = 2016;
#endif

	bool bAnalysisPriorToRptGenOK = false;
	long lDesignRatingRunID = 0;  // SAC 3/27/15
	bool bDHWCalcMethodUserSpecified = false;
	int iRulesetCodeYear = 0;
	if (ResRetVal_ContinueProcessing( iRetVal ))
	{
	//
	//	-----  BEMBase & ruleset loaded/initialized  -----
	// 

		if (!sLogPathFile.isEmpty())
		{	if (sLogPathFile.length() > BEMDEF_MAXLOGFILELINE)
			{	sErrorMsg = QString( "ERROR:  Processing log path/file exceeds maximum length of %1:  %2" ).arg( QString::number(BEMDEF_MAXLOGFILELINE), sLogPathFile );
				iRetVal = BEMAnal_CECRes_InvalidLogFile;
			}
			else if (!BEMPX_WriteLogFile( "checking log file access", sLogPathFile.toLocal8Bit().constData(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
			{	sErrorMsg = QString( "ERROR:  Error encountered writing message to log file:  %1" ).arg( sLogPathFile );
				iRetVal = BEMAnal_CECRes_LogFileWriteError;
			}
		}

	// SAC 3/11/16 - moved declaration of xmlResultsFile up here before model loading in order to be able to write User model to the file BEFORE modifying the project w/ analysis settings
		BEMXMLWriter xmlResultsFile( ((ResRetVal_ContinueProcessing( iRetVal ) && !sXMLResultsFileName.isEmpty()) ? sXMLResultsFileName.toLocal8Bit().constData() : NULL) );
		bool bFirstModelCopyCreated = false;

		if (ResRetVal_ContinueProcessing( iRetVal ) && bLoadModelFile)
		{	// assumes BEMBase cleared out and ruleset re-loaded
			if (sModelPathFile.isEmpty() || !FileExists( sModelPathFile.toLocal8Bit().constData() ))
			{	sErrorMsg = QString( "ERROR:  Building model (project) file not found:  %1" ).arg( (!sModelPathFile.isEmpty() ? sModelPathFile : "(not specified)") );
				iRetVal = BEMAnal_CECRes_ModelFileNotFound;
			}
   		else
			{
			// SAC 6/28/13 - code to detect (and possibly abort due to) errors encountered reading project file
			   int iBEMErr;
				// enable the UI reporting of all (up to MAX_BEMBASE_DATA_SET_ERRORS) BEMBase project file data setting errors
			   int iaFailedBEMBaseDBIDs[   MAX_BEMBASE_DATA_SET_ERRORS ];
			   int iaFailedBEMBaseObjIdxs[ MAX_BEMBASE_DATA_SET_ERRORS ];  // facilitate more informative error reporting
			   for (iBEMErr=0; iBEMErr<MAX_BEMBASE_DATA_SET_ERRORS; iBEMErr++)
			   {
			      iaFailedBEMBaseDBIDs[iBEMErr] = 0;
			      iaFailedBEMBaseObjIdxs[iBEMErr] = -1;
			   }
			   QStringList saFailedBEMBaseData;  // facilitate more informative error reporting

				bool bKeepLogFileOpen = false;
				switch (iLogWritingMode)
				{	case  0 :	bKeepLogFileOpen = false;		break;
					case  1 :	bKeepLogFileOpen = true;		break;
					default :	bKeepLogFileOpen = (bVerbose || pCompRuleDebugInfo != NULL);		break;
				}
				QStringList saWarningsForUser;	// SAC 7/8/14 - added to track issues (not designated as read failures, but worthy of logging)
				if (CMX_LoadModel( NULL, NULL, sModelPathFile.toLocal8Bit().constData(), MAX_BEMBASE_DATA_SET_ERRORS, iaFailedBEMBaseDBIDs, true /*bSupressAllMsgBoxes*/,  // SAC 5/1/14 - supress msgboxes
											iaFailedBEMBaseObjIdxs, &saFailedBEMBaseData, false /*bLogDurations*/, sLogPathFile.toLocal8Bit().constData(), bKeepLogFileOpen, &saWarningsForUser ) != 0)
				{	// deal with or simply report failure of model file open
					sErrorMsg = QString( "ERROR:  Error encountered reading building model (project) file:  %1" ).arg( sModelPathFile );
					iRetVal = BEMAnal_CECRes_ModelInitError;
				}
				else if (!bIgnoreFileReadErrors)
				{	int iNumBEMBaseErrors = 0;
				   for (iBEMErr=0; iBEMErr<MAX_BEMBASE_DATA_SET_ERRORS; iBEMErr++)
					{	if (iaFailedBEMBaseDBIDs[iBEMErr] > 0)
							iNumBEMBaseErrors++;
					}
					if (iNumBEMBaseErrors > 0)
					{	sErrorMsg = QString( "ERROR:  %1 Error(s) encountered reading building model (project) file:  %2" ).arg( QString::number(iNumBEMBaseErrors), sModelPathFile );
						iRetVal = BEMAnal_CECRes_ModelReadError;
					}
				}
				if (saWarningsForUser.size() > 0)	// SAC 7/8/14 - log file-read issues not designated as failures, but worthy of logging
				{	for (int iFRWIdx=0; iFRWIdx < saWarningsForUser.size(); iFRWIdx++)
						BEMPX_WriteLogFile( saWarningsForUser[iFRWIdx], NULL /*sLogPathFile*/, FALSE /*bBlankFile*/,
													TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}

// ??? evaluate FileOpen rulelist to address backward compatibility issues ???
				if (ResRetVal_ContinueProcessing( iRetVal ))
				{	bBEMLogFileSet = TRUE;
					iRV2 = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropInpError, "ProposedInput", bVerbose, pCompRuleDebugInfo );
					if (iRV2 > 0)
						iRetVal = iRV2;
				}

		   // write user model to XML results file		- SAC 3/11/16 - moved up from below to better handle bLoadModelFile scenario
				if (ResRetVal_ContinueProcessing( iRetVal ) && !sXMLResultsFileName.isEmpty())  // SAC 2/19/13 - added to export the USER INPUT model to XML results file
				{
								dTimeToLoadModel += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
					// SAC 4/16/14 - modified call to WriteModel() to cause only valid INPUTs to be written to user input model
					BOOL bXMLInputWriteOK = xmlResultsFile.WriteModel( FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, "User Input" /*pszModelName*/, -1 /*iBEMProcIdx*/, true /*bOnlyValidInputs*/ );
																assert( bXMLInputWriteOK );
								dTimeToWriteResultsXML += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
				}

			// create first COPY of user input model, so that the first model loaded into memory doesn't include any data that we would not want written to an updated User Input written @ end of analysis (SAC 5/12/15)
				if (ResRetVal_ContinueProcessing( iRetVal ))		// SAC 3/11/16 - moved up from below to better handle bLoadModelFile scenario
				{	BEMPX_AddModel( 0 /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
					bFirstModelCopyCreated = true;
				}

			// handle BypassRuleLimits option - when > 0 should cause certain rule-based compliance checks/limits to be bypassed
				if (lBypassRuleLimits > 0)		// SAC 3/11/16 - moved up from below to better handle bLoadModelFile scenario
				   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BypassRuleLimits" ), BEMP_Int, (void*) &lBypassRuleLimits );

			// handle SimSpeedOption property/option - when >= 0 should force use of the specified selection
				if (iSimSpeedOption >= 0)		// SAC 3/11/16 - moved up from below to better handle bLoadModelFile scenario
	   		   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SimSpeedOption" ), BEMP_Int, (void*) &iSimSpeedOption );

			// handle DHWCalcMethod analysis option
				if (iDHWCalcMethodAnalOpt >= 0)		// SAC 3/11/16 - moved up from below to better handle bLoadModelFile scenario
	   		   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:DHWCalcMethod" ), BEMP_Int, (void*) &iDHWCalcMethodAnalOpt );

			// handle EnableResearchMode option - SAC 5/14/16
				if (lEnableResearchMode > 0)	
				   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:EnableResearchMode" ), BEMP_Int, (void*) &lEnableResearchMode );

				if (ResRetVal_ContinueProcessing( iRetVal ))
				{	iRV2 = LocalEvaluateRuleset( sErrorMsg, BEMAnal_CECRes_EvalPropInpError, "ProposedInput", bVerbose, pCompRuleDebugInfo );
					if (iRV2 > 0)
						iRetVal = iRV2;
				}
				BEMPX_RefreshLogFile();	// SAC 5/19/14

			// store certain data only required when project file loaded during analysis
				if (ResRetVal_ContinueProcessing( iRetVal ))
				{
				   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ProjFileName" ), BEMP_QStr, (void*) &sModelFileOnly, BEMO_User, 0, BEMS_ProgDefault );
				}
			}
		}
						dTimeToLoadModel += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

	// SAC 8/20/14 - added to ensure valid object names prior to performing analysis
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	QString sObjNameViolationMsg;
			int iNumObjNameViolations = BEMPX_CheckObjectNames( (char*) pcCharsNotAllowedInObjNames_CECRes, sObjNameViolationMsg, -1 /*iBEMProcIdx*/ );			iNumObjNameViolations;
																// BOOL bAllowTrailingSpaces=TRUE, BOOL bPerformRenames=TRUE, BOOL bLogRenames=TRUE );

		// SAC 11/19/15 - added logic to extract code year out of ruleset label
			QString sLoadedRuleSetID, sLoadedRuleSetVer;
			if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))	// SAC 10/2/14 - RESET iCodeType based on newly loaded ruleset
			{	int iCdYrIdx = sLoadedRuleSetID.indexOf( "20" );
				if (iCdYrIdx > 0)
					 iCdYrIdx = sLoadedRuleSetID.indexOf( " 20" ) + 1;
				if (iCdYrIdx >= 0)
				{	iRulesetCodeYear = atoi( sLoadedRuleSetID.mid( iCdYrIdx, 4 ).toLocal8Bit().constData() );
					assert( iRulesetCodeYear >= 2000 );
				}
										if (bVerbose)
										{	sLogMsg = QString( "  PerfAnal_CECRes - Analysis DLL CodeYear %1 / Ruleset CodeYear %2" ).arg( QString::number(iDLLCodeYear), QString::number(iRulesetCodeYear) );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
			}
		}

	// Check fairly wide variety of file hashes for supporting files - some required, some not - if inconcistencies found, log them and turn OFF report signature use
		int iError;
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	if (bBypassValidFileChecks)
				BEMPX_WriteLogFile( "  PerfAnal_CECRes - Bypassing file validity checks", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/,
												TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			else
			{	QString sFHPathFile, sFHErrMsg; 
				int iNumFileHashErrs = 0;
				bool bRequiredForCodeYear = true;	// SAC 11/19/15
				for (long iFHID=101; (ResRetVal_ContinueProcessing( iRetVal ) && iFHID <= 117); iFHID++)		// SAC 3/17/16 - removed T24DHW DLLs and revised numbering
				{	bRequiredForCodeYear = true;
					switch (iFHID)
					{	case 101 :	BEMPX_GetBEMBaseFile( sFHPathFile );              bRequiredForCodeYear = (iDLLCodeYear < 2016);		break;
						case 102 :	sFHPathFile = ssEXEPath + "BEMCmpMgr13r.dll";     bRequiredForCodeYear = (iDLLCodeYear < 2016);		break;
						case 103 :	sFHPathFile = ssEXEPath + "BEMCmpMgr_noui.dll";   bRequiredForCodeYear = false;							break;		// ignore this file from here on out
						case 104 :	sFHPathFile = ssEXEPath + "BEMProc13r.dll";       bRequiredForCodeYear = (iDLLCodeYear < 2016);		break;
						case 105 :	sFHPathFile = ssEXEPath + "libeay32.dll";         bRequiredForCodeYear = false;  						break;		// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
						case 106 :	sFHPathFile = ssEXEPath + "ssleay32.dll";         bRequiredForCodeYear = false;						   break;		// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
						case 107 :	sFHPathFile = ssEXEPath + "Qt5Cored.dll";         break;
						case 108 :	sFHPathFile = ssEXEPath + "Qt5Guid.dll";          break;
						case 109 :	sFHPathFile = ssEXEPath + "Qt5Xmld.dll";          break;
						case 110 :	sFHPathFile = ssEXEPath + "Qt5Core.dll";          break;
						case 111 :	sFHPathFile = ssEXEPath + "Qt5Gui.dll";           break;
						case 112 :	sFHPathFile = ssEXEPath + "Qt5Xml.dll";           break;
						case 113 :  sFHPathFile = sCSEexe;                            break;
						case 114 :  /*sFHPathFile = sCSEashwat;*/                         bRequiredForCodeYear = false;						   break;
					//	case 31 :   sFHPathFile = sT24WTHRdll;                        break;
					//	case 32 :   sFHPathFile = sT24DHWdll;                         break;
					//	case 33 :   sFHPathFile = sT24ASM32dll;                       break;
					//	case 34 :   sFHPathFile = sT24TDVdll;                         break;
					//	case 35 :   sFHPathFile = sT24UNZIPdll;                       break;
						case 115 :	sFHPathFile = ssEXEPath + "BEMCmpMgr16r.dll";     bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
						case 116 :	sFHPathFile = ssEXEPath + "BEMProc16r.dll";       bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
						case 117 :	BEMPX_GetBEMBaseFile( sFHPathFile );              bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
						default :						assert( FALSE );                   break;
					}
					if (!bRequiredForCodeYear)
					{	// ignore this hash check, as it does not apply to the analysis for this CODEYEAR*
					}
					else if (sFHPathFile.isEmpty() || !FileExists( sFHPathFile.toLocal8Bit().constData() ))
					{	// DO NOTHING - some files expected to be missing - others will prevent success when missing...
					}
					else
					{   char pHashBuffer[65];
				// check weather file hash - SAC 9/2/13
						int iSHA256_RetVal = ComputeSHA256_File( sFHPathFile.toLocal8Bit().constData(), pHashBuffer, 65 );
						if (iSHA256_RetVal != 0)
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
							{	sLogMsg = QString( "Error computing file hash (analysis continuing w/ report signature disabled) - ComputeSHA256_File() returned %1 for file:  %2" ).arg( 
														QString::number(iSHA256_RetVal), sFHPathFile );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
						else
						{	long lFileHashStatus = 0;
						   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), BEMP_Int, (void*) &iFHID     , BEMO_User, 0, BEMS_ProgDefault );
						   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), BEMP_Str, (void*) pHashBuffer, BEMO_User, 0, BEMS_ProgDefault );
							int iFHRetVal = LocalEvaluateRuleset( sFHErrMsg, 48, "CheckFileHash",	bVerbose, pCompRuleDebugInfo );		// file hash checking
							if (iFHRetVal > 0)
							{	bSendRptSignature	= false;			iNumFileHashErrs++;
								if (bLogEachFileHashError)
								{	sLogMsg = QString( "Error evaluating file hash checking rules (analysis continuing w/ report signature disabled) - for file:  %1" ).arg( sFHPathFile );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}	}
							else if (iFHRetVal == 0 && !BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:FileHashStatus" ), lFileHashStatus ))
							{	bSendRptSignature	= false;			iNumFileHashErrs++;
								if (bLogEachFileHashError)
								{	sLogMsg = QString( "    File hash check error - invalid Proj:FileHashStatus (%1) (analysis continuing w/ report signature disabled) - for file:  %2" ).arg( 
																	QString::number(lFileHashStatus), sFHPathFile );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}	}
							else if (iFHRetVal == 0 && lFileHashStatus != 0)
							{	bSendRptSignature	= false;			iNumFileHashErrs++;
								if (bLogEachFileHashError)
								{	sLogMsg = QString( "    File hash check error - failed consistency check (%1) (analysis continuing w/ report signature disabled) - for file:  %2" ).arg( 
																	QString::number(lFileHashStatus), sFHPathFile );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}	}
							else if (bVerbose)
							{	if (bLogEachFileHashError)
								{	sLogMsg = QString( "    File hash check passed for file:  %1" ).arg( sFHPathFile );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}	}
					}	}
				}
				if (iNumFileHashErrs > 0 && !bLogEachFileHashError)
				{	sLogMsg = QString( "    %1 file hash check(s) failed on executable and/or analysis support files (analysis continuing w/ report signature disabled)" ).arg( QString::number(iNumFileHashErrs) );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), iError );
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), iError );
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashStatus"  ), iError );
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}
						dTimeToModelAndSecurityChecks += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		// SAC 5/14/16 - added code to handle setting of batch processing inputs
		std::string sBatchProps[]		= { "RunTitle",		"ClimateZone",		"AnalysisType",	"StandardsVersion",	"AllOrientations",	"FrontOrientation",	"" };
		int			iBatchDatatype[]	= {  BEMP_Str,			 BEMP_Str,			 BEMP_Str,			 BEMP_Str,				 BEMP_Int,				 BEMP_Flt,				};
		int iBIdx=-1;		QString sBatchInp;	long lBatchInp;  double fBatchInp;	void* pBatchInp;
		while (sBatchProps[++iBIdx].size() > 0)
		{	pBatchInp = NULL;
			int iBatchDT = iBatchDatatype[iBIdx];
			if (iBatchDatatype[iBIdx] == BEMP_Str)
			{	GetCSVOptionString( sBatchProps[iBIdx].c_str(), sBatchInp, saCSVOptions );
				if (!sBatchInp.isEmpty())
				{	pBatchInp = (void*) &sBatchInp;
					iBatchDT = BEMP_QStr;
			}	}
			else if (iBatchDatatype[iBIdx] == BEMP_Int)
			{	lBatchInp = GetCSVOptionValue( sBatchProps[iBIdx].c_str(), -99, saCSVOptions );
				if (lBatchInp != -99)
					pBatchInp = (void*) &lBatchInp;
			}
			else if (iBatchDatatype[iBIdx] == BEMP_Flt)
			{	fBatchInp = GetCSVOptionValue( sBatchProps[iBIdx].c_str(), -99, saCSVOptions );
				if (fBatchInp != -99)
					pBatchInp = (void*) &fBatchInp;
			}
			if (pBatchInp)
			   BEMPX_SetBEMData( BEMPX_GetDatabaseID( sBatchProps[iBIdx].c_str(), BEMPX_GetDBComponentID( "Proj" ) ), iBatchDT, pBatchInp );
		}

		if (ResRetVal_ContinueProcessing( iRetVal ) && !bLoadModelFile && !sXMLResultsFileName.isEmpty())  // SAC 2/19/13 - added to export the USER INPUT model to XML results file
		{
	   // write user model to XML results file
			// SAC 4/16/14 - modified call to WriteModel() to cause only valid INPUTs to be written to user input model
			BOOL bXMLInputWriteOK = xmlResultsFile.WriteModel( FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, "User Input" /*pszModelName*/, -1 /*iBEMProcIdx*/, true /*bOnlyValidInputs*/ );
														assert( bXMLInputWriteOK );
						dTimeToWriteResultsXML += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
		}
																assert( !BEMPX_AbortRuleEvaluation() );
		BEMPX_SetAbortRuleEvaluationFlag( false );		// SAC 8/6/13 - set flag indicating that rule processing should be aborted

	// create first COPY of user input model, so that the first model loaded into memory doesn't include any data that we would not want written to an updated User Input written @ end of analysis (SAC 5/12/15)
		if (ResRetVal_ContinueProcessing( iRetVal ) && !bFirstModelCopyCreated)
		{	BEMPX_AddModel( 0 /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
			bFirstModelCopyCreated = true;
		}

	// SAC 3/11/14 - added handling of new BypassRuleLimits option - when =1 should cause certain rule-based compliance checks/limits to be bypassed
		if (ResRetVal_ContinueProcessing( iRetVal ) && !bLoadModelFile && lBypassRuleLimits > 0)
		   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BypassRuleLimits" ), BEMP_Int, (void*) &lBypassRuleLimits );
		BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:BypassRuleLimits" ), lBypassRuleLimits, 0 );

	// SAC 5/14/16 - 
		if (ResRetVal_ContinueProcessing( iRetVal ) && !bLoadModelFile && lEnableResearchMode > 0)
		   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:EnableResearchMode" ), BEMP_Int, (void*) &lEnableResearchMode );
		BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EnableResearchMode" ), lEnableResearchMode, 0 );

	// SAC 1/14/15 - added handling of new SimSpeedOption property/option - when >= 0 should force use of the specified selection
		if (ResRetVal_ContinueProcessing( iRetVal ) && !bLoadModelFile && iSimSpeedOption > 0)
	      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SimSpeedOption" ), BEMP_Int, (void*) &iSimSpeedOption );
		BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:SimSpeedOption" ), iSimSpeedOption );

	// SAC 7/15/15 - added handling of new DHWCalcMethod analysis option
		if (ResRetVal_ContinueProcessing( iRetVal ) && !bLoadModelFile && iDHWCalcMethodAnalOpt >= 0)
	      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:DHWCalcMethod" ), BEMP_Int, (void*) &iDHWCalcMethodAnalOpt );
	   long lDHWCalcMethod = -1;
	   long lDBID_ProjDHWCalcMethod = BEMPX_GetDatabaseID( "Proj:DHWCalcMethod" );		assert( lDBID_ProjDHWCalcMethod > 1 );
		BEMPX_GetInteger( lDBID_ProjDHWCalcMethod, lDHWCalcMethod );
		bDHWCalcMethodUserSpecified = (BEMPX_GetDataStatus( lDBID_ProjDHWCalcMethod ) == BEMS_UserDefined);		//, -1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );

// SAC 9/15/15 - store certain path and filenames to BEMBase for reference during analysis
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	QString sBatchPath, sBatchFile, sModelFile;
			if (sModelFileOnly.lastIndexOf('.') > 0)
				sModelFile = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );
			else
				sModelFile = sModelFileOnly;
			GetCSVOptionString( "BatchPath", sBatchPath, saCSVOptions );
			GetCSVOptionString( "BatchFile", sBatchFile, saCSVOptions );
			if (sBatchPath.isEmpty())
				sBatchPath = sProcessPath;
			if (sBatchFile.isEmpty())
				sBatchFile = sModelFile + QString(" - analysis");

			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BatchPath"      ), BEMP_QStr, (void*) &sBatchPath    , BEMO_User, 0, BEMS_ProgDefault );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BatchFile"      ), BEMP_QStr, (void*) &sBatchFile    , BEMO_User, 0, BEMS_ProgDefault );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ModelPath"      ), BEMP_QStr, (void*) &sModelPathOnly, BEMO_User, 0, BEMS_ProgDefault );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ModelFile"      ), BEMP_QStr, (void*) &sModelFile    , BEMO_User, 0, BEMS_ProgDefault );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ProcessingPath" ), BEMP_QStr, (void*) &sProcessPath  , BEMO_User, 0, BEMS_ProgDefault );
		}

// SAC 6/28/14 - added code to check for IsMultiFamily flag and evaluate rules designed specifically to prepare those models for analysis
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	long lIsMultiFamily = 0;
			BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:IsMultiFamily" ), lIsMultiFamily );
			if (lIsMultiFamily > 0)
			{	if (ResRetVal_ContinueProcessing( iRetVal ))
				{	iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalPropInp2Error, "MultiFamilyAnalysisPrep",	bVerbose, pCompRuleDebugInfo );	// sets up MFam HVACSys objects based on DwellUnitType equipment assignments
					if (iRV2 > 0)
						iRetVal = iRV2;
				}
				if (ResRetVal_ContinueProcessing( iRetVal ))
				{	iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalPropInp2Error, "ProposedInput",	bVerbose, pCompRuleDebugInfo );		// generic project defaulting
					if (iRV2 > 0)
						iRetVal = iRV2;
				}
		}	}
						dTimeToPrepModel[0] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

// SAC 4/25/13 - moved certain model checking rule evaluations up here BEFORE doing other checks...
		long lAnalysisType = 0;
		long lAllOrientations = 0;  // SAC 6/22/13
		lDesignRatingRunID = 0;  // SAC 3/27/15
		long lStdDesignBaseID = 0;  	// SAC 3/27/15
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{
			BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), lAnalysisType    );  // 0-Research / 12-Proposed Only / 13-Proposed and Standard
			BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AllOrientations" ), lAllOrientations );  // 0/1 (boolean)

		// SAC 3/27/15 - parameters used to setup design rating and/or standard design runs
			if (lAnalysisType > 0)
			{	long lAllowDR, lDRCalcs;
				if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AllowDesignRating" ), lAllowDR ) && lAllowDR > 0 &&
					 BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:DesignRatingCalcs"  ), lDRCalcs ) && lDRCalcs > 0)
				{	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:DesignRatingBase" ), lDesignRatingRunID ) || lDesignRatingRunID < 1)
						lDesignRatingRunID = 0;
				}
				BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:StdDesignBase" ), lStdDesignBaseID );  // 0/1 (boolean)
			}

		// ensure RunNumber not already > 0
			long lInitRunNum = (lAnalysisType==0 ? 1 : 0);		// SAC 5/14/14 - ensure initial RunNumber = 1 for Research runs
	      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunNumber" ), BEMP_Int, (void*) &lInitRunNum, BEMO_User, 0, BEMS_ProgDefault );

		// further defaulting/setup of ComplianceReport* booleans
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:CompRptPDFWritten" ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:CompRptXMLWritten" ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			if (lAnalysisType != 13)
			{	bComplianceReportPDF = false;
				bComplianceReportXML = false;
			}
			else
			{	// set flags for outputting compliance reports if option string indicates -OR- if project data says to...
				long lRptFlag=0;
				if (!bComplianceReportPDF && BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ComplianceReportPDF" ), lRptFlag ) && lRptFlag > 0)
					  bComplianceReportPDF	= true;
				if (!bComplianceReportXML && BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ComplianceReportXML" ), lRptFlag ) && lRptFlag > 0)
					  bComplianceReportXML	= true;
			}
			// SAC 3/27/15 - no mods to sfPctDoneFollowingSimulations w/ the addition of DesignRating sim, since w/ or w/out this run shouldn't impact # of rounds of simulation (for dual-core, 4-threaded analysis)
			sfPctDoneFollowingSimulations = 98 - (bComplianceReportPDF ?  4.0 / (lAllOrientations ? 3 : 1) : 0) -
															 (bComplianceReportXML ? 10.0 / (lAllOrientations ? 3 : 1) : 0);  // SAC 8/19/13 - re-initialize value added to enable slower progress reporting when generating reports

					assert( ( !bFullCompAnalSpecified || ( bFullComplianceAnalysis && lAnalysisType == 13) ||
																	 (!bFullComplianceAnalysis && lAnalysisType != 13) ) );  // what if these options not consistent ???
			if (!bFullCompAnalSpecified)
				bFullComplianceAnalysis = (lAnalysisType == 13);
			else if (!bFullComplianceAnalysis && lAnalysisType == 13)
				bFullComplianceAnalysis = true;  // set bFullComplianceAnalysis to true if project data indicates...
		}

//	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");
		QString sModelFileOnlyNoExt = sModelFileOnly;
		if (sModelFileOnlyNoExt.lastIndexOf('.') > 0)
			sModelFileOnlyNoExt = sModelFileOnlyNoExt.left( sModelFileOnlyNoExt.lastIndexOf('.') );

		// check for/create processing path   - SAC 9/25/14 - moved up from below to create path prior to writing Report model ibd
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	if (!DirectoryExists( sProcessPath ))
				CreateAndChangeDirectory( sProcessPath.toLocal8Bit().constData(), FALSE );
		   if (!DirectoryExists( sProcessPath ))
			{	sErrorMsg = "ERROR:  Unable to create or access the CSE processing directory:  " + sProcessPath;
				iRetVal = BEMAnal_CECRes_ProcDirError;
			}
		}
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

// SAC 2/23/15 - added new check for duplicate object names
		if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformDupObjNameCheck)
		{	if (BEMPX_CheckForDuplicateObjectNames( pszAnalErrMsg, 512, TRUE /*bWriteErrorsToLog*/, TRUE /*bSupressAllMessageBoxes*/ ) > 0)
			{	sErrorMsg = pszAnalErrMsg;
				iRetVal = BEMAnal_CECRes_DuplicateObjNames;
			}
		}

// SAC 10/22/14 - moved up HERE from below so that NotInput objects/properties don't get flagged as analysis errors
// ??? - perform range checks only ONCE prior to simulating first model ???
		if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformRangeChecks)
		{
			if (!BEMPX_PerformErrorCheck( (lAnalysisType > 0) /*bRequireRequiredData=TRUE*/, FALSE /*bReportSimDefaultErrors=TRUE*/, FALSE /*bPerformReqdClassCheck=TRUE*/,
													FALSE /*bPostRangeWarnings=FALSE*/, (bIgnoreFileReadErrors ? 0 : BEM_UserInpChk_DisallowNotInput) /**/, bPerformRangeChecks ))
				iRetVal = BEMAnal_CECRes_RangeOrOtherError;  // error messages should already be logged...
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}
		if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

						dTimeToModelAndSecurityChecks += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		// SAC 10/22/14 - added new rulelsit call to ensure generic model summarization PLUS HERS/SpecialFeatures are all present for the Proposed model written to analysis results
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	iRV2 = LocalEvaluateRuleset(		sErrorMsg, BEMAnal_CECRes_EvalAnalPrepError, "OneTimeAnalysisPrep",		bVerbose, pCompRuleDebugInfo );		// one-time only analysis prep rules
			if (iRV2 > 0)
				iRetVal = iRV2;
			if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
				iRetVal = BEMAnal_CECRes_RuleProcAbort;
		}
						dTimeToPrepModel[0] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

	// Set last run date parameter   - SAC 10/22/14 - moved UP from below to get it set properly prior to exporting the Proposed model for reporting purposes
		if (ResRetVal_ContinueProcessing( iRetVal ))  // SAC 8/27/13 - ported rundate setting code from CBECC into BEMCmpMgr
		{	//CTime time = CTime::GetCurrentTime();
			//long lTime = (long) time.GetTime();
			QDateTime current = QDateTime::currentDateTime();
			long lTime = (long) current.toTime_t();	// seconds since 1970-Jan-01 / valid as long int until 2038-Jan-19 / switching to uint extends valid date range to 2106-Feb-07
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunDate" ), BEMP_Int, (void*) &lTime );
		// add formatted RunDate string -> RunDateFmt property
			QString sRunDateFmt;
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunDate" ), sRunDateFmt, FALSE, -1 /*iPrecision*/ );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunDateFmt" ), BEMP_QStr, (void*) &sRunDateFmt );
		}

	// Retrieve report info designed to export summaries of each building model during analysis  - SAC 6/10/13
		QString sAnalysisReport;
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	long lAnalysisReport = 0;
			if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AnalysisReport" ), lAnalysisReport ) && lAnalysisReport > 0)
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnalysisReport" ), sAnalysisReport );
		}

	// ADDED FOR NEW 'REPORT' CSV export
		// call to generate ruleset-defined report on model following simulation & results retrieval/processing
		// do this PRIOR to cleaning up CSE simulation stuff but after all simulation results retrieval & processing is done - in case any of the report stuff references any of that data
			if (ResRetVal_ContinueProcessing( iRetVal ) && !sAnalysisReport.isEmpty())
			{	if (bVerbose)  // SAC 1/31/13
				{	sLogMsg = QString( "      about to generate '%1' model report" ).arg( sAnalysisReport );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				// SAC 2/10/14 - replace (possibly relative) pszModelPathFile w/ a full path version
				QString sGenRptPathFile = sFullModelPathFile;
				if (sGenRptPathFile.lastIndexOf('.') > 0)
					sGenRptPathFile  = sGenRptPathFile.left( sGenRptPathFile.lastIndexOf('.') );
				sGenRptPathFile += " - Rpt";

				int iRptRetVal = CMX_GenerateRulesetModelReport( sGenRptPathFile.toLocal8Bit().constData(), sAnalysisReport.toLocal8Bit().constData(),
																				 NULL /*pszRptPathFile*/, 0 /*iRptPathFileLen*/, (bVerbose), bSilent );
				if (iRptRetVal > 0)
				{	sErrorMsg = QString( "Error:  Model report generation failed w/ error code %1 - report: '%2' - file: '%3'" ).arg( QString::number(iRptRetVal), sAnalysisReport, sGenRptPathFile );
					iRetVal = BEMAnal_CECRes_ModelRptError;
				}
			}
						dTimeToWriteModelAndHrlyCSVs += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		// SAC 4/24/15 - added new log message to help document exactly WHAT ruleset and software performing this analysis
		if (ResRetVal_ContinueProcessing( iRetVal ) && lAnalysisType > 0)
		{	QString sAnalSoftwareVer, sAnalCompMgrVer;
			if (pszUIVersionString && strlen( pszUIVersionString ) > 0)
				sAnalSoftwareVer = pszUIVersionString;
			else
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), sAnalSoftwareVer );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMgrVersion" ), sAnalCompMgrVer );
			sLogMsg = QString( "   Analysis being performed by CompMgrVersion '%1' via SoftwareVersion '%2'" ).arg( sAnalCompMgrVer, sAnalSoftwareVer );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}

		// SAC 4/24/15 - moved up from below so that it is done PRIOR to exporting the Proposed (report) model
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	if (pszUIVersionString && strlen( pszUIVersionString ) > 0)
		      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), BEMP_Str, (void*) pszUIVersionString );
			else
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), iError );
		}

	// SAC 9/23/14 - added code to export detailed 'Report' model to analysis results XML file
		if (ResRetVal_ContinueProcessing( iRetVal ) && !sXMLResultsFileName.isEmpty() && lAnalysisType > 0)
		{	BOOL bXMLWriteOK = xmlResultsFile.WriteModel( TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, "Proposed" /*pszModelName*/ );			assert( bXMLWriteOK );		// was initially 'Report' model
			if (bVerbose)
			{	sLogMsg = QString( "      Writing of XML project %1 model data successful: %2" ).arg( "Report", (bXMLWriteOK ? "True" : "False") );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
			if (bStoreBEMProcDetails)	// SAC 1/20/13 - added export of additional "detail" file to help isolate unnecessary object creation issues
			{	QString sDbgFileName = QString( "%1%2 - Report.ibd-Detail" ).arg( sProcessPath, sModelFileOnlyNoExt );
	      	BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
		}	}
						dTimeToWriteResultsXML += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		// SAC 1/9/13 - added calls to rulelists that CHECK user input model prior to further analysis to catch mandatory minimum (code) & error/omission user errors
		if (ResRetVal_ContinueProcessing( iRetVal ) /*&& iRunIdx == 0*/ && lAnalysisType > 0)
		{
			iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalCodeChkError, "ProposedModelCodeCheck",	bVerbose, pCompRuleDebugInfo );		// check user input model for CODE-related errors
			if (iRV2 > 0)
				iRetVal = iRV2;
						dTimeToModelAndSecurityChecks += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

// ??? perform simulation check before or after (or both) evaluation of 'ProposedModelCodeAdditions' rulelist ???

			if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
				iRetVal = BEMAnal_CECRes_RuleProcAbort;
			if (ResRetVal_ContinueProcessing( iRetVal ))
			{	iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalCodeAddError, "ProposedModelCodeAdditions",	bVerbose, pCompRuleDebugInfo );		// make code-specified additions to user model prior to Proposed simulation
				if (iRV2 > 0)
					iRetVal = iRV2;
			}

	// SAC 1/28/13 - RE-evaluate ProposedINput rules following initial proposed model checks & additions (& deletions)
			if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
				iRetVal = BEMAnal_CECRes_RuleProcAbort;
			if (ResRetVal_ContinueProcessing( iRetVal ))
			{	iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalPropInp2Error, "ProposedInput",	bVerbose, pCompRuleDebugInfo );		// generic project defaulting
				if (iRV2 > 0)
					iRetVal = iRV2;
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
						dTimeToPrepModel[0] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
		}
		if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

	// setup and copy CSE include file defining DHW use profiles - SAC 3/17/16
		long lProjDHWUseIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:CSE_DHWUseIncFile" );
		if (lProjDHWUseIncludeFileDBID < 1)	// SAC 5/17/16 - backward compat
			lProjDHWUseIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:DHWUseIncludeFile" );
		QString sDHWUseIncFile;
		if (ResRetVal_ContinueProcessing( iRetVal ) && lProjDHWUseIncludeFileDBID > 0 && BEMPX_GetString( lProjDHWUseIncludeFileDBID, sDHWUseIncFile ) && !sDHWUseIncFile.isEmpty())
		{
			QString sDHWUseTo, sDHWUseFrom = sCSEEXEPath + sDHWUseIncFile;
			if (!FileExists( sDHWUseFrom.toLocal8Bit().constData() ))
			{	sErrorMsg = QString( "ERROR:  DHW Use/Load Profile CSE include file '%1' missing (expected in CSE directory '%2')" ).arg( sDHWUseIncFile, sCSEEXEPath );
				iRetVal = BEMAnal_CECRes_DHWUseCSEIncMissing;
			}
			else
			{	sDHWUseTo = sProcessPath + sDHWUseIncFile;
				if (!CopyFile( sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData(), FALSE ))
				{	sErrorMsg = QString( "ERROR:  Unable to copy DHW Use/Load Profile CSE include file from '%1' into processing directory '%2'" ).arg( sDHWUseFrom, sDHWUseTo );
					iRetVal = BEMAnal_CECRes_DHWUseCSEIncCopyErr;
				}
				assert( FileExists( sDHWUseTo.toLocal8Bit().constData() ) );
			}
			if (ResRetVal_ContinueProcessing( iRetVal ))
			{	sDHWUseIncFile = sDHWUseTo;
				long lDHWUseIncFileHashID = 0;
				long lDBID_DHWUseIncFileHashID = BEMPX_GetDatabaseID( "Proj:CSE_DHWUseIncFileHashID" );
				if (lDBID_DHWUseIncFileHashID < 1)	// SAC 5/17/16 - backward compat
					lDBID_DHWUseIncFileHashID = BEMPX_GetDatabaseID( "Proj:DHWUseIncFileHashID" );
				if (!bBypassValidFileChecks && BEMPX_GetInteger( lDBID_DHWUseIncFileHashID, lDHWUseIncFileHashID ) && lDHWUseIncFileHashID > 0)
				{	char pHashBuffer[65];
					int iSHA256_DHWUse_RetVal = ComputeSHA256_File( sDHWUseIncFile.toLocal8Bit().constData(), pHashBuffer, 65 );
					if (iSHA256_DHWUse_RetVal != 0)
					{	sErrorMsg = QString( "ERROR:  Error setting up check of DHW use/profile file hash - ComputeSHA256_File() returned %1" ).arg( QString::number(iSHA256_DHWUse_RetVal) );
						iRetVal = BEMAnal_CECRes_DHWUseHashError;
					}
					else
					{	long lDHWUseFileHashStatus = 0;
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), BEMP_Int, (void*) &lDHWUseIncFileHashID, BEMO_User, 0, BEMS_ProgDefault );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), BEMP_Str, (void*) pHashBuffer          , BEMO_User, 0, BEMS_ProgDefault );
						int iFHRetVal = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalChkFileHashError, "CheckFileHash",	bVerbose, pCompRuleDebugInfo );		// file hash checking
						BOOL bFHStatusRetVal = BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:FileHashStatus" ), lDHWUseFileHashStatus );
						if (iFHRetVal > 0 || (iFHRetVal == 0 && !bFHStatusRetVal) || (iFHRetVal == 0 && lDHWUseFileHashStatus != 0))
						{	bSendRptSignature	= false;
							iRetVal = BEMAnal_CECRes_DHWUseHashChkFail;		//		206	// DHW use/profile file hash failed consistency check
							if (bLogEachFileHashError)
							{	if (iFHRetVal > 0)
									sLogMsg = QString( "Error evaluating file hash checking rules (analysis continuing w/ report signature disabled) - for file:  %1" ).arg( sDHWUseIncFile );
								else if (iFHRetVal == 0 && !bFHStatusRetVal)
									sLogMsg = QString( "    File hash check error - invalid Proj:FileHashStatus (%1) (analysis continuing w/ report signature disabled) - for file:  %2" ).arg( 
																	QString::number(lDHWUseFileHashStatus), sDHWUseIncFile );
								else
									sLogMsg = QString( "    File hash check error - failed consistency check (%1) (analysis continuing w/ report signature disabled) - for file:  %2" ).arg( 
																	QString::number(lDHWUseFileHashStatus), sDHWUseIncFile );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), iError );
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), iError );
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashStatus"  ), iError );
					}
			}	}
		}

		if (ResRetVal_ContinueProcessing( iRetVal ))
		{
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherFileName" ), sCSEWthr );
			int iOrigWFNameLen = sCSEWthr.length();
			sCSEWthr     = sCSEWeatherPath + sCSEWthr;    // "CTZ12S13.CSW";
			if (iOrigWFNameLen < 5)
			{	sErrorMsg = "ERROR:  CSE simulation weather file not present in model property: Proj:WeatherFileName";
				iRetVal = BEMAnal_CECRes_GetSimWthrError;
			}
			else if (!FileExists( sCSEWthr.toLocal8Bit().constData() ))
			{	sErrorMsg = "ERROR:  CSE simulation weather file not found:  " + sCSEWthr;
				iRetVal = BEMAnal_CECRes_SimWthrNotFound;
			}
			else if (lAnalysisType > 0)  // only perform weather file hash checks if user performing some sort of compliance analysis
			{
				char pHashBuffer[65];
		// check weather file hash - SAC 9/2/13
				int iSHA256_Wthr_RetVal = ComputeSHA256_File( sCSEWthr.toLocal8Bit().constData(), pHashBuffer, 65 );
				if (iSHA256_Wthr_RetVal != 0)
				{	sErrorMsg = QString( "ERROR:  Error setting up check of weather file hash - ComputeSHA256_File() returned %1" ).arg( QString::number(iSHA256_Wthr_RetVal) );
					iRetVal = BEMAnal_CECRes_SetupWthrHashError;
				}
				else
				{	long lClimateZone = 0, lWthrFileHashStatus = 0;
					if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ClimateZone" ), lClimateZone ) || lClimateZone < 1 || lClimateZone > 16)
					{	sErrorMsg = QString( "ERROR:  Error setting up check of weather file hash - Invalid Proj:ClimateZone (%1)" ).arg( QString::number(lClimateZone) );
						iRetVal = BEMAnal_CECRes_SetupWthrHashError;
					}
					else
					{  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), BEMP_Int, (void*) &lClimateZone, BEMO_User, 0, BEMS_ProgDefault );
				      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), BEMP_Str, (void*) pHashBuffer  , BEMO_User, 0, BEMS_ProgDefault );
						iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalChkFileHashError, "CheckFileHash",	bVerbose, pCompRuleDebugInfo );		// file hash checking
						if (iRV2 > 0)
							iRetVal = iRV2;
						if (ResRetVal_ContinueProcessing( iRetVal ) && !BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:FileHashStatus" ), lWthrFileHashStatus ))
						{	sErrorMsg = QString( "ERROR:  Error setting up check of weather file hash - Invalid Proj:FileHashStatus (%1)" ).arg( QString::number(lWthrFileHashStatus) );
							iRetVal = BEMAnal_CECRes_SetupWthrHashError;
						}
						else if (ResRetVal_ContinueProcessing( iRetVal ) && lWthrFileHashStatus != 0)
						{	sErrorMsg = QString( "ERROR:  Weather file hash failed consistency check (%1)" ).arg( QString::number(lWthrFileHashStatus) );
							iRetVal = BEMAnal_CECRes_WthrHashChkFail;
						}
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashID"      ), iError );
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashToCheck" ), iError );
						BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "Proj:FileHashStatus"  ), iError );
			}	}	}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
						dTimeToModelAndSecurityChecks += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
		}
		if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		if (ResRetVal_ContinueProcessing( iRetVal ) && !sDHWWeatherPath.isEmpty())
		{
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:DHWWthrFileName" ), sDHWWthr );
			int iOrigWFNameLen = sDHWWthr.length();
			sDHWWthr     = sDHWWeatherPath + sDHWWthr;    // "CTZ12S13.CSW";
			if (iOrigWFNameLen < 5)
			{	sErrorMsg = "ERROR:  DHW simulation weather file not present in model property: Proj:DHWWthrFileName";
				iRetVal = BEMAnal_CECRes_GetDHWWthrError;
			}
			else if (!FileExists( sDHWWthr.toLocal8Bit().constData() ))
			{	sErrorMsg = "ERROR:  DHW simulation weather file not found:  " + sDHWWthr;
				iRetVal = BEMAnal_CECRes_DHWWthrNotFound;
			}
			else
				bDHWSimViaWthrFile = TRUE;
		}
		if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
			iRetVal = BEMAnal_CECRes_RuleProcAbort;

		long lProjRunScope = 1;		// 1 => "Newly Constructed" / 2 => "Addition and/or Alteration"		// SAC 12/2/13
		if (ResRetVal_ContinueProcessing( iRetVal ))
		{	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunScope" ), lProjRunScope ))
				lProjRunScope = 1;
		}

	// Check for specification of Report Include file - and if found, prevent secure report
		long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:ReportIncludeFile" );
		QString sChkRptIncFile;
		if (lProjReportIncludeFileDBID > 0 && BEMPX_GetString( lProjReportIncludeFileDBID, sChkRptIncFile /*, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx*/ ) && !sChkRptIncFile.isEmpty())
			bCSEIncludeFileUsed = true;
		else
		{	long lUseTstatIncFile, lDBID_Zone_UseTstatIncFile = BEMPX_GetDatabaseID( "Zone:UseTstatIncFile" );		// SAC 7/2/15
			int iNumZones = (lDBID_Zone_UseTstatIncFile < 1 ? 0 : BEMPX_GetNumObjects( BEMPX_GetClassID( lDBID_Zone_UseTstatIncFile ) ));
			for (int iZnIdx=0; (!bCSEIncludeFileUsed && iZnIdx < iNumZones); iZnIdx++)
			{	if (BEMPX_GetInteger( lDBID_Zone_UseTstatIncFile, lUseTstatIncFile, 0, -1, iZnIdx ) && lUseTstatIncFile > 0)
					bCSEIncludeFileUsed = true;
		}	}

	// SAC 4/29/15 - DISABLE report include file use if all settings are conisistent w/ full secure report generation (to prevent invalid analysis)
		bool bAllowReportIncludeFile = true;
		if (ResRetVal_ContinueProcessing( iRetVal ) && bCSEIncludeFileUsed && bSendRptSignature && (bComplianceReportPDF || bComplianceReportXML) &&
				bFullComplianceAnalysis && bInitHourlyResults && bPerformDupObjNameCheck && bPerformRangeChecks && bPerformSimulations &&
				!bBypassCSE && !bBypassDHW && !bIgnoreFileReadErrors && lBypassRuleLimits < 1 && iSimSpeedOption < 1 && !bDHWCalcMethodUserSpecified)
		{	bAllowReportIncludeFile = false;
			bCSEIncludeFileUsed = false;
								sLogMsg = "CSE report include file use disabled to ensure secure report generation.  Use BypassRuleLimits or other research option to ensure report include file use.";
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}

	// SAC 7/8/15 - transition from T24DHW DLL use -> CSE for DHW simulation
// SAC 9/10/15 - NOTE - the following enduse names for storing DHWPump elec use are INCORRECT (should be "*DHWPmp"), but are being retained in order to maintain consistency w/ results from the previous public release version
// SAC 10/8/15 - fixed bug reported above to bring this enduse name inline with other source code and ruleset 
		QString sT24DHWEnduse = "DHW", sT24DHWPumpEnduse = "DHWPmp";
		if (ResRetVal_ContinueProcessing( iRetVal ) && lDHWCalcMethod > 0)	// DHWCalcMethod == CSE*
		{	// rename T24DHW enduses so that they are NOT included in compliance results
			sT24DHWEnduse = "T24DHW";		sT24DHWPumpEnduse = "T24DHWPmp";
		}

// SAC 12/23/14

//
//	-----  Project loaded & defaulted, weather files present  -----
//	-----  Loop over (potentially multiple) individual Runs  -----
//
#if defined( CSE_MULTI_RUN)
		CSERunMgr cseRunMgr(
			sCSEexe, sCSEWthr, sModelPathOnly, sModelFileOnlyNoExt, sProcessPath, bFullComplianceAnalysis,
			bInitHourlyResults, lAllOrientations, lAnalysisType, lStdDesignBaseID, lDesignRatingRunID, bVerbose,
			bStoreBEMProcDetails, bPerformSimulations, bBypassCSE, bSilent, pCompRuleDebugInfo, pszUIVersionString,
			iSimReportDetailsOption, iSimErrorDetailsOption	);		// SAC 11/7/16 - added sim report/error option arguments
#endif
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		QString sMsg;
//		int iNumRuns = (bFullComplianceAnalysis ? (lAllOrientations > 0 ? 5 : 2) : 1);
// SAC 3/27/15 - mods to describe each run to be performed
		int iNumRuns = 0;
		int iRunType[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
		iRunType[iNumRuns++] = (lAnalysisType < 1 ? CRM_User : (lAllOrientations > 0 ? CRM_NOrientProp : CRM_Prop));
		if (lAnalysisType > 0)
		{	if (lAllOrientations > 0)
			{	iRunType[iNumRuns++] = CRM_EOrientProp;
				iRunType[iNumRuns++] = CRM_SOrientProp;
				iRunType[iNumRuns++] = CRM_WOrientProp;
			}
			if (lAnalysisType == 13)	// SAC 4/21/15 - fix bug where 'Proposed Only' AnalysisType (12) still performing Std Design simulation/reporting
				iRunType[iNumRuns++] = CRM_StdDesign;
			if (lDesignRatingRunID > 0 && lAnalysisType >= 13)		// SAC 12/1/16 - prevent DR run when AnalysisType = ProposedOnly
				iRunType[iNumRuns++] = CRM_DesignRating;
		}

#if defined( CSE_MULTI_RUN)
		siNumProgressRuns = 1;
//#else
//		siNumProgressRuns = iNumRuns;
#endif

		int iRunIdx = 0;
		for (; (ResRetVal_ContinueProcessing( iRetVal ) && iRunIdx < iNumRuns); iRunIdx++)
		{
#if defined( CSE_MULTI_RUN)
			if (iRunIdx > 0 || !bFirstModelCopyCreated)
				BEMPX_AddModel( std::min( iRunIdx, 1 ) /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
			iRV2 = cseRunMgr.SetupRun( iRunIdx, iRunType[iRunIdx], sErrorMsg, bAllowReportIncludeFile );
			if (iRV2 > 0)
				iRetVal = iRV2;
						dTimeToPrepModel[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
		}

		if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations && !bBypassCSE)
			cseRunMgr.DoRuns();
						dTimeCSESim += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		if (ResRetVal_ContinueProcessing( iRetVal ))
		for (iRunIdx = 0; iRunIdx < iNumRuns; iRunIdx++)
		{
			const CSERun& cseRun = cseRunMgr.GetRun(iRunIdx);
			const QString& sRunID = cseRun.GetRunID();
			const QString& sRunIDProcFile = cseRun.GetRunIDProcFile();
			const QString& sRunAbbrev = cseRun.GetRunAbbrev();
			long lRunNumber = (lAnalysisType < 1 ? 1 : cseRun.GetRunNumber());

		// process CSE errors and/or reports into file for user review - SAC 11/7/16
			if (bPerformSimulations && !bBypassCSE && !sCSESimRptOutputFileName.isEmpty())
				cseRunMgr.ArchiveSimOutput( iRunIdx, sCSESimRptOutputFileName, CSERun::OutFileREP );
			if (bPerformSimulations && !bBypassCSE && !sCSESimErrOutputFileName.isEmpty())
				cseRunMgr.ArchiveSimOutput( iRunIdx, sCSESimErrOutputFileName, CSERun::OutFileERR );

			if (ResRetVal_ContinueProcessing( iRetVal )) // SAC 11/7/16 - moved iRetVal == 0 condition out of for() loop and down here to process output of simulated runs (above) even after errors encountered
			{
// SAC 6/19/14 - Set active model index to the appropriate value for this iRunIdx
				BEMPX_SetActiveModel( iRunIdx+1 );

			//	BOOL bLastRun = cseRun.GetLastRun();
				BOOL bIsStdDesign = cseRun.GetIsStdDesign();
				BOOL bIsDesignRtg = cseRun.GetIsDesignRtg();

// SAC 6/19/14 - add models to BEMBase for each run being performed so that the state of each model can be retained for use the second time through the run loop
				if (iRunIdx > 0)
				{
				// Copy results objects from PREVIOUS MODEL to CURRENT MODEL
					int iResCopyRetVal = 0;
					if (ResRetVal_ContinueProcessing( iRetVal ))
					{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
						QString sResCopyErrMsg;
						iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, sRunAbbrev.toLocal8Bit().constData(), iRunIdx, iRunIdx+1 );
						assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
						if (iResCopyRetVal > 0)
						{	if (sErrorMsg.isEmpty())
								sErrorMsg = sResCopyErrMsg;
							switch (iResCopyRetVal)
							{	case 34 :  iRetVal = BEMAnal_CECRes_BadResultsObjTypes;	break;
								case 35 :  iRetVal = BEMAnal_CECRes_ResultsCopyError  ;	break;
								default :	assert( FALSE );	break;
							}
					}	}
				// now results objects from previous run are in place, now ensure that references to those objects are also valid
					char* pszaResObjRefProps[] = { "Proj:RunResults",  "Proj:RunResultsN",  "Proj:RunResultsE",  "Proj:RunResultsS",  "Proj:RunResultsW",  "Proj:ResultSummary", NULL };
					int iRORPIdx = -1;
					while (pszaResObjRefProps[++iRORPIdx] != NULL)
					{	long lRORPDBID = BEMPX_GetDatabaseID( pszaResObjRefProps[iRORPIdx] );			assert( lRORPDBID > 0 );
						int iRORPLen = (lRORPDBID < 1 ? 0 : BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lRORPDBID ), BEMPX_GetPropertyID( lRORPDBID ) /*, iBEMProcIdx*/ ));
						QString sROR;
						for (int iPAIdx=0; iPAIdx < iRORPLen; iPAIdx++)
						{	if (BEMPX_GetString( lRORPDBID+iPAIdx, sROR, TRUE, 0, -1, 0 /*iOccur*/, BEMO_User, NULL, 0, iRunIdx /*iBEMProcIdx*/ ) && !sROR.isEmpty())
							{	int iRORRetVal = BEMPX_SetBEMData( lRORPDBID+iPAIdx, BEMP_QStr, (void*) &sROR, BEMO_User, 0, BEMS_RuleDefined );		iRORRetVal;
	                                                     //BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ... );
					}	}	}
							dTimeToProcResults[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
				}

				if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations && !bBypassCSE)
				{
					int iCSERetVal = cseRun.GetExitCode();
					if (bVerbose)  // SAC 1/31/13
					{	sLogMsg = QString( "      CSE simulation returned %1" ).arg( QString::number(iCSERetVal) );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
					BEMPX_RefreshLogFile();	// SAC 5/19/14

					if (iCSERetVal != 0)
					{	sErrorMsg = QString( "ERROR:  CSE simulation returned %1" ).arg( QString::number(iCSERetVal) );
						iRetVal = BEMAnal_CECRes_CSESimError;
					}
					if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
						iRetVal = BEMAnal_CECRes_RuleProcAbort;

					// Retrieve CSE simulation results
					if (ResRetVal_ContinueProcessing( iRetVal ))
					{	// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
						int iHrlyResRetVal = BEMPX_ReadCSEHourlyResults( cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), lRunNumber-1, 
																													sRunID.toLocal8Bit().constData(), sRunAbbrev.toLocal8Bit().constData() );
						if (bVerbose)  // SAC 1/31/13
						{	sLogMsg = QString( "      Hourly CSE results retrieval returned %1" ).arg( QString::number(iHrlyResRetVal) );
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
					// add new Elec - SHWPmp enduse results array  (other arrays initialized based on enduse names in CSE results file)
						if (BEMPX_AddHourlyResultArray(	NULL, sRunID.toLocal8Bit().constData(), "MtrElec", "DHWPmp", -1 /*iBEMProcIdx*/, TRUE /*bAddIfNotExist*/ ) != 0.0)
						{	assert( false );
						}
					}
				}
				else if (ResRetVal_ContinueProcessing( iRetVal ) && (!bPerformSimulations || bBypassCSE))  // SAC 6/10/13
				{
					if (bVerbose)
						BEMPX_WriteLogFile( "      Skipping CSE simulation", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					si1ProgressRunNum = iRunIdx+1;
					siNumProgressErrors = 0;
					CSE_MsgCallback( 0 /*level*/, "Skipping CSE simulation" );
				}
				BEMPX_RefreshLogFile();	// SAC 5/19/14
						dTimeToProcResults[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
	
				if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations && !bBypassDHW && (lDHWCalcMethod == 0 || lDHWCalcMethod == 2))	// DHWCalcMethod == "T24DHW" -or- "CSE (T24 match)"
				{	// DHW SIMULATION
						assert( false );
						BOOL bDHWSimOK = FALSE;
					QString sDHWErrMsg;
				// T24DHW simulation code removed - not ported to open source
					if (!bDHWSimOK)
					{	assert( FALSE );
						// write error mesage to analysis log file ??
						sErrorMsg = sDHWErrMsg;
						iRetVal = BEMAnal_CECRes_DHWSimError;
					}
				}
				else if (ResRetVal_ContinueProcessing( iRetVal ) && (!bPerformSimulations || bBypassDHW))  // SAC 6/19/13
				{
					if (bVerbose)
						BEMPX_WriteLogFile( "      Skipping DHW simulation", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					CSE_MsgCallback( 0 /*level*/, "Skipping DHW simulation" );
				}
				BEMPX_RefreshLogFile();	// SAC 5/19/14
						dTimeDHWSim += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

			// SAC 7/13/15 - code to export CSV files to facilitate comparison of T24DHW & CSE simulation results
				if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations && lDHWCalcMethod == 2)		// DHWCalcMethod == "CSE (T24 match)"
				{	QString sHrlyDHWPathFile = pszModelPathFile;
					if (sHrlyDHWPathFile.lastIndexOf('.') > 0)
						sHrlyDHWPathFile = sHrlyDHWPathFile.left( sHrlyDHWPathFile.lastIndexOf('.') );
					sHrlyDHWPathFile += sRunIDProcFile;

				// combined CSE & T-24 DHW results
					QString sHrlyDHWPathFile_CSE = sHrlyDHWPathFile + QString( " - Hourly DHW Compare.csv" );
					const char* pszDHWEnduses_CSE[3] =  {  "DHW",  "DHWPmp",  NULL  };
					const char* pszDHWEnduses_T24[3] =  {  "T24DHW",  "T24DHWPmp",  NULL  };
					const char* pszDHWCompares[   3] =  {  "CSE",  "T24"  };
					int iHrlyDHWExportRetVal_CSE = ExportCSVHourlyResultsComparison( sHrlyDHWPathFile_CSE.toLocal8Bit().constData(), sRunID.toLocal8Bit().constData(), "DHW", 
																						pszDHWCompares, pszDHWEnduses_CSE, pszDHWEnduses_T24, NULL, 0, bSilent, -1 /*iBEMProcIdx*/ );		assert( iHrlyDHWExportRetVal_CSE == 0 );
				}

				if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations)
				{
					// Process & summarize results
					iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalProcResultsError, "ProcessResults", bVerbose, pCompRuleDebugInfo );
					if (iRV2 > 0)
						iRetVal = iRV2;
					if (bVerbose)
					{	sLogMsg = "      done calling 'ProcessResults' rules";
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
				}
				if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
					iRetVal = BEMAnal_CECRes_RuleProcAbort;
						dTimeToProcResults[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

			// call to generate ruleset-defined report on model following simulation & results retrieval/processing
			// do this PRIOR to cleaning up CSE simulation stuff but after all simulation results retrieval & processing is done - in case any of the report stuff references any of that data
				if (ResRetVal_ContinueProcessing( iRetVal ) && !sAnalysisReport.isEmpty())
				{	if (bVerbose)  // SAC 1/31/13
					{	sLogMsg = QString( "      about to generate '%1' model report" ).arg( sAnalysisReport );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
					// SAC 2/10/14 - replace (possibly relative) pszModelPathFile w/ a full path version
					QString sGenRptPathFile = sFullModelPathFile;
					if (sGenRptPathFile.lastIndexOf('.') > 0)
						sGenRptPathFile  = sGenRptPathFile.left( sGenRptPathFile.lastIndexOf('.') );
					sGenRptPathFile += sRunIDProcFile;

					int iRptRetVal = CMX_GenerateRulesetModelReport( sGenRptPathFile.toLocal8Bit().constData(), sAnalysisReport.toLocal8Bit().constData(),	
																						NULL /*pszRptPathFile*/, 0 /*iRptPathFileLen*/, (bVerbose), bSilent );
					if (iRptRetVal > 0)
					{	sErrorMsg = QString( "Error:  Model report generation failed w/ error code %1 - report: '%2' - file: '%3'" ).arg( QString::number(iRptRetVal), sAnalysisReport, sGenRptPathFile );
						iRetVal = BEMAnal_CECRes_ModelRptError;
					}
				}
				if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
					iRetVal = BEMAnal_CECRes_RuleProcAbort;

				if (ResRetVal_ContinueProcessing( iRetVal ) && bPerformSimulations)
				{
					// Individual run hourly results CSV export - SAC 8/5/13
					QString sHrlyResExportPathFile, sHrlyResExportOption, sHrlyResExportOptionAll;
					QString sRunAbbrevMod = sRunAbbrev;			sRunAbbrevMod.replace( '-', '_' );		// SAC 11/4/16 - changed INI setting name to conform w/ property name conventions
					sHrlyResExportOption = QString( "ExportHourlyResults_%1" ).arg( sRunAbbrevMod );
					sHrlyResExportOptionAll = "ExportHourlyResults_All";
					if (GetCSVOptionValue( sHrlyResExportOption.toLocal8Bit().constData(), 0, saCSVOptions ) > 0 ||
						 GetCSVOptionValue( sHrlyResExportOptionAll.toLocal8Bit().constData(), 0, saCSVOptions ) > 0)
					{	sHrlyResExportPathFile = pszModelPathFile;
						if (sHrlyResExportPathFile.lastIndexOf('.') > 0)
							sHrlyResExportPathFile = sHrlyResExportPathFile.left( sHrlyResExportPathFile.lastIndexOf('.') );
						sHrlyResExportPathFile += sRunIDProcFile;
						sHrlyResExportPathFile += " - HourlyResults.csv";
						int iHrlyResExportRetVal = CMX_ExportCSVHourlyResults_CECRes( sHrlyResExportPathFile.toLocal8Bit().constData(), pszModelPathFile, 
																						sRunID.toLocal8Bit().constData(), NULL, 0, bSilent, -1 /*iBEMProcIdx*/ );				assert( iHrlyResExportRetVal == 0 );
					}
				}
				if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
					iRetVal = BEMAnal_CECRes_RuleProcAbort;
						dTimeToWriteModelAndHrlyCSVs += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

				if (ResRetVal_ContinueProcessing( iRetVal ))
				{
					// Simulation clean-up + write final (detailed) XML file of inputs & results
					iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_EvalSimCleanupError, "CSE_SimulationCleanUp", bVerbose, pCompRuleDebugInfo );
					if (iRV2 > 0)
						iRetVal = iRV2;

					if (bVerbose)  // SAC 1/31/13
					{	sLogMsg = "      done calling 'CSE_SimulationCleanUp' rules";
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

					// write XML results file if not performing simulation ???
					// SAC 6/25/12 - added code to export detailed XML file following analysis
				// SAC 10/24/14 - modified if statement to not write Proposed model - now written above
					if (!sXMLResultsFileName.isEmpty() && (bIsStdDesign || bIsDesignRtg))  // SAC 3/27/15 - mods to export StdDesign & DesignRtg runs
					{	BOOL bXMLWriteOK = xmlResultsFile.WriteModel( TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, sRunID.toLocal8Bit().constData() /*pszModelName*/ );
																	assert( bXMLWriteOK );
						if (bVerbose)  // SAC 1/31/13
						{	sLogMsg = QString( "      Writing of XML project %1 model data successful: %2" ).arg( sRunID, (bXMLWriteOK ? "True" : "False") );
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
					}
						dTimeToWriteResultsXML += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
				}
				if (ResRetVal_ContinueProcessing( iRetVal ) && BEMPX_AbortRuleEvaluation())
					iRetVal = BEMAnal_CECRes_RuleProcAbort;
				BEMPX_RefreshLogFile();	// SAC 5/19/14
		}	}	// end of:  for (iRunIdx = 0; (iRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)

						dTimeToProcResults[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

#else		// NOT CSE_MULTI_RUN
// code removed ...
		}
#endif		// IF/NOT CSE_MULTI_RUN

		if (ResRetVal_ContinueProcessing( iRetVal ))
			xmlResultsFile.Close();
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

	// ----------
	// COMPLIANCE REPORT GENERATION   - SAC 8/14/13
		bAnalysisPriorToRptGenOK = (ResRetVal_ContinueProcessing( iRetVal ));
		if (ResRetVal_ContinueProcessing( iRetVal ) && (bComplianceReportPDF || bComplianceReportXML))
		{	if (sXMLResultsFileName.isEmpty() || !FileExists( sXMLResultsFileName.toLocal8Bit().constData() ))  // || !bFullComplianceAnalysis || !bPerformSimulations || bBypassCSE || bBypassDHW)
			{	if (sXMLResultsFileName.isEmpty())
					sLogMsg = "      Skipping compliance report generation due to no XML results file specified/available";
				else if (!FileExists( sXMLResultsFileName.toLocal8Bit().constData() ))
					sLogMsg = QString( "      Skipping compliance report generation due to no XML results file not found:  %1" ).arg( sXMLResultsFileName );
				else
					sLogMsg = "      Skipping compliance report generation due to <unknown reason>";

				if (bVerbose)
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				sLogMsg = sLogMsg.trimmed();		// was: TrimLeft();
				CSE_MsgCallback( 0 /*level*/, sLogMsg.toLocal8Bit().constData() );
			}
			else
			{	//const char* pszProxyServerAddress     = (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress    );
				//const char* pszProxyServerCredentials = (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials);
				//const char* pszProxyServerType        = (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType       );
				//const char* pszNetComLibrary          = (sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary         );	// SAC 11/5/15
				QString sCACertPath;
				GetDLLPath( sCACertPath );
				if (sCACertPath[sCACertPath.length()-1] == '\\')
					sCACertPath = sCACertPath.left( sCACertPath.length()-1 );

				int iRpt    = (bComplianceReportPDF ? 0 : 1);
				int iMaxRpt = (bComplianceReportXML ? 1 : 0);
				if (iRpt <= iMaxRpt && iEnableRptGenStatusChecks > 0)
				{	// confirm that report generator is accessible before calling for the report(s) to be generated
					int iRptGenAvail = CMX_CheckSiteAccess( "Proj:RptGenCheckURL", sCACertPath.toLocal8Bit().constData(), sProxyServerAddress.toLocal8Bit().constData(),
																			sProxyServerCredentials.toLocal8Bit().constData(), NULL /*pszErrMsg*/, 0, bVerbose, 
																			sProxyServerType.toLocal8Bit().constData(), sNetComLibrary.toLocal8Bit().constData() );
					if (iRptGenAvail > -10)
					{	// rpt gen NOT available
						sLogMsg = QString( "Compliance report(s) called for but bypassed due to %1." ).arg( 
														(iRptGenAvail<0 ? "report generation being offline" : "report generator website not accessible") );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						iRetVal = BEMAnal_CECRes_CompRptWriteError;
						iRpt = 1;	iMaxRpt = 0;
				}	}

				for (; (ResRetVal_ContinueProcessing( iRetVal ) && iRpt <= iMaxRpt); iRpt++)
				{
					//	QString sMsg, sOutRptFN = (sProjFileName.lastIndexOf('.') > 0 ? sProjFileName.left( sProjFileName.lastIndexOf('.') ) : sProjFileName);
					QString sRptFileExt = (iRpt==0 ? "PDF" : "XML"), sOutRptFN = sModelPathOnly + sModelFileOnlyNoExt;
					sOutRptFN += " - AnalysisResults-BEES.";
					sOutRptFN += sRptFileExt;
					sMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
					             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
									 "(once the file is closed), or \n'Cancel' to abort the %3." ).arg( sRptFileExt, sOutRptFN, "compliance report generation" );
					if (!OKToWriteOrDeleteFile( sOutRptFN.toLocal8Bit().constData(), sMsg, bSilent ))
					{	if (bSilent)
							sErrorMsg = QString( "ERROR:  Unable to overwrite %1 file:  %2" ).arg( sRptFileExt, sOutRptFN );
						else
							sErrorMsg = QString( "ERROR:  User chose not to overwrite %1 file:  %2" ).arg( sRptFileExt, sOutRptFN );
						iRetVal = BEMAnal_CECRes_CompRptWriteError;
					}
					else
					{
						QString sPDFOnly = (iRpt==0 ? "true" : "false");
						QString sDebugRpt = (bVerbose ? "true" : "false");

//sLogMsg = QString( "Pausing before %1 report generation on:  %2" ).arg( (iRpt==0 ? "pdf" : "full"), sResFN );
//BEMMessageBox( sLogMsg , "");

									if (bVerbose)
									{	sLogMsg = QString( "      about to generate %1 compliance report:  %2" ).arg( (iRpt==0 ? "pdf" : "full"), sXMLResultsFileName );
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}

				// final check (and logging) for reasons we might NOT send a signature on to the report generator
						if (bSendRptSignature)
						{	QString sNoSignMsg;
							if (iDLLCodeYear > 0 && iRulesetCodeYear > 0 && iDLLCodeYear != iRulesetCodeYear)		// SAC 11/19/15
								sNoSignMsg = QString( "Compliance report will be generated without security measures due to inconsistency between software library year (%1) and ruleset code year (%2)" ).arg( 
																QString::number(iDLLCodeYear), QString::number(iRulesetCodeYear) );
							else if (!bFullComplianceAnalysis)			// = (GetCSVOptionValue( "FullComplianceAnalysis", 1,  saCSVOptions ) > 0);
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option FullComplianceAnalysis being disabled";
							else if (!bInitHourlyResults)			// = (GetCSVOptionValue( "InitHourlyResults"     , 1,  saCSVOptions ) > 0);
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option InitHourlyResults being disabled"     ;
							else if (!bPerformDupObjNameCheck)
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option PerformDupObjNameCheck being disabled"    ;
	                  else if (!bPerformRangeChecks)		// = (GetCSVOptionValue( "PerformRangeChecks"    , 1,  saCSVOptions ) > 0);
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option PerformRangeChecks being disabled"    ;
	                  else if (!bPerformSimulations)		// = (GetCSVOptionValue( "PerformSimulations"    , 1,  saCSVOptions ) > 0);
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option PerformSimulations being disabled"    ;
	                  else if (bBypassCSE)						// = (GetCSVOptionValue( "BypassCSE"             , 0,  saCSVOptions ) > 0);	// options added 6/19/13
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option BypassCSE being enabled"              ;
	                  else if (bBypassDHW)						// = (GetCSVOptionValue( "BypassDHW"             , 0,  saCSVOptions ) > 0);
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option BypassDHW being enabled"              ;
	                  else if (bIgnoreFileReadErrors)		// = (GetCSVOptionValue( "IgnoreFileReadErrors"  , 0,  saCSVOptions ) > 0);	// option added 6/28/13
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option IgnoreFileReadErrors being enabled"   ;
							else if (lBypassRuleLimits > 0)		// SAC 3/11/14 - added handling of new BypassRuleLimits option - when =1 should cause certain rule-based compliance checks/limits to be bypassed | SAC 4/20/15 - switched to integer flag (from bool)
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option BypassRuleLimits being enabled";
							else if (lEnableResearchMode > 0)		// SAC 5/14/16 - 
								sNoSignMsg = "Compliance report will be generated without security measures due to analysis option EnableResearchMode being enabled";
 							else if (iSimSpeedOption > 0)			// SAC 1/14/15 - new option which must be set to 0 ('Compliance') for valid analysis results
								sNoSignMsg = "Compliance report will be generated without security measures due to SimSpeedOption not set to 'Compliance'";
 							else if (bCSEIncludeFileUsed)			// SAC 12/23/14
								sNoSignMsg = "Compliance report will be generated without security measures due to Proj:ReportIncludeFile being specified in the project data";
 							else if (bDHWCalcMethodUserSpecified)			// SAC 7/15/15
								sNoSignMsg = "Compliance report will be generated without security measures due to Proj:DHWCalcMethod being specified in the project data (via user input or analysis option)";
							else if (iRetVal >= BEMAnal_CECRes_MinErrorWithResults)		// SAC 12/12/16
							{	switch (iRetVal)
								{	case  BEMAnal_CECRes_ModelRptError			:	sNoSignMsg = "Compliance report will be generated without security measures due to error generating model report";		break;
								//	case  BEMAnal_CECRes_CompRptWriteError		:  sNoSignMsg = "Compliance report will be generated without security measures due to inability to write compliance report file (.pdf or .xml)";		break;
								//	case  BEMAnal_CECRes_CompRptGenError		:  sNoSignMsg = "Compliance report will be generated without security measures due to error(s) encountered generating compliance report file (.pdf or .xml)";		break;
									case  BEMAnal_CECRes_EvalChkFileHashError	:  sNoSignMsg = "Compliance report will be generated without security measures due to error(s) evaluating CheckFileHash rules";		break;
									case  BEMAnal_CECRes_WthrHashChkFail		:  sNoSignMsg = "Compliance report will be generated without security measures due to weather file hash failing consistency check";		break;
									case  BEMAnal_CECRes_InputSaveFailed		:  sNoSignMsg = "Compliance report will be generated without security measures due to inability to save project inputs (including results) following analysis";		break;
									case  BEMAnal_CECRes_DHWUseHashChkFail		:  sNoSignMsg = "Compliance report will be generated without security measures due to DHW use/profile file hash failing consistency check";		break;
									default  :	sNoSignMsg = QString( "Compliance report will be generated without security measures due to error encountered during analysis (%1 >= BEMAnal_CECRes_MinErrorWithResults)" ).arg( QString::number(iRetVal) );		break;
								}
							}

							if (!sNoSignMsg.isEmpty())
							{	bSendRptSignature = false;
								BEMPX_WriteLogFile( sNoSignMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}
						}

						// SAC 6/2/14 - added several ruleset-based reporting variables and incorporated them into the GenerateReport_CEC() prototype
						QString sRptGenUIApp, sRptGenUIVer, sRptGenCompReport, sRptGenCompRptID, sRptGenServer, sRptGenApp, sRptGenService, sSecKeyRLName;
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenUIApp"      ), sRptGenUIApp      );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenUIVer"      ), sRptGenUIVer      );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenCompReport" ), sRptGenCompReport );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenCompRptID"  ), sRptGenCompRptID  );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenServer"     ), sRptGenServer     );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenApp"        ), sRptGenApp        );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RptGenService"    ), sRptGenService    );
         			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SecKeyRLName"     ), sSecKeyRLName     );

						int iRptGenRetVal = GenerateReport_CEC( sXMLResultsFileName.toLocal8Bit().constData() /*sProjPath, sResFN*/, sCACertPath.toLocal8Bit().constData(),
																sRptGenCompReport.toLocal8Bit().constData(), sRptGenUIApp.toLocal8Bit().constData(), sRptGenUIVer.toLocal8Bit().constData(), "none" /*Signature*/,
																"none" /*PublicKey*/, NULL /*PrivateKey*/, 
																(sProxyServerAddress.isEmpty()     ? NULL : sProxyServerAddress.toLocal8Bit().constData()), 
																(sProxyServerCredentials.isEmpty() ? NULL : sProxyServerCredentials.toLocal8Bit().constData()),
																sPDFOnly.toLocal8Bit().constData(), sDebugRpt.toLocal8Bit().constData(), bVerbose, bSilent, bSendRptSignature, 
																sRptGenCompRptID.toLocal8Bit().constData(), sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), 
																sRptGenService.toLocal8Bit().constData(), sSecKeyRLName.toLocal8Bit().constData(), NULL /*pszOutputPathFile*/, 
																sProxyServerType.toLocal8Bit().constData(), 
																(sNetComLibrary.isEmpty() ? NULL : sNetComLibrary.toLocal8Bit().constData()) );		// SAC 11/5/15

// GOOD - from UI
// - GenerateReport_CEC( 'C:\WSF\devLibs\CompMgr\src\BEM-open\bin\Res\Projects\Samples-2016\1storyExample3-sv - AnalysisResults.xml', 
// 								'C:\WSF\devLibs\CompMgr\src\BEM-open\bin\Release_VC12', 
// 								'CF1R_NCB_PRF16', 'CBECC-Res', '21', 'none', 'none', '(null)', '(null)', '(null)', 'true', 'true', true, false, false, 
// 								'BEES', 't24docs.com', 'ReportGeneratorResStage', 'ReportingService.svc', 'SetReportKeys',
//                        'C:\WSF\devLibs\CompMgr\src\BEM-open\bin\Res\Projects\Samples-2016\1storyExample3-sv - AnalysisResults-BEES.pdf', 'Http', '(null)' )
// 
// BAD - via Analysis
// - GenerateReport_CEC( 'C:\WSF\devLibs\CompMgr\src\BEM-open\bin\Res\Projects\Samples-2016\1storyExample3-sv2 - AnalysisResults.xml', 
// 								'C:\WSF\devLibs\CompMgr\src\BEM-open\bin\Release_VC12', 
// 								'CF1R_NCB_PRF16', 'CBECC-Res', '21', 'none', 'none', '(null)', '', '', 'true', 'true', true, false, false, 
// 								'BEES', 't24docs.com', 'ReportGeneratorResStage', 'ReportingService.svc', 'SetReportKeys',
//                        '(null)', 'Http', '' )

									if (bVerbose || iRptGenRetVal != 0)
									{	sLogMsg = QString( "      generation of %1 compliance report %2 (returned %3)" ).arg( (iRpt==0 ? "pdf" : "full"), (iRptGenRetVal==0 ? "succeeded" : "failed"), QString::number(iRptGenRetVal) );
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
						if (iRptGenRetVal != 0)
						{	sErrorMsg = QString( "ERROR:  Error encountered generating compliance report file:  %1" ).arg( sOutRptFN );
							iRetVal = BEMAnal_CECRes_CompRptGenError;
						}
						else
						{	long lOne = 1;
							QString sWrittenDBID = (iRpt==0 ? "Proj:CompRptPDFWritten" : "Proj:CompRptXMLWritten");
					      BEMPX_SetBEMData( BEMPX_GetDatabaseID( sWrittenDBID ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
						}
					}
				}
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}
	// end of: COMPLIANCE REPORT GENERATION   - SAC 8/14/13
	// ----------
						dTimeToReport += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

	// SAC 5/11/15 - new code to store analysis results back to oringal project file, which is much more efficient than doing it after analysis completes abd 
		if (ResRetVal_ContinueProcessing( iRetVal ) && (bStoreResultsToModelInput || bStoreDetailedResultsToModelInput))
		{	// copy EUseSummary & EnergyUse objects from final run into the initial user model
			QString sResCopyErrMsg;
			int iResCopyRetVal = CopyAnalysisResultsObjects( sResCopyErrMsg, "final" /*runID*/, iNumRuns /*iBEMProcIdxSrc*/, 0 /*iBEMProcIdxDest*/, bStoreDetailedResultsToModelInput );
			assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
			if (iResCopyRetVal > 0)
			{	if (sErrorMsg.isEmpty())
					sErrorMsg = QString( "ERROR:  Error encountered copying final results into user model:  %1" ).arg( sResCopyErrMsg );
				switch (iResCopyRetVal)
				{	case 34 :  iRetVal = BEMAnal_CECRes_BadResultsObjTypesU;	break;
					case 35 :  iRetVal = BEMAnal_CECRes_ResultsCopyErrorU  ;	break;
					default :	assert( FALSE );	break;
				}
			}
			else
			{	int iPrevActiveModel = BEMPX_GetActiveModel();
				BEMPX_SetActiveModel( 0 );

			// Set SoftwareVersion to BEMBase Project
				if (pszUIVersionString && strlen( pszUIVersionString ) > 0)
				{	long lDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "Proj:SoftwareVersion" );
					QString sProjSoftwareVer;
					if (lDBID_Proj_SoftwareVersion > 0 &&
							(!BEMPX_GetString( lDBID_Proj_SoftwareVersion, sProjSoftwareVer ) || sProjSoftwareVer.isEmpty() || sProjSoftwareVer.compare( pszUIVersionString ) != 0) )
						BEMPX_SetBEMData( lDBID_Proj_SoftwareVersion, BEMP_Str, (void*) pszUIVersionString );
				}

			// Set BEMBase version ID value
				int iBEMCID_BEMVersion = BEMPX_GetDBComponentID( "BEMVersion" );
				long lBEMVerID = (iBEMCID_BEMVersion > 0 ? BEMPX_GetNumPropertyTypes( (int) iBEMCID_BEMVersion ) : 0);
				if (lBEMVerID > 0)
				{	long lCurBEMVer = 0;
					long lDBID_Proj_BEMVersion = BEMPX_GetDatabaseID( "Proj:BEMVersion" );
					if ( lDBID_Proj_BEMVersion > 0 &&
							(!BEMPX_GetInteger( lDBID_Proj_BEMVersion, lCurBEMVer ) || lCurBEMVer != lBEMVerID) )
						BEMPX_SetBEMData( lDBID_Proj_BEMVersion, BEMP_Int, (void*) &lBEMVerID );
				}

			// SAVE PROJECT FILE
				std::string sProjPathFile = sFullModelPathFile.toLocal8Bit().constData();
				bool bFileSaveAllDefinedProperties = false;	// (GetCSVOptionValue( "FileSaveAllDefinedProperties", 0, saCSVOptions ) > 0);
				// SAC 6/14/16 - mod to ensure EITHER .xml OR .ribdx/.ribd16x are interpretted as XML files
				std::string sProjFileLastThreeChars = sProjPathFile.substr( sProjPathFile.size()-3, 3 );
				std::string sProjFileLastChar       = sProjPathFile.substr( sProjPathFile.size()-1, 1 );
				int iFileType = (boost::iequals( sProjFileLastThreeChars.c_str(), "xml" ) || boost::iequals( sProjFileLastChar.c_str(), "x" ) ? BEMFT_XML : BEMFT_Std);
				if (!BEMPX_WriteProjectFile( sProjPathFile.c_str(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/, TRUE /*bSupressAllMsgBoxes*/,
														iFileType, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, -1 /*lTime-1*/ /*lModDate*/ ))
	      	{	assert( FALSE );  // failure to save file
	      		iRetVal = BEMAnal_CECRes_InputSaveFailed;		// Attempt to save project inputs (including results) following analysis failed
	      	}
				BEMPX_SetActiveModel( iPrevActiveModel );
			}
						dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();
		}
	}

	bool bAnalAborted = (bAllowAnalysisAbort && pAnalProgCallbackFunc && slAnalysisProgressCallbackRetVal > 0);
#ifdef CM_QTGUI
	if (!bAnalAborted && bAllowAnalysisAbort && sqt_progress && sqt_progress->wasCanceled())
		bAnalAborted = true;
#endif

	// SAC 6/5/14 - new callback mechanism - report return value indicating abort via calling application callback
	if (pAnalProgCallbackFunc)
	{	if (slAnalysisProgressCallbackRetVal == 0 && !bAnalAborted)		// report 100% complete only for SUCCESSFUL analysis ???  (right now reporting 100% anytime analysis NOT aborted)
		{	long lCBRetVal = pAnalProgCallbackFunc( analysisProgressType_PercentProgress, 100 );
			if (lCBRetVal > 0)
				slAnalysisProgressCallbackRetVal = lCBRetVal;
		}
		if (slAnalysisProgressCallbackRetVal > 0)
		{	iRetVal = BEMAnal_CECRes_AbortViaCallback;
			//if (TRUE)  // bVerbose)
			{	sLogMsg = QString( "      Analysis aborted due to callback function return value of %1 (value must be 0 to continue processing)." ).arg( QString::number(slAnalysisProgressCallbackRetVal) );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
//			FreeCSEDLLIfLoaded();		// temporary ?? - need to unload CSE DLLs if user aborts analysis, else next simulation will bomb
	}	}

// temporary ?? - need to unload CSE DLLs if user aborts analysis, else next simulation will bomb
#ifdef CM_QTGUI
	if (bAllowAnalysisAbort && sqt_progress && sqt_progress->wasCanceled())
	{	iRetVal = BEMAnal_CECRes_UserAbortedAnalysis;
		//if (TRUE)  // bVerbose)
			BEMPX_WriteLogFile( "      Analysis aborted by user via progress dialog button.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//		FreeCSEDLLIfLoaded();
	}

// QT Progress Dialog stuff
	if (sqt_progress && sqt_win)
	{	if (bVerbose)  // SAC 1/31/13
			BEMPX_WriteLogFile( "      about to hide QT progress dialog", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		sqt_progress->setValue(100);
		sqt_win->repaint();
	}
#endif

	if (!sErrorMsg.isEmpty())
	{	BEMPX_WriteLogFile( sErrorMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		BEMPX_AddRulesetError( sErrorMsg.toLocal8Bit().constData() );  // SAC 1/9/13
	}

	slCurrentProgress = 0;
	// SAC 6/5/14 - new callback mechanism - reset static function pointer
	if (pAnalProgCallbackFunc)
	{	spAnalProgCallbackFunc = NULL;
		slAnalysisProgressCallbackRetVal = 0;
	}
	sbAllowCallbackAbort = bStoreAllowCallbackAbort;	// SAC 4/5/15

// SAC 1/12/15 - added code to setup FINAL result log message (including analysis duration stats)
	QString sAnalResLogMsg, sAnalTimeStats, sResTemp1, sResTemp2, sResTemp3, sResTemp4;
	if (iRetVal == BEMAnal_CECRes_RuleProcAbort)
		sAnalResLogMsg = "Analysis aborted";
	else if (!bAnalysisPriorToRptGenOK /*iRetVal != 0*/ || sXMLResultsFileName.isEmpty() || !FileExists( sXMLResultsFileName.toLocal8Bit().constData() ))	// added logic to prevent "errant" report if only error occurred during/after report generation
		sAnalResLogMsg = "Analysis errant";
	else if (!bFullComplianceAnalysis || !bPerformSimulations || bBypassCSE || bBypassDHW)
		sAnalResLogMsg = "Analysis incomplete";
	else if (!BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:PassFail"        ), sResTemp1, TRUE, 0, -1, 0 )  ||
				!BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:Enduse11[8]"     ), sResTemp2, TRUE, 0, -1, 0 )  ||
				!BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:PctSavCmpTDVLbl" ), sResTemp3, TRUE, 0, -1, 0 ))
		sAnalResLogMsg = "Analysis result unknown";
	else
	{	sAnalResLogMsg = QString( "Analysis result:  %1  (TDV margin: %2 (%3%))" ).arg( sResTemp1, sResTemp2, sResTemp3 );
		// SAC 4/6/15 - append design rating onto main result string (if design rating run performed and design rating >= 0)
		double fDesignRating;
		if (lDesignRatingRunID > 0 && BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:DesignRating" ), fDesignRating, 0, -1,  0 /*iOccur*/ ) && fDesignRating >= 0)
		{	sResTemp4 = QString( ", Design Rating %1" ).arg( QString::number(fDesignRating, 'f', 1) );
			sAnalResLogMsg += sResTemp4;
		}
		//if (sResTemp2.indexOf(',') > 0)
		//{	sResTemp2  = '\"' + sResTemp2;
		//	sResTemp2 += '\"';
		//}
		if (!bInitHourlyResults || !bPerformRangeChecks || bIgnoreFileReadErrors || (lBypassRuleLimits > 0) ||
			 (lEnableResearchMode > 0) || bCSEIncludeFileUsed || iSimSpeedOption > 0 || bDHWCalcMethodUserSpecified)
			sAnalResLogMsg += " (result not certified due to analysis option(s))";
	}
						dTimeToOther += DeltaTime( tmMark );		// SAC 1/12/15 - log time spent & reset tmMark
						dTimeOverall += DeltaTime( tmAnalStartTime );	// log time spent over the entire analysis
	double dTimeTotModelPrep = 0.0, dTimeTotProcResults = 0.0; 
	for (int itm=0; itm < MAX_TimeArray_Res; itm++)
	{	dTimeTotModelPrep   += dTimeToPrepModel[itm];
		dTimeTotProcResults += dTimeToProcResults[itm];
	}
	sAnalTimeStats = QString( "  Processing time:  Overall %1 / CSE %2 / ModelPrep %3 / ResultsProcessing %4 / ReportGen %5 / ResXMLWriting %6 / Model&SecurChks %7 / Model&HrlyCSVExports %8 / DHWSim %9 / LoadModel %10 / Other %11" ).arg(
										QString::number(dTimeOverall, 'f', 1), QString::number(dTimeCSESim, 'f', 1), QString::number(dTimeTotModelPrep, 'f', 2), QString::number(dTimeTotProcResults, 'f', 2),
										QString::number(dTimeToReport, 'f', 1), QString::number(dTimeToWriteResultsXML, 'f', 2), QString::number(dTimeToModelAndSecurityChecks, 'f', 2) ).arg(
										QString::number(dTimeToWriteModelAndHrlyCSVs, 'f', 2), QString::number(dTimeDHWSim, 'f', 2), QString::number(dTimeToLoadModel, 'f', 2), QString::number(dTimeToOther, 'f', 2) );
	sAnalResLogMsg += sAnalTimeStats;
	BEMPX_WriteLogFile( sAnalResLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	if (bVerbose)  // SAC 1/31/13
	{	sLogMsg = QString( "      Final return value from CMX_PerformSimulation_CECRes():  %1" ).arg( QString::number(iRetVal) );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	if (bRestoreBEMProcLogTimeStampSetting)		// SAC 11/17/13 - restore BEMProc log timestamp setting (if it was toggled during analysis)
		BEMPX_EnableLogTimeStamps( bInitialBEMProcLogTimeStamp );
	BEMPX_RefreshLogFile();	// SAC 5/19/14

// QT Progress Dialog stuff
#ifdef CM_QTGUI
// TESTING
	if (bDisplayProgress && sqt_win)
	{	if (bVerbose)  // SAC 1/31/13
			BEMPX_WriteLogFile( "      about to clean up QT progress dialog", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		sqt_win->close();
	}
	// SAC 11/17/16 - cleanup minor memory leak
	if (bDisplayProgress)
	{	if (pqt_progress)
			delete pqt_progress;
		if (pqt_win)
			delete pqt_win;
		//if (pqt_layout)  - deallocated by above routines(?)
		//	delete pqt_layout;
	}
	if (bQtAppInitHere)	// SAC 11/11/15
	{	delete sq_app;
		sq_app = NULL;
	}

//bool QWidget::close () [slot]
//Closes this widget. Returns true if the widget was closed; otherwise returns false.
//First it sends the widget a QCloseEvent. The widget is hidden if it accepts the close event. If it ignores the event, nothing happens. The default implementation of QWidget::closeEvent() accepts the close event.
//If the widget has the Qt::WA_DeleteOnClose flag, the widget is also deleted. A close events is delivered to the widget no matter if the widget is visible or not.

	sqt_progress = NULL;
	sqt_win = NULL;
#endif

	return iRetVal;
}
	
	
/////////////////////////////////////////////////////////////////////////////

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error retrieving Proj:AnalysisType and/or Proj:CondFloorArea
//											 2 : Error retrieving Proj:ResultSummary object
//											 3 : Error retrieving Proj:ResultSummary object index
//											 4 : Error retrieving EUseSummary:PassFail (compliance result)
//											 5 : Error retrieving one or more Proj:RunResults results objects
//											 6 : Error retrieving one or more Proj:RunResults results object indices
//											 7 : Error: Unexpected number of RunResults objects or error retrieving WorstOrientation index
//											 8 : Error: Unable to identify which run to return results for (based on pszRunOrientation argument)
//											 9 : Error: Unrecognized results format version argument (-1 => current, else 1-N)
//
// SAC 8/6/13 - added pszRunOrientation argument to facilitate return of orientation-specific results (when performing All Orientation analysis)
#define  CSVFmtVer_CECRes  8		// SAC 8/24/14 - 2->3  - SAC 11/24/14 - 3->4  - SAC 3/31/15 - 4->5  - SAC 2/1/16 - 5->6  - SAC 10/7/16 - 7->8
int CMX_PopulateCSVResultSummary_CECRes(	char* pszResultsString, int iResultsStringLength, const char* pszRunOrientation /*=NULL*/,
														int iResultsFormatVersion /*=-1*/, const char* pszProjectPathFileName /*=NULL*/ )
{	int iRetVal = 0;
	long lAnalysisType, lAllOrientations;
	double fCompMargin=0.0, fCondFloorArea=0.0;
	QString sRunTitle, sAnalysisType, sPassFail;  //, sRuleSetID, sRuleSetVer;
	BOOL bExpectStdDesResults = TRUE;
	BOOL bExpectDesignRatingResults = FALSE;		// SAC 3/31/15

	if (	!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), lAnalysisType    ) ||
			!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), sAnalysisType    ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AllOrientations" ), lAllOrientations ) ||
			!BEMPX_GetFloat(	 BEMPX_GetDatabaseID( "Proj:CondFloorArea"   ), fCondFloorArea   ) )
		iRetVal = 1;
//	else if (!RuleProcGetRulesetID( sRuleSetID, sRuleSetVer ))
//		iRetVal = 2;
	else if (iResultsFormatVersion != -1 && (iResultsFormatVersion < 1 || iResultsFormatVersion > CSVFmtVer_CECRes))
		iRetVal = 9;		// Error: Unrecognized results format version argument (-1 => current, else 1-N)
	else
	{	int iError;
		if (iResultsFormatVersion == -1)
			iResultsFormatVersion = CSVFmtVer_CECRes;
		bExpectStdDesResults = (sAnalysisType.indexOf( "Standard" ) > 0 || sAnalysisType.indexOf( "Compliance" ) > 0);
		long lDesignRatingCalcs;		// SAC 3/31/15
		bExpectDesignRatingResults = (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:DesignRatingCalcs" ), lDesignRatingCalcs ) && lDesignRatingCalcs > 0);
		int iBEMBaseModelCount = BEMPX_GetModelCount();   // SAC 3/28/16

		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle" ), sRunTitle );
		int iEnergyUseObjectSets = 1;  // SAC 8/6/13
		QString sTDVSavPctTot, sTDVSavPctComp, sCAHPKickDOE, sCAHPKickFutCode, sCAHPKickHELtg,
					sCAHPKickTDV100, sCAHPKickTDV60, sCAHPScoreInitVal, sCAHPIncInit, sCAHPScoreFinal, sCAHPIncFinal;
		QString sProjPathFile;
		if (pszProjectPathFileName && strlen( pszProjectPathFileName ) > 0)
			sProjPathFile.sprintf( "\"%s\",", pszProjectPathFileName );
		else
			sProjPathFile = ",";

		long lEnergyCodeYear;	// SAC 10/6/16
		if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYear ))
			lEnergyCodeYear = 0;

		if (iRetVal==0 && lAnalysisType == 13)
		{	if (lAllOrientations > 0)  // SAC 8/6/13
				iEnergyUseObjectSets = 4;
			BEMObject* pObjResultSummary = NULL;
			if (BEMPX_GetObject( BEMPX_GetDatabaseID( "Proj:ResultSummary" ), pObjResultSummary ) && pObjResultSummary && pObjResultSummary->getClass())
			{	int iObjIdx = BEMPX_GetObjectIndex( pObjResultSummary->getClass(), pObjResultSummary );		assert( iObjIdx >= 0 );
				if (iObjIdx >= 0)
				{	sPassFail = "--";  // return PassFail string if full analysis not executed
					if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:PassFail" ), sPassFail, FALSE, 0, BEMP_Str, iObjIdx ) && bExpectStdDesResults)
						iRetVal = 4;

					if (iResultsFormatVersion >= 4)		// SAC 11/24/14
					{
						if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:PctSavingsTDV"    ), sTDVSavPctTot , FALSE, 11, -1, iObjIdx ))
							sTDVSavPctTot.clear();
						if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:PctSavingsCmpTDV" ), sTDVSavPctComp, FALSE, 11, -1, iObjIdx ))
							sTDVSavPctComp.clear();

						long lCAHPProgram;
						if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CAHPProgram" ), lCAHPProgram ) && lCAHPProgram > 0)
						{
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPKickDOE"      ), sCAHPKickDOE     , FALSE,  0, -1, iObjIdx ))
								sCAHPKickDOE.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPKickFutCode"  ), sCAHPKickFutCode , FALSE,  0, -1, iObjIdx ))
								sCAHPKickFutCode.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPKickHELtg"    ), sCAHPKickHELtg   , FALSE,  0, -1, iObjIdx ))
								sCAHPKickHELtg.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPKickTDV100"   ), sCAHPKickTDV100  , FALSE,  0, -1, iObjIdx ))
								sCAHPKickTDV100.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPKickTDV60"    ), sCAHPKickTDV60   , FALSE,  0, -1, iObjIdx ))
								sCAHPKickTDV60.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPScoreInitVal" ), sCAHPScoreInitVal, FALSE,  0, -1, iObjIdx ))
								sCAHPScoreInitVal.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPIncInit"      ), sCAHPIncInit     , FALSE,  2, -1, iObjIdx ))
								sCAHPIncInit.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPScoreFinal"   ), sCAHPScoreFinal  , FALSE,  0, -1, iObjIdx ))
								sCAHPScoreFinal.clear();
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:CAHPIncFinal"     ), sCAHPIncFinal    , FALSE,  2, -1, iObjIdx ))
								sCAHPIncFinal.clear();
						}
					}
				}
				else
					iRetVal = 3;
			}
			else
				iRetVal = 2;
		}

		int iEU;
		double  faStdTDV[11],  faStdKWH[10],  faStdTherms[10],  faStdOther[10],  faStdKW[11];
		double faPropTDV[13], faPropKWH[13], faPropTherms[10], faPropOther[10], faPropKW[13], fPropPVCredit[2]={0,0};	// SAC 10/7/16 - expanded TDV, KWH & KW arrays to 13 to handle PV @ [12]
		double faDRtgTDV[11], faDRtgKWH[10], faDRtgTherms[10], faDRtgOther[10], faDRtgKW[11], fDRtgPctSavTDV, fDesignRating=0;		// TDV & KW arrays sized to include CompTotal to simplify retrieval, but those NOT written to record
		double faDRPropTDV[11], faDRPropKWH[10], faDRPropTherms[10], faDRPropOther[10], faDRPropKW[11];		// SAC 5/1/15 - separate DRtg proposed results (for now only lighting elec may vary)
		double fDRPropKWH_PV=0, fDRPropKW_PV=0, fDRtg_NoPV=0, fDRtg_PVOnly=0;		// SAC 2/1/16 - added DR Prop PV elec use & demand and design rating minus PV  - SAC 3/16/16 - added additional EDR variables
		double fPropKWH_PV=0, fPropKW_PV=0;		// SAC 10/7/16 - added in proposed PV KWH & KW w/ format 8 mods to support 2019 analysis
		long lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResults" );			assert( lDBID_Proj_RunResults > 0 );
      long lDBID_EnergyUse_CompMarginTDV    = BEMPX_GetDatabaseID( "EnergyUse:CompMarginTDV"    );
      long lDBID_EnergyUse_PropElecEnergy   = BEMPX_GetDatabaseID( "EnergyUse:PropElecEnergy"   );
      long lDBID_EnergyUse_PropNatGasEnergy = BEMPX_GetDatabaseID( "EnergyUse:PropNatGasEnergy" );
      long lDBID_EnergyUse_PropOtherEnergy  = BEMPX_GetDatabaseID( "EnergyUse:PropOtherEnergy"  );
      long lDBID_EnergyUse_StdElecEnergy    = BEMPX_GetDatabaseID( "EnergyUse:StdElecEnergy"    );
      long lDBID_EnergyUse_StdNatGasEnergy  = BEMPX_GetDatabaseID( "EnergyUse:StdNatGasEnergy"  );
      long lDBID_EnergyUse_StdOtherEnergy   = BEMPX_GetDatabaseID( "EnergyUse:StdOtherEnergy"   );
      long lDBID_EnergyUse_ProposedTDV      = BEMPX_GetDatabaseID( "EnergyUse:ProposedTDV"      );
      long lDBID_EnergyUse_StandardTDV      = BEMPX_GetDatabaseID( "EnergyUse:StandardTDV"      );
      long lDBID_EnergyUse_PropElecDemand   = BEMPX_GetDatabaseID( "EnergyUse:PropElecDemand"   );		// SAC 8/24/14
      long lDBID_EnergyUse_StdElecDemand    = BEMPX_GetDatabaseID( "EnergyUse:StdElecDemand"    );
      long lDBID_EnergyUse_DRtgElecEnergy   = BEMPX_GetDatabaseID( "EnergyUse:DRtgElecEnergy"   );		// SAC 3/31/15
      long lDBID_EnergyUse_DRtgNatGasEnergy = BEMPX_GetDatabaseID( "EnergyUse:DRtgNatGasEnergy" );
      long lDBID_EnergyUse_DRtgOtherEnergy  = BEMPX_GetDatabaseID( "EnergyUse:DRtgOtherEnergy"  );
      long lDBID_EnergyUse_DesignRatingTDV  = BEMPX_GetDatabaseID( "EnergyUse:DesignRatingTDV"  );
      long lDBID_EnergyUse_DRtgElecDemand   = BEMPX_GetDatabaseID( "EnergyUse:DRtgElecDemand"   );
      long lDBID_EnergyUse_DRtgPctSavTDV    = BEMPX_GetDatabaseID( "EnergyUse:DRtgPctSavTDV"    );
		BEMObject* pObjEnergyUse = NULL;
		if (iRetVal==0)
		{	if (!bExpectStdDesResults)
			{	faStdTDV[ 10] = 0;		faStdKW[ 10] = 0;
				for (iEU=0; iEU<10; iEU++)
				{	faStdTDV[iEU] = 0;	faStdKWH[iEU] = 0;	faStdTherms[iEU] = 0;	faStdOther[iEU] = 0;		faStdKW[iEU] = 0;
				}
			}
			if (!bExpectDesignRatingResults)		// SAC 3/31/15
			{	faDRtgTDV[10] = 0;		faDRtgKW[10] = 0;
				faDRPropTDV[10] = 0;		faDRPropKW[10] = 0;	// SAC 5/1/15
				for (iEU=0; iEU<10; iEU++)
				{	faDRtgTDV[iEU] = 0;		faDRtgKWH[iEU] = 0;		faDRtgTherms[iEU] = 0;		faDRtgOther[iEU] = 0;		faDRtgKW[iEU] = 0;
					faDRPropTDV[iEU] = 0;	faDRPropKWH[iEU] = 0;	faDRPropTherms[iEU] = 0;	faDRPropOther[iEU] = 0;		faDRPropKW[iEU] = 0;
				}
			}

		// set EnergyUse object reference offset based on which set of results is desired - SAC 8/6/13
			if (iEnergyUseObjectSets > 1)
			{	assert( iEnergyUseObjectSets == 4 && lAllOrientations > 0 );	// N,E,S,W is only known case here
		      int iCID_EnergyUse = BEMPX_GetDBComponentID( "EnergyUse" );		assert( iCID_EnergyUse > 0 );
				int iNumEnergyUseObjects = BEMPX_GetNumObjects( iCID_EnergyUse );
				assert( iNumEnergyUseObjects == (4 * 11) );	// current set (as of 8/6/13)
				long lWorstOrientation;
				if (iNumEnergyUseObjects < 40 || !BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:WorstOrientation" ), lWorstOrientation ))
					iRetVal = 7;
				else
				{	if (pszRunOrientation == NULL || strlen( pszRunOrientation ) < 1)
					{	}		// do nothing here - Proj:RunResults array populated w/ worst case, which is the default if no specific orientation is requested
					else if (strlen( pszRunOrientation ) == 1)
					{	     if (pszRunOrientation[0]=='N' || pszRunOrientation[0]=='n')
																												lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsN" );
						else if (pszRunOrientation[0]=='E' || pszRunOrientation[0]=='e')
																												lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsE" );
						else if (pszRunOrientation[0]=='S' || pszRunOrientation[0]=='s')
																												lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsS" );
						else
																												lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsW" );
					}
					else
					{	BEMObject* pEUseSummaryObj = BEMPX_GetObjectByName( BEMPX_GetDBComponentID( "EUseSummary" ), iError, pszRunOrientation );
						int iEUseSummaryObjIdx = (pEUseSummaryObj==NULL ? -1 : BEMPX_GetObjectIndex( pEUseSummaryObj->getClass(), pEUseSummaryObj ));
						if (pEUseSummaryObj == NULL || iEUseSummaryObjIdx < 0 || iEUseSummaryObjIdx > 4)
							iRetVal = 8;
						else
						{	switch (iEUseSummaryObjIdx)
							{	case  0 :																								break;	// "worst case" run results
								case  1 :	lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsN" );	break;	// 'N'
								case  2 :	lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsE" );	break;	// 'E'
								case  3 :	lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsS" );	break;	// 'S'
								case  4 :	lDBID_Proj_RunResults = BEMPX_GetDatabaseID( "Proj:RunResultsW" );	break;	// 'W'
								default :	assert( FALSE );
							}
						}
					}						assert( lDBID_Proj_RunResults > 0 );
				}
			}

			if (iResultsFormatVersion >= 2)		// SAC 11/15/13
			{	BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:PVCredit[1]" ), fPropPVCredit[0], 0, -1, -1, BEMO_User, ((bExpectDesignRatingResults && iBEMBaseModelCount > 2) ? iBEMBaseModelCount-2 : -1) );
				fPropPVCredit[0] = -fPropPVCredit[0];
				if (iResultsFormatVersion >= 5)
				{	BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:PVCredit[2]" ), fPropPVCredit[1] );
					fPropPVCredit[1] = -fPropPVCredit[1];
				}
			}

			for (iEU=0; (iRetVal==0 && iEU<12); iEU++)		// SAC 2/1/16 - iEUs 11->12 to include PV
			{	if (iEU==11)
					iEU++;	// skip 12, go onto 13
				if (BEMPX_GetObject( lDBID_Proj_RunResults+iEU, pObjEnergyUse ) && pObjEnergyUse && pObjEnergyUse->getClass())
				{	int iObjIdx = BEMPX_GetObjectIndex( pObjEnergyUse->getClass(), pObjEnergyUse );		assert( iObjIdx >= 0 );
					if (iObjIdx >= 0)
					{	if (iEU != 12)		// SAC 2/1/16
						{
							BEMPX_GetFloat( 			lDBID_EnergyUse_ProposedTDV     ,    faPropTDV[iEU], 0, BEMP_Flt, iObjIdx );
							BEMPX_GetFloat( 			lDBID_EnergyUse_PropElecDemand  ,    faPropKW[ iEU], 0, BEMP_Flt, iObjIdx );
							if (bExpectStdDesResults)
							{	BEMPX_GetFloat( 		lDBID_EnergyUse_StandardTDV     ,     faStdTDV[iEU], 0, BEMP_Flt, iObjIdx );
								BEMPX_GetFloat( 		lDBID_EnergyUse_StdElecDemand   ,     faStdKW[ iEU], 0, BEMP_Flt, iObjIdx );
							}
							if (bExpectDesignRatingResults)		// SAC 3/31/15
							{	BEMPX_GetFloat( 		lDBID_EnergyUse_DesignRatingTDV ,    faDRtgTDV[  iEU], 0, BEMP_Flt, iObjIdx );
								BEMPX_GetFloat( 		lDBID_EnergyUse_DRtgElecDemand  ,    faDRtgKW[   iEU], 0, BEMP_Flt, iObjIdx );
								BEMPX_GetFloat( 		lDBID_EnergyUse_ProposedTDV   +1,    faDRPropTDV[iEU], 0, BEMP_Flt, iObjIdx );
								BEMPX_GetFloat( 		lDBID_EnergyUse_PropElecDemand+1,    faDRPropKW[ iEU], 0, BEMP_Flt, iObjIdx );
							}
							if (iEU < 10)
							{	BEMPX_GetFloat(		lDBID_EnergyUse_PropElecEnergy  ,    faPropKWH[iEU], 0, BEMP_Flt, iObjIdx );		   faPropKWH[iEU] =    faPropKWH[iEU] * fCondFloorArea / 3.413;
								BEMPX_GetFloat(		lDBID_EnergyUse_PropNatGasEnergy, faPropTherms[iEU], 0, BEMP_Flt, iObjIdx );		faPropTherms[iEU] = faPropTherms[iEU] * fCondFloorArea / 100  ;
								BEMPX_GetFloat(		lDBID_EnergyUse_PropOtherEnergy ,  faPropOther[iEU], 0, BEMP_Flt, iObjIdx );		 faPropOther[iEU] =  faPropOther[iEU] * fCondFloorArea / 1000 ;
								if (bExpectStdDesResults)
								{	BEMPX_GetFloat(	lDBID_EnergyUse_StdElecEnergy   ,     faStdKWH[iEU], 0, BEMP_Flt, iObjIdx );		    faStdKWH[iEU] =     faStdKWH[iEU] * fCondFloorArea / 3.413;
									BEMPX_GetFloat(	lDBID_EnergyUse_StdNatGasEnergy ,  faStdTherms[iEU], 0, BEMP_Flt, iObjIdx );		 faStdTherms[iEU] =  faStdTherms[iEU] * fCondFloorArea / 100  ;
									BEMPX_GetFloat(	lDBID_EnergyUse_StdOtherEnergy  ,   faStdOther[iEU], 0, BEMP_Flt, iObjIdx );		  faStdOther[iEU] =   faStdOther[iEU] * fCondFloorArea / 1000 ;
								}
								if (bExpectDesignRatingResults)		// SAC 3/31/15
								{	BEMPX_GetFloat(	lDBID_EnergyUse_DRtgElecEnergy    ,      faDRtgKWH[iEU], 0, BEMP_Flt, iObjIdx );		     faDRtgKWH[iEU] =      faDRtgKWH[iEU] * fCondFloorArea / 3.413;
									BEMPX_GetFloat(	lDBID_EnergyUse_DRtgNatGasEnergy  ,   faDRtgTherms[iEU], 0, BEMP_Flt, iObjIdx );		  faDRtgTherms[iEU] =   faDRtgTherms[iEU] * fCondFloorArea / 100  ;
									BEMPX_GetFloat(	lDBID_EnergyUse_DRtgOtherEnergy   ,    faDRtgOther[iEU], 0, BEMP_Flt, iObjIdx );		   faDRtgOther[iEU] =    faDRtgOther[iEU] * fCondFloorArea / 1000 ;
									BEMPX_GetFloat(	lDBID_EnergyUse_PropElecEnergy  +1,    faDRPropKWH[iEU], 0, BEMP_Flt, iObjIdx );		   faDRPropKWH[iEU] =    faDRPropKWH[iEU] * fCondFloorArea / 3.413;
									BEMPX_GetFloat(	lDBID_EnergyUse_PropNatGasEnergy+1, faDRPropTherms[iEU], 0, BEMP_Flt, iObjIdx );		faDRPropTherms[iEU] = faDRPropTherms[iEU] * fCondFloorArea / 100  ;
									BEMPX_GetFloat(	lDBID_EnergyUse_PropOtherEnergy +1,  faDRPropOther[iEU], 0, BEMP_Flt, iObjIdx );		 faDRPropOther[iEU] =  faDRPropOther[iEU] * fCondFloorArea / 1000 ;
								}
							}
							else if (iEU==10 && bExpectStdDesResults)
								BEMPX_GetFloat( lDBID_EnergyUse_CompMarginTDV, fCompMargin, 0, BEMP_Flt, iObjIdx );
							if (iEU== 9 && bExpectDesignRatingResults)		// SAC 3/31/15
							{	BEMPX_GetFloat( lDBID_EnergyUse_DRtgPctSavTDV, fDRtgPctSavTDV, 0, BEMP_Flt, iObjIdx );
			// SAC 3/16/16 - moved down below to grab value directly our of summary results (to INCLUDE a fuel-equalizing TDV adjustment not present in TDV results alone)
			//					fDesignRating = 100 - fDRtgPctSavTDV;
						}	}
						else		// iEU == 12 => PV - SAC 2/1/16
						{
							faPropKWH[iEU] = 0.0;	faPropKW[ iEU] = 0.0;	faPropTDV[iEU] = 0.0;
							if (iResultsFormatVersion >= 8 && lEnergyCodeYear >= 2019)		// SAC 10/7/16 - 2019 proposed PV
							{
								BEMPX_GetFloat(		lDBID_EnergyUse_PropElecEnergy  ,  faPropKWH[iEU], 0, BEMP_Flt, iObjIdx );		  faPropKWH[iEU] = faPropKWH[iEU] * fCondFloorArea / 3.413;
								BEMPX_GetFloat( 		lDBID_EnergyUse_PropElecDemand  ,  faPropKW[ iEU], 0, BEMP_Flt, iObjIdx );
								BEMPX_GetFloat( 		lDBID_EnergyUse_ProposedTDV     ,  faPropTDV[iEU], 0, BEMP_Flt, iObjIdx );
								if (bExpectStdDesResults)
								{	fDRPropKWH_PV = faPropKWH[iEU];	// DsgnRtg PV same as Proposed PV in 2019+ analysis
									fDRPropKW_PV  = faPropKW[ iEU];
							}	}
							else if (iResultsFormatVersion >= 6 && bExpectStdDesResults)		// SAC 2/1/16 - added DR Prop PV elec use & demand and design rating minus PV
							{	BEMPX_GetFloat(		lDBID_EnergyUse_PropElecEnergy+1,   fDRPropKWH_PV, 0, BEMP_Flt, iObjIdx );		  fDRPropKWH_PV = fDRPropKWH_PV * fCondFloorArea / 3.413;
								BEMPX_GetFloat( 		lDBID_EnergyUse_PropElecDemand+1,    fDRPropKW_PV, 0, BEMP_Flt, iObjIdx );
							}
						}
					}
					else
						iRetVal = 6;
				}
				else
					iRetVal = 5;
			}

		// moved Energy Design Rating retrieval to below
			QString sDRtg_Std=",";
			if (iResultsFormatVersion >= 6 && bExpectDesignRatingResults)		// SAC 3/16/16
			{	BEMObject* pObjResultSummary = NULL;
				if (BEMPX_GetObject( BEMPX_GetDatabaseID( "Proj:ResultSummary" ), pObjResultSummary ) && pObjResultSummary && pObjResultSummary->getClass())
				{	int iObjIdx = BEMPX_GetObjectIndex( pObjResultSummary->getClass(), pObjResultSummary );		assert( iObjIdx >= 0 );
					if (iObjIdx >= 0)
					{	BEMPX_GetFloat( 	BEMPX_GetDatabaseID( "EUseSummary:DesignRating"       ),  fDesignRating, 0, BEMP_Flt, iObjIdx );
						BEMPX_GetFloat( 	BEMPX_GetDatabaseID( "EUseSummary:DesignRatingNoPV"   ),  fDRtg_NoPV   , 0, BEMP_Flt, iObjIdx );
						BEMPX_GetFloat( 	BEMPX_GetDatabaseID( "EUseSummary:DesignRatingPVOnly" ),  fDRtg_PVOnly , 0, BEMP_Flt, iObjIdx );
						if (bExpectStdDesResults)	// SAC 10/27/16 - prevent reporting DRtg_Std when no std design run (ExEDR)
						{	double fDRtg_Std=0;
							BEMPX_GetFloat( 	BEMPX_GetDatabaseID( "EUseSummary:DesignRatingStd" ),  fDRtg_Std    , 0, BEMP_Flt, iObjIdx );
							sDRtg_Std = QString("%1,").arg( QString::number( fDRtg_Std ) );
						}
				}	}
			}

			if (iRetVal==0)
			{	long lRunDate = 0;
			   QString timeStamp;
			   //CTime locTime = CTime::GetCurrentTime();
				if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate ) && lRunDate > 0)
			   {	//CTime locTime = lRunDate;
					//timeStamp = locTime.Format("%Y-%b-%d %H:%M:%S");
					QDateTime locTime = QDateTime::currentDateTime();
					timeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");
				}
				else
					timeStamp = "<unknown analysis day/time>";

				QString sUIVer, sPrimVer, sSecVer, sRuleVer;
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"  ),	sUIVer   );
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ),	sPrimVer );
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SecSimEngingVer"  ),	sSecVer  );
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RulesetVersion"   ),	sRuleVer );

				QString sCompMargin=",", sDesignRating=",";
				if (bExpectStdDesResults)
					sCompMargin = QString("%1,").arg( QString::number( fCompMargin ) );
				if (bExpectDesignRatingResults)
					sDesignRating = QString("%1,").arg( QString::number( fDesignRating ) );

				QString sBeginFields, sPropEnergy, sStdEnergy, sVersionFields, sPropStdDemand, sDemSavAndCAHP, sDRtgEnergyDemand;
		// SAC 3/31/15 - revisions to populate return string is sections to avoid excessively numerous & long individual format statements
				if (iResultsFormatVersion >= 5)
					sBeginFields.sprintf( "\"%s\",%s\"%s\",\"%s\",\"%s\",%s%s", timeStamp.toLocal8Bit().constData(), sProjPathFile.toLocal8Bit().constData(), 
																						sRunTitle.toLocal8Bit().constData(), sAnalysisType.toLocal8Bit().constData(), 
																						sPassFail.toLocal8Bit().constData(), sCompMargin.toLocal8Bit().constData(), sDesignRating.toLocal8Bit().constData() );
				else
					sBeginFields.sprintf( "\"%s\",\"%s\",\"%s\",\"%s\",%s"     , timeStamp.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), 
																						sAnalysisType.toLocal8Bit().constData(), sPassFail.toLocal8Bit().constData(), sCompMargin.toLocal8Bit().constData() );

				if (iResultsFormatVersion >= 8)	// SAC 10/7/16 - added Proposed PV kWh & kW reporting 
					sPropEnergy.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",	// 43 doubles
										faPropKWH[0], faPropKWH[1], faPropKWH[2], faPropKWH[3], faPropKWH[4], faPropKWH[12/*PV*/], faPropKWH[5], faPropKWH[6], faPropKWH[7], faPropKWH[8], faPropKWH[9], 
										faPropTherms[0], faPropTherms[1], faPropTherms[2], faPropTherms[3], faPropTherms[4], faPropTherms[5], faPropTherms[6], faPropTherms[7], faPropTherms[8], faPropTherms[9], 
										faPropOther[0], faPropOther[1], faPropOther[2], faPropOther[3], faPropOther[4], faPropOther[5], faPropOther[6], faPropOther[7], faPropOther[8], faPropOther[9], 
										faPropTDV[0], faPropTDV[1], faPropTDV[2], faPropTDV[3], faPropTDV[4], (lEnergyCodeYear >= 2019 ? faPropTDV[12/*PV*/] : fPropPVCredit[0]),  // SAC 11/15/13 - added fPropPVCredit  // SAC 10/7/16
										faPropTDV[5], faPropTDV[6], faPropTDV[7], faPropTDV[8], faPropTDV[9], faPropTDV[10] );
				else if (iResultsFormatVersion >= 2)
					sPropEnergy.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",	// 42 doubles
										faPropKWH[0], faPropKWH[1], faPropKWH[2], faPropKWH[3], faPropKWH[4], faPropKWH[5], faPropKWH[6], faPropKWH[7], faPropKWH[8], faPropKWH[9], 
										faPropTherms[0], faPropTherms[1], faPropTherms[2], faPropTherms[3], faPropTherms[4], faPropTherms[5], faPropTherms[6], faPropTherms[7], faPropTherms[8], faPropTherms[9], 
										faPropOther[0], faPropOther[1], faPropOther[2], faPropOther[3], faPropOther[4], faPropOther[5], faPropOther[6], faPropOther[7], faPropOther[8], faPropOther[9], 
										faPropTDV[0], faPropTDV[1], faPropTDV[2], faPropTDV[3], faPropTDV[4], fPropPVCredit[0],  // SAC 11/15/13 - added fPropPVCredit
										faPropTDV[5], faPropTDV[6], faPropTDV[7], faPropTDV[8], faPropTDV[9], faPropTDV[10] );
				else
					sPropEnergy.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",		// 41 doubles
										faPropKWH[0], faPropKWH[1], faPropKWH[2], faPropKWH[3], faPropKWH[4], faPropKWH[5], faPropKWH[6], faPropKWH[7], faPropKWH[8], faPropKWH[9], 
										faPropTherms[0], faPropTherms[1], faPropTherms[2], faPropTherms[3], faPropTherms[4], faPropTherms[5], faPropTherms[6], faPropTherms[7], faPropTherms[8], faPropTherms[9], 
										faPropOther[0], faPropOther[1], faPropOther[2], faPropOther[3], faPropOther[4], faPropOther[5], faPropOther[6], faPropOther[7], faPropOther[8], faPropOther[9], 
										faPropTDV[0], faPropTDV[1], faPropTDV[2], faPropTDV[3], faPropTDV[4], 
										faPropTDV[5], faPropTDV[6], faPropTDV[7], faPropTDV[8], faPropTDV[9], faPropTDV[10] );

				if (bExpectStdDesResults)
					sStdEnergy.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",		// 41 doubles
										faStdKWH[   0], faStdKWH[   1], faStdKWH[   2], faStdKWH[   3], faStdKWH[   4], faStdKWH[   5], faStdKWH[   6], faStdKWH[   7], faStdKWH[   8], faStdKWH[   9], 
										faStdTherms[0], faStdTherms[1], faStdTherms[2], faStdTherms[3], faStdTherms[4], faStdTherms[5], faStdTherms[6], faStdTherms[7], faStdTherms[8], faStdTherms[9], 
										faStdOther[ 0], faStdOther[ 1], faStdOther[ 2], faStdOther[ 3], faStdOther[ 4], faStdOther[ 5], faStdOther[ 6], faStdOther[ 7], faStdOther[ 8], faStdOther[ 9], 
										faStdTDV[   0], faStdTDV[   1], faStdTDV[   2], faStdTDV[   3], faStdTDV[   4], faStdTDV[   5], faStdTDV[   6], faStdTDV[   7], faStdTDV[   8], faStdTDV[   9], faStdTDV[  10] );
				else
					sStdEnergy = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

				sVersionFields.sprintf( "\"%s\",\"%s\",\"%s\",\"%s\",", sRuleVer.toLocal8Bit().constData(), sPrimVer.toLocal8Bit().constData(), 
																							sSecVer.toLocal8Bit().constData(), sUIVer.toLocal8Bit().constData() );

				if (iResultsFormatVersion >= 8)	// SAC 10/7/16 - added Proposed PV kW reporting 
				{	if (bExpectStdDesResults)
						sPropStdDemand.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",
													faPropKW[0], faPropKW[1], faPropKW[2], faPropKW[3], faPropKW[4], faPropKW[12/*PV*/], faPropKW[5], faPropKW[6], faPropKW[7], faPropKW[8], faPropKW[9], faPropKW[10], 
													faStdKW[ 0], faStdKW[ 1], faStdKW[ 2], faStdKW[ 3], faStdKW[ 4], faStdKW[ 5], faStdKW[ 6], faStdKW[ 7], faStdKW[ 8], faStdKW[ 9], faStdKW[ 10] );
					else
						sPropStdDemand.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,,,,,,,,,,,,",
													faPropKW[0], faPropKW[1], faPropKW[2], faPropKW[3], faPropKW[4], faPropKW[12/*PV*/], faPropKW[5], faPropKW[6], faPropKW[7], faPropKW[8], faPropKW[9], faPropKW[10] );
				}
				else if (iResultsFormatVersion >= 3)
				{	if (bExpectStdDesResults)
						sPropStdDemand.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",
													faPropKW[0], faPropKW[1], faPropKW[2], faPropKW[3], faPropKW[4], faPropKW[5], faPropKW[6], faPropKW[7], faPropKW[8], faPropKW[9], faPropKW[10], 
													faStdKW[ 0], faStdKW[ 1], faStdKW[ 2], faStdKW[ 3], faStdKW[ 4], faStdKW[ 5], faStdKW[ 6], faStdKW[ 7], faStdKW[ 8], faStdKW[ 9], faStdKW[ 10] );
					else
						sPropStdDemand.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,,,,,,,,,,,,",
													faPropKW[0], faPropKW[1], faPropKW[2], faPropKW[3], faPropKW[4], faPropKW[5], faPropKW[6], faPropKW[7], faPropKW[8], faPropKW[9], faPropKW[10] );
				}

				if (iResultsFormatVersion >= 4 && bExpectStdDesResults)
					sDemSavAndCAHP.sprintf( "%g,%g,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",
													(faStdKW[9] - faPropKW[9]), (faStdKW[10] - faPropKW[10]),  sTDVSavPctTot.toLocal8Bit().constData(), sTDVSavPctComp.toLocal8Bit().constData(), 	// SAC 11/24/14 - added for format ver 4
													sCAHPKickDOE.toLocal8Bit().constData(), sCAHPKickFutCode.toLocal8Bit().constData(), sCAHPKickHELtg.toLocal8Bit().constData(), 
													sCAHPKickTDV100.toLocal8Bit().constData(), sCAHPKickTDV60.toLocal8Bit().constData(), sCAHPScoreInitVal.toLocal8Bit().constData(), 
													sCAHPIncInit.toLocal8Bit().constData(), sCAHPScoreFinal.toLocal8Bit().constData(), sCAHPIncFinal.toLocal8Bit().constData()  );
				else
					sDemSavAndCAHP = ",,,,,,,,,,,,,";

				if (bExpectDesignRatingResults)
				{	if (iResultsFormatVersion == 5)
						sDRtgEnergyDemand.sprintf(	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"  // 51 doubles - Prop energy, TDV & demand (incl. PV credit)
															"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",  // 50 doubles - DRtg energy, TDV & demand
										faDRPropKWH[0], faDRPropKWH[1], faDRPropKWH[2], faDRPropKWH[3], faDRPropKWH[4], faDRPropKWH[5], faDRPropKWH[6], faDRPropKWH[7], faDRPropKWH[8], faDRPropKWH[9], 
										faDRPropTherms[0], faDRPropTherms[1], faDRPropTherms[2], faDRPropTherms[3], faDRPropTherms[4], faDRPropTherms[5], faDRPropTherms[6], faDRPropTherms[7], faDRPropTherms[8], faDRPropTherms[9], 
										faDRPropOther[0], faDRPropOther[1], faDRPropOther[2], faDRPropOther[3], faDRPropOther[4], faDRPropOther[5], faDRPropOther[6], faDRPropOther[7], faDRPropOther[8], faDRPropOther[9], 
										faDRPropTDV[0], faDRPropTDV[1], faDRPropTDV[2], faDRPropTDV[3], faDRPropTDV[4], fPropPVCredit[1], faDRPropTDV[5], faDRPropTDV[6], faDRPropTDV[7], faDRPropTDV[8], faDRPropTDV[9],
										faDRPropKW[0], faDRPropKW[1], faDRPropKW[2], faDRPropKW[3], faDRPropKW[4], faDRPropKW[5], faDRPropKW[6], faDRPropKW[7], faDRPropKW[8], faDRPropKW[9],
										faDRtgKWH[0], faDRtgKWH[1], faDRtgKWH[2], faDRtgKWH[3], faDRtgKWH[4], faDRtgKWH[5], faDRtgKWH[6], faDRtgKWH[7], faDRtgKWH[8], faDRtgKWH[9], 
										faDRtgTherms[0], faDRtgTherms[1], faDRtgTherms[2], faDRtgTherms[3], faDRtgTherms[4], faDRtgTherms[5], faDRtgTherms[6], faDRtgTherms[7], faDRtgTherms[8], faDRtgTherms[9], 
										faDRtgOther[0], faDRtgOther[1], faDRtgOther[2], faDRtgOther[3], faDRtgOther[4], faDRtgOther[5], faDRtgOther[6], faDRtgOther[7], faDRtgOther[8], faDRtgOther[9], 
										faDRtgTDV[0], faDRtgTDV[1], faDRtgTDV[2], faDRtgTDV[3], faDRtgTDV[4], faDRtgTDV[5], faDRtgTDV[6], faDRtgTDV[7], faDRtgTDV[8], faDRtgTDV[9], 
										faDRtgKW[ 0], faDRtgKW[ 1], faDRtgKW[ 2], faDRtgKW[ 3], faDRtgKW[ 4], faDRtgKW[ 5], faDRtgKW[ 6], faDRtgKW[ 7], faDRtgKW[ 8], faDRtgKW[ 9] );
					else if (iResultsFormatVersion == 6)
						sDRtgEnergyDemand.sprintf(	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"  // 51 doubles - Prop energy, TDV & demand (incl. PV credit)
															"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",  // 53 doubles - DRtg energy, TDV & demand
										faDRPropKWH[0], faDRPropKWH[1], faDRPropKWH[2], faDRPropKWH[3], faDRPropKWH[4],  fDRPropKWH_PV,  faDRPropKWH[5], faDRPropKWH[6], faDRPropKWH[7], faDRPropKWH[8], faDRPropKWH[9], 
										faDRPropTherms[0], faDRPropTherms[1], faDRPropTherms[2], faDRPropTherms[3], faDRPropTherms[4], faDRPropTherms[5], faDRPropTherms[6], faDRPropTherms[7], faDRPropTherms[8], faDRPropTherms[9], 
										faDRPropOther[0], faDRPropOther[1], faDRPropOther[2], faDRPropOther[3], faDRPropOther[4], faDRPropOther[5], faDRPropOther[6], faDRPropOther[7], faDRPropOther[8], faDRPropOther[9], 
										faDRPropTDV[0], faDRPropTDV[1], faDRPropTDV[2], faDRPropTDV[3], faDRPropTDV[4], fPropPVCredit[1], faDRPropTDV[5], faDRPropTDV[6], faDRPropTDV[7], faDRPropTDV[8], faDRPropTDV[9],
										faDRPropKW[0], faDRPropKW[1], faDRPropKW[2], faDRPropKW[3], faDRPropKW[4],  fDRPropKW_PV,  faDRPropKW[5], faDRPropKW[6], faDRPropKW[7], faDRPropKW[8], faDRPropKW[9],
										faDRtgKWH[0], faDRtgKWH[1], faDRtgKWH[2], faDRtgKWH[3], faDRtgKWH[4], faDRtgKWH[5], faDRtgKWH[6], faDRtgKWH[7], faDRtgKWH[8], faDRtgKWH[9], 
										faDRtgTherms[0], faDRtgTherms[1], faDRtgTherms[2], faDRtgTherms[3], faDRtgTherms[4], faDRtgTherms[5], faDRtgTherms[6], faDRtgTherms[7], faDRtgTherms[8], faDRtgTherms[9], 
										faDRtgOther[0], faDRtgOther[1], faDRtgOther[2], faDRtgOther[3], faDRtgOther[4], faDRtgOther[5], faDRtgOther[6], faDRtgOther[7], faDRtgOther[8], faDRtgOther[9], 
										faDRtgTDV[0], faDRtgTDV[1], faDRtgTDV[2], faDRtgTDV[3], faDRtgTDV[4], faDRtgTDV[5], faDRtgTDV[6], faDRtgTDV[7], faDRtgTDV[8], faDRtgTDV[9], 
										faDRtgKW[ 0], faDRtgKW[ 1], faDRtgKW[ 2], faDRtgKW[ 3], faDRtgKW[ 4], faDRtgKW[ 5], faDRtgKW[ 6], faDRtgKW[ 7], faDRtgKW[ 8], faDRtgKW[ 9],  fDRtg_NoPV );
					else if (iResultsFormatVersion >= 7)
						sDRtgEnergyDemand.sprintf(	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"  // 51 doubles - Prop energy, TDV & demand (incl. PV credit)
															"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s",  // 52 doubles & 1 string - DRtg energy, TDV & demand
										faDRPropKWH[0], faDRPropKWH[1], faDRPropKWH[2], faDRPropKWH[3], faDRPropKWH[4],  fDRPropKWH_PV,  faDRPropKWH[5], faDRPropKWH[6], faDRPropKWH[7], faDRPropKWH[8], faDRPropKWH[9], 
										faDRPropTherms[0], faDRPropTherms[1], faDRPropTherms[2], faDRPropTherms[3], faDRPropTherms[4], faDRPropTherms[5], faDRPropTherms[6], faDRPropTherms[7], faDRPropTherms[8], faDRPropTherms[9], 
										faDRPropOther[0], faDRPropOther[1], faDRPropOther[2], faDRPropOther[3], faDRPropOther[4], faDRPropOther[5], faDRPropOther[6], faDRPropOther[7], faDRPropOther[8], faDRPropOther[9], 
										faDRPropTDV[0], faDRPropTDV[1], faDRPropTDV[2], faDRPropTDV[3], faDRPropTDV[4], fPropPVCredit[1], faDRPropTDV[5], faDRPropTDV[6], faDRPropTDV[7], faDRPropTDV[8], faDRPropTDV[9],
										faDRPropKW[0], faDRPropKW[1], faDRPropKW[2], faDRPropKW[3], faDRPropKW[4],  fDRPropKW_PV,  faDRPropKW[5], faDRPropKW[6], faDRPropKW[7], faDRPropKW[8], faDRPropKW[9],
										faDRtgKWH[0], faDRtgKWH[1], faDRtgKWH[2], faDRtgKWH[3], faDRtgKWH[4], faDRtgKWH[5], faDRtgKWH[6], faDRtgKWH[7], faDRtgKWH[8], faDRtgKWH[9], 
										faDRtgTherms[0], faDRtgTherms[1], faDRtgTherms[2], faDRtgTherms[3], faDRtgTherms[4], faDRtgTherms[5], faDRtgTherms[6], faDRtgTherms[7], faDRtgTherms[8], faDRtgTherms[9], 
										faDRtgOther[0], faDRtgOther[1], faDRtgOther[2], faDRtgOther[3], faDRtgOther[4], faDRtgOther[5], faDRtgOther[6], faDRtgOther[7], faDRtgOther[8], faDRtgOther[9], 
										faDRtgTDV[0], faDRtgTDV[1], faDRtgTDV[2], faDRtgTDV[3], faDRtgTDV[4], faDRtgTDV[5], faDRtgTDV[6], faDRtgTDV[7], faDRtgTDV[8], faDRtgTDV[9], 
										faDRtgKW[ 0], faDRtgKW[ 1], faDRtgKW[ 2], faDRtgKW[ 3], faDRtgKW[ 4], faDRtgKW[ 5], faDRtgKW[ 6], faDRtgKW[ 7], faDRtgKW[ 8], faDRtgKW[ 9],  fDRtg_NoPV, fDRtg_PVOnly, sDRtg_Std.toLocal8Bit().constData() );
				}

			// concatenate individual strings into complete CSV record
				sprintf_s( pszResultsString, iResultsStringLength, "%s%s%s%s%s%s%s", sBeginFields.toLocal8Bit().constData(), sPropEnergy.toLocal8Bit().constData(), sStdEnergy.toLocal8Bit().constData(), 
										sVersionFields.toLocal8Bit().constData(), sPropStdDemand.toLocal8Bit().constData(), sDemSavAndCAHP.toLocal8Bit().constData(), sDRtgEnergyDemand.toLocal8Bit().constData() );
			}
		}
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

#define  HrlyExport_NumMeters    3
#define  HrlyExport_NumEnduses  11		// SAC 1/29/16 - increased for PV export
#define  HrlyExport_NumEUGroups  5
static const char* pszMeters[HrlyExport_NumMeters+1]			= { "MtrElec",     "MtrNatGas",  "MtrOther",  NULL };
static const char* pszEnduses[HrlyExport_NumEUGroups][HrlyExport_NumEnduses] =
												{	{ "Htg" ,  "Clg" , "FanV",  NULL , "Dhw" , "DHWPmp", "Lit" , "Refr", "Rcp" , "Ext", "PV"  },		// SAC 7/7/15 - SHW -> DHW   	- SAC 1/29/16 - added PV
													{ "HPHtg", "FanC",  NULL ,  NULL , "DhwBU", NULL   ,  NULL , "Dish",  NULL ,  NULL,  NULL },		// SAC 3/23/16 - DHW -> Dhw & added DhwBU
													{ "FanH",   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Dry" ,  NULL ,  NULL,  NULL },
													{ "Aux" ,   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Wash",  NULL ,  NULL,  NULL },
													{ "Fan" ,   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Cook",  NULL ,  NULL,  NULL }  };
// SAC 7/14/16 - replaced following w/ above (moving Other HVAC into Spc Htg) to be consistent w/ reporting of summary results - based on changes to rules back on 10/16/13 by MJB
//												{	{ "Htg" ,  "Clg" , "FanV", "Aux" , "Dhw" , "DHWPmp", "Lit" , "Refr", "Rcp" , "Ext", "PV"  },		// SAC 7/7/15 - SHW -> DHW   	- SAC 1/29/16 - added PV
//													{ "HPHtg", "FanC",  NULL , "Fan" , "DhwBU", NULL   ,  NULL , "Dish",  NULL ,  NULL,  NULL },		// SAC 3/23/16 - DHW -> Dhw & added DhwBU
//													{ "FanH",   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Dry" ,  NULL ,  NULL,  NULL },
//													{  NULL ,   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Wash",  NULL ,  NULL,  NULL },
//													{  NULL ,   NULL ,  NULL ,  NULL ,  NULL ,  NULL   ,  NULL , "Cook",  NULL ,  NULL,  NULL }  };
// CSE enduses not mapped to hourly results export:  'Tot', 'Proc', 'User1', 'User2'

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error retrieving Proj:AnalysisType, AllOrientations, CondFloorArea, ClimateZone and/or NatGasAvailable
//											 2 : Unable to open and/or write hourly CSV results file
//											 3 : Error encountered opening hourly CSV results file
//											 4 : Unknown error writing hourly CSV results file
//											 5 : 
//											 6 : 

int CMX_ExportCSVHourlyResults_CECRes( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName,
													char* pszErrMsgBuffer/*=NULL*/, int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ )
{	int iRetVal = 0;
	QString sErrMsg;
	long lAnalysisType, lAllOrientations, lClimateZone=0, lNatGasAvailable=0;
	double /*fCompMargin=0.0,*/ fCondFloorArea=0.0;
	QString sRunTitle, sFuelTDVLabel;		// , sPassFail;   // , sAnalysisType;  //, sRuleSetID, sRuleSetVer;
	BOOL bExpectStdDesResults = TRUE;
	if (	!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), lAnalysisType    ) ||
		//	!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), sAnalysisType    ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AllOrientations" ), lAllOrientations ) ||
			!BEMPX_GetFloat(	  BEMPX_GetDatabaseID( "Proj:CondFloorArea"   ), fCondFloorArea   ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ClimateZone"     ), lClimateZone     ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NatGasAvailable" ), lNatGasAvailable ) )
	{	iRetVal = 1;
		sErrMsg = "Error retrieving Proj:AnalysisType, AllOrientations, CondFloorArea, ClimateZone and/or NatGasAvailable";
	}
	else
	{	bExpectStdDesResults = (lAnalysisType > 12);  // (sAnalysisType.indexOf( "Standard" ) > 0 || sAnalysisType.indexOf( "Compliance" ) > 0);
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"     ), sRunTitle );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:FuelTDVLabel" ), sFuelTDVLabel );

//		if (iRetVal==0 && lAnalysisType == 13)
//		{	BEMObject* pObjResultSummary = NULL;
//			if (BEMPX_GetObject( BEMPX_GetDatabaseID( "Proj:ResultSummary" ), pObjResultSummary ) && pObjResultSummary && pObjResultSummary->getClass())
//			{	int iObjIdx = BEMPX_GetObjectIndex( pObjResultSummary->getClass(), pObjResultSummary );		assert( iObjIdx >= 0 );
//				if (iObjIdx >= 0)
//				{	sPassFail = "--";  // return PassFail string if full analysis not executed
//					if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:PassFail" ), sPassFail, FALSE, 0, BEMP_Str, iObjIdx ) && bExpectStdDesResults)
//						iRetVal = 4;
//				}
//				else
//					iRetVal = 3;
//			}
//			else
//				iRetVal = 2;
//		}
	}

	if (iRetVal == 0)
	{	QString sOverwriteMsg;
		sOverwriteMsg.sprintf(	"The hourly CSV results file '%s' is opened in another application.  This file must be closed in that "
										"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
										"(once the file is closed), or \n'Cancel' to abort the analysis.", pszHourlyResultsPathFile );
		if (!OKToWriteOrDeleteFile( pszHourlyResultsPathFile, sOverwriteMsg, bSilent ))
		{	iRetVal = 2;
			sErrMsg.sprintf( "Unable to open and/or write hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
	}

	if (iRetVal==0)
	{	long lRunDate = 0;
	   QString timeStamp;
	   //CTime locTime = CTime::GetCurrentTime();
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate ) && lRunDate > 0)
	   {	//CTime locTime = lRunDate;
			//timeStamp = locTime.Format("%Y-%b-%d %H:%M:%S");
			QDateTime locTime = QDateTime::currentDateTime();
			timeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");
		}
		else
			timeStamp = "<unknown analysis day/time>";

		QString sUIVer, sPrimVer, sSecVer, sRuleVer;
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"  ),	sUIVer   );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:PrimSimEngingVer" ),	sPrimVer );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SecSimEngingVer"  ),	sSecVer  );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RulesetVersion"   ),	sRuleVer );
		bool bExportPV = (sRuleVer.indexOf( "2013" ) < 1);	// SAC 1/29/16 - prevent export of PV for 2013 ruleset
		QString sPV = "PV";

		FILE *fp_CSV;
		int iErrorCode;
		try
		{
//			BEMPX_WriteHourlyResultsSummary( pszHourlyResultsPathFile, bSilent, iBEMProcIdx );

			iErrorCode = fopen_s( &fp_CSV, pszHourlyResultsPathFile, "wb" );
			if (iErrorCode != 0 || fp_CSV == NULL)
			{	iRetVal = 3;
				sErrMsg.sprintf( "Error encountered opening hourly CSV results file:  %s", pszHourlyResultsPathFile );
			}
			else
			{	fprintf( fp_CSV, "16,4,\"Row/Col hourly results data begin\"\n"   );
				fprintf( fp_CSV, "\"Hourly Results of CEC Compliance Manager\"\n" );
				fprintf( fp_CSV, ",Ruleset:,,\"%s\"\n", sRuleVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",CSE:,,\"%s\"\n",     sPrimVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",DHW:,,\"%s\"\n",     sSecVer.toLocal8Bit().constData()  );

				fprintf( fp_CSV,     "Run Title:,,,\"%s\"\n", sRunTitle.toLocal8Bit().constData()        );
				fprintf( fp_CSV, "Run Date/Time:,,,\"%s\"\n", timeStamp.toLocal8Bit().constData()        );
				fprintf( fp_CSV,    "Cond. Area:,,,%.0f\n",   fCondFloorArea   );
				fprintf( fp_CSV,         "Model:,,,\"%s\"\n", pszModelName     );
				fprintf( fp_CSV,  "Fuel TDV Set:,,,\"%s\"\n", sFuelTDVLabel.toLocal8Bit().constData()    );
				fprintf( fp_CSV,    "Model File:,,,\"%s\"\n", pszModelPathFile );
				fprintf( fp_CSV, "\n" );

					// SAC 8/23/14 - updated to include electric demand multipliers
				if (bExportPV)		// SAC 1/29/16 - include PV 
            {	fprintf( fp_CSV,  ",,,Site Electric Use,,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,Site Other Fuel Use,,,,,,,,,,,TDV Multipliers,,Elec Demand,\n" );		// INCLUDING PV
	            fprintf( fp_CSV,  ",,,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,PV,TOTAL,"
												"Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,"
												"Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Electric,Fuel,Multipliers\n" );
         	   fprintf( fp_CSV,  "Mo,Da,Hr,(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
														"(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),"
														"(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(TDV/Btu),(TDV/Btu),(frac)\n" );
				}
				else
            {	fprintf( fp_CSV,  ",,,Site Electric Use,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,Site Other Fuel Use,,,,,,,,,,,TDV Multipliers,,Elec Demand,\n" );			// EXCLUDING PV
	            fprintf( fp_CSV,  ",,,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,"
												"Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,"
												"Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,WtrHt Pump,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Electric,Fuel,Multipliers\n" );
         	   fprintf( fp_CSV,  "Mo,Da,Hr,(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
														"(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),"
														"(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(TDV/Btu),(TDV/Btu),(frac)\n" );
				}

			// SETUP hourly results arrays for export...
				int iYrHr=0;
				double daZero[8760];
				double daMtrTotals[HrlyExport_NumMeters][8760];
				for (; iYrHr<8760; iYrHr++)
					daZero[iYrHr] = 0.0;
				double* daMtrEUData[HrlyExport_NumMeters][HrlyExport_NumEnduses][HrlyExport_NumEUGroups];
				int iMtr=0, iEU, iEU2;
				for (; iMtr < HrlyExport_NumMeters; iMtr++)
				{	for (iYrHr=0; iYrHr<8760; iYrHr++)
						daMtrTotals[iMtr][iYrHr] = 0.0;
					for (iEU=0; iEU < HrlyExport_NumEnduses; iEU++)
						for (iEU2=0; iEU2 < HrlyExport_NumEUGroups; iEU2++)
						{	if (pszEnduses[iEU2][iEU] == NULL ||
									(!bExportPV && sPV.compare( pszEnduses[iEU2][iEU] )==0))		// SAC 1/29/16
								daMtrEUData[iMtr][iEU][iEU2] = &daZero[0];   // no enduse to retrieve results for
							else if (BEMPX_GetHourlyResultArrayPtr( &daMtrEUData[iMtr][iEU][iEU2], NULL, 0, pszModelName,
	 																			 pszMeters[iMtr], pszEnduses[iEU2][iEU], iBEMProcIdx ) == 0 && daMtrEUData[iMtr][iEU][iEU2] != NULL)
							{	for (iYrHr=0; iYrHr<8760; iYrHr++)
									daMtrTotals[iMtr][iYrHr] += daMtrEUData[iMtr][iEU][iEU2][iYrHr];
							}
							else
								daMtrEUData[iMtr][iEU][iEU2] = &daZero[0];   // this combination of meter & enduse does not have results
						}
				}

				int iFuelTDVCol = (lNatGasAvailable > 0 ? 2 : 3);
				double daTDVMults[2][8760];
				double* daTDVData[2] = { &daTDVMults[0][0], &daTDVMults[1][0] };
				if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, "TDVTable", ((lClimateZone-1) * 3) + 1, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
				{	assert( FALSE );
					daTDVData[0] = &daZero[0];
				}
				if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, "TDVTable", ((lClimateZone-1) * 3) + iFuelTDVCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
				{	assert( FALSE );
					daTDVData[1] = &daZero[0];
				}
//	"Calculate TDV - Elec   - SpcHt"			if (LocalRef( RunResults[1]:PropElecEnergy		) < 0.0001) then  0
//			 			  								else  int( (100 * ApplyHourlyResultMultipliers( "HtgTDV", "TDVTable", ((Local( ClimateZone )-1) * 3) + 1, Local( RunID ), "MtrElec",   "Htg", "HPHtg", "FanH" ) / Local( CondFloorArea )) + 0.5) / 100  endif  }
//	"Calculate TDV - NatGas - SpcHt"			if (LocalRef( RunResults[1]:PropNatGasEnergy		) < 0.0001) then  0
//			 			  								else  int( (100 * ApplyHourlyResultMultipliers( "HtgTDV", "TDVTable", ((Local( ClimateZone )-1) * 3) + 2, Local( RunID ), "MtrNatGas", "Htg", "HPHtg"         ) / Local( CondFloorArea )) + 0.5) / 100  endif  }
//	"Calculate TDV - Other  - SpcHt"			if (LocalRef( RunResults[1]:PropOtherEnergy		) < 0.0001) then  0
//			 			  								else  int( (100 * ApplyHourlyResultMultipliers( "HtgTDV", "TDVTable", ((Local( ClimateZone )-1) * 3) + 3, Local( RunID ), "MtrOther",  "Htg", "HPHtg"         ) / Local( CondFloorArea )) + 0.5) / 100  endif  }
//
//			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ClimateZone"     ), lClimateZone     ) ||
//			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NatGasAvailable" ), lNatGasAvailable ) )

				double daElecDemand[8760];		// SAC 8/23/14
				double* daElDmndData = &daElecDemand[0];
				if (BEMPX_GetTableColumn( &daElecDemand[0], 8760, "PeakDemandTable", 1, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
				{	assert( FALSE );
					daElDmndData = &daZero[0];
				}

			// EXPORT hourly results records
				iYrHr = -1;
				int iMo, iDa, iHr;
				for (iMo=1; iMo<13; iMo++)
					for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
						for (iHr=1; iHr<25; iHr++)
						{	iYrHr++;
							if (bExportPV)
			    		        fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																		"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																		"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
					(daMtrEUData[0][0][0][iYrHr] + daMtrEUData[0][0][1][iYrHr] + daMtrEUData[0][0][2][iYrHr] + daMtrEUData[0][0][3][iYrHr] + daMtrEUData[0][0][4][iYrHr]) / 3.412,
					(daMtrEUData[0][1][0][iYrHr] + daMtrEUData[0][1][1][iYrHr] + daMtrEUData[0][1][2][iYrHr] + daMtrEUData[0][1][3][iYrHr] + daMtrEUData[0][1][4][iYrHr]) / 3.412,
					(daMtrEUData[0][2][0][iYrHr] + daMtrEUData[0][2][1][iYrHr] + daMtrEUData[0][2][2][iYrHr] + daMtrEUData[0][2][3][iYrHr] + daMtrEUData[0][2][4][iYrHr]) / 3.412,
					(daMtrEUData[0][3][0][iYrHr] + daMtrEUData[0][3][1][iYrHr] + daMtrEUData[0][3][2][iYrHr] + daMtrEUData[0][3][3][iYrHr] + daMtrEUData[0][3][4][iYrHr]) / 3.412,
					(daMtrEUData[0][4][0][iYrHr] + daMtrEUData[0][4][1][iYrHr] + daMtrEUData[0][4][2][iYrHr] + daMtrEUData[0][4][3][iYrHr] + daMtrEUData[0][4][4][iYrHr]) / 3.412,
					(daMtrEUData[0][5][0][iYrHr] + daMtrEUData[0][5][1][iYrHr] + daMtrEUData[0][5][2][iYrHr] + daMtrEUData[0][5][3][iYrHr] + daMtrEUData[0][5][4][iYrHr]) / 3.412,
					(daMtrEUData[0][6][0][iYrHr] + daMtrEUData[0][6][1][iYrHr] + daMtrEUData[0][6][2][iYrHr] + daMtrEUData[0][6][3][iYrHr] + daMtrEUData[0][6][4][iYrHr]) / 3.412,
					(daMtrEUData[0][7][0][iYrHr] + daMtrEUData[0][7][1][iYrHr] + daMtrEUData[0][7][2][iYrHr] + daMtrEUData[0][7][3][iYrHr] + daMtrEUData[0][7][4][iYrHr]) / 3.412,
					(daMtrEUData[0][8][0][iYrHr] + daMtrEUData[0][8][1][iYrHr] + daMtrEUData[0][8][2][iYrHr] + daMtrEUData[0][8][3][iYrHr] + daMtrEUData[0][8][4][iYrHr]) / 3.412,
					(daMtrEUData[0][9][0][iYrHr] + daMtrEUData[0][9][1][iYrHr] + daMtrEUData[0][9][2][iYrHr] + daMtrEUData[0][9][3][iYrHr] + daMtrEUData[0][9][4][iYrHr]) / 3.412,
					(daMtrEUData[0][10][0][iYrHr] + daMtrEUData[0][10][1][iYrHr] + daMtrEUData[0][10][2][iYrHr] + daMtrEUData[0][10][3][iYrHr] + daMtrEUData[0][10][4][iYrHr]) / 3.412, daMtrTotals[0][iYrHr] / 3.412,
					(daMtrEUData[1][0][0][iYrHr] + daMtrEUData[1][0][1][iYrHr] + daMtrEUData[1][0][2][iYrHr] + daMtrEUData[1][0][3][iYrHr] + daMtrEUData[1][0][4][iYrHr]) / 100.0,
					(daMtrEUData[1][1][0][iYrHr] + daMtrEUData[1][1][1][iYrHr] + daMtrEUData[1][1][2][iYrHr] + daMtrEUData[1][1][3][iYrHr] + daMtrEUData[1][1][4][iYrHr]) / 100.0,
					(daMtrEUData[1][2][0][iYrHr] + daMtrEUData[1][2][1][iYrHr] + daMtrEUData[1][2][2][iYrHr] + daMtrEUData[1][2][3][iYrHr] + daMtrEUData[1][2][4][iYrHr]) / 100.0,
					(daMtrEUData[1][3][0][iYrHr] + daMtrEUData[1][3][1][iYrHr] + daMtrEUData[1][3][2][iYrHr] + daMtrEUData[1][3][3][iYrHr] + daMtrEUData[1][3][4][iYrHr]) / 100.0,
					(daMtrEUData[1][4][0][iYrHr] + daMtrEUData[1][4][1][iYrHr] + daMtrEUData[1][4][2][iYrHr] + daMtrEUData[1][4][3][iYrHr] + daMtrEUData[1][4][4][iYrHr]) / 100.0,
					(daMtrEUData[1][5][0][iYrHr] + daMtrEUData[1][5][1][iYrHr] + daMtrEUData[1][5][2][iYrHr] + daMtrEUData[1][5][3][iYrHr] + daMtrEUData[1][5][4][iYrHr]) / 100.0,
					(daMtrEUData[1][6][0][iYrHr] + daMtrEUData[1][6][1][iYrHr] + daMtrEUData[1][6][2][iYrHr] + daMtrEUData[1][6][3][iYrHr] + daMtrEUData[1][6][4][iYrHr]) / 100.0,
					(daMtrEUData[1][7][0][iYrHr] + daMtrEUData[1][7][1][iYrHr] + daMtrEUData[1][7][2][iYrHr] + daMtrEUData[1][7][3][iYrHr] + daMtrEUData[1][7][4][iYrHr]) / 100.0,
					(daMtrEUData[1][8][0][iYrHr] + daMtrEUData[1][8][1][iYrHr] + daMtrEUData[1][8][2][iYrHr] + daMtrEUData[1][8][3][iYrHr] + daMtrEUData[1][8][4][iYrHr]) / 100.0,
					(daMtrEUData[1][9][0][iYrHr] + daMtrEUData[1][9][1][iYrHr] + daMtrEUData[1][9][2][iYrHr] + daMtrEUData[1][9][3][iYrHr] + daMtrEUData[1][9][4][iYrHr]) / 100.0, daMtrTotals[1][iYrHr] / 100.0,
					(daMtrEUData[2][0][0][iYrHr] + daMtrEUData[2][0][1][iYrHr] + daMtrEUData[2][0][2][iYrHr] + daMtrEUData[2][0][3][iYrHr] + daMtrEUData[2][0][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][1][0][iYrHr] + daMtrEUData[2][1][1][iYrHr] + daMtrEUData[2][1][2][iYrHr] + daMtrEUData[2][1][3][iYrHr] + daMtrEUData[2][1][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][2][0][iYrHr] + daMtrEUData[2][2][1][iYrHr] + daMtrEUData[2][2][2][iYrHr] + daMtrEUData[2][2][3][iYrHr] + daMtrEUData[2][2][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][3][0][iYrHr] + daMtrEUData[2][3][1][iYrHr] + daMtrEUData[2][3][2][iYrHr] + daMtrEUData[2][3][3][iYrHr] + daMtrEUData[2][3][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][4][0][iYrHr] + daMtrEUData[2][4][1][iYrHr] + daMtrEUData[2][4][2][iYrHr] + daMtrEUData[2][4][3][iYrHr] + daMtrEUData[2][4][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][5][0][iYrHr] + daMtrEUData[2][5][1][iYrHr] + daMtrEUData[2][5][2][iYrHr] + daMtrEUData[2][5][3][iYrHr] + daMtrEUData[2][5][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][6][0][iYrHr] + daMtrEUData[2][6][1][iYrHr] + daMtrEUData[2][6][2][iYrHr] + daMtrEUData[2][6][3][iYrHr] + daMtrEUData[2][6][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][7][0][iYrHr] + daMtrEUData[2][7][1][iYrHr] + daMtrEUData[2][7][2][iYrHr] + daMtrEUData[2][7][3][iYrHr] + daMtrEUData[2][7][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][8][0][iYrHr] + daMtrEUData[2][8][1][iYrHr] + daMtrEUData[2][8][2][iYrHr] + daMtrEUData[2][8][3][iYrHr] + daMtrEUData[2][8][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][9][0][iYrHr] + daMtrEUData[2][9][1][iYrHr] + daMtrEUData[2][9][2][iYrHr] + daMtrEUData[2][9][3][iYrHr] + daMtrEUData[2][9][4][iYrHr]) / 1000.0, daMtrTotals[2][iYrHr] / 1000.0,
					daTDVData[0][iYrHr], daTDVData[1][iYrHr], daElDmndData[iYrHr] );
							else	// NO PV Export
			    		        fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																		"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																		"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
					(daMtrEUData[0][0][0][iYrHr] + daMtrEUData[0][0][1][iYrHr] + daMtrEUData[0][0][2][iYrHr] + daMtrEUData[0][0][3][iYrHr] + daMtrEUData[0][0][4][iYrHr]) / 3.412,
					(daMtrEUData[0][1][0][iYrHr] + daMtrEUData[0][1][1][iYrHr] + daMtrEUData[0][1][2][iYrHr] + daMtrEUData[0][1][3][iYrHr] + daMtrEUData[0][1][4][iYrHr]) / 3.412,
					(daMtrEUData[0][2][0][iYrHr] + daMtrEUData[0][2][1][iYrHr] + daMtrEUData[0][2][2][iYrHr] + daMtrEUData[0][2][3][iYrHr] + daMtrEUData[0][2][4][iYrHr]) / 3.412,
					(daMtrEUData[0][3][0][iYrHr] + daMtrEUData[0][3][1][iYrHr] + daMtrEUData[0][3][2][iYrHr] + daMtrEUData[0][3][3][iYrHr] + daMtrEUData[0][3][4][iYrHr]) / 3.412,
					(daMtrEUData[0][4][0][iYrHr] + daMtrEUData[0][4][1][iYrHr] + daMtrEUData[0][4][2][iYrHr] + daMtrEUData[0][4][3][iYrHr] + daMtrEUData[0][4][4][iYrHr]) / 3.412,
					(daMtrEUData[0][5][0][iYrHr] + daMtrEUData[0][5][1][iYrHr] + daMtrEUData[0][5][2][iYrHr] + daMtrEUData[0][5][3][iYrHr] + daMtrEUData[0][5][4][iYrHr]) / 3.412,
					(daMtrEUData[0][6][0][iYrHr] + daMtrEUData[0][6][1][iYrHr] + daMtrEUData[0][6][2][iYrHr] + daMtrEUData[0][6][3][iYrHr] + daMtrEUData[0][6][4][iYrHr]) / 3.412,
					(daMtrEUData[0][7][0][iYrHr] + daMtrEUData[0][7][1][iYrHr] + daMtrEUData[0][7][2][iYrHr] + daMtrEUData[0][7][3][iYrHr] + daMtrEUData[0][7][4][iYrHr]) / 3.412,
					(daMtrEUData[0][8][0][iYrHr] + daMtrEUData[0][8][1][iYrHr] + daMtrEUData[0][8][2][iYrHr] + daMtrEUData[0][8][3][iYrHr] + daMtrEUData[0][8][4][iYrHr]) / 3.412,
					(daMtrEUData[0][9][0][iYrHr] + daMtrEUData[0][9][1][iYrHr] + daMtrEUData[0][9][2][iYrHr] + daMtrEUData[0][9][3][iYrHr] + daMtrEUData[0][9][4][iYrHr]) / 3.412, daMtrTotals[0][iYrHr] / 3.412,
					(daMtrEUData[1][0][0][iYrHr] + daMtrEUData[1][0][1][iYrHr] + daMtrEUData[1][0][2][iYrHr] + daMtrEUData[1][0][3][iYrHr] + daMtrEUData[1][0][4][iYrHr]) / 100.0,
					(daMtrEUData[1][1][0][iYrHr] + daMtrEUData[1][1][1][iYrHr] + daMtrEUData[1][1][2][iYrHr] + daMtrEUData[1][1][3][iYrHr] + daMtrEUData[1][1][4][iYrHr]) / 100.0,
					(daMtrEUData[1][2][0][iYrHr] + daMtrEUData[1][2][1][iYrHr] + daMtrEUData[1][2][2][iYrHr] + daMtrEUData[1][2][3][iYrHr] + daMtrEUData[1][2][4][iYrHr]) / 100.0,
					(daMtrEUData[1][3][0][iYrHr] + daMtrEUData[1][3][1][iYrHr] + daMtrEUData[1][3][2][iYrHr] + daMtrEUData[1][3][3][iYrHr] + daMtrEUData[1][3][4][iYrHr]) / 100.0,
					(daMtrEUData[1][4][0][iYrHr] + daMtrEUData[1][4][1][iYrHr] + daMtrEUData[1][4][2][iYrHr] + daMtrEUData[1][4][3][iYrHr] + daMtrEUData[1][4][4][iYrHr]) / 100.0,
					(daMtrEUData[1][5][0][iYrHr] + daMtrEUData[1][5][1][iYrHr] + daMtrEUData[1][5][2][iYrHr] + daMtrEUData[1][5][3][iYrHr] + daMtrEUData[1][5][4][iYrHr]) / 100.0,
					(daMtrEUData[1][6][0][iYrHr] + daMtrEUData[1][6][1][iYrHr] + daMtrEUData[1][6][2][iYrHr] + daMtrEUData[1][6][3][iYrHr] + daMtrEUData[1][6][4][iYrHr]) / 100.0,
					(daMtrEUData[1][7][0][iYrHr] + daMtrEUData[1][7][1][iYrHr] + daMtrEUData[1][7][2][iYrHr] + daMtrEUData[1][7][3][iYrHr] + daMtrEUData[1][7][4][iYrHr]) / 100.0,
					(daMtrEUData[1][8][0][iYrHr] + daMtrEUData[1][8][1][iYrHr] + daMtrEUData[1][8][2][iYrHr] + daMtrEUData[1][8][3][iYrHr] + daMtrEUData[1][8][4][iYrHr]) / 100.0,
					(daMtrEUData[1][9][0][iYrHr] + daMtrEUData[1][9][1][iYrHr] + daMtrEUData[1][9][2][iYrHr] + daMtrEUData[1][9][3][iYrHr] + daMtrEUData[1][9][4][iYrHr]) / 100.0, daMtrTotals[1][iYrHr] / 100.0,
					(daMtrEUData[2][0][0][iYrHr] + daMtrEUData[2][0][1][iYrHr] + daMtrEUData[2][0][2][iYrHr] + daMtrEUData[2][0][3][iYrHr] + daMtrEUData[2][0][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][1][0][iYrHr] + daMtrEUData[2][1][1][iYrHr] + daMtrEUData[2][1][2][iYrHr] + daMtrEUData[2][1][3][iYrHr] + daMtrEUData[2][1][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][2][0][iYrHr] + daMtrEUData[2][2][1][iYrHr] + daMtrEUData[2][2][2][iYrHr] + daMtrEUData[2][2][3][iYrHr] + daMtrEUData[2][2][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][3][0][iYrHr] + daMtrEUData[2][3][1][iYrHr] + daMtrEUData[2][3][2][iYrHr] + daMtrEUData[2][3][3][iYrHr] + daMtrEUData[2][3][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][4][0][iYrHr] + daMtrEUData[2][4][1][iYrHr] + daMtrEUData[2][4][2][iYrHr] + daMtrEUData[2][4][3][iYrHr] + daMtrEUData[2][4][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][5][0][iYrHr] + daMtrEUData[2][5][1][iYrHr] + daMtrEUData[2][5][2][iYrHr] + daMtrEUData[2][5][3][iYrHr] + daMtrEUData[2][5][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][6][0][iYrHr] + daMtrEUData[2][6][1][iYrHr] + daMtrEUData[2][6][2][iYrHr] + daMtrEUData[2][6][3][iYrHr] + daMtrEUData[2][6][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][7][0][iYrHr] + daMtrEUData[2][7][1][iYrHr] + daMtrEUData[2][7][2][iYrHr] + daMtrEUData[2][7][3][iYrHr] + daMtrEUData[2][7][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][8][0][iYrHr] + daMtrEUData[2][8][1][iYrHr] + daMtrEUData[2][8][2][iYrHr] + daMtrEUData[2][8][3][iYrHr] + daMtrEUData[2][8][4][iYrHr]) / 1000.0,
					(daMtrEUData[2][9][0][iYrHr] + daMtrEUData[2][9][1][iYrHr] + daMtrEUData[2][9][2][iYrHr] + daMtrEUData[2][9][3][iYrHr] + daMtrEUData[2][9][4][iYrHr]) / 1000.0, daMtrTotals[2][iYrHr] / 1000.0,
					daTDVData[0][iYrHr], daTDVData[1][iYrHr], daElDmndData[iYrHr] );
						}

				fflush( fp_CSV );
				fclose( fp_CSV );

//BEMProc:  0   Run: 'Proposed' / 'p'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//        Enduse: 'Tot'   Total: 17085
//        Enduse: 'Clg'   Total: 708
//        Enduse: 'Htg'   Total: 0
//        Enduse: 'HPHtg'   Total: 0
//        Enduse: 'SHW'   Total: 0
//        Enduse: 'FanC'   Total: 589
//        Enduse: 'FanH'   Total: 644
//        Enduse: 'FanV'   Total: 381
//        Enduse: 'Fan'   Total: 0
//        Enduse: 'Aux'   Total: 0
//        Enduse: 'Proc'   Total: 0
//        Enduse: 'Lit'   Total: 3565
//        Enduse: 'Rcp'   Total: 7530
//        Enduse: 'Ext'   Total: 398
//        Enduse: 'Refr'   Total: 2283
//        Enduse: 'Dish'   Total: 430
//        Enduse: 'Dry'   Total: 0
//        Enduse: 'Wash'   Total: 556
//        Enduse: 'Cook'   Total: 0
//        Enduse: 'User1'   Total: 0
//        Enduse: 'User2'   Total: 0
//        Enduse: 'SHWPmp'   Total: 0
//        Enduse: 'HtgTDV'   Total: 3717
//        Enduse: 'ClgTDV'   Total: 25930
//        Enduse: 'IAQVTDV'   Total: 2374
//        Enduse: 'ILtTDV'   Total: 23443
//        Enduse: 'AppTDV'   Total: 20471
//        Enduse: 'RcpTDV'   Total: 47734
//        Enduse: 'ExtTDV'   Total: 2427
//    Meter: 'MtrNatGas'   NumMeters: 24
//        Enduse: 'Tot'   Total: 27208
//        Enduse: 'Clg'   Total: 0
//        Enduse: 'Htg'   Total: 21957
//        Enduse: 'HPHtg'   Total: 0
//        Enduse: 'SHW'   Total: 19150
//        Enduse: 'FanC'   Total: 0
//        Enduse: 'FanH'   Total: 0
//        Enduse: 'FanV'   Total: 0
//        Enduse: 'Fan'   Total: 0
//        Enduse: 'Aux'   Total: 0
//        Enduse: 'Proc'   Total: 0
//        Enduse: 'Lit'   Total: 0
//        Enduse: 'Rcp'   Total: 0
//        Enduse: 'Ext'   Total: 0
//        Enduse: 'Refr'   Total: 0
//        Enduse: 'Dish'   Total: 0
//        Enduse: 'Dry'   Total: 3401
//        Enduse: 'Wash'   Total: 0
//        Enduse: 'Cook'   Total: 1850
//        Enduse: 'User1'   Total: 0
//        Enduse: 'User2'   Total: 0
//        Enduse: 'HtgTDV'   Total: 39855
//        Enduse: 'WHtTDV'   Total: 30731
//        Enduse: 'AppTDV'   Total: 8504
//BEMProc:  0   Run: 'Standard' / 's'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//    Meter: 'MtrNatGas'   NumMeters: 24


//BEMProc:  0   Run: 'Proposed' / 'p-N'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//    Meter: 'MtrNatGas'   NumMeters: 24
//BEMProc:  0   Run: 'Proposed-E' / 'p-E'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//    Meter: 'MtrNatGas'   NumMeters: 24
//BEMProc:  0   Run: 'Proposed-S' / 'p-S'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//    Meter: 'MtrNatGas'   NumMeters: 24
//BEMProc:  0   Run: 'Proposed-W' / 'p-W'   NumMeters:  2
//    Meter: 'MtrElec'   NumMeters: 29
//    Meter: 'MtrNatGas'   NumMeters: 24
//BEMProc:  0   Run: 'Standard' / 's'   NumMeters:  2



//{
//	if (iBEMProcIdx < 0)
//		iBEMProcIdx = eiActiveBEMProcIdx;
//	BEMProcObject* pBEMProc = GetBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
//	if (pBEMProc && pszRunName && pszMeterName && strlen( pszRunName ) > 0 && strlen( pszMeterName ) > 0)
//	{	BEMRun* pRun = pBEMProc->GetRun( pszRunName );
//		if (pRun == NULL)
//		{	assert( FALSE );  // run not found
//		}
//		else
//		{	BEMRunHourlyResultMeter* pMeter = pRun->GetHourlyResultMeter( pszMeterName );
//			if (pMeter == NULL && bAddMeterIfNoExist)
//			{	// SAC 5/14/13 - added logic to add meter if run present but meter isn't
//				if (pRun->m_iNumMeters < BEMRun_NumMeters && pszMeterName && strlen( pszMeterName ) < BEMRun_MeterNameLen)
//				{	
//					strcpy_s( pRun->m_aHourlyResults[ pRun->m_iNumMeters ].m_sMeterName, BEMRun_MeterNameLen, pszMeterName );
//					// assumption is that meters already initialized
//					pRun->m_iNumMeters++;
//					return &pRun->m_aHourlyResults[ pRun->m_iNumMeters-1 ];   // SAC 6/4/13 - added to ensure first call when creating the meter gets a valid return value


//	class BEMProcObject : public CObject
//		BEMRun* GetRun( const char* pszRunName );

//	BEMRunHourlyResultMeter* GetHourlyResultMeter( const char* pszRunName, const char* pszMeterName, int iBEMProcIdx, BOOL bAddMeterIfNoExist )

//	class BEMRunHourlyResultEnduse
//	   char		m_sEnduseName[ BEMRun_EnduseNameLen ];
//		double	m_dTotal;
//		double	m_daHourly[ BEMRun_NumHourlyResults ];
//	
//	class BEMRunHourlyResultMeter
//		BEMRunHourlyResultEnduse* GetHourlyResultEnduse( const char* pszEnduseName );
//	   char		m_sMeterName[ BEMRun_MeterNameLen ];
//		int		m_iNumEnduses;
//		BEMRunHourlyResultEnduse  m_aEnduses[ BEMRun_NumEnduses ];
//	
//	class BEMRun
//		BEMRunHourlyResultMeter* GetHourlyResultMeter( const char* pszMeterName );
//	   char		m_sRunName[   BEMRun_RunNameLen   ];
//	   char		m_sRunAbbrev[ BEMRun_RunAbbrevLen ];
//		int		m_iNumMeters;
//		BEMRunHourlyResultMeter  m_aHourlyResults[ BEMRun_NumMeters ];

			}
		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... ) {
			iRetVal = 4;
			sErrMsg.sprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
			// if (!bSilent)
			// 	BEMMessageBox( "Unknown error writing hourly CSV results file." );
		}
	}

	if (!sErrMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
		sprintf_s( pszErrMsgBuffer, iErrMsgBufferLen, sErrMsg.toLocal8Bit().constData() );

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

int ExportCSVHourlyResultsComparison( const char* pszHourlyResultsPathFile, const char* pszModelName, const char* pszEnduseLabel, const char** apszCompareLabels,
													const char** apszResEnduses1, const char** apszResEnduses2,
													char* pszErrMsgBuffer/*=NULL*/, int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ )
{	int iRetVal = 0;

			iRetVal = 1;
			assert( false ); // not ported to open source

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// SAC 10/7/16 - updated col titles to include new 2019 proposed model PV reporting
static char szCECResCSV1[]	=	",,,,,,,Proposed Model Site Electric Use,,,,,,,,,,,Proposed Model Site Natural Gas Use,,,,,,,,,,Proposed Model Site Other Fuel Use,,,,,,,,,"
										",Proposed Model TDV,,,,,,,,,,,,Standard Model Site Electric Use,,,,,,,,,,Standard Model Site Natural Gas Use,,,,,,,,,,Standard Model Site"
										" Other Fuel Use,,,,,,,,,,Standard Model TDV,,,,,,,,,,,Software Versions,,,,Proposed Model Electric Demand,,,,,,,,,,,,Standard Model Electr"
										"ic Demand,,,,,,,,,,,Savings Results,,,,CAHP-SF / CAHP-MF / CMFNH Results,,,,,,,,,Proposed Design Rating Model Site Electric Use,,,,,,,,,,"
										",Proposed  Design Rating Model Site Natural Gas Use,,,,,,,,,,Proposed  Design Rating Model Site Other Fuel Use,,,,,,,,,,Proposed  Design "
										"Rating Model TDV,,,,,,,,,,,Proposed Design Rating Model Electric Demand,,,,,,,,,,,Reference Design Rating Model Site Electric Use,,,,,,,,"
										",,Reference Design Rating Model Site Natural Gas Use,,,,,,,,,,Reference Design Rating Model Site Other Fuel Use,,,,,,,,,,Reference Design"
										" Rating Model TDV,,,,,,,,,,Reference Design Rating Model Electric Demand,,,,,,,,,,Energy Design Ratings\n";
static char szCECResCSV2[]  =  ",Project,,,Pass /,Compliance,Design,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat"
										",Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins L"
										"ight,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV,Ins Light,Appl & Cook,Plug Lds,Exterior"
										",TOTAL,Comp Total,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent"
										",Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,P"
										"lug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Comp Total,Compliance"
										",,,End User,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Comp Total,Spc Heat,Spc Cool,IAQ"
										" Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Comp Total,Total Demand,Compliance Demand,Total TDV,Compliance TD"
										"V,Zero Energy Ready Kicker,Future Code Kicker,High Efficacy Licker,Low Use Kicker,Ultra Low Use Kicker,Initial Score,Initial Incentive,Fi"
										"nal Score,Final Incentive,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Co"
										"ol,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Ap"
										"pl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV Credit,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,"
										"Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,PV,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr"
										" Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterio"
										"r,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVA"
										"C,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Spc Heat,Spc Cool,IAQ Vent,Other HVAC,Wtr Heat,Ins Light,Appl & Cook,Plug Lds,Exterior,TOTAL,Excluding,Only,Standard\n";
static char szCECResCSV3[]  =  "Run Date/Time,Path/File,Run Title,Analysis Type,Fail,Margin,Rating,(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(Therms),("
										"Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),("
										"MMBtu),(MMBtu),(MMBtu),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(k"
										"TDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(Therms),(Therms),(Ther"
										"ms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu"
										"),(MMBtu),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),("
										"kTDV/ft2-yr),(kTDV/ft2-yr),Ruleset,CSE,CEC DHW,Application,(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW"
										"),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(%),(%),(0 or 5),(0 or 3),(0 or 5),(0 or 5),(0 or 5),(int),($),(int),($),(kWh),(kWh),(kWh),(kWh"
										"),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(MM"
										"Btu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTD"
										"V/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW"
										"),(kW),(kW),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(T"
										"herms),(Therms),(Therms),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(MMBtu),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTD"
										"V/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kTDV/ft2-yr),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),(kW),PV,PV,Design\n";

int CMX_PopulateResultsHeader_Res(	char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len )
{	int iRetVal = 0;
#pragma warning(disable:4996)
	if (pszHdr1 && iHdr1Len > 0)
	{	strncpy( pszHdr1, szCECResCSV1, iHdr1Len-1 );
		if (strlen( pszHdr1 ) < strlen( szCECResCSV1 ))
			iRetVal = 1;
	}
	if (pszHdr2 && iHdr2Len > 0)
	{	strncpy( pszHdr2, szCECResCSV2, iHdr2Len-1 );
		if (iRetVal == 0 && strlen( pszHdr2 ) < strlen( szCECResCSV2 ))
			iRetVal = 2;
	}
	if (pszHdr3 && iHdr3Len > 0)
	{	strncpy( pszHdr3, szCECResCSV3, iHdr3Len-1 );
		if (iRetVal == 0 && strlen( pszHdr3 ) < strlen( szCECResCSV3 ))
			iRetVal = 3;
	}
#pragma warning(default:4996)
	return iRetVal;
}

const char* GetResultsCSVHeader_Res( int i1HdrIdx )
{	const char* pszRetVal = NULL;
	switch (i1HdrIdx)
	{	case  2 :	pszRetVal = szCECResCSV2;			break;
		case  3 :	pszRetVal = szCECResCSV3;			break;
		default :	pszRetVal = szCECResCSV1;			break;
	}
	return pszRetVal;
}


/////////////////////////////////////////////////////////////////////////////

#define  CM_MAX_RESBATCH_VER  1

int CMX_PerformBatchAnalysis_CECRes(	const char* pszBatchPathFile, const char* pszProjectPath, const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
													const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
													const char* pszLogPathFile, const char* pszUIVersionString, const char* pszOptionsCSV /*=NULL*/,
													char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bDisplayProgress /*=false*/, HWND hWnd /*=NULL*/ )
{
	int iRetVal = 0;
	si1ProgressRunNum = 1;
	siNumProgressRuns = 1;
	std::ifstream in( pszBatchPathFile );
	if (!in.is_open())
	{	if (pszErrorMsg && iErrorMsgLen > 0)
			sprintf_s( pszErrorMsg, iErrorMsgLen, "Error opening batch definitions file:  %s", pszBatchPathFile );
									return -10;
	}

	std::string sBatchPathFile = pszBatchPathFile;
	std::string sBatchPath, sBatchFileOnly;
	if (sBatchPathFile.rfind('\\') != std::string::npos)
	{	sBatchPath = sBatchPathFile.substr( 0, sBatchPathFile.rfind('\\')+1 );
		sBatchFileOnly = sBatchPathFile.substr( sBatchPathFile.rfind('\\')+1 );
	}
	std::string sProjPath = pszProjectPath;
	int iLenOptionsCSVArg = (pszOptionsCSV ? strlen( pszOptionsCSV ) : 0);

	std::string sRulesetPathFile = pszRulesetPathFile;
	std::string sRulesetPath;
	if (sRulesetPathFile.rfind('\\') != std::string::npos)
		sRulesetPath = sRulesetPathFile.substr( 0, sRulesetPathFile.rfind('\\')+1 );

	std::string sBatchLogPathFile;
	if (pszLogPathFile && strlen( pszLogPathFile ) > 0)
		sBatchLogPathFile = pszLogPathFile;
	else
	{	sBatchLogPathFile = (sBatchPathFile.rfind('.') != std::string::npos ? sBatchPathFile.substr( 0, sBatchPathFile.rfind('.') ) : sBatchPathFile);
		sBatchLogPathFile += ".log";
	}
	std::string sOverwriteProjFileMsg = boost::str( boost::format( "The batch processing log file '%s' is opened in another application.  This file must be closed in that "
												"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
												"(once the file is closed), or \n'Cancel' to abort the batch processing." ) % sBatchLogPathFile.c_str() );
	if (!OKToWriteOrDeleteFile( sBatchLogPathFile.c_str(), sOverwriteProjFileMsg.c_str() ))
	{	if (pszErrorMsg && iErrorMsgLen > 0)
			sprintf_s( pszErrorMsg, iErrorMsgLen, "Unable to write to batch processing log file:  %s", sBatchLogPathFile );
									return -11;
	}
	else
	{	if (FileExists( sBatchLogPathFile.c_str() ))  // add some separation between previous and new batch runs
		{	BEMPX_WriteLogFile( " ", sBatchLogPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			BEMPX_WriteLogFile( " ", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			BEMPX_WriteLogFile( "------------------------------", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}
		BEMPX_WriteLogFile( "Initiating batch processing...", sBatchLogPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	int iaBatchFieldsPerRecordByVer[] = {	12,	// ver 1
														-1  };
	std::string line;
	int iMode = 0;		// <0-Error Code / 0-Reading Header / 1-Reading Run Records
	int iBatchVer = 1, iRunRecord = 0, iBatchRecNum = 0, iRunsToPerform = 0;
	std::string sBatchResultsFN, sBatchLogFN, sOverwriteResultsFileMsg, sLogMsg, sErrMsg;
	std::string sRecProjInFN, sRecProjOutFN, sRecRunTitle, sRecOutput, sRecOptionCSV;
	std::string sRecClimateZone, sRecAnalysisType, sRecStdsVersion, sRecSimReportFile;
	long iRecMultipleOrientation, iRecFrontOrientation;
	std::vector<std::string> saProjInFN, saProjOutFN, saRunTitle, saOutput, saOptionCSV, saBEMBaseFN, saRulesetFN;
	std::vector<std::string> saClimateZone, saAnalysisType, saStdsVersion, saSimReportFile;
	std::vector<long> iaMultipleOrientation, iaFrontOrientation;
	std::vector<int> iaBatchRecNums;
	while (iMode >= 0 && iRunRecord > -1 && getline( in, line ))
	{	iBatchRecNum++;
		std::vector<std::vector<std::string> > lines;
		ParseCSV( line, lines );
		assert( lines.size()==1 );
		if (lines.size() > 0)
		{
			if (lines[0][0].find(';') == 0)
			{	// comment line - do nothing
			}
			else if (iMode == 0)
			{
				if (lines[0].size() < 2)
				{					iMode = -1;
									sErrMsg = boost::str( boost::format( "Error:  First line of data (record %d) contains only %d values (expecting 2):  '%s'" )
																						% iBatchRecNum % lines[0].size() % line.c_str() );
				}
				else
				{	
					iBatchVer = atoi( lines[0][0].c_str() );
					if (iBatchVer < 1 || iBatchVer > CM_MAX_RESBATCH_VER)
					{				iMode = -2;
									sErrMsg = boost::str( boost::format( "Error:  Invalid batch version number (%d) specified in record %d" )
																						% iBatchVer % iBatchRecNum );
					}
					else
					{
						sBatchResultsFN = lines[0][1];
						PrependPathIfNecessary( sBatchResultsFN, sBatchPath );
						sOverwriteResultsFileMsg = boost::str( boost::format( "The CSV file '%s' is opened in another application.  This file must be closed in that "
																	"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																	"(once the file is closed), or \n'Cancel' to abort the batch processing." ) % sBatchResultsFN );
						if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
						{			iMode = -3;
									sErrMsg = boost::str( boost::format( "Error:  Unable to write to batch results file specified in record %d:  '%s'" )
																						% iBatchRecNum % sBatchResultsFN.c_str() );
						}
						else
							iMode = 1;
					}
				}
			}
			else if (iMode == 1 && lines[0].size() > 0)
			{
				iRunRecord = atoi( lines[0][0].c_str() );
				if (iRunRecord > 0)
				{	if ((INT) lines[0].size() < iaBatchFieldsPerRecordByVer[iBatchVer-1])
					{				iMode = -4;
									sErrMsg = boost::str( boost::format( "Error:  Too few values (%d) found in record %d - expecting %d" )
																						% (int) lines[0].size() % iBatchRecNum % iaBatchFieldsPerRecordByVer[iBatchVer-1] );
					}
					else
					{	// PARSE BATCH RUN RECORD
						int iFld = 1;
						std::string sThisBEMBaseFN, sThisProjRulesetFN;
						sRecProjInFN = lines[0][iFld++];
						PrependPathIfNecessary( sRecProjInFN, sProjPath );
						if (!FileExists( sRecProjInFN.c_str() ))
						{			iMode = -5;
									sErrMsg = boost::str( boost::format( "Error:  Input project file specified in record %d not found:  '%s'" )
																						% iBatchRecNum % sRecProjInFN.c_str() );
						}
			// SAC 11/30/14 - code to use ruleset filename from project input (and if none specified, then 
						else
						{	sThisProjRulesetFN = BEMPX_GetRulesetFilenameFromProjectFile( sRecProjInFN.c_str() );
							if (sThisProjRulesetFN.length() < 1 || boost::iequals( sThisProjRulesetFN, "unknown" ))
								sThisProjRulesetFN = "";
							else
							{	if (sThisProjRulesetFN.rfind(':') != std::string::npos || sThisProjRulesetFN[0] == '\\' || sThisProjRulesetFN[0] == '/')
								{	// ruleset already setup w/ full path
								}
								else if (sRulesetPath.length() > 0)
									sThisProjRulesetFN = sRulesetPath + sThisProjRulesetFN;
								if (!FileExists( sThisProjRulesetFN.c_str() ))
									sThisProjRulesetFN = "";
						}	}
						if (sThisProjRulesetFN.length() < 1)
							sThisProjRulesetFN = pszRulesetPathFile;

			// SAC 12/3/14 - code to get ruleset-specific BEMBase file
						if (boost::iequals( sThisProjRulesetFN, pszRulesetPathFile ) || !FileExists( sThisProjRulesetFN.c_str() ))
							sThisBEMBaseFN = pszBEMBasePathFile;
						else
						{	QString sRulesetBEMBaseFile;
							if (BEMPX_ReadBEMBaseFile( sThisProjRulesetFN.c_str(), sRulesetBEMBaseFile ))
							{	sThisBEMBaseFN = sRulesetPath;
								sThisBEMBaseFN += sRulesetBEMBaseFile.toLocal8Bit().constData();
							}
							else
								sThisBEMBaseFN = pszBEMBasePathFile;	// error
						}

						if (iMode > 0)
						{	sRecProjOutFN = lines[0][iFld++];
							PrependPathIfNecessary( sRecProjOutFN, sProjPath );
							sOverwriteProjFileMsg = "The project file '";
							sOverwriteProjFileMsg.append( sRecProjOutFN );
							sOverwriteProjFileMsg.append( "' is opened in another application.  This file must be closed in that "
																		"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																		"(once the file is closed), or \n'Cancel' to abort the batch processing." );
							if (!OKToWriteOrDeleteFile( sRecProjOutFN.c_str(), sOverwriteProjFileMsg.c_str() ))
							{		iMode = -6;
									sErrMsg = boost::str( boost::format( "Error:  Unable to write to project output/save file specified in record %d:  '%s'" )
																						% iBatchRecNum % sRecProjOutFN.c_str() );
							}
						}

						if (iMode > 0)
						{	sRecRunTitle      = lines[0][iFld++];
							sRecClimateZone   = lines[0][iFld++];
							sRecAnalysisType  = lines[0][iFld++];
							sRecStdsVersion   = lines[0][iFld++];
							sRecSimReportFile = lines[0][iFld++];

							if (lines[0][iFld++].size() < 1)
								iRecMultipleOrientation = -1;
							else
							{	iRecMultipleOrientation = atoi( lines[0][iFld-1].c_str() );
								if (iRecMultipleOrientation < 0 || iRecMultipleOrientation > 1)
								{	iMode = -7;
									sErrMsg = boost::str( boost::format( "Error:  Invalid Multiple Orientation option (%d) specified in record %d" )
																						% iRecMultipleOrientation % iBatchRecNum );
								}
							}
						}
						if (iMode > 0)
						{	if (lines[0][iFld++].size() < 1)
								iRecFrontOrientation = -1;
							else
							{	iRecFrontOrientation = atoi( lines[0][iFld-1].c_str() );
								if (iRecFrontOrientation < 0 || iRecFrontOrientation >= 360)
								{	iMode = -8;
									sErrMsg = boost::str( boost::format( "Error:  Invalid Front Orientation option (%d, should be >=0 and <360) specified in record %d" )
																						% iRecFrontOrientation % iBatchRecNum );
								}
							}
						}

						if (iMode > 0)
						{	sRecOutput     = lines[0][iFld++];
				// SAC 9/15/15 - added storage of batch path & file to beginning of OptionCSV string
							sRecOptionCSV  = boost::str( boost::format( "BatchPath,\"%s\",BatchFile,\"%s\"," ) % sBatchPath % sBatchFileOnly );
							sRecOptionCSV += lines[0][iFld++];
							if (iLenOptionsCSVArg > 0)
								sRecOptionCSV += pszOptionsCSV;
						}

					// store info about this run to be performed
						if (iMode > 0)
						{	assert( iFld == iaBatchFieldsPerRecordByVer[iBatchVer-1] );


//	QStringList files = QFileDialog::getOpenFileNames(this, tr(""),  
//	    QDesktopServices::storageLocation(QDesktopServices::MusicLocation));  
//	  
//	if (files.isEmpty())  
//	    return;  
//	  
//	int index = sources.size();  
//	foreach (QString string, files) {  
//	        Phonon::MediaSource source(string);  
//	  
//	    sources.append(source);  
//	}  


							iRunsToPerform++;
							saProjInFN.push_back(  sRecProjInFN  );
							saProjOutFN.push_back( sRecProjOutFN );
							saRunTitle.push_back(  sRecRunTitle );
							saClimateZone.push_back(         sRecClimateZone   );
							saAnalysisType.push_back(        sRecAnalysisType  );
							saStdsVersion.push_back(         sRecStdsVersion   );
							saSimReportFile.push_back(       sRecSimReportFile );
							iaMultipleOrientation.push_back( iRecMultipleOrientation );
							iaFrontOrientation.push_back(    iRecFrontOrientation );
							saOutput.push_back(              sRecOutput );
							saOptionCSV.push_back(           sRecOptionCSV );
							iaBatchRecNums.push_back(        iBatchRecNum );
							saBEMBaseFN.push_back( sThisBEMBaseFN );
							saRulesetFN.push_back( sThisProjRulesetFN );

							sLogMsg = boost::str( boost::format( "  Run %d / record %d / in:  %s\n                                            / out:  %s\n"
																			"                                            / title: '%s' / CZ: '%s' / anal-type: '%s' / stds-ver: '%s' / rpt-file: '%s'\n"
																			"                                            / mult-orient: '%s' / front: '%s' / results: '%s' / options: '%s'\n"
																			"                                            / bembase file: '%s' / ruleset file: '%s'" )
											% iRunsToPerform % iBatchRecNum % sRecProjInFN % sRecProjOutFN % sRecRunTitle % sRecClimateZone % sRecAnalysisType % sRecStdsVersion % sRecSimReportFile
											% iRecMultipleOrientation % iRecFrontOrientation % sRecOutput % sRecOptionCSV % sThisBEMBaseFN % sThisProjRulesetFN );
							BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
					}
				}
			}
			else
			{	assert( FALSE );
			}
		}
	}

// temporary reference of arguments to avoid compiler wanrings
//	pszProjectPath;		pszBEMBasePathFile;		pszRulesetPathFile;
//	pszCSEEXEPath;			pszCSEWeatherPath;		pszDHWDLLPath;				pszDHWWeatherPath;
//	pszLogPathFile;		pszUIVersionString;		pszOptionsCSV;
//	pszErrorMsg;			iErrorMsgLen;				bDisplayProgress;			hWnd;

	int iRunsGood = 0, iRunsBad = 0, iRunsFailedReports = 0;
	if (iMode > 0 && iRunsToPerform > 0)
	{
		char pszRuleErr[1024];
		bool bAbort = false;
																							//	QString sDbgMsg;
// LOOP OVER EACH BATCH RUN DEFINED
		for (int iRun=0; (!bAbort && iRun < iRunsToPerform); iRun++)
		{
																							//	sDbgMsg.sprintf( "PRIOR to run:  %s", saProjInFN[iRun].c_str() );
																							//	AfxMessageBox( sDbgMsg );

         bool bThisRunGood = false;
			pszRuleErr[0] = '\0';
     	//	CTime timeStartRun = CTime::GetCurrentTime();

			sErrMsg.erase();
			std::string sProjPathFile = saProjOutFN[iRun];
			int iLastDotIdx   = sProjPathFile.rfind('.');			assert( iLastDotIdx   > 0 );
			int iLastSlashIdx = sProjPathFile.rfind('\\');			assert( iLastSlashIdx > 0 );
			std::string sProcessingPath = sProjPathFile.substr( 0, iLastDotIdx );
			sProcessingPath += " - batch\\";
			std::string sProjPath = sProjPathFile.substr( 0, iLastSlashIdx+1 );
			if (!DirectoryExists( sProjPath.c_str() ))
				CreateAndChangeDirectory( sProjPath.c_str(), FALSE );
			if (!boost::iequals( saProjInFN[iRun].c_str(), sProjPathFile.c_str() ) &&   // only copy IN to OUT file if they are different
			    !CopyFile( saProjInFN[iRun].c_str(), sProjPathFile.c_str(), FALSE ))
			{
									sErrMsg = boost::str( boost::format( "Error:  Unable to copy project file (run %d, record %d):  '%s'  to:  '%s'" )
																						% (iRun+1) % iaBatchRecNums[iRun] % saProjInFN[iRun].c_str() % sProjPathFile.c_str() );
			}

			if (sErrMsg.size() < 1)
			{
				// SAC 5/14/16 - added code to enable batch processing options
				std::string sTmp;
				if (saRunTitle[iRun].size() > 0)
				{	sTmp = boost::str( boost::format( "RunTitle,\"%s\"," )         % saRunTitle[iRun]            );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}
				if (saClimateZone[iRun].size() > 0)
				{	sTmp = boost::str( boost::format( "ClimateZone,\"%s\"," )      % saClimateZone[iRun]         );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}
				if (saAnalysisType[iRun].size() > 0)
				{	sTmp = boost::str( boost::format( "AnalysisType,\"%s\"," )     % saAnalysisType[iRun]        );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}
				if (saStdsVersion[iRun].size() > 0)
				{	sTmp = boost::str( boost::format( "StandardsVersion,\"%s\"," ) % saStdsVersion[iRun]         );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}
				if (iaMultipleOrientation[iRun] >= 0)
				{	sTmp = boost::str( boost::format( "AllOrientations,%d," )      % iaMultipleOrientation[iRun] );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}
				if (iaFrontOrientation[iRun] >= 0)
				{	sTmp = boost::str( boost::format( "FrontOrientation,%d," )     % iaFrontOrientation[iRun]    );		saOptionCSV[iRun] = sTmp + saOptionCSV[iRun];	}

				int iAnalRetVal = CMX_PerformAnalysisCB_CECRes(	saBEMBaseFN[iRun].c_str() /*pszBEMBasePathFile*/, saRulesetFN[iRun].c_str() /*pszRulesetPathFile*/, pszCSEEXEPath, pszCSEWeatherPath,
																			pszDHWDLLPath, pszDHWWeatherPath, sProcessingPath.c_str(), sProjPathFile.c_str(),
																			sBatchLogPathFile.c_str() /* ??? use overall batch OR individual Project Log File ??? */,
																			pszUIVersionString, true /*bLoadModelFile*/, saOptionCSV[iRun].c_str(), pszRuleErr, 1024,
																			bDisplayProgress, /*GetSafeHwnd() HWND hWnd,*/ NULL /*callback func ptr*/ );
	// Populate string w/ summary results of analysis

				bool bStoreResults = false;
				if (iAnalRetVal == BEMAnal_CECRes_UserAbortedAnalysis || iAnalRetVal == BEMAnal_CECRes_AbortViaCallback)		// unique return value indicating user aborted analysis -OR- callback return value caused abort
				{	// User aborted individual run, so ask if they want to abort ALL remaining runs
									sErrMsg = boost::str( boost::format( "User aborted batch run %d (record %d)..." ) % (iRun+1) % iaBatchRecNums[iRun] );
					if (iRun < (iRunsToPerform - 1))
					{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
						if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
							bAbort = true;
					}
				}
				else if (iAnalRetVal == BEMAnal_CECRes_CompRptGenError)	// SAC 9/26/16 - revisions to enable results storage even if reports fail to be generated
				{
					sErrMsg = boost::str( boost::format( "Report generation failed processing batch run %d, record %d." ) % (iRun+1) % iaBatchRecNums[iRun] );
					iRunsFailedReports++;
					bStoreResults = true;
				}
				else if (iAnalRetVal > 0)
				{	// some error occurred - should be documented already
					if (strlen( pszRuleErr ) > 0)
									sErrMsg = boost::str( boost::format( "Error:  Processing batch run %d, record %d:  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % pszRuleErr );
					else			sErrMsg = boost::str( boost::format( "Error:  Processing batch run %d, record %d:  (no description returned)" ) % (iRun+1) % iaBatchRecNums[iRun]  );
				}
				else
					bStoreResults = true;

				if (bStoreResults)
				{	// RUN SUCCEEDED
					QVector<QString> saCSVOptions;
					if (saOptionCSV[iRun].size() > 0)
					{	if (ParseCSVRecord( saOptionCSV[iRun].c_str(), &saCSVOptions ) < 2)
						{	assert( false );
					}	}

//	if (iRun < (iRunsToPerform - 1) && ::MessageBox( hWnd, "Confirm Continue", "Run Succeeded ... Continue w/ remaining runs?", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) != IDYES)
//		bAbort = true;

	      	//	CTime locTime = CTime::GetCurrentTime();
					QDateTime locTime = QDateTime::currentDateTime();

					if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
					{	if (iRun < (iRunsToPerform - 1))
						{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
							if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
								bAbort = true;
						}
					}
					else
					{
						bool bWriteHdrs = (!FileExists( sBatchResultsFN.c_str() ));
            //      bool bFileOK = false;
				//      CStdioFile csvFile;
				//		if (bWriteHdrs)
				//         bFileOK = (csvFile.Open( sBatchResultsFN.c_str(), CFile::modeCreate | CFile::modeWrite ) != 0);
				//		else
			   //      	bFileOK = (csvFile.Open( sBatchResultsFN.c_str(), CFile::modeWrite ) != 0);
						QFile csvFile;
						csvFile.setFileName( sBatchResultsFN.c_str() );
						bool bFileOK = csvFile.open( QIODevice::WriteOnly | QIODevice::Text | (bWriteHdrs ? QIODevice::Truncate : QIODevice::Append) );
						if (!bFileOK)
						{	assert( FALSE );
						}
						else
						{	if (bWriteHdrs)
							{	// WRITE HEADER RECORDS
                        csvFile.write( GetResultsCSVHeader_Res( 1 ) );
                        csvFile.write( GetResultsCSVHeader_Res( 2 ) );
                        csvFile.write( GetResultsCSVHeader_Res( 3 ) );
							}
				//			else
			   //      	   csvFile.SeekToEnd();

							char pszCSVResultSummary[ 2560 ];

							int iCSVResVal = CMX_PopulateCSVResultSummary_CECRes(	pszCSVResultSummary, 2560, NULL /*pszRunOrientation*/, -1 /*iResFormatVer*/, sProjPathFile.c_str() );
							if (iCSVResVal == 0)
			   	      {	csvFile.write( pszCSVResultSummary );
			   	      	csvFile.write( "\n" );
			   	      }
							else
								sErrMsg = boost::str( boost::format( "Error:  Processing batch run %d, record %d:  unable to retrieve results summary data.  CMX_PopulateCSVResultSummary_CECRes() returned %d" ) % (iRun+1) % iaBatchRecNums[iRun] % iCSVResVal );

							csvFile.flush();
							csvFile.close();
							bThisRunGood = true;
						}
					}

				// SAC 2/2/14 - mods to store analysis results back to project file
					bool bStoreResultsToModelInput =	(GetCSVOptionValue( "StoreResultsToModelInput", 1, saCSVOptions ) > 0);
					if (!bAbort && bStoreResultsToModelInput)
					{
						QVector<QString> saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles, saNewEUseSumObjs;
						CMX_SaveAnalysisResultsToTempFiles( saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles );  // SAC 2/1/14
						if (saUniqueEUseSumObjs.size() < 1)
						{	assert( FALSE );  // no EUseSum objects found ???
						}
						else if (CMX_LoadModel( saBEMBaseFN[iRun].c_str() /*pszBEMBasePathFile*/, saRulesetFN[iRun].c_str() /*pszRulesetPathFile*/,
														sProjPathFile.c_str(), 0 /*MAX_BEMBASE_DATA_SET_ERRORS*/, NULL /*iaFailedBEMBaseDBIDs*/, true /*bSupressAllMsgBoxes*/,
														NULL /*iaFailedBEMBaseObjIdxs*/, NULL /*&saFailedBEMBaseData*/, false /*bLogDurations*/, sBatchLogPathFile.c_str() ) != 0)
						{	assert( FALSE );  // error reading model file BACK into memory
						}
						else
						{
					// SAC 8/28/16 - fixed bug where lack of defaulting of building model was causing errors in final project file writing due to enum dependencies not being valid
							bool bVerboseInputLogging = (GetCSVOptionValue( "VerboseInputLogging", 0, saCSVOptions ) > 0);
						   CMX_EvaluateRuleset( "ProposedInput", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerboseInputLogging, NULL, NULL, NULL, NULL /*epInpRuleDebugInfo*/ );

							CMX_RestoreAnalysisResultsFromTempFiles( saUniqueEUseSumObjs, saTempPathFiles );

							// ALSO store RunDate to be help verify whether results are "current"
							long lTime = (long) locTime.toTime_t();					assert( lTime > 0);
							if (lTime > 0)
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunDate" ), BEMP_Int, (void*) &lTime );

						// SAVE PROJECT FILE
						// Set SoftwareVersion to BEMBase Project
							if (pszUIVersionString && strlen( pszUIVersionString ) > 0)
							{	long lDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "Proj:SoftwareVersion" );
								QString sProjSoftwareVer;
								if (lDBID_Proj_SoftwareVersion > 0 &&
										(!BEMPX_GetString( lDBID_Proj_SoftwareVersion, sProjSoftwareVer ) || sProjSoftwareVer.isEmpty() || sProjSoftwareVer.compare( pszUIVersionString ) != 0) )
									BEMPX_SetBEMData( lDBID_Proj_SoftwareVersion, BEMP_Str, (void*) pszUIVersionString );
							}

						// Set BEMBase version ID value
							int iBEMCID_BEMVersion = BEMPX_GetDBComponentID( "BEMVersion" );
							long lBEMVerID = (iBEMCID_BEMVersion > 0 ? BEMPX_GetNumPropertyTypes( (int) iBEMCID_BEMVersion ) : 0);
							if (lBEMVerID > 0)
							{	long lCurBEMVer = 0;
								long lDBID_Proj_BEMVersion = BEMPX_GetDatabaseID( "Proj:BEMVersion" );
								if ( lDBID_Proj_BEMVersion > 0 &&
										(!BEMPX_GetInteger( lDBID_Proj_BEMVersion, lCurBEMVer ) || lCurBEMVer != lBEMVerID) )
									BEMPX_SetBEMData( lDBID_Proj_BEMVersion, BEMP_Int, (void*) &lBEMVerID );
							}

							if (GetCSVOptionValue( "ClassifyEditableDefaultsAsUserData", 1 /*default*/, saCSVOptions ) > 0)
								BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ );

							bool bFileSaveAllDefinedProperties = (GetCSVOptionValue( "FileSaveAllDefinedProperties", 0, saCSVOptions ) > 0);
							// SAC 6/14/16 - mod to ensure EITHER .xml OR .ribdx/.ribd16x are interpretted as XML files
							std::string sProjFileLastThreeChars = sProjPathFile.substr( sProjPathFile.size()-3, 3 );
							std::string sProjFileLastChar       = sProjPathFile.substr( sProjPathFile.size()-1, 1 );
							int iFileType = (boost::iequals( sProjFileLastThreeChars.c_str(), "xml" ) || boost::iequals( sProjFileLastChar.c_str(), "x" ) ? BEMFT_XML : BEMFT_Std);
							if (!BEMPX_WriteProjectFile( sProjPathFile.c_str(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/, TRUE /*bSupressAllMsgBoxes*/,
																	iFileType, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lTime-1 /*lModDate*/ ))
				      	{	assert( FALSE );  // failure to save file
				      	}
						}
					}
				}
			}

			if (sErrMsg.size() > 0)
			{	BEMPX_WriteLogFile( sErrMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				if (pszErrorMsg && iErrorMsgLen > 0 && (int) sErrMsg.size() < (iErrorMsgLen - strlen( pszErrorMsg )))
				{	if (strlen( pszErrorMsg ) < 1)
						sprintf_s( pszErrorMsg, iErrorMsgLen, "%s", sErrMsg.c_str() );
					else
					{	strcat_s( pszErrorMsg, iErrorMsgLen, "\n" );
						strcat_s( pszErrorMsg, iErrorMsgLen, sErrMsg.c_str() );
					}
				}
			}

			if (bThisRunGood)
				iRunsGood++;
			else
				iRunsBad++;
		}
	}

	if (iMode < 0)
	{	iRetVal = iMode;
		if (sErrMsg.size() > 0)
		{	BEMPX_WriteLogFile( sErrMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (pszErrorMsg && iErrorMsgLen > 0 && (int) sErrMsg.size() < iErrorMsgLen)
				sprintf_s( pszErrorMsg, iErrorMsgLen, "%s", sErrMsg.c_str() );
		}
	}

	if (iRunsFailedReports > 0)
		sLogMsg = boost::str( boost::format( "Batch processing concluded - %d successful / %d errors/aborts / %d report generation failures / return value: %d" ) %
																iRunsGood % iRunsBad % iRunsFailedReports % iRetVal );
	else
		sLogMsg = boost::str( boost::format( "Batch processing concluded - %d successful / %d errors/aborts / return value: %d" ) % iRunsGood % iRunsBad % iRetVal );
	BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
