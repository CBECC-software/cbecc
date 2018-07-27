// BEMProc_HourlyResults.cpp : 
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

#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProcObject.h"
#include "expTextIO.h"
#include "memLkRpt.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



void BEMPX_InitializeHourlyResults( int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc)
		pBEMProc->initRuns();
}

// SAC 5/10/13 - added for CEC-NRes
BOOL BEMPX_SetupResultRun( int iRunIdx, const char* pszRunName, const char* pszRunAbbrev, int iBEMProcIdx /*=-1*/ )
{	BOOL bRetVal = FALSE;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc && iRunIdx < BEMRun_MaxNumRuns && strlen( pszRunName ) < BEMRun_RunNameLen && strlen( pszRunAbbrev ) < BEMRun_RunAbbrevLen)
		bRetVal = pBEMProc->initRun( iRunIdx, pszRunName, pszRunAbbrev );
	return bRetVal;
}

// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
int BEMPX_ReadCSEHourlyResults( const char* pszFilename, int iRunIdx, const char* pszRunName, const char* pszRunAbbrev, int iBEMProcIdx /*=-1*/,
											const char** ppResMeters /*=NULL*/, const char** ppMetersMap /*=NULL*/, double* pdMetersMult /*=NULL*/,
											const char** ppResEnduses /*=NULL*/, const char** ppEnduseMap /*=NULL*/, bool bInitResults /*=true*/ )
{	int iRetVal = -1;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
				//	// debugging
				//	QString sLogMsg = QString( "Call to BEMPX_ReadCSEHourlyResults() / run: %1, runID: %2, runAbrv: %3, file: %4, BEMProcIdx: %5" ).arg(
				//												QString::number(iRunIdx), pszRunName, pszRunAbbrev, pszFilename, QString::number(iBEMProcIdx) );
				//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	if (!pBEMProc)
		iRetVal = -2;
	else if (iRunIdx < 0 || iRunIdx >= BEMRun_MaxNumRuns)
		iRetVal = -3;
	else if (strlen( pszRunName ) >= BEMRun_RunNameLen)
		iRetVal = -4;
	else if (strlen( pszRunAbbrev ) >= BEMRun_RunAbbrevLen)
		iRetVal = -5;
	else
	{			//	BEMPX_WriteLogFile( "calling pBEMProc->readCSEHourlyResults()...", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		iRetVal = pBEMProc->readCSEHourlyResults( iRunIdx, pszRunName, pszRunAbbrev, pszFilename, ppResMeters,
																ppMetersMap, pdMetersMult, ppResEnduses, ppEnduseMap, bInitResults );
		if (iRetVal < 0)
			iRetVal -= 10;  // to differentiate errors here from errors within pBEMProc->readCSEHourlyResults() - SAC 7/23/18
				//	// debugging
				//	QString sLogMsg = QString( "pBEMProc->readCSEHourlyResults() returned %1" ).arg( QString::number(iRetVal) );
				//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}
	return iRetVal;
}


BEMRunHourlyResultMeter* GetHourlyResultMeter( const char* pszRunName, const char* pszMeterName, int iBEMProcIdx, BOOL bAddMeterIfNoExist )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
   BEMRun* pRun = NULL;
	if (pBEMProc && pszRunName && pszMeterName && strlen( pszRunName ) > 0 && strlen( pszMeterName ) > 0)
	{	pRun = pBEMProc->getRun( pszRunName );
		if (pRun == NULL && iBEMProcIdx < 0)
		{	// try prior models in case the run ID can be found there - SAC 10/5/17
			iBEMProcIdx = eActiveBEMProcIdx;
			while (pRun == NULL && --iBEMProcIdx >= 0)
			{  pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
				if (pBEMProc)
					pRun = pBEMProc->getRun( pszRunName );
		}	}
		if (pRun == NULL)
		{	assert( FALSE );  // run not found
		}
		else
		{	BEMRunHourlyResultMeter* pMeter = pRun->getHourlyResultMeter( pszMeterName );
			if (pMeter == NULL && bAddMeterIfNoExist)
			{	// SAC 5/14/13 - added logic to add meter if run present but meter isn't
				if (pRun->getNumMeters() < BEMRun_NumMeters && pszMeterName && strlen( pszMeterName ) < BEMRun_MeterNameLen)
					return pRun->setNextMeterName( pszMeterName );
			}

			if (pMeter == NULL)
			{	//assert( FALSE );  // meter not found   - avoid excessive asserts...
			}
			else
				return pMeter;
		}
	}
	else
	{	assert( FALSE );  // BEMProc, run and/or meter NULL or empty
	}
	return NULL;
}

BEMRunHourlyResultEnduse* GetHourlyResultEnduse( BEMRunHourlyResultMeter* pMeter, const char* pszEnduse )
{	if (pMeter && pszEnduse && strlen( pszEnduse ) > 0)
	{	BEMRunHourlyResultEnduse* pEnduse = pMeter->getHourlyResultEnduse( pszEnduse );
		if (pEnduse == NULL)
		{	//assert( FALSE );  // enduse not found  - sometimes used to confirm that an enduse doesn't already exist
		}
		else
			return pEnduse;
	}
	return NULL;
}

// return value:	-99999 => result not found
//						<else> => result value
double BEMPX_GetHourlyResultSum( char* pszErrMsgBuffer, int iErrMsgBufferLen, const char* pszRunName, const char* pszMeterName,
											const char* pszEnduse1,           const char* pszEnduse2 /*=NULL*/, const char* pszEnduse3 /*=NULL*/,
											const char* pszEnduse4 /*=NULL*/, const char* pszEnduse5 /*=NULL*/, const char* pszEnduse6 /*=NULL*/,
											const char* pszEnduse7 /*=NULL*/, const char* pszEnduse8 /*=NULL*/, int iBEMProcIdx /*=-1*/ )
{	double dRetVal = -99999.0;
	QString sErrorMsg;
	BEMRunHourlyResultMeter*  pMeter  = GetHourlyResultMeter(  pszRunName, pszMeterName, iBEMProcIdx, FALSE /*bAddMeterIfNoExist*/ );
	if (pMeter)
	{	const char* pszaEU[8] = { pszEnduse1, pszEnduse2, pszEnduse3, pszEnduse4, pszEnduse5, pszEnduse6, pszEnduse7, pszEnduse8 };
		for (int i=0; (i<8 && sErrorMsg.isEmpty()); i++)
			if (pszaEU[i] != NULL && strlen( pszaEU[i] ) > 0)
			{	BEMRunHourlyResultEnduse* pEnduse = GetHourlyResultEnduse( pMeter, pszaEU[i] );
				if (pEnduse == NULL)
				{	// assert( FALSE );  // enduse not found   -- can be OK in some cases where we expect to have missing enduses
					sErrorMsg = QString( "BEMPX_GetHourlyResultSum() Error:  Enduse '%1' (#%2) not found for meter '%3' & run '%4'." ).arg( pszaEU[i], QString::number( i+1 ), pszMeterName, pszRunName );
					dRetVal = -99999.0;
				}
				else
				{	if (dRetVal == -99999.0)
						dRetVal = 0.0;
					dRetVal += pEnduse->getTotal();
				}
			}
		if (sErrorMsg.isEmpty() && dRetVal == -99999.0)
			sErrorMsg = QString( "BEMPX_GetHourlyResultSum() Error:  No valid enduse names provided for meter '%1' & run '%2'." ).arg( pszMeterName, pszRunName );
	}
	else
		sErrorMsg = QString( "BEMPX_GetHourlyResultSum() Error:  Results for meter '%1' not found for run '%2'." ).arg( pszMeterName, pszRunName );

	if (!sErrorMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
	{
#pragma warning(disable : 4996)		// SAC 9/9/16
		strncpy( pszErrMsgBuffer, sErrorMsg.toLocal8Bit().constData(), iErrMsgBufferLen-1 );
		pszErrMsgBuffer[iErrMsgBufferLen-1] = '\0';
#pragma warning(default : 4996)
	}
	return dRetVal;
}

// return value:	-99999 => result not found
//						<else> => result array SUM
double BEMPX_GetHourlyResultArray( char* pszErrMsgBuffer, int iErrMsgBufferLen, double* pDbl, const char* pszRunName,
											  const char* pszMeterName,         const char* pszEnduse1,           const char* pszEnduse2 /*=NULL*/,
											  const char* pszEnduse3 /*=NULL*/, const char* pszEnduse4 /*=NULL*/, const char* pszEnduse5 /*=NULL*/,
											  const char* pszEnduse6 /*=NULL*/, const char* pszEnduse7 /*=NULL*/, const char* pszEnduse8 /*=NULL*/, int iBEMProcIdx /*=-1*/ )
{	double dRetVal = -99999.0;
	BEMRunHourlyResultMeter*  pMeter  = GetHourlyResultMeter(  pszRunName, pszMeterName, iBEMProcIdx, FALSE /*bAddMeterIfNoExist*/ );
	QString sErrorMsg;
	if (pMeter)
	{	const char* pszaEU[8] = { pszEnduse1, pszEnduse2, pszEnduse3, pszEnduse4, pszEnduse5, pszEnduse6, pszEnduse7, pszEnduse8 };
		BOOL bFirstEU = TRUE;
		int iHr=0;
		for (int i=0; (i<8 && sErrorMsg.isEmpty()); i++)
			if (pszaEU[i] != NULL && strlen( pszaEU[i] ) > 0)
			{	BEMRunHourlyResultEnduse* pEnduse = GetHourlyResultEnduse( pMeter, pszaEU[i] );
				if (pEnduse == NULL)
				{	assert( FALSE );  // enduse not found
					sErrorMsg = QString( "BEMPX_GetHourlyResultArray() Error:  Enduse '%1' (#%2) not found for meter '%3' & run '%4'." ).arg( pszaEU[i], QString::number( i+1 ), pszMeterName, pszRunName );
					dRetVal = -99999.0;
				}
				else
				{	if (bFirstEU)
					{	bFirstEU = FALSE;
						dRetVal  = pEnduse->getTotal();
						for (iHr=0; iHr<8760; iHr++)
							pDbl[iHr]  = pEnduse->getHourly(iHr);
					}
					else
					{	dRetVal += pEnduse->getTotal();
						for (iHr=0; iHr<8760; iHr++)
							pDbl[iHr] += pEnduse->getHourly(iHr);
					}
				}
			}
		if (sErrorMsg.isEmpty() && bFirstEU)
			sErrorMsg = QString( "BEMPX_GetHourlyResultArray() Error:  No valid enduse names provided for meter '%1' & run '%2'." ).arg( pszMeterName, pszRunName );
	}
	else
		sErrorMsg = QString( "BEMPX_GetHourlyResultArray() Error:  Results for meter '%1' not found for run '%2'." ).arg( pszMeterName, pszRunName );

	if (!sErrorMsg.isEmpty())
	{
#pragma warning(disable : 4996)		// SAC 9/9/16
		strncpy( pszErrMsgBuffer, sErrorMsg.toLocal8Bit().constData(), iErrMsgBufferLen-1 );
		pszErrMsgBuffer[iErrMsgBufferLen-1] = '\0';
#pragma warning(default : 4996)
	}
	return dRetVal;
}

int BEMPX_GetHourlyResultArrayPtr( double** ppDbl, char* pszErrMsgBuffer, int iErrMsgBufferLen, const char* pszRunName,
	 										  const char* pszMeterName, const char* pszEnduse, int iBEMProcIdx /*=-1*/ )
{	int iRetVal = 0;
	QString sErrorMsg;
	*ppDbl = NULL;
	if (pszRunName == NULL || strlen( pszRunName ) < 1)
	{	iRetVal = 1;
		if (pszErrMsgBuffer && iErrMsgBufferLen > 0)
			sErrorMsg = "BEMPX_GetHourlyResultArrayPtr() Error:  No run name specified for retrieval.";
	}
	else if (pszMeterName == NULL || strlen( pszMeterName ) < 1)
	{	iRetVal = 2;
		if (pszErrMsgBuffer && iErrMsgBufferLen > 0)
			sErrorMsg = "BEMPX_GetHourlyResultArrayPtr() Error:  No meter name specified for retrieval.";
	}
	else if (pszEnduse == NULL || strlen( pszEnduse ) < 1)
	{	iRetVal = 3;
		if (pszErrMsgBuffer && iErrMsgBufferLen > 0)
			sErrorMsg = "BEMPX_GetHourlyResultArrayPtr() Error:  No enduse name specified for retrieval.";
	}
	else
	{	BEMRunHourlyResultMeter*  pMeter  = GetHourlyResultMeter(  pszRunName, pszMeterName, iBEMProcIdx, FALSE /*bAddMeterIfNoExist*/ );
		if (pMeter)
		{	BEMRunHourlyResultEnduse* pEnduse = GetHourlyResultEnduse( pMeter, pszEnduse );
			if (pEnduse == NULL)
			{	iRetVal = 4;
				if (pszErrMsgBuffer && iErrMsgBufferLen > 0)
					sErrorMsg = QString( "BEMPX_GetHourlyResultArrayPtr() Error:  Enduse '%1' not found for meter '%2' & run '%3'." ).arg( pszEnduse, pszMeterName, pszRunName );
			}
			else
				*ppDbl = pEnduse->getHourlyArray();
		}
		else
		{	iRetVal = 5;
			if (pszErrMsgBuffer && iErrMsgBufferLen > 0)
				sErrorMsg = QString( "BEMPX_GetHourlyResultArrayPtr() Error:  Results for meter '%1' not found for run '%2'." ).arg( pszMeterName, pszRunName );
		}
	}
	if (!sErrorMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
	{
#pragma warning(disable : 4996)		// SAC 9/9/16
		strncpy( pszErrMsgBuffer, sErrorMsg.toLocal8Bit().constData(), iErrMsgBufferLen-1 );
		pszErrMsgBuffer[iErrMsgBufferLen-1] = '\0';
#pragma warning(default : 4996)
	}
	return iRetVal;
}

double BEMPX_AddHourlyResultArray(	double* pDbl, const char* pszRunName, const char* pszMeterName, const char* pszEnduse,
												int iBEMProcIdx /*=-1*/, BOOL bAddIfNotExist /*=FALSE*/ )
{	double dRetVal = -99999.0;
	BEMRunHourlyResultMeter* pMeter = GetHourlyResultMeter( pszRunName, pszMeterName, iBEMProcIdx, bAddIfNotExist );
	if (pMeter && pMeter->getNumEnduses()+1 < BEMRun_NumEnduses && strlen( pszEnduse ) < BEMRun_EnduseNameLen)
	{	BEMRunHourlyResultEnduse* pEnduse = GetHourlyResultEnduse( pMeter, pszEnduse );
		if (pEnduse == NULL && pMeter->getNumEnduses() < BEMRun_NumEnduses)
		{	// enduse by this name does not yet exist... which is what we want
			pEnduse = pMeter->addHourlyResultEnduse( pszEnduse );
		}
		if (pEnduse)
		{	if (pDbl)
			{	for (int iHr=0; iHr<8760; iHr++)
					pEnduse->addIntoHourly( iHr, pDbl[iHr] );
			}
			else  // SAC 8/5/13 - added code to allow calling of routine w/ no data to be initialized
				pEnduse->initValues();
			dRetVal = pEnduse->getTotal();
		}
	}
#ifdef _DEBUG
	else if (pMeter)
	{	QString qsErr;
		if (pMeter->getNumEnduses()+1 >= BEMRun_NumEnduses)
			qsErr = "Error:  BEMRun_NumEnduses too small";
		else if (strlen( pszEnduse ) >= BEMRun_EnduseNameLen)
			qsErr = QString( "Error:  enduse name '%1' too long (cannot exceed %2 chars)" ).arg( pszEnduse, QString::number(BEMRun_EnduseNameLen) );
		qsErr += QString( " calling BEMPX_AddHourlyResultArray( <fltarray>, %1, %2, %3, %4, %5 )" ).arg(
							pszRunName, pszMeterName, pszEnduse, QString::number(iBEMProcIdx), (bAddIfNotExist ? "true" : "false") );
		BEMMessageBox( qsErr );
	}
#endif
	return dRetVal;
}

double BEMPX_SumIntoHourlyResultArray( double* pDbl, const char* pszRunName, const char* pszMeterName, const char* pszEnduse, int iBEMProcIdx /*=-1*/, BOOL bAddIfNotExist /*=FALSE*/ )
{	double dRetVal = -99999.0;
	BEMRunHourlyResultMeter* pMeter = GetHourlyResultMeter( pszRunName, pszMeterName, iBEMProcIdx, bAddIfNotExist );
	if (pMeter && pMeter->getNumEnduses()+1 < BEMRun_NumEnduses && strlen( pszEnduse ) < BEMRun_EnduseNameLen)
	{	BEMRunHourlyResultEnduse* pEnduse = GetHourlyResultEnduse( pMeter, pszEnduse );
		if (pEnduse == NULL && pMeter->getNumEnduses() < BEMRun_NumEnduses)
		{	// enduse by this name does not yet exist... which is what we want
			pEnduse = pMeter->addHourlyResultEnduse( pszEnduse );
		}
		if (pEnduse)
		{	// summing into an EXISTING enduse, meaning enduse must already exist
			//pEnduse->m_dTotal = 0.0;
			dRetVal = -pEnduse->getTotal();
			for (int iHr=0; iHr<8760; iHr++)
				pEnduse->addIntoHourly( iHr, pDbl[iHr] );
			dRetVal += pEnduse->getTotal();
		}
	}
	return dRetVal;
}

/////////////////////////////////////////////////////////////////////////////

int BEMPX_WriteHourlyResultsSummary( const char* pszHourlyResultsPathFile, bool /*bSilent*/, int iBEMProcIdx )
{
	int iRetVal = 0;
	FILE *fp_Summary;
	int iErrorCode;
	try
	{
		iErrorCode = fopen_s( &fp_Summary, pszHourlyResultsPathFile, "wb" );
		if (iErrorCode != 0 || fp_Summary == NULL)
			iRetVal = -1;
		else
		{	
			BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
			if (pBEMProc)
			{	int iRun=0;
				for (; (iRetVal >= 0 && iRun < pBEMProc->getNumRuns()); iRun++)
				{	BEMRun* pRun = pBEMProc->getRun( iRun );							assert( pRun );
					if (pRun == NULL)
						iRetVal = -2;
					else
					{	fprintf( fp_Summary, "BEMProc:%3d   Run: '%s' / '%s'   NumMeters:%3d\n", iBEMProcIdx, pRun->getName(), pRun->getAbbrev(), pRun->getNumMeters() );
						iRetVal++;
						int iMtr=0;
						for (; (iRetVal >= 0 && iMtr < pRun->getNumMeters()); iMtr++)
						{	BEMRunHourlyResultMeter* pMtr = pRun->getHourlyResultMeter( iMtr );		assert( pMtr );
							if (pMtr == NULL)
								iRetVal = -3;
							else
							{	fprintf( fp_Summary, "    Meter: '%s'   NumMeters:%3d\n", pMtr->getName(), pMtr->getNumEnduses() );
								iRetVal++;
								int iEU=0;
								for (; (iRetVal >= 0 && iEU < pMtr->getNumEnduses()); iEU++)
								{	BEMRunHourlyResultEnduse* pEU = pMtr->getEnduse( iEU );				assert( pEU );
									if (pEU == NULL)
										iRetVal = -4;
									else
									{	fprintf( fp_Summary, "        Enduse: '%s'   Total: %.0f\n", pEU->getName(), pEU->getTotal() );
										iRetVal++;
									}
								}
							}
						}
					}
				}

				fflush( fp_Summary );
				fclose( fp_Summary );
			}
		}
	}
//	catch(CException e) {
//		BEMMessageBox( "Unexpected error loading symbolic file list." );
//	}
	catch( ... ) {
		BEMMessageBox( "Unknown error writing hourly CSV results file." );
	}

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

