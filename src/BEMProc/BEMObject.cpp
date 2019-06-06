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
#include "BEMPropertyType.h"
#include "BEMProcObject.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
// BEMObject
/////////////////////////////////////////////////////////////////////////////

// SAC 9/24/16 - removed since no longer sotring properties in array of BEMProperty pointers
//		/////////////////////////////////////////////////////////////////////////////
//		//
//		// BEMObject Class Function:  DeleteProperties()
//		//
//		// Purpose ------------------------------------------------------------------
//		//   This function deletes all the properties which describe this object
//		//   
//		// Arguments ----------------------------------------------------------------
//		//   None
//		//   
//		// Return Value -------------------------------------------------------------
//		//   None
//		//   
//		// Notes --------------------------------------------------------------------
//		//   None
//		//   
//		/////////////////////////////////////////////////////////////////////////////
//		void BEMObject::DeleteProperties()
//		{
//			// before blasting vector of properties - loop through each and delete certain (auto-created) referenced objects
//			for (std::vector<BEMProperty>::iterator it = m_properties.begin(); it != m_properties.end(); ++it)
//			{	BEMProperty& prop = *it;
//		
//		      // if this property is a component assignment for a component of type
//		      // AutoCreate, then delete the assigned component as we delete this component
//		      if ( !eDeletingAllObjects && prop.getType() && prop.getType()->getPropType() == BEMP_Obj)   // SAC 3/24/13 - added reference to sbDeletingAllObjects
//		      {	BEMObject* pObj = prop.getObj();
//		      	if (pObj->getClass() && pObj->getClass()->getAutoCreate())
//		         	delete pObj;
//			}	}
//			m_properties.clear();
//		//   for (int iProp=m_properties.GetSize()-1; iProp>=0; iProp--)
//		//   {
//		//      BEMProperty* pProp = (BEMProperty*) m_properties[iProp];
//		//
//		//      // if this property is a component assignment for a component of type
//		//      // AutoCreate, then delete the assigned component as we delete this component
//		//      if ( !sbDeletingAllObjects && pProp && pProp->m_pType && pProp->m_pType->m_iPropType == BEMP_Obj &&   // SAC 3/24/13 - added reference to sbDeletingAllObjects
//		//			  // SAC 6/14/12 - get at ObjClassIdx through pProp->m_pObj pointer INSTEAD of through pProp->m_pType (to avoid ObjClassIdx array complications)
//		//           //pProp->m_pObj && eBEMProc.m_pClasses[ pProp->m_pType->m_i1ObjClassIdx - 1 ].m_iAutoCreate )
//		//           //pProp->m_pObj && pProp->m_pObj->m_pClass && eBEMProc.m_pClasses[ pProp->m_pObj->m_pClass->m_i1BEMClassIdx - 1 ].m_iAutoCreate )
//		//           pProp->m_pObj && pProp->m_pObj->m_pClass && pProp->m_pObj->m_pClass->m_iAutoCreate )
//		//         delete pProp->m_pObj;
//		//
//		//		delete pProp;
//		//   }
//		//   m_properties.RemoveAll();
//		}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  ~BEMObject()
//
// Purpose ------------------------------------------------------------------
//   Destructor - destroys object, inclduing all properties which describe it.
//   We also remove this object from the appropriate object list and remove
//   it from the child list of its parent object
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
void BEMObject::clear()
{
	if (!eShuttingDown)
		// make sure that the currently selective (active) object of this type is not this one
	   BEMPX_CountOrResetObjectRefs( this, FALSE );

   // delete the properties which describe this object
   initProperties(0);	// SAC 9/24/16 - was: DeleteProperties();

   // delete all child objects
   int i;
   for (i = (int) m_children.size()-1; i >= 0; i--)
   {	BEMObject* pChild = m_children.at( i );								assert( pChild );
   	pChild->setParent( NULL );
		delete pChild;
	}
	m_children.clear();

   // remove this object from the appropriate object list
	if (m_class != NULL)
	{	int iNumObjs = m_class->ObjectCount( m_objectType );
   	for (i=0; i < iNumObjs; i++)
   	{	BEMObject* pObj = m_class->GetObject( m_objectType, i );		assert( pObj );
   		if (pObj == this)
   		{	m_class->RemoveObject( m_objectType, i );	
   			break;
   	}	}
   }

   // remove this object from its parent object's list of children
	if (m_parent != NULL)
		m_parent->RemoveChild( this );
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  RemoveChild()
//
// Purpose ------------------------------------------------------------------
//   Removes an object from the list of children
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pChild  : a pointer to the object to be removed from teh list of children
//   
// Return Value -------------------------------------------------------------
//   TRUE if the object is found in the child list and removed, else FALSE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::RemoveChild( BEMObject* pChild )
{
   bool bRetVal = false;
	for (std::vector<BEMObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{	BEMObject* pObj = *it;
		if (pObj == pChild)
		{	m_children.erase( it );
			bRetVal = true;
			break;
	}	}
   return bRetVal;
}


bool BEMObject::GetChildIndices( int& i0ChildIdx, int& iNumChildren )		// SAC 7/23/14 - added to facilitate user-defined child ordering
{	bool bRetVal = false;
	if (m_parent)
		bRetVal = m_parent->GetParentChildIndices( this, i0ChildIdx, iNumChildren );
	return bRetVal;
}

bool BEMObject::GetParentChildIndices( BEMObject* pChild, int& i0ChildIdx, int& iNumChildren )		// SAC 7/23/14 - added to facilitate user-defined child ordering
{	bool bRetVal = false;		int i0ThisChildIdx = -1;
	for (std::vector<BEMObject*>::iterator it = m_children.begin(); (!bRetVal && it != m_children.end()); ++it)
	{	BEMObject* pObj = *it;
		i0ThisChildIdx++;
		if (pObj && pObj == pChild)
		{	i0ChildIdx    = i0ThisChildIdx;
			iNumChildren = (int) m_children.size();
			bRetVal = true;
		}
	}
	return bRetVal;
}


bool BEMObject::ChangeChildIndex( bool bMoveUp /*=true*/ )		// SAC 7/27/14 - added to facilitate user-defined child ordering
{	bool bRetVal = false;
	if (m_parent)
		bRetVal = m_parent->ChangeParentChildIndex( this, bMoveUp );
	return bRetVal;
}

bool BEMObject::ChangeParentChildIndex( BEMObject* pChild, bool bMoveUp /*=true*/ )		// SAC 7/27/14 - added to facilitate user-defined child ordering
{	bool bRetVal = false, bFound = false;		int iSwapIdx, i0ThisChildIdx = -1;
	// loop over all objects in parent's child list
	for (std::vector<BEMObject*>::iterator it = m_children.begin(); (!bRetVal && it != m_children.end()); ++it)
	{	BEMObject* pObj = *it;
		i0ThisChildIdx++;
		if (pObj && pObj == pChild)
		{	bFound = true;
			bool bDoSwap = false;
			if (bMoveUp)
			{	// insert in list BEFORE previous item
						// SAC 8/22/17 - fixed bug in this and following equality check preventing all valid moves
				if (i0ThisChildIdx > 0)		// can't move up from top of vector
				{	iSwapIdx = i0ThisChildIdx - 1;
					bDoSwap = true;
			}	}
			else
			{	// insert in list AFTER next item
				if (i0ThisChildIdx < (int) m_children.size()-1)		// can't move down from end of vector
				{	iSwapIdx = i0ThisChildIdx + 1;
					bDoSwap = true;
			}	}
			if (bDoSwap)
			{	iter_swap( m_children.begin() + i0ThisChildIdx, m_children.begin() + iSwapIdx );
				bRetVal = true;
			}
		}
	}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  CopyObject()
//
// Purpose ------------------------------------------------------------------
//   To copy the contents/description of one building component to another.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj  : pointer to the object copying data FROM
//   
// Return Value -------------------------------------------------------------
//   TRUE if the copy was successful, else FALSE
//   
// Notes --------------------------------------------------------------------
//   CopyObject() does not touch parent/child stuff, only local properties
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::CopyObject( BEMObject* pObj, int iBEMProcIdx /*=-1*/,
										bool bCopyPrimaryDefaultDataAsUserDefined /*=false*/ )		// SAC 6/8/15 - CBECC issue 1061
{
   bool bRetVal = (pObj != NULL);
   if (bRetVal)
   {
   	m_objectID       = pObj->m_objectID      ;  // not currently used
   	// m_objectName     = pObj->m_objectName    ;  // can't have duplicate names !!
      // m_objectType     = pObj->m_objectType    ;  // this has to do with what list this object resides in
      m_userReferenced = pObj->m_userReferenced;
   	m_class          = pObj->m_class         ;  // should already be the same
   	// BEMObject*	m_parent;   // don't copy parent pointer for now
   	// CObList		m_children;	 // don't copy children for now
      m_treeState      = pObj->m_treeState;  // set this item's state to be = copied item's state ??

// do not copy m_modelMappedObjects pointers here ???
//		for (int i=0; i<BEMPROC_MAXMODELS; i++)
//			m_modelMappedObjects[i] = NULL;		// storage of pointers to objects in other models that are either copied to or from this object

      if (iBEMProcIdx < 0)
			iBEMProcIdx = eActiveBEMProcIdx;
      BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   //   // Copy property list by first deleting previous list
   //   // and then creating new list
   //   DeleteProperties();
   //   // loop over all properties, creating new properties identical to object's ones
   //   m_properties.resize( pObj->m_properties.size() );	// SAC 2/17/16 - size entire array once here
      initProperties( (int) pObj->m_properties.size() );	// SAC 2/17/16 - size entire array once here
      for (int iProp=0; (bRetVal && iProp < (int) pObj->m_properties.size()); iProp++)
      {
         BEMProperty* pProp = (BEMProperty*) &pObj->m_properties[iProp];
         if (pProp == NULL)
            bRetVal = FALSE;
         else
         {
            //BEMProperty* pNewProp = new BEMProperty( pProp->getType(), pProp->get1ArrayIdx()-1 );
            BEMProperty* pNewProp = &m_properties[iProp];

            assert( pNewProp );  // SAC 7/31/02
            if (pNewProp == NULL)
               bRetVal = FALSE;
            else
            {
            	pNewProp->setType( pProp->getType() );
            	pNewProp->set1ArrayIdx( pProp->get1ArrayIdx() );

					// SAC 6/14/12 - assume only FIRST ObjClassIdx may be an auto-create object type (??)
               if ( pNewProp->getType() && pNewProp->getType()->getPropType() == BEMP_Obj &&
                    pBEMProc->getClass( pNewProp->getType()->getObj1ClassIdx(0) - 1 )->getAutoCreate() )
                  // don't copy AutoCreate assignments
                  bRetVal = TRUE;
               else
               {	BOOL bCreateCopyOfRefObj = FALSE;  // SAC 5/4/13 - added new check to ensure that objects w/ maxed-out MaxReferences don't accummulate more references...
						int iError;
	               if ( pNewProp->getType() && pNewProp->getType()->getPropType() == BEMP_Obj && pProp->getObj() && pProp->getObj()->m_class &&
   	                 pProp->getObj()->m_class->getMaxReferences() > 0 &&
							  !pProp->getObj()->m_class->getUniqueAssignment() &&  // if this is true, object copy should happen during generic CopyProperty()
							  !BEMPX_CanAssignObject( pProp->getObj()->m_class->get1BEMClassIdx(), iError, BEMPX_GetObjectIndex( pProp->getObj()->m_class, pProp->getObj(), iBEMProcIdx ), iBEMProcIdx ))
	               	bCreateCopyOfRefObj = TRUE;

						bRetVal = pNewProp->CopyProperty( pProp, iBEMProcIdx, FALSE, bCopyPrimaryDefaultDataAsUserDefined );		// SAC 6/8/15 - CBECC issue 1061

						if (bCreateCopyOfRefObj)
						{	assert( FALSE );  // check to see when this happens - SAC 5/4/13 - added new check to ensure that objects w/ maxed-out MaxReferences don't accummulate more references...
							pNewProp->CopyAssignedObject( FALSE /*bLibToUser*/, iBEMProcIdx );
						}
					}
            }
         }
      }

      // now re-create all auto-create attachments
   	AutoCreateReferences( iBEMProcIdx );

      bRetVal = ( m_properties.size() == pObj->m_properties.size() );
   }

   return bRetVal;
}


bool BEMObject::CopyObjectBetweenModels( BEMObject* pObj, int iThisBEMProcIdx, int iSrcBEMProcIdx )
{
	assert( iThisBEMProcIdx >= 0 && iThisBEMProcIdx < eNumBEMProcsLoaded );
	assert(  iSrcBEMProcIdx >= 0 &&  iSrcBEMProcIdx < eNumBEMProcsLoaded );
   BEMProcObject* pThisBEMProc = getBEMProcPointer( iThisBEMProcIdx );				assert( pThisBEMProc );
   BEMProcObject*  pSrcBEMProc = getBEMProcPointer(  iSrcBEMProcIdx );				assert(  pSrcBEMProc );
	bool bRetVal = (pObj && pThisBEMProc && pSrcBEMProc);
	if (bRetVal)
	{	int iError;
		// copy EVERYTHING precisely from originating object, even names since duplications CAN exist across models
   	m_objectID       = pObj->m_objectID      ;  // not currently used
   	m_objectName     = pObj->m_objectName    ;  // CAN have duplicate names across different models (BEMProcObject instances)
		m_objSimName     = pObj->m_objSimName    ;  // Object's Simulation Name (guarenteed unique w/ limited characters)
		m_objSecSimName  = pObj->m_objSecSimName ;  // Object's Secondary Simulation Name (guarenteed unique w/ limited characters)
		m_objTerSimName  = pObj->m_objTerSimName ;  // Object's Tertiary Simulation Name (guarenteed unique w/ limited characters)
      m_objectType     = pObj->m_objectType    ;  // this has to do with what list this object resides in
      m_userReferenced = pObj->m_userReferenced;
	 // pointer to Class is a little trickier, since we should reference the destination BEMProcObject's class, not the class in the source BEMProcObject
   	m_class          = BEMPX_GetClass( pObj->m_class->get1BEMClassIdx(), iError, iThisBEMProcIdx );			assert( m_class );
      m_treeState      = pObj->m_treeState;  // set this item's state to be = copied item's state ??

		m_archiveParentName = (pObj->m_parent == NULL ? "" : pObj->m_parent->m_objectName);  // Store parent object NAME
		m_parent = NULL;           // NOT storing any object pointers - all object pointers will be resolved in another step

		// SET model mapped object pointer of SOURCE object
		if (iThisBEMProcIdx < BEMPROC_MAXMODELS && pObj->m_modelMappedObjects[iThisBEMProcIdx] == NULL)
			pObj->m_modelMappedObjects[iThisBEMProcIdx] = this;
		else
		{	assert( FALSE );  // should never happen - should only have ONE object copy per model (??)
		}
		for (int iM=0; iM<BEMPROC_MAXMODELS; iM++)
			m_modelMappedObjects[iM] = pObj->m_modelMappedObjects[iM];		// storage of pointers to objects in other models that are either copied to or from this object
		m_modelMappedObjects[iSrcBEMProcIdx] = pObj;								// pointers to THIS src object

		m_children.clear();  	 // child pointers to be resolved when other object pointers are

   //   // Copy property list by first deleting previous list
   //   DeleteProperties();
   //   // loop over all properties, creating new properties identical to object's ones
   //   m_properties.resize( pObj->m_properties.size() );	// SAC 2/17/16 - size entire array once here
      initProperties( (int) pObj->m_properties.size() );	// SAC 2/17/16 - size entire array once here
      for (int iProp=0; (bRetVal && iProp < (int) pObj->m_properties.size()); iProp++)
      {
         BEMProperty* pProp = (BEMProperty*) &pObj->m_properties[iProp];
         if (pProp == NULL)
            bRetVal = FALSE;
         else
         {  //BEMProperty* pNewProp = new BEMProperty( pProp->getType(), pProp->get1ArrayIdx()-1 );
	         BEMProperty* pNewProp = &m_properties[iProp];					assert( pNewProp );
            if (pNewProp == NULL)
               bRetVal = FALSE;
            else
            {	pNewProp->setType( pProp->getType() );
            	pNewProp->set1ArrayIdx( pProp->get1ArrayIdx() );
            	bRetVal = pNewProp->CopyPropertyAcrossModels( pProp, iThisBEMProcIdx );  // SAC 3/15/13 - created for this purpose
            }
         }
      }

      // // now re-create all auto-create attachments
   	// AutoCreateReferences( iBEMProcIdx );

      if (bRetVal)
	      bRetVal = ( m_properties.size() == pObj->m_properties.size() );
	}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//bool BEMObject::ArchiveObject( BEMObject* pObj, bool bRestore, int iBEMProcIdx /*=-1*/ )
//{
//   bool bRetVal = (pObj != NULL);
//	if (iBEMProcIdx < 0)  // SAC 3/13/13
//		iBEMProcIdx = eActiveBEMProcIdx;
//
//   if (bRetVal)
//   {
//   	m_objectID       = pObj->m_objectID      ;  // not currently used
//   	m_objectName     = pObj->m_objectName    ;
//      m_objSimName     = pObj->m_objSimName    ;
//      m_objSecSimName  = pObj->m_objSecSimName ;
//      m_objTerSimName  = pObj->m_objTerSimName ;
//      m_objectType     = pObj->m_objectType    ;
//      m_userReferenced = pObj->m_userReferenced;
//   	m_class          = pObj->m_class         ;  // should already be the same
//
//// do not copy m_modelMappedObjects pointers here ???
////		for (int i=0; i<BEMPROC_MAXMODELS; i++)
////			m_modelMappedObjects[i] = NULL;		// storage of pointers to objects in other models that are either copied to or from this object
//
//      m_children.clear();	 // don't copy children - these will be restored via resolving parent names stored below
//      m_parent = NULL;   // can't guarentee restored parent will be at same address, so just blank this out for now
//      if (bRestore)
//         m_archiveParentName = pObj->m_archiveParentName;  // to be resolved in a following step
//      else
//      {
//         if (pObj->m_parent && !pObj->m_parent->m_objectName.isEmpty())
//            m_archiveParentName = pObj->m_parent->m_objectName;
//         else
//            m_archiveParentName.clear();
//      }
//
//      m_treeState      = pObj->m_treeState;  // set this item's state to be = copied item's state ??
//
//      // Copy property list by first deleting previous list
//      // and then creating new list
//      DeleteProperties();
//
//      // loop over all properties, creating new properties identical to object's ones
//      m_properties.resize( pObj->m_properties.size() );	// SAC 2/18/16 - size entire array once here
//      for (int iProp=0; (bRetVal && iProp < (int) pObj->m_properties.size()); iProp++)
//      {
//         BEMProperty* pProp = (BEMProperty*) &pObj->m_properties[iProp];							assert( pProp );
//         if (pProp == NULL)
//            bRetVal = FALSE;
//         else
//         {
//            //BEMProperty* pNewProp = new BEMProperty( pProp->getType(), pProp->get1ArrayIdx()-1 );
//            BEMProperty* pNewProp = (BEMProperty*) &m_properties[iProp];							assert( pNewProp );
//            if (pNewProp == NULL)
//               bRetVal = FALSE;
//            else
//            {
//               pNewProp->ArchiveProperty( pProp, bRestore, iBEMProcIdx );		// type & array index archived here
//               //m_properties.Add( pNewProp );
//            }
//         }
//      }
//
//      bRetVal = ( m_properties.size() == pObj->m_properties.size() );
//   }
//
//   return bRetVal;
//}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
BOOL BEMObject::CopyAllButPropertiesAndChildren( BEMObject* pObj, BEMClass* pClass )
{  assert( pObj && pClass );
   BOOL bRetVal = TRUE;
   if (pObj && pClass)
   {
   	m_objectID          = pObj->m_objectID         ;
   	m_objectName        = pObj->m_objectName       ;
      m_objSimName        = pObj->m_objSimName       ;
      m_objSecSimName     = pObj->m_objSecSimName    ;
      m_objTerSimName     = pObj->m_objTerSimName    ;
      m_objectType        = pObj->m_objectType       ;
      m_userReferenced    = pObj->m_userReferenced   ;
   	m_class             = pClass;
      m_parent            = pObj->m_parent           ;
      m_treeState         = pObj->m_treeState        ;
      m_archiveParentName = pObj->m_archiveParentName;

// do not copy m_modelMappedObjects pointers here ???
//		for (int i=0; i<BEMPROC_MAXMODELS; i++)
//			m_modelMappedObjects[i] = NULL;		// storage of pointers to objects in other models that are either copied to or from this object

      assert( m_children.size() < 1 );  // if there actually ARE children, then they should either be left alone or deleted (as opposed to simply being removed from the children list)
      // m_children.RemoveAll();	 // don't copy children

      initProperties(0);	// SAC 9/24/16 - was: DeleteProperties();      // don't copy properties
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  AutoCreateReferences()
//
// Purpose ------------------------------------------------------------------
//   To create (and assign) all referenced components that are of the type
//   AutoCreate.
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
void BEMObject::AutoCreateReferences( int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // loop over all properties in object
   for (int iProp=0; iProp < (int) m_properties.size(); iProp++)
   {
      BEMProperty* pProp = (BEMProperty*) &m_properties[iProp];						assert( pProp );
      if (pProp == NULL)
         return;
      // if property is of type BEMP_Obj and the object it assigns is AutoCreate, then create
      // a new object of this type and assign it to this property
      //else if ( pProp->getType() && pProp->getType()->getPropType() == BEMP_Obj &&
      //          pProp->getType()->m_i1ObjClassIdx > 0 && pProp->getType()->m_i1ObjClassIdx <= pBEMProc->m_iNumClasses &&
      //          pBEMProc->m_pClasses[ pProp->getType()->m_i1ObjClassIdx-1 ].m_iAutoCreate )
		else   // SAC 6/14/12 - replaced above "else if" statement w/ following to handle compatibility w/ ARRAY of referenced object classes
		{	BOOL bFoundFirstAutoCreate = FALSE;
			for (int iObjCls=0; (!bFoundFirstAutoCreate && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
			{	if ( pProp->getType() && pProp->getType()->getPropType() == BEMP_Obj &&
         	     pProp->getType()->getObj1ClassIdx(iObjCls) > 0 && pProp->getType()->getObj1ClassIdx(iObjCls) <= pBEMProc->getNumClasses() &&
         	     pBEMProc->getClass( pProp->getType()->getObj1ClassIdx(iObjCls)-1 )->getAutoCreate() )
				{	bFoundFirstAutoCreate = TRUE;
         		int i1Class = pProp->getType()->getObj1ClassIdx(iObjCls);
         	
         		// generate unique name for this new AutoCreate object
         		QString sTemp;
					if (pBEMProc->getClass( i1Class-1 )->getMaxDefinable() < 2)   // SAC 2/1/12 - added code to use classes long name alone if it is a single creation class
         			sTemp = pProp->getType()->getDescription();
					else
					{  sTemp  = m_objectName;
         			sTemp += " - ";
         			sTemp += pProp->getType()->getShortName();
					}
         		QString sName = sTemp;
         		int iIdx = 0;
         		while (BEMPX_GetComponentByNameQ( sName, FALSE, iBEMProcIdx ) != NULL)
         		{
         		   //sName.Format( " %d", ++iIdx );
         		   //sName = sTemp + sName;
         		   sName = QString("%1 %2").arg(sTemp, QString::number(++iIdx));
         		}
         	
         		// Create AutoCreate object
      			BEMObject* pObj = pBEMProc->getClass( i1Class-1 )->CreateBEMObject( sName );			assert( pObj );
         	
         		// Set Property pointer to the new AutoCreated object
         		pProp->setObj( pObj );
         		pProp->setDataStatus(  BEMS_ProgDefault );
				}
			}
		}
   }
   return;
}


/////////////////////////////////////////////////////////////////////////////
void SymbolToRuleFile( QString& sString )
{
   int iRightParen = sString.lastIndexOf( ')' );
   int iLeftParen  = sString.lastIndexOf( '(' );
   if ( (iLeftParen >= 0) && (iLeftParen < iRightParen) )
      sString = sString.mid( iLeftParen+1, iRightParen-iLeftParen-1 );
   else
      sString.clear();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  DefaultObject()
//
// Purpose ------------------------------------------------------------------
//   To populate an object's properties with default values (both hard-coded
//   as well as user-defined).
//   
// Arguments ----------------------------------------------------------------
//   int  iOccur          : Occurrence number of object being defaulted
//   BOOL bApplyUserDefs  : (default = TRUE) Flag determining whether or not
//                          to allow user-defined defaulting
//   long lDBID           : DBID of value just modified/reset
//   
// Return Value -------------------------------------------------------------
//   TRUE
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::DefaultObject( int iOccur, bool bApplyUserDefs, long lDBID, BEM_PropertyStatus ePropStatus,
                               BOOL /*bSingleValueModified*/, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = TRUE;
   if (m_class)
   {
		if (iBEMProcIdx < 0)
			iBEMProcIdx = eActiveBEMProcIdx;
      if (iOccur == -1)
         iOccur = BEMPX_GetObjectIndex( m_class, this, iBEMProcIdx );

      BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

      // First apply user-defined defaults where allowed
      if (bApplyUserDefs)
      {
         int iPropIdx = 0;
         // loop over all properties
   		for (int prop = 0; prop < m_class->getNumProps(); prop++)
            // loop over all array elements
            for (int iArr = 0; iArr < pBEMProc->getPropertyType( prop + m_class->getFirstPropID() )->getNumValues(); iArr++)
            {
               long lDBID = BEMPX_GetDBID( m_class->get1BEMClassIdx(), (prop+1), (iArr+1) );  // SAC 7/18/01

               assert( iPropIdx < (int) m_properties.size() );
               BEMProperty* pProp = (BEMProperty*) &m_properties[ iPropIdx++ ];

               if (pProp)
                  // default property
                  pProp->Default( lDBID, iOccur, m_objectType, FALSE, iBEMProcIdx );
            }
      }

      // Now apply hard coded defaults
      if (pBEMProc->getType() == BEMT_CBECC)
      {
         if (eDefaultIDsSet || LoadDefaultIDs())
         {
            int iSetRet = 0;
            long lRulesetDBID  = 0;
            long lRuleFileDBID = 0;

            if (m_class->get1BEMClassIdx() == eDefClassProj)
            {
               lRulesetDBID = eDefDBIDProjRuleset;
               lRuleFileDBID = eDefDBIDProjRuleFile;

               if (lDBID == 0 && BEMPX_GetDataStatus( eDefDBIDProjCreateDate, -1, BEMO_User, iBEMProcIdx ) == BEMS_Undefined)
               {  // Set project creation time
         //         CTime time = CTime::GetCurrentTime();
         //         long lTime = (long) time.GetTime();
						QDateTime current = QDateTime::currentDateTime();
						long lTime = (long) current.toTime_t();	// seconds since 1970-Jan-01 / valid as long int until 2038-Jan-19 / switching to uint extends valid date range to 2106-Feb-07
                  BEMPX_SetBEMData( eDefDBIDProjCreateDate, BEMP_Int, (void*) &lTime,
                                 BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, iBEMProcIdx );
               }
               else if (eDefDBIDProjUniqueAssignFlag > 0 && lDBID == eDefDBIDProjUniqueAssignFlag)
					{		assert( false );			// was:   ResetClassUniqueAssignmentFlags( iBEMProcIdx );
					}
               else if (eDefDBIDProjRemoveDupsFlag   > 0 && lDBID == eDefDBIDProjRemoveDupsFlag)
					{		assert( false );			// was:   RemoveDupUniqueAssignComponents();
					}
            }

            if (lRulesetDBID > 0)
            {
               if (lDBID == lRulesetDBID && ePropStatus == BEMS_UserDefined)
               {  // Ruleset just modified by user, so reset RuleFile to match
                  int iError;
                  BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, m_objectType, iBEMProcIdx );
                  assert (pProp);

                  QString sSymbol = GetSymbolStringFromPtrs( (int) pProp->getInt(), this, pProp, iBEMProcIdx );
                  SymbolToRuleFile( sSymbol );

                  // Set 'Proj:RuleFile' or 'Wizard:RuleFile'
						const QByteArray baStr = sSymbol.toLocal8Bit();
						const char* ssStr = baStr.constData();
                  iSetRet = BEMPX_SetBEMData( lRuleFileDBID, BEMP_Str, (void*) ssStr, BEMO_User,
                                           iOccur, BEMS_ProgDefault, m_objectType, TRUE, iBEMProcIdx );
               }
               else if (lDBID == 0 && BEMPX_GetDataStatus( lRuleFileDBID, iOccur, m_objectType, iBEMProcIdx ) == BEMS_Undefined)
               {  // Defaulting Project or Wizard but RuleFile as yet undefined
                  // Set 'Proj:RuleFile' or 'Wizard:RuleFile'
						const QByteArray baStr = eBEMProc.getCurrentRuleFile().toLocal8Bit();
						const char* ssStr = baStr.constData();
                  iSetRet = BEMPX_SetBEMData( lRuleFileDBID, BEMP_Str, (void*) ssStr, BEMO_User,
                                           iOccur, BEMS_ProgDefault, m_objectType, TRUE, iBEMProcIdx );
                  // now find the Ruleset symbol which contains this RuleFile string
                  int iNumSyms;
                  BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, lRulesetDBID, -1, BEMO_User, iBEMProcIdx );			assert( pSymDepSet );
                  if (pSymDepSet)
                  {  for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
                     {
                        long iSymValue;	QString sSymbol;
                        if (BEMPX_GetSymbolData( iSymValue, sSymbol, pSymDepSet, iSymIdx ) > 0)
                        {
	                        SymbolToRuleFile( sSymbol );
	                        if (sSymbol.compare( eBEMProc.getCurrentRuleFile(), Qt::CaseInsensitive ) == 0)
	                        {  // Set the 'Proj:Ruleset' value
	                           long lNewVal = iSymValue;
	                           iSetRet = BEMPX_SetBEMData(	lRulesetDBID, BEMP_Sym, (void*) &lNewVal, BEMO_User, iOccur,
																				eBEMProc.getCurrentRuleFileStatus(), m_objectType, TRUE, iBEMProcIdx );
	                           break;
						}	}	}	}
               }
            }
         }
      }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  SetTreeState()
//
// Purpose ------------------------------------------------------------------
//   To set the tree state (expanded (1) vs. contracted (0)) for the specified
//   tree mode (defined by iTreeStateIdx argument (0-N)).
//   
// Arguments ----------------------------------------------------------------
//   int iTreeStateIdx : Tree mode index, 0-N (used to select the bit to toggle)
//   int iState        : The state of the selected bit
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   Added 2/6/98 by SAC
//   
/////////////////////////////////////////////////////////////////////////////
void BEMObject::SetTreeState( int iTreeStateIdx, int iState )
{
   int iSelectedBit = (int) pow( 2.0, iTreeStateIdx );

   // new state is 0 but current setting is 1
   if (iState == 0 && (m_treeState & iSelectedBit))
      m_treeState -= iSelectedBit;
   // new state is 1 but current setting is 0
   else if (iState != 0 && !(m_treeState & iSelectedBit))
      m_treeState |= iSelectedBit;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  ObjectTreeStateExpanded()
//
// Purpose ------------------------------------------------------------------
//   To get the tree state (expanded (TRUE) vs. contracted (FALSE)) for the
//   specified tree mode (defined by iTreeStateIdx argument (0-N)).
//   
// Arguments ----------------------------------------------------------------
//   int iTreeStateIdx : Tree mode index, 0-N (used to select the bit to toggle)
//   
// Return Value -------------------------------------------------------------
//   TRUE if the state indicates the tree item should be expanded, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   Added 2/6/98 by SAC
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::ObjectTreeStateExpanded( int iTreeStateIdx )
{
   int iSelectedBit = (int) pow( 2.0, iTreeStateIdx );
   return ((m_treeState & iSelectedBit) != 0);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  EquivalentObject()
//
// Purpose ------------------------------------------------------------------
//   To determine whether the object pointed to by the function's argument is
//   equivalent to this object (i.e. all properties are equal).
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj : object to check equivalence of
//   bool       bIgnoreDataStatus : (default=FALSE) Flag indicating whether or
//                     not inconsistencies in the m_iDataStatus flags should 
//                     cause the equivalence test to fail.
//   
// Return Value -------------------------------------------------------------
//   TRUE if the objects ARE equivalent, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   Added 1/28/99 by SAC
//   Ignores children but DOES check assigned objects.
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::EquivalentObject( BEMObject* pObj, bool bIgnoreDataStatus )
{
   assert( pObj );

//   bool bRetVal = (m_properties.GetCount() == pObj->m_properties.GetCount());
//   // loop over all properties
//   POSITION posL = m_properties.GetHeadPosition();
//   for (POSITION pos = pObj->m_properties.GetHeadPosition();  (bRetVal && pos && posL); )
//   {
//      BEMProperty* pProp  = (BEMProperty*) pObj->m_properties.GetNext( pos );
//      BEMProperty* pPropL = (BEMProperty*) m_properties.GetNext( posL );
// SAC 1/22/02 - Convert m_properties from CObList to CObArray to speed up ruleset evaluations
   bool bRetVal = (m_properties.size() == pObj->m_properties.size());
   for (int iProp=0; (bRetVal && iProp < (int) m_properties.size() && iProp < (int) pObj->m_properties.size()); iProp++)
   {
      BEMProperty* pProp  = (BEMProperty*) &pObj->m_properties[iProp];
      BEMProperty* pPropL = (BEMProperty*) &m_properties[iProp];

      if (!pProp || !pPropL || !pProp->getType() ||
           pProp->getType()         != pPropL->getType()         ||
           pProp->getSpecialValue() != pPropL->getSpecialValue() ||
           pProp->get1ArrayIdx()    != pPropL->get1ArrayIdx()    )
         bRetVal = FALSE;
      else if (!bIgnoreDataStatus && pProp->getDataStatus() != pPropL->getDataStatus())
         bRetVal = FALSE;
      else
      {
         switch (pProp->getType()->getPropType())
         {
            case BEMP_Int :
            case BEMP_Sym : bRetVal = (pProp->getInt()    == pPropL->getInt()   );  break;
            case BEMP_Flt : bRetVal = (pProp->getDouble() == pPropL->getDouble());  break;
            case BEMP_Str : bRetVal = (pProp->getString() == pPropL->getString());  break;
                           // either object pointers are equal OR they are both non-NULL and the objects pointed to are equivalent
            case BEMP_Obj : bRetVal = (pProp->getObj() == pPropL->getObj() ||
                                      (pProp->getObj() && pPropL->getObj() &&
                                       pPropL->getObj()->EquivalentObject( pProp->getObj(), bIgnoreDataStatus )));  break;
            default      : bRetVal = FALSE;  break;
         }

         // SAC 3/23/99 - fixed bug where Prescribed value differences were being interpretted as differences in the objects
         if ( !bRetVal && bIgnoreDataStatus &&
              ( pProp->getType()->getPropType() == BEMP_Int ||
                pProp->getType()->getPropType() == BEMP_Sym ||
                pProp->getType()->getPropType() == BEMP_Flt ||
                pProp->getType()->getPropType() == BEMP_Str ) )
         {  // allow data to differ for certain combinations of local vs. library data status
            if ( ( pProp->getDataStatus()   == BEMS_Undefined   &&
                   (pPropL->getDataStatus() == BEMS_RuleDefault ||
                    pPropL->getDataStatus() == BEMS_RuleDefined) ) ||
                 ( pProp->getDataStatus()   == BEMS_RuleLibrary &&
                    pPropL->getDataStatus() == BEMS_RuleDefined  ) ||
                 ( pProp->getDataStatus()   == BEMS_RuleDefault &&
                   (pPropL->getDataStatus() == BEMS_RuleDefault ||
                    pPropL->getDataStatus() == BEMS_RuleDefined) ) ||
                 ( pProp->getDataStatus()   == BEMS_RuleDefined &&
                    pPropL->getDataStatus() == BEMS_RuleDefined  ) )
               bRetVal = TRUE;
         }
      }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMObject Class Function:  ObjectIsReferenced()
//
// Purpose ------------------------------------------------------------------
//   To determine whether the object pointed to by the function's argument is
//   referenced by this object.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj : object to check for references to
//   
// Return Value -------------------------------------------------------------
//   TRUE if the object is referenced, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   Added 1/28/99 by SAC
//   Ignores children but DOES check assigned objects.
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMObject::ObjectIsReferenced( BEMObject* pObj )
{
   assert( pObj );
   assert( pObj->m_class );

   bool bRetVal = FALSE;

   // loop over all properties
//   for (POSITION pos = m_properties.GetHeadPosition();  (!bRetVal && pos); )
//   {
//      BEMProperty* pProp  = (BEMProperty*) m_properties.GetNext( pos );
// SAC 1/22/02 - Convert m_properties from CObList to CObArray to speed up ruleset evaluations
   for (int iProp=0; (!bRetVal && iProp < (int) m_properties.size()); iProp++)
   {
      BEMProperty* pProp = (BEMProperty*) &m_properties[iProp];
      bRetVal = (pProp && pProp->getType() && pProp->getType()->getPropType() == BEMP_Obj &&
                 //pProp->getType()->m_i1ObjClassIdx == pObj->m_class->get1BEMClassIdx() &&		- SAC 6/14/12 - REMOVED check for consistency w/ PropType:m_i1ObjClassIdx - if found to be needed, will require re-work to check entire ARRAY of compatible classes
                 pProp->getObj() == pObj);
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

