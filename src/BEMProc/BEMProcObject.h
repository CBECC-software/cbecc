/**********************************************************************
 *  Copyright (c) 2012-2016, California Energy Commission
 *  Copyright (c) 2012-2016, Wrightsoft Corporation
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

#ifndef __BEMPROCOBJECT_H__
#define __BEMPROCOBJECT_H__


#include "BEMProc.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMSymbols.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	BEM Run Hourly Results

#define	BEMRun_MaxNumRuns				   6
#define	BEMRun_RunNameLen				  32
#define	BEMRun_RunAbbrevLen			  16
#define	BEMRun_NumMeters				   4
#define	BEMRun_MeterNameLen			  16
#define	BEMRun_NumEnduses				  48   // SAC 8/13/12 - doubled enduse array size since it needs to accommodate TDV versions of each enduse in addition to energy
#define	BEMRun_EnduseNameLen			  32	 // SAC 4/15/15 - 16->32 to accommodate nonres' 'Domestic Hot Water'
#define	BEMRun_NumHourlyResults		8760

/////////////////////////////////////////////////////////////////////////////
//	BEMRunHourlyResultEnduse

class BEMRunHourlyResultEnduse
{
public:
	BEMRunHourlyResultEnduse();
	void    init();
	void    initValues()				{	for (int i=0; i < BEMRun_NumHourlyResults; i++)
													m_hourly[i] = 0.0;
												m_total = 0.0;  }

	bool nameEqual( const char* pszChk );

	void setName( const char* pszName )		{	strcpy_s( m_enduseName, BEMRun_EnduseNameLen, pszName );  }
	const char* getName()	{	return m_enduseName;  }

	double  getHourly( int i )		{	assert( i>=0 && i<BEMRun_NumHourlyResults );
												return m_hourly[i];  }
	double* getHourlyArray()		{	return &m_hourly[0];  }
	void    addIntoHourly( int i, double d )
											{	assert( i>=0 && i<BEMRun_NumHourlyResults );
												m_hourly[i] += d;
												m_total     += d;  }
	double  getTotal()				{	return m_total;  }

private:
   char		m_enduseName[ BEMRun_EnduseNameLen ];
	double	m_total;
	double	m_hourly[ BEMRun_NumHourlyResults ];
};

/////////////////////////////////////////////////////////////////////////////
//	BEMRunHourlyResultMeter

class BEMRunHourlyResultMeter
{
public:
	BEMRunHourlyResultMeter();
	void init();
	bool nameEqual( const char* pszChk );
	int                       getHourlyResultEnduseIndex( const char* pszEnduseName );
	BEMRunHourlyResultEnduse* getHourlyResultEnduse( const char* pszEnduseName );
	BEMRunHourlyResultEnduse* getEnduse( int i )
								{	if (i < 0 || i >= BEMRun_NumEnduses)
										return NULL;
									return &m_enduses[i];  }
	void setName( const char* pszMeterName )		{	strcpy_s( m_meterName, BEMRun_MeterNameLen, pszMeterName );  }
	const char* getName()	{	return m_meterName;  }
	int  getNumEnduses()		{	return m_numEnduses;  }
	BEMRunHourlyResultEnduse* addHourlyResultEnduse( const char* pszEnduseName )
									{	if (m_numEnduses < 0 || m_numEnduses >= BEMRun_NumEnduses)
											return NULL;
										m_enduses[m_numEnduses].setName( pszEnduseName );
										m_enduses[m_numEnduses].initValues();
										return &m_enduses[m_numEnduses++];  }

private:
   char		m_meterName[ BEMRun_MeterNameLen ];
	int		m_numEnduses;
	BEMRunHourlyResultEnduse  m_enduses[ BEMRun_NumEnduses ];
};

/////////////////////////////////////////////////////////////////////////////
//	BEMRun

class BEMRun
{
public:
	BEMRun();
	void init( const char* pszName=NULL, const char* pszAbbrev=NULL );
	bool nameEqual( const char* pszChk );
	const char* getName()		{	return m_runName;  }
	bool abbrevEqual( const char* pszChk );
	const char* getAbbrev()		{	return m_runAbbrev;  }
	int                      getHourlyResultMeterIndex( const char* pszMeterName );
	BEMRunHourlyResultMeter* getHourlyResultMeter( const char* pszMeterName );
	BEMRunHourlyResultMeter* getHourlyResultMeter( int i )
								{	if (i < 0 || i >= BEMRun_NumMeters)
										return NULL;
									return &m_hourlyResults[i];  }
	int readCSEHourlyResults( const char* pszFilename, const char** ppResMeters=NULL, const char** ppMetersMap=NULL,
										double* pdMetersMult=NULL, const char** ppResEnduses=NULL, const char** ppEnduseMap=NULL );
	int getNumMeters()	{	return m_numMeters;  }
	BEMRunHourlyResultMeter* setNextMeterName( const char* pszMeterName )
								{	if (m_numMeters >= BEMRun_NumMeters)
										return NULL;
									m_hourlyResults[m_numMeters].setName( pszMeterName );
									m_numMeters++;
									return &m_hourlyResults[m_numMeters-1];  }
	void setMeterName( int i, const char* pszMeterName )
								{	if (i >= 0 && i < m_numMeters)
										m_hourlyResults[i].setName( pszMeterName );  }

private:
   char		m_runName[   BEMRun_RunNameLen   ];
   char		m_runAbbrev[ BEMRun_RunAbbrevLen ];
	int		m_numMeters;
	BEMRunHourlyResultMeter  m_hourlyResults[ BEMRun_NumMeters ];
};

//	BEM Run Hourly Results - end
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// BEMProcObject
//    An instance of this class is created ...
/////////////////////////////////////////////////////////////////////////////

class BEMProcObject
{
public:
	BEMProcObject();
	~BEMProcObject();

// Operations
public:
   void clear();
	void clearPropTypes();		// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
   BOOL init( int numClasses, int numPropTypes );
	BOOL initPropertyTypes( int iNumPropTypes );		// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
	BOOL copy( BEMProcObject* copyFrom, BOOL copyObjects=TRUE );

   BOOL decompileBinBEMProc( const char* binFileName, BOOL onlySymbol=FALSE );

   void dumpSymbols( QString sFileName );  // SAC 3/14/07

	void		initRuns()			{	for (int iRun=0; iRun < m_numRuns; iRun++)
												m_runs[iRun].init();
											m_numRuns = 0;  }
	BOOL		initRun( int i, const char* pszName=NULL, const char* pszAbbrev=NULL )
										{	if (i >= 0 && i < BEMRun_MaxNumRuns)
											{	m_runs[i].init( pszName, pszAbbrev );
												m_numRuns = std::max( m_numRuns, i+1 );
												return TRUE;
											}
											return FALSE;  }
	int		getNumRuns()		{	return m_numRuns;  }
	BEMRun*	getRun( const char* pszRunName );
	BEMRun*	getRun( int i )	{	if (i < 0 || i >= BEMRun_MaxNumRuns)
												return NULL;
											return &m_runs[i];  }
	int		readCSEHourlyResults( int i, const char* pszName, const char* pszAbbrev,
										const char* pszFilename, const char** ppResMeters=NULL, const char** ppMetersMap=NULL,
										double* pdMetersMult=NULL, const char** ppResEnduses=NULL, const char** ppEnduseMap=NULL )
										{	if (i < 0 || i >= BEMRun_MaxNumRuns)
												return -1;
											m_runs[i].init( pszName, pszAbbrev );
											m_numRuns = std::max( m_numRuns, i+1 );
											return m_runs[i].readCSEHourlyResults( pszFilename, ppResMeters, ppMetersMap,
																								pdMetersMult, ppResEnduses, ppEnduseMap );
										}

	BEMClass*			getClass( int i0Class )				{	assert(  i0Class >= 0 && i0Class < (int) m_classes.size() );
																			return ((i0Class >= 0 && i0Class < (int) m_classes.size()) ? &m_classes[i0Class] : NULL);		}
	int					getClass_NumObjects( int i0Class, BEM_ObjType objType )
																		{	assert(  i0Class >= 0 && i0Class < (int) m_classes.size() );
																			return ((i0Class >= 0 && i0Class < (int) m_classes.size()) ? m_classes[i0Class].ObjectCount( objType ) : 0);		}

	// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
	BEMPropertyType*	getPropertyType( int i0PT, bool bCreateIfNext=false );
	bool insertPropertyType( int idx, BEMPropertyType** pPT )	{	bool bRetVal = false;
																						int iStartSz = (int) m_propTypes.size();
																						if (m_numPropTypes < (int) m_propTypes.size())  // inserting into array containing space @ the end
																						{	for (int i=m_numPropTypes-1; i>=idx; i--)
																								m_propTypes[i+1] = m_propTypes[i];
																							m_propTypes[idx] = *pPT;
																							bRetVal = true;
																						}
																						else
																						{	m_propTypes.insert( m_propTypes.begin()+idx, *pPT );  // grows array capacity
																							bRetVal = ((int) m_propTypes.size() > iStartSz);
																						}
																						if (bRetVal)
																							m_numPropTypes++;
																						return bRetVal;  }

	int	getType()								{	return m_type;					}
	void	setType( int iT )						{	m_type = iT;		return;	}
	int	getNumClasses()						{	return m_classes.size();	}
	void	resizeClasses( int iSize )			{	m_classes.resize( iSize );	}
	// SAC 9/26/16 - m_propTypes vector to BEMPropertyType*
	int	getNumPropertyTypes()				{	return m_numPropTypes;  }		// was: m_propTypes.size();	}
	void	resizePropertyTypes( int iSize )	{	m_propTypes.resize( iSize );
															m_numPropTypes = std::min( m_numPropTypes, iSize );	}

	void	initSrcBEMProcObj()					{	m_srcBEMProcObj = NULL;		return;	}
	BEMProcObject*	getSrcBEMProcObj()		{	return m_srcBEMProcObj;	 }

	bool	isUIActive()					{	return m_uiActive;  }
	void	setUIActive( bool bAct)		{	m_uiActive = bAct;  }

   QString					getBEMProcFileName()						{	return m_binFileName;  }

	QString					getCurrentRuleFile()						{	return m_currentRuleFile;			}
	void						setCurrentRuleFile( QString str )	{	m_currentRuleFile = str;			}
	BEM_PropertyStatus	getCurrentRuleFileStatus()				{	return m_currentRuleFileStatus;	}
	void						setCurrentRuleFileStatus( BEM_PropertyStatus stat )	{	m_currentRuleFileStatus = stat;	}
	
// Attributes
private:
   int              m_type;
   QString          m_binFileName;
   bool             m_uiActive; 		// SAC 9/26/16

   //int              m_numClassesAlloc;
   //int              m_numClasses;
   std::vector<BEMClass>  m_classes;		// was:  CBEMClass* m_classes;

   int              m_numPropTypes;    // # valid, loaded PropTypes
   std::vector<BEMPropertyType*>  m_propTypes;		// was:  CArray<CBEMPropertyType*, CBEMPropertyType*> m_propTypes;

//   CDWordArray      m_symbolsNotToOverwrite;  - not needed ??

   QString           m_currentRuleFile;
   BEM_PropertyStatus m_currentRuleFileStatus;

	int			m_numRuns;
	BEMRun		m_runs[ BEMRun_MaxNumRuns ];

	BEMProcObject*	m_srcBEMProcObj;		// SAC 4/30/15 - added to fix bug where mapped objects across copied BEMProcs where copies are not incremental was causing problems
};


// THE BEMProc object
extern BEMProcObject eBEMProc;
extern int eNumBEMProcsLoaded;
extern int eActiveBEMProcIdx;
extern BEMProcObject* epBEMProcs[BEMPROC_MAXMODELS];

extern BEMProcObject* getBEMProcPointer( int iBEMProcIdx );
extern int getBEMProcIndex( BEMProcObject* pBEMProcObj );
extern void blastSecondaryBEMProcs();

extern bool eShuttingDown;
extern bool eDeletingAllObjects;

extern long BEMP_GetDBParameterID( QString& sInputParam, long iCompID );
extern int  BEMP_GetDBComponentID( QString& sDBComp );
extern int  BEMP_GetClassIndexByLongName( QString& sName );
extern int  BEMP_GetPropertyTypeIndexByName( int i1Class, QString& sName, int iBEMProcIdx=-1 );
extern void ResetCurrentParentPointers( BEMObject* pCurParObj, int i1BEMClass, int iBEMProcIdx=-1 );
extern int CountObjectAssignments( BEMObject* pObj, bool bCheckMaxRefs, bool bStopAfterFirst, bool bCheckUserRefLibObjs,
												bool bTreeCtrlCall, bool bCopyDupRefs, int iBEMProcIdx, bool bResetAllRefs );

//extern BEMSymbolList* InitSymbolList( LPCSTR lpszDepVar, int iSource=BEMS_ProgDefault );
extern BEMSymbolList* GetSymbolList( long lDBID, BOOL* pbSymListArrayDependent=NULL );	// SAC 1/31/01 - Added pbSymListArrayDependent argument to pass back info on whether or not symbol list is array-index-dependent
extern QString GetSymbolStringFromPtrs( long iSymVal, BEMObject* pObj, BEMProperty* pProp, int iBEMProcIdx=-1 );

/////////////////////////////////////////////////////////////////////////////

// Default Class IDs
extern int eDefClassProj;

// Default Project
extern long eDefDBIDProjRuleset;
extern long eDefDBIDProjRuleFile;
extern long eDefDBIDProjCreateDate;
extern long eDefDBIDProjUniqueAssignFlag;
extern long eDefDBIDProjRemoveDupsFlag;

extern bool eDefaultIDsSet;
extern bool eReportedDefaultIDsSetError;

extern bool LoadDefaultIDs();

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMPROCOBJECT_H__
