// rulelist.h - header file for all the ruleset class definitions
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#ifndef __RULELIST_H__
#define __RULELIST_H__

#include "expCrypFile.h"
#include "expTextIO.h"
#include "expTable.h"
#include "expDataType.h"
#include "expRanges.h"
#include "expSymbols.h"
//#include "MaxChild.h"
#include "expReset.h"
//#include "UniqAssn.h"
#include "expRulePropTypeMod.h"
#include "BEMProc.h"

#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o

#define  MAX_NUM_INDIRECTIONS  10   // SAC 6/22/12 - 7->10

// --------------
// from RulExp.h
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "expFormula.h"

#ifdef _WIN64
#define MAXEXPLEN 36864   /* SAC 2/25/19 - increased by 50% for 64-bit */
#else
#define MAXEXPLEN 24576   /* SAC 4/21/17 - increased by 50% due to ExpNode mods | SAC 9/23/99 - Doubled MAXEXPLEN to make up for float -> double node conversion */
#endif

#ifdef __cplusplus
}
#endif
// --------------

// typedef UINT (FAR *PFRuleGetId)( const char *name );
// typedef void (FAR *PFRuleSetValue)( UINT id, float value );
// typedef bool (*PFGetBEMPVar)( const char *name, int* type, void* data, long compID = -1 );

class Rule;  // SAC 8/6/10 - declare before referencing in ExpEvalStruct

/* structure to be passed around which contains expression evaluation info */
typedef struct
{
   long lPrimDBID;
   int  iPrimObjIdx;
   BEM_ObjType ePrimObjType;
   int  iPrimPar1Class;
   int  iPrimParObjIdx;
   BEM_ObjType ePrimParObjType;

// SAC 1/5/99 - added to provide Parent2(Ref)() and Parent3(Ref)() functionality
   int  iPrimPar2Class;
   int  iPrimPar2ObjIdx;
   BEM_ObjType ePrimPar2ObjType;
   int  iPrimPar3Class;
   int  iPrimPar3ObjIdx;
   BEM_ObjType ePrimPar3ObjType;

   long lLocDBID;
   int  iLocObjIdx;
   BEM_ObjType eLocObjType;
   BEM_PropertyStatus eLocStatus;

// SAC 3/20/99 - added to provide post-eval rulelist evaluation via EvalRulelist(), Create*() and Delete*()
   QString sRulelistToEvaluate;
// SAC 3/24/99 - added to allow the Create*() functions to tell BEMPX_SetBEMData() to assign a BEMO_User vs. BEMO_RuleLib component
   BEM_ObjType eNewObjType;
// SAC 3/10/13 - added to cause rule library imports to create new objects with each RuleLib evaluation (as opposed to importing only once and providing multiple references to the single imported object)
   //BOOL 			bImportUniqueRuleLibObjects;
   int 			iImportUniqueRuleLibObjOption;	// SAC 4/25/14 - switched from BOOL (abv) to int: 0-ImportOnlyIfUnique / 1-ImportAlways / 2-EnsureLibraryName (new DEFAULT setting)

   QString		sImportRuleLibParentName;  // SAC 3/17/13 - name of parent of rule lib object to import

// SAC 5/26/00 - added to enable evaluated rulelist to only operate on certain BEMProc components
   int         iRulelistEvalClass;
   BEM_ObjType  eRulelistEvalObjType;
   std::vector<int>  maRulelistEvalObjIdxs;

// SAC 9/25/02 - Added to facilitate verbose output for debugging purposes
   BOOL        bVerboseOutput;

// SAC 2/5/06 - Added members to keep track of components deleted during evaluation of the current rule
   std::vector<int>  maDeletedClassIDs;
   std::vector<int>  maDeletedObjIdxs;

// SAC 10/29/07 - added to facilitate centralized BEMProc data setting (w/ error reporting)
   QString  sRuleID;

// SAC 8/5/10 - added to enable targeted verbose debug output
   BEMCompNameTypePropArray* pTargetedDebugInfo;
   int iNumTargetedDebugItems;
   BOOL bEvalItemADebugTarget;
   BOOL bRuleIDLogged;
   Rule* pRuleBeingEvaled;
   QString sRuleListName;

// SAC 10/12/11 - facilitates nested rule evaluation counting
   long* plRuleEvalCount;
} ExpEvalStruct;

extern void CopyExpEvalStruct( ExpEvalStruct* pDest, ExpEvalStruct* pSrc );   // SAC 10/29/07


/////////////////////////////////////////////////////////////////////////////
//	Rule
//    An instance of this class is present for each individual compliance
//    rule defined in a ruleset.
/////////////////////////////////////////////////////////////////////////////

class Rule
{
public:
   Rule();
   Rule( QString& sRuleID, QString& sDbID, QString& sExp, int iNumIndirections=1, long* plDBIDs=NULL,
				int i1RuleFileIdx=0, int iRuleLineNum=0,     // SAC 4/10/13 - added to aid in debugging
				int iNumAncestors=0, int* piAncestorObjTypes=NULL );  // SAC 4/11/13 - added ancestor object type index initialization
   ~Rule();
   bool ParseLeft( QFile& errorFile );
   void ThrowBEMPError( QFile& errorFile, QString sParam );
   bool Write( CryptoFile& file, QFile& errorFile, const char* pszRLName = NULL );
	bool Parse( QFile& errorFile, const char* pszRLName = NULL );  // SAC 1/29/18

   void Read( CryptoFile& file );
   bool Eval( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined=FALSE, BOOL bPerformSetBEMDataResets=TRUE );  // SAC 9/18/05 - added bPerformSetBEMDataResets argument to facilitate no-reset data setting

	QString	getID()									{	return m_id;	}
//	void		setID( QString& str )				{	m_id = str;		}
//	void		setID( const char* pszStr )		{	m_id = pszStr;		}
	QString	getDBID()								{	return m_dbId;	}
//	void		setDBID( QString& str )				{	m_dbId = str;		}
//	void		setDBID( const char* pszStr )		{	m_dbId = pszStr;		}
	long		getDatabaseID( int idx )					{	return ((idx>=0 && idx<MAX_NUM_INDIRECTIONS) ? m_databaseID[idx] : -1);	}
//	void		setDatabaseID( int idx, long lDBID )	{	if (idx>=0 && idx<MAX_NUM_INDIRECTIONS)
//																			m_databaseID[idx] = lDBID;		}
	int		getNumIndirections()								{	return m_numIndirections;	}
	int		getAncestorObjType( int idx )					{	return ((idx>=0 && idx<MAX_NUM_INDIRECTIONS) ? m_ancestorObjTypes[idx] : -1);	}
//	void		setAncestorObjType( int idx, int lAT )		{	if (idx>=0 && idx<MAX_NUM_INDIRECTIONS)
//																				m_ancestorObjTypes[idx] = iAT;		}

private:
   QString	m_id;               // character string ID of the rule
   QString	m_dbId;             // left portion of rule expression
   QString	m_textExpression;    // right portion of rule expression
	int		m_1RuleFileIdx;		// SAC 4/10/13 - added to aid in debugging
	int		m_ruleLineNum;

   int		m_numIndirections;                     // # of database IDs stored in the following array
   long		m_databaseID[ MAX_NUM_INDIRECTIONS ];  // DBIDs used to determine what data in database to set
   int		m_ancestorObjTypes[ MAX_NUM_INDIRECTIONS ];  // 1-based object type indexes of ancestors of object to be evaluated by rule
   ParsedExpression m_parsedExpression;            // parsed rule expression
};

extern bool ParseRuleDBID( QString& sRuleID, QString& sDBID, int& iNumIndirections, long* plDBIDs, QFile& errorFile );


/////////////////////////////////////////////////////////////////////////////
//	RuleList
//    An instance of this class is created for each list of rules contained
//    in the compliance ruleset
/////////////////////////////////////////////////////////////////////////////

class RuleList
{
public:
   RuleList();
// SAC 5/26/03 - added int iLineNumber & const char* pszFileName arguments
   RuleList( LPCSTR name, bool bSetAllData=TRUE, bool bAllowMultipleEvaluations=TRUE, bool bTagAllDataAsUserDefined=FALSE,
              int iLineNumber=0, const char* pszFileName=NULL, bool bPerformSetBEMDataResets=TRUE );  // SAC 9/18/05 - added to facilitate no-reset data setting
   ~RuleList();

   bool Write( CryptoFile& file, QFile& errorFile );
   bool Parse( QFile& errorFile );  // SAC 1/29/18
   void Read( CryptoFile& file, int iFileStructVer=1 );
   void RemoveAll();

   void  addRule( Rule* pRule )	{	m_rules.push_back( pRule );  }
   Rule* getRule( QString& name );
   Rule* getRule( int idx )		{	return m_rules.at(idx);  }
   int   getRuleCount()				{	return (int) m_rules.size();   }

	QString	getName()								{	return m_name;	}
//	void		setName( QString& str )				{	m_name = str;		}
//	void		setName( const char* pszStr )		{	m_name = pszStr;		}
	bool		getSetAllData()						{	return m_setAllData;	}
	bool		getAllowMultipleEvaluations()		{	return m_allowMultipleEvaluations;	}
	bool		getTagAllDataAsUserDefined()		{	return m_tagAllDataAsUserDefined;	}
	bool		getPerformSetBEMDataResets()		{	return m_performSetBEMDataResets;	}

   int   	getLineNumber()						{	return m_lineNumber;   }
	QString	getFileName()							{	return m_fileName;	}

private:
   std::vector<Rule*>  m_rules;
   QString	m_name;  // name of this rulelist
   bool		m_setAllData;
   bool		m_allowMultipleEvaluations;
   bool		m_tagAllDataAsUserDefined;
   bool		m_performSetBEMDataResets;  // SAC 9/18/05 - added to facilitate no-reset data setting

   int		m_lineNumber;  // SAC 5/26/03 - Added to enable reporting of rulelist line number & filename in compiler output
   QString	m_fileName;
};


/////////////////////////////////////////////////////////////////////////////
//	RuleListList
//    An instance of this class is created for each compliance ruleset and
//    contains the list of complaince rulelists
/////////////////////////////////////////////////////////////////////////////

class RuleListList
{
public: 
   void NewList( LPCSTR name, bool bSetAllData=TRUE, bool bAllowMultipleEvaluations=TRUE, bool bTagAllDataAsUserDefined=FALSE,
                 int iLineNumber=0, const char* pszFileName=NULL, bool bPerformSetBEMDataResets=TRUE );  // SAC 9/18/05
   void RemoveAll();
	void RemoveTrailing( int iNumListsToDelete=1 );
   RuleList* getRuleList( LPCSTR name );
   RuleList* getRuleList( int i )							{	return ((i>=0 && i<(int)m_rules.size()) ? m_rules.at(i) : NULL);  }
   bool IsFirstRuleList( RuleList* list );
   void AddRule( QString& sRuleID, QString& sDbID, QString& sExp, int i1RuleFileIdx=0, int iRuleLineNum=0 );  // SAC 11/7/13 - added rule file/line# args
   void InitRules();
   bool Write( CryptoFile& file, QFile& errorFile );
   void Read( CryptoFile& file, int iFileStructVer=1 );
   bool EvalListDuringEval( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined=FALSE );  // SAC 8/6/10 - added to make mid-eval rulelist evals more convenient
   bool EvalList( LPCSTR listName, BOOL bTagDataAsUserDefined=FALSE,
                  int iEvalOnlyClass=0, BEM_ObjType eEvalOnlyObjType=BEMO_User,  // SAC 5/26/00
                  std::vector<int>* piaEvalOnlyObjs=NULL,   // SAC 5/26/00
                  BOOL bVerboseOutput=FALSE,          // SAC 9/25/02
                  BEMCompNameTypePropArray* pTargetedDebugInfo=NULL,    // SAC 8/5/10 - added pvTargetedDebugInfo argument
						long* plRuleEvalCount=NULL,         // SAC 10/12/11 - to facilitate summing of each individual rule evaluation
						QStringList* psaWarningMsgs=NULL );		// SAC 3/2/18 - added to enable Warning message tracking during normal list evaluation

// SAC 5/21/01 - Added function similar to EvalList(), only the rules therein are designed to populate the error and warning message lists
   bool EvalErrorCheckList( LPCSTR listName, QStringList& saErrorMsgs, QStringList& saWarningMsgs,
                            int iEvalOnlyClass=0, int iEvalOnlyOccur=-1 );

   int  getNumRuleLists()		{	return (int) m_rules.size();  }
   int  getRulelistNames( QVector<QString>& sRulelistNames );

   long getNestedListEvalCount()			{	return m_iNestedListEvalCount;		};
   long getPeakNestedListEvalCount()	{	return m_iPeakNestedListEvalCount;	};
   long getMaxNestedListEvalCount()		{	return m_iMaxNestedListEvalCount;	};
   void setMaxNestedListEvalCount( long lMaxNLEC )		{	m_iMaxNestedListEvalCount = lMaxNLEC;	return;	};

   bool getAbortRuleEvaluation()										{	return m_bAbortRuleEvaluation;	};
   void setAbortRuleEvaluationFlag( bool bAbortRuleEval )	{	m_bAbortRuleEvaluation = bAbortRuleEval;	return;	};

private:
   std::vector<RuleList*>  m_rules;
   int   m_currentList;   // the index of the "current" rulelist
	long  m_iNestedListEvalCount;  // SAC 8/6/13 - added to prevent recursive rulelist evaluations from bombing system
	long  m_iPeakNestedListEvalCount;
	long  m_iMaxNestedListEvalCount;
	bool  m_bAbortRuleEvaluation;		// SAC 8/6/13 - flag to abort rule evaluation when critical errors occur
};


/////////////////////////////////////////////////////////////////////////////
//	RuleSetTransformation
//    An instance of this class is created for each building model transformation associated w/ a ruleset.
/////////////////////////////////////////////////////////////////////////////

#define  TransShortName_MaxLen  3		// SAC 3/29/14 - added to avoid unnecessary string comparisons

class RuleSetTransformation
{
public:
   RuleSetTransformation();
   RuleSetTransformation( QString& sLongName, QString& sShortName, QString& sRulelistName, int iBEMProcIdxToCopy=-1 );
   ~RuleSetTransformation();

public:
   bool Write( CryptoFile& file );
   void Read( CryptoFile& file, int iFileStructVer=1 );
   bool LongGroupNameMatch(  const char* pszChk );
   bool LongGroupNameMatch(  QString& sChk );
   bool ShortGroupNameMatch( const char* pszChk );
   bool ShortGroupNameMatch( QString& sChk );

	int		getBEMProcIdxToCopy()									{	return m_BEMProcIdxToCopy;		}
	void		setBEMProcIdxToCopy( int iBEMProcIdxToCopy )		{	m_BEMProcIdxToCopy = iBEMProcIdxToCopy;	}
	QString	getLongName()									{	return m_longName;	}
//	void		setLongName( QString& str )				{	m_longName = str;		}
//	void		setLongName( const char* pszStr )		{	m_longName = pszStr;		}
	QString	getShortName()									{	return m_shortName;	}
//	void		setShortName( QString& str )				{	m_shortName = str;		}
//	void		setShortName( const char* pszStr )		{	m_shortName = pszStr;		}
	QString	getRuleListName()									{	return m_rulelistName;	}
//	void		setRuleListName( QString& str )				{	m_rulelistName = str;		}
//	void		setRuleListName( const char* pszStr )		{	m_rulelistName = pszStr;		}
	int		numGroupLongNames()							{	return (int) m_groupLongName.size();  }
	QString	getGroupLongName(int i)						{	return m_groupLongName[i];  }
	void		addGroupLongName(QString& s)				{	m_groupLongName.push_back(s);  return;  }
	void		addGroupShortName(QString& s)				{	m_groupShortName.push_back(s);  return;  }

	int		getClassOrDBIDToExcludeSize()				{	return (int) m_objClassesOrDBIDsToExclude.size();  }
	long		getClassOrDBIDToExclude(int i)			{	assert( i>= 0 && i < (int) m_objClassesOrDBIDsToExclude.size() );
																		if (i>= 0 && i < (int) m_objClassesOrDBIDsToExclude.size())
																			return m_objClassesOrDBIDsToExclude[i];
																		return -1;  }
	void		addClassOrDBIDToExclude(long l)			{	m_objClassesOrDBIDsToExclude.push_back(l);  return;  }

private:
	QString		m_longName;
	QString		m_shortName;
	QStringList	m_groupLongName;		// SAC 3/27/14 -  added long & short Group names (to allow rule expressions to be specified once but inserted into multiple transforms)
	QStringList	m_groupShortName;				// SAC 8/20/15 - switched group names from single strings to arrays

	QString		m_rulelistName;

	int			m_BEMProcIdxToCopy;  // added to enable rule text-defined source model IDs (SAC 9/24/13)

   std::vector<long>	m_objClassesOrDBIDsToExclude;	// 1-based indexes of classes (or DBIDs that must evaluate to 1/TRUE) to EXCLUDE from this transformation (when copying objects over from a previous transform) (SAC 9/24/13)
};


/////////////////////////////////////////////////////////////////////////////
//	RuleSetProperty
//    An instance of this class is created for each ruleset variable (RULE NEW) in the ruleset, which
//		describe BEMBase properties nedding to be ADDED in order to process the rules of the ruleset.
/////////////////////////////////////////////////////////////////////////////

class RuleSetProperty
{
public:
   RuleSetProperty();
   RuleSetProperty( int iObjTypeID, int iPropID, QString& sPropName, QString& sPropNameLong, long lDBID,
							int iPropType=-1, int iPropTypeObjID=-1, int iReportPrec=-9 );  // SAC 1/30/13  // SAC 2/5/15
   ~RuleSetProperty();

public:
   bool Write( CryptoFile& file );
   void Read( CryptoFile& file, int iFileStructVer=1 );

	int		getObjTypeID()							{	return m_objTypeID;		}
//	void		setObjTypeID( int iObjTypeID )	{	m_objTypeID = iObjTypeID;	}
	int		getPropID()								{	return m_propID;		}
//	void		setPropID( int iPropID )			{	m_propID = iPropID;	}
	QString	getPropName()									{	return m_propName;	}
	void		setPropName( QString& str )				{	m_propName = str;		}
//	void		setPropName( const char* pszStr )		{	m_propName = pszStr;		}
	QString	getPropNameLong()								{	return m_propNameLong;	}
	void		setPropNameLong( QString& str )			{	m_propNameLong = str;		}
//	void		setPropNameLong( const char* pszStr )	{	m_propNameLong = pszStr;		}
	long		getDBID()								{	return m_dbid;		}
//	void		setDBID( long lDBID )				{	m_dbid = lDBID;	}
	int		getPropType()							{	return m_propType;		}
	void		setPropType( int iPropType )		{	m_propType = iPropType;	}
	int		getPropTypeObjID()								{	return m_propTypeObjID;		}
	void		setPropTypeObjID( int iPropTypeObjID )		{	m_propTypeObjID = iPropTypeObjID;	}
	QString	getUnits()								{	return m_units;	}
	void		setUnits( QString& str )			{	m_units = str;		}
//	void		setUnits( const char* pszStr )	{	m_units = pszStr;		}
	int		getReportPrecision()								{	return m_reportPrecision;		}
	void		setReportPrecision( int iReportPrec )		{	m_reportPrecision = iReportPrec;	}

private:
	int		m_objTypeID;
	int		m_propID;
	QString	m_propName;
	QString	m_propNameLong;  // SAC 1/30/13
	long		m_dbid;
	int		m_propType;
	int		m_propTypeObjID;  // SAC 1/30/13
	QString	m_units;  // SAC 8/6/14
	int		m_reportPrecision;	// SAC 2/5/15
};


/////////////////////////////////////////////////////////////////////////////
//	RuleToolTip
//    An instance of this class is created for each rule that contains HELP or
//    DESCRIPTION text
/////////////////////////////////////////////////////////////////////////////

class RuleToolTip
{
public:
   RuleToolTip();
   RuleToolTip( QString sToolTip, int iNumIndirections=1, long* plDBIDs=NULL,
						int iNumAncestors=0, int* piAncestorObjTypes=NULL );
   ~RuleToolTip();

public:
   bool Write( CryptoFile& file );
   void Read( CryptoFile& file, int iFileStructVer=1 );

	long		getDBID( int i=0 )	{	if (i >= 0 && i < MAX_NUM_INDIRECTIONS)
													return m_databaseID[i];
												return -1;  }
	QString	getString()				{	return m_toolTip;  }

private:
	QString	m_toolTip;
   int		m_numIndirections;                     // # of database IDs stored in the following array
   long		m_databaseID[ MAX_NUM_INDIRECTIONS ];  // DBIDs used to determine what data in database to set
   int		m_ancestorObjTypes[ MAX_NUM_INDIRECTIONS ];  // 1-based object type indexes of ancestors of object to be evaluated by rule
};


/////////////////////////////////////////////////////////////////////////////

class GeomDBIDs
{
public:
	bool	m_bIDInitAttempted;
	bool	m_bIDsOK;

	int 	m_iOID_Story;  // SAC 11/27/13 - added to facilitate footprint SVG export

	int 	m_iOID_Spc;                            			// Typ  NV   US     UL     NO    OC            CV  CP        LName                 
   //long  m_lDBID_Spc_PlenumSpcRef;              			// Obj,  1,  Opt,   "",     1,  "Space",   4, "CondgType",  "PlenumSpaceReference"            
   //long  m_lDBID_Spc_ThrmlZnRef;                			// Obj,  1,  Req,   "",     1,  "ThrmlZn",     0, "",       "ThermalZoneReference"            
   long  m_lDBID_Spc_FlrArea;                   			// Flt,  1,  Req,   "ft2",  0,                              "FloorArea"                  
   long  m_lDBID_Spc_FlrToCeilingHgt;           			// Flt,  1,  Req,   "ft",   0,                              "FloorToCeilingHeight"                  
   long  m_lDBID_Spc_SkylitDaylitArea;          			// Flt,  1,  NInp,  "ft2",  0,                              "SkylitDaylitArea"
   long  m_lDBID_Spc_PriSideDaylitArea;         			// Flt,  1,  NInp,  "ft2",  0,                              "PrimarySideDaylitArea" 
   long  m_lDBID_Spc_SecSideDaylitArea;         			// Flt,  1,  NInp,  "ft2",  0,                              "SecondarySideDaylitArea" 
   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordX;    	// Flt,  1,  NInp,  "ft",   0,                              "SkylitDaylightingReferencePointCoordinateX" 
   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordY;    	// Flt,  1,  NInp,  "ft",   0,                              "SkylitDaylightingReferencePointCoordinateY" 
   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordX;   	// Flt,  1,  NInp,  "ft",   0,                              "PrimarySideDaylightingReferencePointCoordinateX" 
   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordY;   	// Flt,  1,  NInp,  "ft",   0,                              "PrimarySideDaylightingReferencePointCoordinateY" 
   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordX;   	// Flt,  1,  NInp,  "ft",   0,                              "SecondarySideDaylightingReferencePointCoordinateX" 
   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordY;   	// Flt,  1,  NInp,  "ft",   0,                              "SecondarySideDaylightingReferencePointCoordinateY" 
   //long  m_lDBID_Spc_SkylitDayltgCtrlRef;       			// Obj,  1,  Opt,   "",     1,  "DayltgCtrl",   0, "",      "SkylitDaylightingControlReference" 
   //long  m_lDBID_Spc_PriSideDayltgCtrlRef;      			// Obj,  1,  Opt,   "",     1,  "DayltgCtrl",   0, "",      "PrimarySideDaylightingControlReference" 
   //long  m_lDBID_Spc_SecSideDayltgCtrlRef;      			// Obj,  1,  Opt,   "",     1,  "DayltgCtrl",   0, "",      "SecondarySideDaylightingControlReference" 
   long  m_lDBID_Spc_SrcVarSkylitDaylitArea;             // Flt,  1,  NInp,  "ft2",  0,                              "SkylitDaylitArea" 
   long  m_lDBID_Spc_SrcVarPriSideDaylitArea;            // Flt,  1,  NInp,  "ft2",  0,                              "PriSideDaylitArea" 
   long  m_lDBID_Spc_SrcVarSecSideDaylitArea;            // Flt,  1,  NInp,  "ft2",  0,                              "SecSideDaylitArea" 
   long  m_lDBID_Spc_SrcVarSkylitRDP;                 	// Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
   long  m_lDBID_Spc_SrcVarPriSideRDP;                	// Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
   long  m_lDBID_Spc_SrcVarSecSideRDP;                	// Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
   long  m_lDBID_Spc_SkylitRDPCoefs;            			// Flt,  2,  NInp, "",                                      "SkylitRelativeDaylightPotentialCoefficients"
   long  m_lDBID_Spc_PriSideRDPCoefs;           			// Flt,  3,  NInp, "",                                      "SkylitRelativeDaylightPotentialCoefficients"
   long  m_lDBID_Spc_SecSideRDPCoefs;           			// Flt,  3,  NInp, "",                                      "SkylitRelativeDaylightPotentialCoefficients"
   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtEffAp;     	// Flt,  1,  NInp, "",                                      "SkylitDaylightingReferencePointEffectiveAperture" 
   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtSrcOrient; 	// Flt,  1,  NInp, "deg",                                   "SkylitDaylightingReferencePointSourceOrientation" 
   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtEffAp;    	// Flt,  1,  NInp, "",                                      "PrimarySideDaylightingReferencePointEffectiveAperture" 
   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtSrcOrient;	// Flt,  1,  NInp, "deg",                                   "PrimarySideDaylightingReferencePointSourceOrientation" 
   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtEffAp;    	// Flt,  1,  NInp, "",                                      "SecondarySideDaylightingReferencePointEffectiveAperture" 
   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtSrcOrient;	// Flt,  1,  NInp, "deg",                                   "SecondarySideDaylightingReferencePointSourceOrientation" 

   int   m_iOID_ExtWall;
   long  m_lDBID_ExtWall_Az;            			// Flt,  1,  Opt,  "deg",                                   "Azimuth"     

   int   m_iOID_Roof;

   int   m_iOID_Win;                          // Typ  NV   US     UL     NO    OC            CV  CP         LName                 
   long  m_lDBID_Win_FenConsRef;              // Obj,  1,  Opt,  "",      1,  "FenCons",  1, "FenType",    "FenestrationConstructionReference"
   long  m_lDBID_Win_Area;                    // Flt,  1,  Opt,  "ft2",   0,                               "Area"     
   long  m_lDBID_Win_AllowWinShades;          // Int,  1,  Opt,  "",      0,                               "EnableWindowShades",  "" 
   long  m_lDBID_Win_EnableWinShades;         // Int,  1,  Opt,  "",      0,                               "EnableWindowShades",  "" 
   long  m_lDBID_Win_OverhangDepth;           // Flt,  1,  Opt,  "ft",    0,                               "OverhangDepth",  ""
   long  m_lDBID_Win_OverhangDistance;        // Flt,  1,  Opt,  "ft",    0,                               "OverhangDistance",   ""
   long  m_lDBID_Win_OverhangLeftExtension;   // Flt,  1,  Opt,  "ft",    0,                               "OverhangLeftExtension",  ""
   long  m_lDBID_Win_OverhangRightExtension;  // Flt,  1,  Opt,  "ft",    0,                               "OverhangRightExtension",  ""
   long  m_lDBID_Win_OverhangAngle;           // Flt,  1,  Opt,  "deg",   0,                               "OverhangAngle",   ""
   long  m_lDBID_Win_OverhangTransOption;     // Sym,  1,  Opt,  "",      0,                               "OverhangTransmittanceOption",   ""
   long  m_lDBID_Win_OverhangTrans;           // Flt,  1,  Opt,  "frac.", 0,                               "OverhangTransmittance",   ""
   long  m_lDBID_Win_OverhangTransSchRef;     // Obj,  1,  Opt,  "",      1, "Sch",  1, "Type",            "OverhangTransmittanceScheduleReference",   ""
   long  m_lDBID_Win_LeftFinDepth;            // Flt,  1,  Opt,  "ft",    0,                               "LeftFinDepth",  ""
   long  m_lDBID_Win_LeftFinDistance;         // Flt,  1,  Opt,  "ft",    0,                               "LeftFinDistance",   ""
   long  m_lDBID_Win_LeftFinDistanceAbove;    // Flt,  1,  Opt,  "ft",    0,                               "LeftFinDistanceAbove",  ""
   long  m_lDBID_Win_LeftFinDistanceBelow;    // Flt,  1,  Opt,  "ft",    0,                               "LeftFinDistanceBelow",  ""
   long  m_lDBID_Win_LeftFinAngle;            // Flt,  1,  Opt,  "deg",   0,                               "LeftFinAngle",   ""
   long  m_lDBID_Win_LeftFinTransOption;      // Sym,  1,  Opt,  "",      0,                               "LeftFinTransmittanceOption",   ""
   long  m_lDBID_Win_LeftFinTrans;            // Flt,  1,  Opt,  "frac.", 0,                               "LeftFinTransmittance",   ""
   long  m_lDBID_Win_LeftFinTransSchRef;      // Obj,  1,  Opt,  "",      1, "Sch",  1, "Type",            "LeftFinTransmittanceScheduleReference",   ""
   long  m_lDBID_Win_RightFinDepth;           // Flt,  1,  Opt,  "ft",    0,                               "RightFinDepth",  ""
   long  m_lDBID_Win_RightFinDistance;        // Flt,  1,  Opt,  "ft",    0,                               "RightFinDistance",   ""
   long  m_lDBID_Win_RightFinDistanceAbove;   // Flt,  1,  Opt,  "ft",    0,                               "RightFinDistanceAbove",  ""
   long  m_lDBID_Win_RightFinDistanceBelow;   // Flt,  1,  Opt,  "ft",    0,                               "RightFinDistanceBelow",  ""
   long  m_lDBID_Win_RightFinAngle;           // Flt,  1,  Opt,  "deg",   0,                               "RightFinAngle",   ""
   long  m_lDBID_Win_DisableDayltgImpact;     // Int,  1,  - RuleNew added for 2019 analysis - SAC 7/29/18

   int   m_iOID_Skylt;               // Typ  NV   US     UL     NO    OC            CV  CP         LName                 
   long  m_lDBID_Skylt_FenConsRef;   // Obj,  1,  Opt,  "",      1, "FenCons",     2, "FenType",  "FenestrationConstructionReference"
   long  m_lDBID_Skylt_Area;         // Flt,  1,  Opt,  "ft2",   0,                               "Area"     
   long  m_lDBID_Skylt_DisableDayltgImpact;   // Int,  1,  - RuleNew added for 2019 analysis - SAC 7/29/18

   int   m_iOID_PolyLp;                 // Typ  NV   US     UL     NO     LName                 
   long  m_lDBID_PolyLp_Area;           // Flt,  1,  NInp, "ft2",   0,   "Area"            
   long  m_lDBID_PolyLp_NumOfPts;       // Int,  1,  NInp, "",      0,   "NumberOfPoints"
   long  m_lDBID_PolyLp_ParentInfrm;    // Str,  1,  NInp, "",      0,   "ParentInformation"
   long  m_lDBID_PolyLp_XYLen;          // Flt,  1,  NInp, "ft",    0,   "XYLength"        
   long  m_lDBID_PolyLp_Perim;          // Flt,  1,  NInp, "ft",    0,   "Perimeter"        		- SAC 6/5/15
   long  m_lDBID_PolyLp_ZBottom;        // Flt,  1,  NInp, "ft",    0,   "ZBottom"         
   long  m_lDBID_PolyLp_ZTop;           // Flt,  1,  NInp, "ft",    0,   "ZTop"            
   long  m_lDBID_PolyLp_ZHgt;           // Flt,  1,  NInp, "ft",    0,   "ZHeight"         
   long  m_lDBID_PolyLp_ZRngMessage;    // Str,  1,  NInp, "",      0,   "ZRangeMessage"			- SAC 1/22/14 - added to enhance tree display for parent/child Z range verification
   long  m_lDBID_PolyLp_XCenter;        // Flt,  1,  NInp, "ft",    0,   "XCenter"         		- SAC 12/16/14 - added to facilitate window shades
   long  m_lDBID_PolyLp_YCenter;        // Flt,  1,  NInp, "ft",    0,   "YCenter"         
   long  m_lDBID_PolyLp_VectorOi;       // Flt,  1,  NInp, "ft",    0,   "VectorOi"        
   long  m_lDBID_PolyLp_VectorOj;       // Flt,  1,  NInp, "ft",    0,   "VectorOj"        
   long  m_lDBID_PolyLp_VectorOk;       // Flt,  1,  NInp, "ft",    0,   "VectorOk"        
   long  m_lDBID_PolyLp_VectorOLen;     // Flt,  1,  NInp, "ft",    0,   "VectorOLength"   
   long  m_lDBID_PolyLp_UnitVectorOi;   // Flt,  1,  NInp, "ft",    0,   "UnitVectorOi"    
   long  m_lDBID_PolyLp_UnitVectorOj;   // Flt,  1,  NInp, "ft",    0,   "UnitVectorOj"    
   long  m_lDBID_PolyLp_UnitVectorOk;   // Flt,  1,  NInp, "ft",    0,   "UnitVectorOk"    
   long  m_lDBID_PolyLp_VectorPLen;     // Flt,  1,  NInp, "ft",    0,   "VectorPLength"   
   long  m_lDBID_PolyLp_UnitVectorPi;   // Flt,  1,  NInp, "ft",    0,   "UnitVectorPi"    
   long  m_lDBID_PolyLp_UnitVectorPj;   // Flt,  1,  NInp, "ft",    0,   "UnitVectorPj"    
	long  m_lDBID_PolyLp_Azimuth;        // Flt,  1,  NInp, "deg"  SAC 7/12/18 - added w/ NO error checking (used when present)
	long  m_lDBID_PolyLp_TiltAngle;      // Flt,  1,  NInp, "deg"  

   int   m_iOID_CartesianPt;         // Typ  NV   US     UL     NO    OC   CV   CP    LName                 
   long  m_lDBID_CartesianPt_Coord;  // Flt,  3,  Opt,  "ft",    0,                  "Coordinate"		; "X, Y, Z coordinates of polyloop vertex" 

   int   m_iOID_FenCons;             // Typ  NV   US     UL     NO    OC   CV   CP    LName                 
   long  m_lDBID_FenCons_VT;         // Flt,  1,  Req,  "",      0,                  "VisibleTransmittance"               

//   int   m_iOID_DayltgCtrl;                    // Typ  NV   US     UL     NO    OC   CV   CP    LName                 
//   long  m_lDBID_DayltgCtrlDayltgCtrlType;     // Sym,  1,  Req,  "",      0,                  "DaylightingControlType"
//   long  m_lDBID_DayltgCtrlDaylitAreaType;     // Sym,  1,  Req,  "",      0,                  "DaylitAreaType"
//   long  m_lDBID_DayltgCtrlDaylitArea;         // Flt,  1,  Req,  "ft2",   0,                  "DaylitArea"
//   long  m_lDBID_DayltgCtrlIllumRefPtCoord;    // Flt,  3,  Req,  "ft",    0,                  "IlluminanceReferencePointCoordinate"
//   long  m_lDBID_DayltgCtrlDayltgCtrlLtgFrac;  // Flt,  1,  Req,  "",      0,                  "DaylightingControlLightingFraction"
//   long  m_lDBID_DayltgCtrlMinDimLtgFrac;      // Flt,  1,  Opt,  "",      0,                  "MinimumDimmingLightFraction"
//   long  m_lDBID_DayltgCtrlMinDimPwrFrac;      // Flt,  1,  Opt,  "",      0,                  "MinimumDimmingPowerFraction"
//   long  m_lDBID_DayltgCtrlNumOfCtrlSteps;     // Int,  1,  Opt,  "",      0,                  "NumberOfControlSteps"
//   long  m_lDBID_DayltgCtrlIllumSetPt;         // Flt,  1,  Req,  "lux",   0,                  "IlluminanceSetPoint"
//   long  m_lDBID_DayltgCtrlIllumSetPtAdjFac;   // Flt,  1,  NInp, "",      0,                  "IlluminanceSetPointAdjustmentFactor"
//   long  m_lDBID_DayltgCtrlAdjIllumSetPt;      // Flt,  1,  NInp, "lux",   0,                  "AdjustedIlluminanceSetPoint"
//   long  m_lDBID_DayltgCtrlGlrAz;              // Flt,  1,  Req,  "",      0,                  "GlareAzimuth"
//   long  m_lDBID_DayltgCtrlMaxGlrIdx;          // Flt,  1,  Req,  "",      0,                  "MaximumGlareIndex"

public:
   GeomDBIDs()	{	Clear();		};

	void	Clear()	{	m_bIDInitAttempted = false;
							m_bIDsOK = false;		};
	bool	Init( ExpEvalStruct* pEval, ExpError* error );
	bool	Init( QString& sErrMsg );	// SAC 2/25/14 - added to facilitate calling from compliance manager
};

extern double CalcDaylighting( int iDayltMethod, int iSpcObjIdx, const char* pszSpcName, ExpEvalStruct* pEval, ExpError* pError );
extern double InitPolyLoop( int iPolyLpObjIdx, ExpEvalStruct* pEval, ExpError* pError );


/////////////////////////////////////////////////////////////////////////////
//	RuleSet
//    An instance of this class is created for each compliance ruleset.
/////////////////////////////////////////////////////////////////////////////

#define  NUM_RULE_EXPORTFILES  20   // SAC 9/15/15

class RuleSet
{
public:
   RuleSet()				{	initMembers();  }
   ~RuleSet()				{	clear();  }

	void initMembers();
   void clear();

public:
	BOOL  IsProcedural()	{	return (m_iRulesetOrganization == RULESETORG_PROCEDURAL);  };
	BOOL  IsDataModel()	{	return (m_iRulesetOrganization == RULESETORG_DATAMODEL );  };
	bool  DataModelRuleActive()	{	return m_bDataModelRuleActive;  };		// SAC 5/26/16
	int   LabelIndex( QString& sLabel, BOOL bCaseSensitive=FALSE );	// SAC 9/9/14	// SAC 12/19/17 - switched from BOOL LabelMatches() to int LabelIndex() to return 1-based label index (0 if not found)
	int   NumRulesetPropertiesForObject( int iObjTypeID );
	BOOL	PostRulePropsToDatabase( QString& sErrantRuleProps, int iDefaultInputClass=-1 );
   QString  GetBEMBaseFile()		{	return m_sBEMBaseFile;	}

	int   getFileStructVersion()				{	return m_iFileStructVersion;  }
	void  setFileStructVersion(int i)		{	m_iFileStructVersion = i;  return;  }
	void  setRulesetOrganization(int i)		{  m_iRulesetOrganization = i;  return;  }
	int   getRulesetOrganization()			{  return m_iRulesetOrganization;  }
	void  setDataModelRuleActive(bool b)	{	m_bDataModelRuleActive = b;  return;  }
	void  setSimulateDBID(long l)				{	m_lSimulateDBID = l;  return;  }
	long  getSimulateDBID()						{	return m_lSimulateDBID;  }

	void		setRuleSetID(QString& s)			{	m_sRuleSetID = s;  return;  }
	QString	getRuleSetID()							{	return m_sRuleSetID;  }
	void		setRuleSetVersion(QString& s)		{	m_sRuleSetVersion = s;  return;  }
	QString	getRuleSetVersion()					{	return m_sRuleSetVersion;  }
	void		setBEMBaseFile(QString& s)			{	m_sBEMBaseFile = s;  return;  }
	QString	getBEMBaseFile()						{	return m_sBEMBaseFile;  }
	void		setScreensFile(QString& s)			{	m_sScreensFile = s;  return;  }
	QString	getScreensFile()						{	return m_sScreensFile;  }
	void		setToolTipsFile(QString& s)		{	m_sToolTipsFile = s;  return;  }
	QString	getToolTipsFile()						{	return m_sToolTipsFile;  }

	int		getNumLabels()							{	return (int) m_saLabels.size();  }
	QString	getLabel(int i)						{	return ((i>=0 && i<m_saLabels.size()) ? m_saLabels.at(i) : "");  }
	void		addLabel(QString& s)					{	m_saLabels.push_back( s );  return;  }

	QString	getErrorMessage( int idx )			{	assert( idx >= 0 && idx < m_saErrorMessages.count() );
																return (idx >= 0 && idx < m_saErrorMessages.count())     ? m_saErrorMessages[idx] : "";  }
	QString	getErrorPrimObjName( int idx )	{	assert( idx >= 0 && idx < m_saErrorPrimObjNames.count() );
																return (idx >= 0 && idx < m_saErrorPrimObjNames.count()) ? m_saErrorPrimObjNames[idx] : "";  }
	QString	getErrorLocObjName( int idx )		{	assert( idx >= 0 && idx < m_saErrorLocObjNames.count() );
																return (idx >= 0 && idx < m_saErrorLocObjNames.count())  ? m_saErrorLocObjNames[idx] : "";  }
	int		getErrorPrimObjClass( int idx )	{	assert( idx >= 0 && idx < (int) m_iaErrorPrimObjClass.size() );
																return (idx >= 0 && idx < (int) m_iaErrorPrimObjClass.size())  ? m_iaErrorPrimObjClass[idx] : -1;  }
	int		getErrorLocObjClass( int idx )	{	assert( idx >= 0 && idx < (int) m_iaErrorLocObjClass.size() );
																return (idx >= 0 && idx < (int) m_iaErrorLocObjClass.size())   ? m_iaErrorLocObjClass[idx] : -1;  }
	long		getErrorLocDBID( int idx )			{	assert( idx >= 0 && idx < (int) m_laErrorLocDBID.size() );
																return (idx >= 0 && idx < (int) m_laErrorLocDBID.size())       ? m_laErrorLocDBID[idx] : -1;  }

	int	ErrorMessageCount()								{	return m_saErrorMessages.count();  }
	void	AddErrorMessage( const char* pszErrMsg )	{	m_saErrorMessages.push_back( pszErrMsg );
																		m_saErrorPrimObjNames.push_back( "" );  // SAC 4/23/13 - added error message detail data
																		m_saErrorLocObjNames.push_back( "" );
																		m_iaErrorPrimObjClass.push_back(0);
																		m_iaErrorLocObjClass.push_back(0);
																		m_laErrorLocDBID.push_back(0);
																		return;  }
	void	AddErrorMessageDetails( const char* pszErrMsg, int iLocClass, long lLocDBID, const char* pszLocObjName, int iPrimClass=0, const char* pszPrimObjName=NULL )
																	{	m_saErrorMessages.push_back( pszErrMsg );
																		if (pszPrimObjName && strlen( pszPrimObjName ) > 0)  // SAC 4/23/13 - added error message detail data
																			m_saErrorPrimObjNames.push_back( pszPrimObjName );
																		else
																			m_saErrorPrimObjNames.push_back( "" );
																		if (pszLocObjName && strlen( pszLocObjName ) > 0)
																			m_saErrorLocObjNames.push_back( pszLocObjName );
																		else
																			m_saErrorLocObjNames.push_back( "" );
																		m_iaErrorPrimObjClass.push_back( iPrimClass );
																		m_iaErrorLocObjClass.push_back(  iLocClass  );
																		m_laErrorLocDBID.push_back(      lLocDBID   );
																		return;  }
	void	ClearErrorMessages()								{	m_saErrorMessages.clear();
																		m_saErrorPrimObjNames.clear();  // SAC 4/23/13 - added error message detail data
																		m_saErrorLocObjNames.clear();
																		m_iaErrorPrimObjClass.clear();
																		m_iaErrorLocObjClass.clear();
																		m_laErrorLocDBID.clear();
																		return;  }

   bool getAbortRuleEvaluation()										{	return m_ruleListList.getAbortRuleEvaluation();	}
   void setAbortRuleEvaluationFlag( bool bAbortRuleEval )	{	m_ruleListList.setAbortRuleEvaluationFlag( bAbortRuleEval );	return;	}

   bool evalErrorCheckList( LPCSTR listName, QStringList& saErrorMsgs, QStringList& saWarningMsgs,
									 int iEvalOnlyClass=0, int iEvalOnlyOccur=-1 )
   				{	return m_ruleListList.EvalErrorCheckList( listName, saErrorMsgs, saWarningMsgs, iEvalOnlyClass, iEvalOnlyOccur );  }

	void SetDurationMark( int i1MarkIdx )	// SAC 10/24/13 - added to facilitate rule evaluation duration tracking/logging
					{	assert( (i1MarkIdx > 0 && i1MarkIdx <= 4) );
						if (i1MarkIdx > 0 && i1MarkIdx <= 4)
						{	m_timeMark[i1MarkIdx-1] = boost::posix_time::microsec_clock::local_time();
							m_bLogDurations = true;
						}	}
	double GetDurationSinceMark( int i1SinceMarkIdx, bool bResetMark=false )	// SAC 10/24/13
					{	double dRetVal=-1.0;
						if (m_bLogDurations)
						{	assert( (i1SinceMarkIdx > 0 && i1SinceMarkIdx <= 4) );
							if (i1SinceMarkIdx > 0 && i1SinceMarkIdx <= 4)
							{	boost::posix_time::ptime tNow(boost::posix_time::microsec_clock::local_time());
								boost::posix_time::time_duration td = tNow - m_timeMark[i1SinceMarkIdx-1];
								dRetVal = ((double) td.total_microseconds()) / 1000000.0;
								if (bResetMark)
									m_timeMark[i1SinceMarkIdx-1] = tNow;
						}	}
						return dRetVal;	}

   PLogMsgCallbackFunc getLogMsgCallbackFunc()					{	return m_pLogMsgCallbackFunc;  }
	void  setLogMsgCallbackFunc( PLogMsgCallbackFunc pLMCF )	{	m_pLogMsgCallbackFunc = pLMCF;  return;  }

   bool EvaluateRuleListDuringEval( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined=FALSE )
   						{	return m_ruleListList.EvalListDuringEval( pEval, bTagDataAsUserDefined );  }
   bool EvaluateRuleList( LPCSTR listName, BOOL bTagDataAsUserDefined=FALSE,
                  int iEvalOnlyClass=0, BEM_ObjType eEvalOnlyObjType=BEMO_User,
                  std::vector<int>* piaEvalOnlyObjs=NULL,
                  BOOL bVerboseOutput=FALSE,
                  BEMCompNameTypePropArray* pTargetedDebugInfo=NULL,
						long* plRuleEvalCount=NULL,
						QStringList* psaWarningMsgs=NULL )		// SAC 3/2/18 - added to enable Warning message tracking during normal list evaluation
   						{	return m_ruleListList.EvalList( listName, bTagDataAsUserDefined,
   											iEvalOnlyClass, eEvalOnlyObjType, piaEvalOnlyObjs,
   											bVerboseOutput, pTargetedDebugInfo, plRuleEvalCount, psaWarningMsgs );  }

   int  getNumRuleLists()												{	return m_ruleListList.getNumRuleLists();  }
	void addNewRuleList( LPCSTR name, bool bSetAllData=TRUE, bool bAllowMultipleEvaluations=TRUE,
						bool bTagAllDataAsUserDefined=FALSE, int iLineNumber=0, const char* pszFileName=NULL,
						bool bPerformSetBEMDataResets=TRUE )		{	m_ruleListList.NewList( name, bSetAllData,
																						bAllowMultipleEvaluations, bTagAllDataAsUserDefined,
																						iLineNumber, pszFileName, bPerformSetBEMDataResets );  return;  }
   RuleList* getRuleList( LPCSTR name )							{	return m_ruleListList.getRuleList( name );  }
   RuleList* getRuleList( int i )									{	return m_ruleListList.getRuleList( i );  }
	int  getRulelistNames( QVector<QString>& sRulelistNames )	{	return m_ruleListList.getRulelistNames( sRulelistNames );  }
	void readRuleLists( CryptoFile& file, int iFileStructVer=1 )	{	return m_ruleListList.Read( file, iFileStructVer );  }

   void addRuleToCurrentList( QString& sRuleID, QString& sDbID, QString& sExp,
   				int i1RuleFileIdx=0, int iRuleLineNum=0 )		{	m_ruleListList.AddRule( sRuleID, sDbID, sExp,
   																												i1RuleFileIdx, iRuleLineNum );  return;  }
	void deleteTrailingRuleLists( int iNumListsToDelete=1 )	{	m_ruleListList.RemoveTrailing( iNumListsToDelete );  return;  }

	int							getNumTransformations()				{ return (int) m_transformations.size();  }
	RuleSetTransformation*	getTransformation( int idx )		{ return m_transformations.at(idx);  }
	void	addTransformation( RuleSetTransformation* pT )		{ m_transformations.push_back(pT);  return;  }

	BEMTable* getTablePtr( const char* tableName );
	bool  getTableValue( int tableID, double* paramArray, int col, double* pfValue, BOOL bVerboseOutput=FALSE );
	int   getTableID( const char* tableName );
	int   getTableDimension( int tableID, BOOL bParams=TRUE );
	int   getTableName( int tableID, QString& sTableName );
	int	getTableColumnName( int tableID, int columnID, string& sColumnName );
	BEMTableCell* getTableCell(   int iTableID, int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
											vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput=FALSE );
	bool  addTable( const char* name, const char* fileName, int nParams, int nCols, QFile& errorFile );
	bool  addTable( const char* name, const char* fileName, BEMTextIO& file, QFile& errorFile );
	bool  addTable( const char* fileName, QFile& errorFile );
	void  addTable( BEMTable* pTable )					{	m_tables.push_back(pTable);  return;  }

	int               numRulesetProperties()			{	return (int) m_rulesetProperties.size();  }
	RuleSetProperty*  getRuleSetProperty(int i)		{	return (i>=0 && i<numRulesetProperties()) ? m_rulesetProperties.at(i) : NULL;  }
	void  addRuleSetProperty(RuleSetProperty* pRP)	{	m_rulesetProperties.push_back(pRP);  return;  }

	void  addDataType(BEMPropertyDataType* pDT)		{	m_dataTypes.push_back(pDT);  return;  }
	int   getNumDataTypes()									{	return (int) m_dataTypes.size();  }
	void  postDataTypesToDatabase();
	bool  readDataTypesText( QString sFileName, QFile& errorFile );

	void  addRangeCheck(BEMRangeCheck* pR)				{	m_ranges.push_back(pR);  return;  }
	int   getNumRangeChecks()								{	return (int) m_ranges.size();  }
	bool	postRangeChecksToDatabase();
	bool  readRangesText( QString sFileName, QFile& errorFile );

	void  addSymLst(SymLst* pSL)							{	m_symbolLists.push_back(pSL);  return;  }
	int   getNumSymLsts()									{	return (int) m_symbolLists.size();  }
	bool  postSymbolsToDatabase();
	bool  readSymbolsText( QString sFileName, QFile& errorFile );
	void  clearSymbols();

	void  addReset(BEMResetData* pR)						{	m_resets.push_back(pR);  return;  }
	void	addReset( std::vector<long>& modDBIDs, std::vector<long>& resetDBIDs );
	int   getNumResets()										{	return (int) m_resets.size();  }
	void  postResetsToDatabase();
	bool  readResetsText( QString sFileName, QFile& errorFile );

	void  addRulePropTypeMod( BEMPropTypeMod* pRulePropTypeMod );
	void  addRulePropTypeMod( long lDBID, int iReportPrecision );
	void  addRulePropTypeMod( long lDBID, const char* pszPrevName );
	void  postRulePropTypeModsToDatabase();

	int   getNumToolTips()							{	return (int) m_ruleToolTips.size();  }
	long  getToolTipDBID( int i, int j=0 )		{	if (i >= 0 && i < (int) m_ruleToolTips.size() &&
																	 j >= 0 && j < MAX_NUM_INDIRECTIONS)
																	return m_ruleToolTips[i]->getDBID(j);
																return -1;  }
	QString getToolTipString( int i )			{	if (i >= 0 && i < (int) m_ruleToolTips.size())
																	return m_ruleToolTips[i]->getString();
																return "";  }
	void  addToolTip(RuleToolTip* pTT)			{	m_ruleToolTips.push_back(pTT);  return;  }

	GeomDBIDs* getGeomIDs()													{	return &m_GeomIDs;  }
	bool initGeomIDs( ExpEvalStruct* pEval, ExpError* error )	{	return m_GeomIDs.Init( pEval, error );  }
	bool initGeomIDs( QString& sErrMsg )								{	return m_GeomIDs.Init( sErrMsg );  }

	int  nextExportFileIndex()		{	for (int i=0; i<NUM_RULE_EXPORTFILES; i++)
												{	if (m_pfExportFile[i] == NULL)
														return i;
												}
												return -1;  }
	int  writeToExportFile( int iEFIdx, QString& str )
											{	if (iEFIdx < 0 || iEFIdx >= NUM_RULE_EXPORTFILES)
													return -1;		// -1 => invalid file index
												else if (m_pfExportFile[iEFIdx] == NULL)
													return -2;		// -2 => file not opened for writing
												else
													fprintf( m_pfExportFile[iEFIdx], (const char*) str.toLocal8Bit().constData() );
												return 0;  }
	int  openExportFile( int iEFIdx, const char* pszFileName, const char* pszFileMode )
											{	if (iEFIdx < 0 || iEFIdx >= NUM_RULE_EXPORTFILES)
													return -1;		// -1 => invalid file index
												else if (m_pfExportFile[iEFIdx] != NULL)
													return -2;		// -2 => file already open
												else
													fopen_s( &m_pfExportFile[iEFIdx], pszFileName, pszFileMode );
												return (m_pfExportFile[iEFIdx] == NULL ? -3 : 0);  }	// -3 => error opening file
	int  closeExportFile( int iFirstExpFileIdx, int iLastExpFileIdx )
											{	int iRetVal = 0;
												if (iFirstExpFileIdx < 0 || iFirstExpFileIdx >= NUM_RULE_EXPORTFILES)
													iRetVal = -1;		// -1 => invalid iFirstExpFileIdx index
												else if (iLastExpFileIdx < 0 || iLastExpFileIdx >= NUM_RULE_EXPORTFILES)
													iRetVal = -2;		// -1 => invalid iLastExpFileIdx index
												else
													for (int iFI = iFirstExpFileIdx; (iRetVal >= 0 && iFI <= iLastExpFileIdx); iFI++)
													{	if (m_pfExportFile[iFI])
														{	fflush( m_pfExportFile[iFI] );
															fclose( m_pfExportFile[iFI] );
															m_pfExportFile[iFI] = NULL;
															iRetVal++;
													}	}
												return iRetVal;  }

   FILE*	 getWriteToFilePtr()					{	return m_pfWriteToFile;  }
   void   setWriteToFilePtr( FILE* pF )	{	m_pfWriteToFile = pF;  }
	int  writeToOutputFile( QString& str )
											{	if (m_pfWriteToFile == NULL)
													return -1;		// -1 => file not opened for writing
												else
													fprintf( m_pfWriteToFile, (const char*) str.toLocal8Bit().constData() );
												return 0;  }

	void logMsgCallback( int iClassification, QString& sErrorMsg, const char* pszHelpKey )
											{	if (m_pLogMsgCallbackFunc)
													logMsgCallback( iClassification, (const char*) sErrorMsg.toLocal8Bit().constData(), pszHelpKey );
												return;  }
	void logMsgCallback( int iClassification, QString& sErrorMsg, QString& sHelpKey )
											{	if (m_pLogMsgCallbackFunc)
													logMsgCallback( iClassification, (const char*) sErrorMsg.toLocal8Bit().constData(),
																								(const char*)  sHelpKey.toLocal8Bit().constData() );
												return;  }
	void logMsgCallback( int iClassification, const char* pszErrorMsg, const char* pszHelpKey )
											{	if (m_pLogMsgCallbackFunc)
													m_pLogMsgCallbackFunc( iClassification, pszErrorMsg, pszHelpKey );
												return;  }

	bool  writeCompiledRuleset( LPCSTR fileName, QFile& errorFile );

private:
   RuleListList    m_ruleListList;     // all the compliance rules, organized into lists
	std::vector<BEMTable*>	m_tables;   // look-up tables
   std::vector<BEMPropertyDataType*>   m_dataTypes;     // data type assignments
   std::vector<BEMRangeCheck*>   	   m_ranges;        // range check definitions
	std::vector<SymLst*>						m_symbolLists;   // symbol definitions
//   CMaxChildList    m_maxChildList;    // MaxChild list
   std::vector<BEMResetData*>          m_resets;        // reset property definitions
//   CUniqueAssignmentList m_uniqueAssignmentList;  // unique component assignment definitions
   std::vector<BEMPropTypeMod*>        m_rulePropTypeMods;  // SAC 2/5/15 - data used to update BEMBase PropertyType objects
	std::vector<RuleSetTransformation*>	m_transformations;
	std::vector<RuleSetProperty*>	      m_rulesetProperties;
	std::vector<RuleToolTip*>	         m_ruleToolTips;
   QString          m_sRuleSetID;      // ruleset ID string
   QString          m_sRuleSetVersion; // ruleset version string
   QStringList      m_saLabels;			// SAC 9/8/14 - labels used to facilitate ruleset source shared by multiple standards/versions
   // SAC 2/1/99 - Added references to screens and tooltips filenames to enable ruleset toggling to also switch screen definitions
   QString          m_sBEMBaseFile;    // BEMBase data model definitions filename string  - SAC 8/15/14 - added
   QString          m_sScreensFile;    // Screens text filename string
   QString          m_sToolTipsFile;   // ToolTips text filename string

   int              m_iFileStructVersion;  // SAC 6/12/00 - added to enable structure mods while retaining backward compatibility
   PLogMsgCallbackFunc m_pLogMsgCallbackFunc;  // SAC 5/25/12 - added to facilitate calling of messgae logging callback function from throughout ruleset functions
	int              m_iRulesetOrganization;  // SAC 6/21/12 - added to differentiate "procedural" vs. "data model" rulesets
	bool             m_bDataModelRuleActive;  // SAC 5/26/16 - added to enable combination of data model and procedural rule parsing within a data model ruleset
	long             m_lSimulateDBID;			// SAC 3/18/14 - added to enable BEMBase property to control whether or not a simulation is to be performed for each transform
   QStringList        m_saErrorMessages;      // SAC 8/2/12 - added array of error messages
   QStringList        m_saErrorPrimObjNames;  // SAC 4/23/13 - added error message detail data
   QStringList        m_saErrorLocObjNames;
   std::vector<int>    m_iaErrorPrimObjClass;
   std::vector<int>    m_iaErrorLocObjClass;
   std::vector<long>  m_laErrorLocDBID;

   FILE*		m_pfWriteToFile;		// SAC 6/6/13 - added in conjunction w/ new WriteToFile() ruleset function

   FILE*		m_pfExportFile[NUM_RULE_EXPORTFILES];		// SAC 9/15/15 - added in conjunction w/ new Open/Write/CloseExportFile() ruleset functions

	GeomDBIDs	m_GeomIDs;		// SAC 10/1/13 - added in conjunction w/ daylighting calcs

	bool								m_bLogDurations;	// SAC 10/24/13 - added to facilitate rule evaluation duration tracking/logging
	boost::posix_time::ptime	m_timeMark[4];
};

// declare the presence of a single ruleset stored in memory at all times
extern RuleSet ruleSet;


#endif  // ifndef __RULELIST_H__
