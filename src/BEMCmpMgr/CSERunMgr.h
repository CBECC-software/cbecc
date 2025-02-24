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

#ifndef __CSERUNMGR_H__
#define __CSERUNMGR_H__

// from CSEFace.h --
// callback return values
const int CSE_CONTINUE = 0;		// continue execution
const int CSE_ABORT = -1;		// abort and cleanup

extern const char* pszRunAbbrev_u;
extern const char* pszRunAbbrev_pp;
extern const char* pszRunAbbrev_ppN;
extern const char* pszRunAbbrev_ppE;
extern const char* pszRunAbbrev_ppS;
extern const char* pszRunAbbrev_ppW;
extern const char* pszRunAbbrev_smf;
extern const char* pszRunAbbrev_p;
extern const char* pszRunAbbrev_pN;
extern const char* pszRunAbbrev_pE;
extern const char* pszRunAbbrev_pS;
extern const char* pszRunAbbrev_pW;
extern const char* pszRunAbbrev_s;
extern const char* pszRunAbbrev_s2;
extern const char* pszRunAbbrev_s3;
extern const char* pszRunAbbrev_pfx;
extern const char* pszRunAbbrev_pfxN;
extern const char* pszRunAbbrev_pfxE;
extern const char* pszRunAbbrev_pfxS;
extern const char* pszRunAbbrev_pfxW;
extern const char* pszRunAbbrev_dr;
extern const char* pszRunAbbrev_hrtd;	// HERS Rated	- SAC 11/7/19
extern const char* pszRunAbbrev_href;	// HERS Reference
extern const char* pszRunAbbrev_hirt;	// HERS Idx Adjustment Rated
extern const char* pszRunAbbrev_hirf;	// HERS Idx Adjustment Reference

enum CRM_RunType	// SAC 3/26/15
{
   CRM_User,	// user model w/out full proposed setup when in Research Mode
   CRM_PreProp,
   CRM_NOrientPreProp,
   CRM_EOrientPreProp,
   CRM_SOrientPreProp,
   CRM_WOrientPreProp,
   CRM_StdMixedFuel,
   CRM_Prop,
   CRM_NOrientProp,
   CRM_EOrientProp,
   CRM_SOrientProp,
   CRM_WOrientProp,
   CRM_StdDesign,
   CRM_StdDesign2,   // SAC 07/18/23 (2025)
   CRM_StdDesign3,
   CRM_PropFlex,	// SAC 8/3/17 - added proposed Flexibility (for now just pre-cooling) runs
   CRM_NPropFlex,
   CRM_EPropFlex,
   CRM_SPropFlex,
   CRM_WPropFlex,
   CRM_DesignRating,
   CRM_HERSRtd,		// SAC 11/7/19
   CRM_HERSRef,
   CRM_HERSIdxRtd,
   CRM_HERSIdxRef
};

#define  CRM_IsStdDesign(  iRunType )	(bool) ( iRunType >= CRM_StdDesign && iRunType <= CRM_StdDesign3 )   // SAC 07/18/23 (2025)

extern bool RunIsHERS( int iRunID );

class CSERun
{
public:
	enum OutFile { OutFileCSV, OutFileREP, OutFileERR, OutFileCOUNT};

public:
	CSERun();
	~CSERun();
	void SetArgs(const QString& sArgs) { m_sArgs = sArgs; }
	const QString& GetArgs() const { return m_sArgs; }
	void SetRunID(const QString& sRunID) { m_sRunID = sRunID; }
	const QString& GetRunID() const { return m_sRunID; }
	void SetRunIDProcFile(const QString& sRunIDProcFile) { m_sRunIDProcFile = sRunIDProcFile; }
	const QString& GetRunIDProcFile() const { return m_sRunIDProcFile; }
	void SetRunAbbrev(const QString& sRunAbbrev) { m_sRunAbbrev = sRunAbbrev; }
	const QString& GetRunAbbrev() const { return m_sRunAbbrev; }
	void SetOutFile(const QString& sOutFile, OutFile of) { m_sOutFiles[of] = sOutFile; }
	const QString& GetOutFile(OutFile of) const { return m_sOutFiles[of]; }
	void SetTDVFName(const QString& sTDVFName) { m_sTDVFName = sTDVFName; }
	const QString& GetTDVFName() const { return m_sTDVFName; }
	void SetRunNumber(long lRunNumber) { m_lRunNumber = lRunNumber; }
	long GetRunNumber() const { return m_lRunNumber; }
	void SetRunType(int iRunType) { m_iRunType = iRunType; }
	int  GetRunType() const { return m_iRunType; }
	void SetLastRun(BOOL bLastRun) { m_bLastRun = bLastRun; }
	BOOL GetLastRun() const { return m_bLastRun; }
	void SetIsStdDesign(BOOL bIsStdDesign) { m_bIsStdDesign = bIsStdDesign; }
	BOOL GetIsStdDesign() const { return m_bIsStdDesign; }
	BOOL GetIsDesignRtg() const { return (m_iRunType == CRM_DesignRating); }
	BOOL GetIsProposed() const { return (m_iRunType >= CRM_Prop &&
													 m_iRunType <= CRM_WOrientProp); }
	BOOL GetIsHERS() const { return RunIsHERS(m_iRunType); }
	void SetCSE_DHWonly(BOOL bCSE_DHWonly) { m_bCSE_DHWonly = bCSE_DHWonly; }		// SAC 7/7/20
	BOOL GetCSE_DHWonly() const { return m_bCSE_DHWonly; }
	void SetUsingSubstituteResults(BOOL bUsingSubstResults) { m_bUsingSubstituteResults = bUsingSubstResults; }  // SAC 01/21/25
	BOOL GetUsingSubstituteResults() const { return m_bUsingSubstituteResults; }
	void SetExitCode(int iExitCode) { m_iExitCode = iExitCode; }
	int GetExitCode() const { return m_iExitCode; }
	void SetExecStream(class exec_stream_t* pES) { m_pES = pES; }
	class exec_stream_t* GetExecStream() { return m_pES; }

private:
	QString m_sArgs;
	QString m_sRunID;
	QString m_sRunIDProcFile;
	QString m_sRunAbbrev;
	QString m_sOutFiles[OutFileCOUNT];
	QString m_sTDVFName;		// SAC 4/16/17
	long m_lRunNumber;
	int  m_iRunType;	// SAC 3/26/15
	BOOL m_bLastRun;
	BOOL m_bIsStdDesign;
	BOOL m_bCSE_DHWonly;		// SAC 7/7/20
	BOOL m_bUsingSubstituteResults;  // SAC 01/21/25
	int m_iExitCode;
	class exec_stream_t* m_pES;
};		// class CSERun

class CSERunMgr
{
public:
	CSERunMgr(QString sCSEexe, QString sCSEWthr, QString sModelPathOnly, QString sModelFileOnlyNoExt, QString sProcessPath, bool bFullComplianceAnalysis, bool bInitHourlyResults,
		long lAllOrientations, long lAnalysisType, long lStdDesignBaseID, long lDesignRatingRunID, bool bVerbose, bool bStoreBEMProcDetails, bool bPerformSimulations,
		bool bBypassCSE, bool bSilent, void* pCompRuleDebugInfo, const char* pszUIVersionString, int iSimReportOpt=1, int iSimErrorOpt=1, long lStdMixedFuelRunReqd=0,
		long lPrelimPropRunReqd=0, long lPropFlexRunReqd=0, int iNumRuns=-1, const char* pszCodeYear2Digit=NULL, std::vector<long>* plaRIBDIClsObjIndices=NULL,
		const char* pszAltWthrPathFile=NULL );
	~CSERunMgr();
	void DeleteRuns();
	int SetupRun( int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile=true,
						const char* pszRunAbbrev=NULL, bool bCSE_DHWonly=false );		// SAC 7/7/20
	int SetupRun_Simple( int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile=true,
						const char* pszRunAbbrev=NULL, const char* pszExtraCSECmdLineArgs=NULL,
						const char* pszAppendToCSEFile=NULL, int iModelType=0 );
	int SetupRunFinish(  int iRunIdx, QString& sErrorMsg, const char* sCSEFileCopy=NULL );
	int SetupRun_NonRes( int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile=true,
								const char* pszRunID=NULL, const char* pszRunAbbrev=NULL, QString* psCSEVer=NULL,
								int iBEMProcIdx=-1, bool bRemovePVBatt=false, bool bPerformFullCSESim=false, int iCUACReportID=0,   // iCUACReportID - SAC 12/13/24
                        const char* pszSubstituteOutFile=NULL );     // SAC 01/21/25
	bool T24Res_HPWHSizing( QString sProjFileAlone, QString sRunID,
									QString& sErrorMsg, int iModelType=0 );	// SAC 12/13/18 (HPWHSIZE)
	bool T24Res_DHWSolarSysSizing( QString sProjFileAlone, QString sRunID,
								QString& sErrorMsg, int iModelType=0 );	// SAC 1/27/20 (StdSolarSys)
	bool T24Res_DHWNoSolarSysRun( QString sProjFileAlone, QString sRunID,
								QString& sErrorMsg, int iModelType=0 );		// SAC 5/4/20 (FlexibilityCredit)
	const CSERun& GetRun(int iRun) { return *m_vCSERun[iRun]; }
	void SetNumRuns( int iNumRuns ) { m_iNumRuns = iNumRuns; }
	int GetNumRuns() const { return m_iNumRuns; }
	int GetNumProgressRuns() const { return (m_iNumProgressRuns > 0 ? m_iNumProgressRuns : m_iNumRuns); }
	void DoRuns();
	void DoRunRange( int iFirstRunIdx, int iLastRunIdx );
	void MonitorRuns();
	bool ArchiveSimOutput( int iRunIdx, QString sSimOutputPathFile, int iOutFileType );		// SAC 11/7/16 - process CSE errors and/or reports into file for user review
	void IncNumOpenGLErrors() { m_iNumOpenGLErrors++; }
	int  GetNumOpenGLErrors() const { return m_iNumOpenGLErrors; }
	bool ProcessRunOutput(exec_stream_t* pES, size_t iRun, bool &bFirstException);

private:
	void StartRun(CSERun& cseRun);
	QString GetVersionInfo();

private:
	QString m_sCSEexe;
	QString m_sCSEWthr;
	QString m_sModelPathOnly;
	QString m_sModelFileOnlyNoExt;
	QString m_sProcessPath;
	QString m_sCodeYear2Digit;
	bool m_bFullComplianceAnalysis;
	bool m_bInitHourlyResults;
	long m_lAllOrientations;
	long m_lAnalysisType;
	long m_lStdDesignBaseID;
	long m_lDesignRatingRunID;
	long m_lStdMixedFuelRunReqd;
	long m_lPrelimPropRunReqd;
	long m_lPropFlexRunReqd;
	bool m_bVerbose;
	bool m_bStoreBEMProcDetails;
	bool m_bPerformSimulations;
	bool m_bBypassCSE;
	bool m_bSilent;
	void* m_pCompRuleDebugInfo;
	const char* m_pszUIVersionString;
	int m_iError;
	int m_iNumRuns;
	int m_iSimReportOpt;		// SAC 11/5/16 - 0: no CSE reports / 1: user-specified reports / 2: entire .rpt file
	int m_iSimErrorOpt;		// SAC 11/5/16 - 0: no CSE errors / 1: always list CSE errors
	int m_iNumOpenGLErrors;		// SAC 3/16/17
	int m_iNumProgressRuns;		// SAC 5/5/17 - added to facilitate progress reporting on run subsets
	std::vector<CSERun*> m_vCSERun;
	std::vector<CSERun*> m_vCSEActiveRun;
	std::vector<long>* m_plaRIBDIClsObjIndices;
	QString m_sAltWthrPathFile;		// SAC 6/4/20 (RESNET)
//	QStringList m_sCopiedPathFileSrc;		// SAC 9/13/20
//	QStringList m_sCopiedPathFileDest;		// SAC 9/13/20
};		// class CSERunMgr

#endif // __CSERUNMGR_H__