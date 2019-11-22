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
#include "BEMClass.h"
#include "BEMProcObject.h"
#include "BEMPropertyType.h"
#include "BEMProperty.h"
#include "memLkRpt.h"


// SAC 8/7/10 - implementation of targeted debug output
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
void ReportTargetedDebugInfo( /*ExpEvalStruct* pEval, int iDataType,*/ long lDBID, int iObjIdx, /*BEM_ObjType eObjType,*/ QString sCallingFunc, int iBEMProcModel )
{
	int iDataType = BEMPX_GetDataType( lDBID );
	BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( BEMPX_GetClassID( lDBID ), iObjIdx, iBEMProcModel );
   assert( lDBID > 0 && iDataType > 0 );
   if (lDBID > 0 && iDataType > 0)
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
      //if (!pEval->bRuleIDLogged)
      //   sDebug = QString( "      %1  '" ).arg( pEval->pRuleBeingEvaled->getID() );
      //else
         sDebug  = "                   '";

      pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError, iObjIdx, eObjType );
      if (pObj) // && !pObj->getName().isEmpty())
         sDebug += pObj->getName();
      else
         sDebug += "<unknown>";
      sDebug += "' ";
      BEMPX_DBIDToDBCompParamString( lDBID, sDebug2 );
      sDebug += sDebug2;
      sDebug += " -> ";
      sDebug += sRetrievedData;

      //if (!pEval->bRuleIDLogged)
      //{  sDebug2 = QString( "     (rulelist: '%1')" ).arg( pEval->sRuleListName );
      //   sDebug += sDebug2;
      //   pEval->bRuleIDLogged = TRUE;
      //}

      if (!sCallingFunc.isEmpty())
      {  sDebug2 = QString( "   (via %1)" ).arg( sCallingFunc );
         sDebug += sDebug2;
      }

      BEMPX_WriteLogFile( sDebug );
   }
}


/////////////////////////////////////////////////////////////////////////////
// BEMProperty
/////////////////////////////////////////////////////////////////////////////

BEMProperty::~BEMProperty()
{
}


/////////////////////////////////////////////////////////////////////////////

static inline int longVectorIdx( std::vector<long>& laVals, long lVal )
{	int idx = -1;
	for (std::vector<long>::iterator it = laVals.begin(); it != laVals.end(); ++it)
	{	idx++;
		if (*it == lVal)
			return idx;
	}
	return -1;
}


void BEMProperty::ReinitLocalResetData( std::vector<long>& laResetDBIDs, long lDBID, int iOccur /*=-1*/, BOOL bResetUserDefinedData /*=TRUE*/,
   													BEMCompNameTypePropArray* pTargetedDebugInfo /*=NULL*/ )		// SAC 9/25/19 - added pTargetedDebugInfo to enable logging of resets for targeted debug DBIDs
{
   if (m_type && m_1ArrayIdx >= 1 && lDBID > 0)
   {
		int iNumResets = m_type->getNumResetDBIDs( m_1ArrayIdx-1 );
		for (int iR=0; iR < iNumResets; iR++)
		{	long lDBID = m_type->getResetDBID( m_1ArrayIdx-1, iR );
         int i1Array = BEMPX_GetArrayID( lDBID );
         int   iStartArrayInc = 0;
         int   iEndArrayInc   = 0;
         if (i1Array == 0)  // => [ALL]
         {
            int i1Class = BEMPX_GetClassID(    lDBID );
            int i1Param = BEMPX_GetPropertyID( lDBID );
            // get the selected CBEMPropertyType
            BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Param );
            if (pPropType)
            {
               iStartArrayInc = 1;
               iEndArrayInc   = pPropType->getNumValues();
            }
         }

         for (long i2=iStartArrayInc; i2 <= iEndArrayInc; i2++)
         {
            if (longVectorIdx( laResetDBIDs, (lDBID+i2) ) < 0)
            {  // add this DBID to the list of reset DBIDs
               laResetDBIDs.push_back( (lDBID+i2) );
               int iError;
               BEMProperty* pProp = BEMPX_GetProperty( lDBID+i2, iError, iOccur );
               if (pProp && (bResetUserDefinedData || (pProp->m_dataStatus != BEMS_UserLibrary && pProp->m_dataStatus != BEMS_UserDefined)))  // prevent reset of user defined data (when specified)
               {
                  // Reinitialize (default) this property
                  pProp->Default( lDBID+i2, iOccur, BEMO_User, TRUE );

	 	  		      if (pTargetedDebugInfo && pTargetedDebugInfo->MatchExists( lDBID+i2, iOccur ))
            			ReportTargetedDebugInfo( lDBID+i2, iOccur, "ReinitResetData()", -1 /*iBEMProcIdx*/ );

                  // Reinitialize those properties which are in it's ResetData list
                  pProp->ReinitLocalResetData( laResetDBIDs, lDBID+i2, iOccur, bResetUserDefinedData, pTargetedDebugInfo );
               }
            }
         }
      }
   }
}

void BEMProperty::ReinitResetData( long lDBID, int iOccur /*=-1*/, BOOL bResetUserDefinedData /*=TRUE*/,
   											BEMCompNameTypePropArray* pTargetedDebugInfo /*=NULL*/ )		// SAC 9/25/19 - added pTargetedDebugInfo to enable logging of resets for targeted debug DBIDs
{
	std::vector<long> laResetDBIDs;
   laResetDBIDs.push_back( lDBID );
   ReinitLocalResetData( laResetDBIDs, lDBID, iOccur, bResetUserDefinedData, pTargetedDebugInfo );
}


/////////////////////////////////////////////////////////////////////////////
//
// CBEMProperty Class Function:  CopyProperty()
//
// Purpose ------------------------------------------------------------------
//   Copies the contents of one property (pProp) into the local property
//   
// Arguments ----------------------------------------------------------------
//   CBEMProperty* pProp  : pointer to the property to copy the data FROM
//   
// Return Value -------------------------------------------------------------
//   TRUE if valid property passed in, else FALSE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMProperty::CopyProperty( BEMProperty* pProp, int iBEMProcIdx /*=-1*/, bool bForceNonUniqueCompAssignments /*=FALSE*/,
												bool bCopyPrimaryDefaultDataAsUserDefined /*=false*/ )		// SAC 6/8/15 - CBECC issue 1061
{
   bool bRetVal = (pProp != NULL);
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   if (bRetVal)
   {
   	m_type       = pProp->m_type;
      // reset library defined data to user defined (otherwise it won't get written out)
      m_dataStatus = -1;
      if ( (pProp->m_dataStatus == BEMS_RuleLibrary) ||
           (pProp->m_dataStatus == BEMS_UserLibrary) )
         m_dataStatus   = BEMS_UserDefined;
		else if (bCopyPrimaryDefaultDataAsUserDefined &&										// SAC 6/8/15 - CBECC issue 1061
					pProp->m_dataStatus >= BEMS_ProgDefault && pProp->m_dataStatus <= BEMS_UserDefault && m_type)
		{	BEMPropTypeDetails* pDT = m_type->getPropTypeDetails( pProp->m_1ArrayIdx-1 );		assert( pDT );
			if (pDT && pDT->isPrimary())
				m_dataStatus   = BEMS_UserDefined;
		}
		if (m_dataStatus == -1)
         m_dataStatus = pProp->m_dataStatus ;

      m_specialValue = pProp->m_specialValue;
      // m_critDefIdx   = pProp->m_critDefIdx  ;
      m_1ArrayIdx    = pProp->m_1ArrayIdx   ;

   	m_strValue     = pProp->m_strValue    ;
      switch (m_type->getPropType())
      {
         case BEMP_Int : {  m_intValue = pProp->m_intValue;   break;  }
         case BEMP_Sym : {  m_intValue = pProp->m_intValue;   break;  }
         case BEMP_Flt : {  m_dblValue = pProp->m_dblValue;   break;  }
         case BEMP_Obj : {  m_obj = pProp->m_obj;
                           // if this object's class indicates that assignments must be unique, then copy and re-assign the object
                           if (!bForceNonUniqueCompAssignments && m_obj && m_obj->getClass() && m_obj->getClass()->getUniqueAssignment())
                              CopyAssignedObject( FALSE, iBEMProcIdx );
                           break;  }
      }
   }

   return bRetVal;
}

// similar routine to that above, but crossing separate models (CBEMProcObject instances) and ignoring OBJECT pointer
bool BEMProperty::CopyPropertyAcrossModels( BEMProperty* pProp, int iToBEMProcIdx /*=-1*/ )
{
   bool bRetVal = (pProp != NULL && pProp->m_type != NULL);
   if (bRetVal)
   {
   	m_type         = BEMPX_GetPropertyType( pProp->m_type->get1ClassIdx(), pProp->m_type->get1PropTypeIdx(), iToBEMProcIdx );  // get ptr to PropType of DESTINATION model
      m_dataStatus   = pProp->m_dataStatus  ;   // DIRECT copy of DataStatus - regardless of user/library source...
      m_specialValue = pProp->m_specialValue;
     // m_iCritDefIdx   = pProp->m_iCritDefIdx  ;
      m_1ArrayIdx    = pProp->m_1ArrayIdx   ;

   	m_strValue     = pProp->m_strValue    ;
      switch (m_type->getPropType())
      {
         case BEMP_Int : {  m_intValue = pProp->m_intValue;   break;  }
         case BEMP_Sym : {  m_intValue = pProp->m_intValue;   break;  }
         case BEMP_Flt : {  m_dblValue = pProp->m_dblValue;   break;  }
         case BEMP_Obj : {  m_obj = NULL;   // do NOT copy object pointer - object pointers resolved in a second step
									 if (pProp->m_obj)
									 	 m_strValue = pProp->m_obj->getName();
                            break;  }
      }
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Function:  GetCompIsUserDefaultable()
//
// Purpose ------------------------------------------------------------------
//   Get the value of the user defaultable flag member of the compliance data
//   for a selected property type.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   The user defaultable flag for the selected property type's compliance data,
//   OR FALSE if an error occurred retrieving the CBEMDataType instance.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool GetCompIsUserDefaultable( long lDBID )
{  bool bRetVal = FALSE;
	BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lDBID ), BEMPX_GetPropertyID( lDBID ) );		assert( pPropType );
	if (pPropType)
	{	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( BEMPX_GetArrayID( lDBID )-1 );								assert( pPTD );
		if (pPTD)
			bRetVal = ( pPTD->isUserDefaultable() &&
							pPTD->getCompDataType() != BEMD_Default     &&
							pPTD->getCompDataType() != BEMD_CriticalDef &&
							pPTD->getCompDataType() != BEMD_NotInput    );
	}
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMProperty Class Function:  Default()
//
// Purpose ------------------------------------------------------------------
//   Install the default value into the property data
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : 6 digit database ID CCPPAA (comp/property/array)
//   int        iOccur   : occurrence index of component being defaulted
//   BEM_ObjType eObjType : object type of component being defaulted
//   BOOL bReinitializing : Flag defaulting to FALSE indicating whether this
//                          function is being called by CBEMProperty::ReinitResetData()
//   
// Return Value -------------------------------------------------------------
//   TRUE if a default value is installed, else FALSE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMProperty::Default( long lDBID, int iOccur, BEM_ObjType eObjType, BOOL bReinitializing, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = FALSE;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   // start by resetting all data to its most raw state
	m_dataStatus   = 0;
   m_specialValue = 0;
   //if ( m_iCritDefIdx > 0 )
   //   m_iCritDefIdx *= -1;  // negate critical default index for possible later use
   m_intValue = 0;
   m_dblValue = 0;
   m_obj = NULL;
   m_strValue.clear();

   // now set user default (if available)
   void* pUserDef = NULL;  //GetUserDefault( lDBID );
   if (pUserDef && GetCompIsUserDefaultable( lDBID ))
   {
      switch (m_type->getPropType())
      {
         case BEMP_Int : {  m_intValue = *((long  *) pUserDef);   bRetVal = TRUE;   break;  }
         case BEMP_Flt : {  m_dblValue = *((double*) pUserDef);   bRetVal = TRUE;   break;  }
         case BEMP_Sym : { //// defaulting of symbols defined via CSV file tables
                           //int iSymTableIdx = BEMPX_GetIndexOfSymbolTable( lDBID );
                           //if (iSymTableIdx >= 0)
                           //{
                           //   assert( FALSE );  // need to have a mechanism to get the VALUE of a symbol defined in a symbol table!!
                           //}
                           //else
                           //{
                              BEMSymbolList* pSymList = GetSymbolList( lDBID );
                              if (pSymList != NULL)
                              {
                                 long iSymVal = pSymList->GetSymbolValue( lDBID, iOccur, eObjType, (const char*) pUserDef,
                                                                          bReinitializing, iBEMProcIdx );
                                 if (iSymVal != -999)  // SAC 3/14/02 - Switched "symbol not found" value from -1 to -999
                                 {
                                    m_intValue = iSymVal;
                                    bRetVal = TRUE;
												// initiate the reset of certain other symbol lists to file lists
                                    //ResetSymbolFileListIfNecessary( (DWORD) lDBID, (DWORD) iSymVal, iOccur, eObjType, iBEMProcIdx );
                                 }
                              }
                           //}
                           break;  }
         case BEMP_Str : {  m_strValue = ((const char*) pUserDef);   bRetVal = TRUE;   break;  }
         case BEMP_Obj : {  // must convert string object name to object pointer, then set data
                           BEMObject* pPrevObj = m_obj;
                           BEMObject* pNewObj = NULL;
                           if (((const char*) pUserDef)[0] != '\0')
                           {
                              int iError;
                              int iObjType = 0;
                              while (pNewObj == NULL && iObjType < BEMO_NumTypes)
                              {
                                 //pNewObj = BEMPX_GetObjectByName( m_pType->m_i1ObjClassIdx, iError,
                                 //                               (const char*) pUserDef, (BEM_ObjType) iObjType, iBEMProcIdx );
											for (int iObjCls=0; (pNewObj == NULL && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
                                 {	if (m_type->getObj1ClassIdx( iObjCls ) > 0)
													pNewObj = BEMPX_GetObjectByName( m_type->getObj1ClassIdx( iObjCls ), iError,
                                 		                               (const char*) pUserDef, (BEM_ObjType) iObjType, iBEMProcIdx );
											}
                                 iObjType++;
                              }
                           }
                           // Set new referenced lib object's m_bUserReferenced flag
                           if (pNewObj != NULL)
                           {
                              m_obj = pNewObj;
                              bRetVal = TRUE;
                              if (eObjType == BEMO_User)
                                 SetUserReferencedFlag( m_obj, TRUE, iBEMProcIdx );
                           }
                           // Unset previous referenced lib object's m_bUserReferenced flag
                           if (pPrevObj && eObjType == BEMO_User)
                              SetUserReferencedFlag( pPrevObj, FALSE, iBEMProcIdx );
                           break;  }
         default      : {  break;  }
      }

      if (bRetVal)
         m_dataStatus = BEMS_UserDefault;
   }

   // If type = symbol and it is not yet defaulted, then try the default stored in the symbollist itself
   if (!bRetVal && m_type->getPropType() == BEMP_Sym)
   {
   //   // defaulting of symbols defined via CSV file tables
   //   int iSymTableIdx = BEMPX_GetIndexOfSymbolTable( lDBID, iBEMProcIdx );
   //   if (iSymTableIdx >= 0)
   //   {
   //      long iSymDefault = BEMPX_GetSymbolTableDefault( lDBID, iSymTableIdx, iBEMProcIdx );        ASSERT( iSymDefault != -999 );  // none of these to date, no problem though if/when there are
   //      if (iSymDefault != -999)
   //      {
   //         m_intValue = iSymDefault;
   //         m_dataStatus = BEMS_ProgDefault;   // ???
   //         bRetVal = TRUE;
   //      }
   //   }
   //   else
   //   {
         BEMSymbolList* pSymList = GetSymbolList( lDBID );
         if (pSymList)
         {
            BEMSymDependencySet* pSymDepSet = pSymList->GetSymbolDepSet( lDBID, iOccur, eObjType, iBEMProcIdx );
            if (pSymDepSet && pSymDepSet->getDefaultValue() >= 0)
            {
               m_intValue = pSymDepSet->getDefaultValue();
               m_dataStatus = pSymList->getSource();
               bRetVal = TRUE;
            }
         }
   //   }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  GetEquivalentUserObject()
//
// Purpose ------------------------------------------------------------------
//   This function is called to find a user-defined object who's data matches
//   the library object which is identified by the function argument.  This
//   allows us redirect user assignments to library components to point to
//   user-defined copies of the library components so that we don't copy the
//   library component each time the user or ruleset chooses to assign that
//   library component to a user-defined component.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pLibObj  : Pointer to the library component we are attempting
//                         to find the user-defined equivalent of.
//   
// Return Value -------------------------------------------------------------
//   NULL if no user-defined equivalent object found, otherwise a pointer
//   to the equivalent user-defined component.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* GetEquivalentUserObject( BEMObject* pLibObj )
{			assert( pLibObj );
			assert( pLibObj->getClass() );
			assert( (pLibObj->getObjectType() == BEMO_RuleLib || pLibObj->getObjectType() == BEMO_UserLib) );
   BEMObject *pUserObj = NULL, *pUserObjDiffName = NULL;
	for (int ib=0; (pUserObj == NULL && ib < pLibObj->getClass()->ObjectCount( BEMO_User )); ib++)
	{	BEMObject* pObj = (BEMObject*) pLibObj->getClass()->GetObject( BEMO_User, ib );			assert( pObj );
      if (pObj && pObj->EquivalentObject( pLibObj, TRUE ))
         // object valid AND the object's name has the lib object's name in it
         // => the object is/was probably a copy of the library object
         // AND the user and library objects are "equivalent"
		{	if (pObj->getName().indexOf( pLibObj->getName() ) == 0)	// SAC 4/25/14 - definitely return this object if the user object name equals or starts with the rule library object name
				pUserObj = pObj;
			else if (pUserObjDiffName == NULL)  // use the FIRST equivalent, if multiple found
				pUserObjDiffName = pObj;
			else if (				pObj->getName().indexOf( pLibObj->getName() ) > 0 &&
						pUserObjDiffName->getName().indexOf( pLibObj->getName() ) < 0)
				pUserObjDiffName = pObj;	// same objedct equivalence as previously found, but name more consistent, so make this one our fall-back
	}	}
   return pUserObj;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMProperty Class Function:  CopyAssignedObject()
//
// Purpose ------------------------------------------------------------------
//   Copies the object assigned to the m_obj and then re-assigns m_obj to
//   point to the newly created/copied object.  This is in place mainly to
//   handle the ruleset feature to ensure component assignment uniqueness.
//   
// Arguments ----------------------------------------------------------------
//    BOOL bLibToUser  : Flag indicating that we are copying a
//                       library component into a new user defined component
//                       because the user or ruleset is assigning a library
//                       component to a user defined component.
//
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////

static std::vector<BEMObject*> spaImportedRuleLibObjs;  // SAC 3/10/13 - keep track of imported rule library objects for use in defining parents of subordinate rule imports
static std::vector<BEMObject*> spaRuleLibObjsImported;  // SAC 3/11/13 - keep track of SOURCE rule library objects that have been imnported

void ClearRuleLibObjArrays()
{
	spaImportedRuleLibObjs.clear();  // SAC 3/10/13 - clear static array of rule lib imported object pointers before AND after use (just to be safe)
	spaRuleLibObjsImported.clear();  // SAC 3/10/13 - clear static array of rule lib imported object pointers before AND after use (just to be safe)
}
BEMObject* GetCorrespondingRuleLibObjectImportedThisRound( BEMObject* pLibObj )
{
	if (pLibObj && pLibObj->getClass() && !pLibObj->getName().isEmpty())
		if (spaRuleLibObjsImported.size() > 0)
		for (size_t iPO=spaRuleLibObjsImported.size(); iPO > 0; )
		{	if (	spaRuleLibObjsImported[--iPO] && spaRuleLibObjsImported[iPO]->getClass() &&
					spaRuleLibObjsImported[iPO]->getClass()->get1BEMClassIdx() == pLibObj->getClass()->get1BEMClassIdx() &&
					spaRuleLibObjsImported[iPO]->getName() == pLibObj->getName() )
				return spaImportedRuleLibObjs[iPO];
		}
	return NULL;
}
BEMObject* GetImportedRuleLibObjectParent( BEMObject* pNewObj )
{
	if (pNewObj && pNewObj->getClass())
		if (spaImportedRuleLibObjs.size() > 0)
		for (size_t iPO=spaImportedRuleLibObjs.size(); iPO > 0; )
		{	if (spaImportedRuleLibObjs[--iPO] && spaImportedRuleLibObjs[iPO]->getClass() && spaImportedRuleLibObjs[iPO]->getClass()->get1BEMClassIdx() > 0 && 
					pNewObj->getClass()->ClassInParentList( spaImportedRuleLibObjs[iPO]->getClass()->get1BEMClassIdx() ))
				return spaImportedRuleLibObjs[iPO];
		}
	return NULL;
}

// SAC 4/25/14 - switched prev BOOL bImportUniqueRuleLibObjects to int iImportUniqueRuleLibObjOption, w/ options:
//		0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
//		1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
//		2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
BEMObject* CopyComponentWithAssignments( BEMObject* pObj, BEMObject* pParentObj, BOOL bLibToUser, int iBEMProcIdx, 
														int iImportUniqueRuleLibObjOption, const char* pszImportRuleLibParentName )  // SAC 3/10/13   // SAC 3/17/13
{
   BEMObject* pNewObj = NULL;
   if (pObj)
   {
		if (iImportUniqueRuleLibObjOption == 1)
			pNewObj = GetCorrespondingRuleLibObjectImportedThisRound( pObj );  // SAC 3/11/13 - check for this rule lib object already imported during THIS round of imports to avoid unwanted duplicates

		// SAC 1/28/99 - Added to prevent unnecessary copying of library components to new user components when user copies
		//               of the library component already exist
      if (pNewObj == NULL && bLibToUser && (iImportUniqueRuleLibObjOption==0 || iImportUniqueRuleLibObjOption==2))  // SAC 3/10/13
		{	pNewObj = GetEquivalentUserObject( pObj );
			if (pNewObj)
			{	if (pNewObj->getName().indexOf( pObj->getName() ) == 0)
				{	}	// definitely use it if the object found has a name that equals or begins with the lib object name
				else if (iImportUniqueRuleLibObjOption == 2)
				{		// found a corresponding object, but name correspondence doesn't match w/ import option
					pNewObj = NULL;
		}	}	}

	// SAC 4/25/14 - if we are importing lib object such that we ensure name consistency w/ the library object, then we may need to RENAME an existing user object that already has the lib object name
		if (pNewObj == NULL && bLibToUser && iImportUniqueRuleLibObjOption==2)
		{	BEMObject* pUserObjBySameName = BEMPX_GetComponentByNameQ( pObj->getName(), FALSE /*bCheckLibsOnly*/, iBEMProcIdx,
																							TRUE /*bSkipCheckingRuleLib*/, FALSE /*bNameIsPrefix*/ );
			if (pUserObjBySameName && pUserObjBySameName->getClass())
			{	// need to RENAME this existing user object so that when we import the librayr object it can retain it's library name
				QString sNewName, sTryNewName = pUserObjBySameName->getName() + "-user";
				BOOL bNewNameOK = BEMPX_SetObjectCopyName( sNewName, sTryNewName.toLocal8Bit().constData(), TRUE /*bCheckFirst*/, iBEMProcIdx );			assert( bNewNameOK && !sNewName.isEmpty() );
				int iUserObjIdx = BEMPX_GetObjectIndex( pUserObjBySameName->getClass(), pUserObjBySameName, iBEMProcIdx );					assert( iUserObjIdx >= 0 );
				if (bNewNameOK && !sNewName.isEmpty() && iUserObjIdx >= 0)
				{	int iSetRetVal = BEMPX_SetBEMData( BEMPX_GetDBID( pUserObjBySameName->getClass()->get1BEMClassIdx(), 0, BEM_PARAM0_NAME ),
																	BEMP_QStr, (void*) &sNewName,  // BEMP_Str, (void*) ((const char*) sNewName.toLocal8Bit().constData()),
																	pUserObjBySameName->getObjectType() /*eObjType*/, iUserObjIdx, BEMS_UserDefined,
																	BEMO_User /*eObjType*/, TRUE /*bPerformResets*/, iBEMProcIdx );						assert( iSetRetVal >= 0 );
				}
		}	}

		int iError;
		if (pszImportRuleLibParentName && strlen( pszImportRuleLibParentName ) > 0)  // SAC 3/17/13
		{	// pszImportRuleLibParentName should OVERRIDE a default pParentObj (??)
			assert( pParentObj == NULL );
			assert( pObj && pObj->getClass() && pObj->getClass()->get1BEMClassIdx() > 0 );
			if (pObj && pObj->getClass() && pObj->getClass()->get1BEMClassIdx() > 0)
			{	BEMObject* pChkParObj = BEMPX_GetParentObjectByName( pObj->getClass()->get1BEMClassIdx(), iError, pszImportRuleLibParentName, BEMO_User, iBEMProcIdx );
				assert( pChkParObj || bLibToUser );  // SAC 6/13/13 - added '|| bLibToUser' since we DO expect parent here to be NULL in some cases, but that should get remedied below (when bLibToUser TRUE)
				if (pChkParObj)
					pParentObj = pChkParObj;
			}
		}

      if (pNewObj == NULL)
      {
			if (pParentObj == NULL && bLibToUser && pObj->getClass()->getParentType(0) >= 0)  // SAC 3/10/13 - if LibToUser and no parent specified and parent is Global object, then SET PARENT obj ptr
			{	if (pObj->getClass()->getParentType(1) < 0)
				{	BEMClass* pParClass = BEMPX_GetClass( pObj->getClass()->getParentType(0)+1, iError, iBEMProcIdx );
					if (pParClass && pParClass->getMaxDefinable() == 1)
					{	BEMObject* pChkParObj = BEMPX_GetObjectByClass( pObj->getClass()->getParentType(0)+1, iError, 0 /*iObjIdx*/, BEMO_User, iBEMProcIdx );
						if (pChkParObj)
							pParentObj = pChkParObj;
					}
				}
				if (pParentObj == NULL)		// if STILL NULL, then check through recently imported rule lib objects for a possible parent
					pParentObj = GetImportedRuleLibObjectParent( pObj );
			}

         QString sName;
         BOOL bSOCN = BEMPX_SetObjectCopyName( sName, pObj->getName().toLocal8Bit().constData(), TRUE, iBEMProcIdx );		bSOCN;
         // SAC 7/17/98 - Switched to always create "BEMO_User" objects, otherwise imports of Proposed or Budget
         //               designs fail since library components NOT written to .PBD and .BBD files
         pNewObj = BEMPX_CreateObject( pObj->getClass()->get1BEMClassIdx(), sName.toLocal8Bit().constData(), pParentObj, BEMO_User, FALSE, TRUE, iBEMProcIdx );
         if (pNewObj)
         {	if (bLibToUser)
				{	spaImportedRuleLibObjs.push_back( pNewObj );  // SAC 3/10/13 - archive objects imported from rule library for future parent reference access
					spaRuleLibObjsImported.push_back( pObj );  // SAC 3/11/13 - keep track of SOURCE rule library objects that have been imnported
				}

            // First copy the data from the pObj to the pNewObj
            if (BEMPX_CopyComponent( pNewObj, pObj, iBEMProcIdx ))
            {	int i;
               // Now, copy all of the copied object's children into the new object's children
               for (i=0; i < pObj->getChildCount(); i++)
               {	BEMObject* pChildObj = pObj->getChild(i);							assert( pChildObj );
                  if (pChildObj)
                     CopyComponentWithAssignments( pChildObj, pNewObj, bLibToUser, iBEMProcIdx,
															// SAC 4/25/14 - switched prev BOOL bImportUniqueRuleLibObjects to int iImportUniqueRuleLibObjOption
															//		bImportUniqueRuleLibObjects, pszImportRuleLibParentName );
																	iImportUniqueRuleLibObjOption, pszImportRuleLibParentName );
               }

               // Now, copy all assigned components which can only be referenced by a single component
					for (i=0; i < pObj->getPropertiesSize(); i++)
					{	BEMProperty* pProp = pObj->getProperty(i);						assert( pProp );
						// SAC 1/28/99 - added final !..getUniqueAssignment() check since if this flag is TRUE, then this component would have 
						//					  already been copied by BEMProperty::CopyProperty()
                  if ( pProp && pProp->getType() && (pProp->getType()->getPropType() == BEMP_Obj) && pProp->getObj() &&
                       pProp->getObj()->getClass() && !pProp->getObj()->getClass()->getUniqueAssignment() )
                  {
                     BEMObject* pNewAssignedObj = NULL;
							// SAC 1/28/99 - Added second portion of if check to prevent unnecessary copying of library components to new user components
							//               when user copies of the library component already exist
                     if (pProp->getObj()->getClass()->getMaxReferences() == 1 ||
                         (bLibToUser && (pProp->getObj()->getObjectType() == BEMO_RuleLib ||
                                         pProp->getObj()->getObjectType() == BEMO_UserLib)))
                     {
                        pNewAssignedObj = CopyComponentWithAssignments( pProp->getObj(), pProp->getObj()->getParent(), bLibToUser, iBEMProcIdx,
																					// SAC 4/25/14 - switched prev BOOL bImportUniqueRuleLibObjects to int iImportUniqueRuleLibObjOption
																					//			bImportUniqueRuleLibObjects, pszImportRuleLibParentName );
																								iImportUniqueRuleLibObjOption, pszImportRuleLibParentName );
                        if (!pNewAssignedObj)
                        {  assert( FALSE );  }  // error creating (or finding a copy of) new assigned object
                     }

                     if (pNewAssignedObj)  // object has been copied (or a user-defined copy of a library component has been found)
                     {
                        // now assign new object to equivalent property of NEW main object
                        long lAssignDBID = BEMPX_GetDBID( pProp->getType()->get1ClassIdx(), pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() );
                        if (BEMPX_SetBEMData( lAssignDBID, BEMP_Obj, (void*) pNewAssignedObj,
                                           BEMO_User, BEMPX_GetObjectIndex(  pNewObj->getClass(), pNewObj, iBEMProcIdx ),		// SAC 4/28/14 - added iBEMProcIdx to args passed
                                           BEMS_UserDefined, BEMO_User, TRUE, iBEMProcIdx ) < 0)
                        {  assert( FALSE );  }  // error assigning new object
                     }
                  }
               }
            }
         }
      }
   }
   return pNewObj;
}

//		0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
//		1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
//		2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
BEMObject* BEMPX_CopyComponentWithAssignments( BEMObject* pObj, BEMObject* pParentObj, BOOL bLibToUser, int iImportUniqueRuleLibObjOption,
																const char* pszImportRuleLibParentName, int iBEMProcIdx /*=-1*/ )  // SAC 10/14/15
{	return CopyComponentWithAssignments( pObj, pParentObj, bLibToUser, iBEMProcIdx, iImportUniqueRuleLibObjOption, pszImportRuleLibParentName );
}

// SAC 4/25/14 - switched prev BOOL bImportUniqueRuleLibObjects to int iImportUniqueRuleLibObjOption, w/ options:
//		0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
//		1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
//		2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
bool BEMProperty::CopyAssignedObject( BOOL bLibToUser, int iBEMProcIdx, int iImportUniqueRuleLibObjOption, const char* pszImportRuleLibParentName )  // SAC 3/10/13  // SAC 3/17/13
{
   if (m_type && m_type->getPropType() == BEMP_Obj && m_obj)
   {
		if (iBEMProcIdx < 0)
			iBEMProcIdx = eActiveBEMProcIdx;

// vvv TEMPORARY vvv
//      BEMMessageBox( QString( "Copying '%1'." ).arg( getObj()->getName() ), "", 3 /*error*/ );
// ^^^ TEMPORARY ^^^

		ClearRuleLibObjArrays();  // SAC 3/10/13 - clear static array of rule lib imported object pointers before AND after use (just to be safe)
      BEMObject* pNewObj = CopyComponentWithAssignments( m_obj, m_obj->getParent(), bLibToUser, iBEMProcIdx,
																			iImportUniqueRuleLibObjOption, pszImportRuleLibParentName );  // SAC 3/17/13
		ClearRuleLibObjArrays();  // SAC 3/10/13
      if (pNewObj)
      {
         m_obj = pNewObj;
         return TRUE;
      }
   }
   return FALSE;
}


// SAC 9/18/13 - added export of sequence to recursively import library objects into the user model
BEMObject* BEMPX_ImportLibraryObjectToUserModel( BEMObject* pLibObj, BOOL bImportUniqueRuleLibObjects, const char* pszImportRuleLibParentName, int iBEMProcIdx )
{
	BEMObject* pNewObj = NULL;
	if (pLibObj)
	{
		if (iBEMProcIdx < 0)  // SAC 3/13/13
			iBEMProcIdx = eActiveBEMProcIdx;

		ClearRuleLibObjArrays();  // SAC 3/10/13 - clear static array of rule lib imported object pointers before AND after use (just to be safe)
      pNewObj = CopyComponentWithAssignments( pLibObj, pLibObj->getParent(), TRUE /*bLibToUser*/, iBEMProcIdx,
																		// SAC 4/25/14 - revised use of bImportUniqueRuleLibObjects...
																		//		bImportUniqueRuleLibObjects, pszImportRuleLibParentName );  // SAC 3/17/13
																				(bImportUniqueRuleLibObjects ? 1 : 2), pszImportRuleLibParentName );  // SAC 3/17/13
		ClearRuleLibObjArrays();  // SAC 3/10/13
   }
	return pNewObj;
}


