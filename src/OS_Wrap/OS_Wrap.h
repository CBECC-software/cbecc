// OS_Wrap.h
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

#pragma once

#ifdef COMPILE_OS_WRAP
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

//#include <boost/log/attributes/attribute_set.hpp>

//#define  Q_OBJECT    // undefine a macro causing linker issues - OS fix submitted by DanM 7/17/12

#include <direct.h>
#include <string>
#include <iostream>
#include <vector>

class iddObject;  // forward declaration

//using namespace System;

//#define  openstudio_utilities_EXPORTS
//#define  openstudio_runmanager_EXPORTS


bool DLLAPI __cdecl OSWX_UnzipFile( const char* pszZipPathFile, const char* pszFileToUnzip, const char* pszUnzipToPath );

typedef int OSWRAP_MSGCALLBACK( int iCodeType, int level, const char* msg, int action );  // retval:  0:continue / -1:abort  //  level:  0:message / 1:warning / 2:error


enum  OS_EndUseType        //OPENSTUDIO_ENUM(EndUseType,
{	OSEU_IntLights,         //  ((InteriorLights))                     0
	OSEU_ExtLights,         //  ((ExteriorLights))                     1
	OSEU_IntEquip,          //  ((InteriorEquipment))                  2
	OSEU_ExtEquip,          //  ((ExteriorEquipment))                  3
	OSEU_Fans,              //  ((Fans))                               4
	OSEU_Pumps,             //  ((Pumps))                              5
	OSEU_Heating,           //  ((Heating))                            6
	OSEU_Cooling,           //  ((Cooling))                            7
	OSEU_HtReject,          //  ((HeatRejection))                      8
	OSEU_Humid,             //  ((Humidifier))                         9
	OSEU_HtRecov,           //  ((HeatRecovery))                      10
	OSEU_WaterSystems,      //  ((DHW))                               11
	OSEU_Cogen,             //  ((Cogeneration))                      12
	OSEU_Refrig,            //  ((Refrigeration))                     13
//	OSEU_Misc,              //  ((Miscellaneous))                     --
	OSEU_HtgCoils,          //  ((HeatingCoils))                      14
	OSEU_ClgCoils,          //  ((CoolingCoils))                      15
	OSEU_Boilers,           //  ((Boilers))                           16
	OSEU_Baseboard,         //  ((Baseboard))                         17
	OSEU_HtRecov_Clg,       //  ((HeatRecoveryForCooling))            18
	OSEU_HtRecov_Htg,       //  ((HeatRecoveryForHeating))            19
// addition of enduse/subcategory combinations (SAC 8/27/13)
	OSEU_IntLights_Comp,    //  ((InteriorLights)) + "ComplianceLtg"          20		// SAC 11/7/15 - 'Reg Ltg' -> 'ComplianceLtg' (SF tic 544)
	OSEU_IntLights_NonComp, //  ((InteriorLights)) + "NonComplianceLtg"       21		// SAC 11/7/15 - 'NonReg Ltg' -> 'NonComplianceLtg' (SF tic 544)
	OSEU_IntEquip_Recept,   //  ((InteriorEquipment)) + "Receptacle"          22
	OSEU_IntEquip_Process,  //  ((InteriorEquipment)) + "Process"             23
	OSEU_IntEquip_Refrig,   //  ((InteriorEquipment)) + "Refrig"              24
	OSEU_IntEquip_IntTrans, //  ((InteriorEquipment)) + "Internal Transport"  25   - SAC 8/19/14 - added for elevator/escalator power
	OSEU_Fans_PrkgGar,      //  ((Fans)) + "ParkingGarageFans"                26	 - SAC 1/30/17 - to be removed from Comp Fans and add into NonComp Process
	OSEU_NumEndUses
};
#define  OSWrap_NumEPlusEnduses  27

enum  OS_FuelType  // no direct mapping to OpenStudio, which includes wider array of fuels
{  OSF_Elec,       //  ((Electricity)(Electricity))
   OSF_Gas,        //  ((Gas)(Natural Gas))
   OSF_Other,      //  ((OtherFuel)(Other Fuel))
	OSF_NumFuels
};
#define  OSWrap_NumEPlusFuels  3

#define  MAX_NUM_QANALPERIODS      12
typedef struct
{
	long	m_iNumQuickAnalysisPeriods;
	double	m_fQuickAnalysisResultsMult;
	long	m_iQuickAnalysisPeriodBeginMonth[ MAX_NUM_QANALPERIODS ];	// only populated if NOT standard year (1/1-12/31)
	long	m_iQuickAnalysisPeriodBeginDay[   MAX_NUM_QANALPERIODS ];
	long	m_iQuickAnalysisPeriodEndMonth[   MAX_NUM_QANALPERIODS ];
	long	m_iQuickAnalysisPeriodEndDay[     MAX_NUM_QANALPERIODS ];
	long	m_iQuickAnalysisPeriodBeginDOWk[  MAX_NUM_QANALPERIODS ];  // DayOfWeek
					//  RunPeriod runPeriod = model.getUniqueModelObject<RunPeriod>();
					//  runPeriod.setBeginMonth(1);
					//  runPeriod.setBeginDayOfMonth(1);
					//  runPeriod.setEndMonth(12);
					//  runPeriod.setEndDayOfMonth(31);
} QuickAnalysisInfo;


typedef struct
{
	char pszSDDXMLFileName[FILENAME_MAX];
	char pszRunSubdir[FILENAME_MAX];
	char pszWeatherPathFile[FILENAME_MAX];
	char pszSQLOutPathFile[FILENAME_MAX];
	char pszIDFToSimulate[FILENAME_MAX];
	double* pdResults;
	bool bSimulateModel;
	bool bStoreHourlyResults;
	bool bWriteHourlyDebugCSV;
	long lRptFuelUseAs;		// SAC 10/28/15
	QuickAnalysisInfo* pQuickAnalysisInfo;
	int iProgressModel;
	int iSimReturnValue;
}	OSWrap_SimInfo;


// added to expand possible simulations from 2->5
#define  OSW_MaxNumSims  5

// settings that facilitate progress reporting - must align w/ corresponding settings in BEMCmpMgr - SAC 5/27/15
#define  OSW_NRP_AMult  100000000
#define  OSW_NRP_BMult    1000000
#define  OSW_NRP_CMult        100
#define  OSW_NRP_ComplianceProgressID(  lAnalType, lAnalStep, lModels, lSimProg )	(long) ( (lAnalType * OSW_NRP_AMult) + (lAnalStep * OSW_NRP_BMult) + (lModels * OSW_NRP_CMult) + lSimProg )

// B: analysis step
	#define	OSW_NRP_Step_MTrans		4	//	4-Translating Model(s)
	#define	OSW_NRP_Step_MSim			5	//	5-Simulating Model(s)
	#define	OSW_NRP_Step_MSimRes		6	//	6-Simulation Results
// END OF progress reporting defines


#define OSWFT_OSM		0
#define OSWFT_EPlus	1
#define OSWFT_GBXML	2

#define OSWrap_SimSDD_UserAbortedAnalysis		  1	//  was 6:  User aborted analysis											was 11
#define OSWrap_SimSDD_ProcPathNotValid			  2	//  was 3:  Simulation processing path not valid
#define OSWrap_SimSDD_SimEXEPathNotValid		  3	//  was 4:  Simulation executable path not valid						was 12
#define OSWrap_SimSDD_TooManySims				  4	//          Invalid number of concurrent simulations (max = 10)
#define OSWrap_SimSDD_NumSimsWithQuickRunErr	  5	//          Invalid combination of unique model & quick simulations (max 2 models when performing quick runs)

#define OSWrap_SimSDD_InputFileNotFound		 11	//  was 1:  SDD XML simulation input file not found
#define OSWrap_SimSDD_WthrFileNotFound			 12	//  was 2:  Simulation weather file not found
#define OSWrap_SimSDD_SimErrFileNotValid		 13	//  was 5:  Simulation error output path/file not valid				was 10
#define OSWrap_SimSDD_InvalidSimData			 14	//          Invalid simulation input data (run #1)
#define OSWrap_SimSDD_InputFile2NotFound		 21	//  was 7:  SDD XML simulation input file for second of run pair not found
#define OSWrap_SimSDD_WthrFile2NotFound		 22	//  was 8:  Simulation weather file for second of run pair not found
#define OSWrap_SimSDD_SimErrFile2NotValid		 23	//  was 9:  Simulation error output path/file for second of run pair not valid
#define OSWrap_SimSDD_InvalidSim2Data			 24	//          Invalid simulation input data (run #2)
#define OSWrap_SimSDD_InputFile3NotFound		 31	//          SDD XML simulation input file for third of run pair not found
#define OSWrap_SimSDD_WthrFile3NotFound		 32	//          Simulation weather file for third of run pair not found
#define OSWrap_SimSDD_SimErrFile3NotValid		 33	//          Simulation error output path/file for third of run pair not valid
#define OSWrap_SimSDD_InvalidSim3Data			 34	//          Invalid simulation input data (run #3)
#define OSWrap_SimSDD_InputFile4NotFound		 41	//          SDD XML simulation input file for fourth of run pair not found
#define OSWrap_SimSDD_WthrFile4NotFound		 42	//          Simulation weather file for fourth of run pair not found
#define OSWrap_SimSDD_SimErrFile4NotValid		 43	//          Simulation error output path/file for fourth of run pair not valid
#define OSWrap_SimSDD_InvalidSim4Data			 44	//          Invalid simulation input data (run #4)
#define OSWrap_SimSDD_InputFile5NotFound		 51	//          SDD XML simulation input file for fifth of run pair not found
#define OSWrap_SimSDD_WthrFile5NotFound		 52	//          Simulation weather file for fifth of run pair not found
#define OSWrap_SimSDD_SimErrFile5NotValid		 53	//          Simulation error output path/file for fifth of run pair not valid
#define OSWrap_SimSDD_InvalidSim5Data			 54	//          Invalid simulation input data (run #5)
#define OSWrap_SimSDD_InputFile6NotFound		 61	//          SDD XML simulation input file for sixth of run pair not found
#define OSWrap_SimSDD_WthrFile6NotFound		 62	//          Simulation weather file for sixth of run pair not found
#define OSWrap_SimSDD_SimErrFile6NotValid		 63	//          Simulation error output path/file for sixth of run pair not valid
#define OSWrap_SimSDD_InvalidSim6Data			 64	//          Invalid simulation input data (run #6)
#define OSWrap_SimSDD_InputFile7NotFound		 71	//          SDD XML simulation input file for seventh of run pair not found
#define OSWrap_SimSDD_WthrFile7NotFound		 72	//          Simulation weather file for seventh of run pair not found
#define OSWrap_SimSDD_SimErrFile7NotValid		 73	//          Simulation error output path/file for seventh of run pair not valid
#define OSWrap_SimSDD_InvalidSim7Data			 74	//          Invalid simulation input data (run #7)
#define OSWrap_SimSDD_InputFile8NotFound		 81	//          SDD XML simulation input file for eighth of run pair not found
#define OSWrap_SimSDD_WthrFile8NotFound		 82	//          Simulation weather file for eighth of run pair not found
#define OSWrap_SimSDD_SimErrFile8NotValid		 83	//          Simulation error output path/file for eighth of run pair not valid
#define OSWrap_SimSDD_InvalidSim8Data			 84	//          Invalid simulation input data (run #8)
#define OSWrap_SimSDD_InputFile9NotFound		 91	//          SDD XML simulation input file for ninth of run pair not found
#define OSWrap_SimSDD_WthrFile9NotFound		 92	//          Simulation weather file for ninth of run pair not found
#define OSWrap_SimSDD_SimErrFile9NotValid		 93	//          Simulation error output path/file for ninth of run pair not valid
#define OSWrap_SimSDD_InvalidSim9Data			 94	//          Invalid simulation input data (run #9)
#define OSWrap_SimSDD_InputFile10NotFound		101	//          SDD XML simulation input file for tenth of run pair not found
#define OSWrap_SimSDD_WthrFile10NotFound		102	//          Simulation weather file for tenth of run pair not found
#define OSWrap_SimSDD_SimErrFile10NotValid	103	//          Simulation error output path/file for tenth of run pair not valid
#define OSWrap_SimSDD_InvalidSim10Data			104	//          Invalid simulation input data (run #10)

#define OSWrap_SimSDD_OSLoadModelError			211		//  was 31:  Error encountered in OpenStudio loading SDD XML file				was 13
#define OSWrap_SimSDD_OSSaveOSMError			212		//  was 32:  Error encountered in OpenStudio saving model to OSM file		was 14
#define OSWrap_SimSDD_OSSimSQLOutNotFound		213		//  was 33:  Unable to locate EnergyPlus simulation SQL output file			was  6
#define OSWrap_SimSDD_OSModelNotValid			214		//  was 34:  OpenStudio Model not valid following simulation					was  5
#define OSWrap_SimSDD_OSFacilityNotValid		215		//  was 35:  OpenStudio Facility not valid following simulation				was  7
#define OSWrap_SimSDD_OSModelCreateError		216		//  was 36:  Error creating OpenStudio Model object								was  4
#define OSWrap_SimSDD_OSSaveIDFError			217		//  was 43:  Error encountered in OpenStudio saving (forward translated) IDF file
#define OSWrap_SimSDD_OSLoadModel2Error		221		//  was 37:  Error encountered in OpenStudio loading SDD XML file (second run)
#define OSWrap_SimSDD_OSSaveOSM2Error			222		//  was 38:  Error encountered in OpenStudio saving model to OSM file (second run)
#define OSWrap_SimSDD_OSSimSQL2OutNotFound	223		//  was 39:  Unable to locate EnergyPlus simulation SQL output file (second run)
#define OSWrap_SimSDD_OSModel2NotValid			224		//  was 40:  OpenStudio Model not valid following simulation (second run)
#define OSWrap_SimSDD_OSFacility2NotValid		225		//  was 41:  OpenStudio Facility not valid following simulation (second run)
#define OSWrap_SimSDD_OSModel2CreateError		226		//  was 42:  Error creating OpenStudio Model object (second run)
#define OSWrap_SimSDD_OSSaveIDF2Error			227		//  was 44:  Error encountered in OpenStudio saving (forward translated) IDF file (second run)
#define OSWrap_SimSDD_OSLoadModel3Error		231		//           Error encountered in OpenStudio loading SDD XML file (third run)
#define OSWrap_SimSDD_OSSaveOSM3Error			232		//           Error encountered in OpenStudio saving model to OSM file (third run)
#define OSWrap_SimSDD_OSSimSQL3OutNotFound	233		//           nable to locate EnergyPlus simulation SQL output file (third run)
#define OSWrap_SimSDD_OSModel3NotValid			234		//           tudio Model not valid following simulation (third run)
#define OSWrap_SimSDD_OSFacility3NotValid		235		//           tudio Facility not valid following simulation (third run)
#define OSWrap_SimSDD_OSModel3CreateError		236		//           Error creating OpenStudio Model object (third run)
#define OSWrap_SimSDD_OSSaveIDF3Error			237		//           Error encountered in OpenStudio saving (forward translated) IDF file (third run)
#define OSWrap_SimSDD_OSLoadModel4Error		241		//           Error encountered in OpenStudio loading SDD XML file (fourth run)
#define OSWrap_SimSDD_OSSaveOSM4Error			242		//           Error encountered in OpenStudio saving model to OSM file (fourth run)
#define OSWrap_SimSDD_OSSimSQL4OutNotFound	243		//           nable to locate EnergyPlus simulation SQL output file (fourth run)
#define OSWrap_SimSDD_OSModel4NotValid			244		//           tudio Model not valid following simulation (fourth run)
#define OSWrap_SimSDD_OSFacility4NotValid		245		//           tudio Facility not valid following simulation (fourth run)
#define OSWrap_SimSDD_OSModel4CreateError		246		//           Error creating OpenStudio Model object (fourth run)
#define OSWrap_SimSDD_OSSaveIDF4Error			247		//           Error encountered in OpenStudio saving (forward translated) IDF file (fourth run)
#define OSWrap_SimSDD_OSLoadModel5Error		251		//           Error encountered in OpenStudio loading SDD XML file (fifth run)
#define OSWrap_SimSDD_OSSaveOSM5Error			252		//           Error encountered in OpenStudio saving model to OSM file (fifth run)
#define OSWrap_SimSDD_OSSimSQL5OutNotFound	253		//           nable to locate EnergyPlus simulation SQL output file (fifth run)
#define OSWrap_SimSDD_OSModel5NotValid			254		//           tudio Model not valid following simulation (fifth run)
#define OSWrap_SimSDD_OSFacility5NotValid		255		//           tudio Facility not valid following simulation (fifth run)
#define OSWrap_SimSDD_OSModel5CreateError		256		//           Error creating OpenStudio Model object (fifth run)
#define OSWrap_SimSDD_OSSaveIDF5Error			257		//           Error encountered in OpenStudio saving (forward translated) IDF file (fifth run)
#define OSWrap_SimSDD_OSLoadModel6Error		261		//           Error encountered in OpenStudio loading SDD XML file (sixth run)
#define OSWrap_SimSDD_OSSaveOSM6Error			262		//           Error encountered in OpenStudio saving model to OSM file (sixth run)
#define OSWrap_SimSDD_OSSimSQL6OutNotFound	263		//           Unable to locate EnergyPlus simulation SQL output file (sixth run)
#define OSWrap_SimSDD_OSModel6NotValid			264		//           OpenStudio Model not valid following simulation (sixth run)
#define OSWrap_SimSDD_OSFacility6NotValid		265		//           OpenStudio Facility not valid following simulation (sixth run)
#define OSWrap_SimSDD_OSModel6CreateError		266		//           Error creating OpenStudio Model object (sixth run)
#define OSWrap_SimSDD_OSSaveIDF6Error			267		//           Error encountered in OpenStudio saving (forward translated) IDF file (sixth run)
#define OSWrap_SimSDD_OSLoadModel7Error		271		//           Error encountered in OpenStudio loading SDD XML file (seventh run)
#define OSWrap_SimSDD_OSSaveOSM7Error			272		//           Error encountered in OpenStudio saving model to OSM file (seventh run)
#define OSWrap_SimSDD_OSSimSQL7OutNotFound	273		//           Unable to locate EnergyPlus simulation SQL output file (seventh run)
#define OSWrap_SimSDD_OSModel7NotValid			274		//           OpenStudio Model not valid following simulation (seventh run)
#define OSWrap_SimSDD_OSFacility7NotValid		275		//           OpenStudio Facility not valid following simulation (seventh run)
#define OSWrap_SimSDD_OSModel7CreateError		276		//           Error creating OpenStudio Model object (seventh run)
#define OSWrap_SimSDD_OSSaveIDF7Error			277		//           Error encountered in OpenStudio saving (forward translated) IDF file (seventh run)
#define OSWrap_SimSDD_OSLoadModel8Error		281		//           Error encountered in OpenStudio loading SDD XML file (eighth run)
#define OSWrap_SimSDD_OSSaveOSM8Error			282		//           Error encountered in OpenStudio saving model to OSM file (eighth run)
#define OSWrap_SimSDD_OSSimSQL8OutNotFound	283		//           Unable to locate EnergyPlus simulation SQL output file (eighth run)
#define OSWrap_SimSDD_OSModel8NotValid			284		//           OpenStudio Model not valid following simulation (eighth run)
#define OSWrap_SimSDD_OSFacility8NotValid		285		//           OpenStudio Facility not valid following simulation (eighth run)
#define OSWrap_SimSDD_OSModel8CreateError		286		//           Error creating OpenStudio Model object (eighth run)
#define OSWrap_SimSDD_OSSaveIDF8Error			287		//           Error encountered in OpenStudio saving (forward translated) IDF file (eighth run)
#define OSWrap_SimSDD_OSLoadModel9Error		291		//           Error encountered in OpenStudio loading SDD XML file (ninth run)
#define OSWrap_SimSDD_OSSaveOSM9Error			292		//           Error encountered in OpenStudio saving model to OSM file (ninth run)
#define OSWrap_SimSDD_OSSimSQL9OutNotFound	293		//           Unable to locate EnergyPlus simulation SQL output file (ninth run)
#define OSWrap_SimSDD_OSModel9NotValid			294		//           OpenStudio Model not valid following simulation (ninth run)
#define OSWrap_SimSDD_OSFacility9NotValid		295		//           OpenStudio Facility not valid following simulation (ninth run)
#define OSWrap_SimSDD_OSModel9CreateError		296		//           Error creating OpenStudio Model object (ninth run)
#define OSWrap_SimSDD_OSSaveIDF9Error			297		//           Error encountered in OpenStudio saving (forward translated) IDF file (ninth run)
#define OSWrap_SimSDD_OSLoadModel10Error		301		//           Error encountered in OpenStudio loading SDD XML file (tenth run)
#define OSWrap_SimSDD_OSSaveOSM10Error			302		//           Error encountered in OpenStudio saving model to OSM file (tenth run)
#define OSWrap_SimSDD_OSSimSQL10OutNotFound	303		//           Unable to locate EnergyPlus simulation SQL output file (tenth run)
#define OSWrap_SimSDD_OSModel10NotValid		304		//           OpenStudio Model not valid following simulation (tenth run)
#define OSWrap_SimSDD_OSFacility10NotValid	305		//           OpenStudio Facility not valid following simulation (tenth run)
#define OSWrap_SimSDD_OSModel10CreateError	306		//           Error creating OpenStudio Model object (tenth run)
#define OSWrap_SimSDD_OSSaveIDF10Error			307		//           Error encountered in OpenStudio saving (forward translated) IDF file (tenth run)

#define OSWrap_SimSDD_SimFatalError				411		//  was 61:  Fatal error(s) ocurred in EnergyPlus simulation					was  8
#define OSWrap_SimSDD_SimIncomplete				412		//  was 62:  EnergyPlus simulation did not complete successfully				was  9
#define OSWrap_SimSDD_Sim2FatalError			416		//  was 63:  Fatal error(s) ocurred in EnergyPlus simulation (second run)
#define OSWrap_SimSDD_Sim2Incomplete			417		//  was 64:  EnergyPlus simulation did not complete successfully (second run)
#define OSWrap_SimSDD_Sim3FatalError			421		//           Fatal error(s) ocurred in EnergyPlus simulation (third run)
#define OSWrap_SimSDD_Sim3Incomplete			422		//           EnergyPlus simulation did not complete successfully (third run)
#define OSWrap_SimSDD_Sim4FatalError			426		//           Fatal error(s) ocurred in EnergyPlus simulation (fourth run)
#define OSWrap_SimSDD_Sim4Incomplete			427		//           EnergyPlus simulation did not complete successfully (fourth run)
#define OSWrap_SimSDD_Sim5FatalError			431		//           Fatal error(s) ocurred in EnergyPlus simulation (fifth run)
#define OSWrap_SimSDD_Sim5Incomplete			432		//           EnergyPlus simulation did not complete successfully (fifth run)
#define OSWrap_SimSDD_Sim6FatalError			436		//           Fatal error(s) ocurred in EnergyPlus simulation (sixth run)
#define OSWrap_SimSDD_Sim6Incomplete			437		//           EnergyPlus simulation did not complete successfully (sixth run)
#define OSWrap_SimSDD_Sim7FatalError			441		//           Fatal error(s) ocurred in EnergyPlus simulation (seventh run)
#define OSWrap_SimSDD_Sim7Incomplete			442		//           EnergyPlus simulation did not complete successfully (seventh run)
#define OSWrap_SimSDD_Sim8FatalError			446		//           Fatal error(s) ocurred in EnergyPlus simulation (eighth run)
#define OSWrap_SimSDD_Sim8Incomplete			447		//           EnergyPlus simulation did not complete successfully (eighth run)
#define OSWrap_SimSDD_Sim9FatalError			451		//           Fatal error(s) ocurred in EnergyPlus simulation (ninth run)
#define OSWrap_SimSDD_Sim9Incomplete			452		//           EnergyPlus simulation did not complete successfully (ninth run)
#define OSWrap_SimSDD_Sim10FatalError			456		//           Fatal error(s) ocurred in EnergyPlus simulation (tenth run)
#define OSWrap_SimSDD_Sim10Incomplete			457		//           EnergyPlus simulation did not complete successfully (tenth run)


namespace OS_Wrap {


	struct OSWrapLibData
	{
	               std::string    sSimErrPathFile;
	               std::string    sSimVersionID;
	   std::vector<std::string>   saSimWarnings;
	   std::vector<std::string>   saSimSevereErrors;
	   std::vector<std::string>   saSimFatalErrors;
						bool				bSimCompleted;
						bool				bSimCompletedSuccessfully;

		std::vector<std::string>	saZone;
		std::vector<double>			daZone_UMLHClg;
		std::vector<double>			daZone_UMLHHtg;
		std::vector<double>			daZone_ClgDsgnLd;
		std::vector<double>			daZone_HtgDsgnLd;
		std::vector<double>			daZone_ClgDsgnFlow;
		std::vector<double>			daZone_HtgDsgnFlow;

	   std::vector<std::string>   saFan;
		std::vector<double>			daFan_FlowCap;

	   std::vector<std::string>   saCoilClg;
		std::vector<double>			daCoilClg_TotCap;
		std::vector<double>			daCoilClg_SensCap;
	//	std::vector<double>			daCoilClg_FluidLdDsgn;	// TO BE REMOVED
		std::vector<double>			daCoilClg_FluidFlowRtDsgnSim;		// SAC 11/26/13 - added

	   std::vector<std::string>   saCoilHtg;
		std::vector<double>			daCoilHtg_TotCap;
	//	std::vector<double>			daCoilHtg_FluidLdDsgn;	// TO BE REMOVED
		std::vector<double>			daCoilHlg_FluidFlowRtDsgnSim;		// SAC 11/26/13 - added

	   std::vector<std::string>   saBlr;				// SAC 8/28/13 - added Blr, Chlr, HtRej & Pump results
		std::vector<double>			daBlr_CapRtd;
	//	std::vector<double>			daBlr_HtgRtPk;  // SAC 12/9/13 - from hourly results

	   std::vector<std::string>   saChlr;
		std::vector<double>			daChlr_CapRtd;
	//	std::vector<double>			daChlr_EvapClgRtPk;  // SAC 12/9/13 - from hourly results

	   std::vector<std::string>   saHtRej;
		std::vector<double>			daHtRej_CapRtd;
	//	std::vector<double>			daHtRej_HtTransRtPk;  // SAC 12/9/13 - from hourly results

	   std::vector<std::string>   saPump;
		std::vector<double>			daPump_FlowCap;

						bool				bHourlyResultsCurrent;
		std::vector<double>			daHourlyResults[   OSWrap_NumEPlusFuels][OSWrap_NumEPlusEnduses];  // Fuel / Enduse
						double			daHourlyResultsSum[OSWrap_NumEPlusFuels][OSWrap_NumEPlusEnduses];  // Fuel / Enduse
   };


  class __declspec(dllexport) OSWrapLib {

	public:
//		OSWrapLib();
////		virtual ~OSWrapLib();
      OSWrapLib() //: pData[0](new OSWrapLibData) {
                  //      if (pData[0])
						//			pData[0]->bHourlyResultsCurrent = false;
							{	for (int i=0; i<OSW_MaxNumSims; i++)
								{	pData[i] = new OSWrapLibData();
                        	if (pData[i])
										pData[i]->bHourlyResultsCurrent = false;
							}	}
      ~OSWrapLib() { for (int i=0; i<OSW_MaxNumSims; i++)
      						delete pData[i];
							}
      //~OSWrapLib() { this->!OSWrapLib(); }
      //!OSWrapLib() { //Cleanup...();
      //               //Cleanup...();
      //                  delete pData; }


      // return values:  0 => SUCCESS
      //                >0 => Number of BDL file writing commands that were unrecognized
      //                -1 => failure to initialize BDLWriteStruct
      long SDDtoOSM( const char* pszSDDXMLFileName );

		int		InitZoneData(   int iRunIdx );
		std::string GetZoneName( int iRunIdx, int idx );
		void		SetZoneData(    int iRunIdx, int idx, int iDataIdx, double dVal );
      int		AddResult_Zone( int iRunIdx, const char* pszZoneName );
		int		GetResult_Zone( int iRunIdx, int idx, double* pfZoneResults, int iNumResults );
      double	GetResult_ZoneUMLHClg( int iRunIdx, int idx );
      double	GetResult_ZoneUMLHHtg( int iRunIdx, int idx );

		int			InitFanData( int iRunIdx );
		std::string GetFanName(  int iRunIdx, int idx );
		void		SetFanData(     int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_Fan( int iRunIdx, const char* pszFanName );
		int		GetResult_Fan( int iRunIdx, int idx, double* pfFanResults, int iNumResults );

		int			InitCoilClgData( int iRunIdx );
		std::string GetCoilClgName(  int iRunIdx, int idx );
		void		SetCoilClgData( int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_CoilClg( int iRunIdx, const char* pszCoilClgName );
		int		GetResult_CoilClg( int iRunIdx, int idx, double* pfCoilClgResults, int iNumResults );

		int			InitCoilHtgData( int iRunIdx );
		std::string GetCoilHtgName(  int iRunIdx, int idx );
		void		SetCoilHtgData( int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_CoilHtg( int iRunIdx, const char* pszCoilHtgName );
		int		GetResult_CoilHtg( int iRunIdx, int idx, double* pfCoilHtgResults, int iNumResults );

		int			InitBlrData( int iRunIdx );
		std::string GetBlrName(  int iRunIdx, int idx );
		void		SetBlrData(     int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_Blr( int iRunIdx, const char* pszBlrName );
		int		GetResult_Blr( int iRunIdx, int idx, double* pfBlrResults, int iNumResults );

		int			InitChlrData( int iRunIdx );
		std::string GetChlrName(  int iRunIdx, int idx );
		void		SetChlrData(    int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_Chlr( int iRunIdx, const char* pszChlrName );
		int		GetResult_Chlr( int iRunIdx, int idx, double* pfChlrResults, int iNumResults );

		int			InitHtRejData( int iRunIdx );
		std::string GetHtRejName(  int iRunIdx, int idx );
		void		SetHtRejData(   int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_HtRej( int iRunIdx, const char* pszHtRejName );
		int		GetResult_HtRej( int iRunIdx, int idx, double* pfHtRejResults, int iNumResults );

		int			InitPumpData( int iRunIdx );
		std::string GetPumpName(  int iRunIdx, int idx );
		void		SetPumpData(    int iRunIdx, int idx, int iDataIdx, double dVal );
		int      AddResult_Pump( int iRunIdx, const char* pszPumpName );
		int		GetResult_Pump( int iRunIdx, int idx, double* pfPumpResults, int iNumResults );


		std::vector<double>*		GetHourlyResultArray( int iRunIdx, int iFuel, int iEnduse, double* pdTotal );
		void		SumIntoHourlyResult( int iRunIdx, int iFuel, int iEnduse, int iHr, double dVal );
		void		AdjustAndSumHourlyResults( int iRunIdx, double* daFuelConvert );

		int		GetNum_Warnings(				int iRunIdx );
		int		GetNum_SevereErrors(			int iRunIdx );
		int		GetNum_FatalErrors(			int iRunIdx );
		std::string		GetMsg_Warning(		int iRunIdx, int idx );
		std::string		GetMsg_SevereError(	int iRunIdx, int idx );
		std::string		GetMsg_FatalError(	int iRunIdx, int idx );
		std::string		Get_SimErrPathFile(	int iRunIdx );
		std::string		Get_SimVersionID(		int iRunIdx );	// SAC 5/19/14
		bool		GetBool_SimCompleted(		int iRunIdx );
		bool		GetBool_SimCompletedSuccessfully( int iRunIdx );

		long TranslateToSDD( const char* pszInputPathFile, const char* pszOutputPathFile, int iInputType );  // SAC 1/10/14

		std::string GetOpenStudioVersion( bool bLongVersion );
		double	EnergyPlusVersion( const char* pszEPlusPath=NULL );
//		bool		EnergyPlusVersionInstalled( int iMajor, int iMinor=-1, int iBuild=-1 );  // SAC 12/27/13
		void		InitHourlyResults( int iRunIdx );	// SAC 4/17/14

		long SimulateSDD( const char* pszEPlusPath, const char* pszProcessingPath,
							// RUN #1 data
								const char* pszSDDXMLFileName, const char* pszRunSubdir,
								const char* pszWeatherPathFile, double* pdResults, bool bSimulateModel=true,
							   bool bStoreHourlyResults=true, char* pszSQLOutPathFile=0, int iMaxLenSQLOutPathFile=0,
							   bool bWriteHourlyDebugCSV=false, const char* pszIDFToSimulate=NULL,
							   QuickAnalysisInfo* pQuickAnalysisInfo=NULL, int iProgressModel=0,	// SAC 11/6/14
							// RUN #2 data
								const char* pszSDDXMLFile2=NULL, const char* pszRunSubdir2=NULL,
								const char* pszWeatherPathFile2=NULL, double* pdResults2=NULL, bool bSimulateModel2=true,
								bool bStoreHourlyResults2=true, char* pszSQLOutPathFile2=NULL, int iMaxLenSQLOutPathFile2=0,
								bool bWriteHourlyDebugCSV2=false, const char* pszIDFToSimulate2=NULL,  // SAC 1/25/14
							   QuickAnalysisInfo* pQuickAnalysisInfo2=NULL, int iProgressModel2=0,	// SAC 11/6/14
							// general data
								OSWRAP_MSGCALLBACK* pMsgCallback=NULL, int iMsgCallbackType=0, double* pdTranslationTime=NULL,
								double* pdSimulationTime=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0,
								bool bOutputDiagnostics=false, int iCodeType=0 );		// SAC 4/2/15   // SAC 8/20/15

		long SimulateSDD_Multiple( const char* pszEPlusPath, const char* pszProcessingPath,
								OSWrap_SimInfo** paSDDSimInfo, int iNumSDDSimInfo,
								OSWRAP_MSGCALLBACK* pMsgCallback=NULL, int iMsgCallbackType=0, double* pdTranslationTime=NULL,
								double* pdSimulationTime=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0,
								bool bOutputDiagnostics=false, int iCodeType=0 );		// SAC 7/19/15   // SAC 8/20/15

// TESTING/DEBUGGING
		long HourlyResultsRetrieval( const char* pszOSMPathFile, const char* pszSQLPathFile );

	private:
      OSWrapLibData* pData[OSW_MaxNumSims];
      //OSWrapLibData* pData2;


//	public struct OSWrapLibData
//	{
//      char m_sProjFile[ 261 ];
//
//   };
//
//	public ref class OSWrapLib
//	{
//   public:
//      OSWrapLib() : pData(new OSWrapLibData) {
//                        if (pData)
//                        {  
//                        }
//                      }
//      ~OSWrapLib() { this->!OSWrapLib(); }
//      !OSWrapLib() { //Cleanup...();
//                     //Cleanup...();
//                        delete pData; }
//
//      // return values:  0 => SUCCESS
//      //                >0 => Number of BDL file writing commands that were unrecognized
//      //                -1 => failure to initialize BDLWriteStruct
//      long SDDtoOSM( String ^sSDDXMLFileName );
//
//   private:
//      OSWrapLibData* pData;
	};
}
