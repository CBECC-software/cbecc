// BEMCmpMgr.H - Public API exported from 'BEMCmpMgr*.DLL'
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
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#ifndef __BEMCMPMGR_H__
#define __BEMCMPMGR_H__

#include "BEMCmpMgrAPI.h"


enum SimulationType
{      
   ST_ProposedDesign, 
   ST_ProposedFinal, 
   ST_BudgetDesign, 
   ST_BudgetFinal, 
   ST_NumTypes,
};


// Analysis progress tracking callback function
// 	return value of callback function:
//			 0 => Proceed with analysis
//			>0 => Abort analysis - return error code will indicate callback return value as cause (BEMAnal_CECRes_AbortViaCallback, ...)
const long analysisProgressType_Processing        = 0;		// => second argument has no use - typically 0
const long analysisProgressType_PercentProgress   = 1;		// => second argument is percent progress (0-100)
typedef long (CALLBACK* PAnalysisProgressCallbackFunc)( long lAnalProgType, long lData );


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

void BEMCMPMGR_API __cdecl CMX_ExitBEMProcAndCmpMgrDLLs();
void BEMCMPMGR_API __cdecl CMX_ExitBEMCmpMgrDLL();

bool BEMCMPMGR_API __cdecl CMX_GetUIActiveFlag();
void BEMCMPMGR_API __cdecl CMX_SetUIActiveFlag( bool bActiveUI );

BOOL BEMCMPMGR_API __cdecl CMX_LoadRuleset( LPCSTR fileName, BOOL bDeleteAllObjects=TRUE );
BOOL BEMCMPMGR_API __cdecl CMX_GetRulesetID( QString& sRuleSetID, QString& sRuleSetVer );
BOOL BEMCMPMGR_API __cdecl CMX_ReadRulesetID( LPCSTR fileName, QString& sRuleSetID, QString& sRuleSetVer );

BOOL BEMCMPMGR_API __cdecl CMX_GetRulesetBEMBaseFile( LPCSTR fileName, QString& sBEMBaseFN );		// SAC 8/15/14 - added to facilitate dynamic ruleset switching (w/ BEMBase refresh)
BOOL BEMCMPMGR_API __cdecl CMX_GetRulesetScreenFiles( QString& sScreensFN, QString& sToolTipsFN );

/////////////////////////////////////////////////////////////////////////////
// Ruleset Organization exports
BOOL BEMCMPMGR_API __cdecl CMX_RulesetOrganizationIsProcedural();
BOOL BEMCMPMGR_API __cdecl CMX_RulesetOrganizationIsDataModel();
int  BEMCMPMGR_API __cdecl CMX_GetRulesetOrganization();
int  BEMCMPMGR_API __cdecl CMX_GetRulelistNames( QVector<QString>& sRulelistNames );


BOOL BEMCMPMGR_API __cdecl CMX_LoadDataModel(	const char* psBEMProcFileName=NULL, int iBEMType=1 /*BEMT_Other*/,
																const char* psInitLogFileName=NULL );

int  BEMCMPMGR_API __cdecl CMX_LoadModel( const char* pszBEMBinPathFile, const char* pszRulesetPathFile, const char* pszModelPathFile, 
														int iMaxDBIDSetFailures=0, int* piDBIDSetFailures=NULL, bool bSupressAllMsgBoxes=false,
														int* piObjIdxSetFailures=NULL, QStringList* psaDataSetFailures=NULL, bool bLogDurations=false,
														const char* pszLogPathFile=NULL, bool bKeepLogFileOpen=false, QStringList* psaWarningsForUser=NULL,
														bool bCalledFromUI=false );

typedef void (CALLBACK* PLogMsgCallbackFunc) ( int iClassification, const char* pszErrorMsg, const char* pszHelpKey );
BOOL BEMCMPMGR_API __cdecl CMX_EvaluateRuleset( LPCSTR rulelistName, BOOL bReportToLog=FALSE, BOOL bTagDataAsUserDefined=FALSE,
														BOOL bVerboseOutput=FALSE, long* plNumRuleEvals=NULL, double* pdNumSeconds=NULL,
														PLogMsgCallbackFunc pLogMsgCallbackFunc=NULL, void* pCompRuleDebugInfo=NULL ); 

int  BEMCMPMGR_API __cdecl CMX_SaveAnalysisResultsToTempFiles( QVector<QString>& saProjEUseSumObjs, QVector<QString>& saUniqueEUseSumObjs, 
																					QVector<QString>& saTempPathFiles );
int  BEMCMPMGR_API __cdecl CMX_RestoreAnalysisResultsFromTempFiles( QVector<QString>& saUniqueEUseSumObjs, QVector<QString>& saTempPathFiles );


//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Codes listed below...
#define  BEMAnal_CECRes_EXEPathInvalid			 1		//  pszCSEEXEPath doesn't exist
#define  BEMAnal_CECRes_WthrPathInvalid		 2		//  pszCSEWeatherPath doesn't exist
#define  BEMAnal_CECRes_unused					 3		//  
#define  BEMAnal_CECRes_MissingFiles			 4		//  One or more missing files (CSE executable)
#define  BEMAnal_CECRes_BEMBaseNotFound		 5		//  pszBEMBasePathFile doesn't exist
#define  BEMAnal_CECRes_RulesetNotFound		 6		//  pszRulesetPathFile doesn't exist
#define  BEMAnal_CECRes_BEMProcInitError		 7		//  Error initializing BEMProc (database & rules processor module)
#define  BEMAnal_CECRes_RulesetInitError		 8		//  Error initializing compliance ruleset
#define  BEMAnal_CECRes_InvalidLogFile			 9		//  Invalid project log file name (too long)
#define  BEMAnal_CECRes_LogFileWriteError		10		//  Error writing to project log file
#define  BEMAnal_CECRes_ModelFileNotFound		11		//  Building model input/project file not found
#define  BEMAnal_CECRes_ModelInitError			12		//  Error reading/initializing model input/project file
#define  BEMAnal_CECRes_EvalPropInpError		13		//  Error evaluating ProposedInput rules
#define  BEMAnal_CECRes_GetSimWthrError		14		//  Error retrieving CSE weather file name (from Proj:WeatherFileName)
#define  BEMAnal_CECRes_SimWthrNotFound		15		//  Energy (CSE) simulation weather file not found
#define  BEMAnal_CECRes_GetDHWWthrError		16		//  Error retrieving DHW weather file name (from Proj:DHWWthrFileName)
#define  BEMAnal_CECRes_DHWWthrNotFound		17		//  DHW simulation weather file not found
#define  BEMAnal_CECRes_GetReqdDataError		18		//  Error retrieving required data: Proj:RunID and/or Proj:RunAbbrev
#define  BEMAnal_CECRes_ProcPathTooLong		19		//  Analysis processing path too long
#define  BEMAnal_CECRes_EvalPropInp3Error		20		//  Error evaluating ProposedInput rules
#define  BEMAnal_CECRes_EvalPostPropError		21		//  Error evaluating PostProposedInput rules
#define  BEMAnal_CECRes_EvalStdConvError		22		//  Error evaluating BudgetConversion rules
#define  BEMAnal_CECRes_EvalSimPrepError		23		//  Error evaluating CSE_SimulationPrep rules
#define  BEMAnal_CECRes_ProcDirError			24		//  Unable to create or access analysis processing directory
#define  BEMAnal_CECRes_SimOutWriteError		25		//  Unable to open/delete/write simulation output file (.csv or .rep)
#define  BEMAnal_CECRes_SimWthrWriteError		26		//  Unable to open/delete/write simulation weather file
#define  BEMAnal_CECRes_SimWthrCopyError		27		//  Error copying simulation weather file to processing directory
#define  BEMAnal_CECRes_SimInputOpenError		28		//  Unable to open/delete/write simulation input (.cse) file
#define  BEMAnal_CECRes_SimInputWriteError	29		//  Error writing simulation input (.cse) file
#define  BEMAnal_CECRes_CSESimError				30		//  CSE simulation not successful - error code returned
#define  BEMAnal_CECRes_DHWSimError				31		//  DHW simulation not successful
#define  BEMAnal_CECRes_ErrorLoadingCSE		32		//  Error encountered loading CSE DLL(s)
#define  BEMAnal_CECRes_EvalCodeChkError		33		//  Error evaluating ProposedModelCodeCheck rules
#define  BEMAnal_CECRes_EvalSimChkError		34		//  Error evaluating ProposedModelSimulationCheck rules
#define  BEMAnal_CECRes_EvalCodeAddError		35		//  Error evaluating ProposedModelCodeAdditions rules
#define  BEMAnal_CECRes_UserAbortedAnalysis	36		//  User aborted analysis via progress dialog 'Cancel' button
#define  BEMAnal_CECRes_EvalPropInp2Error		37		//  Error evaluating ProposedInput rules
#define  BEMAnal_CECRes_RangeOrOtherError		38		//  Error performing range and/or error checks on building model
#define  BEMAnal_CECRes_EvalSimCleanupError	39		//  Error evaluating CSE_SimulationCleanUp rules
#define  BEMAnal_CECRes_AbortViaCallback		40		//  Analysis aborted based on return from analysis progress callback function
#define  BEMAnal_CECRes_EvalProcResultsError	41		//  Error evaluating ProcessResults rules
#define  BEMAnal_CECRes_EvalPropCompError		42		//  Error evaluating ProposedCompliance rules
#define  BEMAnal_CECRes_ModelReadError			43		//  Error(s) encountered reading building model (project) file
#define  BEMAnal_CECRes_RuleProcAbort			44		//  Error(s) encountered evaluating rules required analysis to abort
#define  BEMAnal_CECRes_BadResultsObjTypes	45		//  Invalid results object types encountered when copying results between models
#define  BEMAnal_CECRes_ResultsCopyError		46		//  Error copying results objects from a previous model
#define  BEMAnal_CECRes_SetupWthrHashError	47		//  Error setting up check of weather file hash
#define  BEMAnal_CECRes_DuplicateObjNames		48		//  Input model contains one or more objects with the same name
#define  BEMAnal_CECRes_MissingZnCSEIncFile	49		//  Missing Zone CSE include file
#define  BEMAnal_CECRes_EvalAnalPrepError		50		//  Error evaluating OneTimeAnalysisPrep rules
#define  BEMAnal_CECRes_BadResultsObjTypesU	51		//  Invalid results object types encountered when copying final results to user model
#define  BEMAnal_CECRes_ResultsCopyErrorU		52		//  Error copying results objects from the final run into the user model
#define  BEMAnal_CECRes_CSEIncFIleWriteError	53		//  Unable to open/delete/write CSE include file
#define  BEMAnal_CECRes_CSEIncFileCopyError	54		//  Error copying CSE include file to processing directory
#define  BEMAnal_CECRes_DHWUseCSEIncMissing	55		//  DHW Use/Load Profile CSE include file missing
#define  BEMAnal_CECRes_DHWUseCSEIncCopyErr	56		//  Error copying DHW Use/Load Profile CSE include file into processing directory
#define  BEMAnal_CECRes_DHWUseHashError		57		//  Error setting up check of DHW use/profile file hash
#define  BEMAnal_CECRes_CSEBattCtrlSetupErr	58		//  Error setting up CSE battery control data
#define  BEMAnal_CECRes_CSEOpenGLError			59		//  Error initializing OpenGL (required for CSE shading simulation)
#define  BEMAnal_CECRes_TDVFileWriteError		60		//  Error writing CSV file w/ TDV data (required for CSE simulation)
#define  BEMAnal_CECRes_EvalSetupPMFError		61		//  Error evaluating SetupRun_ProposedMixedFuel rules
#define  BEMAnal_CECRes_EvalSetupPFlxError	62		//  Error evaluating SetupRun_ProposedFlexibility rules
#define  BEMAnal_CECRes_SimModelInitError		63		//  Error initializing analysis model
#define  BEMAnal_CECRes_AnalResWriteError		64		//  Unable to overwrite analysis results XML file
// ^^^^ Errors listed above result in invalid results ^^^^ || vvvv Errors listed below should still allow users to VIEW analysis results vvvv
#define  BEMAnal_CECRes_MinErrorWithResults	200	// marker for lowest errant retval that includes complete results
#define  BEMAnal_CECRes_ModelRptError			200	// (was 40)  Error generating model report
#define  BEMAnal_CECRes_CompRptWriteError		201	// (was 45)  Unable to write compliance report file (.pdf or .xml)
#define  BEMAnal_CECRes_CompRptGenError		202	// (was 46)  Error(s) encountered generating compliance report file (.pdf or .xml)
#define  BEMAnal_CECRes_EvalChkFileHashError	203	// (was 48)  Error evaluating CheckFileHash rules
#define  BEMAnal_CECRes_WthrHashChkFail		204	// (was 49)  Weather file hash failed consistency check
#define  BEMAnal_CECRes_InputSaveFailed		205	// Attempt to save project inputs (including results) following analysis failed
#define  BEMAnal_CECRes_DHWUseHashChkFail		206	// DHW use/profile file hash failed consistency check
#define  BEMAnal_CECRes_RptGenErrorReturned	207	// Report generator found errors in analysis inputs and/or results
#define  BEMAnal_CECRes_RptGenPDFExtract		208	// Error extracting PDF report from full XML report file
// -----------------------------------------------------------------------------

#ifdef CECRPTGEN
//int DLLAPI __cdecl CMX_GenerateReport_CEC(	int iReportID, const char* pszXMLPath, const char* pszXMLFileNoExt,
//																				const char* pszReportType, const char* pszCACertPath, bool bVerbose=false, bool bSilent=false );
int  BEMCMPMGR_API __cdecl CMX_GenerateReport_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
																				const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, 
																				const char* pszDebugBool, bool bVerbose=false, bool bSilent=false );
int  BEMCMPMGR_API __cdecl CMX_GenerateReport_Proxy_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
																						const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, 
																						const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy 
																						const char* pszDebugBool, bool bVerbose=false, bool bSilent=false,
																						const char* pszCompRptID=NULL, const char* pszRptGenServer=NULL, const char* pszRptGenApp=NULL,		// SAC 8/7/14 - added more args to facilitate URL path specification
																						const char* pszRptGenService=NULL, const char* pszSecKeyRLName=NULL, const char* pszOutputPathFile=NULL,
																						const char* pszProxyType=NULL, const char* pszNetComLibrary=NULL );	// SAC 11/5/15

int  BEMCMPMGR_API __cdecl CMX_CheckSiteAccess(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy  
														char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bVerbose=false, const char* pszProxyType=NULL, const char* pszNetComLibrary=NULL );	// SAC 11/5/15

int  BEMCMPMGR_API __cdecl CMX_GenerateFileHashesFromCSV( const char* pszHashFileListCSVPathFile, const char* pszHashOutputPathFile, const char* pszDefaultPath=NULL );  // SAC 9/2/13

bool BEMCMPMGR_API __cdecl CMX_RetrievePublicKey( QString sSecKeyRulelistName, bool bConvertBinHex, QString& sRptPubKey, QString& sErrMsg );

bool BEMCMPMGR_API __cdecl CMX_ExtractTitle24ReportFromXML( const char* xmlFileName, const char* pdfFileName, const char* rptElemName=NULL, BOOL bSupressAllMessageBoxes=FALSE );

int  BEMCMPMGR_API __cdecl CMX_ExtractErrorsFromReportXML( const char* xmlFileName, QString& sErrors, BOOL bPostToProjectLog=TRUE, BOOL bPostToBEMProc=TRUE, BOOL bSupressAllMessageBoxes=FALSE );
#endif // CECRPTGEN

// SAC 6/10/13 - routine to generate a report summarizing/describing a building model that is heavily ruleset-defined
int  BEMCMPMGR_API __cdecl CMX_GenerateRulesetModelReport(	const char* pszReportSavePathFileNoExt, const char* pszReportSelection,
														char* pszFinalReportPathFile, int iFinalReportPathFileLength,
														bool bVerbose=false, bool bSilent=false );

BOOL BEMCMPMGR_API __cdecl CMX_TransformModel(	LPCSTR sShortTransformName, BOOL bEvalRules, BOOL bReportToLog=FALSE,
														BOOL bVerboseOutput=FALSE, const char* pszBEMBaseDetailsPathFile=NULL,
														BOOL bLogDurationStats=FALSE, void* pCompRuleDebugInfo=NULL );

// routines to access BEMBase data:
int  BEMCMPMGR_API __cdecl CMX_GetDataString(  char* sReturnStr, int iRetStrLen, const char* pszCompParam, const char* pszCompName=NULL, 
								                               BOOL bAddCommas=TRUE, int iPrecision=0, const char* pszDefault=NULL );
int  BEMCMPMGR_API __cdecl CMX_GetDataInteger( long* pReturnInt, const char* pszCompParam,
								                               const char* pszCompName=NULL, long lDefault=0 );
int  BEMCMPMGR_API __cdecl CMX_GetDataFloat(   double* pReturnFlt, const char* pszCompParam,
							 											 const char* pszCompName=NULL, float fDefault=0 );

bool BEMCMPMGR_API __cdecl CMX_SecureExecutable();
long BEMCMPMGR_API __cdecl CMX_EncodeBase64( const unsigned char *input, int length, char* output, int outLength, bool bSecure=false );
int  BEMCMPMGR_API __cdecl CMX_DecodeBase64( char* outData, const char* inData, bool bSecure=false );
int  BEMCMPMGR_API __cdecl CMX_Encrypt( unsigned char * data, int dataLen, unsigned char *encrypted );
int  BEMCMPMGR_API __cdecl CMX_Decrypt( unsigned char * enc_data, int dataLen, unsigned char *decrypted );

#ifdef __cplusplus
}
#endif

#endif // __BEMCMPMGR_H__
