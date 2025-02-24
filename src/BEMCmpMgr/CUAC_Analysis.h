// CUAC_Analysis.h : Declarations for the CUAC (Calif. Utility Allowance Calculator) analysis routine(s)
//
/**********************************************************************
 *  Copyright (c) 2022, California Energy Commission
 *  Copyright (c) 2022, SAC Software Solutions, LLC
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
 *  SAC SOFTWARE SOLUTIONS LLC, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF
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


#ifndef __CUAC_Analysis_H__
#define __CUAC_Analysis_H__

struct CUACUtilityRate  // SAC 10/19/22
{
   bool    bOK;
   QString sUnits;
   double  dMonthlyCharge;
   double  dMinMonthlyCharge;
   long    lNumSeasons;
   QString saSeasonLabels[12];
   long    laSeasonMonthMap[12];
   double  daSeasonalUsePerDay[12];
   double  daaBinSeasonalCost[5][12];
};

//extern void CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
//                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo,
//                              char* pszErrorMsg, int iErrorMsgLen, bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx );

extern void CUAC_RateDownload( QString sRateType, int iErrorRetVal, const char* pszUtilRateRefPropType, QString sProcessingPath, /*QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,*/
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, long iSecurityKeyIndex, const char* pszPrivateKey,
                              const char* pszProxyAddress, const char* pszProxyCredentials, const char* pszProxyType,      // pass NULLs for no proxy - SAC 08/31/23 
                              /*char* pszErrorMsg, int iErrorMsgLen,*/ bool& bAbort, int& iRetVal, QString& sErrMsg, /*(long iCUACReportID,*/ int iCUAC_BEMProcIdx,     // SAC 08/30/23
                              int iConnectTimeoutSecs=10, int iReadWriteTimeoutSecs=CECRptGenDefaultReadWriteTimeoutSecs, const char* pszHardwiredRatePathFile=NULL,    // SAC 08/31/23  // SAC 03/12/24
                              int iDownloadVerbose=-1 );    // SAC 09/03/24

extern int CUAC_WriteCSVSummary( QFile& csvFile, const char* pszProjectPathFileName, const char* pszSimWeatherPath, int iDataModel=0 );    // SAC 12/11/23  // SAC 01/22/25

#endif // __CUAC_Analysis_H__
