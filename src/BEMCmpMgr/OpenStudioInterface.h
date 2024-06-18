// OpenStudioInterface.h : 
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

#if !defined( _OPENSTUDIOINTERFACE_H)
#define _OPENSTUDIOINTERFACE_H

#include "..\OS_Wrap\OS_Wrap.h"

typedef struct
{
   char*       sEnduseName;
   char*       sResEnduseName;   // SAC 10/30/21 (MFam)
   char*       sEnduseAbbrev;		// SAC 8/21/14 - added for hourly results CSV export
   int         iaEndUseIdx[6];
   int         iSumIntoCompliance;
	double      daEnduseTotal[3];
	double      daTDVTotal[3];
	double      daSrcTotal[3];			// SAC 6/27/19 - 2022
	double      daSrcPrmTotal[3];		// SAC 6/27/19 - 2022
	double      daCO2Total[3];			// SAC 9/11/19 - (tic #3106)
	double      daTDSTotal[3];		// SAC 8/26/18 - A2030
	double      daSupply[3];		// SAC 9/7/18 - A2030 [Elec,TDV,TDS]
	double      dElecDemand;		// SAC 10/8/16
	double      daResEnduseTotal[3];    // SAC 10/30/21 (MFam)
	double      daResTDVTotal[3];
	double      daResSrcTotal[3];		
	double      daResSrcPrmTotal[3];	
	double      daResCO2Total[3];		
	double      daResTDSTotal[3];		
	double      daResSupply[3];		
	double      dResElecDemand;		
} EndUseMap;
#define  NUM_T24_NRES_EndUses_19  15	// SAC 7/14/18 - 13->15 for PV/Batt
#define  NUM_T24_NRES_EndUses     16	// added IDX_T24_NRES_EU_EffTot for 2022 analysis - SAC 12/11/21
#define  IDX_T24_NRES_EU_CompTot   7
#define  IDX_T24_NRES_EU_Total    14	// SAC 7/15/18 - 12->14 for PV/Batt
#define  IDX_T24_NRES_EU_EffTot   15   // SAC 12/11/21
#define  IDX_T24_NRES_EU_DHW (IDX_T24_NRES_EU_CompTot-2) // assumes DHW placed second before CompTotal enduse - SAC 9/15/20
#define  IDX_T24_NRES_EU_PV  (IDX_T24_NRES_EU_Total-2)   // assumes PV & Battery come right before TOTAL enduse
#define  IDX_T24_NRES_EU_BT  (IDX_T24_NRES_EU_Total-1)
extern EndUseMap esEUMap_CECNonRes[ NUM_T24_NRES_EndUses+1 ];

#define  NUM_T24_NRES_Fuels        3
extern const char* pszaEPlusFuelNames[NUM_T24_NRES_Fuels];

//enum CodeType	{	CT_T24N,		CT_S901G,	CT_ECBC,	CT_360,	CT_NumTypes  };	// SAC 10/2/14 - SAC 4/13/15 - SAC 1/30/20

typedef struct
{  char*       sEnergyUsePropName;
   int         iEUseSummaryEnduseArray;
   int         iEUseSummaryEnduseDecPrec;
   double      dEUseSummaryEnduseMult;
	double      dAdjust;
} EnergyUseAdjust;

extern double CMX_GetEnergyPlusVersion( const char* pszEPlusPath=NULL );
//extern bool   CMX_IsEnergyPlusVersionInstalled( int iMajor, int iMinor=-1, int iBuild=-1 );  // SAC 12/27/13

extern void SetOSWrapLogFlag( bool bLogOSWrapMsgs );
extern int /*OSWRAP_MSGCALLBACK*/ OSWrapCallback( int iCodeType, int level, const char* msg, long lProgressID );  // retval:  0:continue / -1:abort

#define OSI_SimEPlus_UserAbortedAnalysis		500	// User aborted analysis			was:  1, then 181
#define OSI_SimEPlus_InvalidSimInfo				501	// Invalid simulation settings passed into CMX_PerformSimulation_EnergyPlus_Multiple()

extern int OSWrap_ErrorIDToRunNumber( int iErr );

extern int CMX_PerformSimulation_EnergyPlus(	QString& sErrMsg, const char* pszEPlusPath, const char* pszWthrPath, const char* pszSimProcessDir,
													// RUN #1 arguments
															const char* pszSDDFile, const char* pszRunID=NULL, const char* pszLongRunID=NULL,
															BOOL bIsStdRun=FALSE, BOOL bPostEquipCapsToBEMBase=TRUE, BOOL bSimulateModel=TRUE,	// SAC 3/24/13 - added
															const char* pszIDFToSimulate=NULL, int iBEMProcIdx=-1, int iProgressModel=0,
													// RUN #2 arguments
															const char* pszSDDFile2=NULL, const char* pszRunID2=NULL, const char* pszLongRunID2=NULL,
															BOOL bIsStdRun2=FALSE, BOOL bPostEquipCapsToBEMBase2=TRUE, BOOL bSimulateModel2=TRUE,	// SAC 3/24/13 - added
															const char* pszIDFToSimulate2=NULL, int iBEMProcIdx2=-1, int iProgressModel2=0,
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose=FALSE, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL bDurationStats=FALSE, double* pdTranslationTime=NULL, double* pdSimulationTime=NULL,  // SAC 1/23/14
															int iSimulationStorage=-1, double* dEPlusVer=NULL, char* pszEPlusVerStr=NULL, int iEPlusVerStrLen=0,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr=NULL, int iOpenStudioVerStrLen=0, int iCodeType=CT_T24N,	// SAC 8/22/14		// SAC 10/2/14
															bool bIncludeOutputDiagnostics=false, int iProgressType=0,     // SAC 4/2/15		// SAC 5/27/15
                                             QVector<QString>* psaCopyAcrossModelClassPrefixes=NULL );      // SAC 11/24/20

typedef struct
{
	char pszSDDFile[FILENAME_MAX];
	char pszIDFToSimulate[FILENAME_MAX];
	char pszRunID[32];
	char pszLongRunID[64];
	bool bIsStdRun;
	bool bPostEquipCapsToBEMBase;
	bool bSimulateModel;
	int  iBEMProcIdx;
	int  iProgressModel;
	int  iOrientationIdx;	// for 90.1 baseline orientation runs (1-4)
	int  iRunIdx;
	bool bSimOutVarsCSV;		// SAC 4/12/16
}	OS_SimInfo;
#define  MultEPlusSim_MaxSims  10		// corresponding define in OS_Wrap/OS_Wrap.cpp

extern int CMX_PerformSimulation_EnergyPlus_Multiple(	QString& sErrMsg, const char* pszEPlusPath, const char* pszWthrPath, const char* pszSimProcessDir,
															const char* pszModelkitPath, OS_SimInfo** pSimInfo, int iNumSimInfo,
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose=FALSE, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL bDurationStats=FALSE, double* pdTranslationTime=NULL, double* pdSimulationTime=NULL,  // SAC 1/23/14
															int iSimulationStorage=-1, double* dEPlusVer=NULL, char* pszEPlusVerStr=NULL, int iEPlusVerStrLen=0,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr=NULL, int iOpenStudioVerStrLen=0, int iCodeType=CT_T24N,	// SAC 8/22/14		// SAC 10/2/14
															bool bIncludeOutputDiagnostics=false, int iProgressType=0, 	   // SAC 4/2/15		// SAC 5/27/15
                                             QVector<QString>* psaCopyAcrossModelClassPrefixes=NULL );      // SAC 11/24/20

extern long CMX_TestHourlyResultsRetrieval( const char* pszOSMPathFile, const char* pszSQLPathFile );

extern bool CMX_CopySizingResults_CECNonRes( int iBEMProcIdxSrc, int iBEMProcIdxDest, bool bVerbose=false );


// SAC 4/11/14 - split out OSWrapLib results setup and sim prep to separate routine
enum RunObjectType	{	ROT_Zone,		ROT_Fan,		ROT_CoilClg,	ROT_CoilHtg,	ROT_Blr,		ROT_Chlr,	ROT_HtRej,	ROT_Pump,	ROT_NumTypes  };
extern const char* epszObjNames[ROT_NumTypes];

using namespace OS_Wrap;
class COSRunInfo
{	public:
	   COSRunInfo()	{	}
		void InitializeRunInfo( OSWrapLib* pOSWrap, int iRunIdx, const char* pszSDDFile, const char* pszRunID, const char* pszLongRunID, bool bIsStdRun, bool bPostEquipCapsToBEMBase,
										bool bSimulateModel, int iBEMProcIdx=-1, const char* pszIDFToSimulate=NULL, int iCodeType=CT_T24N, bool bSimOutVarsCSV=false,
										bool bEvalReportRulesFollowingSim=false, bool bSkippingEPlusSim=false );

		bool	StoreHourlyResults()				{	return m_bStoreHourlyResults;		}
		bool	SimulatingFixedIDF()				{	return m_bSimulatingFixedIDF;		}
		int	ClassID(				int iROT )	{	return (iROT >= 0 && iROT < ROT_NumTypes) ? m_iaObjClassID[		iROT ] : -1;	}
		int	NumObjects(			int iROT )	{	return (iROT >= 0 && iROT < ROT_NumTypes) ? m_iaNumObjs[   		iROT ] :  0;	}
		int	NumResultObjects(	int iROT )	{	return (iROT >= 0 && iROT < ROT_NumTypes) ? m_iaNumResultObjs[	iROT ] :  0;	}
		QString ObjectName(	int iROT, int iObjIdx )	{	return (iROT >= 0 && iROT < ROT_NumTypes && iObjIdx >= 0 && iObjIdx < m_saObjNames[iROT].size()) ?
																							m_saObjNames[iROT][iObjIdx] : NULL;	}
		QString IDFToSimulate()			{	return m_sIDFToSimulate;	}
		QString SDDFile()					{	return m_sSDDFile;			}
		QString RunID()					{	return m_sRunID;				}
		QString LongRunID()				{	return m_sLongRunID;			}
		QString WthrPathFile()			{	return m_sWthrPathFile;		}
		bool			IsStdRun()			{	return					m_bIsStdRun;		}
		bool			PostEquipCapsToBEMBase()	{	return	m_bPostEquipCapsToBEMBase;		}
		bool			SimulateModel()	{	return					m_bSimulateModel;	}
		int			BEMProcIdx()		{	return					m_iBEMProcIdx;		}
		int			OSRunIdx()			{	return					m_iOSRunIdx;		}
		int			CodeType()			{	return					m_iCodeType;		}
		long			RptFuelUseAs()		{	return					m_lRptFuelUseAs;	}	// SAC 10/28/15
		long			RunPeriodYear()	{	return					m_lRunPeriodYear;	}	// SAC 3/1/19
		bool			SimOutVarsCSV()	{	return					m_bSimOutVarsCSV;	}	// SAC 4/12/16
		bool			EvalReportRulesFollowingSim()	{	return	m_bEvalReportRulesFollowingSim;	}	// SAC 2/18/20
		bool			SkippingEPlusSim()   {	return m_bSkippingEPlusSim;	}	   // SAC 12/08/21
		QString     SimStatusMsg()			{	return m_sSimStatusMsg;		}        // SAC 12/08/21

		int			NumQuickAnalysisPeriods()		{	return			(int) m_qaData.m_iNumQuickAnalysisPeriods;	}
		double		QuickAnalysisResultsMult()		{	return			m_qaData.m_fQuickAnalysisResultsMult;			}
		int			QuickAnalysisPeriodBeginMonth( int iMoIdx )	{	return	(int) ((iMoIdx >= 0 && iMoIdx < MAX_NUM_QANALPERIODS) ? m_qaData.m_iQuickAnalysisPeriodBeginMonth[iMoIdx] : -1);	}
		int			QuickAnalysisPeriodBeginDay(   int iDaIdx )	{	return	(int) ((iDaIdx >= 0 && iDaIdx < MAX_NUM_QANALPERIODS) ? m_qaData.m_iQuickAnalysisPeriodBeginDay[  iDaIdx] : -1);	}
		int			QuickAnalysisPeriodEndMonth(   int iMoIdx )	{	return	(int) ((iMoIdx >= 0 && iMoIdx < MAX_NUM_QANALPERIODS) ? m_qaData.m_iQuickAnalysisPeriodEndMonth[  iMoIdx] : -1);	}
		int			QuickAnalysisPeriodEndDay(     int iDaIdx )	{	return	(int) ((iDaIdx >= 0 && iDaIdx < MAX_NUM_QANALPERIODS) ? m_qaData.m_iQuickAnalysisPeriodEndDay[    iDaIdx] : -1);	}
		int			QuickAnalysisPeriodEndDOWk(    int iDaIdx )	{	return	(int) ((iDaIdx >= 0 && iDaIdx < MAX_NUM_QANALPERIODS) ? m_qaData.m_iQuickAnalysisPeriodBeginDOWk[ iDaIdx] : -1);	}

      void        SetStoreHourlyResults( bool bSHR )	{	m_bStoreHourlyResults = bSHR;  return;  }    // SAC 10/29/21 (MFam)

      void     AddToSimStatusMsg( QString sMsg )   {  if (!m_sSimStatusMsg.isEmpty())     // SAC 12/08/21
                                                         m_sSimStatusMsg += ", ";
                                                      m_sSimStatusMsg += sMsg;      return;  }

		QuickAnalysisInfo  m_qaData;

	private:
		int				m_iaObjClassID[    ROT_NumTypes ];
		int				m_iaNumResultObjs[ ROT_NumTypes ];
		int				m_iaNumObjs[       ROT_NumTypes ];
		QVector<QString>	m_saObjNames[      ROT_NumTypes ];
			//				int iNumResultZones = 0, iNumZones = 0, iNumResultFans = 0, iNumFans = 0, iNumResultCoilClgs = 0, iNumCoilClgs = 0, iNumResultCoilHtgs = 0, iNumCoilHtgs = 0,
			//						iNumResultBlrs = 0, iNumBlrs = 0, iNumResultChlrs = 0, iNumChlrs = 0, iNumResultHtRejs = 0, iNumHtRejs = 0, iNumResultPumps = 0, iNumPumps = 0;
			//				QVector<QString> saZoneNames, saFanNames, saCoilClgNames, saCoilHtgNames, saBlrNames, saChlrNames, saHtRejNames, saPumpNames;
		int		m_iOSRunIdx;
		bool 		m_bStoreHourlyResults;
		bool 		m_bSimulatingFixedIDF;
		QString	m_sIDFToSimulate;
		QString	m_sSDDFile;
		QString	m_sRunID;
		QString	m_sLongRunID;
		QString	m_sWthrPathFile;
		bool		m_bIsStdRun;
		bool		m_bPostEquipCapsToBEMBase;
		bool		m_bSimulateModel;
		int		m_iBEMProcIdx;
		int		m_iCodeType;
		long		m_lRptFuelUseAs;		// SAC 10/28/15
		long		m_lRunPeriodYear;		// SAC 3/1/19
		bool		m_bSimOutVarsCSV;		// SAC 4/12/16
		bool     m_bEvalReportRulesFollowingSim;	// SAC 2/18/20
      bool     m_bSkippingEPlusSim;    // SAC 12/08/21
		QString	m_sSimStatusMsg;        // SAC 12/08/21
};

// SAC 7/23/18 - new routine to enable split of results processing needed for integration of PV/Battery simulation via CSE
extern int PerformSimulation_EnergyPlus_Multiple(	OSWrapLib& osWrap, COSRunInfo* osRunInfo,
															QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															const char* pszModelkitPath, OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose=FALSE, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL bDurationStats=FALSE, double* pdTranslationTime=NULL, double* pdSimulationTime=NULL,  // SAC 1/23/14
															int iSimulationStorage=-1, double* dEPlusVer=NULL, char* pszEPlusVerStr=NULL, int iEPlusVerStrLen=0,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr=NULL, int iOpenStudioVerStrLen=0, int iCodeType=CT_T24N,
															bool bIncludeOutputDiagnostics=false, int iProgressType=0, bool bUseEPlusRunMgr=false, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
                                             bool bInitRunInfoOnly=false );      // SAC 10/29/21 (MFam)

extern int ProcessSimulationResults_Multiple(	OSWrapLib& osWrap, COSRunInfo* osRunInfo,
															QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose=FALSE, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL bDurationStats=FALSE, double* pdTranslationTime=NULL, double* pdSimulationTime=NULL,  // SAC 1/23/14
															int iSimulationStorage=-1, double* dEPlusVer=NULL, char* pszEPlusVerStr=NULL, int iEPlusVerStrLen=0,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr=NULL, int iOpenStudioVerStrLen=0, int iCodeType=CT_T24N,
															bool bIncludeOutputDiagnostics=false, int iProgressType=0, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
															QStringList* psaEPlusProcDirsToBeRemoved=NULL, bool bReportAllUMLHZones=false, 	// SAC 5/22/19 - added to postpone E+ directory cleanup until end of analysis to avoid deletion errors   // SAC 11/11/19
															QString* sStdDsgnCSEResultsPathFile=NULL, QVector<QString>* psaCopyAcrossModelClassPrefixes=NULL,		// SAC 10/8/20 (tic #3218)   // SAC 11/24/20
                                             void* pCompRuleDebugInfo=NULL, bool bRptMissingEPFiles=true );    // SAC 04/14/21

#endif  // _OPENSTUDIOINTERFACE_H
