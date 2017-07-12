// bemcm_LoadModel.cpp : Defines routines to load models (from input files).
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

#include <boost/filesystem.hpp>

#include "BEMCmpMgr.h"
#include "bemcm_I.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#ifdef OSWRAPPER
#include "OpenStudioInterface.h"
#endif
#include "memLkRpt.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Loading building models (w/ backward compatibility)

//	struct BEMStraightMap  // SAC 11/14/01 - added another method of mapping old properties to new
//	{
//	   int     iVersionCutoff;
//	   LPCSTR  szClassName;		// SAC 1/27/14 - switched from int* pi1Class to NAME of class/object type
//	   LPCSTR  szOldPropType;
//	   LPCSTR  szNewPropType;
//	   BOOL    bPostMappedData;
//	};

#ifdef OSWRAPPER		// => CEC Non-Res ---------------------------

BEMStraightMap sbemStraightMap[] = {
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      1,         "ThrmlZn",           "PrimAirCondgSysRef",                "PriAirCondgSysRef",                  TRUE         },     // SAC 1/27/14
     {      1,         "SpcFuncDefaults",   "ElevEscalSchRef",                   "ElevSchRef",                         TRUE         },     // SAC 1/27/14
     {      1,         "Spc",               "ElevEscalSchRef",                   "ElevSchRef",                         TRUE         },     // SAC 1/27/14
     {      1,         "Lum",               "LuminaireCategory",                 "Category",                           TRUE         },     // SAC 1/28/14
     {      1,         "Lum",               "LuminairePower",                    "Power",                              TRUE         },     // SAC 1/28/14
     {      1,         "Lum",               "LuminaireHeatGainSpaceFraction",    "HeatGainSpaceFraction",              TRUE         },     // SAC 1/28/14
     {      1,         "Lum",               "LuminaireHeatGainRadiantFraction",  "HeatGainRadiantFraction",            TRUE         },     // SAC 1/28/14
     {      1,         "ExtShdgObj",        "SolarReflecatance",                 "SolarReflectance",                   TRUE         },     // SAC 1/28/14
     {      1,         "ExtShdgObj",        "VisibleReflecatance",               "VisibleReflectance",                 TRUE         },     // SAC 1/28/14
     {      1,         "AirSys",            "CoolingSupplyAirTemperature",       "CoolingDesignSupplyAirTemperature",  TRUE         },     // SAC 1/27/14
     {      1,         "AirSys",            "HeatingSupplyAirTemperature",       "HeatingDesignSupplyAirTemperature",  TRUE         },     // SAC 1/27/14
     {      1,         "ZnSys",             "CoolingSupplyAirTemperature",       "CoolingDesignSupplyAirTemperature",  TRUE         },     // SAC 1/27/14
     {      1,         "ZnSys",             "HeatingSupplyAirTemperature",       "HeatingDesignSupplyAirTemperature",  TRUE         },     // SAC 1/27/14
     {      1,         "AirSys",            "ClgSupAirStageTempDiff",            "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtgCtrl",                           "ReheatCtrlMthd",                     FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtgFixedSupTemp",                   "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtgSetPtSchRef",                    "ClgSetptSchRef",                     FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtRstSupHi",                        "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtRstSupLow",                       "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtRstOutdrLow",                     "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtRstOutdrHi",                      "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "HtgSupAirStageTempDiff",            "DsgnPrehtTemp",                      FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "PkCoinClgLd",                       "CoolingCapacity",                    FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSys",            "PkCoinHtgLd",                       "HeatingCapacity",                    FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "ZnSys",             "PkCoinClgLd",                       "CoolingCapacity",                    FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "ZnSys",             "PkCoinHtgLd",                       "HeatingCapacity",                    FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
     {      1,         "AirSeg",            "Src",                               "Path",                               FALSE        },     // SAC 1/27/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      2,         "Proj",              "ExcptCndCRRC",                      "ExcptCondCRRC",                      TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndPartComp1",                 "ExcptCondPartComp1",                 TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndPartComp2",                 "ExcptCondPartComp2",                 TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndDsplyPerim",                "ExcptCondDisplayPerim",              TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndCompleteBldg",              "ExcptCondCompleteBldg",              TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndLtgCred",                   "ExcptCondLtgCred",                   TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndNoLtg",                     "ExcptCondNoLtg",                     TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndDesIllum",                  "ExcptCondDsgnIllum",                 TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndExtLtg",                    "ExcptCondExtLtg",                    TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndRtdCap",                    "ExcptCondRtdCap",                    TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndFanPress",                  "ExcptCondFanPress",                  TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndWCC",                       "ExcptCondWCC",                       TRUE         },     // SAC 1/29/14
     {      2,         "Proj",              "ExcptCndElevEsc",                   "ExcptCondElevEscal",                 TRUE         },     // SAC 1/29/14
//     {      2,         "RecircDHWSys",      "RecircPumpPwr",                     "PumpPwr",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPumpHP",                      "PumpHP",                             TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPumpEff",                     "PumpEff",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircSysStoryCnt",                 "SysStoryCnt",                        TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircLivingUnitCnt",               "LivingUnitCnt",                      TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircSysFlrArea",                  "SysFlrArea",                         TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircWtrHtrCnt",                   "WtrHtrCnt",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeLen",                     "PipeLen",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeDia",                     "PipeDia",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeLctn",                    "PipeLctn",                           TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircLpCnt",                       "LpCnt",                              TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeExtraIns",                "PipeExtraIns",                       TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationPumpPower",            "PumpPower",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationPumpHorsepower",       "PumpHorsepower",                     TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationPumpEfficiency",       "PumpEfficiency",                     TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationSystemStoryCount",     "SystemStoryCount",                   TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationLivingUnitCount",      "LivingUnitCount",                    TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationSystemFloorArea",      "SystemFloorArea",                    TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationWaterHeaterCount",     "WaterHeaterCount",                   TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeLength",                  "PipeLength",                         TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeDiameter",                "PipeDiameter",                       TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecircPipeLocation",                "PipeLocation",                       TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationLoopCount",            "LoopCount",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
//     {      2,         "RecircDHWSys",      "RecirculationPipeExtraInsulation",  "PipeExtraInsulation",                TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
//     {      3,         "Spc",               "FlrArea",                           "Area",                               TRUE         },     // SAC 3/14/14   - SAC 5/13/14 - 'FlrArea' still a valid property, so this would never get triggerred
     {      3,         "Spc",               "ElevEscalSchRef",                   "ElevSchRef",                         TRUE         },     // SAC 3/23/14
     {      3,         "IntLtgSys",         "AllowBoardWd",                      "AllowLen",                           TRUE         },     // SAC 5/13/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      4,         "DrCons",            "GlsArea",                           "Open",                               FALSE        },     // SAC 4/17/14
     {      4,         "DrCons",            "Frm",                               "Open",                               FALSE        },     // SAC 4/17/14
     {      4,         "DrCons",            "GlsPn",                             "Open",                               FALSE        },     // SAC 4/17/14
     {      4,         "DrCons",            "GlsTnt",                            "Open",                               FALSE        },     // SAC 4/17/14
     {      4,         "DrCons",            "SHGC",                              "UFactor",                            FALSE        },     // SAC 4/17/14
     {      4,         "AirSys",            "HVACAutoSizing",                    "Cnt",                                FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "VentCtrl",                          "NightCycleFanCtrl",                  FALSE        },     // SAC 4/24/14
     {      4,         "AirSys",            "GarageVentCtrlMthd",                "NightCycleFanCtrl",                  FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "FDDEnabled",                        "Cnt",                                FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "WesternClgChallengeCert",           "Cnt",                                FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "HtgCap",                            "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "UnmetClgLdHrs",                     "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "UnmetHtgLdHrs",                     "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "SupAirSegRef",                      "NightCycleFanCtrl",                  FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "RetAirSegRef",                      "NightCycleFanCtrl",                  FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "OACtrlRef",                         "NightCycleFanCtrl",                  FALSE        },     // SAC 4/24/14
  // {      4,         "AirSys",            "BaseSysNum",                        "Cnt",                                FALSE        },     // SAC 4/24/14
  // {      4,         "ZnSys",             "HtgCap",                            "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "ZnSys",             "UnmetClgLdHrs",                     "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "ZnSys",             "UnmetHtgLdHrs",                     "ClRstSupHi",                         FALSE        },     // SAC 4/24/14
  // {      4,         "TrmlUnit",          "ReheatDelTemp",                     "HtgAirFlowMax",                      FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "FuelSrc",                           "Type",                               FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "CapSensGrossRtd",                   "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "CapSensNetRtd",                     "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "DXAirflowAdjFac",                   "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "DXFDDFac",                          "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "DXRfrgtChrgFac",                    "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "CoilClg",           "DXUnldRatMin",                      "CapTotNetRtd",                       FALSE        },     // SAC 4/24/14
  // {      4,         "Fan",               "Pwr_fPLRCrvRef",                    "MtrType",                            FALSE        },     // SAC 4/24/14
  // {      4,         "OACtrl",            "EconoHiEnthLockout",                "EconoHiTempLockout",                 FALSE        },     // SAC 4/24/14
  // {      4,         "OACtrl",            "OASchMthd",                         "EconoCtrlMthd",                      FALSE        },     // SAC 4/24/14
  // {      4,         "OACtrl",            "StartUpDelay",                      "EconoHiTempLockout",                 FALSE        },     // SAC 4/24/14
     {      4,         "FluidSys",          "HVACAutoSizing",                    "SHWSysCnt",                          FALSE        },     // SAC 4/24/14
  // {      4,         "FluidSys",          "ClgCap",                            "DsgnSupWtrTemp",                     FALSE        },     // SAC 4/24/14
  // {      4,         "FluidSys",          "HtgCap",                            "DsgnSupWtrTemp",                     FALSE        },     // SAC 4/24/14
  // {      4,         "FluidSys",          "UnmetClgLdHrs",                     "DsgnSupWtrTemp",                     FALSE        },     // SAC 4/24/14
  // {      4,         "FluidSys",          "UnmetHtgLdHrs",                     "DsgnSupWtrTemp",                     FALSE        },     // SAC 4/24/14
     {      4,         "FluidSeg",          "PipeDia",                           "PumpRef",                            FALSE        },     // SAC 4/24/14
     {      4,         "FluidSeg",          "PipeInsThkns",                      "PumpRef",                            FALSE        },     // SAC 4/24/14
     {      4,         "FluidSeg",          "CndctLoss",                         "PumpRef",                            FALSE        },     // SAC 4/24/14
     {      4,         "FluidSeg",          "WtrMnTempSchRef",                   "PumpRef",                            FALSE        },     // SAC 4/24/14
     {      4,         "Chlr",              "Cnt",                               "EvapHasBypass",                      FALSE        },     // SAC 4/24/14
  // {      4,         "Chlr",              "EIR",                               "COP",                                FALSE        },     // SAC 4/24/14
     {      4,         "Chlr",              "EngSpdMin",                         "COP",                                FALSE        },     // SAC 4/24/14
  // {      4,         "HtRej",             "Cap_fTempCrvRef",                   "Pwr_fPLRCrvRef",                     FALSE        },     // SAC 4/24/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      5,         "Proj",              "CliZnCity",                         "CliZnCounty",                        FALSE        },     // SAC 5/9/14
     {      5,         "Proj",              "AutoHardSizeClgSensHtRatRtd",       "AutoHardSizeAirFlowPerSqFt",         FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "ConsPhase",                         "Status",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "CBCOccGrp",                         "Status",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "FenFlrRat",                         "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "ClgUnmetLdHrs",                     "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "HtgUnmetLdHrs",                     "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "CoinDsgnClgLd",                     "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "CoinDsgnHtgLd",                     "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "NonCoinDsgnClgLd",                  "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "NonCoinDsgnHtgLd",                  "BldgAz",                             FALSE        },     // SAC 5/12/14
     {      5,         "Bldg",              "NAng",                              "NAngVector",                         FALSE        },     // SAC 5/13/14
     {      5,         "Spc",               "DsgnNaturalVentRt",                 "IntLPDReg",                          FALSE        },     // SAC 5/12/14
     {      5,         "Spc",               "NaturalVentSchRef",                 "IntLtgRegSchRef",                    FALSE        },     // SAC 5/12/14
     {      5,         "Spc",               "SkylitDayltgCtrlRef",               "IntLtgRegSchRef",                    FALSE        },     // SAC 5/12/14
     {      5,         "Spc",               "PriSideDayltgCtrlRef",              "IntLtgRegSchRef",                    FALSE        },     // SAC 5/12/14
     {      5,         "Spc",               "SecSideDayltgCtrlRef",              "IntLtgRegSchRef",                    FALSE        },     // SAC 5/12/14
     {      5,         "Spc",               "LabRecptUseType",                   "IntLtgRegSchRef",                    FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "ExhSysRef",                         "PriAirCondgSysRef",                  FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "ExhFlowSchRef",                     "PriAirCondgSysRef",                  FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "ExhFlowRt",                         "DayltgCtrlLtgFrac1",                 FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "PassiveClgMthd",                    "DayltgCtrlType",                     FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "PassiveClgRt",                      "DayltgCtrlLtgFrac1",                 FALSE        },     // SAC 5/12/14
     {      5,         "ThrmZn",            "PassiveClgSchRef",                  "PriAirCondgSysRef",                  FALSE        },     // SAC 5/12/14
     {      5,         "AirSys",            "HVACAutoSizing",                    "Cnt",                                FALSE        },     // SAC 5/12/14
     {      5,         "AirSys",            "GarageVentCtrlMthd",                "CtrlSysType",                        FALSE        },     // SAC 5/12/14
     {      5,         "FluidSeg",          "PipeDia",                           "PriSegRef",                          FALSE        },     // SAC 5/12/14
     {      5,         "FluidSeg",          "PipeInsThkns",                      "PriSegRef",                          FALSE        },     // SAC 5/12/14
     {      5,         "FluidSeg",          "CndctLoss",                         "PriSegRef",                          FALSE        },     // SAC 5/12/14
     {      5,         "Chlr",              "Cnt",                               "EvapHasBypass",                      FALSE        },     // SAC 5/12/14
     {      5,         "Chlr",              "EngSpdMin",                         "IPLVEER",                            FALSE        },     // SAC 5/12/14
     {      5,         "Blr",               "Cnt",                               "HasBypass",                          FALSE        },     // SAC 5/12/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      6,         "Fan",               "OverallEff",                        "FlowEff",                            TRUE         },     // SAC 7/17/14
     {      6,         "Proj",              "DisableDayltgCtrlFlag",             "TimeZn",                             FALSE        },     // SAC 8/12/14
     {      6,         "Proj",              "DisableDayltgCtrlDefault",          "TimeZn",                             FALSE        },     // SAC 9/3/14
     {      6,         "ThrmlZn",           "DisableDayltgCtrl1",                "Mult",                               FALSE        },     // SAC 8/12/14
     {      6,         "ThrmlZn",           "DisableDayltgCtrl2",                "Mult",                               FALSE        },     // SAC 8/12/14
     {      6,         "Spc",               "SkylitDayltgCtrls",                 "IntLtgRegSchRef",                    FALSE        },     // SAC 8/12/14
     {      6,         "Spc",               "PriSideDayltgCtrls",                "IntLtgRegSchRef",                    FALSE        },     // SAC 8/12/14
     {      6,         "Spc",               "SecSideDayltgCtrls",                "IntLtgRegSchRef",                    FALSE        },     // SAC 8/12/14
     {      6,         "Spc",               "VentRt",                            "IntLPDReg",                          FALSE        },     // SAC 8/12/14
     {      6,         "WtrHtr",            "FluidSegInRef",                     "FluidSegOutRef",                     FALSE        },     // SAC 9/23/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      7,         "Lum",               "LuminaireType",                     "LampType",                           TRUE         },     // SAC 11/16/14
     {      7,         "Spc",               "InstalledSkylitPower",              "SkylitDayltgInstalledLtgPwr",        TRUE         },     // SAC 11/16/14
     {      7,         "Spc",               "InstalledPrimarySidelitPower",      "PriSideDayltgInstalledLtgPwr",       TRUE         },     // SAC 11/16/14
     {      7,         "Spc",               "InstalledSecondarySidelitPower",    "SecSideDayltgInstalledLtgPwr",       TRUE         },     // SAC 11/16/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      8,         "FluidSys",          "CtrlScheme",                        "Type",                               FALSE        },     // SAC 12/9/14
     {      8,         "FluidSys",          "EquipRef",                          "Type",                               FALSE        },     // SAC 12/9/14
     {      8,         "FluidSys",          "SeqNum",                            "Type",                               FALSE        },     // SAC 12/9/14
     {      8,         "FluidSys",          "TempSetpt",                         "Type",                               FALSE        },     // SAC 12/9/14
     {      8,         "FluidSys",          "MinLd",                             "Type",                               FALSE        },     // SAC 12/9/14
     {      8,         "FluidSys",          "MaxLd",                             "Type",                               FALSE        },     // SAC 12/9/14

     {      8,         "IntLtgSys",         "AreaCatAllowType",                  "AllowType",                          TRUE         },     // SAC 12/19/14
     {      8,         "IntLtgSys",         "TailoredMthdAllowType",             "AllowType",                          TRUE         },     // SAC 12/19/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {     10,         "Proj",              "OwnerName",                         "EnvDsgnrName",                       FALSE        },     // SAC 1/13/15
     {     10,         "Proj",              "OwnerTitle",                        "EnvDsgnrName",                       FALSE        },     // SAC 1/13/15
     {     10,         "Proj",              "OwnerOrg",                          "EnvDsgnrName",                       FALSE        },     // SAC 1/13/15
     {     10,         "Proj",              "OwnerEmail",                        "EnvDsgnrName",                       FALSE        },     // SAC 1/13/15
     {     10,         "Proj",              "OwnerPhone",                        "EnvDsgnrName",                       FALSE        },     // SAC 1/13/15
     {     10,         "Proj",              "ArchName",									"EnvDsgnrName",					        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "ArchTitle",									"EnvDsgnrName",					        FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "ArchOrg",									"EnvDsgnrCompany",					     TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "ArchEmail",									"EnvDsgnrName",					        FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "ArchPhone",									"EnvDsgnrPhone",					        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "HVACEngrName",								"MechDsgnrName",					        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "HVACEngrTitle",							"MechDsgnrName",					        FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "HVACEngrOrg",								"MechDsgnrCompany",					     TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "HVACEngrEmail",							"MechDsgnrName",					        FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "HVACEngrPhone",							"MechDsgnrPhone",					        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "LtgDsgnrName",								"LtgDsgnrName",				           TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "LtgDsgnrTitle",							"LtgDsgnrName",				           FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "LtgDsgnrOrg",								"LtgDsgnrCompany",				        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "LtgDsgnrEmail",							"LtgDsgnrName",				           FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "LtgDsgnrPhone",							"LtgDsgnrPhone",			 		        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "EnergyMdlrName",							"DocAuthName",			  		           TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "EnergyMdlrTitle",							"DocAuthName",			  		           FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "EnergyMdlrOrg",							"DocAuthCompany",			  		        TRUE         },     // SAC 1/19/15
     {     10,         "Proj",              "EnergyMdlrEmail",							"DocAuthName",			  		           FALSE        },     // SAC 1/19/15
     {     10,         "Proj",              "EnergyMdlrPhone",							"DocAuthPhone",				           TRUE         },     // SAC 1/19/15
     {      8,         "Bldg",              "LivingUnitCnt",							"HighRiseResLivingUnitCnt",			  TRUE         },     // SAC 1/21/15 - over phone w/ LH
     {      8,         "Bldg",              "ResidentialStoryCountFossilHeat",	"NonresidentialStoryCountElectricHeat",  TRUE      },     // SAC 1/31/15
     {      8,         "Bldg",              "NonresidentialStoryCountElectricHeat", "ResidentialStoryCountFossilHeat",	  TRUE      },     // SAC 1/31/15
     {      8,         "Spc",               "LabExhaustRateType",						"LabExhRtType",							  TRUE         },     // SAC 1/31/15
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {      9,         "FluidSys",          "EvapFluidSegInRef",                 "Type",                               FALSE        },     // SAC 3/20/15
     {      9,         "Proj",              "EnvDetailsLoc",                     "EnvDetailsLctn",                     TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "MechDetailsLoc",                    "MechDetailsLctn",                    TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "DHWDetailsLoc",                     "DHWDetailsLctn",                     TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "LtgDetailsLoc",                     "LtgDetailsLctn",                     TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "CompPathKitch",                     "CompPathKit",                        TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "LtgOutdoorComp",                    "LtgOutdrComp",                       TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "SolarThermalComp",                  "SolThrmlComp",                       TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "SolarReadyMandComp",                "SolReadyMandComp",                   TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "ComRefrMandComp",                   "ComRfrgMandComp",                    TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "RefrWarehouseMandComp",             "RfrgWarehouseMandComp",              TRUE         },     // SAC 3/26/15
     {      9,         "Proj",              "OutdoorCtrlsRpt",                   "OutdrCtrlsRpt",                      TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "CRRCInitialEmittance",              "CRRCInitialEmit",                    TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "CRRCAgedEmittance",                 "CRRCAgedEmit",                       TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "RoofDens",                          "RfDens",                             TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "BuiltUpRoof",                       "BuiltUpRf",                          TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "BallastedRoof",                     "BallastedRf",                        TRUE         },     // SAC 3/26/15
     {      9,         "FenCons",           "ShadingCred",                       "ShdgCred",                           TRUE         },     // SAC 3/26/15
     {      9,         "Bldg",              "HotelMotelGuestRoomCnt",            "HotelMotelGuestRmCnt",               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "IsHotelMotelGuestRoom",             "IsHotelMotelGuestRm",                TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "HotelMotelGuestRoomCondFlrArea",    "HotelMotelGuestRmCondFlrArea",       TRUE         },     // SAC 3/26/15
     {      9,         "Roof",              "CRRCInitialEmittance",              "CRRCInitialEmit",                    TRUE         },     // SAC 3/26/15
     {      9,         "Roof",              "CRRCAgedEmittance",                 "CRRCAgedEmit",                       TRUE         },     // SAC 3/26/15
     {      9,         "ConsAssm",          "ThrmlEmittanceASTMCertification",   "ThrmlEmitASTMCertification",         FALSE        },     // SAC 5/27/15
     {      9,         "ConsAssm",          "RoofAgedThrmlEmittance",            "RoofAgedThrmlEmit",                  FALSE        },     // SAC 5/27/15
     {      9,         "ConsAssm",          "SolReflASTMCertification",          "RoofAgedThrmlEmit",                  FALSE        },     // SAC 5/27/15
     {      9,         "ConsAssm",          "RoofAgedSolRefl",                   "RoofAgedThrmlEmit",                  FALSE        },     // SAC 5/27/15
     {      9,         "Roof",              "RoofAgedThrmlEmittance",            "RoofAgedThrmlEmit",                  FALSE        },     // SAC 4/15/15
     {      9,         "AirSys",            "Mch02A",                            "NRCAMch02A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch03A",                            "NRCAMch03A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch04A",                            "NRCAMch04H",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch05A",                            "NRCAMch05A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch06A",                            "NRCAMch06A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch07A",                            "NRCAMch07A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch08A",                            "NRCAMch08A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch09A",                            "NRCAMch09A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch10A",                            "NRCAMch10A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch11A",                            "NRCAMch11A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch12A",                            "NRCAMch12A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch13A",                            "NRCAMch13A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch14A",                            "NRCAMch14A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch15A",                            "NRCAMch15A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch16A",                            "NRCAMch16A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch17A",                            "NRCAMch17A",                         TRUE         },     // SAC 5/5/15
     {      9,         "AirSys",            "Mch18A",                            "NRCAMch18A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch02A",                            "NRCAMch02A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch03A",                            "NRCAMch03A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch04A",                            "NRCAMch04H",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch05A",                            "NRCAMch05A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch06A",                            "NRCAMch06A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch07A",                            "NRCAMch07A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch08A",                            "NRCAMch08A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch09A",                            "NRCAMch09A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch10A",                            "NRCAMch10A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch11A",                            "NRCAMch11A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch12A",                            "NRCAMch12A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch13A",                            "NRCAMch13A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch14A",                            "NRCAMch14A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch15A",                            "NRCAMch15A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch16A",                            "NRCAMch16A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch17A",                            "NRCAMch17A",                         TRUE         },     // SAC 5/5/15
     {      9,         "ZnSys",             "Mch18A",                            "NRCAMch18A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch02A",                            "NRCAMch02A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch03A",                            "NRCAMch03A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch04A",                            "NRCAMch04H",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch05A",                            "NRCAMch05A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch06A",                            "NRCAMch06A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch07A",                            "NRCAMch07A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch08A",                            "NRCAMch08A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch09A",                            "NRCAMch09A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch10A",                            "NRCAMch10A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch11A",                            "NRCAMch11A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch12A",                            "NRCAMch12A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch13A",                            "NRCAMch13A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch14A",                            "NRCAMch14A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch15A",                            "NRCAMch15A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch16A",                            "NRCAMch16A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch17A",                            "NRCAMch17A",                         TRUE         },     // SAC 5/5/15
     {      9,         "FluidSys",          "Mch18A",                            "NRCAMch18A",                         TRUE         },     // SAC 5/5/15
//     {     10,         "Proj",              "ArchDsgnrName",     						"EnvDsgnrName",    						  TRUE			},		 // SAC 6/11/15		- removed 8/12/15 while testing ruleset-based data model backward compat
//     {     10,         "Proj",              "ArchDsgnrLicense",  						"EnvDsgnrLicense", 						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrCompany",  						"EnvDsgnrCompany", 						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrAddress",  						"EnvDsgnrAddress", 						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrCity",     						"EnvDsgnrCity",    						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrState",    						"EnvDsgnrState",   						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrZipCode",  						"EnvDsgnrZipCode", 						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "ArchDsgnrPhone",    						"EnvDsgnrPhone",   						  TRUE			},		 // SAC 6/11/15	
//     {     10,         "Proj",              "BldgOwnerName",                     "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerCompany",                  "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerAddress",                  "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerCity",                     "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerState",                    "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerZipCode",                  "EnvDsgnrZipCode",                    FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "BldgOwnerPhone",                    "EnvDsgnrName",                       FALSE        },		 // SAC 6/11/15
//     {     10,         "AirSys",            "DsgnAirFlowMin",                    "DsgnAirFlowMinRat",                  FALSE        },     // SAC 6/11/15
//     {     10,         "FluidSys",          "Number",                            "SolCollectorCnt",                    TRUE         },     // SAC 6/11/15
//     {     10,         "FluidSys",          "SolPanelCnt",                       "SolCollectorCnt",                    TRUE         },     // SAC 6/11/15
//     {     10,         "Spc",               "MandatoryLtgCtrlRpt",               "IsHotelMotelGuestRm",                FALSE        },     // SAC 6/11/15
//     {     10,         "ConsAssm",          "RfDens",                            "RoofDens",                           TRUE         },		 // SAC 6/12/15
//     {     10,         "ConsAssm",          "BuiltUpRf",                         "BuiltUpRoof",                        TRUE         },		 // SAC 6/12/15
//     {     10,         "ConsAssm",          "BallastedRf",                       "BallastedRoof",                      TRUE         },		 // SAC 6/12/15
//     {     10,         "RecircDHWSys",      "Number",                            "SolCollectorCnt",                    TRUE         },     // SAC 6/16/15
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
     {     10,         "SpcFuncDefaults",   "RecircDHWSysRef",                   "ResDHWSysRef",                       TRUE         },     // SAC 5/25/16 - related to switch from RecirdDHW* -> ResDHW*
     {     10,         "Spc",               "RecircDHWSysRef",                   "ResDHWSysRef",                       TRUE         },     // SAC 5/25/16
     {     10,         "Spc",               "RecircHotWtrHtgRt",                 "ResWtrHtgRt",                        TRUE         },     // SAC 5/25/16
     {     11,         "IntLtgSys",         "Status",                            "LumStatus[1]",                       TRUE         },     // SAC 6/1/16
                                                                  { 0, NULL, NULL, NULL, FALSE } };

BEMStraightMap sbemIgnorNewlyNotInputProperties[] = {
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData - in this case used to indicate that a reset should be reported
     {      6,         "Proj",              "ExcptCondLtgCred",                  "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondNoLtg",                    "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondDsgnIllum",                "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondCRRC",                     "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondPartComp1",                "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondPartComp2",                "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondPartComp3",                "none",                               TRUE         },     // SAC 8/7/14
     {      6,         "Proj",              "ExcptCondDisplayPerim",             "none",                               TRUE         },     // SAC 8/12/14
     {      6,         "Mat",               "RVal",                              "none",                               FALSE        },     // SAC 8/12/14
     {      6,         "Mat",               "ThrmlCndct",                        "none",                               FALSE        },     // SAC 8/12/14
     {      6,         "Mat",               "SpecHt",                            "none",                               FALSE        },     // SAC 8/12/14
     {      6,         "Mat",               "Dens",                              "none",                               FALSE        },     // SAC 8/12/14
     {      6,         "Mat",               "Thkns",                             "none",                               FALSE        },     // SAC 8/12/14
     {      7,         "ConsAssm",          "FFactor",                           "none",                               FALSE        },     // SAC 8/18/14
     {      7,         "ConsAssm",          "CFactor",                           "none",                               FALSE        },     // SAC 8/18/14
     {      7,         "Proj",              "SimVarsInterval",                   "none",                               FALSE        },     // SAC 11/16/14
     {      7,         "Proj",              "BaseHVACSameAsPropHVAC",            "none",                               FALSE        },     // SAC 11/16/14
     {      7,         "Proj",              "IsBaseHVAC",                        "none",                               FALSE        },     // SAC 11/16/14
     {      7,         "ConsAssm",          "ExtSolAbs",                         "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "ConsAssm",          "ExtThrmlAbs",                       "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "ConsAssm",          "ExtVisAbs",                         "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "ConsAssm",          "IntSolAbs",                         "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "ConsAssm",          "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "ConsAssm",          "IntVisAbs",                         "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "Spc",               "MaxPerimExposed",                   "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "IntLtgSys",         "SchRef",                            "none",                               TRUE         },     // SAC 11/16/14
     {      7,         "IntLtgSys",         "IntLtgSpecMthd",                    "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "ExtSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "ExtThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "ExtVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "IntSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtFlr",            "IntVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "ExtSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "ExtThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "ExtVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "IntSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ExtWall",           "IntVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "ExtSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "ExtThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "ExtVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "IntSolAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "IntWall",           "IntVisAbs",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ThrmlZn",           "Mult",                              "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "ThrmlZn",           "DCVIsRequired",                     "none",                               FALSE        },     // SAC 11/17/14
     {      7,         "AirSys",            "IsSglZnSys",                        "none",                               FALSE        },     // SAC 11/17/14
     {      7,         "AirSys",            "TrmlUnitHtgCapHotWtr",              "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "AirSys",            "TrmlUnitHtgCapOther",               "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "CoilClg",           "SizingRat",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "CoilHtg",           "SizingRat",                         "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "CoilHtg",           "CapTotRtdStageFrac",                "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "CtrlScheme",                        "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "EquipRef",                          "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "SeqNum",                            "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "TempSetpt",                         "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "MinLd",                             "none",                               TRUE         },     // SAC 11/17/14
//     {      7,         "FluidSys",          "MaxLd",                             "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "WtrHtr",            "CapRtdWithCnt",                     "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "WtrHtr",            "StorCapWithCnt",                    "none",                               TRUE         },     // SAC 11/17/14
     {      7,         "Ceiling",           "ExtThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Ceiling",           "ExtVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Ceiling",           "IntSolAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Ceiling",           "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Ceiling",           "IntVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "IntFlr",            "IntSolAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "IntFlr",            "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "IntFlr",            "IntVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Roof",              "IntSolAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Roof",              "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "Roof",              "IntVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrFlr",          "IntSolAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrFlr",          "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrFlr",          "IntVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrWall",         "IntSolAbs",                         "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrWall",         "IntThrmlAbs",                       "none",                               TRUE         },     // SAC 3/17/15
     {      7,         "UndgrWall",         "IntVisAbs",                         "none",                               TRUE         },     // SAC 3/17/15

     {      9,         "Mat",               "CompositeMatNotes",                 "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Mat",               "HeaderIns",                         "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Mat",               "CMUWt",                             "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Mat",               "CMUFill",                           "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Mat",               "SpandrelPanelIns",                  "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Mat",               "ICCESRptNum",                       "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Mat",               "InsOutsdWtrprfMemb",                "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Spc",               "FuncSchGrp",                        "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Spc",               "OccSensHtRt",                       "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Spc",               "OccLatHtRt",                        "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Spc",               "OccSchRef",                         "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Spc",               "SkylitDayltgRefPtCoord",            "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Spc",               "SkylitDayltgCtrlLtgFrac",           "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Spc",               "PriSideDayltgCtrlLtgFrac",          "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Spc",               "SecSideDayltgCtrlLtgFrac",          "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "ThrmlZn",           "ClgDsgnSizingFac",                  "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "ThrmlZn",           "HtgDsgnSizingFac",                  "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "ThrmlZn",           "ExhFanName",                        "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "ThrmlZn",           "ExhFlowSim",                        "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "DsgnPrehtTemp",                     "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "DsgnPrehtHumidityRat",              "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "DsgnPreclTemp",                     "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "DsgnPreclHumidityRat",              "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "SizingOption",                      "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "ClgAllOutsdAir",                    "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "HtgAllOutsdAir",                    "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "ClgDsgnHumidityRat",                "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "HtgDsgnHumidityRat",                "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "AirSys",            "AirDistType",                       "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "ZnSys",             "ClgCtrl",                           "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "ZnSys",             "AirDistType",                       "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "TrmlUnit",          "MinAirFracSchRef",                  "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Chlr",              "WtrFlowCap",                        "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Blr",               "HIR_fPLRCrvRef",                    "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "Blr",               "WtrFlowCap",                        "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "HtRej",             "Pwr_fPLRCrvRef",                    "none",                               FALSE        },     // SAC 3/20/15
     {      9,         "HtRej",             "LowSpdPwrRat",                      "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "Pump",              "Cnt",                               "none",                               TRUE         },     // SAC 3/20/15
     {      9,         "IntLtgSys",         "ParentSpcFunc",                     "none",                               FALSE        },     // SAC 3/26/15
//     {      9,         "ConsAssm",          "SolReflASTMCertification",          "none",                               TRUE         },     // SAC 3/26/15
//     {      9,         "ConsAssm",          "ThrmlEmittanceASTMCertification",   "none",                               TRUE         },     // SAC 5/5/15
//     {      9,         "ConsAssm",          "RoofAgedSolRefl",                   "none",                               TRUE         },     // SAC 3/26/15
//     {      9,         "ConsAssm",          "RoofAgedThrmlEmittance",            "none",                               TRUE         },     // SAC 5/5/15
     {      9,         "Spc",               "BaseRecptPwrDens",                  "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "BaseRecptSchRef",                   "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "RecptPwrExcptCond",                 "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "BaseGasEqpPwrDens",                 "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "BaseGasEqpSchRef",                  "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "GasEqpPwrDensExcptCond",            "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "BaseCommRfrgEPD",                   "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "BaseCommRfrgEqpSchRef",             "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Spc",               "CommRfrgEPDExcptCond",              "none",                               TRUE         },     // SAC 3/26/15
     {      9,         "Roof",              "RoofAgedSolRefl",                   "none",                               TRUE         },     // SAC 3/26/15
//     {      9,         "Roof",              "RoofAgedThrmlEmittance",            "none",                               TRUE         },     // SAC 3/26/15
//     {      9,         "AirSys",            "StaticPressRstCtrl",                "none",                               TRUE         },     // SAC 3/26/15		- moved to rules
     {      9,         "Spc",               "PriSideDayltgRefPtCoord",           "none",                               TRUE         },     // SAC 5/5/15
     {      9,         "Spc",               "SecSideDayltgRefPtCoord",           "none",                               TRUE         },     // SAC 5/5/15
     {      9,         "Proj",              "PermitMonth",                       "none",                               FALSE        },		 // SAC 6/11/15
     {      9,         "Proj",              "PermitDay",                         "none",                               FALSE        },		 // SAC 6/11/15
     {      9,         "Proj",              "PermitYear",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch02A",                        "none",                               FALSE        },		 // SAC 6/11/15		- SAC 8/13/15 - migrated to ruleset source
//     {     10,         "Proj",              "NRCAMch03A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch04H",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch05A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch06A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch07A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch08A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch09A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch10A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch11A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch12A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch13A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch14A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch15A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch16A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch17A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "Proj",              "NRCAMch18A",                        "none",                               FALSE        },		 // SAC 6/11/15
//     {     10,         "RecircDHWSys",      "LivingUnitCnt",                     "none",                               FALSE        },		 // SAC 6/16/15
     {     11,         "Spc",               "ResLivingUnitCnt",                  "DwellingUnitTypeCnt[3]",             TRUE         },     // SAC 6/1/16

                                                                  { 0, NULL, NULL, NULL, FALSE } };

BEMComponentMap sbemComponentMap[] = {
	// iVersionCutoff    iCompTypeID   szOldCompType               szNewCompType[5]
		{      5,              1,       "DayltgCtrl",               { NULL, NULL, NULL, NULL, NULL } },
		{     10,              2,       "RecircDHWSys",             { "ResDHWSys", NULL, NULL, NULL, NULL } },
		{     10,              3,       "RecirculationDHWSystem",   { "ResidentialDHWSystem", NULL, NULL, NULL, NULL } },
		{     10,              4,       "RecircWtrHtr",             { "ResWtrHtr", NULL, NULL, NULL, NULL } },
		{     10,              5,       "RecirculationWaterHeater", { "ResidentialWaterHeater", NULL, NULL, NULL, NULL } },
	 // end of list
		{ 0, 0, NULL, { NULL, NULL, NULL, NULL, NULL } } };

BEMPropertyMap sbemPropertyMap[] = {
	// iVersionCutoff    iCompTypeID   szOldPropType                                   szNewCompType   szNewPropType                           bPostMappedData
		{     10,              2,       "Status",                                       "ResDHWSys",    "Status",                                     TRUE  },
		{     10,              2,       "Type",                                         "ResDHWSys",    "Type",                                       TRUE  },
		{     10,              2,       "Mult",                                         "ResDHWSys",    "Mult",                                       TRUE  },
		{     10,              2,       "CentralSys",                                   "ResDHWSys",    "CentralSys",                                 TRUE  },
		{     10,              2,       "DistType",                                     "ResDHWSys",    "DistType",                                   TRUE  },
		{     10,              2,       "PumpPwr",                                      "ResDHWSys",    "PumpPwr",                                    TRUE  },
		{     10,              2,       "PumpEff",                                      "ResDHWSys",    "PumpEff",                                    TRUE  },
		{     10,              2,       "SysStoryCnt",                                  "ResDHWSys",    "SysStoryCnt",                                TRUE  },
		{     10,              2,       "LivingUnitCnt",                                "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "TotInpRating",                                 "ResDHWSys",    "TotInpRating",                               TRUE  },
		{     10,              2,       "TotTankVol",                                   "ResDHWSys",    "TotTankVol",                                 TRUE  },
		{     10,              2,       "BaseRecircWtrHtrRef",                          "ResDHWSys",    "BaseResWtrHtrRef",                           TRUE  },
		{     10,              2,       "UseDefaultLps",                                "ResDHWSys",    "UseDefaultLps",                              TRUE  },
		{     10,              2,       "PipeType",                                     "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "PipeLen",                                      "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "PipeDia",                                      "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "PipeLctn",                                     "ResDHWSys",    "PipeLctn",                                   TRUE  },
		{     10,              2,       "LpCnt",                                        "ResDHWSys",    "LpCnt",                                      TRUE  },
		{     10,              2,       "PipeExtraIns",                                 "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "AnnualSolFrac",                                "ResDHWSys",    "AnnualSolFrac",                              TRUE  },
		{     10,              2,       "Manufacturer",                                 "ResDHWSys",    "Manufacturer",                               TRUE  },
		{     10,              2,       "SolFracFluidSysName",                          "ResDHWSys",    "SolFracFluidSysName",                        TRUE  },
		{     10,              2,       "Brand",                                        "ResDHWSys",    "Brand",                                      TRUE  },
		{     10,              2,       "ModelNum",                                     "ResDHWSys",    "ModelNum",                                   TRUE  },
		{     10,              2,       "SRRCCertNum",                                  "ResDHWSys",    "SRRCCertNum",                                TRUE  },
		{     10,              2,       "CollectorType",                                "ResDHWSys",    "CollectorType",                              TRUE  },
		{     10,              2,       "Area",                                         "ResDHWSys",    "Area",                                       TRUE  },
		{     10,              2,       "RatedEffCurveSlope",                           "ResDHWSys",    "RatedEffCurveSlope",                         TRUE  },
		{     10,              2,       "RatedEffCurveIntercept",                       "ResDHWSys",    "RatedEffCurveIntercept",                     TRUE  },
		{     10,              2,       "SolCollectorCnt",                              "ResDHWSys",    "SolCollectorCnt",                            TRUE  },
		{     10,              2,       "Fluid",                                        "ResDHWSys",    "Fluid",                                      TRUE  },
		{     10,              2,       "AngleFromTrueNorth",                           "ResDHWSys",    "AngleFromTrueNorth",                         TRUE  },
		{     10,              2,       "SlopeFromHorizontal",                          "ResDHWSys",    "SlopeFromHorizontal",                        TRUE  },
		{     10,              2,       "NameOfProgramUsed",                            "ResDHWSys",    "NameOfProgramUsed",                          TRUE  },
		{     10,              2,       "Version",                                      "ResDHWSys",    "Version",                                    TRUE  },
		{     10,              2,       "WtrHtrTankVol",                                "ResDHWSys",    "WtrHtrTankVol",                              TRUE  },
		{     10,              2,       "SecondaryTankVol",                             "ResDHWSys",    "SecondaryTankVol",                           TRUE  },
		{     10,              2,       "NumOfIdenticalDwellingUnits",                  "ResDHWSys",    "NumOfIdenticalDwellingUnits",                TRUE  },
		{     10,              2,       "SolFracRpt",                                   "ResDHWSys",    "SolFracRpt",                                 TRUE  },
		{     10,              2,       "PlenumReport",                                 "ResDHWSys",    "PlenumReport",                               TRUE  },
		{     10,              2,       "OutsideReport",                                "ResDHWSys",    "OutsideReport",                              TRUE  },
		{     10,              2,       "BuriedReport",                                 "ResDHWSys",    "BuriedReport",                               TRUE  },
		{     10,              2,       "Multiplier",                                   "ResDHWSys",    "Multiplier",                                 TRUE  },
		{     10,              2,       "CentralSystem",                                "ResDHWSys",    "CentralSystem",                              TRUE  },
		{     10,              2,       "DistributionType",                             "ResDHWSys",    "DistributionType",                           TRUE  },
		{     10,              2,       "PumpPower",                                    "ResDHWSys",    "PumpPower",                                  TRUE  },
		{     10,              2,       "PumpEfficiency",                               "ResDHWSys",    "PumpEfficiency",                             TRUE  },
		{     10,              2,       "SystemStoryCount",                             "ResDHWSys",    "SystemStoryCount",                           TRUE  },
		{     10,              2,       "LivingUnitCount",                              "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "TotalInputRating",                             "ResDHWSys",    "TotalInputRating",                           TRUE  },
		{     10,              2,       "TotalTankVolume",                              "ResDHWSys",    "TotalTankVolume",                            TRUE  },
		{     10,              2,       "BaselineRecirculationWaterHeaterReference",    "ResDHWSys",    "BaselineResidentialWaterHeaterReference",    TRUE  },
		{     10,              2,       "UseDefaultLoops",                              "ResDHWSys",    "UseDefaultLoops",                            TRUE  },
		{     10,              2,       "PipeLength",                                   "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "PipeDiameter",                                 "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "PipeLocation",                                 "ResDHWSys",    "PipeLocation",                               TRUE  },
		{     10,              2,       "LoopCount",                                    "ResDHWSys",    "LoopCount",                                  TRUE  },
		{     10,              2,       "PipeExtraInsulation",                          "ResDHWSys",    "SysStoryCnt",                                FALSE  },
		{     10,              2,       "AnnualSolarFraction",                          "ResDHWSys",    "AnnualSolarFraction",                        TRUE  },
		{     10,              2,       "SolarFractionFluidSystemName",                 "ResDHWSys",    "SolarFractionFluidSystemName",               TRUE  },
		{     10,              2,       "ModelNumber",                                  "ResDHWSys",    "ModelNumber",                                TRUE  },
		{     10,              2,       "SRRCCertificationNumber",                      "ResDHWSys",    "SRRCCertificationNumber",                    TRUE  },
		{     10,              2,       "RatedEfficiencyCurveSlope",                    "ResDHWSys",    "RatedEfficiencyCurveSlope",                  TRUE  },
		{     10,              2,       "RatedEfficiencyCurveIntercept",                "ResDHWSys",    "RatedEfficiencyCurveIntercept",              TRUE  },
		{     10,              2,       "SolarCollectorCount",                          "ResDHWSys",    "SolarCollectorCount",                        TRUE  },
		{     10,              2,       "WaterHeaterTankVolume",                        "ResDHWSys",    "WaterHeaterTankVolume",                      TRUE  },
		{     10,              2,       "SecondaryTankVolume",                          "ResDHWSys",    "SecondaryTankVolume",                        TRUE  },
		{     10,              2,       "NumberOfIdenticalDwellingUnits",               "ResDHWSys",    "NumberOfIdenticalDwellingUnits",             TRUE  },
		{     10,              2,       "SolarFractionReport",                          "ResDHWSys",    "SolarFractionReport",                        TRUE  },
		{     10,              3,       "Status",                                       "ResidentialDHWSystem",    "Status",                                     TRUE  },
		{     10,              3,       "Type",                                         "ResidentialDHWSystem",    "Type",                                       TRUE  },
		{     10,              3,       "Mult",                                         "ResidentialDHWSystem",    "Mult",                                       TRUE  },
		{     10,              3,       "CentralSys",                                   "ResidentialDHWSystem",    "CentralSys",                                 TRUE  },
		{     10,              3,       "DistType",                                     "ResidentialDHWSystem",    "DistType",                                   TRUE  },
		{     10,              3,       "PumpPwr",                                      "ResidentialDHWSystem",    "PumpPwr",                                    TRUE  },
		{     10,              3,       "PumpEff",                                      "ResidentialDHWSystem",    "PumpEff",                                    TRUE  },
		{     10,              3,       "SysStoryCnt",                                  "ResidentialDHWSystem",    "SysStoryCnt",                                TRUE  },
		{     10,              3,       "LivingUnitCnt",                                "ResidentialDHWSystem",    "SysStoryCnt",                                FALSE  },
		{     10,              3,       "TotInpRating",                                 "ResidentialDHWSystem",    "TotInpRating",                               TRUE  },
		{     10,              3,       "TotTankVol",                                   "ResidentialDHWSystem",    "TotTankVol",                                 TRUE  },
		{     10,              3,       "BaseRecircWtrHtrRef",                          "ResidentialDHWSystem",    "BaseRecircWtrHtrRef",                        TRUE  },
		{     10,              3,       "UseDefaultLps",                                "ResidentialDHWSystem",    "UseDefaultLps",                              TRUE  },
		{     10,              3,       "PipeType",                                     "ResidentialDHWSystem",    "SysStoryCnt",                                FALSE  },
		{     10,              3,       "PipeLen",                                      "ResidentialDHWSystem",    "SysStoryCnt",                                FALSE  },
		{     10,              3,       "PipeDia",                                      "ResidentialDHWSystem",    "SysStoryCnt",                                FALSE  },
		{     10,              3,       "PipeLctn",                                     "ResidentialDHWSystem",    "PipeLctn",                                   TRUE  },
		{     10,              3,       "LpCnt",                                        "ResidentialDHWSystem",    "LpCnt",                                      TRUE  },
		{     10,              3,       "PipeExtraIns",                                 "ResidentialDHWSystem",    "SysStoryCnt",                                FALSE  },
		{     10,              3,       "AnnualSolFrac",                                "ResidentialDHWSystem",    "AnnualSolFrac",                              TRUE  },
		{     10,              3,       "Manufacturer",                                 "ResidentialDHWSystem",    "Manufacturer",                               TRUE  },
		{     10,              3,       "SolFracFluidSysName",                          "ResidentialDHWSystem",    "SolFracFluidSysName",                        TRUE  },
		{     10,              3,       "Brand",                                        "ResidentialDHWSystem",    "Brand",                                      TRUE  },
		{     10,              3,       "ModelNum",                                     "ResidentialDHWSystem",    "ModelNum",                                   TRUE  },
		{     10,              3,       "SRRCCertNum",                                  "ResidentialDHWSystem",    "SRRCCertNum",                                TRUE  },
		{     10,              3,       "CollectorType",                                "ResidentialDHWSystem",    "CollectorType",                              TRUE  },
		{     10,              3,       "Area",                                         "ResidentialDHWSystem",    "Area",                                       TRUE  },
		{     10,              3,       "RatedEffCurveSlope",                           "ResidentialDHWSystem",    "RatedEffCurveSlope",                         TRUE  },
		{     10,              3,       "RatedEffCurveIntercept",                       "ResidentialDHWSystem",    "RatedEffCurveIntercept",                     TRUE  },
		{     10,              3,       "SolCollectorCnt",                              "ResidentialDHWSystem",    "SolCollectorCnt",                            TRUE  },
		{     10,              3,       "Fluid",                                        "ResidentialDHWSystem",    "Fluid",                                      TRUE  },
		{     10,              3,       "AngleFromTrueNorth",                           "ResidentialDHWSystem",    "AngleFromTrueNorth",                         TRUE  },
		{     10,              3,       "SlopeFromHorizontal",                          "ResidentialDHWSystem",    "SlopeFromHorizontal",                        TRUE  },
		{     10,              3,       "NameOfProgramUsed",                            "ResidentialDHWSystem",    "NameOfProgramUsed",                          TRUE  },
		{     10,              3,       "Version",                                      "ResidentialDHWSystem",    "Version",                                    TRUE  },
		{     10,              3,       "WtrHtrTankVol",                                "ResidentialDHWSystem",    "WtrHtrTankVol",                              TRUE  },
		{     10,              3,       "SecondaryTankVol",                             "ResidentialDHWSystem",    "SecondaryTankVol",                           TRUE  },
		{     10,              3,       "NumOfIdenticalDwellingUnits",                  "ResidentialDHWSystem",    "NumOfIdenticalDwellingUnits",                TRUE  },
		{     10,              3,       "SolFracRpt",                                   "ResidentialDHWSystem",    "SolFracRpt",                                 TRUE  },
		{     10,              3,       "PlenumReport",                                 "ResidentialDHWSystem",    "PlenumReport",                               TRUE  },
		{     10,              3,       "OutsideReport",                                "ResidentialDHWSystem",    "OutsideReport",                              TRUE  },
		{     10,              3,       "BuriedReport",                                 "ResidentialDHWSystem",    "BuriedReport",                               TRUE  },
		{     10,              3,       "Multiplier",                                   "ResidentialDHWSystem",    "Multiplier",                                 TRUE  },
		{     10,              3,       "CentralSystem",                                "ResidentialDHWSystem",    "CentralSystem",                              TRUE  },
		{     10,              3,       "DistributionType",                             "ResidentialDHWSystem",    "DistributionType",                           TRUE  },
		{     10,              3,       "PumpPower",                                    "ResidentialDHWSystem",    "PumpPower",                                  TRUE  },
		{     10,              3,       "PumpEfficiency",                               "ResidentialDHWSystem",    "PumpEfficiency",                             TRUE  },
		{     10,              3,       "SystemStoryCount",                             "ResidentialDHWSystem",    "SystemStoryCount",                           TRUE  },
		{     10,              3,       "LivingUnitCount",                              "ResidentialDHWSystem",    "LivingUnitCount",                            TRUE  },
		{     10,              3,       "TotalInputRating",                             "ResidentialDHWSystem",    "TotalInputRating",                           TRUE  },
		{     10,              3,       "TotalTankVolume",                              "ResidentialDHWSystem",    "TotalTankVolume",                            TRUE  },
		{     10,              3,       "BaselineRecirculationWaterHeaterReference",    "ResidentialDHWSystem",    "BaselineRecirculationWaterHeaterReference",  TRUE  },
		{     10,              3,       "UseDefaultLoops",                              "ResidentialDHWSystem",    "UseDefaultLoops",                            TRUE  },
		{     10,              3,       "PipeLength",                                   "ResidentialDHWSystem",    "PipeLength",                                 TRUE  },
		{     10,              3,       "PipeDiameter",                                 "ResidentialDHWSystem",    "PipeDiameter",                               TRUE  },
		{     10,              3,       "PipeLocation",                                 "ResidentialDHWSystem",    "PipeLocation",                               TRUE  },
		{     10,              3,       "LoopCount",                                    "ResidentialDHWSystem",    "LoopCount",                                  TRUE  },
		{     10,              3,       "PipeExtraInsulation",                          "ResidentialDHWSystem",    "PipeExtraInsulation",                        TRUE  },
		{     10,              3,       "AnnualSolarFraction",                          "ResidentialDHWSystem",    "AnnualSolarFraction",                        TRUE  },
		{     10,              3,       "SolarFractionFluidSystemName",                 "ResidentialDHWSystem",    "SolarFractionFluidSystemName",               TRUE  },
		{     10,              3,       "ModelNumber",                                  "ResidentialDHWSystem",    "ModelNumber",                                TRUE  },
		{     10,              3,       "SRRCCertificationNumber",                      "ResidentialDHWSystem",    "SRRCCertificationNumber",                    TRUE  },
		{     10,              3,       "RatedEfficiencyCurveSlope",                    "ResidentialDHWSystem",    "RatedEfficiencyCurveSlope",                  TRUE  },
		{     10,              3,       "RatedEfficiencyCurveIntercept",                "ResidentialDHWSystem",    "RatedEfficiencyCurveIntercept",              TRUE  },
		{     10,              3,       "SolarCollectorCount",                          "ResidentialDHWSystem",    "SolarCollectorCount",                        TRUE  },
		{     10,              3,       "WaterHeaterTankVolume",                        "ResidentialDHWSystem",    "WaterHeaterTankVolume",                      TRUE  },
		{     10,              3,       "SecondaryTankVolume",                          "ResidentialDHWSystem",    "SecondaryTankVolume",                        TRUE  },
		{     10,              3,       "NumberOfIdenticalDwellingUnits",               "ResidentialDHWSystem",    "NumberOfIdenticalDwellingUnits",             TRUE  },
		{     10,              3,       "SolarFractionReport",                          "ResidentialDHWSystem",    "SolarFractionReport",                        TRUE  },
	// iVersionCutoff    iCompTypeID   szOldPropType                                   szNewCompType   szNewPropType                           bPostMappedData
      {     10,              2,       "RecircPumpPwr",                                "ResDHWSys",    "PumpPwr",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPumpHP",                                 "ResDHWSys",    "PumpHP",                             TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPumpEff",                                "ResDHWSys",    "PumpEff",                            TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircSysStoryCnt",                            "ResDHWSys",    "SysStoryCnt",                        TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircLivingUnitCnt",                          "ResDHWSys",    "SysStoryCnt",                        FALSE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircSysFlrArea",                             "ResDHWSys",    "SysFlrArea",                         TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircWtrHtrCnt",                              "ResDHWSys",    "WtrHtrCnt",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeLen",                                "ResDHWSys",    "SysStoryCnt",                        FALSE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeDia",                                "ResDHWSys",    "SysStoryCnt",                        FALSE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeLctn",                               "ResDHWSys",    "PipeLctn",                           TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircLpCnt",                                  "ResDHWSys",    "LpCnt",                              TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeExtraIns",                           "ResDHWSys",    "SysStoryCnt",                        FALSE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationPumpPower",                       "ResDHWSys",    "PumpPower",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationPumpHorsepower",                  "ResDHWSys",    "PumpHorsepower",                     TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationPumpEfficiency",                  "ResDHWSys",    "PumpEfficiency",                     TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationSystemStoryCount",                "ResDHWSys",    "SystemStoryCount",                   TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationLivingUnitCount",                 "ResDHWSys",    "LivingUnitCount",                    TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationSystemFloorArea",                 "ResDHWSys",    "SystemFloorArea",                    TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationWaterHeaterCount",                "ResDHWSys",    "WaterHeaterCount",                   TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeLength",                             "ResDHWSys",    "PipeLength",                         TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeDiameter",                           "ResDHWSys",    "PipeDiameter",                       TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecircPipeLocation",                           "ResDHWSys",    "PipeLocation",                       TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationLoopCount",                       "ResDHWSys",    "LoopCount",                          TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
      {     10,              2,       "RecirculationPipeExtraInsulation",             "ResDHWSys",    "PipeExtraInsulation",                TRUE         },     // SAC 1/28/14 - NewProp supplied simply to identify type of data expected - input from file to be ignored
	// iVersionCutoff    iCompTypeID   szOldPropType                                   szNewCompType   szNewPropType                           bPostMappedData
		{     10,              4,       "Status",                                       "ResWtrHtr",    "Status",                                     TRUE  },
		{     10,              4,       "ElementType",                                  "ResWtrHtr",    "ElementType",                                TRUE  },
		{     10,              4,       "TankCat",                                      "ResWtrHtr",    "TankCat",                                    TRUE  },
		{     10,              4,       "TankType",                                     "ResWtrHtr",    "TankType",                                   TRUE  },
		{     10,              4,       "InpRating",                                    "ResWtrHtr",    "InpRating",                                  TRUE  },
		{     10,              4,       "EngyFac",                                      "ResWtrHtr",    "EngyFac",                                    TRUE  },
		{     10,              4,       "TankVol",                                      "ResWtrHtr",    "TankVol",                                    TRUE  },
		{     10,              4,       "TankIntInsR",                                  "ResWtrHtr",    "TankIntInsR",                                TRUE  },
		{     10,              4,       "TankExtInsR",                                  "ResWtrHtr",    "TankExtInsR",                                TRUE  },
		{     10,              4,       "AmbCond",                                      "ResWtrHtr",    "AmbCond",                                    TRUE  },
		{     10,              4,       "StdbyLossFrac",                                "ResWtrHtr",    "StdbyLossFrac",                              TRUE  },
		{     10,              4,       "ThrmlEff",                                     "ResWtrHtr",    "ThrmlEff",                                   TRUE  },
		{     10,              4,       "Cnt",                                          "ResWtrHtr",    "Cnt",                                        TRUE  },
		{     10,              4,       "TankCategory",                                 "ResWtrHtr",    "TankCategory",                               TRUE  },
		{     10,              4,       "InputRating",                                  "ResWtrHtr",    "InputRating",                                TRUE  },
		{     10,              4,       "EnergyFactor",                                 "ResWtrHtr",    "EnergyFactor",                               TRUE  },
		{     10,              4,       "TankVolume",                                   "ResWtrHtr",    "TankVolume",                                 TRUE  },
		{     10,              4,       "TankInteriorInsulationRValue",                 "ResWtrHtr",    "TankInteriorInsulationRValue",               TRUE  },
		{     10,              4,       "TankExteriorInsulationRValue",                 "ResWtrHtr",    "TankExteriorInsulationRValue",               TRUE  },
		{     10,              4,       "AmbientCondition",                             "ResWtrHtr",    "AmbientCondition",                           TRUE  },
		{     10,              4,       "StandbyLossFraction",                          "ResWtrHtr",    "StandbyLossFraction",                        TRUE  },
		{     10,              4,       "ThermalEfficiency",                            "ResWtrHtr",    "ThermalEfficiency",                          TRUE  },
		{     10,              4,       "Count",                                        "ResWtrHtr",    "Count",                                      TRUE  },
		{     10,              5,       "Status",                                       "ResidentialWaterHeater",    "Status",                        TRUE  },
		{     10,              5,       "ElementType",                                  "ResidentialWaterHeater",    "ElementType",                   TRUE  },
		{     10,              5,       "TankCat",                                      "ResidentialWaterHeater",    "TankCat",                       TRUE  },
		{     10,              5,       "TankType",                                     "ResidentialWaterHeater",    "TankType",                      TRUE  },
		{     10,              5,       "InpRating",                                    "ResidentialWaterHeater",    "InpRating",                     TRUE  },
		{     10,              5,       "EngyFac",                                      "ResidentialWaterHeater",    "EngyFac",                       TRUE  },
		{     10,              5,       "TankVol",                                      "ResidentialWaterHeater",    "TankVol",                       TRUE  },
		{     10,              5,       "TankIntInsR",                                  "ResidentialWaterHeater",    "TankIntInsR",                   TRUE  },
		{     10,              5,       "TankExtInsR",                                  "ResidentialWaterHeater",    "TankExtInsR",                   TRUE  },
		{     10,              5,       "AmbCond",                                      "ResidentialWaterHeater",    "AmbCond",                       TRUE  },
		{     10,              5,       "StdbyLossFrac",                                "ResidentialWaterHeater",    "StdbyLossFrac",                 TRUE  },
		{     10,              5,       "ThrmlEff",                                     "ResidentialWaterHeater",    "ThrmlEff",                      TRUE  },
		{     10,              5,       "Cnt",                                          "ResidentialWaterHeater",    "Cnt",                           TRUE  },
		{     10,              5,       "TankCategory",                                 "ResidentialWaterHeater",    "TankCategory",                  TRUE  },
		{     10,              5,       "InputRating",                                  "ResidentialWaterHeater",    "InputRating",                   TRUE  },
		{     10,              5,       "EnergyFactor",                                 "ResidentialWaterHeater",    "EnergyFactor",                  TRUE  },
		{     10,              5,       "TankVolume",                                   "ResidentialWaterHeater",    "TankVolume",                    TRUE  },
		{     10,              5,       "TankInteriorInsulationRValue",                 "ResidentialWaterHeater",    "TankInteriorInsulationRValue",  TRUE  },
		{     10,              5,       "TankExteriorInsulationRValue",                 "ResidentialWaterHeater",    "TankExteriorInsulationRValue",  TRUE  },
		{     10,              5,       "AmbientCondition",                             "ResidentialWaterHeater",    "AmbientCondition",              TRUE  },
		{     10,              5,       "StandbyLossFraction",                          "ResidentialWaterHeater",    "StandbyLossFraction",           TRUE  },
		{     10,              5,       "ThermalEfficiency",                            "ResidentialWaterHeater",    "ThermalEfficiency",             TRUE  },
		{     10,              5,       "Count",                                        "ResidentialWaterHeater",    "Count",                         TRUE  },
	 // end of list
		{ 0, 0, NULL, NULL, NULL } };

#else						// => CEC Res -------------------------------

BEMStraightMap sbemStraightMap[] = {
	// iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
		{      1,       "DHWSysRpt",         "DHWHeater",                         "DHWHeaterRef",                       TRUE         },     // SAC 4/9/14
		{      1,       "IAQVentRpt",        "IAQFan",                            "IAQFanRef",                          TRUE         },     // SAC 4/9/14
		{      1,       "Proj",              "NumMech1HVACEquipUnits",            "NumSCSysEquipUnits",                 TRUE         },     // SAC 4/21/14
	// iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
		{      2,       "HVACDist",          "LowLeakageVal",                     "DuctLeakageVal",                     TRUE         },     // SAC 5/4/14
		{      2,       "Zone",              "WinHHTop",                          "WinHHTopUse",                        FALSE        },     // SAC 5/4/14
		{      2,       "HVACDist",          "DuctInsRvalue",                     "DuctDesignInsRvalue",                TRUE         },     // SAC 5/7/14
		{      2,       "HVACDist",          "RetDuctInsRvalue",                  "RetDuctDesignInsRvalue",             TRUE         },     // SAC 5/7/14
	// iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData
		{      4,       "UndFloor",          "Construction",                      "Surface",                            FALSE        },     // SAC 11/21/14
		{      4,       "UndFloor",          "exConstruction",                    "Surface",                            FALSE        },     // SAC 11/21/14
	 // end of list
		{ 0, NULL, NULL, NULL, FALSE } };

BEMStraightMap sbemIgnorNewlyNotInputProperties[] = {
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData - in this case used to indicate that a reset should be reported
     {      4,         "HVACFan",           "IsVerified",                        "none",                              FALSE        },     // SAC 8/24/14
     {      4,         "HVACFan",           "Status",                            "none",                              FALSE        },     // SAC 8/24/14
     {      4,         "UndFloor",          "FloorZ",                            "none",                              FALSE        },     // SAC 11/21/14
   // iVersionCutoff   szClassName          szOldPropType                        szNewPropType                       bPostMappedData - in this case used to indicate that a reset should be reported
     {      5,         "Win",               "VentArea",                          "none",                              FALSE        },     // SAC 12/15/14	SAC 1/12/15 - reset ver cutoff to 1 to ensure older files adjusted as well
     {      5,         "HVACSys",           "HtSysAFUE",                         "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "HtSysSizingFactor",                 "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "HtSysCapacity",                     "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysSEER",                         "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysEER",                          "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysCFMperTon",                    "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysRefrigChgAdjFctr",             "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysSizingFactor",                 "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "ClSysCapacity",                     "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "HPSysHSPF",                         "none",                              FALSE        },     // SAC 1/12/15
     {      5,         "HVACSys",           "HPSysAuxHtgCap",                    "none",                              FALSE        },     // SAC 1/12/15
                                                                  { 0, NULL, NULL, NULL, FALSE } };

BEMComponentMap sbemComponentMap[] = {
	// iVersionCutoff    iCompTypeID   szOldCompType   szNewCompType[5]
		{      1,              1,       "MECH1",        { "SCSysRpt", NULL, NULL, NULL, NULL } },
	 // end of list
		{ 0, 0, NULL, { NULL, NULL, NULL, NULL, NULL } } };

BEMPropertyMap sbemPropertyMap[] = {
	// iVersionCutoff    iCompTypeID   szOldPropType            szNewCompType   szNewPropType          bPostMappedData
		{      1,              1,       "HVACSysName",           "SCSysRpt",     "SCSysName",               TRUE  },
		{      1,              1,       "DwellingUnit",          "SCSysRpt",     "DwellingUnit",            TRUE  },
		{      1,              1,       "HVACSysType",           "SCSysRpt",     "SCSysType",               TRUE  },
		{      1,              1,       "HeatingType",           "SCSysRpt",     "HeatingType",             TRUE  },
		{      1,              1,       "HeatSysName",           "SCSysRpt",     "HeatSysName",             TRUE  },
		{      1,              1,       "CoolingType",           "SCSysRpt",     "CoolingType",             TRUE  },
		{      1,              1,       "CoolSysName",           "SCSysRpt",     "CoolSysName",             TRUE  },
		{      1,              1,       "FanType",               "SCSysRpt",     "FanType",                 TRUE  },
		{      1,              1,       "DistribType",           "SCSysRpt",     "DistribType",             TRUE  },
		{      1,              1,       "TStatType",             "SCSysRpt",     "TStatType",               TRUE  },
		{      1,              1,       "LLAHUStatus",           "SCSysRpt",     "LLAHUStatus",             TRUE  },
		{      1,              1,       "BypassDuctStatus",      "SCSysRpt",     "BypassDuctStatus",        TRUE  },
		{      1,              1,       "ZonalCoolingType",      "SCSysRpt",     "ZonalCoolingType",        TRUE  },
		{      1,              1,       "CoolCompType",          "SCSysRpt",     "CoolCompType",            TRUE  },
		{      1,              1,       "HeatEfficType",         "SCSysRpt",     "HeatEfficType",           TRUE  },
		{      1,              1,       "MinHeatEffic",          "SCSysRpt",     "MinHeatEffic",            TRUE  },
		{      1,              1,       "MinCoolEER",            "SCSysRpt",     "MinCoolEER",              TRUE  },
		{      1,              1,       "MinCoolSEER",           "SCSysRpt",     "MinCoolSEER",             TRUE  },
		{      1,              1,       "HtPumpCap17",           "SCSysRpt",     "HtPumpCap17",             TRUE  },
		{      1,              1,       "HtPumpCap47",           "SCSysRpt",     "HtPumpCap47",             TRUE  },
		{      1,              1,       "MinCoolCFMperTon",      "SCSysRpt",     "MinCoolCFMperTon",        TRUE  },
		{      1,              1,       "MinDistribInsRval",     "SCSysRpt",     "MinDistribInsRval",       TRUE  },
		{      1,              1,       "HeatSystem",            "SCSysRpt",     "HeatSystem",              TRUE  },
		{      1,              1,       "HeatSysUnitTypeIdx",    "SCSysRpt",     "HeatSysUnitTypeIdx",      TRUE  },
		{      1,              1,       "HeatSysUnitTypeCnt",    "SCSysRpt",     "HeatSysUnitTypeCnt",      TRUE  },
		{      1,              1,       "CoolSystem",            "SCSysRpt",     "CoolSystem",              TRUE  },
		{      1,              1,       "CoolSysUnitTypeIdx",    "SCSysRpt",     "CoolSysUnitTypeIdx",      TRUE  },
		{      1,              1,       "CoolSysUnitTypeCnt",    "SCSysRpt",     "CoolSysUnitTypeCnt",      TRUE  },
		{      1,              1,       "HtPumpSystem",          "SCSysRpt",     "HtPumpSystem",            TRUE  },
		{      1,              1,       "HtPumpSysUnitTypeIdx",  "SCSysRpt",     "HtPumpSysUnitTypeIdx",    TRUE  },
		{      1,              1,       "HtPumpSysUnitTypeCnt",  "SCSysRpt",     "HtPumpSysUnitTypeCnt",    TRUE  },
		{      1,              1,       "HVACSysTypeVal",        "SCSysRpt",     "SCSysTypeVal",            TRUE  },
		{      1,              1,       "HERSAHUAirFlow",        "SCSysRpt",     "HERSAHUAirFlow",          TRUE  },
		{      1,              1,       "HERSAirFlowRptMsg",     "SCSysRpt",     "HERSAirFlowRptMsg",       TRUE  },
		{      1,              1,       "HERSEER",               "SCSysRpt",     "HERSEER",                 TRUE  },
		{      1,              1,       "HERSEERRptMsg",         "SCSysRpt",     "HERSEERRptMsg",           TRUE  },
		{      1,              1,       "HERSSEER",              "SCSysRpt",     "HERSSEER",                TRUE  },
		{      1,              1,       "HERSSEERRptMsg",        "SCSysRpt",     "HERSSEERRptMsg",          TRUE  },
		{      1,              1,       "HERSACCharg",           "SCSysRpt",     "HERSACCharg",             TRUE  },
		{      1,              1,       "HERSACChargRptMsg",     "SCSysRpt",     "HERSACChargRptMsg",       TRUE  },
		{      1,              1,       "HERSDuctLeakage",       "SCSysRpt",     "HERSDuctLeakage",         TRUE  },
		{      1,              1,       "HERSDuctLkgRptMsg",     "SCSysRpt",     "HERSDuctLkgRptMsg",       TRUE  },
		{      1,              1,       "HERSDuctLocation",      "SCSysRpt",     "HERSDuctLocation",        TRUE  },
		{      1,              1,       "HERSDuctLocRptMsg",     "SCSysRpt",     "HERSDuctLocRptMsg",       TRUE  },
		{      1,              1,       "HERSRetDuctDesign",     "SCSysRpt",     "HERSRetDuctDesign",       TRUE  },
		{      1,              1,       "HERSRetDuctRptMsg",     "SCSysRpt",     "HERSRetDuctRptMsg",       TRUE  },
		{      1,              1,       "HERSSupDuctDesign",     "SCSysRpt",     "HERSSupDuctDesign",       TRUE  },
		{      1,              1,       "HERSSupDuctRptMsg",     "SCSysRpt",     "HERSSupDuctRptMsg",       TRUE  },
		{      1,              1,       "HERSAirFilterDesign",   "SCSysRpt",     "HERSAirFilterDesign",     TRUE  },
		{      1,              1,       "HERSAirFltrRptMsg",     "SCSysRpt",     "HERSAirFltrRptMsg",       TRUE  },
	 // end of list
		{ 0, 0, NULL, NULL, NULL } };

#endif


// SAC 1/27/14 - 
int CMX_LoadModel( const char* pszBEMBinPathFile, const char* pszRulesetPathFile, const char* pszModelPathFile, 
										int iMaxDBIDSetFailures /*=0*/, int* piDBIDSetFailures /*=NULL*/, bool bSupressAllMsgBoxes /*=false*/,
										int* piObjIdxSetFailures /*=NULL*/, QStringList* psaDataSetFailures /*=NULL*/, bool bLogDurations /*=false*/,
										const char* pszLogPathFile /*=NULL*/, bool bKeepLogFileOpen /*=false*/, QStringList* psaWarningsForUser /*=NULL*/, bool bCalledFromUI /*=false*/ )
{
	int iRetVal = 0;
	QString sBEMBinFile  = pszBEMBinPathFile;
	QString sRulesetFile = pszRulesetPathFile;
	QString sInputFile   = pszModelPathFile;
	QString sInpPath, sInpExt;
	if (sInputFile.isEmpty() || !FileExists( pszModelPathFile ))
		iRetVal = 1;	// no or missing input file
	else if (!sBEMBinFile.isEmpty() && !FileExists( pszBEMBinPathFile ))
		iRetVal = 2;	// BEMBin file specified, but not found
	else if (!sRulesetFile.isEmpty() && !FileExists( pszRulesetPathFile ))
		iRetVal = 3;	// Ruleset file specified, but not found
	else
	{
		int iLastSlashIdx = std::max( sInputFile.lastIndexOf('\\'), sInputFile.lastIndexOf('/') );;
		int iLastDotIdx = sInputFile.lastIndexOf('.');
		if (iLastSlashIdx > 0)
			sInpPath = sInputFile.left( iLastSlashIdx + 1 );
		if (iLastDotIdx > 0)
			sInpExt = sInputFile.right( sInputFile.length() - iLastDotIdx - 1 );

		if (!sBEMBinFile.isEmpty())
		{
			if (BEMPX_CheckDataModelBin( sBEMBinFile.toLocal8Bit().constData() ) != 0 ||		// SAC 1/3/17
	// don't pass target log filename to BEMPX_LoadDataModel() or it will get overwritten (blasted) during the BEM initialization
			    !BEMPX_LoadDataModel( sBEMBinFile.toLocal8Bit().constData(), BEMT_CBECC ))
				iRetVal = 4;	// initialization of BEM failed
	}	}

	if (iRetVal == 0 && !sRulesetFile.isEmpty() && !CMX_LoadRuleset( sRulesetFile.toLocal8Bit().constData(), TRUE /*bDeleteAllObjects*/ ))
		iRetVal = 5;	// error loading ruleset file

	if (iRetVal == 0)
	{	
// SAC 5/19/14 - mods to enable log files to be kept open for duration of project being opened/processed
		if (bKeepLogFileOpen)
		{	QString sLogFN;
			if (pszLogPathFile && strlen(pszLogPathFile) > 0)
				sLogFN = pszLogPathFile;
			else
			{	int iLastDot = sInputFile.lastIndexOf('.');
				sLogFN = (iLastDot > 0 ? sInputFile.left( iLastDot ) : sInputFile);
				sLogFN += ".log";
			}
			BEMPX_OpenLogFile( sLogFN.toLocal8Bit().constData() );
		}

		long lDBID_Proj_BEMVersion = BEMPX_GetDatabaseID( "BEMVersion", 1 /*eiBDBCID_Proj*/ );
		if (lDBID_Proj_BEMVersion < 1)
			lDBID_Proj_BEMVersion = BEMPX_GetDatabaseID( "BldgEngyModelVersion", 1 /*eiBDBCID_Proj*/ );  // same property, but using std non-res SDD abbreviations
		if (!BEMPX_ReadProjectFile( sInputFile.toLocal8Bit().constData(), BEMFM_INPUT /*iFileMode*/, false /*bRestore*/, false /*bResultsOnly*/,			// Load building model
												pszLogPathFile /*pszLogFileExt*/, 0 /*iBEMProcIdx*/, lDBID_Proj_BEMVersion,
												iMaxDBIDSetFailures, piDBIDSetFailures, sbemStraightMap /*BEMStraightMap* pStraightMap*/, sbemComponentMap /*BEMComponentMap* pCompMap*/,
												sbemPropertyMap /*BEMPropertyMap* pPropMap*/, bSupressAllMsgBoxes, piObjIdxSetFailures, psaDataSetFailures, bLogDurations ) )
			iRetVal = 6;	// error loading building model file
		else
		{	int iError;		QString sWarnMsg, sWarnTmp;
			long lBEMVersion=0;
			if (lDBID_Proj_BEMVersion > 0)
				BEMPX_GetInteger( lDBID_Proj_BEMVersion, lBEMVersion );

		// SAC 8/7/14 - added code to blast certain properties that are switched from some user input type to NotInput - in which case we simply blast the input
			int iINNI = -1;
			while (sbemIgnorNewlyNotInputProperties[++iINNI].szOldPropType != NULL)
				if (sbemIgnorNewlyNotInputProperties[iINNI].iVersionCutoff >= lBEMVersion)
				{	int iINNI_CID = BEMPX_GetDBComponentID( sbemIgnorNewlyNotInputProperties[iINNI].szClassName );
					int iNumINNIObjs = BEMPX_GetNumObjects( iINNI_CID );
					long lINNI_DBID = BEMPX_GetDatabaseID( sbemIgnorNewlyNotInputProperties[iINNI].szOldPropType, iINNI_CID );				assert( lINNI_DBID > 0 );
					for (int iINNIObjIdx=0; (lINNI_DBID > 0 && iINNIObjIdx < iNumINNIObjs); iINNIObjIdx++)
					{	int iINNIstatus = BEMPX_GetDataStatus( lINNI_DBID, iINNIObjIdx );
						if (iINNIstatus >= BEMS_UserDefault && iINNIstatus <= BEMS_UserDefined)
						{	bool bReport = sbemIgnorNewlyNotInputProperties[iINNI].bPostMappedData;
							if (bReport)
							{	long lRedirectDBID = 0;
								bReport = (strcmp( sbemIgnorNewlyNotInputProperties[iINNI].szNewPropType, "none" )==0);
								if (!bReport)
									lRedirectDBID = BEMPX_GetDatabaseID( sbemIgnorNewlyNotInputProperties[iINNI].szNewPropType, iINNI_CID );
								if (lRedirectDBID > 0)
								{	// COPY user-supplied data to different property of same object
									BEMPropertyType* pOldPropType = BEMPX_GetPropertyTypeFromDBID( lINNI_DBID, iError );			assert( pOldPropType );
									if (pOldPropType)
									{	switch (pOldPropType->getPropType())
										{	case  BEMP_Flt :	{	double fData;
																		BEMPX_GetFloat(  lINNI_DBID, fData, 0, -1, iINNIObjIdx );
																		BEMPX_SetBEMData( lRedirectDBID, BEMP_Flt, &fData, BEMO_User, iINNIObjIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
																	}	break;
											case  BEMP_Int :	{	long lData;
																		BEMPX_GetInteger( lINNI_DBID, lData, 0, -1, iINNIObjIdx );
																		BEMPX_SetBEMData(  lRedirectDBID, BEMP_Int, &lData, BEMO_User, iINNIObjIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
																	}	break;
											default        :	{	QString sData;
																		BEMPX_GetString( lINNI_DBID, sData, TRUE, 0, -1, iINNIObjIdx );
																		BEMPX_SetBEMData(  lRedirectDBID, BEMP_Str, (void*) sData.toLocal8Bit().constData(), BEMO_User, iINNIObjIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
																	}	break;
									}	}
									bReport = false;
							}	}

							if (psaWarningsForUser && bReport)	// only report certain reset properties
							{	// REPORT property being blasted
								if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iINNI_CID ), sWarnTmp, FALSE, 0, -1, iINNIObjIdx ) || sWarnTmp.isEmpty())
									sWarnTmp = "(unknown)";
								sWarnMsg = QString( "Backward compatibility note:  %1 '%2' has a user-defined property '%3' defined that is being re-defaulted." ).arg(
														sbemIgnorNewlyNotInputProperties[iINNI].szClassName, sWarnTmp, sbemIgnorNewlyNotInputProperties[iINNI].szOldPropType );
								psaWarningsForUser->push_back( sWarnMsg );
							}
							BEMPX_DefaultProperty( lINNI_DBID, iError, iINNIObjIdx );
				}	}	}


#ifdef OSWRAPPER		// => CEC Non-Res ---------------------------
			double fData;		int iStatus, iSpecialVal;
	// code to switch Spc:FlrArea -> Area  -- 3/15/14
	// added code to copy user-defined values for Spc:xxxDayltgCtrlLtgPwr into new (somewhat redundent) Spc:xxxDayltgInstalledLtgPwr properties
			int iCID_Spc = BEMPX_GetDBComponentID( "Spc" );										assert( iCID_Spc > 0 );
			long lDBID_Spc_FlrArea = BEMPX_GetDatabaseID( "FlrArea", iCID_Spc );			assert( lDBID_Spc_FlrArea > 0 );
			long lDBID_Spc_Area    = BEMPX_GetDatabaseID( "Area",    iCID_Spc );			assert( lDBID_Spc_Area    > 0 );
			long lDBID_Spc_SkylitDayltgCtrlLtgPwr       = BEMPX_GetDatabaseID( "SkylitDayltgCtrlLtgPwr",       iCID_Spc );			assert( lDBID_Spc_SkylitDayltgCtrlLtgPwr > 0 );
			long lDBID_Spc_PriSideDayltgCtrlLtgPwr      = BEMPX_GetDatabaseID( "PriSideDayltgCtrlLtgPwr",      iCID_Spc );			assert( lDBID_Spc_PriSideDayltgCtrlLtgPwr > 0 );
			long lDBID_Spc_SecSideDayltgCtrlLtgPwr      = BEMPX_GetDatabaseID( "SecSideDayltgCtrlLtgPwr",      iCID_Spc );			assert( lDBID_Spc_SecSideDayltgCtrlLtgPwr > 0 );
			long lDBID_Spc_SkylitDayltgInstalledLtgPwr  = BEMPX_GetDatabaseID( "SkylitDayltgInstalledLtgPwr",  iCID_Spc );			assert( lDBID_Spc_SkylitDayltgInstalledLtgPwr > 0 );
			long lDBID_Spc_PriSideDayltgInstalledLtgPwr = BEMPX_GetDatabaseID( "PriSideDayltgInstalledLtgPwr", iCID_Spc );			assert( lDBID_Spc_PriSideDayltgInstalledLtgPwr > 0 );
			long lDBID_Spc_SecSideDayltgInstalledLtgPwr = BEMPX_GetDatabaseID( "SecSideDayltgInstalledLtgPwr", iCID_Spc );			assert( lDBID_Spc_SecSideDayltgInstalledLtgPwr > 0 );
			int iCID_SpcFuncDefaults = BEMPX_GetDBComponentID( "SpcFuncDefaults" );										assert( iCID_SpcFuncDefaults > 0 );
			long lDBID_Spc_SpcFunc     = BEMPX_GetDatabaseID( "SpcFunc", iCID_Spc );									assert( lDBID_Spc_SpcFunc > 0 );
			long lDBID_Spc_SpcFuncDefaultsRef  = BEMPX_GetDatabaseID( "SpcFuncDefaultsRef", iCID_Spc );			assert( lDBID_Spc_SpcFuncDefaultsRef > 0 );
			long lDBID_SpcFuncDefaults_SpcFunc = BEMPX_GetDatabaseID( "SpcFunc", iCID_SpcFuncDefaults );			assert( lDBID_SpcFuncDefaults_SpcFunc > 0 );
			long lDBID_Spc_HotelMotelGuestRmCnt = BEMPX_GetDatabaseID( "HotelMotelGuestRmCnt", iCID_Spc );		assert( lDBID_Spc_HotelMotelGuestRmCnt > 0 );
			long lDBID_Spc_DwellingUnitTypeCnt  = BEMPX_GetDatabaseID( "DwellingUnitTypeCnt",  iCID_Spc );		assert( lDBID_Spc_DwellingUnitTypeCnt > 0 );

			int iCodeType = CT_T24N;		// SAC 10/2/14 - added to facilitate code-specific processing
			QString sLoadedRuleSetID, sLoadedRuleSetVer;
			if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))
			{	if (sLoadedRuleSetID.indexOf( "CA " ) == 0)
					iCodeType = CT_T24N;
				else if (sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0)
					iCodeType = CT_S901G;
				else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
					iCodeType = CT_ECBC;
				else
				{	assert( FALSE );	// what ruleset is this ??
			}	}

			int iNumSpcObjs = BEMPX_GetNumObjects( iCID_Spc );
			if (iCID_Spc > 0 && iNumSpcObjs > 0)
				for (int iSpcIdx=0; iSpcIdx < iNumSpcObjs; iSpcIdx++)
				{	if (lDBID_Spc_FlrArea > 0 && lDBID_Spc_Area > 0 && BEMPX_GetFloat( lDBID_Spc_FlrArea, fData, -1, BEMP_Flt, iSpcIdx ) && fData > 0)
					{	// copy FlrArea value into Area
						BEMPX_SetBEMData( lDBID_Spc_Area, BEMP_Flt, &fData, BEMO_User, iSpcIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
         	      // and default (blast) contents of FlrArea property
						BEMPX_DefaultProperty( lDBID_Spc_FlrArea, iError, iSpcIdx );
					}

					if (lBEMVersion < 7)	// SAC 11/17/14 - added check per Lukas to ensure this switching of data doesn't happen in input files for BEMVer 7 or later
					{	double dData = BEMPX_GetFloatAndStatus( lDBID_Spc_SkylitDayltgCtrlLtgPwr , iStatus, iSpecialVal, iError, iSpcIdx );
						if (iStatus == BEMS_UserDefined)
							BEMPX_SetBEMData( lDBID_Spc_SkylitDayltgInstalledLtgPwr , BEMP_Flt, &dData, BEMO_User, iSpcIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
						dData = BEMPX_GetFloatAndStatus( lDBID_Spc_PriSideDayltgCtrlLtgPwr, iStatus, iSpecialVal, iError, iSpcIdx );
						if (iStatus == BEMS_UserDefined)
							BEMPX_SetBEMData( lDBID_Spc_PriSideDayltgInstalledLtgPwr, BEMP_Flt, &dData, BEMO_User, iSpcIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
						dData = BEMPX_GetFloatAndStatus( lDBID_Spc_SecSideDayltgCtrlLtgPwr, iStatus, iSpecialVal, iError, iSpcIdx );
						if (iStatus == BEMS_UserDefined)
							BEMPX_SetBEMData( lDBID_Spc_SecSideDayltgInstalledLtgPwr, BEMP_Flt, &dData, BEMO_User, iSpcIdx, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
					}

					if (lBEMVersion < 12 &&		// SAC 6/20/16 - mods to handle old Spc:ResLivingUnitCnt -> EITHER HotelMotelGuestRmCnt OR DwellingUnitTypeCnt[3], depending on SpcFunc
							iCID_SpcFuncDefaults > 0 && lDBID_Spc_SpcFunc > 0 && lDBID_Spc_SpcFuncDefaultsRef > 0 && lDBID_SpcFuncDefaults_SpcFunc > 0 &&
							lDBID_Spc_HotelMotelGuestRmCnt > 0 && lDBID_Spc_DwellingUnitTypeCnt > 0 )
					{	long lData2 = BEMPX_GetIntegerAndStatus( lDBID_Spc_DwellingUnitTypeCnt+2, iStatus, iSpecialVal, iError, iSpcIdx );
						if (iStatus == BEMS_UserDefined)
						{	long lSpcFuncInp, lSpcFunc=0;	int iSpcFuncStatus;		BEMObject *pSpcFD;
							lSpcFuncInp = BEMPX_GetIntegerAndStatus( lDBID_Spc_SpcFunc, iSpcFuncStatus, iSpecialVal, iError, iSpcIdx );
							if (iSpcFuncStatus >= BEMS_UserLibrary)
								lSpcFunc = lSpcFuncInp;
							else if (BEMPX_GetObject( lDBID_Spc_SpcFuncDefaultsRef, pSpcFD, -1, iSpcIdx ) && pSpcFD && pSpcFD->getClass())
							{	int iSpcFDIdx = BEMPX_GetObjectIndex(  pSpcFD->getClass(), pSpcFD );
								if (iSpcFDIdx >= 0)
								{	lSpcFuncInp = BEMPX_GetIntegerAndStatus( lDBID_SpcFuncDefaults_SpcFunc, iSpcFuncStatus, iSpecialVal, iError, iSpcFDIdx );
									if (iSpcFuncStatus >= BEMS_UserLibrary)
										lSpcFunc = lSpcFuncInp;
							}	}
							if (lSpcFunc > 0 &&
									( (iCodeType == CT_T24N  && ( lSpcFunc == 125 )) ||	// "Hotel/Motel Guest Room"
									  (iCodeType == CT_S901G && ( lSpcFunc == 263 )) ))	// "Multifamily - Dwelling/Sleeping Units"                     
							{	// Spc:ResLivingUnitCnt has ALREADY been switched to DwellingUnitTypeCnt[3] regardless of SpcFunc, 
								// so for the above SpcFuncs we will switch this data AGAIN from DwellingUnitTypeCnt[3] into HotelMotelGuestRmCnt
								BEMPX_SetBEMData( lDBID_Spc_HotelMotelGuestRmCnt, BEMP_Int, (void*) &lData2, BEMO_User, iSpcIdx, BEMS_UserDefined );
								BEMPX_DefaultProperty(    lDBID_Spc_DwellingUnitTypeCnt+2, iError, iSpcIdx );
							}
							else if (lSpcFunc > 0 &&
									( (iCodeType == CT_S901G && ( lSpcFunc == 237 ||		// "Courthouse/Police Station/Penitentiary - Confinement Cells"
																		   lSpcFunc == 242 ||		// "Dormitory - Living Quarters"                               
																		   lSpcFunc == 244 ||		// "Fire Stations - Sleeping Quarters"                         
																		   lSpcFunc == 254 ||		// "Hospital - Nursery"                                        
																		   lSpcFunc == 257 )) ))	// "Hospital - Patient Room"                     
							{	// Spc:ResLivingUnitCnt has ALREADY been switched to DwellingUnitTypeCnt[3] regardless of SpcFunc, 
								// so for the above SpcFuncs we will switch this data AGAIN from DwellingUnitTypeCnt[3] into DwellingUnitTypeCnt[1]
								BEMPX_SetBEMData( lDBID_Spc_DwellingUnitTypeCnt  , BEMP_Int, (void*) &lData2, BEMO_User, iSpcIdx, BEMS_UserDefined );
								BEMPX_DefaultProperty(    lDBID_Spc_DwellingUnitTypeCnt+2, iError, iSpcIdx );
							}
					}	}
				}

	// code to hard wire old projects to Proj:CompType = "NewComplete"  -- 4/4/14
			long lDBID_Proj_CompType = BEMPX_GetDatabaseID( "Proj:CompType" );			assert( lDBID_Proj_CompType > 0 );
			if (lDBID_Proj_CompType > 0 && BEMPX_GetDataStatus( lDBID_Proj_CompType ) < 1)
				BEMPX_SetBEMData( lDBID_Proj_CompType, BEMP_Str, "NewComplete", BEMO_User, 0, BEMS_UserDefined, BEMO_User, FALSE /*bPerformResets*/ );
	// code to manually migrate Lum:Cat to combination of Lum:FxtrType & Lum:LampType (GC #678)  -- SAC 7/25/14
         long lDBID_Lum_Cat		= BEMPX_GetDatabaseID( "Lum:Cat" );						assert( lDBID_Lum_Cat      > 0 );
         long lDBID_Lum_FxtrType	= BEMPX_GetDatabaseID( "Lum:FxtrType" );				assert( lDBID_Lum_FxtrType > 0 );
         long lDBID_Lum_LampType	= BEMPX_GetDatabaseID( "Lum:LampType" );				assert( lDBID_Lum_LampType > 0 );
			if (lBEMVersion < 7)
			{	int iNumLumObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "Lum" ) );		int iNumLumUpdates = 0;
				QString sLumCat, sLumFT, sLumLT;
				if (lDBID_Lum_Cat > 0 && lDBID_Lum_FxtrType > 0 && lDBID_Lum_LampType > 0 && iNumLumObjs > 0)
					for (int iLumIdx=0; iLumIdx < iNumLumObjs; iLumIdx++)
					{	sLumFT.clear();		sLumLT.clear();		bool bBlastLumCat = true;
						if (BEMPX_GetString( lDBID_Lum_Cat, sLumCat, FALSE, 0, -1, iLumIdx ))
						{	if (!sLumCat.compare("n/a", Qt::CaseInsensitive) || !sLumCat.compare("- specify -", Qt::CaseInsensitive))
							{	// do nothing
							}
							else if (!sLumCat.compare("DownlightCompactFluorescentLuminaire"   , Qt::CaseInsensitive))	{	sLumFT = "RecessedOrDownlight";     sLumLT = "CFL";					  iNumLumUpdates++; }
							else if (!sLumCat.compare("DownlightIncandescentLuminaire"         , Qt::CaseInsensitive))	{	sLumFT = "RecessedOrDownlight";     sLumLT = "Incandescent";		  iNumLumUpdates++; }
							else if (!sLumCat.compare("NonInCeilingFluorescentLuminaire"       , Qt::CaseInsensitive))	{	sLumFT = "NotInCeiling";     			sLumLT = "LinearFluorescent";	  iNumLumUpdates++; }
							else if (!sLumCat.compare("RecessedFluorescentLuminaireWithLens"   , Qt::CaseInsensitive))	{	sLumFT = "RecessedWithLens";     	sLumLT = "LinearFluorescent";	  iNumLumUpdates++; }
							else if (!sLumCat.compare("RecessedFluorescentLuminaireWithoutLens", Qt::CaseInsensitive))	{	sLumFT = "RecessedOrDownlight";		sLumLT = "LinearFluorescent";	  iNumLumUpdates++; }
							else if (psaWarningsForUser)
							{	// REPORT ERROR
								bBlastLumCat = false;
								if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Lum:Name" ), sWarnTmp, FALSE, 0, -1, iLumIdx ) || sWarnTmp.isEmpty())
									sWarnTmp = "(unknown)";
								if (sLumCat.isEmpty())
									sWarnMsg = QString( "Backward compatibility warning:  Lum '%1' has an invalid or unrecognized Cat setting that cannot be used in the latest software." ).arg( sWarnTmp );
								else
									sWarnMsg = QString( "Backward compatibility warning:  Lum '%1' has unrecognized Cat setting '%2' that cannot be used in the latest software." ).arg( sWarnTmp, sLumCat );
								psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
							}
							if (!sLumFT.isEmpty())
								BEMPX_SetBEMData( lDBID_Lum_FxtrType, BEMP_Str, (void*) sLumFT.toLocal8Bit().constData(), BEMO_User, iLumIdx, BEMS_UserDefined );
							if (!sLumLT.isEmpty())
								BEMPX_SetBEMData( lDBID_Lum_LampType, BEMP_Str, (void*) sLumLT.toLocal8Bit().constData(), BEMO_User, iLumIdx, BEMS_UserDefined );
							if (bBlastLumCat)
								BEMPX_DefaultProperty( lDBID_Lum_Cat, iError, iLumIdx );
					}	}
				if (iNumLumUpdates > 0)
				{	sWarnMsg = QString( "Backward compatibility:  Lum:Cat converted to Lum:FxtrType and Lum:LampType for %1 luminaire(s)." ).arg( QString::number(iNumLumUpdates) );
					psaWarningsForUser->push_back( sWarnMsg );
			}	}

		// SAC 4/5/16 - code to force re-default of Proj:CliZn in certain situations
			int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );													assert( iCID_Proj > 0 );
			long lDBID_Proj_ZipCode		= BEMPX_GetDatabaseID( "ZipCode", iCID_Proj );					assert( lDBID_Proj_ZipCode > 0 );
			long lDBID_Proj_CliZn		= BEMPX_GetDatabaseID( "CliZn", iCID_Proj );						assert( lDBID_Proj_CliZn > 0 );
			long lDBID_Proj_CliZnNum	= BEMPX_GetDatabaseID( "CliZnNum", iCID_Proj );					assert( lDBID_Proj_CliZnNum > 0 );
			long lDBID_Proj_WthrSta		= BEMPX_GetDatabaseID( "WeatherStation", iCID_Proj );			assert( lDBID_Proj_WthrSta > 0 );
			long lDBID_Proj_WthrStaNum	= BEMPX_GetDatabaseID( "WeatherStationNum", iCID_Proj );		assert( lDBID_Proj_WthrStaNum > 0 );
			if (iCID_Proj > 0 && lDBID_Proj_ZipCode > 0 && lDBID_Proj_CliZn > 0 && lDBID_Proj_CliZnNum > 0 && lDBID_Proj_WthrSta > 0 && lDBID_Proj_WthrStaNum > 0)
			{	long lZipCodeI, lCliZnI, lCliZnNI, lWSI, lWSNI;		int iStatusZip, iStatusCZ, iStatusCZN, iStatusWS, iStatusWSN;		QString sWarnMsg;
				lZipCodeI = BEMPX_GetIntegerAndStatus( lDBID_Proj_ZipCode   , iStatusZip, iSpecialVal, iError );
				lCliZnI   = BEMPX_GetIntegerAndStatus( lDBID_Proj_CliZn     , iStatusCZ , iSpecialVal, iError );
				lCliZnNI  = BEMPX_GetIntegerAndStatus( lDBID_Proj_CliZnNum  , iStatusCZN, iSpecialVal, iError );
				lWSI      = BEMPX_GetIntegerAndStatus( lDBID_Proj_WthrSta   , iStatusWS , iSpecialVal, iError );
				lWSNI     = BEMPX_GetIntegerAndStatus( lDBID_Proj_WthrStaNum, iStatusWSN, iSpecialVal, iError );
				if (lBEMVersion < 13 && iStatusZip >= BEMS_UserLibrary && lZipCodeI == 92133)
				{	// model included invalid ZipCode = 92133 - removed from ruleset Apr-2016 before release of ver 3d
					long lZip = 92132;
					BEMPX_SetBEMData( lDBID_Proj_ZipCode, BEMP_Int, (void*) &lZip, BEMO_User, -1, BEMS_UserDefined );
					sWarnMsg = "Invalid ZipCode setting of 92133 has been switched to 92132.";
					if (bCalledFromUI)
						sWarnMsg += "\nCheck/confirm location settings before performing analysis.";
					psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
				}
				else if (lBEMVersion < 13 && iStatusZip >= BEMS_UserLibrary && (lZipCodeI == 95321 || lZipCodeI == 92675))
				{	// SAC 2/28/17 - certain zips switched from one CZ to another with release of 2016.3.0 ~Mar-2017 (tic #1972)
					if ( (lZipCodeI == 95321 && lCliZnI == 12 && lWSI == 54 /*  MERCED_724815*/) ||
						  (lZipCodeI == 92675 && lCliZnI ==  6 && lWSI == 24 /*TORRANCE_722955*/) )
					{	// do nothing - user input already reflects new/corrected settings
					}
					else if ( (lZipCodeI == 95321 && lCliZnI != 16 && lWSI != 79 /*SOUTH-LAKE-TAHOE_725847*/) ||
								 (lZipCodeI == 92675 && lCliZnI !=  8 && lWSI != 40 /*       SANTA-ANA_722977*/) ||
								 ( iStatusCZ < BEMS_UserLibrary && iStatusCZN < BEMS_UserLibrary &&
									iStatusWS < BEMS_UserLibrary && iStatusWSN < BEMS_UserLibrary ) )
					{	// user has overridden past defaults -OR- all dependants will be defaulted, so simply inform the user of the change in CZ for the specified ZipCode
						if (lZipCodeI == 95321)
							sWarnMsg = "Mapping of ZipCode 95321 has switched from climate zone 16 to 12 (weather station South Lake Tahoe to Merced).";
						else
							sWarnMsg = "Mapping of ZipCode 92675 has switched from climate zone 8 to 6 (weather station Santa Ana to Torrance).";
						if (bCalledFromUI)
							sWarnMsg += "\nCheck/confirm location settings before performing analysis.";
						psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
					}
					else
					{	// one or more Zip-dependencies are user-defined to the previous (incorrect) default, so re-default ALL
						BEMPX_DefaultProperty( lDBID_Proj_CliZn     , iError );
						BEMPX_DefaultProperty( lDBID_Proj_CliZnNum  , iError );
						BEMPX_DefaultProperty( lDBID_Proj_WthrSta   , iError );
						BEMPX_DefaultProperty( lDBID_Proj_WthrStaNum, iError );
						sWarnMsg = QString( "Mapping of ZipCode %1 has switched climate zones and weather stations, so these data have been re-defaulted (based on ZipCode)." ).arg( QString::number( lZipCodeI ) );
						if (bCalledFromUI)
							sWarnMsg += "\nCheck/confirm location settings before performing analysis.";
						psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
					}
				}
				else if (iStatusZip >= BEMS_UserLibrary && ((iStatusCZ >= BEMS_UserLibrary) || (iStatusCZN >= BEMS_UserLibrary)) &&
							(iStatusWS < BEMS_UserLibrary) && (iStatusWSN < BEMS_UserLibrary))
				{	// we have user-specified ZipCode and CliZn(Num) but no user-specified WeatherStation(Num)
					// next step - check to see if this combination of ZipCode and CliZn(Num) yield a valid WeatherStation default
					// if NO valid WeatherStation exists, then and only then will we reset CliZn * CliZnNum and warn user
					double dZipCode = (double) lZipCodeI;
					double dCliZn   = (double) ((iStatusCZ >= BEMS_UserLibrary) ? lCliZnI : lCliZnNI);
					std::vector<std::string> saIndepNames;		saIndepNames.push_back( "ZipCode" );		saIndepNames.push_back( "CliZn" );
					std::vector<std::string> saIndepStrings;	saIndepStrings.push_back( " " );				saIndepStrings.push_back( " " );
					std::vector<double> faIndepValues;		faIndepValues.push_back( dZipCode );		faIndepValues.push_back( dCliZn );
					std::vector<bool> baIndepNumeric;		baIndepNumeric.push_back( true );			baIndepNumeric.push_back( true );
					std::string sTblErrMsg;
					double dTblVal = BEMPX_RuleTableLookupFloat( "WeatherFileData:IsValid", saIndepNames, saIndepStrings, faIndepValues,
																				baIndepNumeric, sTblErrMsg, FALSE /*bVerboseOutput*/ );
					if ( dTblVal > 0 ||		// IsValid from table > 0 => there IS a valid default WeatherStation
							(sTblErrMsg.length() > 0 && dTblVal == -1) )		// combination of table and column name not found => not evaluating T-24 rules - so bail on data mods
					{	// do nothing
					}
					else
					{		assert( dTblVal == 0.0 );		// lookup return value should be 0 for any invalid combimnation of ZipCode & CliZn...
						BEMPX_DefaultProperty( lDBID_Proj_CliZn   , iError );
						BEMPX_DefaultProperty( lDBID_Proj_CliZnNum, iError );
						sWarnMsg = QString( "There is no longer a default weather station for Zip code %1 in climate zone %2, so the CliZn and CliZnNum"
													" properties have been re-defaulted (based on ZipCode)." ).arg( QString::number(dZipCode, 'f', 0), QString::number(dCliZn, 'f', 0) );
						if (bCalledFromUI)
							sWarnMsg += "\nCheck/confirm location settings before performing analysis.";
						psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
				}	}
			}

		// SAC 4/6/16 - code to override ThrmlZn:VentSrc of "None" w/ "Natural" for residential, conditioned spaces
			//int iCID_Spc = BEMPX_GetDBComponentID( "Spc" );										assert( iCID_Spc > 0 );
			int iCID_ThrmlZn = BEMPX_GetDBComponentID( "ThrmlZn" );															assert( iCID_ThrmlZn > 0 );
			long lDBID_ThrmlZn_VentSrc = BEMPX_GetDatabaseID( "VentSrc", iCID_ThrmlZn );								assert( lDBID_ThrmlZn_VentSrc > 0 );
			long lDBID_Spc_CondgType   = BEMPX_GetDatabaseID( "CondgType", iCID_Spc );									assert( lDBID_Spc_CondgType > 0 );
			long lDBID_Spc_ThrmlZnRef  = BEMPX_GetDatabaseID( "ThrmlZnRef", iCID_Spc );								assert( lDBID_Spc_ThrmlZnRef > 0 );
			std::vector<int> iaZoneVentSrcStatus;		// values:  0 = not applicable to this mod / 1 = zone VentSrc user-defined @ "None" / 2 = 1 + assigning Spc(s) are residential & conditioned
			int iNumZnObjs = BEMPX_GetNumObjects( iCID_ThrmlZn );		long lZnVentSrcI;		int iZnVentSrcStatus;
			int iNumZnsVentSrcNone = 0, iZnIdx;
			if (iCID_ThrmlZn > 0 && iCID_SpcFuncDefaults > 0 && lDBID_ThrmlZn_VentSrc > 0 && lDBID_Spc_SpcFunc > 0 && lDBID_Spc_ThrmlZnRef > 0 && 
					lDBID_Spc_SpcFuncDefaultsRef > 0 && lDBID_SpcFuncDefaults_SpcFunc > 0 && iNumZnObjs > 0)
			{	for (iZnIdx=0; iZnIdx < iNumZnObjs; iZnIdx++)
				{	lZnVentSrcI = BEMPX_GetIntegerAndStatus( lDBID_ThrmlZn_VentSrc, iZnVentSrcStatus, iSpecialVal, iError, iZnIdx );
					if (iZnVentSrcStatus >= BEMS_UserLibrary && lZnVentSrcI == 1)
					{	iNumZnsVentSrcNone++;
						iaZoneVentSrcStatus.push_back( 1 );
					}
					else
						iaZoneVentSrcStatus.push_back( 0 );
				}
				if (iNumZnsVentSrcNone > 0)
				{	long lSpcCondgType;		BEMObject *pSpcZn;
					int iNumResCondZnsVentSrcNone = 0;
					for (int iSpcIdx=0; iSpcIdx < iNumSpcObjs; iSpcIdx++)
					{	if (BEMPX_GetInteger( lDBID_Spc_CondgType, lSpcCondgType, 0, -1, iSpcIdx ) && lSpcCondgType == 1 &&
							 BEMPX_GetObject( lDBID_Spc_ThrmlZnRef, pSpcZn, -1, iSpcIdx ) && pSpcZn && pSpcZn->getClass())
						{	// this is a DirectlyConditioned Spc w/ a valid ThrmlZn assignment
							iZnIdx = BEMPX_GetObjectIndex(  pSpcZn->getClass(), pSpcZn );
							if (iZnIdx >= 0 && iZnIdx < (int) iaZoneVentSrcStatus.size() && iaZoneVentSrcStatus[iZnIdx] == 1)
							{	// the assigned ThrmlZn has a VentSrc of None and we should check to see if this Spc is Res in which case we should upgrade the zone to '2'
								long lSpcFuncI, lSpcFunc=0;	int iSpcFuncStatus;		BEMObject *pSpcFD;
								lSpcFuncI = BEMPX_GetIntegerAndStatus( lDBID_Spc_SpcFunc, iSpcFuncStatus, iSpecialVal, iError, iSpcIdx );
								if (iSpcFuncStatus >= BEMS_UserLibrary)
									lSpcFunc = lSpcFuncI;
								else if (BEMPX_GetObject( lDBID_Spc_SpcFuncDefaultsRef, pSpcFD, -1, iSpcIdx ) && pSpcFD && pSpcFD->getClass())
								{	int iSpcFDIdx = BEMPX_GetObjectIndex(  pSpcFD->getClass(), pSpcFD );
									if (iSpcFDIdx >= 0)
									{	lSpcFuncI = BEMPX_GetIntegerAndStatus( lDBID_SpcFuncDefaults_SpcFunc, iSpcFuncStatus, iSpecialVal, iError, iSpcFDIdx );
										if (iSpcFuncStatus >= BEMS_UserLibrary)
											lSpcFunc = lSpcFuncI;
								}	}
								if (lSpcFunc > 0 &&
										( (iCodeType == CT_T24N  && ( lSpcFunc == 123 ||		// "High-Rise Residential Living Spaces"
																			   lSpcFunc == 125 )) ||	// "Hotel/Motel Guest Room"
										  (iCodeType == CT_S901G && ( lSpcFunc == 237 ||		// "Courthouse/Police Station/Penitentiary - Confinement Cells"
																			   lSpcFunc == 242 ||		// "Dormitory - Living Quarters"                               
																			   lSpcFunc == 244 ||		// "Fire Stations - Sleeping Quarters"                         
																			   lSpcFunc == 254 ||		// "Hospital - Nursery"                                        
																			   lSpcFunc == 257 ||		// "Hospital - Patient Room"                                   
																			   lSpcFunc == 263 ||		// "Hotel/Highway Lodging - Hotel Guest Rooms"                 
																			   lSpcFunc == 266 ||		// "Hotel/Highway Lodging - Highway Lodging Guest Rooms"       
																			   lSpcFunc == 275 )) ))	// "Multifamily - Dwelling/Sleeping Units"                     
								{	iNumResCondZnsVentSrcNone++;
									iaZoneVentSrcStatus[iZnIdx] = 2;		// THIS zone's VentSrc needs to be updated to "Natural"
								}
					}	}	}
					if (iNumResCondZnsVentSrcNone > 0)
					{	// one or more zones must be switched from VentSrc = None -> Natural
						long lVentSrcNatural = 3;		QString sZnName, sWarnTmp;
						for (int iZnIdx=0; iZnIdx < iNumZnObjs; iZnIdx++)
							if (iaZoneVentSrcStatus[iZnIdx] == 2)
							{	BEMPX_SetBEMData( lDBID_ThrmlZn_VentSrc, BEMP_Int, (void*) &lVentSrcNatural, BEMO_User, iZnIdx, BEMS_UserDefined );
								if (iNumResCondZnsVentSrcNone < 3)
								{	if (!sWarnTmp.isEmpty())
										sWarnTmp += "' and '";
									if (BEMPX_GetString( BEMPX_GetDatabaseID( "ThrmlZn:Name" ), sZnName, FALSE, 0, -1, iZnIdx ) && !sZnName.isEmpty())
										sWarnTmp += sZnName;
								}
							}
						if (iNumResCondZnsVentSrcNone < 3)
							sWarnMsg = QString( "VentSrc of residential, conditioned thermal zone%1'%2' switched from 'None' to 'Natural' to ensure proper simulation." ).arg(
															(iNumResCondZnsVentSrcNone == 1 ? " " : "s "), sWarnTmp );
						else 
							sWarnMsg = QString( "VentSrc of %1 residential, conditioned thermal zones have been switched from 'None' to 'Natural' to ensure proper simulation." ).arg( 
															 QString::number(iNumResCondZnsVentSrcNone) );
						psaWarningsForUser->push_back( sWarnMsg );				assert( FALSE );
					}
			}	}
#else
			bCalledFromUI;
#endif

	// backward compatibility for CEC-Res multifamily dwelling units
			bool bAbortMFamDUUpdate = false;
			int iDUCID  = BEMPX_GetDBComponentID( "DwellUnit" );
			int iDUTCID = BEMPX_GetDBComponentID( "DwellUnitType" );
			long lIsMFam, lBEMVer, lIsMFamDBID = BEMPX_GetDatabaseID( "Proj:IsMultiFamily" ), lBEMVerDBID = BEMPX_GetDatabaseID( "Proj:BEMVersion" );
			if (iDUCID > 0 && iDUTCID > 0 && BEMPX_GetNumObjects( iDUCID ) < 1 && BEMPX_GetNumObjects( iDUTCID ) < 1 &&
				 lIsMFamDBID > 0 && BEMPX_GetInteger( lIsMFamDBID, lIsMFam ) && lIsMFam > 0 &&		// is MFam project
				 lBEMVerDBID > 0 && (!BEMPX_GetInteger( lBEMVerDBID, lBEMVer ) || lBEMVer < 4))		// is version of BEMBase PRIOR to switch to DwellUnit* objects
			{	QString sDUErr, sDUTempErr;		int iDUWarnStrSize = -1, iNumDUTCreated = 0;
				if (psaWarningsForUser)
				{	sDUTempErr = "Issues encountered converting old multifamily inputs to new:";
					psaWarningsForUser->push_back( sDUTempErr );
					iDUWarnStrSize = psaWarningsForUser->size();
				}
				int iCID_Proj    = GetBEMBaseCompID( sDUErr, "Proj"    );
				int iCID_Zone    = GetBEMBaseCompID( sDUErr, "Zone"    );
				int iCID_HVACSys = GetBEMBaseCompID( sDUErr, "HVACSys" );
				if (sDUErr.length() > 0)
				{	bAbortMFamDUUpdate = true;
					if (psaWarningsForUser)
					{	sDUTempErr = QString( "   Error retrieving BEMBase object ID(s):  %1." ).arg( sDUErr );
						psaWarningsForUser->push_back( sDUTempErr );
				}	}
				else
				{	long lDBID_Proj_ZonalControl        = GetBEMBaseDBID( sDUErr, "ZonalControl",        iCID_Proj );
					long lDBID_Proj_RunScope            = GetBEMBaseDBID( sDUErr, "RunScope",            iCID_Proj );
               long lDBID_Proj_UnitName            = GetBEMBaseDBID( sDUErr, "UnitName",            iCID_Proj );
               long lDBID_Proj_UnitCount           = GetBEMBaseDBID( sDUErr, "UnitCount",           iCID_Proj );
               long lDBID_Proj_UnitCondFlrArea     = GetBEMBaseDBID( sDUErr, "UnitCondFlrArea",     iCID_Proj );
               long lDBID_Proj_UnitCondFlrArea_Liv = GetBEMBaseDBID( sDUErr, "UnitCondFlrArea_Liv", iCID_Proj );
               long lDBID_Proj_UnitCondFlrArea_Slp = GetBEMBaseDBID( sDUErr, "UnitCondFlrArea_Slp", iCID_Proj );
               long lDBID_Proj_ConditionedZone     = GetBEMBaseDBID( sDUErr, "ConditionedZone",     iCID_Proj );
               long lDBID_Proj_LivingZone          = GetBEMBaseDBID( sDUErr, "LivingZone",          iCID_Proj );
               long lDBID_Proj_SleepingZone        = GetBEMBaseDBID( sDUErr, "SleepingZone",        iCID_Proj );
               long lDBID_Proj_UnitNumBedrooms     = GetBEMBaseDBID( sDUErr, "UnitNumBedrooms",     iCID_Proj );
					long lDBID_Proj_ApplRefrigZone      = GetBEMBaseDBID( sDUErr, "ApplRefrigZone",      iCID_Proj );		// "ApplRefrigZone",    BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned zone for appliances"                 
					long lDBID_Proj_ApplCookZone        = GetBEMBaseDBID( sDUErr, "ApplCookZone",        iCID_Proj );		// "ApplCookZone",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned/unconditioned zone for appliances"   
					long lDBID_Proj_ApplDishZone        = GetBEMBaseDBID( sDUErr, "ApplDishZone",        iCID_Proj );		// "ApplDishZone",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned/unconditioned zone for appliances"   
					long lDBID_Proj_Appl_HaveWasher     = GetBEMBaseDBID( sDUErr, "Appl_HaveWasher",     iCID_Proj );		// "Appl_HaveWasher",   BEMP_Int, 16,   0,           "flag indicating whether a clothes washer is included"    
					long lDBID_Proj_Appl_HaveDryer      = GetBEMBaseDBID( sDUErr, "Appl_HaveDryer",      iCID_Proj );		// "Appl_HaveDryer",    BEMP_Int, 16,   0,           "flag indicating whether a clothes dryer is included"     
					long lDBID_Proj_ApplWasherZone      = GetBEMBaseDBID( sDUErr, "ApplWasherZone",      iCID_Proj );		// "ApplWasherZone",    BEMP_Obj, 16,   1, "Zone",   "Conditioned/unconditioned zone for appliances"           
					long lDBID_Proj_ApplDryerZone       = GetBEMBaseDBID( sDUErr, "ApplDryerZone",       iCID_Proj );		// "ApplDryerZone",     BEMP_Obj, 16,   1, "Zone",   "Conditioned/unconditioned zone for appliances"           
					long lDBID_Proj_ApplDryerFuel       = GetBEMBaseDBID( sDUErr, "ApplDryerFuel",       iCID_Proj );		// "ApplDryerFuel",     BEMP_Sym, 16,   0,           "Fuel used for cooking appliances (stove/oven)"           
					long lDBID_Proj_UnitIAQOption       = GetBEMBaseDBID( sDUErr, "UnitIAQOption",       iCID_Proj );		// "UnitIAQOption",     BEMP_Sym, 16,    0,               ""                                                                                                
					long lDBID_Proj_UnitIAQFan1         = GetBEMBaseDBID( sDUErr, "UnitIAQFan1",         iCID_Proj );		// "UnitIAQFan1",       BEMP_Obj, 16,    1, "IAQFan",     "IAQ fan object"                                                                                  
					long lDBID_Proj_UnitIAQFan2         = GetBEMBaseDBID( sDUErr, "UnitIAQFan2",         iCID_Proj );		// "UnitIAQFan2",       BEMP_Obj, 16,    1, "IAQFan",     "IAQ fan object"                                                                                  
					long lDBID_Proj_UnitIAQFan3         = GetBEMBaseDBID( sDUErr, "UnitIAQFan3",         iCID_Proj );		// "UnitIAQFan3",       BEMP_Obj, 16,    1, "IAQFan",     "IAQ fan object"                                                                                  
					long lDBID_Proj_UnitIAQFan4         = GetBEMBaseDBID( sDUErr, "UnitIAQFan4",         iCID_Proj );		// "UnitIAQFan4",       BEMP_Obj, 16,    1, "IAQFan",     "IAQ fan object"                                                                                  
					long lDBID_Proj_UnitIAQFanCnt1      = GetBEMBaseDBID( sDUErr, "UnitIAQFanCnt1",      iCID_Proj );		// "UnitIAQFanCnt1",    BEMP_Int, 16,    0,               "IAQ fan count"                                                                                   
					long lDBID_Proj_UnitIAQFanCnt2      = GetBEMBaseDBID( sDUErr, "UnitIAQFanCnt2",      iCID_Proj );		// "UnitIAQFanCnt2",    BEMP_Int, 16,    0,               "IAQ fan count"                                                                                   
					long lDBID_Proj_UnitIAQFanCnt3      = GetBEMBaseDBID( sDUErr, "UnitIAQFanCnt3",      iCID_Proj );		// "UnitIAQFanCnt3",    BEMP_Int, 16,    0,               "IAQ fan count"                                                                                   
					long lDBID_Proj_UnitIAQFanCnt4      = GetBEMBaseDBID( sDUErr, "UnitIAQFanCnt4",      iCID_Proj );		// "UnitIAQFanCnt4",    BEMP_Int, 16,    0,               "IAQ fan count"                                                                                   
					long lDBID_Proj_UnitIAQZone1        = GetBEMBaseDBID( sDUErr, "UnitIAQZone1",        iCID_Proj );		// "UnitIAQZone1",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned zone where IAQ fan is located"   
					long lDBID_Proj_UnitIAQZone2        = GetBEMBaseDBID( sDUErr, "UnitIAQZone2",        iCID_Proj );		// "UnitIAQZone2",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned zone where IAQ fan is located"   
					long lDBID_Proj_UnitIAQZone3        = GetBEMBaseDBID( sDUErr, "UnitIAQZone3",        iCID_Proj );		// "UnitIAQZone3",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned zone where IAQ fan is located"   
					long lDBID_Proj_UnitIAQZone4        = GetBEMBaseDBID( sDUErr, "UnitIAQZone4",        iCID_Proj );		// "UnitIAQZone4",      BEMP_Obj, 16,    3, "Zone", 1, "Type", "Zone", 2, "Type", "Zone", 3, "Type",    1080, "Conditioned zone where IAQ fan is located"   
//					long lDBID_Proj_ = GetBEMBaseDBID( sDUErr, "",   iCID_Proj );

					long lDBID_Zone_Type          = GetBEMBaseDBID( sDUErr, "Type",          iCID_Zone );
					long lDBID_Zone_HVACSysStatus = GetBEMBaseDBID( sDUErr, "HVACSysStatus", iCID_Zone );
					long lDBID_Zone_HVACSystem    = GetBEMBaseDBID( sDUErr, "HVACSystem",    iCID_Zone );
					long lDBID_Zone_AltHVACSystem = GetBEMBaseDBID( sDUErr, "AltHVACSystem", iCID_Zone );
					long lDBID_Zone_exHVACSystem  = GetBEMBaseDBID( sDUErr, "exHVACSystem",  iCID_Zone );
					long lDBID_Zone_DHWSys1Status = GetBEMBaseDBID( sDUErr, "DHWSys1Status", iCID_Zone );
					long lDBID_Zone_DHWSys1       = GetBEMBaseDBID( sDUErr, "DHWSys1",       iCID_Zone );
					long lDBID_Zone_AltDHWSys1    = GetBEMBaseDBID( sDUErr, "AltDHWSys1",    iCID_Zone );
					long lDBID_Zone_exDHWSys1     = GetBEMBaseDBID( sDUErr, "exDHWSys1",     iCID_Zone );
					long lDBID_Zone_DHWSys2Status = GetBEMBaseDBID( sDUErr, "DHWSys2Status", iCID_Zone );
					long lDBID_Zone_DHWSys2       = GetBEMBaseDBID( sDUErr, "DHWSys2",       iCID_Zone );
					long lDBID_Zone_AltDHWSys2    = GetBEMBaseDBID( sDUErr, "AltDHWSys2",    iCID_Zone );
					long lDBID_Zone_exDHWSys2     = GetBEMBaseDBID( sDUErr, "exDHWSys2",     iCID_Zone );
//					long lDBID_Zone_ = GetBEMBaseDBID( sDUErr, "",   iCID_Zone );

					long lDBID_HVACSys_Type                 = GetBEMBaseDBID( sDUErr, "Type",                 iCID_HVACSys );
					long lDBID_HVACSys_NumHtPumpSystemTypes = GetBEMBaseDBID( sDUErr, "NumHtPumpSystemTypes", iCID_HVACSys );
					long lDBID_HVACSys_HtPumpSystem         = GetBEMBaseDBID( sDUErr, "HtPumpSystem",         iCID_HVACSys );
					long lDBID_HVACSys_HtPumpSystemCount    = GetBEMBaseDBID( sDUErr, "HtPumpSystemCount",    iCID_HVACSys );
					long lDBID_HVACSys_NumHeatSystemTypes   = GetBEMBaseDBID( sDUErr, "NumHeatSystemTypes",   iCID_HVACSys );
					long lDBID_HVACSys_HeatSystem           = GetBEMBaseDBID( sDUErr, "HeatSystem",           iCID_HVACSys );
					long lDBID_HVACSys_HeatSystemCount      = GetBEMBaseDBID( sDUErr, "HeatSystemCount",      iCID_HVACSys );
					long lDBID_HVACSys_NumCoolSystemTypes   = GetBEMBaseDBID( sDUErr, "NumCoolSystemTypes",   iCID_HVACSys );
					long lDBID_HVACSys_CoolSystem           = GetBEMBaseDBID( sDUErr, "CoolSystem",           iCID_HVACSys );
					long lDBID_HVACSys_CoolSystemCount      = GetBEMBaseDBID( sDUErr, "CoolSystemCount",      iCID_HVACSys );
					long lDBID_HVACSys_DistribSystem        = GetBEMBaseDBID( sDUErr, "DistribSystem",        iCID_HVACSys );
					long lDBID_HVACSys_Fan                  = GetBEMBaseDBID( sDUErr, "Fan",                  iCID_HVACSys );
//					long lDBID_HVACSys_ = GetBEMBaseDBID( sDUErr, "",   iCID_HVACSys );

					long lDBID_DUT_NumBedrooms         = GetBEMBaseDBID( sDUErr, "NumBedrooms",         iDUTCID );		// "NumBedrooms",        BEMP_Int,  1,  1,  0, "",          Default,   "Number of bedrooms"                
					long lDBID_DUT_CondFlrArea         = GetBEMBaseDBID( sDUErr, "CondFlrArea",         iDUTCID );		// "CondFlrArea",        BEMP_Flt,  1,  1,  0, "ft2",    Compulsory,   "Conditioned floor area (per unit)" 
					long lDBID_DUT_HVACSysType         = GetBEMBaseDBID( sDUErr, "HVACSysType",         iDUTCID );		// 
					long lDBID_DUT_NumHeatEquipTypes   = GetBEMBaseDBID( sDUErr, "NumHeatEquipTypes",   iDUTCID );
					long lDBID_DUT_NumHtPumpEquipTypes = GetBEMBaseDBID( sDUErr, "NumHtPumpEquipTypes", iDUTCID );
					long lDBID_DUT_HVACHeatRef         = GetBEMBaseDBID( sDUErr, "HVACHeatRef",         iDUTCID );
					long lDBID_DUT_HVACHtPumpRef       = GetBEMBaseDBID( sDUErr, "HVACHtPumpRef",       iDUTCID );
					long lDBID_DUT_HeatEquipCount      = GetBEMBaseDBID( sDUErr, "HeatEquipCount",      iDUTCID );
					long lDBID_DUT_HtPumpEquipCount    = GetBEMBaseDBID( sDUErr, "HtPumpEquipCount",    iDUTCID );
					long lDBID_DUT_NumCoolEquipTypes   = GetBEMBaseDBID( sDUErr, "NumCoolEquipTypes",   iDUTCID );
					long lDBID_DUT_HVACCoolRef         = GetBEMBaseDBID( sDUErr, "HVACCoolRef",         iDUTCID );
					long lDBID_DUT_CoolEquipCount      = GetBEMBaseDBID( sDUErr, "CoolEquipCount",      iDUTCID );
					long lDBID_DUT_HVACDistRef         = GetBEMBaseDBID( sDUErr, "HVACDistRef",         iDUTCID );
					long lDBID_DUT_HVACFanRef          = GetBEMBaseDBID( sDUErr, "HVACFanRef",          iDUTCID );
					long lDBID_DUT_HaveWasher          = GetBEMBaseDBID( sDUErr, "HaveWasher",          iDUTCID );		// "HaveWasher",     BEMP_Int,  1,  1,      Default,   "Presence of a clothes washer"                    
					long lDBID_DUT_HaveDryer           = GetBEMBaseDBID( sDUErr, "HaveDryer",           iDUTCID );		// "HaveDryer",      BEMP_Int,  1,  1,      Default,   "Presence of a clothes dryer"                     
					long lDBID_DUT_DryerFuel           = GetBEMBaseDBID( sDUErr, "DryerFuel",           iDUTCID );		// "DryerFuel",      BEMP_Sym,  1,  1,      Default,   "Fuel used for cooking appliances (stove/oven)"   
					long lDBID_DUT_NumDHWSysTypes      = GetBEMBaseDBID( sDUErr, "NumDHWSysTypes",      iDUTCID );		// "NumDHWSysTypes", BEMP_Int,  1,  0,      Default,   "Number of DHW systems that serve this DwellUnitType"    
					long lDBID_DUT_DHWSysRef           = GetBEMBaseDBID( sDUErr, "DHWSysRef",           iDUTCID );		// "DHWSysRef",      BEMP_Obj,  5,  1,     Optional,   1, "DHWSys",   "DHW system that serves this equip zone type"            
					long lDBID_DUT_IAQOption           = GetBEMBaseDBID( sDUErr, "IAQOption",           iDUTCID );		// "IAQOption",      BEMP_Sym,  1,  1,      Default,   0,             ""                 
					long lDBID_DUT_IAQFanRef           = GetBEMBaseDBID( sDUErr, "IAQFanRef",           iDUTCID );		// "IAQFanRef",      BEMP_Obj,  4,  1,     Optional,   1, "IAQFan",   "IAQ fan object"   
					long lDBID_DUT_IAQFanCnt           = GetBEMBaseDBID( sDUErr, "IAQFanCnt",           iDUTCID );		// "IAQFanCnt",      BEMP_Int,  4,  1,      Default,   0,             "IAQ fan count"    
//					long lDBID_DUT_ = GetBEMBaseDBID( sDUErr, "",   iDUTCID );

					long lDBID_DU_DwellUnitTypeRef = GetBEMBaseDBID( sDUErr, "DwellUnitTypeRef", iDUCID );		// "DwellUnitTypeRef",   BEMP_Obj,  1,  1,  Compulsory,   1, "DwellUnitType", 0, "",  "DwellUnitType object"                                  
					long lDBID_DU_Count            = GetBEMBaseDBID( sDUErr, "Count",            iDUCID );		// "Count",              BEMP_Int,  1,  1,     Default,   0,                          "DwellUnit count"                                       
					long lDBID_DU_WasherZoneRef    = GetBEMBaseDBID( sDUErr, "WasherZoneRef",    iDUCID );		// "WasherZoneRef",      BEMP_Obj,  1,  1,     Optional,  1, "Zone", 0, "",           "Conditioned/unconditioned zone for clothes washer"     
					long lDBID_DU_DryerZoneRef     = GetBEMBaseDBID( sDUErr, "DryerZoneRef",     iDUCID );		// "DryerZoneRef",       BEMP_Obj,  1,  1,     Optional,  1, "Zone", 0, "",           "Conditioned/unconditioned zone for clothes dryer"      

					if (sDUErr.length() > 0)
					{	bAbortMFamDUUpdate = true;
						if (psaWarningsForUser)
						{	sDUTempErr = QString( "   Error retrieving BEMBase property ID(s):  %1." ).arg( sDUErr );
							psaWarningsForUser->push_back( sDUTempErr );
					}	}
					else
					{	long lZonalControl=0, lRunScope=0;
						BEMPX_GetInteger( lDBID_Proj_ZonalControl, lZonalControl );
						BEMPX_GetInteger( lDBID_Proj_RunScope, lRunScope, 1 /*default to New Cons*/ );
						if (lZonalControl > 0 && psaWarningsForUser)
							psaWarningsForUser->push_back( "   Zonal Control Credit is selected in this project but is incompatible with existing multifamily analysis." );
						for (int iDUIdx=1; (!bAbortMFamDUUpdate && iDUIdx <= 16); iDUIdx++)
						{	long lCount;
							if (BEMPX_GetInteger( lDBID_Proj_UnitCount+iDUIdx-1, lCount ) && lCount > 0)
							{	double fFlrArea;		long lZoneAssignDBID=lDBID_Proj_ConditionedZone+iDUIdx-1;		QString sOldDUName;
								BEMPX_GetString( lDBID_Proj_UnitName+iDUIdx-1, sOldDUName );				assert( !sOldDUName.isEmpty() );
								if (lZonalControl < 1)
									BEMPX_GetFloat( lDBID_Proj_UnitCondFlrArea+iDUIdx-1, fFlrArea );
								else
								{	double fSlpArea, fLivArea;
									BEMPX_GetFloat( lDBID_Proj_UnitCondFlrArea_Liv+iDUIdx-1, fLivArea );
									BEMPX_GetFloat( lDBID_Proj_UnitCondFlrArea_Slp+iDUIdx-1, fSlpArea );
									if (fSlpArea < fLivArea)
									{	fFlrArea = fLivArea;
										lZoneAssignDBID = lDBID_Proj_LivingZone+iDUIdx-1;
									}
									else
									{	fFlrArea = fSlpArea;
										lZoneAssignDBID = lDBID_Proj_SleepingZone+iDUIdx-1;
									}
									if (fSlpArea > 0.01 && fLivArea > 0.01)
									{	fFlrArea = fLivArea + fSlpArea;
										if (psaWarningsForUser)
										{	sDUTempErr = QString( "   Dwelling unit #%1 ('%2') inputs include both living (%3 sf) and sleeping (%4 sf) areas.  Zone assignment based on %5 selection." ).arg(
																		QString::number(iDUIdx), sOldDUName, QString::number(fLivArea), QString::number(fSlpArea), (fSlpArea < fLivArea ? "Living" : "Sleeping") );
											psaWarningsForUser->push_back( sDUTempErr );
								}	}	}
								if (fFlrArea < 0.01 && psaWarningsForUser)
								{	sDUTempErr = QString( "   Dwelling unit #%1 ('%2') inputs include non-zero Count, but no valid floor area." ).arg( QString::number(iDUIdx), sOldDUName );
									psaWarningsForUser->push_back( sDUTempErr );
								}
								if (fFlrArea >= 0.01)
								{	QString sOldDUZone;
									BEMPX_GetString( lZoneAssignDBID, sOldDUZone );				assert( !sOldDUZone.isEmpty() );
									BEMObject* pZnObj = (sOldDUZone.isEmpty() ? NULL : BEMPX_GetObjectByName( iCID_Zone, iError, sOldDUZone.toLocal8Bit().constData() ));
									int iZnObjIdx = (pZnObj==NULL ? -1 : BEMPX_GetObjectIndex( pZnObj->getClass(), pZnObj ));
									if (sOldDUZone.isEmpty() && psaWarningsForUser)
									{	sDUTempErr = QString( "   Dwelling unit #%1 ('%2') inputs include non-zero Count and floor area, but no valid Zone assignment." ).arg( QString::number(iDUIdx), sOldDUName );
										psaWarningsForUser->push_back( sDUTempErr );
									}
									else if ((pZnObj == NULL || iZnObjIdx < 0) && psaWarningsForUser)
									{	sDUTempErr = QString( "   Error retrieving assigned Zone '%1' for dwelling unit #%2 ('%3')." ).arg( sOldDUZone, QString::number(iDUIdx), sOldDUName );
										psaWarningsForUser->push_back( sDUTempErr );
									}
									if (!sOldDUZone.isEmpty() && pZnObj && iZnObjIdx >= 0)
									{	long lNumBedrooms=0;
										BEMPX_GetInteger( lDBID_Proj_UnitNumBedrooms+iDUIdx-1, lNumBedrooms );			assert( lNumBedrooms > 0 || lZonalControl > 0 );
										QString sNewDUTName = "DUT-", sNewDUName;
										if (sOldDUName.isEmpty())
										{	sNewDUName = QString(  "DU%1 %2 bedroom(s), %3 ft2"  ).arg( QString::number(iNumDUTCreated+1), QString::number(lNumBedrooms), QString::number(fFlrArea) );
											sNewDUTName = QString( "DUT%1 %2 bedroom(s), %3 ft2" ).arg( QString::number(iNumDUTCreated+1), QString::number(lNumBedrooms), QString::number(fFlrArea) );
										}
										else
										{	sNewDUName   = sOldDUName;
											sNewDUTName += sOldDUName;
										}
										BEMObject* pDUTObj = BEMPX_CreateObject( iDUTCID, sNewDUTName.toLocal8Bit().constData() );
										int iDUTObjIdx = (pDUTObj==NULL ? -1 : BEMPX_GetObjectIndex( pDUTObj->getClass(), pDUTObj ));
										if ((pDUTObj == NULL || iDUTObjIdx < 0) && psaWarningsForUser)
										{	sDUTempErr = QString( "   Error creating new DwellUnitType object '%1' for dwelling unit #%2 ('%3')." ).arg( sNewDUTName, QString::number(iDUIdx), sOldDUName );
											psaWarningsForUser->push_back( sDUTempErr );
										}
										if (pDUTObj && iDUTObjIdx >= 0)
										{	iNumDUTCreated++;
											BEMObject* pDUObj = BEMPX_CreateObject( iDUCID, sNewDUName.toLocal8Bit().constData(), pZnObj );
											int iDUObjIdx = (pDUObj==NULL ? -1 : BEMPX_GetObjectIndex( pDUObj->getClass(), pDUObj ));
											if ((pDUObj == NULL || iDUObjIdx < 0) && psaWarningsForUser)
											{	sDUTempErr = QString( "   Error creating new DwellUnit object '%1' for dwelling unit #%2 ('%3')." ).arg( sNewDUName, QString::number(iDUIdx), sOldDUName );
												psaWarningsForUser->push_back( sDUTempErr );
											}
											if (pDUObj && iDUObjIdx >= 0)
											{
									// Set data to new DwellUnitType object
												BEMPX_SetBEMData( lDBID_DUT_NumBedrooms, BEMP_Int, &lNumBedrooms, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												BEMPX_SetBEMData( lDBID_DUT_CondFlrArea, BEMP_Flt, &fFlrArea    , BEMO_User, iDUTObjIdx, BEMS_UserDefined );

											// confirm that appliance (other than washer/dryer) zone assignments are consistent w/ parent Zone
												BEMObject *pRefrigZoneObj=NULL, *pCookZoneObj=NULL, *pDishZoneObj=NULL;
												BEMPX_GetObject( lDBID_Proj_ApplRefrigZone+iDUIdx-1, pRefrigZoneObj );
												BEMPX_GetObject( lDBID_Proj_ApplCookZone  +iDUIdx-1, pCookZoneObj );
												BEMPX_GetObject( lDBID_Proj_ApplDishZone  +iDUIdx-1, pDishZoneObj );
												if (pRefrigZoneObj && pRefrigZoneObj != pZnObj && psaWarningsForUser)
												{	sDUTempErr = QString( "   Refrigerator zone assignment of '%1' is inconsistent with the parent zone '%2' for dwelling unit '%3' while processing dwelling unit #%4 ('%5')." ).arg( pRefrigZoneObj->getName(), pZnObj->getName(), pDUObj->getName(), QString::number(iDUIdx), sOldDUName );
													psaWarningsForUser->push_back( sDUTempErr );
												}
												if (pCookZoneObj && pCookZoneObj != pZnObj && psaWarningsForUser)
												{	sDUTempErr = QString( "   Cooking equipment zone assignment of '%1' is inconsistent with the parent zone '%2' for dwelling unit '%3' while processing dwelling unit #%4 ('%5')." ).arg( pCookZoneObj->getName(), pZnObj->getName(), pDUObj->getName(), QString::number(iDUIdx), sOldDUName );
													psaWarningsForUser->push_back( sDUTempErr );
												}
												if (pDishZoneObj && pDishZoneObj != pZnObj && psaWarningsForUser)
												{	sDUTempErr = QString( "   Dishwasher zone assignment of '%1' is inconsistent with the parent zone '%2' for dwelling unit '%3' while processing dwelling unit #%4 ('%5')." ).arg( pDishZoneObj->getName(), pZnObj->getName(), pDUObj->getName(), QString::number(iDUIdx), sOldDUName );
													psaWarningsForUser->push_back( sDUTempErr );
												}

									// Set data to new DwellUnit object
												BEMPX_SetBEMData( lDBID_DU_DwellUnitTypeRef, BEMP_Str, (void*) pDUTObj->getName().toLocal8Bit().constData(), BEMO_User, iDUObjIdx, BEMS_UserDefined );
												BEMPX_SetBEMData( lDBID_DU_Count           , BEMP_Int, &lCount, BEMO_User, iDUObjIdx, BEMS_UserDefined );

											// address washer and dryer presence and zone assignments
												long lHaveAppl=0;
												BEMObject *pWasherZoneObj=NULL, *pDryerZoneObj=NULL;
												if (BEMPX_GetInteger( lDBID_Proj_Appl_HaveWasher+iDUIdx-1, lHaveAppl ))
												{	BEMPX_SetBEMData( lDBID_DUT_HaveWasher, BEMP_Int, &lHaveAppl, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
													if (lHaveAppl > 0)
													{	BEMPX_GetObject( lDBID_Proj_ApplWasherZone+iDUIdx-1, pWasherZoneObj );			assert( pWasherZoneObj );
														if (pWasherZoneObj)
															BEMPX_SetBEMData( lDBID_DU_WasherZoneRef, BEMP_Str, (void*) pWasherZoneObj->getName().toLocal8Bit().constData(), BEMO_User, iDUObjIdx, BEMS_UserDefined );
												}	}
												if (BEMPX_GetInteger( lDBID_Proj_Appl_HaveDryer+iDUIdx-1, lHaveAppl ))
												{	BEMPX_SetBEMData( lDBID_DUT_HaveDryer, BEMP_Int, &lHaveAppl, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
													if (lHaveAppl > 0)
													{	BEMPX_GetObject( lDBID_Proj_ApplDryerZone+iDUIdx-1, pDryerZoneObj );			assert( pDryerZoneObj );
														if (pDryerZoneObj)
															BEMPX_SetBEMData( lDBID_DU_DryerZoneRef, BEMP_Str, (void*) pDryerZoneObj->getName().toLocal8Bit().constData(), BEMO_User, iDUObjIdx, BEMS_UserDefined );
														if (BEMPX_GetInteger( lDBID_Proj_ApplDryerFuel+iDUIdx-1, lHaveAppl ))
															BEMPX_SetBEMData( lDBID_DUT_DryerFuel, BEMP_Int, &lHaveAppl, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												}	}

											// HVAC system data
												long lZoneType, lHVACSysStatus, lCountOfOne=1;
												if (BEMPX_GetInteger( lDBID_Zone_Type, lZoneType, 20 /*default*/, -1, iZnObjIdx ) && lZoneType < 10)
												{	// zone is conditioned, so gather and transfer zone HVAC settings
													BEMPX_GetInteger( lDBID_Zone_HVACSysStatus, lHVACSysStatus, 3 /*default*/, -1, iZnObjIdx );
													long lDBID_HVACSys = (lHVACSysStatus == 1 ? lDBID_Zone_exHVACSystem  :
																				(lHVACSysStatus == 2 ? lDBID_Zone_AltHVACSystem : lDBID_Zone_HVACSystem ));
													BEMObject* pHVACSysObj = NULL;		long lHVACSysType = -1;
													if (lDBID_HVACSys > 0)
														BEMPX_GetObject( lDBID_HVACSys, pHVACSysObj, -1, iZnObjIdx );
													int iHVACSysObjIdx = (pHVACSysObj==NULL ? -1 : BEMPX_GetObjectIndex( pHVACSysObj->getClass(), pHVACSysObj ));
													if (iHVACSysObjIdx >= 0)
														BEMPX_GetInteger( lDBID_HVACSys_Type, lHVACSysType, -1 /*default*/, -1, iHVACSysObjIdx );
													sDUTempErr.clear();
													if (lDBID_HVACSys < 1)
														sDUTempErr = QString( "   Unknown or unrecognized HVACSysStatus for Zone '%1' while processing dwelling unit #%2 ('%3')." ).arg( sOldDUZone, QString::number(iDUIdx), sOldDUName );
													else if (pHVACSysObj == NULL || iHVACSysObjIdx < 0)
														sDUTempErr = QString( "   Unable to retrieve HVACSys object assigned to Zone '%1' while processing dwelling unit #%2 ('%3')." ).arg( sOldDUZone, QString::number(iDUIdx), sOldDUName );
													else if (lHVACSysType != 1 && lHVACSysType != 2)
														sDUTempErr = QString( "   Type (%1) of HVACSys object assigned to Zone '%2' not compatible with new dwelling unit HVAC options (processing dwelling unit #%3 ('%4'))." ).arg( QString::number(lHVACSysType), sOldDUZone, QString::number(iDUIdx), sOldDUName );
													if (!sDUTempErr.isEmpty() && psaWarningsForUser)
														psaWarningsForUser->push_back( sDUTempErr );
													if (sDUTempErr.isEmpty())
													{	// transfer HVACSys data to DwellUnitType
														BEMPX_SetBEMData( lDBID_DUT_HVACSysType, BEMP_Int, &lHVACSysType, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
														long lNumEqps, lEqpCount, lDUTEqpIdx;
														BEMObject* pEqpObj;
														if (lHVACSysType == 2)
														{	// transfer HEAT PUMP assignments
															BEMPX_GetInteger( lDBID_HVACSys_NumHtPumpSystemTypes, lNumEqps, -1 /*default*/, -1, iHVACSysObjIdx );
															if (lNumEqps < 0)
																lNumEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_HVACSys_HtPumpSystem ), BEMPX_GetPropertyID( lDBID_HVACSys_HtPumpSystem ) );
															long iMaxHtPumpEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_DUT_HVACHtPumpRef ), BEMPX_GetPropertyID( lDBID_DUT_HVACHtPumpRef ) );		assert( iMaxHtPumpEqps > 0 );
															lDUTEqpIdx = 0;
															for (int iEqpIdx=0; iEqpIdx < lNumEqps; iEqpIdx++)
																if (	BEMPX_GetObject(  lDBID_HVACSys_HtPumpSystem      + iEqpIdx, pEqpObj  ,    -1, iHVACSysObjIdx ) && pEqpObj &&
																		BEMPX_GetInteger( lDBID_HVACSys_HtPumpSystemCount + iEqpIdx, lEqpCount, 0, -1, iHVACSysObjIdx ) && lEqpCount > 0 )
																{	lDUTEqpIdx++;
																	if (lDUTEqpIdx <= iMaxHtPumpEqps)
																	{	BEMPX_SetBEMData( lDBID_DUT_HVACHtPumpRef    + lDUTEqpIdx-1, BEMP_Str, (void*) pEqpObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												//						BEMPX_SetBEMData( lDBID_DUT_HtPumpEquipCount + lDUTEqpIdx-1, BEMP_Int, &lEqpCount, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																		BEMPX_SetBEMData( lDBID_DUT_HtPumpEquipCount + lDUTEqpIdx-1, BEMP_Int, &lCountOfOne, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																}	}
															if (lDUTEqpIdx > iMaxHtPumpEqps)
															{	if (psaWarningsForUser)
																{	sDUTempErr = QString( "   Too many Heat Pump assignments (%1 vs. max of %2) present in HVACSys '%3' to transfer to new DwellUnitType object '%4' while processing dwelling unit #%5 ('%6')." ).arg( QString::number(lDUTEqpIdx), QString::number(iMaxHtPumpEqps), pHVACSysObj->getName(), pDUTObj->getName(), QString::number(iDUIdx), sOldDUName );
																	psaWarningsForUser->push_back( sDUTempErr );
																}
																lDUTEqpIdx = iMaxHtPumpEqps;
															}
															BEMPX_SetBEMData( lDBID_DUT_NumHtPumpEquipTypes, BEMP_Int, &lDUTEqpIdx, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
														}
														else
														{	// transfer HVACHeat equipment assignments
															BEMPX_GetInteger( lDBID_HVACSys_NumHeatSystemTypes, lNumEqps, -1 /*default*/, -1, iHVACSysObjIdx );
															if (lNumEqps < 0)
																lNumEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_HVACSys_HeatSystem ), BEMPX_GetPropertyID( lDBID_HVACSys_HeatSystem ) );
															long iMaxHeatEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_DUT_HVACHeatRef ), BEMPX_GetPropertyID( lDBID_DUT_HVACHeatRef ) );		assert( iMaxHeatEqps > 0 );
															lDUTEqpIdx = 0;
															for (int iEqpIdx=0; iEqpIdx < lNumEqps; iEqpIdx++)
																if (	BEMPX_GetObject(  lDBID_HVACSys_HeatSystem      + iEqpIdx, pEqpObj  ,    -1, iHVACSysObjIdx ) && pEqpObj &&
																		BEMPX_GetInteger( lDBID_HVACSys_HeatSystemCount + iEqpIdx, lEqpCount, 0, -1, iHVACSysObjIdx ) && lEqpCount > 0 )
																{	lDUTEqpIdx++;
																	if (lDUTEqpIdx <= iMaxHeatEqps)
																	{	BEMPX_SetBEMData( lDBID_DUT_HVACHeatRef    + lDUTEqpIdx-1, BEMP_Str, (void*) pEqpObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												//						BEMPX_SetBEMData( lDBID_DUT_HeatEquipCount + lDUTEqpIdx-1, BEMP_Int, &lEqpCount, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																		BEMPX_SetBEMData( lDBID_DUT_HeatEquipCount + lDUTEqpIdx-1, BEMP_Int, &lCountOfOne, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																}	}
															if (lDUTEqpIdx > iMaxHeatEqps)
															{	if (psaWarningsForUser)
																{	sDUTempErr = QString( "   Too many Heating equipment assignments (%1 vs. max of %2) present in HVACSys '%3' to transfer to new DwellUnitType object '%4' while processing dwelling unit #%5 ('%6')." ).arg( QString::number(lDUTEqpIdx), QString::number(iMaxHeatEqps), pHVACSysObj->getName(), pDUTObj->getName(), QString::number(iDUIdx), sOldDUName );
																	psaWarningsForUser->push_back( sDUTempErr );
																}
																lDUTEqpIdx = iMaxHeatEqps;
															}
															BEMPX_SetBEMData( lDBID_DUT_NumHeatEquipTypes, BEMP_Int, &lDUTEqpIdx, BEMO_User, iDUTObjIdx, BEMS_UserDefined );

															// transfer HVACCool equipment assignments
															BEMPX_GetInteger( lDBID_HVACSys_NumCoolSystemTypes, lNumEqps, -1 /*default*/, -1, iHVACSysObjIdx );
															if (lNumEqps < 0)
																lNumEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_HVACSys_CoolSystem ), BEMPX_GetPropertyID( lDBID_HVACSys_CoolSystem ) );
															long iMaxCoolEqps = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lDBID_DUT_HVACCoolRef ), BEMPX_GetPropertyID( lDBID_DUT_HVACCoolRef ) );		assert( iMaxCoolEqps > 0 );
															lDUTEqpIdx = 0;
															for (int iEqpIdx=0; iEqpIdx < lNumEqps; iEqpIdx++)
																if (	BEMPX_GetObject(  lDBID_HVACSys_CoolSystem      + iEqpIdx, pEqpObj  ,    -1, iHVACSysObjIdx ) && pEqpObj &&
																		BEMPX_GetInteger( lDBID_HVACSys_CoolSystemCount + iEqpIdx, lEqpCount, 0, -1, iHVACSysObjIdx ) && lEqpCount > 0 )
																{	lDUTEqpIdx++;
																	if (lDUTEqpIdx <= iMaxCoolEqps)
																	{	BEMPX_SetBEMData( lDBID_DUT_HVACCoolRef    + lDUTEqpIdx-1, BEMP_Str, (void*) pEqpObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												//						BEMPX_SetBEMData( lDBID_DUT_CoolEquipCount + lDUTEqpIdx-1, BEMP_Int, &lEqpCount, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																		BEMPX_SetBEMData( lDBID_DUT_CoolEquipCount + lDUTEqpIdx-1, BEMP_Int, &lCountOfOne, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
																}	}
															if (lDUTEqpIdx > iMaxCoolEqps)
															{	if (psaWarningsForUser)
																{	sDUTempErr = QString( "   Too many Cooling equipment assignments (%1 vs. max of %2) present in HVACSys '%3' to transfer to new DwellUnitType object '%4' while processing dwelling unit #%5 ('%6')." ).arg( QString::number(lDUTEqpIdx), QString::number(iMaxCoolEqps), pHVACSysObj->getName(), pDUTObj->getName(), QString::number(iDUIdx), sOldDUName );
																	psaWarningsForUser->push_back( sDUTempErr );
																}
																lDUTEqpIdx = iMaxCoolEqps;
															}
															BEMPX_SetBEMData( lDBID_DUT_NumCoolEquipTypes, BEMP_Int, &lDUTEqpIdx, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
														}
														// now transfer Distrib & Fan assignments
														if (BEMPX_GetObject( lDBID_HVACSys_DistribSystem, pEqpObj, -1, iHVACSysObjIdx ) && pEqpObj)
															BEMPX_SetBEMData( lDBID_DUT_HVACDistRef, BEMP_Str, (void*) pEqpObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
														if (BEMPX_GetObject( lDBID_HVACSys_Fan          , pEqpObj, -1, iHVACSysObjIdx ) && pEqpObj)
															BEMPX_SetBEMData( lDBID_DUT_HVACFanRef , BEMP_Str, (void*) pEqpObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
                                 	}	}

											// DHW system data
												long lDHWStatus;
												BEMObject *pDHWSys1Obj=NULL, *pDHWSys2Obj=NULL;
												BEMPX_GetInteger( lDBID_Zone_DHWSys1Status, lDHWStatus, 3 /*default to New*/ );
												long lDBID_ZoneDHWRef = (lDHWStatus == 1 ? lDBID_Zone_exDHWSys1  :
																				(lDHWStatus == 2 ? lDBID_Zone_AltDHWSys1 : lDBID_Zone_DHWSys1 ));
												if (lDBID_ZoneDHWRef > 0)
													BEMPX_GetObject( lDBID_ZoneDHWRef, pDHWSys1Obj, -1, iZnObjIdx );
												// second DHW system assignment...
												BEMPX_GetInteger( lDBID_Zone_DHWSys2Status, lDHWStatus, 3 /*default to New*/ );
												lDBID_ZoneDHWRef = (lDHWStatus == 1 ? lDBID_Zone_exDHWSys2  :
																		 (lDHWStatus == 2 ? lDBID_Zone_AltDHWSys2 : lDBID_Zone_DHWSys2 ));
												if (lDBID_ZoneDHWRef > 0)
												{	if (pDHWSys1Obj)
														BEMPX_GetObject( lDBID_ZoneDHWRef, pDHWSys2Obj, -1, iZnObjIdx );
													else
														BEMPX_GetObject( lDBID_ZoneDHWRef, pDHWSys1Obj, -1, iZnObjIdx );
												}
												long lNumDHWRefs = (pDHWSys1Obj && pDHWSys2Obj ? 2 : (pDHWSys1Obj ? 1 : 0 ));
												BEMPX_SetBEMData( lDBID_DUT_NumDHWSysTypes, BEMP_Int, &lNumDHWRefs, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												if (pDHWSys1Obj)
													BEMPX_SetBEMData( lDBID_DUT_DHWSysRef  , BEMP_Str, (void*) pDHWSys1Obj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												if (pDHWSys2Obj)
													BEMPX_SetBEMData( lDBID_DUT_DHWSysRef+1, BEMP_Str, (void*) pDHWSys2Obj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );

											// IAQ Ventilation data
												long lIAQOption=0;
												BEMPX_GetInteger( lDBID_Proj_UnitIAQOption+iDUIdx-1, lIAQOption );
												if (lIAQOption > 0 && lIAQOption < 4)
													BEMPX_SetBEMData( lDBID_DUT_IAQOption, BEMP_Int, &lIAQOption, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
												BEMObject *pIAQZoneObj=NULL;
												if (lIAQOption == 1)	//	"Default Minimum IAQ Fan"
												{	// check for and report IAQ zone assignment inconsistent w/ parent Zone
													BEMPX_GetObject( lDBID_Proj_UnitIAQZone1+iDUIdx-1, pIAQZoneObj );
													if (pIAQZoneObj && pIAQZoneObj != pZnObj && psaWarningsForUser)
													{	sDUTempErr = QString( "   IAQ ventilation zone assignment of '%1' is inconsistent with the parent zone '%2' for dwelling unit '%3' while processing dwelling unit #%4 ('%5')." ).arg( pIAQZoneObj->getName(), pZnObj->getName(), pDUObj->getName(), QString::number(iDUIdx), sOldDUName );
														psaWarningsForUser->push_back( sDUTempErr );
												}	}
												else if (lIAQOption == 2)	//	"Specify Individual IAQ Fans"
												{	// transfer IAQ fan references & counts and check zone assignments
													BEMObject *pIAQFanObj=NULL;		long lIAQFanCount;
													long lDBID_IAQFan[]      = { lDBID_Proj_UnitIAQFan1, lDBID_Proj_UnitIAQFan2, lDBID_Proj_UnitIAQFan3, lDBID_Proj_UnitIAQFan4 };
													long lDBID_IAQFanCount[] = { lDBID_Proj_UnitIAQFanCnt1, lDBID_Proj_UnitIAQFanCnt2, lDBID_Proj_UnitIAQFanCnt3, lDBID_Proj_UnitIAQFanCnt4 };
													long lDBID_IAQZone[]     = { lDBID_Proj_UnitIAQZone1, lDBID_Proj_UnitIAQZone2, lDBID_Proj_UnitIAQZone3, lDBID_Proj_UnitIAQZone4 };
													for (int iIAQIdx=0; iIAQIdx < 4; iIAQIdx++)
													{	if (	BEMPX_GetObject(  lDBID_IAQFan[     iIAQIdx]+iDUIdx-1, pIAQFanObj   ) && pIAQFanObj &&
																BEMPX_GetInteger( lDBID_IAQFanCount[iIAQIdx]+iDUIdx-1, lIAQFanCount ) && lIAQFanCount > 0 )
														{	BEMPX_SetBEMData( lDBID_DUT_IAQFanRef + iIAQIdx, BEMP_Str, (void*) pIAQFanObj->getName().toLocal8Bit().constData(), BEMO_User, iDUTObjIdx, BEMS_UserDefined );
															BEMPX_SetBEMData( lDBID_DUT_IAQFanCnt + iIAQIdx, BEMP_Int, &lIAQFanCount, BEMO_User, iDUTObjIdx, BEMS_UserDefined );
															// check for and report IAQ zone assignment inconsistent w/ parent Zone
															BEMPX_GetObject( lDBID_IAQZone[iIAQIdx]+iDUIdx-1, pIAQZoneObj );
															if (pIAQZoneObj && pIAQZoneObj != pZnObj && psaWarningsForUser)
															{	sDUTempErr = QString( "   IAQ ventilation zone assignment of '%1' (fan #%2) is inconsistent with the parent zone '%3' for dwelling unit '%4' while processing dwelling unit #%5 ('%6')." ).arg( pIAQZoneObj->getName(), QString::number(iIAQIdx+1), pZnObj->getName(), pDUObj->getName(), QString::number(iDUIdx), sOldDUName );
																psaWarningsForUser->push_back( sDUTempErr );
												}	}	}	}
										}	}
							}	}	}
						}	// end of for 1-16 possible unit types
				}	}

				if (psaWarningsForUser && iDUWarnStrSize == psaWarningsForUser->size())
				{	// REMOVE initial warning/error string if no strings added to array since header string added
					psaWarningsForUser->removeAt( iDUWarnStrSize-1 );
					if (iNumDUTCreated > 0)
					{	sDUTempErr = QString( "Dwelling unit data in this project has been updated to a revised multifamily data model - %1 DwellUnitType & DwellUnit objects created." ).arg( QString::number(iNumDUTCreated) );
						psaWarningsForUser->push_back( sDUTempErr );
						psaWarningsForUser->push_back( "HVAC equipment assignment for multifamily buildings is now done for each individual DwellUnitType.  Review these assignments and counts in the DwellUnitType dialog to ensure proper HVAC equipment simulation and reporting." );
				}	}
			}	// if the model needs to be converted from old (<= v2) to new (v3+) dwelling unit inputs

		// SAC 6/28/17 - added evaluation of rulelist to handle 1-time LoadModel processing
			if (BEMPX_RulelistExists( "LoadModelAdjustments" ))
			{	QString sLMAErrMsg;
				int iLMAEvalRetVal = LocalEvaluateRuleset( sLMAErrMsg, 7, "LoadModelAdjustments", FALSE /*bVerbose*/, NULL /*pCompRuleDebugInfo*/ );
				if (iLMAEvalRetVal != 0)
				{	iRetVal = 7;
					if (psaWarningsForUser)
					{	if (sLMAErrMsg.isEmpty())
							sLMAErrMsg = QString( "ERROR:  Error encountered evaluating rulelist '%1'" ).arg( "LoadModelAdjustments" );
						psaWarningsForUser->push_back( sLMAErrMsg );
			}	}	}
		}
		BEMPX_RefreshLogFile();	// SAC 5/19/14
	}

	return iRetVal;
}




