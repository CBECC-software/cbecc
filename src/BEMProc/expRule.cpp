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
#include "expRule.h"
#include "expRuleList.h"
#include "expRuleFile.h"
// TO OPENSRC ?
//#include "RulPrc.h"
//#include "..\BEMProcI.h"
#include "expyy.h"
#include "BEMProcObject.h"
#include "BEMPropertyType.h"
#include "BEMProperty.h"
#include "BEMClass.h"
#include "BEMProc.h"
#include "BEMProc_FileIO.h"

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <map>
#include "memLkRpt.h"
using namespace std;
using namespace boost::assign;



// SAC 5/21/01 - added pointers to string arrays to facilitate detailed, rule-based BEMProc error/range checking
QStringList* pssaErrorMsgs = NULL;
QStringList* pssaWarningMsgs = NULL;


// SAC 10/24/02 - added new arrays to facilitate new NumDaysInMoDaRange() function
static int iNumDaysInMonth[       12] = {  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };
                                            //  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31
static int iNumDaysInPrevMonths[  12] = {   0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334 };
                                  //  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31
static int iNumDaysInSubseqMonths[12] = { 334, 306, 275, 245, 214, 184, 153, 122,  92,  61,  31,   0 };


static inline BOOL IsReserved_UNDEFINED( double dVal )
   {	return WithinMargin( dVal, -99996.0, 0.1 );  };
static inline BOOL IsReserved_UNCHANGED( double dVal )
   {	return WithinMargin( dVal, -99997.0, 0.1 );  };
static inline BOOL IsReserved_NONE( double dVal )
   {	return WithinMargin( dVal, -99998.0, 0.1 );  };
static inline BOOL IsReserved_DEFAULT( double dVal )
   {	return WithinMargin( dVal, -99999.0, 0.1 );  };


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// SAC 5/1/05 - Converted several routines previously exported from RulExp32.dll into inlines here

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpxStackPush()
//
// Purpose ------------------------------------------------------------------
//   Pushes an expression node onto the stack.
//   
// Arguments ----------------------------------------------------------------
//   ExpStack* stack : pointer to the stack to push the node onto
//   ExpNode*  node  : pointer to the node to be pushed onto the stack
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline void ExpxStackPush( ExpStack* stack, ExpNode* node )
{
   ExpStackPush( stack, node );
}

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpxStackPop()
//
// Purpose ------------------------------------------------------------------
//   Pops a node off the stack.
//   
// Arguments ----------------------------------------------------------------
//   ExpStack* stack  : pointer to the stack to pop the top node off
//   
// Return Value -------------------------------------------------------------
//   A pointer to the node which is popped off the stack.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline ExpNode* ExpxStackPop( ExpStack* stack )
{
   ExpNode* pNode = ExpStackPop( stack );
   return pNode;
}

/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpxNodeDelete()
//
// Purpose ------------------------------------------------------------------
//   Deletes the specified node.
//   
// Arguments ----------------------------------------------------------------
//   ExpNode* pNode  : a pointer to the node to be deleted
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
inline void ExpxNodeDelete( ExpNode* pNode )
{
   ExpNodeDelete( pNode );
}

inline void XExpAddBldgElemNode(long long dbId)
{
   ExpAddBldgElemNode( dbId );
}

inline void XExpAddFunctionNodeByOpType( int iOpType, int nArgs )  // SAC 7/9/12
{	ExpAddFunctionNodeByOpType( iOpType, nArgs );
}

inline void XAddnArg()
{
   AddnArg();
}


/////////////////////////////////////////////////////////////////////////////
//
// Inline Function:  ExpSetErr()
//
// Purpose ------------------------------------------------------------------
//   Sets errors ensizeered by external functions to the structure which
//   tracks all expression parsing and evaluation errors.
//   
// Arguments ----------------------------------------------------------------
//   ExpError*    pError : structure to communicate errors back to the calling function
//   ExpErrorCode code   : error code (enum defined in formula.h)
//   const char*  text   : error message
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static inline void ExpSetErr( ExpError* pError, ExpErrorCode code, const char* text )
{	ExpSetError( pError, code, text );
}
static inline void ExpSetErr( ExpError* pError, ExpErrorCode code, QString& text )
{	ExpSetError( pError, code, text.toLocal8Bit().constData() );
}

static inline int IntegerInArray( std::vector<int>& iaVals, int& iVal )  // SAC 3/4/10
{	int iSize = (int) iaVals.size();
	for (int j=0; j<iSize; j++)
	{	if (iaVals[j] == iVal)
			return j;
	}
	return -1;
}

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

//////////////////////////////////////////////////////////////////////
// Rule evaluation
typedef enum _keywords
{
   KW_Invalid,
   KW_Default,
   KW_None,
   KW_Unchanged,  // SAC 3/31/01
   KW_Undefined,  // SAC 8/24/01
} RL_Keywords;

//////////////////////////////////////////////////////////////////////
// CCompID Class code - this class tracks the current component ID
int CCompID::GetCurrentCompID()
{  return m_currentID;  }
void CCompID::SetCurrentCompID( int id )
{  m_currentID = id;  }

long CCompID::GetCurrentLocalDBID()
{  return m_lLocalDBID;  }
void CCompID::SetCurrentLocalDBID( long lDBID )
{  m_lLocalDBID = lDBID;  }

void CCompID::GetCurrentRulelistName( QString& sRLName )
{	sRLName = m_sRulelistName;
}
void CCompID::SetCurrentRulelistName( const char* pszRLName )
{	if (pszRLName && strlen( pszRLName ) > 0)
		m_sRulelistName = pszRLName;
	else
		m_sRulelistName.clear();
}

CCompID crntCompID;  // declare an instance of this class which will be referenced throughout this module

// End Of CCompID Class code
//////////////////////////////////////////////////////////////////////


void ThrowBEMPError( QFile& errorFile, QString sParam, QString sId )
{
// SAC 4/25/02 - Revised file output to flag errors w/ "*** ERROR ***" string for easier debug mode searching
// SAC 5/1/13 - include ERROR string in release mode executables
//#ifdef _DEBUG
//   errorFile.Write( "\n*** ERROR ***  parsing: ", 26 );
   errorFile.write( "\nERROR parsing: ", 17 );
//#endif

   QString msg = sId + QString("\n") + sParam;
   msg += QString("\n\tInvalid Component:Parameter String: '") + sParam + QString("'\n\n");
   errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
}

/////////////////////////////////////////////////////////////////////////////

bool ParseRuleDBID( QString& sRuleID, QString& sDBID, int& iNumIndirections, long* plDBIDs, QFile& errorFile )
{
   bool bRetVal = TRUE;

	if (ruleSet.DataModelRuleActive())	// SAC 5/26/16
// trim leading portions of DBID string prior to final (rightmost) Component/Object Type string - ancestor object list to left to be parsed elsewhere
	{	QString sTemp = sDBID;
		int iLastColon = sTemp.lastIndexOf(':');
		if (iLastColon > 0)
		{	sTemp = sTemp.left( iLastColon );
			QString sObjTypeStr;
			int iObjTypeID = -1;
			while (iObjTypeID < 1 && iLastColon < sDBID.length())
			{	iLastColon = sTemp.lastIndexOf(':');
				if (iLastColon < 1)
					iLastColon = sDBID.length();
				else
				{	sObjTypeStr = sTemp.right( sTemp.length()-iLastColon-1 );
					iObjTypeID = BEMP_GetDBComponentID( sObjTypeStr );
					sTemp = sTemp.left( iLastColon );
				}
			}

			if (iLastColon > 0 && iLastColon < sDBID.length())
				sDBID = sDBID.right( sDBID.length()-iLastColon-1 );
		}
	}
	
   // parse the first two tokens into a database ID
   int iRefCompID = 0;  // SAC 7/17/01
	int iNumRefComps = 0;  // SAC 8/28/12
   QString sTempDBID = sDBID;
   long lCompParam = BEMPX_GetDatabaseID( sTempDBID, 0, FALSE, &iRefCompID, &iNumRefComps );
	assert( iNumRefComps < 2 );  // Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
   if (lCompParam < BEM_COMP_MULT)
   {
      ThrowBEMPError( errorFile, sDBID, sRuleID );
      bRetVal = FALSE;
   }

	int iError=0;
   int iNumLevels = 1;
   QString temp = sTempDBID;  // m_dbId;
   temp = temp.right( temp.length() - temp.indexOf(':') - 1 );
   // if the parsed portion of the string is not the end, then the database ID
   // will exceed the maximum of 999999, with the mil & 10-mil digits equalling
   // the component (class) ID to be used in the next call to BEMPX_GetDatabaseID()
   while (iRefCompID > 0)  // lCompParam >= 1000000)
   {
      plDBIDs[ iNumLevels-1 ] = lCompParam;  // % 1000000);

      // str2 = (strip left portion of str off, up to and including the SECOND ':')
      temp = temp.right( temp.length() - temp.indexOf(':') - 1 );

// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into acsize (potentially) mulitple compatible referenced obejct types
      //lCompParam = BEMPX_GetDatabaseID( temp, iRefCompID, FALSE, &iRefCompID );
		BOOL bDBIDValid = FALSE;
		int i2ndRefCompID = iRefCompID;
		long l2ndDBID = lCompParam;
		BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( l2ndDBID, iError );						assert( iError==0 );		assert( pPropType );
		for (int iObjCls=0; (pPropType && !bDBIDValid && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
		{	if (pPropType->getObj1ClassIdx( iObjCls ) > 0)
			{	l2ndDBID = BEMPX_GetDatabaseID( temp, pPropType->getObj1ClassIdx( iObjCls ), FALSE, &i2ndRefCompID, &iNumRefComps );
				assert( iNumRefComps < 2 );  // Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
				if (l2ndDBID > 0)
					bDBIDValid = TRUE;
			}
		}
		// update original variables, regardless of whether the processing successfully returned a valid DBID
		lCompParam = l2ndDBID;
		iRefCompID = i2ndRefCompID;

      if (lCompParam < BEM_COMP_MULT)
      {
         ThrowBEMPError( errorFile, temp, sRuleID );
         bRetVal = FALSE;
      }
      iNumLevels++;
   }

   // set the final number of indirections and the last database ID
   iNumIndirections = iNumLevels;
   plDBIDs[ iNumLevels-1 ] = lCompParam;

   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static const char* pszaDataStatus[] = {	"Undef",		// BEMS_Undefined,  
														"PDef" ,		// BEMS_ProgDefault,
														"RDef" ,		// BEMS_RuleDefault,
														"RLib" ,		// BEMS_RuleLibrary,
														"RVal" ,		// BEMS_RuleDefined,
														"UDef" ,		// BEMS_UserDefault,
														"Ulib" ,		// BEMS_UserLibrary,
														"UVal" ,		// BEMS_UserDefined,
														"SRes" ,		// BEMS_SimResult,  
														"UNKn" };	// BEMS_NumTypes,  
static inline const char* GetDataStatusAbbrev( int iDataStatus )
{	return ((iDataStatus >= BEMS_Undefined && iDataStatus < BEMS_NumTypes) ? pszaDataStatus[iDataStatus] : pszaDataStatus[BEMS_NumTypes]);
}

// SAC 8/7/10 - implementation of targeted debug output
void ReportTargetedDebugInfo( ExpEvalStruct* pEval, int iDataType, long lDBID, int iObjIdx, BEM_ObjType eObjType, QString sCallingFunc, int iBEMProcModel )
{
   assert( pEval && lDBID > 0 && iDataType > 0 );
   if (pEval && lDBID > 0 && iDataType > 0)
   {
		int iDataStatus, iSpecialVal, iError;		long lData=0;		double dData=0;		QString sData;		BEMObject* pObj=NULL;
		if (iDataType == BEMP_Sym || iDataType == BEMP_Int)
		{	lData = BEMPX_GetIntegerAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, iBEMProcModel );
			if (iDataStatus > 0 && iDataType == BEMP_Sym)
				sData = BEMPX_GetSymbolString( lData, lDBID, iObjIdx, eObjType );
		}
		else if (iDataType == BEMP_Flt)
			dData = BEMPX_GetFloatAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, iBEMProcModel );
		else if (iDataType == BEMP_Str)
			sData = BEMPX_GetStringAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, iBEMProcModel );
		else if (iDataType == BEMP_Obj)
			pObj  = BEMPX_GetObjectAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, iBEMProcModel );

      QString sRetrievedData;
		if (iDataStatus == BEMS_Undefined)
         sRetrievedData = "UNDEFINED";
      else if (iDataType == BEMP_Sym)
         sRetrievedData = QString( "%1 (%2) (sym) (%3)" ).arg( sData, QString::number(lData), GetDataStatusAbbrev(iDataStatus) );
      else if (iDataType == BEMP_Int)
         sRetrievedData = QString(      "%1 (int) (%2)" ).arg( QString::number(lData), GetDataStatusAbbrev(iDataStatus) );
      else if (iDataType == BEMP_Flt)
         sRetrievedData = QString(       "%1 (flt) (%2)" ).arg( QString::number(dData), GetDataStatusAbbrev(iDataStatus) );
      else if (iDataType == BEMP_Str)
         sRetrievedData = QString(     "'%1' (str) (%2)" ).arg( sData, GetDataStatusAbbrev(iDataStatus) );
      else if (iDataType == BEMP_Obj)
      {	if (pObj)
				sRetrievedData = QString( "'%1' %2 (obj) (%3)" ).arg( pObj->getName(), pObj->getClass()->getShortName(), GetDataStatusAbbrev(iDataStatus) );
			else
				sRetrievedData = QString( "'NONE' (obj) (%1)" ).arg( GetDataStatusAbbrev(iDataStatus) );
      }

      QString sDebug, sDebug2;
      if (!pEval->bRuleIDLogged)
         sDebug = QString( "      %1  '" ).arg( pEval->pRuleBeingEvaled->getID() );
      else
         sDebug  = "                   '";

      pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError, iObjIdx, eObjType );
      if (pObj) // && !pObj->getName().isEmpty())
         sDebug += pObj->getName();
      else
         sDebug += "<unknown>";
      sDebug += "' ";
      BEMPX_DBIDToDBCompParamString( lDBID, sDebug2 );
      sDebug += sDebug2;
      sDebug += "  -retrieval-  ";
      sDebug += sRetrievedData;
      if (!pEval->bRuleIDLogged)
      {  sDebug2 = QString( "     (rulelist: '%1')" ).arg( pEval->sRuleListName );
         sDebug += sDebug2;
         pEval->bRuleIDLogged = TRUE;
      }

      if (!sCallingFunc.isEmpty())
      {  sDebug2 = QString( "   (via %1)" ).arg( sCallingFunc );
         sDebug += sDebug2;
      }

      BEMPX_WriteLogFile( sDebug );
   }
}

/////////////////////////////////////////////////////////////////////////////

// SAC 8/2/12 - New routine to help identify when errors are logged and prevent further processing when called for
static inline bool ErrorFree( ExpError& expError )
{	return (expError.code == EXP_None || expError.code == EXP_RuleWarn);
}

// Extraction of all BEMProc data setting code out of Rule::Eval() ()
bool LocalSetBEMProcData( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined, BOOL bPerformSetBEMDataResets, ExpNode& node, ExpError& expError )
{
   bool bRetVal = false;
   int iError = 0;

   // SAC 9/25/02 - added code to implement verbose debug output
   QString sDebug, sDebug2;
   if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
   {
      if (!pEval->bVerboseOutput && !pEval->bRuleIDLogged)   // SAC 8/6/10 - start by logging rule ID stuff (if not already written to log)
         sDebug = QString( "      %1  '" ).arg( pEval->pRuleBeingEvaled->getID() );
      else
         sDebug  = "                   '";
      BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lLocDBID ), iError, pEval->iLocObjIdx, pEval->eLocObjType );
      if (pObj && !pObj->getName().isEmpty())
         sDebug += pObj->getName();
      else
         sDebug += "<unknown>";
		// SAC 8/6/10 - added echo of Component:Property string
      sDebug += "' ";
      BEMPX_DBIDToDBCompParamString( pEval->lLocDBID, sDebug2 );
      sDebug += sDebug2;
      sDebug += " -> ";
   }

// --- rule evaluation used to go HERE ---

   // SAC 4/2/01 - Added following if() statement to ensure error messages always written to log file
   if (expError.code != EXP_None)
   {
      QString sMsg = expError.string;
      sMsg += " evaluating rule: ";
      sMsg += pEval->sRuleID;
      BEMPX_WriteLogFile( sMsg );
		if (!ErrorFree( expError ))  // SAC 8/2/12 - keep track of number of errors ensizeered during evaluation of rules
		//	ruleSet.AddErrorMessage( sMsg );
		{  int iLocObjClass = BEMPX_GetClassID( pEval->lLocDBID );		// SAC 4/23/13 - expanded error logging to include other details
	      BEMObject* pLocObj  = BEMPX_GetObjectByClass( iLocObjClass, iError, pEval->iLocObjIdx, pEval->eLocObjType );
	      BEMObject* pPrimObj = (pEval->lLocDBID == pEval->lPrimDBID ? NULL : BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iError, pEval->iPrimObjIdx, pEval->ePrimObjType ));
			ruleSet.AddErrorMessageDetails( sMsg.toLocal8Bit().constData(), iLocObjClass, pEval->lLocDBID, (pLocObj ? pLocObj->getName().toLocal8Bit().constData() : ""),
															(pPrimObj ? BEMPX_GetClassID( pEval->lPrimDBID ) : 0), (pPrimObj ? pPrimObj->getName().toLocal8Bit().constData() : "") );
		}
		if (ruleSet.getLogMsgCallbackFunc())
			ruleSet.getLogMsgCallbackFunc()( expError.code == EXP_RuleWarn ? logMsgWARNING : logMsgERROR, (const char*) sMsg.toLocal8Bit().constData(), NULL );
   }

   int iSetRet = 0;
#define  SetBEMData_ErrMsgLen  256
static char pszSetBEMData_ErrMsg[ SetBEMData_ErrMsgLen ];  // SAC 4/10/13 - error message return

   int iDataType = BEMPX_GetDataType( pEval->lLocDBID );
	BOOL bSetObjToNone = (iDataType == BEMP_Obj && node.type == EXP_String &&	  // SAC 4/10/13 - if object assignment being set to "NONE", then re-default the property
									boost::iequals( (char*) node.pValue, "NONE" ));
   if (iDataType == BEMP_Str && BEMPX_GetPropertyID( pEval->lLocDBID ) == 0 &&
                                BEMPX_GetArrayID(    pEval->lLocDBID ) == BEM_PARAM0_ACTION)
   {  // SAC 3/20/99 - Prevent any data setting if propertytype being set is "Action"
      // SAC 9/25/02 - added code to implement verbose debug output
      if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
         sDebug += "Action (no data modified)";
   }
   else if (node.type == EXP_Value  &&  IsReserved_UNCHANGED( node.fValue ))
   {  // => UNCHANGED => bypass all data changing
      bRetVal = true;

      // SAC 9/25/02 - added code to implement verbose debug output
      if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
         sDebug += "UNCHANGED";
   }
   else if (bSetObjToNone || IsReserved_UNDEFINED( node.fValue ) ||  // SAC 8/24/01  - SAC 4/10/13   - SAC 4/21/17 - revised logic due to removal of union in struct
				(node.type == EXP_String && boost::iequals( (char*) node.pValue, "UNDEFINED" )))  // SAC 1/9/14 - revised to better process UNDEFINED data
//   else if (bSetObjToNone || (node.type == EXP_Value  &&  IsReserved_UNDEFINED( node.fValue )) ||  // SAC 8/24/01  - SAC 4/10/13
//				(node.type == EXP_String && IsReserved_UNDEFINED( node.fValue ) && boost::iequals( (char*) node.pValue, "UNDEFINED" )))  // SAC 1/9/14 - revised to better process UNDEFINED data
   {  // => UNDEFINED => re-default (blast) value
      // SAC 9/18/01 - Revised to ignore return value of BEMPX_DefaultProperty() which only returns true is a user-defined default is installed
      BEMPX_DefaultProperty( pEval->lLocDBID, iError, pEval->iLocObjIdx, pEval->eLocObjType );
      if (iError == 0)
      {  bRetVal = true;
         // SAC 9/25/02 - added code to implement verbose debug output
         if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
            sDebug += "UNDEFINED";  // SAC 2/12/14 - make debug reporting more consistent w/ previous versions - was:  (bSetObjToNone ? "NONE" : "UNDEFINED");
      }
      else
      {  QString sMsg;
			sMsg = QString( "Rule evaluated to '%1' and error was ensizeered resetting BEMProc value for rule: %2" ).arg( (bSetObjToNone ? "NONE" : "UNDEFINED"), pEval->sRuleID );
         BEMPX_WriteLogFile( sMsg );
			if (ruleSet.getLogMsgCallbackFunc())
				ruleSet.getLogMsgCallbackFunc()( logMsgERROR, (const char*) sMsg.toLocal8Bit().constData(), NULL );
      }
   }
   else
   {
      // SET DATA
      long lData;
      double fData;
      void* pData = NULL;
      int iSpecialVal = 0;
      if (node.type == EXP_Value)
      {  // rule evaluated to a numeric
         if ( IsReserved_DEFAULT( node.fValue ) || IsReserved_NONE( node.fValue ) )
         {  // rule evaluated to special values to be passed to the database
            iSpecialVal = (IsReserved_DEFAULT( node.fValue )) ? SV_Default : SV_None;

            // SAC 9/25/02 - added code to implement verbose debug output
            if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
               sDebug += (IsReserved_DEFAULT( node.fValue )) ? "Default (special value)" : "None (special value)";
         }
         else
         {
            if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
            {  // cast double result to integer in preparation for setting database data
               lData = (long) node.fValue;
               pData = (void*) &lData;

               // SAC 9/25/02 - added code to implement verbose debug output
               if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
               {
                  sDebug2 = QString( "%1  (%2)" ).arg( QString::number(lData), (iDataType == BEMP_Int ? "int" : "sym") );
                  sDebug += sDebug2;
               }
            }
            else if (iDataType == BEMP_Flt)
            {
               fData = node.fValue;
               pData = (void*) &fData;

               // SAC 9/25/02 - added code to implement verbose debug output
               if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
               {
                  sDebug2 = QString( "%1  (flt)" ).arg( QString::number(fData) );
                  sDebug += sDebug2;
               }
            }
         }
      }
      else if (node.type == EXP_String)
      {  // rule evaluated to a character string
         if (iDataType == BEMP_Obj || iDataType == BEMP_Sym || iDataType == BEMP_Str)
         {
            iDataType = BEMP_Str;
            pData = node.pValue;

            // SAC 9/25/02 - added code to implement verbose debug output
            if (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget)   // SAC 8/6/10
               sDebug += (char*) node.pValue;
         }
      }

      if (iSpecialVal > 0)
      {  // => set special vs. normal value to database
         iSetRet = BEMPX_SetBEMSpecialValue( pEval->lLocDBID, iSpecialVal, pEval->iLocObjIdx,
                                             pEval->eLocStatus, pEval->eLocObjType );					assert( iSetRet >= 0 );  // perhaps add error message logging here(?)
      }
      else if (pData == NULL)
      {  // if pData == NULL then an error occurred somewhere during the evaluation process
         if (expError.code == EXP_None)
         {
            // QString sMsg = (expError.code != EXP_None) ? expError.string : "Bogus Expression Return Value";
            // sMsg += " evaluating rule: ";
			// SAC 5/1/13 - replace 'bogus' w/ 'ERROR' in error messages (plus track this as an error in the ruleset object)
         //   QString sMsg = "Bogus Expression Return Value evaluating rule: ";
            QString sMsg = "ERROR:  Invalid expression return value evaluating rule: ";
            sMsg += pEval->sRuleID;
				// SAC 3/5/13 - more verbose messaging
				QString sCompID;
				BEMClass* pPrimCls = BEMPX_GetClass( BEMPX_GetClassID( pEval->lPrimDBID ), iError, 0 /*iBEMProcIdx*/ );
				BEMClass* pLocCls  = BEMPX_GetClass( BEMPX_GetClassID( pEval->lLocDBID  ), iError, 0 /*iBEMProcIdx*/ );
				QString sLocName, sPrimName;
				if (pPrimCls && pLocCls && pLocCls->get1BEMClassIdx() > 0)
				{	sLocName = BEMPX_GetString( BEMPX_GetDBID( pLocCls->get1BEMClassIdx(), 0, BEM_PARAM0_NAME ), iSpecialVal, iError, 
                                              pEval->iLocObjIdx, pEval->eLocObjType, 0 /*iBEMProcIdx*/ );
					if (pPrimCls->get1BEMClassIdx() != pLocCls->get1BEMClassIdx())
					{	sPrimName = BEMPX_GetString( BEMPX_GetDBID( pPrimCls->get1BEMClassIdx(), 0, BEM_PARAM0_NAME ), iSpecialVal, iError, 
               											  pEval->iPrimObjIdx, pEval->ePrimObjType, 0 /*iBEMProcIdx*/ );
						sCompID = QString( "  on %1 '%2' and %3 '%4'" ).arg( pPrimCls->getShortName(), sPrimName, pLocCls->getShortName(), sLocName );
					}
					else
						sCompID = QString( "  on %1 '%2'" ).arg( pLocCls->getShortName(), sLocName );
					sMsg += sCompID;
				}
            BEMPX_WriteLogFile( sMsg );
				ruleSet.AddErrorMessageDetails( sMsg.toLocal8Bit().constData(), (pLocCls ? pLocCls->get1BEMClassIdx() : 0), pEval->lLocDBID, sLocName.toLocal8Bit().constData(),
																(pPrimCls ? pPrimCls->get1BEMClassIdx() : 0), sPrimName.toLocal8Bit().constData() );
				if (ruleSet.getLogMsgCallbackFunc())
					ruleSet.getLogMsgCallbackFunc()( logMsgERROR, (const char*) sMsg.toLocal8Bit().constData(), NULL );
         }
      }
      else  // set standard data to database
      {
         // SAC 4/11/99 - added code to catch when a new user component is created via assignment of a library component
         //               => enables us to re-evaluate the RuleList again to ensure the newly created component is properly defaulted
         //int iNumAssignComps = 0, iAssignClassIdx = 0;
         int iaNumAssignComps[BEM_MAX_PROPTYPE_OBJREFCLASSES], iaAssignClassIdx[BEM_MAX_PROPTYPE_OBJREFCLASSES];  // SAC 6/14/12 - revised code to handle MULTIPLE possible assigned component types
			int iObjCls = 0;
			for (; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)
			{	iaNumAssignComps[iObjCls] = 0;
				iaAssignClassIdx[iObjCls] = 0;
			}
         if (iDataType == BEMP_Str && BEMPX_GetDataType( pEval->lLocDBID ) == BEMP_Obj)
         {
            BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( pEval->lLocDBID, iError );
            assert( (iError == 0 && pPropType) );
            if (iError == 0 && pPropType)
            {	for (iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)  // SAC 6/14/12
      	      {	iaAssignClassIdx[iObjCls] = pPropType->getObj1ClassIdx( iObjCls );
               	iaNumAssignComps[iObjCls] = (iaAssignClassIdx[iObjCls] <= 0 ? 0 : BEMPX_GetNumObjects( iaAssignClassIdx[iObjCls] ));
					}
            }
         }

         // SAC 3/24/99 - added reference to pEval->eNewObjType
			memset( pszSetBEMData_ErrMsg, '\0', SetBEMData_ErrMsgLen );  // blast error message from last data setting call
         iSetRet = BEMPX_SetBEMData( pEval->lLocDBID, iDataType, pData, pEval->eNewObjType, pEval->iLocObjIdx, pEval->eLocStatus,
                                  pEval->eLocObjType, bPerformSetBEMDataResets, -1 /*iBEMProcIdx*/,   // SAC 9/18/05 - added bPerformSetBEMDataResets argument
											 pEval->iImportUniqueRuleLibObjOption,   // SAC 3/10/13 - added to cause rule library imports to create new objects with each RuleLib evaluation (as opposed to importing only once and providing multiple references to the single imported object)	// SAC 4/25/14 - revised arg
											 pEval->sImportRuleLibParentName.toLocal8Bit().constData(),   // SAC 3/17/13 - name of parent of rule lib object to import
											 pszSetBEMData_ErrMsg, SetBEMData_ErrMsgLen );  // SAC 4/10/13 - error message return

         // SAC 4/11/99 - (see previous 4/11/99 comment)
         //if (iAssignClassIdx > 0 && BEMPX_GetNumObjects( iAssignClassIdx ) > iNumAssignComps)
			BOOL bNewCompCreated = FALSE;
         for (iObjCls=0; (!bNewCompCreated && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12
      		bNewCompCreated = (iaAssignClassIdx[iObjCls] > 0 && iaNumAssignComps[iObjCls] < BEMPX_GetNumObjects( iaAssignClassIdx[iObjCls] ));
         if (bNewCompCreated)
            bRetVal = true;
      }
   }

   // SAC 9/25/02 - added code to implement verbose debug output
   if ((pEval->bVerboseOutput || pEval->bEvalItemADebugTarget) && !sDebug.isEmpty())   // SAC 8/6/10
   {
      if (!pEval->bRuleIDLogged)   // SAC 8/6/10 - append rulelist ID onto debug string
      {  sDebug2 = QString( "     (rulelist: '%1')" ).arg( pEval->sRuleListName );
         sDebug += sDebug2;
         pEval->bRuleIDLogged = TRUE;
      }

		if (iSetRet < 0 && strlen( pszSetBEMData_ErrMsg ) > 0)  // SAC 4/10/13 - error message logging
		{
         sDebug += "   - Error: ";
         sDebug += pszSetBEMData_ErrMsg;
		}
		
      BEMPX_WriteLogFile( sDebug );
		if (ruleSet.getLogMsgCallbackFunc())
			ruleSet.getLogMsgCallbackFunc()( ((iSetRet < 0 && strlen( pszSetBEMData_ErrMsg ) > 0) ? logMsgERROR : logMsgMESSAGE), (const char*) sDebug.toLocal8Bit().constData(), NULL );
   }
	else if (iSetRet < 0 && strlen( pszSetBEMData_ErrMsg ) > 0)  // SAC 4/10/13 - error message logging
	{	// write log entry if error ensizeered (even if not in verbose mode)
      BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lLocDBID ), iError, pEval->iLocObjIdx, pEval->eLocObjType );
      if (pObj && !pObj->getName().isEmpty())
      	sDebug2 = QString( "  on '%1'" ).arg( pObj->getName() );
      else
         sDebug2.clear();
      sDebug = QString( "Error setting rule data:  %1  -- evaluating rule: %2%3" ).arg( pszSetBEMData_ErrMsg, pEval->sRuleID, sDebug2 );
      BEMPX_WriteLogFile( sDebug );
		if (ruleSet.getLogMsgCallbackFunc())
			ruleSet.getLogMsgCallbackFunc()( logMsgERROR, (const char*) sDebug.toLocal8Bit().constData(), NULL );
   }

   // SAC 3/20/99 - Evaluate another rulelist if pEval->sRulelistToEvaluate contains a string
   if (pEval->sRulelistToEvaluate.length() > 0)
   {
      //// SAC 7/1/99 - DEBUGGING
      //BEMMessageBox( QString( "About to evaluate rulelist: %1" ).arg( pEval->sRulelistToEvaluate ), "", 3 /*error*/ );

      // SAC 5/26/00 - added final two arguments to enable evaluated rulelist to only operate on certain BEMProc components
      //if ( !ruleSet.m_ruleListList.EvalList( pEval->sRulelistToEvaluate, bTagDataAsUserDefined, pEval->iRulelistEvalClass,
      //                                       pEval->eRulelistEvalObjType, &pEval->maRulelistEvalObjIdxs, pEval->bVerboseOutput,    // SAC 9/25/02
      //         										pEval->pTargetedDebugInfo, pEval->plRuleEvalCount ) &&   // SAC 10/12/11 - facilitates nested rule evaluation sizeing
      if ( !ruleSet.EvaluateRuleListDuringEval( pEval, bTagDataAsUserDefined ) &&    // SAC 8/6/10 - replaced above call w/ this one
           pEval->sRulelistToEvaluate.compare( "None", Qt::CaseInsensitive ) != 0 )
      {  // error evaluating rulelist
         QString sMsg = "Compliance Rulelist '";
         sMsg += pEval->sRulelistToEvaluate;
         sMsg += "' Not Found evaluating rule: ";
         sMsg += pEval->sRuleID;
         BEMPX_WriteLogFile( sMsg );
			if (ruleSet.getLogMsgCallbackFunc())
				ruleSet.getLogMsgCallbackFunc()( logMsgERROR, (const char*) sMsg.toLocal8Bit().constData(), NULL );
      }
   }
      
   // SAC - 1/2/98 - Attempted fix of rule eval memory leak
   if ( (node.type == EXP_String) && (node.pValue) )
   {  // SAC 6/10/99 - switched this 'delete' to free() since allocation was via malloc() and not 'new'
      // delete node.pValue;
      free( node.pValue );
      node.pValue = NULL;   // SAC 10/30/07 - added to prevent re-deletion of same string later on
   }

   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CopyExpEvalStruct( ExpEvalStruct* pDest, ExpEvalStruct* pSrc )
{
   pDest->lPrimDBID            = pSrc->lPrimDBID            ;
   pDest->iPrimObjIdx          = pSrc->iPrimObjIdx          ;
   pDest->ePrimObjType         = pSrc->ePrimObjType         ;
   pDest->iPrimPar1Class       = pSrc->iPrimPar1Class       ;
   pDest->iPrimParObjIdx       = pSrc->iPrimParObjIdx       ;
   pDest->ePrimParObjType      = pSrc->ePrimParObjType      ;

   pDest->iPrimPar2Class       = pSrc->iPrimPar2Class       ;
   pDest->iPrimPar2ObjIdx      = pSrc->iPrimPar2ObjIdx      ;
   pDest->ePrimPar2ObjType     = pSrc->ePrimPar2ObjType     ;
   pDest->iPrimPar3Class       = pSrc->iPrimPar3Class       ;
   pDest->iPrimPar3ObjIdx      = pSrc->iPrimPar3ObjIdx      ;
   pDest->ePrimPar3ObjType     = pSrc->ePrimPar3ObjType     ;

   pDest->lLocDBID             = pSrc->lLocDBID             ;
   pDest->iLocObjIdx           = pSrc->iLocObjIdx           ;
   pDest->eLocObjType          = pSrc->eLocObjType          ;
   pDest->eLocStatus           = pSrc->eLocStatus           ;

   pDest->sRulelistToEvaluate  = pSrc->sRulelistToEvaluate  ;
   pDest->eNewObjType          = pSrc->eNewObjType          ;
   pDest->iImportUniqueRuleLibObjOption = pSrc->iImportUniqueRuleLibObjOption;  // SAC 3/10/13	// SAC 4/25/14
   pDest->sImportRuleLibParentName    = pSrc->sImportRuleLibParentName;  	 // SAC 3/17/13

   pDest->iRulelistEvalClass   = pSrc->iRulelistEvalClass   ;
   pDest->eRulelistEvalObjType = pSrc->eRulelistEvalObjType ;

   pDest->bVerboseOutput       = pSrc->bVerboseOutput       ;

   pDest->sRuleID              = pSrc->sRuleID              ;

   pDest->pTargetedDebugInfo     = pSrc->pTargetedDebugInfo;      // SAC 8/6/10
   pDest->iNumTargetedDebugItems = pSrc->iNumTargetedDebugItems;
   pDest->bEvalItemADebugTarget  = pSrc->bEvalItemADebugTarget;
   pDest->bRuleIDLogged          = pSrc->bRuleIDLogged;
   pDest->pRuleBeingEvaled       = pSrc->pRuleBeingEvaled;
   pDest->sRuleListName          = pSrc->sRuleListName;

   pDest->plRuleEvalCount      = pSrc->plRuleEvalCount      ;

   pDest->maRulelistEvalObjIdxs.clear();
   pDest->maDeletedClassIDs.clear();
   pDest->maDeletedObjIdxs.clear();
   int i=0;
   for (; i < (int) pSrc->maRulelistEvalObjIdxs.size(); i++)
      pDest->maRulelistEvalObjIdxs.push_back( pSrc->maRulelistEvalObjIdxs[i] );
   for (i=0; i < (int) pSrc->maDeletedClassIDs.size(); i++)
      pDest->maDeletedClassIDs.push_back( pSrc->maDeletedClassIDs[i] );
   for (i=0; i < (int) pSrc->maDeletedObjIdxs.size(); i++)
      pDest->maDeletedObjIdxs.push_back( pSrc->maDeletedObjIdxs[i] );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static const char* spszParseErrors[] = {   /*  0 */  "invalid parse type (only integer, float, string or symbol enabled)"
                                         , /*  1 */  "leading numeric character missing"
                                         , /*  2 */  "leading non-numeric character missing"
                                       };

BOOL ParseStringPortion( QString& sParseStr, ExpNode* pParseNode, int iDataType, int& iErrMsgIdx )
{
   iErrMsgIdx = -1;

   assert( pParseNode );
   if (pParseNode)
   {
      pParseNode->type = EXP_Invalid;
      pParseNode->fValue = 0;
   }

   int iNumCharsParsed = 0;
   QString sVal;
   double fVal=0;
   if (iDataType == BEMP_Int || iDataType == BEMP_Flt)
   {
      while (iNumCharsParsed < sParseStr.length() && sParseStr[iNumCharsParsed] >= '0' && sParseStr[iNumCharsParsed] <= '9')
         iNumCharsParsed++;
      if (iNumCharsParsed < 1)
         iErrMsgIdx = 1;
      else if (iDataType == BEMP_Flt && (iNumCharsParsed+2) <= sParseStr.length() &&
               sParseStr[iNumCharsParsed] == 'p' && sParseStr[iNumCharsParsed+1] >= '0' && sParseStr[iNumCharsParsed+1] <= '9')
      {
         sParseStr[iNumCharsParsed] = '.';
         iNumCharsParsed += 2;
         while (iNumCharsParsed < sParseStr.length() && sParseStr[iNumCharsParsed] >= '0' && sParseStr[iNumCharsParsed] <= '9')
            iNumCharsParsed++;
      }

      if (iDataType == BEMP_Int)
         fVal = atoi( sParseStr.left( iNumCharsParsed ).toLocal8Bit().constData() );
      else
         fVal = atof( sParseStr.left( iNumCharsParsed ).toLocal8Bit().constData() );
   }
   else if (iDataType == BEMP_Str || iDataType == BEMP_Sym)
   {
      iDataType = BEMP_Str;
      while (iNumCharsParsed < sParseStr.length() && (sParseStr[iNumCharsParsed] < '0' || sParseStr[iNumCharsParsed] > '9'))
         iNumCharsParsed++;
      if (iNumCharsParsed < 1)
         iErrMsgIdx = 2;
      else
         sVal = sParseStr.left( iNumCharsParsed );
   }
   else
      iErrMsgIdx = 0;

   if (iErrMsgIdx == -1 && iNumCharsParsed > 0)
   {
      if (iNumCharsParsed >= sParseStr.length())
         sParseStr.clear();
      else
         sParseStr = sParseStr.right( sParseStr.length()-iNumCharsParsed );

      assert( pParseNode );
      if (pParseNode)
      {
         if (iDataType == BEMP_Int || iDataType == BEMP_Flt)
         {
            pParseNode->type = EXP_Value;
            pParseNode->fValue = fVal;
         }
         else
         {
            pParseNode->type = EXP_String;
            if (sVal.length() > 0)
            {
               pParseNode->pValue = malloc( sVal.length() + 1 );
#pragma warning (disable:4996)
               strcpy( (char*) pParseNode->pValue, (const char*) sVal.toLocal8Bit().constData() );
#pragma warning (default:4996)
            }
            else
               pParseNode->pValue = NULL;
         }
      }
   }

   return (iErrMsgIdx == -1);
}

/////////////////////////////////////////////////////////////////////////////

// returned Transformation ID is 1-based, to enable Model DBID's to distinguish 'no model specified' from 'user' (first) model
int RemovePrecedingTransformationID( QString& sDBID, int iCurTransID )
{
	int iFirstColon = sDBID.indexOf(':');
	int iTransIdx = 0;
	if (iFirstColon > 0)
	{	QString sTrans = sDBID.left( iFirstColon );
		if (sTrans.length() <= TransShortName_MaxLen)
		{	int iT, iNumTrans = ruleSet.getNumTransformations();	BOOL bIsAGroupName = FALSE;
			for (iT=0; (iTransIdx == 0 && iT<iNumTrans); iT++)
			{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iT);						assert( pTrans );
				if (pTrans && !pTrans->getShortName().compare( sTrans, Qt::CaseInsensitive ))
					iTransIdx = iT+1;
				else if (pTrans && pTrans->ShortGroupNameMatch( sTrans ))		// SAC 8/20/15 - switched group names from single strings to arrays
					bIsAGroupName = TRUE;
			}
		// SAC 3/29/14 - if this is not a MAIN transform ID, then find appropriate TransIdx based on transform GROUP IDs
			if (iTransIdx < 1 && bIsAGroupName && iCurTransID > 0)
			{	// FIRST see if the current transform is part of the GROUP corresponding to this Trans ID
				RuleSetTransformation* pTrans = ruleSet.getTransformation(iCurTransID-1);		assert( pTrans );
				if (pTrans && pTrans->ShortGroupNameMatch( sTrans ))		// SAC 8/20/15 - switched group names from single strings to arrays
					iTransIdx = iCurTransID;
				else if (pTrans && pTrans->getBEMProcIdxToCopy() >= 0 && pTrans->getBEMProcIdxToCopy() < iNumTrans)
				{	// THEN see if the current transform was originally copied from a transform in the GROUP corresponding to this Trans ID
					RuleSetTransformation* pTrans2 = ruleSet.getTransformation(pTrans->getBEMProcIdxToCopy());			assert( pTrans );
					if (pTrans2 && pTrans2->ShortGroupNameMatch( sTrans ))		// SAC 8/20/15 - switched group names from single strings to arrays
						iTransIdx = pTrans->getBEMProcIdxToCopy() + 1;
			}	}
			if (iTransIdx < 1 && bIsAGroupName)
			{	// THEN start w/ current transform and look back through each one, returning first (most recent) in the specified GROUP
				for (iT=iCurTransID-1; (iTransIdx == 0 && iT>=0); iT--)
				{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iT);					assert( pTrans );
					if (pTrans && pTrans->ShortGroupNameMatch( sTrans ))		// SAC 8/20/15 - switched group names from single strings to arrays
						iTransIdx = iT+1;
			}	}
			if (iTransIdx > 0)
			{	sDBID = sDBID.right( sDBID.length() - iFirstColon - 1 );
				//iFirstColon = sDBID.indexOf(':');
		}	}
	}
	return iTransIdx;
}

// returned Transformation ID is 1-based, to be consistent w/ above routine
int GetTransformationIDFromRulelistName( QString& sRLName )
{
	int iTransIdx = 0;
	int iNumTrans = ruleSet.getNumTransformations();
	for (int iT=0; (iTransIdx == 0 && iT<iNumTrans); iT++)
	{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iT);			assert( pTrans );
		if (pTrans && !pTrans->getRuleListName().compare( sRLName, Qt::CaseInsensitive ))
			iTransIdx = iT+1;
	}
	if (iTransIdx == 0 && iNumTrans > 0 && (!sRLName.compare("rl_DEFAULT", Qt::CaseInsensitive) ||
														 !sRLName.left(8).compare("rl_CHECK", Qt::CaseInsensitive)))
		iTransIdx = 1;
	return iTransIdx;
}


/////////////////////////////////////////////////////////////////////////////
// SAC 8/14/12 - new routine to facilitate more flexible expression syntax, eliminating the need to
//						specify certain generic function names such as Local(), Parent(), etc.
static int SelectFunctionByArgument_Local( const char* name, int crntFunc, ExpError* pError, BOOL bEnsureValidData );  // SAC 6/3/13  // SAC 2/13/14 - added bEnsureValidData

int SelectFunctionByArgument( const char* name, int crntFunc, ExpError* pError )  // SAC 6/3/13
{	return SelectFunctionByArgument_Local( name, crntFunc, pError, (eiParseCount_IfValidAnd > 0 || eiParseCount_ValidOr > 0) /*FALSE*/ );	// SAC 1/30/15
}
//static bool sbParsingValidArgToFunc = false;		// SAC 8/13/14 - added to help augment logic tracking when to return ...Val function types
int SelectFunctionByArgument_Local( const char* name, int crntFunc, ExpError* pError, BOOL bEnsureValidData )  // SAC 6/3/13  // SAC 2/13/14 - added bEnsureValidData
{	int iFuncOpType = -1;
   int iLocalCompID = crntCompID.GetCurrentCompID();
   //long lLocalDBID = crntCompID.GetCurrentLocalDBID();
	bool bSymStr = (crntFunc == BF_SymString);	// SAC 4/10/14
	if (!bEnsureValidData && ( //sbParsingValidArgToFunc ||		// SAC 8/13/14
										eiParseCount_IfValidAnd > 0 || eiParseCount_ValidOr > 0))	// SAC 1/30/15
		bEnsureValidData = TRUE;

		// SAC 7/9/12 - added code to perform additional parsing
				QString sRemainingStr = name;
				int iCurTransID = 0;		QString sRLName;
				if (ruleSet.DataModelRuleActive())	 	// SAC 3/29/14 - enable rulelist expression grouping		// SAC 5/26/16
				{	crntCompID.GetCurrentRulelistName( sRLName );								assert( !sRLName.isEmpty() );
					if (!sRLName.isEmpty())
						iCurTransID = GetTransformationIDFromRulelistName( sRLName );
				}
				int iTransIdx = RemovePrecedingTransformationID( sRemainingStr, iCurTransID );
				BOOL bTransformIDOK = TRUE;
				if (iTransIdx > 0)
				{	//QString sRLName;		   crntCompID.GetCurrentRulelistName( sRLName );  // SAC 9/25/13
					if (!sRLName.isEmpty() && iTransIdx > iCurTransID)
						bTransformIDOK = FALSE;
				}

// TO DO - use iTransIdx to record transformation of model to retrieve data from

				int iParseCompID = -1;
				int iLastParseCompID = iLocalCompID;
				int iLastSpecifiedParseCompID = -1;
				BOOL bAbort = FALSE;
				int iError=0;
				QString sDataPathItem, sCheckObjRefPath;
				BOOL bPathIncludesObjRef = FALSE;
				int iNextColon = sRemainingStr.indexOf(':');
				QString sFirstPortion = (iNextColon < 0 ? sRemainingStr : sRemainingStr.left( iNextColon ));
				if (sRemainingStr.length() < 1 || !bTransformIDOK)  // SAC 9/25/13
				{	assert( FALSE );  // invalid data model path - nothing left after stripping off the transformation ID -OR- transform ID invalid (SAC 9/25/13)
					bAbort = TRUE;
				}
				else if (iNextColon < 0 || BEMP_GetDBComponentID( sFirstPortion ) < 1)
				{	// string passed in does NOT include a leading object name 
					bPathIncludesObjRef = (iNextColon > 0);
					if (BEMPX_GetDatabaseID( sRemainingStr, iLocalCompID ) > BEM_COMP_MULT)
						iParseCompID = iLocalCompID;
					else
					{	// need to work UP the parent objects to see if there is a consistent parent GENERATION that this property exists for
						// (an inconsistent parent generation means we can't parse this @ compile-time (w/out the obejct type specified))

                     long lDBID;
							int iNumValidDBIDsByGeneration[] = { 0,0,0 };
							BEMClass* pCls = BEMPX_GetClass( (int) iLocalCompID, iError );											assert( pCls );
							if (pCls)
							{  for (int iPIdx=0; iPIdx < BEM_MAX_PARENT_TYPES; iPIdx++)
								{	if (pCls->getParentType(iPIdx) >= 0)
									{	int iPClsIdx = pCls->getParentType(iPIdx)+1;
										if (BEMPX_GetDatabaseID( sFirstPortion, iPClsIdx ) > BEM_COMP_MULT)
											iNumValidDBIDsByGeneration[0]++;
										BEMClass* pPCls = BEMPX_GetClass( iPClsIdx, iError );											assert( pPCls );
										if (pPCls)
										{  for (int iP2Idx=0; iP2Idx < BEM_MAX_PARENT_TYPES; iP2Idx++)
											{	if (pPCls->getParentType(iP2Idx) >= 0)
												{	int iP2ClsIdx = pPCls->getParentType(iP2Idx)+1;
													if (BEMPX_GetDatabaseID( sFirstPortion, iP2ClsIdx ) > BEM_COMP_MULT)
														iNumValidDBIDsByGeneration[1]++;
													BEMClass* pP2Cls = BEMPX_GetClass( iP2ClsIdx, iError );								assert( pP2Cls );
													if (pP2Cls)
													{  for (int iP3Idx=0; iP3Idx < BEM_MAX_PARENT_TYPES; iP3Idx++)
														{	if (pP2Cls->getParentType(iP3Idx) >= 0)
															{	int iP3ClsIdx = pP2Cls->getParentType(iP3Idx)+1;
																if (BEMPX_GetDatabaseID( sFirstPortion, iP3ClsIdx ) > BEM_COMP_MULT)
																	iNumValidDBIDsByGeneration[2]++;
													}	}	}
										}	}	}
							}	}	}

							if (iNumValidDBIDsByGeneration[0] == 0 && iNumValidDBIDsByGeneration[1] == 0 && iNumValidDBIDsByGeneration[2] == 0)
							{	// COULD check for this being a Global() object property, but in that case the parsed string should include the object type
								bAbort = TRUE;		assert( FALSE );		// property not found anywhere in the parent hierarchy (within 3 parent generations of the local comp)
								if (pError)
								{	QString sErrMsg;
									if (pCls)
										sErrMsg = QString( "Error parsing data model path '%1' property not found in object %2 (#%3)" ).arg( sFirstPortion, pCls->getShortName(), QString::number(iParseCompID) );
									else
										sErrMsg = QString( "Error parsing data model path '%1' property not found in object %2" ).arg( sRemainingStr, iParseCompID );
									if (!sRemainingStr.compare("RULE", Qt::CaseInsensitive))
										sErrMsg += " (perhaps missing 'ENDRULE')";
									ExpSetErr( pError, EXP_RuleProc, sErrMsg );
								}
							}
							else if (iNumValidDBIDsByGeneration[0] >  0 && iNumValidDBIDsByGeneration[1] == 0 && iNumValidDBIDsByGeneration[2] == 0)
								iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_ParRefSymStr  : BF_ParSymStr ) : (bEnsureValidData ? BF_ParentVal  : (bPathIncludesObjRef ? BF_ParentRef  : BF_Parent )));			// PARENT function
							else if (iNumValidDBIDsByGeneration[0] == 0 && iNumValidDBIDsByGeneration[1] >  0 && iNumValidDBIDsByGeneration[2] == 0)
								iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_Par2RefSymStr : BF_Par2SymStr) : (bEnsureValidData ? BF_Parent2Val : (bPathIncludesObjRef ? BF_Parent2Ref : BF_Parent2)));			// GRAND-PARENT function
							else if (iNumValidDBIDsByGeneration[0] == 0 && iNumValidDBIDsByGeneration[1] == 0 && iNumValidDBIDsByGeneration[2] >  0)
								iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_Par3RefSymStr : BF_Par3SymStr) : (bEnsureValidData ? BF_Parent3Val : (bPathIncludesObjRef ? BF_Parent3Ref : BF_Parent3)));			// GREAT-GRAND-PARENT function
							else
							{	bAbort = TRUE;		assert( FALSE );		// This property found at MULTIPLE parent generation levels
							}
					}
				}
				else
				{	// need to chug through string until we reach (and have parsed) the LAST object name prior to the trailing property name(s)
					while (!bAbort && iNextColon > 0 && !bPathIncludesObjRef)
					{  sDataPathItem = sRemainingStr.left( iNextColon );
						if (iParseCompID > 1)  // treat first object type (Project) special - don't require following object to be strictly a "child"
						{	// search only through children of iParseCompID for next matching object type
							BEMClass* pCls = BEMPX_GetClass( (int) iParseCompID, iError );								assert( pCls );
							if (pCls)
							{	int iNextParseCompID = pCls->GetChildClassID( sDataPathItem.toLocal8Bit().constData() );
								if (iNextParseCompID > 0)
								{	iParseCompID = iLastSpecifiedParseCompID = iNextParseCompID;
								}
								else
								{	long lDBID = BEMPX_GetDatabaseID( sDataPathItem, iParseCompID );
									if (lDBID > BEM_COMP_MULT)
										bPathIncludesObjRef = TRUE;
									else
									{	assert( FALSE );  // invalid data model path - sDataPathItem not a valid child of previously specified object OR property of the last parsed object type in data model path
										bAbort = TRUE;
									}
								}
							}
						}
						else
						{	// this sDataPathItem could be ANY object type
							iParseCompID = BEMP_GetDBComponentID( sDataPathItem );
							if (iParseCompID < 0)
							{	// wasn't an object type, so check for it being an object referencing property of the last parsed object type
								long lDBID = BEMPX_GetDatabaseID( sDataPathItem, iLastParseCompID );
								if (lDBID > BEM_COMP_MULT)
								{	bPathIncludesObjRef = TRUE;
									iParseCompID = iLastParseCompID;
								}
								else
								{	assert( FALSE );  // invalid data model path - first sDataPathItem must either be an object type or a property of the Local object type
									bAbort = TRUE;
								}
							}
							else
								iLastSpecifiedParseCompID = iParseCompID;
						}

						if (iParseCompID < 0)
						{	assert( FALSE );  // invalid data model path - error parsing data model path leading up to final property name
							bAbort = TRUE;
						}
						else
						{  if (bPathIncludesObjRef)
							{	sCheckObjRefPath = sRemainingStr;
								sRemainingStr = sDataPathItem;
							}
							else
								sRemainingStr = sRemainingStr.right( sRemainingStr.length()-iNextColon-1 );
							iNextColon = sRemainingStr.indexOf(':');
							iLastParseCompID = iParseCompID;
						}
					}
				}

				if (!bAbort && iFuncOpType < 0 && bPathIncludesObjRef && !sCheckObjRefPath.isEmpty())
				{	// purpose here is to check through possibly multiple object referencing properties to ensure that
					// each following property name is consistent w/ the object referenced by the previous property
					int iChkObjRefColon = sCheckObjRefPath.indexOf(':');
					int iChkObjRefPathObj = iParseCompID;
					while (!bAbort && iChkObjRefColon > 0)
					{  sDataPathItem    = sCheckObjRefPath.left( iChkObjRefColon );
						sCheckObjRefPath = sCheckObjRefPath.right( sCheckObjRefPath.length()-iChkObjRefColon-1 );
						iChkObjRefColon  = sCheckObjRefPath.indexOf(':');
						long lDBID = BEMPX_GetDatabaseID( sDataPathItem, iChkObjRefPathObj );
						if (lDBID > BEM_COMP_MULT)
						{	if (iChkObjRefColon > 0)
							{	// we will have to loop around again to check the following object reference, so figure out what object type THIS property references
								BEMPropertyType* pObjRefPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
								if (pObjRefPropType == NULL || pObjRefPropType->getPropType() != BEMP_Obj || pObjRefPropType->getObj1ClassIdx( 0 ) < 1)
								{	assert( FALSE );  // invalid data model path - error retrieving property type info OR property type NOT of type BEMP_Obj
									bAbort = TRUE;
								}
								else if (pObjRefPropType->NumberOfDistinctObjectTypesReferenced() > 1)
		// WARNING - this property type can refernce MULTIPLE object types, so evaluation-time checking is required to 
									iChkObjRefColon = -1;  // set next colon character index variable to -1 in order to abort further checking
								else
									iChkObjRefPathObj = pObjRefPropType->getObj1ClassIdx( 0 );
							}
						}
						else
						{	assert( FALSE );  // invalid data model path - data model path item isn't a property of the preceding referenced object type
							bAbort = TRUE;
						}
					}
				}

				if (!bAbort && iFuncOpType < 0)
				{	assert( !sRemainingStr.isEmpty() );
					if (iParseCompID > 0)
					{	// confirm existence of trailing data model path property
						long lDBID = BEMPX_GetDatabaseID( sRemainingStr, iParseCompID );
						if (lDBID < BEM_COMP_MULT)
						{	assert( FALSE );  // invalid data model path - final property name not found for specified object type
							bAbort = TRUE;
							if (pError)
							{	QString sErrMsg;
								BEMClass* pErrClass = BEMPX_GetClass( iParseCompID, iError ); 			assert( pErrClass );
								if (pErrClass)
									sErrMsg = QString( "Error parsing data model path '%1' property not found in object %2 (#%3)" ).arg( sRemainingStr, pErrClass->getShortName(), QString::number(iParseCompID) );
								else
									sErrMsg = QString( "Error parsing data model path '%1' property not found in object %2" ).arg( sRemainingStr, iParseCompID );
								if (!sRemainingStr.compare("RULE", Qt::CaseInsensitive))
									sErrMsg += " (perhaps missing 'ENDRULE')";
								ExpSetErr( pError, EXP_RuleProc, sErrMsg );
							}
						}
						else
						{	// then find relationship between iParseCompID & the "local" object class
							if (iParseCompID == iLocalCompID)
								iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_LocRefSymStr : BF_LocSymStr) : (bEnsureValidData ? BF_LocalVal : (bPathIncludesObjRef ? BF_LocalRef : BF_Local)));	// SAC 2/13/14
							else if (BEMPX_GetClassMaxDefinable( iParseCompID ) == 1)	// MaxDefinable==1 implies Global object type
							//	{	assert( !bPathIncludesObjRef );  // don't have a BF_GlobalRef function
							//		iFuncOpType = BF_Global;	// process as Global() function
							//	}
							// SAC 5/9/13 - allow for GlobalRef()
							{	assert( (!bSymStr || !bPathIncludesObjRef) );	// DON'T have GlobalRefSymbolString() (yet)
								iFuncOpType = (bSymStr ? BF_GlobSymStr : (bEnsureValidData ? BF_GlobalVal : (bPathIncludesObjRef ? BF_GlobalRef : BF_Global)));   // SAC 2/13/14
							}
							else
							{	BEMClass* pCls = BEMPX_GetClass( (int) iLocalCompID, iError );								assert( pCls );
								if (pCls)
								{	std::vector<long>	laParents;
									int iPIdx;
							      for (iPIdx=0; (!bAbort && iFuncOpType < 0 && iPIdx < BEM_MAX_PARENT_TYPES); iPIdx++)
									{	if (pCls->getParentType(iPIdx) == (iParseCompID-1))
											iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_ParRefSymStr : BF_ParSymStr) : (bEnsureValidData ? BF_ParentVal : (bPathIncludesObjRef ? BF_ParentRef : BF_Parent)));				// PARENT function
										else if (pCls->getParentType(iPIdx) >= 0)
											laParents.push_back( pCls->getParentType(iPIdx)+1 );
									}

									if (!bAbort && iFuncOpType < 0 && laParents.size() > 0)
									{	// check grand parent objects 
								      for (iPIdx=0; (!bAbort && iFuncOpType < 0 && iPIdx < (int) laParents.size()); iPIdx++)
										{	pCls = BEMPX_GetClass( (int) laParents[iPIdx], iError );								assert( pCls );
											std::vector<long>	laGParents;
											int iGPIdx;
							      		for (iGPIdx=0; (!bAbort && iFuncOpType < 0 && iGPIdx < BEM_MAX_PARENT_TYPES); iGPIdx++)
											{	if (pCls->getParentType(iGPIdx) == (iParseCompID-1))
													iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_Par2RefSymStr : BF_Par2SymStr) : (bEnsureValidData ? BF_Parent2Val : (bPathIncludesObjRef ? BF_Parent2Ref : BF_Parent2)));	// GRAND-PARENT function
												else if (pCls->getParentType(iGPIdx) >= 0)
													laGParents.push_back( pCls->getParentType(iGPIdx)+1 );
											}

											if (!bAbort && iFuncOpType < 0 && laGParents.size() > 0)
											{	// check great grand parent objects 
								   		   for (iPIdx=0; (!bAbort && iFuncOpType < 0 && iPIdx < (int) laGParents.size()); iPIdx++)
												{	pCls = BEMPX_GetClass( (int) laGParents[iPIdx], iError );								assert( pCls );
							      				for (iGPIdx=0; (!bAbort && iFuncOpType < 0 && iGPIdx < BEM_MAX_PARENT_TYPES); iGPIdx++)
													{	if (pCls->getParentType(iGPIdx) == (iParseCompID-1))
															iFuncOpType = (bSymStr ? (bPathIncludesObjRef ? BF_Par3RefSymStr : BF_Par3SymStr) : (bEnsureValidData ? BF_Parent3Val : (bPathIncludesObjRef ? BF_Parent3Ref : BF_Parent3)));	// GREAT-GRAND-PARENT function
														//else if (pCls->getParentType(iGPIdx) >= 0)
														//	laGParents.push_back( pCls->getParentType(iGPIdx)+1 );
													}
												}
											}	// end of if not Grand-Parent
										}
									}	// end of if not Parent
								}
							}	// end of if not Local
						}
					}
				}


//				iFuncOpType = BF_Local;
//				iParseCompID = iCompID;
//				if (iNextColon > 0)
//				{	QString sCompClass = sRemainingStr.left( iNextColon );
//					int iCompClass = BEMPX_GetDBComponentID( sCompClass );
//					if (iCompClass > 0)
//					{	iParseCompID = iCompClass;
//						if (lLocalDBID > BEM_COMP_MULT && iCompClass == BEMPX_GetClassID( lLocalDBID ))
//						{	// do nothing here - process as Local() function
//						}
//						else if (BEMPX_GetClassMaxDefinable( iCompClass ) == 1)	// MaxDefinable==1 implies Global object type
//							iFuncOpType = BF_Global;	// process as Global() function
//// TO DO ?? check for iCompClass == parent, grand-parent...
//						else
//							iFuncOpType = -1;
//					}
//					else
//						iFuncOpType = -1;  // not sure how to process this portion of string
//					sRemainingStr = sRemainingStr.right( sRemainingStr.length() - iNextColon - 1 );
//					iNextColon = sRemainingStr.indexOf(':');
//					assert( iFuncOpType > -1 );
//				}


//				int iFuncTblNArgs = VAR_ARGS;
//				void* pFuncTablePos = (iFuncOpType >= 0 ? ExpGetFuncTablePtrByOpType( iFuncOpType, &iFuncTblNArgs ) : NULL);
//				
//				if (iFuncOpType >= 0 && iFirstColon < 0)
//				{	// should be a LOCAL property name
//					int iObjID = (iParseCompID > 0 ? iParseCompID : (lLocalDBID > BEM_COMP_MULT ? BEMPX_GetClassID( lLocalDBID ) : -1));		assert( iObjID > 0 );
//					long lThisDBID = BEMPX_GetDatabaseID( sRemainingStr, iObjID );
//					if (lThisDBID > BEM_COMP_MULT)
//					{
//            		// Add a node
//            	//	//XAddnArg();
//					//	XExpAddFunctionNodeByOpType( iFuncOpType, 1 );
//               //
//            	//	found = true;
//            	//	((YYSTYPE*)data)->index = lThisDBID;
//            	//	*pVar = BEMPELEM;
//
//
//				// TO DO ?? check consistency between iFuncTblNArgs (-1 => VAR_ARGS) & number of lDBID arguments pushed to stack ??
//
//						PushnArgs();  // must be called prior to FUNCTION being reduced i.e. prior to arglist being processed.
//               
//               // add DBID (function argument) node(s) FIRST and RETURN info about BEMP function node to be added subsequently to stack
//                  XExpAddBldgElemNode( lThisDBID );
//            		XAddnArg();
//						//ExpAddFunctionNode( pFuncTablePos, GetnArgs() );
//						XExpAddFunctionNodeByOpType( iFuncOpType, GetnArgs() );
//
//            		found = true;
//            		((YYSTYPE*)data)->object = pFuncTablePos;   // doesn't result in node pushed to stack, which is why we need to push both the DBID(s) and function node above
//            		*pVar = FUNCTION;
//
//
//					//	PushnArgs();  // must be called prior to FUNCTION being reduced i.e. prior to arglist being processed.
//					//	XExpAddFunctionNodeByOpType( iFuncOpType, 1 );
//               //
//            	//	found = true;
//            	//	((YYSTYPE*)data)->index = lThisDBID;
//            	//	*pVar = BEMPELEM;
//
//					}
//				}
//// TO DO - what if string being parsed is more complex ??


//	int GetnArgs()  /* Called from parser.c */
//	{
//	   int nArgs = topNarg->nArgs;
//	   Nargs* temp = topNarg;
//	
//	   topNarg = temp->next;
//	   free( temp );
//	
//	   crntFunc = 0;
//	
//	   return( nArgs );
//	}
//	
//	void AddnArg()  /* Called from parser.c */
//	{
//	   if ( topNarg != NULL )
//	      topNarg->nArgs++;
//	}
//	
//	void PushnArgs()  /* Called from parser.c */
//	{
//	   Nargs* newNarg = (Nargs*) malloc( sizeof( Nargs ) );
//	
//	   if ( newNarg != NULL )
//	   {
//	      newNarg->next = topNarg;
//	      newNarg->nArgs = 0;
//	      topNarg = newNarg;
//	   }
//	   else
//	      ; /* TO DO: Out of memory */
//	}


//int GetNodeType( const char* name, int* pVar, int crntFunc, void* data )
//									  string,    &token,     crntFunc,   &yylval     -- args passed in from yylex()

//		crntFunc = functable[ i ].op;
//		yylval.object = &functable[ i ];
//		token = FUNCTION;
//		found = TRUE;


//	{	strcpy( tempString, name );
//		tempString[ strlen( tempString ) ] = '\"';
//		((YYSTYPE*)data)->object = tempString;
//		*pVar = STRING;


// void ExpAddFunctionNode( void* func, int nArgs )
// {
//    FuncTable *function = (FuncTable*)func;
// 
//    if ( nArgs != function->nArgs && function->nArgs != VAR_ARGS ) 
//       ExpSetError( parseError, EXP_BadArgs, function->name );
//    else
//    {
//       ExpNode* node = (ExpNode*)malloc( sizeof( ExpNode ) );
// 
//       if ( node == NULL )
//          ExpSetError( parseError, EXP_NoMem, NULL );
//       else
//       {
//          node->type = EXP_Function;
//          node->fn.function = function->evaluate;
//          node->fn.op = function->op;
//          node->fn.nArgs = nArgs;
// 
//          ExpListAddTail( parseList, node );
//       }
//    }
// }

#ifdef YYDEBUG
#pragma warning(disable : 4996)		// SAC 8/31/16
	const char* pFuncName = (iFuncOpType >= 0 ? ExpGetFuncTableNameByOpType( iFuncOpType ) : NULL);
	char parseMsg[256];
    _snprintf( parseMsg, 256, "         SelectFunctionByArgument: name '%s', iFuncOpType %d (%s)\n", name, iFuncOpType, (pFuncName ? pFuncName : "?") );		// SAC 8/31/16
    ExpPostParserMsg( parseMsg );
#pragma warning(default : 4996)
#endif

//	sbParsingValidArgToFunc = false;		// SAC 8/13/14
	return iFuncOpType;
}

/////////////////////////////////////////////////////////////////////////////

BOOL StringInSymbolList( long lDBID, QString& sString, int iBEMProcIdx /*=-1*/ )
{	BOOL bRetVal = FALSE;
	int iError;
	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
	if (pPropType && pPropType->getPropType() == BEMP_Sym)
	{
   	long iSymVal = -999;
   	//int iSymTableIdx = BEMPX_GetIndexOfSymbolTable( lDBID, iBEMProcIdx );
   	//if (iSymTableIdx >= 0)
   	//   bRetVal = (BEMPX_GetSymbolTableValue( lDBID, sString, iSymTableIdx, -1 /*iOccur*/, iBEMProcIdx ) != -999);
   	
   	if (iSymVal == -999)
   	{  BEMSymbolList* pSymList = GetSymbolList( lDBID );                 			assert( pSymList != NULL );
   	   if (pSymList)
			{	int iNumDepSets = pSymList->getNumSymDependencySets();
				for (int i=0; (!bRetVal && i<iNumDepSets); i++)
				{	BEMSymDependencySet* pDepSet = pSymList->getSymDependencySet(i);		assert( pDepSet );
					if (pDepSet)
					{	int iNumSyms = pDepSet->getNumSymbols();
						for (int j=0; (!bRetVal && j<iNumSyms); j++)
						{	BEMSymbol* pSym = pDepSet->getSymbol(j);								assert( pSym );
							if (pSym && !pSym->getString().compare( sString, Qt::CaseInsensitive  ))
								bRetVal = TRUE;
						}
					}
				}
			}
   	}
	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  GetNodeType()
//
// Purpose ------------------------------------------------------------------
//   Get the type of data which an expression node evaluates to.
//   
// Arguments ----------------------------------------------------------------
//   const char* name     : a reserved keyword or function call string
//   int*        pVar     : pointer to an integer which gets set to a value indicating the node type
//   int         crntFunc : an enum indicating the current function
//   void*       data     : pointer to data passed back to calling function
//   
// Return Value -------------------------------------------------------------
//   TRUE if node type found, else FALSE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4996)		// SAC 8/31/16
int GetNodeType( const char* name, int* pVar, int crntFunc, void* data )
{
   long dbId;
   long long lMDBID;  // SAC 3/14/13
   bool found = FALSE;
   int iCompID = crntCompID.GetCurrentCompID();
   long lLocalDBID = crntCompID.GetCurrentLocalDBID();
   QString temp = name;
   static char tempString[ 256 ];
   int iRefCompID = 0;  // SAC 7/17/01
	int iNumRefComps = 0;  // SAC 8/27/12
#ifdef YYDEBUG
	char parseMsg[256];	parseMsg[0]='\0';
#endif

   // Check for keywords.
   // Since there are only 2, do this.  If we add more we should implement a table.
   if ( _stricmp( name, "default" ) == 0 )
   {
      ((YYSTYPE*)data)->index = (long)KW_Default;
      *pVar = KEYWORD;
      found = TRUE;
#ifdef YYDEBUG
	    _snprintf( parseMsg, 256, "         GetNodeType: name '%s', KEYWORD KW_Default\n", name );		// SAC 8/31/16
#endif
   }
   else if ( _stricmp( name, "none" ) == 0 )
   {
      ((YYSTYPE*)data)->index = (long)KW_None;
      *pVar = KEYWORD;
      found = TRUE;
#ifdef YYDEBUG
	    _snprintf( parseMsg, 256, "         GetNodeType: name '%s', KEYWORD KW_None\n", name );		// SAC 8/31/16
#endif
   }
   else if ( _stricmp( name, "unchanged" ) == 0 )  // SAC 3/31/01
   {
      ((YYSTYPE*)data)->index = (long)KW_Unchanged;
      *pVar = KEYWORD;
      found = TRUE;
#ifdef YYDEBUG
	    _snprintf( parseMsg, 256, "         GetNodeType: name '%s', KEYWORD KW_Unchanged\n", name );		// SAC 8/31/16
#endif
   }
   else if ( _stricmp( name, "undefined" ) == 0 )  // SAC 8/24/01
   {
      ((YYSTYPE*)data)->index = (long)KW_Undefined;
      *pVar = KEYWORD;
      found = TRUE;
#ifdef YYDEBUG
	    _snprintf( parseMsg, 256, "         GetNodeType: name '%s', KEYWORD KW_Undefined\n", name );		// SAC 8/31/16
#endif
   }

	// added code to identify enumeration strings and to store the string as a string node
	else if (lLocalDBID > BEM_COMP_MULT && strlen( name ) > 0 && StringInSymbolList( lLocalDBID, temp, -1 ))
	{
		strcpy( tempString, name );
		tempString[ strlen( tempString ) ] = '\"';
		((YYSTYPE*)data)->object = tempString;
		*pVar = STRING;
		found = TRUE;
#ifdef YYDEBUG
	    _snprintf( parseMsg, 256, "         GetNodeType: name '%s', STRING\n", name );		// SAC 8/31/16
#endif
	}


//		// SAC 2/13/14 - special processing for IfValidAnd() - which we want to cause parsing of arguments for a variety of other functions, like Local*, Parent*, etc.
//	   if (crntFunc == BF_IfValidAnd)
//		{
//			int iFuncOpType = SelectFunctionByArgument_Local( temp, NULL /*ExpError* pError*/, TRUE /*bEnsureValidData*/ );
//		//	int iFuncOpType = parseSelectFunc( string, parseError );  // SAC 6/3/13 - added parseError argument
//			if (iFuncOpType >= 0)
//			{	//		int iFTIdx = -1;
//				//		while (functable[++iFTIdx].name != NULL)
//				//		{	if (functable[iFTIdx].op == iFuncOpType)
//				//				break;
//				//		}
//				//		if (functable[iFTIdx].name != NULL)
//				//		{  crntFunc = functable[ iFTIdx ].op;
//	   	   //		   yylval.object = &functable[ iFTIdx ];
//	   	   //		   token = FUNCTION;
//	   	   //		   found = TRUE;
//	   	   //		   PushnArgs(); // Moved this here from parser.y because it must be called
//	   	   //		                // prior to FUNCTION being reduced i.e. prior to arglist being
//	   	   //		                // processed.
//				//			siInsertFuncMode = 1;   /* SAC 8/14/12 */
//				//		}
//		// UPDATE crntFunc based on the function needed to evaluate the argument
//				crntFunc = iFuncOpType;
//			}
//	   }

	else
	{
#ifdef YYDEBUG
		const char* pFuncName = (crntFunc >= 0 ? ExpGetFuncTableNameByOpType( crntFunc ) : NULL);
#endif

   // Resolve function arguments;
   switch ( crntFunc )
   {
      case BF_Global :
      case BF_GlobSymStr :   // SAC 7/25/01
      case BF_GlobStatus :   // SAC 8/24/01
      case BF_GlobalRef :    // SAC 1/22/07
      case BF_GCompAssign :    // SAC 5/12/12
      case BF_SumChld :
      case BF_ChildRef :
      case BF_SumAll :
      case BF_SumRevRef :
      case BF_MaxChild :
      case BF_MaxAll :
      case BF_MaxRevRef :
      case BF_MinChild :
      case BF_MinAll :
      case BF_MinRevRef :
      case BF_CountRefs :
      case BF_CountUPRefs :
      case BF_CountNoRefs :
      case BF_MaxRevRefC :   // SAC 1/9/02
      case BF_MaxAllComp :   // SAC 1/25/02
      case BF_BitMatchCmp :  // SAC 4/2/02 - first arg should be the Property name of a local number, subsequent are Component:Property strings
      case BF_BitMatchCnt :  // SAC 4/2/02 - first arg should be the Property name of a local number, subsequent are Component:Property strings
      case BF_StrUnique :    // SAC 8/25/03 - first argument of EnsureStringUniqueness() should be Comp:Param string
      case BF_MaxRevRefA :   // SAC 11/10/04
      case BF_CountOccur :   // SAC 5/4/06 - first argument of CountOccurrences() should be Comp:Param string
      case BF_SumToArray :   // SAC 7/21/06 - first argument of SumIntoArrayElement() should be Param or Comp:Param string
      case BF_SumRevRefEx :  // SAC 8/1/06
      case BF_CompArray  :   // SAC 3/7/11 - ComponentArray( <OperationID#>, <Value#>, LocalDBID, Comp:ParamDBID ) - returns array of component references to LocalDBID based on Comp:ParamDBID meeting OperationID & Value condition
      case BF_SumAcrsIf  :   // SAC 2/15/13 - SumAcrossIf( Comp:ParamDBID, <Condition> ), where <Condition> is typically something like "Comp:ParamDBID = "Option""
      case BF_SumChldIf  :   // SAC 2/15/13 - SumChildrenIf( ChildComp:ParamDBID, <Condition> ), where <Condition> is typically something like "ChildComp:ParamDBID = "Option""
      case BF_ScalePolyLp :  // SAC 5/28/13 - 1st arg is a scale method (0/1/...), 2nd is a scaling factor which may be simply an Object:Property path
      case BF_ConsUFctr :    // SAC 6/12/13 - ConsAssmUFactor() has 1 argument, calculation method, which may be entered as an Object:Property path
      case BF_ConsUFctrR :	  // SAC 2/21/14 - ConsUFactorRes() has 1 argument, code vintage (for future use), which may be entered as an Object:Property path
      case BF_DayltArea :    // SAC 10/1/13 - DaylightableArea() has 1 argument, daylight calc methodology/vintage, which may be entered as an Object:Property path
		case BF_GlobalVal  :	  // SAC 2/13/14
		case BF_MaxChildC :    // SAC 10/18/14
		case BF_MinChildC :    // SAC 10/18/14
		case BF_ListRevRef   :  // SAC 1/26/15 - ListRevRef(   RevRefObj:Prop,              "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
		case BF_ListRevRefIf :  // SAC 1/26/15 - ListRevRefIf( RevRefObj:Prop, <Condition>, "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
      case BF_CompIdx      :  // SAC 11/14/16 - moved here since "ComponentIndex" can now include an object reference property argument
      case BF_AddCSERptCol :  // SAC 11/14/16 - added "AddCSEReportCol" w/ second argument that may be object cseReportCol reference property
         {
            int iCompType = 0;  // SAC 1/4/01 - added to facilitate parsing of new BF_CountNoRefs func
            if (crntFunc == BF_CountNoRefs)
               iCompType = iCompID;
            else if (crntFunc == BF_BitMatchCmp || crntFunc == BF_BitMatchCnt || crntFunc == BF_SumToArray || crntFunc == BF_CompIdx)  // SAC 4/2/02  // SAC 7/20/06  // SAC 11/15/16
            {
               if (temp.indexOf(':') < 0)
                  iCompType = iCompID;  // only set iCompID when no component type is specified (enables both local and referenced properties)
            }

				int iCurTransID = 0;		QString sRLName;
				if (ruleSet.DataModelRuleActive())	 	// SAC 3/29/14 - enable rulelist expression grouping		// SAC 5/26/16
				{	crntCompID.GetCurrentRulelistName( sRLName );								assert( !sRLName.isEmpty() );
					if (!sRLName.isEmpty())
					{	iCurTransID = GetTransformationIDFromRulelistName( sRLName );
				}	}
				int iTransIdx = RemovePrecedingTransformationID( temp, iCurTransID );  // SAC 7/16/12
				BOOL bTransformIDOK = TRUE;
				if (iTransIdx > 0)
				{	//QString sRLName;		   crntCompID.GetCurrentRulelistName( sRLName );  // SAC 9/25/13
					if (!sRLName.isEmpty() && iTransIdx > iCurTransID)
					{	assert( FALSE );
						bTransformIDOK = FALSE;
					}
				}

            lMDBID = BEMPX_GetModelDatabaseID( iTransIdx, temp.toLocal8Bit().constData(), iCompType, FALSE, &iRefCompID, &iNumRefComps );
				assert( iNumRefComps < 2 );  // Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
         
            temp = temp.right( temp.length() - temp.indexOf(':') - 1 );
            if (iRefCompID > 0 && bTransformIDOK)  // lMDBID >= 1000000 )
            {
					// SAC 1/3/02 - Added code to prevent multiple indirections for certain Sum, Min, Max & Count functions
               if ( crntFunc == BF_SumRevRef   || crntFunc == BF_MaxRevRef   || crntFunc == BF_MinRevRef   ||
                    crntFunc == BF_CountRefs   || crntFunc == BF_CountUPRefs || crntFunc == BF_CountNoRefs ||
                    crntFunc == BF_MaxRevRefC  || crntFunc == BF_MaxAllComp  || crntFunc == BF_MaxRevRefA  ||   // SAC 11/10/04
                    crntFunc == BF_BitMatchCmp || crntFunc == BF_BitMatchCnt || crntFunc == BF_SumToArray  ||   // SAC 4/2/02  // SAC 7/20/06
                    crntFunc == BF_SumRevRefEx || crntFunc == BF_CompArray   ||   // SAC 8/1/06  // SAC 3/7/11
                    crntFunc == BF_ListRevRef  || crntFunc == BF_ListRevRefIf )   // SAC 1/26/15
                  lMDBID = 0;
               else
               {	int iError=0;
                  temp = temp.right( temp.length() - temp.indexOf(':') - 1 );
                  while ( iRefCompID > 0 /*lMDBID >= 1000000*/  &&  !(lMDBID < 0) )
                  {
                     // Add a node
                     XAddnArg();
                     XExpAddBldgElemNode( lMDBID );  // % 1000000 );

                     // str2 = (strip left portion of str off, up to and including the SECOND ':')
                     temp = temp.right( temp.length() - temp.indexOf(':') - 1 );

// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into account (potentially) mulitple compatible referenced obejct types
                     //lMDBID = BEMPX_GetDatabaseID( temp, iRefCompID, FALSE, &iRefCompID );
							BOOL bDBIDValid = FALSE;
		      			int i2ndRefCompID = iRefCompID;
							long long l2ndDBID = lMDBID;
							long lPTDBID = BEMPX_MDBIDtoDBID( l2ndDBID );
							BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lPTDBID, iError );						assert( iError==0 );		assert( pPropType );
							for (int iObjCls=0; (pPropType && !bDBIDValid && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
							{	if (pPropType->getObj1ClassIdx( iObjCls ) > 0)
								{	l2ndDBID = BEMPX_GetModelDatabaseID( iTransIdx, temp.toLocal8Bit().constData(), pPropType->getObj1ClassIdx( iObjCls ), FALSE, &i2ndRefCompID, &iNumRefComps );
									assert( iNumRefComps < 2 );  // Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
									if (l2ndDBID > 0)
										bDBIDValid = TRUE;
								}
							}
							// update original variables, regardless of whether the processing successfully returned a valid DBID
							lMDBID = l2ndDBID;
							iRefCompID = i2ndRefCompID;
                  }
                  // The last node is added by calling function.
               }
            }
            found = (lMDBID > 0 && bTransformIDOK);
            if ( found )
            {
               ((YYSTYPE*)data)->index = lMDBID;
               *pVar = BEMPELEM;
#ifdef YYDEBUG
					_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPELEM %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), lMDBID );		// SAC 8/31/16
#endif
            }
         }
         break;
// SAC 12/19/01 - Migrated the Local function parsing here when code added to actually parse those Parent*() functions where only one parent type exists
      case BF_Local :
      case BF_LocSymStr :  // SAC 2/8/01
      case BF_LocSymInv  :  // SAC 8/11/06
      case BF_LocalRef :
      case BF_LCompAssign : // "LocalCompAssigned"
      case BF_LIsDefault : // "LocalIsDefault"
      case BF_LocStatus : // "LocalStatus"
      case BF_Parent  :
      case BF_Parent2 :
      case BF_Parent3 :
      case BF_ParentRef  :
      case BF_Parent2Ref :
      case BF_Parent3Ref :
      case BF_PCompAssign :
      case BF_PIsDefault : // "ParentIsDefault"
      case BF_ParStatus : // "ParentStatus"
      case BF_LocMxStrLen : // "LocalMaxStringLength"
      case BF_ParStrAElem : // "ParentStringArrayElement"
      case BF_LocArrIdx : // "LocalArrayIndex"   - SAC 3/3/10
		case BF_LocalVal   :		// SAC 2/13/14
		case BF_ParentVal  :		// SAC 2/13/14
		case BF_Parent2Val :		// SAC 2/13/14
		case BF_Parent3Val :		// SAC 2/13/14
      case BF_RuleLib    :  // 1st arg is a comp id, 2nd is a string so GetNodeType will not be called, 3rd (optional) is integer (0/1 - whether to load lib item regardless of presence of same lib item already in model)
									 // 5th (optional) arg (added 3/17/13) are the Name of the object to be used as the Parent of the imported library object
      case BF_IfValidAnd :  // arguments can be Local*/Parent*/Global* arguments
      case BF_ValidOr    :  // arguments can be Local*/Parent*/Global* arguments
		case BF_SymString  :  // arguments can be Local*/Parent*/Global* arguments
      case BF_HrlyResMltNEM :  // SAC 1/23/17 - ApplyHourlyResultMultipliers_NEM( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"SaleEnduse">, <"TotalEnduse">, <NEMconstant>, <SaleHrlyMultiplier>, <"OtherSaleEnduseOne">, ... )
		case BF_Par2SymStr    :  // SAC 4/10/14
		case BF_Par3SymStr    :  // SAC 4/10/14
		case BF_LocRefSymStr  :  // SAC 4/10/14
		case BF_ParSymStr     :  // SAC 4/10/14
		case BF_ParRefSymStr  :  // SAC 4/10/14
		case BF_Par2RefSymStr :  // SAC 4/10/14
		case BF_Par3RefSymStr :  // SAC 4/10/14
         {	bool bDoneParsingLocPar = false;
						/* SAC 1/30/15 - logic to ensure all arguments evaluate via *Valid() functions for certain functions */
						if (crntFunc == BF_IfValidAnd)
							eiParseCount_IfValidAnd++;		
						else if (crntFunc == BF_ValidOr)
							eiParseCount_ValidOr++;		
				if (crntFunc == BF_RuleLib  &&  temp.indexOf(':') < 0)
				{	// new optional final argument of RuleLibrary() can be a local/primary object property (or characer string, in which case we wouldn't get here)
					// => Parse this just like Local()
					// FIRST check if this is just simply a CompID, in which case only very limited parsing is required
         		dbId = (int)BEMPX_GetDBComponentID( name );
         		found = dbId > 0 && dbId <= BEM_MAX_COMP_ID;
         		if ( found )
         		{
         		   ((YYSTYPE*)data)->index = (long)dbId;
         		   *pVar = BEMPELEM;
         			bDoneParsingLocPar = true;
#ifdef YYDEBUG
						_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPELEM %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), dbId );		// SAC 8/31/16
#endif
         		}
					// else - could be a look-up table call designed to return the name of the rulelib item to import...
				}
         	if (!bDoneParsingLocPar &&  crntFunc == BF_RuleLib  &&  temp.indexOf(':'))   // SAC 3/21/13 - added this last check for ':' since it would have to be a NEW format table in order to return a string argument
				{	// SAC 3/21/13 - another special case where an argument of RuleLibrary() could be a table look-up call (to return the name of the object to be imported into the model)
         		// This code checks for the argument being a valid table reference
         		dbId = ruleSet.getTableID( temp.toLocal8Bit().constData() );
         		found = dbId > 0;
         		if ( found )
         		{
         		   ((YYSTYPE*)data)->index = (long long)dbId;
         		   *pVar = BEMPTABLE;
	         		bDoneParsingLocPar = true;
#ifdef YYDEBUG
						_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPTABLE %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), dbId );		// SAC 8/31/16
#endif
         		}
				}
         	if (!bDoneParsingLocPar)
         	{
					int iCurTransID = 0;		QString sRLName;
					if (ruleSet.DataModelRuleActive())	 	// SAC 3/29/14 - enable rulelist expression grouping		// SAC 5/26/16
					{	crntCompID.GetCurrentRulelistName( sRLName );								assert( !sRLName.isEmpty() );
						if (!sRLName.isEmpty())
						{	iCurTransID = GetTransformationIDFromRulelistName( sRLName );
					}	}
					int iTransIdx = RemovePrecedingTransformationID( temp, iCurTransID );  // SAC 7/16/12
					BOOL bTransformIDOK = TRUE;
					if (iTransIdx > 0)
					{	//QString sRLName;		   crntCompID.GetCurrentRulelistName( sRLName );  // SAC 9/25/13
						if (!sRLName.isEmpty() && iTransIdx > iCurTransID)
						{	assert( FALSE );
							bTransformIDOK = FALSE;
						}
					}

					int iSubOrdFunc = 0;
	         	if ( (crntFunc == BF_RuleLib || crntFunc == BF_IfValidAnd || crntFunc == BF_ValidOr || crntFunc == BF_SymString || crntFunc == BF_HrlyResMltNEM) && bTransformIDOK)  // SAC 2/13/14
					{	// need to fully parse RuleLib Object:Property strings (separately), as they may actually by arguments to table look-ups within RuleLib arguments
			// SAC 8/13/14 - mod to ensure that IfValidAnd & ValidOr function arguments translate into LocalVal/ParentVal... (version of routines the require return data to be valid)
			//			iSubOrdFunc = SelectFunctionByArgument( temp, crntFunc, NULL );
						iSubOrdFunc = SelectFunctionByArgument_Local( temp.toLocal8Bit().constData(), crntFunc, NULL, (crntFunc == BF_IfValidAnd || crntFunc == BF_ValidOr) );
//						if (iSubOrdFunc > 0 && (crntFunc == BF_IfValidAnd || crntFunc == BF_ValidOr))
//							sbParsingValidArgToFunc = true;		// SAC 8/13/14 - added to help augment logic tracking when to return ...Val function types
					}

         	   if (iSubOrdFunc < 1 && bTransformIDOK)
					{	int iCompType = 0;
						if ( crntFunc == BF_Local       || crntFunc == BF_LocSymStr  || crntFunc == BF_LocalRef  || crntFunc == BF_LocSymInv  ||   // SAC 8/11/06
         	   	     crntFunc == BF_LCompAssign || crntFunc == BF_LIsDefault || crntFunc == BF_LocStatus || crntFunc == BF_LocalVal   ||
         	   	     crntFunc == BF_LocMxStrLen || crntFunc == BF_LocArrIdx  || crntFunc == BF_LocRefSymStr  /*|| crntFunc == BF_RuleLib*/ )    // SAC 11/20/09  // SAC 3/3/10
         	   	   iCompType = iCompID;
         	   	else
         	   	{	// SAC 12/19/01 - Added code to parse Parent*() arguments when only one Parent* component type exists - to prevent excessive evaluation time parsing.
         	   	   int iNumGens = ((crntFunc == BF_Parent3 || crntFunc == BF_Parent3Ref || crntFunc == BF_Parent3Val || crntFunc == BF_Par3SymStr || crntFunc == BF_Par3RefSymStr) ? 3 :
         	   	                  ((crntFunc == BF_Parent2 || crntFunc == BF_Parent2Ref || crntFunc == BF_Parent2Val || crntFunc == BF_Par2SymStr || crntFunc == BF_Par2RefSymStr) ? 2 : 1 ));
         	   	   iCompType = BEMPX_GetParentComponentType( iCompID, iNumGens );
							if (iCompType <= 0)  // SAC 8/27/12 - added secondary check to see if first property name listed in argument exists for only a SINGLE possible Parent* object type
	      	   	   {	QString sPropOnly = temp;
								if (sPropOnly.indexOf(':') > 0)
									sPropOnly = sPropOnly.left( sPropOnly.indexOf(':') );
							   iCompType = BEMPX_GetParentComponentTypeForProperty( iCompID, sPropOnly.toLocal8Bit().constData(), iNumGens );
							}
         	   	}
               	
         	   	if (iCompType > 0)
         	   	{  // we CAN parse this function call now because there is only one possible parent* component type
							//int iTransIdx = RemovePrecedingTransformationID( temp );  // SAC 7/16/12
         	   	   lMDBID = BEMPX_GetModelDatabaseID( iTransIdx, temp.toLocal8Bit().constData(), iCompType, FALSE, &iRefCompID, &iNumRefComps );
               	
							// Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
							if (iNumRefComps > 1)
							{	// SAC 8/27/12 - need to abort parsing, since the referenced property is found in MULTIPLE objects that could be referenced.
								// Parsing for this argument needs to occur at Evaluation time
								iCompType = -1;
							}
							else
							{
								// SAC 7/10/00 - Added check to confirm that first DBID returned is consistent with the Local component
         	   	   	if (lMDBID > 0)
         	   	   	{
         	   	   	   int iClassID = BEMPX_GetClassID( lMDBID );  // % 1000000 );
         	   	   	   if (iClassID != iCompType)
         	   	   	      lMDBID = -1;  // this will cause return value of FALSE which will trigger output of compilation error
         	   	   	}
               	
								// SAC 7/10/00 - Added check to confirm that the Local() function does not reference sub-components
         	   	   	if (iRefCompID > 0 /*lMDBID >= 1000000*/  &&  (crntFunc == BF_Local  || crntFunc == BF_LocSymStr || crntFunc == BF_LocSymInv ||  // SAC 2/8/01   // SAC 8/11/06
         	   	   	                                             crntFunc == BF_LocMxStrLen || crntFunc == BF_LocArrIdx ||   // SAC 11/20/09  // SAC 3/3/10
         	   	   	                                             crntFunc == BF_Parent || crntFunc == BF_Parent2 || crntFunc == BF_Parent3 || crntFunc == BF_ParStrAElem ||   // SAC 11/20/09
         	   	   	                                             crntFunc == BF_ParSymStr || crntFunc == BF_Par2SymStr || crntFunc == BF_Par3SymStr ))   // SAC 4/10/14
         	   	   	   lMDBID = -1;  // this will cause return value of FALSE which will trigger output of compilation error
               	
								int iError=0;
								std::vector<long long> laArgsToPush;  // SAC 8/27/12
         	   	   	while (lMDBID > 0 && iRefCompID > 0 && iCompType > 0)  // lMDBID >= 1000000)
         	   	   	{
         	   	   	   // Add a node
         	   	   	   //XAddnArg();
         	   	   	   //XExpAddBldgElemNode(lMDBID);  // % 1000000);
									laArgsToPush.push_back( lMDBID );   // SAC 8/27/12 - postpone pushing any arguments onto the stack until we are certain that ALL object referencing arguments can be parsed @ compile time
               	
         	   	   	   // str2 = (strip left portion of str off, up to and including the SECOND ':')
         	   	   	   temp = temp.right( temp.length() - temp.indexOf(':') - 1 );

// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into account (potentially) mulitple compatible referenced obejct types
         	   		      //lMDBID = BEMPX_GetDatabaseID( temp, iRefCompID, FALSE, &iRefCompID );
									BOOL bDBIDValid = FALSE;
		   	   				int i2ndRefCompID = iRefCompID;
									long long l2ndDBID = lMDBID;
									long lPTDBID = BEMPX_MDBIDtoDBID( l2ndDBID );
									BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lPTDBID, iError );						assert( iError==0 );		assert( pPropType );
									for (int iObjCls=0; (pPropType && !bDBIDValid && iCompType > 0 && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
									{	if (pPropType->getObj1ClassIdx( iObjCls ) > 0)
										{	l2ndDBID = BEMPX_GetModelDatabaseID( iTransIdx, temp.toLocal8Bit().constData(), pPropType->getObj1ClassIdx( iObjCls ), FALSE, &i2ndRefCompID, &iNumRefComps );
											if (iNumRefComps > 1)
											{	// SAC 8/27/12 - need to abort parsing, since the referenced property is found in MULTIPLE objects that could be referenced.
												// Parsing for this argument needs to occur at Evaluation time
												iCompType = -1;
											}
											else if (l2ndDBID > 0)
												bDBIDValid = TRUE;
										}
									}
									// update original variables, regardless of whether the processing successfully returned a valid DBID
									lMDBID = l2ndDBID;
									iRefCompID = i2ndRefCompID;
         	   		   }
               	
								if (iCompType > 0)
								{
									for (int iA=0; iA < (int) laArgsToPush.size(); iA++)
									{	XAddnArg();
         	   	   	   	XExpAddBldgElemNode( laArgsToPush[iA] );  // % 1000000);
									}
               	
         	   		   	// The last node is added by calling function.
         	   		   	found = lMDBID > 0;
         	   		   	if ( found )
         	   		   	{	((YYSTYPE*)data)->index = lMDBID;
         	   		   		*pVar = BEMPELEM;
#ifdef YYDEBUG
										_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPELEM %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), lMDBID );		// SAC 8/31/16
#endif
         	   		   	}
								}
         	   		}
						}
               	
         	   	if (iCompType <= 0)  // SAC 8/27/12 - switched from 'else' of above statement to separate if(), allowing above if to switch iCompType in the event that Local*() functions are not able to be parsed @ compile time
         	   	{  // Here is another special case for reference functions.  If the function is Parent*() (or even Local*() as of 8/27/12) -AND- the argument
         	   	   // cannot be parsed @ runtime due to the potential for multiple parents or other objects being referenced, the argument is kept around as 
							// a string.  The arg in the text expression has no qoutes however, and is not handled where regular strings are handled.
         	   	   // The problem is that ExpAddStringNode()expects a pointer into the expression string ending with a '"' to mark the end of the string. 
         	   	   // To get around this, we store the string in a static array, add the qoute char, and set the pointer to this string instead of into the
         	   	   // expression string.
         	   	   *pVar = STRING;
         	   	   strcpy( tempString, name );
         	   	   tempString[ strlen( tempString ) ] = '\"';
         	   	   ((YYSTYPE*)data)->object = tempString;
#ifdef YYDEBUG
							_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), STRING\n", name, crntFunc, (pFuncName ? pFuncName : "?") );		// SAC 8/31/16
#endif
         	   	   if ( strlen( name ) > 0 )
         	   	      found = TRUE;
         	   	}
					}
         	}
			}
         break;
      case BF_SymValue :
         // The argument for SymValue is a string with qoutes.  
         // We should never get here for this function.
         break;
      case BF_ChildCnt    : // convert to 1-based class index
      case BF_Cr8Child    : // "CreateChildren",  4 arguments - first arg is child comp type
      case BF_DelChild    : // "DeleteChildren",  2 arguments - first arg is child comp type
      case BF_Cr8Comp     : // "CreateComp",      3 arguments - first arg is comp type - as of 11/19/14 up to 5 args
      case BF_DelAllComps : // "DeleteAllComps",  2 arguments - first arg is comp type
      case BF_CompExists  : // "CompExists",  SAC 7/6/01 - added - first arg is comp type
      case BF_CompName    : // "CompName",    SAC 2/3/02 - added to return the name of a component - first arg is comp type
      case BF_CompCnt     : // "ComponentCount",  SAC  4/1/02 - first and only argument is a component type
      case BF_ImportComp  : // SAC 1/6/04 - ImportComponentFromFile( <CompType>, <path/filename> )
      case BF_AsgnCr8Comp : // SAC 3/11/14 - AssignOrCreateComp() - first argument comp type, 2nd is comp name, following args are pairs of created comp property name (in quotes) and values/strings/enumerations for each property */
         dbId = (int)BEMPX_GetDBComponentID( name );
         found = dbId > 0 && dbId <= BEM_MAX_COMP_ID;
         if ( found )
         {
            ((YYSTYPE*)data)->index = (long long)dbId;
            *pVar = BEMPELEM;
#ifdef YYDEBUG
					_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPELEM %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), dbId );		// SAC 8/31/16
#endif
         }
         break;
      case BF_Lookup :
         // Args for table lookup are numbers, not parameter ids
         break;
      case BF_CurTime :
      case BF_CurYear :
         // No arguments for CurrentTime() or CurrentYear() so we should never get here.
         break;
      case BF_Date :
      case BF_MoDaShift :
      case BF_MoDaNumDays :
         // Args for BF_MoDaShift & BF_Date are numbers => should never get here
         // SAC 10/24/02 - Added BF_MoDaNumDays
         break;
      case BF_CheckSym :
         // No arguments for EnsureSymbolExists() so we should never get here.
         break;
      case BF_EvalRules :
         // Argument for EvalRulelist() is a character string
         break;
      case BF_DelComp : // "DeleteComp", 1 char string argument => should never get here
         break;
      case BF_StoreBEMProc : // "StoreBEMProc", 1 char string & 1 integer argument => should never get here
         break;
      case BF_FltToStr : // SAC 2/8/01 - "FltToStr", 1 float & 2 integer arguments => should never get here
         break;
      case BF_StrToFlt : // SAC 2/23/16 - "StrToFlt", 1 string argument => should never get here
         break;

      case BF_SplitPath : // SAC 11/5/04 - 1 string & 1 integer arguments => should never get here
         break;

      case BF_ChildIdx : // SAC 2/27/01 - "ChildIndex",     0 (or 1 integer) arguments => should never get here
         break;

      case BF_OpenExpFile  : // SAC 9/15/15 - added OpenExportFile() - 1 fixed argument, path/filename, 2nd optional argument, FileOpen mode (typically 'wt' or 'at' write/append text), return integer file index 0-N or negative error code
      case BF_CloseExpFile : // SAC 9/15/15 - added CloseExportFile() - single argument is index of export file to close, -1 to close ALL files, return number of files closed successfully
      case BF_WriteExpFile : // SAC 9/15/15 - added WriteToExportFile() - same arguments as other message/log functions w/ additional first argument = export file index (0-N) (file pointer provided in ruleset data)
         break;

      case BF_Format      :
      case BF_PostError   :
      case BF_PostWarn    :
      case BF_PostLogMsg  : // SAC 10/30/07
      case BF_MsgBox      : // SAC 9/29/06 - added MessageBox() function
      case BF_WriteToFile : // SAC 6/6/13 - added WriteToFile() - same arguments as other message/log functions (file pointer provided in ruleset data)
         // SAC 5/14/01 - variable args where 1st is format string followed by up to 6 string or numeric arguments to sprintf()
				// SAC 7/6/17 - added code to enable arguments of these functions to include table look-ups
      		dbId = ruleSet.getTableID( name );
      		found = dbId > 0;
      		if ( found )
      		{  ((YYSTYPE*)data)->index = (long long)dbId;
      		   *pVar = BEMPTABLE;
#ifdef YYDEBUG
					_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d (%s), BEMPTABLE %ld\n", name, crntFunc, (pFuncName ? pFuncName : "?"), dbId );
#endif
      		}
         break;

      case BF_UnqCompName :	// SAC 4/9/02 - Added to ensure that a character string is unique across all currently defined BEMProc component names
         // UniqueComponentName():  1 character string argument => no parsing required
         break;

      case BF_ParCompType :      // SAC 2/16/10 - added
         // No arguments for ParentComponentType(), so we should never get here.
         break;

      case BF_CompType :      // SAC 8/20/12 - added
         // Only a single string argument for ComponentType(), but could potentially be the result of other functions, so no parsing done here
         break;

      case BF_FileExists :  // SAC 1/6/04 - FileExists( <path/filename> ) - only char string arg, so should never get here
         break;

      case BF_EnsureChild :   /* SAC  4/27/04 - added */
         // No arguments for EnsureChildAssigned() so we should never get here.
         break;

      case BF_BEMProcDBID:  // BEMProcDBID()    - SAC 6/14/07
         // 2 character string and 1 integer arguments for BEMProcDBID() - should never get here.
         break;

     case BF_YrMoDa2Date :   // long YrMoDaToSerial( int iYr, int iMo, int iDa );  
     case BF_Date2WkDay  :   // int SerialDateToDayOfMonth( long lSerial );        
     case BF_Date2Mo     :   // int SerialDateToMonth( long lSerial );             
     case BF_Date2Yr     :   // int SerialDateToYear( long lSerial );              
     case BF_YrMoDa2DOW  :   // int YrMoDaToDayOfWeek( int iYr, int iMo, int iDa );
         // all integer arguments - should never get here.
         break;

      case BF_FindInStr :  // SAC 7/2/09 - FindInString( <"main string">, <"substring to find"> )
         // 2 character string arguments only - should never get here.
         break;

      case BF_RplcInStr :  // SAC 11/20/09 - ReplaceInString( <"substring to find">, <"replacement string"> )
         // 2 character string arguments only - should never get here.
         break;

      case BF_HrlyResSum :   // SAC 5/15/12 - HourlyResultSum( <"RunName">, <"MeterName">, <"EnduseOne">, ... )
      case BF_HrlyResMult :  // SAC 5/15/12 - ApplyHourlyResultMultipliers( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"EnduseOne">, ... )
      case BF_HrlyResMltNeg :  // SAC 10/4/17 - ApplyHourlyResultMultipliers_Neg( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"EnduseOne">, ... )
      case BF_CopyHrlyRes :  // SAC 10/5/17 - CopyHourlyResults( <"SrcRunName">, <"SrcMeterName">, <"SrcEnduse">, <"DestRunName">, <"DestMeterName">, <"DestEnduseOne"> )
         // no arguments needing parsing - should never get here.
         break;

      case BF_PolyLpArea :  // SAC 5/28/13 - no arguments needing parsing - should never get here.
		case BF_InitPolyLp :  // SAC 10/29/13 - InitializePolyLoop() - no arguments needing parsing - should never get here.
		case BF_Cr8PolyLp  :  // SAC 2/18/14 - no arguments needing parsing - should never get here.
			break;

		case BF_Cr8SCSysRpt : // SAC 3/10/14 - no arguments needing parsing - should never get here.
		case BF_Cr8DHWRpt   : // SAC 3/14/14 - no arguments needing parsing - should never get here.
		case BF_Cr8IAQRpt   : // SAC 3/26/14 - no arguments needing parsing - should never get here.
   	case BF_Cr8DUHVAC :   // SAC 6/27/14 - no arguments needing parsing - should never get here.
   	case BF_Cr8DURpt  :   // SAC 11/15/14 - no arguments needing parsing - should never get here.
   	case BF_Cr8DUWHtr  :   // SAC 5/30/16 - no arguments needing parsing -should never get here.
			break;

      case BF_LogDuration : // SAC 10/24/13 - added
			// LogDuration() - all string or numeric arguments not needing parsing
         break;

      default : 
         // If we're not looking up a function arg, we MAY be looking up a table id.
         dbId = ruleSet.getTableID( name );
         found = dbId > 0;
         if ( found )
         {
            ((YYSTYPE*)data)->index = (long long)dbId;
            *pVar = BEMPTABLE;
#ifdef YYDEBUG
					_snprintf( parseMsg, 256, "         GetNodeType: name '%s', op %d, BEMPTABLE %ld\n", name, crntFunc, dbId );		// SAC 8/31/16
#endif
         }
         break;
   }
   }

#ifdef YYDEBUG
		if (strlen(parseMsg) < 1)
			_snprintf( parseMsg, 256, "         GetNodeType: name '%s', not found\n", name );		// SAC 8/31/16
		ExpPostParserMsg( parseMsg );
#endif

   return (int) found;
}
#pragma warning(default : 4996)



//////////////////////////////////////////////////////////////////////
// Rule evaluation Callbacks...
//////////////////////////////////////////////////////////////////////

static void GetBEMProcData( long long lMDBID, int iOccur, BEM_ObjType eObjType, ExpStack* stack, ExpError* error, BOOL bGetSymStr,
										ExpEvalStruct* pEval, BOOL bReturnInvalidWhenUndefined, int iObjIdxModel=-1 );  // SAC 8/6/10 - added pEval argument   // SAC 2/13/14 - added bReturnInvalidWhenUndefined
static void GetBEMProcDataToNode( ExpNode* pNode, long long lMDBID, int iOccur, BEM_ObjType eObjType, ExpError* error, BOOL bGetSymStr,
										ExpEvalStruct* pEval, BOOL bReturnInvalidWhenUndefined, int iObjIdxModel=-1 );  // SAC 8/6/10 - added pEval argument   // SAC 2/13/14 - added bReturnInvalidWhenUndefined
static void TableLookupFunction(               int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 9/25/02
static void LocalParentChildRef(               int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );
static void BEMProcSumChildrenAllOrRevRef(      int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );
static void ComponentArray(                    int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 3/7/11
static void BEMProc_CountNoRefs(                int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 1/4/02
static void BEMProc_BitwiseMatches(             int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 4/2/02
static void BEMProc_SumIntoArrayElement(        int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 7/21/06
static void BEMProc_EnsureStringUniqueness(     int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 8/25/03
static BOOL CreateDeleteFuncLeftSideOK(        int op, int nArgs,                  ExpEvalStruct* pEval, ExpError* error );
static void CreateChildrenOrComp(              int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );
static void DeleteChildrenCompOrAll(           int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );
static void AssignOrCreateComp(                int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error );  // SAC 3/11/14
static double ConsAssmUFactor( int iCalcMethod, int iConsAssmObjIdx, BEM_ObjType eConsAssmObjType, QString sConsAssmName, ExpEvalStruct* pEval, ExpError* error );
static double ConsUFactorRes( int iCodeVintage, int iConsAssmObjIdx, BEM_ObjType eConsAssmObjType, const QString& sConsName, ExpEvalStruct* pEval, ExpError* error );
static int    CreateSCSysRptObjects(  QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 3/10/14
static int    CreateDHWRptObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 3/14/14
static int    CreateIAQRptObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 3/26/14
static int    CreateDwellUnitHVACSysObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 6/27/14
static int    CreateDwellUnitRptObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 11/15/14
static int    CreateDwellUnitDHWHeaters( QString& sErrMsg, int iDUDHWObjIdx, BEM_ObjType eDUDHWObjType, const QString& sDUDHWName, ExpEvalStruct* pEval, ExpError* error );	// SAC 5/30/16
static int    AddCSEReportColumn( int nArgs, ExpStack* stack, QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error );		// SAC 11/14/16

static long YrMoDaToSerial( int iYr, int iMo, int iDa );     // based on CalUtils -> Serial MakeSerial( int year, int month, int date, BOOL calcLeap );
static int SerialDateToDayOfMonth( long lSerial );           // based on CalUtils -> int Date(    Serial serialDate, BOOL calcLeap );   // Date of month.
static int SerialDateToMonth( long lSerial );                // based on CalUtils -> int Month(   Serial serialDate, BOOL calcLeap );   // Month of year.
static int SerialDateToYear( long lSerial );                 // based on CalUtils -> int Year(    Serial serialDate );                  // Year of century.
static int YrMoDaToDayOfWeek( int iYr, int iMo, int iDa );   // based on CalUtils -> Day WeekDay( Serial serialDate );                  // Day of week.


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  GetValue()
//
// Purpose ------------------------------------------------------------------
//   Returns the numeric value associated with reserved keywords.
//   
// Arguments ----------------------------------------------------------------
//   ExpNode*       result : pointer to structure which holds the result
//   const ExpNode* node   : pointer to node
//   void*          data   : not used
//   
// Return Value -------------------------------------------------------------
//   TRUE if node not of type EXP_Keyword or if keyword is found, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
int GetValue( ExpNode* result, const ExpNode* node, void* /*data*/ )
{ 
   bool ok = TRUE;

   // Get keyword values
   if ( node->type == EXP_Keyword )
   {
      switch ( (int)node->fValue )
      {
         case KW_Default :
            result->type = EXP_Value;
            result->fValue = -99999;
            break;
         case KW_None :
            result->type = EXP_Value;
            result->fValue = -99998;
            break;
         case KW_Unchanged :               // SAC 3/31/01
            result->type = EXP_Value;
            result->fValue = -99997;
            break;
         case KW_Undefined :               // SAC 8/24/01
            result->type = EXP_Value;
            result->fValue = -99996;
            break;
         default :
            ok = FALSE;
            // Bogus value
            break;
      }
   }

   return (int) ok;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Converts "\*" in string to appropriate escape sequence
void ResolveEscapeSequences( QString& str )  // SAC 7/30/02
{
   char* pszSearchFor[]   = { "\\a", "\\b", "\\f", "\\n", "\\r", "\\t", "\\v", "\\?", "\\'", "\\\"", "\\\\", NULL };
   char* pszReplaceWith[] = {  "\a",  "\b",  "\f",  "\n",  "\r",  "\t",  "\v",  "\?",  "\'",   "\"",   "\\" };
   int idx = -1;
   while (pszSearchFor[ ++idx ] != NULL)
      str.replace( pszSearchFor[ idx ], pszReplaceWith[ idx ] );
// DEBUG version
//   {
//      int iNumReplacements = str.replace( pszSearchFor[ idx ], pszReplaceWith[ idx ] );
//      if (iNumReplacements > 0)
//      {
//         QString sMsg = QString( "Replaced %1 occurrences of \"%2\"" ).arg( QString::number( iNumReplacements ), pszSearchFor[ idx ] );
//         BEMMessageBox( sMsg, NULL, 3 /*error*/ );
//      }
//   }
}


/////////////////////////////////////////////////////////////////////////////

// area3D_Polygon(): compute the area of a 3D planar polygon
//  Input:  int n = the number of vertices in the polygon
//          Point* V = an array of n+2 vertices in a plane with V[n]=V[0]
//          Point N = a normal vector of the polygon's plane
//  Return: the (float) area of the polygon
double PolygonArea_OrderDependent( vector<double>& faX, vector<double>& faY, vector<double>& faZ )  //, double Nx, double Ny, double Nz )
{
	int  i, j, k;		 // loop indices
	int n = faX.size();				assert( n > 2 );

// calculate normal vector HERE
	double Nx, Ny, Nz;		Nx = Ny = Nz = 0;
	for (i = 0; i < n; i++)
	{	j = (i + 1) % n;
		Nx += (faY[i] - faY[j]) * (faZ[i] + faZ[j]);
		Ny += (faZ[i] - faZ[j]) * (faX[i] + faX[j]);
		Nz += (faX[i] - faX[j]) * (faY[i] + faY[j]);
	}

// adjust polygon to be consistent w/ header description
	if (faX[0] != faX[n-1] || faY[0] != faY[n-1] || faZ[0] != faZ[n-1])
	{	faX.push_back( faX[0] );
		faY.push_back( faY[0] );
		faZ.push_back( faZ[0] );
	}
	n = faX.size() - 1;

// original area calc code...
	double area = 0;
	double an, ax, ay, az; // abs value of normal and its coords
	int  coord;		   // coord to ignore: 1=x, 2=y, 3=z

	if (n < 3) return 0;  // a degenerate polygon

	// select largest abs coordinate to ignore for projection
	ax = (Nx>0 ? Nx : -Nx);	// abs x-coord
	ay = (Ny>0 ? Ny : -Ny);	// abs y-coord
	az = (Nz>0 ? Nz : -Nz);	// abs z-coord

	coord = 3;					// ignore z-coord
	if (ax > ay) {
		if (ax > az) coord = 1;   // ignore x-coord
	}
	else if (ay > az) coord = 2;  // ignore y-coord

	// compute area of the 2D projection
	for (i=1, j=2, k=0; i<n; i++, j++, k++) {
		switch (coord) {
		  case 1:
			area += (faY[i] * (faZ[j] - faZ[k]));
			continue;
		  case 2:
			area += (faX[i] * (faZ[j] - faZ[k]));
			continue;
		  case 3:
			area += (faX[i] * (faY[j] - faY[k]));
			continue;
		}
	}
	switch (coord) {	// wrap-around term
	  case 1:
		area += (faY[n] * (faZ[1] - faZ[n-1]));
		break;
	  case 2:
		area += (faX[n] * (faZ[1] - faZ[n-1]));
		break;
	  case 3:
		area += (faX[n] * (faY[1] - faY[n-1]));
		break;
	}

	// scale to get area before projection
	an = sqrt( ax*ax + ay*ay + az*az); // length of normal vector
	switch (coord) {
	  case 1:
		area *= (an / (2*ax));
		break;
	  case 2:
		area *= (an / (2*ay));
		break;
	  case 3:
		area *= (an / (2*az));
	}
	return area;  // can be EITHER positive or negative, based on polygon vertex order (CCW vs. CW)
}
double PolygonArea( vector<double>& faX, vector<double>& faY, vector<double>& faZ )  //, double Nx, double Ny, double Nz )
{	return abs( PolygonArea_OrderDependent( faX, faY, faZ ) );  // return absolute value since reverse order vertices results in negative areas
}

/////////////////////////////////////////////////////////////////////////////

BOOL ParseModelDBID( long long lMDBID, int& i0Model, long& lDBID, int& iObjIdx, BEM_ObjType& eObjType, ExpEvalStruct* pEval )  // SAC 5/28/13 - stripped out of BEMPFunction() to reference from elsewhere
{	BOOL bRetVal = TRUE;
	i0Model = -1;
	if (lMDBID > BEM_MODEL_MULT)
	{	 lDBID = (long) BEMPX_MDBIDtoDBID( lMDBID );
		 i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
	}
	else
		 lDBID = (long) lMDBID;
	int iClass = BEMPX_GetClassID( lDBID );
	if (iClass == BEMPX_GetClassID( pEval->lLocDBID ))
	{	 iObjIdx  = pEval->iLocObjIdx ;
		 eObjType = pEval->eLocObjType;
	}
	else if (iClass == BEMPX_GetClassID( pEval->lPrimDBID ))
	{	 iObjIdx  = pEval->iPrimObjIdx ;
		 eObjType = pEval->ePrimObjType;
	}
	else if (iClass == pEval->iPrimPar1Class)
	{	 iObjIdx  = pEval->iPrimParObjIdx ;
		 eObjType = pEval->ePrimParObjType;
	}
	else if (iClass == pEval->iPrimPar2Class)
	{	 iObjIdx  = pEval->iPrimPar2ObjIdx ;
		 eObjType = pEval->ePrimPar2ObjType;
	}
	else if (iClass == pEval->iPrimPar3Class)
	{	 iObjIdx  = pEval->iPrimPar3ObjIdx ;
		 eObjType = pEval->ePrimPar3ObjType;
	}
	else if (BEMPX_GetNumObjects( iClass, BEMO_User, i0Model ) == 1 &&
				!BEMPX_CanCreateAnotherUserObject( iClass, 1, i0Model ))
	{	 iObjIdx  = 0;
		 eObjType = BEMO_User;
	}
	else
		bRetVal = FALSE;

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

static QString sStrFmtErr;
static bool StringFormatValid( QString& sFmtStr, int iChrIdx, ExpError* error )		// SAC 4/25/16 - added to verify valid format for string output
{	iChrIdx++;
	QChar cNext = sFmtStr[iChrIdx++];
	if (cNext == 's' || cNext == 'S')
		return true;
	else if ( cNext == '-' || cNext == ' '  ||    // Flag Directives
				(cNext >= '0' && cNext <= '9') ||    // Width Specification
				 cNext == '.'                    )   // Precision Specification
		return true;	// add more logic here if/when more detailed QC needed
	// if we got here, the format was not recognized
	assert( FALSE );
	sStrFmtErr = QString( "Error:  unable to format the following into a string:  '%1'" ).arg( sFmtStr );
	//BEMPX_WriteLogFile( sErrMsg );
	ExpSetErr( error, EXP_RuleProc, sStrFmtErr );
   return false;
}

static QString sNumFmtErr;
static bool NumericFormatValid( QString& sFmtStr, int iChrIdx, ExpError* error )		// SAC 4/25/16 - added to verify valid format for numeric output
{	iChrIdx++;
	QChar cNext = sFmtStr[iChrIdx++];
	if (cNext == 'e' || cNext == 'E' || cNext == 'f' || cNext == 'g' || cNext == 'G')
		return true;
	else
	{	if ( cNext == '-' || cNext == '+' || cNext == '0' || cNext == ' ' || cNext == '#' )		// Flag Directives
			cNext = sFmtStr[iChrIdx++];
		if (iChrIdx < sFmtStr.length())
		{	while (cNext >= '0' && cNext <= '9' && iChrIdx < sFmtStr.length())					// Width Specification
				cNext = sFmtStr[iChrIdx++];
			if (cNext >= '.' && iChrIdx < sFmtStr.length())												// start of Precision
			{	cNext = sFmtStr[iChrIdx++];
				while (cNext >= '0' && cNext <= '9' && iChrIdx < sFmtStr.length())				// Precision Specification
					cNext = sFmtStr[iChrIdx++];
			}
			while ((cNext == 'h' || cNext == 'l' || cNext == 'I' || cNext == 'L') &&            // Size Prefixes for Type Specifiers
					 iChrIdx < sFmtStr.length())
				cNext = sFmtStr[iChrIdx++];
		}
		if (iChrIdx <= sFmtStr.length() &&
			 (cNext == 'd' || cNext == 'i' || cNext == 'o' || cNext == 'u' || cNext == 'x' ||	// Type Specifiers
      	  cNext == 'X' || cNext == 'e' || cNext == 'E' || cNext == 'f' || cNext == 'g' ||
      	  cNext == 'G' || cNext == 'n' || cNext == 'p'))
      	return true;
	}
	// if we got here, the format was not recognized
	sNumFmtErr = QString( "Error:  unable to format the following numeric string:  '%1'" ).arg( sFmtStr );			assert( FALSE );
	//BEMPX_WriteLogFile( sErrMsg );
	ExpSetErr( error, EXP_RuleProc, sNumFmtErr );
	return false;
}

// SAC 1/26/15 - populate formatted string via subordinate routine to enable access from other routine(s)
// SAC 4/25/16 - added 'error' arg to report errors
// SAC 3/8/17 - added bPreserveNewlines to avoid calling FormatMultilineString() in certain cases, such as during evaluation of WriteToExportFile() or WriteToFile()
static bool ProcessFormatStatement( QString& sRetStr, QString sFormat, ExpNode** pNode, int iNumNodes, ExpError* error, bool bPreserveNewlines )
{	bool bRetVal = true;

		QString sFormatThis;

//		try	// SAC 4/25/16 - insert try/catch to catch rare instances where CString::Format() throws an exception
//		{
                  sRetStr.clear();
                  if (!bPreserveNewlines)  // SAC 3/8/17
							FormatMultilineString( sFormat );	// SAC 5/11/14
                  for (int i=0; (bRetVal && sFormat.length() > 0 && i < iNumNodes); i++)
                  {
                     int iPctIdx = sFormat.indexOf( '%' );
                     if ( iPctIdx < 0 || iPctIdx >= (sFormat.length()-1) )
                        break;
                     else
                     {
                        // Check to confirm this is in fact a format specifier and not just a random '%'
                        QChar cNext = sFormat[iPctIdx+1];
                        if ( cNext == '-' || cNext == '+' || cNext == '0' || cNext == ' ' || cNext == '#' ||   // Flag Directives
                             (cNext >= '0' && cNext <= '9') ||                                                 // Width Specification
                             cNext == '.' ||                                                                   // Precision Specification
                             cNext == 'h' || cNext == 'l' || cNext == 'I' || cNext == 'L' ||                   // Size Prefixes for Type Specifiers
                             cNext == 'c' || cNext == 'C' || cNext == 'd' || cNext == 'i' || cNext == 'o' ||   // Type Specifiers
                             cNext == 'u' || cNext == 'x' || cNext == 'X' || cNext == 'e' || cNext == 'E' ||
                             cNext == 'f' || cNext == 'g' || cNext == 'G' || cNext == 'n' || cNext == 'p' ||
                             cNext == 's' || cNext == 'S' )
                        {
                           // tough to know where END of format specification is, so perform Format() on everything up to the NEXT '%'
                           int iNextPctIdx = sFormat.indexOf( '%', iPctIdx+1 );
                           sFormatThis.clear();
                           if (iNextPctIdx > 0 && iNextPctIdx < sFormat.length())
                           {  // setup FormatThis string to include everything up to and including the character BEFORE the NEXT '%'
                              sFormatThis = sFormat.left( iNextPctIdx );
                              sFormat = sFormat.right( sFormat.length()-iNextPctIdx );  // trim left portion of string
                           }
                           else
                           {  // No more '%', so pass in entire rest of Format string and blank it out for next round
                              sFormatThis = sFormat;
                              sFormat.clear();
                           }

									QString sTemp;
                           if (pNode[i]->type == EXP_String)
                           {	bRetVal = StringFormatValid( sFormatThis, iPctIdx, error );		// SAC 4/25/16 - added to verify valid format for string output
                           	if (bRetVal)
                              	sTemp.sprintf( sFormatThis.toLocal8Bit().constData(), (char*) pNode[i]->pValue );
                           }
								// experiment w/ using '%c' to insert individual ASCII characters - SAC 3/18/12
                           else if (cNext == 'c')
                              sTemp.sprintf( sFormatThis.toLocal8Bit().constData(), (int) pNode[i]->fValue );
                           else
									{	bRetVal = NumericFormatValid( sFormatThis, iPctIdx, error );		// SAC 4/25/16 - added to verify valid format for string output
                           	if (bRetVal)
                           		sTemp.sprintf( sFormatThis.toLocal8Bit().constData(), pNode[i]->fValue );
                           }
                           sRetStr += sTemp;
                        }
                        else
                        {  // The '%' was NOT the start of a format specifier
                           sRetStr += sFormat.left( iPctIdx+1 );
                           if (cNext == '%')  // SAC 5/14/01 - Moved here from above to prevent double '%' from getting echoed to return string
                              iPctIdx++;
                           // trim left portion of string
                           sFormat = sFormat.right( sFormat.length()-iPctIdx-1 );
                           i--;  // SAC 5/14/01 - added to prevent this occurence of '%' from counting against the number of Format() arguments
                        }
                     }
                  }
                  if (sFormat.length() > 0)
                     sRetStr += sFormat;

                  ResolveEscapeSequences( sRetStr );  // SAC 7/30/02
//		}
//		catch( ... )
//		{	QString sErrMsg;		assert( FALSE );
//			if (sFormatThis.isEmpty())
//				sErrMsg = "Error:  Exception thrown while formatting string";
//			else
//				sErrMsg = QString( "Error:  Exception thrown while formatting string '%1'" ).arg( sFormatThis );
//			//BEMPX_WriteLogFile( sErrMsg );
//			ExpSetErr( error, EXP_RuleProc, sErrMsg );
//			bRetVal = false;
//		}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  BEMPFunction()
//
// Purpose ------------------------------------------------------------------
//   Evaluates a node which references or operates on the building database.
//   
// Arguments ----------------------------------------------------------------
//   ExpStack* stack     : expression stack
//   int       op        : function enum
//   int       nArgs     : number of arguments stored on stack
//   void*     pEvalData : structure containing data describing comp/param being evaluated
//   ExpError* error     : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static int AreSame(double a, double b)  /*SAC 4/21/17 - added DBL_EPSILON check to handle float representation issues */
{	return (fabs(a-b) < (10.0*DBL_EPSILON) ? 1 : 0);
}
                                    //  0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20
static const char* spszAppendNum[] = { "th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th", "th" };

#pragma warning(disable : 4996)		// SAC 9/9/16
void BEMPFunction( ExpStack* stack, int op, int nArgs, void* pEvalData, ExpError* error )
{
   ExpEvalStruct* pEval = (ExpEvalStruct*) pEvalData;
   switch ( op )
   {
      case BF_SymValue   : {// "SymValue",    
                            ExpSetErr( error, EXP_RuleProc, "SymValue() function not implemented" );
                            break; }

      case BF_RuleLib    : {//  RuleLibrary( CompType, "RuleLib Comp Name", <Always Retrieve 0/1>, <Imported object parent> )
									 // optional arg #3 => whether to always retrieve item, regardless of it already existing in the model
									 // optional arg #4 => name or object referencs or name DBID to object that is to serve as the Parent of the imported object
                            // Result node is simply the second argument
                            if (nArgs < 2 || nArgs > 4)  // SAC 3/9/13 - added nArgs check
                            {  QString sErrMsg = QString( "Invalid number of RuleLibrary() arguments (%1 found, should be 2-4)" ).arg( QString::number( nArgs ) );
                               ExpSetErr( error, EXP_RuleProc, sErrMsg );
									 }
                            else
                            {  int iImportUniqueRuleLibObjOption = 2;		// was: BOOL bAlwaysRetrieveComp = FALSE;
									 	 QString sLibParentObjectName;
                               ExpNode* pNode = ExpxStackPop( stack );
										 if (nArgs > 3)  // SAC 3/17/13 - added handling of new 4th optional argument
										 {  if (pNode->type == EXP_String)
										 	 {	 sLibParentObjectName = (char*) pNode->pValue;
											 	 assert( !sLibParentObjectName.isEmpty() );
											 }
                                  else if (pNode->type == EXP_Value)
											 {	 //long lParNameDBID = (long) pNode->fValue;
											 	 long lParNameDBID = 0;
                                     long long lMDBID = (long long) pNode->fValue;
												 int i0Model = -1;
												 int iParNameObjIdx = -1;
											    BEM_ObjType eParNameObjType = BEMO_User;
											//	 if (lMDBID > BEM_MODEL_MULT)
											//	 {	 lParNameDBID = (long) BEMPX_MDBIDtoDBID( lMDBID );
											//	 	 i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
											//	 }
											//	 else
											//	 	 lParNameDBID = (long) lMDBID;
										   // 	 int iParNameClass = BEMPX_GetClassID( lParNameDBID );
											//	 if (iParNameClass == BEMPX_GetClassID( pEval->lLocDBID ))
											//	 {	 iParNameObjIdx  = pEval->iLocObjIdx ;
											//	 	 eParNameObjType = pEval->eLocObjType;
											//	 }
											//	 else if (iParNameClass == BEMPX_GetClassID( pEval->lPrimDBID ))
											//	 {	 iParNameObjIdx  = pEval->iPrimObjIdx ;
											//	 	 eParNameObjType = pEval->ePrimObjType;
											//	 }
											//	 else if (iParNameClass == pEval->iPrimPar1Class)
											//	 {	 iParNameObjIdx  = pEval->iPrimParObjIdx ;
											//	 	 eParNameObjType = pEval->ePrimParObjType;
											//	 }
											//	 else if (iParNameClass == pEval->iPrimPar2Class)
											//	 {	 iParNameObjIdx  = pEval->iPrimPar2ObjIdx ;
											//	 	 eParNameObjType = pEval->ePrimPar2ObjType;
											//	 }
											//	 else if (iParNameClass == pEval->iPrimPar3Class)
											//	 {	 iParNameObjIdx  = pEval->iPrimPar3ObjIdx ;
											//	 	 eParNameObjType = pEval->ePrimPar3ObjType;
											//	 }
											//	 else
											// SAC 5/28/13 - replaced above w/ following call
												 if (!ParseModelDBID( lMDBID, i0Model, lParNameDBID, iParNameObjIdx, eParNameObjType, pEval ))
			                            {  QString sErrMsg = QString( "Unable to retrieve library object parent name, argument #4, DBID %1" ).arg( QString::number( lParNameDBID ) );
			                               ExpSetErr( error, EXP_RuleProc, sErrMsg );
												 }
												 if (iParNameObjIdx >= 0)
												 {
										          int iDataType, iSpecialVal, iError = 0;
            						//			 void* pData = (void*) BEMPX_GetData( lParNameDBID, iDataType, iSpecialVal, iError, iParNameObjIdx, eParNameObjType, FALSE, i0Model );
            						//			 if (pData != NULL)
            						//			 {
            						//			    if (iDataType == BEMP_Obj)
										//				 {	 CBEMObject* pParObj = (CBEMObject*) pData;
										//			 	 	 sLibParentObjectName = pParObj->m_sObjectName;
										//				 }
										//				 else if (iDataType == BEMP_Str)
										//				 	 sLibParentObjectName = *(QString*) pData;
										//				 else
					               //             {  QString sErrMsg = QString( "Library object parent name property not a valid type (expecting object or string), argument #4, DBID %1" ).arg( QString::number( lParNameDBID ) );
					               //                ExpSetErr( error, EXP_RuleProc, sErrMsg );
										//				 }
										//			 }
													iDataType = BEMPX_GetDataType( lParNameDBID );
													switch (iDataType)
													{	case BEMP_Obj : {	BEMObject* pObj = BEMPX_GetObjectPtr( lParNameDBID, iSpecialVal, iError, iParNameObjIdx, eParNameObjType, i0Model );
																				if (pObj)
																					sLibParentObjectName = pObj->getName();
																			 }	break;
														case BEMP_Str : {	QString str = BEMPX_GetString( lParNameDBID, iSpecialVal, iError, iParNameObjIdx, eParNameObjType, i0Model );
																					sLibParentObjectName = str;
																			 }	break;
														default		  : {	QString sErrMsg = QString( "Library object parent name property not a valid type (expecting object or string), argument #4, DBID %1" ).arg( QString::number( lParNameDBID ) );
																				ExpSetErr( error, EXP_RuleProc, sErrMsg );
																			 }	break;
													}
												 }
											 }
											 else
                                     ExpSetErr( error, EXP_RuleProc, "Invalid RuleLibrary() 3rd argument (should be 0/1)" );
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );

											 if (!sLibParentObjectName.compare("NONE", Qt::CaseInsensitive))  // prevent bogus parent object name from propgating into the BEM data setting routine
											 	sLibParentObjectName.clear();
										 }

										 if (nArgs > 2)  // SAC 3/9/13 - added handling of new 3rd optional argument
										 {  if (pNode->type != EXP_Value)
                                     ExpSetErr( error, EXP_RuleProc, "Invalid RuleLibrary() 3rd argument (should be 0/1)" );
                                  else
											    //bAlwaysRetrieveComp = (pNode->fValue > 0.1);
												 iImportUniqueRuleLibObjOption = (int) pNode->fValue;	// SAC 4/25/14
														//	0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
														//	1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
														//	2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
										 }

                               if (pNode->type != EXP_String)
                                  ExpSetErr( error, EXP_RuleProc, "Invalid RuleLibrary() 2nd argument (should be character string)" );
                               
                               // Simply trash the first node = comp ID (don't need it)
                               ExpNode* pJunkNode = ExpxStackPop( stack );
                               ExpxNodeDelete( pJunkNode );
                               
                               // Push second argument node back onto the stack to serve as return value
                               ExpxStackPush( stack, pNode );
                               
                               // SAC 4/28/99 - Set eNewObjType to RuleLib so the data setting stuff knows to search there for the component
                               pEval->eNewObjType = BEMO_RuleLib;
										 pEval->iImportUniqueRuleLibObjOption = iImportUniqueRuleLibObjOption;  // SAC 3/10/13 - added to cause rule library imports to create new objects with each RuleLib evaluation (as opposed to importing only once and providing multiple references to the single imported object)	// SAC 4/25/14
										 pEval->sImportRuleLibParentName = sLibParentObjectName;  // SAC 3/17/13 - name of parent of rule lib object to import
									 }
                            break; }
      case BF_Parent     :  // "Parent",      
      case BF_Parent2    :  // "Parent2",      
      case BF_Parent3    : {// "Parent3",      
                            ExpNode* pNode = ExpxStackPop( stack );

                            int iParClass = (op == BF_Parent ? pEval->iPrimPar1Class : (op == BF_Parent2 ? pEval->iPrimPar2Class : pEval->iPrimPar3Class));
                            if (iParClass <= 0)
                            {  // push a 0-value node onto the stack to prevent a bunch of error messages
                               ExpNode* p0Node = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                               p0Node->type = EXP_Value;
                               p0Node->fValue = 0.0;
                               ExpxStackPush( stack, p0Node );
                            }
                            else
                            {
										 int iTransIdx = -1;
                               if (pNode->type == EXP_String)
                               {
                                  int iRefCompID = 0;  // SAC 7/17/01
											 QString sParArg = (char*) pNode->pValue;
																			assert( !ruleSet.IsDataModel() || (pEval && !pEval->sRuleListName.isEmpty()) );
											 int iCurTransID = ((ruleSet.IsDataModel() && pEval && !pEval->sRuleListName.isEmpty()) ? GetTransformationIDFromRulelistName( pEval->sRuleListName ) : 0); 	// SAC 3/29/14 - enable rulelist expression grouping
											 iTransIdx = RemovePrecedingTransformationID( sParArg, iCurTransID );
                                  long long dbId = BEMPX_GetModelDatabaseID( iTransIdx, sParArg.toLocal8Bit().constData(), iParClass, FALSE, &iRefCompID );
											 // Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference

											 // SAC 7/10/00 - Added check to confirm that first DBID returned is consistent with the Parent* class
                                  if (dbId > 0)
                                  {
                                     int iClassID = BEMPX_GetClassID( dbId );  // % 1000000 );
                                     if (iClassID != iParClass)
                                        dbId = -1;  // this will cause return value of FALSE which will trigger output of compilation error
                                  }

											 // SAC 7/10/00 - Added check to confirm that the Parent*() functions do not reference sub-components
                                  if (iRefCompID > 0)  // dbId >= 1000000)
                                     dbId = -1;  // this will cause return value of FALSE which will trigger output of compilation error

                                  if (dbId > 0)
                                  {
                                     free( pNode->pValue );
                                     pNode->type = EXP_Value;
                                     pNode->fValue = (double) dbId;
                                  }
                               }

                               if (iTransIdx > 0 && iTransIdx > (BEMPX_GetActiveModel()+1))	// SAC 9/25/13 - added check to ensure valid transform index
										 	 ExpSetErr( error, EXP_RuleProc, "Invalid Parent*() argument transform ID (may only reference the current or a prior transform)" );
										 else if (pNode->type == EXP_Value)
                               {
                                  int        iParObjIdx  = (op == BF_Parent  ? pEval->iPrimParObjIdx   :
                                                           (op == BF_Parent2 ? pEval->iPrimPar2ObjIdx  : pEval->iPrimPar3ObjIdx ));
                                  BEM_ObjType eParObjType = (op == BF_Parent  ? pEval->ePrimParObjType  :
                                                           (op == BF_Parent2 ? pEval->ePrimPar2ObjType : pEval->ePrimPar3ObjType));
                                  GetBEMProcData( (long long) pNode->fValue, iParObjIdx, eParObjType, stack, error, ruleSet.IsDataModel()/*bGetSymStr*/, pEval, FALSE );  // SAC 10/18/12 - revised bGetSymStr to retrieve string for DataModel rulesets
                               }
                               else
                                  ExpSetErr( error, EXP_RuleProc, "Invalid Parent() argument" );
                            }
                            ExpxNodeDelete( pNode );
                            break; }

      case BF_LocSymInv  :  // SAC 8/11/06 - added LocalSymbolInvalid()
                           {  ExpNode* pNode = ExpxStackPop( stack );
                              if (pNode->type == EXP_Value)
                              {
											long lDBID = 0;
											long long lMDBID = (long long) pNode->fValue;
											int iBEMProcIdx = -1;
											if (lMDBID > BEM_MODEL_MULT)
											{	iBEMProcIdx = (int) BEMPX_GetModelID( lMDBID ) - 1;
												lDBID = BEMPX_MDBIDtoDBID( lMDBID );
											}
											else
												lDBID = (long) lMDBID;
                                 if (BEMPX_GetDefaultSymbolIfInvalid( lDBID, pEval->iPrimObjIdx, pEval->ePrimObjType, FALSE, iBEMProcIdx ) == 1)
                                    pNode->fValue = (double) 0;  // local symbol value IS VALID
                                 else
                                    pNode->fValue = (double) 1;  // local symbol value IS NOT VALID
                              }
                              else
                              {
                                 ExpSetErr( error, EXP_RuleProc, "Invalid LocalSymbolInvalid() argument" );
                                 pNode->fValue = 1;
                              }
                              ExpxStackPush( stack, pNode );
                            break; }

      case BF_LocSymStr  :  // SAC 2/8/01
      case BF_Local      : {// "Local",       
                            ExpNode* pNode = ExpxStackPop( stack );
									 if (!pNode)
                            	  ExpSetErr( error, EXP_RuleProc, "Local*() argument not found" );
									 else
									 {	if (pNode->type == EXP_Value)
                            	   GetBEMProcData( (long long) pNode->fValue, pEval->iPrimObjIdx, pEval->ePrimObjType, stack, error, (op == BF_LocSymStr || ruleSet.IsDataModel()), pEval, FALSE );  // SAC 10/18/12 - revised bGetSymStr to retrieve string for DataModel rulesets
                            	else
                            	   ExpSetErr( error, EXP_RuleProc, "Invalid Local*() argument" );
                            	ExpxNodeDelete( pNode );
									 }
                            break; }

      case BF_Global      :   // "Global",      
      case BF_GlobSymStr  :   // "GlobalSymbolString" - SAC 7/25/01
//      case BF_GlobStatus  :   // "GlobalStatus" - SAC 8/24/01
      case BF_GCompAssign : { // "GlobalCompAssigned" - SAC 5/12/12
										assert( nArgs < 2 );  // following code not setup to handle multiple arguments (which is why GlobalStatus() now handled below)
                            ExpNode* pNode = ExpxStackPop( stack );
									 if (!pNode)
                            	  ExpSetErr( error, EXP_RuleProc, "Global*() argument not found" );
									 else
                            {	if (pNode->type == EXP_Value)
                            	{  long lDBID = 0;
                            	   long long lMDBID = (long long) pNode->fValue;
											int iBEMProcIdx = -1;
											if (lMDBID > BEM_MODEL_MULT)
											{	iBEMProcIdx = (int) BEMPX_GetModelID( lMDBID ) - 1;
												lDBID = BEMPX_MDBIDtoDBID( lMDBID );
											}
											else
												lDBID = (long) lMDBID;
                            	   int i1Class = BEMPX_GetClassID( lDBID );
                            	   int iError;
                            	   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
                            	   if (iError >= 0 && pClass != NULL)
                            	   {
                            	      if (pClass->getMaxDefinable() != 1)  // SAC 1/23/12 - was:  > 1)
                            	         ExpSetErr( error, EXP_RuleProc, "Invalid Global() component type" );
                            	      else if (op == BF_GlobStatus || op == BF_GCompAssign)  // SAC 5/12/12
                            	      {  // SAC 8/24/01 - based on similar code within LocalParentChildRef()
                            	         // Setup node to be pushed onto stack
                            	         ExpNode* pRetNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                            	         pRetNode->type = EXP_Value;
                            	      	if (op == BF_GlobStatus)
                            	            pRetNode->fValue = BEMPX_GetDataStatus( lDBID, 0, BEMO_User, iBEMProcIdx );
									 	  		   else
									 	  		   {  // Get pointer to object which we are trying to find out is assigned or not
   								 	  		      int iDataStatus, iDataType, iSpecialVal;
														iDataType = BEMPX_GetDataType( lDBID );
            					 	  		//      void* pData = BEMPX_GetDataAndStatus( lDBID, iDataStatus, iDataType, iSpecialVal, iError, -1, BEMO_User, FALSE, iBEMProcIdx );
														BEMObject* pObj = BEMPX_GetObjectAndStatus( lDBID, iDataStatus, iSpecialVal, iError, -1, BEMO_User, iBEMProcIdx );
            					 	  		      // SAC 8/7/10 - implementation of targeted debug output
            					 	  		      if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lDBID, 0 /*iOccur*/ ))
            					 	  		         ReportTargetedDebugInfo( pEval, iDataType, lDBID, 0 /*iOccur*/, BEMO_User /*eObjType*/, "BEMPFunction() on GlobalCompAssigned()", iBEMProcIdx );
            					 	  		      // set return value
            					 	  		      pRetNode->fValue = ((iError >= 0 && pObj && iDataStatus > 0) ? 1.0 : 0.0);  // SAC 11/17/13 - fixed bug by replacing pNode-> with pRetNode-> here
									 	  		   }
                            	         ExpxStackPush( stack, pRetNode );  // push result node onto stack
                            	      }
                            	      else
													// SAC 4/2/14 - replaced 'lDBID' with 'lMDBID' to ensure that MODEL index is accounted for in all Global() data retrieval
                            	         GetBEMProcData( lMDBID, 0, BEMO_User, stack, error, (op == BF_GlobSymStr || ruleSet.IsDataModel()), pEval, FALSE );  // SAC 10/18/12 - revised bGetSymStr to retrieve string for DataModel rulesets
                            	   }
                            	}
                            	else
                            	   ExpSetErr( error, EXP_RuleProc, "Invalid Global*() argument" );
                            	ExpxNodeDelete( pNode );
									 }
                            break; }

      case BF_SumAll     :  // "SumAll",      
      case BF_SumChld    :  // "SumChildren", 
      case BF_SumRevRef  :  // "SumRevRef", 
      case BF_MaxChild   :  // "MaxChild", 
      case BF_MaxAll     :  // "MaxAll", 
      case BF_MaxRevRef  :  // "MaxRevRef", 
      case BF_MinChild   :  // "MinChild", 
      case BF_MinAll     :  // "MinAll", 
      case BF_MinRevRef  :  // "MinRevRef", 
      case BF_CountRefs  :  // "CountRefs", 
      case BF_CountUPRefs : // "CountUniqueParentRefs"
      case BF_MaxRevRefC :  // "MaxRevRefComp",  SAC 1/9/02
      case BF_MaxAllComp :  // "MaxAllComp",  SAC 1/25/02
      case BF_MaxRevRefA :  // "MaxRevRefArray",  SAC 11/10/04
      case BF_CountOccur :  // SAC 5/4/06 - implemented CountOccurrences() - first argument should be Comp:Param string, second a number
      case BF_SumRevRefEx : // SAC 8/1/06 - SumRevRefEx()
      case BF_SumAcrsIf  :  // SAC 2/15/13 - SumAcrossIf( Comp:ParamDBID, <Condition> ), where <Condition> is typically something like "Comp:ParamDBID = "Option""
      case BF_SumChldIf  :  // SAC 2/15/13 - SumChildrenIf( ChildComp:ParamDBID, <Condition> ), where <Condition> is typically something like "ChildComp:ParamDBID = "Option""
		case BF_MaxChildC  :  // SAC 10/18/14
		case BF_MinChildC  :  // SAC 10/18/14
		case BF_ListRevRef   :  // SAC 1/26/15 - ListRevRef(   RevRefObj:Prop,              "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
		case BF_ListRevRefIf :  // SAC 1/26/15 - ListRevRefIf( RevRefObj:Prop, <Condition>, "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
                            BEMProcSumChildrenAllOrRevRef( op, nArgs, stack, pEval, error );
                            break;

      case BF_ConsUFctr  :	// SAC 6/12/13 - ConsAssmUFactor() has 1 argument, calculation method, which may be entered as an Object:Property path
      case BF_ConsUFctrR :	// SAC 2/21/14 - ConsUFactorRes() has 1 argument, code vintage (for future use)
									{	double dUFactor = -1;
										ExpNode* pNode = NULL;
										QString sErrMsg;
										QString sFuncName = (op==BF_ConsUFctr ? "ConsAssmUFactor" : "ConsUFactorRes");
										if (nArgs != 1)
										{  sErrMsg = QString( "Invalid number of %1() arguments (%2 found, expecting 1)" ).arg( sFuncName, QString::number( nArgs ) );
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
										}
										else
										{	int iSpecialVal, iError;
											int iCalcMethod = 1, iCodeVint = 0;
											pNode = ExpxStackPop( stack );
	                           	if (pNode->type != EXP_Value)
											{  if (op==BF_ConsUFctr)
													sErrMsg = QString( "Invalid %1() argument, expecting calculation method (1 - CBECC-Com2013 (no other options at this time))" ).arg( sFuncName );
												else
													sErrMsg = QString( "Invalid %1() argument, expecting code vintage (future use)" ).arg( sFuncName );
											   ExpSetErr( error, EXP_RuleProc, sErrMsg );
											}
											else if (op==BF_ConsUFctr)
                            		{  iCalcMethod = (int) pNode->fValue;
												if (iCalcMethod < 1 || iCalcMethod > 1)
												{  sErrMsg = QString( "Invalid %1() calculation method (%2, expecting 1 (CBECC-Com2013) (no other options available at this time))" ).arg( sFuncName, QString::number( iCalcMethod ) );
												   ExpSetErr( error, EXP_RuleProc, sErrMsg );
													iCalcMethod = 1;
												}
											}
											else
                            			iCodeVint = (int) pNode->fValue;
                            		if (pNode)
												ExpxNodeDelete( pNode );

											int iConsObjIdx = -2;
											BEM_ObjType eConsObjType = BEMO_User;
											QString sConsName;
											QString sObjType = (op==BF_ConsUFctr ? "ConsAssm" : "Cons");
											int iCID_Cons = BEMP_GetDBComponentID( sObjType );							assert( iCID_Cons > 0 );
											if (TRUE)
											{
										// identify Cons to calculate the Ufactor of...
												if (BEMPX_GetClassID( pEval->lPrimDBID ) == iCID_Cons)
												{	iConsObjIdx  = pEval->iPrimObjIdx;
													eConsObjType = pEval->ePrimObjType;
													sConsName = BEMPX_GetString( BEMPX_GetDBID( iCID_Cons, 0, BEM_PARAM0_NAME ), iSpecialVal, 
																								iError, iConsObjIdx, eConsObjType );
												}
												else if (BEMPX_GetClassID( pEval->lLocDBID ) == iCID_Cons)
												{	iConsObjIdx  = pEval->iLocObjIdx;
													eConsObjType = pEval->eLocObjType;
													sConsName = BEMPX_GetString( BEMPX_GetDBID( iCID_Cons, 0, BEM_PARAM0_NAME ), iSpecialVal, 
																								iError, iConsObjIdx, eConsObjType );
												}
												if (iConsObjIdx < 0)
												{  sErrMsg = QString( "Unable to identify %1 to calculate U-factor of (via %2())" ).arg( sObjType, sFuncName );
													ExpSetErr( error, EXP_RuleProc, sErrMsg );
												}
											}

											if (op==BF_ConsUFctr)
												dUFactor = ConsAssmUFactor( iCalcMethod, iConsObjIdx, eConsObjType, sConsName, pEval, error );
											else
												dUFactor = ConsUFactorRes( iCodeVint, iConsObjIdx, eConsObjType, sConsName, pEval, error );

											if (pEval->bVerboseOutput)
											{	sErrMsg = QString( "      %1() on '%2' --> %3  %4" ).arg( sFuncName, sConsName, QString::number( dUFactor, 'g' ), (dUFactor < 0 ? "(error occurred)" : "") );
												//BEMMessageBox( sErrMsg, NULL, 3 /*error*/ );
   										   BEMPX_WriteLogFile( sErrMsg );
											}
										}

										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (dUFactor >= 0)
										{	pNode->type = EXP_Value;
											pNode->fValue = dUFactor;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0.0;
										}
										ExpxStackPush( stack, pNode );
									}	break;

   	case BF_Cr8DUWHtr  :   // SAC 5/30/16 - CreateDwellUnitDHWHeaters( <DwellUnitDHW name> )
									{	double dNumCreated = -1;
										QString sErrMsg;
										int iDUDHWObjIdx = -2, iSpecialVal, iError;
										BEM_ObjType eDUDHWObjType = BEMO_User;
										QString sDUDHWName;
										QString sObjType = "DwellUnitDHW";
										int iCID_DUDHW = BEMP_GetDBComponentID( sObjType );							assert( iCID_DUDHW > 0 );
										if (TRUE)
										{
									// identify DUDHW to calculate the Ufactor of...
											if (BEMPX_GetClassID( pEval->lPrimDBID ) == iCID_DUDHW)
											{	iDUDHWObjIdx  = pEval->iPrimObjIdx;
												eDUDHWObjType = pEval->ePrimObjType;
												sDUDHWName = BEMPX_GetString( BEMPX_GetDBID( iCID_DUDHW, 0, BEM_PARAM0_NAME ), iSpecialVal, 
																							iError, iDUDHWObjIdx, eDUDHWObjType );
											}
											else if (BEMPX_GetClassID( pEval->lLocDBID ) == iCID_DUDHW)
											{	iDUDHWObjIdx  = pEval->iLocObjIdx;
												eDUDHWObjType = pEval->eLocObjType;
												sDUDHWName = BEMPX_GetString( BEMPX_GetDBID( iCID_DUDHW, 0, BEM_PARAM0_NAME ), iSpecialVal, 
																							iError, iDUDHWObjIdx, eDUDHWObjType );
											}
											if (iDUDHWObjIdx < 0)
											{  sErrMsg = QString( "Unable to identify %1 to create water heaters of (via CreateDwellUnitDHWHeaters())" ).arg( sObjType );
												ExpSetErr( error, EXP_RuleProc, sErrMsg );
											}
										}

										dNumCreated = CreateDwellUnitDHWHeaters( sErrMsg, iDUDHWObjIdx, eDUDHWObjType, sDUDHWName, pEval, error );
										if (!sErrMsg.isEmpty())
   									   BEMPX_WriteLogFile( sErrMsg );
										else if (pEval->bVerboseOutput)
										{	sErrMsg = QString( "      CreateDwellUnitDHWHeaters() on '%1' --> %2  %3" ).arg( sDUDHWName, QString::number( dNumCreated ), (dNumCreated < 0 ? "(error occurred)" : "") );
 										   BEMPX_WriteLogFile( sErrMsg );
										}

										ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (dNumCreated >= 0)
										{	pNode->type = EXP_Value;
											pNode->fValue = dNumCreated;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0.0;
										}
										ExpxStackPush( stack, pNode );
									}	break;

		case BF_Cr8SCSysRpt : // SAC 3/10/14 - Creates SCSysRpt 
		case BF_Cr8DHWRpt :   // SAC 3/14/14 - added
		case BF_Cr8IAQRpt :   // SAC 3/26/14 - added CreateIAQRptObjects()
   	case BF_Cr8DUHVAC :   // SAC 6/27/14 - added CreateDwellUnitHVACSysObjects()
   	case BF_Cr8DURpt  :   // SAC 11/15/14 - added CreateDwellUnitRptObjects()
      case BF_AddCSERptCol  :  // SAC 11/14/16 - added "AddCSEReportCol" w/ second argument that may be object cseReportCol reference property
									{	ExpNode* pNode = NULL;
										QString sErrMsg;
										int iNumObjsCreated = (	 op == BF_Cr8SCSysRpt  ? CreateSCSysRptObjects(				sErrMsg, pEval, error ) :
																		(op == BF_Cr8DHWRpt    ? CreateDHWRptObjects( 				sErrMsg, pEval, error ) : 
																		(op == BF_Cr8IAQRpt    ? CreateIAQRptObjects( 				sErrMsg, pEval, error ) :
																		(op == BF_Cr8DUHVAC    ? CreateDwellUnitHVACSysObjects(	sErrMsg, pEval, error ) :
																		(op == BF_AddCSERptCol ? AddCSEReportColumn( nArgs, stack, sErrMsg, pEval, error ) :
																										 CreateDwellUnitRptObjects(		sErrMsg, pEval, error ) )))));
										if (pEval->bVerboseOutput && !sErrMsg.isEmpty())
											//BEMMessageBox( sErrMsg, NULL, 3 /*error*/ );
   									   BEMPX_WriteLogFile( sErrMsg );
										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (sErrMsg.isEmpty())
										{	pNode->type = EXP_Value;
											pNode->fValue = (double) iNumObjsCreated;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0.0;
										}
										ExpxStackPush( stack, pNode );
									}	break;

      case BF_DayltArea :    // SAC 10/1/13 - DaylightableArea() has 1 argument, daylight calc methodology/vintage, which may be entered as an Object:Property path
									{	double dDayltArea = -1;
										ExpNode* pNode = NULL;
										QString sErrMsg;
										if (!ruleSet.initGeomIDs( pEval, error ))  // SAC 10/1/13
										{	// do nothing here - error already posted
										}
										else if (nArgs != 1)
										{  sErrMsg = QString( "Invalid number of DaylightableArea() arguments (%1 found, expecting 1)" ).arg( QString::number( nArgs ) );
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
										}
										else
										{	int iError, iSpecialVal;
											int iCalcMethod = 1;
											pNode = ExpxStackPop( stack );
	                           	if (pNode->type != EXP_Value)
												ExpSetErr( error, EXP_RuleProc, "Invalid DaylightableArea() argument, expecting calculation method (1 - CBECC-Com2013 (no other options at this time))" );
											else
                            		{  iCalcMethod = (int) pNode->fValue;
												if (iCalcMethod < 1 || iCalcMethod > 1)
												{  sErrMsg = QString( "Invalid DaylightableArea() calculation method (%1, expecting 1 (CBECC-Com2013) (no other options available at this time))" ).arg( QString::number( iCalcMethod ) );
												   ExpSetErr( error, EXP_RuleProc, sErrMsg );
													iCalcMethod = 1;
												}
											}
                            		if (pNode)
												ExpxNodeDelete( pNode );

											int iSpcObjIdx = -2;
											QString sSpcName;
											if (TRUE)
											{
										// identify Space to calculate the Daylightable Area of...
												if (BEMPX_GetClassID( pEval->lPrimDBID ) == ruleSet.getGeomIDs()->m_iOID_Spc)
												{	iSpcObjIdx  = pEval->iPrimObjIdx;
													sSpcName = BEMPX_GetString( BEMPX_GetDBID( ruleSet.getGeomIDs()->m_iOID_Spc, 0, BEM_PARAM0_NAME ),  
																								iSpecialVal, iError, iSpcObjIdx );
												}
												else if (BEMPX_GetClassID( pEval->lLocDBID ) == ruleSet.getGeomIDs()->m_iOID_Spc)
												{	iSpcObjIdx  = pEval->iLocObjIdx;
													sSpcName = BEMPX_GetString( BEMPX_GetDBID( ruleSet.getGeomIDs()->m_iOID_Spc, 0, BEM_PARAM0_NAME ),  
																								iSpecialVal, iError, iSpcObjIdx );
												}
												if (iSpcObjIdx < 0)
													ExpSetErr( error, EXP_RuleProc, "Unable to identify Spc to calculate Daylightable Area of (via DaylightableArea())" );
											}

										// Calculate Daylighting
											dDayltArea = CalcDaylighting( iCalcMethod, iSpcObjIdx, sSpcName.toLocal8Bit().constData(), pEval, error );

											if (pEval->bVerboseOutput)
											{	sErrMsg = QString( "      DaylightableArea() on '%1' --> %2  %3" ).arg( sSpcName, QString::number( dDayltArea ), (dDayltArea < 0 ? "(error occurred)" : "") );
												//BEMMessageBox( sErrMsg );
   										   BEMPX_WriteLogFile( sErrMsg );
											}
										}

										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (dDayltArea >= 0)
										{	pNode->type = EXP_Value;
											pNode->fValue = dDayltArea;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0.0;
										}
										ExpxStackPush( stack, pNode );
									}	break;

      case BF_ScalePolyLp : // SAC 5/28/13 - 1st arg is a scale method (0/1/...), 2nd is a scaling factor which may be simply an Object:Property path
      case BF_PolyLpArea  : // SAC 5/28/13 - no arguments needing parsing - should never get here.
                           {  double fPolyArea = -1;
										ExpNode* pNode = NULL;
										QString sErrMsg;
										if (!ruleSet.initGeomIDs( pEval, error ))  // SAC 10/1/13
										{	// do nothing here - error already posted
										}
										else if (op == BF_ScalePolyLp && nArgs != 2)
										{  sErrMsg = QString( "Invalid number of ScalePolyLoop() arguments (%1 found, expecting 2)" ).arg( QString::number( nArgs ) );
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
										}
										else
										{	int iError, iSpecialVal;
											double fScaleFactor = -1;
											QString sScalePolyName;
											if (op == BF_ScalePolyLp)
											{	pNode = ExpxStackPop( stack );
	                           		if (pNode->type != EXP_Value)
													ExpSetErr( error, EXP_RuleProc, "Invalid first ScalePolyLoop() argument, expecting numeric database ID" );
												else
                            			{  long lScaleDBID = 0;
                            			   long long lMDBID = (long long) pNode->fValue;
													int iBEMProcIdx = -1;
													int iScaleObjIdx = -1;
													BEM_ObjType eScaleObjType = BEMO_User;
													if (!ParseModelDBID( lMDBID, iBEMProcIdx, lScaleDBID, iScaleObjIdx, eScaleObjType, pEval ))
													{  sErrMsg = QString( "Unable to decipher PolyLoop scaling factor DBID (%1) (argument #1)" ).arg( QString::number( lScaleDBID ) );
													   ExpSetErr( error, EXP_RuleProc, sErrMsg );
													}
													else
													{  int iDataType, iSpecialVal, iError = 0, iStatus = 0;
										//			   void* pData = (void*) BEMPX_GetData( lScaleDBID, iDataType, iSpecialVal, iError, iScaleObjIdx, eScaleObjType, FALSE, iBEMProcIdx );
														double dData = BEMPX_GetFloatAndStatus( lScaleDBID, iStatus, iSpecialVal, iError, iScaleObjIdx, eScaleObjType, iBEMProcIdx );
													   if (iStatus < 1)
														{  sErrMsg = QString( "Unable to retrieve PolyLoop scaling factor, argument #1, DBID %1" ).arg( QString::number( lScaleDBID ) );
														   ExpSetErr( error, EXP_RuleProc, sErrMsg );
														}
														else
													   {	fScaleFactor = dData;
															if (fScaleFactor <= 0 || fScaleFactor > 1)
															{  sErrMsg = QString( "Invalid PolyLoop scaling factor (%1), argument #1" ).arg( QString::number( fScaleFactor ) );
															   ExpSetErr( error, EXP_RuleProc, sErrMsg );
													   		fScaleFactor = -1;
															}
														}
													}
												}
                            			if (pNode)
													ExpxNodeDelete( pNode );
											}

											int iScaleMethod = -1;
											if (op == BF_ScalePolyLp)
											{	pNode = ExpxStackPop( stack );
	                           		if (pNode->type != EXP_Value)
													ExpSetErr( error, EXP_RuleProc, "Invalid second ScalePolyLoop() argument, expecting scaling method (0-VerticalGlazing or 1-Skylight)" );
												else
                            			{  iScaleMethod = (int) pNode->fValue;
													if (iScaleMethod < 0 || iScaleMethod > 1)
													{  sErrMsg = QString( "Invalid PolyLoop scaling method (%1, expecting 0(VerticalGlazing) or 1(Skylight))" ).arg( QString::number( iScaleMethod ) );
													   ExpSetErr( error, EXP_RuleProc, sErrMsg );
														iScaleMethod = -1;
													}
												}
                            			if (pNode)
													ExpxNodeDelete( pNode );
											}

											int iPolyLpObjIdx = -2;
											BEM_ObjType ePolyLpObjType = BEMO_User;
											int iCID_PolyLp = ruleSet.getGeomIDs()->m_iOID_PolyLp;		// SAC 10/1/13 - was: BEMPX_GetDBComponentID( "PolyLp" );
											if (op == BF_PolyLpArea || (fScaleFactor >= 0 && iScaleMethod >= 0))
											{
										// identify PolyLoop to scale (or retrieve area of)
												if (BEMPX_GetClassID( pEval->lPrimDBID ) == iCID_PolyLp)
												{	iPolyLpObjIdx  = pEval->iPrimObjIdx;
													ePolyLpObjType = pEval->ePrimObjType;
													sScalePolyName = BEMPX_GetString( BEMPX_GetDBID( iCID_PolyLp, 0, BEM_PARAM0_NAME ),  
																									iSpecialVal, iError, iPolyLpObjIdx, ePolyLpObjType );
												}
												else if (BEMPX_GetClassID( pEval->lLocDBID ) == iCID_PolyLp)
												{	iPolyLpObjIdx  = pEval->iLocObjIdx;
													ePolyLpObjType = pEval->eLocObjType;
													sScalePolyName = BEMPX_GetString( BEMPX_GetDBID( iCID_PolyLp, 0, BEM_PARAM0_NAME ),  
																									iSpecialVal, iError, iPolyLpObjIdx, ePolyLpObjType );
												}
												else
												{	// get local object, loop over children and if there is only ONE that is of type PolyLp, then use that one
													int iNumPolyLpChildren = (int) BEMPX_GetNumChildren( pEval->lLocDBID, pEval->iLocObjIdx, pEval->eLocObjType, iCID_PolyLp );
													if (iNumPolyLpChildren == 1)
													{	BEM_ObjType eChldPolyLpObjType = BEMO_User;
														int iChldPolyLpObjIdx = BEMPX_GetChildObjectIndex( BEMPX_GetClassID( pEval->lLocDBID ), iCID_PolyLp, iError,
																													eChldPolyLpObjType, 1 /*i1ChildIdx*/, pEval->iLocObjIdx, pEval->eLocObjType );
														if (iChldPolyLpObjIdx >= 0)
														{	iPolyLpObjIdx  = iChldPolyLpObjIdx;
															ePolyLpObjType = eChldPolyLpObjType;
															sScalePolyName = BEMPX_GetString( BEMPX_GetDBID( pEval->lLocDBID, 0, BEM_PARAM0_NAME ),  
																											iSpecialVal, iError, pEval->iLocObjIdx, pEval->eLocObjType );
														}
													}
												}
												if (iPolyLpObjIdx < 0)
													ExpSetErr( error, EXP_RuleProc, "Unable to identify PolyLoop to scale via ScalePolyLoop()" );
											}

											vector<double> faX, faY, faZ;
											vector<int> iaCartPtObjIdxs;
											double fCentroid[3] = {0,0,0};
											double fOrigPolyArea = 0, fPolyAreaRatio = 1;
											int iCID_CartesianPt = ruleSet.getGeomIDs()->m_iOID_CartesianPt;			// SAC 10/1/13 - was: BEMPX_GetDBComponentID( "CartesianPt" );
											long lDBID_Coord     = ruleSet.getGeomIDs()->m_lDBID_CartesianPt_Coord;	// SAC 10/1/13 - was: BEMPX_GetDatabaseID( "Coord", iCID_CartesianPt );
											int iPt, iNumPolyCoords = 0, iErrantPolyCoordRetrieval = 0;
											if (op == BF_PolyLpArea || (fScaleFactor >= 0 && iScaleMethod >= 0 && iPolyLpObjIdx >= 0))
											{
										// load initial polygon
												int iNumPolyLpCoords = (int) BEMPX_GetNumChildren( iCID_PolyLp, iPolyLpObjIdx, ePolyLpObjType, iCID_CartesianPt );
												double fCoord[3];
												for (iPt=0; (iErrantPolyCoordRetrieval == 0 && iPt < iNumPolyLpCoords); iPt++)
												{	BEM_ObjType eCartPtObjType = BEMO_User;
													int iCartPtObjIdx = BEMPX_GetChildObjectIndex( iCID_PolyLp, iCID_CartesianPt, iError, eCartPtObjType, 
																													iPt+1 /*i1ChildIdx*/, iPolyLpObjIdx, ePolyLpObjType );
													if (iCartPtObjIdx >= 0 && BEMPX_GetFloatArray( lDBID_Coord, fCoord, 3, 0, -1, iCartPtObjIdx, (int) eCartPtObjType ) == 3)
													{	iaCartPtObjIdxs.push_back( iCartPtObjIdx );
														faX.push_back( fCoord[0] );
														faY.push_back( fCoord[1] );
														faZ.push_back( fCoord[2] );
														fCentroid[0] += fCoord[0];
														fCentroid[1] += fCoord[1];
														fCentroid[2] += fCoord[2];
													}
													else
														iErrantPolyCoordRetrieval = iPt + 1;
												}
												if (iErrantPolyCoordRetrieval > 0)
												{  sErrMsg = QString( "Error retrieving PolyLoop coordinate #%1 (ScalePolyLoop(), PolyLoop index %2)" ).arg( QString::number( iErrantPolyCoordRetrieval ), QString::number( iPolyLpObjIdx ) );
												   ExpSetErr( error, EXP_RuleProc, sErrMsg );
												}
												else if (faX.size() < 3)
												{  sErrMsg = QString( "Invalid number of PolyLoop coordinates (%1, at least 3 required) (ScalePolyLoop(), PolyLoop index %2)" ).arg( QString::number( (int) faX.size() ), QString::number( iPolyLpObjIdx ) );
												   ExpSetErr( error, EXP_RuleProc, sErrMsg );
												}
												else
												{	iNumPolyCoords = (int) faX.size();							assert( iNumPolyCoords == iNumPolyLpCoords );
													fOrigPolyArea = PolygonArea( faX, faY, faZ );			assert( fOrigPolyArea > 0 );
													if ((int) faX.size() > iNumPolyCoords)  // remove trailing vertex added by PolygonArea() function (if present)
													{	assert( (int) faX.size() == (iNumPolyCoords+1) );
														faX.pop_back();
														faY.pop_back();
														faZ.pop_back();
													}
													fCentroid[0] /= iNumPolyCoords;
													fCentroid[1] /= iNumPolyCoords;
													fCentroid[2] /= iNumPolyCoords;
													if (op == BF_PolyLpArea)
	                           				fPolyArea = fOrigPolyArea;   // DONE
												}
											}

											if (op == BF_ScalePolyLp && fScaleFactor >= 0 && iScaleMethod >= 0 && iNumPolyCoords > 2)
											{
										// Window PolyLoop Scaling
												if (iScaleMethod == 0)
												{	double fMaxZ = -9999;
													for (iPt=0; iPt < iNumPolyCoords; iPt++)
													{	if (faZ[iPt] > fMaxZ)
															fMaxZ = faZ[iPt];
													}
													// scale each Z coordinate in polygon
													for (iPt=0; iPt < iNumPolyCoords; iPt++)
													{	if (faZ[iPt] != fMaxZ)
															faZ[iPt] = fMaxZ - (fScaleFactor * (fMaxZ - faZ[iPt]));
													}
                           				fPolyArea = PolygonArea( faX, faY, faZ );
													fPolyAreaRatio = (fOrigPolyArea <= 0 ? 0 : (fPolyArea / fOrigPolyArea));
													assert( WithinMargin( fPolyAreaRatio, fScaleFactor, 0.01 ) );
												}
												else if (iScaleMethod == 1)
												{	//iNumPolyCoords = (int) faX.size();
                                       if (iNumPolyCoords == 4)
													{
							// CHECK FOR PAIRS OF SIDE LENGTHS BEING EQUAL ???
														if (TRUE)
														{	double fCntrVctrFctr = sqrt(fScaleFactor);
															for (iPt=0; iPt < iNumPolyCoords; iPt++)
															{	faX[iPt] = fCentroid[0] + ((faX[iPt] - fCentroid[0]) * fCntrVctrFctr);
																faY[iPt] = fCentroid[1] + ((faY[iPt] - fCentroid[1]) * fCntrVctrFctr);
																faZ[iPt] = fCentroid[2] + ((faZ[iPt] - fCentroid[2]) * fCntrVctrFctr);
															}
                           						fPolyArea = PolygonArea( faX, faY, faZ );
															fPolyAreaRatio = (fOrigPolyArea <= 0 ? 0 : (fPolyArea / fOrigPolyArea));
															assert( WithinMargin( fPolyAreaRatio, fScaleFactor, 0.01 ) );
														}
													}
													if (fPolyArea <= 0)
													{	sErrMsg = QString( "Scaling method %1 not compatible w/ non-rectangular PolyLoops (ScalePolyLoop(), PolyLoop index %2)" ).arg( QString::number( iScaleMethod ), QString::number( iPolyLpObjIdx ) );
													   ExpSetErr( error, EXP_RuleProc, sErrMsg );
													}
												}
												else
												{	sErrMsg = QString( "PolyLoop scaling method %1 not yet implemented (ScalePolyLoop(), PolyLoop index %2)" ).arg( QString::number( iScaleMethod ), QString::number( iPolyLpObjIdx ) );
												   ExpSetErr( error, EXP_RuleProc, sErrMsg );
												}
											}

                           		if (op == BF_ScalePolyLp && fPolyArea > 0)
											{	int iErrantPolyCoordSetting = 0, iVal, iSetRetVal;
										// post final PolyLoop data BACK TO  BEMBase
												for (iPt=0; (iErrantPolyCoordSetting == 0 && iPt < iNumPolyCoords); iPt++)
												{	for (iVal=0; (iErrantPolyCoordSetting == 0 && iVal < 3); iVal++)
													{	double fVal = (iVal==0 ? faX[iPt] : (iVal==1 ? faY[iPt] : faZ[iPt]));
														iSetRetVal = BEMPX_SetBEMData( lDBID_Coord + iVal, BEMP_Flt, (void*) &fVal, BEMO_User, iaCartPtObjIdxs[iPt], BEMS_UserDefined /*pEval->eLocStatus*/,
                                  														BEMO_User /*pEval->eLocObjType*/, TRUE /*bPerformSetBEMDataResets*/, -1 /*iBEMProcIdx*/ );
																	  							//	BOOL bImportUniqueRuleLibObjects=FALSE, const char* pszImportRuleLibParentName=NULL,
																	  							//	char* pszErrMsg=NULL, int iErrMsgLen=0 );
														if (iSetRetVal < 0)
														{	iErrantPolyCoordSetting = iPt+1;
															sErrMsg = QString( "Error setting PolyLoop coordinate to BEMBase via ScalePolyLoop() (PolyLoop index %1, coord %2, value %3)" ).arg( QString::number( iPolyLpObjIdx ), QString::number( iPt+1 ), QString::number( iVal+1 ) );
															ExpSetErr( error, EXP_RuleProc, sErrMsg );
														}
													}
												}
												// SAC 10/29/13 - added reset of PolyLp:Area property so that it is consistent w/ the revised area (iff return value of this rule not setting PolyLp:Area)
								// note: resetting PolyLp:Area does NOT cause other PolyLp properties to get reset, such as XYLen, ZBottom, ZTop, ZHgt...
												if (pEval->lLocDBID != ruleSet.getGeomIDs()->m_lDBID_PolyLp_Area)
												{	iSetRetVal = BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_Area, BEMP_Flt, (void*) &fPolyArea, BEMO_User, iPolyLpObjIdx, BEMS_RuleDefined /*pEval->eLocStatus*/,
                                  													BEMO_User /*pEval->eLocObjType*/, TRUE /*bPerformSetBEMDataResets*/, -1 /*iBEMProcIdx*/ );
													assert( iSetRetVal >= 0 );
												}
											}

	if (op == BF_ScalePolyLp && pEval->bVerboseOutput)
	{	sErrMsg = QString( "      ScalePolyLoop( %1, %2 ) on '%3' --> orig area: %4 | scaled area: %5 | area ratio: %6" ).arg( QString::number( iScaleMethod ), QString::number( fScaleFactor ), sScalePolyName, QString::number( fOrigPolyArea ), QString::number( fPolyArea ), QString::number( (fOrigPolyArea > 0 ? fPolyArea / fOrigPolyArea : -1) ) );
		//BEMMessageBox( sErrMsg, NULL, 3 /*error*/ );
      BEMPX_WriteLogFile( sErrMsg );
	}

										}

										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (fPolyArea >= 0)
										{	pNode->type = EXP_Value;
											pNode->fValue = fPolyArea;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0;
										}
										ExpxStackPush( stack, pNode );
                           }  break;

		case BF_Cr8PolyLp  :		// SAC 2/18/14 - added
									{	// 	CreatePolyLpChild( Area, Azimuth, Tilt, Z, PolyType, ...
										//																	0 => other )
										//																	1 => Wall, WallHgt )
										//																	2 => Window, WallHgt, WallArea )
										//																	3 => Door, WallHgt, WallArea )
										//																	4 => Shade, Height, Shape (0-Rect,1-Oct) and Centroid X,Y,Z   - SAC 3/1/17
										//																	5 => Shade, Height, Shape (0-Rect,1-Oct) and Lower-Left X,Y   - SAC 3/4/17
										ExpNode* pNode[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
										QString sErrMsg;
										bool bNumArgsOK = (nArgs > 4 && nArgs < 11);
										if (!ruleSet.initGeomIDs( pEval, error ))
										{	// do nothing here - error already posted
										}
										else if (!bNumArgsOK)
											sErrMsg = QString( "Invalid number of CreatePolyLpChild() arguments (%1), should be 5-7." ).arg( QString::number( nArgs ) );
										int i=nArgs-1;
										for (; i>=0; i--)
										{	int idx = (bNumArgsOK ? i : 0);
											pNode[idx] = ExpxStackPop( stack );
											if (sErrMsg.isEmpty() && (pNode[idx] == NULL  ||  pNode[idx]->type != EXP_Value))
											{	if (pNode[idx] == NULL)
													sErrMsg = QString( "Invalid CreatePolyLpChild() function argument (# %1)." ).arg( QString::number( i+1 ) );
												else
													sErrMsg = QString( "Invalid CreatePolyLpChild() function argument (# %1), must be numeric." ).arg( QString::number( i+1 ) );
											}
											if (!bNumArgsOK)
											{	delete pNode[idx];
												pNode[idx] = NULL;
										}	}

										int iPolyLpObjIdx = -1, iStatus=0, iSpecialVal, iError;
										if (sErrMsg.isEmpty())
										{	if (pNode[4]->fValue == 5)  // different argument specification for Shade w/ lower-left X,Y vs. others where X,Y,Z is centroid
												iPolyLpObjIdx = BEMPX_CreatePolyLoop( pNode[0]->fValue /*Area*/, pNode[1]->fValue /*Azimuth*/, pNode[2]->fValue /*Tilt*/,
																		pNode[3]->fValue /*Z*/, (int) pNode[4]->fValue /*PolyType*/, (pNode[5] ? pNode[5]->fValue : -1) /*Arg6*/,
																		(pNode[6] ? pNode[6]->fValue : -1) /*Arg7*/, -1 /*iBEMProcIdx*/, NULL /*pdFurthestFromXYOrig*/, 
																		(pNode[7] ? pNode[7]->fValue : -1) /*dDX*/, (pNode[8] ? pNode[8]->fValue : -1) /*dDY*/ );  //, (pNode[9] ? pNode[9]->fValue : -1) /*dDZ*/ );
											else
												iPolyLpObjIdx = BEMPX_CreatePolyLoop( pNode[0]->fValue /*Area*/, pNode[1]->fValue /*Azimuth*/, pNode[2]->fValue /*Tilt*/,
																		pNode[3]->fValue /*Z*/, (int) pNode[4]->fValue /*PolyType*/, (pNode[5] ? pNode[5]->fValue : -1) /*Arg6*/,
																		(pNode[6] ? pNode[6]->fValue : -1) /*Arg7*/, -1 /*iBEMProcIdx*/, NULL /*pdFurthestFromXYOrig*/, 0 /*dDX*/,
																		0 /*dDY*/, 0 /*dDZ*/, -1 /*dChldHgt*/, -1 /*dChldX*/, -1 /*dChldY*/, (pNode[7] ? pNode[7]->fValue : -1) /*CentX*/,
																		(pNode[8] ? pNode[8]->fValue : -1) /*CentY*/, (pNode[9] ? pNode[9]->fValue : -1) /*CentZ*/ );
											if (iPolyLpObjIdx < 0)
												sErrMsg = QString( "Error encountered in CreatePolyLpChild() function - return code %1." ).arg( QString::number( iPolyLpObjIdx ) );
											else
											{
										//		QString sParentName;
										//		if (!BEMPX_SetDataString( BEMPX_GetDatabaseID( "Name", BEMPX_GetClassID( pEval->lLocDBID ) ), sParentName,
										//																		FALSE, 0, -1, pEval->iLocObjIdx ) || sParentName.isEmpty())
												QString sParentName = BEMPX_GetStringAndStatus( BEMPX_GetDBID( BEMPX_GetClassID( pEval->lLocDBID ), 0, BEM_PARAM0_NAME ), 
																													iStatus, iSpecialVal, iError, pEval->iLocObjIdx );
												if (iStatus < 1 || sParentName.isEmpty())
													sErrMsg = QString( "CreatePolyLpChild() error encountered retrieving name of parent object (class: %1, object index: %2)." ).arg(
																			QString::number( BEMPX_GetClassID( pEval->lLocDBID ) ), QString::number( pEval->iLocObjIdx ) );
												else
												{	// add as new child of Local object
					   							if (BEMPX_SetBEMData( BEMPX_GetDatabaseID( "PolyLp:Parent" ), BEMP_Str,
																					(void*) sParentName.toLocal8Bit().constData(), BEMO_User, iPolyLpObjIdx ) < 0)
														sErrMsg = QString( "CreatePolyLpChild() error setting parent/child relationship (parent class: %1, index: %2, PolyLp index: %3)." ).arg(
																				QString::number( BEMPX_GetClassID( pEval->lLocDBID ) ), QString::number( pEval->iLocObjIdx ), QString::number( iPolyLpObjIdx ) );
											}	}
										}

										pNode[0] = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (!sErrMsg.isEmpty())
										{	// post error & setup return argument
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
											pNode[0]->type = EXP_Invalid;
											pNode[0]->fValue = 0;
										}
										else
										{	// setup return argument
											pNode[0]->type = EXP_Value;
											pNode[0]->fValue = (double) iPolyLpObjIdx;
										}
										ExpxStackPush( stack, pNode[0] );
									}	break;

		case BF_InitPolyLp :  // SAC 10/29/13 - InitializePolyLoop() sets a variety of stats & normal vector information and returns the area of the PolyLp
                           {  double dPolyArea = -1;
										int iPolyLpObjIdx = -2;
										ExpNode* pNode = NULL;
										QString sErrMsg;
										if (!ruleSet.initGeomIDs( pEval, error ))
										{	// do nothing here - error already posted
										}
										else
										{	int iError;
											BEM_ObjType ePolyLpObjType = BEMO_User;
											int iCID_PolyLp = ruleSet.getGeomIDs()->m_iOID_PolyLp;
											if (TRUE)
											{
										// identify PolyLoop to initialize
												if (BEMPX_GetClassID( pEval->lPrimDBID ) == iCID_PolyLp)
												{	iPolyLpObjIdx  = pEval->iPrimObjIdx;
													ePolyLpObjType = pEval->ePrimObjType;
												}
												else if (BEMPX_GetClassID( pEval->lLocDBID ) == iCID_PolyLp)
												{	iPolyLpObjIdx  = pEval->iLocObjIdx;
													ePolyLpObjType = pEval->eLocObjType;
												}
												else
												{	// get local object, loop over children and if there is only ONE that is of type PolyLp, then use that one
													int iNumPolyLpChildren = (int) BEMPX_GetNumChildren( pEval->lLocDBID, pEval->iLocObjIdx, pEval->eLocObjType, iCID_PolyLp );
													if (iNumPolyLpChildren == 1)
													{	BEM_ObjType eChldPolyLpObjType = BEMO_User;
														int iChldPolyLpObjIdx = BEMPX_GetChildObjectIndex( BEMPX_GetClassID( pEval->lLocDBID ), iCID_PolyLp, iError,
																													eChldPolyLpObjType, 1 /*i1ChildIdx*/, pEval->iLocObjIdx, pEval->eLocObjType );
														if (iChldPolyLpObjIdx >= 0)
														{	iPolyLpObjIdx  = iChldPolyLpObjIdx;
															ePolyLpObjType = eChldPolyLpObjType;
														}
													}
												}
												if (iPolyLpObjIdx < 0)
													ExpSetErr( error, EXP_RuleProc, "Unable to identify PolyLoop to initialize via InitializePolyLoop()" );
										}	}
										if (iPolyLpObjIdx >= 0)
											dPolyArea = InitPolyLoop( iPolyLpObjIdx, pEval, error );

										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										if (dPolyArea >= 0)
										{	pNode->type = EXP_Value;
											pNode->fValue = dPolyArea;
										}
										else
										{	pNode->type = EXP_Invalid;
											pNode->fValue = 0;
										}
										ExpxStackPush( stack, pNode );
                           }  break;

      case BF_CompArray  :  // SAC 3/7/11 - ComponentArray( <OperationID#>, <Value#>, LocalDBID, Comp:ParamDBID ) - returns array of component references to LocalDBID based on Comp:ParamDBID meeting OperationID & Value condition
                            ComponentArray( op, nArgs, stack, pEval, error );
                            break;

      case BF_CountNoRefs : // "CountNoRefs"
                            BEMProc_CountNoRefs( op, nArgs, stack, pEval, error );
                            break;

      case BF_BitMatchCmp : // SAC 4/2/02 - first arg should be the Property name of a local number, subsequent are Component:Property strings
      case BF_BitMatchCnt : // SAC 4/2/02 - first arg should be the Property name of a local number, subsequent are Component:Property strings
                            BEMProc_BitwiseMatches( op, nArgs, stack, pEval, error );
                            break;

      case BF_SumToArray :  // SAC 7/21/06 - first argument of SumIntoArrayElement() should be Param or Comp:Param string, second is 1-based array index and third is value to sum into that array element
                            BEMProc_SumIntoArrayElement( op, nArgs, stack, pEval, error );
                            break;

      case BF_StrUnique :   // SAC 8/25/03 - Implemented EnsureStringUniqueness(): first arg is Comp:Param string and second (optional arg) is maximum string length
                            BEMProc_EnsureStringUniqueness( op, nArgs, stack, pEval, error );
                            break;

      case BF_GlobalRef   :  // "GlobalRef",    - SAC 1/22/07
      case BF_LocalRef   :  // "LocalRef",    
      case BF_ParentRef  :  // "ParentRef",   
      case BF_Parent2Ref :  // "Parent2Ref",   
      case BF_Parent3Ref :  // "Parent3Ref",   
      case BF_ChildRef   :  // "ChildRef",    
      case BF_LCompAssign :  // "LocalComponentAssigned"
      case BF_PCompAssign :  // "ParentComponentAssigned"
      case BF_LIsDefault : // "LocalIsDefault"
      case BF_PIsDefault : // "ParentIsDefault"
      case BF_LocStatus : // "LocalStatus"
      case BF_ParStatus : // "ParentStatus"
      case BF_GlobStatus  :   // "GlobalStatus" - SAC 8/24/01  - SAC 2/7/14 - moved down here to all for GlobalRefStatus
      case BF_LocMxStrLen : // "LocalMaxStringLength"  - SAC 11/20/09
      case BF_ParStrAElem : // "ParentStringArrayElement"  - SAC 11/20/09
		case BF_GlobalVal  :		// SAC 2/13/14
		case BF_LocalVal   :		// SAC 2/13/14
		case BF_ParentVal  :		// SAC 2/13/14
		case BF_Parent2Val :		// SAC 2/13/14
		case BF_Parent3Val :		// SAC 2/13/14
		case BF_Par2SymStr    :  // SAC 4/10/14
		case BF_Par3SymStr    :  // SAC 4/10/14
		case BF_LocRefSymStr  :  // SAC 4/10/14
		case BF_ParSymStr     :  // SAC 4/10/14
		case BF_ParRefSymStr  :  // SAC 4/10/14
		case BF_Par2RefSymStr :  // SAC 4/10/14
		case BF_Par3RefSymStr :  // SAC 4/10/14
                            if (nArgs < 1)
										 ExpSetErr( error, EXP_RuleProc, QString( "Missing %1() function argument(s)" ).arg( ExpGetFuncTableNameByOpType( op ) ) );  // SAC 5/3/17
                            else
                               LocalParentChildRef( op, nArgs, stack, pEval, error );
                            break;

      case BF_ChildCnt   : {// "ChildCount"
                            ExpNode* pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid ChildCount() argument" );
                            else
                               pNode->fValue = BEMPX_GetNumChildren( pEval->lPrimDBID, pEval->iPrimObjIdx, pEval->ePrimObjType,
                                                                        (int) pNode->fValue );
                            ExpxStackPush( stack, pNode );
                            break; }

      case BF_CompCnt    : {// "ComponentCount",  SAC  4/1/02 - first and only argument is a component type
                            ExpNode* pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid ComponentCount() argument" );
                            else
                               pNode->fValue = BEMPX_GetNumObjects( (int) pNode->fValue );
                            ExpxStackPush( stack, pNode );
                            break; }

      case BF_CurTime    :  // "CurrentTime",       
      case BF_CurYear    : {// "CurrentYear",       
                            ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                            pNode->type = EXP_Value;
                      //      CTime time = CTime::GetCurrentTime();
                      //      pNode->fValue = (double) ( op == BF_CurTime ? time.GetTime() :
                      //                                                         time.GetYear() );
                            QDateTime time = QDateTime::currentDateTime();
                            pNode->fValue = (double) ( op == BF_CurTime ? time.toTime_t() :
                                                                               time.date().year() );
                            ExpxStackPush( stack, pNode );
                            break; }

      case BF_Date       : {// "Date",       
                            int iDay = -1;
                            int iMonth = -1;
                            int iYear = -1;
                            // Get the last argument - day
                            ExpNode* pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid Date() 3rd argument" );
                            else
                               iDay = (int) pNode->fValue;
                            // delete last argument node
                            ExpxNodeDelete( pNode );
                               
                            // Get the second argument - month
                            pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid Date() 2nd argument" );
                            else
                               iMonth = (int) pNode->fValue;
                            // delete second argument node
                            ExpxNodeDelete( pNode );
                               
                            // Get the first argument - year
                            pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid Date() 1st argument" );
                            else if (pNode->fValue < 1970 || pNode->fValue > 2037)
                               ExpSetErr( error, EXP_RuleProc, "Invalid Date() year value" );
                            else
                               iYear = (int) pNode->fValue;
                            // don't delete this node since it is the one we will set and push back onto the stack

                            if (iDay > 0 && iMonth > 0 && iYear > 0)
                            {
                         //      CTime time( iYear, iMonth, iDay, 0, 0, 0 );
                         //      pNode->fValue = (double) time.GetTime();
                               QDate date( iYear, iMonth, iDay );
                               QDateTime time( date );
                               pNode->fValue = (double) time.toTime_t();
                            }

                            // Push second argument node back onto the stack to serve as return value
                            ExpxStackPush( stack, pNode );
                            break; }

      case BF_FltToStr :  { // "FltToStr", 1 float & 0-4 integer arguments
                            if (nArgs < 1 || nArgs > 5)
                               ExpSetErr( error, EXP_RuleProc, "Invalid number of FltToStr() arguments" );
                            else
                            {
                               double fValue = 0;
                               int iDecPrec = 0;
                               BOOL bCommas = TRUE;
                               int iZeroFillLeftToLength = 0;
										 BOOL bTrimTrailingDecZeroes = FALSE;

                               ExpNode* pNode = ExpxStackPop( stack );
                               if (nArgs > 4)
                               {  // Parse the (optional) 5th argument - bTrimTrailingDecZeroes
                                  if (pNode->type != EXP_Value)
                                     ExpSetErr( error, EXP_RuleProc, "Invalid FltToStr() 5th argument" );
                                  else
                                     bTrimTrailingDecZeroes = (pNode->fValue != 0);
                                  // delete argument node
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
                               }
                               if (nArgs > 3)
                               {  // Parse the (optional) 4th argument - iZeroFillLeftToLength
                                  if (pNode->type != EXP_Value)
                                     ExpSetErr( error, EXP_RuleProc, "Invalid FltToStr() 4th argument" );
                                  else
                                     iZeroFillLeftToLength = (int) pNode->fValue;
                                  // delete argument node
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
                               }
                               if (nArgs > 2)
                               {  // Parse the (optional) 3rd argument - bCommas
                                  if (pNode->type != EXP_Value)
                                     ExpSetErr( error, EXP_RuleProc, "Invalid FltToStr() 3rd argument" );
                                  else
                                     bCommas = (pNode->fValue != 0);
                                  // delete argument node
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
                               }
                               if (nArgs > 1)
                               {  // Parse the (optional) 2nd argument - decimal precision
                                  if (pNode->type != EXP_Value)
                                     ExpSetErr( error, EXP_RuleProc, "Invalid FltToStr() 2nd argument" );
                                  else
                                     iDecPrec = (int) pNode->fValue;
                                  // delete argument node
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
                               }
                                  
                               // Parse the first argument - numeric value to translate to string
                               if (pNode->type != EXP_Value)
                                  ExpSetErr( error, EXP_RuleProc, "Invalid FltToStr() 1st argument" );
                               else
                                  fValue = pNode->fValue;
                               // don't delete this node since it is the one we will set and push back onto the stack

										 // SAC 2/8/05 - Added code to handle decimal precision values 101-106 as "significant digits" indicators
                               if (iDecPrec >= 101 && iDecPrec <= 106)
                               {                                                             // iDecPrec:    1            2              4               6
                                  iDecPrec -= 100;                                           //          ---------------------------------------------------------
                                  if      (fValue < -10000  )  iDecPrec = max( 0, (iDecPrec - 5) );   // -50,000      -55,000        -55,550         -55,555.5
                                  else if (fValue < -1000   )  iDecPrec = max( 0, (iDecPrec - 4) );   //  -5,000       -5,500         -5,555          -5,555.55
                                  else if (fValue < -100    )  iDecPrec = max( 0, (iDecPrec - 3) );   //    -500         -550           -555.5          -555.555
                                  else if (fValue < -10     )  iDecPrec = max( 0, (iDecPrec - 2) );   //     -50          -55            -55.55          -55.5555
                                  else if (fValue < -1      )  iDecPrec =         (iDecPrec - 1)  ;   //      -5           -5.5           -5.555          -5.55555
                                  else if (fValue < -0.1    )  iDecPrec =          iDecPrec       ;   //      -0.5         -0.55          -0.5555         -0.555555
                                  else if (fValue < -0.01   )  iDecPrec =         (iDecPrec + 1)  ;   //      -0.05        -0.055         -0.05555        -0.0555555
                                  else if (fValue < -0.001  )  iDecPrec =         (iDecPrec + 2)  ;   //      -0.005       -0.0055        -0.005555       -0.00555555
                                  else if (fValue < -0.0001 )  iDecPrec =         (iDecPrec + 3)  ;   //      -0.0005      -0.00055       -0.0005555      -0.000555555
                                  else if (fValue < -0.00001)  iDecPrec =         (iDecPrec + 4)  ;   //      -0.00005     -0.000055      -0.00005555     -0.0000555555
                                  else if (fValue <  0.00001)  iDecPrec =          iDecPrec       ;   //      ±0.0         ±0.00          ±0.0000         ±0.000000
                                  else if (fValue <  0.0001 )  iDecPrec =         (iDecPrec + 4)  ;   //       0.00005      0.000055       0.00005555      0.0000555555
                                  else if (fValue <  0.001  )  iDecPrec =         (iDecPrec + 3)  ;   //       0.0005       0.00055        0.0005555       0.000555555
                                  else if (fValue <  0.01   )  iDecPrec =         (iDecPrec + 2)  ;   //       0.005        0.0055         0.005555        0.00555555
                                  else if (fValue <  0.1    )  iDecPrec =         (iDecPrec + 1)  ;   //       0.05         0.055          0.05555         0.0555555 
                                  else if (fValue <  1      )  iDecPrec =          iDecPrec       ;   //       0.5          0.55           0.5555          0.555555  
                                  else if (fValue <  10     )  iDecPrec =         (iDecPrec - 1)  ;   //       5            5.5            5.555           5.55555   
                                  else if (fValue <  100    )  iDecPrec = max( 0, (iDecPrec - 2) );   //      50           55             55.55           55.5555    
                                  else if (fValue <  1000   )  iDecPrec = max( 0, (iDecPrec - 3) );   //     500          550            555.5           555.555     
                                  else if (fValue <  10000  )  iDecPrec = max( 0, (iDecPrec - 4) );   //   5,000        5,500          5,555           5,555.55       
                                  else                         iDecPrec = max( 0, (iDecPrec - 5) );   //  50,000       55,000         55,550          55,555.5       
                                  assert( iDecPrec >= 0 && iDecPrec < 10 );
                               }

                               QString sNum = BEMPX_FloatToString( fValue, iDecPrec, bCommas, iZeroFillLeftToLength, bTrimTrailingDecZeroes );

                               pNode->type = EXP_String;
                               pNode->pValue = malloc( sNum.length() + 1 );
                               strcpy( (char*) pNode->pValue, (const char*) sNum.toLocal8Bit().constData() );

                               // Push second argument node back onto the stack to serve as return value
                               ExpxStackPush( stack, pNode );
                            }
                            break; }

      case BF_StrToFlt :  { // "StrToFlt", 1 string argument
      								double dVal = 0.0;
										ExpNode* pNode = ExpxStackPop( stack );
										if (pNode->type != EXP_String)
										{	ExpSetErr( error, EXP_RuleProc, "Invalid StrToFlt() argument type (must be string)" );
											pNode->type = EXP_Invalid;
										}
										else
										{	if (strlen( (const char*) pNode->pValue ) > 0)
											{	dVal = BEMPX_StringToFloat( (const char*) pNode->pValue );
												free( pNode->pValue );
											}
											pNode->type = EXP_Value;
										}
										pNode->fValue = dVal;
										ExpxStackPush( stack, pNode );
										break; }

      case BF_SplitPath : {   // SAC 11/5/04 - 1 string & 1 integer arguments
                              // integer argument determines return value:  1 => drive letter (left of ':'), 2 => path, 3 => filename, 4 => extension (no leading dot)

                              // Get the last argument - return value key
                              int iRetKey=0;
                              ExpNode* pNode = ExpxStackPop( stack );
                              if (pNode->type != EXP_Value)
                                 ExpSetErr( error, EXP_RuleProc, "Invalid SplitPath() 2nd argument type (must be integer)" );
                              else if (pNode->fValue < 1 || pNode->fValue > 4)
                                 ExpSetErr( error, EXP_RuleProc, "Invalid SplitPath() 2nd argument value (must be in range 1-4)" );
                              else
                                  iRetKey = (int) pNode->fValue;
                              // delete second argument node
                              ExpxNodeDelete( pNode );
                                  
                              // Get the first argument - full path
                              const char* pszPath = NULL;
                              pNode = ExpxStackPop( stack );
                              if (pNode->type != EXP_String)
                                 ExpSetErr( error, EXP_RuleProc, "Invalid SplitPath() 1st argument type (must be character string)" );
                              else
                                 pszPath = (const char*) pNode->pValue;
                              // don't delete this node since it is the one we will set and push back onto the stack

                              pNode->type = EXP_Invalid;
                              if (pszPath && strlen( pszPath ) > 0)
                              {
                                 char drive[_MAX_DRIVE];
                                 char dir[  _MAX_DIR  ];
                                 char fname[_MAX_FNAME];
                                 char ext[  _MAX_EXT  ];
                                 char* pRetStr = NULL;
                                 _splitpath( pszPath, drive, dir, fname, ext );
                                 switch (iRetKey)
                                 {
                                    case 1 : if (strlen( drive ) > 0)
                                                pRetStr = drive;      break;
                                    case 2 : if (strlen( dir ) > 0)
                                                pRetStr = dir;        break;
                                    case 3 : if (strlen( fname ) > 0)
                                                pRetStr = fname;      break;
                                    case 4 : if (strlen( ext ) > 1)   // SAC 11/9/04 - mods to skip past leading '.'
                                                pRetStr = &ext[1];    break;
                                 }
                                 if (pRetStr && strlen( pRetStr ) > 0)
                                 {
                                    free( pNode->pValue );
                                    pNode->pValue = malloc( strlen( pRetStr ) + 1 );
                                    strcpy( (char*) pNode->pValue, (const char*) pRetStr );
                                    pNode->type = EXP_String;
                                 }
                              }
                              // setup return node for invalid/errant result
                              if (pNode->type == EXP_Invalid)
                              {
                                 free( pNode->pValue );
                                 switch (iRetKey)
                                 {
                                    case  1 : pNode->pValue = malloc( 11 );   strcpy( (char*) pNode->pValue, "(no drive)"     );   break;
                                    case  2 : pNode->pValue = malloc( 10 );   strcpy( (char*) pNode->pValue, "(no path)"      );   break;
                                    case  3 : pNode->pValue = malloc( 14 );   strcpy( (char*) pNode->pValue, "(no filename)"  );   break;
                                    case  4 : pNode->pValue = malloc( 15 );   strcpy( (char*) pNode->pValue, "(no extension)" );   break;
                                    default : pNode->pValue = malloc(  8 );   strcpy( (char*) pNode->pValue, "(error)"        );   break;
                                 }
                                 pNode->type = EXP_String;
                              }
                              // Push argument node back onto the stack to serve as return value
                              ExpxStackPush( stack, pNode );
                              break; }

      case BF_CheckSym   : {// "EnsureSymbolExists",       
                            ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                            pNode->type = EXP_Value;
                            pNode->fValue = (double) BEMPX_GetDefaultSymbolIfInvalid( pEval->lPrimDBID, pEval->iPrimObjIdx, pEval->ePrimObjType );
                            ExpxStackPush( stack, pNode );
                            break; }

      case BF_EvalRules  : {// "EvalRulelist",       
                            // SAC 5/26/00 - switched from 1 fixed to variable (1 or 2) args
                            if (nArgs < 1 || nArgs > 2)
                               ExpSetErr( error, EXP_RuleProc, "Invalid number of EvalRulelist() arguments" );
                            else
                            {
                               ExpNode* pNode = ExpxStackPop( stack );
                               // SAC 5/26/00 - Added EvalOption argument
                               int iEvalOption = 0;
                               if (nArgs == 2)
                               {
                                  if (pNode->type != EXP_Value || pNode->fValue < 0 || pNode->fValue > 2)   // SAC 1/22/06
                                     ExpSetErr( error, EXP_RuleProc, "Invalid EvalRulelist() EvalOption argument" );
                                  else
                                     iEvalOption = (int) pNode->fValue;

                                  // delete last argument node & pop next one
                                  ExpxNodeDelete( pNode );
                                  pNode = ExpxStackPop( stack );
                               }
                               if (pNode->type != EXP_String)
                                  ExpSetErr( error, EXP_RuleProc, "Invalid EvalRulelist() argument" );
                               else // post rulelist name to the eval struct
                               {
                                  pEval->sRulelistToEvaluate = (char*) pNode->pValue;
                                  assert( pEval->maRulelistEvalObjIdxs.size() < 1 );
                                  if (iEvalOption == 1)
                                     pEval->maRulelistEvalObjIdxs.push_back( pEval->iPrimObjIdx );
											 // SAC 1/20/06 - added new eval option = 2 => evaluate rulelist on LOCAL (as opposed to primary) BEMProc component
                                  else if (iEvalOption == 2)
                                  {
                                     pEval->iRulelistEvalClass   = BEMPX_GetClassID( pEval->lLocDBID );  // SAC 1/23/06 - added code to ensure RulelistEvalClass set to proper value
                                     pEval->eRulelistEvalObjType = pEval->eLocObjType;
                                     pEval->maRulelistEvalObjIdxs.push_back( pEval->iLocObjIdx );
                                  }
                               }
                               ExpxStackPush( stack, pNode );
                            }
                            break; }

      case BF_Cr8Child   :  // "CreateChildren",  SAC 5/26/00 - switched from 4 fixed to variable (4 or 5) arguments
      case BF_DelChild   :  // "DeleteChildren",  SAC 5/26/00 - switched from 2 fixed to variable (2 or 3) arguments
      case BF_Cr8Comp    :  // "CreateComp",      SAC 5/26/00 - switched from 3 fixed to variable (3 or 4) arguments - SAC 11/19/14 -> up to 5 args
      case BF_DelComp    :  // "DeleteComp",      SAC 5/26/00 - switched from 1 fixed to variable (1 or 2) arguments
      case BF_DelAllComps:  // "DeleteAllComps",  SAC 5/26/00 - switched from 2 fixed to variable (2 or 3) arguments
                           {// first ensure that the left side of this rule is compatible with the result of this function 
                            if (CreateDeleteFuncLeftSideOK( op, nArgs, pEval, error ))
                            {
                              if (op == BF_Cr8Child || op == BF_Cr8Comp)
                                 CreateChildrenOrComp( op, nArgs, stack, pEval, error );
                              else  // Delete*()
                                 DeleteChildrenCompOrAll( op, nArgs, stack, pEval, error );
                            }
                            break; }

      case BF_AsgnCr8Comp : // SAC 3/11/14 - AssignOrCreateComp() - first argument comp type, 2nd is comp name, following args are pairs of created comp property name (in quotes) and values/strings/enumerations for each property */
                           {// rather complicated proicessing, so do it all in subordinate routine
                          		AssignOrCreateComp( op, nArgs, stack, pEval, error );
                          		break; }

      case BF_CompExists : { // "CompExists",     SAC 7/6/01 - added
                           // Get the last argument - component name
                           QString sCompName;
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String)
                              ExpSetErr( error, EXP_RuleProc, "Invalid CompExists() 2nd argument type" );
                           else
                              sCompName = (const char*) pNode->pValue;
                           // delete second argument node
                           ExpxNodeDelete( pNode );

                           // Get the first argument - component type
                           int i1CompClass = 0;
                           pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_Value)
                              ExpSetErr( error, EXP_RuleProc, "Invalid CompExists() 1st argument type" );
                           else
                              i1CompClass = (int) pNode->fValue;
                           // don't delete this node since it is the one we will set and push back onto the stack

                           int iError;
                           pNode->fValue = ( ( i1CompClass > 0 && !sCompName.isEmpty() &&
                                                    BEMPX_GetObjectByName( i1CompClass, iError, sCompName.toLocal8Bit().constData() ) != NULL ) ? 1 : 0 );

                           // Push argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_CompName : { // "CompName",  SAC 2/3/02 - added to return the name of a component
                           // Get the last argument - component index
                           int i0CompIdx = 0;
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_Value)
                              ExpSetErr( error, EXP_RuleProc, "Invalid CompName() 2nd argument type" );
                           else if (pNode->fValue < 1)
                              ExpSetErr( error, EXP_RuleProc, "Invalid CompName() 2nd argument value too low" );
                           else
                              i0CompIdx = (int) pNode->fValue - 1;
                           // delete second argument node
                           ExpxNodeDelete( pNode );

                           // Get the first argument - component type
                           int i1CompClass = 0;
                           pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_Value)
                              ExpSetErr( error, EXP_RuleProc, "Invalid CompName() 1st argument type" );
                           else
                              i1CompClass = (int) pNode->fValue;
                           // don't delete this node since it is the one we will set and push back onto the stack

                           pNode->type = EXP_String;
                           int iError;
                           BEMObject* pObj = BEMPX_GetObjectByClass( i1CompClass, iError, i0CompIdx );
                           if (iError >= 0 && pObj && !pObj->getName().isEmpty())
                           {
                              pNode->pValue = malloc( pObj->getName().length() + 1 );
                              strcpy( (char*) pNode->pValue, (const char*) pObj->getName().toLocal8Bit().constData() );
                           }
                           else
                           {
                              pNode->pValue = malloc( 5 );
                              strcpy( (char*) pNode->pValue, "NONE" );
                           }

                           // Push argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_CompIdx  : { // "ComponentIndex" - SAC 2/27/01
                           int i0ObjIdx = pEval->iPrimObjIdx;
                           if (nArgs > 1)
                           {  i0ObjIdx = -1;
                           	ExpSetErr( error, EXP_RuleProc, "Invalid number of ComponentIndex() arguments (must be 0-1)" );
                           }
                           else if (nArgs == 1)  // SAC 11/14/16 - revisions to accommodate a single object reference property
                           {
	                           ExpNode* pNode = ExpxStackPop( stack );
	                           if (pNode->type != EXP_Value || pNode->fValue < BEM_COMP_MULT)
	                           {  i0ObjIdx = -1;
                           	   ExpSetErr( error, EXP_RuleProc, "Invalid ComponentIndex() argument type (expecting DBID)" );
                           	}
	                           else
	                           {	int iCIObjIdx = -1;		BEM_ObjType eCIObjTyp = BEMO_User;		int iCISpVal, iCIErr;
	                           	int iCIClsID = BEMPX_GetClassID( (long) pNode->fValue );
	                           	if (iCIClsID == BEMPX_GetClassID( pEval->lPrimDBID ))
	                           	{	iCIObjIdx = pEval->iPrimObjIdx;		eCIObjTyp = pEval->ePrimObjType;
	                           	}
	                           	else if (iCIClsID == BEMPX_GetClassID( pEval->lLocDBID ))
	                           	{	iCIObjIdx = pEval->iLocObjIdx;		eCIObjTyp = pEval->eLocObjType;
	                           	}
											BEMObject* pCIObj = BEMPX_GetObjectPtr( (long) pNode->fValue, iCISpVal, iCIErr, iCIObjIdx, eCIObjTyp );
											if (pCIObj == NULL)
		                           {  i0ObjIdx = -1;
   	                        	   ExpSetErr( error, EXP_RuleProc, "Unable to retrieve object referenced by ComponentIndex() argument" );
      	                     	}
      	                     	else
      	                     		i0ObjIdx = BEMPX_GetObjectIndex( pCIObj->getClass(), pCIObj );
	                           }
	                           // delete argument node
	                           ExpxNodeDelete( pNode );
                           }
                           ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                           pNode->type = EXP_Value;
                           pNode->fValue = (double) i0ObjIdx + 1;
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_ChildIdx : { // "ChildIndex" - SAC 2/27/01
                           // SAC 11/26/02 - Added processing of new (optional) argument
                           if (nArgs > 1)
                              ExpSetErr( error, EXP_RuleProc, "Invalid number of ChildIndex() arguments" );
                           else
                           {
                              ExpNode* pNode = NULL;
                              BOOL bOnlyCountPrimaryObjects = FALSE;
                              if (nArgs > 0)
                              {  // Parse the (optional) 1st argument - bOnlyCountPrimaryObjects
                                 pNode = ExpxStackPop( stack );
                                 if (pNode->type != EXP_Value)
                                    ExpSetErr( error, EXP_RuleProc, "Invalid ChildIndex() 1st argument" );   // SAC 6/24/04 - Corrected bogus error string
                                 else
                                    bOnlyCountPrimaryObjects = ((int) pNode->fValue != 0);
                              }

                              if (pNode == NULL)
                                 pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );

                              pNode->type = EXP_Value;
                              pNode->fValue = 0.0;
                              if (pEval->iPrimPar1Class > 0)
                              {
                                 int iError;
                                 BEMObject* pChildObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
                                 BEMObject* pParObj   = BEMPX_GetObjectByClass( pEval->iPrimPar1Class, iError, pEval->iPrimParObjIdx, pEval->ePrimParObjType );
                                 if (pChildObj && pParObj)
                                 {
                                    int iChildIdx = 0;
                              //      for (POSITION pos = pParObj->m_children.GetHeadPosition(); (pos != NULL && pNode->fValue < 1); /*iChildIdx++*/)
                              //      {
                              //         BEMObject* pObj = (BEMObject*) pParObj->m_children.GetNext( pos );
												for (int iC=0; (pNode->fValue < 1 && iC < pParObj->getChildCount()); iC++)
												{	BEMObject* pObj = pParObj->getChild( iC );			assert( pObj );

                                       if (!bOnlyCountPrimaryObjects || pObj->getClass()->get1BEMClassIdx() == pChildObj->getClass()->get1BEMClassIdx())
                                          iChildIdx++;

                                       if (pObj == pChildObj)
                                          pNode->fValue = iChildIdx;
                                    }
                                 }
                              }
                              ExpxStackPush( stack, pNode );
                           }  break; }

      case BF_StoreBEMProc : // "StoreBEMProc", 1 char string & 1 integer argument
                           {// Second argument is the 0/1 (store user inputs only) flag
                            ExpNode* pNode = ExpxStackPop( stack );
                            if (pNode->type != EXP_Value)
                               ExpSetErr( error, EXP_RuleProc, "Invalid StoreBEMProc() 2nd argument" );

                            // First argument is the file extension
                            ExpNode* pFNExtNode = ExpxStackPop( stack );
                            if (pFNExtNode->type != EXP_String)
                               ExpSetErr( error, EXP_RuleProc, "Invalid StoreBEMProc() 1st argument" );

//// SAC 7/1/99 - DEBUGGING
//QString sMsg = "Storing file: <project file>.";
//sMsg += (const char*) pFNExtNode->pValue;
//BEMMessageBox( sMsg, NULL, 3 /*error*/ );

                            // Call BEMProc function to store the current BEMProc
                            pNode->fValue = (double) BEMPX_WriteProjectFile( (const char*) pFNExtNode->pValue, //(pNode->fValue > 0), TRUE );  - SAC 8/1/12 - updated second argument
									 													(pNode->fValue > 0 ? BEMFM_INPUT : BEMFM_DETAIL) /*iFileMode*/, TRUE /*bUseLogFileName*/ );

//// SAC 7/1/99 - DEBUGGING
//BEMMessageBox( "File Storage Completed", NULL, 3 /*error*/ );

                            // Delete first (file extension character string) node
                            ExpxNodeDelete( pFNExtNode );
                            // Push second argument node back onto the stack to serve as return value
                            ExpxStackPush( stack, pNode );

                            break; }

      case BF_LocArrIdx : {// LocalArrayIndex( <DBID of local value array>, <DBID of array to return value from>, <max # values to search>, <order index of return value> )   - SAC 3/3/10
                           int iOrdIdx = 0, iMaxIdx = 0, i;
                           long lDBIDReturn = 0, lDBIDArray = 0;
									long long lMDBID=0;
									int i0Model = -1;
                           QString sErrMsg;
                           ExpNode* pNode = NULL;
                           for (i=0; i<4; i++)
                           {
                              pNode = ExpxStackPop( stack );
                              if (pNode->type != EXP_Value)
                              {  sErrMsg = QString( "Invalid LocalArrayIndex() argument #%1" ).arg( QString::number( i+1 ) );
                                 ExpSetErr( error, EXP_RuleProc, sErrMsg );
                              }
                              else
                                 switch (i)
                                 {  case 0 :  iOrdIdx     = (int)  pNode->fValue;   break;
                                    case 1 :  iMaxIdx     = (int)  pNode->fValue;   break;
                                    case 2 :		lMDBID = (long long) pNode->fValue;
																if (lMDBID > BEM_MODEL_MULT)
																{	lDBIDReturn = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
																	i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
																}
																else
																	lDBIDReturn = (long) lMDBID;
																break;
                                    case 3 :		lMDBID = (long long) pNode->fValue;
																if (lMDBID > BEM_MODEL_MULT)
																{	lDBIDArray = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
																	i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
																}
																else
																	lDBIDArray = (long) lMDBID;
																break;
                                 }
                              if (i < 3)
                                 ExpxNodeDelete( pNode );
                           }
                           if (pNode->type == EXP_String)
                           {
                              free( pNode->pValue );
                              pNode->pValue = NULL;
                           }
                           pNode->type = EXP_Invalid;
                           pNode->fValue = 0;

                           if (iOrdIdx > 0 && iOrdIdx <= iMaxIdx && lDBIDReturn > BEM_COMP_MULT && lDBIDArray > BEM_COMP_MULT)
                           {  assert( (BEMPX_GetArrayID( lDBIDReturn ) == 1 && BEMPX_GetArrayID( lDBIDArray ) == 1) );
                              assert( BEMPX_GetClassID( lDBIDReturn ) == BEMPX_GetClassID( lDBIDArray ) );
                              assert( BEMPX_GetClassID( lDBIDReturn ) == BEMPX_GetClassID( pEval->lPrimDBID ) );
                              iMaxIdx = min( iMaxIdx, BEMPX_GetNumPropertyTypeElementsFromDBID( lDBIDArray , i0Model ) );
                              iMaxIdx = min( iMaxIdx, BEMPX_GetNumPropertyTypeElementsFromDBID( lDBIDReturn, i0Model ) );
                              if (iOrdIdx <= iMaxIdx)
                              {  double fData, fMaxOrdVal = -99999;
                              	int iStatus=0, iSpecialVal, iError;
                                 std::vector<double> faVals, faRetVals;
                                 for (i=0; i<iMaxIdx; i++)
                           //      {  if (!BEMPX_SetDataFloat( lDBIDArray+i, fData, 0 /*fDefault*/, -1 /*iDispDataType*/, pEval->iPrimObjIdx, pEval->ePrimObjType, i0Model ))
                                 {	fData = BEMPX_GetFloatAndStatus( lDBIDArray+i, iStatus, iSpecialVal, iError, 
																								pEval->iPrimObjIdx, pEval->ePrimObjType, i0Model, true );
                                 	if (iStatus < 1)
                                    {  sErrMsg = QString( "Error retrieving LocalArrayIndex() Array Order value #%1" ).arg( QString::number( i+1 ) );
                                       ExpSetErr( error, EXP_RuleProc, sErrMsg );
                                    }
                                    else
                                    {
                                       faVals.push_back( fData );
                                       if (fData > fMaxOrdVal)
                                          fMaxOrdVal = fData;
                                       if (lDBIDArray == lDBIDReturn)
                                          faRetVals.push_back( fData );
                                       else
                                 //      {  if (!BEMPX_SetDataFloat( lDBIDReturn+i, fData, 0 /*fDefault*/, -1 /*iDispDataType*/, pEval->iPrimObjIdx, pEval->ePrimObjType, i0Model ))
		                                 {	fData = BEMPX_GetFloatAndStatus( lDBIDReturn+i, iStatus, iSpecialVal, iError, 
																										pEval->iPrimObjIdx, pEval->ePrimObjType, i0Model, true );
      		                           	if (iStatus < 1)
                                          {  sErrMsg = QString( "Error retrieving LocalArrayIndex() Return value #%1" ).arg( QString::number( i+1 ) );
                                             ExpSetErr( error, EXP_RuleProc, sErrMsg );
                                          }
                                          else
                                             faRetVals.push_back( fData );
                                       }
                                    }
                                 }  assert( fMaxOrdVal > -99999 );

                                 if (faVals.size() == faRetVals.size() && faVals.size() == iMaxIdx)
                                 {
                                    std::vector<int> iaIdxs;
                                    for (int iOrd=0; iOrd<iOrdIdx; iOrd++)
                                    {  double fNextHighestVal = -99999;
                                       //int   iNextHighestIdx = -1;
                                       for (i=0; i<iMaxIdx; i++)
                                          if (IntegerInArray( iaIdxs, i ) < 0)
                                          {  if (faVals[i] == fMaxOrdVal)
                                             {  if ((int) iaIdxs.size() > iOrd)
                                                   fNextHighestVal = fMaxOrdVal;  // there is at least one more value in array of this value - to be retrieved next time through
                                                else
                                                   iaIdxs.push_back( i );
                                             }
                                             else if (faVals[i] > fNextHighestVal)
                                                fNextHighestVal = faVals[i];  // this is the next highest value in the array that is not yet archived (and also not equal to the previous max val)
                                          }
                                       fMaxOrdVal = fNextHighestVal;  // this is the max value to check for next time through the above loop
                                    }
                                    assert( iaIdxs.size() == iOrdIdx );
                                    if (iaIdxs.size() == iOrdIdx)
                                    {
                                       pNode->type = EXP_Value;
                                       pNode->fValue = faRetVals[ iaIdxs[iOrdIdx-1] ];
                                    }
                                 }
                                 else
                                 {  sErrMsg = QString( "Error retrieving one or more of the expected %1 LocalArrayIndex() values" ).arg( QString::number( iMaxIdx ) );
                                    ExpSetErr( error, EXP_RuleProc, sErrMsg );
                                 }
                              }
                           }
                           ExpxStackPush( stack, pNode );
                           break;
                          }

      case BF_OpenExpFile : // SAC 9/15/15 - added OpenExportFile() - 1 fixed argument, path/filename, 2nd optional argument, FileOpen mode (typically 'wt' or 'at' write/append text), return integer file index 0-N or negative error code
							{  int iRetVal = 0;		QString sErrMsg;
								ExpNode* pNode = NULL;
								if (nArgs < 1)
								{	iRetVal = -1;
									sErrMsg = "OpenExportFile() requires at least one argument, path/filename of file to open.";
									pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
									pNode->type = EXP_Invalid;
								}
								else
								{	int i;
									QString sFOMode = "wt";   // other common is "at" (append)
									pNode = ExpxStackPop( stack );
									if (nArgs > 2)
									{	iRetVal = -2;
										sErrMsg = "OpenExportFile() allows no more than 2 arguments, path/filename of file to open and the file open mode (typically 'wt' or 'at' (write/append text)).";
										for (i=1; i<nArgs; i++)
										{	ExpNode* pDelNode = ExpxStackPop( stack );		assert( pDelNode );
											if (pDelNode)
												ExpxNodeDelete( pDelNode );
									}	}
									else
									{	if (nArgs == 2)
										{	if (pNode->type != EXP_String)
											{	iRetVal = -3;
												sErrMsg = "Invalid OpenExportFile() second argument, expecting string containing file open mode (typically 'wt' or 'at' (write/append text)).";
											}
											else
												sFOMode = (char*) pNode->pValue;
											ExpxNodeDelete( pNode );
											pNode = ExpxStackPop( stack );
										}
										if (pNode->type != EXP_String || strlen( (char*) pNode->pValue ) < 3)
										{	iRetVal = -4;
											sErrMsg = "Invalid OpenExportFile() first argument, expecting string containing path/filename to open.";
										}
										else
										{	QString sExpFN = (char*) pNode->pValue;
            		         		free( pNode->pValue );
											pNode->pValue = NULL;
											iRetVal = ruleSet.nextExportFileIndex();
											if (iRetVal < 0)
											{	iRetVal = -5;
												sErrMsg = "OpenExportFile() Error:  Maximum number of export files exceeded.";
											}
											else
											{	int iOpenRetVal = ruleSet.openExportFile( iRetVal, sExpFN.toLocal8Bit().constData(), sFOMode.toLocal8Bit().constData() );
												if (iOpenRetVal != 0)
												{	iRetVal = -6;
													sErrMsg = QString( "OpenExportFile() Error encountered opening file '%1', open mode '%2'." ).arg( sExpFN, sFOMode );
												}
								}	}	}	}
														assert( pNode );
								if (!sErrMsg.isEmpty())
									ExpSetErr( error, EXP_RuleProc, sErrMsg );
								if (pNode)
								{	pNode->type = EXP_Value;
									pNode->fValue = iRetVal;
					            ExpxStackPush( stack, pNode );
					         }
					         break;
							}

      case BF_CloseExpFile : // SAC 9/15/15 - added CloseExportFile() - single argument is index of export file to close, -1 to close ALL files, return number of files closed successfully
							{  int iRetVal = 0;
								ExpNode* pNode = ExpxStackPop( stack );
      		            if (pNode == NULL  ||  pNode->type != EXP_Value)
		                  {  iRetVal = -1;
      		               QString sErrMsg = "Invalid or missing CloseExportFile() function argument - expecting integer export file index (0-N).";
            		         ExpSetErr( error, EXP_RuleProc, sErrMsg );
            		         if (pNode->type == EXP_String)
            		         {	free( pNode->pValue );
										pNode->pValue = NULL;
            		         }
                  		}
		                  else if (pNode)
      		            {	int iFirstExpFileIdx, iLastExpFileIdx;  iFirstExpFileIdx = iLastExpFileIdx = (int) pNode->fValue;
      		            	if (iFirstExpFileIdx == -1)
      		            	{	iFirstExpFileIdx = 0;
      		            		iLastExpFileIdx  = NUM_RULE_EXPORTFILES-1;
      		            	}
									if (iFirstExpFileIdx < 0 || iLastExpFileIdx >= NUM_RULE_EXPORTFILES)
									{	iRetVal = -2;
      		               	QString sErrMsg = QString( "Invalid export file index (%1/%2) - argument of CloseExportFile()." ).arg( QString::number( iFirstExpFileIdx ), QString::number( iLastExpFileIdx ) );
										ExpSetErr( error, EXP_RuleProc, sErrMsg );
									}
									else
										iRetVal = ruleSet.closeExportFile( iFirstExpFileIdx, iLastExpFileIdx );
								}
								if (!pNode)
									pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
            		      if (pNode)
								{	pNode->type = EXP_Value;
									pNode->fValue = iRetVal;
					            ExpxStackPush( stack, pNode );
					         }
					         break;
							}

      case BF_Format      :
      case BF_PostError   :
      case BF_PostWarn    :
      case BF_PostLogMsg  : // SAC 10/30/07 - added PostMessageToLog()
      case BF_MsgBox      : // SAC 8/16/06 - added MessageBox() function
      case BF_WriteToFile : // SAC 6/6/13 - added WriteToFile() - same arguments as other message/log functions (file pointer provided in ruleset data)
      case BF_WriteExpFile : // SAC 9/15/15 - added WriteToExportFile() - same arguments as other message/log functions w/ additional first argument = export file index (0-N) (file pointer provided in ruleset data)
         {  // SAC 5/14/01 - variable args where 1st is format string followed by up to 6 string or numeric arguments to sprintf()
            // First check for valid number of arguments
            ExpNode* pNode[31];
            int iMinArgs = (op == BF_WriteExpFile ?  2 :  1 );
            int iMaxArgs = (op == BF_WriteExpFile ? 31 : 30 );
            assert( nArgs >= iMinArgs && nArgs <= iMaxArgs );	// SAC 3/23/12 - cranked up max # arguments to 30 (to enable day schedule definitions)
            if (nArgs < iMinArgs)
            {  // post error & setup return argument
               ExpSetErr( error, EXP_RuleProc, "Format() requires at least one argument." );
               pNode[0] = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
               pNode[0]->type = EXP_Invalid;
               pNode[0]->fValue = 0;
            }
            else if (nArgs > iMaxArgs)
            {  // post error, delete all but one arguments & setup return argument
               ExpSetErr( error, EXP_RuleProc, "Format() cannot have more than 30 arguments." );
               pNode[0] = ExpxStackPop( stack );
               for (int i=1; i<nArgs; i++)
               {
                  ExpxNodeDelete( pNode[0] );
                  pNode[0] = ExpxStackPop( stack );
               }
               if (pNode[0]->type == EXP_String)
               {
                  free( pNode[0]->pValue );
                  pNode[0]->pValue = NULL;
               }
               pNode[0]->type = EXP_Invalid;
               pNode[0]->fValue = 0;
            }
            else  // # arguments OK
            {
               // pop and check each function argument
               BOOL bArgsOK = TRUE;
					if (op == BF_WriteExpFile)  // SAC 9/15/15 - decrement nArgs for WriteToExportFile() - first argument handled separately
						nArgs-=1;
				   int i=nArgs-1;
               for (; i>=0; i--)
               {
                  pNode[i] = ExpxStackPop( stack );
                  if (pNode[i] == NULL  ||  ( (i == 0 && pNode[i]->type != EXP_String) ||
                                              (i >  0 && pNode[i]->type != EXP_String && pNode[i]->type != EXP_Value) ))
                  {
                     bArgsOK = FALSE;
                     QString sErrMsg = QString( "Invalid Format() function argument (# %1)." ).arg( QString::number( i+1 ) );
                     ExpSetErr( error, EXP_RuleProc, sErrMsg );
                  }
               }
               int iExpFileIdx = -1;
					if (op == BF_WriteExpFile)  // SAC 9/15/15 - process first WriteToExportFile() argument - export file index
					{  ExpNode* pXFINode = ExpxStackPop( stack );
                  if (pXFINode == NULL  ||  pXFINode->type != EXP_Value)
                  {  bArgsOK = FALSE;
                     QString sErrMsg = "Invalid WriteToExportFile() function argument #1 - must be integer export file index (0-N).";
                     ExpSetErr( error, EXP_RuleProc, sErrMsg );
                  }
                  else if (pXFINode)
                  	iExpFileIdx = (int) pXFINode->fValue;
                  if (pXFINode)
	                  ExpxNodeDelete( pXFINode );
					}

               // now assemble string from arguments
               QString sRetStr;
               bool bFmtOK = true;	// SAC 4/25/16 - added to handle unsuccessful string formatting
               bool bPreserveNewlines = (op == BF_WriteToFile || op == BF_WriteExpFile);  // SAC 3/8/17
               if (bArgsOK)
               {
                  QString sFormat = (char*) pNode[0]->pValue;
						bFmtOK = ProcessFormatStatement( sRetStr, sFormat, &pNode[1], nArgs-1, error, bPreserveNewlines );	// SAC 1/26/15 - populate formatted string via subordinate routine to enable access from other routine(s)

                  // now perform the appropriate action with the resulting string
                  if (bFmtOK && sRetStr.length() > 0 && op != BF_Format)
                  {
                     if (op == BF_PostError)  // SAC 5/21/01
                     {
                        if (pssaErrorMsgs)
                           pssaErrorMsgs->push_back( sRetStr );
                        else
                           ExpSetErr( error, EXP_RuleProc, QString( "Error:  %1" ).arg( sRetStr ) /*"Unable to post Error message."*/ );  // SAC 2/26/05 - Post error msg itself, rather than msg indicating it could not be posted
							// SAC 8/2/12 - logging message here to callback redundent, as it is passed back via callback in CRule:Eval()
							//	if (ruleSet.m_pLogMsgCallbackFunc)
							//		ruleSet.m_pLogMsgCallbackFunc( logMsgERROR, (const char*) sRetStr, NULL );
                     }
                     else if (op == BF_PostWarn)  // SAC 5/21/01
                     {
                        if (pssaWarningMsgs)
                           pssaWarningMsgs->push_back( sRetStr );
                        else
                           ExpSetErr( error, EXP_RuleWarn, QString( "Warning:  %1" ).arg( sRetStr ) /*"Unable to post Warning message."*/ );  // SAC 2/26/05 - Post warning msg itself, rather than msg indicating it could not be posted
							// SAC 8/2/12 - logging message here to callback redundent, as it is passed back via callback in CRule:Eval()
							//	if (ruleSet.m_pLogMsgCallbackFunc)
							//		ruleSet.m_pLogMsgCallbackFunc( logMsgWARNING, (const char*) sRetStr, NULL );
                     }
                     else if (op == BF_MsgBox)  // SAC 9/29/06
                        BEMMessageBox( sRetStr, NULL, 1 /*info*/ );
                     else if (op == BF_PostLogMsg)  // SAC 10/30/07
                     {  BEMPX_WriteLogFile( sRetStr );
                     	ruleSet.logMsgCallback( logMsgMESSAGE, sRetStr, NULL );
                     }
                     else
                     {	// going to write this string to a FILE - which requires minor additional processing - Res ticket 576: writing strings containing '%' bombs the program!
                     	int iFirstPctIdx = sRetStr.indexOf( '%' );
								while (iFirstPctIdx >= 0)
								{	if (iFirstPctIdx == sRetStr.length()-1)
									{	sRetStr += '%';
										iFirstPctIdx = -1;
									}
									else
									{	if (iFirstPctIdx < sRetStr.length()-1 && sRetStr[iFirstPctIdx+1] != '%')
											sRetStr = sRetStr.left( iFirstPctIdx+1 ) + QString('%') + sRetStr.right( sRetStr.length()-iFirstPctIdx-1 );
										iFirstPctIdx = sRetStr.indexOf( '%', iFirstPctIdx+2 );
								}	}

	                     if (op == BF_WriteToFile )  // SAC 6/6/13 - added WriteToFile() - file pointer provided in ruleset data
	                     {  int iWrtRetVal = ruleSet.writeToOutputFile( sRetStr );		assert( iWrtRetVal == 0 );
      	                  if (iWrtRetVal != 0)
									{	QString sErrMsg = QString( "No ruleset file open to write string to:  '%1'" ).arg( sRetStr );
										ExpSetErr( error, EXP_RuleProc, sErrMsg );
								}	}
								else if (op == BF_WriteExpFile)  // SAC 9/15/15 - added WriteToExportFile() - file pointer provided in ruleset data
								{	int iWrtRetVal = ruleSet.writeToExportFile( iExpFileIdx, sRetStr );		assert( iWrtRetVal == 0 );
									if (iWrtRetVal != 0)
									{	QString sErrMsg = QString( "Invalid export file index (%1) or file not open:  '%2'" ).arg( QString::number( iExpFileIdx ), sRetStr );
										ExpSetErr( error, EXP_RuleProc, sErrMsg );
									}
							}	}
                  }
               }

               // finally, delete all but one argument and setup return node
               for (i=1; i<nArgs; i++)
                  ExpxNodeDelete( pNode[i] );
               if (pNode[0]->type == EXP_String)
               {
                  free( pNode[0]->pValue );
                  pNode[0]->pValue = NULL;
               }

               if (!bArgsOK || !bFmtOK)
               {
                  pNode[0]->type = EXP_Invalid;
                  pNode[0]->fValue = 0;
               }
               else
               {
                  pNode[0]->type = EXP_String;
                  if (sRetStr.length() > 0)
                  {
                     pNode[0]->pValue = malloc( sRetStr.length() + 1 );
                     strcpy( (char*) pNode[0]->pValue, (const char*) sRetStr.toLocal8Bit().constData() );
                  }
                  else
                     pNode[0]->pValue = NULL;
               }
            }
            ExpxStackPush( stack, pNode[0] );
            break;
         }

      case BF_LogDuration : // SAC 10/24/13 - added
			// LogDuration( "duration message (w/ format for second echo)", <timerID=4>, <ResetTimer=1> )  - return value is number of seconds
         {  // First check for valid number of arguments
				QString sDurationMsgArg;
				int iTimerID=4, iResetTimer=1;
            ExpNode* pNode[3];											assert( nArgs <= 3 );
            if (nArgs < 1)
            {  pNode[0] = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
               pNode[0]->type = EXP_Value;
				//	sDurationMsgArg = "            LogDuration() returned:  %.3f seconds";  // default message
					sDurationMsgArg = "            LogDuration() returned:  %1 seconds";  // default message
            }
            else if (nArgs > 3)
            {  // post error, delete all but one arguments & setup return argument
               ExpSetErr( error, EXP_RuleProc, "LogDuration() cannot have more than 3 arguments." );
               pNode[0] = ExpxStackPop( stack );
               for (int i=1; i<nArgs; i++)
               {  ExpxNodeDelete( pNode[0] );
                  pNode[0] = ExpxStackPop( stack );
               }
               if (pNode[0]->type == EXP_String)
               {  free( pNode[0]->pValue );
                  pNode[0]->pValue = NULL;
               }
               pNode[0]->type = EXP_Invalid;
               pNode[0]->fValue = 0;
            }
            else  // # arguments OK
            {  // pop and check each function argument
               BOOL bArgsOK = TRUE;
				   int i=nArgs-1;
               for (; i>=0; i--)
               {  pNode[i] = ExpxStackPop( stack );
                  if (pNode[i] == NULL  ||  ( (i == 0 && pNode[i]->type != EXP_String) ||
                                              (i >  0 && pNode[i]->type != EXP_Value) ))
                  {  bArgsOK = FALSE;
                     QString sErrMsg = QString( "Invalid LogDuration() function argument (# %1)." ).arg( QString::number( i+1 ) );
                     ExpSetErr( error, EXP_RuleProc, sErrMsg );
                  }
						else
						{	switch (i)
							{	case  0 :	sDurationMsgArg = (char*) pNode[0]->pValue;
														free( pNode[0]->pValue );	// prepare node to be return value
														pNode[0]->pValue = NULL;
														pNode[0]->type = EXP_Value;
														break;
								case  1 :	iTimerID    = (int) pNode[1]->fValue;		break;
								case  2 :	iResetTimer = (int) pNode[2]->fValue;		break;
								default :	assert( FALSE );		break;
					}	}	}
				}

				if (pNode[0]->type == EXP_Value)
				{	// all OK - get duration value, format into string and log message, returning duration value
					double dDuration = ruleSet.GetDurationSinceMark( iTimerID, (iResetTimer!=0) );
					if (sDurationMsgArg.length() > 1 && dDuration > -0.5)
					{	QString sDurationMsg;
						if (sDurationMsgArg.indexOf('%') >= 0)
							sDurationMsg = QString( sDurationMsgArg ).arg( QString::number( dDuration ) );
						else
							sDurationMsg = sDurationMsgArg;
						BEMPX_WriteLogFile( sDurationMsg );
						ruleSet.logMsgCallback( logMsgMESSAGE, sDurationMsg, NULL );
					}
               pNode[0]->fValue = dDuration;
				}
            ExpxStackPush( stack, pNode[0] );
            break;
         }

      case BF_FindInStr :  // SAC 7/2/09 - FindInString( <"main string">, <"substring to find"> )
                        {  QString sMainStr, sSubStr;
                           ExpNode* pNode = ExpxStackPop( stack );
                           // translate second argument
                           if (pNode->type == EXP_String)
                              sSubStr = (char*) pNode->pValue;
                           else
                              ExpSetErr( error, EXP_RuleProc, "Second FindInString() function argument must be a string." );
                           // delete this node and pop next one
                           ExpxNodeDelete( pNode );
                           pNode = ExpxStackPop( stack );
                           // translate first argument
                           if (pNode->type == EXP_String)
                           {
                              sMainStr = (char*) pNode->pValue;
                              free( pNode->pValue );
                              pNode->pValue = NULL;
                           }
                           else
                              ExpSetErr( error, EXP_RuleProc, "First FindInString() function argument must be a string." );

                           if (!sSubStr.isEmpty() && sMainStr.length() >= sSubStr.length())
                           {  pNode->type = EXP_Value;
                              pNode->fValue = (double) sMainStr.indexOf( sSubStr );
                           }
                           else                           // SAC 8/6/09 - revised code to return valid value here of -1 => substring not found
                           {  pNode->type = EXP_Value;    // pNode->type = EXP_Invalid;
                              pNode->fValue = -1.0;  // pNode->fValue = 0.0;
                           }
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_RplcInStr :  // SAC 11/20/09 - ReplaceInString( <"substring to find">, <"replacement string"> )
                        {  QString sMainStr, sFindStr, sRplcStr;
                           BOOL bRISRetValOK = FALSE;
                           ExpNode* pNode = ExpxStackPop( stack );
                           // translate second argument
                           if (pNode->type == EXP_String)
                              sRplcStr = (char*) pNode->pValue;
                           else
                              ExpSetErr( error, EXP_RuleProc, "Second ReplaceInString() function argument must be a string." );
                           // delete this node and pop next one
                           ExpxNodeDelete( pNode );
                           pNode = ExpxStackPop( stack );
                           // translate first argument
                           if (pNode->type == EXP_String)
                           {
                              sFindStr = (char*) pNode->pValue;
                              free( pNode->pValue );
                              pNode->pValue = NULL;
                           }
                           else
                              ExpSetErr( error, EXP_RuleProc, "First ReplaceInString() function argument must be a string." );

                           if (sRplcStr.indexOf( sFindStr ) >= 0)
                           {  QString sRISErr = QString( "First ReplaceInString() argument '%1' cannot be included in second argument '%2'." ).arg( sFindStr, sRplcStr );
                              ExpSetErr( error, EXP_RuleProc, sRISErr );
                           }
                           else if (BEMPX_GetString( pEval->lLocDBID, sMainStr, TRUE, 0, -1, pEval->iLocObjIdx, pEval->eLocObjType ))
                           {
                              bRISRetValOK = TRUE;
                              int iFindStrLen = sFindStr.length();
                              int iFound = sMainStr.indexOf( sFindStr );
                              while (iFound >= 0)
                              {
                                 sMainStr = sMainStr.left( iFound ) + sRplcStr + sMainStr.right( sMainStr.length()-iFound-iFindStrLen );
                                 iFound = sMainStr.indexOf( sFindStr, iFound+1 );
                              }
                           }

                           if (bRISRetValOK)
                           {  pNode->type = EXP_String;
                              pNode->pValue = malloc( sMainStr.length() + 1 );
                              strcpy( (char*) pNode->pValue, (const char*) sMainStr.toLocal8Bit().constData() );
                           }
                           else
                           {  pNode->type = EXP_Invalid;
                              pNode->fValue = 0;
                           }
                           ExpxStackPush( stack, pNode );
                           break; }

		// SAC 4/9/02 - Added to ensure that a character string is unique across all currently defined BEMProc component names
      case BF_UnqCompName : { // UniqueComponentName():  1 character string argument
                           QString sUnqCompName;
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String)
                              ExpSetErr( error, EXP_RuleProc, "Invalid UniqueComponentName() argument type" );
                           else
                           {
                              sUnqCompName = (const char*) pNode->pValue;
                              if (sUnqCompName.isEmpty())
                                 ExpSetErr( error, EXP_RuleProc, "UniqueComponentName() argument empty" );
                              else if (BEMPX_GetComponentByNameQ( sUnqCompName ) != NULL)
                              {
                                 int iCompIdx = 1;
                                 do
                                 {
                                    sUnqCompName = QString( "%1-%2" ).arg( (const char*) pNode->pValue, QString::number( ++iCompIdx ) );
                                 } while (BEMPX_GetComponentByNameQ( sUnqCompName ) != NULL);
                              }
                              free( pNode->pValue );
                              pNode->pValue = NULL;
                           }

                           if (sUnqCompName.isEmpty())
                           {
                              pNode->type = EXP_Invalid;
                              pNode->fValue = 0;
                           }
                           else
                           {
                              pNode->type = EXP_String;
                              pNode->pValue = malloc( sUnqCompName.length() + 1 );
                              strcpy( (char*) pNode->pValue, (const char*) sUnqCompName.toLocal8Bit().constData() );
                           }
                           ExpxStackPush( stack, pNode );
                           break;  }


      case BF_ParCompType : {    // SAC 2/16/10 - added ParentComponentType() function - no arguments, simply return component type string of parent component (or "none" if no parent exists)
                           QString sParCompType = "none";
                           int iError;
                           BEMObject* pPrimObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
                           if (pPrimObj && pPrimObj->getParent() && pPrimObj->getParent()->getClass())
                              sParCompType = pPrimObj->getParent()->getClass()->getShortName();

                           ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                           pNode->type = EXP_String;
                           pNode->pValue = malloc( sParCompType.length() + 1 );
                           strcpy( (char*) pNode->pValue, (const char*) sParCompType.toLocal8Bit().constData() );
                           ExpxStackPush( stack, pNode );
                           break;  }


      case BF_CompType :	{   // SAC 8/20/12 - added ComponentType( "CompClassName" ) - argument could potentially be the result of other function(s)
									int iCTypRetVal = -1;
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String)
                              ExpSetErr( error, EXP_RuleProc, "Invalid ComponentType() argument type (expecting a character string)" );
                           else
                           {  if (pNode->pValue == NULL || strlen( (const char*) pNode->pValue ) < 1)
                                 ExpSetErr( error, EXP_RuleProc, "ComponentType() argument empty" );
                              else
                              {	iCTypRetVal = (int) BEMPX_GetDBComponentID( (const char*) pNode->pValue );
                                 free( pNode->pValue );
	                              pNode->pValue = NULL;
											if (iCTypRetVal <= 0)
	                                 ExpSetErr( error, EXP_RuleProc, "ComponentType() argument not found in component type list." );
										}
									}
									if (pNode)
									{
	                           pNode->type = (iCTypRetVal > 0 ? EXP_Value : EXP_Invalid);
	                           pNode->fValue = (double) iCTypRetVal;
	                           ExpxStackPush( stack, pNode );
									}
         						break;  }

      case BF_FileExists : {  // SAC 1/6/04 - FileExists( <path/filename> )
                           BOOL bFileExists = FALSE;
                           QString sFileName;
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String)
                              ExpSetErr( error, EXP_RuleProc, "Invalid FileExists() argument type" );
                           else
                           {
                              sFileName = (const char*) pNode->pValue;
                              if (sFileName.isEmpty())
                                 ExpSetErr( error, EXP_RuleProc, "FileExists() argument empty" );
                              else
                                 bFileExists = FileExists( sFileName.toLocal8Bit().constData() );

                              free( pNode->pValue );
                              pNode->pValue = NULL;
                           }

                           if (sFileName.isEmpty())
                              pNode->type = EXP_Invalid;
                           else
                              pNode->type = EXP_Value;
                           pNode->fValue = (bFileExists ? 1 : 0);
                           ExpxStackPush( stack, pNode );
                           break;  }

      case BF_ImportComp : {  // SAC 1/6/04 - ImportComponentFromFile( <path/filename>, <CompType> )
                           ExpNode* pNode = NULL;
                           int iCompType = 0;
                           QString sFileName;
                           if (nArgs != 2)
                           {
                              ExpSetErr( error, EXP_RuleProc, "Invalid number of ImportComponentFromFile() arguments" );
                              // Pop and delete all nodes off stack
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {
                                 pNode = ExpxStackPop( stack );
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {
                                    free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
                           }
                           else
                           {
                              // Get the second argument - <path/filename>
                              pNode = ExpxStackPop( stack );
                              if (pNode->type != EXP_String)
                                 ExpSetErr( error, EXP_RuleProc, "Invalid ImportComponentFromFile() 2nd argument type" );
                              else
                              {
                                 sFileName = (const char*) pNode->pValue;
                                 if (sFileName.isEmpty())
                                    ExpSetErr( error, EXP_RuleProc, "ImportComponentFromFile() 2nd argument empty" );
                                 else if (!FileExists( sFileName.toLocal8Bit().constData() ))
                                 {
                                    ExpSetErr( error, EXP_RuleProc, "ImportComponentFromFile() 2nd argument - file not found" );
                                    sFileName.clear();
                                 }
                                 free( pNode->pValue );
                                 pNode->pValue = NULL;
                              }
                              // delete second argument node
                              ExpxNodeDelete( pNode );

                              // Get the first argument - CompType
                              pNode = ExpxStackPop( stack );
                              if (pNode->type != EXP_Value)
                                 ExpSetErr( error, EXP_RuleProc, "Invalid ImportComponentFromFile() 1st argument type" );
                              else if (pNode->fValue < 1 || pNode->fValue > BEMPX_GetNumClasses())
                                 ExpSetErr( error, EXP_RuleProc, "Invalid ImportComponentFromFile() 1st argument value" );
                              else
                                 iCompType = (int) pNode->fValue;
                              
                              // don't delete this node since it is the one we will set and push back onto the stack
                           }

                           if (pNode)
                           {
                              pNode->type = EXP_Invalid;
                              pNode->fValue = 0;
                              if (iCompType > 1 && !sFileName.isEmpty())
                              {
                                 BEMObject* pObj = BEMPX_ReadProjectComponent( sFileName.toLocal8Bit().constData(), iCompType );
                                 if (pObj && !pObj->getName().isEmpty())
                                 {
                                    pNode->type = EXP_String;
                                    pNode->pValue = malloc( pObj->getName().length() + 1 );
                                    strcpy( (char*) pNode->pValue, (const char*) pObj->getName().toLocal8Bit().constData() );
                                 }
                              }
                              ExpxStackPush( stack, pNode );
                           }
                           break;  }

      case BF_EnsureChild : { // SAC  4/27/04 - added EnsureChildAssigned() function
                           ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                           int iError;
                           BEMObject* pSupposedChildObj = NULL;
                           BEMObject* pPrimObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
                           assert( pPrimObj );
                           if ( BEMPX_GetObject( pEval->lPrimDBID, pSupposedChildObj, -1, pEval->iPrimObjIdx )  &&
                                pSupposedChildObj != NULL  &&  pSupposedChildObj->getParent() != pPrimObj )
                           {  // a non-child component is assigned!
                              BEMObject* pFirstChildObj = NULL;
                              if (BEMPX_GetNumChildren( pEval->lPrimDBID, pEval->iPrimObjIdx, pEval->ePrimObjType,
                                                                        pSupposedChildObj->getClass()->get1BEMClassIdx() ) > 0.5)
                              {  // get object index of the first child of the child class
                                 BEM_ObjType eChildObjType = BEMO_User;
                                 int iFirstChildObjIdx = BEMPX_GetChildObjectIndex( BEMPX_GetClassID( pEval->lPrimDBID ), pSupposedChildObj->getClass()->get1BEMClassIdx(),
                                                                                  iError, eChildObjType, 1, pEval->iPrimObjIdx, pEval->ePrimObjType );
                                 if (iFirstChildObjIdx >= 0)
                                    pFirstChildObj = BEMPX_GetObjectByClass( pSupposedChildObj->getClass()->get1BEMClassIdx(), iError, iFirstChildObjIdx, eChildObjType );
                              }

                              if (pFirstChildObj != NULL)
                              {  // assign the first child of the child class
                                 pNode->type = EXP_String;
                                 pNode->pValue = malloc( pFirstChildObj->getName().length() + 1 );
                                 strcpy( (char*) pNode->pValue, (const char*) pFirstChildObj->getName().toLocal8Bit().constData() );
                              }
                              else
                              {  // blast bogus assignment
                                 pNode->type = EXP_Value;
                                 pNode->fValue = -99998;   // => set to "NONE"
                              }
                           }
                           else
                           {  // if no component already assigned, then do not change anything
                              pNode->type = EXP_Value;
                              pNode->fValue = -99997;
                           }
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_IfValidAnd :   // IfValidAnd()    - SAC 2/13/14
      case BF_ValidOr    : { // ValidOr()       - SAC 4/1/14
										double dResult = 0.0;
										ExpNode* pNode = NULL;
										BOOL bArgsAreStrs = FALSE;
										QString sStr2;
										if (	(op == BF_IfValidAnd && nArgs != 3) ||
												(op == BF_ValidOr    && nArgs != 2) )
										{  if (op == BF_IfValidAnd)
												ExpSetErr( error, EXP_RuleProc, "Invalid number of IfValidAnd() function arguments (should be three)" );
											else
												ExpSetErr( error, EXP_RuleProc, "Invalid number of ValidOr() function arguments (should be two)" );
										   for ( int arg = nArgs; arg > 0; arg-- )		// Pop and delete all nodes off stack
										   {  pNode = ExpxStackPop( stack );
										      if (arg > 1)  // don't delete last argument - used to store return value
										         ExpxNodeDelete( pNode );
										      else if (pNode && pNode->type == EXP_String)
										      {  free( pNode->pValue );
										         pNode->pValue = NULL;
											}	}
											if (nArgs == 0)
												pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										}
										else
										{  double dVal1=0., dVal2=0.;
											QString sStr1;
											int iOper=0;
											BOOL bFuncEvalOK = TRUE;
											BOOL bPerformOperation = TRUE;
									// Final Argument
										   pNode = ExpxStackPop( stack );
											if (pNode && pNode->type == EXP_Invalid)
											{	if (op == BF_IfValidAnd)
													bPerformOperation = FALSE;
												else
												{	bFuncEvalOK = FALSE;
													ExpSetErr( error, EXP_RuleProc, "Invalid final ValidOr() function argument (should be static numeric or string)" );
											}	}
											else if (pNode && pNode->type == EXP_Value)
												dVal2 = pNode->fValue;
											else if (pNode && pNode->type == EXP_String)
											{	bArgsAreStrs = TRUE;
												sStr2 = (char*) pNode->pValue;
											}
											else
											{	bFuncEvalOK = FALSE;
												if (op == BF_IfValidAnd)
													ExpSetErr( error, EXP_RuleProc, "Invalid final IfValidAnd() function argument (should be numeric or string)" );
												else
													ExpSetErr( error, EXP_RuleProc, "Invalid final ValidOr() function argument (should be numeric or string)" );
											}
											if (pNode)
												ExpxNodeDelete( pNode );
									// Conditional Operator
											if (op == BF_IfValidAnd)
										   {	pNode = ExpxStackPop( stack );
												if (pNode && pNode->type == EXP_Value && pNode->fValue >= EQ && pNode->fValue <= GE)
													iOper = (int) pNode->fValue;
												else
												{	bFuncEvalOK = FALSE;
	         								   ExpSetErr( error, EXP_RuleProc, "Invalid middle IfValidAnd() argument (expecting conditional operator)" );
												}
												if (pNode)
													ExpxNodeDelete( pNode );
											}
									// First Argument
										   pNode = ExpxStackPop( stack );
											if (pNode && pNode->type == EXP_Invalid)
												bPerformOperation = FALSE;
											else if (!bArgsAreStrs && pNode && pNode->type == EXP_Value)
												dVal1 = pNode->fValue;
											else if (bArgsAreStrs && pNode && pNode->type == EXP_String)
											{	sStr1 = (char*) pNode->pValue;
												dVal1 = pNode->fValue;  // still grab fValue which can indicate whether or not data retrieved from BEMBase was undefined
											}
											else if (pNode && ( (bArgsAreStrs && pNode->type == EXP_Value) || (!bArgsAreStrs && pNode->type == EXP_String) ))
											{	bFuncEvalOK = FALSE;
												if (op == BF_IfValidAnd)
													ExpSetErr( error, EXP_RuleProc, "Incompatible IfValidAnd() function arguments (must both be numeric or string)" );
												else
													ExpSetErr( error, EXP_RuleProc, "Incompatible ValidOr() function arguments (must both be numeric or string)" );
											}
											else
											{	bFuncEvalOK = FALSE;
												if (op == BF_IfValidAnd)
													ExpSetErr( error, EXP_RuleProc, "Invalid first IfValidAnd() function argument (should be numeric or string)" );
												else
													ExpSetErr( error, EXP_RuleProc, "Invalid first ValidOr() function argument (should be numeric or string)" );
											}
											//if (pNode)   - This node used to return result
											//	ExpxNodeDelete( pNode );
											if (pNode->type == EXP_String)
											{	free( pNode->pValue );
												pNode->pValue = NULL;
											}
									// Perform Operation
											if (bFuncEvalOK)
											{	if (op == BF_ValidOr)
												{	if (!bPerformOperation || WithinMargin( dVal1, -99996.0, 0.1 ))
													{	if (!bArgsAreStrs)
															dResult = dVal2;
													}
													else
													{	dResult = dVal1;
														sStr2 = sStr1;
												}	}
												else if (bPerformOperation)
												{	if (bArgsAreStrs)
													{	// STRING comparison
														switch (iOper)
														{	case EQ :	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) == 0 ? 1.0 : 0.0);		break;     // #define EQ 268   - was: _stricmp( sStr1, sStr2 )
															case NEQ:	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) != 0 ? 1.0 : 0.0);		break;     // #define NEQ 269 
															case LT :	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) <  0 ? 1.0 : 0.0);		break;     // #define LT 270  
															case GT :	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) >  0 ? 1.0 : 0.0);		break;     // #define GT 271  
															case LE :	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) <= 0 ? 1.0 : 0.0);		break;     // #define LE 272  
															case GE :	dResult = (sStr1.compare( sStr2, Qt::CaseInsensitive ) >= 0 ? 1.0 : 0.0);		break;     // #define GE 273  
													}	}
													else
													{	// NUMERIC comparison
														switch (iOper)
											//			{	case EQ :	dResult = (dVal1 == dVal2 ? 1.0 : 0.0);		break;
											//				case NEQ:	dResult = (dVal1 != dVal2 ? 1.0 : 0.0);		break;
											//				case LT :	dResult = (dVal1 <  dVal2 ? 1.0 : 0.0);		break;
											//				case GT :	dResult = (dVal1 >  dVal2 ? 1.0 : 0.0);		break;
											//				case LE :	dResult = (dVal1 <= dVal2 ? 1.0 : 0.0);		break;
											//				case GE :	dResult = (dVal1 >= dVal2 ? 1.0 : 0.0);		break;		- SAC 4/21/17 - replaced w/ below to better handle floating point representation issues
														{	case EQ :	dResult = (AreSame( dVal1, dVal2 )    ? 1.0 : 0.0);		break;
															case NEQ:	dResult = (AreSame( dVal1, dVal2 )==0 ? 1.0 : 0.0);		break;
															case LT :	dResult = ((dVal1 < dVal2 && AreSame( dVal1, dVal2 )==0) ? 1.0 : 0.0);		break;
															case GT :	dResult = ((dVal1 > dVal2 && AreSame( dVal1, dVal2 )==0) ? 1.0 : 0.0);		break;
															case LE :	dResult = ((dVal1 < dVal2 || AreSame( dVal1, dVal2 )   ) ? 1.0 : 0.0);		break;
															case GE :	dResult = ((dVal1 > dVal2 || AreSame( dVal1, dVal2 )   ) ? 1.0 : 0.0);		break;
												}	}	}
										}	}
                              pNode->type = (op == BF_IfValidAnd || !bArgsAreStrs) ? EXP_Value : EXP_String;
										if (pNode->type == EXP_Value)
	                              pNode->fValue = dResult;
										else
										{	pNode->pValue = malloc( sStr2.length() + 1 );
											strcpy( (char*) pNode->pValue, (const char*) sStr2.toLocal8Bit().constData() );
										}
										ExpxStackPush( stack, pNode );
										break; }

		case BF_SymString  :  { // SAC 4/10/14
										ExpNode* pNode = ExpxStackPop( stack );
										if (pNode && pNode->type == EXP_String)
										{	// simply push node back onto stack - this is ALREADY the valid return string
										}
										else
										{	ExpSetErr( error, EXP_RuleProc, "Invalid EnumString() argument - should be Loc/Par#/Global Object:Property name" );
											if (pNode == NULL)
												pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
											pNode->type = EXP_Invalid;
											pNode->fValue = 0.0;
										}
										ExpxStackPush( stack, pNode );
										break; }

      case BF_BEMProcDBID:  { // BEMProcDBID()    - SAC 6/14/07
                           QString sComp, sParam;
                           int iArrIdx=0;
                           // Get the last argument - Array
                           ExpNode* pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_Value)
                              ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() 3rd argument type" );
                           else if (pNode->fValue < 0  ||  pNode->fValue >= BEM_PARAM_MULT)
                              ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() array index" );
                           else
                              iArrIdx = (int) pNode->fValue;
                           // delete third argument node
                           ExpxNodeDelete( pNode );
                              
                           // Get the 2nd argument - Property Name
                           pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String || pNode->pValue == NULL)
                              ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() 2nd argument type" );
                           else
                              sParam = (const char*) pNode->pValue;
                           // delete second argument node
                           ExpxNodeDelete( pNode );
                              
                           // Get the 1st argument - Component Type Name
                           pNode = ExpxStackPop( stack );
                           if (pNode->type != EXP_String || pNode->pValue == NULL)
                              ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() 1st argument type" );
                           else
                           {
                              sComp = (const char*) pNode->pValue;
                              free( pNode->pValue );
                           }
                           // don't delete this node since it is the one we will set and push back onto the stack - but DO (above) free up the char string memory

                           pNode->type = EXP_Invalid;
                           pNode->fValue = 0;
                           int iClass = BEMP_GetDBComponentID( sComp );
                           if (iClass < 1)
                              ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() 1st argument type - Class name not found" );
                           else
                           {
                              long lParamID = BEMP_GetDBParameterID( sParam, iClass );
                              if (lParamID <= BEM_PARAM_MULT || lParamID >= BEM_COMP_MULT)
                              {  assert( FALSE );
                                 ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcDBID() 2nd argument type - Property type not found" );
                              }
                              else
                              {
                                 lParamID /= BEM_PARAM_MULT;
                                 pNode->fValue = (double) BEMPX_GetDBID( iClass, lParamID, iArrIdx );
                                 pNode->type = EXP_Value;
                              }
                           }

                           // Push second argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_YrMoDa2Date :   // long YrMoDaToSerial( int iYr, int iMo, int iDa );  
      case BF_YrMoDa2DOW  :   // int YrMoDaToDayOfWeek( int iYr, int iMo, int iDa );
								{	ExpNode* pNode=NULL;
									int iYr=-1, iMo=-1, iDa=-1;
									bool bErrorLogged = false;
                           for ( int arg = nArgs; arg > 0; arg-- )
                           {  pNode = ExpxStackPop( stack );				assert( pNode );
										if (!bErrorLogged && pNode && pNode->type != EXP_Value)
										{	QString sErrMsg = QString( "Invalid %1() argument #%2 (%3) - should be numeric value." ).arg( (op == BF_YrMoDa2Date ?	"YrMoDaToSerial" : "YrMoDaToDayOfWeek"), QString::number( arg ), (arg==1 ? "year" : (arg==2 ? "month" : "day")) );
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
											bErrorLogged = true;
										}
										else if (!bErrorLogged && pNode && pNode->fValue < 1 && pNode->fValue != -1)
										{	QString sErrMsg = QString( "Invalid %1() argument #%2 (%3) - numeric value must be >= 1 (or -1 indicating 'today')." ).arg( (op == BF_YrMoDa2Date ?	"YrMoDaToSerial" : "YrMoDaToDayOfWeek"), QString::number( arg ), (arg==1 ? "year" : (arg==2 ? "month" : "day")) );
											ExpSetErr( error, EXP_RuleProc, sErrMsg );
											bErrorLogged = true;
										}
										else if (!bErrorLogged && pNode && pNode->fValue == -1)	// SAC 11/9/17 - new option to allow for 'today'
										{	QDateTime time = QDateTime::currentDateTime();
											switch (arg)
											{	case  1 :  iYr = time.date().year();		break;
												case  2 :  iMo = time.date().month();		break;
												case  3 :  iDa = time.date().day();			break;
										}	}
										else if (!bErrorLogged && pNode && pNode->fValue >= 1)
										{	switch (arg)
											{	case  1 :  iYr = (int) pNode->fValue;		break;
												case  2 :  iMo = (int) pNode->fValue;		break;
												case  3 :  iDa = (int) pNode->fValue;		break;
										}	}
                              if (arg > 1)  // don't delete last argument - used to store return value
                                 ExpxNodeDelete( pNode );
                           }
									if (pNode == NULL)
										pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                           if (bErrorLogged)
									{	pNode->type = EXP_Invalid;
										pNode->fValue = 0.0;
									}
									else if (op == BF_YrMoDa2Date)
										pNode->fValue = (double) YrMoDaToSerial( iYr, iMo, iDa );
									else
										pNode->fValue = (double) YrMoDaToDayOfWeek( iYr, iMo, iDa );
									ExpxStackPush( stack, pNode );
									break; }

      case BF_Date2WkDay  :   // int SerialDateToDayOfMonth( long lSerial );        
      case BF_Date2Mo     :   // int SerialDateToMonth( long lSerial );             
      case BF_Date2Yr     :   // int SerialDateToYear( long lSerial );              
								{	ExpNode* pNode = ExpxStackPop( stack );				assert( pNode );
									if (pNode == NULL || pNode->type != EXP_Value || pNode->fValue < 1)
									{	QString sErrMsg = QString( "Invalid %1() date argument - %2." ).arg(
													(op == BF_Date2WkDay ?	"SerialDateToDayOfMonth" : (op == BF_Date2Mo ?	"SerialDateToMonth" : "SerialDateToYear")),
													(pNode->type != EXP_Value ? "should be numeric value" : "must be > 0") );
										ExpSetErr( error, EXP_RuleProc, sErrMsg );
										if (pNode == NULL)
											pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
										pNode->type = EXP_Invalid;
										pNode->fValue = 0.0;
									}
									else if (pNode)
									{	switch (op)
										{	case  BF_Date2WkDay :  pNode->fValue = (double) SerialDateToDayOfMonth( (long) pNode->fValue );		break;
											case  BF_Date2Mo    :  pNode->fValue = (double) SerialDateToMonth(      (long) pNode->fValue );		break;
											case  BF_Date2Yr    :  pNode->fValue = (double) SerialDateToYear(       (long) pNode->fValue );		break;
									}	}
									ExpxStackPush( stack, pNode );
									break; }

      case BF_HrlyResSum : {  // SAC 5/15/12 - HourlyResultSum( <"RunName">, <"MeterName">, <"EnduseOne">, ... )
                           ExpNode* pNode = NULL;
									BOOL bArgsOK = FALSE;
									double dResult = -99999.0;
                           if (nArgs < 3 || nArgs > 10)
                           {  ExpSetErr( error, EXP_RuleProc, "Invalid number of HourlyResultSum() arguments (must be 3-10 strings)" );
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
                           }
                           else
                           {	// valid # of arguments
										QString sArgs[10];
										bArgsOK = TRUE;
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (pNode && pNode->type == EXP_String)
												sArgs[arg-1] = (char*) pNode->pValue;
											else
                           	   {	bArgsOK = FALSE;
												ExpSetErr( error, EXP_RuleProc, "Invalid HourlyResultSum() function argument type (all must be strings)." );
                                 }
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
										if (bArgsOK)
										{	char szErrMsg[256];
											szErrMsg[0] = '\0';
											dResult = BEMPX_GetHourlyResultSum( szErrMsg, 256,  sArgs[0].toLocal8Bit().constData(), sArgs[1].toLocal8Bit().constData(),
																sArgs[2].toLocal8Bit().constData(), sArgs[3].toLocal8Bit().constData(), sArgs[4].toLocal8Bit().constData(),
																sArgs[5].toLocal8Bit().constData(), sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(),
																sArgs[8].toLocal8Bit().constData(), sArgs[9].toLocal8Bit().constData() );
											if (szErrMsg[0] != '\0')
												ExpSetErr( error, EXP_RuleProc, szErrMsg );
										}
									}
									if (WithinMargin( dResult, -99999.0, 0.1 ))
									{  pNode->type = EXP_Invalid;
	                           pNode->fValue = 0;
									}
									else
                           {	pNode->type = EXP_Value;
										pNode->fValue = dResult;
                           }
                           // Push result argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_HrlyResMult :   // SAC 5/15/12 - ApplyHourlyResultMultipliers( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"EnduseOne">, ... )
      								// SAC 9/22/17 - inserted new arguments 4,5,6 (SecHrlyTblName, SecHrlyTblCol# & SecHrlyMult) to enable GHG adders to TDV data for emissions-based analysis
      								// SAC 10/4/17 - modified routine to allow <"HrlyMultTableName"> of "none" to cause a single float stored in #TableDepColumn to be applied to the hourly results
      case BF_HrlyResMltNeg :  // SAC 10/4/17 - ApplyHourlyResultMultipliers_Neg( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"EnduseOne">, ... )
      								 //					(same as BF_HrlyResMult but storing & applying multipliers only to negative values in Meter-Enduse array)
                        {  ExpNode* pNode = NULL;
									BOOL bArgsOK = FALSE;
									double dResult = -99999.0;
                           if (nArgs < 9 || nArgs > 16)
                           {  ExpSetErr( error, EXP_RuleProc, "Invalid number of ApplyHourlyResultMultipliers() arguments (must be 9-16, all strings except #3, 5 & 6 integer table column indices (3,5) & conversion factor(6))" );
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
                           }
                           else
                           {	// valid # of arguments
										QString sArgs[16];
										int iTableColumn = -1, iSecTblCol = -1;
										double dConstHrlyMult = -999, dSecTblMult = 1.0;
										bArgsOK = TRUE;
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (pNode && arg == 3 && pNode->type == EXP_Value)
												dConstHrlyMult = pNode->fValue;
                                 else if (pNode && arg == 5 && pNode->type == EXP_Value)
												iSecTblCol   = (int) pNode->fValue;
                                 else if (pNode && arg == 6 && pNode->type == EXP_Value)
												dSecTblMult  =       pNode->fValue;
											else if (pNode && arg != 3 && arg != 5 && arg != 6 && pNode->type == EXP_String)
												sArgs[arg-1] = (char*) pNode->pValue;
											else
                           	   {	bArgsOK = FALSE;
												ExpSetErr( error, EXP_RuleProc, QString( "Invalid ApplyHourlyResultMultipliers() function argument #%1 type (str, str, int, str, int, float, str, str, str<, str, str...>)." ).arg( QString::number(arg) ) );
                                 }
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
										if (bArgsOK)
										{
											BEMTable* pTable = NULL;
											bool bHaveSecTbl = false;
											BEMTable* pSecTable = NULL;
											bool bHrlyMultIsConst = (sArgs[1].length() > 0 && sArgs[1].compare( "none", Qt::CaseInsensitive ) == 0 && dConstHrlyMult != -999);
											bool bHrlyMultTableOK = true;
											if (!bHrlyMultIsConst)
											{	iTableColumn = (int) dConstHrlyMult;
												bHrlyMultTableOK = false;
											// copy of this table population stuff also exported via routine in Table.cpp
												pTable = ruleSet.getTablePtr( sArgs[1].toLocal8Bit().constData() );
												bHaveSecTbl = (sArgs[3].length() > 0 && sArgs[3].compare( "none", Qt::CaseInsensitive ) != 0);
												pSecTable = (!bHaveSecTbl ? NULL : ruleSet.getTablePtr( sArgs[3].toLocal8Bit().constData() ));
												if (pTable == NULL)
													ExpSetErr( error, EXP_RuleProc, "Table referenced by ApplyHourlyResultMultipliers() function argument not found." );
												else if (iTableColumn > pTable->getNCols())
													ExpSetErr( error, EXP_RuleProc, "Table column specified in ApplyHourlyResultMultipliers() function argument too high." );
												else if (bHaveSecTbl && pSecTable == NULL)
													ExpSetErr( error, EXP_RuleProc, "Secondary (adder) table referenced by ApplyHourlyResultMultipliers() function argument not found." );
												else if (bHaveSecTbl && iSecTblCol > pSecTable->getNCols())
													ExpSetErr( error, EXP_RuleProc, "Secondary (adder) table column specified in ApplyHourlyResultMultipliers() function argument too high." );
	                                 else
													bHrlyMultTableOK = true;
											}
											if (bHrlyMultTableOK)                             
											{	double dHrlyRes[8760];
												char szErrMsg[80];
												szErrMsg[0] = '\0';
												dResult = BEMPX_GetHourlyResultArray( szErrMsg, 80, dHrlyRes,  sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(),
																					sArgs[8].toLocal8Bit().constData(), sArgs[9].toLocal8Bit().constData(), sArgs[10].toLocal8Bit().constData(),
																					sArgs[11].toLocal8Bit().constData(), sArgs[12].toLocal8Bit().constData(), sArgs[13].toLocal8Bit().constData(),
																					sArgs[14].toLocal8Bit().constData(), sArgs[15].toLocal8Bit().constData() );
												if (szErrMsg[0] != '\0')
													ExpSetErr( error, EXP_RuleProc, szErrMsg );
												else if (WithinMargin( dResult, -99999.0, 0.1 ))
													ExpSetErr( error, EXP_RuleProc, "Error encountered retrieving hourly results to be scaled via ApplyHourlyResultMultipliers*() function." );
												else
											// SAC 8/23/14 - mods to allow arg #1 to be "none" => NO storage of final hourly array - only return sum
												{	double dTblVal, dSecTblVal, dHrlySum=0.0;
													for (int iHr=0; iHr<8760; iHr++)
													{	if (op == BF_HrlyResMltNeg && dHrlyRes[iHr] >= 0)
															dHrlyRes[iHr] = 0;		// SAC 10/4/17 - don't apply multiplier and zero out Meter-Enduse array values that are not < 0 for ApplyHourlyResultMultipliers_Neg() function
														else if (bHrlyMultIsConst)
															dHrlyRes[iHr] *= dConstHrlyMult;  // APPLY single (constant) multiplier
														else if (pTable->GrabRecord( iHr+1, iTableColumn, &dTblVal ))  //, BOOL bVerboseOutput=FALSE );  // SAC 5/15/12
														{	if (bHaveSecTbl && pSecTable->GrabRecord( iHr+1, iSecTblCol, &dSecTblVal ))
																dHrlyRes[iHr] *= (dTblVal + (dSecTblVal*dSecTblMult));  // APPLY hourly multiplier factors (w/ adder)
															else
																dHrlyRes[iHr] *= dTblVal;  // APPLY hourly multiplier factors
															dHrlySum += dHrlyRes[iHr];
														}
														else
														{	dResult = -99999;
															ExpSetErr( error, EXP_RuleProc, "Error retrieving hourly table multiplier in ApplyHourlyResultMultipliers*() function." );
															break;
														}
													}

													if (!WithinMargin( dResult, -99999.0, 0.1 ))
													{	if (sArgs[0].compare("none", Qt::CaseInsensitive) == 0)
															dResult = dHrlySum;	// only return sum of multiplied array - don't add array into an hourly enduse
														else
															dResult = BEMPX_AddHourlyResultArray( dHrlyRes, sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(),
																															sArgs[0].toLocal8Bit().constData() );
														if (WithinMargin( dResult, -99999.0, 0.1 ))
															ExpSetErr( error, EXP_RuleProc, "Error adding hourly result array within ApplyHourlyResultMultipliers*() function." );
											}	}	}
         							}
									}
									if (WithinMargin( dResult, -99999.0, 0.1 ))
									{  pNode->type = EXP_Invalid;
	                           pNode->fValue = 0;
									}
									else
                           {	pNode->type = EXP_Value;
										pNode->fValue = dResult;
                           }
                           // Push result argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_CopyHrlyRes :   // SAC 10/5/17 - CopyHourlyResults( <"SrcRunName">, <"SrcMeterName">, <"SrcEnduse">, <"DestRunName">, <"DestMeterName">, <"DestEnduseOne"> )
                        {  ExpNode* pNode = NULL;
									BOOL bArgsOK = FALSE;
									double dResult = -99999.0;
                           	// valid # of arguments
										QString sSrcRun, sSrcMeter, sSrcEU, sDestRun, sDestMeter, sDestEU;
										bArgsOK = TRUE;
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
											if (pNode == NULL || pNode->type != EXP_String || strlen( (char*) pNode->pValue ) < 1)
                           	   {	bArgsOK = FALSE;
												ExpSetErr( error, EXP_RuleProc, QString( "Invalid CopyHourlyResults() function argument #%1: ( SrcRunName, SrcMeterName, SrcEnduse, DestRunName, DestMeterName, DestEnduseOne ) (all strings)." ).arg( QString::number(arg) ) );
                                 }
                                 else
                                 	switch (arg)
                                 	{	case  1 :  sSrcRun    = (char*) pNode->pValue;   break;
                                 		case  2 :  sSrcMeter  = (char*) pNode->pValue;   break;
                                 		case  3 :  sSrcEU     = (char*) pNode->pValue;   break;
                                 		case  4 :  sDestRun   = (char*) pNode->pValue;   break;
                                 		case  5 :  sDestMeter = (char*) pNode->pValue;   break;
                                 		default :  sDestEU    = (char*) pNode->pValue;   break;
                                 	}
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }

										if (bArgsOK)
										{	double dHrlyRes[8760];
											char szErrMsg[80];
											szErrMsg[0] = '\0';
											dResult = BEMPX_GetHourlyResultArray( szErrMsg, 80, dHrlyRes,  sSrcRun.toLocal8Bit().constData(),
																				sSrcMeter.toLocal8Bit().constData(), sSrcEU.toLocal8Bit().constData() );
											if (szErrMsg[0] != '\0')
												ExpSetErr( error, EXP_RuleProc, szErrMsg );
											else if (WithinMargin( dResult, -99999.0, 0.1 ))
												ExpSetErr( error, EXP_RuleProc, "Error encountered retrieving hourly results to be copied via CopyHourlyResults() function." );
											else
											{	dResult = BEMPX_AddHourlyResultArray( dHrlyRes, sDestRun.toLocal8Bit().constData(),
																sDestMeter.toLocal8Bit().constData(), sDestEU.toLocal8Bit().constData() );
												if (WithinMargin( dResult, -99999.0, 0.1 ))
													ExpSetErr( error, EXP_RuleProc, "Error copying hourly result array within CopyHourlyResults() function." );
										}	}

									if (WithinMargin( dResult, -99999.0, 0.1 ))
									{  pNode->type = EXP_Invalid;
	                           pNode->fValue = 0;
									}
									else
                           {	pNode->type = EXP_Value;
										pNode->fValue = 1;
                           }
                           // Push result argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      case BF_HrlyResMltNEM : {  // SAC 1/23/17 - ApplyHourlyResultMultipliers_NEM( <"NewEnduseName">, <"HrlyMultTableName">, #TableDepColumn, <"RunName">, <"MeterName">, <"SaleEnduse">, <"TotalEnduse">, <NEMconstant>, <SaleHrlyMultiplier>, <"OtherSaleEnduseOne">, ... )
      									// SAC 9/22/17 - inserted new arguments 4,5,6 (SecHrlyTblName, SecHrlyTblCol# & SecHrlyMult) to enable GHG adders to TDV data for emissions-based analysis
                           ExpNode* pNode = NULL;
									BOOL bArgsOK = FALSE;
									double dResult = -99999.0;
                           if (nArgs < 11 || nArgs > 19)
                           {  ExpSetErr( error, EXP_RuleProc, "Invalid number of ApplyHourlyResultMultipliers_NEM() arguments (must be 11-19, all strings except #s3 & 5 integer table column indices, #6 TDV adder multiplier, #11 NEM constant & #12 sale enduse multiplier)" );
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
                           }
                           else
                           {	// valid # of arguments
										QString sArgs[19];
										int iTableColumn = -1, iSecTblCol = -1;
										double dNEMconst = 0.0, dHrlyMult=1.0, dSecTblMult = 1.0;
										bArgsOK = TRUE;
                              for ( int arg = nArgs; arg > 0; arg-- )
                              {  pNode = ExpxStackPop( stack );  // Pop and delete all nodes off stack
                                 if (pNode && arg == 3 && pNode->type == EXP_Value)
												iTableColumn = (int) pNode->fValue;
                                 else if (pNode && arg == 5 && pNode->type == EXP_Value)
												iSecTblCol   = (int) pNode->fValue;
                                 else if (pNode && arg == 6 && pNode->type == EXP_Value)
												dSecTblMult  =       pNode->fValue;
                                 else if (pNode && arg == 11 && pNode->type == EXP_Value)
												dNEMconst = pNode->fValue;
                                 else if (pNode && arg == 12 && pNode->type == EXP_Value)
												dHrlyMult = pNode->fValue;
											else if (pNode && arg != 3 && arg != 5 && arg != 6 && arg != 11 && arg != 12 && pNode->type == EXP_String)
												sArgs[arg-1] = (char*) pNode->pValue;
											else
                           	   {	bArgsOK = FALSE;
												ExpSetErr( error, EXP_RuleProc, QString( "Invalid ApplyHourlyResultMultipliers_NEM() function argument #%1 type (str, str, int, str, int, float, str, str, str, float<, float, str, str...>)." ).arg( QString::number(arg) ) );
                                 }
                                 if (arg > 1)  // don't delete last argument - used to store return value
                                    ExpxNodeDelete( pNode );
                                 else if (pNode && pNode->type == EXP_String)
                                 {  free( pNode->pValue );
                                    pNode->pValue = NULL;
                                 }
                              }
										if (bArgsOK)
										{
							// copy of this table population stuff also exported via routine in Table.cpp
											BEMTable* pTable = ruleSet.getTablePtr( sArgs[1].toLocal8Bit().constData() );
											bool bHaveSecTbl = (sArgs[3].length() > 0 && sArgs[3].compare( "none", Qt::CaseInsensitive ) != 0);
											BEMTable* pSecTable = (!bHaveSecTbl ? NULL : ruleSet.getTablePtr( sArgs[3].toLocal8Bit().constData() ));
											if (pTable == NULL)
												ExpSetErr( error, EXP_RuleProc, "Table referenced by ApplyHourlyResultMultipliers_NEM() function argument not found." );
											else if (iTableColumn < 1 || iTableColumn > pTable->getNCols())
												ExpSetErr( error, EXP_RuleProc, "Table column specified in ApplyHourlyResultMultipliers_NEM() function argument out of range." );
											else if (bHaveSecTbl && pSecTable == NULL)
												ExpSetErr( error, EXP_RuleProc, "Secondary (adder) table referenced by ApplyHourlyResultMultipliers_NEM() function argument not found." );
											else if (bHaveSecTbl && (iSecTblCol < 1 || iSecTblCol > pSecTable->getNCols()))
												ExpSetErr( error, EXP_RuleProc, "Secondary (adder) table column specified in ApplyHourlyResultMultipliers_NEM() function argument out of range." );
                                 else
											{	double dTotHrlyRes[8760], dSaleHrlyRes[8760], dOthrHrlyRes[8760];
												char szErrMsg[80];
												szErrMsg[0] = '\0';
												double dTot  = BEMPX_GetHourlyResultArray( szErrMsg, 80, dTotHrlyRes,  sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(), sArgs[9].toLocal8Bit().constData() );
												if (szErrMsg[0] != '\0')
													ExpSetErr( error, EXP_RuleProc, szErrMsg );
												else if (WithinMargin( dTot, -99999.0, 0.1 ))
													ExpSetErr( error, EXP_RuleProc, "Error encountered retrieving total enduse hourly results to be referenced by ApplyHourlyResultMultipliers_NEM() function." );
												else
												{	double dSale = BEMPX_GetHourlyResultArray( szErrMsg, 80, dSaleHrlyRes, sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(), sArgs[8].toLocal8Bit().constData() );
													if (szErrMsg[0] != '\0')
														ExpSetErr( error, EXP_RuleProc, szErrMsg );
													else if (WithinMargin( dSale, -99999.0, 0.1 ))
														ExpSetErr( error, EXP_RuleProc, "Error encountered retrieving sale enduse hourly results to be referenced by ApplyHourlyResultMultipliers_NEM() function." );
													else
													{	dResult = BEMPX_GetHourlyResultArray( szErrMsg, 80, dOthrHrlyRes,  sArgs[6].toLocal8Bit().constData(),  sArgs[7].toLocal8Bit().constData() , sArgs[12].toLocal8Bit().constData() ,
																							sArgs[13].toLocal8Bit().constData(), sArgs[14].toLocal8Bit().constData(), sArgs[15].toLocal8Bit().constData(), sArgs[16].toLocal8Bit().constData(),
																							sArgs[17].toLocal8Bit().constData(), sArgs[18].toLocal8Bit().constData() );
														if (szErrMsg[0] != '\0' && sArgs[12].length() > 0)
															ExpSetErr( error, EXP_RuleProc, szErrMsg );
														else
														{	int iHr;
															if (WithinMargin( dResult, -99999.0, 0.1 ))
															{	dResult = 0.0;
																for (iHr=0; iHr<8760; iHr++)
																	dOthrHrlyRes[iHr] = 0.0;
															}
														// apply <SaleHrlyMultiplier> if not = 1.0 - SAC 4/7/17
															if (dHrlyMult != 1.0)
															{	for (iHr=0; iHr<8760; iHr++)
																{	dTotHrlyRes[ iHr] -= (dSaleHrlyRes[iHr] + dOthrHrlyRes[iHr]);	// remove effect of original sale enduses
																	dSaleHrlyRes[iHr] *= dHrlyMult;											// apply multiplier to sale enduse series
																	dOthrHrlyRes[iHr] *= dHrlyMult;
																	dTotHrlyRes[ iHr] += (dSaleHrlyRes[iHr] + dOthrHrlyRes[iHr]);	// add back effect of multiplied sale enduses
															}	}
															double dTblVal, dSecTblVal, dHrlySum=0.0, dSell;
															for (iHr=0; iHr<8760; iHr++)
															{	if (pTable->GrabRecord( iHr+1, iTableColumn, &dTblVal ))  //, BOOL bVerboseOutput=FALSE );  // SAC 5/15/12
																{	if (dSaleHrlyRes[iHr] == 0.0)
																	{  // do nothing to zero hourly result
																	}
																	else
																	{	if (bHaveSecTbl && pSecTable->GrabRecord( iHr+1, iSecTblCol, &dSecTblVal ))
																			dTblVal += (dSecTblVal*dSecTblMult);  // add (GHG) adder to hourly multiplier
																		if (dTotHrlyRes[iHr] < 0 && dNEMconst != 0.0)
																		{	dSell = dTotHrlyRes[iHr] * dSaleHrlyRes[iHr] / (dSaleHrlyRes[iHr] + dOthrHrlyRes[iHr]);			// elec of Sale enduse to be added back into the grid this hour
																			dSaleHrlyRes[iHr] = ((dSaleHrlyRes[iHr] - dSell) * dTblVal) + (dSell * (dTblVal - dNEMconst));	// TDV calc taking into account NEM constant
																		}
																		else
																			dSaleHrlyRes[iHr] *= dTblVal;  // APPLY hourly multiplier factors
																		dHrlySum += dSaleHrlyRes[iHr];
																}	}
																else
																{	dResult = -99999;
																	ExpSetErr( error, EXP_RuleProc, "Error retrieving hourly table multiplier in ApplyHourlyResultMultipliers_NEM() function." );
																	break;
																}
															}
															if (!WithinMargin( dResult, -99999.0, 0.1 ))
															{	if (sArgs[0].compare("none", Qt::CaseInsensitive) == 0)
																	dResult = dHrlySum;	// only return sum of multiplied array - don't add array into an hourly enduse
																else
																	dResult = BEMPX_AddHourlyResultArray( dSaleHrlyRes, sArgs[6].toLocal8Bit().constData(), sArgs[7].toLocal8Bit().constData(),
																																		 sArgs[0].toLocal8Bit().constData() );
																if (WithinMargin( dResult, -99999.0, 0.1 ))
																	ExpSetErr( error, EXP_RuleProc, "Error adding hourly result array within ApplyHourlyResultMultipliers_NEM() function." );
											}	}	}	}	}
         							}
									}
									if (WithinMargin( dResult, -99999.0, 0.1 ))
									{  pNode->type = EXP_Invalid;
	                           pNode->fValue = 0;
									}
									else
                           {	pNode->type = EXP_Value;
										pNode->fValue = dResult;
                           }
                           // Push result argument node back onto the stack to serve as return value
                           ExpxStackPush( stack, pNode );
                           break; }

      default : { // "Check for table lookups", 
                  if ( op < 0 )
                     TableLookupFunction( op, nArgs, stack, pEval, error );
                  else
                     ExpSetErr( error, EXP_RuleProc, "Invalid function name" );
                break; }

         break;
   }
}
#pragma warning(default : 4996)


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  CreateDeleteFuncLeftSideOK()
//
// Purpose ------------------------------------------------------------------
//   Determines whether the left side of the rule which is evaluating a
//   Create*() ro Delete*() function call is of a legal type.
//   
/////////////////////////////////////////////////////////////////////////////
static BOOL CreateDeleteFuncLeftSideOK( int op, int nArgs, ExpEvalStruct* pEval, ExpError* error )
{
   int iDataType = BEMPX_GetDataType( pEval->lLocDBID );
   int iPropType = BEMPX_GetPropertyID( pEval->lLocDBID );
   int iArrayIdx = BEMPX_GetArrayID(    pEval->lLocDBID );

   if (op == BF_Cr8Child && (iDataType != BEMP_Str || iPropType != 0 || iArrayIdx != BEM_PARAM0_ACTION))
      ExpSetErr( error, EXP_RuleProc, "CreateChildren() must resolve to a *:Action property." );
   else if (op == BF_Cr8Child && (nArgs < 3 || nArgs > 5))
      ExpSetErr( error, EXP_RuleProc, "CreateChildren() must have between 3 and 5 arguments." );

   else if (op == BF_DelChild && (iDataType != BEMP_Str || iPropType != 0 || iArrayIdx != BEM_PARAM0_ACTION))
      ExpSetErr( error, EXP_RuleProc, "DeleteChildren() must resolve to a *:Action property." );
   else if (op == BF_DelChild && (nArgs < 1 || nArgs > 3))
      ExpSetErr( error, EXP_RuleProc, "DeleteChildren() must have between 1 and 3 arguments." );

   else if (op == BF_Cr8Comp && iDataType != BEMP_Obj && (iDataType != BEMP_Str || iPropType != 0 || iArrayIdx != BEM_PARAM0_ACTION))
      ExpSetErr( error, EXP_RuleProc, "CreateComp() must resolve to either a *:Action or component assignment property." );
   else if (op == BF_Cr8Comp && (nArgs < 2 || nArgs > 5))
      ExpSetErr( error, EXP_RuleProc, "CreateComp() must have between 2 and 5 arguments." );

	// SAC 2/5/06 - allow DelComp property to be set to "Action" => delete the "active" component
   else if (op == BF_DelComp && iDataType != BEMP_Obj && 
                                (BEMPX_GetPropertyID( pEval->lPrimDBID ) != 0 || BEMPX_GetArrayID( pEval->lLocDBID ) != BEM_PARAM0_ACTION))
      ExpSetErr( error, EXP_RuleProc, "DeleteComp() must resolve to a component assignment property or 'Action'." );
   else if (op == BF_DelComp && (nArgs < 0 || nArgs > 2))
      ExpSetErr( error, EXP_RuleProc, "DeleteComp() must have between 0 and 2 arguments." );

   else if (op == BF_DelAllComps && (iDataType != BEMP_Str || iPropType != 0 || iArrayIdx != BEM_PARAM0_ACTION))
      ExpSetErr( error, EXP_RuleProc, "DeleteAllComps() must resolve to a *:Action property." );
   else if (op == BF_DelAllComps && (nArgs < 1 || nArgs > 3))
      ExpSetErr( error, EXP_RuleProc, "DeleteAllComps() must have between 1 and 3 arguments." );

   else
      return TRUE;

   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  CreateChildrenOrComp()
//
// Purpose ------------------------------------------------------------------
//   Create child or other building component(s)
//      (via CreateChildren() and CreateComp() functions)
//   
/////////////////////////////////////////////////////////////////////////////
static void CreateChildrenOrComp( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{	QString sErrMsg;
   // BF_Cr8Child  =>  "CreateChildren" => 3-5 arguments, CompType, Num, NamePrefix, <Rulelist>, <EvalOption>
   // BF_Cr8Comp   =>  "CreateComp",    => 2-5 arguments, CompType,      NamePrefix, <Rulelist>, <EvalOption>, <Name of Object to Copy>

   // Pop, store and delete first node
   ExpNode* pNode = ExpxStackPop( stack );

	// SAC 11/19/14 - added code to parse new 5th CreateComp argument
	QString sObjToCopyName;
	BEMObject* pObjToCopy = NULL;
	if (op == BF_Cr8Comp && nArgs > 4)
	{	if (pNode->type != EXP_String)
			ExpSetErr( error, EXP_RuleProc, "Invalid CreateComp() 5th argument (name of object to copy)" );
		else // post rulelist name to the eval struct
			sObjToCopyName = (char*) pNode->pValue;
		ExpxNodeDelete( pNode );
		pNode = ExpxStackPop( stack );
	}

   // SAC 5/26/00 - added code to parse new (optional) EvalOption argument
   int iEvalOption = 1;  // default EvalOption is to evaluate the rulelist for only the newly created components
   if ( (op == BF_Cr8Child  &&  nArgs > 4) ||
        (op == BF_Cr8Comp   &&  nArgs > 3) )
   {
      if (pNode->type != EXP_Value || pNode->fValue < 0 || pNode->fValue > 1)
      {
         if (op == BF_Cr8Child)
               ExpSetErr( error, EXP_RuleProc, "Optional 5th CreateChildren() argument must be EvalOption (0 or 1)" );
         else  ExpSetErr( error, EXP_RuleProc, "Optional 4th CreateComp() argument must be EvalOption (0 or 1)" );
      }
      else // post rulelist name to the eval struct
         iEvalOption = (int) pNode->fValue;
      ExpxNodeDelete( pNode );
      pNode = ExpxStackPop( stack );
   }

   assert( pEval->sRulelistToEvaluate.length() < 1 );
   // SAC 5/26/00 - added code to enable RuleList argument to be optional (as opposed to required)
   if ( (op == BF_Cr8Child  &&  nArgs > 3) ||
        (op == BF_Cr8Comp   &&  nArgs > 2) )
   {
      if (pNode->type != EXP_String)
      {
         if (op == BF_Cr8Child)
               ExpSetErr( error, EXP_RuleProc, "Invalid CreateChildren() 4th argument (Rulelist Name)" );
         else  ExpSetErr( error, EXP_RuleProc, "Invalid CreateComp() 3rd argument (Rulelist Name)" );
      }
      else // post rulelist name to the eval struct
         pEval->sRulelistToEvaluate = (char*) pNode->pValue;
      ExpxNodeDelete( pNode );
      pNode = ExpxStackPop( stack );
   }

   // Pop, store and delete NamePrefix node
   QString sNamePrefix;
   if (pNode->type != EXP_String)
   {
      if (op == BF_Cr8Child)
            ExpSetErr( error, EXP_RuleProc, "Invalid CreateChildren() 3rd argument" );
      else  ExpSetErr( error, EXP_RuleProc, "Invalid CreateComp() 2nd argument" );
   }
   else
      sNamePrefix = (char*) pNode->pValue;
   ExpxNodeDelete( pNode );

   int iNumComps = 1;
   if (op == BF_Cr8Child)
   {  // Pop, store and delete NumChildren node
      pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
         ExpSetErr( error, EXP_RuleProc, "Invalid CreateChildren() 2nd argument" );
      else
         iNumComps = (int) pNode->fValue;
      ExpxNodeDelete( pNode );
   }

   // Pop and store CompType node
   QString sCompName;
   BOOL bSuccess = FALSE;
   pNode = ExpxStackPop( stack );
   if (pNode->type != EXP_Value)
   {
      if (op == BF_Cr8Child)
            ExpSetErr( error, EXP_RuleProc, "Invalid CreateChildren() 1st argument" );
      else  ExpSetErr( error, EXP_RuleProc, "Invalid CreateComp() 1st argument" );
   }
   else
   {  // Perform component creation
      int i1Cr8Class    = (int) pNode->fValue;
      int i1ParentClass = BEMPX_GetClassID( pEval->lPrimDBID );

		if (op == BF_Cr8Comp && !sObjToCopyName.isEmpty())
			// get pointer to object to copy
			pObjToCopy = BEMPX_GetComponentByNameQ( sObjToCopyName, FALSE /*bCheckLibsOnly*/, -1 /*iBEMProcIdx*/, TRUE /*bSkipCheckingRuleLib*/ );
		if (op == BF_Cr8Comp && !sObjToCopyName.isEmpty() && pObjToCopy == NULL)
		{	sErrMsg = QString( "Unable to find object to copy '%1', identified by 5th argument of CreateComp()" ).arg( sObjToCopyName );
			ExpSetErr( error, EXP_RuleProc, sErrMsg );
		}
		else
		{	int iError = 0;
	      BEMObject* pParentObj = NULL;
	      // Final error checking
	      if (op == BF_Cr8Child)
	      {
	         // grab ptr to parent object and ensure it is valid and that we can create the children
	         pParentObj = BEMPX_GetObjectByClass( i1ParentClass, iError, pEval->iPrimObjIdx, pEval->ePrimObjType );

	         if (iError < 0 || pParentObj == NULL)
	            ExpSetErr( error, EXP_RuleProc, "CreateChildren() Error:  Unable to retrieve parent component" );
	         else
	         {
	            bSuccess = BEMPX_CanCreateAnotherChildObject( i1Cr8Class, pParentObj, iNumComps );
	            if (!bSuccess)
	               ExpSetErr( error, EXP_RuleProc, "CreateChildren() Error:  Cannot create child component(s)" );
	         }
	      }
	      else // (op == BF_Cr8Comp)
	      {
	         bSuccess = BEMPX_CanCreateAnotherUserObject( i1Cr8Class, iNumComps );
	         if (!bSuccess)
	            ExpSetErr( error, EXP_RuleProc, "CreateComp() Error:  Cannot create component(s)" );
	         else
	         {  // SAC 5/27/00 - added following code to cause newly created component's Parent to get set to the primary component
	            //               in the event the primary component's class is in the new component's parent list
	            BEMClass* pCr8Class = BEMPX_GetClass( i1Cr8Class, iError );
	            if (pCr8Class  &&  pCr8Class->ClassInParentList( (int) i1ParentClass ))
	               pParentObj = BEMPX_GetObjectByClass( i1ParentClass, iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
	         }
	      }

	      // if final error checking passed, then create the components
	      if (bSuccess)
	      {
	         int iFirstNewObjIdx = BEMPX_GetNumObjects( i1Cr8Class, BEMO_User );
	         for (int i=0; (bSuccess && i<iNumComps); i++)
	         {
	            sCompName = sNamePrefix;
	            if (BEMPX_GetDefaultComponentName( i1Cr8Class, sCompName ))
	            {
	               BEMObject* pNewObj = BEMPX_CreateObject( i1Cr8Class, sCompName.toLocal8Bit().constData(), pParentObj, BEMO_User, FALSE );
	               if (pNewObj == NULL)
	               {
	                  bSuccess = FALSE;
	                  if (op == BF_Cr8Child)
	                        ExpSetErr( error, EXP_RuleProc, "CreateChildren() Error:  Component creation failed" );
	                  else  ExpSetErr( error, EXP_RuleProc, "CreateComp() Error:  Component creation failed" );
	               }
	               else if (op == BF_Cr8Comp && pObjToCopy && !BEMPX_CopyComponent( pNewObj, pObjToCopy, -1 /*iBEMProcIdx*/ ))
						{	sErrMsg = QString( "Copy of object '%1' (identified by 5th argument of CreateComp()) to newly created object '%2' Failed." ).arg( sObjToCopyName, sCompName );
							ExpSetErr( error, EXP_RuleProc, sErrMsg );
						}
	               // SAC 5/26/00 - added code to implement new EvalOption argument
	               else if (pEval->sRulelistToEvaluate.length() > 0 && iEvalOption == 1)
	               {
	                  pEval->iRulelistEvalClass = i1Cr8Class;
	                  pEval->eRulelistEvalObjType = BEMO_User;
	                  pEval->maRulelistEvalObjIdxs.push_back( (iFirstNewObjIdx+i) );
	               }
	            }
	            else
	               bSuccess = FALSE;
	         }
			}
      }
   }

   // setup result node
   if (bSuccess)
   {  // setup node to return the name of the last component created
      // this name will be used to set an assigned component depending on the rule's left side
#pragma warning(disable : 4996)		// SAC 9/9/16
      pNode->type = EXP_String;
      pNode->pValue = malloc( sCompName.length() + 1 );
      strcpy( (char*) pNode->pValue, (const char*) sCompName.toLocal8Bit().constData() );
#pragma warning(default : 4996)
   }
   else
      pNode->type = EXP_Invalid;

   // Push result node onto stack
   ExpxStackPush( stack, pNode );
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  DeleteChildrenCompOrAll()
//
// Purpose ------------------------------------------------------------------
//   Delete children, assigned or all building component(s)
//      (via the DeleteChildren(), DeleteComp() & DeleteAllComps() functions)
//   
/////////////////////////////////////////////////////////////////////////////

static char* pszDelError0[] = {  "Invalid DeleteChildren() 3rd argument (EvalOption)", 
                                 "Invalid DeleteComp() 2nd argument (EvalOption)", 
                                 "Invalid DeleteAllComps() 3rd argument (EvalOption)" };
static char* pszDelError1[] = {  "Invalid DeleteChildren() 2nd argument (RuleList Name)", 
                                 "Invalid DeleteComp() 1st argument (RuleList Name)", 
                                 "Invalid DeleteAllComps() 2nd argument (RuleList Name)" };
static char* pszDelError2[] = {  "Invalid DeleteChildren() 1st argument (Child Component Type)", 
                                 "unknown", 
                                 "Invalid DeleteAllComps() 1st argument (Component Type)" };
static char* pszDelError3[] = {  "DeleteChildren() Error:  Unable to find child component", 
                                 "DeleteComp() Error:  Unable to find component", 
                                 "DeleteAllComps() Error:  Unable to find component" };
static char* pszDelError4[] = {  "DeleteChildren() Error:  Unable to delete child component",
                                 "DeleteComp() Error:  Unable to delete component",
                                 "DeleteAllComps() Error:  Unable to delete component" };

static void DeleteChildrenCompOrAll( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
   // BF_DelChild    =>  "DeleteChildren" => SAC 5/26/00 - switched from 2 fixed to variable (1-3) args:  ChildCompType, <Rulelist>, <EvalOption>
   // BF_DelComp     =>  "DeleteComp"     => SAC 5/26/00 - switched from 1 fixed to variable (0-2) args:                 <Rulelist>, <EvalOption>
   // BF_DelAllComps =>  "DeleteAllComps" => SAC 5/26/00 - switched from 2 fixed to variable (1-3) args:  CompType,      <Rulelist>, <EvalOption>

   int iErrFuncIdx = (op == BF_DelChild ? 0 : (op == BF_DelComp ? 1 : 2));
   BOOL bSuccess = TRUE;

   // default EvalOption => evaluate rulelist for ALL components if func = DeleteAllComps(),
   //                       evaluate rulelist for only the leftmost component if func = DeleteComp() or DeleteChildren()
   int iEvalOption = (op == BF_DelAllComps ? 0 : 1);

   ExpNode* pNode = NULL;
   // Pop and store Rulelist node and then free 
   // SAC 5/26/00 - added code to pop and store new EvalOption argument
   if ( (op == BF_DelChild    && nArgs > 2) ||
        (op == BF_DelComp     && nArgs > 1) ||
        (op == BF_DelAllComps && nArgs > 2) )
   {
      pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value || pNode->fValue < 0 || pNode->fValue > 1)
      {
         ExpSetErr( error, EXP_RuleProc, pszDelError0[iErrFuncIdx] );
         bSuccess = FALSE;
      }
      else // post rulelist name to the eval struct
         iEvalOption = (int) pNode->fValue;
      ExpxNodeDelete( pNode );
   }

   // SAC 5/26/00 - added code to enable RuleList Name argument to be optional
   if ( (op == BF_DelChild    && nArgs > 1) ||
        (op == BF_DelComp     && nArgs > 0) ||
        (op == BF_DelAllComps && nArgs > 1) )
   {
      pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_String)
      {
         ExpSetErr( error, EXP_RuleProc, pszDelError1[iErrFuncIdx] );
         bSuccess = FALSE;
      }
      else // post rulelist name to the eval struct
         pEval->sRulelistToEvaluate = (char*) pNode->pValue;
      ExpxNodeDelete( pNode );
   }

   // Pop, store and delete CompType node for certain functions only
   int i1DelClass = 0;
   if (op == BF_DelChild || op == BF_DelAllComps)
   {
      pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
      {
         ExpSetErr( error, EXP_RuleProc, pszDelError2[iErrFuncIdx] );
         bSuccess = FALSE;
      }
      else
         i1DelClass = (int) pNode->fValue;
      ExpxNodeDelete( pNode );
   }
   else // op == BF_DelComp
   {
      int iGPTError;
      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( pEval->lPrimDBID, iGPTError );
      if (iGPTError == 0 && pPropType)
      {
         assert( pPropType->getPropType() == BEMP_Obj );
         i1DelClass = pPropType->getObj1ClassIdx(0);  // SAC 6/13/12 - only first of possibly several comptible class idxs set here - will get reset later once we dientify the individual object beign deleted
      }
		// SAC 2/5/06 - if property being set is "Action", then delete the "active" component
      else if (BEMPX_GetPropertyID( pEval->lPrimDBID ) == 0 && BEMPX_GetArrayID( pEval->lLocDBID ) == BEM_PARAM0_ACTION)
         i1DelClass = BEMPX_GetClassID( pEval->lPrimDBID );
   }

   if (i1DelClass <= 0)
      bSuccess = FALSE;

   // proceed w/ processing if no argument errors found
   int iNumDeleted = 0;
   if (bSuccess)
   {
      int iNumComps = 1;  // will be already setup for BF_DelComp
      int i1ParentClass = 0;

      if (op == BF_DelChild)
      {  // load number of child components of this type
         i1ParentClass = BEMPX_GetClassID( pEval->lPrimDBID );
         iNumComps = (int) BEMPX_GetNumChildren( i1ParentClass, pEval->iPrimObjIdx, pEval->ePrimObjType, i1DelClass );
      }
      else if (op == BF_DelAllComps)
         // load total number of components of this type
         iNumComps = BEMPX_GetNumObjects( i1DelClass );

      // Perform component deletion
      int iError = 0;
      BEM_ObjType eDelCompType = BEMO_User;
      int iDelCompIdx=-1;
      BEMObject* pDelComp;
      for (int i1DelComp=iNumComps; (bSuccess && i1DelComp>=1); i1DelComp--)
      {
         bSuccess = FALSE;
         // Set iDelCompIdx & eDelCompType
         if (op == BF_DelChild)
            iDelCompIdx = BEMPX_GetChildObjectIndex( i1ParentClass, i1DelClass, iError, eDelCompType,
                                                   i1DelComp, pEval->iPrimObjIdx, pEval->ePrimObjType );
         else if (op == BF_DelComp)
         {  // object to delete is the one which is currently assigned to the property being set by this rule
            int iGetSV, iGetError = 0, iStatus = 0;
      //      void* pData = (void*) BEMPX_GetData( pEval->lPrimDBID, iGetDT, iGetSV, iGetError,
      //                                           pEval->iPrimObjIdx, pEval->ePrimObjType );
				BEMObject* pObj = BEMPX_GetObjectAndStatus( pEval->lPrimDBID, iStatus, iGetSV, iGetError, 
																				pEval->iPrimObjIdx, pEval->ePrimObjType );
            if (iGetError >= 0 && iStatus > 0 && pObj)
				{	assert( pObj->getClass() );
		         i1DelClass = pObj->getClass()->get1BEMClassIdx();  // SAC 6/13/12 - RESET i1DelClass to point to the single, correct class index (to begin with set to only first of potentially several class idxs)
               iDelCompIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1DelClass, iGetError ), pObj );
				}
				// SAC 2/5/06 - if property being set is "Action", then delete the "active" component
            else if (BEMPX_GetPropertyID( pEval->lPrimDBID ) == 0 && BEMPX_GetArrayID( pEval->lLocDBID ) == BEM_PARAM0_ACTION)
               iDelCompIdx = pEval->iPrimObjIdx;
            else
               iDelCompIdx = -1;
         }
         else if (op == BF_DelAllComps)
            iDelCompIdx = i1DelComp-1;

         if (iDelCompIdx < 0)
            ExpSetErr( error, EXP_RuleProc, pszDelError3[iErrFuncIdx] );
         else
         {
            pDelComp = BEMPX_GetObjectByClass( i1DelClass, iError, iDelCompIdx, eDelCompType );
            if (iError < 0 || pDelComp == NULL)
               ExpSetErr( error, EXP_RuleProc, pszDelError4[iErrFuncIdx] );
            else
            {
               BEMPX_DeleteObject( pDelComp );
               iNumDeleted++;
               bSuccess = TRUE;
					// SAC 2/5/06 - Added members to keep track of components deleted during evaluation of the current rule
               pEval->maDeletedClassIDs.push_back( i1DelClass  );
               pEval->maDeletedObjIdxs.push_back(  iDelCompIdx );
            }
         }
      }
		//assert( iNumComps == iNumDeleted );
   }

   // SAC 5/26/00 - Create node to serve as result
   pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );

   // setup result node
   if (bSuccess)
   {
      if (op == BF_DelChild || op == BF_DelAllComps)
      {  // setup node to return the number of children which have been deleted
         pNode->type = EXP_Value;
         pNode->fValue = (double) iNumDeleted;
      }
      else  // op == BF_DelComp
      {  // setup node to return the character string "NONE"
         pNode->type = EXP_String;
#pragma warning(disable : 4996)		// SAC 9/9/16
         pNode->pValue = malloc( 5 );
         strcpy( (char*) pNode->pValue, "NONE" );
#pragma warning(default : 4996)
      }

      // SAC 5/26/00 - added code to implement EvalOption argument
      assert( pEval->maRulelistEvalObjIdxs.size() < 1 );
      if (iEvalOption == 1  &&  pEval->sRulelistToEvaluate.length() > 0)
         pEval->maRulelistEvalObjIdxs.push_back( pEval->iPrimObjIdx );
   }
   else
      pNode->type = EXP_Invalid;

   // Push result node onto stack
   ExpxStackPush( stack, pNode );
}

/////////////////////////////////////////////////////////////////////////////

// SAC 11/14/16 - first argument string indicating special processing 
int AddCSEReportColumn( int nArgs, ExpStack* stack, QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error )
{
	int iRetVal = 0;
	ExpNode* pNode2 = ExpxStackPop( stack );				assert( pNode2 );
	ExpNode* pNode1 = ExpxStackPop( stack );				assert( pNode1 );
	QString sProcOption, sRptColData;
	long lDBID_RptColRef=0;
	if (pNode1->type != EXP_String)
		sErrMsg = QString( "Invalid AddCSEReportColumn() argument #1 (processing option) - should be character string." );
	else
	{	sProcOption = (char*) pNode1->pValue;
		if (pNode2->type == EXP_Value)
			lDBID_RptColRef = (long) pNode2->fValue;	// DBID of cseREPORTCOL property that will store a reference to the adjacent object
		else
			sRptColData = (char*) pNode2->pValue;
	}
	ExpxNodeDelete( pNode1 );
	ExpxNodeDelete( pNode2 );

	long lDBID_RptColVal = BEMPX_GetDatabaseID( "cseREPORTCOL:colVal_x" );		assert( lDBID_RptColVal > BEM_COMP_MULT );
	if (lDBID_RptColVal < BEM_COMP_MULT)
		sErrMsg = QString( "Database ID of cseREPORTCOL:colVal_x invalid." );

	BEMObject* pRptColObj;
	int iError, iSpecVal, iRptColClass = BEMPX_GetClassID( lDBID_RptColVal );
	if (!sErrMsg.isEmpty())
	{	// do nothing
	}
	else if (!sProcOption.compare( "none", Qt::CaseInsensitive ))
	{	QString sRColName = QString( "rcol %1" ).arg( BEMPX_GetNumObjects( iRptColClass )+1 );
		pRptColObj = BEMPX_CreateObject( iRptColClass, sRColName.toLocal8Bit().constData(), NULL /*parent*/ );
		if (pRptColObj == NULL)
			sErrMsg = QString( "Unable to create cseREPORTCOL object." );
		else
		{	iRetVal++;
			if (sRptColData.isEmpty() || BEMPX_SetBEMData( lDBID_RptColVal, BEMP_QStr, (void*) &sRptColData, BEMO_User, -1 /*iOccur*/ ) < 0)
				sErrMsg = QString( "Unable to set cseREPORTCOL:colVal_x = '%1'." ).arg( sRptColData );
		}
	}
	else if (!sProcOption.compare( "AdjacentAttics",  Qt::CaseInsensitive ))
	{	// only connection between Zone and Attic can be via CeilingBelowAttic or IntWall objects - and both must be children of the Zone
		int iZnClsID    = BEMPX_GetClassID( pEval->lPrimDBID );					assert( iZnClsID > 0 );  
		int iAtticClsID = BEMPX_GetDBComponentID( "Attic" );						assert( iAtticClsID > 0 );
		if (iZnClsID != BEMPX_GetDBComponentID( "Zone" ))
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentAttics' option for rule where primary object type not 'Zone'." );
		else if (lDBID_RptColRef < BEM_COMP_MULT)
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentAttics' option due to invalid attic reference database ID (2nd argument)." );
		else if (BEMPX_GetNumObjects( iAtticClsID ) < 1)
		{	// do nothing - no need to do any processing here if no Attic objects exist
		}
		else
		{	std::vector<int> ivAtticIdxs;
			int iChldClsID[]     = {  BEMPX_GetDBComponentID( "CeilingBelowAttic" ),      BEMPX_GetDBComponentID( "IntWall" )  };					assert( iChldClsID[   0] > 0 && iChldClsID[   1] > 0 );
			long lChldAreaDBID[] = {  BEMPX_GetDatabaseID( "Area"     , iChldClsID[0] ),  BEMPX_GetDatabaseID( "Area"   , iChldClsID[1] )  };	assert( lChldAreaDBID[0] > 0 && lChldAreaDBID[1] > 0 );
			long lChldAdjDBID[]  = {  BEMPX_GetDatabaseID( "AtticZone", iChldClsID[0] ),  BEMPX_GetDatabaseID( "Outside", iChldClsID[1] )  };	assert( lChldAdjDBID[ 0] > 0 && lChldAdjDBID[ 1] > 0 );
			double dSurfArea;
			for (int iChldTyp=0; (sErrMsg.isEmpty() && iChldTyp < 2); iChldTyp++)
			{	int iNumChldren = (int) BEMPX_GetNumChildren( iZnClsID, pEval->iPrimObjIdx, BEMO_User, iChldClsID[iChldTyp] );
				BEM_ObjType eChildObjType = BEMO_User;
				for (int iChldIdx=0; (sErrMsg.isEmpty() && iChldIdx < iNumChldren); iChldIdx++)
				{	int iChldObjIdx = BEMPX_GetChildObjectIndex( iZnClsID, iChldClsID[iChldTyp], iError,
                                                            eChildObjType, iChldIdx+1, pEval->iPrimObjIdx );		assert( iChldObjIdx >= 0 );
            	if (iChldObjIdx >= 0 && BEMPX_GetFloat( lChldAreaDBID[iChldTyp], dSurfArea, 0, -1, iChldObjIdx ) &&
            			dSurfArea > 0.1)
            	{	// we have a Zone child surface w/ non-zero Area that MAY be adjacent to an Attic
            		bool bChkSurface = true;
            		if (iChldTyp == 1)
            		{	// ADDITIONAL checking needed for IntWall objects, to confirm that this surface is to be simulated between two modeled zones
							long lIsPartySurf, lOtherSideMod;
							if ( (BEMPX_GetInteger( BEMPX_GetDatabaseID( "IsPartySurface"  , iChldClsID[iChldTyp] ), lIsPartySurf , 0, -1,	iChldObjIdx ) && lIsPartySurf  < 0.5) ||
								  (BEMPX_GetInteger( BEMPX_GetDatabaseID( "OtherSideModeled", iChldClsID[iChldTyp] ), lOtherSideMod, 0, -1,	iChldObjIdx ) && lOtherSideMod > 0.5) )
							{ }	// this surface SHOULD be checked...
							else
								bChkSurface = false;
						}
						if (bChkSurface)
						{	BEMObject* pAdjObj = BEMPX_GetObjectPtr( lChldAdjDBID[iChldTyp], iSpecVal, iError, iChldObjIdx );
							if (pAdjObj && pAdjObj->getClass() && pAdjObj->getClass()->get1BEMClassIdx() == iAtticClsID)
							{	int iAtticObjIdx = BEMPX_GetObjectIndex( pAdjObj->getClass(), pAdjObj );
								if (std::find( ivAtticIdxs.begin(), ivAtticIdxs.end(), iAtticObjIdx ) == ivAtticIdxs.end())
									// this object index NOT yet included in vector of 
									ivAtticIdxs.push_back( iAtticObjIdx );
						}	}
					}
				}	// end of for each child of type iChldTyp
			}	// end of for each iChldTyp

			long lAtticCSEZnRefDBID = BEMPX_GetDatabaseID( "CSE_ZONE", iAtticClsID );												assert( lAtticCSEZnRefDBID > 0 );
			long lAtticNameDBID     = BEMPX_GetDatabaseID( "Name"    , iAtticClsID );												assert( lAtticNameDBID > 0 );
			for (int iAdjObj=0; (sErrMsg.isEmpty() && iAdjObj < (int) ivAtticIdxs.size()); iAdjObj++)
			{	QString sAdjZnName = BEMPX_GetString( lAtticCSEZnRefDBID, iSpecVal, iError, ivAtticIdxs[iAdjObj] );		assert( !sAdjZnName.isEmpty() );
				QString sAtticName = BEMPX_GetString( lAtticNameDBID    , iSpecVal, iError, ivAtticIdxs[iAdjObj] );		assert( !sAtticName.isEmpty() );
				if (!sAdjZnName.isEmpty() && !sAtticName.isEmpty())
				{
				// create and setup cseREPORTCOL object
					QString sRColName = QString( "rcol %1" ).arg( BEMPX_GetNumObjects( iRptColClass )+1 );
					pRptColObj = BEMPX_CreateObject( iRptColClass, sRColName.toLocal8Bit().constData(), NULL /*parent*/ );
					if (pRptColObj == NULL)
						sErrMsg = QString( "Unable to create cseREPORTCOL object (to report Attic '%1' data)." ).arg( sAdjZnName );
					else
					{	iRetVal++;
						if (BEMPX_SetBEMData( lDBID_RptColRef, BEMP_QStr, (void*) &sAtticName, BEMO_User, -1 /*iOccur*/ ) < 0)
							sErrMsg = QString( "Unable to set cseREPORTCOL:<AtticObjRef> = '%1' (DBID = %2)." ).arg( sAtticName, QString::number( lDBID_RptColRef ) );
					}
			}	}
		}
	}
	else if (!sProcOption.compare( "AdjacentGarages", Qt::CaseInsensitive ))
	{	// connections between Zone and Garage can be via IntWall, InteriorFloor & InteriorCeiling objects - and most can be children of EITHER the Zone or Garage
		int iZnClsID = BEMPX_GetClassID( pEval->lPrimDBID );					assert( iZnClsID > 0 );  
		int iGarageClsID = BEMPX_GetDBComponentID( "Garage" );				assert( iGarageClsID > 0 );
		if (iZnClsID != BEMPX_GetDBComponentID( "Zone" ))
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentGarages' option for rule where primary object type not 'Zone'." );
		else if (lDBID_RptColRef < BEM_COMP_MULT)
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentGarages' option due to invalid garage reference database ID (2nd argument)." );
		else if (BEMPX_GetNumObjects( iGarageClsID ) < 1)
		{	// do nothing - no need to do any processing here if no Garage objects exist
		}
		else
		{	std::vector<int> ivGarageIdxs;
			int iParentClsID[]   = {  iZnClsID,  iGarageClsID  };
			int iChldClsID[]     = {  BEMPX_GetDBComponentID( "IntWall" )            ,  BEMPX_GetDBComponentID( "InteriorFloor" )      ,  BEMPX_GetDBComponentID( "InteriorCeiling" )      };	assert( iChldClsID[   0] > 0 && iChldClsID[   1] > 0 && iChldClsID[   2] > 0 );
			long lChldAreaDBID[] = {  BEMPX_GetDatabaseID( "Area"   , iChldClsID[0] ),  BEMPX_GetDatabaseID( "Area"   , iChldClsID[1] ),  BEMPX_GetDatabaseID( "Area"   , iChldClsID[2] )  };	assert( lChldAreaDBID[0] > 0 && lChldAreaDBID[1] > 0 && lChldAreaDBID[2] > 0 );
			long lChldAdjDBID[]  = {  BEMPX_GetDatabaseID( "Outside", iChldClsID[0] ),  BEMPX_GetDatabaseID( "Outside", iChldClsID[1] ),  BEMPX_GetDatabaseID( "Outside", iChldClsID[2] )  };	assert( lChldAdjDBID[ 0] > 0 && lChldAdjDBID[ 1] > 0 && lChldAdjDBID[ 2] > 0 );
			double dSurfArea;
			for (int iParTyp=0; (sErrMsg.isEmpty() && iParTyp < 2); iParTyp++)
			{	int iFirstParObj = (iParTyp==0 ? pEval->iPrimObjIdx : 0 );
				int iLastParObj  = (iParTyp==0 ? pEval->iPrimObjIdx : BEMPX_GetNumObjects( iGarageClsID )-1 );
				for (int iParObjIdx = iFirstParObj; (sErrMsg.isEmpty() && iParObjIdx <= iLastParObj); iParObjIdx++)
				{
					for (int iChldTyp=0; (sErrMsg.isEmpty() && iChldTyp < 3); iChldTyp++)
					{	int iNumChldren = (int) BEMPX_GetNumChildren( iParentClsID[iParTyp], iParObjIdx, BEMO_User, iChldClsID[iChldTyp] );
						BEM_ObjType eChildObjType = BEMO_User;
						for (int iChldIdx=0; (sErrMsg.isEmpty() && iChldIdx < iNumChldren); iChldIdx++)
						{	int iChldObjIdx = BEMPX_GetChildObjectIndex( iParentClsID[iParTyp], iChldClsID[iChldTyp], iError,
		                                                            eChildObjType, iChldIdx+1, iParObjIdx );													assert( iChldObjIdx >= 0 );
		            	if (iChldObjIdx >= 0 && BEMPX_GetFloat( lChldAreaDBID[iChldTyp], dSurfArea, 0, -1, iChldObjIdx ) && dSurfArea > 0.1)
		            	{	// we have a child surface w/ non-zero Area that MAY be fall between a Zone & Garage
		            		bool bChkSurface = true;
		            		if (iChldTyp >= 0) // check applies to ALL of these child types...
		            		{	// ADDITIONAL checking needed for IntWall objects, to confirm that this surface is to be simulated between two modeled zones
									long lIsPartySurf, lOtherSideMod;
									if ( (BEMPX_GetInteger( BEMPX_GetDatabaseID( "IsPartySurface"  , iChldClsID[iChldTyp] ), lIsPartySurf , 0, -1,	iChldObjIdx ) && lIsPartySurf  < 0.5) ||
										  (BEMPX_GetInteger( BEMPX_GetDatabaseID( "OtherSideModeled", iChldClsID[iChldTyp] ), lOtherSideMod, 0, -1,	iChldObjIdx ) && lOtherSideMod > 0.5) )
									{ }	// this surface SHOULD be checked...
									else
										bChkSurface = false;
								}
								if (bChkSurface)
								{	BEMObject* pAdjObj = BEMPX_GetObjectPtr( lChldAdjDBID[iChldTyp], iSpecVal, iError, iChldObjIdx );
									int iAdjObjIdx = (pAdjObj && pAdjObj->getClass()) ? BEMPX_GetObjectIndex( pAdjObj->getClass(), pAdjObj ) : -1;
									if (pAdjObj && pAdjObj->getClass() && ( (iParTyp == 0 && pAdjObj->getClass()->get1BEMClassIdx() == iGarageClsID) ||
																						 (iParTyp == 1 && pAdjObj->getClass()->get1BEMClassIdx() == iGarageClsID &&
																						                  iAdjObjIdx == pEval->iPrimObjIdx) ))
									{	int iGarageObjIdx = (iParTyp == 0 ? iAdjObjIdx : iChldObjIdx);
										if (std::find( ivGarageIdxs.begin(), ivGarageIdxs.end(), iGarageObjIdx ) == ivGarageIdxs.end())
											// this object index NOT yet included in vector of 
											ivGarageIdxs.push_back( iGarageObjIdx );
								}	}
							}
						}	// end of for each child of type iChldTyp
					}	// end of for each iChldTyp
				}	// end of for each parent object of type iParTyp
			}	// end of for each iParTyp

			long lGarageCSEZnRefDBID = BEMPX_GetDatabaseID( "CSE_ZONE", iGarageClsID );												assert( lGarageCSEZnRefDBID > 0 );
			long lGarageNameDBID     = BEMPX_GetDatabaseID( "Name"    , iGarageClsID );												assert( lGarageNameDBID > 0 );
			for (int iAdjObj=0; (sErrMsg.isEmpty() && iAdjObj < (int) ivGarageIdxs.size()); iAdjObj++)
			{	QString sAdjZnName  = BEMPX_GetString( lGarageCSEZnRefDBID, iSpecVal, iError, ivGarageIdxs[iAdjObj] );		assert( !sAdjZnName.isEmpty() );
				QString sGarageName = BEMPX_GetString( lGarageNameDBID    , iSpecVal, iError, ivGarageIdxs[iAdjObj] );		assert( !sGarageName.isEmpty() );
				if (!sAdjZnName.isEmpty() && !sGarageName.isEmpty())
				{
				// create and setup cseREPORTCOL object
					QString sRColName = QString( "rcol %1" ).arg( BEMPX_GetNumObjects( iRptColClass )+1 );
					pRptColObj = BEMPX_CreateObject( iRptColClass, sRColName.toLocal8Bit().constData(), NULL /*parent*/ );
					if (pRptColObj == NULL)
						sErrMsg = QString( "Unable to create cseREPORTCOL object (to report Garage '%1' data)." ).arg( sAdjZnName );
					else
					{	iRetVal++;
						if (BEMPX_SetBEMData( lDBID_RptColRef, BEMP_QStr, (void*) &sGarageName, BEMO_User, -1 /*iOccur*/ ) < 0)
							sErrMsg = QString( "Unable to set cseREPORTCOL:<GarageObjRef> = '%1' (DBID = %2)." ).arg( sGarageName, QString::number( lDBID_RptColRef ) );
					}
			}	}
		}
	}
	else if (!sProcOption.compare( "AdjacentCrlSpcs", Qt::CaseInsensitive ))
	{	// only connection between Zone and CrawlSpace can be via FloorOverCrawl objects - and they must be children of the Zone
		int iZnClsID    = BEMPX_GetClassID( pEval->lPrimDBID );					assert( iZnClsID > 0 );  
		int iCrlSpcClsID = BEMPX_GetDBComponentID( "CrawlSpace" );						assert( iCrlSpcClsID > 0 );
		if (iZnClsID != BEMPX_GetDBComponentID( "Zone" ))
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentCrlSpcs' option for rule where primary object type not 'Zone'." );
		else if (lDBID_RptColRef < BEM_COMP_MULT)
			sErrMsg = QString( "Cannot process AddCSEReportCol() 'AdjacentCrlSpcs' option due to invalid crawl space reference database ID (2nd argument)." );
		else if (BEMPX_GetNumObjects( iCrlSpcClsID ) < 1)
		{	// do nothing - no need to do any processing here if no CrawlSpace objects exist
		}
		else
		{	std::vector<int> ivCrlSpcIdxs;
			int iChldClsID[]     = {  BEMPX_GetDBComponentID( "FloorOverCrawl" )         };		assert( iChldClsID[   0] > 0 );
			long lChldAreaDBID[] = {  BEMPX_GetDatabaseID( "Area"     , iChldClsID[0] )  };		assert( lChldAreaDBID[0] > 0 );
		//	long lChldAdjDBID[]  = {  BEMPX_GetDatabaseID( "AtticZone", iChldClsID[0] )  };		assert( lChldAdjDBID[ 0] > 0 );
			double dSurfArea;
			for (int iChldTyp=0; (sErrMsg.isEmpty() && iChldTyp < 1); iChldTyp++)
			{	int iNumChldren = (int) BEMPX_GetNumChildren( iZnClsID, pEval->iPrimObjIdx, BEMO_User, iChldClsID[iChldTyp] );
				BEM_ObjType eChildObjType = BEMO_User;
				for (int iChldIdx=0; (sErrMsg.isEmpty() && iChldIdx < iNumChldren); iChldIdx++)
				{	int iChldObjIdx = BEMPX_GetChildObjectIndex( iZnClsID, iChldClsID[iChldTyp], iError,
                                                            eChildObjType, iChldIdx+1, pEval->iPrimObjIdx );				assert( iChldObjIdx >= 0 );
            	if (iChldObjIdx >= 0 && BEMPX_GetFloat( lChldAreaDBID[iChldTyp], dSurfArea, 0, -1, iChldObjIdx ) && dSurfArea > 0.1)
            	{	// we have a Zone child surface w/ non-zero Area that MAY be adjacent to a CrawlSpace
            					assert( BEMPX_GetClassMaxDefinable( iCrlSpcClsID ) < 2 );
            		int iCrlSpcObjIdx = 0;
						if (std::find( ivCrlSpcIdxs.begin(), ivCrlSpcIdxs.end(), iCrlSpcObjIdx ) == ivCrlSpcIdxs.end())
							// this object index NOT yet included in vector of 
							ivCrlSpcIdxs.push_back( iCrlSpcObjIdx );
					}
				}	// end of for each child of type iChldTyp
			}	// end of for each iChldTyp

			long lCrlSpcCSEZnRefDBID = BEMPX_GetDatabaseID( "CSE_ZONE", iCrlSpcClsID );												assert( lCrlSpcCSEZnRefDBID > 0 );
			long lCrlSpcNameDBID     = BEMPX_GetDatabaseID( "Name"    , iCrlSpcClsID );												assert( lCrlSpcNameDBID > 0 );
			for (int iAdjObj=0; (sErrMsg.isEmpty() && iAdjObj < (int) ivCrlSpcIdxs.size()); iAdjObj++)
			{	QString sAdjZnName  = BEMPX_GetString( lCrlSpcCSEZnRefDBID, iSpecVal, iError, ivCrlSpcIdxs[iAdjObj] );		assert( !sAdjZnName.isEmpty() );
				QString sCrlSpcName = BEMPX_GetString( lCrlSpcNameDBID    , iSpecVal, iError, ivCrlSpcIdxs[iAdjObj] );		assert( !sCrlSpcName.isEmpty() );
				if (!sAdjZnName.isEmpty() && !sCrlSpcName.isEmpty())
				{
				// create and setup cseREPORTCOL object
					QString sRColName = QString( "rcol %1" ).arg( BEMPX_GetNumObjects( iRptColClass )+1 );
					pRptColObj = BEMPX_CreateObject( iRptColClass, sRColName.toLocal8Bit().constData(), NULL /*parent*/ );
					if (pRptColObj == NULL)
						sErrMsg = QString( "Unable to create cseREPORTCOL object (to report CrawlSpace '%1' data)." ).arg( sAdjZnName );
					else
					{	iRetVal++;
						if (BEMPX_SetBEMData( lDBID_RptColRef, BEMP_QStr, (void*) &sCrlSpcName, BEMO_User, -1 /*iOccur*/ ) < 0)
							sErrMsg = QString( "Unable to set cseREPORTCOL:<CrawlSpaceObjRef> = '%1' (DBID = %2)." ).arg( sCrlSpcName, QString::number( lDBID_RptColRef ) );
					}
			}	}
		}
	}
	else
		sErrMsg = QString( "Invalid AddCSEReportColumn() argument #1: processing option '%1' unrecognized." ).arg( sProcOption );

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}
	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

// SAC 3/11/14 - AssignOrCreateComp() - first argument comp type, 2nd is comp name, following args are pairs of created comp property name (in quotes) and values/strings/enumerations for each property
// SAC 10/31/17 - mod to recognize -99996 as UNDEFINED to check for certain properties that are not defined (via baArgUndef[]) (Res tic #917)
void AssignOrCreateComp( int /*op*/, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
	ExpNode* pNode = NULL;
	vector<string> saArgs, saDBIDs;
	vector<double> faArgs;
	vector<bool> baArgNumeric, baArgUndef;
	vector<long> laDBID;
	vector<int> iaPropType;
	string sCompName, sErrMsg;
	int iObjCID=0, iNumDBIDArgPairs=0, iArgPairIdx, iArg, iError;

	if (nArgs < 4 || (nArgs % 2) > 0)
		boost::str( boost::format( "AssignOrCreateComp() Error:  Expecting >= 4 and an even number of arguments (%d arguments supplied)" ) % nArgs );
	else
	{	// size arrays to store variable arguments
		iNumDBIDArgPairs = (nArgs-2) / 2;					assert( iNumDBIDArgPairs > 0 );
		saArgs.resize(  iNumDBIDArgPairs );
		faArgs.resize(  iNumDBIDArgPairs );
		laDBID.resize(  iNumDBIDArgPairs );
		saDBIDs.resize( iNumDBIDArgPairs );
		baArgNumeric.resize( iNumDBIDArgPairs );
		baArgUndef.resize(   iNumDBIDArgPairs );
		iaPropType.resize(   iNumDBIDArgPairs );
	}

	for (iArg = nArgs; iArg > 0; iArg--)
	{	pNode = ExpxStackPop( stack );
		if (sErrMsg.size() < 1)
		{	if (iArg == 1)
			{	// object type node
				if (pNode->type != EXP_Value)
					boost::str( boost::format( "AssignOrCreateComp() Error:  First argument must be object type to be created ('%s' supplied)" ) % (char*) pNode->pValue );
				else if (pNode->fValue < 1 || pNode->fValue > BEMPX_GetNumClasses())
					boost::str( boost::format( "AssignOrCreateComp() Error:  First argument must be object type to be created (%g supplied)" ) % pNode->fValue );
				else
					iObjCID = (int) pNode->fValue;
			}
			else if (iArg == 2)
			{	// object name
				if (pNode->type != EXP_String)
					boost::str( boost::format( "AssignOrCreateComp() Error:  Second argument must be name of object to be created (%g supplied)" ) % pNode->fValue );
				else if (pNode->pValue == NULL || (strlen( (char*) pNode->pValue ) == 1 && ((char*) pNode->pValue)[0] == ' '))
					sCompName = "";
				else
					sCompName = (char*) pNode->pValue;
			}
			else
			{	// DBID/value pair
				iArgPairIdx = (iArg-3)/2;			assert( iArgPairIdx < iNumDBIDArgPairs );
				if ((iArg % 2) == 0)
				{	// string/numeric value
					baArgNumeric[iArgPairIdx] = (pNode->type != EXP_String);
					baArgUndef[  iArgPairIdx] = false;
					if (pNode->type == EXP_String)
						saArgs[iArgPairIdx] = (char*) pNode->pValue;
					else
					{	faArgs[iArgPairIdx] = pNode->fValue;
						baArgUndef[iArgPairIdx] = IsReserved_UNDEFINED( pNode->fValue );
				}	}
				else
				{	// DBID
					if (pNode->type != EXP_String)
						boost::str( boost::format( "AssignOrCreateComp() Error:  Expected argument #%d to be name of property that subsequent value/string is to be set to (%g supplied instead)" ) % iArg % pNode->fValue );
					else
						saDBIDs[iArgPairIdx] = (char*) pNode->pValue;
		}	}	}
		ExpxNodeDelete( pNode );
	}
	for (iArg=0; (sErrMsg.size() < 1 && iArg < iNumDBIDArgPairs); iArg++)
	{	int iFuncArg = 3 + (iArg * 2);
		long lDBID = BEMPX_GetDatabaseID( saDBIDs[iArg].c_str(), iObjCID );
		if (lDBID < BEM_COMP_MULT)
			boost::str( boost::format( "AssignOrCreateComp() Error:  Expected argument #%d to be name of property that subsequent value/string is to be set to ('%s' supplied instead)" ) % iFuncArg % saDBIDs[iArg].c_str() );
		else
		{	laDBID[iArg] = lDBID;
			BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
			if (pPropType == NULL)
				boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to retrieve BEMPropertyType for argument #%d ('%s' supplied, DBID = %ld)" ) % iFuncArg % saDBIDs[iArg].c_str() % lDBID );
			else
			{	switch (pPropType->getPropType())
				{	case  BEMP_Int :	iaPropType[iArg] = BEMP_Int;
											if (!baArgNumeric[iArg] && !baArgUndef[iArg])
												boost::str( boost::format( "AssignOrCreateComp() Error:  Unexpected BEMPropertyType for argument #%d ('%s' supplied, expecting arg #%d to be numeric)" ) % iFuncArg % saDBIDs[iArg].c_str() % (iFuncArg+1) );
											break;
					case  BEMP_Flt :	iaPropType[iArg] = BEMP_Flt;
											if (!baArgNumeric[iArg] && !baArgUndef[iArg])
												boost::str( boost::format( "AssignOrCreateComp() Error:  Unexpected BEMPropertyType for argument #%d ('%s' supplied, expecting arg #%d to be numeric)" ) % iFuncArg % saDBIDs[iArg].c_str() % (iFuncArg+1) );
											break;
					case  BEMP_Sym :	iaPropType[iArg] = (baArgNumeric[iArg] ? BEMP_Int : BEMP_Str);		break;
					case  BEMP_Str :	iaPropType[iArg] = BEMP_Str;
											if (baArgNumeric[iArg] && !baArgUndef[iArg])
												boost::str( boost::format( "AssignOrCreateComp() Error:  Unexpected BEMPropertyType for argument #%d ('%s' supplied, expecting arg #%d to be a string)" ) % iFuncArg % saDBIDs[iArg].c_str() % (iFuncArg+1) );
											break;
					case  BEMP_Obj :	iaPropType[iArg] = BEMP_Str;
											if (baArgNumeric[iArg] && !baArgUndef[iArg])
												boost::str( boost::format( "AssignOrCreateComp() Error:  Unexpected BEMPropertyType for argument #%d ('%s' supplied, expecting arg #%d to be a string)" ) % iFuncArg % saDBIDs[iArg].c_str() % (iFuncArg+1) );
											break;
					default :	boost::str( boost::format( "AssignOrCreateComp() Error:  Invalid BEMPropertyType for argument #%d ('%s' supplied, type = %ld)" ) % iFuncArg % saDBIDs[iArg].c_str() % pPropType->getPropType() );	break;
		}	}	}
	}

// now check through all objects of this type in model, starting w/ one that may already exist by the same name as that specified in argument #2
	int iExistObjIdx = -1;
	vector<int> iaObjIdx;
	bool bObjFound = false;
	long lData;		double fData;	QString sData;		int iObj, iNumObjs=0;
	if (sErrMsg.size() < 1)
	{	iNumObjs = BEMPX_GetNumObjects( iObjCID );
		if (iNumObjs > 0)
		{	iaObjIdx.resize( iNumObjs );
			BEMObject* pExistObj = BEMPX_GetObjectByName( iObjCID, iError, sCompName.c_str() );
			if (pExistObj && pExistObj->getClass())
				iExistObjIdx = BEMPX_GetObjectIndex( pExistObj->getClass(), pExistObj );
			for (iObj=0; iObj < iNumObjs; iObj++)
			{	if (iExistObjIdx < 1)
					iaObjIdx[iObj] = iObj;
				else if (iObj == 0)
					iaObjIdx[iObj] = iExistObjIdx;
				else if (iObj <= iExistObjIdx)
					iaObjIdx[iObj] = iObj-1;
				else
					iaObjIdx[iObj] = iObj;
			}
		// now search through objects in model for match to function arguments
			int iStatus=0, iSpecialVal, iError;
			for (iObj=0; (!bObjFound && iObj < iNumObjs); iObj++)
			{	bObjFound = true;
				for (iArg=0; (bObjFound && iArg < iNumDBIDArgPairs); iArg++)
				{	if (baArgUndef[iArg])
						bObjFound = (BEMPX_GetDataStatus( laDBID[iArg], iaObjIdx[iObj] ) < 1);	// SAC 10/31/17
					else
						switch( iaPropType[iArg] )
						{	case  BEMP_Int :	if (WithinMargin( faArgs[iArg], 0.0, 0.00001 ))
														bObjFound = (BEMPX_GetInteger( laDBID[iArg], lData, (long) (faArgs[iArg]-2), -1, iaObjIdx[iObj] ) && (lData == 0));
													else
														bObjFound = (BEMPX_GetInteger( laDBID[iArg], lData, (long) (faArgs[iArg]-2), -1, iaObjIdx[iObj] ) && (lData == (long) faArgs[iArg]));
													break;
							case  BEMP_Flt :	//if (WithinMargin( faArgs[iArg], 0.0, 0.00001 ))
													//	bObjFound = (BEMPX_SetDataFloat( laDBID[iArg], fData, (faArgs[iArg]-2), -1, iaObjIdx[iObj] ) && WithinMargin( fData, 0.0, 0.00001 ));
													//else
													//	bObjFound = (BEMPX_SetDataFloat( laDBID[iArg], fData, (faArgs[iArg]-2), -1, iaObjIdx[iObj] ) && WithinMargin( fData, faArgs[iArg], (faArgs[iArg] / 10000.0) ));
													fData = BEMPX_GetFloatAndStatus( laDBID[iArg], iStatus, iSpecialVal, iError, iaObjIdx[iObj], BEMO_User, -1, true );
													if (WithinMargin( faArgs[iArg], 0.0, 0.00001 ))
														bObjFound = (iStatus > 0 && WithinMargin( fData, 0.0, 0.00001 ));
													else
														bObjFound = (iStatus > 0 && WithinMargin( fData, faArgs[iArg], (faArgs[iArg] / 10000.0) ));
													break;
							case  BEMP_Str :	bObjFound = (BEMPX_GetString( laDBID[iArg], sData, FALSE, 0, -1, iaObjIdx[iObj] ) && sData.compare( saArgs[iArg].c_str() ) == 0);
													break;
							default        :	bObjFound = false;	break;
						}
				}
				if (bObjFound)
				{	// make sure that sCompName reflects ACTUAL OBJECT name
					if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iObjCID ), sData, FALSE, 0, -1, iaObjIdx[iObj] ) || sData.isEmpty())
						boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to retrieve name of object matching function arguments (CID = %d, iObjIdx = %d)" ) % iObjCID % iaObjIdx[iObj] );
					else
						sCompName = sData.toLocal8Bit().constData();
		}	}	}
	}

	if (sErrMsg.size() < 1 && !bObjFound)
	{	// need to CREATE NEW object w/ the properties defined in the function arguments
		if (!BEMPX_CanCreateAnotherUserObject( iObjCID, 1 ))
			boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to create new object (CID = %d)" ) % iObjCID );
		else
		{	BEMObject* pParentObj = NULL;
			int i1ParentClass = BEMPX_GetClassID( pEval->lPrimDBID );
			BEMClass* pCr8Class = BEMPX_GetClass( iObjCID, iError );
			if (pCr8Class  &&  pCr8Class->ClassInParentList( (int) i1ParentClass ))
				pParentObj = BEMPX_GetObjectByClass( i1ParentClass, iError, pEval->iPrimObjIdx, pEval->ePrimObjType );

			QString sNewCompName = sCompName.c_str();
			if (!BEMPX_GetDefaultComponentName( iObjCID, sNewCompName ))
				boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to load new object name (CID = %d)" ) % iObjCID );
			else
			{	BEMObject* pNewObj = BEMPX_CreateObject( iObjCID, sNewCompName.toLocal8Bit().constData(), pParentObj, BEMO_User, FALSE );
				if (pNewObj == NULL)
					boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to create new object (CID = %d, '%s')" ) % iObjCID % sNewCompName.toLocal8Bit().constData() );
				else
				{	sCompName = sNewCompName.toLocal8Bit().constData();
					for (iArg=0; (sErrMsg.size() < 1 && iArg < iNumDBIDArgPairs); iArg++)
					{	if (!baArgUndef[iArg])
							switch( iaPropType[iArg] )
							{	case  BEMP_Int :	lData = (long) faArgs[iArg];
														if (BEMPX_SetBEMData( laDBID[iArg], BEMP_Int, (void*) &lData, BEMO_User, iNumObjs /*BEM_PropertyStatus eStatus=BEMS_UserDefined,*/ ) < 0)
															boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to set int to new object (DBID '%s'/%ld, value %ld)" ) % saDBIDs[iArg].c_str() % laDBID[iArg] % lData );
														break;
								case  BEMP_Flt :	fData = faArgs[iArg];
														if (BEMPX_SetBEMData( laDBID[iArg], BEMP_Flt, (void*) &fData, BEMO_User, iNumObjs /*BEM_PropertyStatus eStatus=BEMS_UserDefined,*/ ) < 0)
															boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to set float to new object (DBID '%s'/%ld, value %g)" ) % saDBIDs[iArg].c_str() % laDBID[iArg] % fData );
														break;
								case  BEMP_Str :	sData = saArgs[iArg].c_str();
														if (BEMPX_SetBEMData( laDBID[iArg], BEMP_QStr, (void*) &sData,  // BEMP_Str, (void*) sData.toLocal8Bit().constData(), 
																							BEMO_User, iNumObjs /*BEM_PropertyStatus eStatus=BEMS_UserDefined,*/ ) < 0)
															boost::str( boost::format( "AssignOrCreateComp() Error:  Unable to set string to new object (DBID '%s'/%ld, string '%s')" ) % saDBIDs[iArg].c_str() % laDBID[iArg] % sData.toLocal8Bit().constData() );
														break;
					}		}

			// perhaps in the future enable rulelist eval following object creation...
			//		else if (pEval->sRulelistToEvaluate.length() > 0 && iEvalOption == 1)
			//		{
			//			pEval->iRulelistEvalClass = iObjCID;
			//			pEval->eRulelistEvalObjType = BEMO_User;
			//			pEval->maRulelistEvalObjIdxs.push_back( (iFirstNewObjIdx+i) );
			//		}

		}	}	}
	}

	// allocate & setup result node
	pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
	if (sErrMsg.size() > 0)
	{	ExpSetErr( error, EXP_RuleProc, sErrMsg.c_str() );
		pNode->type = EXP_Invalid;
		pNode->fValue = 0.0;
	}
	else
	{	// setup node to return the name of the last component created
		// this name will be used to set an assigned component depending on the rule's left side
#pragma warning(disable : 4996)		// SAC 9/9/16
		pNode->type = EXP_String;
		pNode->pValue = malloc( sCompName.size() + 1 );
		strcpy( (char*) pNode->pValue, (const char*) sCompName.c_str() );
#pragma warning(default : 4996)
	}

	// Push result node onto stack
	ExpxStackPush( stack, pNode );
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static const char* pszObjType[] = { "User", "RuleLib", "UserLib", "ERROR" };
static void PopulateBEMProcInfo( QString& sBEMProcErr, long lDBID, int iOccur, BEM_ObjType eObjType, int iModel, const char* pszLeading, const char* pszTrailing )  // SAC 12/24/07 - added more verbose BEMProc retrieval info
{
	QString sModelID = "", sModelID2 = "";																assert( iModel < 0 || !ruleSet.IsDataModel() || ruleSet.getNumTransformations() > iModel );
	if (iModel >= 0 && ruleSet.IsDataModel() && ruleSet.getNumTransformations() > iModel)
	{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iModel);					assert( pTrans );
		if (pTrans)
		{	sModelID  = QString( "%1 model, "  ).arg( pTrans->getLongName() );
			sModelID2 = QString( " (%1 model)" ).arg( pTrans->getLongName() );
	}	}

   int iError;
   BEMClass* pClass = BEMPX_GetClass( BEMPX_GetClassID( lDBID ), iError, iModel );
   if (lDBID <= BEM_COMP_MULT || pClass == NULL)
      sBEMProcErr = QString( "invalid DBID '%1' (%2 error %3)" ).arg( QString::number( lDBID ), sModelID, QString::number( iError ) );
   else
   {
      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError, iModel );
      if (pPropType == NULL)
         sBEMProcErr = QString( "invalid %1 property type (%2 class %3, property type %4, error %5)" ).arg( pClass->getShortName(), sModelID, QString::number( BEMPX_GetClassID( lDBID ) ), QString::number( BEMPX_GetPropertyID( lDBID ) ), QString::number( iError ) );
      else if (iOccur < 0)
         sBEMProcErr = QString( "invalid object index (%1) retrieving %2:%3%4" ).arg( QString::number( iOccur ), pClass->getShortName(), pPropType->getShortName(), sModelID2 );
      else
      {	int iObjType = (eObjType==BEMO_User ? 0 : (eObjType==BEMO_RuleLib ? 1 : (eObjType==BEMO_UserLib ? 2 : 3 )));
      	BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError, iOccur, eObjType, iModel );
      	if (pObj == NULL)
      	   sBEMProcErr = QString( "invalid %1 object (%2 class %3, index %4, eObjType %5, error %6)" ).arg( pClass->getShortName(), sModelID, QString::number( BEMPX_GetClassID( lDBID ) ), QString::number( iOccur ), pszObjType[iObjType], QString::number( iError ) );
      	else
      	{
            BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iModel );
            if (pProp == NULL)
               sBEMProcErr = QString( "invalid %1 '%2' property (%3 class %4, property type %5 (%6), array %7, error %8)" ).arg( pClass->getShortName(), pObj->getName(),
                                          sModelID, QString::number( BEMPX_GetClassID( lDBID ) ), pPropType->getShortName(), QString::number( BEMPX_GetPropertyID( lDBID ) ), QString::number( BEMPX_GetArrayID( lDBID ) ), QString::number( iError ) );
            else if (pProp->getDataStatus() <= BEMS_Undefined || pProp->getDataStatus() >= BEMS_NumTypes)
               sBEMProcErr = QString( "invalid %1 '%2' %3 status (%4 class %5, property type %6, array %7, status %8)" ).arg( pClass->getShortName(), pObj->getName(), pPropType->getShortName(),
                                          sModelID, QString::number( BEMPX_GetClassID( lDBID ) ), QString::number( BEMPX_GetPropertyID( lDBID ) ), QString::number( BEMPX_GetArrayID( lDBID ) ), QString::number( pProp->getDataStatus() ) );
            else
               sBEMProcErr = QString( "invalid %1 '%2' %3 data (%4 class %5, property type %6, array %7, status %8)" ).arg( pClass->getShortName(), pObj->getName(), pPropType->getShortName(),
                                          sModelID, QString::number( BEMPX_GetClassID( lDBID ) ), QString::number( BEMPX_GetPropertyID( lDBID ) ), QString::number( BEMPX_GetArrayID( lDBID ) ), QString::number( pProp->getDataStatus() ) );
         }
      }
   }

   if (pszLeading)
      sBEMProcErr = pszLeading + sBEMProcErr;
   if (pszTrailing)
      sBEMProcErr += pszTrailing;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  LocalParentChildRef()
//
// Purpose ------------------------------------------------------------------
//   Evaluates LocalRef, ParentRef and ChildRef functions.
//   
// Arguments ----------------------------------------------------------------
//   int            op    : function enum
//   int            nArgs : number of arguments stored on stack
//   ExpStack*      stack : expression stack
//   ExpEvalStruct* pEval : structure containing data describing comp/param being evaluated
//   ExpError*      error : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static void LocalParentChildRef( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
	bool bRetMustBeValid = (op == BF_GlobalVal || op == BF_LocalVal || op == BF_ParentVal || op == BF_Parent2Val || op == BF_Parent3Val);  // SAC 2/13/14
	bool bGetSymStr = (ruleSet.IsDataModel() || op == BF_LocSymStr || op == BF_GlobSymStr || op == BF_Par2SymStr || op == BF_Par3SymStr || op == BF_LocRefSymStr ||
															  op == BF_ParSymStr || op == BF_ParRefSymStr || op == BF_Par2RefSymStr || op == BF_Par3RefSymStr );  // SAC 4/10/14
   // First grab trailing child index (if ChildRef())
   int iChildIdx = -1;
   if (op == BF_ChildRef)	// pop trailing numeric value to compare the Local* value to
   {
      ExpNode* pIdxNode = ExpxStackPop( stack );
      if (pIdxNode->type != EXP_Value)
		{	if (op == BF_ChildRef)
				ExpSetErr( error, EXP_RuleProc, "Invalid child index (final argument must be numeric value)" );
			else
				ExpSetErr( error, EXP_RuleProc, "Invalid final Local*() argument (must be numeric value)" );
		}
      else
         iChildIdx = (int) pIdxNode->fValue;
      ExpxNodeDelete( pIdxNode );
      nArgs--;
   }

   // Now pop all other (Comp:Param) nodes off stack and store in Long Array
   long plParams[20];
	int i0ArgModel = -1;
	long long lMDBID;
	// SAC 12/19/01 - Revised logic to handle scenario where some fraction of Parent*() function arguments will have already been parsed during ruleset compilation
   ExpNode* pNode = ExpxStackPop( stack );
   int iError = 0;
   int iRefCompID = 0;  // SAC 7/17/01
// SAC 8/28/12 - since object reference properties can now reference multiple object types, the evaluation of LocalRef() and related functions must occur DURING parsing of
//               the (potentially) multi-object referencing string argument - which results in fairly major re-write of this routine to combine the parsing and evaluation portions...
   int iDataStatus, iDataType=0, iSpecialVal;
   BEM_ObjType eObjType=BEMO_User;
	BOOL bParseAsWeEvaluate = FALSE;
	int i1ParsedClass = 0;
	long lParsedDBID = 0;
	int iParsedDBID0Model = -1;
	QString sParseArg;
   if ( pNode->type == EXP_String  &&  nArgs == 1  &&
        ( op == BF_ParentRef  || op == BF_Parent2Ref  || op == BF_Parent3Ref  || op == BF_Parent2Val  || op == BF_Parent3Val || op == BF_Par2SymStr  || op == BF_Par3SymStr   || op == BF_Par2RefSymStr  || op == BF_Par3RefSymStr   ||
          op == BF_PIsDefault || op == BF_ParStatus   || op == BF_PCompAssign || op == BF_ParStrAElem || op == BF_ParentVal  || op == BF_ParSymStr   || op == BF_ParRefSymStr ||    // SAC 11/20/09
			 op == BF_LocalRef   || op == BF_LCompAssign || op == BF_LIsDefault  || op == BF_LocStatus   || op == BF_LocalVal   || op == BF_LocSymStr   || op == BF_LocRefSymStr ||   // SAC 8/28/12 - added LocalRef... options to enable these to be parsed at eval time as well
   		 op == BF_ChildRef   || op == BF_GlobalRef   || op == BF_GlobStatus  || bRetMustBeValid  ) )   // SAC 8/28/12   // SAC 2/13/14
   {  // must PARSE ParentRef() argument -> multiple comp:param ID Args
		bParseAsWeEvaluate = TRUE;
		sParseArg = (char*) pNode->pValue;								assert( !sParseArg.isEmpty() );
		if (op == BF_LocalRef   || op == BF_LCompAssign || op == BF_LIsDefault  || op == BF_LocStatus || op == BF_LocalVal ||   // SAC 8/28/12 - added LocalRef... options to enable these to be parsed at eval time as well
			 op == BF_LocSymStr || op == BF_LocRefSymStr )		// SAC 5/19/17 - added Loc*SymStr checks
			i1ParsedClass = BEMPX_GetClassID( pEval->lPrimDBID );
		else if (op == BF_ChildRef || op == BF_GlobalRef || op == BF_GlobalVal )  // SAC 8/28/12  // SAC 2/13/14
		{	// first portion of argument string identifies the object type to start with
			int iColon = sParseArg.indexOf(':');									assert( iColon > 0 );
			if (iColon > 0)
			{	QString sObjType = sParseArg.left( iColon );
				i1ParsedClass = BEMP_GetDBComponentID( sObjType );		assert( i1ParsedClass > 0 );
				sParseArg = sParseArg.right( sParseArg.length() - iColon - 1 );  // remove leading child/global object type name
			}
		}
		else
      	i1ParsedClass = (op == BF_ParentRef || op == BF_PCompAssign || op == BF_PIsDefault || op == BF_ParStatus || op == BF_ParStrAElem || op == BF_ParentVal || op == BF_ParSymStr || op == BF_ParRefSymStr ? pEval->iPrimPar1Class :    // SAC 11/20/09
                                             (op == BF_Parent2Ref || op == BF_Parent2Val || op == BF_Par2SymStr || op == BF_Par2RefSymStr ? pEval->iPrimPar2Class : pEval->iPrimPar3Class));
		QString sRemainingStr = sParseArg;
												assert( !ruleSet.IsDataModel() || (pEval && !pEval->sRuleListName.isEmpty()) );
		int iCurTransID = ((ruleSet.IsDataModel() && pEval && !pEval->sRuleListName.isEmpty()) ? GetTransformationIDFromRulelistName( pEval->sRuleListName ) : 0); 	// SAC 3/29/14 - enable rulelist expression grouping
		iParsedDBID0Model = RemovePrecedingTransformationID( sRemainingStr, iCurTransID ) - 1;
      lParsedDBID = BEMPX_GetDatabaseID( sRemainingStr, i1ParsedClass, FALSE, &iRefCompID );   // Note: when > 0, piRefCompID identifies only the first of possible several object types that this property can reference

	   // check to confirm that first DBID returned is consistent with the expected class
      if (lParsedDBID > 0)
      {  int iClassID = BEMPX_GetClassID( lParsedDBID );
         if (iClassID != i1ParsedClass)
         {  lParsedDBID = -1;
				QString sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument '%1'" ).arg( sParseArg );
            ExpSetErr( error, EXP_RuleProc, sErrMsg );
         }
			else if (iParsedDBID0Model > BEMPX_GetActiveModel())	// SAC 9/25/13 - added check to ensure valid transform index
         {  lParsedDBID = -1;
				QString sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument transform ID '%1' (may only reference the current or a prior transform)" ).arg( sParseArg );
            ExpSetErr( error, EXP_RuleProc, sErrMsg );
         }
      }
		else
      {	QString sBEMProcErr, sErrModel;  // SAC 6/23/15 - added error reporting
			if (iParsedDBID0Model >= 0 && ruleSet.IsDataModel() && ruleSet.getNumTransformations() > iParsedDBID0Model)
      	{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iParsedDBID0Model);					assert( pTrans );
				if (pTrans)
					sErrModel = QString( " (%1 model)" ).arg( pTrans->getLongName() );
			}
			BEMClass* pBadClass = BEMPX_GetClass( i1ParsedClass, iError, iParsedDBID0Model );
			if (pBadClass)
	      	sBEMProcErr = QString( "Unable to calculate DBID for '%1' from %2%3, inside LocalParentChildRef()" ).arg( sRemainingStr, pBadClass->getShortName(), sErrModel );
			else
				sBEMProcErr = QString( "Unable to calculate DBID for '%1'%2, inside LocalParentChildRef()" ).arg( sRemainingStr, sErrModel );
         ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
         iError = -1;
      }

      if (lParsedDBID > 0)
		{	// remove left portion of string argument through the first ':', which is where subsequent (eval-time) parsing will continue below
			//sParseArg = (sRemainingStr.indexOf(':') > 0 ? sRemainingStr.right( sRemainingStr.length() - sRemainingStr.indexOf(':') - 1 ) : "");
			// SAC 8/13/14 - expanded on above code to ensure the sParseArg is blanked out through the second ':' if the first TWO sections translate to the lDBID already found
			int iFirstColonIdx = sRemainingStr.indexOf(':');
			if (iFirstColonIdx < 1)
				sParseArg.clear();
			else
			{	int iSecondColonIdx = sRemainingStr.indexOf(':', iFirstColonIdx+1);
				if (iSecondColonIdx < 0)
					sParseArg = (BEMPX_GetDatabaseID( sRemainingStr ) == lParsedDBID ? "" : sRemainingStr.right( sRemainingStr.length() - iFirstColonIdx - 1 ));
				else
				{	QString sFirstTwoSects = sRemainingStr.left( iSecondColonIdx );		assert( !sFirstTwoSects.isEmpty() );
					int iColonIdxToUse = (BEMPX_GetDatabaseID( sFirstTwoSects ) == lParsedDBID ? iSecondColonIdx : iFirstColonIdx);
					sParseArg = sRemainingStr.right( sRemainingStr.length() - iColonIdxToUse - 1 );
			}	}
		}
      ExpxNodeDelete( pNode );
	}
	else
	{	for ( int arg = nArgs; arg > 0; arg-- )
      {  if (arg < nArgs)
            pNode = ExpxStackPop( stack );
         if (pNode->type != EXP_Value)
            ExpSetErr( error, EXP_RuleProc, "Invalid XxxRef() argument" );
         else
         //   plParams[ arg-1 ] = (long) pNode->fValue;
         {	lMDBID = (long long) pNode->fValue;				// SAC 3/19/13 - code to handle DBIDs including MODEL index
				if (lMDBID > BEM_MODEL_MULT)
				{	plParams[ arg-1 ] = (long) BEMPX_MDBIDtoDBID( lMDBID );						assert( i0ArgModel<0 || i0ArgModel==((int) BEMPX_GetModelID( lMDBID )-1) );
					i0ArgModel = (int) BEMPX_GetModelID( lMDBID ) - 1;
				}
				else
					plParams[ arg-1 ] = (long) lMDBID;
			}
         ExpxNodeDelete( pNode );
      }
	}

   bool bPushedResult = FALSE;
   int iOccur=-1, iObjIdxModel=-1;		// SAC 6/23/15

   // Get occurrence index for first data retrieval based on Local/Parent/ChildRef type
   // SAC 8/3/99 - added processing to handle ComponentAssigned()
	int iFirstClassToCheck = -1;
   if (op == BF_LocalRef || op == BF_LCompAssign || op == BF_LIsDefault || op == BF_LocStatus || op == BF_LocMxStrLen || op == BF_LocalVal || op == BF_LocSymStr || op == BF_LocRefSymStr)   // SAC 11/20/09
   {
		iFirstClassToCheck = (pEval->lPrimDBID > BEM_COMP_MULT ? BEMPX_GetClassID( pEval->lPrimDBID ) : -1);
      iOccur = pEval->iPrimObjIdx;
      eObjType = pEval->ePrimObjType;
   }
   else if (op == BF_ParentRef || op == BF_PCompAssign || op == BF_PIsDefault || op == BF_ParStatus || op == BF_ParStrAElem || op == BF_ParentVal || op == BF_ParSymStr || op == BF_ParRefSymStr)   // SAC 11/20/09
   {
		iFirstClassToCheck = (pEval->iPrimPar1Class > 0 ? pEval->iPrimPar1Class : -1);
      iOccur = pEval->iPrimParObjIdx;
      eObjType = pEval->ePrimParObjType;
   }
   else if (op == BF_Parent2Ref || op == BF_Parent2Val || op == BF_Par2SymStr || op == BF_Par2RefSymStr)
   {
		iFirstClassToCheck = (pEval->iPrimPar2Class > 0 ? pEval->iPrimPar2Class : -1);
      iOccur = pEval->iPrimPar2ObjIdx;
      eObjType = pEval->ePrimPar2ObjType;
   }
   else if (op == BF_Parent3Ref || op == BF_Parent3Val || op == BF_Par3SymStr || op == BF_Par3RefSymStr)
   {
		iFirstClassToCheck = (pEval->iPrimPar3Class > 0 ? pEval->iPrimPar3Class : -1);
      iOccur = pEval->iPrimPar3ObjIdx;
      eObjType = pEval->ePrimPar3ObjType;
   }
   else if (op == BF_ChildRef)
   {
      int i1ParClass =   BEMPX_GetClassID( pEval->lPrimDBID );
      int i1ChildClass = BEMPX_GetClassID( (bParseAsWeEvaluate ? lParsedDBID : plParams[ 0 ]) );
      iOccur = BEMPX_GetChildObjectIndex( i1ParClass, i1ChildClass, iError, eObjType, iChildIdx,
                                        pEval->iPrimObjIdx, pEval->ePrimObjType );
   }
   else if (op == BF_GlobalRef || op == BF_GlobStatus || op == BF_GlobalVal)  // SAC 1/22/07  // SAC 2/13/14
   {
      iOccur = 0;
      eObjType = BEMPX_GetCurrentObjectType( BEMPX_GetClassID( (bParseAsWeEvaluate ? lParsedDBID : plParams[ 0 ]) ), iOccur,
																					(bParseAsWeEvaluate ? iParsedDBID0Model : i0ArgModel)	 );
   }
   else
      ExpSetErr( error, EXP_RuleProc, "Invalid LocalParentChildRef() Operation Code" );
	assert( iFirstClassToCheck != 0 );		// this value should either be -1 or > 0

   // Retrieve data from database
	int i0Model = (!bParseAsWeEvaluate ? i0ArgModel  : iParsedDBID0Model);
	iError = (bParseAsWeEvaluate && lParsedDBID < 1 && bRetMustBeValid) ? -1 : 0;		// SAC 10/6/14 - abort processing when bRetMustBeValid & parse error occurred
   int iLastArgIdx = nArgs-1;  // SAC 11/20/09
   if ((op == BF_LocMxStrLen || op == BF_ParStrAElem) && plParams[iLastArgIdx] < BEM_COMP_MULT)  // SAC 11/20/09 - don't process the FINAL argument as a DBID if evaluating LocalMaxStringLength() or ParentStringArrayElement() if a non-DBID arg is present
      iLastArgIdx--;
	int iArgIdx = 0, iStatus = 0;
	bool bFirstArgProcessed = false;  // SAC 8/25/14
	int iInvalidFirstArgClass = -1;  // SAC 8/25/14
   // First loop over all but last Comp:Param IDs, getting objects along the way
//   for (int i=0; (iOccur > -1) && (iError >= 0) && (i < iLastArgIdx); i++)
   while ( iOccur > -1 && iError >= 0 && ((bParseAsWeEvaluate && !sParseArg.isEmpty()) || (!bParseAsWeEvaluate && iArgIdx < iLastArgIdx)) )
   {
		long lDBID  = (!bParseAsWeEvaluate ? plParams[iArgIdx] : lParsedDBID);				assert( lDBID > BEM_COMP_MULT );
      BEMObject* pObj = NULL;
		if (!bFirstArgProcessed && iFirstClassToCheck > 0 && iFirstClassToCheck != BEMPX_GetClassID( lDBID ))
		{	iInvalidFirstArgClass = BEMPX_GetClassID( lDBID );										//assert( FALSE );	// catch this new error
		}
		else
      	pObj = (lDBID < BEM_COMP_MULT ? NULL : BEMPX_GetObjectAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, eObjType, i0Model ));
										assert( pObj == NULL || iStatus > 0 );	// if NOT TRUE, then this lDBID NOT an object reference
      if (iError >= 0 && pObj && iStatus > 0)
      {  iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj, i0Model );			iObjIdxModel = i0Model;		// SAC 6/23/15
         eObjType = pObj->getObjectType();

			if (bParseAsWeEvaluate)	// remove left portion of string argument through the first ':', which is where subsequent (eval-time) parsing will continue
		 	{	lParsedDBID = BEMPX_GetDatabaseID( sParseArg, pObj->getClass()->get1BEMClassIdx(), FALSE, &iRefCompID );   // Note: when > 0, piRefCompID identifies only the first of possible several object types that this property can reference
				if (lParsedDBID < 1)
         	{	QString sBEMProcErr, sErrModel;  // SAC 6/23/15 - added error reporting
					if (iParsedDBID0Model >= 0 && ruleSet.IsDataModel() && ruleSet.getNumTransformations() > iParsedDBID0Model)
      			{	RuleSetTransformation* pTrans = ruleSet.getTransformation(iParsedDBID0Model);					assert( pTrans );
						if (pTrans)
							sErrModel = QString( " (%1 model)" ).arg( pTrans->getLongName() );
					}
         		sBEMProcErr = QString( "Unable to calculate DBID for '%1' from %2 '%3'%4, inside LocalParentChildRef()" ).arg( sParseArg, pObj->getClass()->getShortName(), pObj->getName(), sErrModel );
           	   ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
               iError = -1;
            }
				else if (sParseArg.indexOf(':') > 0)
					sParseArg = sParseArg.right( sParseArg.length() - sParseArg.indexOf(':') - 1 );
				else
					sParseArg.clear();
			}
      }
      else
         iOccur = -1;
		iArgIdx++;
		bFirstArgProcessed = true;  // SAC 8/25/14
   }

   // Retrieve and return data associated with last Comp:Param node
   if ( (iOccur < 0) || (iError < 0) )
   {
     	pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );  // SAC 12/19/01
		if (bRetMustBeValid)  // SAC 2/13/14 - ensure return of INVALID node when path not successfully negotiated
		{	// for certain routines we want to know that the data was not returnable
      	pNode->type = EXP_Invalid;
      	pNode->fValue = -99996.0;
		}
		else if (iInvalidFirstArgClass > 0)
		{	BEMClass* pExpectClass = BEMPX_GetClass( iFirstClassToCheck   , iError, i0Model );
			BEMClass* pFoundClass  = BEMPX_GetClass( iInvalidFirstArgClass, iError, i0Model );
			QString sErrMsg;
			if (pExpectClass && pFoundClass)
				sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument - expecting object of type '%1' but found '%2'" ).arg( pExpectClass->getShortName(), pFoundClass->getShortName() );
			else
				sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument - expecting object of type Class=%1 but found Class=%2" ).arg( QString::number( iFirstClassToCheck ), QString::number( iInvalidFirstArgClass ) );
         ExpSetErr( error, EXP_RuleProc, sErrMsg );
	      pNode->type = EXP_Invalid;
      	pNode->fValue = 0.0;
			iInvalidFirstArgClass = -1;  // reset flag to avoid double reporting
		}
		else
      {	// Push node w/ value == 0 onto stack
      	// Allow rules to evaluate despite lack of existing reference objects to prevent
      	// a large number of errors from being reported
      	pNode->type = EXP_Value;
      	pNode->fValue = 0.0;
		}
      ExpxStackPush( stack, pNode );
      bPushedResult = TRUE;
   }
   else
   {
      if (op == BF_LocMxStrLen)  // SAC 11/20/09 - evaluating LocalMaxStringLength()
      {  assert( !bParseAsWeEvaluate );
         long iMaxArrayIdx = (iLastArgIdx < (nArgs-1) && plParams[nArgs-1] < BEM_COMP_MULT ? plParams[nArgs-1] : -1);  // SAC 11/20/09 - user specified the max # of array elements to check
         if (iMaxArrayIdx < 1)
         {
            BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( plParams[ iLastArgIdx ], iError, i0Model );
            if (pPropType)  // && (pPropType->getPropType() == BEMP_Str || pPropType->getPropType() == BEMP_Sym))   - should we restrict this to properties of type symbol or string ???
               iMaxArrayIdx = pPropType->getNumValues();
         }  assert( iMaxArrayIdx > 0 && iMaxArrayIdx <= BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[ iLastArgIdx ], i0Model ) );

         int iMaxStrLen = 0;
         QString sTempMaxStrLen;
         for (int iMSL=0; iMSL < iMaxArrayIdx; iMSL++)
         {
            if (BEMPX_GetString( plParams[ iLastArgIdx ] + iMSL, sTempMaxStrLen, TRUE, 0, -1, iOccur, eObjType, NULL, 0, i0Model ))
               iMaxStrLen = max( iMaxStrLen, sTempMaxStrLen.length() );
         }

         // Setup node to be pushed onto stack
         pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
         pNode->type = EXP_Value;
         pNode->fValue = (double) iMaxStrLen;
         // push result node onto stack
         ExpxStackPush( stack, pNode );
      }
      else if (op == BF_ParStrAElem)  // SAC 11/20/09 - evaluating ParentStringArrayElement()
      {  assert( !bParseAsWeEvaluate );  // allowed above, but clearly needs additional non-string argument...
         assert( plParams[nArgs-1] < BEM_COMP_MULT );  // user should ALWAYS specify the array index
         long i0ArrayIdx = (iLastArgIdx < (nArgs-1) && plParams[nArgs-1] < BEM_COMP_MULT ? plParams[nArgs-1]-1 : 0);  // SAC 11/20/09 - user-specified string array index
         assert( i0ArrayIdx >= 0 && i0ArrayIdx < BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[ iLastArgIdx ], i0Model ) );
         // allocate memory for node to be pushed onto stack
         pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );

         QString sTempStr;
         if (BEMPX_GetString( plParams[ iLastArgIdx ] + i0ArrayIdx, sTempStr, TRUE, 0, -1, iOccur, eObjType, NULL, 0, i0Model ))
         {
#pragma warning(disable : 4996)		// SAC 9/9/16
            pNode->type = EXP_String;
            pNode->pValue = malloc( sTempStr.length() + 1 );
            strcpy( (char*) pNode->pValue, (const char*) sTempStr.toLocal8Bit().constData() );
#pragma warning(default : 4996)
         }
         else
         {  pNode->type = EXP_Invalid;
            pNode->fValue = 0;
         }
         // push result node onto stack
         ExpxStackPush( stack, pNode );
      }
      // SAC 8/3/99 - added processing to handle *CompAssigned() & *IsDefault
      else if ( op == BF_LCompAssign || op == BF_PCompAssign ||
                op == BF_LIsDefault  || op == BF_PIsDefault  ||
                op == BF_LocStatus   || op == BF_ParStatus   || op == BF_GlobStatus )
      {
			long lDBID = (!bParseAsWeEvaluate ? plParams[ iLastArgIdx ] : lParsedDBID);				assert( lDBID > BEM_COMP_MULT );
			if (!bFirstArgProcessed && iFirstClassToCheck > 0 && iFirstClassToCheck != BEMPX_GetClassID( lDBID ))
			{	iInvalidFirstArgClass = BEMPX_GetClassID( lDBID );												//assert( FALSE );	// catch this new error
			}
			else
         {	// Setup node to be pushed onto stack
         	pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );  // SAC 12/19/01
         	pNode->type = EXP_Value;

         	if ( op == BF_LocStatus || op == BF_ParStatus || op == BF_GlobStatus )
         	   pNode->fValue = BEMPX_GetDataStatus( lDBID, iOccur, eObjType, i0Model );
         	else
         	{
					iDataType = BEMPX_GetDataType( lDBID );
         	   // SAC 8/7/10 - implementation of targeted debug output
         	   if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lDBID, iOccur ))
         	      ReportTargetedDebugInfo( pEval, iDataType, lDBID, iOccur, eObjType, "LocalParentChildRef()", i0Model );

         	   // Get pointer to object which we are trying to find out is assigned or not
         //	   void* pData = BEMPX_GetDataAndStatus( lDBID, iDataStatus, iDataType, iSpecialVal, iError, iOccur, eObjType, FALSE /*bReturnParentObject*/, i0Model );
			// SAC 9/5/16 - new open source version of data retrieval...
					BEMObject* pObj=NULL;
					if (iDataType == BEMP_Obj)
						pObj = BEMPX_GetObjectAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, i0Model );
					else if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
						BEMPX_GetIntegerAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, i0Model );
					else if (iDataType == BEMP_Flt)
						BEMPX_GetFloatAndStatus(   lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, i0Model );
					else if (iDataType == BEMP_Str)
						BEMPX_GetStringAndStatus(  lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, i0Model );

         	   // set return value
         	   if (op == BF_LCompAssign || op == BF_PCompAssign)
         	   {  //pNode->fValue = ((iError >= 0 && pData) ? 1.0 : 0.0);   - 7/24/12 - revise return value to equal class index of the referenced object
         	      if (iError >= 0 && pObj && iDataStatus > 0 && pObj->getClass() && pObj->getClass()->get1BEMClassIdx() > 0)
	      	         pNode->fValue = (double) pObj->getClass()->get1BEMClassIdx();
						else
	      	         pNode->fValue = 0.0;
					}
         	   else // if (op == BF_LIsDefault || op == BF_PIsDefault)
         	      pNode->fValue = ((iError >= 0 && iSpecialVal == SV_Default) ? 1.0 : 0.0);
         	}

         	// push result node onto stack
         	ExpxStackPush( stack, pNode );
      }	}
      else
		{	long long lMDBID = (!bParseAsWeEvaluate ? plParams[ iLastArgIdx ] : lParsedDBID);				assert( lMDBID > BEM_COMP_MULT );
			if (!bFirstArgProcessed && iFirstClassToCheck > 0 && iFirstClassToCheck != BEMPX_GetClassID( lMDBID ))
			{	iInvalidFirstArgClass = BEMPX_GetClassID( lMDBID );													//assert( FALSE );	// catch this new error
			}
			else
			{	if (i0Model >= 0)
					lMDBID = BEMPX_DBIDtoMDBID( (i0Model+1), lMDBID );
      	   GetBEMProcData( lMDBID, iOccur, eObjType, stack, error, bGetSymStr, pEval, bRetMustBeValid, iObjIdxModel );  // SAC 10/18/12 - revised bGetSymStr to retrieve string for DataModel rulesets
		}	}

      bPushedResult = TRUE;
   }

	if (iInvalidFirstArgClass > 0) // SAC 8/25/14
	{	// handle this error just like the previous one above
		pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );  // SAC 12/19/01
		if (bRetMustBeValid)  // SAC 2/13/14 - ensure return of INVALID node when path not successfully negotiated
		{	// for certain routines we want to know that the data was not returnable
      	pNode->type = EXP_Invalid;
      	pNode->fValue = -99996.0;
		}
		else
		{	BEMClass* pExpectClass = BEMPX_GetClass( iFirstClassToCheck   , iError, i0Model );
			BEMClass* pFoundClass  = BEMPX_GetClass( iInvalidFirstArgClass, iError, i0Model );
			QString sErrMsg;
			if (pExpectClass && pFoundClass)
				sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument - expecting object of type '%1' but found '%2'" ).arg( pExpectClass->getShortName(), pFoundClass->getShortName() );
			else
				sErrMsg = QString( "Invalid Parent/Local/GlobalRef() argument - expecting object of type Class=%1 but found Class=%2" ).arg( QString::number( iFirstClassToCheck ), QString::number( iInvalidFirstArgClass ) );
         ExpSetErr( error, EXP_RuleProc, sErrMsg );
	      pNode->type = EXP_Invalid;
      	pNode->fValue = 0.0;
		}
      ExpxStackPush( stack, pNode );
      bPushedResult = TRUE;
	}

   // An error has occurred, but lets push a node onto the stack anyway
   // to prevent further errors due to missing result node
   if (!bPushedResult)
   {
      pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );  // SAC 12/19/01
      pNode->type = EXP_Invalid;

      // Push new node onto stack
      ExpxStackPush( stack, pNode );
   }
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool StoreChildObjectPtrs( BEMObject* pParentObj, int iGen, vector<BEMObject*>& paChildObjs, vector<int>& iaGens )
{	bool bRetVal = (pParentObj != NULL);
	if (bRetVal)
	{
//		for (POSITION pos = pParentObj->m_children.GetHeadPosition(); pos != NULL; )
//		{	BEMObject* pChildObj = (BEMObject*) pParentObj->m_children.GetNext( pos );			assert( pChildObj );
		for (int iC=0; iC < pParentObj->getChildCount(); iC++)
		{	BEMObject* pChildObj = pParentObj->getChild( iC );			assert( pChildObj );
			if (pChildObj)
			{	paChildObjs.push_back( pChildObj );
				iaGens.push_back( iGen+1 );
			}
		}
	}
	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  BEMProcSumChildrenAllOrRevRef()
//
// Purpose ------------------------------------------------------------------
//   Evaluates SumChildren(), SumAll(), SumRevRef(), MaxChild(), MaxAll() and
//   MaxRevRef() functions.
//   
// Arguments ----------------------------------------------------------------
//   int            op    : function enum
//   int            nArgs : number of arguments stored on stack
//   ExpStack*      stack : expression stack
//   ExpEvalStruct* pEval : structure containing data describing comp/param being evaluated
//   ExpError*      error : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   Previously named BEMProcSumChildrenOrAll() (prior to incorporation of code
//   to evaluate the BF_SumRevRef operation).
//   
/////////////////////////////////////////////////////////////////////////////

// SAC 8/1/06 - Added new SumRevRefEx() function which operates exactly like SumRevRef() only w/ 2 additional arguments,
//              Arg #4 => flag value describing how to interpret/utilize arg #5
//                          1=>Bool (whether or not to sum),  2=>Sum (sum both arg 2 & 5 into sum),  3=>Product (sum product of args 2 & 5)
//              Arg #5 => DBID of additional item to check, sum or multiply
      // SAC 2/15/13 - SumAcrossIf( Comp:ParamDBID, <Condition> ), where <Condition> is typically something like "Comp:ParamDBID = "Option""
      // SAC 2/15/13 - SumChildrenIf( ChildComp:ParamDBID, <Condition> ), where <Condition> is typically something like "ChildComp:ParamDBID = "Option""
		// SAC 1/26/15 - BF_ListRevRef   : ListRevRef(   RevRefObj:Prop,              "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
		// SAC 1/26/15 - BF_ListRevRefIf : ListRevRefIf( RevRefObj:Prop, <Condition>, "fmt str 1", "fmt str 2-(N-1)", "fmt str last", <1 or more arguments to echo> )
static void BEMProcSumChildrenAllOrRevRef( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
   BOOL bRevRefFunc = (	op == BF_SumRevRef || op == BF_MaxRevRef || op == BF_MinRevRef || op == BF_MaxRevRefC || op == BF_MaxRevRefA || op == BF_SumRevRefEx ||  // SAC 1/3/02  // SAC 11/10/04  // SAC 8/1/06
   							op == BF_ListRevRef || op == BF_ListRevRefIf );		// SAC 1/26/15
   bool bGetMax     = (op == BF_MaxChild || op == BF_MaxAll || op == BF_MaxRevRef || op == BF_MaxRevRefC || op == BF_MaxAllComp || op == BF_MaxRevRefA || op == BF_MaxChildC);  // SAC 1/25/02  // SAC 11/10/04  // SAC 10/18/14
   bool bGetMin     = (op == BF_MinChild || op == BF_MinAll || op == BF_MinRevRef || op == BF_MinChildC);  // SAC 10/18/14
   bool bGetCount   = (op == BF_CountRefs || op == BF_CountUPRefs || op == BF_CountOccur);  // SAC 1/3-4/02  // SAC 5/4/06
   bool bStoreArgsForProcessing = (op == BF_ListRevRef || op == BF_ListRevRefIf);  // SAC 1/26/15
   int i0FirstFormatStrArgIdx = -1;	// SAC 1/26/15
   bool bReturnArrayIdx = (op == BF_MaxRevRefA);   // SAC 11/10/04
	int iOnlyChildGen = -1;  // used to restrict *Children*() routines to a FIXED, SINGLE generation, as opposed to traversing all possible generations (SAC 5/29/15)

   bool bAbort = FALSE;
   double fResult = 0.0;
   QString sResult;
   int iMinMaxArrIdx = -1;   // SAC 11/10/04 - for BF_MaxRevRefA
	BOOL bArgumentConditionExpected = (op == BF_SumAcrsIf || op == BF_SumChldIf || op == BF_ListRevRefIf);  // SAC 3/5/13  // SAC 1/26/15
	BOOL bCondArgsNext = (op == BF_SumAcrsIf || op == BF_SumChldIf);		// SAC 1/26/15 - prevent arg parsing to expect condition args @ end of BF_ListRevRefIf - these will FOLLOW a series of 3 char strings and be in arg #s 2-4
	BOOL bArgCondParsed=FALSE, bArgCondLeftParsed=FALSE, bArgCondRightParsed=FALSE;
	QString sArgCond[2];
	double dArgCond[2]={-99999,-99999};
	long lArgCondDBID[2]={0,0};
	int  iArgCond1Class[2]={0,0}, iArgCondition=0, iArg0Model[2]={-1,-1};
	if ((op == BF_SumAcrsIf || op == BF_SumChldIf) && nArgs < 3)
	{	// modify condition settings to reflect "!= 0" condition when the group of 'condition' arguments consists of only a single argument
		bArgCondRightParsed = TRUE;
		bArgCondParsed = TRUE;
		iArgCondition = 269;  // NEQ
		dArgCond[1] = 0.0;
	}

   // Pop all (Comp:Param & other) nodes off stack and store in Long Array
	long long lMDBID;
   long plParams[40];
	ExpNode* pOrigNodes[40];		int iNumOrigNodes = nArgs;		assert( nArgs < 41 );
	int i0Model = -1, iNumConsecStringArgs = 0;
   for ( int arg = nArgs; arg > 0; arg-- )
   {
      ExpNode* pThisNode = ExpxStackPop( stack );
		if (bArgumentConditionExpected && bCondArgsNext && !bArgCondLeftParsed)
		{	iNumConsecStringArgs = 0;
			if (!bArgCondRightParsed)
			{	if (pThisNode->type == EXP_Value)
				{	if (pThisNode->fValue > BEM_COMP_MULT)
					{	//lArgCondDBID[1] = (long) pThisNode->fValue;
						lMDBID = (long long) pThisNode->fValue;
						if (lMDBID > BEM_MODEL_MULT)
						{	lArgCondDBID[1] = (long) BEMPX_MDBIDtoDBID( lMDBID );
							iArg0Model[1] = (int) BEMPX_GetModelID( lMDBID ) - 1;
						}
						else
							lArgCondDBID[1] = (long) lMDBID;
						iArgCond1Class[1] = BEMPX_GetClassID( lArgCondDBID[1] );
					}
					else
						dArgCond[1] = pThisNode->fValue;
				}
				else
					sArgCond[1] = (const char*) pThisNode->pValue;
				bArgCondRightParsed = TRUE;
			}
			else if (!bArgCondParsed)
			{	if (pThisNode->type != EXP_Value || pThisNode->fValue < EQ || pThisNode->fValue > GE)
				{	bAbort = TRUE;
	            ExpSetErr( error, EXP_RuleProc, "Invalid SumXxxIf() argument (expecting conditional operator)" );
				}
				else
				{	iArgCondition = (int) pThisNode->fValue;
// #define EQ 268
// #define NEQ 269
// #define LT 270
// #define GT 271
// #define LE 272
// #define GE 273
					bArgCondParsed = TRUE;
				}
			}
			else if (!bArgCondLeftParsed)
			{	if (pThisNode->type == EXP_Value)
				{	if (pThisNode->fValue > BEM_COMP_MULT)
					{	//lArgCondDBID[0] = (long) pThisNode->fValue;
						lMDBID = (long long) pThisNode->fValue;
						if (lMDBID > BEM_MODEL_MULT)
						{	lArgCondDBID[0] = (long) BEMPX_MDBIDtoDBID( lMDBID );
							iArg0Model[0] = (int) BEMPX_GetModelID( lMDBID ) - 1;
						}
						else
							lArgCondDBID[0] = (long) lMDBID;
						iArgCond1Class[0] = BEMPX_GetClassID( lArgCondDBID[0] );
					}
					else
						dArgCond[0] = pThisNode->fValue;
				}
				else
					sArgCond[0] = (const char*) pThisNode->pValue;
				bArgCondLeftParsed = TRUE;
			}
			else
			{	assert( FALSE );
			}
         nArgs--;
		}
      else if (pThisNode->type != EXP_Value)
      {
      	if (bStoreArgsForProcessing)
      		iNumConsecStringArgs++;
      	else
         {	bAbort = TRUE;
	         if (bGetMax)
   	         ExpSetErr( error, EXP_RuleProc, "Invalid MaxXxx() argument" );
      	   else if (bGetMin)
         	   ExpSetErr( error, EXP_RuleProc, "Invalid MinXxx() argument" );
	         else if (bGetCount)
   	         ExpSetErr( error, EXP_RuleProc, "Invalid CountXxx() argument" );
      	   else
         	   ExpSetErr( error, EXP_RuleProc, "Invalid SumXxx() argument" );
      }	}
      else
//         plParams[ arg-1 ] = (long) pThisNode->fValue;
		{	iNumConsecStringArgs = 0;
			lMDBID = (long long) pThisNode->fValue;
			if (lMDBID < 11 && lMDBID >= 0 && (op == BF_SumChld || op == BF_MaxChild || op == BF_MinChild || op == BF_MaxChildC || op == BF_MinChildC))	// store OnlyChildGen argument
			{	iOnlyChildGen = (int) lMDBID;  // used to restrict *Children*() routines to a FIXED, SINGLE generation, as opposed to traversing all possible generations (SAC 5/29/15)
	         nArgs--;
			}
			else if (lMDBID > BEM_MODEL_MULT)
			{	plParams[ arg-1 ] = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
				i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
			}
			else
				plParams[ arg-1 ] = (long) lMDBID;
		}

				assert( iNumConsecStringArgs < 3 || (op != BF_ListRevRef || arg == 2) || (op != BF_ListRevRefIf || arg == 3 || arg == 5) );		// check for unexpected format argument indexes...
		if (iNumConsecStringArgs > 2 && ( i0FirstFormatStrArgIdx < 1 || (op == BF_ListRevRef   && arg < 3) ||
																							 (op == BF_ListRevRefIf && arg < 6) ) )
		{	i0FirstFormatStrArgIdx = arg-1;
			if (op == BF_ListRevRefIf && arg < 4)
			{	// modify condition settings to reflect "!= 0" condition
				bArgCondRightParsed = TRUE;
				bArgCondParsed = TRUE;
				iArgCondition = 269;  // NEQ
				dArgCond[1] = 0.0;
			}
			if (bArgumentConditionExpected && !bCondArgsNext)
				bCondArgsNext = TRUE;	// once three consecutive string arguments encountered, assume the next is part of a conditional statement
		}

		if (bStoreArgsForProcessing)
			pOrigNodes[arg-1] = pThisNode;
		else
      	ExpxNodeDelete( pThisNode );
   }

	BOOL bReturnUNDEFINED = FALSE;  // SAC 4/19/13
   if (!bAbort)
   {
      int iObjIdx = -1;
	   int iNumObjs = 0;
	   int iError = 0, iStatus, iSpecialVal;
	   int iObj = 0;
      BEM_ObjType eObjType = BEMO_User;
		int iModelPrimObjIdx = pEval->iPrimObjIdx;  // SAC 4/3/13 - revision to enable child summing from the model specified by i0Model
		if (i0Model >= 0 &&
				op != BF_SumAll && op != BF_MaxAll && op != BF_MinAll)  // SAC 5/12/14 - PREVENT model-specific index retrieval for functions that do not take advantage of iModelPrimObjIdx
			iModelPrimObjIdx = BEMPX_GetObjectIndexAcrossModels( BEMPX_GetClassID( pEval->lPrimDBID ), i0Model, pEval->ePrimObjType, pEval->iPrimObjIdx /*, int iInModel=-1*/ );
		else if (i0Model >= 0)
		{	assert( !bRevRefFunc && !bGetCount && op != BF_SumAcrsIf &&		// make SURE that iModelPrimObjIdx is not going to be used if we skipped setting it above
						op != BF_SumChld && op != BF_MaxChild && op != BF_MinChild && op != BF_SumChldIf && op != BF_MaxChildC && op != BF_MinChildC );   // SAC 10/18/14
		}

      // Get occurrence index for first data retrieval based on Local/Parent/ChildRef type
      QString sErrMsg;
      int i1ChildClass  = 0;
      int i1ParentClass = 0;
      BEMObject* pPrimObj = NULL;
		vector<int> iaChildObjIdxs;
		// SAC 1/3/02 - Added code to handle new BF_Count*Refs functions
      if ( op == BF_SumAll || op == BF_MaxAll || op == BF_MinAll || bRevRefFunc || bGetCount ||
		     op == BF_MaxAllComp || op == BF_SumAcrsIf )  // SAC 2/1/02 - added BF_MaxAllComp  // SAC 3/5/13 - BF_SumAcrsIf
      {
         iNumObjs = BEMPX_GetNumObjects( BEMPX_GetClassID( plParams[ 0 ] ), pEval->ePrimObjType, i0Model );

         if (bRevRefFunc || bGetCount)
         {
            int iTmpErr = 0;
				//int iPObjIdx = (i0Model < 0 ? pEval->iPrimObjIdx : 
				//						BEMPX_GetObjectIndexAcrossModels( BEMPX_GetClassID( pEval->lPrimDBID ), i0Model, pEval->ePrimObjType, pEval->iPrimObjIdx /*, int iInModel=-1*/ ));
            //pPrimObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iTmpErr, iPObjIdx, pEval->ePrimObjType, i0Model );
            pPrimObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( pEval->lPrimDBID ), iTmpErr, iModelPrimObjIdx, pEval->ePrimObjType, i0Model );
         }
      }
      else if (op == BF_SumChld || op == BF_MaxChild || op == BF_MinChild || op == BF_SumChldIf || op == BF_MaxChildC || op == BF_MinChildC)  // SAC 3/5/13 - BF_SumChldIf  // SAC 10/18/14
      {
         i1ChildClass  = BEMPX_GetClassID( plParams[ 0 ] );
         i1ParentClass = BEMPX_GetClassID( pEval->lPrimDBID );
			//assert( i0Model<0 || i0Model==BEMPX_GetActiveModel() );  - SAC 4/3/13 - should be OK to span models now
		//	iNumObjs = (int) BEMPX_GetNumChildren( pEval->lPrimDBID, iModelPrimObjIdx, pEval->ePrimObjType, i1ChildClass, i0Model );
		// SAC 6/3/13 - added code to traverse ALL children, grandchildren, greatgrand... for all possible obejcts of the specified child class and archive their object indexes for later reference
			assert( i1ParentClass != i1ChildClass );
			if (i1ParentClass == i1ChildClass)	// SAC 6/1/16 - added error
         {	bAbort = TRUE;
  	         ExpSetErr( error, EXP_RuleProc, "Parent and child objects of same type" );
  	      }
  	      else
  	      {
  	      	BEMObject* pThisObj = BEMPX_GetObjectByClass( i1ParentClass, iError, iModelPrimObjIdx, BEMO_User, i0Model );		assert( pThisObj );
				vector<BEMObject*> paAllChildObjs;
				vector<int> iaAllChildObjGens;
				paAllChildObjs.push_back( pThisObj );
				iaAllChildObjGens.push_back( 0 );
				int iChildIdx = 0;
				while (iChildIdx < (int) paAllChildObjs.size())
				{	StoreChildObjectPtrs( paAllChildObjs[iChildIdx], iaAllChildObjGens[iChildIdx], paAllChildObjs, iaAllChildObjGens );	// no child can belong to mulitple parents, so there should be no threat of duplicates stored in this vector
					iChildIdx++;
				}
				// now paAllChildObjs vector is populated w/ EVERY descendant of the parent object (and even the parent object itself)
				// now check each of these obejcts and store it in array of child objects that will be looped over when processing...
				iNumObjs = (int) paAllChildObjs.size();
		// SAC 4/20/15 - REMOVED restriction that child objects traversed for mins/maxs/sums be from a single generation (of child objects)
		//		int iChildGen = -1;  // added iChildGen check to ensure that children of only a FIXED, SINGLE generation are referenced in the sum/min/max/... function execution
		      for (iObj=0; iObj<iNumObjs; iObj++)
				{	pThisObj = paAllChildObjs[iObj];
					if (pThisObj && pThisObj->getClass() && pThisObj->getClass()->get1BEMClassIdx() == i1ChildClass)
					{	iChildIdx = BEMPX_GetObjectIndex( pThisObj->getClass(), pThisObj, i0Model );							assert( iChildIdx >= 0 );
						if (iChildIdx >= 0)
						{	//if (iChildGen < 0)
							//	iChildGen = iaAllChildObjGens[iObj];
							//assert( iaAllChildObjGens[iObj] >= iChildGen );		// once we have found the FIRST child generation encountered, we shouldn't come across another object at a more senior generation
							//if (iaAllChildObjGens[iObj] == iChildGen)
		// SAC 5/29/15 - revised above code to account for new argument which specifies a certain child generation (1-10) OR the case where only the first encountered generation should be traversed (0)
							if (iOnlyChildGen == 0)	// initial setting of 0 causes only the first encountered generation to be processed - like the original code did
								iOnlyChildGen = iaAllChildObjGens[iObj];
							if (iOnlyChildGen == -1 || iaAllChildObjGens[iObj] == iOnlyChildGen)
								iaChildObjIdxs.push_back( iChildIdx );
						}
					}
				}
				iNumObjs = (int) iaChildObjIdxs.size();
			}
      }
      else
      {	bAbort = TRUE;
         ExpSetErr( error, EXP_RuleProc, "Invalid BEMProcSumChildrenAllOrRevRef() Operation Code" );
      }

		// SAC 8/1/06 - added code to handle fourth & fifth arguments to SumRevRefEx()
      int iExtendedFlag = 0;
      long lExtDBID = 0;
      if (op == BF_SumRevRefEx)
      {
         assert( nArgs==5 );
         lExtDBID      = plParams[--nArgs];
         iExtendedFlag = plParams[--nArgs];        assert( iExtendedFlag > 0 && iExtendedFlag  < 4 );  // limited to 1-3 for the time being
      }

		// SAC 2/17/04 - Added code to handle new optional FOURTH argument to MaxRevRefComp function
      long lFlagValDBID = 0;  // if this DBID is set, then it must return a non-zero value in order for the selected component to be considered as a return value
      if ( op == BF_MaxRevRefC  &&  nArgs > 3 )
      {
         lFlagValDBID = plParams[nArgs-1];
         nArgs--;
      }

		// SAC 11/10/04 - Added code to handle new optional FOURTH argument to MaxRevRefArray function
      double dLowestMaxVal = -99999999.0;
      if ( op == BF_MaxRevRefA  &&  nArgs > 3 )
      {
         dLowestMaxVal = plParams[nArgs-1] - 0.000001;  // decrement slightly to enable a value EQUAL to this minimum to get caught
         nArgs--;
      }

		// SAC 1/9/02 - Added code to handle third argument to new MaxRevRefComp function
      long lNumParentGenerations = 0;
      if ( (op == BF_MaxRevRefC  &&  nArgs > 2) ||
           (op == BF_MaxAllComp  &&  nArgs > 1) )  // SAC 1/25/02
      {
         lNumParentGenerations = plParams[nArgs-1];
         nArgs--;
      }

		// SAC 5/4/06 - implemented CountOccurrences() - first argument should be Comp:Param string, second a number
      long lCountOccurVal = 0;
      if (op == BF_CountOccur && nArgs > 1)
      {
         lCountOccurVal = plParams[1];
         nArgs--;
      }

		// SAC 1/3/02 - Added code to handle new third argument to *RevRef & second argument of Count*Refs functions
      long lMaxArrayDBID = 0;
      if ( (nArgs > 2 && bRevRefFunc && !bStoreArgsForProcessing) || (nArgs > 1 && bGetCount) )
      {
         lMaxArrayDBID = plParams[nArgs-1];  // SAC 1/27/17 - modified to be EITHER DBID or numeric constant (1-based max array index)
         nArgs--;
      }

		// SAC 6/14/00 - added code to perform RevRef functions over entire array if both assignment and sum/min/max arguments are arrays of the same length
      int iStartArg = 0;
      int iArrIdxLast = 0;
      if ( bGetCount && BEMPX_GetArrayID( plParams[0] ) < 2 && !bAbort )
      {
         int iSizeArg0Arr = BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[0], i0Model );
         if (iSizeArg0Arr > 1)
            iArrIdxLast = iSizeArg0Arr-1;
         iStartArg++;
      }
      else if ( bRevRefFunc && !bStoreArgsForProcessing && nArgs > 1 && BEMPX_GetArrayID( plParams[0] ) < 2  &&  BEMPX_GetArrayID( plParams[1] ) < 2 && !bAbort )
      {
         int iSizeArg0Arr = BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[0], i0Model );
         if (iSizeArg0Arr > 1  &&  iSizeArg0Arr == BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[1], i0Model ))
            iArrIdxLast = iSizeArg0Arr-1;
         iStartArg++;
      }
		// SAC 6/13/05 - Fixed bug where MaxRevRef() not working when second argument specifies particular array index
      else if ( bRevRefFunc && !bStoreArgsForProcessing && nArgs > 1 &&  BEMPX_GetArrayID( plParams[0] ) != BEMPX_GetArrayID( plParams[1] ) && !bAbort )
         iStartArg++;

      assert( (!bGetCount || nArgs == iStartArg || BEMPX_GetArrayID( plParams[0] ) > 1) );  // SAC 1/3/02
#ifdef _DEBUG
				if (bGetCount && nArgs != iStartArg && BEMPX_GetArrayID( plParams[0] ) < 2)
         	{	QString dbgMsg;   dbgMsg = QString( "         BEMProcSumChildrenAllOrRevRef() Error: (bGetCount(true) && nArgs(%1) != iStartArg(%2)) evaluating %3" ).arg(
         											QString::number(nArgs), QString::number(iStartArg), pEval->sRuleID );
         		//errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
         		BEMPX_WriteLogFile( dbgMsg );
               //ruleSet.logMsgCallback( logMsgMESSAGE, sRetStr, NULL );
				}
#endif

      fResult = (bGetMax ? dLowestMaxVal : (bGetMin ? 99999999.0 : 0.0));   // SAC 11/10/04 - added new dLowestMaxVal variable
      vector<int> iaParentObjIdxs;  // SAC 1/4/02
      vector<int> ivObjIdxs;	// SAC 1/26/15
      int iMinMaxObjIdx = -1;
      for (iObj=0; (!bAbort) && (iObj<iNumObjs); iObj++)
      {
			// SAC 1/3/02 - Added code to limit array looping via new third argument to *RevRef & second argument of CountRefs
         int iArrLoopMax = iArrIdxLast;
         if (lMaxArrayDBID > 0)
         {
         	if (lMaxArrayDBID <= (iArrIdxLast+1))  // SAC 1/27/17 - enable second Count*Refs argument to be constant value representing max array element checked for references
               iArrLoopMax = lMaxArrayDBID-1;
         	else
         	{
	      //      double fMaxArr;
	      //      if (BEMPX_SetDataFloat( lMaxArrayDBID, fMaxArr, 1000, -1, iObj, BEMO_User, i0Model )  &&  (fMaxArr+0.1) > 0  &&  (fMaxArr-0.1) < iArrLoopMax)
	            double fMaxArr = BEMPX_GetFloatAndStatus( lMaxArrayDBID, iStatus, iSpecialVal, iError, iObj, BEMO_User, i0Model, true );
					if (iStatus > 0  &&  (fMaxArr+0.1) > 0  &&  (fMaxArr-0.1) < iArrLoopMax)
	               iArrLoopMax = (int) (fMaxArr+0.1) - 1;
	            else if ((fMaxArr-0.1) > (iArrLoopMax+1))	// SAC 9/13/13 - fixed bug where fMax which would cause iArrLoopMax to be unchanged was throwing error
	            {
	               ExpSetErr( error, EXP_RuleProc, "Unable to load array loop maximum index" );
	               bAbort = TRUE;
	               assert( FALSE );
            }	}
         }

			// SAC 6/14/00 - added code to perform RevRef functions over entire array if both assignment and sum/min/max arguments are arrays of the same length
         BOOL bBailOutOfArrayLoop = FALSE;  // SAC 1/4/02
         for (int iArr=0; (!bAbort && !bBailOutOfArrayLoop && iArr <= iArrLoopMax); iArr++)
         {
            int iDataStatus, iDataType, iExDataStatus, iExDataType, iSpecialVal;
            BEMObject* pObj = NULL;

            // Set iObjIdx & eObjType
            if ( op == BF_SumAll || op == BF_MaxAll || op == BF_MinAll || op == BF_MaxAllComp ||  // SAC 1/25/02
                 op == BF_CountOccur || op == BF_SumAcrsIf )  // SAC 5/4/06   // SAC 3/5/13 - BF_SumAcrsIf
            {
               iObjIdx = iObj;
               eObjType = pEval->ePrimObjType;
            }
            else if (bRevRefFunc || bGetCount)
            {
               iObjIdx = -1;
         //      pObj = (BEMObject*) BEMPX_GetData( plParams[0]+iArr, iDataType, iSpecialVal, iError, iObj, pEval->ePrimObjType, FALSE, i0Model );
               pObj = BEMPX_GetObjectAndStatus( plParams[0]+iArr, iDataStatus, iSpecialVal, iError, iObj, pEval->ePrimObjType, i0Model );
               if (iError >= 0 && iDataStatus > 0 && pObj && pObj == pPrimObj)
               {
                  if (bGetCount)
                  {
							// SAC 1/4/02 - Added code to handle new BF_CountUPRefs function
                     BOOL bIncCount = TRUE;
                     if (op == BF_CountUPRefs)
                     {
								// SAC 12/26/07 - fix to code that evaluates CountUniqueParentRefs() - last version was performing unique parent ref check on Primary object and not object being looped over
                        BEMObject* pObj2 = BEMPX_GetObjectByClass( BEMPX_GetClassID( plParams[0] ), iError, iObj, pEval->ePrimObjType, i0Model );       assert( pObj2 );
                        if (pObj2 == NULL || pObj2->getParent() == NULL || pObj2->getParent()->getClass() == NULL)
                           bIncCount = FALSE;
                        else
                        {
                           int iParObjIdx = BEMPX_GetObjectIndex( pObj2->getParent()->getClass(), pObj2->getParent(), i0Model );
                           for (int iPOI=0; (bIncCount && iPOI<(int) iaParentObjIdxs.size()); iPOI++)
                              bIncCount = (iParObjIdx != iaParentObjIdxs[iPOI]);
               
                           if (bIncCount)
                           {
                              bBailOutOfArrayLoop = TRUE;
                              iaParentObjIdxs.push_back( iParObjIdx );
                           }
                        }
                     }
                     if (bIncCount)
                        fResult += 1.0;
                  }
                  else
                  {
                     iObjIdx = iObj;
                     eObjType = pEval->ePrimObjType;
                  }
               }

					// SAC 2/17/04 - Added code to handle new optional FOURTH argument to MaxRevRefComp function
               if (iObjIdx >= 0  &&  lFlagValDBID > 0)
               {
                  long lFlagVal;
                  if (!BEMPX_GetInteger( lFlagValDBID, lFlagVal, 0, -1, iObjIdx, BEMO_User, i0Model ) || lFlagVal <= 0)
                     iObjIdx = -1;
               }
            }
            else
			//		iObjIdx = BEMPX_GetChildObjectIndex( i1ParentClass, i1ChildClass, iError, eObjType,
			//															iObj+1, iModelPrimObjIdx /*pEval->iPrimObjIdx*/, pEval->ePrimObjType, i0Model );
			// SAC 6/3/13 - continuation of fix to ensure that ALL descendants
					iObjIdx = iaChildObjIdxs[iObj];

            if (op == BF_CountOccur || !bGetCount)  // SAC 5/4/06
            {
               // Retrieve data from database
               // First loop over all but last Comp:Param IDs, getting objects along the way
					int iFirstArgArgs = (bStoreArgsForProcessing ? 0 : (nArgs-1));		// SAC 1/26/15
               for (int i=iStartArg; (iObjIdx > -1) && (iError >= 0) && (i < iFirstArgArgs); i++)
               {
            //      pObj = (BEMObject*) BEMPX_GetData( plParams[i], iDataType, iSpecialVal, iError, iObjIdx, eObjType, FALSE, i0Model );
						pObj = BEMPX_GetObjectAndStatus( plParams[i], iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, i0Model );
                  if (iError >= 0 && iDataStatus > 0 && pObj)
                  {
                     iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj, i0Model );
                     eObjType = pObj->getObjectType();
                  }
                  else
                     iObjIdx = -1;
               }

               // Retrieve and add data associated with last Comp:Param node to fResult
               if ( (iObjIdx >= 0) && (iError >= 0) )
               {
						// SAC 8/1/06 - added code to handle fourth & fifth arguments to SumRevRefEx()
                  BOOL bSumThisOne = TRUE;
                  double fExVal = 0;
                  if (bArgumentConditionExpected && bArgCondLeftParsed)
						{	bSumThisOne = FALSE;
							int iLR;
							BOOL bIsNumeric[2]={FALSE,FALSE}, bIsString[2]={FALSE,FALSE};
							QString sValCond[2];
							double dValCond[2]={-99999,-99999};
							for (iLR=0; iLR<2; iLR++)
							{	if (!sArgCond[iLR].isEmpty())
								{	bIsString[iLR] = TRUE;
									sValCond[iLR] = sArgCond[iLR];
								}
								else if (!WithinMargin( dArgCond[iLR], -99999.0, 0.1 ))
								{	bIsNumeric[iLR] = TRUE;
									dValCond[iLR] = dArgCond[iLR];
								}
								else
								{	int iValErr;
									BEMProperty* pValProp = NULL;
									int iValObjIdx = -1;
									BEM_ObjType eValObjType = BEMO_User;
									BOOL bErrorPosted = FALSE;
									if (BEMPX_GetNumObjects( iArgCond1Class[iLR], eObjType, i0Model /*iBEMProcIdx*/ ) == 1)	// SAC 1/27/15 - enable Global (single object occurrence) data retrieval
									{	pValProp = BEMPX_GetProperty( lArgCondDBID[iLR], iValErr, 0 /*iObjIdx*/, eObjType, i0Model /*0 iBEMProcIdx*/ );
										iValObjIdx = 0 /*iObjIdx*/;		eValObjType = eObjType;
									}
									else if (op == BF_SumAcrsIf || op == BF_ListRevRefIf)
									{	if (iArgCond1Class[iLR] == BEMPX_GetClassID( plParams[ 0 ] ))
										{	pValProp = BEMPX_GetProperty( lArgCondDBID[iLR], iValErr, iObjIdx, eObjType, i0Model /*0 iBEMProcIdx*/ );
											iValObjIdx = iObjIdx;		eValObjType = eObjType;
										}
										else if (iArgCond1Class[iLR] == BEMPX_GetClassID( pEval->lPrimDBID ))
										{	pValProp = BEMPX_GetProperty( lArgCondDBID[iLR], iValErr, iModelPrimObjIdx /*pEval->iPrimObjIdx*/, pEval->ePrimObjType, i0Model /*0 iBEMProcIdx*/ );
											iValObjIdx = iModelPrimObjIdx /*pEval->iPrimObjIdx*/;		eValObjType = pEval->ePrimObjType;
										}
										else
										{	//assert( FALSE );  // only local & primary conditional data retrieval for now ... ??
											bErrorPosted = TRUE;
											sErrMsg = QString( "Condition look-ups restricted to local/looping and primary objects (%1)" ).arg( (op == BF_SumAcrsIf ? "SumAcrossIf" : (op == BF_ListRevRefIf ? "ListRevRef" : "???")) );
	                              ExpSetErr( error, EXP_RuleProc, sErrMsg );
										}
									}
									else // BF_SumChldIf
									{	if (iArgCond1Class[iLR] == i1ChildClass)
										{	pValProp = BEMPX_GetProperty( lArgCondDBID[iLR], iValErr, iObjIdx, eObjType, i0Model /*0 iBEMProcIdx*/ );
											iValObjIdx = iObjIdx;		eValObjType = eObjType;
										}
										else
										{	int iNumParGens=0;
											BEMObject*	pParent = BEMPX_GetObjectByClass( (int) i1ChildClass, iValErr, iObjIdx, eObjType, i0Model /*0 iBEMProcIdx*/ );  // assert( pParent );
											if (pParent)
												pParent = pParent->getParent();
											while (pParent && pValProp == NULL && ++iNumParGens < 15)
											{
												if (iArgCond1Class[iLR] == pParent->getClass()->get1BEMClassIdx())
												{	iValObjIdx = BEMPX_GetObjectIndex( pParent->getClass(), pParent, i0Model /*0 iBEMProcIdx*/ );
													eValObjType = pParent->getObjectType();
													pValProp = BEMPX_GetProperty( lArgCondDBID[iLR], iValErr, iValObjIdx, eValObjType, i0Model /*0 iBEMProcIdx*/ );			assert( pValProp );
												}
												else
													pParent = pParent->getParent();
											}
											if (pValProp == NULL)
											{	assert( FALSE );  // condition object not found in parent/child tree ... ??
												bErrorPosted = TRUE;
	                           	   ExpSetErr( error, EXP_RuleProc, "Object condition depends on not found in parent hierarchy (SumChildrenIf)" );
											}
										}
									}
									if (pValProp == NULL && !bErrorPosted)
									{	assert( FALSE );  // unable to locate condition value/string ... ??
										bErrorPosted = TRUE;
	                           ExpSetErr( error, EXP_RuleProc, "Object condition depends on not found (Sum*If)" );
									}
									else if (pValProp && pValProp->getType())
									{	switch (pValProp->getType()->getPropType())
										{	case BEMP_Int	:	bIsNumeric[iLR] = TRUE;		dValCond[iLR] = (double) pValProp->getInt();			break;
											case BEMP_Flt	:	bIsNumeric[iLR] = TRUE;		dValCond[iLR] = (double) pValProp->getDouble();		break;
											case BEMP_Sym	:	bIsNumeric[iLR] = TRUE;		dValCond[iLR] = (double) pValProp->getInt();
																	bIsString[iLR] = TRUE;		sValCond[iLR] = BEMPX_GetSymbolString( pValProp->getInt(), lArgCondDBID[iLR], iValObjIdx, eValObjType, i0Model /*0 iBEMProcIdx*/ );  break;
//const char* __cdecl BEMPX_GetSymbolString( long iSymVal, long lDBID, int iOccur=-1,
//                                         BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
											case BEMP_Str	:	bIsString[iLR] = TRUE;		sValCond[iLR] = pValProp->getString();					break;
											case BEMP_Obj	:	if (pValProp->getObj())
																	{	dValCond[iLR] = (double) BEMPX_GetObjectIndex( pValProp->getObj()->getClass(), pValProp->getObj(), i0Model /*0 iBEMProcIdx*/ );
																		bIsNumeric[iLR] = (dValCond[iLR] >= 0);
																		sValCond[iLR] = (pValProp->getObj() ? pValProp->getObj()->getName() : "");
																		bIsString[iLR] = (!sValCond[iLR].isEmpty());
																	}
																	else
																	{	assert( false );	// SAC 9/25/16 - condition not covered in earlier code ??
																		dValCond[iLR] = 0.0;
																		bIsNumeric[iLR] = FALSE;
																		sValCond[iLR].clear();
																		bIsString[iLR] = FALSE;
																	}											break;
											default			:	assert( FALSE );		break;
										}
									}
								}	// end of if ArgCond is a DBID...
							}	// end of loop over two side of condition

							if (bIsString[0] && bIsString[1])
							{	// STRING comparison
								switch (iArgCondition)
								{	case EQ :	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) == 0);		break;	// was: _stricmp()
									case NEQ:	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) != 0);		break;
									case LT :	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) <  0);		break;
									case GT :	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) >  0);		break;
									case LE :	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) <= 0);		break;
									case GE :	bSumThisOne = (sValCond[0].compare( sValCond[1], Qt::CaseInsensitive ) >= 0);		break;
									default :	bSumThisOne = FALSE;		assert( FALSE );		break;
								}
							}
							else if (bIsNumeric[0] && bIsNumeric[1])
							{	// NUMERIC comparison
								switch (iArgCondition)
					//			{	case EQ :	bSumThisOne = (dValCond[0] == dValCond[1]);		break;
					//				case NEQ:	bSumThisOne = (dValCond[0] != dValCond[1]);		break;
					//				case LT :	bSumThisOne = (dValCond[0] <  dValCond[1]);		break;
					//				case GT :	bSumThisOne = (dValCond[0] >  dValCond[1]);		break;
					//				case LE :	bSumThisOne = (dValCond[0] <= dValCond[1]);		break;
					//				case GE :	bSumThisOne = (dValCond[0] >= dValCond[1]);		break;
					//				default :	bSumThisOne = FALSE;		assert( FALSE );			break;		- SAC 4/21/17 - replaced w/ below to better handle floating point representation issues
								{	case EQ :	bSumThisOne = (AreSame( dValCond[0], dValCond[1] )   );		break;
									case NEQ:	bSumThisOne = (AreSame( dValCond[0], dValCond[1] )==0);		break;
									case LT :	bSumThisOne = (dValCond[0] < dValCond[1] && AreSame( dValCond[0], dValCond[1] )==0);		break;
									case GT :	bSumThisOne = (dValCond[0] > dValCond[1] && AreSame( dValCond[0], dValCond[1] )==0);		break;
									case LE :	bSumThisOne = (dValCond[0] < dValCond[1] || AreSame( dValCond[0], dValCond[1] )   );		break;
									case GE :	bSumThisOne = (dValCond[0] > dValCond[1] || AreSame( dValCond[0], dValCond[1] )   );		break;
									default :	bSumThisOne = FALSE;		assert( FALSE );			break;
								}
							}
							else
							{	assert( FALSE );
							}
						}
						else if (iExtendedFlag)
                  {
               //      void* pData = (void*) BEMPX_GetDataAndStatus( lExtDBID+iArr, iExDataStatus, iExDataType, iSpecialVal, iError, iObjIdx, eObjType, FALSE, i0Model );
               //      if (pData != NULL)
               //      {
               //         // SAC 8/7/10 - implementation of targeted debug output
               //         if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lExtDBID+iArr, iObjIdx ))
               //            ReportTagetedDebugInfo( pEval, iExDataType, lExtDBID+iArr, iObjIdx, eObjType, "BEMProcSumChildrenAllOrRevRef()-1", i0Model );
					// SAC 9/5/16 - replaced above w/ following (during open source conversions)
							iExDataType = BEMPX_GetDataType( lExtDBID + iArr );
							if ((iExDataType == BEMP_Int || iExDataType == BEMP_Sym || iExDataType == BEMP_Flt) &&
								 pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lExtDBID+iArr, iObjIdx ))
								ReportTargetedDebugInfo( pEval, iExDataType, lExtDBID+iArr, iObjIdx, eObjType, "BEMProcSumChildrenAllOrRevRef()-1", i0Model );
							long lData=0;		double dData=0.0;		iDataStatus=0;
							if (iExDataType == BEMP_Int || iExDataType == BEMP_Sym)
								lData = BEMPX_GetIntegerAndStatus( lExtDBID+iArr, iExDataStatus, iSpecialVal, iError, iObjIdx, eObjType, i0Model );
							else if (iExDataType == BEMP_Flt)
								dData = BEMPX_GetFloatAndStatus(   lExtDBID+iArr, iExDataStatus, iSpecialVal, iError, iObjIdx, eObjType, i0Model );

							if (iExDataStatus < 1)		// handle case where property is UNDEFINED
							{	// what to do if "extended" data is UNDEFINED ??
							}
                     else if (iExtendedFlag == 1)
                     {
                        if (iExDataType == BEMP_Int || iExDataType == BEMP_Sym)
                           bSumThisOne = (lData != 0);
                        else if (iExDataType == BEMP_Flt)
                           bSumThisOne = (!WithinMargin( dData, 0, 0.001 ));
                        else
                        {  ExpSetErr( error, EXP_RuleProc, "Data Type Not Usable to Determine Whether or Not to Sum Value" );
                           bAbort = TRUE;
                        }
                     }
                     else
                     {
                        if (iExDataType == BEMP_Int || iExDataType == BEMP_Sym)
                           fExVal = (double) lData;
                        else if (iExDataType == BEMP_Flt)
                           fExVal = dData;
                        else
                        {
                           ExpSetErr( error, EXP_RuleProc, "Data Type Not Usable to Sum Into or Multiply By" );
                           bAbort = TRUE;
                        }
                     }
                  }

                  if (bSumThisOne)   // SAC 8/1/06
	               {
		               if (bStoreArgsForProcessing)	// SAC 1/26/15 - store index of each object to echo via ListRevRef* function
						      ivObjIdxs.push_back( iObjIdx );
		               else
                     {
               //      	void* pData = (void*) BEMPX_GetDataAndStatus( plParams[ nArgs-1 ]+iArr, iDataStatus, iDataType, iSpecialVal, iError, iObjIdx, eObjType, FALSE, i0Model );
	            //      	if (pData != NULL)
	            //      	{
               //      	   // SAC 8/7/10 - implementation of targeted debug output
               //      	   if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( plParams[ nArgs-1 ]+iArr, iObjIdx ))
               //      	      ReportTargetedDebugInfo( pEval, iDataType, plParams[ nArgs-1 ]+iArr, iObjIdx, eObjType, "BEMProcSumChildrenAllOrRevRef()-2", i0Model );
					// SAC 9/5/16 - replaced above w/ following (during open source conversions)
								iDataType = BEMPX_GetDataType( plParams[ nArgs-1 ]+iArr );
								if ((iDataType == BEMP_Int || iDataType == BEMP_Sym || iDataType == BEMP_Flt) &&
									 pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( plParams[ nArgs-1 ]+iArr, iObjIdx ))
									ReportTargetedDebugInfo( pEval, iDataType, plParams[ nArgs-1 ]+iArr, iObjIdx, eObjType, "BEMProcSumChildrenAllOrRevRef()-2", i0Model );
								long lData=0;		double dData=0.0;		iDataStatus=0;
								if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
									lData = BEMPX_GetIntegerAndStatus( plParams[ nArgs-1 ]+iArr, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, i0Model );
								else if (iDataType == BEMP_Flt)
									dData = BEMPX_GetFloatAndStatus(   plParams[ nArgs-1 ]+iArr, iDataStatus, iSpecialVal, iError, iObjIdx, eObjType, i0Model );

									if (iDataStatus < 1)		// handle case where property is UNDEFINED
									{	// data undefined
									// do nothing if data to be summed is undefined
	                     	//   QString sBEMProcErr;  // SAC 12/24/07 - added more verbose BEMProc retrieval info
	                     	//   PopulateBEMProcInfo( sBEMProcErr, plParams[ nArgs-1 ]+iArr, iObjIdx, eObjType, i0Model, "Data Retrieval from BEMProc failed (", ") in BEMProcSumChildrenAllOrRevRef()" );
// INSERT , iBEMProcModel  as 5th argument
	                     	//   ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
	                     	//   bAbort = TRUE;
									}
                     		else if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
                     		{  // Get long data
                     		   if (op == BF_CountOccur)  // SAC 5/4/06
                     		   {
                     		      if (lData == lCountOccurVal)
                     		         fResult += 1.0;
                     		   }
                     		   else
                     		   {
                     		      dData = (double) lData;
                     		      if (iExtendedFlag == 2)  // SAC 8/1/06
                     		         dData += fExVal;
                     		      else if (iExtendedFlag == 3)
                     		         dData *= fExVal;
                     	
                     		      if (!bGetMax && !bGetMin)
                     		         fResult += dData;
                     		      else if (bGetMax && dData > fResult)
                     		      {
                     		         iMinMaxObjIdx = iObjIdx;
                     		         iMinMaxArrIdx = iArr;   // SAC 11/10/04 - for BF_MaxRevRefA
                     		         fResult = dData;
                     		      }
                     		      else if (bGetMin && dData < fResult)
                     		      {
                     		         iMinMaxObjIdx = iObjIdx;
                     		         iMinMaxArrIdx = iArr;   // SAC 11/10/04 - for BF_MaxRevRefA
                     		         fResult = dData;
                     		      }
                     		   }
                     		}
                     		else if (iDataType == BEMP_Flt)
                     		{  // Get float data
                     		   if (iExtendedFlag == 2)  // SAC 8/1/06
                     		      dData += fExVal;
                     		   else if (iExtendedFlag == 3)
                     		      dData *= fExVal;
                     	
                     		   if (!bGetMax && !bGetMin)
                     		      fResult += dData;
                     		   else if (bGetMax && dData > fResult)
                     		   {
                     		      iMinMaxObjIdx = iObjIdx;
                     		      iMinMaxArrIdx = iArr;   // SAC 11/10/04 - for BF_MaxRevRefA
                     		      fResult = dData;
                     		   }
                     		   else if (bGetMin && dData < fResult)
                     		   {
                     		      iMinMaxObjIdx = iObjIdx;
                     		      iMinMaxArrIdx = iArr;   // SAC 11/10/04 - for BF_MaxRevRefA
                     		      fResult = dData;
                     		   }
                     		}
                     		else
                     		{
                     		   ExpSetErr( error, EXP_RuleProc, "Data Type Incompatible with Summing" );
                     		   bAbort = TRUE;
                     		}
                     }	// SAC 1/26/15 - new else for when NOT processing ListRevRef... function arguments
                  }
               }
            }
         }
      }

		if (bStoreArgsForProcessing)	// SAC 1/26/15 - added logic to process ListRevRef* function formatting/populating arguments
		{
			int iNumProcObjs = (int) ivObjIdxs.size();
			if (iNumProcObjs > 0)
			{	int i, iNumFmtArgs = iNumOrigNodes - i0FirstFormatStrArgIdx - 3;
				if (i0FirstFormatStrArgIdx < 1 || iNumFmtArgs < 1 || iNumFmtArgs > 30)
				{	if (i0FirstFormatStrArgIdx < 1)
						ExpSetErr( error, EXP_RuleProc, "Format string arguments not found" );
					else if (iNumFmtArgs < 1)
						ExpSetErr( error, EXP_RuleProc, "No arguments found following formatting strings" );
					else if (iNumFmtArgs > 30)
						ExpSetErr( error, EXP_RuleProc, "Too many arguments found following formatting strings (max of 30)" );
					bAbort = TRUE;
				}
				else
				{	ExpNode* pFmtNodes[30];
					ExpNode tempNodes[30];
					for (i=0; i<iNumFmtArgs; i++)
						ExpNode_init( &tempNodes[i] );	// SAC 4/21/17
				//	{	tempNodes[i].type = EXP_Invalid;
				//		tempNodes[i].fValue = 0;
				//	}
					int iProcObjIdx=0;
					int iFirstProcNodeIdx = i0FirstFormatStrArgIdx + 3;
					std::vector<int>::iterator it = ivObjIdxs.begin();
					for (; (it < ivObjIdxs.end() && !bAbort); it++)
					{	iProcObjIdx++;
						// process each argument following formatting strings into values/strings to be inserted into formatted list
						for (i=0; (i<iNumFmtArgs && !bAbort); i++)
						{	if (pOrigNodes[iFirstProcNodeIdx+i]->type == EXP_String ||
								(pOrigNodes[iFirstProcNodeIdx+i]->type == EXP_Value && pOrigNodes[iFirstProcNodeIdx+i]->fValue < BEM_COMP_MULT))
							{	// no processing of string or value not a DBID required - pass directly into format string population routine
								pFmtNodes[i] = pOrigNodes[iFirstProcNodeIdx+i];
							}
							else if (pOrigNodes[iFirstProcNodeIdx+i]->type == EXP_Value)
							{	long lDBID, iThisModel = i0Model;
								lMDBID = (long long) pOrigNodes[iFirstProcNodeIdx+i]->fValue;
								GetBEMProcDataToNode( &tempNodes[i], lMDBID, *it, eObjType, error, ruleSet.IsDataModel()/*bGetSymStr*/, pEval, TRUE /*bReturnInvalidWhenUndefined*/ );
								if (tempNodes[i].type == EXP_Invalid)
								{  QString sBEMProcErr;
									if (lMDBID > BEM_MODEL_MULT)
									{	lDBID = (long) BEMPX_MDBIDtoDBID( lMDBID );
										iThisModel = (int) BEMPX_GetModelID( lMDBID ) - 1;
									}
									else
										lDBID = (long) lMDBID;
                     	   PopulateBEMProcInfo( sBEMProcErr, lDBID, *it, eObjType, iThisModel, "Data Retrieval from BEMProc failed (", ") in BEMProcSumChildrenAllOrRevRef()" );
// INSERT , iBEMProcModel  as 5th argument
                     	   ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
                     	   bAbort = TRUE;
								}
								else
									pFmtNodes[i] = &tempNodes[i];
							}
						}
						if (!bAbort)
						{	QString sThisObj;
							int iFmtNodeIdx = i0FirstFormatStrArgIdx;
							if (iProcObjIdx > 1)
								iFmtNodeIdx += (iProcObjIdx == iNumProcObjs ? 2 : 1);

							if (ProcessFormatStatement( sThisObj, (const char*) pOrigNodes[iFmtNodeIdx]->pValue, pFmtNodes, iNumFmtArgs, error, true /*bPreserveNewlines*/ ))
								sResult += sThisObj;
							else
							{	ExpSetErr( error, EXP_RuleProc, "Error populating formatted string from function arguments in BEMProcSumChildrenAllOrRevRef()" );
								bAbort = TRUE;
							}
						}

						for (i=0; i<iNumFmtArgs; i++)
						{	if (tempNodes[i].type == EXP_String && tempNodes[i].pValue)
							{
                        free( tempNodes[i].pValue );
                        tempNodes[i].pValue = NULL;
                     }
                     tempNodes[i].type = EXP_Invalid;
                     tempNodes[i].fValue = 0;
						}
					}
			}	}
			else
				bReturnUNDEFINED = TRUE;	// no RevRef obejcts found to echo to result string
		}

		// SAC 1/9/02 - Added code to handle new MaxRevRefComp() function
      if (!bAbort  &&  (op == BF_MaxRevRefC || op == BF_MaxAllComp || op == BF_MaxChildC || op == BF_MinChildC))  // SAC 1/25/02  // SAC 10/18/14
      {
         if (iMinMaxObjIdx < 0)
				bReturnUNDEFINED = TRUE;  // SAC 4/19/13
         //{	assert( FALSE );
         //   ExpSetErr( error, EXP_RuleProc, "Error retrieving index of Min/Max component" );
         //   bAbort = TRUE;
         //}
         else
         {
            BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( plParams[ 0 ] ), iError, iMinMaxObjIdx, BEMO_User, i0Model );
            if (pObj == NULL)
            {
               ExpSetErr( error, EXP_RuleProc, "Error retrieving Min/Max component pointer" );
               bAbort = TRUE;
            }
            else
            {
               while (!bAbort && pObj && lNumParentGenerations > 0)
               {
                  pObj = pObj->getParent();
                  lNumParentGenerations--;
                  if (pObj == NULL)
                  {
                     ExpSetErr( error, EXP_RuleProc, "Error retrieving Min/Max parent component pointer" );
                     bAbort = TRUE;
                  }
               }
            }

            if (pObj)
            {
               assert( !pObj->getName().isEmpty() );
               sResult = pObj->getName();
            }
         }
      }
   }

	if (bStoreArgsForProcessing)	// delete original expression nodes if kept around during processing
	{	for (int arg = iNumOrigNodes; arg > 0; arg--)
			ExpxNodeDelete( pOrigNodes[arg-1] );
	}

   // Create, set and push result node
   ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
   if (bAbort)
      pNode->type = EXP_Invalid;
   else if (bReturnUNDEFINED)  // SAC 4/19/13
	{	pNode->type = EXP_Value;
		pNode->fValue = -99996;  // => UNDEFINED
	}
	else
   {
      if (!sResult.isEmpty())  // SAC 1/9/02 - added string return option for new MaxRevRefComp() function
      {
#pragma warning(disable : 4996)		// SAC 9/9/16
         pNode->type = EXP_String;
         pNode->pValue = malloc( sResult.length() + 1 );
         strcpy( (char*) pNode->pValue, (const char*) sResult.toLocal8Bit().constData() );
#pragma warning(default : 4996)
      }
      else
      {
//         if (bReturnArrayIdx)   // SAC 11/10/04 - for BF_MaxRevRefA
//            fResult = iMinMaxArrIdx;
//         // SAC 5/27/00 - set fResult to 0 if it has not changed from its original value
//         else if ( (bGetMax  &&  fResult == -99999999.0) ||
//                   (bGetMin  &&  fResult ==  99999999.0) )
//            fResult = 0;
//
//         pNode->type = EXP_Value;
//         pNode->fValue = fResult;
// SAC 8/20/13 - replaced above w/ the following to cause Min/Max return value to be UNCHANGED when no value found
         if ( (bGetMax  &&  WithinMargin( fResult, -99999999.0, 0.1 )) ||
              (bGetMin  &&  WithinMargin( fResult,  99999999.0, 0.1 )) )
			{	pNode->type = EXP_Value;
// SAC 9/3/14 - leading up to CBECC-Com v3 release - DR suggests switching Min/Max return value when not set to UNDEFINED, in place of UNCHANGED - to be considered @ a later date
         	pNode->fValue = -99997;   // = UNCHANGED
			}
			else
			{	if (bReturnArrayIdx)   // SAC 11/10/04 - for BF_MaxRevRefA
         	   fResult = iMinMaxArrIdx;

         	pNode->type = EXP_Value;
         	pNode->fValue = fResult;
			}
      }
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}

/////////////////////////////////////////////////////////////////////////////  - SAC 3/7/11
//
// Static Function:  ComponentArray()
//
// Purpose ------------------------------------------------------------------
//              ComponentArray( <OperationID#>, <Value#>, LocalDBID, Comp:ParamDBID ) - BF_CompArray
//              returns array of component references to LocalDBID based on Comp:ParamDBID meeting OperationID & Value condition
//              OperationIDs:  0==value / 1>=value / 2>value / 3<=value / 4<value
//   
// Arguments ----------------------------------------------------------------
//   int            op    : function enum
//   int            nArgs : number of arguments stored on stack
//   ExpStack*      stack : expression stack
//   ExpEvalStruct* pEval : structure containing data describing comp/param being evaluated
//   ExpError*      error : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   Number of components found and stored to array
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
static void ComponentArray( int /*op*/, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
   bool bAbort = FALSE;
   int iResult = 0;

   // Pop all (Comp:Param) nodes off stack and store in Long Array
   long   plParams[20];
   double pdParams[20];
	long long lMDBID;
	int i0Model = -1;
   for ( int arg = nArgs; arg > 0; arg-- )
   {
      ExpNode* pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
      {  bAbort = TRUE;
         ExpSetErr( error, EXP_RuleProc, "Invalid ComponentArray() argument" );
      }
      else
      {  pdParams[ arg-1 ] =        pNode->fValue;
         //plParams[ arg-1 ] = (long) pNode->fValue;
			lMDBID = (long long) pNode->fValue;
			if (lMDBID > BEM_MODEL_MULT && (arg==3 || arg==4))
			{	assert( FALSE );  // routine not yet MODEL-DBID compatible
				plParams[ arg-1 ] = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
				i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
			}
			else
				plParams[ arg-1 ] = (long) lMDBID;
      }
      ExpxNodeDelete( pNode );
   }

   if (!bAbort && nArgs != 4)
   {  bAbort = TRUE;
      ExpSetErr( error, EXP_RuleProc, "Expecting 4 ComponentArray() arguments (<OperationID#>, <Value#>, LocalDBID, Comp:ParamDBID)" );
   }
   
   if (!bAbort)
   {
      int iOperationID  = plParams[0]; 
      double dOperValue = pdParams[1]; 
      long lArrayDBID   = plParams[2]; 
      int iArraySize    = BEMPX_GetNumPropertyTypeElementsFromDBID( lArrayDBID );
                          assert( iArraySize > 1 );  // if == 1, then all we will do is return the first element that passes the test
      int iNumObjs      = BEMPX_GetNumObjects( BEMPX_GetClassID( plParams[3] ), pEval->ePrimObjType );

      BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lArrayDBID ), BEMPX_GetPropertyID( lArrayDBID ) );      assert( pPropType );
      if (!pPropType || pPropType->getPropType() != BEMP_Obj)
      {  bAbort = TRUE;
         ExpSetErr( error, EXP_RuleProc, "Third ComponentArray() argument expected to be an object reference/assignment property" );
      }
      else
      {
         ExpEvalStruct expStructCopy;
         CopyExpEvalStruct( &expStructCopy, pEval );
         expStructCopy.lPrimDBID = expStructCopy.lLocDBID = (lArrayDBID-1);  // start @ DBID-1 since DBIDs are incremented before each data set
         expStructCopy.sRulelistToEvaluate.clear();
        
         int iDataType, iSpecialVal, iObj, iError = 0, iSetArrayIdx = 0, iStatus = 0;
         double dThisObjVal=-1.;
         for (iObj=0; (!bAbort && iSetArrayIdx < iArraySize && iObj<iNumObjs); iObj++)
         {
      //      void* pData = (void*) BEMPX_GetData( plParams[3], iDataType, iSpecialVal, iError, iObj, pEval->ePrimObjType );
            double dData = BEMPX_GetFloatAndStatus( plParams[3], iStatus, iSpecialVal, iError, iObj,
            															pEval->ePrimObjType, -1, true /*bAllowNonFloatDataTypes*/ );
            if (iStatus > 0)
               dThisObjVal = dData;
            else
            {
               ExpSetErr( error, EXP_RuleProc, "Final argument data type incompatible with ComponentArray() function" );
               bAbort = TRUE;
            }
        
               if (!bAbort)
               {  BOOL bPassesCheck = FALSE;
                  switch (iOperationID)     // OperationIDs:  0==value / 1>=value / 2>value / 3<=value / 4<value
                  {  case  0 :  bPassesCheck = (dThisObjVal == dOperValue);   break;
                     case  1 :  bPassesCheck = (dThisObjVal >= dOperValue);   break;
                     case  2 :  bPassesCheck = (dThisObjVal >  dOperValue);   break;
                     case  3 :  bPassesCheck = (dThisObjVal <= dOperValue);   break;
                     case  4 :  bPassesCheck = (dThisObjVal <  dOperValue);   break;
                     default :  ExpSetErr( error, EXP_RuleProc, "Unsupported operation ID specified in first ComponentArray() argument" );
                                bAbort = TRUE;                                break;
                  }
        
                  if (bPassesCheck)
                  {  BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( plParams[3] ), iError, iObj, pEval->ePrimObjType );        assert( pObj );
                     if (pObj && !pObj->getName().isEmpty())
                     {  ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                        if (pNode)
                        {  pNode->type = EXP_String;
#pragma warning(disable : 4996)		// SAC 9/9/16
                           pNode->pValue = malloc( pObj->getName().length() + 1 );
                           strcpy( (char*) pNode->pValue, (const char*) pObj->getName().toLocal8Bit().constData() );
#pragma warning(default : 4996)

                           expStructCopy.lPrimDBID++;   expStructCopy.lLocDBID++;   iSetArrayIdx++;
                           expStructCopy.bEvalItemADebugTarget = (expStructCopy.iNumTargetedDebugItems < 1 ? FALSE : expStructCopy.pTargetedDebugInfo->MatchExists( expStructCopy.lLocDBID, 0 ));  // targeted debugging

                           LocalSetBEMProcData( &expStructCopy, FALSE /*bTagDataAsUserDefined*/, TRUE /*bPerformSetBEMDataResets*/, *pNode, *error );
                           iResult++;

                           ExpxNodeDelete( pNode );
                        }
                     }
                  }
               }
         }

         // go through remainder of array and restore each element to "undefined"
         for (; (!bAbort && iSetArrayIdx < iArraySize); iObj++)
         {
                     {  ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
                        if (pNode)
                        {  pNode->type = EXP_Value;
                           pNode->fValue = -99996;

                           expStructCopy.lPrimDBID++;   expStructCopy.lLocDBID++;   iSetArrayIdx++;
                           expStructCopy.bEvalItemADebugTarget = (expStructCopy.iNumTargetedDebugItems < 1 ? FALSE : expStructCopy.pTargetedDebugInfo->MatchExists( expStructCopy.lLocDBID, 0 ));  // targeted debugging

                           LocalSetBEMProcData( &expStructCopy, FALSE /*bTagDataAsUserDefined*/, TRUE /*bPerformSetBEMDataResets*/, *pNode, *error );
                           //iResult++;  - return value not to indicate array elements restored to undefined

                           ExpxNodeDelete( pNode );
                        }
                     }
         }
      }  // end of:  pPropType of valid type
   }  // end of:  if !bAbort

   // Create, set and push result node
   ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
   if (bAbort)
      pNode->type = EXP_Invalid;
   else
   {
      pNode->type = EXP_Value;
      pNode->fValue = (double) iResult;
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}


// SAC 1/4/01 - the new BF_CountNoRefs is different enough to call for its own evaluation
static void BEMProc_CountNoRefs( int /*op*/, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{	// example:   CountNoRefs( BotBelowZnGrp, Local( NumZones ), Local( BotBelowNumFlrs ) )  endif   }
   bool bAbort = FALSE;
   double fResult = 0.0;

   // Pop all (Comp:Param) nodes off stack and store in Long Array
   long plParams[5];
	long long lMDBID;
	int i0Model = -1;
   for ( int arg = nArgs; arg > 0; arg-- )
   {
      ExpNode* pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
      {
         ExpSetErr( error, EXP_RuleProc, "Invalid CountNoRefs() argument" );
         bAbort = TRUE;
      }
      else
      //   plParams[ arg-1 ] = (long) pNode->fValue;
		{	lMDBID = (long long) pNode->fValue;
			if (lMDBID > BEM_MODEL_MULT)
			{	assert( FALSE );  // routine not yet MODEL-DBID compatible
				plParams[ arg-1 ] = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
				i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
			}
			else
				plParams[ arg-1 ] = (long) lMDBID;
		}
      ExpxNodeDelete( pNode );
   }
   if (nArgs < 1 || nArgs > 3)
   {
      ExpSetErr( error, EXP_RuleProc, "Invalid number of CountNoRefs() arguments" );
      bAbort = TRUE;
   }

   if (!bAbort)
   {
      double dNoRefResult = (nArgs > 2 ? plParams[2] : 1.0);

      int iMaxArrayLoop = (nArgs > 1 ? plParams[1] : 1000);
      if (iMaxArrayLoop < 1)
         iMaxArrayLoop = 1000;
      int iArrLoop = min( iMaxArrayLoop, BEMPX_GetNumPropertyTypeElementsFromDBID( plParams[0] ) );
      assert( iArrLoop < 1000 );

      int iDataType, iSpecialVal, iError = 0, iDataStatus = 0;
      BEMObject* pObj = NULL;
      BOOL bFinished = FALSE;
      for (int iArr=0; (!bAbort && !bFinished && iArr <= iArrLoop); iArr++)
      {
   //      pObj = (BEMObject*) BEMPX_GetData( plParams[0]+iArr, iDataType, iSpecialVal, iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
         pObj = BEMPX_GetObjectAndStatus( plParams[0]+iArr, iDataStatus, iSpecialVal, iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
         if ( iError < 0  ||  pObj == NULL || iDataStatus < 1 )
         {  // found an unassigned pointer
            bFinished = TRUE;
            fResult = dNoRefResult;
         }
      }
   }

   // Create, set and push result node
   ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
   if (bAbort)
      pNode->type = EXP_Invalid;
   else
   {
      pNode->type = EXP_Value;
      pNode->fValue = fResult;
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}


// SAC 4/2/02 - added new function to evaluate the FirstBitwiseMatchComp() and BitwiseMatchCount() ruleset functions
//              BF_BitMatchCmp  - first arg should be the Property name of a local number, subsequent are Component:Property strings (3rd is Parent matching property)
//              BF_BitMatchCnt  - first arg should be the Property name of a local number, subsequent are Component:Property strings (3rd is Parent matching property)
void BEMProc_BitwiseMatches( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{	// example:   ZnGrpWiz:AssignedSystem = FirstBitwiseMatchComp( AssignSystemKey, HVACWiz:AssignShellZnGrp )
   bool bAbort = FALSE;
   double fResult = 0.0;
   QString sCompName;

   // Pop all (Comp:Param) nodes off stack and store in Long Array
   long plParams[5];
	long long lMDBID;
	int i0Model = -1;
   for ( int arg = nArgs; arg > 0; arg-- )
   {
      ExpNode* pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
      {
         if (op == BF_BitMatchCmp)
            ExpSetErr( error, EXP_RuleProc, "Invalid FirstBitwiseMatchComp() argument" );
         else
            ExpSetErr( error, EXP_RuleProc, "Invalid BitwiseMatchCount() argument" );
         bAbort = TRUE;
      }
      else
      //   plParams[ arg-1 ] = (long) pNode->fValue;
		{	lMDBID = (long long) pNode->fValue;
			if (lMDBID > BEM_MODEL_MULT)
			{	assert( FALSE );  // routine not yet MODEL-DBID compatible
				plParams[ arg-1 ] = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
				i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
			}
			else
				plParams[ arg-1 ] = (long) lMDBID;
		}
      ExpxNodeDelete( pNode );
   }
   if (nArgs < 2 || nArgs > 3)
   {
      if (op == BF_BitMatchCmp)
         ExpSetErr( error, EXP_RuleProc, "Invalid number of FirstBitwiseMatchComp() arguments" );
      else
         ExpSetErr( error, EXP_RuleProc, "Invalid number of BitwiseMatchCount() arguments" );
      bAbort = TRUE;
   }

   if (!bAbort)
   {
      int iDataType, iSpecialVal, iError, iDataStatus = 0;
      int iClassToLoopOver = BEMPX_GetClassID( plParams[1] );

      if (nArgs > 2)
      {
         if (iClassToLoopOver != BEMPX_GetClassID( plParams[2] ))
         {
            if (op == BF_BitMatchCmp)
               ExpSetErr( error, EXP_RuleProc, "Invalid third argument component type - FirstBitwiseMatchComp()" );
            else
               ExpSetErr( error, EXP_RuleProc, "Invalid third argument component type - BitwiseMatchCount()" );
            bAbort = TRUE;
         }
         else
         {
            BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( plParams[2], iError );
            if (pPropType == NULL  ||  pPropType->getPropType() != BEMP_Obj)
            {
               if (op == BF_BitMatchCmp)
                  ExpSetErr( error, EXP_RuleProc, "Invalid third argument property type - FirstBitwiseMatchComp()" );
               else
                  ExpSetErr( error, EXP_RuleProc, "Invalid third argument property type - BitwiseMatchCount()" );
               bAbort = TRUE;
            }
         }
      }

      if (!bAbort)
      {
         int iArrLoop = BEMPX_GetNumPropertyTypeElements( iClassToLoopOver, BEMPX_GetPropertyID( plParams[1] ) );
         if (nArgs > 2)
            iArrLoop = min( iArrLoop, BEMPX_GetNumPropertyTypeElements( iClassToLoopOver, BEMPX_GetPropertyID( plParams[2] ) ) );

         BEMObject* pParentObj = NULL;
         if (nArgs > 2)
         {
		//		int iTmpDataType=0;
      //      pParentObj = (BEMObject*) BEMPX_GetData( BEMPX_GetDBID( BEMPX_GetClassID( pEval->lPrimDBID ), iTmpDataType, BEM_PARAM0_PARENT ),
      //                                               iDataType, iSpecialVal, iError, pEval->iPrimObjIdx, pEval->ePrimObjType, TRUE );
         	pParentObj = BEMPX_GetObjectAndStatus( BEMPX_GetClassID( pEval->lPrimDBID ), iDataStatus, iSpecialVal,
         															iError, pEval->iPrimObjIdx, pEval->ePrimObjType );
            assert( pParentObj );
         }

         long lValToMatch, lValToMatch2;
         BEMPX_GetInteger( plParams[0], lValToMatch, 0, -1, pEval->iPrimObjIdx, pEval->ePrimObjType );
         if (lValToMatch > 0)
         {
            int iNumLoopObjs = BEMPX_GetNumObjects( iClassToLoopOver, pEval->ePrimObjType );
            BOOL bDone = FALSE;
            BEMObject* pMatchParentObj;
            for (int iObj=0; (!bDone && iObj<iNumLoopObjs); iObj++)
               for (int iArr=0; (!bDone && iArr<iArrLoop); iArr++)
               {
                  if ( ( pParentObj == NULL  ||
                         ( BEMPX_GetObject( plParams[2]+iArr, pMatchParentObj, BEMP_Obj, iObj, pEval->ePrimObjType ) &&
                           pMatchParentObj == pParentObj ) )  &&
                       BEMPX_GetInteger( plParams[1]+iArr, lValToMatch2, 0, -1, iObj, pEval->ePrimObjType )  &&
                       lValToMatch2 > 0  &&  (lValToMatch & lValToMatch2) )
                  {
                     if (op == BF_BitMatchCmp)
                     {
                        BEMObject* pObj = BEMPX_GetObjectByClass( iClassToLoopOver, iError, iObj );
                        assert( pObj );
                        assert( !pObj->getName().isEmpty() );
                        if (iError >= 0 && pObj && !pObj->getName().isEmpty())
                        {
                           sCompName = pObj->getName();
                           bDone = TRUE;
                        }
                     }
                     else
                        fResult += 1.0;
                  }
               }
         }
      }
   }

   // Create, set and push result node
   ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
   if (bAbort)
      pNode->type = EXP_Invalid;
   else if (op == BF_BitMatchCmp)
   {
      if (sCompName.isEmpty())
      {
         pNode->type = EXP_Value;
         pNode->fValue = -99998;   // => set to "NONE"
      }
      else
      {
#pragma warning(disable : 4996)		// SAC 9/9/16
         pNode->type = EXP_String;
         pNode->pValue = malloc( sCompName.length() + 1 );
         strcpy( (char*) pNode->pValue, (const char*) sCompName.toLocal8Bit().constData() );
#pragma warning(default : 4996)
      }
   }
   else
   {
      pNode->type = EXP_Value;
      pNode->fValue = fResult;
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}


// SAC 7/21/06 - first argument of SumIntoArrayElement() should be Param or Comp:Param string, second is 1-based array index and third is value to sum into that array element
void BEMProc_SumIntoArrayElement( int /*op*/, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
   bool bAbort = FALSE;
   // Pop all (Comp:Param) nodes off stack and store in Long Array
   ExpNode* pNode = NULL;
   long lArrayDBID = 0;
   long lArrayIdx = 0;
   double fValToSum = 0;
	long long lMDBID;
	int i0Model = -1;
   for (int arg = nArgs-1; arg >= 0; arg--)
   {
      pNode = ExpxStackPop( stack );
      if (pNode->type != EXP_Value)
      {
         ExpSetErr( error, EXP_RuleProc, "Invalid SumIntoArrayElement() argument" );
         bAbort = TRUE;
      }
      else
      {
         switch (arg)
         {
            case 0 :  //lArrayDBID = (long)  pNode->fValue;   break;
								{	lMDBID = (long long) pNode->fValue;
									if (lMDBID > BEM_MODEL_MULT)
									{	assert( FALSE );  // routine not yet MODEL-DBID compatible
										lArrayDBID = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
										i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
									}
									else
										lArrayDBID = (long) lMDBID;
								}  break;
            case 1 :  lArrayIdx  = (long)  pNode->fValue;   break;
            case 2 :  fValToSum  =         pNode->fValue;   break;
         }
      }

      if (arg > 0)
         ExpxNodeDelete( pNode );
      else if (pNode->type == EXP_String)
      {  // for last node, free string argument, but not entire node
         free( pNode->pValue );
         pNode->pValue = NULL;
      }
   }

   double fResult = 0.0;
   if (!bAbort && nArgs != 3)
   {
      ExpSetErr( error, EXP_RuleProc, "Invalid number of SumIntoArrayElement() arguments (must be 3)" );
      bAbort = TRUE;
   }
   else if (!bAbort)
   {  // we have 3 arguments of type Value
      int lClassIdx = (int) (lArrayDBID <= BEM_COMP_MULT ? 0 : BEMPX_GetClassID(    lArrayDBID ));
      int lPropIdx  = (int) (lArrayDBID <= BEM_COMP_MULT ? 0 : BEMPX_GetPropertyID( lArrayDBID ));
      bAbort = TRUE;
      if (lClassIdx < 1 || lPropIdx < 1)
         ExpSetErr( error, EXP_RuleProc, "Invalid SumIntoArrayElement() database ID (first) argument" );
      else if (lArrayIdx < 1 || lArrayIdx > 999)
         ExpSetErr( error, EXP_RuleProc, "Invalid SumIntoArrayElement() array index (second) argument" );
      else
      {
         int iMaxArrayItems = BEMPX_GetNumPropertyTypeElements( lClassIdx, lPropIdx );
         if (lArrayIdx > iMaxArrayItems)
            ExpSetErr( error, EXP_RuleProc, "Second SumIntoArrayElement() (array index) argument exceeds size of array" );
         else
         {
            lArrayDBID = BEMPX_GetDBID( lClassIdx, lPropIdx, lArrayIdx );
            BOOL bPrimClass = (lClassIdx == BEMPX_GetClassID( pEval->lPrimDBID ));
            int iOccur   = (bPrimClass ? pEval->iPrimObjIdx  : -1      );
            int iObjType = (bPrimClass ? pEval->ePrimObjType : BEMO_User);
      //      double fBEMPVal = 0;
      //      if (!BEMPX_SetDataFloat( lArrayDBID, fBEMPVal, 0 /*fDefault*/, -1 /*iDispDataType*/, iOccur, iObjType ))
				int iStatus=0, iSpecialVal, iError;
				double fBEMPVal = BEMPX_GetFloatAndStatus( lArrayDBID, iStatus, iSpecialVal, iError, iOccur, (BEM_ObjType) iObjType, -1, true );
				if (iStatus < 1)
               ExpSetErr( error, EXP_RuleProc, "Error retrieving existing database value (SumIntoArrayElement() function)" );
            else
            {
               fBEMPVal += fValToSum;

               bAbort = FALSE;
               BEMPropertyType* pPropType = BEMPX_GetPropertyType( lClassIdx, lPropIdx );      assert( pPropType );
               if (pPropType && (pPropType->getPropType() == BEMP_Int || pPropType->getPropType() == BEMP_Sym))
               {
                  long lBEMPVal = (long) fBEMPVal;
                  if (BEMPX_SetBEMData( lArrayDBID, BEMP_Int, (void*) &lBEMPVal, (BEM_ObjType) iObjType, iOccur, pEval->eLocStatus ) < 0)
                     bAbort = TRUE;
               }
               else if (pPropType && pPropType->getPropType() == BEMP_Flt)
               {
                  if (BEMPX_SetBEMData( lArrayDBID, BEMP_Flt, (void*) &fBEMPVal, (BEM_ObjType) iObjType, iOccur, pEval->eLocStatus ) < 0)
                     bAbort = TRUE;
               }
               else
                  bAbort = TRUE;

               if (!bAbort)
                  fResult = fBEMPVal;
            }
         }
      }
   }

   // setup result node
   if (pNode == NULL)
      pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );

   if (bAbort)
      pNode->type = EXP_Invalid;
   else
   {
      pNode->type = EXP_Value;
      pNode->fValue = fResult;
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}


static int StringInArray( QStringList& saStrs, QString& sStr )  // SAC 8/25/03
{
   int iSize = (int) saStrs.size();
   for (int i=0; i<iSize; i++)
   {
      if (saStrs[i].compare( sStr, Qt::CaseInsensitive ) == 0)
         return i;
   }
   return -1;
}


// SAC 8/25/03 - Implemented EnsureStringUniqueness(): first arg is Comp:Param string and second (optional arg) is maximum string length
static void BEMProc_EnsureStringUniqueness( int /*op*/, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )
{
   bool bAbort = FALSE;
   double fResult = 0.0;
   ExpNode* pNode;
	long long lMDBID;
	int i0Model = -1;

   if (nArgs < 1 || nArgs > 2)
   {
      ExpSetErr( error, EXP_RuleProc, "Invalid number of EnsureStringUniqueness() arguments" );
      bAbort = TRUE;
      // Pop and delete all nodes off stack
      for ( int arg = nArgs; arg > 0; arg-- )
      {
         pNode = ExpxStackPop( stack );
         ExpxNodeDelete( pNode );
      }
   }

   long lDBID = 0;
   int iMaxStringLen = 512;
   if (!bAbort)
   {
      if (nArgs > 1)
      {
         pNode = ExpxStackPop( stack );
         if (pNode->type != EXP_Value)
         {
            ExpSetErr( error, EXP_RuleProc, "Invalid second EnsureStringUniqueness() argument (must be numeric)" );
            bAbort = TRUE;
         }
         else
         {
            iMaxStringLen = (int) pNode->fValue;
            if (iMaxStringLen < 4)
            {
               ExpSetErr( error, EXP_RuleProc, "Invalid second EnsureStringUniqueness() argument (MaxStringLen must be >= 4)" );
               bAbort = TRUE;
            }
         }
         ExpxNodeDelete( pNode );
      }

      pNode = ExpxStackPop( stack );
      if (!bAbort)
      {
         if (pNode->type != EXP_Value)
         {
            ExpSetErr( error, EXP_RuleProc, "Invalid first EnsureStringUniqueness() argument (must be DBID)" );
            bAbort = TRUE;
         }
         else
         //   lDBID = (long) pNode->fValue;
			{	lMDBID = (long long) pNode->fValue;
				if (lMDBID > BEM_MODEL_MULT)
				{	assert( FALSE );  // routine not yet MODEL-DBID compatible
					lDBID = (long) BEMPX_MDBIDtoDBID( lMDBID );				assert( i0Model<0 || i0Model==((int) BEMPX_GetModelID( lMDBID ) - 1) );
					i0Model = (int) BEMPX_GetModelID( lMDBID ) - 1;
				}
				else
					lDBID = (long) lMDBID;
			}
      }
      ExpxNodeDelete( pNode );
   }

   int iBEMPClass = 0;
   BEMPropertyType* pPropType = NULL;
   if (!bAbort)
   {
      int iError;
      iBEMPClass = BEMPX_GetClassID( lDBID );
      pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
      if (pPropType == NULL  ||  pPropType->getPropType() != BEMP_Str)
      {
         ExpSetErr( error, EXP_RuleProc, "Invalid first EnsureStringUniqueness() argument (must be a property of type String)" );
         bAbort = TRUE;
      }
   }

   if (!bAbort)
   {
      int iArrLoop = pPropType->getNumValues();

      int iNumObjs = BEMPX_GetNumObjects( iBEMPClass, pEval->ePrimObjType );
      QStringList saStrs;
      for (int iObj=0; (!bAbort && iObj<iNumObjs); iObj++)
         for (int iArr=0; (!bAbort && iArr<iArrLoop); iArr++)
         {
            int iStatus, iSpecialVal, iError;
      //      QString sStr;
      //      if (BEMPX_GetStringAndStatus( lDBID + iArr, sStr, iStatus, FALSE, 0, BEMP_Str, iObj ))
				QString sStr = BEMPX_GetStringAndStatus( lDBID + iArr, iStatus, iSpecialVal, iError, 
            														iObj, BEMO_User, -1, FALSE, 0 );
            if (iStatus > 0)
            {
               QString sBase = sStr;
               int iUnqIdx=1;
               while (StringInArray( saStrs, sStr ) >= 0)
               {
                  int iNumLen = (iUnqIdx < 9 ? 2 : (iUnqIdx < 99 ? 3 : (iUnqIdx < 999 ? 4 : 5)));
                  sStr = QString( "%1 %2" ).arg( sBase.left( iMaxStringLen - iNumLen ), QString::number( ++iUnqIdx ) );
               }

               saStrs.push_back( sStr );

               if (iUnqIdx > 1)
               {
                  fResult += 1;
                  // assert( iStatus == BEMS_UserDefined );  // what to do if non-unique data NOT user-defined ???
                  BEMPX_SetBEMData( lDBID + iArr, BEMP_QStr, (void*) &sStr,  // BEMP_Str, (void*) sStr.toLocal8Bit().constData(), 
                  								pEval->ePrimObjType, iObj, (BEM_PropertyStatus) iStatus );
               }
            }
         }
   }

   // Create, set and push result node
   pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
   if (bAbort)
      pNode->type = EXP_Invalid;
   else
   {
      pNode->type = EXP_Value;
      pNode->fValue = fResult;
   }
   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  TableLookupFunction()
//
// Purpose ------------------------------------------------------------------
//   Performs all table look-ups.
//   
// Arguments ----------------------------------------------------------------
//   int       op    : function enum
//   int       nArgs : number of arguments stored on stack
//   ExpStack* stack : expression stack
//   ExpError* error : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static void TableLookupFunction( int op, int nArgs, ExpStack* stack, ExpEvalStruct* pEval, ExpError* error )  // SAC 9/25/02
{
	int i1TblIdx = (-op) / BEMP_TABLEID_MULT;
	int i1ColIdx = (-op) % BEMP_TABLEID_MULT;

	if (i1ColIdx == 0)
	{	// ----------- 
		// --- OLD --- style table look-ups w/ fixed independents and return column specified as arguments
		// ----------- 
	   int iCol = 0;
	   ExpNode* pColNode = ExpxStackPop( stack );
	   if (pColNode->type != EXP_Value)
	      ExpSetErr( error, EXP_RuleProc, "Invalid table lookup argument: column" );
	   else
	      iCol = (int) pColNode->fValue;
	
	   double* pfParams = (double*) malloc ( sizeof(double) * nArgs );
	   for ( int arg = nArgs; arg > 1; arg-- )
	   {
	      ExpNode* pNode = ExpxStackPop( stack );
	      if (pNode->type != EXP_Value)
	         ExpSetErr( error, EXP_RuleProc, "Invalid table lookup argument" );
	      else
	         pfParams[ arg-2 ] = pNode->fValue;
	      ExpxNodeDelete( pNode );
	   }
	
	   pColNode->type = EXP_Value;
	   double fReturn = 0;  // SAC 6/30/00 - added initialization to 0 to prevent an unintialized value from being referenced below
	   bool bValueFound = ruleSet.getTableValue( i1TblIdx, pfParams, iCol, &fReturn, pEval->bVerboseOutput );  // SAC 9/25/02
	   pColNode->fValue = fReturn;
	
	   if (!bValueFound)
	   {
			// SAC 10/23/07 - revised error reporting to echo all parameters passed in to table look-up
	      QString sErrMsg, sParam, sTblName;
	      int iNumParams = ruleSet.getTableDimension( i1TblIdx, TRUE /*bParams*/ );
	      if (iNumParams < 1)
	         sErrMsg = "Table look-up failed (invalid table index)";
	      else
	      {  ruleSet.getTableName( i1TblIdx, sTblName );
	         sErrMsg = QString( "Table look-up failed %1(%2" ).arg( sTblName, QString::number( pfParams[0] ) );
	         for (int i=1; i<iNumParams; i++)
	         {  sParam = QString( ", %1" ).arg( QString::number( pfParams[i] ) );
	            sErrMsg += sParam;
	         }
	         sErrMsg += ')';
	      }
	      ExpSetErr( error, EXP_RuleProc, sErrMsg );
	   }
	      
	   // Push new node onto stack
	   ExpxStackPush( stack, pColNode );
	
	   free( pfParams );
	}
	else
	{	// ----------- 
		// --- NEW --- style table look-ups w/ independents specified in arguments by NAME and return value identified via 1iColIdx
		// ----------- 
		vector<string> saIndepNames, saIndepStrings;
		vector<double> faIndepValues;
		vector<bool> baIndepNumeric;
		string sIndepStr, sErrMsg, sWarnMsg;
		double fIndepVal;
		bool bIndepNumeric=false;
      ExpNode* pNode = NULL;
		bool bStoreArguments = (nArgs > 0 && !(nArgs % 2));  // at least one argument and NOT an odd number of arguments
		if (!bStoreArguments)
      {	if (nArgs < 1)
			   sErrMsg = "Invalid number of table lookup arguments (must be > 0)";
			else
			   sErrMsg = "Invalid number of table lookup arguments (must be even #)";
		}
		int arg = nArgs;
	   for (; arg > 0; arg-- )
	   {
	      pNode = ExpxStackPop( stack );
			if (pNode && pNode->type == EXP_String)
			{	bIndepNumeric = false;
				fIndepVal = 0.0;
				sIndepStr = (char*) pNode->pValue;
			}
			else if (pNode && pNode->type == EXP_Value)
			{	bIndepNumeric = true;
				fIndepVal = pNode->fValue;
				sIndepStr.clear();
			}
			else
			{	sErrMsg = "Invalid table lookup argument (lookup value not of type string or value)";
				bStoreArguments = false;
			}
	      ExpxNodeDelete( pNode );
			if (--arg > 0)
			{
		      pNode = ExpxStackPop( stack );
		      if (bStoreArguments)
	      	{	if (pNode->type != EXP_String)
					{	sErrMsg = "Invalid table lookup argument (independent variable name not of type string)";
						bStoreArguments = false;
					}
	      		else if (bStoreArguments)
					{	saIndepNames.push_back( (char*) pNode->pValue );
						baIndepNumeric.push_back( bIndepNumeric );
						faIndepValues.push_back(  fIndepVal     );
  						saIndepStrings.push_back( sIndepStr     );
					}
				}
		      ExpxNodeDelete( pNode );
			}
	   }

	   pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );
	   pNode->type = EXP_Invalid;
		pNode->fValue = 0.;
		BEMTableCell* pRetCell = NULL;
		if (sErrMsg.length() < 1 && bStoreArguments)
		{	pRetCell = ruleSet.getTableCell( i1TblIdx, i1ColIdx, saIndepNames, saIndepStrings,
														faIndepValues, baIndepNumeric, sErrMsg, pEval->bVerboseOutput );
			if (pRetCell)
			{	switch (pRetCell->getCellType())
				{	case BEMTCT_Float     :		pNode->type = EXP_Value;
														pNode->fValue = pRetCell->getValue();
														break;
				   case BEMTCT_String    : {	string strRet = pRetCell->getString();
														if (boost::iequals( strRet, "NA" ) || boost::iequals( strRet, "N/A" ))
														{	pNode->type = EXP_Value;
															pNode->fValue = -99996;  // => UNDEFINED
														}
														else
														{	pNode->type = EXP_String;
#pragma warning(disable : 4996)		// SAC 9/9/16
   														pNode->pValue = malloc( strRet.length() + 1 );
   														strcpy( (char*) pNode->pValue, strRet.c_str() );
#pragma warning(default : 4996)
														}
													}	break;
				   case BEMTCT_Error     :	{	if (sErrMsg.length() < 1)
															sErrMsg = "Table lookup failed.";
														//if (pssaErrorMsgs)
                        						//   pssaErrorMsgs->push_back( sErrMsg.c_str() );
                        						//else
                        						//   ExpSetErr( error, EXP_RuleProc, QString("Error:  ") + QString(sErrMsg.c_str()) );
													}	break;
				   case BEMTCT_Warning   : {	pNode->type = EXP_Value;  // set return value to UNDEFINED rather than retaining an invalid return value
														pNode->fValue = -99996;  // => UNDEFINED
														if (sErrMsg.length() < 1)
															sWarnMsg = "Table lookup warning encountered.";
														else
															sWarnMsg = sErrMsg;
														sErrMsg.clear();
                        						//if (pssaWarningMsgs)
                        						//   pssaWarningMsgs->push_back( sErrMsg.c_str() );
                        						//else
                        						//   ExpSetErr( error, EXP_RuleWarn, QString("Warning:  ") + QString(sErrMsg.c_str()) );
													}	break;
				   case BEMTCT_WildCard  :
				   case BEMTCT_Missing   :  
				   case BEMTCT_Undefined :  // do nothing for these
														pNode->type = EXP_Value;
														pNode->fValue = -99996;  // => UNDEFINED
														break;
				}
			}
		}

		if (pRetCell == NULL && sErrMsg.length() < 1)
			sErrMsg = "Table lookup failed (cell not found).";

		if (sErrMsg.length() > 0 || sWarnMsg.length() > 0)
		{	bool bWarnOnly = (sWarnMsg.length() > 0 && sErrMsg.length() < 1);
         QString sTblName;
			string sColName;
	      ruleSet.getTableName( i1TblIdx, sTblName );
	      ruleSet.getTableColumnName( i1TblIdx, i1ColIdx, sColName );
			string sFullErrMsg = boost::str( boost::format( "Table look-up failed: %s:%s( " ) % sTblName.toLocal8Bit().constData() % sColName );
         for (arg=0; arg < (int) saIndepNames.size(); arg++)
			{	if (arg > 0)
					sFullErrMsg += ", ";
				if (baIndepNumeric[arg])
					sFullErrMsg += boost::str( boost::format( "%s=%g" ) % saIndepNames[arg] % faIndepValues[arg] );
				else
					sFullErrMsg += boost::str( boost::format( "%s='%s'" ) % saIndepNames[arg] % saIndepStrings[arg] );
			}
			sFullErrMsg += " )";
			if (sErrMsg.length() > 0)
			{	sFullErrMsg += "  |  ERROR:  ";
				sFullErrMsg += sErrMsg;
			}
			if (sWarnMsg.length() > 0)
			{	sFullErrMsg += "  |  Warning:  ";
				sFullErrMsg += sWarnMsg;
			}
	      ExpSetErr( error, (bWarnOnly ? EXP_RuleWarn : EXP_RuleProc), sFullErrMsg.c_str() );
		}
//		if (pRetCell == NULL)
//		{	if (sErrMsg.length() < 1)
//				sErrMsg = "Table lookup failed (cell not found).";
//			//if (pssaErrorMsgs)
//         //   pssaErrorMsgs->push_back( sErrMsg.c_str() );
//         //else
//         ExpSetErr( error, EXP_RuleProc, QString("Error:  ") + QString(sErrMsg.c_str()) );
//		}

	   // Push return node onto stack
	   ExpxStackPush( stack, pNode );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  GetBEMProcData()
//
// Purpose ------------------------------------------------------------------
//   Retrieves data from the building database.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : database ID of parameter to get the data of
//   int        iOccur   : occurence index of component to get the data of
//   BEM_ObjType eObjType : type of object to get the data of
//   ExpStack*  stack    : expression stack
//   ExpError*  error    : pointer to error structure used to report errors
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void GetBEMProcData( long long lMDBID, int iOccur, BEM_ObjType eObjType, ExpStack* stack, ExpError* error, BOOL bGetSymStr,
										ExpEvalStruct* pEval, BOOL bReturnInvalidWhenUndefined, int iObjIdxModel /*=-1*/ )  // SAC 8/6/10 - added pEval argument   // SAC 2/13/14 - added bReturnInvalidWhenUndefined
{
   ExpNode* pNode = ExpNode_new();  //(ExpNode*) malloc( sizeof( ExpNode ) );

	GetBEMProcDataToNode( pNode, lMDBID, iOccur, eObjType, error, bGetSymStr, pEval, bReturnInvalidWhenUndefined, iObjIdxModel );

   // Push new node onto stack
   ExpxStackPush( stack, pNode );
}
// SAC 1/27/15 - split into separate routines, one that mallocs the node and pushes result onto stack (above) and another to populate a node w/ BEM data

void GetBEMProcDataToNode( ExpNode* pNode, long long lMDBID, int iOccur, BEM_ObjType eObjType, ExpError* error, BOOL bGetSymStr,
										ExpEvalStruct* pEval, BOOL bReturnInvalidWhenUndefined, int iObjIdxModel /*=-1*/ )  // SAC 8/6/10 - added pEval argument   // SAC 2/13/14 - added bReturnInvalidWhenUndefined
{	assert( pNode );
   pNode->type = EXP_Invalid;
   int iDataStatus=0, iDataType=0, iSpecialVal;
   int iError = 0;

	long lDBID;					// SAC 3/14/13 - added Model DBID compatibility
	int iBEMProcModel = -1;
	if (lMDBID > BEM_MODEL_MULT)
	{
		iBEMProcModel = (int)  BEMPX_GetModelID(  lMDBID ) - 1;  // convert model ID from 1- to 0-based
		lDBID         = (long) BEMPX_MDBIDtoDBID( lMDBID );

		assert( iBEMProcModel <= BEMPX_GetActiveModel() );
// ERROR if  iBEMProcModel > BEMPX_GetActiveModel()

		if (iObjIdxModel >= 0 && iBEMProcModel == iObjIdxModel)		// SAC 6/23/15
		{	// do nothing - no need to translate ObjIdx across models
		}
		else if (iBEMProcModel != BEMPX_GetActiveModel())
		{	// need to get object index of corresponding object in 
			int iOrigOccur = iOccur;
			iOccur = BEMPX_GetObjectIndexAcrossModels( BEMPX_GetClassID(lDBID), iBEMProcModel, eObjType, iOccur, iObjIdxModel );		// assert( iOccur >= 0 ); - already reported
			if (iOccur < 0)
		   {	QString sBEMProcErr, sBEMProcErr2;
				sBEMProcErr2 = QString( "Error: Retrieving data from model %1 (" ).arg( QString::number( iBEMProcModel ) );
		      PopulateBEMProcInfo( sBEMProcErr, lDBID, iOrigOccur, eObjType, iBEMProcModel, sBEMProcErr2.toLocal8Bit().constData(), ") in GetBEMProcData()" );
		      ExpSetErr( error, EXP_RuleProc, sBEMProcErr );

			// SAC 9/24/15 - retain detailed logging of object mapping across transforms for future reference
				int iOutOccur, i1Class = BEMPX_GetClassID(lDBID);
				if (iObjIdxModel == -1)
					iObjIdxModel = BEMPX_GetActiveModel();
				BEMObject* pInObj = BEMPX_GetObjectByClass( i1Class, iError, iOrigOccur, eObjType, iObjIdxModel );				assert( pInObj );
				if (pInObj)
				{	BEMObject* pOutObj = NULL;
					sBEMProcErr = QString( "Error retrieving Object across models, from transform %1 to %2 for %3 '%4' - object mapping -->>" ).arg( QString::number( iObjIdxModel ), QString::number( iBEMProcModel ), pInObj->getClass()->getLongName(), pInObj->getName() );		BEMPX_WriteLogFile( sBEMProcErr );
					for (int i1=0; i1<BEMPROC_MAXMODELS; i1++)
					{	if (pInObj->getModelMappedObject(i1) == NULL)
						{	sBEMProcErr = QString( "   [%1] -> NULL" ).arg( QString::number( i1 ), 2 );		BEMPX_WriteLogFile( sBEMProcErr );
						}
						else
						{	pOutObj = pInObj->getModelMappedObject(i1);
							sBEMProcErr = QString( "   [%1] -> %2 | '%3' object mapping -->>" ).arg( QString::number( i1 ), 2 ).arg( QString::number( (int) pOutObj, 16 ) ).arg( pOutObj->getName() );		BEMPX_WriteLogFile( sBEMProcErr );
							for (int i2=0; i2<BEMPROC_MAXMODELS; i2++)
							{	if (pOutObj->getModelMappedObject(i2) == NULL)
								{	sBEMProcErr = QString( "        [%1] -> NULL" ).arg( QString::number( i2 ), 2 );		BEMPX_WriteLogFile( sBEMProcErr );
								}
								else
								{	sBEMProcErr = QString( "        [%1] -> %2 | '%3' object mapping -->>" ).arg( QString::number( i2 ), 2 ).arg( QString::number( (int) pOutObj->getModelMappedObject(i2), 16 ), pOutObj->getModelMappedObject(i2)->getName() );		BEMPX_WriteLogFile( sBEMProcErr );
				}	}	}	}	}
			}
		}
	}
	else
		lDBID = (long) lMDBID;

//   void* pData = (void*) BEMPX_GetDataAndStatus( lDBID, iDataStatus, iDataType, iSpecialVal, iError, iOccur, eObjType, FALSE /*bReturnParentObject*/, iBEMProcModel );
//
//   QString sCurrStr;
//   if ( pData != NULL )
//   {
//      // SAC 8/7/10 - implementation of targeted debug output
//      if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lDBID, iOccur ))
//         ReportTargetedDebugInfo( pEval, iDataStatus, iDataType, iSpecialVal, lDBID, iOccur, eObjType, "GetBEMProcData()", iBEMProcModel );
//
//		if (iDataStatus < 1)		// handle case where property is UNDEFINED
//		{
//			if (bReturnInvalidWhenUndefined)  // SAC 2/13/14
//			{	pNode->type = EXP_Invalid;
//				pNode->fValue = -99996.0;	// => UNDEFINED
//			}
//			else if (iDataType == BEMP_Int || (iDataType == BEMP_Sym && !bGetSymStr) || iDataType == BEMP_Flt)
//			{	pNode->type = EXP_Value;
//				pNode->fValue = -99996.0;	// => UNDEFINED
//			}
//			else
//			{	pNode->type = EXP_String;
//				pNode->fValue = -99996.0;	// => UNDEFINED
//		      if (iDataType == BEMP_Obj)
//	            sCurrStr = "NONE";
//				else
//   	         sCurrStr = "UNDEFINED";
//			}
//		}
//      else if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
//      {
//			// SAC 2/8/01 - added option to return symbol STRING
//         if (iDataType == BEMP_Sym  &&  bGetSymStr)
//         {
//            sCurrStr = BEMPX_GetSymbolString( (int) *(long*) pData, lDBID, iOccur, eObjType, iBEMProcModel );
//            pNode->type = EXP_String;
//         }
//         else
//         {
//            // Get long data
//            long lNewVal = *(long*) pData;
//            pNode->type = EXP_Value;
//            pNode->fValue = (double) lNewVal;
//         }
//      }
//      else if (iDataType == BEMP_Flt)
//      {
//         // Get long data
//         float fNewVal = *(float*) pData;
//         pNode->type = EXP_Value;
//         pNode->fValue = fNewVal;
//      }
//      else if (iDataType == BEMP_Str)
//      {
//         sCurrStr = *(QString*) pData;
//         pNode->type = EXP_String;
//      }
//      else if (iDataType == BEMP_Obj)
//      {
//         BEMObject* pObj = (BEMObject*) pData;
//         if (iError >= 0 && pObj != NULL)
//            sCurrStr = pObj->getName();
//         else
//            sCurrStr = "NONE";
//         pNode->type = EXP_String;
//      }
//   }
//   else if (BEMPX_GetDataType(lDBID) == BEMP_Obj)
//   {  // failed to get object - lets keep going
//      sCurrStr = "NONE";
//      pNode->type = EXP_String;
//   }
//   else
//   {
//      QString sBEMProcErr;  // SAC 12/24/07 - added more verbose BEMProc retrieval info
//      PopulateBEMProcInfo( sBEMProcErr, lDBID, iOccur, eObjType, iBEMProcModel, "Data Retrieval from BEMProc failed (", ") in GetBEMProcData()" );
//      ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
//   }
// SAC 9/5/16 - replaced above w/ following (during open source conversions)
	QString sCurrStr, sBEMProcErr;
	iDataType = BEMPX_GetDataType( lDBID );
      // SAC 8/7/10 - implementation of targeted debug output
      if (pEval && pEval->iNumTargetedDebugItems > 0 && pEval->pTargetedDebugInfo && pEval->pTargetedDebugInfo->MatchExists( lDBID, iOccur ))
         ReportTargetedDebugInfo( pEval, iDataType, lDBID, iOccur, eObjType, "GetBEMProcData()", iBEMProcModel );
	if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
	{	pNode->fValue = (double) BEMPX_GetIntegerAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcModel );
		if (iDataStatus > 0)
		{	if (iDataType == BEMP_Sym  &&  bGetSymStr)
			{	sCurrStr = BEMPX_GetSymbolString( (int) pNode->fValue, lDBID, iOccur, eObjType, iBEMProcModel );
				pNode->type = EXP_String;
			}
			else
				pNode->type = EXP_Value;
		}
	}
	else if (iDataType == BEMP_Flt)
	{	pNode->fValue = BEMPX_GetFloatAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcModel );
		if (iDataStatus > 0)
			pNode->type = EXP_Value;
	}
	else if (iDataType == BEMP_Str)
	{	sCurrStr = BEMPX_GetStringAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcModel );
		if (iDataStatus > 0)
			pNode->type = EXP_String;
	}
	else if (iDataType == BEMP_Obj)
	{	BEMObject* pObj = BEMPX_GetObjectAndStatus( lDBID, iDataStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcModel );
		pNode->type = EXP_String;
		if (iError >= 0 && pObj)
			sCurrStr = pObj->getName();
		else
			sCurrStr = "NONE";
	}
	else		// invalid DataType
	{	PopulateBEMProcInfo( sBEMProcErr, lDBID, iOccur, eObjType, iBEMProcModel, "Data Retrieval from BEMProc failed (", ") in GetBEMProcData()" );
		ExpSetErr( error, EXP_RuleProc, sBEMProcErr );
   }
	if (iDataStatus < 1 && sBEMProcErr.isEmpty())		// property is UNDEFINED
	{	if (bReturnInvalidWhenUndefined)  // SAC 2/13/14
		{	pNode->type = EXP_Invalid;
			pNode->fValue = -99996.0;	// => UNDEFINED
		}
		else if (iDataType == BEMP_Int || (iDataType == BEMP_Sym && !bGetSymStr) || iDataType == BEMP_Flt)
		{	pNode->type = EXP_Value;
			pNode->fValue = -99996.0;	// => UNDEFINED
		}
		else
		{	pNode->type = EXP_String;
			pNode->fValue = -99996.0;	// => UNDEFINED
			if (iDataType == BEMP_Obj)
				sCurrStr = "NONE";
			else
				sCurrStr = "UNDEFINED";
	}	}

   if (pNode->type == EXP_String)
   {
#pragma warning(disable : 4996)		// SAC 9/9/16
   	pNode->pValue = malloc( sCurrStr.length() + 1 );
		strcpy( (char*) pNode->pValue, (const char*) sCurrStr.toLocal8Bit().constData() );
#pragma warning(default : 4996)
   }
}


double ConsAssmUFactor( int /*iCalcMethod*/, int iConsAssmObjIdx, BEM_ObjType /*eConsAssmObjType*/, QString sConsAssmName, ExpEvalStruct* /*pEval*/, ExpError* error )
{
	double dUFactor = -1;
	int iError;
	QString sUFactorErr, sMatName;

	int iCID_ConsAssm = BEMPX_GetDBComponentID( "ConsAssm" );
	int iCID_Mat      = BEMPX_GetDBComponentID( "Mat" );
	int iCID_Proj     = BEMPX_GetDBComponentID( "Proj" );
	long lDBID_ConsAssm_MatRef        = BEMPX_GetDatabaseID( "MatRef"       , iCID_ConsAssm );
	long lDBID_ConsAssm_OutsdAirFilmR = BEMPX_GetDatabaseID( "OutsdAirFilmR", iCID_ConsAssm );
	long lDBID_ConsAssm_InsdAirFilmR  = BEMPX_GetDatabaseID( "InsdAirFilmR" , iCID_ConsAssm );
	long lDBID_Mat_Name    = BEMPX_GetDatabaseID( "Name"   , iCID_Mat );
	long lDBID_Mat_CodeCat = BEMPX_GetDatabaseID( "CodeCat", iCID_Mat );
	long lDBID_Mat_RVal    = BEMPX_GetDatabaseID( "RVal"   , iCID_Mat );
	BEMPropertyType* pPropType_MatRef = BEMPX_GetPropertyTypeFromDBID( lDBID_ConsAssm_MatRef, iError /*, int iBEMProcIdx=-1*/ );
	if (iCID_ConsAssm < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 object ID." ).arg( "ConsAssm" );
	else if (iCID_Mat < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 object ID." ).arg( "Mat" );
	else if (lDBID_ConsAssm_MatRef < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "ConsAssm:MatRef" );
	else if (lDBID_ConsAssm_OutsdAirFilmR < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "ConsAssm:OutsdAirFilmR" );
	else if (lDBID_ConsAssm_InsdAirFilmR < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "ConsAssm:InsdAirFilmR" );
	else if (lDBID_Mat_CodeCat < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "Mat:CodeCat" );
	else if (lDBID_Mat_RVal < 1)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "Mat:RVal" );
	else if (pPropType_MatRef == NULL)
		sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property type pointer." ).arg( "ConsAssm:MatRef" );
	else
	{	int i=0, iNumMatLayers = 0, iStatus=0, iStatus2=0, iSpecialVal;
		double fNonCompositeRVal = 0, fMatRVal=0;
		int iCompositeMatObjIdx = -1;
		BEMObject* pMatObj;
		int iMaxNumLayers = pPropType_MatRef->getNumValues();
		int iFirstBlankIdx = -1;
		QString sMatCodeCat;
		for (; (i < iMaxNumLayers && sUFactorErr.isEmpty()); i++)
		{	if (BEMPX_GetObject( lDBID_ConsAssm_MatRef + i, pMatObj, -1, iConsAssmObjIdx ) && pMatObj && pMatObj->getClass())
			{	if (iFirstBlankIdx >= 0)
					sUFactorErr = QString( "ConsAssmUFactor Error:  ConsAssm object '%1' has gap in material references (~items %2/%3)." ).arg( sConsAssmName, QString::number( iFirstBlankIdx+1 ), QString::number( i+1 ) );  // ConsAssm objects should not have material gaps
				else
				{	int iMatObjIdx = BEMPX_GetObjectIndex( pMatObj->getClass(), pMatObj );			assert( iMatObjIdx >= 0 );
					if (iMatObjIdx >= 0)
					{	BEMPX_GetString( lDBID_Mat_Name, sMatName, FALSE, 0, -1, iMatObjIdx );		assert( !sMatName.isEmpty() );
               	if (!BEMPX_GetString( lDBID_Mat_CodeCat, sMatCodeCat, FALSE, 0, -1, iMatObjIdx ) || sMatCodeCat.isEmpty())
							sUFactorErr = QString( "ConsAssmUFactor Error:  Error retrieving or invalid CodeCat for Mat '%1' (ConsAssm '%2', mat #%3)." ).arg( sMatName, sConsAssmName, QString::number( i+1 ) );
						else
						{	iNumMatLayers++;
							sMatCodeCat = sMatCodeCat.toLower();
							if (sMatCodeCat.indexOf("composite") < 0)
							{	// this is a layer that does NOT require parallel path calcs, so simply add that layer's RVal to the total
		            //   	if (!BEMPX_SetDataFloat( lDBID_Mat_RVal, fMatRVal, -1, -1, iMatObjIdx ) || fMatRVal < 0)
								fMatRVal = BEMPX_GetFloatAndStatus( lDBID_Mat_RVal, iStatus, iSpecialVal, iError, iMatObjIdx );
								if (iStatus < 1 || fMatRVal < 0)
									sUFactorErr = QString( "ConsAssmUFactor Error:  Errant or missing material layer R-value for ConsAssm '%1', layer %2 (%3)." ).arg( sConsAssmName, QString::number( i+1 ), sMatName );
								else
									fNonCompositeRVal += fMatRVal;
							}
							else
							{	// this layer is a Composite layer that requires parallel path calcs
								if (iCompositeMatObjIdx >= 0)
									sUFactorErr = QString( "ConsAssmUFactor Error:  Multiple composite material layers found for ConsAssm '%1' (layers %2 & %3)." ).arg( sConsAssmName, QString::number( iCompositeMatObjIdx+1 ), QString::number( i+1 ) );
								else
									iCompositeMatObjIdx = iMatObjIdx;
							}
						}
					}
				}
			}
			else if (iFirstBlankIdx < 0)
				iFirstBlankIdx = i;
		}

		if (sUFactorErr.isEmpty() && iNumMatLayers < 1)  // no errors (yet)
		{
	// post error if no material layers found ???
		}

		if (sUFactorErr.isEmpty())  // no errors (yet)
		{
	//		double fOutFilmR, fInFilmR;
	//		if (!BEMPX_SetDataFloat( lDBID_ConsAssm_OutsdAirFilmR, fOutFilmR, -1, -1, iConsAssmObjIdx ) || fOutFilmR < 0)
			double fOutFilmR = BEMPX_GetFloatAndStatus( lDBID_ConsAssm_OutsdAirFilmR, iStatus , iSpecialVal, iError, iConsAssmObjIdx );
			double fInFilmR  = BEMPX_GetFloatAndStatus( lDBID_ConsAssm_InsdAirFilmR , iStatus2, iSpecialVal, iError, iConsAssmObjIdx );
			if (iStatus < 1 || fOutFilmR < 0)
				sUFactorErr = QString( "ConsAssmUFactor Error:  Error retrieving or invalid OutsdAirFilmR for ConsAssm '%1'." ).arg( sConsAssmName );
	//		else if (!BEMPX_SetDataFloat( lDBID_ConsAssm_InsdAirFilmR, fInFilmR, -1, -1, iConsAssmObjIdx ) || fInFilmR < 0)
			else if (iStatus < 1 || fInFilmR < 0)
				sUFactorErr = QString( "ConsAssmUFactor Error:  Error retrieving or invalid InsdAirFilmR for ConsAssm '%1'." ).arg( sConsAssmName );
			else
				fNonCompositeRVal += (fOutFilmR + fInFilmR);
		}

		if (sUFactorErr.isEmpty() && fNonCompositeRVal > 0)  // no errors (yet)
		{	if (iCompositeMatObjIdx < 0)
				dUFactor = 1.0 / fNonCompositeRVal;
			else
			{	// Take into account COMPOSITE material layer
				long lDBID_Proj_WoodFrmRPerIn = BEMPX_GetDatabaseID( "WoodFrmRPerIn", iCID_Proj );
				if (lDBID_Proj_WoodFrmRPerIn < 1)
					sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve %1 property ID." ).arg( "Proj:WoodFrmRPerIn" );

				long	lDBID_Mat_FrmMat, lDBID_Mat_FrmDepthVal, lDBID_Mat_FrmFacCav, lDBID_Mat_FrmFacMembers, lDBID_Mat_FrmFacHeaders,
						lDBID_Mat_CavityIns, lDBID_Mat_HeaderIns;
				long*     plaMatPropDBID[] = {	&lDBID_Mat_FrmMat, &lDBID_Mat_FrmDepthVal, &lDBID_Mat_FrmFacCav, &lDBID_Mat_FrmFacMembers,
															&lDBID_Mat_FrmFacHeaders, &lDBID_Mat_CavityIns, &lDBID_Mat_HeaderIns, NULL };
				const char* pszaMatProps[] = { "FrmMat", "FrmDepthVal", "FrmFacCav", "FrmFacMembers", "FrmFacHeaders", "CavityIns", "HeaderIns" };
				int idx = -1;
				while (plaMatPropDBID[++idx] != NULL && sUFactorErr.isEmpty())
				{	*plaMatPropDBID[idx] = BEMPX_GetDatabaseID( pszaMatProps[idx], iCID_Mat );
					if (*plaMatPropDBID[idx] < 1)
						sUFactorErr = QString( "ConsAssmUFactor Error:  unable to retrieve Mat:%1 property ID." ).arg( pszaMatProps[idx] );
				}
				if (sUFactorErr.isEmpty())
				{	QString sFrmMat;
					BEMPX_GetString( lDBID_Mat_Name, sMatName, FALSE, 0, -1, iCompositeMatObjIdx );		assert( !sMatName.isEmpty() );
              	if (!BEMPX_GetString( lDBID_Mat_FrmMat, sFrmMat, FALSE, 0, -1, iCompositeMatObjIdx ) || sFrmMat.isEmpty())
						sUFactorErr = QString( "ConsAssmUFactor Error:  Errant or missing composite material framing selection for ConsAssm '%1', layer %2 (%3)." ).arg( sConsAssmName, QString::number( i+1 ), sMatName );
					else if (sFrmMat.compare("Wood", Qt::CaseInsensitive))
					{	// for framing materials OTHER THAN Wood, R-value should already be set via table look-up (in previous rules)
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_RVal, fMatRVal, -1, -1, iCompositeMatObjIdx ) || fMatRVal < 0)
						fMatRVal = BEMPX_GetFloatAndStatus( lDBID_Mat_RVal, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1 || fMatRVal < 0)
							sUFactorErr = QString( "ConsAssmUFactor Error:  Errant or missing composite material layer R-value for ConsAssm '%1', material layer %2." ).arg( sConsAssmName, sMatName );
						else
						{	fNonCompositeRVal += fMatRVal;
							dUFactor = 1.0 / fNonCompositeRVal;
						}
					}
					else
					{	// Calculate Parallel Path Overall U-factor for Wood framed surface
						double fFrmDepthVal, fWoodFrmRPerIn, fFrmFacCav, fFrmFacMembers, fFrmFacHeaders, fCavityIns, fHeaderIns;
						QString sBadProp, sBadProps;
				//		if (!BEMPX_SetDataFloat( lDBID_Proj_WoodFrmRPerIn, fWoodFrmRPerIn, -1, -1, -1 )  ||  fWoodFrmRPerIn <= 0 )
						fWoodFrmRPerIn = BEMPX_GetFloatAndStatus( lDBID_Proj_WoodFrmRPerIn, iStatus, iSpecialVal, iError, 0 );
						if (iStatus < 1  ||  fWoodFrmRPerIn <= 0 )
						{	sBadProp = QString( " & Proj:WoodFrmRPerIn (%1 must be > 0)" ).arg( QString::number( fWoodFrmRPerIn )	);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_FrmDepthVal  ,				fFrmDepthVal  , -1, -1, iCompositeMatObjIdx )  ||  fFrmDepthVal   <= 0 )
						fFrmDepthVal = BEMPX_GetFloatAndStatus( lDBID_Mat_FrmDepthVal, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1  ||  fFrmDepthVal   <= 0 )
						{	sBadProp = QString( " & FrmDepthVal (%1 must be > 0)" ).arg(		QString::number( fFrmDepthVal )	);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_FrmFacCav    ,				fFrmFacCav    , -1, -1, iCompositeMatObjIdx )  ||  fFrmFacCav     <  0 )
						fFrmFacCav = BEMPX_GetFloatAndStatus( lDBID_Mat_FrmFacCav, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1  ||  fFrmFacCav     <  0 )
						{	sBadProp = QString( " & FrmFacCav (%1 must be >= 0)" ).arg(			QString::number( fFrmFacCav )		);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_FrmFacMembers,				fFrmFacMembers, -1, -1, iCompositeMatObjIdx )  ||  fFrmFacMembers <  0 )
						fFrmFacMembers = BEMPX_GetFloatAndStatus( lDBID_Mat_FrmFacMembers, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1  ||  fFrmFacMembers <  0 )
						{	sBadProp = QString( " & FrmFacMembers (%1 must be >= 0)" ).arg(	QString::number( fFrmFacMembers )	);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_FrmFacHeaders,				fFrmFacHeaders, -1, -1, iCompositeMatObjIdx )  ||  fFrmFacHeaders <  0 )
						fFrmFacHeaders = BEMPX_GetFloatAndStatus( lDBID_Mat_FrmFacHeaders, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1  ||  fFrmFacHeaders <  0 )
						{	sBadProp = QString( " & FrmFacHeaders (%1 must be >= 0)" ).arg(	QString::number( fFrmFacHeaders )	);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_CavityIns    ,				fCavityIns    , -1, -1, iCompositeMatObjIdx )  ||  fCavityIns     <  0 )
						fCavityIns = BEMPX_GetFloatAndStatus( lDBID_Mat_CavityIns, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1 ||  fCavityIns     <  0 )
						{	sBadProp = QString( " & CavityIns (%1 must be >= 0)" ).arg(			QString::number( fCavityIns )		);		sBadProps += sBadProp;		}
				//		if (!BEMPX_SetDataFloat( lDBID_Mat_HeaderIns    ,				fHeaderIns    , -1, -1, iCompositeMatObjIdx )  )
						fHeaderIns = BEMPX_GetFloatAndStatus( lDBID_Mat_HeaderIns, iStatus, iSpecialVal, iError, iCompositeMatObjIdx );
						if (iStatus < 1)
						{	sBadProp = QString( " & HeaderIns (%1 must be >= 0)" ).arg(			QString::number( fHeaderIns )		);		sBadProps += sBadProp;		}

						if (!sBadProps.isEmpty())
							sUFactorErr = QString( "ConsAssmUFactor Error:  Errant layer value(s) for ConsAssm '%1', Mat '%2':  %3." ).arg( sConsAssmName, sMatName, sBadProps.right( sBadProps.length()-3 ) );
						else if (!WithinMargin(    (fFrmFacCav + fFrmFacMembers + fFrmFacHeaders), 1.0, 0.01 ))
							sUFactorErr = QString( "ConsAssmUFactor Error:  Sum of framing, cavity & header fractions (%1) not = 1.0 for ConsAssm '%2' & Wood composite material layer '%3'." ).arg(
															QString::number( (fFrmFacCav + fFrmFacMembers + fFrmFacHeaders) ), sConsAssmName, sMatName );
						else
						{	double dFracAdj = 1.0 / (fFrmFacCav + fFrmFacMembers + fFrmFacHeaders);
							dUFactor = 0.0;
							if (fFrmFacCav > 0 && fCavityIns >= 0)
								dUFactor += ((1.0 / (fNonCompositeRVal + fCavityIns)) * fFrmFacCav * dFracAdj);
							if (fFrmFacMembers > 0 && (fFrmDepthVal * fWoodFrmRPerIn) >= 0)
								dUFactor += ((1.0 / (fNonCompositeRVal + (fFrmDepthVal * fWoodFrmRPerIn))) * fFrmFacMembers * dFracAdj);
							if (fFrmFacHeaders > 0 && fHeaderIns >= 0)
								dUFactor += ((1.0 / (fNonCompositeRVal + fHeaderIns)) * fFrmFacHeaders * dFracAdj);
							assert( dUFactor < (1 / fNonCompositeRVal) );
						}
					}
				}
			}
		}
	}

	if (!sUFactorErr.isEmpty())
	{	ExpSetErr( error, EXP_RuleProc, sUFactorErr );
		assert( dUFactor < 0 );  // make sure...
		dUFactor = -1;
	}

	return dUFactor;
}	// ConsAssmUFactor
//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// class XMAT, class XCONS: temporary representation of a Cons
//					re calculation of U-factors and other attributes
///////////////////////////////////////////////////////////////////////////////
class XMAT		// temporary material (from Mat object)
{
	friend class XCONS;

	enum { xmatNEEDWRITE=1 };
	QString xm_Name;		// name of material
	int xm_status;			// status bits this XMAT
							//  xmatNEEDWRITE: this material should be
							//        written back to database (see xc_StoreResults())
	double xm_Thickness;	// thickness, in (or -1 if not defined)
	double xm_Density;		// density, lb/ft3
	double xm_SpecHeat;		// spec ht, Btu/lb-F
	double xm_Conductivity;	// conductivity, Btuh-ft/ft2-F
							//   used for U-factor calculation
	double xm_ConductivityQII; // conductivity, Btuh-ft/ft2-F
							// adjusted per Quality Insulation Installation rules
							//   same as xm_Conductivity if project will be inspected
							//   otherwise degraded for e.g. cavity insulation materials
							// used for simulation
	double xm_ConductivityCT;	// conductivity temperature coefficient, 1/F
	double xm_HeatCap;		// heat capacity, Btu/F-ft2
	double xm_Resistance;	// resistance at actual thickness, ft2-F/Btuh
	double xm_RValPerInch;	// resistance per inch, ft2-F/Btuh-in

	static int  xm_matCompID;
	static long xm_NameID;
	static long xm_ThicknessID;
	static long xm_DensityID;     
	static long xm_SpecHeatID;    
	static long xm_ConductivityID;
	static long xm_ConductivityQIIID;
	static long xm_ConductivityCTID;
	static long xm_HeatCapID;    
	static long xm_ResistanceID; 
	static long xm_cseMATERIALID; 
	static long xm_RValPerInchID;

public:
	XMAT();
	void xm_Init();
	BOOL xm_IsEqual( const XMAT& m) const;
	BOOL operator ==(const XMAT& m) const { return xm_IsEqual( m); }
	BOOL operator !=(const XMAT& m) const { return !xm_IsEqual( m); }

	BOOL xm_IsEmpty() const { return xm_Resistance == 0.0 && xm_RValPerInch == 0.0; }
	int xm_FromDB( int iObjIdx, int iObjType=BEMO_User);
	int xm_ToDB( int iObjIdx, int iObjType=BEMO_User) const;
	int xm_FromLib( const char* libName);
	void xm_SetRes( double res) { xm_Resistance = res; }		// TODO
	int xm_Mix( const XMAT& m, double fArea, double fVol);
	int xm_SetDerived();
	int xm_AdjustThickness( double newThkns, int options);
	void xm_SetConductivity( int iQII, double k)
	{	(iQII ? xm_ConductivityQII : xm_Conductivity) = k; }
	double xm_GetConductivity( int iQII) const
	{	return iQII ? xm_ConductivityQII : xm_Conductivity; }
	double xm_GetLateralConductivity( int iQII) const
	{	// conductivity at right angles to heat flow (across construction)
		//    Btuh-ft/ft2-degF
		return xm_GetConductivity( iQII) * xm_Thickness / 12.0;
	}
	double xm_GetResistivity( int iQII) const;
	double xm_GetResistance( int iQII) const
	{	return xm_Thickness * xm_GetResistivity( iQII) / 12.0; }

};		// class XMAT
//-----------------------------------------------------------------------------
class XCONS
{
	enum { XCONS_MAXLAYRS=10 };		// # of layers supported
	enum { XCONS_MAXPATHS=4 };		// # of paths supported
									//   1 = concrete etc
									//   2 = wood/steel framed
									//   3 = ?
									//   4 = double framed
									//       cavity, frm ins, frm out, frm through
	enum { XCONS_PATHCAV, XCONS_PATHFRM1, XCONS_PATHFRM2, XCONS_PATHFRM3 };

	const QString& xc_consName;	// source cons name
	int xc_consIdx;				// source Cons object index
	int xc_UfactorCalcMethod;	// U-factor calculation method
								//   0

	int xc_CanAssignTo;			// "Can Assign To" code (info only, not used)
	int xc_Type;				// type
	int xc_InsideLayerFirst;	// nz iff layer 0 is inside (else layer 0 is outside)

	int xc_NumPaths;			// from DB: # of heat flow paths (1=concrete etc, 2=framed, 4=offset framed)
	int xc_NumLayerMats;		// number of actual layers per caller

	double xc_OutsdAirFilmR;		// outside surface resistance, °F-ft2-h/Btu
	double xc_InsdAirFilmR;		// inside surface resistance, °F-ft2-h/Btu

	double xc_FramingFactor;		// framing factor re wood and metal framed constructions
								//    = fraction of face area that is framing material (remainder = cavity)
	double xc_FramingFactorEff;	// effective framing factor
								//   wood frame: xc_FramingFactor for wood frame
								//   metal frame: (xc_FrameW / xl_LPFrameFlangeWidth) * xc_FramingFactor
	double xc_FrameW;			// effective framing width for steel framed constructions, in
								//   xc_FrameW > xl_LPFrameFlangeWidth re high conduction thru framing
								//   user input or calculated (see xc_UModifiedZoneMethod)
								//   
	int xc_FrameWCanBeInput;	// nz iff FrameW user input is allowed (e.g. due to research mode)
	int xc_SpecifyFrameW;		// nz iff user specified FrameWInput should be used
	double xc_FrameWInput;		// user input FrameW, in


	// NOTE 1: these values must be consistent with ruleset enum definitions
	// NOTE 2: code depends on values (see e.g. xc_IsFurred())
	enum LAYERTYPE { ltyCONTINUOUS=0, ltyWOODFRAMED, ltySTEELFRAMED,
		ltyWOODFURRING=11, ltySTEELFURRING };
	struct XCONSL
	{
#if 0	// restore if needed (e.g. re double wall construction), 4-11-2014
x		double xl_fFrm;			// framing factor for layer
x								//  = 0 - 1, -1 = not framed
#endif
		double xl_thkns;		// layer thickness, in
								//   Note: may possible for xl_mat[ ].xm_Thickness to differ
								//     example: ?
		int xl_LPType;				// Cons::LayerParams layer type, ltyXXX defined above
		double xl_LPFrameSpacing;	//   framed or furred: framing spacing
		double xl_LPFrameWebWidth;	//   framing web width, in (very small for steel)
		double xl_LPFrameFlangeWidth; // framing flange width, in (typically 1.5 in)
		double xl_LPFrameWeight;	// weight of framing, lb/ft
								//   used for deriving metal framing mixed material properties
								//     to account for mass of flange returns etc. that are not
								//     included in conductivity analysis
								//   if 0, derived from geometry
		double xl_LPFKnockOut;	// steel framing "knockout" fraction
								//   re holes in metal framing
								//   implementation applies this factor to web
								//      thickness, so not known how to determine
								//		meaningful values
		double xl_symVal[ XCONS_MAXPATHS];	// user choice value that was source of
											//   this layer (info only, not used)
		XMAT xl_mat[ XCONS_MAXPATHS];		// layer materials
		XCONSL() { xl_Init(); }
		void xl_Init();
		bool xl_LimitSteelFramed();
		int xl_MixFurred();
		int xl_MixSteelFramed( double W, double R);
	} xc_L[ XCONS_MAXLAYRS];

	double xc_RPath[ XCONS_MAXPATHS];	// calculated path R-factors
										//   ft2-F/Btuh

	QString xc_errMsg;					// error message
										//    if empty, no errors so far

								// static IDs etc; constant, resolve once
	static int xc_staticsOK;			
	static int xc_consCompID;
	static long xc_UfactorCalcMethodID;
	static long xc_CanAssignToID;
	static long xc_TypeID;
	static long xc_NumPathsID;
	static long xc_NumLayerMatsID;
	static long xc_InsideLayerFirstID;
	static long xc_OutsdAirFilmRID;
	static long xc_InsdAirFilmRID;
	static long xc_FramingFactorID;
	static long xc_FrameWCanBeInputID;
	static long xc_SpecifyFrameWID; 
	static long xc_FrameWInputID;
	static long xc_FrameWID;

	static int xc_layerParamsCompID;
	static long xc_LPTypeID;                
	static long xc_LPFrameSpacingID;
	static long xc_LPFrameWebWidthID;
	static long xc_LPFrameFlangeWidthID;
	static long xc_LPFrameWeightID;
	static long xc_LPFKnockOutID;

	static long xc_ThicknessID;
	static long xc_FrameLayerSymValID;
	static long xc_CavityLayerSymValID;
	static long xc_FramePathMatsID;
	static long xc_CavityPathMatsID;
	static long xc_LayerParametersID;
	static long xc_PathCodeRValueID;
#if 0
x	int xc_NumLayersSel;		// from DB: # of screen selectable layers
x								//    actual # of layers can be less (if user selects "none" or equivalent)
x	static long xc_WallExtFinishLayerID;
x	static long xc_FlrExtFinishLayerID;
x	static long xc_NumLayersID;
x	static long xc_FrameLayerMapIdxID;
x	static long xc_LayerPropertyIndexID;
#endif

public:
	XCONS::XCONS( const QString& consName, int consIdx);
	void xc_Init();
	int xc_Err( const char* fmt, ...)
	{	va_list ap; va_start (ap, fmt);
		return xc_ErrV( fmt, ap);
	}
	int xc_ErrV( const char* fmt, va_list ap=NULL);
	BOOL xc_IsOK() const { return xc_errMsg.isEmpty(); }
	QString xc_GetErrMsg() const { return xc_errMsg; }
	int xc_Fill();
	int xc_GetDBFloat( long propID, double &v, int iObjIdx=-1, double vDflt=-999.0, BOOL bMsgMissing=TRUE);
	int xc_GetDBInt( long propID, int &v, int iObjIdx=-1, int vDflt=-999, BOOL bMsgMissing=TRUE);
	int xc_GetDBMat( long propID, XMAT& xm, BOOL bMsgMissing=TRUE);
	int xc_GetDBPath( int iL, int iP, long matID, long symID);
	int xc_SetDBMat( long propID, const XMAT& xm);
#if 0
x	int xc_GetLibMat( const char* libName, XMAT& xm, BOOL bMsgMissing=TRUE);
x	int xc_GetOrGenMat(	int iL,	int iP, long matID,	long symID);
#endif
	int xc_GetDBLayerParams( int iL);
	int xc_GetDBLayer( int iL);
	int xc_IsFurred( int iL) const
	{	return xc_L[ iL].xl_LPType >= ltyWOODFURRING; }
	int xc_GetCompID( const char* compName);
	long xc_GetPropID( const char* propName, int compID=-1);
	int xc_DoExtFinishLayer( long ID);
	BEMPropertyType* xc_GetPropType( long propID);
	int xc_Setup();
	double xc_GetFFrm( int iP) const;
	int xc_NumLayers() const { return xc_NumLayerMats; }
	int xc_GetLayerIdx( int iL) const
	{	return xc_InsideLayerFirst ? xc_NumLayers() - iL - 1 : iL; }
	BOOL xc_IsFrameWInput() const
	{	return xc_FrameWCanBeInput && xc_SpecifyFrameW; }
	double xc_UFactor( int iMethod=-1);
	double xc_UParallelPath( int iQII);
	double xc_UIsothermalPlanes( int iQII);
	double xc_UModifiedZoneMethod( int iQII, int options);
	int xc_StoreResults();
	template <typename T> static T bracket( T vMin, T v, T vMax)
	{	return v < vMin ? vMin : v > vMax ? vMax : v; }
};		// class XCONS
//=============================================================================
XMAT::XMAT()
{	xm_Init();
}
//-----------------------------------------------------------------------------
void XMAT::xm_Init()
{
	xm_status = 0;
	xm_Name.clear();
	xm_Thickness = 0.0;
	xm_Density = 0.0;      
	xm_SpecHeat = 0.0;
	xm_Conductivity = 0.0;
	xm_ConductivityQII = 0.0;
	xm_ConductivityCT = 0.0;
	xm_HeatCap = 0.0;
	xm_Resistance = 0.0;
	xm_RValPerInch = 0.0;
}		// XMAT::xm_Init
//-----------------------------------------------------------------------------
BOOL XMAT::xm_IsEqual( const XMAT& m) const
{
	return xm_Thickness == m.xm_Thickness
		&& xm_Density == m.xm_Density
		&& xm_SpecHeat == m.xm_SpecHeat
		&& xm_Conductivity == m.xm_Conductivity
		&& xm_ConductivityQII == m.xm_ConductivityQII
		&& xm_ConductivityCT == m.xm_ConductivityCT
		&& xm_HeatCap == m.xm_HeatCap
		&& xm_Resistance == m.xm_Resistance
		&& xm_RValPerInch == m.xm_RValPerInch;
	// xm_status: do not compare
	// xm_Name: do not compare
}		// XMAT::xm_IsEqual
//-----------------------------------------------------------------------------
int XMAT::xm_FromDB(
	int iObjIdx,	// index of Mat object
	int iObjType	/*=BEMO_USER*/)
// returns 1 TODO: should there be some checking?
{
//	BOOL DLLAPI __cdecl BEMPX_GetString(  long lDBID, QString& sStr,
//                 BOOL bAddCommas=TRUE, int iPrecision=0,
//                 int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//                 const char* pszDefault=NULL, long lDBID2=0, int iBEMProcIdx=-1 );

	BEMPX_GetString( xm_NameID, xm_Name, FALSE, 0, -1, iObjIdx, iObjType, "?");

	int iSpclVal, iErr;
// #define MATVAL( m, vDflt) BEMPX_SetDataFloat( m##ID, m, vDflt, BEMP_Flt, iObjIdx, iObjType);
#define MATVAL( m, vDflt) BEMPX_GetFloat( m##ID, iSpclVal, iErr, iObjIdx, (BEM_ObjType) iObjType, -1, false, vDflt );

	xm_Thickness       = MATVAL( xm_Thickness, -1.0);
	xm_Density         = MATVAL( xm_Density, 0.0);      
	xm_SpecHeat        = MATVAL( xm_SpecHeat, 0.0);
	xm_Conductivity    = MATVAL( xm_Conductivity, -1.0);
	xm_ConductivityQII = MATVAL( xm_ConductivityQII, -1.0);
	xm_ConductivityCT  = MATVAL( xm_ConductivityCT, 0.0);
	xm_HeatCap         = MATVAL( xm_HeatCap, 0.0);
	xm_Resistance      = MATVAL( xm_Resistance, 0.0);
	xm_RValPerInch     = MATVAL( xm_RValPerInch, 0.0);

	xm_status = 0;

	return 1;

#undef MATVAL
}		// XMAT::xm_FromDB
//-----------------------------------------------------------------------------
int XMAT::xm_ToDB(
	int iObjIdx,		// index of Mat object
	int iObjType /*=BEMO_USER*/) const
// returns 1 TODO: should there be some checking?
{
	iObjType;

#define MATVAL( m) BEMPX_SetBEMData( m##ID, BEMP_Flt, (void *)&m, BEMO_User, iObjIdx);
	MATVAL( xm_Thickness);
	MATVAL( xm_Density);      
	MATVAL( xm_SpecHeat);
	MATVAL( xm_Conductivity);
	MATVAL( xm_ConductivityQII);
	MATVAL( xm_ConductivityCT);
	MATVAL( xm_HeatCap);
	MATVAL( xm_Resistance);
	MATVAL( xm_RValPerInch);
	return 1;
#undef MATVAL
}		// XMAT::xm_ToDB
//-----------------------------------------------------------------------------
double XMAT::xm_GetResistivity(		// get material resistance
	int iQII) const	// 0: get res based on xm_Conductivity (nominal value)
					// 1: get res based on xm_ConductivityQII
					//    re Insulation Construction Quality adjustment
					//    QII value is same as nominal if building ICQ=Improved
					//    else maybe higher if 
// returns material resistance, ft2-F/Btuh
{
	double k = xm_GetConductivity( iQII);
	double res = k > .001 ? 1.0 / k : 0.0;
	return res;
}		// XMAT::xm_GetResistivity
//-----------------------------------------------------------------------------
int XMAT::xm_Mix(		// mix in a material (aka 'mush')
	const XMAT& m,	// material to mix in
	double fArea,	// fraction of m to mix in by face area
	double fVol)		// fraction of mix volume taken from m

// Notes:
//   fArea is fraction re perpendicular heat flow
//         determines mixed conductivity (and thus resistance)
//   fVol is actual mix fraction
//         determines density, specific heat, and HC
//   fArea = fVol for wood framing (rectangular framing)
//   usually fVol > fArea for steel to account for flanges etc.

// returns 0 on fail (one/both thicknesses missing)
//         1 and *this updated if success
{
	if (xm_Thickness <= 0.0 || m.xm_Thickness <= 0.0)
		return 0;		// thickness missing
	// double thickRat = m.xm_Thickness / xm_Thickness;		// thickness ratio
	double thickRat = 1.0;

	double fArea1 = 1.0 - fArea;
	double fAreaX = fArea * thickRat;
	xm_Conductivity    = fArea1*xm_Conductivity    + fAreaX*m.xm_Conductivity;
	xm_ConductivityQII = fArea1*xm_ConductivityQII + fAreaX*m.xm_ConductivityQII;
	xm_ConductivityCT  = fArea1*xm_ConductivityCT  + fArea*m.xm_ConductivityCT;

	double fVol1 = 1.0 - fVol;
	// density: combine by volume
	double denMix  = fVol1 * xm_Density + fVol * m.xm_Density * thickRat;

	// specfic heat: combine by mass
	if (denMix > 0.0)
		xm_SpecHeat = (fVol1*xm_Density*xm_SpecHeat + fVol*m.xm_Density*m.xm_SpecHeat) / denMix;
	else
		xm_SpecHeat = fVol1*xm_SpecHeat + fVol*m.xm_SpecHeat;	// density not known

	xm_Density = denMix;

	return xm_SetDerived();		// derive xm_Resistance and xm_RValPerInch
								//   from xm_Conductivity

}	// XMAT::xm_Mix
//-----------------------------------------------------------------------------
int XMAT::xm_SetDerived()		// derive inter-dependent properties
// return 1 on success
//        0 if insufficient properties
{	
	int ret = 1;
	if (xm_Thickness <= 0.0)
		ret = 0;
	double thknsFt = xm_Thickness / 12.0;	// thickness in ft
	if (ret)
	{	// derive consistent conductivity / resistance
		if (xm_ConductivityQII > 0.0)
		{	xm_Resistance = thknsFt / xm_ConductivityQII;
			xm_RValPerInch = xm_Resistance / xm_Thickness;
		}
		else if (xm_RValPerInch > 0.0)
		{	xm_Resistance = xm_RValPerInch * xm_Thickness;
			xm_ConductivityQII = (1.0/12.0) / xm_RValPerInch;
		}
		else if (xm_Resistance > 0.0)
		{	xm_ConductivityQII = thknsFt / xm_Resistance;
			xm_RValPerInch = xm_Resistance / xm_Thickness;
		}
		else
			ret = 0;
	}
	if (ret)
		xm_HeatCap = xm_SpecHeat * xm_Density * thknsFt;	// Btu/ft2
	return ret;
}		// XMAT::xm_SetDerived
//-----------------------------------------------------------------------------
#if 0
incomplete / unnecessary: now handled in rules
int XMAT::xm_AdjustThickness(		// adjust thickness
	double thknsNew,	// new thickness, in
	int options)		// 1: preserve resistance
// return 1 on success
//        0 if insufficient properties
{	
	int ret = 1;
#if 0
	if (xm_Thickness <= 0.)
		ret = 0;
	else
	{	double thickRat = thknsNew / xm_Thickness;
		xm_Thickness = thknsNew;
		if (options & 1)
		{	

		}
	}
	int ret = 1;
	if (xm_Thickness <= 0.0)
		ret = 0;
	double thknsFt = xm_Thickness / 12.0;	// thickness in ft
	if (ret)
	{	// derive consistent conductivity / resistance
		if (xm_ConductivityQII > 0.0)
		{	xm_Resistance = thknsFt / xm_ConductivityQII;
			xm_RValPerInch = xm_Resistance / xm_Thickness;
		}
		else if (xm_RValPerInch > 0.0)
		{	xm_Resistance = xm_RValPerInch * xm_Thickness;
			xm_ConductivityQII = (1.0/12.0) / xm_RValPerInch;
		}
		else if (xm_Resistance > 0.0)
		{	xm_ConductivityQII = thknsFt / xm_Resistance;
			xm_RValPerInch = xm_Resistance / xm_Thickness;
		}
		else
			ret = 0;
	}
	if (ret)
		xm_HeatCap = xm_SpecHeat * xm_Density * thknsFt;	// Btu/ft2
#endif
	return ret;
}		// XMAT::xm_AdjustThickness
//-----------------------------------------------------------------------------
out of service
int XMAT::xm_FromLib(
	const char* libName)
// returns 1: success (*this filled, -1 for missing properties)
//         0: error (no msg)
{
	int iError;
	BEMObject* pMatObj = BEMPX_GetObjectByName( xm_matCompID, iError, libName,
                                        BEMO_RuleLib );

	int ret = 0;
	int iObjIdx = -1;
	if (pMatObj && pMatObj->getClass())
		iObjIdx = BEMPX_GetObjectIndex(  pMatObj->getClass(), pMatObj);

	if (iObjIdx >= 0)
		ret = xm_FromDB( iObjIdx, BEMO_RuleLib);

	if (!ret)
		xm_Init();

	return ret;
}		// XMAT::xm_FromLib
#endif
//-----------------------------------------------------------------------------
XCONS::XCONS(	// c'tor
	const QString& consName,	// name of source Cons
	int consIdx)				// object idx of source Cons
	: xc_consName( consName), xc_consIdx( consIdx)
{
	xc_Init();
}		// XCONS::XCONS
//-----------------------------------------------------------------------------
void XCONS::xc_Init()
{	// xc_consName, xc_consIdx: do not change
	xc_NumPaths = 0;
	xc_NumLayerMats = 0;
	xc_OutsdAirFilmR = 0.0;
	xc_InsdAirFilmR = 0.0;
	xc_UfactorCalcMethod = 0;
	xc_CanAssignTo = 0;
	xc_Type = 0;
	xc_InsideLayerFirst = 0;
	xc_FramingFactor = 0.0;
	xc_FramingFactorEff = 0.0;
	xc_FrameWCanBeInput = 0;
	xc_SpecifyFrameW = 0;
	xc_FrameWInput = 0.0;
	xc_FrameW = 0.0;

	for (int iP=0; iP < XCONS_MAXPATHS; iP++)
		xc_RPath[ iP] = 0.0;

	for (int iL=0; iL<XCONS_MAXLAYRS; iL++)
		xc_L[ iL].xl_Init();
}		// XCONS::xc_Init
//-----------------------------------------------------------------------------
void XCONS::XCONSL::xl_Init()
{	
	xl_thkns = 0.0;
#if 0	// restore if needed, 4-11-2014
x	xl_fFrm = 0.0;
#endif
	xl_LPType = 0;
	xl_LPFrameSpacing = 0.0;
	xl_LPFrameWebWidth = 0.0;
	xl_LPFrameFlangeWidth = 0.0;
	xl_LPFrameWeight = 0.0;
	xl_LPFKnockOut = 0.0;
	for (int iP=0; iP<XCONS_MAXPATHS; iP++)
	{	xl_symVal[ iP] = 0.0;
		xl_mat[ iP].xm_Init();
	}
}		// XCONSL::xl_Init
//-----------------------------------------------------------------------------
int XCONS::xc_ErrV( const char* fmt, va_list ap /*=NULL*/)
// returns -1
{
	QString pfx = QString( "Cons '%1': " ).arg( xc_consName );
	QString msg;
	if (ap)
		msg.vsprintf( fmt, ap );
	else
		msg = fmt;
	xc_errMsg = pfx + msg;
	return -1;
}		// XCONS::xc_ErrV
//-----------------------------------------------------------------------------
#if 0
incomplete / unnecessary: now handled in rules
bool XCONS::XCONSL::xl_LimitSteelFramed()	// limit properties of metal framed layer
// WHY: keep characteristics within limits of underlying regression dataset
{

	if (xl_thkns <= 5.5)
		return false;

	// limit steel framed layer thickness to 2x6
	double thknsWas = xl_thkns;
	xl_thkns = 5.5;
	for (int iP=0; iP<XCONS_MAXPATHS; iP++)
	{	if (xl_mat[ iP].xm_Thickness > 0)
		{	xl_mat[ iP].xm_AdjustThickness( xl_thkns, iP != XCONS_PATHFRM1);
			xl_mat[ iP].xm_status |= XMAT::xmatNEEDWRITE;
		}
	}

	return true;

}		// XCONS::XCONSL::xl_LimitSteelFramed

#endif
//-----------------------------------------------------------------------------
int XCONS::XCONSL::xl_MixFurred()	// make mixed material for furred layer
// XCONS_PATHFRM1 framing material is mixed into XCONS_PATHCAV to
//   approximate overall conductivity and heat capacity

// returns 1 iff success
{
	int ret = 0;
	if (xl_thkns > 0.0 && xl_LPFrameSpacing > 0.0 && xl_mat[ XCONS_PATHFRM1].xm_Density > 0.0)
	{	double fArea = xl_LPFrameWebWidth / xl_LPFrameSpacing;	// web fraction of face area
		// volume of 1 space wide x 1 ft high, ft3
		double volTot = xl_LPFrameSpacing * xl_thkns / 144.0;
		// volume of framing in one space
		double volFrame = xl_LPFrameWeight > 0.0
			? xl_LPFrameWeight / xl_mat[ XCONS_PATHFRM1].xm_Density
			: xl_LPFrameWebWidth * xl_thkns / 144.0;
		double fVol = volFrame / volTot;
		ret = xl_mat[ XCONS_PATHCAV].xm_Mix( xl_mat[ XCONS_PATHFRM1], fArea, fVol);
		if (ret)
			xl_mat[ XCONS_PATHCAV].xm_status |= XMAT::xmatNEEDWRITE;
	}
	return ret;
}	// XCONS::XCONSL::xl_MixFurred
//-----------------------------------------------------------------------------
int XCONS::XCONSL::xl_MixSteelFramed(	// make mixed material for steel framed layer
	double W,	// width of zone to be treated as framed, in
	double R)	// resistance of framed zone, ft2-F/Btuh
// XCONS_PATHCAV material is mixed into XCONS_PATHFRM1 to approximate
//    overall conductivity and mass
// Conductivity is based on zone method calculated R for framed zone (width xc_FrameW).
// Density and specific heat are set to account for all material in the construction.

// see xc_UModifiedZoneMethod()

// returns 1 iff success

{
	int ret = 0;
	if (xl_thkns > 0.0 && W > 0.0)
	{	
		// derive fArea that results in kMix based on xm_ConductivityQII
		double kMix = (xl_thkns/12.0) / max( R, 0.001);
		double kFrm = xl_mat[ XCONS_PATHFRM1].xm_ConductivityQII;
		double kCav = xl_mat[ XCONS_PATHCAV].xm_ConductivityQII;
		double fArea = (kFrm - kCav) != 0.0
						? (kFrm - kMix) / (kFrm - kCav)
						: 0.5;

		// volume being considered
		//   = W wide, thkns deep, 1 ft high
		double volTot = W * xl_thkns / 144.0;

		// volume of frame material
		//   assume 1 framing run per W volume = 1 ft length per volume
		double volFrame;
		if (xl_LPFrameWeight > 0.0 && xl_mat[ XCONS_PATHFRM1].xm_Density > 0.0)
			// vol = 1 ft * weight (lb/ft) / density (lb/ft3)
			volFrame = xl_LPFrameWeight / xl_mat[ XCONS_PATHFRM1].xm_Density;
		else
		{	// weight or density not known, do calc from geometry
			// base on "perimeter" of C-shaped section (inches)
			double p = xl_thkns * (1.0 - xl_LPFKnockOut)		// web
				    + 2.0 * xl_LPFrameFlangeWidth			// flanges
			        + 1.0;									// flange returns (guesstimate)
			volFrame = p * xl_LPFrameWebWidth / 144.0;	// vol = perim * metal thickness
		}
		double fVol = (volTot - volFrame) / volTot;		// fraction from cavity
		ret = xl_mat[ XCONS_PATHFRM1].xm_Mix( xl_mat[ XCONS_PATHCAV], fArea, fVol);
		if (ret)
			xl_mat[ XCONS_PATHFRM1].xm_status |= XMAT::xmatNEEDWRITE;
	}
	return ret;
}	// XCONS::XCONSL::xl_MixSteelFramed
//-----------------------------------------------------------------------------
int XCONS::xc_GetCompID( const char* compName)
{
	int compID = -1;
	if (xc_IsOK())
	{	compID = BEMPX_GetDBComponentID( compName);
		if (compID < 0)
			xc_Err( "unable to retrieve %s component ID", compName);
	}
	return compID;
}	// XCONS::xc_GetCompID
//-----------------------------------------------------------------------------
long XCONS::xc_GetPropID(
	const char* propName,	// property name
	int compID /*=-1*/)		// component ID (default = xc_consCompID)
// returns propID on success
//     else -1 if error here or on any prior call
{
	long propID = -1;
	if (xc_IsOK())
	{	if (compID < 0)
			compID = xc_consCompID;
		propID = BEMPX_GetDatabaseID( propName, compID);
		if (propID < 0)
			xc_Err( "unable to retrieve '%s' property ID", propName);
	}
	return propID;

}	// XCONS::xc_GetPropID
//----------------------------------------------------------------------------
BEMPropertyType* XCONS::xc_GetPropType( long propID)
{
	BEMPropertyType* pPropType = NULL;
	if (xc_IsOK())
	{	int iError;
		pPropType = BEMPX_GetPropertyTypeFromDBID( propID, iError);
		if (!pPropType)
			xc_Err("unable to retrieve property type pointer for ID=%d (iError=%d)",
				propID, iError);
	}
	return pPropType;
}		// XCONS::xc_GetPropType
//--------------------------------------------------------------------------
// constant property IDs
//    resolved on first call by xc_Setup
int XCONS::xc_staticsOK = 0;		// status of static vals (both XCONS and XMAT)
									//   0=not set, 1=set OK, -1=set fail

int XMAT::xm_matCompID         = -1;
long XMAT::xm_NameID			= -1;
long XMAT::xm_ThicknessID       = -1;
long XMAT::xm_DensityID        = -1;     
long XMAT::xm_SpecHeatID       = -1;    
long XMAT::xm_ConductivityID   = -1;
long XMAT::xm_ConductivityQIIID  = -1;
long XMAT::xm_ConductivityCTID = -1;
long XMAT::xm_HeatCapID        = -1;    
long XMAT::xm_ResistanceID     = -1; 
long XMAT::xm_cseMATERIALID    = -1; 
long XMAT::xm_RValPerInchID = -1;

int  XCONS::xc_consCompID = -1;
long XCONS::xc_NumPathsID			 = -1;
long XCONS::xc_NumLayerMatsID        = -1;
long XCONS::xc_InsideLayerFirstID = -1;
long XCONS::xc_CanAssignToID           = -1;
long XCONS::xc_UfactorCalcMethodID     = -1;
long XCONS::xc_TypeID           = -1;
long XCONS::xc_OutsdAirFilmRID	     = -1;
long XCONS::xc_InsdAirFilmRID	     = -1;
long XCONS::xc_FramingFactorID	     = -1;
long XCONS::xc_FrameWCanBeInputID	= -1;
long XCONS::xc_SpecifyFrameWID		= -1;
long XCONS::xc_FrameWInputID		= -1;
long XCONS::xc_FrameWID				= -1;

int  XCONS::xc_layerParamsCompID = -1;
long XCONS::xc_LPTypeID			= -1;                
long XCONS::xc_LPFrameSpacingID	 = -1;;
long XCONS::xc_LPFrameWebWidthID	 = -1;
long XCONS::xc_LPFrameFlangeWidthID  = -1;
long XCONS::xc_LPFrameWeightID       = -1;
long XCONS::xc_LPFKnockOutID         = -1;

long XCONS::xc_ThicknessID		     = -1;
long XCONS::xc_FrameLayerSymValID    = -1;
long XCONS::xc_CavityLayerSymValID    = -1;
long XCONS::xc_FramePathMatsID       = -1;
long XCONS::xc_LayerParametersID       = -1;
long XCONS::xc_PathCodeRValueID       = -1;

long XCONS::xc_CavityPathMatsID      = -1;
#if 0
x long XCONS::xc_WallExtFinishLayerID  = -1;
x long XCONS::xc_FlrExtFinishLayerID  = -1;
x long XCONS::xc_NumLayersID           = -1;
x long XCONS::xc_FrameLayerMapIdxID	 = -1;
x long XCONS::xc_LayerPropertyIndexID	 = -1;
#endif

//-----------------------------------------------------------------------------
int XCONS::xc_Setup()			// setup XCONS/XMAT
// returns 1 if all OK
//        -1 error (only cause = programming error?)
{
	xc_errMsg.clear();
	if (xc_staticsOK == 0)
	{	xc_consCompID = xc_GetCompID( "Cons" );

		#define CONSPROPID( s) xc_##s##ID = xc_GetPropID( #s)
		CONSPROPID( CanAssignTo);
		CONSPROPID( Type);
		CONSPROPID( UfactorCalcMethod);
		CONSPROPID( NumPaths);
		CONSPROPID( NumLayerMats);
		CONSPROPID( InsideLayerFirst);
		CONSPROPID( OutsdAirFilmR);          
		CONSPROPID( InsdAirFilmR);
		CONSPROPID( FramingFactor);
		CONSPROPID( FrameWCanBeInput);
		CONSPROPID( SpecifyFrameW);
		CONSPROPID( FrameWInput);
		CONSPROPID( FrameW);

		CONSPROPID( Thickness);
		CONSPROPID( FrameLayerSymVal);
		CONSPROPID( CavityLayerSymVal);
		CONSPROPID( FramePathMats);
		CONSPROPID( CavityPathMats);
		CONSPROPID( LayerParameters);
		CONSPROPID( PathCodeRValue);

#if 0
		CONSPROPID( NumLayers);
		CONSPROPID( FrameLayerMapIdx);
		CONSPROPID( LayerPropertyIndex);
		CONSPROPID( MaxNumLayers);            
		CONSPROPID( RoofingLayer);            
		CONSPROPID( AbvDeckInsulLayer);       
		CONSPROPID( RoofDeckLayer);
		CONSPROPID( WallExtFinishLayer);
		CONSPROPID( FlrExtFinishLayer);
		CONSPROPID( InsideFinishLayer);       
		CONSPROPID( AtticFloorLayer);         
		CONSPROPID( FloorSurfaceLayer);       
		CONSPROPID( FlrConcreteFillLayer);    
		CONSPROPID( FloorDeckLayer);          
		CONSPROPID( SheathInsul2Layer);       
		CONSPROPID( MassLayer);               
		CONSPROPID( MassThickness);           
		CONSPROPID( FurringInsul2Layer);      
		CONSPROPID( FurringInsulLayer);       
		CONSPROPID( Furring2Layer);           
		CONSPROPID( FurringLayer);            
		CONSPROPID( CavityLayer);             
		CONSPROPID( FrameLayer);              
		CONSPROPID( SheathInsulLayer);        
		CONSPROPID( OtherSideFinishLayer);    
		CONSPROPID( FlrExtFinishLayer);       
		CONSPROPID( FrameW); 		          

		CONSPROPID( FlrExtConditions);
		CONSPROPID( RadiantBarrier);         
		CONSPROPID( RaisedHeelTruss);        
		CONSPROPID( RaisedHeelTrussHeight);  
		CONSPROPID( RoofingType);            
#endif
		#undef CONSPROPID

		// LayerParams properties
		xc_layerParamsCompID = xc_GetCompID( "LayerParams");
		#define LAYERPARAMPROPID( s) xc_LP##s##ID = xc_GetPropID( #s, xc_layerParamsCompID)
		LAYERPARAMPROPID( Type);                  
		LAYERPARAMPROPID( FrameSpacing);
		LAYERPARAMPROPID( FrameWebWidth);
		LAYERPARAMPROPID( FrameFlangeWidth);
		LAYERPARAMPROPID( FrameWeight);
		LAYERPARAMPROPID( FKnockOut);
		#undef LAYERPARAMPROPID


		// Mat properties
		XMAT::xm_matCompID = xc_GetCompID( "Mat" );
		#define MATPROPID( s) XMAT::xm_##s##ID = xc_GetPropID( #s, XMAT::xm_matCompID);
		// long lDBID_Mat_Name    = BEMPX_GetDatabaseID( "Name"   , iCID_Mat );
		MATPROPID( Name);
		MATPROPID( Thickness);
		MATPROPID( Density);
		MATPROPID( SpecHeat);
		MATPROPID( Conductivity);
		MATPROPID( ConductivityQII);
		MATPROPID( ConductivityCT);
		MATPROPID( HeatCap);
		MATPROPID( Resistance);
		MATPROPID( cseMATERIAL);
		MATPROPID( RValPerInch);
		#undef MATPROPID

		xc_staticsOK = xc_errMsg.isEmpty() ? 1 : -1;
	}
	else if (xc_staticsOK < 0)
		xc_ErrV( "invalid prior setup");	// prior call failed

	return xc_staticsOK;
}		// XCONS::xc_Setup
//-----------------------------------------------------------------------------
int XCONS::xc_GetDBFloat(		// get float property value from DB
	long propID,					// property ID
	double& v,						// returned: retrieved value
	int iObjIdx /*=-1*/,			// object index (default = xc_consIdx)
	double vDflt /*=-999.0*/,		// default value
	BOOL bMsgMissing /*=TRUE*/)		// TRUE: error if value not found

// returns: 1= success (v = DB value)
//          0= failure (v = vDflt, xc_errMsg set iff bMsgMissing)
//         -1= nop due to prior error (v = vDflt)

{	v = vDflt;
	int ret = 1;
	if (!xc_IsOK())
		ret = -1;
	else
	{	if (iObjIdx < 0)
			iObjIdx = xc_consIdx;
//		if (!BEMPX_SetDataFloat( propID, v, vDflt, BEMP_Flt, iObjIdx))
		int iStatus=0, iSpecialVal, iError;
		v = BEMPX_GetFloatAndStatus( propID, iStatus, iSpecialVal, iError, 
													iObjIdx, BEMO_User, -1, true, vDflt );
		if (iStatus < 0)
			v = vDflt;		// insurance, BEMPX_GetFloatAndStatus returns default when iStatus < 0
		if (v == vDflt)
		{	ret = 0;
			if (bMsgMissing)
			{	QString sCompParam;
				BEMPX_DBIDToDBCompParamString( propID, sCompParam );
				xc_Err( "no value found for ID=%d (%s)", propID, sCompParam.toLocal8Bit().constData() );
			}
		}
	}
	return ret;
}		// XCONS::xc_GetDBFloat
//-----------------------------------------------------------------------------
int XCONS::xc_GetDBInt(		// get integer property value from DB
	long propID,					// property ID
	int& v,							// returned: retrieved value
	int iObjIdx /*=-1*/,			// object index (default = xc_consIdx)
	int vDflt /*=-999*/,			// default value
	BOOL bMsgMissing /*=TRUE*/)		// TRUE: error if value not found
// returns: 1= success (v = DB value)
//          0= failure (v = vDflt, xc_errMsg set iff bMsgMissing)
//         -1= nop due to prior error (v = vDflt)

{	v = vDflt;
	int ret = 1;
	if (!xc_IsOK())
		ret = -1;
	else
	{	if (iObjIdx < 0)
			iObjIdx = xc_consIdx;
		long vL;
		if (BEMPX_GetInteger( propID, vL, vDflt, BEMP_Int, iObjIdx))
			v = vL;			// convert long to int
		else
			v = vDflt;
		if (v == vDflt)
		{	ret = 0;
			if (bMsgMissing)
			{	QString sCompParam;
				BEMPX_DBIDToDBCompParamString( propID, sCompParam );
				xc_Err( "no value found for ID=%d (%s)", propID, sCompParam.toLocal8Bit().constData() );
			}
		}
	}
	return ret;
}		// XCONS::xc_GetDBInt
//------------------------------------------------------------------------------
int XCONS::xc_GetDBMat(			// get material data from DB
	long propID,		// property ID
	XMAT& xm,			// returned: populated from database
						//   cleared if error
	BOOL bMsgMissing /*=TRUE*/)	// TRUE: error if not found
// returns: 1= success (xm = DB values, not checked for completeness
//          0= failure (xm.xm_Init(), xc_errMsg set iff bMsgMissing)
//         -1= nop due to prior error (xm.xm_Init())
{
	int ret = -1;
	if (xc_IsOK())
	{	BEMObject* pMatObj;
		BEMPX_GetObject(  propID, pMatObj, -1, xc_consIdx);
		int iMatObjIdx = pMatObj ? BEMPX_GetObjectIndex( pMatObj->getClass(), pMatObj) : -1;
		ret = iMatObjIdx >= 0;
		if (ret)
			ret = xm.xm_FromDB( iMatObjIdx);
		if (!ret && bMsgMissing)
		{	xc_Err( "no material found for ID=%d", propID);
			xm.xm_Init();
		}
	}
	return ret;
}		// XCONS::xc_GetDBMat
//------------------------------------------------------------------------------
int XCONS::xc_SetDBMat(			// write material data to DB
	long propID,		// property ID
	const XMAT& xm)		// returned: populated from database
						//   cleared if error
// returns: 1= success
//          0= failure
//         -1= nop due to prior error
{
	int ret = -1;
	if (xc_IsOK())
	{	BEMObject* pMatObj;
		BEMPX_GetObject(  propID, pMatObj, -1, xc_consIdx);
		int iMatObjIdx = pMatObj ? BEMPX_GetObjectIndex( pMatObj->getClass(), pMatObj) : -1;
		ret = iMatObjIdx >= 0;
		if (ret)
			ret = xm.xm_ToDB( iMatObjIdx);
	}
	return ret;
}		// XCONS::xc_SetDBMat
#if 0
//----------------------------------------------------------------------------
int XCONS::xc_SetDBFloat(		// get float property value from DB
	long propID,					// property ID
	double v,						// returned: retrieved value
	int iObjIdx /*=-1*/)			// object index (default = xc_consIdx)
{
////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SetBEMData()
//
// Purpose ------------------------------------------------------------------
//   Sets data to the database, primarily user inputs from the interface or
//   values resulting from the evaluation of compliance rules.
//   
// Arguments ----------------------------------------------------------------
//   long              lDBID     : 6 digit database ID CCPPAA (comp/property/array)
//   int               iDataType : type of data being set (BEMP_Int, BEMP_Flt, BEMP_Sym, BEMP_Str or BEMP_Obj)
//   void*             pData     : pointer to value being set
//   BEM_ObjType        eObjFrom  : (default = BEMO_User) type of object identified by the char string pData (only
//                                 in the event that iDataType = BEMP_Str and the value being set is an object)
//   int               iOccur    : (default = -1) occurrence index of object being edited
//   BEM_PropertyStatus eStatus   : (default = BEMS_UserDefined) status flag describing origin of value
//   BEM_ObjType        eObjType  : (default = BEMO_User) type of object being edited
//   
// Return Value -------------------------------------------------------------
//   integer value:  >= 0      : OK
//                  <0 && >-10 : error value returned from BEMPX_GetProperty()
//                         -10 : incompatible input and database datatypes
//                         -11 : could not find parent object to set
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////

	int ret = BEMPX_SetBEMData( propID, BEMP_Flt, &v)
}		// XCONS::xc_
#endif

#if 0
out of service
//----------------------------------------------------------------------------
int XCONS::xc_GetLibMat(		// get material data from library
	const char* libName,	// material name from library
	XMAT& xm,				// returned: populated from library
							//   cleared if error
	BOOL bMsgMissing /*=TRUE*/)	// TRUE: error if not found
// returns: 1= success (xm = DB values, not checked for completeness
//          0= failure (xm.xm_Init(), xc_errMsg set iff bMsgMissing)
//         -1= nop due to prior error (xm.xm_Init())
{
	int ret = -1;
	if (xc_IsOK())
	{	ret = xm.xm_FromLib( libName);
		if (!ret && bMsgMissing)
			xc_errMsg = QString( "Cons '%1': library material '%2' not found" ).arg( xc_consName, libName );
	}
	return ret;
}		// XCONS::xc_GetLibMat
//-----------------------------------------------------------------------------
int XCONS::xc_GetOrGenMat(		// get or generate a material
	int iL,		// layer idx
	int iP,		// path
	long matID,	// material property ID
	long symID)	// user input symbol
{
	XMAT& xm = xc_L[ iL].xl_mat[ iP];
	int ret = xc_GetDBMat( matID+iL, xc_L[ iL].xl_mat[ iP], FALSE);
	if (ret == 1)
		ret = xm.xm_DeriveRes( xc_L[ iL].xl_thkns);
	else
	{	double symVal;
		xc_GetDBFloat( symID+iL, symVal);
		double res = -1.0;
		if (symVal > 99000.0 && symVal < 99300.0)
			res = symVal - 99000.0;
		else if (symVal < 100.0)
			res = symVal;
		if (res >= 0.)
		{	xm.xm_SetRes( res);
			ret = 1;
		}
	}
	return 1;
}		// XCONS::xc_GetOrGenMat
#endif
//-----------------------------------------------------------------------------
int XCONS::xc_GetDBPath(		// get data for layer path
	int iL,		// layer idx
	int iP,		// path
	long matID,	// material property ID
	long symID)	// user input symbol
{
	// symbol (indicates user input source for material, info only)
	xc_GetDBFloat( symID+iL, xc_L[ iL].xl_symVal[ iP]);

	// material
	XMAT& xm = xc_L[ iL].xl_mat[ iP];
	int ret = xc_GetDBMat( matID+iL, xm, FALSE);

	// if thickness missing or 0, set to layer thickness
	//   (if missing, defaults to -1)
	if (xm.xm_Thickness < 0.001)	// xm_Thickness defaults to -1 if missing
		xm.xm_Thickness = xc_L[ iL].xl_thkns;
	ret = xm.xm_SetDerived();

	return ret;
}		// XCONS::xc_GetDBPath
//----------------------------------------------------------------------------
int XCONS::xc_GetDBLayerParams(		// get LayerParams
	int iL)		// layer idx
// returns: 1= success (xc_L[ iL].xx set)
//          0= missing
//         -1= nop due to prior error (xm.xm_Init())

{
	int ret = -1;
	if (xc_IsOK())
	{	BEMObject* pLPObj;
		BEMPX_GetObject( xc_LayerParametersID+iL, pLPObj, -1, xc_consIdx);
		int iLPObjIdx = pLPObj
				? BEMPX_GetObjectIndex( pLPObj->getClass(), pLPObj)
				: -1;
		ret = iLPObjIdx >= 0;
		if (ret)
		{	xc_GetDBInt( xc_LPTypeID, xc_L[ iL].xl_LPType, iLPObjIdx);
			if (xc_L[ iL].xl_LPType != ltyCONTINUOUS)
			{	// remaining properties available only if non-continuous layer
				xc_GetDBFloat( xc_LPFrameSpacingID,     xc_L[ iL].xl_LPFrameSpacing,     iLPObjIdx);
				xc_GetDBFloat( xc_LPFrameWebWidthID,    xc_L[ iL].xl_LPFrameWebWidth,    iLPObjIdx);
				xc_GetDBFloat( xc_LPFrameFlangeWidthID, xc_L[ iL].xl_LPFrameFlangeWidth, iLPObjIdx);
				xc_GetDBFloat( xc_LPFrameWeightID,      xc_L[ iL].xl_LPFrameWeight,      iLPObjIdx);
				xc_GetDBFloat( xc_LPFKnockOutID,        xc_L[ iL].xl_LPFKnockOut,        iLPObjIdx);
			}
		}
	}
	return ret;
}	// XCONS::xc_GetDBLayerParams
//-----------------------------------------------------------------------------
int XCONS::xc_GetDBLayer(		// retrieve from DB all info about a layer
	int iL)		// layer idx
// returns: 1= success (xc_L[ iL].xx set)
//          0= failure (xc_L[ iL] init'd
//         -1= nop due to prior error (xc_L[ iL] init'd)
{
	int ret = -1;
	xc_L[ iL].xl_Init();
	if (xc_IsOK())
	{	// layer thickness is always populated by rules
		xc_GetDBFloat( xc_ThicknessID+iL, xc_L[ iL].xl_thkns);	// layer thickness, in

		xc_GetDBLayerParams( iL);		// retrieve layer params

		int ret0 = -1;
		int ret1 = -1;
		if (xc_NumPaths==1)
		{	// single path: layers are in Cons:CavityPathMats[]
			//   if furred, furring framing materials in Cons:FramePathMats[]
			ret0 = xc_GetDBPath( iL, XCONS_PATHCAV, xc_CavityPathMatsID, xc_CavityLayerSymValID);
			if (xc_IsFurred( iL))
			{	ret1 = xc_GetDBPath( iL, XCONS_PATHFRM1, xc_FramePathMatsID, xc_FrameLayerSymValID);
				xc_L[ iL].xl_MixFurred();	// mix frame into cavity
			}
		}
		else // xc_NumPaths == 2
		{	
			ret0 = xc_GetDBPath( iL, XCONS_PATHFRM1, xc_FramePathMatsID, xc_FrameLayerSymValID);
			ret1 = xc_GetDBPath( iL, XCONS_PATHCAV, xc_CavityPathMatsID, xc_CavityLayerSymValID);

		}
		// TODO xc_NumPaths == 4

		ret0; ret1;
		ret = 1;		// TODO
	}
	return ret;

}	// XCONS::xc_GetDBLayer
//-----------------------------------------------------------------------------
int XCONS::xc_Fill()		// fill XCONS from Cons data
// returns 1 on success (XCONS calcs can proceed, xc_errMsg empty)
//         0 on error (xc_errMsg set)
//        -1 on pre-existing xc_Setup() error (xc_errMsg set)
{
	int ret = xc_Setup();
	if (ret <= 0)
		return ret;		// one or more invalid IDs

	// common info
	xc_GetDBInt( xc_UfactorCalcMethodID, xc_UfactorCalcMethod);
	xc_GetDBInt( xc_CanAssignToID, xc_CanAssignTo);
	xc_GetDBInt( xc_TypeID, xc_Type);

#if 0
x	xc_GetDBInt( xc_NumLayersID, xc_NumLayersSel);	// number of layers selectable on screen
x													//   for this construction type
x													//   not used here?
x	int frameLayerMapIdx[ 2];
x	xc_GetDBInt( xc_FrameLayerMapIdxID+0, frameLayerMapIdx[ 0]);
x	xc_GetDBInt( xc_FrameLayerMapIdxID+1, frameLayerMapIdx[ 1]);
#endif

	xc_GetDBInt( xc_NumPathsID, xc_NumPaths);		// number of heat flow paths

	xc_GetDBFloat( xc_OutsdAirFilmRID, xc_OutsdAirFilmR);
	xc_GetDBFloat( xc_InsdAirFilmRID, xc_InsdAirFilmR);

	xc_GetDBFloat( xc_FramingFactorID, xc_FramingFactor);
	xc_FramingFactorEff = xc_FramingFactor;

	// user-specfied frameW (re testing steel frame constructions)
	//   not present for all Cons types
	//   if missing, treat as 0 and do not look for related vals
	xc_GetDBInt( xc_FrameWCanBeInputID, xc_FrameWCanBeInput, -1, 0, 0);
	if (xc_FrameWCanBeInput)
	{	xc_GetDBInt( xc_SpecifyFrameWID, xc_SpecifyFrameW);
		xc_GetDBFloat( xc_FrameWInputID, xc_FrameWInput);
	}
	else
	{	xc_SpecifyFrameW = 0;
		xc_FrameWInput = 0.0;
	}

	BEMPropertyType* pPropType = xc_GetPropType( xc_FrameLayerSymValID);

	if (xc_IsOK())
	{	int nL = pPropType->getNumValues();		// # of layers supported by Cons
		assert (nL <= XCONS_MAXLAYRS);

		// number of layers expected
		//   xc_NumLayers() returns this value
		xc_GetDBInt( xc_NumLayerMatsID, xc_NumLayerMats);

		xc_GetDBInt( xc_InsideLayerFirstID, xc_InsideLayerFirst);

		// populate xc_L[] from DB
		//   gets all material properties
		//   reduces furred layers to single mixed materials
		//   steel-framed constructions handled below
		for (int iL=0; iL<xc_NumLayers(); iL++)
			xc_GetDBLayer( iL);
	}

	return xc_IsOK();
}		// XCONS::xc_Fill
//-----------------------------------------------------------------------------
double XCONS::xc_GetFFrm(			// framing factor
	int iP) const		// heat flow path
// returned value is base on xc_FramingFactorEff
//   (possibly adjusted, see UModifiedZoneMethod())
{
	double fFrm = -1.0;
	if (xc_NumPaths == 1)
		fFrm = 1.0;
	else if (xc_NumPaths == 2)
		fFrm = iP == XCONS_PATHCAV
				? 1.0 - xc_FramingFactorEff
				: xc_FramingFactorEff;
	return fFrm;

}		// XCONS::xc_GetFFrm
//----------------------------------------------------------------------------
double XCONS::xc_UFactor(
	int iMethod /*=-1*/)	// calculation method TBD
							//   default = xc_UFactorCalcMethod
{
// 0, Cons:UfactorCalcMethod,  0
// 2,              0,    "- not specified -" 
// 2,              1,    "Parallel Path" 
// 2,              2,    "Isothermal Planes" 
// 2,              3,    "Modified Zone" 

	if (iMethod < 0)
		iMethod = xc_UfactorCalcMethod;

	// calc code U factor with iQII = 0 (nominal properties)
	double U = iMethod == 1 ? xc_UParallelPath( 0)
			: iMethod == 2 ? xc_UIsothermalPlanes( 0)
			: iMethod == 3 ? xc_UModifiedZoneMethod( 0, 0)	// do NOT modify frame properties
			:				 -1.0;

	if (iMethod == 3)
		xc_UModifiedZoneMethod( 1, 1);	// do zone method again, iQII=1
										//  modify frame properties for CSE
										//  ignore return

	return U;
}		// XCONS::xc_UFactor
//-----------------------------------------------------------------------------
double XCONS::xc_UParallelPath(	// construction U-factor, parallel path method
	int iQII)	// 0: use rated material properties
				// 1: use rated or adjusted properties per building ICQ setting
// returns U-factor, Btuh/ft2-F
{
	int iP;
	for (iP=0; iP < XCONS_MAXPATHS; iP++)
		xc_RPath[ iP] = 0.0;

	// layer order not significant
	double Upp = 0.0;
	for (iP=0; iP<xc_NumPaths; iP++)
	{	xc_RPath[ iP] = xc_OutsdAirFilmR + xc_InsdAirFilmR;
		for (int iL=0; iL<xc_NumLayers(); iL++)
			xc_RPath[ iP] += xc_L[ iL].xl_mat[ iP].xm_GetResistance( iQII);
		Upp += xc_GetFFrm( iP) / max( xc_RPath[ iP], .0001);
	}
	return Upp;
}		// XCONS::xc_UParallelPath
//-----------------------------------------------------------------------------
double XCONS::xc_UIsothermalPlanes(		// construction U-factor, isothermal planes method
	int iQII)	// 0: use rated material properties
				// 1: use rated or adjusted properties per building ICQ setting
// returns U-factor, Btuh/ft2-F
{
	double R = xc_OutsdAirFilmR + xc_InsdAirFilmR;	// films
	int iP;
	for (iP=0; iP < XCONS_MAXPATHS; iP++)
		xc_RPath[ iP] = iP < xc_NumPaths ? R : 0.0;

	// layer order not significant
	for (int iL=0; iL<xc_NumLayers(); iL++)
	{	double ULayr = 0.0;
		for (iP=0; iP<xc_NumPaths; iP++)
		{	double RLayrPath = xc_L[ iL].xl_mat[ iP].xm_GetResistance( iQII);
			xc_RPath[ iP] += RLayrPath;
			ULayr += xc_GetFFrm( iP) / max( RLayrPath, .0001);
		}
		R += 1.0/max( ULayr, .0001);
	}

	double Uip = 1.0 / R;
	return Uip;
}		// XCONS::xc_UIsothermalPlanes
//-----------------------------------------------------------------------------
double XCONS::xc_UModifiedZoneMethod(
	int iQII,	// 0: use rated material properties
				// 1: use rated or adjusted properties per building ICQ setting
	int options)	// option bits
					//   1: derived mixed frame properties
					//      to be written back to DB for CSE use
{
	BOOL bModifyFrameMaterial = (options & 1) != 0;

	int iP;
	for (iP=0; iP < XCONS_MAXPATHS; iP++)
		xc_RPath[ iP] = 0.0;
	// additional init?

	if (!xc_IsOK())
		return -1.0;

	double RX[ 2];		// R of non-framed layers

	RX[ 0] = xc_OutsdAirFilmR;	// resistance outside of framed layer
	RX[ 1] = xc_InsdAirFilmR;	// resistance inside of framed layer
	double cLat = -1.0;			// lateral conductance of outside layer with
								//   highest lateral conductance
								//   = thkns*k (1x1 ft), Btuh/ft2-F
	int iLFrm = 999;			// idx of framed layer
								//   init big so layers before finding framed are "outside"

	// loop over layers outside to inside
	//  locate framing layer, accum resistances
	//  exits loop on error
	for (int iL=0; xc_IsOK() && iL<xc_NumLayers(); iL++)
	{	int iLX = xc_GetLayerIdx( iL);		// actual layer index (re layer order)
		const XCONSL& LX = xc_L[ iLX];
								// cavity path layer resistance; frame path s/b same
								//   except for framed layer
		if (LX.xl_LPType == ltySTEELFRAMED)
		{	if (iLFrm < 999)
				xc_Err( "2nd steel framed layer found at %d (only 1 allowed)", iL);
			iLFrm = iL;		// framed layer idx
		}
		else if (LX.xl_LPType != ltyCONTINUOUS)
			xc_Err( "Unsupported framing type at %d", iL);
		else
		{	double R = LX.xl_mat[ XCONS_PATHCAV].xm_GetResistance( iQII);
			RX[ iL > iLFrm] += R;
			if (iL < iLFrm)		// if outside framing
			{	// lateral conductivity (in plane of construction)
				double cLatX= LX.xl_mat[ XCONS_PATHCAV].xm_GetLateralConductivity( iQII);
				if (cLatX > cLat)
					cLat = cLatX;
			}
		}
	}

	if (xc_IsOK() && iLFrm == 999)
		xc_ErrV( "No framed layer");

	if (!xc_IsOK())
		return -1.0;	// invalid setup

	XCONSL& LXFrm = xc_L[ xc_GetLayerIdx( iLFrm)];

#if 0
0 incomplete / unnecessary: now handled in rules
0	bool bFrmLimited = LXFrm.xl_LimitSteelFramed();
#endif

	// working copies of geometry (in ASHRAE HOF notation)
	//  units = inches
	double L = LXFrm.xl_LPFrameFlangeWidth;		// flange width
	double dII = LXFrm.xl_LPFrameWebWidth;		// metal thickness
	double dIIko = dII * (1.0 - LXFrm.xl_LPFKnockOut);
	double ds = LXFrm.xl_thkns;
	double dI = ds - 2.0 * dII;

	// resistivities (per inch)
	double rMet = LXFrm.xl_mat[ XCONS_PATHFRM1].xm_GetResistivity( iQII) / 12.0;
	double rIns = LXFrm.xl_mat[ XCONS_PATHCAV].xm_GetResistivity( iQII) / 12.0;
	double RIns = rIns * ds;		// resistance of cavity insulation

	double RImet = rMet * dI;
	double RIins = rIns * dI;
	double RIImet = rMet * dII;
	double RIIins = rIns * dII;

	// effective framing width
	//   user input or derived
	if (xc_IsFrameWInput())
		xc_FrameW = max( L, xc_FrameWInput);
	else if (cLat <= 0.0)
		xc_FrameW = L;		// no outside layers, assume W = L
	else
	{	// calculate xc_FrameW per Wilcox / Niles regression
		//   TODO: knockout?
		double fWeb = dII / L;				// fraction web based on flange width
		double RFrm = 2.0*RIImet + 1.0/(fWeb/RImet + (1.0-fWeb)/RIins);
											// parallel path R of framing based on flange L
		double crl = 1.0/(RX[ 0] + RFrm + RX[ 1]);	// conductance of frame path
#if 1	// add interior insulation to Csh and limit regression inputs, 11-22-2017
		double cCavPath = 1.0/(RX[ 0] + RIns + RX[ 1]);
		// Regression based on wReg4bFix.xlsx (17-Jul-2014)
		//   = wReg4b.xls (Wilcox 7-Apr-2014) with revised coefficients
		// Variable equivalences --
		//  Wilcox Csh = 1/RX[ 0]: conductance of all layers outside frame incl. film
		//	     rsh used here = RX[ 0] + inside sheathing R; added 11/24/2017 to
		//           approximate effect of inside sheathing insulation.
		//           Reasoning; inside and outside sheathing insul should have same effect approx
		//  Wilcox Rcav = RIns: cavity insulation resistance at full framing thickness
		//       Note: aka Rcv0 in Niles memo
		//  crl: defined identically, resistance at framing width L
		static const double rGBandFilm = 1.13453;	// res of inside layers assumed in regression
													//   = 0.5 in gyp board + inside surface res
		double rsh = RX[ 0] + max( 0., RX[ 1] - rGBandFilm);	//	outside res + inside sheating res

		// limit all independent terms to data range used to make regression
		crl = bracket( .05565, crl, .560885);
		cCavPath = bracket( .017921, cCavPath, 0.391389);
		double cLatL = bracket( .001736, cLat, .13889);
		rsh = bracket( 1./2.898551, rsh, 1./.061843);
		double rCav = bracket( 1.08, RIns, 38.5);

		double W = 5.19788279
				- 20.51917447  * crl
				+  6.369940846 * cLatL
				+ 29.350005	   * crl * crl
				+  2.604793103 * cCavPath * cCavPath
				+  2.715554894 / rsh
				-  5.23862597  * crl / rsh
				-  0.021999407 * crl * rCav;
#elif 0	// revised correlation, 7-17-2014
x		double cCavPath = 1.0/(RX[ 0] + RIns + RX[ 1]);
x		// Regression based on wReg4bFix.xlsx (17-Jul-2014)
x		//   = wReg4b.xls (Wilcox 7-Apr-2014) with revised coefficients
x		//     change: cLat*cLat var found to actually be ccavPath*ccavPath
x		// Variable equivalences --
x		//  Wilcox Csh = 1/RX[ 0]: conductance of all layers outside frame incl. film
x		//  Wilcox Rcav = RIns: cavity insulation resistance at full framing thickness
x		//       Note: aka Rcv0 in Niles memo
x		//  crl: defined identically, resistance at framing width L
x		double W = 5.19788279
x				- 20.51917447  * crl
x				+  6.369940846 * cLat
x				+ 29.350005	   * crl * crl
x				+  2.604793103 * cCavPath * cCavPath
x				+  2.715554894 / RX[ 0]
x				-  5.23862597  * crl / RX[ 0]
x				-  0.021999407 * crl * RIns;
#elif 0
x		// Regression based on wReg4.xls from Bruce Wilcox, 4-1-2014
x		// Variable equivalences --
x		//  csh = 1/RX[ 0]: conductance of all layers outside frame incl. film
x		//  Rcav = RIns: cavity resistance and full framing thickness
x		//  crl: defined identically, resistance at framing width L
x		double W = 5.192432567
x				- 20.41983523  * crl
x				+  6.344876394 * cLat
x				+ 29.16166213  * crl * crl
x				+  2.615485263 * cLat * cLat
x				+  2.706106175 / RX[ 0]
x				-  5.216316517 * crl / RX[ 0]
x				-  0.022176466 * crl * RIns;
#endif
		xc_FrameW = max( L, W);
#if 1
		if (xc_FramingFactor > 0.)
			xc_FrameW = min( xc_FrameW, 0.98*L/xc_FramingFactor);
#endif
	}

	double RI = xc_FrameW / (dIIko / RImet + (xc_FrameW - dII)/RIins);

	double RII = xc_FrameW / (L / RIImet + (xc_FrameW - L) / RIIins);

	xc_FramingFactorEff = xc_FramingFactor * xc_FrameW / L;

	xc_RPath[ XCONS_PATHCAV]  = RX[ 0] + RX[ 1] + RIns;
	xc_RPath[ XCONS_PATHFRM1] = RX[ 0] + RX[ 1] + RII + RI + RII;

	double Uzm = 0.0;
	for (iP=0; iP<xc_NumPaths; iP++)
		Uzm += xc_GetFFrm( iP) / max( xc_RPath[ iP], .0001);

	// optionally generate mixed material for frame
	if (bModifyFrameMaterial)
	{	LXFrm.xl_MixSteelFramed( xc_FrameW, RII + RI + RII);
#if defined( _DEBUG)
		// check with parallel path
		//   U-factor and re-derived path resistances s/b same
		double RPathSave[ 2];
		RPathSave[ XCONS_PATHCAV]  = xc_RPath[ XCONS_PATHCAV];
		RPathSave[ XCONS_PATHFRM1] = xc_RPath[ XCONS_PATHFRM1];
		double Upp = xc_UParallelPath( iQII);
		if (fabs( Uzm - Upp) > .0001
		 || fabs( xc_RPath[ XCONS_PATHCAV] - RPathSave[ XCONS_PATHCAV]) > .001
		 || fabs( xc_RPath[ XCONS_PATHFRM1]- RPathSave[ XCONS_PATHFRM1]) > .001)
			assert( 0);
#endif
	}
	return Uzm;
}		// XCONS::xc_UModifiedZoneMethod
//-----------------------------------------------------------------------------
int XCONS::xc_StoreResults()		// store results to database
{
	int ret = 0;
	int iP;

	// write matrials flagged as xmatNEEDWRITE
	for (int iL=0; iL<xc_NumLayers(); iL++)
	{	for (iP=0; iP<xc_NumPaths; iP++)
		{	const XMAT& xm = xc_L[ iL].xl_mat[ iP];
			if (xm.xm_status & XMAT::xmatNEEDWRITE)
			{	long id = iP == XCONS_PATHCAV ? xc_CavityPathMatsID
						:			            xc_FramePathMatsID;
				ret = xc_SetDBMat( id+iL, xm);
			}
		}
	}

	if (xc_FramingFactorEff != xc_FramingFactor)
		BEMPX_SetBEMData( xc_FramingFactorID,
			BEMP_Flt, &xc_FramingFactorEff, BEMO_User, xc_consIdx, BEMS_RuleDefined);

	for (iP=0; iP<XCONS_MAXPATHS; iP++)
	{	BEMPX_SetBEMData( xc_PathCodeRValueID+iP,
			BEMP_Flt, (void *)(xc_RPath+iP), BEMO_User, xc_consIdx, BEMS_RuleDefined);
	}

	return ret;
}		// XCONS::xc_StoreResults
//-----------------------------------------------------------------------------
double ConsUFactorRes(			// CBECC-Res U-factor calculation
	int iMethod,			// calculation method, TBD
	int consIdx,			// object index of Cons being calculated
	BEM_ObjType /*eConsObjType*/,
	const QString& sConsName,		// name of Cons
	ExpEvalStruct* /*pEval*/,
	ExpError* error )
// returns ...

{
	iMethod;

	double dUFactor = -1;
	int iError;
	QString sUFactorErr, sMatName;

	XCONS xCons( sConsName, consIdx);

	if (xCons.xc_Fill() <= 0)
		sUFactorErr = xCons.xc_GetErrMsg();
	else
		dUFactor = xCons.xc_UFactor();

	if (!sUFactorErr.isEmpty())
	{	ExpSetErr( error, EXP_RuleProc, sUFactorErr );
		assert( dUFactor < 0 );  // make sure...
		dUFactor = -1.;
	}

	if (dUFactor > 0.)
		xCons.xc_StoreResults();

	return dUFactor;
}	// ::ConsUFactorRes

//=============================================================================


static char szSimDef[] = "- sim default -";
static char szNone[]   = "- none -";
static const char* pszSpecial[] = { szSimDef, szNone };

// SAC 11/13/14 - routine to facilitate retrieval of objects w/ specified properties set - and if not found then create it
// Arguments:
// 	int iObjClassIdx			- 1-based BEMBase class index
// 	std::string& sObjName	- gets populated w/ name of object found or created
// 	int iObjCreateOption		- 0-don't create if no match found / 1-create using match data as basis of name / 2-always create new object
// 	each vector synced to identify and specify the data to be matched:
// 		vector<long>& laDBIDs			- DBIDs of properties
// 		vector<int>& iaDataTypes		- 0-string, 1-long, 3-float  (BEMP_Int / BEMP_Flt / BEMP_Str)
//			vector<std::string>& saData	- string data to be matched (blank if iaDataType != BEMP_Str)
//			vector<double>& faData			- float data to be matched (blank if iaDataType != BEMP_Flt)
//			vector<long>& laData				- integer data to be matched (blank if iaDataType != BEMP_Int)
//		int iBEMProcIdx
//	Return values:		0  - OK, existing object name returned
//							1  - OK, no exiting match found, so new object created and set w/ match data
//							2	- No object found and no object created (due to iObjCreateOption argument)
//							11	- error - invalid DBID - unable to retrieve BEMPropertyType*
//							12	- error - invalid combination of input and data model property/data types (float / integer / string)
//							13	- error - unable to retrieve name of existing object that matches specified data
//							14	- error - no matching object found and unable to create non-User object to match specified data
//							15	- error - no matching object found and unable to create another user object of this type (max occurrences already met)
//							16	- error encountered creating new object to match specified data
//							17	- error - unable to set match data to new object
//							18	- error - unable to retrieve name of newly created object
int GetObjectMatchingData( int iObjClassIdx, std::string& sObjName, int iObjCreateOption, vector<long>& laDBIDs, vector<int>& iaDataTypes,
									vector<std::string>& saData, vector<double>& faData, vector<long>& laData, int iBEMProcIdx /*=-1*/,
									BEMObject* pParentObject /*=NULL*/, BEM_ObjType eObjType /*=BEMO_User*/ )
{	int iRetVal = -1;
	//sObjName = "";		SAC 12/14/15 - enable name prefix to be passed into routine
	int i, j, iError, iDataType, iSpecialVal, iStatus, iNumObjs = BEMPX_GetNumObjects( iObjClassIdx, eObjType, iBEMProcIdx );
	if (iObjCreateOption != 2)
	{	for (i=0; (i < iNumObjs && iRetVal < 0); i++)
		{	bool bObjMatch = true;
			for (j=0; (j < (int) laDBIDs.size() && bObjMatch && iRetVal < 0); j++)
			{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( laDBIDs[j], iError, iBEMProcIdx );
				if (pPropType == NULL)
					iRetVal = 11;
				else
				{	if (iaDataTypes[j] == BEMP_Flt && IsReserved_UNDEFINED( faData[j] ))
					{
						int iStatus = BEMPX_GetDataStatus( laDBIDs[j], i, eObjType, iBEMProcIdx );
						bObjMatch = (iStatus == 0);
					}
					else if (iaDataTypes[j] == BEMP_Flt && (IsReserved_DEFAULT( faData[j] ) || IsReserved_NONE( faData[j] )))
					{
				//		BEMPX_GetData( laDBIDs[j], iDataType, iSpecialVal, iError, i, eObjType, FALSE /*bReturnParentObject*/, iBEMProcIdx );
						BEMPX_GetFloat( laDBIDs[j], iSpecialVal, iError, i, eObjType, iBEMProcIdx );
						bObjMatch = (	(IsReserved_DEFAULT( faData[j] ) && iSpecialVal == SV_Default) ||
											(IsReserved_NONE(    faData[j] ) && iSpecialVal == SV_None   ) );
					}
					else if (pPropType->getPropType() == BEMP_Flt)
					{	double fData, fCompare = -99999;
						if (iaDataTypes[j] == BEMP_Flt)
							fCompare = faData[j];
						else if (iaDataTypes[j] == BEMP_Int)
							fCompare = (double) laData[j];
						else if (iaDataTypes[j] == BEMP_Str)
							fCompare = BEMPX_StringToFloat( saData[j].c_str() );
						
				//		if (!BEMPX_SetDataFloat( laDBIDs[j], fData, -99996, -1, i, (int) eObjType, iBEMProcIdx ))
						fData = BEMPX_GetFloatAndStatus( laDBIDs[j], iStatus, iSpecialVal, iError, i, eObjType, iBEMProcIdx, true, -99996 );
						if (iStatus < 1)
							bObjMatch = false;
						else if (fData != fCompare)
							bObjMatch = false;
					}
					else if (pPropType->getPropType() == BEMP_Int || (pPropType->getPropType() == BEMP_Sym && iaDataTypes[j] == BEMP_Int))	// SAC 5/23/16 - added Sym/Int scenario
					{	long lData, lCompare = -999;
						if (iaDataTypes[j] == BEMP_Int)
							lCompare = laData[j];
						else if (iaDataTypes[j] == BEMP_Flt)
							lCompare = (long) faData[j];
						else if (iaDataTypes[j] == BEMP_Str)
							lCompare = BEMPX_StringToLong( saData[j].c_str() );
						
						if (!BEMPX_GetInteger( laDBIDs[j], lData, -996, -1, i, (int) eObjType, iBEMProcIdx ))
							bObjMatch = false;
						else if (lData != lCompare)
							bObjMatch = false;
					}
					else if (iaDataTypes[j] == BEMP_Str)
					{	QString sData, sCompare = saData[j].c_str();
						if (!BEMPX_GetString( laDBIDs[j], sData, TRUE /*bAddCommas*/, (iaDataTypes[j] == BEMP_Int ? 0 : 11) /*iPrecision*/,
															-1, i, (int) eObjType, NULL, 0 /*lDBID2*/, iBEMProcIdx ))
							bObjMatch = false;
						else if (sData.compare( sCompare ))
							bObjMatch = false;
					}
					else
					{	bObjMatch = false;			assert( FALSE );
						iRetVal = 12;
			}	}	}

			if (bObjMatch)
			{	QString sExObjName;
				if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iObjClassIdx ), sExObjName, FALSE /*bAddCommas*/, 0 /*iPrecision*/,
													-1, i, (int) eObjType, NULL, 0 /*lDBID2*/, iBEMProcIdx ))
					iRetVal = 13;
				else
				{	sObjName = sExObjName.toLocal8Bit().constData();
					iRetVal = 0;
			}	}
	}	}	// end of loop over existing objects

	if (iRetVal < 0)
	{	// no existing object w/ matching data, so either set return value or create new object w/ these data specified
		if (iObjCreateOption == 0)
			iRetVal = 2;	// no match found, and don't create new object
		else if (eObjType != BEMO_User)
			iRetVal = 14;	// no match found, and can't create non-user objects
		else if (!BEMPX_CanCreateAnotherUserObject( iObjClassIdx, 1, iBEMProcIdx ))
			iRetVal = 15;	// unable to create another user object of this type (max occurrences already met)
		else
		{	// Create new object
			QString sNewObjName = sObjName.c_str(), sTemp;
			for (j=0; (j < (int) laDBIDs.size()); j++)
			{	if (j > 0)
					sNewObjName += ':';
				if (iaDataTypes[j] == BEMP_Flt && IsReserved_UNDEFINED( faData[j] ))
					sTemp.clear();		// sTemp = "undef";
				else if (iaDataTypes[j] == BEMP_Flt && IsReserved_DEFAULT( faData[j] ))
					sTemp = "default";
				else if (iaDataTypes[j] == BEMP_Flt && IsReserved_NONE( faData[j] ))
					sTemp = "none";
				else if (iaDataTypes[j] == BEMP_Flt)
					sTemp = BEMPX_FloatToString( faData[j], 11 /*nRtOfDec*/, TRUE /*bAddCommas*/ );  // int iZeroFillLeftToLength=0, BOOL bTrimTrailingDecZeroes=FALSE );
				else if (iaDataTypes[j] == BEMP_Int)
					sTemp = BEMPX_FloatToString( (double) laData[j], 0 /*nRtOfDec*/, TRUE /*bAddCommas*/ );  // int iZeroFillLeftToLength=0, BOOL bTrimTrailingDecZeroes=FALSE );
				else
					sTemp = saData[j].c_str();
				if (!sTemp.isEmpty())
					sNewObjName += sTemp;
			}

			//LPCSTR lpszName = ;
			BEMObject* pNewObj = BEMPX_CreateObject( iObjClassIdx, (sNewObjName.isEmpty() ? NULL : ((const char*) sNewObjName.toLocal8Bit().constData())), pParentObject, BEMO_User, TRUE /*bDefaultParent*/, TRUE /*bAutoCreate*/, iBEMProcIdx );
			int iNewObjIdx = (pNewObj && pNewObj->getClass()) ? BEMPX_GetObjectIndex( pNewObj->getClass(), pNewObj, iBEMProcIdx ) : -1;
			if (pNewObj == NULL || iNewObjIdx < 0)
				iRetVal = 16;	// unable to create another user object of this type (max occurrences already met)
			else
			{	// SET data to new object
				bool bDataSetsOK = true;
				for (j=0; (j < (int) laDBIDs.size() && bDataSetsOK); j++)
				{	int iSetRet = 0;
					if (iaDataTypes[j] == BEMP_Flt && IsReserved_UNDEFINED( faData[j] ))
					{	// do nothing - no data to set
					}
					else if (iaDataTypes[j] == BEMP_Flt && (IsReserved_DEFAULT( faData[j] ) || IsReserved_NONE( faData[j] )))
					{	int iSpecialVal = (IsReserved_DEFAULT( faData[j] ) ? SV_Default : SV_None );
						iSetRet = BEMPX_SetBEMSpecialValue( laDBIDs[j], iSpecialVal, iNewObjIdx, BEMS_UserDefined, BEMO_User, iBEMProcIdx );			assert( iSetRet >= 0 );
					}
					else if (iaDataTypes[j] == BEMP_Flt)
					{	double fData = faData[j];
						iSetRet = BEMPX_SetBEMData( laDBIDs[j], BEMP_Flt, &fData, BEMO_User, iNewObjIdx, BEMS_UserDefined,
																BEMO_User, TRUE /*bPerformResets*/, iBEMProcIdx );								assert( iSetRet >= 0 );
					}
					else if (iaDataTypes[j] == BEMP_Int)
					{	long lData = laData[j];
						iSetRet = BEMPX_SetBEMData( laDBIDs[j], BEMP_Int, &lData, BEMO_User, iNewObjIdx, BEMS_UserDefined,
																BEMO_User, TRUE /*bPerformResets*/, iBEMProcIdx );								assert( iSetRet >= 0 );
					}
					else if (iaDataTypes[j] == BEMP_Str)
					{	QString sData = saData[j].c_str();
						iSetRet = BEMPX_SetBEMData( laDBIDs[j], BEMP_QStr, (void*) &sData,  // BEMP_Str, (void*) sData.toLocal8Bit().constData(), 
																BEMO_User, iNewObjIdx, BEMS_UserDefined,
																BEMO_User, TRUE /*bPerformResets*/, iBEMProcIdx );								assert( iSetRet >= 0 );
					}
					else
						iSetRet = -1;
					bDataSetsOK = (iSetRet >= 0);
				}

				if (!bDataSetsOK)
					iRetVal = 17;	// unable to set match data to new object
				else
				{	QString sNewObjName;
					if (!BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iObjClassIdx ), sNewObjName, FALSE /*bAddCommas*/, 0 /*iPrecision*/,
														-1, iNewObjIdx, (int) eObjType, NULL, 0 /*lDBID2*/, iBEMProcIdx ))
						iRetVal = 18;
					else
					{	iRetVal = 1;
						sObjName = sNewObjName.toLocal8Bit().constData();
				}	}
			}
	}	}

	return iRetVal;
}


// SAC 3/10/14 - routine to create objects in order to facilitate SCSysRpt report population
int CreateSCSysRptObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error )
{	int iNumObjsCreated = 0;
	long lIsMultiFamily, lProj_RunScope;
	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:IsMultiFamily" ), lIsMultiFamily ))
		sErrMsg = QString( "CreateSCSysRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:IsMultiFamily" );
	else if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:RunScope" ), lProj_RunScope ))
		sErrMsg = QString( "CreateSCSysRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:RunScope" );
	else
	{
		int iNumErrors = 0, iError;		QString sTmp, sSCSysRptName;
		int iCID_HVACSys       = GetObjectID_LogError( "HVACSys",       iNumErrors, sTmp );
		int iCID_HVACDist      = GetObjectID_LogError( "HVACDist",      iNumErrors, sTmp );
		int iCID_SCSysRpt      = GetObjectID_LogError( "SCSysRpt"  ,    iNumErrors, sTmp );
		int iCID_DwellUnit     = GetObjectID_LogError( "DwellUnit",     iNumErrors, sTmp );
		int iCID_DwellUnitType = GetObjectID_LogError( "DwellUnitType", iNumErrors, sTmp );
		int iCID_Zone          = GetObjectID_LogError( "Zone",          iNumErrors, sTmp );

		long lDBID_Zone_HVACSysStatus           = GetPropertyDBID_LogError( "Zone", "HVACSysStatus",     iCID_Zone, iNumErrors, sTmp );	// SAC 12/23/15

		long lDBID_HVACSys_Name                 = GetPropertyDBID_LogError( "HVACSys", "Name",                 iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_MaxNumHVACEquipTypes = GetPropertyDBID_LogError( "HVACSys", "MaxNumHVACEquipTypes", iCID_HVACSys, iNumErrors, sTmp );
      long lDBID_HVACSys_Type                 = GetPropertyDBID_LogError( "HVACSys", "Type",                 iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Sym,  1,  0,  0, "",     0,                        8001, "HVAC system type"    
      long lDBID_HVACSys_TypeOK               = GetPropertyDBID_LogError( "HVACSys", "TypeOK",               iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        8001, "Whether or not the selected HVAC system type is valid/allowed/enabled"
      long lDBID_HVACSys_IsNew   		       = GetPropertyDBID_LogError( "HVACSys", "IsNew",                iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is New"
      long lDBID_HVACSys_IsAltered   	       = GetPropertyDBID_LogError( "HVACSys", "IsAltered",            iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is Altered"
      long lDBID_HVACSys_IsExisting   	       = GetPropertyDBID_LogError( "HVACSys", "IsExisting",           iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is Existing"
      long lDBID_HVACSys_IsVerified   	       = GetPropertyDBID_LogError( "HVACSys", "IsVerified",           iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "existing conditions will be HERS verified"
      long lDBID_HVACSys_FloorAreaServed      = GetPropertyDBID_LogError( "HVACSys", "FloorAreaServed",      iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Flt, 10,  1,  0, "ft2",  0,                        8008, "Floor area served by this system"    
      long lDBID_HVACSys_NumHeatSystemTypes   = GetPropertyDBID_LogError( "HVACSys", "NumHeatSystemTypes",   iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        8004, "Number of heating equipment unit types"    
      long lDBID_HVACSys_HeatSystemCount      = GetPropertyDBID_LogError( "HVACSys", "HeatSystemCount",      iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int, 10,  1,  0, "",     0,                        8004, "Number of units for this heating equipment type"    
      long lDBID_HVACSys_HeatSystem           = GetPropertyDBID_LogError( "HVACSys", "HeatSystem",           iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Obj, 10,  1,  0, "",     1, "HVACHeat",    1, "",  8004, "Heating component"    
      long lDBID_HVACSys_NumCoolSystemTypes   = GetPropertyDBID_LogError( "HVACSys", "NumCoolSystemTypes",   iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        8004, "Number of cooling equipment unit types"    
      long lDBID_HVACSys_CoolSystemCount      = GetPropertyDBID_LogError( "HVACSys", "CoolSystemCount",      iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int, 10,  1,  0, "",     0,                        8004, "Number of units for this cooling equipment type"    
      long lDBID_HVACSys_CoolSystem           = GetPropertyDBID_LogError( "HVACSys", "CoolSystem",           iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Obj, 10,  1,  0, "",     1, "HVACCool",    1, "",  8006, "Cooling component"    
      long lDBID_HVACSys_NumHtPumpSystemTypes = GetPropertyDBID_LogError( "HVACSys", "NumHtPumpSystemTypes", iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        8004, "Number of heat pump equipment unit types"    
      long lDBID_HVACSys_HtPumpSystemCount    = GetPropertyDBID_LogError( "HVACSys", "HtPumpSystemCount",    iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int, 10,  1,  0, "",     0,                        8004, "Number of units for this heat pump equipment type"    
      long lDBID_HVACSys_HtPumpSystem         = GetPropertyDBID_LogError( "HVACSys", "HtPumpSystem",         iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Obj, 10,  1,  0, "",     1, "HVACHtPump",  1, "",  8004, "Heat pump component"    
      long lDBID_HVACSys_DistribSystem        = GetPropertyDBID_LogError( "HVACSys", "DistribSystem",        iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",     1, "HVACDist",    0, "",  8008, "new Distribution system"    
      long lDBID_HVACSys_Fan                  = GetPropertyDBID_LogError( "HVACSys", "Fan",                  iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",     1, "HVACFan",     0, "",  8010, "new Fan type/system"    
      long lDBID_HVACSys_HtOrClDucted         = GetPropertyDBID_LogError( "HVACSys", "HtOrClDucted",         iCID_HVACSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        8008, "Whether or not this system is ducted - 1-Heat / 2-Cool / 3-Ht&Cl"    
		long lDBID_HVACSys_EqpCountsMustAlign   = GetPropertyDBID_LogError( "HVACSys", "EqpCountsMustAlign",   iCID_HVACSys, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        3208, "Whether or not (1/0) htg/clg equipment types and counts must align (when ducted)"    
		long lDBID_HVACSys_SCSysRptRef          = GetPropertyDBID_LogError( "HVACSys", "SCSysRptRef",          iCID_HVACSys, iNumErrors, sTmp );  // BEMP_Obj, 20,  0,  0, "",    0,  1, "SCSysRpt",    0, "",  8010, "SCSysRpt objects referencing the cool/heat/distrib/fan equipment assigned to thie DwellUnitType"    
		long lDBID_HVACSys_SCSysRptCount        = GetPropertyDBID_LogError( "HVACSys", "SCSysRptCount",        iCID_HVACSys, iNumErrors, sTmp );  // BEMP_Int, 20,  0,  0, "",    0,  0,                        8010, "SCSysRpt object count related to the cool/heat/distrib/fan equipment assigned to thie DwellUnitType"    

//		long lDBID_HVACDist_Type                = GetPropertyDBID_LogError( "HVACDist", "Type",                iCID_HVACDist, iNumErrors, sTmp );  // BEMP_Sym,  1,  0,  0, "",     0,  0,                    8002, "Distribution system type"    
		long lDBID_HVACDist_Status              = GetPropertyDBID_LogError( "HVACDist", "Status",              iCID_HVACDist, iNumErrors, sTmp );  // BEMP_Sym,  1,  
		long lDBID_HVACDist_DuctsMayReqReport   = GetPropertyDBID_LogError( "HVACDist", "DuctsMayReqReport",   iCID_HVACDist, iNumErrors, sTmp );  // BEMP_Int,  1,  
		long lDBID_HVACDist_IsLessThanFortyFt   = GetPropertyDBID_LogError( "HVACDist", "IsLessThanFortyFt",   iCID_HVACDist, iNumErrors, sTmp );  // BEMP_Int,  1,  

//		long lDBID_SCSysRpt_Parent               = GetPropertyDBID_LogError( "SCSysRpt", "Parent",               iCID_SCSysRpt, iNumErrors, sTmp );
//      long lDBID_SCSysRpt_HVACSysRef           = GetPropertyDBID_LogError( "SCSysRpt", "HVACSysRef",           iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACSys",    0, "",   8004, "HVAC system object being reported"  - SAC 10/14/14   
      long lDBID_SCSysRpt_HeatSystem           = GetPropertyDBID_LogError( "SCSysRpt", "HeatSystem",           iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACHeat",    1, "",  8004, "Heating component"    
//      long lDBID_SCSysRpt_HeatSysUnitTypeIdx   = GetPropertyDBID_LogError( "SCSysRpt", "HeatSysUnitTypeIdx",   iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of this heating unit type in parent HVACSys object" 
//      long lDBID_SCSysRpt_HeatSysUnitTypeCnt   = GetPropertyDBID_LogError( "SCSysRpt", "HeatSysUnitTypeCnt",   iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of the heating unit count associated w/ this SCSysRpt object" 
      long lDBID_SCSysRpt_CoolSystem           = GetPropertyDBID_LogError( "SCSysRpt", "CoolSystem",           iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACCool",    1, "",  8006, "Cooling component"    
//      long lDBID_SCSysRpt_CoolSysUnitTypeIdx   = GetPropertyDBID_LogError( "SCSysRpt", "CoolSysUnitTypeIdx",   iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of this cooling unit type in parent HVACSys object" 
//      long lDBID_SCSysRpt_CoolSysUnitTypeCnt   = GetPropertyDBID_LogError( "SCSysRpt", "CoolSysUnitTypeCnt",   iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of the cooling unit count associated w/ this SCSysRpt object" 
      long lDBID_SCSysRpt_HtPumpSystem         = GetPropertyDBID_LogError( "SCSysRpt", "HtPumpSystem",         iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACHtPump",  1, "",  8004, "Heat pump component"    
//      long lDBID_SCSysRpt_HtPumpSysUnitTypeIdx = GetPropertyDBID_LogError( "SCSysRpt", "HtPumpSysUnitTypeIdx", iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of this heat pump unit type in parent HVACSys object" 
//      long lDBID_SCSysRpt_HtPumpSysUnitTypeCnt = GetPropertyDBID_LogError( "SCSysRpt", "HtPumpSysUnitTypeCnt", iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "1-based index of the heat pump unit count associated w/ this SCSysRpt object" 
      long lDBID_SCSysRpt_HVACFanRef           = GetPropertyDBID_LogError( "SCSysRpt", "HVACFanRef",           iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACFan",     0, "",  8010, "Heat/Cool fan associated w/ this SCSysRpt object"    
      long lDBID_SCSysRpt_HVACDistRef          = GetPropertyDBID_LogError( "SCSysRpt", "HVACDistRef",          iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACDist",    0, "",  8010, "Heat/Cool distribution (ducts) associated w/ this SCSysRpt object"    
      long lDBID_SCSysRpt_SCSysTypeVal         = GetPropertyDBID_LogError( "SCSysRpt", "SCSysTypeVal",         iCID_SCSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,                        1003, "Type of parent HVACSys"   
      long lDBID_SCSysRpt_Status               = GetPropertyDBID_LogError( "SCSysRpt", "Status",               iCID_SCSysRpt, iNumErrors, sTmp );  // SAC 12/14/15 - 
      long lDBID_SCSysRpt_DUEquipCnt           = GetPropertyDBID_LogError( "SCSysRpt", "DUEquipCnt",           iCID_SCSysRpt, iNumErrors, sTmp );  // SAC 6/24/16 - 

		long lDBID_DU_Name             = GetPropertyDBID_LogError( "DwellUnit", "Name",             iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DU_DwellUnitTypeRef = GetPropertyDBID_LogError( "DwellUnit", "DwellUnitTypeRef", iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DU_Count            = GetPropertyDBID_LogError( "DwellUnit", "Count",            iCID_DwellUnit, iNumErrors, sTmp );

		long lDBID_DUT_Name                = GetPropertyDBID_LogError( "DwellUnitType", "Name",                iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DUT_HVACSysType         = GetPropertyDBID_LogError( "DwellUnitType", "HVACSysType",         iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Sym,  1,  1,  0, "",    0,  0,                        8005, "" 
		long lDBID_DUT_NumHeatEquipTypes   = GetPropertyDBID_LogError( "DwellUnitType", "NumHeatEquipTypes",   iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "Number of heating unit types"    
		long lDBID_DUT_HVACHeatRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACHeatRef",         iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj,  5,  1,  0, "",    0,  1, "HVACHeat",    0, "",  8004, "Heating component that serves this equip zone type"    
		long lDBID_DUT_HeatEquipCount      = GetPropertyDBID_LogError( "DwellUnitType", "HeatEquipCount",      iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  5,  1,  0, "",    0,  0,                        8004, "Number of units for this heating equipment type"    
		long lDBID_DUT_NumCoolEquipTypes   = GetPropertyDBID_LogError( "DwellUnitType", "NumCoolEquipTypes",   iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "Number of cooling equipment unit types"    
		long lDBID_DUT_HVACCoolRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACCoolRef",         iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj,  5,  1,  0, "",    0,  1, "HVACCool",    0, "",  8006, "Cooling component that serves this equip zone type"    
		long lDBID_DUT_CoolEquipCount      = GetPropertyDBID_LogError( "DwellUnitType", "CoolEquipCount",      iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  5,  1,  0, "",    0,  0,                        8004, "Number of units for this cooling equipment type"    
		long lDBID_DUT_NumHtPumpEquipTypes = GetPropertyDBID_LogError( "DwellUnitType", "NumHtPumpEquipTypes", iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        8004, "Number of heat pump unit types"    
		long lDBID_DUT_HVACHtPumpRef       = GetPropertyDBID_LogError( "DwellUnitType", "HVACHtPumpRef",       iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj,  5,  1,  0, "",    0,  1, "HVACHtPump",  0, "",  8004, "Heat pump component that serves this equip zone type"    
		long lDBID_DUT_HtPumpEquipCount    = GetPropertyDBID_LogError( "DwellUnitType", "HtPumpEquipCount",    iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  5,  1,  0, "",    0,  0,                        8004, "Number of units for this heat pump type"    
		long lDBID_DUT_HVACFanRef          = GetPropertyDBID_LogError( "DwellUnitType", "HVACFanRef",          iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACFan",     0, "",  8010, "Heat/Cool fan that serves this equip zone type"    
		long lDBID_DUT_HVACDistRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACDistRef",         iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj,  1,  0,  0, "",    0,  1, "HVACDist",    0, "",  8010, "Heat/Cool distribution (ducts) that serves this equip zone type"    
		long lDBID_DUT_HeatEquipDucted     = GetPropertyDBID_LogError( "DwellUnitType", "HeatEquipDucted",     iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        3208, "Whether or not (1/0) heating equipment is ducted"    
		long lDBID_DUT_CoolEquipDucted     = GetPropertyDBID_LogError( "DwellUnitType", "CoolEquipDucted",     iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        3208, "Whether or not (1/0) cooling equipment is ducted"    
		long lDBID_DUT_HtPumpEquipDucted   = GetPropertyDBID_LogError( "DwellUnitType", "HtPumpEquipDucted",   iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        3208, "Whether or not (1/0) heat pump equipment is ducted"    
		long lDBID_DUT_EqpCountsMustAlign  = GetPropertyDBID_LogError( "DwellUnitType", "EqpCountsMustAlign",  iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int,  1,  0,  0, "",    0,  0,                        3208, "Whether or not (1/0) htg/clg equipment types and counts must align (when ducted)"    
		long lDBID_DUT_SCSysRptRef         = GetPropertyDBID_LogError( "DwellUnitType", "SCSysRptRef",         iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Obj, 10,  0,  0, "",    0,  1, "SCSysRpt",    0, "",  8010, "SCSysRpt objects referencing the cool/heat/distrib/fan equipment assigned to thie DwellUnitType"    
		long lDBID_DUT_SCSysRptCount       = GetPropertyDBID_LogError( "DwellUnitType", "SCSysRptCount",       iCID_DwellUnitType, iNumErrors, sTmp );   // BEMP_Int, 10,  0,  0, "",    0,  0,                        8010, "SCSysRpt object count related to the cool/heat/distrib/fan equipment assigned to thie DwellUnitType"    

		BEMObject *pSysObj, *pSCSysRptObj;

		if (iNumErrors > 0)
		{	if (iNumErrors > 1)
				sErrMsg = QString( "Error initializing CreateSCSysRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( (iNumErrors-1) ) );
			else
				sErrMsg = QString( "Error initializing CreateSCSysRptObjects database ID %1" ).arg( sTmp );
		}
		else if (lIsMultiFamily > 0)
	// SAC 7/1/14 - added separate path for creating MFam SCSysRpt objects
		{	QString sZnName, sDUName, sDUTName;
			BEMObject *pDUObj, *pDUTObj;
			int iNumZones      = BEMPX_GetNumObjects( iCID_Zone      );
			for (int iZnIdx=0; (sErrMsg.isEmpty() && iZnIdx < iNumZones); iZnIdx++)
			{	//VERIFY( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_Zone ), sZnName, FALSE, 0, -1, iZnIdx ) && !sZnName.isEmpty() );
				int iNumDUChildren = (int) BEMPX_GetNumChildren( iCID_Zone, iZnIdx, BEMO_User, iCID_DwellUnit /*, iBEMProcIdx=-1*/ );
				if (iNumDUChildren < 1)
					sErrMsg = QString( "CreateSCSysRptObjects Error:  No DwellUnit children found for Zone '%1'" ).arg( sZnName );
				else
				{	long lDUCount, lZoneHVACStatus;
					BEMPX_GetInteger( lDBID_Zone_HVACSysStatus, lZoneHVACStatus, 0, -1, iZnIdx );		assert( lZoneHVACStatus > 0 );	// SAC 12/23/15
					for (int i1DUChld=1; (sErrMsg.isEmpty() && i1DUChld <= iNumDUChildren); i1DUChld++)
					{	BEM_ObjType otDU;
						int iDUIdx = BEMPX_GetChildObjectIndex( iCID_Zone, iCID_DwellUnit, iError, otDU, i1DUChld, iZnIdx /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );
						if (iDUIdx < 0)
							sErrMsg = QString( "CreateSCSysRptObjects Error encountered retrieving object index of DwellUnit child #%1 of Zone '%2'" ).arg( QString::number( i1DUChld ), sZnName );
						else
						{	BEMPX_GetString( lDBID_DU_Name, sDUName, FALSE, 0, -1, iDUIdx );		assert( !sDUName.isEmpty() );
							pDUObj = BEMPX_GetObjectByClass( iCID_DwellUnit, iError, iDUIdx );
							if (pDUObj == NULL)
								sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to retrieve pointer to DwellUnit object #%1 '%2'" ).arg( QString::number( iDUIdx+1 ), sDUName );
							else if (!BEMPX_GetObject( lDBID_DU_DwellUnitTypeRef, pDUTObj, -1, iDUIdx /*, int iObjType=BEMO_User, int iBEMProcIdx=-1*/ ) || pDUTObj==NULL || pDUTObj->getClass()==NULL)
								sErrMsg = QString( "CreateSCSysRptObjects Error encountered retrieving DwellUnitTypeRef of DwellUnit '%1'" ).arg( sDUName );
							else if (!BEMPX_GetInteger( lDBID_DU_Count, lDUCount, 0, -1, iDUIdx ) || lDUCount < 1)
							{	// IGNORE invalid DwellUnit:Count ???
							}
							else
							{	int iDUTIdx = BEMPX_GetObjectIndex( pDUTObj->getClass(), pDUTObj /*, int iBEMProcIdx=-1*/ );			assert( iDUTIdx >= 0 );
								if (iDUTIdx < 0)
									sErrMsg = QString( "CreateSCSysRptObjects Error encountered retrieving object index of DwellUnitTypeRef referenced by DwellUnit '%1'" ).arg( sDUName );
								else
								{	BEMPX_GetString( lDBID_DUT_Name, sDUTName, FALSE, 0, -1, iDUTIdx );		assert( !sDUTName.isEmpty() );
									long lType;
									if (BEMPX_GetInteger( lDBID_DUT_HVACSysType, lType, 0, -1, iDUTIdx ))
									{
										bool bIsHP = (lType == 2);		int iEqp, iCnt, iM1Idx;
										long lHtDucted=0, lClDucted=0, lEqpCountsMustAlign=0, lDuctStatus=0, lSCSysStatus;
										QString sDistribName, sFanName;
										BEMPX_GetString( lDBID_DUT_HVACDistRef, sDistribName, FALSE, 0, -1, iDUTIdx );
										BEMPX_GetString( lDBID_DUT_HVACFanRef , sFanName    , FALSE, 0, -1, iDUTIdx );
										if (!sDistribName.isEmpty())
										{	BEMPX_GetInteger( (bIsHP ? lDBID_DUT_HtPumpEquipDucted : lDBID_DUT_HeatEquipDucted), lHtDucted, 0, -1, iDUTIdx );
											if (bIsHP)
												lClDucted = lHtDucted;
											else
												BEMPX_GetInteger( lDBID_DUT_CoolEquipDucted, lClDucted, 0, -1, iDUTIdx );
										//	BEMObject* pDistribObj = BEMPX_GetObjectByName( iCID_HVACDist, iError, sDistribName, BEMO_User, iBEMProcIdx );
										//	if (pDistribObj && pDistribObj->getClass())
										//	{	int iDistribObjIdx = BEMPX_GetObjectIndex( pDistribObj->getClass(), pDistribObj, iBEMProcIdx );
										//		if (iDistribObjIdx >= 0)
										//			BEMPX_GetInteger( lDBID_HVACDist_Type, lDistribType, 0, -1, iDistribObjIdx );
										//	}
											if (lClDucted > 0 || lHtDucted > 0)
											{	BEMObject* pDistObj = NULL;
												if (BEMPX_GetObject( lDBID_DUT_HVACDistRef, pDistObj, -1, iDUTIdx ) && pDistObj && pDistObj->getClass())
												{	int iDistIdx = BEMPX_GetObjectIndex( pDistObj->getClass(), pDistObj /*, int iBEMProcIdx=-1*/ );			assert( iDistIdx >= 0 );
													if (iDistIdx >= 0)
														BEMPX_GetInteger( lDBID_HVACDist_Status, lDuctStatus, 0, -1, iDistIdx );
											}	}
										}
										BEMPX_GetInteger( lDBID_DUT_EqpCountsMustAlign, lEqpCountsMustAlign, 0, -1, iDUTIdx );

								// SAC 11/14/14 - revisions to ignore UnitTypeIdx values and store but don't create unique array elements for Count of equipment
										vector<long> laHtUnitCnt, laClUnitCnt;		// laHtUnitCntIdx, laClUnitCntIdx, laHtUnitTypIdx, laClUnitTypIdx, 
										vector<string> saHtUnitName, saClUnitName;
										long lNumSysTypes = 0, lEqpCnt;		QString sEqpName;
										// first load Heating/HtPump system info
										if (BEMPX_GetInteger( (bIsHP ? lDBID_DUT_NumHtPumpEquipTypes : lDBID_DUT_NumHeatEquipTypes), lNumSysTypes, 0, -1, iDUTIdx ) && lNumSysTypes > 0)
											for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
											{	if (	BEMPX_GetString(  (bIsHP ? lDBID_DUT_HVACHtPumpRef    : lDBID_DUT_HVACHeatRef   )+iEqp, sEqpName, FALSE, 0, -1, iDUTIdx ) && !sEqpName.isEmpty() &&
														BEMPX_GetInteger( (bIsHP ? lDBID_DUT_HtPumpEquipCount : lDBID_DUT_HeatEquipCount)+iEqp, lEqpCnt ,        0, -1, iDUTIdx ) && lEqpCnt > 0)
												{	laHtUnitCnt.push_back( lEqpCnt );
													saHtUnitName.push_back(   (const char*) sEqpName.toLocal8Bit().constData() );
												}
											//		for (iCnt=0; iCnt < lEqpCnt; iCnt++)
											//		{	laHtUnitTypIdx.push_back( iEqp+1 );
											//			laHtUnitCntIdx.push_back( iCnt+1 );
											//			saHtUnitName.push_back(   (const char*) sEqpName );
											//		}
											}
										// then load Cooling system info
										if (!bIsHP && BEMPX_GetInteger( lDBID_DUT_NumCoolEquipTypes, lNumSysTypes, 0, -1, iDUTIdx ) && lNumSysTypes > 0)
											for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
											{	if (	BEMPX_GetString(  lDBID_DUT_HVACCoolRef   +iEqp, sEqpName, FALSE, 0, -1, iDUTIdx ) && !sEqpName.isEmpty() &&
														BEMPX_GetInteger( lDBID_DUT_CoolEquipCount+iEqp, lEqpCnt ,        0, -1, iDUTIdx ) && lEqpCnt > 0)
												{	laClUnitCnt.push_back( lEqpCnt );
													saClUnitName.push_back(   (const char*) sEqpName.toLocal8Bit().constData() );
												}
											//		for (iCnt=0; iCnt < lEqpCnt; iCnt++)
											//		{	laClUnitTypIdx.push_back( iEqp+1 );
											//			laClUnitCntIdx.push_back( iCnt+1 );
											//			saClUnitName.push_back(   (const char*) sEqpName );
											//		}
											}

					// SAC 11/14/14 - no longer match heat/cool equipment w/ unmatched equip types or counts
					//					int iNumSCSysRptObjsToCreate = laHtUnitTypIdx.size();
					//					if (!bIsHP && laHtUnitTypIdx.size() != laClUnitTypIdx.size())
					//					{	// we have an inconsistent number of Ht/Cl units, log a message to that effect
					//						sTmp = QString( "CreateSCSysRptObjects Warning:  Inconsistent number of heating unit types/counts (%1) and cooling types/counts (%2) for DwellUnit object '%3'" ).arg( QString::number( laHtUnitTypIdx.size() ), QString::number( laClUnitTypIdx.size() ), sDUName );
					//						BEMPX_WriteLogFile( sTmp );
			   	//	
					//				// ??? - fill smaller array w/ name/type/count of last item in that array, up to the size of the larger array ???
			   	//	
					//						if (laHtUnitTypIdx.size() < laClUnitTypIdx.size())
					//							iNumSCSysRptObjsToCreate = laClUnitTypIdx.size();
					//					}

										vector<long> laSCSysRptCnt;
										vector<string> saSCSysRptName;
										int iEqpLoopCnt = saHtUnitName.size() + (lEqpCountsMustAlign == 0 ? saClUnitName.size() : 0);
										for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iEqpLoopCnt); iEqp++)
										{	int iHtgIdx = (iEqp < (int) saHtUnitName.size() ? iEqp : -1);
											int iClgIdx = (lEqpCountsMustAlign == 0 ? iEqp - saHtUnitName.size() : iHtgIdx);
											if (iClgIdx >= 0 && (int) saClUnitName.size() < (iClgIdx+1))	// SAC 12/23/15 - prevent accessing saClUnitName when not available (for no-cooling systems)
												iClgIdx = -1;
											long lCount = 0;
											vector<long> laDBIDs, laData;		vector<int> iaDataTypes;		vector<std::string> saData;		vector<double> faData;
										// cooling equip
											laDBIDs.push_back( lDBID_SCSysRpt_CoolSystem );
											laData.push_back( -1 );
											if (iClgIdx >= 0)
											{	iaDataTypes.push_back( BEMP_Str );
												saData.push_back( saClUnitName[iClgIdx] );
												faData.push_back( -1 );
												lCount = laClUnitCnt[iClgIdx];
											}
											else
											{	iaDataTypes.push_back( BEMP_Flt );
												saData.push_back( "" );
												faData.push_back( -99996 );
											}
										// heating equip
											laDBIDs.push_back( (bIsHP ? lDBID_SCSysRpt_HtPumpSystem : lDBID_SCSysRpt_HeatSystem) );
											laData.push_back( -1 );
											if (iHtgIdx >= 0)
											{	iaDataTypes.push_back( BEMP_Str );
												saData.push_back( saHtUnitName[iHtgIdx] );
												faData.push_back( -1 );
												lCount = laHtUnitCnt[iHtgIdx];
											}
											else
											{	iaDataTypes.push_back( BEMP_Flt );
												saData.push_back( "" );
												faData.push_back( -99996 );
											}
										// distrib equip
											laDBIDs.push_back( lDBID_SCSysRpt_HVACDistRef );
											laData.push_back( -1 );
											if (!sDistribName.isEmpty() && ((iHtgIdx >= 0 && lHtDucted > 0) || (iClgIdx >= 0 && lClDucted > 0)))
											{	iaDataTypes.push_back( BEMP_Str );
												saData.push_back( (const char*) sDistribName.toLocal8Bit().constData() );
												faData.push_back( -1 );
											}
											else
											{	iaDataTypes.push_back( BEMP_Flt );
												saData.push_back( "" );
												faData.push_back( -99996 );
											}
										// fan
											laDBIDs.push_back( lDBID_SCSysRpt_HVACFanRef );
											laData.push_back( -1 );
											if (!sFanName.isEmpty() && ((iHtgIdx >= 0 && lHtDucted > 0) || (iClgIdx >= 0 && lClDucted > 0)))		// same logic for including Fan as we have for Distrib ??
											{	iaDataTypes.push_back( BEMP_Str );
												saData.push_back( (const char*) sFanName.toLocal8Bit().constData() );
												faData.push_back( -1 );
											}
											else
											{	iaDataTypes.push_back( BEMP_Flt );
												saData.push_back( "" );
												faData.push_back( -99996 );
											}
										// SCSysTypeVal
											laDBIDs.push_back( lDBID_SCSysRpt_SCSysTypeVal );
											iaDataTypes.push_back( BEMP_Int );
											laData.push_back( (bIsHP ? 2 : 1) );	// 2-"Heat Pump Heating and Cooling System"  /  1-"Other Heating and Cooling System"
											saData.push_back( "" );
											faData.push_back( -1 );
										// Status  - SAC 12/14/15
											lSCSysStatus = (lZoneHVACStatus == 1 /*Existing*/ && lDuctStatus == 4 /*Existing+New*/) ? 4 : lZoneHVACStatus;
											laDBIDs.push_back( lDBID_SCSysRpt_Status );
											iaDataTypes.push_back( BEMP_Int );
											saData.push_back( "" );
											faData.push_back( -1 );
											if (lProj_RunScope == 1)
												laData.push_back( 3 );	// 3-"New"
											else if (lSCSysStatus > 0)
												laData.push_back( lSCSysStatus );
											else
											{	assert( FALSE );	// shouldn't happen
												laData.push_back( 3 );	// 3-"New"
											}

											for (int iCnt=1; (iCnt <= lDUCount && sErrMsg.isEmpty()); iCnt++)		// SAC 12/14/15 - create unique SCSysRpt object for each <count> of each DwellUnit
											{
											// Find or create ScSysRpt object
												//std::string sSCSysRptName;
												//int iRptObjRetVal = GetObjectMatchingData( iCID_SCSysRpt, sSCSysRptName, 1 /*iObjCreateOption*/, laDBIDs, iaDataTypes, saData, faData, laData, -1, NULL /*parent*/, BEMO_User );
												std::string sSCSysRptName;
												if (lDUCount > 1)
													sSCSysRptName = boost::str( boost::format( "%s %d/%d | " ) % sDUName.toLocal8Bit().constData() % iCnt % lDUCount );
												else
													sSCSysRptName = boost::str( boost::format( "%s | " ) % sDUName.toLocal8Bit().constData() );
												int iRptObjRetVal = GetObjectMatchingData( iCID_SCSysRpt, sSCSysRptName, 2 /*iObjCreateOption*/, laDBIDs, iaDataTypes, saData, faData, laData, -1, pDUObj /*parent*/, BEMO_User );
																					assert( iRptObjRetVal == 0 || iRptObjRetVal == 1 );
												if (iRptObjRetVal == 1)
													iNumObjsCreated++;
												else if (iRptObjRetVal > 10)
													sErrMsg = QString( "CreateSCSysRptObjects Error encountered retrieving/creating SCSysRpt object #%1 for DwellUnitType '%2'" ).arg( QString::number( iEqp+1 ), sDUName );
												int iSCSysIdx = (saSCSysRptName.size() < 1 || iRptObjRetVal == 1) ? saSCSysRptName.size() : -1;
												if (iSCSysIdx < 0)
												{	for (int iSR=0; (iSCSysIdx < 0 && iSR < (int) saSCSysRptName.size()); iSR++)
													{	if (sSCSysRptName == saSCSysRptName[iSR])
															iSCSysIdx = iSR;
													}
													if (iSCSysIdx < 0)
														iSCSysIdx = saSCSysRptName.size();
												}																							assert( iSCSysIdx >= 0 );
												if (iSCSysIdx < (int) saSCSysRptName.size())
													laSCSysRptCnt[iSCSysIdx] = laSCSysRptCnt[iSCSysIdx] + lCount;		// SCSysRpt already referenced in array, so just increment count
												else
												{	saSCSysRptName.push_back( sSCSysRptName );		// add SCSysRpt & count to arrays
													laSCSysRptCnt.push_back(  lCount );
												}
											// SAC 6/24/16 - added equipment count in order to get accurate overall equipment count across the entire model
												int iSCSysObjIdx = (iRptObjRetVal == 1 ? BEMPX_GetNumObjects( iCID_SCSysRpt )-1 : -1);			assert( iSCSysObjIdx >= 0 );
												long lEqpCnt = laSCSysRptCnt[iSCSysIdx];
												BEMPX_SetBEMData( lDBID_SCSysRpt_DUEquipCnt, BEMP_Int, (void*) &lEqpCnt, BEMO_User, iSCSysObjIdx );
											}	// end of loop over DwellUnit:Count
										}	// end of loop over possible SCSysRpt obejcts (found or created)

							// now STORE array of SCSysRpt objects and counts back to the DwellUnitType
										int iNumSCSysRpts = (saSCSysRptName.size() <= 10 ? saSCSysRptName.size() : 10);				assert( saSCSysRptName.size() <= 10 ); // if > 10, need to increase size of DwellUnitType:SCSysRpt* properties
										for (int iSR=0; (sErrMsg.isEmpty() && iSR < iNumSCSysRpts); iSR++)
										{	QString sSCSysName = saSCSysRptName[iSR].c_str();
											long lSCSysCnt = laSCSysRptCnt[iSR];
											if (sSCSysName.isEmpty() || lSCSysCnt < 1)
												sErrMsg = QString( "CreateSCSysRptObjects Error:  Invalid data encountered for SCSysRpt reference #%1 of DwellUnitType '%2'" ).arg( QString::number( iSR+1 ), sDUName );
											else if (BEMPX_SetBEMData( lDBID_DUT_SCSysRptRef   + iSR, BEMP_Str, (void*) sSCSysName.toLocal8Bit().constData(), BEMO_User, iDUTIdx ) < 0 ||
														BEMPX_SetBEMData( lDBID_DUT_SCSysRptCount + iSR, BEMP_Int, (void*)               &lSCSysCnt            , BEMO_User, iDUTIdx ) < 0 )
												sErrMsg = QString( "CreateSCSysRptObjects Error encountered storing SCSysRpt reference #%1 for DwellUnitType '%2'" ).arg( QString::number( iSR+1 ), sDUName );
										}

					// OLD method of creating individual SCSysRpt object for EVERY SINGLE Ht, Cl or HtCl combo
					//				// CREATE SCSysRpt objects
					//					for (int iDUCntIdx=1; (sErrMsg.isEmpty() && iDUCntIdx <= lDUCount); iDUCntIdx++)
					//						for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iNumSCSysRptObjsToCreate); iEqp++)
					//						{	sSCSysRptName = QString( "%s %1/%2 eqp %3/%4" ).arg( sDUName, QString::number( iDUCntIdx ), QString::number( lDUCount ), QString::number( iEqp+1 ), QString::number( iNumSCSysRptObjsToCreate ) );
					//							pSCSysRptObj = BEMPX_CreateObject( iCID_SCSysRpt, sSCSysRptName, pDUObj, BEMO_User, FALSE );
					//							if (pSCSysRptObj == NULL || pSCSysRptObj->getClass() == NULL)
					//								sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to create SCSysRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sSCSysRptName );
					//							else
					//							{	iM1Idx = BEMPX_GetObjectIndex( pSCSysRptObj->getClass(), pSCSysRptObj );
					//								if (iM1Idx < 0)
					//									sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to access index of SCSysRpt object '%1'" ).arg( sSCSysRptName );
					//								else
					//								{	// set heating/ht pump unit data
					//									if (iEqp < (int) laHtUnitTypIdx.size())
					//									{	if (BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSystem         : lDBID_SCSysRpt_HeatSystem        ), BEMP_Str, (void*) ((const char*) saHtUnitName[iEqp].c_str()), BEMO_User, iM1Idx ) < 0 ||
					//											 BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSysUnitTypeIdx : lDBID_SCSysRpt_HeatSysUnitTypeIdx), BEMP_Int, (void*)             &laHtUnitTypIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 ||
					//											 BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSysUnitTypeCnt : lDBID_SCSysRpt_HeatSysUnitTypeCnt), BEMP_Int, (void*)             &laHtUnitCntIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 )
					//											sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to set %1 equip data of SCSysRpt object '%2'" ).arg( (bIsHP ? "heating" : "heat pump"), sSCSysRptName );
					//									}
					//									// set cooling unit data
					//									if (iEqp < (int) laClUnitTypIdx.size())
					//									{	if (BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSystem        , BEMP_Str, (void*) ((const char*) saClUnitName[iEqp].c_str()), BEMO_User, iM1Idx ) < 0 ||
					//											 BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSysUnitTypeIdx, BEMP_Int, (void*)             &laClUnitTypIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 ||
					//											 BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSysUnitTypeCnt, BEMP_Int, (void*)             &laClUnitCntIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 )
					//											sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to set %1 equip data of SCSysRpt object '%2'" ).arg( "cooling", sSCSysRptName );
					//									}
					//							// note: no SCSysRpt:HVACSysRef set here since HVACSys objects don't (necessarily) exist @ this point (& that not how systems are created)
					//									if (sErrMsg.isEmpty())
					//										iNumObjsCreated++;
					//						}	}	}

									}	// if valid DwellUnitType type
						}	}	}
					}	// loop over DU children of Zone
				}
			}	// loop over zones
		}

		else
		{	// SINGLE FAMILY
			long lNumDwellingUnits, lNumRptHVACEqpUnits;
			if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NumDwellingUnits" ), lNumDwellingUnits, 1 ))
				sErrMsg = QString( "CreateSCSysRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:NumDwellingUnits" );
			else if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NumSCSysEquipUnits" ), lNumRptHVACEqpUnits, 0 ))
				sErrMsg = QString( "CreateSCSysRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:NumSCSysEquipUnits" );
			else
			{	if (lNumDwellingUnits > lNumRptHVACEqpUnits)
				{	assert( FALSE );		// 
					if (pEval->bVerboseOutput)
					{	QString sLocErrMsg = QString( "Warning: Unexpected condition found in CreateSCSysRptObjects(): Proj:NumDwellingUnits (%1) > Proj:NumSCSysEquipUnits (%2)" ).arg( QString::number( lNumDwellingUnits ), QString::number( lNumRptHVACEqpUnits ) );
						BEMPX_WriteLogFile( sLocErrMsg );
				}	}
				else
				{	int iNumHVACSyss = BEMPX_GetNumObjects( iCID_HVACSys );
					for (int iHV=0; (sErrMsg.isEmpty() && iHV < iNumHVACSyss); iHV++)
					{	// SAC 4/28/15 - added code to ensure creation of SCSysRpt objects when system is ducted and assigned HVACDist has a Status other than 'Existing' (& is greater than 40ft long) (issue 504)
						long lHVACDist_Status = -1,  lHVACDist_DuctsMayReqReport = -1, lHVACDist_IsLessThanFortyFt = -1;
						BEMObject* pHVACDistObj;
						if (BEMPX_GetObject( lDBID_HVACSys_DistribSystem, pHVACDistObj, -1, iHV ) && pHVACDistObj && pHVACDistObj->getClass())
						{	int iHVACDist_ObjIdx = BEMPX_GetObjectIndex( pHVACDistObj->getClass(), pHVACDistObj );
							if (iHVACDist_ObjIdx >= 0)
							{	BEMPX_GetInteger( lDBID_HVACDist_Status           , lHVACDist_Status           , -1, -1, iHVACDist_ObjIdx );
								BEMPX_GetInteger( lDBID_HVACDist_DuctsMayReqReport, lHVACDist_DuctsMayReqReport, -1, -1, iHVACDist_ObjIdx );
								BEMPX_GetInteger( lDBID_HVACDist_IsLessThanFortyFt, lHVACDist_IsLessThanFortyFt,  0, -1, iHVACDist_ObjIdx );
						}	}

						long lType, lTypeOK, lIsNew, lIsAltered, lIsExisting, lIsVerified, lMaxNumHVACEquipTypes, lHtOrClDucted, lEqpCountsMustAlign;
						double fFloorAreaServed;		QString sSysName;
						if (	BEMPX_GetInteger( lDBID_HVACSys_Type                , lType                , 0, -1, iHV ) &&
								BEMPX_GetInteger( lDBID_HVACSys_TypeOK              , lTypeOK              , 0, -1, iHV ) && lTypeOK > 0 &&
								BEMPX_GetInteger( lDBID_HVACSys_IsNew               , lIsNew               , 0, -1, iHV ) && 
								BEMPX_GetInteger( lDBID_HVACSys_IsAltered           , lIsAltered           , 0, -1, iHV ) && 
								BEMPX_GetInteger( lDBID_HVACSys_IsExisting          , lIsExisting          , 0, -1, iHV ) && 
								BEMPX_GetInteger( lDBID_HVACSys_IsVerified          , lIsVerified          , 0, -1, iHV ) && 
								BEMPX_GetInteger( lDBID_HVACSys_MaxNumHVACEquipTypes, lMaxNumHVACEquipTypes, 0, -1, iHV ) && lMaxNumHVACEquipTypes > 0 &&
								BEMPX_GetInteger( lDBID_HVACSys_HtOrClDucted        , lHtOrClDucted        , 0, -1, iHV ) &&
								BEMPX_GetInteger( lDBID_HVACSys_EqpCountsMustAlign  , lEqpCountsMustAlign  , 0, -1, iHV ) &&
								BEMPX_GetFloat(   lDBID_HVACSys_FloorAreaServed     , fFloorAreaServed     , 0, -1, iHV ) && fFloorAreaServed > 0.1 &&
								BEMPX_GetString(  lDBID_HVACSys_Name                , sSysName,       FALSE, 0, -1, iHV ) && !sSysName.isEmpty() )
				// SAC 4/28/15 - remove ALL conditions that prevented generation of SCSysRpt objects - issue 504
				//				(lIsNew > 0 || lIsAltered > 0 || (lIsExisting > 0 && lIsVerified > 0) ||
				//				 (lIsExisting > 0 && lHtOrClDucted > 0 && lHVACDist_DuctsMayReqReport > 0 &&
				//				  (lHVACDist_Status == 2 || (lHVACDist_Status > 2 && lHVACDist_IsLessThanFortyFt == 0)))) )		// SAC 4/28/15 - (issue 504)
						{	// This HVACSys object SHOULD have SCSysRpt objects created for it
							QString sDistribSystem, sFan;
							BEMPX_GetString( lDBID_HVACSys_DistribSystem, sDistribSystem, FALSE, 0, -1, iHV );
							BEMPX_GetString( lDBID_HVACSys_Fan          , sFan          , FALSE, 0, -1, iHV );
							long lHtDucted = (lHtOrClDucted == 1 || lHtOrClDucted == 3);
							long lClDucted = (lHtOrClDucted == 2 || lHtOrClDucted == 3);
							long lHVACSysStatus = (lIsNew > 0 ? 3 /*New*/ : (lIsAltered > 0 ? 2 /*Altered*/ : (lIsExisting > 0 ? 1 /*Existing*/ : 0 /*ERROR*/)));		// SAC 12/23/15
							pSysObj = BEMPX_GetObjectByClass( iCID_HVACSys, iError, iHV );
							if (pSysObj == NULL)
								sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to retrieve pointer to HVACSys object #%1 '%2'" ).arg( QString::number( iHV+1 ), sSysName );
							else
							{	bool bIsHP = (lType == 2);		int iEqp, iCnt, iM1Idx;
								vector<long> laHtUnitCnt, laClUnitCnt;		// laHtUnitTypIdx, laHtUnitCntIdx, laClUnitTypIdx, laClUnitCntIdx;
								vector<string> saHtUnitName, saClUnitName;
								long lNumSysTypes = 0, lDuctStatus=0, lEqpCnt;		QString sEqpName;
					// SAC 11/14/14 - revisions to ignore UnitTypeIdx values and store but don't create unique array elements for Count of equipment
								// first load Heating/HtPump system info
								if (BEMPX_GetInteger( (bIsHP ? lDBID_HVACSys_NumHtPumpSystemTypes : lDBID_HVACSys_NumHeatSystemTypes), lNumSysTypes, 0, -1, iHV ) && lNumSysTypes > 0)
									for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
									{	if (	BEMPX_GetString(  (bIsHP ? lDBID_HVACSys_HtPumpSystem      : lDBID_HVACSys_HeatSystem     )+iEqp, sEqpName, FALSE, 0, -1, iHV ) && !sEqpName.isEmpty() &&
												BEMPX_GetInteger( (bIsHP ? lDBID_HVACSys_HtPumpSystemCount : lDBID_HVACSys_HeatSystemCount)+iEqp, lEqpCnt ,        0, -1, iHV ) && lEqpCnt > 0)
										{	laHtUnitCnt.push_back( lEqpCnt );
											saHtUnitName.push_back( (const char*) sEqpName.toLocal8Bit().constData() );
										}
									//		for (iCnt=0; iCnt < lEqpCnt; iCnt++)
									//		{	laHtUnitTypIdx.push_back( iEqp+1 );
									//			laHtUnitCntIdx.push_back( iCnt+1 );
									//			saHtUnitName.push_back(   (const char*) sEqpName );
									//		}
									}
								// then load Cooling system info
								if (!bIsHP && BEMPX_GetInteger( lDBID_HVACSys_NumCoolSystemTypes, lNumSysTypes, 0, -1, iHV ) && lNumSysTypes > 0)
									for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
									{	if (	BEMPX_GetString(  lDBID_HVACSys_CoolSystem     +iEqp, sEqpName, FALSE, 0, -1, iHV ) && !sEqpName.isEmpty() &&
												BEMPX_GetInteger( lDBID_HVACSys_CoolSystemCount+iEqp, lEqpCnt ,        0, -1, iHV ) && lEqpCnt > 0)
										{	laClUnitCnt.push_back( lEqpCnt );
											saClUnitName.push_back( (const char*) sEqpName.toLocal8Bit().constData() );
										}
									//		for (iCnt=0; iCnt < lEqpCnt; iCnt++)
									//		{	laClUnitTypIdx.push_back( iEqp+1 );
									//			laClUnitCntIdx.push_back( iCnt+1 );
									//			saClUnitName.push_back(   (const char*) sEqpName );
									//		}
									}
								// duct status
								if (!sDistribSystem.isEmpty() && lHVACDist_Status > 0 && (lHtDucted > 0 || lClDucted > 0))
									lDuctStatus = lHVACDist_Status;

					//			int iNumSCSysRptObjsToCreate = laHtUnitTypIdx.size();
					//			if (!bIsHP && laHtUnitTypIdx.size() != laClUnitTypIdx.size())
					//			{	// we have an inconsistent number of Ht/Cl units, log a message to that effect
					//				sTmp = QString( "CreateSCSysRptObjects Warning:  Inconsistent number of heating unit types/counts (%1) and cooling types/counts (%2) for HVACSys object '%3'" ).arg( QString::number( laHtUnitTypIdx.size() ), QString::number( laClUnitTypIdx.size() ), sSysName );
					//				BEMPX_WriteLogFile( sTmp );
   				//
					//		// ??? - fill smaller array w/ name/type/count of last item in that array, up to the size of the larger array ???
   				//
					//				if (laHtUnitTypIdx.size() < laClUnitTypIdx.size())
					//					iNumSCSysRptObjsToCreate = laClUnitTypIdx.size();
					//			}

								vector<long> laSCSysRptCnt;
								vector<string> saSCSysRptName;
								int iEqpLoopCnt = saHtUnitName.size() + (lEqpCountsMustAlign == 0 ? saClUnitName.size() : 0);
								for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iEqpLoopCnt); iEqp++)
								{	int iHtgIdx = (iEqp < (int) saHtUnitName.size() ? iEqp : -1);
									int iClgIdx = (lEqpCountsMustAlign == 0 ? iEqp - saHtUnitName.size() : iHtgIdx);
									if (iClgIdx >= 0 && (int) saClUnitName.size() < (iClgIdx+1))	// SAC 12/23/15 - prevent accessing saClUnitName when not available (for no-cooling systems)
										iClgIdx = -1;
									long lCount = 0;
									vector<long> laDBIDs, laData;		vector<int> iaDataTypes;		vector<std::string> saData;		vector<double> faData;
								// cooling equip
									laDBIDs.push_back( lDBID_SCSysRpt_CoolSystem );
									laData.push_back( -1 );
									if (iClgIdx >= 0)
									{	iaDataTypes.push_back( BEMP_Str );
										saData.push_back( saClUnitName[iClgIdx] );
										faData.push_back( -1 );
										lCount = laClUnitCnt[iClgIdx];
									}
									else
									{	iaDataTypes.push_back( BEMP_Flt );
										saData.push_back( "" );
										faData.push_back( -99996 );
									}
								// heating equip
									laDBIDs.push_back( (bIsHP ? lDBID_SCSysRpt_HtPumpSystem : lDBID_SCSysRpt_HeatSystem) );
									laData.push_back( -1 );
									if (iHtgIdx >= 0)
									{	iaDataTypes.push_back( BEMP_Str );
										saData.push_back( saHtUnitName[iHtgIdx] );
										faData.push_back( -1 );
										lCount = laHtUnitCnt[iHtgIdx];
									}
									else
									{	iaDataTypes.push_back( BEMP_Flt );
										saData.push_back( "" );
										faData.push_back( -99996 );
									}
								// distrib equip
									laDBIDs.push_back( lDBID_SCSysRpt_HVACDistRef );
									laData.push_back( -1 );
									if (!sDistribSystem.isEmpty() && ((iHtgIdx >= 0 && lHtDucted > 0) || (iClgIdx >= 0 && lClDucted > 0)))
									{	iaDataTypes.push_back( BEMP_Str );
										saData.push_back( (const char*) sDistribSystem.toLocal8Bit().constData() );
										faData.push_back( -1 );
									}
									else
									{	iaDataTypes.push_back( BEMP_Flt );
										saData.push_back( "" );
										faData.push_back( -99996 );
									}
								// fan
									laDBIDs.push_back( lDBID_SCSysRpt_HVACFanRef );
									laData.push_back( -1 );
									if (!sFan.isEmpty() && ((iHtgIdx >= 0 && lHtDucted > 0) || (iClgIdx >= 0 && lClDucted > 0)))		// same logic for including Fan as we have for Distrib ??
									{	iaDataTypes.push_back( BEMP_Str );
										saData.push_back( (const char*) sFan.toLocal8Bit().constData() );
										faData.push_back( -1 );
									}
									else
									{	iaDataTypes.push_back( BEMP_Flt );
										saData.push_back( "" );
										faData.push_back( -99996 );
									}
								// SCSysTypeVal
									laDBIDs.push_back( lDBID_SCSysRpt_SCSysTypeVal );
									iaDataTypes.push_back( BEMP_Int );
									laData.push_back( lType );
									saData.push_back( "" );
									faData.push_back( -1 );
								// Status  - SAC 12/14/15
									long lSCSysStatus = (lHVACSysStatus == 1 /*Existing*/ && lDuctStatus == 4 /*Existing+New*/) ? 4 : lHVACSysStatus;
									laDBIDs.push_back( lDBID_SCSysRpt_Status );
									iaDataTypes.push_back( BEMP_Int );
									saData.push_back( "" );
									faData.push_back( -1 );
									if (lProj_RunScope == 1)
										laData.push_back( 3 );	// 3-"New"
									else if (lSCSysStatus > 0)
										laData.push_back( lSCSysStatus );
									else
									{	assert( FALSE );	// shouldn't happen
										laData.push_back( 3 );	// 3-"New"
									}

								// Find or create ScSysRpt object
									std::string sSCSysRptName;
									int iRptObjRetVal = GetObjectMatchingData( iCID_SCSysRpt, sSCSysRptName, 1 /*iObjCreateOption*/, laDBIDs, iaDataTypes, saData, faData, laData, -1, NULL /*parent*/, BEMO_User );
																		assert( iRptObjRetVal == 0 || iRptObjRetVal == 1 );
									if (iRptObjRetVal == 1)
										iNumObjsCreated++;
									else if (iRptObjRetVal > 10)
										sErrMsg = QString( "CreateSCSysRptObjects Error encountered retrieving/creating SCSysRpt object #%1 for HVACSys '%2'" ).arg( QString::number( iEqp+1 ), sSysName );
									int iSCSysIdx = (saSCSysRptName.size() < 1 || iRptObjRetVal == 1) ? saSCSysRptName.size() : -1;
									if (iSCSysIdx < 0)
									{	for (int iSR=0; (iSCSysIdx < 0 && iSR < (int) saSCSysRptName.size()); iSR++)
										{	if (sSCSysRptName == saSCSysRptName[iSR])
												iSCSysIdx = iSR;
										}
										if (iSCSysIdx < 0)
											iSCSysIdx = saSCSysRptName.size();
									}																							assert( iSCSysIdx >= 0 );
									if (iSCSysIdx < (int) saSCSysRptName.size())
										laSCSysRptCnt[iSCSysIdx] = laSCSysRptCnt[iSCSysIdx] + lCount;		// SCSysRpt already referenced in array, so just increment count
									else
									{	saSCSysRptName.push_back( sSCSysRptName );		// add SCSysRpt & count to arrays
										laSCSysRptCnt.push_back(  lCount );
									}
								}	// end of loop over possible SCSysRpt obejcts (found or created)

					// now STORE array of SCSysRpt objects and counts back to the HVACSys
								int iNumSCSysRpts = (saSCSysRptName.size() <= 20 ? saSCSysRptName.size() : 20);				assert( saSCSysRptName.size() <= 20 ); // if > 20, need to increase size of HVACSys:SCSysRpt* properties
								for (int iSR=0; (sErrMsg.isEmpty() && iSR < iNumSCSysRpts); iSR++)
								{	QString sSCSysName = saSCSysRptName[iSR].c_str();
									long lSCSysCnt = laSCSysRptCnt[iSR];
									if (sSCSysName.isEmpty() || lSCSysCnt < 1)
										sErrMsg = QString( "CreateSCSysRptObjects Error:  Invalid data encountered for SCSysRpt reference #%1 of HVACSys '%2'" ).arg( QString::number( iSR+1 ), sSysName );
									else if (BEMPX_SetBEMData( lDBID_HVACSys_SCSysRptRef   + iSR, BEMP_Str, (void*) sSCSysName.toLocal8Bit().constData(), BEMO_User, iHV ) < 0 ||
												BEMPX_SetBEMData( lDBID_HVACSys_SCSysRptCount + iSR, BEMP_Int, (void*)               &lSCSysCnt            , BEMO_User, iHV ) < 0 )
										sErrMsg = QString( "CreateSCSysRptObjects Error encountered storing SCSysRpt reference #%1 for HVACSys '%2'" ).arg( QString::number( iSR+1 ), sSysName );
								}

			// OLD method of creating individual SCSysRpt object for EVERY SINGLE Ht, Cl or HtCl combo
			//				// CREATE SCSysRpt objects
			//					for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iNumSCSysRptObjsToCreate); iEqp++)
			//					{	sSCSysRptName = QString( "%1 SCSysRpt %2" ).arg( sSysName, QString::number( iEqp+1 ) );
			//						pSCSysRptObj = BEMPX_CreateObject( iCID_SCSysRpt, sSCSysRptName, pSysObj, BEMO_User, FALSE );
			//						if (pSCSysRptObj == NULL || pSCSysRptObj->getClass() == NULL)
			//							sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to create SCSysRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sSCSysRptName );
			//						else
			//						{	iM1Idx = BEMPX_GetObjectIndex( pSCSysRptObj->getClass(), pSCSysRptObj );
			//							if (iM1Idx < 0)
			//								sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to access index of SCSysRpt object '%1'" ).arg( sSCSysRptName );
			//							else
			//							{
//			//								VERIFY( BEMPX_SetBEMData( lDBID_SCSysRpt_HVACSysRef, BEMP_Str, (void*) ((const char*) sSysName), BEMO_User, iM1Idx ) >= 0 );	// SAC 10/14/14
			//								// set heating/ht pump unit data
			//								if (iEqp < (int) laHtUnitTypIdx.size())
			//								{	if (BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSystem         : lDBID_SCSysRpt_HeatSystem        ), BEMP_Str, (void*) ((const char*) saHtUnitName[iEqp].c_str()), BEMO_User, iM1Idx ) < 0 ||
			//											FALSE)
//			//										 BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSysUnitTypeIdx : lDBID_SCSysRpt_HeatSysUnitTypeIdx), BEMP_Int, (void*)             &laHtUnitTypIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 ||
//			//										 BEMPX_SetBEMData( (bIsHP ? lDBID_SCSysRpt_HtPumpSysUnitTypeCnt : lDBID_SCSysRpt_HeatSysUnitTypeCnt), BEMP_Int, (void*)             &laHtUnitCntIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 )
			//										sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to set %1 equip data of SCSysRpt object '%2'" ).arg( (bIsHP ? "heating" : "heat pump"), sSCSysRptName );
			//								}
			//								// set cooling unit data
			//								if (iEqp < (int) laClUnitTypIdx.size())
			//								{	if (BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSystem        , BEMP_Str, (void*) ((const char*) saClUnitName[iEqp].c_str()), BEMO_User, iM1Idx ) < 0 ||
			//											FALSE)
//			//										 BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSysUnitTypeIdx, BEMP_Int, (void*)             &laClUnitTypIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 ||
//			//										 BEMPX_SetBEMData( lDBID_SCSysRpt_CoolSysUnitTypeCnt, BEMP_Int, (void*)             &laClUnitCntIdx[iEqp]         , BEMO_User, iM1Idx ) < 0 )
			//										sErrMsg = QString( "CreateSCSysRptObjects Error:  Unable to set %1 equip data of SCSysRpt object '%2'" ).arg( "cooling", sSCSysRptName );
			//								}
			//								if (sErrMsg.isEmpty())
			//									iNumObjsCreated++;
			//					}	}	}
							}	// else (system object pointer is valid)
						}	// end of if (system requires generation of child SCSysRpt objects)
					}	// end of for (each HVACSys object in model)
				}	// else (no DBID errors)
			}	// else (global parameters OK)
	}	}

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}

	return iNumObjsCreated;
}


int CreateDHWRptObjects( QString& sErrMsg, ExpEvalStruct* pEval, ExpError* error )		// SAC 3/14/14
{	int iNumObjsCreated = 0;
	long lIsMultiFamily;
	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:IsMultiFamily" ), lIsMultiFamily ))
		sErrMsg = QString( "CreateDHWRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:IsMultiFamily" );
	else
	{
		int iNumErrors = 0, iError;		QString sTmp, sDHWSysRptName;
	//	int iCID_Proj      = GetObjectID_LogError( "Proj",      iNumErrors, sTmp );
		int iCID_DHWSys    = GetObjectID_LogError( "DHWSys",    iNumErrors, sTmp );
		int iCID_DHWSysRpt = GetObjectID_LogError( "DHWSysRpt", iNumErrors, sTmp );
		int iCID_DwellUnit     = GetObjectID_LogError( "DwellUnit",     iNumErrors, sTmp );
		int iCID_DwellUnitType = GetObjectID_LogError( "DwellUnitType", iNumErrors, sTmp );
		int iCID_Zone          = GetObjectID_LogError( "Zone",          iNumErrors, sTmp );

		long lDBID_DHWSys_Name             = GetPropertyDBID_LogError( "DHWSys", "Name",             iCID_DHWSys, iNumErrors, sTmp );
		long lDBID_DHWSys_TotNumDHWHeaters = GetPropertyDBID_LogError( "DHWSys", "TotNumDHWHeaters", iCID_DHWSys, iNumErrors, sTmp );
      long lDBID_DHWSys_SystemType       = GetPropertyDBID_LogError( "DHWSys", "SystemType",       iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Sym,  1,  0,  0, "",     0,                        8001, "DHW system type"    
   //   long lDBID_DHWSys_IsNew   		       = GetPropertyDBID_LogError( "DHWSys", "IsNew",                iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is New"
   //   long lDBID_DHWSys_IsAltered   	       = GetPropertyDBID_LogError( "DHWSys", "IsAltered",            iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is Altered"
   //   long lDBID_DHWSys_IsExisting   	    = GetPropertyDBID_LogError( "DHWSys", "IsExisting",           iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "flag set if this object is Existing"
   //   long lDBID_DHWSys_IsVerified   	    = GetPropertyDBID_LogError( "DHWSys", "IsVerified",           iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",     0,                        3008, "existing conditions will be HERS verified"
      long lDBID_DHWSys_FloorAreaServed  = GetPropertyDBID_LogError( "DHWSys", "FloorAreaServed",  iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Flt,  6,  0,  0, "ft2",  0,  0,   8008, "Floor area served by this system" 
      long lDBID_DHWSys_NumDHWHeaters    = GetPropertyDBID_LogError( "DHWSys", "NumDHWHeaters",    iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int, 
      long lDBID_DHWSys_HeaterMult       = GetPropertyDBID_LogError( "DHWSys", "HeaterMult",       iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Int,  6, 
      long lDBID_DHWSys_DHWHeater        = GetPropertyDBID_LogError( "DHWSys", "DHWHeater",        iCID_DHWSys, iNumErrors, sTmp );	// BEMP_Obj,  6,  1,  0, "",     1, "DHWHeater",   

      long lDBID_DHWSysRpt_DHWHeaterRef  = GetPropertyDBID_LogError( "DHWSysRpt", "DHWHeaterRef",  iCID_DHWSysRpt, iNumErrors, sTmp );  // BEMP_Obj,  1,  0,  0, "",    0,  1, "DHWHeater",  
      long lDBID_DHWSysRpt_DHWHeaterIdx  = GetPropertyDBID_LogError( "DHWSysRpt", "DHWHeaterIdx",  iCID_DHWSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,               
      long lDBID_DHWSysRpt_DHWHeaterCnt  = GetPropertyDBID_LogError( "DHWSysRpt", "DHWHeaterCnt",  iCID_DHWSysRpt, iNumErrors, sTmp );  // BEMP_Int,  1,  0,  0, "",    0,  0,               
      long lDBID_DHWSysRpt_DHWSysRef     = GetPropertyDBID_LogError( "DHWSysRpt", "DHWSysRef",     iCID_DHWSysRpt, iNumErrors, sTmp );  // 
      long lDBID_DHWSysRpt_DHWSysIdx     = GetPropertyDBID_LogError( "DHWSysRpt", "DHWSysIdx",     iCID_DHWSysRpt, iNumErrors, sTmp );  // SAC 10/14/14

		long lDBID_DU_Name             = GetPropertyDBID_LogError( "DwellUnit", "Name",             iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DU_DwellUnitTypeRef = GetPropertyDBID_LogError( "DwellUnit", "DwellUnitTypeRef", iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DU_Count            = GetPropertyDBID_LogError( "DwellUnit", "Count",            iCID_DwellUnit, iNumErrors, sTmp );

		long lDBID_DUT_Name           = GetPropertyDBID_LogError( "DwellUnitType", "Name",           iCID_DwellUnitType, iNumErrors, sTmp );
      long lDBID_DUT_NumDHWSysTypes = GetPropertyDBID_LogError( "DwellUnitType", "NumDHWSysTypes", iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int,  1,  0,  0, "",   0,  0,             8004, "Number of DHW systems that serve this DwellUnitType"    
      long lDBID_DUT_DHWSysRef      = GetPropertyDBID_LogError( "DwellUnitType", "DHWSysRef",      iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Obj,  5,  1,  0, "",   0,  1, "DHWSys",   8004, "DHW system that serves this equip zone type"    
      long lDBID_DUT_ServedByDHWSys = GetPropertyDBID_LogError( "DwellUnitType", "ServedByDHWSys", iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int,  1,  0,  0, "",   0,  0,             8004, "Boolean (0/1) whether or not this DUT is served by one or more valid DHWSys objects"    

		long lType, lTotNumDHWHeaters;		double fFloorAreaServed;
		//long lTypeOK, lIsNew, lIsAltered, lIsExisting, lIsVerified;
		QString sSysName;
		BEMObject *pSysObj, *pDHWSysRptObj;

		if (iNumErrors > 0)
		{	if (iNumErrors > 1)
				sErrMsg = QString( "Error initializing CreateDHWRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
			else
				sErrMsg = QString( "Error initializing CreateDHWRptObjects database ID %1" ).arg( sTmp );
		}

		else if (lIsMultiFamily > 0)
	// SAC 7/1/14 - added separate path for creating MFam DHWSysRpt objects
		{	QString sZnName, sDUName, sDUTName;
			BEMObject *pDUObj, *pDUTObj;
			int iNumZones      = BEMPX_GetNumObjects( iCID_Zone      );
			for (int iZnIdx=0; (sErrMsg.isEmpty() && iZnIdx < iNumZones); iZnIdx++)
			{	//VERIFY( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_Zone ), sZnName, FALSE, 0, -1, iZnIdx ) && !sZnName.isEmpty() );
				int iNumDUChildren = (int) BEMPX_GetNumChildren( iCID_Zone, iZnIdx, BEMO_User, iCID_DwellUnit /*, iBEMProcIdx=-1*/ );
				if (iNumDUChildren < 1)
					sErrMsg = QString( "CreateDHWRptObjects Error:  No DwellUnit children found for Zone '%1'" ).arg( sZnName );
				else
				{	long lDUCount;
					for (int i1DUChld=1; (sErrMsg.isEmpty() && i1DUChld <= iNumDUChildren); i1DUChld++)
					{	BEM_ObjType otDU;
						int iDUIdx = BEMPX_GetChildObjectIndex( iCID_Zone, iCID_DwellUnit, iError, otDU, i1DUChld, iZnIdx /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );
						if (iDUIdx < 0)
							sErrMsg = QString( "CreateDHWRptObjects Error encountered retrieving object index of DwellUnit child #%1 of Zone '%2'" ).arg( QString::number( i1DUChld ), sZnName );
						else
						{	BEMPX_GetString( lDBID_DU_Name, sDUName, FALSE, 0, -1, iDUIdx );		assert( !sDUName.isEmpty() );
							pDUObj = BEMPX_GetObjectByClass( iCID_DwellUnit, iError, iDUIdx );
							if (pDUObj == NULL)
								sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to retrieve pointer to DwellUnit object #%1 '%2'" ).arg( QString::number( iDUIdx+1 ), sDUName );
							else if (!BEMPX_GetObject( lDBID_DU_DwellUnitTypeRef, pDUTObj, -1, iDUIdx /*, int iObjType=BEMO_User, int iBEMProcIdx=-1*/ ) || pDUTObj==NULL || pDUTObj->getClass()==NULL)
								sErrMsg = QString( "CreateDHWRptObjects Error encountered retrieving DwellUnitTypeRef of DwellUnit '%1'" ).arg( sDUName );
							else if (!BEMPX_GetInteger( lDBID_DU_Count, lDUCount, 0, -1, iDUIdx ) || lDUCount < 1)
							{	// IGNORE invalid DwellUnit:Count ???
							}
							else
							{	int iDUTIdx = BEMPX_GetObjectIndex( pDUTObj->getClass(), pDUTObj /*, int iBEMProcIdx=-1*/ );			assert( iDUTIdx >= 0 );
								if (iDUTIdx < 0)
									sErrMsg = QString( "CreateDHWRptObjects Error encountered retrieving object index of DwellUnitTypeRef referenced by DwellUnit '%1'" ).arg( sDUName );
								else
								{	BEMPX_GetString( lDBID_DUT_Name, sDUTName, FALSE, 0, -1, iDUTIdx );		assert( !sDUTName.isEmpty() );
									long lDUT_NumDHWSysTypes, lDUT_ServedByDHWSys;
									if (BEMPX_GetInteger( lDBID_DUT_NumDHWSysTypes, lDUT_NumDHWSysTypes, 0, -1, iDUTIdx ) && lDUT_NumDHWSysTypes > 0 &&
										 BEMPX_GetInteger( lDBID_DUT_ServedByDHWSys, lDUT_ServedByDHWSys, 0, -1, iDUTIdx ) && lDUT_ServedByDHWSys > 0 )
									{	for (int iDUCntIdx=1; (sErrMsg.isEmpty() && iDUCntIdx <= lDUCount); iDUCntIdx++)
											for (int iDUT_DHWIdx = 0; (sErrMsg.isEmpty() && iDUT_DHWIdx < lDUT_NumDHWSysTypes); iDUT_DHWIdx++)
												{	BEMPX_GetObject( lDBID_DUT_DHWSysRef + iDUT_DHWIdx, pSysObj, -1, iDUTIdx /*, int iObjType=BEMO_User, int iBEMProcIdx=-1*/ );
													int iDHWSysIdx = ((pSysObj==NULL || pSysObj->getClass()==NULL) ? -1 : BEMPX_GetObjectIndex( pSysObj->getClass(), pSysObj /*, int iBEMProcIdx=-1*/ ));			assert( iDHWSysIdx >= 0 );
													if (iDHWSysIdx < 0)
														sErrMsg = QString( "CreateDHWRptObjects Error encountered retrieving object index of DHWSys #%1 referenced by DwellUnitType '%2'" ).arg( QString::number( iDUT_DHWIdx+1 ), sDUTName );
													else if (	BEMPX_GetInteger( lDBID_DHWSys_SystemType      , lType            , 0, -1, iDHWSysIdx ) && lType > 0 &&
																//	BEMPX_GetInteger( lDBID_DHWSys_TypeOK          , lTypeOK          , 0, -1, iDHWSysIdx ) && lTypeOK > 0 &&
																//	BEMPX_GetInteger( lDBID_DHWSys_IsNew           , lIsNew           , 0, -1, iDHWSysIdx ) && 
																//	BEMPX_GetInteger( lDBID_DHWSys_IsAltered       , lIsAltered       , 0, -1, iDHWSysIdx ) && 
																//	BEMPX_GetInteger( lDBID_DHWSys_IsExisting      , lIsExisting      , 0, -1, iDHWSysIdx ) && 
																//	BEMPX_GetInteger( lDBID_DHWSys_IsVerified      , lIsVerified      , 0, -1, iDHWSysIdx ) && 
																	BEMPX_GetInteger( lDBID_DHWSys_TotNumDHWHeaters, lTotNumDHWHeaters, 0, -1, iDHWSysIdx ) && lTotNumDHWHeaters > 0 &&
																	BEMPX_GetFloat(   lDBID_DHWSys_FloorAreaServed , fFloorAreaServed , 0, -1, iDHWSysIdx ) && fFloorAreaServed > 0.1 &&
																	BEMPX_GetString(  lDBID_DHWSys_Name            , sSysName,   FALSE, 0, -1, iDHWSysIdx ) && !sSysName.isEmpty() &&
																	TRUE  )
													{	// DHWSys assigned to DUT is valid 
														int iEqp, iCnt, iDRIdx;
														long lDHWSysAssignIdx = iDUT_DHWIdx + 1;  // SAC 10/14/14
														vector<long> laDHWHtrTypIdx, laDHWHtrCntIdx;
														vector<string> saDHWHtrName;
														long lNumSysTypes = 0, lEqpCnt;		QString sEqpName;
														// first load DHW heater info
														if (BEMPX_GetInteger( lDBID_DHWSys_NumDHWHeaters, lNumSysTypes, 0, -1, iDHWSysIdx ) && lNumSysTypes > 0)
															for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
															{	if (	BEMPX_GetString(  lDBID_DHWSys_DHWHeater +iEqp, sEqpName, FALSE, 0, -1, iDHWSysIdx ) && !sEqpName.isEmpty() &&
																		BEMPX_GetInteger( lDBID_DHWSys_HeaterMult+iEqp, lEqpCnt ,        0, -1, iDHWSysIdx ) && lEqpCnt > 0)
																{	laDHWHtrTypIdx.push_back( iEqp+1 );
																	laDHWHtrCntIdx.push_back( lEqpCnt );
																	saDHWHtrName.push_back(   (const char*) sEqpName.toLocal8Bit().constData() );
															}	}
													// SAC 10/14/14 - replaced below w/ above that causes only 1 DHWSysRpt for 1-N Count of this DHWHeater within this row of the DHWSys heater assignments
													//				for (iCnt=0; iCnt < lEqpCnt; iCnt++)
													//				{	laDHWHtrTypIdx.push_back( iEqp+1 );
													//					laDHWHtrCntIdx.push_back( iCnt+1 );
													//					saDHWHtrName.push_back(   (const char*) sEqpName );
													//		}		}
														int iNumDHWRptObjsToCreate = laDHWHtrTypIdx.size();
													// CREATE DHWSysRpt objects
														for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iNumDHWRptObjsToCreate); iEqp++)
														{	sDHWSysRptName = QString( "%1 %2/%3 | %4 %5/%6 | Eqp %7/%8" ).arg( sDUName, QString::number( iDUCntIdx ), QString::number( lDUCount ), sSysName, QString::number( iDUT_DHWIdx+1 ), QString::number( lDUT_NumDHWSysTypes ), QString::number( iEqp+1 ), QString::number( iNumDHWRptObjsToCreate ) );
															pDHWSysRptObj = BEMPX_CreateObject( iCID_DHWSysRpt, sDHWSysRptName.toLocal8Bit().constData(), pDUObj, BEMO_User, FALSE );
															if (pDHWSysRptObj == NULL || pDHWSysRptObj->getClass() == NULL)
																sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to create DHWSysRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sDHWSysRptName );
															else
															{	iDRIdx = BEMPX_GetObjectIndex( pDHWSysRptObj->getClass(), pDHWSysRptObj );
																if (iDRIdx < 0)
																	sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to access index of DHWSysRpt object '%1'" ).arg( sDHWSysRptName );
																else
																{	// set DHW heater data
																	if (iEqp < (int) laDHWHtrTypIdx.size())
																	{	if (BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWSysRef   , BEMP_Str, (void*)         sSysName.toLocal8Bit().constData(), BEMO_User, iDRIdx ) < 0 ||
																			 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWSysIdx   , BEMP_Int, (void*)             &lDHWSysAssignIdx             , BEMO_User, iDRIdx ) < 0 ||
																			 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterRef, BEMP_Str, (void*) ((const char*) saDHWHtrName[iEqp].c_str()), BEMO_User, iDRIdx ) < 0 ||
																			 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterIdx, BEMP_Int, (void*)             &laDHWHtrTypIdx[iEqp]         , BEMO_User, iDRIdx ) < 0 ||
																			 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterCnt, BEMP_Int, (void*)             &laDHWHtrCntIdx[iEqp]         , BEMO_User, iDRIdx ) < 0 )
																			sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to set %1 equip data of DHWSysRpt object '%2'" ).arg( "DHW", sDHWSysRptName );
																	}
																	if (sErrMsg.isEmpty())
																		iNumObjsCreated++;
														}	}	}
													}
												}	// loop over DUCount & DUT DHW systems & system pointer valid
						}	}	}	}
					}	// end of for - loop over DUChildren of zone
				}
			}	// end of loop over Zones
		}	// else if IsMultiFamily

		else
		{	// SINGLE FAMILY
			long lNumDwellingUnits, lNumDHWEquipUnits;
			if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NumDwellingUnits" ), lNumDwellingUnits, 1 ))
				sErrMsg = QString( "CreateDHWRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:NumDwellingUnits" );
			else if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:NumDHWEquipUnits" ), lNumDHWEquipUnits, 0 ))
				sErrMsg = QString( "CreateDHWRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:NumDHWEquipUnits" );
			else
			{	if (lNumDwellingUnits > lNumDHWEquipUnits)
				{	assert( FALSE );		// 
					if (pEval->bVerboseOutput)
					{	QString sLocErrMsg = QString( "Warning: Unexpected condition found in CreateDHWRptObjects(): Proj:NumDwellingUnits (%1) > Proj:NumDHWEquipUnits (%2)" ).arg( QString::number( lNumDwellingUnits ), QString::number( lNumDHWEquipUnits ) );
						BEMPX_WriteLogFile( sLocErrMsg );
				}	}

				int iNumDHWSyss = BEMPX_GetNumObjects( iCID_DHWSys );
				for (int iDHWSysIdx=0; (sErrMsg.isEmpty() && iDHWSysIdx < iNumDHWSyss); iDHWSysIdx++)
				{	if (	BEMPX_GetInteger( lDBID_DHWSys_SystemType      , lType            , 0, -1, iDHWSysIdx ) && lType > 0 &&
						//	BEMPX_GetInteger( lDBID_DHWSys_TypeOK          , lTypeOK          , 0, -1, iDHWSysIdx ) && lTypeOK > 0 &&
						//	BEMPX_GetInteger( lDBID_DHWSys_IsNew           , lIsNew           , 0, -1, iDHWSysIdx ) && 
						//	BEMPX_GetInteger( lDBID_DHWSys_IsAltered       , lIsAltered       , 0, -1, iDHWSysIdx ) && 
						//	BEMPX_GetInteger( lDBID_DHWSys_IsExisting      , lIsExisting      , 0, -1, iDHWSysIdx ) && 
						//	BEMPX_GetInteger( lDBID_DHWSys_IsVerified      , lIsVerified      , 0, -1, iDHWSysIdx ) && 
							BEMPX_GetInteger( lDBID_DHWSys_TotNumDHWHeaters, lTotNumDHWHeaters, 0, -1, iDHWSysIdx ) && lTotNumDHWHeaters > 0 &&
							BEMPX_GetFloat(   lDBID_DHWSys_FloorAreaServed , fFloorAreaServed , 0, -1, iDHWSysIdx ) && fFloorAreaServed > 0.1 &&
							BEMPX_GetString(  lDBID_DHWSys_Name            , sSysName,   FALSE, 0, -1, iDHWSysIdx ) && !sSysName.isEmpty() &&
						//	(lIsNew > 0 || lIsAltered > 0 || (lIsExisting > 0 && lIsVerified > 0)) )
							TRUE )
					{	// This DHWSys object SHOULD have DHWSysRpt child objects created for it
						pSysObj = BEMPX_GetObjectByClass( iCID_DHWSys, iError, iDHWSysIdx );
						if (pSysObj == NULL)
							sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to retrieve pointer to DHWSys object #%1 '%2'" ).arg( QString::number( iDHWSysIdx+1 ), sSysName );
						else
						{	int iEqp, iCnt, iDRIdx;
							vector<long> laDHWHtrTypIdx, laDHWHtrCntIdx;
							vector<string> saDHWHtrName;
							long lNumSysTypes = 0, lEqpCnt;		QString sEqpName;
							// first load DHW heater info
							if (BEMPX_GetInteger( lDBID_DHWSys_NumDHWHeaters, lNumSysTypes, 0, -1, iDHWSysIdx ) && lNumSysTypes > 0)
								for (iEqp=0; iEqp < lNumSysTypes; iEqp++)
								{	if (	BEMPX_GetString(  lDBID_DHWSys_DHWHeater +iEqp, sEqpName, FALSE, 0, -1, iDHWSysIdx ) && !sEqpName.isEmpty() &&
											BEMPX_GetInteger( lDBID_DHWSys_HeaterMult+iEqp, lEqpCnt ,        0, -1, iDHWSysIdx ) && lEqpCnt > 0)
									{	laDHWHtrTypIdx.push_back( iEqp+1 );
										laDHWHtrCntIdx.push_back( lEqpCnt );
										saDHWHtrName.push_back(   (const char*) sEqpName.toLocal8Bit().constData() );
								}	}
						// SAC 10/14/14 - replaced below w/ above that causes only 1 DHWSysRpt for 1-N Count of this DHWHeater within this row of the DHWSys heater assignments
						//				for (iCnt=0; iCnt < lEqpCnt; iCnt++)
						//				{	laDHWHtrTypIdx.push_back( iEqp+1 );
						//					laDHWHtrCntIdx.push_back( iCnt+1 );
						//					saDHWHtrName.push_back(   (const char*) sEqpName );
						//		}		}
							int iNumDHWRptObjsToCreate = laDHWHtrTypIdx.size();

						// CREATE DHWSysRpt objects
							for (iEqp=0; (sErrMsg.isEmpty() && iEqp < iNumDHWRptObjsToCreate); iEqp++)
							{	sDHWSysRptName = QString( "%1 DHWSysRpt %2/%3" ).arg( sSysName, QString::number( iEqp+1 ), QString::number( iNumDHWRptObjsToCreate ) );
								pDHWSysRptObj = BEMPX_CreateObject( iCID_DHWSysRpt, sDHWSysRptName.toLocal8Bit().constData(), pSysObj, BEMO_User, FALSE );
								if (pDHWSysRptObj == NULL || pDHWSysRptObj->getClass() == NULL)
									sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to create DHWSysRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sDHWSysRptName );
								else
								{	iDRIdx = BEMPX_GetObjectIndex( pDHWSysRptObj->getClass(), pDHWSysRptObj );
									if (iDRIdx < 0)
										sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to access index of DHWSysRpt object '%1'" ).arg( sDHWSysRptName );
									else
									{	// set DHW heater data
										if (iEqp < (int) laDHWHtrTypIdx.size())
										{	if (BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterRef, BEMP_Str, (void*) ((const char*) saDHWHtrName[iEqp].c_str()), BEMO_User, iDRIdx ) < 0 ||
												 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterIdx, BEMP_Int, (void*)             &laDHWHtrTypIdx[iEqp]         , BEMO_User, iDRIdx ) < 0 ||
												 BEMPX_SetBEMData( lDBID_DHWSysRpt_DHWHeaterCnt, BEMP_Int, (void*)             &laDHWHtrCntIdx[iEqp]         , BEMO_User, iDRIdx ) < 0 )
									// note: NOT setting DHWSysRpt:DHWSysIdx for single family models
												sErrMsg = QString( "CreateDHWRptObjects Error:  Unable to set %1 equip data of DHWSysRpt object '%2'" ).arg( "DHW", sDHWSysRptName );
										}
										if (sErrMsg.isEmpty())
											iNumObjsCreated++;
							}	}	}
						}	// else (system object pointer is valid)
					}	// end of if (system requires generation of child DHWSysRpt objects)
				}	// end of for (each DHWSys object in model)
			}	// else (no DBID errors)
		}	// else (single family)
	}	// else (no error retrieving Proj:IsMultiFamily)

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}

	return iNumObjsCreated;
}


int CreateIAQRptObjects( QString& sErrMsg, ExpEvalStruct* /*pEval*/, ExpError* error )		// SAC 3/26/14
{	int iNumObjsCreated = 0;
	long lIsMultiFamily;
	if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:IsMultiFamily" ), lIsMultiFamily ))
		sErrMsg = QString( "CreateIAQRptObjects Error:  unable to retrieve value for %1" ).arg( "Proj:IsMultiFamily" );
	else
	{	int iNumErrors = 0, iError;		QString sTmp, sIAQRptName;
		int iCID_Proj       = GetObjectID_LogError( "Proj",       iNumErrors, sTmp );
		int iCID_IAQVentRpt = GetObjectID_LogError( "IAQVentRpt", iNumErrors, sTmp );

		if (iNumErrors > 0)
		{	if (iNumErrors > 1)
				sErrMsg = QString( "Error initializing CreateIAQRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
			else
				sErrMsg = QString( "Error initializing CreateIAQRptObjects database ID %1" ).arg( sTmp );
		}
		else if (lIsMultiFamily > 0)
	// SAC 6/30/14 - added separate path for creating MFam IAQRpt objects
		{	int iCID_DwellUnit     = GetObjectID_LogError( "DwellUnit",     iNumErrors, sTmp );
			int iCID_DwellUnitType = GetObjectID_LogError( "DwellUnitType", iNumErrors, sTmp );
			int iCID_Zone          = GetObjectID_LogError( "Zone",          iNumErrors, sTmp );

			long lDBID_DU_Name             = GetPropertyDBID_LogError( "DwellUnit", "Name",             iCID_DwellUnit, iNumErrors, sTmp );
			long lDBID_DU_Count            = GetPropertyDBID_LogError( "DwellUnit", "Count",            iCID_DwellUnit, iNumErrors, sTmp );		// BEMP_Int,  1,  1,  0, "",   0,  0,             1025, "Dwelling unit count" 
			long lDBID_DU_DwellUnitTypeRef = GetPropertyDBID_LogError( "DwellUnit", "DwellUnitTypeRef", iCID_DwellUnit, iNumErrors, sTmp );		// BEMP_Obj,  1,  1,  0, "",   0,  1, "DwellUnitType", 0, "",  1080, "DwellUnitType object" 

			long lDBID_DUT_Name            = GetPropertyDBID_LogError( "DwellUnitType", "Name",           iCID_DwellUnitType, iNumErrors, sTmp );
			long lDBID_DUT_IAQOption       = GetPropertyDBID_LogError( "DwellUnitType", "IAQOption",      iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Sym, 1,  1,  0, "",   0,  0,             8005, "" 
			long lDBID_DUT_IAQNumFanRefs   = GetPropertyDBID_LogError( "DwellUnitType", "IAQNumFanRefs",  iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int, 1,  1,  0, "",   0,  0,             1080, "number of valid IAQ fan assignments" 
			long lDBID_DUT_IAQFanRef       = GetPropertyDBID_LogError( "DwellUnitType", "IAQFanRef",      iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Obj, 4,  1,  0, "",   0,  1, "IAQFan",   1080, "IAQ fan object" 
			long lDBID_DUT_IAQFanCnt       = GetPropertyDBID_LogError( "DwellUnitType", "IAQFanCnt",      iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int, 4,  1,  0, "",   0,  0,             1080, "IAQ fan count" 
		//	long lDBID_DUT_UnitTypesToDisplay = GetPropertyDBID_LogError( "DwellUnitType", "UnitTypesToDisplay", iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int,  1,  0,  0, "",   0,  0,             1025, "Number of dwelling unit types to display in UI" 
		//	long lDBID_DUT_UnitInputValid     = GetPropertyDBID_LogError( "DwellUnitType", "UnitInputValid",     iCID_DwellUnitType, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             3008, "boolean (0/1) indicating valid inputs for each dwelling unit type" 

		//	long lDBID_IAQVentRpt_IAQVentName      = GetPropertyDBID_LogError( "IAQVentRpt", "IAQVentName",      iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Str,  1,  0,  0, "",   0,  0,                 1003, "name of IAQVentRpt instance with unique IAQFan properties by dwelling unit"   
			long lDBID_IAQVentRpt_DwellUnitRef     = GetPropertyDBID_LogError( "IAQVentRpt", "DwellUnitRef",     iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",   0,  1, "DwellUnit",    1003, "dwelling unit served by IAQVent System (only for multifamily projects)"        
			long lDBID_IAQVentRpt_DwellUnitTypeRef = GetPropertyDBID_LogError( "IAQVentRpt", "DwellUnitTypeRef", iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",   0,  1, "DwellUnitRef", 1003, "dwelling unit type served by IAQVent System (only for multifamily projects)"   
		//	long lDBID_IAQVentRpt_DwellingUnitIdx  = GetPropertyDBID_LogError( "IAQVentRpt", "DwellingUnitIdx",  iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,                 1003, "1-based index of dwelling unit served by IAQVent System (or 0 for single family homes)"   
			long lDBID_IAQVentRpt_DwellingUnitCnt  = GetPropertyDBID_LogError( "IAQVentRpt", "DwellingUnitCnt",  iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,                 1003, "1-based index of dwelling unit count served by IAQVent System (or 0 for single family homes)"   
		//	long lDBID_IAQVentRpt_IAQOption        = GetPropertyDBID_LogError( "IAQVentRpt", "IAQOption",        iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Str,  1,  0,  0, "",   0,  0,                 1003, "IAQ ventilation option"   
			long lDBID_IAQVentRpt_IAQFanRef        = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanRef",        iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",   0,  1, "IAQFan",       8004, "IAQ Fan object for this report record"    
			long lDBID_IAQVentRpt_IAQFanIdx        = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanIdx",        iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,                 8004, "1-based index of this IAQ fan associated w/ the referencing dwelling unit" 
			long lDBID_IAQVentRpt_IAQFanCnt   	   = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanCnt",        iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,                 8004, "1-based index of the IAQ fan count associated w/ the referencing dwelling unit" 

			if (iNumErrors > 0)
			{	if (iNumErrors > 1)
					sErrMsg = QString( "Error initializing CreateIAQRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
				else
					sErrMsg = QString( "Error initializing CreateIAQRptObjects database ID %1" ).arg( sTmp );
			}
			else
			{	long lIAQOption, lDUT_IAQNumFanRefs, lDUT_IAQFanCnt, lDU_Count;		QString sZnName, sDUName, sDUTName, sIAQVentRptName;
				BEMObject *pDUTObj, *pIAQFanObj, *pIAQVentRptObj;
				int iNumZones      = BEMPX_GetNumObjects( iCID_Zone      );
				//int iNumDwellUnits = BEMPX_GetNumObjects( iCID_DwellUnit );
				for (int iZnIdx=0; (sErrMsg.isEmpty() && iZnIdx < iNumZones); iZnIdx++)
				{	//VERIFY( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_Zone ), sZnName, FALSE, 0, -1, iZnIdx ) && !sZnName.isEmpty() );
					int iNumDUChildren = (int) BEMPX_GetNumChildren( iCID_Zone, iZnIdx, BEMO_User, iCID_DwellUnit /*, iBEMProcIdx=-1*/ );
					if (iNumDUChildren < 1)
						sErrMsg = QString( "CreateIAQRptObjects Error:  No DwellUnit children found for Zone '%1'" ).arg( sZnName );
					else
					{	long lDUCount;
						for (int i1DUChld=1; (sErrMsg.isEmpty() && i1DUChld <= iNumDUChildren); i1DUChld++)
						{	BEM_ObjType otDU;
							int iDUIdx = BEMPX_GetChildObjectIndex( iCID_Zone, iCID_DwellUnit, iError, otDU, i1DUChld, iZnIdx /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );
							if (iDUIdx < 0)
								sErrMsg = QString( "CreateIAQRptObjects Error encountered retrieving object index of DwellUnit child #%1 of Zone '%2'" ).arg( QString::number( i1DUChld ), sZnName );
							else
							{	BEMPX_GetString( lDBID_DU_Name, sDUName, FALSE, 0, -1, iDUIdx );		assert( !sDUName.isEmpty() );
								if (!BEMPX_GetObject( lDBID_DU_DwellUnitTypeRef, pDUTObj, -1, iDUIdx /*, int iObjType=BEMO_User, int iBEMProcIdx=-1*/ ) || pDUTObj==NULL || pDUTObj->getClass()==NULL)
									sErrMsg = QString( "Error encountered retrieving DwellUnitTypeRef of DwellUnit '%1'" ).arg( sDUName );
								else if (!BEMPX_GetInteger( lDBID_DU_Count, lDUCount, 0, -1, iDUIdx ) || lDUCount < 1)
								{	// IGNORE invalid DwellUnit:Count ???
								}
								else
								{	int iDUTIdx = BEMPX_GetObjectIndex( pDUTObj->getClass(), pDUTObj /*, int iBEMProcIdx=-1*/ );			assert( iDUTIdx >= 0 );
									if (iDUTIdx < 0)
										sErrMsg = QString( "CreateIAQRptObjects Error encountered retrieving object index of DwellUnitTypeRef referenced by DwellUnit '%1'" ).arg( sDUName );
									else
									{	BEMPX_GetString( lDBID_DUT_Name, sDUTName, FALSE, 0, -1, iDUTIdx );		assert( !sDUTName.isEmpty() );
										BEMPX_GetInteger( lDBID_DUT_IAQOption, lIAQOption, 0, -1, iDUTIdx );			assert( lIAQOption == 1 || lIAQOption == 2 );
																// IAQOption ->	1,	"Default Minimum IAQ Fan"   //   2,	"Specify Individual IAQ Fans"   //   3,	"CFI (Central Fan Integrated) IAQ"
										if (lIAQOption == 1 || lIAQOption == 2)
										{	for (long iCnt=1; (sErrMsg.isEmpty() && iCnt <= lDUCount); iCnt++)
											{	if (lIAQOption == 1)	// "Default Minimum IAQ Fan"
												{	sIAQVentRptName = QString( "%1 %2/%3" ).arg( sDUName, QString::number( iCnt ), QString::number( lDUCount ) );
													pIAQVentRptObj = BEMPX_CreateObject( iCID_IAQVentRpt, sIAQVentRptName.toLocal8Bit().constData(), NULL, BEMO_User, FALSE );
													if (pIAQVentRptObj == NULL || pIAQVentRptObj->getClass() == NULL)
														sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to create IAQVentRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sIAQVentRptName );
													else
													{	int iDRIdx = BEMPX_GetObjectIndex( pIAQVentRptObj->getClass(), pIAQVentRptObj );
														if (iDRIdx < 0)
															sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to access index of IAQVentRpt object '%1'" ).arg( sIAQVentRptName );
														else
														{	// set IAQ vent report data
												//			BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitIdx , BEMP_Int, (void*) &lDwellingUnitIdx       , BEMO_User, iDRIdx );
															BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellUnitRef    , BEMP_Str, (void*) sDUName.toLocal8Bit().constData() , BEMO_User, iDRIdx );
															BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellUnitTypeRef, BEMP_Str, (void*) sDUTName.toLocal8Bit().constData(), BEMO_User, iDRIdx );
															BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitCnt , BEMP_Int, (void*) &iCnt                             , BEMO_User, iDRIdx );
															iNumObjsCreated++;
													}	}
												}
												else		// IAQOption = "Specify Individual IAQ Fans"
												{	long lIdx, lNumFanRefs, lMaxFanCnt;		QString sFanName;
													BEMPX_GetInteger( lDBID_DUT_IAQNumFanRefs, lNumFanRefs, 0, -1, iDUTIdx );			assert( lNumFanRefs >= 0 && lNumFanRefs < 5 );
													for (lIdx=1; (sErrMsg.isEmpty() && lIdx <= lNumFanRefs); lIdx++)
													{	if (	BEMPX_GetString(  lDBID_DUT_IAQFanRef + lIdx-1, sFanName, FALSE, 0, -1, iDUTIdx ) && !sFanName.isEmpty() &&
																BEMPX_GetInteger( lDBID_DUT_IAQFanCnt + lIdx-1, lMaxFanCnt,      0, -1, iDUTIdx ) && lMaxFanCnt > 0 )
														{	for (long lFanCnt=1; (sErrMsg.isEmpty() && lFanCnt <= lMaxFanCnt); lFanCnt++)
															{	sIAQVentRptName = QString( "%1 %2/%3 fan %4/%5 cnt %6/%7" ).arg( sDUName, QString::number( iCnt ), QString::number( lDUCount ), QString::number( lIdx ), QString::number( lNumFanRefs ), QString::number( lFanCnt ), QString::number( lMaxFanCnt ) );
																pIAQVentRptObj = BEMPX_CreateObject( iCID_IAQVentRpt, sIAQVentRptName.toLocal8Bit().constData(), NULL, BEMO_User, FALSE );
																if (pIAQVentRptObj == NULL || pIAQVentRptObj->getClass() == NULL)
																	sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to create IAQVentRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sIAQVentRptName );
																else
																{	int iDRIdx = BEMPX_GetObjectIndex( pIAQVentRptObj->getClass(), pIAQVentRptObj );
																	if (iDRIdx < 0)
																		sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to access index of IAQVentRpt object '%1'" ).arg( sIAQVentRptName );
																	else
																	{	// set IAQ vent report data
													//					BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitIdx , BEMP_Int, (void*) &lDwellingUnitIdx       , BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellUnitRef    , BEMP_Str, (void*) sDUName.toLocal8Bit().constData() , BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellUnitTypeRef, BEMP_Str, (void*) sDUTName.toLocal8Bit().constData(), BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitCnt , BEMP_Int, (void*) &iCnt                             , BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanRef       , BEMP_Str, (void*) sFanName.toLocal8Bit().constData(), BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanIdx       , BEMP_Int, (void*) &lIdx                             , BEMO_User, iDRIdx );
																		BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanCnt       , BEMP_Int, (void*) &lFanCnt                          , BEMO_User, iDRIdx );
																		iNumObjsCreated++;
																}	}
														}	}
												}	}
											}
										}
				}	}	}	}	}	}
		}	}
		else
		{	long lDBID_Proj_UnitIAQOption      = GetPropertyDBID_LogError( "Proj", "UnitIAQOption",      iCID_Proj, iNumErrors, sTmp );		// BEMP_Sym, 16,  1,  0, "",   0,  0,             8005, "" 
			long lDBID_Proj_UnitIAQNumFanRefs  = GetPropertyDBID_LogError( "Proj", "UnitIAQNumFanRefs",  iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1080, "number of valid IAQ fan assignments" 
			long lDBID_Proj_UnitIAQFan1        = GetPropertyDBID_LogError( "Proj", "UnitIAQFan1",        iCID_Proj, iNumErrors, sTmp );		// BEMP_Obj, 16,  1,  0, "",   0,  1, "IAQFan",   1080, "IAQ fan object" 
			long lDBID_Proj_UnitIAQFan2        = GetPropertyDBID_LogError( "Proj", "UnitIAQFan2",        iCID_Proj, iNumErrors, sTmp );		// BEMP_Obj, 16,  1,  0, "",   0,  1, "IAQFan",   1080, "IAQ fan object" 
			long lDBID_Proj_UnitIAQFan3        = GetPropertyDBID_LogError( "Proj", "UnitIAQFan3",        iCID_Proj, iNumErrors, sTmp );		// BEMP_Obj, 16,  1,  0, "",   0,  1, "IAQFan",   1080, "IAQ fan object" 
			long lDBID_Proj_UnitIAQFan4        = GetPropertyDBID_LogError( "Proj", "UnitIAQFan4",        iCID_Proj, iNumErrors, sTmp );		// BEMP_Obj, 16,  1,  0, "",   0,  1, "IAQFan",   1080, "IAQ fan object" 
			long lDBID_Proj_UnitIAQFanCnt1     = GetPropertyDBID_LogError( "Proj", "UnitIAQFanCnt1",     iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1080, "IAQ fan count" 
			long lDBID_Proj_UnitIAQFanCnt2     = GetPropertyDBID_LogError( "Proj", "UnitIAQFanCnt2",     iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1080, "IAQ fan count" 
			long lDBID_Proj_UnitIAQFanCnt3     = GetPropertyDBID_LogError( "Proj", "UnitIAQFanCnt3",     iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1080, "IAQ fan count" 
			long lDBID_Proj_UnitIAQFanCnt4     = GetPropertyDBID_LogError( "Proj", "UnitIAQFanCnt4",     iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1080, "IAQ fan count" 
		//	long lDBID_Proj_UnitTypesToDisplay = GetPropertyDBID_LogError( "Proj", "UnitTypesToDisplay", iCID_Proj, iNumErrors, sTmp );		// BEMP_Int,  1,  0,  0, "",   0,  0,             1025, "Number of dwelling unit types to display in UI" 
		//	long lDBID_Proj_UnitInputValid     = GetPropertyDBID_LogError( "Proj", "UnitInputValid",     iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             3008, "boolean (0/1) indicating valid inputs for each dwelling unit type" 
			long lDBID_Proj_UnitName           = GetPropertyDBID_LogError( "Proj", "UnitName",           iCID_Proj, iNumErrors, sTmp );		// BEMP_Str, 16,  1,  0, "",   0,  0,             1025, "Dwelling unit name" 
		//	long lDBID_Proj_UnitCount          = GetPropertyDBID_LogError( "Proj", "UnitCount",          iCID_Proj, iNumErrors, sTmp );		// BEMP_Int, 16,  1,  0, "",   0,  0,             1025, "Dwelling unit count" 

		//	long lDBID_IAQVentRpt_IAQVentName     = GetPropertyDBID_LogError( "IAQVentRpt", "IAQVentName",     iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Str,  1,  0,  0, "",   0,  0,             1003, "name of IAQVentRpt instance with unique IAQFan properties by dwelling unit"   
			long lDBID_IAQVentRpt_DwellingUnitIdx = GetPropertyDBID_LogError( "IAQVentRpt", "DwellingUnitIdx", iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,             1003, "1-based index of dwelling unit served by IAQVent System (or 0 for single family homes)"   
			long lDBID_IAQVentRpt_DwellingUnitCnt = GetPropertyDBID_LogError( "IAQVentRpt", "DwellingUnitCnt", iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,             1003, "1-based index of dwelling unit count served by IAQVent System (or 0 for single family homes)"   
		//	long lDBID_IAQVentRpt_IAQOption       = GetPropertyDBID_LogError( "IAQVentRpt", "IAQOption",       iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Str,  1,  0,  0, "",   0,  0,             1003, "IAQ ventilation option"   
			long lDBID_IAQVentRpt_IAQFanRef       = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanRef",       iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Obj,  1,  0,  0, "",   0,  1, "IAQFan",   8004, "IAQ Fan object for this report record"    
			long lDBID_IAQVentRpt_IAQFanIdx       = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanIdx",       iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,             8004, "1-based index of this IAQ fan associated w/ the referencing dwelling unit" 
			long lDBID_IAQVentRpt_IAQFanCnt   	  = GetPropertyDBID_LogError( "IAQVentRpt", "IAQFanCnt",       iCID_IAQVentRpt, iNumErrors, sTmp );	// BEMP_Int,  1,  0,  0, "",   0,  0,             8004, "1-based index of the IAQ fan count associated w/ the referencing dwelling unit" 

			if (iNumErrors > 0)
			{	if (iNumErrors > 1)
					sErrMsg = QString( "Error initializing CreateIAQRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
				else
					sErrMsg = QString( "Error initializing CreateIAQRptObjects database ID %1" ).arg( sTmp );
			}
			else
			{	long lUnitIAQOption, lUnitIAQNumFanRefs, lUnitIAQFanCnt, lMaxDUnitLp = 1, lUnitInputValid, lUnitCount;		QString sDUnitName, sIAQVentRptName;
				BEMObject *pIAQFanObj, *pIAQVentRptObj;
		//		if (lIsMultiFamily > 0)
		//			BEMPX_GetInteger( lDBID_Proj_UnitTypesToDisplay, lMaxDUnitLp );
				for (int iDUnit=0; (sErrMsg.isEmpty() && iDUnit < lMaxDUnitLp); iDUnit++)
				{	bool bProcessThisDUnit = true;		lUnitCount = 1;
		//			if (lIsMultiFamily > 0)
		//				bProcessThisDUnit = (BEMPX_GetInteger( lDBID_Proj_UnitInputValid+iDUnit, lUnitInputValid ) && lUnitInputValid > 0 &&
		//											BEMPX_GetInteger( lDBID_Proj_UnitCount     +iDUnit, lUnitCount      ) && lUnitCount > 0 );
					if (bProcessThisDUnit)
					{	long lDwellingUnitIdx = iDUnit;	// + (lIsMultiFamily > 0 ? 1 : 0);
						BEMPX_GetString(  lDBID_Proj_UnitName     +iDUnit, sTmp );
						BEMPX_GetInteger( lDBID_Proj_UnitIAQOption+iDUnit, lUnitIAQOption );			assert( lUnitIAQOption == 1 || lUnitIAQOption == 2 );
												// Proj:UnitIAQOption ->	1,	"Default Minimum IAQ Fan"   //   2,	"Specify Individual IAQ Fans"   //   3,	"CFI (Central Fan Integrated) IAQ"
						if (lUnitIAQOption == 1 || lUnitIAQOption == 2)
						{	sDUnitName = "SFam";
		//					if (lIsMultiFamily == 0)
		//						sDUnitName = "SFam";
		//					else if (!sTmp.isEmpty())
		//						sDUnitName = QString( "%1-%2", QString::number( iDUnit+1 ), sTmp );
		//					else
		//						sDUnitName = QString( "%1-MFam", QString::number( iDUnit+1 ) );
							for (int iUnitCnt=0; (sErrMsg.isEmpty() && iUnitCnt < lUnitCount); iUnitCnt++)
							{	long lDwellingUnitCnt = iUnitCnt;	// + (lIsMultiFamily > 0 ? 1 : 0);
								if (lUnitIAQOption == 1)	// "Default Minimum IAQ Fan"
		//						{	if (lIsMultiFamily > 0)
		//								sIAQVentRptName = QString( "%1 IAQVentRpt %2", sDUnitName, QString::number( iUnitCnt+1 ) );
		//							else
		//								sIAQVentRptName = QString( "%1 IAQVentRpt", sDUnitName );
								{	sIAQVentRptName = QString( "%1 IAQVentRpt" ).arg( sDUnitName );
									pIAQVentRptObj = BEMPX_CreateObject( iCID_IAQVentRpt, sIAQVentRptName.toLocal8Bit().constData(), NULL, BEMO_User, FALSE );
									if (pIAQVentRptObj == NULL || pIAQVentRptObj->getClass() == NULL)
										sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to create IAQVentRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sIAQVentRptName );
									else
									{	int iDRIdx = BEMPX_GetObjectIndex( pIAQVentRptObj->getClass(), pIAQVentRptObj );
										if (iDRIdx < 0)
											sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to access index of IAQVentRpt object '%1'" ).arg( sIAQVentRptName );
										else
										{	// set IAQ vent report data
											BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitIdx, BEMP_Int, (void*) &lDwellingUnitIdx , BEMO_User, iDRIdx );
											BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitCnt, BEMP_Int, (void*) &lDwellingUnitCnt , BEMO_User, iDRIdx );
											iNumObjsCreated++;
									}	}
								}
								else		// UnitIAQOption = "Specify Individual IAQ Fans"
								{	long lUnitIdx, lNumFanRefs, lMaxFanCnt;		QString sFanName;
									BEMPX_GetInteger( lDBID_Proj_UnitIAQNumFanRefs +iDUnit, lNumFanRefs );			assert( lNumFanRefs >= 0 && lNumFanRefs < 5 );
									for (lUnitIdx=1; (sErrMsg.isEmpty() && lUnitIdx <= lNumFanRefs); lUnitIdx++)
									{	long lDBID_IAQFan=0, lDBID_IAQFanCnt=0;
										switch (lUnitIdx)
										{	case  1 :	lDBID_IAQFan = lDBID_Proj_UnitIAQFan1;		lDBID_IAQFanCnt = lDBID_Proj_UnitIAQFanCnt1;		break;
											case  2 :	lDBID_IAQFan = lDBID_Proj_UnitIAQFan2;		lDBID_IAQFanCnt = lDBID_Proj_UnitIAQFanCnt2;		break;
											case  3 :	lDBID_IAQFan = lDBID_Proj_UnitIAQFan3;		lDBID_IAQFanCnt = lDBID_Proj_UnitIAQFanCnt3;		break;
											case  4 :	lDBID_IAQFan = lDBID_Proj_UnitIAQFan4;		lDBID_IAQFanCnt = lDBID_Proj_UnitIAQFanCnt4;		break;
										}
										if (	lDBID_IAQFan > 0 && lDBID_IAQFanCnt > 0 &&
												BEMPX_GetString(  lDBID_IAQFan    +iDUnit, sFanName   ) && !sFanName.isEmpty() &&
												BEMPX_GetInteger( lDBID_IAQFanCnt +iDUnit, lMaxFanCnt ) && lMaxFanCnt > 0 )
										{	for (long lFanCnt=1; (sErrMsg.isEmpty() && lFanCnt <= lMaxFanCnt); lFanCnt++)
		//									{	if (lIsMultiFamily > 0)
		//											sIAQVentRptName = QString( "%1 IAQVentRpt %2-%3-%4" ).arg( sDUnitName, QString::number( iUnitCnt+1 ), QString::number( lUnitIdx ), QString::number( lFanCnt ) );
		//										else
		//											sIAQVentRptName = QString( "%1 IAQVentRpt %2-%3" ).arg( sDUnitName, QString::number( lUnitIdx ), QString::number( lFanCnt ) );
											{	sIAQVentRptName = QString( "%1 IAQVentRpt %2-%3" ).arg( sDUnitName, QString::number( lUnitIdx ), QString::number( lFanCnt ) );
												pIAQVentRptObj = BEMPX_CreateObject( iCID_IAQVentRpt, sIAQVentRptName.toLocal8Bit().constData(), NULL, BEMO_User, FALSE );
												if (pIAQVentRptObj == NULL || pIAQVentRptObj->getClass() == NULL)
													sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to create IAQVentRpt object #%1 '%2'" ).arg( QString::number( iNumObjsCreated+1 ), sIAQVentRptName );
												else
												{	int iDRIdx = BEMPX_GetObjectIndex( pIAQVentRptObj->getClass(), pIAQVentRptObj );
													if (iDRIdx < 0)
														sErrMsg = QString( "CreateIAQRptObjects Error:  Unable to access index of IAQVentRpt object '%1'" ).arg( sIAQVentRptName );
													else
													{	// set IAQ vent report data
														BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitIdx, BEMP_Int, (void*) &lDwellingUnitIdx                 , BEMO_User, iDRIdx );
														BEMPX_SetBEMData( lDBID_IAQVentRpt_DwellingUnitCnt, BEMP_Int, (void*) &lDwellingUnitCnt                 , BEMO_User, iDRIdx );
														BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanRef      , BEMP_Str, (void*) sFanName.toLocal8Bit().constData(), BEMO_User, iDRIdx );
														BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanIdx      , BEMP_Int, (void*) &lUnitIdx                         , BEMO_User, iDRIdx );
														BEMPX_SetBEMData( lDBID_IAQVentRpt_IAQFanCnt      , BEMP_Int, (void*) &lFanCnt                          , BEMO_User, iDRIdx );
														iNumObjsCreated++;
												}	}
										}	}
								}	}
						}	}
				}	}
	}	}	}

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}

	return iNumObjsCreated;
}

//=============================================================================
// SAC 6/27/14 - routine to create HVACSys objects for simulation of HVACSys objects serving DwellUnits
int CreateDwellUnitHVACSysObjects( QString& sErrMsg, ExpEvalStruct* /*pEval*/, ExpError* error )
{	int iNumObjsCreated = 0;
	int iNumErrors = 0;			QString sTmp, sZnName, sDUName, sDUTName;
	int iCID_DwellUnit = GetObjectID_LogError( "DwellUnit", iNumErrors, sTmp );
	int iCID_Zone		 = GetObjectID_LogError( "Zone",      iNumErrors, sTmp );
	long lNumDwellUnits = BEMPX_GetNumObjects( iCID_DwellUnit );
	long lNumZones      = BEMPX_GetNumObjects( iCID_Zone      );
	if (lNumDwellUnits > 0 && lNumZones > 0)
	{	int iCID_DwellUnitType	= GetObjectID_LogError( "DwellUnitType", iNumErrors, sTmp );
		int iCID_HVACSys			= GetObjectID_LogError( "HVACSys", iNumErrors, sTmp );
		int iCID_HVACFan			= GetObjectID_LogError( "HVACFan", iNumErrors, sTmp );

		long lDBID_Zone_HVACSysStatus = GetPropertyDBID_LogError( "Zone", "HVACSysStatus", iCID_Zone, iNumErrors, sTmp );		// BEMP_Sym,  "Status of HVAC System - New, Altered or Existing" 
		long lDBID_Zone_HVACSystem    = GetPropertyDBID_LogError( "Zone", "HVACSystem",    iCID_Zone, iNumErrors, sTmp );		// "HVACSys",  3, "Status",   "New HVAC system assignment"     
		long lDBID_Zone_AltHVACSystem = GetPropertyDBID_LogError( "Zone", "AltHVACSystem", iCID_Zone, iNumErrors, sTmp );		// "HVACSys",  2, "Status",   "Altered HVAC system assignment" 
		long lDBID_Zone_exHVACSystem  = GetPropertyDBID_LogError( "Zone", "exHVACSystem",  iCID_Zone, iNumErrors, sTmp );		// "HVACSys",  1, "Status",   "Existing HVAC system assignment"

		long lDBID_DwellUnit_DwellUnitTypeRef = GetPropertyDBID_LogError( "DwellUnit", "DwellUnitTypeRef", iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DwellUnit_Count            = GetPropertyDBID_LogError( "DwellUnit", "Count"           , iCID_DwellUnit, iNumErrors, sTmp );

		long lDBID_DwellUnitType_HVACSysType         = GetPropertyDBID_LogError( "DwellUnitType", "HVACSysType"        , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_NumHeatEquipTypes   = GetPropertyDBID_LogError( "DwellUnitType", "NumHeatEquipTypes"  , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HVACHeatRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACHeatRef"        , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HeatEquipCount      = GetPropertyDBID_LogError( "DwellUnitType", "HeatEquipCount"     , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_NumCoolEquipTypes   = GetPropertyDBID_LogError( "DwellUnitType", "NumCoolEquipTypes"  , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HVACCoolRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACCoolRef"        , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_CoolEquipCount      = GetPropertyDBID_LogError( "DwellUnitType", "CoolEquipCount"     , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_NumHtPumpEquipTypes = GetPropertyDBID_LogError( "DwellUnitType", "NumHtPumpEquipTypes", iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HVACHtPumpRef       = GetPropertyDBID_LogError( "DwellUnitType", "HVACHtPumpRef"      , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HtPumpEquipCount    = GetPropertyDBID_LogError( "DwellUnitType", "HtPumpEquipCount"   , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HVACFanRef          = GetPropertyDBID_LogError( "DwellUnitType", "HVACFanRef"         , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_HVACDistRef         = GetPropertyDBID_LogError( "DwellUnitType", "HVACDistRef"        , iCID_DwellUnitType, iNumErrors, sTmp );
		long lDBID_DwellUnitType_PreventCoolingSim   = GetPropertyDBID_LogError( "DwellUnitType", "PreventCoolingSim"  , iCID_DwellUnitType, iNumErrors, sTmp );		// SAC 8/5/15

		long lDBID_HVACSys_Type                 = GetPropertyDBID_LogError( "HVACSys", "Type"                , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_Status               = GetPropertyDBID_LogError( "HVACSys", "Status"              , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_NumHeatSystemTypes   = GetPropertyDBID_LogError( "HVACSys", "NumHeatSystemTypes"  , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_HeatSystemCount      = GetPropertyDBID_LogError( "HVACSys", "HeatSystemCount"     , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_HeatSystem           = GetPropertyDBID_LogError( "HVACSys", "HeatSystem"          , iCID_HVACSys, iNumErrors, sTmp );
//		long lDBID_HVACSys_AutoSizeHeatInp      = GetPropertyDBID_LogError( "HVACSys", "AutoSizeHeatInp"     , iCID_HVACSys, iNumErrors, sTmp );
//		long lDBID_HVACSys_HeatDucted           = GetPropertyDBID_LogError( "HVACSys", "HeatDucted"          , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_NumCoolSystemTypes   = GetPropertyDBID_LogError( "HVACSys", "NumCoolSystemTypes"  , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_CoolSystemCount      = GetPropertyDBID_LogError( "HVACSys", "CoolSystemCount"     , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_CoolSystem           = GetPropertyDBID_LogError( "HVACSys", "CoolSystem"          , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_PreventCoolingSim    = GetPropertyDBID_LogError( "HVACSys", "PreventCoolingSim"   , iCID_HVACSys, iNumErrors, sTmp );		// SAC 8/5/15
//		long lDBID_HVACSys_AutoSizeCoolInp      = GetPropertyDBID_LogError( "HVACSys", "AutoSizeCoolInp"     , iCID_HVACSys, iNumErrors, sTmp );
//		long lDBID_HVACSys_CoolDucted           = GetPropertyDBID_LogError( "HVACSys", "CoolDucted"          , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_NumHtPumpSystemTypes = GetPropertyDBID_LogError( "HVACSys", "NumHtPumpSystemTypes", iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_HtPumpSystemCount    = GetPropertyDBID_LogError( "HVACSys", "HtPumpSystemCount"   , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_HtPumpSystem         = GetPropertyDBID_LogError( "HVACSys", "HtPumpSystem"        , iCID_HVACSys, iNumErrors, sTmp );
//		long lDBID_HVACSys_HtPumpDucted         = GetPropertyDBID_LogError( "HVACSys", "HtPumpDucted"        , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_DistribSystem        = GetPropertyDBID_LogError( "HVACSys", "DistribSystem"       , iCID_HVACSys, iNumErrors, sTmp );
		long lDBID_HVACSys_Fan                  = GetPropertyDBID_LogError( "HVACSys", "Fan"                 , iCID_HVACSys, iNumErrors, sTmp );

		long lDBID_HVACFan_Type                 = GetPropertyDBID_LogError( "HVACFan", "Type"                , iCID_HVACFan, iNumErrors, sTmp );		// BEMP_Sym,  1,  0,  0, "",                 0,  0,                        8002, "Fan type"    
		long lDBID_HVACFan_WperCFMCool          = GetPropertyDBID_LogError( "HVACFan", "WperCFMCool"         , iCID_HVACFan, iNumErrors, sTmp );		// BEMP_Flt,  1,  0,  0, "W/CFM",            0,  0,                        8005, "Fan watts per CFM of air flow" 

		if (iNumErrors > 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitHVACSysObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
		else if (iNumErrors == 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitHVACSysObjects database ID %1" ).arg( sTmp );
		else
		{	BEMObject *pDUTObj;		int iError, iDUIdx;		long lZoneHVACSysStatus;
			int iMaxHVACSysHeatRefs   = BEMPX_GetNumPropertyTypeElementsFromDBID( lDBID_HVACSys_HeatSystem   /*, int iBEMProcIdx=-1*/ );
			int iMaxHVACSysCoolRefs   = BEMPX_GetNumPropertyTypeElementsFromDBID( lDBID_HVACSys_CoolSystem   /*, int iBEMProcIdx=-1*/ );
			int iMaxHVACSysHtPumpRefs = BEMPX_GetNumPropertyTypeElementsFromDBID( lDBID_HVACSys_HtPumpSystem /*, int iBEMProcIdx=-1*/ );
			for (int iZnIdx=0; (sErrMsg.isEmpty() && iZnIdx < lNumZones); iZnIdx++)
			{	BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_Zone ), sZnName, FALSE, 0, -1, iZnIdx );		assert( !sZnName.isEmpty() );
		// SAC 8/26/14 - added logic to get Zone:HVACSysStatus, apply that status to HVACSys objects created to serve this Zone, and assign the created HVACSys to the proper assignment property (based on status)
				BEMPX_GetInteger( lDBID_Zone_HVACSysStatus, lZoneHVACSysStatus, 0, -1, iZnIdx );		assert( lZoneHVACSysStatus > 0 );
				int iNumDUChildren = (int) BEMPX_GetNumChildren( iCID_Zone, iZnIdx, BEMO_User, iCID_DwellUnit /*, iBEMProcIdx=-1*/ );
				if (iNumDUChildren < 1)
					sErrMsg = QString( "Error:  No DwellUnit children found for Zone '%1'" ).arg( sZnName );
				else
				{	long lHVACSysType = -1, lHVACSysTypeChk;
					long lEqpNum, lEqpCount, lDUCount, lPreventCoolingSim=0, lTempPreventClSim;	int iEqpIdx, iFanIdx=-1;
					double fFanWperCFM=-1, fThisFanWperCFM=-1;
					BEMObject *pDistObj=NULL, *pThisDistObj=NULL;
					QStringList saHeatNames, saCoolNames;
					std::vector<long> laHeatCount, laCoolCount;
					QString sFan, sFanType, sDistrib, sHVACSysType, sHVACSysTypeChk, sThisFan, sThisFanType, sThisDistName, sFanDUTName, sDistDUTName;
					for (int i1DUChld=1; (sErrMsg.isEmpty() && i1DUChld <= iNumDUChildren); i1DUChld++)
					{	BEM_ObjType otDU;
						int iDUIdx = BEMPX_GetChildObjectIndex( iCID_Zone, iCID_DwellUnit, iError, otDU, i1DUChld, iZnIdx /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );
						if (iDUIdx < 0)
							sErrMsg = QString( "Error encountered retrieving object index of DwellUnit child #%1 of Zone '%2'" ).arg( QString::number( i1DUChld ), sZnName );
						else
						{	BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_DwellUnit ), sDUName, FALSE, 0, -1, iDUIdx );		assert( !sDUName.isEmpty() );
							if (!BEMPX_GetObject( lDBID_DwellUnit_DwellUnitTypeRef, pDUTObj, -1, iDUIdx /*, int iObjType=BEMO_User, int iBEMProcIdx=-1*/ ) || pDUTObj==NULL || pDUTObj->getClass()==NULL)
								sErrMsg = QString( "Error encountered retrieving DwellUnitTypeRef of DwellUnit '%1'" ).arg( sDUName );
							else if (!BEMPX_GetInteger( lDBID_DwellUnit_Count, lDUCount, 0, -1, iDUIdx ) || lDUCount < 1)
							{	// IGNORE invalid DwellUnit:Count ???
							}
							else
							{	int iDUTIdx = BEMPX_GetObjectIndex( pDUTObj->getClass(), pDUTObj /*, int iBEMProcIdx=-1*/ );			assert( iDUTIdx >= 0 );
								if (iDUTIdx < 0)
									sErrMsg = QString( "Error encountered retrieving object index of DwellUnitTypeRef referenced by DwellUnit '%1'" ).arg( sDUName );
								else
								{	BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iCID_DwellUnitType ), sDUTName, FALSE, 0, -1, iDUTIdx );		assert( !sDUTName.isEmpty() );
									if (!BEMPX_GetInteger( lDBID_DwellUnitType_HVACSysType, lHVACSysTypeChk, 0, -1, iDUTIdx ) || lHVACSysTypeChk < 0)
										sErrMsg = QString( "Error encountered retrieving HVAC system type of DwellUnitType '%1'" ).arg( sDUTName );
									else
									{	BEMPX_GetString( lDBID_DwellUnitType_HVACSysType, sHVACSysTypeChk, FALSE, 0, -1, iDUTIdx );		assert( !sHVACSysTypeChk.isEmpty() );
										if (lHVACSysType == -1)
										{	lHVACSysType = lHVACSysTypeChk;
											sHVACSysType = sHVACSysTypeChk;
										}
										if (lHVACSysType != lHVACSysTypeChk)
											sErrMsg = QString( "Error:  All DwellUnit children of zone '%1' must be served by the same type of HVAC equipment (combination of '%2' & '%3' found)." ).arg( sZnName, sHVACSysType, sHVACSysTypeChk );
										else
										{	BEMObject *pEqpObj;		//int iEqpIdx;
											if (lHVACSysType == 2)
											{	// process HEAT PUMP equipment
												if (!BEMPX_GetInteger( lDBID_DwellUnitType_NumHtPumpEquipTypes, lEqpNum, 0, -1, iDUTIdx ))
												{	assert( FALSE );
													lEqpNum = 0;
												}
												for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < lEqpNum); iEqpIdx++)
												{	BEMPX_GetObject(  lDBID_DwellUnitType_HVACHtPumpRef   +iEqpIdx, pEqpObj  ,    -1, iDUTIdx );		assert( (pEqpObj && pEqpObj->getClass()) );
													BEMPX_GetInteger( lDBID_DwellUnitType_HtPumpEquipCount+iEqpIdx, lEqpCount, 0, -1, iDUTIdx );
													if (pEqpObj && pEqpObj->getClass() && lEqpCount > 0)
													{	int iEqpObjIdx = BEMPX_GetObjectIndex( pEqpObj->getClass(), pEqpObj );				assert( iEqpObjIdx >= 0 );
														if (iEqpObjIdx < 0)
														{	assert( FALSE );	// bogus equipment object
														}
														else
														{	int iEqpArrIdx = StringInArray( saHeatNames, pEqpObj->getName() );
															if (iEqpArrIdx < 0)	// not already in the list...
															{	saHeatNames.push_back( pEqpObj->getName() );
																laHeatCount.push_back( (lEqpCount * lDUCount) );
															}
															else	// simply increment count...
																laHeatCount[iEqpArrIdx] += (lEqpCount * lDUCount);
													}	}
													else
													{	assert( FALSE );	// bogus equipment object or count
												}	}
											}
											else
											{	// process Heat/Cool equipment
												if (!BEMPX_GetInteger( lDBID_DwellUnitType_NumHeatEquipTypes, lEqpNum, 0, -1, iDUTIdx ))
												{	assert( FALSE );
													lEqpNum = 0;
												}
												for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < lEqpNum); iEqpIdx++)
												{	BEMPX_GetObject(  lDBID_DwellUnitType_HVACHeatRef   +iEqpIdx, pEqpObj  ,    -1, iDUTIdx );		assert( (pEqpObj && pEqpObj->getClass()) );
													BEMPX_GetInteger( lDBID_DwellUnitType_HeatEquipCount+iEqpIdx, lEqpCount, 0, -1, iDUTIdx );
													if (pEqpObj && pEqpObj->getClass() && lEqpCount > 0)
													{	int iEqpObjIdx = BEMPX_GetObjectIndex( pEqpObj->getClass(), pEqpObj );				assert( iEqpObjIdx >= 0 );
														if (iEqpObjIdx < 0)
														{	assert( FALSE );	// bogus equipment object
														}
														else
														{	int iEqpArrIdx = StringInArray( saHeatNames, pEqpObj->getName() );
															if (iEqpArrIdx < 0)	// not already in the list...
															{	saHeatNames.push_back( pEqpObj->getName() );
																laHeatCount.push_back( (lEqpCount * lDUCount) );
															}
															else	// simply increment count...
																laHeatCount[iEqpArrIdx] += (lEqpCount * lDUCount);
													}	}
													else
													{	assert( FALSE );	// bogus equipment object or count
												}	}
												// cooling equip...
												if (!BEMPX_GetInteger( lDBID_DwellUnitType_NumCoolEquipTypes, lEqpNum, 0, -1, iDUTIdx ))
												{	assert( FALSE );
													lEqpNum = 0;
												}
												for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < lEqpNum); iEqpIdx++)
												{	BEMPX_GetObject(  lDBID_DwellUnitType_HVACCoolRef      +iEqpIdx, pEqpObj           ,    -1, iDUTIdx );		assert( (pEqpObj && pEqpObj->getClass()) );
													BEMPX_GetInteger( lDBID_DwellUnitType_CoolEquipCount   +iEqpIdx, lEqpCount         , 0, -1, iDUTIdx );
													if (pEqpObj && pEqpObj->getClass() && lEqpCount > 0)
													{	int iEqpObjIdx = BEMPX_GetObjectIndex( pEqpObj->getClass(), pEqpObj );				assert( iEqpObjIdx >= 0 );
														if (iEqpObjIdx < 0)
														{	assert( FALSE );	// bogus equipment object
														}
														else
														{	int iEqpArrIdx = StringInArray( saCoolNames, pEqpObj->getName() );
															if (iEqpArrIdx < 0)	// not already in the list...
															{	saCoolNames.push_back( pEqpObj->getName() );
																laCoolCount.push_back( (lEqpCount * lDUCount) );
															}
															else	// simply increment count...
																laCoolCount[iEqpArrIdx] += (lEqpCount * lDUCount);
													}	}
													else
													{	assert( FALSE );	// bogus equipment object or count
												}	}
											// SAC 8/5/15 - added logic to set PreventCoolingSim flag to '1', if set for any DUT of child DUs
												if (lEqpNum > 0 && lPreventCoolingSim < 1 && BEMPX_GetInteger( lDBID_DwellUnitType_PreventCoolingSim, lTempPreventClSim, 0, -1, iDUTIdx ) && lTempPreventClSim > 0)
													lPreventCoolingSim = lTempPreventClSim;
											}

											// Fan - allow different fan assignments, as long as their Types are consistent - simulate least efficient fan
											BEMPX_GetObject( lDBID_DwellUnitType_HVACFanRef, pEqpObj, -1, iDUTIdx );
											sThisFan = ((pEqpObj && !pEqpObj->getName().isEmpty()) ? pEqpObj->getName() : "");
											iFanIdx = (pEqpObj && pEqpObj->getClass()) ? BEMPX_GetObjectIndex( pEqpObj->getClass(), pEqpObj ) : -1;
											if (iFanIdx < 0)
											{	sThisFanType.clear();
												fThisFanWperCFM = -1;
											}
											else
											{	BEMPX_GetString( lDBID_HVACFan_Type, sThisFanType, TRUE, 0, -1, iFanIdx );
												BEMPX_GetFloat( lDBID_HVACFan_WperCFMCool, fThisFanWperCFM, -1, -1, iFanIdx );
											}
											if (i1DUChld == 1 || (!sThisFanType.isEmpty() && sThisFanType.compare( sFanType )==0))
											{	// first fan or fan type checks out
												if (i1DUChld == 1 || fThisFanWperCFM > fFanWperCFM)	// if multiple fans of same type, use the least energy efficient to simulate the zone
												{	sFan			= sThisFan;
													sFanType		= sThisFanType;
													fFanWperCFM	= fThisFanWperCFM;
													sFanDUTName = sDUTName;
											}	}
											else if (sFan.isEmpty() && sThisFan.isEmpty())
											{	// no fan assigned to first or subsequent DUT of DU child - OK
											}
											else if ((!sThisFanType.isEmpty() || !sFanType.isEmpty()) && sThisFanType.compare( sFanType ))
												sErrMsg = QString( "Error creating HVACSys object for Zone '%1':  Inconsistent Fan:Type for Fan '%2' of DwellingUnitType '%3' vs. Fan '%4' of DwellingUnitType '%5'." ).arg(
																			sZnName, sFan, sFanDUTName, sThisFan, sDUTName );

											// Distribution system
											BEMPX_GetObject( lDBID_DwellUnitType_HVACDistRef, pEqpObj, -1, iDUTIdx );
											pThisDistObj  = pEqpObj;
											sThisDistName = ((pEqpObj && !pEqpObj->getName().isEmpty()) ? pEqpObj->getName() : "");
											if (i1DUChld == 1)
											{	sDistrib		 = sThisDistName;
												sDistDUTName = sDUTName;
												pDistObj		 = pThisDistObj;
											}
											else if ((!sThisDistName.isEmpty() || !sDistrib.isEmpty()) && sThisDistName.compare( sDistrib ))
											{	bool bDistsEqual = (pDistObj && pThisDistObj && pDistObj->EquivalentObject( pThisDistObj, true /*bIgnoreDataStatus*/ ));
												if (!bDistsEqual)
													sErrMsg = QString( "Error creating HVACSys object for Zone '%1':  HVACDist '%2' assigned to DwellingUnitType '%3' must be equivalent to the HVACDist '%4' of DwellingUnitType '%5'." ).arg(
																			sZnName, sThisDistName, sDUTName, sDistrib, sDistDUTName );
											}
										}	// end of else - HVACSysType OK
									}
								}
							}	// end of else - DwellUnit:DwellUnitTypeRef OK
						}
					}	// for each DUChild of Zone

				// Have all HVAC equipment data, now create Zone-specific HVACSys object
					if (!BEMPX_CanCreateAnotherUserObject( iCID_HVACSys /*, int iNumObjs=1, int iBEMProcIdx=-1*/ ))
						sErrMsg = QString( "Unable to create a HVACSys object for Zone '%1'" ).arg( sZnName );
					else
					{	QString sHVACSysName = QString( "%1 HVACSys" ).arg( sZnName );
						BEMObject* pHVACSysObj = BEMPX_CreateObject( iCID_HVACSys, sHVACSysName.toLocal8Bit().constData() );		assert( pHVACSysObj && pHVACSysObj->getClass() );
						if (pHVACSysObj && pHVACSysObj->getClass())
						{	sHVACSysName = pHVACSysObj->getName();
							int iHVACSysIdx = BEMPX_GetObjectIndex( pHVACSysObj->getClass(), pHVACSysObj );				assert( iHVACSysIdx >= 0 );
							if (iHVACSysIdx >= 0)
							{	assert(	(lHVACSysType == 2 && saHeatNames.size() > 0) ||
											(lHVACSysType != 2 && saHeatNames.size()   > 0) );
								BEMPX_SetBEMData( lDBID_HVACSys_Status, BEMP_Int, (void*) &lZoneHVACSysStatus, BEMO_User, iHVACSysIdx );		// SAC 8/26/14
								if (BEMPX_SetBEMData( lDBID_HVACSys_Type, BEMP_Int, (void*) &lHVACSysType, BEMO_User, iHVACSysIdx ) < 0)
									sErrMsg = QString( "Error encountered attempting to set HVACSys '%1' Type to %2" ).arg( sHVACSysName, QString::number( lHVACSysType ) );
								else
								{	if (lHVACSysType != 2)	// Heat/Cool
									{	assert( saHeatNames.size() == laHeatCount.size() && saHeatNames.size() < iMaxHVACSysHeatRefs );
										lEqpCount = min( saHeatNames.size(), iMaxHVACSysHeatRefs );
										BEMPX_SetBEMData( lDBID_HVACSys_NumHeatSystemTypes, BEMP_Int, (void*) &lEqpCount, BEMO_User, iHVACSysIdx );
										for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < saHeatNames.size() && iEqpIdx < iMaxHVACSysHeatRefs); iEqpIdx++)
										{	lEqpCount = laHeatCount[iEqpIdx];
											if (BEMPX_SetBEMData( lDBID_HVACSys_HeatSystem     +iEqpIdx, BEMP_Str, (void*) saHeatNames[iEqpIdx].toLocal8Bit().constData(), BEMO_User, iHVACSysIdx ) < 0 ||
												 BEMPX_SetBEMData( lDBID_HVACSys_HeatSystemCount+iEqpIdx, BEMP_Int, (void*)               &lEqpCount                      , BEMO_User, iHVACSysIdx ) < 0)
											{	assert( FALSE );
										}	}
										assert( saCoolNames.size() == laCoolCount.size() && saCoolNames.size() < iMaxHVACSysCoolRefs );
										lEqpCount = min( saCoolNames.size(), iMaxHVACSysCoolRefs );
										BEMPX_SetBEMData( lDBID_HVACSys_NumCoolSystemTypes, BEMP_Int, (void*) &lEqpCount, BEMO_User, iHVACSysIdx );
										for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < saCoolNames.size() && iEqpIdx < iMaxHVACSysCoolRefs); iEqpIdx++)
										{	lEqpCount = laCoolCount[iEqpIdx];
											if (BEMPX_SetBEMData( lDBID_HVACSys_CoolSystem     +iEqpIdx, BEMP_Str, (void*) saCoolNames[iEqpIdx].toLocal8Bit().constData(), BEMO_User, iHVACSysIdx ) < 0 ||
												 BEMPX_SetBEMData( lDBID_HVACSys_CoolSystemCount+iEqpIdx, BEMP_Int, (void*)               &lEqpCount                      , BEMO_User, iHVACSysIdx ) < 0)
											{	assert( FALSE );
										}	}
									// SAC 8/5/15 - added logic to set PreventCoolingSim flag to '1', if set for any DUT of child DUs
										if (lPreventCoolingSim > 0)
											BEMPX_SetBEMData( lDBID_HVACSys_PreventCoolingSim, BEMP_Int, (void*) &lPreventCoolingSim, BEMO_User, iHVACSysIdx );
									}
									else	// Heat Pump
									{	assert( saHeatNames.size() == laHeatCount.size() && saHeatNames.size() < iMaxHVACSysHtPumpRefs );
										lEqpCount = min( saHeatNames.size(), iMaxHVACSysHtPumpRefs );
										BEMPX_SetBEMData( lDBID_HVACSys_NumHtPumpSystemTypes, BEMP_Int, (void*) &lEqpCount, BEMO_User, iHVACSysIdx );
										for (iEqpIdx=0; (sErrMsg.isEmpty() && iEqpIdx < saHeatNames.size() && iEqpIdx < iMaxHVACSysHtPumpRefs); iEqpIdx++)
										{	lEqpCount = laHeatCount[iEqpIdx];
											if (BEMPX_SetBEMData( lDBID_HVACSys_HtPumpSystem     +iEqpIdx, BEMP_Str, (void*) saHeatNames[iEqpIdx].toLocal8Bit().constData(), BEMO_User, iHVACSysIdx ) < 0 ||
												 BEMPX_SetBEMData( lDBID_HVACSys_HtPumpSystemCount+iEqpIdx, BEMP_Int, (void*)               &lEqpCount                      , BEMO_User, iHVACSysIdx ) < 0)
											{	assert( FALSE );
									}	}	}

									if (!sFan.isEmpty())
										BEMPX_SetBEMData( lDBID_HVACSys_Fan,           BEMP_Str, (void*) sFan.toLocal8Bit().constData()    , BEMO_User, iHVACSysIdx );
									if (!sDistrib.isEmpty())
										BEMPX_SetBEMData( lDBID_HVACSys_DistribSystem, BEMP_Str, (void*) sDistrib.toLocal8Bit().constData(), BEMO_User, iHVACSysIdx );

								// assign system to Zone
									if (sErrMsg.isEmpty())
										//VERIFY( BEMPX_SetBEMData( lDBID_Zone_HVACSystem, BEMP_Str, (void*) ((const char*) sHVACSysName), BEMO_User, iZnIdx ) >= 0 );
										switch (lZoneHVACSysStatus)
										{	case  2 :	BEMPX_SetBEMData( lDBID_Zone_AltHVACSystem, BEMP_Str, (void*) sHVACSysName.toLocal8Bit().constData(), BEMO_User, iZnIdx );		break;
											case  1 :	BEMPX_SetBEMData( lDBID_Zone_exHVACSystem , BEMP_Str, (void*) sHVACSysName.toLocal8Bit().constData(), BEMO_User, iZnIdx );		break;
											default :	BEMPX_SetBEMData( lDBID_Zone_HVACSystem   , BEMP_Str, (void*) sHVACSysName.toLocal8Bit().constData(), BEMO_User, iZnIdx );		break;
										}
								}
							}	// end of if valid iHVACSysIdx
						}	// end of if valid pHVACSysObj...
				}	}
			}	// for each Zone
		}	// end of else - BEMBase IDs OK
	}	// end of if - we have DwellUnit & Zone objects

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}

	return iNumObjsCreated;
}

//=============================================================================
// SAC 11/15/14 - routine to create DwellUnitRpt objects - one object for each DwellUnit:Count
int CreateDwellUnitRptObjects( QString& sErrMsg, ExpEvalStruct* /*pEval*/, ExpError* error )
{	int iNumObjsCreated = 0;
	int iNumErrors = 0;			QString sTmp, sDUName;
	int iCID_DwellUnit = GetObjectID_LogError( "DwellUnit", iNumErrors, sTmp );
	long lNumDwellUnits = BEMPX_GetNumObjects( iCID_DwellUnit );
	if (lNumDwellUnits > 0)
	{	long lDBID_DwellUnit_Name   = GetPropertyDBID_LogError( "DwellUnit", "Name"  , iCID_DwellUnit, iNumErrors, sTmp );
		long lDBID_DwellUnit_Count  = GetPropertyDBID_LogError( "DwellUnit", "Count" , iCID_DwellUnit, iNumErrors, sTmp );

		int iCID_DwellUnitRpt = GetObjectID_LogError( "DwellUnitRpt", iNumErrors, sTmp );

		if (iNumErrors > 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitRptObjects database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
		else if (iNumErrors == 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitRptObjects database ID %1" ).arg( sTmp );
		else
		{	long lDUCount;			int iError;
			for( int iDUIdx=0; (sErrMsg.isEmpty() && iDUIdx < lNumDwellUnits); iDUIdx++)
			{	if (!BEMPX_GetString(  lDBID_DwellUnit_Name , sDUName, FALSE, 0, -1, iDUIdx ) || sDUName.isEmpty() ||
					 !BEMPX_GetInteger( lDBID_DwellUnit_Count, lDUCount,       0, -1, iDUIdx ) )
					sErrMsg = QString( "Error encountered retrieving Name and/or Count of DwellUnit #%1 '%2'" ).arg( QString::number( iDUIdx+1 ), sDUName );
				else
				{	BEMObject* pDUObj = BEMPX_GetObjectByClass( iCID_DwellUnit, iError, iDUIdx );		// BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
					if (pDUObj == NULL)
						sErrMsg = QString( "Error encountered retrieving pointer to object DwellUnit #%1 '%2'" ).arg( QString::number( iDUIdx+1 ), sDUName );
					else
						for (int iCnt=1; (sErrMsg.isEmpty() && iCnt <= lDUCount); iCnt++)
						{	QString sDURName = QString( "%1-(%2/%3)" ).arg( sDUName, QString::number( iCnt ), QString::number( lDUCount ) );
							BEMObject* pDURObj = BEMPX_CreateObject( iCID_DwellUnitRpt, sDURName.toLocal8Bit().constData(), pDUObj );					assert( pDURObj );
							if (pDURObj == NULL)
								sErrMsg = QString( "Error encountered creating DwellUnitRpt child #%1 of DwellUnit #%2 '%3'" ).arg( QString::number( iCnt ), QString::number( iDUIdx+1 ), sDUName );
						}
				}
			}
	}	}

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
	}

	return iNumObjsCreated;
}

//=============================================================================

int CreateDwellUnitDHWHeaters( QString& sErrMsg, int /*iDUDHWObjIdx*/, BEM_ObjType /*eDUDHWObjType*/, const QString& sDUDHWName, ExpEvalStruct* /*pEval*/, ExpError* error )	// SAC 5/30/16
{
//		CreateDwellUnitDHWHeaters( DwellUnitDHWName )
//			loop over all cseDHWSYS objects and for each where cseDHWSYS:SourceDwellUnitDHW = DwellUnitDHWName...
//				grab cseDHWSYS:SourceDHWSys
//				loop over all ResWtrHtr children of cseDHWSYS:SourceDHWSys, creating a cseDHWHEATER for each, named "dhwhtr-<ResWtrHtr:Name> - <DwellUnitDHWName>"
//				set:	cseDHWHEATER:Parent = cseDHWSYS
//						cseDHWHEATER:SourceDHWHeater = ResWtrHtr:Name
	int iNumCSEDHWHtrsCreated = 0;		int iNumErrors = 0;			QString sTmp;
	int iCID_CSEDHWSys  = GetObjectID_LogError( "cseDHWSYS", iNumErrors, sTmp );
	int iCID_ResDHWSys  = GetObjectID_LogError( "ResDHWSys", iNumErrors, sTmp );
	int iCID_ResWtrHtr  = GetObjectID_LogError( "ResWtrHtr", iNumErrors, sTmp );
	int iCID_CSEDHWHtr  = GetObjectID_LogError( "cseDHWHEATER", iNumErrors, sTmp );
	int iCID_CSEDHWTank = GetObjectID_LogError( "cseDHWTANK", iNumErrors, sTmp );
	long lNumCSEDHWSyss = BEMPX_GetNumObjects( iCID_CSEDHWSys );
	long lNumResWtrHtrs = BEMPX_GetNumObjects( iCID_ResWtrHtr );
	if (lNumCSEDHWSyss > 0 && lNumResWtrHtrs > 0)
	{	long lDBID_CSEDHWSys_SrcDUDHW   = GetPropertyDBID_LogError( "cseDHWSYS"   , "SourceDwellUnitDHW", iCID_CSEDHWSys , iNumErrors, sTmp );
		long lDBID_CSEDHWSys_SrcDHWSys  = GetPropertyDBID_LogError( "cseDHWSYS"   , "SourceDHWSys"      , iCID_CSEDHWSys , iNumErrors, sTmp );
		//long lDBID_CSEDHWSys_Parent     = GetPropertyDBID_LogError( "cseDHWSYS"   , "Parent"            , iCID_CSEDHWSys , iNumErrors, sTmp );
		long lDBID_ResWtrHtr_Name       = GetPropertyDBID_LogError( "ResWtrHtr"   , "Name"              , iCID_ResWtrHtr , iNumErrors, sTmp );
		long lDBID_ResWtrHtr_CSESimTank = GetPropertyDBID_LogError( "ResWtrHtr"   , "CSE_SimulateTank"  , iCID_ResWtrHtr , iNumErrors, sTmp );
		long lDBID_CSEDHWHtr_SrcDHWHtr  = GetPropertyDBID_LogError( "cseDHWHEATER", "SourceDHWHeater"   , iCID_CSEDHWHtr , iNumErrors, sTmp );
		//long lDBID_CSEDHWHtr_Parent     = GetPropertyDBID_LogError( "cseDHWHEATER", "Parent"            , iCID_CSEDHWHtr , iNumErrors, sTmp );
		long lDBID_ResDHWSys_CentralSys = GetPropertyDBID_LogError( "ResDHWSys"   , "CentralSys"        , iCID_ResDHWSys , iNumErrors, sTmp );
		long lDBID_CSEDHWTnk_SrcDHWHtr  = GetPropertyDBID_LogError( "cseDHWTANK"  , "SourceDHWHeater"   , iCID_CSEDHWTank, iNumErrors, sTmp );
		if (iNumErrors > 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitDHWHeaters database IDs, starting with %1 (plus %2 others)" ).arg( sTmp, QString::number( iNumErrors-1 ) );
		else if (iNumErrors == 1)
			sErrMsg = QString( "Error initializing CreateDwellUnitDHWHeaters database ID %1" ).arg( sTmp );
		else
		{	int iError;		QString sCSEDSys_SrcDUDHW;		BEMObject *pCSEDSys, *pCSEDSys_SrcDHWSys;
			for (int iCSEDSIdx=0; (sErrMsg.isEmpty() && iCSEDSIdx < lNumCSEDHWSyss); iCSEDSIdx++)
			{	pCSEDSys = BEMPX_GetObjectByClass( iCID_CSEDHWSys, iError, iCSEDSIdx );															assert( pCSEDSys );
				if (pCSEDSys && BEMPX_GetString( lDBID_CSEDHWSys_SrcDUDHW, sCSEDSys_SrcDUDHW , FALSE, 0, -1, iCSEDSIdx ) && 
					 !sCSEDSys_SrcDUDHW.isEmpty() && sCSEDSys_SrcDUDHW.compare( sDUDHWName )==0 &&
					 BEMPX_GetObject( lDBID_CSEDHWSys_SrcDHWSys, pCSEDSys_SrcDHWSys, -1, iCSEDSIdx ) && pCSEDSys_SrcDHWSys )
				{	
					int iResDHWSysIdx = BEMPX_GetObjectIndex( pCSEDSys_SrcDHWSys->getClass(), pCSEDSys_SrcDHWSys );				assert( iResDHWSysIdx >= 0 );
					if (iResDHWSysIdx >= 0)
					{	long lResDHWSys_CentralSys = 0;
						BEMPX_GetInteger( lDBID_ResDHWSys_CentralSys, lResDHWSys_CentralSys, 0, -1, iResDHWSysIdx );
						BEM_ObjType eResDHWSysObjType = BEMO_User;
						int iNumResWtrHtrChildren = (int) BEMPX_GetNumChildren( iCID_ResDHWSys, iResDHWSysIdx, eResDHWSysObjType, iCID_ResWtrHtr );
						for (int iWtrHtr=0; (sErrMsg.isEmpty() && iWtrHtr < iNumResWtrHtrChildren); iWtrHtr++)
						{
							BEM_ObjType eResWtrHtrObjType = BEMO_User;		QString sRWH_Name;
							int iResWtrHtrObjIdx = BEMPX_GetChildObjectIndex( iCID_ResDHWSys, iCID_ResWtrHtr, iError, eResDHWSysObjType, 
																							  iWtrHtr+1 /*i1ChildIdx*/, iResDHWSysIdx, eResWtrHtrObjType );
							if (iResWtrHtrObjIdx >= 0 && BEMPX_GetString( lDBID_ResWtrHtr_Name , sRWH_Name , FALSE, 0, -1, iResWtrHtrObjIdx ) &&
								 !sRWH_Name.isEmpty())
							{
								QString sCSEWtrHtrName = "dhwhtr-" + sDUDHWName + QString(" - ") + sRWH_Name;
								BEMObject* pCSEWtrHtrObj = BEMPX_CreateObject( iCID_CSEDHWHtr, sCSEWtrHtrName.toLocal8Bit().constData(), pCSEDSys );		assert( pCSEWtrHtrObj );
								if (pCSEWtrHtrObj == NULL)
									sErrMsg = QString( "Error encountered creating cseDHWHEATER child #%1 of cseDHWSYS #%2 '%3'" ).arg( QString::number( iWtrHtr+1 ), QString::number( iCSEDSIdx+1 ), pCSEDSys->getName() );
								else
								{	iNumCSEDHWHtrsCreated++;
									int iCSEDHWHtrIdx = BEMPX_GetObjectIndex( pCSEWtrHtrObj->getClass(), pCSEWtrHtrObj );				assert( iCSEDHWHtrIdx >= 0 );
									BEMPX_SetBEMData( lDBID_CSEDHWHtr_SrcDHWHtr , BEMP_Str, (void*) sRWH_Name.toLocal8Bit().constData(), BEMO_User, iCSEDHWHtrIdx );
									long lResWtrHtr_CSESimTank;
									BEMPX_GetInteger( lDBID_ResWtrHtr_CSESimTank, lResWtrHtr_CSESimTank, 0, -1, iResWtrHtrObjIdx );
									if (lResDHWSys_CentralSys < 1 && lResWtrHtr_CSESimTank > 0)
									{	// create cseDHWTANK as well
										QString sCSEDHWTankName = "dhwtnk-" + sDUDHWName + QString(" - ") + sRWH_Name;
										BEMObject* pCSEDHWTankObj = BEMPX_CreateObject( iCID_CSEDHWTank, sCSEDHWTankName.toLocal8Bit().constData(), pCSEDSys );		assert( pCSEDHWTankObj );
										if (pCSEDHWTankObj == NULL)
											sErrMsg = QString( "Error encountered creating cseDHWTANK child #%1 of cseDHWSYS #%2 '%3'" ).arg( QString::number( iWtrHtr+1 ), QString::number( iCSEDSIdx+1 ), pCSEDSys->getName() );
										else
										{	int iCSEDHWTankIdx = BEMPX_GetObjectIndex( pCSEDHWTankObj->getClass(), pCSEDHWTankObj );				assert( iCSEDHWTankIdx >= 0 );
											BEMPX_SetBEMData( lDBID_CSEDHWTnk_SrcDHWHtr, BEMP_Str, (void*) sRWH_Name.toLocal8Bit().constData(), BEMO_User, iCSEDHWTankIdx );
									}	}
							}	}
						}	// end of For each child ResWtrHtr
				}	}
			}	// end of For each cseDHWSYS
	}	}

	if (!sErrMsg.isEmpty())
	{	assert( FALSE );
		ExpSetErr( error, EXP_RuleProc, sErrMsg );
		iNumCSEDHWHtrsCreated = -1;
	}
	return iNumCSEDHWHtrsCreated;
}

//=============================================================================

double BEMPX_GetRulesetSimulateFlagValue( double fDefault /*=1*/ )
{	double fRetVal = fDefault;
	if (ruleSet.getSimulateDBID() > BEM_COMP_MULT)
	{	double fData;
		if (BEMPX_GetFloat( ruleSet.getSimulateDBID(), fData, fDefault ))
			fRetVal = fData;
	}
	return fRetVal;
}

//=============================================================================


//=============================================================================
// Calendar/Date routines based on CalUtils

#define MIN_YEAR         1900    // Min year
#define MAX_YEAR         2050    // Max year
#define MIN_SERIAL       1       // 1900-JAN-1
#define MAX_SERIAL       55153   // 2050-DEC-31

typedef enum
{
   Sunday = 1,
   Monday,
   Tuesday,
   Wednesday,
   Thursday,
   Friday,
   Saturday,
   NDays
} Day;                              // Day of the week.

//typedef long Serial;
//typedef int  Julian;       // Date of this year.
//typedef int  YearHour;

const UINT LEAP_PERIOD              = 4;       // Years in a leap cycle.
const int DAYS_PER_WEEK             = 7;
const int DAYS_PER_YEAR             = 365;     // Non-leap year.
const int HOURS_PER_DAY             = 24;
const int HOURS_PER_WEEK            = 168;
const int WEEKS_PER_MONTH           = 6;       // Maximum.
const int MONTHS_PER_YEAR           = 12;
const int HOURS_PER_YEAR            = HOURS_PER_DAY * DAYS_PER_YEAR;

static const int START_YEAR_LOOKUP  = 100;  // 2000 is a good place to start

static char* dayStr[7] = { "Sunday", "Monday", "Tuesday", "Wednesday",
                               "Thursday", "Friday", "Saturday" };
static char* shortMonthStr[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
static char* longMonthStr[12] = { "January", "February", "March", "April",
                                  "May", "June", "July", "August", "September",
                                  "October", "November", "December" };

inline BOOL static IsLeapYear( int year )
   { return !(year % LEAP_PERIOD); }

inline BOOL static ValidateYear( int year )
   { return year >= MIN_YEAR && year <= MAX_YEAR; }

inline BOOL static ValidateMonth( int month )
   { return month > 0 && month <= MONTHS_PER_YEAR; }

inline BOOL static ValidateSerial( long serial )
   { return serial >= MIN_SERIAL && serial <= MAX_SERIAL; }

inline BOOL static ValidateJulian( int year, int julian )
   { return julian >= 0 && julian - IsLeapYear( year ) <= DAYS_PER_YEAR; }

static const int datesPerMonth[2][MONTHS_PER_YEAR] =
{
   { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },   // Normal Year.
   { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }    // Leap Year.
};

//   yearStartDate[] look-up table.
//      Gives the number of dates elapsed from
//      1-Jan-1900 to 1-Jan of the index year.
static const long yearStartDate[] =
{
       0,    366,    731,   1096,   1461,   1827,   2192,
    2557,   2922,   3288,   3653,   4018,   4383,   4749,
    5114,   5479,   5844,   6210,   6575,   6940,   7305,
    7671,   8036,   8401,   8766,   9132,   9497,   9862,
   10227,  10593,  10958,  11323,  11688,  12054,  12419,
   12784,  13149,  13515,  13880,  14245,  14610,  14976,
   15341,  15706,  16071,  16437,  16802,  17167,  17532,
   17898,  18263,  18628,  18993,  19359,  19724,  20089,
   20454,  20820,  21185,  21550,  21915,  22281,  22646,
   23011,  23376,  23742,  24107,  24472,  24837,  25203,
   25568,  25933,  26298,  26664,  27029,  27394,  27759,
   28125,  28490,  28855,  29220,  29586,  29951,  30316,
   30681,  31047,  31412,  31777,  32142,  32508,  32873,
   33238,  33603,  33969,  34334,  34699,  35064,  35430,
   35795,  36160,  36525,  36891,  37256,  37621,  37986,
   38352,  38717,  39082,  39447,  39813,  40178,  40543,
   40908,  41274,  41639,  42004,  42369,  42735,  43100,
   43465,  43830,  44196,  44561,  44926,  45291,  45657,
   46022,  46387,  46752,  47118,  47483,  47848,  48213,
   48579,  48944,  49309,  49674,  50040,  50405,  50770,
   51135,  51501,  51866,  52231,  52596,  52962,  53327,
   53692,  54057,  54423,  54788
};

static const int monthLookUp[2][MONTHS_PER_YEAR + 1] =
{
  { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
  { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

long MakeJulian( int year, int month, int day, BOOL calcLeap )
{
   return ( (calcLeap) ? monthLookUp[ IsLeapYear( year ) ][ month - 1 ] + day :
                         monthLookUp[           0        ][ month - 1 ] + day );
}

long YrMoDaToSerial( int iYr, int iMo, int iDa )     // based on CalUtils -> Serial MakeSerial( int year, int month, int date, BOOL calcLeap );
{  BOOL calcLeap = TRUE;
   long serialDate = 0;
   if( ValidateYear( iYr ) && ValidateMonth( iMo ) )
   {
      int adjustYear = iYr - MIN_YEAR;
      serialDate = yearStartDate[ adjustYear ] + MakeJulian( iYr, iMo, iDa, calcLeap );

//      if ( (!calcLeap) && (IsLeapYear( year )) &&
//           ( ((month == 2) && (date == 29)) || (month > 2) ) )
//         serialDate --;
   }
   assert( !serialDate == 0 );
   return serialDate;
}

int SerialDateToDayOfMonth( long lSerial )           // based on CalUtils -> int Date(    Serial serialDate, BOOL calcLeap );   // Date of month.
{  BOOL calcLeap = TRUE;
   BOOL ok = ValidateSerial( lSerial );
   int date = 0;
   if( ok )
   {
      int baseYear  = START_YEAR_LOOKUP;
      if( lSerial >= yearStartDate[ baseYear ] )
      {  while( lSerial >= yearStartDate[ baseYear ] )
         {  baseYear++;
         }
         baseYear--;
      }
      else
      {  while( lSerial <= yearStartDate[ baseYear ] )
         {  baseYear--;
         }
      }

      long remainder = (lSerial - yearStartDate[ baseYear ]);
      assert( remainder > 0 );
      int month = 0;
      while( remainder > monthLookUp[ (calcLeap && IsLeapYear( baseYear )) ][ month ] )
      {  month++;
      }
      month--;
      date = remainder - monthLookUp[ (calcLeap && IsLeapYear( baseYear )) ][ month ];
   }
   assert( !date == 0 );

   return date;
}

int SerialDateToMonth( long lSerial )                // based on CalUtils -> int Month(   Serial serialDate, BOOL calcLeap );   // Month of year.
{  BOOL calcLeap = TRUE;
   BOOL ok = ValidateSerial( lSerial );
   int month  = 0;
   if( ok )
   {  int baseYear  = START_YEAR_LOOKUP;
      if( lSerial >= yearStartDate[ baseYear ] )
      {  while( lSerial > yearStartDate[ baseYear ] )
         {  baseYear++;
         }
         baseYear--;
      }
      else
      {  while( lSerial < yearStartDate[ baseYear ] )
         {  baseYear--;
         }
      }
      long remainder = (lSerial - yearStartDate[ baseYear ]);
      while( remainder > monthLookUp[ (calcLeap && IsLeapYear( baseYear )) ][ month ] )
      {  month++;
      }
   }
   return month;
}

int SerialDateToYear( long lSerial )                 // based on CalUtils -> int Year(    Serial serialDate );                  // Year of century.
{
   BOOL ok = ValidateSerial( lSerial );
   int year  = START_YEAR_LOOKUP;
   if( ok )
   { if( lSerial >= yearStartDate[ year ] )
      {  while( lSerial >= yearStartDate[ year ] )
         {  year++;
         }
         year--;
      }
      else
      {  while( lSerial < yearStartDate[ year ] )
         {  year--;
         }
   }  }
   return year + MIN_YEAR;
}

int YrMoDaToDayOfWeek( int iYr, int iMo, int iDa )   // based on CalUtils -> Day WeekDay( Serial serialDate );                  // Day of week.
{
	long lSerialDate = YrMoDaToSerial( iYr, iMo, iDa );
   Day day = Sunday;
   if (ValidateSerial( lSerialDate ))
   {  if( (lSerialDate) % DAYS_PER_WEEK )
         day = (Day) (lSerialDate % DAYS_PER_WEEK);
      else
         day = (Day) DAYS_PER_WEEK;
   }
   return (int) day;
}

// end of - routines based on CalUtils
//=============================================================================


// rulelist.cpp end



