// CUAC_Analysis.cpp : Defines the CUAC (Calif. Utility Allowance Calculator) analysis routine(s)
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

#include "stdafx.h"

//#include <direct.h>           // Directory related system routines
//#include <stdio.h>
#include <io.h>
#include <strsafe.h>    // SAC 10/29/24

//#include <QtGui>
// TO DO  #include <openssl/crypto.h>   // SAC 10/16/13

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProcObject.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CSERunMgr.h"
#include "BEMCmpMgrCom.h"
#include "BEMCM_I.h"
#include "OpenStudioInterface.h"
#include "ModelkitInterface.h"      // SAC 06/16/22
#include "memLkRpt.h"
#include "BEMCmpMgrProgress.h"      // SAC 06/20/22
#include "CUAC_Analysis.h"    
#include "CUACToolMiner\CUACToolMiner.h"    


////////////////////////////////////////////////////////////////////////////////
static int iNumDaysInMonth[12]     = {  31,    28,    31,    30,    31,    30,    31,    31,    30,    31,    30,    31   };
static bool bCoolingMonth[12]      = { false, false, false,  true,  true,  true,  true,  true,  true,  true, false, false };
static const char* pszMoLabels[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

#define  NumDwellingMeters   7
#define  NumInitialEnduses  14
static const char* pszCUACMeters[2][NumDwellingMeters]  = { { "Elec_0bedrm", "Elec_1bedrm", "Elec_2bedrm", "Elec_3bedrm", "Elec_4bedrm", "Elec_5bedrm", "Elec_6bedrm" },
                                                            {  "Gas_0bedrm",  "Gas_1bedrm",  "Gas_2bedrm",  "Gas_3bedrm",  "Gas_4bedrm",  "Gas_5bedrm",  "Gas_6bedrm" } };
static const char* pszInitialCUACEnduses[NumInitialEnduses+1]  = { "Cooling", "Heating", "DHW", "Ventilation", "HVAC Other", "Plug Loads", "Lighting", "Refrigerator", "Dishwasher", "Dryer", "Washer", "Cooking", "Photovoltaics", "Battery", NULL };
                                                               //       0        1        2        3              4              5           6           7                 8           9        10          11          12             13
// RES meters & enduses - SAC 06/01/24 (res tic #1378)
#define  NumInitialResEnduses  24
static const char* pszCUACResMeters[3]                               = {       "MtrElec",   "MtrNatGas",   "MtrOther"  };
static const char* pszInitialCUACResEnduses[NumInitialResEnduses+1]  = { "Clg", "Htg", "HPBU", "Dhw", "DhwBU", "DhwMFL", "FanC", "FanH", "FanV", "Fan", "Aux", "Proc", "Lit", "Rcp", "Ext", "Refr", "Dish", "Dry", "Wash", "Cook", "User1", "User2", "BT", "PV", NULL };
                                                                  //      *0     *1       2     *3       4         5        6       7      *8      9      10     11     *12    *13     14    *15     *16     *17    *18     *19       20       21    *22   *23
// special Res enduse processing:  >=0 sum into that init res enduse / -1 distribute between Clg & Htg init res enduses / -99 no action (primary enduse)
static int iaCUACResEnduseActions[NumInitialResEnduses]              = {  -99,   -99,     1,    -99,     3,        3,       0,      1,     -99,    1,      1,    13,    -99,   -99,    13,   -99,    -99,    -99,   -99,    -99,       0,       3,   -99,  -99  }; 

// CUAC reporting enduses:    / 12->13 - SAC 12/12/24
#define  NumCUACEnduses  13
static const char* pszOldCUACEnduseProps[NumCUACEnduses+1]    = { "Cooking", "Cooling",    "DHW",   "Dishwasher",  "Dryer",  "Heating",      NULL,   "Lighting", "PlugLoads", "Refrigerator", "Washer", "PVGeneration", "Battery",  NULL  };
static const char* pszCUACRptEnduseAbbrevs[NumCUACEnduses+1]  = {  "Ckg",      "Clg",      "DHW",      "Dish",     "Dryer",    "Htg",      "IAQVent",  "Ltg",      "PlugLds",  "Rfrg",         "Wash",     "PVSys",      "Batt",    NULL  };   // added Batt - SAC 12/12/24
static int iaInitToRptsEnduseMap[NumCUACEnduses+1]            = {    11,         0,          2,           8,          9,         1,            3,        6,            5,        7,              10,          12,          13,        -1  };
static int iaResInitToRptsEnduseMap[NumCUACEnduses+1]         = {    19,         0,          3,          16,         17,         1,            8,       12,           13,       15,              18,          23,          22,        -1  };   // SAC 06/01/24 (res tic #1378)
static bool baHaveFuelEnduseHrlyResults[2][NumCUACEnduses]  = { {   true,       true,       true,       true,       true,       true,       true,       true,       true,       true,           true,       true,        true      },
                                                                {   true,      false,       true,      false,       true,       true,      false,      false,      false,      false,          false,      false,       false      }  };
static const char* pszCUACCSVElecEnduseLabels                 =    "Cooking,Cooling,DHW,Dishwasher,Dryer,Heating,IAQ Vent,Lighting,Plug Loads,Refrigerator,Washer,PV,Batt,";   // added Batt - SAC 12/12/24
static const char* pszCUACCSVGasEnduseLabels                  =    "Cooking,DHW,Dryer,Heating,";
static const char* pszCUACCSVUnitTypeLabels[]                 = {  "Studio", "1 Bedroom", "2 Bedroom", "3 Bedroom", "4 Bedroom", "5 Bedroom", "6 Bedroom"  };

static bool LoadCUACUtilityRate( CUACUtilityRate& rate, int iRateObjIdx, int iBEMProcIdx, QString& qsErrMsg );


////////////////////////////////////////////////////////////////////////////////

bool G2MonthSeasonPeriodOverlap( int iSeasPerObjIdx, int iMo, int iMoHrStart, int iMoHrEnd, int& iSeasMoHrStart, int& iSeasMoHrEnd, int iCUAC_BEMProcIdx, QString& sErrMsg )
{  bool bRetVal = false;
   int iSpecVal, iErr;
   int iCID_SeasonTimePeriod = BEMPX_GetDBComponentID( "CPR_SeasonTimePeriod" );
   long lStartDay   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "StartDay",   iCID_SeasonTimePeriod ), iSpecVal, iErr, iSeasPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
   long lStartMonth = BEMPX_GetInteger( BEMPX_GetDatabaseID( "StartMonth", iCID_SeasonTimePeriod ), iSpecVal, iErr, iSeasPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
   long lEndDay     = BEMPX_GetInteger( BEMPX_GetDatabaseID( "EndDay",     iCID_SeasonTimePeriod ), iSpecVal, iErr, iSeasPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
   long lEndMonth   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "EndMonth",   iCID_SeasonTimePeriod ), iSpecVal, iErr, iSeasPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
   if (lStartDay < 0 || lStartMonth < 0 || lEndDay < 0 || lEndMonth < 0)
      sErrMsg = QString( "G2MonthSeasonPeriodOverlap() error loading start/end day/month data for SeasonTimePeriod '%1' (%2)" ).arg( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_SeasonTimePeriod ), iSpecVal, iErr, iSeasPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ), QString::number( iSeasPerObjIdx+1 ) );
   else
   {  int iDaysInMo = (iMoHrEnd - iMoHrStart)/24;
      if (lStartMonth > lEndMonth || (lStartMonth == lEndMonth && lStartDay > lEndDay))
      {  // period wraps around from end of year into beginning of year
         if (iMo < lEndMonth || iMo > lStartMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart;                          iSeasMoHrEnd = iMoHrEnd;
         }
         else if (iMo == lEndMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart;                          iSeasMoHrEnd = iMoHrStart + (lEndDay * 24) - 1;    // added trailing -1 - SAC 12/12/23
         }
         else if (iMo == lStartMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart + ((lStartDay-1) * 24);   iSeasMoHrEnd = iMoHrEnd;
         }
      }
      else
      {  // period DOES NOT wrap around from end of year into beginning of year
         if (iMo > lStartMonth && iMo < lEndMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart;                          iSeasMoHrEnd = iMoHrEnd;
         }
         else if (iMo == lEndMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart;                          iSeasMoHrEnd = iMoHrStart + (lEndDay * 24) - 1;    // added trailing -1 - SAC 12/12/23
         }
         else if (iMo == lStartMonth)
         {  bRetVal = true;         iSeasMoHrStart = iMoHrStart + ((lStartDay-1) * 24);   iSeasMoHrEnd = iMoHrEnd;
         }
   }  }
   return bRetVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

double DayHourlySum( double* pdHrly )     // SAC 01/16/25
{  double dSum = 0.0;
   for (int iHr=0; iHr<24; iHr++)
      dSum += pdHrly[iHr];
   return dSum;
}

double AdjustJA13HPWHDayUseProfile( double* pdHrlyUse, int iFirstPeakHr, int iPeakDuration,
                                    double dPeakReductionFrac, double dTargetOffPeakUseMult,
                                    double dMaxOffPeakUseMult, int iEarliestHrMod, double dTargetUseTotIncrease )    // SAC 01/16/25  // SAC 01/22/25
{  assert( pdHrlyUse != NULL );
   assert( iFirstPeakHr >= 0 && iFirstPeakHr < 23 );
   assert( iPeakDuration > 0 && iPeakDuration < (24-iFirstPeakHr) );
   assert( dPeakReductionFrac < 1.0 && dPeakReductionFrac >= 0.0 );
   assert( dTargetOffPeakUseMult > 1.0 );
   assert( dMaxOffPeakUseMult >= dTargetOffPeakUseMult );
   assert( iEarliestHrMod >= 0 && iEarliestHrMod < iFirstPeakHr );
   assert( dTargetUseTotIncrease > 0.0 );
   double dRetVal = -1;
   if (pdHrlyUse != NULL &&  iFirstPeakHr >= 0 && iFirstPeakHr < 23 &&
       iPeakDuration > 0 && iPeakDuration < (24-iFirstPeakHr) &&
       dPeakReductionFrac < 1.0 && dPeakReductionFrac >= 0.0 &&
       dTargetOffPeakUseMult > 1.0 && dTargetUseTotIncrease > 0.0 &&
       iEarliestHrMod >= 0 && iEarliestHrMod < iFirstPeakHr )
   {  int hr, i2ndRedEndHr=-1, iOrigPeakDur = iPeakDuration, i1stRedEndHr = iFirstPeakHr + iPeakDuration-1;
      if (i1stRedEndHr > 23)
      {  assert( false );
         // peak period extends beyond end of day - shouldn't ever happen, but in case...
         double dTargetUseTotIncMult = 1.0 - ((double) (i1stRedEndHr - 23) / (double) iPeakDuration);
         dTargetUseTotIncrease *= dTargetUseTotIncMult;
         iPeakDuration -= (i1stRedEndHr - 23);
         i1stRedEndHr = 23;
      }
      if (iPeakDuration > 4)
      {  // reduce savings fracs for peak hours past first 4
         i2ndRedEndHr = i1stRedEndHr;
         i1stRedEndHr = iFirstPeakHr + 4-1;
      }

      double dTargetOffPeakShiftedUse = dTargetUseTotIncrease;
      for (hr = iFirstPeakHr; hr <= i1stRedEndHr; hr++)
         if (pdHrlyUse[hr] > 0.0)
         {  dTargetOffPeakShiftedUse += (pdHrlyUse[hr] * (1.0 - dPeakReductionFrac));
            pdHrlyUse[hr] *= dPeakReductionFrac;
         }
      if (i2ndRedEndHr > 0)
         for (hr = i1stRedEndHr+1; hr <= i2ndRedEndHr; hr++)
         {  dPeakReductionFrac = (1.0 + dPeakReductionFrac) / 2.0;   // increase dPeakReductionFrac w/ each passing hour to value half way between it and 1.0
            if (pdHrlyUse[hr] > 0.0)
            {  dTargetOffPeakShiftedUse += (pdHrlyUse[hr] * (1.0 - dPeakReductionFrac));
               pdHrlyUse[hr] *= dPeakReductionFrac;
         }  }

      // we've reduced OnPeak energy above, now shift that to prior hours (below)
      // start by identifying what off-peak multipler would be required to shift various #s of off-peak hrs (to equal total increase use desired)
      int iNumOffPkHrsToShift=0, iNumOffPeakHrs = std::min( iOrigPeakDur+1, 4 );
      double dOffPkSum[4] = { 0.0, 0.0, 0.0, 0.0 }, dOffPkAdjMults[4] = { 0.0, 0.0, 0.0, 0.0 }, dOffPkAdjMultsDeltas[4] = { -1.0, -1.0, -1.0, -1.0 };
      if (iFirstPeakHr-1 >= 0)
      {  dOffPkSum[0] = pdHrlyUse[iFirstPeakHr-1];
         if (dOffPkSum[0] > 0.0)
         {  dOffPkAdjMults[0] = (dOffPkSum[0] + dTargetOffPeakShiftedUse) / dOffPkSum[0];
            dOffPkAdjMultsDeltas[0] = dOffPkAdjMults[0] - dTargetOffPeakUseMult;
         }
         if (iNumOffPeakHrs > 1 && iFirstPeakHr-2 >= 0)
         {  dOffPkSum[1] = dOffPkSum[0] + pdHrlyUse[iFirstPeakHr-2];
            if (dOffPkSum[1] > 0.0)
            {  dOffPkAdjMults[1] = (dOffPkSum[1] + dTargetOffPeakShiftedUse) / dOffPkSum[1];
               dOffPkAdjMultsDeltas[1] = dOffPkAdjMults[1] - dTargetOffPeakUseMult;
            }
            if (iNumOffPeakHrs > 2 && iFirstPeakHr-3 >= 0)
            {  dOffPkSum[2] = dOffPkSum[1] + pdHrlyUse[iFirstPeakHr-3];
               if (dOffPkSum[2] > 0.0)
               {  dOffPkAdjMults[2] = (dOffPkSum[2] + dTargetOffPeakShiftedUse) / dOffPkSum[2];
                  dOffPkAdjMultsDeltas[2] = dOffPkAdjMults[2] - dTargetOffPeakUseMult;
               }
               if (iNumOffPeakHrs > 3 && iFirstPeakHr-4 >= 0)
               {  dOffPkSum[3] = dOffPkSum[2] + pdHrlyUse[iFirstPeakHr-4];
                  if (dOffPkSum[3] > 0.0)
                  {  dOffPkAdjMults[3] = (dOffPkSum[3] + dTargetOffPeakShiftedUse) / dOffPkSum[3];
                     dOffPkAdjMultsDeltas[3] = dOffPkAdjMults[3] - dTargetOffPeakUseMult;
         }  }  }  }
      }
      // determine how many off-peak hours to shift
      double dDistribRemaining = 0.0;
      if (dOffPkSum[3] < 0.0001)
      {  iNumOffPkHrsToShift = 4;
         dRetVal = 1.0;
         dDistribRemaining = dTargetOffPeakShiftedUse;
      }
      else if (dOffPkSum[3] > 0.0 && (dOffPkAdjMults[3] > dTargetOffPeakUseMult || abs( dOffPkAdjMultsDeltas[3] ) < abs( dOffPkAdjMultsDeltas[2] ) ||
                                                                                       (dOffPkAdjMultsDeltas[3] < 0.0 && dOffPkAdjMultsDeltas[2] > 0.0)))
      {  iNumOffPkHrsToShift = 4;
         if (dOffPkAdjMults[3] > dMaxOffPeakUseMult)
         {  dDistribRemaining = (dOffPkSum[3] + dTargetOffPeakShiftedUse) - (dOffPkSum[3] * dMaxOffPeakUseMult);
            dOffPkAdjMults[3] = dMaxOffPeakUseMult;
         }
         dRetVal = dOffPkAdjMults[3];
      }
      else if (dOffPkSum[2] > 0.0 && (dOffPkAdjMults[2] > dTargetOffPeakUseMult || abs( dOffPkAdjMultsDeltas[2] ) < abs( dOffPkAdjMultsDeltas[1] ) ||
                                                                                       (dOffPkAdjMultsDeltas[2] < 0.0 && dOffPkAdjMultsDeltas[1] > 0.0)))
      {  iNumOffPkHrsToShift = 3;
         if (dOffPkAdjMults[2] > dMaxOffPeakUseMult)
         {  dDistribRemaining = (dOffPkSum[2] + dTargetOffPeakShiftedUse) - (dOffPkSum[2] * dMaxOffPeakUseMult);
            dOffPkAdjMults[2] = dMaxOffPeakUseMult;
         }
         dRetVal = dOffPkAdjMults[2];
      }
      else if (dOffPkSum[1] > 0.0 && (dOffPkAdjMults[1] > dTargetOffPeakUseMult || abs( dOffPkAdjMultsDeltas[1] ) < abs( dOffPkAdjMultsDeltas[0] ) ||
                                                                                       (dOffPkAdjMultsDeltas[1] < 0.0 && dOffPkAdjMultsDeltas[0] > 0.0)))
      {  iNumOffPkHrsToShift = 2;
         if (dOffPkAdjMults[1] > dMaxOffPeakUseMult)
         {  dDistribRemaining = (dOffPkSum[1] + dTargetOffPeakShiftedUse) - (dOffPkSum[1] * dMaxOffPeakUseMult);
            dOffPkAdjMults[1] = dMaxOffPeakUseMult;
         }
         dRetVal = dOffPkAdjMults[1];
      }
      else if (dOffPkSum[0] > 0.0)
      {  iNumOffPkHrsToShift = 1;
         if (dOffPkAdjMults[0] > dMaxOffPeakUseMult)
         {  dDistribRemaining = (dOffPkSum[0] + dTargetOffPeakShiftedUse) - (dOffPkSum[0] * dMaxOffPeakUseMult);
            dOffPkAdjMults[0] = dMaxOffPeakUseMult;
         }
         dRetVal = dOffPkAdjMults[0];
      }                                      assert( dRetVal > 0.0 && iNumOffPkHrsToShift > 0 );

      // APPLY off-peak shift
      if (dRetVal > 1.0 && iNumOffPkHrsToShift > 0)
      {     pdHrlyUse[iFirstPeakHr-1] *= dRetVal;
         if (iNumOffPkHrsToShift > 1)
            pdHrlyUse[iFirstPeakHr-2] *= dRetVal;
         if (iNumOffPkHrsToShift > 2)
            pdHrlyUse[iFirstPeakHr-3] *= dRetVal;
         if (iNumOffPkHrsToShift > 3)
            pdHrlyUse[iFirstPeakHr-4] *= dRetVal;
      }
      if (dDistribRemaining > 0.001 && iNumOffPkHrsToShift > 0)
      {     pdHrlyUse[iFirstPeakHr-1] += (dDistribRemaining / iNumOffPkHrsToShift);
         if (iNumOffPkHrsToShift > 1)
            pdHrlyUse[iFirstPeakHr-2] += (dDistribRemaining / iNumOffPkHrsToShift);
         if (iNumOffPkHrsToShift > 2)
            pdHrlyUse[iFirstPeakHr-3] += (dDistribRemaining / iNumOffPkHrsToShift);
         if (iNumOffPkHrsToShift > 3)
            pdHrlyUse[iFirstPeakHr-4] += (dDistribRemaining / iNumOffPkHrsToShift);
      }
   }
   return dRetVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//											96 : Error calculating CUAC utility bill(s)
void CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, char* pszErrorMsg, int iErrorMsgLen,
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iDataModel /*=0*/, int iBillCalcDetails /*=-1*/,
                              int iDownloadVerbose /*=-1*/, bool bWritePDF /*=true*/, bool bWriteCSV /*=true*/, int iBatchRunIdx /*=0*/, const char* pAnalysisInvalidMsg /*=NULL*/ )
{  // at this point, ruleset object is loaded w/ all hourly results read directly from CSE run(s)
// TEMPORARY
//bVerbose = true;
   //bool bCUACRptVerbose = (iBillCalcDetails < 0 ? bVerbose : (iBillCalcDetails > 0 ? true : false));
   if (iBillCalcDetails < 0)     // replaced bCUACRptVerbose w/ variable iBillCalcDetails - SAC 12/06/23
      iBillCalcDetails = (bVerbose ? 1 : 0);
   if (iDownloadVerbose < 0)     // SAC 09/03/24
      iDownloadVerbose = (bVerbose ? 1 : 0);

   int iMtr, iFuel, iMo, iDay, iHr, i0YrDay, iTemp, iSpecVal, iErr, iStep = 1;
   long laNumUnitsByBedrms[NumDwellingMeters], lTemp, lNumUnitTypes=0;
   bool bOldCUAC = (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CUAC_OldAccessDB" ), lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0) ? true : false;

   int iPrevRuleErrs = BEMPX_GetRulesetErrorCount();   // add eval of rules to setup utility rates - SAC 09/14/22
                  if (iBillCalcDetails > 0) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupGen1ElecRate & CUAC_SetupGen1GasRate rules (if needed)" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bRateEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupGen1ElecRate" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - errors encountered evaluating CUAC_SetupGen1ElecRate rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }
   bRateEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupGen1GasRate" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - errors encountered evaluating CUAC_SetupGen1GasRate rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }

   long lDBID_CUAC_IncludeDHWInUtilityBills = BEMPX_GetDatabaseID( "CUAC:IncludeDHWInUtilityBills" );    // SAC 09/03/24
   bool bExcludeDHW = false;
   if ( lDBID_CUAC_IncludeDHWInUtilityBills > 0 && BEMPX_GetInteger( lDBID_CUAC_IncludeDHWInUtilityBills, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp < 1)
      bExcludeDHW = true;

   int iCID_CUAC    = BEMPX_GetDBComponentID( "CUAC" );
   int iCID_OldCUAC = BEMPX_GetDBComponentID( "OldCUAC" );
   int iCID_OldCUACApt = BEMPX_GetDBComponentID( "OldCUACApt" );
   QString sStep = "Init";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "AffordableUnitsByBedrms", iCID_CUAC )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0)
      {  if (iDataModel == 1)
            laNumUnitsByBedrms[iMtr] = (lTemp >= 1 ? 1 : 0);   // SFam analysis always models just a single dwelling - SAC 10/22/24
         else
            laNumUnitsByBedrms[iMtr] = lTemp;
         lNumUnitTypes++;
      }
      else
         laNumUnitsByBedrms[iMtr] = 0;
   }
   if (lNumUnitTypes < 1)  // abort analysis if no unit types specified - SAC 10/19/22
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
      sErrMsg = QString( "CUAC Error: No affordable units specified. Specify affordable units via checkboxes in residential zone dialog." );
      BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }

   int iResFuelMtrIdx = 1;    // NatGas         // Res - SAC 09/11/24 (res tic #1378)
   if (iDataModel == 1)
   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:GasType" ), lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 1)
         iResFuelMtrIdx = 2;  // Other fuel
   }

   bool bAnalysisValid = (pAnalysisInvalidMsg == NULL || strlen( pAnalysisInvalidMsg ) < 3);   // SAC 01/02/25
   if (!bAnalysisValid)
   {  long lDBID_CUAC_AnalysisInvalidMsg = BEMPX_GetDatabaseID( "CUAC:AnalysisInvalidMsg" );
      if (lDBID_CUAC_AnalysisInvalidMsg > 0)
         BEMPX_SetBEMData( lDBID_CUAC_AnalysisInvalidMsg, BEMP_Str, (void*) pAnalysisInvalidMsg );
   }

   double daZero[8760];    // restored to prevent CSV writing error when no Gas meter present in model - SAC 02/28/24
   double daHrlyElecCost[8760];
   for (iHr=0; iHr<8760; iHr++)
   {  daZero[iHr] = 0.0;
      daHrlyElecCost[iHr] = 0.0;
   }
   bool bHrlyElecCostVariesForDay[365];  int iDayFirstPeakHr[2][365], iDayPeakDuration[2][365];
   double daOffPeakUseMult[2][365], daPctDayElecUseIncrease[2][365];
   for (iDay=0; iDay<365; iDay++)
   {  bHrlyElecCostVariesForDay[iDay] = false;
      iDayFirstPeakHr[ 0][iDay] = -1;   iDayFirstPeakHr[ 1][iDay] = -1;
      iDayPeakDuration[0][iDay] =  0;   iDayPeakDuration[1][iDay] =  0;
      daOffPeakUseMult[       0][iDay] = 0.0;   daOffPeakUseMult[       1][iDay] = 0.0;
      daPctDayElecUseIncrease[0][iDay] = 0.0;   daPctDayElecUseIncrease[1][iDay] = 0.0;
   }

   // Retrieve & Load utility rate data  - SAC 10/19/22
         // moved up from below - SAC 01/12/25 (tic #1388)
   int iCID_UtilityRate = BEMPX_GetDBComponentID( "CPR_UtilityRate" );
   CUACUtilityRate utilRate[2];
   utilRate[0].bOK = utilRate[1].bOK = false;
   int iG2RateObjIdx[2] = { -1, -1 };
   long laDBID_RateGen[2] = { BEMPX_GetDatabaseID( "ElecTariffGen"     , iCID_CUAC ), BEMPX_GetDatabaseID( "GasTariffGen"     , iCID_CUAC ) };     // SAC 09/01/23
   long laDBID_RateRef[2] = { BEMPX_GetDatabaseID( "ElecUtilityRateRef", iCID_CUAC ), BEMPX_GetDatabaseID( "GasUtilityRateRef", iCID_CUAC ) };     // loop to include Gas rate - SAC 10/25/22
   QString saFuelLabels[2] = { "Elec", "Gas" };
   QString saFuelUnitLabels[2] = { "kWh", "therms" };
   QString saFuelUnitLabels1[2] = { "kWh", "therm" };
   for (iFuel=0; iFuel < 2; iFuel++)
   { 
      long lUtilRateGen = BEMPX_GetInteger( laDBID_RateGen[iFuel], iSpecVal, iErr, -1, BEMO_User, iCUAC_BEMProcIdx );      //  2 => 2023+ CPR rates
      if (lUtilRateGen == 2)     // SAC 09/01/23
      {  BEMObject* pG2RateObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( (iFuel==0 ? "CPR_ElecUtilityRateRef" : "CPR_GasUtilityRateRef"), iCID_CUAC ), iSpecVal, iErr, -1 /*occur*/, BEMO_User, iCUAC_BEMProcIdx );
         iG2RateObjIdx[iFuel]  = (pG2RateObj == NULL ? -1 : BEMPX_GetObjectIndex( pG2RateObj->getClass(), pG2RateObj, iCUAC_BEMProcIdx ));
         if (iG2RateObjIdx[iFuel] < 0)
         {  sErrMsg = QString( "CUAC Gen2 %1 Utility Rate not found" ).arg( saFuelLabels[iFuel] );
            BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         }
         else if (iBillCalcDetails > 0)
            BEMPX_WriteLogFile( QString( "CUAC Gen2 %1 Utility Rate '%2' in use" ).arg( saFuelLabels[iFuel], pG2RateObj->getName() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      }
      if (iG2RateObjIdx[iFuel] < 0)
      {  BEMObject* pRate = BEMPX_GetObjectPtr( laDBID_RateRef[iFuel], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iRateObjIdx = (pRate == NULL ? -1 : BEMPX_GetObjectIndex( pRate->getClass(), pRate, iCUAC_BEMProcIdx ));
         if (iRateObjIdx >= 0 && !LoadCUACUtilityRate( utilRate[iFuel], iRateObjIdx, iCUAC_BEMProcIdx, sErrMsg ))
         {  if (sErrMsg.isEmpty())
               sErrMsg = QString( "CUAC %1 Utility Rate Initialization Error" ).arg( saFuelLabels[iFuel] );
            else
               sErrMsg = QString( "CUAC %1 Utility Rate Initialization Error:  " ).arg( saFuelLabels[iFuel] ) + sErrMsg;
            BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   }  }  }

   int iCID_EnergyCost  = BEMPX_GetDBComponentID( "CPR_EnergyCost" );
   long lDBID_EnergyCost_CostName         = BEMPX_GetDatabaseID( "CostName",          iCID_EnergyCost );
   long lDBID_EnergyCost_PeriodType       = BEMPX_GetDatabaseID( "PeriodType",        iCID_EnergyCost );
   long lDBID_EnergyCost_Delivery         = BEMPX_GetDatabaseID( "Delivery",          iCID_EnergyCost );
   long lDBID_EnergyCost_NonBypassable    = BEMPX_GetDatabaseID( "NonBypassable",     iCID_EnergyCost );
   long lDBID_EnergyCost_TotalConsumption = BEMPX_GetDatabaseID( "TotalConsumption",  iCID_EnergyCost );
   long lDBID_EnergyCost_NumTiers         = BEMPX_GetDatabaseID( "NumTiers",          iCID_EnergyCost );
   long lDBID_EnergyCost_Tiers            = BEMPX_GetDatabaseID( "Tiers",             iCID_EnergyCost );

   int iCID_NetExcessCreditCost = BEMPX_GetDBComponentID( "CPR_NetExcessCreditCost" );
   long lDBID_NetExcessCreditCost_CostName       = BEMPX_GetDatabaseID( "CostName",       iCID_NetExcessCreditCost );
   long lDBID_NetExcessCreditCost_CostPeriodType = BEMPX_GetDatabaseID( "CostPeriodType", iCID_NetExcessCreditCost );
   long lDBID_NetExcessCreditCost_NumTiers       = BEMPX_GetDatabaseID( "NumTiers",       iCID_NetExcessCreditCost );
   long lDBID_NetExcessCreditCost_Tiers          = BEMPX_GetDatabaseID( "Tiers",          iCID_NetExcessCreditCost );

   int iCID_HourlyTOUCost = BEMPX_GetDBComponentID( "CPR_HourlyTOUCost" );
   long lDBID_HourlyTOUCost_CostName                 = BEMPX_GetDatabaseID( "CostName",                 iCID_HourlyTOUCost );
   long lDBID_HourlyTOUCost_ApplicableDays           = BEMPX_GetDatabaseID( "ApplicableDays",           iCID_HourlyTOUCost );
   long lDBID_HourlyTOUCost_NumHourlyTimeOfUseMonths = BEMPX_GetDatabaseID( "NumHourlyTimeOfUseMonths", iCID_HourlyTOUCost );
   long lDBID_HourlyTOUCost_HourlyTimeOfUseMonths    = BEMPX_GetDatabaseID( "HourlyTimeOfUseMonths",    iCID_HourlyTOUCost );

   int iCID_HourlyTOUMonth = BEMPX_GetDBComponentID( "CPR_HourlyTOUMonth" );
   long lDBID_HourlyTOUMonth_MonthName = BEMPX_GetDatabaseID( "MonthName", iCID_HourlyTOUMonth );
   long lDBID_HourlyTOUMonth_Prices    = BEMPX_GetDatabaseID( "Prices",    iCID_HourlyTOUMonth );

   int iCID_Tier = BEMPX_GetDBComponentID( "CPR_Tier" );
   long lDBID_Tier_TierNumber = BEMPX_GetDatabaseID( "TierNumber",  iCID_Tier );
   long lDBID_Tier_Price      = BEMPX_GetDatabaseID( "Price",       iCID_Tier );
   long lDBID_Tier_Quantity   = BEMPX_GetDatabaseID( "Quantity",    iCID_Tier );

   long lPVBillingOption=0, lPVCarryoverOption=-1;    // SAC 12/10/22
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "PVBillingOption"  , iCID_CUAC ), lPVBillingOption  , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "PVCarryoverOption", iCID_CUAC ), lPVCarryoverOption, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
         // CUAC:PVBillingOption,  2      ; SAC 12/10/22
         //              0,    "PV Offsets Monthly Use"
         //              1,    "PV Offsets Monthly Use w/ Carryover"
         // CUAC:PVCarryoverOption,  12   ; SAC 12/10/22
         //              0,    "never ends"
         //              1,    "ends after Jan"
         //              2,    "ends after Feb"

   int iMoHrStart[12], iMoHrEnd[12];
   iMoHrStart[0] = 0;   iMoHrEnd[0] = (24*iNumDaysInMonth[0])-1;
   for (iTemp=1; iTemp<12; iTemp++)
   {  iMoHrStart[iTemp] = iMoHrEnd[  iTemp-1] + 1;
      iMoHrEnd[  iTemp] = iMoHrStart[iTemp] + (24*iNumDaysInMonth[iTemp])-1;
   }

   // Adjust DHW elec use for meters w/ JA13 (demand response) HPWHs - SAC 01/12/25 (tic #1388)
   long lPerformJA13DHWBillAdjustments = 0;     iFuel = 0;  // elec
   bool bTOUPricesFound = false;
   int iNumJA13DHWTOUPeriodDays = 0;      // SAC 01/21/25
   // 0/1 project-wide toggle for doing JA13 elec bill adjustments
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "PerformJA13DHWBillAdj", iCID_CUAC ), lPerformJA13DHWBillAdjustments, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   if (bExcludeDHW)
   {  }     // ignore all JA13 HPWH adjustments if we are excluding DHW all together
   else if (lPerformJA13DHWBillAdjustments > 0 && !bOldCUAC && iG2RateObjIdx[iFuel] < 0)
      sErrMsg = QString( "CUAC %1 Utility bill calc error:  no Electric rate assigned or rate data invalid - needed for DHW HPWH JA13 credit calcs" ).arg( saFuelLabels[iFuel] );
   else if (lPerformJA13DHWBillAdjustments > 0)
   {  long lNumRateSeasons    = BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumRateSeasons"   , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
      long lNumHourlyTOUCosts = BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumHourlyTOUCosts", iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
      if (lNumRateSeasons < 1)
         sErrMsg = QString( "CUAC %1 Utility bill calc error:  rate must include at least one RateSeason" ).arg( saFuelLabels[iFuel] );
      else
      {
            bool bIgnoreNetExcesCredits=false, bIgnoreHourlyTOU=false;
            long lElecTariffAdj=0;
            //double dElecBillMinMoCharge=-999.0, dElecBillMinAnnCharge=-999.0;
            //if (iFuel == 0)  // Electric processing
            //{
            //   lElecBillReconBeginMo = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:ElecBillReconBeginMo" ), iSpecVal, iErr, 0 /*ObjIdx*/, BEMO_User, iCUAC_BEMProcIdx );      // SAC 12/10/23 (CUAC)
               BEMPX_GetInteger( BEMPX_GetDatabaseID( "ElecTariffAdj", iCID_CUAC ), lElecTariffAdj, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );       // SAC 12/13/23
               if (lElecTariffAdj == 2)   // hardwiring VNEM2 - SAC 12/13/23
               {  bIgnoreNetExcesCredits = true;
                  bIgnoreHourlyTOU       = true;
                  QString qsElecTariffAdj;
                  BEMPX_GetString( BEMPX_GetDatabaseID( "ElecTariffAdj", iCID_CUAC ), qsElecTariffAdj, FALSE, 0, -1, 0, BEMO_User, "??", 0, iCUAC_BEMProcIdx ); 
                  BEMPX_WriteLogFile( QString( "  applying user-specified utility bill adjustment '%1' to utility bill calc" ).arg( qsElecTariffAdj ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
            //   BEMPX_GetFloat( BEMPX_GetDatabaseID( "ElecBillMinMoCharge" , iCID_CUAC ), dElecBillMinMoCharge , -999.0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );    // SAC 12/14/23
            //   BEMPX_GetFloat( BEMPX_GetDatabaseID( "ElecBillMinAnnCharge", iCID_CUAC ), dElecBillMinAnnCharge, -999.0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ); 
            //}


                  //QString qsEncodedRateName       = BEMPX_GetString( BEMPX_GetDatabaseID( "EncodedRateName"      , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  QString qsMeteringType          = BEMPX_GetString( BEMPX_GetDatabaseID( "MeteringType"         , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  //QString qsReconciliationPeriod  = BEMPX_GetString( BEMPX_GetDatabaseID( "ReconciliationPeriod" , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  //QString qsNettingPeriodInterval = BEMPX_GetString( BEMPX_GetDatabaseID( "NettingPeriodInterval", iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  //QString qsDemandInterval        = BEMPX_GetString( BEMPX_GetDatabaseID( "DemandInterval"       , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  //long lAnnualBilling     = BEMPX_GetInteger( BEMPX_GetDatabaseID( "AnnualBilling"    , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );

                  bool bFullRetailReimbForExports = false;
                  if ( (iFuel == 0 && lElecTariffAdj == 2) ||                                      // SAC 12/13/23
                       !qsMeteringType.compare( "NetMetering",         Qt::CaseInsensitive ) ||    // SAC 12/04/23
                       !qsMeteringType.compare( "OptionalNetMetering", Qt::CaseInsensitive ) )
                     bFullRetailReimbForExports = true;


                     for (iMo=0; (iMo<12 && sErrMsg.isEmpty()); iMo++)
                     {  //double dMonBypassableCost = 0.0, dMonNonBypassableCost = 0.0, dMonMinCost = 0.0;
                        for (int iSeas=0; (iSeas < lNumRateSeasons && sErrMsg.isEmpty()); iSeas++)
                        {  BEMObject* pSeasObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "RateSeasons", iCID_UtilityRate )+iSeas, iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                           int iSeasObjIdx     = (pSeasObj == NULL ? -1 : BEMPX_GetObjectIndex( pSeasObj->getClass(), pSeasObj, iCUAC_BEMProcIdx ));
                           if (iSeasObjIdx < 0)
                              sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve RateSeasons #%2" ).arg( saFuelLabels[iFuel], QString::number( iSeas+1 ) );
                           else
                           {  QString qsSeasName     = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_RateSeason:Name"             ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              QString qsSeasJSONName = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_RateSeason:SeasonName"       ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              long lNumSeasonPeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_RateSeason:NumSeasonPeriods" ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              int iSeasMoHrStart=-1, iSeasMoHrEnd=-1;
                              for (int iSeasPer=0; (iSeasPer < lNumSeasonPeriods && sErrMsg.isEmpty() && (iSeasMoHrStart < 0 || iSeasMoHrEnd < 0)); iSeasPer++)
                              {  BEMObject* pSeasPerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_RateSeason:SeasonPeriods" )+iSeasPer, iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                 int iSeasPerObjIdx     = (pSeasPerObj == NULL ? -1 : BEMPX_GetObjectIndex( pSeasPerObj->getClass(), pSeasPerObj, iCUAC_BEMProcIdx ));
                                 if (iSeasPerObjIdx < 0)
                                    sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve SeasonTimePeriod #%2 for RateSeasons #%3" ).arg( saFuelLabels[iFuel], QString::number( iSeasPer+1 ), QString::number( iSeas+1 ) );
                                 else
                                    G2MonthSeasonPeriodOverlap( iSeasPerObjIdx, iMo+1, iMoHrStart[iMo], iMoHrEnd[iMo], iSeasMoHrStart, iSeasMoHrEnd, iCUAC_BEMProcIdx, sErrMsg );
                              }
                              if (sErrMsg.isEmpty() && iSeasMoHrStart >= 0 && iSeasMoHrEnd > 0)
                              {                       if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "            %1 - Seas #%2, %3 / %4, yr hrs %5-%6:" ).arg( pszMoLabels[iMo], QString::number( iSeas+1 ), qsSeasName, qsSeasJSONName, QString::number( iSeasMoHrStart ), QString::number( iSeasMoHrEnd ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

                                 long lNumTOUPeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_RateSeason:NumTimeOfUsePeriods" ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                 for (int iTOUPer=0; (iTOUPer < lNumTOUPeriods && sErrMsg.isEmpty()); iTOUPer++)
                                 {  BEMObject* pTOUPerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_RateSeason:TimeOfUsePeriods" )+iTOUPer, iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    int iTOUPerObjIdx     = (pTOUPerObj == NULL ? -1 : BEMPX_GetObjectIndex( pTOUPerObj->getClass(), pTOUPerObj, iCUAC_BEMProcIdx ));
                                    if (iTOUPerObjIdx < 0)
                                       sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve TOUPeriod #%2 for RateSeasons #%3" ).arg( saFuelLabels[iFuel], QString::number( iTOUPer+1 ), QString::number( iSeas+1 ) );
                                    else
                                    {                 if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "               TOUPeriod #%1, %2 / %3:" ).arg( QString::number( iTOUPerObjIdx+1 ), 
                                                                                                            BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:Name"    ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ),
                                                                                                            BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TOUName" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       long lNumDailyTimePeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_TOUPeriod:NumTimePeriods" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       BEMObject* pCostCompObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_TOUPeriod:CostComponents" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       int iCostCompObjIdx     = (pCostCompObj == NULL ? -1 : BEMPX_GetObjectIndex( pCostCompObj->getClass(), pCostCompObj, iCUAC_BEMProcIdx ));
                                       if (iCostCompObjIdx < 0)
                                          sErrMsg = QString( "CUAC %1 Utility bill calc error:  CostComponents not defined for TOUPeriod #%2 %3, RateSeasons #%4" ).arg( saFuelLabels[iFuel], QString::number( iTOUPer+1 ), 
                                                               BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TOUName" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ), QString::number( iSeas+1 ) );
                                       else
                                       {  // Days:   0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                                          double dDayHrMult[7][24] = { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };
                                          int iNumTimePeriodHrsInWk = 0;      // SAC 09/18/23
                                          for (int iDailyTimePer=0; (iDailyTimePer < lNumDailyTimePeriods && sErrMsg.isEmpty()); iDailyTimePer++)
                                          {  BEMObject* pDailyTimePerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TimePeriods" )+iDailyTimePer, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             int iDailyTimePerObjIdx     = (pDailyTimePerObj == NULL ? -1 : BEMPX_GetObjectIndex( pDailyTimePerObj->getClass(), pDailyTimePerObj, iCUAC_BEMProcIdx ));
                                             if (iDailyTimePerObjIdx < 0)
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve DailyTimePeriod #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iDailyTimePer+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                             else
                                             {  int iCID_DailyTimePeriod = BEMPX_GetDBComponentID( "CPR_DailyTimePeriod" );
                                                double dStartTime    = BEMPX_GetFloat(  BEMPX_GetDatabaseID( "StartTime",      iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                double dEndTime      = BEMPX_GetFloat(  BEMPX_GetDatabaseID( "EndTime",        iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                QString sWhichDays   = BEMPX_GetString( BEMPX_GetDatabaseID( "ApplicableDays", iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                // mods to accommodate valid scenario where dEndTime < dStartTime - meaning period turns corner over midnight - SAC 12/04/23
                                                if (dStartTime < 0 || dEndTime < 0 || dEndTime == dStartTime /*|| dEndTime < dStartTime*/ || sWhichDays.isEmpty())
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  invalid data describing DailyTimePeriod #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iDailyTimePer+1 ), QString::number( iDailyTimePerObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else
                                                {  QString sDTPName  = BEMPX_GetString( BEMPX_GetDatabaseID( "Name",           iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                               if (iBillCalcDetails > 0)
                                                                  BEMPX_WriteLogFile( QString( "                  DlyTimePeriod #%1, %2 - days: %3, hrs %4-%5:" ).arg( QString::number( iDailyTimePer+1 ), sDTPName, sWhichDays, QString::number( dStartTime ), QString::number( dEndTime ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                   double dStartTm[] = {  dStartTime                              , (dStartTime < dEndTime ? 100.0 : 0.0) };      // SAC 12/04/23
                                                   double dEndTm[]   = { (dStartTime < dEndTime ? dEndTime : 24.0),  dEndTime   };
                                                   // intialize dDayHrMult[][] arrays to keep track of days & hours this TOU period enforced
                                                   for (iDay=0; iDay < 7; iDay++)                                 //0, CPR_DailyTimePeriod:ApplicableDays,   -1
                                                      if (  !sWhichDays.compare( "All"      ) ||                  //2,              1,    "All" 
                                                           (!sWhichDays.compare( "Weekdays" ) && iDay < 5) ||     //2,              0,    "Weekdays" 
                                                           (!sWhichDays.compare( "Weekends" ) && iDay > 4) )      //2,              2,    "Weekends" 
                                                         for (iHr=0; iHr < 24; iHr++)
                                                         {  if ( (iHr >= (dStartTm[0]-0.1) && iHr < (dEndTm[0]-0.1)) ||
                                                                 (iHr >= (dStartTm[1]-0.1) && iHr < (dEndTm[1]-0.1)) )
                                                            {  dDayHrMult[iDay][iHr] = 1.0;
                                                               iNumTimePeriodHrsInWk++;
                                                         }  }
                                          }  }  }
                                                                     assert( (!bOldCUAC || iNumTimePeriodHrsInWk == 0 || iNumTimePeriodHrsInWk == 168) );      // if OldCUAC, TOU period should cover ALL or NONE of the week - SAC 09/18/23
                                          // CPR_TOUPeriod TimePeriods loaded - now move on to CostComponent
                                          // sum use and find peak demand during month within TOU period
                                          int iHrInDay;
                                          //double dMoTOUUse = 0.0, dMoTOUPeakDem = 0.0, dMonBypassableTOUCost = 0.0, dMonNonBypassableTOUCost = 0.0, dMoTOUDailyUse[31];
                                          //for (iDay=0; iDay<31; iDay++)
                                          //   dMoTOUDailyUse[iDay] = 0.0;
                                          if (TRUE)  // !bOldCUAC)
                                          {  // HOURLY simulation results

                                             // CPR_PeriodCost:EnergyCosts
                                             int iCostIdx, iTierIdx;
                                             long lNumEnergyCosts   = BEMPX_GetInteger(   BEMPX_GetDatabaseID( "CPR_PeriodCost:NumEnergyCosts" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             for (iCostIdx = 0; (iCostIdx < lNumEnergyCosts && sErrMsg.isEmpty()); iCostIdx++)
                                             {  BEMObject* pEnergyCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_PeriodCost:EnergyCosts" )+iCostIdx, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                int iEnergyCostObjIdx     = (pEnergyCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pEnergyCostObj->getClass(), pEnergyCostObj, iCUAC_BEMProcIdx ));
                                                if (iEnergyCostObjIdx < 0)
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve EnergyCost #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else
                                                {  QString sPeriodType    = BEMPX_GetString(  lDBID_EnergyCost_PeriodType,       iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                   long lNumTiers         = BEMPX_GetInteger( lDBID_EnergyCost_NumTiers,         iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                   long lTotalConsumption = BEMPX_GetInteger( lDBID_EnergyCost_TotalConsumption, iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                   long lNonBypassable    = BEMPX_GetInteger( lDBID_EnergyCost_NonBypassable,    iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );    // SAC 09/11/23
                                                            //  "CostName",                 BEMP_Str,  1,  0,  0,  Pres,  "",                 0,  0,                                 1005, "Name of the cost component",    "Name" 
                                                            //  "Delivery",                 BEMP_Int,  1,  0,  0,  Pres,  "",                 0,  0,                                 1005, "Boolean indicating if this is a delivery charge or not",  "" 
                                                   if (lNumTiers < 1 || sPeriodType.isEmpty())
                                                      sErrMsg = QString( "CUAC %1 Utility bill calc error:  invalid data describing EnergyCosts #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iEnergyCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                   else if (lTotalConsumption > 0)
                                                      sErrMsg = QString( "CUAC %1 Utility bill calc error:  TotalConsumption not yet implemented for EnergyCosts #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iEnergyCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                   else
                                                   {  //double dThisMoTOUUse = dMoTOUUse;
                                                      //double dThisMoTOUDailyUse[31];
                                                      //if (!sPeriodType.compare("PerDayBilled"))
                                                      //{  for (iDay=0; iDay<31; iDay++)
                                                      //      dThisMoTOUDailyUse[iDay] = dMoTOUDailyUse[iDay];
                                                      //}
                                                      //double dThisCost = 0.0;
                                                      for (iTierIdx = 0; (iTierIdx < lNumTiers && sErrMsg.isEmpty()); iTierIdx++)
                                                      {  BEMObject* pTierObj = BEMPX_GetObjectPtr( lDBID_EnergyCost_Tiers+iTierIdx, iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         int iTierObjIdx     = (pTierObj == NULL ? -1 : BEMPX_GetObjectIndex( pTierObj->getClass(), pTierObj, iCUAC_BEMProcIdx ));
                                                         if (iTierObjIdx < 0)
                                                            sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve Tier #%2 for RateSeasons #%3, TOUPeriod #%4, EnergyCosts #%5" ).arg( saFuelLabels[iFuel], QString::number( iTierIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ) );
                                                         else
                                                         {  long lTierNumber  = BEMPX_GetInteger( lDBID_Tier_TierNumber, iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                            double dPrice     = BEMPX_GetFloat(   lDBID_Tier_Price,      iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                            double dQuantity  = BEMPX_GetFloat(   lDBID_Tier_Quantity,   iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );

                                                            // when accumulating 8760 of TOU prices, only track the FIRST tier cost > 0 - SAC 01/15/25
                                                            if (dPrice > 0 && iTierIdx < (lNumTiers-1))
                                                               lNumTiers = iTierIdx+1;

                                                            //double dThisTierCost = 0.0;
                                                            //if (!sPeriodType.compare("PerDayBilled"))
                                                            //{  for (iDay=0; iDay<31; iDay++)
                                                            //   {  double dDayQuantity = 0.0;
                                                            //      if (dThisMoTOUDailyUse[iDay] > 0)
                                                            //         dDayQuantity = (dQuantity > 0 ? std::min( dThisMoTOUDailyUse[iDay], dQuantity ) : dThisMoTOUDailyUse[iDay]);
                                                            //      else if (dThisMoTOUDailyUse[iDay] < 0 && bFullRetailReimbForExports && dPrice > 0 && lNonBypassable == 0)     // for exports, only apply charge if price > 0 - SAC 12/04/23
                                                            //         dDayQuantity = (dQuantity > 0 ? std::max( dThisMoTOUDailyUse[iDay], (-1.0 * dQuantity) ) : dThisMoTOUDailyUse[iDay]);
                                                            //      if (dDayQuantity != 0.0)
                                                            //      {  dThisTierCost += (dDayQuantity * dPrice);
                                                            //         dThisMoTOUDailyUse[iDay] -= dDayQuantity;
                                                            //            if (iBillCalcDetails > 1 && sErrMsg.isEmpty())
                                                            //               BEMPX_WriteLogFile( QString( "                           Tier #%1, day %2: %3 @ price %4 = %5" ).arg( QString::number( iTierIdx+1 ), QString::number( iDay+1 ), QString::number( dDayQuantity ), QString::number( dPrice ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                            //      }
                                                            //   }
                                                            //}
                                                            //else if (!sPeriodType.compare("PerBillingCycle"))
                                                            //{  dQuantity = 0.0;
                                                            //   if (dThisMoTOUUse < 0 && bFullRetailReimbForExports && dPrice > 0 && lNonBypassable == 0)      // for exports, only apply charge if price > 0 - SAC 12/04/23
                                                            //      dQuantity = (dQuantity > 0 ? std::max( dThisMoTOUUse, (-1.0 * dQuantity) ) : dThisMoTOUUse);
                                                            //   else if (dThisMoTOUUse > 0)
                                                            //      dQuantity = (dQuantity > 0 ? std::min( dThisMoTOUUse, dQuantity ) : dThisMoTOUUse);
                                                            //   dThisTierCost += (dQuantity * dPrice);
                                                            //   dThisMoTOUUse -=  dQuantity;
                                                            //            if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                            //               BEMPX_WriteLogFile( QString( "                           Tier #%1: %2 @ price %3 = %4" ).arg( QString::number( iTierIdx+1 ), QString::number( dQuantity ), QString::number( dPrice ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                            //}
                                                            //else
                                                            //   sErrMsg = QString( "CUAC %1 Utility bill calc error:  unrecognized PeriodType '%2' for RateSeasons #%3, TOUPeriod #%4, EnergyCosts #%5, Tier #%6" ).arg( 
                                                            //                        saFuelLabels[iFuel], sPeriodType, QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ), QString::number( iTierIdx+1 ) );
                                                            // re: above - assumption is that PeriodType doesn't impact tracking of energy cost per hour... - SAC 01/15/25

                                                                  //if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                  //   BEMPX_WriteLogFile( QString( "                           Tier #%1 cost: %2" ).arg( QString::number( iTierIdx+1 ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                            //dThisCost += dThisTierCost;

                                                            if (dPrice > 0)
                                                            {  bTOUPricesFound = true;
                                                               for (iHr = iSeasMoHrStart; iHr <= iSeasMoHrEnd; iHr++)
                                                               {  i0YrDay  = (int) (iHr/24);
                                                                  iHrInDay = iHr - (i0YrDay*24);
                                                                  iDay = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDay>=0 && iDay<7) );
                                                                  if (dDayHrMult[iDay][iHrInDay] > 0.1)
                                                                  {
                                                                     daHrlyElecCost[iHr] += dPrice;
                                                                     //int iMoTOUDayIdx = i0YrDay - ((int) (iSeasMoHrStart/24));               assert( iMoTOUDayIdx >= 0 && iMoTOUDayIdx < 31 );     // debugging - SAC 09/26/23
                                                                     //dMoTOUDailyUse[iMoTOUDayIdx] += (daHrlyTotUse[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                                     //dMoTOUUse                    += (daHrlyTotUse[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                                     //if (bFullRetailReimbForExports && daHrlyExports[iHr] < 0)      // SAC 12/04/23
                                                                     //{  dMoTOUDailyUse[iMoTOUDayIdx] += (daHrlyExports[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                                     //   dMoTOUUse                    += (daHrlyExports[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                                     //}
                                                                     //if (daHrlyTotUse[iHr] > dMoTOUPeakDem)
                                                                     //   dMoTOUPeakDem = daHrlyTotUse[iHr];
                                                            }  }  }

                                                      }  }
                                                      //if (lNonBypassable && dThisCost > 0)
                                                      //{  dMonNonBypassableTOUCost += dThisCost;
                                                      //   dMonNonBypassableCost += dThisCost;
                                                      //}
                                                      //else
                                                      //{  dMonBypassableTOUCost += dThisCost;
                                                      //   dMonBypassableCost += dThisCost;
                                                      //}
                                                      //            if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                      //               BEMPX_WriteLogFile( QString( "                     EnergyCost #%1 total cost: %2  (cumulative TOU cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( iCostIdx+1 ), QString::number( dThisCost ), QString::number( dMonBypassableTOUCost ), QString::number( dMonNonBypassableTOUCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                             }  }  }

                                          }  // if (TRUE)  // !bOldCUAC) - hourly sim results

                                       }
                                 }  }  // end of loop over TOU periods of Season

                              }  // end of if this season overlaps w/ iMo
                           }
                        }  // end of loop over seasons (overlapping w/ month)
                     }  // end of loop over months

      }  // end of processing of rate data into costs by hour


      if (bTOUPricesFound)
      {  double dJA13DHWBillAdjDeltaPkPriceFrac = BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUAC:JA13DHWBillAdjPctDeltaPkPrice" ), iSpecVal, iErr,     // SAC 01/21/25
                                                                  0, BEMO_User, iCUAC_BEMProcIdx, false, 10.0 ) * 0.01;       // minimum frac difference in on-peak vs. off-peak elec price to perform peak shift
         iHr = 0;    double dRangeFrac, dMinPeakPrice;
         for (iMo=0; iMo<12; iMo++)
            for (iDay=0; iDay<iNumDaysInMonth[iMo]; iDay++)
            {  double dDayMaxPrice=0.0, dDayMinPrice=9999.0;
               i0YrDay  = (int) (iHr/24);
               int iEndDayHr = iHr+24;
               for (iTemp=iHr; iTemp < iEndDayHr; iTemp++)
               {  dDayMaxPrice = (daHrlyElecCost[iTemp] > dDayMaxPrice ? daHrlyElecCost[iTemp] : dDayMaxPrice);
                  dDayMinPrice = (daHrlyElecCost[iTemp] < dDayMinPrice ? daHrlyElecCost[iTemp] : dDayMinPrice);
               }           assert( dDayMaxPrice > 0.0001 );
               if (dDayMaxPrice > 0.0001)    // error ??
               {  dRangeFrac = (dDayMaxPrice - dDayMinPrice) / dDayMaxPrice;
                  if (dRangeFrac >= dJA13DHWBillAdjDeltaPkPriceFrac /*0.03*/)     // must have >= dJA13DHWBillAdjDeltaPkPriceFrac price variation  (was originally hard-coded 3%)
                  {  dMinPeakPrice = dDayMaxPrice - (dDayMaxPrice * dRangeFrac * 0.1);
                     bool bSkipToNextPeak = (daHrlyElecCost[iHr] >= dMinPeakPrice);
                     bool bFoundEndOfFirstPeak = false, bFoundEndOfSecondPeak = false;
                     for (iTemp=iHr; (iTemp < iEndDayHr && !bFoundEndOfSecondPeak); iTemp++)
                     {  if (bFoundEndOfFirstPeak)
                        {  if (iDayFirstPeakHr[1][i0YrDay] < 0 && daHrlyElecCost[iTemp] >= dMinPeakPrice)
                           {  iDayFirstPeakHr[ 1][i0YrDay] = iTemp-iHr;
                              iDayPeakDuration[1][i0YrDay]++;
                           }
                           else if (daHrlyElecCost[iTemp] >= dMinPeakPrice)
                              iDayPeakDuration[1][i0YrDay]++;
                           else if (iDayFirstPeakHr[1][i0YrDay] >= 0)
                              bFoundEndOfSecondPeak = true;
                        }
                        else
                        {  if (bSkipToNextPeak && daHrlyElecCost[iTemp] < dMinPeakPrice)
                              bSkipToNextPeak = false;
                           else if (iDayFirstPeakHr[0][i0YrDay] < 0 && daHrlyElecCost[iTemp] >= dMinPeakPrice)
                           {  iDayFirstPeakHr[ 0][i0YrDay] = iTemp-iHr;
                              iDayPeakDuration[0][i0YrDay]++;
                           }
                           else if (daHrlyElecCost[iTemp] >= dMinPeakPrice)
                              iDayPeakDuration[0][i0YrDay]++;
                           else if (iDayFirstPeakHr[0][i0YrDay] >= 0)
                              bFoundEndOfFirstPeak = true;
                     }  }

                     if (iDayFirstPeakHr[0][i0YrDay] >= 0 || iDayFirstPeakHr[1][i0YrDay] >= 0)
                        iNumJA13DHWTOUPeriodDays++;      // SAC 01/21/25


                     // MORE peak checking ???


               }  }
               iHr += 24;
            }

         if (iBillCalcDetails > 0)  // write CSV file w/ TOU detail by day
         {
            QString sJA13CSVFN = sProcessingPath + sModelFileOnly + QString(" - JA13 TOU detail.csv");
            QString sJA13CSVMsg;
            sJA13CSVMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                         "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                         "(once the file is closed), or \n'Abort' to abort the %s.", "CSV", sJA13CSVFN.toLocal8Bit().constData(), "CSV export" );
            if (!OKToWriteOrDeleteFile( sJA13CSVFN.toLocal8Bit().constData(), sJA13CSVMsg, bSilent ))
            {  }
            //   BEMPX_WriteLogFile( QString( "Unable to write CUAC input/output CSV export file:  %1" ).arg( sJA13CSVFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            else
            {
               FILE *fp_CSV;
               int iErrorCode;
               try
               {
                  iErrorCode = fopen_s( &fp_CSV, sJA13CSVFN.toLocal8Bit().constData(), "wb" );   // Overwrite CSV
                  if (iErrorCode != 0 || fp_CSV == NULL)
                     BEMPX_WriteLogFile( QString( "Error encountered opening CUAC JA13 TOU detail CSV file:  %1" ).arg( sJA13CSVFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {  const char* pszDOWLbls[] = {  "Mon",  "Tue",  "Wed",  "Thu",  "Fri",  "Sat",  "Sun"  };
                     QString sElecUtility        = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     QString sG2ElecTerritory    = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     QString sG2ElecTariff       = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     QString sElecTariffType     = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     QString sElecTariffAdj      = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj"   ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     QString sG2ElecTariffERN    = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTariffERN" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     long lG2ElecTariffUpdMonth  = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdMonth" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     long lG2ElecTariffUpdDay    = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdDay"   ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     long lG2ElecTariffUpdYear   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdYear"  ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                     fprintf( fp_CSV,  "1,format ID,\n" );
                     fprintf( fp_CSV,  "Electric Utility:,\n" );
                     fprintf( fp_CSV,  ",Name,,\"%s\",\n",            sElecUtility.toLocal8Bit().constData()     );
                     fprintf( fp_CSV,  ",Territory,,\"%s\",\n",       sG2ElecTerritory.toLocal8Bit().constData() );
                     fprintf( fp_CSV,  ",Tariff,,\"%s\",\n",          sG2ElecTariff.toLocal8Bit().constData()    );
                     fprintf( fp_CSV,  ",Type,,\"%s\",\n",            sElecTariffType.toLocal8Bit().constData()  );
                     fprintf( fp_CSV,  ",Adjustment,,\"%s\",\n",      sElecTariffAdj.toLocal8Bit().constData()   );
                     fprintf( fp_CSV,  ",EncodedRateName,,\"%s\",\n", sG2ElecTariffERN.toLocal8Bit().constData() );
                     fprintf( fp_CSV,  ",Date,,%d/%d/%d,\n",          lG2ElecTariffUpdMonth, lG2ElecTariffUpdDay, lG2ElecTariffUpdYear );
                     fprintf( fp_CSV,  ",,,,,,,,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,\n" );
                     fprintf( fp_CSV,  "Mo,Da,DOW,1Start,1Hrs,2Start,2Hrs,,'12-1,,'2-3,,'4-5,,'6-7,,'8-9,,'10-11,,noon-1,,'2-3,,'4-5,,'6-7,,'8-9,,'10-11,,\n" );
                     QString qsHrlyVals;
                     int iYrHr=0, iDOW;
                     i0YrDay = 0;
                     for (iMo=1; iMo<=12; iMo++)
                        for (iDay=1; iDay<=iNumDaysInMonth[iMo-1]; iDay++)
                        {
                           iDOW = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDOW>=0 && iDOW<7) );      // 0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                           qsHrlyVals = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24," ).arg( 
                                 QString::number( daHrlyElecCost[iYrHr   ] ), QString::number( daHrlyElecCost[iYrHr+ 1] ), QString::number( daHrlyElecCost[iYrHr+ 2] ), QString::number( daHrlyElecCost[iYrHr+ 3] ),
                                 QString::number( daHrlyElecCost[iYrHr+ 4] ), QString::number( daHrlyElecCost[iYrHr+ 5] ), QString::number( daHrlyElecCost[iYrHr+ 6] ), QString::number( daHrlyElecCost[iYrHr+ 7] ), 
                                 QString::number( daHrlyElecCost[iYrHr+ 8] ), QString::number( daHrlyElecCost[iYrHr+ 9] ), QString::number( daHrlyElecCost[iYrHr+10] ), QString::number( daHrlyElecCost[iYrHr+11] ), 
                                 QString::number( daHrlyElecCost[iYrHr+12] ), QString::number( daHrlyElecCost[iYrHr+13] ), QString::number( daHrlyElecCost[iYrHr+14] ), QString::number( daHrlyElecCost[iYrHr+15] ), 
                                 QString::number( daHrlyElecCost[iYrHr+16] ), QString::number( daHrlyElecCost[iYrHr+17] ), QString::number( daHrlyElecCost[iYrHr+18] ), QString::number( daHrlyElecCost[iYrHr+19] ), 
                                 QString::number( daHrlyElecCost[iYrHr+20] ), QString::number( daHrlyElecCost[iYrHr+21] ), QString::number( daHrlyElecCost[iYrHr+22] ), QString::number( daHrlyElecCost[iYrHr+23] )  );
                           fprintf( fp_CSV,  "%d,%d,%s,%d,%d,%d,%d,$/kWh,%s\n",  iMo, iDay, pszDOWLbls[iDOW],
                                                   iDayFirstPeakHr[0][i0YrDay], iDayPeakDuration[0][i0YrDay],
                                                   iDayFirstPeakHr[1][i0YrDay], iDayPeakDuration[1][i0YrDay], qsHrlyVals.toLocal8Bit().constData() );
                           iYrHr += 24;
                           i0YrDay++;
                        }
                     fflush( fp_CSV );
                     fclose( fp_CSV );
                  }
               }
               catch( ... ) {
                  BEMPX_WriteLogFile( QString( "Unknown error writing CUAC JA13 TOU detail CSV file:  %1" ).arg( sJA13CSVFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
         }  }
      }  // end of if (bTOUPricesFound)

   }


   double dAffordablePVDCSysSizeFrac=0.0, dAffordableBattMaxCapFrac=0.0;
   double* pdaInitDHWElec[] = {  NULL, NULL, NULL, NULL, NULL, NULL, NULL };
   if (bOldCUAC)
   {  // add setting of CUAC:RunDateFmt when processing OldCUAC projects - SAC 01/10/24
		QString sRunDateFmt;
		QDateTime current = QDateTime::currentDateTime();
		long lTime = (long) current.toTime_t();	// seconds since 1970-Jan-01 / valid as long int until 2038-Jan-19 / switching to uint extends valid date range to 2106-Feb-07
		long lDBID_RunDate = BEMPX_GetDatabaseID( "Proj:RunDate" );
		BEMPX_SetBEMData( lDBID_RunDate, BEMP_Int, (void*) &lTime );
      BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -4 /*iPrecision*/ );      // format: "M/d/yyyy h:m:s ap"
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), BEMP_QStr, (void*) &sRunDateFmt ); 
   }
   else  // if (!bOldCUAC)
   {


      // Adjustments to energy use streams to account for CUAC equipment efficiency inputs -- TO DO ??


      // Adjust DHW elec use for meters w/ JA13 (demand response) HPWHs - SAC 01/12/25 (tic #1388)
      if (lPerformJA13DHWBillAdjustments > 0 && !bExcludeDHW && iNumJA13DHWTOUPeriodDays > 0)
      {  iFuel = 0;
         double dJA13DHWBillAdjUseIncreaseFrac = BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUAC:JA13DHWBillAdjPctUseIncrease" ), iSpecVal, iErr,    // SAC 01/17/25
                                                                  0, BEMO_User, iCUAC_BEMProcIdx, false, 7.0 ) * 0.01;     // frac increase in DHW elec use on peak-shifted days
         double dJA13DHWBillAdjMaxOffPeakMult  = BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUAC:JA13DHWBillAdjMaxOffPeakMult" ), iSpecVal, iErr,    // SAC 01/22/25
                                                                  0, BEMO_User, iCUAC_BEMProcIdx, false, 5.0 );     // maximum off-peak elec use multiplier (to cover on-peak reduction), else remaining use distributed evenly in 4 prior hours
         for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         {  long lNumUnits;   double dMtrJA13DHWAdjFactor = 0.0;
            BEMPX_GetInteger( BEMPX_GetDatabaseID( "AffordableUnitsByBedrms",            iCID_CUAC )+iMtr, lNumUnits           , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
            // on-peak elec use multiplier for each unit type having JA13 HPWHs - SAC 01/15/25
            BEMPX_GetFloat(   BEMPX_GetDatabaseID( "AffordableUnitJA13DHWBillAdjFactor", iCID_CUAC )+iMtr, dMtrJA13DHWAdjFactor, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
            if (lNumUnits > 0 && dMtrJA13DHWAdjFactor >= 0.0001)
            {  double *pdDHWUse=NULL;
               const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[0][iMtr] : pszCUACResMeters[0]); 
               BEMPX_GetHourlyResultArrayPtr( &pdDHWUse, NULL, 0, "Proposed", pszCUACMtr, "Dhw", iCUAC_BEMProcIdx );    assert( pdDHWUse );
               if (pdDHWUse)
               {  double dInitDHWAnnUse=0.0, dAdjDHWAnnUse=0.0;
                  pdaInitDHWElec[iMtr] = (double*) malloc( sizeof(double) * 8760 );
                  int iYrHr=0, iDOW;
                  for (iYrHr=0; iYrHr<8760; iYrHr++)
                  {  pdaInitDHWElec[iMtr][iYrHr] = pdDHWUse[iYrHr];
                     dInitDHWAnnUse             += pdDHWUse[iYrHr];
                  }

                  const char* pszDOWLbls[] = {  "Mon",  "Tue",  "Wed",  "Thu",  "Fri",  "Sat",  "Sun"  };
                  QString sJA13CSVFN = sProcessingPath + sModelFileOnly + QString(" - JA13 TOU detail - %1.csv").arg( pszCUACCSVUnitTypeLabels[iMtr] );
                  bool bWriteJA13DetailsCSVFile = (iBillCalcDetails > 0);
                  if (bWriteJA13DetailsCSVFile)  // write CSV file w/ TOU detail by day
                  {  QString sJA13CSVMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                                  "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                                  "(once the file is closed), or \n'Abort' to abort the %s.", "CSV", sJA13CSVFN.toLocal8Bit().constData(), "CSV export" );
                     bWriteJA13DetailsCSVFile = OKToWriteOrDeleteFile( sJA13CSVFN.toLocal8Bit().constData(), sJA13CSVMsg, bSilent );
                  }
                  FILE *fp_CSV;
                  try
                  {
                     if (bWriteJA13DetailsCSVFile)  // write CSV file w/ TOU detail by day
                     {  int iErrorCode = fopen_s( &fp_CSV, sJA13CSVFN.toLocal8Bit().constData(), "wb" );   // Overwrite CSV
                        bWriteJA13DetailsCSVFile = (iErrorCode == 0 && fp_CSV != NULL);
                        if (!bWriteJA13DetailsCSVFile)
                           BEMPX_WriteLogFile( QString( "Error encountered opening CUAC JA13 TOU %1 detail CSV file:  %2" ).arg( pszCUACCSVUnitTypeLabels[iMtr], sJA13CSVFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                     }
                     if (bWriteJA13DetailsCSVFile) 
                     {  
                        QString sElecUtility        = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        QString sG2ElecTerritory    = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        QString sG2ElecTariff       = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        QString sElecTariffType     = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        QString sElecTariffAdj      = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj"   ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        QString sG2ElecTariffERN    = BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTariffERN" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        long lG2ElecTariffUpdMonth  = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdMonth" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        long lG2ElecTariffUpdDay    = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdDay"   ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        long lG2ElecTariffUpdYear   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffUpdYear"  ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
                        fprintf( fp_CSV,  "1,format ID,\n" );
                        fprintf( fp_CSV,  "Electric Utility:,\n" );
                        fprintf( fp_CSV,  ",Name,,\"%s\",\n",            sElecUtility.toLocal8Bit().constData()     );
                        fprintf( fp_CSV,  ",Territory,,\"%s\",\n",       sG2ElecTerritory.toLocal8Bit().constData() );
                        fprintf( fp_CSV,  ",Tariff,,\"%s\",\n",          sG2ElecTariff.toLocal8Bit().constData()    );
                        fprintf( fp_CSV,  ",Type,,\"%s\",\n",            sElecTariffType.toLocal8Bit().constData()  );
                        fprintf( fp_CSV,  ",Adjustment,,\"%s\",\n",      sElecTariffAdj.toLocal8Bit().constData()   );
                        fprintf( fp_CSV,  ",EncodedRateName,,\"%s\",\n", sG2ElecTariffERN.toLocal8Bit().constData() );
                        fprintf( fp_CSV,  ",Date,,%d/%d/%d,\n",          lG2ElecTariffUpdMonth, lG2ElecTariffUpdDay, lG2ElecTariffUpdYear );
                        fprintf( fp_CSV,  ",Dwelling Type,,\"%s\",\n",   pszCUACCSVUnitTypeLabels[iMtr] );

                        fprintf( fp_CSV,  ",,,,,,,,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,\n" );
                        fprintf( fp_CSV,  "Mo,Da,DOW,1Start,1Hrs,2Start,2Hrs,,'12-1,,'2-3,,'4-5,,'6-7,,'8-9,,'10-11,,noon-1,,'2-3,,'4-5,,'6-7,,'8-9,,'10-11,,\n" );
                     }

                     i0YrDay = iYrHr = 0;
                     for (iMo=1; iMo<=12; iMo++)
                        for (iDay=1; iDay<=iNumDaysInMonth[iMo-1]; iDay++)
                        {
                           iDOW = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDOW>=0 && iDOW<7) );      // 0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                           double dDayUse[3] = {  0.0,  0.0,  0.0  };
                           dDayUse[0] = DayHourlySum( &pdDHWUse[iYrHr] );
                           int iEarliestHrMod = 0, iPkDayIdx = 0;
                           if (iDayFirstPeakHr[0][i0YrDay] >= 0 && iDayFirstPeakHr[1][i0YrDay] >= 0)
                           {  // Two individual peaks this day! - process fist (earlier) one first

                              assert( false );
                           //
                           // --- TO DO ---
                           //

                           }
                           else if (iDayFirstPeakHr[0][i0YrDay] >= 0 || iDayFirstPeakHr[1][i0YrDay] >= 0)
                           {  // Single peak period this day
                              iPkDayIdx = (iDayFirstPeakHr[0][i0YrDay] >= 0 ? 0 : 1);
                              daOffPeakUseMult[iPkDayIdx][i0YrDay] = AdjustJA13HPWHDayUseProfile( &pdDHWUse[iYrHr],
                                                                           iDayFirstPeakHr[iPkDayIdx][i0YrDay],
                                                                           iDayPeakDuration[iPkDayIdx][i0YrDay],
                                                                           dMtrJA13DHWAdjFactor, 2.3 /*dTargetOffPeakUseMult*/,
                                                                           dJA13DHWBillAdjMaxOffPeakMult,
                                                                           iEarliestHrMod, (dDayUse[0] * dJA13DHWBillAdjUseIncreaseFrac) /*dTargetUseTotIncrease*/ );     assert( daOffPeakUseMult[iPkDayIdx][i0YrDay] > 1.0 );
                              dDayUse[1] = DayHourlySum( &pdDHWUse[iYrHr] );
                              daPctDayElecUseIncrease[iPkDayIdx][i0YrDay] = (dDayUse[0] < 0.01 ? 0.0 :
                                                                              (100.0 * (dDayUse[1] - dDayUse[0]) / dDayUse[0]) );
                           }
                           // else - NO peak, therefore NO changes to this day's elec use

                           //       daOffPeakUseMult[       0][iDay] = 0.0;   daOffPeakUseMult[       1][iDay] = 0.0;
                           //       daPctDayElecUseIncrease[0][iDay] = 0.0;   daPctDayElecUseIncrease[1][iDay] = 0.0;
                           //fprintf( fp_CSV,  "%d,%d,%s,%d,%d,%d,%d,%s\n",  iMo, iDay, pszDOWLbls[iDOW],
                           //                        iDayFirstPeakHr[0][i0YrDay], iDayPeakDuration[0][i0YrDay],
                           //                        iDayFirstPeakHr[1][i0YrDay], iDayPeakDuration[1][i0YrDay], qsHrlyVals.toLocal8Bit().constData() );


                           if (bWriteJA13DetailsCSVFile) 
                           {  QString qsHrlyVals = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24," ).arg( 
                                    QString::number( daHrlyElecCost[iYrHr   ] ), QString::number( daHrlyElecCost[iYrHr+ 1] ), QString::number( daHrlyElecCost[iYrHr+ 2] ), QString::number( daHrlyElecCost[iYrHr+ 3] ),
                                    QString::number( daHrlyElecCost[iYrHr+ 4] ), QString::number( daHrlyElecCost[iYrHr+ 5] ), QString::number( daHrlyElecCost[iYrHr+ 6] ), QString::number( daHrlyElecCost[iYrHr+ 7] ), 
                                    QString::number( daHrlyElecCost[iYrHr+ 8] ), QString::number( daHrlyElecCost[iYrHr+ 9] ), QString::number( daHrlyElecCost[iYrHr+10] ), QString::number( daHrlyElecCost[iYrHr+11] ), 
                                    QString::number( daHrlyElecCost[iYrHr+12] ), QString::number( daHrlyElecCost[iYrHr+13] ), QString::number( daHrlyElecCost[iYrHr+14] ), QString::number( daHrlyElecCost[iYrHr+15] ), 
                                    QString::number( daHrlyElecCost[iYrHr+16] ), QString::number( daHrlyElecCost[iYrHr+17] ), QString::number( daHrlyElecCost[iYrHr+18] ), QString::number( daHrlyElecCost[iYrHr+19] ), 
                                    QString::number( daHrlyElecCost[iYrHr+20] ), QString::number( daHrlyElecCost[iYrHr+21] ), QString::number( daHrlyElecCost[iYrHr+22] ), QString::number( daHrlyElecCost[iYrHr+23] )  );
                              fprintf( fp_CSV,  "%d,%d,%s,%d,%d,%d,%d,$/kWh,%s\n",  iMo, iDay, pszDOWLbls[iDOW],
                                                      iDayFirstPeakHr[0][i0YrDay], iDayPeakDuration[0][i0YrDay],
                                                      iDayFirstPeakHr[1][i0YrDay], iDayPeakDuration[1][i0YrDay], qsHrlyVals.toLocal8Bit().constData() );
                              qsHrlyVals = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24," ).arg( 
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr   ] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 1] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 2] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 3] ),
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr+ 4] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 5] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 6] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 7] ), 
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr+ 8] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+ 9] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+10] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+11] ), 
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr+12] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+13] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+14] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+15] ), 
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr+16] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+17] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+18] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+19] ), 
                                    QString::number( pdaInitDHWElec[iMtr][iYrHr+20] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+21] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+22] ), QString::number( pdaInitDHWElec[iMtr][iYrHr+23] )  );
                              fprintf( fp_CSV,  ",,,OffPk mult,%g,init sum,%g,kWh before,%s\n",  daOffPeakUseMult[iPkDayIdx][i0YrDay], dDayUse[0], qsHrlyVals.toLocal8Bit().constData() );
                              qsHrlyVals = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24," ).arg( 
                                    QString::number( pdDHWUse[iYrHr   ] ), QString::number( pdDHWUse[iYrHr+ 1] ), QString::number( pdDHWUse[iYrHr+ 2] ), QString::number( pdDHWUse[iYrHr+ 3] ),
                                    QString::number( pdDHWUse[iYrHr+ 4] ), QString::number( pdDHWUse[iYrHr+ 5] ), QString::number( pdDHWUse[iYrHr+ 6] ), QString::number( pdDHWUse[iYrHr+ 7] ), 
                                    QString::number( pdDHWUse[iYrHr+ 8] ), QString::number( pdDHWUse[iYrHr+ 9] ), QString::number( pdDHWUse[iYrHr+10] ), QString::number( pdDHWUse[iYrHr+11] ), 
                                    QString::number( pdDHWUse[iYrHr+12] ), QString::number( pdDHWUse[iYrHr+13] ), QString::number( pdDHWUse[iYrHr+14] ), QString::number( pdDHWUse[iYrHr+15] ), 
                                    QString::number( pdDHWUse[iYrHr+16] ), QString::number( pdDHWUse[iYrHr+17] ), QString::number( pdDHWUse[iYrHr+18] ), QString::number( pdDHWUse[iYrHr+19] ), 
                                    QString::number( pdDHWUse[iYrHr+20] ), QString::number( pdDHWUse[iYrHr+21] ), QString::number( pdDHWUse[iYrHr+22] ), QString::number( pdDHWUse[iYrHr+23] )  );
                              fprintf( fp_CSV,  ",,,%% kWh inc,%g,aft sum,%g,kWh after,%s\n",  daPctDayElecUseIncrease[iPkDayIdx][i0YrDay], dDayUse[1], qsHrlyVals.toLocal8Bit().constData() );
                           }

                           iYrHr += 24;
                           i0YrDay++;
                        }

                     if (bWriteJA13DetailsCSVFile) 
                     {  fflush( fp_CSV );
                        fclose( fp_CSV );
                     }
                  }
                  catch( ... ) {
                     BEMPX_WriteLogFile( QString( "Unknown error writing CUAC JA13 TOU %1 detail CSV file:  %2" ).arg( pszCUACCSVUnitTypeLabels[iMtr], sJA13CSVFN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  }

            }  }
      }  }


      // Divvy PV & Batt based on PVAllocMethod - SAC 11/21/22
      double dPVAnnual = BEMPX_GetHourlyResultSum(   NULL, 0, "Proposed", "Electricity", "Photovoltaics", NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
      if (dPVAnnual == -99999.0)
         dPVAnnual = 0.0;
      double dBattAnnual = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", "Electricity", "Battery",       NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
      if (dBattAnnual == -99999.0)
         dBattAnnual = 0.0;
      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordablePVDCSysSizeFrac", iCID_CUAC ), dAffordablePVDCSysSizeFrac, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordableBattMaxCapFrac",  iCID_CUAC ), dAffordableBattMaxCapFrac , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
      if ( (dPVAnnual != 0.0 || dBattAnnual != 0.0) && (dAffordablePVDCSysSizeFrac > 0 || dAffordableBattMaxCapFrac > 0) )
      {
         double daDwellingPVFrac[NumDwellingMeters], daDwellingBattFrac[NumDwellingMeters];
         long lPVAllocMethod=0;     // 0: Num Residents / 1: Electricity Use / 2: User Allocation
         if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "PVAllocMethod", iCID_CUAC ), lPVAllocMethod, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) || lPVAllocMethod == 2)
         {  // Divvy PV/Batt into affordable housing meters by user specified allocation percentages - SAC 12/09/22
            long lNumUnits;
            double dPctIndivPV, dPctIndivPVSum, dPctIndivBatt;
            if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PctIndivUnitPVSum", iCID_CUAC ), dPctIndivPVSum, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) ||
                  dPctIndivPVSum < 99.96 || dPctIndivPVSum > 100.04)
            {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
               sErrMsg = QString( "CUAC Error: Invalid or missing PV allocation by unit type data. Access these inputs via PV Allocation button in CUAC dialog tab." );
               BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               return;
            }
            else
            {  for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
               {  BEMPX_GetInteger( BEMPX_GetDatabaseID( "AffordableUnitsByBedrms", iCID_CUAC )+iMtr, lNumUnits  , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
                  if (lNumUnits > 0 && BEMPX_GetFloat( BEMPX_GetDatabaseID( "PctIndivUnitPVByBedrms" , iCID_CUAC )+iMtr, dPctIndivPV, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && dPctIndivPV > 0)
                     daDwellingPVFrac[iMtr] = (dPctIndivPV * (iDataModel == 1 ? 1 : lNumUnits)) / 100.0;   // SFam analysis always models just a single dwelling - SAC 10/22/24
                  else
                     daDwellingPVFrac[iMtr] = 0.0;
                  if (lNumUnits > 0 && BEMPX_GetFloat( BEMPX_GetDatabaseID( "PctIndivUnitBattByBedrms" , iCID_CUAC )+iMtr, dPctIndivBatt, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && dPctIndivBatt > 0)
                     daDwellingBattFrac[iMtr] = (dPctIndivBatt * (iDataModel == 1 ? 1 : lNumUnits)) / 100.0;   // support separate Battery allocation data - SAC 11/14/25 (tic #3641)
                  else
                     daDwellingBattFrac[iMtr] = 0.0;
            }  }
         }
         else if (lPVAllocMethod == 0)
         {  // Divvy PV/Batt into affordable housing meters by number of residents - SAC 11/21/22
            for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
            {  BEMPX_GetFloat( BEMPX_GetDatabaseID( "ResidentFracByBedrms", iCID_CUAC )+iMtr, daDwellingPVFrac[iMtr], 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
               daDwellingBattFrac[iMtr] = daDwellingPVFrac[iMtr];
         }  }
         else
         {  // Divvy PV/Batt into affordable housing meters by annual dwelling electric use - SAC 09/10/22
            double dTotalAllDwellingElecUse = 0.0;
            for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
            {
               const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[0][iMtr] : pszCUACResMeters[0]);      // SAC 05/31/24
               if (laNumUnitsByBedrms[iMtr] < 1)
               {  daDwellingPVFrac[iMtr] = daDwellingBattFrac[iMtr] = 0.0;
               }
               else
               {  if (iDataModel == 1)       // Res - SAC 06/02/24 (res tic #1378)
                  {  daDwellingPVFrac[iMtr] = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[0], pszInitialCUACResEnduses[1], pszInitialCUACResEnduses[2], pszInitialCUACResEnduses[3],
                                                                                                             pszInitialCUACResEnduses[4], pszInitialCUACResEnduses[5], pszInitialCUACResEnduses[6], pszInitialCUACResEnduses[7], iCUAC_BEMProcIdx );
                     if (daDwellingPVFrac[iMtr] == -99999.0)
                        daDwellingPVFrac[iMtr] = 0.0;
                     double dTemp = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[ 8], pszInitialCUACResEnduses[ 9], pszInitialCUACResEnduses[10], pszInitialCUACResEnduses[11],
                                                                                               pszInitialCUACResEnduses[12], pszInitialCUACResEnduses[13], pszInitialCUACResEnduses[14], pszInitialCUACResEnduses[15], iCUAC_BEMProcIdx );
                     if (dTemp != -99999.0)
                        daDwellingPVFrac[iMtr] += dTemp;

                     dTemp        = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[16], pszInitialCUACResEnduses[17], pszInitialCUACResEnduses[18], pszInitialCUACResEnduses[19],
                                                                                               pszInitialCUACResEnduses[20], pszInitialCUACResEnduses[21], pszInitialCUACResEnduses[22], pszInitialCUACResEnduses[23], iCUAC_BEMProcIdx );
                     if (dTemp != -99999.0)
                        daDwellingPVFrac[iMtr] += dTemp;
                  }
                  else 
                  {  daDwellingPVFrac[iMtr] = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACEnduses[0], pszInitialCUACEnduses[1], pszInitialCUACEnduses[2], pszInitialCUACEnduses[3],
                                                                                                             pszInitialCUACEnduses[4], pszInitialCUACEnduses[5], pszInitialCUACEnduses[6], pszInitialCUACEnduses[7], iCUAC_BEMProcIdx );
                     if (daDwellingPVFrac[iMtr] == -99999.0)
                        daDwellingPVFrac[iMtr] = 0.0;
                     double dTemp = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACEnduses[8], pszInitialCUACEnduses[9], pszInitialCUACEnduses[10], pszInitialCUACEnduses[11],
                                                                                               pszInitialCUACEnduses[12], pszInitialCUACEnduses[13], NULL, NULL, iCUAC_BEMProcIdx );
                     if (dTemp != -99999.0)
                        daDwellingPVFrac[iMtr] += dTemp;
                  }
                  dTotalAllDwellingElecUse += daDwellingPVFrac[iMtr];
            }  }

            assert( dTotalAllDwellingElecUse > 0 );
            if (dTotalAllDwellingElecUse > 0)
               for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
               {  if (daDwellingPVFrac[iMtr] > 0)
                     daDwellingPVFrac[iMtr] = daDwellingPVFrac[iMtr] / dTotalAllDwellingElecUse;
                  daDwellingBattFrac[iMtr] = daDwellingPVFrac[iMtr];
               }
         }
               if (iBillCalcDetails > 0)
                  BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - PV allocation fracs:  %1 | %2 | %3 | %4 | %5 | %6 | %7" ).arg( QString::number( daDwellingPVFrac[0] ), QString::number( daDwellingPVFrac[1] ), QString::number( daDwellingPVFrac[2] ), QString::number( daDwellingPVFrac[3] ),
                                       QString::number( daDwellingPVFrac[4] ), QString::number( daDwellingPVFrac[5] ), QString::number( daDwellingPVFrac[6] ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

         double *pdPVHrlyData=NULL, *pdBattHrlyData=NULL;
         if (dPVAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdPVHrlyData  , NULL, 0, "Proposed", "Electricity", "Photovoltaics", iCUAC_BEMProcIdx );
         if (dBattAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdBattHrlyData, NULL, 0, "Proposed", "Electricity", "Battery"      , iCUAC_BEMProcIdx );

         for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         {  const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[0][iMtr] : pszCUACResMeters[0]);      // SAC 05/31/24
            if (daDwellingPVFrac[iMtr] > 0)
            {  // PV
               if (pdPVHrlyData && dAffordablePVDCSysSizeFrac > 0)
                  BEMPX_SumIntoHourlyResultArray( pdPVHrlyData, "Proposed", pszCUACMtr, "Photovoltaics", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordablePVDCSysSizeFrac * daDwellingPVFrac[iMtr]) );
            }
            if (daDwellingBattFrac[iMtr] > 0)      // SAC 11/14/24 (tic #3641)
            {  // Battery
               if (pdBattHrlyData && dAffordableBattMaxCapFrac > 0)
                  BEMPX_SumIntoHourlyResultArray( pdBattHrlyData, "Proposed", pszCUACMtr, "Battery", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordableBattMaxCapFrac * daDwellingBattFrac[iMtr]) );
         }  }
      }
                                             iStep = 2;     sStep = "PV-Batt";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }


      // TO DO - DIVVY UP ACROSS ALL FUELS, not BY INDIVIDUAL FUEL

      // Merge enduses into final reporting set - SAC 09/10/22
      for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         if (laNumUnitsByBedrms[iMtr] > 0)
            for (iFuel=0; iFuel < 2; iFuel++)
            {
               int iResMtrIdx = (iFuel == 0 ? 0 : iResFuelMtrIdx);      // SAC 09/11/24 (res tic #1378)
               const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[iFuel][iMtr] : pszCUACResMeters[iResMtrIdx]);    // SAC 05/31/24
               // Com - split Other HVAC into Cooling & Heating
               if (iDataModel == 0)
               {  double dHVACOthrUse = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, "HVAC Other", NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                  if (dHVACOthrUse > 0)
                  {  double dCoolAdd[8760], dHeatAdd[8760];
                     double *pdCool=NULL, *pdHeat=NULL, *pdHVACOthr=NULL;
                     BEMPX_GetHourlyResultArrayPtr( &pdCool    , NULL, 0, "Proposed", pszCUACMtr, "Cooling"   , iCUAC_BEMProcIdx );
                     BEMPX_GetHourlyResultArrayPtr( &pdHeat    , NULL, 0, "Proposed", pszCUACMtr, "Heating"   , iCUAC_BEMProcIdx );
                     BEMPX_GetHourlyResultArrayPtr( &pdHVACOthr, NULL, 0, "Proposed", pszCUACMtr, "HVAC Other", iCUAC_BEMProcIdx );
                     iHr = 0;
                     for (iMo=0; iMo<12; iMo++)
                        for (iDay=0; iDay<iNumDaysInMonth[iMo]; iDay++)
                        {  double dCoolDay=0.0, dHeatDay=0.0;
                           int iEndDayHr = iHr+24;
                           for (iTemp=iHr; iTemp < iEndDayHr; iTemp++)
                           {  dCoolDay += (pdCool ? pdCool[iTemp] : 0.0);
                              dHeatDay += (pdHeat ? pdHeat[iTemp] : 0.0);
                           }
                           bool bAllCool = ( (dCoolDay > 0 && dHeatDay < 0.0001) || (dCoolDay < 0.0001 && dHeatDay < 0.0001 &&  bCoolingMonth[iMo]) );
                           bool bAllHeat = ( (dHeatDay > 0 && dCoolDay < 0.0001) || (dCoolDay < 0.0001 && dHeatDay < 0.0001 && !bCoolingMonth[iMo]) );
                           assert( bAllCool || bAllHeat || (dCoolDay > 0.0001 && dHeatDay > 0.0001) );
                           for (iTemp=iHr; (pdHVACOthr && iTemp < iEndDayHr); iTemp++)
                           {  if (pdHVACOthr[iTemp] <= 0.0)
                              {  dCoolAdd[iTemp] = 0.0;
                                 dHeatAdd[iTemp] = 0.0;
                              }
                              else if (bAllCool)
                              {  dCoolAdd[iTemp] = pdHVACOthr[iTemp];
                                 dHeatAdd[iTemp] = 0.0;
                              }
                              else if (bAllHeat)
                              {  dCoolAdd[iTemp] = 0.0;
                                 dHeatAdd[iTemp] = pdHVACOthr[iTemp];
                              }
                              else if (dCoolDay > 0.0001 && dHeatDay > 0.0001)
                              {  dCoolAdd[iTemp] = pdHVACOthr[iTemp] * (dCoolDay / (dCoolDay + dHeatDay));
                                 dHeatAdd[iTemp] = (pdHVACOthr[iTemp] - dCoolAdd[iTemp]);
                              }
                              else
                              {  assert( false );
                                 dCoolAdd[iTemp] = 0.0;
                                 dHeatAdd[iTemp] = 0.0;
                           }  }
                           iHr += 24;
                        }

                     BEMPX_AddHourlyResultArray(     NULL,     "Proposed", pszCUACMtr, "HVAC Other", iCUAC_BEMProcIdx );   // zero out "HVAC Other" enduse
                     BEMPX_SumIntoHourlyResultArray( dCoolAdd, "Proposed", pszCUACMtr, "Cooling"   , iCUAC_BEMProcIdx );
                     BEMPX_SumIntoHourlyResultArray( dHeatAdd, "Proposed", pszCUACMtr, "Heating"   , iCUAC_BEMProcIdx );
                  }
                  // removed merging of Batt into PV, now that we are tracking batt separately - SAC 12/12/24
                  // if (dAffordableBattMaxCapFrac > 0.0001)      // add logic to sum Batt into PV (following scaling) - SAC 11/12/24 (tic #3641)
                  // {  double *pdAdd=NULL;
                  //    BEMPX_GetHourlyResultArrayPtr(    &pdAdd, NULL, 0, "Proposed", pszCUACMtr, "Battery"      , iCUAC_BEMProcIdx );       assert(pdAdd);
                  //    if (pdAdd)
                  //    {  BEMPX_SumIntoHourlyResultArray( pdAdd, "Proposed", pszCUACMtr,          "Photovoltaics", iCUAC_BEMProcIdx );
                  //       BEMPX_AddHourlyResultArray(      NULL, "Proposed", pszCUACMtr,          "Battery"      , iCUAC_BEMProcIdx );   // zero out enduse summed into another
                  // }  }
               }
               // Res - merge CSE enduses into CUAC reporting group - SAC 06/02/24 (res tic #1378)
               if (iDataModel == 1)
               {  for (int iEU=0; iEU < NumInitialResEnduses; iEU++)
                     if (iaCUACResEnduseActions[iEU] >= 0 && iaCUACResEnduseActions[iEU] < NumInitialResEnduses)
                     {  assert( iaCUACResEnduseActions[iEU] != iEU );  // shouldn't ever copy enduse onto itself
                        double dEUEnergyUse = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[iEU], NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                        if (dEUEnergyUse != 0 && dEUEnergyUse > -99998.0)
                        {  double *pdAdd=NULL;
                           BEMPX_GetHourlyResultArrayPtr(    &pdAdd, NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[              iEU ], iCUAC_BEMProcIdx );       assert(pdAdd);
                           if (pdAdd)
                           {  BEMPX_SumIntoHourlyResultArray( pdAdd, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[iaCUACResEnduseActions[iEU]], iCUAC_BEMProcIdx );
                              BEMPX_AddHourlyResultArray(      NULL, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[                       iEU ], iCUAC_BEMProcIdx );   // zero out enduse summed into another
                     }  }  }
                  if (bExcludeDHW)     // SAC 09/04/24
                     BEMPX_AddHourlyResultArray( NULL, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[ 3 /*DHW*/ ], iCUAC_BEMProcIdx );   // zero out DHW enduse if analysis to exclude it
                  if (dAffordablePVDCSysSizeFrac < 1.0)     // SAC 09/07/24
                     BEMPX_ScaleHourlyResultArray( dAffordablePVDCSysSizeFrac, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[ 23 /*PV*/   ], iCUAC_BEMProcIdx );
                  if (dAffordableBattMaxCapFrac < 1.0)
                     BEMPX_ScaleHourlyResultArray( dAffordableBattMaxCapFrac,  "Proposed", pszCUACMtr, pszInitialCUACResEnduses[ 22 /*Batt*/ ], iCUAC_BEMProcIdx );
               // restore if/when Battery enduse allowed in Res CUAC analysis - SAC 11/12/24 (tic #3641)
               //   if (dAffordableBattMaxCapFrac > 0.0001)      // add logic to sum Batt into PV (following scaling) - SAC 11/12/24 (tic #3641)
               //   {  double *pdAdd=NULL;
               //      BEMPX_GetHourlyResultArrayPtr(    &pdAdd, NULL, 0, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[ 22 /*Batt*/ ], iCUAC_BEMProcIdx );       assert(pdAdd);
               //      if (pdAdd)
               //      {  BEMPX_SumIntoHourlyResultArray( pdAdd, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[          23 /*PV*/   ], iCUAC_BEMProcIdx );
               //         BEMPX_AddHourlyResultArray(      NULL, "Proposed", pszCUACMtr, pszInitialCUACResEnduses[          22 /*Batt*/ ], iCUAC_BEMProcIdx );   // zero out enduse summed into another
               //   }  }
               }
            }
                                             iStep = 3;     sStep = "DistribEnduses";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

      // Reduce meters to energy use by dwelling unit - SAC 09/10/22
      for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         if (laNumUnitsByBedrms[iMtr] > 1 || (laNumUnitsByBedrms[iMtr] > 0 && iDataModel == 1))
            for (iFuel=0; iFuel < 2; iFuel++)
            {  double dFuelMult = 1.0;
               if (iDataModel == 1)
                  dFuelMult = (iFuel==0 ? 0.29307 : 0.01);    // Elec kBtu->kWh / Gas kBtu->therms - SAC 06/03/24 (res tic #1378)
               double dMult = dFuelMult / (double) laNumUnitsByBedrms[iMtr];
               int iResMtrIdx = (iFuel == 0 ? 0 : iResFuelMtrIdx);      // SAC 09/11/24 (res tic #1378)
               const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[iFuel][iMtr] : pszCUACResMeters[iResMtrIdx]);    // SAC 05/31/24
               int iMaxEnduse         = (iDataModel == 0 ? NumInitialEnduses : NumInitialResEnduses);
               for (iTemp=0; iTemp < iMaxEnduse; iTemp++)
               {  const char* pszCUACEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iTemp] : pszInitialCUACResEnduses[iTemp]);    // SAC 05/31/24
                  BEMPX_ScaleHourlyResultArray( dMult, "Proposed", pszCUACMtr, pszCUACEnduse, iCUAC_BEMProcIdx );
            }  }
                                             iStep = 4;     sStep = "SingleDwelling";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

   }  // end of if (!bOldCUAC)  --  done prepping & loading hourly energy use data

   // added total elec use calc - elec use sum of each hour where we are NOT exporting to grid - SAC 12/13/24
   double dTotNonExportElecUse[NumDwellingMeters];
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
      dTotNonExportElecUse[iMtr] = 0.0;
   if (!bOldCUAC)
   {  for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         if (laNumUnitsByBedrms[iMtr] > 0)
         {  int iCEUIdx;
            double *pdHrlyUse[NumCUACEnduses];
            const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[0/*iFuel*/][iMtr] : pszCUACResMeters[0/*elec*/]); 
            for (iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
            {  int iInitMtrIdx                  = (iDataModel == 0 ? iaInitToRptsEnduseMap[iCEUIdx]     : iaResInitToRptsEnduseMap[iCEUIdx]     );
               const char* pszHrlyResultsEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iInitMtrIdx] : pszInitialCUACResEnduses[iInitMtrIdx] );
               BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse[iCEUIdx], NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, iCUAC_BEMProcIdx );
                     //if (pdHrlyUse[iCEUIdx])
                     //      BEMPX_WriteLogFile( QString( "   cuac analysis - get hrly result ptr SUCCESS for run Proposed, meter %1, enduse %2" ).arg( pszCUACMtr, pszHrlyResultsEnduse ), NULL, FALSE, TRUE, FALSE );
                     //else  BEMPX_WriteLogFile( QString( "   cuac analysis - get hrly result ptr FAILED  for run Proposed, meter %1, enduse %2" ).arg( pszCUACMtr, pszHrlyResultsEnduse ), NULL, FALSE, TRUE, FALSE );
               if (pdHrlyUse[iCEUIdx] == NULL)
                  pdHrlyUse[iCEUIdx] = &daZero[0];
            }
            for (iHr=0; iHr<8760; iHr++)
            {  double dHrTot = 0.0;
               for (iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
                  dHrTot += pdHrlyUse[iCEUIdx][iHr];
               if (dHrTot >= 0.0001)
                  dTotNonExportElecUse[iMtr] += dHrTot;
            }
            if (iBillCalcDetails > 0)
               BEMPX_WriteLogFile( QString( "   meter '%1' annual elec use across hrs of positive use: %2 kWh  (hours of net export to grid ignored)" ).arg( pszCUACMtr, QString::number(dTotNonExportElecUse[iMtr]) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   }     }

                  if (iBillCalcDetails > 0) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupResults rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bResultsSetupEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupResults" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - errors encountered evaluating CUAC_SetupResults rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }


   // Retrieve hourly series' calculate & post monthly sums and utility bills
   double dZero = 0.0;
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
      if (laNumUnitsByBedrms[iMtr] > 0)
      {
         int iOldCUACAptObjIdx = -1;
         if (bOldCUAC)
         {  BEMObject* pOldCUACAptObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "AptDataRef", iCID_OldCUAC )+iMtr, iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
            iOldCUACAptObjIdx = (pOldCUACAptObj == NULL ? -1 : BEMPX_GetObjectIndex( pOldCUACAptObj->getClass(), pOldCUACAptObj, iCUAC_BEMProcIdx ));    assert( iOldCUACAptObjIdx >= 0 );
         }
         BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CUACResultsRef", iCID_CUAC )+iMtr, iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         for (iFuel=0; (iResObjIdx >= 0 && iFuel < 2); iFuel++)
         {
            double dTotSiteHourlyUse=0.0, dTotAnnUse=0.0, dCommunitySolarAnnCredit=0.0, dTotUseByMo[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
            double dTotUseByMoBeforeCarryover[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
            int iResMtrIdx = (iFuel == 0 ? 0 : iResFuelMtrIdx);      // SAC 09/11/24 (res tic #1378)
            const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[iFuel][iMtr] : pszCUACResMeters[iResMtrIdx]);    // SAC 05/31/24
            for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
            //{  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? (iCEUIdx==11 ? "ElecGen" : "ElecUse") : "GasUse");
            {  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? "ElecUse" : "GasUse");
               long lDBID_CEUFuelResult = BEMPX_GetDatabaseID( qsCEUFuelUseName );
               if (lDBID_CEUFuelResult > 0)     // some enduse/fuel combinations not possible or tracked
               {  int iInitMtrIdx                  = (iDataModel == 0 ? iaInitToRptsEnduseMap[iCEUIdx]     : iaResInitToRptsEnduseMap[iCEUIdx]     );
                  const char* pszHrlyResultsEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iInitMtrIdx] : pszInitialCUACResEnduses[iInitMtrIdx] );

                  if (!bOldCUAC)
                  {  // HOURLY simulation results
                     double dCEUAnnTot = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                     if ( (iCEUIdx==11 && dCEUAnnTot > -0.001) || (iCEUIdx!=11 && dCEUAnnTot < 0.01) )
                     {  for (iTemp=0; iTemp<14; iTemp++)
                           BEMPX_SetBEMData( lDBID_CEUFuelResult+iTemp, BEMP_Flt, (void*) &dZero, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }
                     else
                     {  double *pdHrlyUse=NULL;
                        double dAnnUse = 0.0;
                        BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse, NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, iCUAC_BEMProcIdx );
                        for (iMo=0; (pdHrlyUse && iMo<12); iMo++)
                        {  double dMoUse = 0.0;
                           for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                           {  dMoUse += pdHrlyUse[iHr];
                              dTotSiteHourlyUse += std::max( pdHrlyUse[iHr], 0.0 );
                           }
                           dAnnUse += dMoUse;
                           dTotUseByMo[iMo] += dMoUse;
                           BEMPX_SetBEMData( lDBID_CEUFuelResult+iMo, BEMP_Flt, (void*) &dMoUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }
                        dTotAnnUse = dAnnUse;
                        BEMPX_SetBEMData( lDBID_CEUFuelResult+12, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual
                        dAnnUse /= 365.0;
                        BEMPX_SetBEMData( lDBID_CEUFuelResult+13, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // daily
                     }
                  }  // end of if (!bOldCUAC)

                  else
                  {  // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                     long lDBID_OldCUACFuelResult = 0;
                     double dOldCUACEnergyScale = (iFuel==0 ? 1.0 : 0.01);  // scale kBtu -> therms for gas - SAC 09/19/23
                     if (pszOldCUACEnduseProps[iCEUIdx] && iOldCUACAptObjIdx >= 0)
                     {  QString qsOldCUACFuelUseName = pszOldCUACEnduseProps[iCEUIdx];
                        if (qsOldCUACFuelUseName.compare("PVGeneration") != 0)
                           qsOldCUACFuelUseName += (iFuel==0 ? "Elec" : "Gas");
                        lDBID_OldCUACFuelResult = BEMPX_GetDatabaseID( qsOldCUACFuelUseName, iCID_OldCUACApt );
                     }
                     double dMoUse, dAnnUse = 0.0;
                     for (iMo=0; iMo<12; iMo++)
                     {  if (iOldCUACAptObjIdx >= 0 && lDBID_OldCUACFuelResult > 0)
                           dMoUse = BEMPX_GetFloat( lDBID_OldCUACFuelResult+iMo, iSpecVal, iErr, 
                                                    iOldCUACAptObjIdx, BEMO_User, iCUAC_BEMProcIdx, false, 0.0 ) * dOldCUACEnergyScale;
                        else
                           dMoUse = 0.0;
                        dAnnUse += dMoUse;
                        dTotUseByMo[iMo] += dMoUse;
                        dTotSiteHourlyUse += std::max( dMoUse, 0.0 );
                        BEMPX_SetBEMData( lDBID_CEUFuelResult+iMo, BEMP_Flt, (void*) &dMoUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }
                     dTotAnnUse = dAnnUse;
                     BEMPX_SetBEMData( lDBID_CEUFuelResult+12, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual
                     dAnnUse /= 365.0;
                     BEMPX_SetBEMData( lDBID_CEUFuelResult+13, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // daily
                  }

                  for (iMo=0; iMo<12; iMo++)
                     dTotUseByMoBeforeCarryover[iMo] = dTotUseByMo[iMo];      // keep track of both initial & carryover monthly energy - SAC 09/28/23
               }
            }

            if (iFuel == 0)  // Electric processing
            {  double dCarryOver=0.0;
               int iBillMo, iFirstBillMo = ((lPVCarryoverOption==0 || lPVCarryoverOption==12) ? 0 : lPVCarryoverOption);
               if (lPVBillingOption > 0)     // special processing for Elec use - carryover negative (due to PV) monthly use - SAC 12/10/22
               {  int iNumLoops = (lPVCarryoverOption==0 ? 2 : 1);
                  for (int iLp=0; iLp<iNumLoops; iLp++)
                     for (iMo=0; iMo<12; iMo++)
                     {
                        iBillMo = iMo+iFirstBillMo;
                        if (iBillMo > 11)
                           iBillMo -= 12;

                        if (dTotUseByMo[iBillMo] < 0)
                        {  // add to carryover
                           dCarryOver -= dTotUseByMo[iBillMo];
                           dTotUseByMo[iBillMo] = 0.0;
                        }
                        else if (dTotUseByMo[iBillMo] > 0 && dCarryOver > 0)
                        {  if (dTotUseByMo[iBillMo] > dCarryOver)
                           {  // reduce month's use partly by carryover
                              dTotUseByMo[iBillMo] -= dCarryOver;
                              dCarryOver = 0.0;
                           }
                           else
                           {  // carryover covers all of this month's use
                              dCarryOver -= dTotUseByMo[iBillMo];
                              dTotUseByMo[iBillMo] = 0.0;
                        }  }
               }     }

               long lDBID_BillingElecUse = BEMPX_GetDatabaseID( "CUACResults:BillingElecUse" );       assert( lDBID_BillingElecUse > 0 );
               if (lDBID_BillingElecUse > 0)
               {  double dAnnUse = 0.0;
                  for (iMo=0; iMo<12; iMo++)          // store BillingElecUse
                  {  dAnnUse += dTotUseByMo[iMo];
                     BEMPX_SetBEMData( lDBID_BillingElecUse+iMo, BEMP_Flt, (void*) &dTotUseByMo[iMo], BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                  }
                  BEMPX_SetBEMData( lDBID_BillingElecUse+12, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual
                  dAnnUse /= 365.0;
                  BEMPX_SetBEMData( lDBID_BillingElecUse+13, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // daily
               }

               long lDBID_CommunitySolarAnnCreditByBedrms = BEMPX_GetDatabaseID( "CUAC:CommunitySolarAnnCreditByBedrms" );       assert( lDBID_CommunitySolarAnnCreditByBedrms > 0 );  // SAC 10/03/23
               if (lDBID_CommunitySolarAnnCreditByBedrms > 0)
               {  dCommunitySolarAnnCredit = BEMPX_GetFloat( lDBID_CommunitySolarAnnCreditByBedrms+iMtr, iSpecVal, iErr, 
                                                               0 /*ObjIdx*/, BEMO_User, iCUAC_BEMProcIdx, false, 0.0 );
                                                      if (iBillCalcDetails > 0 && dCommunitySolarAnnCredit > 0.0)
                                                         BEMPX_WriteLogFile( QString( "   %1 community solar annual elec bill credit: $%2" ).arg( pszCUACCSVUnitTypeLabels[iMtr], QString::number( dCommunitySolarAnnCredit ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
            }

            bool bIgnoreNetExcesCredits=false, bIgnoreHourlyTOU=false;
            long lElecBillReconBeginMo=1, lElecTariffAdj=0;
            double dElecBillMinMoCharge=-999.0, dElecBillMinAnnCharge=-999.0;
            if (iFuel == 0)  // Electric processing
            {
               lElecBillReconBeginMo = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:ElecBillReconBeginMo" ), iSpecVal, iErr, 0 /*ObjIdx*/, BEMO_User, iCUAC_BEMProcIdx );      // SAC 12/10/23 (CUAC)
               BEMPX_GetInteger( BEMPX_GetDatabaseID( "ElecTariffAdj", iCID_CUAC ), lElecTariffAdj, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );       // SAC 12/13/23
               if (lElecTariffAdj == 2)   // hardwiring VNEM2 - SAC 12/13/23
               {  bIgnoreNetExcesCredits = true;
                  bIgnoreHourlyTOU       = true;
                  QString qsElecTariffAdj;
                  BEMPX_GetString( BEMPX_GetDatabaseID( "ElecTariffAdj", iCID_CUAC ), qsElecTariffAdj, FALSE, 0, -1, 0, BEMO_User, "??", 0, iCUAC_BEMProcIdx ); 
                  BEMPX_WriteLogFile( QString( "  applying user-specified utility bill adjustment '%1' to utility bill calc" ).arg( qsElecTariffAdj ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
               BEMPX_GetFloat( BEMPX_GetDatabaseID( "ElecBillMinMoCharge" , iCID_CUAC ), dElecBillMinMoCharge , -999.0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );    // SAC 12/14/23
               BEMPX_GetFloat( BEMPX_GetDatabaseID( "ElecBillMinAnnCharge", iCID_CUAC ), dElecBillMinAnnCharge, -999.0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ); 
            }

            // Calculate utility bills
            QString sFuelCostPropName = (iFuel==0 ? "CUACResults:ElecCosts" : "CUACResults:GasCosts");
            long lDBID_FuelCostResult = BEMPX_GetDatabaseID( sFuelCostPropName );         assert( lDBID_FuelCostResult > 0 );
            if (lDBID_FuelCostResult > 0)
            {  if (dTotAnnUse > 0.1 && iG2RateObjIdx[iFuel] < 0 && !utilRate[iFuel].bOK)
               {  // post error if energy use present but no rate assigned
                  sErrMsg = QString( "CUAC %1 Utility bill calc error:  energy use present but no rate assigned or rate data invalid" ).arg( saFuelLabels[iFuel] );
               }
               else if (iG2RateObjIdx[iFuel] >= 0)
               {  // ---------------------------------------------------------
                  // ---  Calculate utility bill based on 2023+ CPR rates  ---
                  // ---------------------------------------------------------
                  QString qsEncodedRateName       = BEMPX_GetString( BEMPX_GetDatabaseID( "EncodedRateName"      , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  QString qsMeteringType          = BEMPX_GetString( BEMPX_GetDatabaseID( "MeteringType"         , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  QString qsReconciliationPeriod  = BEMPX_GetString( BEMPX_GetDatabaseID( "ReconciliationPeriod" , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  QString qsNettingPeriodInterval = BEMPX_GetString( BEMPX_GetDatabaseID( "NettingPeriodInterval", iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  QString qsDemandInterval        = BEMPX_GetString( BEMPX_GetDatabaseID( "DemandInterval"       , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  long lAnnualBilling     = BEMPX_GetInteger( BEMPX_GetDatabaseID( "AnnualBilling"    , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  long lNumRateSeasons    = BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumRateSeasons"   , iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                  long lNumHourlyTOUCosts = BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumHourlyTOUCosts", iCID_UtilityRate ), iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );

                  bool bFullRetailReimbForExports = false;
                  if ( (iFuel == 0 && lElecTariffAdj == 2) ||                                      // SAC 12/13/23
                       !qsMeteringType.compare( "NetMetering",         Qt::CaseInsensitive ) ||    // SAC 12/04/23
                       !qsMeteringType.compare( "OptionalNetMetering", Qt::CaseInsensitive ) )
                     bFullRetailReimbForExports = true;

                  double dFinalNetSurplusCompPrice = 0.0;
                  //if (lNumHourlyTOUCosts > 0)
                  //   sErrMsg = QString( "CUAC %1 Utility bill calc error:  not yet compatible with rates described by HourlyTOUCosts" ).arg( saFuelLabels[iFuel] );
                  //else if (lNumRateSeasons < 1)
                  if (lNumRateSeasons < 1)
                     sErrMsg = QString( "CUAC %1 Utility bill calc error:  rate must include at least one RateSeason" ).arg( saFuelLabels[iFuel] );

                  if (!sErrMsg.isEmpty())
                     BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {  // store 8760 energy use for this fuel & meter for use in Gen2 utility bill calcs
                     double daHrlyTotUse[8760], daHrlyExports[8760], dHrlyUseTot=0.0, dHrlyExpTot=0.0;
                     double dCarryOverDollars=0.0, dCarryOverKWH=0.0, dMonthlyNetSurpKWH[12];      // SAC 12/04/23
                     for (iHr=0; iHr<8760; iHr++)
                     {  daHrlyTotUse[ iHr] = 0.0;
                        daHrlyExports[iHr] = 0.0;
                     }
                     if (!bOldCUAC)
                     {  // HOURLY simulation results
                        for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
                        {  int iInitMtrIdx                  = (iDataModel == 0 ? iaInitToRptsEnduseMap[iCEUIdx]     : iaResInitToRptsEnduseMap[iCEUIdx]     );
                           const char* pszHrlyResultsEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iInitMtrIdx] : pszInitialCUACResEnduses[iInitMtrIdx] );
                           double dCEUAnnTot = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                           if ( (iCEUIdx==11 && dCEUAnnTot > -0.01) || (iCEUIdx!=11 && dCEUAnnTot < 0.01) )
                           {  // skip
                           }
                           else
                           {  double *pdHrlyUse=NULL;
                              BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse, NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, iCUAC_BEMProcIdx );
                              for (iMo=0; (pdHrlyUse && iMo<12); iMo++)
                                 for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                                    daHrlyTotUse[iHr] += pdHrlyUse[iHr];
                        }  }
                        for (iMo=0; iMo<12; iMo++)    // SAC 12/04/23
                        {  double dMoUse=0.0;
                           for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                              dMoUse += daHrlyTotUse[iHr];           // fixed bug?  '=' -> '+=' - SAC 01/12/25
                           dMonthlyNetSurpKWH[iMo] = (dMoUse < 0.0 ? (dMoUse * -1.0) : 0.0);
                        }
                        for (iHr=0; iHr<8760; iHr++)
                        {  if (daHrlyTotUse[ iHr] < 0)
                           {  daHrlyExports[iHr] = daHrlyTotUse[iHr];
                              daHrlyTotUse[ iHr] = 0.0;
                           }
                           dHrlyUseTot += daHrlyTotUse[iHr];    dHrlyExpTot += daHrlyExports[iHr];
                        }
                     }
                     else
                     {  // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                        for (iMo=0; iMo<12; iMo++)
                        {  if (dTotUseByMo[iMo] >= 0.0)
                           {  dMonthlyNetSurpKWH[iMo] = 0.0;
                              dHrlyUseTot +=  dTotUseByMo[iMo];
                           }
                           else
                           {  dMonthlyNetSurpKWH[iMo] = (dTotUseByMo[iMo] * -1.0);
                              dHrlyExpTot += dMonthlyNetSurpKWH[iMo];
                     }  }  }
                     int iNumMosNetSurplus = 0;    // SAC 12/04/23
                     for (iMo=0; iMo<12; iMo++)
                        iNumMosNetSurplus += (dMonthlyNetSurpKWH[iMo] > 0.001);
                                                      if (iBillCalcDetails > 0)
                                                      {  if (dHrlyExpTot > -0.01 && dHrlyExpTot < 0.01)
                                                                  BEMPX_WriteLogFile(    QString( "   %1 annual %2 use: %3 %4"               ).arg( pszCUACCSVUnitTypeLabels[iMtr], saFuelLabels[iFuel], QString::number( dHrlyUseTot ), saFuelUnitLabels[iFuel] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         else  {  BEMPX_WriteLogFile(    QString( "   %1 annual %2 use: %3 %4   exports: %5" ).arg( pszCUACCSVUnitTypeLabels[iMtr], saFuelLabels[iFuel], QString::number( dHrlyUseTot ), saFuelUnitLabels[iFuel], QString::number( dHrlyExpTot ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                                  if (iNumMosNetSurplus > 0)
                                                                     BEMPX_WriteLogFile( QString( "            %1 net surplus months:  Jan %2, Feb %3, Mar %4, Apr %5, May %6, Jun %7, Jul %8, Aug %9, Sep %10, Oct %11, Nov %12, Dec %13" ).arg( QString::number( iNumMosNetSurplus ), QString::number( dMonthlyNetSurpKWH[0] ), QString::number( dMonthlyNetSurpKWH[1] ), QString::number( dMonthlyNetSurpKWH[2] ), QString::number( dMonthlyNetSurpKWH[3] ),
                                                                                                                        QString::number( dMonthlyNetSurpKWH[4] ), QString::number( dMonthlyNetSurpKWH[5] ), QString::number( dMonthlyNetSurpKWH[6] ), QString::number( dMonthlyNetSurpKWH[7] ), QString::number( dMonthlyNetSurpKWH[8] ), QString::number( dMonthlyNetSurpKWH[9] ), QString::number( dMonthlyNetSurpKWH[10] ), QString::number( dMonthlyNetSurpKWH[11] ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                               }
                                                         BEMPX_WriteLogFile(             QString( "      Gen2 %1 '%2' utility bill calc -" ).arg( saFuelLabels[iFuel], qsEncodedRateName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      }
                     double dAnnCost = 0.0;

                     int iNumMoGrps = ((iFuel==0 && lElecBillReconBeginMo > 1) ? 2 : 1);     // enable 2 rounds of month groups to calc bills based on reconciliation period - SAC 12/10/23
                     int iMoGrpStrt[] = { (iNumMoGrps == 1 ?  0 : lElecBillReconBeginMo-1), (iNumMoGrps == 1 ? -1 : 0) };
                     int iMoGrpEnd[]  = { 11, (iNumMoGrps == 1 ? -1 : lElecBillReconBeginMo-2) };
                     for (int iMoGrp=0; (iMoGrp<iNumMoGrps && sErrMsg.isEmpty()); iMoGrp++)
                     for (iMo=iMoGrpStrt[iMoGrp]; (iMo<=iMoGrpEnd[iMoGrp] && sErrMsg.isEmpty()); iMo++)
                     //for (iMo=0; (iMo<12 && sErrMsg.isEmpty()); iMo++)
                     {  double dMonBypassableCost = 0.0, dMonNonBypassableCost = 0.0, dMonMinCost = 0.0;
                        for (int iSeas=0; (iSeas < lNumRateSeasons && sErrMsg.isEmpty()); iSeas++)
                        {  BEMObject* pSeasObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "RateSeasons", iCID_UtilityRate )+iSeas, iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                           int iSeasObjIdx     = (pSeasObj == NULL ? -1 : BEMPX_GetObjectIndex( pSeasObj->getClass(), pSeasObj, iCUAC_BEMProcIdx ));
                           if (iSeasObjIdx < 0)
                              sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve RateSeasons #%2" ).arg( saFuelLabels[iFuel], QString::number( iSeas+1 ) );
                           else
                           {  QString qsSeasName     = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_RateSeason:Name"             ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              QString qsSeasJSONName = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_RateSeason:SeasonName"       ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              long lNumSeasonPeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_RateSeason:NumSeasonPeriods" ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                              int iSeasMoHrStart=-1, iSeasMoHrEnd=-1;
                              for (int iSeasPer=0; (iSeasPer < lNumSeasonPeriods && sErrMsg.isEmpty() && (iSeasMoHrStart < 0 || iSeasMoHrEnd < 0)); iSeasPer++)
                              {  BEMObject* pSeasPerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_RateSeason:SeasonPeriods" )+iSeasPer, iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                 int iSeasPerObjIdx     = (pSeasPerObj == NULL ? -1 : BEMPX_GetObjectIndex( pSeasPerObj->getClass(), pSeasPerObj, iCUAC_BEMProcIdx ));
                                 if (iSeasPerObjIdx < 0)
                                    sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve SeasonTimePeriod #%2 for RateSeasons #%3" ).arg( saFuelLabels[iFuel], QString::number( iSeasPer+1 ), QString::number( iSeas+1 ) );
                                 else
                                    G2MonthSeasonPeriodOverlap( iSeasPerObjIdx, iMo+1, iMoHrStart[iMo], iMoHrEnd[iMo], iSeasMoHrStart, iSeasMoHrEnd, iCUAC_BEMProcIdx, sErrMsg );
                              }
                              if (sErrMsg.isEmpty() && iSeasMoHrStart >= 0 && iSeasMoHrEnd > 0)
                              {                       if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "            %1 - Seas #%2, %3 / %4, yr hrs %5-%6:" ).arg( pszMoLabels[iMo], QString::number( iSeas+1 ), qsSeasName, qsSeasJSONName, QString::number( iSeasMoHrStart ), QString::number( iSeasMoHrEnd ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         //BEMPX_WriteLogFile( QString( "            Seas #%1, %2 / %3 - month %4, yr hrs %5-%6:" ).arg( QString::number( iSeas+1 ), qsSeasName, qsSeasJSONName, QString::number( iMo+1 ), QString::number( iSeasMoHrStart ), QString::number( iSeasMoHrEnd ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

                                 long lNumTOUPeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_RateSeason:NumTimeOfUsePeriods" ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                 for (int iTOUPer=0; (iTOUPer < lNumTOUPeriods && sErrMsg.isEmpty()); iTOUPer++)
                                 {  BEMObject* pTOUPerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_RateSeason:TimeOfUsePeriods" )+iTOUPer, iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    int iTOUPerObjIdx     = (pTOUPerObj == NULL ? -1 : BEMPX_GetObjectIndex( pTOUPerObj->getClass(), pTOUPerObj, iCUAC_BEMProcIdx ));
                                    if (iTOUPerObjIdx < 0)
                                       sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve TOUPeriod #%2 for RateSeasons #%3" ).arg( saFuelLabels[iFuel], QString::number( iTOUPer+1 ), QString::number( iSeas+1 ) );
                                    else
                                    {                 if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "               TOUPeriod #%1, %2 / %3:" ).arg( QString::number( iTOUPerObjIdx+1 ), 
                                                                                                            BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:Name"    ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ),
                                                                                                            BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TOUName" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       long lNumDailyTimePeriods = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_TOUPeriod:NumTimePeriods" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       BEMObject* pCostCompObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_TOUPeriod:CostComponents" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       int iCostCompObjIdx     = (pCostCompObj == NULL ? -1 : BEMPX_GetObjectIndex( pCostCompObj->getClass(), pCostCompObj, iCUAC_BEMProcIdx ));
                                       if (iCostCompObjIdx < 0)
                                          sErrMsg = QString( "CUAC %1 Utility bill calc error:  CostComponents not defined for TOUPeriod #%2 %3, RateSeasons #%4" ).arg( saFuelLabels[iFuel], QString::number( iTOUPer+1 ), 
                                                               BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TOUName" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx ), QString::number( iSeas+1 ) );
                                       else
                                       {  // Days:   0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                                          double dDayHrMult[7][24] = { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };
                                          int iNumTimePeriodHrsInWk = 0;      // SAC 09/18/23
                                          for (int iDailyTimePer=0; (iDailyTimePer < lNumDailyTimePeriods && sErrMsg.isEmpty()); iDailyTimePer++)
                                          {  BEMObject* pDailyTimePerObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_TOUPeriod:TimePeriods" )+iDailyTimePer, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             int iDailyTimePerObjIdx     = (pDailyTimePerObj == NULL ? -1 : BEMPX_GetObjectIndex( pDailyTimePerObj->getClass(), pDailyTimePerObj, iCUAC_BEMProcIdx ));
                                             if (iDailyTimePerObjIdx < 0)
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve DailyTimePeriod #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iDailyTimePer+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                             else
                                             {  int iCID_DailyTimePeriod = BEMPX_GetDBComponentID( "CPR_DailyTimePeriod" );
                                                double dStartTime    = BEMPX_GetFloat(  BEMPX_GetDatabaseID( "StartTime",      iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                double dEndTime      = BEMPX_GetFloat(  BEMPX_GetDatabaseID( "EndTime",        iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                QString sWhichDays   = BEMPX_GetString( BEMPX_GetDatabaseID( "ApplicableDays", iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                // mods to accommodate valid scenario where dEndTime < dStartTime - meaning period turns corner over midnight - SAC 12/04/23
                                                if (dStartTime < 0 || dEndTime < 0 || dEndTime == dStartTime /*|| dEndTime < dStartTime*/ || sWhichDays.isEmpty())
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  invalid data describing DailyTimePeriod #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iDailyTimePer+1 ), QString::number( iDailyTimePerObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else
                                                {  QString sDTPName  = BEMPX_GetString( BEMPX_GetDatabaseID( "Name",           iCID_DailyTimePeriod ), iSpecVal, iErr, iDailyTimePerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                               if (iBillCalcDetails > 0)
                                                                  BEMPX_WriteLogFile( QString( "                  DlyTimePeriod #%1, %2 - days: %3, hrs %4-%5:" ).arg( QString::number( iDailyTimePer+1 ), sDTPName, sWhichDays, QString::number( dStartTime ), QString::number( dEndTime ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                   double dStartTm[] = {  dStartTime                              , (dStartTime < dEndTime ? 100.0 : 0.0) };      // SAC 12/04/23
                                                   double dEndTm[]   = { (dStartTime < dEndTime ? dEndTime : 24.0),  dEndTime   };
                                                   // intialize dDayHrMult[][] arrays to keep track of days & hours this TOU period enforced
                                                   for (iDay=0; iDay < 7; iDay++)                                 //0, CPR_DailyTimePeriod:ApplicableDays,   -1
                                                      if (  !sWhichDays.compare( "All"      ) ||                  //2,              1,    "All" 
                                                           (!sWhichDays.compare( "Weekdays" ) && iDay < 5) ||     //2,              0,    "Weekdays" 
                                                           (!sWhichDays.compare( "Weekends" ) && iDay > 4) )      //2,              2,    "Weekends" 
                                                         for (iHr=0; iHr < 24; iHr++)
                                                         {  if ( (iHr >= (dStartTm[0]-0.1) && iHr < (dEndTm[0]-0.1)) ||
                                                                 (iHr >= (dStartTm[1]-0.1) && iHr < (dEndTm[1]-0.1)) )
                                                            {  dDayHrMult[iDay][iHr] = 1.0;
                                                               iNumTimePeriodHrsInWk++;
                                                         }  }
                                          }  }  }
                                                                     assert( (!bOldCUAC || iNumTimePeriodHrsInWk == 0 || iNumTimePeriodHrsInWk == 168) );      // if OldCUAC, TOU period should cover ALL or NONE of the week - SAC 09/18/23
                                          // CPR_TOUPeriod TimePeriods loaded - now move on to CostComponent
                                          // sum use and find peak demand during month within TOU period
                                          double dMoTOUUse = 0.0, dMoTOUPeakDem = 0.0, dMonBypassableTOUCost = 0.0, dMonNonBypassableTOUCost = 0.0, dMoTOUDailyUse[31];    int iHrInDay;
                                          for (iDay=0; iDay<31; iDay++)
                                             dMoTOUDailyUse[iDay] = 0.0;
                                          if (!bOldCUAC)
                                          {  // HOURLY simulation results
                                             for (iHr = iSeasMoHrStart; iHr <= iSeasMoHrEnd; iHr++)
                                             {  i0YrDay  = (int) (iHr/24);
                                                iHrInDay = iHr - (i0YrDay*24);
                                                iDay = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDay>=0 && iDay<7) );
                                                if (dDayHrMult[iDay][iHrInDay] > 0.1)
                                                {  int iMoTOUDayIdx = i0YrDay - ((int) (iSeasMoHrStart/24));               assert( iMoTOUDayIdx >= 0 && iMoTOUDayIdx < 31 );     // debugging - SAC 09/26/23
                                                   dMoTOUDailyUse[iMoTOUDayIdx] += (daHrlyTotUse[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                   dMoTOUUse                    += (daHrlyTotUse[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                   if (bFullRetailReimbForExports && daHrlyExports[iHr] < 0)      // SAC 12/04/23
                                                   {  dMoTOUDailyUse[iMoTOUDayIdx] += (daHrlyExports[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                      dMoTOUUse                    += (daHrlyExports[iHr] * dDayHrMult[iDay][iHrInDay]);
                                                   }
                                                   if (daHrlyTotUse[iHr] > dMoTOUPeakDem)
                                                      dMoTOUPeakDem = daHrlyTotUse[iHr];
                                             }  }
                                          }
                                          else
                                          {  // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                                             double dDaysInSeasMo = (iSeasMoHrEnd - iSeasMoHrStart - 2) / 24.0;            assert( dDaysInSeasMo > 0 && dDaysInSeasMo <= 31.0 );
                                             dMoTOUUse = (bFullRetailReimbForExports ? dTotUseByMo[iMo] : std::max( dTotUseByMo[iMo], 0.0 ));     // add max() to prevent negative energy charges - SAC 09/21/23  // bFullRetailReimbForExports - SAC 12/04/23
                                             for (iDay=0; iDay<dDaysInSeasMo; iDay++)
                                                dMoTOUDailyUse[iDay] = dMoTOUUse / dDaysInSeasMo;
                                          }
                                                      if (iBillCalcDetails > 0)
                                                      {  QString sMoTOUDailyUse = QString( "%1" ).arg( QString::number( dMoTOUDailyUse[0] ) );
                                                         for (iDay=1; iDay<iNumDaysInMonth[iMo]; iDay++)
                                                            sMoTOUDailyUse += QString( ", %1" ).arg( QString::number( dMoTOUDailyUse[iDay] ) );
                                                         BEMPX_WriteLogFile( QString( "                  TOUPeriod Energy: %1  Demand: %2  DailyEnergy: %3" ).arg( QString::number( dMoTOUUse ), QString::number( dMoTOUPeakDem ), sMoTOUDailyUse ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      }

                                          // CPR_PeriodCost:DemandCosts
                                          long lNumDemandCosts   = BEMPX_GetInteger(   BEMPX_GetDatabaseID( "CPR_PeriodCost:NumDemandCosts" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          int iCostIdx, iTierIdx;
                                          for (iCostIdx = 0; (iCostIdx < lNumDemandCosts && sErrMsg.isEmpty()); iCostIdx++)
                                          {  BEMObject* pDemCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_PeriodCost:DemandCosts" )+iCostIdx, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             int iDemCostObjIdx     = (pDemCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pDemCostObj->getClass(), pDemCostObj, iCUAC_BEMProcIdx ));
                                             if (iDemCostObjIdx < 0)
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve DemandCost #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                             else
                                             {  QString sCostName             = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_DemandCost:CostName"             ), iSpecVal, iErr, iDemCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                QString sDemandChargeStrategy = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_DemandCost:DemandChargeStrategy" ), iSpecVal, iErr, iDemCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                long lNonBypassable           = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_DemandCost:NonBypassable"        ), iSpecVal, iErr, iDemCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );  // SAC 09/11/23
                                                long lNumTiers                = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_DemandCost:NumTiers"             ), iSpecVal, iErr, iDemCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                if (sDemandChargeStrategy.compare("BillingPeriodMaximum"))
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  DemandCost DemandChargeStrategy '%2' not currently supported - DemandCost #%3 (occur %4) (RateSeasons #%5, TOUPeriod #%6)" ).arg( 
                                                                                 saFuelLabels[iFuel], sDemandChargeStrategy, QString::number( iCostIdx+1 ), QString::number( iDemCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                                        // 0, CPR_DemandCost:DemandChargeStrategy,  -1
                                                                        // 2,              0,    "BillingPeriodMaximum" 
                                                                        // 2,              1,    "SumOfDailyMaximum" 
                                                                        // 2,              2,    "AverageOfDailyMaximum" 
                                                else if (lNumTiers > 0)
                                                {  double dThisMoTOUPeakDem = dMoTOUPeakDem;
                                                   double dThisCost = 0.0;
                                                   for (iTierIdx = 0; (iTierIdx < lNumTiers && sErrMsg.isEmpty()); iTierIdx++)
                                                   {  BEMObject* pTierObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_DemandCost:Tiers" )+iTierIdx, iSpecVal, iErr, iDemCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      int iTierObjIdx     = (pTierObj == NULL ? -1 : BEMPX_GetObjectIndex( pTierObj->getClass(), pTierObj, iCUAC_BEMProcIdx ));
                                                      if (iTierObjIdx < 0)
                                                         sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve Tier #%2 for RateSeasons #%3, TOUPeriod #%4, DemandCosts #%5" ).arg( saFuelLabels[iFuel], QString::number( iTierIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ) );
                                                      else
                                                      {  long lTierNumber  = BEMPX_GetInteger( lDBID_Tier_TierNumber, iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dPrice     = BEMPX_GetFloat(   lDBID_Tier_Price,      iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dQuantity  = BEMPX_GetFloat(   lDBID_Tier_Quantity,   iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dThisTierCost = 0.0;
                                                         if (!sDemandChargeStrategy.compare("BillingPeriodMaximum"))
                                                         {  if (dQuantity > 0)
                                                            {  dThisTierCost     += (std::min( dThisMoTOUPeakDem, dQuantity ) * dPrice);
                                                               dThisMoTOUPeakDem -=  std::min( dThisMoTOUPeakDem, dQuantity );
                                                            }
                                                            else 
                                                            {  dThisTierCost    += (dThisMoTOUPeakDem * dPrice);
                                                               dThisMoTOUPeakDem = 0.0;
                                                         }  }
                                                         else
                                                            sErrMsg = QString( "CUAC %1 Utility bill calc error:  unrecognized DemandChargeStrategy '%2' for RateSeasons #%3, TOUPeriod #%4, DemandCosts #%5, Tier #%6" ).arg( 
                                                                                 saFuelLabels[iFuel], sDemandChargeStrategy, QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ), QString::number( iTierIdx+1 ) );

                                                               if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                  BEMPX_WriteLogFile( QString( "                           Tier #%1 cost: %2" ).arg( QString::number( iTierIdx+1 ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         dThisCost += dThisTierCost;
                                                   }  }
                                                   if (lNonBypassable)
                                                   {  dMonNonBypassableTOUCost += dThisCost;
                                                      dMonNonBypassableCost += dThisCost;
                                                   }
                                                   else
                                                   {  dMonBypassableTOUCost += dThisCost;
                                                      dMonBypassableCost += dThisCost;
                                                   }
                                                               if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                  BEMPX_WriteLogFile( QString( "                     DemandCost #%1 total cost: %2  (cumulative TOU cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( iCostIdx+1 ), QString::number( dThisCost ), QString::number( dMonBypassableTOUCost ), QString::number( dMonNonBypassableTOUCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                }
                                          }  }

                                          // CPR_PeriodCost:EnergyCosts
                                          long lNumEnergyCosts   = BEMPX_GetInteger(   BEMPX_GetDatabaseID( "CPR_PeriodCost:NumEnergyCosts" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          for (iCostIdx = 0; (iCostIdx < lNumEnergyCosts && sErrMsg.isEmpty()); iCostIdx++)
                                          {  BEMObject* pEnergyCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_PeriodCost:EnergyCosts" )+iCostIdx, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             int iEnergyCostObjIdx     = (pEnergyCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pEnergyCostObj->getClass(), pEnergyCostObj, iCUAC_BEMProcIdx ));
                                             if (iEnergyCostObjIdx < 0)
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve EnergyCost #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                             else
                                             {  QString sPeriodType    = BEMPX_GetString(  lDBID_EnergyCost_PeriodType,       iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                long lNumTiers         = BEMPX_GetInteger( lDBID_EnergyCost_NumTiers,         iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                long lTotalConsumption = BEMPX_GetInteger( lDBID_EnergyCost_TotalConsumption, iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                long lNonBypassable    = BEMPX_GetInteger( lDBID_EnergyCost_NonBypassable,    iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );    // SAC 09/11/23
                                                         //  "CostName",                 BEMP_Str,  1,  0,  0,  Pres,  "",                 0,  0,                                 1005, "Name of the cost component",    "Name" 
                                                         //  "Delivery",                 BEMP_Int,  1,  0,  0,  Pres,  "",                 0,  0,                                 1005, "Boolean indicating if this is a delivery charge or not",  "" 
                                                if (lNumTiers < 1 || sPeriodType.isEmpty())
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  invalid data describing EnergyCosts #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iEnergyCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else if (lTotalConsumption > 0)
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  TotalConsumption not yet implemented for EnergyCosts #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iEnergyCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else
                                                {  double dThisMoTOUUse = dMoTOUUse;
                                                   double dThisMoTOUDailyUse[31];
                                                   if (!sPeriodType.compare("PerDayBilled"))
                                                   {  for (iDay=0; iDay<31; iDay++)
                                                         dThisMoTOUDailyUse[iDay] = dMoTOUDailyUse[iDay];
                                                   }
                                                   double dThisCost = 0.0;
                                                   for (iTierIdx = 0; (iTierIdx < lNumTiers && sErrMsg.isEmpty()); iTierIdx++)
                                                   {  BEMObject* pTierObj = BEMPX_GetObjectPtr( lDBID_EnergyCost_Tiers+iTierIdx, iSpecVal, iErr, iEnergyCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      int iTierObjIdx     = (pTierObj == NULL ? -1 : BEMPX_GetObjectIndex( pTierObj->getClass(), pTierObj, iCUAC_BEMProcIdx ));
                                                      if (iTierObjIdx < 0)
                                                         sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve Tier #%2 for RateSeasons #%3, TOUPeriod #%4, EnergyCosts #%5" ).arg( saFuelLabels[iFuel], QString::number( iTierIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ) );
                                                      else
                                                      {  long lTierNumber  = BEMPX_GetInteger( lDBID_Tier_TierNumber, iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dPrice     = BEMPX_GetFloat(   lDBID_Tier_Price,      iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dQuantity  = BEMPX_GetFloat(   lDBID_Tier_Quantity,   iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                         double dThisTierCost = 0.0;
                                                         if (!sPeriodType.compare("PerDayBilled"))
                                                         {  for (iDay=0; iDay<31; iDay++)
                                                            {  double dDayQuantity = 0.0;
                                                               if (dThisMoTOUDailyUse[iDay] > 0)
                                                                  dDayQuantity = (dQuantity > 0 ? std::min( dThisMoTOUDailyUse[iDay], dQuantity ) : dThisMoTOUDailyUse[iDay]);
                                                               else if (dThisMoTOUDailyUse[iDay] < 0 && bFullRetailReimbForExports && dPrice > 0 && lNonBypassable == 0)     // for exports, only apply charge if price > 0 - SAC 12/04/23
                                                                  dDayQuantity = (dQuantity > 0 ? std::max( dThisMoTOUDailyUse[iDay], (-1.0 * dQuantity) ) : dThisMoTOUDailyUse[iDay]);
                                                               if (dDayQuantity != 0.0)
                                                               {  dThisTierCost += (dDayQuantity * dPrice);
                                                                  dThisMoTOUDailyUse[iDay] -= dDayQuantity;
                                                                     if (iBillCalcDetails > 1 && sErrMsg.isEmpty())
                                                                        BEMPX_WriteLogFile( QString( "                           Tier #%1, day %2: %3 @ price %4 = %5" ).arg( QString::number( iTierIdx+1 ), QString::number( iDay+1 ), QString::number( dDayQuantity ), QString::number( dPrice ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                               }
                                                               //if (dQuantity > 0)
                                                               //{  dThisTierCost += (std::min( dThisMoTOUDailyUse[iDay], dQuantity ) * dPrice);
                                                               //   dThisMoTOUDailyUse[iDay] -= std::min( dThisMoTOUDailyUse[iDay], dQuantity );
                                                               //}
                                                               //else 
                                                               //{  dThisTierCost += (dThisMoTOUDailyUse[iDay] * dPrice);
                                                               //   dThisMoTOUDailyUse[iDay] = 0.0;
                                                            }  //}
                                                         }
                                                         else if (!sPeriodType.compare("PerBillingCycle"))
                                                         {  dQuantity = 0.0;
                                                            if (dThisMoTOUUse < 0 && bFullRetailReimbForExports && dPrice > 0 && lNonBypassable == 0)      // for exports, only apply charge if price > 0 - SAC 12/04/23
                                                               dQuantity = (dQuantity > 0 ? std::max( dThisMoTOUUse, (-1.0 * dQuantity) ) : dThisMoTOUUse);
                                                            else if (dThisMoTOUUse > 0)
                                                               dQuantity = (dQuantity > 0 ? std::min( dThisMoTOUUse, dQuantity ) : dThisMoTOUUse);
                                                            dThisTierCost += (dQuantity * dPrice);
                                                            dThisMoTOUUse -=  dQuantity;
                                                                     if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                        BEMPX_WriteLogFile( QString( "                           Tier #%1: %2 @ price %3 = %4" ).arg( QString::number( iTierIdx+1 ), QString::number( dQuantity ), QString::number( dPrice ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                            //if (dQuantity > 0)
                                                            //{  dThisTierCost += (std::min( dThisMoTOUUse, dQuantity ) * dPrice);
                                                            //   dThisMoTOUUse -=  std::min( dThisMoTOUUse, dQuantity );
                                                            //}
                                                            //else
                                                            //{  dThisTierCost += (dThisMoTOUUse * dPrice);
                                                            //   dThisMoTOUUse = 0.0;
                                                         }  //}
                                                         else
                                                            sErrMsg = QString( "CUAC %1 Utility bill calc error:  unrecognized PeriodType '%2' for RateSeasons #%3, TOUPeriod #%4, EnergyCosts #%5, Tier #%6" ).arg( 
                                                                                 saFuelLabels[iFuel], sPeriodType, QString::number( iSeas+1 ), QString::number( iTOUPer+1 ), QString::number( iCostIdx+1 ), QString::number( iTierIdx+1 ) );

                                                               //if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                               //   BEMPX_WriteLogFile( QString( "                           Tier #%1 cost: %2" ).arg( QString::number( iTierIdx+1 ), QString::number( dThisTierCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         dThisCost += dThisTierCost;
                                                   }  }
                                                   if (lNonBypassable && dThisCost > 0)
                                                   {  dMonNonBypassableTOUCost += dThisCost;
                                                      dMonNonBypassableCost += dThisCost;
                                                   }
                                                   else
                                                   {  dMonBypassableTOUCost += dThisCost;
                                                      dMonBypassableCost += dThisCost;
                                                   }
                                                               if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                  BEMPX_WriteLogFile( QString( "                     EnergyCost #%1 total cost: %2  (cumulative TOU cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( iCostIdx+1 ), QString::number( dThisCost ), QString::number( dMonBypassableTOUCost ), QString::number( dMonNonBypassableTOUCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

                                          }  }  }

                                          // CPR_PeriodCost:NetExcessCreditCosts
                                          long lNumNetExcessCreditCosts   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_PeriodCost:NumNetExcessCreditCosts" ), iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          if (lNumNetExcessCreditCosts > 0 && bIgnoreNetExcesCredits)
                                                   BEMPX_WriteLogFile( QString( "   NetExcessCreditCosts (%1 found) being ignored due to user rate adjustment inputs" ).arg( QString::number( lNumNetExcessCreditCosts ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          else
                                          for (iCostIdx = 0; (iCostIdx < lNumNetExcessCreditCosts && sErrMsg.isEmpty()); iCostIdx++)
                                          {  assert( !bFullRetailReimbForExports );    // SAC 12/04/23
                                                if (bFullRetailReimbForExports)
                                                   BEMPX_WriteLogFile( QString( "   utility bill calc issue (?):  NetExcessCreditCosts not applicable for NetMetering rates" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                             BEMObject* pNetExcsCredCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_PeriodCost:NetExcessCreditCosts" )+iCostIdx, iSpecVal, iErr, iTOUPerObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             int iNetExcsCredCostObjIdx     = (pNetExcsCredCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pNetExcsCredCostObj->getClass(), pNetExcsCredCostObj, iCUAC_BEMProcIdx ));
                                             if (iNetExcsCredCostObjIdx < 0)
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve NetExcessCreditCost #%2 for RateSeasons #%3, TOUPeriod #%4" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                             else
                                             {  QString sCostName   = BEMPX_GetString(  lDBID_NetExcessCreditCost_CostName,       iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                QString sPeriodType = BEMPX_GetString(  lDBID_NetExcessCreditCost_CostPeriodType, iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                long lNumTiers      = BEMPX_GetInteger( lDBID_NetExcessCreditCost_NumTiers,       iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                if (lNumTiers < 1 || sPeriodType.isEmpty())
                                                   sErrMsg = QString( "CUAC %1 Utility bill calc error:  invalid data describing NetExcessCreditCosts #%2 (occur %3) (RateSeasons #%4, TOUPeriod #%5)" ).arg( saFuelLabels[iFuel], QString::number( iCostIdx+1 ), QString::number( iNetExcsCredCostObjIdx ), QString::number( iSeas+1 ), QString::number( iTOUPer+1 ) );
                                                else if (bOldCUAC)
                                                   BEMPX_WriteLogFile( QString( "   utility bill calc issue:  NetExcessCreditCosts #%1, %2 / %3: ignored due to incompatibility w/ monthly (old) CUAC energy use details" ).arg( QString::number( iNetExcsCredCostObjIdx+1 ), 
                                                                                       BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetExcessCreditCost:Name" ), iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                else
                                                {  double dMoTOUExports = 0.0;
                                                   for (iHr = iSeasMoHrStart; iHr <= iSeasMoHrEnd; iHr++)
                                                   {  i0YrDay  = (int) (iHr/24);
                                                      iHrInDay = iHr - (i0YrDay*24);
                                                      iDay = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDay>=0 && iDay<7) );
                                                      if (dDayHrMult[iDay][iHrInDay] > 0.1)
                                                         dMoTOUExports -= daHrlyExports[iHr];
                                                   }
                                                   if (dMoTOUExports <= 0)
                                                   {        if (iBillCalcDetails > 0)
                                                               BEMPX_WriteLogFile( QString( "                  NetExcessCreditCosts #%1, %2 / %3: ignored due to no exports" ).arg( QString::number( iNetExcsCredCostObjIdx+1 ), 
                                                                                                                  BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetExcessCreditCost:Name" ), iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                   }
                                                   else
                                                   {        if (iBillCalcDetails > 0)
                                                               BEMPX_WriteLogFile( QString( "                  NetExcessCreditCosts #%1, %2 / %3:" ).arg( QString::number( iNetExcsCredCostObjIdx+1 ), 
                                                                                                                  BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetExcessCreditCost:Name" ), iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      long lNumTiers      = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_NetExcessCreditCost:NumTiers" ), iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      if (lNumTiers > 0)
                                                      {  double dThisCredit = 0.0;
                                                         for (int iTierIdx = 0; (iTierIdx < lNumTiers && dMoTOUExports > 0 && sErrMsg.isEmpty()); iTierIdx++)
                                                         {  BEMObject* pTierObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_NetExcessCreditCost:Tiers" )+iTierIdx, iSpecVal, iErr, iNetExcsCredCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                            int iTierObjIdx     = (pTierObj == NULL ? -1 : BEMPX_GetObjectIndex( pTierObj->getClass(), pTierObj, iCUAC_BEMProcIdx ));
                                                            if (iTierObjIdx < 0)
                                                               sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve Tier #%2 for Season #%3, CPR_NetSurplusCompensationCost #%4" ).arg( saFuelLabels[iFuel], QString::number( iTierIdx+1 ), QString::number( iSeas+1 ), QString::number( iNetExcsCredCostObjIdx+1 ) );
                                                            else
                                                            {  long lTierNumber  = BEMPX_GetInteger( lDBID_Tier_TierNumber, iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                               double dPrice     = BEMPX_GetFloat(   lDBID_Tier_Price,      iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                               double dQuantity  = BEMPX_GetFloat(   lDBID_Tier_Quantity,   iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                               if (dQuantity < 0)  // dQuantity undefined
                                                                  dQuantity = dMoTOUExports;
                                                               else
                                                                  dQuantity = std::min( dQuantity, dMoTOUExports );
                                                               double dThisTierCredit = (dPrice * dQuantity);
                                                               dMoTOUExports -= dQuantity;
                                                               dThisCredit += dThisTierCredit;
                                                                  if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                                     BEMPX_WriteLogFile( QString( "                           Tier #%1 %2 @ price %3 = %4" ).arg( QString::number( iTierIdx+1 ), QString::number( dQuantity ), QString::number( dPrice ), QString::number( dThisTierCredit ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         }  }
                                                         dMonBypassableCost -= dThisCredit;
                                                                  if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                                     BEMPX_WriteLogFile( QString( "                     credit amount: %1  (cumulative %2 cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( dThisCredit ), pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dMonNonBypassableCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                   }  }
                                          }  }  }
                                       }
                                 }  }  // end of loop over TOU periods of Season

                                 // CPR_RateSeason:SeasonCosts
                                 BEMObject* pSeasCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_RateSeason:SeasonCosts" ), iSpecVal, iErr, iSeasObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                 int iSeasCostObjIdx     = (pSeasCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pSeasCostObj->getClass(), pSeasCostObj, iCUAC_BEMProcIdx ));
                                 if (iSeasCostObjIdx >= 0)
                                 {                    if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "               SeasonCost %1:" ).arg( BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_SeasonCost:Name" ), iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    int iFxdCost;

                                    // CPR_SeasonCost:FixedCosts
                                    long lNumFixedCosts = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_SeasonCost:NumFixedCosts" ), iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    for (iFxdCost=0; (iFxdCost < lNumFixedCosts && sErrMsg.isEmpty()); iFxdCost++)
                                    {  BEMObject* pFxdCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_SeasonCost:FixedCosts" )+iFxdCost, iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       int iFxdCostObjIdx     = (pFxdCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pFxdCostObj->getClass(), pFxdCostObj, iCUAC_BEMProcIdx ));
                                       if (iFxdCostObjIdx < 0)
                                          sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve FixedCost #%2 for SeasonCost #%3" ).arg( saFuelLabels[iFuel], QString::number( iFxdCost+1 ), QString::number( iSeas+1 ) );
                                       else
                                       {  QString sCostName = BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_FixedCost:CostName" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          if (sCostName.indexOf("Minimum") >= 0)
                                          {  // ignore 'Minimum...' charges here - only apply those in MinimumBillCosts
                                             if (iMoGrp==0 && iMo==iMoGrpStrt[iMoGrp])  // was: (iMo==0)
                                                BEMPX_WriteLogFile( QString( "                  FixedCost '%1' being ignored - minimum charges expected in MinimumBillCosts / %2 tariff '%3', season #%4 %5" ).arg( 
                                                                                                               sCostName, saFuelLabels[iFuel], qsEncodedRateName, QString::number( iSeas+1 ), qsSeasName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          }
                                          else
                                          {        if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                  FixedCost #%1, %2 / %3:" ).arg( QString::number( iFxdCostObjIdx+1 ), 
                                                                                                         BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_FixedCost:Name"     ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                             double dAmount      = BEMPX_GetFloat(  BEMPX_GetDatabaseID(  "CPR_FixedCost:Amount"        ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             QString sPeriodType = BEMPX_GetString( BEMPX_GetDatabaseID(  "CPR_FixedCost:PeriodType"    ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             long lNonBypassable = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_FixedCost:NonBypassable" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );   // SAC 09/11/23
                                             double dThisFxdCost = 0.0;
                                             if (!sPeriodType.compare("PerDayBilled"))
                                                dThisFxdCost = (dAmount * iNumDaysInMonth[iMo]);
                                             else if (!sPeriodType.compare("PerBillingCycle"))
                                                dThisFxdCost = dAmount;
                                             else
                                                sErrMsg = QString( "CUAC %1 Utility bill calc error:  unrecognized PeriodType '%2' for FixedCost #%3, season #%4 %5" ).arg( 
                                                                                    saFuelLabels[iFuel], sPeriodType, QString::number( iFxdCost+1 ), QString::number( iSeas+1 ), qsSeasName );
                                             if (lNonBypassable)
                                                dMonNonBypassableCost += dThisFxdCost;
                                             else
                                                dMonBypassableCost += dThisFxdCost;
                                                   if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                     amount: %1  (cumulative %2 cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( dThisFxdCost ), pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dMonNonBypassableCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          }
                                    }  }

                                    // CPR_SeasonCost:MinimumBillCosts
                                    lNumFixedCosts = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_SeasonCost:NumMinimumBillCosts" ), iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    for (iFxdCost=0; (iFxdCost < lNumFixedCosts && sErrMsg.isEmpty()); iFxdCost++)
                                    {  BEMObject* pFxdCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_SeasonCost:MinimumBillCosts" )+iFxdCost, iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       int iFxdCostObjIdx     = (pFxdCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pFxdCostObj->getClass(), pFxdCostObj, iCUAC_BEMProcIdx ));
                                       if (iFxdCostObjIdx < 0)
                                          sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve MinimumBillCost (FixedCost) #%2 for SeasonCost #%3" ).arg( saFuelLabels[iFuel], QString::number( iFxdCost+1 ), QString::number( iSeas+1 ) );
                                       else
                                       {  QString sCostName = BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_FixedCost:CostName" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                   if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                  MinimumBill FixedCost #%1, %2 / %3:" ).arg( QString::number( iFxdCostObjIdx+1 ), 
                                                                                                         BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_FixedCost:Name"     ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          double dAmount      = BEMPX_GetFloat(  BEMPX_GetDatabaseID( "CPR_FixedCost:Amount"     ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          QString sPeriodType = BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_FixedCost:PeriodType" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          double dThisFxdCost = 0.0;
                                          if (!sPeriodType.compare("PerDayBilled"))
                                             dThisFxdCost = (dAmount * iNumDaysInMonth[iMo]);
                                          else if (!sPeriodType.compare("PerBillingCycle"))
                                             dThisFxdCost = dAmount;
                                          else
                                             sErrMsg = QString( "CUAC %1 Utility bill calc error:  unrecognized PeriodType '%2' for MinimumBill FixedCost #%3, season #%4 %5" ).arg( 
                                                                                 saFuelLabels[iFuel], sPeriodType, QString::number( iFxdCost+1 ), QString::number( iSeas+1 ), qsSeasName );
                                          dMonMinCost += dThisFxdCost;
                                                   if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                     amount: %1  (%2 minimum cost: %3)" ).arg( QString::number( dThisFxdCost ), pszMoLabels[iMo], QString::number( dMonMinCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    }  }

                                    // CPR_SeasonCost:NetSurplusCompensationCosts
                                    lNumFixedCosts = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_SeasonCost:NumNetSurplusCompensationCosts" ), iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    for (iFxdCost=0; (iFxdCost < lNumFixedCosts && sErrMsg.isEmpty()); iFxdCost++)
                                    {  BEMObject* pFxdCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_SeasonCost:NetSurplusCompensationCosts" )+iFxdCost, iSpecVal, iErr, iSeasCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                       int iFxdCostObjIdx     = (pFxdCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pFxdCostObj->getClass(), pFxdCostObj, iCUAC_BEMProcIdx ));
                                       if (iFxdCostObjIdx < 0)
                                          sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve NetSurplusCompensationCost #%2 for SeasonCost #%3" ).arg( saFuelLabels[iFuel], QString::number( iFxdCost+1 ), QString::number( iSeas+1 ) );
                                       else
                                       {  QString sCostName = BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetSurplusCompensationCost:CostName" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                          double dMoNetSurplus = 0.0;
                                          if (!bOldCUAC)
                                          {  // HOURLY simulation results
                                             for (iHr = iSeasMoHrStart; iHr <= iSeasMoHrEnd; iHr++)
                                                dMoNetSurplus += (daHrlyTotUse[iHr] + daHrlyExports[iHr]);
                                          }
                                          else
                                          {  // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                                             dMoNetSurplus = dTotUseByMo[iMo];
                                          }
                                          if (dMoNetSurplus >= 0)
                                          {        if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                  NetSurplusCompensationCost #%1, %2 / %3: ignored due to no net surplus (%4 energy use)" ).arg( QString::number( iFxdCostObjIdx+1 ), 
                                                                                                         BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetSurplusCompensationCost:Name" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName, QString::number( dMoNetSurplus ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          }
                                          else
                                          {
                                                   if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "                  NetSurplusCompensationCost #%1, %2 / %3:" ).arg( QString::number( iFxdCostObjIdx+1 ), 
                                                                                                         BEMPX_GetString( BEMPX_GetDatabaseID( "CPR_NetSurplusCompensationCost:Name" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx ), sCostName ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                             long lNumTiers      = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_NetSurplusCompensationCost:NumTiers" ), iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                             if (lNumTiers > 0)
                                             {  double dThisCredit = 0.0;
                                                for (int iTierIdx = 0; (iTierIdx < lNumTiers && dMoNetSurplus < 0 && sErrMsg.isEmpty()); iTierIdx++)
                                                {  BEMObject* pTierObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_NetSurplusCompensationCost:Tiers" )+iTierIdx, iSpecVal, iErr, iFxdCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                   int iTierObjIdx     = (pTierObj == NULL ? -1 : BEMPX_GetObjectIndex( pTierObj->getClass(), pTierObj, iCUAC_BEMProcIdx ));
                                                   if (iTierObjIdx < 0)
                                                      sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve Tier #%2 for Season #%3, NetSurplusCompensationCost #%4" ).arg( saFuelLabels[iFuel], QString::number( iTierIdx+1 ), QString::number( iSeas+1 ), QString::number( iFxdCost+1 ) );
                                                   else
                                                   {  long lTierNumber  = BEMPX_GetInteger( lDBID_Tier_TierNumber, iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      double dPrice     = BEMPX_GetFloat(   lDBID_Tier_Price,      iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      double dQuantity  = BEMPX_GetFloat(   lDBID_Tier_Quantity,   iSpecVal, iErr, iTierObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                                      if (bFullRetailReimbForExports && qsReconciliationPeriod.compare("Perennially")!=0 && qsReconciliationPeriod.compare("Monthly")!=0)     // prevent comp calc now if reconciliation flagged for annual - SAC 12/04/23
                                                      {  dFinalNetSurplusCompPrice = dPrice;
                                                            if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                               BEMPX_WriteLogFile( QString( "                           Tier #%1: storing price of %3 for final reconciliation" ).arg( QString::number( iTierIdx+1 ), QString::number( dPrice ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         dThisCredit = 0.0;
                                                         iTierIdx = lNumTiers-1;
                                                      }
                                                      else
                                                      {  if (dQuantity < 0)  // dQuantity undefined
                                                            dQuantity = -1*dMoNetSurplus;
                                                         else
                                                            dQuantity = std::min( dQuantity, (-1*dMoNetSurplus) );
                                                         double dThisTierCredit = (dPrice * dQuantity);
                                                         dMoNetSurplus += dQuantity;
                                                         dThisCredit += dThisTierCredit;
                                                            if (iBillCalcDetails > 0 && sErrMsg.isEmpty())
                                                               BEMPX_WriteLogFile( QString( "                           Tier #%1: %2 @ price %3 = %4" ).arg( QString::number( iTierIdx+1 ), QString::number( dQuantity ), QString::number( dPrice ), QString::number( dThisTierCredit ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                }  }  }
                                                dMonBypassableCost -= dThisCredit;
                                                         if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "                     credit amount: %1  (cumulative %2 cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( dThisCredit ), pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dMonNonBypassableCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          }  }
                                    }  }

                                 }  // have valid SeasonCosts

                              }  // end of if this season overlaps w/ iMo
                           }
                        }  // end of loop over seasons (overlapping w/ month)

                        if (lNumHourlyTOUCosts > 0 && bIgnoreHourlyTOU)    // SAC 12/13/23
                              BEMPX_WriteLogFile( QString( "   HourlyTOUCosts (%1 found) being ignored due to user rate adjustment inputs" ).arg( QString::number( lNumHourlyTOUCosts ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        else if (lNumHourlyTOUCosts > 0)       // SAC 09/11/23
                        {  double dMoExports = 0.0;
                           if (bFullRetailReimbForExports)     // SAC 12/04/23
                              BEMPX_WriteLogFile( QString( "   utility bill calc issue:  HourlyTOUCosts for %1 ignored due to incompatibility w/ NetMetering rate types" ).arg( pszMoLabels[iMo] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           else if (!bOldCUAC)
                           {  // HOURLY simulation results
                              for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                                 dMoExports -= daHrlyExports[iHr];
                           }
                           else
                           {  // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                              BEMPX_WriteLogFile( QString( "   utility bill calc issue:  HourlyTOUCosts for %1 ignored due to incompatibility w/ monthly (old) CUAC energy use details" ).arg( pszMoLabels[iMo] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           }
                           if (dMoExports <= 0.0)
                           {                       if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "            skipping HourlyTOUCosts for %1 due to no exports" ).arg( pszMoLabels[iMo] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           }
                           else
                           {  int iDayIdx;
                              // array days:  0-Weekday / 1-Weekend   -- day of week:  0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                              bool bDayLoaded[2] = { false, false };
                              double dDayHrMult[2][24] = { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                                           { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };
                              for (int iHrlyTOUCost=0; (iHrlyTOUCost < lNumHourlyTOUCosts && sErrMsg.isEmpty()); iHrlyTOUCost++)
                              {  BEMObject* pHrlyTOUCostObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "HourlyTOUCosts", iCID_UtilityRate )+iHrlyTOUCost, iSpecVal, iErr, iG2RateObjIdx[iFuel], BEMO_User, iCUAC_BEMProcIdx );
                                 int iHrlyTOUCostObjIdx     = (pHrlyTOUCostObj == NULL ? -1 : BEMPX_GetObjectIndex( pHrlyTOUCostObj->getClass(), pHrlyTOUCostObj, iCUAC_BEMProcIdx ));
                                 if (iHrlyTOUCostObjIdx < 0)
                                    sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve HourlyTOUCosts #%2" ).arg( saFuelLabels[iFuel], QString::number( iHrlyTOUCost+1 ) );
                                 else
                                 {  QString qsHrlyTOUCostName       = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_HourlyTOUCost:Name"                     ), iSpecVal, iErr, iHrlyTOUCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    QString qsHrlyTOUCostCostName   = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_HourlyTOUCost:CostName"                 ), iSpecVal, iErr, iHrlyTOUCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    QString qsHrlyTOUCostApplicDays = BEMPX_GetString(  BEMPX_GetDatabaseID( "CPR_HourlyTOUCost:ApplicableDays"           ), iSpecVal, iErr, iHrlyTOUCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    long lNumHrlyTOUCostMonths      = BEMPX_GetInteger( BEMPX_GetDatabaseID( "CPR_HourlyTOUCost:NumHourlyTimeOfUseMonths" ), iSpecVal, iErr, iHrlyTOUCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );   assert( lNumHrlyTOUCostMonths == 12 );
                                    iDayIdx = (qsHrlyTOUCostApplicDays.compare("Weekends")==0 ? 1 : 0);
                                    BEMObject* pHrlyTOUMoObj     = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CPR_HourlyTOUCost:HourlyTimeOfUseMonths" )+iMo, iSpecVal, iErr, iHrlyTOUCostObjIdx, BEMO_User, iCUAC_BEMProcIdx );
                                    int iHrlyTOUMoObjIdx         = (pHrlyTOUMoObj == NULL ? -1 : BEMPX_GetObjectIndex( pHrlyTOUMoObj->getClass(), pHrlyTOUMoObj, iCUAC_BEMProcIdx ));
                                    if (iHrlyTOUMoObjIdx < 0)
                                       sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve HourlyTOUMonth #%2 (%3)" ).arg( saFuelLabels[iFuel], QString::number( iMo+1 ), pszMoLabels[iMo] );
                                    else
                                    {  int iNumHrs = BEMPX_GetFloatArray( BEMPX_GetDatabaseID( "CPR_HourlyTOUMonth:Prices" ), dDayHrMult[iDayIdx], 24, 0, BEMP_Flt, iHrlyTOUMoObjIdx );      assert( iNumHrs == 24 );
                                       if (iNumHrs==24)
                                       {  bDayLoaded[iDayIdx] = true;
                                          if (qsHrlyTOUCostApplicDays.compare("All")==0)
                                          {  bDayLoaded[1] = true;
                                             for (iHr=0; iHr<24; iHr++)
                                                dDayHrMult[1][iHr] = dDayHrMult[0][iHr];
                                          }        if (iBillCalcDetails > 0)
                                                      BEMPX_WriteLogFile( QString( "            HourlyTOUCosts for %1, %2 (%3) %4 %5 loaded:  %6, %7, %8, ..." ).arg( pszMoLabels[iMo], qsHrlyTOUCostName, QString::number( iHrlyTOUCostObjIdx ), qsHrlyTOUCostCostName, qsHrlyTOUCostApplicDays, QString::number( dDayHrMult[iDayIdx][0] ), QString::number( dDayHrMult[iDayIdx][1] ), QString::number( dDayHrMult[iDayIdx][2] ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }
                                       else
                                       {  sErrMsg = QString( "CUAC %1 Utility bill calc error:  unable to retrieve HourlyTOUMonth %2 (%3) %4 %5 Prices for %6" ).arg( saFuelLabels[iFuel], qsHrlyTOUCostName, QString::number( iHrlyTOUCostObjIdx ), qsHrlyTOUCostCostName, qsHrlyTOUCostApplicDays, pszMoLabels[iMo] );
                                          //BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    }  }
                              }  }
                              if (sErrMsg.isEmpty())
                              {  double dThisCredit = 0.0;
                                 int iHrInDay, iDayOfWk;
                                 for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                                    if (daHrlyExports[iHr] < 0.0)
                                    {  i0YrDay  = (int) (iHr/24);
                                       iHrInDay = iHr - (i0YrDay*24);
                                       iDayOfWk = i0YrDay + 3 - ( ((int) ((i0YrDay+3)/7)) * 7 );    assert( (iDay>=0 && iDay<7) );      // 0-Mon  1-Tue  2-Wed  3-Thu  4-Fri  5-Sat  6-Sun
                                       iDayIdx  = (iDayOfWk < 5 ? 0 : 1);    // 0-Weekday  1-Weekend
                                       if (bDayLoaded[iDayIdx])
                                       {  dThisCredit -= (daHrlyExports[iHr] * dDayHrMult[iDayIdx][iHrInDay]);
                                                   if (iBillCalcDetails > 1)
                                                      BEMPX_WriteLogFile( QString( "                           iHr %1 / i0YrDay %2 / iHrInDay %3 / iDayOfWk %4 / iDayIdx %5 / exported %6 / TOUcost %7 / cum. credit %8" ).arg( QString::number( iHr ), QString::number( i0YrDay ), QString::number( iHrInDay ), QString::number( iDayOfWk ), QString::number( iDayIdx ), QString::number( daHrlyExports[iHr] ), QString::number( dDayHrMult[iDayIdx][iHrInDay] ), QString::number( dThisCredit ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    }  }
                                 dMonBypassableCost -= dThisCredit;
                                                         if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "                     credit amount: %1  (cumulative %2 cost: %3/%4 (bypassable/non-bypsbl))" ).arg( QString::number( dThisCredit ), pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dMonNonBypassableCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           }  }
                        }  // end of if lNumHourlyTOUCosts > 0

                        if (!qsReconciliationPeriod.compare("Perennially"))
                        {  // NO reconciliation ever!
                           if (dMonBypassableCost < 0.0)
                           {                             if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "              zeroing out %1 bypassable credit of %2 (reconciliation period = Perennially)" ).arg( pszMoLabels[iMo], QString::number( -dMonBypassableCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              dMonBypassableCost = 0.0;  // zero out month's credit
                        }  }
                        else if (!qsReconciliationPeriod.compare("Monthly"))
                        {  // Monthly reconciliation
                           // NetSurplusCompensationCosts should have already been applied above
                           // leave dMonBypassableCost unchanged
                        }
                        else if (bFullRetailReimbForExports)      // NetMetering
                        {  // Annual (or undefined) reconciliation
                           double dMoNetSurplus = 0.0;
                           if (!bOldCUAC)
                           {  // HOURLY simulation results
                              for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                                 dMoNetSurplus += (daHrlyTotUse[iHr] + daHrlyExports[iHr]);
                           }
                           else
                              // MONTHLY simulation results (from old CUAC project data) - SAC 09/18/23
                              dMoNetSurplus = dTotUseByMo[iMo];

                           // push any credit this month into CarryOver*
                           if (dMonBypassableCost < 0.0)
                           {  dCarryOverKWH -= std::min( dMoNetSurplus, 0.0 );
                                                      if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "              pushing %1 bypassable credit of %2 to next month (rolling credit: $%3 & %4 kWh)" ).arg( pszMoLabels[iMo], QString::number( -dMonBypassableCost ), QString::number( dCarryOverDollars-dMonBypassableCost ), QString::number( dCarryOverKWH ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              dCarryOverDollars -= dMonBypassableCost;
                              dMonBypassableCost = 0.0;
                           }
                           else if (dCarryOverDollars > 0.0)
                           {  if ((dMonBypassableCost+dMonNonBypassableCost) <= dMonMinCost)
                              {  // no changes to rollover credit if we will be applying monthly min charge
                                                      if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "              leaving rolling credit unchanged in %1, min charge of %2 >= (nonbypassable + bypassable charges: %3) (remaining rolling credit: $%4 & %5 kWh)" ).arg( pszMoLabels[iMo], QString::number( dMonMinCost ), QString::number( dMonBypassableCost+dMonNonBypassableCost ), QString::number( dCarryOverDollars ), QString::number( dCarryOverKWH )  ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              }
                              else if (dCarryOverDollars > dMonBypassableCost)
                              {  // rollover credit exceeds MonBypassableCost
                                 dCarryOverKWH -= (dCarryOverKWH * dMonBypassableCost / dCarryOverDollars);
                                                      if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "              reducing rolling credit in %1 by bypassable cost of %2 (remaining rolling credit: $%3 & %4 kWh)" ).arg( pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dCarryOverDollars-dMonBypassableCost ), QString::number( dCarryOverKWH )  ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                 dCarryOverDollars -= dMonBypassableCost;
                                 dMonBypassableCost = 0.0;
                              }
                              else
                              {  // MonBypassableCost >= rollover credit
                                                      if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "              reducing %1 bypassable cost of %2 by rolling credit of %3 (remaining bypassable cost: %4)" ).arg( pszMoLabels[iMo], QString::number( dMonBypassableCost ), QString::number( dCarryOverDollars ), QString::number( dMonBypassableCost-dCarryOverDollars ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                 dMonBypassableCost -= dCarryOverDollars;
                                 dCarryOverKWH     = 0.0;
                                 dCarryOverDollars = 0.0;
                              }
                           }

                           if ( iMoGrp==(iNumMoGrps-1) && iMo==iMoGrpEnd[iMoGrp] )   // final month of Annual (or undefined) NetMetering reconciliation   // was: iMo == 11 - SAC 12/10/23
                           {  if (dCarryOverDollars > 0.0)
                              { // if (bFullRetailReimbForExports)
                                // {
                                    if (dCarryOverKWH > 0 && dFinalNetSurplusCompPrice > 0)
                                    {                    if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "              final month NetSurplusCompensation: %1 kWh @ %2 $/kWh => credit of $%3" ).arg( 
                                                               QString::number( dCarryOverKWH ), QString::number( dFinalNetSurplusCompPrice ), QString::number( dCarryOverKWH*dFinalNetSurplusCompPrice ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       dMonBypassableCost -= (dCarryOverKWH * dFinalNetSurplusCompPrice);
                                    }
                                    else
                                    {                    if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "              final month NetSurplusCompensation: %1 kWh @ %2 $/kWh => no credit" ).arg( 
                                                               QString::number( dCarryOverKWH ), QString::number( dFinalNetSurplusCompPrice ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    }
                                // }
                                // else
                                // {                       if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                //                            BEMPX_WriteLogFile( QString( "              final month bypassable cost reduced by rolling credit of %1 (%2 bypassable cost %3)" ).arg( 
                                //                               QString::number( dCarryOverDollars ), QString::number( dMonBypassableCost-dCarryOverDollars ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                //    dMonBypassableCost -= dCarryOverDollars;
                                // }
                              }
                              dCarryOverKWH = dCarryOverDollars = 0.0;
                           }
                        }

                        //if (dMonCost < dMonMinCost)      // SAC 09/03/23
                        //   dMonCost = dMonMinCost;
                        double dMonCost = 0.0;
                        if (dMonBypassableCost < 0.0)    // SAC 09/11/23
                           dMonCost = std::max( dMonNonBypassableCost, dMonMinCost ) + dMonBypassableCost;
                        else 
                           dMonCost = std::max( (dMonNonBypassableCost + dMonBypassableCost), dMonMinCost );
                        if (dCommunitySolarAnnCredit > 0.0)    // adjust monthly bill by CommunitySolar credit amount - SAC 10/03/23
                        {  dMonCost -= (dCommunitySolarAnnCredit/12.0);
                                                         if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "                 monthly community solar credit applied: $%1" ).arg( QString::number( (dCommunitySolarAnnCredit/12.0) ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }
                        // apply user/default/research limits on monthly bills - SAC 12/14/23
                        if (dElecBillMinMoCharge == -1 && dMonCost < dMonMinCost)
                        {  BEMPX_WriteLogFile( QString( "              increasing monthly cost (%1 -> %2) to prevent bill less than monthly minimum as defined by tariff" ).arg( QString::number( dMonCost ), QString::number( dMonMinCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           dMonCost = dMonMinCost;
                        }
                        else if (dElecBillMinMoCharge >= 0 && dMonCost < dElecBillMinMoCharge)
                        {  BEMPX_WriteLogFile( QString( "              increasing monthly cost (%1 -> %2) to prevent bill less than that prescribed in ruleset" ).arg( QString::number( dMonCost ), QString::number( dElecBillMinMoCharge ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           dMonCost = dMonMinCost;
                        }
                        dAnnCost += dMonCost;
                                                         if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                            BEMPX_WriteLogFile( QString( "              %1 charge: %2 / annual charge: %3" ).arg( pszMoLabels[iMo], QString::number( dMonCost ), QString::number( dAnnCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        BEMPX_SetBEMData( lDBID_FuelCostResult+iMo+2, BEMP_Flt, (void*) &dMonCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly cost

                     }  // end of loop over months

                     // apply user/default/research limits on annual bill - SAC 12/14/23
                     if (dElecBillMinAnnCharge > -998 && dAnnCost < dElecBillMinAnnCharge)
                     {  BEMPX_WriteLogFile( QString( "            increasing annual cost (%1 -> %2) to prevent bill less than that prescribed in ruleset" ).arg( QString::number( dAnnCost ), QString::number( dElecBillMinAnnCharge ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        dAnnCost = dElecBillMinAnnCharge;
                     }

                     if (iFuel == 0 && dTotNonExportElecUse[iMtr] >= 0.001)
                        dTotSiteHourlyUse = dTotNonExportElecUse[iMtr];    // revised to store/use version of total use that ignores hours of elec export - SAC 12/13/24

                     double dCostPerUnitEnergy = 0.0;       // SAC 09/28/23
                     if (dAnnCost > 0.01 && dTotSiteHourlyUse > 0.1)
                        dCostPerUnitEnergy = dAnnCost / dTotSiteHourlyUse;
                     else if (dAnnCost > 0.01)
                        dCostPerUnitEnergy = dAnnCost;
                     QString sFuelCostPerEnergyPropName = (iFuel==0 ? "CUACResults:ElecCostPerEnergyUse" : "CUACResults:GasCostPerEnergyUse");
                     long lDBID_FuelCostPerEnergy = BEMPX_GetDatabaseID( sFuelCostPerEnergyPropName );   assert( lDBID_FuelCostPerEnergy > 0 );
                     if (lDBID_FuelCostPerEnergy > 0)
                        BEMPX_SetBEMData( lDBID_FuelCostPerEnergy, BEMP_Flt, (void*) &dCostPerUnitEnergy, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     QString sFuelEnergyUsedPropName = (iFuel==0 ? "CUACResults:ElecEnergyUsed" : "CUACResults:GasEnergyUsed");
                     long lDBID_FuelEnergyUsed = BEMPX_GetDatabaseID( sFuelEnergyUsedPropName );   assert( lDBID_FuelEnergyUsed > 0 );
                     if (lDBID_FuelEnergyUsed > 0)
                        BEMPX_SetBEMData( lDBID_FuelEnergyUsed, BEMP_Flt, (void*) &dTotSiteHourlyUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                                                         if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                         {  if (dCostPerUnitEnergy > 0.01)
                                                                  BEMPX_WriteLogFile( QString( "            total annual charge: $%1  ($%2/%3)" ).arg( QString::number( dAnnCost ), QString::number( dCostPerUnitEnergy ), saFuelUnitLabels1[iFuel] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                            else  BEMPX_WriteLogFile( QString( "            total annual charge: $%1"           ).arg( QString::number( dAnnCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         }
                     BEMPX_SetBEMData( lDBID_FuelCostResult  , BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual cost
                     dAnnCost /= 12;
                     BEMPX_SetBEMData( lDBID_FuelCostResult+1, BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly avg cost
                  }
               }  // END OF  if (iG2RateObjIdx[iFuel] >= 0) - calc utility bill based on 2023+ CPR rates (above)
               else if (utilRate[iFuel].bOK)
               {  double dFuelRateMult = 1.0;
                  if (iFuel == 0 && utilRate[iFuel].sUnits.compare( "kWh", Qt::CaseInsensitive ))
                     sErrMsg = QString( "CUAC Electric Utility Rate Units (%1) not recognized" ).arg( utilRate[iFuel].sUnits );
                  else if (iFuel == 1 && utilRate[iFuel].sUnits.compare( "therms", Qt::CaseInsensitive )==0)
                     dFuelRateMult = 1.0;      // hourly data alrady in therms - SAC 10/26/22
                  else if (iFuel == 1 && utilRate[iFuel].sUnits.compare( "gallons", Qt::CaseInsensitive )==0)
                     dFuelRateMult = 100/91.647;   // therms to gallons conversion
                  else if (iFuel == 1 && utilRate[iFuel].sUnits.compare( "kBtu", Qt::CaseInsensitive ))
                     sErrMsg = QString( "CUAC Gas Utility Rate Units (%1) not recognized" ).arg( utilRate[iFuel].sUnits );

                  if (!sErrMsg.isEmpty())
                     BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {  double dAnnCost = 0.0;
                                                      if (iBillCalcDetails > 0)
                                                      {  BEMPX_WriteLogFile( QString( "   %1 annual %2 use: %3 %4" ).arg( pszCUACCSVUnitTypeLabels[iMtr], saFuelLabels[iFuel], QString::number( dTotAnnUse ), saFuelUnitLabels[iFuel] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         BEMPX_WriteLogFile( QString( "      Gen1 %1 utility bill calc -" ).arg( saFuelLabels[iFuel] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      }
                     for (iMo=0; iMo<12; iMo++)
                     {  double dThisBinCost, dMonCost = utilRate[iFuel].dMonthlyCharge;
                        int iSeason = utilRate[iFuel].laSeasonMonthMap[iMo];  // 0-Win, 1-Sum
                        double dDailyUseBin = utilRate[iFuel].daSeasonalUsePerDay[iSeason] * iNumDaysInMonth[iMo];
                        double dMonRateUse = dTotUseByMo[iMo] * dFuelRateMult;
                                                      if (iBillCalcDetails > 0)
                                                      {  if (dTotUseByMoBeforeCarryover[iMo] > (dTotUseByMo[iMo]-0.1) && dTotUseByMoBeforeCarryover[iMo] < (dTotUseByMo[iMo]+0.1))
                                                               BEMPX_WriteLogFile( QString( "            %1, season %2, %3 use %4 %5, mo cost $%6"                       ).arg( pszMoLabels[iMo], QString::number(iSeason), saFuelLabels[iFuel], QString::number(dMonRateUse), utilRate[iFuel].sUnits, QString::number(dMonCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         else  BEMPX_WriteLogFile( QString( "            %1, season %2, %3 use %4 %5 (%6 before carryover), mo cost $%7" ).arg( pszMoLabels[iMo], QString::number(iSeason), saFuelLabels[iFuel], QString::number(dMonRateUse), utilRate[iFuel].sUnits, QString::number( (dTotUseByMoBeforeCarryover[iMo] * dFuelRateMult) ), QString::number(dMonCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      }
                        for (int iBin=0; (dMonRateUse > 0 && iBin < 4); iBin++)
                        {
                           if (dMonRateUse <= dDailyUseBin)
                           {  dThisBinCost = (dMonRateUse * utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]);
                              dMonCost   += dThisBinCost;
                              dMonRateUse = 0.0;
                                                      if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "                  bin %1:  %2 %3 @ $%4 = $%5" ).arg( QString::number(iBin+1), QString::number(dMonRateUse), utilRate[iFuel].sUnits, QString::number(utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]), QString::number(dThisBinCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           }
                           else
                           {  dThisBinCost = (dDailyUseBin * utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]);
                              dMonCost    += dThisBinCost;
                              dMonRateUse -= dDailyUseBin;
                                                      if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "                  bin %1:  %2 %3 @ $%4 = $%5  (%6 remaining)" ).arg( QString::number(iBin+1), QString::number(dDailyUseBin), utilRate[iFuel].sUnits, QString::number(utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]), QString::number(dThisBinCost), QString::number(dMonRateUse) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }  }
                        if (dMonRateUse > 0)  // apply final bin cost to all remaining use (?)
                        {  dThisBinCost = (dMonRateUse * utilRate[iFuel].daaBinSeasonalCost[4][iSeason]);
                           dMonCost    += dThisBinCost;
                                                      if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "                  remainder:  %1 %2 @ $%3 = $%4" ).arg( QString::number(dMonRateUse), utilRate[iFuel].sUnits, QString::number(utilRate[iFuel].daaBinSeasonalCost[4][iSeason]), QString::number(dThisBinCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }
                        if (dMonCost < utilRate[iFuel].dMinMonthlyCharge)
                        {  dMonCost = utilRate[iFuel].dMinMonthlyCharge;
                                                      if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "                  min monthly charge of $%1 applied" ).arg( QString::number(dMonCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }
                        if (dCommunitySolarAnnCredit > 0.0)    // adjust monthly bill by CommunitySolar credit amount - SAC 10/03/23
                        {  dMonCost -= (dCommunitySolarAnnCredit/12.0);
                                                      if (iBillCalcDetails > 0)
                                                         BEMPX_WriteLogFile( QString( "                  monthly community solar credit applied: $%1" ).arg( QString::number( (dCommunitySolarAnnCredit/12.0) ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }
                        dAnnCost += dMonCost;
                                                      if (iBillCalcDetails > 0 && dMonCost > 0.01)
                                                         BEMPX_WriteLogFile( QString( "               %1 charge $%2  (cumulative $%3)" ).arg( pszMoLabels[iMo], QString::number(dMonCost), QString::number(dAnnCost) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        BEMPX_SetBEMData( lDBID_FuelCostResult+iMo+2, BEMP_Flt, (void*) &dMonCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly cost
                     }

                     double dCostPerUnitEnergy = 0.0;       // SAC 09/28/23
                     if (dAnnCost > 0.01 && dTotSiteHourlyUse > 0.1)
                        dCostPerUnitEnergy = dAnnCost / dTotSiteHourlyUse;
                     else if (dAnnCost > 0.01)
                        dCostPerUnitEnergy = dAnnCost;
                     QString sFuelCostPerEnergyPropName = (iFuel==0 ? "CUACResults:ElecCostPerEnergyUse" : "CUACResults:GasCostPerEnergyUse");
                     long lDBID_FuelCostPerEnergy = BEMPX_GetDatabaseID( sFuelCostPerEnergyPropName );   assert( lDBID_FuelCostPerEnergy > 0 );
                     if (lDBID_FuelCostPerEnergy > 0)
                        BEMPX_SetBEMData( lDBID_FuelCostPerEnergy, BEMP_Flt, (void*) &dCostPerUnitEnergy, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     QString sFuelEnergyUsedPropName = (iFuel==0 ? "CUACResults:ElecEnergyUsed" : "CUACResults:GasEnergyUsed");
                     long lDBID_FuelEnergyUsed = BEMPX_GetDatabaseID( sFuelEnergyUsedPropName );   assert( lDBID_FuelEnergyUsed > 0 );
                     if (lDBID_FuelEnergyUsed > 0)
                        BEMPX_SetBEMData( lDBID_FuelEnergyUsed, BEMP_Flt, (void*) &dTotSiteHourlyUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                                                      if (sErrMsg.isEmpty() && iBillCalcDetails > 0)
                                                      {  if (dCostPerUnitEnergy > 0.01)
                                                               BEMPX_WriteLogFile( QString( "            total annual charge: $%1  ($%2/%3)" ).arg( QString::number( dAnnCost ), QString::number( dCostPerUnitEnergy ), saFuelUnitLabels1[iFuel] ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         else  BEMPX_WriteLogFile( QString( "            total annual charge: $%1"           ).arg( QString::number( dAnnCost ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                      }
                     BEMPX_SetBEMData( lDBID_FuelCostResult  , BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual cost
                     dAnnCost /= 12;
                     BEMPX_SetBEMData( lDBID_FuelCostResult+1, BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly avg cost
               }  }
            }
                     //1,           "ElecCosts",                         BEMP_Flt, 14,  1,  0,  Pres,  "$",                0,  0,                           1001, "ElectricityCosts",   ""  ; 1-Annual, 2-MonthlyAvg, 3-14-Monthly
                     //1,           "GasCosts",                          BEMP_Flt, 14,  1,  0,  Pres,  "$",                0,  0,                           1001, "GasCosts",    ""         ; "
      }  }
                     // struct CUACUtilityRate  // SAC 10/19/22
                     // {
                     //    bool    bOK;
                     //    QString sUnits;
                     //    double  dMonthlyCharge;
                     //    double  dMinMonthlyCharge;
                     //    long    lNumSeasons;
                     //    QString saSeasonLabels[12];
                     //    long    laSeasonMonthMap[12];
                     //    double  daSeasonalUsePerDay[12];
                     //    double  daaBinSeasonalCost[5][12];
                     // };

                  if (iBillCalcDetails > 0) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_FinalCalcs rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bFinalResultsCalcsEvalSuccessful = CMX_EvaluateRuleset( "CUAC_FinalCalcs" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - errors encountered evaluating CUAC_FinalCalcs rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }

   // setup reporting properties (from Proj & CUAC inputs) - SAC 10/31/24 (tic #1386)
   if (!bAbort && sErrMsg.isEmpty())
   {                 if (iBillCalcDetails > 0) 
                        BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupReportingProperties rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      CMX_EvaluateRuleset( "CUAC_SetupReportingProperties" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   }

   // write top portion of CUAC input/output CSV file (via ruleset) - SAC 10/20/22
   if (!bAbort && sErrMsg.isEmpty() && bWriteCSV)
   {  QString sIOCSVPathFile = BEMPX_GetString( BEMPX_GetDatabaseID( "InOutCSVPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
      if (sIOCSVPathFile.isEmpty())
         BEMPX_WriteLogFile( QString( "CUAC:InOutCSVPathFile undefined - needed for input/output CSV export" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      else
      {  QString sMsg;
         sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                      "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                      "(once the file is closed), or \n'Abort' to abort the %s.", "CSV", sIOCSVPathFile.toLocal8Bit().constData(), "CSV export" );
         if (!OKToWriteOrDeleteFile( sIOCSVPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
            BEMPX_WriteLogFile( QString( "Unable to write CUAC input/output CSV export file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         else
         {
                     if (iBillCalcDetails > 0) 
                        BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_WriteInputOutputCSV rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            BOOL bIOCSVExportEvalSuccessful = CMX_EvaluateRuleset( "CUAC_WriteInputOutputCSV" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
            BEMPX_RefreshLogFile();
            if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
            {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - errors encountered evaluating CUAC_WriteInputOutputCSV rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               return;
            }
            else if (!bOldCUAC)
            {  // HOURLY simulation results - SAC 09/18/23
               // append all hourly results to end of CSV file - SAC 10/20/22
               FILE *fp_CSV;
               int iErrorCode;
               try
               {
                  iErrorCode = fopen_s( &fp_CSV, sIOCSVPathFile.toLocal8Bit().constData(), "ab" );   // APPEND to CSV
                  if (iErrorCode != 0 || fp_CSV == NULL)
                     BEMPX_WriteLogFile( QString( "Error encountered opening CUAC CSV results file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {  double *pdHrlyUse[120];   // max should be NumDwellingMeters * (NumElecEnduses + NumGasEnduses)
                     int iHrlyUsePtrIdx = 0, iNumRptgMtrs = 0;
                     QString saCSVColLabels[3];
                     saCSVColLabels[0] = ",,,";    saCSVColLabels[1] = ",,,";    saCSVColLabels[2] = "Mo,Da,Hr,";
                     for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
                        if (laNumUnitsByBedrms[iMtr] > 0)
                        {  saCSVColLabels[0] += QString( "%1 Electric Use,,,,,,,,,,,,,%2 Gas Use,,,," ).arg( pszCUACCSVUnitTypeLabels[iMtr], pszCUACCSVUnitTypeLabels[iMtr] );
                           saCSVColLabels[1] += pszCUACCSVElecEnduseLabels;      saCSVColLabels[1] += pszCUACCSVGasEnduseLabels;
                           saCSVColLabels[2] += "(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(therms),(therms),(therms),(therms),";  // inserted another kWh for Batt - SAC 12/12/24
                           iNumRptgMtrs++;
                           for (iFuel=0; iFuel<2; iFuel++)
                              for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
                                 if (baHaveFuelEnduseHrlyResults[iFuel][iCEUIdx])
                                 {  int iInitMtrIdx                  = (iDataModel == 0 ? iaInitToRptsEnduseMap[iCEUIdx]     : iaResInitToRptsEnduseMap[iCEUIdx]     );
                                    const char* pszHrlyResultsEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iInitMtrIdx] : pszInitialCUACResEnduses[iInitMtrIdx] );
                                    pdHrlyUse[iHrlyUsePtrIdx] = NULL;
                                    int iResMtrIdx = (iFuel == 0 ? 0 : iResFuelMtrIdx);      // SAC 09/11/24 (res tic #1378)
                                    const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[iFuel][iMtr] : pszCUACResMeters[iResMtrIdx]);    // SAC 05/31/24   // fix bug in Res hrly export: iResFuelMtrIdx -> iResMtrIdx - SAC 12/13/24
                                    BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse[iHrlyUsePtrIdx], NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, iCUAC_BEMProcIdx );
                                    if (pdHrlyUse[iHrlyUsePtrIdx] == NULL)
                                       pdHrlyUse[iHrlyUsePtrIdx] = &daZero[0];      // to prevent CSV writing error when no Gas meter present in model - SAC 02/28/24
                                    iHrlyUsePtrIdx++;
                                 }
                        }  assert( iHrlyUsePtrIdx == (iNumRptgMtrs * 17) );

                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[0].toLocal8Bit().constData() );   
                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[1].toLocal8Bit().constData() );   
                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[2].toLocal8Bit().constData() );   

                     int iAnnHrIdx=0;
                     QString qsMtrResStr[NumDwellingMeters];
                     for (iMo=1; iMo<=12; iMo++)
                        for (iDay=1; iDay<=iNumDaysInMonth[iMo-1]; iDay++)
                           for (iHr=1; iHr<=24; iHr++)
                           {  for (iMtr=0; iMtr < iNumRptgMtrs; iMtr++)
                              {  int iMtrResColIdx = (iMtr * 17);
                                 qsMtrResStr[iMtr] = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17," ).arg(
                                             QString::number(pdHrlyUse[iMtrResColIdx   ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+1 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+2 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+3 ][iAnnHrIdx]),
                                             QString::number(pdHrlyUse[iMtrResColIdx+4 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+5 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+6 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+7 ][iAnnHrIdx]), 
                                             QString::number(pdHrlyUse[iMtrResColIdx+8 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+9 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+10][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+11][iAnnHrIdx]), 
                                             QString::number(pdHrlyUse[iMtrResColIdx+12][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+13][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+14][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+15][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+16][iAnnHrIdx]) );
                              }
                              switch (iNumRptgMtrs)
                              {  case  1 :  fprintf( fp_CSV,  "%d,%d,%d,%s\n",             iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData() );   break;
                                 case  2 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s\n",           iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData() );   break;
                                 case  3 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s\n",         iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData() );   break;
                                 case  4 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s\n",       iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData() );   break;
                                 case  5 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s\n",     iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
                                                                                                           qsMtrResStr[4].toLocal8Bit().constData() );   break;
                                 case  6 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s%s\n",   iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
                                                                                                           qsMtrResStr[4].toLocal8Bit().constData(), qsMtrResStr[5].toLocal8Bit().constData() );   break;
                                 case  7 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s%s%s\n", iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
                                                                                                           qsMtrResStr[4].toLocal8Bit().constData(), qsMtrResStr[5].toLocal8Bit().constData(), qsMtrResStr[6].toLocal8Bit().constData() );   break;
                              }  iAnnHrIdx++;
                           }
                     fflush( fp_CSV );
                     fclose( fp_CSV );
                  }
               }
               catch( ... ) {
                  //iRetVal = 4;
                  //sErrMsg = QString::asprintf( "Unknown error writing hourly CSV results file:  %s", sIOCSVPathFile.toLocal8Bit().constData() );
                  BEMPX_WriteLogFile( QString( "Unknown error writing CUAC CSV results file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
            }
   }  }  }


                     if (bStoreBEMDetails)
                     {  QString sDbgFN = sProcessingPath + sModelFileOnly + ".ibd-Detail-PostCUAC";
                        if (iBatchRunIdx > 0)
                           sDbgFN += QString("-%1").arg(QString::number( iBatchRunIdx ));
                        BEMPX_WriteProjectFile( sDbgFN.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, iCUAC_BEMProcIdx );
                     }

   // PDF report generation
   if (!bAbort && sErrMsg.isEmpty() && bWritePDF)
   {
      long lRptOption = BEMPX_GetInteger( BEMPX_GetDatabaseID( "RptOption", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );      //  1 "Draft" / 2 "Final" / 3 "Annual"
      int iRptID=0;
      QString sSubmitPDFPathFile = BEMPX_GetString( BEMPX_GetDatabaseID( "SubmitPDFPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
      if (sSubmitPDFPathFile.isEmpty())
         BEMPX_WriteLogFile( QString( "CUAC:SubmitPDFPathFile undefined - needed for submittal report PDF generation" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      else
      {  QString sMsg;
         sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                      "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                      "(once the file is closed), or \n'Abort' to abort the %s.", "PDF", sSubmitPDFPathFile.toLocal8Bit().constData(), "PDF report generation" );
         if (!OKToWriteOrDeleteFile( sSubmitPDFPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
            BEMPX_WriteLogFile( QString( "Unable to write CUAC submittal report PDF file:  %1" ).arg( sSubmitPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         else
         {
            iRptID = lRptOption;
            int iPDFGenRetVal = BEMPX_GeneratePDF( sSubmitPDFPathFile.toLocal8Bit().constData(), sRptGraphicsPath.toLocal8Bit().constData(), iRptID, iCUAC_BEMProcIdx, iDataModel );
            BEMPX_WriteLogFile( QString( "CUAC submittal report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sSubmitPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

            if (iPDFGenRetVal == 0)    // details report - SAC 01/03/23
            {  // same here for Details report
               QString sDetailsPDFPathFile = BEMPX_GetString( BEMPX_GetDatabaseID( "DetailsPDFPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
               if (sDetailsPDFPathFile.isEmpty())
                  BEMPX_WriteLogFile( QString( "CUAC:DetailsPDFPathFile undefined - needed for details report PDF generation" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               else
               {  QString sMsg;
                  sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                               "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                               "(once the file is closed), or \n'Abort' to abort the %s.", "PDF", sDetailsPDFPathFile.toLocal8Bit().constData(), "PDF report generation" );
                  if (!OKToWriteOrDeleteFile( sDetailsPDFPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
                     BEMPX_WriteLogFile( QString( "Unable to write CUAC details report PDF file:  %1" ).arg( sDetailsPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {
                     iRptID += 10;
                     int iPDFGenRetVal = BEMPX_GeneratePDF( sDetailsPDFPathFile.toLocal8Bit().constData(), sRptGraphicsPath.toLocal8Bit().constData(), iRptID, iCUAC_BEMProcIdx, iDataModel );
                     BEMPX_WriteLogFile( QString( "CUAC details report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sDetailsPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }  }
            }

            int iGotHere = 1;
      }  }

   }

   // call rulelist to delete any CPR_* rate components - SAC 09/20/23
   CMX_EvaluateRuleset( "CUAC_DeleteCPRRates" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );

   // free up double arrays storing initial DHW electric use, prior to JA13 HPWH adjustments - SAC 01/15/25
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
   {  if (pdaInitDHWElec[iMtr] != NULL)
         free( pdaInitDHWElec[iMtr] );
   }

   if (!sErrMsg.isEmpty() && iRetVal == 0)      // SAC 09/29/23
   {  iRetVal = 96;  // Error calculating CUAC utility bill(s)
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - %1" ).arg( sErrMsg ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   }
}


bool LoadCUACUtilityRate( CUACUtilityRate& rate, int iRateObjIdx, int iBEMProcIdx, QString& qsErrMsg )      // SAC 10/19/22
{  bool bRetVal = true;
   int iSpecVal, iErr;
   rate.sUnits            = BEMPX_GetString(  BEMPX_GetDatabaseID( "UtilityRate:Units"            ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
   rate.dMonthlyCharge    = BEMPX_GetFloat(   BEMPX_GetDatabaseID( "UtilityRate:MonthlyCharge"    ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
   rate.dMinMonthlyCharge = BEMPX_GetFloat(   BEMPX_GetDatabaseID( "UtilityRate:MinMonthlyCharge" ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
   rate.lNumSeasons       = BEMPX_GetInteger( BEMPX_GetDatabaseID( "UtilityRate:NumSeasons"       ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
   if (rate.lNumSeasons < 1 || rate.lNumSeasons > 12)
   {  bRetVal = false;
      qsErrMsg = QString( "Utility Rate NumSeasons (%1) expected to be in the range 1-12, rate object index %2" ).arg( QString::number( rate.lNumSeasons ), QString::number( iRateObjIdx ) );
   }
   for (int iMo=0; (bRetVal && iMo < 12); iMo++)
      rate.laSeasonMonthMap[iMo]   = BEMPX_GetInteger( BEMPX_GetDatabaseID( "UtilityRate:SeasonMonthMap" )+iMo,   iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx ) - 1;     // switched to range of 0-N - SAC 10/21/22
   for (int iSeas=0; (bRetVal && iSeas < rate.lNumSeasons); iSeas++)
   {  rate.saSeasonLabels[iSeas]   = BEMPX_GetString(  BEMPX_GetDatabaseID( "UtilityRate:SeasonLabels"   )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
      rate.daSeasonalUsePerDay[iSeas]   = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:SeasonalUsePerDay" )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
      rate.daaBinSeasonalCost[0][iSeas] = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:Bin1SeasonalCost"  )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
      rate.daaBinSeasonalCost[1][iSeas] = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:Bin2SeasonalCost"  )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
      rate.daaBinSeasonalCost[2][iSeas] = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:Bin3SeasonalCost"  )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
      rate.daaBinSeasonalCost[3][iSeas] = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:Bin4SeasonalCost"  )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
      rate.daaBinSeasonalCost[4][iSeas] = BEMPX_GetFloat( BEMPX_GetDatabaseID( "UtilityRate:Bin5SeasonalCost"  )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
   }
   rate.bOK = bRetVal;
   return bRetVal;
}


void CUAC_AnalysisProcessing_BatchRates( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, char* pszErrorMsg, int iErrorMsgLen,
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iDataModel /*=0*/, int iBillCalcDetails /*=-1*/,
                              int iSecurityKeyIndex, const char* pszSecurityKey, const char* pszProxyServerAddress, const char* pszProxyServerCredentials,
                              const char* pszProxyServerType, int iRptGenConnectTimeout, int iRptGenReadWriteTimeout, int iDownloadVerbose, const char* pAnalysisInvalidMsg )
{  // at this point, ruleset object is loaded w/ all hourly results read directly from CSE run(s)
   std::vector<std::string> svUtilRatesToDelete;      // SAC 09/27/23 (CUAC)
   QString sElecERN, sGasERN;
   long lBatchRateIdx=0;
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:BatchRateIdx" ), lBatchRateIdx, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   while (iRetVal == 0 && lBatchRateIdx > 0)
   {
      CMX_EvaluateRuleset( "CUACRates_Setup" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );

      BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2ElecTariffERN" ), sElecERN, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iCUAC_BEMProcIdx );
      BEMPX_GetString(  BEMPX_GetDatabaseID( "CUAC:G2GasTariffERN"  ), sGasERN , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iCUAC_BEMProcIdx );
      if (sGasERN.isEmpty())
         sGasERN = "(none)";
		BEMPX_WriteLogFile( "\n\n", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		BEMPX_WriteLogFile( "-------------------------------------------------", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		BEMPX_WriteLogFile( QString( "CUAC batch rate run #%1   elec: %2  /  gas: %3" ).arg( QString::number( lBatchRateIdx ), sElecERN, sGasERN ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

      if (iRetVal == 0)
      {  long lElecTariffGen=0, lGasTariffGen=0;
         if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:ElecTariffGen" ), lElecTariffGen, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lElecTariffGen > 1)
         {  CUAC_RateDownload( "Electric", 94, "CUAC:CPR_ElecUtilityRateRef", sProcessingPath, /*sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear,*/ bStoreBEMDetails, bSilent, bVerbose,
                               bResearchMode, pCompRuleDebugInfo, iSecurityKeyIndex, pszSecurityKey, pszProxyServerAddress, pszProxyServerCredentials, pszProxyServerType,
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout, NULL, iDownloadVerbose );
               //											94 : Error downloading CUAC electric tariff schedule
            if (iRetVal > 0)
				   ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 94 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
            else //if (iAnalysisStorage < 3)
               svUtilRatesToDelete.push_back( ((std::string) sProcessingPath.toLocal8Bit().constData()) + ((std::string) "er.json") );
         }
         if (iRetVal == 0 && !bAbort && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:GasTariffGen"  ), lGasTariffGen, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lGasTariffGen > 1)
         {  CUAC_RateDownload( "Gas", 95, "CUAC:CPR_GasUtilityRateRef", sProcessingPath, /*sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear,*/ bStoreBEMDetails, bSilent, bVerbose,
                               bResearchMode, pCompRuleDebugInfo, iSecurityKeyIndex, pszSecurityKey, pszProxyServerAddress, pszProxyServerCredentials, pszProxyServerType,
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout, NULL, iDownloadVerbose );
               //											95 : Error downloading CUAC gas tariff schedule
            if (iRetVal > 0)
				   ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 95 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
            else //if (iAnalysisStorage < 3)
               svUtilRatesToDelete.push_back( ((std::string) sProcessingPath.toLocal8Bit().constData()) + ((std::string) "gr.json") );
         }
      }

      if (iRetVal == 0)
      {
         CUAC_AnalysisProcessing( sProcessingPath, sModelPathOnly, sModelFileOnly, sRptGraphicsPath, iRulesetCodeYear,
                              bStoreBEMDetails, bSilent, bVerbose, bResearchMode, pCompRuleDebugInfo, pszErrorMsg, iErrorMsgLen,
                              bAbort, iRetVal, sErrMsg, iCUACReportID, iCUAC_BEMProcIdx, iDataModel, iBillCalcDetails /*=-1*/,
                              iDownloadVerbose, false /*bWritePDF*/, false /*bWriteCSV*/, lBatchRateIdx, pAnalysisInvalidMsg );
         for (auto& dnldRateFile : svUtilRatesToDelete)     // delete downloaded rate file(s)
         //   DeleteFile( dnldRateFile.c_str() );
         {  std::string sNewName = dnldRateFile;
            sNewName += "-";  sNewName += std::to_string( lBatchRateIdx );
            rename( dnldRateFile.c_str(), sNewName.c_str() );
         }
      }

      if (iRetVal == 0)
      {  CMX_EvaluateRuleset( "CUACRates_Final" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );
      //{  CMX_EvaluateRuleset( "CUACRates_Final" , TRUE, FALSE /*bTagDataAsUserDefined*/, TRUE, NULL, NULL, NULL, pCompRuleDebugInfo );
         BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:BatchRateIdx" ), lBatchRateIdx, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
      }
   }
}


////////////////////////////////////////////////////////////////////////////////

int CUAC_WriteCSVSummary( QFile& csvFile, const char* pszProjectPathFileName, const char* pszSimWeatherPath, int iDataModel /*=0*/ )  // SAC 12/11/23   // SAC 01/22/25
{	int iRetVal = 0;
   // iDataModel: 0 MFam / 1 SFam
	QString sModelPathFile		= pszProjectPathFileName;
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

	QString sSimWeatherPath		= pszSimWeatherPath;
	RelativeToCompletePath_IfNeeded( sSimWeatherPath  );

	double dTimeOverall = 0;
		QString sRunTitle, sWthrStn, sAnnWthrFile, sTimeStamp, sLogMsg, sBEMErr;
	//	QString sAnalType, sPropSimSummary, sStdSimSummary, sAppVer, sCmpMgrVer, sEPlusVer, sOSVer;
	//	double dRptTotArea, dRptCndArea;   // SAC 2/19/17
		int iCID_Proj      = GetBEMBaseCompID( sBEMErr, "Proj"      );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"       ), sRunTitle );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherStation" ), sWthrStn  );

   if (iDataModel == 1)    // SFam                 // SAC 01/22/25
   {
      long lRunDate;
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate ) && lRunDate > 0)
	   {	QDateTime locTime = QDateTime::currentDateTime();
			sTimeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");
      }
      else
         BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunDateISO" ), sTimeStamp );
   }
   else     // MFam
   {
   	BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:AnalysisDuration" ), dTimeOverall );
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"    ), sAppVer    );
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), sCmpMgrVer );
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Ruleset"            ), sRuleVer   );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile"  ), sAnnWthrFile );
	//	BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotFlrArea"      ), dRptTotArea );
	//	BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), dRptCndArea );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunDateLog"      ), sTimeStamp );		// SAC 11/04/19
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:OpenStudioVersion" ), sOSVer );		// SAC 11/04/19
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EngyPlusVersion" ), sEPlusVer );		// SAC 11/04/19
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CSEVersion"      ), sCSEVersion );	// SAC 11/04/19
   }

   int iCID_CUAC = GetBEMBaseCompID( sBEMErr, "CUAC" );
   long lDBID_CUAC_AffordableUnitsByBedrms    = BEMPX_GetDatabaseID( "AffordableUnitsByBedrms",    iCID_CUAC );
   long lDBID_CUAC_NumAffordableDwellingUnits = BEMPX_GetDatabaseID( "NumAffordableDwellingUnits", iCID_CUAC );
   long lDBID_CUAC_CUACResultsRef = BEMPX_GetDatabaseID( "CUACResultsRef", iCID_CUAC );
   long lDBID_CUAC_UnitTypeLabels = BEMPX_GetDatabaseID( "UnitTypeLabels", iCID_CUAC );
   long lAffordableUnitsByBedrms[8], lAffordableUnitsByBedrmsSum=0, lNumAffordableDwellingUnits=0, lCUACResNumUnits[8];
   long lDBID_CUACResults_AvgCosts[5] = { BEMPX_GetDatabaseID( "CUACResults:ElecCosts[2]"     ), BEMPX_GetDatabaseID( "CUACResults:GasCosts[2]" ), BEMPX_GetDatabaseID( "CUACResults:WaterCosts[2]" ),
                                          BEMPX_GetDatabaseID( "CUACResults:TrashMonthlyCost" ), BEMPX_GetDatabaseID( "CUACResults:TotCosts[2]" ) };
   double dCost, dUnitWghtAvgCosts[5] = {0.0,0.0,0.0,0.0,0.0};
   int iCUACResultsIdx[8];
   QString sUnitTypeLabels[8];
   int iMostCommonUnitNum = 0, iMostCommonUnitIdx = 0;     // SFam - SAC 01/22/25
   int iSpecVal, iErr, iCost, iResIdx=0;
   for (int i=0; i<8; i++)
   {  if (BEMPX_GetInteger( lDBID_CUAC_AffordableUnitsByBedrms+i, lAffordableUnitsByBedrms[i], 0, -1 ) && lAffordableUnitsByBedrms[i] > 0)
      {  lAffordableUnitsByBedrmsSum += lAffordableUnitsByBedrms[i];
         if (lAffordableUnitsByBedrms[i] > iMostCommonUnitNum)
         {  iMostCommonUnitNum = lAffordableUnitsByBedrms[i];
            iMostCommonUnitIdx = i;
         }
         BEMObject* pResObj = BEMPX_GetObjectPtr( lDBID_CUAC_CUACResultsRef+i, iSpecVal, iErr, 0 );   assert( pResObj );
         if (pResObj)
         {  iCUACResultsIdx[ iResIdx] = BEMPX_GetObjectIndex( pResObj->getClass(), pResObj );         assert( iCUACResultsIdx[iResIdx] >= 0 );
            lCUACResNumUnits[iResIdx] = lAffordableUnitsByBedrms[i];
            BEMPX_GetString( lDBID_CUAC_UnitTypeLabels+i, sUnitTypeLabels[iResIdx] );
            for (iCost=0; iCost<5; iCost++)
            {  if (BEMPX_GetFloat( lDBID_CUACResults_AvgCosts[iCost], dCost, 0, -1, iCUACResultsIdx[iResIdx] ))
                  dUnitWghtAvgCosts[iCost] += (dCost * lCUACResNumUnits[iResIdx]);
            }
            iResIdx++;
         }
      }
      else
         lAffordableUnitsByBedrms[i] = 0;
   }
   BEMPX_GetInteger( lDBID_CUAC_NumAffordableDwellingUnits, lNumAffordableDwellingUnits, 0, -1 );
   assert( lNumAffordableDwellingUnits == lAffordableUnitsByBedrmsSum );
   if (lNumAffordableDwellingUnits > 0)
   {  for (iCost=0; iCost<5; iCost++)
         dUnitWghtAvgCosts[iCost] /= lNumAffordableDwellingUnits;
   }

   QString sElecUtil, sElecTerr, sElecTariff, sGasUtil, sGasTerr, sGasTariff;
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), sElecUtil   );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), sElecTerr   );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), sElecTariff );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"      ), sGasUtil    );
   if (!sGasUtil.isEmpty() && !sGasUtil.compare( "no gas service" ))
   {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTerritory" ), sGasTerr   );
      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTariff"    ), sGasTariff );
   }

   QString sResults;
   if (iDataModel == 1)    // SFam                 // SAC 01/22/25
      sResults = QString::asprintf( "%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%s,%.2f,%.2f,%.2f,%.2f,%.2f,%ld\n", 
               sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), 
               sElecUtil.toLocal8Bit().constData(), sElecTerr.toLocal8Bit().constData(), sElecTariff.toLocal8Bit().constData(), sGasUtil.toLocal8Bit().constData(), sGasTerr.toLocal8Bit().constData(), sGasTariff.toLocal8Bit().constData(),
               pszCUACCSVUnitTypeLabels[iMostCommonUnitIdx], dUnitWghtAvgCosts[0], dUnitWghtAvgCosts[1], dUnitWghtAvgCosts[2], dUnitWghtAvgCosts[3], dUnitWghtAvgCosts[4], lNumAffordableDwellingUnits );
               // sUnitTypeLabels[iMostCommonUnitIdx].toLocal8Bit().constData(), dUnitWghtAvgCosts[0], dUnitWghtAvgCosts[1], dUnitWghtAvgCosts[2], dUnitWghtAvgCosts[3], dUnitWghtAvgCosts[4], lNumAffordableDwellingUnits );
   else  // MFam
      sResults = QString::asprintf( "%s,\"%s\",\"%s\",\"%s\",%d:%.2d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%.2f,%.2f,%.2f,%.2f,%.2f,%ld\n", 
               sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)),
               sElecUtil.toLocal8Bit().constData(), sElecTerr.toLocal8Bit().constData(), sElecTariff.toLocal8Bit().constData(), sGasUtil.toLocal8Bit().constData(), sGasTerr.toLocal8Bit().constData(), sGasTariff.toLocal8Bit().constData(),
               dUnitWghtAvgCosts[0], dUnitWghtAvgCosts[1], dUnitWghtAvgCosts[2], dUnitWghtAvgCosts[3], dUnitWghtAvgCosts[4], lNumAffordableDwellingUnits );
   csvFile.write( sResults.toLocal8Bit().constData() );

   return iRetVal;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CUACToolMiner integration -

int CMX_GetCUACDBProjectList( std::string sCUACPathFilename, std::vector<std::string>& vsProjects,
                              std::vector<int>& viProjectIDs, bool bLogCUACToolMiner )
{
   //auto res = getProjectList( "C:/CUAC/CUACTool-Rev2-0-0.accdb", vsProjects);

   //auto res = getProjectList( sCUACPathFilename, vsProjects);

   std::string sCUACLogPathFilename;      // debug logging - SAC 04/11/24
   if (bLogCUACToolMiner)
   {  sCUACLogPathFilename = sCUACPathFilename;
      size_t iLastDot = sCUACLogPathFilename.find_last_of('.');
      if (iLastDot > 0)
         sCUACLogPathFilename.resize(iLastDot);
      sCUACLogPathFilename += "-log.txt";
   }

   CUACToolMiner db(sCUACLogPathFilename);    // revised to return both Project strings AND IDs - SAC 09/18/23
   int res = db.open_connection(sCUACPathFilename);
   if (res == CUACToolMiner::no_error)
   {
      res = db.get_column_values("tProjects", "Project Name", vsProjects);
      if (res == CUACToolMiner::no_error)
         res = db.get_column_values("tProjects", "ProjectID", viProjectIDs);
   }

   if (res != CUACToolMiner::no_error)
      std::cout << "Error: " << res << std::endl;
   else {
      std::cout << "Database contains " << vsProjects.size() << " project(s)." << std::endl;
      for (auto& project : vsProjects)
         std::cout << project << std::endl;
   }
   std::cout << std::endl;
   return res;
}

int CMX_ExportCUACDBProjectTables( std::string sCUACPathFilename, std::string sOutputPath,
                        const std::string& sProject_name, bool bLogCUACToolMiner )  //, const std::vector<std::string>& sTable_names)
{
   std::string sCUACLogPathFilename;      // debug logging - SAC 04/11/24
   if (bLogCUACToolMiner)
   {  sCUACLogPathFilename = sCUACPathFilename;
      size_t iLastDot = sCUACLogPathFilename.find_last_of('.');
      if (iLastDot > 0)
         sCUACLogPathFilename.resize(iLastDot);
      sCUACLogPathFilename += "-log.txt";
   }

   CUACToolMiner db(sCUACLogPathFilename);    // revised to return both Project strings AND IDs - SAC 09/18/23
   int res = db.open_connection(sCUACPathFilename);
   if (res == CUACToolMiner::no_error)
   {
      std::vector<std::string> sTablesNames(  {"tProjects",
                                                  "tVersion",
                                                  "tInputApt",
                                                  "tInputCECPV",
                                                  "qSummaryCecpvTotalsByApt",
                                                  "qSummaryAllElectricEndUsesByApt",
                                                  "qSummaryAllGasEndUsesByApt"} );
      res = exportTables( db, sOutputPath, sTablesNames );
   }

//   if (res != CUACToolMiner::no_error)
//      std::cout << "Error: " << res << std::endl;
//   else {
//      std::cout << "Database contains " << vsProjects.size() << " project(s)." << std::endl;
//      for (auto& project : vsProjects)
//         std::cout << project << std::endl;
//   }
//   std::cout << std::endl;
   return res;

//     int res = CUACToolMiner::no_error;
//     std::error_code ec;
// 
// //    // Create output folder
// //    try {
// //        std::filesystem::create_directory(data_dir + "/output");
// //    }
// //    catch (std::filesystem::filesystem_error const& ec) {
// //        std::cout << "Error creating/finding directory: " << ec.path1() << std::endl;
// //        res = CUACToolMiner::fileio_error;
// //    }
// //    if (res != CUACToolMiner::no_error)
// //        return res;
// //
// //    // Create project folder
// //    //auto sProj_data_path = data_dir + "/output/" + sProject_name;
// //    auto sProj_data_path = sOutputPath + "/" + sProject_name;
// //    try {
// //        std::filesystem::create_directory(sProj_data_path);
// //    }
// //    catch (std::filesystem::filesystem_error const& ec) {
// //        std::cout << "Error creating/finding directory: " << ec.path1() << std::endl;
// //        res = CUACToolMiner::fileio_error;
// //    }
// //    if (res != CUACToolMiner::no_error)
// //        return res;
// 
//       std::vector<std::string> sTable_names;
//     res = getProjectData( sCUACPathFilename, sProject_name, sOutputPath );  // sProj_data_path);
//     if (res != CUACToolMiner::no_error)
//         std::cout << "Error: " << res << std::endl << std::endl;
//     else
//         std::cout << "Project " << sProject_name << " data written to " << sOutputPath  // sProj_data_path
//                   << std::endl
//                   << std::endl;
// 
//     return res;
// 
// // int export_project_data(const std::string& sProject_name,
// //                         const std::vector<std::string>& sTable_names)
// // {
// //     std::cout << std::endl;
// // 
// //     std::string sProj_data_path;
// //     int res = get_project_data_path(sProject_name, sProj_data_path);
// //     if (res != CUACToolMiner::no_error)
// //         return res;
// // 
// //     res = getProjectData(sMainDBPathFilename, sProject_name, sProj_data_path);
// //     if (res != CUACToolMiner::no_error)
// //         std::cout << "Error: " << res << std::endl << std::endl;
// //     else
// //         std::cout << "Project " << sProject_name << " data written to " << sProj_data_path
// //                   << std::endl;
// // 
// //     return res;
}

// int CMX_ExportCUACDBSummaryTable( std::string sCUACPathFilename, std::string sOutputPath,
//                         const std::string& sProject_name, bool bIsElec )
//                             //const std::vector<std::string>& sTable_names,
//                             //const std::string& sCombined_table_name)
// {
//     int res = CUACToolMiner::no_error;
// 
// 
//     std::vector<std::string> sElecTable_names({"qSummaryLightingTotalsByApt",
//                                            "qSummaryHeatingTotalsByApt",
//                                            "qSummaryDHWTotalsByApt",
//                                            "qSummaryCookingTotalsByApt",
//                                            "qSummaryCoolingTotalsByApt",
//                                            "qSummaryRefrigeratorTotalsByApt",
//                                            "qSummaryDishwasherTotalsByApt",
//                                            "qSummaryWasherTotalsByApt",
//                                            "qSummaryDryerTotalsByApt",
//                                            "qSummaryPlugLoadsTotalsByApt"});
//     std::vector<std::string> sGasTable_names({"qSummaryHeatingTotalsByAptGas",
//                                            "qSummaryDHWTotalsByAptGas",
//                                            "qSummaryCookingTotalsByAptGas",
//                                            "qSummaryDryerTotalsByAptGas"});
//    std::string sCombined_table_name = (bIsElec ? "qSummaryAllElectricEndUsesByApt" : "qSummaryAllGasEndUsesByApt");
//    // return summarize_common_tables(sProject_name, sTable_names, "qSummaryAllElectricEndUsesByApt");
// 
// 
//     CUACToolMiner db;
//     res = db.open_connection(sCUACPathFilename);
//     if (res != CUACToolMiner::no_error)
//         return res;
// 
// //    // Create output folder
// //    try {
// //        std::filesystem::create_directory(data_dir + "/output");
// //    }
// //    catch (std::filesystem::filesystem_error const& ec) {
// //        std::cout << "Error creating/finding directory: " << ec.path1() << std::endl;
// //        res = CUACToolMiner::fileio_error;
// //        return res;
// //    }
// //
// //    // Create project folder
// //    auto sProj_data_path = data_dir + "/output/" + sProject_name;
// //    try {
// //        std::filesystem::create_directory(sProj_data_path);
// //    }
// //    catch (std::filesystem::filesystem_error const& ec) {
// //        std::cout << "Error creating/finding directory: " << ec.path1() << std::endl;
// //        res = CUACToolMiner::fileio_error;
// //        return res;
// //    }
// 
//     CUACToolMiner::Project project;
//     if (bIsElec)
//       res = db.get_project(sProject_name, sElecTable_names, project);
//     else
//       res = db.get_project(sProject_name, sGasTable_names , project);
// 
//     if (res != CUACToolMiner::no_error)
//         return res;
// 
//     CUACToolMiner::Table combined_table;
//     combined_table.first = sCombined_table_name;
//     bool first(true);
//     for (auto& table : project.second) {
//         auto& combined_cols = combined_table.second;
//         auto& cols = table.second;
//         if (first)
//             combined_cols = cols;
//         else {
//             auto& combined_col = combined_cols.begin();
//             for (auto& col : cols) {
//                 combined_col->second.insert(
//                     combined_col->second.end(), col.second.begin(), col.second.end());
//                 ++combined_col;
//             }
//         }
//         first = false;
//     }
//     std::string sProj_data_path_filename = sOutputPath + "/" + combined_table.first + ".csv";
//     res = db.export_table(combined_table, sProj_data_path_filename);
// 
//     if (res != CUACToolMiner::no_error)
//         std::cout << "Error writing data" << std::endl;
//     else
//         std::cout << "Project " << sProject_name << " data written to file "
//                   << sProj_data_path_filename << std::endl;
//     std::cout << std::endl;
//     return res;
// }


std::string CUACToolMinerErrorMsg( int err )    // SAC 09/15/23
{  std::string sErrMsg;
   switch (err)
   {  case CUACToolMiner::data_error     :  sErrMsg = "data error";              break;
      case CUACToolMiner::odbc_error     :  sErrMsg = "ODBC (database) error";   break;
      case CUACToolMiner::fileio_error   :  sErrMsg = "file I/O error";          break;
      case CUACToolMiner::runtime_error  :  sErrMsg = "runtime error";           break;
   }
   return sErrMsg;
}

// return values: 
//    0 - OK
//    1-20 - CUACToolMiner error code
//    21 : ruleset database (BEMBase) lacking CUAC, OldCUAC and/or OldCUACApt object definitions
//    22 : error creating CUAC object
//    23 : error creating OldCUAC object
//    24 : error creating OldCUACApt object
int CMX_PortOldCUACToCBECC( std::string sCUACPathFilename, long projectID, std::string sProjectName,     // SAC 09/15/23
                              std::string& sErrMsg, bool bLogCUACToolMiner )
{  int iRetVal = 0;
   const std::vector<std::string> tables_to_export(
      {"tProjects", "tVersion", "tInputApt", "tInputCECPV", "tVNM"});

   int iCID_CUAC        = BEMPX_GetDBComponentID( "CUAC" );          assert( iCID_CUAC > 0 );
   int iCID_OldCUAC     = BEMPX_GetDBComponentID( "OldCUAC" );       assert( iCID_OldCUAC > 0 );
   int iCID_OldCUACApt  = BEMPX_GetDBComponentID( "OldCUACApt" );    assert( iCID_OldCUACApt > 0 );
   // long lDBID_CUAC_ProjectID         = BEMPX_GetDatabaseID( "ProjectID",          iCID_CUAC );

   bool bVerboseLogging = false;     // SAC 10/11/23

   std::string sVal;  long lVal, lGasUtilID;  double dVal;
   if (iCID_CUAC < 1 || iCID_OldCUAC < 1 || iCID_OldCUACApt < 1)
   {  iRetVal = 21;
      sErrMsg = "Ruleset database (BEMBase) lacking CUAC and/or OldCUAC object definitions";
   }
   else if (BEMPX_GetNumObjects( iCID_CUAC ) < 1)  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
   {  BEMObject* pCUACObj = BEMPX_CreateObject( iCID_CUAC, sProjectName.c_str() );
      if (pCUACObj == NULL)
      {  iRetVal = 22;
         sErrMsg = "Error creating primary CUAC object";
   }  }
   if (iRetVal == 0 && BEMPX_GetNumObjects( iCID_OldCUAC ) < 1)
   {  sVal = sProjectName + "-import";
      BEMObject* pCUACObj = BEMPX_CreateObject( iCID_OldCUAC, sVal.c_str() );
      if (pCUACObj == NULL)
      {  iRetVal = 23;
         sErrMsg = "Error creating OldCUAC object";
   }  }

   std::string sCUACLogPathFilename;      // debug logging - SAC 04/11/24
   if (bLogCUACToolMiner)
   {  sCUACLogPathFilename = sCUACPathFilename;
      size_t iLastDot = sCUACLogPathFilename.find_last_of('.');
      if (iLastDot > 0)
         sCUACLogPathFilename.resize(iLastDot);
      sCUACLogPathFilename += "-log.txt";
   }

   CUACToolMiner db(sCUACLogPathFilename);
   iRetVal = db.open_connection(sCUACPathFilename);
   if (iRetVal == 0)
   {  // Get project ID
      //long projectID(-1);
      //iRetVal = db.get_project_ID(sProjectName, projectID);
      //if (iRetVal != 0)
      //   sErrMsg = "Error retrieving CUAC ProjectID from Access database table: " + CUACToolMinerErrorMsg( iRetVal );
      //else
      if (TRUE)
      {
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjectID", iCID_OldCUAC ), BEMP_Int, (void*) &projectID );
         double dProjID = (double) projectID;
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjectID", iCID_CUAC    ), BEMP_Flt, (void*) &dProjID );     // added storage of numeric CUAC:ProjectID - SAC 01/10/24

         std::string project_cond("ProjectID=" + std::to_string(projectID));
         int iLocRes = db.get_key_value("tProjects", "ProjectID", "Address", projectID, sVal);     // "Project Name", ... , sProjectName -->> "ProjectID", ... , projectID - SAC 09/18/23
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:StAddress" ), BEMP_Str, (void*) sVal.c_str() );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "City", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:City" ), BEMP_Str, (void*) sVal.c_str() );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "Zipcode", projectID, lVal);
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ZipCode" ), BEMP_Int, (void*) &lVal );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "ElectricUtilityID", projectID, lVal);     // SAC 09/16/23
         if (iLocRes == 0)
         {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OldElecUtilityID", iCID_CUAC ), BEMP_Int, (void*) &lVal );
            CMX_EvaluateRuleset( "CUAC_MapOldCUACElecUtility" , FALSE /*bVerbose*/, FALSE /*bTagDataAsUserDefined*/, FALSE /*bVerbose*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );
            iLocRes = db.get_key_value("tProjects", "ProjectID", "ElectricTerritory", projectID, sVal);
               if (bVerboseLogging)
                  BEMPX_WriteLogFile( QString( "ElecTerritory:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            if (iLocRes == 0 && sVal.length() > 0)
            {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ElecTerritory", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
               iLocRes = db.get_key_value("tProjects", "ProjectID", "TariffType", projectID, sVal);
                  if (bVerboseLogging)
                     BEMPX_WriteLogFile( QString( "ElecTariff:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               if (iLocRes == 0 && sVal.length() > 0)
               {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ElecTariff", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
                  CMX_EvaluateRuleset( "CUAC_PerformGen2UtilityRateMapping_Electric" , FALSE /*bVerbose*/, FALSE /*bTagDataAsUserDefined*/, FALSE /*bVerbose*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );
         }  }  }

         iLocRes = db.get_key_value("tProjects", "ProjectID", "GasUtilityID", projectID, lGasUtilID); 
         if (iLocRes == 0)
         {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OldGasUtilityID", iCID_CUAC ), BEMP_Int, (void*) &lGasUtilID );
            CMX_EvaluateRuleset( "CUAC_MapOldCUACGasUtility" , FALSE /*bVerbose*/, FALSE /*bTagDataAsUserDefined*/, FALSE /*bVerbose*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );
            if (lGasUtilID > 0 && lGasUtilID != 6)  // if valid gas utility (not 6 => 'no gas service')
            {  iLocRes = db.get_key_value("tProjects", "ProjectID", "GasTerritory", projectID, sVal);
                  if (bVerboseLogging)
                     BEMPX_WriteLogFile( QString( "GasTerritory:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               if (iLocRes == 0 && sVal.length() > 0)
               {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "GasTerritory", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
                  iLocRes = db.get_key_value("tProjects", "ProjectID", "TariffType", projectID, sVal);
                     if (bVerboseLogging)
                        BEMPX_WriteLogFile( QString( "GasTariff:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  if (iLocRes == 0 && sVal.length() > 0)
                  {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "GasTariff" , iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
                     CMX_EvaluateRuleset( "CUAC_PerformGen2UtilityRateMapping_Gas" , FALSE /*bVerbose*/, FALSE /*bTagDataAsUserDefined*/, FALSE /*bVerbose*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );
         }  }  }  }

         // ??? TrashTariff & WaterTariff ???
         // iLocRes = db.get_key_value("tProjects", "ProjectID", "TrashTariff", projectID, lVal);
         // if (iLocRes == 0)
         //    BEMPX_WriteLogFile( QString( "TrashTariff:  %1" ).arg( QString::number( lVal ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         // iLocRes = db.get_key_value("tProjects", "ProjectID", "WaterTariff", projectID, lVal);
         // if (iLocRes == 0)
         //    BEMPX_WriteLogFile( QString( "WaterTariff:  %1" ).arg( QString::number( lVal ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "AffordableHousing", projectID, lVal);     // SAC 09/16/23
         if (iLocRes == 0)
         {  if (lVal)
               sVal = "Affordable Housing";
            else
               sVal = "unknown";
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "UnitType", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         }

         iLocRes = db.get_key_value("tProjects", "ProjectID", "OwnerName", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OwnerName", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "OwnerAddress", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OwnerAddress", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "OwnerCity", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OwnerCity", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "OwnerState", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OwnerState", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "OwnerZip", projectID, lVal);
         if (iLocRes == 0 && lVal > 0)
         {  sVal = std::to_string( lVal );
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OwnerZIPCode", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         }

         iLocRes = db.get_key_value("tProjects", "ProjectID", "ContactName", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ContactName", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "ContactPhone", projectID, dVal); 
         if (iLocRes == 0 && dVal > 0)
         {  sVal = std::to_string( dVal );
            size_t posDot = sVal.find(".");
            if (posDot != std::string::npos)
               sVal.resize( posDot );  // trim trailing decimal .000...
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ContactPhone", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         }
         iLocRes = db.get_key_value("tProjects", "ProjectID", "ContactEmail", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ContactEMail", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "WaterHeatingFuel", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "WaterHeatingFuel", iCID_OldCUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "HeatingFuel",      projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "HeatingFuel",      iCID_OldCUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "CookingFuel",      projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CookingFuel",      iCID_OldCUAC ), BEMP_Str, (void*) sVal.c_str() );

         // PropaneRateSummer
         // PropaneRateWinter

         iLocRes = db.get_key_value("tProjects", "ProjectID", "EnergyStarPlugLoad", projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "EnergyStarPlugLoad", iCID_OldCUAC ), BEMP_Int, (void*) &lVal );

         // LightingEfficacy

         iLocRes = db.get_key_value("tProjects", "ProjectID", "WaterRateType", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
         {  if (sVal.find( "Usage" ) != std::string::npos)
               lVal = 2;
            else if (sVal.find( "monthly" ) != std::string::npos)
               lVal = 1;
            else
               lVal = 0;
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "WaterRateType", iCID_CUAC ), BEMP_Int, (void*) &lVal );
         }
         iLocRes = db.get_key_value("tProjects", "ProjectID", "WaterFlatMonthlyRate", projectID, dVal); 
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "WaterMonthlyCost",     iCID_CUAC ), BEMP_Flt, (void*) &dVal );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "WaterUsageRate",       projectID, dVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "WaterVolumeCost",      iCID_CUAC ), BEMP_Flt, (void*) &dVal );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "TrashRateType", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
         {  if (sVal.find( "monthly" ) != std::string::npos)
               lVal = 1;
            else
               lVal = 0;
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "TrashRateType", iCID_CUAC ), BEMP_Int, (void*) &lVal );
         }
         iLocRes = db.get_key_value("tProjects", "ProjectID", "TrashFlatMonthlyRate", projectID, dVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "TrashMonthlyCost",     iCID_CUAC ), BEMP_Flt, (void*) &dVal );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "CommonLaundryFacility",   projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CommonLaundryFacility",   iCID_OldCUAC ), BEMP_Int, (void*) &lVal );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "CommonWashers",           projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CommonWashers",           iCID_OldCUAC ), BEMP_Int, (void*) &lVal );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "CommonWashersEnergyStar", projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CommonWashersEnergyStar", iCID_OldCUAC ), BEMP_Int, (void*) &lVal );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "CommonDryers",            projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CommonDryers",            iCID_OldCUAC ), BEMP_Int, (void*) &lVal );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "CommonDryersEnergyStar",  projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "CommonDryersEnergyStar",  iCID_OldCUAC ), BEMP_Int, (void*) &lVal );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "APN", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "APN", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
         iLocRes = db.get_key_value("tProjects", "ProjectID", "OtherProjectIdentifier", projectID, sVal);
         if (iLocRes == 0 && sVal.length() > 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "OtherProjectID",         iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );

         iLocRes = db.get_key_value("tProjects", "ProjectID", "PrintFinal",            projectID, lVal); 
         if (iLocRes == 0)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID(               "PrintFinal",            iCID_OldCUAC ), BEMP_Int, (void*) &lVal );


         int iAptTypeID, iAptTypeFoundIdx=0;
         int iAptObjIdx[7], iaNumBdrms[7];
         std::string sAptTypes[7], saNumBdrms[7], sAptType, sNumBdrms;
         for (iAptTypeID=1; (iRetVal==0 && iAptTypeID <= 7); iAptTypeID++)    // studio - 5-bdrm
         {  std::string aptTypeID_cond("AptTypeID=" + std::to_string(iAptTypeID));
            std::string sCond_ProjAndAptTypeID = project_cond + " AND " + aptTypeID_cond;
            long lAptID=0, lNumUnits=0;
            if (db.get_column_value( "tInputApt", "AptID", lAptID,    sCond_ProjAndAptTypeID ) == 0 && lAptID > 0 &&
                db.get_column_value( "tInputApt", "Units", lNumUnits, sCond_ProjAndAptTypeID ) == 0 && lNumUnits > 0 )
            {  switch(iAptTypeID)
               {  case  2 :  sAptType = "One Bedroom";      sNumBdrms = "One";      break;
                  case  3 :  sAptType = "Two Bedroom";      sNumBdrms = "Two";      break;
                  case  4 :  sAptType = "Three Bedroom";    sNumBdrms = "Three";    break;
                  case  5 :  sAptType = "Four Bedroom";     sNumBdrms = "Four";     break;
                  case  6 :  sAptType = "Five Bedroom";     sNumBdrms = "Five";     break;
                  case  7 :  sAptType = "Six Bedroom";      sNumBdrms = "Six";      break;
                  default :  sAptType = "Studio";           sNumBdrms = "Studio";   break;
               }
               sVal = sAptType + " oldData";
               BEMObject* pCUACObj = BEMPX_CreateObject( iCID_OldCUACApt, sVal.c_str() );
               if (pCUACObj == NULL)
               {  iRetVal = 24;
                  sErrMsg = "Error creating OldCUACApt object: " + sVal;
               }
               else
               {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AptDataRef[1]", iCID_OldCUAC )+iAptTypeID-1, BEMP_Obj, (void*) pCUACObj );
                  iAptObjIdx[iAptTypeFoundIdx] = BEMPX_GetObjectIndex( pCUACObj->getClass(), pCUACObj );      assert( iAptObjIdx[iAptTypeFoundIdx] >= 0 );
                  sAptTypes[ iAptTypeFoundIdx] = sAptType;
                  iaNumBdrms[iAptTypeFoundIdx] = iAptTypeID-1;
                  saNumBdrms[iAptTypeFoundIdx] = sNumBdrms;

                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AptID",              iCID_OldCUACApt ), BEMP_Int, (void*) &lAptID   , BEMO_User, iAptObjIdx[iAptTypeFoundIdx] );
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumAffordableUnits", iCID_OldCUACApt ), BEMP_Int, (void*) &lNumUnits, BEMO_User, iAptObjIdx[iAptTypeFoundIdx] );
                  long lNumBdrms = iAptTypeID-1;
                  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumBedrooms",        iCID_OldCUACApt ), BEMP_Int, (void*) &lNumBdrms, BEMO_User, iAptObjIdx[iAptTypeFoundIdx] );    // SAC 09/18/23

                  iLocRes = db.get_column_value( "tInputApt", "UnitsMarketRate", lVal, sCond_ProjAndAptTypeID ); 
                  if (iLocRes == 0)
                     BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumMarketRateUnits", iCID_OldCUACApt ), BEMP_Int, (void*) &lVal );

//                  char pszOldCUACVar[32];  int iPropIdx = -1;     // retrieval of monthly use inputs from Apt table - SAC 09/17/23
//                  const char* pszOldCUACFmt[] = { "ACM_Heating_KWH%d", "ACM_Heating_KBTU%d", "ACM_DHW_KWH%d",
//                                                  "ACM_DHW_KBTU%d",    "ACM_Cooling_KWH%d"  };
//                  long laDBID_BEMBase[] = { BEMPX_GetDatabaseID( "ACMHeatingElec[1]" , iCID_OldCUACApt ),
//                                            BEMPX_GetDatabaseID( "ACMHeatingGas[1]"  , iCID_OldCUACApt ),
//                                            BEMPX_GetDatabaseID( "ACMWaterHtgElec[1]", iCID_OldCUACApt ),
//                                            BEMPX_GetDatabaseID( "ACMWaterHtgGas[1]" , iCID_OldCUACApt ),
//                                            BEMPX_GetDatabaseID( "ACMCoolingElec[1]" , iCID_OldCUACApt ), 0 };
//                  for (int iMo=1; (iRetVal==0 && iMo <= 12); iMo++)
//                  {  iPropIdx = -1;
//                     while (laDBID_BEMBase[++iPropIdx] > 0)
//                     {  snprintf( pszOldCUACVar, sizeof(pszOldCUACVar), pszOldCUACFmt[iPropIdx], iMo );
//                        iLocRes = db.get_column_value( "tInputApt", pszOldCUACVar, dVal, sCond_ProjAndAptTypeID ); 
//                        if (iLocRes == 0)
//                           BEMPX_SetBEMData( laDBID_BEMBase[iPropIdx]+iMo-1, BEMP_Flt, (void*) &dVal );
//                  }  }

                  iAptTypeFoundIdx++;
            }  }
         }  // end of loop over every possible Apt type


         if (iRetVal==0 && iAptTypeFoundIdx > 0)
         {  // setup ELECTRIC Summary table
         //   double dPctCommLoad = 0.0;
         //   char pszMoPVCUACVar[32];
         //   long lDBID_PVGen = BEMPX_GetDatabaseID( "PVGeneration[1]", iCID_OldCUACApt );
         //   long laPrevPVIDs[7] = {0,0,0,0,0,0,0};
         //   long lPVID;
         //   std::string sPVCond = project_cond;
         //   for (int iApt=0; (iRetVal==0 && iApt < iAptTypeFoundIdx); iApt++)
         //      // no known link from Proj/Apt IDs to PV IDs
         //      if (db.get_column_value( "tInputCECPV", "PVID", lPVID, sPVCond ) == 0 && lPVID > 0)
         //      {
         //         iLocRes = db.get_column_value( "tInputCECPV", "PVSystemName", sVal, sPVCond );
         //         // ??? whether or not to require presence of # bedrooms included in PVSystemName ???
         //         // if (sVal.find( saNumBdrms[iApt] )!=std::string::npos ||
         //         //     sVal.find( std::to_string(iaNumBdrms[iApt]) )!=std::string::npos)
         //         // {
         //         //    
         //         // }
         //         iLocRes = db.get_column_value( "tInputCECPV", "PercentForCommonLoad", dPctCommLoad, sPVCond );   assert( dPctCommLoad >= 0 && dPctCommLoad < 100 );
         //         if (dPctCommLoad >= 0 && dPctCommLoad < 100)
         //         {
         //            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PVSystemName", iCID_OldCUACApt ), BEMP_Str, (void*) sVal.c_str(), BEMO_User, iAptObjIdx[iApt] );
         //            for (int iMo=1; (iRetVal==0 && iMo <= 12); iMo++)
         //            {  snprintf( pszMoPVCUACVar, sizeof(pszMoPVCUACVar), "KWH%d", iMo );
         //               iLocRes = db.get_column_value( "tInputCECPV", pszMoPVCUACVar, dVal, sPVCond );      dVal *= -1.0;   // flip to negative values - SAC 09/18/23
         //               if (iLocRes == 0)
         //                  BEMPX_SetBEMData( lDBID_PVGen+iMo-1, BEMP_Flt, (void*) &dVal, BEMO_User, iAptObjIdx[iApt] );
         //         }  }
         //         //sPVCond += " AND PVID!=" + std::to_string(lPVID);
         //         sPVCond += " AND Not PVID=" + std::to_string(lPVID);
         //      }
         //      int CUACToolMiner::get_summary_Cecpv_project_table(const int projectID_in, Table& table)

            CUACToolMiner::Tables tables;    // SAC 10/11/23
            std::vector<std::string> sPVTable_name({"qSummaryCecpvTotalsByApt"}); 
            iLocRes = db.get_project_tables( projectID, sPVTable_name, tables );
            auto& table = tables[0];
            auto& cols = table.second;
            double daaPVByAptAndMo[8][12] = { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                                              { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };
            char num[50];
            long lEnduseDBID = BEMPX_GetDatabaseID( "PVGeneration", iCID_OldCUACApt );
            bool done(false);
            int iColIdx=0;
            std::size_t iRow(0);
            while (!done) 
            {  done = true;
               iColIdx = 0;
               int iThisAptObjIdx = -1;
               double dResFrac=1.0, dUnitWeight=0.0;
               std::string sTemp;
               for (auto& col : cols) 
               {  auto &col_vals = col.second;
                  if (iRow < col_vals.size())
                  {  switch (iColIdx)
                     {  case  0 :   {  if (bVerboseLogging)
                                          sTemp = "AptType " + col_vals[iRow].as_string();
                                       assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                       for (int iApt=0; (iThisAptObjIdx < 0 && iApt < iAptTypeFoundIdx); iApt++)
                                       {  sTemp = col_vals[iRow].as_string();
                                          iThisAptObjIdx = (sTemp.compare(sAptTypes[iApt])==0 ? iAptObjIdx[iApt] : -1);
                                       }           if (bVerboseLogging)
                                                      BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( sTemp.c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    }  break;
                        case  1 :   {  if (bVerboseLogging)
                                          sTemp += " / PVSystemName "      + col_vals[iRow].as_string();
                                       // ignore PVSystemName
                                    }  break;
                        case  2 :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += " / PctForCommonLoad "  + std::string(num);  }
                                       dResFrac = 1 - (col_vals[iRow].as_double() / 100.0);
                                    }  break;
                        case  3 :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += " / UnitWeight "        + std::string(num);  }
                                       dUnitWeight = col_vals[iRow].as_double();
                                    }  break;
                        case  4 :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += " / DailyAvg "          + std::string(num);  }
                                       // ignore DailyAvg
                                    }  break;
                        case  5 :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += " / AnnualTotal "       + std::string(num);  }
                                       // ignore AnnualTotal
                                    }  break;
                        case  6 :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += " / " + std::string(num);  }
                                       if (iThisAptObjIdx >= 0)
                                          //daaPVByAptAndMo[iThisAptObjIdx][0] += (dResFrac * dUnitWeight * col_vals[iRow].as_double());
                                          daaPVByAptAndMo[iThisAptObjIdx][0] += col_vals[iRow].as_double();     // ResFrac & UnitWeight seem to already be applied - post-SP1 FIX - SAC 11/09/23
                                    }  break;
                        default :   {  if (bVerboseLogging)
                                       {  snprintf(num, 50, "%f", col_vals[iRow].as_double());  sTemp += ", "  + std::string(num);  }
                                       if (iThisAptObjIdx >= 0)
                                          //daaPVByAptAndMo[iThisAptObjIdx][iColIdx-6] += (dResFrac * dUnitWeight * col_vals[iRow].as_double());
                                          daaPVByAptAndMo[iThisAptObjIdx][iColIdx-6] += col_vals[iRow].as_double();     // ResFrac & UnitWeight seem to already be applied
                                    }  break;
                     }
                     done = false;
                     iColIdx++;
                  }
               }
               ++iRow;
               if (bVerboseLogging)
                  BEMPX_WriteLogFile( QString( "%1" ).arg( sTemp.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            }
            int iSetRetVal;
            for (int iApt=0; iApt < iAptTypeFoundIdx; iApt++)
               for (int iMo=0; iMo<12; iMo++)
               {  iSetRetVal = BEMPX_SetBEMData( lEnduseDBID+iMo, BEMP_Flt, (void*) &daaPVByAptAndMo[iApt][iMo], BEMO_User, iApt );
               }
         }

         if (iRetVal==0 && iAptTypeFoundIdx > 0)
         {  // setup ELECTRIC Summary table
            std::vector<std::string> sElecTable_names({"qSummaryLightingTotalsByApt",
                                                   "qSummaryHeatingTotalsByApt",
                                                   "qSummaryDHWTotalsByApt",
                                                   "qSummaryCookingTotalsByApt",
                                                   "qSummaryCoolingTotalsByApt",
                                                   "qSummaryRefrigeratorTotalsByApt",
                                                   "qSummaryDishwasherTotalsByApt",
                                                   "qSummaryWasherTotalsByApt",
                                                   "qSummaryDryerTotalsByApt",
                                                   "qSummaryPlugLoadsTotalsByApt"}); 
            // CUACToolMiner::Project project;
            // //iLocRes = db.get_project(sProjectName, sElecTable_names, project);
            // for (auto& table_name : sElecTable_names)
            // {  CUACToolMiner::Table table;
            //    if (table_name == "qSummaryDryerTotalsByApt")
            //       iLocRes = db.get_dryer_electric_use_table(project, table);
            //    else if (table_name == "qSummaryDryerTotalsByAptGas")
            //       iLocRes = db.get_dryer_gas_use_table(project, table);
            //    else
            //       iLocRes = db.get_table(table_name, "ProjectID", projectID, table);
            //    if (iLocRes != CUACToolMiner::no_error)
            //       break;
            //    project.second.push_back(table);
            // }
            CUACToolMiner::Tables tables;    // updates to CUACToolMiner - SAC 09/26/23
            //int res = getProjectTables(mainDB, sProject_name, tables, sTable_names);
            iLocRes = db.get_project_tables( projectID, sElecTable_names, tables );
            if (iLocRes != CUACToolMiner::no_error)
            {  iRetVal = iLocRes;
               sErrMsg = "Error importing CUAC summary electric use table from database: " + CUACToolMinerErrorMsg( iRetVal );
            }
            else
            {  CUACToolMiner::Table combined_table;
               combined_table.first = "qSummaryAllElectricEndUsesByApt";
               bool first(true);
               //for (auto& table : tables) {
               //    auto& combined_cols = combined_table.second;
               //    auto& cols = table.second;
               //    if (first)
               //        combined_cols = cols;
               //    else {
               //        auto& combined_col = combined_cols.begin();
               //        for (auto& col : cols) {
               //            combined_col->second.insert(
               //                combined_col->second.end(), col.second.begin(), col.second.end());
               //            ++combined_col;
               //        }
               //    }
               //    first = false;
               //}
               for (auto& table : tables) {
                   auto& combined_cols = combined_table.second;
                   auto& cols = table.second;
                   if (first)
                       combined_cols = cols;
                   else {
                       auto combined_col = combined_cols.begin();
                       for (auto& col : cols) {
                           if (combined_col == combined_cols.end()) {
                               //logger->debug(
                               //    fmt::format("Attempting to combine mismatched table: {}", table.first));
                               break;
                           }
                           combined_col->second.insert(
                               combined_col->second.end(), col.second.begin(), col.second.end());
                           ++combined_col;
                       }
                   }
                   first = false;
               }

               auto& cols = combined_table.second;
//               std::vector<CUACToolMiner::Column>& cols = combined_table.second;
               bool done(false);
               int iColIdx=0;
               std::size_t iRow(0);
               while (!done) 
               {  done = true;
                  iColIdx = 0;
                  int iThisAptObjIdx = -1;
                  long lEnduseDBID = 0;
                  std::string sTemp;
                  for (auto& col : cols) 
//                  for (CUACToolMiner::Column& col : cols) 
                  {
                     auto &col_vals = col.second;
//                      std::vector<std::string> &col_vals = col.second;
                     if (iRow < col_vals.size())
                     {  switch (iColIdx)
                        {  case  0 :   {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                          for (int iApt=0; (iThisAptObjIdx < 0 && iApt < iAptTypeFoundIdx); iApt++)
                                          {  sTemp = col_vals[iRow].as_string();
                                             iThisAptObjIdx = (sTemp.compare(sAptTypes[iApt])==0 ? iAptObjIdx[iApt] : -1);
                                          }           if (bVerboseLogging)
                                                         BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( sTemp.c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  break;
                           case  1 :   {  if (iThisAptObjIdx >= 0)
                                          {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                             std::string sPropName = col_vals[iRow].as_string();
                                             if (sPropName.compare("Plug Loads")==0)
                                                sPropName = "PlugLoads";
                                             sPropName += "Elec[1]";
                                             lEnduseDBID = BEMPX_GetDatabaseID( sPropName.c_str(), iCID_OldCUACApt );
                                                      if (bVerboseLogging)
                                                         BEMPX_WriteLogFile( QString( "     property: %1 => DBID %2" ).arg( sPropName.c_str(), QString::number(lEnduseDBID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  }  break;
                           case  2 :
                           case  3 :   break;   // skip daily avg & annual total (or PVSystemName & PercentForCommonLoad for PV table)
                           default :   {  if (iThisAptObjIdx >= 0 && lEnduseDBID > 0)
                                          {  int iMo = iColIdx-3;
                                             switch (col_vals[iRow].index())        // SAC 09/20/23
                                             {  case CUACToolMiner::double_type :  dVal = col_vals[iRow].as_double();  break;
                                                case CUACToolMiner::int_type    :  dVal = col_vals[iRow].as_int();     break;
                                                case CUACToolMiner::string_type :  sTemp = col_vals[iRow].as_string();
                                                                                   dVal = atof( sTemp.c_str() );       break;
                                                default  :  assert( false );  break;
                                             }
                                             int iSetRetVal = BEMPX_SetBEMData( lEnduseDBID+iMo-1, BEMP_Flt, (void*) &dVal, BEMO_User, iThisAptObjIdx );
                                                      //if (bVerboseLogging)
                                                      //   BEMPX_WriteLogFile( QString( "        set %1 to DBID %2 objectIdx %3 - returned %4" ).arg( QString::number(dVal), QString::number(lEnduseDBID+iMo-1), QString::number(iThisAptObjIdx), QString::number(iSetRetVal) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  }  break;
                        }
                        done = false;
                        iColIdx++;
                     }
                  }
                  ++iRow;
         }  }  }  // setup & store Elec summary data

         if (iRetVal==0 && iAptTypeFoundIdx > 0)
         {  // setup GAS Summary table
            std::vector<std::string> sGasTable_names({"qSummaryHeatingTotalsByAptGas",
                                                   "qSummaryDHWTotalsByAptGas",
                                                   "qSummaryCookingTotalsByAptGas",
                                                   "qSummaryDryerTotalsByAptGas"});
            // CUACToolMiner::Project project;
            // //iLocRes = db.get_project(sProjectName, sGasTable_names, project);
            // for (auto& table_name : sGasTable_names)
            // {  CUACToolMiner::Table table;
            //    if (table_name == "qSummaryDryerTotalsByApt")
            //       iLocRes = db.get_dryer_electric_use_table(project, table);
            //    else if (table_name == "qSummaryDryerTotalsByAptGas")
            //       iLocRes = db.get_dryer_gas_use_table(project, table);
            //    else
            //       iLocRes = db.get_table(table_name, "ProjectID", projectID, table);
            //    if (iLocRes != CUACToolMiner::no_error)
            //       break;
            //    project.second.push_back(table);
            // }
            CUACToolMiner::Tables tables;    // updates to CUACToolMiner - SAC 09/26/23
            //int res = getProjectTables(mainDB, sProject_name, tables, sTable_names);
            iLocRes = db.get_project_tables( projectID, sGasTable_names, tables );
            if (iLocRes != CUACToolMiner::no_error)
            {  iRetVal = iLocRes;
               sErrMsg = "Error importing CUAC summary gas use table from database: " + CUACToolMinerErrorMsg( iRetVal );
            }
            else
            {  CUACToolMiner::Table combined_table;
               combined_table.first = "qSummaryAllGasEndUsesByApt";
               bool first(true);
               for (auto& table : tables) {
                   auto& combined_cols = combined_table.second;
                   auto& cols = table.second;
                   if (first)
                       combined_cols = cols;
                   else {
                       auto combined_col = combined_cols.begin();
                       for (auto& col : cols) {
                           if (combined_col == combined_cols.end()) {
                               //logger->debug(
                               //    fmt::format("Attempting to combine mismatched table: {}", table.first));
                               break;
                           }
                           combined_col->second.insert(
                               combined_col->second.end(), col.second.begin(), col.second.end());
                           ++combined_col;
                       }
                   }
                   first = false;
               }

               auto& cols = combined_table.second;
//               std::vector<CUACToolMiner::Column>& cols = combined_table.second;
               bool done(false);
               int iColIdx=0;
               std::size_t iRow(0);
               while (!done) 
               {  done = true;
                  iColIdx = 0;
                  int iThisAptObjIdx = -1;
                  long lEnduseDBID = 0;
                  std::string sTemp;
                  for (auto& col : cols) 
//                  for (CUACToolMiner::Column& col : cols) 
                  {
                     auto &col_vals = col.second;
//                      std::vector<std::string> &col_vals = col.second;
                     if (iRow < col_vals.size())
                     {  switch (iColIdx)
                        {  case  0 :   {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                          for (int iApt=0; (iThisAptObjIdx < 0 && iApt < iAptTypeFoundIdx); iApt++)
                                          {  sTemp = col_vals[iRow].as_string();
                                             iThisAptObjIdx = (sTemp.compare(sAptTypes[iApt])==0 ? iAptObjIdx[iApt] : -1);
                                             //iThisAptObjIdx = (col_vals[iRow].compare(sAptTypes[iApt])==0 ? iAptObjIdx[iApt] : -1);
                                          }           if (bVerboseLogging)
                                                         BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( sTemp.c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  break;
                           case  1 :   {  if (iThisAptObjIdx >= 0)
                                          {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                             std::string sPropName = col_vals[iRow].as_string();
                                             if (sPropName.compare("Plug Loads")==0)
                                                sPropName = "PlugLoads";
                                             sPropName += "Gas[1]";
                                             lEnduseDBID = BEMPX_GetDatabaseID( sPropName.c_str(), iCID_OldCUACApt );
                                                      if (bVerboseLogging)
                                                         BEMPX_WriteLogFile( QString( "     property: %1 => DBID %2" ).arg( sPropName.c_str(), QString::number(lEnduseDBID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  }  break;
                           case  2 :
                           case  3 :   break;   // skip daily avg & annual total
                           default :   {  if (iThisAptObjIdx >= 0 && lEnduseDBID > 0)
                                          {  int iMo = iColIdx-3;
                                             switch (col_vals[iRow].index())     // SAC 09/20/23
                                             {  case CUACToolMiner::double_type :  dVal = col_vals[iRow].as_double();  break;
                                                case CUACToolMiner::int_type    :  dVal = col_vals[iRow].as_int();     break;
                                                case CUACToolMiner::string_type :  sTemp = col_vals[iRow].as_string();
                                                                                   dVal = atof( sTemp.c_str() );       break;
                                                default  :  assert( false );  break;
                                             }
                                             int iSetRetVal = BEMPX_SetBEMData( lEnduseDBID+iMo-1, BEMP_Flt, (void*) &dVal, BEMO_User, iThisAptObjIdx );
                                                      //if (bVerboseLogging)
                                                      //   BEMPX_WriteLogFile( QString( "        set %1 to DBID %2 objectIdx %3 - returned %4" ).arg( QString::number(dVal), QString::number(lEnduseDBID+iMo-1), QString::number(iThisAptObjIdx), QString::number(iSetRetVal) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  }  break;
                        }
                        done = false;
                        iColIdx++;
                     }
                  }
                  ++iRow;
         }  }  }  // setup & store Elec summary data

      }
   }
   else
      sErrMsg = "Error initializing CUAC Access database: " + CUACToolMinerErrorMsg( iRetVal );

   return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::string LatestDateString( int& iYr, int& iMo, int& iDay, std::string prevDateStr, std::string chkDateStr )    // SAC 11/12/24
{  bool bReturnNew = false;
   size_t lastSlash  = chkDateStr.rfind('/');
   size_t firstSlash = chkDateStr.find( '/');
   if (firstSlash < lastSlash && firstSlash != std::string::npos && lastSlash != std::string::npos)
   {  int iThisYr=0, iThisMo=0, iThisDay=0;
      std::string str = chkDateStr.substr( lastSlash+1, std::string::npos ); // yr
      if (str.length() > 0)
         iThisYr = std::stoi( str );
      str = chkDateStr.substr( firstSlash+1, (lastSlash - firstSlash - 1) ); // da
      if (str.length() > 0)
         iThisDay = std::stoi( str );
      str = chkDateStr.substr( 0, firstSlash ); // mo
      if (str.length() > 0)
         iThisMo = std::stoi( str );
      if (iThisYr > iYr || (iThisYr == iYr && iThisMo > iMo) ||
          (iThisYr == iYr && iThisMo == iMo && iThisDay > iDay))
      {  bReturnNew = true;
         iYr = iThisYr;   iMo = iThisMo;   iDay = iThisDay;
   }  }
   return (bReturnNew ? chkDateStr : prevDateStr);
}

// return value:  > 0  =>  success, # reports combined
//                = 0  =>  no errors encountered, but also no reports combined (?)
//                < 0  =>  # of errors encountered - combining process aborted
int CUAC_CombineReports( bool bStoreBEMDetails, bool bSilent, bool bVerbose, char* pszOutputMsg, int iOutputMsgLen,
                         const char* pszRptGraphicsPath, int iCUAC_BEMProcIdx /*=-1*/, int iDataModel /*=0*/ )   // iDataModel: 0-CBECC / 1-SFam Res
{  int i, iRetVal = 0;

   QString qsData, qsTemp;
   std::string sOutPathFileCSV, sOutPathFilePDFD, sOutPathFilePDFS, sInPathFile, sErrorMsg, sWthrFileMismatch, sOutputMsg, sOutputPathFileBase;
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:CombinedResultsFile" ), qsData, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iCUAC_BEMProcIdx ); 
   qsTemp = qsData.right(4);
   if (qsTemp.compare( ".csv", Qt::CaseInsensitive ) == 0)
      qsData = qsData.left( qsData.length()-4 );
   sOutputPathFileBase = qsData.toLocal8Bit().constData();

   sOutPathFileCSV  = sOutputPathFileBase;      sOutPathFileCSV  += " - CUAC-combined.csv";
   sOutPathFilePDFD = sOutputPathFileBase;      sOutPathFilePDFD += " - CUAC-combined Details.pdf";
   sOutPathFilePDFS = sOutputPathFileBase;      sOutPathFilePDFS += " - CUAC-combined Submittal.pdf";

   bool bWriteCombineDetails = bVerbose;     // SAC 11/06/24
      // TESTING
      // bWriteCombineDetails = true;

   // testing / debugging
   std::string sOutPathFileDbg[4];
   sOutPathFileDbg[0] = sOutputPathFileBase;   sOutPathFileDbg[0] += "-CUACCombine-1.ibd-detail";
   sOutPathFileDbg[1] = sOutputPathFileBase;   sOutPathFileDbg[1] += "-CUACCombine-2.ibd-detail";
   sOutPathFileDbg[2] = sOutputPathFileBase;   sOutPathFileDbg[2] += "-CUACCombine-3.ibd-detail";
   sOutPathFileDbg[3] = sOutputPathFileBase;   sOutPathFileDbg[3] += "-CUACCombine-4.ibd-detail";
   if (bWriteCombineDetails)
      BEMPX_WriteProjectFile( sOutPathFileDbg[0].c_str(), BEMFM_DETAIL, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
                              false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, iCUAC_BEMProcIdx, -1, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );


   int iNumCombineFiles = 0, iFileFormatVer = 0, iTotNumAffordableDwellings = 0, iTotNumMarketRateDwellings = 0;
   long iaTotNumAffordableDwellingsByBdrm[8] = {0,0,0,0,0,0,0,0}, iaTotNumMarketRateDwellingsByBdrm[8] = {0,0,0,0,0,0,0,0};
   double dTotPVKW = 0.0;
   std::string sWthrFile, sElecUtilTerrRate, sGasUtilTerrRate, sCommunitySolarProjRpt, sSingleInvalidAnalysisMsg;  // items that must be consistent across each combined report
   std::string sElecUtil, sElecTerr, sElecRate, eElecRateType, sElecRateAdj, sGasUtil, sGasTerr, sGasRate, sGasRateType;  // to report in combined output
   std::vector<long> ivCombineFileIdx, ivTotNumAffordableUnits, ivNumAffordableDwellingsBySize[8], ivNumMarketRateDwellingsBySize[8];
   long lProjZipCodeRpt=0, iTotNumInvalidAnalyses=0, iNumInvalidFileIdxs=0, iInvalidFileIdxs[3]={-1,-1,-1};    double dProjectIDRpt=-99;    // SAC 11/06/24
   int iTariffYr=0, iTariffMo=0, iTariffDay=0;
   std::string sProjStAddressRpt, sProjCityRpt, sProjStateRpt, sOwnerNameRpt, sOwnerAddressRpt, sOwnerCityRpt, sOwnerStateRpt, sOwnerZIPCodeRpt,      // SAC 11/06/24
               sContactNameRpt, sContactPhoneRpt, sContactEMailRpt, sLocalityRpt, sUnitTypeRpt, sAPNRpt, sOtherProjectIDRpt, sReportTypeRpt, sProjNameRpt, 
               sProjGasTypeRpt, sProjSoftwareVersionRpt, sProjCompManagerVersionRpt, sTariffDateRpt, sRunDateFmtRpt, sVerNum;               
   long lLastResultsToCombineIdx;
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:LastResultsToCombineIdx" ), lLastResultsToCombineIdx, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   bool bFirstCombineFile = true;
   for (i=0; i < lLastResultsToCombineIdx; i++)
   {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ResultsCSVToCombine" )+i, qsData, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iCUAC_BEMProcIdx ); 
      if (!qsData.isEmpty())
      {  if (!FileExists( qsData.toLocal8Bit().constData() ))
         {  // error - file not found
            iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
            sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d not found - %s\r\n" ) % (i+1) % qsData.toLocal8Bit().constData() );
         }
         else
         {  std::string sThisPathFile = qsData.toLocal8Bit().constData();
            std::ifstream in( sThisPathFile );
            if (!in.is_open())
            {  // error - opening file
               iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
               sErrorMsg += boost::str( boost::format( "Error: Unable to open Combine CSV file #%d - %s\r\n" ) % (i+1) % sThisPathFile );
            }
            else
            {  int iTotNumAffordableDwellingsThisFile=0, iaNumAffordableDwellingsByBdrm[8] = {0,0,0,0,0,0,0,0};
               int iTotNumMarketRateDwellingsThisFile=0, iaNumMarketRateDwellingsByBdrm[8] = {0,0,0,0,0,0,0,0};
               std::string line, sTemp, sThisFileWthr, sThisElecRate, sThisGasRate;
               std::vector<std::vector<std::string> > lines;
               bool bErrorInThisFile = false;
               int iNumInvalidAnalyses=0;   std::string sFirstInvalidAnalysisMsg;   // SAC 01/03/25
               getline( in, line );    // format ver #
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 0 && lines[0][0].length() > 0)
                  iFileFormatVer = std::stoi( lines[0][0] );
               else
                  iFileFormatVer = 0;  // error

               if (i > 0)
                  sOutputMsg += "\r\n";
               sOutputMsg += boost::str( boost::format( "Processing file #%d:  %s  (format %d)\r\n" ) % (i+1) % sThisPathFile % iFileFormatVer );

               getline( in, line );    // CUAC Analysis Inputs and Results Report		
               getline( in, line );    // 	Software:	CBECC 2022.3.1 (1357)
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 2 && lines[0][2].length() > 0)   // && sProjSoftwareVersionRpt.compare("(multiple)")!=0)
               {  size_t pos2 = lines[0][2].find('2');
                  std::string sThisVerNum;
                  if (pos2 > 0 && pos2 < lines[0][2].length())
                     sThisVerNum = lines[0][2].substr( pos2 );
                  if ( sThisVerNum.length() > 0 &&
                       ( sProjSoftwareVersionRpt.length() < 1 ||
                         sThisVerNum.compare( sVerNum ) > 0 ) )
                  {  sProjSoftwareVersionRpt = lines[0][2];
                     sVerNum = sThisVerNum;
               }  }

               getline( in, line );    // 	Ruleset:	BEMCmpMgr 2022.3.1 (8625)
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 2 && lines[0][2].length() > 0 && sProjCompManagerVersionRpt.compare("(multiple)")!=0)
               {  if (sProjCompManagerVersionRpt.length() < 1)
                     sProjCompManagerVersionRpt = lines[0][2];
                  else if (sProjCompManagerVersionRpt.compare( lines[0][2] )!=0)
                     sProjCompManagerVersionRpt = "(multiple)";
               }

               getline( in, line );    // 	CSE:	CSE19 0.922.1 EXE
               getline( in, line );    // 	Tariff Date:	12/18/2023
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 2 && lines[0][2].length() > 0)   // && sTariffDateRpt.compare("(multiple)")!=0)
                  sTariffDateRpt = LatestDateString( iTariffYr, iTariffMo, iTariffDay, sTariffDateRpt, lines[0][2] );

               getline( in, line );    // Run Title:		MF8 Restructure Prototype
               getline( in, line );    // Run Date/Time:		2024-10-24T17:32:47-07:00
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 2 && lines[0][2].length() > 0 && sRunDateFmtRpt.compare("(multiple)")!=0)
               {  if (sRunDateFmtRpt.length() < 1)
                     sRunDateFmtRpt = lines[0][2];
                  else if (sRunDateFmtRpt.compare( lines[0][2] )!=0)
                     sRunDateFmtRpt = "(multiple)";
               }

               getline( in, line );    // Model File:		C:/CBECC-Res/CUAC/Support/24-10-24 RedwdDA PVInBillCalcs/1-NEM2Adj/CUAC-MF8Unit_2Story_ELEC-CZ12
               getline( in, line );    // Weather File:		SACRAMENTO-EXECUTIVE_STYP20.epw
               ParseCSV( line, lines );      assert( lines.size() > 0 );
               if (lines[0].size() > 2)
               {  sThisFileWthr = lines[0][2];
                  size_t iLastSlash = sThisFileWthr.rfind( "\\" );
                  if (iLastSlash != std::string::npos)
                     sThisFileWthr = sThisFileWthr.substr( iLastSlash+1 );
                  if (bFirstCombineFile)
                     sWthrFile = sThisFileWthr;
                  else if (!boost::iequals( sWthrFile, sThisFileWthr ))
                  {  // error - weather file doesn't match   - switched to Warning - SAC 11/14/24 (tic #1386)
                     //bErrorInThisFile = true;
                     //sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d's weather file mismatch -\r\n   %s\r\n   -vs.-  %s\r\n" ) % (i+1) % sWthrFile % sThisFileWthr );
                     if (sWthrFileMismatch.length() < 1)
                        sWthrFileMismatch = boost::str( boost::format( "first weather file encountered:\r\n    %s\r\n" ) % sWthrFile );
                     sWthrFileMismatch   += boost::str( boost::format( "file #%d:    %s\r\n" ) % (i+1) % sThisFileWthr );
               }  }

               if (iFileFormatVer >= 7)   // SAC 01/03/25
               {  getline( in, line );    // Valid/Invalid analysis msg
                  ParseCSV( line, lines );      assert( lines.size() > 0 );
                  if (lines[0].size() > 2)
                  {  std::string sThisValidMsg = lines[0][2];
                     if (sThisValidMsg.find("Invalid") != std::string::npos)
                     {  if (sThisValidMsg[0] >= '0' && sThisValidMsg[0] <= '9')  // msg string begins w/ the # of invalid analyses
                        {  // this is a combined CSV w/ possibly multiple invalid analyses
                           std::size_t iFirstSpc = sThisValidMsg.find(" ");         assert( iFirstSpc != std::string::npos );
                           if (iFirstSpc != std::string::npos)
                           {  std::string sNumInvalid = sThisValidMsg.substr( 0, iFirstSpc );
                              int iThisNumInvalid = atoi( sNumInvalid.c_str() );
                              std::size_t iInvMsgBegin = sThisValidMsg.find(" - ");
                              if (iThisNumInvalid == 1 && iTotNumInvalidAnalyses == 0 && iInvMsgBegin != std::string::npos &&
                                  sThisValidMsg.length() > iInvMsgBegin+3)
                                 sFirstInvalidAnalysisMsg = sThisValidMsg.substr( iInvMsgBegin+3 );
                              iTotNumInvalidAnalyses += iThisNumInvalid;
                              if (iNumInvalidFileIdxs < 3)
                                 iInvalidFileIdxs[iNumInvalidFileIdxs] = i+1;
                              iNumInvalidFileIdxs++;
                        }  }
                        else
                        {  std::size_t iInvMsgBegin = sThisValidMsg.find(" - ");
                           if (iTotNumInvalidAnalyses == 0 && iInvMsgBegin != std::string::npos &&
                               sThisValidMsg.length() > iInvMsgBegin+3)
                              sFirstInvalidAnalysisMsg = sThisValidMsg.substr( iInvMsgBegin+3 );
                           iTotNumInvalidAnalyses += 1;
                           if (iNumInvalidFileIdxs < 3)
                              iInvalidFileIdxs[iNumInvalidFileIdxs] = i+1;
                           iNumInvalidFileIdxs++;
                        }
                        if (iTotNumInvalidAnalyses == 1 && sFirstInvalidAnalysisMsg.length() > 0)
                           sSingleInvalidAnalysisMsg = sFirstInvalidAnalysisMsg;
                        else
                           sSingleInvalidAnalysisMsg.clear();
               }  }  }

               if (!bErrorInThisFile)
               {  getline( in, line );       // blank
                  getline( in, line );       // Analysis Inputs:	
                  if (iFileFormatVer >= 4)         // SAC 11/06/24
                  {  getline( in, line );    // Site Address: ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 7 && lines[0][7].length() > 0 && sOwnerNameRpt.compare("(multiple)")!=0)
                     {  if (sOwnerNameRpt.length() < 1)
                           sOwnerNameRpt = lines[0][7];
                        else if (sOwnerNameRpt.compare( lines[0][7] )!=0)
                           sOwnerNameRpt = "(multiple)";
                     }
                     if (lines[0].size() > 13 && lines[0][13].length() > 0 && sContactNameRpt.compare("(multiple)")!=0)
                     {  if (sContactNameRpt.length() < 1)
                           sContactNameRpt = lines[0][13];
                        else if (sContactNameRpt.compare( lines[0][13] )!=0)
                           sContactNameRpt = "(multiple)";
                     }
                     getline( in, line );    //    Address: ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 2 && lines[0][2].length() > 0 && sProjStAddressRpt.compare("(multiple)")!=0)
                     {  if (sProjStAddressRpt.length() < 1)
                           sProjStAddressRpt = lines[0][2];
                        else if (sProjStAddressRpt.compare( lines[0][2] )!=0)
                           sProjStAddressRpt = "(multiple)";
                     }
                     if (lines[0].size() > 7 && lines[0][7].length() > 0 && sOwnerAddressRpt.compare("(multiple)")!=0)
                     {  if (sOwnerAddressRpt.length() < 1)
                           sOwnerAddressRpt = lines[0][7];
                        else if (sOwnerAddressRpt.compare( lines[0][7] )!=0)
                           sOwnerAddressRpt = "(multiple)";
                     }
                     if (lines[0].size() > 13 && lines[0][13].length() > 0 && sContactEMailRpt.compare("(multiple)")!=0)
                     {  if (sContactEMailRpt.length() < 1)
                           sContactEMailRpt = lines[0][13];
                        else if (sContactEMailRpt.compare( lines[0][13] )!=0)
                           sContactEMailRpt = "(multiple)";
                     }
                     getline( in, line );    //    City / St / Zip ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 2 && lines[0][2].length() > 0 && sProjCityRpt.compare("(multiple)")!=0)
                     {  if (sProjCityRpt.length() < 1)
                           sProjCityRpt = lines[0][2];
                        else if (sProjCityRpt.compare( lines[0][2] )!=0)
                           sProjCityRpt = "(multiple)";
                     }
                     if (lines[0].size() > 4 && lines[0][4].length() > 0 && lProjZipCodeRpt != -999)
                     {  long lZip = std::stoi( lines[0][4] );
                        if (lZip > 0 && lProjZipCodeRpt == 0)
                           lProjZipCodeRpt = lZip;
                        else if (lZip > 0 && lZip != lProjZipCodeRpt)
                           lProjZipCodeRpt = -999;    // multiple (leave undefined)
                     }
                     if (lines[0].size() > 7 && lines[0][7].length() > 0 && sOwnerCityRpt.compare("(multiple)")!=0)
                     {  if (sOwnerCityRpt.length() < 1)
                           sOwnerCityRpt = lines[0][7];
                        else if (sOwnerCityRpt.compare( lines[0][7] )!=0)
                           sOwnerCityRpt = "(multiple)";
                     }
                     if (lines[0].size() > 8 && lines[0][8].length() > 0 && sOwnerStateRpt.compare("(multiple)")!=0)
                     {  if (sOwnerStateRpt.length() < 1)
                           sOwnerStateRpt = lines[0][8];
                        else if (sOwnerStateRpt.compare( lines[0][8] )!=0)
                           sOwnerStateRpt = "(multiple)";
                     }
                     if (lines[0].size() > 9 && lines[0][9].length() > 0 && sOwnerZIPCodeRpt.compare("(multiple)")!=0)
                     {  if (sOwnerZIPCodeRpt.length() < 1)
                           sOwnerZIPCodeRpt = lines[0][9];
                        else if (sOwnerZIPCodeRpt.compare( lines[0][9] )!=0)
                           sOwnerZIPCodeRpt = "(multiple)";
                     }
                     if (lines[0].size() > 13 && lines[0][13].length() > 0 && sContactPhoneRpt.compare("(multiple)")!=0)
                     {  if (sContactPhoneRpt.length() < 1)
                           sContactPhoneRpt = lines[0][13];
                        else if (sContactPhoneRpt.compare( lines[0][13] )!=0)
                           sContactPhoneRpt = "(multiple)";
                     }
                     getline( in, line );    // blank
                     getline( in, line );    //  Locality ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 2 && lines[0][2].length() > 0 && sLocalityRpt.compare("(multiple)")!=0)
                     {  if (sLocalityRpt.length() < 1)
                           sLocalityRpt = lines[0][2];
                        else if (sLocalityRpt.compare( lines[0][2] )!=0)
                           sLocalityRpt = "(multiple)";
                     }
                     if (lines[0].size() > 5 && lines[0][5].length() > 0 && dProjectIDRpt != -999)
                     {  double dProjID = std::stod( lines[0][5] );
                        if (dProjectIDRpt == -99)
                           dProjectIDRpt = dProjID;
                        else if (dProjID != dProjectIDRpt)
                           dProjectIDRpt = -999;    // multiple (leave undefined)
                     }
                     if (lines[0].size() > 8 && lines[0][8].length() > 0 && sOtherProjectIDRpt.compare("(multiple)")!=0)
                     {  if (sOtherProjectIDRpt.length() < 1)
                           sOtherProjectIDRpt = lines[0][8];
                        else if (sOtherProjectIDRpt.compare( lines[0][8] )!=0)
                           sOtherProjectIDRpt = "(multiple)";
                     }
                     if (iFileFormatVer >= 5 && lines[0].size() > 13 && lines[0][13].length() > 0)    // SAC 11/12/24 (tic #1386)
                     {  if (sReportTypeRpt.length() < 1)
                           sReportTypeRpt = lines[0][13];
                        else if (!boost::iequals( sReportTypeRpt, lines[0][13] ))
                        {  // error - report type doesn't match
                           bErrorInThisFile = true;
                           sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d's report type mismatch -\r\n   %s\r\n   -vs.-  %s\r\n" ) % (i+1) % sReportTypeRpt % lines[0][13] );
                     }  }
                     getline( in, line );    //  Unit Type ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 2 && lines[0][2].length() > 0 && sUnitTypeRpt.compare("(multiple)")!=0)
                     {  if (sUnitTypeRpt.length() < 1)
                           sUnitTypeRpt = lines[0][2];
                        else if (sUnitTypeRpt.compare( lines[0][2] )!=0)
                           sUnitTypeRpt = "(multiple)";
                     }
                     if (lines[0].size() > 5 && lines[0][5].length() > 0 && sAPNRpt.compare("(multiple)")!=0)
                     {  if (sAPNRpt.length() < 1)
                           sAPNRpt = lines[0][5];
                        else if (sAPNRpt.compare( lines[0][5] )!=0)
                           sAPNRpt = "(multiple)";
                     }
                     getline( in, line );    //  Project Name ...
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 2 && lines[0][2].length() > 0 && sProjNameRpt.compare("(multiple)")!=0)
                     {  if (sProjNameRpt.length() < 1)
                           sProjNameRpt = lines[0][2];
                        else if (sProjNameRpt.compare( lines[0][2] )!=0)
                           sProjNameRpt = "(multiple)";
                     }
                     if (lines[0].size() > 8 && lines[0][8].length() > 0 && sProjGasTypeRpt.compare("(multiple)")!=0)
                     {  if (sProjGasTypeRpt.length() < 1)
                           sProjGasTypeRpt = lines[0][8];
                        else if (sProjGasTypeRpt.compare( lines[0][8] )!=0)
                           sProjGasTypeRpt = "(multiple)";
                     }
                  }

                  getline( in, line );       // 	# Affordable Units by Type:
                  bool bTotalRowFound = false;
                  for (int j=0; (j<10 && !bTotalRowFound); j++)
                  {  getline( in, line );    // ,,<bedroom size>,
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0][2].find( "Total" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iTotNumAffordableDwellingsThisFile = std::stoi( lines[0][4] );
                        iTotNumAffordableDwellings += iTotNumAffordableDwellingsThisFile;
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                        {  iTotNumMarketRateDwellingsThisFile = std::stoi( lines[0][5] );
                           iTotNumMarketRateDwellings += iTotNumMarketRateDwellingsThisFile;
                        }
                        bTotalRowFound = true;
                     }
                     else if (lines[0][2].find( "Studio" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[0] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[0] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "1 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[1] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[1] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "2 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[2] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[2] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "3 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[3] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[3] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "4 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[4] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[4] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "5 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[5] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[5] += std::stoi( lines[0][5] );
                     }
                     else if (lines[0][2].find( "6 Bed" ) != std::string::npos && lines[0][4].length() > 0)
                     {  iaNumAffordableDwellingsByBdrm[6] += std::stoi( lines[0][4] );
                        if (iFileFormatVer > 2 && lines[0][5].length() > 0)
                           iaNumMarketRateDwellingsByBdrm[6] += std::stoi( lines[0][5] );
                     }
                     else
                     {  // error - unrecognized # units record
                        bErrorInThisFile = true;
                        sErrorMsg += boost::str( boost::format( "Error: Unrecognized unit type (%s) in file #%d\r\n" ) % lines[0][2] % (i+1) );
                     }

                     if (!bErrorInThisFile && !bTotalRowFound)
                     {  if (iFileFormatVer < 3)
                           sOutputMsg += boost::str( boost::format( "   %d affordable %s dwellings\r\n" ) % std::stoi( lines[0][4] ) % lines[0][2] );
                        else
                           sOutputMsg += boost::str( boost::format( "   %d affordable & %d market rate %s dwellings\r\n" ) % std::stoi( lines[0][4] ) % std::stoi( lines[0][5] ) % lines[0][2] );
                  }  }

                  if (!bTotalRowFound)
                  {  // error - unrecognized # units record
                     bErrorInThisFile = true;
                     sErrorMsg += boost::str( boost::format( "Error: Total dwelling unit type count not found in file #%d\r\n" ) % (i+1) );
               }  }

               if (!bErrorInThisFile)
               {  getline( in, line );       // elec utility
                  ParseCSV( line, lines );      assert( lines.size() > 0 && lines[0].size() > 23 );
                  sThisElecRate = boost::str( boost::format( "%s  /  %s  /  %s  /  %s  /  %s" ) % lines[0][3] % lines[0][10] % lines[0][14] % lines[0][20] % lines[0][23] );
                  if (bFirstCombineFile)
                  {  sElecUtilTerrRate = sThisElecRate;
                     sElecUtil = lines[0][3];
                     sElecTerr = lines[0][10];
                     sElecRate = lines[0][14];
                     eElecRateType = lines[0][20];
                     sElecRateAdj  = lines[0][23];
                  }
                  else if (!boost::iequals( sElecUtilTerrRate, sThisElecRate ))
                  {  // error - elec rate doesn't match
                     bErrorInThisFile = true;
                     sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d's eletric rate mismatch -\r\n   %s\r\n   -vs.-  %s\r\n" ) % (i+1) % sElecUtilTerrRate % sThisElecRate );
               }  }

               if (!bErrorInThisFile)
               {  getline( in, line );       // gas utility
                  ParseCSV( line, lines );      assert( lines.size() > 0 && lines[0].size() > 3 );
                  sThisGasRate = lines[0][3];
                  if (sThisGasRate.find( "no gas" ) == std::string::npos) // IGNORE 'no gas' rate files
                  {  if (lines[0].size() > 20)     // fix bug where 'no gas' not properly flagged - SAC 11/07/24
                        sThisGasRate = boost::str( boost::format( "%s  /  %s  /  %s  /  %s" ) % lines[0][3] % lines[0][10] % lines[0][14] % lines[0][20] );
                     if (sGasUtilTerrRate.length() < 1)
                     {  sGasUtilTerrRate = sThisGasRate;
                        sGasUtil = lines[0][3];
                        if (lines[0].size() > 10)
                           sGasTerr = lines[0][10];
                        if (lines[0].size() > 14)
                           sGasRate = lines[0][14];
                        if (lines[0].size() > 20)
                           sGasRateType = lines[0][20];
                     }
                     else if (!boost::iequals( sGasUtilTerrRate, sThisGasRate ))
                     {  // error - elec rate doesn't match
                        bErrorInThisFile = true;
                        sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d's gas rate mismatch -\r\n   %s\r\n   -vs.-  %s\r\n" ) % (i+1) % sGasUtilTerrRate % sThisGasRate );
               }  }  }

                  // sOutputMsg += boost::str( boost::format( "file #%d, weather: %s, total affordable units: %d,\r\n   file: %s\r\n   elec rate: %s\r\n   gas rate: %s\r\n\r\n" ) % (i+1) % sThisFileWthr % iTotNumAffordableDwellings % sThisPathFile % sThisElecRate % sThisGasRate );

               if (bErrorInThisFile)
                  iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
               else
               {  ivCombineFileIdx.push_back( i );
                  ivTotNumAffordableUnits.push_back( iTotNumAffordableDwellingsThisFile );
                  for (int j=0; j<8; j++)
                  {  iaTotNumAffordableDwellingsByBdrm[j] += iaNumAffordableDwellingsByBdrm[j];
                     iaTotNumMarketRateDwellingsByBdrm[j] += iaNumMarketRateDwellingsByBdrm[j];
                     ivNumAffordableDwellingsBySize[j].push_back( iaNumAffordableDwellingsByBdrm[j] );
                     ivNumMarketRateDwellingsBySize[j].push_back( iaNumMarketRateDwellingsByBdrm[j] );
               }  }
               bFirstCombineFile = false;
            }
   }  }  }
   if (iRetVal >= 0 && iTotNumAffordableDwellings < 1)
   {  iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
      sErrorMsg += "Error: Combining process aborted due to no affordable units found\r\n";
   }
   else if (iRetVal >= 0 && iTotNumInvalidAnalyses > 0)     // added to prevent combination of 'invalid' analyses CSVs - SAC 01/26/25
   {  iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
      if (iTotNumInvalidAnalyses == 1 && sSingleInvalidAnalysisMsg.length() > 0)
         sErrorMsg += boost::str( boost::format( "Error: Combining process aborted due to 1 invalid report included in CSV file #%d: %s\r\n" ) % iInvalidFileIdxs[0] % sSingleInvalidAnalysisMsg );
      else
         switch (iNumInvalidFileIdxs)
         {  case 2  : sErrorMsg += boost::str( boost::format( "Error: Combining process aborted due to invalid reports specified in 2 CSV files: #%d, & #%d\r\n" ) % iInvalidFileIdxs[0] % iInvalidFileIdxs[1] );  break;
            case 3  : sErrorMsg += boost::str( boost::format( "Error: Combining process aborted due to invalid reports specified in 3 CSV files: #%d, #%d, & #%d\r\n" ) % iInvalidFileIdxs[0] % iInvalidFileIdxs[1] % iInvalidFileIdxs[2] );  break;
            default : sErrorMsg += boost::str( boost::format( "Error: Combining process aborted due to invalid reports specified in %d CSV files: #%d, #%d, #%d and %d other(s)\r\n" ) % iNumInvalidFileIdxs % iInvalidFileIdxs[0] % iInvalidFileIdxs[1] % iInvalidFileIdxs[2] % (iNumInvalidFileIdxs-3) );  break;
   }     }
   else if (iRetVal >= 0 && sReportTypeRpt.length() < 1)
   {  iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
      //sErrorMsg += "Error: Aborting combining process due to v5 report details CSV not included in combine set (Report Type undefined). Rerun at least 1 CUAC project in current release.\r\n";
      sErrorMsg += "Error: Combining process aborted. Include at least 1 CUAC report from the current release.\r\n";
   }

   if (iRetVal >= 0 && sWthrFileMismatch.length() > 1)
   {  // CONFIRM from user that processing should continue
      std::string sWarningMsg;
      if (!bSilent)
      {  sWarningMsg = boost::str( boost::format( "Warning:  Weather file inconsistency found -\n%s\nContinue combining these CUAC report files?" ) % sWthrFileMismatch );
         if (::MessageBox( NULL /*hWnd*/, sWarningMsg.c_str(), "CUAC Weather File Mismatch", MB_YESNO|MB_DEFBUTTON1|MB_ICONQUESTION ) == IDNO)
            iRetVal = -1;
      }
      if (iRetVal < 0)
         // post weather file message to sErrorMsg and process like any other error 
         sErrorMsg = boost::str( boost::format( "Error:  Combining process aborted due to Weather File Inconsistency -\r\n%s" ) % sWthrFileMismatch );
      else
      {  // post message to project log & routine output msg
         sWarningMsg  = "Warning:  CUAC report files combined despite Weather File Inconsistency -\r\n";
         sWarningMsg += sWthrFileMismatch;
         BEMPX_WriteLogFile( sWarningMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         if (sOutputMsg.length() > 5)
            sOutputMsg += "\r\n";
         sOutputMsg += sWarningMsg;
         sWthrFile += "  (multiple)";  // add multiple label to end of first wthr file found

      //						{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
      //							if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
      //								bAbort = true;
      //						}
      //
      //            bAbort = (BEMMessageBox(sUserMsg, "", 3 /*error*/, (QMessageBox::Retry | QMessageBox::Abort) )  == QMessageBox::Abort );
      //
      //					QMessageBox msgBox;
      //					msgBox.setWindowTitle( qsPreAnalChkDlgCaption );
      //					msgBox.setIcon( QMessageBox::Warning ); 
      //					msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
      //					msgBox.setText( qsPreAnalChkDlgBody );
      //					msgBox.setDetailedText( qsPreAnalChkDlgDetails );
      //					msgBox.setStandardButtons( QMessageBox::Ok );
      //					if (iNumPreAnalChkErrs < 1)
      //						msgBox.addButton( QMessageBox::Abort );
      //					msgBox.setDefaultButton( QMessageBox::Ok );
      //					if (iAnalysisDialogTimeout > 0)
      //						msgBox.button(QMessageBox::Ok)->animateClick(iAnalysisDialogTimeout*1000);		// SAC 1/31/20 - set 10 sec timer, at which time 'OK' is automatically registered/clicked (CEC/LF request)
      //					showDetailsInQMessageBox(msgBox, 770, 300);		// routine to OPEN Details (to start with) + resize text box (to larger size)
      //					bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);
      //
      //						{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
      //							if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
      //								bAbort = true;
      //						}
      //
      //																		QMessageBox msgBox;
      //																		msgBox.setWindowTitle( qstrUMLHDlgCaption );
      //																		msgBox.setIcon( QMessageBox::Warning ); 
      //																		msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
      //																		msgBox.setText( qstrUMLHWarningMsg );
      //																		msgBox.setDetailedText( qstrUMLHWarningDetails );
      //																		msgBox.setStandardButtons( QMessageBox::Ok );  // needed for timeout to function
      //																		msgBox.setDefaultButton( QMessageBox::Ok );
      //																		if (iAnalysisDialogTimeout > 0)
      //																			msgBox.button(QMessageBox::Ok)->animateClick(iAnalysisDialogTimeout*1000);		// SAC 7/1/20 - apply dialog timeout here (Com tic #2680)
      //																		msgBox.exec();
      //
      //																	//	QMessageBox msgBox;
      //																	//	msgBox.setWindowTitle( "CheckSiteAccessViaQt()" );
      //																	//	msgBox.setIcon( QMessageBox::Warning ); 
      //																//		msgBox.setText( QString("About to delete Temp File: %1").arg(szTempFileName) );
      //																//		msgBox.exec();
      //
      //
      //				                                 //				QMessageBox msgBox;
      //				                                 //				msgBox.setWindowTitle( "CSE" );
      //				                                 //				msgBox.setIcon( QMessageBox::Warning ); 
      //				                                 //				msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
      //				                                 //				msgBox.setText( "About to launch CSE simulation(s)" );
      //				                                 //		//		msgBox.setDetailedText( qsRptIssuesDlgDetails );
      //				                                 //				msgBox.setStandardButtons( QMessageBox::Ok );
      //				                                 //				msgBox.addButton( QMessageBox::Abort );
      //				                                 //				msgBox.setDefaultButton( QMessageBox::Ok );
      //				                                 //				msgBox.exec();

   }  }

   // second round of reading - pull in all data and post to CUACCombine object
   if (iRetVal >= 0)
   {  for (i = 0; i < (int) ivCombineFileIdx.size(); i++)
      {  int iFileIdx = ivCombineFileIdx[i];
         BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ResultsCSVToCombine" )+iFileIdx, qsData, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iCUAC_BEMProcIdx ); 
         if (!qsData.isEmpty())
         {  if (!FileExists( qsData.toLocal8Bit().constData() ))
            {  // error - file not found
               iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
               sErrorMsg += boost::str( boost::format( "Error: Combine CSV file #%d not found (round 2) - %s\r\n" ) % (i+1) % qsData.toLocal8Bit().constData() );
            }
            else
            {  std::string sThisPathFile = qsData.toLocal8Bit().constData();
               std::ifstream in( sThisPathFile );
               if (!in.is_open())
               {  // error - opening file
                  iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
                  sErrorMsg += boost::str( boost::format( "Error: Unable to open Combine CSV file #%d (round 2) - %s\r\n" ) % (i+1) % sThisPathFile );
               }
               else
               {  bool bErrorInThisFile = false;
                  int iBDBCID_CUACCombine = BEMPX_GetDBComponentID( "CUACCombine" );
                  int iBDBCID_CUACResults = BEMPX_GetDBComponentID( "CUACResults" );
                  long lDBID_Combine_CUACResultsRef = BEMPX_GetDatabaseID( "CUACResultsRef", iBDBCID_CUACCombine );
                  std::string sCUACCombineName = boost::str( boost::format( "Combine file %d" ) % (iFileIdx+1) );
                  BEMObject* pCombineObj = BEMPX_CreateObject( iBDBCID_CUACCombine, sCUACCombineName.c_str(), NULL, BEMO_User, TRUE, TRUE, iCUAC_BEMProcIdx );
                  int iCombineObjIdx = (pCombineObj == NULL ? -1 : BEMPX_GetObjectIndex( pCombineObj->getClass(), pCombineObj, iCUAC_BEMProcIdx ));
                  if (iCombineObjIdx < 0)
                  {  // error - creating CUACCombine object
                     bErrorInThisFile = true;
                     sErrorMsg += boost::str( boost::format( "Error: Unable to create CUACCombine object for file #%d -\r\n   %s\r\n" ) % (iFileIdx+1) % sThisPathFile.c_str() );
                  }
                  else
                  {  std::string line, sTemp;      int j, k;
                     std::vector<std::vector<std::string> > lines;
                     double dTemp, dCommunitySolarKW = 0.0, dTotAffordableDwellingWeight = 0.0, daAffordableDwellingWeightsBySize[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                     int iaResultsObjIdx[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
                     dTotAffordableDwellingWeight = (double) ivTotNumAffordableUnits[i] / (double) iTotNumAffordableDwellings;
                     BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AffordableUnitsWeight", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTotAffordableDwellingWeight, 
                                       BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ReportFileName", iBDBCID_CUACCombine ), BEMP_Str, (void*) sThisPathFile.c_str(), 
                                       BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                     long lTemp, lTotAffordUnits=0, lTotMktRateUnits=0;       // SAC 11/06/24
                     for (j=0; (j<8 && ivNumAffordableDwellingsBySize[j].size() > iFileIdx); j++)
                     {  lTemp = ivNumAffordableDwellingsBySize[j][iFileIdx];      lTotAffordUnits += lTemp;
                        BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AffordableUnitsByBedrms", iBDBCID_CUACCombine ) + j, BEMP_Int, (void*) &lTemp, 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        lTemp = ivNumMarketRateDwellingsBySize[j][iFileIdx];      lTotMktRateUnits += lTemp;
                        BEMPX_SetBEMData( BEMPX_GetDatabaseID( "MktRateUnitsByBedrms"   , iBDBCID_CUACCombine ) + j, BEMP_Int, (void*) &lTemp, 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }
                     BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumAffordableDwellingUnits", iBDBCID_CUACCombine ), BEMP_Int, (void*) &lTotAffordUnits, 
                                       BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumMktRateDwellingUnits"   , iBDBCID_CUACCombine ), BEMP_Int, (void*) &lTotMktRateUnits, 
                                       BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                     getline( in, line );    // format ver #
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines[0].size() > 0 && lines[0][0].length() > 0)
                        iFileFormatVer = std::stoi( lines[0][0] );
                     getline( in, line );    // CUAC Analysis Inputs and Results Report		
                     getline( in, line );    // 	Software:	CBECC 2022.3.1 (1357)
                     getline( in, line );    // 	Ruleset:	BEMCmpMgr 2022.3.1 (8625)
                     getline( in, line );    // 	CSE:	CSE19 0.922.1 EXE
                     getline( in, line );    // 	Tariff Date:	12/18/2023
                     getline( in, line );    // Run Title:		MF8 Restructure Prototype
                     getline( in, line );    // Run Date/Time:		2024-10-24T17:32:47-07:00
                     getline( in, line );    // Model File:		C:/CBECC-Res/CUAC/Support/24-10-24 RedwdDA PVInBillCalcs/1-NEM2Adj/CUAC-MF8Unit_2Story_ELEC-CZ12
                     getline( in, line );    // Weather File:		SACRAMENTO-EXECUTIVE_STYP20.epw
                     getline( in, line );    // blank
                     getline( in, line );    // Analysis Inputs:	
                     if (iFileFormatVer >= 4)         // SAC 11/06/24
                     {  getline( in, line );    // Site Address: ...
                        getline( in, line );    //    Address: ...
                        getline( in, line );    //    City / St / Zip ...
                        getline( in, line );    // blank
                        getline( in, line );    //  Locality ...
                        getline( in, line );    //  Unit Type ...
                        getline( in, line );    //  Project Name ...
                     }
                     getline( in, line );    // 	# Affordable Units by Type:
                     bool bTotalRowFound = false;
                     for (j=0; (j<10 && !bTotalRowFound); j++)
                     {  getline( in, line );    // ,,<bedroom size>,
                        ParseCSV( line, lines );      assert( lines.size() > 0 );
                        if (lines[0][2].find( "Total" ) != std::string::npos)
                           bTotalRowFound = true;
                     }
                     getline( in, line );    // Electric rate info
                     getline( in, line );    // Gas rate info
                     getline( in, line );    // Water bill inputs
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines.size() > 0 && lines[0].size() > 3)
                     {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "WaterRateType", iBDBCID_CUACCombine ), BEMP_Str, (void*) lines[0][3].c_str(), 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        if (lines[0].size() > 7 && lines[0][7].length() > 0)
                        {  dTemp = std::stod( lines[0][7] ) * dTotAffordableDwellingWeight;
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( "WaterMonthlyCost", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTemp, 
                                             BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                           if (lines[0].size() > 11 && lines[0][11].length() > 0)
                           {  dTemp = std::stod( lines[0][11] ) * dTotAffordableDwellingWeight;
                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( "WaterVolumeCost", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTemp, 
                                                BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }  }  }

                     getline( in, line );    // Trash bill inputs
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines.size() > 0 && lines[0].size() > 3)
                     {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "TrashRateType", iBDBCID_CUACCombine ), BEMP_Str, (void*) lines[0][3].c_str(), 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        if (lines[0].size() > 7 && lines[0][7].length() > 0)
                        {  dTemp = std::stod( lines[0][7] ) * dTotAffordableDwellingWeight;
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( "TrashMonthlyCost", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTemp, 
                                             BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }  }

                     getline( in, line );    // Community Solar inputs
                     ParseCSV( line, lines );      assert( lines.size() > 0 );
                     if (lines.size() > 0 && lines[0].size() > 3 && lines[0].size() < 7)
                        BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CommunitySolarDescrip", iBDBCID_CUACCombine ), BEMP_Str, (void*) lines[0][3].c_str(), 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     else if (lines.size() > 0 && lines[0].size() > 6 && lines[0][6].length() > 0)
                     {  dCommunitySolarKW = std::stod( lines[0][6] );   // summed, not weighted  * dTotAffordableDwellingWeight;
                        BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CommunitySolarCap", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dCommunitySolarKW, 
                                          BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        if (lines[0].size() > 10)
                        {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CommunitySolarDescrip", iBDBCID_CUACCombine ), BEMP_Str, (void*) lines[0][10].c_str(), 
                                             BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                           if (dCommunitySolarKW > 0.0 && lines[0][10].length() > 0 && sCommunitySolarProjRpt.compare("(multiple projects)") != 0)
                           {  if (sCommunitySolarProjRpt.length() < 1)
                                 sCommunitySolarProjRpt = lines[0][10];
                              else if (sCommunitySolarProjRpt.compare(lines[0][10]) != 0)
                                 sCommunitySolarProjRpt = "(multiple projects)";
                        }  }
                     }

                     getline( in, line );    // blank  -OR-  On-site PV inputs
                     ParseCSV( line, lines );      //assert( lines.size() > 0 );
                     if (lines.size() > 0 && lines[0].size() > 2)
                     {  if (lines[0].size() > 6 && lines[0][6].length() > 0)
                        {  // there IS an On-Site PV row w/ PV cap specified
                           dTemp = std::stod( lines[0][6] );   // summed, not weighted  * dTotAffordableDwellingWeight;
                           BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OnSitePVServingAffordable", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTemp, 
                                             BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }
                        getline( in, line );    // blank -or- Battery Inputs - line following On-site PV inputs
                        if (iFileFormatVer >= 5)
                        {  ParseCSV( line, lines );      //assert( lines.size() > 0 );
                           if (lines[0].size() > 6 && lines[0][6].length() > 0 && lines[0][1].find( "Battery" ) != std::string::npos)
                           {  // there IS an On-Site Battery row w/ Batt cap specified
                              dTemp = std::stod( lines[0][6] );   // summed, not weighted  * dTotAffordableDwellingWeight;
                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OnSiteBattServingAffordable", iBDBCID_CUACCombine ), BEMP_Flt, (void*) &dTemp, 
                                                BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                              getline( in, line );    // blank line following On-site Batt inputs
                     }  }  }

                     // create & setup CUACResults objects for each bedrm type dwelling set in this Combine file - SAC 10/30/24 (tic #1386)
                     long lCombineBdrmIdx;
                     std::vector<long>   lvDwellBdrmIdx;
                     std::vector<int>    ivDwellResultsObjIdx;
                     std::vector<double> dvDwellWeight;
                     for (j=0; j<8; j++)
                     {  daAffordableDwellingWeightsBySize[j] = (iaTotNumAffordableDwellingsByBdrm[j] < 1 ? 0.0 : 
                                                                  (double) ivNumAffordableDwellingsBySize[j][iFileIdx] / (double) iaTotNumAffordableDwellingsByBdrm[j] );
                        if (daAffordableDwellingWeightsBySize[j] > 0.0001)
                        {  lCombineBdrmIdx = j+1;
                           std::string sResName = (j==0 ? boost::str( boost::format(  "Studio Cmbn file %d results" ) %     (iFileIdx+1) ) :
                                                          boost::str( boost::format( "%dbedrm Cmbn file %d results" ) % j % (iFileIdx+1) ) );
                           BEMObject* pResultsObj = BEMPX_CreateObject( iBDBCID_CUACResults, sResName.c_str(), NULL, BEMO_User, TRUE, TRUE, iCUAC_BEMProcIdx );
                           int iResultsObjIdx = (pResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pResultsObj->getClass(), pResultsObj, iCUAC_BEMProcIdx ));
                           if (iResultsObjIdx < 0)
                           {  // error - creating CUACResults object
                              bErrorInThisFile = true;
                              sErrorMsg += boost::str( boost::format( "Error: Unable to create CUACResults object '%s' for file #%d -\r\n   %s\r\n" ) % sResName.c_str() % (iFileIdx+1) % sThisPathFile.c_str() );
                           }
                           else
                           {  BEMPX_SetBEMData( lDBID_Combine_CUACResultsRef + j, BEMP_Obj, (void*) pResultsObj, 
                                                BEMO_User, iCombineObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CombineBdrmIdx", iBDBCID_CUACResults ), BEMP_Int, (void*) &lCombineBdrmIdx, 
                                                BEMO_User, iResultsObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CombineWeight" , iBDBCID_CUACResults ), BEMP_Flt, (void*) &daAffordableDwellingWeightsBySize[j], 
                                                BEMO_User, iResultsObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );

                              lvDwellBdrmIdx.push_back( lCombineBdrmIdx );
                              ivDwellResultsObjIdx.push_back( iResultsObjIdx );
                              dvDwellWeight.push_back( daAffordableDwellingWeightsBySize[j] );
                     }  }  }
                     int iNumDwellTypes = (int) ivDwellResultsObjIdx.size();

                     getline( in, line );    // Analysis Results:	
                     if (dCommunitySolarKW > 0.0001)
                        getline( in, line );    // extra label line when CommSlr reported

                     getline( in, line );    // Unit Type ... label row
                     getline( in, line );    // Monthly Usage ... label row
                     for (j=0; j < iNumDwellTypes; j++)
                     {  getline( in, line );    // total usage by utility / comm solar PV & credit
                        ParseCSV( line, lines );      assert( lines.size() > 0 );
                        const char* pszMoUsageCostProps[] = {  "ElecCosts[2]", "GasCosts[2]", "WaterCosts[2]", "TrashMonthlyCost",
                                                               "TotCosts[2]",  "CommunitySolarSizePerUnit", "CommunitySolarCreditPerUnit" };
                        double dMult[]  = {  dvDwellWeight[j], dvDwellWeight[j], dvDwellWeight[j], dvDwellWeight[j],
                                             dvDwellWeight[j], dvDwellWeight[j], (dvDwellWeight[j] * 12.0) };
                        int iaColIdx[]  = {  4, 5, 6, 7, 8, 14, 15, -1 };
                        k = -1;
                        while (iaColIdx[++k] >= 0)
                        {  if (lines.size() > 0 && lines[0].size() > iaColIdx[k] && lines[0][iaColIdx[k]].length() > 0)
                           {  dTemp = std::stod( lines[0][iaColIdx[k]] ) * dMult[k];
                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( pszMoUsageCostProps[k], iBDBCID_CUACResults ), BEMP_Flt, (void*) &dTemp, 
                                                BEMO_User, ivDwellResultsObjIdx[j], BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }  }
                     }

                     getline( in, line );    // blank
                     getline( in, line );    // Unit Type ... (& enduse) label row
                     getline( in, line );    // Monthly Allowance ... (& fuel) label row
                     for (j=0; j < iNumDwellTypes; j++)
                     {  getline( in, line );    // monthly allowance by enduse & fuel
                        ParseCSV( line, lines );      assert( lines.size() > 0 );
                        const char* pszMoUsageCostProps[] = {  "Allowances[1]", "Allowances[2]", "Allowances[3]", "Allowances[4]", "Allowances[5]", "Allowances[6]", "Allowances[7]",
                                                               "Allowances[8]", "Allowances[9]", "Allowances[10]", "Allowances[11]", "Allowances[12]", "Allowances[13]" };
                        int iaColIdx[]  = {  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1 };
                        k = -1;
                        while (iaColIdx[++k] >= 0)
                        {  if (lines.size() > 0 && lines[0].size() > iaColIdx[k] && lines[0][iaColIdx[k]].length() > 0)
                           {  dTemp = std::stod( lines[0][iaColIdx[k]] ) * dvDwellWeight[j];
                              BEMPX_SetBEMData( BEMPX_GetDatabaseID( pszMoUsageCostProps[k], iBDBCID_CUACResults ), BEMP_Flt, (void*) &dTemp, 
                                                BEMO_User, ivDwellResultsObjIdx[j], BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }  }
                     }

                     getline( in, line );    // blank
                     getline( in, line );    // Unit Type ... (& months/total) label row
                     const char* pszMoUsageByEUProps[7][13] =  { {  "ClgElecUse[1]", "ClgElecUse[2]", "ClgElecUse[3]", "ClgElecUse[4]", "ClgElecUse[5]", "ClgElecUse[6]", "ClgElecUse[7]",
                                                                    "ClgElecUse[8]", "ClgElecUse[9]", "ClgElecUse[10]", "ClgElecUse[11]", "ClgElecUse[12]", "ClgElecUse[13]"  },
                                                                 {  "HtgElecUse[1]", "HtgElecUse[2]", "HtgElecUse[3]", "HtgElecUse[4]", "HtgElecUse[5]", "HtgElecUse[6]", "HtgElecUse[7]",
                                                                    "HtgElecUse[8]", "HtgElecUse[9]", "HtgElecUse[10]", "HtgElecUse[11]", "HtgElecUse[12]", "HtgElecUse[13]"  },
                                                                 {  "HtgGasUse[1]", "HtgGasUse[2]", "HtgGasUse[3]", "HtgGasUse[4]", "HtgGasUse[5]", "HtgGasUse[6]", "HtgGasUse[7]",
                                                                    "HtgGasUse[8]", "HtgGasUse[9]", "HtgGasUse[10]", "HtgGasUse[11]", "HtgGasUse[12]", "HtgGasUse[13]"  },
                                                                 {  "DHWElecUse[1]", "DHWElecUse[2]", "DHWElecUse[3]", "DHWElecUse[4]", "DHWElecUse[5]", "DHWElecUse[6]", "DHWElecUse[7]",
                                                                    "DHWElecUse[8]", "DHWElecUse[9]", "DHWElecUse[10]", "DHWElecUse[11]", "DHWElecUse[12]", "DHWElecUse[13]"  },
                                                                 {  "DHWGasUse[1]", "DHWGasUse[2]", "DHWGasUse[3]", "DHWGasUse[4]", "DHWGasUse[5]", "DHWGasUse[6]", "DHWGasUse[7]",
                                                                    "DHWGasUse[8]", "DHWGasUse[9]", "DHWGasUse[10]", "DHWGasUse[11]", "DHWGasUse[12]", "DHWGasUse[13]"  },
                                                                 {  "PVSysElecUse[1]", "PVSysElecUse[2]", "PVSysElecUse[3]", "PVSysElecUse[4]", "PVSysElecUse[5]", "PVSysElecUse[6]", "PVSysElecUse[7]",
                                                                    "PVSysElecUse[8]", "PVSysElecUse[9]", "PVSysElecUse[10]", "PVSysElecUse[11]", "PVSysElecUse[12]", "PVSysElecUse[13]"  },
                                                                 {  "BattElecUse[1]", "BattElecUse[2]", "BattElecUse[3]", "BattElecUse[4]", "BattElecUse[5]", "BattElecUse[6]", "BattElecUse[7]",
                                                                    "BattElecUse[8]", "BattElecUse[9]", "BattElecUse[10]", "BattElecUse[11]", "BattElecUse[12]", "BattElecUse[13]"  }  };
                     double daEnduseMult[] = { 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0 };
                     int iNumEUs = (iFileFormatVer >= 6 ? 7 : 6);    // SAC 12/16/24
                     for (int iEU=0; iEU < iNumEUs; iEU++)
                     {  int iaColIdx[]  = {  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, -1 };
                        getline( in, line );       // <enduse> <fuel> Usage
                        for (j=0; j < iNumDwellTypes; j++)
                        {  getline( in, line );    // energy use by month & total
                           ParseCSV( line, lines );      assert( lines.size() > 0 );
                           k = -1;
                           while (iaColIdx[++k] >= 0)
                           {  if (lines.size() > 0 && lines[0].size() > iaColIdx[k] && lines[0][iaColIdx[k]].length() > 0)
                              {  dTemp = std::stod( lines[0][iaColIdx[k]] ) * dvDwellWeight[j] * daEnduseMult[iEU];
                                 BEMPX_SetBEMData( BEMPX_GetDatabaseID( pszMoUsageByEUProps[iEU][k], iBDBCID_CUACResults ), BEMP_Flt, (void*) &dTemp, 
                                                   BEMO_User, ivDwellResultsObjIdx[j], BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }  }  }
                     }

                     getline( in, line );    // blank                                                 - SAC 11/05/24
                     getline( in, line );    // Electric kWh Usage by End Use:
                     getline( in, line );    // Unit Type ... (& months/total) label row
                     const char* pszElecUsageByEUProps[11][14] =  { {  "CkgElecUse[14]", "CkgElecUse[13]", "CkgElecUse[1]", "CkgElecUse[2]", "CkgElecUse[3]", "CkgElecUse[4]", "CkgElecUse[5]",
                                                                    "CkgElecUse[6]", "CkgElecUse[7]", "CkgElecUse[8]", "CkgElecUse[9]", "CkgElecUse[10]", "CkgElecUse[11]", "CkgElecUse[12]"  },
                                                                 {  "ClgElecUse[14]", "ClgElecUse[13]", "ClgElecUse[1]", "ClgElecUse[2]", "ClgElecUse[3]", "ClgElecUse[4]", "ClgElecUse[5]",
                                                                    "ClgElecUse[6]", "ClgElecUse[7]", "ClgElecUse[8]", "ClgElecUse[9]", "ClgElecUse[10]", "ClgElecUse[11]", "ClgElecUse[12]"  },
                                                                 {  "DHWElecUse[14]", "DHWElecUse[13]", "DHWElecUse[1]", "DHWElecUse[2]", "DHWElecUse[3]", "DHWElecUse[4]", "DHWElecUse[5]",
                                                                    "DHWElecUse[6]", "DHWElecUse[7]", "DHWElecUse[8]", "DHWElecUse[9]", "DHWElecUse[10]", "DHWElecUse[11]", "DHWElecUse[12]"  },
                                                                 {  "DishElecUse[14]", "DishElecUse[13]", "DishElecUse[1]", "DishElecUse[2]", "DishElecUse[3]", "DishElecUse[4]", "DishElecUse[5]",
                                                                    "DishElecUse[6]", "DishElecUse[7]", "DishElecUse[8]", "DishElecUse[9]", "DishElecUse[10]", "DishElecUse[11]", "DishElecUse[12]"  },
                                                                 {  "DryerElecUse[14]", "DryerElecUse[13]", "DryerElecUse[1]", "DryerElecUse[2]", "DryerElecUse[3]", "DryerElecUse[4]", "DryerElecUse[5]",
                                                                    "DryerElecUse[6]", "DryerElecUse[7]", "DryerElecUse[8]", "DryerElecUse[9]", "DryerElecUse[10]", "DryerElecUse[11]", "DryerElecUse[12]"  },
                                                                 {  "HtgElecUse[14]", "HtgElecUse[13]", "HtgElecUse[1]", "HtgElecUse[2]", "HtgElecUse[3]", "HtgElecUse[4]", "HtgElecUse[5]",
                                                                    "HtgElecUse[6]", "HtgElecUse[7]", "HtgElecUse[8]", "HtgElecUse[9]", "HtgElecUse[10]", "HtgElecUse[11]", "HtgElecUse[12]"  },
                                                                 {  "IAQVentElecUse[14]", "IAQVentElecUse[13]", "IAQVentElecUse[1]", "IAQVentElecUse[2]", "IAQVentElecUse[3]", "IAQVentElecUse[4]", "IAQVentElecUse[5]",
                                                                    "IAQVentElecUse[6]", "IAQVentElecUse[7]", "IAQVentElecUse[8]", "IAQVentElecUse[9]", "IAQVentElecUse[10]", "IAQVentElecUse[11]", "IAQVentElecUse[12]"  },
                                                                 {  "LtgElecUse[14]", "LtgElecUse[13]", "LtgElecUse[1]", "LtgElecUse[2]", "LtgElecUse[3]", "LtgElecUse[4]", "LtgElecUse[5]",
                                                                    "LtgElecUse[6]", "LtgElecUse[7]", "LtgElecUse[8]", "LtgElecUse[9]", "LtgElecUse[10]", "LtgElecUse[11]", "LtgElecUse[12]"  },
                                                                 {  "PlugLdsElecUse[14]", "PlugLdsElecUse[13]", "PlugLdsElecUse[1]", "PlugLdsElecUse[2]", "PlugLdsElecUse[3]", "PlugLdsElecUse[4]", "PlugLdsElecUse[5]",
                                                                    "PlugLdsElecUse[6]", "PlugLdsElecUse[7]", "PlugLdsElecUse[8]", "PlugLdsElecUse[9]", "PlugLdsElecUse[10]", "PlugLdsElecUse[11]", "PlugLdsElecUse[12]"  },
                                                                 {  "RfrgElecUse[14]", "RfrgElecUse[13]", "RfrgElecUse[1]", "RfrgElecUse[2]", "RfrgElecUse[3]", "RfrgElecUse[4]", "RfrgElecUse[5]",
                                                                    "RfrgElecUse[6]", "RfrgElecUse[7]", "RfrgElecUse[8]", "RfrgElecUse[9]", "RfrgElecUse[10]", "RfrgElecUse[11]", "RfrgElecUse[12]"  },
                                                                 {  "WashElecUse[14]", "WashElecUse[13]", "WashElecUse[1]", "WashElecUse[2]", "WashElecUse[3]", "WashElecUse[4]", "WashElecUse[5]",
                                                                    "WashElecUse[6]", "WashElecUse[7]", "WashElecUse[8]", "WashElecUse[9]", "WashElecUse[10]", "WashElecUse[11]", "WashElecUse[12]"  }  };
                     //double daEnduseMult[] = { 1.0, 1.0, 1.0, 1.0, 1.0, -1.0 };
                     for (j=0; j < iNumDwellTypes; j++)
                     {  int iaColIdx[]  = {  4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1 };
                        //getline( in, line );       // <enduse> <fuel> Usage
                        for (int iEU=0; iEU<11; iEU++)
                        {  getline( in, line );    // energy use by avg day, total & month
                           ParseCSV( line, lines );      assert( lines.size() > 0 );
                           k = -1;
                           while (iaColIdx[++k] >= 0)
                           {  if (lines.size() > 0 && lines[0].size() > iaColIdx[k] && lines[0][iaColIdx[k]].length() > 0)
                              {  dTemp = std::stod( lines[0][iaColIdx[k]] ) * dvDwellWeight[j];  // * daEnduseMult[iEU];
                                 BEMPX_SetBEMData( BEMPX_GetDatabaseID( pszElecUsageByEUProps[iEU][k], iBDBCID_CUACResults ), BEMP_Flt, (void*) &dTemp, 
                                                   BEMO_User, ivDwellResultsObjIdx[j], BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }  }  }
                     }

                     getline( in, line );    // blank
                     getline( in, line );    // Gas kBtu Usage by End Use:
                     getline( in, line );    // Unit Type ... (& months/total) label row
                     const char* pszGasUsageByEUProps[4][14] =  {  { "CkgGasUse[14]", "CkgGasUse[13]", "CkgGasUse[1]", "CkgGasUse[2]", "CkgGasUse[3]", "CkgGasUse[4]", "CkgGasUse[5]",
                                                                     "CkgGasUse[6]", "CkgGasUse[7]", "CkgGasUse[8]", "CkgGasUse[9]", "CkgGasUse[10]", "CkgGasUse[11]", "CkgGasUse[12]"  },
                                                                   { "DHWGasUse[14]", "DHWGasUse[13]", "DHWGasUse[1]", "DHWGasUse[2]", "DHWGasUse[3]", "DHWGasUse[4]", "DHWGasUse[5]",
                                                                     "DHWGasUse[6]", "DHWGasUse[7]", "DHWGasUse[8]", "DHWGasUse[9]", "DHWGasUse[10]", "DHWGasUse[11]", "DHWGasUse[12]"  },
                                                                   { "DryerGasUse[14]", "DryerGasUse[13]", "DryerGasUse[1]", "DryerGasUse[2]", "DryerGasUse[3]", "DryerGasUse[4]", "DryerGasUse[5]",
                                                                     "DryerGasUse[6]", "DryerGasUse[7]", "DryerGasUse[8]", "DryerGasUse[9]", "DryerGasUse[10]", "DryerGasUse[11]", "DryerGasUse[12]"  },
                                                                   { "HtgGasUse[14]", "HtgGasUse[13]", "HtgGasUse[1]", "HtgGasUse[2]", "HtgGasUse[3]", "HtgGasUse[4]", "HtgGasUse[5]",
                                                                     "HtgGasUse[6]", "HtgGasUse[7]", "HtgGasUse[8]", "HtgGasUse[9]", "HtgGasUse[10]", "HtgGasUse[11]", "HtgGasUse[12]"  }  };
                     for (j=0; j < iNumDwellTypes; j++)
                     {  int iaColIdx[]  = {  4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1 };
                        //getline( in, line );       // <enduse> <fuel> Usage
                        for (int iEU=0; iEU<4; iEU++)
                        {  getline( in, line );    // energy use by avg day, total & month
                           ParseCSV( line, lines );      assert( lines.size() > 0 );
                           k = -1;
                           while (iaColIdx[++k] >= 0)
                           {  if (lines.size() > 0 && lines[0].size() > iaColIdx[k] && lines[0][iaColIdx[k]].length() > 0)
                              {  dTemp = std::stod( lines[0][iaColIdx[k]] ) * dvDwellWeight[j];  // * daEnduseMult[iEU];
                                 BEMPX_SetBEMData( BEMPX_GetDatabaseID( pszGasUsageByEUProps[iEU][k], iBDBCID_CUACResults ), BEMP_Flt, (void*) &dTemp, 
                                                   BEMO_User, ivDwellResultsObjIdx[j], BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                        }  }  }
                     }


//      BEMPX_SetBEMData( lDBID_CombineResultsOutput, BEMP_Str, (void*) sOutputMsg.c_str(), 
//                     BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );


// 0,  "CUACCombine",    "CalUtilityAllowanceCalcCombine",   "CUACCombine <i>",    0,  0,  0, "Proj",    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   1000
// 
//    CUACResultsRef[4] = UVal: "3bedrm results"


// 0,  "CUACResults",    "CalUtilityAllowanceCalcResults",   "CUACResults <i>",    0,  0,  0, "Proj",    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   1000
// ;
// ;                                                 VType     NV  WA  SP    US    UL                 UT  NO  OC            CV  CP      HI    LName                 
// ;                                                -----------------------------------------------------------------------------------------------------
// 1,           "CombineBdrmIdx",                    BEMP_Int,  1,  0,  0,  Pres,  "",                 0,  0,                           1001, "CombineBdrmIdx",  ""   ; 1-Studio, 2-1bdrm, ... 7-6bdrm   - SAC 10/27/24 (tic #1386)
// 1,           "CombineWeight",                     BEMP_Flt,  1,  0,  0,  Pres,  "",                 0,  0,                           1001, "CombineWeight",  "" 
// 
// 1,           "TotCosts",                          BEMP_Flt,  2,  1,  0,  Pres,  "$",                0,  0,                           1001, "TotalCosts",  ""   ; 1-Annual, 2-Monthly
// 1,           "ElecCosts",                         BEMP_Flt, 14,  1,  0,  Pres,  "$",                0,  0,                           1001, "ElectricityCosts",   ""  ; 1-Annual, 2-MonthlyAvg, 3-14-Monthly
// 1,           "ElecCostPerEnergyUse",              BEMP_Flt,  1,  0,  0,  Pres,  "$/kWh",            0,  0,                           1001, "ElectricityCostPerEnergyUse",   ""   ; SAC 09/28/23
// 1,           "ElecEnergyUsed",                    BEMP_Flt,  1,  0,  0,  Pres,  "kWh",              0,  0,                           1001, "ElectricityEnergyUsed",   ""         ; SAC 09/28/23
// 1,           "GasCosts",                          BEMP_Flt, 14,  1,  0,  Pres,  "$",                0,  0,                           1001, "GasCosts",    ""         ; "
// 1,           "GasCostPerEnergyUse",               BEMP_Flt,  1,  0,  0,  Pres,  "$/therm",          0,  0,                           1001, "GasCostPerEnergyUse",   ""     ; SAC 09/28/23
// 1,           "GasEnergyUsed",                     BEMP_Flt,  1,  0,  0,  Pres,  "therms",           0,  0,                           1001, "GasEnergyUsed",   ""           ; SAC 09/28/23
// 1,           "WaterCosts",                        BEMP_Flt, 14,  1,  0,  Pres,  "$",                0,  0,                           1001, "WaterCosts",  ""   ; 1-Annual, 2-MonthlyAvg, 3-14-Monthly
// 1,           "TrashMonthlyCost",                  BEMP_Flt,  1,  0,  0,  Pres,  "$",                0,  0,                           1001, "TrashMonthlyCost",  "" 
// 1,           "Allowances",                        BEMP_Flt, 15,  1,  0,  Pres,  "$",                0,  0,                           1001, "Allowances",  ""   ; (based on Submittal Report)
// 
// 1,           "CkgElecUse",                        BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "CookingElectricityUse",  ""   ; 1-12:monthly, 13:annual, 14:daily
// 1,           "CkgGasUse",                         BEMP_Flt, 14,  1,  0,  Pres,  "therm",            0,  0,                           1001, "CookingGasUse",  ""     ; fix unit label: kBtu -> therm - SAC 02/09/23
// 1,           "ClgElecUse",                        BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "CoolingElectricityUse",  "" 
// 1,           "DHWElecUse",                        BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "DHWElectricityUse",  ""  
// 1,           "DHWGasUse",                         BEMP_Flt, 14,  1,  0,  Pres,  "therm",            0,  0,                           1001, "DHWGasUse",  ""  
// 1,           "DishElecUse",                       BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "DishwasherElectricityUse",  ""  
// 1,           "DryerElecUse",                      BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "DryerElectricityUse",  ""  
// 1,           "DryerGasUse",                       BEMP_Flt, 14,  1,  0,  Pres,  "therm",            0,  0,                           1001, "DryerGasUse",  ""  
// 1,           "HtgElecUse",                        BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "HeatingElectricityUse",  ""  
// 1,           "HtgGasUse",                         BEMP_Flt, 14,  1,  0,  Pres,  "therm",            0,  0,                           1001, "HeatingGasUse",  ""  
// 1,           "IAQVentElecUse",                    BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "IndoorAirQualityVentilationElectricityUse",  ""     ; SAC 10/19/22
// 1,           "LtgElecUse",                        BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "LightingElectricityUse",  ""  
// 1,           "PlugLdsElecUse",                    BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "PlugLoadsElectricityUse",  ""  
// 1,           "RfrgElecUse",                       BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "RefrigeratorElectricityUse",  ""  
// 1,           "WashElecUse",                       BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "WasherElectricityUse",  ""  
// 1,           "PVSysElecUse",                      BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "PhotovoltaicSystemElectricityUse",  "" 
// 1,           "TotalElecUse",                      BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "TotalElectricityUse",  ""   ; 1-12:monthly, 13:annual, 14:daily
// 1,           "TotalGasUse",                       BEMP_Flt, 14,  1,  0,  Pres,  "therm",            0,  0,                           1001, "TotalGasUse",  ""  
// 1,           "BillingElecUse",                    BEMP_Flt, 14,  1,  0,  Pres,  "kWh",              0,  0,                           1001, "BillingElectricityUse",  ""   ; 1-12:monthly, 13:annual, 14:daily   ; SAC 12/10/22
// 
// 1,           "WaterUse",                          BEMP_Flt, 14,  1,  0,  Pres,  "gallons",          0,  0,                           1001, "WaterUse",  ""   ; 1-12:monthly, 13:annual, 14:daily


                  }


                  if (bErrorInThisFile)
                     iRetVal = (iRetVal < 0 ? iRetVal-1 : -1);
                  else if (iRetVal >= 0)
                     iRetVal++;

   }  }  }  }  }

   // setup certain high-level data for output to Combined reports - SAC 10/31/24
   int iPrevRuleErrs = BEMPX_GetRulesetErrorCount(); 
   if (iRetVal > 0)
   {  
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:WeatherFileNameRpt" ), BEMP_Str, (void*) sWthrFile.c_str(),      BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ElecUtilityRpt"     ), BEMP_Str, (void*) sElecUtil.c_str(),      BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritoryRpt" ), BEMP_Str, (void*) sElecTerr.c_str(),      BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:G2ElecTariffRpt"    ), BEMP_Str, (void*) sElecRate.c_str(),      BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ElecTariffTypeRpt"  ), BEMP_Str, (void*) eElecRateType.c_str(),  BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ElecTariffAdjRpt"   ), BEMP_Str, (void*) sElecRateAdj.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:GasUtilityRpt"      ), BEMP_Str, (void*) sGasUtil.c_str(),       BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:G2GasTerritoryRpt"  ), BEMP_Str, (void*) sGasTerr.c_str(),       BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:G2GasTariffRpt"     ), BEMP_Str, (void*) sGasRate.c_str(),       BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:GasTariffTypeRpt"   ), BEMP_Str, (void*) sGasRateType.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (lProjZipCodeRpt > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjZipCodeRpt"  ), BEMP_Int, (void*) &lProjZipCodeRpt,       BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (dProjectIDRpt != -999)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjectIDRpt"    ), BEMP_Int, (void*) &dProjectIDRpt,         BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (sProjStAddressRpt.compare("(multiple)")==0 && sProjCityRpt.compare("(multiple)")==0)
      {  sProjCityRpt.clear();   sProjStateRpt.clear();   
      }
      if (sOwnerAddressRpt.compare("(multiple)")==0 && sOwnerCityRpt.compare("(multiple)")==0)
      {  sOwnerCityRpt.clear();   sOwnerStateRpt.clear();   sOwnerZIPCodeRpt.clear();
      }

      if (sProjStAddressRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjStAddressRpt" ), BEMP_Str, (void*) sProjStAddressRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjCityRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjCityRpt" ), BEMP_Str, (void*) sProjCityRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjStateRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjStateRpt" ), BEMP_Str, (void*) sProjStateRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOwnerNameRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OwnerNameRpt" ), BEMP_Str, (void*) sOwnerNameRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOwnerAddressRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OwnerAddressRpt" ), BEMP_Str, (void*) sOwnerAddressRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOwnerCityRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OwnerCityRpt" ), BEMP_Str, (void*) sOwnerCityRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOwnerStateRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OwnerStateRpt" ), BEMP_Str, (void*) sOwnerStateRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOwnerZIPCodeRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OwnerZIPCodeRpt" ), BEMP_Str, (void*) sOwnerZIPCodeRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sContactNameRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ContactNameRpt" ), BEMP_Str, (void*) sContactNameRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sContactPhoneRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ContactPhoneRpt" ), BEMP_Str, (void*) sContactPhoneRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sContactEMailRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ContactEMailRpt" ), BEMP_Str, (void*) sContactEMailRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (sLocalityRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:LocalityRpt" ), BEMP_Str, (void*) sLocalityRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sUnitTypeRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:UnitTypeRpt" ), BEMP_Str, (void*) sUnitTypeRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sAPNRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:APNRpt" ), BEMP_Str, (void*) sAPNRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sOtherProjectIDRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:OtherProjectIDRpt" ), BEMP_Str, (void*) sOtherProjectIDRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sReportTypeRpt.length() > 0)    // SAC 11/12/24
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ReportTypeRpt" ), BEMP_Str, (void*) sReportTypeRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjNameRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjNameRpt" ), BEMP_Str, (void*) sProjNameRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjGasTypeRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjGasTypeRpt" ), BEMP_Str, (void*) sProjGasTypeRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjSoftwareVersionRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjSoftwareVersionRpt" ), BEMP_Str, (void*) sProjSoftwareVersionRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sProjCompManagerVersionRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:ProjCompManagerVersionRpt" ), BEMP_Str, (void*) sProjCompManagerVersionRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sTariffDateRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:TariffDateRpt" ), BEMP_Str, (void*) sTariffDateRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sRunDateFmtRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:RunDateFmtRpt" ), BEMP_Str, (void*) sRunDateFmtRpt.c_str(),   BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );


//         case  5 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerZIPCode"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case  6 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"    ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case  7 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactPhone"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case  8 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactEMail"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case  9 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj"   ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:APN"            ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case 10 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"      ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OtherProjectID" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
//         case 11 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTerritory"  ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;
//         case 12 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTariff"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;
//         case 13 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariffType"   ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;     // SAC 01/25/24
//
//
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:StAddress" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:City"    ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:State"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ZipCode" ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerName"      ), qsLabel2, FAL
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerAddress"   ), qsLabel2, FAL
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerCity"      ), qsLabel2, FAL
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerState"     ), qsLabel2, FAL
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerZIPCode"   ), qsLabel2, 
//
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"    ), qsLabel2, 
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactPhone"   ), qsLabel2, 
//   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactEMail"   ), qsLabel2, 
//
//   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
//   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
//   if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TariffDate" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
//   if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), qsRunDateFmt, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsRunDateFmt.isEmpty())
//
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Name" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      // SAC 01/04/23
//      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ProjectID" ), qsLabel,  FALSE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:GasType" ), qsTemp, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );     // ported (revised) from Details report - SAC 09/21/23
//      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:Locality" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:APN"            ), qsLabel2, 
//      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OtherProjectID" ), qsLabel2, 
//
//   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
//   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:AffordableUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0)
//            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//         if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumDwellingUnitsByBedrms", iResProjClassID )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp >= laNumUnitsByBedrms[iMtr])
//
//   BEMPX_GetString(      BEMPX_GetDatabaseID( "CUAC:TrashRateType"    ), qsLabel  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:TrashRateType"    ), lRateType,        0, -1, 0, BEMO_User, iBEMProcIdx ) && lRateType > 0)  // prevent reporting invalid trash costs - SAC 09/14/23
//      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:TrashMonthlyCost" ), qsTemp   ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//
//   BEMPX_GetString(      BEMPX_GetDatabaseID( "CUAC:WaterRateType"    ), qsLabel  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:WaterRateType"    ), lRateType,        0, -1, 0, BEMO_User, iBEMProcIdx ) && lRateType > 0)  // prevent reporting invalid water costs - SAC 09/14/23
//      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:WaterMonthlyCost" ), qsTemp   ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//   {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:WaterVolumeCost"  ), qsTemp , TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel3 = QString( "$ %1" ).arg( qsTemp );
//
//   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:UseCommunitySolar"     ), lTemp, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lTemp > 0 &&
//       BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:TotCommunitySolarSize" ), dTemp, 0, -1, 0, BEMO_User, iBEMProcIdx ) && dTemp > 0.1)
//      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarProject" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//
//      for (int iMtr=0; iMtr < lNumUnitTypes; iMtr++)
//            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//            if (BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarSizeByBedrms"      )+iMtrIdx, dCSPV  , 0, -1, 0, BEMO_User, iBEMProcIdx ) && dCSPV   > 0.01 &&
//                BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarAnnCreditByBedrms" )+iMtrIdx, dCSCred, 0, -1, 0, BEMO_User, iBEMProcIdx ) && dCSCred > 0.01)
//               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:CommunitySolarSizeByBedrms"      )+iMtrIdx, qsLabel, TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel += " kW";
//      for (int iMtr=0; iMtr < lNumUnitTypes; iMtr++)
//               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:PctIndivUnitPVByBedrms" )+iMtrIdx, qsLabel, TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel += " %";
//               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:IndivUnitPVByBedrms"    )+iMtrIdx, qsLabel, TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );



// IS THERE A NEED TO EVALUATE CUAC_FinalCalcs - or a variation there of??
//                     if (bWriteCombineDetails) 
//                        BEMPX_WriteLogFile( QString( "  CUAC_CombineReports - CUAC_FinalCalcs rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//      BOOL bFinalResultsCalcsEvalSuccessful = CMX_EvaluateRuleset( "CUAC_FinalCalcs" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
//      BEMPX_RefreshLogFile();
//      if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
//      {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
//                        BEMPX_WriteLogFile( QString( "  CUAC_CombineReports - errors encountered evaluating CUAC_FinalCalcs rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//         return;
//      }


      if (iTotNumInvalidAnalyses > 1)     // SAC 01/03/25
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:NumInvalidAnalyses" ), BEMP_Int, (void*) &iTotNumInvalidAnalyses,  BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      if (sSingleInvalidAnalysisMsg.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:AnalysisInvalidMsg" ), BEMP_Str, (void*) sSingleInvalidAnalysisMsg.c_str(),  BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (sCommunitySolarProjRpt.length() > 0)
         BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:CommunitySolarProjRpt" ), BEMP_Str, (void*) sCommunitySolarProjRpt.c_str(),  BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );

      if (!CMX_EvaluateRuleset( "CUAC_SetupReportingProperties_Combined" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ ))   //, &saPreAnalChkWarningMsgs );
      {  // error - evaluating rule: CUAC_SetupReportingProperties_Combined
         iRetVal = -1;
         sErrorMsg += "Error: evaluating rulelist 'CUAC_SetupReportingProperties_Combined'\r\n";
      }

      // testing / debugging
      if (bWriteCombineDetails)
         BEMPX_WriteProjectFile( sOutPathFileDbg[1].c_str(), BEMFM_DETAIL, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
                                 false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, iCUAC_BEMProcIdx, -1, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );
   }

   // write CUAC input/output details CSV file (via ruleset) - SAC 11/06/24
   if (iRetVal > 0)
   {
      QString sIOCSVPathFile = sOutPathFileCSV.c_str();  // BEMPX_GetString( BEMPX_GetDatabaseID( "InOutCSVPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
      if (sIOCSVPathFile.isEmpty())
      //   BEMPX_WriteLogFile( QString( "CUAC:InOutCSVPathFile undefined - needed for input/output CSV export" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      {  iRetVal = -1;
         sErrorMsg += "Error: CUAC input/output details CSV export path/file name undefined\r\n";
      }
      else
      {  QString sMsg;
         sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                      "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                      "(once the file is closed), or \n'Abort' to abort the %s.", "CSV", sIOCSVPathFile.toLocal8Bit().constData(), "CSV export" );
         if (!OKToWriteOrDeleteFile( sIOCSVPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
         //   BEMPX_WriteLogFile( QString( "Unable to write CUAC input/output CSV export file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         {  iRetVal = -1;
            sErrorMsg += "Error: Unable to write CUAC input/output CSV export file:\r\n";
            sErrorMsg += sIOCSVPathFile.toLocal8Bit().constData();   sErrorMsg += "\r\n";
         }
         else
         {
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:InOutCSVPathFile" ), BEMP_QStr, (void*) &sIOCSVPathFile, BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     if (bWriteCombineDetails) 
                        BEMPX_WriteLogFile( QString( "  CUAC_CombineReports - CUAC_WriteInputOutputCSV rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            BOOL bIOCSVExportEvalSuccessful = CMX_EvaluateRuleset( "CUAC_WriteInputOutputCSV" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );   //, &saPreAnalChkWarningMsgs );
            BEMPX_RefreshLogFile();
            if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
            {  //bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
               //      BEMPX_WriteLogFile( QString( "  CUAC_CombineReports - errors encountered evaluating CUAC_WriteInputOutputCSV rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               //return;
               iRetVal = -1;
               sErrorMsg += "Errors encountered evaluating CUAC_WriteInputOutputCSV rules\r\n";
            }
         //   else if (!bOldCUAC)
         //   {  // HOURLY simulation results - SAC 09/18/23
         //      // append all hourly results to end of CSV file - SAC 10/20/22
         //      FILE *fp_CSV;
         //      int iErrorCode;
         //      try
         //      {
         //         iErrorCode = fopen_s( &fp_CSV, sIOCSVPathFile.toLocal8Bit().constData(), "ab" );   // APPEND to CSV
         //         if (iErrorCode != 0 || fp_CSV == NULL)
         //            BEMPX_WriteLogFile( QString( "Error encountered opening CUAC CSV results file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         //         else
         //         {  double *pdHrlyUse[120];   // max should be NumDwellingMeters * (NumElecEnduses + NumGasEnduses)
         //            int iHrlyUsePtrIdx = 0, iNumRptgMtrs = 0;
         //            QString saCSVColLabels[3];
         //            saCSVColLabels[0] = ",,,";    saCSVColLabels[1] = ",,,";    saCSVColLabels[2] = "Mo,Da,Hr,";
         //            for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         //               if (laNumUnitsByBedrms[iMtr] > 0)
         //               {  saCSVColLabels[0] += QString( "%1 Electric Use,,,,,,,,,,,,%2 Gas Use,,,," ).arg( pszCUACCSVUnitTypeLabels[iMtr], pszCUACCSVUnitTypeLabels[iMtr] );
         //                  saCSVColLabels[1] += pszCUACCSVElecEnduseLabels;      saCSVColLabels[1] += pszCUACCSVGasEnduseLabels;
         //                  saCSVColLabels[2] += "(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(therms),(therms),(therms),(therms),";
         //                  iNumRptgMtrs++;
         //                  for (iFuel=0; iFuel<2; iFuel++)
         //                     for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
         //                        if (baHaveFuelEnduseHrlyResults[iFuel][iCEUIdx])
         //                        {  int iInitMtrIdx                  = (iDataModel == 0 ? iaInitToRptsEnduseMap[iCEUIdx]     : iaResInitToRptsEnduseMap[iCEUIdx]     );
         //                           const char* pszHrlyResultsEnduse = (iDataModel == 0 ? pszInitialCUACEnduses[iInitMtrIdx] : pszInitialCUACResEnduses[iInitMtrIdx] );
         //                           pdHrlyUse[iHrlyUsePtrIdx] = NULL;
         //                           int iResMtrIdx = (iFuel == 0 ? 0 : iResFuelMtrIdx);      // SAC 09/11/24 (res tic #1378)
         //                           const char* pszCUACMtr = (iDataModel == 0 ? pszCUACMeters[iFuel][iMtr] : pszCUACResMeters[iResFuelMtrIdx]);    // SAC 05/31/24
         //                           BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse[iHrlyUsePtrIdx], NULL, 0, "Proposed", pszCUACMtr, pszHrlyResultsEnduse, iCUAC_BEMProcIdx );
         //                           if (pdHrlyUse[iHrlyUsePtrIdx] == NULL)
         //                              pdHrlyUse[iHrlyUsePtrIdx] = &daZero[0];      // to prevent CSV writing error when no Gas meter present in model - SAC 02/28/24
         //                           iHrlyUsePtrIdx++;
         //                        }
         //               }  assert( iHrlyUsePtrIdx == (iNumRptgMtrs * 16) );

         //            fprintf( fp_CSV,  "%s\n", saCSVColLabels[0].toLocal8Bit().constData() );   
         //            fprintf( fp_CSV,  "%s\n", saCSVColLabels[1].toLocal8Bit().constData() );   
         //            fprintf( fp_CSV,  "%s\n", saCSVColLabels[2].toLocal8Bit().constData() );   

         //            int iAnnHrIdx=0;
         //            QString qsMtrResStr[NumDwellingMeters];
         //            for (iMo=1; iMo<=12; iMo++)
         //               for (iDay=1; iDay<=iNumDaysInMonth[iMo-1]; iDay++)
         //                  for (iHr=1; iHr<=24; iHr++)
         //                  {  for (iMtr=0; iMtr < iNumRptgMtrs; iMtr++)
         //                     {  int iMtrResColIdx = (iMtr * 16);
         //                        qsMtrResStr[iMtr] = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16," ).arg(
         //                                    QString::number(pdHrlyUse[iMtrResColIdx   ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+1 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+2 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+3 ][iAnnHrIdx]),
         //                                    QString::number(pdHrlyUse[iMtrResColIdx+4 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+5 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+6 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+7 ][iAnnHrIdx]), 
         //                                    QString::number(pdHrlyUse[iMtrResColIdx+8 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+9 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+10][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+11][iAnnHrIdx]), 
         //                                    QString::number(pdHrlyUse[iMtrResColIdx+12][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+13][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+14][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+15][iAnnHrIdx]) );
         //                     }
         //                     switch (iNumRptgMtrs)
         //                     {  case  1 :  fprintf( fp_CSV,  "%d,%d,%d,%s\n",             iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData() );   break;
         //                        case  2 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s\n",           iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData() );   break;
         //                        case  3 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s\n",         iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData() );   break;
         //                        case  4 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s\n",       iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData() );   break;
         //                        case  5 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s\n",     iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
         //                                                                                                  qsMtrResStr[4].toLocal8Bit().constData() );   break;
         //                        case  6 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s%s\n",   iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
         //                                                                                                  qsMtrResStr[4].toLocal8Bit().constData(), qsMtrResStr[5].toLocal8Bit().constData() );   break;
         //                        case  7 :  fprintf( fp_CSV,  "%d,%d,%d,%s%s%s%s%s%s%s\n", iMo, iDay, iHr, qsMtrResStr[0].toLocal8Bit().constData(), qsMtrResStr[1].toLocal8Bit().constData(), qsMtrResStr[2].toLocal8Bit().constData(), qsMtrResStr[3].toLocal8Bit().constData(),
         //                                                                                                  qsMtrResStr[4].toLocal8Bit().constData(), qsMtrResStr[5].toLocal8Bit().constData(), qsMtrResStr[6].toLocal8Bit().constData() );   break;
         //                     }  iAnnHrIdx++;
         //                  }
         //            fflush( fp_CSV );
         //            fclose( fp_CSV );
         //         }
         //      }
         //      catch( ... ) {
         //         //iRetVal = 4;
         //         //sErrMsg = QString::asprintf( "Unknown error writing hourly CSV results file:  %s", sIOCSVPathFile.toLocal8Bit().constData() );
         //         BEMPX_WriteLogFile( QString( "Unknown error writing CUAC CSV results file:  %1" ).arg( sIOCSVPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         //      }
         //   }
      }  }


      // testing / debugging
      if (bWriteCombineDetails)
         BEMPX_WriteProjectFile( sOutPathFileDbg[2].c_str(), BEMFM_DETAIL, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
                                 false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, iCUAC_BEMProcIdx, -1, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );

   }

   // PDF report generation - SAC 11/06/24
   if (iRetVal > 0)
   {
      int iRptID=0;
      QString sSubmitPDFPathFile = sOutPathFilePDFS.c_str();  // BEMPX_GetString( BEMPX_GetDatabaseID( "SubmitPDFPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
      if (sSubmitPDFPathFile.isEmpty())
      //   BEMPX_WriteLogFile( QString( "CUAC:SubmitPDFPathFile undefined - needed for submittal report PDF generation" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      {  iRetVal = -1;
         sErrorMsg += "Error: CUAC submittal report PDF path/file name undefined\r\n";
      }
      else
      {  QString sMsg;
         sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                      "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                      "(once the file is closed), or \n'Abort' to abort the %s.", "PDF", sSubmitPDFPathFile.toLocal8Bit().constData(), "PDF report generation" );
         if (!OKToWriteOrDeleteFile( sSubmitPDFPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
         //   BEMPX_WriteLogFile( QString( "Unable to write CUAC submittal report PDF file:  %1" ).arg( sSubmitPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         {  iRetVal = -1;
            sErrorMsg += "Error: Unable to write CUAC submittal report PDF file:\r\n";
            sErrorMsg += sSubmitPDFPathFile.toLocal8Bit().constData();   sErrorMsg += "\r\n";
         }
         else
         {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:SubmitPDFPathFile" ), BEMP_QStr, (void*) &sSubmitPDFPathFile, BEMO_User, 0, BEMS_ProgDefault, BEMO_User, TRUE, iCUAC_BEMProcIdx );
            iRptID = 2;  // default to Final
            if (boost::iequals( sReportTypeRpt, "Draft" ))
               iRptID = 1;
            else if (boost::iequals( sReportTypeRpt, "Annual" ))
               iRptID = 3;

            int iPDFGenRetVal = BEMPX_GeneratePDF( sSubmitPDFPathFile.toLocal8Bit().constData(), pszRptGraphicsPath, iRptID, iCUAC_BEMProcIdx, iDataModel );
            BEMPX_WriteLogFile( QString( "CUAC submittal report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sSubmitPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

            if (iPDFGenRetVal == 0)    // details report - SAC 01/03/23
            {  // same here for Details report
               QString sDetailsPDFPathFile = sOutPathFilePDFD.c_str();  // BEMPX_GetString( BEMPX_GetDatabaseID( "DetailsPDFPathFile", iCID_CUAC ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
               if (sDetailsPDFPathFile.isEmpty())
                  BEMPX_WriteLogFile( QString( "CUAC:DetailsPDFPathFile undefined - needed for details report PDF generation" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               else
               {  QString sMsg;
                  sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
                               "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                               "(once the file is closed), or \n'Abort' to abort the %s.", "PDF", sDetailsPDFPathFile.toLocal8Bit().constData(), "PDF report generation" );
                  if (!OKToWriteOrDeleteFile( sDetailsPDFPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
                     BEMPX_WriteLogFile( QString( "Unable to write CUAC details report PDF file:  %1" ).arg( sDetailsPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  else
                  {
                     iRptID += 10;
                     int iPDFGenRetVal = BEMPX_GeneratePDF( sDetailsPDFPathFile.toLocal8Bit().constData(), pszRptGraphicsPath, iRptID, iCUAC_BEMProcIdx, iDataModel );
                     BEMPX_WriteLogFile( QString( "CUAC details report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sDetailsPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                     if (iPDFGenRetVal != 0)
                     {  iRetVal = -1;
                        sErrorMsg += "Error writing CUAC details PDF report file:\r\n";
                        sErrorMsg += sDetailsPDFPathFile.toLocal8Bit().constData();   sErrorMsg += "\r\n";
                     }
               }  }
            }
            else
            {  iRetVal = -1;
               sErrorMsg += "Error writing CUAC submittal PDF report file:\r\n";
               sErrorMsg += sSubmitPDFPathFile.toLocal8Bit().constData();   sErrorMsg += "\r\n";
            }

            int iGotHere = 1;
      }  }

   }

   // call rulelist to delete all CUACCombine & CUACResults objects - SAC 11/06/24
   CMX_EvaluateRuleset( "CUAC_CombineReportsCleanup" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );   //, &saPreAnalChkWarningMsgs );

      // testing / debugging
      if (bWriteCombineDetails)
         BEMPX_WriteProjectFile( sOutPathFileDbg[3].c_str(), BEMFM_DETAIL, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
                                 false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, iCUAC_BEMProcIdx, -1, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );



//      "ResultsCSVToCombineDir",            BEMP_Str,  1,  0,  0,   Opt,  "",                 0,  0,                           1005, "Directory where detailed CUAC results CSV files to be combined are located",  ""   ; SAC 10/24/24 (tic #1386)
//      "ResultsCSVToCombine",               BEMP_Str, 20,  1,  0,   Opt,  "",                 0,  0,                           1005, "CSV file containing detailed CUAC results to be combined with others",  ""   ; SAC 10/23/24 (tic #1386)
//      "CombinedResultsFile",               BEMP_Str,  1,  0,  0,   Opt,  "",                 0,  0,                           1005, "Path and file name that is the basis of the combined CUAC results files",  "" 
//      "LastResultsToCombineIdx",           BEMP_Int,  1,  0,  0,  NInp,  "",                 0,  0,                          39110, "1-based index of last defined ResultsCSVToCombine",    "" 
//      "CombineResultsOutput",              BEMP_Str,  1,  0,  0,  NInp,  "",                 0,  0,                           1005, "Notes/Errors resulting from CUAC report combining process",  ""   ; SAC 10/26/24 (tic #1386)
//      "ShowCombineResultsOutput",          BEMP_Int,  1,  0,  0,  NInp,  "",                 0,  0,                           1005, "whether or not to show Notes/Errors resulting from CUAC report combining process",  "" 



//	std::ifstream in( pszBatchPathFile );
//	if (!in.is_open())
//	{	if (pszErrorMsg && iErrorMsgLen > 0)
//			sprintf_s( pszErrorMsg, iErrorMsgLen, "Error opening batch definitions file:  %s", pszBatchPathFile );
//									return -10;
//	}


//				std::ifstream bemInFile(  sProjPathFile );
//				std::ofstream bemOutFile( saProjOutFN[iRun] );  //, std::ios_base::binary | std::ios_base::app );


//			QString sResFile = QString( "%1%2.csv" ).arg( sProcessPath, sModelFileOnlyNoExt );
////QString sDbgMsg = QString( "about to retrieve solar sizing results from:\n%1" ).arg( sResFile );
////BEMMessageBox( sDbgMsg );
//			std::ifstream in( sResFile.toLocal8Bit().constData() );
//			if (!in.is_open())
//				sErrMsg = QString::asprintf( "ERROR:  unable to open sizing run results file %s", sResFile.toLocal8Bit().constData() );
//
//			if (sErrMsg.isEmpty())
//			{
//				std::string line;
//				std::vector<std::vector<std::string> > lines;
//				getline( in, line );		// first ver #
//				getline( in, line );		//  hdr 1
//				getline( in, line );		//  hdr 2
//				getline( in, line );		//  hdr 3
//
//            // parse final header line for autosized cseDHWHEATER names (w/ cap & vol results) - SAC 07/08/21 (tic #1275)
//				ParseCSV( line, lines );      assert( lines.size()==1 );
//            if (lines[0].size() > 8 && pasAutoszdCHPWHs)
//            {  for (int iAH=7; (sErrMsg.isEmpty() && iAH < (int) lines[0].size()); iAH+=2)
//               {  std::string sCHPWHName = lines[0][iAH].substr( 0, lines[0][iAH].length()-4 );
//                  if (sCHPWHName.length() < 1)
//   						sErrMsg = QString::asprintf( "ERROR:  unable to parse %s solar sizing run autosized CHPWH name from header '%s'", sRunID.toLocal8Bit().constData(), lines[0][iAH].c_str() );
//                  else
//                     pasAutoszdCHPWHs->push_back( sCHPWHName );
//            }  }


//		BEMPX_SetBEMData( lDBID_RunDate, BEMP_Int, (void*) &lTime );
//      BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -4 /*iPrecision*/ );      // format: "M/d/yyyy h:m:s ap"
//      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), BEMP_QStr, (void*) &sRunDateFmt ); 
//
//      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordablePVDCSysSizeFrac", iCID_CUAC ), dAffordablePVDCSysSizeFrac, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
//      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordableBattMaxCapFrac",  iCID_CUAC ), dAffordableBattMaxCapFrac , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
//         if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "PVAllocMethod", iCID_CUAC ), lPVAllocMethod, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) || lPVAllocMethod == 2)
//
//BOOL    BEMPROC_API __cdecl BEMPX_GetString(  long lDBID, QString& sStr, BOOL bAddCommas=TRUE, int iPrecision=0,		// for backward compatibility with BEMPX_SetDataString
//																	int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//																	const char* pszDefault=NULL, long lDBID2=0, int iBEMProcIdx=-1 );



   if (sOutputMsg.length() > 10)
      sOutputMsg += "\r\n";
   if (iRetVal > 0)
      sOutputMsg += boost::str( boost::format( "%d CUAC reports successfully combined and stored as:\r\n%s - CUAC*.*\r\n" ) % iRetVal % sOutputPathFileBase );
   else
      sOutputMsg += "CUAC report combining unsuccessful.\r\n";

   if (sErrorMsg.length() > 5)
   {  if (sOutputMsg.length() > 10 && bWriteCombineDetails)
         BEMPX_WriteLogFile( sOutputMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      // replace sOutputMsg w/ sErrorMsg (if there IS an error message)
      sOutputMsg = sErrorMsg;
   }

   if (pszOutputMsg && iOutputMsgLen > 0)
   {  if (sOutputMsg.length() >= iOutputMsgLen)
         pszOutputMsg[iOutputMsgLen-1] = '\0';
      //strncpy_s( pszOutputMsg, iOutputMsgLen-1, sOutputMsg.c_str(), sOutputMsg.length() );
      StringCchCopyA( pszOutputMsg, iOutputMsgLen-1, sOutputMsg.c_str() );
   }
      //sprintf_s( pszOutputMsg, iOutputMsgLen, "%s", sOutputMsg.c_str() );

   long lDBID_CombineResultsOutput = BEMPX_GetDatabaseID( "CUAC:CombineResultsOutput" );
   if (lDBID_CombineResultsOutput)
   {  ////QString qsOut = sOutputMsg.c_str();
      //char * cstr = new char [sOutputMsg.length()+1];
      //std::strcpy (cstr, sOutputMsg.c_str());
      //BEMPX_SetBEMData( lDBID_CombineResultsOutput, BEMP_Str, (void*) cstr, 
      //               BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
      //delete [] cstr;
      BEMPX_SetBEMData( lDBID_CombineResultsOutput, BEMP_Str, (void*) sOutputMsg.c_str(), 
                        BEMO_User, -1, BEMS_ProgDefault /*BEMS_UserDefined*/, BEMO_User, TRUE, iCUAC_BEMProcIdx );
   }

   return iRetVal;
}
