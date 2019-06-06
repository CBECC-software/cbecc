// rulelist.cpp - all the ruleset class definitions
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

#include "stdafx.h"
#include <math.h>
#include "expRuleList.h"
#include "expRule.h"
// TO OPENSRC ?
//#include "RulPrc.h"
//#include "..\BEMProcI.h"
#include "expyy.h"
#include "BEMProcObject.h"
#include "BEMPropertyType.h"
#include "BEMProperty.h"
#include "BEMClass.h"
#include "BEMProcI.h"

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <map>
using namespace std;
using namespace boost::assign;

#include "boost/date_time/posix_time/posix_time.hpp" // include all types plus i/o (ptime...)
using namespace boost::posix_time;

#include "memLkRpt.h"


static inline void ExpSetErr( ExpError* pError, ExpErrorCode code, const char* text )
{
   ExpSetError( pError, code, text );
}


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetRulesetID()
//
// Purpose ------------------------------------------------------------------
//   Returns the ruleset ID and version strings from the current ruleset.
//   
// Arguments ----------------------------------------------------------------
//   QString& sRuleSetID  : string to populate with ruleset ID
//   QString& sRuleSetVer : string to populate with ruleset version
//   
// Return Value -------------------------------------------------------------
//   TRUE if the ruleset strings are available and properly set, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_GetRulesetID( QString& sRuleSetID, QString& sRuleSetVer )		// was: RuleProcGetRulesetID()
{	sRuleSetID.clear();
	sRuleSetVer.clear();
	if (!ruleSet.getRuleSetID().isEmpty() && !ruleSet.getRuleSetVersion().isEmpty())
	{	sRuleSetID  = ruleSet.getRuleSetID();
		sRuleSetVer = ruleSet.getRuleSetVersion();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  RuleProcGetScreenFiles()
//
// Purpose ------------------------------------------------------------------
//   Returns the screens and tooltips filename strings from the current ruleset.
//   
// Arguments ----------------------------------------------------------------
//   QString& sScreensFN  : string to populate with Screens text filename
//   QString& sToolTipsFN : string to populate with ToolTips text filename
//   
// Return Value -------------------------------------------------------------
//   TRUE if the filename strings are available and properly set, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_GetScreenFiles( QString& sScreensFN, QString& sToolTipsFN )		// was: RuleProcGetScreenFiles
{ 
   sScreensFN.clear();
   sToolTipsFN.clear();
   if (!ruleSet.getScreensFile().isEmpty() && !ruleSet.getToolTipsFile().isEmpty())
   {
      sScreensFN  = ruleSet.getScreensFile();
      sToolTipsFN = ruleSet.getToolTipsFile();
      return TRUE;
   }
   return FALSE;
}


int BEMPX_GetRulesetOrganization()		// was: RuleProcGetRulesetOrganization()
{	return ruleSet.getRulesetOrganization();
}


/////////////////////////////////////////////////////////////////////////////

int BEMPX_GetNumRuleToolTips()		// SAC 5/11/14
{	return (int) ruleSet.getNumToolTips();
}

bool BEMPX_GetRuleToolTipData( int i0TTIdx, QString& sTTText, long& lDBID, int idx /*=0*/ )	// SAC 5/11/14
{	if (i0TTIdx >= 0 && i0TTIdx < ruleSet.getNumToolTips())
	{	sTTText = ruleSet.getToolTipString( i0TTIdx );
		lDBID   = ruleSet.getToolTipDBID(   i0TTIdx, idx );
							//	CString m_sToolTip;
							//	int     m_iNumIndirections;                     // # of database IDs stored in the following array
							//	long    m_lDatabaseID[ MAX_NUM_INDIRECTIONS ];  // DBIDs used to determine what data in database to set
							//	int     m_iaAncestorObjTypes[ MAX_NUM_INDIRECTIONS ];  // 1-based object type indexes of ancestors of object to be evaluated by rule
		return (lDBID > 0);
	}
	return false;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ruleset error exports
int  BEMPX_GetRulesetErrorCount()
{	return ruleSet.ErrorMessageCount();
}

bool BEMPX_GetRulesetErrorMessage( int i1ErrMsgIdx, char* pszErrMsg, int iMsgBufferLen )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() && pszErrMsg &&
				strncpy_s( pszErrMsg, iMsgBufferLen, ruleSet.getErrorMessage(i1ErrMsgIdx-1).toLocal8Bit().constData(), _TRUNCATE ) == 0 );
}

void BEMPX_ClearRulesetErrors()
{	ruleSet.ClearErrorMessages();
	return;
}

void BEMPX_AddRulesetError( const char* pszErrMsg )
{	ruleSet.AddErrorMessage( pszErrMsg );
	return;
}

// ruleset error externs
int  BEMP_GetRulesetErrorLocalClass( int i1ErrMsgIdx )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() ? ruleSet.getErrorLocObjClass(i1ErrMsgIdx-1) : -1 );
}
long BEMP_GetRulesetErrorLocalDBID(  int i1ErrMsgIdx )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() ? ruleSet.getErrorLocDBID(i1ErrMsgIdx-1) : -1 );
}
bool BEMP_GetRulesetErrorLocalObjectName(   int i1ErrMsgIdx, char* pszObjName, int iBufferLen )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() && pszObjName &&
				strncpy_s( pszObjName, iBufferLen, ruleSet.getErrorLocObjName(i1ErrMsgIdx-1).toLocal8Bit().constData(), _TRUNCATE ) == 0 );
}
int  BEMP_GetRulesetErrorPrimaryClass(      int i1ErrMsgIdx )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() ? ruleSet.getErrorPrimObjClass(i1ErrMsgIdx-1) : -1 );
}
bool BEMP_GetRulesetErrorPrimaryObjectName( int i1ErrMsgIdx, char* pszObjName, int iBufferLen )
{	return ( i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount() && pszObjName &&
				strncpy_s( pszObjName, iBufferLen, ruleSet.getErrorPrimObjName(i1ErrMsgIdx-1).toLocal8Bit().constData(), _TRUNCATE ) == 0 );
}
bool BEMP_PopulateRulesetErrorMessage(      int i1ErrMsgIdx, QString& sErrMsg, bool bVerbose /*=FALSE*/ )
{	bool bRetVal = (i1ErrMsgIdx > 0 && i1ErrMsgIdx <= ruleSet.ErrorMessageCount());
	if (bRetVal)
	{	sErrMsg.clear();
		// filter out generic messages that indicate certain rulelists failing
		if (bVerbose || ruleSet.getErrorMessage(i1ErrMsgIdx-1).left(41).compare("ERROR:  Error encountered evaluating rule", Qt::CaseInsensitive) != 0)
		{
			sErrMsg = ruleSet.getErrorMessage(i1ErrMsgIdx-1);
			if (!bVerbose)
			{	// if verbose flag NOT set, then strip off details of where (in rule source) error occurred
				int iRuleDetailIdx = sErrMsg.indexOf( " evaluating rule: " );
				if (iRuleDetailIdx > 0)
					sErrMsg = sErrMsg.left( iRuleDetailIdx );
			}

			if (ruleSet.getErrorLocObjClass(i1ErrMsgIdx-1) > 0 && ruleSet.getErrorPrimObjClass(i1ErrMsgIdx-1) > 0 &&
				 ruleSet.getErrorLocObjClass(i1ErrMsgIdx-1) != ruleSet.getErrorPrimObjClass(i1ErrMsgIdx-1) &&
				 !ruleSet.getErrorLocObjName(i1ErrMsgIdx-1).isEmpty() && !ruleSet.getErrorPrimObjName(i1ErrMsgIdx-1).isEmpty())
			{	int iError;
				BEMClass* pLocClass  = BEMPX_GetClass( ruleSet.getErrorLocObjClass( i1ErrMsgIdx-1), iError );									assert( pLocClass  );
				BEMClass* pPrimClass = BEMPX_GetClass( ruleSet.getErrorPrimObjClass(i1ErrMsgIdx-1), iError );									assert( pPrimClass );
				BEMPropertyType* pLocPropType = BEMPX_GetPropertyTypeFromDBID( ruleSet.getErrorLocDBID(i1ErrMsgIdx-1), iError );		assert( pLocPropType );
				if (pLocClass && pPrimClass && pLocPropType)
				{	if (	sErrMsg.indexOf( pPrimClass->getLongName() ) >= 0 || sErrMsg.indexOf( ruleSet.getErrorPrimObjName(i1ErrMsgIdx-1) ) >= 0 || sErrMsg.indexOf( pLocPropType->getShortName() ) >= 0 ||
							sErrMsg.indexOf(  pLocClass->getLongName() ) >= 0 || sErrMsg.indexOf( ruleSet.getErrorLocObjName( i1ErrMsgIdx-1) ) >= 0 )
					{  // don't actually modify the error message if all substrings we are about to add are already listed in the message
					}
					else
						sErrMsg += QString( "  (%1 '%2' / %3 '%4' %5)" ).arg( pPrimClass->getLongName(), ruleSet.getErrorPrimObjName(i1ErrMsgIdx-1),
																								 pLocClass->getLongName(), ruleSet.getErrorLocObjName( i1ErrMsgIdx-1), pLocPropType->getShortName() );
				}
			}
			else if (ruleSet.getErrorLocObjClass(i1ErrMsgIdx-1) > 0 && !ruleSet.getErrorLocObjName(i1ErrMsgIdx-1).isEmpty())
			{	int iError;
				BEMClass* pLocClass  = BEMPX_GetClass( ruleSet.getErrorLocObjClass( i1ErrMsgIdx-1), iError );									assert( pLocClass  );
				BEMPropertyType* pLocPropType = BEMPX_GetPropertyTypeFromDBID( ruleSet.getErrorLocDBID(i1ErrMsgIdx-1), iError );			assert( pLocPropType );
				if (pLocClass && pLocPropType)
				{	if (sErrMsg.indexOf(  pLocClass->getLongName() ) >= 0 || sErrMsg.indexOf( ruleSet.getErrorLocObjClass( i1ErrMsgIdx-1) ) >= 0 || sErrMsg.indexOf( pLocPropType->getShortName() ) >= 0)
					{  // don't actually modify the error message if all substrings we are about to add are already listed in the message
					}
					else
						sErrMsg += QString( "  (%1 '%2' %3)" ).arg( pLocClass->getLongName(), ruleSet.getErrorLocObjName( i1ErrMsgIdx-1), pLocPropType->getShortName() );
				}
			}
		}
	}
	return bRetVal;
}

void BEMP_AddRulesetErrorExt( const char* pszErrMsg, int iLocClass, long lLocDBID, const char* pszLocObjName, int iPrimClass /*=0*/, const char* pszPrimObjName /*=NULL*/ )
{
	ruleSet.AddErrorMessageDetails( pszErrMsg, iLocClass, lLocDBID, pszLocObjName, iPrimClass, pszPrimObjName );
	return;
}


/////////////////////////////////////////////////////////////////////////////
// SAC 8/6/13 - get/set flags indicating that rule processing was/should be aborted
bool BEMPX_AbortRuleEvaluation()
{	return ruleSet.getAbortRuleEvaluation();
}
void BEMPX_SetAbortRuleEvaluationFlag( bool bAbortRuleEval )
{	return ruleSet.setAbortRuleEvaluationFlag( bAbortRuleEval );
}

/////////////////////////////////////////////////////////////////////////////
bool BEMPX_InitGeometryIDs( QString& sErrMsg )		// SAC 2/25/14
{	return ruleSet.initGeomIDs( sErrMsg );
}

/////////////////////////////////////////////////////////////////////////////
// SAC 5/27/00 - added to retrieve the names of each rulelist in the ruleset
int BEMPX_GetRulelistNames( QVector<QString>& sRulelistNames )		// was: RuleProcGetRulelistNames()
{	return ruleSet.getRulelistNames( sRulelistNames );
}

bool BEMPX_RulelistExists( LPCSTR listName )		// SAC 2/27/17
{	return (ruleSet.getRuleList( listName ) != NULL);
}

void BEMPX_DeleteTrailingRuleLists( int iNumListsToDelete /*=1*/ )	// SAC 1/29/18
{	ruleSet.deleteTrailingRuleLists( iNumListsToDelete );
	return;
}

/////////////////////////////////////////////////////////////////////////////

bool BEMPX_EvaluateRuleList( LPCSTR listName, BOOL bTagDataAsUserDefined /*=FALSE*/, int iEvalOnlyClass /*=0*/,
														int iEvalOnlyObjIdx /*=-1*/, int iEvalOnlyObjType /*=0*/, BOOL bVerboseOutput /*=FALSE*/,
														void* pvTargetedDebugInfo /*=NULL*/, long* plNumRuleEvals /*=NULL*/, double* pdNumSeconds /*=NULL*/, 
														PLogMsgCallbackFunc pLogMsgCallbackFunc /*=NULL*/,
														QStringList* psaWarningMsgs /*=NULL*/ )		// SAC 3/2/18 - added to enable Warning message tracking during normal list evaluation
{
   std::vector<int>* pivEvalOnlyObjs = NULL;  // SAC 8/11/02 - Added code to enable BEMPX_EvaluateRuleList() to specify a single component to evaluate
   std::vector<int> ivEvalOnlyObjs;
   if (iEvalOnlyClass > 0 && iEvalOnlyObjIdx >= 0)
   {
      ivEvalOnlyObjs.push_back( iEvalOnlyObjIdx );
      pivEvalOnlyObjs = &ivEvalOnlyObjs;
   }

   PLogMsgCallbackFunc pARCHIVELogMsgCallbackFunc = NULL;
	if (pLogMsgCallbackFunc)  // store current ruleSet message logging function pointer for later restoration...
   {	pARCHIVELogMsgCallbackFunc = ruleSet.getLogMsgCallbackFunc();
		ruleSet.setLogMsgCallbackFunc( pLogMsgCallbackFunc );
	}

	// SAC 10/12/11 - revisions to track rule evalaution time
	long lRuleEvalCount=0;
	ptime t1(microsec_clock::local_time());
   bool bRetVal = ruleSet.EvaluateRuleList( listName, bTagDataAsUserDefined, iEvalOnlyClass, (BEM_ObjType) iEvalOnlyObjType,
										pivEvalOnlyObjs, bVerboseOutput, (BEMCompNameTypePropArray*) pvTargetedDebugInfo, &lRuleEvalCount, psaWarningMsgs );
	ptime t2(microsec_clock::local_time());

	if (plNumRuleEvals && pdNumSeconds)  // return number of rules evaluated & approximate duration of rule evaluation
	{	*plNumRuleEvals = lRuleEvalCount;
		time_duration td = t2-t1;
		*pdNumSeconds = ((double) td.total_microseconds()) / 1000000.0;
	}

	if (pLogMsgCallbackFunc)  // restore initial ruleSet message logging function pointer
		ruleSet.setLogMsgCallbackFunc( pARCHIVELogMsgCallbackFunc );

	return bRetVal;
}

// SAC 5/21/01 - Added function similar to RuleProcEvalList(), only the rules therein are designed to populate the error and warning message lists
bool BEMPX_EvalErrorCheckList( LPCSTR listName, QStringList& saErrorMsgs, QStringList& saWarningMsgs,
                                 int iEvalOnlyClass, int iEvalOnlyOccur )
{
   return( ruleSet.evalErrorCheckList( listName, saErrorMsgs, saWarningMsgs, iEvalOnlyClass, iEvalOnlyOccur ) );
}


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpDeleteParsed()
//
// Purpose ------------------------------------------------------------------
//   Delete all the nodes which make up a parsed expression.
//   
// Arguments ----------------------------------------------------------------
//   ParsedExpression *pParsed  : the parsed expression to delete the nodes of
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline bool ExpDeleteParsed( ParsedExpression *pParsed )
{
   ExpListDelete( pParsed );
   return( TRUE );
}


/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpEvaluate()
//
// Purpose ------------------------------------------------------------------
//   Evaluate an expression, storing its result at pResult.
//   
// Arguments ----------------------------------------------------------------
//   ParsedExpression* pExp       : expression to be evaluated
//   PFGetValue        pfGetValue : pointer to the function which gets current
//                                  building database data from database IDs
//   PFFormulaFunction pfBEMPFunc  : pointer to the function which evalutes
//                                  building database functions
//   void*             pData      : pointer to structure which used referenced by
//                                  the external Formula and GetValue functions to
//                                  identify what dbase parameter is being evaluated
//   void*             pResult    : address where the expression result is to be stored
//   ExpError*         pError     : structure to communicate errors back to
//                                  the calling function
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline bool ExpEvaluate( ParsedExpression* pExp, PFGetValue pfGetValue, 
                         PFFormulaFunction pfBEMPFunc, void* pData, 
                         void* pResult, ExpError* pError )
{
   EvaluateExpression( pExp, pfGetValue, pfBEMPFunc, pData, pResult, pError );
   return( TRUE );
}

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpParse()
//
// Purpose ------------------------------------------------------------------
//   Parses a textual expression (psTextExp) into a parsed expression (pCompExp).
//   
// Arguments ----------------------------------------------------------------
//   const char*       psTextExp     : the text expression to be parsed
//   ParsedExpression* pCompExp      : where the parsed expression is to be stored
//   PFGetVar          pfGetNodeType : pointer to the function which translates
//                                     component:parameter strings into database IDs
//   ExpError*         pError        : structure to communicate errors back to
//                                     the calling function
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline bool ExpParse( const char* psTextExp, ParsedExpression* pCompExp,
                      PFGetVar pfGetNodeType, PFSelectFunction pfSelectFunc, ExpError* pError )
{
	ResetCurrentFunctionTracking();  // SAC 2/14/14 - reset nest CurFunc tracking mechanism
   ParseExpression( psTextExp, pCompExp, pfGetNodeType, pfSelectFunc, pError );
   return( TRUE );
}

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpParsedToBlob()
//
// Purpose ------------------------------------------------------------------
//   To convert a parsed expression to a "blob" in preparation for output to
//   a file.  This function call actually determines how big the resulting blob
//   will be and allocates memory for the blob (as opposed to ExpMakeBlob()
//   which simply stores the produced blob in a location already allocated).
//   
// Arguments ----------------------------------------------------------------
//   ParsedExpression* pExp : parsed expression to be converted into "blob"
//   void**            blob : a pointer to the address where the blob is created
//   long*             size : a pointer to a value where the blob size is written
//   
// Return Value -------------------------------------------------------------
//   TRUE if the resulting blob size is not 0, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline bool ExpParsedToBlob( ParsedExpression* pExp, void** blob, long* size )
{
   *size = ParsedToBlob( pExp, blob, MAXEXPLEN );
   return( *size != 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpBlobToParsed()
//
// Purpose ------------------------------------------------------------------
//   To convert a "blob" back into a parsed expression following the import of
//   the blob from a file.
//   
// Arguments ----------------------------------------------------------------
//   ParsedExpression* pExp : pointer to where the resulting parsed expression
//                            is to be stored
//   void*             blob : pointer to the blob to be converted into a parsed exp
//   
// Return Value -------------------------------------------------------------
//   The return value from BlobToParsed().
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline bool ExpBlobToParsed( ParsedExpression* pExp, void* blob )
{
   return( BlobToParsed( pExp, blob ) == TRUE );
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class GeomDBIDs
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static inline int GetObjectID_LogError( const char* pszObj, int& iNumInitErrors, QString& sInitError )
{	int iOID = BEMPX_GetDBComponentID( pszObj );
	if (iOID <= 0)
	{	if (iNumInitErrors == 0)
		{	assert( FALSE );
			sInitError = QString( "object type '%1'" ).arg( pszObj );
		}
		iNumInitErrors++;
	}
	return iOID;
}

static inline long GetPropertyDBID_LogError( const char* pszObj, const char* pszProp, int iOID, int& iNumInitErrors, QString& sInitError )
{	long lDBID = BEMPX_GetDatabaseID( pszProp, iOID );
	if (lDBID <= 0)
	{	if (iNumInitErrors == 0)
		{	assert( FALSE );
			sInitError = QString( "property '%1:%2'" ).arg( pszObj, pszProp );
		}
		iNumInitErrors++;
	}
	return lDBID;
}

bool GeomDBIDs::Init( QString& sErrMsg )	// SAC 2/25/14 - added to facilitate calling from compliance manager
{
	if (!m_bIDInitAttempted)
	{	int iNumInitErrors = 0;
		QString sFirstInitError;

   	m_iOID_PolyLp			= GetObjectID_LogError( "PolyLp", iNumInitErrors, sFirstInitError );
		if (m_iOID_PolyLp > 0)
		{	m_lDBID_PolyLp_Area         = GetPropertyDBID_LogError( "PolyLp", "Area",         m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_NumOfPts     = GetPropertyDBID_LogError( "PolyLp", "NumOfPts",     m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_ParentInfrm  = GetPropertyDBID_LogError( "PolyLp", "ParentInfrm",  m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_XYLen        = GetPropertyDBID_LogError( "PolyLp", "XYLen",        m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_Perim        = GetPropertyDBID_LogError( "PolyLp", "Perim",        m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_ZBottom      = GetPropertyDBID_LogError( "PolyLp", "ZBottom",      m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_ZTop         = GetPropertyDBID_LogError( "PolyLp", "ZTop",         m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_ZHgt         = GetPropertyDBID_LogError( "PolyLp", "ZHgt",         m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_ZRngMessage  = GetPropertyDBID_LogError( "PolyLp", "ZRngMessage",  m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_XCenter      = GetPropertyDBID_LogError( "PolyLp", "XCenter",      m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_YCenter      = GetPropertyDBID_LogError( "PolyLp", "YCenter",      m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_VectorOi     = GetPropertyDBID_LogError( "PolyLp", "VectorOi",     m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_VectorOj     = GetPropertyDBID_LogError( "PolyLp", "VectorOj",     m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_VectorOk     = GetPropertyDBID_LogError( "PolyLp", "VectorOk",     m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_VectorOLen   = GetPropertyDBID_LogError( "PolyLp", "VectorOLen",   m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_UnitVectorOi = GetPropertyDBID_LogError( "PolyLp", "UnitVectorOi", m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_UnitVectorOj = GetPropertyDBID_LogError( "PolyLp", "UnitVectorOj", m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_UnitVectorOk = GetPropertyDBID_LogError( "PolyLp", "UnitVectorOk", m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_VectorPLen   = GetPropertyDBID_LogError( "PolyLp", "VectorPLen",   m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_UnitVectorPi = GetPropertyDBID_LogError( "PolyLp", "UnitVectorPi", m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_UnitVectorPj = GetPropertyDBID_LogError( "PolyLp", "UnitVectorPj", m_iOID_PolyLp, iNumInitErrors, sFirstInitError );
			m_lDBID_PolyLp_Azimuth      = BEMPX_GetDatabaseID(                "Azimuth",      m_iOID_PolyLp );		// SAC 7/12/18 - added w/ NO error checking (used when present)
			m_lDBID_PolyLp_TiltAngle    = BEMPX_GetDatabaseID(                "TiltAngle",    m_iOID_PolyLp );
		}

   	m_iOID_CartesianPt	= GetObjectID_LogError( "CartesianPt", iNumInitErrors, sFirstInitError );
		if (m_iOID_CartesianPt > 0)
   		m_lDBID_CartesianPt_Coord = GetPropertyDBID_LogError( "CartesianPt", "Coord", m_iOID_CartesianPt, iNumInitErrors, sFirstInitError );

#ifdef GEOM_NRES
		m_iOID_Story	= GetObjectID_LogError( "Story", iNumInitErrors, sFirstInitError );

		m_iOID_Spc		= GetObjectID_LogError( "Spc", iNumInitErrors, sFirstInitError );
		if (m_iOID_Spc > 0)
   	{
		//	m_lDBID_Spc_PlenumSpcRef            			= GetPropertyDBID_LogError( "Spc", "PlenumSpcRef",            m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   	//	m_lDBID_Spc_ThrmlZnRef              			= GetPropertyDBID_LogError( "Spc", "ThrmlZnRef",              m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_FlrArea                 			= GetPropertyDBID_LogError( "Spc", "FlrArea",                 m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_FlrToCeilingHgt         			= GetPropertyDBID_LogError( "Spc", "FlrToCeilingHgt",         m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SkylitDaylitArea        			= GetPropertyDBID_LogError( "Spc", "SkylitDaylitArea",        m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_PriSideDaylitArea       			= GetPropertyDBID_LogError( "Spc", "PriSideDaylitArea",       m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SecSideDaylitArea       			= GetPropertyDBID_LogError( "Spc", "SecSideDaylitArea",       m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordX  	= GetPropertyDBID_LogError( "Spc", "SrcVarSkylitDayltgRefPtCoordX",  m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordY  	= GetPropertyDBID_LogError( "Spc", "SrcVarSkylitDayltgRefPtCoordY",  m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordX 	= GetPropertyDBID_LogError( "Spc", "SrcVarPriSideDayltgRefPtCoordX", m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordY 	= GetPropertyDBID_LogError( "Spc", "SrcVarPriSideDayltgRefPtCoordY", m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordX 	= GetPropertyDBID_LogError( "Spc", "SrcVarSecSideDayltgRefPtCoordX", m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordY 	= GetPropertyDBID_LogError( "Spc", "SrcVarSecSideDayltgRefPtCoordY", m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   	//	m_lDBID_Spc_SkylitDayltgCtrlRef     			= GetPropertyDBID_LogError( "Spc", "SkylitDayltgCtrlRef",     m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   	//	m_lDBID_Spc_PriSideDayltgCtrlRef    			= GetPropertyDBID_LogError( "Spc", "PriSideDayltgCtrlRef",    m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   	//	m_lDBID_Spc_SecSideDayltgCtrlRef    			= GetPropertyDBID_LogError( "Spc", "SecSideDayltgCtrlRef",    m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSkylitDaylitArea           = GetPropertyDBID_LogError( "Spc", "SrcVarSkylitDaylitArea",        m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarPriSideDaylitArea          = GetPropertyDBID_LogError( "Spc", "SrcVarPriSideDaylitArea",       m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
   		m_lDBID_Spc_SrcVarSecSideDaylitArea          = GetPropertyDBID_LogError( "Spc", "SrcVarSecSideDaylitArea",       m_iOID_Spc, iNumInitErrors, sFirstInitError ); 
         m_lDBID_Spc_SrcVarSkylitRDP               	= GetPropertyDBID_LogError( "Spc", "SrcVarSkylitRDP",               m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarPriSideRDP              	= GetPropertyDBID_LogError( "Spc", "SrcVarPriSideRDP",              m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarSecSideRDP              	= GetPropertyDBID_LogError( "Spc", "SrcVarSecSideRDP",              m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SkylitRDPCoefs          			= GetPropertyDBID_LogError( "Spc", "SkylitRDPCoefs",          m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_PriSideRDPCoefs         			= GetPropertyDBID_LogError( "Spc", "PriSideRDPCoefs",         m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SecSideRDPCoefs         			= GetPropertyDBID_LogError( "Spc", "SecSideRDPCoefs",         m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarSkylitDayltgRefPtEffAp     = GetPropertyDBID_LogError( "Spc", "SrcVarSkylitDayltgRefPtEffAp",      m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarSkylitDayltgRefPtSrcOrient = GetPropertyDBID_LogError( "Spc", "SrcVarSkylitDayltgRefPtSrcOrient",  m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarPriSideDayltgRefPtEffAp    = GetPropertyDBID_LogError( "Spc", "SrcVarPriSideDayltgRefPtEffAp",     m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarPriSideDayltgRefPtSrcOrient= GetPropertyDBID_LogError( "Spc", "SrcVarPriSideDayltgRefPtSrcOrient", m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarSecSideDayltgRefPtEffAp    = GetPropertyDBID_LogError( "Spc", "SrcVarSecSideDayltgRefPtEffAp",     m_iOID_Spc, iNumInitErrors, sFirstInitError );
         m_lDBID_Spc_SrcVarSecSideDayltgRefPtSrcOrient= GetPropertyDBID_LogError( "Spc", "SrcVarSecSideDayltgRefPtSrcOrient", m_iOID_Spc, iNumInitErrors, sFirstInitError );
		}

   	m_iOID_ExtWall	= GetObjectID_LogError( "ExtWall", iNumInitErrors, sFirstInitError );
		if (m_iOID_ExtWall > 0)
   	{	m_lDBID_ExtWall_Az     = GetPropertyDBID_LogError( "ExtWall", "Az", m_iOID_ExtWall, iNumInitErrors, sFirstInitError ); 
		}

   	m_iOID_Roof		= GetObjectID_LogError( "Roof", iNumInitErrors, sFirstInitError );

   	m_iOID_Win		= GetObjectID_LogError( "Win", iNumInitErrors, sFirstInitError );
		if (m_iOID_Win > 0)
   	{	m_lDBID_Win_FenConsRef             = GetPropertyDBID_LogError( "Win", "FenConsRef",             m_iOID_Win, iNumInitErrors, sFirstInitError );
   		m_lDBID_Win_Area                   = GetPropertyDBID_LogError( "Win", "Area",                   m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_AllowWinShades         = GetPropertyDBID_LogError( "Win", "AllowWinShades",         m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_EnableWinShades        = GetPropertyDBID_LogError( "Win", "EnableWinShades",        m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangDepth          = GetPropertyDBID_LogError( "Win", "OverhangDepth",          m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangDistance       = GetPropertyDBID_LogError( "Win", "OverhangDistance",       m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangLeftExtension  = GetPropertyDBID_LogError( "Win", "OverhangLeftExtension",  m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangRightExtension = GetPropertyDBID_LogError( "Win", "OverhangRightExtension", m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangAngle          = GetPropertyDBID_LogError( "Win", "OverhangAngle",          m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangTransOption    = GetPropertyDBID_LogError( "Win", "OverhangTransOption",    m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangTrans          = GetPropertyDBID_LogError( "Win", "OverhangTrans",          m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_OverhangTransSchRef    = GetPropertyDBID_LogError( "Win", "OverhangTransSchRef",    m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinDepth           = GetPropertyDBID_LogError( "Win", "LeftFinDepth",           m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinDistance        = GetPropertyDBID_LogError( "Win", "LeftFinDistance",        m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinDistanceAbove   = GetPropertyDBID_LogError( "Win", "LeftFinDistanceAbove",   m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinDistanceBelow   = GetPropertyDBID_LogError( "Win", "LeftFinDistanceBelow",   m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinAngle           = GetPropertyDBID_LogError( "Win", "LeftFinAngle",           m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinTransOption     = GetPropertyDBID_LogError( "Win", "LeftFinTransOption",     m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinTrans           = GetPropertyDBID_LogError( "Win", "LeftFinTrans",           m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_LeftFinTransSchRef     = GetPropertyDBID_LogError( "Win", "LeftFinTransSchRef",     m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_RightFinDepth          = GetPropertyDBID_LogError( "Win", "RightFinDepth",          m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_RightFinDistance       = GetPropertyDBID_LogError( "Win", "RightFinDistance",       m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_RightFinDistanceAbove  = GetPropertyDBID_LogError( "Win", "RightFinDistanceAbove",  m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_RightFinDistanceBelow  = GetPropertyDBID_LogError( "Win", "RightFinDistanceBelow",  m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_RightFinAngle          = GetPropertyDBID_LogError( "Win", "RightFinAngle",          m_iOID_Win, iNumInitErrors, sFirstInitError );
			m_lDBID_Win_DisableDayltgImpact    = BEMPX_GetDatabaseID(             "DisableDayltgImpact",    m_iOID_Win );		// SAC 7/29/18 - added w/ NO error checking (used when present for 2019 DayLtg)
		}

   	m_iOID_Skylt	= GetObjectID_LogError( "Skylt", iNumInitErrors, sFirstInitError );
		if (m_iOID_Skylt > 0)
   	{	m_lDBID_Skylt_FenConsRef = GetPropertyDBID_LogError( "Skylt", "FenConsRef", m_iOID_Skylt, iNumInitErrors, sFirstInitError );
   		m_lDBID_Skylt_Area       = GetPropertyDBID_LogError( "Skylt", "Area",       m_iOID_Skylt, iNumInitErrors, sFirstInitError );
			m_lDBID_Skylt_DisableDayltgImpact  = BEMPX_GetDatabaseID(     "DisableDayltgImpact",  m_iOID_Skylt );		// SAC 7/29/18 - added w/ NO error checking (used when present for 2019 DayLtg)
		}

   	m_iOID_FenCons	= GetObjectID_LogError( "FenCons", iNumInitErrors, sFirstInitError );
		if (m_iOID_FenCons > 0)
   		m_lDBID_FenCons_VT = GetPropertyDBID_LogError( "FenCons", "VT", m_iOID_FenCons, iNumInitErrors, sFirstInitError );

				//   int   m_iOID_DayltgCtrl                     // Typ  NV   US     UL     NO    OC   CV   CP    LName                 
				//   long  m_lDBID_DayltgCtrlDayltgCtrlType      // Sym,  1,  Req,  "",      0,                  "DaylightingControlType"
				//   long  m_lDBID_DayltgCtrlDaylitAreaType      // Sym,  1,  Req,  "",      0,                  "DaylitAreaType"
				//   long  m_lDBID_DayltgCtrlDaylitArea          // Flt,  1,  Req,  "ft2",   0,                  "DaylitArea"
				//   long  m_lDBID_DayltgCtrlIllumRefPtCoord     // Flt,  3,  Req,  "ft",    0,                  "IlluminanceReferencePointCoordinate"
				//   long  m_lDBID_DayltgCtrlDayltgCtrlLtgFrac   // Flt,  1,  Req,  "",      0,                  "DaylightingControlLightingFraction"
				//   long  m_lDBID_DayltgCtrlMinDimLtgFrac       // Flt,  1,  Opt,  "",      0,                  "MinimumDimmingLightFraction"
				//   long  m_lDBID_DayltgCtrlMinDimPwrFrac       // Flt,  1,  Opt,  "",      0,                  "MinimumDimmingPowerFraction"
				//   long  m_lDBID_DayltgCtrlNumOfCtrlSteps      // Int,  1,  Opt,  "",      0,                  "NumberOfControlSteps"
				//   long  m_lDBID_DayltgCtrlIllumSetPt          // Flt,  1,  Req,  "lux",   0,                  "IlluminanceSetPoint"
				//   long  m_lDBID_DayltgCtrlIllumSetPtAdjFac    // Flt,  1,  NInp, "",      0,                  "IlluminanceSetPointAdjustmentFactor"
				//   long  m_lDBID_DayltgCtrlAdjIllumSetPt       // Flt,  1,  NInp, "lux",   0,                  "AdjustedIlluminanceSetPoint"
				//   long  m_lDBID_DayltgCtrlGlrAz               // Flt,  1,  Req,  "",      0,                  "GlareAzimuth"
				//   long  m_lDBID_DayltgCtrlMaxGlrIdx           // Flt,  1,  Req,  "",      0,                  "MaximumGlareIndex"
#endif

		m_bIDInitAttempted = true;
		m_bIDsOK = (iNumInitErrors == 0);
		if (!m_bIDsOK)
		{	if (iNumInitErrors > 1)
				sErrMsg = QString( "Error initializing geometry database IDs, starting with %1 (plus %2 others)" ).arg( sFirstInitError, QString::number((iNumInitErrors-1)) );
			else
				sErrMsg = QString( "Error initializing geometry database ID %1" ).arg( sFirstInitError );
		}
	}
	return m_bIDsOK;
}

bool GeomDBIDs::Init( ExpEvalStruct* /*pEval*/, ExpError* error )
{
	QString sErrMsg;
	Init( sErrMsg );
	if (!m_bIDsOK && error)
		ExpSetErr( error, EXP_RuleProc, sErrMsg.toLocal8Bit().constData() );
	return m_bIDsOK;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleSet
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Declare an instance of the RuleSet class which will be the one operated on in memory
RuleSet ruleSet;

/////////////////////////////////////////////////////////////////////////////
void RuleSet::initMembers()
{
   m_sRuleSetID.clear();
   m_sRuleSetVersion.clear();
   m_saLabels.clear();
   m_sBEMBaseFile.clear();
   m_sScreensFile.clear();
   m_sToolTipsFile.clear();
   m_iFileStructVersion = 1;  // SAC 6/12/00 - added to enable structure mods while retaining backward compatibility
	m_pLogMsgCallbackFunc = NULL;
	m_iRulesetOrganization = RULESETORG_PROCEDURAL;  // SAC 6/21/12 - added to differentiate "procedural" vs. "data model" rulesets
	m_bDataModelRuleActive = false;
	m_lSimulateDBID = 0;	 // SAC 3/18/14 - added to enable BEMBase property to control whether or not a simulation is to be performed for each transform

	m_saErrorMessages.clear();
	m_saErrorPrimObjNames.clear();
	m_saErrorLocObjNames.clear();
	m_iaErrorPrimObjClass.clear();
	m_iaErrorLocObjClass.clear();
	m_laErrorLocDBID.clear();

	m_pfWriteToFile = NULL;  // SAC 6/6/13
	for (int j=0; j<NUM_RULE_EXPORTFILES; j++)		// SAC 9/15/15
		m_pfExportFile[j] = NULL;

	m_GeomIDs.Clear();		// SAC 10/1/13 - added in conjunction w/ daylighting calcs
	m_bLogDurations = false;	// SAC 10/24/13
	//m_timeMark[0] = 0;	m_timeMark[1] = 0;	m_timeMark[2] = 0;	m_timeMark[3] = 0;
}

/////////////////////////////////////////////////////////////////////////////
void RuleSet::clear()
{	int i;
   m_ruleListList.RemoveAll();
	for (i = (int) m_tables.size()-1; i >= 0; i--)		// replaces: m_tableList.RemoveAll();
	{	assert( m_tables.at(i) );
		if (m_tables.at(i))
			delete m_tables.at(i);
	}
	m_tables.clear();
	for (i = (int) m_dataTypes.size()-1; i >= 0; i--)		// replaces: m_dataTypeList.RemoveAll();
	{	assert( m_dataTypes.at(i) );
		if (m_dataTypes.at(i))
			delete m_dataTypes.at(i);
	}
	m_dataTypes.clear();
	for (i = (int) m_ranges.size()-1; i >= 0; i--)		// replaces: m_rangesList.RemoveAll();
	{	assert( m_ranges.at(i) );
		if (m_ranges.at(i))
			delete m_ranges.at(i);
	}
	m_ranges.clear();
	clearSymbols();
//   m_maxChildList.RemoveAll();
	for (i = (int) m_resets.size()-1; i >= 0; i--)		// replaces: m_resetList.RemoveAll();
	{	assert( m_resets.at(i) );
		if (m_resets.at(i))
			delete m_resets.at(i);
	}
	m_resets.clear();
//   m_uniqueAssignmentList.RemoveAll();
	for (i = (int) m_rulePropTypeMods.size()-1; i >= 0; i--)		// replaces: m_rulePropTypeModList.RemoveAll();
	{	assert( m_rulePropTypeMods.at(i) );
		if (m_rulePropTypeMods.at(i))
			delete m_rulePropTypeMods.at(i);
	}
	m_rulePropTypeMods.clear();

	for (i = (int) m_transformations.size()-1; i >= 0; i--)		// replaces: (similar logic deleting transformations, followed by) m_paTransformations.RemoveAll();
	{	assert( m_transformations.at(i) );
		if (m_transformations.at(i))
			delete m_transformations.at(i);
	}
	m_transformations.clear();

	for (i = (int) m_rulesetProperties.size()-1; i >= 0; i--)		// replaces: (similar logic deleting ruleset properties, followed by) m_paRulesetProperties.RemoveAll();
	{	assert( m_rulesetProperties.at(i) );
		if (m_rulesetProperties.at(i))
			delete m_rulesetProperties.at(i);
	}
	m_rulesetProperties.clear();

	for (i = (int) m_ruleToolTips.size()-1; i >= 0; i--)		// replaces: (similar logic deleting ruleset tioltips, followed by) m_paRuleToolTips.RemoveAll();
	{	assert( m_ruleToolTips.at(i) );
		if (m_ruleToolTips.at(i))
			delete m_ruleToolTips.at(i);
	}
	m_ruleToolTips.clear();

	if (m_pfWriteToFile)  // SAC 6/6/13
	{	fflush( m_pfWriteToFile );
		fclose( m_pfWriteToFile );
	}
	for (i=0; i<NUM_RULE_EXPORTFILES; i++)		// SAC 9/15/15
	{	if (m_pfExportFile[i])
		{	fflush( m_pfExportFile[i] );
			fclose( m_pfExportFile[i] );
	}	}

	initMembers();
}

void RuleSet::clearSymbols()
{
	for (int i = (int) m_symbolLists.size()-1; i >= 0; i--)		// replaces: m_symbolList.RemoveAll();
	{	assert( m_symbolLists.at(i) );
		if (m_symbolLists.at(i))
			delete m_symbolLists.at(i);
	}
	m_symbolLists.clear();
}

// SAC 12/19/17 - switched from BOOL LabelMatches() to int LabelIndex() to return 1-based label index (0 if not found)
int RuleSet::LabelIndex( QString& sLabel, BOOL bCaseSensitive /*=FALSE*/ )		// SAC 9/9/14
{	int iRetVal = 0;
   int iNumLabels = m_saLabels.size();
	for (int i=0; (iRetVal==0 && i < iNumLabels); i++)
	{	if (m_saLabels[i].compare( sLabel, (bCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) )==0)
			iRetVal = i+1;
		//bRetVal = (	m_saLabels[i].compare( sLabel, (bCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) )==0 );
	}
	return iRetVal;
}


int RuleSet::NumRulesetPropertiesForObject( int iObjTypeID )
{	int iRetVal = 0;
   size_t iSize = m_rulesetProperties.size();
   for (size_t j=0; j<iSize; j++)
   {  RuleSetProperty* pRP = m_rulesetProperties[j];       assert( pRP );
      if (pRP && pRP->getObjTypeID() == iObjTypeID)
			iRetVal++;
   }
	return iRetVal;
}


BOOL RuleSet::PostRulePropsToDatabase( QString& sErrantRuleProps, int iDefaultInputClass /*=-1*/ )
{	sErrantRuleProps.clear();
	int iSize = (int) m_rulesetProperties.size();  // SAC 7/6/12

	if (iSize > 0)		// SAC 9/26/16 - m_propTypes vector to BEMPropertyType* -- resize array ONCE, then subsequent insertions shift existing array but don't resize it
	{	assert( eActiveBEMProcIdx < 1 );
	   BEMProcObject* pBEMProc = getBEMProcPointer( -1 );			assert( pBEMProc );
	   if (pBEMProc)
	   {	int iNumStartPropTypes = pBEMProc->getNumPropertyTypes();
			pBEMProc->resizePropertyTypes( iNumStartPropTypes + iSize );
	}	}

	for (int j=0; j<iSize; j++)
	{	RuleSetProperty* pRP = m_rulesetProperties[j];       assert( pRP );
		if (pRP)
		{	QString sErrMsg;
			int iPropType = (pRP->getPropType() >= 0 ? pRP->getPropType() : BEMP_Str);		// BEMP_Int / BEMP_Flt / BEMP_Sym / BEMP_Str / BEMP_Obj
			if (!BEMPX_InsertPropertyType( sErrMsg, pRP->getObjTypeID(), pRP->getPropID(), pRP->getPropName().toLocal8Bit().constData(), pRP->getDBID(),
														iPropType, pRP->getPropTypeObjID(), pRP->getPropNameLong().toLocal8Bit().constData(), pRP->getUnits().toLocal8Bit().constData(),   // SAC 1/30/13
														-1 /*iBEMProcIdx*/, TRUE /*bDefinedByRuleset*/, pRP->getReportPrecision() ))
			{	QString append;
				append = QString( "   %1\n" ).arg( sErrMsg );		assert( false );
				sErrantRuleProps += append;
			}
	// SAC 9/17/14 - check to see if this rule prop has an inputclass specified, and if not, create one based on the iDefaultInputClass arg
			else if (iDefaultInputClass >= 0)
			{
				BEMPropertyDataType* pDT = NULL;		// was: CDataType* pDT = ruleSet.m_dataTypes.GetDataType( pRP->m_dbid );
			   int iSize2 = (int) m_dataTypes.size();					// SAC 2/20/19 - fixed bug during mods for x64 where iSize & j ints were re-declared inside loop of original iSize & j
			   for (int j2=0; (pDT== NULL && j2<iSize2); j2++)
			   {  /*BEMPropertyDataType* pDTTmp = m_dataTypes[j];*/       assert( m_dataTypes[j2] );
			      if (m_dataTypes[j2] && m_dataTypes[j2]->getDBID() == pRP->getDBID())
						pDT = m_dataTypes[j2];
			   }
				if (pDT == NULL)
				{	pDT = new BEMPropertyDataType( pRP->getDBID(), iDefaultInputClass, (iDefaultInputClass==BEMPropertyDataType::Compulsory) /*bPrimary*/ );				assert( pDT );
					if (pDT)
						m_dataTypes.push_back( pDT );
			}	}
		}
	}
	return (sErrantRuleProps.isEmpty());
}


/////////////////////////////////////////////////////////////////////////////

BEMTable* RuleSet::getTablePtr( const char* tableName )
{
	BEMTable* pTbl = NULL;
	for (std::vector<BEMTable*>::iterator it = m_tables.begin(); (pTbl == NULL && it != m_tables.end()); ++it)
	{	if ((*it)->getName() == tableName)
			pTbl = *it;
	}
	return pTbl;
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleSet Class Function:  getTableValue()
//
// Purpose ------------------------------------------------------------------
//   Performs a table look-up on the desired table contained in the tablelist.
//   
// Arguments ----------------------------------------------------------------
//   int    tableID    : 1-based integer index of desired table in tablelist
//   float* paramArray : array of independent var values to find matching table row
//   int    col        : column of dependent value to return
//   float* pfValue    : address of memory to populate with table look-up result
//   
// Return Value -------------------------------------------------------------
//   FALSE if the table corresponding to the tableID argument os not found,
//   else the return value of the BEMTable::Lookup() function.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleSet::getTableValue( int tableID, double* paramArray, int col, double* pfValue, BOOL bVerboseOutput )
{
   bool bRetVal = FALSE;
   // return FALSE right off the bat if the list does not contain as many tables as tableID argument requires
   if ( tableID > (int) m_tables.size() || tableID < 1 )
      return bRetVal;

	BEMTable* table = m_tables.at(tableID-1);					assert( table );

   // perform look-up on desired table
   if ( table )
	{	assert( table->getColumnTitleCount()==0 );  // should be OLD style table w/ no column titles
      bRetVal = table->Lookup( paramArray, col, pfValue, bVerboseOutput );  // SAC 9/25/02
	}

   return bRetVal;
}


BEMTableCell* RuleSet::getTableCell( int iTableID, int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
											vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput /*=FALSE*/ )
{	BEMTableCell* pRetCell = NULL;
   // return NULL right off the bat if the list does not contain as many table as tableID argument requires
   if ( iTableID > (int) m_tables.size() || iTableID < 1 || iRetColID < 1 )
	{	assert( FALSE );
		if (iTableID > (int) m_tables.size())
			sErrMsg = boost::str( boost::format( "Table not found (table ID %d exceeds max %d)" ) % iTableID % m_tables.size() );
		else if (iTableID < 1)
			sErrMsg = boost::str( boost::format( "Table not found (table ID %d must be > 0)" ) % iTableID );
		else if (iRetColID < 1)
			sErrMsg = boost::str( boost::format( "Column not found (column ID %d must be > 0)" ) % iRetColID );
      return NULL;
	}

	BEMTable* table = m_tables.at(iTableID-1);					assert( table );

   // perform look-up on desired table
   if ( table )
	{	assert( (int) table->getColumnTitleCount() >= iRetColID );
		if ((int) table->getColumnTitleCount() >= iRetColID)
	      pRetCell = table->LookupCell( iRetColID, saIndepNames, saIndepStrings, faIndepValues, baIndepNumeric, sErrMsg, bVerboseOutput );
	}
   return pRetCell;
}

/////////////////////////////////////////////////////////////////////////////

int RuleSet::getTableDimension( int tableID, BOOL bParams /*=TRUE*/ )
{
   int iRetVal = -1;
   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
   if ( tableID > (int) m_tables.size() || tableID < 1 )
      return iRetVal;

	BEMTable* table = m_tables.at(tableID-1);					assert( table );

   // perform look-up on desired table
   if ( table != NULL )
      iRetVal = (bParams ? table->getNParams() : table->getNCols());

   return iRetVal;
}


int RuleSet::getTableName( int tableID, QString& sTableName )
{
   sTableName.clear();
   int iRetVal = -1;
   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
   if ( tableID > (int) m_tables.size() || tableID < 1 )
      return iRetVal;

	BEMTable* table = m_tables.at(tableID-1);					assert( table );

   // perform look-up on desired table
   if ( table != NULL )
   {
      sTableName = table->getName();
      iRetVal = tableID;
   }

   return iRetVal;
}


int RuleSet::getTableColumnName( int tableID, int columnID, string& sColumnName )
{
	sColumnName.clear();

   int iRetVal = -1;
   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
   if ( tableID > (int) m_tables.size() || tableID < 1 )
      return iRetVal;

	BEMTable* table = m_tables.at(tableID-1);					assert( table );

   // perform look-up on desired table
   if ( table != NULL )
   {
		sColumnName = table->GetColumnName( columnID );
      if (sColumnName.length() > 0)
			iRetVal = columnID;
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleSet Class Function:  getTableID()
//
// Purpose ------------------------------------------------------------------
//   Gets the 1-based array index of the table of the name tablename.
//   
// Arguments ----------------------------------------------------------------
//   const char* tableName : the name of the table for which the index is desired
//   
// Return Value -------------------------------------------------------------
//   The 1-based index of the desired table in the tablelist, or
//   -1 if the table is not found.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
int RuleSet::getTableID( const char* tableName )
{
	int iRetVal = -1;
	BOOL bDone = FALSE;
	QString sTbl = tableName, sVar;
	if (strchr( tableName, ':' ))   // iff the table name includes a colon, split tableName into table and variable (column label) portions for individual look-ups
	{	//sTbl = tableName;
		sVar = sTbl.right( sTbl.length() - sTbl.indexOf(':') - 1 );			assert( !sVar.isEmpty() );
		if (sVar.indexOf(':') >= 0)
			bDone = TRUE;	// not a valid table name if there are MORE than 1 ':'
		else
		{
			sTbl = sTbl.left( sTbl.indexOf(':') );											assert( !sTbl.isEmpty() && sTbl.indexOf(':') < 0 );
//			szTblName = (const char*) sTbl.toLocal8Bit().constData();
//			szVarName = (const char*) sVar.toLocal8Bit().constData();
		}
	}
	
   // loop over list of tables
   int id = 1;
	BEMTable* pSelTable = NULL;
	for (std::vector<BEMTable*>::iterator it = m_tables.begin(); (pSelTable == NULL && it != m_tables.end()); ++it)
	{	if (!(*it)->getName().compare( sTbl, Qt::CaseInsensitive ))
      {  iRetVal = id * BEMP_TABLEID_MULT;
			pSelTable = *it;
		}
		id++;
	}

	if (pSelTable && iRetVal > 0 && !sVar.isEmpty())
	{	int iColumnID = pSelTable->GetColumnIndex( sVar.toLocal8Bit().constData() );
		if (iColumnID < 0)
		{	assert( FALSE );   // found table, but did not find column label
			iRetVal = -1;
		}
		else
			iRetVal += iColumnID;
	}

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// SAC 4/5/16 - added to enable lookup of float in cell of new-syntax table
double BEMPX_RuleTableLookupFloat( const char* pszTableAndColumnName, vector<string>& saIndepNames, vector<string>& saIndepStrings,
												vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput /*=FALSE*/ )
{	double dRetVal = 0;
   int iTableID = ruleSet.getTableID( pszTableAndColumnName );
   if (iTableID <= 0)
	{	sErrMsg = boost::str( boost::format( "Table not found (table:column %s)" ) % pszTableAndColumnName );
		dRetVal = -1;
	}
   else
   {	int i1TblIdx = iTableID / BEMP_TABLEID_MULT;
		int i1ColIdx = iTableID % BEMP_TABLEID_MULT;
		BEMTableCell* pRetCell = ruleSet.getTableCell( i1TblIdx, i1ColIdx, saIndepNames, saIndepStrings,
																		faIndepValues, baIndepNumeric, sErrMsg, bVerboseOutput );
		if (pRetCell == NULL)
		{	if (sErrMsg.length() < 1)
				sErrMsg = boost::str( boost::format( "Table cell not found (table:column %s)" ) % pszTableAndColumnName );
			dRetVal = -2;
		}
		else
		{	switch (pRetCell->getCellType())
			{	case BEMTCT_Float     :		dRetVal = pRetCell->getValue();
													break;
			   case BEMTCT_String    : {	//string strRet = pRetCell->getString();
													sErrMsg = boost::str( boost::format( "Table cell contained string '%s', not float (table:column %s)" ) % pRetCell->getString() % pszTableAndColumnName );
													dRetVal = -3;
												}	break;
			   case BEMTCT_Error     :	{	if (sErrMsg.length() < 1)
			   										sErrMsg = boost::str( boost::format( "Table cell contained Error, not float (table:column %s)" ) % pszTableAndColumnName );
													dRetVal = -4;
												}	break;
			   case BEMTCT_Warning   : {	if (sErrMsg.length() < 1)
			   										sErrMsg = boost::str( boost::format( "Table cell contained Warning, not float (table:column %s)" ) % pszTableAndColumnName );
													dRetVal = -5;
												}	break;
			   case BEMTCT_WildCard  :	{	sErrMsg = boost::str( boost::format( "Table cell contained wildcard, not float (table:column %s)" ) % pszTableAndColumnName );
													dRetVal = -6;
												}	break;
			   case BEMTCT_Missing   :	{	sErrMsg = boost::str( boost::format( "Table cell missing, no float returned (table:column %s)" ) % pszTableAndColumnName );
													dRetVal = -7;
												}	break;
			   case BEMTCT_Undefined :	{	sErrMsg = boost::str( boost::format( "Table cell undefined, no float returned (table:column %s)" ) % pszTableAndColumnName );
													dRetVal = -8;
												}	break;
	}	}	}
	return dRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// sTableName & iTableColumn arguments:
//		either valid table name alone w/ column index,
//		OR sTableName = "TableName:ColumnName" and iTableColumn = -1
double BEMPX_ApplyHourlyMultipliersFromTable( double* dHrlyVals, LPCSTR sTableName, int iTableColumn, bool /*bVerbose*/ )
{
	double dRetVal = 0.0;
	QString qsColName, qsTableNameOnly = sTableName;	// SAC 10/8/16 - modified code to enable sTableName to include both table and column names
	int iColonIdx = qsTableNameOnly.indexOf(':');
	if (iColonIdx > 0 && iColonIdx < qsTableNameOnly.length()-1)
	{	qsColName = qsTableNameOnly.right( qsTableNameOnly.length()-iColonIdx-1 );
		qsTableNameOnly = qsTableNameOnly.left( iColonIdx );
	}
	BEMTable* pTable = ruleSet.getTablePtr( qsTableNameOnly.toLocal8Bit().constData() );
	if (pTable == NULL)
		dRetVal = -1;  // ExpSetErr( error, EXP_RuleProc, "Table referenced by ApplyHourlyResultMultipliers() function argument not found." );
	else
	{	if (!qsColName.isEmpty() && iTableColumn < 0)
			iTableColumn = pTable->GetColumnIndex( qsColName.toLocal8Bit().constData() );
		if (iTableColumn < 0 || iTableColumn > pTable->getNCols())
			dRetVal = -2;  // ExpSetErr( error, EXP_RuleProc, "Table column specified in ApplyHourlyResultMultipliers() function argument too high." );
		else
		{	double dTblVal;
			for (int iHr=0; (dRetVal != -9999 && iHr < 8760); iHr++)
			{	if (pTable->GrabRecord( iHr+1, iTableColumn, &dTblVal, true /*bIgnoreIndepCols*/ ))  //, BOOL bVerboseOutput=FALSE );  // SAC 5/15/12
					dRetVal += (dHrlyVals[iHr] * dTblVal);  // APPLY hourly multiplier factors
				else
				{	dRetVal = -9999;	// SAC 6/25/18 - revised balance check to prevent minor negative use from erroring out (Com tic #2145)
					//ExpSetErr( error, EXP_RuleProc, "Error retrieving hourly table multiplier in ApplyHourlyResultMultipliers() function." );
					break;
				}
			}
	}	}
	if (dRetVal == -9999)
		dRetVal = -3;	// SAC 6/25/18 - retain original '-3' retval indicating table value retrieval failure
	return dRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// SAC 10/24/13 - added to facilitate analysis & rule evaluation duration tracking/logging

void BEMPX_SetDurationMark( int i1MarkIdx )		// was: RuleProcSetDurationMark()
{	ruleSet.SetDurationMark( i1MarkIdx );
	return;
}

double BEMPX_GetDurationSinceMark( int i1SinceMarkIdx, bool bResetMark /*=false*/ )		// was: RuleProcGetDurationSinceMark()
{	return ruleSet.GetDurationSinceMark( i1SinceMarkIdx, bResetMark );
}


/////////////////////////////////////////////////////////////////////////////
// SAC 5/7/13 - routine to retrieve 0-based index of transform based on short name

int BEMPX_GetTransformIndex( LPCSTR sShortTransformName )		// was: RuleProcGetTransformIndex()
{	int iNumRulesetTransforms = ruleSet.getNumTransformations();
	for (int i=0; i < iNumRulesetTransforms; i++)
	{	RuleSetTransformation* pTrans = ruleSet.getTransformation(i);			assert( pTrans );
		if (pTrans && !pTrans->getShortName().compare( sShortTransformName, Qt::CaseInsensitive ))
			return i;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// SAC 3/15/13 - added routines to load information about a model transformation to be made and to evalaute rules for a given transform
int BEMPX_GetTransformInitializationInfo(	LPCSTR sShortTransformName, int* pi1BEMProcIdxToCopy,		// was: RuleProcGetTransformInitializationInfo()
														long* plDBIDsToBypassCopy, int iMaxBypassClasses )
{	int iRetVal = -1;
   int iNumRulesetTransforms = ruleSet.getNumTransformations();
	for (int i=0; (iRetVal == -1 && i < iNumRulesetTransforms); i++)
	{
		RuleSetTransformation* pTrans = ruleSet.getTransformation(i);			assert( pTrans );
		if (pTrans && !pTrans->getShortName().compare( sShortTransformName, Qt::CaseInsensitive ))
		{	iRetVal = i;
			*pi1BEMProcIdxToCopy = pTrans->getBEMProcIdxToCopy();
			int iLastExcld = (iMaxBypassClasses < pTrans->getClassOrDBIDToExcludeSize() ? iMaxBypassClasses : pTrans->getClassOrDBIDToExcludeSize());
			for (int j=0; j < iLastExcld; j++)
				plDBIDsToBypassCopy[j] = pTrans->getClassOrDBIDToExclude(j);

		// report error (?)
			if (iMaxBypassClasses < pTrans->getClassOrDBIDToExcludeSize())
			{	assert( FALSE );
				iRetVal = -2;  // too few items in array of piClassesToBypassCopy
			}
		}
	}
	return iRetVal;
}

int BEMPX_EvaluateTransform(	LPCSTR sShortTransformName, BOOL bVerboseOutput /*=FALSE*/, void* pvTargetedDebugInfo /*=NULL*/,		// was: RuleProcEvaluateTransform()
										long* plNumRuleEvals /*=NULL*/, double* pdNumSeconds /*=NULL*/ )
{	int iRetVal = -1;
   int iNumRulesetTransforms = ruleSet.getNumTransformations();
	for (int i=0; (iRetVal < 0 && i < iNumRulesetTransforms); i++)
	{
		RuleSetTransformation* pTrans = ruleSet.getTransformation(i);			assert( pTrans );
		if (pTrans && !pTrans->getShortName().compare( sShortTransformName, Qt::CaseInsensitive ) &&
				!pTrans->getRuleListName().isEmpty())
		{	if (BEMPX_EvaluateRuleList( pTrans->getRuleListName().toLocal8Bit().constData(), FALSE /*bTagDataAsUserDefined*/,
											0 /*iEvalOnlyClass*/, -1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/,
											bVerboseOutput, pvTargetedDebugInfo, plNumRuleEvals, pdNumSeconds ))
				iRetVal = i;
			else
			{	assert( FALSE );
				iRetVal = -2;
			}
		}
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

bool BEMPX_WriteFileFromRulelist( LPCSTR sFileName, LPCSTR sRulelistName, bool bVerbose /*=false*/ )	// was: RuleProcWriteFileFromRulelist()
{
	bool bRetVal = true;

	if (ruleSet.getWriteToFilePtr())  // SAC 6/6/13
	{																assert( FALSE );	// file should not ever be left open/valid between report writes
				if (bVerbose)  // SAC 2/10/14
					BEMPX_WriteLogFile( "            in BEMPX_WriteFileFromRulelist(), flushing & closing opened report file", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		fflush( ruleSet.getWriteToFilePtr() );
		fclose( ruleSet.getWriteToFilePtr() );
		ruleSet.setWriteToFilePtr( NULL );
	}

	FILE* pFile;
   fopen_s( &pFile, sFileName, "wt" );
   if (pFile)
   {
		ruleSet.setWriteToFilePtr( pFile );

				if (bVerbose)  // SAC 2/10/14
					BEMPX_WriteLogFile( QString("            in BEMPX_WriteFileFromRulelist(), successfully opened output file:  %1").arg(sFileName), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

		bRetVal = BEMPX_EvaluateRuleList( sRulelistName, FALSE /*bTagDataAsUserDefined*/, 0 /*iEvalOnlyClass*/, -1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/,
													 (bVerbose) );  //, void* pvTargetedDebugInfo /*=NULL*/, long* plNumRuleEvals /*=NULL*/, double* pdNumSeconds /*=NULL*/ )

				if (bVerbose && !bRetVal)  // SAC 2/10/14
					BEMPX_WriteLogFile( QString("            in BEMPX_WriteFileFromRulelist(), error(s) encountered evaluating file writing rulelist:  %1").arg(sRulelistName), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

		// flush, close & blast file pointer regardless of rulelist evaluation success
		fflush( ruleSet.getWriteToFilePtr() );
		fclose( ruleSet.getWriteToFilePtr() );
		ruleSet.setWriteToFilePtr( NULL );
	}
	else
	{			if (bVerbose)  // SAC 2/10/14
					BEMPX_WriteLogFile( QString("            in BEMPX_WriteFileFromRulelist(), unable to open report file:  %1").arg(sFileName), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		bRetVal = false;
	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

void RuleSet::postDataTypesToDatabase()
{
	BOOL bFirstOne = TRUE;
	int iNumDTs = getNumDataTypes();
	for (int i=0; i<iNumDTs; i++)
	{	BEMPropertyDataType* pDT = m_dataTypes.at(i);			assert( pDT );
		if (pDT)
		{
			if (bFirstOne)
			{	if (pDT->getDBID() == 1)  // DEFAULT
					BEMP_InitializeDataTypes( pDT->m_compDataType, pDT->m_primary, pDT->m_editable, pDT->m_userDefault, 
							pDT->m_displayInput, pDT->m_displayProposed, pDT->m_displayBudget, pDT->m_notInputMode, pDT->m_notInputMsg );
				else	// use program defaults
					BEMP_InitializeDataTypes();
				bFirstOne = FALSE;
			}
			else if (pDT->getDBID() != 1)
			{
				BEMPX_SetPropertyTypeDetails( pDT->m_dbid, pDT->m_compDataType, pDT->m_primary, pDT->m_editable,
													pDT->m_userDefault, pDT->m_displayInput, pDT->m_displayProposed, 
													pDT->m_displayBudget, pDT->m_notInputMode, pDT->m_notInputMsg.toLocal8Bit().constData() );		// SAC 8/12/15
			}
			else
			{	assert( false );
			}
	}	}
	return;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleSetTransformation
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
RuleSetTransformation::RuleSetTransformation()
{
	m_BEMProcIdxToCopy = -1;
}

RuleSetTransformation::RuleSetTransformation( QString& sLongName, QString& sShortName, QString& sRulelistName, int iBEMProcIdxToCopy )
{
	m_longName     = sLongName;
	m_shortName    = sShortName;				assert( m_shortName.length() <= TransShortName_MaxLen );
	m_rulelistName = sRulelistName;
	m_BEMProcIdxToCopy = iBEMProcIdxToCopy;
	m_objClassesOrDBIDsToExclude.clear();		// SAC 3/19/14
}

RuleSetTransformation::~RuleSetTransformation()
{
}

bool RuleSetTransformation::Write( CryptoFile& file )
{
   bool bRetVal = TRUE;

   file.WriteQString( m_longName );
   file.WriteQString( m_shortName );

	// SAC 3/27/14 -  added long & short Group names (to allow rule expressions to be specified once but inserted into multiple transforms)
	// SAC 8/20/15 - switched group names from single strings to arrays
	int i, iSize = m_groupLongName.size();
   file.Write( &iSize, sizeof( int ) );
	for (i=0; i<iSize; i++)
   	file.WriteQString( m_groupLongName[i] );
	iSize = m_groupShortName.size();
   file.Write( &iSize, sizeof( int ) );
	for (i=0; i<iSize; i++)
   	file.WriteQString( m_groupShortName[i] );

   file.WriteQString( m_rulelistName );
   file.Write( &m_BEMProcIdxToCopy, sizeof( int ) );

   iSize = (int) m_objClassesOrDBIDsToExclude.size();		// SAC 3/19/14
   file.Write( &iSize, sizeof( int ) );
	for (int i=0; i<iSize; i++)
	{	long lEx = m_objClassesOrDBIDsToExclude[i];
		file.Write( &lEx, sizeof( long ) );
	}

   return bRetVal;
}

void RuleSetTransformation::Read( CryptoFile& file, int iFileStructVer /*=1*/ )
{
   int size;
   file.ReadQString( m_longName );  // read string out of file
   file.ReadQString( m_shortName );
	QString str;
	if (iFileStructVer > 16)		// SAC 8/20/15 - switched group names from single strings to arrays
	{	int iNumStrs, i;
		file.Read( &iNumStrs, sizeof( int ) ); // get num strings
		for (i=0; i<iNumStrs; i++)
		{	file.ReadQString( str );
			m_groupLongName.append( str );
		}
		file.Read( &iNumStrs, sizeof( int ) ); // get num strings
		for (i=0; i<iNumStrs; i++)
		{	file.ReadQString( str );
			m_groupShortName.append( str );
		}
	}
	else if (iFileStructVer > 9)		// SAC 3/27/14 -  added long & short Group names (to allow rule expressions to be specified once but inserted into multiple transforms)
	{	file.ReadQString( str );
		m_groupLongName.append( str );
		file.ReadQString( str );
		m_groupShortName.append( str );
	}
	else
	{	m_groupLongName.clear();
		m_groupShortName.clear();
	}

   file.ReadQString( m_rulelistName );

   m_objClassesOrDBIDsToExclude.clear();
	if (iFileStructVer > 6)
   {	file.Read( &m_BEMProcIdxToCopy, sizeof( int ) );

		file.Read( &size, sizeof( int ) );
		if (size > 0)
		{	int iEx;		long lEx;
			m_objClassesOrDBIDsToExclude.resize( size );		// SAC 3/19/14
			for (int i=0; i<size; i++)
			{	if (iFileStructVer > 8)
					file.Read( &lEx, sizeof( long ) );
				else
				{	file.Read( &iEx, sizeof( int ) );
					lEx = iEx;
				}
				m_objClassesOrDBIDsToExclude[i] = lEx;
		}	}
	}
	else
   	m_BEMProcIdxToCopy = -1;
}


bool RuleSetTransformation::LongGroupNameMatch( const char* pszChk )
{	if (pszChk==NULL || strlen( pszChk ) < 1)
	{	assert( FALSE );
	}
	else
	{	for (int i=0; i<m_groupLongName.size(); i++)
			if (!m_groupLongName[i].compare( pszChk, Qt::CaseInsensitive ))
				return true;
	}
	return false;
}
bool RuleSetTransformation::LongGroupNameMatch( QString& sChk )
{	if (sChk.length() < 1)
	{	assert( FALSE );
	}
	else
	{	for (int i=0; i<m_groupLongName.size(); i++)
			if (!m_groupLongName[i].compare( sChk, Qt::CaseInsensitive ))
				return true;
	}
	return false;
}

bool RuleSetTransformation::ShortGroupNameMatch( const char* pszChk )
{	if (pszChk==NULL || strlen( pszChk ) < 1)
	{	assert( FALSE );
	}
	else
	{	for (int i=0; i<m_groupShortName.size(); i++)
			if (!m_groupShortName[i].compare( pszChk, Qt::CaseInsensitive ))
				return true;
	}
	return false;
}
bool RuleSetTransformation::ShortGroupNameMatch( QString& sChk )
{	if (sChk.length() < 1)
	{	assert( FALSE );
	}
	else
	{	for (int i=0; i<m_groupShortName.size(); i++)
			if (!m_groupShortName[i].compare( sChk, Qt::CaseInsensitive ))
				return true;
	}
	return false;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleSetProperty
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
RuleSetProperty::RuleSetProperty()
{
	m_objTypeID	= 0;
	m_propID		= 0;
	m_propName.clear();
	m_propNameLong.clear();
	m_dbid			= 0;
	m_propType		= -1;
	m_propTypeObjID = -1;
	m_reportPrecision = -9;	// SAC 2/5/15
	m_units.clear();
}

RuleSetProperty::RuleSetProperty( int iObjTypeID, int iPropID, QString& sPropName, QString& sPropNameLong, long lDBID,
												int iPropType /*=-1*/, int iPropTypeObjID /*=-1*/, int iReportPrec /*=-9*/ )
{
	m_objTypeID		= iObjTypeID;
	m_propID			= iPropID   ;
	m_propName			= sPropName ;
	m_propNameLong	= sPropNameLong;
	m_dbid				= lDBID     ;
	m_propType			= iPropType;
	m_propTypeObjID	= iPropTypeObjID;
	m_reportPrecision = iReportPrec;	// SAC 2/5/15
	m_units.clear();
}

RuleSetProperty::~RuleSetProperty()
{
}

bool RuleSetProperty::Write( CryptoFile& file )
{
   bool bRetVal = TRUE;

   file.Write( &m_objTypeID, sizeof( int    ) );
   file.Write( &m_propID   , sizeof( int    ) );

   file.WriteQString( m_propName );
   file.WriteQString( m_propNameLong );

   file.Write( &m_dbid     , sizeof( long   ) );
   file.Write( &m_propType , sizeof( int    ) );
   file.Write( &m_propTypeObjID, sizeof( int    ) );

   file.WriteQString( m_units );

   file.Write( &m_reportPrecision, sizeof( int ) );	// SAC 2/5/15

   return bRetVal;
}

void RuleSetProperty::Read( CryptoFile& file, int iFileStructVer )
{
   file.Read( &m_objTypeID, sizeof( int    ) );
   file.Read( &m_propID   , sizeof( int    ) );

   file.ReadQString( m_propName );
   file.ReadQString( m_propNameLong );

   file.Read( &m_dbid     , sizeof( long   ) );
   file.Read( &m_propType , sizeof( int    ) );
   file.Read( &m_propTypeObjID, sizeof( int    ) );

	if (iFileStructVer > 11)	// SAC 8/6/14
		file.ReadQString( m_units );
	else
		m_units.clear();

	if (iFileStructVer >= 15)	// SAC 2/5/15
	   file.Read( &m_reportPrecision, sizeof( int ) );
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleToolTip
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
RuleToolTip::RuleToolTip()
{
	m_toolTip.clear();
   m_numIndirections = 0;
	for (int i=0; i < MAX_NUM_INDIRECTIONS; i++)
	{	m_databaseID[i] = 0;
		m_ancestorObjTypes[i] = 0;
	}
}

RuleToolTip::RuleToolTip( QString sToolTip, int iNumIndirections /*=1*/, long* plDBIDs /*=NULL*/,
						int iNumAncestors /*=0*/, int* piAncestorObjTypes /*=NULL*/ )
{
	m_toolTip = sToolTip;
   m_numIndirections = iNumIndirections;
	for (int i=0; i < MAX_NUM_INDIRECTIONS; i++)
	{ 	m_databaseID[i]       = ((plDBIDs            && i < iNumIndirections) ? plDBIDs[i]            : 0);  // DBIDs used to determine what data in database to set
	  	m_ancestorObjTypes[i] = ((piAncestorObjTypes && i < iNumAncestors   ) ? piAncestorObjTypes[i] : 0);  // 1-based object type indexes of ancestors of object to be evaluated by rule
	}
}

RuleToolTip::~RuleToolTip()
{
}

bool RuleToolTip::Write( CryptoFile& file )
{
   bool bRetVal = TRUE;

	// write ruletooltip to file						
	file.WriteQString( m_toolTip );

	file.Write( &m_numIndirections, sizeof( int ) );
	int i;
	for (i = 0; i < m_numIndirections; i++)
		file.Write( &m_databaseID[ i ], sizeof( long ) );
	for (i = 0; i < MAX_NUM_INDIRECTIONS; i++ )  // SAC 4/11/13 - storage of ancestor tree
		file.Write( &m_ancestorObjTypes[ i ], sizeof( int ) );

   return bRetVal;
}

void RuleToolTip::Read( CryptoFile& file, int /*iFileStructVer=1*/ )
{
	file.ReadQString( m_toolTip );

   file.Read( &m_numIndirections, sizeof( int ) );  // read # indirections
	int i;
   for (i = 0; i < m_numIndirections; i++ )
      file.Read( &m_databaseID[ i ], sizeof( long ) );  // read each database ID
   for (i = 0; i < MAX_NUM_INDIRECTIONS; i++ )  // SAC 4/11/13 - storage of ancestor tree
      file.Read( &m_ancestorObjTypes[ i ], sizeof( int ) );
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class Rule
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  Rule()
//
// Purpose ------------------------------------------------------------------
//   Constructor - inits parsed expression nodelist to NULL
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
Rule::Rule()
{
   m_parsedExpression.nodeList = NULL;
	m_1RuleFileIdx = 0;		// SAC 4/10/13 - added to aid in debugging
	m_ruleLineNum  = 0;
	for (int i=0; i < MAX_NUM_INDIRECTIONS; i++)
	{	m_databaseID[i] = 0;
		m_ancestorObjTypes[i] = 0;
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  Rule()
//
// Purpose ------------------------------------------------------------------
//   Constructor - Sets ID DBID and text expression strings from arguments and
//   inits parsed expression nodelist to NULL.
//   
// Arguments ----------------------------------------------------------------
//   QString& sRuleID : String to set m_sId to
//   QString& sDbID   : String to set m_dbId to
//   QString& sExp    : String to set m_textExpression to
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
//Rule::Rule( LPCSTR sRuleID, LPCSTR sDbID, LPCSTR sExp, int iNumIndirections /*=1*/, long* plDBIDs /*=NULL*/,
Rule::Rule( QString& sRuleID, QString& sDbID, QString& sExp, int iNumIndirections /*=1*/, long* plDBIDs /*=NULL*/,
					int i1RuleFileIdx /*=0*/, int iRuleLineNum /*=0*/, int iNumAncestors /*=0*/, int* piAncestorObjTypes /*=NULL*/ )
{
   m_id = sRuleID;
   m_dbId = sDbID;
   m_textExpression = sExp;
   m_parsedExpression.nodeList = NULL;
	m_1RuleFileIdx = i1RuleFileIdx;		// SAC 4/10/13 - added to aid in debugging
	m_ruleLineNum  = iRuleLineNum ;
   m_numIndirections = iNumIndirections;
	for (int i=0; i < MAX_NUM_INDIRECTIONS; i++)
	{ 	m_databaseID[i]       = ((plDBIDs            && i < iNumIndirections) ? plDBIDs[i]            : 0);  // DBIDs used to determine what data in database to set
	  	m_ancestorObjTypes[i] = ((piAncestorObjTypes && i < iNumAncestors   ) ? piAncestorObjTypes[i] : 0);  // 1-based object type indexes of ancestors of object to be evaluated by rule
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  ~Rule()
//
// Purpose ------------------------------------------------------------------
//   Destructor - deletes parsed expression memory
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
Rule::~Rule()
{
   ExpDeleteParsed( &m_parsedExpression );
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  ThrowBEMPError()
//
// Purpose ------------------------------------------------------------------
//   Constructs an error message and writes it to an error file.
//   
// Arguments ----------------------------------------------------------------
//   QFile&  errorFile : file to write error message to
//   QString sParam    : component/parameter string which caused error
//   
// Return Value -------------------------------------------------------------
//   None
//
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void Rule::ThrowBEMPError( QFile& errorFile, QString sParam )
{
// SAC 4/25/02 - Revised file output to flag errors w/ "*** ERROR ***" string for easier debug mode searching
// SAC 5/1/13 - include ERROR string in release mode executables
//#ifdef _DEBUG
//   errorFile.Write( "\n*** ERROR ***  parsing: ", 26 );
   errorFile.write( "\nERROR parsing: ", 17 );
//#endif

   QString msg = m_id + QString("\n") + m_dbId;
   msg += QString("\n\tInvalid Component:Parameter String: '") + sParam + QString("'\n\n");
   errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  ParseLeft()
//
// Purpose ------------------------------------------------------------------
//   Parses the left side of the rule, which includes a basic or complex
//   component:parameter[array] string.
//   
// Arguments ----------------------------------------------------------------
//   QFile& errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   FALSE if any call to BEMPX_GetDatabaseID() fails, else TRUE
//   
// Notes --------------------------------------------------------------------
//   The string which is parsed could be as simple as "token:token" or as
//   complex as "token:token[number]:token[number]:token[number]...".
//   
/////////////////////////////////////////////////////////////////////////////
bool Rule::ParseLeft( QFile& errorFile )
{
	return ParseRuleDBID( m_id, m_dbId, m_numIndirections, m_databaseID, errorFile );  //, BOOL bDataModelOrg /*=FALSE*/ )
}


/////////////////////////////////////////////////////////////////////////////
// SAC 6/17/10 - added code to write detailed BEMProc upon FIRST occurrence of an error
#ifdef _DEBUG
static BOOL sBEMPgErrorEnsizeered = FALSE;
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  Eval()
//
// Purpose ------------------------------------------------------------------
//   Evaluate the rule.
//   
// Arguments ----------------------------------------------------------------
//   ExpEvalStruct* pEval
//   
// Return Value -------------------------------------------------------------
//   bool value: TRUE if a component was created due to a library component
//   being referenced => allows the RuleList to re-evaluate itself in order
//   to ensure ALL necessary defaulting has been performed.
//   
// Notes --------------------------------------------------------------------
//   Call ExpEvaluate() for this rule and return the resulting floating point value.
//   
/////////////////////////////////////////////////////////////////////////////
bool Rule::Eval( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined, BOOL bPerformSetBEMDataResets )  // SAC 9/18/05 - added bPerformSetBEMDataResets argument to facilitate no-reset data setting
{
   bool bRetVal = false;
   ExpNode node;
   ExpNode_init( &node );	// SAC 4/21/17
   node.type = EXP_Invalid;
   ExpError expError;
   expError.code = EXP_None;  // SAC 4/2/01
#ifdef _DEBUG  // code to facilitate debugging by enabling breakpoints based on rule line numbers (w/out modifying compiled rule structure)
	int iRuleLineNumStart = m_id.indexOf( " Line " ) + 6;
	int iRuleLineNumsize = m_id.indexOf( ":", iRuleLineNumStart ) - iRuleLineNumStart;
	QString sRuleLineNum = m_id.mid( iRuleLineNumStart, iRuleLineNumsize );
	int iRuleLineNum = (sRuleLineNum.isEmpty() ? 0 : atol( sRuleLineNum.toLocal8Bit().constData() ));			iRuleLineNum;
#endif
   // evaluate the rule
   ExpEvaluate( &m_parsedExpression, GetValue, BEMPFunction, pEval, &node, &expError );

// SAC 6/17/10 - added code to write detailed BEMProc upon FIRST occurrence of an error
#ifdef _DEBUG
   if (!sBEMPgErrorEnsizeered && expError.code != EXP_None)
   {  sBEMPgErrorEnsizeered = TRUE;
      BEMPX_WriteProjectFile( "first BEMProc rule eval error.ibd-detail", BEMFM_DETAIL /*FALSE /*bIsInputMode*/, FALSE /*bUseLogFileName*/,
                                                                 FALSE /*bWriteAllProperties*/, TRUE /*bSupressAllMessageBoxes*/ );
   }
#endif
// END OF - code to write detailed BEMProc upon FIRST occurrence of an error

   pEval->sRuleID = m_id;  // SAC 10/29/07
   bRetVal = LocalSetBEMProcData( pEval, bTagDataAsUserDefined, bPerformSetBEMDataResets, node, expError );

   // SAC 4/11/99 - switched return value from float to bool
   // return( node.info.fValue );  // return the result of the evaluation
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Writes the binary rule to the rules file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file      : encrypted file to write the parsed expression to
//   QFile&       errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   FALSE if any parsing errors occur, else TRUE.
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     Call ExpParse() to parse text rule expression.
//     Call ExpParsedToBlob() to convert parsed expression into a binary object to 
//       save in the rules binary file.  ExpParsedToBlob() allocates memory for this object
//     Write the length of the name of the rule followed by the actual string.
//     Write the binary rule object to the file.
//     free the memory for the binary object.
//   
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
const char* pszNodeTypes[] = 
		{     "Invalid    "		// EXP_Invalid,     
        ,   "Value      "		// EXP_Value,       
        ,   "String     "		// EXP_String,      
        ,   "Index      "		// EXP_Index,       
        ,   "Keyword    "		// EXP_Keyword,     
        ,   "BldgRule   "		// EXP_BldgRule,    
        ,   "Expression "		// EXP_Expression,  
        ,   "Function   "		// EXP_Function,    
        ,   "LookupFunc "		// EXP_LookupFunc,  
        ,   "If         "		// EXP_If,          
        ,   "Else       "		// EXP_Else,        
        ,   "Endif      "		// EXP_Endif,       
        ,   "Switch     "		// EXP_Switch,      
        ,   "Default    "		// EXP_Default,     
        ,   "Case       "		// EXP_Case,        
        ,   "EndSwitch  "		// EXP_EndSwitch    
      };
#endif

// SAC 8/31/16 - added to enable writing of parser messages to error log file
static QFile* spErrFile = NULL;
void ExpPostParserMsg(const char* msg)
{	if (spErrFile && msg)
		spErrFile->write( msg, strlen(msg) );
}

bool Rule::Parse( QFile& errorFile, const char* pszRLName )  // SAC 1/29/18 - similar to Write() but doesn't write rule to file, just keeps it in memory for direct use/evaluation
{
   ExpError error;

   // parse the left side of the rule (must befre setting up crntCompID)
	spErrFile = &errorFile;		// SAC 8/31/16
   bool bRetVal = ParseLeft( errorFile );

   // set the current component type ID to the leftmost component of the component/parameter string
	QString sCompID = m_dbId.left( m_dbId.indexOf(':') );
	if (ruleSet.DataModelRuleActive())   // SAC 7/8/12		// SAC 5/26/16 - revised for conventional rulelists in DataModel rulesets
	{	int iLastColon = m_dbId.lastIndexOf(':');				assert( iLastColon > 0 );
		if (iLastColon > 0)
		{	QString sLeftMinusProp = m_dbId.left( iLastColon );
			iLastColon = sLeftMinusProp.lastIndexOf(':');
			if (iLastColon > 0)
				sCompID = sLeftMinusProp.right( sLeftMinusProp.length() - iLastColon );
			else
				sCompID = sLeftMinusProp;
		}
	}
	int iPrimCompID = BEMPX_GetDBComponentID( sCompID.toLocal8Bit().constData() ); 
   crntCompID.SetCurrentCompID( iPrimCompID );  // (int)BEMPX_GetDBComponentID( sCompID ) ); 
   crntCompID.SetCurrentLocalDBID( (m_numIndirections > 0 ? m_databaseID[ m_numIndirections-1 ] : 0) );
   crntCompID.SetCurrentRulelistName( pszRLName );  // SAC 9/25/13

   // parse right side (expression portion) of the rule
   ExpParse( m_textExpression.toLocal8Bit().constData(), &m_parsedExpression, GetNodeType, SelectFunctionByArgument, &error );  /* SAC 8/14/12 */
										assert( eiParseCount_IfValidAnd == 0 && eiParseCount_ValidOr == 0 );		// SAC 1/30/15 - should always be 0 following expression parse (unless error occurred...)
										eiParseCount_IfValidAnd = 0;		eiParseCount_ValidOr = 0;  // just in case...
	spErrFile = NULL;		// SAC 8/31/16

   // if parsing OK, then write it to the encrypted output file
   bool bError = FALSE;
//   bool bError = TRUE;
//   if ( EXP_ERRORCODE( error ) == EXP_None )
//   {
//   	...  blob and writing code
//   }

   if (bError)
   {  // an error occurred parsing the right sides of the rule expression,
      // OR converting the expression to a "blob"
      // so write out the left portion like normal w/ no right side, then
      // write an error message to the error file and return FALSE

// SAC 1/5/02 - Revised file output to flag errors w/ "*** ERROR ***" string for easier _DEBUG mode searching
#ifdef _DEBUG
      errorFile.write( "\n*** ERROR ***  parsing: ", 26 );
#endif

      // create and write error message to errorFile
      QString msg = m_id + QString("\n") + m_dbId;
      msg += QString("\n\t");
      if ( EXP_ERRORCODE( error ) != EXP_None )
         msg += EXP_ERRORMSG( error );
      else
         msg += "Error translating expression to 'blob'";
      msg += QString("\n") + QString("Full expression:") + QString("\n");    // SAC 3/14/13 - added full text expression following error message
		msg += m_textExpression;
      msg += QString("\n") + QString("\n");
      errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
      bRetVal = FALSE;  // return FALSE
   }
   return bRetVal;
}

bool Rule::Write( CryptoFile& file, QFile& errorFile, const char* pszRLName )
{                                                            
   ExpError error;

   // parse the left side of the rule (must befre setting up crntCompID)
	spErrFile = &errorFile;		// SAC 8/31/16
   bool bRetVal = ParseLeft( errorFile );

   // set the current component type ID to the leftmost component of the component/parameter string
	QString sCompID = m_dbId.left( m_dbId.indexOf(':') );
	if (ruleSet.DataModelRuleActive())   // SAC 7/8/12		// SAC 5/26/16 - revised for conventional rulelists in DataModel rulesets
	{	int iLastColon = m_dbId.lastIndexOf(':');				assert( iLastColon > 0 );
		if (iLastColon > 0)
		{	QString sLeftMinusProp = m_dbId.left( iLastColon );
			iLastColon = sLeftMinusProp.lastIndexOf(':');
			if (iLastColon > 0)
				sCompID = sLeftMinusProp.right( sLeftMinusProp.length() - iLastColon );
			else
				sCompID = sLeftMinusProp;
		}
	}
	int iPrimCompID = BEMPX_GetDBComponentID( sCompID.toLocal8Bit().constData() ); 
   crntCompID.SetCurrentCompID( iPrimCompID );  // (int)BEMPX_GetDBComponentID( sCompID ) ); 
   crntCompID.SetCurrentLocalDBID( (m_numIndirections > 0 ? m_databaseID[ m_numIndirections-1 ] : 0) );
   crntCompID.SetCurrentRulelistName( pszRLName );  // SAC 9/25/13

   // parse right side (expression portion) of the rule
   ExpParse( m_textExpression.toLocal8Bit().constData(), &m_parsedExpression, GetNodeType, SelectFunctionByArgument, &error );  /* SAC 8/14/12 */
										assert( eiParseCount_IfValidAnd == 0 && eiParseCount_ValidOr == 0 );		// SAC 1/30/15 - should always be 0 following expression parse (unless error occurred...)
										eiParseCount_IfValidAnd = 0;		eiParseCount_ValidOr = 0;  // just in case...
	spErrFile = NULL;		// SAC 8/31/16

   // if parsing OK, then write it to the encrypted output file
   bool bError = TRUE;
   if ( EXP_ERRORCODE( error ) == EXP_None )
   {
      void *blob = NULL;
      long int size;
      
      // ParsedToBlob does a "*blob = malloc( size );" so we need to free it later.
      ExpParsedToBlob( &m_parsedExpression, &blob, &size ); 

      if ( (size > 0) && (blob != NULL) )
      {
         bError = FALSE;

         // write rule to file
         file.WriteQString( m_id );

	      file.Write( &m_1RuleFileIdx, sizeof( int ) );    // SAC 4/10/13 - added to aid in debugging
	      file.Write( &m_ruleLineNum , sizeof( int ) );

         file.Write( &m_numIndirections, sizeof( int ) );
			int i;
         for (i = 0; i < m_numIndirections; i++)
            file.Write( &m_databaseID[ i ], sizeof( long ) );

	   	for (i = 0; i < MAX_NUM_INDIRECTIONS; i++ )  // SAC 4/11/13 - storage of ancestor tree
   	      file.Write( &m_ancestorObjTypes[ i ], sizeof( int ) );

#ifdef _DEBUG
         QString dbgMsg;   dbgMsg = QString( "         'blob' size: %1\n" ).arg( QString::number(size) );		// SAC 8/31/16 - revised for consistency w/ YYDEBUG messages
         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );

	   	ExpNode* node;
	      //QString dbgMsg;
			int iNodeIdx = 0;
	   	for (node = ExpListHead( &m_parsedExpression ); node != NULL; node = ExpListNext( &m_parsedExpression, node ))
	   	{	switch (node->type)
				{	case EXP_Keyword	:
					case EXP_Value		:	if (node->fValue > BEM_COMP_MULT)
														dbgMsg = QString( "         node%1:  type %2 fValue %3\n" ).arg( QString::number( ++iNodeIdx ), 3 ).arg( pszNodeTypes[node->type] ).arg( QString::number( node->fValue, 'f', 0 ) );
												else	dbgMsg = QString( "         node%1:  type %2 fValue%3\n"  ).arg( QString::number( ++iNodeIdx ), 3 ).arg( pszNodeTypes[node->type] ).arg( QString::number( node->fValue, 'e' ), 13 );
				//	case EXP_Value		:	dbgMsg.sprintf( "         node%3d:  type %s fValue%14e\n", ++iNodeIdx, pszNodeTypes[node->type], node->fValue );
															break;
				//	case EXP_String	:	dbgMsg.sprintf( "         node%3d:  type %s pValue '%s'\n", ++iNodeIdx, pszNodeTypes[node->type], (char*) node->pValue );
					case EXP_String	:	dbgMsg = QString( "         node%1:  type %2 pValue '%3'\n" ).arg( QString::number( ++iNodeIdx ), 3 ).arg( pszNodeTypes[node->type] ).arg( QLatin1String( (const char*) node->pValue ) );
															break;
					case EXP_Function	:	dbgMsg.sprintf( "         node%3d:  type %s                       function%3d  op%5d  nArgs%2d\n", ++iNodeIdx,
															pszNodeTypes[node->type], node->fn.function, node->fn.op, node->fn.nArgs );
															break;
					default  			:	dbgMsg.sprintf( "         node%3d:  type %s \n", ++iNodeIdx, pszNodeTypes[node->type] );
															break;
				}
	         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
	   	}
//typedef struct ExpNode
//{  ExpNodeType type;     /* node type */
//   union
//   {  void* pValue;      /* pointer to a value, typically a character string */
//      double fValue;      /* a floating point value */
//      struct
//      {  int function;   /* function ID */
//         int op;         /* operation ID */
//         int nArgs;      /* this keeps track of the number of function arguments for variable argument functions  */
//      } fn;
//   } info;
//} ExpNode;
#endif

         file.Write( blob, (UINT)size );
         free( blob );
      }
   }

   if (bError)
   {  // an error occurred parsing the right sides of the rule expression,
      // OR converting the expression to a "blob"
      // so write out the left portion like normal w/ no right side, then
      // write an error message to the error file and return FALSE
      file.WriteQString( m_id );

      file.Write( &m_1RuleFileIdx, sizeof( int ) );    // SAC 4/10/13 - added to aid in debugging
      file.Write( &m_ruleLineNum , sizeof( int ) );

      file.Write( &m_numIndirections, sizeof( int ) );
		int i;
      for (i = 0; i < m_numIndirections; i++)
         file.Write( &m_databaseID[ i ], sizeof( long ) );

   	for (i = 0; i < MAX_NUM_INDIRECTIONS; i++ )  // SAC 4/11/13 - storage of ancestor tree
         file.Write( &m_ancestorObjTypes[ i ], sizeof( int ) );

      long noBlobSize = 0;
      file.Write( &noBlobSize, sizeof( long ) );

// SAC 1/5/02 - Revised file output to flag errors w/ "*** ERROR ***" string for easier _DEBUG mode searching
#ifdef _DEBUG
      errorFile.write( "\n*** ERROR ***  parsing: ", 26 );
#endif

      // create and write error message to errorFile
      QString msg = m_id + QString("\n") + m_dbId;
      msg += QString("\n\t");
      if ( EXP_ERRORCODE( error ) != EXP_None )
         msg += EXP_ERRORMSG( error );
      else
         msg += "Error translating expression to 'blob'";
      msg += QString("\n") + QString("Full expression:") + QString("\n");    // SAC 3/14/13 - added full text expression following error message
		msg += m_textExpression;
      msg += QString("\n") + QString("\n");
      errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
      bRetVal = FALSE;  // return FALSE
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Rule Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads the binary rule from the binary encrypted rules file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : binary encrypted rules file to read the rule from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     Read the length of the name of the rule
//     Read length bytes into a buffer 
//     Read the lenth of the binary rule object
//     allocate a buffer for the binary rule object
//     Read length bytes into the buffer;
//     Call ExpBlobToParsed() to convert the rule into a parsed expression and save it
//     free the buffers
//   
/////////////////////////////////////////////////////////////////////////////
void Rule::Read( CryptoFile& file )
{
   long int size;
   int length, i;

   file.ReadQString( m_id );  // read m_id string from file

   file.Read( &m_1RuleFileIdx, sizeof( int ) );    // SAC 4/10/13 - added to aid in debugging
   file.Read( &m_ruleLineNum , sizeof( int ) );

   file.Read( &m_numIndirections, sizeof( int ) );  // read # indirections
   for (i = 0; i < m_numIndirections; i++ )
      file.Read( &m_databaseID[ i ], sizeof( long ) );  // read each database ID

   for (i = 0; i < MAX_NUM_INDIRECTIONS; i++ )  // SAC 4/11/13 - storage of ancestor tree
      file.Read( &m_ancestorObjTypes[ i ], sizeof( int ) );

   file.Read( &size, sizeof( long int ) );  // read size of rule expression buffer
   
   if ( size == 0 )
      ; // Error: The rule didn't parse and there is no blob.
   else
   {
      void *blob = malloc( (UINT)size );
      *(long*)blob = (long)size;
      // read rule expression (in blob format)
      file.Read( &((char*)blob)[ sizeof( long int ) ], (UINT)size - sizeof( long int ) );
      // convert blob expression to parsed expression and store it
      ExpBlobToParsed( &m_parsedExpression, blob );

      free( blob );
   }
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleList
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  RuleList()
//
// Purpose ------------------------------------------------------------------
//   Constructor - inits rulelist name
//   
// Arguments ----------------------------------------------------------------
//   QString& name : name to store in m_name
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// SAC 5/26/03 - added int iLineNumber & const char* pszFileName arguments
RuleList::RuleList( LPCSTR name, bool bSetAllData, bool bAllowMultipleEvaluations, bool bTagAllDataAsUserDefined,
                      int iLineNumber, const char* pszFileName, bool bPerformSetBEMDataResets )  // SAC 9/18/05
{
   m_name = name;
   m_setAllData = bSetAllData;
   m_allowMultipleEvaluations = bAllowMultipleEvaluations;
   m_tagAllDataAsUserDefined = bTagAllDataAsUserDefined;  // SAC 4/2/01
   m_performSetBEMDataResets = bPerformSetBEMDataResets;  // SAC 9/18/05

   m_lineNumber = iLineNumber;  // SAC 5/26/03 - Added to enable reporting of rulelist line number & filename in compiler output
   if (pszFileName)
      m_fileName = pszFileName;
   else
      m_fileName.clear();
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  RuleList()
//
// Purpose ------------------------------------------------------------------
//   Constructor - does nothing
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
RuleList::RuleList()
{
   m_setAllData = TRUE;
   m_allowMultipleEvaluations = TRUE;
   m_tagAllDataAsUserDefined = FALSE;
   m_performSetBEMDataResets = TRUE;  // SAC 9/18/05 - added to facilitate no-reset data setting

   m_lineNumber = 0;  // SAC 5/26/03 - Added to enable reporting of rulelist line number & filename in compiler output
   m_fileName.clear();
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  ~RuleList()
//
// Purpose ------------------------------------------------------------------
//   Destructor - removes all Rules contained in the rulelist
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
RuleList::~RuleList()
{
   RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  GetRule()
//
// Purpose ------------------------------------------------------------------
//   Gets a pointer to the rule object corresponding to the name passed in.
//   
// Arguments ----------------------------------------------------------------
//   QString& name : name of the rule for which a pointer is desired
//   
// Return Value -------------------------------------------------------------
//   Returns NULL if unsuccessful, else returns pointer to the desired Rule.
//   
// Notes --------------------------------------------------------------------
//   Searches the rule list for the rule with the given name
//   
/////////////////////////////////////////////////////////////////////////////
Rule* RuleList::getRule( QString& name )
{
	Rule* rule = NULL;
	for (std::vector<Rule*>::iterator it = m_rules.begin(); (rule == NULL && it != m_rules.end()); ++it)
	{	if ((*it)->getID() == name)
			rule = *it;
	}
	return rule;
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  RemoveAll()
//
// Purpose ------------------------------------------------------------------
//   Delete each rule int the list and then delete the list.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void RuleList::RemoveAll()
{
	for (int i = (int) m_rules.size()-1; i >= 0; i--)
	{	assert( m_rules.at(i) );
		if (m_rules.at(i))
			delete m_rules.at(i);
	}
	m_rules.clear();
}

/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Writes the rulelist to a binary encrypted output file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file      : the binary encrypted file to write the rulelist to
//   QFile&       errorFile : a file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   FALSE if the writing of any rule fails (Rule::Write()), else TRUE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleList::Write( CryptoFile& file, QFile& errorFile )
{
   bool bRetVal = TRUE;
	ruleSet.setDataModelRuleActive( (ruleSet.IsDataModel() && getName().left(3).compare("rl_")==0) );  // SAC 5/26/16 - added to enable combination of data model and procedural rule parsing within a data model ruleset

   // first write the rulelist name to the output file
   file.WriteQString( m_name );

   // then write the rulelist m_setAllData flag
   file.Write( &m_setAllData, sizeof( bool ) );

   // SAC 6/12/00 - added writing of new m_allowMultipleEvaluations flag value (RULESET_STRUCT_VERSION >= 2)
   file.Write( &m_allowMultipleEvaluations, sizeof( bool ) );

   // SAC 4/2/01 - added writing of new m_tagAllDataAsUserDefined flag value (RULESET_STRUCT_VERSION >= 3)
   file.Write( &m_tagAllDataAsUserDefined, sizeof( bool ) );

   // SAC 5/26/03 - Added to enable reporting of rulelist line number & filename in compiler output
   file.Write( &m_lineNumber, sizeof( int ) );
   file.WriteQString( m_fileName );

   // SAC 9/18/05 - added new m_performSetBEMDataResets member to facilitate no-reset data setting
   file.Write( &m_performSetBEMDataResets, sizeof( bool ) );

   // then write the number of rules contained in the rulelist
   int size = (int) m_rules.size();
   file.Write( &size, sizeof( int ) );

	for (int i = 0; i < size; i++)
	{	Rule* rule= m_rules.at(i);			assert( rule );
		if (rule)
		{
#ifdef _DEBUG
			QString dbgMsg = QString( "      Rule: %1 '%2'\n" ).arg( QString::number(i+1), rule->getID() );		// SAC 8/31/16 - added '\n' so as not to interfere w/ YYDEBUG messages
			errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif
			bRetVal = (rule->Write( file, errorFile, m_name.toLocal8Bit().constData() ) && bRetVal);
		}
		else
			bRetVal = FALSE;
	}
	ruleSet.setDataModelRuleActive( (ruleSet.IsDataModel() != FALSE) );  // SAC 5/26/16 - re-default before return

   return bRetVal;
}

bool RuleList::Parse( QFile& errorFile )    // SAC 1/29/18 - similar to Write() but doesn't write rule to file, just keeps it in memory for direct use/evaluation
{
   bool bRetVal = TRUE;
	ruleSet.setDataModelRuleActive( (ruleSet.IsDataModel() && getName().left(3).compare("rl_")==0) );  // SAC 5/26/16 - added to enable combination of data model and procedural rule parsing within a data model ruleset

    // then write the number of rules contained in the rulelist
   int size = (int) m_rules.size();
 	for (int i = 0; i < size; i++)
	{	Rule* rule= m_rules.at(i);			assert( rule );
		if (rule)
		{
#ifdef _DEBUG
			QString dbgMsg = QString( "      Rule: %1 '%2'\n" ).arg( QString::number(i+1), rule->getID() );		// SAC 8/31/16 - added '\n' so as not to interfere w/ YYDEBUG messages
			errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif
			bRetVal = (rule->Parse( errorFile, m_name.toLocal8Bit().constData() ) && bRetVal);
		}
		else
			bRetVal = FALSE;
	}
	ruleSet.setDataModelRuleActive( (ruleSet.IsDataModel() != FALSE) );  // SAC 5/26/16 - re-default before return

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleList Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads the rulelist data out of a binary encrypted file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted file to read the rulelist from
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void RuleList::Read( CryptoFile& file, int iFileStructVer )
{
   int nRules, size = 0;

   file.ReadQString( m_name );  // read rulelist name out of file

   // then write the rulelist m_setAllData flag
   file.Read( &m_setAllData, sizeof( bool ) );

   if (iFileStructVer > 1)
      file.Read( &m_allowMultipleEvaluations, sizeof( bool ) );

   // SAC 4/2/01
   if (iFileStructVer > 2)
      file.Read( &m_tagAllDataAsUserDefined, sizeof( bool ) );

   // SAC 5/26/03 - Added to enable reporting of rulelist line number & filename in compiler output
   if (iFileStructVer > 3)
   {
      file.Read( &m_lineNumber, sizeof( int ) );
      file.ReadQString( m_fileName );  // read rulelist filename out of file
   }
   else
   {
      m_lineNumber = 0;  
      m_fileName.clear();
   }

   // SAC 9/18/05 - added new m_performSetBEMDataResets member to facilitate no-reset data setting
   if (iFileStructVer > 4)
      file.Read( &m_performSetBEMDataResets, sizeof( bool ) );
   else
      m_performSetBEMDataResets = TRUE;

   file.Read( &nRules, sizeof( int ) );		assert( nRules >= 0 );  // get the number of rules from file
   m_rules.resize( nRules );
   while ( size < nRules )  // create and read each rule, then add to the rulelist
   {
      Rule* rule = new Rule;						assert( rule );
      rule->Read( file );
      m_rules[size++] = rule;
   }
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class RuleListList
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  NewList()
//
// Purpose ------------------------------------------------------------------
//   Adds a new rulelist by the name specified to the list of rulelists.
//   
// Arguments ----------------------------------------------------------------
//   QString& name : name of the new rulelist
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// SAC 5/26/03 - added int iLineNumber & const char* pszFileName arguments
void RuleListList::NewList( LPCSTR name, bool bSetAllData, bool bAllowMultipleEvaluations, bool bTagAllDataAsUserDefined,
                             int iLineNumber, const char* pszFileName, bool bPerformSetBEMDataResets )  // SAC 9/18/05
{
   RuleList* newList = new RuleList( name, bSetAllData, bAllowMultipleEvaluations, bTagAllDataAsUserDefined,
                                       iLineNumber, pszFileName, bPerformSetBEMDataResets );			assert( newList );	// create new rulelist
	m_rules.push_back( newList );
   m_currentList = (int) m_rules.size()-1;  // set current rulelistlist position
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  RemoveAll()
//
// Purpose ------------------------------------------------------------------
//   Removes and deletes all rulelists from this list of rulelists.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void RuleListList::RemoveAll()
{
	for (int i = (int) m_rules.size()-1; i >= 0; i--)
	{	assert( m_rules.at(i) );
		if (m_rules.at(i))
			delete m_rules.at(i);
	}
	m_rules.clear();
}

void RuleListList::RemoveTrailing( int iNumListsToDelete )
{	int iLastIdx = (iNumListsToDelete < (int) m_rules.size() ? (int) m_rules.size()-iNumListsToDelete : 0 );
	for (int i = (int) m_rules.size()-1; i >= iLastIdx; i--)
	{	assert( m_rules.at(i) );
		if (m_rules.at(i))
			delete m_rules.at(i);
	}
	if (iLastIdx==0)
		m_rules.clear();
	else
		m_rules.resize(iLastIdx);
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  AddRule()
//
// Purpose ------------------------------------------------------------------
//   Adds a rule to the current rulelist (the last rulelist in the list of rulelists)
//   
// Arguments ----------------------------------------------------------------
//   QString& sRuleID : rule name identifer
//   QString& sDbID   : left side of rule expression
//   QString& sExp    : right side of rule expression
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void RuleListList::AddRule( QString& sRuleID, QString& sDbID, QString& sExp, int i1RuleFileIdx /*=0*/, int iRuleLineNum /*=0*/ )  // SAC 11/7/13
{
   Rule* newRule = new Rule( sRuleID, sDbID, sExp, 1 /*iNumIndirections*/, NULL /*plDBIDs*/, i1RuleFileIdx, iRuleLineNum );  // create new rule
   RuleList* list = m_rules.at( m_currentList );		assert( list );	// get a pointer to the current rulelist
	if (list)
		list->addRule( newRule );
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  getRuleList()
//
// Purpose ------------------------------------------------------------------
//   Get a pointer to the rulelist of the specified name.
//   
// Arguments ----------------------------------------------------------------
//   QString& name : the name of the rulelist for which a pointer it desired
//   
// Return Value -------------------------------------------------------------
//   NULL if hte rulelist is not found, else a pointer to the desired rulelist.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
RuleList* RuleListList::getRuleList( LPCSTR name )
{
	RuleList* list = NULL;
	for (std::vector<RuleList*>::iterator it = m_rules.begin(); (list == NULL && it != m_rules.end()); ++it)
	{	if ((*it)->getName() == name)
			list = *it;
	}
	return list;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  IsFirstRuleList()
//
// Purpose ------------------------------------------------------------------
//   Determine whether or not the specified rulelist is the first one.
//
// Arguments ----------------------------------------------------------------
//   RuleList* list : a pointer to the rulelist in question
//   
// Return Value -------------------------------------------------------------
//   TRUE if the specified rulelist is the first one in the list of rulelists,
//   else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleListList::IsFirstRuleList( RuleList* list )
{
   RuleList* ruleList = m_rules.at(0);
   return (ruleList == list);
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  EvalList()
//
// Purpose ------------------------------------------------------------------
//   Evaluates all rules contained in the specified rulelist.
//   
// Arguments ----------------------------------------------------------------
//   QString& listName : name of the rulelist to evaluate all the rules of
//   
// Return Value -------------------------------------------------------------
//   TRUE if a rulelist by the selected name is found, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     loop over the list given by listName
//     {
//        Get the next rule
//        Get the database id for the name of the rule.
//        Evaluate the rule and call SetValue() to save the value;
//     }
//   
/////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG_EVALLIST  // SAC 12/14/01 - Debugging stuff added
static int siNestingsize = 0;
static QString ssNestingMsg = "\n";
#endif

bool RuleListList::EvalListDuringEval( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined /*=FALSE*/ )  // SAC 8/6/10 - added to make mid-eval rulelist evals more convenient
{
   assert( pEval );
   if (pEval == NULL)
      return false;
   return EvalList( pEval->sRulelistToEvaluate.toLocal8Bit().constData(), bTagDataAsUserDefined, pEval->iRulelistEvalClass, pEval->eRulelistEvalObjType,
                    &pEval->maRulelistEvalObjIdxs, pEval->bVerboseOutput, pEval->pTargetedDebugInfo, pEval->plRuleEvalCount );
}

bool RuleListList::EvalList( LPCSTR listName, BOOL bTagDataAsUserDefined,
                              int iEvalOnlyClass /*=0*/,                  // SAC 5/26/00
                              BEM_ObjType eEvalOnlyObjType /*=BEMO_User*/,  // SAC 5/26/00
                              std::vector<int>* piaEvalOnlyObjs /*=NULL*/,      // SAC 5/26/00
                              BOOL bVerboseOutput /*=FALSE*/,             // SAC 9/25/02
                              BEMCompNameTypePropArray* pTargetedDebugInfo /*=NULL*/,        // SAC 8/5/10 - added pvTargetedDebugInfo argument
										long* plRuleEvalCount /*=NULL*/,            // SAC 10/12/11 - to facilitate summing of each individual rule evaluation
										QStringList* psaWarningMsgs /*=NULL*/ )     // SAC 3/2/18 - added to enable Warning message tracking during normal list evaluation
{
   int iRound = 1;
   RuleList* list = getRuleList( listName );  // get the desired rulelist

	m_iNestedListEvalCount++;		// SAC 8/6/13 - added to prevent recursive rulelist evaluations from bombing system
	if (getAbortRuleEvaluation())
   	list = NULL;  // prevent evaluation of this rulelist
	else
	{	if (m_iNestedListEvalCount > m_iPeakNestedListEvalCount)
			m_iPeakNestedListEvalCount = m_iNestedListEvalCount;
		if (m_iNestedListEvalCount > m_iMaxNestedListEvalCount)
		{	assert( FALSE );	// too much rulelist eval nesting
			QString sErrMsg;
			sErrMsg = QString( "Error:  Maximum nested rulelist evaluations reached attempting to evaluate '%1'." ).arg( listName );
	      BEMPX_WriteLogFile( sErrMsg );
			ruleSet.AddErrorMessage( sErrMsg.toLocal8Bit().constData() );
			setAbortRuleEvaluationFlag( true );  // Critical error - all further processing should be aborted
	   	list = NULL;  // prevent evaluation of this rulelist
		}
	}

	bool bWarningMsgTracking = false;	// SAC 3/2/18
	if (list && pssaWarningMsgs == NULL && psaWarningMsgs)
	{	pssaWarningMsgs = psaWarningMsgs;
		bWarningMsgTracking = true;
	}

   while (list && iRound > 0 && !getAbortRuleEvaluation())
   {
// DEBUGGING
// QString sDbgMsg;

      // SAC 9/14/10 - added new debugging feature to turn on verbose logging only for specified rulelists
      // BOOL bTurnOnVerboseForThisList = FALSE;    - no need to track situations where the Verbose flag is toggled on via this mechanism (??)
      if (!bVerboseOutput && pTargetedDebugInfo && pTargetedDebugInfo->RulelistMatchExists( listName ))
      {  // bTurnOnVerboseForThisList = TRUE;
         bVerboseOutput = TRUE;
// sDbgMsg = QString( "Verbose flag toggled ON to evaluate rulelist: '%1'" ).arg( listName );
      }
// else if (bVerboseOutput && listName.indexOf( "_airHP" ) >= 0)
// sDbgMsg = QString( "Verbose flag already on to evaluate rulelist: '%1'" ).arg( listName );
// else if (listName.indexOf( "_airHP" ) >= 0)
// { if (pTargetedDebugInfo == NULL)
//   sDbgMsg = QString( "Verbose flag off and (pTargetedDebugInfo == NULL) to evaluate rulelist: '%1'" ).arg( listName );
//   else
//   sDbgMsg = QString( "Verbose flag off and no rulelist name match to evaluate rulelist: '%1'" ).arg( listName );
// }
// if (!sDbgMsg.isEmpty())
//   BEMMessageBox( sDbgMsg, "RuleListList::EvalList() Verbose Flag", 3 /*error*/ );

      // SAC 9/25/02 - added code to implement verbose debug output
      QString sDebug, sDebug2;
      if (bVerboseOutput)
      {
         sDebug  = "   EVALUATING RULELIST:  " + QString(listName);
         if (piaEvalOnlyObjs  &&  piaEvalOnlyObjs->size() > 0)
         {
            int iError;
            BEMClass* pDbgClass = (iEvalOnlyClass < 1 ? NULL : BEMPX_GetClass( iEvalOnlyClass, iError ));
            if (pDbgClass && !pDbgClass->getShortName().isEmpty())
               sDebug2 = QString( "  (on %1 specific %2 components)" ).arg( QString::number(piaEvalOnlyObjs->size()), pDbgClass->getShortName() );
            else
               sDebug2 = QString( "  (on %1 specific components)" ).arg( QString::number(piaEvalOnlyObjs->size()) );
            sDebug += sDebug2;
         }
         else
            sDebug += "  (on all components)";
         BEMPX_WriteLogFile( sDebug );
      }

#ifdef DEBUG_EVALLIST  // SAC 12/14/01 - Debugging stuff added
      for (int iNT=0; iNT<siNestingsize; iNT++)
         ssNestingMsg += "    ";
      QString sNestTemp;
      sNestTemp = QString( "%1 round %2 beginning\n" ).arg( listName, QString::number(iRound) );
      ssNestingMsg += sNestTemp;
      siNestingsize++;
      DWORD dwTicksize = GetTicksize();
#endif

      bool bEvalAgain = false;
//      bool bIsFirst   = IsFirstRuleList( list );  // set flag indicating whether or not this is the first rulelist
      int iNumRulesEvaled = 0;  // set flag which tracks number of evaluated rules
      int iNumRules = list->getRuleCount();
      // loop over all rules in the rulelist
		for (int iRl=0; (iRl<iNumRules && !getAbortRuleEvaluation()); iRl++)
		{	Rule* rule = list->getRule( iRl );					assert( rule );
         if (rule != NULL)
         {  
            // SAC 5/26/00 - added code to implement rulelist evaluation for only a subset of components
            int i1Class = BEMPX_GetClassID( rule->getDatabaseID(  0 ) );
            BOOL bLimitedObjects = (piaEvalOnlyObjs  &&  piaEvalOnlyObjs->size() > 0);
            if (bLimitedObjects  &&  i1Class != iEvalOnlyClass)
            {
               // do nothing - this rule applies to a component type other than the subset of components
               //              for which we are evaluating this rulelist.
            }
            else
            {
               // evaluate the rule
               ExpEvalStruct eval;
               int iCompDataType = BEMPX_GetCompDataType( rule->getDatabaseID( rule->getNumIndirections()-1 ) );
               // Set status flag to be used to flag data set to building database
               eval.eLocStatus = ( (bTagDataAsUserDefined || list->getTagAllDataAsUserDefined()) ? BEMS_UserDefined :
                                   ( ( iCompDataType == BEMD_Default     || 
                                       iCompDataType == BEMD_CriticalDef ) ?
                                           BEMS_RuleDefault : BEMS_RuleDefined ) );

               // set bEval TRUE if a flag is set indicating that ALL rules are to be evaluated, or if the compliance datatype is Prescribed or NotInput
               bool bEval = (list->getSetAllData() || /*iCompDataType == BEMD_Prescribed ||*/ iCompDataType == BEMD_NotInput);		// SAC 4/4/13 - modified to prevent overwrite of user data for Prescribed values (when bSetAllData not TRUE)

               // SAC 9/25/02 - added code to implement verbose debug output
               eval.bVerboseOutput = bVerboseOutput;
               if (bVerboseOutput)
               {
                  sDebug = QString( "      %1  --  List: '%2'" ).arg( rule->getID(), listName );
                  BEMPX_WriteLogFile( sDebug );
               }

            // SAC 8/5/10 - added to enable targeted verbose debug output
               eval.pTargetedDebugInfo = pTargetedDebugInfo;
               eval.iNumTargetedDebugItems = (pTargetedDebugInfo == NULL ? 0 : pTargetedDebugInfo->getCompNameTypePropCount());
               eval.pRuleBeingEvaled = rule;
               eval.sRuleListName = listName;

               // loop over all object types
               // SAC 5/26/00 - added code to implement rulelist evaluation for only a subset of components
               int iFirstObjType = (bLimitedObjects ? eEvalOnlyObjType : 0 );
               int iLastObjType  = (bLimitedObjects ? eEvalOnlyObjType : BEMO_NumTypes-1 );
               for (int iObjType=iFirstObjType; (iObjType <= iLastObjType && !getAbortRuleEvaluation()); iObjType++)
               {
                  BEM_ObjType eObjType = (BEM_ObjType) iObjType;

                  // loop over BEMProc objects (including indirections)
                  // SAC 5/26/00 - added code to implement rulelist evaluation for only a subset of components
                  int iLastObjIdx = (int) (bLimitedObjects ? piaEvalOnlyObjs->size()-1 : BEMPX_GetNumObjects( i1Class, eObjType )-1 );
                  for (int iObjIdx=0; (iObjIdx<=iLastObjIdx && !getAbortRuleEvaluation()); iObjIdx++)
                  {
                     int iPrimObj = (bLimitedObjects ? (int) piaEvalOnlyObjs->at( iObjIdx ) : iObjIdx );
                     int iError = 0;
                     BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iPrimObj, eObjType );
                     if ( (iError >= 0) && (pObj != NULL) &&
                          ( (eObjType == BEMO_User) || (pObj->getUserReferenced()) ) )
                     {
							   // we now have either a user-defined object or a library object
                        // which is referenced by a user-defined object
                        eval.lPrimDBID     = rule->getDatabaseID( 0 );
                        eval.iPrimObjIdx   = iPrimObj;
                        eval.ePrimObjType  = eObjType;

                        // set occurrence index for primary object's parent
                        eval.iPrimPar1Class = 0;
                        eval.iPrimParObjIdx = -1;
                        eval.ePrimParObjType = BEMO_NumTypes;
                        eval.iPrimPar2Class = 0;
                        eval.iPrimPar2ObjIdx = -1;
                        eval.ePrimPar2ObjType = BEMO_NumTypes;
                        eval.iPrimPar3Class = 0;
                        eval.iPrimPar3ObjIdx = -1;
                        eval.ePrimPar3ObjType = BEMO_NumTypes;
                        if (pObj->getParent() && pObj->getParent()->getClass())  // FIRST Level Parent
                        {  eval.iPrimPar1Class  = pObj->getParent()->getClass()->get1BEMClassIdx();
                           eval.ePrimParObjType = pObj->getParent()->getObjectType();
                           eval.iPrimParObjIdx  = BEMPX_GetObjectIndex( pObj->getParent()->getClass(), pObj->getParent() );
                           if (pObj->getParent()->getParent() && pObj->getParent()->getParent()->getClass())  // SECOND Level Parent
                           {  eval.iPrimPar2Class   = pObj->getParent()->getParent()->getClass()->get1BEMClassIdx();
                              eval.ePrimPar2ObjType = pObj->getParent()->getParent()->getObjectType();
                              eval.iPrimPar2ObjIdx  = BEMPX_GetObjectIndex( pObj->getParent()->getParent()->getClass(), pObj->getParent()->getParent() );
                              if (pObj->getParent()->getParent()->getParent() && pObj->getParent()->getParent()->getParent()->getClass())  // THIRD Level Parent
                              {  eval.iPrimPar3Class   = pObj->getParent()->getParent()->getParent()->getClass()->get1BEMClassIdx();
                                 eval.ePrimPar3ObjType = pObj->getParent()->getParent()->getParent()->getObjectType();
                                 eval.iPrimPar3ObjIdx  = BEMPX_GetObjectIndex( pObj->getParent()->getParent()->getParent()->getClass(), pObj->getParent()->getParent()->getParent() );
                              }
                           }
                        }

                        BEMObject* pPrimObj = pObj;
                        int iObj = iPrimObj;
                        BEM_ObjType eObjTyp = eObjType;

                        int iIndir = 0;
                        // traverse all rule indirections to get to the actual data to be set
                        while (pObj && ++iIndir < rule->getNumIndirections())	// was only a single '&'
                        {
                           int iDataType, iError, iSpecialVal;
                           pObj = BEMPX_GetObjectPtr( rule->getDatabaseID( iIndir-1 ),
                                                      iSpecialVal, iError, iObj, eObjTyp );
                           if (iError >= 0 && pObj)
                           {
                              eObjTyp = pObj->getObjectType();
                              iObj = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
                           }
                           else
                              pObj = NULL;
                        }

                        if (pObj != NULL)
                        {  // We have valid primary & secondary objects - so evaluate
                           bool bLocalEval = bEval;
                           if (!bLocalEval)
                           {  // allow evaluation if user has NOT entered a value yet
                              int iDataStatus = BEMPX_GetDataStatus( rule->getDatabaseID( rule->getNumIndirections()-1 ),
                                                                     iObj, eObjTyp );
                              bLocalEval = ( (iDataStatus == BEMS_Undefined  ) ||
                                             (iDataStatus == BEMS_ProgDefault) ||
                                             (iDataStatus == BEMS_RuleDefault) ||
                                             (iDataStatus == BEMS_RuleDefined) ||
                                       //      (iDataStatus == BEMS_UserDefault) ||    // SAC 11/27/99 - removed to prevent overwriting UserDefault values
                                             (iDataStatus == BEMS_SimResult  ) );
                              // => don't override if status =  BEMS_RuleLibrary, BEMS_UserLibrary or BEMS_UserDefined
                           }

                           // SAC 3/20/99 - ensure that "Action" rules get evaluated
                           if ( !bLocalEval && BEMPX_GetPropertyID( rule->getDatabaseID( rule->getNumIndirections()-1 ) ) == 0 &&
                                             ( BEMPX_GetArrayID(    rule->getDatabaseID( rule->getNumIndirections()-1 ) ) == BEM_PARAM0_ACTION  ||
															  BEMPX_GetArrayID(    rule->getDatabaseID( rule->getNumIndirections()-1 ) ) == BEM_PARAM0_NAME    ||   // SAC 4/20/12 - added conditions for Name & Parent - to ensure that they get evaluated
															  BEMPX_GetArrayID(    rule->getDatabaseID( rule->getNumIndirections()-1 ) ) == BEM_PARAM0_PARENT ) )
                              bLocalEval = TRUE;

                           if (bLocalEval)
                           {
							// SAC 4/11/13 - code to verify valid parent ancestry prior to evaluating the rule
										BOOL bParentAncestryOK = TRUE;
										if (rule->getAncestorObjType(0) > 0)
										{	int iPTAIdx = -1;
		                  		   BEMObject* pChldObj = pPrimObj;
											QString sAncErrMsg;
											while (bParentAncestryOK && ++iPTAIdx < MAX_NUM_INDIRECTIONS && rule->getAncestorObjType(iPTAIdx) > 0)
											{	if (pChldObj->getParent() == NULL)
												{	// No parent to traverse
													bParentAncestryOK = FALSE;
													if (bVerboseOutput)
													{	BEMClass* pMissingCls = BEMPX_GetClass( rule->getAncestorObjType(iPTAIdx), iError );
														sAncErrMsg = QString( "Parent of %1 '%2' not found (expecting %3)" ).arg( pChldObj->getClass()->getShortName(), pChldObj->getName(),
																																				(pMissingCls ? pMissingCls->getShortName() : "<unknown>") );
													}
												}
												else if (pChldObj->getParent()->getClass() == NULL || pChldObj->getParent()->getClass()->get1BEMClassIdx() != rule->getAncestorObjType(iPTAIdx))
												{	// Parent types do not match
													bParentAncestryOK = FALSE;
													if (bVerboseOutput)
													{	BEMClass* pMissingCls = BEMPX_GetClass( rule->getAncestorObjType(iPTAIdx), iError );
														sAncErrMsg = QString( "Parent of %1 '%2' is %3 '%4' (not a %5)" ).arg( pChldObj->getClass()->getShortName(), pChldObj->getName(),
																	pChldObj->getParent()->getClass()->getShortName(), pChldObj->getParent()->getName(), (pMissingCls ? pMissingCls->getShortName() : "<unknown>") );
													}
												}
												else
				            		         pChldObj = pChldObj->getParent();
											}
											if (!bParentAncestryOK && bVerboseOutput)
											{	assert( !sAncErrMsg.isEmpty() );
												QString sAncErrMsg2, sAncErrMsg3;
								   		   BEMPX_DBIDToDBCompParamString( rule->getDatabaseID( rule->getNumIndirections()-1 ), sAncErrMsg3 );
							      		   sAncErrMsg2 = QString( "                   '%1' %2 -> not evaluated due to parent ancestry:  %3     (rulelist: '%4')" ).arg(
															pObj->getName(), sAncErrMsg3, sAncErrMsg, eval.sRuleListName );
										      BEMPX_WriteLogFile( sAncErrMsg2 );
											}
										}
							// SAC 4/11/13 - end of - code to verify valid parent ancestry prior to evaluating the rule

										if (bParentAncestryOK)
										{
										   // EVALUATE RULE
                        	      eval.lLocDBID   = rule->getDatabaseID( rule->getNumIndirections()-1 );
                        	      eval.iLocObjIdx = iObj;
                        	      eval.eLocObjType = eObjTyp;

                        	      // SAC 3/20/99 - added for post-eval rulelist evaluation
                        	      eval.sRulelistToEvaluate.clear();
                        	      // SAC 5/26/00 - added for post-eval rulelist evaluation
                        	      eval.iRulelistEvalClass = i1Class;
                        	      eval.eRulelistEvalObjType = eval.ePrimObjType;
                        	      eval.maRulelistEvalObjIdxs.clear();

                        	      // SAC 3/24/99 - added to enable flexibility in assigning user vs. rule lib components
                        	      //eval.eNewObjType = BEMO_RuleLib;
                        	      // SAC 4/28/99 - switched default NewObjType to BEMO_User -> gets switched back to RuleLib only if RuleLib function is called
                        	      eval.eNewObjType = BEMO_User;
                        	   //   eval.bImportUniqueRuleLibObjects = FALSE;  // SAC 3/10/13 - added to cause rule library imports to create new objects with each RuleLib evaluation (as opposed to importing only once and providing multiple references to the single imported object)
                        	      eval.iImportUniqueRuleLibObjOption = 2;  // SAC 4/25/14 - switched from BOOL (abv) to int: 0-ImportOnlyIfUnique / 1-ImportAlways / 2-EnsureLibraryName (new DEFAULT setting)
											eval.sImportRuleLibParentName.clear();  // SAC 3/17/13 - name of parent of rule lib object to import

											// SAC 2/5/06 - Added members to keep track of components deleted during evaluation of the current rule
                        	      eval.maDeletedClassIDs.clear();
                        	      eval.maDeletedObjIdxs.clear();

                        	      eval.bEvalItemADebugTarget = (eval.iNumTargetedDebugItems < 1 ? FALSE : eval.pTargetedDebugInfo->MatchExists( eval.lLocDBID, iObj ));   // SAC 8/6/10 - targeted debugging
                        	      eval.bRuleIDLogged = FALSE;

               						eval.plRuleEvalCount = plRuleEvalCount;   // SAC 10/12/11 - facilitates nested rule evaluation sizeing

                        	      // evaluate rule
                        	      if (rule->Eval( &eval, bTagDataAsUserDefined, list->getPerformSetBEMDataResets() ))  // SAC 9/18/05
                        	         bEvalAgain = true;
                        	      iNumRulesEvaled++;
											if (plRuleEvalCount)   // SAC 10/12/11
												*plRuleEvalCount += 1;

											// SAC 2/5/06 - Added code to adjust object index loop to acsize for deleted components
                        	      if (!bLimitedObjects && eval.maDeletedClassIDs.size() > 0)
                        	      {
                        	         int iPrevDels=0, iLaterDels=0, iCurDel=0;
                        	         for (int iDIdx=0; iDIdx < (int) eval.maDeletedClassIDs.size(); iDIdx++)
                        	            if (eval.maDeletedClassIDs[iDIdx] == (WORD) i1Class)
                        	            {
                        	               if (eval.maDeletedObjIdxs[iDIdx] > iObjIdx)
                        	                  iLaterDels++;  // an object later in the list was deleted, so simply reduce number of objects to be looped over
                        	               else if (eval.maDeletedObjIdxs[iDIdx] == iObjIdx)
                        	                  iCurDel++;
                        	               else
                        	                  iPrevDels++;
                        	            }
                        	         assert( iCurDel < 2 );
                        	         assert( (iPrevDels+iLaterDels+iCurDel-1) <= iLastObjIdx );
                        	         iLastObjIdx -= (iPrevDels+iCurDel+iLaterDels);
                        	         iObjIdx     -= (iPrevDels+iCurDel           );
                        	      }
                        	   }
                        	}
								}
                     }
                  }
               }
            }
         }
      }

#ifdef DEBUG_EVALLIST  // SAC 12/14/01 - Debugging stuff added
      float fDeltaTick = (float) (GetTicksize() - dwTicksize);
      siNestingsize--;
      for (iNT=0; iNT<siNestingsize; iNT++)
         ssNestingMsg += "    ";
      if (iNumRulesEvaled > 0)
            sNestTemp.sprintf( "%s round %d done - %g msecs - %.3f msecs/rule\n",    listName, iRound, fDeltaTick, (fDeltaTick / iNumRulesEvaled) );
      else  sNestTemp.sprintf( "%s round %d done - %g msecs - NO rules evaluated\n", listName, iRound, fDeltaTick );
      ssNestingMsg += sNestTemp;
      if (siNestingsize == 0)
      {
         BEMPX_WriteLogFile( ssNestingMsg );
         ssNestingMsg = "\n";
      }
#endif

      // SAC 4/11/99 - added this code to cause rulelist to be re-evaluated -> necessary when a
      //               library assignment causes a new user component to be created
      // SAC 7/1/99 - Added "&& !list->getSetAllData()" to if statement so that only Input rulelists may be reevaluated
      // SAC 6/12/00 - Added reference to m_allowMultipleEvaluations flag to enable rulelists to enable/disable multiple evaluations
      if (bEvalAgain  &&  iRound < 3  &&  !list->getSetAllData()  &&  list->getAllowMultipleEvaluations())
      {	//assert( iRound == 1 );
         iRound++;
      }
      else
         iRound = 0;
   }

   // Notify user of number of rules evaluated
//   BEMMessageBox( QString( "Number of rules evaluated = %1" ).arg( QString::number(iNumRulesEvaled) ), "EvalList() Finished", 3 /*error*/ );

	m_iNestedListEvalCount--;  // SAC 8/6/13 - added to prevent recursive rulelist evaluations from bombing system
			assert( m_iNestedListEvalCount >= 0 );

	if (bWarningMsgTracking)	// SAC 3/2/18
		pssaWarningMsgs = NULL;

   return (list != NULL);
}


// SAC 5/21/01 - Added function similar to EvalList(), only the rules therein are designed to populate the error and warning message lists
bool RuleListList::EvalErrorCheckList( LPCSTR listName, QStringList& saErrorMsgs, QStringList& saWarningMsgs,
                                        int iEvalOnlyClass, int iEvalOnlyOccur )
{
   bool bRetVal = FALSE;
   pssaErrorMsgs = &saErrorMsgs;
   pssaWarningMsgs = &saWarningMsgs;

   if (iEvalOnlyOccur >= 0  &&  iEvalOnlyClass > 0  &&  iEvalOnlyClass <= BEMPX_GetNumClasses())
   {
      std::vector<int> iaObjIdx;
      iaObjIdx.push_back( iEvalOnlyOccur );
      bRetVal = ruleSet.EvaluateRuleList( listName, FALSE, iEvalOnlyClass, BEMO_User, &iaObjIdx );
   }
   else
      bRetVal = ruleSet.EvaluateRuleList( listName );

   pssaErrorMsgs = NULL;
   pssaWarningMsgs = NULL;

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Writes the list of rulelists to the binary encrypted output file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file      : the binary encrypted file to write the list of rulelists to
//   QFile&       errorFile : a file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if all rulelists are written without any failures, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     Open the rule file
//     Write the number of rule lists
//     loop over the list of lists
//        Write the rule list;
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleListList::Write( CryptoFile& file, QFile& errorFile )
{
   bool bRetVal = TRUE;

   int size = (int) m_rules.size();
   file.Write( &size, sizeof( int ) );  // write the number of rulelists

   // loop over all rulelists, writing each to the output file
   for (int i=0; i<size; i++)
   {	RuleList* ruleList = m_rules.at(i);				assert( ruleList );
      if (ruleList)
      {
#ifdef _DEBUG
         QString dbgMsg;
         dbgMsg = QString::number(ruleList->getRuleCount());
         dbgMsg = "\n   Writing " + dbgMsg;
         dbgMsg += " rules for rulelist '";
         dbgMsg += ruleList->getName();   dbgMsg += "'\n";
         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif
         bRetVal = ((ruleList->Write( file, errorFile )) && (bRetVal));
      }
      else
         bRetVal = FALSE;
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a list of rulelists from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read the rulelists from
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     Read the number of rule lists
//     loop over the list of lists
//        Read the rule list;
//        Add it to the list of lists
//   
/////////////////////////////////////////////////////////////////////////////
void RuleListList::Read( CryptoFile& file, int iFileStructVer )
{
   RemoveAll();

   int nLists;
   file.Read( &nLists, sizeof( int ) );  // get the number of rulelists

   int size = 0;
   while ( size < nLists )
   {  // create and read all rulelists contained in file
   //   QString name = "";
   //   NewList( name.toLocal8Bit().constData() );
      NewList( "" );
      (m_rules.at( m_currentList ))->Read( file, iFileStructVer );
      size++;
   }

	m_iNestedListEvalCount = 0;  // SAC 8/6/13
	m_iPeakNestedListEvalCount = 0;
	m_iMaxNestedListEvalCount = 100;
	setAbortRuleEvaluationFlag( false );
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleListList Class Function:  InitRules()
//
// Purpose ------------------------------------------------------------------
//   Reinitializes all rulelists, deleting all rules in each.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void RuleListList::InitRules()
{
	m_iNestedListEvalCount = 0;  // SAC 8/6/13
	m_iPeakNestedListEvalCount = 0;
	setAbortRuleEvaluationFlag( false );
   if (m_rules.size() > 0)
      RemoveAll();
}


int  RuleListList::getRulelistNames( QVector<QString>& sRulelistNames )
{
   int iNumLists = 0;
   int size = (int) m_rules.size();
   for (int i=0; i<size; i++)
   {	RuleList* ruleList = m_rules.at(i);				assert( ruleList );
      if (ruleList)
      {
         sRulelistNames.push_back( ruleList->getName() );
         iNumLists++;
      }
   }
   return iNumLists;
}


