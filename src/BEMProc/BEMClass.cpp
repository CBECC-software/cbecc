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
#include "BEMProc.h"
#include "BEMClass.h"
#include "BEMProcObject.h"
#include "expTextIO.h"
#include "expCrypFile.h"


/////////////////////////////////////////////////////////////////////////////
// BEMClass
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMClass Class Function:  BEMClass()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initializes the BEMClass instance to zeroes.
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
BEMClass::BEMClass()
{
	clear();
}

BEMClass::~BEMClass()
{
	clear();
}

void BEMClass::clear()
{
	m_shortName.clear();
	m_longName.clear();
   m_defaultName.clear();
   m_numProps			= 0;
   m_maxDefinable	= 0;
   m_maxReferences  = 0;
   m_maxSimComps    = 0;
   m_maxChildren    = -1;
	m_autoCreate     = 0;
   m_bldgPtrIdx		= 0;
   m_firstPropID		= 0;
	m_helpID			= 0;

   m_1BEMClassIdx     = 0;
	m_1MirrorClassIdx  = 0;
	m_mirrorClassName.clear();
   m_currentBEM0ObjIdx = 0;
   m_currentBEMObjType = BEMO_User;
   m_currentParent   = NULL;

   m_uniqueAssignment = FALSE;
	m_uniqueAssignArray.clear();

   m_purgeUnrefCompsBeforeSim = FALSE;
   m_objectCopyFlag = 0;
	m_writeAsSingleRecord = FALSE;
	m_XMLIgnoreName = FALSE;
	m_defaultNameTemplate.clear();

	int i=0;
	for (; i < BEM_MAX_PARENT_TYPES; i++)
	{	m_parentType[i] = -1;
		m_parentTypeStr[i].clear();
	}
	for (i=0; i < BEM_MAX_CHILD_TYPES; i++)
		m_childType[i] = -1;
	m_numChildTypes = 0;

	for (int iOT=0; iOT<3; iOT++)		// delete all objects of each type
	{	std::vector<BEMObject*>* pObjs = NULL;
		switch (iOT)
		{	case  0 :	pObjs = &m_bdObjects;
			case  1 :	pObjs = &m_rlObjects;
			case  2 :	pObjs = &m_ulObjects;
		}					assert( pObjs );
		if (pObjs)
		{	for (int i = (int) pObjs->size()-1; i >= 0; i--)
			{	assert( pObjs->at(i) );
				if (pObjs->at(i))
					delete pObjs->at(i);
			}
			pObjs->clear();
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL BEMClass::Copy( BEMClass* pClass, BOOL bCopyObjects /*=TRUE*/ )
{  assert( pClass );
   BOOL bRetVal = TRUE;
   if (pClass)
   {
      m_shortName                 = pClass->m_shortName;
      m_longName                  = pClass->m_longName;
      m_defaultName               = pClass->m_defaultName;
      m_numProps                  = pClass->m_numProps;
      m_maxDefinable              = pClass->m_maxDefinable;
      m_maxReferences             = pClass->m_maxReferences;
      m_maxSimComps               = pClass->m_maxSimComps;
      m_maxChildren               = pClass->m_maxChildren;
      m_autoCreate                = pClass->m_autoCreate;
      m_bldgPtrIdx                = pClass->m_bldgPtrIdx;
      m_firstPropID               = pClass->m_firstPropID;
      m_helpID                    = pClass->m_helpID;

      m_1BEMClassIdx              = pClass->m_1BEMClassIdx;
		m_1MirrorClassIdx           = pClass->m_1MirrorClassIdx;
		m_mirrorClassName           = pClass->m_mirrorClassName;
      m_currentBEM0ObjIdx         = pClass->m_currentBEM0ObjIdx;
      m_currentBEMObjType         = pClass->m_currentBEMObjType;
      m_currentParent             = NULL;   // SAC 3/26/07 - was: pClass->m_currentParent;

      m_uniqueAssignment          = pClass->m_uniqueAssignment;
      m_uniqueAssignArray         = pClass->m_uniqueAssignArray;

      m_purgeUnrefCompsBeforeSim  = pClass->m_purgeUnrefCompsBeforeSim;
      m_objectCopyFlag            = pClass->m_objectCopyFlag;

		m_writeAsSingleRecord       = pClass->m_writeAsSingleRecord;
		m_XMLIgnoreName             = pClass->m_XMLIgnoreName;
		m_defaultNameTemplate       = pClass->m_defaultNameTemplate;

		int i=0;
      for (; i < BEM_MAX_PARENT_TYPES; i++)
		{	m_parentType[i]    = pClass->m_parentType[i];
			m_parentTypeStr[i] = pClass->m_parentTypeStr[i];
		}
      for (i=0; i < BEM_MAX_CHILD_TYPES; i++)
         m_childType[i] = pClass->m_childType[i];
		m_numChildTypes = pClass->m_numChildTypes;

      if (bCopyObjects)  // SAC 3/19/13 - added 
		{	
			for (i=0; (bRetVal && i < 3); i++)
			{
				std::vector<BEMObject*>* pFromObjVector = NULL;
				std::vector<BEMObject*>* pToObjVector = NULL;
				switch (i)
				{	case 0 :		pFromObjVector = &pClass->m_bdObjects;		pToObjVector = &m_bdObjects;		break;
					case 1 :		pFromObjVector = &pClass->m_rlObjects;		pToObjVector = &m_rlObjects;		break;
					case 2 :		pFromObjVector = &pClass->m_ulObjects;		pToObjVector = &m_ulObjects;		break;
				}
				for (int ib=0; (bRetVal && ib < (int) pFromObjVector->size()); ib++)
				{	BEMObject* pFromObj = (BEMObject*) &pFromObjVector->at(ib);			assert( pFromObj );
					if (pFromObj == NULL)
						bRetVal = FALSE;
					else
					{
						BEMObject* pToObj = NULL;
						try
						{  // allocate new object
							pToObj = new BEMObject();							assert( pToObj );
							if (pToObj && pToObj->CopyAllButPropertiesAndChildren( pFromObj, this ))
								pToObjVector->push_back( pToObj );
							else
								bRetVal = FALSE;
						}
						catch (std::exception& e)
						{	std::cout << "Warning: BEMClass::Copy failed to create BEMObject because " << e.what() << '\n';
						}
					 	catch (...)
					  	{  std::cout << "Warning: BEMClass::Copy failed to create BEMObject\n";
					  	}
				}	}
      	}
		}
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMClass Class Function:  CreateBEMObject()
//
// Purpose ------------------------------------------------------------------
//   Create a new bldg component of a particular component type (BEMClass).
//   
// Arguments ----------------------------------------------------------------
//   QString sName        : Name of the new object to be created - this name must
//                          be unique across all other bldg component names
//   BEM_ObjType objType   : (default = BEMO_User) Object type
//   BEMObject* pParent   : (default = NULL) Pointer to parent object
//   BOOL bDefaultParent  : (default = TRUE) TRUE only if the default parent for this
//                          component type is to be installed as this object's parent
//   BOOL bAutoCreate     : (default = TRUE) TRUE only if all referenced classes which
//                          are tagged as AutoCreate should be created automatically
//   
// Return Value -------------------------------------------------------------
//   NULL if an error occurred when creating the new object, otherwise a pointer
//   to the newly created object (building component).
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* BEMClass::CreateBEMObject( QString sName, BEM_ObjType objType /* = BEMO_User */, 
                                     BEMObject* pParent /* = NULL */, bool bDefaultParent /* = TRUE */,
                                     bool bAutoCreate /* = TRUE */, int iBEMProcIdx /* = -1 */, BOOL bIgnoreMaxDefinable /*=FALSE*/,
                                     int i0ChildIdx /*=-1*/ )  // SAC 5/29/14 - added i0ChildIdx in place of BOOL bMakeFirstChild = FALSE );
{
   // get the current count of the number of objects of the desired type already created
   int iCurCount = ObjectCount(objType);
   if (iCurCount == -1)
		return NULL;   // abort if the objType doesn't match the above selections

	if ( !bIgnoreMaxDefinable && objType == BEMO_User && m_maxDefinable > 0 && iCurCount >= m_maxDefinable )  // SAC 1/23/12 - enable m_maxDefinable==0 to enable unlimited creations
		return NULL;   // abort if we cannot create and more user defined objects of this type

	// what about if the combination of user defined and user referenced library objects exceeds the m_maxDefinable ???

	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

	// TO DO: Deal with ParentType/ChildType checks
	
	BEMObject* pObject = NULL;
	try
	{
      // allocate new object
		pObject = new BEMObject( sName, objType, this );												assert( pObject );

		if (pObject)
      {	// if this class is to have no parent, then set the parent pointer to NULL
	      if (m_parentType[0] >= 0)
	      {
	         // set parent pointer
	   	   if (objType == BEMO_User && pParent == NULL && bDefaultParent)
	   	   	pObject->setParent( m_currentParent );
	         else
	            pObject->setParent( pParent );
	      }

	   	// compute size of property array - properties which will describe this new object
	   	int prop, iPIdx = -1, iNumProps = 0;
			for (prop = 0; prop < m_numProps; prop++)
			{	BEMPropertyType* pPropType = pBEMProc->getPropertyType( prop + m_firstPropID );		assert( pPropType );
				iNumProps += (pPropType == NULL ? 0 : pPropType->getNumValues());
			}	assert( iNumProps >= 0 );
			pObject->initProperties( iNumProps );
			bool bPropsOK = true;
			for (prop = 0; (bPropsOK && prop < m_numProps); prop++)
			{	BEMPropertyType* pPropType = pBEMProc->getPropertyType( prop + m_firstPropID );		assert( pPropType );
	         for (int iArr = 0; (bPropsOK && pPropType && iArr < pPropType->getNumValues()); iArr++)
	   	//		obj.m_properties.push_back( pBEMProc->m_pPropTypes[ prop + m_firstPropID ]->CreateBEMProperty( iArr ) );
				{	bPropsOK = pObject->initProperty( ++iPIdx, pPropType, iArr );							assert( bPropsOK );
				}
			}

	      // add this object to it's parent's child list
			if (pObject->haveParent())
	      {	pObject->addChildToParent( i0ChildIdx );
	
			// Not sure what the potential ramifications might be in the below code if the max is reached and the newly
			// created object has been added to the head of the parent's m_children CObList
	         // if the parent object is the m_currentParent AND this parent can't accept any more children
	         // of this type, then reassign the m_currentParent pointer
	         if (pObject->getClass() && pObject->getParent() == pObject->getClass()->m_currentParent &&
	             !BEMPX_CanCreateAnotherChildObject( pObject->getClass()->m_1BEMClassIdx, pObject->getParent(), 1, iBEMProcIdx ))
	            ResetCurrentParentPointers( pObject->getParent(), pObject->getClass()->m_1BEMClassIdx, iBEMProcIdx );
	      }

	      // add this object to the appropriate list of objects
	      switch ( objType )
	      {	case BEMO_User    :	m_bdObjects.push_back( pObject );		break;
				case BEMO_RuleLib :	m_rlObjects.push_back( pObject );		break;
				case BEMO_UserLib :	m_ulObjects.push_back( pObject );		break;
				default :	assert( false );		break;
	      }

	      // make this new object the "current" object => this one will be "Active"
	      BEMPX_SetActiveObjectIndex( m_1BEMClassIdx, iCurCount, objType, iBEMProcIdx );
	      // default the property values which describe this object
	      BOOL bDefOK = pObject->DefaultObject( iCurCount, TRUE, 0, BEMS_Undefined, FALSE, iBEMProcIdx );		bDefOK;

	      // create any referenced objects which are tagged as AutoCreate
	      if (objType == BEMO_User && bAutoCreate)
	   	   pObject->AutoCreateReferences( iBEMProcIdx );

//#ifdef _DEBUG
//	      int iNewCount = ObjectCount(objType);
//	      if (m_maxDefinable > 0 && iNewCount == m_maxDefinable && iNewCount > 11)  // SAC 1/23/12 - enable m_maxDefinable==0 to enable unlimited creations
//	         BEMMessageBox( QString( "Creating the last possible component (%1) of type %2." ).arg( QString::number(iNewCount), obj.m_pClass->m_longName ), "", 3 /*error*/ );
//#endif

			return pObject;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Warning: BEMClass::CreateBEMObject failed to create object because " << e.what() << '\n';
	}
 	catch (...)
  	{
	   std::cout << "Warning: BEMClass::CreateBEMObject failed to create object\n";
  	}
  	if (pObject)
  		delete pObject;

	return NULL;
}


void BEMClass::AddObject( BEMObject* pObj, BEM_ObjType objType /*=BEMO_User*/ )
{
	if (pObj)
	{	// add this object to the appropriate list of objects
		switch ( objType )
		{	case BEMO_User    :	m_bdObjects.push_back( pObj );		break;
			case BEMO_RuleLib :	m_rlObjects.push_back( pObj );		break;
			case BEMO_UserLib :	m_ulObjects.push_back( pObj );		break;
			default :	assert( false );		break;
		}
	}
	else
	{	assert( false );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMClass Class Function:  RemoveObjects()
//
// Purpose ------------------------------------------------------------------
//   Deletes all the objects of a particular type
//   
// Arguments ----------------------------------------------------------------
//   BEM_ObjType eObjType  : the type of object which we want to delete all instances of
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMClass::RemoveObjects( BEM_ObjType eObjType, bool bDeleteObjects /*=true*/ )
{
	std::vector<BEMObject*>* pObjs = NULL;
	switch (eObjType)
	{	case  BEMO_User    :	pObjs = &m_bdObjects;	break;
		case  BEMO_RuleLib :	pObjs = &m_rlObjects;	break;
		case  BEMO_UserLib :	pObjs = &m_ulObjects;	break;
	}					assert( pObjs );
	if (pObjs)
	{	if (bDeleteObjects)
		{	for (int i = (int) pObjs->size()-1; i >= 0; i--)
			{	assert( pObjs->at(i) );
				if (pObjs->at(i))
					delete pObjs->at(i);
		}	}
		pObjs->clear();
	}
}

bool BEMClass::RemoveObject( BEM_ObjType eObjType, int iObjIdx )
{	bool bRetVal = false;
	std::vector<BEMObject*>* pObjs = NULL;
	switch (eObjType)
	{	case  BEMO_User    :	pObjs = &m_bdObjects;	break;
		case  BEMO_RuleLib :	pObjs = &m_rlObjects;	break;
		case  BEMO_UserLib :	pObjs = &m_ulObjects;	break;
	}					assert( pObjs );
   if (pObjs && iObjIdx >= 0 && iObjIdx < (int) pObjs->size())
   {	int iThisObjIdx = -1;
		for (std::vector<BEMObject*>::iterator it = pObjs->begin(); it != pObjs->end(); ++it)
		{	if (++iThisObjIdx == iObjIdx)
			{	pObjs->erase( it );
				bRetVal = true;
				break;
		}	}
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int BEMClass::ObjectCount( BEM_ObjType eObjType )
{  int iRetVal = -1;
   switch ( eObjType )
   {
      case BEMO_User    :  iRetVal = m_bdObjects.size();   break;
      case BEMO_RuleLib :  iRetVal = m_rlObjects.size();   break;
      case BEMO_UserLib :  iRetVal = m_ulObjects.size();   break;
   }  
   return iRetVal;
}

BEMObject* BEMClass::GetObject( BEM_ObjType eObjType, int iObjIdx )
{	BEMObject* pRetVal = NULL;
   switch ( eObjType )
   {
      case BEMO_User    :  pRetVal = m_bdObjects.at(iObjIdx);   break;
      case BEMO_RuleLib :  pRetVal = m_rlObjects.at(iObjIdx);   break;
      case BEMO_UserLib :  pRetVal = m_ulObjects.at(iObjIdx);   break;
   }  
   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL BEMClass::ClassInParentList( int i1ParentClass )
{
   for (int iPar=0; iPar<BEM_MAX_PARENT_TYPES; iPar++)
      if (m_parentType[iPar] == i1ParentClass-1)
         return TRUE;
   return FALSE;
}

void BEMClass::SetParentChildTypesFromStrings()
{	int iError;
	for (int i=0; i<BEM_MAX_PARENT_TYPES; i++)
	{	m_parentType[i] = (m_parentTypeStr[i].isEmpty() ? 0 : BEMP_GetDBComponentID( m_parentTypeStr[i] )) - 1;	// SAC 8/31/16 - adjusted so these comp IDs are 0-based
		if (m_parentType[i] >= 0)
		{	BEMClass* pParCls = BEMPX_GetClass( m_parentType[i]+1, iError );				assert( pParCls );
			if (pParCls)
			{	if (!pParCls->addChildType( m_1BEMClassIdx-1 ))
				{	assert( false );
			}	}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
int BEMClass::GetChildClassID( const char* pszChildClassName )	// SAC 8/15/12
{
	int iClassID = BEMPX_GetDBComponentID( pszChildClassName );
	if (iClassID > 0)
	{	for (int iChld=0; iChld<BEM_MAX_CHILD_TYPES; iChld++)
	      if (m_childType[iChld] == iClassID-1)
	         return iClassID;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////

void BEMClass::ReadText( BEMTextIO& file, int iFileVersion )
{
   m_shortName = file.ReadString();   file.PostReadToken();
   m_longName  = file.ReadString();   file.PostReadToken();

   if (iFileVersion >= 2)  // SAC 1/24/12
	{  m_defaultName	= file.ReadString();				file.PostReadToken();  // SAC 1/24/12 - (file ver 2) added to specify a template for defaulting new component names 
	}

   m_maxDefinable  =       file.ReadLong();   file.PostReadToken();
   m_maxReferences = (int) file.ReadLong();   file.PostReadToken();
   m_autoCreate    = (int) file.ReadLong();   file.PostReadToken();

//   if (iFileVersion >= 3)  // SAC 7/25/02 - Added code to read in new "MirrorClassName" member
//   {
//      m_sMirrorClassName = file.ReadString();   file.PostReadToken();
//   }

   for (int i=0; i<BEM_MAX_PARENT_TYPES; i++)
   {	if (i < 5 || iFileVersion >= 2)	// SAC 1/24/12 - maintain compatibility w/ BEMBase.txt files that list only 5 parent types
      {	m_parentTypeStr[i] = file.ReadString();
      	file.PostReadToken();
		}
   }

   m_maxChildren = (int) file.ReadLong();
   file.PostReadToken();
   m_maxSimComps = (int) file.ReadLong();
   file.PostReadToken();
   m_purgeUnrefCompsBeforeSim = (BOOL) file.ReadLong();
   file.PostReadToken();

   if (iFileVersion >= 2)  // SAC 6/6/03 - Added flag value
   {
      m_objectCopyFlag = (int) file.ReadLong();					file.PostReadToken();
	   m_writeAsSingleRecord	= (BOOL) file.ReadLong();		file.PostReadToken();  // SAC 1/24/12 - (file ver 2) added to facilitate tighter IBD & XML file writing             
	   m_XMLIgnoreName			= (BOOL) file.ReadLong();		file.PostReadToken();  // SAC 1/24/12 - (file ver 2) added to prevent output of component names to XML files        
   }

   m_helpID = (UINT) file.ReadLong();
   file.PostReadToken();
}

/////////////////////////////////////////////////////////////////////////////

void BEMClass::Write( CryptoFile& file )
{
   file.WriteQString( m_shortName );
   file.WriteQString( m_longName );
   file.Write( &m_maxDefinable,  sizeof( long  ));
   file.Write( &m_maxReferences, sizeof( int ));
   file.Write( &m_autoCreate,    sizeof( int ));
//   QString m_parentType[BEM_MAX_PARENT_TYPES];
   file.Write( &m_maxChildren             , sizeof( int ));
   file.Write( &m_maxSimComps             , sizeof( int ));
   file.Write( &m_purgeUnrefCompsBeforeSim, sizeof( BOOL  ));
   file.Write( &m_helpID                  , sizeof( UINT  ));

   file.Write( &m_1BEMClassIdx,     sizeof( int ));
   file.Write( &m_1MirrorClassIdx, sizeof( int ));  // SAC 7/28/02 - added writing of new member
   file.Write( &m_objectCopyFlag,  sizeof( int ));  // SAC 6/6/03 - Added flag value
   file.Write( &m_writeAsSingleRecord, sizeof( BOOL ));		// SAC 1/24/12 - (file ver 2) added to facilitate tighter IBD & XML file writing
   file.Write( &m_XMLIgnoreName,  		 sizeof( BOOL ));		// SAC 1/24/12 - (file ver 2) added to prevent output of component names to XML files
   file.WriteQString( m_defaultName );					// SAC 1/24/12 - (file ver 2) added to specify a template for defaulting new component names
   file.Write( &m_firstPropID,     sizeof( int ));
   file.Write( &m_numProps,        sizeof( int ));

   int i=0;
   for (i=0; i<BEM_MAX_PARENT_TYPES; i++)
      file.Write( &m_parentType[i], sizeof( int ));
   for (i=0; i<BEM_MAX_CHILD_TYPES; i++)
      file.Write( &m_childType[i], sizeof( int ));
   file.Write( &m_numChildTypes, sizeof( int ));
}


