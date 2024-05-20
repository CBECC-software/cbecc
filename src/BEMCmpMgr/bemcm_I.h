// bemcm_I.H - externs used within 'BEMCmpMgr*.DLL'
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


#ifndef __BEMCM_I_H__
#define __BEMCM_I_H__

#include <sys/timeb.h>
#include <sys/stat.h>
#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
#include "boost/filesystem.hpp"

//#include <QtGui>
#ifdef CM_QTGUI		// SAC 2/1/13 - added to enable version of BEMCmpMgr w/out QtGui links
#include <QtWidgets/qprogressdialog.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include "Qt_FileDownloader.h"		// SAC 9/18/14
#endif

#ifdef CM_QTGUI
extern QApplication* sq_app;
extern bool sbQtAppDuringInit;
#endif

extern bool ebLogAnalysisMsgs;     // SAC 10/27/21 (MFam)

extern bool FileExists( QString& sFileName );
extern bool FileExists( const char* pszFileName );
extern BOOL DirectoryExists( QString sDirName );
extern bool GetDLLPath( QString& sDLLPath );
extern void CreateAndChangeDirectory( const char* pszDirName, BOOL bRemoveDir=FALSE );
extern BOOL FileWriteable( const char* pszFileName );
extern BOOL OKToWriteOrDeleteFile( const char* pszFileName, QString sUserMsg, bool bSilent=false );
extern BOOL CopySimFile( const char* sSrc, const char* sTarget, const char* sExt, int iNum );
extern int  StringInArray( QVector<QString>& saStrs, QString& sStr );
extern bool AppendMessage( char* pszMsg, int iMsgLen, const char* pszMsgToAppend );

extern void ParseCSV(const std::string& csvSource, std::vector<std::vector<std::string> >& lines);
extern int  StripOutCSVOptions( QString& sRecOptionCSV, QVector<QString>* psaClrOptions, QString sReplace );

extern int  GetBEMBaseCompID( QString& sErr, const char* szComp );
extern long GetBEMBaseDBID(   QString& sErr, const char* szProp, int iCompID );

extern int LocalEvaluateRuleset( QString& sErrMsg, int iErrRetVal, const char* pszRulelistName,
											BOOL bVerbose, void* pCompRuleDebugInfo,
											QStringList* psaWarningMsgs=NULL );		// SAC 3/2/18 - added to enable Warning message tracking during rulelist evaluation

extern BOOL CM_EvaluateModelRules(	LPCSTR sShortTransformName, BOOL bReportToLog=FALSE,
	  									BOOL bVerboseOutput=FALSE, const char* pszBEMBaseDetailsPathFile=NULL,
										BOOL bLogDurationStats=FALSE, void* pCompRuleDebugInfo=NULL );

extern int Local_GenerateRulesetModelReport( QString sRptPathFile, QString sRptRL,
	 											bool bVerbose /*=false*/, bool bSilent /*=false*/ );

extern void ProcessAnalysisError( QString& sErrMsg, bool& bAbort, int& iRetVal,
							int iErrID, bool bErrCausesAbort, bool bWriteToLog, char* pszErrorMsg,
							int iErrorMsgLen, int iDontAbortOnErrorsThruStep, int iStepCheck );

extern int ParseCSVRecord(     const char* pszParseStr, QVector<QString>* psaCSVFields );
extern int GetCSVOptionValue(  const char* pszOptName, int iDefault, QVector<QString>& saCSVOptions );
extern int GetCSVOptionString( const char* pszOptName, QString& sOptString, QVector<QString>& saCSVOptions );

extern QString ssEXEPath;
extern void StoreEXEPath();
extern bool RelativeToCompletePath_IfNeeded( QString& sPathFile );
extern void PrependPathIfNecessary( std::string& sFileName, std::string& sPath );

extern int     CopyAnalysisResultsObjects(           QString& sErrMsg, const char* pszRunID, int iBEMProcIdxSrc, int iBEMProcIdxDest,
                                                         bool bIncludeEnergyUseObjs, QVector<QString>* psaCopyClassPrefixes=NULL );    // added psaCopyClassPrefixes - SAC 11/24/20
extern int  CM_CopyAnalysisResultsObjects_CECNonRes( QString& sErrMsg, const char* pszRunID, int iBEMProcIdxSrc, int iBEMProcIdxDest,
                                                         QVector<QString>* psaCopyClassPrefixes=NULL );	// SAC 6/19/14 - moved from OpenStudioInterface    // SAC 11/24/20

#define  MAX_BEMBASE_DATA_SET_ERRORS  100
extern double DeltaTime( boost::posix_time::ptime& tmStart );

// reporting and security
extern int GenerateReport_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
										const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, const char* pszPrivateKey, 
										const char* pszProxyAddress, const char* pszProxyCredentials, 		// pass NULLs for no proxy 
										const char* pszPDFOnlyBool, const char* pszDebugBool, bool bVerbose=false, bool bSilent=false, bool bSendSignature=false,
										const char* pszCompRptID=NULL, const char* pszRptGenServer=NULL, const char* pszRptGenApp=NULL,
										const char* pszRptGenService=NULL, const char* pszSecKeyRLName=NULL, const char* pszOutputPathFile=NULL,
										const char* pszProxyType=NULL, const char* pszNetComLibrary=NULL, long iSecurityKeyIndex=0,		// SAC 1/10/17
										bool bFinalPDFGeneration=true, bool bSchemaBasedRptGen=false );		// SAC 7/18/17   // SAC 11/20/18
extern int GenerateReportViaQt(	const char* pszOutPathFile, const char* pszURL, const char* pszCACertPath, const char* pszRptData, int iRptDataLen,
											const char* pszProxyAddress=NULL, const char* pszProxyCredentials=NULL, const char* pszProxyType=NULL,		// pass NULLs for no proxy
											char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false );
extern int GenerateReportViaHttpLib(	const char* pszOutPathFile, const char* pszURL, const char* pszCACertPath, const char* pszRptData, int iRptDataLen,
											const char* pszProxyAddress=NULL, const char* pszProxyCredentials=NULL, const char* pszProxyType=NULL,		// pass NULLs for no proxy
											char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false );      // SAC 06/13/21

extern int CheckSiteAccess(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy
										char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false,
										char* pszFoundProxyAddress=NULL, int iFoundProxyAddressLen=0,
										char* pszFoundProxyCredentials=NULL, int iFoundProxyCredentialsLen=0 );
extern int CheckSiteAccessViaQt(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy
										const char* pszProxyType, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false );
extern int CheckSiteAccessViaHttpLib(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy
										const char* pszProxyType, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false );    // SAC 06/12/21

//extern int ComputeSHA1( const char* pszPathFile );
extern int ComputeSHA256_File( const char* pszPathFile, char* pResultBuffer, int iResultBufferLen );
extern int ComputeSHA256_File_Raw( const char* pszPathFile, unsigned char* hash, int iHashLen );
extern int ComputeSHA256_Compare( const char* pszPathFile, const char* pBufferToCompare );

extern bool ParseTitle24ReportXML( const char* xmlFileName, const char* pdfFileName, const char* rptElemName=NULL, BOOL bSupressAllMessageBoxes=FALSE,
                                   const char** saPayloadAttribs=NULL, QString** qsaPayloadAttribStrings=NULL );    // SAC 12/05/21
extern int  ExtractErrorsFromTitle24ReportXML( const char* xmlFileName, QString& sErrors, BOOL bPostToProjectLog=TRUE, BOOL bPostToBEMProc=TRUE, BOOL bSupressAllMessageBoxes=FALSE );
extern long EncodeBase64FromFile( const char* inFileName, QString& encStr );

extern void CM_CryptDecode( char* lpBuf, int length );
extern void CM_CryptEncode( char* lpBuf, int length );
extern void CM_CharSwap(    char* lpBuf, int length );

extern QString AnalysisAction_PhaseString( long iAnalPhase );
extern QString AnalysisAction_BeforeAfter( long iBeforeAfter );

// moved from BEMCmpMgrCom.h to enable access during Res/MFam analysis - SAC 11/29/21
extern int  BCM_NRP_NumModels( int iModels );
extern int  BCM_NRP_NumProgressModels( long lNRP );
extern void SetCECNResProgressVal_Parallel( bool bAll, bool bZP, bool bAP, bool bEPlusSim, bool bCSESim );  // SAC 11/19/21
extern void SetCECNResProgressVal_Serial( bool bZP, bool bAP, bool bZB, bool bAB );
extern int  GetCECNResProgressIndex( long lStep, long lModel, long lSimProg );
extern void SetCECNResProgressMessage( QString& sMsg, long lNRPStep, long lNRPModels, long lSimProg );
extern float *faCECNResProgressVals, fCECNResProgressValSum;
extern float *faCECNResCumulativeProgressSum;
extern bool ebLogAnalysisProgress;     // SAC 01/14/22


////////////////////////////////////////////////////////////////////////////////
// CSE & Analysis progress tracking callback stuff
class CSERunMgr;
typedef int CSE_MSGCALLBACK( int level, const char* msg);
extern int /*CALLBACK*/ CSE_MsgCallback( int level, const char* msg );
extern void SetCSEMessageProcessingType( int iMPT=0 );   // SAC 11/19/21
extern  int CSE_ProcessMessage( int level, const char* msg, int iRun=-1, const class CSERunMgr* pCSERunMgr=NULL);
extern const char* pszCSEProgressMsgs[];
extern int siNumProgressErrors;
extern int si1ProgressRunNum;
extern int siNumProgressRuns;
#ifdef CM_QTGUI
extern QWidget* sqt_win;
extern QProgressDialog* sqt_progress;
#ifdef OSWRAPPER
extern Qt_URLFile	surlFile;		// SAC 9/18/14
#endif
#endif
extern void SetProgressMessage( QString str, bool bBatchMode );
extern QString sqProgressMsg;
extern QString sqProgressRunName;
extern bool sbFreezeProgress;	// SAC 5/31/16

typedef long (CALLBACK* PAnalysisProgressCallbackFunc)( long lAnalProgType, long lData );

extern PAnalysisProgressCallbackFunc spAnalProgCallbackFunc;
extern long slAnalysisProgressCallbackRetVal;
extern long slCurrentProgress;

extern double sfPctDoneFollowingSimulations;  // SAC 8/19/13 - added to enable slower progress reporting when generating reports
extern bool sbLogCSECallbacks;
extern int  siCallbackCount;
extern bool sbAllowCallbackAbort;	// SAC 4/5/15
extern std::map<std::string, int> mapCSECallback;
extern void ClearCSEProgressMap();	// SAC 1/12/18
// end of - Analysis progress tracking callback 


#endif // __BEMCM_I_H__
