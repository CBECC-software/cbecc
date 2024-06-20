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
// CUAC reporting enduses:
#define  NumCUACEnduses  12
static const char* pszOldCUACEnduseProps[NumCUACEnduses+1]    = { "Cooking", "Cooling",    "DHW",   "Dishwasher",  "Dryer",  "Heating",      NULL,   "Lighting", "PlugLoads", "Refrigerator", "Washer", "PVGeneration",  NULL };
static const char* pszCUACRptEnduseAbbrevs[NumCUACEnduses+1]  = {  "Ckg",      "Clg",      "DHW",      "Dish",     "Dryer",    "Htg",      "IAQVent",  "Ltg",      "PlugLds",  "Rfrg",     "Wash",     "PVSys",     NULL };
static int iaInitToRptsEnduseMap[NumCUACEnduses+1]            = {    11,         0,          2,           8,          9,         1,            3,        6,            5,        7,          10,          12,        -1  };
static bool baHaveFuelEnduseHrlyResults[2][NumCUACEnduses]  = { {   true,       true,       true,       true,       true,       true,       true,       true,       true,       true,       true,       true  },
                                                                {   true,      false,       true,      false,       true,       true,      false,      false,      false,      false,      false,      false  } };
static const char* pszCUACCSVElecEnduseLabels                 =    "Cooking,Cooling,DHW,Dishwasher,Dryer,Heating,IAQ Vent,Lighting,Plug Loads,Refrigerator,Washer,PV,";
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

//											96 : Error calculating CUAC utility bill(s)
void CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, char* pszErrorMsg, int iErrorMsgLen,
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iBillCalcDetails /*=-1*/,
                              bool bWritePDF /*=true*/, bool bWriteCSV /*=true*/, int iBatchRunIdx /*=0*/ )
{  // at this point, ruleset object is loaded w/ all hourly results read directly from CSE run(s)
// TEMPORARY
//bVerbose = true;
   //bool bCUACRptVerbose = (iBillCalcDetails < 0 ? bVerbose : (iBillCalcDetails > 0 ? true : false));
   if (iBillCalcDetails < 0)     // replaced bCUACRptVerbose w/ variable iBillCalcDetails - SAC 12/06/23
      iBillCalcDetails = (bVerbose ? 1 : 0);

   int iMtr, iFuel, iMo, iDay, iHr, iTemp, iSpecVal, iErr, iStep = 1;
   long laNumUnitsByBedrms[NumDwellingMeters], lTemp, lNumUnitTypes=0;
   bool bOldCUAC = (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CUAC_OldAccessDB" ), lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0) ? true : false;

   int iPrevRuleErrs = BEMPX_GetRulesetErrorCount();   // add eval of rules to setup utility rates - SAC 09/14/22
                  if (iBillCalcDetails > 0) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupGen1ElecRate & CUAC_SetupGen1GasRate rules (if needed)" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bRateEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupGen1ElecRate" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
      return;
   }
   bRateEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupGen1GasRate" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
      return;
   }

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
      {  laNumUnitsByBedrms[iMtr] = lTemp;
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

//   double daZero[8760];
//   for (iHr=0; iHr<8760; iHr++)
//      daZero[iHr] = 0.0;

   if (!bOldCUAC)
   {
      // Divvy PV & Batt based on PVAllocMethod - SAC 11/21/22
      double dPVAnnual = BEMPX_GetHourlyResultSum(   NULL, 0, "Proposed", "Electricity", "Photovoltaics", NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
      if (dPVAnnual == -99999.0)
         dPVAnnual = 0.0;
      double dBattAnnual = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", "Electricity", "Battery",       NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
      if (dBattAnnual == -99999.0)
         dBattAnnual = 0.0;
      double dAffordablePVDCSysSizeFrac=0.0, dAffordableBattMaxCapFrac=0.0;
      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordablePVDCSysSizeFrac", iCID_CUAC ), dAffordablePVDCSysSizeFrac, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
      BEMPX_GetFloat( BEMPX_GetDatabaseID( "AffordableBattMaxCapFrac",  iCID_CUAC ), dAffordableBattMaxCapFrac , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
      if ( (dPVAnnual != 0.0 || dBattAnnual != 0.0) && (dAffordablePVDCSysSizeFrac > 0 || dAffordableBattMaxCapFrac > 0) )
      {
         double daDwellingPVBattFrac[NumDwellingMeters];
         long lPVAllocMethod=0;     // 0: Num Residents / 1: Electricity Use / 2: User Allocation
         if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "PVAllocMethod", iCID_CUAC ), lPVAllocMethod, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) || lPVAllocMethod == 2)
         {  // Divvy PV/Batt into affordable housing meters by user specified allocation percentages - SAC 12/09/22
            long lNumUnits;
            double dPctIndivPV, dPctIndivPVSum;
            if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "PctIndivUnitPVSum", iCID_CUAC ), dPctIndivPVSum, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) ||
                  dPctIndivPVSum < 99.96 || dPctIndivPVSum > 100.04)
            {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
               sErrMsg = QString( "CUAC Error: Invalid or missing PV allocation by unit type data. Access these inputs via PV Allocation button in CUAC dialog tab." );
               BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               return;
            }
            else
            {  for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
               {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "AffordableUnitsByBedrms", iCID_CUAC )+iMtr, lNumUnits  , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lNumUnits   > 0 &&
                      BEMPX_GetFloat(   BEMPX_GetDatabaseID( "PctIndivUnitPVByBedrms" , iCID_CUAC )+iMtr, dPctIndivPV, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && dPctIndivPV > 0)
                     daDwellingPVBattFrac[iMtr] = (dPctIndivPV * lNumUnits) / 100.0;
                  else
                     daDwellingPVBattFrac[iMtr] = 0.0;
            }  }
         }
         else if (lPVAllocMethod == 0)
         {  // Divvy PV/Batt into affordable housing meters by number of residents - SAC 11/21/22
            for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
               BEMPX_GetFloat( BEMPX_GetDatabaseID( "ResidentFracByBedrms", iCID_CUAC )+iMtr, daDwellingPVBattFrac[iMtr], 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
         }
         else
         {  // Divvy PV/Batt into affordable housing meters by annual dwelling electric use - SAC 09/10/22
            double dTotalAllDwellingElecUse = 0.0;
            for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
            {
               if (laNumUnitsByBedrms[iMtr] < 1)
                  daDwellingPVBattFrac[iMtr] = 0.0;
               else
               {  daDwellingPVBattFrac[iMtr] = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[0][iMtr], pszInitialCUACEnduses[0], pszInitialCUACEnduses[1], pszInitialCUACEnduses[2], pszInitialCUACEnduses[3],
                                                                                                                     pszInitialCUACEnduses[4], pszInitialCUACEnduses[5], pszInitialCUACEnduses[6], pszInitialCUACEnduses[7], iCUAC_BEMProcIdx );
                  if (daDwellingPVBattFrac[iMtr] == -99999.0)
                     daDwellingPVBattFrac[iMtr] = 0.0;
                  double dTemp = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[0][iMtr], pszInitialCUACEnduses[8], pszInitialCUACEnduses[9], pszInitialCUACEnduses[10], pszInitialCUACEnduses[11],
                                                                                                         pszInitialCUACEnduses[12], pszInitialCUACEnduses[13], NULL, NULL, iCUAC_BEMProcIdx );
                  if (dTemp != -99999.0)
                     daDwellingPVBattFrac[iMtr] += dTemp;
                  dTotalAllDwellingElecUse += daDwellingPVBattFrac[iMtr];
            }  }
            assert( dTotalAllDwellingElecUse > 0 );
            if (dTotalAllDwellingElecUse > 0)
               for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
                  if (daDwellingPVBattFrac[iMtr] > 0)
                     daDwellingPVBattFrac[iMtr] = daDwellingPVBattFrac[iMtr] / dTotalAllDwellingElecUse;
         }
               if (iBillCalcDetails > 0)
                  BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - PV allocation fracs:  %1 | %2 | %3 | %4 | %5 | %6 | %7" ).arg( QString::number( daDwellingPVBattFrac[0] ), QString::number( daDwellingPVBattFrac[1] ), QString::number( daDwellingPVBattFrac[2] ), QString::number( daDwellingPVBattFrac[3] ),
                                       QString::number( daDwellingPVBattFrac[4] ), QString::number( daDwellingPVBattFrac[5] ), QString::number( daDwellingPVBattFrac[6] ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

         double *pdPVHrlyData=NULL, *pdBattHrlyData=NULL;
         if (dPVAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdPVHrlyData  , NULL, 0, "Proposed", "Electricity", "Photovoltaics", iCUAC_BEMProcIdx );
         if (dBattAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdBattHrlyData, NULL, 0, "Proposed", "Electricity", "Battery"      , iCUAC_BEMProcIdx );

         for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
            if (daDwellingPVBattFrac[iMtr] > 0)
            {
               // PV
               if (pdPVHrlyData && dAffordablePVDCSysSizeFrac > 0 && daDwellingPVBattFrac[iMtr] > 0)
                  BEMPX_SumIntoHourlyResultArray( pdPVHrlyData, "Proposed", pszCUACMeters[0][iMtr], "Photovoltaics", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordablePVDCSysSizeFrac * daDwellingPVBattFrac[iMtr]) );
               // Battery
               if (pdBattHrlyData && dAffordableBattMaxCapFrac > 0 && daDwellingPVBattFrac[iMtr] > 0)
                  BEMPX_SumIntoHourlyResultArray( pdBattHrlyData, "Proposed", pszCUACMeters[0][iMtr], "Battery", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordableBattMaxCapFrac * daDwellingPVBattFrac[iMtr]) );
            }
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
               double dHVACOthrUse = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], "HVAC Other", NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
               if (dHVACOthrUse > 0)
               {  double dCoolAdd[8760], dHeatAdd[8760];
                  double *pdCool=NULL, *pdHeat=NULL, *pdHVACOthr=NULL;
                  BEMPX_GetHourlyResultArrayPtr( &pdCool    , NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], "Cooling"   , iCUAC_BEMProcIdx );
                  BEMPX_GetHourlyResultArrayPtr( &pdHeat    , NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], "Heating"   , iCUAC_BEMProcIdx );
                  BEMPX_GetHourlyResultArrayPtr( &pdHVACOthr, NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], "HVAC Other", iCUAC_BEMProcIdx );
                  iHr = 0;
                  for (iMo=0; iMo<12; iMo++)
                     for (iDay=0; iDay<iNumDaysInMonth[iMo]; iDay++)
                     {  double dCoolDay=0.0, dHeatDay=0.0;
                        int iEndDayHr = iHr+24;
                        for (iTemp=iHr; iTemp < iEndDayHr; iTemp++)
                        {  dCoolDay += pdCool[iTemp];
                           dHeatDay += pdHeat[iTemp];
                        }
                        bool bAllCool = ( (dCoolDay > 0 && dHeatDay < 0.0001) || (dCoolDay < 0.0001 && dHeatDay < 0.0001 &&  bCoolingMonth[iMo]) );
                        bool bAllHeat = ( (dHeatDay > 0 && dCoolDay < 0.0001) || (dCoolDay < 0.0001 && dHeatDay < 0.0001 && !bCoolingMonth[iMo]) );
                        assert( bAllCool || bAllHeat || (dCoolDay > 0.0001 && dHeatDay > 0.0001) );
                        for (iTemp=iHr; iTemp < iEndDayHr; iTemp++)
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

                  BEMPX_AddHourlyResultArray(     NULL,     "Proposed", pszCUACMeters[iFuel][iMtr], "HVAC Other", iCUAC_BEMProcIdx );   // zero out "HVAC Other" enduse
                  BEMPX_SumIntoHourlyResultArray( dCoolAdd, "Proposed", pszCUACMeters[iFuel][iMtr], "Cooling"   , iCUAC_BEMProcIdx );
                  BEMPX_SumIntoHourlyResultArray( dHeatAdd, "Proposed", pszCUACMeters[iFuel][iMtr], "Heating"   , iCUAC_BEMProcIdx );
            }  }
      iStep = 3;     sStep = "DistribEnduses";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

      // Reduce meters to energy use by dwelling unit - SAC 09/10/22
      for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
         if (laNumUnitsByBedrms[iMtr] > 1)
            for (iFuel=0; iFuel < 2; iFuel++)
            {  double dMult = 1.0 / (double) laNumUnitsByBedrms[iMtr];
               for (iTemp=0; iTemp < NumInitialEnduses; iTemp++)
                  BEMPX_ScaleHourlyResultArray( dMult, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iTemp], iCUAC_BEMProcIdx );
            }
      iStep = 4;     sStep = "SingleDwelling";
            if (iBillCalcDetails > 0)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

   }  // end of if (!bOldCUAC)


   // Adjustments to energy use streams to account for CUAC equipment efficiency inputs



                  if (iBillCalcDetails > 0) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupResults rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bResultsSetupEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupResults" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;   iRetVal = 96;  // Error calculating CUAC utility bill(s)
      return;
   }

   // Retrieve & Load utility rate data  - SAC 10/19/22
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

   // Retrieve hourly series' calculate & post monthly sums and utility bills
   int iMoHrStart[12], iMoHrEnd[12];
   iMoHrStart[0] = 0;   iMoHrEnd[0] = (24*iNumDaysInMonth[0])-1;
   for (iTemp=1; iTemp<12; iTemp++)
   {  iMoHrStart[iTemp] = iMoHrEnd[  iTemp-1] + 1;
      iMoHrEnd[  iTemp] = iMoHrStart[iTemp] + (24*iNumDaysInMonth[iTemp])-1;
   }
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
            for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
            //{  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? (iCEUIdx==11 ? "ElecGen" : "ElecUse") : "GasUse");
            {  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? "ElecUse" : "GasUse");
               long lDBID_CEUFuelResult = BEMPX_GetDatabaseID( qsCEUFuelUseName );
               if (lDBID_CEUFuelResult > 0)     // some enduse/fuel combinations not possible or tracked
               {  int iInitMtrIdx = iaInitToRptsEnduseMap[iCEUIdx];

                  if (!bOldCUAC)
                  {  // HOURLY simulation results
                     double dCEUAnnTot = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iInitMtrIdx], NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                     if ( (iCEUIdx==11 && dCEUAnnTot > 0.01) || (iCEUIdx!=11 && dCEUAnnTot < 0.01) )
                     {  for (iTemp=0; iTemp<14; iTemp++)
                           BEMPX_SetBEMData( lDBID_CEUFuelResult+iTemp, BEMP_Flt, (void*) &dZero, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }
                     else
                     {  double *pdHrlyUse=NULL;
                        double dAnnUse = 0.0;
                        BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse, NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iInitMtrIdx], iCUAC_BEMProcIdx );
                        for (iMo=0; iMo<12; iMo++)
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
                        {  int iInitMtrIdx = iaInitToRptsEnduseMap[iCEUIdx];
                           double dCEUAnnTot = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iInitMtrIdx], NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
                           if ( (iCEUIdx==11 && dCEUAnnTot > -0.01) || (iCEUIdx!=11 && dCEUAnnTot < 0.01) )
                           {  // skip
                           }
                           else
                           {  double *pdHrlyUse=NULL;
                              BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse, NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iInitMtrIdx], iCUAC_BEMProcIdx );
                              for (iMo=0; iMo<12; iMo++)
                                 for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                                    daHrlyTotUse[iHr] += pdHrlyUse[iHr];
                        }  }
                        for (iMo=0; iMo<12; iMo++)    // SAC 12/04/23
                        {  double dMoUse=0.0;
                           for (iHr = iMoHrStart[iMo]; iHr <= iMoHrEnd[iMo]; iHr++)
                              dMoUse = daHrlyTotUse[iHr];
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
                                          double dMoTOUUse = 0.0, dMoTOUPeakDem = 0.0, dMonBypassableTOUCost = 0.0, dMonNonBypassableTOUCost = 0.0, dMoTOUDailyUse[31];    int i0YrDay, iHrInDay;
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
                                 int i0YrDay, iHrInDay, iDayOfWk;
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
      return;
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
                        {  saCSVColLabels[0] += QString( "%1 Electric Use,,,,,,,,,,,,%2 Gas Use,,,," ).arg( pszCUACCSVUnitTypeLabels[iMtr], pszCUACCSVUnitTypeLabels[iMtr] );
                           saCSVColLabels[1] += pszCUACCSVElecEnduseLabels;      saCSVColLabels[1] += pszCUACCSVGasEnduseLabels;
                           saCSVColLabels[2] += "(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(therms),(therms),(therms),(therms),";
                           iNumRptgMtrs++;
                           for (iFuel=0; iFuel<2; iFuel++)
                              for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
                                 if (baHaveFuelEnduseHrlyResults[iFuel][iCEUIdx])
                                 {  int iInitMtrIdx = iaInitToRptsEnduseMap[iCEUIdx];
                                    pdHrlyUse[iHrlyUsePtrIdx] = NULL;
                                    BEMPX_GetHourlyResultArrayPtr( &pdHrlyUse[iHrlyUsePtrIdx++], NULL, 0, "Proposed", pszCUACMeters[iFuel][iMtr], pszInitialCUACEnduses[iInitMtrIdx], iCUAC_BEMProcIdx );
                                 }
                        }  assert( iHrlyUsePtrIdx == (iNumRptgMtrs * 16) );

                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[0].toLocal8Bit().constData() );   
                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[1].toLocal8Bit().constData() );   
                     fprintf( fp_CSV,  "%s\n", saCSVColLabels[2].toLocal8Bit().constData() );   

                     int iAnnHrIdx=0;
                     QString qsMtrResStr[NumDwellingMeters];
                     for (iMo=1; iMo<=12; iMo++)
                        for (iDay=1; iDay<=iNumDaysInMonth[iMo-1]; iDay++)
                           for (iHr=1; iHr<=24; iHr++)
                           {  for (iMtr=0; iMtr < iNumRptgMtrs; iMtr++)
                              {  int iMtrResColIdx = (iMtr * 16);
                                 qsMtrResStr[iMtr] = QString( "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16," ).arg(
                                             QString::number(pdHrlyUse[iMtrResColIdx   ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+1 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+2 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+3 ][iAnnHrIdx]),
                                             QString::number(pdHrlyUse[iMtrResColIdx+4 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+5 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+6 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+7 ][iAnnHrIdx]), 
                                             QString::number(pdHrlyUse[iMtrResColIdx+8 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+9 ][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+10][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+11][iAnnHrIdx]), 
                                             QString::number(pdHrlyUse[iMtrResColIdx+12][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+13][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+14][iAnnHrIdx]), QString::number(pdHrlyUse[iMtrResColIdx+15][iAnnHrIdx]) );
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
            int iPDFGenRetVal = BEMPX_GeneratePDF( sSubmitPDFPathFile.toLocal8Bit().constData(), sRptGraphicsPath.toLocal8Bit().constData(), iRptID, iCUAC_BEMProcIdx );
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
                     int iPDFGenRetVal = BEMPX_GeneratePDF( sDetailsPDFPathFile.toLocal8Bit().constData(), sRptGraphicsPath.toLocal8Bit().constData(), iRptID, iCUAC_BEMProcIdx );
                     BEMPX_WriteLogFile( QString( "CUAC details report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sDetailsPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }  }
            }

            int iGotHere = 1;
      }  }

   }

   // call rulelist to delete any CPR_* rate components - SAC 09/20/23
   CMX_EvaluateRuleset( "CUAC_DeleteCPRRates" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );

   if (!sErrMsg.isEmpty() && iRetVal == 0)      // SAC 09/29/23
      iRetVal = 96;  // Error calculating CUAC utility bill(s)
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
                              bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx, int iBillCalcDetails /*=-1*/,
                              int iSecurityKeyIndex, const char* pszSecurityKey, const char* pszProxyServerAddress, const char* pszProxyServerCredentials,
                              const char* pszProxyServerType, int iRptGenConnectTimeout, int iRptGenReadWriteTimeout )
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
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout );
               //											94 : Error downloading CUAC electric tariff schedule
            if (iRetVal > 0)
				   ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 94 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
            else //if (iAnalysisStorage < 3)
               svUtilRatesToDelete.push_back( ((std::string) sProcessingPath.toLocal8Bit().constData()) + ((std::string) "er.json") );
         }
         if (iRetVal == 0 && !bAbort && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:GasTariffGen"  ), lGasTariffGen, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lGasTariffGen > 1)
         {  CUAC_RateDownload( "Gas", 95, "CUAC:CPR_GasUtilityRateRef", sProcessingPath, /*sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear,*/ bStoreBEMDetails, bSilent, bVerbose,
                               bResearchMode, pCompRuleDebugInfo, iSecurityKeyIndex, pszSecurityKey, pszProxyServerAddress, pszProxyServerCredentials, pszProxyServerType,
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout );
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
                              bAbort, iRetVal, sErrMsg, iCUACReportID, iCUAC_BEMProcIdx, iBillCalcDetails /*=-1*/,
                              false /*bWritePDF*/, false /*bWriteCSV*/, lBatchRateIdx );
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

int CUAC_WriteCSVSummary( QFile& csvFile, const char* pszProjectPathFileName, const char* pszSimWeatherPath )  // SAC 12/11/23
{	int iRetVal = 0;

	QString sModelPathFile		= pszProjectPathFileName;
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

	QString sSimWeatherPath		= pszSimWeatherPath;
	RelativeToCompletePath_IfNeeded( sSimWeatherPath  );

	double dTimeOverall = 0;
	BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:AnalysisDuration" ), dTimeOverall );

		QString sRunTitle, sWthrStn, sAnnWthrFile, sTimeStamp, sLogMsg, sBEMErr;
	//	QString sAnalType, sPropSimSummary, sStdSimSummary, sAppVer, sCmpMgrVer, sEPlusVer, sOSVer;
	//	double dRptTotArea, dRptCndArea;   // SAC 2/19/17
		int iCID_Proj      = GetBEMBaseCompID( sBEMErr, "Proj"      );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"       ), sRunTitle );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherStation" ), sWthrStn  );
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
   int iSpecVal, iErr, iCost, iResIdx=0;
   for (int i=0; i<8; i++)
   {  if (BEMPX_GetInteger( lDBID_CUAC_AffordableUnitsByBedrms+i, lAffordableUnitsByBedrms[i], 0, -1 ) && lAffordableUnitsByBedrms[i] > 0)
      {  lAffordableUnitsByBedrmsSum += lAffordableUnitsByBedrms[i];
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


   QString sResults = QString::asprintf( "%s,\"%s\",\"%s\",\"%s\",%d:%.2d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%.2f,%.2f,%.2f,%.2f,%.2f,%ld\n", 
               sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)),
               sElecUtil.toLocal8Bit().constData(), sElecTerr.toLocal8Bit().constData(), sElecTariff.toLocal8Bit().constData(), sGasUtil.toLocal8Bit().constData(), sGasTerr.toLocal8Bit().constData(), sGasTariff.toLocal8Bit().constData(),
               dUnitWghtAvgCosts[0], dUnitWghtAvgCosts[1], dUnitWghtAvgCosts[2], dUnitWghtAvgCosts[3], dUnitWghtAvgCosts[4], lNumAffordableDwellingUnits );
   csvFile.write( sResults.toLocal8Bit().constData() );


   return iRetVal;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CUACToolMiner integration -

int CMX_GetCUACDBProjectList( std::string sCUACPathFilename, std::vector<std::string>& vsProjects, std::vector<int>& viProjectIDs )
{
   //auto res = getProjectList( "C:/CUAC/CUACTool-Rev2-0-0.accdb", vsProjects);

   //auto res = getProjectList( sCUACPathFilename, vsProjects);

   CUACToolMiner db;    // revised to return both Project strings AND IDs - SAC 09/18/23
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
                        const std::string& sProject_name )  //, const std::vector<std::string>& sTable_names)
{
   CUACToolMiner db;    // revised to return both Project strings AND IDs - SAC 09/18/23
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
                              std::string& sErrMsg )
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

   CUACToolMiner db;
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
               // BEMPX_WriteLogFile( QString( "ElecTerritory:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            if (iLocRes == 0 && sVal.length() > 0)
            {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ElecTerritory", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
               iLocRes = db.get_key_value("tProjects", "ProjectID", "TariffType", projectID, sVal);
                  // BEMPX_WriteLogFile( QString( "ElecTariff:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                  // BEMPX_WriteLogFile( QString( "GasTerritory:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               if (iLocRes == 0 && sVal.length() > 0)
               {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "GasTerritory", iCID_CUAC ), BEMP_Str, (void*) sVal.c_str() );
                  iLocRes = db.get_key_value("tProjects", "ProjectID", "TariffType", projectID, sVal);
                     // BEMPX_WriteLogFile( QString( "GasTariff:  %1" ).arg( sVal.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                                       }           // BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( col_vals[0].c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                                          }           // BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( col_vals[0].c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  break;
                           case  1 :   {  if (iThisAptObjIdx >= 0)
                                          {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                             std::string sPropName = col_vals[iRow].as_string();
                                             if (sPropName.compare("Plug Loads")==0)
                                                sPropName = "PlugLoads";
                                             sPropName += "Elec[1]";
                                             lEnduseDBID = BEMPX_GetDatabaseID( sPropName.c_str(), iCID_OldCUACApt );
                                                      // BEMPX_WriteLogFile( QString( "     property: %1 => DBID %2" ).arg( sPropName.c_str(), QString::number(lEnduseDBID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                                                      // BEMPX_WriteLogFile( QString( "        set %1 to DBID %2 objectIdx %3 - returned %4" ).arg( QString::number(dVal), QString::number(lEnduseDBID+iMo-1), QString::number(iThisAptObjIdx), QString::number(iSetRetVal) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                                          }           // BEMPX_WriteLogFile( QString( "  elec summary row:  %1 => iThisAptObjIdx %2" ).arg( col_vals[0].c_str(), QString::number(iThisAptObjIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }  break;
                           case  1 :   {  if (iThisAptObjIdx >= 0)
                                          {  assert( col_vals[iRow].index() == CUACToolMiner::string_type );
                                             std::string sPropName = col_vals[iRow].as_string();
                                             if (sPropName.compare("Plug Loads")==0)
                                                sPropName = "PlugLoads";
                                             sPropName += "Gas[1]";
                                             lEnduseDBID = BEMPX_GetDatabaseID( sPropName.c_str(), iCID_OldCUACApt );
                                                      // BEMPX_WriteLogFile( QString( "     property: %1 => DBID %2" ).arg( sPropName.c_str(), QString::number(lEnduseDBID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
                                                      // BEMPX_WriteLogFile( QString( "        set %1 to DBID %2 objectIdx %3 - returned %4" ).arg( QString::number(dVal), QString::number(lEnduseDBID+iMo-1), QString::number(iThisAptObjIdx), QString::number(iSetRetVal) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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


