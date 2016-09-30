// BEMCmpMgrRes.H - Public API exported from 'BEMCmpMgrRes*.DLL'
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

#ifndef __BEMCMPMGRRES_H__
#define __BEMCMPMGRRES_H__

#include "BEMCmpMgr.h"


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


// SAC 9/18/12 - added to facilitate BEopt interface
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
int BEMCMPMGR_API __cdecl CMX_PerformSimulation_CECRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile, const char* pszCSEEXEPath,
										const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath, const char* pszProcessPath,
		                        const char* pszModelPathFile,	const char* pszLogPathFile, HWND hWnd /*=NULL*/, BOOL bFullComplianceAnalysis=FALSE,
										const char* pszUIVersionString=NULL, BOOL bDisplayProgress=FALSE, BOOL bLoadModelFile=TRUE, BOOL bInitHourlyResults=TRUE,
		                        BOOL bStoreBEMProcDetails=FALSE, BOOL bVerbose=FALSE, BOOL bPerformRangeChecks=TRUE, BOOL bPerformSimulations=TRUE,
										BOOL bDurationStats=FALSE );

int BEMCMPMGR_API __cdecl CMX_PerformBatchAnalysis_CECRes(	const char* pszBatchPathFile, const char* pszProjectPath, const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
														const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
														const char* pszLogPathFile, const char* pszUIVersionString, const char* pszOptionsCSV=NULL,
														char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false, HWND hWnd=NULL );

// -----------------------------------------------------------------------------
int BEMCMPMGR_API __cdecl CMX_PerformAnalysisCB_CECRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
												const char* pszProcessingPath, const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString,
												bool bLoadModelFile=true, const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0,
												bool bDisplayProgress=false, PAnalysisProgressCallbackFunc pAnalProgCallbackFunc=NULL );
int BEMCMPMGR_API __cdecl CMX_PerformAnalysis_CECRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
												const char* pszCSEEXEPath, const char* pszCSEWeatherPath, const char* pszDHWDLLPath, const char* pszDHWWeatherPath,
												const char* pszProcessingPath, const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString,
												bool bLoadModelFile=true, const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0,
												bool bDisplayProgress=false, HWND hWnd=NULL );
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Codes listed below...

int BEMCMPMGR_API __cdecl CMX_PopulateResultsHeader_Res(	char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len );
int BEMCMPMGR_API __cdecl CMX_PopulateCSVResultSummary_CECRes(	char* pszResultsString, int iResultsStringLength, const char* pszRunOrientation=NULL,
														int iResultsFormatVersion=-1, const char* pszProjectPathFileName=NULL );
int BEMCMPMGR_API __cdecl CMX_ExportCSVHourlyResults_CECRes( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName,
													char* pszErrMsgBuffer=NULL, int iErrMsgBufferLen=0, bool bSilent=false, int iBEMProcIdx=-1 );

#ifdef __cplusplus
}
#endif

#endif // __BEMCMPMGRRES_H__
