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

static bool LoadCUACUtilityRate( CUACUtilityRate& rate, int iRateObjIdx, int iBEMProcIdx, QString& qsErrMsg );


////////////////////////////////////////////////////////////////////////////////
void CUAC_AnalysisProcessing( QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, int iRulesetCodeYear,
                              bool bStoreBEMDetails, bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo,
                              char* pszErrorMsg, int iErrorMsgLen, bool& bAbort, int& iRetVal, QString& sErrMsg, long iCUACReportID, int iCUAC_BEMProcIdx )
{  // at this point, ruleset object is loaded w/ all hourly results read directly from CSE run(s)

// TEMPORARY
bVerbose = true;

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
   CUACUtilityRate rateElec, rateGas;
   rateElec.bOK = rateGas.bOK = false;

   BEMObject* pRate = BEMPX_GetObjectPtr( BEMPX_GetDatabaseID( "CUAC:ElecUtilityRateRef" ), iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
   int iRateObjIdx = (pRate == NULL ? -1 : BEMPX_GetObjectIndex( pRate->getClass(), pRate, iCUAC_BEMProcIdx ));
   if (iRateObjIdx >= 0 && !LoadCUACUtilityRate( rateElec, iRateObjIdx, iCUAC_BEMProcIdx, sErrMsg ))
   {  if (sErrMsg.isEmpty())
         sErrMsg = QString( "CUAC Elec Utility Rate Initialization Error" );
      else
         sErrMsg = QString( "CUAC Elec Utility Rate Initialization Error:  " ) + sErrMsg;
      BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   }
   // CUAC:GasUtilityRateRef



// 1,           "MonthlyCharge",                     BEMP_Flt,  1,  0,  0,   Opt,  "$",                0,  0,                           1001, "MonthlyCharge",  "" 
// 1,           "MinMonthlyCharge",                  BEMP_Flt,  1,  0,  0,   Opt,  "$",                0,  0,                           1001, "MinMonthlyCharge",  "" 
// 
// 1,           "NumSeasons",                        BEMP_Int,  1,  0,  0,   Opt,  "",                 0,  0,                           1001, "NumberSeasons",  "" 
// 1,           "SeasonLabels",                      BEMP_Str, 12,  1,  0,   Opt,  "",                 0,  0,                           1001, "SeasonLabels",  "" 
// 1,           "SeasonMonthMap",                    BEMP_Int, 12,  1,  0,   Opt,  "",                 0,  0,                           1001, "SeasonMonthMap",  "" 
// 
// 1,           "SeasonalUsePerDay",                 BEMP_Flt, 12,  1,  0,   Opt,  "",                 0,  0,                           1001, "SeasonalUsePerDay",  "" 
// 1,           "Bin1SeasonalCost",                  BEMP_Flt, 12,  1,  0,   Opt,  "$",                0,  0,                           1001, "Bin1SeasonalCost",  "" 
// 1,           "Bin2SeasonalCost",                  BEMP_Flt, 12,  1,  0,   Opt,  "$",                0,  0,                           1001, "Bin2SeasonalCost",  "" 
// 1,           "Bin3SeasonalCost",                  BEMP_Flt, 12,  1,  0,   Opt,  "$",                0,  0,                           1001, "Bin3SeasonalCost",  "" 
// 1,           "Bin4SeasonalCost",                  BEMP_Flt, 12,  1,  0,   Opt,  "$",                0,  0,                           1001, "Bin4SeasonalCost",  "" 
// 1,           "Bin5SeasonalCost",                  BEMP_Flt, 12,  1,  0,   Opt,  "$",                0,  0,                           1001, "Bin5SeasonalCost",  "" 

// struct CUACUtilityRate  // SAC 10/19/22
// {
//    double  dElecMonthlyCharge;
//    double  dElecMinMonthlyCharge;
//    long    lNumSeasons;
//    QString saSeasonLabels[12];
//    long    laSeasonMonthMap[12];
//    double  daSeasonalUsePerDay[12];
//    double  daaBinSeasonalCost[5][12];
// };



   // Calculate utility bills



                     if (bStoreBEMDetails)
                     {  QString sDbgFN = sProcessingPath + sModelFileOnly + ".ibd-Detail-PostCUAC";
                        BEMPX_WriteProjectFile( sDbgFN.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, iCUAC_BEMProcIdx );
                     }

}


bool LoadCUACUtilityRate( CUACUtilityRate& rate, int iRateObjIdx, int iBEMProcIdx, QString& qsErrMsg )      // SAC 10/19/22
{  bool bRetVal = true;
   int iSpecVal, iErr;
   rate.dElecMonthlyCharge    = BEMPX_GetFloat(   BEMPX_GetDatabaseID( "UtilityRate:MonthlyCharge"    ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
   rate.dElecMinMonthlyCharge = BEMPX_GetFloat(   BEMPX_GetDatabaseID( "UtilityRate:MinMonthlyCharge" ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx, false, 0.0 );
   rate.lNumSeasons           = BEMPX_GetInteger( BEMPX_GetDatabaseID( "UtilityRate:NumSeasons"       ), iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
   if (rate.lNumSeasons < 1 || rate.lNumSeasons > 12)
   {  bRetVal = false;
      qsErrMsg = QString( "Utility Rate NumSeasons (%1) expected to be in the range 1-12, rate object index %2" ).arg( QString::number( rate.lNumSeasons ), QString::number( iRateObjIdx ) );
   }
   for (int iSeas=0; (bRetVal && iSeas < rate.lNumSeasons); iSeas++)
   {  rate.saSeasonLabels[iSeas]   = BEMPX_GetString(  BEMPX_GetDatabaseID( "UtilityRate:SeasonLabels"   )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
      rate.laSeasonMonthMap[iSeas] = BEMPX_GetInteger( BEMPX_GetDatabaseID( "UtilityRate:SeasonMonthMap" )+iSeas, iSpecVal, iErr, iRateObjIdx, BEMO_User, iBEMProcIdx );
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

