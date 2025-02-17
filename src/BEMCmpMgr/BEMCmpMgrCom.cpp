// BEMCmpMgrCom.cpp : Defines the commercial model analysis routines
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

//#include <direct.h>  			// Directory related system routines
//#include <stdio.h>
#include <io.h>

//#include <QtGui>
// TO DO  #include <openssl/crypto.h>	// SAC 10/16/13

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
#include "CUAC_Analysis.h"          // SAC 09/09/22


static int CMX_ExportCSVHourlyResults_A2030( const char* pszHourlyResultsPathFile, const char* pszModelName, char* pszErrMsgBuffer /*=NULL*/,
													int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ );


////////////////////////////////////////////////////////////////////////////////
static int iNumDaysInMonth[12] = {  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };


////////////////////////////////////////////////////////////////////////////////
// ASHRAE Std 90.1 AppG (S901G) analysis progress data & routines
																	//    BCM_NRP_Step_Init,  BCM_NRP_Step_Read,    BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSimRes,    BCM_NRP_Step_Store,  BCM_NRP_Step_Report,  BCM_NRP_Step_Done
const char* pszS901GProgressMsgs[]					 = { " Initialization",  " Read Project",      " Model Prep:  ",    " Translation:  ",    " Simulation:  ",   " Sim Results:  ",       " Model Storage",    " Report Generation", " Completed",   NULL  };

long			laS901GProgressSteps[]					 = {  BCM_NRP_Step_Init,  BCM_NRP_Step_Read,    BCM_NRP_Step_MPrep,  BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,   BCM_NRP_Step_MSimRes,  BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes,   BCM_NRP_Step_MPrep,  BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep, BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans, BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,   BCM_NRP_Step_MSimRes,  BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes, BCM_NRP_Step_MSimRes,   BCM_NRP_Step_Store,  BCM_NRP_Step_Report,   0 };
long			laS901GProgressModels[]					 = {                0,                  0,      BCM_NRAP_Model_zp,   BCM_NRAP_Model_zb1, BCM_NRAP_Model_zb2, BCM_NRAP_Model_zb3, BCM_NRAP_Model_zb4,  BCM_NRAP_Model_zp,    BCM_NRAP_Model_zb1,  BCM_NRAP_Model_zb2,  BCM_NRAP_Model_zb3,  BCM_NRAP_Model_zb4,   BCM_NRAP_Model_zp,  BCM_NRAP_Model_zb1, BCM_NRAP_Model_zb2, BCM_NRAP_Model_zb3, BCM_NRAP_Model_zb4,  BCM_NRAP_Model_zp,     BCM_NRAP_Model_zb1,   BCM_NRAP_Model_zb2,   BCM_NRAP_Model_zb3,   BCM_NRAP_Model_zb4,     BCM_NRAP_Model_ap,   BCM_NRAP_Model_ab1, BCM_NRAP_Model_ab2, BCM_NRAP_Model_ab3, BCM_NRAP_Model_ab4,  BCM_NRAP_Model_ap,    BCM_NRAP_Model_ab1,  BCM_NRAP_Model_ab2,  BCM_NRAP_Model_ab3,  BCM_NRAP_Model_ab4,   BCM_NRAP_Model_ap,  BCM_NRAP_Model_ab1, BCM_NRAP_Model_ab2, BCM_NRAP_Model_ab3, BCM_NRAP_Model_ab4,  BCM_NRAP_Model_ap,     BCM_NRAP_Model_ab1,   BCM_NRAP_Model_ab2,   BCM_NRAP_Model_ab3,   BCM_NRAP_Model_ab4,                  0,                   0,        0 };
float       faS901GProgressVals_SerlAllSims[]    = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     3,                   3,                   3,                   3,                  10,                  10,                 10,                 10,                 10,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    3,                   3,                   3,                   3,                   30,                 30,                 30,                 30,                 30,                  2,                     2,                    2,                    2,                    2,                      3,                  15,          };
float       fS901GProgressValSum_SerlAllSims     =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    3 +                  3 +                  3 +                  3 +                 10 +                 10 +                10 +                10 +                10 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   3 +                  3 +                  3 +                  3 +                  30 +                30 +                30 +                30 +                30 +                 2 +                    2 +                   2 +                   2 +                   2 +                     3 +                 15            ;
float       faS901GProgressVals_SerlZBAPABSims[] = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     3,                   3,                   3,                   3,                   1,                  10,                 10,                 10,                 10,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    3,                   3,                   3,                   3,                   30,                 30,                 30,                 30,                 30,                  2,                     2,                    2,                    2,                    2,                      3,                  15,          };
float       fS901GProgressValSum_SerlZBAPABSims  =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    3 +                  3 +                  3 +                  3 +                  1 +                 10 +                10 +                10 +                10 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   3 +                  3 +                  3 +                  3 +                  30 +                30 +                30 +                30 +                30 +                 2 +                    2 +                   2 +                   2 +                   2 +                     3 +                 15            ;
float       faS901GProgressVals_SerlZPAPSims[]   = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     0,                   0,                   0,                   0,                  10,                   0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    0,                   0,                   0,                   0,                   30,                  0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                      3,                  15,          };
float       fS901GProgressValSum_SerlZPAPSims    =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    0 +                  0 +                  0 +                  0 +                 10 +                  0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   0 +                  0 +                  0 +                  0 +                  30 +                 0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                     3 +                 15            ;
float       faS901GProgressVals_SerlAPSim[]      = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     0,                   0,                   0,                   0,                   1,                   0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    0,                   0,                   0,                   0,                   30,                  0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                      3,                  15,          };
float       fS901GProgressValSum_SerlAPSim       =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    0 +                  0 +                  0 +                  0 +                  1 +                  0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   0 +                  0 +                  0 +                  0 +                  30 +                 0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                     3 +                 15            ;
float       faS901GProgressVals_ParlAllSims[]    = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     3,                   3,                   3,                   3,                   1,                  12,                 12,                 12,                 12,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    3,                   3,                   3,                   3,                    1,                 35,                 35,                 35,                 35,                  2,                     2,                    2,                    2,                    2,                      5,                  15,          };
float       fS901GProgressValSum_ParlAllSims     =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    3 +                  3 +                  3 +                  3 +                  1 +                 12 +                12 +                12 +                12 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   3 +                  3 +                  3 +                  3 +                   1 +                35 +                35 +                35 +                35 +                 2 +                    2 +                   2 +                   2 +                   2 +                     5 +                 15            ;
float       faS901GProgressVals_ParlZPAPSims[]   = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     0,                   0,                   0,                   0,                  10,                   0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    0,                   0,                   0,                   0,                   30,                  0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                      5,                  15,          };
float       fS901GProgressValSum_ParlZPAPSims    =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    0 +                  0 +                  0 +                  0 +                 10 +                  0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   0 +                  0 +                  0 +                  0 +                  30 +                 0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                     5 +                 15            ;
float       faS901GProgressVals_ParlAPSims[]     = {                1,                  3,                   2,                    2,                  2,                  2,                  2,                  3,                     0,                   0,                   0,                   0,                   1,                   0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                       2,                   2,                  2,                  2,                  2,                   3,                    0,                   0,                   0,                   0,                   30,                  0,                  0,                  0,                  0,                  2,                     2,                    2,                    2,                    2,                      5,                  15,          };
float       fS901GProgressValSum_ParlAPSims      =                  1 +                 3 +                  2 +                   2 +                 2 +                 2 +                 2 +                 3 +                    0 +                  0 +                  0 +                  0 +                  1 +                  0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                      2 +                  2 +                 2 +                 2 +                 2 +                  3 +                   0 +                  0 +                  0 +                  0 +                  30 +                 0 +                 0 +                 0 +                 0 +                 2 +                    2 +                   2 +                   2 +                   2 +                     5 +                 15            ;

//const char** pszS901GProgressMsgs=NULL;
float *faS901GProgressVals=NULL, fS901GProgressValSum=0;

#define  NUM_S901GProgressEntries  48
float  faS901GCumulativeProgressSum[NUM_S901GProgressEntries];
void SetS901GCumulativeProgressSum()
{	int idx = -1;			bool bDone = false;
	while (++idx < NUM_S901GProgressEntries)
	{	if (bDone)
			faS901GCumulativeProgressSum[idx] = 0;
		else
		{	faS901GCumulativeProgressSum[idx] = (idx < 1 ? 0 : faS901GCumulativeProgressSum[idx-1] + faS901GProgressVals[idx-1]);
			if (laS901GProgressSteps[idx] == 0)
				bDone = true;
		}
	}
	assert( bDone );
}

void SetS901GProgressMessage( QString& sMsg, long lNRPStep, long lNRPModels )
{	sMsg = pszS901GProgressMsgs[lNRPStep-1];
	if (lNRPModels > 0)
	{	int iNumModels = BCM_NRP_NumModels( lNRPModels );		int iModelsFound = iNumModels;
		int iaModelIDs[]    = {  BCM_NRAP_Model_zp , BCM_NRAP_Model_zb1, BCM_NRAP_Model_zb2, BCM_NRAP_Model_zb3, BCM_NRAP_Model_zb4, BCM_NRAP_Model_ap , BCM_NRAP_Model_ab1, BCM_NRAP_Model_ab2, BCM_NRAP_Model_ab3, BCM_NRAP_Model_ab4,  -1 };
		const char* ppsMA[] = {               "zp" ,              "zb1",              "zb2",              "zb3",              "zb4",              "ap" ,              "ab1",              "ab2",              "ab3",              "ab4",  NULL };
		int idx=-1;
		if      (iNumModels == 4 && lNRPModels == (BCM_NRAP_Model_zb1+BCM_NRAP_Model_zb2+BCM_NRAP_Model_zb3+BCM_NRAP_Model_zb4))
			sMsg += "zb1-4";
		else if (iNumModels == 5 && lNRPModels == (BCM_NRAP_Model_zb1+BCM_NRAP_Model_zb2+BCM_NRAP_Model_zb3+BCM_NRAP_Model_zb4 + BCM_NRAP_Model_zp))
			sMsg += "zp & zb1-4";
		else if (iNumModels == 4 && lNRPModels == (BCM_NRAP_Model_ab1+BCM_NRAP_Model_ab2+BCM_NRAP_Model_ab3+BCM_NRAP_Model_ab4))
			sMsg += "ab1-4";
		else if (iNumModels == 5 && lNRPModels == (BCM_NRAP_Model_ab1+BCM_NRAP_Model_ab2+BCM_NRAP_Model_ab3+BCM_NRAP_Model_ab4 + BCM_NRAP_Model_ap))
			sMsg += "ap & ab1-4";
		else
		{	iModelsFound = 0;
			while (iaModelIDs[++idx] >= 0)
			{	if (lNRPModels & iaModelIDs[idx])
				{	iModelsFound++;
					sMsg += ppsMA[idx];
					if (iModelsFound < iNumModels-1)				sMsg += ", ";
					else if (iModelsFound == iNumModels-1)		sMsg += " & ";
				}
		}	}
		assert( iModelsFound == iNumModels );
	}
}

void SetS901GProgressMessage( QString& sMsg, long lProgressID )
{	long lNRPStep  = BCM_NRP_Step(  lProgressID );
	long lNRPModel = BCM_NRP_Model( lProgressID );
	SetS901GProgressMessage( sMsg, lNRPStep, lNRPModel );
}


void SetS901GProgressVal_Parallel( bool bAll, bool bZP, bool bAP )
{	//pszS901GProgressMsgs = pszS901GProgressMsgs_Parl;
	if (bAll)
	{	faS901GProgressVals  = faS901GProgressVals_ParlAllSims;
		fS901GProgressValSum = fS901GProgressValSum_ParlAllSims;
	}
	else if (bZP && bAP)
	{	faS901GProgressVals  = faS901GProgressVals_ParlZPAPSims;
		fS901GProgressValSum = fS901GProgressValSum_ParlZPAPSims;
	}
	else
	{	faS901GProgressVals  = faS901GProgressVals_ParlAPSims;
		fS901GProgressValSum = fS901GProgressValSum_ParlAPSims;
	}
	SetS901GCumulativeProgressSum();
}
void SetS901GProgressVal_Serial( bool bZP, bool bAP, bool bZB, bool bAB )
{	//pszS901GProgressMsgs = pszS901GProgressMsgs_Serl;
	if (!bZP && bAP && !bZB && !bAB)
   {  faS901GProgressVals  = faS901GProgressVals_SerlAPSim;
      fS901GProgressValSum = fS901GProgressValSum_SerlAPSim;
	}
	else if (bZP && bAP && !bZB && !bAB)
   {  faS901GProgressVals  = faS901GProgressVals_SerlZPAPSims;
      fS901GProgressValSum = fS901GProgressValSum_SerlZPAPSims;
	}
	else if (!bZP && bAP && bZB && bAB)
   {  faS901GProgressVals  = faS901GProgressVals_SerlZBAPABSims;
      fS901GProgressValSum = fS901GProgressValSum_SerlZBAPABSims;
	}
	else
   {  faS901GProgressVals  = faS901GProgressVals_SerlAllSims;
      fS901GProgressValSum = fS901GProgressValSum_SerlAllSims;
	}
	SetS901GCumulativeProgressSum();
}


/////////////////////////////////////////////////////////////////////////////

//int /*CALLBACK*/ CECNRes_ProgressIncrement( int i0CurRunStep )
int /*CALLBACK*/ CECNRes_ProgressIncrement( long lProgressID )
{
	int iRetVal = 1;

	bool bCalcProgress = (spAnalProgCallbackFunc != NULL);		// SAC 5/28/15 - progress reporting update
#ifdef CM_QTGUI
	if (!bCalcProgress && sqt_win && sqt_progress)
		bCalcProgress = true;
#endif

	if (bCalcProgress)
	{
		//int iPassedInCurRunStep = i0CurRunStep;
	//	if (i0CurRunStep >= CNRP_NumSteps)
	//	{	ASSERT( i0CurRunStep < CNRP_NumSteps );
	//		i0CurRunStep = CNRP_NumSteps - 1;
	//	}
	//	if (sqt_win && sqt_progress && faCECNResProgressVals != NULL && fCECNResProgressValSum > 0.01)
	//	{	int i=-1;
	//		float fValSumThusFar = 0;
	//		while (++i < i0CurRunStep)
	//			fValSumThusFar += faCECNResProgressVals[i];
	//		int iProgValue = (int) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((fValSumThusFar / fCECNResProgressValSum / siNumProgressRuns) * 98));
	// SAC 5/26/15 - new progress tracking mechanism
		long lNRPStep    = BCM_NRP_Step(  lProgressID );
		long lNRPModel   = BCM_NRP_Model( lProgressID );
		long lNRPSimProg = BCM_NRP_Prog(  lProgressID );	// SAC 2/18/19 - added SimProg component to track monthly sim progress
		int iNRPIdx = GetCECNResProgressIndex( lNRPStep, lNRPModel, lNRPSimProg );				assert( iNRPIdx >= 0 );
		if (iNRPIdx < 0)
			iNRPIdx = 0;
		int iProgValue = 0;
		if (faCECNResProgressVals != NULL && fCECNResProgressValSum > 0.01)
			iProgValue = (int) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((faCECNResCumulativeProgressSum[iNRPIdx] / fCECNResProgressValSum / siNumProgressRuns) * 98));

// QT Progress Dialog stuff
#ifdef CM_QTGUI
		long lNRPType  = BCM_NRP_Type(  lProgressID );
		if (sqt_win && sqt_progress)
		{	sqt_progress->setValue( iProgValue );
			//SetProgressMessage( pszCECNResProgressMsgs[lNRPStep-1] );		// i0CurRunStep] );
			QString sProgMsg;
			SetCECNResProgressMessage( sProgMsg, lNRPStep, lNRPModel, lNRPSimProg );

// TEMP - test/debug - SAC 11/18/21
//BEMPX_WriteLogFile( QString( "              CECNRes_ProgressIncrement() - iProgValue: %1  fCECNResProgressValSum: %2  sbFreezeProgress: %3  sProgMsg: '%4'" ).arg( QString::number(iProgValue), QString::number(fCECNResProgressValSum), (sbFreezeProgress ? "true" : "false"), sProgMsg ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         if (ebLogAnalysisProgress)    // SAC 01/14/22
            BEMPX_WriteLogFile( QString( "              analysis progress: %1%  (%2/%3)  %4  (ID: %5 - CECNRes_ProgressIncrement)" ).arg( 
                     QString::number(iProgValue), QString::number(faCECNResCumulativeProgressSum[iNRPIdx]), QString::number(fCECNResProgressValSum), sProgMsg, QString::number(lProgressID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

// testing
//QString sLog = QString( "   CECNRes_ProgressIncrement():  lProgressID %1  iNRPIdx %2  iProgValue %3 (%4/%5)  sProgMsg %6" ).arg( QString::number(lProgressID), QString::number(iNRPIdx),
//															QString::number(iProgValue), QString::number(faCECNResCumulativeProgressSum[iNRPIdx]), QString::number(fCECNResProgressValSum), sProgMsg );
//BEMPX_WriteLogFile( sLog, NULL, FALSE, TRUE, FALSE );

			SetProgressMessage( (const char*) sProgMsg.toLocal8Bit().constData(), (lNRPType == BCM_NRP_Type_Batch) );
			sqt_progress->setLabelText( sqProgressMsg );
			sqt_win->repaint();
			if (sbAllowCallbackAbort && sqt_progress->wasCanceled())
				iRetVal = 0;

// testing...
//	QString sLogMsg;	sLogMsg.Format( "   Analysis Progress:  %s  (%d%%)  - %ld", sProgMsg, iProgValue, lProgressID );
//	BEMPX_WriteLogFile( QString( "   Analysis Progress:  %1  (%2%)  - %3" ).arg( sProgMsg, QString::number(iProgValue), QString::number(lProgressID) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

			//if (!bFound && !strncmp( msg, "Error", 5 ))
			//{	siNumProgressErrors++;
			//	SetProgressMessage( msg );
			//	sqt_progress->setLabelText( sqProgressMsg );
			//	sqt_win->repaint();
			//}
		}
#endif

//QString sDbgMsg;	sDbgMsg.Format( "CECNRes_ProgressIncrement( %d ) -> %d & progress value %d%%", iPassedInCurRunStep, i0CurRunStep, iProgValue );
//BEMMessageBox( sDbgMsg, "" );

	// SAC 5/28/15 - callback mechanism
		if (iRetVal == 1 && spAnalProgCallbackFunc != NULL && slAnalysisProgressCallbackRetVal < 1)
		{	long lCBRetVal = spAnalProgCallbackFunc( lProgressID, iProgValue );
			if (lCBRetVal > 0)
			{	iRetVal = 0;
				slAnalysisProgressCallbackRetVal = lCBRetVal;
		}	}
	}	// end of - if (bCalcProgress)

	return iRetVal;
}


static inline int GetS901GProgressIndex( long lStep, long lModel )
{	int iRetVal = -2;
	for (int i=0; iRetVal < -1; i++)
	{
		if (laS901GProgressSteps[i] == 0)
			iRetVal = -1;
		else if (laS901GProgressSteps[i] == lStep)
		{	if ( laS901GProgressModels[i] == 0 ||
				 (laS901GProgressModels[i] & lModel))
				iRetVal = i;
	}	}
	return iRetVal;
}

//int /*CALLBACK*/ S901G_ProgressIncrement( int i0CurRunStep )
int /*CALLBACK*/ S901G_ProgressIncrement( long lProgressID )
{
	int iRetVal = 1;

	bool bCalcProgress = (spAnalProgCallbackFunc != NULL);		// SAC 5/28/15 - progress reporting update
#ifdef CM_QTGUI
	if (!bCalcProgress && sqt_win && sqt_progress)
		bCalcProgress = true;
#endif

	if (bCalcProgress)
	{
		//int iPassedInCurRunStep = i0CurRunStep;
	//	if (i0CurRunStep >= CNRP_NumSteps)
	//	{	assert( i0CurRunStep < CNRP_NumSteps );
	//		i0CurRunStep = CNRP_NumSteps - 1;
	//	}
	//	if (sqt_win && sqt_progress && faS901GProgressVals != NULL && fS901GProgressValSum > 0.01)
	//	{	int i=-1;
	//		float fValSumThusFar = 0;
	//		while (++i < i0CurRunStep)
	//			fValSumThusFar += faS901GProgressVals[i];
	//		int iProgValue = (int) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((fValSumThusFar / fS901GProgressValSum / siNumProgressRuns) * 98));
	// SAC 5/26/15 - new progress tracking mechanism
		long lNRPStep  = BCM_NRP_Step(  lProgressID );
		long lNRPModel = BCM_NRP_Model( lProgressID );
		int iNRPIdx = GetS901GProgressIndex( lNRPStep, lNRPModel );				assert( iNRPIdx >= 0 );
		if (iNRPIdx < 0)
			iNRPIdx = 0;
		int iProgValue = 0;
		if (faS901GProgressVals != NULL && fS901GProgressValSum > 0.01)
			iProgValue = (int) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((faS901GCumulativeProgressSum[iNRPIdx] / fS901GProgressValSum / siNumProgressRuns) * 98));

// QT Progress Dialog stuff
#ifdef CM_QTGUI
		long lNRPType  = BCM_NRP_Type(  lProgressID );
		if (sqt_win && sqt_progress)
		{	sqt_progress->setValue( iProgValue );
			//SetProgressMessage( pszS901GProgressMsgs[lNRPStep-1] );		// i0CurRunStep] );
			QString sProgMsg;
			SetS901GProgressMessage( sProgMsg, lNRPStep, lNRPModel );
			SetProgressMessage( (const char*) sProgMsg.toLocal8Bit().constData(), (lNRPType == BCM_NRP_Type_Batch) );
			sqt_progress->setLabelText( sqProgressMsg );
			sqt_win->repaint();
			if (sbAllowCallbackAbort && sqt_progress->wasCanceled())
				iRetVal = 0;

// testing...
//	QString sLogMsg;	sLogMsg.Format( "   Analysis Progress:  %s  (%d%%)  - %ld", sProgMsg, iProgValue, lProgressID );
//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

			//if (!bFound && !strncmp( msg, "Error", 5 ))
			//{	siNumProgressErrors++;
			//	SetProgressMessage( msg );
			//	sqt_progress->setLabelText( sqProgressMsg );
			//	sqt_win->repaint();
			//}
		}
#endif

//QString sDbgMsg;	sDbgMsg.Format( "S901G_ProgressIncrement( %d ) -> %d & progress value %d%%", iPassedInCurRunStep, i0CurRunStep, iProgValue );
//BEMMessageBox( sDbgMsg, "" );

	// SAC 5/28/15 - callback mechanism
		if (iRetVal == 1 && spAnalProgCallbackFunc != NULL && slAnalysisProgressCallbackRetVal < 1)
		{	long lCBRetVal = spAnalProgCallbackFunc( lProgressID, iProgValue );
			if (lCBRetVal > 0)
			{	iRetVal = 0;
				slAnalysisProgressCallbackRetVal = lCBRetVal;
		}	}
	}	// end of - if (bCalcProgress)

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

static inline int /*CALLBACK*/ NRes_ProgressIncrement( int iCodeType, long lProgressID )
{	return  (iCodeType == CT_T24N ?  CECNRes_ProgressIncrement( lProgressID )  :  S901G_ProgressIncrement( lProgressID )  );
}

//static int siOSWrapProgressIndex = 0;
static bool sbLogOSWrapMessages = false;
void SetOSWrapLogFlag( bool bLogOSWrapMsgs )
{	sbLogOSWrapMessages = bLogOSWrapMsgs;
	//siOSWrapProgressIndex = 0;
}
int /*OSWRAP_MSGCALLBACK*/ OSWrapCallback( int iCodeType, int /*level*/, const char* msg, long lProgressID )  // retval:  0:continue / -1:abort  //  level:  0:message / 1:warning / 2:error
{
	int iRetVal = 0;

	if (sbLogOSWrapMessages)
		BEMPX_WriteLogFile( msg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	if (lProgressID > 0)  // (action == 3)
	{	//assert( siOSWrapProgressIndex > 0 && siOSWrapProgressIndex < CNRP_NumSteps );		//	if (     siOSWrapProgressIndex < CNRP_PropSizSim)		siOSWrapProgressIndex = CNRP_PropSizSim;
		//																											//	else if (siOSWrapProgressIndex < CNRP_StdSizSim)		siOSWrapProgressIndex = CNRP_StdSizSim;
		//																											//	else if (siOSWrapProgressIndex < CNRP_PropSim)			siOSWrapProgressIndex = CNRP_PropSim;
		//																											//	else if (siOSWrapProgressIndex < CNRP_StdAnnSim)		siOSWrapProgressIndex = CNRP_StdAnnSim;
		//iRetVal = (CECNRes_ProgressIncrement( siOSWrapProgressIndex ) == 0 ? -1 : 0);
		iRetVal = (NRes_ProgressIncrement( iCodeType, lProgressID ) == 0 ? -1 : 0);
	}

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

void ProcessNonResAnalysisAbort( int iCodeType, int iProgressStep, QString& sErrMsg, bool& bAbort, int& iRetVal, char* pszErrorMsg, int iErrorMsgLen )
{	QString sMsg;		int iErrorID=0;
	if (iCodeType == CT_T24N)
		SetCECNResProgressMessage( sMsg, iProgressStep, 0 /*lNRPModel*/, 0 /*lNRPSimProg*/ );
	else
		SetS901GProgressMessage( sMsg, iProgressStep, 0 /*lNRPModel*/ );
	if (spAnalProgCallbackFunc != NULL && slAnalysisProgressCallbackRetVal > 0)
	{	//											52 : Analysis aborted via callback function in calling application
		iErrorID = 52;
		sErrMsg = QString::asprintf( "Analysis aborted by calling application during%s analysis step (callback function returned %d)", sMsg.toLocal8Bit().constData(), slAnalysisProgressCallbackRetVal );
	}
	else
	{	//											33 : User aborted analysis via progress dialog 'Cancel' button
		iErrorID = 33;
		sErrMsg = QString::asprintf( "User aborted analysis via progress dialog 'Cancel' button during%s analysis step", sMsg.toLocal8Bit().constData() );
	}
	ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iErrorID /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
}


/////////////////////////////////////////////////////////////////////////////

inline static void InitHourlyArray( double* pDbl, double dVal )      // SAC 01/19/24
{	for (int hr=0; hr<8760; hr++)
		pDbl[hr] = dVal;
}


/////////////////////////////////////////////////////////////////////////////

int CMX_WindowDoorOverlaps_CECNonRes( bool /*bVerbose*/, bool /*bStoreBEMDetails*/, bool /*bSilent*/, QString& sErrMsg )
{	int iRetVal = 0;
	QString sLogMsg, sBEMErr;
	int iCID_Spc       = GetBEMBaseCompID( sBEMErr, "Spc"       );
	int iCID_ExtWall   = GetBEMBaseCompID( sBEMErr, "ExtWall"   );
	int iCID_Win       = GetBEMBaseCompID( sBEMErr, "Win"       );
	int iCID_Dr        = GetBEMBaseCompID( sBEMErr, "Dr"        );
	if (sBEMErr.length() > 0)
	{	iRetVal = -1;
		sErrMsg = QString::asprintf( "Error retrieving BEMBase object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
	}
	else
	{
	//	long lDBID_ExtWall_Area            = GetBEMBaseDBID( sBEMErr, "Area",            iCID_ExtWall );
		long lDBID_ExtWall_WinShadeGeomReqd = GetBEMBaseDBID( sBEMErr, "WinShadeGeomReqd", iCID_ExtWall );
	//	long lDBID_ExtWall_Hgt             = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_ExtWall );
	//	long lDBID_ExtWall_Wd              = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_ExtWall );
	//	long lDBID_Win_Area                = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Win );
		long lDBID_Win_Hgt                 = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_Win );
		long lDBID_Win_Wd                  = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_Win );
		long lDBID_Win_X                   = GetBEMBaseDBID( sBEMErr, "X",               iCID_Win );
		long lDBID_Win_Y                   = GetBEMBaseDBID( sBEMErr, "Y",               iCID_Win );
	//	long lDBID_Dr_Area                 = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Dr );
		long lDBID_Dr_Hgt                  = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_Dr );
		long lDBID_Dr_Wd                   = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_Dr );
		long lDBID_Dr_X                    = GetBEMBaseDBID( sBEMErr, "X",               iCID_Dr );
		long lDBID_Dr_Y                    = GetBEMBaseDBID( sBEMErr, "Y",               iCID_Dr );
		if (sBEMErr.length() > 0)
		{	iRetVal = -2;
			sErrMsg = QString::asprintf( "Error retrieving BEMBase property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
		}
		else
		{	int iError, iNumSpcs = BEMPX_GetNumObjects( iCID_Spc );
			long lWinShadeGeomReqd;
			double f1X, f1Y, f1Hgt, f1Wd,  f2X, f2Y, f2Hgt, f2Wd;
			for (int iSpc=0; (iRetVal>=0 && iSpc < iNumSpcs); iSpc++)
			{	BEMObject* pSpcObj = BEMPX_GetObjectByClass( iCID_Spc, iError, iSpc );
				if (pSpcObj)
			//	{	for (POSITION pos = pSpcObj->m_children.GetHeadPosition(); pos != NULL; )
			//		{	BEMObject* pChildObj = pSpcObj->m_children.GetNext( pos );
				{	for (int iChld=0; (iRetVal>=0 && iChld < pSpcObj->getChildCount()); iChld++)
					{	BEMObject* pChildObj = pSpcObj->getChild( iChld );
						if (pChildObj && pChildObj->getClass() && pChildObj->getClass()->get1BEMClassIdx() == iCID_ExtWall)
						{	int iObjIdx = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );			assert( iObjIdx >= 0 );
							if (iObjIdx >= 0 && BEMPX_GetInteger( lDBID_ExtWall_WinShadeGeomReqd, lWinShadeGeomReqd, -1, BEMP_Int, iObjIdx ) && lWinShadeGeomReqd > 0)
							{	int iNumWallErrors = 0;		QString sOverlapsOnThisExtWall;
							//	for (POSITION posC = pChildObj->m_children.GetHeadPosition(); (iRetVal>=0 && posC != NULL); )
							//	{	BEMObject* pWinDoorObj = pChildObj->m_children.GetNext( posC );
								for (int iGChld=0; (iRetVal>=0 && iGChld < pChildObj->getChildCount()); iGChld++)
								{	BEMObject* pWinDoorObj = pChildObj->getChild( iGChld );
									if (pWinDoorObj && pWinDoorObj->getClass() && (pWinDoorObj->getClass()->get1BEMClassIdx() == iCID_Win ||
																								pWinDoorObj->getClass()->get1BEMClassIdx() == iCID_Dr ) )
									{	// check for overlaps between THIS child window/door and all subsequent windows/doors
										// no need to check for windows/doors overlapping outer ExtWall boundaries - that is handled in rules
										bool bWinObj = (pWinDoorObj->getClass()->get1BEMClassIdx() == iCID_Win);
										int iWDObjIdx = BEMPX_GetObjectIndex( pWinDoorObj->getClass(), pWinDoorObj );													assert( iWDObjIdx >= 0 );
										BEMPX_GetFloat( (bWinObj ? lDBID_Win_X   : lDBID_Dr_X  ), f1X  , -1, BEMP_Flt, iWDObjIdx );			assert( f1X   >= 0 );	// checked in rules, so no error return here
										BEMPX_GetFloat( (bWinObj ? lDBID_Win_Y   : lDBID_Dr_Y  ), f1Y  , -1, BEMP_Flt, iWDObjIdx );			assert( f1Y   >= 0 );
										BEMPX_GetFloat( (bWinObj ? lDBID_Win_Hgt : lDBID_Dr_Hgt), f1Hgt, -1, BEMP_Flt, iWDObjIdx );			assert( f1Hgt >  0 );
										BEMPX_GetFloat( (bWinObj ? lDBID_Win_Wd  : lDBID_Dr_Wd ), f1Wd , -1, BEMP_Flt, iWDObjIdx );			assert( f1Wd  >  0 );
										double f1X2 = f1X + f1Wd,  f1Y2 = f1Y + f1Hgt;

										int iNumOverlapsThisWinDr = 0;		QString sOverlappingWinsDrs;
									//	for (POSITION pos2 = posC; pos2 != NULL; )
									//	{	BEMObject* pWinDoorObj2 = pChildObj->m_children.GetNext( pos2 );
										for (int iGChld2=iGChld+1; iGChld2 < pChildObj->getChildCount(); iGChld2++)
										{	BEMObject* pWinDoorObj2 = pChildObj->getChild( iGChld2 );
											if (pWinDoorObj2 && pWinDoorObj2->getClass() && (pWinDoorObj2->getClass()->get1BEMClassIdx() == iCID_Win ||
																										  pWinDoorObj2->getClass()->get1BEMClassIdx() == iCID_Dr ) )
											{	// check for overlaps between THIS child window/door and all subsequent windows/doors
												// no need to check for windows/doors overlapping outer ExtWall boundaries - that is handled in rules
												bool bWinObj2 = (pWinDoorObj2->getClass()->get1BEMClassIdx() == iCID_Win);
												int iWD2ObjIdx = BEMPX_GetObjectIndex( pWinDoorObj2->getClass(), pWinDoorObj2 );												assert( iWDObjIdx >= 0 );
												BEMPX_GetFloat( (bWinObj2 ? lDBID_Win_X   : lDBID_Dr_X  ), f2X  , -1, BEMP_Flt, iWD2ObjIdx );		assert( f2X   >= 0 );	// checked in rules, so no error return here
												BEMPX_GetFloat( (bWinObj2 ? lDBID_Win_Y   : lDBID_Dr_Y  ), f2Y  , -1, BEMP_Flt, iWD2ObjIdx );		assert( f2Y   >= 0 );
												BEMPX_GetFloat( (bWinObj2 ? lDBID_Win_Hgt : lDBID_Dr_Hgt), f2Hgt, -1, BEMP_Flt, iWD2ObjIdx );		assert( f2Hgt >  0 );
												BEMPX_GetFloat( (bWinObj2 ? lDBID_Win_Wd  : lDBID_Dr_Wd ), f2Wd , -1, BEMP_Flt, iWD2ObjIdx );		assert( f2Wd  >  0 );
												double f2X2 = f2X + f2Wd,  f2Y2 = f2Y + f2Hgt;

												if (	( (f2X < f1X && f2X2 > f1X) || (f2X2 > f1X2 && f2X < f1X2) || (f2X >= f1X && f2X2 <= f1X2) ) &&
														( (f2Y < f1Y && f2Y2 > f1Y) || (f2Y2 > f1Y2 && f2Y < f1Y2) || (f2Y >= f1Y && f2Y2 <= f1Y2) ) )
												{	// found overlap
													iNumOverlapsThisWinDr++;
													if (!sOverlappingWinsDrs.isEmpty())
														sOverlappingWinsDrs += ", ";
													sLogMsg = QString::asprintf( "%s '%s'", (bWinObj2 ? "Win" : "Door"), pWinDoorObj2->getName().toLocal8Bit().constData() );
													sOverlappingWinsDrs += sLogMsg;
										}	}	}

										if (iNumOverlapsThisWinDr > 0)
										{	// record overlaps between this win/door and subsequent win/door siblings
											iNumWallErrors++;
											if (!sOverlapsOnThisExtWall.isEmpty())
												sOverlapsOnThisExtWall += " | ";
											sLogMsg = QString::asprintf( "%s '%s' overlaps %s", (bWinObj ? "Win" : "Door"), pWinDoorObj->getName().toLocal8Bit().constData(), sOverlappingWinsDrs.toLocal8Bit().constData() );
											sOverlapsOnThisExtWall += sLogMsg;
									}	}
								}	// end of loop over children of wall

								if (iNumWallErrors > 0)
								{	// record all overlaps between this ExtWall's child wins/doors
									iRetVal++;
									sLogMsg = QString::asprintf( "ExtWall '%s' has overlapping windows/doors as follows:  %s", pChildObj->getName().toLocal8Bit().constData(), sOverlapsOnThisExtWall.toLocal8Bit().constData() );
									BEMPX_AddRulesetError( sLogMsg.toLocal8Bit().constData() );	// log individual ExtWall errors to ruleset error list
				// ALWAYS write error message (per wall) to log ??
								//	if (bVerbose)
									{	sLogMsg = "   Error: " + sLogMsg;
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}	}	}
					}	// end of loop over space children
			}	}	// end of loop over spaces
	}	}
	return iRetVal;
}


static inline double RoundDbl( double dVal, double dDivPerUnit )
{	return (dDivPerUnit <= 0.0 ? 0.0 : floor( ((dVal * dDivPerUnit) + 0.5) ) / dDivPerUnit);
}

static double sdPi        = acos(-1.0);
static double sd2Pi       = 2.0 * sdPi;
static double sdHalfPi    = asin(1.0);
static double sd3HalfPi   = 3.0 * sdHalfPi;

void IncrementRoofBucketIndex( int& iRoofBucketIdx )
{	iRoofBucketIdx = (iRoofBucketIdx + 3) % 8;
	return;
}

class CWinShadeSurface
{
public:
	int	m_iClassID;
	int	m_iObjectIdx;
	int	m_iOrientationIdx;
	double m_fZLevel;

	// args to generate PolyLp
	double m_fArea;
	double m_fAz;
	double m_fTilt;
	double m_fZ;
	double m_fArg6;
	double m_fArg7;
	int	m_iPolyType;

	// used during loop where surface PolyLps are defined
	bool	m_bSurfaceProcessed;
	bool	m_bWinShadeChildren;
	double m_dWinShadeMaxDepth;
	double m_dDX;
	double m_dDY;
	double m_dDZ;
	double m_dSideBySideOffset;

public:
	CWinShadeSurface( int iClassID=0, int iObjectIdx=-1, int iOrientationIdx=-1, double fZLevel=0,
							double fArea=0, double fAz=0, double fTilt=0, double fZ=0, double fArg6=0, double fArg7=0, int iPolyType=-1, double dWinShadeMaxDepth=0.0,
							bool bSurfaceProcessed=false, bool bWinShadeChildren=false, double dDX=0.0, double dDY=0.0, double dDZ=0.0, double dSideBySideOffset=0.0 )
			{	m_iClassID			= iClassID;
				m_iObjectIdx		= iObjectIdx;
				m_iOrientationIdx	= iOrientationIdx;
				m_fZLevel			= fZLevel;
				m_fArea				= fArea		;
				m_fAz					= fAz			;
				m_fTilt				= fTilt		;
				m_fZ					= fZ			;
				m_fArg6				= fArg6		;
				m_fArg7				= fArg7		;
				m_iPolyType			= iPolyType	;
				m_bSurfaceProcessed = bSurfaceProcessed;
				m_bWinShadeChildren = bWinShadeChildren;
				m_dWinShadeMaxDepth = dWinShadeMaxDepth;
				m_dDX					= dDX;
				m_dDY					= dDY;
				m_dDZ					= dDZ;
				m_dSideBySideOffset = dSideBySideOffset;
			};
};

void AddObjectByZ( std::vector <CWinShadeSurface>& svWinShadeSurfs, int iClassID, int iObjIdx, int iOrientationIdx, double fZLevel,
							double fArea, double fAz, double fTilt, double fZ, double fArg6, double fArg7, int iPolyType, double dWinShadeMaxDepth )
{	// array organized from low to high Z (most likely closest to input order)
	std::vector<CWinShadeSurface>::iterator it;
	if (svWinShadeSurfs.size() < 1)
		svWinShadeSurfs.push_back( CWinShadeSurface( iClassID, iObjIdx, iOrientationIdx, fZLevel, fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, dWinShadeMaxDepth ) );
	else
	{	it = svWinShadeSurfs.end()-1;
		if (fZLevel >= it->m_fZLevel)		// always add surface to end of list if it's Z level is >= last item in the array
			svWinShadeSurfs.push_back( CWinShadeSurface( iClassID, iObjIdx, iOrientationIdx, fZLevel, fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, dWinShadeMaxDepth ) );
		else
		{	for (it=svWinShadeSurfs.begin(); it < svWinShadeSurfs.end(); it++)
			{	if (fZLevel < it->m_fZLevel)
					break;
			}
			if (it == svWinShadeSurfs.end())
				svWinShadeSurfs.push_back( CWinShadeSurface( iClassID, iObjIdx, iOrientationIdx, fZLevel, fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, dWinShadeMaxDepth ) );
			else
				svWinShadeSurfs.insert( it, CWinShadeSurface( iClassID, iObjIdx, iOrientationIdx, fZLevel, fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, dWinShadeMaxDepth ) );
	}	}
}

int AzimuthToOrientationBucketIdx( double fAz )
{	int iRetVal = 0;
	fAz = 180 - fAz - 90;	// convert from BEM Azimuth to surface normal angle w/ East=0, North=90... (how orientation index is organized)
	if (fAz < 0)
		fAz += 360.0;
	if (fAz > 360)
		fAz -= 360.0;
	assert( fAz >= 0 && fAz <= 360 );
	if (     fAz <=  22.5)		iRetVal = 0;
	else if (fAz <   67.5)		iRetVal = 1;
	else if (fAz <= 112.5)		iRetVal = 2;
	else if (fAz <  157.5)		iRetVal = 3;
	else if (fAz <= 202.5)		iRetVal = 4;
	else if (fAz <  247.5)		iRetVal = 5;
	else if (fAz <= 292.5)		iRetVal = 6;
	else if (fAz <  337.5)		iRetVal = 7;
	return iRetVal;
}

void AddChildPolyLoops( int& iRetVal, BEMObject* pChildObj, bool bWinShadeMode, double fParentDZ, double fParentArea, double fAz, double fTilt, bool bVerbose, QString& sErrMsg, 
								int iCID_Win, long lDBID_Win_Area, long lDBID_Win_IsGlazedDoor, long lDBID_Win_PolyZ, long lDBID_Win_Hgt, long lDBID_Win_X, long lDBID_Win_Y,
								int iCID_Dr, long lDBID_Dr_Area, long lDBID_Dr_PolyZ, long lDBID_Dr_Hgt, long lDBID_Dr_X, long lDBID_Dr_Y,
								int iCID_Skylt, long lDBID_Skylt_Area, long lDBID_Skylt_PolyZ,    long lDBID_PolyLp_Parent, double dDX, double dDY, double dDZ )
{
	QString sSurfErrMsg, sLogMsg;
	double fArea, fZ, fArg6, fArg7, fChldHgt=-1, fChldX=-1, fChldY=-1;
	int iPolyType, iObjIdx, iPolyLpObjIdx;
	bool bIsSurface;
	long lIsGlazedDr=0;

					//		double fParentDZ = fArg6, fParentArea = fArea;
						//	for (POSITION pos2 = pChildObj->m_children.GetHeadPosition(); (iRetVal>=0 && pos2 != NULL); )
						//	{	BEMObject* pGChildObj = pChildObj->m_children.GetNext( pos2 );
							for (int iChld=0; (iRetVal>=0 && iChld < pChildObj->getChildCount()); iChld++)
							{	BEMObject* pGChildObj = pChildObj->getChild( iChld );
								if (pGChildObj && pGChildObj->getClass())
								{	sSurfErrMsg.clear();
									fArea=-1;	fZ=-1;	fArg6=-1;	fArg7=-1;	iPolyType=0;	bIsSurface=true;
									iObjIdx = BEMPX_GetObjectIndex( pGChildObj->getClass(), pGChildObj );
									if (     pGChildObj->getClass()->get1BEMClassIdx() == iCID_Win)
									{	if (!BEMPX_GetFloat( lDBID_Win_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
										else if (fArea <= 0)                                                          sSurfErrMsg += ", Area not > 0";
										if (!BEMPX_GetFloat( lDBID_Win_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", PolyZ undefined";
										iPolyType = (BEMPX_GetInteger( lDBID_Win_IsGlazedDoor, lIsGlazedDr, -1, BEMP_Int, iObjIdx ) && lIsGlazedDr) ? 3 : 2;
										if (bWinShadeMode)
										{	if (!BEMPX_GetFloat( lDBID_Win_Hgt, fChldHgt, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Hgt undefined";
											else if (fChldHgt <= 0)                                                       sSurfErrMsg += ", Hgt not > 0";
											if (!BEMPX_GetFloat( lDBID_Win_X  , fChldX  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", X undefined";
											else if (fChldX   <  0)                                                       sSurfErrMsg += ", X not >= 0";
											if (!BEMPX_GetFloat( lDBID_Win_Y  , fChldY  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Y undefined";
											else if (fChldY   <  0)                                                       sSurfErrMsg += ", Y not >= 0";
									}	}
									else if (pGChildObj->getClass()->get1BEMClassIdx() == iCID_Dr )
									{	if (!BEMPX_GetFloat( lDBID_Dr_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
										else if (fArea <= 0)                                                          sSurfErrMsg += ", Area not > 0";
										if (!BEMPX_GetFloat( lDBID_Dr_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", PolyZ undefined";
										iPolyType = 3;
										if (bWinShadeMode)
										{	if (!BEMPX_GetFloat( lDBID_Dr_Hgt, fChldHgt, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Hgt undefined";
											else if (fChldHgt <= 0)                                                       sSurfErrMsg += ", Hgt not > 0";
											if (!BEMPX_GetFloat( lDBID_Dr_X  , fChldX  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", X undefined";
											else if (fChldX   <  0)                                                       sSurfErrMsg += ", X not >= 0";
											if (!BEMPX_GetFloat( lDBID_Dr_Y  , fChldY  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Y undefined";
											else if (fChldY   <  0)                                                       sSurfErrMsg += ", Y not >= 0";
									}	}
									else if (pGChildObj->getClass()->get1BEMClassIdx() == iCID_Skylt)
									{	if (!BEMPX_GetFloat( lDBID_Skylt_Area , fArea, -1, BEMP_Flt, iObjIdx ))	sSurfErrMsg += ", Area undefined";
										else if (fArea <= 0)                                                          sSurfErrMsg += ", Area not > 0";
										if (!BEMPX_GetFloat( lDBID_Skylt_PolyZ, fZ   , -1, BEMP_Flt, iObjIdx ))	sSurfErrMsg += ", PolyZ undefined";
										iPolyType = 0;
									}
									else
										bIsSurface = false;

									if (bIsSurface)
									{	if (!sSurfErrMsg.isEmpty())
										{	iRetVal = -3;
											sErrMsg = QString::asprintf( "Error gathering data to create PolyLp object:  %s '%s' %s",
																		pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData(),
																		sSurfErrMsg.right( sSurfErrMsg.length()-2 ).toLocal8Bit().constData() );
										}
										else
										{	// call PolyLp creation routine
											iPolyLpObjIdx = BEMPX_CreatePolyLoop( fArea, fAz, fTilt, fZ, iPolyType, fParentDZ, fParentArea, -1 /*iBEMProcIdx*/, NULL, dDX, dDY, dDZ, fChldHgt, fChldX, fChldY );
											if (iPolyLpObjIdx < 0)
											{	if (fArea > fParentArea)
												{	iRetVal = -6;
													sErrMsg = QString::asprintf( "Error generating building geometry: %s '%s' area (%g) exceeds parent %s '%s' area (%g)", pGChildObj->getClass()->getLongName().toLocal8Bit().constData(),  
																				pGChildObj->getName().toLocal8Bit().constData(), fArea, pChildObj->getClass()->getLongName().toLocal8Bit().constData(),
																				pChildObj->getName().toLocal8Bit().constData(), fParentArea );
												}
												else
												{	iRetVal = -4;
													sErrMsg = QString::asprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, WallHt %g, WallArea %g)",
																				pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData(),
																				fArea, fAz, fTilt, fZ, iPolyType, fParentDZ, fParentArea );
											}	}
											else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pGChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
											{	iRetVal = -5;
												sErrMsg = QString::asprintf( "Error adding PolyLp child to %s '%s'", pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData() );
											}
											else
											{	iRetVal++;
												if (bVerbose)
												{	sLogMsg = QString::asprintf( "         PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, WallHt %g, WallArea %g)", 
																				pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData(), 
																				fArea, fAz, fTilt, fZ, iPolyType, fParentDZ, fParentArea );
													BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
											}	}
									}	}
							}	}
	return;
}

//		Return Values:	>=	0 =>	SUCCESS
//							<  0 =>	Error Code:
//											 -1 : Error retrieving BEMBase object ID(s)
//											 -2 : Error retrieving BEMBase property ID(s)
//											 -3 : Error retrieving surface data (or value(s) out of range)
//											 -4 : Error creating PolyLp object
//											 -5 : Error adding new PolyLp as child to surface
//											 -6 : Error creating PolyLp object due to child area > parent area
int CMX_GeneratePolyLoops_CECNonRes( bool bVerbose, bool /*bStoreBEMDetails*/, bool /*bSilent*/, QString& sErrMsg )
{	int iRetVal = 0;
	QString sLogMsg, sBEMErr;
	int iCID_Proj      = GetBEMBaseCompID( sBEMErr, "Proj"      );
	int iCID_PolyLp    = GetBEMBaseCompID( sBEMErr, "PolyLp"    );
	int iCID_Spc       = GetBEMBaseCompID( sBEMErr, "Spc"       );
	int iCID_Ceiling   = GetBEMBaseCompID( sBEMErr, "Ceiling"   );
	int iCID_ExtFlr    = GetBEMBaseCompID( sBEMErr, "ExtFlr"    );
	int iCID_ExtWall   = GetBEMBaseCompID( sBEMErr, "ExtWall"   );
	int iCID_Win       = GetBEMBaseCompID( sBEMErr, "Win"       );
	int iCID_Dr        = GetBEMBaseCompID( sBEMErr, "Dr"        );
	int iCID_Skylt     = GetBEMBaseCompID( sBEMErr, "Skylt"     );	// SAC 5/9/14 - added export of Skylt objects
	int iCID_IntFlr    = GetBEMBaseCompID( sBEMErr, "IntFlr"    );
	int iCID_IntWall   = GetBEMBaseCompID( sBEMErr, "IntWall"   );
	int iCID_Roof      = GetBEMBaseCompID( sBEMErr, "Roof"      );
	int iCID_UndgrFlr  = GetBEMBaseCompID( sBEMErr, "UndgrFlr"  );
	int iCID_UndgrWall = GetBEMBaseCompID( sBEMErr, "UndgrWall" );
	if (sBEMErr.length() > 0)
	{	iRetVal = -1;
		sErrMsg = QString::asprintf( "Error retrieving BEMBase object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
	}
	else
	{
		long lDBID_Proj_NumWinsHavingShades = GetBEMBaseDBID( sBEMErr, "NumWinsHavingShades", iCID_Proj );
		//long lDBID_Spc_FlrZ                = GetBEMBaseDBID( sBEMErr, "FlrZ",            iCID_Spc );
		//long lDBID_Spc_FlrToCeilingHgt     = GetBEMBaseDBID( sBEMErr, "FlrToCeilingHgt", iCID_Spc );
		long lDBID_Ceiling_Area            = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Ceiling );
		long lDBID_Ceiling_Tilt            = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_Ceiling );
		long lDBID_Ceiling_PolyZ           = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_Ceiling );
		long lDBID_ExtFlr_Area             = GetBEMBaseDBID( sBEMErr, "Area",            iCID_ExtFlr );
		long lDBID_ExtFlr_Az               = GetBEMBaseDBID( sBEMErr, "Az",              iCID_ExtFlr );
		long lDBID_ExtFlr_Tilt             = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_ExtFlr );
		long lDBID_ExtFlr_PolyZ            = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_ExtFlr );
		long lDBID_ExtWall_Area            = GetBEMBaseDBID( sBEMErr, "Area",            iCID_ExtWall );
		long lDBID_ExtWall_Az              = GetBEMBaseDBID( sBEMErr, "Az",              iCID_ExtWall );
		long lDBID_ExtWall_Tilt            = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_ExtWall );
		long lDBID_ExtWall_PolyZ           = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_ExtWall );
		long lDBID_ExtWall_PolyDZ          = GetBEMBaseDBID( sBEMErr, "PolyDZ",          iCID_ExtWall );
		long lDBID_ExtWall_WinShadeGeomReqd = GetBEMBaseDBID( sBEMErr, "WinShadeGeomReqd", iCID_ExtWall );
		long lDBID_ExtWall_WinShadeMaxDepth = GetBEMBaseDBID( sBEMErr, "WinShadeMaxDepth", iCID_ExtWall );
		long lDBID_ExtWall_Hgt             = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_ExtWall );
	//	long lDBID_ExtWall_Wd              = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_ExtWall );
		long lDBID_Win_Area                = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Win );
		long lDBID_Win_IsGlazedDoor        = GetBEMBaseDBID( sBEMErr, "IsGlazedDoor",    iCID_Win );
		long lDBID_Win_PolyZ               = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_Win );
		long lDBID_Win_Hgt                 = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_Win );
	//	long lDBID_Win_Wd                  = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_Win );
		long lDBID_Win_X                   = GetBEMBaseDBID( sBEMErr, "X",               iCID_Win );
		long lDBID_Win_Y                   = GetBEMBaseDBID( sBEMErr, "Y",               iCID_Win );
		long lDBID_Dr_Area                 = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Dr );
		long lDBID_Dr_PolyZ                = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_Dr );
		long lDBID_Dr_Hgt                  = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_Dr );
	//	long lDBID_Dr_Wd                   = GetBEMBaseDBID( sBEMErr, "Wd",              iCID_Dr );
		long lDBID_Dr_X                    = GetBEMBaseDBID( sBEMErr, "X",               iCID_Dr );
		long lDBID_Dr_Y                    = GetBEMBaseDBID( sBEMErr, "Y",               iCID_Dr );
		long lDBID_Skylt_Area              = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Skylt );
		long lDBID_Skylt_PolyZ             = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_Skylt );
		long lDBID_IntFlr_Area             = GetBEMBaseDBID( sBEMErr, "Area",            iCID_IntFlr );
		long lDBID_IntFlr_Tilt             = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_IntFlr );
		long lDBID_IntFlr_PolyZ            = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_IntFlr );
		long lDBID_IntFlr_PolyAz           = GetBEMBaseDBID( sBEMErr, "PolyAz",          iCID_IntFlr );
		long lDBID_IntWall_Area            = GetBEMBaseDBID( sBEMErr, "Area",            iCID_IntWall );
		long lDBID_IntWall_Tilt            = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_IntWall );
		long lDBID_IntWall_PolyZ           = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_IntWall );
		long lDBID_IntWall_PolyDZ          = GetBEMBaseDBID( sBEMErr, "PolyDZ",          iCID_IntWall );
		long lDBID_IntWall_PolyAz          = GetBEMBaseDBID( sBEMErr, "PolyAz",          iCID_IntWall );
		long lDBID_Roof_Area               = GetBEMBaseDBID( sBEMErr, "Area",            iCID_Roof );
		long lDBID_Roof_Az                 = GetBEMBaseDBID( sBEMErr, "Az",              iCID_Roof );
		long lDBID_Roof_Tilt               = GetBEMBaseDBID( sBEMErr, "Tilt",            iCID_Roof );
		long lDBID_Roof_PolyZ              = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_Roof );
		long lDBID_UndgrFlr_Area           = GetBEMBaseDBID( sBEMErr, "Area",            iCID_UndgrFlr );
		long lDBID_UndgrFlr_PolyZ          = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_UndgrFlr );
		long lDBID_UndgrFlr_PolyAz         = GetBEMBaseDBID( sBEMErr, "PolyAz",          iCID_UndgrFlr );
		long lDBID_UndgrWall_Area          = GetBEMBaseDBID( sBEMErr, "Area",            iCID_UndgrWall );
		long lDBID_UndgrWall_Hgt           = GetBEMBaseDBID( sBEMErr, "Hgt",             iCID_UndgrWall );
		long lDBID_UndgrWall_PolyZ         = GetBEMBaseDBID( sBEMErr, "PolyZ",           iCID_UndgrWall );
		long lDBID_UndgrWall_PolyAz        = GetBEMBaseDBID( sBEMErr, "PolyAz",          iCID_UndgrWall );
		long lDBID_PolyLp_Parent           = GetBEMBaseDBID( sBEMErr, "Parent",          iCID_PolyLp );
		if (sBEMErr.length() > 0)
		{	iRetVal = -2;
			sErrMsg = QString::asprintf( "Error retrieving BEMBase property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
		}
		else
		{	int iError, iNumSpcs = BEMPX_GetNumObjects( iCID_Spc );
			double fArea, fAz, fTilt, fZ, fArg6, fArg7, fWinShadeMaxDepth;
			int iPolyType, iPolyLpObjIdx;
//			long lIsGlazedDr;
			bool bIsSurface;
			QString sSurfErrMsg;
			long lNumWinsHavingShades, lWinShadeGeomReqd;
			BEMPX_GetInteger( lDBID_Proj_NumWinsHavingShades, lNumWinsHavingShades );	// SAC 1/6/15
			double dFurthestInteriorFromXYOrig = 0.0, dWinShadeMaxDepth;
			// SAC 1/6/15 - for window shading scenario, don't write Roof or ExtWall surfaces insode Spc loop, instead just accumulate lists of these surfaces by orientation bucket (8)
			int iOrientBucketIdx, iRoofOrientBucketIdx=0, iNumWinShadeSurfsSkipped=0;
			std::vector <CWinShadeSurface> svWinShadeSurfs;	// organized radially in 8 buckets
//			std::vector <int> ivaClassIDs[8], ivaObjIdxs[8];	// organized radially in 8 buckets
//			std::vector <double> fvaTopZ[8];
			for (int iSpc=0; (iRetVal>=0 && iSpc < iNumSpcs); iSpc++)
			{	BEMObject* pSpcObj = BEMPX_GetObjectByClass( iCID_Spc, iError, iSpc );
				if (pSpcObj)
			//	{	for (POSITION pos = pSpcObj->m_children.GetHeadPosition(); (iRetVal>=0 && pos != NULL); )
			//		{	BEMObject* pChildObj = pSpcObj->m_children.GetNext( pos );
				{	for (int iChld=0; (iRetVal>=0 && iChld < pSpcObj->getChildCount()); iChld++)
					{	BEMObject* pChildObj = pSpcObj->getChild( iChld );
						if (pChildObj && pChildObj->getClass())
						{	sSurfErrMsg.clear();
							fArea=-1;	fAz=-1;	fTilt=-1;	fZ=-1;	fArg6=-1;	fArg7=-1;	iPolyType=0;	fWinShadeMaxDepth=0;		bIsSurface=true;
							int iObjIdx = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );
							bool bProcessSurface = true;
							if (     pChildObj->getClass()->get1BEMClassIdx() == iCID_Ceiling  )
							{	if (!BEMPX_GetFloat( lDBID_Ceiling_Area , fArea, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_Ceiling_Tilt , fTilt, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_Ceiling_PolyZ, fZ   , -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								fAz = 0;
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_ExtFlr   )
							{	if (!BEMPX_GetFloat( lDBID_ExtFlr_Area , fArea, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_ExtFlr_Az   , fAz  , -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_ExtFlr_Tilt , fTilt, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_ExtFlr_PolyZ, fZ   , -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_ExtWall  )
							{	if (!BEMPX_GetFloat( lDBID_ExtWall_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_ExtWall_Az    , fAz  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_ExtWall_Tilt  , fTilt, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_ExtWall_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_ExtWall_PolyDZ, fArg6, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								iPolyType = 1;
								if (lNumWinsHavingShades > 0)		// write ExtWall surfaces in SECOND round of processing when window shades enabled
								{	bProcessSurface = false;		iNumWinShadeSurfsSkipped++;		dWinShadeMaxDepth = 0.0;
									if (BEMPX_GetInteger( lDBID_ExtWall_WinShadeGeomReqd, lWinShadeGeomReqd, 0, BEMP_Int, iObjIdx ) && lWinShadeGeomReqd > 0)
									{	BEMPX_GetFloat( lDBID_ExtWall_Hgt, fArg6, fArg6, BEMP_Flt, iObjIdx );  // switch out PolyDZ with Hgt when WinShadeGeomReqd
										if (BEMPX_GetFloat( lDBID_ExtWall_WinShadeMaxDepth, fWinShadeMaxDepth, fWinShadeMaxDepth, BEMP_Flt, iObjIdx ) &&
												!WithinMargin( fWinShadeMaxDepth, 0.0, 0.01 ))
											dWinShadeMaxDepth = fWinShadeMaxDepth;
									}
									iOrientBucketIdx = AzimuthToOrientationBucketIdx( fAz );
//									InsertObjectByHeight( ivaClassIDs[iOrientBucketIdx], ivaObjIdxs[iOrientBucketIdx], fvaTopZ[iOrientBucketIdx], iCID_ExtWall, iObjIdx, fZ+fArg6 );
									AddObjectByZ( svWinShadeSurfs, iCID_ExtWall, iObjIdx, iOrientBucketIdx, fZ+fArg6,
														fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, dWinShadeMaxDepth );
								}
				// SAC 3/23/15 - added alternate scenario to base wall dimensions on 2/1 Wd/Ht aspect ratio for small walls where wall area < default wall height
								else if (fArg6 >= fArea && fArea > 0.01)
									fArg6 = sqrt( (fArea/2.0) );
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_IntFlr   )
							{	if (!BEMPX_GetFloat( lDBID_IntFlr_Area  , fArea, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_IntFlr_PolyAz, fAz  , -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_IntFlr_Tilt  , fTilt, -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_IntFlr_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))			sSurfErrMsg += ",  undefined";
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_IntWall  )
							{	if (!BEMPX_GetFloat( lDBID_IntWall_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_IntWall_PolyAz, fAz  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_IntWall_Tilt  , fTilt, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_IntWall_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_IntWall_PolyDZ, fArg6, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								iPolyType = 1;
				// SAC 3/23/15 - added alternate scenario to base wall dimensions on 2/1 Wd/Ht aspect ratio for small walls where wall area < default wall height
								if (fArg6 >= fArea && fArea > 0.01)
									fArg6 = sqrt( (fArea/2.0) );
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_Roof     )
							{	if (!BEMPX_GetFloat( lDBID_Roof_Area , fArea, -1, BEMP_Flt, iObjIdx ))				sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_Roof_Az   , fAz  , -1, BEMP_Flt, iObjIdx ))				sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_Roof_Tilt , fTilt, -1, BEMP_Flt, iObjIdx ))				sSurfErrMsg += ",  undefined";
								else if (fTilt <  0)                                                                sSurfErrMsg += ", Tilt not >= 0";
								if (!BEMPX_GetFloat( lDBID_Roof_PolyZ, fZ   , -1, BEMP_Flt, iObjIdx ))				sSurfErrMsg += ",  undefined";
								if (lNumWinsHavingShades > 0)		// write Roof surfaces in SECOND round of processing when window shades enabled
								{	bProcessSurface = false;		iNumWinShadeSurfsSkipped++;
									if (WithinMargin( fTilt, 0.0, 0.1 ) || WithinMargin( fTilt, 180.0, 0.1 ))
//									{	InsertObjectByHeight( ivaClassIDs[iRoofOrientBucketIdx], ivaObjIdxs[iRoofOrientBucketIdx], fvaTopZ[iRoofOrientBucketIdx], iCID_Roof, iObjIdx, fZ+1 );
									{	AddObjectByZ( svWinShadeSurfs, iCID_Roof, iObjIdx, iRoofOrientBucketIdx, fZ+1,
															fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, 0.0 );
										IncrementRoofBucketIndex( iRoofOrientBucketIdx );					assert( iRoofOrientBucketIdx >= 0 && iRoofOrientBucketIdx < 8 );
									}
									else
									{	iOrientBucketIdx = AzimuthToOrientationBucketIdx( fAz );
//										InsertObjectByHeight( ivaClassIDs[iOrientBucketIdx], ivaObjIdxs[iOrientBucketIdx], fvaTopZ[iOrientBucketIdx], iCID_Roof, iObjIdx, fZ+1 );
										AddObjectByZ( svWinShadeSurfs, iCID_Roof, iObjIdx, iOrientBucketIdx, fZ+1,
															fArea, fAz, fTilt, fZ, fArg6, fArg7, iPolyType, 0.0 );
									}
								}
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_UndgrFlr )
							{	if (!BEMPX_GetFloat( lDBID_UndgrFlr_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_UndgrFlr_PolyAz, fAz  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								if (!BEMPX_GetFloat( lDBID_UndgrFlr_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ",  undefined";
								fTilt = 180;
							}
							else if (pChildObj->getClass()->get1BEMClassIdx() == iCID_UndgrWall)
							{	if (!BEMPX_GetFloat( lDBID_UndgrWall_Area  , fArea, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Area undefined";
								else if (fArea <= 0)                                                                sSurfErrMsg += ", Area not > 0";
								if (!BEMPX_GetFloat( lDBID_UndgrWall_PolyAz, fAz  , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", PolyAz undefined";
								if (!BEMPX_GetFloat( lDBID_UndgrWall_PolyZ , fZ   , -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", PolyZ undefined";
								if (!BEMPX_GetFloat( lDBID_UndgrWall_Hgt   , fArg6, -1, BEMP_Flt, iObjIdx ))		sSurfErrMsg += ", Hgt undefined";
								else if (fArg6 <= 0)                                                                sSurfErrMsg += ", Hgt not > 0";
								fTilt = 90;
				// SAC 3/23/15 - added alternate scenario to base wall dimensions on 2/1 Wd/Ht aspect ratio for small walls where wall area < default wall height
								if (fArg6 >= fArea && fArea > 0.01)
									fArg6 = sqrt( (fArea/2.0) );
							}
							else
								bIsSurface = false;

							if (bIsSurface)
							{	if (!sSurfErrMsg.isEmpty())
								{	iRetVal = -3;
									sErrMsg = QString::asprintf( "Error gathering data to create PolyLp object:  %s '%s' %s", pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																							pChildObj->getName().toLocal8Bit().constData(), sSurfErrMsg.right( sSurfErrMsg.length()-2 ).toLocal8Bit().constData() );
								}
								else if (bProcessSurface)
								{	// call PolyLp creation routine
									iPolyLpObjIdx = BEMPX_CreatePolyLoop( fArea, fAz, fTilt, fZ, iPolyType, fArg6, fArg7, -1 /*iBEMProcIdx*/, &dFurthestInteriorFromXYOrig );
									if (iPolyLpObjIdx < 0)
									{	iRetVal = -4;
										sErrMsg = QString::asprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g) - BEMPX_CreatePolyLoop() returned %d",
																		pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																		pChildObj->getName().toLocal8Bit().constData(), fArea, fAz, fTilt, fZ, iPolyType, fArg6, fArg7, iPolyLpObjIdx );
									}
									else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
									{	iRetVal = -5;
										sErrMsg = QString::asprintf( "Error adding PolyLp child to %s '%s'", pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData() );
									}
									else
									{	iRetVal++;
										if (bVerbose)
										{	sLogMsg = QString::asprintf( "      PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", 
																		pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																		pChildObj->getName().toLocal8Bit().constData(), fArea, fAz, fTilt, fZ, iPolyType, fArg6, fArg7 );
											BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
									}	}
							}	}

							if (bProcessSurface && iRetVal>=0)
							{	AddChildPolyLoops( iRetVal, pChildObj, false /*(lNumWinsHavingShades > 0)*/, fArg6, fArea, fAz, fTilt, bVerbose, sErrMsg, 
															iCID_Win, lDBID_Win_Area, lDBID_Win_IsGlazedDoor, lDBID_Win_PolyZ, lDBID_Win_Hgt, lDBID_Win_X, lDBID_Win_Y,
															iCID_Dr,  lDBID_Dr_Area, lDBID_Dr_PolyZ, lDBID_Dr_Hgt, lDBID_Dr_X, lDBID_Dr_Y,
															iCID_Skylt, lDBID_Skylt_Area, lDBID_Skylt_PolyZ, lDBID_PolyLp_Parent, 0.0, 0.0, 0.0 );
							}
			}	}	}	}



//			std::vector <CWinShadeSurface> svWinShadeSurfs;	// organized radially in 8 buckets

//		class CWinShadeSurface
//			int	m_iClassID;
//			int	m_iObjectIdx;
//			int	m_iOrientationIdx;
//			double m_fZLevel;
//			// args to generate PolyLp
//			double m_fArea;
//			double m_fAz;
//			double m_fTilt;
//			double m_fZ;
//			double m_fArg6;
//			double m_fArg7;
//			int	m_iPolyType;



	// SAC 1/7/15 - special processing to generate window-shaded ExtWall & Roof surfaces radially to prevent unintended surface shading
	double dRadialMargin_Initial = 30.0;
	double dRadialMargin_BetweenSurfaces = 5.0;
	double dSideBySideExtWallMargin = 0.0;		// in addition to max ht of side-by-side walls
			if (iNumWinShadeSurfsSkipped > 0)
			{	int iError;
				double dInitDist = RoundDbl( dFurthestInteriorFromXYOrig + dRadialMargin_Initial, 1.0 );
				double daNextSurfDistByOrient[] = {  dInitDist, dInitDist, dInitDist, dInitDist, dInitDist, dInitDist, dInitDist, dInitDist };
				double daLastSurfBotZByOrient[] = {    99999.0,   99999.0,   99999.0,   99999.0,   99999.0,   99999.0,   99999.0,   99999.0 };
				double dMaxSecondaryRoofArea = 0.0;		int iLoopMax = 2;

				for (int iLoop=0; (iRetVal >= 0 && iLoop < iLoopMax); iLoop++)
				{	// outer loop to better handle roof surfaces (other than very first one)
					if (iLoop == 1)
					{	// adjust daNextSurfDistByOrient array to shift roof surfaces 2-N further away from all bldg centroid and ExtWalls
						double daStoreNSDByO[8];		int iOIdx;
						for (iOIdx=0; iOIdx<8; iOIdx++)
							daStoreNSDByO[iOIdx] = daNextSurfDistByOrient[iOIdx];
						for (iOIdx=0; iOIdx<8; iOIdx++)
							daNextSurfDistByOrient[iOIdx] = 4.0 * sqrt( dMaxSecondaryRoofArea ) +
										std::max( daStoreNSDByO[ iOIdx ], std::max( daStoreNSDByO[((iOIdx + 1) % 8)], daStoreNSDByO[((iOIdx + 7) % 8)] ) );
					}

					bool bFirstSurfaceProcessed = false;
					std::vector<CWinShadeSurface>::reverse_iterator it = svWinShadeSurfs.rbegin();
					for (; (iRetVal >= 0 && it != svWinShadeSurfs.rend()); ++it)
					{	if (!it->m_bSurfaceProcessed)		// don't re-process surface already handled in previous loop
						{
							std::vector <CWinShadeSurface*> svpWinShadeSurfs;		// shade surface pointer array
							double dOverallExtWallWidth = 0.0;
							if (it->m_iClassID == iCID_ExtWall && it->m_fArg6 > 0.01)
							{	// check for other ExtWall objects w/ same ZLevel and Azimuth
								dOverallExtWallWidth = 0;  // width = area / hgt
								double dMatchZLevel = it->m_fZLevel;
								double dMatchAz     = it->m_fAz    ;
								double  fMatchHeight = it->m_fArg6  ;
								double dMinZThisGroup = 99999.0;
								std::vector<CWinShadeSurface>::iterator it2 = svWinShadeSurfs.begin();
								bool bEWallChkDone = false;
								for (; !bEWallChkDone; it2++)
								{	if (!it2->m_bSurfaceProcessed && it2->m_iClassID == iCID_ExtWall && it2->m_fArg6 > 0.01 && 
											WithinMargin( dMatchZLevel, it2->m_fZLevel, 0.5 ) &&
											WithinMargin( dMatchAz    , it2->m_fAz    , 1.0 ) )
									{	// add this ExtWall to list of surfaces to process THIS round is the height is within 3" and Az within 1 deg
										if (dOverallExtWallWidth > 0.0)
											dOverallExtWallWidth += (dSideBySideExtWallMargin + std::max( fMatchHeight, it2->m_fArg6 ));
										it2->m_dSideBySideOffset = dOverallExtWallWidth;
										dOverallExtWallWidth += (it2->m_fArea / it2->m_fArg6);
										fMatchHeight = it2->m_fArg6;
										if (it2->m_fZ < dMinZThisGroup)
											dMinZThisGroup = it2->m_fZ;
										svpWinShadeSurfs.push_back( (CWinShadeSurface*) &(*it2) );
									}
									bEWallChkDone = (it2->m_iClassID == iCID_ExtWall && it2->m_iObjectIdx == it->m_iObjectIdx);
								}
							// cause this group of surfaces to be further away from bldg origin when top of these walls higher than bottom of previous wall(s) in this orientation bucket
								if (dMatchZLevel > daLastSurfBotZByOrient[it->m_iOrientationIdx])
									daNextSurfDistByOrient[it->m_iOrientationIdx] += (2 * (dMatchZLevel - daLastSurfBotZByOrient[it->m_iOrientationIdx]));
								daLastSurfBotZByOrient[it->m_iOrientationIdx] = dMinZThisGroup;
							}
							else if (it->m_iClassID == iCID_Roof)
							{	if (!bFirstSurfaceProcessed || iLoop == 1)
									svpWinShadeSurfs.push_back( (CWinShadeSurface*) &(*it) );
								else if (it->m_fArea > dMaxSecondaryRoofArea)
									dMaxSecondaryRoofArea = it->m_fArea;
							}

							int iNumSurfacesThisRound = (int) svpWinShadeSurfs.size(), iSurfIndex=0;
							std::vector<CWinShadeSurface*>::iterator itp = svpWinShadeSurfs.begin();
							for (; (iRetVal >= 0 && itp < svpWinShadeSurfs.end()); itp++)
							{	iSurfIndex++;
								bool bCenteredRoof = false;
								double dFurthestFromXYOrigin=0;
								double dOrientRadians = (*itp)->m_iOrientationIdx * sdHalfPi/2.0;

								if ((*itp)->m_iClassID == iCID_ExtWall)
								{							assert( (*itp)->m_fArea > 0 && (*itp)->m_fArg6 > 0 );
									double dHalfWallWd = dOverallExtWallWidth / 2.0;		// was:  ((*itp)->m_fArea > 0 && (*itp)->m_fArg6 > 0) ? ((*itp)->m_fArea / (*itp)->m_fArg6) / 2.0 : 30.0;
									double dStartWallRads = dOrientRadians - atan2( dHalfWallWd, daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] );
									double dStartWallDist = sqrt( (daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] * daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ]) + (dHalfWallWd * dHalfWallWd) );
									(*itp)->m_dDX = RoundDbl( cos( dStartWallRads ) * dStartWallDist, 1.0 );
									(*itp)->m_dDY = RoundDbl( sin( dStartWallRads ) * dStartWallDist, 1.0 );
									if ((*itp)->m_dSideBySideOffset > 0)
									{	// this is the 2nd-nth wall to be generated side-by-side in the same plane, so we need to shift its starting position so as not to overlap other walls in this plane
										double dSeg1Ang = (180. - (*itp)->m_fAz + ((*itp)->m_fAz > 180. ? 360. : 0.)) * sdPi / 180.;
										(*itp)->m_dDX = (*itp)->m_dDX + RoundDbl( ( (*itp)->m_dSideBySideOffset * cos( dSeg1Ang ) ), 1000. );	// minor rounding to prevent excessive decimal precision (and 0.0 weirdness)
										(*itp)->m_dDY = (*itp)->m_dDY + RoundDbl( ( (*itp)->m_dSideBySideOffset * sin( dSeg1Ang ) ), 1000. );
									}
									if (BEMPX_GetInteger( lDBID_ExtWall_WinShadeGeomReqd, lWinShadeGeomReqd, 0, BEMP_Int, (*itp)->m_iObjectIdx ) && lWinShadeGeomReqd > 0)
										(*itp)->m_bWinShadeChildren = true;
								}
								else if ((*itp)->m_iClassID == iCID_Roof)
								{	double dHalfWd = sqrt( (*itp)->m_fArea )/2.0;
									if (it == svWinShadeSurfs.rbegin()) // special processing for when the topmost surface is a Roof - we center it in the model
									{	bCenteredRoof = true;
										double dRfPosAngle = (180 - (*itp)->m_fAz - 135) * sdPi / 180.0;
										double dRfPosDist = sqrt( 2*dHalfWd*dHalfWd );
										(*itp)->m_dDX = RoundDbl( cos( dRfPosAngle ) * dRfPosDist, 1.0 );
										(*itp)->m_dDY = RoundDbl( sin( dRfPosAngle ) * dRfPosDist, 1.0 );
								//		dDX = int(  dHalfWd + 0.5 );
								//		dDY = int( -dHalfWd - 0.5 );
									}
									else
									{	double dStartRads = dOrientRadians - atan2( dHalfWd, daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] );
										double dStartDist = sqrt( (daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] * daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ]) + (dHalfWd * dHalfWd) );
										(*itp)->m_dDX = RoundDbl( cos( dStartRads ) * dStartDist, 1.0 );
										(*itp)->m_dDY = RoundDbl( sin( dStartRads ) * dStartDist, 1.0 );
								}	}

								BEMObject* pChildObj = BEMPX_GetObjectByClass( (*itp)->m_iClassID, iError, (*itp)->m_iObjectIdx, BEMO_User, -1 /*iBEMProcIdx*/ );			assert( pChildObj && pChildObj->getClass() );
								if (pChildObj && pChildObj->getClass())
								{
								// call PolyLp creation routine
									iPolyLpObjIdx = BEMPX_CreatePolyLoop( (*itp)->m_fArea, (*itp)->m_fAz, (*itp)->m_fTilt, (*itp)->m_fZ, (*itp)->m_iPolyType, (*itp)->m_fArg6, (*itp)->m_fArg7, -1 /*iBEMProcIdx*/,
																						&dFurthestFromXYOrigin, (*itp)->m_dDX, (*itp)->m_dDY, (*itp)->m_dDZ );
									(*itp)->m_bSurfaceProcessed = true;
									bFirstSurfaceProcessed = true;
									if (iPolyLpObjIdx < 0)
									{	iRetVal = -4;
										sErrMsg = QString::asprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", 
																		pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData(),
																		(*itp)->m_fArea, (*itp)->m_fAz, (*itp)->m_fTilt, (*itp)->m_fZ, (*itp)->m_iPolyType, (*itp)->m_fArg6, (*itp)->m_fArg7 );
									}
									else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
									{	iRetVal = -5;
										sErrMsg = QString::asprintf( "Error adding PolyLp child to %s '%s'", pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData() );
									}
									else
									{	iRetVal++;
										if (bVerbose)
										{	sLogMsg = QString::asprintf( "      PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																		pChildObj->getName().toLocal8Bit().constData(), (*itp)->m_fArea, (*itp)->m_fAz, (*itp)->m_fTilt, (*itp)->m_fZ, (*itp)->m_iPolyType, (*itp)->m_fArg6, (*itp)->m_fArg7 );
											BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
									}	}

									if (iRetVal>=0)
									{	AddChildPolyLoops( iRetVal, pChildObj, (*itp)->m_bWinShadeChildren, (*itp)->m_fArg6, (*itp)->m_fArea, (*itp)->m_fAz, (*itp)->m_fTilt, bVerbose, sErrMsg, 
																	iCID_Win, lDBID_Win_Area, lDBID_Win_IsGlazedDoor, lDBID_Win_PolyZ, lDBID_Win_Hgt, lDBID_Win_X, lDBID_Win_Y,
																	iCID_Dr,  lDBID_Dr_Area, lDBID_Dr_PolyZ, lDBID_Dr_Hgt, lDBID_Dr_X, lDBID_Dr_Y,
																	iCID_Skylt, lDBID_Skylt_Area, lDBID_Skylt_PolyZ, lDBID_PolyLp_Parent, (*itp)->m_dDX, (*itp)->m_dDY, (*itp)->m_dDZ );

									// and finally adjust distances for next surface (in this and adjoining directions)
										if (bCenteredRoof)
										{	if (dFurthestFromXYOrigin > dFurthestInteriorFromXYOrig)
											{
												dInitDist = RoundDbl( dFurthestFromXYOrigin + dRadialMargin_Initial, 1.0 );
												for (int iRI=0; iRI < 8; iRI++)
													daNextSurfDistByOrient[iRI] = dInitDist;
										}	}
										else if (iSurfIndex == iNumSurfacesThisRound)	// don't increment daNextSurfDistByOrient[] between ExtWall surfaces positioned in the same plane
										{
											double dDistInc = dFurthestFromXYOrigin - daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ];		assert( dDistInc >= 0 );
											int iAdjOrientIdx = ((*itp)->m_iOrientationIdx + 1) % 8;
											daNextSurfDistByOrient[ iAdjOrientIdx ] = std::max( daNextSurfDistByOrient[ iAdjOrientIdx ], (daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] + dDistInc + dRadialMargin_BetweenSurfaces/2.0) );
											iAdjOrientIdx = ((*itp)->m_iOrientationIdx + 7) % 8;
											daNextSurfDistByOrient[ iAdjOrientIdx ] = std::max( daNextSurfDistByOrient[ iAdjOrientIdx ], (daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] + dDistInc + dRadialMargin_BetweenSurfaces/2.0) );
											daNextSurfDistByOrient[ (*itp)->m_iOrientationIdx ] += (dDistInc + dRadialMargin_BetweenSurfaces);
									}	}

								}
							}	// loop over surfaces to create, which may be multiple ExtWalls in same plane

					}	}
					if (dMaxSecondaryRoofArea < 0.1)
						iLoopMax = 1;		// if NO secondary Roof surfaces were encountered, then there is no need to execute the second iLoop loop
				}	// end of for (iLoop) loop
			}
	}	}

	if (!sErrMsg.isEmpty())
		BEMPX_WriteLogFile( sErrMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
	else if (bVerbose)
	{	sLogMsg = QString::asprintf( "   %d PolyLp objects created by CMX_GeneratePolyLoops_CECNonRes()", iRetVal );
		BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
	}

	return iRetVal;
}


int CMX_AdjustDataModelForGeometryInpType_CECNonRes()	// SAC 3/23/14 - port from UI
{	int iRetVal = 0;

	QString sGeometryInpType;
	long lIsDetailedGeometry = (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:GeometryInpType" ), sGeometryInpType ) &&
											!sGeometryInpType.isEmpty() && sGeometryInpType.compare("Simplified", Qt::CaseInsensitive) == 0) ? 0 : 1;

	int ieCompDT     = (lIsDetailedGeometry == 0) ? BEMD_Compulsory : BEMD_NotInput;
//	int ieCompDT_CR  = (lIsDetailedGeometry == 0) ? BEMD_Compulsory : BEMD_Required;
	int ieCompDT_RN  = (lIsDetailedGeometry == 0) ? BEMD_Required   : BEMD_NotInput;		// SAC 1/5/15 - added to accommodate window shade feature
	int ieCompDT_ON  = (lIsDetailedGeometry == 0) ? BEMD_Optional   : BEMD_NotInput;		// SAC 1/11/15 - added to accommodate window shade feature
//	int ieCompDTReqd = (lIsDetailedGeometry == 0) ? BEMD_Optional   : BEMD_Required;
	bool bPrimary    = (lIsDetailedGeometry == 0) ? true : false;
	bool bEditable = bPrimary, bUserDefaultable = bPrimary;
	bool bDispInp = true, bDispProp = true, bDispBudg = true;
	// and then make certain adjustments to BEMBase property input classes to ensure that properties required for simplified geometry are marked as such (& marked as NotInput for detailed geometry)
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Story:Z"                ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Story:FlrToFlrHgt"      ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Story:FlrToCeilingHgt"  ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Ceiling:Area"           ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Door:Area"              ), ieCompDT_RN , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "ExtFlr:Area"            ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "ExtWall:Area"           ), ieCompDT_RN , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "ExtWall:Azimuth"        ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "ExtWall:Tilt"           ), ieCompDT_ON ,   false  , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "IntFlr:Area"            ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "IntWall:Area"           ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Roof:Area"              ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Roof:Azimuth"           ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Roof:Tilt"              ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Skylight:Area"          ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Spc:Area"               ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );	// SAC 6/5/15 - was ieCompDT_CR
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Spc:Perim"              ), ieCompDT_ON ,   false  , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );	// SAC 1/21/15
//	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Spc:FlrArea"            ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
//	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Spc:FlrToCeilingHgt"    ), ieCompDTReqd, false    , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );   - keep Optional for both simplified & detailed geometry
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "UndgrFlr:Area"          ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "UndgrWall:Area"         ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "Window:Area"            ), ieCompDT_RN , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
//	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "CeilingBelowAttic:Area" ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );
//	BEMPX_SetPropertyTypeDetails( BEMPX_GetDatabaseID( "FlrAboveCrawlSpc:Area"  ), ieCompDT    , bPrimary , bEditable, bUserDefaultable, bDispInp, bDispProp, bDispBudg, DTNotInp_AllowUIReset, "" );

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

static inline double LineAngle( double dX1, double dX2, double dY1, double dY2, double dMargin )
{	if (WithinMargin( dY1, dY2, dMargin ))
	{	if (dX2 > dX1)
			return 0.0;
		else
			return sdPi;
	}
	else if (WithinMargin( dX1, dX2, dMargin ))
	{	if (dY2 > dY1)
			return sdHalfPi;
		else
			return sd3HalfPi;
	}
	double dAng = atan2( (dY2-dY1), (dX2-dX1) );
	return (dAng < -0.000005 ? dAng + sd2Pi : dAng);
}

static inline double ValOrZero( double dVal, double dMargin )
{	if (WithinMargin( dVal, 0.0, dMargin ))
		return 0.0;
	return dVal;
}


int CreateWindowShadeObject( BEMObject* pWinObj, int iWin, BEMObject* pGParentSpcObj, QString sAppendToName, const char* pszShadeDescrip, QString& sErrMsg, long lObjRefDBID,
											double* pdX, double* pdY, double* pdZ, long lDBID_Win_TransOption, long lDBID_Win_Trans, long lDBID_Win_TransSchRef )
{	int iRetVal = 0;
	QString sBEMErr;
	int iCID_ExtShdgObj	= GetBEMBaseCompID( sBEMErr, "ExtShdgObj" );
	int iCID_PolyLp		= GetBEMBaseCompID( sBEMErr, "PolyLp" );
	int iCID_CartesianPt	= GetBEMBaseCompID( sBEMErr, "CartesianPt" );
	long lDBID_CartesianPt_Coord = (iCID_CartesianPt > 0 ? GetBEMBaseDBID( sBEMErr, "Coord", iCID_CartesianPt ) : 0);
	long lDBID_ExtShdgObj_TransOption  = (iCID_ExtShdgObj > 0 ? GetBEMBaseDBID( sBEMErr, "TransOption", iCID_ExtShdgObj ) : 0);
	long lDBID_ExtShdgObj_Trans        = (iCID_ExtShdgObj > 0 ? GetBEMBaseDBID( sBEMErr, "Trans",       iCID_ExtShdgObj ) : 0);
	long lDBID_ExtShdgObj_TransSchRef  = (iCID_ExtShdgObj > 0 ? GetBEMBaseDBID( sBEMErr, "TransSchRef", iCID_ExtShdgObj ) : 0);
	long lDBID_ExtShdgObj_WinRef       = (iCID_ExtShdgObj > 0 ? GetBEMBaseDBID( sBEMErr, "WinRef",      iCID_ExtShdgObj ) : 0);	// SAC 9/14/16 - added to enable ExtShdgObj rules to reference the Win they shade
	if (sBEMErr.length() > 0)
	{	iRetVal = -2;
		sErrMsg = QString::asprintf( "Error retrieving BEMBase CreateWindowShadeObject ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
	}
	else
	{	QString sShadeName = (pWinObj ? pWinObj->getName() : "Window");
		sShadeName += sAppendToName;
		BEMObject* pShdObj = BEMPX_CreateObject( iCID_ExtShdgObj, sShadeName.toLocal8Bit().constData(), pGParentSpcObj );  // , BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE, bool bAutoCreate = TRUE, int iBEMProcIdx=-1, BOOL bIgnoreMaxDefinable=FALSE, int i0ChildIdx =-1 );
		if (pShdObj == NULL)
		{	iRetVal = -3;
			sErrMsg = QString::asprintf( "Error creating %s ExtShdgObj for window '%s'", pszShadeDescrip, (pWinObj ? pWinObj->getName().toLocal8Bit().constData() : "unknown") );
		}
		else
		{	// set reference to this ExtShdgObj to Win
			int iESOIdx = BEMPX_GetObjectIndex( pShdObj->getClass(), pShdObj /*, int iBEMProcIdx=-1*/ );			assert( iESOIdx >= 0 );
			BEMPX_SetBEMData( lObjRefDBID, BEMP_Obj, (void*) pShdObj, BEMO_User, iWin );
			long lFlag1 = 1;
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "IsWinShade", iCID_ExtShdgObj ), BEMP_Int, (void*) &lFlag1, BEMO_User, iESOIdx );		// SAC 1/9/15 - set flag identifying this as a WinShade object
			BEMPX_SetBEMData( lDBID_ExtShdgObj_WinRef, BEMP_Obj, (void*) pWinObj, BEMO_User, iESOIdx );	// SAC 9/14/16

		// pass Trans* property values from Win* to ExtShdgObj
			QString sTransOpt, sTransSched;		double fTrans;
			if (BEMPX_GetString( lDBID_Win_TransOption, sTransOpt, FALSE, 0, -1, iWin ) && !sTransOpt.isEmpty())
			{	if (sTransOpt.indexOf( "Sched" ) >= 0)
				{	if (BEMPX_GetString( lDBID_Win_TransSchRef, sTransSched, FALSE, 0, -1, iWin ) && !sTransSched.isEmpty())
					{	BEMPX_SetBEMData( lDBID_ExtShdgObj_TransOption, BEMP_QStr, (void*) &sTransOpt  , BEMO_User, iESOIdx );
						BEMPX_SetBEMData( lDBID_ExtShdgObj_TransSchRef, BEMP_QStr, (void*) &sTransSched, BEMO_User, iESOIdx );
					}
					else
					{	assert( FALSE );
				}	}
				else
				{	if (BEMPX_GetFloat( lDBID_Win_Trans, fTrans, -1, -1, iWin ) && fTrans >= 0 && fTrans <= 1)
					{	BEMPX_SetBEMData( lDBID_ExtShdgObj_TransOption, BEMP_QStr, (void*) &sTransOpt, BEMO_User, iESOIdx );
						BEMPX_SetBEMData( lDBID_ExtShdgObj_Trans      , BEMP_Flt, (void*) &fTrans                  , BEMO_User, iESOIdx );
					}
					else
					{	assert( FALSE );
			}	}	}
			else
			{	assert( FALSE );
			}


		// CREATE NEW PolyLp to define ExtShdgObj's geometry
			BEMObject* pPolyLpObj = BEMPX_CreateObject( iCID_PolyLp, NULL, pShdObj );
			if (pPolyLpObj == NULL)
			{	iRetVal = -4;
				sErrMsg = QString::asprintf( "Error creating PolyLp to store geometry for %s '%s' of window '%s'", pszShadeDescrip, pShdObj->getName().toLocal8Bit().constData(), 
																(pWinObj ? pWinObj->getName().toLocal8Bit().constData() : "unknown") );
			}
			else
			{	double faCoord[3];
				for (int iCoord=0; (iRetVal>=0 && iCoord < 4); iCoord++)
				{	BEMObject* pCoordObj = BEMPX_CreateObject( iCID_CartesianPt, NULL, pPolyLpObj );
					if (pCoordObj == NULL)
					{	iRetVal = -5;
						sErrMsg = QString::asprintf( "Error creating CartesianPt #%d to store geometry for %s '%s' of window '%s'", iCoord+1, pszShadeDescrip, 
																pShdObj->getName().toLocal8Bit().constData(), (pWinObj ? pWinObj->getName().toLocal8Bit().constData() : "unknown") );
					}
					else
					{	faCoord[0] = ValOrZero( pdX[iCoord], 0.0001 );		faCoord[1] = ValOrZero( pdY[iCoord], 0.0001 );		faCoord[2] = ValOrZero( pdZ[iCoord], 0.0001 );
						BEMPX_SetBEMData( lDBID_CartesianPt_Coord  , BEMP_Flt, (void*) &faCoord[0], BEMO_User, -1 );
						BEMPX_SetBEMData( lDBID_CartesianPt_Coord+1, BEMP_Flt, (void*) &faCoord[1], BEMO_User, -1 );
						BEMPX_SetBEMData( lDBID_CartesianPt_Coord+2, BEMP_Flt, (void*) &faCoord[2], BEMO_User, -1 );
					}
				}
				if (iRetVal >= 0)
					iRetVal++;
			}
	}	}
	return iRetVal;
}


//		Return Values:	>=	0 =>	SUCCESS
//							<  0 =>	Error Code:
//											 -1 : Error retrieving BEMBase object ID(s)
//											 -2 : Error retrieving BEMBase property ID(s)
//											 -3 : Error creating new ExtShdgObj
//											 -4 : Error creating PolyLp for new ExtShdgObj
//											 -5 : Error creating CartesianPt for new ExtShdgObj
//											 -6 : Error 
int CMX_GenerateWindowShades_CECNonRes( bool bVerbose, bool /*bStoreBEMDetails*/, bool /*bSilent*/, QString& sErrMsg )
{	int iRetVal = 0;
	QString sLogMsg, sBEMErr, sWinName, sTemp, sMissingPolyLpWins, sBadPolyLpDataWins, sHorizWins;
	int iNumWinsProcessed=0, iNumWinsMissingPolyLp=0, iNumWinsBadPolyLpData=0, iNumHorizWins=0;
//	int iCID_ExtWall		= GetBEMBaseCompID( sBEMErr, "ExtWall" );
	int iCID_Win			= GetBEMBaseCompID( sBEMErr, "Win" );
//	int iCID_ExtShdgObj	= GetBEMBaseCompID( sBEMErr, "ExtShdgObj" );
	int iCID_PolyLp		= GetBEMBaseCompID( sBEMErr, "PolyLp" );
//	int iCID_CartesianPt	= GetBEMBaseCompID( sBEMErr, "CartesianPt" );
	if (sBEMErr.length() > 0)
	{	iRetVal = -1;
		sErrMsg = QString::asprintf( "Error retrieving BEMBase CMX_GenerateWindowShades object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
	}
	else
	{	//long lDBID_Win_Area                   = GetBEMBaseDBID( sBEMErr, "Area", iCID_Win );
		long lDBID_Win_Name                   = GetBEMBaseDBID( sBEMErr, "Name",                   iCID_Win );
		long lDBID_Win_AllowWinShades         = GetBEMBaseDBID( sBEMErr, "AllowWinShades",         iCID_Win );
		long lDBID_Win_EnableWinShades        = GetBEMBaseDBID( sBEMErr, "EnableWinShades",        iCID_Win );
		long lDBID_Win_OverhangDepth          = GetBEMBaseDBID( sBEMErr, "OverhangDepth",          iCID_Win );
		long lDBID_Win_OverhangDistance       = GetBEMBaseDBID( sBEMErr, "OverhangDistance",       iCID_Win );
		long lDBID_Win_OverhangLeftExtension  = GetBEMBaseDBID( sBEMErr, "OverhangLeftExtension",  iCID_Win );
		long lDBID_Win_OverhangRightExtension = GetBEMBaseDBID( sBEMErr, "OverhangRightExtension", iCID_Win );
		long lDBID_Win_OverhangAngle          = GetBEMBaseDBID( sBEMErr, "OverhangAngle",          iCID_Win );
		long lDBID_Win_OverhangTransOption    = GetBEMBaseDBID( sBEMErr, "OverhangTransOption",    iCID_Win );
		long lDBID_Win_OverhangTrans          = GetBEMBaseDBID( sBEMErr, "OverhangTrans",          iCID_Win );
		long lDBID_Win_OverhangTransSchRef    = GetBEMBaseDBID( sBEMErr, "OverhangTransSchRef",    iCID_Win );
		long lDBID_Win_LeftFinDepth           = GetBEMBaseDBID( sBEMErr, "LeftFinDepth",           iCID_Win );
		long lDBID_Win_LeftFinDistance        = GetBEMBaseDBID( sBEMErr, "LeftFinDistance",        iCID_Win );
		long lDBID_Win_LeftFinDistanceAbove   = GetBEMBaseDBID( sBEMErr, "LeftFinDistanceAbove",   iCID_Win );
		long lDBID_Win_LeftFinDistanceBelow   = GetBEMBaseDBID( sBEMErr, "LeftFinDistanceBelow",   iCID_Win );
		long lDBID_Win_LeftFinAngle           = GetBEMBaseDBID( sBEMErr, "LeftFinAngle",           iCID_Win );
		long lDBID_Win_LeftFinTransOption     = GetBEMBaseDBID( sBEMErr, "LeftFinTransOption",     iCID_Win );
		long lDBID_Win_LeftFinTrans           = GetBEMBaseDBID( sBEMErr, "LeftFinTrans",           iCID_Win );
		long lDBID_Win_LeftFinTransSchRef     = GetBEMBaseDBID( sBEMErr, "LeftFinTransSchRef",     iCID_Win );
		long lDBID_Win_RightFinDepth          = GetBEMBaseDBID( sBEMErr, "RightFinDepth",          iCID_Win );
		long lDBID_Win_RightFinDistance       = GetBEMBaseDBID( sBEMErr, "RightFinDistance",       iCID_Win );
		long lDBID_Win_RightFinDistanceAbove  = GetBEMBaseDBID( sBEMErr, "RightFinDistanceAbove",  iCID_Win );
		long lDBID_Win_RightFinDistanceBelow  = GetBEMBaseDBID( sBEMErr, "RightFinDistanceBelow",  iCID_Win );
		long lDBID_Win_RightFinAngle          = GetBEMBaseDBID( sBEMErr, "RightFinAngle",          iCID_Win );
		long lDBID_Win_RightFinTransOption    = GetBEMBaseDBID( sBEMErr, "RightFinTransOption",    iCID_Win );
		long lDBID_Win_RightFinTrans          = GetBEMBaseDBID( sBEMErr, "RightFinTrans",          iCID_Win );
		long lDBID_Win_RightFinTransSchRef    = GetBEMBaseDBID( sBEMErr, "RightFinTransSchRef",    iCID_Win );
		long lDBID_Win_OverhangRef            = GetBEMBaseDBID( sBEMErr, "OverhangRef",            iCID_Win );  // BEMP_Obj,  Pres,    1, "ExtShdgObj",  0, "",  "OverhangReference",  "" 
		long lDBID_Win_LeftFinRef             = GetBEMBaseDBID( sBEMErr, "LeftFinRef",             iCID_Win );  // BEMP_Obj,  Pres,    1, "ExtShdgObj",  0, "",  "LeftFinReference",  "" 
		long lDBID_Win_RightFinRef            = GetBEMBaseDBID( sBEMErr, "RightFinRef",            iCID_Win );  // BEMP_Obj,  Pres,    1, "ExtShdgObj",  0, "",  "RightFinReference",  "" 
//		long lDBID_PolyLp_Area         = GetBEMBaseDBID( sBEMErr, "Area",         iCID_PolyLp );
//		long lDBID_PolyLp_NumOfPts     = GetBEMBaseDBID( sBEMErr, "NumOfPts",     iCID_PolyLp );
//		long lDBID_PolyLp_ParentInfrm  = GetBEMBaseDBID( sBEMErr, "ParentInfrm",  iCID_PolyLp );
		long lDBID_PolyLp_XYLen        = GetBEMBaseDBID( sBEMErr, "XYLen",        iCID_PolyLp );
//		long lDBID_PolyLp_ZBottom      = GetBEMBaseDBID( sBEMErr, "ZBottom",      iCID_PolyLp );
		long lDBID_PolyLp_ZTop         = GetBEMBaseDBID( sBEMErr, "ZTop",         iCID_PolyLp );
		long lDBID_PolyLp_ZHgt         = GetBEMBaseDBID( sBEMErr, "ZHgt",         iCID_PolyLp );
//		long lDBID_PolyLp_ZRngMessage  = GetBEMBaseDBID( sBEMErr, "ZRngMessage",  iCID_PolyLp );
		long lDBID_PolyLp_XCenter      = GetBEMBaseDBID( sBEMErr, "XCenter",      iCID_PolyLp );
		long lDBID_PolyLp_YCenter      = GetBEMBaseDBID( sBEMErr, "YCenter",      iCID_PolyLp );
//		long lDBID_PolyLp_VectorOi     = GetBEMBaseDBID( sBEMErr, "VectorOi",     iCID_PolyLp );
//		long lDBID_PolyLp_VectorOj     = GetBEMBaseDBID( sBEMErr, "VectorOj",     iCID_PolyLp );
//		long lDBID_PolyLp_VectorOk     = GetBEMBaseDBID( sBEMErr, "VectorOk",     iCID_PolyLp );
//		long lDBID_PolyLp_VectorOLen   = GetBEMBaseDBID( sBEMErr, "VectorOLen",   iCID_PolyLp );
		long lDBID_PolyLp_UnitVectorOi = GetBEMBaseDBID( sBEMErr, "UnitVectorOi", iCID_PolyLp );
		long lDBID_PolyLp_UnitVectorOj = GetBEMBaseDBID( sBEMErr, "UnitVectorOj", iCID_PolyLp );
		long lDBID_PolyLp_UnitVectorOk = GetBEMBaseDBID( sBEMErr, "UnitVectorOk", iCID_PolyLp );
//		long lDBID_PolyLp_VectorPLen   = GetBEMBaseDBID( sBEMErr, "VectorPLen",   iCID_PolyLp );
//		long lDBID_PolyLp_UnitVectorPi = GetBEMBaseDBID( sBEMErr, "UnitVectorPi", iCID_PolyLp );
//		long lDBID_PolyLp_UnitVectorPj = GetBEMBaseDBID( sBEMErr, "UnitVectorPj", iCID_PolyLp );
//		long lDBID_PolyLp_Parent       = GetBEMBaseDBID( sBEMErr, "Parent", iCID_PolyLp );
//   	long lDBID_CartesianPt_Coord = GetBEMBaseDBID( sBEMErr, "Coord", iCID_CartesianPt );
		if (sBEMErr.length() > 0)
		{	iRetVal = -2;
			sErrMsg = QString::asprintf( "Error retrieving BEMBase CMX_GenerateWindowShades property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
		}
		else
		{	int iError, iNumWins = BEMPX_GetNumObjects( iCID_Win );
//			double fArea, fAz, fTilt, fZ, fArg6, fArg7;
//			int iPolyType, iPolyLpObjIdx;
//			long lIsGlazedDr;
//			bool bIsSurface;
//			QString sSurfErrMsg;
			for (int iWin=0; (iRetVal>=0 && iWin < iNumWins); iWin++)
			{	long lAllow, lEnable;
				double fOverhangDepth, fLeftFinDepth, fRightFinDepth;
				BEMPX_GetFloat( lDBID_Win_OverhangDepth, fOverhangDepth, -1, BEMP_Flt, iWin );
				BEMPX_GetFloat( lDBID_Win_LeftFinDepth , fLeftFinDepth , -1, BEMP_Flt, iWin );
				BEMPX_GetFloat( lDBID_Win_RightFinDepth, fRightFinDepth, -1, BEMP_Flt, iWin );
				if (	BEMPX_GetInteger( lDBID_Win_AllowWinShades , lAllow , -1, BEMP_Int, iWin ) && lAllow  &&
						BEMPX_GetInteger( lDBID_Win_EnableWinShades, lEnable, -1, BEMP_Int, iWin ) && lEnable &&
					 ( fOverhangDepth > 0.0001 || fLeftFinDepth  > 0.0001 || fRightFinDepth > 0.0001 ) &&
						BEMPX_GetString( lDBID_Win_Name, sWinName, FALSE, 0, BEMP_Str, iWin ) )
				{
				// gather generic info to support all window shade polygon creation
					BEM_ObjType eChildObjType;
					int iPolyIdx = BEMPX_GetChildObjectIndex( iCID_Win, iCID_PolyLp, iError, eChildObjType, 1 /*i1ChildIdx*/, iWin );  // , BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
					if (iPolyIdx < 0)
					{	iNumWinsMissingPolyLp++;
						sTemp = QString::asprintf( "%s'%s' (#%d)", (sMissingPolyLpWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
						sMissingPolyLpWins += sTemp;
					}
					else
					{	// have index of PolyLp describing the Window
						double fXYLen, fXCenter, fYCenter, fZHgt, fZTop, fUnitVectorOi, fUnitVectorOj, fUnitVectorOk;
						if (!BEMPX_GetFloat( lDBID_PolyLp_XYLen       , fXYLen,        -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_XCenter     , fXCenter,      -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_YCenter     , fYCenter,      -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_ZHgt        , fZHgt,         -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_ZTop        , fZTop,         -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_UnitVectorOi, fUnitVectorOi, -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_UnitVectorOj, fUnitVectorOj, -1, BEMP_Flt, iPolyIdx ) ||
							 !BEMPX_GetFloat( lDBID_PolyLp_UnitVectorOk, fUnitVectorOk, -1, BEMP_Flt, iPolyIdx ) )
						{	iNumWinsBadPolyLpData++;
							sTemp = QString::asprintf( "%s'%s' (#%d)", (sBadPolyLpDataWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
							sBadPolyLpDataWins += sTemp;
						}
						else if (fXYLen < 0.0001 || (WithinMargin( fUnitVectorOi, 0.0, 0.0001 ) && WithinMargin( fUnitVectorOj, 0.0, 0.0001 )))
						{	iNumHorizWins++;
							sTemp = QString::asprintf( "%s'%s' (#%d)", (sHorizWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
							sHorizWins += sTemp;
						}
						else
						{	// Win PolyLp data valid
							double dXCtr = fXCenter, dYCtr = fYCenter;
				//			double dZCtr = (fZTop - (fZHgt / 2.0));
				//			double dXYNormalAngle = atan2( fUnitVectorOj, fUnitVectorOi );	// XYNormalAngle in radians (in range -pi to +pi)
				//			double dXYAngleToLeftEdge  = dXYNormalAngle + (dXYNormalAngle < -sdHalfPi ?  sd3HalfPi : -sdHalfPi);		// (in range -pi to +pi)
				//			double dXYAngleToRightEdge = dXYNormalAngle + (dXYNormalAngle >  sdHalfPi ? -sd3HalfPi :  sdHalfPi);		// (in range -pi to +pi)
							double dXYNormalAngle = LineAngle( 0, fUnitVectorOi, 0, fUnitVectorOj, 0.001 );	// XYNormalAngle in radians (in range 0 to 2pi)
							double dXYAngleToLeftEdge  = dXYNormalAngle + (dXYNormalAngle <  sdHalfPi ?  sd3HalfPi : -sdHalfPi);		// (in range 0 to 2pi)
							double dXYAngleToRightEdge = dXYNormalAngle + (dXYNormalAngle > sd3HalfPi ? -sd3HalfPi :  sdHalfPi);		// (in range 0 to 2pi)
							double dXLeftCtr  = dXCtr + ((fXYLen/2.0) * cos( dXYAngleToLeftEdge  ));
							double dYLeftCtr  = dYCtr + ((fXYLen/2.0) * sin( dXYAngleToLeftEdge  ));
							double dXRightCtr = dXCtr + ((fXYLen/2.0) * cos( dXYAngleToRightEdge ));
							double dYRightCtr = dYCtr + ((fXYLen/2.0) * sin( dXYAngleToRightEdge ));
							double dZAngle, dXYHyp, dX[4], dY[4], dZ[4];

						// process this window for shades to be generated
							iNumWinsProcessed++;
							BEMObject* pWinObj = BEMPX_GetObjectByClass( iCID_Win, iError, iWin );										assert( pWinObj );
							BEMObject* pParentWallObj = (pWinObj        == NULL ? NULL : pWinObj->getParent()       );		assert( pParentWallObj );
							BEMObject* pGParentSpcObj = (pParentWallObj == NULL ? NULL : pParentWallObj->getParent());		assert( pGParentSpcObj );
							BEMObject *pShdObj;

//	QString	getName();       // Name of the building component
//	BEMClass*	getClass();            // Pointer to BEMClass instance which defines this component type
//	BEMObject*	getParent();           // Pointer to this components parent component


						// OVERHANG creation
							if (BEMPX_GetObject( lDBID_Win_OverhangRef, pShdObj, -1, iWin ) && pShdObj)
								BEMPX_DeleteObject( pShdObj );  // DELETE an existing overhang assigned to this Win
							if (fOverhangDepth > 0.0001)
							{	double fODist, fOLeftExt, fORightExt, fOAngle;
							 	BEMPX_GetFloat( lDBID_Win_OverhangDistance      , fODist    , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_OverhangLeftExtension , fOLeftExt , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_OverhangRightExtension, fORightExt, -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_OverhangAngle         , fOAngle   , -1, BEMP_Flt, iWin );

								dXLeftCtr  = dXCtr + (((fXYLen/2.0) + fOLeftExt ) * cos( dXYAngleToLeftEdge  ));
								dYLeftCtr  = dYCtr + (((fXYLen/2.0) + fOLeftExt ) * sin( dXYAngleToLeftEdge  ));
								dXRightCtr = dXCtr + (((fXYLen/2.0) + fORightExt) * cos( dXYAngleToRightEdge ));
								dYRightCtr = dYCtr + (((fXYLen/2.0) + fORightExt) * sin( dXYAngleToRightEdge ));
					//			dZAngle = (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ) ? 0.0 : asin( fUnitVectorOk ));
								dXYHyp = sqrt( (fUnitVectorOi*fUnitVectorOi) + (fUnitVectorOj*fUnitVectorOj) );
								dZAngle = LineAngle( 0, dXYHyp, 0, fUnitVectorOk, 0.001 );	// radians (in range 0 to 2pi)
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
								{	// normal vector is parallel to ground, so Z straight up => X,Y locations same @ overhang level than @ mid-window
									dX[0] = dXLeftCtr;
									dY[0] = dYLeftCtr;
									dX[3] = dXRightCtr;
									dY[3] = dYRightCtr;
								}
								else
					//			{	double dXYAngleToTopEdge = dXYNormalAngle + (dXYNormalAngle > 0 ? -sdPi :  sdPi);		// (in range -pi to +pi)
								{	double dXYAngleToTopEdge = dXYNormalAngle + (dXYNormalAngle > sdPi ? -sdPi :  sdPi);		// (in range 0 to 2pi)
									double dOXYLen = (((fZHgt/cos( dZAngle ))/2.0) + fODist) * sin( dZAngle );
									dX[0] = dXLeftCtr  + (dOXYLen * cos( dXYAngleToTopEdge  ));
									dY[0] = dYLeftCtr  + (dOXYLen * sin( dXYAngleToTopEdge  ));
									dX[3] = dXRightCtr + (dOXYLen * cos( dXYAngleToTopEdge  ));
									dY[3] = dYRightCtr + (dOXYLen * sin( dXYAngleToTopEdge  ));
								}
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
									dZ[0] = fZTop + fODist;		// normal vector is parallel to ground, so Z straight up - no angle calcs needed
								else
									dZ[0] = fZTop + (fODist * cos( dZAngle ));	// normal vector is NOT parallel to ground and ODist is non-zero
								dZ[3] = dZ[0];
							// first and last vertices set, now deal w/ vertices that represent the end of the overhang
								if (WithinMargin( fOAngle, 90.0, 0.001 ))
								{	// 90 deg angle means we can use normal vector to extend overhang
									dX[1] = dX[0] + (fUnitVectorOi * fOverhangDepth);
									dY[1] = dY[0] + (fUnitVectorOj * fOverhangDepth);
									dZ[1] = dZ[0] + (fUnitVectorOk * fOverhangDepth);
									dX[2] = dX[3] + (fUnitVectorOi * fOverhangDepth);
									dY[2] = dY[3] + (fUnitVectorOj * fOverhangDepth);
									dZ[2] = dZ[3] + (fUnitVectorOk * fOverhangDepth);
								}
								else
								{	// NOT 90 deg angle, so angle calcs required to extend overhang
									dZAngle = sdPi * (fOAngle - 90.0) / 180.0;	// START w/ OAngle in radians
									if (!WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
										dZAngle += asin( fUnitVectorOk );
									double dOXYLen = fOverhangDepth * cos( dZAngle );
									dX[1] = dX[0] + (dOXYLen        * cos( dXYNormalAngle ));
									dY[1] = dY[0] + (dOXYLen        * sin( dXYNormalAngle ));
									dZ[1] = dZ[0] + (fOverhangDepth * sin( dZAngle        ));
									dX[2] = dX[3] + (dX[1] - dX[0]);
									dY[2] = dY[3] + (dY[1] - dY[0]);
									dZ[2] = dZ[3] + (dZ[1] - dZ[0]);
								}

							// CREATE NEW ExtShdgObj
								int iCr8ShdObj = CreateWindowShadeObject( pWinObj, iWin, pGParentSpcObj, " - Ovrhng", "overhang", sErrMsg, lDBID_Win_OverhangRef, &dX[0], &dY[0], &dZ[0],
																						lDBID_Win_OverhangTransOption, lDBID_Win_OverhangTrans, lDBID_Win_OverhangTransSchRef );
								iRetVal = (iCr8ShdObj < 0 ? iCr8ShdObj : iRetVal+1);
							}

						// LEFT FIN creation
							if (iRetVal >= 0 && BEMPX_GetObject( lDBID_Win_LeftFinRef, pShdObj, -1, iWin ) && pShdObj)
								BEMPX_DeleteObject( pShdObj );  // DELETE an existing left fin assigned to this Win
							if (iRetVal >= 0 && fLeftFinDepth > 0.0001)
							{	double fLFDist, fLFDistAbv, fLFDistBlw, fLFAngle;
							 	BEMPX_GetFloat( lDBID_Win_LeftFinDistance      , fLFDist    , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_LeftFinDistanceAbove , fLFDistAbv , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_LeftFinDistanceBelow , fLFDistBlw , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_LeftFinAngle         , fLFAngle   , -1, BEMP_Flt, iWin );

								dXLeftCtr  = dXCtr + (((fXYLen/2.0) + fLFDist) * cos( dXYAngleToLeftEdge  ));
								dYLeftCtr  = dYCtr + (((fXYLen/2.0) + fLFDist) * sin( dXYAngleToLeftEdge  ));
								dXYHyp = sqrt( (fUnitVectorOi*fUnitVectorOi) + (fUnitVectorOj*fUnitVectorOj) );
								dZAngle = LineAngle( 0, dXYHyp, 0, fUnitVectorOk, 0.001 );	// radians (in range 0 to 2pi)
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
								{	// normal vector is parallel to ground, so Z straight up => X,Y locations same @ overhang level than @ mid-window
									dX[0] = dX[3] = dXLeftCtr;
									dY[0] = dY[3] = dYLeftCtr;
									dZ[0] = fZTop - fLFDistBlw - fZHgt;
									dZ[3] = fZTop + fLFDistAbv;
								}
								else	// more complicated finding point 1 & 4 coordinates when window not vertical
								{	double dXYAngleToTopEdge = dXYNormalAngle;
									if (sin( dZAngle ) > 0)
										dXYAngleToTopEdge += (dXYNormalAngle >= sdPi ? -sdPi :  sdPi);		// (in range 0 to 2pi)
									double dOXYTopLen = ((fZHgt/2.0) * fabs( tan( dZAngle ))) + (fLFDistAbv * fabs( sin( dZAngle )));
									double dOXYBotLen = ((fZHgt/2.0) * fabs( tan( dZAngle ))) + (fLFDistBlw * fabs( sin( dZAngle )));
									dX[0] = dXLeftCtr - (dOXYBotLen * cos( dXYAngleToTopEdge  ));
									dY[0] = dYLeftCtr - (dOXYBotLen * sin( dXYAngleToTopEdge  ));
									dX[3] = dXLeftCtr + (dOXYTopLen * cos( dXYAngleToTopEdge  ));
									dY[3] = dYLeftCtr + (dOXYTopLen * sin( dXYAngleToTopEdge  ));
									dZ[0] = fZTop - fZHgt - (fLFDistBlw * fabs( cos( dZAngle )));
									dZ[3] = fZTop         + (fLFDistAbv * fabs( cos( dZAngle )));
								}

								double dXYFinAngle = dXYAngleToLeftEdge + (sdPi * (180.0 - fLFAngle) / 180.0);	// -pi to 2pi
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
								{	// normal vector is parallel to ground, so extension of fin exclusively in XY-plane
									dX[1] = dX[0] + (fLeftFinDepth * cos( dXYFinAngle  ));
									dY[1] = dY[0] + (fLeftFinDepth * sin( dXYFinAngle  ));
									dX[2] = dX[3] + (fLeftFinDepth * cos( dXYFinAngle  ));
									dY[2] = dY[3] + (fLeftFinDepth * sin( dXYFinAngle  ));
									dZ[1] = dZ[0];
									dZ[2] = dZ[3];
								}
								else	// more complicated finding point 2 & 3 coordinates when window not vertical
								{	double dXYFinLen = fLeftFinDepth * fabs( cos( dZAngle ));
									dX[1] = dX[0] + (dXYFinLen * cos( dXYFinAngle  ));
									dY[1] = dY[0] + (dXYFinLen * sin( dXYFinAngle  ));
									dX[2] = dX[3] + (dXYFinLen * cos( dXYFinAngle  ));
									dY[2] = dY[3] + (dXYFinLen * sin( dXYFinAngle  ));
									dZ[1] = dZ[0] + (fLeftFinDepth * sin( dZAngle ));
									dZ[2] = dZ[3] + (fLeftFinDepth * sin( dZAngle ));
								}

							// CREATE NEW ExtShdgObj
								int iCr8ShdObj = CreateWindowShadeObject( pWinObj, iWin, pGParentSpcObj, " - LtFin", "left fin", sErrMsg, lDBID_Win_LeftFinRef, &dX[0], &dY[0], &dZ[0],
																						lDBID_Win_LeftFinTransOption, lDBID_Win_LeftFinTrans, lDBID_Win_LeftFinTransSchRef );
								iRetVal = (iCr8ShdObj < 0 ? iCr8ShdObj : iRetVal+1);
							}

						// RIGHT FIN creation
							if (iRetVal >= 0 && BEMPX_GetObject( lDBID_Win_RightFinRef, pShdObj, -1, iWin ) && pShdObj)
								BEMPX_DeleteObject( pShdObj );  // DELETE an existing right fin assigned to this Win
							if (iRetVal >= 0 && fRightFinDepth > 0.0001)
							{	double fRFDist, fRFDistAbv, fRFDistBlw, fRFAngle;
							 	BEMPX_GetFloat( lDBID_Win_RightFinDistance      , fRFDist    , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_RightFinDistanceAbove , fRFDistAbv , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_RightFinDistanceBelow , fRFDistBlw , -1, BEMP_Flt, iWin );
							 	BEMPX_GetFloat( lDBID_Win_RightFinAngle         , fRFAngle   , -1, BEMP_Flt, iWin );

								dXRightCtr  = dXCtr + (((fXYLen/2.0) + fRFDist) * cos( dXYAngleToRightEdge  ));
								dYRightCtr  = dYCtr + (((fXYLen/2.0) + fRFDist) * sin( dXYAngleToRightEdge  ));
								dXYHyp = sqrt( (fUnitVectorOi*fUnitVectorOi) + (fUnitVectorOj*fUnitVectorOj) );
								dZAngle = LineAngle( 0, dXYHyp, 0, fUnitVectorOk, 0.001 );	// radians (in range 0 to 2pi)
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
								{	// normal vector is parallel to ground, so Z straight up => X,Y locations same @ overhang level than @ mid-window
									dX[0] = dX[3] = dXRightCtr;
									dY[0] = dY[3] = dYRightCtr;
									dZ[0] = fZTop + fRFDistAbv;
									dZ[3] = fZTop - fRFDistBlw - fZHgt;
								}
								else	// more complicated finding point 1 & 4 coordinates when window not vertical
								{	double dXYAngleToTopEdge = dXYNormalAngle;
									if (sin( dZAngle ) > 0)
										dXYAngleToTopEdge += (dXYNormalAngle >= sdPi ? -sdPi :  sdPi);		// (in range 0 to 2pi)
									double dOXYTopLen = ((fZHgt/2.0) * fabs( tan( dZAngle ))) + (fRFDistAbv * fabs( sin( dZAngle )));
									double dOXYBotLen = ((fZHgt/2.0) * fabs( tan( dZAngle ))) + (fRFDistBlw * fabs( sin( dZAngle )));
									dX[0] = dXRightCtr + (dOXYTopLen * cos( dXYAngleToTopEdge  ));
									dY[0] = dYRightCtr + (dOXYTopLen * sin( dXYAngleToTopEdge  ));
									dX[3] = dXRightCtr - (dOXYBotLen * cos( dXYAngleToTopEdge  ));
									dY[3] = dYRightCtr - (dOXYBotLen * sin( dXYAngleToTopEdge  ));
									dZ[0] = fZTop         + (fRFDistAbv * fabs( cos( dZAngle )));
									dZ[3] = fZTop - fZHgt - (fRFDistBlw * fabs( cos( dZAngle )));
								}

								double dXYFinAngle = dXYAngleToRightEdge - (sdPi * (180.0 - fRFAngle) / 180.0);	// -pi to 2pi
								if (WithinMargin( fUnitVectorOk, 0.0, 0.0001 ))
								{	// normal vector is parallel to ground, so extension of fin exclusively in XY-plane
									dX[1] = dX[0] + (fRightFinDepth * cos( dXYFinAngle  ));
									dY[1] = dY[0] + (fRightFinDepth * sin( dXYFinAngle  ));
									dX[2] = dX[3] + (fRightFinDepth * cos( dXYFinAngle  ));
									dY[2] = dY[3] + (fRightFinDepth * sin( dXYFinAngle  ));
									dZ[1] = dZ[0];
									dZ[2] = dZ[3];
								}
								else	// more complicated finding point 2 & 3 coordinates when window not vertical
								{	double dXYFinLen = fRightFinDepth * fabs( cos( dZAngle ));
									dX[1] = dX[0] + (dXYFinLen * cos( dXYFinAngle  ));
									dY[1] = dY[0] + (dXYFinLen * sin( dXYFinAngle  ));
									dX[2] = dX[3] + (dXYFinLen * cos( dXYFinAngle  ));
									dY[2] = dY[3] + (dXYFinLen * sin( dXYFinAngle  ));
									dZ[1] = dZ[0] + (fRightFinDepth * sin( dZAngle ));
									dZ[2] = dZ[3] + (fRightFinDepth * sin( dZAngle ));
								}

							// CREATE NEW ExtShdgObj
								int iCr8ShdObj = CreateWindowShadeObject( pWinObj, iWin, pGParentSpcObj, " - RtFin", "right fin", sErrMsg, lDBID_Win_RightFinRef, &dX[0], &dY[0], &dZ[0],
																						lDBID_Win_RightFinTransOption, lDBID_Win_RightFinTrans, lDBID_Win_RightFinTransSchRef );
								iRetVal = (iCr8ShdObj < 0 ? iCr8ShdObj : iRetVal+1);
							}
						}	// Win PolyLp data retrieved from BEMBase valid
					}	// valid Win PolyLp
			}	}
	}	}

	if (!sErrMsg.isEmpty())
		BEMPX_WriteLogFile( sErrMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
	else if (bVerbose)
		BEMPX_WriteLogFile( QString::asprintf( "   %d window shade (and child PolyLp) object(s) created for %d windows by CMX_GenerateWindowShades_CECNonRes()", iRetVal, iNumWinsProcessed ) );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////


#define  MAX_NRStorageVal  3		// SAC 1/24/14
typedef struct nrfilepruneinfo_
{
   std::string sFileExt;
	bool   bFNameInclRunID;
	bool   bReportFailure;
	int    iaDelForOptVal[MAX_NRStorageVal];
} NRFilePruneInfo;


void DefaultModel_CECNonRes( int& iPrevRuleErrs, QString& sUIVersionString, int& iRetVal, bool bVerbose, void* pCompRuleDebugInfo,
										int iDontAbortOnErrorsThruStep, int iNumFileOpenDefaultingRounds )	// SAC 4/11/18
{
	BEMPX_SetAbortRuleEvaluationFlag( false );		// SAC 8/6/13 - set flag indicating that rule processing should be aborted

	iPrevRuleErrs = BEMPX_GetRulesetErrorCount();			assert( iPrevRuleErrs < 1 );
							if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
								BEMPX_WriteLogFile( "  PerfAnal_CECNRes - Defaulting model", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	// SAC 3/6/14 - added code to set UIVersionString to BEMBase
	if (!sUIVersionString.isEmpty())
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), BEMP_QStr, (void*) &sUIVersionString );

// TRIM TO SINGLE EVALUATION once ordered rule evaluation implemented
	if (iNumFileOpenDefaultingRounds > 0)
	   CMX_EvaluateRuleset( "rl_DEFAULT", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo ); // SAC 4/16/13 - triple eval DEFAULT rules to overcome rule order issues -- TEMPORARILY - TO DO
	if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs && iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
	{
//										 9 : Errors encountered evaluating input model defaulting rules
			iRetVal = (iRetVal > 0 ? iRetVal : 9);		// don't abort (?)
	}
	else
	{	for (int iDR=2; iDR <= iNumFileOpenDefaultingRounds; iDR++)
	   	CMX_EvaluateRuleset( "rl_DEFAULT", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );

		if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs && iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
		{
//										10 : Errors encountered evaluating input model defaulting rules (multiple times)
			iRetVal = (iRetVal > 0 ? iRetVal : 10);		// don't abort (?)
		}
	}
	BEMPX_RefreshLogFile();	// SAC 5/19/14
}

/////////////////////////////////////////////////////////////////////////////
// AnalysisAction stuff - SAC 2/20/20

void MidAnalysis_ApplyAnalysisActionToDatabase( long iAnalPhase, long iBeforeAfter, QString& sErrMsg, bool& bAbort, int& iRetVal, int iErrID, bool bVerbose,
																char* pszErrorMsg, int iErrorMsgLen, int iDontAbortOnErrorsThruStep, int iStepCheck ) 
{
			QString qsApplyAnalActError;
			int iApplyAnalActRetVal = BEMPX_ApplyAnalysisActionToDatabase( iAnalPhase, iBeforeAfter, qsApplyAnalActError, bVerbose );		// SAC 1/30/20
			if (iApplyAnalActRetVal > 0)
				qsApplyAnalActError = QString( "      %1 AnalysisAction(s) successfully applied to building model: %2 / %3" ).arg(
													QString::number(iApplyAnalActRetVal), AnalysisAction_PhaseString(iAnalPhase), AnalysisAction_BeforeAfter(iBeforeAfter) );
			else if (!qsApplyAnalActError.isEmpty())
			{	sErrMsg = qsApplyAnalActError;
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iErrID, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iStepCheck );
			}
			if (!qsApplyAnalActError.isEmpty())
				BEMPX_WriteLogFile( qsApplyAnalActError, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
}

/////////////////////////////////////////////////////////////////////////////


#ifdef CM_QTGUI
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QTextEdit>
void showDetailsInQMessageBox(QMessageBox& messageBox, int iTextWd, int iTextHt)
{
   foreach (QAbstractButton *button, messageBox.buttons())
   {
      if (messageBox.buttonRole(button) == QMessageBox::ActionRole)
      {
         button->click();
         break;
      }
   }
   QList<QTextEdit*> textBoxes = messageBox.findChildren<QTextEdit*>();
   if(textBoxes.size())
      textBoxes[0]->setFixedSize(iTextWd, iTextHt);
}
#endif


#define  Com_NumCSEMeters    4    // 3->4 to accommodate new MtrElec2 to track RegLtg & ProcMtrs for ResOtherZn - SAC 04/13/22 (Com tic #3366)
static const char* pszMeters[Com_NumCSEMeters+1]			= { "MtrElec",     "MtrNatGas",  "MtrOther",  "MtrElec2",    NULL };
static const char* pszMeters_ComMap[Com_NumCSEMeters+1]	= { "Electricity", "NaturalGas", "OtherFuel", "Electricity", NULL };		// SAC 5/31/16 - added to enable retrieval of CSE results to -Com analysis
double         sdaMeterMults_ComMap[Com_NumCSEMeters+1]	= {    0.293,         0.01,         0.01,        0.293,      0.0  };		// SAC 6/1/16 - added to convert units of CSE results to -Com analysis (1/3.412 for elec)  // SAC 6/29/16 - inc NG & Oth fuel mults by 10 fixing MBtu->therms

#define  Com_NumCSEMeters_CUAC  24     // SAC 09/08/22 (CUAC)
static const char* pszCUACMeters[Com_NumCSEMeters_CUAC+1]			= { "MtrElec",     "MtrNatGas",  "MtrOther",   "MtrElec_0bedrm", "MtrNatGas_0bedrm", "MtrOther_0bedrm",  "MtrElec_1bedrm", "MtrNatGas_1bedrm", "MtrOther_1bedrm",  "MtrElec_2bedrm", "MtrNatGas_2bedrm", "MtrOther_2bedrm",  "MtrElec_3bedrm", "MtrNatGas_3bedrm", "MtrOther_3bedrm",  "MtrElec_4bedrm", "MtrNatGas_4bedrm", "MtrOther_4bedrm",  "MtrElec_5bedrm", "MtrNatGas_5bedrm", "MtrOther_5bedrm",  "MtrElec_6bedrm", "MtrNatGas_6bedrm", "MtrOther_6bedrm",    NULL };
static const char* pszCUACMeters_ComMap[Com_NumCSEMeters_CUAC+1]	= { "Electricity", "NaturalGas", "OtherFuel",  "Elec_0bedrm",    "Gas_0bedrm",       "Gas_0bedrm",       "Elec_1bedrm",    "Gas_1bedrm",       "Gas_1bedrm",       "Elec_2bedrm",    "Gas_2bedrm",       "Gas_2bedrm",       "Elec_3bedrm",    "Gas_3bedrm",       "Gas_3bedrm",       "Elec_4bedrm",    "Gas_4bedrm",       "Gas_4bedrm",       "Elec_5bedrm",    "Gas_5bedrm",       "Gas_5bedrm",       "Elec_6bedrm",    "Gas_6bedrm",       "Gas_6bedrm",         NULL };	
double         sdaCUACMeterMults_ComMap[Com_NumCSEMeters_CUAC+1]	= {    0.293,         0.01,         0.01,         0.293,            0.01,               0.01,               0.293,            0.01,               0.01,               0.293,            0.01,               0.01,               0.293,            0.01,               0.01,               0.293,            0.01,               0.01,               0.293,            0.01,               0.01,               0.293,            0.01,               0.01,              0.0  };	

#define  Com_NumCSEMeters_Custom1  7   // SAC 11/03/23
static const char* pszCust1Meters[Com_NumCSEMeters_Custom1+1]			= { "MtrElec_ResDwell", "MtrNGas_ResDwell",    "MtrOthr_ResDwell",   "MtrElec",     "MtrElec2",    "MtrNatGas",  "MtrOther",   NULL };
static const char* pszCust1Meters_ComMap[Com_NumCSEMeters_Custom1+1]	= { "Elec_ResDwell",    "NaturalGas_ResDwell", "OtherFuel_ResDwell", "Electricity", "Electricity", "NaturalGas", "OtherFuel",  NULL };	
double         sdaCust1MeterMults_ComMap[Com_NumCSEMeters_Custom1+1]	= {    0.293,              1.0,                   1.0,                  0.293,         0.293,         1.0,          1.0,       0.0  };	
static const char* pszCust1Meters_Unique[]	= { "Elec_ResDwell", "NaturalGas_ResDwell", "OtherFuel_ResDwell", "Electricity", "NaturalGas", "OtherFuel", NULL };	

//static const char* pszCSEDHWEnduseList[] = { /*"Tot", "Clg", "Htg", "HPBU",*/ "Dhw",                "DhwBU",              "DhwMFL",             /*"FanC", "FanH", "FanV", "Fan", "Aux", "Proc", "Lit", "Rcp", "Ext", "Refr", "Dish", "Dry", "Wash", "Cook", "User1",*/ "User2",            /* "PV",            "BT",*/    NULL };	// added to facilitate retrieval of Res DHW separate from other enduses - SAC 10/8/20 (tic #3218)
static const char* pszCSEEnduseList19[]    = { /*"Tot", "Clg", "Htg", "HPBU",*/ "Dhw",                "DhwBU",              "DhwMFL",             /*"FanC", "FanH", "FanV", "Fan", "Aux", "Proc", "Lit", "Rcp", "Ext", "Refr", "Dish", "Dry", "Wash", "Cook", "User1",*/ "User2",               "PV",            "BT",      NULL };	// "DHWPmp", ??   // SAC 7/15/18 - added PV & Batt  	// SAC 7/27/18 - added "DhwMFL" (DHWLOOP pumping energy - CSE19 v0.850.0, SVN r1098)
static const char* pszCSEEUList_ComMap19[] = { /* NULL,  NULL,  NULL,   NULL,*/ "Domestic Hot Water", "Domestic Hot Water", "Domestic Hot Water", /* NULL ,  NULL ,  NULL ,  NULL,  NULL,  NULL ,  NULL,  NULL,  NULL,  NULL ,  NULL ,  NULL,  NULL ,  NULL ,   NULL ,*/ "Domestic Hot Water",  "Photovoltaics", "Battery", NULL }; 				// SAC 1/8/19 - summed in CSE enduse 'User2' to each elec DHW results retrieval (to capture HPWH XBU energy)
// created separate 22+ CSE results mapping (below) to cover ALL enduses - SAC 10/28/21 (MFam)
static const char* pszCSEEnduseList[]      = { /*"Tot",*/ "Clg",              "Htg",              "HPBU",             "Dhw",                   "DhwBU",                 "DhwMFL",                "FanC",           "FanH",           "FanV",           "Fan",            "Aux",              "Proc",       "Lit",          "Rcp",           "Ext",        "Refr",         "Dish",       "Dry",        "Wash",       "Cook",       /*"User1",*/ "User2",                 "PV",            "BT",      NULL };	// "DHWPmp", ??   // SAC 7/15/18 - added PV & Batt  	// SAC 7/27/18 - added "DhwMFL" (DHWLOOP pumping energy - CSE19 v0.850.0, SVN r1098)
static const char* pszCSEEUList_ComMap[]   = { /* NULL,*/ "ResSpace Cooling", "ResSpace Heating", "ResSpace Heating", "ResDomestic Hot Water", "ResDomestic Hot Water", "ResDomestic Hot Water", "ResIndoor Fans", "ResIndoor Fans", "ResIndoor Fans", "ResIndoor Fans", "ResPumps & Misc.", "ResProcess", "ResOther Ltg", "ResReceptacle", "ResProcess", "ResProcess",   "ResProcess", "ResProcess", "ResProcess", "ResProcess", /*  NULL ,*/ "ResDomestic Hot Water", "Photovoltaics", "Battery", NULL }; 		// SAC 1/8/19 - summed in CSE enduse 'User2' to each elec DHW results retrieval (to capture HPWH XBU energy)
static const char* pszCSEEUList_CUACMap[]  = { /* NULL,*/ "Cooling",          "Heating",          "Heating",          "DHW",                   "DHW",                   "DHW",                   "Cooling",        "Heating",        "Ventilation",    "Ventilation",    "HVAC Other",       "Plug Loads", "Lighting",     "Plug Loads",    "Plug Loads", "Refrigerator", "Dishwasher", "Dryer",      "Washer",     "Cooking",    /*  NULL ,*/ "DHW",                   "Photovoltaics", "Battery", NULL };       // CSE enduse mapping for CUAC - SAC 09/07/22
static const char* pszCSEEnduseList_PVBatt[]  = { /*"Tot", "Clg",              "Htg",              "HPBU",             "Dhw",                   "DhwBU",                 "DhwMFL",                "FanC",           "FanH",           "FanV",           "Fan",            "Aux",              "Proc",       "Lit",          "Rcp",           "Ext",        "Refr",         "Dish",       "Dry",        "Wash",       "Cook",       "User1",  "User2", */     "PV",            "BT",      NULL };   // SAC 09/08/22 (CUAC)
static const char* pszCSEEUList_PVBatt[]      = { /* NULL, "Cooling",          "Heating",          "Heating",          "DHW",                   "DHW",                   "DHW",                   "Cooling",        "Heating",        "Ventilation",    "Ventilation",    "HVAC Other",       "Plug Loads", "Lighting",     "Plug Loads",    "Plug Loads", "Refrigerator", "Dishwasher", "Dryer",      "Washer",     "Cooking",      NULL ,  "DHW",   */     "Photovoltaics", "Battery", NULL }; 
static const char* pszCSEEnduseListALL[]      = { "Tot",   "Clg",              "Htg",              "HPBU",             "Dhw",                   "DhwBU",                 "DhwMFL",                "FanC",           "FanH",           "FanV",           "Fan",            "Aux",              "Proc",       "Lit",          "Rcp",           "Ext",        "Refr",         "Dish",       "Dry",        "Wash",       "Cook",       "User1",  "User2",        "PV",            "BT",      NULL };	// CustomMeterOption - SAC 11/03/23
static const char  szCSEEnduses_CSV[]         =   "Tot,Clg,Htg,HPBU,Dhw,DhwBU,DhwMFL,FanC,FanH,FanV,Fan,Aux,Proc,Lit,Rcp,Ext,Refr,Dish,Dry,Wash,Cook,User1,User2,BT,PV,";

static int ProcessModelReports( const char* pszModelPathFile, long lDBID_ReportType, long lDBID_ReportFileAppend, int iObjIdx, bool /*bProcessCurrentSelection*/,
									QVector<QString>& saModelReportOptions, bool bVerbose, bool bSilent );

static const char* GetResultsCSVHeader_NonRes( int i1HdrIdx, int iCodeType );

const char pcCharsNotAllowedInObjNames_CECNonRes[] = { '"', ',', '\'', '!', ';', NULL };	// SAC 8/20/14

static QString sDbgFileName;





void CSERunLoop( int iSimRunIdx, OS_SimInfo** posSimInfo, QString** pqsCSESimStatusMsg, bool bStoreHourlyResults, QString sProcessingPath, QString sModelPathOnly, QString sModelFileOnly, bool bSecureT24NRptGenActivated,
                  bool bPerformFullCSESim, bool bBypassRecircDHW, long lNumPVArraysChk, bool bEnablePVBattSim, const char* pszUIVersionString,
                  QString sCSEexe, QString sCSEEXEPath, QString qsCSEName, QString sAnnualWeatherFile,
                  int iCodeType, int iRulesetCodeYear, long lAnalysisType, int iDontAbortOnErrorsThruStep, int iAnalStep, bool bProposedOnly, bool bStoreBEMDetails,
                  bool bSilent, bool bVerbose, bool bResearchMode, void* pCompRuleDebugInfo, QString& sCSEIncludeFileDBID, QString& sCSEVersion, char* pszErrorMsg, int iErrorMsgLen,
                  bool& bAbort, int& iRetVal, QString& sErrMsg, QString& sStdDsgnCSEResultsPathFile, long iCUACReportID, long iCustomMeterOption )     // added iCUACReportID argument - SAC 09/08/22 (CUAC)  // iCustomMeterOption - SAC 11/03/23
{
	int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );
   QString sLogMsg;
   long lExcludePVBattFromSim, lDBID_Proj_ExcludePVBattFromSim = BEMPX_GetDatabaseID( "CSE_ExcludePVBattFromSim", iCID_Proj );
   long lSimPVBattOnly = 0   , lDBID_Proj_SimPVBattOnly        = BEMPX_GetDatabaseID( "CSE_SimPVBattOnly",        iCID_Proj );
   bool bReportSimProgress = (iRulesetCodeYear >= 2022);    // SAC 01/24/22 (MFam)   // renamed & added 2019 vs. 22 logic - SAC 02/07/22 (tic #3345)
   long lDBID_ResProj_HVACSizingNeeded  = BEMPX_GetDatabaseID( "ResProj:HVACSizingNeeded" );
   long lDBID_Proj_HaveStandaloneBatt   = BEMPX_GetDatabaseID( "Proj:HaveStandaloneBatt" );     // SAC 05/26/22


              				std::vector<int> iaCSESimRunIdx;
                        int iSR=0;
								for (iSR=0; iSR <= iSimRunIdx; iSR++)	// loop over runs just simulated in E+ above
								{
                           // add logic to add CSE SIZING runs to run list if flagged - SAC 05/08/22
									if (bPerformFullCSESim && posSimInfo[iSR]->bSimulateModel && !bStoreHourlyResults)
                           {  long lCSEHVACSizingReqd = 0;
                              if (BEMPX_GetInteger( lDBID_ResProj_HVACSizingNeeded, lCSEHVACSizingReqd, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx ) &&
                                  lCSEHVACSizingReqd > 0)
                              {  iaCSESimRunIdx.push_back(iSR);
                                 bReportSimProgress = false;      // prevent sim progress reporting for sizing runs ???
				   						if (TRUE)  // bVerbose)
					   						BEMPX_WriteLogFile( QString::asprintf( "      Performing CSE HVAC Sizing %s simulation", posSimInfo[iSR]->pszLongRunID ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              }
                           }
								   // SAC 7/23/18 - CSE simulation moved down HERE so that CSE inputs can include E+ elec use hourly data that feeds into the Battery simulation
								   // SAC 5/27/16 - moved Recirc/Res DHW simulation outside code which gets bypassed due to bCallOpenStudio
									else if (posSimInfo[iSR]->bSimulateModel && bStoreHourlyResults)
									{  if (bPerformFullCSESim && lDBID_Proj_ExcludePVBattFromSim > 0 && lDBID_Proj_SimPVBattOnly > 0 &&
                                  BEMPX_GetInteger( lDBID_Proj_ExcludePVBattFromSim, lExcludePVBattFromSim, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx ) && lExcludePVBattFromSim > 0 &&
                                  BEMPX_GetInteger( lDBID_Proj_SimPVBattOnly       , lSimPVBattOnly       , 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx ) && lSimPVBattOnly > 0 )
                              {  // don't add this run idx to CSE simulation array - already simulated in a prior round (as denoted by both above flags being > 0)
                              }
                              else
                              {  int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
   										int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray"   ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
                                 long lHaveStandaloneBatt=0;
                                 if (lDBID_Proj_HaveStandaloneBatt > 0)    // SAC 05/26/22
                                    BEMPX_GetInteger( lDBID_Proj_HaveStandaloneBatt, lHaveStandaloneBatt, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
	   									if ( bPerformFullCSESim || (!bBypassRecircDHW && iNumRecircDHWSysObjs > 0) ||
                                      ((iNumPVArrayObjs > 0 || lHaveStandaloneBatt > 0) && bEnablePVBattSim) )		// SAC 4/3/19   // SAC 05/26/22
                                 {  iaCSESimRunIdx.push_back(iSR);
                                    if (lSimPVBattOnly > 0)
                                       bReportSimProgress = false;
                                 }
			   							else if (iNumRecircDHWSysObjs > 0 || iNumPVArrayObjs > 0)
				   						{	if (bVerbose)
					   							BEMPX_WriteLogFile( QString::asprintf( "      Skipping CSE ResDHW/PV/Battery %s simulation", posSimInfo[iSR]->pszLongRunID ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                    //			CSE_MsgCallback( 0 /*level*/, "Skipping CSE ResDHW/PV/Battery simulation" );
										}  }
                        }  }

                        if (iaCSESimRunIdx.size() > 0)
                        {
									if (!FileExists( sCSEexe.toLocal8Bit().constData() ))
									{	sErrMsg = QString::asprintf( "%s (residential DHW/PV/Battery simulation engine) executable not found: '%s'", qsCSEName.toLocal8Bit().constData(), sCSEexe.toLocal8Bit().constData() );		assert( FALSE );
                                    //				54 : CSE (residential DHW & PV/Battery simulation engine) executable(s) not found
													// SAC 12/18/17 - replaced iDontAbortOnErrorsThruStep w/ '0' to prevent program crash when CSE exe not found
										ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 54 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, iAnalStep /*iStepCheck*/ );
									}
									assert( FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ) );
                        }

                        if (iaCSESimRunIdx.size() > 0 && sErrMsg.isEmpty())
                        {
									bool bFullComplianceAnalysis = (!bResearchMode && !bProposedOnly);
									lAnalysisType = (bResearchMode ? 0 : (bProposedOnly ? 12 : 13));  // based on CBECC-Res options: 0-Research / 12-Proposed Only / 13-Proposed and Standard

									CSERunMgr cseRunMgr(	sCSEexe, sAnnualWeatherFile, sModelPathOnly, sModelFileOnly, sProcessingPath, bFullComplianceAnalysis,
												            false /*bInitHourlyResults*/, 0 /*lAllOrientations*/, lAnalysisType, iRulesetCodeYear, 0 /*lDesignRatingRunID*/, bVerbose,
												            bStoreBEMDetails, true /*bPerformSimulations*/, false /*bBypassCSE*/, bSilent, pCompRuleDebugInfo, pszUIVersionString,
												            0 /*iSimReportDetailsOption*/, 0 /*iSimErrorDetailsOption*/, 0 /*lStdMixedFuelRunReqd*/, 0 /*lPrelimPropRunReqd*/,		// SAC 11/7/16 - added sim report/error option arguments, disabled until/unless wanted for Com analysis
                                                0 /*lPropFlexRunReqd*/, (int) iaCSESimRunIdx.size() /*iNumRuns*/ );     // add spcification of iNumRuns - SAC 06/08/24
									   //			dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

									int iRunType[     10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
									int iRunSimRunIdx[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
									//int iCSESimRetVal = 0;    - removed to fix problem where CSE errors not propogating into overall analysis errors - SAC 05/18/22
                           int iCSR, iNumCSERuns = 0, iNumSubstCSEResultsFiles = 0;
                           for (iCSR=0; (iCSR < (int) iaCSESimRunIdx.size() && iRetVal /*iCSESimRetVal*/ == 0); iCSR++)
                           {
                              iSR = iaCSESimRunIdx[iCSR];
                              int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
										int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray"   ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );

								         // CSE (DHW &/or PVArray/Battery) SIMULATION
												// perform DHW simulation using CSE and add those results into the hourly results already stored in BEMProc (should be after reading E+ results but before applying TDV multipliers)
					                  // --- CSE DHW (&/or PVArray/Battery) simulation based on CECRes analysis ---
												QString sCSE_DHWUseMthd, sCSE_DHWUseIncFile;
												BEMPX_GetString( BEMPX_GetDatabaseID( "CSE_DHWUseMthd"   , iCID_Proj ), sCSE_DHWUseMthd   , FALSE, 0, -1, -1, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx );
												BEMPX_GetString( BEMPX_GetDatabaseID( "CSE_DHWUseIncFile", iCID_Proj ), sCSE_DHWUseIncFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx );	// SAC 2/20/19
												if (sCSE_DHWUseIncFile.isEmpty())
													sCSE_DHWUseIncFile = "DHWDU2.txt";     // DHWDU.txt -> DHWDU2.txt - SAC 03/16/21
												if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.isEmpty())
												{	sErrMsg = QString::asprintf( "%s (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid", qsCSEName.toLocal8Bit().constData() );
                                       //				56 : CSE (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid
													ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 56 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
												}
												else if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.compare("New (via wsDayUse)", Qt::CaseInsensitive)==0)
												{	// setup and copy CSE include file defining DHW use profiles - SAC 3/17/16
													//QString sDHWUseIncFile = "DHWDU.txt";	// SAC 1/24/19 - updated from DHWDUMF.txt to DHWDU.txt
													QString sDHWUseTo, sDHWUseFrom = sCSEEXEPath + sCSE_DHWUseIncFile;
													if (!FileExists( sDHWUseFrom.toLocal8Bit().constData() ))
													{	sErrMsg = QString::asprintf( "%s (residential DHW simulation engine) use profile file not found:  %s", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData() );
                                          //			55 : CSE (residential DHW simulation engine) use profile file not found
														ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 55 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
													}
													else
													{	sDHWUseTo = sProcessingPath + sCSE_DHWUseIncFile;
														if (!CopyFile( sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData(), FALSE ))
														{	sErrMsg = QString::asprintf( "Unable to copy %s DHW Use/Load Profile include file from '%s' into processing directory '%s'", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData() );
                                          //			57 : Unable to copy DHW Use/Load Profile CSE include file into processing directory
															ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 57 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
														}
														assert( FileExists( sDHWUseTo.toLocal8Bit().constData() ) );
														// RE-check DHW incl file hash ??
												}	}

												if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())
												{
												   // Check for specification of Report Include file - and if found, prevent secure report
													//long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "CSE_RptIncFile", iCID_Proj );
                              			long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "ResProj:ReportIncludeFile" );     // switch to newer version - SAC 05/13/22
													QString sChkRptIncFile;
													if (lProjReportIncludeFileDBID > 0 &&
														 BEMPX_GetString( lProjReportIncludeFileDBID, sChkRptIncFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx ) && !sChkRptIncFile.isEmpty())
														sCSEIncludeFileDBID = "ResProj:ReportIncludeFile";  // "Proj:CSE_RptIncFile";
												   // DISABLE report include file use if all settings are conisistent w/ full secure report generation (to prevent invalid analysis)
													bool bAllowReportIncludeFile = true;
													//if (!sCSEIncludeFileDBID.isEmpty() && iCodeType == CT_T24N && bSendRptSignature && (bComplianceReportPDF || bComplianceReportXML || bComplianceReportStd) &&
													//		!sXMLResultsFileName.isEmpty() && iAnalysisThruStep >= 8 && sIDFToSimulate.isEmpty() && iDLLCodeYear == iRulesetCodeYear && !bBypassInputChecks &&
													//		!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] && !bBypassUMLHChecks && !bBypassCheckSimRules && 
													//		plOverrideAutosize[0] == -1 && plOverrideAutosize[1] == -1 && plOverrideAutosize[2] == -1 && plOverrideAutosize[3] == -1 && !bBypassCheckCodeRules && 
													//		lQuickAnalysis <= 0 && !bIgnoreFileReadErrors && !bBypassValidFileChecks && sDevOptsNotDefaulted.isEmpty() && sExcptDsgnModelFile.isEmpty() &&
													//		lNumSpaceWithDefaultedDwellingUnitArea < 1 && !bBypassPreAnalysisCheckRules)
													if (!sCSEIncludeFileDBID.isEmpty() && bSecureT24NRptGenActivated)
													{	bAllowReportIncludeFile = false;
														sCSEIncludeFileDBID.clear();
																			BEMPX_WriteLogFile( QString::asprintf( "%s report include file use disabled to ensure secure report generation.  Use one of the Bypass* or other research option(s) to ensure report include file use.", qsCSEName.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
                                             // debugging
                                             //BEMPX_WriteLogFile( QString( "   Perform NRes Analysis:  iRunIdx %1, pszRunAbbrev %2" ).arg( QString::number( posSimInfo[iSR]->iRunIdx ), posSimInfo[iSR]->pszRunID ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													iRunType[iNumCSERuns] = (lAnalysisType < 1 ? CRM_User :
																		         (((iCodeType == CT_T24N && posSimInfo[iSR]->iRunIdx == 3) || (iCodeType != CT_T24N && posSimInfo[iSR]->iRunIdx >  5)) ? CRM_StdDesign :
                                                               (( iCodeType == CT_T24N && posSimInfo[iSR]->iRunIdx == 1) ? CRM_StdMixedFuel : CRM_Prop)));     // zb => CRM_StdMixedFuel - SAC 05/13/22
              									iRunSimRunIdx[iNumCSERuns] = iSR;

                                       // mechanism to bypass simulation by supplying CSE results file(s) specified in Proj data - SAC 01/21/25
                                       long lDBID_SubstituteCSEResultsPathFile = BEMPX_GetDatabaseID( "Proj:SubstituteCSEResultsPathFile" );
                                       QString sSubstituteCSEResultsPathFile;
                                       bool bHaveSubstCSEResultsPathFile = ( lDBID_SubstituteCSEResultsPathFile > 0 &&
                                                                             BEMPX_GetString( lDBID_SubstituteCSEResultsPathFile+posSimInfo[iSR]->iRunIdx, sSubstituteCSEResultsPathFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx ) && !sSubstituteCSEResultsPathFile.isEmpty() );

									            //	siNumProgressRuns = 1;
									            //	int iRunIdx = 0;
									            //	for (; (iRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)
									            //	{
									            //		if (iRunIdx > 0 || !bFirstModelCopyCreated)
									            //			BEMPX_AddModel( std::min( iRunIdx, 1 ) /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
                                             // debugging PV-solar
                                             //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), about to call cseRunMgr.SetupRun_NonRes() for run %1" ).arg( posSimInfo[iSR]->pszRunID ), NULL, FALSE, TRUE, FALSE );
                                             //BEMPX_WriteLogFile( QString( "   debugging, pre-cseRunMgr.SetupRun_NonRes() - lAnalysisType = %1 / RunType = %2" ).arg( QString::number( lAnalysisType ), QString::number( iRunType[0] ) ), NULL, FALSE, TRUE, FALSE );
														iRetVal /*iCSESimRetVal*/ = cseRunMgr.SetupRun_NonRes( iNumCSERuns/*iRunIdx*/, iRunType[iNumCSERuns/*iRunIdx*/], sErrMsg, bAllowReportIncludeFile, 
																													posSimInfo[iSR]->pszLongRunID, posSimInfo[iSR]->pszRunID, &sCSEVersion,
																													posSimInfo[iSR]->iBEMProcIdx, (lNumPVArraysChk > 0 && !bEnablePVBattSim), bPerformFullCSESim, iCUACReportID,    // SAC 4/3/19 - added new arg to cause removal of PVArray & Battery objects   // SAC 10/26/21 (MFam)  // SAC 12/13/24 (CUAC)
                                                                                       (bHaveSubstCSEResultsPathFile ? sSubstituteCSEResultsPathFile.toLocal8Bit().constData() : NULL) );   // SAC 01/21/25
                                          iNumCSERuns++;
                                          if (bHaveSubstCSEResultsPathFile)
                                             iNumSubstCSEResultsFiles++;
                                             // debugging PV-solar
                                             //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), back from cseRunMgr.SetupRun_NonRes() - returned %1: %2" ).arg( QString::number( iRetVal /*iCSESimRetVal*/ ), sErrMsg ), NULL, FALSE, TRUE, FALSE );
									            //					dTimeToPrepModel[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
									            //	}
                                    }
                           } // end of:  for (int iCSR=0; (iCSER <...

                           if ((iNumCSERuns - iNumSubstCSEResultsFiles) > 0 && iRetVal /*iCSESimRetVal*/ == 0)    // execute CSE simulations in parallel - SAC 11/18/21
                           {
				                                 //	if (iRetVal == 0)
				                                 //	{
				                                 //				QMessageBox msgBox;
				                                 //				msgBox.setWindowTitle( "CSE" );
				                                 //				msgBox.setIcon( QMessageBox::Warning ); 
				                                 //				msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
				                                 //				msgBox.setText( "About to launch CSE simulation(s)" );
				                                 //		//		msgBox.setDetailedText( qsRptIssuesDlgDetails );
				                                 //				msgBox.setStandardButtons( QMessageBox::Ok );
				                                 //				msgBox.addButton( QMessageBox::Abort );
				                                 //				msgBox.setDefaultButton( QMessageBox::Ok );
				                                 //				msgBox.exec();
				                                 //	}

               							// re-init data used to track simulation progress
								               ClearCSEProgressMap();	// SAC 11/18/21
                                       SetCSEMessageProcessingType( 1 );   // 0=>CEC Res / 1=>CEC NRes - SAC 11/19/21

                                       if (!bReportSimProgress)    // SAC 01/24/22 (MFam)
                                       {  bool bSaveFreezeProg = sbFreezeProgress;
                                          sbFreezeProgress = true;	// prevent progress reporting during (very quick) CSE PV/Batt only simulations
														cseRunMgr.DoRuns();
                                          sbFreezeProgress = bSaveFreezeProg;
                                       }
                                       else
														cseRunMgr.DoRuns();

									            //				dTimeCSESim += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
                           }

                           // process CSE results - SAC 11/18/21
                           int iCSESimErrCode = 0;  // SAC 05/18/22
                           for (iCSR=0; (iCSR < iNumCSERuns && iRetVal /*iCSESimRetVal*/ == 0); iCSR++)
                           {
                              iSR = iRunSimRunIdx[iCSR];
											BOOL bCSESimOK = TRUE;		QString sCSEErrMsg;

									            //	for (iRunIdx = 0; (iRetVal == 0 && iRetVal /*iCSESimRetVal*/ == 0 && iRunIdx < iNumRuns); iRunIdx++)
									            //	{
									            //		// SAC 6/19/14 - Set active model index to the appropriate value for this iRunIdx
									            //		BEMPX_SetActiveModel( iRunIdx+1 );
								
														const CSERun& cseRun = cseRunMgr.GetRun(iCSR/*iRunIdx*/);
														const QString& sRunID = cseRun.GetRunID();
									            //	const QString& sRunIDProcFile = cseRun.GetRunIDProcFile();
														const QString& sRunAbbrev = cseRun.GetRunAbbrev();
														long lRunNumber = (lAnalysisType < 1 ? 1 : cseRun.GetRunNumber());
                                          BOOL bUsingSubstResults = cseRun.GetUsingSubstituteResults();     // SAC 01/21/25
													//	BOOL bLastRun = cseRun.GetLastRun();
									            //	BOOL bIsStdDesign = cseRun.GetIsStdDesign();
									            //	BOOL bIsDesignRtg = cseRun.GetIsDesignRtg();
								
														if (iRetVal == 0)  // && iCSESimRetVal == 0)
														{
															int iCSERetVal = (bUsingSubstResults ? 0 : cseRun.GetExitCode());
															if (bVerbose || ebLogAnalysisMsgs)    // SAC 1/31/13    // SAC 10/22/21
																BEMPX_WriteLogFile( QString::asprintf( "      %s simulation returned %d (%s, Run# %ld)", qsCSEName.toLocal8Bit().constData(), iCSERetVal, sRunAbbrev.toLocal8Bit().constData(), lRunNumber ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															BEMPX_RefreshLogFile();	// SAC 5/19/14

															if (iCSERetVal != 0)
															{	sErrMsg = QString::asprintf( "ERROR:  %s simulation returned %d (%s, Run# %ld)", qsCSEName.toLocal8Bit().constData(), iCSERetVal, sRunAbbrev.toLocal8Bit().constData(), lRunNumber );
																iRetVal /*iCSESimRetVal*/ = BEMAnal_CECRes_CSESimError;
                                                iCSESimErrCode = iCSERetVal;
																BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															}
									                  //	if (iRetVal == 0 /*&& iCSESimRetVal == 0*/ && BEMPX_AbortRuleEvaluation())
									                  //		iRetVal /*iCSESimRetVal*/ = BEMAnal_CECRes_RuleProcAbort;

                                             long lCSEHVACSizingReqd = 0;     // prevent hourly results retrieval for sizing runs - SAC 05/12/22
                                             bool bIsSizingRun = (BEMPX_GetInteger( lDBID_ResProj_HVACSizingNeeded, lCSEHVACSizingReqd, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx ) &&
                                                                  lCSEHVACSizingReqd > 0);

                                             const char** ppCSEMeters  = (iCustomMeterOption == 1 ? pszCust1Meters            : (iCUACReportID > 0 ? pszCUACMeters            : pszMeters        ));       // SAC 09/08/22 (CUAC)  // CustomMeterOption - SAC 11/03/23
                                             const char** ppCSEMtrsMap = (iCustomMeterOption == 1 ? pszCust1Meters_ComMap     : (iCUACReportID > 0 ? pszCUACMeters_ComMap     : pszMeters_ComMap ));
                                             double*      pdMeterMults = (iCustomMeterOption == 1 ? sdaCust1MeterMults_ComMap : (iCUACReportID > 0 ? sdaCUACMeterMults_ComMap : sdaMeterMults_ComMap ));

                                             const char** ppCSEEnduses  = (iCustomMeterOption == 1 ? pszCSEEnduseListALL : (lSimPVBattOnly > 0 ? pszCSEEnduseList_PVBatt : (iCUACReportID > 0 ? pszCSEEnduseList     : (bPerformFullCSESim ? pszCSEEnduseList    : pszCSEEnduseList19   ))));   // SAC 10/28/21 (MFam)  // CustomMeterOption - SAC 11/03/23
                                             const char** ppCSEComEUMap = (iCustomMeterOption == 1 ? pszCSEEnduseListALL : (lSimPVBattOnly > 0 ? pszCSEEUList_PVBatt     : (iCUACReportID > 0 ? pszCSEEUList_CUACMap : (bPerformFullCSESim ? pszCSEEUList_ComMap : pszCSEEUList_ComMap19))));

															// Retrieve CSE simulation results
															if (iRetVal == 0 /*&& iCSESimRetVal == 0*/ && !bIsSizingRun)
															{	// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
																int iHrlyResRetVal = BEMPX_ReadCSEHourlyResults( cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), -1 /*lRunNumber-1*/,
																											sRunID.toLocal8Bit().constData(), sRunAbbrev.toLocal8Bit().constData(), posSimInfo[iSR]->iBEMProcIdx /*-1*/,
																											ppCSEMeters, ppCSEMtrsMap, pdMeterMults, ppCSEEnduses, ppCSEComEUMap, false /*bInitResults*/ );	// SAC 5/31/16  // SAC 7/23/18

																if (iHrlyResRetVal > 0 && iRunType[0] == CRM_StdDesign)		// SAC 10/8/20 (tic #3218)
																	sStdDsgnCSEResultsPathFile = cseRun.GetOutFile( CSERun::OutFileCSV );

		                                          //	sLogMsg = QString::asprintf( "      BEMPX_ReadCSEHourlyResults( %s, %d, %s, %s, BEMProc %d, ... ) returned %d", cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), lRunNumber-1,
		                                          //																									sRunID.toLocal8Bit().constData(), sRunAbbrev.toLocal8Bit().constData(), posSimInfo[iSR]->iBEMProcIdx, iHrlyResRetVal );
		                                          //	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																if (iHrlyResRetVal < 0)  // SAC 6/12/17
																{	switch (iHrlyResRetVal)
																	{	case -1 :  sLogMsg = QString( "Error retrieving hourly %1 results (-1) / run: %2, runID: %3, runAbrv: %4, file: %5" ).arg(
																																qsCSEName, QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );		break;
																		case -2 :  sLogMsg = QString( "Error retrieving hourly %1 results (-2) / Unable to retrieve BEMProc pointer / run: %2, runID: %3, runAbrv: %4, file: %5" ).arg(
																																qsCSEName, QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );		break;
																		case -3 :  sLogMsg = QString( "Error retrieving hourly %1 results (-3) / Run index not in valid range 0-%2 / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(BEMRun_MaxNumRuns-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );		break;
																		case -4 :  sLogMsg = QString( "Error retrieving hourly %1 results (-4) / RunID too large (limit of %2 chars) / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(BEMRun_RunNameLen-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );		break;
																		case -5 :  sLogMsg = QString( "Error retrieving hourly %1 results (-5) / RunAbrv too large (limit of %2 chars) / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(BEMRun_RunAbbrevLen-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -11:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / Invalid RunNumber / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -12:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / too many enduses found in results file / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -13:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / enduse name too long / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -14:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / incorrect number of fields encountered while reading meter hourly results / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -15:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / meter name too long / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -16:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / error opening CSE hourly results file / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -17:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / error parsing CSE hourly results file / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -18:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / CSE hourly results file not found / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		case -19:  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / too many meters found in results file / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																		default :  sLogMsg = QString( "Error retrieving hourly %1 results (%2) / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
																																qsCSEName, QString::number(iHrlyResRetVal), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );	break;
																	}
																	if (sLogMsg.size() > 0)
																		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																}
																else if (bVerbose)  // SAC 1/31/13
																	BEMPX_WriteLogFile( QString::asprintf( "      Hourly %s results retrieval returned %d", qsCSEName.toLocal8Bit().constData(), iHrlyResRetVal ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															   // add new Elec - SHWPmp enduse results array  (other arrays initialized based on enduse names in CSE results file)
									                     //		BEMPX_AddHourlyResultArray(	NULL, sRunID, "MtrElec", "DHWPmp", -1 /*iBEMProcIdx*/, TRUE /*bAddIfNotExist*/ );


                              						bool bIsStdDesign = !sRunAbbrev.compare("ab");
                              						if (iRetVal == 0 && (!sRunAbbrev.compare("ap") || bIsStdDesign))		// SAC 2/2/20 - ported from Res (Com tic #3157)  // SAC 9/17/20 - made to work (tic #3215)
                              						{	// revised to set data to Proj rather than EUseSummary due to how we blast & re-create EUseSummary objects later in analysis - SAC 9/17/20 (tic #3215)
                              							long lDBID_SSFResult = BEMPX_GetDatabaseID( (bIsStdDesign ? "Proj:StdDHW_SSF" : "Proj:PropDHW_SSF") );
                              							int iNumDHWSolarSys = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "cseDHWSOLARSYS" ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
                                                      // debugging DHW-SSFreporting - SAC 9/17/20
                                                      //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), run %1, iNumDHWSolarSys %2" ).arg( sRunAbbrev, QString::number( iNumDHWSolarSys ) ), NULL, FALSE, TRUE, FALSE );
                              							if (lDBID_SSFResult > 0 && iNumDHWSolarSys > 0)
                              							{	QString qsSSFPathFile = cseRun.GetOutFile( CSERun::OutFileCSV );				assert( qsSSFPathFile.length() > 6 );
                              								qsSSFPathFile = qsSSFPathFile.left( qsSSFPathFile.length()-4 ) + QString("-SSF.csv");
                              								QVector<QString> vqsSSFObjectNames;
                              								std::vector<double> daSSFResults;
                              								QString qsSSFError;
                              								int iSSFNum = CMX_RetrieveCSEAnnualCSVResult( qsSSFPathFile, vqsSSFObjectNames, daSSFResults, qsSSFError );
                              															//	int iResultColInGroup=2, int iNameColInGroup=1, int iNumColsInGroup=2, int iNumHdrCols=2, int iNumHdrRows=4 );		// SAC 1/29/20
                                                         // debugging DHW-SSFreporting - SAC 9/17/20
                                                         //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), CMX_RetrieveCSEAnnualCSVResult returned %1 for run %2 from CSV file: %3" ).arg( QString::number( iSSFNum ), sRunAbbrev, qsSSFPathFile ), NULL, FALSE, TRUE, FALSE );
                              								if (iSSFNum < 0)
                              									BEMPX_WriteLogFile( QString( "      %1" ).arg( qsSSFError ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              								else if (iSSFNum > 0)
                              								{	if (bIsStdDesign)
                              									{	// only store SSF result for model-wide Std design SolarSys
                              										long lDBID_StdDHWSolarSys = BEMPX_GetDatabaseID( "Proj:StdDHWSolarSysRef" );		assert( lDBID_StdDHWSolarSys > 0 );
                              										QString sStdDHWSlrSys;
                              										if (BEMPX_GetString( lDBID_StdDHWSolarSys, sStdDHWSlrSys, FALSE, 0, -1, 0, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx ))
                              										{	bool bSSFFound=false;
                              											for (int iSSF=0; (!bSSFFound && iSSF < iSSFNum); iSSF++)
                              											{	if (vqsSSFObjectNames[iSSF] == sStdDHWSlrSys)
                              												{	double dSSF = std::min( 1.0, daSSFResults[iSSF] );
                              													BEMPX_SetBEMData( lDBID_SSFResult, BEMP_Flt, &dSSF, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, posSimInfo[iSR]->iBEMProcIdx );
                                                                        // debugging DHW-SSFreporting - SAC 9/17/20
                                                                        //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), just set std model SSF to %1 for DHWSolarSys '%2'" ).arg( QString::number( dSSF ), sStdDHWSlrSys ), NULL, FALSE, TRUE, FALSE );
                              													bSSFFound = true;
                              											}	}
                              											if (!bSSFFound)
                              												BEMPX_WriteLogFile( "      Std model DHWSolarSys SSF result not found", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              									}	}
                              									else
                              									{	// store results to first 10 Proposed SolarSystems
                              										long lDBID_SSFNames = BEMPX_GetDatabaseID( "Proj:PropDHWNames_SSF" );		assert( lDBID_SSFNames > 0 );
                              										int iMaxNumSSFs = std::min( iSSFNum, BEMPX_GetNumPropertyTypeElementsFromDBID( lDBID_SSFNames ) );
                                                               // debugging DHW-SSFreporting - SAC 9/17/20
                                                               //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), about to set prop model SSF... lDBID_SSFNames %1 / iSSFNum %2 / iMaxNumSSFs %3" ).arg( QString::number( lDBID_SSFNames ), QString::number( iSSFNum ), QString::number( iMaxNumSSFs ) ), NULL, FALSE, TRUE, FALSE );
                              										for (int iSSF=0; iSSF < iMaxNumSSFs; iSSF++)
                              										{	double dSSF = std::min( 1.0, daSSFResults[iSSF] );
                              											QString sSSFName = vqsSSFObjectNames[iSSF];
                              											BEMPX_SetBEMData( lDBID_SSFResult+iSSF, BEMP_Flt,  &dSSF,             BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, posSimInfo[iSR]->iBEMProcIdx );
                              											BEMPX_SetBEMData( lDBID_SSFNames +iSSF, BEMP_QStr, (void*) &sSSFName, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, posSimInfo[iSR]->iBEMProcIdx );
                                                                  // debugging DHW-SSFreporting - SAC 9/17/20
                                                                  //	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), just set prop model SSF to %1 for DHWSolarSys '%2'" ).arg( QString::number( dSSF ), sSSFName ), NULL, FALSE, TRUE, FALSE );
                              										}
                              								}	}
                              						}	}

															}
														}
									            //}
												
												bCSESimOK = (iCSESimErrCode /*iCSESimRetVal*/ == 0);
												if (sCSEErrMsg.isEmpty() && iCSESimErrCode /*iCSESimRetVal*/ != 0)
													sCSEErrMsg = QString::asprintf( "error code %d", iCSESimErrCode /*iCSESimRetVal*/ );

											if (!bCSESimOK)
											{	sErrMsg = QString::asprintf( "CSE (Residential/PV/Battery) simulation not successful:  %s", sCSEErrMsg.toLocal8Bit().constData() );
                                    //				41 : CSE (Residential/PV/Battery) simulation not successful
												ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 41 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
											}
                                 if (iSR < MultEPlusSim_MaxSims && pqsCSESimStatusMsg)     // add logging of CSE status/result to string eventually posted to EUseSummary:SimSummary SAC 12/08/21
                                 {  if (!pqsCSESimStatusMsg[iSR]->isEmpty() && pqsCSESimStatusMsg[iSR]->indexOf("Error") > 0)
                                    {  // don't overwrite Error message from prior CSE sim
                                    }
                                    else if (!bCSESimOK)
                                       *pqsCSESimStatusMsg[iSR] = QString( "CSE Error (%1)" ).arg( QString::number(iCSESimErrCode /*iCSESimRetVal*/) );
                                    else
                                       *pqsCSESimStatusMsg[iSR] = "CSE Successful";
                                 }
                                 //{  QString qsCSESimStatusMsg;
                                 //   if (!bCSESimOK)
                                 //      qsCSESimStatusMsg = QString( "CSE Error (%1)" ).arg( QString::number(iCSESimErrCode /*iCSESimRetVal*/) );
                                 //   else
                                 //      qsCSESimStatusMsg = "CSE Successful";
                                 //   posRunInfo[iSR]->AddToSimStatusMsg( qsCSESimStatusMsg );
                                 //}

                                 // code to ensure Load Passing CSV files written by CSE are flushed, closed & readable before continuing - SAC 03/20/22
                                 long lDBID_Proj_CSE_LoadPassingExportFileName = BEMPX_GetDatabaseID( "Proj:CSE_LoadPassingExportFileName" );
     										QString sLoadPassingExportFile;
                                 if (lDBID_Proj_CSE_LoadPassingExportFileName > 0 && 
                                     BEMPX_GetString( lDBID_Proj_CSE_LoadPassingExportFileName, sLoadPassingExportFile, FALSE, 0, -1, 0, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx ) &&
                                     !sLoadPassingExportFile.isEmpty())
                                 {
                                    sLoadPassingExportFile = sProcessingPath + sLoadPassingExportFile;
                                    bool bLPFileOK = false;  int iLPTry = 0;
                                    while (!bLPFileOK && ++iLPTry <= 10)
                                    {  if (iLPTry > 1)
                                          Sleep( 1000 );  // pause before next attempt
                                       FILE* fileLP = NULL;
                                       int iLPFileErrorCode=0, iLPFileSeekErr=0, iLPFileSize=0;
                                       try
                                       {
                                          iLPFileErrorCode = fopen_s( &fileLP, sLoadPassingExportFile.toLocal8Bit().constData(), "rb" );
                                          if (iLPFileErrorCode == 0)
                                          {  // file opened ... now ensure we can read data
                                             iLPFileSeekErr = fseek( fileLP, 0L, SEEK_END );  // seek to the end for filesize info
                                             if (iLPFileSeekErr == 0)
                                                iLPFileSize = ftell( fileLP );
                                          }
                                          QString qsLPFileStatus;
                                          if (iLPFileErrorCode == 0 && iLPFileSeekErr == 0 && iLPFileSize > 0)
                                          {  bLPFileOK = true;
                                             qsLPFileStatus = QString( "file found and opened - size: %1" ).arg( QString::number( iLPFileSize ) );
                                          }
                                          else if (iLPFileErrorCode != 0)
                                             qsLPFileStatus = QString( "file open error (%1)" ).arg( QString::number( iLPFileErrorCode ) );
                                          else if (iLPFileSeekErr != 0)
                                             qsLPFileStatus = QString( "file seek error (%1)" ).arg( QString::number( iLPFileSeekErr ) );
                                          else if (iLPFileSize <= 0)
                                             qsLPFileStatus = QString( "file size not determined" );
                                          BEMPX_WriteLogFile( QString("   CSE load passing file check (iter %1):  %2").arg(QString::number(iLPTry), qsLPFileStatus), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                          fclose( fileLP );
                                       }
                                       //catch(const std::exception& e)
                                       //{
                                       //   std::cerr << e.what() << '\n';
                                       //}
                                       catch( ... )
                                       {
                                          BEMPX_WriteLogFile( QString("   CSE load passing file check (iter %1):  file exception thrown").arg(QString::number(iLPTry)), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                       }
                                    }  // end of while loop checking load passing CSE export
                                 }

											BEMPX_RefreshLogFile();	// SAC 5/19/14
										
                           }  // end of:  for (int iCSR=0; (iCSER < iNumCSERuns...
								}	// end of:  if (iaCSESimRunIdx.size() > 0 && sErrMsg.isEmpty())
			// END OF CSE ResDHW/PV/Battery simulation
}



//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:
//											 1 : pszBEMBasePathFile doesn't exist
//											 2 : pszRulesetPathFile doesn't exist
//											 3 : pszSimWeatherPath doesn't exist
//											 4 : pszCompMgrDLLPath specified, but doesn't exist
//											 5 : Invalid project log file name (too long)
//											 6 : Error writing to project log file
//											 7 : Building model input/project file not found
//											 8 : Error reading/initializing model input/project file
//											 9 : Errors encountered evaluating input model defaulting rules
//											10 : Errors encountered evaluating input model defaulting rules (multiple times)
//											11 : Error(s) encountered performing required data & numeric range checks
//											12 : Error(s) encountered checking input model for simulation compatibility
//											13 : Error(s) encountered checking input model for code requirements
//											14 : Error encountered initializing weather file locations and/or names
//											15 : Error creating or accessing the analysis processing directory
//											16 : Error generating Proposed Sizing model
//											17 : Error generating Proposed (final) model
//											18 : Error generating Standard Sizing model
//											19 : Error generating Standard (final) model
//											20 : Error initializing Standard Sizing model
//											21 : Error initializing Standard (final) model
//											22 : Analysis aborted - user chose not to overwrite SDD XML file
//											23 : Error: Unable to write SDD XML file
//											24 : Error(s) encountered simulating Standard Sizing model
//											25 : Error(s) encountered simulating Proposed model
//											26 : Error(s) encountered simulating Standard (final) model
//											27 : Error(s) encountered retrieving Standard Sizing model simulation results
//											28 : Error(s) encountered retrieving Proposed model simulation results
//											29 : Error(s) encountered retrieving Standard (final) model simulation results
//											30 : Model zone(s) exceed unmet load hours limits
//											31 : Error initializing building model database
//											32 : Error loading analysis ruleset
//											33 : User aborted analysis via progress dialog 'Cancel' button
//											34 : Invalid results object types
//											35 : Error copying results objects from a previous model
//											36 : Error copying equipment sizes/flows from source model
//											37 : Error(s) encountered reading building model (input/project) file
//											38 : Error:  EnergyPlus simulation engine not found.
//											39 : Error:  Version of EnergyPlus installed not compatible with analysis.
//											40 : Error setting up check of weather & design day file hashes
//											41 : CSE (Residential/PV/Battery) simulation not successful
//											42 : Error encountered in creating building geometry
//											43 : Error encountered initializing building geometry DBIDs
//											44 : Error initializing Proposed model
//											45 : Error(s) encountered simulating Proposed Sizing model
//											46 : Error(s) encountered retrieving Proposed Sizing model simulation results
//											47 : Error encountered in generating window shades
//											48 : UseExcptDsgnModel flag set but no path/filename specified by UseExcptDsgnModel
//											49 : IDF path/filename specified by Proj:UseExcptDsgnModel not found
//											50 : Exceptional Design IDF specification and the Quick Analysis feature cannot both be activated
//											51 : Window(s) and/or Door(s) are overlapping on ExtWalls with window shades defined
//											52 : Analysis aborted via callback function in calling application
//											53 : Input model contains one or more objects with the same name
//											54 : CSE (residential DHW, PV & Battery simulation engine) executable not found
//											55 : CSE (residential DHW simulation engine) use profile file not found
//											56 : CSE (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid
//											57 : Unable to copy DHW Use/Load Profile CSE include file into processing directory
//											58 : Unable to open/delete/write simulation input (.cse) file
//											59 : Error writing simulation input (.cse) file
//											60 : Unable to open/delete/write simulation weather file
//											61 : Error copying simulation weather file to processing directory
//											62 : Unable to open/delete/write simulation output file (.csv or .rep)
//											63 : Error evaluating CSE_SimulationPrep rules
//											64 : Unable to open/delete/write CSE include file
//											65 : Error copying simulation weather file to processing directory
//											66 : Analysis aborted - user chose to abort due to pre-analysis check warning(s) and/or compliance reporting issue(s)
//											67 : Error evaluating ProposedModelPrep rules
//											68 : One or more errors returned from Compliance Report Generator
//											69 : Error evaluating rulelist that converts residential DHW systems to code baseline
//											70 : Error evaluating 'GenerateZEROCodeReport' rulelist
//											71 : Error(s) encountered performing pre-analysis check of input model
//											72	: Error in sizing small central residential HPWH system(s) using CSE
//											73	: EnergyPlus IDF path/filename too long
//											74 : Error copying EnergyPlus simulation input file to processing directory
//											75 : Error copying EnergyPlus simulation weather file to processing directory
//											76 : Error evaluating 'AnalysisPostProcessing' rulelist
//											77 : Error applying AnalysisAction(s) to building model
//											78	: Error in sizing standard design DHW solar system using CSE
//											79	: Error in determining TDV of DHWSolarSys system(s) using CSE
//											80 : Analysis aborted - user chose not to overwrite NRCC/LMCC-PRF XML reporting file
//											81 : Error(s) encountered performing NRCC/LMCC-PRF XML export prep rules
//											82 : Error evaluating PreSim (sim input editing) rules
//											83 : Error evaluating ProposedCompliance residential rules
//											84	: Error evaluating ProposedInput_MFam residential rules  (BEMAnal_CECRes_EvalPropInp3Error)
//											85	: Error evaluating ProposedModelSimulationCheck residential rules  (BEMAnal_CECRes_EvalSimChkError)
//											86	: Error evaluating PostProposedInput residential rules  (BEMAnal_CECRes_EvalPostPropError)
//											87	: Error evaluating MultiFamilyAnalysisPrep rules  (BEMAnal_CECRes_EvalPropInp2Error)
//											88	: Error evaluating OneTimeAnalysisPrep rules  (BEMAnal_CECRes_EvalAnalPrepError)
//											89	: Error evaluating ProposedModelCodeAdditions rules  (BEMAnal_CECRes_EvalCodeAddError)
//											90 : Unable to open/delete/write CSE load-passing CSV file from prior E+ simulation
//											91 : Modelkit processing called for but Modelkit not found
//											92 : Modelkit processing error encountered
//											93	: Error evaluating GenerateDDYFromWeatherData rules
//											94 : Error downloading CUAC electric tariff schedule
//											95 : Error downloading CUAC gas tariff schedule
//											96 : Error calculating CUAC utility bill(s)
//											97	: Error evaluating SetupMFamInteriorSurfaces rules
//				101-200 - OS/E+ simulation issues
int CMX_PerformAnalysis_CECNonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile, const char* pszSimWeatherPath,
												const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath, const char* pszModelPathFile,
												const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile /*=true*/, const char* pszOptionsCSV /*=NULL*/,
												char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bDisplayProgress /*=false*/, HWND /*hWnd=NULL*/,
												char* pszResultsSummary /*=NULL*/, int iResultsSummaryLen /*=0*/, int iSecurityKeyIndex /*=0*/, const char* pszSecurityKey /*=NULL*/ )		// SAC 5/16/14   // SAC 1/10/17
{	return CMX_PerformAnalysisCB_NonRes(	pszBEMBasePathFile, pszRulesetPathFile, pszSimWeatherPath, pszCompMgrDLLPath, pszDHWWeatherPath, pszProcessingPath, pszModelPathFile,
														pszLogPathFile, pszUIVersionString, bLoadModelFile /*=true*/, pszOptionsCSV /*=NULL*/, pszErrorMsg /*=NULL*/, iErrorMsgLen /*=0*/,
														bDisplayProgress /*=false*/, pszResultsSummary /*=NULL*/, iResultsSummaryLen /*=0*/, iSecurityKeyIndex, pszSecurityKey, NULL /*pAnalProgCallbackFunc*/ );
}

int CMX_PerformAnalysisCB_NonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile, const char* pszSimWeatherPath,
												const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath, const char* pszModelPathFile,
												const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile /*=true*/, const char* pszOptionsCSV /*=NULL*/,
												char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bDisplayProgress /*=false*/,
												char* pszResultsSummary /*=NULL*/, int iResultsSummaryLen /*=0*/, int iSecurityKeyIndex /*=0*/, const char* pszSecurityKey /*=NULL*/,		// SAC 5/16/14   // SAC 1/10/17
												PAnalysisProgressCallbackFunc pAnalProgCallbackFunc /*=NULL*/ )		// SAC 5/28/15
{	int iRetVal = 0;
	bool bAbort = false;
	QString sUIVersionString = pszUIVersionString;
	QString sMsg, sErrMsg, sLogMsg;
#define NRES_AnalErrMsg_Len  1024
	char pszAnalErrMsg[NRES_AnalErrMsg_Len];	// SAC 6/12/15
	int iError;

// SAC 1/23/14 - added duration logic and corresponding logging (above & beyond DurationStats option)
	boost::posix_time::ptime	tmAnalStartTime = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::ptime	tmAnalOther = tmAnalStartTime, tmMark;
#define  MAX_TimeArray  6
	double dTimeToTranslate[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
	double dTimeToSimDsgn[  ] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
	double dTimeToSimAnn[   ] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
	double dTimeToReport = 0.0, dTimeToOther = 0.0, dTimeOverall = 0.0; 
	int iNumTimeToTranslate=0, iNumTimeToSimDsgn=0, iNumTimeToSimAnn=0, iNumTimeToReport=0, iNumDsgnSims=0, iNumAnnSims=0; 

	QVector<QString> saCSVOptions;
	if (pszOptionsCSV && strlen( pszOptionsCSV ) > 0)
	{	if (ParseCSVRecord( pszOptionsCSV, &saCSVOptions ) < 2)
		{	assert( false );
	}	}
//	int  iMaxNumErrsReportedPerType	=	 GetCSVOptionValue( "MaxNumErrorsReportedPerType",   5,  saCSVOptions ); 
	int iVerbose = GetCSVOptionValue( "Verbose", 0, saCSVOptions );
	bool bVerbose = (iVerbose > 0);
	bool bStoreBEMDetails				=	(GetCSVOptionValue( "StoreBEMDetails"            ,   0,  saCSVOptions ) > 0);
	bool bSilent							=	(GetCSVOptionValue( "Silent"                     ,   0,  saCSVOptions ) > 0);
	int  iAnalysisThruStep				=	 GetCSVOptionValue( "AnalysisThruStep"           , 100,  saCSVOptions ); 
	int  iDontAbortOnErrorsThruStep	=	 GetCSVOptionValue( "DontAbortOnErrorsThruStep"  ,   0,  saCSVOptions ); 		// SAC 7/25/13 - added to ensure analysis pushed thru to a certain point regardless of errors encountered
	bool bBypassInputChecks				=	(GetCSVOptionValue( "BypassInputChecks"          ,   0,  saCSVOptions ) > 0);
	bool bBypassUMLHChecks				=	(GetCSVOptionValue( "BypassUMLHChecks"           ,   0,  saCSVOptions ) > 0);
	bool bBypassPreAnalysisCheckRules=	(GetCSVOptionValue( "BypassPreAnalysisCheckRules",   0,  saCSVOptions ) > 0);  // SAC 1/25/19 - (tic #2924)
	bool bBypassCheckSimRules			=	(GetCSVOptionValue( "BypassCheckSimRules"        ,   0,  saCSVOptions ) > 0);
	bool bBypassCheckCodeRules			=	(GetCSVOptionValue( "BypassCheckCodeRules"       ,   0,  saCSVOptions ) > 0);
	bool bBypassValidFileChecks		=	(GetCSVOptionValue( "BypassValidFileChecks"      ,   0,  saCSVOptions ) > 0);  // SAC 11/11/13
	bool bDurationStats					=	(GetCSVOptionValue( "DurationStats"              ,   0,  saCSVOptions ) > 0);
	int  iNumBypassItems = 4;
	bool pbBypassOpenStudio[10]		={	false, false, false, false, false, false, false, false, false, false };		// moved real/used init of these down below where we know the CodeType being analyzed
	long plOverrideAutosize[10]		={	false, false, false, false, false, false, false, false, false, false };
	bool bIgnoreFileReadErrors			= ( GetCSVOptionValue( "IgnoreFileReadErrors"       ,   0,  saCSVOptions ) > 0);		// SAC 6/28/13 - added
	bool bPurgeUnreferencedObjects	= ( GetCSVOptionValue( "PurgeUnreferencedObjects"   ,   1,  saCSVOptions ) > 0);		// SAC 8/12/13 - added
	bool bProduceALLModelReports		= ( GetCSVOptionValue( "ModelRpt_ALL"               ,   0,  saCSVOptions ) > 0);		// SAC 8/24/13 - added
	bool bSendRptSignature				= ( GetCSVOptionValue( "SendRptSignature"           ,   1,  saCSVOptions ) > 0);				bool bOrigSendRptSignature = bSendRptSignature;
	bool bComplianceReportPDF			= ( GetCSVOptionValue( "ComplianceReportPDF"        ,   0,  saCSVOptions ) > 0);
	bool bComplianceReportXML			= ( GetCSVOptionValue( "ComplianceReportXML"        ,   0,  saCSVOptions ) > 0);
	bool bComplianceReportStd			= ( GetCSVOptionValue( "ComplianceReportStd"        ,   0,  saCSVOptions ) > 0);		// SAC 11/13/15
	bool bBypassRecircDHW				=	(GetCSVOptionValue( "BypassRecircDHW"            ,   0,  saCSVOptions ) > 0);		// SAC 10/21/13
	int  iSimulationStorage				=	 GetCSVOptionValue( "SimulationStorage"          ,   1,  saCSVOptions ); 	// SAC 1/23/14
	int  iAnalysisStorage  				=	 GetCSVOptionValue( "AnalysisStorage"            ,   2,  saCSVOptions ); 	// SAC 1/23/14
	bool bParallelSimulations			=	 GetCSVOptionValue( "ParallelSimulations"        ,   1,  saCSVOptions );	// SAC 4/18/14
	int  iLogWritingMode  				=	 GetCSVOptionValue( "LogWritingMode"             , 100,  saCSVOptions ); 	// SAC 5/20/14
	bool bVerboseReportRules			=	(GetCSVOptionValue( "LogReportRuleEvaluation"    ,   0,  saCSVOptions ) > 0);	// SAC 5/20/14
	long lQuickAnalysisOption			=   GetCSVOptionValue( "QuickAnalysis"              ,  -1,  saCSVOptions );		// SAC 11/8/14
	bool bWriteRulePropsToResultsXML	=  (GetCSVOptionValue( "WriteRulePropsToResultsXML" ,   0,  saCSVOptions ) > 0);	// SAC 1/12/15		// SAC 2/18/15 - toggled default to 0
	int  iEnableRptGenStatusChecks	=	 GetCSVOptionValue( "EnableRptGenStatusChecks"   ,   1,  saCSVOptions );		// SAC 2/20/15
	bool bWriteUMLHViolationsToFile	=  (GetCSVOptionValue( "WriteUMLHViolationsToFile"  ,   1,  saCSVOptions ) > 0);	// SAC 3/18/15
	bool bLogCSESimulation	         =  (GetCSVOptionValue( "LogRecircDHWSimulation"     ,   0,  saCSVOptions ) > 0) ||	// SAC 6/4/15
	                                    (GetCSVOptionValue( "LogCSESimulation"           ,   0,  saCSVOptions ) > 0);	// SAC 7/13/18
	bool bPromptUserUMLHWarning		=  (GetCSVOptionValue( "PromptUserUMLHWarning"      ,   0,  saCSVOptions ) > 0);	// SAC 3/11/15
	bool bPerformDupObjNameCheck		=  (GetCSVOptionValue( "PerformDupObjNameCheck"     ,   1,  saCSVOptions ) > 0);	// SAC 6/12/15
	int  iPreAnalysisCheckPromptOption = GetCSVOptionValue( "PreAnalysisCheckPromptOption",  0,  saCSVOptions );		// SAC 1/26/19 - (tic #2924)
	int  iCompReportWarningOption		=	 GetCSVOptionValue( "CompReportWarningOption"    ,   0,  saCSVOptions );		// SAC 7/5/16
	int  iAnalysisDialogTimeout		=	 GetCSVOptionValue( "AnalysisDialogTimeout"      ,  20,  saCSVOptions );		// SAC 1/31/20   // SAC 7/1/20 - renamed & applied to UMLH dialog
	bool bReportStandardUMLHs		   =  (GetCSVOptionValue( "ReportStandardUMLHs"        ,   0,  saCSVOptions ) > 0);	// SAC 11/11/19
	bool bReportAllUMLHZones    		=  (GetCSVOptionValue( "ReportAllUMLHZones"         ,   0,  saCSVOptions ) > 0);	// SAC 11/11/19
	bool bSimulateCSEOnly	   		=  (GetCSVOptionValue( "SimulateCSEOnly"            ,   0,  saCSVOptions ) > 0);	// SAC 3/10/20
	bool bReportGenVerbose	   		=  (GetCSVOptionValue( "ReportGenVerbose"           ,   0,  saCSVOptions ) > 0);	// SAC 3/20/20
   long lIsBatchProcessing          =   GetCSVOptionValue( "IsBatchProcessing"          ,   0,  saCSVOptions );		// SAC 03/19/21
	bool bReportGenNRCCPRFXML	 		=  (GetCSVOptionValue( "ReportGenNRCCPRFXML"        ,   1,  saCSVOptions ) > 0);	// SAC 04/10/21  // switched default to 1 - SAC 08/31/22
   long lLogAnalysisProgressOption  =   GetCSVOptionValue( "LogAnalysisProgress"        ,  -1,  saCSVOptions );		// SAC 01/14/22
   long lEnableResearchMode	      =   GetCSVOptionValue( "EnableResearchMode"         ,   0,  saCSVOptions );		// SAC 02/26/22
   long lAllowPropPVBatt            =   GetCSVOptionValue( "AllowProposedPVBattery"     ,  -1,  saCSVOptions );		// SAC 10/25/23
   long lAllowStdPV                 =   GetCSVOptionValue( "AllowStandardPV"            ,  -1,  saCSVOptions );		// SAC 10/25/23
   long lAllowStdBatt               =   GetCSVOptionValue( "AllowStandardBattery"       ,  -1,  saCSVOptions );		// SAC 10/25/23
   bool bAllowAnalysisAbort			=  true;		//(GetCSVOptionValue( "AllowAnalysisAbort"         ,   1,  saCSVOptions ) > 0);	// SAC 4/5/15
	if (bPromptUserUMLHWarning && (bSilent || iDontAbortOnErrorsThruStep > 6))
		bPromptUserUMLHWarning = false;		// SAC 3/19/15 - toggle OFF PromptUserUMLHWarning if 'silent' flag set or DontAbortOnErrorsThruStep includes UMLH check step

	int  iRptGenConnectTimeout		   =	 GetCSVOptionValue( "RptGenConnectTimeout"       ,  10,  saCSVOptions );		// SAC 11/02/22
	int  iRptGenReadWriteTimeout		=	 GetCSVOptionValue( "RptGenReadWriteTimeout"     , CECRptGenDefaultReadWriteTimeoutSecs,  saCSVOptions );		// SAC 11/02/22

	int  iDownloadVerbose         	=	 GetCSVOptionValue( "DownloadVerbose"            ,  -1,  saCSVOptions );		// SAC 09/03/24

	long plExportHourlyResults[4]		={	                                                     0                      ,		// SAC 8/21/14
													                                                     0                      ,		// SAC 8/21/14
													 GetCSVOptionValue( "ExportHourlyResults_ap"     ,   0,  saCSVOptions )     ,		// SAC 8/21/14
													 GetCSVOptionValue( "ExportHourlyResults_ab"     ,   0,  saCSVOptions )       };	// SAC 8/21/14

	int  iExportHourlyResults_All		=	 GetCSVOptionValue( "ExportHourlyResults_All"    ,   0,  saCSVOptions ); 	// SAC 8/21/14
	if (iExportHourlyResults_All > 0)
	{	plExportHourlyResults[2] = iExportHourlyResults_All;
		plExportHourlyResults[3] = iExportHourlyResults_All;
	}

	long plSimOutputVariablesToCSV[4]	={	 GetCSVOptionValue( "SimOutputVariablesToCSV_zp"  ,   0,  saCSVOptions ) ,		// SAC 4/11/16
													    GetCSVOptionValue( "SimOutputVariablesToCSV_zb"  ,   0,  saCSVOptions ) ,		// SAC 4/11/16
														 GetCSVOptionValue( "SimOutputVariablesToCSV_ap"  ,   0,  saCSVOptions ) ,		// SAC 4/11/16
														 GetCSVOptionValue( "SimOutputVariablesToCSV_ab"  ,   0,  saCSVOptions )   };	// SAC 4/11/16
	int  iSimOutputVariablesToCSV_All	=	 GetCSVOptionValue( "SimOutputVariablesToCSV_All" ,   0,  saCSVOptions ); 		// SAC 4/11/16
	if (iSimOutputVariablesToCSV_All > 0)
	{	plSimOutputVariablesToCSV[0] = iSimOutputVariablesToCSV_All;		plSimOutputVariablesToCSV[1] = iSimOutputVariablesToCSV_All;
		plSimOutputVariablesToCSV[2] = iSimOutputVariablesToCSV_All;		plSimOutputVariablesToCSV[3] = iSimOutputVariablesToCSV_All;
	}
	bool bNeedReadVarsESO = (	plSimOutputVariablesToCSV[0] > 0 || plSimOutputVariablesToCSV[1] > 0 || 
										plSimOutputVariablesToCSV[2] > 0 || plSimOutputVariablesToCSV[3] > 0 );

	int iDLLCodeYear = 2013;		// SAC 11/19/15
#ifdef CODEYEAR2016
	    iDLLCodeYear = 2016;
#elif  CODEYEAR2019
	    iDLLCodeYear = 2019;
#elif  CODEYEAR2022
	    iDLLCodeYear = 2022;		// SAC 4/24/20
#elif  CODEYEAR2025
	    iDLLCodeYear = 2025;		// SAC 10/23/22
#endif

	int iNumFileOpenDefaultingRounds = GetCSVOptionValue( "NumFileOpenDefaultingRounds", 3, saCSVOptions );		// SAC 4/11/18

	bool bUseEPlusRunMgr = (GetCSVOptionValue( "UseEPlusRunMgr", 1, saCSVOptions ) > 0);		// SAC 2/15/19

	QString sProxyServerAddress, sProxyServerCredentials, sProxyServerType, sNetComLibrary;
	GetCSVOptionString( "ProxyServerAddress"    , sProxyServerAddress    , saCSVOptions );
	GetCSVOptionString( "ProxyServerCredentials", sProxyServerCredentials, saCSVOptions );
	GetCSVOptionString( "ProxyServerType"       , sProxyServerType       , saCSVOptions );		// SAC 11/3/15
	GetCSVOptionString( "NetComLibrary"         , sNetComLibrary         , saCSVOptions );		// SAC 11/5/15

	QString sRunTitle;		// SAC 5/16/14 - added CSVOptions-based RunTitle specification
	GetCSVOptionString( "RunTitle", sRunTitle, saCSVOptions );

	QString sIDFToSimulate;
	GetCSVOptionString( "IDFToSimulate", sIDFToSimulate, saCSVOptions );		// SAC 1/25/14 - added new INI option to force simulation of a certain IDF file, regardless of the model/OSM(s) generated during analysis
	if (!sIDFToSimulate.isEmpty() && !FileExists( sIDFToSimulate.toLocal8Bit().constData() ))
	{	BEMPX_WriteLogFile( QString::asprintf( "File specified in IDFToSimulate option not found:  %s", sIDFToSimulate.toLocal8Bit().constData() ) );
		sIDFToSimulate.clear();
	}

   QString sModelkitPath;     // HybridCooling - SAC 06/23/22
   GetCSVOptionString( "ModelkitPath", sModelkitPath, saCSVOptions );

   long iCUACReportID = GetCSVOptionValue( "CUACReportID", 0, saCSVOptions );		// value > 0 => doing CUAC analysis & reporting - SAC 08/19/22 (CUAC)
   int iCUAC_BEMProcIdx = -1;
   //if (iCUACReportID > 0)  // test
   //   BEMMessageBox( QString::asprintf( "CUACReportID %ld", iCUACReportID ) );
   long iLogCUACBillCalcDetails = GetCSVOptionValue( "LogCUACBillCalcDetails", -1, saCSVOptions );		// value < 0: use bVerbose / > 0: log details / else don't - SAC 09/21/23 (CUAC)
	QString sCUACElecTariffFile, sCUACGasTariffFile;      // SAC 03/12/24
	GetCSVOptionString( "CUACElecTariffFile", sCUACElecTariffFile, saCSVOptions );
	GetCSVOptionString( "CUACGasTariffFile" , sCUACGasTariffFile , saCSVOptions );
   QString sCUACInvalidMsg;      // SAC 01/02/25

   long iCustomMeterOption = GetCSVOptionValue( "CustomMeterOption", -1, saCSVOptions );		// value > 0 => custom sim metering that invalidates compliance analysis - SAC 11/02/23

   bool bSaveLogAnalysisMsgs = ebLogAnalysisMsgs;
   ebLogAnalysisMsgs = (GetCSVOptionValue( "LogAnalysisMsgs", 0, saCSVOptions ) > 0);     // mechanism to toggle ON analysis messages w/out full verbose output - SAC 06/26/23

	int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );
	QString sDebugRuleEvalCSV;		// SAC 1/9/14 - ported from Res analysis - ability to specify targeted rule eval debug info
	GetCSVOptionString( "DebugRuleEvalCSV", sDebugRuleEvalCSV, saCSVOptions );
	BEMCompNameTypePropArray compRuleDebugInfo;
	void* pCompRuleDebugInfo = NULL;
	if (!sDebugRuleEvalCSV.isEmpty() && FileExists( sDebugRuleEvalCSV.toLocal8Bit().constData() ))
	{	sLogMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Abort' to ignore this file.", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
		if (!OKToWriteOrDeleteFile( sDebugRuleEvalCSV.toLocal8Bit().constData(), sLogMsg, bSilent ))
		{	if (bSilent)
				sLogMsg = QString::asprintf( "ERROR:  Unable to open %s file:  %s", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
			else
				sLogMsg = QString::asprintf( "ERROR:  User chose not to use/reference %s file:  %s", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
			BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
		}
      else
		{	int iDbgVerboseFlag=0, iDbgLogRuleListEval=0;
			if (compRuleDebugInfo.ReadData( sDebugRuleEvalCSV.toLocal8Bit().constData(), iDbgVerboseFlag, iDbgLogRuleListEval ))
			{	if (iDbgLogRuleListEval != iVerbose)
				{	iVerbose = iDbgLogRuleListEval;
					bVerbose = (iVerbose > 0);
				}
				pCompRuleDebugInfo = &compRuleDebugInfo;
			}
			else
			{	assert( FALSE );	// error reading rule debug info CSV
	}	}	}

  // SAC 12/19/13 - added mechanism to ensure report watermarked for non-compliance when certain developer options flags are set by user (not defaulted)
	QString sDevOptsNotDefaulted, sDevOptsNotDefaultedAbbrev;
	QString saDevOptsObjProps[] = {	"Proj:DisableDayltgCtrls", "Proj:DefaultDayltgCtrls", "Proj:AutoHardSize", "Proj:AutoEffInput", " " };		// SAC 8/12/14 - updated w/ latest dayltg flags
	double faDevOptsPropOKVals[] = {               0,                         0,                      0,                      0           };

	QString sCSEIncludeFileDBID;	// SAC 5/18/16
	sbLogCSECallbacks = bLogCSESimulation;
	QString sCSEexe, sMissing;
	siCallbackCount = 0;		// SAC 11/17/13 - reset CSE message callback counter between each analysis run
	bool bStoreAllowCallbackAbort = sbAllowCallbackAbort;		// SAC 4/5/15
	sbAllowCallbackAbort = bAllowAnalysisAbort;
	ClearCSEProgressMap();	// SAC 1/12/18

   bool bOrig_LogAnalysisProgress = ebLogAnalysisProgress;     // SAC 01/14/22 (MFam)
   if (lLogAnalysisProgressOption >= 0)
      ebLogAnalysisProgress = (lLogAnalysisProgressOption > 0);

// QT Application stuff
//#ifdef CM_QTGUI
	int iProgressRetVal = 1;
	int iProgressStep = -1;
	bool bQtAppInitHere = false;	// SAC 11/11/15
	if (sq_app == NULL && (bDisplayProgress || bPromptUserUMLHWarning))
	{	//assert( sq_app == NULL );
		QCoreApplication* pQCA = QCoreApplication::instance();
		if (pQCA)
			sq_app = (QApplication*) pQCA;
		else
		{	int argc = 0;
			sq_app = new QApplication( argc, NULL );
			bQtAppInitHere = true;
		}
		if (sq_app)
		{	ssEXEPath = sq_app->applicationDirPath();
			ssEXEPath = QDir::cleanPath(ssEXEPath);
			if (ssEXEPath[ssEXEPath.length()-1] != '/' &&
				 ssEXEPath[ssEXEPath.length()-1] != '\\')
				ssEXEPath += '/';  // ensure trailing slash
	}	}
   else
      StoreEXEPath();      // restore original EXE path retrieval for when no sq_app - SAC 01/19/25
//#endif

	QString sBEMBasePathFile	= pszBEMBasePathFile;
	QString sRulesetPathFile	= pszRulesetPathFile;
	QString sSimWeatherPath		= pszSimWeatherPath;
	QString sCompMgrDLLPath		= pszCompMgrDLLPath;		// SAC 3/6/14
	if (sCompMgrDLLPath.isEmpty())
		sCompMgrDLLPath = ssEXEPath;
	QString sEPlusPath;		// SAC 12/30/13 - added
	GetCSVOptionString( "EnergyPlusPath", sEPlusPath, saCSVOptions );
	if (sEPlusPath.isEmpty())
	//	sEPlusPath = "EPlus\\";
		sEPlusPath = sCompMgrDLLPath + "EPlus\\";
	if (sModelkitPath.isEmpty())     // HybridCooling - SAC 06/23/22
		sModelkitPath = sCompMgrDLLPath + "Modelkit\\";
   else if (sModelkitPath.right(1).compare('/')!=0 && sModelkitPath.right(1).compare('\\')!=0)
      sModelkitPath += "\\";  // ensure ModelkitPath contains trailing slash/backslash
	QString sDHWWeatherPath		= pszDHWWeatherPath;
	QString sProcessingPath		= pszProcessingPath;
	QString sModelPathFile		= pszModelPathFile;
	QString sLogPathFile			= pszLogPathFile;

	RelativeToCompletePath_IfNeeded( sBEMBasePathFile );		// revise EACH path to be relative to EXE path (if the path is specified but not complete)
	RelativeToCompletePath_IfNeeded( sRulesetPathFile );
	RelativeToCompletePath_IfNeeded( sSimWeatherPath  );
	RelativeToCompletePath_IfNeeded( sCompMgrDLLPath  );
	RelativeToCompletePath_IfNeeded( sDHWWeatherPath  );
	RelativeToCompletePath_IfNeeded( sProcessingPath  );
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	RelativeToCompletePath_IfNeeded( sLogPathFile     );
	RelativeToCompletePath_IfNeeded( sEPlusPath       );  // SAC 12/30/13

   QString qsBEMBaseDir;      // SAC 10/28/22 (CUAC)
   QString qsBEMBaseExtension = sBEMBasePathFile.right(4);
   if (!qsBEMBaseExtension.isEmpty() && qsBEMBaseExtension.compare(".bin", Qt::CaseInsensitive))
   {  // have sBEMBasePathFile but NOT a .bin filename - use only for qsBEMBaseDir
      qsBEMBaseDir = sBEMBasePathFile;
      if (qsBEMBaseDir.right(1).compare('/') && qsBEMBaseDir.right(1).compare('\\'))
         qsBEMBaseDir += '\\';  // add trailing backslash
      sBEMBasePathFile.clear();
      pszBEMBasePathFile = NULL;
   }
   else if (FileExists( sBEMBasePathFile ))
   {  // use path of sBEMBasePathFile to set qsBEMBaseDir
      int iLastSlash = std::max( sBEMBasePathFile.lastIndexOf('\\'), sBEMBasePathFile.lastIndexOf('/') );
      qsBEMBaseDir = sBEMBasePathFile.left( iLastSlash+1 );
   }
   // else - qsBEMBaseDir left blank which may cause CUAC PDF report gen issue in finding CEC logo JPG

	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	QString sModelFileOnlyWithExt = sModelFileOnly;
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

	QString sXMLResultsFileName = sModelPathFile;
	if (sXMLResultsFileName.lastIndexOf('.'))
		sXMLResultsFileName  = sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') );
	sXMLResultsFileName += " - AnalysisResults.xml";

	QString sNRCCXMLFileName = sModelPathFile;	// SAC 11/26/20
	if (sNRCCXMLFileName.lastIndexOf('.'))
		sNRCCXMLFileName  = sNRCCXMLFileName.left( sNRCCXMLFileName.lastIndexOf('.') );
   // sNRCCXMLFileName += " - NRCCPRF.xml";   - moved down, after loading model when we know NRCC vs. LMCC - SAC 08/24/22 (LMCC)
	int iNRCCXMLClassID = 0;

	// UMLH check stuff
	QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));		// enables Locale-specific formatted numeric strings
	QString sUMLHTextFileMsg, sUMLHTextFileName = sModelPathFile;
	if (sUMLHTextFileName.lastIndexOf('.'))
	{	sUMLHTextFileName  = sUMLHTextFileName.left( sUMLHTextFileName.lastIndexOf('.') );
		sUMLHTextFileName += " - UMLH Zones.txt";
		if (FileExists( sUMLHTextFileName.toLocal8Bit().constData() ))	// if UMLH Zones text file already exists (from previous run), delete it before continuing processing
			DeleteFile( sUMLHTextFileName.toLocal8Bit().constData() );
	}
	int iNumPropClgUMLHViolations=0, iNumPropHtgUMLHViolations=0;		// SAC 4/6/20
	bool bFailAnalysisForUMLH = false;		// SAC 4/23/20 (tic #2680)

	bool bRestoreBEMProcLogTimeStampSetting = false;  // SAC 11/17/13
	bool bInitialBEMProcLogTimeStamp = BEMPX_GetLogTimeStamps();
	if ( ( bInitialBEMProcLogTimeStamp && iVerbose == 2) ||
		  (!bInitialBEMProcLogTimeStamp && iVerbose != 2) )		// SAC 11/17/13 - switch log timestamp setting depending on iVerbose setting (if needed)
	{	bRestoreBEMProcLogTimeStampSetting = true;
		BEMPX_EnableLogTimeStamps( (iVerbose != 2) );
	}

	// SAC 3/6/14 - setup log filename in the case where we will be loading the project file during analysis
	if (bLoadModelFile && FileExists( sModelPathFile.toLocal8Bit().constData() ) && sLogPathFile.isEmpty())
	{	if (sModelPathFile.lastIndexOf('.') > 0)
			sLogPathFile = sModelPathFile.left( sModelPathFile.lastIndexOf('.') );
		else
			sLogPathFile = sModelPathFile;
		sLogPathFile += ".log";
		BEMPX_WriteLogFile( "Initializing log path/file", sLogPathFile.toLocal8Bit().constData(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	int iCodeType = CT_T24N;		// SAC 10/2/14 - added to facilitate code-specific processing
	QString sLoadedRuleSetID, sLoadedRuleSetVer;
	if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))
	{	if (sLoadedRuleSetID.indexOf( "T24N" ) >= 0 || sLoadedRuleSetID.indexOf( "CA " ) == 0)
			iCodeType = CT_T24N;
		else if (sLoadedRuleSetID.indexOf( "S901G" ) >= 0 ||
					(sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0))
			iCodeType = CT_S901G;
		else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
			iCodeType = CT_ECBC;
		else if (sLoadedRuleSetID.indexOf( "360" ) >= 0)	// SAC 1/30/20
			iCodeType = CT_360;
		else
		{	assert( FALSE );	// what ruleset is this ??
	}	}

   QVector<QString> saCopyAcrossModelClassPrefixes;      // added to copy NRCCPRF objects into each subsequent model - SAC 11/24/20
	if (iCodeType == CT_T24N)
   {  saCopyAcrossModelClassPrefixes.push_back( QString( "nrcc" ) );
      saCopyAcrossModelClassPrefixes.push_back( QString( "cf1r" ) );    // added to include CF1R objects for LMCC reporting - SAC 08/22/22 (LMCC)
   }

	// initialize progress dialog settings
	if (iCodeType == CT_T24N)
	{	if (bParallelSimulations)
				SetCECNResProgressVal_Parallel( true, true, true, true, false );  // assume E+ and no CSE - SAC 11/19/21
		else	SetCECNResProgressVal_Serial( true, true, true, true );
	}
	else
	{	if (bParallelSimulations)
				SetS901GProgressVal_Parallel( true, true, true );
		else	SetS901GProgressVal_Serial( true, true, true, true );
	}
   int iDbgOutFileIdx=1;  // variable to ensure unique debug output filenames - SAC 11/25/20

                        // SAC 5/5/15 - ResultSummary Logging
								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
								{	BEMPX_WriteLogFile( "  PerfAnal_NRes - starting, w/ arguments:", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									QString sOptsCSV = pszOptionsCSV;
								// prevent logging sensitive info contained in OptionsCSV string
							//		int iOptCSVIdx = sOptsCSV.indexOf("ProxyServerAddress");
							//		if (iOptCSVIdx >= 0)
							//		{	int iCom1Idx = sOptsCSV.indexOf(",", iOptCSVIdx+1);
							//			if (iCom1Idx)
							//			{	int iCom2Idx = sOptsCSV.indexOf(",", iCom1Idx+1);
							//				if (iCom1Idx < (iCom2Idx-1))
							//					sOptsCSV = sOptsCSV.left( iCom1Idx+1 ) + "<PrxySrvrAdd>" + sOptsCSV.right( sOptsCSV.length()-iCom2Idx );
							//		}	}
							//		iOptCSVIdx = sOptsCSV.indexOf("ProxyServerCredentials");
							//		if (iOptCSVIdx >= 0)
							//		{	int iCom1Idx = sOptsCSV.indexOf(",", iOptCSVIdx+1);
							//			if (iCom1Idx)
							//			{	int iCom2Idx = sOptsCSV.indexOf(",", iCom1Idx+1);
							//				if (iCom1Idx < (iCom2Idx-1))
							//					sOptsCSV = sOptsCSV.left( iCom1Idx+1 ) + "<PrxySrvrCred>" + sOptsCSV.right( sOptsCSV.length()-iCom2Idx );
							//		}	}
							// SAC 8/21/18 - new method of removing sensitive data from that written to the log file
									QVector<QString> saClrOptions;  saClrOptions.push_back("ProxyServerAddress");  saClrOptions.push_back("ProxyServerCredentials");  // SAC 8/21/18
									StripOutCSVOptions( sOptsCSV, &saClrOptions, "***" );

									for (int iArg=0; iArg<17; iArg++)
									{	switch (iArg)
										{	case  0 :	sLogMsg = QString::asprintf( "       BEMBasePathFile    = %s", (pszBEMBasePathFile == NULL ? "(null)" : (strlen( pszBEMBasePathFile ) < 1 ? "(empty)" : pszBEMBasePathFile)) );	  break;
											case  1 :	sLogMsg = QString::asprintf( "       RulesetPathFile    = %s", (pszRulesetPathFile == NULL ? "(null)" : (strlen( pszRulesetPathFile ) < 1 ? "(empty)" : pszRulesetPathFile)) );     break;
											case  2 :	sLogMsg = QString::asprintf( "       SimWeatherPath     = %s", (pszSimWeatherPath  == NULL ? "(null)" : (strlen( pszSimWeatherPath  ) < 1 ? "(empty)" : pszSimWeatherPath )) );     break;
											case  3 :	sLogMsg = QString::asprintf( "       CompMgrDLLPath     = %s", (pszCompMgrDLLPath  == NULL ? "(null)" : (strlen( pszCompMgrDLLPath  ) < 1 ? "(empty)" : pszCompMgrDLLPath )) );     break;
											case  4 :	sLogMsg = QString::asprintf( "       DHWWeatherPath     = %s", (pszDHWWeatherPath  == NULL ? "(null)" : (strlen( pszDHWWeatherPath  ) < 1 ? "(empty)" : pszDHWWeatherPath )) );     break;
											case  5 :	sLogMsg = QString::asprintf( "       ProcessingPath     = %s", (pszProcessingPath  == NULL ? "(null)" : (strlen( pszProcessingPath  ) < 1 ? "(empty)" : pszProcessingPath )) );     break;
											case  6 :	sLogMsg = QString::asprintf( "       ModelPathFile      = %s", (pszModelPathFile   == NULL ? "(null)" : (strlen( pszModelPathFile   ) < 1 ? "(empty)" : pszModelPathFile  )) );     break;
											case  7 :	sLogMsg = QString::asprintf( "       LogPathFile        = %s", (pszLogPathFile     == NULL ? "(null)" : (strlen( pszLogPathFile     ) < 1 ? "(empty)" : pszLogPathFile    )) );     break;
											case  8 :	sLogMsg = QString::asprintf( "       UIVersionString    = %s", (pszUIVersionString == NULL ? "(null)" : (strlen( pszUIVersionString ) < 1 ? "(empty)" : pszUIVersionString)) );     break;
											case  9 :	sLogMsg = QString::asprintf( "       LoadModelFile      = %s", (bLoadModelFile   ? "true" : "false") );		break;
											case 10 :	sLogMsg = QString::asprintf( "       OptionsCSV         = %s", (pszOptionsCSV      == NULL ? "(null)" : (strlen( pszOptionsCSV      ) < 1 ? "(empty)" : sOptsCSV.toLocal8Bit().constData() )) );     break;
											case 11 :	sLogMsg = QString::asprintf( "       ErrorMsg           = %s", (pszErrorMsg        == NULL ? "(null)" : (iErrorMsgLen > 0 ? "(assumed to be initialized)" : "(unused)"    )) );     break;
											case 12 :	sLogMsg = QString::asprintf( "       ErrorMsgLen        = %d", iErrorMsgLen );										break;
											case 13 :	sLogMsg = QString::asprintf( "       DisplayProgress    = %s", (bDisplayProgress ? "true" : "false") );     break;
											case 14 :	sLogMsg = QString::asprintf( "       ResultsSummary     = %s", (pszResultsSummary  == NULL ? "(null)" : (strlen( pszResultsSummary  ) < 1 ? "(empty)" : pszResultsSummary )) );     break;
											case 15 :	sLogMsg = QString::asprintf( "       ResultsSummaryLen  = %d", iResultsSummaryLen );     break;
											case 16 :	sLogMsg = QString::asprintf( "       pProgCallbackFunc  = %s", (pAnalProgCallbackFunc == NULL ? "(null)" : "(assumed to be initialized)") );     break;
											default :	sLogMsg.clear();		break;
										}
										if (!sLogMsg.isEmpty())
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}	}

#ifdef _DEBUG  //VS19 - SAC 10/14/20
	SetOSWrapLogFlag( true );
#else
	SetOSWrapLogFlag( bVerbose );
#endif 
	int iProgressType = (siNumProgressRuns > 1 ? BCM_NRP_Type_Batch : BCM_NRP_Type_Comp);
	// SAC 5/28/15 - callback mechanism - initialize static function pointer
	assert( spAnalProgCallbackFunc == NULL && slAnalysisProgressCallbackRetVal == 0 );
	if (pAnalProgCallbackFunc)
	{	spAnalProgCallbackFunc = pAnalProgCallbackFunc;
		slAnalysisProgressCallbackRetVal = 0;
	}
	sbAllowCallbackAbort = bStoreAllowCallbackAbort;	// SAC 5/24/16

// QT Progress Dialog stuff
#ifdef CM_QTGUI
	QVBoxLayout* pqt_layout = NULL;
	QWidget* pqt_win = NULL;
	QProgressDialog* pqt_progress = NULL;
	if (bDisplayProgress)
	{
		//static QWidget* sqt_win = NULL;
		//static QProgressDialog* sqt_progress = NULL;
	
		pqt_layout = new QVBoxLayout;
	//	QVBoxLayout qt_layout();
		//QWidget*  win = new QWidget;
		//QProgressDialog* progress = new QProgressDialog("Fetching data...", "Cancel", 0, 100);
		assert( sqt_win == NULL && sqt_progress == NULL );
		pqt_win = new QWidget;
		siNumProgressErrors = 0;
		SetProgressMessage( " Initializing", (iProgressType == BCM_NRP_Type_Batch) );
		pqt_progress = new QProgressDialog( sqProgressMsg, "Abort Analysis", 0, 100 );
		// functions setLabelText() and setCancelButtonText() set the texts shown.
	 
	// QProgressBar {
	//     border: 2px solid grey;
	//     border-radius: 5px;
	// }
	//
	// QProgressBar::chunk {
	//     background-color: #05B8CC;
	//     width: 20px;
	// }
	 
	//	QWidget qt_win();
	//	QProgressDialog qt_progress( "Performing Analysis...", "Cancel", 0, 100 );
		pqt_progress->setWindowModality( Qt::WindowModal );
		pqt_layout->addWidget( pqt_progress, Qt::AlignCenter );
		pqt_win->setLayout( pqt_layout );
	// TESTING
		pqt_win->setAttribute(Qt::WA_DeleteOnClose);
	// TESTING
		pqt_progress->setValue( 0 );
		pqt_progress->setMinimumWidth(400);		// SAC 2/18/19
		pqt_win->show();
		sqt_progress = pqt_progress;
		sqt_win = pqt_win;

	//	for (int iPD = 0; iPD < 100; iPD++)
	//	{
	//		sqt_progress->setValue(iPD);
	//		sqt_win->show();
	//	
	//		if (sqt_progress->wasCanceled())
	//			break;
	//		//... copy one file
	////               pause( 2000 );
	//	}
	//	 
	//	sqt_progress->setValue(100);
	//	sqt_win->show();
	}
//#endif
//
//#ifdef CM_QTGUI
							if (!bAbort && bDisplayProgress)
							{	// enum  CECNResProgressSteps   {   CNRP_Init,  CNRP_ModelPrep,  CNRP_PropSizTrn,  CNRP_PropSizSim,  CNRP_StdSizTrn,  CNRP_StdSizSim,  CNRP_PropTrn,  CNRP_PropSim,  CNRP_StdAnnTrn,  CNRP_StdAnnSim,  CNRP_Results,  CNRP_NumSteps };
								//iProgressStep = CNRP_Init;
								iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_Init, 0 /*lModels*/, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
							}
#endif


	// Misc checks

//											 3 : pszSimWeatherPath doesn't exist
//											 4 : pszDHWDLLPath specified, but doesn't exist
		// for most/all above errors:
		//		bAbort = true;

	int iPrevRuleErrs = 0;
	bool bExpectValidResults = true;
   long lRuleRepoRev = 0;     // SAC 12/18/24
	if (bLoadModelFile && !bAbort)
	{
		if (!sBEMBasePathFile.isEmpty())
		{	assert( !sRulesetPathFile.isEmpty() );  // if (re)loading BEMBase, we must also reload ruleset
								if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Initializing BEMBase", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!FileExists( sBEMBasePathFile.toLocal8Bit().constData() ))
			{	sErrMsg = QString::asprintf( "ERROR:  BEMBase (building data model) definitions file not found:  %s", sBEMBasePathFile.toLocal8Bit().constData() );
//											 1 : pszBEMBasePathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 1 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (sRulesetPathFile.isEmpty() || !FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg = QString::asprintf( "ERROR:  BEM ruleset file not found:  %s", (!sRulesetPathFile.isEmpty() ? sRulesetPathFile.toLocal8Bit().constData() : "(not specified)") );
//											 2 : pszRulesetPathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 2 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (!CMX_LoadDataModel( sBEMBasePathFile.toLocal8Bit().constData(), BEMT_CBECC ))	// was: CMX__ReInitBEMProc( sBEMBasePathFile, BEMT_CBECC ))
			{	sErrMsg = QString::asprintf( "ERROR:  BEMBase (building data model) (re)initialization:  %s", sBEMBasePathFile.toLocal8Bit().constData() );
//											31 : Error initializing building model database
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 31 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}
   	
		if (iRetVal == 0 && !sRulesetPathFile.isEmpty())
		{						if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Initializing ruleset", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg = QString::asprintf( "ERROR:  BEM ruleset file not found:  %s", sRulesetPathFile.toLocal8Bit().constData() );
//											 2 : pszRulesetPathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 2 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (!CMX_LoadRuleset( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg = QString::asprintf( "ERROR:  Ruleset loading error encountered:  %s", sRulesetPathFile.toLocal8Bit().constData() );
//											32 : Error loading analysis ruleset
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 32 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}

		if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))	// SAC 10/2/14 - RESET iCodeType based on newly loaded ruleset
		{	if (sLoadedRuleSetID.indexOf( "T24N" ) >= 0 || sLoadedRuleSetID.indexOf( "CA " ) == 0)
				iCodeType = CT_T24N;
			else if (sLoadedRuleSetID.indexOf( "S901G" ) >= 0 ||
						(sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0))
				iCodeType = CT_S901G;
			else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
				iCodeType = CT_ECBC;
			else if (sLoadedRuleSetID.indexOf( "360" ) >= 0)		// SAC 1/30/20
				iCodeType = CT_360;
			else
			{	assert( FALSE );	// what ruleset is this ??
		}	}
		else
		{	assert( FALSE );	// no valid ruleset ID found ?
		}

		if (iRetVal == 0)
		{
			iCID_Proj = BEMPX_GetDBComponentID( "Proj" );
			//
			//	-----  BEMBase & ruleset loaded/initialized  -----
			// 
			if (!sLogPathFile.isEmpty())
			{	if (sLogPathFile.length() > BEMDEF_MAXLOGFILELINE)
				{	sErrMsg = QString::asprintf( "ERROR:  Processing log path/file exceeds maximum length of %d:  %s", BEMDEF_MAXLOGFILELINE, sLogPathFile.toLocal8Bit().constData() );
//											 5 : Invalid project log file name (too long)
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 5 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
				else if (!BEMPX_WriteLogFile( "checking log write", sLogPathFile.toLocal8Bit().constData(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
				{	sErrMsg = QString::asprintf( "ERROR:  Error encountered writing message to log file:  %s", sLogPathFile.toLocal8Bit().constData() );
//											 6 : Error writing to project log file
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 6 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
			}
			if (iRetVal == 0)
			{	// assumes BEMBase cleared out and ruleset re-loaded
				if (sModelPathFile.isEmpty() || !FileExists( sModelPathFile.toLocal8Bit().constData() ))
				{	sErrMsg = QString::asprintf( "ERROR:  Building model (project) file not found:  %s", (!sModelPathFile.isEmpty() ? sModelPathFile.toLocal8Bit().constData() : "(not specified)") );
//											 7 : Building model input/project file not found
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 7 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
								//bool  __declspec(dllexport) __cdecl BEMPX_ReadProjectFile(  const char* fileName, int iFileMode /*bool bIsInputMode*/, bool bRestore=FALSE, bool bResultsOnly=FALSE,
   			else			//    const char* pszLogFileExt=NULL, int iBEMProcIdx=0, long lDBIDVersion=0, int iMaxDBIDSetFailures=0, int* piDBIDSetFailures=NULL, BEMStraightMap* pStraightMap=NULL,        
				{				//    BEMComponentMap* pCompMap=NULL, BEMPropertyMap* pPropMap=NULL, BOOL bSupressAllMessageBoxes=FALSE, int* piObjIdxSetFailures=NULL, QVector<QString>* psaDataSetFailures=NULL );
#ifdef CM_QTGUI
							if (!bAbort && bDisplayProgress)
							{	// enum  CECNResProgressSteps   {   CNRP_Init,  CNRP_ModelPrep,  CNRP_PropSizTrn,  CNRP_PropSizSim,  CNRP_StdSizTrn,  CNRP_StdSizSim,  CNRP_PropTrn,  CNRP_PropSim,  CNRP_StdAnnTrn,  CNRP_StdAnnSim,  CNRP_Results,  CNRP_NumSteps };
								//iProgressStep = CNRP_ModelPrep;
								iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_Read, 0 /*lModels*/, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
							}
#endif

				// SAC 6/28/13 - code to detect (and possibly abort due to) errors encountered reading project file
				   int iBEMErr;
					// enable the UI reporting of all (up to MAX_BEMBASE_DATA_SET_ERRORS) BEMBase project file data setting errors
				   int iaFailedBEMBaseDBIDs[   MAX_BEMBASE_DATA_SET_ERRORS ];
				   int iaFailedBEMBaseObjIdxs[ MAX_BEMBASE_DATA_SET_ERRORS ];  // facilitate more informative error reporting
				   for (iBEMErr=0; iBEMErr<MAX_BEMBASE_DATA_SET_ERRORS; iBEMErr++)
				   {
				      iaFailedBEMBaseDBIDs[iBEMErr] = 0;
				      iaFailedBEMBaseObjIdxs[iBEMErr] = -1;
				   }
				   QStringList saFailedBEMBaseData;  // facilitate more informative error reporting

								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Loading SDD model", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

					bool bKeepLogFileOpen = false;	// SAC 5/20/14
					switch (iLogWritingMode)
					{	case  0 :	bKeepLogFileOpen = false;		break;
						case  1 :	bKeepLogFileOpen = true;		break;
						default :	bKeepLogFileOpen = (bVerbose || bDurationStats || pCompRuleDebugInfo != NULL);		break;
					}
				// SAC 1/28/14 - call local CMX_LoadModel routine to incorporate backward compatibility features
					QStringList saWarningsForUser;	// SAC 7/8/14 - added to track issues (not designated as read failures, but worthy of logging)
					if (CMX_LoadModel( NULL, NULL, sModelPathFile.toLocal8Bit().constData(), MAX_BEMBASE_DATA_SET_ERRORS, iaFailedBEMBaseDBIDs, true /*bSupressAllMsgBoxes*/,	// SAC 5/1/14 - supress msgboxes
												iaFailedBEMBaseObjIdxs, &saFailedBEMBaseData, false /*bLogDurations*/, sLogPathFile.toLocal8Bit().constData(), bKeepLogFileOpen, &saWarningsForUser ) != 0)
					{	// deal with or simply report failure of model file open
						sErrMsg = QString::asprintf( "ERROR:  Error encountered reading building model (project) file:  %s", sModelPathFile.toLocal8Bit().constData() );
//											 8 : Error reading/initializing model input/project file
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 8 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
					}
					else if (!bIgnoreFileReadErrors)
					{	int iNumBEMBaseErrors = 0;
					   for (iBEMErr=0; iBEMErr<MAX_BEMBASE_DATA_SET_ERRORS; iBEMErr++)
						{	if (iaFailedBEMBaseDBIDs[iBEMErr] > 0)
								iNumBEMBaseErrors++;
						}
						if (iNumBEMBaseErrors > 0)
						{	sErrMsg = QString::asprintf( "ERROR:  %d Error(s) encountered reading building model (input/project) file:  %s", iNumBEMBaseErrors, sModelPathFile.toLocal8Bit().constData() );
//												37 : Error(s) encountered reading building model (input/project) file
							ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 37 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
						}
					}
					if (saWarningsForUser.size() > 0)	// SAC 7/8/14 - log file-read issues not designated as failures, but worthy of logging
					{	for (int iFRWIdx=0; iFRWIdx < saWarningsForUser.size(); iFRWIdx++)
							BEMPX_WriteLogFile( saWarningsForUser[iFRWIdx], NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
								if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Back from loading SDD model", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

			      // EnableResearchMode stuff - SAC 02/26/22
				   long lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) );
               assert( (lEnableResearchMode < 1 || lDBID_Proj_EnableResearchMode > 0) );     // if EnableResearchMode CSV option specified, then there should also be a valid EnableResearchMode ResProj property
				   if (lDBID_Proj_EnableResearchMode > 0)
				   {	long lERM;
				   	if (!BEMPX_GetInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ))
				   		lERM = -1;
				   	if (lEnableResearchMode < 1 && lERM > 0.5)
				   		// This file was last SAVED IN RESEARCH MODE, but current INI file does not include research mode enabling setting
				   		BEMPX_WriteLogFile( "Warning: Research mode is selected in this project file but not activated in current analysis.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				   	else if (lERM < -0.5)	// SAC 2/4/16 - only reset EnableResearchMode to INI setting if NOT specified in input file
				         BEMPX_SetBEMData( lDBID_Proj_EnableResearchMode, BEMP_Int, (void*) &lEnableResearchMode, BEMO_User, -1, BEMS_ProgDefault );
				   }

			// ??? evaluate FileOpen rulelist to address backward compatibility issues ???\

				// store certain data only required when project file loaded during analysis
					if (iRetVal == 0)
					{
					   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjFileName", iCID_Proj ), BEMP_QStr, (void*) &sModelFileOnlyWithExt, BEMO_User, 0, BEMS_ProgDefault );
					}
					BEMPX_RefreshLogFile();	// SAC 5/19/14
   	
				//	else
				//	{	bBEMLogFileSet = TRUE;
				//	}
				}
			}
		}

		if (!sErrMsg.isEmpty())
		{
			BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsg.toLocal8Bit().constData() ))
				BEMPX_AddRulesetError( sErrMsg.toLocal8Bit().constData() );	// only log ruleset error if sErrMsg NOT appended onto return error message (pszErrorMsg)
			if (iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
				bAbort = true;
		}
	}
	else if (!bAbort)
	{
		BEMPX_DeleteModels( false /*bIncludingUserModel*/ );   // SAC 3/24/13
		BEMPX_SetActiveModel( 0 );
		BEMPX_ClearRulesetErrors();
		BEMPX_ClearTransformBEMProcMap();	// SAC 3/27/20

		// EnableResearchMode stuff - SAC 02/26/22
		long lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) );
      assert( (lEnableResearchMode < 1 || lDBID_Proj_EnableResearchMode > 0) );     // if EnableResearchMode CSV option specified, then there should also be a valid EnableResearchMode ResProj property
		if (lDBID_Proj_EnableResearchMode > 0)
		{	long lERM;
			if (!BEMPX_GetInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ))
				lERM = -1;
			if (lEnableResearchMode < 1 && lERM > 0.5)
				// The loaded project IS IN RESEARCH MODE, but current INI file does not include research mode enabling setting
				BEMPX_WriteLogFile( "Warning: Research mode is selected in this project but not activated in current analysis.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			else if (lERM < -0.5)	// SAC 2/4/16 - only reset EnableResearchMode to INI setting if NOT specified in input file
		      BEMPX_SetBEMData( lDBID_Proj_EnableResearchMode, BEMP_Int, (void*) &lEnableResearchMode, BEMO_User, -1, BEMS_ProgDefault );
         if (lERM >= 0)    // if ERM specified in project file, then perform analysis w/ that, regardless of INI option - SAC 02/26/22
            lEnableResearchMode = lERM;
		}
   }

	if (!bAbort)
	{  long lDBID_Proj_AllowPropPVBatt = BEMPX_GetDatabaseID( "AllowPropPVBatt", BEMPX_GetDBComponentID( "Proj" ) );  // Use OptionsCSV if defined and not -1, else load from file - SAC 10/25/23
      long lDBID_Proj_AllowStdPV      = BEMPX_GetDatabaseID( "AllowStdPV"     , BEMPX_GetDBComponentID( "Proj" ) );
      long lDBID_Proj_AllowStdBatt    = BEMPX_GetDatabaseID( "AllowStdBatt"   , BEMPX_GetDBComponentID( "Proj" ) );
      if (lDBID_Proj_AllowPropPVBatt > 0)
      {  if (lAllowPropPVBatt != -1)
		      BEMPX_SetBEMData( lDBID_Proj_AllowPropPVBatt, BEMP_Int, (void*) &lAllowPropPVBatt, BEMO_User, -1, BEMS_ProgDefault );
         else
            BEMPX_GetInteger( lDBID_Proj_AllowPropPVBatt, lAllowPropPVBatt, -1 );
      }
      if (lDBID_Proj_AllowStdPV      > 0)
      {  if (lAllowStdPV != -1)
		      BEMPX_SetBEMData( lDBID_Proj_AllowStdPV     , BEMP_Int, (void*) &lAllowStdPV, BEMO_User, -1, BEMS_ProgDefault );
         else
            BEMPX_GetInteger( lDBID_Proj_AllowStdPV     , lAllowStdPV     , -1 );
      }
      if (lDBID_Proj_AllowStdBatt    > 0)
      {  if (lAllowStdBatt != -1)
		      BEMPX_SetBEMData( lDBID_Proj_AllowStdBatt   , BEMP_Int, (void*) &lAllowStdBatt, BEMO_User, -1, BEMS_ProgDefault );
         else
            BEMPX_GetInteger( lDBID_Proj_AllowStdBatt   , lAllowStdBatt   , -1 );
	}  }

		int iRulesetCodeYear = 0;
		if (iRetVal == 0)
		{	int  iBypassOS_all			=	 GetCSVOptionValue( "BypassOpenStudio_all"       ,   0,  saCSVOptions ); 	// SAC 5/20/14
			if (iCodeType == CT_T24N)
			{	iNumBypassItems = 4;
				pbBypassOpenStudio[0]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zp"        ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[1]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zb"        ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[2]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ap"        ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[3]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ab"        ,   0,  saCSVOptions ) > 0);
				plOverrideAutosize[0]	=	 GetCSVOptionValue( "OverrideAutosize_zp"        ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[1]	=	 GetCSVOptionValue( "OverrideAutosize_zb"        ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[2]	=	 GetCSVOptionValue( "OverrideAutosize_ap"        ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[3]	=	 GetCSVOptionValue( "OverrideAutosize_ab"        ,  -1,  saCSVOptions )     ;
				bExpectValidResults = (	!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] &&	// SAC 1/16/15
												!pbBypassOpenStudio[3] && iAnalysisThruStep >= 7);
			}
			else
			{	iNumBypassItems = 10;	// SAC 11/2/16 - fix to ensure that Bypass flags beyond [3] are referenced
				pbBypassOpenStudio[0]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zp"        ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[1]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zb1"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[2]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zb2"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[3]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zb3"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[4]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_zb4"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[5]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ap"        ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[6]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ab1"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[7]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ab2"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[8]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ab3"       ,   0,  saCSVOptions ) > 0);
				pbBypassOpenStudio[9]	=	(iBypassOS_all > 0 || GetCSVOptionValue( "BypassOpenStudio_ab4"       ,   0,  saCSVOptions ) > 0);
				plOverrideAutosize[0]	=	 GetCSVOptionValue( "OverrideAutosize_zp"        ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[1]	=	 GetCSVOptionValue( "OverrideAutosize_zb1"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[2]	=	 GetCSVOptionValue( "OverrideAutosize_zb2"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[3]	=	 GetCSVOptionValue( "OverrideAutosize_zb3"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[4]	=	 GetCSVOptionValue( "OverrideAutosize_zb4"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[5]	=	 GetCSVOptionValue( "OverrideAutosize_ap"        ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[6]	=	 GetCSVOptionValue( "OverrideAutosize_ab1"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[7]	=	 GetCSVOptionValue( "OverrideAutosize_ab2"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[8]	=	 GetCSVOptionValue( "OverrideAutosize_ab3"       ,  -1,  saCSVOptions )     ;
				plOverrideAutosize[9]	=	 GetCSVOptionValue( "OverrideAutosize_ab4"       ,  -1,  saCSVOptions )     ;
				bExpectValidResults = (	!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] &&	!pbBypassOpenStudio[3] &&
												!pbBypassOpenStudio[4] && !pbBypassOpenStudio[5] && !pbBypassOpenStudio[6] && !pbBypassOpenStudio[7] &&
												!pbBypassOpenStudio[8] && !pbBypassOpenStudio[9] && iAnalysisThruStep >= 7);
			}

         // be able to identify RuleRepoRev - initially to distinguish use of CSE19 vs. CSE(.exe) - SAC 12/18/24
         if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RuleRepoRev" ), lRuleRepoRev ))
            lRuleRepoRev = 0;

		   // SAC 11/19/15 - added logic to extract code year out of ruleset label
			if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))	// SAC 10/2/14 - RESET iCodeType based on newly loaded ruleset
			{	int iCdYrIdx = sLoadedRuleSetID.indexOf( " 20" ) + 1;		// SAC 4/25/16 - revised logic to process S901G '-2010' code year properly
				if (iCdYrIdx < 1)
					 iCdYrIdx = sLoadedRuleSetID.indexOf( "20" );
				if (iCdYrIdx >= 0)
				{	iRulesetCodeYear = atoi( sLoadedRuleSetID.mid( iCdYrIdx, 4 ).toLocal8Bit().constData() );
					assert( iRulesetCodeYear >= 2000 );
				}
										if (bVerbose)
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Analysis DLL CodeYear %d / Ruleset CodeYear %d", iDLLCodeYear, iRulesetCodeYear ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
		}

#ifdef CM_QTGUI
							if (!bAbort && bDisplayProgress)
							{	// enum  CECNResProgressSteps   {   CNRP_Init,  CNRP_ModelPrep,  CNRP_PropSizTrn,  CNRP_PropSizSim,  CNRP_StdSizTrn,  CNRP_StdSizSim,  CNRP_PropTrn,  CNRP_PropSim,  CNRP_StdAnnTrn,  CNRP_StdAnnSim,  CNRP_Results,  CNRP_NumSteps };
								//iProgressStep = CNRP_ModelPrep;
								iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_MPrep, BCM_NRP_Model_zp /*lModels*/, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );		// BCM_NRP_Model_zp
							}
#endif

  // SAC 8/20/14 - added check (& fix) for object name violations
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	QString sObjNameViolationMsg;
		int iNumObjNameViolations = BEMPX_CheckObjectNames( (char*) pcCharsNotAllowedInObjNames_CECNonRes, sObjNameViolationMsg, -1 /*iBEMProcIdx*/,
																				FALSE /*bAllowTrailingSpaces*/ );			iNumObjNameViolations;

			long lDBID_ProjFileNameNoExt = BEMPX_GetDatabaseID( "Proj:ProjFileNameNoExt" );		// SAC 12/6/19  - SAC 2/2/20 - ported from Res (Com tic #3157)
			if (lDBID_ProjFileNameNoExt > 0 && !sModelFileOnly.isEmpty())
				BEMPX_SetBEMData( lDBID_ProjFileNameNoExt, BEMP_QStr, (void*) &sModelFileOnly, BEMO_User, 0, BEMS_ProgDefault );
	}

   // added storage of IsBatchProcessing to enable suppression of message boxes within ruleset - SAC 03/19/21
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && lIsBatchProcessing > 0)
   {  long lDBID_IsBatchProcessing = BEMPX_GetDatabaseID( "IsBatchProcessing", iCID_Proj );
      if (lDBID_IsBatchProcessing > 0)
   	   BEMPX_SetBEMData( lDBID_IsBatchProcessing, BEMP_Int, (void*) &lIsBatchProcessing, BEMO_User, 0, BEMS_ProgDefault );     // -> BEMS_ProgDefault - SAC 03/25/21
   }

   // storage of CUACReportID to enable ruleset access of CUAC analysis indicator - SAC 08/19/22
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && iCUACReportID > 0)
   {  long lDBID_CUACReportID = BEMPX_GetDatabaseID( "CUACReportID", iCID_Proj );
      if (lDBID_CUACReportID > 0)
   	   BEMPX_SetBEMData( lDBID_CUACReportID, BEMP_Int, (void*) &iCUACReportID, BEMO_User, 0, BEMS_ProgDefault ); 
   }

   // added stuff related to CustomMeterOption - CSVOption will override what is in project file
   bool bCustomMeterResultsStored = false;
   if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {  long lDBID_CustomMeterOption = BEMPX_GetDatabaseID( "CustomMeterOption", iCID_Proj );
      if (lDBID_CustomMeterOption > 0 && iCustomMeterOption >= 0)
   	   BEMPX_SetBEMData( lDBID_CustomMeterOption, BEMP_Int, (void*) &iCustomMeterOption, BEMO_User, 0, BEMS_ProgDefault );     // ??? store as user-defined vs. prog default ???
      else if (lDBID_CustomMeterOption > 0)
         BEMPX_GetInteger( lDBID_CustomMeterOption, iCustomMeterOption, -1 );
   }

  // SAC 8/23/18 - moved up from below initial defaulting for newly opened model to ensure certain properties (CSE_Name) are defauted before being retrieved/referenced
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && bLoadModelFile)
   	// SAC 4/4/14 - added call to defaulting stuff for models just loaded to ensure all defaults present prior to PolyLp generation
		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

   bool bPerformFullCSESim = false;    // SAC 10/26/21 (MFam)
   bool bPerformCSEDHWSim = false;     // SAC 03/07/22 (MFam)
   if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {  long lSimMFamUnits = 0;
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "SimMFamUnits", iCID_Proj ), lSimMFamUnits );
//BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - setting bPerformFullCSESim, Proj:SimMFamUnits = %d", lSimMFamUnits ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      bPerformFullCSESim = (lSimMFamUnits > 0);
      long lSimResDHW = 0;
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "SimResDHW", iCID_Proj ), lSimResDHW );
      bPerformCSEDHWSim = (lSimResDHW > 0);
   }
   bool bPerformComSim = false;        // SAC 10/29/21 (MFam)
   if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {  long lSimComFlag = 0;
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "SimComFlag", iCID_Proj ), lSimComFlag, 1 /*default*/ );
      bPerformComSim = (lSimComFlag > 0);
   }

   QString sBypassCompRptMsg;    // SAC 12/01/22
   BEMPX_GetString( BEMPX_GetDatabaseID( "BypassCompRptMsg", iCID_Proj ), sBypassCompRptMsg );

// SAC 6/12/15 - added new check for duplicate object names
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && bPerformDupObjNameCheck)
	{	if (BEMPX_CheckForDuplicateObjectNames( pszAnalErrMsg, NRES_AnalErrMsg_Len, TRUE /*bWriteErrorsToLog*/, TRUE /*bSupressAllMessageBoxes*/ ) > 0)
		{	sErrMsg = pszAnalErrMsg;
//											53 : Input model contains one or more objects with the same name
			ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 53 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
	}	}

  // SAC 3/22/14 - added check for all compulsory inputs PRIOR to any/all other processing
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	CMX_AdjustDataModelForGeometryInpType_CECNonRes();	// SAC 3/23/14 - ported from UI - ensures InputClass for each property associated w/ geometry input is properly defined
		iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
		BOOL bCompulsoryCheckOK;
		if (!bBypassInputChecks)
		{						if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Checking SDD model for Compulsory inputs", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			bCompulsoryCheckOK = BEMPX_PerformErrorCheck( FALSE /*bRequireRequiredData=TRUE*/, FALSE /*bReportSimDefaultErrors=TRUE*/, FALSE /*bPerformReqdClassCheck=TRUE*/,
																		 FALSE /*bPostRangeWarnings=FALSE*/, (bIgnoreFileReadErrors ? 0 : BEM_UserInpChk_DisallowNotInput) /*iUserInpChk*/ );
			if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs && iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
			{
//											11 : Error(s) encountered performing required data & numeric range checks
				iRetVal = (iRetVal > 0 ? iRetVal : 11);		// do abort (after ALL checks)
				bAbort = true;
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
	}	}

	long lHVACAutoSizing=0;		// SAC 2/17/20 - load to alter order to eval of rl_REPORT rules vs. simulation runtime
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
		BEMPX_GetInteger( BEMPX_GetDatabaseID( "HVACAutoSizing", iCID_Proj ), lHVACAutoSizing );

  // SAC 5/16/14 - added CSVOptions-based RunTitle specification
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && !sRunTitle.isEmpty())
	   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunTitle", iCID_Proj ), BEMP_QStr, (void*) &sRunTitle, BEMO_User );

  // SAC 12/19/13 - added mechanism to ensure report watermarked for non-compliance when certain developer options flags are set by user (not defaulted)
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	int iDOOPIdx = -1;		double fDOOPVal;		int iLastDevOptClassIdx = -1;
		while (saDevOptsObjProps[++iDOOPIdx].length() > 1)
		{	long lDBID = BEMPX_GetDatabaseID( saDevOptsObjProps[iDOOPIdx] );
			if (lDBID < 1)
			{	assert( FALSE ); // what to do here ???
			}
			else
			{	int iCID = BEMPX_GetClassID( lDBID );
				if (iCID < 1)
				{	assert( FALSE ); // what to do here ???
				}
				else
				{	int iNumObjs = BEMPX_GetNumObjects( iCID );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
					for (int iDOO=0; iDOO < iNumObjs; iDOO++)
					{	int iDOStatus = BEMPX_GetDataStatus( lDBID, iDOO );  // , BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
						BEMPX_GetFloat( lDBID, fDOOPVal, faDevOptsPropOKVals[iDOOPIdx]-100, -1, iDOO );		// SAC 5/13/14 - added check so that DevOpt value could be USER defined but still OK for valid analysis
						if (iDOStatus > BEMS_RuleDefined && !WithinMargin( fDOOPVal, faDevOptsPropOKVals[iDOOPIdx], 0.01 ))
						{	int iColonIdx = saDevOptsObjProps[iDOOPIdx].indexOf(':');		assert( iColonIdx > 0 );
							QString sDOObjName, sTemp;
							BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID ), sDOObjName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iDOO );
							if (iColonIdx < 1)
								sTemp = QString::asprintf( "\n          %s", saDevOptsObjProps[iDOOPIdx].toLocal8Bit().constData() );
							else
								sTemp = QString::asprintf( "\n          %s '%s' %s", saDevOptsObjProps[iDOOPIdx].left(iColonIdx).toLocal8Bit().constData(), sDOObjName.toLocal8Bit().constData(), 
																						saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 ).toLocal8Bit().constData() );
							sDevOptsNotDefaulted += sTemp;
						// SAC 7/6/16 - added for improved user prompting
							if (!sDevOptsNotDefaultedAbbrev.isEmpty())
								sDevOptsNotDefaultedAbbrev += ", ";
							if (iColonIdx < 1)
								sDevOptsNotDefaultedAbbrev += saDevOptsObjProps[iDOOPIdx];
							else if (iLastDevOptClassIdx == iCID)
								sDevOptsNotDefaultedAbbrev += saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 );
							else // if (iLastDevOptClassIdx != iCID)
							{	if (iCID==1)
									sTemp = QString::asprintf( "project %s", saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 ).toLocal8Bit().constData() );
								else
									sTemp = QString::asprintf( "%s %s", saDevOptsObjProps[iDOOPIdx].left(iColonIdx).toLocal8Bit().constData(), 
																	saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 ).toLocal8Bit().constData() );
								sDevOptsNotDefaultedAbbrev += sTemp;
							}
							iLastDevOptClassIdx = iCID;
			}	}	}	}
		}
		if (!sDevOptsNotDefaulted.isEmpty())
		{	QString sDevOptsNotDefaultedMsg = "Warning:  The following developer options must be defaulted (not specified by the user) in order to perform a valid compliance analysis:" + sDevOptsNotDefaulted;
			BEMPX_WriteLogFile( sDevOptsNotDefaultedMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         if (iCUACReportID > 0)
            sCUACInvalidMsg = "Developer options specified";      // SAC 01/02/25
		}
	}

   // Update sSimWeatherPath to account for research mode substitution - SAC 08/27/24
   if (!bAbort && !BEMPX_AbortRuleEvaluation() && !sSimWeatherPath.isEmpty())
   {  QString sSimWeatherPathSub, sWthrPathSub;
      long lERM, lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) ),
                 lDBID_Proj_WeatherPathSub     = BEMPX_GetDatabaseID( "WeatherPathSub",     BEMPX_GetDBComponentID( "Proj" ) );
      if (lDBID_Proj_EnableResearchMode > 0 && lDBID_Proj_WeatherPathSub > 0 &&
          BEMPX_GetInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ) && lERM > 0 &&
          BEMPX_GetString(  lDBID_Proj_WeatherPathSub, sWthrPathSub ) && !sWthrPathSub.isEmpty())
      {  // replace right-most portion of sSimWeatherPath with sWthrPathSub, and confirm that it is a valid path
         int iPathLenMinusLastPart = sSimWeatherPath.lastIndexOf( '\\', sSimWeatherPath.length()-2 );
         if (iPathLenMinusLastPart > 0)
         {  QString sTempSimWeatherPath = sSimWeatherPath.left( iPathLenMinusLastPart+1 );
            sTempSimWeatherPath += sWthrPathSub;
            sTempSimWeatherPath += '\\';
                  // BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - iPathLenMinusLastPart: %d / sSimWeatherPath:  %s / sTempSimWeatherPath:  %s", iPathLenMinusLastPart, sSimWeatherPath.toLocal8Bit().constData(), sTempSimWeatherPath.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            if (DirectoryExists( sTempSimWeatherPath ))
            {        BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Replacing weather file path:  %s  -->>  %s", sSimWeatherPath.toLocal8Bit().constData(), sTempSimWeatherPath.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               sSimWeatherPath = sTempSimWeatherPath;
      }  }  }
   }

	QString sCSEEXEPath			= sCompMgrDLLPath + "CSE\\";		// SAC 5/24/16
	QString sCSEWeatherPath		= sSimWeatherPath;
	QString qsCSEName="CSE";
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{
	// Setup CSE executable filename based on setting from ruleset - SAC 12/17/17
		if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CSEName" ), qsCSEName ) || qsCSEName.isEmpty())
			qsCSEName = "CSE";
					//	#ifdef _DEBUG
					//			sCSEexe      = sCSEEXEPath + "csed.exe";
					//	#else
					//			sCSEexe      = sCSEEXEPath + "cse.exe";
					//	#endif
		sCSEexe = sCSEEXEPath + qsCSEName + ".exe";
		//if (!FileExists( sCSEexe.toLocal8Bit().constData() ))
		//{	sErrorMsg = "ERROR:  The following required file(s) were not found:\n   " + sCSEexe;
		//	iRetVal = BEMAnal_CECRes_MissingFiles;
	}	//}

// Check fairly wide variety of file hashes for supporting files - some required, some not - if inconcistencies found, log them and turn OFF report signature use
#define  MAX_FileHashID  32      // 50->32 - SAC 04/14/21
	int iNumFileHashErrs = 0;
	if (iCodeType == CT_S901G || iCodeType == CT_ECBC)
		bBypassValidFileChecks = true;	// SAC 12/23/14 - turn OFF file hash checks for S901G analyses
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	if (bBypassValidFileChecks)
			BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing file validity checks", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		else
		{	QString sCSE_DHWUseIncFile;
			BEMPX_GetString( BEMPX_GetDatabaseID( "CSE_DHWUseIncFile", iCID_Proj ), sCSE_DHWUseIncFile );   // SAC 03/19/21
			if (sCSE_DHWUseIncFile.isEmpty())
				sCSE_DHWUseIncFile = "DHWDU2.txt"; 
         QString sFHPathFile, sFHErrMsg; 
			bool bLogEachFileHashError = (bVerbose);
			bool bRequiredForCodeYear = true;
			for (long iFHID=1; (iRetVal == 0 && iFHID <= MAX_FileHashID); iFHID++)
			{	bRequiredForCodeYear = true;
			// SAC 1/14/17 - updated file hash table for 2016/19 analysis (using new open source exes)
				switch (iFHID)
				{	case  1 :	BEMPX_GetBEMBaseFile( sFHPathFile );                              bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case  2 :	BEMPX_GetBEMBaseFile( sFHPathFile );                              bRequiredForCodeYear = (iDLLCodeYear == 2022);		break;
					case  3 :	sFHPathFile = sCompMgrDLLPath + "BEMCmpMgr22c.dll";               bRequiredForCodeYear = (iDLLCodeYear == 2022);		break;   // SAC 3/6/14 - revised ALL to reference more specific paths
					case  4 :	sFHPathFile = sCompMgrDLLPath + "BEMProc22c.dll";                 bRequiredForCodeYear = (iDLLCodeYear == 2022);		break;
					case  5 :	sFHPathFile = sCompMgrDLLPath + "OS_Wrap22.dll";                  bRequiredForCodeYear = (iDLLCodeYear == 2022);		break;
					case  6 :	sFHPathFile = sCompMgrDLLPath + "libcrypto-1_1-x64.dll";  	      bRequiredForCodeYear = false;  							break;	// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
					case  7 :	sFHPathFile = sCompMgrDLLPath + "libssl-1_1-x64.dll"; 			   bRequiredForCodeYear = false;  							break;	// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
					case  8 :	sFHPathFile = sCompMgrDLLPath + "openstudiolib.dll";              break;
					case  9 :	sFHPathFile = sCompMgrDLLPath + "Qt5Cored.dll";                   break;  // SAC 12/3/14 - revised for Qt5
					case 10 :	sFHPathFile = sCompMgrDLLPath + "Qt5Guid.dll";                    break;
					case 11 :	sFHPathFile = sCompMgrDLLPath + "Qt5Networkd.dll";                break;
					case 12 :	sFHPathFile = sCompMgrDLLPath + "Qt5Sqld.dll";                    break;
					case 13 :	sFHPathFile = sCompMgrDLLPath + "Qt5Widgetsd.dll";                break;
					case 14 :	sFHPathFile = sCompMgrDLLPath + "Qt5Xmld.dll";                    break;
					case 15 :	sFHPathFile = sCompMgrDLLPath + "Qt5Core.dll";                    break;
					case 16 :   sFHPathFile = sCompMgrDLLPath + "Qt5Gui.dll";                     break;
					case 17 :   sFHPathFile = sCompMgrDLLPath + "Qt5Network.dll";                 break;
					case 18 :   sFHPathFile = sCompMgrDLLPath + "Qt5Sql.dll";                     break;
					case 19 :   sFHPathFile = sCompMgrDLLPath + "Qt5Widgets.dll";                 break;
					case 20 :   sFHPathFile = sCompMgrDLLPath + "Qt5Xml.dll";                     break;
					case 21 :   sFHPathFile = sEPlusPath + "EnergyPlus.exe";          				break;
					case 22 :   sFHPathFile = sEPlusPath + "Energy+.idd";             				break;
					case 23 :	sFHPathFile = sEPlusPath + "energyplusapi.dll";        				break;
					case 24 :	sFHPathFile = sEPlusPath + "EPMacro.exe";               				break;
					case 25 :	sFHPathFile = sEPlusPath + "ExpandObjects.exe";        				break;
					case 26 :	sFHPathFile = sEPlusPath + "ReadVarsESO.exe";	        				break;
					case 27 :	sFHPathFile = sCompMgrDLLPath + "BEMCmpMgr19c.dll";               bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 28 :	sFHPathFile = sCompMgrDLLPath + "BEMProc19c.dll";                 bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 29 :	sFHPathFile = sCompMgrDLLPath + "OS_Wrap19.dll";                  bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 30 :	sFHPathFile = sCSEEXEPath + "cse19d.exe";	             				break;	// SAC 5/24/16
					case 31 :	if (lRuleRepoRev >= 8681)     // SAC 12/18/24
                                 sFHPathFile = sCSEEXEPath + "cse.exe";
                           else  sFHPathFile = sCSEEXEPath + "cse19.exe";	       				break;
					case 32 :	sFHPathFile = sCSEEXEPath + sCSE_DHWUseIncFile;	     					break;     
					default :			assert( FALSE );                                      		break;
				}
				if (!bRequiredForCodeYear)
				{	// do nothing here - the selected DLL should not be used w/ the CODEYEAR* setting compiled into this DLL
				}
				else if (sFHPathFile.isEmpty() || !FileExists( sFHPathFile.toLocal8Bit().constData() ))
				{	// DO NOTHING - some files expected to be missing - others will prevent success when missing...
										if (bVerbose &&	// SAC 3/6/14 - added verbose logging of this condition
#ifdef _DEBUG
												((iFHID < 15 || iFHID > 20) && iFHID != 31))
#else
												((iFHID <  9 || iFHID > 14) && iFHID != 30))
#endif
										{	if (sFHPathFile.isEmpty())
												sLogMsg = QString::asprintf( "    File to perform hash check on not specified (iFHID = %d)", iFHID );
											else
												sLogMsg = QString::asprintf( "    File to perform hash check on missing (iFHID = %d):  %s", iFHID, sFHPathFile.toLocal8Bit().constData() );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
				}
				else
				{   char pHashBuffer[65];
			// check vareity of support file hashes - SAC 9/14/13
					int iSHA256_RetVal = ComputeSHA256_File( sFHPathFile.toLocal8Bit().constData(), pHashBuffer, 65 );
					if (iSHA256_RetVal != 0)
					{	bSendRptSignature	= false;			iNumFileHashErrs++;
						if (bLogEachFileHashError)
							BEMPX_WriteLogFile( QString::asprintf( "Error computing file hash (analysis continuing w/ report signature disabled) - ComputeSHA256_File() returned %d for file:  %s", iSHA256_RetVal, sFHPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
					else
					{	long lFileHashStatus = 0;
					   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "FileHashID"     , iCID_Proj ), BEMP_Int, (void*) &iFHID     , BEMO_User, 0, BEMS_ProgDefault );
					   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "FileHashToCheck", iCID_Proj ), BEMP_Str, (void*) pHashBuffer, BEMO_User, 0, BEMS_ProgDefault );
						int iFHRetVal = LocalEvaluateRuleset( sFHErrMsg, 48 /*value doesn't matter - not returned*/, "rl_FILEHASHES",	bVerbose, pCompRuleDebugInfo );		// file hash checking
						if (iFHRetVal > 0)
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
								BEMPX_WriteLogFile( QString::asprintf( "Error evaluating file hash checking rules (analysis continuing w/ report signature disabled) - for file:  %s", sFHPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
						else if (iFHRetVal == 0 && !BEMPX_GetInteger( BEMPX_GetDatabaseID( "FileHashStatus", iCID_Proj ), lFileHashStatus ))
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
								BEMPX_WriteLogFile( QString::asprintf( "    File hash check error - invalid Proj:FileHashStatus (%ld) (analysis continuing w/ report signature disabled) - for file:  %s", lFileHashStatus, sFHPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
						else if (iFHRetVal == 0 && lFileHashStatus != 0)
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
								BEMPX_WriteLogFile( QString::asprintf( "    File hash check error - failed consistency check (%ld) (analysis continuing w/ report signature disabled) - for file:  %s", lFileHashStatus, sFHPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
						else if (bVerbose)
						{	if (bLogEachFileHashError)
								BEMPX_WriteLogFile( QString::asprintf( "    File hash check passed for file:  %s", sFHPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
				}	}
			}
			if (iNumFileHashErrs > 0 && !bLogEachFileHashError)
				BEMPX_WriteLogFile( QString::asprintf( "   %d file hash check(s) failed on executable and/or analysis support files (analysis continuing w/ report signature disabled)", iNumFileHashErrs ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashID"     , iCID_Proj ), iError );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashToCheck", iCID_Proj ), iError );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashStatus" , iCID_Proj ), iError );
         if (iNumFileHashErrs > 0 && iCUACReportID > 0 && sCUACInvalidMsg.isEmpty())
            sCUACInvalidMsg = QString::asprintf( "%d file hash check(s) failed", iNumFileHashErrs );      // SAC 01/02/25
		}
		BEMPX_RefreshLogFile();	// SAC 5/19/14
	}

// Setup array of model reports to be output during analysis
	QVector<QString> saModelReportOptions;
	long lDBID_Proj_RuleReportType = 0;
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	// load array of possible enumerations (report types)
		lDBID_Proj_RuleReportType = BEMPX_GetDatabaseID( "RuleReportType", iCID_Proj );						assert( lDBID_Proj_RuleReportType > 0 );
		int iNumSyms;		long iSymValue;
		QVector<QString> saRuleReportTypeEnums;
		//CArray<BEMSymbol*, BEMSymbol*>* pSymArray = 
		BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, lDBID_Proj_RuleReportType );
		if (!pSymDepSet)
		{	assert( FALSE );
		}
		else
		{	for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
			{	QString str;
				int isdRetVal = BEMPX_GetSymbolData( iSymValue, str, pSymDepSet, iSymIdx );
				if (str.length() > 0)
					saRuleReportTypeEnums.push_back( str );
		}	}

		// check for occurrence of report types in CSV options passed into analysis routine
		for (int iRptOpt=0; iRptOpt < saRuleReportTypeEnums.size(); iRptOpt++)
		{	if (bProduceALLModelReports || GetCSVOptionValue( saRuleReportTypeEnums[iRptOpt].toLocal8Bit().constData(), 0, saCSVOptions ) > 0)
				// add this report type to cause generation of model reports
				saModelReportOptions.push_back( saRuleReportTypeEnums[iRptOpt] );
		}
	}
	
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	sErrMsg.clear();
		if (sProcessingPath.length() > (_MAX_PATH - std::max( (sModelFileOnly.length() + 20),		// sPFB + 20  used to represent the max length likely used for file appended to run path
																						38 )))										// 38 => length of probable max OS/E+ processing path addition:  'ModelToIdf\EnergyPlus-0\eplusout.audit'
		{	sErrMsg = QString::asprintf( "Error: Analysis processing path too long:  ", sProcessingPath.toLocal8Bit().constData() );
//											14 : Error encountered initializing weather file locations and/or names
			ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 14 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
		}
		else
		{	if (!DirectoryExists( sProcessingPath ))
				CreateAndChangeDirectory( sProcessingPath.toLocal8Bit().constData(), FALSE );
			if (!DirectoryExists( sProcessingPath ))
			{	sErrMsg = QString::asprintf( "Error: Unable to create or access the analysis processing directory:  ", sProcessingPath.toLocal8Bit().constData() );
//												15 : Error creating or accessing the analysis processing directory
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 15 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}
	}

   // Make changes to address MFam dwelling/common interior surfaces - SAC 01/31/24
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	long lIntSurfModelMthd=0;
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResProj:IntSurfModelMthd" ), lIntSurfModelMthd ) && lIntSurfModelMthd > 0)
		{  int iSetupMFamIntSurfsRetVal = LocalEvaluateRuleset( sErrMsg, 97, "SetupMFamInteriorSurfaces", bVerbose, pCompRuleDebugInfo );  
                           //											97	: Error evaluating SetupMFamInteriorSurfaces rules
         if (iSetupMFamIntSurfsRetVal > 0)
            iRetVal = iSetupMFamIntSurfsRetVal;
   }  }

   // Generate PolyLp objects based on 2D geometry inputs (for applicable projects)
	int iCID_PolyLp = (!bAbort && !BEMPX_AbortRuleEvaluation()) ? BEMPX_GetDBComponentID( "PolyLp" ) : -1;
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	long lIsDetailedGeom=1;
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "IsDetailedGeometry", iCID_Proj ), lIsDetailedGeom ) && lIsDetailedGeom == 0)
		{	// first make sure ruleset's GeomIDs are valid
			QString sCr8PolyLpErrMsg;
			if (!BEMPX_InitGeometryIDs( sCr8PolyLpErrMsg ))
			{	if (sCr8PolyLpErrMsg.isEmpty())
					sErrMsg = "ERROR:  Building geometry DBID initialization failed";
				else
					sErrMsg = QString::asprintf( "ERROR:  Building geometry DBID initialization failed:  %s", sCr8PolyLpErrMsg.toLocal8Bit().constData() );
//											43 : Error encountered initializing building geometry DBIDs
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 43 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
			else
			{	// start by deleting ALL existing PolyLp objects
				int iNumPolyLps = BEMPX_GetNumObjects( iCID_PolyLp /*, BEMO_User, iBEMProcIdx*/ );
				if (iNumPolyLps > 0)
				{	sLogMsg = QString::asprintf( "Warning:  Simplified geometry model includes %d PolyLp objects (expecting none)", iNumPolyLps );			assert( FALSE );  // shouldn't ever get here unless user model includes PolyLp objects
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				for (int iDelObj = iNumPolyLps-1; iDelObj >= 0; iDelObj--)
				{	BEMObject* pObj = BEMPX_GetObjectByClass( iCID_PolyLp, iError, iDelObj /*, BEMO_User, iBEMProcIdx*/ );
					if (pObj && iError == 0)
						BEMPX_DeleteObject( pObj /*, iBEMProcIdx*/ );
				}
				long lNumWinsHavingShades;
																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail-noPolys");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}
				// and then create the new PolyLp objects....
				int iCr8PolyLpRetVal = CMX_GeneratePolyLoops_CECNonRes( bVerbose, bStoreBEMDetails, bSilent, sCr8PolyLpErrMsg );
				if (iCr8PolyLpRetVal < 0)
				{
					sErrMsg = QString::asprintf( "%s  - Unable to generate building geometry for simulation (return code %d)", sCr8PolyLpErrMsg.toLocal8Bit().constData(), iCr8PolyLpRetVal );
//												42 : Error encountered in creating building geometry
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 42 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
				else if (!bAbort && !BEMPX_AbortRuleEvaluation() && BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumWinsHavingShades", iCID_Proj ), lNumWinsHavingShades ) && lNumWinsHavingShades > 0)
					// RE-default model if window shades are to be generated, to ensure that all PolyLp obejcts are fully defaulted
					DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );
																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail-postPolys");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}
			}
	}	}

	// SAC 12/10/14 - window shade generation
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	long lNumWinsHavingShades=0;
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumWinsHavingShades", iCID_Proj ), lNumWinsHavingShades ) && lNumWinsHavingShades > 0)
		{						if (bVerbose)
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Generating shades for %d model windows", lNumWinsHavingShades ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			QString sGenWinShadesErrMsg;
			if (!BEMPX_InitGeometryIDs( sGenWinShadesErrMsg ))
			{	if (sGenWinShadesErrMsg.isEmpty())
					sErrMsg = "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades)";
				else
					sErrMsg = QString::asprintf( "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades):  %s", sGenWinShadesErrMsg.toLocal8Bit().constData() );
//											43 : Error encountered initializing building geometry DBIDs
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 43 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
			else
			{
		// before further processing, check all ExtWalls w/ window shades for overlapping windows/doors
				int iWinDoorOverlaps = CMX_WindowDoorOverlaps_CECNonRes( bVerbose, bStoreBEMDetails, bSilent, sGenWinShadesErrMsg );
				if (iWinDoorOverlaps > 0)
				{	sErrMsg = QString::asprintf( "ERROR:  Window(s) and/or Door(s) are overlapping on %d ExtWalls with window shades defined", iWinDoorOverlaps );
//											51 : Window(s) and/or Door(s) are overlapping on ExtWalls with window shades defined
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 51 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
				else if (!sGenWinShadesErrMsg.isEmpty())
				{	sErrMsg = QString::asprintf( "%s  - Checking for window/door overlaps", sGenWinShadesErrMsg.toLocal8Bit().constData() );
//											43 : Error encountered initializing building geometry DBIDs
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 43 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
				else
				{
			// for all code types to date (T24N & S901G) certain ExtShdgObjs should be deleted BEFORE generation of window shades based on simplified window shade inputs
					long lIsDetailedGeom=1;
					BEMPX_GetInteger( BEMPX_GetDatabaseID( "IsDetailedGeometry", iCID_Proj ), lIsDetailedGeom );
					int iCID_ExtShdgObj = BEMPX_GetDBComponentID( "ExtShdgObj" );
					long lApplyStdShdg, lDBID_ExtShdgObj_ApplyStdShdg = BEMPX_GetDatabaseID( "ApplyStdShdg", iCID_ExtShdgObj );			assert( lDBID_ExtShdgObj_ApplyStdShdg > 0 );
					int iNumShds = BEMPX_GetNumObjects( iCID_ExtShdgObj );
					for (int iShd = iNumShds-1; iShd >= 0; iShd--)
					{	BEMObject* pShdObj = BEMPX_GetObjectByClass( iCID_ExtShdgObj, iError, iShd );
						BEMPX_GetInteger( lDBID_ExtShdgObj_ApplyStdShdg, lApplyStdShdg, 0, -1, iShd );
						if (pShdObj && ( ( iCodeType == CT_T24N  && ( lIsDetailedGeom == 0 || lApplyStdShdg == 1 || (	pShdObj->getParent() && pShdObj->getParent()->getClass() &&
																																						pShdObj->getParent()->getClass()->get1BEMClassIdx() == iCID_Proj ))) ||
											  ( iCodeType != CT_T24N  && ( lIsDetailedGeom == 0 || lApplyStdShdg == 1       )) ))
							BEMPX_DeleteObject( pShdObj /*, int iBEMProcIdx=-1*/ );
					}

																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail-preWinShades");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}
					int iGenWinShadesRetVal = CMX_GenerateWindowShades_CECNonRes( bVerbose, bStoreBEMDetails, bSilent, sGenWinShadesErrMsg );
					if (iGenWinShadesRetVal < 0)
					{
						sErrMsg = QString::asprintf( "%s  - Unable to generate window shade (return code %d)", sGenWinShadesErrMsg.toLocal8Bit().constData(), iGenWinShadesRetVal );
//													47 : Error encountered in generating window shades
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 47 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
					}
																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail-postWinShades");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}
			}	}
	}	}

   // classes to IGNORE when writing AnalysisResults XML file (added) - SAC 02/07/22 (tic #3345)
   int iAnalysisResultsXML_NumClassIDsToIgnore = 0;
   int iAnalysisResultsXML_ClassIDsToIgnore[5] = { 0, 0, 0, 0, 0 };
   if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {  iAnalysisResultsXML_ClassIDsToIgnore[0] = iCID_PolyLp;
      iAnalysisResultsXML_ClassIDsToIgnore[1] = BEMPX_GetDBComponentID( "SchDay" );
      iAnalysisResultsXML_ClassIDsToIgnore[2] = BEMPX_GetDBComponentID( "SchWeek" );
      iAnalysisResultsXML_ClassIDsToIgnore[3] = BEMPX_GetDBComponentID( "Sch" );
      iAnalysisResultsXML_NumClassIDsToIgnore = 4;
   }

	if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {	// moved defaulting stuff to subordinate routine to enable multiple calls
		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

	// SAC 10/3/14 - mod to delete any EUseSummary objects from user model to avoid having them written to the results' user model
		int iNumEUseSUmObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ) );
		for (int iEUSidx=iNumEUseSUmObjs-1; iEUSidx >= 0; iEUSidx--)
		{	BEMObject* pEUSObj = BEMPX_GetObjectByClass( BEMPX_GetDBComponentID( "EUseSummary" ), iError, iEUSidx );			assert( pEUSObj );
			if (pEUSObj)
				BEMPX_DeleteObject( pEUSObj );
		}
	}

	if (!bAbort && !BEMPX_AbortRuleEvaluation())		// SAC 2/1/20 - apply any AnalysisActions flagged for application LoadModel_AfterDefaulting
			MidAnalysis_ApplyAnalysisActionToDatabase( BEMAnalActPhase_LoadModel, BEMAnalActWhen_LoadModel_AfterDefaulting, sErrMsg, bAbort, iRetVal,
																		77 /*iErrID*/, bVerbose, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );	// SAC 2/20/20
//											77 : Error applying AnalysisAction(s) to building model
//			QString qsApplyAnalActError;
//			int iApplyAnalActRetVal = BEMPX_ApplyAnalysisActionToDatabase( BEMAnalActPhase_LoadModel, BEMAnalActWhen_LoadModel_AfterDefaulting, qsApplyAnalActError, bVerbose );		// SAC 1/30/20
//			if (iApplyAnalActRetVal > 0)
//				qsApplyAnalActError = QString( "      %1 AnalysisAction(s) successfully applied to building model: LoadModel / BeforeDefaulting" ).arg( QString::number(iApplyAnalActRetVal) );
//			else if (!qsApplyAnalActError.isEmpty())
//			{	sErrMsg = qsApplyAnalActError;
////											77 : Error applying AnalysisAction(s) to building model
//				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 77 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
//			}
//			if (!qsApplyAnalActError.isEmpty())
//				BEMPX_WriteLogFile( qsApplyAnalActError, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	if (!bAbort && !sXMLResultsFileName.isEmpty() && FileExists( sXMLResultsFileName ))
	{	sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
	                "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Abort' to abort the %s.", "analysis results XML", sXMLResultsFileName.toLocal8Bit().constData(), "analysis" );
		if (!OKToWriteOrDeleteFile( sXMLResultsFileName.toLocal8Bit().constData(), sMsg ))
		{	sErrMsg = QString::asprintf( "Analysis aborting - user chose not to overwrite analysis results XML file:  %s", sXMLResultsFileName.toLocal8Bit().constData() );
//											15 : Error creating or accessing the analysis processing directory
			ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 15 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
	}	}
	BEMXMLWriter xmlResultsFile( ((!bAbort && !sXMLResultsFileName.isEmpty()) ? (const char*) sXMLResultsFileName.toLocal8Bit().constData() : NULL) );
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && !sXMLResultsFileName.isEmpty())
	{							if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Writing user input to analysis results XML", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		// SAC 4/16/14 - modified call to WriteModel() to cause only valid INPUTs to be written to user input model
		BOOL bXMLInputWriteOK = xmlResultsFile.WriteModel( FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, "User Input" /*pszModelName*/, -1 /*iBEMProcIdx*/, true /*bOnlyValidInputs*/ );		assert( bXMLInputWriteOK );
	}

   // finish defining output NRCC/LMCC XML report filename - SAC 08/24/22 (LMCC)
   long lIsLowRiseMFam=0, lDBID_IsLowRiseMFam = BEMPX_GetDatabaseID( "IsLowRiseMFam", iCID_Proj );
   QString qsSchemaXMLFileDescrip;
   if (iRulesetCodeYear >= 2022 && lDBID_IsLowRiseMFam > 0 && BEMPX_GetInteger( lDBID_IsLowRiseMFam, lIsLowRiseMFam ) && lIsLowRiseMFam > 0)
   {  sNRCCXMLFileName   += " - LMCCPRF.xml";     // replaced NRCC w/ " - LMCCPRF.xml";  - SAC 10/17/22
      qsSchemaXMLFileDescrip = "LMCCPRF report XML";
   }
   else
   {  sNRCCXMLFileName   += " - NRCCPRF.xml";
      qsSchemaXMLFileDescrip = "NRCCPRF report XML";
   }
	iNRCCXMLClassID = (iCodeType != CT_T24N ? 0 : BEMPX_GetDBComponentID("nrccComplianceDocumentPackage"));
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && iNRCCXMLClassID > 0 && !sNRCCXMLFileName.isEmpty() && FileExists( sNRCCXMLFileName ) && iCUACReportID < 1)	// SAC 11/26/20
	{	sLogMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
	  	             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Abort' to abort the %3." ).arg( qsSchemaXMLFileDescrip.toLocal8Bit().constData(), sNRCCXMLFileName.toLocal8Bit().constData(), "analysis" );
		if (!OKToWriteOrDeleteFile( sNRCCXMLFileName.toLocal8Bit().constData(), sLogMsg, bSilent ))
		{	sErrMsg = QString( "ERROR:  Analysis aborting - user chose not to overwrite the %1 file:  %2" ).arg( qsSchemaXMLFileDescrip, sNRCCXMLFileName );
//											80 : Analysis aborted - user chose not to overwrite NRCCPRF XML reporting file
			ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 80 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
	}	}
	BEMXMLWriter xmlNRCCPRFFile( ((!bAbort && !BEMPX_AbortRuleEvaluation() && iNRCCXMLClassID > 0 && !sNRCCXMLFileName.isEmpty() && iCUACReportID < 1) ? sNRCCXMLFileName.toLocal8Bit().constData() : NULL), -1, BEMFT_NRCCXML );


	// SAC 9/9/18 - store certain path and filenames to BEMBase for reference during analysis (ported from Res analysis)
   // moved UP from below in order to set PRIOR TO calling rules to generate the DDY file for this run - SAC 09/06/22
	if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())
	{	//QString sBatchPath, sBatchFile, sModelFile;
		//if (sModelFileOnly.lastIndexOf('.') > 0)
		//	sModelFile = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );
		//else
		//	sModelFile = sModelFileOnly;
		//GetCSVOptionString( "BatchPath", sBatchPath, saCSVOptions );
		//GetCSVOptionString( "BatchFile", sBatchFile, saCSVOptions );
		//if (sBatchPath.isEmpty())
		//	sBatchPath = sProcessPath;
		//if (sBatchFile.isEmpty())
		//	sBatchFile = sModelFile + QString(" - analysis");

		//BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BatchPath"      ), BEMP_QStr, (void*) &sBatchPath    , BEMO_User, 0, BEMS_ProgDefault );
		//BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:BatchFile"      ), BEMP_QStr, (void*) &sBatchFile    , BEMO_User, 0, BEMS_ProgDefault );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ModelPath"      ), BEMP_QStr, (void*) &sModelPathOnly,  BEMO_User, 0, BEMS_ProgDefault );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ModelFile"      ), BEMP_QStr, (void*) &sModelFileOnly,  BEMO_User, 0, BEMS_ProgDefault );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ProcessingPath" ), BEMP_QStr, (void*) &sProcessingPath, BEMO_User, 0, BEMS_ProgDefault );
	}

   if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())      // SAC 09/06/22
   {  long lGenerateWthrLocDDY=0, lDBID_GenerateWthrLocDDY = BEMPX_GetDatabaseID( "Proj:GenerateWeatherLocationDDY" );
      if (lDBID_GenerateWthrLocDDY > 0 && BEMPX_GetInteger( lDBID_GenerateWthrLocDDY, lGenerateWthrLocDDY ) && lGenerateWthrLocDDY > 0)
      {  int iGenDDYRetVal = LocalEvaluateRuleset( sErrMsg, 93, "GenerateDDYFromWeatherData", bVerbose, pCompRuleDebugInfo );   // sets up MFam HVACSys objects based on DwellUnitType equipment assignments
                           //											93	: Error evaluating GenerateDDYFromWeatherData rules
         if (iGenDDYRetVal > 0)
            iRetVal = iGenDDYRetVal;
   }  }

   QString qsCompMetricLbl_Short = "TDV";
   if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation()) 
      BEMPX_GetString( BEMPX_GetDatabaseID( "CompMetricLbl_Short", iCID_Proj ), qsCompMetricLbl_Short, FALSE, 0, -1, 0, BEMO_User, "TDV" );   // base metric label on new ruleset var - SAC 01/26/23

	bool bResearchMode = false;
	bool bProposedOnly = false;		// SAC 9/6/13
	BOOL bCompletedAnalysisSteps = FALSE;
	long lQuickAnalysis = 0;		   // SAC 11/8/14
	long lCSESimSpeedOption = 0;		// 0:Compliance, 1:Quick, 2:Specify - SAC 03/02/23
	long lNumPVArraysChk = 0;			// SAC 4/3/19
	bool bEnablePVBattSim = false;	// SAC 4/3/19
   bool bHaveStdPVSim = false;      // SAC 12/08/21
	long lNumUserSpecMats = 0;			// SAC 12/16/21
	long lNumAutosizedResHtPumps = 0;   // SAC 10/15/22
	long lNumResVCHP2HtPumps = 0;       // SAC 10/15/22
	QString sReadVarsESOexe, sReadVarsESOrvi;		// SAC 4/11/16
	QString sExcptDsgnModelFile;	// SAC 12/19/14
	QString sAnnualWeatherFile;
	long lNumSpaceWithDefaultedDwellingUnitArea = 0;	// SAC 6/1/16
	QString sCACertPath;
	GetDLLPath( sCACertPath );
	if (sCACertPath[sCACertPath.length()-1] == '\\')
		sCACertPath = sCACertPath.left( sCACertPath.length()-1 );
	QStringList saEPlusProcDirsToBeRemoved;	// SAC 5/22/19
   std::vector<std::string> svUtilRatesToDelete;      // SAC 09/27/23 (CUAC)
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{
// SAC 4/23/13 - added code to evalaute rl_CHECKCODE & rl_CHECKSIM rulelists and report resulting errors
	//	char pszRuleErr[1024];
//		QString sChkErrMsg;
//		int iPrevErrs = 0;
		BOOL bChkCode = TRUE;
		BOOL bReDefaultModel = FALSE;
	//	int iMaxNumErrsReportedPerType = ReadProgInt( "options", "MaxNumErrorsReportedPerType", 5 );
	//	BOOL bBypassInputChecks = (ReadProgInt( "options", "BypassInputChecks", 0) > 0);
		long lDBID_Proj_AnalysisType = BEMPX_GetDatabaseID( "AnalysisType", iCID_Proj );						assert( lDBID_Proj_AnalysisType > 0 );
		if (lDBID_Proj_AnalysisType > 0)
		{	QString sAT, sATcopy;
			BEMPX_GetString( lDBID_Proj_AnalysisType, sAT );
			sATcopy = sAT;
			sAT = sAT.toLower();
			bResearchMode = (sAT.indexOf("research") >= 0);
			bChkCode = !bResearchMode;
			bProposedOnly = (sAT.indexOf("proposedonly") >= 0);      // SAC 9/6/13
			if ((bProposedOnly || bResearchMode || iCUACReportID > 0) && iAnalysisThruStep > 7)
			{	iAnalysisThruStep = 7;
            if (iCUACReportID > 0)     // SAC 01/15/24
					BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - AnalysisThruStep being set to #%d for CUAC analysis", iAnalysisThruStep ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            else
					BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - AnalysisThruStep being set to #%d due to Proj:AnalysisType = %s (or other special processing modes)", iAnalysisThruStep, sATcopy.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}

		// further defaulting/setup of CompReport* booleans
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportPDFWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportXMLWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportStdWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			if (bResearchMode || bProposedOnly || iCUACReportID > 0)
			{	bComplianceReportPDF = false;
				bComplianceReportXML = false;
				bComplianceReportStd = false;
			}
			else
			{	// set flags for outputting compliance reports if option string indicates -OR- if project data says to...
				long lRptFlag=0;
				if (!bComplianceReportPDF && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CompReportPDF", iCID_Proj ), lRptFlag ) && lRptFlag > 0)
					  bComplianceReportPDF	= true;
				if (!bComplianceReportXML && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CompReportXML", iCID_Proj ), lRptFlag ) && lRptFlag > 0)
					  bComplianceReportXML	= true;
				if (!bComplianceReportStd && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CompReportStd", iCID_Proj ), lRptFlag ) && lRptFlag > 0)	// SAC 11/13/15
					  bComplianceReportStd	= true;
			}
		}

		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "QuickAnalysis", iCID_Proj ), lQuickAnalysis ) && lQuickAnalysisOption >= 0 && lQuickAnalysisOption != lQuickAnalysis)	// SAC 11/8/14
		{						if (bVerbose)
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Forcing QuickAnalysis setting to %d", lQuickAnalysisOption ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			lQuickAnalysis = lQuickAnalysisOption;
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "QuickAnalysis", iCID_Proj ), BEMP_Int, (void*) &lQuickAnalysis );
			bReDefaultModel = TRUE;
		}

      BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResProj:SimSpeedOption" ), lCSESimSpeedOption, -1 );     // 0:Compliance, 1:Quick, 2:Specify - SAC 03/02/23
      if (lCSESimSpeedOption == 0 && lQuickAnalysis > 0)
		{						if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Forcing ResProj:SimSpeedOption to 'Quick' due to QuickAnalysis setting", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			lCSESimSpeedOption = 1;
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ResProj:SimSpeedOption" ), BEMP_Int, (void*) &lCSESimSpeedOption );
		}

		// SAC 4/11/16 - confirm existence of ReadVarsESO exe and rvi files (needed for new SimOutputVariablesToCSV feature)
		if (bNeedReadVarsESO)
		{	sLogMsg.clear();
			sReadVarsESOexe = sEPlusPath + QString("ReadVarsESO.exe");
			bool bRVEexePresent = (FileExists( sReadVarsESOexe.toLocal8Bit().constData() ));
			sReadVarsESOrvi = sModelPathOnly + QString("SimOutVarsToCSV.rvi");
			bool bRVErviPresent = (FileExists( sReadVarsESOrvi.toLocal8Bit().constData() ));
			if (!bRVErviPresent)		// if SimOutVarsToCSV.rvi not in ModelPath, then look for one in EPlusPath
			{	sReadVarsESOrvi = sEPlusPath + QString("SimOutVarsToCSV.rvi");
				bRVErviPresent = (FileExists( sReadVarsESOrvi.toLocal8Bit().constData() ));
			}
			if (bRVEexePresent && bRVErviPresent)
			{	QString sReadVarsESOrviFrom = sReadVarsESOrvi;
				sReadVarsESOrvi = sProcessingPath + QString("SimOutVarsToCSV.rvi");
				if (!CopyFile( sReadVarsESOrviFrom.toLocal8Bit().constData(), sReadVarsESOrvi.toLocal8Bit().constData(), FALSE ))
				{	bRVErviPresent = false;
					sLogMsg = QString::asprintf( "SimOutputVariablesToCSV option(s) disabled due to error copying RVI file: '%s' to '%s'", sReadVarsESOrviFrom.toLocal8Bit().constData(), sReadVarsESOrvi.toLocal8Bit().constData() );
			}	}
			if (!bRVEexePresent || !bRVErviPresent)
			{	if (sLogMsg.isEmpty())
				{	sLogMsg = "SimOutputVariablesToCSV option(s) disabled due to missing file(s):";
					if (!bRVEexePresent)
						sLogMsg += QString("\n      ") + sReadVarsESOexe;
					if (!bRVErviPresent)
						sLogMsg += QString("\n      ") + sReadVarsESOrvi;
				}
				plSimOutputVariablesToCSV[0] = 0;		plSimOutputVariablesToCSV[1] = 0;
				plSimOutputVariablesToCSV[2] = 0;		plSimOutputVariablesToCSV[3] = 0;
			}
			if (!sLogMsg.isEmpty())
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}

	// Exceptional Design Model (IDF) File
		long lUseExcptDsgnModel;
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "UseExcptDsgnModel", iCID_Proj ), lUseExcptDsgnModel ) && lUseExcptDsgnModel > 0)	// SAC 12/18/14
		{	
			if (!BEMPX_GetString( BEMPX_GetDatabaseID( "ExcptDsgnModelFile", iCID_Proj ), sExcptDsgnModelFile ) || sExcptDsgnModelFile.isEmpty() ||
				 (!sExcptDsgnModelFile.isEmpty() && !FileExists( sExcptDsgnModelFile.toLocal8Bit().constData() )) || lQuickAnalysis > 0)
			{	int iLocalErr = 0;
				if (sExcptDsgnModelFile.isEmpty())
				{	iLocalErr = 48;
//											48 : UseExcptDsgnModel flag set but no path/filename specified by UseExcptDsgnModel
					sErrMsg = "Exceptional Design IDF Error:  UseExcptDsgnModel flag set but no path/filename specified by UseExcptDsgnModel";
				}
				else if (!FileExists( sExcptDsgnModelFile.toLocal8Bit().constData() ))
				{	iLocalErr = 49;
//											49 : IDF path/filename specified by Proj:UseExcptDsgnModel not found
					sErrMsg = QString::asprintf( "Exceptional Design IDF Error:  IDF path/filename specified by UseExcptDsgnModel not found:  %s", sExcptDsgnModelFile.toLocal8Bit().constData() );
				}
				else if (lQuickAnalysis > 0)
				{	iLocalErr = 50;
					//						50 : Exceptional Design IDF specification and the Quick Analysis feature cannot both be activated
					sErrMsg = "Exceptional Design IDF specification and the Quick Analysis feature cannot both be activated for a single run";
				}
				if (iLocalErr > 0)
				{	ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iLocalErr /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
					sExcptDsgnModelFile.clear();
				}
			}
			else
			{	QString sExcptDsgnModelFileMsg;
				sExcptDsgnModelFileMsg = QString::asprintf( "Exceptional Design simulation input used in analysis:  ", sExcptDsgnModelFile.toLocal8Bit().constData() );
				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ExcptDsgnModelFileMsg", iCID_Proj ), BEMP_QStr, (void*) &sExcptDsgnModelFileMsg, BEMO_User, 0, BEMS_ProgDefault );
			}
		}

      // SAC 6/1/16 - added check used to disable report security if any DwellingUnitArea values used in analysis are defaulted by the ruleset
		long lDBID_Proj_DefDwellUnitArea = BEMPX_GetDatabaseID( "DefaultedDwellingUnitArea", iCID_Proj );		assert( lDBID_Proj_DefDwellUnitArea > 0 );
		if (lDBID_Proj_DefDwellUnitArea > 0)
			BEMPX_GetInteger( lDBID_Proj_DefDwellUnitArea, lNumSpaceWithDefaultedDwellingUnitArea );

	   // SAC 4/3/19 - added flag to prevent PV-Batt simulation (unless project input allows)
		lNumPVArraysChk  = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray" ) );
      long lHaveStandaloneBatt=0, lDBID_Proj_HaveStandaloneBatt = BEMPX_GetDatabaseID( "HaveStandaloneBatt", iCID_Proj );     // SAC 05/26/22
      double fT24PVSize=0;    // add logic to set bEnablePVBattSim to true if T24PVSize (2022+ prescriptive (std design) PV) > 0 - SAC 12/08/21
		bEnablePVBattSim = ( ( lNumPVArraysChk > 0 ||
                             ( lDBID_Proj_HaveStandaloneBatt > 0 && BEMPX_GetInteger( lDBID_Proj_HaveStandaloneBatt, lHaveStandaloneBatt, 0, -1, 0 ) &&
                               lHaveStandaloneBatt > 0 ) ) ||
                           (BEMPX_GetFloat( BEMPX_GetDatabaseID( "T24PVSize", iCID_Proj ), fT24PVSize, 0, -1, 0 ) && fT24PVSize > 0.1) );
		if (bEnablePVBattSim)
		{	long lPVBattSim, lDBID_Proj_PVBattSim = BEMPX_GetDatabaseID( "PVBattSim", iCID_Proj );		assert( lDBID_Proj_PVBattSim > 0 );
			if (lDBID_Proj_PVBattSim > 0 && BEMPX_GetInteger( lDBID_Proj_PVBattSim, lPVBattSim ) && lPVBattSim == 0)
				bEnablePVBattSim = false;
		}

		long lDBID_Proj_NumUserSpecMats = BEMPX_GetDatabaseID( "NumUserSpecMats", iCID_Proj );	   // SAC 12/16/21
		if (lDBID_Proj_NumUserSpecMats > 0)
			BEMPX_GetInteger( lDBID_Proj_NumUserSpecMats, lNumUserSpecMats );

		long lDBID_Proj_NumAutosizedResHtPumps = BEMPX_GetDatabaseID( "NumAutosizedResHtPumps", iCID_Proj );     // SAC 10/15/22
		if (lDBID_Proj_NumAutosizedResHtPumps > 0)
			BEMPX_GetInteger( lDBID_Proj_NumAutosizedResHtPumps, lNumAutosizedResHtPumps );
		long lDBID_Proj_NumResVCHP2HtPumps = BEMPX_GetDatabaseID( "NumResVCHP2HtPumps", iCID_Proj );	            // SAC 10/15/22
		if (lDBID_Proj_NumResVCHP2HtPumps > 0)
			BEMPX_GetInteger( lDBID_Proj_NumResVCHP2HtPumps, lNumResVCHP2HtPumps );

      // SAC 9/3/13 - moved up here (above CHECKCODE) from below so that weather file hash checks can occur via CHECKCODE
		//sErrMsg.clear();
		if (!bAbort && !BEMPX_AbortRuleEvaluation())
		{	//const char* pszProxyServerAddress     = (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()    );
			//const char* pszProxyServerCredentials = (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData());
			//const char* pszProxyServerType        = (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()       );
			if (CMX_SetupAnalysisWeatherPaths( sSimWeatherPath.toLocal8Bit().constData(), true /*bAnnual*/, true /*bDDY*/, sErrMsg, true /*bAllowWthrDownload*/, 
										(sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()),
										(sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
										(sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()) ) != 0)		// SAC 3/8/13 - added weather file prep routine
			{	BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
            QString sWthrStaErrMsg;    // enable ruleset-defined WeatherStation error messaging - SAC
   			if (BEMPX_GetString( BEMPX_GetDatabaseID( "WeatherStationErrorMsg", iCID_Proj ), sWthrStaErrMsg ) && !sWthrStaErrMsg.isEmpty())
               sErrMsg = sWthrStaErrMsg;
            else
   				sErrMsg = QString::asprintf( "Error encountered initializing weather file locations and/or names for path:  %s", sSimWeatherPath.toLocal8Bit().constData() );
//											14 : Error encountered initializing weather file locations and/or names
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 14 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
		}	}

	// SAC 9/3/13 - added weather file hash check logic
		BOOL bWthrHashesSet = FALSE;
		if (bChkCode && iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())  // only perform weather file hash checks if user performing some sort of compliance analysis	// SAC 10/30/14 - prevent hash checks if errors already occurred
		{	BOOL bWthrHashError = FALSE;
			int iSHA256_AnnWthr_RetVal=0, iSHA256_DDYWthr_RetVal=0;
			QString sDDWeatherFile, sWthrFileEPWHash, sWthrFileDDYHash;
			if (!BEMPX_GetString( BEMPX_GetDatabaseID( "AnnualWeatherFile", iCID_Proj ), sAnnualWeatherFile ) || sAnnualWeatherFile.isEmpty() ||
				 !BEMPX_GetString( BEMPX_GetDatabaseID( "DDWeatherFile"    , iCID_Proj ), sDDWeatherFile     ) || sDDWeatherFile.isEmpty() )
				bWthrHashError = TRUE;
			else
			{	char pEPWHashBuffer[65], pDDYHashBuffer[65];
		// check weather file hash - SAC 9/2/13
				iSHA256_AnnWthr_RetVal = ComputeSHA256_File( sAnnualWeatherFile.toLocal8Bit().constData(), pEPWHashBuffer, 65 );
				iSHA256_DDYWthr_RetVal = ComputeSHA256_File( sDDWeatherFile.toLocal8Bit().constData()    , pDDYHashBuffer, 65 );
				if (iSHA256_AnnWthr_RetVal != 0 || iSHA256_DDYWthr_RetVal != 0)
					bWthrHashError = TRUE;
				else
				{	// post weather file hashes to Proj properties for check in CHECKCODE rules
					bWthrHashesSet = TRUE;
					BEMPX_SetBEMData( BEMPX_GetDatabaseID( "WthrFileEPWHash", iCID_Proj ), BEMP_Str, (void*) pEPWHashBuffer, BEMO_User, 0, BEMS_ProgDefault );
			      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "WthrFileDDYHash", iCID_Proj ), BEMP_Str, (void*) pDDYHashBuffer, BEMO_User, 0, BEMS_ProgDefault );
				}
			}
			if (bWthrHashError)
			{	if (sAnnualWeatherFile.isEmpty())
					sErrMsg = "Error:  Simulation annual weather (EPW) file not defined (setting up check of weather & design day file hashes)";
				else if (sDDWeatherFile.isEmpty())
					sErrMsg = "Error:  Simulation design day (DDY) file not defined (setting up check of weather & design day file hashes)";
				else if (iSHA256_AnnWthr_RetVal != 0)
					sErrMsg = QString::asprintf( "Error:  Unable to compute hash of simulation annual weather (EPW) on:  %s", sAnnualWeatherFile.toLocal8Bit().constData() );
				else if (iSHA256_DDYWthr_RetVal != 0)
					sErrMsg = QString::asprintf( "Error:  Unable to compute hash of simulation design day (DDY) on:  %s", sDDWeatherFile.toLocal8Bit().constData() );
				else
					sErrMsg = "Error:  Unknown error encountered setting up check of weather & design day file hashes";
//												40 : Error setting up check of weather & design day file hashes
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 40 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
		}

      if (iRetVal == 0 && iCUACReportID > 0)    // SAC 08/30/23 (CUAC)
      {  bool bG2ElecRateLoaded=false, bG2GasRateLoaded=false;

            // -----------------
            // ---- Testing ----
               // int iCID_CPR_UtilityRate = BEMPX_GetDBComponentID( "CPR_UtilityRate" );       assert( iCID_CPR_UtilityRate > 0 );
               // QString sG2ElecRateFile, sG2GasRateFile, sG2RateName, qsReadJSONErrMsg;
               // BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TestG2ElecRateFile" ), sG2ElecRateFile );
               // BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TestG2GasRateFile"  ), sG2GasRateFile  );
               // if (iCID_CPR_UtilityRate > 0 && (!sG2ElecRateFile.isEmpty() || !sG2GasRateFile.isEmpty()))
               // {
			      // 																	sDbgFileName = sProcessingPath + sModelFileOnly + QString(" - PreG2RateImport.ibd-Detail");
   		      // 																	BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
               //    if (!sG2ElecRateFile.isEmpty())
               //    {  sG2RateName = QString( "G2ElecRate %1" ).arg( QString::number( BEMPX_GetNumObjects( iCID_CPR_UtilityRate, BEMO_User, iCUAC_BEMProcIdx ) + 1 ) );
               //       int iReadJSONRetVal = BEMPX_ReadComponentFromJSONFile( sG2ElecRateFile.toLatin1().constData(), "CPR_UtilityRate", sG2RateName.toLatin1().constData(), -1, &qsReadJSONErrMsg, "PathFileLoadedFrom" );
               //       if (iReadJSONRetVal >= 0)
               //       {  int iJSONRateError;
               //          BEMObject* pUtilRateObj = BEMPX_GetObjectByClass( iCID_CPR_UtilityRate, iJSONRateError, iReadJSONRetVal );
               //          if (pUtilRateObj)
               //          {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:CPR_ElecUtilityRateRef" ), BEMP_Obj, (void*) pUtilRateObj );
               //             BEMPX_WriteLogFile( QString("   G2 elec rate parse successful:  rate '%1' / file: %2").arg( pUtilRateObj->getName(), sG2ElecRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //             bG2ElecRateLoaded = true;
               //          }
               //          else
               //             BEMPX_WriteLogFile( QString("   G2 elec rate parse successful but error posting rate to BEMBase:  file: %1").arg( sG2ElecRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //       }
               //       else
               //          BEMPX_WriteLogFile( QString("   G2 elec rate parse error:  code %1: %2 / file: %3").arg( QString::number( iReadJSONRetVal ), qsReadJSONErrMsg, sG2ElecRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //    }
               //    if (!sG2GasRateFile.isEmpty())
               //    {  sG2RateName = QString( "G2GasRate %1" ).arg( QString::number( BEMPX_GetNumObjects( iCID_CPR_UtilityRate, BEMO_User, iCUAC_BEMProcIdx ) + 1 ) );
               //       int iReadJSONRetVal = BEMPX_ReadComponentFromJSONFile( sG2GasRateFile.toLatin1().constData(), "CPR_UtilityRate", sG2RateName.toLatin1().constData(), -1, &qsReadJSONErrMsg, "PathFileLoadedFrom" );
               //       if (iReadJSONRetVal >= 0)
               //       {  int iJSONRateError;
               //          BEMObject* pUtilRateObj = BEMPX_GetObjectByClass( iCID_CPR_UtilityRate, iJSONRateError, iReadJSONRetVal );
               //          if (pUtilRateObj)
               //          {  BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:CPR_GasUtilityRateRef" ), BEMP_Obj, (void*) pUtilRateObj );
               //             BEMPX_WriteLogFile( QString("   G2 gas rate parse successful:  rate '%1' / file: %2").arg( pUtilRateObj->getName(), sG2GasRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //             bG2GasRateLoaded = true;
               //          }
               //          else
               //             BEMPX_WriteLogFile( QString("   G2 gas rate parse successful but error posting rate to BEMBase:  file: %1").arg( sG2GasRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //       }
               //       else
               //          BEMPX_WriteLogFile( QString("   G2 gas rate parse error:  code %1: %2 / file: %3").arg( QString::number( iReadJSONRetVal ), qsReadJSONErrMsg, sG2GasRateFile ).toLatin1().constData(), NULL, false /*bBlankFile*/ );
               //    }
               //    // default CPR utility rate objects
               //    CMX_EvaluateRuleset( "CUAC_DefaultGen2Rates", bVerbose, /*bTagDataAsUserDefined*/ TRUE, bVerbose, NULL, NULL, NULL, /*epInpRuleDebugInfo*/ NULL ); 
			      // 																	sDbgFileName = sProcessingPath + sModelFileOnly + QString(" - PostG2RateImport.ibd-Detail");
   		      // 																	BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
               // }
            // ---- Testing ----   END OF
            // -----------------

         long lElecTariffGen=0, lGasTariffGen=0;
         if (!bG2ElecRateLoaded && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:ElecTariffGen" ), lElecTariffGen ) && lElecTariffGen > 1)
         {  CUAC_RateDownload( "Electric", 94, "CUAC:CPR_ElecUtilityRateRef", sProcessingPath, /*sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear,*/ bStoreBEMDetails, bSilent, bVerbose,
                               bResearchMode, pCompRuleDebugInfo, iSecurityKeyIndex, (pszSecurityKey ? pszSecurityKey : NULL),
                               (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
                               (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
                               (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout,
                               (sCUACElecTariffFile.isEmpty()     ? NULL : (const char*) sCUACElecTariffFile.toLocal8Bit().constData()), iDownloadVerbose );
               //											94 : Error downloading CUAC electric tariff schedule
            if (iRetVal > 0)
				   ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 94 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
            else if (iAnalysisStorage < 3)
               svUtilRatesToDelete.push_back( ((std::string) sProcessingPath.toLocal8Bit().constData()) + ((std::string) "er.json") );
         }
         if (iRetVal == 0 && !bAbort && !bG2GasRateLoaded && BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:GasTariffGen"  ), lGasTariffGen  ) && lGasTariffGen > 1)
         {  CUAC_RateDownload( "Gas", 95, "CUAC:CPR_GasUtilityRateRef", sProcessingPath, /*sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear,*/ bStoreBEMDetails, bSilent, bVerbose,
                               bResearchMode, pCompRuleDebugInfo, iSecurityKeyIndex, (pszSecurityKey ? pszSecurityKey : NULL),
                               (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
                               (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
                               (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
                               /*pszErrorMsg, iErrorMsgLen,*/ bAbort, iRetVal, sErrMsg, /*iCUACReportID,*/ iCUAC_BEMProcIdx, iRptGenConnectTimeout, iRptGenReadWriteTimeout,
                               (sCUACGasTariffFile.isEmpty()      ? NULL : (const char*) sCUACGasTariffFile.toLocal8Bit().constData()), iDownloadVerbose );
               //											95 : Error downloading CUAC gas tariff schedule
            if (iRetVal > 0)
				   ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 95 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
            else if (iAnalysisStorage < 3)
               svUtilRatesToDelete.push_back( ((std::string) sProcessingPath.toLocal8Bit().constData()) + ((std::string) "gr.json") );
      }  }

		BOOL bChkFailureDetailsWritten=FALSE;
		if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0)
		{
			int iNumCantGenRptsTRUE = 0;
			QString qsPreAnalChkDlgBody, qsPreAnalChkDlgDetails;
			int iNumPreAnalChkErrs=0, iNumPreAnalChkWarns=0;
			QStringList saPreAnalChkWarningMsgs;

// -----------------------------------------------------
// NEW ERROR/WARNING CHECKING & REPORTING STUFF
// -----------------------------------------------------
		if (!bBypassPreAnalysisCheckRules)		// SAC 1/25/19 (tic #2924)
			{
				iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
   								if (bVerbose)
										BEMPX_WriteLogFile( "  PerfAnal_NRes - Pre-Analysis Check of SDD model", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   	  		BOOL bChkEvalSuccessful = CMX_EvaluateRuleset( "rl_PREANALYSISCHECK" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo, &saPreAnalChkWarningMsgs );
				BEMPX_RefreshLogFile();

				iNumPreAnalChkErrs = BEMPX_GetRulesetErrorCount() - iPrevRuleErrs;
				iNumPreAnalChkWarns = saPreAnalChkWarningMsgs.size();
				if ((iNumPreAnalChkErrs > 0 || iNumPreAnalChkWarns > 0) && iDontAbortOnErrorsThruStep < 1 &&
					 iPreAnalysisCheckPromptOption == 1)	// iPreAnalysisCheckPromptOption = 1  =>  no user prompt / abort analysis if either pre-analysis errors OR warnings are detected
				{
//											71 : Error(s) encountered performing pre-analysis check of input model
						iRetVal = (iRetVal > 0 ? iRetVal : 71);
						bAbort = true;
				}
				else if (iNumPreAnalChkErrs > 0)
				{															if (bStoreBEMDetails && !bChkFailureDetailsWritten)
																			{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(" - PreAnalChk.ibd-Detail");
   																			BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
   																			bChkFailureDetailsWritten = TRUE;
																			}
					if (iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
					{
//											71 : Error(s) encountered performing pre-analysis check of input model
						iRetVal = (iRetVal > 0 ? iRetVal : 71);
						bAbort = true;

						if (iPreAnalysisCheckPromptOption >= 3)		// only prompt user of errors if iPreAnalysisCheckPromptOption >= 3
						{	// populate message re: errors for user prompt
							char pszRuleErr[1024];
							int iErrCount = 0;
							QString qsErrTmp;
							for (int iErr=1; iErr<=iNumPreAnalChkErrs; iErr++)
							{	if (BEMPX_GetRulesetErrorMessage( iPrevRuleErrs+iErr, pszRuleErr, 1024 ))
								{	// filter out generic messages that indicate certain rulelists failing
									if (	_strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rulelist 'ProposedModel", 60 ) == 0 )		// ProposedModelCodeCheck / SimulationCheck / CodeAdditions
									{	// do not report these errors which are always accommpanied by error messages, even when in Verbose mode...
									}
									else if (bVerbose || _strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rule", 41 ) != 0)
									{	iErrCount += 1;
										//if (iErrCount <= iMaxErrCount)
											if (iNumPreAnalChkErrs < 2)
												qsErrTmp = QString( "\n%1" ).arg( pszRuleErr );
											else
												qsErrTmp = QString( "\n(%1)  %2" ).arg( QString::number(iErrCount), pszRuleErr );
											if (!bVerbose)
											{	// if verbose flag NOT set, then strip off details of rule where error occurred
												int iRuleDetailIdx = qsErrTmp.indexOf( "evaluating " );
												if (iRuleDetailIdx > 0)
													qsErrTmp = qsErrTmp.left( iRuleDetailIdx );
											}
											qsPreAnalChkDlgDetails += qsErrTmp;
								}	}
								else
								{	assert( false );
								}
							}	assert( (iErrCount > 0 || qsPreAnalChkDlgDetails.isEmpty()) );
							if (qsPreAnalChkDlgDetails.isEmpty())
							{	// for some reason, no errors were retrieved above...
								qsPreAnalChkDlgDetails = "Error(s) detected during pre-analysis model check. Refer to project log for details.";
							}
							else
							{	iNumPreAnalChkErrs = iErrCount;
								qsPreAnalChkDlgDetails = QString( "%1 error(s) detected by pre-analysis check:" ).arg( QString::number(iErrCount) ) + qsPreAnalChkDlgDetails;
							}
						}
				}	}
				iPrevRuleErrs = BEMPX_GetRulesetErrorCount();

				if (iNumPreAnalChkWarns > 0)
				{	// warnings reported during rl_PREANALYSISCHECK NOT echoed to project log, so we should do that before aborting or prompting user to continue
					bool bPromptUserWarnings = (iPreAnalysisCheckPromptOption >= 2);
					if (bPromptUserWarnings && iNumPreAnalChkErrs > 0)
						qsPreAnalChkDlgDetails += "\n\n";

					if (iNumPreAnalChkWarns < 2)
					{	//BEMPX_WriteLogFile( QString("Warning:  %1").arg(saPreAnalChkWarningMsgs[0]), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						if (bPromptUserWarnings)
							qsPreAnalChkDlgDetails += saPreAnalChkWarningMsgs[0];
						//	qsPreAnalChkDlgDetails += QString( "Warning detected by pre-analysis check:" );
					}
					else
					{	if (bPromptUserWarnings)
							qsPreAnalChkDlgDetails += QString( "%1 warnings detected by pre-analysis check:" ).arg( QString::number(iNumPreAnalChkWarns) );
						for (int iWM=1; iWM<=iNumPreAnalChkWarns; iWM++)
						{	//BEMPX_WriteLogFile( QString("Warning:  %1").arg(saPreAnalChkWarningMsgs[iWM-1]), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							if (bPromptUserWarnings)
								qsPreAnalChkDlgDetails += QString( "\n(%1)  %2" ).arg( QString::number(iWM), saPreAnalChkWarningMsgs[iWM-1] );
					}	}
				}
			}	// end of code that performs Pre-Analysis Check rulelist eval

			QString qsRptIssueDescrip, qsRptIssuePrompt, qsRptIssueListing;
			int iNumRptSecOffTRUE = 0;
			if (iCodeType == CT_T24N && (bComplianceReportPDF || bComplianceReportXML) && !sXMLResultsFileName.isEmpty())
			{	// SAC 7/5/16 - added code to check for any/all conditions where report generation will be prevented or not secure and prompt user of this condition before proceeding with analysis
			#define  NumCantGenRpts  6
				int iCantGenRptIdx[NumCantGenRpts];
				bool bCantGenRpt[] = {	!FileExists( sXMLResultsFileName.toLocal8Bit().constData() ),
												false,	// defined below - check for report gen website not accessible
												false,	// defined below - check for report gen offline
												!sIDFToSimulate.isEmpty(),
												(pbBypassOpenStudio[0] || pbBypassOpenStudio[1] || pbBypassOpenStudio[2] || pbBypassOpenStudio[3]),
                                    !sBypassCompRptMsg.isEmpty()  };    // SAC 12/01/22
				if (iEnableRptGenStatusChecks > 0)
				{	int iRptGenAvail = CMX_CheckSiteAccess( "Proj:RptGenCheckURL", sCACertPath.toLocal8Bit().constData(),
															(sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
															(sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
															NULL /*pszErrMsg*/, 0, bVerbose, 
															(sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
															(sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()) );
					if (iRptGenAvail > -10)
						// rpt gen NOT available
						bCantGenRpt[ (iRptGenAvail < 0 ? 2 : 1) ] = true;
					//	sLogMsg = QString::asprintf( "Compliance report(s) called for but bypassed due to %s.", (iRptGenAvail<0 ? "report generation being offline" : "report generator website not accessible") );
					//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				int iRF;
				for (iRF=0; iRF < NumCantGenRpts; iRF++)
				{	if (bCantGenRpt[iRF])
						iCantGenRptIdx[iRF] = iNumCantGenRptsTRUE++;
					else
						iCantGenRptIdx[iRF] = -1;
				}

				if (iNumCantGenRptsTRUE > 0)
				{
					bComplianceReportPDF = bComplianceReportXML = bComplianceReportStd = false;
					BEMPX_WriteLogFile( "   Skipping compliance report generation due to:", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					for (iRF=0; iRF < NumCantGenRpts; iRF++)
					{	if (bCantGenRpt[iRF])
						{	if (iNumCantGenRptsTRUE == 1)
								qsRptIssueListing = "Unable to generate compliance report due to ";
		//						qsRptIssueListing = "<a>Unable to generate compliance report due to ";
							else if (iCantGenRptIdx[iRF] == 0)
								qsRptIssueListing = "Unable to generate compliance report due to:";
		//						qsRptIssueListing = "<a>Unable to generate compliance report due to:<br></a>";
							switch (iRF)
							{	case  0 :	sLogMsg = QString::asprintf( "      XML results file not found:  %s", sXMLResultsFileName.toLocal8Bit().constData() );						break;
								case  1 :	sLogMsg =       "      report generator website not accessible";											break;
								case  2 :	sLogMsg =       "      report generator offline";																break;
								case  3 :	sLogMsg =       "      IDF file specified in analysis options overriding compliance models";		break;
								case  4 :	sLogMsg =       "      one or more OpenStudio/EnergyPlus simulations being bypassed";				break;
								case  5 :	sLogMsg = QString( "      %1" ).arg( sBypassCompRptMsg );				break;
								default :	sLogMsg.clear();		break;
							}
							if (!sLogMsg.isEmpty())
							{	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								sLogMsg = sLogMsg.trimmed();		// was: TrimLeft();
								if (iNumCantGenRptsTRUE == 1)
									qsRptIssueListing += QString( "%1." ).arg( sLogMsg );
		//							qsRptIssueListing += QString( "%1.<br></a>" ).arg( sLogMsg );
								else
									qsRptIssueListing += QString( "\n(%1) %2" ).arg( QChar('a'+iCantGenRptIdx[iRF]), sLogMsg );
		//							qsRptIssueListing += QString( "<a>%1) %2<br><\a>" ).arg( QChar('a'+iCantGenRptIdx[iRF]), sLogMsg );
					}	}	}
					qsRptIssuePrompt = "<a>Press 'OK' to continue performing anaysis or 'Abort' to terminate analysis.<br></a>";
					qsRptIssueDescrip = "ompliance report generation issue";
				}
				else if (bOrigSendRptSignature)
				{
					long lDisableMandUFacChecks;
					if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "DisableMandUFacChecks", iCID_Proj ), lDisableMandUFacChecks ))		// SAC 2/7/17 - new cause for disabling report security
						lDisableMandUFacChecks = 0;
					//long lResBaseSysChange;         - REMOVED due to changes to ACM - SAC 04/14/21
					//if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResBaseSysChange", iCID_Proj ), lResBaseSysChange ))		// SAC 10/30/19 - new cause for disabling report security
					//	lResBaseSysChange = 0;
					long lDisableMandOccSensorCtrl;
					if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "DisableMandOccSensorCtrl", iCID_Proj ), lDisableMandOccSensorCtrl ))		// SAC 11/1/19 - new cause for disabling report security
						lDisableMandOccSensorCtrl = 0;
			#define  NumRptSecOff  30
					int iRptSecOffIdx[NumRptSecOff];
					bool bRptSecOff[] = {	(bOrigSendRptSignature && iNumFileHashErrs > 0),
													(iDLLCodeYear > 0 && iRulesetCodeYear > 0 && iDLLCodeYear != iRulesetCodeYear),  // inconsistency between software library year (%d) and ruleset code year (%d)", iDLLCodeYear, iRulesetCodeYear );
													(bBypassInputChecks),						// input checks having been bypassed";
													(bBypassUMLHChecks),							// unmet load hour checks having been bypassed";
													(bBypassPreAnalysisCheckRules),			// pre-analysis check rules having been bypassed";		// SAC 1/25/19 (tic #2924)
													(bBypassCheckSimRules),						// simulation check rules having been bypassed";
													(bBypassCheckCodeRules),					// energy code checking rules having been bypassed";
													(plOverrideAutosize[0] != -1 || plOverrideAutosize[1] != -1 || plOverrideAutosize[2] != -1 || plOverrideAutosize[3] != -1),	// override of equipment auto-sizing in one or more simulations";
													(lQuickAnalysis > 0),						// QuickAnalysis option being activated";
													(bIgnoreFileReadErrors),					// file read errors having been ignored";
													(bBypassValidFileChecks),					// file validity checks having been bypassed";
													(!sDevOptsNotDefaultedAbbrev.isEmpty()),	// developer options being activated (as described in previous log message)";
													(!sExcptDsgnModelFile.isEmpty()),			// user specification of alternative proposed simulation IDF file";
													(!sCSEIncludeFileDBID.isEmpty()),			// user specification of CSE include file(s): %s", sCSEIncludeFileDBID );
													(lNumSpaceWithDefaultedDwellingUnitArea > 0),  	// # dwelling unit areas have not been entered by the user
													(lDisableMandUFacChecks > 0),  			// mandatory U-factor checks disabled by the user - SAC 2/7/17
													(iNumFileOpenDefaultingRounds != 3),	// number of model defaulting rounds overridden by user - SAC 4/11/18 
													(lNumPVArraysChk > 0 && bEnablePVBattSim && iRulesetCodeYear < 2022), 		// model includes PV array(s) (and possibly battery) which are not yet allowed in permit analysis  - SAC 4/3/19   // revised to ignore check for 2022+ code vintages - SAC 12/15/21
											      false,   //		(lResBaseSysChange > 0) ,					// flag (Proj:ResBaseSysChange) causing high-rise res baseline system type change for >8 stories set  - SAC 10/30/19     // restored array value as causing indexing issues below - SAC 08/28/21
													(lDisableMandOccSensorCtrl > 0),			// flag (Proj:DisableMandOccSensorCtrl) disabling mandatory occupancy control sensor checks  - SAC 11/1/19
													(bSimulateCSEOnly),  						// causes analysis to skip past EPlus simulations
													(lNumUserSpecMats > 0), 		         // # of Mats defined by user-specified properties and used to describe simulated surfaces in the building - SAC 12/16/21
                                       (lEnableResearchMode > 0),             // EnableResearchMode activated
                                       (lNumAutosizedResHtPumps > 0),         // Autosized Res HtPumps - SAC 10/15/22
                                       (lNumResVCHP2HtPumps > 0),             // VCHP2 Res HtPumps - SAC 10/15/22
                                       (lCSESimSpeedOption > 0),              // CSE simulation modes - 0:Compliance, 1:Quick, 2:Specify - SAC 03/02/23
                                       (lAllowPropPVBatt != -1),              // AllowPropPVBatt activated - SAC 10/25/23
                                       (lAllowStdPV      != -1),              // AllowStdPV      activated - SAC 10/25/23
                                       (lAllowStdBatt    != -1),              // AllowStdBatt    activated - SAC 10/25/23
                                       (iCustomMeterOption > 0),              // CustomMeterOption - SAC 11/02/23
                                       false  };

					for (iRF=0; iRF < NumRptSecOff; iRF++)
					{	if (bRptSecOff[iRF])
							iRptSecOffIdx[iRF] = iNumRptSecOffTRUE++;
						else
							iRptSecOffIdx[iRF] = -1;
					}

					if (iNumRptSecOffTRUE > 0)
					{
						bSendRptSignature = false;
						BEMPX_WriteLogFile( "   Compliance report will be watermarked (not valid compliance documentation) due to:", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						for (iRF=0; iRF < NumRptSecOff; iRF++)
						{	if (bRptSecOff[iRF])
							{	if (iNumRptSecOffTRUE == 1)
									qsRptIssueListing = "Compliance report will be watermarked (cannot serve as compliance documentation) due to ";
		//							qsRptIssueListing = "<a>Compliance report will be watermarked (cannot serve as compliance documentation) due to ";
								else if (iRptSecOffIdx[iRF] == 0)
									qsRptIssueListing = "Compliance report will be watermarked (cannot serve as compliance documentation) due to:";
		//							qsRptIssueListing = "<a>Compliance report will be watermarked (cannot serve as compliance documentation) due to:<br></a>";
								switch (iRF)
								{	case  0 :	sLogMsg = QString::asprintf( "      %d file hash check(s) failed on executable and/or analysis support files (see log file for details)", iNumFileHashErrs );		break;
									case  1 :	sLogMsg = QString::asprintf( "      inconsistency between software library year (%d) and ruleset code year (%d)", iDLLCodeYear, iRulesetCodeYear );		break;
									case  2 :	sLogMsg =        "      input checks being bypassed";		break;
									case  3 :	sLogMsg =        "      unmet load hour checks being bypassed";		break;
									case  4 :	sLogMsg =        "      pre-analysis check rules being bypassed";		break;		// SAC 1/25/19 (tic #2924)
									case  5 :	sLogMsg =        "      simulation check rules being bypassed";		break;
									case  6 :	sLogMsg =        "      energy code checking rules being bypassed";		break;
									case  7 :	sLogMsg =        "      the override of equipment auto-sizing in one or more simulations";		break;
									case  8 :	sLogMsg =        "      the QuickAnalysis option being activated";		break;
									case  9 :	sLogMsg =        "      file read errors being ignored";		break;
									case 10 :	sLogMsg =        "      file validity (hash) checks being bypassed";		break;
									case 11 :	sLogMsg = QString::asprintf( "      developer options being activated: %s (see log file for details)", sDevOptsNotDefaultedAbbrev.toLocal8Bit().constData() );		break;
//	QString sDevOptsNotDefaulted;
//	QString saDevOptsObjProps[] = {	"Proj:DisableDayltgCtrls", "Proj:DefaultDayltgCtrls", "Proj:AutoHardSize", "Proj:AutoEffInput", " " };		// SAC 8/12/14 - updated w/ latest dayltg flags
//	double faDevOptsPropOKVals[] = {               0,                         0,                      0,                      0           };
									case 12 :	sLogMsg =        "      user specification of alternative proposed simulation IDF file";		break;
									case 13 :	sLogMsg = QString::asprintf( "      user specification of %s include file(s): %s", qsCSEName.toLocal8Bit().constData(), sCSEIncludeFileDBID.toLocal8Bit().constData() );		break;
									case 14 :	sLogMsg = QString::asprintf( "      %d dwelling unit space(s) with defaulted information in the Dwelling Unit Data tab", lNumSpaceWithDefaultedDwellingUnitArea );		break;
							//		case 14 :	sLogMsg = QString::asprintf( "      presence of %d space(s) with defaulted residential dwelling unit areas (Spc:DwellUnitTypeArea[*])", lNumSpaceWithDefaultedDwellingUnitArea );
//	case 12 :	sLogMsg = QString::asprintf( "      presence of %d space(s) with defaulted residential dwelling unit areas (Spc:DwellUnitTypeArea[*])", lNumSpaceWithDefaultedDwellingUnitArea );
									case 15 :	sLogMsg =        "      mandatory U-factor checks disabled";		break;	// SAC 2/7/17
									case 16 :	sLogMsg = QString::asprintf( "      number of model defaulting rounds overridden by user (%d entered, 3 required)", iNumFileOpenDefaultingRounds );		break;	// SAC 4/11/18
									case 17 :	sLogMsg =        "      model includes PV array(s) which are not yet allowed in permit analysis";		break;	// SAC 4/3/19
							//		case 18 :	sLogMsg =        "      ResBaseSysChange flag causing high-rise residential baseline system type change for >8 stories set";		break;	// SAC 10/30/19
									case 19 :	sLogMsg =        "      DisableMandOccSensorCtrl flag causing mandatory occupancy control sensor checks to be disabled";		break;	// SAC 11/1/19
									case 20 :	sLogMsg =        "      SimulateCSEOnly flag causing EnergyPlus simulations to be skipped";		break;	// SAC 3/11/20
									case 21 :	sLogMsg = QString::asprintf( "      %ld Material object(s) include user-specified properties that are not allowed in permit analysis", lNumUserSpecMats );		break;	// SAC 12/16/21
									case 22 :	sLogMsg =        "      EnableResearchMode flag activated";		break;	// SAC 02/26/22
                           case 23 :   sLogMsg = QString::asprintf( "      %ld Residential heat pump object(s) are configured for auto-sizing which is not allowed in permit analysis", lNumAutosizedResHtPumps );		break;	// SAC 10/15/22
                           case 24 :   sLogMsg = QString::asprintf( "      %ld Residential heat pump object(s) are specified as 'VCHP - Detailed' which is not allowed in permit analysis", lNumResVCHP2HtPumps );		break;	// SAC 10/15/22
                           case 25 :   sLogMsg = QString::asprintf( "      Residential (CSE) simulation speed setting of '%s' is not allowed in permit analysis, 'Compliance' required", (lCSESimSpeedOption==1 ? "Quick" : "Specify") );		break;	// SAC 03/02/23
									case 26 :	sLogMsg =        "      AllowProposedPVBattery flag activated";   break;	// SAC 10/25/23
									case 27 :	sLogMsg =        "      AllowStandardPV flag activated";		      break;	// SAC 10/25/23
									case 28 :	sLogMsg =        "      AllowStandardBattery flag activated";		break;	// SAC 10/25/23
									case 29 :	sLogMsg =        "      CustomMeterOption activated";		break;	// SAC 11/02/23
									default :	sLogMsg.clear();		break;
								}
								if (!sLogMsg.isEmpty())
								{	if (iRF == 0)	// hash check failures already reported to log above
										BEMPX_WriteLogFile( "      file hash check(s) failures listed above", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									else
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									sLogMsg = sLogMsg.trimmed();		// was: TrimLeft();
									if (iNumRptSecOffTRUE == 1)
										qsRptIssueListing += QString( "%1." ).arg( sLogMsg );
		//								qsRptIssueListing += QString( "%1.<br></a>" ).arg( sLogMsg );
									else
										qsRptIssueListing += QString( "\n(%1) %2" ).arg( QString::number( iRptSecOffIdx[iRF]+1 ), sLogMsg );
		//								qsRptIssueListing += QString( "<a>%1) %2<br><\a>" ).arg( QString::number( iRptSecOffIdx[iRF]+1 ), sLogMsg );
						}	}	}
// kludge to plug in user prompt from Larry
						if (iNumRptSecOffTRUE == 1 && bRptSecOff[14] && sUIVersionString.indexOf( "CBECC-Com" ) >= 0)
							qsRptIssuePrompt = "<a>Press Abort and enter design dwelling unit information to receive a compliant report.<br></a>";
						else
							qsRptIssuePrompt = "<a>Press 'OK' to continue performing anaysis or 'Abort' to terminate analysis.<br></a>";
						qsRptIssueDescrip = "ompliance report watermarking issue";
					}
				}
			}

			// iCompReportWarningOption - Options include:
			//    0 - (compliance engine & batch processing default) no user prompt / continue analysis regardless of compliance report issues
			//    1 - no user prompt / abort analysis of report generation is not available / continue analysis if report is available with security disabled
			//    2 - no user prompt / abort analysis if either report generation is unavailable or security is disabled
			//    3 - prompt user when report generation is not available / continue analysis without prompting user if report security is disabled
			//    4 - abort analysis with no user prompt if report generation is not available / prompt user if report security is disabled
			//    5 - (CBECC-Com live analysis default) prompt user if either report generation is not available or if report security is disabled
			// --------------------------------------------------------
			// iPreAnalysisCheckPromptOption - Options include:
			//    0 - (compliance engine & batch processing default) no user prompt / abort analysis if errors are detected, otherwise continue analysis (regardless of any warnings)
			//    1 - no user prompt / abort analysis if either pre-analysis errors OR warnings are detected
			//    2 - abort analysis with no user prompt if pre-analysis errors are detected / prompt user to continue or abort analysis if warnings are detected
			//    3 - (CBECC-Com live analysis default) prompt user if any pre-analysis errors or warnings are detected (w/ option to continue or abort if warnings but no errors detected)
			if ( (iNumPreAnalChkErrs  < 1 && !qsRptIssuePrompt.isEmpty() && (iCompReportWarningOption > 0 || iNumPreAnalChkErrs > 0)) ||
				  (iNumPreAnalChkErrs  > 0 && iPreAnalysisCheckPromptOption >= 3) ||
				  (iNumPreAnalChkWarns > 0 && iPreAnalysisCheckPromptOption >= 2) )
			{	bool bRptIssueAbort = false;
				bool bSomeRptIssueDescribed = (!qsRptIssueDescrip.isEmpty());
				QString qsPreAnalChkDlgCaption;

				// at this point we have errors & possible warnings echoed to qsPreAnalChkDlgDetails, qsPreAnalChkDlgBody is empty
				//	and report issues are described in qsRptIssue*
				if (iNumPreAnalChkErrs > 0)
				{	// report ONLY the pre-analysis errors
					qsPreAnalChkDlgBody = QString( "<a>Pre-analysis check detected %1 error(s) in user model. Details listed below.<br><br></a>" ).arg( QString::number(iNumPreAnalChkErrs) );
					qsPreAnalChkDlgBody += QString( "<a>Press 'OK' to terminate analysis.<br></a>" ).arg( QString::number(iNumPreAnalChkErrs) );
					qsPreAnalChkDlgCaption = "Pre-Analysis Check Error(s)";
				}
				else
				{	if (!qsRptIssueListing.isEmpty())
					{	// append reporting issue details following warnings
						if (iNumPreAnalChkWarns > 0)
							qsPreAnalChkDlgDetails += QString( "\n\n" );
						qsPreAnalChkDlgDetails += qsRptIssueListing;
					}

					if (iNumPreAnalChkWarns < 1 && !qsRptIssueDescrip.isEmpty())
					{	// base dialog body on reporting issues alone
						qsPreAnalChkDlgBody = QString( "<a>C%1(s) were detected during a pre-analysis check - details listed below.<br><br></a>" ).arg( qsRptIssueDescrip );
						if (iNumCantGenRptsTRUE < 1)  // old caption defaulting...
							// security issue(s) only
							qsPreAnalChkDlgCaption = "Compliance Report Watermark Issue(s)";
						else if (iNumRptSecOffTRUE < 1)
							// no reports only
							qsPreAnalChkDlgCaption = "Compliance Report Generation Issue(s)";
						else
							// combination of report gen access & security issues
							qsPreAnalChkDlgCaption = "Compliance Report Generation and Watermark Issues";
					}
					else if (qsRptIssueDescrip.isEmpty())
					{	// base dialog body on check warnings alone
						qsPreAnalChkDlgBody = QString( "<a>Issue(s) were detected during a pre-analysis check - details listed below.<br><br></a>" );
						qsPreAnalChkDlgCaption = "Pre-Analysis Check Warning(s)";
					}
					else
					{	// base dialog body on check warnings + reporting issues
						qsPreAnalChkDlgBody = QString( "<a>A combination of pre-analysis check and c%1(s) were detected during a pre-analysis check - details listed below.<br><br></a>" ).arg( qsRptIssueDescrip );
						qsPreAnalChkDlgCaption = "Pre-Analysis Check Warning and Reporting Issues";
					}

					if (!qsRptIssuePrompt.isEmpty())
						qsPreAnalChkDlgBody += qsRptIssuePrompt;  // might be custom prompt related to ...design dwelling unit information...
					else
						qsPreAnalChkDlgBody += "<a>Press 'OK' to continue performing anaysis or 'Abort' to terminate analysis.<br></a>";
				}

//						if (qsPreAnalChkDlgBody.isEmpty())
//						{	// no reporting issues found, so just need to deal w/ 
//
//							{	qsPreAnalChkDlgBody = QString( "Pre-analysis check detected %1 error(s) in user model. Details listed below." ).arg( QString::number(iErrCount) );
//
//
//						if (!qsPreAnalChkDlgBody.isEmpty() &&
//							  ((iCompReportWarningOption == 3 && iNumCantGenRptsTRUE > 0) ||
//								 iCompReportWarningOption > 3 ))
//						{	qsPreAnalChkDlgDetails += QString( "\n\n" );
//
//
//			QString qsRptIssuePrompt, qsRptIssueListing;
//					qsRptIssuePrompt = "<a>Press 'OK' to continue performing anaysis or 'Abort' to terminate analysis.<br></a>";
//// kludge to plug in user prompt from Larry
//						if (iNumRptSecOffTRUE == 1 && bRptSecOff[14] && sUIVersionString.indexOf( "CBECC-Com" ) >= 0)
//							qsRptIssuePrompt += "<a>Press Abort and enter design dwelling unit information to receive a compliant report.<br></a>";
//						else
//							qsRptIssuePrompt += "<a>Press 'OK' to continue performing anaysis or 'Abort' to terminate analysis.<br></a>";
//
//					qsRptIssueDescrip = "ompliance report generation issue";
//						qsRptIssueDescrip = "ompliance report watermarking issue";
//
//
//				iNumPreAnalChkErrs = (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs);
//				iNumPreAnalChkWarns = saPreAnalChkWarningMsgs.size();
//							if (qsPreAnalChkDlgDetails.isEmpty())
//							{	// for some reason, no errors were retrieved above...
//								qsPreAnalChkDlgBody = "Error(s) detected during pre-analysis model check. Refer to project log for details.";
//							}
//							else
//							{	qsPreAnalChkDlgBody = QString( "Pre-analysis check detected %1 error(s) in user model. Details listed below." ).arg( QString::number(iErrCount) );
//								iNumPreAnalChkErrs = iErrCount;
//								qsPreAnalChkDlgDetails = QString( "%1 error(s) detected by pre-analysis check:" ).arg( QString::number(iErrCount) ) + qsPreAnalChkDlgDetails;
//							}

	// ??? what if there is a CONFLICT between iCompReportWarningOption & iPreAnalysisCheckPromptOption ... ???
				if (bSomeRptIssueDescribed && iCompReportWarningOption == 4 && iNumCantGenRptsTRUE > 0)
					bRptIssueAbort = true;
				else if (bSomeRptIssueDescribed && iCompReportWarningOption < 3)
				{	if (iCompReportWarningOption == 2)
						bRptIssueAbort = true;
					else if (iCompReportWarningOption == 1 && iNumCantGenRptsTRUE > 0)
						bRptIssueAbort = true;
				}
				if ( (iNumPreAnalChkErrs  > 0 && iPreAnalysisCheckPromptOption >= 3) ||
				     (iNumPreAnalChkWarns > 0 && iPreAnalysisCheckPromptOption >= 2) ||
					  (!bRptIssueAbort && ((iCompReportWarningOption == 3 && iNumCantGenRptsTRUE > 0) ||
												   iCompReportWarningOption > 3)) )
				{	// prompt user
					assert( !qsPreAnalChkDlgCaption.isEmpty() && !qsPreAnalChkDlgBody.isEmpty() );
										//from Larry:
										//(1)    5 dwelling unit spaces are using defaulted information in the Dwelling Unit Data Tabs.  Press Abort and enter design dwelling unit information to receive a compliant report.
#ifdef CM_QTGUI
               if (bDisplayProgress)      // SAC 01/19/25
					{  // display report issues dialog
					   if (sq_app)
					   	sq_app->beep();
					   QMessageBox msgBox;
					   msgBox.setWindowTitle( qsPreAnalChkDlgCaption );
					   msgBox.setIcon( QMessageBox::Warning ); 
					   msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
					   msgBox.setText( qsPreAnalChkDlgBody );
					   msgBox.setDetailedText( qsPreAnalChkDlgDetails );
					   msgBox.setStandardButtons( QMessageBox::Ok );
					   if (iNumPreAnalChkErrs < 1)
					   	msgBox.addButton( QMessageBox::Abort );
					   msgBox.setDefaultButton( QMessageBox::Ok );
					   if (iAnalysisDialogTimeout > 0)
					   	msgBox.button(QMessageBox::Ok)->animateClick(iAnalysisDialogTimeout*1000);		// SAC 1/31/20 - set 10 sec timer, at which time 'OK' is automatically registered/clicked (CEC/LF request)
					   showDetailsInQMessageBox(msgBox, 770, 300);		// routine to OPEN Details (to start with) + resize text box (to larger size)
					   bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);
               }
               else
               {  bRptIssueAbort = false;
                  BEMPX_WriteLogFile( QString("%1 - %2").arg( qsPreAnalChkDlgCaption, qsPreAnalChkDlgBody ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  BEMPX_WriteLogFile( qsPreAnalChkDlgDetails, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
               }
#endif
				}

				if (bRptIssueAbort && iNumPreAnalChkErrs < 1)
				{	sErrMsg = "Analysis aborting - user chose to terminate due to pre-analysis check warning(s) and/or compliance report issue(s)";
//										66 : Analysis aborted - user chose to abort due to pre-analysis check warning(s) and/or compliance reporting issue(s)
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 66 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
			}
		}	// end of outer check for analysis continuing that encapsulates all pre-analysis & report gen checks

		if (!bAbort && !BEMPX_AbortRuleEvaluation() && bReDefaultModel)		// SAC 11/8/14
			DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

      // SAC 6/28/14 - added code to check for IsMultiFamily flag and evaluate rules designed specifically to prepare those models for analysis   // ported to Com - SAC 10/31/21
		if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 && bPerformFullCSESim)
		{
			int iMFPrepRetVal = LocalEvaluateRuleset(	sErrMsg, 87, "MultiFamilyAnalysisPrep",	bVerbose, pCompRuleDebugInfo );	// sets up MFam HVACSys objects based on DwellUnitType equipment assignments
                           //											87	: Error evaluating MultiFamilyAnalysisPrep rules  (BEMAnal_CECRes_EvalPropInp2Error)
			if (iMFPrepRetVal > 0)
				iRetVal = iMFPrepRetVal;
      	if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0)
      		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

         // additional model prep needed for Res analysis - SAC 11/17/21
        	if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 && !bResearchMode && !bProposedOnly)
   		{	iMFPrepRetVal = LocalEvaluateRuleset(	sErrMsg, 88, "OneTimeAnalysisPrep",	bVerbose, pCompRuleDebugInfo );
                           //											88	: Error evaluating OneTimeAnalysisPrep rules  (BEMAnal_CECRes_EvalAnalPrepError)
   			if (iMFPrepRetVal > 0)
   				iRetVal = iMFPrepRetVal;
         	if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0)
         		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );
         }
		}
					//	dTimeToPrepModel[0] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

		if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0)
		{
			if (bBypassInputChecks)
				BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing input (range and required input) checks", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (bBypassCheckSimRules)
				BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing simulation input checks (that are intended to ensure the building model is complete)", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!bChkCode)
				BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing energy code checks (due to research mode)", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			else if (bBypassCheckCodeRules)
			{	BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing energy code checks", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				bChkCode = FALSE;
			}

			iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
			BOOL bRangeCheckOK, bChkEvalSuccessful;
	      for (int iChk=(bBypassInputChecks ? 1 : 0); iChk < (bChkCode ? 3 : 2); iChk++)
			{						if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
										BEMPX_WriteLogFile( "  PerfAnal_NRes - Checking SDD model", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				if (iChk==0)
					bRangeCheckOK = BEMPX_PerformErrorCheck( bChkCode /*bRequireRequiredData=TRUE*/, FALSE /*bReportSimDefaultErrors=TRUE*/,
																			FALSE /*bPerformReqdClassCheck=TRUE*/, FALSE /*bPostRangeWarnings=FALSE*/ );
				else if (iChk==1 && !bBypassCheckSimRules )
	      		bChkEvalSuccessful = CMX_EvaluateRuleset( "rl_CHECKSIM" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );
				else if (iChk==2 && !bBypassCheckCodeRules)
	      		bChkEvalSuccessful = CMX_EvaluateRuleset( "rl_CHECKCODE", bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );
				BEMPX_RefreshLogFile();	// SAC 5/19/14

				if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs)
				{															if (bStoreBEMDetails && !bChkFailureDetailsWritten)
																			{	QString sChkErr = (iChk==0 ? " - RangeReqd" : (iChk==1 ? " - ChkSim" : " - ChkCode"));
																				sDbgFileName = sProcessingPath + sModelFileOnly + sChkErr + QString(".ibd-Detail");
	   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
	   																		bChkFailureDetailsWritten = TRUE;
																			}
					if (iDontAbortOnErrorsThruStep < 1)  // check flag to bypass errors
					{
//											11 : Error(s) encountered performing required data & numeric range checks
//											12 : Error(s) encountered checking input model for simulation compatibility
//											13 : Error(s) encountered checking input model for code requirements
						iRetVal = (iRetVal > 0 ? iRetVal : 11+iChk);		// do abort (after ALL checks)
						bAbort = true;
				}	}

				iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
			}

			// blast weather file hash property values - not helpful for them to remain in analysis inputs - SAC 9/3/13
			if (bWthrHashesSet)
			{	BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "WthrFileEPWHash", iCID_Proj ), iError );
				BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "WthrFileDDYHash", iCID_Proj ), iError );
			}

					if (iAnalysisThruStep < 2)
					{	bCompletedAnalysisSteps = TRUE;
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
		}
	}

   long lIsCalPRM = 0, lDBID_Proj_IsCalPRM = BEMPX_GetDatabaseID( "IsCalPRM", iCID_Proj );      // SAC 10/29/23
   if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 && lDBID_Proj_IsCalPRM > 0)
      BEMPX_GetInteger( lDBID_Proj_IsCalPRM, lIsCalPRM );

		if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 && bPerformFullCSESim && !bResearchMode && !bProposedOnly)
      {  // additional model prep needed for Res analysis - SAC 11/17/21
   		int iMFPrepRetVal = LocalEvaluateRuleset(	sErrMsg, 89, "ProposedModelCodeAdditions", bVerbose, pCompRuleDebugInfo );
                        //											89	: Error evaluating ProposedModelCodeAdditions rules  (BEMAnal_CECRes_EvalCodeAddError)
   		if (iMFPrepRetVal > 0)
   			iRetVal = iMFPrepRetVal;
        	else if (!bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0)
        		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );
      }

		// BEFORE writing SDD XML file, evaluate rulelist that does certain OSM-prep, incl. creating & assigning ThrmlEngyStor:DischrgSchRef, ChrgSchRef & ChlrOnlySchRef based on ModeSchRef
			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 &&
				 BEMPX_RulelistExists( "ProposedModelPrep" ))
			{
				int iOSTPRetVal = LocalEvaluateRuleset( sErrMsg, 67, "ProposedModelPrep", bVerbose, pCompRuleDebugInfo );
                           //											67 : Error evaluating ProposedModelPrep rules
				if (iOSTPRetVal != 0 || BEMPX_AbortRuleEvaluation())
					//ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 67 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 67 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}

	QVector<QString> saSimulatedRunIDs;
	double dEPlusVer=0.0;	// SAC 5/16/14
	char pszEPlusVerStr[60] = "\0";
	char pszOpenStudioVerStr[60] = "\0";
	QString sCSEVersion;  // SAC 10/10/16
	bool bHaveResult=false, bResultIsPass=false;
	QString sResTemp1, sResTemp2;
	int iAnalStep=-1;		//, iProgressModel2=0;
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && !bCompletedAnalysisSteps)
	{

	//				BOOL bStoreBEMDetails = (ReadProgInt( "options", "StoreBEMDetails", 0) > 0);
//MarkRuleDataUserDefined=1

		QString sDbgFileName;
		int iNumRuns = 4;		// std scenario for T24N
		if (bResearchMode)
			iNumRuns = 1;
		else if (iCodeType == CT_T24N)
	// SAC 11/22/16 - revised logic to NOT limit iNumRuns but rather toggle off individual runs below for bProposedOnly analysis
		{	//if (bProposedOnly)
			//	iNumRuns = 2;
		}
		else	// S901G or ECBC		- SAC 8/21/15
		{	//if (bProposedOnly)
			//	iNumRuns = 2;
			//else
				iNumRuns = 10;
		}

		assert( BEMPX_GetActiveModel() == 0 );

		if (bResearchMode || bProposedOnly || iCUACReportID > 0)  // SAC 11/22/16 - was: iNumRuns < 4)
		{	// second round of progress dialog setting initialization
			if (iCodeType == CT_T24N)
			{	if (bParallelSimulations)
						SetCECNResProgressVal_Parallel( false, true, true, bPerformComSim, bPerformFullCSESim );  // SAC 11/19/21
				else	SetCECNResProgressVal_Serial( true, true, false, false );
			}
			else
			{	if (bParallelSimulations)
						SetS901GProgressVal_Parallel( false, true, true );
				else	SetS901GProgressVal_Serial( true, true, false, false );
			}
		}
																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}

		BEMPX_InitializeHourlyResults();  // initialize hourly results stored in BEMProc
		// DELETE ALL EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
// debugging PV-solar
//	BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), about to delete any/all EUseSummary & EnergyUse" ), NULL, FALSE, TRUE, FALSE );
		int iResObjCls[3] = { BEMPX_GetDBComponentID( "EUseSummary" ), BEMPX_GetDBComponentID( "EnergyUse" ), 0 };		assert( iResObjCls[0] > 0 && iResObjCls[1] > 0 );
		int iResObjClsIdx=-1;
		while (iResObjCls[++iResObjClsIdx] > 0)
		{  int iNumObjsToDel = BEMPX_GetNumObjects( iResObjCls[iResObjClsIdx], BEMO_User /*, iCurActiveBEMProcIdx*/ );
			for (int iDelObjIdx = iNumObjsToDel-1; iDelObjIdx >= 0; iDelObjIdx--)
			{	BEMObject* pDelObj = BEMPX_GetObjectByClass( iResObjCls[iResObjClsIdx], iError, iDelObjIdx, BEMO_User /*, iCurActiveBEMProcIdx*/ );		assert( pDelObj );
				if (pDelObj)
					BEMPX_DeleteObject( pDelObj /*, iCurActiveBEMProcIdx*/ );
			}
		}

	// Set last run date parameter - added 11/12/13 by SAC from Res analysis
		if (iRetVal == 0)  // SAC 8/27/13 - ported rundate setting code from CBECC into BEMCmpMgr
		{	//CTime time = CTime::GetCurrentTime();
			//long lTime = (long) time.GetTime();
			QDateTime current = QDateTime::currentDateTime();
			long lTime = (long) current.toTime_t();	// seconds since 1970-Jan-01 / valid as long int until 2038-Jan-19 / switching to uint extends valid date range to 2106-Feb-07
			long lDBID_RunDate = BEMPX_GetDatabaseID( "RunDate", iCID_Proj );
			BEMPX_SetBEMData( lDBID_RunDate, BEMP_Int, (void*) &lTime );
		// add formatted RunDate string -> RunDateFormatted property
			QString sRunDateFmt;
			BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -1 /*iPrecision*/ );
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunDateFmt", iCID_Proj ), BEMP_QStr, (void*) &sRunDateFmt );  // was: Proj:RunDateFormatted - SAC 10/28/21
			BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -3 /*iPrecision*/ );	// SAC 5/16/18 - added new '-3' format to handle output as ISO (xsd:datetime) string  // SAC 9/10/18 - ported from Res
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunDateISO", iCID_Proj ), BEMP_QStr, (void*) &sRunDateFmt );
         if (iCUACReportID > 0)
         {  BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -4 /*iPrecision*/ );      // new format: "M/d/yyyy h:m:s ap" - SAC 10/28/22 (CUAC)
            BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), BEMP_QStr, (void*) &sRunDateFmt ); 
         }
		}

					//		AnalysisThruStep options:
					//		     iRun
					//		  1    0   - Analysis Initialization (DEFAULT/PREANALYSISCHECK/CHECKSIM/CHECKCODE rules)
					//		  2   0-1  - Evaluate SIZING_PROPOSED and SIZING_BASELINE rules
					//		  3   0-1  - Generate SIZING_PROPOSED and SIZING_BASELINE OSM & IDF
					//		  4   0-1  - Simulate SIZING_PROPOSED and SIZING_BASELINE models & retrieve results (possibly iterate for ruleset autosized models)
					//		  5   2-3  - Evaluate ANNUAL_PROPOSED and ANNUAL_BASELINE rules
					//		  6   2-3  - Generate ANNUAL_PROPOSED and ANNUAL_BASELINE OSM & IDF
					//		  7   2-3  - Simulate ANNUAL_PROPOSED and ANNUAL_BASELINE models & retrieve results / UMLH check
					//		  8    3   - Generation of compliance report

								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( "  PerfAnal_NRes - starting run loop", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		int iRun = 0;
		COSRunInfo osRunInfo[MultEPlusSim_MaxSims];	// SAC 4/18/14 - used to store simulation inputs for runs that are skipped and to be simulated w/ following run
		OS_SimInfo osSimInfo[MultEPlusSim_MaxSims];	// SAC 8/19/15 - used to facilitate more than 2 simulations at a time (for 90.1 baseline orientation sim/averaging)
		OS_SimInfo* posSimInfo[MultEPlusSim_MaxSims];
		for (; iRun < MultEPlusSim_MaxSims; iRun++)
			posSimInfo[iRun] = &osSimInfo[iRun];
	   BOOL bModelOK = TRUE;
		BOOL bModelInitialized[]   = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };				assert( iNumRuns <= 10 );
		BOOL bSizingRunSimulated[] = { FALSE, FALSE, FALSE, FALSE, FALSE };
		bool bModelToBeSimulated[] = { true, (iNumRuns > 1), (iNumRuns > 2), (iNumRuns > 3), (iNumRuns > 4), (iNumRuns > 5), (iNumRuns > 6), (iNumRuns > 7), (iNumRuns > 8), (iNumRuns > 9) };
		if (bProposedOnly || iCUACReportID > 0)  // SAC 11/22/16 - new logic to handle bProposedOnly analysis
		{	if (iCodeType == CT_T24N)
			{	assert( iNumRuns == 4 );
				bModelToBeSimulated[1] = false;  bModelToBeSimulated[3] = false;  // toggle OFF baseline sizing and annunal runs
			}
			else	// S901G or ECBC		- SAC 8/21/15
			{	bModelToBeSimulated[1] = false;  bModelToBeSimulated[2] = false;  bModelToBeSimulated[3] = false;  bModelToBeSimulated[4] = false;	// toggle OFF baseline runs by orientation
				bModelToBeSimulated[6] = false;  bModelToBeSimulated[7] = false;  bModelToBeSimulated[8] = false;  bModelToBeSimulated[9] = false;
		}	}
		int iPropModelRunIdx = (iCodeType == CT_T24N ? 2 : 5);		// SAC 4/6/20

      bool bLogCSERunLoopDetails = (bVerbose || ebLogAnalysisMsgs);
               // DEBUGGING
               //bLogCSERunLoopDetails = true;

		int iLastHrlyStorModelIdx = -1;
      //		bool bThisOSSimSkipped = false, bLastOSSimSkipped = false;	// SAC 4/18/14
		bool bSimRunsNow = false;	// SAC 8/19/15 - added to facilitate more than 2 simulations at a time (for 90.1 baseline orientation sim/averaging)
		int iSimRunIdx = 0, iSimRun, iProgressModelSum=0;
		QString sErrMsgShortenedToFit;
		long lZEROCode=0;			QString sZeroCdHrlyExportPathFile;		bool bZCHrlyFileWritten = false;		// SAC 9/8/18
      long lOne = 1, lZero = 0;

      // ----------
      // RUN LOOP
      // ----------
		for (iRun=0; (!bAbort && !BEMPX_AbortRuleEvaluation() && !bCompletedAnalysisSteps && iRun < iNumRuns); iRun++)
		{
			BOOL bSimulateModel = bModelToBeSimulated[iRun], bFinalRun = FALSE;  // SAC 11/22/16 - was: TRUE;		// SAC 11/18/20 - bFinalRun
			int iProgressModel=0, iSizingRunIdx=-1, iModelGenErr=0, iResultRunIdx=0, iSimErrID=0, iResErrID=0;		//, iProgressModel2=0;
			iAnalStep=-1;
			QString sRunID, sRunIDLong;
			if (iCodeType == CT_T24N)
			{	switch (iRun)
				{	case  1 :				sRunID = "zb";			sRunIDLong = "Standard Sizing";		bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_zb;									iAnalStep = 3;		iResultRunIdx = 1;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	/*siOSWrapProgressIndex = CNRP_StdSizSim;*/		break;
					case  2 :				sRunID = "ap";			sRunIDLong = "Proposed";				bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[3]);		iProgressModel = BCM_NRP_Model_ap;		iSizingRunIdx = 0;	iAnalStep = 4;		iResultRunIdx = 0;	iModelGenErr = 17;	iSimErrID = 25;		iResErrID = 28;	/*siOSWrapProgressIndex = CNRP_PropSim;*/			break;
					case  3 :				sRunID = "ab";			sRunIDLong = "Standard";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_ab;		iSizingRunIdx = 1;	iAnalStep = 6;		iResultRunIdx = 1;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	bFinalRun = TRUE;		/*siOSWrapProgressIndex = CNRP_StdAnnSim;*/		break;
					default :	if (bResearchMode)
											{	sRunID = "r";			sRunIDLong = "Research";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_u;																																										bFinalRun = TRUE;		/*siOSWrapProgressIndex = CNRP_PropSizSim;*/	}
									else	{	sRunID = "zp";			sRunIDLong = "Proposed Sizing";		bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[1]);		iProgressModel = BCM_NRP_Model_zp;									iAnalStep = 2;		iResultRunIdx = 0;	iModelGenErr = 16;	iSimErrID = 45;		iResErrID = 46;	/*siOSWrapProgressIndex = CNRP_PropSizSim;*/	}	break;
			}	}
			else
			{	switch (iRun)
				{	case  1 :				sRunID = "zb1";		sRunIDLong = "Baseline Sizing1";		bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_zb1;								iAnalStep = 2;		iResultRunIdx = 1;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	break;
					case  2 :				sRunID = "zb2";		sRunIDLong = "Baseline Sizing2";		bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_zb2;								iAnalStep = 2;		iResultRunIdx = 2;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	break;
					case  3 :				sRunID = "zb3";		sRunIDLong = "Baseline Sizing3";		bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_zb3;								iAnalStep = 2;		iResultRunIdx = 3;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	break;
					case  4 :				sRunID = "zb4";		sRunIDLong = "Baseline Sizing4";		bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRAP_Model_zb4;								iAnalStep = 3;		iResultRunIdx = 4;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	break;
					case  5 :				sRunID = "ap";			sRunIDLong = "Proposed";				bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[6]);		iProgressModel = BCM_NRAP_Model_ap ;	iSizingRunIdx = 0;	iAnalStep = 4;		iResultRunIdx = 0;	iModelGenErr = 17;	iSimErrID = 25;		iResErrID = 28;	break;
					case  6 :				sRunID = "ab1";		sRunIDLong = "Baseline1";				bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_ab1;	iSizingRunIdx = 1;	iAnalStep = 4;		iResultRunIdx = 1;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	break;
					case  7 :				sRunID = "ab2";		sRunIDLong = "Baseline2";				bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_ab2;	iSizingRunIdx = 2;	iAnalStep = 4;		iResultRunIdx = 2;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	break;
					case  8 :				sRunID = "ab3";		sRunIDLong = "Baseline3";				bSimRunsNow = (bSimulateModel && !bParallelSimulations);											iProgressModel = BCM_NRAP_Model_ab3;	iSizingRunIdx = 3;	iAnalStep = 4;		iResultRunIdx = 3;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	break;
					case  9 :				sRunID = "ab4";		sRunIDLong = "Baseline4";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRAP_Model_ab4;	iSizingRunIdx = 4;	iAnalStep = 6;		iResultRunIdx = 4;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	bFinalRun = TRUE;		break;
					default :	if (bResearchMode)
											{	sRunID = "r";			sRunIDLong = "Research";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_u   ;																																									bFinalRun = TRUE;		}
									else	{	sRunID = "zp";			sRunIDLong = "Proposed Sizing";		bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[1]);		iProgressModel = BCM_NRAP_Model_zp ;								iAnalStep = 2;		iResultRunIdx = 0;	iModelGenErr = 16;	iSimErrID = 45;		iResErrID = 46;	}	break;
			}	}
								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Run loop %d for model %s / bSimulateModel %s / bSimRunsNow %s", iRun, sRunID.toLocal8Bit().constData(), (bSimulateModel ? "true" : "false"), (bSimRunsNow ? "true" : "false") ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

            #ifdef CM_QTGUI
							sqProgressRunName = ""; // sRunID;
							if (!bAbort && !BEMPX_AbortRuleEvaluation() && bDisplayProgress)
							{	// enum  CECNResProgressSteps   {   CNRP_Init,  CNRP_ModelPrep,  CNRP_PropSizTrn,  CNRP_PropSizSim,  CNRP_StdSizTrn,  CNRP_StdSizSim,  CNRP_PropTrn,  CNRP_PropSim,  CNRP_StdAnnTrn,  CNRP_StdAnnSim,  CNRP_Results,  CNRP_NumSteps };
								//iProgressStep = CNRP_PropSizTrn + (iRun * 2);
								iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_MPrep, iProgressModel, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
							}
            #endif

			if (!bSimulateModel)
				BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing %s model setup and simulation", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			else
			{
//			bLastOSSimSkipped = bThisOSSimSkipped;		// SAC 4/18/14
//			bThisOSSimSkipped = false;
			QString sProjFileAlone = sModelFileOnly;
			BOOL bCallOpenStudio = TRUE;
			bool bStoreHourlyResults = false;
                        							assert( iSizingRunIdx < 5 );	// otherwise above bSizingRunSimulated array requires re-sizing
								if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Preparing model %s", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			int iCurActiveBEMProcIdx = -1;
			if (bResearchMode)
			{	sProjFileAlone += " - run";
			}
			else
			{
				sErrMsg.clear();
				sDbgFileName = (bStoreBEMDetails ? sProcessingPath + sModelFileOnly + QString(" - ") + sRunID + QString(".ibd-Detail") : "");

				bool bCopySizingResultsOK = true;		int iBEMProcIdxToCopy = -1;
				if (iRun == 0 || !bModelInitialized[iRun])
				{  bModelOK  = CMX_TransformModel( sRunID.toLocal8Bit().constData(), TRUE /*bEvalRules*/, bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/,
				   											sDbgFileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );
                                 if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                    BEMPX_WriteLogFile( QString::asprintf( "    model transform performed for '%s'", sRunID.toLocal8Bit().constData() ) );
            }
				else
				{  int iThisRunBEMProcIdx = BEMPX_GetTransformIndex( sRunID.toLocal8Bit().constData() );		assert( iThisRunBEMProcIdx > 0 );
					if (BEMPX_GetActiveModel() != iThisRunBEMProcIdx)
						BEMPX_SetActiveModel( iThisRunBEMProcIdx );
					if (iSizingRunIdx >= 0 && bSizingRunSimulated[iSizingRunIdx])
					{	long laDBIDsToBypassCopy[21] = {  0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,  0 };
  						int iTransIdx = BEMPX_GetTransformInitializationInfo( sRunID.toLocal8Bit().constData(), &iBEMProcIdxToCopy, laDBIDsToBypassCopy, 20 );				assert( iTransIdx >= 0 );
						bCopySizingResultsOK = CMX_CopySizingResults_CECNonRes( iBEMProcIdxToCopy, iThisRunBEMProcIdx, bVerbose /*bVerboseOutput*/ );
                                 if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                    BEMPX_WriteLogFile( QString::asprintf( "    sizing results copied from BEMProcIdx %d to model '%s'", iBEMProcIdxToCopy, sRunID.toLocal8Bit().constData() ) );
					}
			   	bModelOK  = CM_EvaluateModelRules( sRunID.toLocal8Bit().constData(), bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/, 
			   													sDbgFileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );		assert( bModelOK );
                                 if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                    BEMPX_WriteLogFile( QString::asprintf( "    model transform rules evaluated for '%s'", sRunID.toLocal8Bit().constData() ) );
				}
				if (bModelOK && bPurgeUnreferencedObjects)
					// Purge user-defined non-parent/child components which are not referenced  - SAC 8/12/13 - added to prevent simulation of objects that are not referenced in the building model
					BEMPX_PurgeUnreferencedComponents();
				if (iAnalysisThruStep < iAnalStep)
				{	bCompletedAnalysisSteps = TRUE;
										BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				else if (iNumBypassItems > iRun && pbBypassOpenStudio && pbBypassOpenStudio[iRun])  // ReadProgInt( "options", "BypassOpenStudio_**", 0 ) > 0)
				{	bCallOpenStudio = FALSE;
                                 if (bLogCSERunLoopDetails)    // SAC 06/26/23
                                    BEMPX_WriteLogFile( QString::asprintf( "    skipping OpenStudio for model '%s' due to BypassOpenStudio flags", sRunID.toLocal8Bit().constData() ) );
            }

				if (!bCopySizingResultsOK)
				{	sErrMsg = QString::asprintf( "Error copying equipment sizes/flows from %d to '%s' model", iBEMProcIdxToCopy, sRunID.toLocal8Bit().constData() );
//											36 : Error copying equipment sizes/flows from source model
					if (iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 36 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
				}
				if (!bModelOK && iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
				{	assert( FALSE ); // shouldn't ever get here since we are no longer generating pz model
					sErrMsg = QString::asprintf( "Error generating %s model", sRunIDLong.toLocal8Bit().constData() );
//											16 : Error generating Proposed Sizing model
//											18 : Error generating Standard Sizing model
//											17 : Error generating Proposed (final) model
//											19 : Error generating Standard (final) model
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iModelGenErr /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
				}
				BEMPX_RefreshLogFile();	// SAC 5/19/14

				if (bModelOK)
					bModelInitialized[iRun] = TRUE;
				if (bCallOpenStudio && BEMPX_GetRulesetSimulateFlagValue( 1 /*fDefault*/ ) < 0.1)	// SAC 4/1/14 - added logic to check for simulate flag being set
				{	bCallOpenStudio = FALSE;
							if (bVerbose)
								BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing OpenStudio due to Simulate flag in BEMBase toggled off (%s)", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				else if (bCallOpenStudio && !bSimulateModel)
					bCallOpenStudio = FALSE;	// SAC 11/22/16 - ensure no sim of models when in ProposedOnly mode

			// check for any SUBSEQUENT transforms that initialize to this one and init them (w/out rule evaluation) PRIOR to performing simulation & retrieving results
								if (bVerbose)
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Checking for subsequent model init (%s)", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				iCurActiveBEMProcIdx = BEMPX_GetActiveModel();
				int iRunBEMProcIdx = BEMPX_GetTransformIndex( sRunID.toLocal8Bit().constData() );		assert( iRunBEMProcIdx > 0 );
				for (int iRun2=iRun+1; (sErrMsg.isEmpty() && !bAbort && !BEMPX_AbortRuleEvaluation() && !bCompletedAnalysisSteps && iRun2 < iNumRuns); iRun2++)
				{
	// ??? added to prevent init of ap prior to init of zb2-4
					if (iRun2 < BEMPX_GetModelCount() && !bModelInitialized[iRun2])
					{	QString sRunID2, sRunID2Long;		int iModel2InitErr = 0, iAnalStep2 = 0;
						if (iCodeType == CT_T24N)
						{	switch (iRun2)
							{	case  1 :	sRunID2 = "zb";		sRunID2Long = "Standard Sizing";		iModel2InitErr = 20;		iAnalStep2 = 3;		break;
								case  2 :	sRunID2 = "ap";		sRunID2Long = "Proposed";				iModel2InitErr = 44;		iAnalStep2 = 4;		break;
								case  3 :	sRunID2 = "ab";		sRunID2Long = "Standard";				iModel2InitErr = 21;		iAnalStep2 = 6;		break;
						}	}
						else
						{	switch (iRun2)
							{	case  1 :	sRunID2 = "zb1";		sRunID2Long = "Baseline Sizing1";	iModel2InitErr = 20;		iAnalStep2 = 3;		break;
								case  2 :	sRunID2 = "zb2";		sRunID2Long = "Baseline Sizing2";	iModel2InitErr = 20;		iAnalStep2 = 3;		break;
								case  3 :	sRunID2 = "zb3";		sRunID2Long = "Baseline Sizing3";	iModel2InitErr = 20;		iAnalStep2 = 3;		break;
								case  4 :	sRunID2 = "zb4";		sRunID2Long = "Baseline Sizing4";	iModel2InitErr = 20;		iAnalStep2 = 3;		break;
								case  5 :	sRunID2 = "ap";		sRunID2Long = "Proposed";				iModel2InitErr = 44;		iAnalStep2 = 4;		break;
								case  6 :	sRunID2 = "ab1";		sRunID2Long = "Baseline1";				iModel2InitErr = 21;		iAnalStep2 = 6;		break;
								case  7 :	sRunID2 = "ab2";		sRunID2Long = "Baseline2";				iModel2InitErr = 21;		iAnalStep2 = 6;		break;
								case  8 :	sRunID2 = "ab3";		sRunID2Long = "Baseline3";				iModel2InitErr = 21;		iAnalStep2 = 6;		break;
								case  9 :	sRunID2 = "ab4";		sRunID2Long = "Baseline4";				iModel2InitErr = 21;		iAnalStep2 = 6;		break;
						}	}
						int iBEMProcIdxToCopy = 0;
						long laDBIDsToBypassCopy[21] = {  0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,  0 };
	   				int iTransIdx = BEMPX_GetTransformInitializationInfo( sRunID2.toLocal8Bit().constData(), &iBEMProcIdxToCopy, laDBIDsToBypassCopy, 20 );			assert( iTransIdx >= 0 );
						if (iBEMProcIdxToCopy <= iRunBEMProcIdx)
						{	QString sDbgRun2FileName;
							if (bStoreBEMDetails)
								sDbgRun2FileName = QString::asprintf( "%s%s - %s.ibd-Detail", sProcessingPath.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunID2.toLocal8Bit().constData() );
							bModelInitialized[iRun2] = CMX_TransformModel( sRunID2.toLocal8Bit().constData(), FALSE /*bEvalRules*/, bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/, 
																							sDbgRun2FileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );

							if (!bModelInitialized[iRun2])
							{	sErrMsg = QString::asprintf( "Error generating %s model", sRunID2Long.toLocal8Bit().constData() );
//											44 : Error initializing Proposed model
//											20 : Error initializing Standard Sizing model
//											21 : Error initializing Standard (final) model
						//		if ((iRun2==1 && iDontAbortOnErrorsThruStep < 3) || (iRun2==2 && iDontAbortOnErrorsThruStep < 6) || (iRun2==3 && iDontAbortOnErrorsThruStep < 6))  // check flag to bypass errors
								if (iDontAbortOnErrorsThruStep < iAnalStep2)  // check flag to bypass errors
									ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iModel2InitErr /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 6 /*iStepCheck*/ );
							}
							else if (iRulesetCodeYear < 2022)   // only do this manual ResDHWBaselineRulelistName evaluation for code years prior to 2022 - SAC 11/13/21
						// code to evaluate rulelist FOLLOWING model transformation (for now to facilitate Res DHW baseline via modified CBECC-Res rules) - SAC 8/17/18 (Com tic #2675)
							{	QString sResDHWBaselineRulelistName;
								BEMPX_GetString( BEMPX_GetDatabaseID( "ResDHWBaselineRulelistName", iCID_Proj ), sResDHWBaselineRulelistName );
								if (sResDHWBaselineRulelistName.length() > 0)
								{	if (!BEMPX_RulelistExists( sResDHWBaselineRulelistName.toLocal8Bit().constData() ))
										BEMPX_WriteLogFile( QString::asprintf( "Warning:  ResDHWBaselineRulelist '%s' not found in ruleset.", sResDHWBaselineRulelistName.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									else
									{
		// debugging
		//BEMPX_WriteLogFile( QString::asprintf( "Evaluating ResDHWBaselineRulelist '%s' on model %d (iCurActiveBEMProcIdx %d).", sResDHWBaselineRulelistName.toLocal8Bit().constData(), BEMPX_GetActiveModel(), iCurActiveBEMProcIdx ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										int iResDHWBaseRetVal = LocalEvaluateRuleset( sErrMsg, 69, sResDHWBaselineRulelistName.toLocal8Bit().constData(), bVerbose, pCompRuleDebugInfo );
//											69 : Error evaluating rulelist that converts residential DHW systems to code baseline
										if (iResDHWBaseRetVal != 0 || BEMPX_AbortRuleEvaluation())
											ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 69 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
								}	}
							}
					}	}
				}

				if (BEMPX_GetActiveModel() != iCurActiveBEMProcIdx && !bAbort && !BEMPX_AbortRuleEvaluation())
					BEMPX_SetActiveModel( iCurActiveBEMProcIdx );
			}

		// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model
			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{	// set flag indicating hourly results storage
		//		int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );									assert( iCID_Proj > 0 );
				long lBeginMonth, lBeginDay, lEndMonth, lEndDay, lYear;
				if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodBeginMonth", iCID_Proj ), lBeginMonth ) && lBeginMonth ==  1  &&
						BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodBeginDay",   iCID_Proj ), lBeginDay   ) && lBeginDay   ==  1  && 
						BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodEndMonth",   iCID_Proj ), lEndMonth   ) && lEndMonth   == 12  && 
						BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodEndDay",     iCID_Proj ), lEndDay     ) && lEndDay     == 31  && 
						BEMPX_GetInteger( BEMPX_GetDatabaseID( "RunPeriodYear",       iCID_Proj ), lYear       ) && lYear       > 0  )
					bStoreHourlyResults = true;
				if (bStoreHourlyResults)
				{	if (iLastHrlyStorModelIdx >= 0 && iLastHrlyStorModelIdx < iCurActiveBEMProcIdx)
					{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run into the current model

//			QString sDbgDetailPathFile = QString( "%1dbgCopyResObjs-fromModel%2-%3b4.ibd-Detail" ).arg( sProcessingPath, QString::number( iCurActiveBEMProcIdx), QString::number(iDbgOutFileIdx+1) );
//      	BEMPX_WriteProjectFile( sDbgDetailPathFile.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true,  iCurActiveBEMProcIdx );

						QString sResCopyErrMsg;
						int iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, sRunID.toLocal8Bit().constData(), iLastHrlyStorModelIdx, iCurActiveBEMProcIdx, NULL );  // don't copy nrcc* objects here - was: &saCopyAcrossModelClassPrefixes );  - SAC 11/26/20
						assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
								if (bVerbose)   // SAC 11/04/23
								{  if (iResCopyRetVal > 0)
                           	BEMPX_WriteLogFile( QString( "  PerfAnalysis - error copying results objects from %1 (%2) to %3 (%4):  %5" ).arg( "prior", QString::number(iLastHrlyStorModelIdx), sRunID, QString::number(iCurActiveBEMProcIdx), sResCopyErrMsg ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                           else
                           	BEMPX_WriteLogFile( QString( "  PerfAnalysis - results objects copied from %1 (%2) to %3 (%4)" ).arg( "prior", QString::number(iLastHrlyStorModelIdx), sRunID, QString::number(iCurActiveBEMProcIdx) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }
						if (iResCopyRetVal > 0 &&
							//	((iRun==0 && iDontAbortOnErrorsThruStep < 3) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 6)) )  // check flag to bypass errors
								iDontAbortOnErrorsThruStep < iAnalStep )  // check flag to bypass errors
							iRetVal = (iRetVal > 0 ? iRetVal : iResCopyRetVal);		// DO abort

//// debugging copying of results & NRCC objects from model to model
//			sDbgDetailPathFile = QString( "%1dbgCopyResObjs-fromModel%2-%3.ibd-Detail" ).arg( sProcessingPath, QString::number(iLastHrlyStorModelIdx), QString::number(iDbgOutFileIdx++) );
//      	BEMPX_WriteProjectFile( sDbgDetailPathFile.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, iLastHrlyStorModelIdx );
//			sDbgDetailPathFile = QString( "%1dbgCopyResObjs-fromModel%2-%3.ibd-Detail" ).arg( sProcessingPath, QString::number( iCurActiveBEMProcIdx), QString::number(iDbgOutFileIdx++) );
//      	BEMPX_WriteProjectFile( sDbgDetailPathFile.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true,  iCurActiveBEMProcIdx );

					}
					iLastHrlyStorModelIdx = iCurActiveBEMProcIdx;
				}
			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{	if (plOverrideAutosize[iRun] >= 0)
				{	// OVERRIDE global HVAC autosize flag (if specified in options settings)
			      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "HVACAutoSizing", iCID_Proj ), BEMP_Int, (void*) &plOverrideAutosize[iRun], BEMO_User, 0, BEMS_UserDefined /*???*/ );
					lHVACAutoSizing = plOverrideAutosize[iRun];		// SAC 2/17/20
				}
				else
					BEMPX_GetInteger( BEMPX_GetDatabaseID( "HVACAutoSizing", iCID_Proj ), lHVACAutoSizing );
			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{

// CHECK FOR FILES TO BE WRITTEN DURING ANALYSIS TO BE WRITABLE  (???)

			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{
				QString sProjSDDFile = sProcessingPath + sProjFileAlone + " - " + sRunID + ".xml";
				sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
			                "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
								 "(once the file is closed), or \n'Abort' to abort the %s.", "SDD XML", sProjSDDFile.toLocal8Bit().constData(), "analysis" );
				if (!OKToWriteOrDeleteFile( sProjSDDFile.toLocal8Bit().constData(), sMsg ))
				{	sErrMsg = QString::asprintf( "Analysis aborting - user chose not to overwrite SDD XML file:  %s", sProjSDDFile.toLocal8Bit().constData() );
//										22 : Analysis aborted - user chose not to overwrite SDD XML file
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 22 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
				else if (!BEMPX_WriteProjectFile( sProjSDDFile.toLocal8Bit().constData(), BEMFM_SIM, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/,
															FALSE /*bSupressAllMessageBoxes*/, BEMFT_XML /*iFileType*/ ))
				{	sErrMsg = QString::asprintf( "Error: Unable to write %s model SDD XML file:  %s", sRunIDLong.toLocal8Bit().constData(), sProjSDDFile.toLocal8Bit().constData() );
//										23 : Error: Unable to write SDD XML file
				//	if ((iRun==0 && iDontAbortOnErrorsThruStep < 3) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 6))  // check flag to bypass errors
					if (iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 23 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
				}

			// Generate Rule-Based model reports
				bool bEvalReportRulesFollowingSim = false;
				if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
				{	if (lHVACAutoSizing == 0 || !bCallOpenStudio)
					{
//BEMPX_WriteLogFile( QString::asprintf( "about to process reports (prior to sim) for model:  %s", sProjSDDFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						int iModelReportsRetVal = ProcessModelReports( sProjSDDFile.toLocal8Bit().constData(), lDBID_Proj_RuleReportType, BEMPX_GetDatabaseID( "RuleReportFileAppend", iCID_Proj ),
																						-1, true /*bProcessCurrentSelection*/, saModelReportOptions, bVerboseReportRules /*bVerbose*/, bSilent );
						if (iModelReportsRetVal > 0 && bVerbose)
							BEMPX_WriteLogFile( QString::asprintf( "%d rule-based reports written for model:  %s", iModelReportsRetVal, sProjSDDFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						else if (iModelReportsRetVal < 0)
							// DON'T ABORT ANALYSIS if model report writing fails ???  (just logging message)
							BEMPX_WriteLogFile( QString::asprintf( "Error generating rule-based reports (%d) for model:  %s", iModelReportsRetVal, sProjSDDFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
					else
						bEvalReportRulesFollowingSim = true;
				}

			// continue on processing run...
				bool bForceXMLFileWriteDespiteAbort = false;		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
				if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
				{	SetCurrentDirectory( sProcessingPath.toLocal8Bit().constData() );
					BEMPX_SetupResultRun( iResultRunIdx, sRunIDLong.toLocal8Bit().constData(), sRunID.toLocal8Bit().constData() /* ??? 0 iBEMProcIdx */ );		// SAC 5/10/13

					if (!bCallOpenStudio || !bSimulateModel)
					{	bModelToBeSimulated[iRun] = false;
						// third round of progress dialog setting initialization
						if (iCodeType == CT_T24N)
						{	if (bParallelSimulations)
									SetCECNResProgressVal_Parallel( (iNumRuns > 3 && (bModelToBeSimulated[0] || bModelToBeSimulated[1]) && (bModelToBeSimulated[2] || bModelToBeSimulated[3])), bModelToBeSimulated[0], bModelToBeSimulated[2], bPerformComSim, bPerformFullCSESim );  // SAC 11/19/21
							else	SetCECNResProgressVal_Serial( bModelToBeSimulated[0], bModelToBeSimulated[2], bModelToBeSimulated[1], bModelToBeSimulated[3] );
						}
						else
						{	if (bParallelSimulations)
									SetS901GProgressVal_Parallel( (iNumRuns > 9 && (bModelToBeSimulated[0] || bModelToBeSimulated[1] || bModelToBeSimulated[2] || bModelToBeSimulated[3] || bModelToBeSimulated[4]) &&
																								  (bModelToBeSimulated[5] || bModelToBeSimulated[6] || bModelToBeSimulated[7] || bModelToBeSimulated[8] || bModelToBeSimulated[9])), bModelToBeSimulated[0], bModelToBeSimulated[5] );
							else	SetS901GProgressVal_Serial( bModelToBeSimulated[0], bModelToBeSimulated[5], (bModelToBeSimulated[1] || bModelToBeSimulated[2] || bModelToBeSimulated[3] || bModelToBeSimulated[4]),
																																		 (bModelToBeSimulated[6] || bModelToBeSimulated[7] || bModelToBeSimulated[8] || bModelToBeSimulated[9]) );
						}
					}

	// ----------------------
	//		SIMULATE MODEL
	// ----------------------

					bool baSimPassesUMLHLimits[] = { true, true };
					long lAnalysisType = -1;
					if (!bCallOpenStudio)
					{	BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing OpenStudio (and simulation) for %s model", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

						// SAC 7/23/18 - additional message if bypassing OS will also result in CSE sim being bypassed
						if (bSimulateModel && bStoreHourlyResults)
						{  int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ) );
							int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray" ) );
							if ((!bBypassRecircDHW && iNumRecircDHWSysObjs > 0) || iNumPVArrayObjs > 0)
								BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing CSE simulation as well (due to OpenStudio bypass) for %s model", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
					}
					// else   - replaced 'else' w/ logic to ensure sim of Prop models even when Std models not simulated - SAC 12/17/24
               else
// TO DO - finish this fix - needs to NOT toggle back ON secondary run in pair - SAC 12/18/24
               //if ( bCallOpenStudio ||
               //     (iCodeType == CT_T24N && bParallelSimulations &&
               //      (iRun == 1 || iRun == 3) && bModelToBeSimulated[iRun-1]) )
					{			if (bVerbose)
									BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Calling PerfSim_E+ for %s model", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						if (!bSimulateModel)
							BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing simulation of %s model", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

						int iSimRetVal = 0;
              		QString sEPlusSimErrMsg;
						if (!bAbort && !BEMPX_AbortRuleEvaluation())
						{	//QString sSimWeatherPath = esDataPath + "EPW\\";

					// ENERGYPLUS SIMULATION
							if (!sIDFToSimulate.isEmpty())
							{	if (sExcptDsgnModelFile.isEmpty())
									BEMPX_WriteLogFile( QString::asprintf( "    SIMULATING FIXED IDF FILE:  %s", sIDFToSimulate.toLocal8Bit().constData() ) );
								else
									BEMPX_WriteLogFile( QString::asprintf( "    SIMULATING FIXED IDF FILE (for runs other than annual proposed):  %s", sIDFToSimulate.toLocal8Bit().constData() ) );
							}
							QString sProjSDDFileNoPath = sProjSDDFile.right( sProjSDDFile.length() - sProjSDDFile.lastIndexOf('\\') - 1 );
							dTimeToOther += DeltaTime( tmAnalOther );		// log time spent prior to this point to "other" bucket
//				// SAC 4/18/14 - logic to SKIP certain simulations and simulate them with the FOLLOWING run
							bModelToBeSimulated[iRun] = true;
//							bThisOSSimSkipped = (bParallelSimulations && !bLastOSSimSkipped && bSimulateModel && iNumRuns > 3 && (iRun==0 || iRun==2));
							QString sLocalIDFToSim = (!sExcptDsgnModelFile.isEmpty() && ((iCodeType == CT_T24N && iRun == 2) || (iCodeType != CT_T24N && iRun == 5))) ? sExcptDsgnModelFile : sIDFToSimulate;	// SAC 12/19/14 - use sExcptDsgnModelFile for annual proposed run (if specified)

							bool bIsDsgnSim = ((iCodeType == CT_T24N && iRun < 2) || (iCodeType != CT_T24N && iRun < 5));
							osRunInfo[iSimRunIdx].InitializeRunInfo( NULL, iRun, sProjSDDFileNoPath.toLocal8Bit().constData(), sRunID.toLocal8Bit().constData(), sRunIDLong.toLocal8Bit().constData(),
																					((iCodeType == CT_T24N && iRun > 2) || (iCodeType != CT_T24N && iRun > 5)) /*bIsStdRun*/,
																					(bIsDsgnSim || lHVACAutoSizing > 0) /*bPostEquipCapsToBEMBase*/,		// SAC 2/17/20 - PostEquipCapsToBEMBase if lHVACAutoSizing
																					bSimulateModel, iCurActiveBEMProcIdx, sLocalIDFToSim.toLocal8Bit().constData(), CT_T24N /*iCodeType*/,
																					false /*bSimOutVarsCSV*/, bEvalReportRulesFollowingSim );

#pragma warning(disable:4996)
						// SAC 8/19/15 - setup "multiple" simulation input data
							strncpy( osSimInfo[iSimRunIdx].pszSDDFile, osRunInfo[iSimRunIdx].SDDFile().toLocal8Bit().constData(), FILENAME_MAX-1 );
							if (osRunInfo[iSimRunIdx].IDFToSimulate().length() > 0)
								strncpy( osSimInfo[iSimRunIdx].pszIDFToSimulate, osRunInfo[iSimRunIdx].IDFToSimulate().toLocal8Bit().constData(), FILENAME_MAX-1 );
							else
								osSimInfo[iSimRunIdx].pszIDFToSimulate[0] = '\0';
							strncpy( osSimInfo[iSimRunIdx].pszRunID    , osRunInfo[iSimRunIdx].RunID().toLocal8Bit().constData()    , 31 );
							strncpy( osSimInfo[iSimRunIdx].pszLongRunID, osRunInfo[iSimRunIdx].LongRunID().toLocal8Bit().constData(), 63 );
#pragma warning(default:4996)
							osSimInfo[iSimRunIdx].bIsStdRun						= osRunInfo[iSimRunIdx].IsStdRun();
							osSimInfo[iSimRunIdx].bPostEquipCapsToBEMBase	= osRunInfo[iSimRunIdx].PostEquipCapsToBEMBase();
							osSimInfo[iSimRunIdx].bSimulateModel				= osRunInfo[iSimRunIdx].SimulateModel();
							osSimInfo[iSimRunIdx].iBEMProcIdx					= osRunInfo[iSimRunIdx].BEMProcIdx();
							osSimInfo[iSimRunIdx].iOrientationIdx				= 0;		// 90.1 only
							osSimInfo[iSimRunIdx].iRunIdx							= iRun;
                     if (osRunInfo[iSimRunIdx].RunID().compare("ap") == 0)       // SAC 09/09/22 (CUAC)
                        iCUAC_BEMProcIdx = osRunInfo[iSimRunIdx].BEMProcIdx();
							// SAC 4/12/16 - integrate bSimOutVarsCSV initialization so that multi-orient runs work w/out INI toggle for each orientation
							if (iCodeType == CT_T24N)
							{	switch (osRunInfo[iSimRunIdx].OSRunIdx())		// SAC 5/27/15 - new progress reporting mods
								{	case  0 :	iProgressModel = BCM_NRP_Model_zp;		osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 0 ] > 0);		break;
									case  1 :	iProgressModel = BCM_NRP_Model_zb;		osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 1 ] > 0);		break;
									case  2 :	iProgressModel = BCM_NRP_Model_ap;		osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 2 ] > 0);		break;
									case  3 :	iProgressModel = BCM_NRP_Model_ab;		osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 3 ] > 0);		break;
							}	}
							else
							{	switch (osRunInfo[iSimRunIdx].OSRunIdx())
								{	case  0 :	iProgressModel = BCM_NRAP_Model_zp;		osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 0 ] > 0);		break;
									case  1 :	iProgressModel = BCM_NRAP_Model_zb1;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 1 ] > 0);		break;
									case  2 :	iProgressModel = BCM_NRAP_Model_zb2;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 1 ] > 0);		break;
									case  3 :	iProgressModel = BCM_NRAP_Model_zb3;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 1 ] > 0);		break;
									case  4 :	iProgressModel = BCM_NRAP_Model_zb4;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 1 ] > 0);		break;
									case  5 :	iProgressModel = BCM_NRAP_Model_ap ;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 2 ] > 0);		break;
									case  6 :	iProgressModel = BCM_NRAP_Model_ab1;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 3 ] > 0);		break;
									case  7 :	iProgressModel = BCM_NRAP_Model_ab2;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 3 ] > 0);		break;
									case  8 :	iProgressModel = BCM_NRAP_Model_ab3;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 3 ] > 0);		break;
									case  9 :	iProgressModel = BCM_NRAP_Model_ab4;	osSimInfo[iSimRunIdx].bSimOutVarsCSV = (plSimOutputVariablesToCSV[ 3 ] > 0);		break;
							}	}

							osSimInfo[iSimRunIdx].iProgressModel = iProgressModel;
							iProgressModelSum += iProgressModel;

                     // RESET bSimRunsNow flag in cases where second of parallel runs toggled OFF - SAC 06/26/23
                     if (!bSimRunsNow && bParallelSimulations)
                     {  if (iCodeType == CT_T24N)
                           bSimRunsNow = ( (iRun == 1 && bModelToBeSimulated[0] && !bResearchMode) ||    // zp & zb
                                           (iRun == 3 && bModelToBeSimulated[2]) );                      // ap & ab
                        else
                           bSimRunsNow = ( (iRun == 1 && bModelToBeSimulated[0] && !bResearchMode) ||    // zp & zb*
                                           (iRun == 9 && bModelToBeSimulated[5]) );                      // ap & ab*
                     }

// didn't work because actual sim & results retrieval done on DIFFERENT array of osRunInfo[] - SAC 10/29/21 (MFam)
//BEMPX_WriteLogFile( QString( "  PerfAnal_NRes - iSimRunIdx %1, bPerformComSim %2, bPerformFullCSESim %3, bStoreHourlyResults %4" ).arg( QString::number(iSimRunIdx), (bPerformComSim ? "true" : "false"), (bPerformFullCSESim ? "true" : "false"), (bStoreHourlyResults ? "true" : "false") ), NULL, FALSE, TRUE, FALSE );
//                     if (!bPerformComSim && bPerformFullCSESim && bStoreHourlyResults)
//                        osRunInfo[iSimRunIdx].SetStoreHourlyResults( true );    // make sure HourlyResults toggled ON for runs where we are skipping E+ but simulating CSE - SAC 10/29/21 (MFam)
//BEMPX_WriteLogFile( QString( "  PerfAnal_NRes - osRunInfo[%1].m_bStoreHourlyResults = %2" ).arg( QString::number(iSimRunIdx), (osRunInfo[iSimRunIdx].StoreHourlyResults() ? "true" : "false") ), NULL, FALSE, TRUE, FALSE );

//							if (bThisOSSimSkipped)
//							{ }	// do nothing here
//							else
							if (bSimRunsNow)
							{	if (bIsDsgnSim)
//										iNumDsgnSims += ((osRunInfo[0].OSRunIdx() > -1 && osRunInfo[1].OSRunIdx() > -1) ? 2 : 1);
//								else	iNumAnnSims  += ((osRunInfo[0].OSRunIdx() > -1 && osRunInfo[1].OSRunIdx() > -1) ? 2 : 1);
										iNumDsgnSims += (iSimRunIdx + 1);
								else	iNumAnnSims  += (iSimRunIdx + 1);

								OSWrapLib osWrap;		// SAC 7/23/18 - added when spliting results processing allowing for CSE simulations following E+
								COSRunInfo osRunInfo[MultEPlusSim_MaxSims];

      						// CSE Simulation info ----- 
                        int iSR=0;
                        QString   qsCSESimStatusMsg[MultEPlusSim_MaxSims];
                        QString* pqsCSESimStatusMsg[MultEPlusSim_MaxSims];
                        long lCSE_ExcludePVBattFromSim[MultEPlusSim_MaxSims];
		                  for (; iSR < MultEPlusSim_MaxSims; iSR++)
		                  {  pqsCSESimStatusMsg[iSR] = &qsCSESimStatusMsg[iSR];
                           lCSE_ExcludePVBattFromSim[iSR] = -1;
                        }
                        bool bPVBattExcludedFromRound1 = false;
                        long lDBID_Proj_ExcludePVBattFromSim = BEMPX_GetDatabaseID( "CSE_ExcludePVBattFromSim", iCID_Proj );
                        long lDBID_Proj_SimPVBattOnly        = BEMPX_GetDatabaseID( "CSE_SimPVBattOnly",        iCID_Proj );
                        long lHaveStandaloneBatt=0, lDBID_Proj_HaveStandaloneBatt = BEMPX_GetDatabaseID( "HaveStandaloneBatt", iCID_Proj );     // SAC 05/26/22
                        long lDBID_ResProj_HVACSizingNeeded  = BEMPX_GetDatabaseID( "ResProj:HVACSizingNeeded" );
								QString sStdDsgnCSEResultsPathFile;		// added to fix bug in Flexibility credit calcs - SAC 10/8/20 (tic #3218)
                        bool bSecureT24NRptGenActivated = (iCodeType == CT_T24N && bSendRptSignature && (bComplianceReportPDF || bComplianceReportXML || bComplianceReportStd) &&
															!sXMLResultsFileName.isEmpty() && iAnalysisThruStep >= 8 && sIDFToSimulate.isEmpty() && iDLLCodeYear == iRulesetCodeYear && !bBypassInputChecks &&
															!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] && !bBypassUMLHChecks && !bBypassCheckSimRules && 
															plOverrideAutosize[0] == -1 && plOverrideAutosize[1] == -1 && plOverrideAutosize[2] == -1 && plOverrideAutosize[3] == -1 && !bBypassCheckCodeRules && 
															lQuickAnalysis <= 0 && !bIgnoreFileReadErrors && !bBypassValidFileChecks && sDevOptsNotDefaulted.isEmpty() && sExcptDsgnModelFile.isEmpty() &&
															lNumSpaceWithDefaultedDwellingUnitArea < 1 && !bBypassPreAnalysisCheckRules);

      						// CSE Simulation Loop #1 ----- 
                        bool bCSEHVACSizingSimulationsPerformed = false;
                        if (bPerformFullCSESim && lDBID_Proj_ExcludePVBattFromSim > 0 && lDBID_Proj_SimPVBattOnly > 0 &&
                            (bStoreHourlyResults || lDBID_ResProj_HVACSizingNeeded > 0))
                        {  bool bPerformSimLoop1 = bStoreHourlyResults;
                           for (iSR=0; (iSR <= iSimRunIdx && !bPerformSimLoop1); iSR++)	// loop over runs in search for any requiring HVAC sizing runs
                           {  if (posSimInfo[iSR]->bSimulateModel)
                              {  long lCSEHVACSizingReqd = 0;
                                 if (BEMPX_GetInteger( lDBID_ResProj_HVACSizingNeeded, lCSEHVACSizingReqd, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx ) &&
                                     lCSEHVACSizingReqd > 0)
                                 {  bPerformSimLoop1 = true;
                                    bCSEHVACSizingSimulationsPerformed = true;
                                          if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 1 - CSE sizing reqd for '%s' model", posSimInfo[iSR]->pszRunID ) );
                                 }
                                 else if (bLogCSERunLoopDetails)    // SAC 06/26/23
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 1 - CSE sizing ResProj:HVACSizingNeeded flag False for '%s' model", posSimInfo[iSR]->pszRunID ) );
                              }
                              else if (bLogCSERunLoopDetails)    // SAC 06/26/23
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 1 - CSE sizing bSimulateModel flag False for '%s' model", posSimInfo[iSR]->pszRunID ) );
                           }
                           if (bStoreHourlyResults || bPerformSimLoop1)
                           {  for (iSR=0; iSR <= iSimRunIdx; iSR++)	// loop over runs to ensure no PV/Batt simulations performed this round
                                 if (posSimInfo[iSR]->bSimulateModel)
                                 {  int iNumPVArrayObjs  = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray" ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
                                    int iNumBattObjs     = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "Batt"    ), BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
                                    if (lDBID_Proj_HaveStandaloneBatt > 0)    // SAC 05/26/22
                                       BEMPX_GetInteger( lDBID_Proj_HaveStandaloneBatt, lHaveStandaloneBatt, 0, -1, 0, BEMO_User, posSimInfo[iSR]->iBEMProcIdx );
                                    if ((iNumPVArrayObjs > 0 || lHaveStandaloneBatt > 0) && iNumBattObjs > 0)
                                    {  bPVBattExcludedFromRound1 = true;
                                       lCSE_ExcludePVBattFromSim[iSR] = 1;
                                       BEMPX_SetBEMData( lDBID_Proj_ExcludePVBattFromSim, BEMP_Int, (void*) &lOne, BEMO_User, 0, BEMS_UserDefined /*???*/, BEMO_User, 1, posSimInfo[iSR]->iBEMProcIdx );
                                          if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 1 - PV/Batt excluded from '%s' model sim", posSimInfo[iSR]->pszRunID ) );
                                    }
                                 }
                              CSERunLoop( iSimRunIdx, posSimInfo, pqsCSESimStatusMsg, bStoreHourlyResults, sProcessingPath, sModelPathOnly, sModelFileOnly, bSecureT24NRptGenActivated,
                                             bPerformFullCSESim, bBypassRecircDHW, lNumPVArraysChk, bEnablePVBattSim, pszUIVersionString,
                                             sCSEexe, sCSEEXEPath, qsCSEName, sAnnualWeatherFile,
                                             iCodeType, iRulesetCodeYear, lAnalysisType, iDontAbortOnErrorsThruStep, iAnalStep, bProposedOnly, bStoreBEMDetails,
                                             bSilent, bVerbose, bResearchMode, pCompRuleDebugInfo, sCSEIncludeFileDBID, sCSEVersion, pszErrorMsg, iErrorMsgLen,
                                             bAbort, iRetVal, sErrMsg, sStdDsgnCSEResultsPathFile, iCUACReportID, iCustomMeterOption );
                           }
                           else if (bLogCSERunLoopDetails)    // SAC 06/26/23
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 1 - CSE sizing not performed for '%s' model (bStoreHourlyResults %s, bPerformSimLoop1 %s)", posSimInfo[iSR]->pszRunID, (bStoreHourlyResults ? "true" : "false"), (bPerformSimLoop1 ? "true" : "false") ) );
                        }

                           //BEMMessageBox( QString::asprintf( "Pause following first CSE run loop:  bPerformFullCSESim %s / bStoreHourlyResults %s / lDBID_Proj_ExcludePVBattFromSim %ld / lDBID_Proj_SimPVBattOnly %ld",
                           //                                      (bPerformFullCSESim ? "true" : "false"), (bStoreHourlyResults ? "true" : "false"), lDBID_Proj_ExcludePVBattFromSim, lDBID_Proj_SimPVBattOnly ) );

                        if ( (iRetVal != 0 && iRetVal != iSimRetVal) ||    // ensure errant RetVal prevents further sims - SAC 09/26/23
                             bSimulateCSEOnly )		// SAC 3/10/20 - added logic to SKIP E+ and move directly onto CSE simulation...
									iSimRetVal = iRetVal;   // switch from 0 to iRetVal so that failed CSE sim above prevents subsequent rule eval & analysis - SAC 06/26/23
								else
                        {
                           // make sure to DELETE existing CSE LoadPassing CSV schedule files before E+ simulation(s) - SAC 03/30/22
                           long lDBID_Proj_CSE_LoadPassingExportFileName = BEMPX_GetDatabaseID( "Proj:CSE_LoadPassingExportFileName" );
                           QString sLoadPassingExportFile;
                           for (iSR=0; (lDBID_Proj_CSE_LoadPassingExportFileName > 0 && iSR <= iSimRunIdx); iSR++)	// loop over runs to be simulated this round
                              if (posSimInfo[iSR]->bSimulateModel &&
                                  BEMPX_GetString( lDBID_Proj_CSE_LoadPassingExportFileName, sLoadPassingExportFile, FALSE, 0, -1, 0, BEMO_User, NULL, 0, posSimInfo[iSR]->iBEMProcIdx ) &&
                                  !sLoadPassingExportFile.isEmpty())
                              {
                                 sLoadPassingExportFile = sProcessingPath + QString("files\\") + sLoadPassingExportFile;
                                 QString sFileDelMsg = QString( "The %1 file '%2' is opened in another application.  This file must be closed in that "
                                                                "application before an updated file can be written.\n\nSelect 'Retry' to proceed "
                                                                "(once the file is closed), or \n'Abort' to abort the analysis." ).arg( "load-passing CSV", sLoadPassingExportFile );
                                 if (!OKToWriteOrDeleteFile( sLoadPassingExportFile.toLocal8Bit().constData(), sFileDelMsg, bSilent ))
                                 {  sErrMsg = QString::asprintf( "Error: Unable to overwrite CSE load-passing CSV file:  %s", sLoadPassingExportFile.toLocal8Bit().constData() );
                                       //							90 : Unable to open/delete/write CSE load-passing CSV file from prior E+ simulation
                                    if (iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
                                       ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 23 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
                                 }
                                 else if (FileExists( sLoadPassingExportFile.toLocal8Bit().constData() ))
                                 {
                                    DeleteFile( sLoadPassingExportFile.toLocal8Bit().constData() );
                                    if (bVerbose)
                                       BEMPX_WriteLogFile( QString::asprintf( "      just deleted prior CSE load-passing CSV file used as E+ schedule:  %s", sLoadPassingExportFile.toLocal8Bit().constData() ) );
                                 }
                                       //   else
                                       //      BEMPX_WriteLogFile( QString::asprintf( "      prior CSE load-passing CSV file used as E+ schedule NOT FOUND:  %s", sLoadPassingExportFile.toLocal8Bit().constData() ) );
                              }

                                 //  BEMMessageBox( "Pausing before E+ simulation(s)" );
								//	iSimRetVal = CMX_PerformSimulation_EnergyPlus_Multiple(	sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
									iSimRetVal = PerformSimulation_EnergyPlus_Multiple( osWrap, &osRunInfo[0], sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
																					sProcessingPath.toLocal8Bit().constData(), sModelkitPath.toLocal8Bit().constData(), posSimInfo, iSimRunIdx+1, 
																			// remaining general arguments
																					bVerbose, FALSE /*bDurationStats*/, &dTimeToTranslate[iNumTimeToTranslate++],
																					(bIsDsgnSim ? &dTimeToSimDsgn[iNumTimeToSimDsgn++] : &dTimeToSimAnn[iNumTimeToSimAnn++]),
																					iSimulationStorage, &dEPlusVer, pszEPlusVerStr, 60, pszOpenStudioVerStr, 60 , iCodeType,
																					false /*bIncludeOutputDiagnostics*/, iProgressType, bUseEPlusRunMgr, (!bPerformComSim) );		// SAC 5/27/15   // SAC 2/15/19    // SAC 10/29/21 (MFam)

										if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Back from PerfSim_E+ (%s model, %d return value)", sRunID.toLocal8Bit().constData(), iSimRetVal ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }

							   // moved some post-E+ processing into if (bSimRunsNow) statement
								tmAnalOther = boost::posix_time::microsec_clock::local_time();		// reset timer for "other" bucket

								if (/*bSimRunsNow &&*/ iSimRetVal == 0 && bIsDsgnSim)		// SAC 4/1/14
									for (iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
										bSizingRunSimulated[osSimInfo[iSimRun].iRunIdx] = TRUE;

								if (/*bSimRunsNow &&*/ (iSimRetVal == 0 || iSimRetVal == OSI_SimEPlus_UserAbortedAnalysis))
									for (iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
										saSimulatedRunIDs.push_back( osRunInfo[iSimRun].RunID() );

                           //BEMMessageBox( "Pausing before second CSE run loop" );

      						// CSE Simulation Loop #2 ----- 
                        if ( ( bPerformFullCSESim && bStoreHourlyResults && lDBID_Proj_ExcludePVBattFromSim > 0 &&
                               lDBID_Proj_SimPVBattOnly > 0 && !bPVBattExcludedFromRound1) ||
                             bCSEHVACSizingSimulationsPerformed )
                        {  // no CSE simulation here, because entire model(s) already simulated (in CSE) above in round 1 
                                          if (bLogCSERunLoopDetails)    // SAC 05/24/22
                                             BEMPX_WriteLogFile( QString::asprintf( "    CSE run loop 2 - skipping CSE model sim(s) due to sizing performed and/or PV/Batt included in run loop 2" ) );
                        }
                        else if (iSimRetVal == 0)     // only when iSimRetVal 0 - SAC 09/26/23
                        {  for (iSR=0; iSR <= iSimRunIdx; iSR++)	// loop over runs to ensure ONLY necessary simulations performed this round 
                           {  if (posSimInfo[iSR]->bSimulateModel && lCSE_ExcludePVBattFromSim[iSR] > 0)
                              {  // reset flags to ensure ONLY PV/Batt simulations performed this round (when excluded above)
                                 BEMPX_SetBEMData( lDBID_Proj_ExcludePVBattFromSim, BEMP_Int, (void*) &lZero, BEMO_User, 0, BEMS_UserDefined /*???*/, BEMO_User, 1, posSimInfo[iSR]->iBEMProcIdx );
                                 BEMPX_SetBEMData( lDBID_Proj_SimPVBattOnly,        BEMP_Int, (void*) &lOne,  BEMO_User, 0, BEMS_UserDefined /*???*/, BEMO_User, 1, posSimInfo[iSR]->iBEMProcIdx );
                              }
                              else if (posSimInfo[iSR]->bSimulateModel && lCSE_ExcludePVBattFromSim[iSR] < 0)
                              {  // full model should have been simulated above, so tweak flags to prevent simulation in this round
                                 BEMPX_SetBEMData( lDBID_Proj_ExcludePVBattFromSim, BEMP_Int, (void*) &lOne,            BEMO_User, 0, BEMS_UserDefined /*???*/, BEMO_User, 1, posSimInfo[iSR]->iBEMProcIdx );
                                 long lSimPVBattOnly = (!bPerformFullCSESim && bPerformCSEDHWSim ? 0 : 1);     // SAC 03/07/22 (MFam)
                                 BEMPX_SetBEMData( lDBID_Proj_SimPVBattOnly,        BEMP_Int, (void*) &lSimPVBattOnly,  BEMO_User, 0, BEMS_UserDefined /*???*/, BEMO_User, 1, posSimInfo[iSR]->iBEMProcIdx );
                              }
                           }
                           CSERunLoop( iSimRunIdx, posSimInfo, pqsCSESimStatusMsg, bStoreHourlyResults, sProcessingPath, sModelPathOnly, sModelFileOnly, bSecureT24NRptGenActivated,
                                          bPerformFullCSESim, bBypassRecircDHW, lNumPVArraysChk, bEnablePVBattSim, pszUIVersionString,
                                          sCSEexe, sCSEEXEPath, qsCSEName, sAnnualWeatherFile,
                                          iCodeType, iRulesetCodeYear, lAnalysisType, iDontAbortOnErrorsThruStep, iAnalStep, bProposedOnly, bStoreBEMDetails,
                                          bSilent, bVerbose, bResearchMode, pCompRuleDebugInfo, sCSEIncludeFileDBID, sCSEVersion, pszErrorMsg, iErrorMsgLen,
                                          bAbort, iRetVal, sErrMsg, sStdDsgnCSEResultsPathFile, iCUACReportID, iCustomMeterOption );
                           if (iRetVal != 0 && iRetVal != iSimRetVal)    // ensure errant RetVal prevents further sims - SAC 09/26/23
		   							iSimRetVal = iRetVal;  
                        }
                        // store CSE run summaries
                        for (iSR=0; iSR <= iSimRunIdx; iSR++)	// loop over runs just simulated in CSE above
                           if (!qsCSESimStatusMsg[iSR].isEmpty())
                              osRunInfo[iSR].AddToSimStatusMsg( qsCSESimStatusMsg[iSR] );

							   // processing of analysis results following ALL simulations - SAC 7/23/18
								if (iSimRetVal == 0 && !bSimulateCSEOnly)
								{
                              // debugging PV-solar
                              //BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), about to call ProcessSimulationResults_Multiple() for %1 run(s)" ).arg( QString::number( iSimRunIdx ) ), NULL, FALSE, TRUE, FALSE );
                              //BEMPX_WriteLogFile( QString( "   in CMX_PerformAnalysisCB_NonRes(), about to call ProcessSimulationResults_Multiple()" ), NULL, FALSE, TRUE, FALSE );
									iSimRetVal = ProcessSimulationResults_Multiple(	osWrap, &osRunInfo[0], sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
																				sProcessingPath.toLocal8Bit().constData(), posSimInfo, iSimRunIdx+1, 
																		// remaining general arguments
																				bVerbose, FALSE /*bDurationStats*/, &dTimeToTranslate[iNumTimeToTranslate++],
																				(bIsDsgnSim ? &dTimeToSimDsgn[iNumTimeToSimDsgn++] : &dTimeToSimAnn[iNumTimeToSimAnn++]),
																				iSimulationStorage, &dEPlusVer, pszEPlusVerStr, 60, pszOpenStudioVerStr, 60 , iCodeType,
																				false /*bIncludeOutputDiagnostics*/, iProgressType, &saEPlusProcDirsToBeRemoved, bReportAllUMLHZones,		// SAC 5/22/19   // SAC 11/11/19
																				&sStdDsgnCSEResultsPathFile, &saCopyAcrossModelClassPrefixes, pCompRuleDebugInfo, 	// SAC 10/8/20 (tic #3218)   // SAC 11/24/20   // SAC 04/14/21
                                                            bPerformComSim /*bRptMissingEPFiles*/ );    // SAC 10/29/21 (MFam)

                              //// debugging copying of results & NRCC objects from model to model
                              //	for (int iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
                              //		if (osSimInfo[iSimRun].iRunIdx > -1 && osSimInfo[iSimRun].iRunIdx < 4 &&
                              //				plExportHourlyResults[ osSimInfo[iSimRun].iRunIdx ] > 0)
                              //		{	QString sDbgDetailPathFile = sProcessingPath;
                              //			sDbgDetailPathFile += osRunInfo[iSimRun].SDDFile();								assert( sDbgDetailPathFile.lastIndexOf('.') > 0 );
                              //			if (sDbgDetailPathFile.lastIndexOf('.') > 0)
                              //				sDbgDetailPathFile = sDbgDetailPathFile.left( sDbgDetailPathFile.lastIndexOf('.') );
                              //			sDbgDetailPathFile += QString(" - dbg-%1.ibd-Detail").arg( QString::number(iDbgOutFileIdx++) );
                              //      	BEMPX_WriteProjectFile( sDbgDetailPathFile.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, osSimInfo[iSimRun].iBEMProcIdx );
                              //      }
								}

                        // store CustomMeter results AFTER other results retrieval and creation/population of EUseSummary object - SAC 11/03/23
                        if (iSimRetVal == 0 && iCustomMeterOption == 1 && !bCustomMeterResultsStored)
                        {  char szCustMtr1ErrMsg[256];      szCustMtr1ErrMsg[0] = '\0';
                           int iPropRunBEMProcIdx = BEMPX_GetTransformIndex( "ap" );
                           int iStdRunBEMProcIdx  = BEMPX_GetTransformIndex( "ab" );
                           if ( iPropRunBEMProcIdx >= 0 && BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iPropRunBEMProcIdx ) > 0 &&
                                 (iStdRunBEMProcIdx < 0 || BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iStdRunBEMProcIdx  ) < 1) )
                              iStdRunBEMProcIdx = iPropRunBEMProcIdx;
                           if (iPropRunBEMProcIdx >= 0 && iStdRunBEMProcIdx >= 0 && BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iStdRunBEMProcIdx ) > 0)
                           // if (iPropRunBEMProcIdx >= 0 && BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iPropRunBEMProcIdx ) > 0)
                           {
                                    // int iNumPropEUseSums = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iPropRunBEMProcIdx );
                                    // int iNumStdEUseSums  = (iStdRunBEMProcIdx < 0 ? -1 : BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, iStdRunBEMProcIdx ));
                                    // BEMPX_WriteLogFile( QString( "         CustomMeter results storage: iPropRunBEMProcIdx %1 (%2 EUseSumms) / iStdRunBEMProcIdx %3 (%4 EUseSumms)" ).arg( QString::number(iPropRunBEMProcIdx), QString::number(iNumPropEUseSums), QString::number(iStdRunBEMProcIdx), QString::number(iNumStdEUseSums) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              long lNumDwellingUnits = 0;
                              BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResProj:NumDwellingUnits" ), lNumDwellingUnits, 0, -1, 0, BEMO_User, iPropRunBEMProcIdx );
                              long lDBID_EUseSum_CSEMeterNames_ap = BEMPX_GetDatabaseID( "EUseSummary:CSEMeterNames_ap" );
                              long lDBID_EUseSum_CSEMeterResults_ap[] = { BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_1" ), BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_2" ),
                                                                          BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_3" ), BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_4" ),
                                                                          BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_5" ), BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_6" ),
                                                                          BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_7" ), BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_8" ), 0 };
                              if (lDBID_EUseSum_CSEMeterNames_ap > 0 && lDBID_EUseSum_CSEMeterResults_ap[0] > 0 && lNumDwellingUnits > 0)
                              {  int iMtr=-1;
                                 while (pszCust1Meters_Unique[++iMtr] && lDBID_EUseSum_CSEMeterResults_ap[iMtr] > 0)
                                 {  int iEnduse=0;
                                    BEMPX_SetBEMData( lDBID_EUseSum_CSEMeterNames_ap+iMtr, BEMP_Str, (void*) pszCust1Meters_Unique[iMtr], BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, iStdRunBEMProcIdx );
                                    szCustMtr1ErrMsg[0] = '\0';
                                    double dCustMtrSum = BEMPX_GetHourlyResultSum( szCustMtr1ErrMsg, 256, "Proposed" /*sRunID.toLocal8Bit().constData()*/, 
		      																		                  pszCust1Meters_Unique[iMtr], pszCSEEnduseListALL[0], NULL, NULL,
                                                                                    NULL, NULL, NULL, NULL, NULL, iPropRunBEMProcIdx /*posSimInfo[iSR]->iBEMProcIdx*/ );
                                    if (strlen( szCustMtr1ErrMsg ) < 1 && dCustMtrSum != 0.0)
                                    {  // store annual energy use by ResDwell sums to EUseSummary object

                                                         //double dCustMtrSum = BEMPX_GetHourlyResultSum( szCustMtr1ErrMsg, 256, sRunID.toLocal8Bit().constData(), 
																			//	                                               pszCust1Meters_Unique[iMtr], pszCSEEnduseListALL[iEnduse], NULL, NULL,
                                                         //                                                  NULL, NULL, NULL, NULL, NULL, iPropRunBEMProcIdx );
                                                            do
                                                            {  if (iEnduse > 0)
                                                               {  szCustMtr1ErrMsg[0] = '\0';
                                                                  dCustMtrSum = BEMPX_GetHourlyResultSum( szCustMtr1ErrMsg, 256, "Proposed" /*sRunID.toLocal8Bit().constData()*/, 
																				                                               pszCust1Meters_Unique[iMtr], pszCSEEnduseListALL[iEnduse], NULL, NULL,
                                                                                                           NULL, NULL, NULL, NULL, NULL, iPropRunBEMProcIdx );
                                                               }
                                                               if (strlen( szCustMtr1ErrMsg ) < 1 && dCustMtrSum != 0.0)
                                                                  dCustMtrSum /= lNumDwellingUnits;
                                                               else
                                                                  dCustMtrSum = 0.0;
                                                                        // BEMPX_WriteLogFile( QString( "         %1 %2: %3 (per dwelling)" ).arg( pszCust1Meters_Unique[iMtr], pszCSEEnduseListALL[iEnduse], QString::number(dCustMtrSum) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                               BEMPX_SetBEMData( lDBID_EUseSum_CSEMeterResults_ap[iMtr]+iEnduse, BEMP_Flt, &dCustMtrSum, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, iStdRunBEMProcIdx );
                                                            } while (pszCSEEnduseListALL[++iEnduse] != NULL);
                                    }
                                    else
                                    {  dCustMtrSum = 0.0;
                                       do
                                       {  BEMPX_SetBEMData( lDBID_EUseSum_CSEMeterResults_ap[iMtr]+iEnduse, BEMP_Flt, &dCustMtrSum, BEMO_User, 0, BEMS_UserDefined, BEMO_User, TRUE, iStdRunBEMProcIdx );
                                       } while (pszCSEEnduseListALL[++iEnduse] != NULL);
                                    }
                                 }
                                 if (iMtr > 1)
                                    bCustomMeterResultsStored = true;   // SAC 11/04/23
                              }
                                                   //if (strlen(szCustMtr1ErrMsg) > 0)
                                                   //   BEMPX_WriteLogFile( QString( "      %1" ).arg( szCustMtr1ErrMsg ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                        }  }

							}	// end of: if (bSimRunsNow)


						// Generate Rule-Based model reports - second round FOLLOWING simulation & results retrieval (when lHVACAutoSizing)
							if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation() && bSimRunsNow && iSimRetVal == 0)		// SAC 2/18/20
							{	int iRptStoreActiveModel = BEMPX_GetActiveModel();
								for (int iRptRun=0; iRptRun < iSimRunIdx+1; iRptRun++)
									if (osRunInfo[iRptRun].EvalReportRulesFollowingSim())
									{
										BEMPX_SetActiveModel( osSimInfo[iRptRun].iBEMProcIdx );
										QString sSDDPathFile = sProcessingPath + osRunInfo[iRptRun].SDDFile();
//BEMPX_WriteLogFile( QString::asprintf( "about to process reports (following sim) for model:  %s", sSDDPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										int iModelReportsRetVal = ProcessModelReports( sSDDPathFile.toLocal8Bit().constData(), lDBID_Proj_RuleReportType, BEMPX_GetDatabaseID( "RuleReportFileAppend", iCID_Proj ),
																										-1, true /*bProcessCurrentSelection*/, saModelReportOptions, bVerboseReportRules /*bVerbose*/, bSilent );
										if (iModelReportsRetVal > 0 && bVerbose)
											BEMPX_WriteLogFile( QString::asprintf( "%d rule-based reports written for model:  %s", iModelReportsRetVal, osRunInfo[iRptRun].SDDFile().toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										else if (iModelReportsRetVal < 0)
											// DON'T ABORT ANALYSIS if model report writing fails ???  (just logging message)
											BEMPX_WriteLogFile( QString::asprintf( "Error generating rule-based reports (%d) for model:  %s", iModelReportsRetVal, osRunInfo[iRptRun].SDDFile().toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
								BEMPX_SetActiveModel( iRptStoreActiveModel );
							}


						// SAC 8/21/14 - added export of hourly results CSV
							if (bSimRunsNow && iSimRetVal == 0 && !bIsDsgnSim)
							{	for (iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
								{	if (osSimInfo[iSimRun].iRunIdx > -1 && osSimInfo[iSimRun].iRunIdx < 4 &&
											plExportHourlyResults[ osSimInfo[iSimRun].iRunIdx ] > 0)
									{	QString sHrlyResExportPathFile = sProcessingPath;
										sHrlyResExportPathFile += osRunInfo[iSimRun].SDDFile();								assert( sHrlyResExportPathFile.lastIndexOf('.') > 0 );
										if (sHrlyResExportPathFile.lastIndexOf('.') > 0)
											sHrlyResExportPathFile = sHrlyResExportPathFile.left( sHrlyResExportPathFile.lastIndexOf('.') );
										sHrlyResExportPathFile += " - HourlyResults.csv";
										char pszHrlyResErrMsgBuffer[512];  pszHrlyResErrMsgBuffer[0]=0;
                              QString qsHrlyRptModelName = osRunInfo[iSimRun].LongRunID();      // replace 'Standard' w/ 'Baseline' for CalPRM runs - SAC 10/29/23
                              if (lIsCalPRM && !qsHrlyRptModelName.compare( "Standard" ))
                                 qsHrlyRptModelName = "Baseline";
										int iHrlyResExportRetVal = CMX_ExportCSVHourlyResults_Com( sHrlyResExportPathFile.toLocal8Bit().constData(), sModelPathFile.toLocal8Bit().constData(), 
																									qsHrlyRptModelName.toLocal8Bit().constData(), iCodeType, pszHrlyResErrMsgBuffer, 512, bSilent,
																									osRunInfo[iSimRun].BEMProcIdx(), pszEPlusVerStr, pszOpenStudioVerStr );				assert( iHrlyResExportRetVal == 0 );
													if (iHrlyResExportRetVal != 0)
   													BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - hourly results CSV export Failed for run %s -> return code %d: %s  (exporting to file:  %s)",
																				qsHrlyRptModelName.toLocal8Bit().constData(), iHrlyResExportRetVal, pszHrlyResErrMsgBuffer,
																				sHrlyResExportPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													else if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
														BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - hourly results CSV export for run %s %s (return code %d):  %s",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), (iHrlyResExportRetVal==0 ? "successful" : "failed"), 
																				iHrlyResExportRetVal, sHrlyResExportPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}

								// SAC 9/6/18 - write ZERO code hourly results CSV file
									if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ZEROCode" ), lZEROCode, 0, -1, 0, BEMO_User, osRunInfo[iSimRun].BEMProcIdx() ) && lZEROCode > 0 &&
										 !osRunInfo[iSimRun].RunID().compare("ap"))
									{	sZeroCdHrlyExportPathFile = sProcessingPath;
										sZeroCdHrlyExportPathFile += osRunInfo[iSimRun].SDDFile();								assert( sZeroCdHrlyExportPathFile.lastIndexOf('.') > 0 );
										if (sZeroCdHrlyExportPathFile.lastIndexOf('.') > 0)
											sZeroCdHrlyExportPathFile = sZeroCdHrlyExportPathFile.left( sZeroCdHrlyExportPathFile.lastIndexOf('.') );
										sZeroCdHrlyExportPathFile += " - ZEROCode Hrly.csv";
										QString sZeroCdHrlyMsg;
										sZeroCdHrlyMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
										             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
														 "(once the file is closed), or \n'Abort' to abort the %s.", "ZERO Code hourly results", sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), "hourly results export" );
										if (OKToWriteOrDeleteFile( sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), sZeroCdHrlyMsg, bSilent ))
										{	char pszZeroCdErrMsgBuffer[512];  pszZeroCdErrMsgBuffer[0]=0;
											int iZeroCdExportRetVal = CMX_ExportCSVHourlyResults_A2030( sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), osRunInfo[iSimRun].LongRunID().toLocal8Bit().constData(),
																									pszZeroCdErrMsgBuffer, 512, bSilent, osRunInfo[iSimRun].BEMProcIdx() );				assert( iZeroCdExportRetVal == 0 );
													if (iZeroCdExportRetVal != 0)
														BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - ZERO Code hourly results CSV export Failed for run %s -> return code %d: %s  (exporting to file:  %s)",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), iZeroCdExportRetVal, pszZeroCdErrMsgBuffer,
																				sZeroCdHrlyExportPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													else if (bVerbose)
														BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - ZERO Code hourly results CSV export for run %s %s (return code %d):  %s",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), (iZeroCdExportRetVal==0 ? "successful" : "failed"), 
																				iZeroCdExportRetVal, sZeroCdHrlyExportPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													if (iZeroCdExportRetVal == 0)
														bZCHrlyFileWritten = true;
									}	}

								// SAC 9/10/18 - storage of sim engine version IDs for reporting
									if (!osRunInfo[iSimRun].RunID().compare("ab"))
									{	if (pszOpenStudioVerStr && strlen( pszOpenStudioVerStr ) > 0)
											BEMPX_SetBEMData( BEMPX_GetDatabaseID( "OpenStudioVersion", iCID_Proj ), BEMP_Str, (void*) pszOpenStudioVerStr, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, iCurActiveBEMProcIdx /*osRunInfo[iR].BEMProcIdx()*/ );
										QString sEPlusVer;
										if (pszEPlusVerStr && strlen( pszEPlusVerStr ) > 0)
											sEPlusVer = pszEPlusVerStr;
										else if (dEPlusVer > 0.1)
											sEPlusVer = QString::asprintf( "%g", dEPlusVer );
										if (!sEPlusVer.isEmpty())
											BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EngyPlusVersion", iCID_Proj ), BEMP_QStr, (void*) &sEPlusVer, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, iCurActiveBEMProcIdx /*osRunInfo[iR].BEMProcIdx()*/ );
										if (!sCSEVersion.isEmpty())
											BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CSEVersion"     , iCID_Proj ), BEMP_QStr, (void*) &sCSEVersion, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, iCurActiveBEMProcIdx /*osRunInfo[iR].BEMProcIdx()*/ );
									}

								// SAC 9/6/18 - write ZERO code hourly results CSV file
									if (lZEROCode > 0 && !osRunInfo[iSimRun].RunID().compare("ab") && bZCHrlyFileWritten)
									{	QString sZeroCdRptPathFile = sModelPathOnly + sModelFileOnly;
										sZeroCdRptPathFile += " - ZEROCode Rpt.csv";
										QString sZeroCdRptMsg;
										sZeroCdRptMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
										             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
														 "(once the file is closed), or \n'Abort' to abort the %s.", "ZERO Code report", sZeroCdRptPathFile.toLocal8Bit().constData(), "report generation" );
										if (OKToWriteOrDeleteFile( sZeroCdRptPathFile.toLocal8Bit().constData(), sZeroCdRptMsg, bSilent ))
										{
											if (!BEMPX_RulelistExists( "GenerateZEROCodeReport" ))
												BEMPX_WriteLogFile( QString::asprintf( "Warning:  'GenerateZEROCodeReport' rulelist not found in ruleset." ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
											else
											{
				// debugging
				BEMPX_WriteLogFile( QString::asprintf( "Evaluating 'GenerateZEROCodeReport' rulelist on model %d (iCurActiveBEMProcIdx %d).", BEMPX_GetActiveModel(), iCurActiveBEMProcIdx ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												int iCODEZeroRptRetVal = LocalEvaluateRuleset( sErrMsg, 70, "GenerateZEROCodeReport", bVerbose, pCompRuleDebugInfo );
//													70 : Error evaluating 'GenerateZEROCodeReport' rulelist
												if (iCODEZeroRptRetVal != 0 || BEMPX_AbortRuleEvaluation())
													ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 70 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
												else
												{	QString sZeroCdHrlyPathFile = sProcessingPath + sModelFileOnly;
													sZeroCdHrlyPathFile += " - ap - ZEROCode Hrly.csv";
													if (!FileExists( sZeroCdHrlyPathFile.toLocal8Bit().constData() ))
													{	assert( false );
												// report as error if hourly results CSV file not found ??
													}
													else
													{	// append sZeroCdHrlyPathFile onto the end of sZeroCdRptPathFile
														std::ofstream of_a(  sZeroCdRptPathFile.toLocal8Bit().constData(), std::ios_base::binary | std::ios_base::app );
														std::ifstream if_b( sZeroCdHrlyPathFile.toLocal8Bit().constData(), std::ios_base::binary );
														of_a.seekp( 0, std::ios_base::end );
														of_a << if_b.rdbuf();
													// store path/filename of report file to BEMBase (for display via UI)
														BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ZEROCodePathFile", iCID_Proj ), BEMP_QStr, (void*) &sZeroCdRptPathFile, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, iCurActiveBEMProcIdx /*osRunInfo[iR].BEMProcIdx()*/ );
									}	}	}	}	}

							}	}

							if (iSimRetVal == OSI_SimEPlus_UserAbortedAnalysis)
								ProcessNonResAnalysisAbort( iCodeType, BCM_NRP_Step_MSim, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
								//ProcessNonResAnalysisAbort( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, BCM_NRP_Step_MSim, iProgressModelSum, 0 ), sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );

							BEMPX_RefreshLogFile();	// SAC 5/19/14
						}

#ifdef CM_QTGUI
							if (!bAbort && !BEMPX_AbortRuleEvaluation() && bDisplayProgress && (iRun+1) == iNumRuns)  // only increment to 'Results' item after LAST run
							{	// enum  CECNResProgressSteps   {   CNRP_Init,  CNRP_ModelPrep,  CNRP_PropSizTrn,  CNRP_PropSizSim,  CNRP_StdSizTrn,  CNRP_StdSizSim,  CNRP_PropTrn,  CNRP_PropSim,  CNRP_StdAnnTrn,  CNRP_StdAnnSim,  CNRP_Results,  CNRP_NumSteps };
								//iProgressStep = CNRP_Results;
								iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_Store, 0 /*lModels*/, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
							}
#endif

						if (!bAbort && !BEMPX_AbortRuleEvaluation())
						{
							if (iSimRetVal != 0)
							{	int iErrantRunNum = OSWrap_ErrorIDToRunNumber( iSimRetVal );
								assert( iErrantRunNum > 0 );
								if (iErrantRunNum < 1)
								{	if (sEPlusSimErrMsg.isEmpty())
										sErrMsg = QString::asprintf( "Error(s) encountered simulating multiple models (sim returned %d)", iSimRetVal );
									else
										sErrMsg = QString::asprintf( "Error(s) encountered simulating multiple models (sim returned %d):\n      %s", iSimRetVal, sEPlusSimErrMsg.toLocal8Bit().constData() );
								}
								else if (sEPlusSimErrMsg.isEmpty())
									sErrMsg = QString::asprintf( "Error(s) encountered simulating %s model (sim returned %d)", osRunInfo[iErrantRunNum-1].LongRunID().toLocal8Bit().constData(), iSimRetVal );
								else
									sErrMsg = QString::asprintf( "Error(s) encountered simulating %s model (sim returned %d):\n      %s", osRunInfo[iErrantRunNum-1].LongRunID().toLocal8Bit().constData(), 
																																									iSimRetVal, sEPlusSimErrMsg.toLocal8Bit().constData() );
//												45 : Error(s) encountered simulating Proposed Sizing model
//												24 : Error(s) encountered simulating Standard Sizing model
//												25 : Error(s) encountered simulating Proposed model
//												26 : Error(s) encountered simulating Standard (final) model
						//		if ((iRun==0 && iDontAbortOnErrorsThruStep < 4) || (iRun==1 && iDontAbortOnErrorsThruStep < 4) || (iRun==2 && iDontAbortOnErrorsThruStep < 7) || (iRun==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
								if (iDontAbortOnErrorsThruStep < (iAnalStep+1))  // check flag to bypass errors
									iRetVal = (iRetVal > 0 ? iRetVal : iSimErrID);	//(iRun==0 ? 45 : (23+iRun)));		// DO abort
								bForceXMLFileWriteDespiteAbort = true;		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
							}
//							else if (bStoreHourlyResults && !bThisOSSimSkipped)
							else if (bStoreHourlyResults && bSimRunsNow)
							{	if (!bAbort && !BEMPX_AbortRuleEvaluation())
								{
									int iBDBCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
									if (iBDBCID_EUseSummary <= 0 || BEMPX_GetNumObjects( iBDBCID_EUseSummary ) < 1)
									{	sErrMsg = QString::asprintf( "Error(s) encountered retrieving %s model simulation results", sRunIDLong.toLocal8Bit().constData() );
//													46 : Error(s) encountered retrieving Proposed Sizing model simulation results
//													27 : Error(s) encountered retrieving Standard Sizing model simulation results
//													28 : Error(s) encountered retrieving Proposed model simulation results
//													29 : Error(s) encountered retrieving Standard (final) model simulation results
								//		if ((iRun==0 && iDontAbortOnErrorsThruStep < 4) || (iRun==1 && iDontAbortOnErrorsThruStep < 4) || (iRun==2 && iDontAbortOnErrorsThruStep < 7) || (iRun==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
										if (iDontAbortOnErrorsThruStep < (iAnalStep+1))  // check flag to bypass errors
											iRetVal = (iRetVal > 0 ? iRetVal : iResErrID);	//(iRun==0 ? 46 : (26+iRun)));		// DO abort
										bForceXMLFileWriteDespiteAbort = true;		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
									}
									else
									{	if (bBypassUMLHChecks)
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Bypassing UMLH check on %s model", sRunID.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										else
										{	int iCID_ThrmlZn = BEMPX_GetDBComponentID( "ThrmlZn" );																	assert( iCID_ThrmlZn > 0 );
											long lDBID_ThrmlZn_ClgUMLHLimit = BEMPX_GetDatabaseID( "ClgUMLHLimit", iCID_ThrmlZn );							assert( iCID_ThrmlZn < 1 || lDBID_ThrmlZn_ClgUMLHLimit > 0 );
											long lDBID_ThrmlZn_HtgUMLHLimit = BEMPX_GetDatabaseID( "HtgUMLHLimit", iCID_ThrmlZn );							assert( iCID_ThrmlZn < 1 || lDBID_ThrmlZn_HtgUMLHLimit > 0 );
											long lDBID_ThrmlZn_BypassClgUMLHLimit = BEMPX_GetDatabaseID( "BypassClgUMLHLimit", iCID_ThrmlZn );		// SAC 5/12/19 - added to enable individual Zone Clg/Htg bypass of UMLH limits (tic #2680)
											long lDBID_ThrmlZn_BypassHtgUMLHLimit = BEMPX_GetDatabaseID( "BypassHtgUMLHLimit", iCID_ThrmlZn );
											QString cstrUMLHWarningMsg, cstrUMLHWarningDetails, cstrUMLHDlgCaption;
											if (iCID_ThrmlZn > 0)
											{	for (int iR=0; iR <= iSimRunIdx; iR++)
													if (osRunInfo[iR].OSRunIdx() >= 0)
													{													assert( sErrMsg.isEmpty() );	// confirm error message not populated yet - else code @ end of for loop likely needing some mods
														if (bVerbose || bReportAllUMLHZones)	// SAC 11/11/19 - bReportAllUMLHZones
															BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - UMLH check on %s model", osRunInfo[iR].RunID().toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

											// Check for zones exceeding maxiumum number of cooling/heat load hours - SAC 8/31/13
															int iNumZonesExceedClgUMLHs = 0, iNumZonesExceedHtgUMLHs = 0,  iMaxZoneExceedClgUMLHsIdx = -1, iMaxZoneExceedHtgUMLHsIdx = -1;
															double fMaxZoneClgUMLHs = 0, fMaxZoneHtgUMLHs = 0, fNumZoneClgUMLHs = 0, fNumZoneHtgUMLHs = 0;
															QString sMaxZoneClgUMLHsName, sMaxZoneHtgUMLHsName, sErrantZoneList, sAppendToErrantZoneList;
															int iNumZones = (iCID_ThrmlZn < 1 ? 0 : BEMPX_GetNumObjects( iCID_ThrmlZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ));			// assert( iNumZones > 0 );  - removed assert - SAC 11/03/23
															bool bIsPropModel = (osRunInfo[iR].OSRunIdx() == iPropModelRunIdx);		// SAC 4/6/20
#define  UMLH_ERR_MSG_BASELINE	225	// space for leading line:  Error: In XXXXXXXXXXXXX model, ### zone(s) exceed maximum cooling unmet load hours (####) and ### zone(s) exceed maximum heating unmet load hours (####)
															// and trailing line:       (and ### other zones, as reported in project log file)
															QString sReducedErrantZoneList;
															long lConstantClgUMLHLimit = -1, lConstantHtgUMLHLimit = -1;  // SAC 5/21/19 - to report individual UMLH limit values in warning message
															int iMaxErrantZoneListToAppend = 0, iNumZnsExcludedFromErrZoneList = 0;
															if (iErrorMsgLen > 0 && pszErrorMsg && (iErrorMsgLen - strlen( pszErrorMsg )) > UMLH_ERR_MSG_BASELINE)
																iMaxErrantZoneListToAppend = iErrorMsgLen - ((int) strlen( pszErrorMsg ) + UMLH_ERR_MSG_BASELINE);
															long lDBID_ThrmlZn_ClgUnmetLdHrs = BEMPX_GetDatabaseID( "ClgUnmetLdHrs", iCID_ThrmlZn );			assert( lDBID_ThrmlZn_ClgUnmetLdHrs > 0 );
															long lDBID_ThrmlZn_HtgUnmetLdHrs = BEMPX_GetDatabaseID( "HtgUnmetLdHrs", iCID_ThrmlZn );			assert( lDBID_ThrmlZn_HtgUnmetLdHrs > 0 );
															long lDBID_ThrmlZn_Name          = BEMPX_GetDatabaseID( "Name"         , iCID_ThrmlZn );			assert( lDBID_ThrmlZn_Name          > 0 );
															for (int iZn=0; iZn < iNumZones; iZn++)
															{	double fMaxUnmetClgLdHrs, fMaxUnmetHtgLdHrs;
																if (lDBID_ThrmlZn_ClgUMLHLimit < 1 || !BEMPX_GetFloat( lDBID_ThrmlZn_ClgUMLHLimit, fMaxUnmetClgLdHrs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ))		// SAC 3/9/15 - new ThrmlZn-specific limits
																{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "MaxClgUnmetLdHrs", iCID_Proj ), fMaxUnmetClgLdHrs, 0, -1, 0, BEMO_User, osRunInfo[iR].BEMProcIdx() ))
																		fMaxUnmetClgLdHrs = -1;
																}
																if (lDBID_ThrmlZn_HtgUMLHLimit < 1 || !BEMPX_GetFloat( lDBID_ThrmlZn_HtgUMLHLimit, fMaxUnmetHtgLdHrs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ))
																{	if (!BEMPX_GetFloat( BEMPX_GetDatabaseID( "MaxHtgUnmetLdHrs", iCID_Proj ), fMaxUnmetHtgLdHrs, 0, -1, 0, BEMO_User, osRunInfo[iR].BEMProcIdx() ))
																		fMaxUnmetHtgLdHrs = -1;
																}
																long lBypassClgUMLHLimit=0, lBypassHtgUMLHLimit=0;		// SAC 5/12/19 (tic #2680)
																if (lDBID_ThrmlZn_BypassClgUMLHLimit < 1 || !BEMPX_GetInteger( lDBID_ThrmlZn_BypassClgUMLHLimit, lBypassClgUMLHLimit, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ))
																	lBypassClgUMLHLimit = 0;
																if (lDBID_ThrmlZn_BypassHtgUMLHLimit < 1 || !BEMPX_GetInteger( lDBID_ThrmlZn_BypassHtgUMLHLimit, lBypassHtgUMLHLimit, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ))
																	lBypassHtgUMLHLimit = 0;

																if (fMaxUnmetClgLdHrs > -0.5 && BEMPX_GetFloat( lDBID_ThrmlZn_ClgUnmetLdHrs, fNumZoneClgUMLHs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ) &&
																	 fNumZoneClgUMLHs > 0 /*&& lBypassClgUMLHLimit == 0*/)		// SAC 5/13/19 (tic #2680)
																{	if ((lBypassClgUMLHLimit == 0 || bReportAllUMLHZones) && fNumZoneClgUMLHs > (fMaxZoneClgUMLHs + 0.1))
																	{	iMaxZoneExceedClgUMLHsIdx = iZn;
																		fMaxZoneClgUMLHs = fNumZoneClgUMLHs;
																	}
																	if (lBypassClgUMLHLimit == 0 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1))		// SAC 11/11/19 - moved lBypassClgUMLHLimit == 0 check from above to here (to enable reporting of Std model UMLH info)
																	{	iNumZonesExceedClgUMLHs++;
																		if (bIsPropModel)		// SAC 4/6/20
																			iNumPropClgUMLHViolations++;
																		if (lConstantClgUMLHLimit == -1)  // SAC 5/21/19
																			lConstantClgUMLHLimit = (long) (fMaxUnmetClgLdHrs + 0.1);
																		else if (lConstantClgUMLHLimit > 0 && lConstantClgUMLHLimit != (long) (fMaxUnmetClgLdHrs + 0.1))
																			lConstantClgUMLHLimit = -2;  // => no constant UMLH limit
																	}
																}

																if (fMaxUnmetHtgLdHrs > -0.5 && BEMPX_GetFloat( lDBID_ThrmlZn_HtgUnmetLdHrs, fNumZoneHtgUMLHs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ) &&
																	 fNumZoneHtgUMLHs > 0 /*&& lBypassHtgUMLHLimit == 0*/)		// SAC 5/13/19 (tic #2680)
																{	if ((lBypassClgUMLHLimit == 0 || bReportAllUMLHZones) && fNumZoneHtgUMLHs > (fMaxZoneHtgUMLHs + 0.1))
																	{	iMaxZoneExceedHtgUMLHsIdx = iZn;
																		fMaxZoneHtgUMLHs = fNumZoneHtgUMLHs;
																	}
																	if (lBypassClgUMLHLimit == 0 && fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1))		// SAC 11/11/19 - moved lBypassClgUMLHLimit == 0 check from above to here (to enable reporting of Std model UMLH info)
																	{	iNumZonesExceedHtgUMLHs++;
																		if (bIsPropModel)		// SAC 4/6/20
																			iNumPropHtgUMLHViolations++;
																		if (lConstantHtgUMLHLimit == -1)  // SAC 5/21/19
																			lConstantHtgUMLHLimit = (long) (fMaxUnmetHtgLdHrs + 0.1);
																		else if (lConstantHtgUMLHLimit > 0 && lConstantHtgUMLHLimit != (long) (fMaxUnmetHtgLdHrs + 0.1))
																			lConstantHtgUMLHLimit = -2;  // => no constant UMLH limit
																	}
																}

																if ((bVerbose || bReportAllUMLHZones) && (bReportStandardUMLHs || !osRunInfo[iR].IsStdRun()))	// SAC 11/11/19 - bReportAllUMLHZones
																{	QString sUMLHZoneName, sUMLHZoneLog;
																	BEMPX_GetString( lDBID_ThrmlZn_Name, sUMLHZoneName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iZn,
																									BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() );		assert( !sUMLHZoneName.isEmpty() );
																	sUMLHZoneLog = QString::asprintf( "          clg: %.0f  htg: %.0f  '%s'", fNumZoneClgUMLHs, fNumZoneHtgUMLHs, sUMLHZoneName.toLocal8Bit().constData() );
																	BEMPX_WriteLogFile( sUMLHZoneLog, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																}

                     			                  // append record to string reporting zone UMLH issues - SAC 9/6/13
																if ( (fMaxUnmetClgLdHrs > -0.5 && lBypassClgUMLHLimit == 0 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1)) ||
																	  (fMaxUnmetHtgLdHrs > -0.5 && lBypassHtgUMLHLimit == 0 && fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1)) )
																{	// SAC 5/13/19 - zero out UMLH values for which checks are to be Bypassed (tic #2680)
																	if (lBypassClgUMLHLimit)
																		fNumZoneClgUMLHs = 0;
																	if (lBypassHtgUMLHLimit)
																		fNumZoneHtgUMLHs = 0;
																	BEMPX_GetString( lDBID_ThrmlZn_Name, sMaxZoneClgUMLHsName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iZn,
																									BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() );		assert( !sMaxZoneClgUMLHsName.isEmpty() );
																	sAppendToErrantZoneList = QString::asprintf( "\n          clg: %.0f  htg: %.0f  '%s'", fNumZoneClgUMLHs, fNumZoneHtgUMLHs, sMaxZoneClgUMLHsName.toLocal8Bit().constData() );
														// SAC 3/8/14 - added code to limit zones reported back to calling application so that error message doesn't exceed max length
																	if (iMaxErrantZoneListToAppend > 0 && iNumZnsExcludedFromErrZoneList > 0)
																		iNumZnsExcludedFromErrZoneList++;	// already to the point where we are excluding zones, so just increment the counter of skipped zones
																	else if (iMaxErrantZoneListToAppend > 0 && sReducedErrantZoneList.isEmpty() &&
																				(sErrantZoneList.length() + sAppendToErrantZoneList.length()) > iMaxErrantZoneListToAppend)
																	{	sReducedErrantZoneList = sErrantZoneList;
																		iNumZnsExcludedFromErrZoneList++;
																	}
																	sErrantZoneList += sAppendToErrantZoneList;
																			if (bReportStandardUMLHs || !osRunInfo[iR].IsStdRun())  //bVerbose)	// SAC 3/10/15 - added verbose logging of each UMLH errant zone inside zone loop to catch variation in UMLH limits (by zone)   // SAC 11/11/19 - added bReportStandardUMLHs
																			{	if (fMaxUnmetClgLdHrs > -0.5 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1) && fMaxUnmetHtgLdHrs > -0.5 && fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1))
																				{	sLogMsg = QString::asprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: cooling %.0f (%.0f max) and heating %.0f (%.0f max)", 
																											osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs, fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' cooling %L2 > %L3 and heating %L4 > %L5\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneClgUMLHs ).arg( fMaxUnmetClgLdHrs ).arg( fNumZoneHtgUMLHs ).arg( fMaxUnmetHtgLdHrs ) );
																					sMsg = QString::asprintf( "  '%s' cooling %g > %g and heating %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs, fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																				}
																				else if (fMaxUnmetClgLdHrs > -0.5 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1))
																				{	sLogMsg = QString::asprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: cooling %.0f (%.0f max)", osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' cooling %L2 > %L3\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneClgUMLHs ).arg( fMaxUnmetClgLdHrs ) );
																					sMsg = QString::asprintf( "  '%s' cooling %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs );
																				}
																				else
																				{	sLogMsg = QString::asprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: heating %.0f (%.0f max)", osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' heating %L2 > %L3\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneHtgUMLHs ).arg( fMaxUnmetHtgLdHrs ) );
																					sMsg = QString::asprintf( "  '%s' heating %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																				}
																				cstrUMLHWarningDetails += sMsg;
																				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																			}
																}
															}	// end of loop over all Zones

															BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumZnsExceedClgUnmetLdHrs", iCID_Proj ), BEMP_Int, &iNumZonesExceedClgUMLHs, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
															BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumZnsExceedHtgUnmetLdHrs", iCID_Proj ), BEMP_Int, &iNumZonesExceedHtgUMLHs, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
															BEMPX_SetBEMData( BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrs"       , iCID_Proj ), BEMP_Flt, &fMaxZoneClgUMLHs       , BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
															BEMPX_SetBEMData( BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrs"       , iCID_Proj ), BEMP_Flt, &fMaxZoneHtgUMLHs       , BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
                     		
															if (iMaxZoneExceedClgUMLHsIdx >= 0)
															{	BEMPX_GetString( lDBID_ThrmlZn_Name, sMaxZoneClgUMLHsName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iMaxZoneExceedClgUMLHsIdx, BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() );		assert( !sMaxZoneClgUMLHsName.isEmpty() );
															}
															if (sMaxZoneClgUMLHsName.isEmpty())
																BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName", iCID_Proj ), iError, 0, BEMO_User, osRunInfo[iR].BEMProcIdx() );
															else
																BEMPX_SetBEMData(      BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName", iCID_Proj ), BEMP_QStr, (void*) &sMaxZoneClgUMLHsName, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
                     		
															if (iMaxZoneExceedHtgUMLHsIdx >= 0)
															{	BEMPX_GetString( lDBID_ThrmlZn_Name, sMaxZoneHtgUMLHsName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iMaxZoneExceedHtgUMLHsIdx, BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() );		assert( !sMaxZoneHtgUMLHsName.isEmpty() );
															}
															if (sMaxZoneHtgUMLHsName.isEmpty())
																BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName", iCID_Proj ), iError, 0, BEMO_User, osRunInfo[iR].BEMProcIdx() );
															else
																BEMPX_SetBEMData(      BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName", iCID_Proj ), BEMP_QStr, (void*) &sMaxZoneHtgUMLHsName, BEMO_User, -1, BEMS_SimResult, BEMO_User, TRUE, osRunInfo[iR].BEMProcIdx() );
                     		
															if (iNumZonesExceedClgUMLHs > 0 || iNumZonesExceedHtgUMLHs > 0)
															{
																if (!osRunInfo[iR].IsStdRun())
																	bFailAnalysisForUMLH = true;		// SAC 4/23/20 - ensure final result not "PASS" when UMLHs exceeded in Prop model (tic #2680)

																QString sClgHoursStr = "hours", sHtgHoursStr = "hours";		// SAC 5/21/19 - include max UMLH limits in warning message
																if (lConstantClgUMLHLimit > 0)
																	sClgHoursStr = QString::asprintf( "hours of %d", lConstantClgUMLHLimit );
																if (lConstantHtgUMLHLimit > 0)
																	sHtgHoursStr = QString::asprintf( "hours of %d", lConstantHtgUMLHLimit );
																if (iNumZonesExceedClgUMLHs > 0 && iNumZonesExceedHtgUMLHs > 0)
																	sErrMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s and %d zone(s) exceed maximum heating unmet load %s", iNumZonesExceedClgUMLHs, /*fMaxUnmetClgLdHrs,*/
																								osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs /*, fMaxUnmetHtgLdHrs*/, sHtgHoursStr.toLocal8Bit().constData() );
																else if (iNumZonesExceedClgUMLHs > 0)
																	sErrMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s", iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetClgLdHrs*/, sClgHoursStr.toLocal8Bit().constData() );
																else  // if (iNumZonesExceedHtgUMLHs > 0)
																	sErrMsg = QString::asprintf( "Warning:  %d zone(s) in %s model exceed maximum heating unmet load %s", iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetHtgLdHrs*/, sHtgHoursStr.toLocal8Bit().constData() );

																if (iMaxErrantZoneListToAppend > 0 && !sReducedErrantZoneList.isEmpty())	// SAC 3/8/14
																	// repeat same message but w/ shortened list of zones
																	sErrMsgShortenedToFit = QString::asprintf( "%s%s\n          (and %d other zone(s), as reported in project log file)", sErrMsg.toLocal8Bit().constData(), sReducedErrantZoneList.toLocal8Bit().constData(), iNumZnsExcludedFromErrZoneList );
																sErrMsg += sErrantZoneList;
																bForceXMLFileWriteDespiteAbort = true;		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
//														30 : Model zone(s) exceed unmet load hours limits
							// SAC 3/10/15 - prevent erroring out of analysis for UMLH limit reason
							//									if ((osRunInfo[iR].OSRunIdx()==0 && iDontAbortOnErrorsThruStep < 4) || (osRunInfo[iR].OSRunIdx()==2 && iDontAbortOnErrorsThruStep < 7))		// SAC 1/30/15 - no longer error out for baseline run - was:  || (osRunInfo[iR].OSRunIdx()==1 && iDontAbortOnErrorsThruStep < 4) || (osRunInfo[iR].OSRunIdx()==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
							//										iRetVal = (iRetVal > 0 ? iRetVal : 30);		// DO abort

																if (bReportStandardUMLHs || !osRunInfo[iR].IsStdRun())  //bVerbose)	// SAC 3/10/15 - added verbose logging of each UMLH errant zone inside zone loop to catch variation in UMLH limits (by zone)   // SAC 11/11/19 - added bReportStandardUMLHs
																{	sUMLHTextFileMsg = cstrUMLHWarningDetails;		// qstrUMLHWarningDetails.toStdString().c_str();
																	if (iNumZonesExceedClgUMLHs > 0 && iNumZonesExceedHtgUMLHs > 0)
																	{	//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum cooling unmet load hours and %L3 zone(s) exceed maximum heating unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedClgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) ).arg( iNumZonesExceedHtgUMLHs );
																		cstrUMLHWarningMsg = QString::asprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s and %d zone(s) exceed maximum heating unmet load %s.<br><br></a>",
    																												iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs, sHtgHoursStr.toLocal8Bit().constData() );
																		sLogMsg = QString::asprintf( "%d zone(s) in %s model exceed maximum cooling unmet load %s and %d zone(s) exceed maximum heating unmet load %s:\n",
																													iNumZonesExceedClgUMLHs, /*fMaxUnmetClgLdHrs,*/ osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs /*, fMaxUnmetHtgLdHrs*/, sHtgHoursStr.toLocal8Bit().constData() );
																	}
																	else if (iNumZonesExceedClgUMLHs > 0)
																	{	//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum cooling unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedClgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) );
																		cstrUMLHWarningMsg = QString::asprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum cooling unmet load %s.<br><br></a>",
    																												iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sClgHoursStr.toLocal8Bit().constData() );
																		sLogMsg = QString::asprintf( "%d zone(s) in %s model exceed maximum cooling unmet load %s:\n", iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetClgLdHrs*/, sClgHoursStr.toLocal8Bit().constData() );
																	}
																	else  // if (iNumZonesExceedHtgUMLHs > 0)
																	{	//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum heating unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedHtgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) );
																		cstrUMLHWarningMsg = QString::asprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum heating unmet load %s.<br><br></a>",
    																												iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sHtgHoursStr.toLocal8Bit().constData() );
																		sLogMsg = QString::asprintf( "%d zone(s) in %s model exceed maximum heating unmet load %s:\n", iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetHtgLdHrs*/, sHtgHoursStr.toLocal8Bit().constData() );
																	}
																	sUMLHTextFileMsg = sLogMsg + sUMLHTextFileMsg;
																	//qstrUMLHWarningDetails.prepend( "Zones exceeding unmet load hour limits:\n" );
																	//qstrUMLHWarningMsg.append( "<a>All thermal zones exceeding unmet load hour limits will be reported on PRF-1.<br></a>" );
																	//qstrUMLHWarningMsg.append( "<a>In the future, projects with zones exceeding UMLH limits will not be useable for compliance.</a>" );
																	cstrUMLHWarningDetails = "Zones exceeding unmet load hour limits:\n" + cstrUMLHWarningDetails;
																	// SAC 4/2/19 - wording updated to include: watermarked 'not for compliance' (tic #2680)
																	cstrUMLHWarningMsg += "<a>All thermal zones exceeding unmet load hour limits will be reported on PRF-1, which will be watermarked 'not for compliance'.<br></a>";
																	if (iRulesetCodeYear < 2019)		// SAC 1/29/20 - remove trailing sentence from 2019+ analysis (Com tic #3173)   // SAC 4/23/20 - flipped equality to OMIT this sentence in 2019+ msgs (tic #2680)
																		cstrUMLHWarningMsg += "<a>In the future, projects with zones exceeding UMLH limits will not be useable for compliance.</a>";

																	QString sUMLHFAQLink;
																	if (!BEMPX_GetString( BEMPX_GetDatabaseID( "UnmetLdHrsFAQLink", iCID_Proj ), sUMLHFAQLink ))
																		sUMLHFAQLink.clear();
																	if (!sUMLHFAQLink.isEmpty())
																	{	sUMLHTextFileMsg += "For information on resolving unmet load hour issues visit:  ";
																		sUMLHTextFileMsg += sUMLHFAQLink;
																		sUMLHTextFileMsg += "\n";
																		//qstrUMLHWarningMsg.append( QString( "<a><br></a><a href=%1>Click here for information on resolving unmet load hour issues.</a>" ).arg( ((const char*) sUMLHFAQLink) ) );
																		sMsg = QString::asprintf( "<a><br></a><a href=%s>Click here for information on resolving unmet load hour issues.</a>", sUMLHFAQLink.toLocal8Bit().constData() );
																		cstrUMLHWarningMsg += sMsg;
																	}

															// write text file w/ UMLH zone listing
																	if (bWriteUMLHViolationsToFile && !sUMLHTextFileName.isEmpty())
																	{	QString sUMLHOverwriteMsg;
																		sUMLHOverwriteMsg = QString::asprintf(	"The zone UMLH violations text file '%s' is opened in another application.  This file must be closed in that application before an updated file "
																											"can be written.\n\nSelect 'Retry' to proceed (once the file is closed), or \n'Abort' to abort the file writing.", sUMLHTextFileName.toLocal8Bit().constData() );
																		if (!OKToWriteOrDeleteFile( sUMLHTextFileName.toLocal8Bit().constData(), sUMLHOverwriteMsg, bSilent ))
																			sUMLHOverwriteMsg = QString::asprintf( "Unable to open and/or write zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
																		else
																		{	sUMLHOverwriteMsg.clear();
																			FILE *fp_UMLH;
																			int iUMLHErrorCode;
																			try
																			{	iUMLHErrorCode = fopen_s( &fp_UMLH, sUMLHTextFileName.toLocal8Bit().constData(), "wb" );
																				if (iUMLHErrorCode != 0 || fp_UMLH == NULL)
																					sUMLHOverwriteMsg = QString::asprintf( "Error encountered opening zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
																				else
																				{	long lUMLHRunDate = 0;
																					if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lUMLHRunDate ) && lUMLHRunDate > 0)
																				   {	//CTime locTime = lUMLHRunDate;
																						//fprintf( fp_UMLH, "Run Date/Time:  %s\n", locTime.Format("%Y-%b-%d %H:%M:%S") );
																						QDateTime locTime = QDateTime::currentDateTime();
																						fprintf( fp_UMLH, "Run Date/Time:  %s\n", locTime.toString("yyyy-MM-dd HH:mm:ss").toLocal8Bit().constData() );
																					}
																					fprintf( fp_UMLH, sUMLHTextFileMsg.toLocal8Bit().constData() );
																					fflush(  fp_UMLH );
																					fclose(  fp_UMLH );
																			}	}
																			catch( ... )
																			{	sUMLHOverwriteMsg = QString::asprintf( "Unknown error writing zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
																			}
																		}
																		if (!sUMLHOverwriteMsg.isEmpty())
																			BEMPX_WriteLogFile( sUMLHOverwriteMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																	}
#ifdef CM_QTGUI
															// display UMLH zone dialog
																	//	qstrUMLHWarningMsg = "<a>Warning:  3 zone(s) in Proposed model exceed maximum cooling unmet load hours and 2 zone(s) exceed maximum heating unmet load hours.<br><br></a>"
																	//    						"<a href=http://bees.archenergy.com/faq_hvac.html>Click here for more information</a>";
																	//	qstrUMLHWarningDetails = "Zone(s) exceeding UMLH limits:\n  'Wing1_Side1_Zn' cooling 186 > 150 and heating 198 > 150\n  'Wing1_Side2_Zn' cooling 246 > 150\n"
																	//									"  'Common_Lobby_Zn' heating 201 > 150\n  'Common_Corridor_Zn' cooling 153 > 150\n";
																	if (bPromptUserUMLHWarning && !osRunInfo[iR].IsStdRun())	// SAC 11/11/19 - never prompt for Std model violations
																	{
                                                      if (bDisplayProgress)      // SAC 01/19/25
                                                      {  if (sq_app)		// added - SAC 7/1/20
																		   	sq_app->beep();
																		   QString qstrUMLHWarningMsg = cstrUMLHWarningMsg;
																		   QString qstrUMLHWarningDetails = cstrUMLHWarningDetails;
																		   QString qstrUMLHDlgCaption = cstrUMLHDlgCaption;
																		   qstrUMLHDlgCaption = QString( "%1 Model Unmet Load Hours" ).arg( osRunInfo[iR].LongRunID() );
																		   QMessageBox msgBox;
																		   msgBox.setWindowTitle( qstrUMLHDlgCaption );
																		   msgBox.setIcon( QMessageBox::Warning ); 
																		   msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
																		   msgBox.setText( qstrUMLHWarningMsg );
																		   msgBox.setDetailedText( qstrUMLHWarningDetails );
																		   msgBox.setStandardButtons( QMessageBox::Ok );  // needed for timeout to function
																		   msgBox.setDefaultButton( QMessageBox::Ok );
																		   if (iAnalysisDialogTimeout > 0)
																		   	msgBox.button(QMessageBox::Ok)->animateClick(iAnalysisDialogTimeout*1000);		// SAC 7/1/20 - apply dialog timeout here (Com tic #2680)
																		   msgBox.exec();
                                                      }
                                                      else
                                                      {  BEMPX_WriteLogFile( QString("%1 - %2").arg( cstrUMLHDlgCaption, cstrUMLHWarningMsg ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                                                         BEMPX_WriteLogFile( cstrUMLHWarningDetails, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																	}  }
#endif
																}
															}

												// added copy of error message writing/processing from below to ensure error messages written to log for EVERY run resulting in errors
														if (!sErrMsg.isEmpty())
														{
															// SAC 4/2/19 - moved log file writing code to inside !IsStdRun() check to prevent echoing std run UMLH to project log (tic #2680)
															// SAC 11/11/19 - augmented above mod to report std model UMLHs based on INI setting
															if (bReportStandardUMLHs || !osRunInfo[iR].IsStdRun())
																BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															if (!osRunInfo[iR].IsStdRun())  // osRunInfo[iR].OSRunIdx() == 0 || osRunInfo[iR].OSRunIdx() == 2)
															{
																// throw error only if UMLH limits exceeded for * Proposed models  - SAC 1/31/15
																baSimPassesUMLHLimits[iR] = false;
																bool bErrMsgAppendedToReturn = false;
																if (!sErrMsgShortenedToFit.isEmpty())
																{	assert( (pszErrorMsg == NULL || iErrorMsgLen < 1 || (sErrMsgShortenedToFit.length() < (iErrorMsgLen - (int) strlen( pszErrorMsg )))) );
																	bErrMsgAppendedToReturn = AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsgShortenedToFit.toLocal8Bit().constData() );
																}
																else
																	bErrMsgAppendedToReturn = AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsg.toLocal8Bit().constData() );
												// SAC 6/25/15 - removed code that logs UMLH warnings as errors and toggles the bAbort bool
												//				if (!bErrMsgAppendedToReturn)
												//					BEMPX_AddRulesetError( sErrMsg );	// only log ruleset error if sErrMsg NOT appended onto return error message (pszErrorMsg)
												//				if ((osRunInfo[iR].OSRunIdx()==0 && iDontAbortOnErrorsThruStep < 4) || (osRunInfo[iR].OSRunIdx()==1 && iDontAbortOnErrorsThruStep < 4) ||
												//					 (osRunInfo[iR].OSRunIdx()==2 && iDontAbortOnErrorsThruStep < 7) || (osRunInfo[iR].OSRunIdx()==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
												//					bAbort = true;
															}
															sErrMsg.clear();
															sErrMsgShortenedToFit.clear();
														}
													}	// if (osRunInfo[iR].RunID() >= 0)
											}	// if (iCID_ThrmlZn > 0)
										}	// else  => perform UMLH checks
							}	}	}

   						// AnalysisAction - End / BeforeAnalPostProc processing   - SAC 11/17/20
							if (iRetVal == 0 && !bAbort && bFinalRun)
								MidAnalysis_ApplyAnalysisActionToDatabase( BEMAnalActPhase_End, BEMAnalActWhen_End_BeforeAnalPostProc, sErrMsg, bAbort, iRetVal,
																							77 /*iErrID*/, bVerbose, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );	// SAC 11/17/20

                     // evaluate rules following ap model to facilitate CustomMeterOption results storage - SAC 11/02/23
							if (!bAbort && !BEMPX_AbortRuleEvaluation() && iSimRetVal==0 && 
								 BEMPX_RulelistExists( "RunPostProcessing" ))
							{
								int iPostProcRuleRetVal = LocalEvaluateRuleset( sErrMsg, 76, "RunPostProcessing", bVerbose, pCompRuleDebugInfo );
//											76 : Error evaluating 'AnalysisPostProcessing' rulelist
								if (iPostProcRuleRetVal != 0 || BEMPX_AbortRuleEvaluation())
									ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 76 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
							}

   						// evaluate 'AnalysisPostProcessing' rulelist - SAC 4/20/19
                           //BEMPX_WriteLogFile( QString::asprintf( "checking b4 eval of 'AnalysisPostProcessing' rulelist - iRun=%d, iNumRuns=%d, AnalysisType=%d", iRun, iNumRuns, lAnalysisType ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							if (!bAbort && !BEMPX_AbortRuleEvaluation() && iSimRetVal==0 && 
                         ( (iRun+1) == iNumRuns || (iRun == iPropModelRunIdx && bProposedOnly) ) &&
								 BEMPX_RulelistExists( "AnalysisPostProcessing" ))
							{
				// debugging
				//BEMPX_WriteLogFile( QString::asprintf( "Evaluating 'AnalysisPostProcessing' rulelist on model %d (iCurActiveBEMProcIdx %d).", BEMPX_GetActiveModel(), iCurActiveBEMProcIdx ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								int iPostProcRuleRetVal = LocalEvaluateRuleset( sErrMsg, 76, "AnalysisPostProcessing", bVerbose, pCompRuleDebugInfo );
//											76 : Error evaluating 'AnalysisPostProcessing' rulelist
								if (iPostProcRuleRetVal != 0 || BEMPX_AbortRuleEvaluation())
									ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 76 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
							}

//							if (bStoreBEMDetails && !bThisOSSimSkipped)
							if (bStoreBEMDetails && bSimRunsNow)
							{	for (int iR=0; iR <= iSimRunIdx; iR++)
									if (osRunInfo[iR].RunID() >= 0)
									{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(" - ") + osRunInfo[iR].RunID() + ".ibd-Detail-PostSim";
										BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL, false, false, FALSE, 0, false, NULL, true, osRunInfo[iR].BEMProcIdx() );
							}		}
							BEMPX_RefreshLogFile();	// SAC 5/19/14
						}
					}

					if (sErrMsg.isEmpty() && baSimPassesUMLHLimits[0] && baSimPassesUMLHLimits[1]
										//		 && (	//(iRun == 0 && iAnalysisThruStep < 5) ||
										//				(iRun == 1 && iAnalysisThruStep < 5) ||
										//				//(iRun == 2 && iAnalysisThruStep < 8) ||
										//				(iRun == 3 && iAnalysisThruStep < 8) ) )
												 &&  iAnalysisThruStep < (iAnalStep+2)  )
					{	bCompletedAnalysisSteps = TRUE;
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
				}

				if (!sErrMsg.isEmpty())
				{	BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					bool bErrMsgAppendedToReturn = false;
					if (!sErrMsgShortenedToFit.isEmpty())
					{	assert( (pszErrorMsg == NULL || iErrorMsgLen < 1 || (sErrMsgShortenedToFit.length() < (iErrorMsgLen - (int) strlen( pszErrorMsg )))) );
						bErrMsgAppendedToReturn = AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsgShortenedToFit.toLocal8Bit().constData() );
					}
					else
						bErrMsgAppendedToReturn = AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsg.toLocal8Bit().constData() );
					if (!bErrMsgAppendedToReturn)
						BEMPX_AddRulesetError( sErrMsg.toLocal8Bit().constData() );	// only log ruleset error if sErrMsg NOT appended onto return error message (pszErrorMsg)
			//		if ((iRun==0 && iDontAbortOnErrorsThruStep < 4) || (iRun==1 && iDontAbortOnErrorsThruStep < 4) || (iRun==2 && iDontAbortOnErrorsThruStep < 7) || (iRun==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
					if (iDontAbortOnErrorsThruStep < (iAnalStep+1))  // check flag to bypass errors
						bAbort = true;
					sErrMsg.clear();
					sErrMsgShortenedToFit.clear();
				}

				if (!bAbort && !BEMPX_AbortRuleEvaluation() && bFailAnalysisForUMLH)		// SAC 4/23/20 - code to change compliance result if needed for UMLH failures (tic #2680)
				{	QString sPassFailResult;
					for (int iR=0; iR <= iSimRunIdx; iR++)
						if (osRunInfo[iR].OSRunIdx() >= 0 && osRunInfo[iR].RunID().length() > 0)
						{	int iNumEUseSums = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, osRunInfo[iR].BEMProcIdx() );
							for (int iEUS=0; iEUS < iNumEUseSums; iEUS++)
								if (BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:PassFail" ), sPassFailResult, TRUE, 0, -1, iEUS, BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() ) &&
										sPassFailResult.compare("PASS", Qt::CaseInsensitive)==0)
								{	// need to SWITCH this compliance result from PASS to FAIL-UMLH
									sPassFailResult = "FAIL-UMLH";
											if (bVerbose)		// SAC 4/23/20 - moved down INSIDE iR run loop
												BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Switching %s compliance result to '%s'", osRunInfo[iR].RunID().toLocal8Bit().constData(), sPassFailResult.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:PassFail"      ), BEMP_QStr, (void*) &sPassFailResult,         BEMO_User, iEUS, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo[iR].BEMProcIdx() );
      							BEMPX_SetBEMData( BEMPX_GetDatabaseID( "EUseSummary:ComplyMessage" ), BEMP_Str , (void*) "DOES NOT COMPLY (UMLH)", BEMO_User, iEUS, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo[iR].BEMProcIdx() );   // SAC 12/13/21
						}		}
				}

				if (!bAbort && !BEMPX_AbortRuleEvaluation())	   // new property to track when analysis is invalid - SAC 05/05/23 (gh NRes PRF schema issue #51)
            {
               long lDBID_EUseSum_AnalysisValid = BEMPX_GetDatabaseID( "EUseSummary:AnalysisValid" );
               long lAnalysisValid = (bSendRptSignature ? 1 : 0);
					for (int iR=0; (lDBID_EUseSum_AnalysisValid > 0 && iR <= iSimRunIdx); iR++)
						if (osRunInfo[iR].OSRunIdx() >= 0 && osRunInfo[iR].RunID().length() > 0)
						{	int iNumEUseSums = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ), BEMO_User, osRunInfo[iR].BEMProcIdx() );
							for (int iEUS=0; iEUS < iNumEUseSums; iEUS++)
									BEMPX_SetBEMData( lDBID_EUseSum_AnalysisValid, BEMP_Int, (void*) &lAnalysisValid, BEMO_User, iEUS, BEMS_UserDefined, BEMO_User, TRUE /*bPerfResets*/, osRunInfo[iR].BEMProcIdx() );
						}
            }

				if ((!bAbort && !BEMPX_AbortRuleEvaluation()) || bForceXMLFileWriteDespiteAbort)		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
				{
				// SAC 6/25/12 - added code to export detailed XML file following analysis
			      //QString sXMLFileName = sOriginalFileName;		//assert( sXMLFileName.lastIndexOf('.') == sXMLFileName.length()-4 );
//					if (!sXMLResultsFileName.isEmpty() && bStoreHourlyResults && !bThisOSSimSkipped)
					if (!sXMLResultsFileName.isEmpty() && bStoreHourlyResults && bSimRunsNow)
					{	for (int iR=0; iR <= iSimRunIdx; iR++)
							if (osRunInfo[iR].OSRunIdx() >= 0 && osRunInfo[iR].RunID().length() > 0)
							{			if (bVerbose)		// SAC 4/23/20 - moved down INSIDE iR run loop
											BEMPX_WriteLogFile( QString::asprintf( "  PerfAnal_NRes - Exporting %s model details to results XML", osRunInfo[iR].RunID().toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								// SAC 1/6/15 - added args to prevent export of PolyLp objects (and in turn, also CartesianPts)
								// SAC 1/11/15 - added new argument to prevent export of RULE NEW (ruleset-defined) properties to all models following User Model
								BOOL bXMLWriteOK = xmlResultsFile.WriteModel( TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, osRunInfo[iR].LongRunID().toLocal8Bit().constData(),
																								osRunInfo[iR].BEMProcIdx(), false /*bOnlyValidInputs*/, iAnalysisResultsXML_NumClassIDsToIgnore /*iNumClassIDsToIgnore*/, iAnalysisResultsXML_ClassIDsToIgnore /*piClassIDsToIgnore*/,   // SAC 02/07/22 (tic #3345)
																								bWriteRulePropsToResultsXML /*bWritePropertiesDefinedByRuleset*/, true /*bUseReportPrecisionSettings*/ );			assert( bXMLWriteOK );
								if (bVerbose)  // SAC 1/31/13
									BEMPX_WriteLogFile( QString::asprintf( "      Writing of %s model XML project data successful: %s", osRunInfo[iR].RunID().toLocal8Bit().constData(), (bXMLWriteOK ? "True" : "False") ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}		}
				}
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14

			if (bSimRunsNow)		// SAC 8/19/15
			{	iSimRunIdx = iProgressModelSum = 0;
			}
			else if (bModelToBeSimulated[iRun])
				iSimRunIdx++;

			}

		}	// end of:  for iRun = 0-iNumRuns
		if (iRetVal == 0)
			xmlResultsFile.Close();

      // implemented final NRCCPRF XML output code based on Res analysis - SAC 11/26/20
		//if (iRunIdx == iRunIdxFinalNRCC && ResRetVal_ContinueProcessing( iRetVal ) && iNRCCXMLClassID > 0 && !sNRCCXMLFileName.isEmpty() && lAnalysisType > 0)		// SAC 3/5/18 - NRCCPRF01E Final results storage  // SAC 4/15/20 - revise to use Std design for EAA runs
		if (iRetVal == 0 && iNRCCXMLClassID > 0 && !sNRCCXMLFileName.isEmpty() && iCUACReportID < 1)  // && lAnalysisType > 0)	
		{
			iPrevRuleErrs = BEMPX_GetRulesetErrorCount();
   							if (bVerbose || ebLogAnalysisMsgs)    // SAC 10/22/21
									BEMPX_WriteLogFile( QString( "  PerfAnal_NRes - %1 prep rules" ).arg( qsSchemaXMLFileDescrip ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   		BOOL bChkEvalSuccessful = CMX_EvaluateRuleset( "rl_NRCCPRF" , bVerbose, FALSE /*bTagDataAsUserDefined*/, bVerbose, NULL, NULL, NULL, pCompRuleDebugInfo );     // SAC 11/27/20    //, &saPreAnalChkWarningMsgs );
			BEMPX_RefreshLogFile();
			if (BEMPX_GetRulesetErrorCount() > iPrevRuleErrs && iDontAbortOnErrorsThruStep < 8)
			{
//											81 : Error(s) encountered performing NRCCPRF XML export prep rules
					iRetVal = (iRetVal > 0 ? iRetVal : 81);
					bAbort = true;
			}
         //iRV2 = LocalEvaluateRuleset(	sErrorMsg, BEMAnal_CECRes_CF1RXMLFinalError, "CF1RPRF01E_Final",	bVerbose, pCompRuleDebugInfo );
			//if (iRV2 > 0)
			//	iRetVal = iRV2;
			//// moved up here from after Run loop so that the CF1RPRF01EFile is written before switching over to subsequent (RESNET) models - SAC 4/12/20
			//else
			//{
            //	sLogMsg.clear();
				//	QString sEncodedInput;
				//	long lEncInpRetVal = EncodeBase64FromFile( pszFullPath, sEncodedInput );
				//	if (lEncInpRetVal < 0)
				//		sLogMsg = QString( "   Error Encoding Input for inclusion in NRCC XML file (EncodeBase64FromFile returned %1)" ).arg( QString::number(lEncInpRetVal) );
				//	else if (sEncodedInput.length() < 1)
				//		sLogMsg = QString( "   Error Encoding Input for inclusion in NRCC XML file (nothing returned from EncodeBase64FromFile)" );
				//	else
				//	{	int iEncSetRetVal = BEMPX_SetBEMData( BEMPX_GetDatabaseID( "nrccComplianceDocumentPackage:afterchildren_Input" ), BEMP_QStr, (void*) &sEncodedInput );	// SAC 5/3/19 - InputData -> Input
				//		if (iEncSetRetVal < 0)
				//			sLogMsg = QString( "   Error setting encoded input file to BEMBase for NRCC XML export (BEMPX_SetBEMData returned %1)" ).arg( QString::number(iEncSetRetVal) );
				//	}
				//	if (!sLogMsg.isEmpty())
				//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

				BOOL bXMLWriteOK = xmlNRCCPRFFile.WriteCF1RPRF01E( iNRCCXMLClassID, TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, -1 /*iBEMProcIdx*/,
																					false /*bOnlyValidInputs*/, true /*bWritePropertiesDefinedByRuleset*/, false /*bUseReportPrecisionSettings*/, BEMFT_NRCCXML /*iFileType*/ );
																	assert( bXMLWriteOK );
				if (bVerbose || pCompRuleDebugInfo != NULL)  // SAC 1/31/13
				{	sLogMsg = QString( "      Writing of %1 file successful: %2" ).arg( qsSchemaXMLFileDescrip, (bXMLWriteOK ? "True" : "False") );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				xmlNRCCPRFFile.Close();
			//}
         			dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();	
		}

		if (iRetVal == 0 && iCodeType == CT_T24N)
		{	// SAC 8/28/17 - moved some results code up here to enable Pass/Fail result to impact bSendRptSignature
			bHaveResult = (	!bAbort && iRetVal == 0 &&
									!sXMLResultsFileName.isEmpty() && FileExists( sXMLResultsFileName.toLocal8Bit().constData() ) &&
									iAnalysisThruStep >= 8 && !pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] &&
									BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:PassFail"   ), sResTemp1 ) &&
									BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:Enduse8[8]" ), sResTemp2 ) );
			bResultIsPass = (bHaveResult && (sResTemp1.indexOf("PASS") >= 0 || sResTemp1.indexOf("Pass") >= 0 || sResTemp1.indexOf("pass") >= 0));

		// possible mods needed here OR where 'PASS' originally set if we need to switch result to FAIL when iNumPropClgUMLHViolations or iNumPropHtgUMLHViolations > 0 - SAC 4/6/20

		}

      // perform CUAC analysis/calcs - SAC 09/09/22
      if (iRetVal == 0 && iCUACReportID > 0)
      {
         if (sCUACInvalidMsg.isEmpty())      // SAC 01/02/25
         {  if (iDLLCodeYear > 0 && iRulesetCodeYear > 0 && iDLLCodeYear != iRulesetCodeYear)
               sCUACInvalidMsg = QString::asprintf( "Inconsistent software library year (%d) and ruleset code year (%d)", iDLLCodeYear, iRulesetCodeYear );
				else if (bBypassInputChecks)
               sCUACInvalidMsg = "Input checks bypassed";
				else if (bBypassUMLHChecks)
               sCUACInvalidMsg = "Unmet load hour checks bypassed";
				else if (bBypassPreAnalysisCheckRules)
               sCUACInvalidMsg = "Pre-analysis check rules bypassed";
				else if (bBypassCheckSimRules)
               sCUACInvalidMsg = "Simulation check rules bypassed";
				else if (bBypassCheckCodeRules)
               sCUACInvalidMsg = "Energy code checking rules bypassed";
				else if (lQuickAnalysis > 0)
               sCUACInvalidMsg = "QuickAnalysis option activated";
				else if (bIgnoreFileReadErrors)
               sCUACInvalidMsg = "File read errors ignored";
				else if (bBypassValidFileChecks)
               sCUACInvalidMsg = "File validity checks bypassed";
				else if (!sExcptDsgnModelFile.isEmpty())
               sCUACInvalidMsg = "Alternative proposed simulation IDF file specified";
				else if (!sCSEIncludeFileDBID.isEmpty())
               sCUACInvalidMsg = "User specification of CSE include file(s)";
				else if (lNumSpaceWithDefaultedDwellingUnitArea > 0)
               sCUACInvalidMsg = "# dwelling unit areas not specified";
				else if (iNumFileOpenDefaultingRounds != 3)
               sCUACInvalidMsg = "Number of model defaulting rounds overridden";
				else if (bSimulateCSEOnly)
               sCUACInvalidMsg = "Option to skip past EPlus simulations specified";
				else if (lNumUserSpecMats > 0)
               sCUACInvalidMsg = "Construction Mats defined by user-specified properties";
            else if (lEnableResearchMode > 0)
               sCUACInvalidMsg = "EnableResearchMode activated";
            else if (lNumAutosizedResHtPumps > 0)
               sCUACInvalidMsg = "Autosized Residential HtPumps";
            else if (lNumResVCHP2HtPumps > 0)
               sCUACInvalidMsg = "VCHP2 Residential HtPumps";
            else if (lCSESimSpeedOption > 0)
               sCUACInvalidMsg = "CSE simulation mode not set to 0:Compliance";
            else if (iCustomMeterOption > 0)
               sCUACInvalidMsg = "CustomMeterOption specified";
         }

         long lBatchRateIdx=0;
         BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:BatchRateIdx" ), lBatchRateIdx );
         if (lBatchRateIdx > 0)
            CUAC_AnalysisProcessing_BatchRates( sProcessingPath, sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear, bStoreBEMDetails, bSilent, bVerbose,
                                     bResearchMode, pCompRuleDebugInfo, pszErrorMsg, iErrorMsgLen, bAbort, iRetVal, sErrMsg, iCUACReportID, iCUAC_BEMProcIdx, 0 /*com*/, iLogCUACBillCalcDetails,
                                     iSecurityKeyIndex, (pszSecurityKey ? pszSecurityKey : NULL),
                                     (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
                                     (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
                                     (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
                                     iRptGenConnectTimeout, iRptGenReadWriteTimeout, iDownloadVerbose, 
                                     (sCUACInvalidMsg.isEmpty()         ? NULL : (const char*) sCUACInvalidMsg.toLocal8Bit().constData()) );   // SAC 01/02/25
         else
         {  CUAC_AnalysisProcessing( sProcessingPath, sModelPathOnly, sModelFileOnly, qsBEMBaseDir, iRulesetCodeYear, bStoreBEMDetails, bSilent, bVerbose,
                                     bResearchMode, pCompRuleDebugInfo, pszErrorMsg, iErrorMsgLen, bAbort, iRetVal, sErrMsg, iCUACReportID, iCUAC_BEMProcIdx, 0 /*com*/,
                                     iLogCUACBillCalcDetails, iDownloadVerbose, true /*bWritePDF*/, true /*bWriteCSV*/, 0 /*iBatchRunIdx*/,
                                     (sCUACInvalidMsg.isEmpty()         ? NULL : (const char*) sCUACInvalidMsg.toLocal8Bit().constData()) );   // SAC 01/02/25
                        //   CSERunLoop( iSimRunIdx, posSimInfo, pqsCSESimStatusMsg, bStoreHourlyResults, sProcessingPath, sModelPathOnly, sModelFileOnly, bSecureT24NRptGenActivated,
                        //                  bPerformFullCSESim, bBypassRecircDHW, lNumPVArraysChk, bEnablePVBattSim, pszUIVersionString,
                        //                  sCSEexe, sCSEEXEPath, qsCSEName, sAnnualWeatherFile,
                        //                  iCodeType, iRulesetCodeYear, lAnalysisType, iDontAbortOnErrorsThruStep, iAnalStep, bProposedOnly, bStoreBEMDetails,
                        //                  bSilent, bVerbose, bResearchMode, pCompRuleDebugInfo, sCSEIncludeFileDBID, sCSEVersion, pszErrorMsg, iErrorMsgLen,
                        //                  bAbort, iRetVal, sErrMsg, sStdDsgnCSEResultsPathFile, iCUACReportID, iCustomMeterOption );
            for (auto& dnldRateFile : svUtilRatesToDelete)     // delete downloaded rate file(s) - SAC 09/27/23
               DeleteFile( dnldRateFile.c_str() );
         }
         if (iRetVal > 0)
         {  if (sErrMsg.isEmpty())
            {  if (iErrorMsgLen > 0 && pszErrorMsg)
                  sErrMsg = pszErrorMsg;
               else
                  sErrMsg = QString( "Error: Unable to calculate CUAC utility bills and/or generate reports/output." );
            }
            ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 96 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
            //											96 : Error calculating CUAC utility bill(s)
      }  }

	// AnalysisAction - End / AfterAnalPostProc processing   - SAC 11/17/20
		if (iRetVal == 0 && !bAbort)
			MidAnalysis_ApplyAnalysisActionToDatabase( BEMAnalActPhase_End, BEMAnalActWhen_End_AfterAnalPostProc, sErrMsg, bAbort, iRetVal,
																		77 /*iErrID*/, bVerbose, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );	// SAC 11/17/20

	// ----------
	// COMPLIANCE REPORT GENERATION   - SAC 9/14/13
		if (iRetVal == 0 && iCodeType == CT_T24N && (bComplianceReportPDF || bComplianceReportXML || bComplianceReportStd) && !sXMLResultsFileName.isEmpty())		// SAC 10/7/14 - added check to require iCodeType == CT_T24N (no rpt gen reports for 90.1 analysis)
		{	if (sXMLResultsFileName.isEmpty() || !FileExists( sXMLResultsFileName.toLocal8Bit().constData() ) || iAnalysisThruStep < 8 || !sIDFToSimulate.isEmpty() ||
					pbBypassOpenStudio[0] || pbBypassOpenStudio[1] || pbBypassOpenStudio[2] || pbBypassOpenStudio[3] ) // ||
			//		pbBypassSimulation[0] || pbBypassSimulation[1] || pbBypassSimulation[2] || pbBypassSimulation[3] )
			{
			}
			else
			{
#ifdef CM_QTGUI
							if (!bAbort && !BEMPX_AbortRuleEvaluation() && bDisplayProgress)  // only increment to 'Results' item after LAST run
							{	iProgressRetVal = NRes_ProgressIncrement( iCodeType, BCM_NRP_ComplianceProgressID( iProgressType, iProgressStep = BCM_NRP_Step_Report, 0 /*lModels*/, 0 /*lSimProg*/ ) );
								if (iProgressRetVal == 0)
									ProcessNonResAnalysisAbort( iCodeType, iProgressStep, sErrMsg, bAbort, iRetVal, pszErrorMsg, iErrorMsgLen );
							}
#endif

				if (iRetVal == 0)
				{
					//const char* pszProxyServerAddress     = (sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()    );
					//const char* pszProxyServerCredentials = (sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData());
					//const char* pszProxyServerType        = (sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()       );	// SAC 11/4/15
					//const char* pszNetComLibrary          = (sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()         );	// SAC 11/5/15

		//			int iRpt    = 0;  // (bComplianceReportPDF ? 0 : 1);
		//			int iMaxRpt = 2;  // (bComplianceReportXML ? 1 : 0);
		//			bool baDoRpt[] = { bComplianceReportPDF, bComplianceReportXML, bComplianceReportStd };		// SAC 11/13/15
		//			int iNumRptsToGen = (bComplianceReportPDF ? 1 : 0);
		//			if (bComplianceReportXML)
		//				iNumRptsToGen++;
		//			if (bComplianceReportStd)
		//				iNumRptsToGen++;
		// SAC 8/24/17 - replaced above w/ following to enable single-pass rpt gen
					QString sRptIDStr, sRptFileExt;
					long lRptIDNum = -1;		// SAC 8/24/17 - enable specification of a report ID number Component:Property name
					long lDBID_RptIDNum = BEMPX_GetDatabaseID( "Proj:CompReportNum" );
					bool bRptToGen = false, bRptVerbose = (bVerbose || bReportGenVerbose);	// SAC 3/20/20
					if (lDBID_RptIDNum > BEM_COMP_MULT)
					{	if (!BEMPX_GetInteger( lDBID_RptIDNum, lRptIDNum, -1 ))
							lRptIDNum = -1;
						else
						{	bRptToGen = (lRptIDNum > 0);
							sRptIDStr = "Proj:CompReportNum";
							sRptFileExt = "xml";
					}	}
					else
					{	bRptToGen = (bComplianceReportPDF || bComplianceReportXML);  // no Std rpt output w/out Proj:CompReportNum - || bComplianceReportStd );
						if (bComplianceReportPDF && bComplianceReportXML)
							sRptIDStr = "both";
						else if (bComplianceReportPDF)
							sRptIDStr = "true";
						if (bComplianceReportXML)
							sRptFileExt = "xml";
						else
							sRptFileExt = "pdf";
					}

					if (bRptToGen && iEnableRptGenStatusChecks > 0)
					{	// confirm that report generator is accessible before calling for the report(s) to be generated
						int iRptGenAvail = CMX_CheckSiteAccess( "Proj:RptGenCheckURL", sCACertPath.toLocal8Bit().constData(),
																				(sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
																				(sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
																				NULL /*pszErrMsg*/, 0, bVerbose, 
																				(sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
																				(sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()) );
						if (iRptGenAvail > -10)
						{	// rpt gen NOT available
							BEMPX_WriteLogFile( QString::asprintf( "Compliance report(s) called for but bypassed due to %s.", (iRptGenAvail<0 ? "report generation being offline" : "report generator website not accessible") ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							// iRetVal = 45;
							bRptToGen = false;  // iRpt = 1;	iMaxRpt = 0;
					}	}

					QString sLogMsg2;
		// SAC 8/24/17 - mods to support single-pass report generation
		//			for (; (iRetVal == 0 && iRpt <= iMaxRpt); iRpt++)
					if (bRptToGen && iRulesetCodeYear < 2022)  // baDoRpt[iRpt])      // toggle OFF generation of AnalysisResults report for 2022+ analysis - SAC 05/26/22
					{
						sLogMsg.clear();
						//	QString sMsg, sOutRptFN = (sProjFileName.lastIndexOf('.') > 0 ? sProjFileName.left( sProjFileName.lastIndexOf('.') ) : sProjFileName);
		//				QString sRptFileExt = (iRpt==1 ? "XML" : "PDF"), sOutRptFN = sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') );
		//				if (iRpt == 2)
		//					sOutRptFN += "-BEES-Std.";
		//				else
		//					sOutRptFN += "-BEES.";
		//				sOutRptFN += sRptFileExt;
						QString sOutRptFN;
						int iOrigRptIDNum = lRptIDNum;
						for (int iRptChk=0; iRptChk<3; iRptChk++)
						{	int iRptBitChk = (iRptChk==0 ? 1 : (iRptChk==1 ? 2 : 4));
							if (iRptChk==0 || lRptIDNum & iRptBitChk)
							{	QString sRptChkExt, sRptChkFNAppend, sRptChkDescrip;
								switch (iRptChk)
								{	case  0 :  sRptChkExt = "XML";  sRptChkFNAppend = "-BEES.";			break;
									case  1 :  sRptChkExt = "PDF";  sRptChkFNAppend = "-BEES.";			break;
									case  2 :  sRptChkExt = "PDF";  sRptChkFNAppend = "-BEES-Std.";	break;
								}
								sOutRptFN = QString( "%1%2%3" ).arg( sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') ), sRptChkFNAppend, sRptChkExt );
								sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
								             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
												 "(once the file is closed), or \n'Abort' to abort the %s.", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData(), "overwriting of this file" );
								if (!OKToWriteOrDeleteFile( sOutRptFN.toLocal8Bit().constData(), sMsg, bSilent ))
								{	if (iRptChk==0)
									{	if (bSilent)
											sLogMsg = QString::asprintf( "   Reporting disabled due to inability to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg = QString::asprintf( "   Reporting disabled due to user choosing not to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum = 0;  // toggle off generation of ALL reports
									}
									else
									{	if (bSilent)
											sLogMsg = QString::asprintf( "   Unable to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg = QString::asprintf( "   User chose not to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum -= iRptBitChk;  // toggle off generation of this rpt, but still proceed w/ others
									}
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									//iRetVal = 45;
								}
                        else if (FileExists( sOutRptFN ))      // added code to DELETE the old report file(s) prior to new report generation - SAC 10/01/21
                           DeleteFile( sOutRptFN.toLocal8Bit().constData() );
						}	}
						if (lRptIDNum > 0 && lRptIDNum != iOrigRptIDNum)
							// update RptIDNum in database to reflect report(s) removed from generation list in above loop
				      	BEMPX_SetBEMData( lDBID_RptIDNum, BEMP_Int, (void*) &lRptIDNum, BEMO_User, -1, BEMS_ProgDefault );

						if (lRptIDNum > 0 && bSendRptSignature && (!bHaveResult || !bResultIsPass ||		// toggle OFF report security if compliance result is undefined or 'Fail'
																				 iNumPropClgUMLHViolations > 0 || iNumPropHtgUMLHViolations > 0))		// prevent signature when UMLH limits exceeded
						{	// SAC 8/28/17 - prevent report signature if compliance result NOT PASS
							if (!bHaveResult)
								sLogMsg = "Compliance report will be generated without security measures due to compliance result not calculated";
							else if (!bResultIsPass)
								sLogMsg = "Compliance report will be generated without security measures due to non-passing compliance result";
							else if (iNumPropClgUMLHViolations > 0 || iNumPropHtgUMLHViolations > 0)		// SAC 4/6/20
							{	if (iNumPropClgUMLHViolations > 0 && iNumPropHtgUMLHViolations > 0)
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding cooling and %2 zone(s) exceeding heating unmet load hour limits" ).arg( QString::number(iNumPropClgUMLHViolations), QString::number(iNumPropHtgUMLHViolations) );
								else if (iNumPropClgUMLHViolations > 0)
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding cooling unmet load hour limits" ).arg( QString::number(iNumPropClgUMLHViolations) );
								else
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding heating unmet load hour limits" ).arg( QString::number(iNumPropHtgUMLHViolations) );
							}
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							bSendRptSignature = false;
						}

						if (lRptIDNum > 0)  // baDoRpt[iRpt])
						{
		//					QString sPDFOnly = "Proj:CompReportNum";  // SAC 8/24/17 - was: (iRpt!=1 ? "true" : "false");
							QString sDebugRpt = (bVerbose ? "true" : "false");
		//					QString sRptNameProp = (iRpt==2 ? "RptGenStdReport" : "RptGenCompReport");		// SAC 11/13/15
							QString sRptNameProp = "RptGenCompReport";

//BEMMessageBox( QString::asprintf( "Pausing before %s report generation on:  %s", (iRpt==0 ? "pdf" : "full"), sResFN ), "" );

									if (bVerbose)
		//							{	sLogMsg2 = QString::asprintf( "      about to generate %s compliance report:  %s", (iRpt!=1 ? "pdf" : "full"), sXMLResultsFileName.toLocal8Bit().constData() );
									{	sLogMsg2 = QString::asprintf( "      about to generate compliance report(s):  %s", sXMLResultsFileName.toLocal8Bit().constData() );
										BEMPX_WriteLogFile( sLogMsg2, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}

					// SAC 6/2/14 - added several ruleset-based reporting variables and incorporated them into the GenerateReport_CEC() prototype
							QString sRptGenUIApp, sRptGenUIVer, sRptGenCompReport, sRptGenCompRptID, sRptGenServer, sRptGenApp, sRptGenService, sSecKeyRLName;
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenUIApp"     , iCID_Proj ), sRptGenUIApp      );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenUIVer"     , iCID_Proj ), sRptGenUIVer      );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID(  sRptNameProp     , iCID_Proj ), sRptGenCompReport );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenCompRptID" , iCID_Proj ), sRptGenCompRptID  );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenServer"    , iCID_Proj ), sRptGenServer     );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenApp"       , iCID_Proj ), sRptGenApp        );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenService"   , iCID_Proj ), sRptGenService    );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "SecKeyRLName"    , iCID_Proj ), sSecKeyRLName     );

							dTimeToOther += DeltaTime( tmAnalOther );		// log time spent prior to this point to "other" bucket
							tmMark = boost::posix_time::microsec_clock::local_time();		// set timer for Report bucket

						//	int iRptGenRetVal = GenerateReport_CEC( sXMLResultsFileName /*sProjPath, sResFN*/, sCACertPath, "NRCC_PRF_01", "CBECC", "Com", "none" /*Signature*/,
							int iRptGenRetVal = GenerateReport_CEC( sXMLResultsFileName.toLocal8Bit().constData() /*sProjPath, sResFN*/, sCACertPath.toLocal8Bit().constData(), 
																	sRptGenCompReport.toLocal8Bit().constData(), sRptGenUIApp.toLocal8Bit().constData(), sRptGenUIVer.toLocal8Bit().constData(),
																	"none" /*Signature*/, "none" /*PublicKey*/, (pszSecurityKey ? pszSecurityKey : NULL) /*PrivateKey*/, 
																	(sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
																	(sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
																	sRptIDStr.toLocal8Bit().constData(), sDebugRpt.toLocal8Bit().constData(), bRptVerbose, bSilent, bSendRptSignature,
																	sRptGenCompRptID.toLocal8Bit().constData(), sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), 
																	sRptGenService.toLocal8Bit().constData(), sSecKeyRLName.toLocal8Bit().constData(), NULL /*pszOutputPathFile*/, 
																	(sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
																	(sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()), iSecurityKeyIndex, false, false, 		// SAC 11/5/15   // SAC 1/10/17   // SAC 8/25/17
                                                   iRptGenConnectTimeout, iRptGenReadWriteTimeout );    // SAC 11/02/22

							dTimeToReport += DeltaTime( tmMark );		// log time spent generating report
							iNumTimeToReport++; 
							tmAnalOther = boost::posix_time::microsec_clock::local_time();		// reset timer for "other" bucket
										if (bVerbose || iRptGenRetVal != 0)
		//								{	sLogMsg2 = QString::asprintf( "      generation of %s compliance report %s (returned %d)", (iRpt!=1 ? "pdf" : "full"), (iRptGenRetVal==0 ? "succeeded" : "failed"), iRptGenRetVal );
										{	sLogMsg2 = QString::asprintf( "      generation of compliance report(s) %s (returned %d)", (iRptGenRetVal==0 ? "succeeded" : "failed"), iRptGenRetVal );
											BEMPX_WriteLogFile( sLogMsg2, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
							if (iRptGenRetVal != 0)
							{	sLogMsg = QString::asprintf( "   Error (%d) encountered generating compliance report file:  %s", iRptGenRetVal, sOutRptFN.toLocal8Bit().constData() );
								//iRetVal = 46;
							}
							else
							{	bool bRetainXMLRptFile = (lRptIDNum & 1);		bool bExtCompPdf=true, bExtStdPdf=true;
								sOutRptFN = QString( "%1-BEES.xml" ).arg( sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') ) );
								if (lRptIDNum & 2)	// PDF Comp Rpt
								{	QString sOutPDFRptFN = QString( "%1-BEES.pdf" ).arg( sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') ) );
									if (!CMX_ExtractTitle24ReportFromXML( sOutRptFN.toLocal8Bit().constData(), sOutPDFRptFN.toLocal8Bit().constData(), "Report2", TRUE /*bSupressAllMessageBoxes*/ ))
									{	QString sExtractRptErr = QString( "Error encountered extracting PDF %1 report (%2) from XML: %3" ).arg( "Compliance", "Report2", sOutRptFN );
										BEMPX_WriteLogFile( sExtractRptErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										bRetainXMLRptFile = true;		bExtCompPdf = false;
								}	}
								if (lRptIDNum & 4)	// PDF Std Model Rpt
								{	QString sOutPDFRptFN = QString( "%1-BEES-Std.pdf" ).arg( sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') ) );
									if (!CMX_ExtractTitle24ReportFromXML( sOutRptFN.toLocal8Bit().constData(), sOutPDFRptFN.toLocal8Bit().constData(), "Report3", TRUE /*bSupressAllMessageBoxes*/ ))
									{	QString sExtractRptErr = QString( "Error encountered extracting PDF %1 report (%2) from XML: %3" ).arg( "Standard Model", "Report3", sOutRptFN );
										BEMPX_WriteLogFile( sExtractRptErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										bRetainXMLRptFile = true;		bExtStdPdf = false;
								}	}

							// CHECK FOR ERRORS in XML returned from report generator
								QString sRGErrs;
								int iNumRptGenErrs = ExtractErrorsFromTitle24ReportXML( sOutRptFN.toLocal8Bit().constData(), sRGErrs, TRUE /*bPostToProjectLog*/,
																											TRUE /*bPostToBEMProc*/, TRUE /*bSupressAllMessageBoxes*/ );
								if (iRetVal == 0 && iNumRptGenErrs > 0)
									iRetVal = 68;				// One or more errors returned from Compliance Report Generator - already logged by above call

								if (!bRetainXMLRptFile)
									// DELETE Full (XML) compliance report (if XML (full) report not requested & no errors logged there)
									DeleteFile( sOutRptFN.toLocal8Bit().constData() );

		//						QString sWrittenDBID = (iRpt==0 ? "CompReportPDFWritten" : (iRpt==1 ? "CompReportXMLWritten" : "CompReportStdWritten"));
		//				      BEMPX_SetBEMData( BEMPX_GetDatabaseID( sWrittenDBID, iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
								if (lRptIDNum & 1)	// SAC 8/24/17
						      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportXMLWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
								if (lRptIDNum & 2 && bExtCompPdf)
						      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportPDFWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
								if (lRptIDNum & 4 && bExtStdPdf)
						      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportStdWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
							}
						}
						if (!sLogMsg.isEmpty())
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}

            // added PDF report generation based on NRCC-PRF XML otuput file - SAC 04/10/21
					if (bRptToGen && bReportGenNRCCPRFXML && !sNRCCXMLFileName.isEmpty())
					{
						sLogMsg.clear();
						QString sOutRptFN;
						int iOrigRptIDNum = lRptIDNum;
                  // reduced iRptChk loop end from 2 to 1 - no "Std" version of NRCC-PRF XML reporting - SAC 04/10/21
						for (int iRptChk=0; iRptChk<2; iRptChk++)
						{	int iRptBitChk = (iRptChk==0 ? 1 : (iRptChk==1 ? 2 : 4));
							if (iRptChk==0 || lRptIDNum & iRptBitChk)
							{	QString sRptChkExt, sRptChkFNAppend, sRptChkDescrip;
								switch (iRptChk)
								{	case  0 :  sRptChkExt = "XML";  sRptChkFNAppend = "-BEES.";			break;
									case  1 :  sRptChkExt = "PDF";  sRptChkFNAppend = "-BEES.";			break;
								//	case  2 :  sRptChkExt = "PDF";  sRptChkFNAppend = "-BEES-Std.";	break;
								}
								sOutRptFN = QString( "%1%2%3" ).arg( sNRCCXMLFileName.left( sNRCCXMLFileName.lastIndexOf('.') ), sRptChkFNAppend, sRptChkExt );
								sMsg = QString::asprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
								             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
												 "(once the file is closed), or \n'Abort' to abort the %s.", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData(), "overwriting of this file" );
								if (!OKToWriteOrDeleteFile( sOutRptFN.toLocal8Bit().constData(), sMsg, bSilent ))
								{	if (iRptChk==0)
									{	if (bSilent)
											sLogMsg = QString::asprintf( "   Reporting disabled due to inability to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg = QString::asprintf( "   Reporting disabled due to user choosing not to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum = 0;  // toggle off generation of ALL reports
									}
									else
									{	if (bSilent)
											sLogMsg = QString::asprintf( "   Unable to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg = QString::asprintf( "   User chose not to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum -= iRptBitChk;  // toggle off generation of this rpt, but still proceed w/ others
									}
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									//iRetVal = 45;
								}
                        else if (FileExists( sOutRptFN ))      // added code to DELETE the old report file(s) prior to new report generation - SAC 10/01/21
                           DeleteFile( sOutRptFN.toLocal8Bit().constData() );
						}	}
                  // no mods to BEMBase for NRCC-PRF reporting - until it is the main report generated - SAC 04/10/21  // restored - SAC 10/19/22
						if (lRptIDNum > 0 && lRptIDNum != iOrigRptIDNum)
							// update RptIDNum in database to reflect report(s) removed from generation list in above loop
				      	BEMPX_SetBEMData( lDBID_RptIDNum, BEMP_Int, (void*) &lRptIDNum, BEMO_User, -1, BEMS_ProgDefault );

                  // restore once the NRCC-PRF report is the MAIN permit report - until then bSendRptSignature will be set above - SAC 04/10/21  // restored - SAC 10/19/22
						if (lRptIDNum > 0 && bSendRptSignature && (!bHaveResult || !bResultIsPass ||		// toggle OFF report security if compliance result is undefined or 'Fail'
																				 iNumPropClgUMLHViolations > 0 || iNumPropHtgUMLHViolations > 0))		// prevent signature when UMLH limits exceeded
						{	// SAC 8/28/17 - prevent report signature if compliance result NOT PASS
							if (!bHaveResult)
								sLogMsg = "Compliance report will be generated without security measures due to compliance result not calculated";
							else if (!bResultIsPass)
								sLogMsg = "Compliance report will be generated without security measures due to non-passing compliance result";
							else if (iNumPropClgUMLHViolations > 0 || iNumPropHtgUMLHViolations > 0)		// SAC 4/6/20
							{	if (iNumPropClgUMLHViolations > 0 && iNumPropHtgUMLHViolations > 0)
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding cooling and %2 zone(s) exceeding heating unmet load hour limits" ).arg( QString::number(iNumPropClgUMLHViolations), QString::number(iNumPropHtgUMLHViolations) );
								else if (iNumPropClgUMLHViolations > 0)
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding cooling unmet load hour limits" ).arg( QString::number(iNumPropClgUMLHViolations) );
								else
									sLogMsg = QString( "Compliance report will be generated without security measures due to %1 zone(s) exceeding heating unmet load hour limits" ).arg( QString::number(iNumPropHtgUMLHViolations) );
							}
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							bSendRptSignature = false;
						}

						if (lRptIDNum > 0)  // baDoRpt[iRpt])
						{
							QString sDebugRpt = (bVerbose ? "true" : "false");
							QString sRptNameProp = "NRCC_RptGenCompReport";       // SAC 04/10/21
                     //BEMMessageBox( QString::asprintf( "Pausing before %s report generation on:  %s", (iRpt==0 ? "pdf" : "full"), sResFN ), "" );
									if (bVerbose)
									{	sLogMsg2 = QString::asprintf( "      about to generate compliance report(s):  %s", sNRCCXMLFileName.toLocal8Bit().constData() );
										BEMPX_WriteLogFile( sLogMsg2, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}

   					// SAC 6/2/14 - added several ruleset-based reporting variables and incorporated them into the GenerateReport_CEC() prototype
							QString sRptGenUIApp, sRptGenUIVer, sRptGenCompReport, sRptGenCompRptID, sRptGenServer, sRptGenApp, sRptGenService, sSecKeyRLName;
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenUIApp"       , iCID_Proj ), sRptGenUIApp      );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenUIVer"       , iCID_Proj ), sRptGenUIVer      );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID(  sRptNameProp       , iCID_Proj ), sRptGenCompReport );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "RptGenCompRptID"   , iCID_Proj ), sRptGenCompRptID  );
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "NRCC_RptGenServer" , iCID_Proj ), sRptGenServer     );   // SAC 04/10/21
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "NRCC_RptGenApp"    , iCID_Proj ), sRptGenApp        );   // SAC 04/10/21
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "NRCC_RptGenService", iCID_Proj ), sRptGenService    );   // SAC 04/11/21
      	   			BEMPX_GetString( BEMPX_GetDatabaseID( "SecKeyRLName"      , iCID_Proj ), sSecKeyRLName     );

							dTimeToOther += DeltaTime( tmAnalOther );		// log time spent prior to this point to "other" bucket
							tmMark = boost::posix_time::microsec_clock::local_time();		// set timer for Report bucket

						//	int iRptGenRetVal = GenerateReport_CEC( sNRCCXMLFileName /*sProjPath, sResFN*/, sCACertPath, "NRCC_PRF_01", "CBECC", "Com", "none" /*Signature*/,
							int iRptGenRetVal = GenerateReport_CEC( sNRCCXMLFileName.toLocal8Bit().constData() /*sProjPath, sResFN*/, sCACertPath.toLocal8Bit().constData(), 
																	sRptGenCompReport.toLocal8Bit().constData(), sRptGenUIApp.toLocal8Bit().constData(), sRptGenUIVer.toLocal8Bit().constData(),
																	"none" /*Signature*/, "none" /*PublicKey*/, (pszSecurityKey ? pszSecurityKey : NULL) /*PrivateKey*/, 
																	(sProxyServerAddress.isEmpty()     ? NULL : (const char*) sProxyServerAddress.toLocal8Bit().constData()), 
																	(sProxyServerCredentials.isEmpty() ? NULL : (const char*) sProxyServerCredentials.toLocal8Bit().constData()), 
																	sRptIDStr.toLocal8Bit().constData(), sDebugRpt.toLocal8Bit().constData(), bRptVerbose, bSilent, bSendRptSignature,
																	sRptGenCompRptID.toLocal8Bit().constData(), sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), 
																	sRptGenService.toLocal8Bit().constData(), sSecKeyRLName.toLocal8Bit().constData(), NULL /*pszOutputPathFile*/, 
																	(sProxyServerType.isEmpty()        ? NULL : (const char*) sProxyServerType.toLocal8Bit().constData()), 
																	(sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()), iSecurityKeyIndex,		// SAC 11/5/15   // SAC 1/10/17   // SAC 8/25/17
                                                   false /*bFinalPDFGeneration*/, true /*bSchemaBasedRptGen*/, iRptGenConnectTimeout, iRptGenReadWriteTimeout );     // SAC 04/11/21   // SAC 11/02/22
							dTimeToReport += DeltaTime( tmMark );		// log time spent generating report
							iNumTimeToReport++; 
							tmAnalOther = boost::posix_time::microsec_clock::local_time();		// reset timer for "other" bucket
										if (bVerbose || iRptGenRetVal != 0)
										{	sLogMsg2 = QString::asprintf( "      generation of compliance report(s) %s (returned %d)", (iRptGenRetVal==0 ? "succeeded" : "failed"), iRptGenRetVal );
											BEMPX_WriteLogFile( sLogMsg2, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
							if (iRptGenRetVal != 0)
							{	sLogMsg = QString::asprintf( "   Error (%d) encountered generating compliance report file:  %s", iRptGenRetVal, sOutRptFN.toLocal8Bit().constData() );
								//iRetVal = 46;
							}
							else
							{	bool bRetainXMLRptFile = (lRptIDNum & 1);		bool bExtCompPdf=true, bExtStdPdf=true;
								sOutRptFN = QString( "%1-BEES.xml" ).arg( sNRCCXMLFileName.left( sNRCCXMLFileName.lastIndexOf('.') ) );
								if (lRptIDNum & 2)	// PDF Comp Rpt
								{	QString sOutPDFRptFN = QString( "%1-BEES.pdf" ).arg( sNRCCXMLFileName.left( sNRCCXMLFileName.lastIndexOf('.') ) );
                           QString qsPayldTransID, qsPayldProcDateTime;    // SAC 12/05/21
                           const char* saPayloadAttribs[] = { "complianceDocumentGUID", "processedDate", NULL };
                           QString* qsaPayloadAttribStrings[] = { &qsPayldTransID, &qsPayldProcDateTime, NULL };
									if (!CMX_ExtractTitle24ReportFromXML( sOutRptFN.toLocal8Bit().constData(), sOutPDFRptFN.toLocal8Bit().constData(), "Report2", TRUE /*bSupressAllMessageBoxes*/,
                                                                 saPayloadAttribs, qsaPayloadAttribStrings ))
									{	QString sExtractRptErr = QString( "Error encountered extracting PDF %1 report (%2) from XML: %3" ).arg( "Compliance", "Report2", sOutRptFN );
										BEMPX_WriteLogFile( sExtractRptErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										bRetainXMLRptFile = true;		bExtCompPdf = false;
									}
                           else     // store NRCC PRF report gen transaction ID & date/time to BEMBase - SAC 12/05/21
                           {  //BEMPX_WriteLogFile( QString( "              CMX_ExtractTitle24ReportFromXML() - PayldTransID '%1'  PayldProcDateTime '%2'" ).arg( qsPayldTransID, qsPayldProcDateTime ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              long lDBID_NRCCPRFPayldTransID  = BEMPX_GetDatabaseID( "EUseSummary:NRCCPRFPayldTransID" );
                              long lDBID_NRCCPRFPayldProcDate = BEMPX_GetDatabaseID( "EUseSummary:NRCCPRFPayldProcDate" );
                              if (!qsPayldTransID.isEmpty() && lDBID_NRCCPRFPayldTransID > 0)
                                 BEMPX_SetBEMData( lDBID_NRCCPRFPayldTransID, BEMP_QStr, (void*) &qsPayldTransID, BEMO_User, 0 );  //, BEMS_ProgDefault );
                              if (!qsPayldProcDateTime.isEmpty() && lDBID_NRCCPRFPayldProcDate > 0)
                                 BEMPX_SetBEMData( lDBID_NRCCPRFPayldProcDate, BEMP_QStr, (void*) &qsPayldProcDateTime, BEMO_User, 0 );  //, BEMS_ProgDefault );
                           }
                        }
								if (lRptIDNum & 4)	// PDF Std Model Rpt
								{	QString sOutPDFRptFN = QString( "%1-BEES-Std.pdf" ).arg( sNRCCXMLFileName.left( sNRCCXMLFileName.lastIndexOf('.') ) );
									if (!CMX_ExtractTitle24ReportFromXML( sOutRptFN.toLocal8Bit().constData(), sOutPDFRptFN.toLocal8Bit().constData(), "Report3", TRUE /*bSupressAllMessageBoxes*/ ))
									{	QString sExtractRptErr = QString( "Error encountered extracting PDF %1 report (%2) from XML: %3" ).arg( "Standard Model", "Report3", sOutRptFN );
										BEMPX_WriteLogFile( sExtractRptErr, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										bRetainXMLRptFile = true;		bExtStdPdf = false;
								}	}

							// CHECK FOR ERRORS in XML returned from report generator
								QString sRGErrs;
								int iNumRptGenErrs = ExtractErrorsFromTitle24ReportXML( sOutRptFN.toLocal8Bit().constData(), sRGErrs, TRUE /*bPostToProjectLog*/,
																											TRUE /*bPostToBEMProc*/, TRUE /*bSupressAllMessageBoxes*/ );
            // don't alter the main PerfAnal return value until NRCC-PRF report is the MAIN permit report - SAC 04/10/21
				//				if (iRetVal == 0 && iNumRptGenErrs > 0)
				//					iRetVal = 68;				// One or more errors returned from Compliance Report Generator - already logged by above call

								if (!bRetainXMLRptFile)
									// DELETE Full (XML) compliance report (if XML (full) report not requested & no errors logged there)
									DeleteFile( sOutRptFN.toLocal8Bit().constData() );

            // don't alter BEMBase CompReport* properties until NRCC-PRF report is the MAIN permit report - SAC 04/10/21
				//				long lOne = 1;
				//				if (lRptIDNum & 1)	// SAC 8/24/17
				//		      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportXMLWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
				//				if (lRptIDNum & 2 && bExtCompPdf)
				//		      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportPDFWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
				//				if (lRptIDNum & 4 && bExtStdPdf)
				//		      	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "CompReportStdWritten", iCID_Proj ), BEMP_Int, (void*) &lOne, BEMO_User, -1, BEMS_ProgDefault );
							}
						}
						if (!sLogMsg.isEmpty())
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
			}	}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}
	// end of: COMPLIANCE REPORT GENERATION   - SAC 9/14/13
	// ----------

	// SAC 5/22/19 - added code to remove E+ processing directories here, @ end of analysis to avoid deletion errors
		int iNumEPlusProcDirs = (int) saEPlusProcDirsToBeRemoved.size();
		if (iNumEPlusProcDirs > 0)
		{	if (!sProcessingPath.isEmpty())
			{	SetCurrentDirectory( sProcessingPath.toLocal8Bit().constData() );
				//BEMPX_WriteLogFile( "   current directory set to processing path", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
			for (int iEPDir=0; iEPDir<iNumEPlusProcDirs; iEPDir++)
			{	std::string sEPlusDirToDel = saEPlusProcDirsToBeRemoved[iEPDir].toLocal8Bit().constData();
				try
				{	/*boost::uintmax_t uiNumDeleted =*/ boost::filesystem::remove_all( sEPlusDirToDel.c_str() );
				}
				catch (const boost::filesystem::filesystem_error& ex)
				{	std::string sFailMsg = boost::str( boost::format( "    during simulation file clean-up, unable to remove directory:  %s  - %s" ) % sEPlusDirToDel.c_str() % ex.what() );
					BEMPX_WriteLogFile( sFailMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}	}	}
	}

// SAC 1/24/14 - added code to address file pruning - iAnalysisStorage >= 3 => keep ALL files
	if (iAnalysisStorage >= 0 && iAnalysisStorage < 3 && saSimulatedRunIDs.size() > 0 && iRetVal == 0)
	{	std::string sFileToDel, sFailMsg;
		// data defining which files get deleted        - for iAnalysisStorage =  0  1  2
		NRFilePruneInfo fpInfo[] = {	{	".xml",                 true,  true,   { 1, 0, 0 } },
												{	".osm",                 true,  true,   { 1, 1, 0 } },
												{	".ibd-Detail",          false, false,  { 1, 1, 1 } },
												{	".ibd-Detail",          true,  false,  { 1, 1, 1 } },
												{	".ibd-Detail-B4Eval",   true,  false,  { 1, 1, 1 } },
												{	".ibd-Detail-PostSim",  true,  false,  { 1, 1, 1 } },
												{	"",                     true,  false,  { 1, 1, 1 } } };
		for (int iR=0; iR < saSimulatedRunIDs.size(); iR++)
		{	int iFP = -1;
			while (fpInfo[++iFP].sFileExt.size() > 1)
			{	if (fpInfo[iFP].iaDelForOptVal[iAnalysisStorage] && (iR == 0 || fpInfo[iFP].bFNameInclRunID))
				{	if (fpInfo[iFP].bFNameInclRunID)
						sFileToDel = boost::str( boost::format( "%s%s - %s%s" ) % sProcessingPath.toLocal8Bit().constData() % sModelFileOnly.toLocal8Bit().constData() % 
																									saSimulatedRunIDs[iR].toLocal8Bit().constData() % fpInfo[iFP].sFileExt );
					else
						sFileToDel = boost::str( boost::format( "%s%s%s" ) % sProcessingPath.toLocal8Bit().constData() % sModelFileOnly.toLocal8Bit().constData() % 
																									fpInfo[iFP].sFileExt );
					BOOL bFileExists = FileExists( sFileToDel.c_str() );
					if (bFileExists)
					{	_chmod( sFileToDel.c_str(), _S_IREAD | _S_IWRITE );	// ensure file is writable so that it can be deleted down below
						if (!DeleteFile( sFileToDel.c_str() ))
						{	if (fpInfo[iFP].bReportFailure)
							{	sFailMsg = boost::str( boost::format( "    during analysis file clean-up, error deleting file:  %s" ) % sFileToDel.c_str() );
								BEMPX_WriteLogFile( sFailMsg.c_str(), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}	}	}
		}	}	}
	}


// SAC 1/23/14 - added code to setup FINAL result log message (including analysis duration stats)
	QString sAnalResLogMsg, sAnalTimeStats, sCUACResultsSummary;
   if (iCUACReportID > 0)     // SAC 01/02/25
      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ResultsSummary" ), sCUACResultsSummary );     // SAC 01/02/25
	if (bAbort)
		sAnalResLogMsg = "Analysis aborted";
	else if (iRetVal != 0 || sXMLResultsFileName.isEmpty() || !FileExists( sXMLResultsFileName.toLocal8Bit().constData() ))
		sAnalResLogMsg = "Analysis errant";
   else if (!sCUACResultsSummary.isEmpty())
      sAnalResLogMsg = sCUACResultsSummary;     // SAC 01/02/25
	else if (iAnalysisThruStep < 8 ||
					pbBypassOpenStudio[0] || pbBypassOpenStudio[1] || pbBypassOpenStudio[2] || pbBypassOpenStudio[3] ) // ||
			//		pbBypassSimulation[0] || pbBypassSimulation[1] || pbBypassSimulation[2] || pbBypassSimulation[3] )
		sAnalResLogMsg = "Analysis incomplete";
	else if (!bHaveResult)
		sAnalResLogMsg = "Analysis result unknown";
	else
	{	//sAnalResLogMsg = QString::asprintf( "Analysis result:  %s  (%s margin: %s)", sResTemp1.toLocal8Bit().constData(), (iRulesetCodeYear < 2025 ? "TDV" : "SLCC"), sResTemp2.toLocal8Bit().constData() );  // SAC 12/01/22
      sAnalResLogMsg = QString::asprintf( "Analysis result:  %s  (%s margin: %s)", sResTemp1.toLocal8Bit().constData(), qsCompMetricLbl_Short.toLocal8Bit().constData(), sResTemp2.toLocal8Bit().constData() );  // SAC 12/01/22  // SAC 01/26/23
		if (sResTemp2.indexOf(',') > 0)
		{	sResTemp2  = '\"' + sResTemp2;
			sResTemp2 += '\"';
	}	}

	dTimeToOther += DeltaTime( tmAnalOther );			// log time spent prior to this point to "other" bucket
	dTimeOverall += DeltaTime( tmAnalStartTime );	// log time spent over the entire analysis
	double dTimeTotTrans = 0.0, dTimeTotDsgn = 0.0, dTimeTotAnn = 0.0; 
	for (int itm=0; itm < MAX_TimeArray; itm++)
	{	dTimeTotTrans += dTimeToTranslate[itm];
		dTimeTotDsgn  += dTimeToSimDsgn[  itm];
		dTimeTotAnn   += dTimeToSimAnn[   itm];
	}
	assert( iNumDsgnSims >= iNumTimeToSimDsgn && iNumAnnSims >= iNumTimeToSimAnn );
	iNumTimeToSimDsgn += std::max( (iNumDsgnSims - iNumTimeToSimDsgn), 0 );
	iNumTimeToSimAnn  += std::max( (iNumAnnSims  - iNumTimeToSimAnn ), 0 );
	if (iNumTimeToTranslate > 1)
		dTimeTotTrans /= iNumTimeToTranslate;
	if (iNumTimeToSimDsgn   > 1)  
		dTimeTotDsgn  /= iNumTimeToSimDsgn  ;
	if (iNumTimeToSimAnn    > 1)  
		dTimeTotAnn   /= iNumTimeToSimAnn   ;
	sAnalTimeStats = QString::asprintf( "   processing time:  Overall %d:%.2d / SDD2IDF x%d%s%d:%.2d / SizSim x%d%s%d:%.2d / AnnSim x%d%s%d:%.2d / ReportGen x%d %d:%.2d / Other %d:%.2d",	// SAC 11/5/14 - 'SDD2OSM' -> 'SDD2IDF'
						int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)),
						iNumTimeToTranslate, (iNumTimeToTranslate > 1 ? " avg " : " "), int(dTimeTotTrans/60), int(fmod(dTimeTotTrans, 60.0)), 
						iNumTimeToSimDsgn  , (iNumTimeToSimDsgn   > 1 ? " avg " : " "), int(dTimeTotDsgn /60), int(fmod(dTimeTotDsgn , 60.0)), 
						iNumTimeToSimAnn   , (iNumTimeToSimAnn    > 1 ? " avg " : " "), int(dTimeTotAnn  /60), int(fmod(dTimeTotAnn  , 60.0)), 
						iNumTimeToReport, int(dTimeToReport/60), int(fmod(dTimeToReport, 60.0)), int(dTimeToOther/60), int(fmod(dTimeToOther, 60.0)) );
	//sAnalResLogMsg += sAnalTimeStats;
	BEMPX_WriteLogFile( sAnalResLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	BEMPX_WriteLogFile( sAnalTimeStats, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );     // separate results from time logging messages to better highlight results diffs between batches of runs - SAC 11/30/23

	if (!bAbort && !BEMPX_AbortRuleEvaluation())		// SAC 11/04/19 - separated out storage of CSV log formatted timestamp from pszResultsSummary population
	{	//CTime locTime = CTime::GetCurrentTime();
		QDateTime locTime = QDateTime::currentDateTime();
		QString sTimeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunDateLog", iCID_Proj ), BEMP_QStr, (void*) &sTimeStamp, BEMO_User, -1, BEMS_ProgDefault );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AnalysisDuration", iCID_Proj ), BEMP_Flt, &dTimeOverall, BEMO_User, -1, BEMS_ProgDefault );
	}

	if (bVerbose)
		BEMPX_WriteLogFile( QString::asprintf( "      Final return value from CMX_PerformAnalysis_CECNonRes():  %d", iRetVal ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	if (bRestoreBEMProcLogTimeStampSetting)		// SAC 11/17/13 - restore BEMProc log timestamp setting (if it was toggled during analysis)
		BEMPX_EnableLogTimeStamps( bInitialBEMProcLogTimeStamp );


// SAC 5/5/15 - ResultSummary Logging
		sLogMsg = QString::asprintf( "      ResultsSummary population:  bAbort = (%s) / RuleProcAbort = (%s) / iRetVal = %d / pszResultsSummary = %s / iResultsSummaryLen = %d", (bAbort ? "true" : "false"),
				(BEMPX_AbortRuleEvaluation() ? "true" : "false"), iRetVal, (pszResultsSummary  == NULL ? "(null)" : (strlen( pszResultsSummary  ) < 1 ? "(empty)" : pszResultsSummary )), iResultsSummaryLen );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

// SAC 5/16/14 - added code to populate record of analysis results
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && pszResultsSummary && iResultsSummaryLen > 1)
	{
		int iCSVRes_RetVal = CMX_PopulateCSVResultSummary_NonRes( pszResultsSummary, iResultsSummaryLen, pszModelPathFile, pszSimWeatherPath /*, int iEUseSummaryIdx=0*/ );	// SAC 11/04/19

// SAC 5/5/15 - ResultSummary Logging
		BEMPX_WriteLogFile( QString::asprintf( "      ResultsSummary:  %s", pszResultsSummary ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	}
	BEMPX_RefreshLogFile();	// SAC 5/19/14

// final analysis progress and callback calls...
	bool bAnalAborted = (bAllowAnalysisAbort && pAnalProgCallbackFunc && slAnalysisProgressCallbackRetVal > 0);
#ifdef CM_QTGUI
	if (!bAnalAborted && bAllowAnalysisAbort && sqt_progress && sqt_progress->wasCanceled())
		bAnalAborted = true;
#endif

	// SAC 5/28/15 - callback mechanism - report return value indicating abort via calling application callback
	if (pAnalProgCallbackFunc)
	{	if (slAnalysisProgressCallbackRetVal == 0 && !bAnalAborted)		// report 100% complete only for SUCCESSFUL analysis ???  (right now reporting 100% anytime analysis NOT aborted)
		{	long lCBRetVal = pAnalProgCallbackFunc( BCM_NRP_ComplianceProgressID( iProgressType, BCM_NRP_Step_Done, 0 /*lModels*/, 0 /*lSimProg*/ ), 100 );
			if (lCBRetVal > 0)
				slAnalysisProgressCallbackRetVal = lCBRetVal;
		}
		if (slAnalysisProgressCallbackRetVal > 0 && iRetVal != 52)
		{	iRetVal = 52;
//											52 : Analysis aborted via callback function in calling application
			//if (TRUE)  // bVerbose)
				BEMPX_WriteLogFile( QString::asprintf( "Analysis aborted due to callback function return value of %ld (value must be 0 to continue processing).", slAnalysisProgressCallbackRetVal ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}	}

#ifdef CM_QTGUI
// QT Progress Dialog stuff
	if (sqt_progress && sqt_win)
	{	//if (bVerbose)  // SAC 1/31/13
		//	BEMPX_WriteLogFile( "      about to hide QT progress dialog", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		sqt_progress->setValue(100);
		sqt_win->repaint();
	}
#endif

// QT Progress Dialog stuff
#ifdef CM_QTGUI
// TESTING
	if (bDisplayProgress && sqt_win)
	{	//if (bVerbose)  // SAC 1/31/13
		//	BEMPX_WriteLogFile( "      about to clean up QT progress dialog", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		sqt_win->close();
	}
	if (bQtAppInitHere)  // bDisplayProgress || bPromptUserUMLHWarning)
	{	delete sq_app;
		sq_app = NULL;
	}

	if (pqt_progress)
	{	delete pqt_progress;
		pqt_progress = NULL;
	}
	if (pqt_win)
	{	delete pqt_win;
		pqt_win = NULL;
	}
	//if (pqt_layout)  - deallocated by above routines(?)
	//{	delete pqt_layout;
		pqt_layout = NULL;
	//}

//bool QWidget::close () [slot]
//Closes this widget. Returns true if the widget was closed; otherwise returns false.
//First it sends the widget a QCloseEvent. The widget is hidden if it accepts the close event. If it ignores the event, nothing happens. The default implementation of QWidget::closeEvent() accepts the close event.
//If the widget has the Qt::WA_DeleteOnClose flag, the widget is also deleted. A close events is delivered to the widget no matter if the widget is visible or not.

	sqt_progress = NULL;
	sqt_win = NULL;
#endif

   if (lLogAnalysisProgressOption >= 0)      // SAC 01/14/22 (MFam)
      ebLogAnalysisProgress = bOrig_LogAnalysisProgress;

   if (ebLogAnalysisMsgs != bSaveLogAnalysisMsgs)     // SAC 06/26/23
      ebLogAnalysisMsgs = bSaveLogAnalysisMsgs;

	// SAC 5/28/15 - callback mechanism - reset static function pointer
	if (pAnalProgCallbackFunc)
	{	spAnalProgCallbackFunc = NULL;
		slAnalysisProgressCallbackRetVal = 0;
	}

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////


//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error - Results string length insufficient to store entire CSV record
//											 2 : Error - Results string empty
int CMX_PopulateCSVResultSummary_NonRes(	char* pszResultsString, int iResultsStringLength, const char* pszProjectPathFileName /*=NULL*/,
														const char* pszSimWeatherPath /*=NULL*/, int iEUseSummaryIdx /*=0*/ )	// SAC 11/04/19
{	int iRetVal = 0;

	QString sModelPathFile		= pszProjectPathFileName;
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

	QString sSimWeatherPath		= pszSimWeatherPath;
	RelativeToCompletePath_IfNeeded( sSimWeatherPath  );

	int iCodeType = CT_T24N, iRulesetCodeYear = 0;
	QString sLoadedRuleSetID, sLoadedRuleSetVer;
	if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))
	{	if (sLoadedRuleSetID.indexOf( "T24N" ) >= 0 || sLoadedRuleSetID.indexOf( "CA " ) == 0)
			iCodeType = CT_T24N;
		else if (sLoadedRuleSetID.indexOf( "S901G" ) >= 0 ||
					(sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0))
			iCodeType = CT_S901G;
		else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
			iCodeType = CT_ECBC;
		else if (sLoadedRuleSetID.indexOf( "360" ) >= 0)		// SAC 1/30/20
			iCodeType = CT_360;
		else
		{	assert( FALSE );	// what ruleset is this ??
		}
		int iCdYrIdx = sLoadedRuleSetID.indexOf( " 20" ) + 1;		// revised logic to process S901G '-2010' code year properly
		if (iCdYrIdx < 1)
			 iCdYrIdx = sLoadedRuleSetID.indexOf( "20" );
		if (iCdYrIdx >= 0)
		{	iRulesetCodeYear = atoi( sLoadedRuleSetID.mid( iCdYrIdx, 4 ).toLocal8Bit().constData() );
			assert( iRulesetCodeYear >= 2000 );
	}	}

	// ensure CodeType-specific BEMProcIdx used in retrieving UMLH (and other?) results
	int iModelCount = BEMPX_GetModelCount();
	int iBEMProcIdx_Prop = ((iCodeType == CT_T24N && iModelCount >= 4) ? 3 : (iCodeType != CT_T24N && iModelCount >= 7) ? 6 : (iModelCount >= 4) ? 3 : -1);
	int iBEMProcIdx_Std  = ((iCodeType == CT_T24N && iModelCount >= 5) ? 4 : (iCodeType != CT_T24N && iModelCount >= 8) ? 7 : (iModelCount >= 5) ? 4 : -1);

	//bool bExpectValidResults = true;
	double dTimeOverall = 0;
	BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:AnalysisDuration" ), dTimeOverall );

	QString sResTemp1, sResTemp2, sEUseSummName;
	BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:PassFail"   ), sResTemp1, TRUE, 0, -1, iEUseSummaryIdx );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:Enduse8[8]" ), sResTemp2, TRUE, 0, -1, iEUseSummaryIdx );
	BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:Name"   ), sEUseSummName, TRUE, 0, -1, iEUseSummaryIdx );
   double dCompMarg = strtof( sResTemp2.toLocal8Bit().constData(), NULL );    // fix problem where CompMargin values outside +/-1k causing problems due to presence of comma in string - SAC 01/11/23
   sResTemp2 = QString::number( dCompMarg );

		QString sRunTitle, sWthrStn, sAnalType, sPropSimSummary, sStdSimSummary, sAppVer, sCmpMgrVer, sRulesetID, sRuleVer, sAnnWthrFile, sEPlusVer, sTimeStamp, sOSVer, sCSEVersion, sLogMsg, sBEMErr;
		double dRptTotArea, dRptCndArea;   // SAC 2/19/17
		int iCID_Proj      = GetBEMBaseCompID( sBEMErr, "Proj"      );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"       ), sRunTitle );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherStation" ), sWthrStn  );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnalysisType"   ), sAnalType );
		BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:SimSummary" )  , sPropSimSummary, FALSE, 0, -1, iEUseSummaryIdx, BEMO_User, "unknown" );
		BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:SimSummary" )+2, sStdSimSummary , FALSE, 0, -1, iEUseSummaryIdx, BEMO_User, "unknown" );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"    ), sAppVer    );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), sCmpMgrVer );
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Ruleset"            ), sRuleVer   );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile"  ), sAnnWthrFile );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotFlrArea"      ), dRptTotArea );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), dRptCndArea );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunDateLog"      ), sTimeStamp );		// SAC 11/04/19
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:OpenStudioVersion" ), sOSVer );		// SAC 11/04/19
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:EngyPlusVersion" ), sEPlusVer );		// SAC 11/04/19
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CSEVersion"      ), sCSEVersion );	// SAC 11/04/19
		if (sCSEVersion.isEmpty())
			sCSEVersion = "-";
		if (!CMX_GetRulesetID( sRulesetID, sRuleVer ))
		{	assert( FALSE );
			sRuleVer = "???";
		}

		double fEnergyResults[2][9][NUM_T24_NRES_EndUses_19];		// Prop/Std -- Elec/NGas/Othr/TDV/ElecKW/Src -- SpcHtg/SpcClg...ProcLtg/ProcMtrs/PV/Battery/TOTAL		- SAC 10/10/16 - added elec demand  - SAC 2/7/17 - added ProcMtrs  - SAC 7/20/18 - added PV&Batt & switched to use of NUM_T24_NRES_EndUses  - SAC 6/29/19 - 5->7 result sets, adding SrcEnergy & SrcPrmEnergy for 2022  - SAC 9/24/19 - trimmed trailing SrcPrm   - SAC 11/4/19 - added C02 emissions
		double fEnergyCosts[2][4] = { {0,0,0,0}, {0,0,0,0} };	// Prop/Std -- Elec/NGas/Othr/TOTAL
		long lDBID_Res[2][9]		= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:ProposedTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropElecDemand" ), BEMPX_GetDatabaseID( "EnergyUse:PropElecC02" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasC02" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherC02" ), BEMPX_GetDatabaseID( "EnergyUse:ProposedSrc" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StandardTDV" ), BEMPX_GetDatabaseID( "EnergyUse:StdElecDemand"  ), BEMPX_GetDatabaseID( "EnergyUse:StdElecC02"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasC02"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherC02"  ), BEMPX_GetDatabaseID( "EnergyUse:StandardSrc" ) } };
		int iResArrayIdx[2][9]	= { {	                                   0             ,                                    0               ,                                    0              ,                             iEUseSummaryIdx   ,                                    0             ,                             iEUseSummaryIdx   ,                             iEUseSummaryIdx     ,                             iEUseSummaryIdx    ,                             iEUseSummaryIdx    },		// SAC 11/4/19
											 {                                    0             ,                                    0               ,                                    0              ,                             iEUseSummaryIdx   ,                                    0             ,                             iEUseSummaryIdx   ,                             iEUseSummaryIdx     ,                             iEUseSummaryIdx    ,                             iEUseSummaryIdx    } };
		long lDBID_Costs[2][4]	= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropTotalCost" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdTotalCost"  ) } };
		double fTDVbyFuel[2][3] = { {0,0,0}, {0,0,0} };	// TDV results: Prop/Std - Elec/NGas/Othr  - SAC 2/19/17
		long lDBID_TDVbF[2][3]	= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherTDV" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecTDV"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasTDV"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherTDV"  ) } };
		int iTDVbFArrIdx[2][3]	= { {	                             iEUseSummaryIdx  ,                              iEUseSummaryIdx    ,                              iEUseSummaryIdx    },		// SAC 11/4/19
											 {                              iEUseSummaryIdx  ,                              iEUseSummaryIdx    ,                              iEUseSummaryIdx    } };

//           "PropElecSupEnergy", BEMP_Flt,  1,  0,  0,  Pres,  "kWh",              0,  0,                39110, "Proposed run Electric energy SUPPLY for this enduse (negative value)",  ""  ; SAC 9/7/18
//           "PropElecSupTDV",    BEMP_Flt,  1,  0,  0,  Pres,  "kTDV/ft2-yr",      0,  0,                39110, "Proposed run Electric SUPPLY TDV for this enduse (negative value)",  "" 
//           "StdElecSupEnergy",  BEMP_Flt,  1,  0,  0,  Pres,  "kWh",              0,  0,                39110, "Standard run Electric energy SUPPLY for this enduse (negative value)",  "" 
//           "StdElecSupTDV",     BEMP_Flt,  1,  0,  0,  Pres,  "kTDV/ft2-yr",      0,  0,                39110, "Standard run Electric SUPPLY TDV for this enduse (negative value)",  "" 

		int iNumBadResults=0, iNumResAttempts=0,  iNumBadEDResults=0, iNumEDResAttempts=0;
		for (int iRR=0; iRR<2; iRR++)
			for (int iRF=0; iRF<9; iRF++)		// SAC 6/29/19 - 5->7 for 2022 Src+   - SAC 9/24/19 - 7->6   - SAC 11/4/19 - 6->9
			{	int iMaxREU = NUM_T24_NRES_EndUses_19-1;   // SAC 2/19/17 - was: (iRF==3 ? 7 : 12);  - SAC 7/20/18 - 12->NUM_T24_NRES_EndUses-1
				for (int iREU=0; iREU<=iMaxREU; iREU++)
				{	if ( (iRF == 3 &&  iCodeType != CT_T24N ) ||		// SAC 10/7/14 - store TDV results only for T24 runs
						  (iRF >= 5 && (iCodeType != CT_T24N || iRulesetCodeYear < 2019) ) ||		// SAC 11/4/19 - store C02 results only for T24 2019+ runs
						  (iRF >= 8 && (iCodeType != CT_T24N || iRulesetCodeYear < 2022) ) ) 		// SAC 6/29/19 - store SrcEnergy & SrcPrmEnergy results only for T24 2022+ runs
						fEnergyResults[iRR][iRF][iREU] = 0;
					else
					{	if (iRF==4)	// elec demand
							iNumEDResAttempts++;
						else
							iNumResAttempts++;
						if (!BEMPX_GetFloat(  lDBID_Res[iRR][iRF]+iResArrayIdx[iRR][iRF], fEnergyResults[iRR][iRF][iREU], 0, -1,  iREU ))
						{	if (iRF==4)	// elec demand
								iNumBadEDResults++;
							else
								iNumBadResults++;
							fEnergyResults[iRR][iRF][iREU] = 0;
					}	}
				}
			// storage of energy COST results
				if (iRF<4 && (iCodeType == CT_S901G || iCodeType == CT_ECBC))
					BEMPX_GetFloat(  lDBID_Costs[iRR][iRF], fEnergyCosts[iRR][iRF], 0, -1, iMaxREU /*index of Total enduse*/ );	// SAC 7/20/18 - Tot EU idx 12->iMaxREU following addition of PV & Battery
			// storage of TDV by Fuel results  - SAC 2/19/17
				if (iRF<3 && iCodeType == CT_T24N)
					BEMPX_GetFloat(  lDBID_TDVbF[iRR][iRF]+iTDVbFArrIdx[iRR][iRF], fTDVbyFuel[iRR][iRF], 0, -1, iMaxREU /*index of Total enduse*/ );	// SAC 7/20/18 - Tot EU idx 12->iMaxREU following addition of PV & Battery
			}
			if (/*bExpectValidResults &&*/ iNumBadResults >= iNumResAttempts)
			{	assert( FALSE );	// was expecting valid results, but NONE were retrievable
			}
		bool bHaveElecDemandResults = (iNumBadEDResults < iNumEDResAttempts);	// SAC 10/11/16

	  // UMLH reporting
		double fPropMaxClgUMLHs, fPropMaxHtgUMLHs, fStdMaxClgUMLHs, fStdMaxHtgUMLHs;
		QString sPropMaxClgUMLHZnName, sPropMaxHtgUMLHZnName, sStdMaxClgUMLHZnName, sStdMaxHtgUMLHZnName, sPropClgUMLHData, sPropHtgUMLHData, sStdClgUMLHData, sStdHtgUMLHData;
		long lPropClgNumZonesExceed, lPropHtgNumZonesExceed, lStdClgNumZonesExceed, lStdHtgNumZonesExceed;
		if (iBEMProcIdx_Prop < 0)  // SAC 10/28/13
		{		sPropClgUMLHData = ",,";
				sPropHtgUMLHData = ",,";
		}
		else
		{	if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedClgUnmetLdHrs", iCID_Proj ), lPropClgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Prop /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrs"       , iCID_Proj ), fPropMaxClgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Prop /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName"   , iCID_Proj ), sPropMaxClgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx_Prop /*iBEMProcIdx*/ );
				if (sPropMaxClgUMLHZnName.isEmpty())
					sPropClgUMLHData = QString::asprintf( "%g,,%d", fPropMaxClgUMLHs, lPropClgNumZonesExceed );
				else
					sPropClgUMLHData = QString::asprintf( "%g,\"%s\",%d", fPropMaxClgUMLHs, sPropMaxClgUMLHZnName.toLocal8Bit().constData(), lPropClgNumZonesExceed );
			}
			else
				sPropClgUMLHData = ",,";

			if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedHtgUnmetLdHrs", iCID_Proj ), lPropHtgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Prop /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrs"       , iCID_Proj ), fPropMaxHtgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Prop /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName"   , iCID_Proj ), sPropMaxHtgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx_Prop /*iBEMProcIdx*/ );
				if (sPropMaxHtgUMLHZnName.isEmpty())
					sPropHtgUMLHData = QString::asprintf( "%g,,%d", fPropMaxHtgUMLHs, lPropHtgNumZonesExceed );
				else
					sPropHtgUMLHData = QString::asprintf( "%g,\"%s\",%d", fPropMaxHtgUMLHs, sPropMaxHtgUMLHZnName.toLocal8Bit().constData(), lPropHtgNumZonesExceed );
			}
			else
				sPropHtgUMLHData = ",,";
		}
		if (iBEMProcIdx_Std < 0)  // SAC 10/28/13
		{		sStdClgUMLHData = ",,";
				sStdHtgUMLHData = ",,";
		}
		else
		{	if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedClgUnmetLdHrs", iCID_Proj ), lStdClgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Std /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrs"       , iCID_Proj ), fStdMaxClgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Std /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName"   , iCID_Proj ), sStdMaxClgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx_Std /*iBEMProcIdx*/ );
				if (sStdMaxClgUMLHZnName.isEmpty())
					sStdClgUMLHData = QString::asprintf( "%g,,%d", fStdMaxClgUMLHs, lStdClgNumZonesExceed );
				else
					sStdClgUMLHData = QString::asprintf( "%g,\"%s\",%d", fStdMaxClgUMLHs, sStdMaxClgUMLHZnName.toLocal8Bit().constData(), lStdClgNumZonesExceed );
			}
			else
				sStdClgUMLHData = ",,";

			if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedHtgUnmetLdHrs", iCID_Proj ), lStdHtgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Std /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrs"       , iCID_Proj ), fStdMaxHtgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     iBEMProcIdx_Std /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName"   , iCID_Proj ), sStdMaxHtgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx_Std /*iBEMProcIdx*/ );
				if (sStdMaxHtgUMLHZnName.isEmpty())
					sStdHtgUMLHData = QString::asprintf( "%g,,%d", fStdMaxHtgUMLHs, lStdHtgNumZonesExceed );
				else
					sStdHtgUMLHData = QString::asprintf( "%g,\"%s\",%d", fStdMaxHtgUMLHs, sStdMaxHtgUMLHZnName.toLocal8Bit().constData(), lStdHtgNumZonesExceed );
			}
			else
				sStdHtgUMLHData = ",,";
		}

      long lIsCalPRM = 0, lDBID_Proj_IsCalPRM = BEMPX_GetDatabaseID( "Proj:IsCalPRM" );      // SAC 10/29/23   // extended from 4->14 values - SAC 10/30/23
      if (lDBID_Proj_IsCalPRM > 0)
         BEMPX_GetInteger( lDBID_Proj_IsCalPRM, lIsCalPRM );
		QString sPRMTargetPerf = ",,,,,,,,,,,,,,";
      if (lIsCalPRM)
      {  double daPRMTargetPerf[14];
         if ( BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[10]" ), daPRMTargetPerf[ 0], 0, -1,  15 ) &&   // EffComp
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[10]" ), daPRMTargetPerf[ 1], 0, -1,   7 ) &&   // TotComp
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[ 1]" ), daPRMTargetPerf[ 2], 0, -1,   8 ) &&   // Recpt
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[ 1]" ), daPRMTargetPerf[ 3], 0, -1,   9 ) &&   // Proc
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[ 1]" ), daPRMTargetPerf[ 4], 0, -1,  10 ) &&   // OthrLtg
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[ 1]" ), daPRMTargetPerf[ 5], 0, -1,  11 ) &&   // ProcMtrs
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardTDV[10]" ), daPRMTargetPerf[ 6], 0, -1,  14 ) &&   // TOTAL
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[10]" ), daPRMTargetPerf[ 7], 0, -1,  15 ) &&   // EffComp
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[10]" ), daPRMTargetPerf[ 8], 0, -1,   7 ) &&   // TotComp
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[ 1]" ), daPRMTargetPerf[ 9], 0, -1,   8 ) &&   // Recpt
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[ 1]" ), daPRMTargetPerf[10], 0, -1,   9 ) &&   // Proc
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[ 1]" ), daPRMTargetPerf[11], 0, -1,  10 ) &&   // OthrLtg
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[ 1]" ), daPRMTargetPerf[12], 0, -1,  11 ) &&   // ProcMtrs
              BEMPX_GetFloat( BEMPX_GetDatabaseID( "EnergyUse:StandardSrc[10]" ), daPRMTargetPerf[13], 0, -1,  14 ) )    // TOTAL
            sPRMTargetPerf = QString::asprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,", daPRMTargetPerf[0], daPRMTargetPerf[1], daPRMTargetPerf[ 2], daPRMTargetPerf[ 3], daPRMTargetPerf[ 4], daPRMTargetPerf[ 5],
                                                      daPRMTargetPerf[6], daPRMTargetPerf[7], daPRMTargetPerf[8], daPRMTargetPerf[9], daPRMTargetPerf[10], daPRMTargetPerf[11], daPRMTargetPerf[12], daPRMTargetPerf[13] );
      }

		QString sElecDemandResults;
		if (bHaveElecDemandResults && iCodeType == CT_T24N)	// SAC 10/11/16
		{	sElecDemandResults = QString::asprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",
				// Proposed model electric demand
						fEnergyResults[0][4][ 0], fEnergyResults[0][4][ 1], fEnergyResults[0][4][ 2], fEnergyResults[0][4][ 3], fEnergyResults[0][4][ 4], fEnergyResults[0][4][ 5], fEnergyResults[0][4][ 6], fEnergyResults[0][4][ 7],
						fEnergyResults[0][4][ 8], fEnergyResults[0][4][ 9], fEnergyResults[0][4][10], fEnergyResults[0][4][11], fEnergyResults[0][4][12], fEnergyResults[0][4][13], fEnergyResults[0][4][14],
				// Standard model electric demand
						fEnergyResults[1][4][ 0], fEnergyResults[1][4][ 1], fEnergyResults[1][4][ 2], fEnergyResults[1][4][ 3], fEnergyResults[1][4][ 4], fEnergyResults[1][4][ 5], fEnergyResults[1][4][ 6], fEnergyResults[1][4][ 7],
						fEnergyResults[1][4][ 8], fEnergyResults[1][4][ 9], fEnergyResults[1][4][10], fEnergyResults[1][4][11], fEnergyResults[1][4][12], fEnergyResults[1][4][13], fEnergyResults[1][4][14]  );
		}
		else
			sElecDemandResults = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

		QString sC02EmissionResults;
		if (iCodeType == CT_T24N && iRulesetCodeYear >= 2019)	// SAC 11/4/19
		{	sC02EmissionResults = QString::asprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",   // 56 floats 
				// Proposed model electric C02 emissions
						fEnergyResults[0][5][ 0], fEnergyResults[0][5][ 1], fEnergyResults[0][5][ 2], fEnergyResults[0][5][ 3], fEnergyResults[0][5][ 4], fEnergyResults[0][5][ 5], fEnergyResults[0][5][ 6], fEnergyResults[0][5][ 7],
						fEnergyResults[0][5][ 8], fEnergyResults[0][5][ 9], fEnergyResults[0][5][10], fEnergyResults[0][5][11], fEnergyResults[0][5][12], fEnergyResults[0][5][13], fEnergyResults[0][5][14],
				// Proposed model fuel C02 emissions
						fEnergyResults[0][6][ 0] +fEnergyResults[0][7][ 0], fEnergyResults[0][6][ 1] +fEnergyResults[0][7][ 1], fEnergyResults[0][6][ 2] +fEnergyResults[0][7][ 2], fEnergyResults[0][6][ 3] +fEnergyResults[0][7][ 3],
						fEnergyResults[0][6][ 4] +fEnergyResults[0][7][ 4], fEnergyResults[0][6][ 5] +fEnergyResults[0][7][ 5], fEnergyResults[0][6][ 6] +fEnergyResults[0][7][ 6], fEnergyResults[0][6][ 7] +fEnergyResults[0][7][ 7],
						fEnergyResults[0][6][ 8] +fEnergyResults[0][7][ 8], fEnergyResults[0][6][ 9] +fEnergyResults[0][7][ 9], fEnergyResults[0][6][10] +fEnergyResults[0][7][10], fEnergyResults[0][6][11] +fEnergyResults[0][7][11], fEnergyResults[0][6][14] +fEnergyResults[0][7][14],
				// Standard model electric C02 emissions
						fEnergyResults[1][5][ 0], fEnergyResults[1][5][ 1], fEnergyResults[1][5][ 2], fEnergyResults[1][5][ 3], fEnergyResults[1][5][ 4], fEnergyResults[1][5][ 5], fEnergyResults[1][5][ 6], fEnergyResults[1][5][ 7],
						fEnergyResults[1][5][ 8], fEnergyResults[1][5][ 9], fEnergyResults[1][5][10], fEnergyResults[1][5][11], fEnergyResults[1][5][12], fEnergyResults[1][5][13], fEnergyResults[1][5][14],
				// Proposed model fuel C02 emissions
						fEnergyResults[1][6][ 0] +fEnergyResults[1][7][ 0], fEnergyResults[1][6][ 1] +fEnergyResults[1][7][ 1], fEnergyResults[1][6][ 2] +fEnergyResults[1][7][ 2], fEnergyResults[1][6][ 3] +fEnergyResults[1][7][ 3],
						fEnergyResults[1][6][ 4] +fEnergyResults[1][7][ 4], fEnergyResults[1][6][ 5] +fEnergyResults[1][7][ 5], fEnergyResults[1][6][ 6] +fEnergyResults[1][7][ 6], fEnergyResults[1][6][ 7] +fEnergyResults[1][7][ 7],
						fEnergyResults[1][6][ 8] +fEnergyResults[1][7][ 8], fEnergyResults[1][6][ 9] +fEnergyResults[1][7][ 9], fEnergyResults[1][6][10] +fEnergyResults[1][7][10], fEnergyResults[1][6][11] +fEnergyResults[1][7][11], fEnergyResults[1][6][14] +fEnergyResults[1][7][14]  );
		}
		else
			sC02EmissionResults = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";  // 56 cells

		QString sSrcEnergyResults;
		if (iCodeType == CT_T24N && iRulesetCodeYear >= 2022)	// SAC 6/29/19
		{	//sSrcEnergyResults = QString::asprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",
			sSrcEnergyResults = QString::asprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",   // SAC 9/24/19
				// Proposed model Source Energy
						fEnergyResults[0][8][ 0], fEnergyResults[0][8][ 1], fEnergyResults[0][8][ 2], fEnergyResults[0][8][ 3], fEnergyResults[0][8][ 4], fEnergyResults[0][8][ 5], fEnergyResults[0][8][ 6], fEnergyResults[0][8][ 7],
						fEnergyResults[0][8][ 8], fEnergyResults[0][8][ 9], fEnergyResults[0][8][10], fEnergyResults[0][8][11], fEnergyResults[0][8][12], fEnergyResults[0][8][13], fEnergyResults[0][8][14],
				// Standard model Source Energy
						fEnergyResults[1][8][ 0], fEnergyResults[1][8][ 1], fEnergyResults[1][8][ 2], fEnergyResults[1][8][ 3], fEnergyResults[1][8][ 4], fEnergyResults[1][8][ 5], fEnergyResults[1][8][ 6], fEnergyResults[1][8][ 7],
						fEnergyResults[1][8][ 8], fEnergyResults[1][8][ 9], fEnergyResults[1][8][10], fEnergyResults[1][8][11], fEnergyResults[1][8][12], fEnergyResults[1][8][13], fEnergyResults[1][8][14] );
			//	// Proposed model SourcePrime Energy
			//			fEnergyResults[0][6][ 0], fEnergyResults[0][6][ 1], fEnergyResults[0][6][ 2], fEnergyResults[0][6][ 3], fEnergyResults[0][6][ 4], fEnergyResults[0][6][ 5], fEnergyResults[0][6][ 6], fEnergyResults[0][6][ 7],
			//			fEnergyResults[0][6][ 8], fEnergyResults[0][6][ 9], fEnergyResults[0][6][10], fEnergyResults[0][6][11], fEnergyResults[0][6][12], fEnergyResults[0][6][13], fEnergyResults[0][6][14],
			//	// Standard model SourcePrime Energy
			//			fEnergyResults[1][6][ 0], fEnergyResults[1][6][ 1], fEnergyResults[1][6][ 2], fEnergyResults[1][6][ 3], fEnergyResults[1][6][ 4], fEnergyResults[1][6][ 5], fEnergyResults[1][6][ 6], fEnergyResults[1][6][ 7],
			//			fEnergyResults[1][6][ 8], fEnergyResults[1][6][ 9], fEnergyResults[1][6][10], fEnergyResults[1][6][11], fEnergyResults[1][6][12], fEnergyResults[1][6][13], fEnergyResults[1][6][14] );
		}
		else
			//sSrcEnergyResults = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";
			sSrcEnergyResults = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

		double dFlexTDV = 0.0;		// SAC 9/16/20 (tic #3218)
		QString sFlexReqdPV = ",", sPropSSF = ",", sStdSSF = ",";			// SAC 9/17/20 (tic #3215)
		if (iCodeType == CT_T24N && iRulesetCodeYear >= 2019)
		{	if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:FlexibilityTDV" ), dFlexTDV, 0, -1, iEUseSummaryIdx /*iOccur*/ ) && dFlexTDV != 0)
			{	fEnergyResults[0][3][ 7] += dFlexTDV;			// adjust CompTotal
				if (fEnergyResults[0][3][12] < 0)
					fEnergyResults[0][3][12] -= dFlexTDV;		// adjust PV ... or
				else
					fEnergyResults[0][3][14] += dFlexTDV;		// total
			}
			double dSSFtemp;
			if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:ReqdPV_SolThrml" ), dSSFtemp, 0, -1, iEUseSummaryIdx /*iOccur*/ ) && dSSFtemp > 0)		// SAC 9/17/20 (tic #3215)
				sFlexReqdPV = QString::asprintf( "%g,", dSSFtemp );
			if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:PropDHW_SSF"     ), dSSFtemp, 0, -1, iEUseSummaryIdx /*iOccur*/ ) && dSSFtemp > 0)
				sPropSSF = QString::asprintf(    "%g,", dSSFtemp );
			if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:StdDHW_SSF"      ), dSSFtemp, 0, -1, iEUseSummaryIdx /*iOccur*/ ) && dSSFtemp > 0)
				sStdSSF = QString::asprintf(     "%g,", dSSFtemp );
		}

		QString sRptGenInfo = ",,";      // added Report Gen NRCC PRF transaction ID & processing date/time @ col GH - SAC 12/05/21
		if (iCodeType == CT_T24N && iRulesetCodeYear >= 2019)
      {  QString qsPayldTransID, qsPayldProcDateTime;
         BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:NRCCPRFPayldTransID"  ), qsPayldTransID     , FALSE, 0, -1, iEUseSummaryIdx );  //, BEMO_User, NULL, 0, iBEMProcIdx );
         BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:NRCCPRFPayldProcDate" ), qsPayldProcDateTime, FALSE, 0, -1, iEUseSummaryIdx );  //, BEMO_User, NULL, 0, iBEMProcIdx );
         if (!qsPayldTransID.isEmpty() || !qsPayldProcDateTime.isEmpty())
				sRptGenInfo = QString::asprintf( "\"%s\",%s,", qsPayldTransID.toLocal8Bit().constData(), qsPayldProcDateTime.toLocal8Bit().constData() );
      }

// SAC 5/5/15 - ResultSummary Logging
	sLogMsg = QString::asprintf( "      ResultsSummary components1:  %s / %s / %s / %s / %s / %d:%.2d / %s / %s", 
						sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(),
						sAnalType.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)), sResTemp1.toLocal8Bit().constData() /*PassFail*/, sResTemp2.toLocal8Bit().constData() /*CompMargin*/ );
	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	sLogMsg = QString::asprintf( "      ResultsSummary components2:  %s / %s / %s / %s / %s / %s / %s / %s", 
						sAppVer.toLocal8Bit().constData(), sCmpMgrVer.toLocal8Bit().constData(), sRuleVer.toLocal8Bit().constData(), sOSVer.toLocal8Bit().constData(), 
						sEPlusVer.toLocal8Bit().constData(), sCSEVersion.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(), sModelPathOnly.toLocal8Bit().constData() );
	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

#pragma warning(disable:4996)
		if (iCodeType == CT_T24N)		// SAC 10/7/14 - export of TDV results needed only for T24 analysis
			_snprintf( pszResultsString, iResultsStringLength, "%s,\"%s\",\"%s\",\"%s\",\"%s\",%g,%g,\"%s\",%d:%.2d,%s,%s,"					// begin thru CompMargin
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// prop      - SAC 7/20/18 - addition of PV & Batt Elec enduses
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,%s%s%s"    // prop   - SAC 9/16/20 - added dFlexTDV (tic #3218)  // SAC 9/17/20 (tic #3215)
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// std
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,"    // std
							"%s"                                                                                                     // prop & std kW
							"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%s%s%s%s\n",
						sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), sEUseSummName.toLocal8Bit().constData(), dRptCndArea, dRptTotArea,  // SAC 2/18/17  // SAC 11/4/19
						sAnalType.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)), sResTemp1.toLocal8Bit().constData() /*PassFail*/, sResTemp2.toLocal8Bit().constData() /*CompMargin*/,
				// Proposed model
						"--", "--", sPropSimSummary.toLocal8Bit().constData(),
						fEnergyResults[0][0][ 0], fEnergyResults[0][0][ 1], fEnergyResults[0][0][ 2], fEnergyResults[0][0][ 3], fEnergyResults[0][0][ 4], fEnergyResults[0][0][ 5],
						fEnergyResults[0][0][ 6], fEnergyResults[0][0][ 7], fEnergyResults[0][0][ 8], fEnergyResults[0][0][ 9], fEnergyResults[0][0][10], fEnergyResults[0][0][11], fEnergyResults[0][0][12], fEnergyResults[0][0][13], fEnergyResults[0][0][14],
						fEnergyResults[0][1][ 0], fEnergyResults[0][1][ 1], fEnergyResults[0][1][ 2], fEnergyResults[0][1][ 3], fEnergyResults[0][1][ 4], fEnergyResults[0][1][ 5],
						fEnergyResults[0][1][ 6], fEnergyResults[0][1][ 7], fEnergyResults[0][1][ 8], fEnergyResults[0][1][ 9], fEnergyResults[0][1][10], fEnergyResults[0][1][11], fEnergyResults[0][1][14],
						fEnergyResults[0][2][ 0], fEnergyResults[0][2][ 1], fEnergyResults[0][2][ 2], fEnergyResults[0][2][ 3], fEnergyResults[0][2][ 4], fEnergyResults[0][2][ 5],
						fEnergyResults[0][2][ 6], fEnergyResults[0][2][ 7], fEnergyResults[0][2][ 8], fEnergyResults[0][2][ 9], fEnergyResults[0][2][10], fEnergyResults[0][2][11], fEnergyResults[0][2][14],
						fEnergyResults[0][3][ 0], fEnergyResults[0][3][ 1], fEnergyResults[0][3][ 2], fEnergyResults[0][3][ 3], fEnergyResults[0][3][ 4], fEnergyResults[0][3][ 5],
						fEnergyResults[0][3][ 6], dFlexTDV,                 fEnergyResults[0][3][ 7], fEnergyResults[0][3][ 8], fEnergyResults[0][3][ 9], fEnergyResults[0][3][10], fEnergyResults[0][3][11], fEnergyResults[0][3][12], fEnergyResults[0][3][13], fEnergyResults[0][3][14],
						fTDVbyFuel[0][0],	fTDVbyFuel[0][1],	fTDVbyFuel[0][2],	// TDV results: Prop - Elec/NGas/Othr  - SAC 2/19/17
						sPropClgUMLHData.toLocal8Bit().constData(), sPropHtgUMLHData.toLocal8Bit().constData(),			// UMLHs
						sFlexReqdPV.toLocal8Bit().constData(), sPropSSF.toLocal8Bit().constData(), sStdSSF.toLocal8Bit().constData(),			// SAC 9/17/20 (tic #3215)
				// Standard model
						"--", "--", sStdSimSummary.toLocal8Bit().constData(),
						fEnergyResults[1][0][ 0], fEnergyResults[1][0][ 1], fEnergyResults[1][0][ 2], fEnergyResults[1][0][ 3], fEnergyResults[1][0][ 4], fEnergyResults[1][0][ 5],
						fEnergyResults[1][0][ 6], fEnergyResults[1][0][ 7], fEnergyResults[1][0][ 8], fEnergyResults[1][0][ 9], fEnergyResults[1][0][10], fEnergyResults[1][0][11], fEnergyResults[1][0][12], fEnergyResults[1][0][13], fEnergyResults[1][0][14],
						fEnergyResults[1][1][ 0], fEnergyResults[1][1][ 1], fEnergyResults[1][1][ 2], fEnergyResults[1][1][ 3], fEnergyResults[1][1][ 4], fEnergyResults[1][1][ 5],
						fEnergyResults[1][1][ 6], fEnergyResults[1][1][ 7], fEnergyResults[1][1][ 8], fEnergyResults[1][1][ 9], fEnergyResults[1][1][10], fEnergyResults[1][1][11], fEnergyResults[1][1][14],
						fEnergyResults[1][2][ 0], fEnergyResults[1][2][ 1], fEnergyResults[1][2][ 2], fEnergyResults[1][2][ 3], fEnergyResults[1][2][ 4], fEnergyResults[1][2][ 5],
						fEnergyResults[1][2][ 6], fEnergyResults[1][2][ 7], fEnergyResults[1][2][ 8], fEnergyResults[1][2][ 9], fEnergyResults[1][2][10], fEnergyResults[1][2][11], fEnergyResults[1][2][14],
						fEnergyResults[1][3][ 0], fEnergyResults[1][3][ 1], fEnergyResults[1][3][ 2], fEnergyResults[1][3][ 3], fEnergyResults[1][3][ 4], fEnergyResults[1][3][ 5], 
						fEnergyResults[1][3][ 6], fEnergyResults[1][3][ 7], fEnergyResults[1][3][ 8], fEnergyResults[1][3][ 9], fEnergyResults[1][3][10], fEnergyResults[1][3][11], fEnergyResults[1][3][12], fEnergyResults[1][3][13], fEnergyResults[1][3][14],
						fTDVbyFuel[1][0],	fTDVbyFuel[1][1],	fTDVbyFuel[1][2],	// TDV results: Std - Elec/NGas/Othr  - SAC 2/19/17
						sStdClgUMLHData.toLocal8Bit().constData(), sStdHtgUMLHData.toLocal8Bit().constData(),				// UMLHs
				// Proposed & Standard model electric demand
						sElecDemandResults.toLocal8Bit().constData(),
				// final version labels & paths
						//sAppVer, sCmpMgrVer, sRuleVer, sOSVer, sEPlusVer, "-", sAnnWthrFile, pszModelPathFile );
						sAppVer.toLocal8Bit().constData(), sCmpMgrVer.toLocal8Bit().constData(), sRuleVer.toLocal8Bit().constData(), sOSVer.toLocal8Bit().constData(), 
						sEPlusVer.toLocal8Bit().constData(), sCSEVersion.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(), sModelPathOnly.toLocal8Bit().constData(),
                  sRptGenInfo.toLocal8Bit().constData(), sC02EmissionResults.toLocal8Bit().constData(), sSrcEnergyResults.toLocal8Bit().constData(), sPRMTargetPerf.toLocal8Bit().constData() );      // SAC 12/05/21  // SAC 10/29/23

		else if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14 - export of Energy Cost results needed only for 90.1 analysis
			_snprintf( pszResultsString, iResultsStringLength, "%s,\"%s\",\"%s\",\"%s\",\"%s\",%d:%.2d,%s,%s,"
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// prop      - SAC 7/20/18 - addition of PV & Batt Elec enduses
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,"                                           // prop
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// std
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,"                                           // std
							"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",
						sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), 
						sAnalType.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)), sResTemp1.toLocal8Bit().constData() /*PassFail*/, sResTemp2.toLocal8Bit().constData() /*CompMargin*/,
				// Proposed model
						"--", "--", sPropSimSummary.toLocal8Bit().constData(),  fEnergyCosts[0][0], fEnergyCosts[0][1], fEnergyCosts[0][2], fEnergyCosts[0][3],
						fEnergyResults[0][0][ 0], fEnergyResults[0][0][ 1], fEnergyResults[0][0][ 2], fEnergyResults[0][0][ 3], fEnergyResults[0][0][ 4], fEnergyResults[0][0][ 5],
						fEnergyResults[0][0][ 6],                           fEnergyResults[0][0][ 8], fEnergyResults[0][0][ 9], fEnergyResults[0][0][10], fEnergyResults[0][0][11], fEnergyResults[0][0][12], fEnergyResults[0][0][13], fEnergyResults[0][0][14],
						fEnergyResults[0][1][ 0], fEnergyResults[0][1][ 1], fEnergyResults[0][1][ 2], fEnergyResults[0][1][ 3], fEnergyResults[0][1][ 4], fEnergyResults[0][1][ 5],                          
						fEnergyResults[0][1][ 6],                           fEnergyResults[0][1][ 8], fEnergyResults[0][1][ 9], fEnergyResults[0][1][10], fEnergyResults[0][1][11], fEnergyResults[0][1][14],
						fEnergyResults[0][2][ 0], fEnergyResults[0][2][ 1], fEnergyResults[0][2][ 2], fEnergyResults[0][2][ 3], fEnergyResults[0][2][ 4], fEnergyResults[0][2][ 5],                          
						fEnergyResults[0][2][ 6],                           fEnergyResults[0][2][ 8], fEnergyResults[0][2][ 9], fEnergyResults[0][2][10], fEnergyResults[0][2][11], fEnergyResults[0][2][14],
						sPropClgUMLHData.toLocal8Bit().constData(), sPropHtgUMLHData.toLocal8Bit().constData(),			// UMLHs
				// Standard model
						"--", "--", sStdSimSummary.toLocal8Bit().constData(),  fEnergyCosts[1][0], fEnergyCosts[1][1], fEnergyCosts[1][2], fEnergyCosts[1][3],
						fEnergyResults[1][0][ 0], fEnergyResults[1][0][ 1], fEnergyResults[1][0][ 2], fEnergyResults[1][0][ 3], fEnergyResults[1][0][ 4], fEnergyResults[1][0][ 5],
						fEnergyResults[1][0][ 6],                           fEnergyResults[1][0][ 8], fEnergyResults[1][0][ 9], fEnergyResults[1][0][10], fEnergyResults[1][0][11], fEnergyResults[1][0][12], fEnergyResults[1][0][13], fEnergyResults[1][0][14],
						fEnergyResults[1][1][ 0], fEnergyResults[1][1][ 1], fEnergyResults[1][1][ 2], fEnergyResults[1][1][ 3], fEnergyResults[1][1][ 4], fEnergyResults[1][1][ 5],                          
						fEnergyResults[1][1][ 6],                           fEnergyResults[1][1][ 8], fEnergyResults[1][1][ 9], fEnergyResults[1][1][10], fEnergyResults[1][1][11], fEnergyResults[1][1][14],
						fEnergyResults[1][2][ 0], fEnergyResults[1][2][ 1], fEnergyResults[1][2][ 2], fEnergyResults[1][2][ 3], fEnergyResults[1][2][ 4], fEnergyResults[1][2][ 5],                          
						fEnergyResults[1][2][ 6],                           fEnergyResults[1][2][ 8], fEnergyResults[1][2][ 9], fEnergyResults[1][2][10], fEnergyResults[1][2][11], fEnergyResults[1][2][14],
						sStdClgUMLHData.toLocal8Bit().constData(), sStdHtgUMLHData.toLocal8Bit().constData(),				// UMLHs
				// final version labels & paths
						//sAppVer, sCmpMgrVer, sRuleVer, sOSVer, sEPlusVer, "-", sAnnWthrFile, pszModelPathFile );
						sAppVer.toLocal8Bit().constData(), sCmpMgrVer.toLocal8Bit().constData(), sRuleVer.toLocal8Bit().constData(), sOSVer.toLocal8Bit().constData(), 
						sEPlusVer.toLocal8Bit().constData(), sCSEVersion.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(), sModelPathOnly.toLocal8Bit().constData() );
		else
		{	assert( FALSE );
		}
#pragma warning(default:4996)

	if (strlen( pszResultsString ) >= (iResultsStringLength-1))
		iRetVal = 1;				//	 1 : Error - Results string length insufficient to store entire CSV record
	else if (strlen( pszResultsString ) < 1)
		iRetVal = 2;				//	 2 : Error - Results string empty

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

//static const char* /* 560*/ pszNonResResultsHdr1 = ",,,,Analysis:,,,,Proposed ...
//static const char* /* 968*/ pszNonResResultsHdr2 = ",,,,,,Pass /,Compliance,...
//static const char* /*2706*/ pszNonResResultsHdr3 = "Start Date & Time,Filename ...

// SAC 10/10/16 - updated T24N CSV summary results header strings to include prop & std model electric demand
// SAC 2/7/17 - added Proc Mtrs enduse (tic #2033)
// SAC 2/18/17 - added total & cond floor area + TDV results for unregulated enduses and TDV totals by fuel (for 2019.0.1 release)
// SAC 7/20/18 - added PV & Battery enduses (for A2030 & 2019.0.3 releases)
// SAC 6/28/19 - added 2022 Source & SrcPrime energy use columns out to the right
// SAC 9/24/19 - removed 2022 SrcPrime energy use columns
// SAC 11/4/19 - added Results Set (5th column) and C02 emissions by model (Prop/Std) and Fuel (Elec/Fuel)
// SAC 3/20/20 - fixed col CK T24N header: Lighting -> Indoor Lighting (tic #3188)
// SAC 9/16/20 - added Flexibility Proposed TDV (col BK) (tic #3218)
// SAC 9/17/20 - added Flexibility Req'd PV and Prop & Std DHW SSF (cols CC-CE) (tic #3215)
// added Report Gen NRCC PRF transaction ID & processing date/time - SAC 12/05/21
static char szT24NCSV1[]	 =	",,,,,,,Analysis:,,,,Proposed Model:,,,Proposed Model,,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,"
										",,,,Proposed Model,,,Proposed Model,,,,,,Flexibility,Calculated SSFs,,Standard Model:,,,Standard Model,,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,Sta"
										"ndard Model,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,,,Standard Model,,,Standard Model,,,,,,Proposed Model,,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,,"
										",Calling,Compliance,,,,Secondary,,,Report Generation,,Proposed Model,,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,,,Standard"
										" Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,,\n";   // 665 chars
static char szT24NCSV2[]	 =	",,,,,Conditioned Floor,Total Floor,,,Pass /,Compliance,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Energy Consumption (th"
										"erms),,,,,,,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,Time Dependent Valuation (kTDV/ft2),,,,,,,,,,,,,,,,TDV by Fuel (kTDV/ft2),,,Cooling"
										" Unmet Load Hours,,,Heating Unmet Load Hours,,,Req'd PV,Proposed,Standard,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Ene"
										"rgy Consumption (therms),,,,,,,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,Time Dependent Valuation (kTDV/ft2),,,,,,,,,,,,,,,TDV by Fuel (k"
										"TDV/ft2),,,Cooling Unmet Load Hours,,,Heating Unmet Load Hours,,,Generation Coincident Peak Demand (kW),,,,,,,,,,,,,,,Generation Coincident Peak De"
										"mand (kW),,,,,,,,,,,,,,,Application,Manager,Ruleset,OpenStudio,EnergyPlus,Simulation,,,NRCC/LMCC PRF Processing,,Site Electric CO2 Emissions (tonne),,,,"
										",,,,,,,,,,,Site Fuel CO2 Emissions (tonne),,,,,,,,,,,,,Site Electric CO2 Emissions (tonne),,,,,,,,,,,,,,,Site Fuel CO2 Emissions (tonne),,,,,,,,,,,"
										",,Source Energy Use (kBtu/ft2),,,,,,,,,,,,,,,Source Energy Use (kBtu/ft2),,,,,,,,,,,,,,\n";   // 1117 chars
static char szT24NCSV3[]	 =	"Start Date & Time,Filename (saved to),Run Title,Weather Station,Results Set,Area (SqFt),Area (SqFt),Analysis Type,Elapsed Time,Fail,Margin,Time,Rul"
										"e Eval Status,Simulation Status,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle"
										",Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp To"
										"tal,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp"
										" Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,F"
										"lexibility,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Electric,Natural Gas,Propane,Zone Max,Zone Name,Num Zones Exceed Max,"
										"Zone Max,Zone Name,Num Zones Exceed Max,(kW),(frac),(frac),Time,Rule Eval Status,Simulation Status,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pu"
										"mps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fan"
										"s,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor "
										"Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indo"
										"or Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Electric,Natur"
										"al Gas,Propane,Zone Max,Zone Name,Num Zones Exceed Max,Zone Max,Zone Name,Num Zones Exceed Max,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps "
										"& Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht"
										" Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Version,Version,Version,"
										"Version,Version,Version,Weather File Path,Project Path,Transaction ID,Date/Time,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic"
										" Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps &"
										" Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pump"
										"s & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,"
										"Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fa"
										"ns,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Coo"
										"ling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,"
                              "Efficiency Compliance,Total Compliance,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Efficiency Compliance,Total Compliance,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL\n";   // 3251 chars

static char szT24NCSV1_Dyn[] =	",,,,,,,Analysis:,,,,Proposed Model:,,,Proposed Model,,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,"
										",,,,Proposed Model,,,Proposed Model,,,,,,Flexibility,Calculated SSFs,,%1 Model:,,,%2 Model,,,,,,,,,,,,,,,%3 Model,,,,,,,,,,,,,%4"
										" Model,,,,,,,,,,,,,%5 Model,,,,,,,,,,,,,,,%6 Model,,,%7 Model,,,,,,Proposed Model,,,,,,,,,,,,,,,%8 Model,,,,,,,,,,,,,,"
										",Calling,Compliance,,,,Secondary,,,Report Generation,,Proposed Model,,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,%9 Model,,,,,,,,,,,,,,,%10"
										" Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,,,%11 Model,,,,,,,,,,,,,,,Target Performance:,,,,,,,,,,,,,\n";   // ~700 chars
static char szT24NCSV2_Dyn[] =	",,,,,Conditioned Floor,Total Floor,,,Pass /,Compliance,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Energy Consumption (th"
										"erms),,,,,,,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,%1 (%2) (%3/ft2),,,,,,,,,,,,,,,,%4 by Fuel (%5/ft2),,,Cooling"
										" Unmet Load Hours,,,Heating Unmet Load Hours,,,Req'd PV,Proposed,Standard,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Ene"
										"rgy Consumption (therms),,,,,,,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,%6 (%7) (%8/ft2),,,,,,,,,,,,,,,%9 by Fuel (%10"
										"/ft2),,,Cooling Unmet Load Hours,,,Heating Unmet Load Hours,,,Generation Coincident Peak Demand (kW),,,,,,,,,,,,,,,Generation Coincident Peak De"
										"mand (kW),,,,,,,,,,,,,,,Application,Manager,Ruleset,OpenStudio,EnergyPlus,Simulation,,,NRCC/LMCC PRF Processing,,Site Electric CO2 Emissions (tonne),,,,"
										",,,,,,,,,,,Site Fuel CO2 Emissions (tonne),,,,,,,,,,,,,Site Electric CO2 Emissions (tonne),,,,,,,,,,,,,,,Site Fuel CO2 Emissions (tonne),,,,,,,,,,,"
										",,Source Energy Use (kBtu/ft2),,,,,,,,,,,,,,,Source Energy Use (kBtu/ft2),,,,,,,,,,,,,,,%11 (%12/ft2),,,,,,,Source Energy Use (kBtu/ft2),,,,,,,\n";   // ~1191 chars   // enable dynamic labels - SAC 01/26/23  // add metric units labels - SAC 10/29/23

static char szS901GCSV1[]	=	",,,,Analysis:,,,,Proposed Model:,,,Proposed Model,,,,Proposed Model,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,Proposed Model"
										",,,,,,Standard Model:,,,Standard Model,,,,Standard Model,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,Standard Model,,,,,,,,,,,,Standard Model,,,,,,Calling,Compliance,,,,Secondary,,\n";
static char szS901GCSV2[]	=	",,,,,,Pass /,Compliance,Elapsed,,,Energy Costs ($),,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,Natural Gas Energy Consumption (therms),,,,,,,"
										",,,,,Other Fuel Energy Consumption (MBtu),,,,,,,,,,,,Cooling Unmet Load Hours,,,Heating Unmet Load Hours,,,Elapsed,,,Energy Costs ($),,,,Electric E"
										"nergy Consumption (kWh),,,,,,,,,,,,,,Natural Gas Energy Consumption (therms),,,,,,,,,,,,Other Fuel Energy Consumption (MMBtu),,,,,,,,,,,,Cooling Un"
										"met Load Hours,,,Heating Unmet Load Hours,,,Application,Manager,Ruleset,OpenStudio,EnergyPlus,Simulation,,\n";
static char szS901GCSV3[]	=	"Start Date & Time,Filename (saved to),Run Title,Weather Station,Analysis Type,Elapsed Time,Fail,Margin,Time,Rule Eval Status,Simulation Status,Elec"
										"tricity,Natural Gas,Other Fuel,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,Proce"
										"ss,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,Pr"
										"ocess,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,Process,Ot"
										"her Ltg,Proc Mtrs,TOTAL,Zone Max,Zone Name,Num Zones Exceed Max,Zone Max,Zone Name,Num Zones Exceed Max,Time,Rule Eval Status,Simulation Status,Ele"
										"ctricity,Natural Gas,Other Fuel,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,Proc"
										"ess,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,P"
										"rocess,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Receptacle,Process,O"
										"ther Ltg,Proc Mtrs,TOTAL,Zone Max,Zone Name,Num Zones Exceed Max,Zone Max,Zone Name,Num Zones Exceed Max,Version,Version,Version,Version,Version,Ve"
										"rsion,Weather File Path,Project Path\n";

int CMX_PopulateResultsHeader_CECNonRes(	char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len )	// SAC 5/16/14
{	return CMX_PopulateResultsHeader_NonRes( pszHdr1, iHdr1Len, pszHdr2, iHdr2Len, pszHdr3, iHdr3Len, CT_T24N );
}

int CMX_PopulateResultsHeader_NonRes(	char* pszHdr1, int iHdr1Len, char* pszHdr2, int iHdr2Len, char* pszHdr3, int iHdr3Len, int iCodeType )	// SAC 12/3/14
{	int iRetVal = 0;
	const char* pszaHdrs[3];
   long lEngyCodeYearNum=0;
   BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" ), lEngyCodeYearNum );  // SAC 12/01/22
	if (iCodeType == CT_S901G || iCodeType == CT_ECBC)
	{	pszaHdrs[0] = szS901GCSV1;		pszaHdrs[1] = szS901GCSV2;		pszaHdrs[2] = szS901GCSV3;
	}
	else
	{	pszaHdrs[0] = szT24NCSV1;		pszaHdrs[1] = szT24NCSV2;		pszaHdrs[2] = szT24NCSV3;
	}

   QString qsCompMetricLbl_Short, qsCompMetricLbl_Long, qsCompMetricLbl_Units, qsDynamic2ndHeader;         // base metric label on new ruleset var - SAC 01/26/23  // metric units - SAC 10/29/23
   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), qsCompMetricLbl_Short );
   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Long"  ), qsCompMetricLbl_Long  );
   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Units" ), qsCompMetricLbl_Units );
   if (iCodeType != CT_S901G && iCodeType != CT_ECBC && !qsCompMetricLbl_Short.isEmpty() && !qsCompMetricLbl_Long.isEmpty() && !qsCompMetricLbl_Units.isEmpty())
      qsDynamic2ndHeader = QString( szT24NCSV2_Dyn ).arg( qsCompMetricLbl_Long, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Long, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units );

   long lIsCalPRM = 0, lDBID_Proj_IsCalPRM = BEMPX_GetDatabaseID( "Proj:IsCalPRM" );      // SAC 10/29/23
   if (lDBID_Proj_IsCalPRM > 0)
      BEMPX_GetInteger( lDBID_Proj_IsCalPRM, lIsCalPRM );
   QString qsDynamic1stHeader, qsBaseModelName = (lIsCalPRM ? "Baseline" : "Standard");
   if (iCodeType != CT_S901G && iCodeType != CT_ECBC && !qsCompMetricLbl_Short.isEmpty() && !qsCompMetricLbl_Long.isEmpty())
      qsDynamic1stHeader = QString( szT24NCSV1_Dyn ).arg( qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName );

#pragma warning(disable:4996)
	if (pszHdr1 && iHdr1Len > 0)
	{	if (!qsDynamic1stHeader.isEmpty())     // SAC 10/29/23
      {  strncpy( pszHdr1, qsDynamic1stHeader.toLocal8Bit().constData(), iHdr1Len-1 );
		   if (iRetVal == 0 && strlen( pszHdr1 ) < qsDynamic1stHeader.length())
			   iRetVal = 1;
      }
      else
      {  strncpy( pszHdr1, pszaHdrs[0], iHdr1Len-1 );
		   if (strlen( pszHdr1 ) < strlen( pszaHdrs[0] ))
			   iRetVal = 1;
	}  }
	if (pszHdr2 && iHdr2Len > 0)
	{	if (!qsDynamic2ndHeader.isEmpty())     // SAC 01/26/23
      {  strncpy( pszHdr2, qsDynamic2ndHeader.toLocal8Bit().constData(), iHdr2Len-1 );
		   if (iRetVal == 0 && strlen( pszHdr2 ) < qsDynamic2ndHeader.length())
			   iRetVal = 2;
      }
      else
      {  strncpy( pszHdr2, pszaHdrs[1], iHdr2Len-1 );
		   if (iRetVal == 0 && strlen( pszHdr2 ) < strlen( pszaHdrs[1] ))
			   iRetVal = 2;
	}  }
	if (pszHdr3 && iHdr3Len > 0)
	{	strncpy( pszHdr3, pszaHdrs[2], iHdr3Len-1 );
		if (iRetVal == 0 && strlen( pszHdr3 ) < strlen( pszaHdrs[2] ))
			iRetVal = 3;
	}
#pragma warning(default:4996)
	return iRetVal;
}

const char* GetResultsCSVHeader_NonRes( int i1HdrIdx, int iCodeType )	// SAC 12/3/14
{	const char* pszRetVal = NULL;
	switch (iCodeType)
	{	case CT_S901G :
		case CT_ECBC  :	switch (i1HdrIdx)
								{	case  2 :	pszRetVal = szS901GCSV2;		break;
									case  3 :	pszRetVal = szS901GCSV3;		break;
									default :	pszRetVal = szS901GCSV1;		break;
								}	break;
		default :			switch (i1HdrIdx)
								{	case  2 :	pszRetVal = szT24NCSV2;			break;
									case  3 :	pszRetVal = szT24NCSV3;			break;
									default :	pszRetVal = szT24NCSV1;			break;
								}	break;
	}
	return pszRetVal;
}


/////////////////////////////////////////////////////////////////////////////

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error - Results string length insufficient to store entire CSV record
//											 2 : Error - Results string empty
int CMX_PopulateCustomMeterCSVResultSummary_NonRes(	char* pszResultsString, int iResultsStringLength, const char* pszProjectPathFileName /*=NULL*/,
														            int i0EUseSummaryIdx /*=0*/ )	// SAC 11/04/23
{	int iRetVal = 0;

	QString sModelPathFile		= pszProjectPathFileName;
	RelativeToCompletePath_IfNeeded( sModelPathFile   );
	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                            sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

//	// ensure CodeType-specific BEMProcIdx used in retrieving UMLH (and other?) results
//	int iModelCount = BEMPX_GetModelCount();
//	int iBEMProcIdx_Prop = ((iCodeType == CT_T24N && iModelCount >= 4) ? 3 : (iCodeType != CT_T24N && iModelCount >= 7) ? 6 : (iModelCount >= 4) ? 3 : -1);
//	int iBEMProcIdx_Std  = ((iCodeType == CT_T24N && iModelCount >= 5) ? 4 : (iCodeType != CT_T24N && iModelCount >= 8) ? 7 : (iModelCount >= 5) ? 4 : -1);

	QString sRunTitle, sWthrStn, sCmpMgrVer, /*sAnnWthrFile,*/ sTimeStamp, sLogMsg, sBEMErr;
	double dRptTotArea, dRptCndArea, dResFlrArea; 
   long lResLivingUnitCnt;
	int iCID_Proj      = GetBEMBaseCompID( sBEMErr, "Proj"      );
	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"       ), sRunTitle );
	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherStation" ), sWthrStn  );
	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), sCmpMgrVer );
	//BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile"  ), sAnnWthrFile );
	BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotFlrArea"      ), dRptTotArea );
	BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), dRptCndArea );
	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunDateLog"      ), sTimeStamp );
	BEMPX_GetInteger( BEMPX_GetDatabaseID( "Bldg:ResLivingUnitCnt" ), lResLivingUnitCnt );    // SAC 11/06/23
	BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:ResFlrArea"       ), dResFlrArea );

   _snprintf( pszResultsString, iResultsStringLength-2, "%s,\"%s\",\"%s\",\"%s\",%g,%g,%g,%d,\"%s\",",
               sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(),
               dRptCndArea, dRptTotArea, dResFlrArea, lResLivingUnitCnt, sCmpMgrVer.toLocal8Bit().constData() );

   QString sMtr;     int iNumMeters = 0;     double dVal;   char pszVal[32];
   long lDBID_EUseSum_CSEMeterNames_ap     = BEMPX_GetDatabaseID( "EUseSummary:CSEMeterNames_ap" );
   long lDBID_EUseSum_CSEMeterResults_ap_1 = BEMPX_GetDatabaseID( "EUseSummary:CSEMeterResults_ap_1" );
   do
   {  if (BEMPX_GetString( lDBID_EUseSum_CSEMeterNames_ap+iNumMeters, sMtr, FALSE, 0, -1, i0EUseSummaryIdx ) && !sMtr.isEmpty())
      {  int iEU=-1;
         while( pszCSEEnduseListALL[++iEU] != NULL)
         {  if (BEMPX_GetFloat( lDBID_EUseSum_CSEMeterResults_ap_1 + (BEM_PARAM_MULT * iNumMeters) + iEU, dVal ))
            {  _snprintf( pszVal, 32, "%g,", dVal );
               strcat_s( pszResultsString, iResultsStringLength-2, pszVal );
            }
            else
               strcat_s( pszResultsString, iResultsStringLength-2, "," );
         }
         iNumMeters++;
      }
      else
         sMtr.clear();
   } while (!sMtr.isEmpty());

   strcat_s( pszResultsString, iResultsStringLength, "\n" );
   return iRetVal;
}

int CMX_PopulateCustomMeterCSVResultSummaryHeaders_NonRes(	char* pszHeader1String, int iHeader1StringLength, char* pszHeader2String, int iHeader2StringLength, int i0EUseSummaryIdx )	 // SAC 11/04/23
{	int iRetVal = 0;
   long lDBID_EUseSum_CSEMeterNames_ap = BEMPX_GetDatabaseID( "EUseSummary:CSEMeterNames_ap" );
   int iNumMeters = 0;
   QStringList slMeters;   QString sMtr;
   do
   {  if (BEMPX_GetString( lDBID_EUseSum_CSEMeterNames_ap+iNumMeters, sMtr, FALSE, 0, -1, i0EUseSummaryIdx ) && !sMtr.isEmpty())
      {  iNumMeters++;
         if (sMtr.indexOf("Elec") >= 0)
         {  if (sMtr.indexOf("Dwell") >= 0)
               sMtr += " (kWh per dwelling),,,,,,,,,,,,,,,,,,,,,,,,,";
            else
               sMtr += " (kWh),,,,,,,,,,,,,,,,,,,,,,,,,";
         }
         else
         {  if (sMtr.indexOf("Dwell") >= 0)
               sMtr += " (kBtu per dwelling),,,,,,,,,,,,,,,,,,,,,,,,,";
            else
               sMtr += " (kBtu),,,,,,,,,,,,,,,,,,,,,,,,,";
         }
         slMeters.push_back( sMtr );
      }
      else
         sMtr.clear();
   } while (!sMtr.isEmpty());

   if (pszHeader1String && iHeader1StringLength > 0)
   {  _snprintf( pszHeader1String, iHeader1StringLength-2, ",,,,Conditioned Floor,Total Floor,Residential,Residential,Software," );
      for (int iMtr=0; iMtr < iNumMeters; iMtr++)
         strcat_s( pszHeader1String, iHeader1StringLength-2, slMeters[iMtr].toLocal8Bit().constData() );
      strcat_s( pszHeader1String, iHeader1StringLength, "\n" );
   }
   if (pszHeader2String && iHeader2StringLength > 0)
   {  _snprintf( pszHeader2String, iHeader2StringLength-2, "Start Date & Time,Filename (saved to),Run Title,Weather Station,Area (SqFt),Area (SqFt),Area (SqFt),Dwelling Count,SVN Rev," );
      for (int iMtr=0; iMtr < iNumMeters; iMtr++)
         strcat_s( pszHeader2String, iHeader2StringLength-2, szCSEEnduses_CSV );
      strcat_s( pszHeader2String, iHeader2StringLength, "\n" );
   }
   return iRetVal;
}

int CMX_WriteCustomMeterCSVResultSummary_NonRes(  const char* pszResultsPathFile, const char* pszProjectPathFileName  ) 
                     //         int iResultsStringLength, const char* pszProjectPathFileName /*=NULL*/,
							//							const char* pszSimWeatherPath /*=NULL*/, int iEUseSummaryIdx /*=0*/ )	// SAC 11/04/19
{	int iRetVal = 0;

	bool bWriteHdrs = (!FileExists( pszResultsPathFile ));
	QFile csvFile;
	csvFile.setFileName( pszResultsPathFile );
	bool bFileOK = false;
	if (bWriteHdrs)
		bFileOK = csvFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
	else
		bFileOK = csvFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
	if (!bFileOK)
	{	iRetVal = -1;     assert( FALSE );
	}
	else
	{
      char pszData[4096];
		if (bWriteHdrs)
		{	// populate & write header records
         char pszHdr1[1024];
         int iHdrRetVal = CMX_PopulateCustomMeterCSVResultSummaryHeaders_NonRes(	pszHdr1, 1024, pszData, 4096, 0 /*i0EUseSummaryIdx*/ );	 // SAC 11/06/23
         if (iHdrRetVal == 0)
         {  csvFile.write( pszHdr1 );
            csvFile.write( pszData );
         }
         else
         {	iRetVal = -2;     assert( FALSE );
         }
      }

      if (iRetVal == 0)
      {  // populate & write CustomMeter results data to CSV
         int iDataRetVal = CMX_PopulateCustomMeterCSVResultSummary_NonRes(	pszData, 4096, pszProjectPathFileName /*=NULL*/, 0 /*i0EUseSummaryIdx*/ );	 // SAC 11/06/23
         if (iDataRetVal == 0)
            csvFile.write( pszData );
         else
         {	iRetVal = -3;     assert( FALSE );
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

#define  CM_MAX_BATCH_VER 4		// SAC 6/21/18 - 2->3 (CSE path)  | SAC 1/24/20 - 3->4 (AnalysisAction table)

int path_len( std::string& str )
{	int iPathLen = -1, iPathLen2 = -1;
	if (str.rfind('\\') != std::string::npos)
		iPathLen  = (int) str.rfind('\\');
	if (str.rfind('/' ) != std::string::npos)
		iPathLen2 = (int) str.rfind('/' );
	return std::max( iPathLen, iPathLen2 );
}

// restored use of bDisplayProgress argument (to enable CBECC-CLI batch analysis) - SAC 02/13/25
int CMX_PerformBatchAnalysis_CECNonRes(	const char* pszBatchPathFile, const char* pszProjectPath, const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
														const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath,
														const char* /*pszLogPathFile*/, const char* pszUIVersionString, const char* pszOptionsCSV /*=NULL*/,
														char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bDisplayProgress /*=false*/, HWND hWnd /*=NULL*/, bool bOLDRules /*=false*/,
														int iSecurityKeyIndex /*=0*/, const char* pszSecurityKey /*=NULL*/, char* pszResultMsg /*=NULL*/, int iResultMsgLen /*=0*/,    // SAC 1/10/17   // SAC 12/3/17
                                          const char* pszProxyOptionsCSV /*=NULL*/, bool bSilent /*=false*/ )    // separate out Proxy settings since can't communicate these via CSV file (nested quoted strings) - SAC 10/09/21
{
	int iRetVal = 0;
	si1ProgressRunNum = 1;
	siNumProgressRuns = 1;
	std::ifstream in( pszBatchPathFile );
	if (!in.is_open())
	{	if (pszErrorMsg && iErrorMsgLen > 0)
			sprintf_s( pszErrorMsg, iErrorMsgLen, "Error opening batch definitions file:  %s", pszBatchPathFile );
									return -10;
	}

	std::string sBatchPathFile = pszBatchPathFile;
	std::string sBatchPath;
	int iTempPathLen = path_len( sBatchPathFile );
	if (iTempPathLen > 0)
		sBatchPath = sBatchPathFile.substr( 0, iTempPathLen+1 );
	std::string sProjPath = pszProjectPath;
	int iLenOptionsCSVArg = (pszOptionsCSV ? (int) strlen( pszOptionsCSV ) : 0);

	std::string sRulesetPathFile = pszRulesetPathFile;
	std::string sRulesetPath;
	iTempPathLen = path_len( sRulesetPathFile );
	if (iTempPathLen > 0)
		sRulesetPath = sRulesetPathFile.substr( 0, iTempPathLen+1 );

	std::string sBatchLogPathFile = (sBatchPathFile.rfind('.') != std::string::npos ? sBatchPathFile.substr( 0, sBatchPathFile.rfind('.') ) : sBatchPathFile);
	sBatchLogPathFile += ".log";
	std::string sOverwriteProjFileMsg = boost::str( boost::format( "The batch processing log file '%s' is opened in another application.  This file must be closed in that "
												"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
												"(once the file is closed), or \n'Abort' to abort the batch processing." ) % sBatchLogPathFile.c_str() );
	if (!OKToWriteOrDeleteFile( sBatchLogPathFile.c_str(), sOverwriteProjFileMsg.c_str(), bSilent ))
	{	if (pszErrorMsg && iErrorMsgLen > 0)
			sprintf_s( pszErrorMsg, iErrorMsgLen, "Unable to write to batch processing log file:  %s", sBatchLogPathFile.c_str() );
									return -11;
	}
	else
	{	if (FileExists( sBatchLogPathFile.c_str() ))  // add some separation between previous and new batch runs
		{	BEMPX_WriteLogFile( " ", sBatchLogPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			BEMPX_WriteLogFile( " ", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			BEMPX_WriteLogFile( "------------------------------", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}
		BEMPX_WriteLogFile( "Initiating batch processing...", sBatchLogPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	int iaBatchFieldsPerRecordByVer[] = {	 9,	// ver 1
														10,	// ver 2
														11,	// ver 3 - CSE path - SAC 6/21/18
														11,	// ver 4 - 11+(variable columns) - SAC 1/24/20
														-1  };
	std::string line;
	int iMode = 0;		// <0-Error Code / 0-Reading Header / 1-Reading Run Records / 2-Reading AnalysisAction data
	int iBatchVer = 1, iRunRecord = 0, iBatchRecNum = 0, iRunsToPerform = 0;
	std::string sBatchResultsFN, sBatchLogFN, sBatchCustomMeterResultsFN, sOverwriteResultsFileMsg, sOverwriteResultsCustomMeterFileMsg, sLogMsg, sErrMsg;
	std::string sRecProjInFN, sRecProjOutFN, sRecRunTitle, sRecOutput, sRecOptionCSV, sRecCopySimXMLToPath, sRecCopyCSEToPath;
	std::string sAnalActType, sAnalActPhase, sAnalActBeforeAfter, sAnalActObjProp, sAnalActAlterObj;	// SAC 1/24/20
	int iRecAutosizeP=0, iRecAutosizeBZ=0, iRecAutosizeB=0;
	std::vector<std::string> saProjInFN, saProjOutFN, saRunTitle, saOutput, saOptionCSV, saCopySimXMLToPath, saCopyCSEToPath, saBEMBaseFN, saRulesetFN;
	std::vector<std::string> saAnalActType, saAnalActPhase, saAnalActBeforeAfter, saAnalActObjProp, saAnalActAlterObj;	// SAC 1/24/20
	std::vector<int> iaAnalActDataType;		// SAC 1/25/20
	std::vector<std::vector<std::string>> saaAnalActStrData;		// SAC 1/25/20 - saaAnalActStrData[AnalActionRow][BatchRunRecord]
	std::vector<std::vector<double>> daaAnalActFltData;
	std::vector<std::vector<int>> iaaAnalActIntData, iaaAnalActCellBlank;
   int iNumCustomMeterRuns=0;    // SAC 11/04/23
   bool bSkipCustomMeterStorage=false;
	int iNumAnalysisActions = 0;
	std::vector<int> iaBatchRecNums;
	while (iMode >= 0 && iRunRecord > -1 && getline( in, line ))
	{	iBatchRecNum++;
		std::vector<std::vector<std::string> > lines;
		ParseCSV( line, lines );
		assert( lines.size()==1 );
		if (lines.size() > 0)
		{	if (lines[0][0].size() > 3 && lines[0][0][0] < 0 && lines[0][0][1] < 0 && lines[0][0][2] < 0 && lines[0][0][3] > 0)
				lines[0][0] = lines[0][0].erase( 0, 3 );		// SAC 5/9/17 - blast bogus chars prior to usable record data (possibly resulting from Excel save in 'CSV UTF-8' format)
			if (lines[0][0].find(';') == 0)
			{	// comment line - do nothing
			}
			else if (iMode == 0)
			{
				if (lines[0].size() < 2)
				{					iMode = -1;
									sErrMsg = boost::str( boost::format( "Error:  First line of data (record %d) contains only %d values (expecting 2):  '%s'" )
																						% iBatchRecNum % lines[0].size() % line.c_str() );
				}
				else
				{	
					iBatchVer = atoi( lines[0][0].c_str() );
					if (iBatchVer < 1 || iBatchVer > CM_MAX_BATCH_VER)
					{				iMode = -2;
									sErrMsg = boost::str( boost::format( "Error:  Invalid batch version number (%d) specified in record %d, expected value 1-%d" )
																						% iBatchVer % iBatchRecNum % CM_MAX_BATCH_VER );
					}
					else
					{
						sBatchResultsFN = lines[0][1];
						PrependPathIfNecessary( sBatchResultsFN, sBatchPath );
						sOverwriteResultsFileMsg = boost::str( boost::format( "The CSV file '%s' is opened in another application.  This file must be closed in that "
																	"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																	"(once the file is closed), or \n'Abort' to abort the batch processing." ) % sBatchResultsFN );
						if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str(), bSilent ))
						{			iMode = -3;
									sErrMsg = boost::str( boost::format( "Error:  Unable to write to batch results file specified in record %d:  '%s'" )
																						% iBatchRecNum % sBatchResultsFN.c_str() );
						}
						else if (iBatchVer > 3)
							iMode = 2;	// to read AnalysisAction table
						else
							iMode = 1;
					}
				}
			}
			else if (iMode == 2 && lines[0].size() > 0)	// read AnalysisAction table - SAC 1/24/20
			{
				sAnalActType = lines[0][0];
				if (boost::iequals( sAnalActType, "END" ))
					iMode = 1;  // begin reading batch run records next
				else if (lines[0].size() > 2)
				{	sAnalActPhase = lines[0][1];
					sAnalActBeforeAfter = lines[0][2];
					if (lines[0].size() > 3)
						sAnalActObjProp = lines[0][3];
					else
						sAnalActObjProp.clear();
					if (lines[0].size() > 4)
						sAnalActAlterObj = lines[0][4];
					else
						sAnalActAlterObj.clear();

					saAnalActType.push_back( sAnalActType );
					saAnalActPhase.push_back( sAnalActPhase );
					saAnalActBeforeAfter.push_back( sAnalActBeforeAfter );
					saAnalActObjProp.push_back( sAnalActObjProp );
					saAnalActAlterObj.push_back( sAnalActAlterObj );

					int iAADataType = 2; // string
					if (boost::iequals( sAnalActType, "NewFloat" ) || boost::iequals( sAnalActType, "SetFloat" ))
						iAADataType = 0;  // float
					else if (boost::iequals( sAnalActType, "NewInteger" ) || boost::iequals( sAnalActType, "SetInteger" ))
						iAADataType = 1;  // integer
					else if (boost::iequals( sAnalActType, "RulelistPathFile" ) || boost::iequals( sAnalActType, "TablePathFile" ))		// SAC 11/16/20
						iAADataType = 3;  // path/file
					iaAnalActDataType.push_back( iAADataType );

					std::vector<std::string> saAnalActStrData;		// SAC 1/25/20 - saaAnalActStrData[AnalActionRow][BatchRunRecord]
					saaAnalActStrData.push_back( saAnalActStrData );
					std::vector<double> daAnalActFltData;
					daaAnalActFltData.push_back( daAnalActFltData );
					std::vector<int> iaAnalActIntData;
					iaaAnalActIntData.push_back( iaAnalActIntData );
					std::vector<int> iaAnalActCellBlank;
					iaaAnalActCellBlank.push_back( iaAnalActCellBlank );
				}
				else
				{				iMode = -12;
								sErrMsg = boost::str( boost::format( "Error:  Too few values (%d) found for AnalysisAction #%d (file record %d) - expecting 3-5" )
																					% (int) lines[0].size() % (int) (saAnalActType.size()+1) % iBatchRecNum );
				}
			}
			else if (iMode == 1 && lines[0].size() > 0)
			{
				iNumAnalysisActions = (int) saAnalActType.size();
				if (iaBatchFieldsPerRecordByVer[iBatchVer-1] == 11 && iNumAnalysisActions > 0)	// SAC 1/25/20
					iaBatchFieldsPerRecordByVer[iBatchVer-1] += iNumAnalysisActions;
				iRunRecord = atoi( lines[0][0].c_str() );
				if (iRunRecord > 0)
				{	if ((INT) lines[0].size() < iaBatchFieldsPerRecordByVer[iBatchVer-1])
					{				iMode = -4;
									sErrMsg = boost::str( boost::format( "Error:  Too few values (%d) found in record %d - expecting %d" )
																						% (int) lines[0].size() % iBatchRecNum % iaBatchFieldsPerRecordByVer[iBatchVer-1] );
					}
					else
					{	// PARSE BATCH RUN RECORD
						int iFld = 1;
						std::string sThisBEMBaseFN, sThisProjRulesetFN, sAAData;
						sRecProjInFN = lines[0][iFld++];
						PrependPathIfNecessary( sRecProjInFN, sProjPath );
						if (!FileExists( sRecProjInFN.c_str() ))
						{			iMode = -5;
									sErrMsg = boost::str( boost::format( "Error:  Input project file specified in record %d not found:  '%s'" )
																						% iBatchRecNum % sRecProjInFN.c_str() );
						}
			// SAC 11/30/14 - code to use ruleset filename from project input (and if none specified, then 
						else
						{	sThisProjRulesetFN = BEMPX_GetRulesetFilenameFromProjectFile( sRecProjInFN.c_str() );
							if (sThisProjRulesetFN.length() < 1 || boost::iequals( sThisProjRulesetFN, "unknown" ))
								sThisProjRulesetFN = "";
							else
							{	if (sThisProjRulesetFN.rfind(':') != std::string::npos || sThisProjRulesetFN[0] == '\\' || sThisProjRulesetFN[0] == '/')
								{	// ruleset already setup w/ full path
								}
								else if (sRulesetPath.length() > 0)
									sThisProjRulesetFN = sRulesetPath + sThisProjRulesetFN;
								if (!FileExists( sThisProjRulesetFN.c_str() ))
									sThisProjRulesetFN = "";
						}	}
						if (sThisProjRulesetFN.length() < 1)
							sThisProjRulesetFN = pszRulesetPathFile;

			// SAC 12/3/14 - code to get ruleset-specific BEMBase file
						if (boost::iequals( sThisProjRulesetFN, pszRulesetPathFile ) || !FileExists( sThisProjRulesetFN.c_str() ))
							sThisBEMBaseFN = pszBEMBasePathFile;
						else
						{	QString sRulesetBEMBaseFile;
							if (BEMPX_ReadBEMBaseFile( sThisProjRulesetFN.c_str(), sRulesetBEMBaseFile ))
							{	sThisBEMBaseFN = sRulesetPath;
								sThisBEMBaseFN += sRulesetBEMBaseFile.toLocal8Bit().constData();
							}
							else
								sThisBEMBaseFN = pszBEMBasePathFile;	// error
						}

						if (iMode > 0)
						{	sRecProjOutFN = lines[0][iFld++];
							PrependPathIfNecessary( sRecProjOutFN, sProjPath );
							sOverwriteProjFileMsg = "The project file '";
							sOverwriteProjFileMsg.append( sRecProjOutFN );
							sOverwriteProjFileMsg.append( "' is opened in another application.  This file must be closed in that "
																		"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																		"(once the file is closed), or \n'Abort' to abort the batch processing." );
							if (!OKToWriteOrDeleteFile( sRecProjOutFN.c_str(), sOverwriteProjFileMsg.c_str(), bSilent ))
							{		iMode = -6;
									sErrMsg = boost::str( boost::format( "Error:  Unable to write to project output/save file specified in record %d:  '%s'" )
																						% iBatchRecNum % sRecProjOutFN.c_str() );
							}
						}

						if (iMode > 0)
						{	if (iBatchVer < 2)
								sRecCopySimXMLToPath.erase();
							else
							{	sRecCopySimXMLToPath = lines[0][iFld++];
								PrependPathIfNecessary( sRecCopySimXMLToPath, sProjPath );
								if (sRecCopySimXMLToPath.size() > 0 && !DirectoryExists( sRecCopySimXMLToPath.c_str() ))
								{	boost::filesystem::create_directories( sRecCopySimXMLToPath.c_str() );
									if (!DirectoryExists( sRecCopySimXMLToPath.c_str() ))
									{	iMode = -10;
										sErrMsg = boost::str( boost::format( "Error:  Path to copy simulation SDD XML files to (specified in record %d) not found:  '%s'" )
																							% iBatchRecNum % sRecCopySimXMLToPath.c_str() );
								}	}
							}
						}

						if (iMode > 0)
						{	if (iBatchVer < 3)
								sRecCopyCSEToPath.erase();
							else
							{	sRecCopyCSEToPath = lines[0][iFld++];
								PrependPathIfNecessary( sRecCopyCSEToPath, sProjPath );
								if (sRecCopyCSEToPath.size() > 0 && !DirectoryExists( sRecCopyCSEToPath.c_str() ))
								{	boost::filesystem::create_directories( sRecCopyCSEToPath.c_str() );
									if (!DirectoryExists( sRecCopyCSEToPath.c_str() ))
									{	iMode = -11;
										sErrMsg = boost::str( boost::format( "Error:  Path to copy CSE simulation files to (specified in record %d) not found:  '%s'" )
																							% iBatchRecNum % sRecCopyCSEToPath.c_str() );
								}	}
							}
						}

						if (iMode > 0)
							sRecRunTitle = lines[0][iFld++];

						if (iMode > 0 && iNumAnalysisActions > 0)		// SAC 1/25/20 - read AnalysisAction data columns for this batch rec into array matrix
						{
							for (int iAA=0; (iMode > 0 && iAA < iNumAnalysisActions); iAA++)
							{	if (iAA > 0)
									sAAData += " | ";
								if (lines[0][iFld++].size() < 1)
								{	iaaAnalActCellBlank[iAA].push_back( 1 );
									saaAnalActStrData[  iAA].push_back( "" );
									daaAnalActFltData[  iAA].push_back( 0 );
									iaaAnalActIntData[  iAA].push_back( 0 );
									sAAData += "-";
								}
								else
								{	iaaAnalActCellBlank[iAA].push_back( 0 );
									sAAData += lines[0][iFld-1];
									if (iaAnalActDataType[iAA] == 0)
										daaAnalActFltData[iAA].push_back( atof( lines[0][iFld-1].c_str() ) );
									else
										daaAnalActFltData[iAA].push_back( 0 );
									if (iaAnalActDataType[iAA] == 1)
										iaaAnalActIntData[iAA].push_back( atoi( lines[0][iFld-1].c_str() ) );
									else
										iaaAnalActIntData[iAA].push_back( 0 );
									if (iaAnalActDataType[iAA] == 2 || iaAnalActDataType[iAA] == 3)
										saaAnalActStrData[iAA].push_back( lines[0][iFld-1] );
									else
										saaAnalActStrData[iAA].push_back( "" );
						}	}	}

						if (iMode > 0)
						{	if (lines[0][iFld++].size() < 1)
								iRecAutosizeP = -1;
							else
							{	iRecAutosizeP = atoi( lines[0][iFld-1].c_str() );
								if (iRecAutosizeP < 0 || iRecAutosizeP > 1)
								{	iMode = -7;
									sErrMsg = boost::str( boost::format( "Error:  Invalid Proposed model autosize option (%d) specified in record %d" )
																						% iRecAutosizeP % iBatchRecNum );
								}
							}
						}

						if (iMode > 0)
						{	if (lines[0][iFld++].size() < 1)
								iRecAutosizeBZ = -1;
							else
							{	iRecAutosizeBZ = atoi( lines[0][iFld-1].c_str() );
								if (iRecAutosizeBZ < 0 || iRecAutosizeBZ > 1)
								{	iMode = -8;
									sErrMsg = boost::str( boost::format( "Error:  Invalid Baseline-Sizing model autosize option (%d) specified in record %d" )
																						% iRecAutosizeBZ % iBatchRecNum );
								}
							}
						}
						if (iMode > 0)
						{	if (lines[0][iFld++].size() < 1)
								iRecAutosizeB = -1;
							else
							{	iRecAutosizeB = atoi( lines[0][iFld-1].c_str() );
								if (iRecAutosizeB < 0 || iRecAutosizeB > 1)
								{	iMode = -9;
									sErrMsg = boost::str( boost::format( "Error:  Invalid Baseline model autosize option (%d) specified in record %d" )
																						% iRecAutosizeB % iBatchRecNum );
								}
							}
						}

						if (iMode > 0)
						{	sRecOutput = lines[0][iFld++];

							sRecOptionCSV.erase();
							switch (iRecAutosizeP)
							{	case  0 :	sRecOptionCSV = "OverrideAutosize_p,0,";		break;
								case  1 :	sRecOptionCSV = "OverrideAutosize_p,1,";		break;
							}
							switch (iRecAutosizeBZ)
							{	case  0 :	sRecOptionCSV += "OverrideAutosize_bz,0,";	break;
								case  1 :	sRecOptionCSV += "OverrideAutosize_bz,1,";	break;
							}
							switch (iRecAutosizeB)
							{	case  0 :	sRecOptionCSV += "OverrideAutosize_b,0,";		break;
								case  1 :	sRecOptionCSV += "OverrideAutosize_b,1,";		break;
							}
							if (sRecRunTitle.length() > 0)		// SAC 5/16/14 - pass RunTitle into analysis via OptionsCSV
							{	sRecOptionCSV += "RunTitle,\"";
								sRecOptionCSV += sRecRunTitle;
								sRecOptionCSV += "\",";
							}
							if (lines[0][iFld].size() > 0)
								sRecOptionCSV += lines[0][iFld++];
                     sRecOptionCSV += "IsBatchProcessing,1,";     // SAC 03/19/21
							if (iLenOptionsCSVArg > 0)
								sRecOptionCSV += pszOptionsCSV;
                     if (pszProxyOptionsCSV && strlen( pszProxyOptionsCSV ) > 0)    // SAC 10/09/21
                        sRecOptionCSV += pszProxyOptionsCSV;
						}

					// store info about this run to be performed
						if (iMode > 0)
						{	assert( iFld == iaBatchFieldsPerRecordByVer[iBatchVer-1] );
							iRunsToPerform++;
							saProjInFN.push_back(  sRecProjInFN  );
							saProjOutFN.push_back( sRecProjOutFN );
							saRunTitle.push_back(  sRecRunTitle );
							saOutput.push_back(    sRecOutput );
							saOptionCSV.push_back( sRecOptionCSV );
							iaBatchRecNums.push_back( iBatchRecNum );
							saCopySimXMLToPath.push_back( sRecCopySimXMLToPath );  // ver 2
							saCopyCSEToPath.push_back( sRecCopyCSEToPath );  // ver 3
							saBEMBaseFN.push_back( sThisBEMBaseFN );
							saRulesetFN.push_back( sThisProjRulesetFN );
							QVector<QString> saClrOptions;  saClrOptions.push_back("ProxyServerAddress");  saClrOptions.push_back("ProxyServerCredentials");  // SAC 8/21/18
							QString qsRecOptionCSV = sRecOptionCSV.c_str();
							StripOutCSVOptions( qsRecOptionCSV, &saClrOptions, "***" );

							sLogMsg = boost::str( boost::format( "  Run %d / record %d / in:  %s\n                                            / out:  %s\n"
																			"                                            / title: '%s' / results: '%s' / options: '%s'" )
																					% iRunsToPerform % iBatchRecNum % sRecProjInFN % sRecProjOutFN % sRecRunTitle % sRecOutput % qsRecOptionCSV.toLocal8Bit().constData() );
							if (iNumAnalysisActions > 0)
								sLogMsg += boost::str( boost::format( "\n                                            / AnalysisAction data: %s" ) % sAAData.c_str() );
							BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
					}
				}
			}
			else
			{	assert( FALSE );
			}
		}
	}

	int iRunsGood = 0, iRunsBad = 0;
	if (iMode > 0 && iRunsToPerform > 0)
	{					si1ProgressRunNum = 0;		// SAC 5/28/15
						siNumProgressRuns = iRunsToPerform;
		char pszRuleErr[1024];
		bool bAbort = false;
// LOOP OVER EACH BATCH RUN DEFINED
		for (int iRun=0; (!bAbort && iRun < iRunsToPerform); iRun++)
		{				si1ProgressRunNum++;		// SAC 5/28/15
         bool bThisRunGood = false;
			pszRuleErr[0] = '\0';
     		//CTime timeStartRun = CTime::GetCurrentTime();
			QDateTime timeStartRun = QDateTime::currentDateTime();
			sErrMsg.erase();
			std::string sProjPathFile = saProjOutFN[iRun];
			int iLastDotIdx   = (int) sProjPathFile.rfind('.');			assert( iLastDotIdx   > 0 );
			int iLastSlashIdx = path_len( sProjPathFile );			assert( iLastSlashIdx > 0 );
			std::string sProcessingPath = sProjPathFile.substr( 0, iLastDotIdx );
			sProcessingPath += " - batch\\";
			std::string sProjPath = sProjPathFile.substr( 0, iLastSlashIdx+1 );

			bool bHaveAnalActionsThisRun = false;
			if (iNumAnalysisActions > 0)
			{	for (int iAA=0; (!bHaveAnalActionsThisRun && iAA<iNumAnalysisActions); iAA++)
				{	assert( (int) iaaAnalActCellBlank[iAA].size() > iRun );
					bHaveAnalActionsThisRun = (iaaAnalActCellBlank[iAA][iRun] == 0);
			}	}
			if (bHaveAnalActionsThisRun)		// APPEND special ID to end of sProjPathFile to be used to assemble the final file including AnalysisAction objects - SAC 1/26/20
				sProjPathFile += "-orig";

			if (!DirectoryExists( sProjPath.c_str() ))
				CreateAndChangeDirectory( sProjPath.c_str(), FALSE );
			if (!boost::iequals( saProjInFN[iRun].c_str(), sProjPathFile.c_str() ) &&   // only copy IN to OUT file if they are different
			    !CopyFile( saProjInFN[iRun].c_str(), sProjPathFile.c_str(), FALSE ))
			{
									sErrMsg = boost::str( boost::format( "Error:  Unable to copy project file (run %d, record %d):  '%s'  to:  '%s'" )
																						% (iRun+1) % iaBatchRecNums[iRun] % saProjInFN[iRun].c_str() % sProjPathFile.c_str() );
			}
			else if (bHaveAnalActionsThisRun)		// write AnalysisAction data into bottom of batch input before processing - SAC 1/25/20
			{	std::string ibdLine;
				std::ifstream bemInFile(  sProjPathFile );
				std::ofstream bemOutFile( saProjOutFN[iRun] );  //, std::ios_base::binary | std::ios_base::app );
				if (bemInFile.is_open() && bemOutFile.is_open())
				{	//bemFile.seekg( -256, std::ios::end );		// move to 128 chars from the end of the file
					while (getline(bemInFile, ibdLine))
					{
  						if (ibdLine.find( "END_OF_FILE" ) != std::string::npos)
  						{	for (int iAA=0; iAA<iNumAnalysisActions; iAA++)
							{	assert( (int) iaaAnalActCellBlank[iAA].size() > iRun );
								if (iaaAnalActCellBlank[iAA][iRun] == 0)
								{
  									bemOutFile << boost::str( boost::format(    "\nAnalysisAction   \"AnalAct %d\"\n" ) % (iAA+1) );
  									bemOutFile << boost::str( boost::format(    "   Type = \"%s\"\n" ) % saAnalActType[iAA] );
  									bemOutFile << boost::str( boost::format(    "   AnalysisPhase = \"%s\"\n" ) % saAnalActPhase[iAA] );
  									bemOutFile << boost::str( boost::format(    "   BeforeAfterPhase = \"%s\"\n" ) % saAnalActBeforeAfter[iAA] );
									if (saAnalActObjProp[iAA].length() > 0)
	  									bemOutFile << boost::str( boost::format( "   ObjPropertyName = \"%s\"\n" ) % saAnalActObjProp[iAA] );
									if (saAnalActAlterObj[iAA].length() > 0)
	  									bemOutFile << boost::str( boost::format( "   AlterObjName = \"%s\"\n" ) % saAnalActAlterObj[iAA] );
									switch (iaAnalActDataType[iAA])
									{	case  0 :  bemOutFile << boost::str( boost::format( "   SetValFloat = %g\n"        ) % daaAnalActFltData[iAA][iRun] );		break;
										case  1 :  bemOutFile << boost::str( boost::format( "   SetValInteger = %d\n"      ) % iaaAnalActIntData[iAA][iRun] );		break;
										case  2 :  bemOutFile << boost::str( boost::format( "   SetValString = \"%s\"\n"   ) % saaAnalActStrData[iAA][iRun] );		break;
										default :  bemOutFile << boost::str( boost::format( "   SetValPathFile = \"%s\"\n" ) % saaAnalActStrData[iAA][iRun] );		break;
									}
  									bemOutFile << "   ..\n\n";
  							}	}
  							bemOutFile << "\nEND_OF_FILE\n\n";
							break;
  						}
  						else
  						{	bemOutFile << ibdLine;
  							bemOutFile << '\n';
  					}	}
					//bemInFile.close();
					bemOutFile.flush();
					//bemOutFile.close();  - force destructor to perform close to ensure immediate read of the file (bleow) is successful
				}
				else
				{					sErrMsg = boost::str( boost::format( "Error:  Unable to open and insert AnalysisAction objects to project file (run %d, record %d):  '%s'" )
																						% (iRun+1) % iaBatchRecNums[iRun] % sProjPathFile.c_str() );
				}
				sProjPathFile = saProjOutFN[iRun];	// restore original proj out filename for further processing
			}


//	Sleep(5000);				// SAC 5/22/19 - additional pause to ensure directory clean-up successful


			if (sErrMsg.size() < 1)
			{
				int iAnalRetVal = -1;
            bool bRulesetNameIncl25 = (saRulesetFN[iRun].find("25") != std::string::npos ? true : false);     // SAC 10/25/22
				assert( !bOLDRules );
				char pszResultsRecord[3200] = "\0";       // increased length from 2056->3200 - SAC 05/25/22
					iAnalRetVal = CMX_PerformAnalysis_CECNonRes( saBEMBaseFN[iRun].c_str() /*pszBEMBasePathFile*/, saRulesetFN[iRun].c_str() /*pszRulesetPathFile*/,
												pszSimWeatherPath, pszCompMgrDLLPath, pszDHWWeatherPath, sProcessingPath.c_str(), sProjPathFile.c_str(),
												sBatchLogPathFile.c_str() /* ??? use overall batch OR individual Project Log File ??? */,
												pszUIVersionString, true /*bLoadModelFile*/, saOptionCSV[iRun].c_str(), pszRuleErr, 1024,
												/*true*/ bDisplayProgress, hWnd, pszResultsRecord, 3200, iSecurityKeyIndex, pszSecurityKey );   // SAC 1/10/17
				if (iAnalRetVal == 33)
				{	// User aborted individual run, so ask if they want to abort ALL remaining runs
									sErrMsg = boost::str( boost::format( "User aborted batch run %d (record %d)..." ) % (iRun+1) % iaBatchRecNums[iRun] );
					if (iRun < (iRunsToPerform - 1))
					{	if (bSilent)      // SAC 02/13/25
                     bAbort = true;
                  else
                  {  sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
						   if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
							   bAbort = true;
					}  }
				}
				else if (iAnalRetVal > 0)
				{	// some error occurred - should be documented already
					if (strlen( pszRuleErr ) > 0)
									sErrMsg = boost::str( boost::format( "Error:  Processing batch run %d, record %d:  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % pszRuleErr );
					else			sErrMsg = boost::str( boost::format( "Error:  Processing batch run %d, record %d:  (no description returned)" ) % (iRun+1) % iaBatchRecNums[iRun]  );
				}
				else
				{	// RUN SUCCEEDED
					QVector<QString> saCSVOptions;
					if (saOptionCSV[iRun].size() > 0)
					{	if (ParseCSVRecord( saOptionCSV[iRun].c_str(), &saCSVOptions ) < 2)
						{	assert( false );
					}	}
               long lEnableResearchMode	      =   GetCSVOptionValue( "EnableResearchMode"         ,   0,  saCSVOptions );		// SAC 04/06/22

//	if (iRun < (iRunsToPerform - 1) && ::MessageBox( hWnd, "Confirm Continue", "Run Succeeded ... Continue w/ remaining runs?", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) != IDYES)
//		bAbort = true;

	      		//CTime locTime = CTime::GetCurrentTime();
					QDateTime locTime = QDateTime::currentDateTime();

				// SAC 12/3/14 - logic identical to analysis routine to identify ruleset type - used to determine which CSV results file headers to use
					int iCodeType = CT_T24N;		// SAC 10/2/14 - added to facilitate code-specific processing
					QString sLoadedRuleSetID, sLoadedRuleSetVer;
					if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))
					{	if (sLoadedRuleSetID.indexOf( "T24N" ) >= 0 || sLoadedRuleSetID.indexOf( "CA " ) == 0)
							iCodeType = CT_T24N;
						else if (sLoadedRuleSetID.indexOf( "S901G" ) >= 0 ||
									(sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0))
							iCodeType = CT_S901G;
						else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
							iCodeType = CT_ECBC;
						else if (sLoadedRuleSetID.indexOf( "360" ) >= 0)	// SAC 1/30/20
							iCodeType = CT_360;
						else
						{	assert( FALSE );	// what ruleset is this ??
					}	}
               long iCUACReportID = GetCSVOptionValue( "CUACReportID", 0, saCSVOptions );    // value > 0 => doing CUAC analysis & reporting - SAC 12/11/23 (CUAC)

				   // SAC 11/4/19 - moved summary results CSV record writing to HERE FROM BELOW to enable export of multiple records (results sets) per run
					if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str(), bSilent ))
					{	if (iRun < (iRunsToPerform - 1))
						{	if (bSilent)
                        bAbort = true;
                     else 
                     {  sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
							   if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
								   bAbort = true;
						}  }
					}
					else
					{	bool bWriteHdrs = (!FileExists( sBatchResultsFN.c_str() ));
						QFile csvFile;
						csvFile.setFileName( sBatchResultsFN.c_str() );
						bool bFileOK = false;
						if (bWriteHdrs)
							bFileOK = csvFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
						else
							bFileOK = csvFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
						if (!bFileOK)
						{	assert( FALSE );
						}
						else
						{
                     if (iCUACReportID > 0)
                     {
							   if (bWriteHdrs)
							   {	// WRITE HEADER RECORDS
                           csvFile.write( ",,,,,,,,,,,,,,,,,,Unit Type Results,,\n" );
                           csvFile.write( ",,,,Elapsed,Electric,,,Gas,,,Unit Type Weighted Average Allowances ($),,,,,Num Units,,,Number,\n" );
                           csvFile.write( "Start Date & Time,Filename (saved to),Run Title,Weather Station,Time,Utility,Territory,Tariff,Utility,Territory,Tariff,Electric,Gas,Water,Trash,Total,Total,,Unit Type,of Units,\n" );
                        }
                        int iCSVRetVal = CUAC_WriteCSVSummary( csvFile, sProjPathFile.c_str(), pszSimWeatherPath, 0 /*MFam*/ );
                     }
                     else
                     {
							   if (bWriteHdrs)
							   {	// WRITE HEADER RECORDS
                           QString qsCompMetricLbl_Short, qsCompMetricLbl_Long, qsCompMetricLbl_Units, qsDynamic1stHeader, qsDynamic2ndHeader;         // base metric label on new ruleset var - SAC 01/26/23  // metric units & CalPRM - SAC 10/29/23
                           long lIsCalPRM = 0;
                           if (iCodeType == CT_T24N)
                           {  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), qsCompMetricLbl_Short );
                              BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Long"  ), qsCompMetricLbl_Long  );
                              BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Units" ), qsCompMetricLbl_Units );
                              long lDBID_Proj_IsCalPRM = BEMPX_GetDatabaseID( "Proj:IsCalPRM"  );         // SAC 10/29/23
                              if (lDBID_Proj_IsCalPRM > 0)
                                 BEMPX_GetInteger( lDBID_Proj_IsCalPRM, lIsCalPRM );
                           }
                           if (iCodeType == CT_T24N && !qsCompMetricLbl_Short.isEmpty())     // SAC 10/29/23
                           {  QString qsBaseModelName = (lIsCalPRM ? "Baseline" : "Standard");
                              qsDynamic1stHeader = QString( szT24NCSV1_Dyn ).arg( qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName, qsBaseModelName );
                              csvFile.write( qsDynamic1stHeader.toLocal8Bit().constData() );
                           }
                           else
                              csvFile.write( GetResultsCSVHeader_NonRes( 1, iCodeType ) );

                           //if (bRulesetNameIncl25 && iCodeType == CT_T24N)
                           //   csvFile.write( szT24NCSV2_SLCC );      // kludge to select column labels replacing kTDV w/ $ for 2025 T24N - SAC 10/25/22
                           //else
                           //   csvFile.write( GetResultsCSVHeader_NonRes( 2, iCodeType ) );
                           if (iCodeType == CT_T24N)
                           {  
                              if (!qsCompMetricLbl_Short.isEmpty() && !qsCompMetricLbl_Long.isEmpty())
                                 qsDynamic2ndHeader = QString( szT24NCSV2_Dyn ).arg( qsCompMetricLbl_Long, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Long, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units, qsCompMetricLbl_Short, qsCompMetricLbl_Units );
                              csvFile.write( qsDynamic2ndHeader.toLocal8Bit().constData() );
                           }
                           else
                              csvFile.write( GetResultsCSVHeader_NonRes( 2, iCodeType ) );

                           csvFile.write( GetResultsCSVHeader_NonRes( 3, iCodeType ) );
							   }

			         	   csvFile.write( pszResultsRecord );

							   // export CSV results for subsequent results sets (when multiple EUseSummary objects present)
							   int iCSVRetVal = 0;
							   long lNumResultsSets=0;
							   BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NumResultsSets" ), lNumResultsSets );		// SAC 11/04/19
							   // check for consistency between lNumResultsSets & number of EUseSummary objects??
							   for (int iResSet = 1; (iResSet < lNumResultsSets && iCSVRetVal < 1); iResSet++)
							   {	iCSVRetVal = CMX_PopulateCSVResultSummary_NonRes( pszResultsRecord, 2056, sProjPathFile.c_str(), pszSimWeatherPath, iResSet );		// SAC 11/04/19
							   	if (iCSVRetVal < 1)
					            	csvFile.write( pszResultsRecord );
							   }
                     }

							csvFile.flush();
							csvFile.close();
							bThisRunGood = true;
						}
					}

               long lCustomMeterOption=0;
               BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CustomMeterOption" ), lCustomMeterOption, -1 );
               if (lCustomMeterOption > 0 && sBatchCustomMeterResultsFN.length() < 1 && iCUACReportID < 1)
               {
                  sBatchCustomMeterResultsFN  =  sBatchResultsFN.substr( 0, sBatchResultsFN.length()-4 );
                  sBatchCustomMeterResultsFN += "-CustomMeter.csv";
						sOverwriteResultsCustomMeterFileMsg = boost::str( boost::format( "The CSV file '%s' is opened in another application.  This file must be closed in that "
																	"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																	"(once the file is closed), or \n'Abort' to skip storage of custom meter results." ) % sBatchCustomMeterResultsFN );
						if (!OKToWriteOrDeleteFile( sBatchCustomMeterResultsFN.c_str(), sOverwriteResultsCustomMeterFileMsg.c_str(), bSilent ))
							bSkipCustomMeterStorage = true;
               }
               if (lCustomMeterOption > 0 && !bSkipCustomMeterStorage && iCUACReportID < 1)
               {  int iWriteCustomMeterCSVRetVal = CMX_WriteCustomMeterCSVResultSummary_NonRes( sBatchCustomMeterResultsFN.c_str(), sProjPathFile.c_str() );
                  if (iWriteCustomMeterCSVRetVal != 0)
						{	assert( FALSE );  // error writing CustomMeter CSV export
					}  }

				   // SAC 2/2/14 - mods to store analysis results back to project file
					bool bStoreResultsToModelInput =	(GetCSVOptionValue( "StoreResultsToModelInput", 1, saCSVOptions ) > 0);
					if (bStoreResultsToModelInput && iCUACReportID < 1)
					{
						QVector<QString> saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles, saNewEUseSumObjs;
						CMX_SaveAnalysisResultsToTempFiles( saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles );  // SAC 2/1/14
						if (saUniqueEUseSumObjs.size() < 1)
						{	assert( FALSE );  // no EUseSum objects found ???
						}
						else if (CMX_LoadModel( saBEMBaseFN[iRun].c_str() /*pszBEMBasePathFile*/, saRulesetFN[iRun].c_str() /*pszRulesetPathFile*/,
														sProjPathFile.c_str(), 0 /*MAX_BEMBASE_DATA_SET_ERRORS*/, NULL /*iaFailedBEMBaseDBIDs*/, true /*bSupressAllMsgBoxes*/,
														NULL /*iaFailedBEMBaseObjIdxs*/, NULL /*&saFailedBEMBaseData*/, false /*bLogDurations*/, sBatchLogPathFile.c_str() ) != 0)
						{	assert( FALSE );  // error reading model file BACK into memory
						}
						else
						{  // added storage of IsBatchProcessing to enable suppression of message boxes within ruleset - SAC 03/25/21
               	   long lIsBatchProcessing = 1;
                     long lDBID_IsBatchProcessing = BEMPX_GetDatabaseID( "Proj:IsBatchProcessing" );
                     if (lDBID_IsBatchProcessing > 0)
                  	   BEMPX_SetBEMData( lDBID_IsBatchProcessing, BEMP_Int, (void*) &lIsBatchProcessing, BEMO_User, 0, BEMS_ProgDefault );     // -> BEMS_ProgDefault - SAC 03/25/21

      			      // EnableResearchMode stuff, needed to prevent RESET of ERM-dependent data when batch processing - SAC 04/06/22
      				   long lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) );
                     assert( (lEnableResearchMode < 1 || lDBID_Proj_EnableResearchMode > 0) );     // if EnableResearchMode CSV option specified, then there should also be a valid EnableResearchMode ResProj property
      				   if (lDBID_Proj_EnableResearchMode > 0)
      				   {	long lERM;
      				   	if (!BEMPX_GetInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ))
      				   		lERM = -1;
      				   	if (lEnableResearchMode < 1 && lERM > 0.5)
      				   		// This file was last SAVED IN RESEARCH MODE, but current INI file does not include research mode enabling setting
      				   		BEMPX_WriteLogFile( "Warning: Research mode is selected in this project file but not activated in current analysis.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      				   	else if (lERM < -0.5)	// SAC 2/4/16 - only reset EnableResearchMode to INI setting if NOT specified in input file
      				         BEMPX_SetBEMData( lDBID_Proj_EnableResearchMode, BEMP_Int, (void*) &lEnableResearchMode, BEMO_User, -1, BEMS_ProgDefault );
      				   }

					// SAC 7/26/16 - fixed bug where lack of defaulting of building model was causing errors in final project file writing due to enum dependencies not being valid
							bool bVerboseInputLogging = (GetCSVOptionValue( "VerboseInputLogging", 0, saCSVOptions ) > 0);
							int iNumFileOpenDefaultingRounds = GetCSVOptionValue( "NumFileOpenDefaultingRounds", 3, saCSVOptions );
							for (int iDR=1; iDR <= iNumFileOpenDefaultingRounds; iDR++)
							   CMX_EvaluateRuleset( "rl_DEFAULT", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerboseInputLogging, NULL, NULL, NULL, NULL /*epInpRuleDebugInfo*/ );
						   //CMX_EvaluateRuleset( "rl_DEFAULT", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerboseInputLogging, NULL, NULL, NULL, NULL /*epInpRuleDebugInfo*/ );
						   //CMX_EvaluateRuleset( "rl_DEFAULT", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, bVerboseInputLogging, NULL, NULL, NULL, NULL /*epInpRuleDebugInfo*/ );

							CMX_RestoreAnalysisResultsFromTempFiles( saUniqueEUseSumObjs, saTempPathFiles );

							// ALSO store RunDate to be help verify whether results are "current"
							long lTime = (long) locTime.toTime_t();					assert( lTime > 0);
							if (lTime > 0)
								BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:RunDate" ), BEMP_Int, (void*) &lTime );

						// SAVE PROJECT FILE
						// Set SoftwareVersion to BEMBase Project
							if (pszUIVersionString && strlen( pszUIVersionString ) > 0)
							{	long lDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "Proj:SoftwareVersion" );
								QString sProjSoftwareVer;
								if (lDBID_Proj_SoftwareVersion > 0 &&
										(!BEMPX_GetString( lDBID_Proj_SoftwareVersion, sProjSoftwareVer ) || sProjSoftwareVer.isEmpty() || sProjSoftwareVer.compare( pszUIVersionString ) != 0) )
									BEMPX_SetBEMData( lDBID_Proj_SoftwareVersion, BEMP_Str, (void*) pszUIVersionString );
							}

						// Set BEMBase version ID value
							int iBEMCID_BEMVersion = BEMPX_GetDBComponentID( "BEMVersion" );
							long lBEMVerID = (iBEMCID_BEMVersion > 0 ? BEMPX_GetNumPropertyTypes( (int) iBEMCID_BEMVersion ) : 0);
							if (lBEMVerID > 0)
							{	long lCurBEMVer = 0;
								long lDBID_Proj_BEMVersion = BEMPX_GetDatabaseID( "Proj:BldgEngyModelVersion" );
								if ( lDBID_Proj_BEMVersion > 0 &&
										(!BEMPX_GetInteger( lDBID_Proj_BEMVersion, lCurBEMVer ) || lCurBEMVer != lBEMVerID) )
									BEMPX_SetBEMData( lDBID_Proj_BEMVersion, BEMP_Int, (void*) &lBEMVerID );
							}

							if (GetCSVOptionValue( "ClassifyEditableDefaultsAsUserData", 0 /*default*/, saCSVOptions ) > 0)		// SAC 2/21/20
								BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ );

							bool bFileSaveAllDefinedProperties = (GetCSVOptionValue( "FileSaveAllDefinedProperties", 0, saCSVOptions ) > 0);
							// SAC 6/14/16 - mod to ensure EITHER .xml OR .ribdx/.ribd16x are interpretted as XML files
							std::string sProjFileLastThreeChars = sProjPathFile.substr( sProjPathFile.size()-3, 3 );
							std::string sProjFileLastChar       = sProjPathFile.substr( sProjPathFile.size()-1, 1 );
							int iFileType = (boost::iequals( sProjFileLastThreeChars.c_str(), "xml" ) || boost::iequals( sProjFileLastChar.c_str(), "x" ) ? BEMFT_XML : BEMFT_Std);
							if (!BEMPX_WriteProjectFile( sProjPathFile.c_str(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/, TRUE /*bSupressAllMsgBoxes*/,
																	iFileType, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lTime-1 /*lModDate*/ ))
				      	{	assert( FALSE );  // failure to save file
				      	}
						}
					}

				// COPY Sim SDD XML files to specified location
					if (sErrMsg.size() < 1 && saCopySimXMLToPath[iRun].size() > 0 && iCUACReportID < 1)
					{	int iProjOutPathLen    = path_len( sProjPathFile ) + 1;												assert( iProjOutPathLen > 3 );
						int iProjOutFileExtLen = (int) (sProjPathFile.length() - sProjPathFile.rfind('.'));			assert( iProjOutFileExtLen > 2 && iProjOutFileExtLen < 8 );
						std::string sOutFileOnly = sProjPathFile.substr( iProjOutPathLen, (sProjPathFile.length()-iProjOutPathLen-iProjOutFileExtLen) );
						std::string sSimSDDXMLSrcBase = sProcessingPath;
						sSimSDDXMLSrcBase += sOutFileOnly;
						int iNumFiles = (bOLDRules ? 3 : 4);
						for (int iXMLIdx=0; (!bAbort && sErrMsg.size() < 1 && iXMLIdx < iNumFiles); iXMLIdx++)
						{	std::string sSimSDDXMLSrc = sSimSDDXMLSrcBase;
							std::string sFileToWrite = saCopySimXMLToPath[iRun];
							sFileToWrite  += sOutFileOnly;
							if (bOLDRules)
								switch (iXMLIdx)
								{	case  0 :	sSimSDDXMLSrc += " - p.xml";		sFileToWrite += " - p.xml";		break;
									case  1 :	sSimSDDXMLSrc += " - bz.xml";		sFileToWrite += " - bz.xml";		break;
									case  2 :	sSimSDDXMLSrc += " - b.xml";		sFileToWrite += " - b.xml";		break;
									default :	sSimSDDXMLSrc  = "";					sFileToWrite  = "";					break;
								}
							else
								switch (iXMLIdx)
								{	case  0 :	sSimSDDXMLSrc += " - zp.xml";		sFileToWrite += " - zp.xml";		break;
									case  1 :	sSimSDDXMLSrc += " - zb.xml";		sFileToWrite += " - zb.xml";		break;
									case  2 :	sSimSDDXMLSrc += " - ap.xml";		sFileToWrite += " - ap.xml";		break;
									case  3 :	sSimSDDXMLSrc += " - ab.xml";		sFileToWrite += " - ab.xml";		break;
									default :	sSimSDDXMLSrc  = "";					sFileToWrite  = "";					break;
								}
							if (sSimSDDXMLSrc.length() > 1)
							{
//		std::string sTempDbgCopy = boost::str( boost::format( "sProjPathFile = %s\niProjOutPathLen = %d   iProjOutFileExtLen = %d   sOutFileOnly = %s\nsSimSDDXMLSrcBase = %s\nsSimSDDXMLSrc = %s\nsFileToWrite = %s" )
//										% sProjPathFile % iProjOutPathLen % iProjOutFileExtLen % sOutFileOnly % sSimSDDXMLSrcBase % sSimSDDXMLSrc % sFileToWrite );
//		::MessageBox( hWnd, sTempDbgCopy.c_str(), "SDD XML Copying info", MB_ICONSTOP );
								if (boost::iequals( sSimSDDXMLSrc.c_str(), sFileToWrite.c_str() ))   // only copy IN to OUT file if they are different
								{	// no problem - simply do nothing
								}
								else if (!FileExists( sSimSDDXMLSrc.c_str() ))
								{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
									sLogMsg = boost::str( boost::format( "Unable to find simulation SDD XML file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sSimSDDXMLSrc );
									BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
								else
								{	std::string sOverwriteSDDXMLMsg = boost::str( boost::format( "The simulation SDD XML file '%s' is opened in another application.  This file must be closed in that "
																				"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																				"(once the file is closed), or \n'Abort' to abort the batch processing." ) % sFileToWrite.c_str() );
									if (!OKToWriteOrDeleteFile( sFileToWrite.c_str(), sOverwriteSDDXMLMsg.c_str(), bSilent ))
									{	if (bSilent)
                                 bAbort = true;
                              else 
                              {  sLogMsg = boost::str( boost::format( "Unable to overwrite simulation SDD XML file (run %d, record %d).\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
										   if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
											   bAbort = true;
										   else
										   {	sLogMsg = boost::str( boost::format( "User chose not to overwrite simulation SDD XML file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sFileToWrite.c_str() );
											   BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                              }  }
									}
									else if (!CopyFile( sSimSDDXMLSrc.c_str(), sFileToWrite.c_str(), FALSE ))
									{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
										sLogMsg = boost::str( boost::format( "Error encountered copying simulation SDD XML file (run %d, record %d) from '%s' to '%s'" ) % (iRun+1) % iaBatchRecNums[iRun] % sSimSDDXMLSrc.c_str() % sFileToWrite.c_str() );
										BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
							}	}
					}	}

				// COPY CSE files to specified location
					if (sErrMsg.size() < 1 && saCopyCSEToPath[iRun].size() > 0 && iCUACReportID < 1)
					{	int iProjOutPathLen    = path_len( sProjPathFile ) + 1;												assert( iProjOutPathLen > 3 );
						int iProjOutFileExtLen = (int) (sProjPathFile.length() - sProjPathFile.rfind('.'));			assert( iProjOutFileExtLen > 2 && iProjOutFileExtLen < 8 );
						std::string sOutFileOnly = sProjPathFile.substr( iProjOutPathLen, (sProjPathFile.length()-iProjOutPathLen-iProjOutFileExtLen) );
						std::string sCSESrcBase = sProcessingPath;
						sCSESrcBase += sOutFileOnly;
						for (int iCSEFileIdx=0; (!bAbort && sErrMsg.size() < 1 && iCSEFileIdx < 8); iCSEFileIdx++)
						{	std::string sCSESrc = sCSESrcBase;
							std::string sFileToWrite = saCopyCSEToPath[iRun];
							sFileToWrite  += sOutFileOnly;
								switch (iCSEFileIdx)
								{	case  0 :	sCSESrc += " - zp-cse.cse";		sFileToWrite += " - zp-cse.cse";		break;
									case  1 :	sCSESrc += " - zb-cse.cse";		sFileToWrite += " - zb-cse.cse";		break;
									case  2 :	sCSESrc += " - ap-cse.cse";		sFileToWrite += " - ap-cse.cse";		break;
									case  3 :	sCSESrc += " - ab-cse.cse";		sFileToWrite += " - ab-cse.cse";		break;
									case  4 :	sCSESrc += " - zp-cse.rep";		sFileToWrite += " - zp-cse.rep";		break;
									case  5 :	sCSESrc += " - zb-cse.rep";		sFileToWrite += " - zb-cse.rep";		break;
									case  6 :	sCSESrc += " - ap-cse.rep";		sFileToWrite += " - ap-cse.rep";		break;
									case  7 :	sCSESrc += " - ab-cse.rep";		sFileToWrite += " - ab-cse.rep";		break;
									default :	sCSESrc  = "";					sFileToWrite  = "";					break;
								}
							if (sCSESrc.length() > 1)
							{
//		std::string sTempDbgCopy = boost::str( boost::format( "sProjPathFile = %s\niProjOutPathLen = %d   iProjOutFileExtLen = %d   sOutFileOnly = %s\nsCSESrcBase = %s\nsCSESrc = %s\nsFileToWrite = %s" )
//										% sProjPathFile % iProjOutPathLen % iProjOutFileExtLen % sOutFileOnly % sCSESrcBase % sCSESrc % sFileToWrite );
//		::MessageBox( hWnd, sTempDbgCopy.c_str(), "CSE Copying info", MB_ICONSTOP );
								if (boost::iequals( sCSESrc.c_str(), sFileToWrite.c_str() ))   // only copy IN to OUT file if they are different
								{	// no problem - simply do nothing
								}
								else if (!FileExists( sCSESrc.c_str() ))
								{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
					// don't report missing CSE files - to be expected
					//				sLogMsg = boost::str( boost::format( "Unable to find CSE file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sCSESrc );
					//				BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
								else
								{	std::string sOverwriteCSEMsg = boost::str( boost::format( "The CSE file '%s' is opened in another application.  This file must be closed in that "
																				"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
																				"(once the file is closed), or \n'Abort' to abort the batch processing." ) % sFileToWrite.c_str() );
									if (!OKToWriteOrDeleteFile( sFileToWrite.c_str(), sOverwriteCSEMsg.c_str(), bSilent ))
									{	if (bSilent)
                                 bAbort = true;
                              else 
                              {  sLogMsg = boost::str( boost::format( "Unable to overwrite CSE file (run %d, record %d).\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
										   if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
											   bAbort = true;
										   else
										   {	sLogMsg = boost::str( boost::format( "User chose not to overwrite CSE file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sFileToWrite.c_str() );
											   BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}  }
									}
									else if (!CopyFile( sCSESrc.c_str(), sFileToWrite.c_str(), FALSE ))
									{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
										sLogMsg = boost::str( boost::format( "Error encountered copying CSE file (run %d, record %d) from '%s' to '%s'" ) % (iRun+1) % iaBatchRecNums[iRun] % sCSESrc.c_str() % sFileToWrite.c_str() );
										BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
							}	}
					}	}

				// SAC 11/4/19 - moved summary results CSV record writing up FROM HERE to enable export of multiple records (results sets) per run
				//	if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
				//	...
				}
			}

			if (sErrMsg.size() > 0)
			{	BEMPX_WriteLogFile( sErrMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				if (pszErrorMsg && iErrorMsgLen > 0 && (int) sErrMsg.size() < (iErrorMsgLen - strlen( pszErrorMsg )))
				{	if (strlen( pszErrorMsg ) < 1)
						sprintf_s( pszErrorMsg, iErrorMsgLen, "%s", sErrMsg.c_str() );
					else
					{	strcat_s( pszErrorMsg, iErrorMsgLen, "\n" );
						strcat_s( pszErrorMsg, iErrorMsgLen, sErrMsg.c_str() );
					}
				}
			}

			if (bThisRunGood)
				iRunsGood++;
			else
				iRunsBad++;

		// clean up BEMProc & ruleset memory (SAC 10/4/16)
			BEMPX_CloseBEMProc( true /*bShuttingDown*/, false /*bCloseLogFile*/ );
			// BEMPX_DeleteAllObjects( -1 /*iOnlyTypeToDelete*/, FALSE /*bReInitSymbols*/ );  - doesn't free up ruleset data...
			// BEMPX_CloseBEMProc();  - would also close log file, which I don't think we want
			// CMX_ExitBEMCmpMgrDLL();  - no need to free QApp ??

		}	// end of loop over batch of runs

						si1ProgressRunNum = 1;		// SAC 5/28/15
						siNumProgressRuns = 1;
	}

	if (iMode < 0)
	{	iRetVal = iMode;
		if (sErrMsg.size() > 0)
		{	BEMPX_WriteLogFile( sErrMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (pszErrorMsg && iErrorMsgLen > 0 && (int) sErrMsg.size() < iErrorMsgLen)
				sprintf_s( pszErrorMsg, iErrorMsgLen, "%s", sErrMsg.c_str() );
		}
	}

	sLogMsg = boost::str( boost::format( "Batch processing concluded - %d successful / %d errors/aborts / return value: %d" ) % iRunsGood % iRunsBad % iRetVal );
	if (pszResultMsg && iResultMsgLen > 0)
		sprintf_s( pszResultMsg, iResultMsgLen, "%d runs successful / %d errors/aborts", iRunsGood, iRunsBad );
	BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// routine to generate CSV (or other textual) reports via rule evaluation
// return:  >= 0 : successful, # of model reports written
//				<  0 : error code
int ProcessModelReports( const char* pszModelPathFile, long lDBID_ReportType, long lDBID_ReportFileAppend, int iObjIdx, bool /*bProcessCurrentSelection*/,
									QVector<QString>& saModelReportOptions, bool bVerbose, bool bSilent )
{
	int iRetVal = 0, iCurrentSelStatus = 0, iSpecialVal, iError;
	QString sCurrentSelection = BEMPX_GetStringAndStatus( lDBID_ReportType, iCurrentSelStatus, iSpecialVal, iError, 
		                                                   iObjIdx, BEMO_User, -1 /*iBEMProcIdx*/, FALSE /*AddCommas*/ );

	QString sLogMsg, sRptPathFileBase = pszModelPathFile;
	if (sRptPathFileBase.lastIndexOf('.') > 0)
		sRptPathFileBase = sRptPathFileBase.left( sRptPathFileBase.lastIndexOf('.') );

	//int iRptsWritten = 0;
	QVector<int> iaRptRetVals;
	BOOL bCurSelValid = (!sCurrentSelection.isEmpty() && iCurrentSelStatus > 0);
	int iMaxRptIdx = saModelReportOptions.size() - (bCurSelValid ? 0 : 1);  // +1 for current selection
	for (int iRpt=1; iRpt <= iMaxRptIdx; iRpt++)		// revised loop start from 0->1 to skip 'None' (blank) CSV output - SAC 4/8/20
	{	QString sRpt;
		if (iRpt == saModelReportOptions.size())
			sRpt = sCurrentSelection;
		else
		{	sRpt = saModelReportOptions[iRpt];
			if (bCurSelValid && !sCurrentSelection.compare( sRpt ))
				iMaxRptIdx--;  // if got here and report being processed same as current selection, then avoid writing it twice (now and at end of looping)
		}

		if (!sRpt.isEmpty() && sRpt.compare("None", Qt::CaseInsensitive))		// prevent output of 'None' report - SAC 4/8/20
		{	int iThisRptRetVal = 0;
			if (BEMPX_SetBEMData( lDBID_ReportType, BEMP_QStr, (void*) &sRpt, BEMO_User, iObjIdx ) < 0)
				iThisRptRetVal = -1;
			else
			{	long lRptEnumVal;
				QString sRptFileAppend;
				if (!BEMPX_GetInteger( lDBID_ReportType, lRptEnumVal, 0, -1, iObjIdx ))
					iThisRptRetVal = -2;
				else if (BEMPX_SetBEMData( lDBID_ReportFileAppend, BEMP_Int, (void*) &lRptEnumVal, BEMO_User, iObjIdx ) < 0)
					iThisRptRetVal = -3;
				else if (!BEMPX_GetString( lDBID_ReportFileAppend, sRptFileAppend, FALSE, 0, -1, iObjIdx ) || sRptFileAppend.isEmpty())
					iThisRptRetVal = -4;
				else
				{	QString sRptPathFile = sRptPathFileBase + sRptFileAppend;
							if (bVerbose)
								BEMPX_WriteLogFile( QString::asprintf( "      about to generate '%s' model report:  %s", sRpt.toLocal8Bit().constData(), sRptPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  // DEBUGGING
                  //	BEMPX_WriteLogFile( QString::asprintf( "      about to generate '%s' model report #%d:  %s", sRpt.toLocal8Bit().constData(), iRpt, sRptPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					int iRptRetVal = Local_GenerateRulesetModelReport( sRptPathFile, "rl_REPORT", bVerbose, bSilent );
					if (iRptRetVal > 0)
					{	BEMPX_WriteLogFile( QString::asprintf( "Error:  Model report generation failed w/ error code %d - report: '%s' - file: '%s'", iRptRetVal, sRpt.toLocal8Bit().constData(), sRptPathFile.toLocal8Bit().constData() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						iThisRptRetVal = -5;
					}
					else
						iThisRptRetVal = 1;
				}
			}
			iaRptRetVals.push_back( iThisRptRetVal );
			if (iRetVal >= 0)
			{	if (iThisRptRetVal < 0)
					iRetVal  = iThisRptRetVal;
				else
					iRetVal += iThisRptRetVal;
			}
		}
	}

	// restore initial selection
	if (!bCurSelValid)
		BEMPX_DefaultProperty( lDBID_ReportType, iError );
	else
		BEMPX_SetBEMData( lDBID_ReportType, BEMP_QStr, (void*) &sCurrentSelection,
											BEMO_User, iObjIdx, (BEM_PropertyStatus) iCurrentSelStatus );

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

int CMX_SetupAnalysisWeatherPaths( const char* pszWthrPath, bool bAnnual, bool bDDY, QString& sErrMsg, bool bAllowWthrDownload /*=false*/,
												const char* pszProxyAddress /*=NULL*/, const char* pszProxyCredentials /*=NULL*/, const char* pszProxyType /*=NULL*/ )
{	QString sWthrPath = pszWthrPath;
	int iRetVal = 0;
//   QString sWthrPath = ReadProgString( "paths", "WeatherPath", "EPW\\", TRUE );
	QString sWeatherStation;
	long lDBID_Proj_WeatherStation    = BEMPX_GetDatabaseID( "Proj:WeatherStation" );
	long lDBID_Proj_AnnualWeatherFile = BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile" );
	long lDBID_Proj_DDWeatherFile     = BEMPX_GetDatabaseID( "Proj:DDWeatherFile" );
	if (lDBID_Proj_WeatherStation < BEM_COMP_MULT || lDBID_Proj_AnnualWeatherFile < BEM_COMP_MULT || lDBID_Proj_DDWeatherFile < BEM_COMP_MULT)
	{	iRetVal = 1;
		sErrMsg = "CMX_SetupAnalysisWeatherPaths() Error:  One or more invalid database IDs";
	}
	else
	{	QString sTmpAnnWthr, sTmpDDY;   bool bWthrOverride=false;
	   BEMPX_GetString( lDBID_Proj_AnnualWeatherFile, sTmpAnnWthr );
	   BEMPX_GetString( lDBID_Proj_DDWeatherFile    , sTmpDDY );
      QString sWeatherStationFileBase, sWeatherLocationDDYFile;   long lGenerateWeatherLocationDDY=0;     // SAC 09/06/22
      BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:WeatherStationFileBase" ), sWeatherStationFileBase );
      BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:WeatherLocationDDYFile" ), sWeatherLocationDDYFile );
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:GenerateWeatherLocationDDY" ), lGenerateWeatherLocationDDY );
	   if (!sTmpAnnWthr.isEmpty() && sTmpDDY.isEmpty() && sTmpAnnWthr.indexOf('/') < 0 && sTmpAnnWthr.indexOf('\\') < 0)
		{	sWeatherStation = sTmpAnnWthr;	// SAC 2/1/20 - use AnnualWeatherFile as basis of annual & DDY sim weather files
			bWthrOverride = true;
		}
		else
		{  if (!sWeatherStationFileBase.isEmpty())         // SAC 09/06/22
            sWeatherStation = sWeatherStationFileBase;
         else
            BEMPX_GetString( lDBID_Proj_WeatherStation, sWeatherStation );
      }
		if (!DirectoryExists( sWthrPath ))
		{	iRetVal = 2;
			sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Path containing weather files not found:  '%s'", sWthrPath.toLocal8Bit().constData() );
		}
		else if (sWeatherStation.isEmpty())
		{	iRetVal = 3;
			sErrMsg = "CMX_SetupAnalysisWeatherPaths() Error:  Project's WeatherStation property not defined.";
		}
		else
		{	QString sDDWeatherFile, sAnnualWeatherFile, sWeatherFileAppend, sWeatherFileDownloadURL;
	//		sAnnualWeatherFile = sWthrPath + sWeatherStation + "_CZ2010.epw";
	//		sDDWeatherFile     = sWthrPath + sWeatherStation + "_CZ2010.ddy";
			long lDBID_Proj_WeatherFileAppend = BEMPX_GetDatabaseID( "Proj:WeatherFileAppend" );		// SAC 9/15/14 - mods to allow wthr file names to vary based on rules (for S901G)
			if (bWthrOverride)
			{	// no appending to wthr file if supplied via input AnnualWeatherFile
			}
			else if (lDBID_Proj_WeatherFileAppend > 0)
			   BEMPX_GetString( lDBID_Proj_WeatherFileAppend, sWeatherFileAppend );
			else if (sWeatherStationFileBase.isEmpty())     // only append the generic "_CZ2010" if sWeatherStationFileBase not specified - SAC 09/06/22
				sWeatherFileAppend = "_CZ2010";
			sAnnualWeatherFile = sWthrPath + sWeatherStation + sWeatherFileAppend + ".epw";
         if (lGenerateWeatherLocationDDY > 0 && !sWeatherLocationDDYFile.isEmpty())       // SAC 09/06/22
            sDDWeatherFile  = sWeatherLocationDDYFile;
         else
			   sDDWeatherFile  = sWthrPath + sWeatherStation + sWeatherFileAppend + ".ddy";

			long lDBID_Proj_WeatherFileDownloadURL = BEMPX_GetDatabaseID( "Proj:WeatherFileDownloadURL" );		// SAC 9/15/14 - mods to enable internet download of wthr files (for S901G)
			if ( ( (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() )) || (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() )) ) && lDBID_Proj_WeatherFileDownloadURL && bAllowWthrDownload &&
				  BEMPX_GetString( lDBID_Proj_WeatherFileDownloadURL, sWeatherFileDownloadURL ) && !sWeatherFileDownloadURL.isEmpty() )
			{	// attempt to download weather file(s) needed for simulation
#ifndef CM_QTGUI
				iRetVal = 11;
				sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download not implemented when Qt GUI libraries not loaded:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );
				pszProxyAddress;		pszProxyCredentials;		pszProxyType;		// reference args not used in this mode to avoid compiler warnings
//#else
//#ifndef OSWRAPPER
//				iRetVal = 12;
//				sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download not implemented when OpenStudio not loaded:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );
//				pszProxyAddress;		pszProxyCredentials;		pszProxyType;		// reference args not used in this mode to avoid compiler warnings
#else
				QString sWthrZipPathFile = sWthrPath + sWeatherStation + sWeatherFileAppend + ".zip";
				QString sAnnualWeatherFileAlone =      sWeatherStation + sWeatherFileAppend + ".epw";
				QString sDDWeatherFileAlone     =      sWeatherStation + sWeatherFileAppend + ".ddy";
			// FIRST check for presence of ZIP file, and if it is present try just unzipping first - if not, store downloaded zip to DIFFERENT name
				if (FileExists( sWthrZipPathFile.toLocal8Bit().constData() ))
				{	// zip file already exists, so see about unzipping what we need from it
					if (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ))
						OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(), sAnnualWeatherFileAlone.toLocal8Bit().constData(), sWthrPath.toLocal8Bit().constData() );
					if (bDDY    && !FileExists( sDDWeatherFile.toLocal8Bit().constData()     ))
						OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(), sDDWeatherFileAlone.toLocal8Bit().constData()    , sWthrPath.toLocal8Bit().constData() );
				}
			// then download zip file if still missing epw or ddy
				if ( (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() )) || (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() )) )
				{	int iDnldRetVal = surlFile.DownloadFile( sWeatherFileDownloadURL.toLocal8Bit().constData() /*const char* pszUrl*/, sWthrZipPathFile.toLocal8Bit().constData(),
																			NULL, pszProxyAddress, pszProxyCredentials, pszProxyType );
					if (iDnldRetVal > 0)
					{	iRetVal = 14 + iDnldRetVal;
						switch (iDnldRetVal)
						{	case  1 :	sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - invalid storage path:  %s", sWthrZipPathFile.toLocal8Bit().constData() );					break;
							case  2 :	sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - error downloading file:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );			break;		// this error occurs when NORESCO proxy not able to be negotiated
							case  3 :	sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - user chose not to overwrite file:  %s  -->>  %s", sWeatherFileDownloadURL.toLocal8Bit().constData(), sWthrZipPathFile.toLocal8Bit().constData() );		break;
							default :	sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed:  %s  -->>  %s", sWeatherFileDownloadURL.toLocal8Bit().constData(), sWthrZipPathFile.toLocal8Bit().constData() );	break;
					}	}
					else if (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ) && !OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(),
																																				sAnnualWeatherFileAlone.toLocal8Bit().constData(), sWthrPath.toLocal8Bit().constData() ))
					{	iRetVal = 13;
						sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Unable to extract hourly simulation weather file from download:  %s  -->>  %s/%s", sWeatherFileDownloadURL.toLocal8Bit().constData(), 
															sWthrZipPathFile.toLocal8Bit().constData(), sAnnualWeatherFileAlone.toLocal8Bit().constData() );
					}
					else if (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() ) && !OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(),
																																				sDDWeatherFileAlone.toLocal8Bit().constData(), sWthrPath.toLocal8Bit().constData() ))
					{	iRetVal = 14;
						sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Unable to extract design day simulation weather file from download:  %s  -->>  %s/%s", sWeatherFileDownloadURL.toLocal8Bit().constData(), 
															sWthrZipPathFile.toLocal8Bit().constData(), sDDWeatherFileAlone.toLocal8Bit().constData() );
				}	}
#endif
			}

			if (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ))
			{	iRetVal = (iRetVal < 1 ? 4 : iRetVal);
				if (sErrMsg.isEmpty())
					sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file not found:  '%s'", sAnnualWeatherFile.toLocal8Bit().constData() );
			}
			else if (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() ))
			{	iRetVal = (iRetVal < 1 ? 5 : iRetVal);
				if (sErrMsg.isEmpty())
					sErrMsg = QString::asprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Design day simulation file not found:  '%s'", sDDWeatherFile.toLocal8Bit().constData() );
			}
		//	else		- modified to set wthr filename regardless of success or file presence
		//	{
				if (bAnnual)
				{	sAnnualWeatherFile.replace( '\\', '/' );  // replace backslashes w/ slashes to provide more universal compatibility
			      BEMPX_SetBEMData( lDBID_Proj_AnnualWeatherFile, BEMP_QStr, (void*) &sAnnualWeatherFile );
               long lDBID_Proj_AnnualWeatherFileNoPath = BEMPX_GetDatabaseID( "Proj:AnnualWeatherFileNoPath" );   // added to facilitate NRCC-PRF XML reporting - SAC 04/13/21
               if (lDBID_Proj_AnnualWeatherFileNoPath > 0)
               {  int iLastSlashIdx = sAnnualWeatherFile.lastIndexOf('/');
                  if (iLastSlashIdx > 0)
                     sAnnualWeatherFile = sAnnualWeatherFile.right( sAnnualWeatherFile.length()-iLastSlashIdx-1 );
   			      BEMPX_SetBEMData( lDBID_Proj_AnnualWeatherFileNoPath, BEMP_QStr, (void*) &sAnnualWeatherFile );

                  // code to also set ResProj:WeatherFileName - needed for batch processing to work properly - SAC 11/01/21 (MFam)
                  long lDBID_ResProj_WeatherFileName = BEMPX_GetDatabaseID( "ResProj:WeatherFileName" );
                  if (lDBID_ResProj_WeatherFileName > 0)  // regardless of presence of ResProj...
      			      BEMPX_SetBEMData( lDBID_ResProj_WeatherFileName, BEMP_QStr, (void*) &sAnnualWeatherFile );
				}  }
				if (bDDY)
				{	sDDWeatherFile.replace( '\\', '/' );  // replace backslashes w/ slashes to provide more universal compatibility
			      BEMPX_SetBEMData( lDBID_Proj_DDWeatherFile, BEMP_QStr, (void*) &sDDWeatherFile );
				}
		//	}
		}
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

int WriteCSVHourlyResultsHeader( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, int iCodeType /*=0*/,
														bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/, const char* pszEPlusVerStr /*=NULL*/,
														const char* pszOpenStudioVerStr /*=NULL*/, QString& sErrMsg, const char* pszFileDescrip )
{	int iRetVal = 0;
	double fCondFloorArea=0.0, fNonresFlrArea=0.0, fResFlrArea=0.0;
   long lEngyCodeYearNum=0, lHotelMotelGuestRmCnt=0, lResLivingUnitCnt=0;
   bool bEchoNResData = true, bEchoResData = false;  // SAC 07/19/22
   QString sRunTitle;
	if (!BEMPX_GetFloat(	 BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), fCondFloorArea  ,       0, -1, 0, BEMO_User,          iBEMProcIdx ))
   {  iRetVal = 1;
		sErrMsg = "Error retrieving Proj:AnalysisType, CliZnNum, WeatherStation and/or Bldg:TotCondFlrArea";
   }
   else
	{  BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:RunTitle"        ), sRunTitle );
      BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:NonResFlrArea"   ), fNonresFlrArea  , 0, -1, 0, BEMO_User, iBEMProcIdx );
      BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:ResFlrArea"      ), fResFlrArea     , 0, -1, 0, BEMO_User, iBEMProcIdx );
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" ), lEngyCodeYearNum, 0, -1, 0, BEMO_User, iBEMProcIdx );
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "Bldg:HotelMotelGuestRmCnt" ), lHotelMotelGuestRmCnt, 0, -1, 0, BEMO_User, iBEMProcIdx );    // SAC 09/22/23
      BEMPX_GetInteger( BEMPX_GetDatabaseID( "Bldg:ResLivingUnitCnt"     ), lResLivingUnitCnt,     0, -1, 0, BEMO_User, iBEMProcIdx );

      bEchoNResData = (fNonresFlrArea > 1 || lHotelMotelGuestRmCnt > 0);   // SAC 07/19/22   // ensure all hotel/motel also echos E+ results - SAC 09/22/23
      bEchoResData  = (fResFlrArea    > 1 && lResLivingUnitCnt > 0);       // prevent listing Res enduses when no dwellings present - SAC 09/22/23

		QString sOverwriteMsg;
		sOverwriteMsg = QString::asprintf(	"The hourly CSV results file '%s' is opened in another application.  This file must be closed in that "
										"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
										"(once the file is closed), or \n'Abort' to abort the hourly export.", pszHourlyResultsPathFile );
		if (!OKToWriteOrDeleteFile( pszHourlyResultsPathFile, sOverwriteMsg, bSilent ))
		{	iRetVal = 2;
			sErrMsg = QString::asprintf( "Unable to open and/or write hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
   }

   if (iRetVal == 0)
   {  long lRunDate = 0;
	   QString timeStamp;
	   //CTime locTime = CTime::GetCurrentTime();
		if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lRunDate > 0)
	   {	//CTime locTime = lRunDate;
	   	QDateTime locTime = QDateTime::currentDateTime();
			timeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");
		}
		else
			timeStamp = "<unknown analysis day/time>";

		QString sUIVer, sCmpMgrVer, sOSVer, sEPlusVer, sCSEVer, sRuleVer;
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"    ),	sUIVer   );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ),	sCmpMgrVer );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:DHWSimEngVersion"   ),	sCSEVer );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Ruleset"            ),	sRuleVer );
		if (pszEPlusVerStr && strlen( pszEPlusVerStr ) > 0)
			sEPlusVer = pszEPlusVerStr;
		else
			sEPlusVer = (bEchoResData && !bEchoNResData) ? "n/a" : "???";     // SAC 07/19/22
		if (pszOpenStudioVerStr && strlen( pszOpenStudioVerStr ) > 0)
			sOSVer = pszOpenStudioVerStr;
		else
			sOSVer = (bEchoResData && !bEchoNResData) ? "n/a" : "???";     // SAC 07/19/22
		QString qsCSEName;	// SAC 12/17/17
		if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CSENme"  ),	qsCSEName  ))
			qsCSEName = "CSE";

   	FILE *fp_CSV;
		int iErrorCode;
		try
		{
//			BEMPX_WriteHourlyResultsSummary( pszHourlyResultsPathFile, bSilent, iBEMProcIdx );
			iErrorCode = fopen_s( &fp_CSV, pszHourlyResultsPathFile, "wb" );
			if (iErrorCode != 0 || fp_CSV == NULL)
			{	iRetVal = 3;
				sErrMsg = QString::asprintf( "Error encountered opening hourly CSV results file:  %s", pszHourlyResultsPathFile );
			}
			else
			{  int iFirstDataRow = (lEngyCodeYearNum >= 2022 ? 19 : 18);
            int iFirstDataCol = (lEngyCodeYearNum >= 2022 ?  5 :  4);      // insert DST column (#4) - SAC 11/11/22
            fprintf( fp_CSV, "%d,%d,\"Row/Col hourly results data begin\"\n", iFirstDataRow, iFirstDataCol );
				fprintf( fp_CSV, "\"%s\"\n", pszFileDescrip );
				fprintf( fp_CSV, ",Software:,,\"%s\"\n",   sUIVer.toLocal8Bit().constData()     );
				fprintf( fp_CSV, ",CompMgr:,,\"%s\"\n",    sCmpMgrVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",OpenStudio:,,\"%s\"\n", sOSVer.toLocal8Bit().constData()     );
				fprintf( fp_CSV, ",EnergyPlus:,,\"%s\"\n", sEPlusVer.toLocal8Bit().constData()  );
				fprintf( fp_CSV, ",%s:,,\"%s\"\n",         qsCSEName.toLocal8Bit().constData(), sCSEVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",Ruleset:,,\"%s\"\n",    sRuleVer.toLocal8Bit().constData()   );

				fprintf( fp_CSV,     "Run Title:,,,\"%s\"\n", sRunTitle.toLocal8Bit().constData()  );
				fprintf( fp_CSV, "Run Date/Time:,,,\"%s\"\n", timeStamp.toLocal8Bit().constData()  );
            if (lEngyCodeYearNum >= 2022)    // SAC 11/01/21 (MFam)
   			{	fprintf( fp_CSV,      "NonRes Cond. Area:,,,%.0f\n",   fNonresFlrArea  );
   				fprintf( fp_CSV, "Residential Cond. Area:,,,%.0f\n",   fResFlrArea     );
            } else
   				fprintf( fp_CSV,    "Cond. Area:,,,%.0f\n",   fCondFloorArea   );

				fprintf( fp_CSV,         "Model:,,,\"%s\"\n", pszModelName     );
		//		fprintf( fp_CSV,  "Fuel TDV Set:,,,\"%s\"\n", sFuelTDVLabel    );
				fprintf( fp_CSV,    "Model File:,,,\"%s\"\n", pszModelPathFile );
				fprintf( fp_CSV, "\n" );

				fflush( fp_CSV );
				fclose( fp_CSV );
			}
		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... ) {
			iRetVal = 4;
			sErrMsg = QString::asprintf( "Unknown error writing hourly CSV results file header:  %s", pszHourlyResultsPathFile );
			// if (!bSilent)
			// 	BEMMessageBox( "Unknown error writing hourly CSV results file." );
		}
	}
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

int CMX_ExportCSVHourlyResults_CECNonRes( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, char* pszErrMsgBuffer /*=NULL*/,
														int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/, const char* pszEPlusVerStr /*=NULL*/,
														const char* pszOpenStudioVerStr /*=NULL*/ )
{	return CMX_ExportCSVHourlyResults_Com( pszHourlyResultsPathFile, pszModelPathFile, pszModelName, CT_T24N, pszErrMsgBuffer, iErrMsgBufferLen, bSilent, iBEMProcIdx, pszEPlusVerStr, pszOpenStudioVerStr );
}
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error retrieving Proj:AnalysisType, CliZnNum, WeatherStation and/or Bldg:TotCondFlrArea
//											 2 : Unable to open and/or write hourly CSV results file
//											 3 : Error encountered opening hourly CSV results file
//											 4 : Unknown error writing hourly CSV results file
//											 5 : Unexpected enduse count or index
//											 6 : RunPeriodYear (####) not compatible w/ daylight savings time labels (expecting 2009)
//                                7 : 
int CMX_ExportCSVHourlyResults_Com( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, int iCodeType /*=0*/, char* pszErrMsgBuffer /*=NULL*/,
														int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/, const char* pszEPlusVerStr /*=NULL*/,
														const char* pszOpenStudioVerStr /*=NULL*/ )
{	int iRetVal = 0;
	QString sErrMsg;
	long lCliZnNum=0, lEngyCodeYearNum=0;
	QString sAnalysisType, sWeatherStation;
	BOOL bExpectStdDesResults = TRUE;
	if (	!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), sAnalysisType   , TRUE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CliZnNum"        ), lCliZnNum       ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) ||
			!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:WeatherStation"  ), sWeatherStation , TRUE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) ||
         !BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" ), lEngyCodeYearNum,       0, -1, 0, BEMO_User,          iBEMProcIdx ) )
	{	iRetVal = 1;
		sErrMsg = "Error retrieving Proj:AnalysisType, CliZnNum, WeatherStation and/or EngyCodeYearNum";
	}
	else if (NUM_T24_NRES_EndUses_19 != 15 || IDX_T24_NRES_EU_Total != 14)	// SAC 2/1/17 - added error check to prevent bomb below  // SAC 7/15/18 - updated expected total to 15 (for PV & Batt)
	{	iRetVal = 5;
		sErrMsg = QString("Unexpected enduse count (%1) or total index (%2) (expecting 15 and 14 respectively)").arg(QString::number(NUM_T24_NRES_EndUses_19), QString::number(IDX_T24_NRES_EU_Total));
	}
	else
	{	bExpectStdDesResults = (sAnalysisType.indexOf( "Compl" ) >= 0);
		//BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:FuelTDVLabel" ), sFuelTDVLabel );
	}

	long lRunPeriodYear;    // insert DST column (#4) - SAC 11/11/22
   int iDST_StMo=-1, iDST_StDa=-1, iDST_EndMo=-1, iDST_EndDa=-1;
   QString sTimeType = "Std";
	if ( lEngyCodeYearNum >= 2022 && BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunPeriodYear" ), lRunPeriodYear ) && lRunPeriodYear > 0 )
   {  long lDisableDayltSavTimeSim=0;
      if ( BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:DisableDayltSavTimeSim" ), lDisableDayltSavTimeSim ) && lDisableDayltSavTimeSim > 0 )
      {  // do nothing - input property specifies NO DST simulation
      }
      else
      {  if (lRunPeriodYear == 2009)
         {  sTimeType = "DST";
            iDST_StMo  =  3;    iDST_StDa  = 8;
            iDST_EndMo = 11;    iDST_EndDa = 1;
         }
         else
         {	iRetVal = 6;
      		sErrMsg = QString("RunPeriodYear (%1) not compatible w/ daylight savings time labels (expecting 2009)").arg(QString::number(lRunPeriodYear));
   }  }  }

	if (iRetVal==0)
      iRetVal = WriteCSVHourlyResultsHeader( pszHourlyResultsPathFile, pszModelPathFile, pszModelName, iCodeType, bSilent, iBEMProcIdx,
														   pszEPlusVerStr, pszOpenStudioVerStr, sErrMsg, "Hourly Results of CEC Compliance Manager" );

	if (iRetVal==0)
	{
   	FILE *fp_CSV;
		int iErrorCode;
		try
		{
//			BEMPX_WriteHourlyResultsSummary( pszHourlyResultsPathFile, bSilent, iBEMProcIdx );
			iErrorCode = fopen_s( &fp_CSV, pszHourlyResultsPathFile, "ab" );   // APPEND to header already written to file via WriteCSVHourlyResultsHeader() - SAC 10/03/21
			if (iErrorCode != 0 || fp_CSV == NULL)
			{	iRetVal = 3;
				sErrMsg = QString::asprintf( "Error encountered opening hourly CSV results file:  %s", pszHourlyResultsPathFile );
			}
			else
			{
      	   double fNonresFlrArea=0.0, fResFlrArea=0.0;     // SAC 11/01/21 (MFam)
            long lHotelMotelGuestRmCnt=0, lResLivingUnitCnt=0;
            BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:NonResFlrArea"   ), fNonresFlrArea  , 0, -1, 0, BEMO_User, iBEMProcIdx );
            BEMPX_GetFloat(   BEMPX_GetDatabaseID( "Bldg:ResFlrArea"      ), fResFlrArea     , 0, -1, 0, BEMO_User, iBEMProcIdx );
            BEMPX_GetInteger( BEMPX_GetDatabaseID( "Bldg:HotelMotelGuestRmCnt" ), lHotelMotelGuestRmCnt, 0, -1, 0, BEMO_User, iBEMProcIdx );    // SAC 09/22/23
            BEMPX_GetInteger( BEMPX_GetDatabaseID( "Bldg:ResLivingUnitCnt"     ), lResLivingUnitCnt,     0, -1, 0, BEMO_User, iBEMProcIdx );
            bool bEchoNResData = (fNonresFlrArea > 1 || lHotelMotelGuestRmCnt > 0);    // ensure all hotel/motel also echos E+ results - SAC 09/22/23
            bool bEchoResData  = (fResFlrArea    > 1 && lResLivingUnitCnt > 0);        // prevent listing Res enduses when no dwellings are present - SAC 09/22/23
      		long lEngyCodeYearNum = 2016;	// SAC 3/11/20 - added to ensure correct TDV column indices (changed in 2022)
      		long lDBID_Proj_EngyCodeYearNum = BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" );
      		if (lDBID_Proj_EngyCodeYearNum < BEM_COMP_MULT || !BEMPX_GetInteger( lDBID_Proj_EngyCodeYearNum, lEngyCodeYearNum, 0, -1, -1, BEMO_User, iBEMProcIdx ) || lEngyCodeYearNum < 1)
      			lEngyCodeYearNum = 2016;

      	   // ASSUMES:  NUM_T24_NRES_EndUses_19 = 15  -AND-  IDX_T24_NRES_EU_CompTot = 7  -AND-  IDX_T24_NRES_EU_Total = 14
      		int iEUO[2][NUM_T24_NRES_EndUses_19] = { { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 7, 14         },		// SAC 2/1/17 - updated to include Process Motors
      													   	  { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11,         7, 14, -1, -1 } };		// SAC 7/20/18 - divided into two sets - Elec vs. Other (in adding PV & Batt)		// SAC 9/15/19 - invalid EUs idxs to -1 (was trippling SpcHt results
      		int iNumEUs = NUM_T24_NRES_EndUses_19;
      		if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14   // SAC 7/15/18 - further revs to ignoree PV & Batt
      		{	iNumEUs = NUM_T24_NRES_EndUses_19-3;
      			iEUO[0][iNumEUs-1] = IDX_T24_NRES_EU_Total;		iEUO[0][iNumEUs] = 0;		// bypass reporting of CompTotal enduse
      			iEUO[1][iNumEUs-1] = IDX_T24_NRES_EU_Total;		iEUO[1][iNumEUs] = 0;		// bypass reporting of CompTotal enduse
      		}

            QString sTDV="TDV", sKTDV="kTDV";      // revise TDV labels to SLCC & $ for 2025+ code vintage - SAC 11/29/22
            BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), sTDV, FALSE, 0, -1, 0, BEMO_User, "TDV", 0, iBEMProcIdx );   // base metric label on new ruleset var - SAC 01/26/23
            if (lEngyCodeYearNum >= 2025)
            {  /*sTDV="SLCC";*/   sKTDV="$";
            }

				if (iCodeType == CT_T24N)		// SAC 10/7/14
				{  if (lEngyCodeYearNum >= 2022 && (!bEchoNResData || !bEchoResData))
               {  // move PV & Battery out to right - no other changes
                  // inserted columns for source energy, CO2 emissions and elec demand multipliers for 2022.3.0-SP2 - SAC 01/18/24 (tic #3421)
                  fprintf( fp_CSV,  ",,,,Site Electric Use,,,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,,,Site Propane Use,,,,,,,,,,,,,%s Multipliers,,,Source Energy Multipliers,,,CO2 Emissions Multipliers,,,Elec Demand,Building Wide,\n", sTDV.toLocal8Bit().constData() );
      	         fprintf( fp_CSV,  ",,,Local Time,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,,%s,%s\n",
   												esEUMap_CECNonRes[iEUO[0][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][10]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[0][13]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][14]].sEnduseAbbrev,  
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
                                       esEUMap_CECNonRes[iEUO[0][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][12]].sEnduseAbbrev );   // moved PV & Battery to very end, after TDV
   	            fprintf( fp_CSV,  "Mo,Da,Hr,(%s),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
                                             "(%s/kWh),(%s/MBtu),(%s/MBtu),(kBtu/kWh),(kBtu/therm),(kBtu/therm),(tonnes CO2-e/kWh),(tonnes CO2-e/therm),(tonnes CO2-e/therm),(frac),(kWh),(kWh)\n", sTimeType.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData() );
               }
               else if (lEngyCodeYearNum >= 2022)
               {  // move PV & Battery out to right, add separate col of TDV mults (for PV & Batt), and then write a complete set of more column headers for Res data
                  // inserted columns for source energy, CO2 emissions and elec demand multipliers for 2022.3.0-SP2 - SAC 01/18/24 (tic #3421)
                  fprintf( fp_CSV,  ",,,,Nonres Site Electric Use,,,,,,,,,,,,,Nonres Site Natural Gas Use,,,,,,,,,,,,,Nonres Site Propane Use,,,,,,,,,,,,,Nonres %s Multipliers,,,Nonres Source Energy Multipliers,,,Nonres CO2 Emissions Multipliers,,,Nonres Elec Demand,Building Wide,,PV/Batt Mults (Res/NRes area weighted avg),,,,Residential Site Electric Use,,,,,,,,,,,,,Residential Site Natural Gas Use,,,,,,,,,,,,,Residential Site Propane Use,,,,,,,,,,,,,Res %s Multipliers,,,Res Source Energy Multipliers,,,Res CO2 Emissions Multipliers,,,Res Elec Demand,\n",
                                       sTDV.toLocal8Bit().constData(), sTDV.toLocal8Bit().constData() );
      	         fprintf( fp_CSV,  ",,,Local Time,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,,%s,%s,%s,Source Energy,CO2 Emis,Elec Demand,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,Electric,NatGas,OtherFuel,\n",
   												esEUMap_CECNonRes[iEUO[0][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][10]].sEnduseAbbrev,	esEUMap_CECNonRes[iEUO[0][13]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][14]].sEnduseAbbrev,  
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
                                       esEUMap_CECNonRes[iEUO[0][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][12]].sEnduseAbbrev, sTDV.toLocal8Bit().constData(),     // moved PV & Battery to follow nonres TDV
   												esEUMap_CECNonRes[iEUO[0][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 3]].sEnduseAbbrev,   // added entirely new set of columns for RES results
   												esEUMap_CECNonRes[iEUO[0][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][13]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][14]].sEnduseAbbrev,  
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev );
   	            fprintf( fp_CSV,  "Mo,Da,Hr,(%s),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
                                             "(%s/kWh),(%s/MBtu),(%s/MBtu),(kBtu/kWh),(kBtu/therm),(kBtu/therm),(tonnes CO2-e/kWh),(tonnes CO2-e/therm),(tonnes CO2-e/therm),(frac),(kWh),(kWh),(%s/kWh),(kBtu/kWh),(tonnes CO2-e/kWh),(frac),"
                                             "(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"
                                             "(%s/kWh),(%s/MBtu),(%s/MBtu),(kBtu/kWh),(kBtu/therm),(kBtu/therm),(tonnes CO2-e/kWh),(tonnes CO2-e/therm),(tonnes CO2-e/therm),(frac),\n", sTimeType.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(),
                                       sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData(), sKTDV.toLocal8Bit().constData() );
               }
               else
               {  fprintf( fp_CSV,  ",,,Site Electric Use,,,,,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,,,Site Propane Use,,,,,,,,,,,,,TDV Multipliers,\n" );		// SAC 10/28/15 - 'Other Fuel' -> 'Propane'
      	         fprintf( fp_CSV,  ",,,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,Electric,NatGas,OtherFuel\n",
   												esEUMap_CECNonRes[iEUO[0][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[0][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][11]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[0][12]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][13]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][14]].sEnduseAbbrev,  // SAC 7/15/18 - added PV & Battery
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev,
   												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
   												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][12]].sEnduseAbbrev );
   	            fprintf( fp_CSV,  "Mo,Da,Hr,(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),"		// SAC 10/28/15 - 'therms' -> 'kBtu'
   														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kTDV/kWh),(kTDV/MBtu),(kTDV/MBtu)\n" );		// SAC 10/28/15 - 'therms' -> 'kBtu' and 'kTDV/thrm' -> 'kTDV/MBtu'
               }
				}
				else if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14
				{	fprintf( fp_CSV,  ",,,Site Electric Use,,,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,,,Site Other Fuel Use,\n" );
   	         fprintf( fp_CSV,  ",,,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
												esEUMap_CECNonRes[iEUO[0][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 3]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[0][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 7]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[0][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[0][11]].sEnduseAbbrev,
												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev,
												esEUMap_CECNonRes[iEUO[1][ 0]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 1]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 2]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 3]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[1][ 4]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 5]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 6]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 7]].sEnduseAbbrev, 
												esEUMap_CECNonRes[iEUO[1][ 8]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][ 9]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][10]].sEnduseAbbrev, esEUMap_CECNonRes[iEUO[1][11]].sEnduseAbbrev );
	            fprintf( fp_CSV,  "Mo,Da,Hr,(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),(kWh),"
														"(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),(Therms),"
														"(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu)\n" );		// SAC 10/28/15 - 'therms' -> 'kBtu' for Other Fuel use
				}

			   // SETUP hourly results arrays for export...
				int iYrHr=0;
				double daZero[8760];
				//double daMtrTotals[HrlyExport_CECNonRes_NumMeters][8760];
				for (; iYrHr<8760; iYrHr++)
					daZero[iYrHr] = 0.0;

				double *daMtrEUData[NUM_T24_NRES_Fuels][NUM_T24_NRES_EndUses_19], *daMtrEUResData[NUM_T24_NRES_Fuels][NUM_T24_NRES_EndUses_19];
				double *daMtrCTotData[NUM_T24_NRES_Fuels],    *daMtrTotData[NUM_T24_NRES_Fuels],       // switched from local 8760 arrays to malloc/free due to stack overflow - SAC 11/01/21
                   *daMtrCTotResData[NUM_T24_NRES_Fuels], *daMtrTotResData[NUM_T24_NRES_Fuels];
				int iMtr=0, iEU;
				for (; iMtr < NUM_T24_NRES_Fuels; iMtr++)
				{  daMtrCTotData[   iMtr] = (double*) malloc( sizeof(double) * 8760 );
				   daMtrTotData[    iMtr] = (double*) malloc( sizeof(double) * 8760 );
				   daMtrCTotResData[iMtr] = (double*) malloc( sizeof(double) * 8760 );
				   daMtrTotResData[ iMtr] = (double*) malloc( sizeof(double) * 8760 );
            	for (iYrHr=0; iYrHr<8760; iYrHr++)
					{	daMtrCTotData[iMtr][iYrHr] = 0.0;
						daMtrTotData[ iMtr][iYrHr] = 0.0;
                  daMtrCTotResData[iMtr][iYrHr] = 0.0;
						daMtrTotResData[ iMtr][iYrHr] = 0.0;
				}	}
				for (iMtr=0; iMtr < NUM_T24_NRES_Fuels; iMtr++)
				{	//	for (iYrHr=0; iYrHr<8760; iYrHr++)
					//		daMtrTotals[iMtr][iYrHr] = 0.0;
					int iEUOM = (iMtr==0 ? 0 : 1);
					int iEUCmpTot=-1, iEUTot=-1;	// SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
					{  if (iEUO[iEUOM][iEU] == IDX_T24_NRES_EU_CompTot)	
						{	iEUCmpTot = iEU;
							daMtrEUData[   iMtr][iEU] = &daMtrCTotData[iMtr][0];
							daMtrEUResData[iMtr][iEU] = &daMtrCTotResData[iMtr][0];
						}
                  else if (iEUO[iEUOM][iEU] == IDX_T24_NRES_EU_Total)
						{	iEUTot = iEU;
							daMtrEUData[   iMtr][iEU] = &daMtrTotData[iMtr][0];
							daMtrEUResData[iMtr][iEU] = &daMtrTotResData[iMtr][0];
						}
                  else
                  {  if (iEUO[iEUOM][iEU] < 0)  // removed: || !bEchoNResData) - to ensure EPlus ResCentral HVAC results get incorporated into Res hourly results - SAC 12/05/24 (gh support #83)
   							daMtrEUData[iMtr][iEU] = &daZero[0];   // EUs not to be reported - SAC 9/15/19
   						else if (BEMPX_GetHourlyResultArrayPtr( &daMtrEUData[iMtr][iEU], NULL, 0, pszModelName, pszaEPlusFuelNames[iMtr],
   	 																esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sEnduseName, iBEMProcIdx ) == 0 && daMtrEUData[iMtr][iEU] != NULL)
   						{	// OK - do nothing
   						}
   						else
   							daMtrEUData[iMtr][iEU] = &daZero[0];   // this combination of meter & enduse does not have results, so assign 8760 of zeroes

                     // retrieve Residential-only hourly results - SAC 11/01/21 (MFam)
                     // added logic to ensure that PV & Battery results retrieved for runs where bEchoResData=true & bEchoNResData=false - SAC 07/19/22
                     if (iEUO[iEUOM][iEU] < 0 || !bEchoResData || esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sResEnduseName == NULL ||
                         (bEchoNResData && strcmp( esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sEnduseName, esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sResEnduseName ) == 0))
   							daMtrEUResData[iMtr][iEU] = &daZero[0];  
   						else if (BEMPX_GetHourlyResultArrayPtr( &daMtrEUResData[iMtr][iEU], NULL, 0, pszModelName, pszaEPlusFuelNames[iMtr],
   	 																esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sResEnduseName, iBEMProcIdx ) == 0 && daMtrEUResData[iMtr][iEU] != NULL)
   						{	// res hourly results OK
                        if (!bEchoNResData && daMtrEUData[iMtr][iEU] != &daZero[0] &&     // if NOT echoing NRes data but we HAVE NRes hourly results (presumably from ResCentral HVAC), then sum those into the Res results - SAC 12/05/24 (gh support #83)
                            iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_PV && iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_BT)     // ignore PV & Batt here since they are duplicates of what is already retrieved for Res
                           for (iYrHr=0; iYrHr<8760; iYrHr++)
                              daMtrEUResData[iMtr][iEU][iYrHr] += daMtrEUData[iMtr][iEU][iYrHr];
   						}
   						else if (!bEchoNResData && daMtrEUData[iMtr][iEU] != &daZero[0] &&     // if no Res data And NOT echoing NRes data but we HAVE NRes hourly results (presumably from ResCentral HVAC), then use those as Res results - SAC 12/05/24 (gh support #83)
                              iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_PV && iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_BT)     // ignore PV & Batt here since they are duplicates of what is already retrieved for Res
                        daMtrEUResData[iMtr][iEU] = daMtrEUData[iMtr][iEU];
                     else 
   							daMtrEUResData[iMtr][iEU] = &daZero[0];   // this combination of meter & enduse does not have results, so assign 8760 of zeroes
               }  }
					// sum indiviudal enduse results into the CompTot & Tot enduses - SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
						if (iEU != iEUCmpTot && iEU != iEUTot && iEUO[iEUOM][iEU] >= 0 && 	// SAC 9/15/19
                      iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_PV && iEUO[iEUOM][iEU] != IDX_T24_NRES_EU_BT)  // remove PV & Battery from NRes/Res totals
						{	for (iYrHr=0; iYrHr<8760; iYrHr++)
							{	daMtrEUData[   iMtr][iEUTot][iYrHr] += daMtrEUData[iMtr][iEU][iYrHr];
                        daMtrEUResData[iMtr][iEUTot][iYrHr] += daMtrEUResData[iMtr][iEU][iYrHr];
                     }
							if (esEUMap_CECNonRes[iEUO[iEUOM][iEU]].iSumIntoCompliance)
							{	for (iYrHr=0; iYrHr<8760; iYrHr++)
								{	daMtrEUData[   iMtr][iEUCmpTot][iYrHr] += daMtrEUData[iMtr][iEU][iYrHr];
                           daMtrEUResData[iMtr][iEUCmpTot][iYrHr] += daMtrEUResData[iMtr][iEU][iYrHr];
						}	}  }
				}

				double dFUMlt = 100.0;		// SAC 10/28/15 - therms -> kBtu
				double dFTMlt =  10.0;		// SAC 10/28/15 - kTDV/therm -> kTDV/MBtu
				if (iCodeType == CT_T24N)		// SAC 10/7/14
				{
					long lPrimResultSetIdx = 1;	// SAC 3/11/20 - added to ensure main/primary result set TDV exported here
					long lDBID_Proj_PrimResultSetIdx = BEMPX_GetDatabaseID( "Proj:PrimResultSetIdx" );
					if (lDBID_Proj_PrimResultSetIdx < BEM_COMP_MULT || !BEMPX_GetInteger( lDBID_Proj_PrimResultSetIdx, lPrimResultSetIdx, 0, -1, -1, BEMO_User, iBEMProcIdx ) || lPrimResultSetIdx < 1)
						lPrimResultSetIdx = 1;
					QString sTDVMultTableName, sResTDVMultTableName;		// SAC 11/5/19
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVMultTableName" )+lPrimResultSetIdx-1, sTDVMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					if (sTDVMultTableName.isEmpty())
						sTDVMultTableName = "TDVbyCZandFuel";
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResTDVMultTableName" )+lPrimResultSetIdx-1, sResTDVMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    // SAC 11/01/21 (MFam)

					int iElecTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) + 0 + 2) : ((0 * 16) + lCliZnNum + 1) );	// SAC 3/11/20
					int iNGasTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) + 1 + 2) : ((1 * 16) + lCliZnNum + 1) );
					int iPropTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) + 2 + 2) : ((2 * 16) + lCliZnNum + 1) );

					//	int iFuelTDVCol = (lNatGasAvailable > 0 ? 2 : 3);
					//double daTDVMults[3][8760], daResTDVMults[3][8760];
               double *daTDVMults[3], *daResTDVMults[3];   // switched from stack to heap memory for 8760 multiplier arrays - SAC 01/19/24
                  daTDVMults[0]    = (double*) malloc( sizeof(double) * 8760 );   daTDVMults[1]    = (double*) malloc( sizeof(double) * 8760 );   daTDVMults[2]    = (double*) malloc( sizeof(double) * 8760 );
                  daResTDVMults[0] = (double*) malloc( sizeof(double) * 8760 );   daResTDVMults[1] = (double*) malloc( sizeof(double) * 8760 );   daResTDVMults[2] = (double*) malloc( sizeof(double) * 8760 );
					double* daTDVData[3]    = { &daTDVMults[0][0], &daTDVMults[1][0], &daTDVMults[2][0] };
					double* daResTDVData[3] = { &daResTDVMults[0][0], &daResTDVMults[1][0], &daResTDVMults[2][0] };
		            //	int iTableCol = ((lCliZnNum-1) * 3) + iFl + 2;
		            //	dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
               if (lEngyCodeYearNum < 2022 || (!bEchoNResData && bEchoResData))     // load daTDVMults w/ RES TDV mults if reporting Res and not NRes results - SAC 11/01/21 (MFam)
               {	if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[0] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[1] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daTDVMults[2][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[2] = &daZero[0];
   					assert( (daTDVData[0] != &daZero[0] && daTDVData[1] != &daZero[1] && daTDVData[2] != &daZero[2]) );
               }
               else
               {	if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, sTDVMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[0] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, sTDVMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[1] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daTDVMults[2][0], 8760, sTDVMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daTDVData[2] = &daZero[0];
   					assert( (daTDVData[0] != &daZero[0] && daTDVData[1] != &daZero[1] && daTDVData[2] != &daZero[2]) );
               }
               if (lEngyCodeYearNum >= 2022 && bEchoNResData && bEchoResData)
               {	if (BEMPX_GetTableColumn( &daResTDVMults[0][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daResTDVData[0] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daResTDVMults[1][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daResTDVData[1] = &daZero[0];
   					if (BEMPX_GetTableColumn( &daResTDVMults[2][0], 8760, sResTDVMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
   						daResTDVData[2] = &daZero[0];
   					assert( (daResTDVData[0] != &daZero[0] && daResTDVData[1] != &daZero[1] && daResTDVData[2] != &daZero[2]) );
               }
               double dFracRArea  = (fResFlrArea < 0.1 ? 0.0 : fResFlrArea / (fNonresFlrArea + fResFlrArea));
               double dFracNRArea = 1.0 - dFracRArea;

					QString sSrcEngyMultTableName, sResSrcEngyMultTableName;		// SAC 01/18/24
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SrcEngyMultTableName"    )+lPrimResultSetIdx-1, sSrcEngyMultTableName   , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResSrcEngyMultTableName" )+lPrimResultSetIdx-1, sResSrcEngyMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );

					//double daSrcEngyMults[3][8760], daResSrcEngyMults[3][8760];       // SAC 01/18/24
               double *daSrcEngyMults[3], *daResSrcEngyMults[3];   // switched from stack to heap memory for 8760 multiplier arrays - SAC 01/19/24
                  daSrcEngyMults[0]    = (double*) malloc( sizeof(double) * 8760 );   daSrcEngyMults[1]    = (double*) malloc( sizeof(double) * 8760 );   daSrcEngyMults[2]    = (double*) malloc( sizeof(double) * 8760 );
                  daResSrcEngyMults[0] = (double*) malloc( sizeof(double) * 8760 );   daResSrcEngyMults[1] = (double*) malloc( sizeof(double) * 8760 );   daResSrcEngyMults[2] = (double*) malloc( sizeof(double) * 8760 );
					double* daSrcEngyData[3]    = { &daSrcEngyMults[0][0], &daSrcEngyMults[1][0], &daSrcEngyMults[2][0] };
					double* daResSrcEngyData[3] = { &daResSrcEngyMults[0][0], &daResSrcEngyMults[1][0], &daResSrcEngyMults[2][0] };
               if (lEngyCodeYearNum >= 2022)
               {  if (bEchoNResData && !sSrcEngyMultTableName.isEmpty())
                  {	if (BEMPX_GetTableColumn( &daSrcEngyMults[0][0], 8760, sSrcEngyMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[0] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daSrcEngyMults[1][0], 8760, sSrcEngyMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[1] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daSrcEngyMults[2][0], 8760, sSrcEngyMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[2] = &daZero[0];
      					assert( (daSrcEngyData[0] != &daZero[0] && daSrcEngyData[1] != &daZero[1] && daSrcEngyData[2] != &daZero[2]) );
                  }
                  else if (!bEchoNResData && bEchoResData && !sResSrcEngyMultTableName.isEmpty())
                  {	if (BEMPX_GetTableColumn( &daSrcEngyMults[0][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[0] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daSrcEngyMults[1][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[1] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daSrcEngyMults[2][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daSrcEngyData[2] = &daZero[0];
      					assert( (daSrcEngyData[0] != &daZero[0] && daSrcEngyData[1] != &daZero[1] && daSrcEngyData[2] != &daZero[2]) );
                  }
                  if (bEchoNResData && bEchoResData)
                  {	if (BEMPX_GetTableColumn( &daResSrcEngyMults[0][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResSrcEngyData[0] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daResSrcEngyMults[1][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iNGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResSrcEngyData[1] = &daZero[0];
      					if (BEMPX_GetTableColumn( &daResSrcEngyMults[2][0], 8760, sResSrcEngyMultTableName.toLocal8Bit().constData(), iPropTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResSrcEngyData[2] = &daZero[0];
      					assert( (daResSrcEngyData[0] != &daZero[0] && daResSrcEngyData[1] != &daZero[1] && daResSrcEngyData[2] != &daZero[2]) );
               }  }

					QString sCO2EmissionsElecTableName, sCO2EmissionsNatGasTableName, sCO2EmissionsOtherTableName;		// SAC 01/18/24
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsElecTable"   )+lPrimResultSetIdx-1, sCO2EmissionsElecTableName  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsNatGasTable" )+lPrimResultSetIdx-1, sCO2EmissionsNatGasTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CO2EmissionsOtherTable"  )+lPrimResultSetIdx-1, sCO2EmissionsOtherTableName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
               double dCO2EmissionsNatGasMult=0.0, dCO2EmissionsOtherMult=0.0;
               BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsNatGasMult"  )+lPrimResultSetIdx-1, dCO2EmissionsNatGasMult, 0.0, -1, 0, BEMO_User, iBEMProcIdx );
               BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:CO2EmissionsOtherMult"   )+lPrimResultSetIdx-1, dCO2EmissionsOtherMult , 0.0, -1, 0, BEMO_User, iBEMProcIdx );
					int iCO2ElecTableCol   = (sCO2EmissionsElecTableName.isEmpty()   ? 0 : lCliZnNum + 1);
					int iCO2NatGasTableCol = (sCO2EmissionsNatGasTableName.isEmpty() ? 0 : lCliZnNum + 1 + (!sCO2EmissionsNatGasTableName.compare(sCO2EmissionsElecTableName) ? 16 : 0));
					int iCO2OtherTableCol  = (sCO2EmissionsOtherTableName.isEmpty()  ? 0 : lCliZnNum + 1 + (!sCO2EmissionsOtherTableName.compare( sCO2EmissionsElecTableName) ? 32 : 0));

					QString sResCO2EmissionsElecTableName, sResCO2EmissionsNatGasTableName, sResCO2EmissionsOtherTableName;		// SAC 01/18/24
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsElecTable"   )+lPrimResultSetIdx-1, sResCO2EmissionsElecTableName  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsNatGasTable" )+lPrimResultSetIdx-1, sResCO2EmissionsNatGasTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsOtherTable"  )+lPrimResultSetIdx-1, sResCO2EmissionsOtherTableName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
               double dResCO2EmissionsNatGasMult=0.0, dResCO2EmissionsOtherMult=0.0;
               BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsNatGasMult"  )+lPrimResultSetIdx-1, dResCO2EmissionsNatGasMult, 0.0, -1, 0, BEMO_User, iBEMProcIdx );
               BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Proj:ResCO2EmissionsOtherMult"   )+lPrimResultSetIdx-1, dResCO2EmissionsOtherMult , 0.0, -1, 0, BEMO_User, iBEMProcIdx );
					int iResCO2ElecTableCol   = (sResCO2EmissionsElecTableName.isEmpty()   ? 0 : lCliZnNum + 1);
					int iResCO2NatGasTableCol = (sResCO2EmissionsNatGasTableName.isEmpty() ? 0 : lCliZnNum + 1 + (!sResCO2EmissionsNatGasTableName.compare(sResCO2EmissionsElecTableName) ? 16 : 0));
					int iResCO2OtherTableCol  = (sResCO2EmissionsOtherTableName.isEmpty()  ? 0 : lCliZnNum + 1 + (!sResCO2EmissionsOtherTableName.compare( sResCO2EmissionsElecTableName) ? 32 : 0));

					//double daCO2EmisMults[3][8760], daResCO2EmisMults[3][8760];       // SAC 01/19/24
               double *daCO2EmisMults[3], *daResCO2EmisMults[3];   // switched from stack to heap memory for 8760 multiplier arrays - SAC 01/19/24
                  daCO2EmisMults[0]    = (double*) malloc( sizeof(double) * 8760 );   daCO2EmisMults[1]    = (double*) malloc( sizeof(double) * 8760 );   daCO2EmisMults[2]    = (double*) malloc( sizeof(double) * 8760 );
                  daResCO2EmisMults[0] = (double*) malloc( sizeof(double) * 8760 );   daResCO2EmisMults[1] = (double*) malloc( sizeof(double) * 8760 );   daResCO2EmisMults[2] = (double*) malloc( sizeof(double) * 8760 );
					double* daCO2EmisData[3]    = { &daCO2EmisMults[0][0], &daCO2EmisMults[1][0], &daCO2EmisMults[2][0] };
					double* daResCO2EmisData[3] = { &daResCO2EmisMults[0][0], &daResCO2EmisMults[1][0], &daResCO2EmisMults[2][0] };
               if (lEngyCodeYearNum >= 2022)
               {  if (bEchoNResData)
                  {	if (!sCO2EmissionsElecTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[0][0], 8760, sCO2EmissionsElecTableName.toLocal8Bit().constData(), iCO2ElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[0] = &daZero[0];
      					if (sCO2EmissionsNatGasTableName.isEmpty() && dCO2EmissionsNatGasMult > 0.0)
                        InitHourlyArray( daCO2EmisMults[1], dCO2EmissionsNatGasMult );
                     else if (!sCO2EmissionsElecTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[1][0], 8760, sCO2EmissionsNatGasTableName.toLocal8Bit().constData(), iCO2NatGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[1] = &daZero[0];
      					if (sCO2EmissionsOtherTableName.isEmpty() && dCO2EmissionsOtherMult > 0.0)
                        InitHourlyArray( daCO2EmisMults[2], dCO2EmissionsOtherMult );
                     else if (!sCO2EmissionsOtherTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[2][0], 8760, sCO2EmissionsOtherTableName.toLocal8Bit().constData(), iCO2OtherTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[2] = &daZero[0];
      					assert( (daCO2EmisData[0] != &daZero[0] && daCO2EmisData[1] != &daZero[1] && daCO2EmisData[2] != &daZero[2]) );
                  }
                  else if (!bEchoNResData && bEchoResData)
                  {	if (!sResCO2EmissionsElecTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[0][0], 8760, sResCO2EmissionsElecTableName.toLocal8Bit().constData(), iResCO2ElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[0] = &daZero[0];
      					if (sResCO2EmissionsNatGasTableName.isEmpty() && dResCO2EmissionsNatGasMult > 0.0)
                        InitHourlyArray( daCO2EmisMults[1], dResCO2EmissionsNatGasMult );
                     else if (!sResCO2EmissionsNatGasTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[1][0], 8760, sResCO2EmissionsNatGasTableName.toLocal8Bit().constData(), iResCO2NatGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[1] = &daZero[0];
      					if (sResCO2EmissionsOtherTableName.isEmpty() && dResCO2EmissionsOtherMult > 0.0)
                        InitHourlyArray( daCO2EmisMults[2], dResCO2EmissionsOtherMult );
                     else if (!sResCO2EmissionsOtherTableName.isEmpty() && BEMPX_GetTableColumn( &daCO2EmisMults[2][0], 8760, sResCO2EmissionsOtherTableName.toLocal8Bit().constData(), iResCO2OtherTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daCO2EmisData[2] = &daZero[0];
      					assert( (daCO2EmisData[0] != &daZero[0] && daCO2EmisData[1] != &daZero[1] && daCO2EmisData[2] != &daZero[2]) );
                  }
                  if (bEchoNResData && bEchoResData)
                  {	if (!sResCO2EmissionsElecTableName.isEmpty() && BEMPX_GetTableColumn( &daResCO2EmisMults[0][0], 8760, sResCO2EmissionsElecTableName.toLocal8Bit().constData(), iResCO2ElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResCO2EmisData[0] = &daZero[0];
      					if (sResCO2EmissionsNatGasTableName.isEmpty() && dResCO2EmissionsNatGasMult > 0.0)
                        InitHourlyArray( daResCO2EmisMults[1], dResCO2EmissionsNatGasMult );
                     else if (!sResCO2EmissionsNatGasTableName.isEmpty() && BEMPX_GetTableColumn( &daResCO2EmisMults[1][0], 8760, sResCO2EmissionsNatGasTableName.toLocal8Bit().constData(), iResCO2NatGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResCO2EmisData[1] = &daZero[0];
      					if (sResCO2EmissionsOtherTableName.isEmpty() && dResCO2EmissionsOtherMult > 0.0)
                        InitHourlyArray( daResCO2EmisMults[2], dResCO2EmissionsOtherMult );
                     else if (!sResCO2EmissionsOtherTableName.isEmpty() && BEMPX_GetTableColumn( &daResCO2EmisMults[2][0], 8760, sResCO2EmissionsOtherTableName.toLocal8Bit().constData(), iResCO2OtherTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResCO2EmisData[2] = &daZero[0];
      					assert( (daResCO2EmisData[0] != &daZero[0] && daResCO2EmisData[1] != &daZero[1] && daResCO2EmisData[2] != &daZero[2]) );
               }  }

					QString sElecDemMultTableName, sResElecDemMultTableName;		// SAC 01/19/24
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ElecDemMultTableName"    )+lPrimResultSetIdx-1, sElecDemMultTableName   , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
					BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ResElecDemMultTableName" )+lPrimResultSetIdx-1, sResElecDemMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
               if (!sElecDemMultTableName.isEmpty()    && sElecDemMultTableName.indexOf(':') > 0)
                  sElecDemMultTableName    = sElecDemMultTableName.left(    sElecDemMultTableName.indexOf(':') );
               if (!sResElecDemMultTableName.isEmpty() && sResElecDemMultTableName.indexOf(':') > 0)
                  sResElecDemMultTableName = sResElecDemMultTableName.left( sResElecDemMultTableName.indexOf(':') );
               int iElecDemMultTableCol=2, iResElecDemMultTableCol=2;
					//double daElecDemMults[8760], daResElecDemMults[8760];
               double *daElecDemMults, *daResElecDemMults;   // switched from stack to heap memory for 8760 multiplier arrays - SAC 01/19/24
                  daElecDemMults = (double*) malloc( sizeof(double) * 8760 );   daResElecDemMults = (double*) malloc( sizeof(double) * 8760 );
					double* daElecDemData    = &daElecDemMults[0];
					double* daResElecDemData = &daResElecDemMults[0];
               if (lEngyCodeYearNum >= 2022)
               {  if (bEchoNResData && !sElecDemMultTableName.isEmpty())
                  {	if (BEMPX_GetTableColumn( &daElecDemMults[0], 8760, sElecDemMultTableName.toLocal8Bit().constData(), iElecDemMultTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daElecDemData = &daZero[0];
      					assert( daElecDemData != &daZero[0] );
                  }
                  else if (!bEchoNResData && bEchoResData && !sResElecDemMultTableName.isEmpty())
                  {	if (BEMPX_GetTableColumn( &daElecDemMults[0], 8760, sResElecDemMultTableName.toLocal8Bit().constData(), iResElecDemMultTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daElecDemData = &daZero[0];
      					assert( daElecDemData != &daZero[0] );
                  }
                  if (bEchoNResData && bEchoResData && !sResElecDemMultTableName.isEmpty())
                  {	if (BEMPX_GetTableColumn( &daResElecDemMults[0], 8760, sResElecDemMultTableName.toLocal8Bit().constData(), iResElecDemMultTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
      						daResElecDemData = &daZero[0];
      					assert( daResElecDemData != &daZero[0] );
               }  }

				   // EXPORT hourly results records
					iYrHr = -1;
					int iMo, iDa, iHr, iLocTmMo, iLocTmDa, iLocTmHr;
               if (lEngyCodeYearNum < 2022)     // 2019 and earlier
   					for (iMo=1; iMo<13; iMo++)
   						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
   							for (iHr=1; iHr<25; iHr++)
   							{	iYrHr++;
   				            fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
   						daMtrEUData[0][ 0][iYrHr], daMtrEUData[0][ 1][iYrHr], daMtrEUData[0][ 2][iYrHr], daMtrEUData[0][ 3][iYrHr], daMtrEUData[0][ 4][iYrHr],
                     daMtrEUData[0][ 5][iYrHr], daMtrEUData[0][ 6][iYrHr], daMtrEUData[0][ 7][iYrHr], daMtrEUData[0][ 8][iYrHr], daMtrEUData[0][ 9][iYrHr],
                     daMtrEUData[0][10][iYrHr], daMtrEUData[0][11][iYrHr], daMtrEUData[0][12][iYrHr], daMtrEUData[0][13][iYrHr], daMtrEUData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
   						daMtrEUData[1][ 0][iYrHr]*dFUMlt, daMtrEUData[1][ 1][iYrHr]*dFUMlt, daMtrEUData[1][ 2][iYrHr]*dFUMlt, daMtrEUData[1][ 3][iYrHr]*dFUMlt, daMtrEUData[1][ 4][iYrHr]*dFUMlt,
                     daMtrEUData[1][ 5][iYrHr]*dFUMlt, daMtrEUData[1][ 6][iYrHr]*dFUMlt, daMtrEUData[1][ 7][iYrHr]*dFUMlt, daMtrEUData[1][ 8][iYrHr]*dFUMlt, daMtrEUData[1][ 9][iYrHr]*dFUMlt,
                     daMtrEUData[1][10][iYrHr]*dFUMlt, daMtrEUData[1][11][iYrHr]*dFUMlt, daMtrEUData[1][12][iYrHr]*dFUMlt, daMtrEUData[2][ 0][iYrHr]*dFUMlt, daMtrEUData[2][ 1][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 2][iYrHr]*dFUMlt, daMtrEUData[2][ 3][iYrHr]*dFUMlt, daMtrEUData[2][ 4][iYrHr]*dFUMlt, daMtrEUData[2][ 5][iYrHr]*dFUMlt, daMtrEUData[2][ 6][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 7][iYrHr]*dFUMlt, daMtrEUData[2][ 8][iYrHr]*dFUMlt, daMtrEUData[2][ 9][iYrHr]*dFUMlt, daMtrEUData[2][10][iYrHr]*dFUMlt, daMtrEUData[2][11][iYrHr]*dFUMlt,
                     daMtrEUData[2][12][iYrHr]*dFUMlt,
   						daTDVData[0][iYrHr], daTDVData[1][iYrHr]*dFTMlt, daTDVData[2][iYrHr]*dFTMlt );
   							}
               else if (bEchoNResData && !bEchoResData)  // still just one set of results data - Nonres - but shift PV/Battery to end of record
   					for (iMo=1; iMo<13; iMo++)
   						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
   							for (iHr=1; iHr<25; iHr++)
   							{  iLocTmMo = iMo;  iLocTmDa = iDa;
                           if ( iDST_StMo < 0 || iMo < iDST_StMo || iMo > iDST_EndMo ||      // local time labeling - SAC 11/11/22
                                (iMo == iDST_StMo  && (iDa < iDST_StDa  || (iDa == iDST_StDa  && iHr <= 2))) ||
                                (iMo == iDST_EndMo && (iDa > iDST_EndDa || (iDa == iDST_EndDa && iHr >  2))) )
                              iLocTmHr = iHr;   // local time = Std time
                           else if (iHr < 24)   // DST shifting mid-day       // DST shift FIX (from subtracting to adding hr) - SAC 05/10/24
                              iLocTmHr = iHr+1;
                           else if (iDa < iNumDaysInMonth[iMo-1])    // DST shifting to following day
                           {  iLocTmDa = iDa+1;  iLocTmHr = 1;   
                           }
                           else                 // DST shifting to following month
                           {  iLocTmMo = iMo+1;  iLocTmDa = 1;  iLocTmHr = 1;   
                           }
                           iYrHr++;
   				            fprintf( fp_CSV,  "%d,%d,%d, %02d/%02d %02d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"      // revised DST format to exclude trailing ':00' - SAC 11/12/22
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr, iLocTmMo, iLocTmDa, iLocTmHr,
   						daMtrEUData[0][ 0][iYrHr], daMtrEUData[0][ 1][iYrHr], daMtrEUData[0][ 2][iYrHr], daMtrEUData[0][ 3][iYrHr], daMtrEUData[0][ 4][iYrHr],
                     daMtrEUData[0][ 5][iYrHr], daMtrEUData[0][ 6][iYrHr], daMtrEUData[0][ 7][iYrHr], daMtrEUData[0][ 8][iYrHr], daMtrEUData[0][ 9][iYrHr],
                     daMtrEUData[0][10][iYrHr], daMtrEUData[0][13][iYrHr], daMtrEUData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
   						daMtrEUData[1][ 0][iYrHr]*dFUMlt, daMtrEUData[1][ 1][iYrHr]*dFUMlt, daMtrEUData[1][ 2][iYrHr]*dFUMlt, daMtrEUData[1][ 3][iYrHr]*dFUMlt, daMtrEUData[1][ 4][iYrHr]*dFUMlt,
                     daMtrEUData[1][ 5][iYrHr]*dFUMlt, daMtrEUData[1][ 6][iYrHr]*dFUMlt, daMtrEUData[1][ 7][iYrHr]*dFUMlt, daMtrEUData[1][ 8][iYrHr]*dFUMlt, daMtrEUData[1][ 9][iYrHr]*dFUMlt,
                     daMtrEUData[1][10][iYrHr]*dFUMlt, daMtrEUData[1][11][iYrHr]*dFUMlt, daMtrEUData[1][12][iYrHr]*dFUMlt, daMtrEUData[2][ 0][iYrHr]*dFUMlt, daMtrEUData[2][ 1][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 2][iYrHr]*dFUMlt, daMtrEUData[2][ 3][iYrHr]*dFUMlt, daMtrEUData[2][ 4][iYrHr]*dFUMlt, daMtrEUData[2][ 5][iYrHr]*dFUMlt, daMtrEUData[2][ 6][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 7][iYrHr]*dFUMlt, daMtrEUData[2][ 8][iYrHr]*dFUMlt, daMtrEUData[2][ 9][iYrHr]*dFUMlt, daMtrEUData[2][10][iYrHr]*dFUMlt, daMtrEUData[2][11][iYrHr]*dFUMlt,
                     daMtrEUData[2][12][iYrHr]*dFUMlt,		daTDVData[0][iYrHr], daTDVData[1][iYrHr]*dFTMlt, daTDVData[2][iYrHr]*dFTMlt,
                     daSrcEngyData[0][iYrHr], daSrcEngyData[1][iYrHr], daSrcEngyData[2][iYrHr],  daCO2EmisData[0][iYrHr], daCO2EmisData[1][iYrHr], daCO2EmisData[2][iYrHr],  daElecDemData[iYrHr],     // SAC 01/19/24
                     daMtrEUData[0][11][iYrHr], daMtrEUData[0][12][iYrHr] );
   							}
               else if (!bEchoNResData && bEchoResData)  // still just one set of results data - RES - and shift PV/Battery to end of record
   					for (iMo=1; iMo<13; iMo++)
   						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
   							for (iHr=1; iHr<25; iHr++)
   							{	iLocTmMo = iMo;  iLocTmDa = iDa;
                           if ( iDST_StMo < 0 || iMo < iDST_StMo || iMo > iDST_EndMo ||      // local time labeling - SAC 11/11/22
                                (iMo == iDST_StMo  && (iDa < iDST_StDa  || (iDa == iDST_StDa  && iHr <= 2))) ||
                                (iMo == iDST_EndMo && (iDa > iDST_EndDa || (iDa == iDST_EndDa && iHr >  2))) )
                              iLocTmHr = iHr;   // local time = Std time
                           else if (iHr < 24)   // DST shifting mid-day       // DST shift FIX (from subtracting to adding hr) - SAC 05/10/24
                              iLocTmHr = iHr+1;
                           else if (iDa < iNumDaysInMonth[iMo-1])    // DST shifting to following day
                           {  iLocTmDa = iDa+1;  iLocTmHr = 1;   
                           }
                           else                 // DST shifting to following month
                           {  iLocTmMo = iMo+1;  iLocTmDa = 1;  iLocTmHr = 1;   
                           }
                           iYrHr++;
   				            fprintf( fp_CSV,  "%d,%d,%d, %02d/%02d %02d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr, iLocTmMo, iLocTmDa, iLocTmHr,
   						daMtrEUResData[0][ 0][iYrHr], daMtrEUResData[0][ 1][iYrHr], daMtrEUResData[0][ 2][iYrHr], daMtrEUResData[0][ 3][iYrHr], daMtrEUResData[0][ 4][iYrHr],
                     daMtrEUResData[0][ 5][iYrHr], daMtrEUResData[0][ 6][iYrHr], daMtrEUResData[0][ 7][iYrHr], daMtrEUResData[0][ 8][iYrHr], daMtrEUResData[0][ 9][iYrHr],
                     daMtrEUResData[0][10][iYrHr], daMtrEUResData[0][13][iYrHr], daMtrEUResData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
   						daMtrEUResData[1][ 0][iYrHr]*dFUMlt, daMtrEUResData[1][ 1][iYrHr]*dFUMlt, daMtrEUResData[1][ 2][iYrHr]*dFUMlt, daMtrEUResData[1][ 3][iYrHr]*dFUMlt, daMtrEUResData[1][ 4][iYrHr]*dFUMlt,
                     daMtrEUResData[1][ 5][iYrHr]*dFUMlt, daMtrEUResData[1][ 6][iYrHr]*dFUMlt, daMtrEUResData[1][ 7][iYrHr]*dFUMlt, daMtrEUResData[1][ 8][iYrHr]*dFUMlt, daMtrEUResData[1][ 9][iYrHr]*dFUMlt,
                     daMtrEUResData[1][10][iYrHr]*dFUMlt, daMtrEUResData[1][11][iYrHr]*dFUMlt, daMtrEUResData[1][12][iYrHr]*dFUMlt, daMtrEUResData[2][ 0][iYrHr]*dFUMlt, daMtrEUResData[2][ 1][iYrHr]*dFUMlt,
                     daMtrEUResData[2][ 2][iYrHr]*dFUMlt, daMtrEUResData[2][ 3][iYrHr]*dFUMlt, daMtrEUResData[2][ 4][iYrHr]*dFUMlt, daMtrEUResData[2][ 5][iYrHr]*dFUMlt, daMtrEUResData[2][ 6][iYrHr]*dFUMlt,
                     daMtrEUResData[2][ 7][iYrHr]*dFUMlt, daMtrEUResData[2][ 8][iYrHr]*dFUMlt, daMtrEUResData[2][ 9][iYrHr]*dFUMlt, daMtrEUResData[2][10][iYrHr]*dFUMlt, daMtrEUResData[2][11][iYrHr]*dFUMlt,
                     daMtrEUResData[2][12][iYrHr]*dFUMlt,		daTDVData[0][iYrHr], daTDVData[1][iYrHr]*dFTMlt, daTDVData[2][iYrHr]*dFTMlt,
                     daSrcEngyData[0][iYrHr], daSrcEngyData[1][iYrHr], daSrcEngyData[2][iYrHr],  daCO2EmisData[0][iYrHr], daCO2EmisData[1][iYrHr], daCO2EmisData[2][iYrHr],  daElecDemData[iYrHr],     // SAC 01/19/24
                     daMtrEUResData[0][11][iYrHr], daMtrEUResData[0][12][iYrHr] );
   							}
               else  // write separate Nonres & Res results data
   					for (iMo=1; iMo<13; iMo++)
   						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
   							for (iHr=1; iHr<25; iHr++)
   							{	iLocTmMo = iMo;  iLocTmDa = iDa;
                           if ( iDST_StMo < 0 || iMo < iDST_StMo || iMo > iDST_EndMo ||      // local time labeling - SAC 11/11/22
                                (iMo == iDST_StMo  && (iDa < iDST_StDa  || (iDa == iDST_StDa  && iHr <= 2))) ||
                                (iMo == iDST_EndMo && (iDa > iDST_EndDa || (iDa == iDST_EndDa && iHr >  2))) )
                              iLocTmHr = iHr;   // local time = Std time
                           else if (iHr < 24)   // DST shifting mid-day       // DST shift FIX (from subtracting to adding hr) - SAC 05/10/24
                              iLocTmHr = iHr+1;
                           else if (iDa < iNumDaysInMonth[iMo-1])    // DST shifting to following day
                           {  iLocTmDa = iDa+1;  iLocTmHr = 1;   
                           }
                           else                 // DST shifting to following month
                           {  iLocTmMo = iMo+1;  iLocTmDa = 1;  iLocTmHr = 1;   
                           }
                           iYrHr++;
   				            fprintf( fp_CSV,  "%d,%d,%d, %02d/%02d %02d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	                "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"   // added 10 for NRes Src,CO2,ElDem + PV/B Src,CO2,ElDem - SAC 01/19/24
                                                                      "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
   																	                "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr, iLocTmMo, iLocTmDa, iLocTmHr,    // added 7 for Res Src,CO2,ElDem - SAC 01/19/24
   						daMtrEUData[0][ 0][iYrHr], daMtrEUData[0][ 1][iYrHr], daMtrEUData[0][ 2][iYrHr], daMtrEUData[0][ 3][iYrHr], daMtrEUData[0][ 4][iYrHr],    // NONRES data
                     daMtrEUData[0][ 5][iYrHr], daMtrEUData[0][ 6][iYrHr], daMtrEUData[0][ 7][iYrHr], daMtrEUData[0][ 8][iYrHr], daMtrEUData[0][ 9][iYrHr],
                     daMtrEUData[0][10][iYrHr], daMtrEUData[0][13][iYrHr], daMtrEUData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
   						daMtrEUData[1][ 0][iYrHr]*dFUMlt, daMtrEUData[1][ 1][iYrHr]*dFUMlt, daMtrEUData[1][ 2][iYrHr]*dFUMlt, daMtrEUData[1][ 3][iYrHr]*dFUMlt, daMtrEUData[1][ 4][iYrHr]*dFUMlt,
                     daMtrEUData[1][ 5][iYrHr]*dFUMlt, daMtrEUData[1][ 6][iYrHr]*dFUMlt, daMtrEUData[1][ 7][iYrHr]*dFUMlt, daMtrEUData[1][ 8][iYrHr]*dFUMlt, daMtrEUData[1][ 9][iYrHr]*dFUMlt,
                     daMtrEUData[1][10][iYrHr]*dFUMlt, daMtrEUData[1][11][iYrHr]*dFUMlt, daMtrEUData[1][12][iYrHr]*dFUMlt, daMtrEUData[2][ 0][iYrHr]*dFUMlt, daMtrEUData[2][ 1][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 2][iYrHr]*dFUMlt, daMtrEUData[2][ 3][iYrHr]*dFUMlt, daMtrEUData[2][ 4][iYrHr]*dFUMlt, daMtrEUData[2][ 5][iYrHr]*dFUMlt, daMtrEUData[2][ 6][iYrHr]*dFUMlt,
                     daMtrEUData[2][ 7][iYrHr]*dFUMlt, daMtrEUData[2][ 8][iYrHr]*dFUMlt, daMtrEUData[2][ 9][iYrHr]*dFUMlt, daMtrEUData[2][10][iYrHr]*dFUMlt, daMtrEUData[2][11][iYrHr]*dFUMlt,
                     daMtrEUData[2][12][iYrHr]*dFUMlt,		daTDVData[0][iYrHr], daTDVData[1][iYrHr]*dFTMlt, daTDVData[2][iYrHr]*dFTMlt,
                     daSrcEngyData[0][iYrHr], daSrcEngyData[1][iYrHr], daSrcEngyData[2][iYrHr],  daCO2EmisData[0][iYrHr], daCO2EmisData[1][iYrHr], daCO2EmisData[2][iYrHr],  daElecDemData[iYrHr],     // SAC 01/19/24
                     daMtrEUData[0][11][iYrHr], daMtrEUData[0][12][iYrHr],    ((daTDVData[0][iYrHr]*dFracNRArea)+(daResTDVData[0][iYrHr]*dFracRArea)),         // PV, Battery & PV/Batt TDV
                     ((daSrcEngyData[0][iYrHr]*dFracNRArea)+(daResSrcEngyData[0][iYrHr]*dFracRArea)),  ((daCO2EmisData[0][iYrHr]*dFracNRArea)+(daResCO2EmisData[0][iYrHr]*dFracRArea)),  ((daElecDemData[iYrHr]*dFracNRArea)+(daResElecDemData[iYrHr]*dFracRArea)),  // PV/B Src,CO2,ElDem - SAC 01/19/24
                     daMtrEUResData[0][ 0][iYrHr], daMtrEUResData[0][ 1][iYrHr], daMtrEUResData[0][ 2][iYrHr], daMtrEUResData[0][ 3][iYrHr], daMtrEUResData[0][ 4][iYrHr],       // RES data
                     daMtrEUResData[0][ 5][iYrHr], daMtrEUResData[0][ 6][iYrHr], daMtrEUResData[0][ 7][iYrHr], daMtrEUResData[0][ 8][iYrHr], daMtrEUResData[0][ 9][iYrHr],
                     daMtrEUResData[0][10][iYrHr], daMtrEUResData[0][13][iYrHr], daMtrEUResData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
   						daMtrEUResData[1][ 0][iYrHr]*dFUMlt, daMtrEUResData[1][ 1][iYrHr]*dFUMlt, daMtrEUResData[1][ 2][iYrHr]*dFUMlt, daMtrEUResData[1][ 3][iYrHr]*dFUMlt, daMtrEUResData[1][ 4][iYrHr]*dFUMlt,
                     daMtrEUResData[1][ 5][iYrHr]*dFUMlt, daMtrEUResData[1][ 6][iYrHr]*dFUMlt, daMtrEUResData[1][ 7][iYrHr]*dFUMlt, daMtrEUResData[1][ 8][iYrHr]*dFUMlt, daMtrEUResData[1][ 9][iYrHr]*dFUMlt,
                     daMtrEUResData[1][10][iYrHr]*dFUMlt, daMtrEUResData[1][11][iYrHr]*dFUMlt, daMtrEUResData[1][12][iYrHr]*dFUMlt, daMtrEUResData[2][ 0][iYrHr]*dFUMlt, daMtrEUResData[2][ 1][iYrHr]*dFUMlt,
                     daMtrEUResData[2][ 2][iYrHr]*dFUMlt, daMtrEUResData[2][ 3][iYrHr]*dFUMlt, daMtrEUResData[2][ 4][iYrHr]*dFUMlt, daMtrEUResData[2][ 5][iYrHr]*dFUMlt, daMtrEUResData[2][ 6][iYrHr]*dFUMlt,
                     daMtrEUResData[2][ 7][iYrHr]*dFUMlt, daMtrEUResData[2][ 8][iYrHr]*dFUMlt, daMtrEUResData[2][ 9][iYrHr]*dFUMlt, daMtrEUResData[2][10][iYrHr]*dFUMlt, daMtrEUResData[2][11][iYrHr]*dFUMlt,
                     daMtrEUResData[2][12][iYrHr]*dFUMlt,		daResTDVData[0][iYrHr], daResTDVData[1][iYrHr]*dFTMlt, daResTDVData[2][iYrHr]*dFTMlt,
                     daResSrcEngyData[0][iYrHr], daResSrcEngyData[1][iYrHr], daResSrcEngyData[2][iYrHr],  daResCO2EmisData[0][iYrHr], daResCO2EmisData[1][iYrHr], daResCO2EmisData[2][iYrHr],  daResElecDemData[iYrHr]  );     // SAC 01/19/24
   							}

               free( daTDVMults[0] );           free( daTDVMults[1] );           free( daTDVMults[2] );        // switched from stack to heap memory for 8760 multiplier arrays - SAC 01/19/24
               free( daResTDVMults[0] );        free( daResTDVMults[1] );        free( daResTDVMults[2] );
               free( daSrcEngyMults[0] );       free( daSrcEngyMults[1] );       free( daSrcEngyMults[2] );
               free( daResSrcEngyMults[0] );    free( daResSrcEngyMults[1] );    free( daResSrcEngyMults[2] );
               free( daCO2EmisMults[0] );       free( daCO2EmisMults[1] );       free( daCO2EmisMults[2] );
               free( daResCO2EmisMults[0] );    free( daResCO2EmisMults[1] );    free( daResCO2EmisMults[2] );
               free( daElecDemMults );          free( daResElecDemMults );
				}
				else if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14
				{	//	int iFuelTDVCol = (lNatGasAvailable > 0 ? 2 : 3);
				   // EXPORT hourly results records
					iYrHr = -1;
					int iMo, iDa, iHr;
					for (iMo=1; iMo<13; iMo++)
						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
							for (iHr=1; iHr<25; iHr++)
							{	iYrHr++;
				            fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
						daMtrEUData[0][ 0][iYrHr], daMtrEUData[0][ 1][iYrHr], daMtrEUData[0][ 2][iYrHr], daMtrEUData[0][ 3][iYrHr], daMtrEUData[0][ 4][iYrHr], daMtrEUData[0][ 5][iYrHr],
						daMtrEUData[0][ 6][iYrHr], daMtrEUData[0][ 7][iYrHr], daMtrEUData[0][ 8][iYrHr], daMtrEUData[0][ 9][iYrHr], daMtrEUData[0][10][iYrHr], daMtrEUData[0][11][iYrHr],
						daMtrEUData[1][ 0][iYrHr], daMtrEUData[1][ 1][iYrHr], daMtrEUData[1][ 2][iYrHr], daMtrEUData[1][ 3][iYrHr], daMtrEUData[1][ 4][iYrHr], daMtrEUData[1][ 5][iYrHr],
						daMtrEUData[1][ 6][iYrHr], daMtrEUData[1][ 7][iYrHr], daMtrEUData[1][ 8][iYrHr], daMtrEUData[1][ 9][iYrHr], daMtrEUData[1][10][iYrHr], daMtrEUData[1][11][iYrHr],
						daMtrEUData[2][ 0][iYrHr]*dFUMlt, daMtrEUData[2][ 1][iYrHr]*dFUMlt, daMtrEUData[2][ 2][iYrHr]*dFUMlt, daMtrEUData[2][ 3][iYrHr]*dFUMlt, daMtrEUData[2][ 4][iYrHr]*dFUMlt, daMtrEUData[2][ 5][iYrHr]*dFUMlt,
						daMtrEUData[2][ 6][iYrHr]*dFUMlt, daMtrEUData[2][ 7][iYrHr]*dFUMlt, daMtrEUData[2][ 8][iYrHr]*dFUMlt, daMtrEUData[2][ 9][iYrHr]*dFUMlt, daMtrEUData[2][10][iYrHr]*dFUMlt, daMtrEUData[2][11][iYrHr]*dFUMlt );
							}
				}

				fflush( fp_CSV );
				fclose( fp_CSV );

				for (iMtr=0; iMtr < NUM_T24_NRES_Fuels; iMtr++)    // switched from local 8760 arrays to malloc/free due to stack overflow - SAC 11/01/21
				{  free( daMtrCTotData[   iMtr] );
				   free( daMtrTotData[    iMtr] );
				   free( daMtrCTotResData[iMtr] );
				   free( daMtrTotResData[ iMtr] );
            }
			}
		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... ) {
			iRetVal = 4;
			sErrMsg = QString::asprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
			// if (!bSilent)
			// 	BEMMessageBox( "Unknown error writing hourly CSV results file." );
		}
	}

	if (!sErrMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
		sprintf_s( pszErrMsgBuffer, iErrMsgBufferLen, sErrMsg.toLocal8Bit().constData() );

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code
//											 1 : Error retrieving Proj:GasType, CliZnNum and/or other required data
//											 2 : Unable to open and/or write hourly CSV results file
//											 3 : Error encountered opening hourly CSV results file
//											 4 : Unknown error writing hourly CSV results file
//											 5 : Unexpected enduse count or index
//											 6 : Error retrieving TDS Table/Column and/or Mutiplier data
int CMX_ExportCSVHourlyResults_A2030( const char* pszHourlyResultsPathFile, const char* pszModelName, char* pszErrMsgBuffer /*=NULL*/,
													int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ )
{	int iRetVal = 0;
	QString sErrMsg;

	int iFl;
	QString saTDSTableName[3];   long laTDSColumnNum[3];   double daTDSMult[3];   int iTDSType[3] = {0,0,0};		// SAC 9/6/18 - A2030
	long lGasType, lCliZnNum;   double dEmisMult;
	if (	!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:GasType"              ), lGasType    ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CliZnNum"             ), lCliZnNum   ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) ||
			!BEMPX_GetFloat(	 BEMPX_GetDatabaseID( "Proj:ZEROCodeEmissionMult" ), dEmisMult   ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) )
	{	iRetVal = 1;
		sErrMsg = "Error retrieving Proj:GasType, CliZnNum and/or other required data";
	}
	else if (NUM_T24_NRES_EndUses_19 != 15 || IDX_T24_NRES_EU_Total != 14)	// SAC 2/1/17 - added error check to prevent bomb below  // SAC 7/15/18 - updated expected total to 15 (for PV & Batt)
	{	iRetVal = 5;
		sErrMsg = QString("Unexpected enduse count (%1) or total index (%2) (expecting 15 and 14 respectively)").arg(QString::number(NUM_T24_NRES_EndUses_19), QString::number(IDX_T24_NRES_EU_Total));
	}
	else
	{	bool bSetTDSResults = true;
		for (iFl=0; (bSetTDSResults && iFl < OSF_NumFuels); iFl++)
		{	if (BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:TDSTableName" )+iFl, saTDSTableName[iFl], FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !saTDSTableName[iFl].isEmpty() &&
				 BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:TDSColumnNum" )+iFl, laTDSColumnNum[iFl], 0, -1, -1, BEMO_User, iBEMProcIdx ) && laTDSColumnNum[iFl] > 0)
				iTDSType[iFl] = 1;
			else if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:TDSMult"   )+iFl, daTDSMult[     iFl], 0, -1, -1, BEMO_User, iBEMProcIdx ) && daTDSMult[iFl] != 0.0)
				iTDSType[iFl] = 2;
			if (iTDSType[iFl] < 1)
				bSetTDSResults = false;
		}
		if (!bSetTDSResults)
		{	iRetVal = 6;
			sErrMsg = "Error retrieving TDS Table/Column and/or Mutiplier data";
	}	}

	if (iRetVal == 0)
	{	QString sOverwriteMsg;
		sOverwriteMsg = QString::asprintf(	"The ZERO Code hourly CSV results file '%s' is opened in another application.  This file must be closed in that "
										"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
										"(once the file is closed), or \n'Abort' to abort the hourly export.", pszHourlyResultsPathFile );
		if (!OKToWriteOrDeleteFile( pszHourlyResultsPathFile, sOverwriteMsg, bSilent ))
		{	iRetVal = 2;
			sErrMsg = QString::asprintf( "Unable to open and/or write ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
	}

	if (iRetVal == 0)
	{	FILE *fp_CSV;
		int iErrorCode;
		try
		{
			iErrorCode = fopen_s( &fp_CSV, pszHourlyResultsPathFile, "wb" );
			if (iErrorCode != 0 || fp_CSV == NULL)
			{	iRetVal = 3;
				sErrMsg = QString::asprintf( "Error encountered opening ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
			}
			else
			{	fprintf( fp_CSV, "Hourly Results,\n" );
				fprintf( fp_CSV, ",,,Proposed Design Site Energy,,,,,Proposed Design Source Energy,,,,,Proposed Design TDV Energy,,,,,Proposed Design Emissions,\n" );
				fprintf( fp_CSV, ",,,Electric,Gas,PV Systems,Battery,Total,Electric,Gas,PV Systems,Battery,Total,Electric,Gas,PV Systems,Battery,Total,Electric,Gas,PV Systems,Battery,Total\n" );
				fprintf( fp_CSV, "Mo,Da,Hr,(kWh),(kBtu),(kWh),(kWh),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(kBtu),(lb),(lb),(lb),(lb),(lb)\n" );

			// SETUP hourly results arrays for export...
				int iYrHr=0;
				double daZero[8760];
				for (; iYrHr<8760; iYrHr++)
					daZero[iYrHr] = 0.0;

				double* daMtrEUData[ 2/*NUM_T24_NRES_Fuels*/][NUM_T24_NRES_EndUses_19];
				double  daMtrTotData[2/*NUM_T24_NRES_Fuels*/][8760];  // excluding PV & Battery
				int iEUOM=0, iEU;
				int iNumEUs = NUM_T24_NRES_EndUses_19;
				if (lGasType != 1)
					lGasType = 2;
				for (; iEUOM < 2; iEUOM++)
				{	int iMtr = (iEUOM < 1 ? iEUOM : lGasType);
					for (iEU=0; iEU < iNumEUs; iEU++)
					{	if (BEMPX_GetHourlyResultArrayPtr( &daMtrEUData[iEUOM][iEU], NULL, 0, pszModelName, pszaEPlusFuelNames[iMtr],
	 																esEUMap_CECNonRes[iEU].sEnduseName, iBEMProcIdx ) == 0 && daMtrEUData[iEUOM][iEU] != NULL)
						{	// OK - do nothing
						}
						else
						{	if (iEU == IDX_T24_NRES_EU_Total)
							{	daMtrEUData[iEUOM][iEU] = &daMtrTotData[iEUOM][0];
								for (iYrHr=0; iYrHr<8760; iYrHr++)
									daMtrTotData[iEUOM][iYrHr] = 0.0;
							}
							else
								daMtrEUData[iEUOM][iEU] = &daZero[0];   // this combination of meter & enduse does not have results, so assign 8760 of zeroes
					}	}

					// sum indiviudal enduse results into the CompTot & Tot enduses - SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
						if (iEU != IDX_T24_NRES_EU_CompTot && iEU != IDX_T24_NRES_EU_Total &&
							 iEU != IDX_T24_NRES_EU_PV && iEU != IDX_T24_NRES_EU_BT)		// SAC 9/6/18 - prevents summing of PV & Battery into Total
						{	for (iYrHr=0; iYrHr<8760; iYrHr++)
								daMtrEUData[iEUOM][IDX_T24_NRES_EU_Total][iYrHr] += daMtrEUData[iEUOM][iEU][iYrHr];
						}
				}

				long lPrimResultSetIdx = 1;	// SAC 3/11/20 - added to ensure main/primary result set TDV exported here
				long lDBID_Proj_PrimResultSetIdx = BEMPX_GetDatabaseID( "Proj:PrimResultSetIdx" );
				if (lDBID_Proj_PrimResultSetIdx < BEM_COMP_MULT || !BEMPX_GetInteger( lDBID_Proj_PrimResultSetIdx, lPrimResultSetIdx, 0, -1, -1, BEMO_User, iBEMProcIdx ) || lPrimResultSetIdx < 1)
					lPrimResultSetIdx = 1;
				QString sTDVMultTableName;		// SAC 11/5/19
				BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:TDVMultTableName" )+lPrimResultSetIdx-1, sTDVMultTableName, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
				if (sTDVMultTableName.isEmpty())
					sTDVMultTableName = "TDVbyCZandFuel";

				long lEngyCodeYearNum = 2016;	// SAC 3/11/20 - added to ensure correct TDV column indices (changed in 2022)
				long lDBID_Proj_EngyCodeYearNum = BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" );
				if (lDBID_Proj_EngyCodeYearNum < BEM_COMP_MULT || !BEMPX_GetInteger( lDBID_Proj_EngyCodeYearNum, lEngyCodeYearNum, 0, -1, -1, BEMO_User, iBEMProcIdx ) || lEngyCodeYearNum < 1)
					lEngyCodeYearNum = 2016;
				int iElecTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) +     0    + 2) : ((    0    * 16) + lCliZnNum + 1) );	// SAC 3/11/20
				int  iGasTableCol = (lEngyCodeYearNum <= 2019 ? (((lCliZnNum-1) * 3) + lGasType + 2) : ((lGasType * 16) + lCliZnNum + 1) );

					double daTDVMults[2][8760];
					double* daTDVData[2] = { &daTDVMults[0][0], &daTDVMults[1][0] };
		//	int iTableCol = ((lCliZnNum-1) * 3) + iFl + 2;
		//	dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
					if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, sTDVMultTableName.toLocal8Bit().constData(), iElecTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[0] = &daZero[0];
					}
					if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, sTDVMultTableName.toLocal8Bit().constData(),  iGasTableCol, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[1] = &daZero[0];
					}

				// TDS hourly multipliers
					double daTDSMults[2][8760];
					double* daTDSData[2] = { &daTDSMults[0][0], &daTDSMults[1][0] };
					int iTDSGasIdx = lGasType;
					if (iTDSType[0] == 1 && BEMPX_GetTableColumn( &daTDSMults[0][0], 8760, saTDSTableName[0].toLocal8Bit().constData(),
																					laTDSColumnNum[0], NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) == 0)
					{	// fine, do nothing
					}
					else if (iTDSType[0] == 2 && daTDSMult[0] != 0.0)
					{	for (iYrHr=0; iYrHr<8760; iYrHr++)
							daTDSMults[0][iYrHr] = daTDSMult[0];
					}
					else
					{	assert( FALSE );
						daTDSData[0] = &daZero[0];
					}

					if (iTDSType[iTDSGasIdx] == 1 && BEMPX_GetTableColumn( &daTDSMults[1][0], 8760, saTDSTableName[iTDSGasIdx].toLocal8Bit().constData(),
																								laTDSColumnNum[iTDSGasIdx], NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) == 0)
					{	// fine, do nothing
					}
					else if (iTDSType[iTDSGasIdx] == 2 && daTDSMult[iTDSGasIdx] != 0.0)
					{	for (iYrHr=0; iYrHr<8760; iYrHr++)
							daTDSMults[1][iYrHr] = daTDSMult[iTDSGasIdx];
					}
					else
					{	assert( FALSE );
						daTDSData[1] = &daZero[0];
					}

				// EXPORT hourly results records
					iYrHr = -1;
					int iMo, iDa, iHr;
					for (iMo=1; iMo<13; iMo++)
						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
							for (iHr=1; iHr<25; iHr++)
							{	iYrHr++;
				            fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
						// Proposed SITE Energy
						daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr], daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr] * 100,
						daMtrEUData[0][IDX_T24_NRES_EU_PV   ][iYrHr], daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr], 
						(( daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] + daMtrEUData[0][IDX_T24_NRES_EU_PV][iYrHr] +
						   daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr] ) * 3.412) + (daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr] * 100),
						// Proposed SOURCE Energy
						(daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] * daTDSData[0][iYrHr] / 1000),	// Btu -> kBtu
						(daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr] * daTDSData[1][iYrHr] * 100 ),
						(daMtrEUData[0][IDX_T24_NRES_EU_PV   ][iYrHr] * daTDSData[0][iYrHr] / 1000),
						(daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr] * daTDSData[0][iYrHr] / 1000), 
						((daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] + daMtrEUData[0][IDX_T24_NRES_EU_PV][iYrHr] +
						  daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr]) * daTDSData[0][iYrHr] / 1000) +
						 (daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr]  * daTDSData[1][iYrHr] * 100 ),
						// Proposed TDV Energy
						(daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] * daTDVData[0][iYrHr]),
						(daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr] * daTDVData[1][iYrHr]),
						(daMtrEUData[0][IDX_T24_NRES_EU_PV   ][iYrHr] * daTDVData[0][iYrHr]),
						(daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr] * daTDVData[0][iYrHr]), 
						((daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] + daMtrEUData[0][IDX_T24_NRES_EU_PV][iYrHr] +
						  daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr]) * daTDVData[0][iYrHr]) +
						 (daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr]  * daTDVData[1][iYrHr]),
						// Proposed Emissions
						(daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] * dEmisMult * daTDSData[0][iYrHr] / 1000),	// kWh * lb/kBtu * Btu/kWh / 1000 = lb
						(daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr] * dEmisMult * daTDSData[1][iYrHr] * 100 ),
						(daMtrEUData[0][IDX_T24_NRES_EU_PV   ][iYrHr] * dEmisMult * daTDSData[0][iYrHr] / 1000),
						(daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr] * dEmisMult * daTDSData[0][iYrHr] / 1000), 
						((daMtrEUData[0][IDX_T24_NRES_EU_Total][iYrHr] + daMtrEUData[0][IDX_T24_NRES_EU_PV][iYrHr] +
						  daMtrEUData[0][IDX_T24_NRES_EU_BT   ][iYrHr]) * dEmisMult * daTDSData[0][iYrHr] / 1000) +
						 (daMtrEUData[1][IDX_T24_NRES_EU_Total][iYrHr]  * dEmisMult * daTDSData[1][iYrHr] * 100 ) );
							}

				fflush( fp_CSV );
				fclose( fp_CSV );
			}
		}
		catch( ... ) {
			iRetVal = 4;
			sErrMsg = QString::asprintf( "Unknown error writing ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
	}

	if (!sErrMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
		sprintf_s( pszErrMsgBuffer, iErrMsgBufferLen, sErrMsg.toLocal8Bit().constData() );

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

int CMX_ExecuteModelkitBat(	LPCSTR sModelkitBatPathFile, LPCSTR sModelkitRubyScriptPathFile,  
                        LPCSTR sIDFPath, LPCSTR sIDFFilenameNoExt, bool bVerboseOutput,
                        char* pszReturnStr, int iReturnStrLength )
{
   return ExecuteModelkitBat(	sModelkitBatPathFile, sModelkitRubyScriptPathFile, sIDFPath,
                              sIDFFilenameNoExt, bVerboseOutput, pszReturnStr, iReturnStrLength );
}





