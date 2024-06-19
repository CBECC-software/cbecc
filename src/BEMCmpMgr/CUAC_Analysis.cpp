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


////////////////////////////////////////////////////////////////////////////////
static int iNumDaysInMonth[12] = {   31,    28,    31,    30,   31,   30,   31,   31,   30,   31,   30,    31   };
static bool bCoolingMonth[12]  = {  false, false, false, true, true, true, true, true, true, true, false, false };

#define  NumDwellingMeters   7
#define  NumInitialEnduses  14
static const char* pszCUACMeters[2][NumDwellingMeters]  = { { "Elec_0bedrm", "Elec_1bedrm", "Elec_2bedrm", "Elec_3bedrm", "Elec_4bedrm", "Elec_5bedrm", "Elec_6bedrm" },
                                                            {  "Gas_0bedrm",  "Gas_1bedrm",  "Gas_2bedrm",  "Gas_3bedrm",  "Gas_4bedrm",  "Gas_5bedrm",  "Gas_6bedrm" } };
static const char* pszInitialCUACEnduses[NumInitialEnduses+1]  = { "Cooling", "Heating", "DHW", "Ventilation", "HVAC Other", "Plug Loads", "Lighting", "Refrigerator", "Dishwasher", "Dryer", "Washer", "Cooking", "Photovoltaics", "Battery", NULL };
                                                               //       0        1        2        3              4              5           6           7                 8           9        10          11          12             13
// CUAC reporting enduses:
#define  NumCUACEnduses  12
static const char* pszCUACRptEnduseAbbrevs[NumCUACEnduses+1]  = {  "Ckg",      "Clg",      "DHW",      "Dish",     "Dryer",    "Htg",      "IAQVent",  "Ltg",      "PlugLds",  "Rfrg",     "Wash",     "PVSys",     NULL };
static int iaInitToRptsEnduseMap[NumCUACEnduses+1]            = {    11,         0,          2,           8,          9,         1,            3,        6,            5,        7,          10,          12,        -1  };
static bool baHaveFuelEnduseHrlyResults[2][NumCUACEnduses]  = { {   true,       true,       true,       true,       true,       true,       true,       true,       true,       true,       true,       true  },
                                                                {   true,      false,       true,      false,       true,       true,      false,      false,      false,      false,      false,      false  } };
static const char* pszCUACCSVElecEnduseLabels                 =    "Cooking,Cooling,DHW,Dishwasher,Dryer,Heating,IAQ Vent,Lighting,Plug Loads,Refrigerator,Washer,PV,";
static const char* pszCUACCSVGasEnduseLabels                  =    "Cooking,DHW,Dryer,Heating,";
static const char* pszCUACCSVUnitTypeLabels[]                 = {  "Studio", "1 Bedroom", "2 Bedroom", "3 Bedroom", "4 Bedroom", "5 Bedroom", "6 Bedroom"  };

static bool LoadCUACUtilityRate( CUACUtilityRate& rate, int iRateObjIdx, int iBEMProcIdx, QString& qsErrMsg );


////////////////////////////////////////////////////////////////////////////////
void CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, QString sRptGraphicsPath, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo,
                              char* pszErrorMsg, int iErrorMsgLen, bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx )
{  // at this point, ruleset object is loaded w/ all hourly results read directly from CSE run(s)

// TEMPORARY
//bVerbose = true;

   int iPrevRuleErrs = BEMPX_GetRulesetErrorCount();   // add eval of rules to setup utility rates - SAC 09/14/22
                  if (bVerbose) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupRates rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bRateEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupRates" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;
      return;
   }

   int iMtr, iFuel, iMo, iDay, iHr, iTemp, iSpecVal, iErr, iStep = 1;
   QString sStep = "Init";
            if (bVerbose)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }

   long laNumUnitsByBedrms[NumDwellingMeters], lTemp, lNumUnitTypes=0;
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:AffordableUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0)
      {  laNumUnitsByBedrms[iMtr] = lTemp;
         lNumUnitTypes++;
      }
      else
         laNumUnitsByBedrms[iMtr] = 0;
   }
   if (lNumUnitTypes < 1)  // abort analysis if no unit types specified - SAC 10/19/22
   {  bAbort = true;
      BEMPX_WriteLogFile( QString( "CUAC Error: No affordable units specified. Specify affordable units via checkboxes in residential zone dialog." ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      return;
   }

//   double daZero[8760];
//   for (iHr=0; iHr<8760; iHr++)
//      daZero[iHr] = 0.0;

   // Divvy PV/Batt into affordable housing meters by annual dwelling electric use - SAC 09/10/22
   double dPVAnnual = BEMPX_GetHourlyResultSum(   NULL, 0, "Proposed", "Electricity", "Photovoltaics", NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
   if (dPVAnnual == -99999.0)
      dPVAnnual = 0.0;
   double dBattAnnual = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", "Electricity", "Battery",       NULL, NULL, NULL, NULL, NULL, NULL, NULL, iCUAC_BEMProcIdx );
   if (dBattAnnual == -99999.0)
      dBattAnnual = 0.0;
   double dAffordablePVDCSysSizeFrac=0.0, dAffordableBattMaxCapFrac=0.0;
   BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUAC:AffordablePVDCSysSizeFrac" ), dAffordablePVDCSysSizeFrac, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUAC:AffordableBattMaxCapFrac"  ), dAffordableBattMaxCapFrac , 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx );
   if ( (dPVAnnual != 0.0 || dBattAnnual != 0.0) && (dAffordablePVDCSysSizeFrac > 0 || dAffordableBattMaxCapFrac > 0) )
   {  double dTotalAllDwellingElecUse = 0.0;
      double daDwellingElecFrac[NumDwellingMeters];
      for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
      {
         if (laNumUnitsByBedrms[iMtr] < 1)
            daDwellingElecFrac[iMtr] = 0.0;
         else
         {  daDwellingElecFrac[iMtr] = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[0][iMtr], pszInitialCUACEnduses[0], pszInitialCUACEnduses[1], pszInitialCUACEnduses[2], pszInitialCUACEnduses[3],
                                                                                                               pszInitialCUACEnduses[4], pszInitialCUACEnduses[5], pszInitialCUACEnduses[6], pszInitialCUACEnduses[7], iCUAC_BEMProcIdx );
            if (daDwellingElecFrac[iMtr] == -99999.0)
               daDwellingElecFrac[iMtr] = 0.0;
            double dTemp = BEMPX_GetHourlyResultSum( NULL, 0, "Proposed", pszCUACMeters[0][iMtr], pszInitialCUACEnduses[8], pszInitialCUACEnduses[9], pszInitialCUACEnduses[10], pszInitialCUACEnduses[11],
                                                                                                   pszInitialCUACEnduses[12], pszInitialCUACEnduses[13], NULL, NULL, iCUAC_BEMProcIdx );
            if (dTemp != -99999.0)
               daDwellingElecFrac[iMtr] += dTemp;
            dTotalAllDwellingElecUse += daDwellingElecFrac[iMtr];
      }  }
      assert( dTotalAllDwellingElecUse > 0 );
      if (dTotalAllDwellingElecUse > 0)
      {
         double *pdPVHrlyData=NULL, *pdBattHrlyData=NULL;
         if (dPVAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdPVHrlyData  , NULL, 0, "Proposed", "Electricity", "Photovoltaics", iCUAC_BEMProcIdx );
         if (dBattAnnual != 0.0)
            BEMPX_GetHourlyResultArrayPtr( &pdBattHrlyData, NULL, 0, "Proposed", "Electricity", "Battery"      , iCUAC_BEMProcIdx );

         for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
            if (daDwellingElecFrac[iMtr] > 0)
            {
               daDwellingElecFrac[iMtr] = daDwellingElecFrac[iMtr] / dTotalAllDwellingElecUse;
               // PV
               if (pdPVHrlyData && dAffordablePVDCSysSizeFrac > 0 && daDwellingElecFrac[iMtr] > 0)
                  BEMPX_SumIntoHourlyResultArray( pdPVHrlyData, "Proposed", pszCUACMeters[0][iMtr], "Photovoltaics", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordablePVDCSysSizeFrac * daDwellingElecFrac[iMtr]) );
               // Battery
               if (pdBattHrlyData && dAffordableBattMaxCapFrac > 0 && daDwellingElecFrac[iMtr] > 0)
                  BEMPX_SumIntoHourlyResultArray( pdBattHrlyData, "Proposed", pszCUACMeters[0][iMtr], "Battery", iCUAC_BEMProcIdx, FALSE /*bAddIfNotExist*/,
                                                  (dAffordableBattMaxCapFrac * daDwellingElecFrac[iMtr]) );
      }     }
   }
   iStep = 2;     sStep = "PV-Batt";
            if (bVerbose)
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
            if (bVerbose)
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
            if (bVerbose)
            {  QString sDbgFN = sProcessingPath + sModelFileOnly + QString(" - CUAC use totals %1-%2.txt").arg( QString::number(iStep), sStep );
               BEMPX_WriteHourlyResultsSummary( sDbgFN.toLocal8Bit().constData(), bSilent, iCUAC_BEMProcIdx );
            }



   // Adjustments to energy use streams to account for CUAC equipment efficiency inputs



                  if (bVerbose) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_SetupResults rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bResultsSetupEvalSuccessful = CMX_EvaluateRuleset( "CUAC_SetupResults" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;
      return;
   }


   // Retrieve & Load utility rate data  - SAC 10/19/22
   CUACUtilityRate utilRate[2];
   utilRate[0].bOK = utilRate[1].bOK = false;
   long laDBID_RateRef[2] = { BEMPX_GetDatabaseID( "CUAC:ElecUtilityRateRef" ), BEMPX_GetDatabaseID( "CUAC:GasUtilityRateRef" ) };     // loop to include Gas rate - SAC 10/25/22
   QString saFuelLabels[2] = { "Elec", "Gas" };
   for (iFuel=0; iFuel < 2; iFuel++)
   {  BEMObject* pRate = BEMPX_GetObjectPtr( laDBID_RateRef[iFuel], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
      int iRateObjIdx = (pRate == NULL ? -1 : BEMPX_GetObjectIndex( pRate->getClass(), pRate, iCUAC_BEMProcIdx ));
      if (iRateObjIdx >= 0 && !LoadCUACUtilityRate( utilRate[iFuel], iRateObjIdx, iCUAC_BEMProcIdx, sErrMsg ))
      {  if (sErrMsg.isEmpty())
            sErrMsg = QString( "CUAC %1 Utility Rate Initialization Error" ).arg( saFuelLabels[iFuel] );
         else
            sErrMsg = QString( "CUAC %1 Utility Rate Initialization Error:  " ).arg( saFuelLabels[iFuel] ) + sErrMsg;
         BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   }  }


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
         BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CUAC:CUACResultsRef" )+iMtr, iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         for (iFuel=0; (iResObjIdx >= 0 && iFuel < 2); iFuel++)
         {
            double dTotUseByMo[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
            for (int iCEUIdx=0; iCEUIdx < NumCUACEnduses; iCEUIdx++)
            //{  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? (iCEUIdx==11 ? "ElecGen" : "ElecUse") : "GasUse");
            {  QString qsCEUFuelUseName = QString( "CUACResults:%1" ).arg( pszCUACRptEnduseAbbrevs[iCEUIdx] );      qsCEUFuelUseName += (iFuel==0 ? "ElecUse" : "GasUse");
               long lDBID_CEUFuelResult = BEMPX_GetDatabaseID( qsCEUFuelUseName );
               if (lDBID_CEUFuelResult > 0)     // some enduse/fuel combinations not possible or tracked
               {  int iInitMtrIdx = iaInitToRptsEnduseMap[iCEUIdx];
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
                           dMoUse += pdHrlyUse[iHr];
                        dAnnUse += dMoUse;
                        dTotUseByMo[iMo] += dMoUse;
                        BEMPX_SetBEMData( lDBID_CEUFuelResult+iMo, BEMP_Flt, (void*) &dMoUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );
                     }
                     BEMPX_SetBEMData( lDBID_CEUFuelResult+12, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual
                     dAnnUse /= 365.0;
                     BEMPX_SetBEMData( lDBID_CEUFuelResult+13, BEMP_Flt, (void*) &dAnnUse, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // daily
               }  }
            }

            // Calculate utility bills
            QString sFuelCostPropName = (iFuel==0 ? "CUACResults:ElecCosts" : "CUACResults:GasCosts");
            long lDBID_FuelCostResult = BEMPX_GetDatabaseID( sFuelCostPropName );         assert( lDBID_FuelCostResult > 0 );
            if (lDBID_FuelCostResult > 0 && utilRate[iFuel].bOK)
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
                  for (iMo=0; iMo<12; iMo++)
                  {  double dMonCost = utilRate[iFuel].dMonthlyCharge;
                     int iSeason = utilRate[iFuel].laSeasonMonthMap[iMo];  // 0-Win, 1-Sum
                     double dDailyUseBin = utilRate[iFuel].daSeasonalUsePerDay[iSeason] * iNumDaysInMonth[iMo];
                     double dMonRateUse = dTotUseByMo[iMo] * dFuelRateMult;
                     for (int iBin=0; (dMonRateUse > 0 && iBin < 4); iBin++)
                     {
                        if (dMonRateUse <= dDailyUseBin)
                        {  dMonCost += (dMonRateUse * utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]);
                           dMonRateUse = 0.0;
                        }
                        else
                        {  dMonCost += (dDailyUseBin * utilRate[iFuel].daaBinSeasonalCost[iBin][iSeason]);
                           dMonRateUse -= dDailyUseBin;
                     }  }
                     if (dMonRateUse > 0)  // apply final bin cost to all remaining use (?)
                        dMonCost += (dMonRateUse * utilRate[iFuel].daaBinSeasonalCost[4][iSeason]);
                     if (dMonCost < utilRate[iFuel].dMinMonthlyCharge)
                        dMonCost = utilRate[iFuel].dMinMonthlyCharge;
                     dAnnCost += dMonCost;
                     BEMPX_SetBEMData( lDBID_FuelCostResult+iMo+2, BEMP_Flt, (void*) &dMonCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly cost
                  }
                  BEMPX_SetBEMData( lDBID_FuelCostResult  , BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // annual cost
                  dAnnCost /= 12;
                  BEMPX_SetBEMData( lDBID_FuelCostResult+1, BEMP_Flt, (void*) &dAnnCost, BEMO_User, iResObjIdx, BEMS_UserDefined, BEMO_User, TRUE, iCUAC_BEMProcIdx );  // monthly avg cost
            }  }
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


                  if (bVerbose) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_FinalCalcs rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   BOOL bFinalResultsCalcsEvalSuccessful = CMX_EvaluateRuleset( "CUAC_FinalCalcs" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
   BEMPX_RefreshLogFile();
   if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
   {  bAbort = true;
      return;
   }


   // write top portion of CUAC input/output CSV file (via ruleset) - SAC 10/20/22
   QString sIOCSVPathFile = BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:InOutCSVPathFile" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
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
                  if (bVerbose) 
                     BEMPX_WriteLogFile( QString( "  CUAC_AnalysisProcessing - CUAC_WriteInputOutputCSV rules" ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         BOOL bIOCSVExportEvalSuccessful = CMX_EvaluateRuleset( "CUAC_WriteInputOutputCSV" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );   //, &saPreAnalChkWarningMsgs );
         BEMPX_RefreshLogFile();
         if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
         {  bAbort = true;
            return;
         }
         else
         {  // append all hourly results to end of CSV file - SAC 10/20/22
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
   }  }


                     if (bStoreBEMDetails)
                     {  QString sDbgFN = sProcessingPath + sModelFileOnly + ".ibd-Detail-PostCUAC";
                        BEMPX_WriteProjectFile( sDbgFN.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, iCUAC_BEMProcIdx );
                     }

   // PDF report generation
   if (!bAbort && sErrMsg.isEmpty())
   {
      QString sSubmitPDFPathFile = BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:SubmitPDFPathFile" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
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

            int iPDFGenRetVal = BEMPX_GeneratePDF( sSubmitPDFPathFile.toLocal8Bit().constData(), sRptGraphicsPath.toLocal8Bit().constData(), 0, iCUAC_BEMProcIdx );
            BEMPX_WriteLogFile( QString( "CUAC submittal report PDF generation returned %1:  %2" ).arg( QString::number(iPDFGenRetVal), sSubmitPDFPathFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

            int iGotHere = 1;
      }  }

      // same here for Details report

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

