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
#include <iostream>
#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProcCompile.h"
#include "BEMProcObject.h"
#include "BEMProc_FileIO.h"
#include "expTextIO.h"
#include "expCrypFile.h"
#include "expRuleList.h"
#include "expRuleFile.h"
#include "expLibraryIO.h"
#include "memLkRpt.h"

/////////////////////////////////////////////////////////////////////////////

static char szBEMRulPrcVersion[]      = "BEMRulPrc-3.00";
// SAC 4/2/01  - Struct Version 2 -> 3:  Add TagAllDataAsUserDefined flag at end of RULELIST definitions
// SAC 5/26/03 - Struct Version 3 -> 4:  Added rulelist line number & filename to CRuleList class to enable reporting in compiler output
// SAC 9/18/05 - Struct Version 4 -> 5:  Added m_bPerformSetBEMDataResets to CRuleList class to facilitate no-reset data setting
// SAC 6/21/12 - Struct Version 5 -> 6:  Major rule source file and class structure mods to facilitate "data model" organized rulesets
// SAC 9/24/13 - Struct Version 6 -> 7:  additions to store new data present in CRuleSetTransformation
// SAC 3/18/14 - Struct Version 7 -> 8:  addition of simulation DBID 
// SAC 3/19/14 - Struct Version 8 -> 9:  CRuleSetTransformation mods - exclude class id to full DBID and addition of alternate (grouped) tansform labels
// SAC 3/27/14 - Struct Version 9 -> 10:  CRuleSetTransformation mods - added long and short Group names
// SAC 5/11/14 - Struct Version 10 -> 11:  CRuleToolTip mods - added ToolTip messages based on HELP and/or DESCRIPTION fields of RULEs
// SAC 8/6/14  - Struct Version 11 -> 12:  CRulesetProperty mod - added Units field
// SAC 8/15/14 - Struct Version 12 -> 13:  added CRuleSet::m_sBEMBaseFile to facilitate dynamic ruleset (& data model) switching
// SAC 9/9/14  - Struct Version 13 -> 14:  added CRuleSet::m_saLabels to facilitate ruleset source shared by multiple standards/versions
// SAC 2/5/15  - Struct Version 14 -> 15:  added CRuleSet::m_rulePropTypeModList - data used to update BEMBase PropertyType objects
// SAC 8/12/15 - Struct Version 15 -> 16:  added new m_saPreviousNames member of CRuleSet::m_rulePropTypeModList - used to update BEMBase PropertyType
// SAC 8/20/15 - Struct Version 16 -> 17:  switched CRuleSetTransformation long/short group names from single strings to arrays
// SAC 8/5/16  - Struct Version 17 -> 18:  no structural change, just migration to open source dependent executables
// SAC 12/29/16- Struct Version 18 -> 19:  addition of flag near beginning of file documenting whether ruleset was compiled by a "secure" version of code
static int  siCurBEMRulPrcFileStructVersion = 19;  // this is what always gets written to newly created ruleset bin files

/////////////////////////////////////////////////////////////////////////////

// BEM object which contains dynamic arrays of all Classes and PropertyTypes
BEMProcObject eBEMProc;
// SAC 3/13/13 - added multiple model support
int eNumBEMProcsLoaded = 0;
int eActiveBEMProcIdx  = 0;
BEMProcObject* epBEMProcs[];

BEMProcObject* getBEMProcPointer( int iBEMProcIdx )
{	// SAC 3/13/13 - added multiple model support
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	assert( iBEMProcIdx <= eNumBEMProcsLoaded );
   return (iBEMProcIdx == 0 ? &eBEMProc : (iBEMProcIdx <= eNumBEMProcsLoaded ? epBEMProcs[iBEMProcIdx-1] : NULL));
}

int getBEMProcIndex( BEMProcObject* pBEMProcObj )
{	int iRetVal = -1;
	if (pBEMProcObj == &eBEMProc)
		iRetVal = 0;
	else
	{	for (int i=1; (iRetVal < 0 && i <= eNumBEMProcsLoaded); i++)
			if (pBEMProcObj == epBEMProcs[i-1])
				iRetVal = i;
	}
	return iRetVal;
}

void blastSpecificBEMProcs( int iFirst, int iNum )		// SAC 3/13/13 - added multiple model support
{	assert( iFirst > 0 );
	assert( eNumBEMProcsLoaded >= (iFirst+iNum) );
	assert(  BEMPROC_MAXMODELS >= (iFirst+iNum-1) );
	if (iFirst > 0 && eNumBEMProcsLoaded >= (iFirst+iNum) && BEMPROC_MAXMODELS >= (iFirst+iNum-1))
	{	for (int i=iFirst+iNum-2; i>iFirst; i--)
			if (epBEMProcs[i])
			{	delete epBEMProcs[i];
				epBEMProcs[i] = NULL;
			}
		//eNumBEMProcsLoaded = std::max( eNumBEMProcsLoaded, 1 );
	}
}

void blastSecondaryBEMProcs()		// SAC 3/13/13 - added multiple model support
{
	for (int i=0; i<BEMPROC_MAXMODELS; i++)
		if (epBEMProcs[i])
		{	delete epBEMProcs[i];
			epBEMProcs[i] = NULL;
		}
	eNumBEMProcsLoaded = std::max( eNumBEMProcsLoaded, 1 );
}

bool eShuttingDown = false;
bool eDeletingAllObjects = false;


/////////////////////////////////////////////////////////////////////////////
//	BEMRunHourlyResultEnduse

BEMRunHourlyResultEnduse::BEMRunHourlyResultEnduse()
{
	init();
}

void BEMRunHourlyResultEnduse::init()
{
   m_enduseName[0] = '\0';
	initValues();
}

bool BEMRunHourlyResultEnduse::nameEqual( const char* pszChk )
{	return (/*strcmp*/boost::iequals( m_enduseName, pszChk ) /*== 0*/);
}


/////////////////////////////////////////////////////////////////////////////
//	BEMRunHourlyResultMeter

BEMRunHourlyResultMeter::BEMRunHourlyResultMeter()
{
	m_numEnduses = 0;
	init();
}

void BEMRunHourlyResultMeter::init()
{
	for (int iEU=0; iEU < m_numEnduses; iEU++)
		m_enduses[iEU].init();
	m_meterName[0] = '\0';
	m_numEnduses = 0;
}

bool BEMRunHourlyResultMeter::nameEqual( const char* pszChk )
{	return (/*strcmp*/boost::iequals( m_meterName, pszChk ) /*== 0*/);
}

BEMRunHourlyResultEnduse* BEMRunHourlyResultMeter::getHourlyResultEnduse( const char* pszEnduseName )
{	if (pszEnduseName && strlen( pszEnduseName ) > 0)
	{	int iEU=0;
		for (; iEU < m_numEnduses; iEU++)
//		{	if (strcmp( m_enduses[iEU].m_enduseName, pszEnduseName ) == 0)
		{	if (m_enduses[iEU].nameEqual( pszEnduseName ))
				return &m_enduses[iEU];
		}
	}
	return NULL;
}

int BEMRunHourlyResultMeter::getHourlyResultEnduseIndex( const char* pszEnduseName )
{	if (pszEnduseName && strlen( pszEnduseName ) > 0)
	{	int iEU=0;
		for (; iEU < m_numEnduses; iEU++)
//		{	if (strcmp( m_enduses[iEU].m_enduseName, pszEnduseName ) == 0)
		{	if (m_enduses[iEU].nameEqual( pszEnduseName ))
				return iEU;
		}
	}
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//	BEMRun

BEMRun::BEMRun()
{
	m_numMeters = 0;
	init();
}

void BEMRun::init( const char* pszName /*=NULL*/, const char* pszAbbrev /*=NULL*/ )
{
	for (int iMtr=0; iMtr < m_numMeters; iMtr++)
		m_hourlyResults[iMtr].init();
	if (pszName && strlen(pszName) > 0)
		strncpy_s( m_runName, BEMRun_RunNameLen, pszName, _TRUNCATE );
	else
		m_runName[0] = '\0';
	if (pszAbbrev && strlen(pszAbbrev) > 0)
		strncpy_s( m_runAbbrev, BEMRun_RunAbbrevLen, pszAbbrev, _TRUNCATE );
	else
		m_runAbbrev[0] = '\0';
	m_numMeters = 0;
}

bool BEMRun::nameEqual( const char* pszChk )
{	return (/*strcmp*/boost::iequals( m_runName, pszChk ) /*== 0*/);
}

bool BEMRun::abbrevEqual( const char* pszChk )
{	return (/*strcmp*/boost::iequals( m_runAbbrev, pszChk ) /*== 0*/);
}

BEMRunHourlyResultMeter* BEMRun::getHourlyResultMeter( const char* pszMeterName )
{	if (pszMeterName && strlen( pszMeterName ) > 0)
	{	int iMtr=0;
		for (; iMtr < m_numMeters; iMtr++)
//		{	if (strcmp( m_hourlyResults[iMtr].m_meterName, pszMeterName ) == 0)
		{	if (m_hourlyResults[iMtr].nameEqual( pszMeterName ))
				return &m_hourlyResults[iMtr];
		}
	}
	return NULL;
}

int BEMRun::getHourlyResultMeterIndex( const char* pszMeterName )
{	if (pszMeterName && strlen( pszMeterName ) > 0)
	{	int iMtr=0;
		for (; iMtr < m_numMeters; iMtr++)
//		{	if (strcmp( m_aHourlyResults[iMtr].m_sMeterName, pszMeterName ) == 0)
		{	if (m_hourlyResults[iMtr].nameEqual( pszMeterName ))
				return iMtr;
		}
	}
	return -1;
}

// ----------------------------------------------------------------

QString GetMappedString( const char** ppResEnduses, const char** ppEnduseMap, QString& sEnduse, int* pIdx )
{	QString sRetVal;
	int idx = -1;
	while (ppResEnduses[++idx] != NULL && sRetVal.isEmpty())
	{	if (sEnduse.compare( ppResEnduses[idx] )==0)
		{	sRetVal = ppEnduseMap[idx];
			if (pIdx)
				*pIdx = idx;
		}
	}
	return sRetVal;
}

// ----------------------------------------------------------------
// ReadCSEHourlyResults()
//		return values:		> 0 : number of meters for which hourly results were read
//								  0 : 
//								 -2 : too many enduses found in results file
//								 -3 : enduse name too long
//								 -4 : incorrect number of fields encountered while reading meter hourly results
//								 -5 : meter name too long
//								 -6 : error opening CSE hourly results file
//								 -7 : error parsing CSE hourly results file
//								 -8 : CSE hourly results file not found
//								 -9 : too many meters found in results file
//								-10 : 
// ----------------------------------------------------------------
int BEMRun::readCSEHourlyResults( const char* pszFilename, const char** ppResMeters /*=NULL*/, const char** ppMetersMap /*=NULL*/,
											double* pdMetersMult /*=NULL*/, const char** ppResEnduses /*=NULL*/, const char** ppEnduseMap /*=NULL*/ )
{	int iRetVal = (FileExists( pszFilename ) ? 0 : -8);
	if (iRetVal == 0)
	{	QStringList saCSVFields, saColTitles;
   	try
   	{  // open file
   	   BEMTextIO file( pszFilename, BEMTextIO::load );
   	
//sLogMsg.Format( "   RetrieveCSEResults():  Parsing CSE results file:  '%s'", saResultFiles[i] );
//BEMPX_WriteLogFile( sLogMsg );

			int iFld, iaResFieldIdx[ BEMRun_NumEnduses ];
   	   try
   	   {
//   	      TRY
//   	      {	
					int iMode=0, iNumFields=0, iNumEUs=0, iThisMtrIdx=-1, iHour=0;
					BOOL bEOFReached = FALSE;		double data, dMult=1.0;
					QString sMeterName;
					do
					{	if (iMode < 2)
							iNumFields = file.ParseCSVRecord( saColTitles );
						else
							iNumFields = file.ParseCSVRecord( saCSVFields );
						if (iNumFields == -1)
							bEOFReached = TRUE;
						else
						{	switch (iMode)
							{	case  0 :	// searching for next report header
												if (iNumFields >= 2 && saColTitles[0].indexOf("Energy Use")>=0 && saColTitles[1].indexOf("Hour")>=0)
													iMode = 1;  // found header, next record should be report column titles
												break;
								case  1 :	// just found report header, very next record should be report column titles
												if (iNumFields >= 6 && saColTitles[0].indexOf("Meter")>=0 && saColTitles[1].indexOf("Mon")>=0 && saColTitles[2].indexOf("Day")>=0)
													iMode = 2;  // this record contains column titles

//   char		m_sEnduseName[ BEMRun_EnduseNameLen ];
//	double	m_dTotal;
//	double	m_daHourly[ BEMRun_NumHourlyResults ];
//
//   char		m_sMeterName[ BEMRun_MeterNameLen ];
//	CBEMRunHourlyResultEnduse  m_aEnduses[ BEMRun_NumEnduses ];

												else
												{	assert( FALSE );  // recod following Energy Use / Year header should always be report column title record!!
												}	break;
								case  2 :	// in process of reading results records
												if (iHour == 0)	// store meter name which is the first field on each hourly record the FIRST time through the records
												{	for (iFld=0; iFld < BEMRun_NumEnduses; iFld++)	// initialize field map to be straight through (no mapping) - SAC 5/31/16
														iaResFieldIdx[iFld] = (ppResMeters==NULL || ppMetersMap==NULL) ? iFld : -1;
													QString sMtr;			int iMtrMapIdx = -1;		iThisMtrIdx = -1;		dMult = 1.0;
													if (saCSVFields[0].length() >= BEMRun_MeterNameLen)
													{	assert( FALSE );
														iRetVal = -5;
													}
													else if (ppResMeters==NULL || ppMetersMap==NULL)
														sMtr = saCSVFields[0];
													else
													{	sMtr = GetMappedString( ppResMeters, ppMetersMap, saCSVFields[0], &iMtrMapIdx );
														if (!sMtr.isEmpty())  // ignore this entire meter if not in mapped list
														{	iThisMtrIdx = getHourlyResultMeterIndex( sMtr.toLocal8Bit().constData() );
															if (iThisMtrIdx >= 0)  // this meter already defined, so use it
																sMtr.clear();
															if (pdMetersMult && iMtrMapIdx >= 0)
																dMult = pdMetersMult[iMtrMapIdx];
													}	}
													if (!sMtr.isEmpty())
													{	iThisMtrIdx = m_numMeters++;
														if (iThisMtrIdx >= BEMRun_NumMeters)
														{	assert( FALSE );
															iRetVal = -9;
														}
														else
														{	assert( sMtr.length() < BEMRun_MeterNameLen );
															setMeterName( iThisMtrIdx, sMtr.toLocal8Bit().constData() );
													}	}
//																strcpy_s( m_hourlyResults[ iMeterIdx ].m_sMeterName, BEMRun_MeterNameLen, saCSVFields[0] );

													if (iRetVal >= 0)
													{	iNumEUs = iNumFields-5;
									//					if (sMtr.isEmpty()) // Meter NOT added => no need to RE-initialize enduse list
									//					{	if (iNumFields >= (m_hourlyResults[ iThisMtrIdx ].getNumEnduses() + 5))		// was: != - switched to enable ignoring certain enduses
									//						{	//assert( FALSE );
									//							//iRetVal = -4;
			//		//2018-07-23 23:48:45 - BEMRun::readCSEHourlyResults() returning -4:  iNumFields = 30 / iThisMtrIdx = 0 / m_hourlyResults[ iThisMtrIdx ].getNumEnduses() = 13
			//		// debugging
			//		QString sLogMsg = QString( "BEMRun::readCSEHourlyResults() previously would have returned -4:  iNumFields = %1 / iThisMtrIdx = %2 / m_hourlyResults[ iThisMtrIdx ].getNumEnduses() = %3" ).arg(
			//														QString::number(iNumFields), QString::number(iThisMtrIdx), QString::number(m_hourlyResults[ iThisMtrIdx ].getNumEnduses()) );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

									//					}	}
									//					else if (!sMtr.isEmpty()) // new Meter added

														bool bResFieldsValid = false;		// SAC 7/24/18
														for (iFld=0; (!bResFieldsValid && iFld < BEMRun_NumEnduses); iFld++)	
															bResFieldsValid = (iaResFieldIdx[iFld] >= 0);

														if (!sMtr.isEmpty() || !bResFieldsValid) // new Meter added -OR- ResFields needing initialization
														{	
															for (iFld=0; (iRetVal>=0 && iFld < iNumEUs); iFld++)
															{	if (saColTitles[iFld+5].length() >= BEMRun_EnduseNameLen)
																{	assert( FALSE );
																	iRetVal = -3;
																}
																else
																{	QString sEU = (ppResEnduses && ppEnduseMap) ? GetMappedString( ppResEnduses, ppEnduseMap, saColTitles[iFld+5], NULL ) : saColTitles[iFld+5];
																	if (sEU.isEmpty())
																		iaResFieldIdx[iFld] = -1;
																	else
																	{	int iEUFldIdx = m_hourlyResults[ iThisMtrIdx ].getHourlyResultEnduseIndex( sEU.toLocal8Bit().constData() );
																		if (iEUFldIdx >= 0)
			//	{
																			iaResFieldIdx[iFld] = iEUFldIdx;
			//		// debugging
			//		QString sLogMsg = QString( "      iEUFldIdx = %1" ).arg( QString::number(iEUFldIdx) );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			//	}
																		else if (m_hourlyResults[ iThisMtrIdx ].getNumEnduses() >= (BEMRun_NumEnduses-1))
																		{	assert( FALSE );
																			iRetVal = -2;
																		}
																		else
																		{	assert( sEU.length() < BEMRun_EnduseNameLen );
																			iaResFieldIdx[iFld] = m_hourlyResults[ iThisMtrIdx ].getNumEnduses();
																			m_hourlyResults[ iThisMtrIdx ].addHourlyResultEnduse( sEU.toLocal8Bit().constData() );  // saColTitles[iFld+5] );
			//		// debugging
			//		QString sLogMsg = QString( "      iaResFieldIdx[iFld] = %1  /  addHourlyResultEnduse( %2 )" ).arg( QString::number(iaResFieldIdx[iFld]), sEU );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
																}	}	}
															}
														}
													}
			//		// debugging
			//		QString sLogMsg = QString( "      iThisMtrIdx = %1  /  dMult = %2  /  sMtr = %3" ).arg(
			//										QString::number(iThisMtrIdx), QString::number(dMult), sMtr );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												}

												if (iThisMtrIdx >= 0)
												{	for (iFld=0; iFld < iNumEUs /*m_hourlyResults[ iMeterIdx ].getNumEnduses()*/; iFld++)
													{
			//	if (iHour == 0) {
			//		// debugging
			//		QString sLogMsg = QString( "          iFld %1  /  iaResFieldIdx[iFld] %2  /  m_hourlyResults[ iThisMtrIdx ].getNumEnduses() %3" ).arg(
			//												QString::number(iFld), QString::number(iaResFieldIdx[iFld]), QString::number(m_hourlyResults[ iThisMtrIdx ].getNumEnduses()) );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			//	}
														if (iaResFieldIdx[iFld] >= 0 && iaResFieldIdx[iFld] < m_hourlyResults[ iThisMtrIdx ].getNumEnduses())
														{	data = atof( saCSVFields[iFld+5].toLocal8Bit().constData() ) * dMult;
															m_hourlyResults[ iThisMtrIdx ].getEnduse( iaResFieldIdx[iFld] )->addIntoHourly( iHour, data );
			//	if (iHour < 12) {
			//		// debugging
			//		QString sLogMsg = QString( "             hr %1 = %2" ).arg( QString::number(iHour), QString::number(data) );
			//		BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			//	}
												}	}	}
												iHour++;
												if (iHour == 8760)
												{	iHour = 0;		// FINISHED parsing this set of hourly results, so reset hour count and mode and search for subsequent set of hourly results...
													iMode = 0;
													iRetVal++;
												}
												break;
							}
						}
					} while (!bEOFReached && iRetVal >= 0);  // continue until EOF which results in 
   	   }
//   	   CATCH( BEMTextIOException, err )
//   	   {  // ERROR occurred
////   	      sLogMsg.Format( "Error parsing CSE results\r\nFrom File: %s\r\n\r\n\t%s\r\n\r\n", saResultFiles[i], err->m_strError );
//   	      //errorFile.Write( msg.GetBuffer( msg.length() ), msg.length() );
//   	      //msg.ReleaseBuffer();
////BEMPX_WriteLogFile( sLogMsg );
//				iRetVal = -7;
//   	
////   	      BEMMessageBox( sLogMsg, NULL, 2 /*warning*/ );
//   	      THROW_LAST();
//   	   }
//   	   END_CATCH
			catch (std::exception& e)
			{
				QString msg = QString( "Error reading CSE hourly results CSV.\nFrom File: %1\n\t - cause: %2\n" ).arg( pszFilename, e.what() );
				std::cout << msg.toLocal8Bit().constData();
	   //      BEMMessageBox( msg, "", 2 /*warning*/ );
	         iRetVal = -7;
			}
		 	catch (...)
		  	{
				QString msg = QString( "Error reading CSE hourly results CSV.\nFrom File: %1\n" ).arg( pszFilename );
				std::cout << msg.toLocal8Bit().constData();
	   //      BEMMessageBox( msg, "", 2 /*warning*/ );
	         iRetVal = -7;
		  	}
   	
   	   file.Close();  // SAC 6/1/06
   	}
//   	CATCH( CFileException, error )
//   	{
////   	   sLogMsg.Format( "Error opening file: %s", saResultFiles[i] );
//   	   //errorFile.Write( msg.GetBuffer( msg.length() ), msg.length() );
//   	   //msg.ReleaseBuffer();
////BEMPX_WriteLogFile( sLogMsg );
//			iRetVal = -6;
//
////   	   BEMMessageBox( sLogMsg, NULL, 2 /*warning*/ );
//   	}
//   	END_CATCH
		catch (std::exception& e)
		{
			QString msg = QString( "Error opening CSE hourly results CSV file: %1\n\t - cause: %2\n" ).arg( pszFilename, e.what() );
			std::cout << msg.toLocal8Bit().constData();
  	//      BEMMessageBox( msg, "", 2 /*warning*/ );
  	      iRetVal = -6;
		}
	 	catch (...)
	  	{
			QString msg = QString( "Error opening CSE hourly results CSV file: %1\n" ).arg( pszFilename );
			std::cout << msg.toLocal8Bit().constData();
  	//      BEMMessageBox( msg, "", 2 /*warning*/ );
  	      iRetVal = -6;
	  	}
	}  // end of if file exists...
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// BEMProcObject
/////////////////////////////////////////////////////////////////////////////

BEMProcObject::BEMProcObject()
{
   clear();
   m_uiActive = true;	// SAC 9/26/16 - do this outside clear() so that it is retained during/following data model resets
}

BEMProcObject::~BEMProcObject()
{
   clear();
}

void BEMProcObject::clear()
{
	m_classes.resize(0);

//	m_propTypes.resize(0);
// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
	clearPropTypes();

   //m_numClassesAlloc = 0;
   //m_numClasses = 0;
   //m_numPropTypes = 0;

	for (int iRun=0; iRun < m_numRuns; iRun++)  // SAC 5/15/12
		m_runs[ iRun ].init();
	m_numRuns = 0;

	m_srcBEMProcObj = NULL;		// SAC 4/30/15
}

// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
void BEMProcObject::clearPropTypes()
{
	for (int i = (int) m_propTypes.size()-1; i >= 0; i--)	
	{	if (m_propTypes.at(i))
			delete m_propTypes.at(i);
	}
	m_propTypes.resize(0);
	m_numPropTypes = 0;
}

BOOL BEMProcObject::copy( BEMProcObject* pCopyFrom, BOOL bCopyObjects /*=TRUE*/ )
{
	BOOL bRetVal = (pCopyFrom != NULL);									assert( bRetVal );
	if (bRetVal)
	{	int i=0;
		m_type          = pCopyFrom->m_type;        
		m_binFileName   = pCopyFrom->m_binFileName; 
		m_srcBEMProcObj = pCopyFrom;		// SAC 4/30/15

		//m_numClassesAlloc    = 0;
		//m_numClasses         = 0;
		//if (pCopyFrom->m_numClassesAlloc > 0)
		if (pCopyFrom->m_classes.size() > 0)
   	{	try
   		{
   			m_classes = pCopyFrom->m_classes;	// std::vector should handle all the details
   			if (m_classes.size() != pCopyFrom->m_classes.size())
					{	assert( FALSE );
						bRetVal = FALSE;
					}
   		   //m_numClassesAlloc	= pCopyFrom->m_numClassesAlloc;
				//m_numClasses		= pCopyFrom->m_numClasses;
   		}
   		catch (std::exception& e)
   		{
				std::cout << "Warning: BEMProcObject::Copy failed to create Classes because " << e.what() << '\n';
				bRetVal = FALSE;
			}
   		catch (...)
   		{
				std::cout << "Warning: BEMProcObject::Copy failed to create Classes\n";
				bRetVal = FALSE;
   		}
			if (!bRetVal && m_classes.size() > 0)
				m_classes.resize(0);
			else if (bRetVal)
			{	if (!bCopyObjects)
				{	// clear out arrays of object pointers and each class' m_currentParent
					for (int iCls=0; iCls < (int) m_classes.size(); iCls++)
					{
						m_classes[iCls].RemoveObjects( BEMO_User   , false /*bDeleteObjects*/ );
						m_classes[iCls].RemoveObjects( BEMO_RuleLib, false /*bDeleteObjects*/ );
						m_classes[iCls].RemoveObjects( BEMO_UserLib, false /*bDeleteObjects*/ );
						m_classes[iCls].setCurrentParent( NULL );
					}
				}
				else
				{
					assert( !bCopyObjects );	// code not present (and not currently needed) to copy objects themselves, only arrays of object pointers copied above
				}
			}
		}

		//m_numPropTypes = 0;
		//if (bRetVal && pCopyFrom->m_numPropTypes > 0)
		if (bRetVal && pCopyFrom->m_propTypes.size() > 0)
		{
			try
			{
   	//		m_propTypes = pCopyFrom->m_propTypes;	// std::vector should handle all the details
   	//		if (m_propTypes.size() != pCopyFrom->m_propTypes.size())
		//			{	assert( FALSE );
		//				bRetVal = FALSE;
		//			}
		//		//if (bRetVal)
		//		//	m_numPropTypes = pCopyFrom->m_numPropTypes;
		// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
				m_numPropTypes = pCopyFrom->m_numPropTypes;			assert( pCopyFrom->m_numPropTypes <= (int) pCopyFrom->m_propTypes.size() );
				BEMPropertyType* pPT = NULL;
				m_propTypes.resize( pCopyFrom->m_propTypes.size(), pPT );	// fill array w/ NULL ptrs
				for (int i=0; i<m_numPropTypes; i++)
				{
					pPT = new BEMPropertyType();							assert( pPT );
					if (pPT)
					{
						if (pPT->Copy( pCopyFrom->m_propTypes[i] ))
							m_propTypes[i] = pPT;
						else
						{	assert( false );	// BEMPropertyType::Copy() failed
						}
				}	}
			}
   		catch (std::exception& e)
   		{
				std::cout << "Warning: BEMProcObject::Copy failed to create Property Types because " << e.what() << '\n';
				bRetVal = FALSE;
			}
			catch (...)
			{
				std::cout << "Warning: BEMProcObject::copy failed to create Property Types\n";
				bRetVal = FALSE;
			}
			if (!bRetVal && m_propTypes.size() > 0)
				m_propTypes.resize(0);
		}

      if (bRetVal)
		{
//			m_dwaSymbolsNotToOverwrite.Copy( pCopyFrom->m_dwaSymbolsNotToOverwrite );
			m_currentRuleFile			= pCopyFrom->m_currentRuleFile      ;
			m_currentRuleFileStatus	= pCopyFrom->m_currentRuleFileStatus;

		 // don't copy BEMRun data...
		 	m_numRuns = 0;
			//	BEMRun m_runs[ BEMRun_MaxNumRuns ];
		}
	}
	return bRetVal;
}


BOOL BEMProcObject::init( int iNumClasses, int iNumPropTypes )
{				assert( iNumClasses > 0 );
				assert( iNumPropTypes > 0 );
   clear();
   BOOL bRetVal = TRUE;
   try
   {
		m_classes.resize( iNumClasses );
      //m_numClassesAlloc = iNumClasses;
   }
	catch (std::exception& e)
	{
		std::cout << "Warning: BEMProcObject::Init failed to create Classes because " << e.what() << '\n';
		bRetVal = FALSE;
	}
   catch (...)
   {
   	std::cout << "Warning: BEMProcObject::Init failed to create Classes\n";
      bRetVal = FALSE;
   }
	if (!bRetVal && m_classes.size() > 0)
		m_classes.resize(0);
   else if (bRetVal)
		bRetVal = initPropertyTypes( iNumPropTypes );

   return bRetVal;
}


BOOL BEMProcObject::initPropertyTypes( int iNumPropTypes )
{
   BOOL bRetVal = TRUE;

		try
	   {
			// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
			clearPropTypes();
			m_numPropTypes = 0;  // # valid, loaded PropTypes
			BEMPropertyType* pPT = NULL;
			m_propTypes.resize( iNumPropTypes, pPT );	// fill array w/ NULL ptrs
			for (int i=0; i<iNumPropTypes; i++)
			{
				pPT = new BEMPropertyType();				assert( pPT );
				if (pPT)
					m_propTypes[i] = pPT;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Warning: BEMProcObject::initPropertyTypes failed to create Property Types because " << e.what() << '\n';
			bRetVal = FALSE;
		}
		catch (...)
		{
   		std::cout << "Warning: BEMProcObject::initPropertyTypes failed to create Property Types\n";
	      bRetVal = FALSE;
   	}
		if (!bRetVal && m_propTypes.size() > 0)
			clearPropTypes();

   return bRetVal;
}

BEMPropertyType* BEMProcObject::getPropertyType( int i0PT, bool bCreateIfNext /*=false*/ )
{	BEMPropertyType* pPT=NULL;
	if (i0PT >= 0 && i0PT < (int) m_propTypes.size() && (i0PT < m_numPropTypes || bCreateIfNext))
	{	pPT = m_propTypes[i0PT];
		if (pPT == NULL && bCreateIfNext)
		{	try
			{	pPT = new BEMPropertyType();				assert( pPT );
				if (pPT)
					m_propTypes[i0PT] = pPT;
			}
			catch (std::exception& e)
			{	std::cout << "Warning: BEMProcObject::getPropertyType failed to create new Property Type because " << e.what() << '\n';
			}
			catch (...)
			{	std::cout << "Warning: BEMProcObject::getPropertyType failed to create new Property Type\n";
	   	}
		}
		if (i0PT >= m_numPropTypes)
			m_numPropTypes = i0PT+1;
	}
	else if (bCreateIfNext && i0PT == m_numPropTypes && i0PT >= 0 && i0PT <= (int) m_propTypes.size())
	{	try
		{
			pPT = new BEMPropertyType();				assert( pPT );
			if (pPT)
			{	if (i0PT < (int) m_propTypes.size())
					m_propTypes[i0PT] = pPT;
				else
					m_propTypes.push_back( pPT );
				m_numPropTypes++;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Warning: BEMProcObject::getPropertyType failed to create Property Type because " << e.what() << '\n';
		}
		catch (...)
		{
   		std::cout << "Warning: BEMProcObject::getPropertyType failed to create Property Type\n";
   	}
	}
	else
	{	assert( false );   // failed this criteria:  i0PT >= 0 && i0PT < (int) m_propTypes.size() && i0PT < m_numPropTypes
	}
	return pPT;
}

BEMRun* BEMProcObject::getRun( const char* pszRunName )
{	if (pszRunName && strlen( pszRunName ) > 0)
	{	int iRun=0;
		for (; iRun < m_numRuns; iRun++)  // first check argument vs. long run names
		{	if (m_runs[iRun].nameEqual( pszRunName ))
				return &m_runs[iRun];
		}
		for (iRun=0; iRun < m_numRuns; iRun++)  // then charg arg vs. run abbreviations
		{	if (m_runs[iRun].abbrevEqual( pszRunName ))
				return &m_runs[iRun];
		}
	}
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Extern Function:  LoadDefaultIDs()
//
// Purpose ------------------------------------------------------------------
//   To set several static integer values which store the component type and
//   database IDs for certain database parameters which require hard-coded
//   defaulting.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   TRUE if all IDs set successfully, else FALSE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////

// Default Class IDs
int eDefClassProj   = -1;

// Default Project
long eDefDBIDProjRuleset    = -1;
long eDefDBIDProjRuleFile   = -1;
long eDefDBIDProjCreateDate = -1;
long eDefDBIDProjUniqueAssignFlag = -1;
long eDefDBIDProjRemoveDupsFlag   = -1;

bool eDefaultIDsSet = FALSE;
bool eReportedDefaultIDsSetError = FALSE;

bool LoadDefaultIDs()
{
   if (eBEMProc.getType() == BEMT_CBECC)
   {
      // First load Class IDs
      eDefClassProj    = (int) BEMPX_GetDBComponentID( "Proj" );
		if (eDefClassProj <= 0)
			eDefClassProj = (int) BEMPX_GetDBComponentID( "Project" );    // try alternative spelling
      
      // Then load DBIDs
      // Project
		if (eDefClassProj > 0)
		{
      	eDefDBIDProjRuleset          = BEMPX_GetDatabaseID( "Ruleset",          eDefClassProj );
      	eDefDBIDProjRuleFile         = BEMPX_GetDatabaseID( "RuleFile",         eDefClassProj );
      	eDefDBIDProjCreateDate       = BEMPX_GetDatabaseID( "CreateDate",       eDefClassProj );
      	eDefDBIDProjUniqueAssignFlag = BEMPX_GetDatabaseID( "UniqueAssignFlag", eDefClassProj );
      	eDefDBIDProjRemoveDupsFlag   = BEMPX_GetDatabaseID( "RemoveDupsFlag", 	eDefClassProj );
		}

      eDefaultIDsSet = ( (eDefClassProj   > 0) &&
                    //      ( > 0) && 
                          (eDefDBIDProjRuleset > 0) && (eDefDBIDProjRuleFile > 0) && (eDefDBIDProjCreateDate > 0) &&
                    //      ( > 0) && 
                          TRUE );
   }
   else
      eDefaultIDsSet = TRUE;

   if (!eDefaultIDsSet && !eReportedDefaultIDsSetError)
   {
		assert( false );
//      BEMMessageBox( "Error loading default IDs.", "BEMProc Error", 3 /*error*/ );
      eReportedDefaultIDsSetError = TRUE;
   }

   return eDefaultIDsSet;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static void CA_DBIDToDBCompParamString( long lDBID, QString& sCompParam )
{
   sCompParam.clear();
   int iClass = BEMPX_GetClassID(    lDBID );
   int iProp  = BEMPX_GetPropertyID( lDBID );
   int iArray = BEMPX_GetArrayID(    lDBID );
   BEMProcObject* pBEMProc = getBEMProcPointer( -1 /*iBEMProcIdx*/ );
//   if (iClass < 1 || iClass > soaClasses.GetSize())
   if (iClass < 1 || iClass > BEMPX_GetNumClasses())
      sCompParam = QString( "DBID %1 Not Found" ).arg( QString::number(lDBID) );
   else
   {
//      CBEMAsciiClass* pClass = (CBEMAsciiClass*) soaClasses.GetAt( iClass-1 );
      int iError;
		BEMClass* pClass = BEMPX_GetClass( iClass, iError );									assert( pClass );
      if (pClass)
      {
//         sCompParam = pClass->m_sShortName;
         sCompParam = pClass->getShortName();
         sCompParam += ':';
         if (iProp > 0)
         {
//            int i0PropIdx = pClass->m_iFirstPropID + iProp - 1;
            int i0PropIdx = pClass->getFirstPropID() + iProp - 1;
//            if (i0PropIdx < 0 || i0PropIdx >= soaPropTypes.GetSize())
            if (i0PropIdx < 0 || i0PropIdx >= pBEMProc->getNumPropertyTypes())
               sCompParam += "UnknownParam";
            else
            {
//               CBEMAsciiPropType* pPT = (CBEMAsciiPropType*) soaPropTypes.GetAt( i0PropIdx );
					BEMPropertyType* pPT = pBEMProc->getPropertyType( i0PropIdx );			assert( pPT );
               if (pPT)
               {
//                  sCompParam += pPT->m_sShortName;
//                  if (pPT->m_iNumValues > 1)
                  sCompParam += pPT->getShortName();
                  if (pPT->getNumValues() > 1)
                     // append array index within square brackets
                     sCompParam += QString( "[%1]" ).arg( QString::number(iArray) );
               }
               else
                  sCompParam += "UnknownParam";
            }
         }
         else if (iProp == 0)
         {
            switch (iArray)
            {
               case BEM_PARAM0_ACTIVE  :   sCompParam += "Active";      break;  
               case BEM_PARAM0_NAME    :   sCompParam += "Name";        break;  
               case BEM_PARAM0_PARENT  :   sCompParam += "Parent";      break;  
               case BEM_PARAM0_NEWPAR  :   sCompParam += "NewParent";   break;  
               case BEM_PARAM0_NEWCOPY :   sCompParam += "NewCopy";     break;  
               case BEM_PARAM0_PARCLAS :   sCompParam += "PClass";      break;  
               case BEM_PARAM0_ACTION  :   sCompParam += "Action";      break;  
               case BEM_PARAM0_CREATE  :   sCompParam += "Create";      break;  
               case BEM_PARAM0_DELETE  :   sCompParam += "Delete";      break;  
               case BEM_PARAM0_CR8OPT  :   sCompParam += "Cr8Option";   break;  
               case BEM_PARAM0_USERLIB :   sCompParam += "UserLib";     break;  
               case BEM_PARAM0_RULELIB :   sCompParam += "RuleLib";     break;  
               default                 :   sCompParam += "UnknownParam";   break;  
            }
         }
         else
            sCompParam += "UnknownParam";
      }
      else
         sCompParam += "UnknownComp";
   }
}


static void WriteCompParamToTextFile( BEMTextIO& file, long lDBID )
{
   QString sCompParam;
   CA_DBIDToDBCompParamString( lDBID, sCompParam );
   sCompParam = "- " + sCompParam + "  ";
   file.WriteToken( sCompParam.toLocal8Bit().constData(), sCompParam.length() );
}

/////////////////////////////////////////////////////////////////////////////
//   CASym
//    An instance of this class is created for each symbol definition
//    contained in the selected compliance ruleset.

class CASym
{
public:
   CASym( long iVal=0, const char* str=NULL )	{	m_iValue = iVal;
   																if (str)
   																	m_sString = str;	}
   ~CASym()		{ }

   long    m_iValue;    // numeric value of this symbol
   QString m_sString;   // symbol string to be displayed in drop-down listboxes for selection by user

public:
   void Read(  CryptoFile& file );
   void Write( CryptoFile& file );
   void WriteText( BEMTextIO& file );
};

void CASym::Read( CryptoFile& file )
{
   file.Read( &m_iValue, sizeof( long ) );
   file.ReadQString( m_sString );
//   int length = 0;
//   file.Read( &length, sizeof( int ) );
//   file.Read( m_sString.GetBuffer( length ), length );
//   m_sString.ReleaseBuffer();
}

void CASym::Write( CryptoFile& file )
{
   file.Write( &m_iValue, sizeof( long ) );
   file.WriteQString( m_sString );
//   int length = m_sString.length();
//   file.Write( &length, sizeof( int ) );
//   file.Write( (const char*)m_sString, length );
}

void CASym::WriteText( BEMTextIO& file )
{
   file << m_iValue;
   file << m_sString.toLocal8Bit().constData();
   file.NewLine();
}

/////////////////////////////////////////////////////////////////////////////
//   CASymDepLst
//    An instance of this class is created for each dependency list of
//    symbol definitions contained in the selected compliance ruleset.

class CASymDepLst
{
public:
   CASymDepLst( long iDefault=0 )	{	m_iDefaultValue = iDefault;
													m_iNumDepDBIDs = 0;
													for (int i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
													{	m_lDBID[    i] = 0;
														m_fDepValue[i] = 0;
													}		}
   ~CASymDepLst();

   long     m_iDefaultValue;                               // numeric value of the default symbol
   int      m_iNumDepDBIDs;                                // the number of dependencies (0-2)
   long     m_lDBID[     MAX_DEP_DBIDS_PER_SYMBOL_LIST ];  // lDBID of dependencies
   double   m_fDepValue[ MAX_DEP_DBIDS_PER_SYMBOL_LIST ];  // floating point values for dependency check(s)
   std::vector<CASym*>  m_olSymbols;      // vector of CASymDepLst

public:
   void Read(  CryptoFile& file );
   void Write( CryptoFile& file );
   void WriteText( BEMTextIO& file );
};

CASymDepLst::~CASymDepLst()
{
	for (int i = (int) m_olSymbols.size()-1; i >= 0; i--)
   {	CASym* pSym = m_olSymbols.at( i );								assert( pSym );
		delete pSym;
	}
	m_olSymbols.clear();
}

void CASymDepLst::Read( CryptoFile& file )
{
   file.Read( &m_iDefaultValue, sizeof( long ) );
   file.Read( &m_iNumDepDBIDs, sizeof( int ) );

   int i=0;
   for (i=0; i < m_iNumDepDBIDs; i++)
   {
      file.Read( &m_lDBID[    i], sizeof( long ) );
      file.Read( &m_fDepValue[i], sizeof( double ) );
   }

   int iCount;
   file.Read( &iCount, sizeof( int ) );
   for (i=0; i < iCount; i++)
   {
      CASym* symbol = new CASym;
      symbol->Read( file );
      m_olSymbols.push_back( symbol );
   }
}

void CASymDepLst::Write( CryptoFile& file )
{
   file.Write( &m_iDefaultValue, sizeof( long ) );
   file.Write( &m_iNumDepDBIDs, sizeof( int ) );

	int i;
   for (i=0; i < m_iNumDepDBIDs; i++)
   {
      file.Write( &m_lDBID[    i], sizeof( long ) );
      file.Write( &m_fDepValue[i], sizeof( double ) );
   }

   int iCount = m_olSymbols.size();
   file.Write( &iCount, sizeof( int ) );

	for (i=0; i < iCount; i++)
   {	CASym* pSym = m_olSymbols.at( i );				assert( pSym );
   	if (pSym)
   		pSym->Write( file );
   }
}

void CASymDepLst::WriteText( BEMTextIO& file )
{
   file.NewLine();
   file.WriteToken( "CASymDepLst:", 13 );
   file.NewLine();

   file << m_iDefaultValue;
   file << m_iNumDepDBIDs;
   file.NewLine();

	int i;
   for (i=0; i < m_iNumDepDBIDs; i++)
   {
      file << m_lDBID[i];
      WriteCompParamToTextFile( file, m_lDBID[i] );
      file << m_fDepValue[i];
      file.NewLine();
   }

	for (i=0; i < (int) m_olSymbols.size(); i++)
   {	CASym* pSym = m_olSymbols.at( i );				assert( pSym );
   	if (pSym)
   		pSym->WriteText( file );
   }
}

/////////////////////////////////////////////////////////////////////////////
//   CASymLst
//    An instance of this class is created for each list of symbol dependency
//    list for a single set of lDBIDs.

class CASymLst
{
public:
   CASymLst()		{ };
   ~CASymLst();

   std::vector<long>          m_aDBIDs;            // lDBID(s) which this symbol list describe
   std::vector<CASymDepLst*>  m_aSymDepLists;      // list of CASymDepLst

public:
   void Read(  CryptoFile& file );
   void Write( CryptoFile& file );
   void WriteText( BEMTextIO& file );
};

CASymLst::~CASymLst()
{
	for (int i = (int) m_aSymDepLists.size()-1; i >= 0; i--)
   {	CASymDepLst* pSymDepLst = m_aSymDepLists.at( i );				assert( pSymDepLst );
		delete pSymDepLst;
	}
	m_aSymDepLists.clear();
}

void CASymLst::Read( CryptoFile& file )
{
   int iCount;
   file.Read( &iCount, sizeof( int ) );
   long lDBID;
   int i=0;
   for (i=0; i < iCount; i++)
   {
      file.Read( &lDBID, sizeof( long ) );
      m_aDBIDs.push_back( lDBID );
   }

   file.Read( &iCount, sizeof( int ) );
   for (i=0; i < iCount; i++)
   {
      CASymDepLst* symdeplst = new CASymDepLst;
      symdeplst->Read( file );
      m_aSymDepLists.push_back( symdeplst );
   }
}

void CASymLst::Write( CryptoFile& file )
{
   int i, iCount = m_aDBIDs.size();
   file.Write( &iCount, sizeof( int ) );
   for (i=0; i < iCount; i++)
      file.Write( &m_aDBIDs[i], sizeof( long ) );

   iCount = m_aSymDepLists.size();
   file.Write( &iCount, sizeof( int ) );

	for (i=0; i < (int) m_aSymDepLists.size(); i++)
   {	CASymDepLst* pSymDepLst = m_aSymDepLists.at( i );				assert( pSymDepLst );
   	if (pSymDepLst)
   		pSymDepLst->Write( file );
   }
}

void CASymLst::WriteText( BEMTextIO& file )
{
   file.NewLine();
   file.NewLine();
   file.WriteToken( "CASymLst:", 10 );
   file.NewLine();

   int i, iCount = (int) m_aDBIDs.size();
   for (i=0; i < iCount; i++)
   {
      file << (long) m_aDBIDs[i];
      WriteCompParamToTextFile( file, (long) m_aDBIDs[i] );
   }

	for (i=0; i < (int) m_aSymDepLists.size(); i++)
   {	CASymDepLst* pSymDepLst = m_aSymDepLists.at( i );				assert( pSymDepLst );
   	if (pSymDepLst)
   		pSymDepLst->WriteText( file );
   }
}

/////////////////////////////////////////////////////////////////////////////
//   CASymLstList
//    An instance of this class is created for each list of symbol
//    definitions.  For now, there is only one such list for each ruleset.

//class CASymLstList : public CObList
//{
//public: 
//   ~CASymLstList();
//   void RemoveAll();
//
//   CArray<CASymbolTable*, CASymbolTable*>  m_psaSymbolTables;
//
//   bool ReadText( QString sFileName );  //, CFile& errorFile );
//
//   bool Read( CCryptoFile& file ); 
//   bool Write( CCryptoFile& file );
//   void WriteText( QString sFileName );  // SAC 6/2/06
//
//   bool PostSymbolsToDatabase();
//
//// SAC 6/1/06 - added function to handle parsing of additional symbol definition data sstored in separate CSV files
//   bool ReadSymbolDataFromCSV( QString sMainSymbolFN, QString sCSVSymbolFN );
//};

/////////////////////////////////////////////////////////////////////////////

// 0 - OK
// 1 - No filename specified
// 2 - File doesn't exist
// 3 - Error opening file
// 4 - Secure EXE but insecure data model binary
// 5 - Insecure EXE but secure data model binary
// 6 - Inconsistent data model binary structure version (file old)
// 7 - Inconsistent data model binary structure version (file newer than executable)
int BEMPX_CheckDataModelBin( const char* pszBinFileName )	
{	int iRetVal = 0;
	QString sFileName = pszBinFileName;
   if (sFileName.length() < 1)
		//sErrMsg = "No BEMProc file name specified.";
		iRetVal = 1;
   else if (!FileExists( sFileName.toLocal8Bit().constData() ))
		//sErrMsg = QString( "BEMProc file not found:  '%1'" ).arg( sFileName );
		iRetVal = 2;
   else
   {
      CryptoFile file( sFileName.toLocal8Bit().constData() );
      if (!file.open( QIODevice::ReadOnly ))
			//sErrMsg = QString( "Error opening BEMProc file:  '%1'" ).arg( sFileName );
			iRetVal = 3;
		else
		{
			int iVer, iSecureFile = 0;
			// read the BEMProc version and number of class and proptype values
			file.ReadDirect( &iVer, sizeof( int ) );
			if (iVer > 28)
				file.ReadDirect( &iSecureFile, sizeof( int ) );

			bool bSecureEXE = BEMPX_SecureExecutable();
			if (bSecureEXE && iSecureFile == 0)
				iRetVal = 4;
			else if (!bSecureEXE && iSecureFile > 0)
				iRetVal = 5;
			else if (iVer < BEMPROC_VERSION)
				iRetVal = 6;
			else if (iVer > BEMPROC_VERSION)
				iRetVal = 7;

			file.close();
	}	}
	return iRetVal;
}

BOOL BEMProcObject::decompileBinBEMProc( const char* pszBinFileName, BOOL bOnlySymbols )
{
   BOOL bRetVal = FALSE;
   clear();
   if (pszBinFileName)
      m_binFileName = pszBinFileName;

	QString sErrMsg;
   if (m_binFileName.length() < 1)
		sErrMsg = "No BEMProc file name specified.";
   else if (!FileExists( m_binFileName.toLocal8Bit().constData() ))
		sErrMsg = QString( "BEMProc file not found:  '%1'" ).arg( m_binFileName );
   else
   {
      CryptoFile file( m_binFileName.toLocal8Bit().constData() );
      if (!file.open( QIODevice::ReadOnly ))
			sErrMsg = QString( "Error opening BEMProc file:  '%1'" ).arg( m_binFileName );
		else
		{
      int iVer, iNumClasses, iNumPropTypes, iNumSymbolTables;
      // read the BEMProc version and number of class and proptype values
      file.ReadDirect( &iVer, sizeof( int ) );

		// SAC 1/3/17 - added security setting info
		int iSecure = 0;
		if (iVer > 28)
	      file.ReadDirect( &iSecure, sizeof( int ) );

      file.Read( &iNumClasses, sizeof( int ) );
      file.Read( &iNumPropTypes, sizeof( int ) );
      file.Read( &iNumSymbolTables, sizeof( int ) );			assert( iNumSymbolTables < 1 );	// symbol tables NYI
      if (iVer != BEMPROC_VERSION)
			sErrMsg = QString( "Incompatible BEMProc version:  %1 expected vs. %2 from file" ).arg( QString::number(BEMPROC_VERSION), QString::number(iVer) );
         //BEMMessageBox( "Incompatible BEMProc version.", "CBEMProcObject::DecompileBinBEMProc() Error", 3 /*error*/ );
      else if (!bOnlySymbols && !init( iNumClasses, iNumPropTypes ))  //, iNumSymbolTables ))
			sErrMsg = "CBEMProcObject::Init() failed.";
         //BEMMessageBox( "CBEMProcObject::Init() failed.", "CBEMProcObject::DecompileBinBEMProc() Error", 3 /*error*/ );
      else
      {	QString str;	long lData;		int iData;		BOOL bData;		UINT uiData;
			if (!bOnlySymbols)
			{	resizeClasses( iNumClasses );
				initPropertyTypes( iNumPropTypes );
			}
         // Read in Class info
         BEMClass cTemp;
         BEMClass* pClass = NULL;
			int i=0;
         for (i=0; i<iNumClasses; i++)
         {
            if (bOnlySymbols)
                  pClass = &cTemp;
            else  pClass = getClass( i );

            file.ReadQString( str );		pClass->setShortName( str );
            file.ReadQString( str );		pClass->setLongName( str );
            pClass->setDefaultName( pClass->getLongName() );

            file.Read( &lData, sizeof( long ) );		pClass->setMaxDefinable( lData );
            file.Read( &iData, sizeof( int ) );			pClass->setMaxReferences( iData );
            file.Read( &iData, sizeof( int ) );			pClass->setAutoCreate( iData );

            file.Read( &iData, sizeof( int ) );			pClass->setMaxChildren( iData );
            file.Read( &iData, sizeof( int ) );			pClass->setMaxSimComps( iData );
            file.Read( &bData, sizeof( BOOL ) );		pClass->setPurgeUnrefCompsBeforeSim( bData );
            file.Read( &uiData, sizeof( UINT ) );		pClass->setHelpID( uiData );

            file.Read( &iData, sizeof( int ) );			pClass->set1BEMClassIdx( iData );
            file.Read( &iData, sizeof( int ) );			pClass->set1MirrorClassIdx( iData );
            file.Read( &iData, sizeof( int ) );			pClass->setObjectCopyFlag( iData );			// SAC 6/6/03 - Added flag value
            file.Read( &bData, sizeof( BOOL ) );		pClass->setWriteAsSingleRecord( bData );	// SAC 1/24/12 - (file ver 2) added to facilitate tighter IBD & XML file writing              
            file.Read( &bData, sizeof( BOOL ) );		pClass->setXMLIgnoreName( bData );			// SAC 1/24/12 - (file ver 2) added to prevent output of component names to XML files         
            file.ReadQString( str );						pClass->setDefaultNameTemplate( str );		// SAC 1/24/12 - (file ver 2) added to specify a template for defaulting new component names  
            file.Read( &iData, sizeof( int ) );			pClass->setFirstPropID( iData );
            file.Read( &iData, sizeof( int ) );			pClass->setNumProps( iData );
                      
				int j=0;
            for (j=0; j<BEM_MAX_PARENT_TYPES; j++)
            {	file.Read( &iData, sizeof( int ) );		pClass->setParentType( j, iData );
            }
            for (j=0; j<BEM_MAX_CHILD_TYPES; j++)
            {	file.Read( &iData, sizeof( int ) );		pClass->setChildType( j, iData );
            }

            file.Read( &iData, sizeof( int ) );			pClass->setNumChildTypes( iData );
         }
         //if (!bOnlySymbols)
         //   m_iNumClasses = iNumClasses;

         // Read in PropertyType info
         BEMPropertyType ptTemp;
         BEMPropertyType* pPropType = NULL;
         int iNumPrevProps = 0;
         int iLastClass = -1;
         for (i=0; i<iNumPropTypes; i++)
         {
            if (bOnlySymbols)
                  pPropType = &ptTemp;
            else  pPropType = getPropertyType( i, true /*bCreateIfNext*/ );

            file.ReadQString( str );					pPropType->setShortName( str );
            file.Read( &iData, sizeof( int ) );		pPropType->setPropType( iData );
            file.Read( &iData, sizeof( int ) );		pPropType->setNumValues( iData );
            file.ReadQString( str );					pPropType->setUnitsLabel( str );
            file.Read( &iData, sizeof( int ) );		pPropType->setUseForTrees( iData );

				for (int iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
   	      {  file.Read( &iData, sizeof( int  ) );		pPropType->setObj1ClassIdx( iObjCls, iData );
      	      file.Read( &lData, sizeof( long ) );		pPropType->setObjTypeDBID(  iObjCls, lData );
         	   file.Read( &lData, sizeof( long ) );		pPropType->setObjTypeValue( iObjCls, lData );
            }

            file.Read( &uiData, sizeof( UINT  ) );		pPropType->setHelpID( uiData );

            //file.ReadQString( pPropType->m_sErrorCheckRulelistName );  // SAC 5/21/01 - added new member
            file.Read( &bData, sizeof( BOOL ) );		pPropType->setXMLWriteArrayIndices( bData );		// SAC 1/24/12 - (file ver 2) added to indicate whether or not array indices are to be written to output XML files

            file.Read( &lData, sizeof( long ) );		pPropType->setWriteSimulationFlag( lData );		// SAC 5/22/12 - (file ver 3)

            file.Read( &iData, sizeof( int ) );			pPropType->setReportPrecision( iData );		// SAC 2/4/15 - (no text file I/O yet)

				long lUserSpecification=-1;
            file.Read( &lUserSpecification, sizeof( long ) );		// SAC 2/25/13 - (file ver 5)

            file.ReadQString( str );					pPropType->setDescription( str );
            file.ReadQString( str );					pPropType->setInputClassInfo( str );	// SAC 3/3/14 - (file ver 6)

			// SAC 8/6/15 - to facilitate data model backward compatibility by tracking re-named properties
				int iNumPrevNames, iPrevNameIdx;		QString sPrevName;
            file.Read( &iNumPrevNames, sizeof( int ) );
				for (iPrevNameIdx=0; iPrevNameIdx<iNumPrevNames; iPrevNameIdx++)
				{	file.ReadQString( sPrevName );
					pPropType->addPreviousName( sPrevName );
				}

            file.Read( &iData, sizeof( int ) );			pPropType->set1ClassIdx( iData );
            file.Read( &iData, sizeof( int ) );			pPropType->set1PropTypeIdx( iData );

			// code to initialize new m_iSumOfPreviousProperties member (without altering binary file format)
            if (pPropType->get1ClassIdx() != iLastClass)
            {  iNumPrevProps = 0;
               iLastClass = pPropType->get1ClassIdx();
            }
            pPropType->setSumOfPreviousProperties( iNumPrevProps );
            iNumPrevProps += pPropType->getNumValues();

				// SAC 6/14/12 - moved UP w/ other referenced object compatibility stuff
            //file.Read( &pPropType->m_i1ObjClassIdx, sizeof( int ) );
            //file.Read( &pPropType->m_lObjTypeDBID , sizeof( long  ) );

            if (!bOnlySymbols)
            {	pPropType->initPropTypeDetails();
					if (lUserSpecification >= 0)  // SAC 2/25/12
				//		for (int idx=0; idx < pPropType->getNumValues(); idx++)
				//		{	BEMPropTypeDetails* pDT = pPropType->getPropTypeDetails(idx);			assert( pDT );
				// SAC 10/12/16 - modify init to set only FIRST of array to the BEMBase-defined data type (consistent w/ old version)
						{	BEMPropTypeDetails* pDT = pPropType->getPropTypeDetails(0);			assert( pDT );
							if (pDT)
							{	switch (lUserSpecification)              //      compDataType        primary  editable  userDefault  displayInput/Prop/Budg  notInputMode      notInputMsg
								{	case BEMD_Compulsory   :  pDT->setData( (int) lUserSpecification, TRUE ,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
									case BEMD_Required     :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
									case BEMD_CondRequired :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;	// SAC 2/11/15
									case BEMD_Optional     :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
									case BEMD_Default      :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
									case BEMD_CriticalDef  :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
									case BEMD_Prescribed   :  pDT->setData( (int) lUserSpecification, FALSE,   TRUE ,    TRUE ,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;	// SAC 4/4/13 - modified to allow Prescribed data to be modified by user (for Research mode)
	   							case BEMD_NotInput     :  pDT->setData( (int) lUserSpecification, FALSE,   FALSE,    FALSE,             TRUE, TRUE, TRUE, DTNotInp_AllowUIReset, "" );  break;
								}
							}
						}
            }
         }
         //if (!bOnlySymbols)
         //   m_iNumPropTypes = iNumPropTypes;
         //
         // symbol tables NYI
         // // Read in SymbolTable info
         // BEMSymbolTable locSymTable;
         // BEMSymbolTable* pSymTable = NULL;
         // for (i=0; i<iNumSymbolTables; i++)
         // {
         //    if (bOnlySymbols)
         //          pSymTable = &locSymTable;
         //    else  pSymTable = &m_pSymbolTables[i];
         //
         //    int iNumDBIDs;
         //    file.Read( &iNumDBIDs, sizeof( int ) );
         //    for (int j=0; j<iNumDBIDs; j++)
         //    {
         //       file.Read( &pSymTable->m_laDBID[j], sizeof( long  ) );
         //       file.Read( &pSymTable->m_iaDefault[j], sizeof( int ) );
         //
         //       int iNumAlwaysSyms, iNumRecords;
         //       file.Read( &iNumAlwaysSyms, sizeof( int ) );
			// 	   int k=0;
         //       for (; k<iNumAlwaysSyms; k++)
         //       {
         //          BEMSymbol* pSym = new BEMSymbol;       ASSERT( pSym );
         //          if (pSym)
         //          {
         //             file.Read( &pSym->m_iValue, sizeof( long ) );
         //
         //             int length = 0;
         //             file.Read( &length, sizeof( int ) );
         //             file.Read( pSym->m_sString.GetBuffer( length ), length );
         //             pSym->m_sString.ReleaseBuffer( length );
         //
         //             pSymTable->m_psaEveryListSymbols[j].Add( pSym );
         //          }
         //       }
         //
         //       file.Read( &iNumRecords, sizeof( int ) );
         //       for (k=0; k<iNumRecords; k++)
         //       {
         //          BEMSymbol* pSym = new BEMSymbol;       ASSERT( pSym );
         //          if (pSym)
         //          {
         //             file.Read( &pSym->m_iValue, sizeof( long ) );
         //
         //             int length = 0;
         //             file.Read( &length, sizeof( int ) );
         //             file.Read( pSym->m_sString.GetBuffer( length ), length );
         //             pSym->m_sString.ReleaseBuffer( length );
         //
         //             pSymTable->m_psaSymbolTable[j].Add( pSym );
         //          }
         //       }
         //    }
         // }
         // if (!bOnlySymbols)
         //    m_iNumSymbolTables = iNumSymbolTables;

      //   // Now load symbol data
      //   CASymLstList symbolList;
      //   //symbolList.RemoveAll();
      //   // This call both reads in the symbol info AND posts it to the BEMProc
      //   bRetVal = symbolList.Read( file );
      	bRetVal = TRUE;
			int iNumSymLsts;
			file.Read( &iNumSymLsts, sizeof( int ) );
			if (iNumSymLsts > 0)
			{
			   std::vector<CASymLst> aSymLists;      // vector of CASymLst
			   aSymLists.resize(iNumSymLsts);
				for (i=0; i < iNumSymLsts; i++)
					aSymLists[i].Read( file );

				// following based on RuleSet::postSymbolsToDatabase()
					   // Post Symbol information to Building Database for access by user interface module
					   std::vector<long> laSymbolsNotOverwritten;
						for (int iS=0; (bRetVal && iS < (int) aSymLists.size()); iS++)	
						{	CASymLst* pSL = &aSymLists.at(iS);
					      if (pSL)
					      {
					         // Replace existing BEMProc symbol info with that contained in this SymLst
					         for (i=0; i < (int) pSL->m_aDBIDs.size(); i++)
					         {
					            void* pBEMPSL = BEMPX_OverwriteSymbolList( pSL->m_aDBIDs[i], BEMS_ProgDefault );  // SAC 9/15/16 - was: BEMS_RuleDefault );
					            if (pBEMPSL == NULL)
					               // BEMProc is preventing us from overwriting this SymbolList - probably due to simulation module
					               laSymbolsNotOverwritten.push_back( pSL->m_aDBIDs[i] );
					            else
					            {  // loop over entire list, writing each element to the file
										for (std::vector<CASymDepLst*>::iterator it = pSL->m_aSymDepLists.begin(); it != pSL->m_aSymDepLists.end(); ++it)
										{	CASymDepLst* pSDL = *it;
					                  if (pSDL)
					                  {
					                     void* pBEMPSDL = BEMPX_AddSymbolDepList( pBEMPSL, pSDL->m_iDefaultValue,
					                                                           pSDL->m_lDBID[0], pSDL->m_fDepValue[0],
					                                                           pSDL->m_lDBID[1], pSDL->m_fDepValue[1],
					                                                           pSDL->m_lDBID[2], pSDL->m_fDepValue[2] );
					                     if (pBEMPSDL)
					                     {  // loop over entire list, writing each element to the file
													for (std::vector<CASym*>::iterator it2 = pSDL->m_olSymbols.begin(); it2 != pSDL->m_olSymbols.end(); ++it2)
													{	CASym* pS = *it2;
					                           if (!pS || !BEMPX_AddSymbol( pBEMPSDL, pS->m_iValue, pS->m_sString.toLocal8Bit().constData() ))
														{	bRetVal = FALSE;		assert( FALSE );
					                        }	}
					                     }
					                     else
												{	bRetVal = FALSE;		assert( FALSE );
					                  }	}
					                  else
											{	bRetVal = FALSE;		assert( FALSE );
					               }	}
					            }
					         }
					      }
					      else
							{	bRetVal = FALSE;		assert( FALSE );
					   }	}
					   if (laSymbolsNotOverwritten.size() > 0)
					   {  // one or more SymbolLists were not overwritten, so display error message
					      QString sTemp, sMsg = "The ruleset was prevented from resetting the following symbol lists in order to preserve"
					                     		  " simulation module integrity:\n";
					      int iSize = (int) laSymbolsNotOverwritten.size();
					      for (int i=0; i<iSize; i++)
					      {  BEMPX_DBIDToDBCompParamString( laSymbolsNotOverwritten[i], sTemp );
					         sMsg += QString( "     %2\n" ).arg( sTemp );
					      }
					      sMsg += "\nConsult your compliance ruleset and/or simulation module provider for further assistance.";
					      BEMMessageBox( sMsg, "", 2 /*warning*/ );
					      bRetVal = FALSE;
					   }
			}
      }
      }
   }

	if (!sErrMsg.isEmpty())
      BEMMessageBox( sErrMsg, "CBEMProcObject::DecompileBinBEMProc() Error", 3 /*error*/ );

   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

static BOOL ReadBEMBaseText( const char* sBEMFileName );
static BOOL ReadBEMEnumsText( std::vector<CASymLst*>& aSymLists, const char* sBEMFileName );
static BOOL WriteCompiledBEMProc( const char* pszBEMBinFileName, std::vector<CASymLst*>& aSymLists );

BOOL BEMPX_CompileDataModel(	const char* sBEMFileName, const char* sEnumsFileName,
										const char* sBEMBinFileName /*=NULL*/, QString* psClassPropMsg /*=NULL*/ )
{
	if (psClassPropMsg)
		psClassPropMsg->clear();
//	CASymLstList sllSymbols;
//   if (ReadAsciiBEMProc( sBEMFileName ) && sllSymbols.ReadText( sSymFileName ))
   std::vector<CASymLst*> aSymLists;      // vector of CASymLst ptrs
	BOOL bRetVal = (ReadBEMBaseText( sBEMFileName ) && ReadBEMEnumsText( aSymLists, sEnumsFileName ));
	if (bRetVal)
	{
      int iError, iNumClasses = BEMPX_GetNumClasses();
      if (psClassPropMsg)
      	psClassPropMsg->append( QString( "%1 Classes\nNumber of properties by class:\n" ).arg( QString::number( iNumClasses ) ) );

      // Set final Class and PropType data
	   int i=0;
      // initialize each CBEMAsciiClass' parent and child indexes
      for (i=0; i < iNumClasses; i++)
      {
//         CBEMAsciiClass* pClass = (CBEMAsciiClass*) soaClasses.GetAt(i);
			BEMClass* pClass = BEMPX_GetClass( i+1, iError );
         if (pClass)
         {
            // setup parent type indexes based on parent type class strings
            pClass->SetParentChildTypesFromStrings();

				if (psClassPropMsg)
            	psClassPropMsg->append( QString( "\n   %1 - %2 - %3" ).arg( QString::number( i+1 ), 3 ).arg( QString::number( pClass->getNumProps() ), 3 ).arg( pClass->getLongName() ) );
         }
      }

      // initialize each CBEMAsciiPropType's m_i1ObjClassIdx (only if m_iPropType == BEMP_Obj && m_sObjClass != NULL) and m_lObjTypeDBID
//      iSize = soaPropTypes.GetSize();
      int iNumPropTypes = eBEMProc.getNumPropertyTypes();
      for (i=0; i < iNumPropTypes; i++)
      {
         //CBEMAsciiPropType* pPT = (CBEMAsciiPropType*) soaPropTypes.GetAt(i);
			BEMPropertyType* pPT = eBEMProc.getPropertyType( i );
         if (pPT && pPT->getPropType() == BEMP_Obj)
         {	bool bPTObjClsInfoOK = pPT->setObjClassDataFromStrings();			assert( bPTObjClsInfoOK );
         }
      }
//            // ERROR - if m_iPropType == BEMP_Obj then m_lpszObjClass must have a valid class name
//            assert( pPT->m_saObjClass[0].length() > 0 );
//				for (int iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
//				{	pPT->m_laObjTypeDBID[ iObjCls] = 0;
//					if (pPT->m_saObjClass[iObjCls].IsEmpty())
//						pPT->m_ia1ObjClassIdx[iObjCls] = 0;
//					else
//					{  //int iClassIdx = GetClassIndexByShortName( eBEMProc.m_pPropTypes[ i ].m_lpszObjClass );
//            		int iClassIdx = GetLocalClassID( pPT->m_saObjClass[iObjCls] );
//            		ASSERT( iClassIdx > 0 );   // ERROR - no short class name match found
//            		pPT->m_ia1ObjClassIdx[iObjCls] = iClassIdx;
//            		
//            		// Set m_lObjTypeDBID iff m_sObjTypeProp NOT NULL
//            		if (pPT->m_saObjTypeProp[iObjCls].length() > 0)
//            		   pPT->m_laObjTypeDBID[iObjCls] = GetLocalDatabaseID( pPT->m_saObjTypeProp[iObjCls], iClassIdx );
//				}	}

		QString strBEMBinFileName;
		if (sBEMBinFileName && strlen(sBEMBinFileName) > 0)
			strBEMBinFileName = sBEMBinFileName;
		else
		{	strBEMBinFileName = sBEMFileName;
			if (strBEMBinFileName.lastIndexOf('.') > 3)
				strBEMBinFileName = strBEMBinFileName.left( strBEMBinFileName.lastIndexOf('.') );
			strBEMBinFileName += ".bin";
		}

      // Write BEMProc CCryptoFile
      bRetVal = WriteCompiledBEMProc( strBEMBinFileName.toLocal8Bit().constData(), aSymLists );

//		if (bReportBEMStats)
//	      BEMMessageBox( sClassPropMsg, "Data Model Class Summary", 1 /*info*/ );
   }

//   // clear out all static arrays
//   ClearBEMProcArrays();

	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

BOOL ReadBEMBaseText( const char* sBEMFileName )
{
   BOOL bRetVal = TRUE;

//   // clear out BEMProc static arrays
//   ClearBEMProcArrays();
//   soaClasses.SetSize( 100, 20 );
//   soaPropTypes.SetSize( 1000, 100 );
   BEMProcObject* pBEMProc = getBEMProcPointer( -1 /*iBEMProcIdx*/ );		assert( pBEMProc );
	int iClassSize=100, iPropTypeSize=1000;
	pBEMProc->resizeClasses( iClassSize );
	pBEMProc->resizePropertyTypes( iPropTypeSize );

   try
   {  // open file
      BEMTextIO file( sBEMFileName, BEMTextIO::load );

      try
      {
         BEMClass* pClass = NULL;
         BEMPropertyType* pPT = NULL;
         int iClassIdx = 0;
         int iClassPropIdx = 0;
         int iOverallPropIdx = 0;
         int iRecHdr = (int) file.ReadLong();   // read first record header value

			// interpret a first header value > 1000 as a version number vs. as a standard record header
         int iFileVersion = 1;
         if (iRecHdr > 1000)
         {
            iFileVersion = iRecHdr - 1000;
            iRecHdr = (int) file.ReadLong();   // read next (first) record header value
         }

         while (iRecHdr >= 0)
         {
            file.PostReadToken();
            if (iRecHdr == 0)  // Class record
            {
               // incrament ClassIdx and reset ClassPropIdx
               iClassIdx++;
               iClassPropIdx = 0;

               // Create new Class
//               pClass = new BEMClass;
					if (iClassIdx >= iClassSize)
					{	iClassSize += 20;
						pBEMProc->resizeClasses( iClassSize );
					}
					pClass = pBEMProc->getClass( iClassIdx-1 );			assert( pClass );
               if (pClass)
               {	pClass->clear();
                  // read class data from text file
                  pClass->ReadText( file, iFileVersion );

                  // Set some Class data
                  pClass->set1BEMClassIdx( iClassIdx );
                  pClass->setFirstPropID( iOverallPropIdx );

//                  if (!ClassNameIsUnique( soaClasses, pClass, iClassIdx-1 ))
						QString sClassShortName = pClass->getShortName();
						int iPrevClassIdx = BEMP_GetDBComponentID(sClassShortName);
						if (iPrevClassIdx > 0 && iPrevClassIdx < iClassIdx)
                  {  // report error, but go ahead and add to array anyway so that subsequent property reading can still proceed
                     BEMMessageBox( QString( "Multiple BEMProc classes named '%1' found." ).arg( pClass->getShortName() ), "", 2 /*warning*/ );
                     bRetVal = FALSE;
                  }

//                  // add this Class to the class array
//                  soaClasses.SetAtGrow( iClassIdx-1, pClass );

                  if (!pClass->getMirrorClassName().isEmpty())  // SAC 7/28/02 - Added code to copy all BEMPropertyTypes from Mirror class
                  {
                     assert( pClass->get1MirrorClassIdx() == 0 );
//                     int iNumPrevClasses = soaClasses.GetSize()-1;
							QString sMirClsName = pClass->getMirrorClassName();
							pClass->set1MirrorClassIdx( BEMP_GetDBComponentID( sMirClsName ) );			assert( pClass->get1MirrorClassIdx() > 0 );
//                     int iNumPrevClasses = iClassIdx-1;
//                     for (int iMC=0; (pClass->get1MirrorClassIdx() == 0 && iMC<iNumPrevClasses); iMC++)
//                     {
//                        BEMClass* pClass2 = (BEMClass*) soaClasses.GetAt(iMC);
//                        assert( pClass2 );
//                        if (pClass2)
//                           pClass->set1MirrorClassIdx( (pClass->getMirrorClassName().Compare( pClass2->getShortName() ) != 0 ? 0 : iMC+1) );
//                     }
                     if (pClass->get1MirrorClassIdx() < 1)
                     {
                        BEMMessageBox( QString( "Mirror class '%1' for class '%2' not found." ).arg( pClass->getMirrorClassName(), pClass->getShortName() ), "", 2 /*warning*/ );
                        bRetVal = FALSE;
                     }
                     else
                     {  // Add mirror class' properties to this class
//                        BEMClass* pClass2 = (BEMClass*) soaClasses.GetAt( pClass->get1MirrorClassIdx()-1 );
                        BEMClass* pClass2 = pBEMProc->getClass( pClass->get1MirrorClassIdx()-1 );			assert( pClass2 );
                        int iMPFirst = pClass2->getFirstPropID();
                        int iMPLast  = pClass2->getNumProps() + iMPFirst - 1;
//                        assert( iMPLast < soaPropTypes.GetSize() );
                        for (int iMP = iMPFirst; iMP <= iMPLast; iMP++)
                        {
//                           BEMPropertyType* pPT2 = (BEMPropertyType*) soaPropTypes.GetAt( iMP );
//                           assert( pPT2 );
									BEMPropertyType* pPT2 = pBEMProc->getPropertyType( iMP-1 );				assert( pPT2 );
                           if (pPT2)
                           {
                              // Create new PropType
//                              pPT = new BEMPropertyType( pPT2 );
										if (iOverallPropIdx >= iPropTypeSize)
										{	iPropTypeSize += 100;
											pBEMProc->resizePropertyTypes( iPropTypeSize );
										}
				                  pPT = pBEMProc->getPropertyType( iOverallPropIdx, true /*bCreateIfNext*/ );		assert( pPT );
                              if (pPT)
                              {
	                              // incrament ClassPropIdx and OverallPropIdx
   	                           iClassPropIdx++;
      	                        iOverallPropIdx++;

      	                        pPT->Copy( pPT2 );
                                 // Set some PropType data
                                 pPT->set1ClassIdx( iClassIdx );
                                 pPT->set1PropTypeIdx( iClassPropIdx );

                                 // SAC 7/28/02 - Convert Symbolic & Object properties to String in the mirror component (to avoid symbol list and dependency complications)
                                 if (pPT->getPropType() == BEMP_Sym || pPT->getPropType() == BEMP_Obj)
                                    pPT->setPropType( BEMP_Str );

//                                 // add this PropType to the prop type array
//                                 // no need to check num props against BEM_PARAM_MULT since it is simply a copy of an existing class
//                                 soaPropTypes.SetAtGrow( iOverallPropIdx-1, pPT );
                              }
                           }
                        }
                     }
                  }
               }
            }
            else if (iRecHdr == 1)  // PropertyType record
            {
               // Create new PropType
//               pPT = new BEMPropertyType;
					if (iOverallPropIdx >= iPropTypeSize)
					{	iPropTypeSize += 300;
						pBEMProc->resizePropertyTypes( iPropTypeSize );
					}
				   pPT = pBEMProc->getPropertyType( iOverallPropIdx, true /*bCreateIfNext*/ );		assert( pPT );
               if (pPT)
               {  // incrament ClassPropIdx and OverallPropIdx
	               iClassPropIdx++;
	               iOverallPropIdx++;

						// read PropType data from text file
                  pPT->ReadText( file, iFileVersion );

                  // Set some PropType data
                  pPT->set1ClassIdx( iClassIdx );
                  pPT->set1PropTypeIdx( iClassPropIdx );

//                  if (!PropertyNameIsUnique( soaPropTypes, pPT, (iOverallPropIdx-iClassPropIdx), iOverallPropIdx-1 ))
						QString sPropShortName = pPT->getShortName();
						int iPrevPropTypeIdx = BEMP_GetDBParameterID(sPropShortName, iClassIdx);
						if (iPrevPropTypeIdx > 0 && iPrevPropTypeIdx < iClassPropIdx)
						{  // report error, but go ahead and add to array anyway so that subsequent property reading can still proceed
							BEMMessageBox( QString("Multiple BEMProc properties for class '%1' named '%2' found.").arg(pClass->getShortName(), pPT->getShortName()), "", 2 /*warning*/ );
							bRetVal = FALSE;
						}
						else
							pClass->incNumProps();

                  // add this PropType to the prop type array
//                  if (iClassPropIdx < (BEM_COMP_MULT/BEM_PARAM_MULT))
//                     soaPropTypes.SetAtGrow( iOverallPropIdx-1, pPT );
//                  else
                  if (iClassPropIdx >= (BEM_COMP_MULT/BEM_PARAM_MULT))
                  {
                     BEMMessageBox( QString( "Too many property types for class '%1' and %2  (max of %3)" ).arg( pClass->getShortName(), pPT->getShortName(), QString::number( BEM_COMP_MULT/BEM_PARAM_MULT ) ), "", 2 /*warning*/ );
                     bRetVal = FALSE;
                     delete pPT;
                  }
               }
            }
            else
               assert( FALSE );

            iRecHdr = (int) file.ReadLong();   // read next record header value
         }
//         // Set array sizes so that future GetSize() calls return the exact size
//         soaClasses.SetSize( iClassIdx );
//         soaPropTypes.SetSize( iOverallPropIdx );

         if (iRecHdr != -1)
            bRetVal = FALSE;
			else
			{	// trim unused class & property type objects off end of arrays
				pBEMProc->resizeClasses(iClassIdx);
				pBEMProc->resizePropertyTypes(iOverallPropIdx);
			}
      }
		catch (std::exception& e)
		{
			QString msg = QString( "Error Reading BEM Data Model source data.\nFrom File: %1\n\t - cause: %2\n" ).arg( sBEMFileName, e.what() );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
		}
	 	catch (...)
	  	{
			QString msg = QString( "Error Reading BEM Data Model source data.\nFrom File: %1\n" ).arg( sBEMFileName );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
	  	}
   }
	catch (std::exception& e)
	{
		std::cout << "Error opening file: " << sBEMFileName << "  - cause: " << e.what() << '\n';
      bRetVal = FALSE;
	}
 	catch (...)
  	{
	   std::cout << "Error opening file: " << sBEMFileName << '\n';
      bRetVal = FALSE;
	}
   
   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

long ReadDBID( BEMTextIO& symFile )  //, CFile& errorFile )
{
   QString sName;
   symFile.ReadBEMProcParam( sName );
//   long lDBID = GetLocalDatabaseID( sName, 0 );
   long lDBID = BEMPX_GetDatabaseID( sName );

   // Post error to error listing and set bRetVal to FALSE if database ID is invalid
   if (lDBID <= 0)
      BEMMessageBox( QString( "\tParameter '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number( symFile.GetLineCount() ) ), "", 2 /*warning*/ );

   symFile.PostReadToken();
   return lDBID;
}

BOOL ReadBEMEnumsText( std::vector<CASymLst*>& aSymLists, const char* sBEMFileName )
{	BOOL bRetVal = TRUE;

		// what used to be ReadBEMEnumsText( &aSymLists, sEnumsFileName ) function
		QStringList saEnumFiles;
		saEnumFiles.push_back( sBEMFileName );
		for (int iEF=0; (bRetVal && iEF < (int) saEnumFiles.size()); iEF++)
		{
   		try
   		{  // open file
   		   BEMTextIO file( saEnumFiles[iEF].toLocal8Bit().constData(), BEMTextIO::load );
   		   try
   		   {
// 	  	      try
// 	  	      {
   		         CASymDepLst* pCurSymDepLst = NULL;
   		         CASymLst* pCurSymLst = NULL;
   		         int iRecHdr = (int) file.ReadLong();   // read record header value
   		         int iLastRecHdr = -1;
   		         int iLastDefault = 0;
   		         while (iRecHdr >= 0)
   		         {
   		            file.PostReadToken();
   		            if (iRecHdr == 0)  // beginning of a symbol list
   		            {
   		               if (iLastRecHdr != 0)          // last record was NOT a sym list beginning 
   		               {                              // => create a new CASymLst object & add it to the list
   		                  pCurSymLst = new CASymLst;
   		                  aSymLists.push_back( pCurSymLst );
   		               }
   	
   		               assert (pCurSymLst != NULL);
   		               // read symbol list's DBID
   		               long lSymDBID = ReadDBID( file );
   		               pCurSymLst->m_aDBIDs.push_back( (DWORD) lSymDBID );
   		               iLastDefault = (int) file.ReadLong();  // read default value for this symbol list

   		               // Post error message if DBID is not of type BEMP_Sym
// 	  	               if (GetLocalDataType( lSymDBID ) != BEMP_Sym)
   		               if (BEMPX_GetDataType( lSymDBID ) != BEMP_Sym)
   		                  BEMMessageBox( QString( "\tParameter not of type 'BEMP_Sym' on line: %1\n\n" ).arg( QString::number( file.GetLineCount() ) ), "", 2 /*warning*/ );
   		            }
   		            else if (iRecHdr == 1)  // beginning of a symbol dep list
   		            {
   		               assert (pCurSymLst != NULL);
   		               if (iLastRecHdr != 1)          // last record was NOT a sym dep list beginning 
   		               {                              // => create a new CASymDepLst object & add it to the current CASymLst
   		                  pCurSymDepLst = new CASymDepLst;
   		                  pCurSymLst->m_aSymDepLists.push_back( pCurSymDepLst );
   		               }
   	
   		               assert (pCurSymDepLst->m_iNumDepDBIDs < MAX_DEP_DBIDS_PER_SYMBOL_LIST);
   		               pCurSymDepLst->m_lDBID[     pCurSymDepLst->m_iNumDepDBIDs   ] = ReadDBID( file );
   		               pCurSymDepLst->m_fDepValue[ pCurSymDepLst->m_iNumDepDBIDs++ ] = file.ReadDouble();
   		               file.PostReadToken();
   		               pCurSymDepLst->m_iDefaultValue = file.ReadLong();
   		            }
   		            else if (iRecHdr == 2)  // a single symbol definition
   		            {
   		               assert (pCurSymLst != NULL);
   		               if (iLastRecHdr == 0)          // last record was a sym list beginning 
   		               {                              // => must create a dummy CASymDepLst object w/ no dependencies
   		                  pCurSymDepLst = new CASymDepLst( iLastDefault );  // use CASymLst default
   		                  pCurSymLst->m_aSymDepLists.push_back( pCurSymDepLst );
   		               }
   		               assert (pCurSymDepLst != NULL);
   		               CASym* pCurSym = new CASym;							assert( pCurSym );
   		               pCurSym->m_iValue = file.ReadLong();       // read numeric value of this symbol
   		               file.PostReadToken();
   		               pCurSym->m_sString = file.ReadString();   // read symbol string
   		               pCurSymDepLst->m_olSymbols.push_back( pCurSym );
   		            }
   		            else if (iRecHdr == 3)  // read additional symbol definition data from similarly formatted text files
							{
   		               QString sEnumFile = file.ReadString();
								if (sEnumFile.isEmpty())
								{	assert( FALSE );	// post error or just ignore blank enum filename ???
								}
								else
								{	if (sEnumFile.indexOf(':') < 0 || sEnumFile.indexOf( '\\' ) != 0)
									{	if (saEnumFiles[iEF].lastIndexOf('\\') > 0)
											sEnumFile = saEnumFiles[iEF].left( saEnumFiles[iEF].lastIndexOf('\\')+1 ) + sEnumFile;
									}
									if (!FileExists( sEnumFile.toLocal8Bit().constData() ))
									{	assert( FALSE );	// post error or just ignore missing enum file ???
									}
									else
										saEnumFiles.push_back( sEnumFile );
								}
							}
   	
   		            iLastRecHdr = iRecHdr;
   		            iRecHdr = (int) file.ReadLong();   // read next record header value
   		         }
   	
   		         if (iRecHdr != -1)
   		            bRetVal = FALSE;
// 	  	      }
// 	  	      CATCH( BEMTextioException, err )
// 	  	      {
// 	  	         if ( err->m_cause == BEMTextioException::endOfFile )
// 	  	            ; // we're done, no problem
// 	  	         else
// 	  	            THROW_LAST();
// 	  	      }
// 	  	      END_CATCH
   		   }
// 	  	   CATCH( BEMTextioException, err )
// 	  	   {
// 	  	      QString msg = QString("Error Reading symbols\n");
// 	  	      msg += QString("From File: ") + saEnumFiles[iEF] + QString( "\n" );
// 	  	      msg += QString("\n\t") + QString( err->m_strError ) + QString("\n") + QString("\n");
// 	  	      bRetVal = FALSE;
// 	  	
// 	  	      BEMMessageBox( msg, "", 2 /*warning*/ );
// 	  	      THROW_LAST();
// 	  	   }
// 	  	   END_CATCH
				catch (std::exception& e)
				{
					QString msg = QString( "Error reading enumeration definitions.\nFrom File: %1\n\t - cause: %2\n" ).arg( saEnumFiles[iEF], e.what() );
					std::cout << msg.toLocal8Bit().constData();
		         BEMMessageBox( msg, "", 2 /*warning*/ );
		         bRetVal = FALSE;
				}
			 	catch (...)
			  	{
					QString msg = QString( "Error reading enumeration definitions.\nFrom File: %1\n" ).arg( saEnumFiles[iEF] );
					std::cout << msg.toLocal8Bit().constData();
		         BEMMessageBox( msg, "", 2 /*warning*/ );
		         bRetVal = FALSE;
			  	}
   	
   		   file.Close();  // SAC 6/1/06
   		}
// 	  	CATCH( CFileException, error )
// 	  	{
// 	  	   QString msg = QString( "Error opening file: " ) + saEnumFiles[iEF];
// 	  	   BEMMessageBox( msg, "", 2 /*warning*/ );
// 	  	   bRetVal = FALSE;
// 	  	}
// 	  	END_CATCH
			catch (std::exception& e)
			{
				QString msg = QString( "Error opening enumeration definitions file: %1\n\t - cause: %2\n" ).arg( saEnumFiles[iEF], e.what() );
				std::cout << msg.toLocal8Bit().constData();
   	      BEMMessageBox( msg, "", 2 /*warning*/ );
   	      bRetVal = FALSE;
			}
		 	catch (...)
		  	{
				QString msg = QString( "Error opening enumeration definitions file: %1\n" ).arg( saEnumFiles[iEF] );
				std::cout << msg.toLocal8Bit().constData();
   	      BEMMessageBox( msg, "", 2 /*warning*/ );
   	      bRetVal = FALSE;
		  	}
		}  // end of loop over each enumerations file

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

static bool WriteSymbols( CryptoFile& file, std::vector<CASymLst*>& aSymLists );
static void WriteSymbolsToText( QString sFileName, std::vector<CASymLst*>& aSymLists );

BOOL WriteCompiledBEMProc( const char* pszBEMBinFileName, std::vector<CASymLst*>& aSymLists )
{
	QString sFileName = pszBEMBinFileName;
	BOOL bRet = FALSE;
	CryptoFile file( pszBEMBinFileName );
	// attempt to open output binary encrypted ruleset file
	try
	{
		if (file.open( QIODevice::WriteOnly | QIODevice::Truncate ))
		{                             
			// Write the BEMProc Version and Class and PropType array sizes to the file
			int iVersion = BEMPROC_VERSION;
			int iClassCount = (int) eBEMProc.getNumClasses();
			int iPropTypeCount = (int) eBEMProc.getNumPropertyTypes();
			int iNumSymTables = 0;		// pSymbols->m_psaSymbolTables.GetSize();   // SAC 6/26/06
			file.WriteDirect( &iVersion, sizeof( int ) );
			int iSecure = (BEMPX_SecureExecutable() ? 1 : 0);	// SAC 1/3/17
			file.WriteDirect( &iSecure, sizeof( int ) );

			file.Write( &iClassCount, sizeof( int ) );
			file.Write( &iPropTypeCount, sizeof( int ) );
			file.Write( &iNumSymTables, sizeof( int ) );   // SAC 6/26/06

			// write each BEMClass to the file
			int i=0;
			for (; i < iClassCount; i++)
			{
				BEMClass* pClass = eBEMProc.getClass( i );					assert(pClass);
				pClass->Write( file );
			}
			// write each CBEMAsciiPropType to the file
			for (i=0; i < iPropTypeCount; i++)
			{
				BEMPropertyType* pPT = eBEMProc.getPropertyType( i );		assert(pPT);
				pPT->Write( file );
			}

#ifdef _DEBUG
			WriteSymbolsToText( sFileName, aSymLists );		// write DEBUG Symbol data to text file
#endif

			WriteSymbols( file, aSymLists );						// write Symbol data to file

			file.close();          // close output file
			bRet = TRUE;
		}
		else
			BEMMessageBox( QString( "Unable to open output file:\n  %1" ).arg( sFileName ), "", 3 /*error*/ );
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error writing binary data model file: %1\n\t - cause: %2\n" ).arg( sFileName, e.what() );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error writing binary data model file: %1\n" ).arg( sFileName );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}
	return bRet;
}

bool WriteSymbols( CryptoFile& file, std::vector<CASymLst*>& aSymLists )
{	// previsouly wrote symbol tables first...
	int count = (int) aSymLists.size();
	file.Write( &count, sizeof( int ) );
	for (std::vector<CASymLst*>::iterator it = aSymLists.begin(); it != aSymLists.end(); ++it)
		(*it)->Write( file );	// write each CASymLst to the file
   return TRUE;
}

void WriteSymbolsToText( QString sFileName, std::vector<CASymLst*>& aSymLists )
{
   // convert filename from binary compiled BEMProc to debug symbols text file
   sFileName = sFileName.left( sFileName.lastIndexOf('.') );
   sFileName += " - Enums Debug.txt";
	try
	{
      BEMTextIO file( sFileName.toLocal8Bit().constData(), BEMTextIO::store );
      try
      {
			int count = (int) aSymLists.size();
			//file.Write( &count, sizeof( int ) );
			file << count;
			file.NewLine();
			for (std::vector<CASymLst*>::iterator it = aSymLists.begin(); it != aSymLists.end(); ++it)
				(*it)->WriteText( file );	// write each CASymLst to the file
      }
		catch (std::exception& e)
		{
			QString msg = QString( "Error writing enumeration debug data to file: %1\n\t - cause: %2\n" ).arg( sFileName, e.what() );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
		}
	 	catch (...)
	  	{
			QString msg = QString( "Error writing enumeration debug data to file: %1\n" ).arg( sFileName );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
	  	}
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening enumeration debug file: %1\n\t - cause: %2\n" ).arg( sFileName, e.what() );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening enumeration debug file: %1\n" ).arg( sFileName );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static bool WriteCompiledRuleset( LPCSTR fileName, QFile& errorFile );

BOOL BEMPX_CompileRuleset(	const char* sBEMBinFileName, const char* sPrimRuleFileName, const char* sCompiledRuleFileName,
									const char* sLogFileName /*=NULL*/, QString* psRuleCompileMsg/*=NULL*/ )
{
	BOOL bRetVal = TRUE;

   // blast any current ruleset data
   ruleSet.clear();
   if (!eBEMProc.decompileBinBEMProc( sBEMBinFileName ))
   	return FALSE;

	QFile fileLog( sLogFileName );
	try
	{
		if (fileLog.open( QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate ))
		{                             
			// create "Reading..." message and write to error file
			QString readMsg = QString( "Reading rules file:  %1\n\n" ).arg( sPrimRuleFileName );
			fileLog.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

			QString fileNameString = sPrimRuleFileName;
			RuleFile file( fileNameString );   // create and open ruleset file

			fileNameString.replace('\\', '/');
			int iPathLen = fileNameString.lastIndexOf('/');
			if (iPathLen > 0)
			{	bool bCurPathOK = QDir::setCurrent( fileNameString.left(iPathLen) );		assert( bCurPathOK );
			}

			bRetVal = file.Read( fileLog );   // read ASCII rules into memory

			if (bRetVal)
				bRetVal = WriteCompiledRuleset( sCompiledRuleFileName, fileLog );

			fileLog.close();                  // close log file
		}
		else
			BEMMessageBox( QString( "Unable to open ruleset compilation log file:\n  %1" ).arg( sLogFileName ), "", 3 /*error*/ );
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error writing ruleset compilation log file: %1\n\t - cause: %2\n" ).arg( sLogFileName, e.what() );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error writing ruleset compilation log file: %1\n" ).arg( sLogFileName );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}
	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

int BEMPX_ParseRuleListFile(	const char* sRuleListFileName, QStringList& saRuleListNames,
										const char* sLogFileName /*=NULL*/, QString* psRuleCompileMsg/*=NULL*/, bool bParseRules /*=false*/ )
{
	int iRetVal = 0;

// shouldn't blast current ruleset data when parsing a single rulelist file
//   // blast any current ruleset data
//   ruleSet.clear();
//   if (!eBEMProc.decompileBinBEMProc( sBEMBinFileName ))
//   	return FALSE;

	QFile fileLog( sLogFileName );
	try
	{
		if (fileLog.open( QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate ))
		{                             
			// create "Reading..." message and write to error file
			QString readMsg = QString( "Reading rulelist file:  %1\n\n" ).arg( sRuleListFileName );
			fileLog.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

			QString fileNameString = sRuleListFileName;
			RuleFile file( fileNameString );   // create and open ruleset file

// no need to switch current path when parsing only a single rulelist file
//			fileNameString.replace('\\', '/');
//			int iPathLen = fileNameString.lastIndexOf('/');
//			if (iPathLen > 0)
//			{	bool bCurPathOK = QDir::setCurrent( fileNameString.left(iPathLen) );		assert( bCurPathOK );
//			}

			//file.lFileStructVer = ruleSet.getFileStructVersion()();
//			bRetVal = file.Read( fileLog );   // read ASCII rules into memory

				int ruleListIndex = ruleSet.getNumRuleLists();
				int iNumOrigRuleLists = ruleListIndex;
				int iNumRuleFiles = 1;
				if (file.ReadRuleFile( fileNameString.toLocal8Bit().constData(), iNumRuleFiles++, ruleListIndex, fileLog, ruleSet.getFileStructVersion() ))
					iRetVal = ruleSet.getNumRuleLists() - iNumOrigRuleLists;
				for (int i=iNumOrigRuleLists; (iRetVal > 0 && i < (iNumOrigRuleLists+iRetVal)); i++)
				{	RuleList* pRL = ruleSet.getRuleList( i );		assert( pRL != NULL );
					if (pRL)
					{	if (bParseRules)
						{	if (!pRL->Parse( fileLog ))
							{	ruleSet.deleteTrailingRuleLists( iRetVal );		// blast newly added rulelists
								iRetVal = 0;
						}	}
						if (iRetVal > 0)
							saRuleListNames.push_back( pRL->getName() );
				}	}

//			if (bRetVal)
//				bRetVal = WriteCompiledRuleset( sCompiledRuleFileName, fileLog );

			fileLog.close();                  // close log file
		}
		else
			BEMMessageBox( QString( "Unable to open rulelist parsing log file:\n  %1" ).arg( sLogFileName ), "", 3 /*error*/ );
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error writing rulelist parsing log file: %1\n\t - cause: %2\n" ).arg( sLogFileName, e.what() );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error writing rulelist parsing log file: %1\n" ).arg( sLogFileName );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

void BEMPX_GetBEMBaseFile( QString& sBEMBaseFile, int iBEMProcIdx/*=-1*/ )		// was: BEMPX_GetBEMProcPathFile()
{	sBEMBaseFile.clear();
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
	if (pBEMProc)
		sBEMBaseFile = pBEMProc->getBEMProcFileName();
	return;
}


/////////////////////////////////////////////////////////////////////////////
//
// Extern Function:  CheckRulesetFileVerAndReadID()
//
// Purpose ------------------------------------------------------------------
//   Read in the RulPrc version ID string and compare with the current
//   version.  If it is compatible (matches) then read in the ruleset ID and
//   version strings.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file            : file to read the info from
//   QString&    sRuleSetID      : string to populate with the ruleset ID
//   QString&    sRuleSetVersion : string to populate with the ruleset version
//   
// Return Value -------------------------------------------------------------
//   TRUE if this ruleset file matches the current RulPrc file version, else
//   FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool CheckRulesetFileVerAndReadID( CryptoFile& file, QString& sRuleSetID, QString& sRuleSetVersion, 
												int& iStructVer, bool& bRulesetSecure )
{
   // Read RulPrc file version info from file
   QString sFileVer;
   file.ReadQString( sFileVer );

   // Compare file ver string from file to the current one, and return FALSE if different
   QString sRP32Ver = szBEMRulPrcVersion;
   bRulesetSecure = false;
   if (sRP32Ver == sFileVer)
   {
      // read in RULESETID and RULESETVERSION
      sRuleSetID.clear();
      sRuleSetVersion.clear();
      file.ReadQString( sRuleSetID );
      file.ReadQString( sRuleSetVersion );

      if (sRP32Ver == sFileVer)
      {  file.ReadDirect( &iStructVer, sizeof( int ) );
      	if (iStructVer >= 19)
      	{	int iScr;	file.ReadDirect( &iScr, sizeof( int ) );
      		bRulesetSecure = (iScr > 0);
      }	}
      else
         iStructVer = 1;

      return true;
   }
   return false;
}


/////////////////////////////////////////////////////////////////////////////
// Exported Function:  WriteCompiledRuleset()
/////////////////////////////////////////////////////////////////////////////
bool WriteCompiledRuleset( LPCSTR fileName, QFile& errorFile )
{	return ruleSet.writeCompiledRuleset( fileName, errorFile );
}

bool RuleSet::writeCompiledRuleset( LPCSTR fileName, QFile& errorFile )
{ 
   bool bRetVal = FALSE;
	try
	{
      CryptoFile file( fileName );
		if (!file.open( QIODevice::WriteOnly | QIODevice::Truncate ))
			BEMMessageBox( QString( "Unable to open output binary compiled ruleset:\n  %1" ).arg( fileName ), "", 3 /*error*/ );
		else
      {	QString dbgMsg;
         // write RulPrc file version info to file
         QString sRP32Ver = szBEMRulPrcVersion;
         file.WriteQString( sRP32Ver );

         // next write RULESETID and RULESETVERSION
         file.WriteQString( m_sRuleSetID );
         file.WriteQString( m_sRuleSetVersion );

         // SAC 6/12/00 - next write RULESET_STRUCT_VERSION
         file.WriteDirect( &siCurBEMRulPrcFileStructVersion, sizeof( int ) );

			int iRulesSecure = (BEMPX_SecureExecutable() ? 1 : 0);		// SAC 12/29/16 - added to track whether encryption used when writing ruleset
         file.WriteDirect( &iRulesSecure, sizeof( int ) );

			file.WriteQString( m_sBEMBaseFile );		// SAC 8/15/14 - added

         // next write Screens and ToolTips text filename strings
         file.WriteQString( m_sScreensFile );
         file.WriteQString( m_sToolTipsFile );

         file.Write( &m_iRulesetOrganization, sizeof( int ) );  // SAC 10/18/12

			int i, iRd = (int) m_saLabels.size();		// SAC 9/8/14 - labels used to facilitate ruleset source shared by multiple standards/versions
			file.Write( &iRd, sizeof( int ) );
			for (i=0; i<iRd; i++)
	         file.WriteQString( m_saLabels.at(i) );

         file.Write( &m_lSimulateDBID, sizeof( long ) );  // SAC 3/18/14

         // now write rest of ruleset file
         long	lRuleBytes, lTableBytes, lDTBytes, lRangeBytes, lSymbolBytes, lMaxChildBytes,
					lResetBytes, lUnqAssBytes, lPropTypeModBytes, lLibBytes, lTransformBytes, lRulePropBytes, lToolTipBytes;
         bRetVal = m_ruleListList.Write( file, errorFile );  // write rules to output file
         lRuleBytes = file.m_lByteCount;

		// SAC 7/11/12 - moved RulesetProperties up to first thing written/read so that they can be processed PRIOR to their dependencies (data types & symbols)
			iRd = numRulesetProperties();		// SAC 7/6/12
			file.Write( &iRd, sizeof( int ) );
			for (i=0; i<iRd; i++)
			{	getRuleSetProperty(i)->Write( file );
			}
			lRulePropBytes = file.m_lByteCount;

         // write tables to output file
			   int nTables = (int) m_tables.size();
			   file.Write( &nTables, sizeof( int ) );  // write number of tables to file
#ifdef _DEBUG
				dbgMsg = QString( "\n   Writing list of %1 tables.\n" ).arg( QString::number(nTables) );
			   errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif
			   int iTableIdx = 1;
			   for (; iTableIdx <= nTables; iTableIdx++)
			   {  // get next table
			      BEMTable *table = m_tables.at(iTableIdx-1);			assert( table );
			      if (table)
			      {
#ifdef _DEBUG
			         dbgMsg = QString( "      Table: %1 '%2'" ).arg( QString::number(iTableIdx), table->getName() );
			         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif
			         // write table data to file
			         table->Write( file, errorFile );
			      }
			   }   
         lTableBytes = file.m_lByteCount;

         // write data types to output file
			   int nDataTypes = (int) m_dataTypes.size();
			   // write the number of datatype definitions
			   file.Write( &nDataTypes, sizeof( int ) );
			   // loop over entire list, writing each to the file
			   for (i=0; i<nDataTypes; i++)
			   {  BEMPropertyDataType* dataType = m_dataTypes.at(i);		assert( dataType );
			      dataType->Write( file );
			   }
         lDTBytes = file.m_lByteCount;

         // write range checks to output file
			   int nRanges = (int) m_ranges.size();
			   // write the number of range check definitions
			   file.Write( &nRanges, sizeof( int ) );
			   // loop over entire list, writing each to the file
			   for (i=0; i<nRanges; i++)
			   {  BEMRangeCheck* range= m_ranges.at(i);			assert( range );
			      range->Write( file );
			   }
         lRangeBytes = file.m_lByteCount;

         // write symbol list to output file
			   int nSymLists = (int) m_symbolLists.size();
			   // write the number of symbol list definitions
			   file.Write( &nSymLists, sizeof( int ) );
				for (i=0; i < nSymLists; i++)
				{	assert( m_symbolLists.at(i) );
					if (m_symbolLists.at(i))
						m_symbolLists.at(i)->Write( file );;
				}
         lSymbolBytes = file.m_lByteCount;

//         m_maxChildList.Write( file );    // write MaxChild list to output file
         lMaxChildBytes = file.m_lByteCount;

         // write reset list to output file
			   int nResets = (int) m_resets.size();
			   // write the number of reset list definitions
			   file.Write( &nResets, sizeof( int ) );
			   // loop over entire list, writing each to the file
				for (i=0; i < nResets; i++)
			   {
			      BEMResetData* reslst = m_resets.at(i);			assert( reslst );
			      reslst->Write( file );
			   }
         lResetBytes = file.m_lByteCount;

//         m_uniqueAssignmentList.Write( file ); // write Unique Assignment list to output file
         lUnqAssBytes = file.m_lByteCount;

         // write data used to update BEMBase PropertyType objects
			   int nRPTMs = (int) m_rulePropTypeMods.size();
			   // write the number of RulePropTypeMod definitions
			   file.Write( &nRPTMs, sizeof( int ) );
			   // loop over entire list, writing each to the file
				for (i=0; i < nRPTMs; i++)
			   {  BEMPropTypeMod* pRulePropTypeMod = m_rulePropTypeMods.at(i);		assert( pRulePropTypeMod );
			      pRulePropTypeMod->Write( file );
			   }
			lPropTypeModBytes = file.m_lByteCount;

			iRd = m_ruleToolTips.size();		// SAC 5/11/14
			file.Write( &iRd, sizeof( int ) );
			for (i=0; i<iRd; i++)
			{	bool bWriteTTs = m_ruleToolTips[i]->Write( file );		assert( bWriteTTs );
			}
			lToolTipBytes = file.m_lByteCount;

			//m_transformations.Write( file );		// SAC 6/21/12
			iRd = m_transformations.size();
			file.Write( &iRd, sizeof( int ) );
			for (i=0; i<iRd; i++)
			{	bool bWriteTrans = m_transformations[i]->Write( file );		assert( bWriteTrans );
			}
			lTransformBytes = file.m_lByteCount;

         WriteRuleLibrary( file, errorFile );     // write rule library to output file
         lLibBytes = file.m_lByteCount;

         file.close();          // close output file

			// SAC 3/26/03 - loop over all rulelists, writing summary of each to the output file
         QString tempStr;
         dbgMsg =           "\n\nRulelist Summary:                                                                   Allow  Tag As"
                              "\n         Line   Num                                                       Set ALL    Mult   User   Perform"
                              "\n  Num     Num  Rules  Rulelist Name                                         Data    Evals  Defind   Resets   Rulelist Filename"
                              "\n  ---------------------------------------------------------------------------------------------------------------------";
         QString sSpearator = "\n      ---------------------------------------------------------------------------------------------------------";
			int iNumRLs = getNumRuleLists();
			for (int iRL=1; iRL <= iNumRLs; iRL++)
			{	RuleList* ruleList = getRuleList(iRL-1);
            if (ruleList)
            {
               //tempStr.Format( "\n%5d %7ld %5ld   %-52s   %s        %s      %s        %s      %s", iRL, ruleList->m_iLineNumber, ruleList->GetCount(), ruleList->m_name,
               //                (ruleList->m_bSetAllData ? "T":"-"), (ruleList->m_bAllowMultipleEvaluations ? "T":"-"), (ruleList->m_bTagAllDataAsUserDefined ? "T":"-"),
               //                (ruleList->m_bPerformSetBEMDataResets ? "T":"-"), ruleList->m_sFileName );  // SAC 9/18/05
               //dbgMsg += tempStr;
               dbgMsg += QString( "\n%1 %2 %3   %4   %5        %6      %7        %8      %9" ).arg( QString::number(iRL), 5 ).arg( QString::number(ruleList->getLineNumber()), 7 ).arg(
               								QString::number(ruleList->getRuleCount()), 5 ).arg( ruleList->getName(), -52 ).arg( 
                               (ruleList->getSetAllData() ? "T":"-"), (ruleList->getAllowMultipleEvaluations() ? "T":"-"), (ruleList->getTagAllDataAsUserDefined() ? "T":"-"),
                               (ruleList->getPerformSetBEMDataResets() ? "T":"-"), ruleList->getFileName() );
               if (iRL % 5 == 0)
                  dbgMsg += sSpearator;
         }	}
         dbgMsg += "\n";
         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );

         //dbgMsg.Format( "%ld", lRuleBytes );
         //dbgMsg =             "\n\nBinary Ruleset Writing Summary (bytes written):\n   Rules:      " + dbgMsg;
         //tempStr.Format( "%ld", lRulePropBytes  - lRuleBytes      );   dbgMsg += "\n   Rule Props: " + tempStr;
         //tempStr.Format( "%ld", lTableBytes     - lRulePropBytes  );   dbgMsg += "\n   Tables:     " + tempStr;
         //tempStr.Format( "%ld", lDTBytes        - lTableBytes     );   dbgMsg += "\n   DataTypes:  " + tempStr;
         //tempStr.Format( "%ld", lRangeBytes     - lDTBytes        );   dbgMsg += "\n   Ranges:     " + tempStr;
         //tempStr.Format( "%ld", lSymbolBytes    - lRangeBytes     );   dbgMsg += "\n   Symbols:    " + tempStr;
         //tempStr.Format( "%ld", lMaxChildBytes  - lSymbolBytes    );   dbgMsg += "\n   MaxChild:   " + tempStr;
         //tempStr.Format( "%ld", lResetBytes     - lMaxChildBytes  );   dbgMsg += "\n   Resets:     " + tempStr;
         //tempStr.Format( "%ld", lUnqAssBytes    - lResetBytes     );   dbgMsg += "\n   UnqAssign:  " + tempStr;
         //tempStr.Format( "%ld", lPropTypeModBytes - lUnqAssBytes  );   dbgMsg += "\n   PropTypMod: " + tempStr;
         //tempStr.Format( "%ld", lToolTipBytes - lPropTypeModBytes );   dbgMsg += "\n   ToolTips:   " + tempStr;
         //tempStr.Format( "%ld", lTransformBytes - lToolTipBytes   );   dbgMsg += "\n   Transforms: " + tempStr;
         //tempStr.Format( "%ld", lLibBytes       - lTransformBytes );   dbgMsg += "\n   Library:    " + tempStr;
         //dbgMsg += "\n";
         dbgMsg  = QString( "\n\nBinary Ruleset Writing Summary (bytes written):\n   Rules:      %1" ).arg( QString::number(lRuleBytes) );
         dbgMsg += QString( "\n   Rule Props: %1"   ).arg( QString::number( lRulePropBytes  - lRuleBytes      ) );
         dbgMsg += QString( "\n   Tables:     %1"   ).arg( QString::number( lTableBytes     - lRulePropBytes  ) );
         dbgMsg += QString( "\n   DataTypes:  %1"   ).arg( QString::number( lDTBytes        - lTableBytes     ) );
         dbgMsg += QString( "\n   Ranges:     %1"   ).arg( QString::number( lRangeBytes     - lDTBytes        ) );
         dbgMsg += QString( "\n   Symbols:    %1"   ).arg( QString::number( lSymbolBytes    - lRangeBytes     ) );
         dbgMsg += QString( "\n   MaxChild:   %1"   ).arg( QString::number( lMaxChildBytes  - lSymbolBytes    ) );
         dbgMsg += QString( "\n   Resets:     %1"   ).arg( QString::number( lResetBytes     - lMaxChildBytes  ) );
         dbgMsg += QString( "\n   UnqAssign:  %1"   ).arg( QString::number( lUnqAssBytes    - lResetBytes     ) );
         dbgMsg += QString( "\n   PropTypMod: %1"   ).arg( QString::number( lPropTypeModBytes - lUnqAssBytes  ) );
         dbgMsg += QString( "\n   ToolTips:   %1"   ).arg( QString::number( lToolTipBytes - lPropTypeModBytes ) );
         dbgMsg += QString( "\n   Transforms: %1"   ).arg( QString::number( lTransformBytes - lToolTipBytes   ) );
         dbgMsg += QString( "\n   Library:    %1\n" ).arg( QString::number( lLibBytes       - lTransformBytes ) );
         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
      }
//      else
//         BEMMessageBox( "Unable to open output file.", NULL, 3 /*error*/ );
      //errorFile.Close();        // close error file
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error writing binary compiled ruleset file: %1\n\t - cause: %2\n" ).arg( fileName, e.what() );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error writing binary compiled ruleset file: %1\n" ).arg( fileName );
		std::cout << sErrMsg.toLocal8Bit().constData();
		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}

   return bRetVal;
}
