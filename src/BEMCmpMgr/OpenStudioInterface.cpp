// OpenStudioInterface.cpp : 
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
#include "EPlusRunMgr.h"
#include "BEMCmpMgrProgress.h"   // SAC 06/20/22

using namespace OS_Wrap;


// const char* pszEPlusEndUseCategs[] = {	"Heating",         // 0   - SAC 7/20/18 - never referenced
// 													"Cooling",         // 1
// 													"Int Lights",      // 2
// 													"Ext Lights",      // 3
// 													"Int Equipment",   // 4
// 													"Ext Equipment",   // 5
// 													"Fans",            // 6
// 													"Pumps",           // 7
// 													"HeatRejection",   // 8
// 													"Humidifier",      // 9
// 													"HeatRecovery",    // 10
// 													"WaterSystems",    // 11
// 													"Refrigeration",   // 12
// 													"Generators" };    // 13
// static int siEndUsesToReport[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, -1 };   - SAC 7/20/18 - never referenced
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

// SAC 10/13/15 - switched 'Process Ltg' to 'Other Ltg'
													                                                                                                                                              // SumInto                                                                                                                                      Res Totals
EndUseMap esEUMap_CECNonRes[] =                                         // enduses...                                                                                                   Compliance   daEnduseTotal    daTDVTotal       daSrcTotal       daSrcPrmTotal    daCO2Total       daTDSTotal       daSupply         EDem     daResEnduseTotal daResTDVTotal    daResSrcTotal    daResSrcPrmTotal daResCO2Total    daResTDSTotal    daResSupply      ResEDem
{	{  "Space Heating"         ,  "ResSpace Heating"      ,  "Spc Heat"  ,  OSEU_Heating,           OSEU_HtgCoils,         OSEU_Baseboard,    OSEU_HtRecov_Htg,    OSEU_Boilers,  -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Space Cooling"         ,  "ResSpace Cooling"      ,  "Spc Cool"  ,  OSEU_Cooling,           OSEU_ClgCoils,         OSEU_HtRecov_Clg,        -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Indoor Fans"           ,  "ResIndoor Fans"        ,  "Indr Fans" ,  OSEU_Fans,                    -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Heat Rejection"        ,  "ResHeat Rejection"     ,  "Heat Rej"  ,  OSEU_HtReject,                -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Pumps & Misc."         ,  "ResPumps & Misc."      ,  "Pump&Misc" ,  OSEU_Pumps,             OSEU_HtRecov,          OSEU_Humid,              -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
//	{  "Domestic HW"           ,  "ResDomestic HW"        ,  "Dom HW"    ,  OSEU_WaterSystems,            -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Domestic Hot Water"    ,  "ResDomestic Hot Water" ,  "Dom HW"    ,  OSEU_WaterSystems,            -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
//	{  "Lighting"              ,  "ResLighting"           ,  "Lighting"  ,  OSEU_IntLights_Reg,           -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Indoor Lighting"       ,  "ResIndoor Lighting"    ,  "Lighting"  ,  OSEU_IntLights_Comp,          -1,                    -1,                -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Total Compliance"      ,  "Total Compliance"      ,  "Tot Comp"  ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// SAC 11/5/19 - to camel case to allow screen display
	{  "Receptacle"            ,  "ResReceptacle"         ,  "Recept"    ,  OSEU_IntEquip_Recept,         -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Process"               ,  "ResProcess"            ,  "Process"   ,  OSEU_IntEquip_Process,  OSEU_IntEquip_Refrig,  OSEU_Refrig,       OSEU_IntEquip_IntTrans,   -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// SAC 8/19/14 - added OSEU_IntEquip_IntTrans to capture elevator/escalator energy use
	{  "Other Ltg"             ,  "ResOther Ltg"          ,  "Othr Ltg"  ,  OSEU_IntLights_NonComp,       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Process Motors"        ,  "ResProcess Motors"     ,  "Proc Mtrs" ,  OSEU_Fans_ProcMtrs,           -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// SAC 2/1/17 - added Process Motors to capture parking garage exhaust fans (tic #2033)  // SAC 8/14/17 - switched OSEU_Fans_PrkgGar to OSEU_Fans_ProcMtrs
	{  "Photovoltaics"         ,  "Photovoltaics"         ,  "PV"        ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// SAC 7/14/18
	{  "Battery"               ,  "Battery"               ,  "Battery"   ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// SAC 7/14/18
	{  "TOTAL"                 ,  "TOTAL"                 ,  "TOTAL"     ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },
	{  "Efficiency Compliance" ,  "Efficiency Compliance" ,  "Eff Comp"  ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   },		// added to enable 2022 analysis - SAC 12/11/21
	{  NULL                    ,  NULL                    ,  NULL        ,      -1,                       -1,                    -1,                -1,                 -1,       -1,        0,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0,     0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0   }  };
                                                                                                                           // FINAL enduse index must be '-1' for each record

const char* pszaEPlusFuelNames[] = {		"Electricity",    // OSF_Elec,    //  ((Electricity)(Electricity))
														"NaturalGas" ,    // OSF_Gas,     //  ((Gas)(Natural Gas))        
														"OtherFuel"   };  // OSF_Other,   //  ((OtherFuel)(Other Fuel))   
static const char* pszaFuelPropName[] = {		"Elec",
															"NatGas",
															"Other"   };

const char*  pszCSEMtrNames[]    = { "MtrElec", "MtrNatGas", "MtrOther" };		// SAC 10/8/20 (tic #3218)
static double daCSEMtrTDVMults[] = { 1/3.412 /*kBtu->kWh*/,  0.01 /*kBtu->therm*/,  0.01 /*kBtu->therm*/ };		// (CSE kBTU * TDV Mult) conversion to kTDV - SAC 10/8/20 (tic #3218)
const char*  pszCSEDHWEnduseList[] = { /*"Tot", "Clg", "Htg", "HPBU",*/ "Dhw", "DhwBU", "DhwMFL", /*"FanC", "FanH", "FanV", "Fan", "Aux", "Proc", "Lit", "Rcp", "Ext", "Refr", "Dish", "Dry", "Wash", "Cook",*/ "User2", /*"User2", "PV", "BT",*/ NULL };	// added to facilitate retrieval of Res DHW separate from other enduses - SAC 10/8/20 (tic #3218)

static double dHrlyRes[8760];
static double dHrlyResCompTot[8760];
static double dHrlyResTot[8760];
static double dStdResDHWHrlyRes[8760];		// SAC 10/8/20 (tic #3218)
static void InitHrlyRes( double* pRes )
{	for (int hr=0; hr<8760; hr++)
		pRes[hr] = 0.0;
}

static double SumHrlyRes( double* pRes )
{	double dRes=0.0;
	for (int hr=0; hr<8760; hr++)
		dRes += pRes[hr];
	return dRes;
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
                           BEMPX_GetDBComponentID( "ResOtherZn" ),      // SAC 05/12/22 (MFam)
									0, -99  };
#define  MAX_RESCOPY_DBIDSPEROBJ  6
		const char* pszPropNames[9][MAX_RESCOPY_DBIDSPEROBJ] = {	{	"ClgDsgnLd"        , "HtgDsgnLd"         , "ClgDsgnFlowSim", "HtgDsgnFlowSim",  NULL,  NULL  },
																					{	"FlowCapSim"       ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapTotGrossRtdSim", "CapSensGrossRtdSim",  NULL           ,  NULL           ,  NULL,  NULL  }, 
																					{	"CapTotGrossRtdSim",  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"CapRtdSim"        ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"FlowCapSim"       ,  NULL               ,  NULL           ,  NULL           ,  NULL,  NULL  },
																					{	"ClgDsgnLd"        , "HtgDsgnLd"         , "ClgDsgnFlowSim", "HtgDsgnFlowSim",  NULL,  NULL  }  };
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
								{	// assert( FALSE );	// allow not all results to be retrieved
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
												bool bSimulateModel, int iBEMProcIdx /*=-1*/, const char* pszIDFToSimulate /*=NULL*/, int iCodeType /*=CT_T24N*/, bool bSimOutVarsCSV /*=false*/,
												bool bEvalReportRulesFollowingSim /*=false*/, bool bSkippingEPlusSim /*=false*/ )
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
            //BEMPX_WriteLogFile( QString( "   COSRunInfo::InitializeRunInfo() - setting m_bStoreHourlyResults to %1" ).arg( (m_bStoreHourlyResults ? "true" : "false") ) );

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
            //BEMPX_WriteLogFile( QString( "   COSRunInfo::InitializeRunInfo() - setting m_bStoreHourlyResults to false (pOSWrap = NULL)" ), NULL, FALSE, TRUE, FALSE );
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
	m_bEvalReportRulesFollowingSim = bEvalReportRulesFollowingSim;	// SAC 2/18/20
   m_bSkippingEPlusSim = bSkippingEPlusSim;  // SAC 12/08/21

	m_lRptFuelUseAs = -1;	// SAC 10/28/15
	long lRFUA;
	if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "RptFuelUseAs", iCID_Proj ), lRFUA, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lRFUA >= 0)
		m_lRptFuelUseAs = lRFUA;

	long lRPYr;		// SAC 3/1/19
	if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodYear", iCID_Proj ), lRPYr, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lRPYr > 0)
		m_lRunPeriodYear = lRPYr;
	else
		m_lRunPeriodYear = -1;

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
	double dDelta = (dVal < 0 ? -0.5 : 0.5);	// SAC 9/14/19 (tic #3106)
	switch (iDecPrec)
	{	case -3 :	dRetVal = (double) ((int) ((dVal /   1000.0) + dDelta)) *   1000.0;		break;
		case -2 :	dRetVal = (double) ((int) ((dVal /    100.0) + dDelta)) *    100.0;		break;
		case -1 :	dRetVal = (double) ((int) ((dVal /     10.0) + dDelta)) *     10.0;		break;
		case  0 :	dRetVal = (double) ((int) ((dVal           ) + dDelta))           ;		break;
		case  1 :	dRetVal = (double) ((int) ((dVal *     10.0) + dDelta)) /     10.0;		break;
		case  2 :	dRetVal = (double) ((int) ((dVal *    100.0) + dDelta)) /    100.0;		break;
		case  3 :	dRetVal = (double) ((int) ((dVal *   1000.0) + dDelta)) /   1000.0;		break;
		case  4 :	dRetVal = (double) ((int) ((dVal *  10000.0) + dDelta)) /  10000.0;		break;
		case  5 :	dRetVal = (double) ((int) ((dVal * 100000.0) + dDelta)) / 100000.0;		break;
		default :	assert( FALSE );		break;
	}
	return dRetVal;
}


// SAC 4/17/14 - moved ALL results processing to this subordinate routine
// SAC 7/23/18 - split ProcessSimulationResults() into two separate routines:
//						RetrieveSimulationResults() to retrieve hourly results and process ReadVarsESO requests, and
//						ProcessNonresSimulationResults() to perform TDV calcs, UMLH checks, cr8/edit EnergyUse and EUseSummary objects, etc.
//BOOL ProcessSimulationResults( OSWrapLib& osWrap, COSRunInfo& osRunInfo, int& iRetVal, const char* pszSimProcessDir, BOOL bVerbose, int iSimulationStorage, const char* pszEPlusPath )
BOOL RetrieveSimulationResults( OSWrapLib& osWrap, COSRunInfo& osRunInfo, int& iRetVal, const char* pszSimProcessDir, BOOL bVerbose, int iSimulationStorage, const char* pszEPlusPath )
{
	BOOL bRetVal = TRUE;
	QString sLogMsg, sTemp;

		if (osRunInfo.StoreHourlyResults() && iRetVal == 0)
		{							if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Pulling/grouping/summing hourly results from OSWrap", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   		long lEngyCodeYearNum;		// SAC 12/12/21
   		BEMPX_GetInteger(BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum"), lEngyCodeYearNum, 2019, -1, -1, BEMO_User, osRunInfo.BEMProcIdx());			assert( lEngyCodeYearNum > 0 );
			int iCID_EnergyUse = BEMPX_GetDBComponentID( "EnergyUse" );		assert( iCID_EnergyUse > 0 );
			int iEUIdx, iFl, hr /*, iError*/;
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
					esEUMap_CECNonRes[iEUIdx].daSrcTotal[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daCO2Total[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daTDSTotal[   iFl] = 0.0;
					if (iFl==0)  // SAC 10/8/16
					{	esEUMap_CECNonRes[iEUIdx].dElecDemand = 0.0;
						esEUMap_CECNonRes[iEUIdx].daSupply[0] = 0.0;		// SAC 9/7/18 - A2030 [Elec,TDV,TDS]
						esEUMap_CECNonRes[iEUIdx].daSupply[1] = 0.0;
						esEUMap_CECNonRes[iEUIdx].daSupply[2] = 0.0;
				}	}
			}
			for (iFl=0; iFl < OSF_NumFuels; iFl++)
			{
//BEMPX_WriteLogFile( QString( "   Process hourly results for Fuel %1 (%2)" ).arg( QString::number( iFl ), (iFl==0 ? "Elec" : (iFl==1 ? "Gas" : "Other" )) ) );
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
//BEMPX_WriteLogFile( QString( "      Enduse: %1 (%2) - Total use: %3" ).arg( esEUMap_CECNonRes[iEUIdx].sEnduseAbbrev, QString::number( iEUIdx ), QString::number( esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] ) ) );
//"Space Cooling"      ,  "Spc Cool"  ,  OSEU_Cooling,           OSEU_ClgCoils,         OSEU_HtRecov_Clg,        -1,                 -1,       -1,        1,       0.0, 0.0, 0.0,   0.0, 0.0, 0.0   },
					if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot && iEUIdx != IDX_T24_NRES_EU_Total && esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0)  // SAC 7/15/18 - '>0' -> '!=0' to allow for negative (PV/Batt) enduses
					{
							esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
						if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
							esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
                  if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
							esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
					}

					if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot && iEUIdx != IDX_T24_NRES_EU_Total)
					//{	double dResult = BEMPX_AddHourlyResultArray( dHrlyRes, pszLongRunID, pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, -1 /*iBEMProcIdx*/, TRUE /*bAddIfNoExist*/ );
					{	double dResult = BEMPX_SumIntoHourlyResultArray( dHrlyRes, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, osRunInfo.BEMProcIdx(), TRUE /*bAddIfNoExist*/ );		dResult;
						// not the case when preliminary simulation results in some simulation results being populated prior to retrieval of these -- assert( WithinMargin( dResult, esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl], (max( fabs(dResult), fabs(esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl]) )/1000.0) ) );  // dResult == esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] );
					//	if (dResult == -99999)
					//	{	ExpSetErr( error, EXP_RuleProc, "Error adding hourly result array within ApplyHourlyResultMultipliers() function." );
					//		break;
					//	}
					}
				}	// end of: while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
			}	// end of: for iFl=0-OSF_NumFuels
		}	// end of: if (osRunInfo.StoreHourlyResults()


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
				{
					boost::posix_time::ptime tmCSVStartTime = boost::posix_time::microsec_clock::local_time();	// SAC 5/22/19

					QString sSimOutVarsFreq;
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

					if (bVerbose)
					{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmCSVStartTime;	// SAC 5/22/19
						double dCSVTime = ((double) td.total_microseconds()) / 1000000.0;
						QString sCSVTimeMsg = QString::asprintf( "     SimOutVarsToCSV Processing time:  %.3f sec", dCSVTime );
						BEMPX_WriteLogFile( sCSVTimeMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
			}	}

	//		QString sEPlusOutPath = QString::asprintf( "%s%s\\EnergyPlus\\", sProcessingPath, osSimInfo[iSimRun].pszRunID );
	//		QString sSimOutVarsCSVPathFile = sProcessingPath;
	//		sSimOutVarsCSVPathFile += osRunInfo[iSimRun].SDDFile();								assert( sSimOutVarsCSVPathFile.lastIndexOf('.') > 0 );
	//		if (sSimOutVarsCSVPathFile.lastIndexOf('.') > 0)
	//			sSimOutVarsCSVPathFile = sSimOutVarsCSVPathFile.left( sSimOutVarsCSVPathFile.lastIndexOf('.') );
	//		sSimOutVarsCSVPathFile += " - OutputVars.csv";
	//		QString sOverwriteMsg;
	//		sLogMsg.clear();
	//		sOverwriteMsg = QString::asprintf( "The CSV file '%s' is opened in another application.  This file must be closed in that "
	//										"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
	//										"(once the file is closed), or \n'Cancel' to abort the analysis.", sSimOutVarsCSVPathFile );
	//		if (!OKToWriteOrDeleteFile( sSimOutVarsCSVPathFile, sOverwriteMsg, bSilent ))
	//		{	if (bSilent)
	//				sLogMsg = QString::asprintf( "Warning:  Unable to overwrite SimOutputVariablesToCSV file:  %s", sSimOutVarsCSVPathFile );
	//			else
	//				sLogMsg = QString::asprintf( "Warning:  User chose not to overwrite SimOutputVariablesToCSV file:  %s", sSimOutVarsCSVPathFile );
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
	//						sLogMsg = QString::asprintf( "Warning:  Unable to copy SimOutVarsToCSV file from '%s' to '%s'", sOutCSV, sSimOutVarsCSVPathFile );
	//					else
	//					{	int iGotHere = 1;
	//						iGotHere;
	//					}
	//				}
	//				catch(exec_stream_t::error_t &e)
	//				{	sLogMsg = QString::asprintf( "Warning:  Execution of ReadVarsESO reported error: %s", e.what() );
	//				}
	//		}	}
	//		if (!sLogMsg.isEmpty())
	//			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

			if (bDirChangedToEPlus)
            _chdir( pszSimProcessDir );
			if (sWarnMsg.size() > 0)
				BEMPX_WriteLogFile( sWarnMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}


	return bRetVal;
}


BOOL ProcessNonresSimulationResults( OSWrapLib& osWrap, COSRunInfo& osRunInfo, int& iRetVal, const char* pszSimProcessDir,
													BOOL bVerbose, int iSimulationStorage, const char* pszEPlusPath,
													QStringList* psaEPlusProcDirsToBeRemoved /*=NULL*/, bool bReportAllUMLHZones, 		// SAC 5/22/19 - added to postpone E+ directory cleanup until end of analysis to avoid deletion errors   // SAC 11/11/19
													QString* sStdDsgnCSEResultsPathFile /*=NULL*/, bool bRptMissingEPFiles )		// SAC 10/8/20 (tic #3218)
{
	BOOL bRetVal = TRUE;
	QString sLogMsg, sTemp;
   bool bHrlyDebugLogging = false;  //true;      // DEBUGGING - SAC 06/02/22

		double fBldgNonResFlrArea = 0, fBldgResFlrArea = 0, fTotBldgFlrArea=0, fNonResAreaRatio=0;
		long lCliZnNum=0;
		if (BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:NonResFlrArea" ), fBldgNonResFlrArea, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  // SAC 3/13/13 - CondFlrArea -> res/nonres...
			 BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:ResFlrArea"    ), fBldgResFlrArea   , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  (fBldgNonResFlrArea > 0 || fBldgResFlrArea > 0) &&
			 BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CliZnNum"      ), lCliZnNum         , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) &&  lCliZnNum > 0 )
			fTotBldgFlrArea = fBldgNonResFlrArea + fBldgResFlrArea;
                           if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/02/22
                              BEMPX_WriteLogFile( QString( "   ProcessNonresSimulationResults() - run '%1', CZ %2, NonResArea %3, ResArea %4, TotArea %5, iRetVal %6" ).arg( osRunInfo.RunID(), QString::number( lCliZnNum ), QString::number( fBldgNonResFlrArea ), QString::number( fBldgResFlrArea ), QString::number( fTotBldgFlrArea ), QString::number( iRetVal ) ) );

      BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:NonResAreaRatio" ), fNonResAreaRatio, 1, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );    // SAC 10/30/21 (MFam)
      double fResAreaRatio = 1 - fNonResAreaRatio;    // SAC 12/09/21

		int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
		long lDBID_EUseSummary_ZoneUMLHsLoaded  = BEMPX_GetDatabaseID( "ZoneUMLHsLoaded", iCID_EUseSummary );		assert( lDBID_EUseSummary_ZoneUMLHsLoaded > 0 );
		long lDBID_EUseSummary_ZoneUMLHs        = BEMPX_GetDatabaseID( "ZoneUMLHs"      , iCID_EUseSummary );		assert( lDBID_EUseSummary_ZoneUMLHs > 0 );

		long lEngyCodeYearNum;		// SAC 9/23/19 - added to facilitate changes in TDV/SrcEngy table look-up column #s
		BEMPX_GetInteger(BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum"), lEngyCodeYearNum, 2019, -1, -1, BEMO_User, osRunInfo.BEMProcIdx());			assert( lEngyCodeYearNum > 0 );

		QString sCO2EmissionsResultsUnit;	// SAC 9/11/19 - added CO2 emissions calcs (tic #3106)
		double fCO2EmissionsElecConvFac = 0, fCO2EmissionsNatGasConvFac = 0, fCO2EmissionsOtherConvFac = 0, fCO2EmissionsResultsMult = 0;	// SAC 9/12/19 - added *ConvFacs (tic #3106)
		long lCO2EmissionsResultsDecPrec = 0;
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsElecConvFac"   ), fCO2EmissionsElecConvFac   , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsNatGasConvFac" ), fCO2EmissionsNatGasConvFac , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsOtherConvFac"  ), fCO2EmissionsOtherConvFac  , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsResultsUnit"   ), sCO2EmissionsResultsUnit   , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsResultsMult"   ), fCO2EmissionsResultsMult   , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
		BEMPX_GetInteger(BEMPX_GetDatabaseID( "Proj:CO2EmissionsResultsDecPrec"), lCO2EmissionsResultsDecPrec, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
		int iCO2EmisTotalRnd = lCO2EmissionsResultsDecPrec;
		if (     fCO2EmissionsResultsMult > 999)		iCO2EmisTotalRnd -= 3;
		else if (fCO2EmissionsResultsMult > 99)		iCO2EmisTotalRnd -= 2;
		else if (fCO2EmissionsResultsMult > 9)			iCO2EmisTotalRnd -= 1;
		else if (fCO2EmissionsResultsMult < 0.01)		iCO2EmisTotalRnd += 3;
		else if (fCO2EmissionsResultsMult < 0.1)		iCO2EmisTotalRnd += 2;
		else if (fCO2EmissionsResultsMult < 1)			iCO2EmisTotalRnd += 1;

		int iFl;
		QString saTDSTableName[3];   long laTDSColumnNum[3];   double daTDSMult[3];   int iTDSType[3] = {0,0,0};		// SAC 8/26/18 - A2030
		bool bSetTDSResults = true;
		for (iFl=0; (bSetTDSResults && iFl < OSF_NumFuels); iFl++)
		{	if (BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:TDSTableName" )+iFl, saTDSTableName[iFl], FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) && !saTDSTableName[iFl].isEmpty() &&
				 BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:TDSColumnNum" )+iFl, laTDSColumnNum[iFl], 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && laTDSColumnNum[iFl] > 0)
				iTDSType[iFl] = 1;
			else if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:TDSMult"   )+iFl, daTDSMult[     iFl], 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && daTDSMult[iFl] != 0.0)
				iTDSType[iFl] = 2;
			if (iTDSType[iFl] < 1)
				bSetTDSResults = false;
		}

		int iOrientNum = 0;
		if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
		{	QString sRunID = osRunInfo.RunID();
			if (sRunID.length() == 3)
			{	sRunID = sRunID[2];
				iOrientNum = atoi( sRunID.toLocal8Bit().constData() );
		}	}

		long lNumResultsSets;		// SAC 11/3/19 - enable multiple results sets (2022)
		BEMPX_GetInteger(BEMPX_GetDatabaseID( "Proj:NumResultsSets"), lNumResultsSets, 1, -1, -1, BEMO_User, osRunInfo.BEMProcIdx());			assert( (lNumResultsSets > 0 && lNumResultsSets < 11) );

         //BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - marker 1: StoreHourlyResults %1, iRetVal %2" ).arg( QString::number( (osRunInfo.StoreHourlyResults() ? 1 : 0) ), QString::number( iRetVal ) ) );
		if (osRunInfo.StoreHourlyResults() && iRetVal == 0)
		{
			for (int iResSet=0; iResSet < lNumResultsSets; iResSet++)		// SAC 11/3/19
			{		//  "NumResultsSets",          BEMP_Int,  1,  0,  0,  NInp,  "",             "NumberResultsSets",                 ""  ; number of SETS of results (first implemented for 2022 testing to include 6 sets of TDV & CO2 multiplier tables & results) - SAC 11/03/19
					//  "TDVMultTableName",        BEMP_Str, 10,  1,  0,  NInp,  "",             "TDVMultiplierTableName",            "" 
					//  "ElecDemMultTableName",    BEMP_Str, 10,  1,  0,  NInp,  "",             "ElectricDemandMultiplierTableName", "" 
					//  "CO2EmissionsElecTable",   BEMP_Str, 10,  1,  0,  NInp,  "",             "CO2EmissionsElecricTable",          "" 
					//  "CO2EmissionsNatGasMult",  BEMP_Flt, 10,  1,  0,  NInp,  "ton/MBtuh",    "CO2EmissionsNaturalGasMultiplier",  "" 
					//  "CO2EmissionsOtherMult",   BEMP_Flt, 10,  1,  0,  NInp,  "ton/MBtuh",    "CO2EmissionsOtherMultiplier",       "" 
					//  "SrcEngyMultTableName",    BEMP_Str, 10,  1,  0,  NInp,  "",             "SourceEnergyMultiplierTableName",   "" 
			QString sResultSetName;		// SAC 11/3/19
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResultSetName" )+iResSet, sResultSetName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );

			QString sTDVMultTableName, sResTDVMultTableName;		// SAC 11/3/19
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVMultTableName" )+iResSet, sTDVMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResTDVMultTableName" )+iResSet, sResTDVMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );

			QString sHrlyElecDemMultTblCol, sResHrlyElecDemMultTblCol;	// SAC 10/8/16 - enable specification of hourly elec demand mult table:column via ruleset var
			if (osRunInfo.m_qaData.m_iNumQuickAnalysisPeriods < 1)	// SAC 10/11/16 - prevent demand calcs/storage when performing QuickAnalysis
			{	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ElecDemMultTableName" )+iResSet, sHrlyElecDemMultTblCol, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
            BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResElecDemMultTableName" )+iResSet, sResHrlyElecDemMultTblCol, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
         }

			QString sCO2EmissionsElecTableName, sCO2EmissionsNatGasTableName, sCO2EmissionsOtherTableName;	// SAC 12/10/19 - expanded to include NatGas & Other tables
			double fCO2EmissionsNatGasMult = 0, fCO2EmissionsOtherMult = 0;
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsElecTable"   )+iResSet, sCO2EmissionsElecTableName  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsNatGasTable" )+iResSet, sCO2EmissionsNatGasTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsOtherTable"  )+iResSet, sCO2EmissionsOtherTableName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsNatGasMult"  )+iResSet, fCO2EmissionsNatGasMult     , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
			BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsOtherMult"   )+iResSet, fCO2EmissionsOtherMult      , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
			QString sResCO2EmissionsElecTableName, sResCO2EmissionsNatGasTableName, sResCO2EmissionsOtherTableName;	// SAC 10/30/21 (MFam)
			double fResCO2EmissionsNatGasMult = 0, fResCO2EmissionsOtherMult = 0;
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsElecTable"   )+iResSet, sResCO2EmissionsElecTableName  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsNatGasTable" )+iResSet, sResCO2EmissionsNatGasTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsOtherTable"  )+iResSet, sResCO2EmissionsOtherTableName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsNatGasMult"  )+iResSet, fResCO2EmissionsNatGasMult     , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
			BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsOtherMult"   )+iResSet, fResCO2EmissionsOtherMult      , 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );

			QString sSrcEnergyTableName, sResSrcEnergyTableName;  //, sSrcEnergyPrmTableName;	// SAC 6/27/19 - enable calc and storage of Source Energy results (for 2022 research)
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SrcEngyMultTableName"   )+iResSet, sSrcEnergyTableName   , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
			BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResSrcEngyMultTableName"   )+iResSet, sResSrcEnergyTableName   , FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );
		// 	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SrcEngyPrimeMultTableName" ), sSrcEnergyPrmTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() );

		// copy Flexibility (PV-solar thermal) credit-related results from Proj to EUseSummary objects - SAC 9/14/20
			long lDBID_Proj_StdDHWNoSlrSysEnergy = BEMPX_GetDatabaseID( "Proj:StdDHWNoSlrSysEnergy" );		// BEMP_Flt, 30,  1,  0,  NInp,  "",      "StandardDHWNoSolarSystemEnergy", ""    ; "Standard design energy use of DHW w/out SolarSys [1-ElecKWH, 2-NGasKBtu, 3-OthrKBtu]"    ; SAC 9/14/20
			long lDBID_Proj_StdDHWNoSlrSysTDV    = BEMPX_GetDatabaseID( "Proj:StdDHWNoSlrSysTDV"    );		// BEMP_Flt, 30,  1,  0,  NInp,  "kTDV",  "StandardDHWNoSolarSystemTDV", ""       ; "Standard design kTDV of DHW w/out SolarSys [1-Elec, 2-NGas, 3-Othr]"
			long lDBID_Proj_StdDHWNoSlrSysTotTDV = BEMPX_GetDatabaseID( "Proj:StdDHWNoSlrSysTotTDV" );		// BEMP_Flt, 10,  1,  0,  NInp,  "kTDV",  "StandardDHWNoSolarSystemTotalTDV", ""  ; "Standard design kTDV of DHW w/out SolarSys (sum across all fuels)"
			long lDBID_Proj_TDVof1KWCFIPV        = BEMPX_GetDatabaseID( "Proj:TDVof1KWCFIPV"        );		// BEMP_Flt, 10,  1,  0,  NInp,  "kTDV",  "TDVof1KWCFIPV", ""                     ; TDV of a generic 1kW CFI PV array
			long lDBID_EUS_StdDHWNoSlrSysEnergy = BEMPX_GetDatabaseID( "StdDHWNoSlrSysEnergy", iCID_EUseSummary );	// BEMP_Flt, 3,  1,  0,  NInp,  "",      "StandardDHWNoSolarSystemEnergy", ""    ; "Standard design energy use of DHW w/out SolarSys [1-ElecKWH, 2-NGasKBtu, 3-OthrKBtu]"    ; SAC 9/14/20
			long lDBID_EUS_StdDHWNoSlrSysTDV    = BEMPX_GetDatabaseID( "StdDHWNoSlrSysTDV"   , iCID_EUseSummary );	// BEMP_Flt, 3,  1,  0,  NInp,  "kTDV",  "StandardDHWNoSolarSystemTDV", ""       ; "Standard design kTDV of DHW w/out SolarSys [1-Elec, 2-NGas, 3-Othr]"
			long lDBID_EUS_StdDHWNoSlrSysTotTDV = BEMPX_GetDatabaseID( "StdDHWNoSlrSysTotTDV", iCID_EUseSummary );	// BEMP_Flt, 1,  0,  0,  NInp,  "kTDV",  "StandardDHWNoSolarSystemTotalTDV", ""  ; "Standard design kTDV of DHW w/out SolarSys (sum across all fuels)"
			long lDBID_EUS_TDVof1KWCFIPV        = BEMPX_GetDatabaseID( "TDVof1KWCFIPV"       , iCID_EUseSummary );	// BEMP_Flt, 1,  0,  0,  NInp,  "kTDV",  "TDVof1KWCFIPV", ""                     ; TDV of a generic 1kW CFI PV array
			double dFlexData, dStdDHWNoSlrSysTotTDV=0.0, dTDVof1KWCFIPV=0.0, dDHWSolPVCredFrac=0.0, dFlexPropTDV=0.0, dFlexReqdPVKW=0.0, dResStdDHWTotTDV=0.0;		// SAC 10/8/20 (tic #3218)
			double dStdDHWNoSlrEnergy[] = { 0.0, 0.0, 0.0 };
			bool bPropPVTDVAdjustedForFlex = false;
         double dFlex_SelfUtilTDVAdj = 0.0, dFlex_SelfUtilElecAdj = 0.0, dFlex_SelfUtilSrcAdj = 0.0;
			if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:UseCentralElecDHWSolPVCredPct" ), dDHWSolPVCredFrac, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dDHWSolPVCredFrac > 0)
			{	dDHWSolPVCredFrac /= 100.0;
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysEnergy  +(iResSet*3), dStdDHWNoSlrEnergy[0], 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dStdDHWNoSlrEnergy[0] > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysEnergy  ,  BEMP_Flt, &dStdDHWNoSlrEnergy[0], BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysEnergy+1+(iResSet*3), dStdDHWNoSlrEnergy[1], 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dStdDHWNoSlrEnergy[1] > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysEnergy+1,  BEMP_Flt, &dStdDHWNoSlrEnergy[1], BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysEnergy+2+(iResSet*3), dStdDHWNoSlrEnergy[2], 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dStdDHWNoSlrEnergy[2] > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysEnergy+2,  BEMP_Flt, &dStdDHWNoSlrEnergy[2], BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysTDV  +(iResSet*3), dFlexData, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dFlexData > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysTDV  ,  BEMP_Flt, &dFlexData, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysTDV+1+(iResSet*3), dFlexData, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dFlexData > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysTDV+1,  BEMP_Flt, &dFlexData, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysTDV+2+(iResSet*3), dFlexData, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dFlexData > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysTDV+2,  BEMP_Flt, &dFlexData, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_StdDHWNoSlrSysTotTDV+iResSet,    dStdDHWNoSlrSysTotTDV, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dStdDHWNoSlrSysTotTDV > 0)
					BEMPX_SetBEMData( lDBID_EUS_StdDHWNoSlrSysTotTDV, BEMP_Flt, &dStdDHWNoSlrSysTotTDV, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				if (BEMPX_GetFloat( lDBID_Proj_TDVof1KWCFIPV+iResSet,    dTDVof1KWCFIPV, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() ) && dTDVof1KWCFIPV < 0)
					BEMPX_SetBEMData( lDBID_EUS_TDVof1KWCFIPV, BEMP_Flt, &dTDVof1KWCFIPV, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				// divide dStdDHWNoSlrSysTotTDV & dTDVof1KWCFIPV by floor area - SAC 9/15/20
				dStdDHWNoSlrSysTotTDV = dStdDHWNoSlrSysTotTDV / fTotBldgFlrArea;
				dTDVof1KWCFIPV        = dTDVof1KWCFIPV        / fTotBldgFlrArea;
			}

         double dCmntySlr_ElecEnergy=0.0, dCmntySlr_ElecDemand=0.0, dCmntySlr_TDV=0.0, dCmntySlr_CO2=0.0, dCmntySlr_Src=0.0, dCmntySlr_PVSize=0.0;
         double dSelfUtil_GridHarmCredPk=0.0, dSelfUtil_EnergyEffCap=0.0, dSelfUtil_EnergyEffTDV=0.0, dSelfUtil_EffBattFrac=0.0;    // SAC 06/05/22
         if (osRunInfo.IsStdRun())
         {  long lDBID_Proj_CmntySlr_ElecEnergy  = BEMPX_GetDatabaseID( "Proj:CmntySlr_ElecEnergy"  );      // SAC 06/02/22
            long lDBID_Proj_CmntySlr_ElecDemand  = BEMPX_GetDatabaseID( "Proj:CmntySlr_ElecDemand"  );
            long lDBID_Proj_CmntySlr_TDV     = BEMPX_GetDatabaseID( "Proj:CmntySlr_TDV"  );
            long lDBID_Proj_CmntySlr_CO2     = BEMPX_GetDatabaseID( "Proj:CmntySlr_CO2"  );
            long lDBID_Proj_CmntySlr_Src     = BEMPX_GetDatabaseID( "Proj:CmntySlr_Src"  );
            if (lDBID_Proj_CmntySlr_ElecEnergy > 0)
               BEMPX_GetFloat( lDBID_Proj_CmntySlr_ElecEnergy, dCmntySlr_ElecEnergy, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
            if (lDBID_Proj_CmntySlr_ElecDemand > 0)
               BEMPX_GetFloat( lDBID_Proj_CmntySlr_ElecDemand, dCmntySlr_ElecDemand, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
            if (lDBID_Proj_CmntySlr_TDV > 0)
               BEMPX_GetFloat( lDBID_Proj_CmntySlr_TDV, dCmntySlr_TDV, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
            if (lDBID_Proj_CmntySlr_CO2 > 0)
               BEMPX_GetFloat( lDBID_Proj_CmntySlr_CO2, dCmntySlr_CO2, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
            if (lDBID_Proj_CmntySlr_Src > 0)
               BEMPX_GetFloat( lDBID_Proj_CmntySlr_Src, dCmntySlr_Src, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
                           if (bHrlyDebugLogging && dCmntySlr_ElecEnergy < -0.1)      // DEBUGGING - SAC 06/02/22
                              BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - Community Solar (per kW): ElecEnergy %1 kWh | ElecDemand %2 kW | %3 kTDV | CO2 %4 kg | source %5 kBtu" ).arg( 
                                                   QString::number(dCmntySlr_ElecEnergy), QString::number(dCmntySlr_ElecDemand), QString::number(dCmntySlr_TDV), QString::number(dCmntySlr_CO2), QString::number(dCmntySlr_Src) ) );  
            // Self Utilization Credit stuff - similar to Community Solar above, in that it depends on Std model results - SAC 06/05/22
            long lDBID_Proj_AllowBattGridHarmCredit  = BEMPX_GetDatabaseID( "Proj:AllowBattGridHarmCredit"  );
            long lDBID_Proj_BattGridHarmCredit       = BEMPX_GetDatabaseID( "Proj:BattGridHarmCredit"  );
            long lDBID_Proj_GridHarmCredPk           = BEMPX_GetDatabaseID( "Proj:GridHarmCredPk"  );
            long lAllowBattGridHarmCredit, lBattGridHarmCredit;
            if (lDBID_Proj_AllowBattGridHarmCredit > 0 && BEMPX_GetInteger( lDBID_Proj_AllowBattGridHarmCredit, lAllowBattGridHarmCredit, 0, BEMP_Int, 0 /*ObjIdx*/, BEMO_User, osRunInfo.BEMProcIdx() ) && lAllowBattGridHarmCredit > 0 &&
                lDBID_Proj_BattGridHarmCredit > 0 && BEMPX_GetInteger( lDBID_Proj_BattGridHarmCredit, lBattGridHarmCredit, 0, BEMP_Int, 0 /*ObjIdx*/, BEMO_User, osRunInfo.BEMProcIdx() ) && lBattGridHarmCredit > 0 &&
                lDBID_Proj_GridHarmCredPk > 0)
               BEMPX_GetFloat( lDBID_Proj_GridHarmCredPk, dSelfUtil_GridHarmCredPk, 0, -1, -1, BEMO_User, osRunInfo.BEMProcIdx() );
                           if (bHrlyDebugLogging && dSelfUtil_GridHarmCredPk > 0.0001)      // DEBUGGING - SAC 06/05/22
                              BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - Self Utilization Credit: GridHarmCredPk frac %1" ).arg( QString::number(dSelfUtil_GridHarmCredPk) ) );  
         }

									if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Summing hourly simulation results, TDV calcs, etc.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			int iCID_EnergyUse = BEMPX_GetDBComponentID( "EnergyUse" );		assert( iCID_EnergyUse > 0 );
			int iEUIdx, /*hr,*/ iError;
			QString sEUPropNameBase = (osRunInfo.IsStdRun() ? "Std" : "Prop"), sPropName;
			bool bIsT24Prop = (osRunInfo.CodeType() == CT_T24N && !osRunInfo.IsStdRun());		// SAC 7/28/20
			for (iFl=0; iFl < OSF_NumFuels; iFl++)
			{	iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{	// initialize result to contain hourly results sum already stored (via previous simulation of this run, such as CEC-T24 DHW)
					double dExistResult    = BEMPX_GetHourlyResultSum( NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName,    NULL, NULL, NULL, NULL, NULL, NULL, NULL, osRunInfo.BEMProcIdx() );
					double dResExistResult = BEMPX_GetHourlyResultSum( NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sResEnduseName, NULL, NULL, NULL, NULL, NULL, NULL, NULL, osRunInfo.BEMProcIdx() );   // SAC 10/30/21 (MFam)
               // fix bug where PV & Battery energy use is DOUBLED due to both NRes & Res results duplicated to facilitate weighting of TDV and other factors by AreaRatios - SAC 05/11/22
               if (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)
               {  dExistResult    *= fNonResAreaRatio;
                  dResExistResult *= fResAreaRatio;
               }
                           if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/02/22
                              BEMPX_WriteLogFile( QString( "   ProcessNonresSimulationResults() - %1 %2: Com hrly sum %3 / Res %4" ).arg( (iFl==0 ? "Elec" : (iFl==1 ? "Gas" : "Other" )), esEUMap_CECNonRes[iEUIdx].sEnduseName, QString::number(dExistResult), QString::number(dResExistResult) ) );  // SAC 05-11/22
					if (dExistResult != -99999.0)
						esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] = dExistResult;
					else
						esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] = 0.0;
					if (dResExistResult != -99999.0)
					{	esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl]  = dResExistResult;
                  esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl]    += dResExistResult;
               }
					else
						esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daTDVTotal[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daSrcTotal[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daCO2Total[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daTDSTotal[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daResTDVTotal[   iFl] = 0.0;   // SAC 10/30/21 (MFam)
					esEUMap_CECNonRes[iEUIdx].daResSrcTotal[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daResSrcPrmTotal[iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daResCO2Total[   iFl] = 0.0;
					esEUMap_CECNonRes[iEUIdx].daResTDSTotal[   iFl] = 0.0;
					if (iFl==0)  // SAC 10/8/16
					{	esEUMap_CECNonRes[iEUIdx].dElecDemand = 0.0;
						esEUMap_CECNonRes[iEUIdx].daSupply[0] = 0.0;		// SAC 9/7/18 - A2030 [Elec,TDV,TDS]
						esEUMap_CECNonRes[iEUIdx].daSupply[1] = 0.0;
						esEUMap_CECNonRes[iEUIdx].daSupply[2] = 0.0;
                  esEUMap_CECNonRes[iEUIdx].dResElecDemand = 0.0;    // SAC 10/30/21 (MFam)
						esEUMap_CECNonRes[iEUIdx].daResSupply[0] = 0.0;
						esEUMap_CECNonRes[iEUIdx].daResSupply[1] = 0.0;
						esEUMap_CECNonRes[iEUIdx].daResSupply[2] = 0.0;
				}	}
			}
			for (iFl=0; iFl < OSF_NumFuels; iFl++)
			{
                           if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/02/22
                              BEMPX_WriteLogFile( QString( "   ProcessNonresSimulationResults() - processing hourly results for Fuel %1 (%2)" ).arg( QString::number( iFl ), (iFl==0 ? "Elec" : (iFl==1 ? "Gas" : "Other" )) ) );
				esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daEnduseTotal[   iFl] = esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daEnduseTotal[   iFl] = esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot].daEnduseTotal[   iFl] = 0.0;  // SAC 7/23/18 - to be re-calced in following loop
				esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daResEnduseTotal[iFl] = esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daResEnduseTotal[iFl] = esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot].daResEnduseTotal[iFl] = 0.0;  // SAC 10/30/21 (MFam)
				iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{
      			// SAC 8/18/14 - fixed bug where DHW simulation results NOT being accounted for when applying TDV multipliers to hourly results
					double* pdBEMHrlyRes = NULL;  double* pdBEMResHrlyRes = NULL;
					int iBEMHrlyResPtrRV   = BEMPX_GetHourlyResultArrayPtr( &pdBEMHrlyRes,    NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName,    osRunInfo.BEMProcIdx() );
					int iBEMResHrlyResPtrRV = -1;
               if (fBldgResFlrArea > 0 && iEUIdx != IDX_T24_NRES_EU_PV && iEUIdx != IDX_T24_NRES_EU_BT)
                  iBEMResHrlyResPtrRV = BEMPX_GetHourlyResultArrayPtr( &pdBEMResHrlyRes, NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sResEnduseName, osRunInfo.BEMProcIdx() );
					bool bBEMHrlyResPtrOK    = (pdBEMHrlyRes    && iBEMHrlyResPtrRV   ==0);			//assert( bBEMHrlyResPtrOK );  // needs to be valid following split of results processing routine? - SAC 7/23/18
					bool bBEMResHrlyResPtrOK = (pdBEMResHrlyRes && iBEMResHrlyResPtrRV==0);		// SAC 10/30/21 (MFam)
							// assert( (bBEMHrlyResPtrOK || iEUIdx == IDX_T24_NRES_EU_CompTot || iEUIdx == IDX_T24_NRES_EU_Total ) );
               	// debugging
               	//	// failure EXPECTED for enduses:  "COMPLIANCE TOTAL" & "TOTAL"
               	//if (!bBEMHrlyResPtrOK)
               	//{	QString qsHrlyResPtrErr = QString( "      BEMPX_GetHourlyResultArrayPtr( RunID %1, Fuel %2, Enduse %3, BEMProcIdx %4 ) error: returned %5, pdBEMHrlyRes %6" ).arg(
               	//														osRunInfo.LongRunID(), pszaEPlusFuelNames[iFl], esEUMap_CECNonRes[iEUIdx].sEnduseName, QString::number(osRunInfo.BEMProcIdx()), QString::number(iBEMHrlyResPtrRV), (pdBEMHrlyRes ? "valid" : "NULL") );
               	//	BEMPX_WriteLogFile( qsHrlyResPtrErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               	//}

				   // SAC 7/23/18 - repeat summing for CompTot and Total enduses done preliminarily above
					if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot && iEUIdx != IDX_T24_NRES_EU_Total &&
                   (esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0 || esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0))  // SAC 7/15/18 - '>0' -> '!=0' to allow for negative (PV/Batt) enduses
					{
                     esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daEnduseTotal[   iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[   iFl];
                     esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daResEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl];
						if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
                  {  esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daEnduseTotal[   iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[   iFl];
                     esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daResEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl];
                  }
                  if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
                  {  esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daEnduseTotal[   iFl] += esEUMap_CECNonRes[iEUIdx].daEnduseTotal[   iFl];
                     esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daResEnduseTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl];
               }  }

				   // we now have all hourly results for this ruleset enduse and fuel (Elec/NatGas/Other) combination...
				   // NOW grab the hourly TDV Factors (from ruleset table), apply them to the hourly results and sum the totals into annual TDV results (by fuel and enduse) 
					if (osRunInfo.CodeType() == CT_T24N && iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_Total && iEUIdx != IDX_T24_NRES_EU_EffTot)		// added check to perform TDV only on CT_T24N runs
					{	assert( fTotBldgFlrArea > 0 );
						int iTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) + iFl + 2) : ((iFl * 16) + lCliZnNum + 1) );		// SAC 9/23/19 - iTableCol dependence on lEngyCodeYearNum
						double dTDVSum = 0.0, dSrcSum = 0.0, dSrcPrmSum = 0.0, dCO2Sum = 0.0, dResTDVSum = 0.0, dResSrcSum = 0.0, dResSrcPrmSum = 0.0, dResCO2Sum = 0.0;
						if (esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0 || esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0)  // SAC 7/15/18 - '>0' -> '!=0' to allow for negative (PV/Batt) enduses
						{
                     if (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)    // for PV &/or Batt - apply weighted TDV multipliers - SAC 12/09/21
                     {  dTDVSum       = fNonResAreaRatio * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes),    sTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                        if (!sResTDVMultTableName.isEmpty() && fResAreaRatio > 0.001)
   						      dResTDVSum =    fResAreaRatio * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes), sResTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                        dTDVSum += dResTDVSum;
                     }
                     else 
							{  dTDVSum       = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes), sTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                        if (!sResTDVMultTableName.isEmpty())
							      dResTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                        dTDVSum += dResTDVSum;
                     }
                           //BEMPX_WriteLogFile( QString( "         iTableCol %1 - dTDVSum %2" ).arg( QString::number( iTableCol ), QString::number( dTDVSum ) ) );
							if (sSrcEnergyTableName.length() > 1)
                     {  if (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)    // for PV &/or Batt - apply weighted Src multipliers - SAC 12/09/21
								{  dSrcSum       = fNonResAreaRatio * BEMPX_ApplyHourlyMultipliersFromTable(    (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes),    sSrcEnergyTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                           if (!sResSrcEnergyTableName.isEmpty() && fResAreaRatio > 0.001) 
                              dResSrcSum =    fResAreaRatio * BEMPX_ApplyHourlyMultipliersFromTable(    (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes), sResSrcEnergyTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                           dSrcSum += dResSrcSum;
                        }
							   else
                     	{  dSrcSum       = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK    ? pdBEMHrlyRes    : dHrlyRes),    sSrcEnergyTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
      							if (sResSrcEnergyTableName.length() > 1)
      								dResSrcSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResSrcEnergyTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
                           dSrcSum += dResSrcSum;
                     }  }
   						//	if (!sSrcEnergyPrmTableName.isEmpty())
   						//		dSrcPrmSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sSrcEnergyPrmTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );

   						// code to retrieve hourly residential DHW results and calculate total TDV (needed for Flexibility credit calc) - SAC 10/8/20 (tic #3218)
							if (iEUIdx == IDX_T24_NRES_EU_DHW && dDHWSolPVCredFrac > 0 && dStdDHWNoSlrEnergy[iFl] > 0 && sStdDsgnCSEResultsPathFile && !sStdDsgnCSEResultsPathFile->isEmpty())
							{	if (!FileExists( *sStdDsgnCSEResultsPathFile ))
								{	assert( false );
								}
								else
								{	InitHrlyRes( dStdResDHWHrlyRes );
									int iNumCSEMtrRes = BEMPX_RetrieveCSEHourlyResults( sStdDsgnCSEResultsPathFile->toLocal8Bit().constData(), pszCSEMtrNames[iFl],
																											(const char**) pszCSEDHWEnduseList, dStdResDHWHrlyRes );
									if (iNumCSEMtrRes > 0)
									{
										double dCSETDVSum = BEMPX_ApplyHourlyMultipliersFromTable( dStdResDHWHrlyRes, sTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) );
										if (dCSETDVSum > 0)
											dResStdDHWTotTDV += (dCSETDVSum * daCSEMtrTDVMults[iFl]);
                                          if (bHrlyDebugLogging)      // DEBUGGING
                                             BEMPX_WriteLogFile( QString( "         Flex Calc: Std Res DHW %1 TDV (%2 * %3) = %4, total %5" ).arg( pszCSEMtrNames[iFl], QString::number( dCSETDVSum ), QString::number( daCSEMtrTDVMults[iFl] ), QString::number( (dCSETDVSum * daCSEMtrTDVMults[iFl]) ), QString::number( dResStdDHWTotTDV ) ) );
							}	}	}

							// SAC 9/11/19 - CO2 emissions (tonne) (tic #3106)
							int iNatGasCO2ColOffset = (sCO2EmissionsElecTableName.compare( sCO2EmissionsNatGasTableName )==0 ? 16 : 0);		// SAC 12/10/19
							int iOtherCO2ColOffset  = (sCO2EmissionsElecTableName.compare( sCO2EmissionsOtherTableName  )==0 ? 32 : 0);
							if (iFl==0 && sCO2EmissionsElecTableName.length() > 1 && fCO2EmissionsElecConvFac > 0.0)
								dCO2Sum = fCO2EmissionsElecConvFac /*MWh-tonne/kWh-ton*/ * /*kWh * ton/MWh*/ BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sCO2EmissionsElecTableName.toLocal8Bit().constData(), lCliZnNum+1, (bVerbose != FALSE) );
							else if (iFl==1 && sCO2EmissionsNatGasTableName.length() > 1 && fCO2EmissionsNatGasConvFac > 0.0)
								dCO2Sum = fCO2EmissionsNatGasConvFac * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sCO2EmissionsNatGasTableName.toLocal8Bit().constData(), lCliZnNum+1+iNatGasCO2ColOffset, (bVerbose != FALSE) );
							else if (iFl==2 && sCO2EmissionsOtherTableName.length() > 1 && fCO2EmissionsOtherConvFac > 0.0)
								dCO2Sum = fCO2EmissionsOtherConvFac  * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sCO2EmissionsOtherTableName.toLocal8Bit().constData(), lCliZnNum+1+iOtherCO2ColOffset, (bVerbose != FALSE) );
							else if ( (iFl==1 && fCO2EmissionsNatGasMult > 0.0 && fCO2EmissionsNatGasConvFac > 0.0) ||
										 (iFl==2 && fCO2EmissionsOtherMult  > 0.0 && fCO2EmissionsOtherConvFac  > 0.0) )
								dCO2Sum = (iFl==1 ? fCO2EmissionsNatGasConvFac : fCO2EmissionsOtherConvFac) /*MBtu-tonne/therm-ton*/ * /*therm * ton/MBtu*/ (iFl==1 ? fCO2EmissionsNatGasMult : fCO2EmissionsOtherMult) * SumHrlyRes( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes) );

                     // RES CO2 results - SAC 10/31/21 (MFam)
                     // fCO2EmissionsElecConvFac, fCO2EmissionsNatGasConvFac & fCO2EmissionsOtherConvFac assumed SAME between Com & Res
                     if (esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0)
							{  if (iFl==0 && sResCO2EmissionsElecTableName.length() > 1 && fCO2EmissionsElecConvFac > 0.0)
   								dResCO2Sum = fCO2EmissionsElecConvFac /*MWh-tonne/kWh-ton*/ * /*kWh * ton/MWh*/ BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResCO2EmissionsElecTableName.toLocal8Bit().constData(), lCliZnNum+1, (bVerbose != FALSE) );
   							else if (iFl==1 && sResCO2EmissionsNatGasTableName.length() > 1 && fCO2EmissionsNatGasConvFac > 0.0)
   								dResCO2Sum = fCO2EmissionsNatGasConvFac * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResCO2EmissionsNatGasTableName.toLocal8Bit().constData(), lCliZnNum+1+iNatGasCO2ColOffset, (bVerbose != FALSE) );
   							else if (iFl==2 && sResCO2EmissionsOtherTableName.length() > 1 && fCO2EmissionsOtherConvFac > 0.0)
   								dResCO2Sum = fCO2EmissionsOtherConvFac  * BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResCO2EmissionsOtherTableName.toLocal8Bit().constData(), lCliZnNum+1+iOtherCO2ColOffset, (bVerbose != FALSE) );
   							else if ( (iFl==1 && fResCO2EmissionsNatGasMult > 0.0 && fCO2EmissionsNatGasConvFac > 0.0) ||
   										 (iFl==2 && fResCO2EmissionsOtherMult  > 0.0 && fCO2EmissionsOtherConvFac  > 0.0) )
   								dResCO2Sum = (iFl==1 ? fCO2EmissionsNatGasConvFac : fCO2EmissionsOtherConvFac) /*MBtu-tonne/therm-ton*/ * /*therm * ton/MBtu*/ (iFl==1 ? fResCO2EmissionsNatGasMult : fResCO2EmissionsOtherMult) * SumHrlyRes( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes) );
                        dCO2Sum += dResCO2Sum;
                     }
						}
         				//	if (dTDVSum < 0)
         				//	{	// ERROR
         				//		assert( FALSE );
         				//	}
         				//	else if (fTotBldgFlrArea > 0)
						if (fTotBldgFlrArea > 0)
						{		esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl] = dTDVSum / fTotBldgFlrArea;
								esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
							if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
								esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
                     if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
								esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];

							if (sSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
							{		esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl] = dSrcSum / fTotBldgFlrArea;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl];
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl];
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl];
							}
						      // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/27/19 - 2022
						      // {		esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl] = dSrcPrmSum / fTotBldgFlrArea;
						      // 		esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daSrcPrmTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl];
						      // 	if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
						      // 		esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daSrcPrmTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl];
						      // }

							// SAC 9/11/19 - CO2 emissions (tonne) (tic #3106)
							if (dCO2Sum != 0.0)
							{		esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl] = dCO2Sum;   // store as tonne, not tonne/sqft (/ fTotBldgFlrArea)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl], iCO2EmisTotalRnd );
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl], iCO2EmisTotalRnd );
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl], iCO2EmisTotalRnd );
							}
						}
						if (fBldgResFlrArea > 0)      // SAC 10/30/21 (MFam)
						{		esEUMap_CECNonRes[iEUIdx].daResTDVTotal[iFl] = dResTDVSum / fBldgResFlrArea;
								esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daResTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResTDVTotal[iFl];
							if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
								esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daResTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResTDVTotal[iFl];
                     if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
								esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daResTDVTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResTDVTotal[iFl];

							if (sSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
							{		esEUMap_CECNonRes[iEUIdx].daResSrcTotal[iFl] = dResSrcSum / fBldgResFlrArea;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daResSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResSrcTotal[iFl];
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daResSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResSrcTotal[iFl];
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daResSrcTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daResSrcTotal[iFl];
							}

							// SAC 9/11/19 - CO2 emissions (tonne) (tic #3106)
							if (dResCO2Sum != 0.0)
							{		esEUMap_CECNonRes[iEUIdx].daResCO2Total[iFl] = dResCO2Sum;   // store as tonne, not tonne/sqft (/ fTotBldgFlrArea)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daResCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daResCO2Total[iFl], iCO2EmisTotalRnd );
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daResCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daResCO2Total[iFl], iCO2EmisTotalRnd );
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daResCO2Total[iFl] += RoundVal( esEUMap_CECNonRes[iEUIdx].daResCO2Total[iFl], iCO2EmisTotalRnd );
							}
						}
                                          if (bHrlyDebugLogging)      // DEBUGGING
                                             BEMPX_WriteLogFile( QString( "         ProcessNonresSimulationResults() - %1:  dTDVSum %2 | fTotBldgFlrArea %3 | esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl] %4" ).arg( esEUMap_CECNonRes[iEUIdx].sEnduseAbbrev, QString::number( dTDVSum ), QString::number( fTotBldgFlrArea ), QString::number( esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl] ) ) );

                  // calc amount of Community Solar needed for Proposed design - SAC 06/03/22
                  if (osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun() && iEUIdx == IDX_T24_NRES_EU_PV && dCmntySlr_TDV < 0 && dTDVSum < 0)
                  {  assert( dCmntySlr_PVSize < 0.1 );
                     dCmntySlr_PVSize = dTDVSum / dCmntySlr_TDV;
                     long lDBID_EUseSmry_CommunitySlrPVPwr = BEMPX_GetDatabaseID( "EUseSummary:CommunitySlrPVPwr" );
                     if (lDBID_EUseSmry_CommunitySlrPVPwr > 0)
                        BEMPX_SetBEMData( lDBID_EUseSmry_CommunitySlrPVPwr, BEMP_Flt, &dCmntySlr_PVSize, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                                          if (bHrlyDebugLogging)      // DEBUGGING
                                             BEMPX_WriteLogFile( QString( "            ProcessNonresSimulationResults() - Community Solar PVSize: %1 kWdc" ).arg( QString::number( dCmntySlr_PVSize ) ) );
                  }

   					// calc and store A2030 TDS results - SAC 8/26/18
						if (bSetTDSResults)
						{	double dTDSFuelMult[] = {  0.001,	// elec: Btu -> kBtu   - SAC 9/10/18
																100.0,	// ngas: thrm -> kBtu
																100.0 };	// othr: thrm -> kBtu
							double dTDSSum = 0.0;
							if (esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0)  // SAC 7/15/18 - '>0' -> '!=0' to allow for negative (PV/Batt) enduses
							{	if (iTDSType[iFl] == 1)
									dTDSSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), saTDSTableName[iFl].toLocal8Bit().constData(), laTDSColumnNum[iFl], (bVerbose != FALSE) );
								else if (iTDSType[iFl] == 2)
								{	for (int hr=0; hr<8760; hr++)
										dTDSSum += (bBEMHrlyResPtrOK ? pdBEMHrlyRes[hr] : dHrlyRes[hr]) * daTDSMult[iFl];
							}	}
							if (fTotBldgFlrArea > 0)
							{		esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl] = dTDSSum * dTDSFuelMult[iFl] / fTotBldgFlrArea;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daTDSTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl];
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daTDSTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl];
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daTDSTotal[iFl] += esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl];
						}	}

						if (iFl == 0)	// SAC 9/7/18 - A2030 [Elec,TDV] - Elec Supply results
						{	double* pdInitHrlyRes = (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes);
							double daHrlyElecSup[8760];
							esEUMap_CECNonRes[iEUIdx].daSupply[0] = 0.0;
							for (int hr=0; hr<8760; hr++)
							{	if (pdInitHrlyRes[hr] < 0.0)
								{	daHrlyElecSup[hr] = pdInitHrlyRes[hr];
									esEUMap_CECNonRes[iEUIdx].daSupply[0] += pdInitHrlyRes[hr];
								}
								else
									daHrlyElecSup[hr] = 0.0;
							}
							esEUMap_CECNonRes[iEUIdx].daSupply[1] = (esEUMap_CECNonRes[iEUIdx].daSupply[0] >= 0.0 ? 0.0 :
										BEMPX_ApplyHourlyMultipliersFromTable( &daHrlyElecSup[0], sTDVMultTableName.toLocal8Bit().constData(), iTableCol, (bVerbose != FALSE) ) / fTotBldgFlrArea);

							if (bSetTDSResults)
							{	esEUMap_CECNonRes[iEUIdx].daSupply[2] = 0.0;
								if (esEUMap_CECNonRes[iEUIdx].daSupply[0] != 0)  // SAC 7/15/18 - '>0' -> '!=0' to allow for negative (PV/Batt) enduses
								{	if (iTDSType[iFl] == 1)
										esEUMap_CECNonRes[iEUIdx].daSupply[2] = BEMPX_ApplyHourlyMultipliersFromTable( &daHrlyElecSup[0], saTDSTableName[iFl].toLocal8Bit().constData(), laTDSColumnNum[iFl], (bVerbose != FALSE) );
									else if (iTDSType[iFl] == 2)
									{	for (int hr=0; hr<8760; hr++)
											esEUMap_CECNonRes[iEUIdx].daSupply[2] += daHrlyElecSup[hr] * daTDSMult[iFl];
								}	}
								if (esEUMap_CECNonRes[iEUIdx].daSupply[2] != 0)
									esEUMap_CECNonRes[iEUIdx].daSupply[2] /= (fTotBldgFlrArea * 1000.0);  // SAC 9/10/18 - incl Btu -> kBtu conversion
							}

							if (fTotBldgFlrArea > 0)
							{		esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daSupply[0] += esEUMap_CECNonRes[iEUIdx].daSupply[0];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daSupply[1] += esEUMap_CECNonRes[iEUIdx].daSupply[1];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].daSupply[2] += esEUMap_CECNonRes[iEUIdx].daSupply[2];
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
								{	esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daSupply[0] += esEUMap_CECNonRes[iEUIdx].daSupply[0];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daSupply[1] += esEUMap_CECNonRes[iEUIdx].daSupply[1];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].daSupply[2] += esEUMap_CECNonRes[iEUIdx].daSupply[2];
                        }
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
								{	esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daSupply[0] += esEUMap_CECNonRes[iEUIdx].daSupply[0];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daSupply[1] += esEUMap_CECNonRes[iEUIdx].daSupply[1];
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daSupply[2] += esEUMap_CECNonRes[iEUIdx].daSupply[2];
							}	}
						}

   					// SAC 10/8/16 - elec demand calc
						if (iFl==0 && sHrlyElecDemMultTblCol.length() > 1 && esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0.0)
						{
							double dEDem = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), sHrlyElecDemMultTblCol.toLocal8Bit().constData(), -1, (bVerbose != FALSE) );
							if (dEDem != 0.0)
							{		esEUMap_CECNonRes[iEUIdx].dElecDemand = dEDem;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].dElecDemand += dEDem;
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].dElecDemand += dEDem;
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
									esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].dElecDemand += dEDem;
						}	}
                  // Residential demand - SAC 10/31/21 (MFam)
						if (iFl==0 && sResHrlyElecDemMultTblCol.length() > 1 && esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0.0)
						{
							double dEDem = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMResHrlyResPtrOK ? pdBEMResHrlyRes : dHrlyRes), sResHrlyElecDemMultTblCol.toLocal8Bit().constData(), -1, (bVerbose != FALSE) );
							if (dEDem != 0.0)
							{		esEUMap_CECNonRes[iEUIdx].dElecDemand += dEDem;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].dElecDemand += dEDem;
                           esEUMap_CECNonRes[iEUIdx].dResElecDemand = dEDem;
									esEUMap_CECNonRes[IDX_T24_NRES_EU_Total  ].dResElecDemand += dEDem;
								if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
								{	esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].dElecDemand += dEDem;
                           esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].dResElecDemand += dEDem;
                        }
                        if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance && lEngyCodeYearNum >= 2022)
								{	esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].dElecDemand += dEDem;
                           esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].dResElecDemand += dEDem;
						}	}  }
					}
            }	// end of  while (esEUMap_CECNonRes[++iEUIdx]...

            // ADJUST Proposed model PV, CompTot & Total EnergyUse properties to account for Community Solar - SAC 06/03/22
            if (iFl==0 && osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun() && dCmntySlr_PVSize > 0.1)
            {  int iaCommSlrEndUses[] = { IDX_T24_NRES_EU_PV, IDX_T24_NRES_EU_CompTot, IDX_T24_NRES_EU_Total, -1 };
               EnergyUseAdjust aCSAData[] =      { {  "ProposedTDV[1]",     4, 2, 1.0,    dCmntySlr_PVSize * dCmntySlr_TDV        / fTotBldgFlrArea   },
                                                   {  "PropElecEnergy",     2, 1, 0.001,  dCmntySlr_PVSize * dCmntySlr_ElecEnergy                     },
                                                   {  "PropTotalEnergy",   -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_ElecEnergy / fTotBldgFlrArea   },
                                                   {  "PropElecDemand",    -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_ElecDemand                     },
                                                   {  "PropElecResEnergy", -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_ElecEnergy * fResAreaRatio     },
                                                   {  "PropElecTDV[1]",    -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_TDV        / fTotBldgFlrArea   },
                                                   {  "PropElecResTDV[1]", -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_TDV * fResAreaRatio / fTotBldgFlrArea },
                                                   {  "PropElecSupEnergy", -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_ElecEnergy                     },
                                                   {  "PropElecSupTDV",    -1, 0, 1.0,    dCmntySlr_PVSize * dCmntySlr_TDV        / fTotBldgFlrArea   },
                                                   {  "ProposedSrc[1]",    11, 2, 1.0,    dCmntySlr_PVSize * dCmntySlr_Src        / fTotBldgFlrArea   },
                                                   {  "PropElecC02[1]",    17, 2, 1.0,    dCmntySlr_PVSize * dCmntySlr_CO2 * 0.001                    },
                                                   {  "PropTotalC02[1]",   19, 2, 1.0,    dCmntySlr_PVSize * dCmntySlr_CO2 * 0.001                    },
                                                   {  "",                  -1, 0, 1.0,    0.0   } };
               int iCommSlrEUIdx = -1;  double fVal;
               QString sResultVal;
               while (iaCommSlrEndUses[++iCommSlrEUIdx] >= 0)
               {  iEUIdx = iaCommSlrEndUses[iCommSlrEUIdx];
                  BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );     assert( pEUObj );
                  int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));           assert( iEUObjIdx >= 0 );
                  if (iEUObjIdx >= 0)
                  {  int iCSPropIdx = -1;
                     while (strlen( aCSAData[++iCSPropIdx].sEnergyUsePropName ) > 0)
                     {
                        BEMPX_GetFloat(   BEMPX_GetDatabaseID( aCSAData[iCSPropIdx].sEnergyUsePropName, iCID_EnergyUse ), fVal, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                        fVal += aCSAData[iCSPropIdx].dAdjust;
                        BEMPX_SetBEMData( BEMPX_GetDatabaseID( aCSAData[iCSPropIdx].sEnergyUsePropName, iCID_EnergyUse ), BEMP_Flt, &fVal, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        if (aCSAData[iCSPropIdx].iEUseSummaryEnduseArray > 0)
                        {
                           long lDBID_EUseSumProp = BEMPX_GetDatabaseID( QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(aCSAData[iCSPropIdx].iEUseSummaryEnduseArray) ), iCID_EUseSummary );    assert( lDBID_EUseSumProp > 0 );
                           fVal *= aCSAData[iCSPropIdx].dEUseSummaryEnduseMult;
                           if (WithinMargin( fVal, 0.0, 0.001 ))
                              sResultVal = "--";
                           else
                              sResultVal = BEMPX_FloatToString( fVal, aCSAData[iCSPropIdx].iEUseSummaryEnduseDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                           BEMPX_SetBEMData( lDBID_EUseSumProp, BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        }
               }  }  }
            }

            // Calc final Self Util adjustments and ADJUST Proposed model Batt & EffTot EnergyUse properties to account for Self Utilization - SAC 06/05/22
            if (iFl==(OSF_NumFuels-1) && osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun() && dSelfUtil_GridHarmCredPk > 0.001)
            {  double dTotStdEffTDV = esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daTDVTotal[0] + esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daTDVTotal[1] +
                                      esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot ].daTDVTotal[2];
               BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[IDX_T24_NRES_EU_BT].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );     assert( pEUObj );
               int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));           assert( iEUObjIdx >= 0 );
               double dPropBattTDV=0.0, dPropBattElec=0.0, dPropBattDemand=0.0, dPropBattSrc=0.0, dPropBattCO2=0.0, dPropBattElecSupEnergy=0.0, dPropBattElecSupTDV=0.0;
               if (iEUObjIdx >= 0)
               {  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "ProposedTDV[1]" ,   iCID_EnergyUse ), dPropBattTDV          , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PropElecEnergy" ,   iCID_EnergyUse ), dPropBattElec         , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );   dPropBattElec /= 1000.0;  // kWh -> MWh
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PropElecDemand" ,   iCID_EnergyUse ), dPropBattDemand       , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "ProposedSrc[1]" ,   iCID_EnergyUse ), dPropBattSrc          , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PropTotalC02[1]",   iCID_EnergyUse ), dPropBattCO2          , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PropElecSupEnergy", iCID_EnergyUse ), dPropBattElecSupEnergy, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                  BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PropElecSupTDV",    iCID_EnergyUse ), dPropBattElecSupTDV   , 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                           if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/05/22
                           {  QString sDbgTDVLbl /*= (lEngyCodeYearNum < 2025 ? "TDV" : "SLCC")*/, sDbgTDVUnitLbl = (lEngyCodeYearNum < 2025 ? "kTDV" : "$");      // SAC 12/01/22
                              BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), sDbgTDVLbl, FALSE, 0, -1, 0, BEMO_User, "TDV", 0, osRunInfo.BEMProcIdx() );
                              BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - Self Utilization calc prep: TotStdEff%1 %2 %3/sf | PropBatt%4 %5 %6/sf | PropBattElec %7 MWh  | PropBattDemand %8 kW | PropBattCO2 %9 tonne | PropBattSrc %10 kBtu/sf" ).arg( 
                                                   sDbgTDVLbl, QString::number(dTotStdEffTDV), sDbgTDVUnitLbl, sDbgTDVLbl, QString::number(dPropBattTDV), sDbgTDVUnitLbl, QString::number(dPropBattElec), QString::number(dPropBattDemand), QString::number(dPropBattCO2), QString::number(dPropBattSrc) ) );  
                           }
               }
               if (dTotStdEffTDV > 0 && dPropBattTDV < 0)
               {
                  dSelfUtil_EnergyEffCap = dTotStdEffTDV * dSelfUtil_GridHarmCredPk;
                  dSelfUtil_EnergyEffTDV = std::min( dSelfUtil_EnergyEffCap, (-1.0 * dPropBattTDV) );
                  double dSU_PropBattTDVFrac = -1.0 * dSelfUtil_EnergyEffTDV / dPropBattTDV;
                  double dSU_PropBattTDV    = dFlex_SelfUtilTDVAdj  = dSU_PropBattTDVFrac * dPropBattTDV;
                  double dSU_PropBattElec   = dFlex_SelfUtilElecAdj = dSU_PropBattTDVFrac * dPropBattElec;
                  double dSU_PropBattDemand = dSU_PropBattTDVFrac * dPropBattDemand;
                  double dSU_PropBattSrc    = dFlex_SelfUtilSrcAdj = dSU_PropBattTDVFrac * dPropBattSrc;
                  double dSU_PropBattCO2    = dSU_PropBattTDVFrac * dPropBattCO2;
                           if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/05/22
                           {  QString sDbgTDVLbl /*= (lEngyCodeYearNum < 2025 ? "TDV" : "SLCC")*/, sDbgTDVUnitLbl = (lEngyCodeYearNum < 2025 ? "kTDV" : "$");      // SAC 12/01/22
                              BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), sDbgTDVLbl, FALSE, 0, -1, 0, BEMO_User, "TDV", 0, osRunInfo.BEMProcIdx() );
                              BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - Self Utilization calc: SUCreditEffCap %1 %2/sf | SUCreditEff%3 %4 %5/sf | PropBatt%6Frac %7" ).arg( 
                                                   QString::number(dSelfUtil_EnergyEffCap), sDbgTDVUnitLbl, sDbgTDVLbl, QString::number(dSelfUtil_EnergyEffTDV), sDbgTDVUnitLbl, sDbgTDVLbl, QString::number(dSU_PropBattTDVFrac) ) );  
                           }

                  // start by adjusting BT & EffTot EnergyUse objects w/ Self Util adjustments
                  int iaSelfUtilEndUses[]   = { IDX_T24_NRES_EU_BT, IDX_T24_NRES_EU_EffTot, -1 };
                  double daSelfUtilEUMult[] = {             -1.0  ,              1.0           };
                  int iSelfUtilEUIdx = -1;  double fVal;
                  EnergyUseAdjust aSUAData[] =      { {  "ProposedTDV[1]",     4, 2, 1.0,    dSU_PropBattTDVFrac * dPropBattTDV                              },
                                                      {  "PropElecEnergy",     2, 1, 0.001,  dSU_PropBattTDVFrac * dPropBattElec * 1000.0                    },
                                                      {  "PropTotalEnergy",   -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattElec * 1000.0 / fTotBldgFlrArea  },
                                                      {  "PropElecDemand",    -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattDemand                           },
                                                      {  "PropElecResEnergy", -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattElec * 1000.0 * fResAreaRatio    },
                                                      {  "PropElecTDV[1]",    -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattTDV                    },
                                                      {  "PropElecResTDV[1]", -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattTDV * fResAreaRatio    },
                                                      {  "PropElecSupEnergy", -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattElecSupEnergy          },
                                                      {  "PropElecSupTDV",    -1, 0, 1.0,    dSU_PropBattTDVFrac * dPropBattElecSupTDV             },
                                                      {  "ProposedSrc[1]",    11, 2, 1.0,    dSU_PropBattTDVFrac * dPropBattSrc                    },
                                                //      {  "PropElecC02[1]",    17, 2, 1.0,    dSU_PropBattTDVFrac * dPropBattCO2                    },  - no Flex reported here, so CO2 removed from Batt dissapears entirely
                                                //      {  "PropTotalC02[1]",   19, 2, 1.0,    dSU_PropBattTDVFrac * dPropBattCO2                    },
                                                      {  "",                  -1, 0, 1.0,    0.0   } };
                  QString sResultVal;
                  while (iaSelfUtilEndUses[++iSelfUtilEUIdx] >= 0)
                  {  iEUIdx = iaSelfUtilEndUses[iSelfUtilEUIdx];
                     BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );     assert( pEUObj );
                     int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));           assert( iEUObjIdx >= 0 );
                     if (iEUObjIdx >= 0)
                     {  int iSUPropIdx = -1;
                        while (strlen( aSUAData[++iSUPropIdx].sEnergyUsePropName ) > 0)
                        {
                           BEMPX_GetFloat(   BEMPX_GetDatabaseID( aSUAData[iSUPropIdx].sEnergyUsePropName, iCID_EnergyUse ), fVal, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
                           fVal += (aSUAData[iSUPropIdx].dAdjust * daSelfUtilEUMult[iSelfUtilEUIdx]);
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( aSUAData[iSUPropIdx].sEnergyUsePropName, iCID_EnergyUse ), BEMP_Flt, &fVal, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                           if (aSUAData[iSUPropIdx].iEUseSummaryEnduseArray > 0)
                           {
                              long lDBID_EUseSumProp = BEMPX_GetDatabaseID( QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(aSUAData[iSUPropIdx].iEUseSummaryEnduseArray) ), iCID_EUseSummary );    assert( lDBID_EUseSumProp > 0 );
                              fVal *= aSUAData[iSUPropIdx].dEUseSummaryEnduseMult;
                              if (WithinMargin( fVal, 0.0, 0.001 ))
                                 sResultVal = "--";
                              else
                                 sResultVal = BEMPX_FloatToString( fVal, aSUAData[iSUPropIdx].iEUseSummaryEnduseDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                              BEMPX_SetBEMData( lDBID_EUseSumProp, BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                           }
                  }  }  }
                  // finally - manual edits to EUseSummary to log Flexibility data
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:FlexibilityTDV"           ), BEMP_Flt, &dSU_PropBattTDV       , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_EffTDVCap"       ), BEMP_Flt, &dSelfUtil_EnergyEffCap, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_EffTDV"          ), BEMP_Flt, &dSelfUtil_EnergyEffTDV, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattTDVFrac" ), BEMP_Flt, &dSU_PropBattTDVFrac   , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattTDV"     ), BEMP_Flt, &dSU_PropBattTDV       , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattElec"    ), BEMP_Flt, &dSU_PropBattElec      , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattDemand"  ), BEMP_Flt, &dSU_PropBattDemand    , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattSrc"     ), BEMP_Flt, &dSU_PropBattSrc       , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:SelfUtil_PropBattCO2"     ), BEMP_Flt, &dSU_PropBattCO2       , BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
               }
            }

            // RE-loop through enduse mapping for total storage, since some CompTot enduses (PV & Batt) now exist BELOW CompTot for 2022 analysis - SAC 12/12/21
				iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
				{
   				// store annual energy use & TDV sums by fuel and enduse
					if (iCID_EnergyUse > 0)
					{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );
						if (pEUObj == NULL)
						{	assert( !osRunInfo.IsStdRun() && iFl==0 );	// should need to create EU object if first run & first fuel
                                 if (bHrlyDebugLogging)      // DEBUGGING
                                    BEMPX_WriteLogFile( QString( "   ProcessNonresSimulationResults() - creating EnergyUse object '%1'" ).arg( esEUMap_CECNonRes[iEUIdx].sEnduseName ), NULL, FALSE, TRUE, FALSE );
							pEUObj = BEMPX_CreateObject( iCID_EnergyUse, esEUMap_CECNonRes[iEUIdx].sEnduseName, NULL /*pPar*/, BEMO_User, true /*bDfltPar*/, true /*bAutoCr8*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseName", iCID_EnergyUse ), BEMP_Str, (void*) esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User,
                                                     -1 /*iOccur*/, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );  // -or- BEMS_SimResult
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunResults" ) + iEUIdx, BEMP_Obj, (void*) pEUObj, BEMO_User,
                                                     -1 /*iOccur*/, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );  // -or- BEMS_SimResult   - SAC 9/7/18 - A2030
						}
						else
						{	assert( osRunInfo.IsStdRun() || iFl>0 );		// should NOT have EU object in model if this is the first run, first fuel
						}
						if (pEUObj == NULL)
						{	assert( FALSE );
						}
						else
						{	int iEUObjIdx = BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() );		assert( iEUObjIdx >= 0 );
							double fResult = esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl];
							if (iOrientNum < 1)
								sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
							else
								sPropName = QString( "%1%2EnergyByOrient[%3]" ).arg( sEUPropNameBase, pszaFuelPropName[iFl], QString::number(iOrientNum) );	// S901G
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     if (fBldgResFlrArea > 0)      // SAC 10/31/21 (MFam)
							{  fResult = esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl];
                        if (iOrientNum < 1)
   								sPropName = QString( "%1%2ResEnergy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
   							else
   								sPropName = QString( "%1%2ResEnergyByOrient[%3]" ).arg( sEUPropNameBase, pszaFuelPropName[iFl], QString::number(iOrientNum) );	// S901G
   							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     }

							// then do same for TDV...
							if (osRunInfo.CodeType() == CT_T24N)		// added check to perform TDV only on CT_T24N runs
							{	fResult = esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];
								sPropName = QString( "%1%2TDV" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								if (sSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
								{	fResult = esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl];
									sPropName = QString( "%1%2Src" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
							// 	if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/27/19 - 2022
							// 	{	fResult = esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl];
							// 		sPropName = QString( "%1%2SrcPrm" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
							// 		BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							// 	}
								if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/11/19 - CO2 emissions (tonne) (tic #3106)
								{	fResult = esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl];
									sPropName = QString( "%1%2C02" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}

                        if (fBldgResFlrArea > 0)      // SAC 10/31/21 (MFam)
                        {	fResult = esEUMap_CECNonRes[iEUIdx].daResTDVTotal[iFl];
   								sPropName = QString( "%1%2ResTDV" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
   								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                           if (sResSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
   								{	fResult = esEUMap_CECNonRes[iEUIdx].daResSrcTotal[iFl];
   									sPropName = QString( "%1%2ResSrc" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
   									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   								}
   							// 	if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/27/19 - 2022
   							// 	{	fResult = esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl];
   							// 		sPropName = QString( "%1%2SrcPrm" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
   							// 		BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   							// 	}
   								if (sResCO2EmissionsElecTableName.length() > 1)		// SAC 9/11/19 - CO2 emissions (tonne) (tic #3106)
   								{	fResult = esEUMap_CECNonRes[iEUIdx].daResCO2Total[iFl];
   									sPropName = QString( "%1%2ResC02" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
   									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        }  }
							}
							if (bSetTDSResults)		// SAC 8/26/18 - A2030
							{	fResult = esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl];
								sPropName = QString( "%1%2TDS" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}

							if (iFl == 0 && esEUMap_CECNonRes[iEUIdx].daSupply[0] != 0.0)	// SAC 9/7/18 - A2030 [Elec,TDV] - Elec Supply results
							{	fResult = esEUMap_CECNonRes[iEUIdx].daSupply[0];
								sPropName = QString( "%1ElecSupEnergy" ).arg( sEUPropNameBase );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
							if (iFl == 0 && esEUMap_CECNonRes[iEUIdx].daSupply[1] != 0.0)
							{	fResult = esEUMap_CECNonRes[iEUIdx].daSupply[1];
								sPropName = QString( "%1ElecSupTDV" ).arg( sEUPropNameBase );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
							if (iFl == 0 && esEUMap_CECNonRes[iEUIdx].daSupply[2] != 0.0)
							{	fResult = esEUMap_CECNonRes[iEUIdx].daSupply[2];
								sPropName = QString( "%1ElecSupTDS" ).arg( sEUPropNameBase );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}

   						// SAC 10/8/16 - post elec demand to database
							if (iFl==0 && sHrlyElecDemMultTblCol.length() > 1 && (esEUMap_CECNonRes[iEUIdx].daEnduseTotal[iFl] != 0.0 || esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0.0))
							{	fResult = esEUMap_CECNonRes[iEUIdx].dElecDemand;
								if (iOrientNum < 1)
									sPropName = QString( "%1ElecDemand" ).arg( sEUPropNameBase );
								else
									sPropName = QString( "%1ElecDemandByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );	// S901G
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
                     // Residential demand - SAC 10/31/21 (MFam)
							if (iFl==0 && sResHrlyElecDemMultTblCol.length() > 1 && esEUMap_CECNonRes[iEUIdx].daResEnduseTotal[iFl] != 0.0)
							{	fResult = esEUMap_CECNonRes[iEUIdx].dResElecDemand;
								if (iOrientNum < 1)
									sPropName = QString( "%1ResElecDemand" ).arg( sEUPropNameBase );
								else
									sPropName = QString( "%1ResElecDemandByOrient[%2]" ).arg( sEUPropNameBase, QString::number(iOrientNum) );	// S901G
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fResult, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}
					}
				}	// end of  while (esEUMap_CECNonRes[++iEUIdx]...
			}	// end of  for (iFl...

			// now go BACK through enduses storing total kBTU/ft2-yr sums
			QString sPassFail;
         bool bT24NComplyPasses = true;      // SAC 12/09/21
#define  MAX_T24N_METRIC  4
         QString saT24NCompMetrics[MAX_T24N_METRIC], saT24NCompMetricPassFail[MAX_T24N_METRIC];   double daT24NCompMargin[MAX_T24N_METRIC], daT24NCompPctMargin[MAX_T24N_METRIC];   int iT24NMetricIdx=0;
			double dRndPropTDVTot=0.0, dRndStdTDVTot = 0.0, dRndPropTDVCompTot=0.0, dRndPropTDVEffTot=0.0, dRndStdTDVCompTot=0.0, dRndStdTDVEffTot=0.0;
			double dRndPropSrcTot=0.0, dRndStdSrcTot = 0.0, dRndPropSrcCompTot=0.0, dRndPropSrcEffTot=0.0, dRndStdSrcCompTot=0.0, dRndStdSrcEffTot=0.0;
			double dRndSrcPrmTotMargin=0.0, dRndSrcPrmCompTotMargin=0.0, dRndStdSrcPrmTot = 0.0, dRndStdSrcPrmCompTot=0.0;
			if (fTotBldgFlrArea > 0 && iCID_EnergyUse > 0)
			{	iEUIdx = -1;
				while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL && (iEUIdx != IDX_T24_NRES_EU_EffTot || lEngyCodeYearNum >= 2022))
				{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
					int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
					if (iEUObjIdx >= 0)
					{	double fEUTot = 0, fVal, fTDVTot = 0, fTDSTot = 0, fSrcTot = 0, fSrcPrmTot = 0, fCO2Tot = 0;
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
							{	fTDVTot += esEUMap_CECNonRes[iEUIdx].daTDVTotal[iFl];  // no unit conversion needed for TDV
								if (sSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
									fSrcTot += esEUMap_CECNonRes[iEUIdx].daSrcTotal[iFl];
							// 	if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/27/19 - 2022
							// 		fSrcPrmTot += esEUMap_CECNonRes[iEUIdx].daSrcPrmTotal[iFl];
								if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
									fCO2Tot += RoundVal( esEUMap_CECNonRes[iEUIdx].daCO2Total[iFl], iCO2EmisTotalRnd );
							}
							if (bSetTDSResults)		// SAC 8/26/18 - A2030
								fTDSTot += esEUMap_CECNonRes[iEUIdx].daTDSTotal[iFl];  // no unit conversion needed for TDS
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
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fTDVTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (osRunInfo.IsStdRun() && iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot && iEUIdx != IDX_T24_NRES_EU_Total)		// SAC 6/8/16 - replace real differences w/ sum of rounded differences (tic #1735)
							{	double fPropTDV = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "ProposedTDV", iCID_EnergyUse )+iResSet, fPropTDV, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
								{	assert( FALSE );
								}
								else
								{
								   // SAC 5/8/14 - revise margin results to be consistent w/ rounded values   // SAC 6/8/16 - switched TDV rounding from 1 to 2 decimal places (tic #1735)
									double dStTDV = RoundVal( fTDVTot , 2 );
									double dPrTDV = RoundVal( fPropTDV, 2 );
									if (iEUIdx == IDX_T24_NRES_EU_DHW && dDHWSolPVCredFrac > 0)		// Flexibility Credit calcs - SAC 9/15/20
									{	//double dStdDHWSolThrmlDelta = dStdDHWNoSlrSysTotTDV - fTDVTot;			assert( dStdDHWSolThrmlDelta > 0 );
										double dStdDHWSolThrmlDelta = dStdDHWNoSlrSysTotTDV - (dResStdDHWTotTDV / fTotBldgFlrArea);			assert( dResStdDHWTotTDV > 0 && dStdDHWSolThrmlDelta > 0 );		// SAC 10/8/20 (tic #3218)
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:StdResDHWTotTDV" ), BEMP_Flt, &dResStdDHWTotTDV, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										if (dStdDHWSolThrmlDelta > 0)
										{	dFlexPropTDV  = -1 * dStdDHWSolThrmlDelta * dDHWSolPVCredFrac;		// apply user-specified fraction of PVSolthrml TDV diff as Flex credit
											BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:FlexibilityTDV" ), BEMP_Flt, &dFlexPropTDV, BEMO_User, iResSet, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 9/16/20 (tic #3218)
											if (dTDVof1KWCFIPV < 0)
												dFlexReqdPVKW = dFlexPropTDV / dTDVof1KWCFIPV;
											// round Flex-related results
											dFlexPropTDV = RoundVal( dFlexPropTDV, 2 );
											if (dFlexReqdPVKW > 0)
											{	dFlexReqdPVKW = RoundVal( dFlexReqdPVKW, 1 );
                                          if (bHrlyDebugLogging)      // DEBUGGING
                                             BEMPX_WriteLogFile( QString( "   in ProcessNonresSimulationResults(), Flexibility data:  dStdDHWSolThrmlDelta %1 / dDHWSolPVCredFrac %2 / dFlexPropTDV %3 / dFlexReqdPVKW %4" ).arg(
                                       														QString::number( dStdDHWSolThrmlDelta ), QString::number( dDHWSolPVCredFrac ), QString::number( dFlexPropTDV ), QString::number( dFlexReqdPVKW ) ), NULL, FALSE, TRUE, FALSE );
   										   dRndPropTDVCompTot += dFlexPropTDV;		// apply Flex credit to running PropTDVCompTot - SAC 9/15/20
      										dRndPropTDVEffTot  += dFlexPropTDV;		// apply Flex credit to running PropTDVEffTot - SAC 12/11/21
									}	}  }
									else if (iEUIdx == IDX_T24_NRES_EU_PV && dPrTDV < 0 && dFlexPropTDV < 0)	// Flexibility Credit calcs - SAC 9/15/20
									{	dPrTDV -= dFlexPropTDV;					// adjust PV dPrTDV to EXCLUDE TDV applied to Flex credit (above)
										bPropPVTDVAdjustedForFlex = true;
									}
									else if (iEUIdx == IDX_T24_NRES_EU_BT && dFlex_SelfUtilTDVAdj < 0)	// Self Utilization Flexibility Credit - SAC 06/05/22
									{	//dPrTDV            += dFlex_SelfUtilTDVAdj;
                              dRndPropTDVCompTot += dFlex_SelfUtilTDVAdj;
                              dRndPropTDVEffTot  += dFlex_SelfUtilTDVAdj;
									   dRndPropTDVTot     += dFlex_SelfUtilTDVAdj;
										//bPropPVTDVAdjustedForFlex = true;
									}

									if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
									{	dRndPropTDVCompTot += dPrTDV;
										dRndStdTDVCompTot  += dStTDV;
									   if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
									   {	dRndPropTDVEffTot += dPrTDV;
									   	dRndStdTDVEffTot  += dStTDV;
									}  }
									dRndStdTDVTot  += dStTDV;
									dRndPropTDVTot += dPrTDV;

								   double fCompMargin = (dStTDV - dPrTDV);
								   double fPctImprove = (dStTDV > 0 ? ((dStTDV - dPrTDV) * 100.0 / dStTDV) : 0.0);
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
						}	}

						if (osRunInfo.CodeType() == CT_T24N && sSrcEnergyTableName.length() > 1)		// SAC 6/27/19 - 2022
						{
							sPropName = QString( "%1Src" ).arg( sEUPropNameBase );
							sPropName.replace( "Prop", "Proposed" );    // unfortunate inconsistency in property naming...
							sPropName.replace( "Std" , "Standard" );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fSrcTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (osRunInfo.IsStdRun() && iEUIdx != IDX_T24_NRES_EU_Total && iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot)
							{	double fPropSrc = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "ProposedSrc", iCID_EnergyUse )+iResSet, fPropSrc, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
								{	assert( FALSE );
								}
								else
								{	//double fCompMarginReal = fSrcTot - fPropSrc;
									//double fPctImproveReal = ((fSrcTot > 0 ? (fSrcTot - fPropSrc) / fSrcTot : 0) * 100.0);
									double dStSrc = RoundVal( fSrcTot , 2 );
									double dPrSrc = RoundVal( fPropSrc, 2 );

									if (iEUIdx == IDX_T24_NRES_EU_BT && dFlex_SelfUtilSrcAdj != 0)	   // Self Utilization Flexibility Credit - SAC 06/05/22
									{	//dPrSrc            += dFlex_SelfUtilSrcAdj;
                              dRndPropSrcCompTot += dFlex_SelfUtilSrcAdj;
                              dRndPropSrcEffTot  += dFlex_SelfUtilSrcAdj;
   									dRndPropSrcTot     += dFlex_SelfUtilSrcAdj;
										//bPropPVTDVAdjustedForFlex = true;
									}

                           // revised logic to sum Comp & Eff totals during this round of EU looping and SET those data to BEMBase later, down below - SAC 12/12/21
                           if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
                           {  // sum PV & Battery into CompTot for 2022+ analysis - SAC 12/12/21
										dRndPropSrcCompTot += dPrSrc;
										dRndStdSrcCompTot  += dStSrc;
                              if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
                              {	dRndPropSrcEffTot += dPrSrc;
											dRndStdSrcEffTot  += dStSrc;
                           }	}
									dRndStdSrcTot  += dStSrc;
									dRndPropSrcTot += dPrSrc;

									double fCompMargin = (dStSrc - dPrSrc);
   								double fPctImprove = (dStSrc > 0 ? ((dStSrc - dPrSrc) * 100.0 / dStSrc) : 0.0);
   								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
						}	}
						if (osRunInfo.CodeType() == CT_T24N && sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
						{
							sPropName = QString( "%1TotalC02" ).arg( sEUPropNameBase );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, BEMP_Flt, &fCO2Tot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (osRunInfo.IsStdRun())
							{	double fPropCO2 = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PropTotalC02", iCID_EnergyUse )+iResSet, fPropCO2, 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
								{	assert( FALSE );
								}
								else
								{	double fMargin = fCO2Tot - fPropCO2;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "MarginC02", iCID_EnergyUse )+iResSet, BEMP_Flt, &fMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
						}	}

      				// SAC 8/26/18 - TDS storage
						if (bSetTDSResults)
						{
							sPropName = QString( "%1TDS" ).arg( sEUPropNameBase );
							sPropName.replace( "Prop", "Proposed" );    // unfortunate inconsistency in property naming...
							sPropName.replace( "Std" , "Standard" );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), BEMP_Flt, &fTDSTot, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}

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
							         //	else if (sCostMethod.compare("Average State Cost", Qt::CaseInsensitive))
							         //		sLogMsg = QString( "  ProcessSimulationResults - Error - unrecognized Proj:%1 '%2'" ).arg( sCostMethodProp, sCostMethod );
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
									{	//double fCompMarginReal = fTotalCost - fPropCost;
										//double fPctImproveReal = ((fTotalCost > 0 ? (fTotalCost - fPropCost) / fTotalCost : 0) * 100.0);
									
										double dStCost = RoundVal( fTotalCost, 0 );		// ensure margin results consistent w/ rounded values (dollars)
										double dPrCost = RoundVal( fPropCost , 0 );
										double fCompMargin = (dStCost - dPrCost);
										double fPctImprove = (dStCost > 0 ? ((dStCost - dPrCost) * 100.0 / dStCost) : 0.0);

										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
										sPassFail = (fCompMargin > -0.001 /*>=0*/ ? "PASS" : "FAIL");
	
												sLogMsg = QString( "  PerfSim_E+ - Final Result: %1  -- compliance margin: %2 (%3%)" ).arg( sPassFail, QString::number(fCompMargin), QString::number(fPctImprove, 'f', 2) );
												BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}	}
							}
						}
					}
				}	// end of:  while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL...

            // added separate section to store rounded results for CompTot, EffTot & overall Tot enduses - SAC 12/12/21
				if (osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun())
				{	BEMObject* pEUObj;
               int iEUObjIdx;
               // IDX_T24_NRES_EU_EffTot
               if (lEngyCodeYearNum >= 2022)
               {  pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[IDX_T24_NRES_EU_EffTot].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
					   iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
   					if (iEUObjIdx >= 0)
                  {  // TDV
                     double fCompMargin = (dRndStdTDVEffTot - dRndPropTDVEffTot);
   						double fPctImprove = (dRndStdTDVEffTot > 0 ? ((dRndStdTDVEffTot - dRndPropTDVEffTot) * 100.0 / dRndStdTDVEffTot) : 0.0);
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     if (fCompMargin <= -0.001)       // SAC 12/09/21
                        bT24NComplyPasses = false;
                     assert( iT24NMetricIdx < MAX_T24N_METRIC );
                     if (iT24NMetricIdx < MAX_T24N_METRIC)
                     {  saT24NCompMetrics[       iT24NMetricIdx  ] = (lEngyCodeYearNum < 2025 ? "EffTDV" : "EffSLCC");     // SAC 12/01/22
                        saT24NCompMetricPassFail[iT24NMetricIdx  ] = (fCompMargin <= -0.001 ? "Fail" : "Pass");      // SAC 12/13/21
                        daT24NCompMargin[        iT24NMetricIdx  ] = fCompMargin;
                        daT24NCompPctMargin[     iT24NMetricIdx++] = fPctImprove;
							}
                     // Src
                     fCompMargin =  dRndStdSrcEffTot - dRndPropSrcEffTot;
   						fPctImprove = (dRndStdSrcEffTot > 0 ? ((dRndStdSrcEffTot - dRndPropSrcEffTot) * 100.0 / dRndStdSrcEffTot) : 0.0);
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
               }  }
               // IDX_T24_NRES_EU_CompTot
               pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[IDX_T24_NRES_EU_CompTot].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
					iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
   				if (iEUObjIdx >= 0)
               {  // TDV
                  double fCompMargin =  dRndStdTDVCompTot - dRndPropTDVCompTot;
   					double fPctImprove = (dRndStdTDVCompTot > 0 ? ((dRndStdTDVCompTot - dRndPropTDVCompTot) * 100.0 / dRndStdTDVCompTot) : 0.0);
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  if (fCompMargin <= -0.001)       // SAC 12/09/21
                     bT24NComplyPasses = false;
                  assert( iT24NMetricIdx < MAX_T24N_METRIC );
                  if (iT24NMetricIdx < MAX_T24N_METRIC)
                  {  saT24NCompMetrics[       iT24NMetricIdx  ] = (lEngyCodeYearNum < 2025 ? "CmpTDV" : "CmpSLCC");   // SAC 12/01/22
                     saT24NCompMetricPassFail[iT24NMetricIdx  ] = (fCompMargin <= -0.001 ? "Fail" : "Pass");      // SAC 12/13/21
                     daT24NCompMargin[        iT24NMetricIdx  ] = fCompMargin;
                     daT24NCompPctMargin[     iT24NMetricIdx++] = fPctImprove;
						}
                  // Src
                  fCompMargin =  dRndStdSrcCompTot - dRndPropSrcCompTot;
   					fPctImprove = (dRndStdSrcCompTot > 0 ? ((dRndStdSrcCompTot - dRndPropSrcCompTot) * 100.0 / dRndStdSrcCompTot) : 0.0);
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  if (lEngyCodeYearNum >= 2022)
                  {  if (fCompMargin <= -0.001)       // SAC 12/09/21
                        bT24NComplyPasses = false;
                     assert( iT24NMetricIdx < MAX_T24N_METRIC );
                     if (iT24NMetricIdx < MAX_T24N_METRIC)
                     {  saT24NCompMetrics[       iT24NMetricIdx  ] = "Source";
                        saT24NCompMetricPassFail[iT24NMetricIdx  ] = (fCompMargin <= -0.001 ? "Fail" : "Pass");      // SAC 12/13/21
                        daT24NCompMargin[        iT24NMetricIdx  ] = fCompMargin;
                        daT24NCompPctMargin[     iT24NMetricIdx++] = fPctImprove;
               }	}  }
               // IDX_T24_NRES_EU_Total
               pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[IDX_T24_NRES_EU_Total].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
					iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
   				if (iEUObjIdx >= 0)
               {  // TDV
                  double fCompMargin =  dRndStdTDVTot - dRndPropTDVTot;
   					double fPctImprove = (dRndStdTDVTot > 0 ? ((dRndStdTDVTot - dRndPropTDVTot) * 100.0 / dRndStdTDVTot) : 0.0);
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveTDV", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  // Src
                  fCompMargin =  dRndStdSrcTot - dRndPropSrcTot;
   					fPctImprove = (dRndStdSrcTot > 0 ? ((dRndStdSrcTot - dRndPropSrcTot) * 100.0 / dRndStdSrcTot) : 0.0);
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompMarginSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fCompMargin, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctImproveSrc", iCID_EnergyUse )+iResSet, BEMP_Flt, &fPctImprove, BEMO_User, iEUObjIdx, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
               }

				   // move pass/fail logic for T24N down HERE to allow for it to rely on multiple comparisons - SAC 12/09/21
               if (iT24NMetricIdx == 0)
                  bT24NComplyPasses = false;
               sPassFail = (bT24NComplyPasses ? "PASS" : "FAIL");

               if (iT24NMetricIdx > 0)
               {  if (iT24NMetricIdx == 1)
                     sLogMsg = QString( "  PerfSim_E+ - Final Result: %1  -- compliance margin: %2 (%3%)" ).arg( sPassFail, QString::number(daT24NCompMargin[0]), QString::number(daT24NCompPctMargin[0], 'f', 2) );
                  else
                     for (int iT24NM=0; iT24NM < iT24NMetricIdx; iT24NM++)
                     {  if (iT24NM == 0)
                           sLogMsg = QString( "  PerfSim_E+ - Final Result: %1  -- compliance margins:  %2 %3 (%4%)" ).arg( sPassFail, saT24NCompMetrics[iT24NM], QString::number(daT24NCompMargin[iT24NM]), QString::number(daT24NCompPctMargin[iT24NM], 'f', 2) );
                        else
                           sLogMsg += QString( " | %1 %2 (%3%)" ).arg( saT24NCompMetrics[iT24NM], QString::number(daT24NCompMargin[iT24NM]), QString::number(daT24NCompPctMargin[iT24NM], 'f', 2) );
                     }
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            }  }
			}  // energy use totals for this run posted to BEMBase

			if (iCID_EUseSummary > 0 && fTotBldgFlrArea > 0)
			{						if (bVerbose || bHrlyDebugLogging)      // DEBUGGING
										BEMPX_WriteLogFile( "  PerfSim_E+ - Posting results to BEMBase", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				if (BEMPX_GetNumObjects( iCID_EUseSummary, BEMO_User, osRunInfo.BEMProcIdx() ) <= iResSet)
				{
                  //BEMPX_WriteLogFile( QString( "   ProcessNonresSimulationResults() - creating EUseSummary object %1 '%2'" ).arg( QString::number( iResSet ), sResultSetName ), NULL, FALSE, TRUE, FALSE );
					BEMObject* pEUseSmryObj = BEMPX_CreateObject( iCID_EUseSummary, sResultSetName.toLocal8Bit().constData() /*szName*/, NULL /*pPar*/, BEMO_User, true /*bDfltPar*/, true /*bAutoCr8*/, osRunInfo.BEMProcIdx() );
               long lDBID_Proj_EUseSummaryRef = BEMPX_GetDatabaseID( "Proj:EUseSummaryRef" );      // needed for NRCCPRF XML population - SAC 11/27/20
               if (pEUseSmryObj && lDBID_Proj_EUseSummaryRef > 0)
   					BEMPX_SetBEMData( lDBID_Proj_EUseSummaryRef, BEMP_Obj, pEUseSmryObj, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}
				if (BEMPX_GetNumObjects( iCID_EUseSummary, BEMO_User, osRunInfo.BEMProcIdx() ) > iResSet)
				{
					long l0 = 0;
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded                                 , BEMP_Int, &l0, BEMO_User, iResSet, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_Int, &l0, BEMO_User, iResSet, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						if (!sPassFail.isEmpty())
						{	if (osRunInfo.NumQuickAnalysisPeriods() > 0)		// SAC 11/11/14 - if performing QuickAnalysis, do NOT store final PASS/FAIL string to database
								sPassFail = " ";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PassFail", iCID_EUseSummary ), BEMP_QStr, (void*) &sPassFail, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

                     // store pass/fail messages by compliance metric - SAC 12/13/21
                     for (int iT24NM=0; iT24NM < iT24NMetricIdx; iT24NM++)
                     {  if (!saT24NCompMetricPassFail[iT24NM].isEmpty())
      							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "MetricPassFail", iCID_EUseSummary ) + iT24NM, BEMP_QStr, (void*) &saT24NCompMetricPassFail[iT24NM], BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     }

							// SAC 6/8/16 - store new PctSav* values & labels (tic #1735)
							double fRndTDVTotPctSav     = (dRndStdTDVTot     > 0 ? ((dRndStdTDVTot     - dRndPropTDVTot    ) * 100.0 / dRndStdTDVTot    ) : 0);
							double fRndTDVCompTotPctSav = (dRndStdTDVCompTot > 0 ? ((dRndStdTDVCompTot - dRndPropTDVCompTot) * 100.0 / dRndStdTDVCompTot) : 0);
							QString sRndTDVTotPctSav     = "-";
							QString sRndTDVCompTotPctSav = "-";
							if (osRunInfo.NumQuickAnalysisPeriods() < 1)
							{	if (fRndTDVTotPctSav <= -0.0001 || fRndTDVTotPctSav >= 0.0001)
									sRndTDVTotPctSav = QString::number(fRndTDVTotPctSav, 'f', 1);
								if (fRndTDVCompTotPctSav <= -0.0001 || fRndTDVCompTotPctSav >= 0.0001)
									sRndTDVCompTotPctSav = QString::number(fRndTDVCompTotPctSav, 'f', 1);
                        if (lEngyCodeYearNum < 2025)     // SAC 12/01/22
								{  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsTDV",     iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsCmpTDV",  iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        }
                        else
								{  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsSLCC",    iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsCmpSLCC", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        }
							}
                     if (lEngyCodeYearNum < 2025)     // SAC 12/01/22
   						{  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavTDVLbl"   ,  iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavCmpTDVLbl",  iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     }
                     else
   						{  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavSLCCLbl"   , iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavCmpSLCCLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     }
                     if (lEngyCodeYearNum >= 2022)    // SAC 12/12/21
                     {	double fRndTDVEffTotPctSav  = (dRndStdTDVEffTot  > 0 ? ((dRndStdTDVEffTot - dRndPropTDVEffTot) * 100.0 / dRndStdTDVEffTot ) : 0);
   							QString sRndTDVEffTotPctSav  = "-";
   							if (osRunInfo.NumQuickAnalysisPeriods() < 1)
   							{	if (fRndTDVEffTotPctSav <= -0.0001 || fRndTDVEffTotPctSav >= 0.0001)
   									sRndTDVEffTotPctSav = QString::number(fRndTDVEffTotPctSav, 'f', 1);
                           if (lEngyCodeYearNum < 2025)     // SAC 12/01/22
      								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsEffTDV",  iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVEffTotPctSav , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                           else
      								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsEffSLCC", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndTDVEffTotPctSav , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   							}
                        if (lEngyCodeYearNum < 2025)     // SAC 12/01/22
      							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavEffTDVLbl",  iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVEffTotPctSav , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        else
      							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavEffSLCCLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndTDVEffTotPctSav , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                     }

							if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
							{	double fRndSrcTotPctSav     = (dRndStdSrcTot     > 0 ? ((dRndStdSrcTot     - dRndPropSrcTot    ) * 100.0 / dRndStdSrcTot    ) : 0);
								double fRndSrcCompTotPctSav = (dRndStdSrcCompTot > 0 ? ((dRndStdSrcCompTot - dRndPropSrcCompTot) * 100.0 / dRndStdSrcCompTot) : 0);
								QString sRndSrcTotPctSav     = "-";
								QString sRndSrcCompTotPctSav = "-";
								if (osRunInfo.NumQuickAnalysisPeriods() < 1)
								{	if (fRndSrcTotPctSav <= -0.0001 || fRndSrcTotPctSav >= 0.0001)
										sRndSrcTotPctSav = QString::number(fRndSrcTotPctSav, 'f', 1);
									if (fRndSrcCompTotPctSav <= -0.0001 || fRndSrcCompTotPctSav >= 0.0001)
										sRndSrcCompTotPctSav = QString::number(fRndSrcCompTotPctSav, 'f', 1);
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsSrc",    iCID_EUseSummary ), BEMP_Flt, (void*) &fRndSrcTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsCmpSrc", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndSrcCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavSrcLbl"   , iCID_EUseSummary ), BEMP_QStr, (void*) &sRndSrcTotPctSav    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavCmpSrcLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndSrcCompTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        if (lEngyCodeYearNum >= 2022)    // SAC 12/12/21
                        {	double fRndSrcEffTotPctSav  = (dRndStdSrcEffTot  > 0 ? ((dRndStdSrcEffTot - dRndPropSrcEffTot) * 100.0 / dRndStdSrcEffTot ) : 0);
   								QString sRndSrcEffTotPctSav = "-";
   								if (osRunInfo.NumQuickAnalysisPeriods() < 1)
   								{	if (fRndSrcEffTotPctSav <= -0.0001 || fRndSrcEffTotPctSav >= 0.0001)
   										sRndSrcEffTotPctSav = QString::number(fRndSrcEffTotPctSav, 'f', 1);
   									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsEffSrc", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndSrcEffTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   								}
   								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavEffSrcLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndSrcEffTotPctSav, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        }
							}
						// 	if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
						// 	{	double fRndSrcPrmTotPctSav     = (dRndStdSrcPrmTot     > 0 ? (dRndSrcPrmTotMargin     * 100.0 / dRndStdSrcPrmTot    ) : 0);
						// 		double fRndSrcPrmCompTotPctSav = (dRndStdSrcPrmCompTot > 0 ? (dRndSrcPrmCompTotMargin * 100.0 / dRndStdSrcPrmCompTot) : 0);
						// 		QString sRndSrcPrmTotPctSav     = "-";
						// 		QString sRndSrcPrmCompTotPctSav = "-";
						// 		if (osRunInfo.NumQuickAnalysisPeriods() < 1)
						// 		{	if (fRndSrcPrmTotPctSav <= -0.0001 || fRndSrcPrmTotPctSav >= 0.0001)
						// 				sRndSrcPrmTotPctSav = QString::number(fRndSrcPrmTotPctSav, 'f', 1);
						// 			if (fRndSrcPrmCompTotPctSav <= -0.0001 || fRndSrcPrmCompTotPctSav >= 0.0001)
						// 				sRndSrcPrmCompTotPctSav = QString::number(fRndSrcPrmCompTotPctSav, 'f', 1);
						// 			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsSrcPrm",    iCID_EUseSummary ), BEMP_Flt, (void*) &fRndSrcPrmTotPctSav    , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						// 			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavingsCmpSrcPrm", iCID_EUseSummary ), BEMP_Flt, (void*) &fRndSrcPrmCompTotPctSav, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						// 		}
						// 		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavSrcPrmLbl"   , iCID_EUseSummary ), BEMP_QStr, (void*) &sRndSrcPrmTotPctSav    , BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						// 		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PctSavCmpSrcPrmLbl", iCID_EUseSummary ), BEMP_QStr, (void*) &sRndSrcPrmCompTotPctSav, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						// 	}
						}
	
				      // GENERATION & STORAGE OF SIMULATION STATUS MESSAGE
						int iSimIdx = (!osRunInfo.IsStdRun() ? 0 : (osRunInfo.StoreHourlyResults() ? 2 : 1));
                  if (!osRunInfo.SkippingEPlusSim())     // SAC 12/08/21
					   {  //	sLogMsg = (osWrap.GetBool_SimCompleted() ? "Completed" : "")
   						sLogMsg = (osWrap.GetBool_SimCompletedSuccessfully( osRunInfo.OSRunIdx() ) ? "E+ Successful" : "E+ Unsuccessful");
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
                     osRunInfo.AddToSimStatusMsg( sLogMsg );
                  }
                  sLogMsg = osRunInfo.SimStatusMsg();    // SAC 12/08/21
					         //	QString sTempDbgMsg;		sTempDbgMsg = QString( "Setting EUseSummary:SimSummary[%1] (%2) -> %3" ).arg( QString::number(iSimIdx+1), QString::number(BEMPX_GetDatabaseID( "SimSummary", iCID_EUseSummary ) + iSimIdx), sLogMsg );
					         //	BEMMessageBox( sTempDbgMsg );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "SimSummary", iCID_EUseSummary ) + iSimIdx, BEMP_QStr, (void*) &sLogMsg, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
													if (bVerbose)
													{	sLogMsg = "  PerfSim_E+ - " + sLogMsg;
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
					         //	std::string	sSimErrPathFile = osWrap.Get_SimErrPathFile();
					         //	QString sSimInfo = QString::asprintf( "ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s",
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
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[2]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[3]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[4]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[11]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
					   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[14]", iCID_EUseSummary ), BEMP_Str, "Proposed"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[17]", iCID_EUseSummary ), BEMP_Str, "Prop Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[18]", iCID_EUseSummary ), BEMP_Str, "Prop Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[19]", iCID_EUseSummary ), BEMP_Str, "Prop Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
	
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[1]", iCID_EUseSummary ), BEMP_Str, "End Use"      , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[2]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[3]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					      // SAC 11/17/14 - modified label to include TDV in title following Design and switch units from kTDV/.. to kBtu/..
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[4]", iCID_EUseSummary ), BEMP_Str, "Design TDV"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[11]", iCID_EUseSummary ), BEMP_Str, "Source Energy", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[14]", iCID_EUseSummary ), BEMP_Str, "Src 2 Energy" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
							{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[17]", iCID_EUseSummary ), BEMP_Str, "Electric CO2" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[18]", iCID_EUseSummary ), BEMP_Str, "Fuel CO2"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[19]", iCID_EUseSummary ), BEMP_Str, "Total CO2"    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[2]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[3]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[4]", iCID_EUseSummary ), BEMP_Str, (lEngyCodeYearNum >= 2025 ? "($/ft²-yr)" : "(kBtu/ft²-yr)"), BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );   // updated TDV units for 2025 from kBtu/ft²-yr -> $/ft²-yr - SAC 10/25/22
							if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[11]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[14]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
							{	QString sCO2EmisResLabel;
								if (!sCO2EmissionsResultsUnit.isEmpty())
									sCO2EmisResLabel = QString( "Emis. (%1)" ).arg( sCO2EmissionsResultsUnit );
								else
									sCO2EmisResLabel = "Emis. (tonne)";
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[17]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[18]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[19]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}
						else if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[2]", iCID_EUseSummary ), BEMP_Str, "Electricity"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[3]", iCID_EUseSummary ), BEMP_Str, "Natural Gas"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							QString sOtherFuelLabel;
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EnergyCostOtherFuelLabel" ), sOtherFuelLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) || sOtherFuelLabel.length() < 3 ||
									!sOtherFuelLabel.compare("Natural Gas", Qt::CaseInsensitive))		// SAC 10/28/15 - prevent double reporting of 'Natural Gas'
								sOtherFuelLabel = "Other Fuel";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[4]", iCID_EUseSummary ), BEMP_QStr, (void*) &sOtherFuelLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[2]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[3]", iCID_EUseSummary ), BEMP_Str, "Site (therms)", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[4]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
						}
		
						iEUIdx = -1;
						while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)
						{
							sPropName = QString( "Enduse%1[1]" ).arg( QString::number(iEUIdx+1) );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_Str, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
					}
					else
					{
						if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[5]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[6]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[7]", iCID_EUseSummary ), BEMP_Str, "Standard"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[5]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[6]", iCID_EUseSummary ), BEMP_Str, "Design"       , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[7]", iCID_EUseSummary ), BEMP_Str, "Design TDV"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[5]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[6]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[7]", iCID_EUseSummary ), BEMP_Str, (lEngyCodeYearNum >= 2025 ? "($/ft²-yr)" : "(kBtu/ft²-yr)"), BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );   // updated TDV units for 2025 from kBtu/ft²-yr -> $/ft²-yr - SAC 10/25/22

                     QString qsCompMargStr, qsCompMargTemp;
                     BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), qsCompMargTemp, FALSE, 0, -1, 0, BEMO_User, "TDV", 0, osRunInfo.BEMProcIdx() );   // SAC 01/26/23
                     qsCompMargStr = QString( "%1 Margin" ).arg( qsCompMargTemp );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[8]", iCID_EUseSummary ), BEMP_Str, "Compliance"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
   						//BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[8]", iCID_EUseSummary ), BEMP_Str, (lEngyCodeYearNum >= 2025 ? "SLCC Margin" : "TDV Margin"   ), BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );   // SAC 12/01/22
   						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &qsCompMargStr , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );   // SAC 12/01/22
   						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[8]", iCID_EUseSummary ), BEMP_Str, (lEngyCodeYearNum >= 2025 ? "($/ft²-yr)"  : "(kBtu/ft²-yr)"), BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );   // updated TDV units for 2025 from kBtu/ft²-yr -> $/ft²-yr - SAC 10/25/22

							if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
							{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[12]", iCID_EUseSummary ), BEMP_Str, "Standard"      , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[12]", iCID_EUseSummary ), BEMP_Str, "Source Energy" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[12]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[13]", iCID_EUseSummary ), BEMP_Str, "Compliance"    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[13]", iCID_EUseSummary ), BEMP_Str, "Src Margin"    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[13]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
						   // {	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[15]", iCID_EUseSummary ), BEMP_Str, "Standard"      , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[15]", iCID_EUseSummary ), BEMP_Str, "Src 2 Energy"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[15]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[16]", iCID_EUseSummary ), BEMP_Str, "Compliance"    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[16]", iCID_EUseSummary ), BEMP_Str, "Src 2 Margin"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[16]", iCID_EUseSummary ), BEMP_Str, "(kBtu/ft²-yr)" , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						   // }
							if (sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
							{	QString sCO2EmisResLabel, sCO2EmisMargResLabel;
								if (!sCO2EmissionsResultsUnit.isEmpty())
								{	sCO2EmisResLabel = QString( "Emis. (%1)" ).arg( sCO2EmissionsResultsUnit );
									sCO2EmisMargResLabel = QString( "Margin (%1)" ).arg( sCO2EmissionsResultsUnit );
								}
								else
								{	sCO2EmisResLabel = "Emis. (tonne)";
									sCO2EmisMargResLabel = "Margin (tonne)";
								}
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[20]", iCID_EUseSummary ), BEMP_Str, "Std Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[21]", iCID_EUseSummary ), BEMP_Str, "Std Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[22]", iCID_EUseSummary ), BEMP_Str, "Std Design"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[20]", iCID_EUseSummary ), BEMP_Str, "Electric CO2", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[21]", iCID_EUseSummary ), BEMP_Str, "Fuel CO2"    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[22]", iCID_EUseSummary ), BEMP_Str, "Total CO2"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[20]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[21]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[22]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[23]", iCID_EUseSummary ), BEMP_Str, "CO2"         , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[23]", iCID_EUseSummary ), BEMP_Str, "Emissions"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[23]", iCID_EUseSummary ), BEMP_QStr, (void*) &sCO2EmisMargResLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}

                           //if (bHrlyDebugLogging)      // DEBUGGING - SAC 06/05/22
                           //   BEMPX_WriteLogFile( QString( "      ProcessNonresSimulationResults() - about to store DHWSolPVCred Flexibility title/data to EUseSummary" ) );  
							if (dDHWSolPVCredFrac > 0 || dFlex_SelfUtilTDVAdj < 0.0)		// Flexibility Credit reporting - SAC 9/15/20
							{	if (dFlex_SelfUtilTDVAdj < 0.0)
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[1]", iCID_EUseSummary ), BEMP_Str, "Self Utilization", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                        else
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[1]", iCID_EUseSummary ), BEMP_Str, "Flexibility"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								QString qsFlexDashes = "--";
								QString qsFlexPropTDV, qsFlexMargTDV, qsFlexPropElec, qsFlexPropSrc, qsFlexMargSrc;
                        if (dDHWSolPVCredFrac > 0)
   							{	qsFlexPropElec = qsFlexPropSrc = qsFlexMargSrc = qsFlexDashes;
                           if (dFlexPropTDV < 0)
   								{	qsFlexPropTDV = BEMPX_FloatToString(       dFlexPropTDV , 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
   									qsFlexMargTDV = BEMPX_FloatToString( (-1 * dFlexPropTDV), 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
   								}
   								else
   									qsFlexPropTDV = qsFlexMargTDV = qsFlexDashes;
                        }
                        else     // Self Utilization Flexibility - SAC 06/05/22
                        {  qsFlexPropTDV  = BEMPX_FloatToString(       dFlex_SelfUtilTDVAdj  , 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                           qsFlexMargTDV  = BEMPX_FloatToString( (-1 * dFlex_SelfUtilTDVAdj ), 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                           qsFlexPropElec = BEMPX_FloatToString(       dFlex_SelfUtilElecAdj , 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                           qsFlexPropSrc  = BEMPX_FloatToString(       dFlex_SelfUtilSrcAdj  , 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                           qsFlexMargSrc  = BEMPX_FloatToString( (-1 * dFlex_SelfUtilSrcAdj ), 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
                        }
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[2]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexPropElec, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[3]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexDashes  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[4]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexPropTDV , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[5]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexDashes  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[6]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexDashes  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[7]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexDashes  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[8]" , iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexMargTDV , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[11]", iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexPropSrc , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[12]", iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexDashes  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EnduseFlex[13]", iCID_EUseSummary ), BEMP_QStr, (void*) &qsFlexMargSrc , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                              //	BEMPX_WriteLogFile( QString( "   in ProcessNonresSimulationResults(), EnduseFlex[2-8] set + ReqdPV_SolThrml to %1" ).arg( QString::number(dFlexReqdPVKW) ), NULL, FALSE, TRUE, FALSE );
								if (dDHWSolPVCredFrac > 0 && dFlexReqdPVKW > 0)
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ReqdPV_SolThrml", iCID_EUseSummary ), BEMP_Flt, (void*) &dFlexReqdPVKW, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}
						else if (osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC)		// for CT_S901G runs 
						{	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[5]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[6]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[7]", iCID_EUseSummary ), BEMP_Str, "Baseline"     , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[5]", iCID_EUseSummary ), BEMP_Str, "Electricity"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[6]", iCID_EUseSummary ), BEMP_Str, "Natural Gas"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							QString sOtherFuelLabel;
							if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EnergyCostOtherFuelLabel" ), sOtherFuelLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) || sOtherFuelLabel.length() < 3 ||
									!sOtherFuelLabel.compare("Natural Gas", Qt::CaseInsensitive))		// SAC 10/28/15 - prevent double reporting of 'Natural Gas'
								sOtherFuelLabel = "Other Fuel";
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[7]", iCID_EUseSummary ), BEMP_QStr, (void*) &sOtherFuelLabel, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[5]", iCID_EUseSummary ), BEMP_Str, "Site (MWh)"   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[6]", iCID_EUseSummary ), BEMP_Str, "Site (therms)", BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[7]", iCID_EUseSummary ), BEMP_Str, "Site (MBtu)"  , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );	// SAC 10/28/15 - therms -> MBtu

							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title1[8]", iCID_EUseSummary ), BEMP_Str, "Energy"       , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title2[8]", iCID_EUseSummary ), BEMP_Str, "Cost"         , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Title3[8]", iCID_EUseSummary ), BEMP_Str, "Summary"      , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						}
					}
	
			      // includes TDV & comp margin retrieval & setting (if present in data model)
					QString sPropName2, sResultVal;
					//double dRndResSum[5] = { 0.0,0.0,0.0,0.0,0.0 };
               double dEnduseRndSums[3][5] = { {0.0,0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0,0.0} };   // [3] => Eff, Comp & Tot - SAC 12/12/21
					iEUIdx = -1;
					while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL && (iEUIdx != IDX_T24_NRES_EU_EffTot || lEngyCodeYearNum >= 2022))
					{	BEMObject* pEUObj = BEMPX_GetObjectByName( iCID_EnergyUse, iError, esEUMap_CECNonRes[iEUIdx].sEnduseName, BEMO_User, osRunInfo.BEMProcIdx() );		assert( pEUObj );
						int iEUObjIdx = (pEUObj == NULL ? -1 : BEMPX_GetObjectIndex( pEUObj->getClass(), pEUObj, osRunInfo.BEMProcIdx() ));					assert( iEUObjIdx >= 0 );
						if (iEUObjIdx >= 0)
						{	double fVal[8] = {0,0,0,0,0,0,0,0};
							for (iFl=0; iFl < OSF_NumFuels; iFl++)
							{
								sPropName = QString( "%1%2Energy" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[iFl], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[iFl] = 0;
							}
							if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs ONLY
							{	fVal[1] += fVal[2];   fVal[2] = 0;	  // sum NatGas & Other fuel together into fVal[1] and zero out fVal[2]
								sPropName = QString( "%1TDV" ).arg( (!osRunInfo.IsStdRun() ? "Proposed" : "Standard") );
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, fVal[2], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[2] = 0;
								if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
								{	sPropName = QString( "%1Src" ).arg( (!osRunInfo.IsStdRun() ? "Proposed" : "Standard") );
									if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, fVal[3], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
										fVal[3] = 0;
								}

								if ( osRunInfo.IsStdRun() && dFlexPropTDV < 0 &&
									  ( iEUIdx == IDX_T24_NRES_EU_CompTot ||
                               iEUIdx == IDX_T24_NRES_EU_EffTot  ||     // SAC 12/11/21
										(iEUIdx == IDX_T24_NRES_EU_PV    &&  bPropPVTDVAdjustedForFlex) ||
										(iEUIdx == IDX_T24_NRES_EU_Total && !bPropPVTDVAdjustedForFlex) ) )		// Flexibility Credit reporting - SAC 9/15/20
								{	// adjust previously stored Proposed result to account for dFlexPropTDV
									sPropName = QString( "Enduse%1[4]" ).arg( QString::number(iEUIdx+1) );
									QString qsPropTDV;
									if (BEMPX_GetString( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), qsPropTDV, FALSE, 0, -1, iResSet, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ) && qsPropTDV.length() > 2)
									{	double dPropFlexAdjVal = atof( qsPropTDV.toLocal8Bit().constData() );
										double dPropFlexAdjMult = (iEUIdx == IDX_T24_NRES_EU_PV ? -1.0 : 1.0);
										dPropFlexAdjVal += (dPropFlexAdjMult * dFlexPropTDV);
										if (iEUIdx == IDX_T24_NRES_EU_PV && WithinMargin( dPropFlexAdjVal, 0.0, 0.0001 ))
											sResultVal = "--";
										else
											sResultVal = BEMPX_FloatToString( dPropFlexAdjVal, 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                                 //	BEMPX_WriteLogFile( QString( "   in ProcessNonresSimulationResults(), REVISING %1 to %2" ).arg( sPropName, sResultVal ), NULL, FALSE, TRUE, FALSE );
								}	}

							   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
							   // {	sPropName = QString( "%1SrcPrm" ).arg( (!osRunInfo.IsStdRun() ? "Proposed" : "Standard") );
							   // 	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, fVal[4], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
							   // 		fVal[4] = 0;
							   // }
							}
							//int iStartCol = (iEUIdx==IDX_T24_NRES_EU_CompTot ? 2 : 0);
							double dCol1Div = (osRunInfo.CodeType() == CT_T24N ? 10.0 :  1.0);		// SAC 10/28/15 - T24N fuel use therms -> MBtu
							double dCol2Div = (osRunInfo.CodeType() == CT_T24N ?  1.0 : 10.0);		// SAC 10/28/15 - S901G other fuel use therms -> MBtu
						   // int iNumCols = (osRunInfo.CodeType() != CT_T24N ? 3 : (!sSrcEnergyPrmTableName.isEmpty() ? 5 : (sSrcEnergyTableName.length() > 1 ? 4 : 3)));		// SAC 6/28/19 - 2022
							int iNumCols = (osRunInfo.CodeType() != CT_T24N ? 3 : (sSrcEnergyTableName.length() > 1 ? 4 : 3));		// SAC 6/28/19 - 2022
							for (int iCol=0; iCol<iNumCols; iCol++)
							{
								int iEnduseID = (iCol < 3 ? iCol+(osRunInfo.IsStdRun() ? 5 : 2) : (iCol*3)+(osRunInfo.IsStdRun() ? 3 : 2));
								sPropName = QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(iEnduseID) );
								double dValToDisplay = fVal[iCol] /	(iCol==0 ? 1000.0 : (iCol==1 ? dCol1Div : (iCol==2 ? dCol2Div : 1.0))  );  // (iCol==1 ? 1.0 : 1000.0 );  // (iCol==2 ? 1 : 1000);
								//	double dMinValToDisplay = 				(iCol==1 ? 0.5    : 0.05 );
								int iDecPrec;
								if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs ONLY
									//iDecPrec = 		1;		// SAC 10/28/15 - ALL results now #.# since converting fuel use from therms to MBtu - was:  (iCol==1 ? 0      : 1    );
									iDecPrec = 		(iCol>=2 ? 2 : 1 );		// SAC 6/8/16 - T24 TDV results now reported w/ 2 decimal places (tic #1735)
								else
									iDecPrec = 		(iCol==1 ? 0 : 1 );		// SAC 10/28/15 - S901G Other fuel use therms -> MBtu  was: (iCol==0 ? 1 : 0 );
					         // SAC 5/8/14 - revise display of sums to reflect
								BOOL bTrueZero = FALSE;
								if (iEUIdx != IDX_T24_NRES_EU_CompTot && iEUIdx != IDX_T24_NRES_EU_EffTot && iEUIdx != IDX_T24_NRES_EU_Total)
								{	bTrueZero = WithinMargin( dValToDisplay, 0.0, 0.0001 );

                           double dRndVal = RoundVal( dValToDisplay, iDecPrec );
                           dEnduseRndSums[2][iCol] += dRndVal;
                           if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance || (lEngyCodeYearNum >= 2022 && (iEUIdx == IDX_T24_NRES_EU_PV || iEUIdx == IDX_T24_NRES_EU_BT)))
                           {  dEnduseRndSums[1][iCol] += dRndVal;
                              if (esEUMap_CECNonRes[iEUIdx].iSumIntoCompliance)
                                 dEnduseRndSums[0][iCol] += dRndVal;
                           }

   					         // SAC 5/8/14 - switched display to '--' for TRUE zeroes or values for anything else (that may even display as a zero)
   								if (bTrueZero)
   									sResultVal = "--";
   								else
   									sResultVal = BEMPX_FloatToString( dValToDisplay, iDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
   								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                              //	BEMPX_WriteLogFile( QString( "   in ProcessNonresSimulationResults(), setting %1 to %2" ).arg( sPropName, sResultVal ), NULL, FALSE, TRUE, FALSE );
							}  }

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
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
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
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_Flt, (void*) &dEDem, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
	
						   // lastly, populate Compliance Margin column
							// SAC 8/14/19 - removed logic preventing storage of Enduse%1[8] (% compliance margin) for non-compliance enduses (Com tic #3074)
							//if (osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun() && iEUIdx <= IDX_T24_NRES_EU_CompTot)
							if (osRunInfo.CodeType() == CT_T24N && osRunInfo.IsStdRun())
							{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "CompMarginTDV", iCID_EnergyUse )+iResSet, fVal[5], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[5] = 0;
								sPropName = QString( "Enduse%1[8]" ).arg( QString::number(iEUIdx+1) );
								//	if (fVal[5] >= 0.05 || fVal[5] <= -0.05)
	                     //	{	sResultVal = BEMPX_FloatToString( fVal[5], 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
								//		BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								//	}
								//	else
								//		BEMPX_DefaultProperty( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), iError, -1, BEMO_User, osRunInfo.BEMProcIdx() );
					         // SAC 5/8/14 - switched display to '--' for TRUE zeroes or values for anything else (that may even display as a zero)
								if (WithinMargin( fVal[5], 0.0, 0.0049 ))		// SAC 6/8/16 - increase margin around 0 that will display as '--' from 0.0001 to 0.0049
									sResultVal = "--";
	                     else
									sResultVal = BEMPX_FloatToString( fVal[5], 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );		// SAC 6/8/16 - 1 -> 2 decimal places (tic #1735)
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								if (sSrcEnergyTableName.length() > 1)		// SAC 6/28/19 - 2022
								{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "CompMarginSrc", iCID_EnergyUse )+iResSet, fVal[6], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
										fVal[6] = 0;
									sPropName = QString( "Enduse%1[13]" ).arg( QString::number(iEUIdx+1) );
									if (WithinMargin( fVal[6], 0.0, 0.0049 ))		// SAC 6/8/16 - increase margin around 0 that will display as '--' from 0.0001 to 0.0049
										sResultVal = "--";
	         	            else
										sResultVal = BEMPX_FloatToString( fVal[6], 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
							   // if (!sSrcEnergyPrmTableName.isEmpty())		// SAC 6/28/19 - 2022
							   // {	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "CompMarginSrcPrm", iCID_EnergyUse )+iResSet, fVal[7], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
							   // 		fVal[7] = 0;
							   // 	sPropName = QString( "Enduse%1[16]" ).arg( QString::number(iEUIdx+1) );
							   // 	if (WithinMargin( fVal[7], 0.0, 0.0049 ))		// SAC 6/8/16 - increase margin around 0 that will display as '--' from 0.0001 to 0.0049
							   // 		sResultVal = "--";
	         	         //    else
							   // 		sResultVal = BEMPX_FloatToString( fVal[7], 2 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
							   // 	BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							   // }
							}
							else if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && osRunInfo.IsStdRun() && iEUIdx == IDX_T24_NRES_EU_Total)
							{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PropTotalCost", iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[1] = 0;
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "StdTotalCost", iCID_EnergyUse ), fVal[2], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fVal[2] = 0;
								if (fVal[1] < 0.1 || fVal[2] < 0.1)
								{	sResultVal = "--";
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse1[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse2[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
								else
								{	fVal[5] = (int( fVal[2] + 0.5 ) - int( fVal[1] + 0.5 ));
									sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse1[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									sResultVal = BEMPX_FloatToString( fVal[2], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse2[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
									sResultVal = BEMPX_FloatToString( fVal[5], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									sResultVal = "$ " + sResultVal;
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[8]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
							}

							if (osRunInfo.CodeType() == CT_T24N && sCO2EmissionsElecTableName.length() > 1)		// SAC 9/12/19 - CO2 emissions (tonne) (tic #3106)
							{	double fCO2[4] = {0,0,0,0};
								assert( OSF_NumFuels < 5 );
								for (iFl=0; iFl < OSF_NumFuels; iFl++)
								{	sPropName = QString( "%1%2C02" ).arg( sEUPropNameBase, pszaFuelPropName[iFl] );
									if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, fCO2[iFl], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
										fCO2[iFl] = 0;
								}
								fCO2[1] += fCO2[2];   fCO2[2] = 0;	  // sum NatGas & Other fuel together into fCO2[1] and zero out fCO2[2]
								sPropName = QString( "%1TotalC02" ).arg( sEUPropNameBase );
								if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse )+iResSet, fCO2[2], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
									fCO2[2] = 0;
								fCO2[0] *= fCO2EmissionsResultsMult;		fCO2[1] *= fCO2EmissionsResultsMult;		fCO2[2] *= fCO2EmissionsResultsMult;
								for (int iCol=0; iCol<3; iCol++)
								{	if (fCO2[iCol] != 0.0)
									{	int iEnduseID = iCol + (osRunInfo.IsStdRun() ? 20 : 17);
										sPropName = QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(iEnduseID) );
										sResultVal = BEMPX_FloatToString( fCO2[iCol], lCO2EmissionsResultsDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}	}
								if (osRunInfo.IsStdRun())	// Margin column
								{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "MarginC02", iCID_EnergyUse )+iResSet, fCO2[0], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() ))
										fCO2[0] = 0;
									sPropName = QString( "Enduse%1[23]" ).arg( QString::number(iEUIdx+1) );
									sResultVal = BEMPX_FloatToString( fCO2[0], lCO2EmissionsResultsDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								}
							}

						   // special processing for S901G - store energy COSTS in the IDX_T24_NRES_EU_CompTot bucket (Enduse8[2-7])
							if ((osRunInfo.CodeType() == CT_S901G || osRunInfo.CodeType() == CT_ECBC) && iEUIdx == IDX_T24_NRES_EU_Total)
							{	sResultVal = "Energy Costs";
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Enduse8[1]", iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								sPropName = QString( "%1ElecCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 5 : 2) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								sPropName = QString( "%1NatGasCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 6 : 3) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );

								sPropName = QString( "%1OtherCost" ).arg( sEUPropNameBase );
										BEMPX_GetFloat( BEMPX_GetDatabaseID( sPropName, iCID_EnergyUse ), fVal[1], 0, BEMP_Flt, iEUObjIdx, BEMO_User, osRunInfo.BEMProcIdx() );
										if (fVal[1] < 0.01)
											sResultVal = "--";
										else
										{	sResultVal = BEMPX_FloatToString( fVal[1], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );
											sResultVal = "$ " + sResultVal;
										}
										sPropName = QString( "Enduse8[%1]" ).arg( QString::number(osRunInfo.IsStdRun() ? 7 : 4) );
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
							}
						}	// end of  if (iEUObjIdx >= 0)
					}	// end of  while (esEUMap_CECNonRes[++iEUIdx].sEnduseName != NULL)

               // store EUseSummary enduse sums AFTER main enduse loop since sums NOT in enduse def order - SAC 12/12/21
               int iSumEUIdxs[] = { IDX_T24_NRES_EU_EffTot, IDX_T24_NRES_EU_CompTot, IDX_T24_NRES_EU_Total, -1 };
               int iEUIdxIdx = -1;
               while (iSumEUIdxs[++iEUIdxIdx] >= 0)
                  if (iSumEUIdxs[iEUIdxIdx] != IDX_T24_NRES_EU_EffTot || lEngyCodeYearNum >= 2022)
                  {  iEUIdx = iSumEUIdxs[iEUIdxIdx];
               		int iNumCols = (osRunInfo.CodeType() != CT_T24N ? 3 : (sSrcEnergyTableName.length() > 1 ? 4 : 3));		// SAC 6/28/19 - 2022
            			for (int iCol=0; iCol<iNumCols; iCol++)
            			{
            				int iEnduseID = (iCol < 3 ? iCol+(osRunInfo.IsStdRun() ? 5 : 2) : (iCol*3)+(osRunInfo.IsStdRun() ? 3 : 2));
            				sPropName = QString( "Enduse%1[%2]" ).arg( QString::number(iEUIdx+1), QString::number(iEnduseID) );
         					int iDecPrec;
         					if (osRunInfo.CodeType() == CT_T24N)		// for CT_T24N runs ONLY
         						iDecPrec = 		(iCol>=2 ? 2 : 1 );		// SAC 6/8/16 - T24 TDV results now reported w/ 2 decimal places (tic #1735)
         					else
         						iDecPrec = 		(iCol==1 ? 0 : 1 );		// SAC 10/28/15 - S901G Other fuel use therms -> MBtu  was: (iCol==0 ? 1 : 0 );
         					sResultVal = BEMPX_FloatToString( dEnduseRndSums[iEUIdxIdx][iCol], iDecPrec /*nRtOfDec*/, TRUE /*bAddCommas*/ );
         					BEMPX_SetBEMData( BEMPX_GetDatabaseID( sPropName, iCID_EUseSummary ), BEMP_QStr, (void*) &sResultVal, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                  }	}

				   // SAC 2/16/20 - if PV present, then grab total elec array, calculate exports and set that data to EUseSummary:Prop/StdPV_*
					long lDBID_PV_Export = BEMPX_GetDatabaseID( QString( "%1PV_Export" ).arg( sEUPropNameBase ), iCID_EUseSummary );
					if (lDBID_PV_Export > 0)
					{	double dPV_Total = esEUMap_CECNonRes[IDX_T24_NRES_EU_PV].daEnduseTotal[0/*elec*/];
						double dPV_Export=0.0, dPV_PctExport=0.0;
						if (dPV_Total != 0)
						{
						   //	double* pTotElec=NULL;
						   //	if (BEMPX_GetHourlyResultArrayPtr( &pTotElec, NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[0/*elec*/],
			 			   //													esEUMap_CECNonRes[IDX_T24_NRES_EU_Total].sEnduseName, osRunInfo.BEMProcIdx() ) == 0 && pTotElec != NULL)
			 			   //	{	for (int hr=0; hr<8760; hr++)
			 			   //		{	//if (pTotElec[hr] < 0)
			 			   //				dPV_Export += pTotElec[hr];
				 		   //	}	}
						   // IDX_T24_NRES_EU_Total hourly results series is NOT a sum of all enduses, so need to sum them by hour HERE to determine export result
							int hr=0;
							double* daElecEUData[NUM_T24_NRES_EndUses];
							double* daResElecEUData[NUM_T24_NRES_EndUses];  // added RES enduse data to export calc (previously ignored) - SAC 05/24/22
							int iEU;
							for (iEU=0; iEU < NUM_T24_NRES_EndUses; iEU++)
							{	if (iEU == IDX_T24_NRES_EU_CompTot || iEU == IDX_T24_NRES_EU_Total || iEU == IDX_T24_NRES_EU_EffTot)
									daElecEUData[iEU] = NULL;
								else if (BEMPX_GetHourlyResultArrayPtr( &daElecEUData[iEU], NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[0],
			 																esEUMap_CECNonRes[iEU].sEnduseName, osRunInfo.BEMProcIdx() ) == 0 && daElecEUData[iEU] != NULL)
								{	// OK - do nothing
								}
								else
									daElecEUData[iEU] = NULL;   // this combination of meter & enduse does not have results, so assign 8760 of zeroes
                        // same as above, but this time for RES enduse arrays (previously ignored) - SAC 05/24/22
                        if (iEU == IDX_T24_NRES_EU_CompTot || iEU == IDX_T24_NRES_EU_Total || iEU == IDX_T24_NRES_EU_EffTot ||
                            iEU == IDX_T24_NRES_EU_PV || iEU == IDX_T24_NRES_EU_BT)
									daResElecEUData[iEU] = NULL;
								else if (BEMPX_GetHourlyResultArrayPtr( &daResElecEUData[iEU], NULL, 0, osRunInfo.LongRunID().toLocal8Bit().constData(), pszaEPlusFuelNames[0],
			 																esEUMap_CECNonRes[iEU].sResEnduseName, osRunInfo.BEMProcIdx() ) == 0 && daResElecEUData[iEU] != NULL)
								{	// OK - do nothing
								}
								else
									daResElecEUData[iEU] = NULL;   // this combination of meter & enduse does not have results, so assign 8760 of zeroes
							}
							for (hr=0; hr<8760; hr++)
							{	// now sum enduse results by hour to determine export
								double dEUSumThisHr = 0.0;
								for (iEU=0; iEU < NUM_T24_NRES_EndUses; iEU++)
									dEUSumThisHr += ( (daElecEUData[   iEU]==NULL ? 0.0 : daElecEUData[   iEU][hr]) +
                                             (daResElecEUData[iEU]==NULL ? 0.0 : daResElecEUData[iEU][hr]) );
								if (dEUSumThisHr < 0.0)
		 							dPV_Export += dEUSumThisHr;
							}
							dPV_Total  *= -1.0;
							dPV_Export *= -1.0;
							dPV_PctExport = dPV_Export * 100.0 / dPV_Total;			assert( dPV_PctExport >= 0 && dPV_PctExport < 100 );
				 		}
						long lDBID_PV_Total  = BEMPX_GetDatabaseID( QString( "%1PV_Total"     ).arg( sEUPropNameBase ), iCID_EUseSummary );
						long lDBID_PV_PctExp = BEMPX_GetDatabaseID( QString( "%1PV_PctExport" ).arg( sEUPropNameBase ), iCID_EUseSummary );
                                 if (bHrlyDebugLogging)      // DEBUGGING
                                    BEMPX_WriteLogFile( QString( "   storing PV data for model %1 (dbid %2): Tot %3  Exp %4" ).arg( sEUPropNameBase, QString::number( lDBID_PV_Total ), QString::number( dPV_Total ), QString::number( dPV_Export ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

						BEMPX_SetBEMData( lDBID_PV_Total , BEMP_Flt, (void*) &dPV_Total    , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( lDBID_PV_Export, BEMP_Flt, (void*) &dPV_Export   , BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
						BEMPX_SetBEMData( lDBID_PV_PctExp, BEMP_Flt, (void*) &dPV_PctExport, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					}

				   // SAC 9/17/20 - copy DHW SolarThermal SSF results from Proj to EUseSummary (if present) (tic #3215)
					if (osRunInfo.IsStdRun())
					{	long lDBID_Proj_StdDHW_SSF    = BEMPX_GetDatabaseID( "Proj:StdDHW_SSF" );
						long lDBID_EUseSum_StdDHW_SSF = BEMPX_GetDatabaseID( "EUseSummary:StdDHW_SSF" );
						if (lDBID_Proj_StdDHW_SSF > 0 && lDBID_EUseSum_StdDHW_SSF > 0)
						{	double dSSF;
							if (BEMPX_GetFloat( lDBID_Proj_StdDHW_SSF, dSSF, -1, BEMP_Flt, 0, BEMO_User, osRunInfo.BEMProcIdx() ) && dSSF > 0)
								BEMPX_SetBEMData( lDBID_EUseSum_StdDHW_SSF, BEMP_Flt, (void*) &dSSF, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
					}	}
					else
					{	long lDBID_Proj_PropDHWNames_SSF    = BEMPX_GetDatabaseID( "Proj:PropDHWNames_SSF" );
						long lDBID_Proj_PropDHW_SSF         = BEMPX_GetDatabaseID( "Proj:PropDHW_SSF" );
						long lDBID_EUseSum_PropDHWNames_SSF = BEMPX_GetDatabaseID( "EUseSummary:PropDHWNames_SSF" );
						long lDBID_EUseSum_PropDHW_SSF      = BEMPX_GetDatabaseID( "EUseSummary:PropDHW_SSF" );
						bool bNoMoreSSFs=false;		int iSSFIdx=-1;
						while (++iSSFIdx < 10 && !bNoMoreSSFs)
						{	double dSSF;	QString qsSSFname;
							if (BEMPX_GetFloat(  lDBID_Proj_PropDHW_SSF      + iSSFIdx, dSSF,      -1, BEMP_Flt, 0, BEMO_User, osRunInfo.BEMProcIdx() ) && dSSF > 0 &&
								 BEMPX_GetString( lDBID_Proj_PropDHWNames_SSF + iSSFIdx, qsSSFname, FALSE, 0, -1, 0, BEMO_User, NULL, 0, osRunInfo.BEMProcIdx() ))
							{	BEMPX_SetBEMData( lDBID_EUseSum_PropDHW_SSF      + iSSFIdx, BEMP_Flt,  (void*) &dSSF,      BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
								BEMPX_SetBEMData( lDBID_EUseSum_PropDHWNames_SSF + iSSFIdx, BEMP_QStr, (void*) &qsSSFname, BEMO_User, iResSet, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
                           //	BEMPX_WriteLogFile( QString( "   in ProcessNonresSimulationResults(), just set prop model SSF to %1 for DHWSolarSys '%2' to EUseSummary" ).arg( QString::number( dSSF ), qsSSFname ), NULL, FALSE, TRUE, FALSE );
							}
							else
								bNoMoreSSFs = true;
					}	}

				}
			}	// end of  if (iCID_EUseSummary > 0 && fTotBldgFlrArea > 0)

			}	// end of:  for (int iResSet=0; iResSet < lNumResultsSets; iResSet++) - loop over multiple results sets - SAC 11/3/19
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
			long lDBID_ThrmlZn_ClgUMLHLimit  = BEMPX_GetDatabaseID( "ClgUMLHLimit",   osRunInfo.ClassID( ROT_Zone ) );		// SAC 7/28/20
			long lDBID_ThrmlZn_HtgUMLHLimit  = BEMPX_GetDatabaseID( "HtgUMLHLimit",   osRunInfo.ClassID( ROT_Zone ) );
			long lDBID_ThrmlZn_BypassClgUMLHLimit = BEMPX_GetDatabaseID( "BypassClgUMLHLimit", osRunInfo.ClassID( ROT_Zone ) );
			long lDBID_ThrmlZn_BypassHtgUMLHLimit = BEMPX_GetDatabaseID( "BypassHtgUMLHLimit", osRunInfo.ClassID( ROT_Zone ) );
			long lDBID_Proj_MaxClgUnmetLdHrs = BEMPX_GetDatabaseID( "Proj:MaxClgUnmetLdHrs" );
			long lDBID_Proj_MaxHtgUnmetLdHrs = BEMPX_GetDatabaseID( "Proj:MaxHtgUnmetLdHrs" );
									if (bVerbose)
										BEMPX_WriteLogFile( "  PerfSim_E+ - Pulling UMLH & sizing results from OSWrap", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			bool bTrackUMLHExceeded = (osRunInfo.StoreHourlyResults() && osRunInfo.CodeType() == CT_T24N && !osRunInfo.IsStdRun());		// SAC 7/28/20
			if (osRunInfo.NumObjects( ROT_Zone ) > 0 && lDBID_ThrmlZn_ClgUnmetLdHrs > 0 && lDBID_ThrmlZn_HtgUnmetLdHrs > 0 &&
					lDBID_ThrmlZn_ClgDsgnLd > 0 && lDBID_ThrmlZn_HtgDsgnLd > 0 && lDBID_ThrmlZn_ClgDsgnFlow > 0 && lDBID_ThrmlZn_HtgDsgnFlow > 0 )
			{	//double fZnUnmetLdClg, fZnUnmetLdHtg;
				double faZnResults[6] = {0,0,0,0,0,0};
		      // SAC 1/11/14 - units -> IP  (2 already in IP, the other needing conversion from SI)
		      //	double faZnResMult[6] = {1, 1 /*hr*/,	3.412142F, 3.412142F, /*W->Btuh*/		2119, 2119 /*m3/s->cfm*/ };
				double faZnResMult[6] = {1, 1 /*hr*/,	1, 1, /*Btuh*/		1, 1 /*cfm*/ };
				long laDBID[6] = { lDBID_ThrmlZn_ClgUnmetLdHrs, lDBID_ThrmlZn_HtgUnmetLdHrs, lDBID_ThrmlZn_ClgDsgnLd, lDBID_ThrmlZn_HtgDsgnLd, lDBID_ThrmlZn_ClgDsgnFlow, lDBID_ThrmlZn_HtgDsgnFlow };
				assert( osRunInfo.NumResultObjects( ROT_Zone ) == osRunInfo.NumObjects( ROT_Zone ) );	// otherwise, one or more zones missing from UMLH results
				bool bMaxUMLHLenMet = false;
				int iNumZonesExceedClgUMLHs = 0, iNumZonesExceedHtgUMLHs = 0;		// SAC 7/28/20
				long lConstantClgUMLHLimit = -1, lConstantHtgUMLHLimit = -1;
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

					if (bTrackUMLHExceeded && (faZnResults[0] > 0 || faZnResults[1] > 0))		// SAC 7/28/20
					{	double fMaxUnmetClgLdHrs, fMaxUnmetHtgLdHrs;
						if (lDBID_ThrmlZn_ClgUMLHLimit < 1 || !BEMPX_GetFloat( lDBID_ThrmlZn_ClgUMLHLimit, fMaxUnmetClgLdHrs, 0, -1, iZn, BEMO_User, osRunInfo.BEMProcIdx() ))
						{	if (lDBID_Proj_MaxClgUnmetLdHrs < 1 || !BEMPX_GetFloat( lDBID_Proj_MaxClgUnmetLdHrs, fMaxUnmetClgLdHrs, 0, -1, 0, BEMO_User, osRunInfo.BEMProcIdx() ))
								fMaxUnmetClgLdHrs = -1;
						}
						if (lDBID_ThrmlZn_HtgUMLHLimit < 1 || !BEMPX_GetFloat( lDBID_ThrmlZn_HtgUMLHLimit, fMaxUnmetHtgLdHrs, 0, -1, iZn, BEMO_User, osRunInfo.BEMProcIdx() ))
						{	if (lDBID_Proj_MaxHtgUnmetLdHrs < 1 || !BEMPX_GetFloat( lDBID_Proj_MaxHtgUnmetLdHrs, fMaxUnmetHtgLdHrs, 0, -1, 0, BEMO_User, osRunInfo.BEMProcIdx() ))
								fMaxUnmetHtgLdHrs = -1;
						}
						long lBypassClgUMLHLimit=0, lBypassHtgUMLHLimit=0;		// SAC 5/12/19 (tic #2680)
						if (lDBID_ThrmlZn_BypassClgUMLHLimit < 1 || !BEMPX_GetInteger( lDBID_ThrmlZn_BypassClgUMLHLimit, lBypassClgUMLHLimit, 0, -1, iZn, BEMO_User, osRunInfo.BEMProcIdx() ))
							lBypassClgUMLHLimit = 0;
						if (lDBID_ThrmlZn_BypassHtgUMLHLimit < 1 || !BEMPX_GetInteger( lDBID_ThrmlZn_BypassHtgUMLHLimit, lBypassHtgUMLHLimit, 0, -1, iZn, BEMO_User, osRunInfo.BEMProcIdx() ))
							lBypassHtgUMLHLimit = 0;

						if (fMaxUnmetClgLdHrs > -0.5 && lBypassClgUMLHLimit == 0 && faZnResults[0] > (fMaxUnmetClgLdHrs + 0.1))
						{	iNumZonesExceedClgUMLHs++;
							if (lConstantClgUMLHLimit == -1)
								lConstantClgUMLHLimit = (long) (faZnResults[0] + 0.1);
							else if (lConstantClgUMLHLimit > 0 && lConstantClgUMLHLimit != (long) (faZnResults[0] + 0.1))
								lConstantClgUMLHLimit = -2;  // => no constant UMLH limit
						}
						if (fMaxUnmetHtgLdHrs > -0.5 && lBypassClgUMLHLimit == 0 && faZnResults[1] > (fMaxUnmetHtgLdHrs + 0.1))
						{	iNumZonesExceedHtgUMLHs++;
							if (lConstantHtgUMLHLimit == -1) 
								lConstantHtgUMLHLimit = (long) (faZnResults[1] + 0.1);
							else if (lConstantHtgUMLHLimit > 0 && lConstantHtgUMLHLimit != (long) (faZnResults[1] + 0.1))
								lConstantHtgUMLHLimit = -2;  // => no constant UMLH limit
					}	}

					if (!bMaxUMLHLenMet)		// SAC 12/17/13 - prevent ZoneUMLH string from exceeding TextIO string length max - which in turn causes errors on File-Open
					{	if (!sZoneUMLHSummary.isEmpty())	// SAC 5/31/14 - revised newline writing to prevent trailing \r\n @ end of string
							sZoneUMLHSummary += "\r\n";
						if ((sZoneUMLHSummary.length() + 120) < TextioMaxLine)	// SAC 5/31/14 - increased 100->120 as max TextIO string len still being exceeded
						//if ((sZoneUMLHSummary.length() + 120) < TextioMaxLine || bReportAllUMLHZones)	// SAC 5/31/14 - increased 100->120 as max TextIO string len still being exceeded   // SAC 11/11/19
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
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHsLoaded + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_Int,          &l1,               BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
	#ifdef _DEBUG
	//	QString sDbgMsg;	sDbgMsg = QString( "Posting UMLHs data to BEMBase:\n%1" ).arg( sZoneUMLHSummary );	::MessageBox( NULL, sDbgMsg, NULL, MB_ICONEXCLAMATION );
	#endif
					BEMPX_SetBEMData( lDBID_EUseSummary_ZoneUMLHs       + (osRunInfo.IsStdRun() ? 1 : 0), BEMP_QStr, (void*) &sZoneUMLHSummary, BEMO_User, 0, BEMS_SimResult, BEMO_User, TRUE /*bPerfResets*/, osRunInfo.BEMProcIdx() );
				}

				if (bTrackUMLHExceeded && (iNumZonesExceedClgUMLHs > 0 || iNumZonesExceedHtgUMLHs > 0))		// SAC 7/28/20
				{
					QString sClgHoursStr = "hours", sHtgHoursStr = "hours";	
					if (lConstantClgUMLHLimit > 0)
						sClgHoursStr = QString::asprintf( "hours of %d", lConstantClgUMLHLimit );
					if (lConstantHtgUMLHLimit > 0)
						sHtgHoursStr = QString::asprintf( "hours of %d", lConstantHtgUMLHLimit );

					QString cstrUMLHWarningMsg;
					if (iNumZonesExceedClgUMLHs > 0 && iNumZonesExceedHtgUMLHs > 0)
						cstrUMLHWarningMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s and %d zone(s) exceed maximum heating unmet load %s.",
    																iNumZonesExceedClgUMLHs, osRunInfo.LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs, sHtgHoursStr.toLocal8Bit().constData() );
					else if (iNumZonesExceedClgUMLHs > 0)
						cstrUMLHWarningMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s.",
    																iNumZonesExceedClgUMLHs, osRunInfo.LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData() );
					else  // if (iNumZonesExceedHtgUMLHs > 0)
						cstrUMLHWarningMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum heating unmet load %s.",
    																iNumZonesExceedHtgUMLHs, osRunInfo.LongRunID().toLocal8Bit().constData(), sHtgHoursStr.toLocal8Bit().constData() );
					cstrUMLHWarningMsg += "\r\n\r\nAll thermal zones exceeding unmet load hour limits will be reported on PRF-1, which will be watermarked 'not for compliance'.";

					// store warning message for display in UI results dialog - SAC 7/28/20
					long lDBID_ZoneUMLHsMsg			= BEMPX_GetDatabaseID( "EUseSummary:ZoneUMLHsMsg" );
					long lDBID_HaveZoneUMLHsMsg	= BEMPX_GetDatabaseID( "EUseSummary:HaveZoneUMLHsMsg" );
					long lDBID_ZoneUMLHsLink		= BEMPX_GetDatabaseID( "EUseSummary:ZoneUMLHsLink" );
					if (lDBID_ZoneUMLHsMsg > 0 && lDBID_HaveZoneUMLHsMsg > 0)
					{	long lHaveErrMsg = 1;
						BEMPX_SetBEMData( lDBID_HaveZoneUMLHsMsg, BEMP_Int , &lHaveErrMsg, BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, osRunInfo.BEMProcIdx() );
						QString sUMLHErrMsg = cstrUMLHWarningMsg;
						BEMPX_SetBEMData( lDBID_ZoneUMLHsMsg    , BEMP_QStr, &sUMLHErrMsg, BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, osRunInfo.BEMProcIdx() );
					}
					QString sUMLHFAQLink;
					if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:UnmetLdHrsFAQLink" ), sUMLHFAQLink ))
						sUMLHFAQLink.clear();
					if (!sUMLHFAQLink.isEmpty())
					{	if (lDBID_ZoneUMLHsLink > 0)		// SAC 7/28/20
							BEMPX_SetBEMData( lDBID_ZoneUMLHsLink, BEMP_QStr, &sUMLHFAQLink, BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, osRunInfo.BEMProcIdx() );
				}	}
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

	// moved ReadVarsESO / SimOutVarsToCSV.rvi processing from here into RetrieveSimulationResults()

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
			unsigned uiLastDot = (int) sSDDFileRoot.rfind('.');
			if (uiLastDot != std::string::npos)
				sSDDFileRoot = sSDDFileRoot.substr( 0, uiLastDot );
			// data defining which files get copied where      - for iSimulationStorage =  1  2  3  4  5  6  7
			FileCopyInfo fcInfo[] = {//{	"in.idf",         ".idf",            1, true,  { 1, 1, 1, 1, 1, 1, 1 } },	-- IDF file now written to std processing directory - just leave alone for now
												{	"eplustbl.htm",   ".htm",            0, true,  { 0, 1, 1, 1, 1, 1, 1 } },
												{	"eplusssz.csv",   " - ssz.csv",      0, false, { 0, 0, 1, 1, 1, 1, 1 } },	// SAC 1/24/19 - switched bReportFailure from true to false
												{	"epluszsz.csv",   " - zsz.csv",      0, false, { 0, 0, 1, 1, 1, 1, 1 } },	// SAC 1/24/19 - switched bReportFailure from true to false
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
												{	"in.idf",         "",                0, false, { 0, 0, 0, 0, 0, 0, 0 } },  // no copy, just include to ensure writable  - SAC 2/18/19
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
					{	if (fcInfo[iFC].bReportFailure && bRptMissingEPFiles)
							sFailMsg = boost::str( boost::format( "    during simulation file clean-up, file not found:  %s" ) % sCopyFr.c_str() );
					}
					else	// file exists
					{	if (!CopyFile( sCopyFr.c_str(), sCopyTo.c_str(), FALSE ))
						{	if (fcInfo[iFC].bReportFailure && bRptMissingEPFiles)
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
			if (psaEPlusProcDirsToBeRemoved)		// SAC 5/22/19 - added to postpone E+ directory cleanup until end of analysis to avoid deletion errors
				psaEPlusProcDirsToBeRemoved->push_back( QString(sEPlusDirToDel.c_str()) );
			else
			{	try
				{	uiNumDeleted = boost::filesystem::remove_all( sEPlusDirToDel.c_str() );
				}
				catch (const boost::filesystem::filesystem_error& ex)
				{	sFailMsg = boost::str( boost::format( "    during simulation file clean-up, unable to remove directory:  %s  - %s" ) % sEPlusDirToDel.c_str() % ex.what() );
					BEMPX_WriteLogFile( sFailMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}	}
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
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
                                             QVector<QString>* psaCopyAcrossModelClassPrefixes /*=NULL*/ )      // SAC 11/24/20
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
								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
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
														(bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, osRunInfo.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo.m_qaData, iProgressModel,		// SAC 1/25/14		// SAC 11/6/14
									// RUN #2 data
														osRunInfo2.SDDFile().toLocal8Bit().constData(), osRunInfo2.RunID().toLocal8Bit().constData(),
														osRunInfo.WthrPathFile().toLocal8Bit().constData(), (double*) &adResults2[0],
														osRunInfo2.SimulateModel(), (osRunInfo.StoreHourlyResults() != FALSE), pszSQLOutPathFile2, iMaxLenSQLOutPathFile2,
														(bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, osRunInfo2.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo2.m_qaData,	iProgressModel2,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType );
	else
		lSimRetVal = osWrap.SimulateSDD( pszEPlusPath, pszSimProcessDir, osRunInfo.SDDFile().toLocal8Bit().constData(), osRunInfo.RunID().toLocal8Bit().constData(),
														osRunInfo.WthrPathFile().toLocal8Bit().constData(), (double*) &adResults[0],
														osRunInfo.SimulateModel(), (osRunInfo.StoreHourlyResults() != FALSE), pszSQLOutPathFile, iMaxLenSQLOutPathFile,
														(bVerbose != FALSE) /*bWriteHourlyDebugCSV*/, osRunInfo.IDFToSimulate().toLocal8Bit().constData(), &osRunInfo.m_qaData, iProgressModel,  // SAC 1/25/14
														NULL, NULL, NULL, NULL, true, true, NULL, 0, false, NULL, NULL, 0,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType );

								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
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

	//ProcessSimulationResults( osWrap, osRunInfo, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/17/14 - moved ALL results processing to subordinate routine
	RetrieveSimulationResults( osWrap, osRunInfo, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );		// SAC 7/23/18 - replaced w/ subset routine that performs only hourly results retrieval

	if (bHaveSecondRun)
	{	int iResCopyRetVal = 0;
		if (osRunInfo.StoreHourlyResults() && osRunInfo2.StoreHourlyResults() && iRetVal == 0)
		{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
			QString sResCopyErrMsg;
			iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, osRunInfo2.RunID().toLocal8Bit().constData(), osRunInfo.BEMProcIdx(), osRunInfo2.BEMProcIdx(), psaCopyAcrossModelClassPrefixes );
			assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
			if (iResCopyRetVal > 0)
			{	if (sErrMsg.isEmpty())
					sErrMsg = sResCopyErrMsg;
				iRetVal = iResCopyRetVal;
			}
		}
      if (iResCopyRetVal == 0)
			//ProcessSimulationResults( osWrap, osRunInfo2, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/18/14
			RetrieveSimulationResults( osWrap, osRunInfo2, iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );		// SAC 7/23/18 - replaced w/ subset routine that performs only hourly results retrieval
	}

								if (bVerbose && iRetVal != OSI_SimEPlus_UserAbortedAnalysis)
									BEMPX_WriteLogFile( "  PerfSim_E+ - returning", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	
	return iRetVal;
}


// SAC 8/18/15
int CMX_PerformSimulation_EnergyPlus_Multiple(	QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															const char* pszModelkitPath, OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose /*=FALSE*/, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL /*bDurationStats=FALSE*/, double* pdTranslationTime /*=NULL*/, double* pdSimulationTime /*=NULL*/,  // SAC 1/23/14
															int iSimulationStorage /*=-1*/, double* dEPlusVer /*=NULL*/, char* pszEPlusVerStr /*=NULL*/, int iEPlusVerStrLen /*=0*/,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr /*=NULL*/, int iOpenStudioVerStrLen /*=0*/, int iCodeType /*=CT_T24N*/,
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
                                             QVector<QString>* psaCopyAcrossModelClassPrefixes /*=NULL*/ )     // SAC 11/24/20
{
	OSWrapLib osWrap;
	COSRunInfo osRunInfo[MultEPlusSim_MaxSims];
	int iSimRetVal = PerformSimulation_EnergyPlus_Multiple( osWrap, &osRunInfo[0], sErrMsg, pszEPlusPath, NULL /*pszWthrPath*/, pszSimProcessDir,
															pszModelkitPath, pSimInfo, iNumSimInfo, bVerbose, FALSE /*bDurationStats*/, pdTranslationTime, pdSimulationTime,
															iSimulationStorage, dEPlusVer, pszEPlusVerStr, iEPlusVerStrLen, pszOpenStudioVerStr,
															iOpenStudioVerStrLen, iCodeType, bIncludeOutputDiagnostics, iProgressType );
	if (iSimRetVal == 0)
		iSimRetVal = ProcessSimulationResults_Multiple(	osWrap, &osRunInfo[0], sErrMsg, pszEPlusPath, NULL /*pszWthrPath*/, pszSimProcessDir,
															pSimInfo, iNumSimInfo, bVerbose, FALSE /*bDurationStats*/, pdTranslationTime, pdSimulationTime,
															iSimulationStorage, dEPlusVer, pszEPlusVerStr, iEPlusVerStrLen, pszOpenStudioVerStr,
															iOpenStudioVerStrLen, iCodeType, bIncludeOutputDiagnostics, iProgressType, NULL, false, NULL, psaCopyAcrossModelClassPrefixes );
	return iSimRetVal;
}

int PerformSimulation_EnergyPlus_Multiple(	OSWrapLib& osWrap, COSRunInfo* osRunInfo,
															QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															const char* pszModelkitPath, OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose /*=FALSE*/, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL /*bDurationStats=FALSE*/, double* pdTranslationTime /*=NULL*/, double* pdSimulationTime /*=NULL*/,  // SAC 1/23/14
															int iSimulationStorage /*=-1*/, double* dEPlusVer /*=NULL*/, char* pszEPlusVerStr /*=NULL*/, int iEPlusVerStrLen /*=0*/,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr /*=NULL*/, int iOpenStudioVerStrLen /*=0*/, int iCodeType /*=CT_T24N*/,
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/, bool bUseEPlusRunMgr /*=false*/, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
                                             bool bInitRunInfoOnly /*=false*/ )     // SAC 10/29/21 (MFam)
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
// SAC 7/23/18 - moved into function arguments
//	OSWrapLib osWrap;
//	COSRunInfo osRunInfo[MultEPlusSim_MaxSims];
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
										pSimInfo[iRun]->bSimulateModel, pSimInfo[iRun]->iBEMProcIdx, pSimInfo[iRun]->pszIDFToSimulate, iCodeType, pSimInfo[iRun]->bSimOutVarsCSV,
                              false /*bEvalReportRulesFollowingSim*/, bInitRunInfoOnly /*bSkippingEPlusSim*/ );      // SAC 12/08/21
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

         long lProj_Meter=0;        // SAC 10/04/21
         BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:Meter" ), lProj_Meter, 0, -1, 0, BEMO_User, pSimInfo[iRun]->iBEMProcIdx );
			oswSimInfo[iRun].bWriteCustomMetersHourlyCSV = (lProj_Meter > 0);

			oswSimInfo[iRun].lRptFuelUseAs			= osRunInfo[iRun].RptFuelUseAs();		// SAC 10/28/15
			oswSimInfo[iRun].lRunPeriodYear			= osRunInfo[iRun].RunPeriodYear();		// SAC 3/1/19
			oswSimInfo[iRun].pQuickAnalysisInfo		= &osRunInfo[iRun].m_qaData;
			oswSimInfo[iRun].iProgressModel			= pSimInfo[iRun]->iProgressModel;
			oswSimInfo[iRun].iSimReturnValue			= 0;
	}	}

	char pszSimSDDErrorMsg[1024];		pszSimSDDErrorMsg[0] = '\0';
   long lSimRetVal = 0;
   if (!bInitRunInfoOnly)     // SAC 10/29/21 (MFam)
	{
   							if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( "  PerfSim_E+ - About to simulate SDD", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
// --------------------
// SIMULATE SDD MODELS
// --------------------
	   lSimRetVal = osWrap.SimulateSDD_Multiple( pszEPlusPath, pszSimProcessDir, poswSimInfo, iNumSimInfo,
														(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pdTranslationTime, pdSimulationTime,  // SAC 1/23/14		// SAC 5/27/15
																							// OSWRAP_MSGCALLBACK OSWrapCallback( int level, const char* msg, int action )
														pszSimSDDErrorMsg, 1024, bIncludeOutputDiagnostics, iCodeType, !bUseEPlusRunMgr );
								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
								{	sLogMsg = QString( "  PerfSim_E+ - Back from SDD simulation (returned %1)" ).arg( QString::number(lSimRetVal) );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}

//		// Info related to models needing to be simulated
//		sLogMsg = QString( "  SimulateSDD_Multiple() - pszEPlusPath:  %1"     ).arg( pszEPlusPath );				BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//		sLogMsg = QString( "  SimulateSDD_Multiple() - pszSimProcessDir:  %1" ).arg( pszSimProcessDir );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//		sLogMsg = QString( "  SimulateSDD_Multiple() - %1 sim infos:" ).arg( QString::number(iNumSimInfo) );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//		for (int iSI=0; iSI < iNumSimInfo; iSI++)
//		{	sLogMsg = QString( "                            %1: SDDXMLFile:  %2%3" ).arg( QString::number(iSI+1), pszSimProcessDir, oswSimInfo[iSI].pszSDDXMLFileName );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//			sLogMsg = QString( "                               pszRunSubdir:  %1" ).arg( oswSimInfo[iSI].pszRunSubdir );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//			sLogMsg = QString( "                               SimulateModel: %1" ).arg( QString::number(oswSimInfo[iSI].bSimulateModel ? 1 : 0) );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
////			sLogMsg = QString( "                               iRunIdx:  %1  / SimulateModel: %2" ).arg( QString::number(oswSimInfo[iSI].iRunIdx), QString::number(oswSimInfo[iSI].bSimulateModel ? 1 : 0) );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//			sLogMsg = QString( "                               pszWeatherPathFile:  %1" ).arg( oswSimInfo[iSI].pszWeatherPathFile );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//			sLogMsg = QString( "                               pszSQLOutPathFile:  %1" ).arg( oswSimInfo[iSI].pszSQLOutPathFile );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//			if (oswSimInfo[iSI].pQuickAnalysisInfo && oswSimInfo[iSI].pQuickAnalysisInfo->m_iNumQuickAnalysisPeriods > 0)
//			{
//				sLogMsg = QString( "                                  NumQuickAnalysisPeriods:  %1" ).arg( QString::number(oswSimInfo[iSI].pQuickAnalysisInfo->m_iNumQuickAnalysisPeriods) );		BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, TRUE, FALSE );
//		}	}
////BEMMessageBox( "Sim Info posted to log file" );


	double dEPlusVerNum=-1;
	if (bUseEPlusRunMgr && lSimRetVal == 0)
	{
		boost::posix_time::ptime	tmStartTime = boost::posix_time::microsec_clock::local_time();  // SAC 1/23/14

		EPlusRunMgr epRunMgr( pszEPlusPath, pszSimProcessDir, iCodeType, iProgressType, bVerbose /*bVerbose*/, true /*bSilent*/ );
		int iRunIdx = 0, iNumRuns=0;		QString sSetupRunErrMsg, sFirstRunSubdir;
		for (int iSI=0; (lSimRetVal == 0 && iSI < iNumSimInfo); iSI++)
		{	if (oswSimInfo[iSI].pszRunSubdir && oswSimInfo[iSI].pszWeatherPathFile && oswSimInfo[iSI].bSimulateModel)
			{	QString qsIDFPathFile;
				if (oswSimInfo[iSI].pszIDFToSimulate && strlen( oswSimInfo[iSI].pszIDFToSimulate ) > 0)
				{	if (FileExists( oswSimInfo[iSI].pszIDFToSimulate ))
						qsIDFPathFile = oswSimInfo[iSI].pszIDFToSimulate;
					else
						lSimRetVal = 49;		// IDF path/filename specified by Proj:UseExcptDsgnModel not found
			//			const char* pszIDFToSim = paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->pszIDFToSimulate;
			//		// deal w/ PRE-DEFINED IDF files
			//			if (pszIDFToSim && strlen( pszIDFToSim ) > 0 && boost::filesystem::exists(openstudio::toPath(pszIDFToSim)))
			//			{	int iCITLastDot = sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].rfind('.');
			//				if (iCITLastDot > 0)
			//				{	std::string sCopyIDFTo = sProcessingPath + sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].substr( 0, iCITLastDot );
			//					sCopyIDFTo += "-fxd.idf";
			//					if (boost::filesystem::exists( sCopyIDFTo ))
			//						boost::filesystem::remove(  sCopyIDFTo );
			//					boost::filesystem::copy_file( pszIDFToSim, sCopyIDFTo );
			//					if (boost::filesystem::exists( sCopyIDFTo ))
			//					{	//bSimulatePredefinedIDF[0] = true;
			//						idfPath[iESimIdx] = openstudio::toPath( sCopyIDFTo );
			//			}	}	}
				}
				else
				{	qsIDFPathFile = QString( "%1%2" ).arg( pszSimProcessDir, oswSimInfo[iSI].pszSDDXMLFileName );
					qsIDFPathFile = qsIDFPathFile.left( qsIDFPathFile.length()-3 );
					qsIDFPathFile += "idf";
				}

			// Evaluate rules that serve to modify IDF file being simulated - SAC 04/23/21
				if (lSimRetVal == 0 && FileExists( qsIDFPathFile ))
				{	QString qsModIDFRulelistName;
					if (iCodeType == CT_T24N)
					{	switch (oswSimInfo[iSI].iProgressModel)
						{	case BCM_NRP_Model_zb	:	qsModIDFRulelistName = "zb";  break;
							case BCM_NRP_Model_ab	:	qsModIDFRulelistName = "ab";  break;
							case BCM_NRP_Model_zp	:	qsModIDFRulelistName = "zp";  break;
							case BCM_NRP_Model_ap	:	qsModIDFRulelistName = "ap";  break;
					}	}
					else
					{	switch (oswSimInfo[iSI].iProgressModel)
						{	case BCM_NRAP_Model_zp	:	qsModIDFRulelistName = "zp";  break;
							case BCM_NRAP_Model_ap	:	qsModIDFRulelistName = "ap";  break;
							case BCM_NRAP_Model_zb1	:	qsModIDFRulelistName = "zb1";  break;
							case BCM_NRAP_Model_zb2	:	qsModIDFRulelistName = "zb2";  break;
							case BCM_NRAP_Model_zb3	:	qsModIDFRulelistName = "zb3";  break;
							case BCM_NRAP_Model_zb4	:	qsModIDFRulelistName = "zb4";  break;
							case BCM_NRAP_Model_ab1	:	qsModIDFRulelistName = "ab1";  break;
							case BCM_NRAP_Model_ab2	:	qsModIDFRulelistName = "ab2";  break;
							case BCM_NRAP_Model_ab3	:	qsModIDFRulelistName = "ab3";  break;
							case BCM_NRAP_Model_ab4	:	qsModIDFRulelistName = "ab4";  break;
					}	}
               qsModIDFRulelistName += "_EnergyPlus_PreSim";
               if (BEMPX_RulelistExists( qsModIDFRulelistName.toLocal8Bit().constData() ))
               {  QString qsOpenSimInputExportFileErr;
                  int iSimInputExpFileIdx = BEMPX_OpenSimInputExportFile( qsIDFPathFile.toLocal8Bit().constData(), qsOpenSimInputExportFileErr ); 
                  if (iSimInputExpFileIdx < 0)
                  {	lSimRetVal = 82;		// Error evaluating PreSim (sim input editing) rules
   						if (!qsOpenSimInputExportFileErr.isEmpty())
	   						BEMPX_WriteLogFile( qsOpenSimInputExportFileErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  }
                  else
                  {	int iSaveActiveBEMProcIdx = BEMPX_GetActiveModel();      // SAC 04/27/21
				         BEMPX_SetActiveModel( osRunInfo[iSI].BEMProcIdx() );

                     if (!BEMPX_EvaluateRuleList( qsModIDFRulelistName.toLocal8Bit().constData(), FALSE /*bTagDataAsUserDefined*/, 
																		0 /*iEvalOnlyClass*/, -1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/, bVerbose ))
									//bool BEMPX_EvaluateRuleList( LPCSTR listName, BOOL bTagDataAsUserDefined=FALSE, int iEvalOnlyClass=0,	int iEvalOnlyObjIdx=-1,
									//				int iEvalOnlyObjType=0, BOOL bVerboseOutput=FALSE, void* pvTargetedDebugInfo=NULL, long* plNumRuleEvals=NULL,
									//				double* pdNumSeconds=NULL, PLogMsgCallbackFunc pLogMsgCallbackFunc=NULL, QStringList* psaWarningMsgs=NULL );		
							{	lSimRetVal = 82;		// Error evaluating PreSim (sim input editing) rules
                        sErrMsg = QString( "Error evaluating PreSim rulelist '%1'" ).arg( qsModIDFRulelistName );
							}
                     BEMPX_CloseSimInputExportFile( iSimInputExpFileIdx );

				         if (BEMPX_GetActiveModel() != iSaveActiveBEMProcIdx)  // SAC 04/27/21
					         BEMPX_SetActiveModel( iSaveActiveBEMProcIdx );
                  }
            }  }

            // Modelkit processing:  ID = 1 => HybridCooling  - SAC 06/22/22
            long lModelkitProcessingID = 0;
				if (lSimRetVal == 0 && FileExists( qsIDFPathFile ) &&
                BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ModelkitProcessingID" ), lModelkitProcessingID, 0, -1, 0, BEMO_User, osRunInfo[iSI].BEMProcIdx() ) &&
                lModelkitProcessingID > 0)
            {
                        //bVerbose = TRUE;
               QString sModelkitPath = pszModelkitPath;
               QString sModelkitBatPathFile        = sModelkitPath + QString("modelkit-catalyst\\bin\\modelkit.bat");
               QString sModelkitRubyScriptPathFile = sModelkitPath + QString("hybrid-hvac.rb");
               QString sModelkitProcpath  = pszSimProcessDir;
               QString sMkIDFPathFile     = QString( "%1%2" ).arg( sModelkitProcpath, oswSimInfo[iSI].pszSDDXMLFileName );
					sMkIDFPathFile = qsIDFPathFile.left( qsIDFPathFile.length()-4 );
               QString sMkIDFFilenameNoExt   = sMkIDFPathFile.right( sMkIDFPathFile.length() - sModelkitProcpath.length() );
               QString sMkSupportCSVPathFile = sMkIDFPathFile + QString( " - HybridHVAC.csv" );
					sMkIDFPathFile += ".idf";

                        //BEMPX_WriteLogFile( QString( "calling CMX_ExecuteModelkitBat:\n   sModelkitBatPathFile = %1\n   sModelkitRubyScriptPathFile = %2\n   sModelkitProcpath = %3\n   sMkIDFFilenameNoExt = %4\n   " ).arg(
                        //            sModelkitBatPathFile, sModelkitRubyScriptPathFile, sModelkitProcpath, sMkIDFFilenameNoExt ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

               lSimRetVal = 91;   // Modelkit processing called for but Modelkit not found
               if (!DirectoryExists( sModelkitPath ))
                  sErrMsg = QString( "Error: Modelkit processing called for but Modelkit path not found:  %1" ).arg( sModelkitPath );
               else if (!FileExists( sModelkitBatPathFile ))
                  sErrMsg = QString( "Error: Modelkit processing called for but Modelkit .bat file not found:  %1" ).arg( sModelkitBatPathFile );
               else if (!FileExists( sModelkitRubyScriptPathFile ))
                  sErrMsg = QString( "Error: Modelkit processing called for but Modelkit ruby script not found:  %1" ).arg( sModelkitRubyScriptPathFile );
               else if (qsIDFPathFile.compare( sMkIDFPathFile, Qt::CaseInsensitive ))
                  sErrMsg = QString( "Error: Modelkit processing IDF path/filename inconsistency:  '%1' vs. '%2'" ).arg( sMkIDFPathFile, qsIDFPathFile );
               else if (!FileExists( sMkSupportCSVPathFile ))
                  sErrMsg = QString( "Error: Modelkit processing called for but model HybridHVAC.csv file not found:  %1" ).arg( sMkSupportCSVPathFile );
               else
               {  lSimRetVal = 0;  // restore non-error state

                  QString sMkInitIDFPathFile = sMkSupportCSVPathFile.left( sMkSupportCSVPathFile.length()-4 ) + QString("-initial.idf");
                  if (FileExists( sMkInitIDFPathFile ))
                     DeleteFile( sMkInitIDFPathFile.toLocal8Bit().constData() );    // CMX_ExecuteModelkitBat will fail if ...initial.idf already exists

                  char pszModelkitBatRetString[1024] = "\0";
                  int iModelkitBatRetVal = CMX_ExecuteModelkitBat( sModelkitBatPathFile.toLocal8Bit().constData(), sModelkitRubyScriptPathFile.toLocal8Bit().constData(), 
                                                sModelkitProcpath.toLocal8Bit().constData(), sMkIDFFilenameNoExt.toLocal8Bit().constData(), bVerbose /*bVerboseOutput*/,
                                                pszModelkitBatRetString, 1023 );
                  if (iModelkitBatRetVal > 0)
                  {  lSimRetVal = 92;     // Modelkit processing error encountered
                     if (strlen( pszModelkitBatRetString ) > 0)
                        sErrMsg = QString( "Error: Modelkit processing error encountered (returned %1) on '%2':  %3" ).arg( QString::number( iModelkitBatRetVal ), sMkIDFFilenameNoExt, pszModelkitBatRetString );
                     else
                        sErrMsg = QString( "Error: Modelkit processing error encountered (returned %1) on '%2'" ).arg( QString::number( iModelkitBatRetVal ), sMkIDFFilenameNoExt );
                  }
                  else if (bVerbose && strlen( pszModelkitBatRetString ) > 0)
                     BEMMessageBox( QString( "Modelkit processing on %1 successful:  %2" ).arg( sMkIDFFilenameNoExt, pszModelkitBatRetString ) );
               }
            }  // end of Modelkit processing - SAC 06/23/22

			// Execute AnalysisActions that pertain to ActOnSimInput - SAC 3/10/20
				if (lSimRetVal == 0 && FileExists( qsIDFPathFile ))
				{	int iAnalPhase = -1;
					if (iCodeType == CT_T24N)
					{	switch (oswSimInfo[iSI].iProgressModel)
						{	case BCM_NRP_Model_zb	:	iAnalPhase = BEMAnalActPhase_BaselineSizing;  break;
							case BCM_NRP_Model_ab	:	iAnalPhase = BEMAnalActPhase_BaselineAnnual;  break;
							case BCM_NRP_Model_zp	:	iAnalPhase = BEMAnalActPhase_ProposedSizing;  break;
							case BCM_NRP_Model_ap	:	iAnalPhase = BEMAnalActPhase_ProposedAnnual;  break;
					}	}
					else
					{	switch (oswSimInfo[iSI].iProgressModel)
						{	case BCM_NRAP_Model_zp	:	iAnalPhase = BEMAnalActPhase_ProposedSizing;  break;
							case BCM_NRAP_Model_ap	:	iAnalPhase = BEMAnalActPhase_ProposedAnnual;  break;
							case BCM_NRAP_Model_zb1	:	iAnalPhase = BEMAnalActPhase_BaselineSizing;  break;
							case BCM_NRAP_Model_zb2	:	iAnalPhase = BEMAnalActPhase_BaselineSizing;  break;
							case BCM_NRAP_Model_zb3	:	iAnalPhase = BEMAnalActPhase_BaselineSizing;  break;
							case BCM_NRAP_Model_zb4	:	iAnalPhase = BEMAnalActPhase_BaselineSizing;  break;
							case BCM_NRAP_Model_ab1	:	iAnalPhase = BEMAnalActPhase_BaselineAnnual;  break;
							case BCM_NRAP_Model_ab2	:	iAnalPhase = BEMAnalActPhase_BaselineAnnual;  break;
							case BCM_NRAP_Model_ab3	:	iAnalPhase = BEMAnalActPhase_BaselineAnnual;  break;
							case BCM_NRAP_Model_ab4	:	iAnalPhase = BEMAnalActPhase_BaselineAnnual;  break;
					}	}
					if (iAnalPhase > 0)
					{	QString qsApplyAnalActError;
						int iApplyAnalActRetVal = BEMPX_ApplyAnalysisActionToDatabase( iAnalPhase, BEMAnalActWhen_Transform_ActOnEPlusSimInput, qsApplyAnalActError, bVerbose,
																											qsIDFPathFile.toLocal8Bit().constData() );
						if (iApplyAnalActRetVal > 0)
							qsApplyAnalActError = QString( "      %1 AnalysisAction(s) successfully applied to building model: %2 / %3" ).arg(
																QString::number(iApplyAnalActRetVal), AnalysisAction_PhaseString(iAnalPhase), AnalysisAction_BeforeAfter(BEMAnalActWhen_Transform_ActOnEPlusSimInput) );
						else if (iApplyAnalActRetVal < 0)
							lSimRetVal = 77;		// Error applying AnalysisAction(s) to building model
					//	else if (!qsApplyAnalActError.isEmpty())
					//	{	lSimRetVal = 77;		// Error applying AnalysisAction(s) to building model
					//	//	sErrMsg = qsApplyAnalActError;
					//	//	ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iErrID, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
					//	}
						if (!qsApplyAnalActError.isEmpty())
							BEMPX_WriteLogFile( qsApplyAnalActError, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}	}

				if (lSimRetVal == 0)
				{  char pszEPlusIDDFN[32] = "\0";
               if (oswSimInfo[iSI].bWriteCustomMetersHourlyCSV)      // SAC 10/04/21
               {  strcpy_s( pszEPlusIDDFN, 32, "Energy+500CstmMtrs.idd" );
                  BEMPX_WriteLogFile( QString("   simulating E+ using %1 to facilitate custom meter output").arg( pszEPlusIDDFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
               int iRunOK = epRunMgr.SetupRun( iRunIdx++, oswSimInfo[iSI].pszRunSubdir, qsIDFPathFile,
																oswSimInfo[iSI].pszWeatherPathFile, oswSimInfo[iSI].bStoreHourlyResults,
																oswSimInfo[iSI].iProgressModel, sSetupRunErrMsg, pszEPlusIDDFN );
					if (iRunOK != 0)
					{
						lSimRetVal = iRunOK;		// additional error reporting here??
               }
               else
               {  iNumRuns++;
                  if (iNumRuns == 1)
                     sFirstRunSubdir = oswSimInfo[iSI].pszRunSubdir;
               }
		}	}	}

		if (lSimRetVal == 0 && iRunIdx > 0)
		{
												//		bool bSaveFreezeProg = sbFreezeProgress;
												//		sbFreezeProgress = true;
//BEMMessageBox( "About to E+ via EPlusRunMgr" );
			epRunMgr.DoRuns();
//BEMMessageBox( "Back from E+ via EPlusRunMgr" );
												//		sbFreezeProgress = bSaveFreezeProg;
#ifdef _DEBUG  //VS19 - SAC 10/14/20
			BEMPX_WriteLogFile( QString( "   back from E+ via EPlusRunMgr:  %1 run(s), beginning w/ %2" ).arg( QString::number( iNumRuns ), sFirstRunSubdir ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
#endif  //VS19

			if (pdSimulationTime)
			{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStartTime;
				*pdSimulationTime = ((double) td.total_microseconds()) / 1000000.0;
			}

			// SAC 2/14/19 - split sim prep (above) from results retrieval (below) to allow for E+ sim management outside OpenStudio
			if (lSimRetVal == 0)
			{
				if (pszEPlusVerStr && iEPlusVerStrLen > 0)		// SAC 3/1/19
				{	QString sEPVerStr = epRunMgr.GetVersionInfo();
					if (!sEPVerStr.isEmpty())
					{	strncpy_s( pszEPlusVerStr, iEPlusVerStrLen, sEPVerStr.toLocal8Bit().constData(), iEPlusVerStrLen-1 );
						pszEPlusVerStr[iEPlusVerStrLen-1] = '\0';
				}	}
				dEPlusVerNum = epRunMgr.GetVersionNum();
		//		lSimRetVal = osWrap.ProcessResults_Multiple(	pszEPlusPath, pszSimProcessDir, poswSimInfo, iNumSimInfo,
		//										(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pszSimSDDErrorMsg, 1024, iCodeType, epRunMgr.GetVersionNum() );
			}

//	void DeleteRuns();


	}	}

	//else if (lSimRetVal == 0)
	if (lSimRetVal == 0)
	{
#ifdef _DEBUG  //VS19 - SAC 10/14/20
			BEMPX_WriteLogFile( QString( "   calling osWrap.ProcessResults_Multiple() on %1 run(s)" ).arg( QString::number( iNumSimInfo ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
#endif  //VS19
      			lSimRetVal = osWrap.ProcessResults_Multiple(	pszEPlusPath, pszSimProcessDir, poswSimInfo, iNumSimInfo,
												(OSWRAP_MSGCALLBACK*) OSWrapCallback, iProgressType, pszSimSDDErrorMsg, 1024, iCodeType, dEPlusVerNum );
#ifdef _DEBUG  //VS19 - SAC 10/14/20
			BEMPX_WriteLogFile( QString( "   back from osWrap.ProcessResults_Multiple(), retval:  %1" ).arg( QString::number( lSimRetVal ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
#endif  //VS19
   }

	if (dEPlusVer)
		*dEPlusVer = osWrap.EnergyPlusVersion( pszEPlusPath );  // SAC 5/16/14
#pragma warning(disable:4996)
//	if (pszEPlusVerStr && iEPlusVerStrLen > 0)
//	{	std::string sVerStr = osWrap.Get_SimVersionID(0);
//		strncpy( pszEPlusVerStr, sVerStr.c_str(), iEPlusVerStrLen-1 );
//		pszEPlusVerStr[iEPlusVerStrLen-1] = '\0';
//	}
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

//	bool bCopyHourlyResultsToNextModel = false;
//	for (iRun=0; iRun < iNumSimInfo; iRun++)
//	{
//		if (osRunInfo[iRun].StoreHourlyResults())
//			bCopyHourlyResultsToNextModel = true;
//		int iResCopyRetVal = 0;
//		if (iRun > 0 && bCopyHourlyResultsToNextModel && iRetVal == 0)
//		{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
//			QString sResCopyErrMsg;
//			iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, osRunInfo[iRun].RunID().toLocal8Bit().constData(), osRunInfo[iRun-1].BEMProcIdx(), osRunInfo[iRun].BEMProcIdx() );
//			assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
//			if (iResCopyRetVal > 0)
//			{	if (sErrMsg.isEmpty())
//				{	sErrMsg = sResCopyErrMsg;
//					sTempErr = QString( " (from run %1 to %2 (of %3))" ).arg( QString::number(iRun), QString::number(iRun+1), QString::number(iNumSimInfo) );
//					sErrMsg += sTempErr;
//				}
//				iRetVal = iResCopyRetVal;
//		}	}
//		if (iResCopyRetVal == 0)
//			ProcessSimulationResults( osWrap, osRunInfo[iRun], iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/17/14 - moved ALL results processing to subordinate routine
//	}
// SAC 7/23/18 - replaced above w/ below to ONLY retrieve E+ hourly results here - shifting remaining results processing into 
	for (iRun=0; iRun < iNumSimInfo; iRun++)
	{	if (osRunInfo[iRun].StoreHourlyResults())
			RetrieveSimulationResults( osWrap, osRunInfo[iRun], iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath );	// SAC 4/17/14 - moved ALL results processing to subordinate routine
	}
//	BEMPX_WriteLogFile( "  pausing 5 secs to allow E+cleanup", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//	Sleep(5000);				// SAC 5/22/19 - additional pause to ensure directory clean-up successful

   }  // end of: if (!bInitRunInfoOnly)     // SAC 10/29/21 (MFam)

								if (bVerbose && iRetVal != OSI_SimEPlus_UserAbortedAnalysis)
									BEMPX_WriteLogFile( "  PerfSim_E+ - returning", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	
	return iRetVal;
}


// SAC 7/23/18 - split out later portion of CMX_PerformSimulation_EnergyPlus_Multiple() to handle results processing following multiple engine simulations
int ProcessSimulationResults_Multiple(	OSWrapLib& osWrap, COSRunInfo* osRunInfo,
															QString& sErrMsg, const char* pszEPlusPath, const char* /*pszWthrPath*/, const char* pszSimProcessDir,
															OS_SimInfo** pSimInfo, int iNumSimInfo,		// SAC 8/19/15
													// other general args
															/*PUICallbackFunc lpfnCallback,*/ BOOL bVerbose /*=FALSE*/, // BOOL bPerformRangeChecks=TRUE,
                          							BOOL /*bDurationStats=FALSE*/, double* pdTranslationTime /*=NULL*/, double* pdSimulationTime /*=NULL*/,  // SAC 1/23/14
															int iSimulationStorage /*=-1*/, double* dEPlusVer /*=NULL*/, char* pszEPlusVerStr /*=NULL*/, int iEPlusVerStrLen /*=0*/,  // SAC 1/23/14  // SAC 5/16/14  // SAC 5/19/14
															char* pszOpenStudioVerStr /*=NULL*/, int iOpenStudioVerStrLen /*=0*/, int iCodeType /*=CT_T24N*/,
															bool bIncludeOutputDiagnostics /*=false*/, int iProgressType /*=0*/, 	// SAC 4/2/15		// SAC 5/27/15 - iProgressType see BCM_NRP_*
															QStringList* psaEPlusProcDirsToBeRemoved /*=NULL*/, bool bReportAllUMLHZones /*=false*/, 		// SAC 5/22/19 - added to postpone E+ directory cleanup until end of analysis to avoid deletion errors   // SAC 11/11/19
															QString* sStdDsgnCSEResultsPathFile /*=NULL*/, QVector<QString>* psaCopyAcrossModelClassPrefixes /*=NULL*/, 		// SAC 10/8/20 (tic #3218)   // SAC 11/24/20
                                             void* pCompRuleDebugInfo /*=NULL*/, bool bRptMissingEPFiles /*=true*/ )      // SAC 04/14/21
{
	int iRetVal = 0;
	QString sTempErr;

	bool bCopyHourlyResultsToNextModel = false;
	for (int iRun=0; iRun < iNumSimInfo; iRun++)
	{
		if (osRunInfo[iRun].StoreHourlyResults())
			bCopyHourlyResultsToNextModel = true;
		int iResCopyRetVal = 0;
		if (iRun > 0 && bCopyHourlyResultsToNextModel && iRetVal == 0)
		{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
			QString sResCopyErrMsg;
//BEMPX_WriteLogFile( QString( "   in ProcessSimulationResults_Multiple(), CM_CopyAnalysisResultsObjects_CECNonRes() BEMProcIdx %1 to %2" ).arg( QString::number(osRunInfo[iRun-1].BEMProcIdx()), QString::number(osRunInfo[iRun].BEMProcIdx()) ), NULL, FALSE, TRUE, FALSE );
			iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, osRunInfo[iRun].RunID().toLocal8Bit().constData(), osRunInfo[iRun-1].BEMProcIdx(), osRunInfo[iRun].BEMProcIdx(), psaCopyAcrossModelClassPrefixes );
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
		{
//BEMPX_WriteLogFile( QString( "   in ProcessSimulationResults_Multiple(), about to call ProcessNonresSimulationResults() on run %1" ).arg( osRunInfo[iRun].RunID() ), NULL, FALSE, TRUE, FALSE );
			ProcessNonresSimulationResults( osWrap, osRunInfo[iRun], iRetVal, pszSimProcessDir, bVerbose, iSimulationStorage, pszEPlusPath, 	// SAC 4/17/14 - moved ALL results processing to subordinate routine
														psaEPlusProcDirsToBeRemoved, bReportAllUMLHZones, sStdDsgnCSEResultsPathFile, bRptMissingEPFiles );		// SAC 5/22/19 - added to postpone E+ directory cleanup until end of analysis to avoid deletion errors   // SAC 11/11/19

      // call *_PostSim rulelist, if exists, to enable reporting of either hourly or non-hourly sim results - SAC 04/14/21
         QString sPostSimRulelistName = QString( "%1_PostSim" ).arg( osRunInfo[iRun].RunID() );
			if (!BEMPX_RulelistExists( sPostSimRulelistName.toLocal8Bit().constData() ))
         {
            if (bVerbose)
               BEMPX_WriteLogFile( QString::asprintf( "   rulelist not found (and therefore not evaluated):  %s", sPostSimRulelistName.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         }
         else
         {
				int iSaveActiveBEMProcIdx = BEMPX_GetActiveModel();
				BEMPX_SetActiveModel( osRunInfo[iRun].BEMProcIdx() );

            if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
               BEMPX_WriteLogFile( QString::asprintf( "   about to evaluate rulelist '%s' on BEMProcIdx %d", sPostSimRulelistName.toLocal8Bit().constData(), osRunInfo[iRun].BEMProcIdx() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			   //iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
   			//				if (bVerbose)
				//					BEMPX_WriteLogFile( "  PerfAnal_NRes - NRCCPRF XML prep rules", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   		   BOOL bPostSimEvalSuccessful = CMX_EvaluateRuleset( sPostSimRulelistName.toLocal8Bit().constData(), bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );     // SAC 04/14/21
			   //BEMPX_RefreshLogFile();
			   //if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs && iDontAbortOnErrorsThruStep < 8)
			   //{
				//	iRetVal = (iRetVal > 0 ? iRetVal : 81);
				//	bAbort = true;
			   //}

				if (BEMPX_GetActiveModel() != iSaveActiveBEMProcIdx)  // && !bAbort && !BEMPX_AbortRuleEvaluation())
					BEMPX_SetActiveModel( iSaveActiveBEMProcIdx );
         }
		}
	}

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
