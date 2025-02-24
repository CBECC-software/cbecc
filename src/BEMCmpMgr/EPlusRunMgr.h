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

#ifndef __EPLUSRUNMGR_H__
#define __EPLUSRUNMGR_H__

class EPlusRun
{
public:
	enum OutFile { OutFileCSV, OutFileREP, OutFileERR, OutFileCOUNT};

public:
	EPlusRun();
	~EPlusRun();
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
	void SetProcessPath(const QString& sProcessPath) { m_sProcessPath = sProcessPath; }
	const QString& GetProcessPath() const { return m_sProcessPath; }
//	void SetTDVFName(const QString& sTDVFName) { m_sTDVFName = sTDVFName; }
//	const QString& GetTDVFName() const { return m_sTDVFName; }
	void SetRunNumber(long lRunNumber) { m_lRunNumber = lRunNumber; }
	long GetRunNumber() const { return m_lRunNumber; }
	void SetProgressModel(long lProgressModel) { m_lProgressModel = lProgressModel; }
	long GetProgressModel() const { return m_lProgressModel; }
	void SetSimulationMonth(int iSimMonth) { m_iSimMonth = iSimMonth; }
	int  GetSimulationMonth() const { return m_iSimMonth; }
	void SetHourlySimulation(bool bHourlySim) { m_bHourlySim = bHourlySim; }
	bool GetHourlySimulation() const { return m_bHourlySim; }
//	void SetRunType(int iRunType) { m_iRunType = iRunType; }
//	int  GetRunType() const { return m_iRunType; }
//	void SetLastRun(BOOL bLastRun) { m_bLastRun = bLastRun; }
//	BOOL GetLastRun() const { return m_bLastRun; }
//	void SetIsStdDesign(BOOL bIsStdDesign) { m_bIsStdDesign = bIsStdDesign; }
//	BOOL GetIsStdDesign() const { return m_bIsStdDesign; }
//	BOOL GetIsDesignRtg() const { return (m_iRunType == CRM_DesignRating); }
	void SetExitCode(int iExitCode) { m_iExitCode = iExitCode; }
	int GetExitCode() const { return m_iExitCode; }
	void SetExecStream(class exec_stream_t* pES) { m_pES = pES; }
	class exec_stream_t* GetExecStream() { return m_pES; }
	bool StdoutFileNeedingOpen() { return (fp_stdout == NULL && !m_bStdoutWritten); }
	bool StdoutFileWriteable()   { return (fp_stdout != NULL && !m_bStdoutWritten); }
	void OpenStdoutFile( QString sStdoutFN );
	void WriteStdoutString( std::string str );
	void SetStdoutWritten(bool bStdoutWritten) { m_bStdoutWritten = bStdoutWritten; }
	bool GetStdoutWritten() const { return m_bStdoutWritten; }

private:
	QString m_sArgs;
	QString m_sRunID;
	QString m_sRunIDProcFile;
	QString m_sRunAbbrev;
	QString m_sOutFiles[OutFileCOUNT];
	QString m_sProcessPath;
	long m_lRunNumber;
	long m_lProgressModel;
	int m_iSimMonth;		// SAC 2/17/19 - 0-init, 1-Jan, ... 12-Dec
	bool m_bHourlySim;	// SAC 2/17/19
//	int  m_iRunType;	// SAC 3/26/15
//	BOOL m_bLastRun;
//	BOOL m_bIsStdDesign;
	int m_iExitCode;
	class exec_stream_t* m_pES;
	FILE *fp_stdout;
	bool m_bStdoutWritten;
};		// class EPlusRun

class EPlusRunMgr
{
public:
	EPlusRunMgr(QString sEPlusPath, QString sModelPathOnly, int iCodeType,
					int iProgressType, bool bVerbose, bool bSilent, int iNumRuns=-1 );
	//	QString sProcessPath, QString sModelFileOnlyNoExt, bool bFullComplianceAnalysis, bool bInitHourlyResults,
	//	long lAllOrientations, long lAnalysisType, long lStdDesignBaseID, long lDesignRatingRunID, bool bStoreBEMProcDetails, bool bPerformSimulations,
	//	bool bBypassEPlus, void* pCompRuleDebugInfo, const char* pszUIVersionString, int iSimReportOpt=1, int iSimErrorOpt=1, long lStdMixedFuelRunReqd=0,
	//	long lPrelimPropRunReqd=0, long lPropFlexRunReqd=0 );
	~EPlusRunMgr();
	void DeleteRuns();
	int SetupRun( int iRunIdx, QString sRunAbbrev, QString sIDFPathFile,
						QString sEPlusWthr, bool bHourlySim, long lProgressModel, QString& sErrorMsg, const char* pszEPlusIDDFN=NULL );
	//					int iRunType, bool bAllowReportIncludeFile=true,
	//					const char* pszRunAbbrev=NULL );
	//int SetupRun_Simple( int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile=true,
	//					const char* pszRunAbbrev=NULL, const char* pszExtraEPlusCmdLineArgs=NULL,
	//					const char* pszAppendToEPlusFile=NULL, int iModelType=0 );
	int SetupRunFinish( int iRunIdx, QString& sErrorMsg, const char* pszEPlusIDDFN=NULL );
	//int SetupRun_NonRes(int iRunIdx, int iRunType, QString& sErrorMsg, bool bAllowReportIncludeFile=true,
	//							const char* pszRunID=NULL, const char* pszRunAbbrev=NULL, QString* psEPlusVer=NULL, int iBEMProcIdx=-1 );
	const EPlusRun& GetRun(int iRun) { return *m_vEPlusRun[iRun]; }
	void SetNumRuns( int iNumRuns ) { m_iNumRuns = iNumRuns; }
	int GetNumRuns() const { return m_iNumRuns; }
	int GetNumProgressRuns() const { return (m_iNumProgressRuns > 0 ? m_iNumProgressRuns : m_iNumRuns); }
	void IncrementSimulationProgress();		// SAC 2/17/19
	void DoRuns();
	void DoRunRange( int iFirstRunIdx, int iLastRunIdx );
	void MonitorRuns();
	//bool ArchiveSimOutput( int iRunIdx, QString sSimOutputPathFile, int iOutFileType );		// SAC 11/7/16 - process CSE errors and/or reports into file for user review
	void IncNumOpenGLErrors() { m_iNumOpenGLErrors++; }
	int  GetNumOpenGLErrors() const { return m_iNumOpenGLErrors; }
	bool ProcessRunOutput(exec_stream_t* pES, size_t iRun, bool &bFirstException);
	QString GetVersionInfo();
	double  GetVersionNum()		{	return m_dEPlusVersion;  }

private:
	void StartRun(EPlusRun& eplusRun);

private:
	QString m_sEPlusPath;
//	QString m_sEPlusWthr;
	QString m_sModelPathOnly;
//	QString m_sModelFileOnlyNoExt;
	QString m_sEPlusVersion;
	double  m_dEPlusVersion;
//	bool m_bFullComplianceAnalysis;
//	bool m_bInitHourlyResults;
//	long m_lAllOrientations;
//	long m_lAnalysisType;
//	long m_lStdDesignBaseID;
//	long m_lDesignRatingRunID;
//	long m_lStdMixedFuelRunReqd;
//	long m_lPrelimPropRunReqd;
//	long m_lPropFlexRunReqd;
	int m_iCodeType;
	int m_iProgressType;
	bool m_bAbortingSims;
	bool m_bVerbose;
	bool m_bStoreBEMProcDetails;
	bool m_bPerformSimulations;
	bool m_bBypassEPlus;
	bool m_bSilent;
//	void* m_pCompRuleDebugInfo;
//	const char* m_pszUIVersionString;
	int m_iError;
	int m_iNumRuns;
	int m_iSimProgressMonth;	// SAC 2/17/19
	int m_iSimReportOpt;		// SAC 11/5/16 - 0: no CSE reports / 1: user-specified reports / 2: entire .rpt file
	int m_iSimErrorOpt;		// SAC 11/5/16 - 0: no CSE errors / 1: always list CSE errors
	int m_iNumOpenGLErrors;		// SAC 3/16/17
	int m_iNumProgressRuns;		// SAC 5/5/17 - added to facilitate progress reporting on run subsets
	std::vector<EPlusRun*> m_vEPlusRun;
	std::vector<EPlusRun*> m_vEPlusActiveRun;

};		// class EPlusRunMgr

#endif // __EPLUSRUNMGR_H__