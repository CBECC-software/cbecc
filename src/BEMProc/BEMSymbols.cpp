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

#include "stdafx.h"
#include <iostream>
#include "BEMProcObject.h"
#include "BEMSymbols.h"


/////////////////////////////////////////////////////////////////////////////
//
// Extern Function:  GetSymbolList()
//
// Purpose ------------------------------------------------------------------
//   To convert a database ID to a pointer to the corresponding symbol list.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID   : database ID of the property for which the symbol list is desired
//   
// Return Value -------------------------------------------------------------
//   NULL if a corresponding symbol list is not found, otherwise it returns
//   a pointer to the corresponding symbol list.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BEMSymbolList* GetSymbolList( long lDBID, BOOL* pbSymListArrayDependent /*=NULL*/ )
{
   if (pbSymListArrayDependent)
      *pbSymListArrayDependent = FALSE;

   int iError;
   BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
   if (iError >= 0 && pPropType)
   {
      if (pbSymListArrayDependent && pPropType->getSymbolList() && pPropType->getSymbolList()->getNumSymDependencySets() > 0)
         *pbSymListArrayDependent = pPropType->getSymbolList()->SymbolDepSetArrayDependent( lDBID, -1, BEMO_User );
      return pPropType->getSymbolList();
   }

   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// Function:  GetSymbolStringFromPtrs()
//
// Purpose ------------------------------------------------------------------
//   To return a symbol string from its corresponding numeric value and
//   pointers to the database object and property which it might be set to.
//   
// Arguments ----------------------------------------------------------------
//   long          iSymVal : numeric value of the desired symbol
//   BEMObject*   pObj    : pointer to the component which this symbol could be set to
//   BEMProperty* pProp   : pointer to the component's property which this symbol could be set to
//   
// Return Value -------------------------------------------------------------
//   NULL if the symbol was not found, otherwise a pointer to the LPCSTR of
//   the desired symbol.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
QString GetSymbolStringFromPtrs( long iSymVal, BEMObject* pObj, BEMProperty* pProp, int iBEMProcIdx /*=-1*/ )
{	QString sRet;
   if (pObj && pProp)
   {
		if (iBEMProcIdx < 0)  // SAC 3/13/13
			iBEMProcIdx = eActiveBEMProcIdx;

      // get the class, property type and array indices from the object and property pointers
      int i1Class = pObj->getClass()->get1BEMClassIdx();
      int i1Param = pProp->getType()->get1PropTypeIdx();
      int i1Array = pProp->get1ArrayIdx();
      // get the database ID from the class, property type, and array indices
      long lDBID = BEMPX_GetDBID( i1Class, i1Param, i1Array );
      // get the object occurrence index from pointers to the class and object
      int iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx );

      if (lDBID > 0 && iOccur >= 0)
      	sRet = BEMPX_GetSymbolString( iSymVal, lDBID, iOccur, pObj->getObjectType(), iBEMProcIdx );
   }
   return sRet;
}



/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetSymbolListIndices()
//
// Purpose ------------------------------------------------------------------
//   To populate the first and last index arguments with the first and last
//   symbol indices which can be used to describe a particular database property.
//   
// Arguments ----------------------------------------------------------------
//   int&       iFirstIndex : integer to populate with the FIRST desired symbol index
//   int&       iLastIndex  : integer to populate with the LAST desired symbol index
//   long       lDBID       : database ID of the property for which the available symbols are desired
//   int        iOccur      : occurence index of component to retrieve the symbol list for
//   BEM_ObjType eObjType    : type of component to retrieve the symbol list for
//   
// Return Value -------------------------------------------------------------
//    0 : OK
//   -1 : error - first and last indices NOT set because symbol list not found
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BEMSymDependencySet* BEMPX_GetSymbolListPointer(	int& iNumSymbols, long lDBID, int iOccur /*=-1*/, BEM_ObjType eObjType /*=BEMO_User*/,
																		int iBEMProcIdx /*=-1*/, BOOL* pbSymListArrayDependent /*=NULL*/ )
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   iNumSymbols = 0;
   if (pbSymListArrayDependent)
      *pbSymListArrayDependent = FALSE;

   // get the desired symbol list from lDBID
   BEMSymbolList* pSymList = GetSymbolList( lDBID );
   if (pSymList)
   {
      if (pbSymListArrayDependent && pSymList->getNumSymDependencySets() > 0)
         *pbSymListArrayDependent = pSymList->SymbolDepSetArrayDependent( lDBID, iOccur, eObjType, iBEMProcIdx );

      // get the desired symbol dep set from the symbol list and lDBID, iOccur & eObjType
      BEMSymDependencySet* pSymDepList = pSymList->GetSymbolDepSet( lDBID, iOccur, eObjType, iBEMProcIdx );
      if (pSymDepList)
      {  // if symbol dep set found, then set iNumSymbols and return pointer to CObList
         iNumSymbols = pSymDepList->getNumSymbols();
         return pSymDepList;
      }
   }
   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetSymbolString()
//
// Purpose ------------------------------------------------------------------
//   To return a symbol string from its corresponding numeric value and
//   the database property which it describes.
//   
// Arguments ----------------------------------------------------------------
//   int        iSymVal  : numeric value of the desired symbol
//   long       lDBID    : database ID of the property for which the available symbol is desired
//   int        iOccur   : occurence index of component to retrieve the symbol for
//   BEM_ObjType eObjType : type of component to retrieve the symbol for
//   
// Return Value -------------------------------------------------------------
//   NULL if the symbol was not found, otherwise a pointer to the LPCSTR of
//   the desired symbol.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
QString BEMPX_GetSymbolString(	long iSymVal, long lDBID, int iOccur, BEM_ObjType eObjType,
											int iBEMProcIdx /*=-1*/, BOOL bOnlyFromCurrentSymDepSet /*=TRUE*/ )
{
	QString sRet;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

	// get the desired symbol list from lDBID
	BEMSymbolList* pSymList = GetSymbolList( lDBID );
	if (pSymList)
		// get a pointer to the desired symbol from the symbol list and lDBID, iOccur, eObjType and symbol value
		sRet = pSymList->GetSymbolString( lDBID, iOccur, eObjType, iSymVal, iBEMProcIdx, bOnlyFromCurrentSymDepSet );

   // return NULL if SymboList not found
   return sRet;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetSymbolData()
//
// Purpose ------------------------------------------------------------------
//   Get pointers to both the symbol character string (return value) and the
//   symbol's numeric value (first argument) for a specific symbol.
//   
// Arguments ----------------------------------------------------------------
//   long& iSymValue : integer value to populate with the desired symbol's numeric value
//   int   iSymIdx   : 0-based index of the symbol to get the string and value for
//   
// Return Value -------------------------------------------------------------
//   NULL if the symbol was not found, otherwise a pointer to the LPCSTR of
//   the desired symbol.  (though not a return value, the first argument is also
//   set to the desired symbol's numeric value in order to be used by the calling
//   procedure following this function's return).
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetSymbolData( long& iSymValue, QString& sSymString, BEMSymDependencySet* pSymDepSet, int iSymIdx /*=0*/ )
{	int iRetVal = -1;
   iSymValue = 0;		sSymString.clear();
   // verify that the index provided is within the valid range of symbol indices
   if (pSymDepSet && iSymIdx >= 0 && iSymIdx < pSymDepSet->getNumSymbols())
   {
      BEMSymbol* pSym = pSymDepSet->getSymbol( iSymIdx );
      if (pSym)
      {
         iSymValue  = pSym->getValue();
         sSymString = pSym->getString();
         iRetVal = (int) sSymString.size();
      }
   }
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
void BEMPX_SymbolToRuleFile( QString& sString )
{
   int iRightParen = sString.lastIndexOf( ')' );
   int iLeftParen  = sString.lastIndexOf( '(' );
   if ( (iLeftParen >= 0) && (iLeftParen < iRightParen) )
      sString = sString.mid( iLeftParen+1, iRightParen-iLeftParen-1 );
   else
      sString.clear();
}



/////////////////////////////////////////////////////////////////////////////
// BEMSymbolList
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// BEMSymbolList Structure Function:  GetSymbolDepSet()
//
// Purpose ------------------------------------------------------------------
//   Gets a pointer to the BEMSymDependencySet which contains all symbols which
//   can currently be assigned to the database property identified by the arguments.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : database ID of the property for which the available SymDepSet is desired
//   int        iOccur   : occurence index of component to retrieve the SymDepSet for
//   BEM_ObjType eObjType : type of component to retrieve the SymDepSet for
//   
// Return Value -------------------------------------------------------------
//   NULL if symbol is not found, otherwise a pointer to the BEMSymDependencySet
//   which contains all valid symbols which may be assigned to the property
//   identified by the function arguments.
//   
// Notes --------------------------------------------------------------------
//   None
/////////////////////////////////////////////////////////////////////////////
BEMSymDependencySet* BEMSymbolList::GetSymbolDepSet(	long lDBID, int iOccur, BEM_ObjType eObjType,
																		int iBEMProcIdx /*=-1*/, int* pIdx /*=NULL*/ )
{
   BEMSymDependencySet* pRetVal = NULL;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   // loop over all entries in the m_olDepSets list of BEMSymDependencySet (until return value is set)
	int idx = -1;
	for (std::vector<BEMSymDependencySet>::iterator it = m_depSets.begin(); (pRetVal == NULL && it != m_depSets.end()); ++it)
	{	BEMSymDependencySet& sds = *it;
		idx++;
		if (sds.PassesDepChecks( lDBID, iOccur, eObjType, iBEMProcIdx ))
		{
			if (pIdx)
            *pIdx = idx;
         pRetVal = &sds;
      }
   }

   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
bool BEMSymbolList::SymbolDepSetArrayDependent( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = FALSE;
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;

   // loop over all entries in the m_depSets list of BEMSymDependencySet (until return value is set)
	for (std::vector<BEMSymDependencySet>::iterator it = m_depSets.begin(); (!bRetVal && it != m_depSets.end()); ++it)
	{	BEMSymDependencySet& sds = *it;

      // make sure pointer to BEMSymDependencySet is valid and check to see if it's 
      // dependency settings pass
      if (sds.HasArrayDependency( lDBID, iOccur, eObjType, iBEMProcIdx ))
         bRetVal = TRUE;
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymbolList Structure Function:  GetSymbolValue()
//
// Purpose ------------------------------------------------------------------
//   To get the numeric value associated with the symbol identified by the arguments
//   
// Arguments ----------------------------------------------------------------
//   long        lDBID    : database ID of the property for which the symbol value is desired
//   int         iOccur   : occurence index of component to retrieve the symbol value of
//   BEM_ObjType  eObjType : type of component to retrieve the symbol value of
//   const char* pSymStr  : the symbol's character string 
//   BOOL bOnlyFromCurrentSymDepSet : Flag defaulting to FALSE which (if TRUE) prevents
//                                    returning a symbol value from a SymDepSet other than
//                                    the currently selected one.
//   
// Return Value -------------------------------------------------------------
//   -999 : symbol not found    // SAC 3/14/02 - Switched "symbol not found" value from -1 to -999
//   Else : numeric value of the desired symbol
//   
// Notes --------------------------------------------------------------------
//   If the specified symbol is not found in the "current" BEMSymDependencySet,
//   then all other BEMSymDependencySets in the m_depSets are searched and the
//   first match found is returned.
//   
/////////////////////////////////////////////////////////////////////////////
long BEMSymbolList::GetSymbolValue( long lDBID, int iOccur, BEM_ObjType eObjType, const char* pSymStr,
                                     BOOL bOnlyFromCurrentSymDepSet, int iBEMProcIdx /*=-1*/ )
{
   long iRetVal = -999;  // Switched "symbol not found" value from -1 to -999
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   // get the current BEMSymDependencySet based on the lDBID, iOccur and eObjType arguments
   BEMSymDependencySet* pSymDepSet = GetSymbolDepSet( lDBID, iOccur, eObjType, iBEMProcIdx );
   if (pSymDepSet != NULL)
      iRetVal = pSymDepSet->GetSymbolValue( pSymStr );

   if (iRetVal == -999 && !bOnlyFromCurrentSymDepSet)  // SAC 3/14/02
   {  // if not found in list which was returned from GetSymbolDepSet(), try other symbol lists
		for (std::vector<BEMSymDependencySet>::iterator it = m_depSets.begin(); (iRetVal == -999 && it != m_depSets.end()); ++it)
		{	BEMSymDependencySet& sds = *it;
         if (&sds != pSymDepSet)
            iRetVal = sds.GetSymbolValue( pSymStr );
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymbolList Structure Function:  GetSymbolString()
//
// Purpose ------------------------------------------------------------------
//   Get the character string associated with the symbol which is available
//   to define the property identified by the first three arguments and has
//   the numeric value equal to the last argument.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : database ID of the property for which the symbol is desired
//   int        iOccur   : occurence index of component to retrieve the symbol of
//   BEM_ObjType eObjType : type of component to retrieve the symbol of
//   long       iSymVal  : numeric value associated with the desired symbol
//   
// Return Value -------------------------------------------------------------
//   NULL if the desired symbol is not found, otherwise a void pointer to the
//   character string which identifies the desired symbol.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
QString BEMSymbolList::GetSymbolString( long lDBID, int iOccur, BEM_ObjType eObjType, long iSymVal, int iBEMProcIdx /*=-1*/,
                                            BOOL bOnlyFromCurrentSymDepSet /*=TRUE*/ )  // SAC 3/13/01 - added final argument
{
   QString sRetVal;
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;

   // get the BEMSymDependencySet based on the lDBID, iOccur and eObjType arguments
   BEMSymDependencySet* pSymDepSet = GetSymbolDepSet( lDBID, iOccur, eObjType, iBEMProcIdx );
   if (pSymDepSet)
      sRetVal = pSymDepSet->GetSymbolString( iSymVal );

	// following section (based on BEMSymbolList::GetSymbolValue()) to get string REGARDLESS of what DepList it is in
   if (sRetVal.isEmpty()  &&  !bOnlyFromCurrentSymDepSet)
   {  // if not found in list which was returned from GetSymbolDepSet(), try other symbol lists
		for (std::vector<BEMSymDependencySet>::iterator it = m_depSets.begin(); (sRetVal.isEmpty() && it != m_depSets.end()); ++it)
		{	BEMSymDependencySet& sds = *it;
         if (&sds != pSymDepSet)
            sRetVal = sds.GetSymbolString( iSymVal );
      }
   }

   return sRetVal;
}


/////////////////////////////////////////////////////////////////////////////
BOOL BEMSymbolList::Copy( BEMSymbolList* pSymList )
{  assert( pSymList );
   BOOL bRetVal = TRUE;
   if (pSymList)
   {
      m_source = pSymList->m_source;
		if (pSymList->m_depSets.size() > 0)
		{
			try
			{
   			m_depSets = pSymList->m_depSets;	// std::vector should handle all the details
   			if (m_depSets.size() != pSymList->m_depSets.size())
					{	assert( FALSE );
						bRetVal = FALSE;
					}
			}
   		catch (std::exception& e)
   		{
				std::cout << "Warning: BEMSymbolList::Copy failed to create BEMSymDependencySet array because " << e.what() << '\n';
				bRetVal = FALSE;
			}
			catch (...)
			{
				std::cout << "Warning: BEMSymbolList::Copy failed to create BEMSymDependencySet array\n";
				bRetVal = FALSE;
			}
			if (!bRetVal && m_depSets.size() > 0)
				m_depSets.resize(0);
		}
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// BEMSymDependencySet
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  BEMSymDependencySet()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initializes data to zero.
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
BEMSymDependencySet::BEMSymDependencySet()
{
   for (int i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
   {
      m_compParam[i] = 0;
      m_comp[i]      = 0;
      m_dataType[i]  = 0;
      m_depValue[i]  = -1.0;
   }
   m_defaultValue = 0;    // in relation to global symbol list
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  ~BEMSymDependencySet()
//
// Purpose ------------------------------------------------------------------
//   Destructor
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
BEMSymDependencySet::~BEMSymDependencySet()
{
	m_symbols.resize(0);
}


BOOL BEMSymDependencySet::Copy( BEMSymDependencySet* pSymDepSet )
{  assert( pSymDepSet );
   BOOL bRetVal = TRUE;
   if (pSymDepSet)
   {
      int i=0;
      for (; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
      {
         m_compParam[ i ] = pSymDepSet->m_compParam[ i ];
         m_comp[      i ] = pSymDepSet->m_comp[      i ];
         m_dataType[  i ] = pSymDepSet->m_dataType[  i ];
         m_depValue[  i ] = pSymDepSet->m_depValue[  i ];
      }

      m_defaultValue = pSymDepSet->m_defaultValue;

		m_symbols.resize( pSymDepSet->m_symbols.size() );
		for (std::vector<BEMSymbol>::iterator it = pSymDepSet->m_symbols.begin(); (bRetVal && it != pSymDepSet->m_symbols.end()); ++it)
		{	BEMSymbol& sym = *it;

			BEMSymbol newSym( &sym );
			m_symbols.push_back( newSym );

   	   //   TRY
   	   //   {
   		//      pNewSym = new BEMSymbol( pSym );       assert( pNewSym );
         //      if (pNewSym)
         //         m_oaSymbols.Add( pNewSym );
         //      else
         //         bRetVal = FALSE;
   	   //   }
   	   //   CATCH_ALL(e)
   	   //   {
         //      bRetVal = FALSE;
      	//      TRACE0("Warning: BEMSymDependencySet::Copy() Symbol failed\n");
      	//      if (pNewSym)
      	//	      delete pNewSym;
   	   //   }
   	   //   END_CATCH_ALL
      }
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  Init()
//
// Purpose ------------------------------------------------------------------
//   Initializes all the Class members.
//   
// Arguments ----------------------------------------------------------------
//   int    iNumSymbols   : the number of symbols defined in this SymDepSet
//   int    iDefaultValue : the default symbol's value
//   int    iCompID       : the default component ID for the dependency info
//   LPCSTR lpszDepVar1   : the character string identifying the first component/parameter dependency
//   float  fDepVal1      : the value defined for the first component/parameter dependency
//   LPCSTR lpszDepVar2   : the character string identifying the second component/parameter dependency
//   float  fDepVal2      : the value defined for the second component/parameter dependency
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMSymDependencySet::Init( long iDefaultValue, // int iCompID,
                  	           LPCSTR lpszDepVar1, double dDepVal1,
                  	           LPCSTR lpszDepVar2, double dDepVal2,
                  	           LPCSTR lpszDepVar3, double dDepVal3 )
{
   // set the m_defaultValue member
   m_defaultValue = iDefaultValue;

   for (int i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
   {
      LPCSTR lpszDepVar = (i==0 ? lpszDepVar1 : (i==1 ? lpszDepVar2 : lpszDepVar3));
      double    dDepVal = (i==0 ?    dDepVal1 : (i==1 ?    dDepVal2 :    dDepVal3));

      // only set the first dependent comp/param data if the lpszDepVar1 != NULL
      if (lpszDepVar != NULL)
      {
         assert( (i < 1 || (m_compParam[0] > 0 && m_comp[0])) );
         assert( (i < 2 || (m_compParam[1] > 0 && m_comp[1])) );

         // first convert the lpszDepVar into a valid database ID
    //     QString sDepVar = lpszDepVar;
         m_compParam[i] = BEMPX_GetDatabaseID( lpszDepVar );	// sDepVar );

         assert( m_compParam[i] > 0 );

         // set the m_comp & m_dataType members based on the database ID
         m_comp[i]     = BEMPX_GetClassID(    m_compParam[i] );

         m_dataType[i] = BEMPX_GetDataType( m_compParam[i] );

         // set the m_depValue member
         m_depValue[i] = dDepVal;
      }
   }
} 


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  Init()
//
// Purpose ------------------------------------------------------------------
//   Initializes all the Class members.
//   
// Arguments ----------------------------------------------------------------
//   int  iDefaultValue : the default symbol's value
//   long   lDepVar1      : the DBID identifying the first component/parameter dependency
//   float  fDepVal1      : the value defined for the first component/parameter dependency
//   long   lDepVar2      : the DBID identifying the second component/parameter dependency
//   float  fDepVal2      : the value defined for the second component/parameter dependency
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMSymDependencySet::Init( long iDefaultValue, long lDepVar1, double dDepVal1, long lDepVar2, double dDepVal2, long lDepVar3, double dDepVal3 )
{
   // set the m_defaultValue member
   m_defaultValue = iDefaultValue;

// SAC 7/21/05 - Restructured code into loop over array of dependencies
   for (int i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
   {
      long   lDepVar = (i==0 ? lDepVar1 : (i==1 ? lDepVar2 : lDepVar3));
      double dDepVal = (i==0 ? dDepVal1 : (i==1 ? dDepVal2 : dDepVal3));

      // only set the first dependent comp/param data if lDepVar1 > 0
      if (lDepVar > 0)
      {
         m_compParam[i] = lDepVar;

         // set the m_lComp1 & m_iDataType1 members based on the database ID
         m_comp[i]     = BEMPX_GetClassID(     m_compParam[i] );
         m_dataType[i] = BEMPX_GetDataType( m_compParam[i] );

         // set the m_fDepVal1 member
         m_depValue[i] = dDepVal;
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  PassesDepChecks()
//
// Purpose ------------------------------------------------------------------
//   Determines whether or not the database's current values are such that
//   this BEMSymDependencySet can be used to describe the database parameter
//   identified by the function arguments.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : database ID of the property for which this dependency check is being performed
//   int        iOccur   : occurence index of component for which this dependency check is being performed
//   BEM_ObjType eObjType : type of component for which this dependency check is being performed
//   
// Return Value -------------------------------------------------------------
//   TRUE if the dependency checking members pass for the parameter identified
//   by the function arguments => this BEMSymDependencySet's symbols can be used
//   to describe this property.
//   Else, FALSE => dependency check failed.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMSymDependencySet::PassesDepChecks( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = TRUE;
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;
   long lLocalClass = BEMPX_GetClassID( lDBID );

// SAC 8/11/98 - Added code to match up array values if both incoming (lDBID) property AND
//               dep list (m_lCompParam*) property has the same size array
   int iLocalArray = BEMPX_GetArrayID( lDBID );

   // only check dependency #1 if m_lCompParam1 > 0 (m_lCompParam1 <= 0 means there is no dependency info)
// SAC 5/31/99 - Added code to allow a m_fDepValue* value of -999 serve as a wild card
// SAC 7/21/05 - Restructured code into loop over array of dependencies
   for (int i=0; (bRetVal && i<MAX_DEP_DBIDS_PER_SYMBOL_LIST); i++)
      if (m_compParam[i] > 0 && m_depValue[i] != -999)
      {
         // for global references, set iDepOccur = 0, else (for local) set iDepOccur = iOccur
         int iDepOccur = (m_comp[i] == lLocalClass) ? iOccur : 0;
         int iSpecialVal, iError;
         long lTempDBID = m_compParam[i];
         if (iLocalArray > 1)
         {  // if the PropertyType which corresponds to m_lCompParam1 has the same number of array values
            // as lDBID's, then setup lTempDBID to get same array value as lDBID corresponds to
            BEMPropertyType* pPT1 = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
            BEMPropertyType* pPT2 = BEMPX_GetPropertyTypeFromDBID( m_compParam[i], iError );
            if (pPT1 && pPT2 && pPT1->getNumValues() == pPT2->getNumValues())
               lTempDBID += (iLocalArray-1);
         }

			int iDataType = BEMPX_GetDataType( lTempDBID );
			if (iDataType < 0)
				bRetVal = FALSE;
			else if (m_dataType[i] == BEMP_Int || m_dataType[i] == BEMP_Sym || m_dataType[i] == BEMP_Flt)
			{	if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
				{	long lData = BEMPX_GetInteger( lTempDBID, iSpecialVal, iError, iDepOccur, eObjType, iBEMProcIdx );
					if (iError < 0 || lData != (long) m_depValue[i])  // SAC 8/30/16 - added iError check to ensure retrieval error prevents success
						bRetVal = FALSE;
				}
				else if (iDataType == BEMP_Flt)
				{	double dData = BEMPX_GetFloat( lTempDBID, iSpecialVal, iError, iDepOccur, eObjType, iBEMProcIdx );
					if (dData != m_depValue[i])
						bRetVal = FALSE;
				}
				else
					bRetVal = FALSE;	// invalid comparison type
			}
         else  // return FALSE if retrieved data not of type Int, Sym or Flt
            bRetVal = FALSE;
      }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// This function based on code provided in the previous function
bool BEMSymDependencySet::HasArrayDependency( long lDBID, int iOccur, BEM_ObjType /*eObjType*/, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = FALSE;
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;
   long lLocalClass = BEMPX_GetClassID( lDBID );

   // only check dependency #1 if m_lCompParam1 > 0 (m_lCompParam1 <= 0 means there is no dependency info)
// SAC 5/31/99 - Added code to allow a m_fDepValue* value of -999 serve as a wild card
// SAC 7/21/05 - switched all references to dep members -> new array members
   if (m_compParam[0] > 0 && m_depValue[0] != -999)
   {
      // for global references, set iDepOccur = 0, else (for local) set iDepOccur = iOccur
      int iDepOccur = (m_comp[0] == lLocalClass) ? iOccur : 0;
      int iError;
      // if the PropertyType which corresponds to m_lCompParam1 has the same number of array values
      // as lDBID's, then setup lTempDBID to get same array value as lDBID corresponds to
      BEMPropertyType* pPT1 = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
      BEMPropertyType* pPT2 = BEMPX_GetPropertyTypeFromDBID( m_compParam[0], iError );
      if (pPT1 && pPT2 && pPT1->getNumValues() > 1 && pPT1->getNumValues() == pPT2->getNumValues())
         bRetVal = TRUE;
      else if (pPT1)
         for (int i=1; (!bRetVal && i<MAX_DEP_DBIDS_PER_SYMBOL_LIST); i++)  // SAC 7/21/05 - Added loop to facilitate mods to num deps
         {
            // for global references, set iDepOccur = 0, else (for local) set iDepOccur = iOccur
            iDepOccur = (m_comp[i] == lLocalClass) ? iOccur : 0;
            // if the PropertyType which corresponds to m_lCompParam1 has the same number of array values
            // as lDBID's, then setup lTempDBID to get same array value as lDBID corresponds to
            pPT2 = BEMPX_GetPropertyTypeFromDBID( m_compParam[i], iError );
            if (pPT2 && pPT1->getNumValues() > 1 && pPT1->getNumValues() == pPT2->getNumValues())
               bRetVal = TRUE;
         }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMSymDependencySet Class Function:  GetSymbolValue()
//
// Purpose ------------------------------------------------------------------
//   Get the value of the symbol contained in this BEMSymDependencySet whose
//   character string matches that of the function argument.
//   
// Arguments ----------------------------------------------------------------
//   const char* pSymStr  : the string identifying the symbol for which the value is sought
//   
// Return Value -------------------------------------------------------------
//   -999 : symbol not found  // SAC 3/14/02 - Switched "symbol not found" value from -1 to -999
//   Else : numeric value of the desired symbol
//   
// Notes --------------------------------------------------------------------
//   The string comparison is NOT case sensitive.
//   
/////////////////////////////////////////////////////////////////////////////
long BEMSymDependencySet::GetSymbolValue( const char* pSymStr )
{
	int iRetVal = -999;
   QString sSymStr = pSymStr;
	for (std::vector<BEMSymbol>::iterator it = m_symbols.begin(); it != m_symbols.end(); ++it)
	{	BEMSymbol& sym = *it;
      // check for (case-insensitive) symbol string match
		if (sSymStr.compare( sym.getString(), Qt::CaseInsensitive ) == 0)
      {
         // Switched "symbol not found" value from -1 to -999
         assert( sym.getValue() != -999 );  // assert() to prevent case where symbol value == -999 => Not Found
         iRetVal = sym.getValue();
         break;
      }
   }
   return iRetVal;
}

QString BEMSymDependencySet::GetSymbolString( long iSymVal )
{
	QString sRetVal = "";
	for (std::vector<BEMSymbol>::iterator it = m_symbols.begin(); it != m_symbols.end(); ++it)
	{	BEMSymbol& sym = *it;
      // check for symbol value match
		if (iSymVal == sym.getValue())
		{	sRetVal = sym.getString();
			break;
	}	}
	return sRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//SAC - 2/27/98 - New Function
/////////////////////////////////////////////////////////////////////////////
BEMSymbol* BEMSymDependencySet::CreateBEMSymbol( long iSymValue, LPCSTR lpszSymString )
{
	try
	{
		BEMSymbol sym( iSymValue, lpszSymString );
      m_symbols.push_back( sym );
      return &(m_symbols.back());
	}
	catch (std::exception& e)
	{
		std::cout << "Warning: BEMSymbolList::CreateBEMSymDepSet() failed because " << e.what() << '\n';
	}
   catch (...)
   {
   	std::cout << "Warning: BEMSymbolList::CreateBEMSymDepSet() failed\n";
   }
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// prevent the ruleset from overwriting symbols tagged by the
// simulation module as ones which should not be.
/////////////////////////////////////////////////////////////////////////////
static BOOL OKToOverwriteSymbol( long lDBID )
{
//   int iArraySize = (int) eBEMProc.m_symbolsNotToOverwrite.size();
//   for (int i=0; i<iArraySize; i++)
//   {
//      if (eBEMProc.m_symbolsNotToOverwrite[i] == lDBID)
//         return FALSE;
//   }
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// enable rule processor to override BEMProc symbol definitions based
// on the contents of the compliance ruleset being loaded
/////////////////////////////////////////////////////////////////////////////
void* BEMPX_OverwriteSymbolList( long lDBID, int iSource )
{
   if (iSource == BEMS_ProgDefault || OKToOverwriteSymbol( (DWORD) lDBID ))
   {
      BEMSymbolList* pSymList = GetSymbolList( lDBID );
      if (pSymList)
         pSymList->Init( iSource );

      return (void*) pSymList;
   }
   return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// enable rule processor to override BEMProc symbol definitions based
// on the contents of the compliance ruleset being loaded
/////////////////////////////////////////////////////////////////////////////
void* BEMPX_AddSymbolDepList( void* pvBEMSymList, long iDefaultVal, long lDBID1, double fDepVal1, long lDBID2, double fDepVal2, long lDBID3, double fDepVal3 )
{
   BEMSymbolList* pSymList = (BEMSymbolList*) pvBEMSymList;
   if (pSymList)
   {
   	return pSymList->addSymDependencySet( iDefaultVal, lDBID1, fDepVal1, lDBID2, fDepVal2, lDBID3, fDepVal3  );
//      BEMSymDependencySet* pSymDepSet = NULL;
//      try
//      {  // allocate new BEMSymDependencySet
//         pSymDepSet = new BEMSymDependencySet();			assert( pSymDepSet );
//
//         // initialize BEMSymDependencySet members
//         pSymDepSet->Init( iDefaultVal, lDBID1, fDepVal1, lDBID2, fDepVal2, lDBID3, fDepVal3 );
//
//         // add BEMSymDependencySet to the end of this member's m_oaDepSets array
//         pSymList->addSymDependencySet( pSymDepSet );
//
//         return (void*) pSymDepSet;
//      }
//		catch (std::exception& e)
//		{	std::cout << "Warning: BEMPX_AddSymbolDepList() failed because " << e.what() << '\n';
//		}
//	 	catch (...)
//	  	{  std::cout << "Warning: BEMPX_AddSymbolDepList() failed.\n";
//	  	}
//      if (pSymDepSet != NULL)
//         delete pSymDepSet;
   }
   return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// enable rule processor to override BEMProc symbol definitions based
// on the contents of the compliance ruleset being loaded
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_AddSymbol( void* pvBEMSymDepList, long iSymVal, const char* pszSymString )
{
   BEMSymDependencySet* pSymDepSet = (BEMSymDependencySet*) pvBEMSymDepList;
   if (pSymDepSet)
   {
	   BEMSymbol* pSym = pSymDepSet->CreateBEMSymbol( iSymVal, (LPCSTR) pszSymString );
      return (pSym != NULL);
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// SAC - 11/27/98 - Added to allow ruleset to default a symbolic value of the
//                  current value does not exist for the symbol list.
/////////////////////////////////////////////////////////////////////////////
// SAC 8/11/06 - added bReturnDefaultSymVal argument to enable return of (0/1) indicating whether or not existing symbol value maps to a valid symbol string
long BEMPX_GetDefaultSymbolIfInvalid( long lDBID, int iOccur, BEM_ObjType eObjType, BOOL bReturnDefaultSymVal /*=TRUE*/, int iBEMProcIdx /*=-1*/ )
{
   // get the desired symbol list from lDBID
   BOOL bSymValOK = FALSE;
   long lSymVal = -1;
   BEMSymbolList* pSymList = GetSymbolList( lDBID );
   if (pSymList)
   {
//      int iDataType, iSpecVal, iError;
//      // retrieve the data stored in the database
//      void* pData = BEMPX_GetBEMData( lDBID, iDataType, iSpecVal, iError, iOccur, eObjType, FALSE, iBEMProcIdx );
//      // if data retrieved successfully AND the data is a symbolic value, then...
//      if ( iError >= 0 && pData && iDataType == BEMP_Sym )
//      {
//         lSymVal = *((long*) pData);
		if (BEMPX_GetDataType( lDBID ) == BEMP_Sym)
		{
			int iSpecVal, iError;
			lSymVal = BEMPX_GetInteger( lDBID, iSpecVal, iError, iOccur, eObjType, iBEMProcIdx );

         // get a pointer to the desired symbol from the symbol list and lDBID, iOccur, eObjType and symbol value
         QString sSymStr = pSymList->GetSymbolString( lDBID, iOccur, eObjType, (int) lSymVal, iBEMProcIdx );
         if (!sSymStr.isEmpty())
            bSymValOK = TRUE;
      }

      if (!bReturnDefaultSymVal)  // SAC 8/11/06 - added if statement to enable boolean return (0/1) indicating whether or not existing symbol value maps to a valid symbol string
      {
         lSymVal = (bSymValOK ? 1 : 0);
      }
      else if (!bSymValOK)
      {  // error retrieving value OR the value doesn't correspond to a valid symbol entry
         // => reset symbol value to the default for this symbol list
         BEMSymDependencySet* pSymDepSet = pSymList->GetSymbolDepSet( lDBID, iOccur, eObjType, iBEMProcIdx );
         if (pSymDepSet && pSymDepSet->getDefaultValue() >= 0)
            lSymVal = pSymDepSet->getDefaultValue();
      }
   }

   return lSymVal;
}


/////////////////////////////////////////////////////////////////////////////




