// OpenStudioInterface.cpp : 
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

#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include "BEMCmpMgrCom.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\expTextIO.h"
#include "OpenStudioInterface.h"
// #include "..\BEMProc\RulPrc\textio.h"
#include "boost/filesystem.hpp"
#include "exec-stream.h"		// SAC 4/12/16 - added to facilitate execution of ReadVarsESO following E+ simulations
#include <io.h>
#include <sys/stat.h>
#include "memLkRpt.h"

using namespace OS_Wrap;


const char* pszEPlusEndUseCategs[] = {	"Heating",         // 0
													"Cooling",         // 1
													"Int Lights",      // 2
													"Ext Lights",      // 3
													"Int Equipment",   // 4
													"Ext Equipment",   // 5
													"Fans",            // 6
													"Pumps",           // 7
													"HeatRejection",   // 8
													"Humidifier",      // 9
													"HeatRecovery",    // 10
													"WaterSystems",    // 11
													"Refrigeration",   // 12
													"Generators" };    // 13
static int siEndUsesToReport[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, -1 };
//	const char* pszEndusePropNames[] = {	"Enduse1",   
//														"Enduse2",   
//														"Enduse3",   
//														"Enduse4",   
//														"Enduse5",   
//														"Enduse6",   
//														"Enduse7",   
//														"Enduse8",   
//														"Enduse9",   
//														"Enduse10",  
//														"Enduse11",  
//														"Enduse12",  
//														"Enduse13",  
//														"Enduse14",  
//														"Enduse15" };


// E+/OS Enduses NOT YET MAPPED to results passed back to the compliance analysis
//		OSEU_ExtLights,     //  ((ExteriorLights))              1
//		OSEU_ExtEquip,      //  ((ExteriorEquipment))           3
//		OSEU_Cogen,         //  ((Cogeneration))                12
//		OSEU_HtRecov_Clg,   //  ((HeatRecoveryForCooling))      19      - ???
//		OSEU_HtRecov_Htg,   //  ((HeatRecoveryForHeating)));    20      - ???
// Other Enduse QUESTIONS
// 	OSEU_IntEquip,      //  ((InteriorEquipment))           2     - Receptacle (or Process)
// 	OSEU_Misc,          //  ((Miscellaneous))               14    - Receptacle (or Process)
// 	OSEU_HtgCoils,      //  ((HeatingCoils))                15    - Spc Heating (or exclude)
// 	OSEU_ClgCoils,      //  ((CoolingCoils))                16    - Spc Cooling (or exclude)
// 	OSEU_Boilers,       //  ((Boilers))                     17    - Process (and/or Spc Htg)
// 	OSEU_Baseboard,     //  ((Baseboard))                   18    - Spc Heating (???)

// typedef struct
// {
//    char*       sEnduseName;
//    int         iaEndUseIdx[6];
//    int         iSumIntoCompliance;
// 	double      daEnduseTotal[3];
// 	double      daTDVTotal[3];
// 	double      dElecDemand;		// SAC 10/8/16
// } EndUseMap;
//#define  NUM_T24_NRES_EndUses     12
//#define  IDX_T24_NRES_EU_CompTot   7
//#define  IDX_T24_NRES_EU_Total    11
// SAC 10/13/15 - switched 'Process Ltg' to 'Other Ltg'
													                                                                                                                // SumInto
EndUseMap esEUMap_CECNonRes[] =           // enduses...                                                                                                   Compliance   daEnduseTotal    daTDVTotal
{	{  "Space Heating"      ,  "Spc Heat"  ,  OSEU_Heating,           OSEU_HtgCoils,         OSEU_Baseboard,    OSEU_HtRecov_Htg,    OSEU_Boilers,  -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Space Cooling"      ,  "Spc Cool"  ,  OSEU_Cooling,           OSEU_ClgCoils,         OSEU_HtRecov_Clg,        -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Indoor Fans"        ,  "Indr Fans" ,  OSEU_Fans,                    -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Heat Rejection"     ,  "Heat Rej"  ,  OSEU_HtReject,                -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Pumps & Misc."      ,  "Pump&Misc" ,  OSEU_Pumps,             OSEU_HtRecov,          OSEU_Humid,              -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
//	{  "Domestic HW"        ,  "Dom HW"    ,  OSEU_WaterSystems,            -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Domestic Hot Water" ,  "Dom HW"    ,  OSEU_WaterSystems,            -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
//	{  "Lighting"           ,  "Lighting"  ,  OSEU_IntLights_Reg,           -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Indoor Lighting"    ,  "Lighting"  ,  OSEU_IntLights_Comp,          -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "COMPLIANCE TOTAL"   ,  "Comp Tot"  ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Receptacle"         ,  "Recept"    ,  OSEU_IntEquip_Recept,         -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Process"            ,  "Process"   ,  OSEU_IntEquip_Process,  OSEU_IntEquip_Refrig,  OSEU_Refrig,       OSEU_IntEquip_IntTrans,   -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },		// SAC 8/19/14 - added OSEU_IntEquip_IntTrans to capture elevator/escalator energy use
	{  "Other Ltg"          ,  "Othr Ltg"  ,  OSEU_IntLights_NonComp,       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Process Motors"     ,  "Proc Mtrs" ,  OSEU_Fans_PrkgGar,            -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },		// SAC 2/1/17 - added Process Motors to capture parking garage exhaust fans (tic #2033)
	{  "TOTAL"              ,  "TOTAL"     ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  NULL                 ,  NULL        ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   }  };
                                                                                                // FINAL enduse index must be '-1' for each record

const char* pszaEPlusFuelNames[] = {		"Electricity",    // OSF_Elec,    //  ((Electricity)(Electricity))
														"NaturalGas" ,    // OSF_Gas,     //  ((Gas)(Natural Gas))        
														"OtherFuel"   };  // OSF_Other,   //  ((OtherFuel)(Other Fuel))   
static const char* pszaFuelPropName[] = {		"Elec",
															"NatGas",
															"Other"   };

static double dHrlyRes[8760];
static double dHrlyResCompTot[8760];
static double dHrlyResTot[8760];
static void InitHrlyRes( double* pRes )
{	for (int hr=0; hr<8760; hr++)
		pRes[hr] = 0.0;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

long CMX_TranslateToSDD( const char* pszInputPathFile, const char* pszOutputPathFile, int iInputType )  // SAC 1/10/14
{
	OSWrapLib osWrap;
	return osWrap.TranslateToSDD( pszInputPathFile, pszOutputPathFile, iInputType );
}

double CMX_GetEnergyPlusVersion( const char* pszEPlusPath /*=NULL*/ )
{
	OSWrapLib osWrap;
	return osWrap.EnergyPlusVersion( pszEPlusPath );
}

//bool CMX_IsEnergyPlusVersionInstalled( int iMajor, int iMinor /*=-1*/, int iBuild /*=-1*/ )  // SAC 12/27/13
//{
//	OSWrapLib osWrap;
//	return osWrap.EnergyPlusVersionInstalled( iMajor, iMinor, iBuild );
//}


long CMX_TestHourlyResultsRetrieval( const char* pszOSMPathFile, const char* pszSQLPathFile )
{
	OSWrapLib osWrap;
	long lRetVal = osWrap.HourlyResultsRetrieval( pszOSMPathFile, pszSQLPathFile );
	return lRetVal;
}


bool CMX_CopySizingResults_CECNonRes( int iBEMProcIdxSrc, int iBEMProcIdxDest, bool /*bVerbose=false*/ )
{	int iModelCount = BEMPX_GetModelCount();
	bool bRetVal = (iBEMProcIdxSrc < iModelCount && iBEMProcIdxDest < iModelCount);
	if (!bRetVal)
	{	assert( FALSE );
	}
	else
	{	int iClassIDs[] = {	BEMPX_GetDBComponentID( "ThrmlZn" ),
									BEMPX_GetDBComponentID( "Fan"     ),
									BEMPX_GetDBComponentID( "CoilClg" ),
									BEMPX_GetDBComponentID( "CoilHtg" ),
									BEMPX_GetDBComponentID( "Blr"     ),			// SAC 8/27/13 - added Blr, Chlr, HtRej & Pump results
									BEMPX_GetDBComponentID( "Chlr"    ),
									BEMPX_GetDBComponentID( "HtRej"   ),
									BEMPX_GetDBComponentID( "Pump"    ),
									0, -99  };
#define  MAX_RESCOPY_DBIDSPEROBJ  6
		const char* pszPropNames[8][MAX_RESCOPY_DBIDSPEROBJ] = {	{	"ClgDsgnLd"        , "HtgDsgnLd"         , "ClgDsgnFlowSim", "HtgDsgnFlowSim",  NULL,  NULL  },
																					{	"FlowCapSim"       ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapTotGrossRtdSim", "CapSensGrossRtdSim",  NULL           ,  NULL           ,  NULL,  NULL  }, 
																					{	"CapTotGrossRtdSim",  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"FlowCapSim"       ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  }  };
		long laDBIDs[MAX_RESCOPY_DBIDSPEROBJ];
		int iClsIdx=-1;
		while (iClassIDs[++iClsIdx] > 0 && bRetVal)
		{	int iNumCopyFromObjs = BEMPX_GetNumObjects( iClassIDs[iClsIdx], BEMO_User, iBEMProcIdxSrc );
			int iNumCopyToObjs   = BEMPX_GetNumObjects( iClassIDs[iClsIdx], BEMO_User, iBEMProcIdxDest );			assert( iNumCopyFromObjs == iNumCopyToObjs );
			if (iNumCopyFromObjs == iNumCopyToObjs && iNumCopyFromObjs > 0)
			{	double fVal;
				for (int i=0; (bRetVal && i<MAX_RESCOPY_DBIDSPEROBJ); i++)
				{	if (pszPropNames[iClsIdx][i] != NULL)
					{	laDBIDs[i] = BEMPX_GetDatabaseID( pszPropNames[iClsIdx][i], iClassIDs[iClsIdx] );				assert( laDBIDs[i] > 0 );

						if (laDBIDs[i] <= 0)
						{	assert( FALSE );
						}
						else
						{	for (int iObj=0; iObj < iNumCopyFromObjs; iObj++)
								if (BEMPX_GetFloat( laDBIDs[i], fVal, -999 /*default*/, -1 /*DispDataType*/, iObj, BEMO_User, iBEMProcIdxSrc ) && fVal != -999)
								{	if (BEMPX_SetBEMData( laDBIDs[i], BEMP_Flt, &fVal, BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerformResets*/, iBEMProcIdxDest ) < 0)
									{	bRetVal = false;		assert( FALSE );
									}
								}
								else
								{	assert( FALSE );	// allow not all results to be retrieved
								}
						}
// SAC 6/13/13 - didn't seem to be looping over all objects in above code...
//						if (laDBIDs[i] > 0 && BEMPX_GetFloat( laDBIDs[i], fVal, -999 /*default*/, -1 /*DispDataType*/, i, BEMO_User, iBEMProcIdxSrc ) && fVal != -999)
//						{	if (BEMPX_SetBEMData( laDBIDs[i], BEMP_Flt, &fVal, BEMO_User, i, BEMS_SimResult, BEMO_User, TRUE /*bPerformResets*/, iBEMProcIdxDest ) < 0)
//							{	bRetVal = false;		assert( FALSE );
//							}
//						}
//						else
//						{	assert( FALSE );	// allow not all results to be retrieved
//						}
					}
				}
			}
		}
		assert( iClassIDs[++iClsIdx] == -99 );  // if not, then one of the classes screwed up
	}
	return bRetVal;
}


void LogEnergyPlusMessages( OSWrapLib* pOSWrap, COSRunInfo* pOSRunInfo )
{	std::string strMsg;
	QString sLogMsg;
	for (int iMsgTyp=0; (pOSWrap && pOSRunInfo && iMsgTyp<3); iMsgTyp++)
	{	int iNumMsgs 		= (iMsgTyp==0 ? pOSWrap->GetNum_FatalErrors( pOSRunInfo->OSRunIdx() ) : (iMsgTyp==1 ? pOSWrap->GetNum_SevereErrors( pOSRunInfo->OSRunIdx() ) : pOSWrap->GetNum_Warnings( pOSRunInfo->OSRunIdx() )));
		QString sMsgType	= (iMsgTyp==0 ? "Fatal Error(s)" : (iMsgTyp==1 ? "Severe Error(s)" : "Warning(s)"));
		if (iNumMsgs > 0)
		{
			sLogMsg = QString( "    EnergyPlus %1 (%2):" ).arg( sMsgType, QString::number(iNumMsgs) );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			for (int iMsgIdx=0; iMsgIdx<iNumMsgs; iMsgIdx++)
			{	if (iMsgTyp==0)
					strMsg = pOSWrap->GetMsg_FatalError( pOSRunInfo->OSRunIdx(), iMsgIdx );
				else if (iMsgTyp==1)
					strMsg = pOSWrap->GetMsg_SevereError( pOSRunInfo->OSRunIdx(), iMsgIdx );
				else
					strMsg = pOSWrap->GetMsg_Warning( pOSRunInfo->OSRunIdx(), iMsgIdx );
				assert( strMsg.size() > 0 );
				if (strMsg.size() > 0)
		//		{	sLogMsg = QString( "     %3d: %s" ).arg( iMsgIdx+1, strMsg.c_str() );
				{
					sLogMsg = QString( "     %1: %2" ).arg( QString::number(iMsgIdx+1), 3 ).arg( strMsg.c_str() );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
}	}	}	}	}


#define  MAX_SimStorageVal  7		// SAC 1/24/14
typedef struct filecopyinfo_
{
   std::string sCopyFrom;
   std::string sCopyTo;
	int    iFromDirID;
	bool   bReportFailure;
	int    iaCopyForOptVal[MAX_SimStorageVal];
} FileCopyInfo;


//enum RunObjectType	{				ROT_Zone,		ROT_Fan,		ROT_CoilClg,	ROT_CoilHtg,	ROT_Blr,		ROT_Chlr,	ROT_HtRej,	ROT_Pump,	ROT_NumTypes  };
const char* epszObjNames[] = {	"ThrmlZn",		"Fan",		"CoilClg",		"CoilHtg",		"Blr",		"Chlr",		"HtRej",		"Pump"  };

void COSRunInfo::InitializeRunInfo( OSWrapLib* pOSWrap, int iRunIdx, const char* pszSDDFile, const char* pszRunID, const char* pszLongRunID, bool bIsStdRun, bool bPostEquipCapsToBEMBase,
												bool bSimulateModel, int iBEMProcIdx /*=-1*/, const char* pszIDFToSimulate /*=NULL*/, int iCodeType /*=CT_T24N*/, bool bSimOutVarsCSV /*=false*/ )
{	QString sObjName;
	m_bStoreHourlyResults = false;
	int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );												assert( iCID_Proj > 0 );
	if (pOSWrap)
	{	for (int i=0; i<ROT_NumTypes; i++)
		{	m_iaNumResultObjs[i] = 0;
			m_iaNumObjs[      i] = 0;
			m_saObjNames[     i].clear();
			m_iaObjClassID[i]   = BEMPX_GetDBComponentID( epszObjNames[i] );					assert( m_iaObjClassID[i] > 0 );
			long lDBID_obj_Name = BEMPX_GetDatabaseID( "Name", m_iaObjClassID[i] );			assert( lDBID_obj_Name > 0 );
			if (m_iaObjClassID[i] > 0 && lDBID_obj_Name > 0)
			{	m_iaNumObjs[i] = BEMPX_GetNumObjects( m_iaObjClassID[i], BEMO_User, iBEMProcIdx );
				for (int iObj=0; iObj < m_iaNumObjs[i]; iObj++)
				{	if (!BEMPX_GetString( lDBID_obj_Name, sObjName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iObj, BEMO_User, NULL, 0, iBEMProcIdx ) || sObjName.isEmpty())
					{	assert( FALSE );		// object name problem !!
					}
					else
					{	m_saObjNames[i].push_back( sObjName );
						int iRV=-1;
						switch (i)
						{	case  0 :  iRV = pOSWrap->AddResult_Zone(    iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  1 :  iRV = pOSWrap->AddResult_Fan(     iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  2 :  iRV = pOSWrap->AddResult_CoilClg( iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  3 :  iRV = pOSWrap->AddResult_CoilHtg( iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  4 :  iRV = pOSWrap->AddResult_Blr(     iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  5 :  iRV = pOSWrap->AddResult_Chlr(    iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  6 :  iRV = pOSWrap->AddResult_HtRej(   iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							case  7 :  iRV = pOSWrap->AddResult_Pump (   iRunIdx, sObjName.toLocal8Bit().constData() );			assert( iRV > 0 );			break;
							default :	assert( FALSE );
						}
						if (iRV > 0)
							m_iaNumResultObjs[i] += 1;
		}	}	}	}

	  // SAC 4/19/13 - determine if annual sim, and if so, call for hourly results storage
		long lBeginMonth, lBeginDay, lEndMonth, lEndDay, lYear;
		m_bStoreHourlyResults = (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodBeginMonth", iCID_Proj ), lBeginMonth, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lBeginMonth ==  1  &&
											BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodBeginDay",   iCID_Proj ), lBeginDay  , 0, -1, 0, BEMO_User, iBEMProcIdx ) && lBeginDay   ==  1  && 
											BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodEndMonth",   iCID_Proj ), lEndMonth  , 0, -1, 0, BEMO_User, iBEMProcIdx ) && lEndMonth   == 12  && 
											BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodEndDay",     iCID_Proj ), lEndDay    , 0, -1, 0, BEMO_User, iBEMProcIdx ) && lEndDay     == 31  && 
											BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodYear",       iCID_Proj ), lYear      , 0, -1, 0, BEMO_User, iBEMProcIdx ) && lYear       > 0  );

		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile" ), m_sWthrPathFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx );
	}
	else
	{	for (int i=0; i<ROT_NumTypes; i++)
		{	m_iaNumResultObjs[i] = 0;
			m_iaNumObjs[      i] = 0;
			m_saObjNames[     i].clear();
			m_iaObjClassID[   i] = 0;
		}
		m_bStoreHourlyResults = false;
		m_sWthrPathFile.clear();
	}

	m_iOSRunIdx			= iRunIdx;
	m_bSimulatingFixedIDF = (pszIDFToSimulate && strlen( pszIDFToSimulate ) > 0 && FileExists( pszIDFToSimulate ));  // SAC 1/25/14
	m_sIDFToSimulate	= pszIDFToSimulate;
	m_sSDDFile			= pszSDDFile;
	m_sRunID  			= pszRunID;
	m_sLongRunID		= pszLongRunID;
	m_bIsStdRun			= bIsStdRun;
	m_bPostEquipCapsToBEMBase = bPostEquipCapsToBEMBase;
	m_bSimulateModel	= bSimulateModel;
	m_iBEMProcIdx		= iBEMProcIdx;
	m_iCodeType			= iCodeType;
	m_bSimOutVarsCSV	= bSimOutVarsCSV;		// SAC 4/12/16

	m_lRptFuelUseAs = -1;	// SAC 10/28/15
	long lRFUA;
	if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "RptFuelUseAs", iCID_Proj ), lRFUA, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lRFUA >= 0)
		m_lRptFuelUseAs = lRFUA;

	long lDoQuickAnalysis=0;
	bool bQuickAnalysisDataOK=false;
	if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "QuickAnalysis"            , iCID_Proj ), lDoQuickAnalysis                    , 0, -1, 0, BEMO_User, iBEMProcIdx ) && lDoQuickAnalysis > 0 &&
			BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumOfQuickAnalysisPeriods", iCID_Proj ), m_qaData.m_iNumQuickAnalysisPeriods , 0, -1, 0, BEMO_User, iBEMProcIdx ) &&
					m_qaData.m_iNumQuickAnalysisPeriods > 0 && m_qaData.m_iNumQuickAnalysisPeriods <= MAX_NUM_QANALPERIODS &&
			BEMPX_GetFloat(   BEMPX_GetDatabaseID( "QuickAnalysisResultsMult" , iCID_Proj ), m_qaData.m_fQuickAnalysisResultsMult, 0, -1, 0, BEMO_User, iBEMProcIdx ) && m_qaData.m_fQuickAnalysisResultsMult > 0 )
	{	bQuickAnalysisDataOK = true;
		long lDBID_Proj_QuickAnalysisBeginMonth     = BEMPX_GetDatabaseID( "QuickAnalysisBeginMonth"    , iCID_Proj );
		long lDBID_Proj_QuickAnalysisBeginDay       = BEMPX_GetDatabaseID( "QuickAnalysisBeginDay"      , iCID_Proj );
		long lDBID_Proj_QuickAnalysisEndMonth       = BEMPX_GetDatabaseID( "QuickAnalysisEndMonth"      , iCID_Proj );
		long lDBID_Proj_QuickAnalysisEndDay         = BEMPX_GetDatabaseID( "QuickAnalysisEndDay"        , iCID_Proj );
		long lDBID_Proj_QuickAnalysisBeginDayOfWeek = BEMPX_GetDatabaseID( "QuickAnalysisBeginDayOfWeek", iCID_Proj );
		int iaDaysPerMo[12] = { 31, 28, 31, 30, 31, 30,  31, 31, 30, 31, 30, 31 };
		for (int iPer=0; (bQuickAnalysisDataOK && iPer < MAX_NUM_QANALPERIODS); iPer++)
		{	if (iPer < m_qaData.m_iNumQuickAnalysisPeriods)
			{	if (	!BEMPX_GetInteger( lDBID_Proj_QuickAnalysisBeginMonth     + iPer, m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ], 0, -1, 0, BEMO_User, iBEMProcIdx ) ||
						!BEMPX_GetInteger( lDBID_Proj_QuickAnalysisBeginDay       + iPer, m_qaData.m_iQuickAnalysisPeriodBeginDay[   iPer ], 0, -1, 0, BEMO_User, iBEMProcIdx ) ||
						!BEMPX_GetInteger( lDBID_Proj_QuickAnalysisEndMonth       + iPer, m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ], 0, -1, 0, BEMO_User, iBEMProcIdx ) ||
						!BEMPX_GetInteger( lDBID_Proj_QuickAnalysisEndDay         + iPer, m_qaData.m_iQuickAnalysisPeriodEndDay[     iPer ], 0, -1, 0, BEMO_User, iBEMProcIdx ) ||
						!BEMPX_GetInteger( lDBID_Proj_QuickAnalysisBeginDayOfWeek + iPer, m_qaData.m_iQuickAnalysisPeriodBeginDOWk[  iPer ], 0, -1, 0, BEMO_User, iBEMProcIdx ) ||
						m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ] < 1  ||  m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ] > 12  ||
						m_qaData.m_iQuickAnalysisPeriodBeginDay[   iPer ] < 1  ||  m_qaData.m_iQuickAnalysisPeriodBeginDay[   iPer ] > iaDaysPerMo[ m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ]-1 ]  ||
						m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ] < 1  ||  m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ] > 12  ||
						m_qaData.m_iQuickAnalysisPeriodEndDay[     iPer ] < 1  ||  m_qaData.m_iQuickAnalysisPeriodEndDay[     iPer ] > iaDaysPerMo[ m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ]-1 ]  ||
						m_qaData.m_iQuickAnalysisPeriodBeginDOWk[  iPer ] < 1  ||  m_qaData.m_iQuickAnalysisPeriodBeginDOWk[  iPer ] >  7  )
					bQuickAnalysisDataOK = false;
			}
			else
			{	m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ] = 0;			m_qaData.m_iQuickAnalysisPeriodBeginDay[   iPer ] = 0;
				m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ] = 0;			m_qaData.m_iQuickAnalysisPeriodEndDay[     iPer ] = 0;		m_qaData.m_iQuickAnalysisPeriodBeginDOWk[  iPer ] = 0;
		}	}
	}
	if (!bQuickAnalysisDataOK)
	{	m_qaData.m_iNumQuickAnalysisPeriods = 0;
		m_qaData.m_fQuickAnalysisResultsMult = 1;
		for (int iPer=0; iPer < MAX_NUM_QANALPERIODS; iPer++)
		{	m_qaData.m_iQuickAnalysisPeriodBeginMonth[ iPer ] = 0;			m_qaData.m_iQuickAnalysisPeriodBeginDay[   iPer ] = 0;
			m_qaData.m_iQuickAnalysisPeriodEndMonth[   iPer ] = 0;			m_qaData.m_iQuickAnalysisPeriodEndDay[     iPer ] = 0;		m_qaData.m_iQuickAnalysisPeriodBeginDOWk[  iPer ] = 0;
		}
	}
}


static inline double RoundVal( double dVal, int iDecPrec )
{	double dRetVal = 0.0;
	switch (iDecPrec)
	{	case -3 :	dRetVal = (double) ((int) ((dVal / 1000.0) + 0.5)) * 1000.0;		break;
		case -2 :	dRetVal = (double) ((int) ((dVal /  100.0) + 0.5)) *  100.0;		break;
		case -1 :	dRetVal = (double) ((int) ((dVal /   10.0) + 0.5)) *   10.0;		break;
		case  0 :	dRetVal = (double) ((int) ((dVal         ) + 0.5))         ;		break;
		case  1 :	dRetVal = (double) ((int) ((dVal *   10.0) + 0.5)) /   10.0;		break;
		case  2 :	dRetVal = (double) ((int) ((dVal *  100.0) + 0.5)) /  100.0;		break;
		case  3 :	dRetVal = (double) ((int) ((dVal * 1000.0) + 0.5)) / 1000.0;		break;
		default :	assert( FALSE );		break;
	}
	return dRetVal;
}


// SAC 4/17/14 - moved ALL results processing to this subordinate routine
BOOL ProcessSimulationResults( OSWrapLib& osWrap, COSRunInfo& osRunInfo, int& iRetVal, const char* pszSimProcessDir, BOOL bVerbose, int iSimulationStorage, const char* pszEPlusPath )
{
	BOOL bRetVal = TRUE;
	QString sLogMsg, sTemp;

		double fBldgNonResFlrArea = 0, fBldgResFlrArea = 0, fTotBldgFlrArea=0;
		long lCliZnNum=0;
		if (BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:NonResFlrArea" ), fBldgNonResFlrArea, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  // SAC 3/13/13 - CondFlrArea -> res/nonres...
			 BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:ResFlrArea"    ), fBldgResFlrArea   , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  (fBldgNonResFlrArea > 0 || fBldgResFlrArea > 0) &&
			 BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CliZnNum"      ), lCliZnNum         , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  lCliZnNum > 0 )
			fTotBldgFlrArea = fBldgNonResFlrArea + fBldgResFlrArea;

		int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
		long lDBID_EUseSummary_ZoneUMLHsLoaded  = BEMPX_GetDatabaseID( "ZoneUMLHsLoaded", iCID_EUseSummary );		assert( lDBID_EUseSummary_ZoneUMLHsLoaded > 0 );
		long lDBID_EUseSummary_ZoneUMLHs        = BEMPX_GetDatabaseID( "ZoneUMLHs"      , iCID_EUseSummary );		assert( lDBID_EUseSummary_ZoneUMLHs > 0 );

		QString sHrlyElecDemMultTblCol;	// SAC 10/8/16 - enable specification of hourly elec demand mult table:column via ruleset var
		if (osRunInfo.m_qaData.m_iNumQuickAnalysisPeriods < 1)	// SAC 10/11/16 - prevent demand calcs/storage when performing QuickAnalysis
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:HrlyElecDemMultTableAndColumnName" ), sHrlyElecDemMultTblCol, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );

		int iOrientNum = 0;
		if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
		{	QString sRunID = osRunInfo.RunID();
			if (sRunID.length() == 3)
			{	sRunID = sRunID[2];
				iOrientNum = atoi( sRunID.toLocal8Bit().constData() );
		}	}

		if (osRunInfo.StoreHourlyResults() && iRetVal == 0)
		{							if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Pulling/grouping/summing hourly results from OSWrap", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			int iCID_EnergyUse = BEMPX_GetDBComponentID( "EnergyUse" );		assert( iCID_EnergyUse > 0 );
			int iEUIdx, iFl, hr, iError;
			QString sEUPropNameBase = (osRunInfo.IsStdRun() ? "Std" : "Prop"), sPropName;
			for (iFl=0; iFl < OSF_NumFuels; iFl++)
			{	iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{	// initialize result to contain hourly results sum already stored (via previous simulation of this run, such as CEC-T24 DHW)
					double dExistResult = BEMPX_GetHourlyResultSum( NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, NULL, NULL, NULL, NULL, NULL, NULL, NULL, osRunInfo.BEMProcIdx() );
					if (dExistResult != -99999.0)
						esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] = dExistResult;
					else
						esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daTDVTotal[   iFl] = 0.0;
					if (iFl==0)  // SAC 10/8/16
						esEUMap_CECNonRes[iEUIdx].dElecDemand = 0.0;
				}
			}
			for (iFl=0; iFl < OSF_NumFuels; iFl++)
			{
				InitHrlyRes( dHrlyResCompTot );
				InitHrlyRes( dHrlyResTot );
				iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{	
					InitHrlyRes( dHrlyRes );
					double dEUTot = 0.0;
					int iEU2Idx = -1;
					while (esEUMap_CECNonRes[iEUIdx].iaEndUseIdx[++iEU2Idx] >= 0)
					{	dEUTot = 0.0;
						std::vector<double>* pdaHrlyOSRes = osWrap.GetHourlyResultArray( osRunInfo.OSRunIdx(), iFl, esEUMap_CECNonRes[iEUIdx].iaEndUseIdx[iEU2Idx], &dEUTot );
						if (pdaHrlyOSRes)
						{	esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] += dEUTot;
							for (hr=0; hr<8760; hr++)
								dHrlyRes[hr] += pdaHrlyOSRes->at(hr);
						}
					}
					if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total && esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] > 0)
					{
							esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
						if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
							esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
					}
	
					if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total)
					//{	double dResult = BEMPX_AddHourlyResultArray( dHrlyRes, pszLongRunID, pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, -1 /*iBEMProcIdx*/, TRUE /*bAddIfNoExist*/ );
					{	double dResult = BEMPX_SumIntoHourlyResultArray( dHrlyRes, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, osRunInfo.BEMProcIdx(), TRUE /*bAddIfNoExist*/ );		dResult;
						// not the case when preliminary simulation results in some simulation results being populated prior to retrieval of these -- assert( WithinMargin( dResult, esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl], (max( fabs(dResult), fabs(esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl]) )/1000.0) ) );  // dResult == esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] );
					//	if (dResult == -99999)
					//	{	ExpSetErr( error, EXP_RuleProc, "Error adding hourly result array within ApplyHourlyResultMultipliers() function." );
					//		break;
					//	}
					}

			// SAC 8/18/14 - fixed bug where DHW simulation results NOT being accounted for when applying TDV multipliers to hourly results
					double* pdBEMHrlyRes	= NULL;
					int iBEMHrlyResPtrRV = BEMPX_GetHourlyResultArrayPtr( &pdBEMHrlyRes, NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, osRunInfo.BEMProcIdx() );
					bool bBEMHrlyResPtrOK = (pdBEMHrlyRes && iBEMHrlyResPtrRV==0);
	
				// we now have all hourly results for this ruleset enduse and fuel (Elec/NatGas/Other) combination...
				// NOW grab the hourly TDV Factors (from ruleset table), apply them to the hourly results and sum the totals into annual TDV results (by fuel and enduse) 
					if (osRunInfo.CodeType() == CT_T24N && iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total)		// added check to perform TDV only on CT_T24N runs
					{	assert( fTotBldgFlrArea > 0 );
						int iTableCol = ((lCliZnNum-1) * 3) + iFl + 2;
	// TO DO - move table name OUT of source code
						double dTDVSum = 0.0;
						if (esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] > 0)
			//				dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( dHrlyRes, "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
							dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
						if (dTDVSum < 0)
						{	// ERROR
							assert( FALSE );
						}
						else if (fTotBldgFlrArea > 0)
						{		esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl] = dTDVSum / fTotBldgFlrArea;
	
								esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
							if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
								esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
						}

					// SAC 10/8/16 - elec demand calc
						if (iFl==0 && !sHrlyElecDemMultTblCol.isEmpty() && esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0.0)
						{
							double dEDem = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sHrlyElecDemMultTblCol.toLocal8Bit().constData(), -1, (bVerbose != FALSE) );
							if (dEDem != 0.0)
							{		esEUMap_CECNonRes[iEUIdx].dElecDemand = dEDem;

									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].dElecDemand += dEDem;
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].dElecDemand += dEDem;
						}	}
					}

				// store annual energy use & TDV sums by fuel and enduse
					if (iCID_EnergyUse > 0)
					{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );
						if (pEUObj == NULL)
						{	assert( !osRunInfo.IsStdRun() && iFl==0 );	// should need to create EU object if first run & first fuel
							pEUObj = BEMPX_CreateObject( iCID_EnergyUse, esEUMap_CECNonRes[iEUIdx].sEnduseName, NULL /*pPar*/, BEMO_User, true /*bDfltPar*/, true /*bAutoCr8*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseName", iCID_EnergyUse ), BEMP_Str, (void*) esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User,
                                                     -1 /*iOccur*/, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );  // -or- BEMS_SimResult
						}
						else
						{	assert( osRunInfo.IsStdRun() || iFl>0 );		// should NOT have EU object in model if this is the first run, first fuel
						}
						if (pEUObj == NULL)
						{	assert( FALSE );
						}
						else
						{	int iEUObjIdx = BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() );		assert( iEUObjIdx >= 0 );
							double fEnergy = esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
							if (iOrientNum < 1)
								sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
							else
								sPropName = QString( "%1%2EnergyByOrient[%3]" ).arg( sEUPropNameBase, pszaFuelPropName[iFl], QString::number(iOrientNum) );	// S901G
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fEnergy, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							// then do same for TDV...
							if (osRunInfo.CodeType() == CT_T24N)		// added check to perform TDV only on CT_T24N runs
							{	fEnergy = esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
								sPropName = QString( "%1%2TDV" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fEnergy, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						// SAC 10/8/16 - post elec demand to database
							if (iFl==0 && !sHrlyElecDemMultTblCol.isEmpty() && esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0.0)
							{	double dEDem = esEUMap_CECNonRes[iEUIdx].dElecDemand;
								if (iOrientNum < 1)
									sPropName = QString( "%1ElecDemand" ).arg( sEUPropNameBase );
								else
									sPropName = QString( "%1ElecDemandByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );	// S901G
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &dEDem, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}
					}
				}	// end of  while (esEUMap_CECNonRes[++iEUIdx]...
			}	// end of  for (iFl...
	
			// now go BACK through enduses storing total kBTU/ft2-yr sums
			QString sPassFail;
			double dRndTDVTotMargin=0.0, dRndTDVCompTotMargin=0.0, dRndStdTDVTot = 0.0, dRndStdTDVCompTot=0.0;
			if (fTotBldgFlrArea > 0 && iCID_EnergyUse > 0)
			{	iEUIdx = -1;
				double fRndCompMarginTot = 0;
				double dRndPropTDVTot = 0.0;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
					int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
					if (iEUObjIdx >= 0)
					{	double fEUTot = 0, fVal, fTDVTot = 0;
						for (iFl=0; iFl < OSF_NumFuels; iFl++)
						{
							if (iOrientNum < 1)
								sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
							else
								sPropName = QString( "%1%2EnergyByOrient[%3]" ).arg( sEUPropNameBase, pszaFuelPropName[iFl], QString::number(iOrientNum) );
							if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
							{	assert( FALSE );
							}
							else if (fVal > 0)
							{	if (iFl == 0)
									fEUTot += (fVal * 3.41214 / fTotBldgFlrArea);				// kWh -> kBtu/SF
								else
									fEUTot += (fVal * 100.0   / fTotBldgFlrArea);				// therms -> kBtu/SF
							}
							if (osRunInfo.CodeType() == CT_T24N)		// added check to perform TDV only on CT_T24N runs
								fTDVTot += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];  // no unit conversion needed for TDV
						}
						if (iOrientNum < 1)
							sPropName = QString( "%1TotalEnergy" ).arg( sEUPropNameBase );
						else
							sPropName = QString( "%1TotalEnergyByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fEUTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
				// and do something similar for TDV - only no unit adjustments here, just summing of existing data
						if (osRunInfo.CodeType() == CT_T24N)		// added check to perform TDV only on CT_T24N runs
						{
							sPropName = QString( "%1TDV" ).arg( sEUPropNameBase );
							sPropName.replace( "Prop", "Proposed" );    // unfortunate inconsistency in property naming...
							sPropName.replace( "Std" , "Standard" );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fTDVTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (osRunInfo.IsStdRun())
							{	double fPropTDV = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "ProposedTDV", iCID_EnergyUse ), fPropTDV, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
								{	assert( FALSE );
								}
								else
								{	double fCompMarginReal = fTDVTot - fPropTDV;																				fCompMarginReal;
									double fPctImproveReal = ((fTDVTot > 0 ? (fTDVTot - fPropTDV) / fTDVTot : 0) * 100.0);			fPctImproveReal;
								// SAC 5/8/14 - revise margin results to be consistent w/ rounded values   // SAC 6/8/16 - switched TDV rounding from 1 to 2 decimal places (tic #1735)
									double dStTDV = RoundVal( fTDVTot , 2 );
									double dPrTDV = RoundVal( fPropTDV, 2 );
									if (iEUIdx == IDX_T24_NRES_EU_CompTot || iEUIdx == IDX_T24_NRES_EU_Total)		// SAC 6/8/16 - replace real differences w/ sum of rounded differences (tic #1735)
									{	dStTDV = dRndStdTDVTot;
										dPrTDV = dRndPropTDVTot;
										if (iEUIdx == IDX_T24_NRES_EU_CompTot)
										{	dRndTDVCompTotMargin = dRndStdTDVTot - dRndPropTDVTot;
											dRndStdTDVCompTot    = dRndStdTDVTot;
										}
										else
											dRndTDVTotMargin     = dRndStdTDVTot - dRndPropTDVTot;
									}
									else
									{	dRndStdTDVTot  += dStTDV;
										dRndPropTDVTot += dPrTDV;
									}
									double fCompMargin = (dStTDV - dPrTDV);
									double fPctImprove = (dStTDV > 0 ? ((dStTDV - dPrTDV) * 100.0 / dStTDV) : 0.0);
									if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total)
									{	fRndCompMarginTot += fCompMargin;
				//						dRndStdTDVTot     += dStTDV;
									}
									else
									{	fCompMargin = fRndCompMarginTot;
										fPctImprove = (dRndStdTDVTot > 0 ? (fCompMargin * 100.0 / dRndStdTDVTot) : 0.0);
									}

									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse ), BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse ), BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									if (iEUIdx == IDX_T24_NRES_EU_CompTot)
									{	sPassFail = (fCompMargin > -0.001 /*>=0*/ ? "PASS" : "FAIL");
	
											sLogMsg = QString( "  PerfSim_E+ - Final Result: %1  -- compliance margin: %2 (%3%)" ).arg( sPassFail, QString::number(fCompMargin), QString::number(fPctImprove, 'f', 2) );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
								}
						}	}

						if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && osRunInfo.IsStdRun() && iOrientNum == 4)	// calculate final (average) energy for S901G & ECBC
						{
		// SAC 8/27/15 - SUM ALL ENERGY RESULTS INTO SINGLE/PREVIOUS PROPERTIES
							double fElecTot=0, fGasTot=0, fOthrTot=0, fTotal=0, fElec, fGas, fOthr, fTot;
							for (int iOIdx=1; iOIdx<=4; iOIdx++)
							{
								sPropName = QString( "StdElecEnergyByOrient[%1]" ).arg(   QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fElec, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
								sPropName = QString( "StdNatGasEnergyByOrient[%1]" ).arg( QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fGas , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
								sPropName = QString( "StdOtherEnergyByOrient[%1]" ).arg(  QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fOthr, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
								sPropName = QString( "StdTotalEnergyByOrient[%1]" ).arg(  QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fTot , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
								fElecTot += fElec;		fGasTot += fGas;		fOthrTot += fOthr;		fTotal += fTot;
							}
							fElecTot = (fElecTot/4.0);		fGasTot = (fGasTot/4.0);		fOthrTot = (fOthrTot/4.0);		fTotal = (fTotal/4.0);
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdElecEnergy",   iCID_EnergyUse ), BEMP_Flt, &fElecTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdNatGasEnergy", iCID_EnergyUse ), BEMP_Flt, &fGasTot , BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdOtherEnergy",  iCID_EnergyUse ), BEMP_Flt, &fOthrTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdTotalEnergy",  iCID_EnergyUse ), BEMP_Flt, &fTotal  , BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}

						if (iEUIdx == IDX_T24_NRES_EU_Total)		// utility cost calcs
						{	long lCalculateEnergyCosts;
							int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );
							if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CalculateEnergyCosts", iCID_Proj ), lCalculateEnergyCosts, 0, BEMP_Int, 0 /*ObjIdx*/, BEMO_User, osRunInfo.BEMProcIdx() ) && lCalculateEnergyCosts > 0)
							{	QString sCostMethod, sCostMethodProp, sCostProp, sEnergyUseProp, sEnergyCostProp, sEnergyCostOTherFuel;		long lTrackCost;		double fCost, fEnergyUse, fTotalCost=0;
								for (int iFuelType=0; iFuelType < 2; iFuelType++)	// Elec / Other
								{	sLogMsg.clear();
									lTrackCost = 0;
									int iFuel = iFuelType;
									switch (iFuelType)
									{	case  0:	sCostMethodProp = "ElecCostMethod";				sCostProp = "AvgElecCost";			lTrackCost = 1;
														if (iOrientNum < 1)
														{	sEnergyUseProp = QString( "%1ElecEnergy" ).arg( sEUPropNameBase );
															sEnergyCostProp = QString( "%1ElecCost" ).arg( sEUPropNameBase );
														}
														else
														{	sEnergyUseProp = QString( "%1ElecEnergyByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
															sEnergyCostProp = QString( "%1ElecCostByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
														}
													break;
										default:	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "TrackOTherFuel", iCID_Proj ), lTrackCost, 0, BEMP_Int, 0 /*ObjIdx*/, BEMO_User, osRunInfo.BEMProcIdx() ))
														sLogMsg = "  ProcessSimulationResults - Error retrieving Proj:TrackOTherFuel";
													else if (!BEMPX_GetString( BEMPX_GetDatabaseID( "EnergyCostOTherFuel", iCID_Proj ), sEnergyCostOTherFuel, FALSE, 0, -1, 0 /*ObjIdx*/, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ))
														sLogMsg = "  ProcessSimulationResults - Error retrieving Proj:EnergyCostOTherFuel";
													else if (lTrackCost)
													{	sCostMethodProp = "OtherFuelCostMethod";		sCostProp = "AvgOtherFuelCost";
														if (sEnergyCostOTherFuel.indexOf("Nat") >= 0 && sEnergyCostOTherFuel.indexOf("Gas") >= 0)
														{	iFuel = 1;
															if (iOrientNum < 1)
															{	sEnergyUseProp = QString( "%1NatGasEnergy" ).arg( sEUPropNameBase );
																sEnergyCostProp = QString(  "%1NatGasCost" ).arg( sEUPropNameBase );
															}
															else
															{	sEnergyUseProp = QString( "%1NatGasEnergyByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
																sEnergyCostProp = QString(  "%1NatGasCostByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
															}
														}
														else
														{	iFuel = 2;
															if (iOrientNum < 1)
															{	sEnergyUseProp = QString( "%1OtherEnergy" ).arg( sEUPropNameBase );
																sEnergyCostProp = QString(  "%1OtherCost" ).arg( sEUPropNameBase );
															}
															else
															{	sEnergyUseProp = QString( "%1OtherEnergyByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
																sEnergyCostProp = QString(  "%1OtherCostByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
															}
														}
													}	break;
									}
									if (lTrackCost) 
									{
										if (!BEMPX_GetString( BEMPX_GetDatabaseID( sCostMethodProp, iCID_Proj ), sCostMethod, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) || sCostMethod.isEmpty())
											sLogMsg = QString( "  ProcessSimulationResults - Error retrieving Proj:%1" ).arg( sCostMethodProp );
							//			else if (sCostMethod.compare("Average State Cost", Qt::CaseInsensitive))
							//				sLogMsg = QString( "  ProcessSimulationResults - Error - unrecognized Proj:%1 '%2'" ).arg( sCostMethodProp, sCostMethod );
										else if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sCostProp, iCID_Proj ), fCost, 0, BEMP_Flt, 0, BEMO_User, osRunInfo.BEMProcIdx() ))
											sLogMsg = QString( "  ProcessSimulationResults - Error retrieving '%1' EnergyUse:%2" ).arg( esEUMap_CECNonRes[iEUIdx].sEnduseName, sCostProp );
										else if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sEnergyUseProp, iCID_EnergyUse ), fEnergyUse, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
											sLogMsg = QString( "  ProcessSimulationResults - Error retrieving '%1' EnergyUse:%2" ).arg( esEUMap_CECNonRes[iEUIdx].sEnduseName, sEnergyUseProp );
										else
										{	// have cost & energy use - calc cost & set it
											switch (iFuel)
											{	case  0:		fCost = (((int) ((fCost * fEnergyUse                    ) + 0.5)) / 100.0);		break;	// elec     ¢/kWh * kWh / 100 = $
												case  1:		fCost = (((int) ((fCost * fEnergyUse             * 100.0) + 0.5)) / 100.0);		break;	// nat gas  $/therm * therms = $
												case  2:		fCost = (((int) ((fCost * fEnergyUse * 0.6674285 * 100.0) + 0.5)) / 100.0);		break;	// other    $/gallon * 0.6674285 gal/therm * therms = $
											}
											fTotalCost += fCost;
											BEMPX_SetBEMData( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), BEMP_Flt, &fCost, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										}
										if (!sLogMsg.isEmpty())
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}	}
								if (iOrientNum < 1)
									sEnergyCostProp = QString( "%1TotalCost" ).arg( sEUPropNameBase );
								else
									sEnergyCostProp = QString( "%1TotalCostByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), BEMP_Flt, &fTotalCost, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && osRunInfo.IsStdRun() && iOrientNum == 4)	// calculate final (average) costs for S901G & ECBC
								{
			// SAC 8/27/15 - SUM ALL COSTS INTO SINGLE/PREVIOUS PROPERTIES
									double fElecTot=0, fGasTot=0, fOthrTot=0, fElec, fGas, fOthr, fTot;
									fTotalCost = 0;
									for (int iOIdx=1; iOIdx<=4; iOIdx++)
									{
										sEnergyCostProp = QString( "StdElecCostByOrient[%1]" ).arg(   QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), fElec, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										sEnergyCostProp = QString( "StdNatGasCostByOrient[%1]" ).arg( QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), fGas , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										sEnergyCostProp = QString( "StdOtherCostByOrient[%1]" ).arg(  QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), fOthr, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										sEnergyCostProp = QString( "StdTotalCostByOrient[%1]" ).arg(  QString::number(iOIdx) );		BEMPX_GetFloat( BEMPX_GetDatabaseID( sEnergyCostProp, iCID_EnergyUse ), fTot , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										fElecTot += fElec;		fGasTot += fGas;		fOthrTot += fOthr;		fTotalCost += fTot;
									}
									fElecTot = (fElecTot/4.0);		fGasTot = (fGasTot/4.0);		fOthrTot = (fOthrTot/4.0);		fTotalCost = (fTotalCost/4.0);
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdElecCost",   iCID_EnergyUse ), BEMP_Flt, &fElecTot  , BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdNatGasCost", iCID_EnergyUse ), BEMP_Flt, &fGasTot   , BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdOtherCost",  iCID_EnergyUse ), BEMP_Flt, &fOthrTot  , BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "StdTotalCost",  iCID_EnergyUse ), BEMP_Flt, &fTotalCost, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								// calculate final result based on cost data only for S901G rules
									double fPropCost = 0;
									if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PropTotalCost", iCID_EnergyUse ), fPropCost, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									{	assert( FALSE );
									}
									else
									{	double fCompMarginReal = fTotalCost - fPropCost;																					fCompMarginReal;
										double fPctImproveReal = ((fTotalCost > 0 ? (fTotalCost - fPropCost) / fTotalCost : 0) * 100.0);		fPctImproveReal;
									
										double dStCost = RoundVal( fTotalCost, 0 );		// ensure margin results consistent w/ rounded values (dollars)
										double dPrCost = RoundVal( fPropCost , 0 );
										double fCompMargin = (dStCost - dPrCost);
										double fPctImprove = (dStCost > 0 ? ((dStCost - dPrCost) * 100.0 / dStCost) : 0.0);

										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse ), BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse ), BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										sPassFail = (fCompMargin > -0.001 /*>=0*/ ? "PASS" : "FAIL");
	
												sLogMsg = QString( "  PerfSim_E+ - Final Result: %1  -- compliance margin: %2 (%3%)" ).arg( sPassFail, QString::number(fCompMargin), QString::number(fPctImprove, 'f', 2) );
												BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}	}
							}
						}
					}
				}	
			}  // energy use totals for this run posted to BEMBase





//		// SAC 5/8/14 - added round of processing to ensure that compliance and overall sums are consistent w/ the reported decimal precision
//			if (osRunInfo.IsStdRun())
//			{	double faRunFuelSums[] = {};
//				iEUIdx = -1;
//				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
//				{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
//					int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
//					if (iEUObjIdx >= 0)
//					{
//			QString sEUPropNameBase = (osRunInfo.IsStdRun() ? "Std" : "Prop");
//						double fEUTot = 0, fVal, fTDVTot = 0;
//						for (iFl=0; iFl < OSF_NumFuels; iFl++)
//						{	sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
//							if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
//							{	assert( FALSE );
//							}
//							else if (fVal > 0)
//							{	if (iFl == 0)
//									fEUTot += (fVal * 3.41214 / fTotBldgFlrArea);				// kWh -> kBtu/SF
//								else
//									fEUTot += (fVal * 100.0   / fTotBldgFlrArea);				// therms -> kBtu/SF
//							}
//							fTDVTot += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];  // no unit conversion needed for TDV
//						}
//						sPropName = QString( "%1TotalEnergy" ).arg( sEUPropNameBase );
//						BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fEUTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );




/*

static inline double RoundVal( double dVal, int iDecPrec )
{	double dRetVal = 0.0;
	switch (iDecPrec)
	{	case -3 :	dRetVal = (double) ((int) ((fTDVTot  / 1000.0) + 0.5)) * 1000.0;		break;
		case -2 :	dRetVal = (double) ((int) ((fTDVTot  /  100.0) + 0.5)) *  100.0;		break;
		case -1 :	dRetVal = (double) ((int) ((fTDVTot  /   10.0) + 0.5)) *   10.0;		break;
		case  0 :	dRetVal = (double) ((int) ((fTDVTot          ) + 0.5))         ;		break;
		case  1 :	dRetVal = (double) ((int) ((fTDVTot  *   10.0) + 0.5)) /   10.0;		break;
		case  2 :	dRetVal = (double) ((int) ((fTDVTot  *  100.0) + 0.5)) /  100.0;		break;
		case  3 :	dRetVal = (double) ((int) ((fTDVTot  * 1000.0) + 0.5)) / 1000.0;		break;
		default :	assert( FALSE );		break;
	}
	return dRetVal;
}

				// SAC 5/8/14 - add local energy use SUMS that are consistent w/ reported decimal precision
typedef struct
{
   char*       sEnduseName;
   int         iaEndUseIdx[6];
   int         iSumIntoCompliance;
	double      daEnduseTotal[3];
	double      daTDVTotal[3];
} EndUseMap;

#define  NUM_T24_NRES_EndUses     12
#define  IDX_T24_NRES_EU_CompTot   7
#define  IDX_T24_NRES_EU_Total    11                                                                                                 // SumInto
static EndUseMap sEUMap[] =  // enduses...                                                                                               Compliance   daEnduseTotal    daTDVTotal
{	{  "Space Heating"      ,  OSEU_Heating,           OSEU_HtgCoils,         OSEU_Baseboard,    OSEU_HtRecov_Htg,  OSEU_Boilers,  -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Space Cooling"      ,  OSEU_Cooling,           OSEU_ClgCoils,         OSEU_HtRecov_Clg,        -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Indoor Fans"        ,  OSEU_Fans,                    -1,                    -1,                -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Heat Rejection"     ,  OSEU_HtReject,                -1,                    -1,                -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Pumps & Misc."      ,  OSEU_Pumps,             OSEU_HtRecov,          OSEU_Humid,              -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Domestic HW"        ,  OSEU_WaterSystems,            -1,                    -1,                -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Lighting"           ,  OSEU_IntLights_Reg,           -1,                    -1,                -1,               -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Compliance Total"   ,      -1,                       -1,                    -1,                -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Receptacle"         ,  OSEU_IntEquip_Recept,         -1,                    -1,                -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Process"            ,  OSEU_IntEquip_Process,  OSEU_IntEquip_Refrig,  OSEU_Refrig,             -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "Process Ltg"        ,  OSEU_IntLights_NonReg,        -1,                    -1,                -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  "TOTAL"              ,      -1,                       -1,                    -1,                -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
	{  NULL                 ,      -1,                       -1,                    -1,                -1,               -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   }  };
                                                                                                // FINAL enduse index must be '-1' for each record

const char* pszaEPlusFuelNames[] = {		"Electricity",    // OSF_Elec,    //  ((Electricity)(Electricity))
														"NaturalGas" ,    // OSF_Gas,     //  ((Gas)(Natural Gas))        
														"OtherFuel"   };  // OSF_Other,   //  ((OtherFuel)(Other Fuel))   

  <EnergyUse>
    <Name>Space Heating</Name>
    <EnduseName>Space Heating</EnduseName>
    <ProposedTDV>8.22153</ProposedTDV>
    <StandardTDV>8.34999</StandardTDV>
    <CompMarginTDV>0.128458</CompMarginTDV>
    <PctImproveTDV>1.53842</PctImproveTDV>

    <PropElecEnergy>0</PropElecEnergy>
    <PropNatGasEnergy>239.092</PropNatGasEnergy>
    <PropOtherEnergy>0</PropOtherEnergy>
    <PropTotalEnergy>4.34551</PropTotalEnergy>

    <StdElecEnergy>0</StdElecEnergy>
    <StdNatGasEnergy>242.882</StdNatGasEnergy>
    <StdOtherEnergy>0</StdOtherEnergy>
    <StdTotalEnergy>4.41439</StdTotalEnergy>

    <PropElecTDV>0</PropElecTDV>
    <PropNatGasTDV>8.22153</PropNatGasTDV>
    <PropOtherTDV>0</PropOtherTDV>

    <StdElecTDV>0</StdElecTDV>
    <StdNatGasTDV>8.34999</StdNatGasTDV>
    <StdOtherTDV>0</StdOtherTDV>
  </EnergyUse>

*/	





			if (iCID_EUseSummary > 0 && fTotBldgFlrArea > 0)
			{						if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Posting results to BEMBase", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				if (BEMPX_GetNumObjects( iCID_EUseSummary, BEMO_User, osRunInfo.BEMProcIdx() ) < 1)
				{	BEMPX_CreateObject( iCID_EUseSummary, NULL /*szName*/, NULL /*pPar*/, BEMO_User, true /*bDfltPar*/, true /*bAutoCr8*/, osRunInfo.BEMProcIdx() );		long l0 = 0;
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded                                 , BEMP_Int, &l0, BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_Int, &l0, BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
				if (BEMPX_GetNumObjects( iCID_EUseSummary, BEMO_User, osRunInfo.BEMProcIdx() ) > 0)
				{
						if (!sPassFail.isEmpty())
						{	if (osRunInfo.NumQuickAnalysisPeriods() > 0)		// SAC 11/11/14 - if performing QuickAnalysis, do NOT store final PASS/FAIL string to database
								sPassFail = " ";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PassFail", iCID_EUseSummary ), BEMP_QStr, (void*) &sPassFail, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							// SAC 6/8/16 - store new PctSav* values & labels (tic #1735)
							double fRndTDVTotPctSav     = (dRndStdTDVTot     > 0 ? (dRndTDVTotMargin     * 100.0 / dRndStdTDVTot    ) : 0);
							double fRndTDVCompTotPctSav = (dRndStdTDVCompTot > 0 ? (dRndTDVCompTotMargin * 100.0 / dRndStdTDVCompTot) : 0);
							QString sRndTDVTotPctSav     = "-";
							QString sRndTDVCompTotPctSav = "-";
							if (osRunInfo.NumQuickAnalysisPeriods() < 1)
							{	if (fRndTDVTotPctSav <= -0.0001 || fRndTDVTotPctSav >= 0.0001)
									sRndTDVTotPctSav = QString::number(fRndTDVTotPctSav, 'f', 1);
								if (fRndTDVCompTotPctSav <= -0.0001 || fRndTDVCompTotPctSav >= 0.0001)
									sRndTDVCompTotPctSav = QString::number(fRndTDVCompTotPctSav, 'f', 1);
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsTDV",    iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVTotPctSav    , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsCmpTDV", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVCompTotPctSav, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavTDVLbl"   , iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVTotPctSav    , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavCmpTDVLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVCompTotPctSav, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
	
				// GENERATION & STORAGE OF SIMULATION STATUS MESSAGE
						int iSimIdx = (!osRunInfo.IsStdRun() ? 0 : (osRunInfo.StoreHourlyResults() ? 2 : 1));
					//	sLogMsg = (osWrap.GetBool_SimCompleted() ? "Completed" : "")
						sLogMsg = (osWrap.GetBool_SimCompletedSuccessfully( osRunInfo.OSRunIdx() ) ? "Successful" : "Unsuccessful");
						int iNumWarn    = osWrap.GetNum_Warnings(     osRunInfo.OSRunIdx() );
						int iNumSverErr = osWrap.GetNum_SevereErrors( osRunInfo.OSRunIdx() );
						int iNumFatlErr = osWrap.GetNum_FatalErrors(  osRunInfo.OSRunIdx() );
						int iErrsWritten = 0;
						if (iNumFatlErr > 0)
						{	sLogMsg += " (";
							sTemp = QString( "%1 fatal err%2" ).arg( QString::number(iNumFatlErr), (iNumFatlErr > 1 ? "ors" : "or") );			iErrsWritten += iNumFatlErr;
							sLogMsg += sTemp;
						}
						if (iNumSverErr > 0)
						{	sLogMsg += (iErrsWritten == 0 ? " (" : ", ");
							sTemp = QString( "%1 severe err%2" ).arg( QString::number(iNumSverErr), (iNumSverErr > 1 ? "ors" : "or") );		iErrsWritten += iNumSverErr;
							sLogMsg += sTemp;
						}
						if (iNumWarn > 0)
						{	sLogMsg += (iErrsWritten == 0 ? " (" : ", ");
							sTemp = QString( "%1 warni%2" ).arg( QString::number(iNumWarn), (iNumWarn > 1 ? "ngs" : "ng") );				iErrsWritten += iNumWarn;
							sLogMsg += sTemp;
						}
						if (iErrsWritten > 0)
							sLogMsg += ")";
					//	QString sTempDbgMsg;		sTempDbgMsg = QString( "Setting EUseSummary:SimSummary[%1] (%2) -> %3" ).arg( QString::number(iSimIdx+1), QString::number(BEMPX_GetDatabaseID( "SimSummary", iCID_EUseSummary ) + iSimIdx), sLogMsg );
					//	BEMMessageBox( sTempDbgMsg );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "SimSummary", iCID_EUseSummary ) + iSimIdx, BEMP_QStr, (void*) &sLogMsg, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
													if (bVerbose)
													{	sLogMsg = "  PerfSim_E+ - " + sLogMsg;
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
					//	QString sSimInfo;
					//	std::string	sSimErrPathFile = osWrap.Get_SimErrPathFile();
					//	sSimInfo.sprintf( "ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s",
					//							sSimErrPathFile.c_str(), osWrap.GetNum_Warnings(), osWrap.GetNum_SevereErrors(), osWrap.GetNum_FatalErrors(),
					//							(osWrap.GetBool_SimCompleted() ? "TRUE" : "FALSE"), (osWrap.GetBool_SimCompletedSuccessfully() ? "TRUE" : "FALSE") );
					//	BEMMessageBox( sSimInfo, NULL, 2 /*warning*/ );
					////	std::string sDbgMsg = boost::str( boost::format("%s / dot @ %d / space @ %d") % sSDDXMLFile % iLastDot % iLastSpc );
					////	BEMMessageBox( sDbgMsg.c_str(), NULL, 2 /*warning*/ );
					////	sDbgMsg = boost::str( boost::format("ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s")
					////									% sErrPathFile % pData->saSimWarnings.size() % pData->saSimSevereErrors.size() % pData->saSimFatalErrors.size()
					////									% (errorFile.completed() ? "TRUE" : "FALSE") % (errorFile.completedSuccessfully() ? "TRUE" : "FALSE") );
					////	BEMMessageBox( sDbgMsg.c_str(), NULL, 2 /*warning*/ );
	
	
									if (bVerbose)
										LogEnergyPlusMessages( &osWrap, &osRunInfo );
	
					if (!osRunInfo.IsStdRun())
					{
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[2]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[3]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[4]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[1]", iCID_EUseSummary ), BEMP_Str, "End Use"      , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[2]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[3]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					// SAC 11/17/14 - modified label to include TDV in title following Design and switch units from kTDV/.. to kBtu/..
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[4]", iCID_EUseSummary ), BEMP_Str, "Design TDV"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[2]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[3]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[4]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)", BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
						else if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[2]", iCID_EUseSummary ), BEMP_Str, "Electricity"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[3]", iCID_EUseSummary ), BEMP_Str, "Natural Gas"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							QString sOtherFuelLabel;
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EnergyCostOtherFuelLabel" ), sOtherFuelLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) || sOtherFuelLabel.length() < 3 ||
									!sOtherFuelLabel.compare("Natural Gas", Qt::CaseInsensitive))		// SAC 10/28/15 - prevent double reporting of 'Natural Gas'
								sOtherFuelLabel = "Other Fuel";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[4]", iCID_EUseSummary ), BEMP_QStr, (void*) &sOtherFuelLabel, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[2]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[3]", iCID_EUseSummary ), BEMP_Str, "Site (therms)", BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[4]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
						}
		
						iEUIdx = -1;
						while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
						{
							sPropName = QString( "Enduse%1[1]" ).arg( QString::number(iEUIdx+1) );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_Str, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
					}
					else
					{
						if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[5]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[6]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[7]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[5]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[6]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[7]", iCID_EUseSummary ), BEMP_Str, "Design TDV"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[5]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[6]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[7]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)", BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[8]", iCID_EUseSummary ), BEMP_Str, "Compliance"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[8]", iCID_EUseSummary ), BEMP_Str, "TDV Margin"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[8]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)", BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
						else if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[5]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[6]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[7]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[5]", iCID_EUseSummary ), BEMP_Str, "Electricity"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[6]", iCID_EUseSummary ), BEMP_Str, "Natural Gas"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							QString sOtherFuelLabel;
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EnergyCostOtherFuelLabel" ), sOtherFuelLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) || sOtherFuelLabel.length() < 3 ||
									!sOtherFuelLabel.compare("Natural Gas", Qt::CaseInsensitive))		// SAC 10/28/15 - prevent double reporting of 'Natural Gas'
								sOtherFuelLabel = "Other Fuel";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[7]", iCID_EUseSummary ), BEMP_QStr, (void*) &sOtherFuelLabel, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[5]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[6]", iCID_EUseSummary ), BEMP_Str, "Site (therms)", BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[7]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[8]", iCID_EUseSummary ), BEMP_Str, "Energy"       , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[8]", iCID_EUseSummary ), BEMP_Str, "Cost"         , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[8]", iCID_EUseSummary ), BEMP_Str, "Summary"      , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
					}
	
			// includes TDV & comp margin retrieval & setting (if present in data model)
					QString sPropName2, sResultVal;
					double dRndResSum[3] = { 0.0,0.0,0.0 };
					iEUIdx = -1;
					while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
					{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
						int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
						if (iEUObjIdx >= 0)
						{	double fVal[4] = {0,0,0,0};
							for (iFl=0; iFl < OSF_NumFuels; iFl++)
							{
								sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[iFl], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[iFl] = 0;
							}
							if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs ONLY
							{	fVal[1] += fVal[2];   fVal[2] = 0;	  // sum NatGas & Other fuel together into fVal[1] and zero out fVal[2]
								sPropName = QString( "%1TDV" ).arg( (!osRunInfo.IsStdRun() ? "Proposed" : "Standard") );
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[2], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[2] = 0;
							}
							//int iStartCol = (iEUIdx==IDX_T24_NRES_EU_CompTot ? 2 : 0);
							double dCol1Div = (osRunInfo.CodeType() == CT_T24N ? 10.0 :  1.0);		// SAC 10/28/15 - T24N fuel use therms -> MBtu
							double dCol2Div = (osRunInfo.CodeType() == CT_T24N ?  1.0 : 10.0);		// SAC 10/28/15 - S901G other fuel use therms -> MBtu
							for (int iCol=0; iCol<3; iCol++)
							{
								sPropName = QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(iCol+(osRunInfo.IsStdRun() ? 5 : 2)) );
								double dValToDisplay = fVal[iCol] /	(iCol==0 ? 1000.0 : (iCol==1 ? dCol1Div : (iCol==2 ? dCol2Div : 1.0))  );  // (iCol==1 ? 1.0 : 1000.0 );  // (iCol==2 ? 1 : 1000);
								//	double dMinValToDisplay = 				(iCol==1 ? 0.5    : 0.05 );
								int iDecPrec;
								if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs ONLY
									//iDecPrec = 		1;		// SAC 10/28/15 - ALL results now #.# since converting fuel use from therms to MBtu - was:  (iCol==1 ? 0      : 1    );
									iDecPrec = 		(iCol==2 ? 2 : 1 );		// SAC 6/8/16 - T24 TDV results now reported w/ 2 decimal places (tic #1735)
								else
									iDecPrec = 		(iCol==1 ? 0 : 1 );		// SAC 10/28/15 - S901G Other fuel use therms -> MBtu  was: (iCol==0 ? 1 : 0 );
					// SAC 5/8/14 - revise display of sums to reflect
								BOOL bTrueZero = FALSE;
								if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total)
								{	bTrueZero = WithinMargin( dValToDisplay, 0.0, 0.0001 );
									dRndResSum[iCol] += RoundVal( dValToDisplay, iDecPrec );
								}
								else
									dValToDisplay = dRndResSum[iCol];  // sum of ROUNDED values

								//	if (dValToDisplay >= dMinValToDisplay)
	                     //	{	sResultVal = BEMPX_FloatToString( dValToDisplay, iDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
								//		BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								//	}
								//	else
								//		BEMPX_DefaultProperty( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), iError, -1, BEMO_User, osRunInfo.BEMProcIdx() );
					// SAC 5/8/14 - switched display to '--' for TRUE zeroes or values for anything else (that may even display as a zero)
								if (bTrueZero)
									sResultVal = "--";
								else
									sResultVal = BEMPX_FloatToString( dValToDisplay, iDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}

							// SAC 10/9/16 - store demand results
								sPropName = QString( "%1ElecDemand" ).arg( sEUPropNameBase );
								double dEDem = 0.0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), dEDem, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									dEDem = 0.0;
								sPropName = QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number((osRunInfo.IsStdRun() ? 10 : 9)) );
								if (WithinMargin( dEDem, 0.0, 0.001 ))
									sResultVal = "--";
								else
									sResultVal = BEMPX_FloatToString( dEDem, 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								if (iEUIdx == IDX_T24_NRES_EU_Total && osRunInfo.IsStdRun())
								{	// calculate and store kW difference
									sPropName = QString( "PropElecDemand" );
									double dPropEDem = 0.0;
									if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), dPropEDem, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
										dPropEDem = 0.0;
									sPropName = QString( "MarginkW" );
									dEDem = RoundVal( dEDem, 1 ) - RoundVal( dPropEDem, 1 );
									//if (WithinMargin( dEDem, 0.0, 0.001 ))
									//	sResultVal = "--";
									//else
									//	sResultVal = BEMPX_FloatToString( dEDem, 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									//BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_Flt, (void*) &dEDem, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
	
						// lastly, populate Compliance Margin column
							if (osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun() && iEUIdx <= IDX_T24_NRES_EU_CompTot)
							{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse ), fVal[3], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[3] = 0;
								sPropName = QString( "Enduse%1[8]" ).arg( QString::number(iEUIdx+1) );
								//	if (fVal[3] >= 0.05 || fVal[3] <= -0.05)
	                     //	{	sResultVal = BEMPX_FloatToString( fVal[3], 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
								//		BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								//	}
								//	else
								//		BEMPX_DefaultProperty( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), iError, -1, BEMO_User, osRunInfo.BEMProcIdx() );
					// SAC 5/8/14 - switched display to '--' for TRUE zeroes or values for anything else (that may even display as a zero)
								if (WithinMargin( fVal[3], 0.0, 0.0049 ))		// SAC 6/8/16 - increase margin around 0 that will display as '--' from 0.0001 to 0.0049
									sResultVal = "--";
	                     else
									sResultVal = BEMPX_FloatToString( fVal[3], 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );		// SAC 6/8/16 - 1 -> 2 decimal places (tic #1735)
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
							else if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && osRunInfo.IsStdRun() && iEUIdx == IDX_T24_NRES_EU_Total)
							{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PropTotalCost", iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[1] = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "StdTotalCost", iCID_EnergyUse ), fVal[2], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[2] = 0;
								if (fVal[1] < 0.1 || fVal[2] < 0.1)
								{	sResultVal = "--";
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse1[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse2[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
								else
								{	fVal[3] = (int( fVal[2] + 0.5 ) - int( fVal[1] + 0.5 ));
									sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse1[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									sResultVal = BEMPX_FloatToString( fVal[2], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse2[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									sResultVal = BEMPX_FloatToString( fVal[3], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
							}

						// special processing for S901G - store energy COSTS in the IDX_T24_NRES_EU_CompTot bucket (Enduse8[2-7])
							if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && iEUIdx == IDX_T24_NRES_EU_Total)
							{	sResultVal = "Energy Costs";
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[1]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								sPropName = QString( "%1ElecCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 5 : 2) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								sPropName = QString( "%1NatGasCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 6 : 3) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								sPropName = QString( "%1OtherCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 7 : 4) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}	// end of  if (iEUObjIdx >= 0)
					}	// end of  while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				}
			}	// end of  if (iCID_EUseSummary > 0 && fTotBldgFlrArea > 0)
		}	// end of  if (osRunInfo.StoreHourlyResults())

	
		if (osRunInfo.SimulateModel() && iRetVal == 0)
		{
			QString sZoneUMLHSummary, sTemp;
			long lDBID_ThrmlZn_ClgUnmetLdHrs = BEMPX_GetDatabaseID( "ClgUnmetLdHrs",  osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_ClgUnmetLdHrs > 0 );
			long lDBID_ThrmlZn_HtgUnmetLdHrs = BEMPX_GetDatabaseID( "HtgUnmetLdHrs",  osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_HtgUnmetLdHrs > 0 );
			long lDBID_ThrmlZn_ClgDsgnLd     = BEMPX_GetDatabaseID( "ClgDsgnLd",      osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_ClgDsgnLd     > 0 );    // "Btuh", 
			long lDBID_ThrmlZn_HtgDsgnLd     = BEMPX_GetDatabaseID( "HtgDsgnLd",      osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_HtgDsgnLd     > 0 );    // "Btuh", 
			long lDBID_ThrmlZn_ClgDsgnFlow   = BEMPX_GetDatabaseID( "ClgDsgnFlowSim", osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_ClgDsgnFlow   > 0 );    // "cfm",    - SAC 1/18/14 - added trailing "Sim" to prop names (GC issue #389)
			long lDBID_ThrmlZn_HtgDsgnFlow   = BEMPX_GetDatabaseID( "HtgDsgnFlowSim", osRunInfo.ClassID( ROT_Zone ) );			assert( lDBID_ThrmlZn_HtgDsgnFlow   > 0 );    // "cfm",  
									if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Pulling UMLH & sizing results from OSWrap", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (osRunInfo.NumObjects( ROT_Zone ) > 0 && lDBID_ThrmlZn_ClgUnmetLdHrs > 0 && lDBID_ThrmlZn_HtgUnmetLdHrs > 0 &&
					lDBID_ThrmlZn_ClgDsgnLd > 0 && lDBID_ThrmlZn_HtgDsgnLd > 0 && lDBID_ThrmlZn_ClgDsgnFlow > 0 && lDBID_ThrmlZn_HtgDsgnFlow > 0 )
			{	//double fZnUnmetLdClg, fZnUnmetLdHtg;
				double faZnResults[6] = {0,0,0,0,0,0};
		// SAC 1/11/14 - units -> IP  (2 already in IP, the other needing conversion from SI)
		//		double faZnResMult[6] = {1, 1 /*hr*/,	3.412142F, 3.412142F, /*W->Btuh*/		2119, 2119 /*m3/s->cfm*/ };
				double faZnResMult[6] = {1, 1 /*hr*/,	1, 1, /*Btuh*/		1, 1 /*cfm*/ };
				long laDBID[6] = { lDBID_ThrmlZn_ClgUnmetLdHrs, lDBID_ThrmlZn_HtgUnmetLdHrs, lDBID_ThrmlZn_ClgDsgnLd, lDBID_ThrmlZn_HtgDsgnLd, lDBID_ThrmlZn_ClgDsgnFlow, lDBID_ThrmlZn_HtgDsgnFlow };
				assert( osRunInfo.NumResultObjects( ROT_Zone ) == osRunInfo.NumObjects( ROT_Zone ) );	// otherwise, one or more zones missing from UMLH results
				bool bMaxUMLHLenMet = false;
				for (int iZn=0; iZn < osRunInfo.NumObjects( ROT_Zone ); iZn++)
				{
					//fZnUnmetLdClg = osWrap.GetResult_ZoneUMLHClg( iZn );								assert( fZnUnmetLdClg >= 0.0 );
					//fZnUnmetLdHtg = osWrap.GetResult_ZoneUMLHHtg( iZn );								assert( fZnUnmetLdHtg >= 0.0 );
					int iNumRes = osWrap.GetResult_Zone( osRunInfo.OSRunIdx(), iZn, faZnResults, 6 );									assert( iNumRes==6 );
	
	// ADD ERRROR RETURN
	
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					//BEMPX_SetBEMData( lDBID_ThrmlZn_ClgUnmetLdHrs, BEMP_Flt, &fZnUnmetLdClg, BEMO_User, iZn );
					//BEMPX_SetBEMData( lDBID_ThrmlZn_HtgUnmetLdHrs, BEMP_Flt, &fZnUnmetLdHtg, BEMO_User, iZn );
					for (int ir=0; ir<6; ir++)
					{	faZnResults[ir] *= faZnResMult[ir];
						BEMPX_SetBEMData( laDBID[ir], BEMP_Flt, &faZnResults[ir], BEMO_User, iZn, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					}
					if (!bMaxUMLHLenMet)		// SAC 12/17/13 - prevent ZoneUMLH string from exceeding TextIO string length max - which in turn causes errors on File-Open
					{	if (!sZoneUMLHSummary.isEmpty())	// SAC 5/31/14 - revised newline writing to prevent trailing \r\n @ end of string
							sZoneUMLHSummary += "\r\n";
						if ((sZoneUMLHSummary.length() + 120) < TextioMaxLine)	// SAC 5/31/14 - increased 100->200 as max TextIO string len still being exceeded
							sTemp = QString("clg: %1  htg: %2  '%3'" ).arg( QString::number(faZnResults[0], 'f', 0), QString::number(faZnResults[1], 'f', 0), 
															(osRunInfo.NumResultObjects( ROT_Zone )==osRunInfo.NumObjects( ROT_Zone ) ? osRunInfo.ObjectName( ROT_Zone, iZn ) : "unknown") );
						else
						{	sTemp = "... and additional zone(s)";
							bMaxUMLHLenMet = true;
						}
						sZoneUMLHSummary += sTemp;
					}
				}
	
			// post zone UMLH summary to BEMBase  -  ONLY FOR runs where hourly results are stored
				if (osRunInfo.StoreHourlyResults() && lDBID_EUseSummary_ZoneUMLHs > 0 && lDBID_EUseSummary_ZoneUMLHsLoaded > 0 && BEMPX_GetNumObjects( iCID_EUseSummary, BEMO_User, osRunInfo.BEMProcIdx() ) > 0 && !sZoneUMLHSummary.isEmpty())
				{	long l1 = 1;
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_Int,                       &l1,                BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	#ifdef _DEBUG
	//	QString sDbgMsg;	sDbgMsg = QString( "Posting UMLHs data to BEMBase:\n%1" ).arg( sZoneUMLHSummary );	::MessageBox( NULL, sDbgMsg, NULL, MB_ICONEXCLAMATION );
	#endif
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHs       + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_QStr, (void*) &sZoneUMLHSummary, BEMO_User, 0, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
			long lDBID_Fan_FlowCap = BEMPX_GetDatabaseID( "FlowCapSim", osRunInfo.ClassID( ROT_Fan ) );			assert( lDBID_Fan_FlowCap > 0 );
			if (osRunInfo.NumObjects( ROT_Fan ) > 0 && lDBID_Fan_FlowCap > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_Fan )==osRunInfo.NumObjects( ROT_Fan ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP
		//		double faResMult[2] = { 2119, 2119 /*m3/s->cfm*/ };
				double faResMult[2] = { 1, 1 /*cfm*/ };
				//long laDBID[2] = { lDBID_Fan_FlowCap, lDBID_Fan_FlowCap };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_Fan ); iObj++)
				{
					int iNumRes = osWrap.GetResult_Fan( osRunInfo.OSRunIdx(), iObj, faResults, 1 );									assert( iNumRes==1 );
					faResults[0] *= faResMult[0];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_Fan_FlowCap, BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
			long lDBID_CoilClg_CapTotGrossRtd     = BEMPX_GetDatabaseID( "CapTotGrossRtdSim" , osRunInfo.ClassID( ROT_CoilClg ) );			assert( lDBID_CoilClg_CapTotGrossRtd     > 0 );
			long lDBID_CoilClg_CapSensGrossRtd    = BEMPX_GetDatabaseID( "CapSensGrossRtdSim", osRunInfo.ClassID( ROT_CoilClg ) );			assert( lDBID_CoilClg_CapSensGrossRtd    > 0 );
	//		long lDBID_CoilClg_FluidLdDsgn        = BEMPX_GetDatabaseID( "FluidLdDsgn"       , osRunInfo.ClassID( ROT_CoilClg ) );			assert( lDBID_CoilClg_FluidLdDsgn        > 0 );		// SAC 9/5/13
			long lDBID_CoilClg_FluidFlowRtDsgnSim = BEMPX_GetDatabaseID( "FluidFlowRtDsgnSim", osRunInfo.ClassID( ROT_CoilClg ) );			assert( lDBID_CoilClg_FluidFlowRtDsgnSim > 0 );		// SAC 11/26/13
	//		if (iNumCoilClgs > 0 && lDBID_CoilClg_CapTotGrossRtd > 0 && lDBID_CoilClg_CapSensGrossRtd > 0 && lDBID_CoilClg_FluidLdDsgn > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			if (osRunInfo.NumObjects( ROT_CoilClg ) > 0 && lDBID_CoilClg_CapTotGrossRtd > 0 && lDBID_CoilClg_CapSensGrossRtd > 0 && lDBID_CoilClg_FluidFlowRtDsgnSim > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_CoilClg )==osRunInfo.NumObjects( ROT_CoilClg ) );
				double faResults[3] = {0,0,0};
		// SAC 1/11/14 - units -> IP  (2 already in IP, the other needing conversion from SI)
		//		double faResMult[3] = { 3.412142F, 3.412142F /*W->Btuh*/,  15852.0F /*m3/s->gpm*/ };
				double faResMult[3] = { 1, 1 /*Btuh*/,  15852.0F /*m3/s->gpm*/ };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_CoilClg ); iObj++)
				{
					int iNumRes = osWrap.GetResult_CoilClg( osRunInfo.OSRunIdx(), iObj, faResults, 3 );									assert( iNumRes==3 );
					faResults[0] *= faResMult[0];			faResults[1] *= faResMult[1];       faResults[2] *= faResMult[2];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_CoilClg_CapTotGrossRtd    , BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					BEMPX_SetBEMData( lDBID_CoilClg_CapSensGrossRtd   , BEMP_Flt, &faResults[1], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	//				BEMPX_SetBEMData( lDBID_CoilClg_FluidLdDsgn       , BEMP_Flt, &faResults[2], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					BEMPX_SetBEMData( lDBID_CoilClg_FluidFlowRtDsgnSim, BEMP_Flt, &faResults[2], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
			long lDBID_CoilHtg_CapTotGrossRtd     = BEMPX_GetDatabaseID( "CapTotGrossRtdSim" , osRunInfo.ClassID( ROT_CoilHtg ) );			assert( lDBID_CoilHtg_CapTotGrossRtd     > 0 );
	//		long lDBID_CoilHtg_FluidLdDsgn        = BEMPX_GetDatabaseID( "FluidLdDsgn"       , osRunInfo.ClassID( ROT_CoilHtg ) );			assert( lDBID_CoilHtg_FluidLdDsgn        > 0 );	// SAC 9/5/13
			long lDBID_CoilHtg_FluidFlowRtDsgnSim = BEMPX_GetDatabaseID( "FluidFlowRtDsgnSim", osRunInfo.ClassID( ROT_CoilHtg ) );			assert( lDBID_CoilHtg_FluidFlowRtDsgnSim > 0 );	// SAC 11/26/13
	//		if (iNumCoilHtgs > 0 && lDBID_CoilHtg_CapTotGrossRtd > 0 && lDBID_CoilHtg_FluidLdDsgn > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			if (osRunInfo.NumObjects( ROT_CoilHtg ) > 0 && lDBID_CoilHtg_CapTotGrossRtd > 0 && lDBID_CoilHtg_FluidFlowRtDsgnSim > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_CoilHtg )==osRunInfo.NumObjects( ROT_CoilHtg ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP  (1 already in IP, the other needing conversion from SI)
		//		double faResMult[2] = { 3.412142F /*W->Btuh*/,  15852.0F /*m3/s->gpm*/ };
				double faResMult[2] = { 1 /*Btuh*/,  15852.0F /*m3/s->gpm*/ };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_CoilHtg ); iObj++)
				{
					int iNumRes = osWrap.GetResult_CoilHtg( osRunInfo.OSRunIdx(), iObj, faResults, 2 );									assert( iNumRes==2 );
					faResults[0] *= faResMult[0];			faResults[1] *= faResMult[1];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_CoilHtg_CapTotGrossRtd    , BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	//				BEMPX_SetBEMData( lDBID_CoilHtg_FluidLdDsgn       , BEMP_Flt, &faResults[1], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					BEMPX_SetBEMData( lDBID_CoilHtg_FluidFlowRtDsgnSim, BEMP_Flt, &faResults[1], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
		// SAC 8/27/13 - added Blr, Chlr, HtRej & Pump results
			long lDBID_Blr_CapRtd = BEMPX_GetDatabaseID( "CapRtdSim", osRunInfo.ClassID( ROT_Blr ) );								assert( lDBID_Blr_CapRtd > 0 );
			if (osRunInfo.NumObjects( ROT_Blr ) > 0 && lDBID_Blr_CapRtd > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_Blr )==osRunInfo.NumObjects( ROT_Blr ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP  (no change - not from TabularDataWithStrings)
				double faResMult[2] = { 3.412142F, 3.412142F,/*W->Btuh*/ };
				//long laDBID[2] = { lDBID_Blr_CapRtd, 0 };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_Blr ); iObj++)
				{	int iNumRes = osWrap.GetResult_Blr( osRunInfo.OSRunIdx(), iObj, faResults, 1 );									assert( iNumRes==1 );
					faResults[0] *= faResMult[0];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_Blr_CapRtd, BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
			long lDBID_Chlr_CapRtd = BEMPX_GetDatabaseID( "CapRtdSim", osRunInfo.ClassID( ROT_Chlr ) );								assert( lDBID_Chlr_CapRtd > 0 );
			if (osRunInfo.NumObjects( ROT_Chlr ) > 0 && lDBID_Chlr_CapRtd > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_Chlr )==osRunInfo.NumObjects( ROT_Chlr ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP  (no change - not from TabularDataWithStrings)
				double faResMult[2] = { 3.412142F, 3.412142F,/*W->Btuh*/ };
				//long laDBID[2] = { lDBID_Chlr_CapRtd, 0 };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_Chlr ); iObj++)
				{	int iNumRes = osWrap.GetResult_Chlr( osRunInfo.OSRunIdx(), iObj, faResults, 1 );									assert( iNumRes==1 );
					faResults[0] *= faResMult[0];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_Chlr_CapRtd, BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}

			long lDBID_HtRej_CapRtd = BEMPX_GetDatabaseID( "CapRtdSim", osRunInfo.ClassID( ROT_HtRej ) );							assert( lDBID_HtRej_CapRtd > 0 );
			if (osRunInfo.NumObjects( ROT_HtRej ) > 0 && lDBID_HtRej_CapRtd > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_HtRej )==osRunInfo.NumObjects( ROT_HtRej ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP  (no change - not from TabularDataWithStrings)
				double faResMult[2] = { 3.412142F, 3.412142F,/*W->Btuh*/ };
				//long laDBID[2] = { lDBID_HtRej_CapRtd, 0 };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_HtRej ); iObj++)
				{	int iNumRes = osWrap.GetResult_HtRej( osRunInfo.OSRunIdx(), iObj, faResults, 1 );									assert( iNumRes==1 );
					faResults[0] *= faResMult[0];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_HtRej_CapRtd, BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
	
			long lDBID_Pump_FlowCap = BEMPX_GetDatabaseID( "FlowCapSim", osRunInfo.ClassID( ROT_Pump ) );							assert( lDBID_Pump_FlowCap > 0 );
			if (osRunInfo.NumObjects( ROT_Pump ) > 0 && lDBID_Pump_FlowCap > 0 && osRunInfo.PostEquipCapsToBEMBase())	// SAC 9/10/13 - only post equipment sizing results to BEMBase when specified
			{	assert( osRunInfo.NumResultObjects( ROT_Pump )==osRunInfo.NumObjects( ROT_Pump ) );
				double faResults[2] = {0,0};
		// SAC 1/11/14 - units -> IP
		//		double faResMult[2] = { 15852, 15852, /* m3/s -> gpm */ };
				double faResMult[2] = { 1, 1, /* gpm -> gpm */ };
				//long laDBID[2] = { lDBID_Pump_FlowCap, 0 };
				for (int iObj=0; iObj < osRunInfo.NumObjects( ROT_Pump ); iObj++)
				{	int iNumRes = osWrap.GetResult_Pump( osRunInfo.OSRunIdx(), iObj, faResults, 1 );									assert( iNumRes==1 );
					faResults[0] *= faResMult[0];
	      	// set data to BEMBase regardless of whether the return value is valid (??)
					BEMPX_SetBEMData( lDBID_Pump_FlowCap, BEMP_Flt, &faResults[0], BEMO_User, iObj, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
			}
		}

	// SAC 4/11/16 - implemented new SimOutputVariablesToCSV feature to make simulation results more accessible (csv vs. sql)
		if (osRunInfo.SimulateModel() && iRetVal == 0 && osRunInfo.SimOutVarsCSV())
		{	std::string sEPlusProcDir, sRVEexeFrom, sRVEexeTo, sRVErviFrom, sRVErviTo, sEPlusESOfile, sWarnMsg;
			sRVEexeFrom		= boost::str( boost::format( "%sReadVarsESO.exe" ) % pszEPlusPath );
			sRVErviFrom		= boost::str( boost::format( "%sSimOutVarsToCSV.rvi" ) % pszSimProcessDir );
			bool bDirChangedToEPlus = false;
			if (!FileExists( sRVEexeFrom.c_str() ))
				sWarnMsg = boost::str( boost::format( "Warning:  SimOutVarsToCSV action bypassed due to missing file:  %s" ) % sRVEexeFrom );
			else if (!FileExists( sRVErviFrom.c_str() ))
				sWarnMsg = boost::str( boost::format( "Warning:  SimOutVarsToCSV action bypassed due to missing file:  %s" ) % sRVErviFrom );
			else
			{	sEPlusProcDir = boost::str( boost::format( "%s%s\\EnergyPlus\\"    ) % pszSimProcessDir % osRunInfo.RunID().toLocal8Bit().constData() );
				sRVEexeTo     = boost::str( boost::format( "%sReadVarsESO.exe"     ) % sEPlusProcDir );
				sRVErviTo     = boost::str( boost::format( "%sSimOutVarsToCSV.rvi" ) % sEPlusProcDir );
				if (!CopyFile( sRVEexeFrom.c_str(), sRVEexeTo.c_str(), FALSE ))
				{	assert( FALSE );
					sWarnMsg = boost::str( boost::format( "Warning:  SimOutVarsToCSV action bypassed due to error copying '%s' to '%s'" ) % sRVEexeFrom % sRVEexeTo );
				}
				if (!CopyFile( sRVErviFrom.c_str(), sRVErviTo.c_str(), FALSE ))
				{	assert( FALSE );
					sWarnMsg = boost::str( boost::format( "Warning:  SimOutVarsToCSV action bypassed due to error copying '%s' to '%s'" ) % sRVErviFrom % sRVErviTo );
				}
				else
				{	QString sSimOutVarsFreq;
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SimVarsInterval" ), sSimOutVarsFreq, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
					if (!sSimOutVarsFreq.isEmpty() && (sSimOutVarsFreq.compare("Monthly", Qt::CaseInsensitive)==0 || sSimOutVarsFreq.compare("Timestep" , Qt::CaseInsensitive)==0 || sSimOutVarsFreq.compare("Daily", Qt::CaseInsensitive)==0
															  || sSimOutVarsFreq.compare("Hourly" , Qt::CaseInsensitive)==0 || sSimOutVarsFreq.compare("RunPeriod", Qt::CaseInsensitive)==0))
						sSimOutVarsFreq = " " + sSimOutVarsFreq;
					else
						sSimOutVarsFreq.clear();
					sRVErviTo = "SimOutVarsToCSV.rvi unlimited";		// convert sRVErviTo into command line for ReadVarsESO
					if (!sSimOutVarsFreq.isEmpty())
						sRVErviTo += sSimOutVarsFreq.toLocal8Bit().constData();
	            _chdir( sEPlusProcDir.c_str() );
					bDirChangedToEPlus = true;
					exec_stream_t es;
					try
					{	es.start( sRVEexeTo, sRVErviTo, CREATE_NO_WINDOW );
						while (es.running())
							Sleep( 100 );
					}
					catch(exec_stream_t::error_t &e)
					{	sWarnMsg = boost::str( boost::format( "Warning:  Execution of ReadVarsESO reported error: %s" ) % e.what() );
					}
			}	}

	//		QString sEPlusOutPath;		sEPlusOutPath.sprintf( "%s%s\\EnergyPlus\\", sProcessingPath, osSimInfo[iSimRun].pszRunID );
	//		QString sSimOutVarsCSVPathFile = sProcessingPath;
	//		sSimOutVarsCSVPathFile += osRunInfo[iSimRun].SDDFile();								assert( sSimOutVarsCSVPathFile.lastIndexOf('.') > 0 );
	//		if (sSimOutVarsCSVPathFile.lastIndexOf('.') > 0)
	//			sSimOutVarsCSVPathFile = sSimOutVarsCSVPathFile.left( sSimOutVarsCSVPathFile.lastIndexOf('.') );
	//		sSimOutVarsCSVPathFile += " - OutputVars.csv";
	//		QString sOverwriteMsg;
	//		sLogMsg.clear();
	//		sOverwriteMsg.sprintf( "The CSV file '%s' is opened in another application.  This file must be closed in that "
	//										"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
	//										"(once the file is closed), or \n'Cancel' to abort the analysis.", sSimOutVarsCSVPathFile );
	//		if (!OKToWriteOrDeleteFile( sSimOutVarsCSVPathFile, sOverwriteMsg, bSilent ))
	//		{	if (bSilent)
	//				sLogMsg.sprintf( "Warning:  Unable to overwrite SimOutputVariablesToCSV file:  %s", sSimOutVarsCSVPathFile );
	//			else
	//				sLogMsg.sprintf( "Warning:  User chose not to overwrite SimOutputVariablesToCSV file:  %s", sSimOutVarsCSVPathFile );
	//		}
	//		else
	//		{
	//			QString sRVEexeTo = sEPlusOutPath + QString("ReadVarsESO.exe");
	//			QString sRVErviTo = sEPlusOutPath + QString("SimOutVarsToCSV.rvi");
	//			if (!CopyFile( sReadVarsESOexe, sRVEexeTo, FALSE ))
	//			{	assert( FALSE );
	//			}
	//			if (!CopyFile( sReadVarsESOrvi, sRVErviTo, FALSE ))
	//			{	assert( FALSE );
	//			}
	//			else
	//			{	sRVErviTo = "SimOutVarsToCSV.rvi unlimited";		// convert sRVErviTo into command line for ReadVarsESO
	//				exec_stream_t es;
	//				try
	//				{	es.start( (const char*)sRVEexeTo, (const char*)sRVErviTo );  //, CREATE_NO_WINDOW );
	//					while (es.running())
	//					{	Sleep( 100 );
	//					}
	//					// ReadVarsESO execution done - now copy output over to final file
	//					QString sOutCSV = sEPlusOutPath + QString("eplusout.csv");
	//					if (!FileExists( sOutCSV ))
	//						sLogMsg = "Warning:  SimOutVarsToCSV ouput file not found";
	//					else if (!CopyFile( sOutCSV, sSimOutVarsCSVPathFile, FALSE ))
	//						sLogMsg.sprintf( "Warning:  Unable to copy SimOutVarsToCSV file from '%s' to '%s'", sOutCSV, sSimOutVarsCSVPathFile );
	//					else
	//					{	int iGotHere = 1;
	//						iGotHere;
	//					}
	//				}
	//				catch(exec_stream_t::error_t &e)
	//				{	sLogMsg.sprintf( "Warning:  Execution of ReadVarsESO reported error: %s", e.what() );
	//				}
	//		}	}
	//		if (!sLogMsg.isEmpty())
	//			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

			if (bDirChangedToEPlus)
            _chdir( pszSimProcessDir );
			if (sWarnMsg.size() > 0)
				BEMPX_WriteLogFile( sWarnMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}

	// SAC 1/24/14 - added code to address simultion file deletion & movement
		if (iSimulationStorage >= 0 && iRetVal == 0)
		{	std::string sRootProcDir, sEPlusProcDir, sEPlusProc2Dir, sSDDFileRoot, sCopyFr, sCopyTo, sFailMsg;
			sRootProcDir   = boost::str( boost::format( "%s%s\\" ) % pszSimProcessDir % osRunInfo.RunID().toLocal8Bit().constData() );
//			sEPlusProcDir  = boost::str( boost::format( "%sModelToIdf\\EnergyPlus-0\\" ) % sRootProcDir.c_str() );
//			sEPlusProc2Dir = boost::str( boost::format( "%sModelToIdf\\" ) % sRootProcDir.c_str() );
//			if (osRunInfo.SimulatingFixedIDF())  // SAC 1/25/14
//				sEPlusProcDir  = boost::str( boost::format( "%sEnergyPlus\\" ) % sRootProcDir.c_str() );
// SAC 11/5/14 - modified run directories since ModelToIDF now done via API and not RunManager - hence no ModelToidf subdirectory
			sEPlusProcDir  = boost::str( boost::format( "%sEnergyPlus\\" ) % sRootProcDir.c_str() );
			sSDDFileRoot = osRunInfo.SDDFile().toLocal8Bit().constData();
			boost::uintmax_t uiNumDeleted;
			unsigned uiLastDot = sSDDFileRoot.rfind('.');
			if (uiLastDot != std::string::npos)
				sSDDFileRoot = sSDDFileRoot.substr( 0, uiLastDot );
			// data defining which files get copied where      - for iSimulationStorage =  1  2  3  4  5  6  7
			FileCopyInfo fcInfo[] = {//{	"in.idf",         ".idf",            1, true,  { 1, 1, 1, 1, 1, 1, 1 } },	-- IDF file now written to std processing directory - just leave alone for now
												{	"eplustbl.htm",   ".htm",            0, true,  { 0, 1, 1, 1, 1, 1, 1 } },
												{	"eplusssz.csv",   " - ssz.csv",      0, true,  { 0, 0, 1, 1, 1, 1, 1 } },
												{	"epluszsz.csv",   " - zsz.csv",      0, true,  { 0, 0, 1, 1, 1, 1, 1 } },
												{	"eplusout.csv",   ".csv",            0, false, { 0, 0, 1, 1, 1, 1, 1 } },	// SAC 4/12/16 - for SimOutputVariablesToCSV - SAC 4/26/16 - toggled from T to F since they may not be present
												{	"eplusout.eio",   ".eio",            0, true,  { 0, 0, 1, 1, 1, 1, 1 } },
												{	"eplusout.err",   ".err",            0, true,  { 0, 0, 1, 1, 1, 1, 1 } },
												{	"eplusout.rdd",   ".rdd",            0, true,  { 0, 0, 1, 1, 1, 1, 1 } },
												{	"stderr",         " - stderr",       0, false, { 0, 0, 1, 1, 1, 1, 1 } },
												{	"eplusout.sql",   ".sql",            0, true,  { 0, 0, 0, 1, 0, 1, 1 } },
												{	"eplusout.eso",   ".eso",            0, false, { 0, 0, 0, 0, 1, 1, 1 } },	// SAC 3/4/14 - toggled report failure here from T to F, as these may not be written when debug results turned off
												{	"eplusout.mtr",   ".mtr",            0, true,  { 0, 0, 0, 0, 1, 1, 1 } },
										//		{	"Energy+.ini",    " - Energy+.ini",  0, true,  { 0, 0, 0, 0, 0, 0, 1 } },	- SAC 11/21/15 - no longer written/produced as of E+ ver 8.3 (??)
												{	"eplusout.audit", ".audit",          0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"eplusout.bnd",   ".bnd",            0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"eplusout.end",   ".end",            0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"eplusout.mdd",   ".mdd",            0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"eplusout.mtd",   ".mtd",            0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"eplusout.shd",   ".shd",            0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"sqlite.err",     " - sqlite.err",   0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"stdout",         " - stdout",       0, true,  { 0, 0, 0, 0, 0, 0, 1 } },
												{	"in.epw",         "",                0, true,  { 0, 0, 0, 0, 0, 0, 0 } },  // no copy, just include to ensure writable
												{	"",               "",                0, true,  { 0, 0, 0, 0, 0, 0, 0 } } };
			int iFC = -1;
			while (fcInfo[++iFC].sCopyFrom.size() > 1)
//			{	sCopyFr = boost::str( boost::format( "%s%s" ) % (fcInfo[iFC].iFromDirID==0 ? sEPlusProcDir.c_str() : sEPlusProc2Dir.c_str()) % fcInfo[iFC].sCopyFrom.c_str() );
			{	sCopyFr = boost::str( boost::format( "%s%s" ) % sEPlusProcDir.c_str() % fcInfo[iFC].sCopyFrom.c_str() );
				BOOL bFileExists = FileExists( sCopyFr.c_str() );
				if (bFileExists)
					_chmod( sCopyFr.c_str(), _S_IREAD | _S_IWRITE );	// ensure file is writable so that it can be deleted down below
				if (	iSimulationStorage > MAX_SimStorageVal ||
						(iSimulationStorage > 0 && fcInfo[iFC].iaCopyForOptVal[iSimulationStorage-1]) )
				{	sCopyTo = boost::str( boost::format( "%s%s%s" ) % sRootProcDir.c_str() % sSDDFileRoot.c_str() % fcInfo[iFC].sCopyTo.c_str() );
					sFailMsg = "";
					if (!bFileExists)
					{	if (fcInfo[iFC].bReportFailure)
							sFailMsg = boost::str( boost::format( "    during simulation file clean-up, file not found:  %s" ) % sCopyFr.c_str() );
					}
					else	// file exists
					{	if (!CopyFile( sCopyFr.c_str(), sCopyTo.c_str(), FALSE ))
						{	if (fcInfo[iFC].bReportFailure)
								sFailMsg = boost::str( boost::format( "    during simulation file clean-up, unable to copy file:  '%s' -to- '%s'" ) % sCopyFr.c_str() % sCopyTo.c_str() );
					}	}
					if (sFailMsg.size() > 0)
						BEMPX_WriteLogFile( sFailMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}	}
			// done copying all files (that we intend to save) - now blast the entire simulation processing direcotry
			std::string sEPlusDirToDel;
			if (iSimulationStorage == 0)
				sEPlusDirToDel = boost::str( boost::format( "%s%s" ) % pszSimProcessDir % osRunInfo.RunID().toLocal8Bit().constData() );
			else
				sEPlusDirToDel = boost::str( boost::format( "%sEnergyPlus" ) % sRootProcDir.c_str() );
	//		else if (osRunInfo.SimulatingFixedIDF())  // SAC 1/25/14
	//			sEPlusDirToDel = boost::str( boost::format( "%sEnergyPlus" ) % sRootProcDir.c_str() );
	//		else
	//			sEPlusDirToDel = boost::str( boost::format( "%sModelToIdf" ) % sRootProcDir.c_str() );
			try
			{	uiNumDeleted = boost::filesystem::remove_all( sEPlusDirToDel.c_str() );
			}
			catch (const boost::filesystem::filesystem_error& ex)
			{	sFailMsg = boost::str( boost::format( "    during simulation file clean-up, unable to remove directory:  %s  - %s" ) % sEPlusDirToDel.c_str() % ex.what() );
				BEMPX_WriteLogFile( sFailMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
		}

	return bRetVal;
}


// SAC 7/14/12
//   const char* pszProjectFile    : path/directory/filename of current project file
int CMX_PerformSimulation_EnergyPlus(	QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
													// RUN #1 arguments
															const char* pszSDDFile, const char* pszRunID /*=NULL*/, const char* pszLongRunID /*=NULL*/,
															BOOL bIsStdRun /*=FALSE*/, BOOL bPostEquipCapsToBEMBase /*=TRUE*/, BOOL bSimulateModel /*=TRUE*/,	// SAC 3/24/13 - added
															const char* pszIDFToSimulate /*=NULL*/, int iBEMProcIdx /*=-1*/, int iProgressModel /*=0*/,
													// RUN #2 arguments
															const char* pszSDDFile2 /*=NULL*/, const char* pszRunID2 /*=NULL*/, const char* pszLongRunID2 /*=NULL*/,
															BOOL bIsStdRun2 /*=FALSE*/, BOOL bPostEquipCapsToBEMBase2 /*=TRUE*/, BOOL bSimulateModel2 /*=TRUE*/,	// SAC 3/24/13 - added
															const char* pszIDFToSimulate2 /*=NULL*/, int iBEMProcIdx2 /*=-1*/, int iProgressModel2 /*=0*/,
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose /*=FALSE*/, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL /*bDurationStats=FALSE*/, double* pdTranslationTime /*=NULL*/, double* pdSimulationTime /*=NULL*/,  // SAC 1/23/14
															int iSimulationStorage /*=-1*/, double* dEPlusVer /*=NULL*/, char* pszEPlusVerStr /*=NULL*/, int iEPlusVerStrLen /*=0*/,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr /*=NULL*/, int iOpenStudioVerStrLen /*=0*/, int iCodeType /*=CT_T24N*/,
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/ )	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
{
	int iRetVal = 0;
	QString sLogMsg, sTemp;

//	OS_Wrap::OSWrapLib osWrap;
	OSWrapLib osWrap;
	COSRunInfo osRunInfo, osRunInfo2;
	osRunInfo.InitializeRunInfo( &osWrap, 0, pszSDDFile, pszRunID, pszLongRunID, (bIsStdRun != FALSE), (bPostEquipCapsToBEMBase != FALSE), (bSimulateModel != FALSE), iBEMProcIdx, pszIDFToSimulate, iCodeType );
	bool bHaveSecondRun = (pszSDDFile2 && FileExists( pszSDDFile2 ));
	if (bHaveSecondRun)
		osRunInfo2.InitializeRunInfo( &osWrap, 1, pszSDDFile2, pszRunID2, pszLongRunID2, (bIsStdRun2 != FALSE), (bPostEquipCapsToBEMBase2 != FALSE), (bSimulateModel2 != FALSE), iBEMProcIdx2, pszIDFToSimulate2, iCodeType );

	if (iProgressModel < 1 && bSimulateModel)
	{	if (bIsStdRun)
			iProgressModel = (bPostEquipCapsToBEMBase ? BCM_NRP_Model_zb : BCM_NRP_Model_ab);
		else
			iProgressModel = (bPostEquipCapsToBEMBase ? BCM_NRP_Model_zp : BCM_NRP_Model_ap);
	}
	if (iProgressModel2 < 1 && bHaveSecondRun && bSimulateModel2)
	{	if (bIsStdRun2)
			iProgressModel2 = (bPostEquipCapsToBEMBase2 ? BCM_NRP_Model_zb : BCM_NRP_Model_ab);
		else
			iProgressModel2 = (bPostEquipCapsToBEMBase2 ? BCM_NRP_Model_zp : BCM_NRP_Model_ap);
	}

//	//QString sWthrPathFile = pszWthrPath;
//	//sWthrPathFile += "CZ12RV2.epw";
//	QString sWthrPathFile;
//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile" ), sWthrPathFile );
#define  EPLUS_EUMult  14
	double adResults[5*EPLUS_EUMult] = {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										            0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double adResults2[5*EPLUS_EUMult] = {  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										            0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
   char pszSQLOutPathFile[MAX_PATH+1];
   char pszSQLOutPathFile2[MAX_PATH+1];
	int iMaxLenSQLOutPathFile = MAX_PATH+1;
	int iMaxLenSQLOutPathFile2 = MAX_PATH+1;
								if (bVerbose)
									BEMPX_WriteLogFile( "  PerfSim_E+ - About to simulate SDD", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	char pszSimSDDErrorMsg[1024];		pszSimSDDErrorMsg[0] = '\0';
// --------------------
// SIMULATE SDD MODEL
// --------------------
	long lSimRetVal=0;
	if (bHaveSecondRun)
		lSimRetVal = osWrap.SimulateSDD( pszEPlusPath, pszSimProcessDir, osRunInfo.SDDFile().toLocal8Bit().constData(), osRunInfo.RunID().toLocal8Bit().constData(),
														osRunInfo.WthrPathFile().toLocal8Bit().constData(), (double*) &adResults[0],
														osRunInfo.SimulateModel(), (osRunInfo.StoreHourlyResults() != FALSE), pszSQLOutPathFile, iMaxLenSQLOutPathFile,
		// restore once hrly results debugged...		  (bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, (OSWRAP_MSGCALLBACK*) OSWrapCallback );
														TRUE /*bWriteHourlyDebugCSV*/, osRunInfo.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo.m_qaData, iProgressModel,		// SAC 1/25/14		// SAC 11/6/14
									// RUN #2 data
														osRunInfo2.SDDFile().toLocal8Bit().constData(), osRunInfo2.RunID().toLocal8Bit().constData(),
														osRunInfo.WthrPathFile().toLocal8Bit().constData(), (double*) &adResults2[0],
														osRunInfo2.SimulateModel(), (osRunInfo.StoreHourlyResults() != FALSE), pszSQLOutPathFile2, iMaxLenSQLOutPathFile2,
		// restore once hrly results debugged...		  (bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, (OSWRAP_MSGCALLBACK*) OSWrapCallback );
														TRUE /*bWriteHourlyDebugCSV*/, osRunInfo2.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo2.m_qaData,	iProgressModel2,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType );
	else
		lSimRetVal = osWrap.SimulateSDD( pszEPlusPath, pszSimProcessDir, osRunInfo.SDDFile().toLocal8Bit().constData(), osRunInfo.RunID().toLocal8Bit().constData(),
														osRunInfo.WthrPathFile().toLocal8Bit().constData(), (double*) &adResults[0],
														osRunInfo.SimulateModel(), (osRunInfo.StoreHourlyResults() != FALSE), pszSQLOutPathFile, iMaxLenSQLOutPathFile,
		// restore once hrly results debugged...		  (bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, (OSWRAP_MSGCALLBACK*) OSWrapCallback );
														TRUE /*bWriteHourlyDebugCSV*/, osRunInfo.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo.m_qaData, iProgressModel,  // SAC 1/25/14
														NULL, NULL, NULL, NULL, true, true, NULL, 0, false, NULL, NULL, 0,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType );

								if (bVerbose)
								{	sLogMsg = QString( "  PerfSim_E+ - Back from SDD simulation (returned %1)" ).arg( QString::number(lSimRetVal) );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}

	if (dEPlusVer)
		*dEPlusVer = osWrap.EnergyPlusVersion( pszEPlusPath );  // SAC 5/16/14
#pragma warning(disable:4996)
	if (pszEPlusVerStr && iEPlusVerStrLen > 0)
	{	std::string sVerStr = osWrap.Get_SimVersionID(0);
		strncpy( pszEPlusVerStr, sVerStr.c_str(), iEPlusVerStrLen-1 );
		pszEPlusVerStr[iEPlusVerStrLen-1] = '\0';
	}
	if (pszOpenStudioVerStr && iOpenStudioVerStrLen > 0)	// SAC 8/22/14
	{	std::string sVerStr = osWrap.GetOpenStudioVersion( true /*long/verbose version*/ );
		strncpy( pszOpenStudioVerStr, sVerStr.c_str(), iOpenStudioVerStrLen-1 );
		pszOpenStudioVerStr[iOpenStudioVerStrLen-1] = '\0';
	}
#pragma warning(default:4996)

	if (strlen( pszSimSDDErrorMsg ) > 0)
		BEMPX_WriteLogFile( pszSimSDDErrorMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	if (lSimRetVal == OSWrap_SimSDD_UserAbortedAnalysis)  // ABORTING ANALYSIS
	{	if (bVerbose)
			LogEnergyPlusMessages( &osWrap, &osRunInfo );
		iRetVal = OSI_SimEPlus_UserAbortedAnalysis;
	}
	else if (lSimRetVal != 0)
	{	assert( lSimRetVal > 0 && lSimRetVal < 81 );  // this is the range we are expecting OS_Wrap error codes to fall into
		LogEnergyPlusMessages( &osWrap, &osRunInfo );

// TODO - REVISE FOR MODIFIED ERROR CODES

		iRetVal = lSimRetVal + 100;  // some OpenStudio or EnergyPlus simulation error
		switch (lSimRetVal)
		{	case  OSWrap_SimSDD_InputFileNotFound    :	sErrMsg = QString( "SDD XML simulation input file not found:  %1%2" ).arg( pszSimProcessDir, osRunInfo.SDDFile() );	break;
			case  OSWrap_SimSDD_WthrFileNotFound     :	sErrMsg = QString( "Simulation weather file not found:  %1" ).arg( osRunInfo.WthrPathFile() );								break;
			case  OSWrap_SimSDD_ProcPathNotValid     :	sErrMsg = QString( "Simulation processing path not valid:  %1" ).arg( pszSimProcessDir );										break;
			case  OSWrap_SimSDD_SimEXEPathNotValid   :	sErrMsg = QString( "Simulation executable path not valid:  %1" ).arg( pszEPlusPath );											break;
			case  OSWrap_SimSDD_SimErrFileNotValid   :	sErrMsg = QString( "Simulation error output path/file not valid for %1" ).arg( osRunInfo.SDDFile() );						break;
	//		case  OSWrap_SimSDD_UserAbortedAnalysis  :	sErrMsg = QString( "",  );		break;   - handled above
			case  OSWrap_SimSDD_InputFile2NotFound   :	sErrMsg = QString( "SDD XML simulation input file not found:  %1%2" ).arg( pszSimProcessDir, osRunInfo2.SDDFile() );	break;
			case  OSWrap_SimSDD_WthrFile2NotFound    :	sErrMsg = QString( "Simulation weather file not found:  %1" ).arg( osRunInfo2.WthrPathFile() );								break;
			case  OSWrap_SimSDD_SimErrFile2NotValid  :	sErrMsg = QString( "Simulation error output path/file not valid for %1" ).arg( osRunInfo2.SDDFile() );					break;
			case  OSWrap_SimSDD_OSLoadModelError     :	sErrMsg = QString( "Error encountered in OpenStudio loading SDD XML file:  %1%2" ).arg( pszSimProcessDir, osRunInfo.SDDFile() );		break;
			case  OSWrap_SimSDD_OSSaveOSMError       :	sErrMsg = QString( "Error encountered in OpenStudio saving model to OSM file for %1" ).arg( osRunInfo.SDDFile() );	break;
			case  OSWrap_SimSDD_OSSimSQLOutNotFound  :	sErrMsg = QString( "Unable to locate EnergyPlus simulation SQL output file for %1" ).arg( osRunInfo.SDDFile() );		break;
			case  OSWrap_SimSDD_OSModelNotValid      :	sErrMsg = QString( "OpenStudio Model not valid following simulation of %1" ).arg( osRunInfo.SDDFile() );					break;
			case  OSWrap_SimSDD_OSFacilityNotValid   :	sErrMsg = QString( "OpenStudio Facility not valid following simulation of %1" ).arg( osRunInfo.SDDFile() );				break;
			case  OSWrap_SimSDD_OSModelCreateError   :	sErrMsg = QString( "Error creating OpenStudio Model object for %1" ).arg( osRunInfo.SDDFile() );							break;
			case  OSWrap_SimSDD_OSLoadModel2Error    :	sErrMsg = QString( "Error encountered in OpenStudio loading SDD XML file:  %1%2" ).arg( pszSimProcessDir, osRunInfo2.SDDFile() );	break;
			case  OSWrap_SimSDD_OSSaveOSM2Error      :	sErrMsg = QString( "Error encountered in OpenStudio saving model to OSM file for %1" ).arg( osRunInfo2.SDDFile() );	break;
			case  OSWrap_SimSDD_OSSimSQL2OutNotFound :	sErrMsg = QString( "Unable to locate EnergyPlus simulation SQL output file for %1" ).arg( osRunInfo2.SDDFile() );		break;
			case  OSWrap_SimSDD_OSModel2NotValid     :	sErrMsg = QString( "OpenStudio Model not valid following simulation of %1" ).arg( osRunInfo2.SDDFile() );				break;
			case  OSWrap_SimSDD_OSFacility2NotValid  :	sErrMsg = QString( "OpenStudio Facility not valid following simulation of %1" ).arg( osRunInfo2.SDDFile() );			break;
			case  OSWrap_SimSDD_OSModel2CreateError  :	sErrMsg = QString( "Error creating OpenStudio Model object for %1" ).arg( osRunInfo2.SDDFile() );							break;
			case  OSWrap_SimSDD_SimFatalError        :	sErrMsg = QString( "Fatal error(s) ocurred in EnergyPlus simulation of %1" ).arg( osRunInfo.SDDFile() );					break;
			case  OSWrap_SimSDD_SimIncomplete        :	sErrMsg = QString( "EnergyPlus simulation did not complete successfully for %1" ).arg( osRunInfo.SDDFile() );			break;
			case  OSWrap_SimSDD_Sim2FatalError       :	sErrMsg = QString( "Fatal error(s) ocurred in EnergyPlus simulation of %1" ).arg( osRunInfo2.SDDFile() );					break;
			case  OSWrap_SimSDD_Sim2Incomplete       :	sErrMsg = QString( "EnergyPlus simulation did not complete successfully for %1" ).arg( osRunInfo2.SDDFile() );			break;
			default		: sErrMsg = QString( "Unrecognized OSWrap error #%1" ).arg( QString::number(lSimRetVal) );		break;
		}
	}

	ProcessSimulationResults( osWrap, osRunInfo, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/17/14 - moved ALL results processing to subordinate routine

	if (bHaveSecondRun)
	{	int iResCopyRetVal = 0;
		if (osRunInfo.StoreHourlyResults() && osRunInfo2.StoreHourlyResults() && iRetVal == 0)
		{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
			QString sResCopyErrMsg;
			iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, osRunInfo2.RunID().toLocal8Bit().constData(), osRunInfo.BEMProcIdx(), osRunInfo2.BEMProcIdx() );
			assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
			if (iResCopyRetVal > 0)
			{	if (sErrMsg.isEmpty())
					sErrMsg = sResCopyErrMsg;
				iRetVal = iResCopyRetVal;
			}
		}
      if (iResCopyRetVal == 0)
			ProcessSimulationResults( osWrap, osRunInfo2, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/18/14
	}

								if (bVerbose && iRetVal != OSI_SimEPlus_UserAbortedAnalysis)
									BEMPX_WriteLogFile( "  PerfSim_E+ - returning", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	
	return iRetVal;
}


// SAC 8/18/15
int CMX_PerformSimulation_EnergyPlus_Multiple(	QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose /*=FALSE*/, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL /*bDurationStats=FALSE*/, double* pdTranslationTime /*=NULL*/, double* pdSimulationTime /*=NULL*/,  // SAC 1/23/14
															int iSimulationStorage /*=-1*/, double* dEPlusVer /*=NULL*/, char* pszEPlusVerStr /*=NULL*/, int iEPlusVerStrLen /*=0*/,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr /*=NULL*/, int iOpenStudioVerStrLen /*=0*/, int iCodeType /*=CT_T24N*/,
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/ )	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
{

//typedef struct
//{
//	char pszSDDFile[FILENAME_MAX];
//	char pszIDFToSimulate[FILENAME_MAX];
//	char pszRunID[32];
//	char pszLongRunID[64];
//	bool bIsStdRun;
//	bool bPostEquipCapsToBEMBase;
//	bool bSimulateModel;
//	int  iBEMProcIdx;
//	int  iProgressModel;
//	int  iOrientationIdx;	// for 90.1 baseline orientation runs (1-4)
//}	OS_SimInfo;

	int iRetVal = 0;
	QString sLogMsg, sTemp;

	if (pSimInfo == NULL || iNumSimInfo < 1 || iNumSimInfo > MultEPlusSim_MaxSims)
	{	iRetVal = OSI_SimEPlus_InvalidSimInfo;
		assert( FALSE );
	}

//	OS_Wrap::OSWrapLib osWrap;
	OSWrapLib osWrap;
	COSRunInfo osRunInfo[MultEPlusSim_MaxSims];
	OSWrap_SimInfo oswSimInfo[MultEPlusSim_MaxSims];
	OSWrap_SimInfo* poswSimInfo[MultEPlusSim_MaxSims];
#define  EPLUS_EUMult  14
	double adResults[MultEPlusSim_MaxSims][5*EPLUS_EUMult] =  { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
																					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	int iRun=0;
	for (; iRun < MultEPlusSim_MaxSims; iRun++)
		poswSimInfo[iRun] = (iRun < iNumSimInfo ? &oswSimInfo[iRun] : NULL);
	for (iRun=0; (iRun < iNumSimInfo && iRetVal == 0); iRun++)
	{	if (pSimInfo[iRun] == NULL)
		{	iRetVal = OSI_SimEPlus_InvalidSimInfo;
			assert( FALSE );
		}
		else
		{	osRunInfo[iRun].InitializeRunInfo( &osWrap, iRun, pSimInfo[iRun]->pszSDDFile, pSimInfo[iRun]->pszRunID, pSimInfo[iRun]->pszLongRunID, pSimInfo[iRun]->bIsStdRun, pSimInfo[iRun]->bPostEquipCapsToBEMBase,
										pSimInfo[iRun]->bSimulateModel, pSimInfo[iRun]->iBEMProcIdx, pSimInfo[iRun]->pszIDFToSimulate, iCodeType, pSimInfo[iRun]->bSimOutVarsCSV );

			if (pSimInfo[iRun]->iProgressModel < 1 && pSimInfo[iRun]->bSimulateModel)
			{	if (iCodeType == CT_T24N)
				{	if (pSimInfo[iRun]->bIsStdRun)
						pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRP_Model_zb : BCM_NRP_Model_ab);
					else
						pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRP_Model_zp : BCM_NRP_Model_ap);
				}
				else
				{	if (pSimInfo[iRun]->bIsStdRun)
						switch (pSimInfo[iRun]->iOrientationIdx)
						{	case  1:  pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRAP_Model_zb1 : BCM_NRAP_Model_ab1);
							case  2:  pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRAP_Model_zb2 : BCM_NRAP_Model_ab2);
							case  3:  pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRAP_Model_zb3 : BCM_NRAP_Model_ab3);
							case  4:  pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRAP_Model_zb4 : BCM_NRAP_Model_ab4);
						}
					else
						pSimInfo[iRun]->iProgressModel = (pSimInfo[iRun]->bPostEquipCapsToBEMBase ? BCM_NRAP_Model_zp : BCM_NRAP_Model_ap);
			}	}

#pragma warning(disable:4996)
		// setup OSWrap_SimInfo structure to pass into OS_Wrap simulation routine
			if (pSimInfo[iRun]->pszSDDFile && strlen( pSimInfo[iRun]->pszSDDFile ) > 0)
				strncpy( oswSimInfo[iRun].pszSDDXMLFileName, pSimInfo[iRun]->pszSDDFile, FILENAME_MAX-1 );
			else
				oswSimInfo[iRun].pszSDDXMLFileName[0] = '\0';
			if (pSimInfo[iRun]->pszRunID && strlen( pSimInfo[iRun]->pszRunID ) > 0)
				strncpy( oswSimInfo[iRun].pszRunSubdir, pSimInfo[iRun]->pszRunID, FILENAME_MAX-1 );
			else
				oswSimInfo[iRun].pszRunSubdir[0] = '\0';
			strncpy( oswSimInfo[iRun].pszWeatherPathFile, osRunInfo[iRun].WthrPathFile().toLocal8Bit().constData(), FILENAME_MAX-1 );
			oswSimInfo[iRun].pszSQLOutPathFile[0] = '\0';
			if (pSimInfo[iRun]->pszIDFToSimulate && strlen( pSimInfo[iRun]->pszIDFToSimulate ) > 0)
				strncpy( oswSimInfo[iRun].pszIDFToSimulate, pSimInfo[iRun]->pszIDFToSimulate, FILENAME_MAX-1 );
			else
				oswSimInfo[iRun].pszIDFToSimulate[0] = '\0';
#pragma warning(default:4996)
			oswSimInfo[iRun].pdResults					= &adResults[iRun][0]; 
			oswSimInfo[iRun].bSimulateModel			= pSimInfo[iRun]->bSimulateModel;
			oswSimInfo[iRun].bStoreHourlyResults	= osRunInfo[iRun].StoreHourlyResults();
			oswSimInfo[iRun].bWriteHourlyDebugCSV	= true;
			oswSimInfo[iRun].lRptFuelUseAs			= osRunInfo[iRun].RptFuelUseAs();		// SAC 10/28/15
			oswSimInfo[iRun].pQuickAnalysisInfo		= &osRunInfo[iRun].m_qaData;
			oswSimInfo[iRun].iProgressModel			= pSimInfo[iRun]->iProgressModel;
			oswSimInfo[iRun].iSimReturnValue			= 0;
	}	}

								if (bVerbose)
									BEMPX_WriteLogFile( "  PerfSim_E+ - About to simulate SDD", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	char pszSimSDDErrorMsg[1024];		pszSimSDDErrorMsg[0] = '\0';
// --------------------
// SIMULATE SDD MODELS
// --------------------
	long lSimRetVal = osWrap.SimulateSDD_Multiple( pszEPlusPath, pszSimProcessDir, poswSimInfo, iNumSimInfo,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType );

								if (bVerbose)
								{	sLogMsg = QString( "  PerfSim_E+ - Back from SDD simulation (returned %1)" ).arg( QString::number(lSimRetVal) );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}

	if (dEPlusVer)
		*dEPlusVer = osWrap.EnergyPlusVersion( pszEPlusPath );  // SAC 5/16/14
#pragma warning(disable:4996)
	if (pszEPlusVerStr && iEPlusVerStrLen > 0)
	{	std::string sVerStr = osWrap.Get_SimVersionID(0);
		strncpy( pszEPlusVerStr, sVerStr.c_str(), iEPlusVerStrLen-1 );
		pszEPlusVerStr[iEPlusVerStrLen-1] = '\0';
	}
	if (pszOpenStudioVerStr && iOpenStudioVerStrLen > 0)	// SAC 8/22/14
	{	std::string sVerStr = osWrap.GetOpenStudioVersion( true /*long/verbose version*/ );
		strncpy( pszOpenStudioVerStr, sVerStr.c_str(), iOpenStudioVerStrLen-1 );
		pszOpenStudioVerStr[iOpenStudioVerStrLen-1] = '\0';
	}
#pragma warning(default:4996)

	if (strlen( pszSimSDDErrorMsg ) > 0)
		BEMPX_WriteLogFile( pszSimSDDErrorMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	QString sTempErr;
	if (lSimRetVal == OSWrap_SimSDD_UserAbortedAnalysis)  // ABORTING ANALYSIS
	{	if (bVerbose)
		{	for (iRun=0; iRun < iNumSimInfo; iRun++)
			{
				sLogMsg = QString( "  Simulation messages for model %1 of %2:  %3  -  %4" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].RunID(), osRunInfo[iRun].SDDFile() );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				LogEnergyPlusMessages( &osWrap, &osRunInfo[iRun] );		// SAC 8/19/15 - not sure if we shoudl post a line or two identifying the simulation model before this call...
		}	}
		iRetVal = OSI_SimEPlus_UserAbortedAnalysis;
	}
	else if (lSimRetVal != 0)
	{	assert( lSimRetVal > 0 && lSimRetVal < 499 );  // this is the range we are expecting OS_Wrap error codes to fall into

					// DEBUGGING
						sLogMsg = QString( "        osWrap.SimulateSDD_Multiple() returned:  %1" ).arg( QString::number(lSimRetVal) );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

		for (iRun=0; iRun < iNumSimInfo; iRun++)
		{
			sLogMsg = QString( "  Simulation messages for model %1 of %2:  %3  -  %4" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].RunID(), osRunInfo[iRun].SDDFile() );
			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			LogEnergyPlusMessages( &osWrap, &osRunInfo[iRun] );		// SAC 8/19/15 - not sure if we shoudl post a line or two identifying the simulation model before this call...
		}

// TODO - REVISE FOR MODIFIED ERROR CODES

		iRetVal = lSimRetVal;	//  + 100;  // some OpenStudio or EnergyPlus simulation error
		if (lSimRetVal < OSWrap_SimSDD_InputFileNotFound)
		{	switch (lSimRetVal)
			{	case  OSWrap_SimSDD_ProcPathNotValid     		:	sErrMsg = QString( "Simulation processing path not valid:  %1" ).arg( pszSimProcessDir );							break;
				case  OSWrap_SimSDD_SimEXEPathNotValid   		:	sErrMsg = QString( "Simulation executable path not valid:  %1" ).arg( pszEPlusPath );								break;
				case  OSWrap_SimSDD_TooManySims   				:	sErrMsg = QString( "Invalid number of concurrent simulations (%1 > max of 10)" ).arg( QString::number(iNumSimInfo) );			break;
				case  OSWrap_SimSDD_NumSimsWithQuickRunErr   :	sErrMsg = QString( "Invalid combination of unique model & quick simulations (%1 > max of 2 models when performing quick runs)" ).arg( QString::number(iNumSimInfo) );		break;
				default													:	sErrMsg = QString( "Unrecognized OSWrap error #%1" ).arg( QString::number(lSimRetVal) );												break;
		}	}
		else	// search for and post error messages for each individual run error
		{	for (iRun=0; iRun < iNumSimInfo; iRun++)
				if (oswSimInfo[iRun].iSimReturnValue >= OSWrap_SimSDD_InputFileNotFound)
				{	if (!sErrMsg.isEmpty())
						sErrMsg += "\n      ";
					switch (oswSimInfo[iRun].iSimReturnValue)
					{	case  OSWrap_SimSDD_InputFileNotFound    :	sTempErr = QString( "SDD XML simulation input file not found (run %1 of %2):  %3%4" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), pszSimProcessDir, osRunInfo[iRun].SDDFile() );	break;
						case  OSWrap_SimSDD_WthrFileNotFound     :	sTempErr = QString( "Simulation weather file not found (run %1 of %2):  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].WthrPathFile() );								break;
						case  OSWrap_SimSDD_SimErrFileNotValid   :	sTempErr = QString( "Simulation error output path/file not valid for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );					break;
						case  OSWrap_SimSDD_InvalidSimData       :	sTempErr = QString( "Invalid simulation input data for run %1 (of %2)" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo) );						break;
						case  OSWrap_SimSDD_OSLoadModelError     :	sTempErr = QString( "Error encountered in OpenStudio loading SDD XML file (run %1 of %2):  %3%4" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), pszSimProcessDir, osRunInfo[iRun].SDDFile() );		break;
						case  OSWrap_SimSDD_OSSaveOSMError       :	sTempErr = QString( "Error encountered in OpenStudio saving model to OSM file for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );	break;
						case  OSWrap_SimSDD_OSSimSQLOutNotFound  :	sTempErr = QString( "Unable to locate EnergyPlus simulation SQL output file for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );		break;
						case  OSWrap_SimSDD_OSModelNotValid      :	sTempErr = QString( "OpenStudio Model not valid following simulation of run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );				break;
						case  OSWrap_SimSDD_OSFacilityNotValid   :	sTempErr = QString( "OpenStudio Facility not valid following simulation of run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );			break;
						case  OSWrap_SimSDD_OSModelCreateError   :	sTempErr = QString( "Error creating OpenStudio Model object for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );							break;
						case  OSWrap_SimSDD_OSSaveIDFError       :	sTempErr = QString( "Error encountered in OpenStudio saving (forward translated) IDF file for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );							break;
						case  OSWrap_SimSDD_SimFatalError        :	sTempErr = QString( "Fatal error(s) ocurred in EnergyPlus simulation of run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );				break;
						case  OSWrap_SimSDD_SimIncomplete        :	sTempErr = QString( "EnergyPlus simulation did not complete successfully for run %1 of %2:  %3" ).arg( QString::number(iRun+1), QString::number(iNumSimInfo), osRunInfo[iRun].SDDFile() );			break;
						default		: sTempErr = QString( "Unrecognized OSWrap error #%1" ).arg( QString::number(lSimRetVal) );		break;
					}
					sErrMsg += sTempErr;
				}
		}
	}

	bool bCopyHourlyResultsToNextModel = false;
	for (iRun=0; iRun < iNumSimInfo; iRun++)
	{
		if (osRunInfo[iRun].StoreHourlyResults())
			bCopyHourlyResultsToNextModel = true;
		int iResCopyRetVal = 0;
		if (iRun > 0 && bCopyHourlyResultsToNextModel && iRetVal == 0)
		{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
			QString sResCopyErrMsg;
			iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, osRunInfo[iRun].RunID().toLocal8Bit().constData(), osRunInfo[iRun-1].BEMProcIdx(), osRunInfo[iRun].BEMProcIdx() );
			assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
			if (iResCopyRetVal > 0)
			{	if (sErrMsg.isEmpty())
				{	sErrMsg = sResCopyErrMsg;
					sTempErr = QString( " (from run %1 to %2 (of %3))" ).arg( QString::number(iRun), QString::number(iRun+1), QString::number(iNumSimInfo) );
					sErrMsg += sTempErr;
				}
				iRetVal = iResCopyRetVal;
		}	}
		if (iResCopyRetVal == 0)
			ProcessSimulationResults( osWrap, osRunInfo[iRun], iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/17/14 - moved ALL results processing to subordinate routine
	}

								if (bVerbose && iRetVal != OSI_SimEPlus_UserAbortedAnalysis)
									BEMPX_WriteLogFile( "  PerfSim_E+ - returning", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	
	return iRetVal;
}


int OSWrap_ErrorIDToRunNumber( int iErr )
{	int iRetVal = 0;
	int iDelta1 = OSWrap_SimSDD_InputFile2NotFound - OSWrap_SimSDD_InputFileNotFound;
	int iDelta2 = OSWrap_SimSDD_OSLoadModel2Error  - OSWrap_SimSDD_OSLoadModelError;
	int iDelta3 = OSWrap_SimSDD_Sim2FatalError     - OSWrap_SimSDD_SimFatalError;
	if (     iErr <  OSWrap_SimSDD_InputFileNotFound)					iRetVal = 0;	// general errors, not run-specific
	else if (iErr <  OSWrap_SimSDD_InputFile2NotFound)					iRetVal = 1;
	else if (iErr <  OSWrap_SimSDD_InputFile3NotFound)					iRetVal = 2;
	else if (iErr <  OSWrap_SimSDD_InputFile4NotFound)					iRetVal = 3;
	else if (iErr <  OSWrap_SimSDD_InputFile5NotFound)					iRetVal = 4;
	else if (iErr <  OSWrap_SimSDD_InputFile6NotFound)					iRetVal = 5;
	else if (iErr <  OSWrap_SimSDD_InputFile7NotFound)					iRetVal = 6;
	else if (iErr <  OSWrap_SimSDD_InputFile8NotFound)					iRetVal = 7;
	else if (iErr <  OSWrap_SimSDD_InputFile9NotFound)					iRetVal = 8;
	else if (iErr <  OSWrap_SimSDD_InputFile10NotFound)				iRetVal = 9;
	else if (iErr < (OSWrap_SimSDD_InputFile10NotFound+iDelta1))	iRetVal = 10;
	else if (iErr <  OSWrap_SimSDD_OSLoadModelError)					iRetVal = 0;	// unassigned between lists of errors
	else if (iErr <  OSWrap_SimSDD_OSLoadModel2Error)					iRetVal = 1;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel3Error)					iRetVal = 2;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel4Error)					iRetVal = 3;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel5Error)					iRetVal = 4;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel6Error)					iRetVal = 5;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel7Error)					iRetVal = 6;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel8Error)					iRetVal = 7;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel9Error)					iRetVal = 8;
	else if (iErr <  OSWrap_SimSDD_OSLoadModel10Error)					iRetVal = 9;
	else if (iErr < (OSWrap_SimSDD_OSLoadModel10Error+iDelta2))		iRetVal = 10;
	else if (iErr <  OSWrap_SimSDD_SimFatalError)						iRetVal = 0;	// unassigned between lists of errors
	else if (iErr <  OSWrap_SimSDD_Sim2FatalError)						iRetVal = 1;
	else if (iErr <  OSWrap_SimSDD_Sim3FatalError)						iRetVal = 2;
	else if (iErr <  OSWrap_SimSDD_Sim4FatalError)						iRetVal = 3;
	else if (iErr <  OSWrap_SimSDD_Sim5FatalError)						iRetVal = 4;
	else if (iErr <  OSWrap_SimSDD_Sim6FatalError)						iRetVal = 5;
	else if (iErr <  OSWrap_SimSDD_Sim7FatalError)						iRetVal = 6;
	else if (iErr <  OSWrap_SimSDD_Sim8FatalError)						iRetVal = 7;
	else if (iErr <  OSWrap_SimSDD_Sim9FatalError)						iRetVal = 8;
	else if (iErr <  OSWrap_SimSDD_Sim10FatalError)						iRetVal = 9;
	else if (iErr < (OSWrap_SimSDD_Sim10FatalError+iDelta3))			iRetVal = 10;
	return iRetVal;
}
