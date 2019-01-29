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
#include "memLkRpt.h"

static int CMX_ExportCSVHourlyResults_A2030( const char* pszHourlyResultsPathFile, const char* pszModelName, char* pszErrMsgBuffer /*=NULL*/,
													int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/ );


////////////////////////////////////////////////////////////////////////////////
int BCM_NRP_NumModels( int iModels )
{	return	(iModels & BCM_NRP_Model_1  ? 1 : 0) + (iModels & BCM_NRP_Model_2  ? 1 : 0) + (iModels & BCM_NRP_Model_3  ? 1 : 0) + (iModels & BCM_NRP_Model_4  ? 1 : 0) + (iModels & BCM_NRP_Model_5  ? 1 : 0) +
				(iModels & BCM_NRP_Model_6  ? 1 : 0) + (iModels & BCM_NRP_Model_7  ? 1 : 0) + (iModels & BCM_NRP_Model_8  ? 1 : 0) + (iModels & BCM_NRP_Model_9  ? 1 : 0) + (iModels & BCM_NRP_Model_10 ? 1 : 0) +
				(iModels & BCM_NRP_Model_11 ? 1 : 0) + (iModels & BCM_NRP_Model_12 ? 1 : 0) + (iModels & BCM_NRP_Model_13 ? 1 : 0) ;
}
int BCM_NRP_NumProgressModels( long lNRP )
{	return	(BCM_NRP_Model( lNRP ) & BCM_NRP_Model_1  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_2  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_3  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_4  ? 1 : 0) +
				(BCM_NRP_Model( lNRP ) & BCM_NRP_Model_5  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_6  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_7  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_8  ? 1 : 0) +
				(BCM_NRP_Model( lNRP ) & BCM_NRP_Model_9  ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_10 ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_11 ? 1 : 0) + (BCM_NRP_Model( lNRP ) & BCM_NRP_Model_12 ? 1 : 0) +
				(BCM_NRP_Model( lNRP ) & BCM_NRP_Model_13 ? 1 : 0) ;
}

static int iNumDaysInMonth[12] = {  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };

////////////////////////////////////////////////////////////////////////////////
// CEC Non-res analysis progress data & routines
																	//    BCM_NRP_Step_Init,  BCM_NRP_Step_Read,    BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSimRes,    BCM_NRP_Step_Store,  BCM_NRP_Step_Report,  BCM_NRP_Step_Done
const char* pszCECNResProgressMsgs[]					= { " Initialization",  " Read Project",      " Model Prep:  ",    " Translation:  ",    " Simulation:  ",   " Sim Results:  ",       " Model Storage",    " Report Generation", " Completed",   NULL  };

long			laCECNResProgressSteps[]					= {   BCM_NRP_Step_Init,  BCM_NRP_Step_Read,    BCM_NRP_Step_MPrep,  BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSimRes,  BCM_NRP_Step_MSimRes,   BCM_NRP_Step_MPrep,  BCM_NRP_Step_MPrep,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MTrans,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSim,  BCM_NRP_Step_MSimRes,  BCM_NRP_Step_MSimRes,   BCM_NRP_Step_Store,  BCM_NRP_Step_Report,  0 };
long			laCECNResProgressModels[]					= {                0,                  0,       BCM_NRP_Model_zp,    BCM_NRP_Model_zb,    BCM_NRP_Model_zp,     BCM_NRP_Model_zb,     BCM_NRP_Model_zp,   BCM_NRP_Model_zb,   BCM_NRP_Model_zp,      BCM_NRP_Model_zb,       BCM_NRP_Model_ap,    BCM_NRP_Model_ab,    BCM_NRP_Model_ap,     BCM_NRP_Model_ab,     BCM_NRP_Model_ap,   BCM_NRP_Model_ab,   BCM_NRP_Model_ap,      BCM_NRP_Model_ab,                   0,                   0,        0 };
float       faCECNResProgressVals_SerlAllSims[]    = {                1,                  3,                   2,                    2,                  3,                     3,                  10,                  10,                 2,                     2,                       2,                   2,                   3,                    3,                   30,                 30,                 2,                     2,                      3,                  15,          };
float       fCECNResProgressValSum_SerlAllSims     =                  1 +                 3 +                  2 +                   2 +                 3 +                    3 +                 10 +                 10 +                2 +                    2 +                      2 +                  2 +                  3 +                   3 +                  30 +                30 +                2 +                    2 +                     3 +                 15            ;
float       faCECNResProgressVals_SerlZBAPABSims[] = {                1,                  3,                   2,                    2,                  3,                     3,                   1,                  10,                 2,                     2,                       2,                   2,                   3,                    3,                   30,                 30,                 2,                     2,                      3,                  15,          };
float       fCECNResProgressValSum_SerlZBAPABSims  =                  1 +                 3 +                  2 +                   2 +                 3 +                    3 +                  1 +                 10 +                2 +                    2 +                      2 +                  2 +                  3 +                   3 +                  30 +                30 +                2 +                    2 +                     3 +                 15            ;
float       faCECNResProgressVals_SerlZPAPSims[]   = {                1,                  3,                   2,                    2,                  3,                     0,                  10,                   0,                 2,                     2,                       2,                   2,                   3,                    0,                   30,                  0,                 2,                     2,                      3,                  15,          };
float       fCECNResProgressValSum_SerlZPAPSims    =                  1 +                 3 +                  2 +                   2 +                 3 +                    0 +                 10 +                  0 +                2 +                    2 +                      2 +                  2 +                  3 +                   0 +                  30 +                 0 +                2 +                    2 +                     3 +                 15            ;
float       faCECNResProgressVals_SerlAPSim[]      = {                1,                  3,                   2,                    2,                  3,                     0,                   1,                   0,                 2,                     2,                       2,                   2,                   3,                    0,                   30,                  0,                 2,                     2,                      3,                  15,          };
float       fCECNResProgressValSum_SerlAPSim       =                  1 +                 3 +                  2 +                   2 +                 3 +                    0 +                  1 +                  0 +                2 +                    2 +                      2 +                  2 +                  3 +                   0 +                  30 +                 0 +                2 +                    2 +                     3 +                 15            ;
float       faCECNResProgressVals_ParlAllSims[]    = {                1,                  3,                   2,                    2,                  3,                     3,                   1,                  12,                 2,                     2,                       2,                   2,                   3,                    3,                    1,                 35,                 2,                     2,                      5,                  15,          };
float       fCECNResProgressValSum_ParlAllSims     =                  1 +                 3 +                  2 +                   2 +                 3 +                    3 +                  1 +                 12 +                2 +                    2 +                      2 +                  2 +                  3 +                   3 +                   1 +                35 +                2 +                    2 +                     5 +                 15            ;
float       faCECNResProgressVals_ParlZPAPSims[]   = {                1,                  3,                   2,                    2,                  3,                     0,                  10,                   0,                 2,                     2,                       2,                   2,                   3,                    0,                   30,                  0,                 2,                     2,                      5,                  15,          };
float       fCECNResProgressValSum_ParlZPAPSims    =                  1 +                 3 +                  2 +                   2 +                 3 +                    0 +                 10 +                  0 +                2 +                    2 +                      2 +                  2 +                  3 +                   0 +                  30 +                 0 +                2 +                    2 +                     5 +                 15            ;
float       faCECNResProgressVals_ParlAPSims[]     = {                1,                  3,                   2,                    2,                  3,                     0,                   1,                   0,                 2,                     2,                       2,                   2,                   3,                    0,                   30,                  0,                 2,                     2,                      5,                  15,          };
float       fCECNResProgressValSum_ParlAPSims      =                  1 +                 3 +                  2 +                   2 +                 3 +                    0 +                  1 +                  0 +                2 +                    2 +                      2 +                  2 +                  3 +                   0 +                  30 +                 0 +                2 +                    2 +                     5 +                 15            ;

//const char** pszCECNResProgressMsgs=NULL;
float *faCECNResProgressVals=NULL, fCECNResProgressValSum=0;

#define  NUM_CECNResProgressEntries  25
float  faCECNResCumulativeProgressSum[NUM_CECNResProgressEntries];
void SetCECNResCumulativeProgressSum()
{	int idx = -1;			bool bDone = false;
	while (++idx < NUM_CECNResProgressEntries)
	{	if (bDone)
			faCECNResCumulativeProgressSum[idx] = 0;
		else
		{	faCECNResCumulativeProgressSum[idx] = (idx < 1 ? 0 : faCECNResCumulativeProgressSum[idx-1] + faCECNResProgressVals[idx-1]);
			if (laCECNResProgressSteps[idx] == 0)
				bDone = true;
		}
	}
	assert( bDone );
}

void SetCECNResProgressMessage( QString& sMsg, long lNRPStep, long lNRPModels )
{	sMsg = pszCECNResProgressMsgs[lNRPStep-1];
	if (lNRPModels > 0)
	{	int iNumModels = BCM_NRP_NumModels( lNRPModels );		int iModelsFound = 0;
		if (lNRPModels & BCM_NRP_Model_zp)
		{	iModelsFound++;
			sMsg += "zp";
			if (iModelsFound < iNumModels-1)				sMsg += ", ";
			else if (iModelsFound == iNumModels-1)		sMsg += " & ";
		}
		if (lNRPModels & BCM_NRP_Model_zb)
		{	iModelsFound++;
			sMsg += "zb";
			if (iModelsFound < iNumModels-1)				sMsg += ", ";
			else if (iModelsFound == iNumModels-1)		sMsg += " & ";
		}
		if (lNRPModels & BCM_NRP_Model_ap)
		{	iModelsFound++;
			sMsg += "ap";
			if (iModelsFound < iNumModels-1)				sMsg += ", ";
			else if (iModelsFound == iNumModels-1)		sMsg += " & ";
		}
		if (lNRPModels & BCM_NRP_Model_ab)
		{	iModelsFound++;
			sMsg += "ab";
			if (iModelsFound < iNumModels-1)				sMsg += ", ";
			else if (iModelsFound == iNumModels-1)		sMsg += " & ";
		}
		assert( iModelsFound == iNumModels );
	}
}

void SetCECNResProgressMessage( QString& sMsg, long lProgressID )
{	long lNRPStep  = BCM_NRP_Step(  lProgressID );
	long lNRPModel = BCM_NRP_Model( lProgressID );
	SetCECNResProgressMessage( sMsg, lNRPStep, lNRPModel );
}


void SetCECNResProgressVal_Parallel( bool bAll, bool bZP, bool bAP )
{	//pszCECNResProgressMsgs = pszCECNResProgressMsgs_Parl;
	if (bAll)
	{	faCECNResProgressVals  = faCECNResProgressVals_ParlAllSims;
		fCECNResProgressValSum = fCECNResProgressValSum_ParlAllSims;
	}
	else if (bZP && bAP)
	{	faCECNResProgressVals  = faCECNResProgressVals_ParlZPAPSims;
		fCECNResProgressValSum = fCECNResProgressValSum_ParlZPAPSims;
	}
	else
	{	faCECNResProgressVals  = faCECNResProgressVals_ParlAPSims;
		fCECNResProgressValSum = fCECNResProgressValSum_ParlAPSims;
	}
	SetCECNResCumulativeProgressSum();
}
void SetCECNResProgressVal_Serial( bool bZP, bool bAP, bool bZB, bool bAB )
{	//pszCECNResProgressMsgs = pszCECNResProgressMsgs_Serl;
	if (!bZP && bAP && !bZB && !bAB)
   {  faCECNResProgressVals  = faCECNResProgressVals_SerlAPSim;
      fCECNResProgressValSum = fCECNResProgressValSum_SerlAPSim;
	}
	else if (bZP && bAP && !bZB && !bAB)
   {  faCECNResProgressVals  = faCECNResProgressVals_SerlZPAPSims;
      fCECNResProgressValSum = fCECNResProgressValSum_SerlZPAPSims;
	}
	else if (!bZP && bAP && bZB && bAB)
   {  faCECNResProgressVals  = faCECNResProgressVals_SerlZBAPABSims;
      fCECNResProgressValSum = fCECNResProgressValSum_SerlZBAPABSims;
	}
	else
   {  faCECNResProgressVals  = faCECNResProgressVals_SerlAllSims;
      fCECNResProgressValSum = fCECNResProgressValSum_SerlAllSims;
	}
	SetCECNResCumulativeProgressSum();
}

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

static inline int GetCECNResProgressIndex( long lStep, long lModel )
{	int iRetVal = -2;
	for (int i=0; iRetVal < -1; i++)
	{
		if (laCECNResProgressSteps[i] == 0)
			iRetVal = -1;
		else if (laCECNResProgressSteps[i] == lStep)
		{	if ( laCECNResProgressModels[i] == 0 ||
				 (laCECNResProgressModels[i] & lModel))
				iRetVal = i;
	}	}
	return iRetVal;
}

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
		long lNRPStep  = BCM_NRP_Step(  lProgressID );
		long lNRPModel = BCM_NRP_Model( lProgressID );
		int iNRPIdx = GetCECNResProgressIndex( lNRPStep, lNRPModel );				assert( iNRPIdx >= 0 );
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
			SetCECNResProgressMessage( sProgMsg, lNRPStep, lNRPModel );
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
		SetCECNResProgressMessage( sMsg, iProgressStep, 0 /*lNRPModel*/ );
	else
		SetS901GProgressMessage( sMsg, iProgressStep, 0 /*lNRPModel*/ );
	if (spAnalProgCallbackFunc != NULL && slAnalysisProgressCallbackRetVal > 0)
	{	//											52 : Analysis aborted via callback function in calling application
		iErrorID = 52;
		sErrMsg.sprintf( "Analysis aborted by calling application during%s analysis step (callback function returned %d)", sMsg.toLocal8Bit().constData(), slAnalysisProgressCallbackRetVal );
	}
	else
	{	//											33 : User aborted analysis via progress dialog 'Cancel' button
		iErrorID = 33;
		sErrMsg.sprintf( "User aborted analysis via progress dialog 'Cancel' button during%s analysis step", sMsg.toLocal8Bit().constData() );
	}
	ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iErrorID /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
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
		sErrMsg.sprintf( "Error retrieving BEMBase object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
			sErrMsg.sprintf( "Error retrieving BEMBase property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
													sLogMsg.sprintf( "%s '%s'", (bWinObj2 ? "Win" : "Door"), pWinDoorObj2->getName().toLocal8Bit().constData() );
													sOverlappingWinsDrs += sLogMsg;
										}	}	}

										if (iNumOverlapsThisWinDr > 0)
										{	// record overlaps between this win/door and subsequent win/door siblings
											iNumWallErrors++;
											if (!sOverlapsOnThisExtWall.isEmpty())
												sOverlapsOnThisExtWall += " | ";
											sLogMsg.sprintf( "%s '%s' overlaps %s", (bWinObj ? "Win" : "Door"), pWinDoorObj->getName().toLocal8Bit().constData(), sOverlappingWinsDrs.toLocal8Bit().constData() );
											sOverlapsOnThisExtWall += sLogMsg;
									}	}
								}	// end of loop over children of wall

								if (iNumWallErrors > 0)
								{	// record all overlaps between this ExtWall's child wins/doors
									iRetVal++;
									sLogMsg.sprintf( "ExtWall '%s' has overlapping windows/doors as follows:  %s", pChildObj->getName().toLocal8Bit().constData(), sOverlapsOnThisExtWall.toLocal8Bit().constData() );
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
											sErrMsg.sprintf( "Error gathering data to create PolyLp object:  %s '%s' %s",
																		pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData(),
																		sSurfErrMsg.right( sSurfErrMsg.length()-2 ).toLocal8Bit().constData() );
										}
										else
										{	// call PolyLp creation routine
											iPolyLpObjIdx = BEMPX_CreatePolyLoop( fArea, fAz, fTilt, fZ, iPolyType, fParentDZ, fParentArea, -1 /*iBEMProcIdx*/, NULL, dDX, dDY, dDZ, fChldHgt, fChldX, fChldY );
											if (iPolyLpObjIdx < 0)
											{	if (fArea > fParentArea)
												{	iRetVal = -6;
													sErrMsg.sprintf( "Error generating building geometry: %s '%s' area (%g) exceeds parent %s '%s' area (%g)", pGChildObj->getClass()->getLongName().toLocal8Bit().constData(),  
																				pGChildObj->getName().toLocal8Bit().constData(), fArea, pChildObj->getClass()->getLongName().toLocal8Bit().constData(),
																				pChildObj->getName().toLocal8Bit().constData(), fParentArea );
												}
												else
												{	iRetVal = -4;
													sErrMsg.sprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, WallHt %g, WallArea %g)",
																				pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData(),
																				fArea, fAz, fTilt, fZ, iPolyType, fParentDZ, fParentArea );
											}	}
											else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pGChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
											{	iRetVal = -5;
												sErrMsg.sprintf( "Error adding PolyLp child to %s '%s'", pGChildObj->getClass()->getShortName().toLocal8Bit().constData(), pGChildObj->getName().toLocal8Bit().constData() );
											}
											else
											{	iRetVal++;
												if (bVerbose)
												{	sLogMsg.sprintf( "         PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, WallHt %g, WallArea %g)", 
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
		sErrMsg.sprintf( "Error retrieving BEMBase object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
			sErrMsg.sprintf( "Error retrieving BEMBase property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
									sErrMsg.sprintf( "Error gathering data to create PolyLp object:  %s '%s' %s", pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																							pChildObj->getName().toLocal8Bit().constData(), sSurfErrMsg.right( sSurfErrMsg.length()-2 ).toLocal8Bit().constData() );
								}
								else if (bProcessSurface)
								{	// call PolyLp creation routine
									iPolyLpObjIdx = BEMPX_CreatePolyLoop( fArea, fAz, fTilt, fZ, iPolyType, fArg6, fArg7, -1 /*iBEMProcIdx*/, &dFurthestInteriorFromXYOrig );
									if (iPolyLpObjIdx < 0)
									{	iRetVal = -4;
										sErrMsg.sprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g) - BEMPX_CreatePolyLoop() returned %d",
																		pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
																		pChildObj->getName().toLocal8Bit().constData(), fArea, fAz, fTilt, fZ, iPolyType, fArg6, fArg7, iPolyLpObjIdx );
									}
									else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
									{	iRetVal = -5;
										sErrMsg.sprintf( "Error adding PolyLp child to %s '%s'", pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData() );
									}
									else
									{	iRetVal++;
										if (bVerbose)
										{	sLogMsg.sprintf( "      PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", 
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
										sErrMsg.sprintf( "Error creating PolyLp object:  %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", 
																		pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData(),
																		(*itp)->m_fArea, (*itp)->m_fAz, (*itp)->m_fTilt, (*itp)->m_fZ, (*itp)->m_iPolyType, (*itp)->m_fArg6, (*itp)->m_fArg7 );
									}
									else if (BEMPX_SetBEMData( lDBID_PolyLp_Parent, BEMP_QStr, (void*) &pChildObj->getName(), BEMO_User, iPolyLpObjIdx ) < 0)
									{	iRetVal = -5;
										sErrMsg.sprintf( "Error adding PolyLp child to %s '%s'", pChildObj->getClass()->getShortName().toLocal8Bit().constData(), pChildObj->getName().toLocal8Bit().constData() );
									}
									else
									{	iRetVal++;
										if (bVerbose)
										{	sLogMsg.sprintf( "      PolyLp created for %s '%s' (Area %g, Az %g, Tilt %g, Z %g, PolyType %d, Arg6 %g, Arg7 %g)", pChildObj->getClass()->getShortName().toLocal8Bit().constData(),
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
	{	sLogMsg.sprintf( "   %d PolyLp objects created by CMX_GeneratePolyLoops_CECNonRes()", iRetVal );
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
		sErrMsg.sprintf( "Error retrieving BEMBase CreateWindowShadeObject ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
	}
	else
	{	QString sShadeName = (pWinObj ? pWinObj->getName() : "Window");
		sShadeName += sAppendToName;
		BEMObject* pShdObj = BEMPX_CreateObject( iCID_ExtShdgObj, sShadeName.toLocal8Bit().constData(), pGParentSpcObj );  // , BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE, bool bAutoCreate = TRUE, int iBEMProcIdx=-1, BOOL bIgnoreMaxDefinable=FALSE, int i0ChildIdx =-1 );
		if (pShdObj == NULL)
		{	iRetVal = -3;
			sErrMsg.sprintf( "Error creating %s ExtShdgObj for window '%s'", pszShadeDescrip, (pWinObj ? pWinObj->getName().toLocal8Bit().constData() : "unknown") );
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
				sErrMsg.sprintf( "Error creating PolyLp to store geometry for %s '%s' of window '%s'", pszShadeDescrip, pShdObj->getName().toLocal8Bit().constData(), 
																(pWinObj ? pWinObj->getName().toLocal8Bit().constData() : "unknown") );
			}
			else
			{	double faCoord[3];
				for (int iCoord=0; (iRetVal>=0 && iCoord < 4); iCoord++)
				{	BEMObject* pCoordObj = BEMPX_CreateObject( iCID_CartesianPt, NULL, pPolyLpObj );
					if (pCoordObj == NULL)
					{	iRetVal = -5;
						sErrMsg.sprintf( "Error creating CartesianPt #%d to store geometry for %s '%s' of window '%s'", iCoord+1, pszShadeDescrip, 
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
		sErrMsg.sprintf( "Error retrieving BEMBase CMX_GenerateWindowShades object ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
			sErrMsg.sprintf( "Error retrieving BEMBase CMX_GenerateWindowShades property ID(s):  %s", sBEMErr.toLocal8Bit().constData() );
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
						sTemp.sprintf( "%s'%s' (#%d)", (sMissingPolyLpWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
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
							sTemp.sprintf( "%s'%s' (#%d)", (sBadPolyLpDataWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
							sBadPolyLpDataWins += sTemp;
						}
						else if (fXYLen < 0.0001 || (WithinMargin( fUnitVectorOi, 0.0, 0.0001 ) && WithinMargin( fUnitVectorOj, 0.0, 0.0001 )))
						{	iNumHorizWins++;
							sTemp.sprintf( "%s'%s' (#%d)", (sHorizWins.isEmpty() ? "" : ", "), sWinName.toLocal8Bit().constData(), iWin+1 );
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
	{	sLogMsg.sprintf( "   %d window shade (and child PolyLp) object(s) created for %d windows by CMX_GenerateWindowShades_CECNonRes()", iRetVal, iNumWinsProcessed );
		BEMPX_WriteLogFile( sLogMsg );  //, sLogPathFile, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
	}

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
							if (bVerbose)
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


#define  Com_NumCSEMeters    3
static const char* pszMeters[Com_NumCSEMeters+1]			= { "MtrElec",     "MtrNatGas",  "MtrOther",  NULL };
static const char* pszMeters_ComMap[Com_NumCSEMeters+1]	= { "Electricity", "NaturalGas", "OtherFuel", NULL };		// SAC 5/31/16 - added to enable retrieval of CSE results to -Com analysis
double         sdaMeterMults_ComMap[Com_NumCSEMeters+1]	= {    0.293,         0.01,         0.01,     0.0  };		// SAC 6/1/16 - added to convert units of CSE results to -Com analysis (1/3.412 for elec)  // SAC 6/29/16 - inc NG & Oth fuel mults by 10 fixing MBtu->therms

static const char* pszCSEEnduseList[]    = { /*"Tot", "Clg", "Htg", "HPHtg",*/ "Dhw",                "DhwBU",              "DhwMFL",             /*"FanC", "FanH", "FanV", "Fan", "Aux", "Proc", "Lit", "Rcp", "Ext", "Refr", "Dish", "Dry", "Wash", "Cook",*/ "User2",              /*"User2",*/ "PV",            "BT",      NULL };	// "DHWPmp", ??   // SAC 7/15/18 - added PV & Batt  	// SAC 7/27/18 - added "DhwMFL" (DHWLOOP pumping energy - CSE19 v0.850.0, SVN r1098)
static const char* pszCSEEUList_ComMap[] = { /* NULL,  NULL,  NULL,   NULL ,*/ "Domestic Hot Water", "Domestic Hot Water", "Domestic Hot Water", /* NULL ,  NULL ,  NULL ,  NULL,  NULL,  NULL ,  NULL,  NULL,  NULL,  NULL ,  NULL ,  NULL,  NULL ,  NULL ,*/ "Domestic Hot Water", /*  NULL ,*/ "Photovoltaics", "Battery", NULL }; 				// SAC 1/8/19 - summed in CSE enduse 'User2' to each elec DHW results retrieval (to capture HPWH XBU energy)

static int ProcessModelReports( const char* pszModelPathFile, long lDBID_ReportType, long lDBID_ReportFileAppend, int iObjIdx, bool /*bProcessCurrentSelection*/,
									QVector<QString>& saModelReportOptions, bool bVerbose, bool bSilent );

static const char* GetResultsCSVHeader_NonRes( int i1HdrIdx, int iCodeType );

const char pcCharsNotAllowedInObjNames_CECNonRes[] = { '"', ',', '\'', '!', ';', NULL };	// SAC 8/20/14

static QString sDbgFileName;

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
//											41 : CSE (ResDHW/PV/Battery) simulation not successful
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
	bool bAllowAnalysisAbort			=  true;		//(GetCSVOptionValue( "AllowAnalysisAbort"         ,   1,  saCSVOptions ) > 0);	// SAC 4/5/15
	if (bPromptUserUMLHWarning && (bSilent || iDontAbortOnErrorsThruStep > 6))
		bPromptUserUMLHWarning = false;		// SAC 3/19/15 - toggle OFF PromptUserUMLHWarning if 'silent' flag set or DontAbortOnErrorsThruStep includes UMLH check step

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
#endif

	int iNumFileOpenDefaultingRounds = GetCSVOptionValue( "NumFileOpenDefaultingRounds", 3, saCSVOptions );		// SAC 4/11/18

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
	{	sLogMsg.sprintf( "File specified in IDFToSimulate option not found:  %s", sIDFToSimulate.toLocal8Bit().constData() );
		BEMPX_WriteLogFile( sLogMsg );
		sIDFToSimulate.clear();
	}

	int iCID_Proj = BEMPX_GetDBComponentID( "Proj" );
	QString sDebugRuleEvalCSV;		// SAC 1/9/14 - ported from Res analysis - ability to specify targeted rule eval debug info
	GetCSVOptionString( "DebugRuleEvalCSV", sDebugRuleEvalCSV, saCSVOptions );
	BEMCompNameTypePropArray compRuleDebugInfo;
	void* pCompRuleDebugInfo = NULL;
	if (!sDebugRuleEvalCSV.isEmpty() && FileExists( sDebugRuleEvalCSV.toLocal8Bit().constData() ))
	{	sLogMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Abort' to ignore this file.", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
		if (!OKToWriteOrDeleteFile( sDebugRuleEvalCSV.toLocal8Bit().constData(), sLogMsg, bSilent ))
		{	if (bSilent)
				sLogMsg.sprintf( "ERROR:  Unable to open %s file:  %s", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
			else
				sLogMsg.sprintf( "ERROR:  User chose not to use/reference %s file:  %s", "rule evaluation debug", sDebugRuleEvalCSV.toLocal8Bit().constData() );
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

	QString sModelPathOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.left(                               sModelPathFile.lastIndexOf('\\') + 1 ) : "");
	QString sModelFileOnly = (sModelPathFile.lastIndexOf('\\') ? sModelPathFile.right( sModelPathFile.length() - sModelPathFile.lastIndexOf('\\') - 1 ) : "");		assert( !sModelFileOnly.isEmpty() );
	QString sModelFileOnlyWithExt = sModelFileOnly;
	if (sModelFileOnly.lastIndexOf('.') > 0)
		sModelFileOnly = sModelFileOnly.left( sModelFileOnly.lastIndexOf('.') );

	QString sXMLResultsFileName = sModelPathFile;
	if (sXMLResultsFileName.lastIndexOf('.'))
		sXMLResultsFileName  = sXMLResultsFileName.left( sXMLResultsFileName.lastIndexOf('.') );
	sXMLResultsFileName += " - AnalysisResults.xml";

	// UMLH check stuff
	QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));		// enables Locale-specific formatted numeric strings
	QString sUMLHTextFileMsg, sUMLHTextFileName = sModelPathFile;
	if (sUMLHTextFileName.lastIndexOf('.'))
	{	sUMLHTextFileName  = sUMLHTextFileName.left( sUMLHTextFileName.lastIndexOf('.') );
		sUMLHTextFileName += " - UMLH Zones.txt";
		if (FileExists( sUMLHTextFileName.toLocal8Bit().constData() ))	// if UMLH Zones text file already exists (from previous run), delete it before continuing processing
			DeleteFile( sUMLHTextFileName.toLocal8Bit().constData() );
	}

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
	{	if (sLoadedRuleSetID.indexOf( "CA " ) == 0)
			iCodeType = CT_T24N;
		else if (sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0)
			iCodeType = CT_S901G;
		else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
			iCodeType = CT_ECBC;
		else
		{	assert( FALSE );	// what ruleset is this ??
	}	}

	// initialize progress dialog settings
	if (iCodeType == CT_T24N)
	{	if (bParallelSimulations)
				SetCECNResProgressVal_Parallel( true, true, true );
		else	SetCECNResProgressVal_Serial( true, true, true, true );
	}
	else
	{	if (bParallelSimulations)
				SetS901GProgressVal_Parallel( true, true, true );
		else	SetS901GProgressVal_Serial( true, true, true, true );
	}

// SAC 5/5/15 - ResultSummary Logging
			if (bVerbose || !bVerbose)
			//					if (bVerbose)
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
										{	case  0 :	sLogMsg.sprintf( "       BEMBasePathFile    = %s", (pszBEMBasePathFile == NULL ? "(null)" : (strlen( pszBEMBasePathFile ) < 1 ? "(empty)" : pszBEMBasePathFile)) );	  break;
											case  1 :	sLogMsg.sprintf( "       RulesetPathFile    = %s", (pszRulesetPathFile == NULL ? "(null)" : (strlen( pszRulesetPathFile ) < 1 ? "(empty)" : pszRulesetPathFile)) );     break;
											case  2 :	sLogMsg.sprintf( "       SimWeatherPath     = %s", (pszSimWeatherPath  == NULL ? "(null)" : (strlen( pszSimWeatherPath  ) < 1 ? "(empty)" : pszSimWeatherPath )) );     break;
											case  3 :	sLogMsg.sprintf( "       CompMgrDLLPath     = %s", (pszCompMgrDLLPath  == NULL ? "(null)" : (strlen( pszCompMgrDLLPath  ) < 1 ? "(empty)" : pszCompMgrDLLPath )) );     break;
											case  4 :	sLogMsg.sprintf( "       DHWWeatherPath     = %s", (pszDHWWeatherPath  == NULL ? "(null)" : (strlen( pszDHWWeatherPath  ) < 1 ? "(empty)" : pszDHWWeatherPath )) );     break;
											case  5 :	sLogMsg.sprintf( "       ProcessingPath     = %s", (pszProcessingPath  == NULL ? "(null)" : (strlen( pszProcessingPath  ) < 1 ? "(empty)" : pszProcessingPath )) );     break;
											case  6 :	sLogMsg.sprintf( "       ModelPathFile      = %s", (pszModelPathFile   == NULL ? "(null)" : (strlen( pszModelPathFile   ) < 1 ? "(empty)" : pszModelPathFile  )) );     break;
											case  7 :	sLogMsg.sprintf( "       LogPathFile        = %s", (pszLogPathFile     == NULL ? "(null)" : (strlen( pszLogPathFile     ) < 1 ? "(empty)" : pszLogPathFile    )) );     break;
											case  8 :	sLogMsg.sprintf( "       UIVersionString    = %s", (pszUIVersionString == NULL ? "(null)" : (strlen( pszUIVersionString ) < 1 ? "(empty)" : pszUIVersionString)) );     break;
											case  9 :	sLogMsg.sprintf( "       LoadModelFile      = %s", (bLoadModelFile   ? "true" : "false") );		break;
											case 10 :	sLogMsg.sprintf( "       OptionsCSV         = %s", (pszOptionsCSV      == NULL ? "(null)" : (strlen( pszOptionsCSV      ) < 1 ? "(empty)" : sOptsCSV.toLocal8Bit().constData() )) );     break;
											case 11 :	sLogMsg.sprintf( "       ErrorMsg           = %s", (pszErrorMsg        == NULL ? "(null)" : (iErrorMsgLen > 0 ? "(assumed to be initialized)" : "(unused)"    )) );     break;
											case 12 :	sLogMsg.sprintf( "       ErrorMsgLen        = %d", iErrorMsgLen );										break;
											case 13 :	sLogMsg.sprintf( "       DisplayProgress    = %s", (bDisplayProgress ? "true" : "false") );     break;
											case 14 :	sLogMsg.sprintf( "       ResultsSummary     = %s", (pszResultsSummary  == NULL ? "(null)" : (strlen( pszResultsSummary  ) < 1 ? "(empty)" : pszResultsSummary )) );     break;
											case 15 :	sLogMsg.sprintf( "       ResultsSummaryLen  = %d", iResultsSummaryLen );     break;
											case 16 :	sLogMsg.sprintf( "       pProgCallbackFunc  = %s", (pAnalProgCallbackFunc == NULL ? "(null)" : "(assumed to be initialized)") );     break;
											default :	sLogMsg.clear();		break;
										}
										if (!sLogMsg.isEmpty())
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}	}

	SetOSWrapLogFlag( bVerbose );
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
	if (bLoadModelFile && !bAbort)
	{
		if (!sBEMBasePathFile.isEmpty())
		{	assert( !sRulesetPathFile.isEmpty() );  // if (re)loading BEMBase, we must also reload ruleset
								if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Initializing BEMBase", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!FileExists( sBEMBasePathFile.toLocal8Bit().constData() ))
			{	sErrMsg.sprintf( "ERROR:  BEMBase (building data model) definitions file not found:  %s", sBEMBasePathFile.toLocal8Bit().constData() );
//											 1 : pszBEMBasePathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 1 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (sRulesetPathFile.isEmpty() || !FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg.sprintf( "ERROR:  BEM ruleset file not found:  %s", (!sRulesetPathFile.isEmpty() ? sRulesetPathFile.toLocal8Bit().constData() : "(not specified)") );
//											 2 : pszRulesetPathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 2 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (!CMX_LoadDataModel( sBEMBasePathFile.toLocal8Bit().constData(), BEMT_CBECC ))	// was: CMX__ReInitBEMProc( sBEMBasePathFile, BEMT_CBECC ))
			{	sErrMsg.sprintf( "ERROR:  BEMBase (building data model) (re)initialization:  %s", sBEMBasePathFile.toLocal8Bit().constData() );
//											31 : Error initializing building model database
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 31 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}
   	
		if (iRetVal == 0 && !sRulesetPathFile.isEmpty())
		{						if (bVerbose)
									BEMPX_WriteLogFile( "  PerfAnal_NRes - Initializing ruleset", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			if (!FileExists( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg.sprintf( "ERROR:  BEM ruleset file not found:  %s", sRulesetPathFile.toLocal8Bit().constData() );
//											 2 : pszRulesetPathFile doesn't exist
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 2 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
			else if (!CMX_LoadRuleset( sRulesetPathFile.toLocal8Bit().constData() ))
			{	sErrMsg.sprintf( "ERROR:  Ruleset loading error encountered:  %s", sRulesetPathFile.toLocal8Bit().constData() );
//											32 : Error loading analysis ruleset
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 32 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}

		if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))	// SAC 10/2/14 - RESET iCodeType based on newly loaded ruleset
		{	if (sLoadedRuleSetID.indexOf( "CA " ) == 0)
				iCodeType = CT_T24N;
			else if (sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0)
				iCodeType = CT_S901G;
			else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
				iCodeType = CT_ECBC;
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
				{	sErrMsg.sprintf( "ERROR:  Processing log path/file exceeds maximum length of %d:  %s", BEMDEF_MAXLOGFILELINE, sLogPathFile.toLocal8Bit().constData() );
//											 5 : Invalid project log file name (too long)
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 5 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
				else if (!BEMPX_WriteLogFile( "checking log write", sLogPathFile.toLocal8Bit().constData(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ))
				{	sErrMsg.sprintf( "ERROR:  Error encountered writing message to log file:  %s", sLogPathFile.toLocal8Bit().constData() );
//											 6 : Error writing to project log file
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 6 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
			}
			if (iRetVal == 0)
			{	// assumes BEMBase cleared out and ruleset re-loaded
				if (sModelPathFile.isEmpty() || !FileExists( sModelPathFile.toLocal8Bit().constData() ))
				{	sErrMsg.sprintf( "ERROR:  Building model (project) file not found:  %s", (!sModelPathFile.isEmpty() ? sModelPathFile.toLocal8Bit().constData() : "(not specified)") );
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

								if (bVerbose)
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
						sErrMsg.sprintf( "ERROR:  Error encountered reading building model (project) file:  %s", sModelPathFile.toLocal8Bit().constData() );
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
						{	sErrMsg.sprintf( "ERROR:  %d Error(s) encountered reading building model (input/project) file:  %s", iNumBEMBaseErrors, sModelPathFile.toLocal8Bit().constData() );
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
	}

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
										{	sLogMsg.sprintf( "  PerfAnal_NRes - Analysis DLL CodeYear %d / Ruleset CodeYear %d", iDLLCodeYear, iRulesetCodeYear );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
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
	}

  // SAC 8/23/18 - moved up from below initial defaulting for newly opened model to ensure certain properties (CSE_Name) are defauted before being retrieved/referenced
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && bLoadModelFile)
   	// SAC 4/4/14 - added call to defaulting stuff for models just loaded to ensure all defaults present prior to PolyLp generation
		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

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
								sTemp.sprintf( "\n          %s", saDevOptsObjProps[iDOOPIdx].toLocal8Bit().constData() );
							else
								sTemp.sprintf( "\n          %s '%s' %s", saDevOptsObjProps[iDOOPIdx].left(iColonIdx).toLocal8Bit().constData(), sDOObjName.toLocal8Bit().constData(), 
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
									sTemp.sprintf( "project %s", saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 ).toLocal8Bit().constData() );
								else
									sTemp.sprintf( "%s %s", saDevOptsObjProps[iDOOPIdx].left(iColonIdx).toLocal8Bit().constData(), 
																	saDevOptsObjProps[iDOOPIdx].right( saDevOptsObjProps[iDOOPIdx].length() - iColonIdx - 1 ).toLocal8Bit().constData() );
								sDevOptsNotDefaultedAbbrev += sTemp;
							}
							iLastDevOptClassIdx = iCID;
			}	}	}	}
		}
		if (!sDevOptsNotDefaulted.isEmpty())
		{	QString sDevOptsNotDefaultedMsg = "Warning:  The following developer options must be defaulted (not specified by the user) in order to perform a valid compliance analysis:" + sDevOptsNotDefaulted;
			BEMPX_WriteLogFile( sDevOptsNotDefaultedMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}
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
#define  MAX_FileHashID  50
	int iNumFileHashErrs = 0;
	if (iCodeType == CT_S901G || iCodeType == CT_ECBC)
		bBypassValidFileChecks = true;	// SAC 12/23/14 - turn OFF file hash checks for S901G analyses
	if (!bAbort && !BEMPX_AbortRuleEvaluation())
	{	if (bBypassValidFileChecks)
			BEMPX_WriteLogFile( "  PerfAnal_NRes - Bypassing file validity checks", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		else
		{	QString sFHPathFile, sFHErrMsg; 
			bool bLogEachFileHashError = (bVerbose);
			bool bRequiredForCodeYear = true;
			for (long iFHID=1; (iRetVal == 0 && iFHID <= MAX_FileHashID); iFHID++)
			{	bRequiredForCodeYear = true;
			// SAC 1/14/17 - updated file hash table for 2016/19 analysis (using new open source exes)
				switch (iFHID)
				{	case  1 :	BEMPX_GetBEMBaseFile( sFHPathFile );                              bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
					case  2 :	sFHPathFile = sCompMgrDLLPath + "BEMCmpMgr16c.dll";               bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;   // SAC 3/6/14 - revised ALL to reference more specific paths
					case  3 :	sFHPathFile = sCompMgrDLLPath + "BEMProc16c.dll";                 bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
					case  4 :	sFHPathFile = sCompMgrDLLPath + "OS_Wrap16.dll";                  bRequiredForCodeYear = (iDLLCodeYear == 2016);		break;
					case  5 :	sFHPathFile = sCompMgrDLLPath + "libeay32.dll";   				      bRequiredForCodeYear = false;  							break;	// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
					case  6 :	sFHPathFile = sCompMgrDLLPath + "ssleay32.dll";     				   bRequiredForCodeYear = false;  							break;	// SAC 12/24/15 - remove check on SSL DLLs, as they may not be in same EXE directory as other EXE/DLLs
					case  7 :	sFHPathFile = sCompMgrDLLPath + "openstudio_analysis.dll";        break;
					case  8 :	sFHPathFile = sCompMgrDLLPath + "openstudio_analysisdriver.dll";  break;
					case  9 :	sFHPathFile = sCompMgrDLLPath + "openstudio_energyplus.dll";      break;
					case 10 :	sFHPathFile = sCompMgrDLLPath + "openstudio_gbxml.dll";           break;  // SAC 12/3/14 - added
					case 11 :	sFHPathFile = sCompMgrDLLPath + "openstudio_isomodel.dll";        break;  // SAC 11/11/13 - added
					case 12 :	sFHPathFile = sCompMgrDLLPath + "openstudio_model.dll";           break;
					case 13 :	sFHPathFile = sCompMgrDLLPath + "openstudio_osversion.dll";       break;
					case 14 :	sFHPathFile = sCompMgrDLLPath + "openstudio_project.dll";         break;
					case 15 :   sFHPathFile = sCompMgrDLLPath + "openstudio_radiance.dll";        break;
					case 16 :   sFHPathFile = sCompMgrDLLPath + "openstudio_ruleset.dll";         break;
					case 17 :   sFHPathFile = sCompMgrDLLPath + "openstudio_runmanager.dll";      break;
					case 18 :   sFHPathFile = sCompMgrDLLPath + "openstudio_sdd.dll";             break;
					case 19 :   sFHPathFile = sCompMgrDLLPath + "openstudio_utilities.dll";       break;
					case 20 :   sFHPathFile = sCompMgrDLLPath + "qtwinmigrate.dll";               break;
					case 21 :   sFHPathFile = sCompMgrDLLPath + "zkexpat.dll";                    break;
					case 22 :	sFHPathFile = sCompMgrDLLPath + "qwt.dll";                        bRequiredForCodeYear = false;  							break;	// SAC 8/27/17 - removed (not req'd for analysis)
					case 23 :	sFHPathFile = sCompMgrDLLPath + "Qt5Cored.dll";                   break;  // SAC 12/3/14 - revised for Qt5
					case 24 :	sFHPathFile = sCompMgrDLLPath + "Qt5Guid.dll";                    break;
					case 25 :	sFHPathFile = sCompMgrDLLPath + "Qt5Networkd.dll";                break;
					case 26 :	sFHPathFile = sCompMgrDLLPath + "Qt5Sqld.dll";                    break;
					case 27 :	sFHPathFile = sCompMgrDLLPath + "Qt5WebKitd.dll";                 break;
					case 28 :	sFHPathFile = sCompMgrDLLPath + "Qt5Widgetsd.dll";                break;
					case 29 :	sFHPathFile = sCompMgrDLLPath + "Qt5Xmld.dll";                    break;
					case 30 :	sFHPathFile = sCompMgrDLLPath + "Qt5Core.dll";                    break;
					case 31 :	sFHPathFile = sCompMgrDLLPath + "Qt5Gui.dll";                     break;
					case 32 :   sFHPathFile = sCompMgrDLLPath + "Qt5Network.dll";                 break;
					case 33 :   sFHPathFile = sCompMgrDLLPath + "Qt5Sql.dll";                     break;
					case 34 :   sFHPathFile = sCompMgrDLLPath + "Qt5WebKit.dll";                  break;
					case 35 :   sFHPathFile = sCompMgrDLLPath + "Qt5Widgets.dll";                 break;
					case 36 :   sFHPathFile = sCompMgrDLLPath + "Qt5Xml.dll";                     break;
					case 37 :   sFHPathFile = sEPlusPath + "EnergyPlus.exe";          				break;
					case 38 :   sFHPathFile = sEPlusPath + "Energy+.idd";             				break;
					case 39 :   sFHPathFile = sEPlusPath + "energyplusapi.dll";        				break;
					case 40 :   sFHPathFile = sEPlusPath + "EPMacro.exe";               				break;
					case 41 :   sFHPathFile = sEPlusPath + "ExpandObjects.exe";        				break;
					case 42 :   sFHPathFile = sEPlusPath + "ReadVarsESO.exe";	        				break;
					case 43 :	sFHPathFile = sCompMgrDLLPath + "BEMCmpMgr19c.dll";               bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 44 :	sFHPathFile = sCompMgrDLLPath + "BEMProc19c.dll";                 bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 45 :	BEMPX_GetBEMBaseFile( sFHPathFile );			                     bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 46 :   sFHPathFile = sCSEEXEPath + "cse19.exe";	             				bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;	// SAC 5/24/16
					case 47 :   sFHPathFile = sCSEEXEPath + "cse.exe";				       				bRequiredForCodeYear = (iDLLCodeYear <= 2016);		break;
					case 48 :   sFHPathFile = sCSEEXEPath + "calc_bt_control.exe";      				bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					case 49 :   sFHPathFile = sCSEEXEPath + "DHWDU.txt";	           					break;
					case 50 :	sFHPathFile = sCompMgrDLLPath + "OS_Wrap19.dll";                  bRequiredForCodeYear = (iDLLCodeYear == 2019);		break;
					default :			assert( FALSE );                                      		break;
				}
				if (!bRequiredForCodeYear)
				{	// do nothing here - the selected DLL should not be used w/ the CODEYEAR* setting compiled into this DLL
				}
				else if (sFHPathFile.isEmpty() || !FileExists( sFHPathFile.toLocal8Bit().constData() ))
				{	// DO NOTHING - some files expected to be missing - others will prevent success when missing...
										if (bVerbose &&	// SAC 3/6/14 - added verbose logging of this condition
#ifdef _DEBUG
												((iFHID < 30 || iFHID > 36) && iFHID != 47))
#else
												((iFHID < 23 || iFHID > 29) && iFHID != 46))
#endif
										{	if (sFHPathFile.isEmpty())
												sLogMsg.sprintf( "    File to perform hash check on not specified (iFHID = %d)", iFHID );
											else
												sLogMsg.sprintf( "    File to perform hash check on missing (iFHID = %d):  %s", iFHID, sFHPathFile.toLocal8Bit().constData() );
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
						{	sLogMsg.sprintf( "Error computing file hash (analysis continuing w/ report signature disabled) - ComputeSHA256_File() returned %d for file:  %s", iSHA256_RetVal, sFHPathFile.toLocal8Bit().constData() );
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}	}
					else
					{	long lFileHashStatus = 0;
					   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "FileHashID"     , iCID_Proj ), BEMP_Int, (void*) &iFHID     , BEMO_User, 0, BEMS_ProgDefault );
					   BEMPX_SetBEMData( BEMPX_GetDatabaseID( "FileHashToCheck", iCID_Proj ), BEMP_Str, (void*) pHashBuffer, BEMO_User, 0, BEMS_ProgDefault );
						int iFHRetVal = LocalEvaluateRuleset( sFHErrMsg, 48 /*value doesn't matter - not returned*/, "rl_FILEHASHES",	bVerbose, pCompRuleDebugInfo );		// file hash checking
						if (iFHRetVal > 0)
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
							{	sLogMsg.sprintf( "Error evaluating file hash checking rules (analysis continuing w/ report signature disabled) - for file:  %s", sFHPathFile.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
						else if (iFHRetVal == 0 && !BEMPX_GetInteger( BEMPX_GetDatabaseID( "FileHashStatus", iCID_Proj ), lFileHashStatus ))
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
							{	sLogMsg.sprintf( "    File hash check error - invalid Proj:FileHashStatus (%ld) (analysis continuing w/ report signature disabled) - for file:  %s", lFileHashStatus, sFHPathFile.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
						else if (iFHRetVal == 0 && lFileHashStatus != 0)
						{	bSendRptSignature	= false;			iNumFileHashErrs++;
							if (bLogEachFileHashError)
							{	sLogMsg.sprintf( "    File hash check error - failed consistency check (%ld) (analysis continuing w/ report signature disabled) - for file:  %s", lFileHashStatus, sFHPathFile.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
						else if (bVerbose)
						{	if (bLogEachFileHashError)
							{	sLogMsg.sprintf( "    File hash check passed for file:  %s", sFHPathFile.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
				}	}
			}
			if (iNumFileHashErrs > 0 && !bLogEachFileHashError)
			{	sLogMsg.sprintf( "   %d file hash check(s) failed on executable and/or analysis support files (analysis continuing w/ report signature disabled)", iNumFileHashErrs );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashID"     , iCID_Proj ), iError );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashToCheck", iCID_Proj ), iError );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "FileHashStatus" , iCID_Proj ), iError );
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
		{	sErrMsg.sprintf( "Error: Analysis processing path too long:  ", sProcessingPath.toLocal8Bit().constData() );
//											14 : Error encountered initializing weather file locations and/or names
			ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 14 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
		}
		else
		{	if (!DirectoryExists( sProcessingPath ))
				CreateAndChangeDirectory( sProcessingPath.toLocal8Bit().constData(), FALSE );
			if (!DirectoryExists( sProcessingPath ))
			{	sErrMsg.sprintf( "Error: Unable to create or access the analysis processing directory:  ", sProcessingPath.toLocal8Bit().constData() );
//												15 : Error creating or accessing the analysis processing directory
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 15 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
			}
		}
	}

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
					sErrMsg.sprintf( "ERROR:  Building geometry DBID initialization failed:  %s", sCr8PolyLpErrMsg.toLocal8Bit().constData() );
//											43 : Error encountered initializing building geometry DBIDs
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 43 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
			else
			{	// start by deleting ALL existing PolyLp objects
				int iNumPolyLps = BEMPX_GetNumObjects( iCID_PolyLp /*, BEMO_User, iBEMProcIdx*/ );
				if (iNumPolyLps > 0)
				{	sLogMsg.sprintf( "Warning:  Simplified geometry model includes %d PolyLp objects (expecting none)", iNumPolyLps );			assert( FALSE );  // shouldn't ever get here unless user model includes PolyLp objects
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
					sErrMsg.sprintf( "%s  - Unable to generate building geometry for simulation (return code %d)", sCr8PolyLpErrMsg.toLocal8Bit().constData(), iCr8PolyLpRetVal );
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
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Generating shades for %d model windows", lNumWinsHavingShades );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
			QString sGenWinShadesErrMsg;
			if (!BEMPX_InitGeometryIDs( sGenWinShadesErrMsg ))
			{	if (sGenWinShadesErrMsg.isEmpty())
					sErrMsg = "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades)";
				else
					sErrMsg.sprintf( "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades):  %s", sGenWinShadesErrMsg.toLocal8Bit().constData() );
//											43 : Error encountered initializing building geometry DBIDs
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 43 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
			else
			{
		// before further processing, check all ExtWalls w/ window shades for overlapping windows/doors
				int iWinDoorOverlaps = CMX_WindowDoorOverlaps_CECNonRes( bVerbose, bStoreBEMDetails, bSilent, sGenWinShadesErrMsg );
				if (iWinDoorOverlaps > 0)
				{	sErrMsg.sprintf( "ERROR:  Window(s) and/or Door(s) are overlapping on %d ExtWalls with window shades defined", iWinDoorOverlaps );
//											51 : Window(s) and/or Door(s) are overlapping on ExtWalls with window shades defined
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 51 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
				}
				else if (!sGenWinShadesErrMsg.isEmpty())
				{	sErrMsg.sprintf( "%s  - Checking for window/door overlaps", sGenWinShadesErrMsg.toLocal8Bit().constData() );
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
						sErrMsg.sprintf( "%s  - Unable to generate window shade (return code %d)", sGenWinShadesErrMsg.toLocal8Bit().constData(), iGenWinShadesRetVal );
//													47 : Error encountered in generating window shades
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 47 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
					}
																		if (bStoreBEMDetails)
																		{	sDbgFileName = sProcessingPath + sModelFileOnly + QString(".ibd-Detail-postWinShades");
   																		BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/ );
																		}
			}	}
	}	}

	if (!bAbort && !BEMPX_AbortRuleEvaluation())
   {	// moved defaulting stuff to subordinate routine to enable multiple calls
		DefaultModel_CECNonRes( iPrevRuleErrs, sUIVersionString, iRetVal, bVerbose, pCompRuleDebugInfo, iDontAbortOnErrorsThruStep, iNumFileOpenDefaultingRounds );

	// SAC 10/3/14 - mod to delete any EUseSummary objects from user model to avoid having them written to the results' user model
		int iNumEUseSUmObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "EUseSummary" ) );
		for (int iEUSidx=0; iEUSidx < iNumEUseSUmObjs; iEUSidx++)
		{	BEMObject* pEUSObj = BEMPX_GetObjectByClass( BEMPX_GetDBComponentID( "EUseSummary" ), iError, iEUSidx );			assert( pEUSObj );
			if (pEUSObj)
				BEMPX_DeleteObject( pEUSObj );
		}
	}

	if (!bAbort && !sXMLResultsFileName.isEmpty() && FileExists( sXMLResultsFileName ))
	{	sMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
	                "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Abort' to abort the %s.", "analysis results XML", sXMLResultsFileName.toLocal8Bit().constData(), "analysis" );
		if (!OKToWriteOrDeleteFile( sXMLResultsFileName.toLocal8Bit().constData(), sMsg ))
		{	sErrMsg.sprintf( "Analysis aborting - user chose not to overwrite analysis results XML file:  %s", sXMLResultsFileName.toLocal8Bit().constData() );
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

	bool bResearchMode = false;
	bool bProposedOnly = false;		// SAC 9/6/13
	BOOL bCompletedAnalysisSteps = FALSE;
	long lQuickAnalysis = 0;		// SAC 11/8/14
	QString sReadVarsESOexe, sReadVarsESOrvi;		// SAC 4/11/16
	QString sExcptDsgnModelFile;	// SAC 12/19/14
	QString sAnnualWeatherFile;
	long lNumSpaceWithDefaultedDwellingUnitArea = 0;	// SAC 6/1/16
	QString sCACertPath;
	GetDLLPath( sCACertPath );
	if (sCACertPath[sCACertPath.length()-1] == '\\')
		sCACertPath = sCACertPath.left( sCACertPath.length()-1 );
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
			if ((bProposedOnly || bResearchMode) && iAnalysisThruStep > 7)
			{	iAnalysisThruStep = 7;
											sLogMsg.sprintf( "  PerfAnal_NRes - AnalysisThruStep being set to #%d due to Proj:AnalysisType = %s", iAnalysisThruStep, sATcopy.toLocal8Bit().constData() );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}

		// further defaulting/setup of CompReport* booleans
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportPDFWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportXMLWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMPX_DefaultProperty( BEMPX_GetDatabaseID( "CompReportStdWritten", iCID_Proj ), iError );   //, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			if (bResearchMode || bProposedOnly)
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
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Forcing QuickAnalysis setting to %d", lQuickAnalysisOption );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
			lQuickAnalysis = lQuickAnalysisOption;
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "QuickAnalysis", iCID_Proj ), BEMP_Int, (void*) &lQuickAnalysis );
			bReDefaultModel = TRUE;
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
					sLogMsg.sprintf( "SimOutputVariablesToCSV option(s) disabled due to error copying RVI file: '%s' to '%s'", sReadVarsESOrviFrom.toLocal8Bit().constData(), sReadVarsESOrvi.toLocal8Bit().constData() );
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
					sErrMsg.sprintf( "Exceptional Design IDF Error:  IDF path/filename specified by UseExcptDsgnModel not found:  %s", sExcptDsgnModelFile.toLocal8Bit().constData() );
				}
				else if (lQuickAnalysis > 0)
				{	iLocalErr = 50;
//											50 : Exceptional Design IDF specification and the Quick Analysis feature cannot both be activated
					sErrMsg = "Exceptional Design IDF specification and the Quick Analysis feature cannot both be activated for a single run";
				}
				if (iLocalErr > 0)
				{	ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iLocalErr /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
					sExcptDsgnModelFile.clear();
				}
			}
			else
			{	QString sExcptDsgnModelFileMsg;
				sExcptDsgnModelFileMsg.sprintf( "Exceptional Design simulation input used in analysis:  ", sExcptDsgnModelFile.toLocal8Bit().constData() );
				BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ExcptDsgnModelFileMsg", iCID_Proj ), BEMP_QStr, (void*) &sExcptDsgnModelFileMsg, BEMO_User, 0, BEMS_ProgDefault );
			}
		}

// SAC 6/1/16 - added check used to disable report security if any DwellingUnitArea values used in analysis are defaulted by the ruleset
		long lDBID_Proj_DefDwellUnitArea = BEMPX_GetDatabaseID( "DefaultedDwellingUnitArea", iCID_Proj );		assert( lDBID_Proj_DefDwellUnitArea > 0 );
		if (lDBID_Proj_DefDwellUnitArea > 0)
			BEMPX_GetInteger( lDBID_Proj_DefDwellUnitArea, lNumSpaceWithDefaultedDwellingUnitArea );

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
				sErrMsg.sprintf( "Error encountered initializing weather file locations and/or names for path:  %s", sSimWeatherPath.toLocal8Bit().constData() );
//											14 : Error encountered initializing weather file locations and/or names
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 14 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
		}	}

	// SAC 9/9/18 - store certain path and filenames to BEMBase for reference during analysis (ported from Res analysis)
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
					sErrMsg.sprintf( "Error:  Unable to compute hash of simulation annual weather (EPW) on:  %s", sAnnualWeatherFile.toLocal8Bit().constData() );
				else if (iSHA256_DDYWthr_RetVal != 0)
					sErrMsg.sprintf( "Error:  Unable to compute hash of simulation design day (DDY) on:  %s", sDDWeatherFile.toLocal8Bit().constData() );
				else
					sErrMsg = "Error:  Unknown error encountered setting up check of weather & design day file hashes";
//												40 : Error setting up check of weather & design day file hashes
				ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 40 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}
		}

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
												int iRuleDetailIdx = qsErrTmp.indexOf( "evaluating rule: " );
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
			#define  NumCantGenRpts  5
				int iCantGenRptIdx[NumCantGenRpts];
				bool bCantGenRpt[] = {	!FileExists( sXMLResultsFileName.toLocal8Bit().constData() ),
												false,	// defined below - check for report gen website not accessible
												false,	// defined below - check for report gen offline
												!sIDFToSimulate.isEmpty(),
												(pbBypassOpenStudio[0] || pbBypassOpenStudio[1] || pbBypassOpenStudio[2] || pbBypassOpenStudio[3])  };
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
					//	sLogMsg.sprintf( "Compliance report(s) called for but bypassed due to %s.", (iRptGenAvail<0 ? "report generation being offline" : "report generator website not accessible") );
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
							{	case  0 :	sLogMsg.sprintf( "      XML results file not found:  %s", sXMLResultsFileName.toLocal8Bit().constData() );						break;
								case  1 :	sLogMsg =       "      report generator website not accessible";											break;
								case  2 :	sLogMsg =       "      report generator offline";																break;
								case  3 :	sLogMsg =       "      IDF file specified in analysis options overriding compliance models";		break;
								case  4 :	sLogMsg =       "      one or more OpenStudio/EnergyPlus simulations being bypassed";				break;
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
			#define  NumRptSecOff  16
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
													(iNumFileOpenDefaultingRounds != 3)  };	// number of model defaulting rounds overridden by user - SAC 4/11/18 
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
								{	case  0 :	sLogMsg.sprintf( "      %d file hash check(s) failed on executable and/or analysis support files (see log file for details)", iNumFileHashErrs );		break;
									case  1 :	sLogMsg.sprintf( "      inconsistency between software library year (%d) and ruleset code year (%d)", iDLLCodeYear, iRulesetCodeYear );		break;
									case  2 :	sLogMsg =        "      input checks being bypassed";		break;
									case  3 :	sLogMsg =        "      unmet load hour checks being bypassed";		break;
									case  4 :	sLogMsg =        "      pre-analysis check rules being bypassed";		break;		// SAC 1/25/19 (tic #2924)
									case  5 :	sLogMsg =        "      simulation check rules being bypassed";		break;
									case  6 :	sLogMsg =        "      energy code checking rules being bypassed";		break;
									case  7 :	sLogMsg =        "      the override of equipment auto-sizing in one or more simulations";		break;
									case  8 :	sLogMsg =        "      the QuickAnalysis option being activated";		break;
									case  9 :	sLogMsg =        "      file read errors being ignored";		break;
									case 10 :	sLogMsg =        "      file validity (hash) checks being bypassed";		break;
									case 11 :	sLogMsg.sprintf( "      developer options being activated: %s (see log file for details)", sDevOptsNotDefaultedAbbrev.toLocal8Bit().constData() );		break;
//	QString sDevOptsNotDefaulted;
//	QString saDevOptsObjProps[] = {	"Proj:DisableDayltgCtrls", "Proj:DefaultDayltgCtrls", "Proj:AutoHardSize", "Proj:AutoEffInput", " " };		// SAC 8/12/14 - updated w/ latest dayltg flags
//	double faDevOptsPropOKVals[] = {               0,                         0,                      0,                      0           };
									case 12 :	sLogMsg =        "      user specification of alternative proposed simulation IDF file";		break;
									case 13 :	sLogMsg.sprintf( "      user specification of %s include file(s): %s", qsCSEName.toLocal8Bit().constData(), sCSEIncludeFileDBID.toLocal8Bit().constData() );		break;
									case 14 :	sLogMsg.sprintf( "      %d dwelling unit space(s) with defaulted information in the Dwelling Unit Data tab", lNumSpaceWithDefaultedDwellingUnitArea );		break;
							//		case 14 :	sLogMsg.sprintf( "      presence of %d space(s) with defaulted residential dwelling unit areas (Spc:DwellUnitTypeArea[*])", lNumSpaceWithDefaultedDwellingUnitArea );
//	case 12 :	sLogMsg.sprintf( "      presence of %d space(s) with defaulted residential dwelling unit areas (Spc:DwellUnitTypeArea[*])", lNumSpaceWithDefaultedDwellingUnitArea );
									case 15 :	sLogMsg =        "      mandatory U-factor checks disabled";		break;	// SAC 2/7/17
									case 16 :	sLogMsg.sprintf( "      number of model defaulting rounds overridden by user (%d entered, 3 required)", iNumFileOpenDefaultingRounds );		break;	// SAC 4/11/18
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
					// display report issues dialog
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
					showDetailsInQMessageBox(msgBox, 770, 300);		// routine to OPEN Details (to start with) + resize text box (to larger size)
					bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);
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
			{						if (bVerbose)
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
											sLogMsg.sprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
		}
	}

		// BEFORE writing SDD XML file, evaluate rulelist that does certain OSM-prep, incl. creating & assigning ThrmlEngyStor:DischrgSchRef, ChrgSchRef & ChlrOnlySchRef based on ModeSchRef
			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation() && iRetVal == 0 &&
				 BEMPX_RulelistExists( "ProposedModelPrep" ))
			{
				int iOSTPRetVal = LocalEvaluateRuleset( sErrMsg, 67, "ProposedModelPrep", bVerbose, pCompRuleDebugInfo );
//											67 : Error evaluating ProposedModelPrep rules
				if (iOSTPRetVal != 0 || BEMPX_AbortRuleEvaluation())
//					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 67 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 67 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 1 /*iStepCheck*/ );
			}

	QVector<QString> saSimulatedRunIDs;
	double dEPlusVer=0.0;	// SAC 5/16/14
	char pszEPlusVerStr[60] = "\0";
	char pszOpenStudioVerStr[60] = "\0";
	QString sCSEVersion;  // SAC 10/10/16
	bool bHaveResult=false, bResultIsPass=false;
	QString sResTemp1, sResTemp2;
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

		if (bResearchMode || bProposedOnly)  // SAC 11/22/16 - was: iNumRuns < 4)
		{	// second round of progress dialog setting initialization
			if (iCodeType == CT_T24N)
			{	if (bParallelSimulations)
						SetCECNResProgressVal_Parallel( false, true, true );
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
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunDateFormatted", iCID_Proj ), BEMP_QStr, (void*) &sRunDateFmt );
			BEMPX_GetString( lDBID_RunDate, sRunDateFmt, FALSE, -3 /*iPrecision*/ );	// SAC 5/16/18 - added new '-3' format to handle output as ISO (xsd:datetime) string  // SAC 9/10/18 - ported from Res
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "RunDateISO", iCID_Proj ), BEMP_QStr, (void*) &sRunDateFmt );
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

								if (bVerbose)
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
		if (bProposedOnly)  // SAC 11/22/16 - new logic to handle bProposedOnly analysis
		{	if (iCodeType == CT_T24N)
			{	assert( iNumRuns == 4 );
				bModelToBeSimulated[1] = false;  bModelToBeSimulated[3] = false;  // toggle OFF baseline sizing and annunal runs
			}
			else	// S901G or ECBC		- SAC 8/21/15
			{	bModelToBeSimulated[1] = false;  bModelToBeSimulated[2] = false;  bModelToBeSimulated[3] = false;  bModelToBeSimulated[4] = false;	// toggle OFF baseline runs by orientation
				bModelToBeSimulated[6] = false;  bModelToBeSimulated[7] = false;  bModelToBeSimulated[8] = false;  bModelToBeSimulated[9] = false;
		}	}

		int iLastHrlyStorModelIdx = -1;
//		bool bThisOSSimSkipped = false, bLastOSSimSkipped = false;	// SAC 4/18/14
		bool bSimRunsNow = false;	// SAC 8/19/15 - added to facilitate more than 2 simulations at a time (for 90.1 baseline orientation sim/averaging)
		int iSimRunIdx = 0, iSimRun, iProgressModelSum=0;
		QString sErrMsgShortenedToFit;
		long lZEROCode=0;			QString sZeroCdHrlyExportPathFile;		bool bZCHrlyFileWritten = false;		// SAC 9/8/18

// ----------
// RUN LOOP
// ----------
		for (iRun=0; (!bAbort && !BEMPX_AbortRuleEvaluation() && !bCompletedAnalysisSteps && iRun < iNumRuns); iRun++)
		{
//			bLastOSSimSkipped = bThisOSSimSkipped;		// SAC 4/18/14
//			bThisOSSimSkipped = false;
			QString sProjFileAlone = sModelFileOnly;
			BOOL bCallOpenStudio = TRUE;
			BOOL bSimulateModel = bModelToBeSimulated[iRun];  // SAC 11/22/16 - was: TRUE;
			bool bStoreHourlyResults = false;
			QString sRunID, sRunIDLong;
			int iProgressModel=0, iSizingRunIdx=-1, iAnalStep=-1, iModelGenErr=0, iResultRunIdx=0, iSimErrID=0, iResErrID=0;		//, iProgressModel2=0;
			if (iCodeType == CT_T24N)
			{	switch (iRun)
				{	case  1 :				sRunID = "zb";			sRunIDLong = "Standard Sizing";		bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_zb;									iAnalStep = 3;		iResultRunIdx = 1;	iModelGenErr = 18;	iSimErrID = 24;		iResErrID = 27;	/*siOSWrapProgressIndex = CNRP_StdSizSim;*/		break;
					case  2 :				sRunID = "ap";			sRunIDLong = "Proposed";				bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[3]);		iProgressModel = BCM_NRP_Model_ap;		iSizingRunIdx = 0;	iAnalStep = 4;		iResultRunIdx = 0;	iModelGenErr = 17;	iSimErrID = 25;		iResErrID = 28;	/*siOSWrapProgressIndex = CNRP_PropSim;*/			break;
					case  3 :				sRunID = "ab";			sRunIDLong = "Standard";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_ab;		iSizingRunIdx = 1;	iAnalStep = 6;		iResultRunIdx = 1;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	/*siOSWrapProgressIndex = CNRP_StdAnnSim;*/		break;
					default :	if (bResearchMode)
											{	sRunID = "r";			sRunIDLong = "Research";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_u;																																										/*siOSWrapProgressIndex = CNRP_PropSizSim;*/	}
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
					case  9 :				sRunID = "ab4";		sRunIDLong = "Baseline4";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRAP_Model_ab4;	iSizingRunIdx = 4;	iAnalStep = 6;		iResultRunIdx = 4;	iModelGenErr = 19;	iSimErrID = 26;		iResErrID = 29;	break;
					default :	if (bResearchMode)
											{	sRunID = "r";			sRunIDLong = "Research";				bSimRunsNow = bSimulateModel;																				iProgressModel = BCM_NRP_Model_u   ;														}
									else	{	sRunID = "zp";			sRunIDLong = "Proposed Sizing";		bSimRunsNow = bSimulateModel && (!bParallelSimulations || !bModelToBeSimulated[1]);		iProgressModel = BCM_NRAP_Model_zp ;								iAnalStep = 2;		iResultRunIdx = 0;	iModelGenErr = 16;	iSimErrID = 45;		iResErrID = 46;	}	break;
			}	}
							assert( iSizingRunIdx < 5 );	// otherwise above bSizingRunSimulated array requires re-sizing

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

								if (bVerbose)
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Preparing model %s", sRunID.toLocal8Bit().constData() );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
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
				   bModelOK  = CMX_TransformModel( sRunID.toLocal8Bit().constData(), TRUE /*bEvalRules*/, bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/,
				   											sDbgFileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );
				else
				{  int iThisRunBEMProcIdx = BEMPX_GetTransformIndex( sRunID.toLocal8Bit().constData() );		assert( iThisRunBEMProcIdx > 0 );
					if (BEMPX_GetActiveModel() != iThisRunBEMProcIdx)
						BEMPX_SetActiveModel( iThisRunBEMProcIdx );
					if (iSizingRunIdx >= 0 && bSizingRunSimulated[iSizingRunIdx])
					{	long laDBIDsToBypassCopy[21] = {  0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,  0 };
  						int iTransIdx = BEMPX_GetTransformInitializationInfo( sRunID.toLocal8Bit().constData(), &iBEMProcIdxToCopy, laDBIDsToBypassCopy, 20 );				assert( iTransIdx >= 0 );
						bCopySizingResultsOK = CMX_CopySizingResults_CECNonRes( iBEMProcIdxToCopy, iThisRunBEMProcIdx, bVerbose /*bVerboseOutput*/ );
					}
			   	bModelOK  = CM_EvaluateModelRules( sRunID.toLocal8Bit().constData(), bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/, 
			   													sDbgFileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );		assert( bModelOK );
				}
				if (bModelOK && bPurgeUnreferencedObjects)
					// Purge user-defined non-parent/child components which are not referenced  - SAC 8/12/13 - added to prevent simulation of objects that are not referenced in the building model
					BEMPX_PurgeUnreferencedComponents();
				if (iAnalysisThruStep < iAnalStep)
				{	bCompletedAnalysisSteps = TRUE;
										sLogMsg.sprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep );
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				else if (iNumBypassItems > iRun && pbBypassOpenStudio && pbBypassOpenStudio[iRun])  // ReadProgInt( "options", "BypassOpenStudio_**", 0 ) > 0)
					bCallOpenStudio = FALSE;

				if (!bCopySizingResultsOK)
				{	sErrMsg.sprintf( "Error copying equipment sizes/flows from %d to '%s' model", iBEMProcIdxToCopy, sRunID.toLocal8Bit().constData() );
//											36 : Error copying equipment sizes/flows from source model
					if (iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 36 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
				}
				if (!bModelOK && iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
				{	assert( FALSE ); // shouldn't ever get here since we are no longer generating pz model
					sErrMsg.sprintf( "Error generating %s model", sRunIDLong.toLocal8Bit().constData() );
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
							{	sLogMsg.sprintf( "  PerfAnal_NRes - Bypassing OpenStudio due to Simulate flag in BEMBase toggled off (%s)", sRunID.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}
				}
				else if (bCallOpenStudio && !bSimulateModel)
					bCallOpenStudio = FALSE;	// SAC 11/22/16 - ensure no sim of models when in ProposedOnly mode

			// check for any SUBSEQUENT transforms that initialize to this one and init them (w/out rule evaluation) PRIOR to performing simulation & retrieving results
								if (bVerbose)
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Checking for subsequent model init (%s)", sRunID.toLocal8Bit().constData() );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
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
								sDbgRun2FileName.sprintf( "%s%s - %s.ibd-Detail", sProcessingPath.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunID2.toLocal8Bit().constData() );
							bModelInitialized[iRun2] = CMX_TransformModel( sRunID2.toLocal8Bit().constData(), FALSE /*bEvalRules*/, bVerbose /*bLogRuleEvaluation*/, bVerbose /*bVerboseOutput*/, 
																							sDbgRun2FileName.toLocal8Bit().constData(), bDurationStats, pCompRuleDebugInfo );

							if (!bModelInitialized[iRun2])
							{	sErrMsg.sprintf( "Error generating %s model", sRunID2Long.toLocal8Bit().constData() );
//											44 : Error initializing Proposed model
//											20 : Error initializing Standard Sizing model
//											21 : Error initializing Standard (final) model
						//		if ((iRun2==1 && iDontAbortOnErrorsThruStep < 3) || (iRun2==2 && iDontAbortOnErrorsThruStep < 6) || (iRun2==3 && iDontAbortOnErrorsThruStep < 6))  // check flag to bypass errors
								if (iDontAbortOnErrorsThruStep < iAnalStep2)  // check flag to bypass errors
									ProcessAnalysisError( sErrMsg, bAbort, iRetVal, iModel2InitErr /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, 6 /*iStepCheck*/ );
							}
							else
						// code to evaluate rulelist FOLLOWING model transformation (for now to facilitate Res DHW baseline via modified CBECC-Res rules) - SAC 8/17/18 (Com tic #2675)
							{	QString sResDHWBaselineRulelistName;
								BEMPX_GetString( BEMPX_GetDatabaseID( "ResDHWBaselineRulelistName", iCID_Proj ), sResDHWBaselineRulelistName );
								if (sResDHWBaselineRulelistName.length() > 0)
								{	if (!BEMPX_RulelistExists( sResDHWBaselineRulelistName.toLocal8Bit().constData() ))
									{	sLogMsg.sprintf( "Warning:  ResDHWBaselineRulelist '%s' not found in ruleset.", sResDHWBaselineRulelistName.toLocal8Bit().constData() );
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
									else
									{
		// debugging
		sLogMsg.sprintf( "Evaluating ResDHWBaselineRulelist '%s' on model %d (iCurActiveBEMProcIdx %d).", sResDHWBaselineRulelistName.toLocal8Bit().constData(), BEMPX_GetActiveModel(), iCurActiveBEMProcIdx );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
						QString sResCopyErrMsg;
						int iResCopyRetVal = CM_CopyAnalysisResultsObjects_CECNonRes( sResCopyErrMsg, sRunID.toLocal8Bit().constData(), iLastHrlyStorModelIdx, iCurActiveBEMProcIdx );
						assert( iResCopyRetVal == 0 || !sResCopyErrMsg.isEmpty() );
						if (iResCopyRetVal > 0 &&
							//	((iRun==0 && iDontAbortOnErrorsThruStep < 3) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 6)) )  // check flag to bypass errors
								iDontAbortOnErrorsThruStep < iAnalStep )  // check flag to bypass errors
							iRetVal = (iRetVal > 0 ? iRetVal : iResCopyRetVal);		// DO abort
					}
					iLastHrlyStorModelIdx = iCurActiveBEMProcIdx;
				}
			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation() && plOverrideAutosize[iRun] >= 0)
			{	// OVERRIDE global HVAC autosize flag (if specified in options settings)
		      BEMPX_SetBEMData( BEMPX_GetDatabaseID( "HVACAutoSizing", iCID_Proj ), BEMP_Int, (void*) &plOverrideAutosize[iRun], BEMO_User, 0, BEMS_UserDefined /*???*/ );
			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{

// CHECK FOR FILES TO BE WRITTEN DURING ANALYSIS TO BE WRITABLE  (???)

			}

			if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
			{
				QString sProjSDDFile = sProcessingPath + sProjFileAlone + " - " + sRunID + ".xml";
				sMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
			                "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
								 "(once the file is closed), or \n'Abort' to abort the %s.", "SDD XML", sProjSDDFile.toLocal8Bit().constData(), "analysis" );
				if (!OKToWriteOrDeleteFile( sProjSDDFile.toLocal8Bit().constData(), sMsg ))
				{	sErrMsg.sprintf( "Analysis aborting - user chose not to overwrite SDD XML file:  %s", sProjSDDFile.toLocal8Bit().constData() );
//										22 : Analysis aborted - user chose not to overwrite SDD XML file
					ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 22 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, 1 /*iStepCheck*/ );
				}
				else if (!BEMPX_WriteProjectFile( sProjSDDFile.toLocal8Bit().constData(), BEMFM_SIM, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/,
															FALSE /*bSupressAllMessageBoxes*/, BEMFT_XML /*iFileType*/ ))
				{	sErrMsg.sprintf( "Error: Unable to write %s model SDD XML file:  %s", sRunIDLong.toLocal8Bit().constData(), sProjSDDFile.toLocal8Bit().constData() );
//										23 : Error: Unable to write SDD XML file
				//	if ((iRun==0 && iDontAbortOnErrorsThruStep < 3) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 6))  // check flag to bypass errors
					if (iDontAbortOnErrorsThruStep < iAnalStep)  // check flag to bypass errors
						ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 23 /*iErrID*/, true /*bErrCausesAbort*/, false /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
				}

			// Generate Rule-Based model reports
				if (!bCompletedAnalysisSteps && !bAbort && !BEMPX_AbortRuleEvaluation())
				{	int iModelReportsRetVal = ProcessModelReports( sProjSDDFile.toLocal8Bit().constData(), lDBID_Proj_RuleReportType, BEMPX_GetDatabaseID( "RuleReportFileAppend", iCID_Proj ),
																					-1, true /*bProcessCurrentSelection*/, saModelReportOptions, bVerboseReportRules /*bVerbose*/, bSilent );
					if (iModelReportsRetVal > 0 && bVerbose)
					{	sLogMsg.sprintf( "%d rule-based reports written for model:  %s", iModelReportsRetVal, sProjSDDFile.toLocal8Bit().constData() );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
					else if (iModelReportsRetVal < 0)
					{	// DON'T ABORT ANALYSIS if model report writing fails ???  (just logging message)
						sLogMsg.sprintf( "Error generating rule-based reports (%d) for model:  %s", iModelReportsRetVal, sProjSDDFile.toLocal8Bit().constData() );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
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
									SetCECNResProgressVal_Parallel( (iNumRuns > 3 && (bModelToBeSimulated[0] || bModelToBeSimulated[1]) && (bModelToBeSimulated[2] || bModelToBeSimulated[3])), bModelToBeSimulated[0], bModelToBeSimulated[2] );
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


// SAC 7/23/18 - CSE simulation moved DOWN, INSIDE if() statement launching E+ simulations, so that CSE inputs can include E+ elec use hourly data that feeds into the Battery simulation
//			// SAC 5/27/16 - moved Recirc/Res DHW simulation outside code which gets bypassed due to bCallOpenStudio
//						if (bSimulateModel && bStoreHourlyResults)
//						{  int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ) );
//							int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray" ) );
//							if ((!bBypassRecircDHW && iNumRecircDHWSysObjs > 0) || iNumPVArrayObjs > 0)
//							{
//					// CSE (DHW &/or PVArray/Battery) SIMULATION
//								BOOL bCSESimOK = TRUE;		QString sCSEErrMsg;
//									// perform DHW simulation using CSE and add those results into the hourly results already stored in BEMProc (should be after reading E+ results but before applying TDV multipliers)
//		// --- CSE DHW (&/or PVArray/Battery) simulation based on CECRes analysis ---
//									QString sCSE_DHWUseMthd;
//									BEMPX_GetString( BEMPX_GetDatabaseID( "CSE_DHWUseMthd", iCID_Proj ), sCSE_DHWUseMthd );
//									if (!FileExists( sCSEexe.toLocal8Bit().constData() ))
//									{	sErrMsg.sprintf( "%s (residential DHW/PV/Battery simulation engine) executable not found: '%s'", qsCSEName.toLocal8Bit().constData(), sCSEexe.toLocal8Bit().constData() );		assert( FALSE );
////											54 : CSE (residential DHW & PV/Battery simulation engine) executable(s) not found
//													// SAC 12/18/17 - replaced iDontAbortOnErrorsThruStep w/ '0' to prevent program crash when CSE exe not found
//										ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 54 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, iAnalStep /*iStepCheck*/ );
//									}
//									else if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.isEmpty())
//									{	sErrMsg.sprintf( "%s (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid", qsCSEName.toLocal8Bit().constData() );
////											56 : CSE (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid
//										ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 56 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
//									}
//									else if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.compare("New (via wsDayUse)", Qt::CaseInsensitive)==0)
//									{	// setup and copy CSE include file defining DHW use profiles - SAC 3/17/16
//										QString sDHWUseIncFile = "DHWDUMF.txt";
//										QString sDHWUseTo, sDHWUseFrom = sCSEEXEPath + sDHWUseIncFile;
//										if (!FileExists( sDHWUseFrom.toLocal8Bit().constData() ))
//										{	sErrMsg.sprintf( "%s (residential DHW simulation engine) use profile file not found:  %s", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData() );
////												55 : CSE (residential DHW simulation engine) use profile file not found
//											ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 55 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
//										}
//										else
//										{	sDHWUseTo = sProcessingPath + sDHWUseIncFile;
//											if (!CopyFile( sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData(), FALSE ))
//											{	sErrMsg.sprintf( "Unable to copy %s DHW Use/Load Profile include file from '%s' into processing directory '%s'", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData() );
////													57 : Unable to copy DHW Use/Load Profile CSE include file into processing directory
//												ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 57 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
//											}
//											assert( FileExists( sDHWUseTo.toLocal8Bit().constData() ) );
//											// RE-check DHW incl file hash ??
//									}	}
//
//				// WRITE TDV FILE FOR BATTERY SIM (tdvElec only)
//
//									int iCSESimRetVal = 0;
//									if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())
//									{
//									// Check for specification of Report Include file - and if found, prevent secure report
//										long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "CSE_RptIncFile", iCID_Proj );
//										QString sChkRptIncFile;
//										if (lProjReportIncludeFileDBID > 0 && BEMPX_GetString( lProjReportIncludeFileDBID, sChkRptIncFile ) && !sChkRptIncFile.isEmpty())
//											sCSEIncludeFileDBID = "Proj:CSE_RptIncFile";
//									// DISABLE report include file use if all settings are conisistent w/ full secure report generation (to prevent invalid analysis)
//										bool bAllowReportIncludeFile = true;
//										if (!sCSEIncludeFileDBID.isEmpty() && iCodeType == CT_T24N && bSendRptSignature && (bComplianceReportPDF || bComplianceReportXML || bComplianceReportStd) &&
//												!sXMLResultsFileName.isEmpty() && iAnalysisThruStep >= 8 && sIDFToSimulate.isEmpty() && iDLLCodeYear == iRulesetCodeYear && !bBypassInputChecks &&
//												!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] && !bBypassUMLHChecks && !bBypassCheckSimRules && 
//												plOverrideAutosize[0] == -1 && plOverrideAutosize[1] == -1 && plOverrideAutosize[2] == -1 && plOverrideAutosize[3] == -1 && !bBypassCheckCodeRules && 
//												lQuickAnalysis <= 0 && !bIgnoreFileReadErrors && !bBypassValidFileChecks && sDevOptsNotDefaulted.isEmpty() && sExcptDsgnModelFile.isEmpty() &&
//												lNumSpaceWithDefaultedDwellingUnitArea < 1)
//										{	bAllowReportIncludeFile = false;
//											sCSEIncludeFileDBID.clear();
//																sLogMsg.sprintf( "%s report include file use disabled to ensure secure report generation.  Use one of the Bypass* or other research option(s) to ensure report include file use.", qsCSEName.toLocal8Bit().constData() );
//																BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//										}
//
//										/*QString sT24DHWEnduse = "T24DHW", sT24DHWPumpEnduse = "T24DHWPmp";*/			assert( FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ) );
//										bool bFullComplianceAnalysis = (!bResearchMode && !bProposedOnly);
//										long lAnalysisType = (bResearchMode ? 0 : (bProposedOnly ? 12 : 13));  // based on CBECC-Res options: 0-Research / 12-Proposed Only / 13-Proposed and Standard
//										CSERunMgr cseRunMgr(
//													sCSEexe, sAnnualWeatherFile, sModelPathOnly, sModelFileOnly, sProcessingPath, bFullComplianceAnalysis,
//													false /*bInitHourlyResults*/, 0 /*lAllOrientations*/, lAnalysisType, iRulesetCodeYear, 0 /*lDesignRatingRunID*/, bVerbose,
//													bStoreBEMDetails, true /*bPerformSimulations*/, false /*bBypassCSE*/, bSilent, pCompRuleDebugInfo, pszUIVersionString,
//													0 /*iSimReportDetailsOption*/, 0 /*iSimErrorDetailsOption*/	);		// SAC 11/7/16 - added sim report/error option arguments, disabled until/unless wanted for Com analysis
//						//								dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
//
//						//				QString sMsg;
//										int iRunType[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
//										iRunType[0] = (lAnalysisType < 1 ? CRM_User :
//															(((iCodeType == CT_T24N && iRun == 3) || (iCodeType != CT_T24N && iRun >  5)) ? CRM_StdDesign : CRM_Prop));
//						//				siNumProgressRuns = 1;
//						//				int iRunIdx = 0;
//						//				for (; (iRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)
//						//				{
//						//					if (iRunIdx > 0 || !bFirstModelCopyCreated)
//						//						BEMPX_AddModel( std::min( iRunIdx, 1 ) /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
//											iCSESimRetVal = cseRunMgr.SetupRun_NonRes( 0/*iRunIdx*/, iRunType[0/*iRunIdx*/], sErrMsg, bAllowReportIncludeFile, 
//																							sRunIDLong.toLocal8Bit().constData(), sRunID.toLocal8Bit().constData(), &sCSEVersion );
//						//								dTimeToPrepModel[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
//						//				}
//
//	//	if (iRetVal == 0)
//	//	{
//	//				QMessageBox msgBox;
//	//				msgBox.setWindowTitle( "CSE" );
//	//				msgBox.setIcon( QMessageBox::Warning ); 
//	//				msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
//	//				msgBox.setText( "About to launch CSE simulation(s)" );
//	//		//		msgBox.setDetailedText( qsRptIssuesDlgDetails );
//	//				msgBox.setStandardButtons( QMessageBox::Ok );
//	//				msgBox.addButton( QMessageBox::Abort );
//	//				msgBox.setDefaultButton( QMessageBox::Ok );
//	//				msgBox.exec();
//	//	}
//
//										if (iRetVal == 0 && iCSESimRetVal == 0)		// && bPerformSimulations && !bBypassCSE)
//										{	bool bSaveFreezeProg = sbFreezeProgress;
//											sbFreezeProgress = true;	// SAC 5/31/16 - prevent progress reporting during (very quick) CSE DHW simulations
//											cseRunMgr.DoRuns();
//											sbFreezeProgress = bSaveFreezeProg;
//										}
//						//								dTimeCSESim += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
//
//						//				for (iRunIdx = 0; (iRetVal == 0 && iCSESimRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)
//						//				{
//						//					// SAC 6/19/14 - Set active model index to the appropriate value for this iRunIdx
//						//					BEMPX_SetActiveModel( iRunIdx+1 );
//								
//											const CSERun& cseRun = cseRunMgr.GetRun(0/*iRunIdx*/);
//											const QString& sRunID = cseRun.GetRunID();
//						//					const QString& sRunIDProcFile = cseRun.GetRunIDProcFile();
//											const QString& sRunAbbrev = cseRun.GetRunAbbrev();
//											long lRunNumber = (lAnalysisType < 1 ? 1 : cseRun.GetRunNumber());
//										//	BOOL bLastRun = cseRun.GetLastRun();
//						//					BOOL bIsStdDesign = cseRun.GetIsStdDesign();
//						//					BOOL bIsDesignRtg = cseRun.GetIsDesignRtg();
//								
//											if (iRetVal == 0 && iCSESimRetVal == 0)
//											{
//												int iCSERetVal = cseRun.GetExitCode();
//												if (bVerbose)  // SAC 1/31/13
//												{	sLogMsg.sprintf( "      %s simulation returned %d", qsCSEName.toLocal8Bit().constData(), iCSERetVal );
//													BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//												}
//												BEMPX_RefreshLogFile();	// SAC 5/19/14
//								
//												if (iCSERetVal != 0)
//												{	sErrMsg.sprintf( "ERROR:  %s simulation returned %d", qsCSEName.toLocal8Bit().constData(), iCSERetVal );
//													iCSESimRetVal = BEMAnal_CECRes_CSESimError;
//													BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//												}
//						//						if (iRetVal == 0 && iCSESimRetVal == 0 && BEMPX_AbortRuleEvaluation())
//						//							iCSESimRetVal = BEMAnal_CECRes_RuleProcAbort;
//								
//												// Retrieve CSE simulation results
//												if (iRetVal == 0 && iCSESimRetVal == 0)
//												{	// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
//													int iHrlyResRetVal = BEMPX_ReadCSEHourlyResults( cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), lRunNumber-1, sRunID.toLocal8Bit().constData(),
//																								sRunAbbrev.toLocal8Bit().constData(), -1, pszMeters, pszMeters_ComMap, sdaMeterMults_ComMap, pszCSEEnduseList, pszCSEEUList_ComMap );	// SAC 5/31/16
//													if (iHrlyResRetVal < 0)  // SAC 6/12/17
//													{	switch (iHrlyResRetVal)
//														{	case -1 :  sLogMsg = QString( "Error retrieving hourly %1 results (-1) / run: %2, runID: %3, runAbrv: %4, file: %5" ).arg(
//																													qsCSEName, QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );
//															case -2 :  sLogMsg = QString( "Error retrieving hourly %1 results (-2) / Unable to retrieve BEMProc pointer / run: %2, runID: %3, runAbrv: %4, file: %5" ).arg(
//																													qsCSEName, QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );
//															case -3 :  sLogMsg = QString( "Error retrieving hourly %1 results (-3) / Run index not in valid range 0-%2 / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
//																													qsCSEName, QString::number(BEMRun_MaxNumRuns-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );
//															case -4 :  sLogMsg = QString( "Error retrieving hourly %1 results (-4) / RunID too large (limit of %2 chars) / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
//																													qsCSEName, QString::number(BEMRun_RunNameLen-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );
//															case -5 :  sLogMsg = QString( "Error retrieving hourly %1 results (-4) / RunAbrv too large (limit of %2 chars) / run: %3, runID: %4, runAbrv: %5, file: %6" ).arg( 
//																													qsCSEName, QString::number(BEMRun_RunAbbrevLen-1), QString::number(lRunNumber-1), sRunID, sRunAbbrev, cseRun.GetOutFile(CSERun::OutFileCSV) );
//														}
//														if (sLogMsg.size() > 0)
//															BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//													}
//													else if (bVerbose)  // SAC 1/31/13
//													{	sLogMsg.sprintf( "      Hourly %s results retrieval returned %d", qsCSEName.toLocal8Bit().constData(), iHrlyResRetVal );
//														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//													}
//												// add new Elec - SHWPmp enduse results array  (other arrays initialized based on enduse names in CSE results file)
//						//							BEMPX_AddHourlyResultArray(	NULL, sRunID, "MtrElec", "DHWPmp", -1 /*iBEMProcIdx*/, TRUE /*bAddIfNotExist*/ );
//												}
//											}
//						//				}
//
//									}
//									bCSESimOK = (iCSESimRetVal == 0);
//									if (sCSEErrMsg.isEmpty() && iCSESimRetVal != 0)
//										sCSEErrMsg.sprintf( "error code %d", iCSESimRetVal );
//
//								if (!bCSESimOK)
//								{	sErrMsg.sprintf( "CSE (ResDHW/PV/Battery) simulation not successful:  %s", sCSEErrMsg.toLocal8Bit().constData() );
////										41 : CSE (ResDHW/PV/Battery) simulation not successful
//									ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 41 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
//								}
//								BEMPX_RefreshLogFile();	// SAC 5/19/14
//							}
//							else if (iNumRecircDHWSysObjs > 0 || iNumPVArrayObjs > 0)
//							{	if (bVerbose)
//									BEMPX_WriteLogFile( "      Skipping CSE ResDHW/PV/Battery simulation", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
////								CSE_MsgCallback( 0 /*level*/, "Skipping CSE ResDHW/PV/Battery simulation" );
//						}	}
//			// END OF CSE ResDHW/PV/Battery simulation

					bool baSimPassesUMLHLimits[] = { true, true };
					if (!bCallOpenStudio)
					{	sLogMsg.sprintf( "  PerfAnal_NRes - Bypassing OpenStudio (and simulation) for %s model", sRunID.toLocal8Bit().constData() );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

						// SAC 7/23/18 - additional message if bypassing OS will also result in CSE sim being bypassed
						if (bSimulateModel && bStoreHourlyResults)
						{  int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ) );
							int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray" ) );
							if ((!bBypassRecircDHW && iNumRecircDHWSysObjs > 0) || iNumPVArrayObjs > 0)
							{	sLogMsg.sprintf( "  PerfAnal_NRes - Bypassing CSE simulation as well (due to OpenStudio bypass) for %s model", sRunID.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}	}
					}
					else
					{			if (bVerbose)
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Calling PerfSim_E+ for %s model", sRunID.toLocal8Bit().constData() );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
						if (!bSimulateModel)
						{	sLogMsg.sprintf( "  PerfAnal_NRes - Bypassing simulation of %s model", sRunID.toLocal8Bit().constData() );
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}

						int iSimRetVal = 0;
              		QString sEPlusSimErrMsg;
						if (!bAbort && !BEMPX_AbortRuleEvaluation())
						{	//QString sSimWeatherPath = esDataPath + "EPW\\";

					// ENERGYPLUS SIMULATION
							if (!sIDFToSimulate.isEmpty())
							{	if (sExcptDsgnModelFile.isEmpty())
									sLogMsg.sprintf( "    SIMULATING FIXED IDF FILE:  %s", sIDFToSimulate.toLocal8Bit().constData() );
								else
									sLogMsg.sprintf( "    SIMULATING FIXED IDF FILE (for runs other than annual proposed):  %s", sIDFToSimulate.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg );
							}
							QString sProjSDDFileNoPath = sProjSDDFile.right( sProjSDDFile.length() - sProjSDDFile.lastIndexOf('\\') - 1 );
							dTimeToOther += DeltaTime( tmAnalOther );		// log time spent prior to this point to "other" bucket
//				// SAC 4/18/14 - logic to SKIP certain simulations and simulate them with the FOLLOWING run
							bModelToBeSimulated[iRun] = true;
//							bThisOSSimSkipped = (bParallelSimulations && !bLastOSSimSkipped && bSimulateModel && iNumRuns > 3 && (iRun==0 || iRun==2));
							QString sLocalIDFToSim = (!sExcptDsgnModelFile.isEmpty() && ((iCodeType == CT_T24N && iRun == 2) || (iCodeType != CT_T24N && iRun == 5))) ? sExcptDsgnModelFile : sIDFToSimulate;	// SAC 12/19/14 - use sExcptDsgnModelFile for annual proposed run (if specified)

							bool bIsDsgnSim = ((iCodeType == CT_T24N && iRun < 2) || (iCodeType != CT_T24N && iRun < 5));
							osRunInfo[iSimRunIdx].InitializeRunInfo( NULL, iRun, sProjSDDFileNoPath.toLocal8Bit().constData(), sRunID.toLocal8Bit().constData(), sRunIDLong.toLocal8Bit().constData(),
																					((iCodeType == CT_T24N && iRun > 2) || (iCodeType != CT_T24N && iRun > 5)) /*bIsStdRun*/, bIsDsgnSim /*bPostEquipCapsToBEMBase*/,
																					bSimulateModel, iCurActiveBEMProcIdx, sLocalIDFToSim.toLocal8Bit().constData() );

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

							//	iSimRetVal = CMX_PerformSimulation_EnergyPlus_Multiple(	sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
								iSimRetVal = PerformSimulation_EnergyPlus_Multiple( osWrap, &osRunInfo[0], sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
																				sProcessingPath.toLocal8Bit().constData(), posSimInfo, iSimRunIdx+1, 
																		// remaining general arguments
																				bVerbose, FALSE /*bDurationStats*/, &dTimeToTranslate[iNumTimeToTranslate++],
																				(bIsDsgnSim ? &dTimeToSimDsgn[iNumTimeToSimDsgn++] : &dTimeToSimAnn[iNumTimeToSimAnn++]),
																				iSimulationStorage, &dEPlusVer, pszEPlusVerStr, 60, pszOpenStudioVerStr, 60 , iCodeType,
																				false /*bIncludeOutputDiagnostics*/, iProgressType );		// SAC 5/27/15

							// moved some post-E+ processing into if (bSimRunsNow) statement
								tmAnalOther = boost::posix_time::microsec_clock::local_time();		// reset timer for "other" bucket
										if (bVerbose)
										{	sLogMsg.sprintf( "  PerfAnal_NRes - Back from PerfSim_E+ (%s model, %d return value)", sRunID.toLocal8Bit().constData(), iSimRetVal );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}

								if (/*bSimRunsNow &&*/ iSimRetVal == 0 && bIsDsgnSim)		// SAC 4/1/14
									for (iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
										bSizingRunSimulated[osSimInfo[iSimRun].iRunIdx] = TRUE;

								if (/*bSimRunsNow &&*/ (iSimRetVal == 0 || iSimRetVal == OSI_SimEPlus_UserAbortedAnalysis))
									for (iSimRun=0; iSimRun <= iSimRunIdx; iSimRun++)
										saSimulatedRunIDs.push_back( osRunInfo[iSimRun].RunID() );



						// CSE Simulation Loop -----
								for (int iSR=0; iSR <= iSimRunIdx; iSR++)	// loop over runs just simulated in E+ above
								{
								// SAC 7/23/18 - CSE simulation moved down HERE so that CSE inputs can include E+ elec use hourly data that feeds into the Battery simulation
								// SAC 5/27/16 - moved Recirc/Res DHW simulation outside code which gets bypassed due to bCallOpenStudio
									if (osSimInfo[iSR].bSimulateModel && bStoreHourlyResults)
									{  int iNumRecircDHWSysObjs = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "ResDHWSys" ), BEMO_User, osSimInfo[iSR].iBEMProcIdx );
										int iNumPVArrayObjs      = BEMPX_GetNumObjects( BEMPX_GetDBComponentID( "PVArray"   ), BEMO_User, osSimInfo[iSR].iBEMProcIdx );
										if ((!bBypassRecircDHW && iNumRecircDHWSysObjs > 0) || iNumPVArrayObjs > 0)
										{
								// CSE (DHW &/or PVArray/Battery) SIMULATION
											BOOL bCSESimOK = TRUE;		QString sCSEErrMsg;
												// perform DHW simulation using CSE and add those results into the hourly results already stored in BEMProc (should be after reading E+ results but before applying TDV multipliers)
					// --- CSE DHW (&/or PVArray/Battery) simulation based on CECRes analysis ---
												QString sCSE_DHWUseMthd;
												BEMPX_GetString( BEMPX_GetDatabaseID( "CSE_DHWUseMthd", iCID_Proj ), sCSE_DHWUseMthd, FALSE, 0, -1, -1, BEMO_User, NULL, 0, osSimInfo[iSR].iBEMProcIdx );
												if (!FileExists( sCSEexe.toLocal8Bit().constData() ))
												{	sErrMsg.sprintf( "%s (residential DHW/PV/Battery simulation engine) executable not found: '%s'", qsCSEName.toLocal8Bit().constData(), sCSEexe.toLocal8Bit().constData() );		assert( FALSE );
//														54 : CSE (residential DHW & PV/Battery simulation engine) executable(s) not found
																// SAC 12/18/17 - replaced iDontAbortOnErrorsThruStep w/ '0' to prevent program crash when CSE exe not found
													ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 54 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, 0 /*iDontAbortOnErrorsThruStep*/, iAnalStep /*iStepCheck*/ );
												}
												else if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.isEmpty())
												{	sErrMsg.sprintf( "%s (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid", qsCSEName.toLocal8Bit().constData() );
//														56 : CSE (residential DHW simulation) Day Use Type (Proj:CSE_DHWUseMthd) invalid
													ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 56 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
												}
												else if (iNumRecircDHWSysObjs > 0 && sCSE_DHWUseMthd.compare("New (via wsDayUse)", Qt::CaseInsensitive)==0)
												{	// setup and copy CSE include file defining DHW use profiles - SAC 3/17/16
													QString sDHWUseIncFile = "DHWDU.txt";	// SAC 1/24/19 - updated from DHWDUMF.txt to DHWDU.txt
													QString sDHWUseTo, sDHWUseFrom = sCSEEXEPath + sDHWUseIncFile;
													if (!FileExists( sDHWUseFrom.toLocal8Bit().constData() ))
													{	sErrMsg.sprintf( "%s (residential DHW simulation engine) use profile file not found:  %s", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData() );
//															55 : CSE (residential DHW simulation engine) use profile file not found
														ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 55 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
													}
													else
													{	sDHWUseTo = sProcessingPath + sDHWUseIncFile;
														if (!CopyFile( sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData(), FALSE ))
														{	sErrMsg.sprintf( "Unable to copy %s DHW Use/Load Profile include file from '%s' into processing directory '%s'", qsCSEName.toLocal8Bit().constData(), sDHWUseFrom.toLocal8Bit().constData(), sDHWUseTo.toLocal8Bit().constData() );
//																57 : Unable to copy DHW Use/Load Profile CSE include file into processing directory
															ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 57 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
														}
														assert( FileExists( sDHWUseTo.toLocal8Bit().constData() ) );
														// RE-check DHW incl file hash ??
												}	}

												int iCSESimRetVal = 0;
												if (iRetVal == 0 && !bAbort && !BEMPX_AbortRuleEvaluation())
												{
												// Check for specification of Report Include file - and if found, prevent secure report
													long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "CSE_RptIncFile", iCID_Proj );
													QString sChkRptIncFile;
													if (lProjReportIncludeFileDBID > 0 &&
														 BEMPX_GetString( lProjReportIncludeFileDBID, sChkRptIncFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, osSimInfo[iSR].iBEMProcIdx ) && !sChkRptIncFile.isEmpty())
														sCSEIncludeFileDBID = "Proj:CSE_RptIncFile";
												// DISABLE report include file use if all settings are conisistent w/ full secure report generation (to prevent invalid analysis)
													bool bAllowReportIncludeFile = true;
													if (!sCSEIncludeFileDBID.isEmpty() && iCodeType == CT_T24N && bSendRptSignature && (bComplianceReportPDF || bComplianceReportXML || bComplianceReportStd) &&
															!sXMLResultsFileName.isEmpty() && iAnalysisThruStep >= 8 && sIDFToSimulate.isEmpty() && iDLLCodeYear == iRulesetCodeYear && !bBypassInputChecks &&
															!pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] && !bBypassUMLHChecks && !bBypassCheckSimRules && 
															plOverrideAutosize[0] == -1 && plOverrideAutosize[1] == -1 && plOverrideAutosize[2] == -1 && plOverrideAutosize[3] == -1 && !bBypassCheckCodeRules && 
															lQuickAnalysis <= 0 && !bIgnoreFileReadErrors && !bBypassValidFileChecks && sDevOptsNotDefaulted.isEmpty() && sExcptDsgnModelFile.isEmpty() &&
															lNumSpaceWithDefaultedDwellingUnitArea < 1 && !bBypassPreAnalysisCheckRules)
													{	bAllowReportIncludeFile = false;
														sCSEIncludeFileDBID.clear();
																			sLogMsg.sprintf( "%s report include file use disabled to ensure secure report generation.  Use one of the Bypass* or other research option(s) to ensure report include file use.", qsCSEName.toLocal8Bit().constData() );
																			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}

													/*QString sT24DHWEnduse = "T24DHW", sT24DHWPumpEnduse = "T24DHWPmp";*/			assert( FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ) );
													bool bFullComplianceAnalysis = (!bResearchMode && !bProposedOnly);
													long lAnalysisType = (bResearchMode ? 0 : (bProposedOnly ? 12 : 13));  // based on CBECC-Res options: 0-Research / 12-Proposed Only / 13-Proposed and Standard
													CSERunMgr cseRunMgr(
																sCSEexe, sAnnualWeatherFile, sModelPathOnly, sModelFileOnly, sProcessingPath, bFullComplianceAnalysis,
																false /*bInitHourlyResults*/, 0 /*lAllOrientations*/, lAnalysisType, iRulesetCodeYear, 0 /*lDesignRatingRunID*/, bVerbose,
																bStoreBEMDetails, true /*bPerformSimulations*/, false /*bBypassCSE*/, bSilent, pCompRuleDebugInfo, pszUIVersionString,
																0 /*iSimReportDetailsOption*/, 0 /*iSimErrorDetailsOption*/	);		// SAC 11/7/16 - added sim report/error option arguments, disabled until/unless wanted for Com analysis
									//								dTimeToOther += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

									//				QString sMsg;
													int iRunType[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
													iRunType[0] = (lAnalysisType < 1 ? CRM_User :
																		(((iCodeType == CT_T24N && osSimInfo[iSR].iRunIdx == 3) || (iCodeType != CT_T24N && osSimInfo[iSR].iRunIdx >  5)) ? CRM_StdDesign : CRM_Prop));

									//				siNumProgressRuns = 1;
									//				int iRunIdx = 0;
									//				for (; (iRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)
									//				{
									//					if (iRunIdx > 0 || !bFirstModelCopyCreated)
									//						BEMPX_AddModel( std::min( iRunIdx, 1 ) /*iBEMProcIdxToCopy=0*/, NULL /*plDBIDsToBypass=NULL*/, true /*bSetActiveBEMProcToNew=true*/ );
														iCSESimRetVal = cseRunMgr.SetupRun_NonRes( 0/*iRunIdx*/, iRunType[0/*iRunIdx*/], sErrMsg, bAllowReportIncludeFile, 
																										osSimInfo[iSR].pszLongRunID, osSimInfo[iSR].pszRunID, &sCSEVersion, osSimInfo[iSR].iBEMProcIdx );
									//								dTimeToPrepModel[iRunIdx] += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark
									//				}

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

													if (iRetVal == 0 && iCSESimRetVal == 0)		// && bPerformSimulations && !bBypassCSE)
													{	bool bSaveFreezeProg = sbFreezeProgress;
														sbFreezeProgress = true;	// SAC 5/31/16 - prevent progress reporting during (very quick) CSE DHW simulations
														cseRunMgr.DoRuns();
														sbFreezeProgress = bSaveFreezeProg;
													}
									//								dTimeCSESim += DeltaTime( tmMark );		tmMark = boost::posix_time::microsec_clock::local_time();		// SAC 1/12/15 - log time spent & reset tmMark

									//				for (iRunIdx = 0; (iRetVal == 0 && iCSESimRetVal == 0 && iRunIdx < iNumRuns); iRunIdx++)
									//				{
									//					// SAC 6/19/14 - Set active model index to the appropriate value for this iRunIdx
									//					BEMPX_SetActiveModel( iRunIdx+1 );
								
														const CSERun& cseRun = cseRunMgr.GetRun(0/*iRunIdx*/);
														const QString& sRunID = cseRun.GetRunID();
									//					const QString& sRunIDProcFile = cseRun.GetRunIDProcFile();
														const QString& sRunAbbrev = cseRun.GetRunAbbrev();
														long lRunNumber = (lAnalysisType < 1 ? 1 : cseRun.GetRunNumber());
													//	BOOL bLastRun = cseRun.GetLastRun();
									//					BOOL bIsStdDesign = cseRun.GetIsStdDesign();
									//					BOOL bIsDesignRtg = cseRun.GetIsDesignRtg();
								
														if (iRetVal == 0 && iCSESimRetVal == 0)
														{
															int iCSERetVal = cseRun.GetExitCode();
															if (bVerbose)  // SAC 1/31/13
															{	sLogMsg.sprintf( "      %s simulation returned %d", qsCSEName.toLocal8Bit().constData(), iCSERetVal );
																BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															}
															BEMPX_RefreshLogFile();	// SAC 5/19/14
								
															if (iCSERetVal != 0)
															{	sErrMsg.sprintf( "ERROR:  %s simulation returned %d", qsCSEName.toLocal8Bit().constData(), iCSERetVal );
																iCSESimRetVal = BEMAnal_CECRes_CSESimError;
																BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															}
									//						if (iRetVal == 0 && iCSESimRetVal == 0 && BEMPX_AbortRuleEvaluation())
									//							iCSESimRetVal = BEMAnal_CECRes_RuleProcAbort;
								
															// Retrieve CSE simulation results
															if (iRetVal == 0 && iCSESimRetVal == 0)
															{	// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
																int iHrlyResRetVal = BEMPX_ReadCSEHourlyResults( cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), -1 /*lRunNumber-1*/,
																											sRunID.toLocal8Bit().constData(), sRunAbbrev.toLocal8Bit().constData(), osSimInfo[iSR].iBEMProcIdx /*-1*/,
																											pszMeters, pszMeters_ComMap, sdaMeterMults_ComMap, pszCSEEnduseList, pszCSEEUList_ComMap, false /*bInitResults*/ );	// SAC 5/31/16  // SAC 7/23/18
		//	sLogMsg.sprintf( "      BEMPX_ReadCSEHourlyResults( %s, %d, %s, %s, BEMProc %d, ... ) returned %d", cseRun.GetOutFile( CSERun::OutFileCSV).toLocal8Bit().constData(), lRunNumber-1,
		//																									sRunID.toLocal8Bit().constData(), sRunAbbrev.toLocal8Bit().constData(), osSimInfo[iSR].iBEMProcIdx, iHrlyResRetVal );
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
																{	sLogMsg.sprintf( "      Hourly %s results retrieval returned %d", qsCSEName.toLocal8Bit().constData(), iHrlyResRetVal );
																	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																}
															// add new Elec - SHWPmp enduse results array  (other arrays initialized based on enduse names in CSE results file)
									//							BEMPX_AddHourlyResultArray(	NULL, sRunID, "MtrElec", "DHWPmp", -1 /*iBEMProcIdx*/, TRUE /*bAddIfNotExist*/ );
															}
														}
									//				}

												}
												bCSESimOK = (iCSESimRetVal == 0);
												if (sCSEErrMsg.isEmpty() && iCSESimRetVal != 0)
													sCSEErrMsg.sprintf( "error code %d", iCSESimRetVal );

											if (!bCSESimOK)
											{	sErrMsg.sprintf( "CSE (ResDHW/PV/Battery) simulation not successful:  %s", sCSEErrMsg.toLocal8Bit().constData() );
//													41 : CSE (ResDHW/PV/Battery) simulation not successful
												ProcessAnalysisError( sErrMsg, bAbort, iRetVal, 41 /*iErrID*/, true /*bErrCausesAbort*/, true /*bWriteToLog*/, pszErrorMsg, iErrorMsgLen, iDontAbortOnErrorsThruStep, iAnalStep /*iStepCheck*/ );
											}
											BEMPX_RefreshLogFile();	// SAC 5/19/14
										}
										else if (iNumRecircDHWSysObjs > 0 || iNumPVArrayObjs > 0)
										{	if (bVerbose)
												BEMPX_WriteLogFile( "      Skipping CSE ResDHW/PV/Battery simulation", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//											CSE_MsgCallback( 0 /*level*/, "Skipping CSE ResDHW/PV/Battery simulation" );
									}	}

								}	// end of: for (iSR=0-iSimRunIdx)
			// END OF CSE ResDHW/PV/Battery simulation



							// processing of analysis results foillowing ALL simulations - SAC 7/23/18
								if (iSimRetVal == 0)
									iSimRetVal = ProcessSimulationResults_Multiple(	osWrap, &osRunInfo[0], sEPlusSimErrMsg, sEPlusPath.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(),
																				sProcessingPath.toLocal8Bit().constData(), posSimInfo, iSimRunIdx+1, 
																		// remaining general arguments
																				bVerbose, FALSE /*bDurationStats*/, &dTimeToTranslate[iNumTimeToTranslate++],
																				(bIsDsgnSim ? &dTimeToSimDsgn[iNumTimeToSimDsgn++] : &dTimeToSimAnn[iNumTimeToSimAnn++]),
																				iSimulationStorage, &dEPlusVer, pszEPlusVerStr, 60, pszOpenStudioVerStr, 60 , iCodeType,
																				false /*bIncludeOutputDiagnostics*/, iProgressType );
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
										int iHrlyResExportRetVal = CMX_ExportCSVHourlyResults_Com( sHrlyResExportPathFile.toLocal8Bit().constData(), sModelPathFile.toLocal8Bit().constData(), 
																									osRunInfo[iSimRun].LongRunID().toLocal8Bit().constData(), iCodeType, pszHrlyResErrMsgBuffer, 512, bSilent,
																									osRunInfo[iSimRun].BEMProcIdx(), pszEPlusVerStr, pszOpenStudioVerStr );				assert( iHrlyResExportRetVal == 0 );
													if (iHrlyResExportRetVal != 0)
													{	sLogMsg.sprintf( "  PerfAnal_NRes - hourly results CSV export Failed for run %s -> return code %d: %s  (exporting to file:  %s)",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), iHrlyResExportRetVal, pszHrlyResErrMsgBuffer,
																				sHrlyResExportPathFile.toLocal8Bit().constData() );
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
													else if (bVerbose)
													{	sLogMsg.sprintf( "  PerfAnal_NRes - hourly results CSV export for run %s %s (return code %d):  %s",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), (iHrlyResExportRetVal==0 ? "successful" : "failed"), 
																				iHrlyResExportRetVal, sHrlyResExportPathFile.toLocal8Bit().constData() );
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
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
										sZeroCdHrlyMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
										             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
														 "(once the file is closed), or \n'Abort' to abort the %s.", "ZERO Code hourly results", sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), "hourly results export" );
										if (OKToWriteOrDeleteFile( sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), sZeroCdHrlyMsg, bSilent ))
										{	char pszZeroCdErrMsgBuffer[512];  pszZeroCdErrMsgBuffer[0]=0;
											int iZeroCdExportRetVal = CMX_ExportCSVHourlyResults_A2030( sZeroCdHrlyExportPathFile.toLocal8Bit().constData(), osRunInfo[iSimRun].LongRunID().toLocal8Bit().constData(),
																									pszZeroCdErrMsgBuffer, 512, bSilent, osRunInfo[iSimRun].BEMProcIdx() );				assert( iZeroCdExportRetVal == 0 );
													if (iZeroCdExportRetVal != 0)
													{	sLogMsg.sprintf( "  PerfAnal_NRes - ZERO Code hourly results CSV export Failed for run %s -> return code %d: %s  (exporting to file:  %s)",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), iZeroCdExportRetVal, pszZeroCdErrMsgBuffer,
																				sZeroCdHrlyExportPathFile.toLocal8Bit().constData() );
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
													else if (bVerbose)
													{	sLogMsg.sprintf( "  PerfAnal_NRes - ZERO Code hourly results CSV export for run %s %s (return code %d):  %s",
																				osRunInfo[iSimRun].RunID().toLocal8Bit().constData(), (iZeroCdExportRetVal==0 ? "successful" : "failed"), 
																				iZeroCdExportRetVal, sZeroCdHrlyExportPathFile.toLocal8Bit().constData() );
														BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
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
											sEPlusVer.sprintf( "%g", dEPlusVer );
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
										sZeroCdRptMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
										             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
														 "(once the file is closed), or \n'Abort' to abort the %s.", "ZERO Code report", sZeroCdRptPathFile.toLocal8Bit().constData(), "report generation" );
										if (OKToWriteOrDeleteFile( sZeroCdRptPathFile.toLocal8Bit().constData(), sZeroCdRptMsg, bSilent ))
										{
											if (!BEMPX_RulelistExists( "GenerateZEROCodeReport" ))
											{	sLogMsg.sprintf( "Warning:  'GenerateZEROCodeReport' rulelist not found in ruleset." );
												BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
											}
											else
											{
				// debugging
				sLogMsg.sprintf( "Evaluating 'GenerateZEROCodeReport' rulelist on model %d (iCurActiveBEMProcIdx %d).", BEMPX_GetActiveModel(), iCurActiveBEMProcIdx );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
										sErrMsg.sprintf( "Error(s) encountered simulating multiple models (sim returned %d)", iSimRetVal );
									else
										sErrMsg.sprintf( "Error(s) encountered simulating multiple models (sim returned %d):\n      %s", iSimRetVal, sEPlusSimErrMsg.toLocal8Bit().constData() );
								}
								else if (sEPlusSimErrMsg.isEmpty())
									sErrMsg.sprintf( "Error(s) encountered simulating %s model (sim returned %d)", osRunInfo[iErrantRunNum-1].LongRunID().toLocal8Bit().constData(), iSimRetVal );
								else
									sErrMsg.sprintf( "Error(s) encountered simulating %s model (sim returned %d):\n      %s", osRunInfo[iErrantRunNum-1].LongRunID().toLocal8Bit().constData(), 
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
									{	sErrMsg.sprintf( "Error(s) encountered retrieving %s model simulation results", sRunIDLong.toLocal8Bit().constData() );
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
										{	sLogMsg.sprintf( "  PerfAnal_NRes - Bypassing UMLH check on %s model", sRunID.toLocal8Bit().constData() );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
										else
										{	int iCID_ThrmlZn = BEMPX_GetDBComponentID( "ThrmlZn" );																	assert( iCID_ThrmlZn > 0 );
											long lDBID_ThrmlZn_ClgUMLHLimit = BEMPX_GetDatabaseID( "ClgUMLHLimit", iCID_ThrmlZn );							assert( iCID_ThrmlZn < 1 || lDBID_ThrmlZn_ClgUMLHLimit > 0 );
											long lDBID_ThrmlZn_HtgUMLHLimit = BEMPX_GetDatabaseID( "HtgUMLHLimit", iCID_ThrmlZn );							assert( iCID_ThrmlZn < 1 || lDBID_ThrmlZn_HtgUMLHLimit > 0 );
											QString cstrUMLHWarningMsg, cstrUMLHWarningDetails, cstrUMLHDlgCaption;
											if (iCID_ThrmlZn > 0)
											{	for (int iR=0; iR <= iSimRunIdx; iR++)
													if (osRunInfo[iR].OSRunIdx() >= 0)
													{													assert( sErrMsg.isEmpty() );	// confirm error message not populated yet - else code @ end of for loop likely needing some mods
														if (bVerbose)
														{	sLogMsg.sprintf( "  PerfAnal_NRes - UMLH check on %s model", osRunInfo[iR].RunID().toLocal8Bit().constData() );
															BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
														}
											// Check for zones exceeding maxiumum number of cooling/heat load hours - SAC 8/31/13
															int iNumZonesExceedClgUMLHs = 0, iNumZonesExceedHtgUMLHs = 0,  iMaxZoneExceedClgUMLHsIdx = -1, iMaxZoneExceedHtgUMLHsIdx = -1;
															double fMaxZoneClgUMLHs = 0, fMaxZoneHtgUMLHs = 0, fNumZoneClgUMLHs = 0, fNumZoneHtgUMLHs = 0;
															QString sMaxZoneClgUMLHsName, sMaxZoneHtgUMLHsName, sErrantZoneList, sAppendToErrantZoneList;
															int iNumZones = (iCID_ThrmlZn < 1 ? 0 : BEMPX_GetNumObjects( iCID_ThrmlZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ));			assert( iNumZones > 0 );
#define  UMLH_ERR_MSG_BASELINE	225	// space for leading line:  Error: In XXXXXXXXXXXXX model, ### zone(s) exceed maximum cooling unmet load hours (####) and ### zone(s) exceed maximum heating unmet load hours (####)
															// and trailing line:       (and ### other zones, as reported in project log file)
															QString sReducedErrantZoneList;
															int iMaxErrantZoneListToAppend = 0, iNumZnsExcludedFromErrZoneList = 0;
															if (iErrorMsgLen > 0 && pszErrorMsg && (iErrorMsgLen - strlen( pszErrorMsg )) > UMLH_ERR_MSG_BASELINE)
																iMaxErrantZoneListToAppend = iErrorMsgLen - (strlen( pszErrorMsg ) + UMLH_ERR_MSG_BASELINE);
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

																if (fMaxUnmetClgLdHrs > -0.5 && BEMPX_GetFloat( lDBID_ThrmlZn_ClgUnmetLdHrs, fNumZoneClgUMLHs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ) && fNumZoneClgUMLHs > 0)
																{	if (fNumZoneClgUMLHs > (fMaxZoneClgUMLHs + 0.1))
																	{	iMaxZoneExceedClgUMLHsIdx = iZn;
																		fMaxZoneClgUMLHs = fNumZoneClgUMLHs;
																	}
																	if (fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1))
																		iNumZonesExceedClgUMLHs++;
																}
																if (fMaxUnmetHtgLdHrs > -0.5 && BEMPX_GetFloat( lDBID_ThrmlZn_HtgUnmetLdHrs, fNumZoneHtgUMLHs, 0, -1, iZn, BEMO_User, osRunInfo[iR].BEMProcIdx() ) && fNumZoneHtgUMLHs > 0)
																{	if (fNumZoneHtgUMLHs > (fMaxZoneHtgUMLHs + 0.1))
																	{	iMaxZoneExceedHtgUMLHsIdx = iZn;
																		fMaxZoneHtgUMLHs = fNumZoneHtgUMLHs;
																	}
																	if (fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1))
																		iNumZonesExceedHtgUMLHs++;
																}

                     			                  // append record to string reporting zone UMLH issues - SAC 9/6/13
																if ( (fMaxUnmetClgLdHrs > -0.5 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1)) ||
																	  (fMaxUnmetHtgLdHrs > -0.5 && fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1)) )
																{	BEMPX_GetString( lDBID_ThrmlZn_Name, sMaxZoneClgUMLHsName, FALSE /*bAddCommas*/, 0 /*iPrecision*/, -1 /*iDispDataType*/, iZn,
																									BEMO_User, NULL, 0, osRunInfo[iR].BEMProcIdx() );		assert( !sMaxZoneClgUMLHsName.isEmpty() );
																	sAppendToErrantZoneList.sprintf( "\n          clg: %.0f  htg: %.0f  '%s'", fNumZoneClgUMLHs, fNumZoneHtgUMLHs, sMaxZoneClgUMLHsName.toLocal8Bit().constData() );
														// SAC 3/8/14 - added code to limit zones reported back to calling application so that error message doesn't exceed max length
																	if (iMaxErrantZoneListToAppend > 0 && iNumZnsExcludedFromErrZoneList > 0)
																		iNumZnsExcludedFromErrZoneList++;	// already to the point where we are excluding zones, so just increment the counter of skipped zones
																	else if (iMaxErrantZoneListToAppend > 0 && sReducedErrantZoneList.isEmpty() &&
																				(sErrantZoneList.length() + sAppendToErrantZoneList.length()) > iMaxErrantZoneListToAppend)
																	{	sReducedErrantZoneList = sErrantZoneList;
																		iNumZnsExcludedFromErrZoneList++;
																	}
																	sErrantZoneList += sAppendToErrantZoneList;
																			if (!osRunInfo[iR].IsStdRun())  //bVerbose)	// SAC 3/10/15 - added verbose logging of each UMLH errant zone inside zone loop to catch variation in UMLH limits (by zone)
																			{	if (fMaxUnmetClgLdHrs > -0.5 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1) && fMaxUnmetHtgLdHrs > -0.5 && fNumZoneHtgUMLHs > (fMaxUnmetHtgLdHrs + 0.1))
																				{	sLogMsg.sprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: cooling %.0f (%.0f max) and heating %.0f (%.0f max)", 
																											osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs, fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' cooling %L2 > %L3 and heating %L4 > %L5\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneClgUMLHs ).arg( fMaxUnmetClgLdHrs ).arg( fNumZoneHtgUMLHs ).arg( fMaxUnmetHtgLdHrs ) );
																					sMsg.sprintf( "  '%s' cooling %g > %g and heating %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs, fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																				}
																				else if (fMaxUnmetClgLdHrs > -0.5 && fNumZoneClgUMLHs > (fMaxUnmetClgLdHrs + 0.1))
																				{	sLogMsg.sprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: cooling %.0f (%.0f max)", osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' cooling %L2 > %L3\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneClgUMLHs ).arg( fMaxUnmetClgLdHrs ) );
																					sMsg.sprintf( "  '%s' cooling %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneClgUMLHs, fMaxUnmetClgLdHrs );
																				}
																				else
																				{	sLogMsg.sprintf( "Simulation Warning:  %s model zone '%s' exceeds UMLH limits: heating %.0f (%.0f max)", osRunInfo[iR].LongRunID().toLocal8Bit().constData(), sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
																					//qstrUMLHWarningDetails.append( QString( "  '%1' heating %L2 > %L3\n" ).arg( ((const char*) sMaxZoneClgUMLHsName) ).arg( fNumZoneHtgUMLHs ).arg( fMaxUnmetHtgLdHrs ) );
																					sMsg.sprintf( "  '%s' heating %g > %g\n", sMaxZoneClgUMLHsName.toLocal8Bit().constData(), fNumZoneHtgUMLHs, fMaxUnmetHtgLdHrs );
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
															{	if (iNumZonesExceedClgUMLHs > 0 && iNumZonesExceedHtgUMLHs > 0)
																	sErrMsg.sprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load hours and %d zone(s) exceed maximum heating unmet load hours", iNumZonesExceedClgUMLHs, /*fMaxUnmetClgLdHrs,*/ osRunInfo[iR].LongRunID().toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs /*, fMaxUnmetHtgLdHrs*/ );
																else if (iNumZonesExceedClgUMLHs > 0)
																	sErrMsg.sprintf( "Warning:  %d zone(s) in %s model exceed maximum cooling unmet load hours", iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetClgLdHrs*/ );
																else  // if (iNumZonesExceedHtgUMLHs > 0)
																	sErrMsg.sprintf( "Warning:  %d zone(s) in %s model exceed maximum heating unmet load hours", iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetHtgLdHrs*/ );
																if (iMaxErrantZoneListToAppend > 0 && !sReducedErrantZoneList.isEmpty())	// SAC 3/8/14
																	// repeat same message but w/ shortened list of zones
																	sErrMsgShortenedToFit.sprintf( "%s%s\n          (and %d other zone(s), as reported in project log file)", sErrMsg.toLocal8Bit().constData(), sReducedErrantZoneList.toLocal8Bit().constData(), iNumZnsExcludedFromErrZoneList );
																sErrMsg += sErrantZoneList;
																bForceXMLFileWriteDespiteAbort = true;		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
//														30 : Model zone(s) exceed unmet load hours limits
							// SAC 3/10/15 - prevent erroring out of analysis for UMLH limit reason
							//									if ((osRunInfo[iR].OSRunIdx()==0 && iDontAbortOnErrorsThruStep < 4) || (osRunInfo[iR].OSRunIdx()==2 && iDontAbortOnErrorsThruStep < 7))		// SAC 1/30/15 - no longer error out for baseline run - was:  || (osRunInfo[iR].OSRunIdx()==1 && iDontAbortOnErrorsThruStep < 4) || (osRunInfo[iR].OSRunIdx()==3 && iDontAbortOnErrorsThruStep < 7))  // check flag to bypass errors
							//										iRetVal = (iRetVal > 0 ? iRetVal : 30);		// DO abort

																if (!osRunInfo[iR].IsStdRun())  //bVerbose)	// SAC 3/10/15 - added verbose logging of each UMLH errant zone inside zone loop to catch variation in UMLH limits (by zone)
																{	sUMLHTextFileMsg = cstrUMLHWarningDetails;		// qstrUMLHWarningDetails.toStdString().c_str();
																	if (iNumZonesExceedClgUMLHs > 0 && iNumZonesExceedHtgUMLHs > 0)
																	{
																		//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum cooling unmet load hours and %L3 zone(s) exceed maximum heating unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedClgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) ).arg( iNumZonesExceedHtgUMLHs );
																		cstrUMLHWarningMsg.sprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum cooling unmet load hours and %d zone(s) exceed maximum heating unmet load hours.<br><br></a>",
    																												iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs );
																		sLogMsg.sprintf( "%d zone(s) in %s model exceed maximum cooling unmet load hours and %d zone(s) exceed maximum heating unmet load hours:\n", iNumZonesExceedClgUMLHs, /*fMaxUnmetClgLdHrs,*/ osRunInfo[iR].LongRunID().toLocal8Bit().constData(), iNumZonesExceedHtgUMLHs /*, fMaxUnmetHtgLdHrs*/ );
																	}
																	else if (iNumZonesExceedClgUMLHs > 0)
																	{
																		//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum cooling unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedClgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) );
																		cstrUMLHWarningMsg.sprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum cooling unmet load hours.<br><br></a>",
    																												iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() );
																		sLogMsg.sprintf( "%d zone(s) in %s model exceed maximum cooling unmet load hours:\n", iNumZonesExceedClgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetClgLdHrs*/ );
																	}
																	else  // if (iNumZonesExceedHtgUMLHs > 0)
																	{
																		//qstrUMLHWarningMsg = QString( "<a>Warning:  %L1 zone(s) in %2 model exceed maximum heating unmet load hours.<br><br></a>" )
    																	//											.arg( iNumZonesExceedHtgUMLHs ).arg( ((const char*) osRunInfo[iR].LongRunID()) );
																		cstrUMLHWarningMsg.sprintf( "<a>Warning:  %d zone(s) in %s model exceed maximum heating unmet load hours.<br><br></a>",
    																												iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() );
																		sLogMsg.sprintf( "%d zone(s) in %s model exceed maximum heating unmet load hours:\n", iNumZonesExceedHtgUMLHs, osRunInfo[iR].LongRunID().toLocal8Bit().constData() /*, fMaxUnmetHtgLdHrs*/ );
																	}
																	sUMLHTextFileMsg = sLogMsg + sUMLHTextFileMsg;
																	//qstrUMLHWarningDetails.prepend( "Zones exceeding unmet load hour limits:\n" );
																	//qstrUMLHWarningMsg.append( "<a>All thermal zones exceeding unmet load hour limits will be reported on PRF-1.<br></a>" );
																	//qstrUMLHWarningMsg.append( "<a>In the future, projects with zones exceeding UMLH limits will not be useable for compliance.</a>" );
																	cstrUMLHWarningDetails = "Zones exceeding unmet load hour limits:\n" + cstrUMLHWarningDetails;
																	cstrUMLHWarningMsg += "<a>All thermal zones exceeding unmet load hour limits will be reported on PRF-1.<br></a>";
																	cstrUMLHWarningMsg += "<a>In the future, projects with zones exceeding UMLH limits will not be useable for compliance.</a>";

																	QString sUMLHFAQLink;
																	if (!BEMPX_GetString( BEMPX_GetDatabaseID( "UnmetLdHrsFAQLink", iCID_Proj ), sUMLHFAQLink ))
																		sUMLHFAQLink.clear();
																	if (!sUMLHFAQLink.isEmpty())
																	{	sUMLHTextFileMsg += "For information on resolving unmet load hour issues visit:  ";
																		sUMLHTextFileMsg += sUMLHFAQLink;
																		sUMLHTextFileMsg += "\n";
																		//qstrUMLHWarningMsg.append( QString( "<a><br></a><a href=%1>Click here for information on resolving unmet load hour issues.</a>" ).arg( ((const char*) sUMLHFAQLink) ) );
																		sMsg.sprintf( "<a><br></a><a href=%s>Click here for information on resolving unmet load hour issues.</a>", sUMLHFAQLink.toLocal8Bit().constData() );
																		cstrUMLHWarningMsg += sMsg;
																	}

															// write text file w/ UMLH zone listing
																	if (bWriteUMLHViolationsToFile && !sUMLHTextFileName.isEmpty())
																	{	QString sUMLHOverwriteMsg;
																		sUMLHOverwriteMsg.sprintf(	"The zone UMLH violations text file '%s' is opened in another application.  This file must be closed in that application before an updated file "
																											"can be written.\n\nSelect 'Retry' to proceed (once the file is closed), or \n'Abort' to abort the file writing.", sUMLHTextFileName.toLocal8Bit().constData() );
																		if (!OKToWriteOrDeleteFile( sUMLHTextFileName.toLocal8Bit().constData(), sUMLHOverwriteMsg, bSilent ))
																			sUMLHOverwriteMsg.sprintf( "Unable to open and/or write zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
																		else
																		{	sUMLHOverwriteMsg.clear();
																			FILE *fp_UMLH;
																			int iUMLHErrorCode;
																			try
																			{	iUMLHErrorCode = fopen_s( &fp_UMLH, sUMLHTextFileName.toLocal8Bit().constData(), "wb" );
																				if (iUMLHErrorCode != 0 || fp_UMLH == NULL)
																					sUMLHOverwriteMsg.sprintf( "Error encountered opening zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
																				else
																				{	long lUMLHRunDate = 0;
																					if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lUMLHRunDate ) && lUMLHRunDate > 0)
																				   {	//CTime locTime = lUMLHRunDate;
																						//fprintf( fp_UMLH, "Run Date/Time:  %s\n", locTime.Format("%Y-%b-%d %H:%M:%S") );
																						QDateTime locTime = QDateTime::currentDateTime();
																						fprintf( fp_UMLH, "Run Date/Time:  %s\n", locTime.toString("yyyy-MM-dd HH:mm:ss") );
																					}
																					fprintf( fp_UMLH, sUMLHTextFileMsg.toLocal8Bit().constData() );
																					fflush(  fp_UMLH );
																					fclose(  fp_UMLH );
																			}	}
																			catch( ... )
																			{	sUMLHOverwriteMsg.sprintf( "Unknown error writing zone UMLH violations text file:  %s", sUMLHTextFileName.toLocal8Bit().constData() );
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
																	if (bPromptUserUMLHWarning)
																	{	QString qstrUMLHWarningMsg = cstrUMLHWarningMsg;
																		QString qstrUMLHWarningDetails = cstrUMLHWarningDetails;
																		QString qstrUMLHDlgCaption = cstrUMLHDlgCaption;
																		qstrUMLHDlgCaption = QString( "%1 Model Unmet Load Hours" ).arg( osRunInfo[iR].LongRunID() );
																		QMessageBox msgBox;
																		msgBox.setWindowTitle( qstrUMLHDlgCaption );
																		msgBox.setIcon( QMessageBox::Warning ); 
																		msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
																		msgBox.setText( qstrUMLHWarningMsg );
																		msgBox.setDetailedText( qstrUMLHWarningDetails );
																		msgBox.exec();
																	}
#endif
																}
															}

												// added copy of error message writing/processing from below to ensure error messages written to log for EVERY run resulting in errors
														if (!sErrMsg.isEmpty())
														{
															BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
															if (!osRunInfo[iR].IsStdRun())  // osRunInfo[iR].OSRunIdx() == 0 || osRunInfo[iR].OSRunIdx() == 2)
															{	// throw error only if UMLH limits exceeded for * Proposed models  - SAC 1/31/15
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
											sLogMsg.sprintf( "  PerfAnal_NRes - Completed analysis steps thru #%d", iAnalysisThruStep );
											BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
				if ((!bAbort && !BEMPX_AbortRuleEvaluation()) || bForceXMLFileWriteDespiteAbort)		// SAC 9/6/13 - added to ensure XML results file still written despite errors (to help diagnose problems in model...)
				{				if (bVerbose)
								{	sLogMsg.sprintf( "  PerfAnal_NRes - Exporting %s model details to results XML", sRunID.toLocal8Bit().constData() );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
								}
				// SAC 6/25/12 - added code to export detailed XML file following analysis
			      //QString sXMLFileName = sOriginalFileName;		//assert( sXMLFileName.lastIndexOf('.') == sXMLFileName.length()-4 );
//					if (!sXMLResultsFileName.isEmpty() && bStoreHourlyResults && !bThisOSSimSkipped)
					if (!sXMLResultsFileName.isEmpty() && bStoreHourlyResults && bSimRunsNow)
					{	for (int iR=0; iR <= iSimRunIdx; iR++)
							if (osRunInfo[iR].OSRunIdx() >= 0 && osRunInfo[iR].RunID().length() > 0)
							{	// SAC 1/6/15 - added args to prevent export of PolyLp objects (and in turn, also CartesianPts)
								// SAC 1/11/15 - added new argument to prevent export of RULE NEW (ruleset-defined) properties to all models following User Model
								BOOL bXMLWriteOK = xmlResultsFile.WriteModel( TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, osRunInfo[iR].LongRunID().toLocal8Bit().constData(),
																								osRunInfo[iR].BEMProcIdx(), false /*bOnlyValidInputs*/, 1 /*iNumClassIDsToIgnore*/, &iCID_PolyLp /*piClassIDsToIgnore*/,
																								bWriteRulePropsToResultsXML /*bWritePropertiesDefinedByRuleset*/, true /*bUseReportPrecisionSettings*/ );			assert( bXMLWriteOK );
								if (bVerbose)  // SAC 1/31/13
								{	sLogMsg.sprintf( "      Writing of %s model XML project data successful: %s", osRunInfo[iR].RunID().toLocal8Bit().constData(), (bXMLWriteOK ? "True" : "False") );
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}		}	}
				}
			}
			BEMPX_RefreshLogFile();	// SAC 5/19/14

			if (bSimRunsNow)		// SAC 8/19/15
			{	iSimRunIdx = iProgressModelSum = 0;
			}
			else if (bModelToBeSimulated[iRun])
				iSimRunIdx++;
		}	// end of:  for iRun = 0-iNumRuns
		if (iRetVal == 0)
			xmlResultsFile.Close();

		if (iRetVal == 0 && iCodeType == CT_T24N)
		{	// SAC 8/28/17 - moved some results code up here to enable Pass/Fail result to impact bSendRptSignature
			bHaveResult = (	!bAbort && iRetVal == 0 &&
									!sXMLResultsFileName.isEmpty() && FileExists( sXMLResultsFileName.toLocal8Bit().constData() ) &&
									iAnalysisThruStep >= 8 && !pbBypassOpenStudio[0] && !pbBypassOpenStudio[1] && !pbBypassOpenStudio[2] && !pbBypassOpenStudio[3] &&
									BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:PassFail"   ), sResTemp1 ) &&
									BEMPX_GetString(  BEMPX_GetDatabaseID( "EUseSummary:Enduse8[8]" ), sResTemp2 ) );
			bResultIsPass = (bHaveResult && (sResTemp1.indexOf("PASS") >= 0 || sResTemp1.indexOf("Pass") >= 0 || sResTemp1.indexOf("pass") >= 0));
		}

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
					bool bRptToGen = false, bRptVerbose = bVerbose;
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
							sLogMsg.sprintf( "Compliance report(s) called for but bypassed due to %s.", (iRptGenAvail<0 ? "report generation being offline" : "report generator website not accessible") );
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							// iRetVal = 45;
							bRptToGen = false;  // iRpt = 1;	iMaxRpt = 0;
					}	}

					QString sLogMsg2;
		// SAC 8/24/17 - mods to support single-pass report generation
		//			for (; (iRetVal == 0 && iRpt <= iMaxRpt); iRpt++)
					if (bRptToGen)  // baDoRpt[iRpt])
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
								sMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
								             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
												 "(once the file is closed), or \n'Abort' to abort the %s.", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData(), "overwriting of this file" );
								if (!OKToWriteOrDeleteFile( sOutRptFN.toLocal8Bit().constData(), sMsg, bSilent ))
								{	if (iRptChk==0)
									{	if (bSilent)
											sLogMsg.sprintf( "   Reporting disabled due to inability to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg.sprintf( "   Reporting disabled due to user choosing not to overwrite main report output file:  %s", sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum = 0;  // toggle off generation of ALL reports
									}
									else
									{	if (bSilent)
											sLogMsg.sprintf( "   Unable to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										else
											sLogMsg.sprintf( "   User chose not to overwrite %s file:  %s", sRptChkExt.toLocal8Bit().constData(), sOutRptFN.toLocal8Bit().constData() );
										lRptIDNum -= iRptBitChk;  // toggle off generation of this rpt, but still proceed w/ others
									}
									BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									//iRetVal = 45;
								}
						}	}
						if (lRptIDNum > 0 && lRptIDNum != iOrigRptIDNum)
							// update RptIDNum in database to reflect report(s) removed from generation list in above loop
				      	BEMPX_SetBEMData( lDBID_RptIDNum, BEMP_Int, (void*) &lRptIDNum, BEMO_User, -1, BEMS_ProgDefault );

						if (lRptIDNum > 0 && bSendRptSignature && (!bHaveResult || !bResultIsPass))	// toggle OFF report security if compliance result is undefined or 'Fail'
						{	// SAC 8/28/17 - prevent report signature if compliance result NOT PASS
							if (!bHaveResult)
								sLogMsg = "Compliance report will be generated without security measures due to compliance result not calculated";
							else if (!bResultIsPass)
								sLogMsg = "Compliance report will be generated without security measures due to non-passing compliance result";
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							bSendRptSignature = false;
						}

						if (lRptIDNum > 0)  // baDoRpt[iRpt])
						{
		//					QString sPDFOnly = "Proj:CompReportNum";  // SAC 8/24/17 - was: (iRpt!=1 ? "true" : "false");
							QString sDebugRpt = (bVerbose ? "true" : "false");
		//					QString sRptNameProp = (iRpt==2 ? "RptGenStdReport" : "RptGenCompReport");		// SAC 11/13/15
							QString sRptNameProp = "RptGenCompReport";

//sLogMsg.sprintf( "Pausing before %s report generation on:  %s", (iRpt==0 ? "pdf" : "full"), sResFN );
//BEMMessageBox( sLogMsg, "" );

									if (bVerbose)
		//							{	sLogMsg2.sprintf( "      about to generate %s compliance report:  %s", (iRpt!=1 ? "pdf" : "full"), sXMLResultsFileName.toLocal8Bit().constData() );
									{	sLogMsg2.sprintf( "      about to generate compliance report(s):  %s", sXMLResultsFileName.toLocal8Bit().constData() );
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
																	(sNetComLibrary.isEmpty()          ? NULL : (const char*) sNetComLibrary.toLocal8Bit().constData()), iSecurityKeyIndex, false );		// SAC 11/5/15   // SAC 1/10/17   // SAC 8/25/17
							dTimeToReport += DeltaTime( tmMark );		// log time spent generating report
							iNumTimeToReport++; 
							tmAnalOther = boost::posix_time::microsec_clock::local_time();		// reset timer for "other" bucket
										if (bVerbose || iRptGenRetVal != 0)
		//								{	sLogMsg2.sprintf( "      generation of %s compliance report %s (returned %d)", (iRpt!=1 ? "pdf" : "full"), (iRptGenRetVal==0 ? "succeeded" : "failed"), iRptGenRetVal );
										{	sLogMsg2.sprintf( "      generation of compliance report(s) %s (returned %d)", (iRptGenRetVal==0 ? "succeeded" : "failed"), iRptGenRetVal );
											BEMPX_WriteLogFile( sLogMsg2, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
							if (iRptGenRetVal != 0)
							{	sLogMsg.sprintf( "   Error (%d) encountered generating compliance report file:  %s", iRptGenRetVal, sOutRptFN.toLocal8Bit().constData() );
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

								long lOne = 1;
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
			}	}
			BEMPX_RefreshLogFile();	// SAC 5/19/14
		}
	// end of: COMPLIANCE REPORT GENERATION   - SAC 9/14/13
	// ----------
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
	QString sAnalResLogMsg, sAnalTimeStats;
	if (bAbort)
		sAnalResLogMsg = "Analysis aborted";
	else if (iRetVal != 0 || sXMLResultsFileName.isEmpty() || !FileExists( sXMLResultsFileName.toLocal8Bit().constData() ))
		sAnalResLogMsg = "Analysis errant";
	else if (iAnalysisThruStep < 8 ||
					pbBypassOpenStudio[0] || pbBypassOpenStudio[1] || pbBypassOpenStudio[2] || pbBypassOpenStudio[3] ) // ||
			//		pbBypassSimulation[0] || pbBypassSimulation[1] || pbBypassSimulation[2] || pbBypassSimulation[3] )
		sAnalResLogMsg = "Analysis incomplete";
	else if (!bHaveResult)
		sAnalResLogMsg = "Analysis result unknown";
	else
	{	sAnalResLogMsg.sprintf( "Analysis result:  %s  (TDV margin: %s)", sResTemp1.toLocal8Bit().constData(), sResTemp2.toLocal8Bit().constData() );
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
	sAnalTimeStats.sprintf( "  Processing time:  Overall %d:%.2d / SDD2IDF x%d%s%d:%.2d / SizSim x%d%s%d:%.2d / AnnSim x%d%s%d:%.2d / ReportGen x%d %d:%.2d / Other %d:%.2d",	// SAC 11/5/14 - 'SDD2OSM' -> 'SDD2IDF'
						int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)),
						iNumTimeToTranslate, (iNumTimeToTranslate > 1 ? " avg " : " "), int(dTimeTotTrans/60), int(fmod(dTimeTotTrans, 60.0)), 
						iNumTimeToSimDsgn  , (iNumTimeToSimDsgn   > 1 ? " avg " : " "), int(dTimeTotDsgn /60), int(fmod(dTimeTotDsgn , 60.0)), 
						iNumTimeToSimAnn   , (iNumTimeToSimAnn    > 1 ? " avg " : " "), int(dTimeTotAnn  /60), int(fmod(dTimeTotAnn  , 60.0)), 
						iNumTimeToReport, int(dTimeToReport/60), int(fmod(dTimeToReport, 60.0)), int(dTimeToOther/60), int(fmod(dTimeToOther, 60.0)) );
	sAnalResLogMsg += sAnalTimeStats;
	BEMPX_WriteLogFile( sAnalResLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	if (bVerbose)
	{	sLogMsg.sprintf( "      Final return value from CMX_PerformAnalysis_CECNonRes():  %d", iRetVal );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	if (bRestoreBEMProcLogTimeStampSetting)		// SAC 11/17/13 - restore BEMProc log timestamp setting (if it was toggled during analysis)
		BEMPX_EnableLogTimeStamps( bInitialBEMProcLogTimeStamp );


// SAC 5/5/15 - ResultSummary Logging
		sLogMsg.sprintf( "      ResultsSummary population:  bAbort = (%s) / RuleProcAbort = (%s) / iRetVal = %d / pszResultsSummary = %s / iResultsSummaryLen = %d", (bAbort ? "true" : "false"),
				(BEMPX_AbortRuleEvaluation() ? "true" : "false"), iRetVal, (pszResultsSummary  == NULL ? "(null)" : (strlen( pszResultsSummary  ) < 1 ? "(empty)" : pszResultsSummary )), iResultsSummaryLen );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
// SAC 5/16/14 - added code to populate record of analysis results
	if (!bAbort && !BEMPX_AbortRuleEvaluation() && pszResultsSummary && iResultsSummaryLen > 1)
	{	//CTime locTime = CTime::GetCurrentTime();
		QDateTime locTime = QDateTime::currentDateTime();
		QString sTimeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss");

		QString sWthrStn, sAnalType, sPropSimSummary, sStdSimSummary, sAppVer, sCmpMgrVer, sRulesetID, sRuleVer, sAnnWthrFile, sEPlusVer;
		double dRptTotArea, dRptCndArea;   // SAC 2/19/17
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"       ), sRunTitle );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:WeatherStation" ), sWthrStn  );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnalysisType"   ), sAnalType );
		BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:SimSummary" )  , sPropSimSummary, FALSE, 0, -1, -1, BEMO_User, "unknown" );
		BEMPX_GetString( BEMPX_GetDatabaseID( "EUseSummary:SimSummary" )+2, sStdSimSummary , FALSE, 0, -1, -1, BEMO_User, "unknown" );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion"    ), sAppVer    );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), sCmpMgrVer );
	//	BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Ruleset"            ), sRuleVer   );
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:AnnualWeatherFile"  ), sAnnWthrFile );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotFlrArea"      ), dRptTotArea );
		BEMPX_GetFloat(  BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), dRptCndArea );
		if (pszEPlusVerStr && strlen( pszEPlusVerStr ) > 0)
			sEPlusVer = pszEPlusVerStr;
		else if (dEPlusVer > 0.1)
			sEPlusVer.sprintf( "%g", dEPlusVer );
		else
			sEPlusVer = "???";
		QString sOSVer = "???";
		if (pszOpenStudioVerStr && strlen( pszOpenStudioVerStr ) > 0)
			sOSVer = pszOpenStudioVerStr;
		if (sCSEVersion.isEmpty())
			sCSEVersion = "-";

		if (!CMX_GetRulesetID( sRulesetID, sRuleVer ))
		{	assert( FALSE );
			sRuleVer = "???";
		}

		double fEnergyResults[2][5][NUM_T24_NRES_EndUses];		// Prop/Std -- Elec/NGas/Othr/TDV/ElecKW -- SpcHtg/SpcClg...ProcLtg/ProcMtrs/PV/Battery/TOTAL		- SAC 10/10/16 - added elec demand  - SAC 2/7/17 - added ProcMtrs  - SAC 7/20/18 - added PV&Batt & switched to use of NUM_T24_NRES_EndUses
		double fEnergyCosts[2][4] = { {0,0,0,0}, {0,0,0,0} };	// Prop/Std -- Elec/NGas/Othr/TOTAL
		long lDBID_Res[2][5]		= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherEnergy" ), BEMPX_GetDatabaseID( "EnergyUse:ProposedTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropElecDemand" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherEnergy"  ), BEMPX_GetDatabaseID( "EnergyUse:StandardTDV" ), BEMPX_GetDatabaseID( "EnergyUse:StdElecDemand"  ) } };
		long lDBID_Costs[2][4]	= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherCost" ), BEMPX_GetDatabaseID( "EnergyUse:PropTotalCost" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherCost"  ), BEMPX_GetDatabaseID( "EnergyUse:StdTotalCost"  ) } };
		double fTDVbyFuel[2][3] = { {0,0,0}, {0,0,0} };	// TDV results: Prop/Std - Elec/NGas/Othr  - SAC 2/19/17
		long lDBID_TDVbF[2][3]	= { {	BEMPX_GetDatabaseID( "EnergyUse:PropElecTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropNatGasTDV" ), BEMPX_GetDatabaseID( "EnergyUse:PropOtherTDV" ) },
											 { BEMPX_GetDatabaseID( "EnergyUse:StdElecTDV"  ), BEMPX_GetDatabaseID( "EnergyUse:StdNatGasTDV"  ), BEMPX_GetDatabaseID( "EnergyUse:StdOtherTDV"  ) } };

//           "PropElecSupEnergy", BEMP_Flt,  1,  0,  0,  Pres,  "kWh",              0,  0,                39110, "Proposed run Electric energy SUPPLY for this enduse (negative value)",  ""  ; SAC 9/7/18
//           "PropElecSupTDV",    BEMP_Flt,  1,  0,  0,  Pres,  "kTDV/ft2-yr",      0,  0,                39110, "Proposed run Electric SUPPLY TDV for this enduse (negative value)",  "" 
//           "StdElecSupEnergy",  BEMP_Flt,  1,  0,  0,  Pres,  "kWh",              0,  0,                39110, "Standard run Electric energy SUPPLY for this enduse (negative value)",  "" 
//           "StdElecSupTDV",     BEMP_Flt,  1,  0,  0,  Pres,  "kTDV/ft2-yr",      0,  0,                39110, "Standard run Electric SUPPLY TDV for this enduse (negative value)",  "" 

		int iNumBadResults=0, iNumResAttempts=0,  iNumBadEDResults=0, iNumEDResAttempts=0;
		for (int iRR=0; iRR<2; iRR++)
			for (int iRF=0; iRF<5; iRF++)
			{	int iMaxREU = NUM_T24_NRES_EndUses-1;   // SAC 2/19/17 - was: (iRF==3 ? 7 : 12);  - SAC 7/20/18 - 12->NUM_T24_NRES_EndUses-1
				for (int iREU=0; iREU<=iMaxREU; iREU++)
				{	if (iCodeType == CT_T24N || iRF != 3)	// SAC 10/7/14 - store TDV results only for T24 runs
					{	if (iRF==4)	// elec demand
							iNumEDResAttempts++;
						else
							iNumResAttempts++;
						if (!BEMPX_GetFloat(  lDBID_Res[iRR][iRF], fEnergyResults[iRR][iRF][iREU], 0, -1,  iREU ))
						{	if (iRF==4)	// elec demand
								iNumBadEDResults++;
							else
								iNumBadResults++;
							fEnergyResults[iRR][iRF][iREU] = 0;
					}	}
					else
						fEnergyResults[iRR][iRF][iREU] = 0;
				}
			// storage of energy COST results
				if (iRF<4 && (iCodeType == CT_S901G || iCodeType == CT_ECBC))
					BEMPX_GetFloat(  lDBID_Costs[iRR][iRF], fEnergyCosts[iRR][iRF], 0, -1, iMaxREU /*index of Total enduse*/ );	// SAC 7/20/18 - Tot EU idx 12->iMaxREU following addition of PV & Battery
			// storage of TDV by Fuel results  - SAC 2/19/17
				if (iRF<3 && iCodeType == CT_T24N)
					BEMPX_GetFloat(  lDBID_TDVbF[iRR][iRF], fTDVbyFuel[iRR][iRF], 0, -1, iMaxREU /*index of Total enduse*/ );	// SAC 7/20/18 - Tot EU idx 12->iMaxREU following addition of PV & Battery
			}
			if (bExpectValidResults && iNumBadResults >= iNumResAttempts)
			{	assert( FALSE );	// was expecting valid results, but NONE were retrievable
			}
		bool bHaveElecDemandResults = (iNumBadEDResults < iNumEDResAttempts);	// SAC 10/11/16

	  // UMLH reporting
		double fPropMaxClgUMLHs, fPropMaxHtgUMLHs, fStdMaxClgUMLHs, fStdMaxHtgUMLHs;
		QString sPropMaxClgUMLHZnName, sPropMaxHtgUMLHZnName, sStdMaxClgUMLHZnName, sStdMaxHtgUMLHZnName, sPropClgUMLHData, sPropHtgUMLHData, sStdClgUMLHData, sStdHtgUMLHData;
		long lPropClgNumZonesExceed, lPropHtgNumZonesExceed, lStdClgNumZonesExceed, lStdHtgNumZonesExceed;
		if (BEMPX_GetModelCount() < 4)  // SAC 10/28/13
		{		sPropClgUMLHData = ",,";
				sPropHtgUMLHData = ",,";
		}
		else
		{	if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedClgUnmetLdHrs", iCID_Proj ), lPropClgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     3 /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrs"       , iCID_Proj ), fPropMaxClgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     3 /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		 BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName"   , iCID_Proj ), sPropMaxClgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, 3 /*iBEMProcIdx*/ );
				if (sPropMaxClgUMLHZnName.isEmpty())
					sPropClgUMLHData.sprintf( "%g,,%d", fPropMaxClgUMLHs, lPropClgNumZonesExceed );
				else
					sPropClgUMLHData.sprintf( "%g,\"%s\",%d", fPropMaxClgUMLHs, sPropMaxClgUMLHZnName.toLocal8Bit().constData(), lPropClgNumZonesExceed );
			}
			else
				sPropClgUMLHData = ",,";

			if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedHtgUnmetLdHrs", iCID_Proj ), lPropHtgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     3 /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrs"       , iCID_Proj ), fPropMaxHtgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     3 /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		 BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName"   , iCID_Proj ), sPropMaxHtgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, 3 /*iBEMProcIdx*/ );
				if (sPropMaxHtgUMLHZnName.isEmpty())
					sPropHtgUMLHData.sprintf( "%g,,%d", fPropMaxHtgUMLHs, lPropHtgNumZonesExceed );
				else
					sPropHtgUMLHData.sprintf( "%g,\"%s\",%d", fPropMaxHtgUMLHs, sPropMaxHtgUMLHZnName.toLocal8Bit().constData(), lPropHtgNumZonesExceed );
			}
			else
				sPropHtgUMLHData = ",,";
		}
		if (BEMPX_GetModelCount() < 5)  // SAC 10/28/13
		{		sStdClgUMLHData = ",,";
				sStdHtgUMLHData = ",,";
		}
		else
		{	if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedClgUnmetLdHrs", iCID_Proj ), lStdClgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     4 /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrs"       , iCID_Proj ), fStdMaxClgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     4 /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		 BEMPX_GetDatabaseID( "MaxZnClgUnmetLdHrsName"   , iCID_Proj ), sStdMaxClgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, 4 /*iBEMProcIdx*/ );
				if (sStdMaxClgUMLHZnName.isEmpty())
					sStdClgUMLHData.sprintf( "%g,,%d", fStdMaxClgUMLHs, lStdClgNumZonesExceed );
				else
					sStdClgUMLHData.sprintf( "%g,\"%s\",%d", fStdMaxClgUMLHs, sStdMaxClgUMLHZnName.toLocal8Bit().constData(), lStdClgNumZonesExceed );
			}
			else
				sStdClgUMLHData = ",,";

			if (	BEMPX_GetInteger( BEMPX_GetDatabaseID( "NumZnsExceedHtgUnmetLdHrs", iCID_Proj ), lStdHtgNumZonesExceed, 0, -1,  0 /*iOccur*/, BEMO_User,     4 /*iBEMProcIdx*/ ) &&
					BEMPX_GetFloat(   BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrs"       , iCID_Proj ), fStdMaxHtgUMLHs      , 0, -1,  0 /*iOccur*/, BEMO_User,     4 /*iBEMProcIdx*/ ) )
			{	BEMPX_GetString(		 BEMPX_GetDatabaseID( "MaxZnHtgUnmetLdHrsName"   , iCID_Proj ), sStdMaxHtgUMLHZnName , FALSE, 0, -1, 0, BEMO_User, NULL, 0, 4 /*iBEMProcIdx*/ );
				if (sStdMaxHtgUMLHZnName.isEmpty())
					sStdHtgUMLHData.sprintf( "%g,,%d", fStdMaxHtgUMLHs, lStdHtgNumZonesExceed );
				else
					sStdHtgUMLHData.sprintf( "%g,\"%s\",%d", fStdMaxHtgUMLHs, sStdMaxHtgUMLHZnName.toLocal8Bit().constData(), lStdHtgNumZonesExceed );
			}
			else
				sStdHtgUMLHData = ",,";
		}

		QString sElecDemandResults;
		if (bHaveElecDemandResults && iCodeType == CT_T24N)	// SAC 10/11/16
		{	sElecDemandResults.sprintf( "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,",
				// Proposed model electric demand
						fEnergyResults[0][4][ 0], fEnergyResults[0][4][ 1], fEnergyResults[0][4][ 2], fEnergyResults[0][4][ 3], fEnergyResults[0][4][ 4], fEnergyResults[0][4][ 5], fEnergyResults[0][4][ 6], fEnergyResults[0][4][ 7],
						fEnergyResults[0][4][ 8], fEnergyResults[0][4][ 9], fEnergyResults[0][4][10], fEnergyResults[0][4][11], fEnergyResults[0][4][12], fEnergyResults[0][4][13], fEnergyResults[0][4][14],
				// Standard model electric demand
						fEnergyResults[1][4][ 0], fEnergyResults[1][4][ 1], fEnergyResults[1][4][ 2], fEnergyResults[1][4][ 3], fEnergyResults[1][4][ 4], fEnergyResults[1][4][ 5], fEnergyResults[1][4][ 6], fEnergyResults[1][4][ 7],
						fEnergyResults[1][4][ 8], fEnergyResults[1][4][ 9], fEnergyResults[1][4][10], fEnergyResults[1][4][11], fEnergyResults[1][4][12], fEnergyResults[1][4][13], fEnergyResults[1][4][14]  );
		}
		else
			sElecDemandResults = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

// SAC 5/5/15 - ResultSummary Logging
	sLogMsg.sprintf( "      ResultsSummary components1:  %s / %s / %s / %s / %s / %d:%.2d / %s / %s", 
						sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(),
						sAnalType.toLocal8Bit().constData(), int(dTimeOverall/60), int(fmod(dTimeOverall, 60.0)), sResTemp1.toLocal8Bit().constData() /*PassFail*/, sResTemp2.toLocal8Bit().constData() /*CompMargin*/ );
	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	sLogMsg.sprintf( "      ResultsSummary components2:  %s / %s / %s / %s / %s / %s / %s / %s", 
						sAppVer.toLocal8Bit().constData(), sCmpMgrVer.toLocal8Bit().constData(), sRuleVer.toLocal8Bit().constData(), sOSVer.toLocal8Bit().constData(), 
						sEPlusVer.toLocal8Bit().constData(), sCSEVersion.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(), sModelPathOnly.toLocal8Bit().constData() );
	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

#pragma warning(disable:4996)
		if (iCodeType == CT_T24N)		// SAC 10/7/14 - export of TDV results needed only for T24 analysis
			_snprintf( pszResultsSummary, iResultsSummaryLen, "%s,\"%s\",\"%s\",\"%s\",%g,%g,\"%s\",%d:%.2d,%s,%s,"					// begin thru CompMargin
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// prop      - SAC 7/20/18 - addition of PV & Batt Elec enduses
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,"    // prop
							"\"%s\",\"%s\",\"%s\",%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"		// std
							"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%s,%s,"    // std
							"%s"                                                                                                     // prop & std kW
							"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",
						sTimeStamp.toLocal8Bit().constData(), sModelFileOnly.toLocal8Bit().constData(), sRunTitle.toLocal8Bit().constData(), sWthrStn.toLocal8Bit().constData(), dRptCndArea, dRptTotArea,  // SAC 2/18/17
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
						fEnergyResults[0][3][ 6], fEnergyResults[0][3][ 7], fEnergyResults[0][3][ 8], fEnergyResults[0][3][ 9], fEnergyResults[0][3][10], fEnergyResults[0][3][11], fEnergyResults[0][3][12], fEnergyResults[0][3][13], fEnergyResults[0][3][14],
						fTDVbyFuel[0][0],	fTDVbyFuel[0][1],	fTDVbyFuel[0][2],	// TDV results: Prop - Elec/NGas/Othr  - SAC 2/19/17
						sPropClgUMLHData.toLocal8Bit().constData(), sPropHtgUMLHData.toLocal8Bit().constData(),			// UMLHs
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
						sEPlusVer.toLocal8Bit().constData(), sCSEVersion.toLocal8Bit().constData(), sSimWeatherPath.toLocal8Bit().constData(), sModelPathOnly.toLocal8Bit().constData() );

		else if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14 - export of Energy Cost results needed only for 90.1 analysis
			_snprintf( pszResultsSummary, iResultsSummaryLen, "%s,\"%s\",\"%s\",\"%s\",\"%s\",%d:%.2d,%s,%s,"
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

// SAC 5/5/15 - ResultSummary Logging
		sLogMsg.sprintf( "      ResultsSummary:  %s", pszResultsSummary );
		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

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
			{	sLogMsg.sprintf( "Analysis aborted due to callback function return value of %ld (value must be 0 to continue processing).", slAnalysisProgressCallbackRetVal );
				BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
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

	// SAC 5/28/15 - callback mechanism - reset static function pointer
	if (pAnalProgCallbackFunc)
	{	spAnalProgCallbackFunc = NULL;
		slAnalysisProgressCallbackRetVal = 0;
	}

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////

#define  CM_MAX_BATCH_VER  3		// SAC 6/21/18 - 2->3 (CSE path)

int path_len( std::string& str )
{	int iPathLen = -1, iPathLen2 = -1;
	if (str.rfind('\\') != std::string::npos)
		iPathLen  = str.rfind('\\');
	if (str.rfind('/' ) != std::string::npos)
		iPathLen2 = str.rfind('/' );
	return std::max( iPathLen, iPathLen2 );
}

int CMX_PerformBatchAnalysis_CECNonRes(	const char* pszBatchPathFile, const char* pszProjectPath, const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
														const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath,
														const char* /*pszLogPathFile*/, const char* pszUIVersionString, const char* pszOptionsCSV /*=NULL*/,
														char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool /*bDisplayProgress=false*/, HWND hWnd /*=NULL*/, bool bOLDRules /*=false*/,
														int iSecurityKeyIndex /*=0*/, const char* pszSecurityKey /*=NULL*/, char* pszResultMsg /*=NULL*/, int iResultMsgLen /*=0*/ )   // SAC 1/10/17   // SAC 12/3/17
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
	int iLenOptionsCSVArg = (pszOptionsCSV ? strlen( pszOptionsCSV ) : 0);

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
	if (!OKToWriteOrDeleteFile( sBatchLogPathFile.c_str(), sOverwriteProjFileMsg.c_str() ))
	{	if (pszErrorMsg && iErrorMsgLen > 0)
			sprintf_s( pszErrorMsg, iErrorMsgLen, "Unable to write to batch processing log file:  %s", sBatchLogPathFile );
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
														-1  };
	std::string line;
	int iMode = 0;		// <0-Error Code / 0-Reading Header / 1-Reading Run Records
	int iBatchVer = 1, iRunRecord = 0, iBatchRecNum = 0, iRunsToPerform = 0;
	std::string sBatchResultsFN, sBatchLogFN, sOverwriteResultsFileMsg, sLogMsg, sErrMsg;
	std::string sRecProjInFN, sRecProjOutFN, sRecRunTitle, sRecOutput, sRecOptionCSV, sRecCopySimXMLToPath, sRecCopyCSEToPath;
	int iRecAutosizeP=0, iRecAutosizeBZ=0, iRecAutosizeB=0;
	std::vector<std::string> saProjInFN, saProjOutFN, saRunTitle, saOutput, saOptionCSV, saCopySimXMLToPath, saCopyCSEToPath, saBEMBaseFN, saRulesetFN;
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
						if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
						{			iMode = -3;
									sErrMsg = boost::str( boost::format( "Error:  Unable to write to batch results file specified in record %d:  '%s'" )
																						% iBatchRecNum % sBatchResultsFN.c_str() );
						}
						else
							iMode = 1;
					}
				}
			}
			else if (iMode == 1 && lines[0].size() > 0)
			{
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
						std::string sThisBEMBaseFN, sThisProjRulesetFN;
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
							if (!OKToWriteOrDeleteFile( sRecProjOutFN.c_str(), sOverwriteProjFileMsg.c_str() ))
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
						{	sRecRunTitle = lines[0][iFld++];
							if (lines[0][iFld++].size() < 1)
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
							if (iLenOptionsCSVArg > 0)
								sRecOptionCSV += pszOptionsCSV;
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
			int iLastDotIdx   = sProjPathFile.rfind('.');			assert( iLastDotIdx   > 0 );
			int iLastSlashIdx = path_len( sProjPathFile );			assert( iLastSlashIdx > 0 );
			std::string sProcessingPath = sProjPathFile.substr( 0, iLastDotIdx );
			sProcessingPath += " - batch\\";
			std::string sProjPath = sProjPathFile.substr( 0, iLastSlashIdx+1 );
			if (!DirectoryExists( sProjPath.c_str() ))
				CreateAndChangeDirectory( sProjPath.c_str(), FALSE );
			if (!boost::iequals( saProjInFN[iRun].c_str(), sProjPathFile.c_str() ) &&   // only copy IN to OUT file if they are different
			    !CopyFile( saProjInFN[iRun].c_str(), sProjPathFile.c_str(), FALSE ))
			{
									sErrMsg = boost::str( boost::format( "Error:  Unable to copy project file (run %d, record %d):  '%s'  to:  '%s'" )
																						% (iRun+1) % iaBatchRecNums[iRun] % saProjInFN[iRun].c_str() % sProjPathFile.c_str() );
			}

			if (sErrMsg.size() < 1)
			{
				int iAnalRetVal = -1;
				assert( !bOLDRules );
				char pszResultsRecord[2056] = "\0";
					iAnalRetVal = CMX_PerformAnalysis_CECNonRes( saBEMBaseFN[iRun].c_str() /*pszBEMBasePathFile*/, saRulesetFN[iRun].c_str() /*pszRulesetPathFile*/,
												pszSimWeatherPath, pszCompMgrDLLPath, pszDHWWeatherPath, sProcessingPath.c_str(), sProjPathFile.c_str(),
												sBatchLogPathFile.c_str() /* ??? use overall batch OR individual Project Log File ??? */,
												pszUIVersionString, true /*bLoadModelFile*/, saOptionCSV[iRun].c_str(), pszRuleErr, 1024,
												true /*bDisplayProgress*/, hWnd, pszResultsRecord, 2056, iSecurityKeyIndex, pszSecurityKey );   // SAC 1/10/17
				if (iAnalRetVal == 33)
				{	// User aborted individual run, so ask if they want to abort ALL remaining runs
									sErrMsg = boost::str( boost::format( "User aborted batch run %d (record %d)..." ) % (iRun+1) % iaBatchRecNums[iRun] );
					if (iRun < (iRunsToPerform - 1))
					{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
						if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
							bAbort = true;
					}
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

//	if (iRun < (iRunsToPerform - 1) && ::MessageBox( hWnd, "Confirm Continue", "Run Succeeded ... Continue w/ remaining runs?", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) != IDYES)
//		bAbort = true;

	      		//CTime locTime = CTime::GetCurrentTime();
					QDateTime locTime = QDateTime::currentDateTime();

				// SAC 12/3/14 - logic identical to analysis routine to identify ruleset type - used to determine which CSV results file headers to use
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

				// SAC 2/2/14 - mods to store analysis results back to project file
					bool bStoreResultsToModelInput =	(GetCSVOptionValue( "StoreResultsToModelInput", 1, saCSVOptions ) > 0);
					if (bStoreResultsToModelInput)
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
						{
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
					if (sErrMsg.size() < 1 && saCopySimXMLToPath[iRun].size() > 0)
					{	int iProjOutPathLen    = path_len( sProjPathFile ) + 1;										assert( iProjOutPathLen > 3 );
						int iProjOutFileExtLen = sProjPathFile.length() - sProjPathFile.rfind('.');			assert( iProjOutFileExtLen > 2 && iProjOutFileExtLen < 8 );
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
									if (!OKToWriteOrDeleteFile( sFileToWrite.c_str(), sOverwriteSDDXMLMsg.c_str() ))
									{	sLogMsg = boost::str( boost::format( "Unable to overwrite simulation SDD XML file (run %d, record %d).\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
										if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
											bAbort = true;
										else
										{	sLogMsg = boost::str( boost::format( "User chose not to overwrite simulation SDD XML file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sFileToWrite.c_str() );
											BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
									}
									else if (!CopyFile( sSimSDDXMLSrc.c_str(), sFileToWrite.c_str(), FALSE ))
									{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
										sLogMsg = boost::str( boost::format( "Error encountered copying simulation SDD XML file (run %d, record %d) from '%s' to '%s'" ) % (iRun+1) % iaBatchRecNums[iRun] % sSimSDDXMLSrc.c_str() % sFileToWrite.c_str() );
										BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
							}	}
					}	}

				// COPY CSE files to specified location
					if (sErrMsg.size() < 1 && saCopyCSEToPath[iRun].size() > 0)
					{	int iProjOutPathLen    = path_len( sProjPathFile ) + 1;										assert( iProjOutPathLen > 3 );
						int iProjOutFileExtLen = sProjPathFile.length() - sProjPathFile.rfind('.');			assert( iProjOutFileExtLen > 2 && iProjOutFileExtLen < 8 );
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
									if (!OKToWriteOrDeleteFile( sFileToWrite.c_str(), sOverwriteCSEMsg.c_str() ))
									{	sLogMsg = boost::str( boost::format( "Unable to overwrite CSE file (run %d, record %d).\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
										if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
											bAbort = true;
										else
										{	sLogMsg = boost::str( boost::format( "User chose not to overwrite CSE file (run %d, record %d):  %s" ) % (iRun+1) % iaBatchRecNums[iRun] % sFileToWrite.c_str() );
											BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
										}
									}
									else if (!CopyFile( sCSESrc.c_str(), sFileToWrite.c_str(), FALSE ))
									{	// DON'T ABORT ANALYSIS - simply report copy issue to log file
										sLogMsg = boost::str( boost::format( "Error encountered copying CSE file (run %d, record %d) from '%s' to '%s'" ) % (iRun+1) % iaBatchRecNums[iRun] % sCSESrc.c_str() % sFileToWrite.c_str() );
										BEMPX_WriteLogFile( sLogMsg.c_str(), NULL /*psNewLogFileName*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
							}	}
					}	}

					if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
					{	if (iRun < (iRunsToPerform - 1))
						{	sLogMsg = boost::str( boost::format( "Batch run %d (record %d) aborted.\n\nWould you like to abort remaining %d runs?" ) % (iRun+1) % iaBatchRecNums[iRun] % (iRunsToPerform - iRun - 1) );
							if (::MessageBox( hWnd, sLogMsg.c_str(), "Confirm Batch Abort", MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDYES)
								bAbort = true;
						}
					}
					else
					{
						bool bWriteHdrs = (!FileExists( sBatchResultsFN.c_str() ));

            //      bool bFileOK = false;
				//      CStdioFile csvFile;
				//		if (bWriteHdrs)
				//         bFileOK = (csvFile.Open( sBatchResultsFN.c_str(), CFile::modeCreate | CFile::modeWrite ) != 0);
				//		else
			   //      	bFileOK = (csvFile.Open( sBatchResultsFN.c_str(), CFile::modeWrite ) != 0);
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
							if (bWriteHdrs)
							{	// WRITE HEADER RECORDS
            //            csvFile.WriteString( GetResultsCSVHeader_NonRes( 1, iCodeType ) );
            //            csvFile.WriteString( GetResultsCSVHeader_NonRes( 2, iCodeType ) );
            //            csvFile.WriteString( GetResultsCSVHeader_NonRes( 3, iCodeType ) );
                        csvFile.write( GetResultsCSVHeader_NonRes( 1, iCodeType ) );
                        csvFile.write( GetResultsCSVHeader_NonRes( 2, iCodeType ) );
                        csvFile.write( GetResultsCSVHeader_NonRes( 3, iCodeType ) );
							}
				//			else
			   //      	   csvFile.SeekToEnd();

			   //      	csvFile.WriteString( pszResultsRecord );
			         	csvFile.write( pszResultsRecord );

							csvFile.flush();
							csvFile.close();
							bThisRunGood = true;
						}
					}
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
	for (int iRpt=0; iRpt <= iMaxRptIdx; iRpt++)
	{	QString sRpt;
		if (iRpt == saModelReportOptions.size())
			sRpt = sCurrentSelection;
		else
		{	sRpt = saModelReportOptions[iRpt];
			if (bCurSelValid && !sCurrentSelection.compare( sRpt ))
				iMaxRptIdx--;  // if got here and report being processed same as current selection, then avoid writing it twice (now and at end of looping)
		}

		if (!sRpt.isEmpty())
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
							{	sLogMsg.sprintf( "      about to generate '%s' model report:  %s", sRpt.toLocal8Bit().constData(), sRptPathFile.toLocal8Bit().constData() );
								BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							}
					int iRptRetVal = Local_GenerateRulesetModelReport( sRptPathFile, "rl_REPORT", bVerbose, bSilent );
					if (iRptRetVal > 0)
					{	sLogMsg.sprintf( "Error:  Model report generation failed w/ error code %d - report: '%s' - file: '%s'", iRptRetVal, sRpt.toLocal8Bit().constData(), sRptPathFile.toLocal8Bit().constData() );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
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
	{
	   BEMPX_GetString( lDBID_Proj_WeatherStation, sWeatherStation );
		if (!DirectoryExists( sWthrPath ))
		{	iRetVal = 2;
			sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Path containing weather files not found:  '%s'", sWthrPath.toLocal8Bit().constData() );
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
			if (lDBID_Proj_WeatherFileAppend > 0)
			   BEMPX_GetString( lDBID_Proj_WeatherFileAppend, sWeatherFileAppend );
			else
				sWeatherFileAppend = "_CZ2010";
			sAnnualWeatherFile = sWthrPath + sWeatherStation + sWeatherFileAppend + ".epw";
			sDDWeatherFile     = sWthrPath + sWeatherStation + sWeatherFileAppend + ".ddy";

			long lDBID_Proj_WeatherFileDownloadURL = BEMPX_GetDatabaseID( "Proj:WeatherFileDownloadURL" );		// SAC 9/15/14 - mods to enable internet download of wthr files (for S901G)
			if ( ( (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() )) || (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() )) ) && lDBID_Proj_WeatherFileDownloadURL && bAllowWthrDownload &&
				  BEMPX_GetString( lDBID_Proj_WeatherFileDownloadURL, sWeatherFileDownloadURL ) && !sWeatherFileDownloadURL.isEmpty() )
			{	// attempt to download weather file(s) needed for simulation
#ifndef CM_QTGUI
				iRetVal = 11;
				sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download not implemented when Qt GUI libraries not loaded:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );
				pszProxyAddress;		pszProxyCredentials;		pszProxyType;		// reference args not used in this mode to avoid compiler warnings
//#else
//#ifndef OSWRAPPER
//				iRetVal = 12;
//				sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download not implemented when OpenStudio not loaded:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );
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
						{	case  1 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - invalid storage path:  %s", sWthrZipPathFile.toLocal8Bit().constData() );					break;
							case  2 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - error downloading file:  %s", sWeatherFileDownloadURL.toLocal8Bit().constData() );			break;		// this error occurs when NORESCO proxy not able to be negotiated
							case  3 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - user chose not to overwrite file:  %s  -->>  %s", sWeatherFileDownloadURL.toLocal8Bit().constData(), sWthrZipPathFile.toLocal8Bit().constData() );		break;
							default :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed:  %s  -->>  %s", sWeatherFileDownloadURL.toLocal8Bit().constData(), sWthrZipPathFile.toLocal8Bit().constData() );	break;
					}	}
					else if (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ) && !OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(),
																																				sAnnualWeatherFileAlone.toLocal8Bit().constData(), sWthrPath.toLocal8Bit().constData() ))
					{	iRetVal = 13;
						sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Unable to extract hourly simulation weather file from download:  %s  -->>  %s/%s", sWeatherFileDownloadURL.toLocal8Bit().constData(), 
															sWthrZipPathFile.toLocal8Bit().constData(), sAnnualWeatherFileAlone.toLocal8Bit().constData() );
					}
					else if (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() ) && !OSWX_UnzipFile( sWthrZipPathFile.toLocal8Bit().constData(),
																																				sDDWeatherFileAlone.toLocal8Bit().constData(), sWthrPath.toLocal8Bit().constData() ))
					{	iRetVal = 14;
						sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Unable to extract design day simulation weather file from download:  %s  -->>  %s/%s", sWeatherFileDownloadURL.toLocal8Bit().constData(), 
															sWthrZipPathFile.toLocal8Bit().constData(), sDDWeatherFileAlone.toLocal8Bit().constData() );
				}	}
#endif
			}

			if (bAnnual && !FileExists( sAnnualWeatherFile.toLocal8Bit().constData() ))
			{	iRetVal = (iRetVal < 1 ? 4 : iRetVal);
				if (sErrMsg.isEmpty())
					sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file not found:  '%s'", sAnnualWeatherFile.toLocal8Bit().constData() );
			}
			else if (bDDY && !FileExists( sDDWeatherFile.toLocal8Bit().constData() ))
			{	iRetVal = (iRetVal < 1 ? 5 : iRetVal);
				if (sErrMsg.isEmpty())
					sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Design day simulation file not found:  '%s'", sDDWeatherFile.toLocal8Bit().constData() );
			}
		//	else		- modified to set wthr filename regardless of success or file presence
		//	{
				if (bAnnual)
				{	sAnnualWeatherFile.replace( '\\', '/' );  // replace backslashes w/ slashes to provide more universal compatibility
			      BEMPX_SetBEMData( lDBID_Proj_AnnualWeatherFile, BEMP_QStr, (void*) &sAnnualWeatherFile );
				}
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
//											 6 : 
int CMX_ExportCSVHourlyResults_Com( const char* pszHourlyResultsPathFile, const char* pszModelPathFile, const char* pszModelName, int iCodeType /*=0*/, char* pszErrMsgBuffer /*=NULL*/,
														int iErrMsgBufferLen /*=0*/, bool bSilent /*=false*/, int iBEMProcIdx /*=-1*/, const char* pszEPlusVerStr /*=NULL*/,
														const char* pszOpenStudioVerStr /*=NULL*/ )
{	int iRetVal = 0;
	QString sErrMsg;
	long lCliZnNum=0;
	double fCondFloorArea=0.0;
	QString sAnalysisType, sWeatherStation, sRunTitle;
	BOOL bExpectStdDesResults = TRUE;
	if (	!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:AnalysisType"    ), sAnalysisType   , TRUE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) ||
			!BEMPX_GetFloat(	 BEMPX_GetDatabaseID( "Bldg:TotCondFlrArea"  ), fCondFloorArea  ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) ||
			!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CliZnNum"        ), lCliZnNum       ,       0, -1, 0, BEMO_User,          iBEMProcIdx ) ||
			!BEMPX_GetString(  BEMPX_GetDatabaseID( "Proj:WeatherStation"  ), sWeatherStation , TRUE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) )
	{	iRetVal = 1;
		sErrMsg = "Error retrieving Proj:AnalysisType, CliZnNum, WeatherStation and/or Bldg:TotCondFlrArea";
	}
	else if (NUM_T24_NRES_EndUses != 15 || IDX_T24_NRES_EU_Total != 14)	// SAC 2/1/17 - added error check to prevent bomb below  // SAC 7/15/18 - updated expected total to 15 (for PV & Batt)
	{	iRetVal = 5;
		sErrMsg = QString("Unexpected enduse count (%1) or total index (%2) (expecting 15 and 14 respectively)").arg(QString::number(NUM_T24_NRES_EndUses), QString::number(IDX_T24_NRES_EU_Total));
	}
	else
	{	bExpectStdDesResults = (sAnalysisType.indexOf( "Compl" ) >= 0);
		BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:RunTitle"     ), sRunTitle );
		//BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:FuelTDVLabel" ), sFuelTDVLabel );
	}

	if (iRetVal == 0)
	{	QString sOverwriteMsg;
		sOverwriteMsg.sprintf(	"The hourly CSV results file '%s' is opened in another application.  This file must be closed in that "
										"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
										"(once the file is closed), or \n'Abort' to abort the hourly export.", pszHourlyResultsPathFile );
		if (!OKToWriteOrDeleteFile( pszHourlyResultsPathFile, sOverwriteMsg, bSilent ))
		{	iRetVal = 2;
			sErrMsg.sprintf( "Unable to open and/or write hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
	}

	if (iRetVal==0)
	{	long lRunDate = 0;
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
			sEPlusVer = "???";
		if (pszOpenStudioVerStr && strlen( pszOpenStudioVerStr ) > 0)
			sOSVer = pszOpenStudioVerStr;
		else
			sOSVer = "???";

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
				sErrMsg.sprintf( "Error encountered opening hourly CSV results file:  %s", pszHourlyResultsPathFile );
			}
			else
			{	fprintf( fp_CSV, "18,4,\"Row/Col hourly results data begin\"\n"   );
				fprintf( fp_CSV, "\"Hourly Results of CEC Compliance Manager\"\n" );
				fprintf( fp_CSV, ",Software:,,\"%s\"\n",   sUIVer.toLocal8Bit().constData()     );
				fprintf( fp_CSV, ",CompMgr:,,\"%s\"\n",    sCmpMgrVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",OpenStudio:,,\"%s\"\n", sOSVer.toLocal8Bit().constData()     );
				fprintf( fp_CSV, ",EnergyPlus:,,\"%s\"\n", sEPlusVer.toLocal8Bit().constData()  );
				fprintf( fp_CSV, ",%s:,,\"%s\"\n",         qsCSEName.toLocal8Bit().constData(), sCSEVer.toLocal8Bit().constData() );
				fprintf( fp_CSV, ",Ruleset:,,\"%s\"\n",    sRuleVer.toLocal8Bit().constData()   );

				fprintf( fp_CSV,     "Run Title:,,,\"%s\"\n", sRunTitle.toLocal8Bit().constData()  );
				fprintf( fp_CSV, "Run Date/Time:,,,\"%s\"\n", timeStamp.toLocal8Bit().constData()  );
				fprintf( fp_CSV,    "Cond. Area:,,,%.0f\n",   fCondFloorArea   );
				fprintf( fp_CSV,         "Model:,,,\"%s\"\n", pszModelName     );
		//		fprintf( fp_CSV,  "Fuel TDV Set:,,,\"%s\"\n", sFuelTDVLabel    );
				fprintf( fp_CSV,    "Model File:,,,\"%s\"\n", pszModelPathFile );
				fprintf( fp_CSV, "\n" );

	// ASSUMES:  NUM_T24_NRES_EndUses = 15  -AND-  IDX_T24_NRES_EU_CompTot = 7  -AND-  IDX_T24_NRES_EU_Total = 14
		int iEUO[2][NUM_T24_NRES_EndUses] = { { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 7, 14       },		// SAC 2/1/17 - updated to include Process Motors
														  { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11,         7, 14, 0, 0 } };	// SAC 7/20/18 - divided into two sets - Elec vs. Other (in adding PV & Batt)
		int iNumEUs = NUM_T24_NRES_EndUses;
		if (iCodeType == CT_S901G || iCodeType == CT_ECBC)		// SAC 10/7/14   // SAC 7/15/18 - further revs to ignoree PV & Batt
		{	iNumEUs = NUM_T24_NRES_EndUses-3;
			iEUO[0][iNumEUs-1] = IDX_T24_NRES_EU_Total;		iEUO[0][iNumEUs] = 0;		// bypass reporting of CompTotal enduse
			iEUO[1][iNumEUs-1] = IDX_T24_NRES_EU_Total;		iEUO[1][iNumEUs] = 0;		// bypass reporting of CompTotal enduse
		}

				if (iCodeType == CT_T24N)		// SAC 10/7/14
				{	fprintf( fp_CSV,  ",,,Site Electric Use,,,,,,,,,,,,,,,Site Natural Gas Use,,,,,,,,,,,,,Site Propane Use,,,,,,,,,,,,,TDV Multipliers,\n" );		// SAC 10/28/15 - 'Other Fuel' -> 'Propane'
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

				double* daMtrEUData[NUM_T24_NRES_Fuels][NUM_T24_NRES_EndUses];
				double  daMtrCTotData[NUM_T24_NRES_Fuels][8760], daMtrTotData[NUM_T24_NRES_Fuels][8760];
				int iMtr=0, iEU;
				for (; iMtr < NUM_T24_NRES_Fuels; iMtr++)
				{	//	for (iYrHr=0; iYrHr<8760; iYrHr++)
					//		daMtrTotals[iMtr][iYrHr] = 0.0;
					int iEUOM = (iMtr==0 ? 0 : 1);
					int iEUCmpTot=-1, iEUTot=-1;	// SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
					{	if (BEMPX_GetHourlyResultArrayPtr( &daMtrEUData[iMtr][iEU], NULL, 0, pszModelName, pszaEPlusFuelNames[iMtr],
	 																esEUMap_CECNonRes[iEUO[iEUOM][iEU]].sEnduseName, iBEMProcIdx ) == 0 && daMtrEUData[iMtr][iEU] != NULL)
						{	// OK - do nothing
						}
						else
						{	if (iEUO[iEUOM][iEU] == IDX_T24_NRES_EU_CompTot)		// SAC 2/1/17 - used to sum CompTot & Tot results, as they are NOT represented in the meter results retrieved above
							{	iEUCmpTot = iEU;
								daMtrEUData[iMtr][iEU] = &daMtrCTotData[iMtr][0];
								for (iYrHr=0; iYrHr<8760; iYrHr++)
									daMtrCTotData[iMtr][iYrHr] = 0.0;
							}
							else if (iEUO[iEUOM][iEU] == IDX_T24_NRES_EU_Total)
							{	iEUTot = iEU;
								daMtrEUData[iMtr][iEU] = &daMtrTotData[iMtr][0];
								for (iYrHr=0; iYrHr<8760; iYrHr++)
									daMtrTotData[iMtr][iYrHr] = 0.0;
							}
							else
								daMtrEUData[iMtr][iEU] = &daZero[0];   // this combination of meter & enduse does not have results, so assign 8760 of zeroes
					}	}

					// sum indiviudal enduse results into the CompTot & Tot enduses - SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
						if (iEU != iEUCmpTot && iEU != iEUTot)
						{	for (iYrHr=0; iYrHr<8760; iYrHr++)
								daMtrEUData[iMtr][iEUTot][iYrHr] += daMtrEUData[iMtr][iEU][iYrHr];
							if (esEUMap_CECNonRes[iEUO[iEUOM][iEU]].iSumIntoCompliance)
							{	for (iYrHr=0; iYrHr<8760; iYrHr++)
									daMtrEUData[iMtr][iEUCmpTot][iYrHr] += daMtrEUData[iMtr][iEU][iYrHr];
						}	}
				}

				double dFUMlt = 100.0;		// SAC 10/28/15 - therms -> kBtu
				double dFTMlt =  10.0;		// SAC 10/28/15 - kTDV/therm -> kTDV/MBtu
				if (iCodeType == CT_T24N)		// SAC 10/7/14
				{	//	int iFuelTDVCol = (lNatGasAvailable > 0 ? 2 : 3);
					double daTDVMults[3][8760];
					double* daTDVData[3] = { &daTDVMults[0][0], &daTDVMults[1][0], &daTDVMults[2][0] };
		//	int iTableCol = ((lCliZnNum-1) * 3) + iFl + 2;
		//	dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
					if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, "TDVbyCZandFuel", ((lCliZnNum-1) * 3) + 2    , NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[0] = &daZero[0];
					}
					if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, "TDVbyCZandFuel", ((lCliZnNum-1) * 3) + 2 + 1, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[1] = &daZero[0];
					}
					if (BEMPX_GetTableColumn( &daTDVMults[2][0], 8760, "TDVbyCZandFuel", ((lCliZnNum-1) * 3) + 2 + 2, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[2] = &daZero[0];
					}

				// EXPORT hourly results records
					iYrHr = -1;
					int iMo, iDa, iHr;
					for (iMo=1; iMo<13; iMo++)
						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
							for (iHr=1; iHr<25; iHr++)
							{	iYrHr++;
				            fprintf( fp_CSV,  "%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,"
																	"%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,\n",		iMo, iDa, iHr,
						daMtrEUData[0][ 0][iYrHr], daMtrEUData[0][ 1][iYrHr], daMtrEUData[0][ 2][iYrHr], daMtrEUData[0][ 3][iYrHr], daMtrEUData[0][ 4][iYrHr], daMtrEUData[0][ 5][iYrHr],
						daMtrEUData[0][ 6][iYrHr], daMtrEUData[0][ 7][iYrHr], daMtrEUData[0][ 8][iYrHr], daMtrEUData[0][ 9][iYrHr], daMtrEUData[0][10][iYrHr], daMtrEUData[0][11][iYrHr], daMtrEUData[0][12][iYrHr], daMtrEUData[0][13][iYrHr], daMtrEUData[0][14][iYrHr],		// SAC 7/15/18 - added PV & Battery
						daMtrEUData[1][ 0][iYrHr]*dFUMlt, daMtrEUData[1][ 1][iYrHr]*dFUMlt, daMtrEUData[1][ 2][iYrHr]*dFUMlt, daMtrEUData[1][ 3][iYrHr]*dFUMlt, daMtrEUData[1][ 4][iYrHr]*dFUMlt, daMtrEUData[1][ 5][iYrHr]*dFUMlt,
						daMtrEUData[1][ 6][iYrHr]*dFUMlt, daMtrEUData[1][ 7][iYrHr]*dFUMlt, daMtrEUData[1][ 8][iYrHr]*dFUMlt, daMtrEUData[1][ 9][iYrHr]*dFUMlt, daMtrEUData[1][10][iYrHr]*dFUMlt, daMtrEUData[1][11][iYrHr]*dFUMlt, daMtrEUData[1][12][iYrHr]*dFUMlt,
						daMtrEUData[2][ 0][iYrHr]*dFUMlt, daMtrEUData[2][ 1][iYrHr]*dFUMlt, daMtrEUData[2][ 2][iYrHr]*dFUMlt, daMtrEUData[2][ 3][iYrHr]*dFUMlt, daMtrEUData[2][ 4][iYrHr]*dFUMlt, daMtrEUData[2][ 5][iYrHr]*dFUMlt,
						daMtrEUData[2][ 6][iYrHr]*dFUMlt, daMtrEUData[2][ 7][iYrHr]*dFUMlt, daMtrEUData[2][ 8][iYrHr]*dFUMlt, daMtrEUData[2][ 9][iYrHr]*dFUMlt, daMtrEUData[2][10][iYrHr]*dFUMlt, daMtrEUData[2][11][iYrHr]*dFUMlt, daMtrEUData[2][12][iYrHr]*dFUMlt,
						daTDVData[0][iYrHr], daTDVData[1][iYrHr]*dFTMlt, daTDVData[2][iYrHr]*dFTMlt );
							}
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
			}
		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... ) {
			iRetVal = 4;
			sErrMsg.sprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
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
	else if (NUM_T24_NRES_EndUses != 15 || IDX_T24_NRES_EU_Total != 14)	// SAC 2/1/17 - added error check to prevent bomb below  // SAC 7/15/18 - updated expected total to 15 (for PV & Batt)
	{	iRetVal = 5;
		sErrMsg = QString("Unexpected enduse count (%1) or total index (%2) (expecting 15 and 14 respectively)").arg(QString::number(NUM_T24_NRES_EndUses), QString::number(IDX_T24_NRES_EU_Total));
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
		sOverwriteMsg.sprintf(	"The ZERO Code hourly CSV results file '%s' is opened in another application.  This file must be closed in that "
										"application before an updated file can be written.\n\nSelect 'Retry' to proceed "
										"(once the file is closed), or \n'Abort' to abort the hourly export.", pszHourlyResultsPathFile );
		if (!OKToWriteOrDeleteFile( pszHourlyResultsPathFile, sOverwriteMsg, bSilent ))
		{	iRetVal = 2;
			sErrMsg.sprintf( "Unable to open and/or write ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
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
				sErrMsg.sprintf( "Error encountered opening ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
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

				double* daMtrEUData[ 2/*NUM_T24_NRES_Fuels*/][NUM_T24_NRES_EndUses];
				double  daMtrTotData[2/*NUM_T24_NRES_Fuels*/][8760];  // excluding PV & Battery
				int iEUOM=0, iEU;
				int iNumEUs = NUM_T24_NRES_EndUses;
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

#define  IDX_T24_NRES_EU_PV  (IDX_T24_NRES_EU_Total-2)   // assumes PV & Battery come right before TOTAL enduse
#define  IDX_T24_NRES_EU_BT  (IDX_T24_NRES_EU_Total-1)

					// sum indiviudal enduse results into the CompTot & Tot enduses - SAC 2/1/17
					for (iEU=0; iEU < iNumEUs; iEU++)
						if (iEU != IDX_T24_NRES_EU_CompTot && iEU != IDX_T24_NRES_EU_Total &&
							 iEU != IDX_T24_NRES_EU_PV && iEU != IDX_T24_NRES_EU_BT)		// SAC 9/6/18 - prevents summing of PV & Battery into Total
						{	for (iYrHr=0; iYrHr<8760; iYrHr++)
								daMtrEUData[iEUOM][IDX_T24_NRES_EU_Total][iYrHr] += daMtrEUData[iEUOM][iEU][iYrHr];
						}
				}

					double daTDVMults[2][8760];
					double* daTDVData[2] = { &daTDVMults[0][0], &daTDVMults[1][0] };
		//	int iTableCol = ((lCliZnNum-1) * 3) + iFl + 2;
		//	dTDVSum = BEMPX_ApplyHourlyMultipliersFromTable( (bBEMHrlyResPtrOK ? pdBEMHrlyRes : dHrlyRes), "TDVbyCZandFuel", iTableCol, (bVerbose != FALSE) );
					if (BEMPX_GetTableColumn( &daTDVMults[0][0], 8760, "TDVbyCZandFuel", ((lCliZnNum-1) * 3) + 2           , NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
					{	assert( FALSE );
						daTDVData[0] = &daZero[0];
					}
					if (BEMPX_GetTableColumn( &daTDVMults[1][0], 8760, "TDVbyCZandFuel", ((lCliZnNum-1) * 3) + 2 + lGasType, NULL /*pszErrMsgBuffer*/, 0 /*iErrMsgBufferLen*/ ) != 0)
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
			sErrMsg.sprintf( "Unknown error writing ZERO Code hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
	}

	if (!sErrMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
		sprintf_s( pszErrMsgBuffer, iErrMsgBufferLen, sErrMsg.toLocal8Bit().constData() );

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

//static const char* /* 379*/ pszNonResResultsHdr1 = ",,,,Analysis:,,,,Proposed ...
//static const char* /* 683*/ pszNonResResultsHdr2 = ",,,,,,Pass /,Compliance,...
//static const char* /*1745*/ pszNonResResultsHdr3 = "Start Date & Time,Filename ...

// SAC 10/10/16 - updated T24N CSV summary results header strings to include prop & std model electric demand
// SAC 2/7/17 - added Proc Mtrs enduse (tic #2033)
// SAC 2/18/17 - added total & cond floor area + TDV results for unregulated enduses and TDV totals by fuel (for 2019.0.1 release)
// SAC 7/20/18 - added PV & Battery enduses (for A2030 & 2019.0.3 releases)
static char szT24NCSV1[]	 =	",,,,,,Analysis:,,,,Proposed Model:,,,Proposed Model,,,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,Proposed Model,,,,,,,,,,,,,"
										",,Proposed Model,,,Proposed Model,,,,,,Standard Model:,,,Standard Model,,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,Standar"
										"d Model,,,,,,,,,,,,,,,Standard Model,,,Standard Model,,,,,,Proposed Model,,,,,,,,,,,,,,,Standard Model,,,,,,,,,,,,,,,Calling,Compliance,,,,Secondary,,\n";
static char szT24NCSV2[]	 =	",,,,Conditioned Floor,Total Floor,,,Pass /,Compliance,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Energy Consumption (the"
										"rms),,,,,,,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,Time Dependent Valuation (kTDV/ft2),,,,,,,,,,,,,,,TDV by Fuel (kTDV/ft2),,,Cooling U"
										"nmet Load Hours,,,Heating Unmet Load Hours,,,Elapsed,,,Electric Energy Consumption (kWh),,,,,,,,,,,,,,,Natural Gas Energy Consumption (therms),,,,,"
										",,,,,,,,Propane Energy Consumption (MBtu),,,,,,,,,,,,,Time Dependent Valuation (kTDV/ft2),,,,,,,,,,,,,,,TDV by Fuel (kTDV/ft2),,,Cooling Unmet Load"
										" Hours,,,Heating Unmet Load Hours,,,Generation Coincident Peak Demand (kW),,,,,,,,,,,,,,,Generation Coincident Peak Demand (kW),,,,,,,,,,,,,,,Appli"
										"cation,Manager,Ruleset,OpenStudio,EnergyPlus,Simulation,,\n";
static char szT24NCSV3[]	 =	"Start Date & Time,Filename (saved to),Run Title,Weather Station,Area (SqFt),Area (SqFt),Analysis Type,Elapsed Time,Fail,Margin,Time,Rule Eval Statu"
										"s,Simulation Status,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptacle,Process,Oth"
										"er Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Receptac"
										"le,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Recep"
										"tacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Total,Re"
										"ceptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Electric,Natural Gas,Propane,Zone Max,Zone Name,Num Zones Exceed Max,Zone Max,Zone Name,Num Z"
										"ones Exceed Max,Time,Rule Eval Status,Simulation Status,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Lighting,Comp"
										" Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor"
										" Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Ind"
										"oor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,"
										"Indoor Lighting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Electric,Natural Gas,Propane,Zone Max,Zone Name,Num Zones Exceed"
										" Max,Zone Max,Zone Name,Num Zones Exceed Max,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lighting,Comp Tot"
										"al,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Spc Heating,Spc Cooling,Indoor Fans,Ht Reject,Pumps & Misc,Domestic Hot Water,Indoor Lig"
										"hting,Comp Total,Receptacle,Process,Other Ltg,Proc Mtrs,PV,Battery,TOTAL,Version,Version,Version,Version,Version,Version,Weather File Path,Project Path\n";

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
	if (iCodeType == CT_S901G || iCodeType == CT_ECBC)
	{	pszaHdrs[0] = szS901GCSV1;		pszaHdrs[1] = szS901GCSV2;		pszaHdrs[2] = szS901GCSV3;
	}
	else
	{	pszaHdrs[0] = szT24NCSV1;		pszaHdrs[1] = szT24NCSV2;		pszaHdrs[2] = szT24NCSV3;
	}

#pragma warning(disable:4996)
	if (pszHdr1 && iHdr1Len > 0)
	{	strncpy( pszHdr1, pszaHdrs[0], iHdr1Len-1 );
		if (strlen( pszHdr1 ) < strlen( pszaHdrs[0] ))
			iRetVal = 1;
	}
	if (pszHdr2 && iHdr2Len > 0)
	{	strncpy( pszHdr2, pszaHdrs[1], iHdr2Len-1 );
		if (iRetVal == 0 && strlen( pszHdr2 ) < strlen( pszaHdrs[1] ))
			iRetVal = 2;
	}
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



