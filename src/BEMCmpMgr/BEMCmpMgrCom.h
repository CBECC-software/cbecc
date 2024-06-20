// BEMCmpMgrCom.H - Public API exported from 'BEMCmpMgrCom*.DLL'
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

#ifndef __BEMCMPMGRCOM_H__
#define __BEMCMPMGRCOM_H__

#include "BEMCmpMgr.h"


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


int  BEMCMPMGR_API __cdecl CMX_AdjustDataModelForGeometryInpType_CECNonRes();	// SAC 3/23/14 - port from UI

int  BEMCMPMGR_API __cdecl CMX_GenerateWindowShades_CECNonRes( bool bVerbose, bool bStoreBEMDetails, bool bSilent, QString& sErrMsg );

int  BEMCMPMGR_API __cdecl CMX_SetupAnalysisWeatherPaths( const char* pszWthrPath, bool bAnnual, bool bDDY, QString& sErrMsg, bool bAllowWthrDownload=false,
														const char* pszProxyAddress=NULL, const char* pszProxyCredentials=NULL, const char* pszProxyType=NULL );

int  BEMCMPMGR_API __cdecl CMX_PerformBatchAnalysis_CECNonRes(	const char* pszBatchPathFile, const char* pszProjectPath, const char* pszBEMBasePathFile,
														const char* pszRulesetPathFile, const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath,
														const char* pszLogPathFile, const char* pszUIVersionString, const char* pszOptionsCSV=NULL,
														char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false, HWND hWnd=NULL, bool bOLDRules=false,
														int iSecurityKeyIndex=0, const char* pszSecurityKey=NULL, char* pszResultMsg=NULL, int iResultMsgLen=0, 		// SAC 1/10/17   // SAC 12/3/17
                                          const char* pszProxyOptionsCSV=NULL );    // separate out Proxy settings since can't communicate these via CSV file (nested quoted strings) - SAC 10/09/21

//	int  BEMCMPMGR_API __cdecl CMX_PerformAnalysis_CECNonRes_OLD(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
//													const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath,
//													const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile=true,
//													const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false, HWND hWnd=NULL );

int  BEMCMPMGR_API __cdecl CMX_PerformAnalysisCB_NonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath,
												const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile=true,
												const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false,
												char* pszResultsSummary=NULL, int iResultsSummaryLen=0, int iSecurityKeyIndex=0, const char* pszSecurityKey=NULL,		// SAC 5/16/14   // SAC 1/10/17
												PAnalysisProgressCallbackFunc pAnalProgCallbackFunc=NULL );		// SAC 5/28/15

int  BEMCMPMGR_API __cdecl CMX_PerformAnalysis_CECNonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath,
												const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile=true,
												const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false, HWND hWnd=NULL,
												char* pszResultsSummary=NULL, int iResultsSummaryLen=0, int iSecurityKeyIndex=0, const char* pszSecurityKey=NULL );		// SAC 5/16/14   // SAC 1/10/17
											//	int iMaxNumErrsReportedPerType=5, 
		                    			//	bool bStoreBEMDetails=false, bool bVerbose=false, int iAnalysisThruStep=100, bool bBypassInputChecks=false, bool bBypassUMLHChecks=false,
											//	bool* pbBypassOpenStudio=NULL, bool* pbBypassSimulation=NULL, int iNumBypassItems=0, bool bDurationStats=false );

int  BEMCMPMGR_API __cdecl CMX_PopulateResultsHeader_NonRes(		char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len, int iCodeType=0 );	// SAC 12/3/14
int  BEMCMPMGR_API __cdecl CMX_PopulateResultsHeader_CECNonRes(	char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len );	// SAC 5/16/14

int  BEMCMPMGR_API __cdecl CMX_PopulateCSVResultSummary_NonRes(	char* pszResultsString, int iResultsStringLength, const char* pszProjectPathFileName=NULL,
																						const char* pszSimWeatherPath=NULL, int iEUseSummaryIdx=0 );	// SAC 11/04/19

int  BEMCMPMGR_API __cdecl CMX_PopulateCustomMeterCSVResultSummary_NonRes(	       char* pszResultsString, int iResultsStringLength, const char* pszProjectPathFileName,
														                                        int i0EUseSummaryIdx=0 );
int  BEMCMPMGR_API __cdecl CMX_PopulateCustomMeterCSVResultSummaryHeaders_NonRes( char* pszHeader1String, int iHeader1StringLength,
                                                                                  char* pszHeader2String, int iHeader2StringLength, int i0EUseSummaryIdx=0 );
int  BEMCMPMGR_API __cdecl CMX_WriteCustomMeterCSVResultSummary_NonRes(           const char* pszResultsPathFile, const char* pszProjectPathFileName  );

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
int  BEMCMPMGR_API __cdecl CMX_ExportCSVHourlyResults_CECNonRes( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, char* pszErrMsgBuffer=NULL,
																			int iErrMsgBufferLen=0, bool bSilent=false, int iBEMProcIdx=-1, const char* pszEPlusVerStr=NULL, const char* pszOpenStudioVerStr=NULL );

//		iCodeType based on  enum CodeType  in OpenStudioInterface.h
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
int  BEMCMPMGR_API __cdecl CMX_ExportCSVHourlyResults_Com( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, int iCodeType=0, char* pszErrMsgBuffer=NULL,
																			int iErrMsgBufferLen=0, bool bSilent=false, int iBEMProcIdx=-1, const char* pszEPlusVerStr=NULL, const char* pszOpenStudioVerStr=NULL );

#define CMX_OSWFT_OSM	0
#define CMX_OSWFT_EPlus	1
#define CMX_OSWFT_GBXML	2
long BEMCMPMGR_API __cdecl CMX_TranslateToSDD( const char* pszInputPathFile, const char* pszOutputPathFile, int iInputType );  // SAC 1/10/14

int  BEMCMPMGR_API __cdecl CMX_ExecuteModelkitBat(	LPCSTR sModelkitBatPathFile, LPCSTR sModelkitRubyScriptPathFile,     // SAC 06/16/22
                        LPCSTR sIDFPath, LPCSTR sIDFFilenameNoExt, bool bVerboseOutput=false,
                        char* pszReturnStr=NULL, int iReturnStrLength=0 );


void  BEMCMPMGR_API __cdecl CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, char* pszErrorMsg, int iErrorMsgLen,
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iBillCalcDetails=-1,
                              bool bWritePDF=true, bool bWriteCSV=true, int iBatchRunIdx=0 );

void  BEMCMPMGR_API __cdecl CUAC_AnalysisProcessing_BatchRates( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, char* pszErrorMsg, int iErrorMsgLen,
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iBillCalcDetails /*=-1*/,
                              int iSecurityKeyIndex, const char* pszSecurityKey, const char* pszProxyServerAddress, const char* pszProxyServerCredentials,
                              const char* pszProxyServerType, int iRptGenConnectTimeout, int iRptGenReadWriteTimeout );

int  BEMCMPMGR_API __cdecl CMX_RateDownload( const char* pszRateType, int iErrorRetVal, const char* pszUtilRateRefPropType, const char* pszProcessingPath, /*QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,*/
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, long iSecurityKeyIndex, const char* pszPrivateKey,
                              const char* pszProxyAddress, const char* pszProxyCredentials, const char* pszProxyType,      // pass NULLs for no proxy - SAC 08/31/23 
                              char* pszErrorMsg, int iErrorMsgLen, /*(long iCUACReportID,*/ int iCUAC_BEMProcIdx,     // SAC 08/30/23
                              int iConnectTimeoutSecs /*=10*/, int iReadWriteTimeoutSecs /*=CECRptGenDefaultReadWriteTimeoutSecs*/ );      // SAC 08/31/23

int  BEMCMPMGR_API __cdecl CMX_GetCUACDBProjectList(  std::string sCUACPathFilename, std::vector<std::string>& vsProjects, std::vector<int>& viProjectIDs );

int  BEMCMPMGR_API __cdecl CMX_PortOldCUACToCBECC(    std::string sCUACPathFilename, long projectID, std::string sProjectName,      // SAC 09/15/23
                                                      std::string& sErrMsg );
// testing...
int  BEMCMPMGR_API __cdecl CMX_ExportCUACDBProjectTables( std::string sCUACPathFilename, std::string sOutputPath,
                                          const std::string& sProject_name );  //, const std::vector<std::string>& sTable_names)
//int  BEMCMPMGR_API __cdecl CMX_ExportCUACDBSummaryTable( std::string sCUACPathFilename, std::string sOutputPath,
//                                          const std::string& sProject_name, bool bIsElec );

#ifdef __cplusplus
}
#endif

#endif // __BEMCMPMGRCOM_H__
