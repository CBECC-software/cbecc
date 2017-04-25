// BEMProc.cpp : Defines the exported functions for the DLL application.
//
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
#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProcObject.h"
#include "BEMClass.h"
#include "BEMProperty.h"
#include "BEMProc_FileIO.h"
#include "expTextIO.h"

#include <QtCore/qvector.h>
#include <QtCore/QFileInfo.h>
//#include <QtWidgets/qprogressdialog.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>

#include "expRuleList.h"
#include "expFormula.h"
#include "memLkRpt.h"


// This is an example of an exported variable
BEMPROC_API int nBEMProc=0;

// This is an example of an exported function.
BEMPROC_API int fnBEMProc(void)
{

	std::string msg = boost::str( boost::format( "%.1f" ) % 1.234 );

	return 42;
}

//// This is the constructor of a class that has been exported.
//// see BEMProc.h for the class definition
//CBEMProcClass::CBEMProcClass()
//{
//	return;
//}

//static ExpNode sNode;

/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_GetUIActiveFlag()
{	return eBEMProc.isUIActive();
}

void BEMPX_SetUIActiveFlag( bool bActiveUI )
{	eBEMProc.setUIActive( bActiveUI );
	return;
}


/////////////////////////////////////////////////////////////////////////////
bool BEMPX_SecureExecutable()
{	char test[] = "Check String";
	QString qsTest = test;
	ExpCryptEncode( test, strlen( test ) );
	return (qsTest.compare(test)!=0);
}

/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_LoadDataModel( const char* psBEMProcFileName, int iBEMType, const char* psInitLogFileName )
{
   BOOL bRetVal = TRUE;

	QString sInitLogFileName = psInitLogFileName;
//	if (sInitLogFileName.indexOf(':') < 0 && sInitLogFileName.indexOf('\\') != 0)		// not a complete path, so assume it is relative to EXE path
//		RelativeToCompletePath( sInitLogFileName );							// revise file path to be relative to EXE path

   // call function to setup untitled log file
   InitUntitledLogFile( sInitLogFileName.toLocal8Bit().constData() );

   // Initialize BEMProc data
	BEMPX_DeleteAllObjects( -1 /*iOnlyTypeToDelete*/, FALSE /*bReInitSymbols*/ );

   eBEMProc.setType( iBEMType );
	eBEMProc.initSrcBEMProcObj();		// SAC 4/30/15
	eActiveBEMProcIdx = 0;
   bRetVal = eBEMProc.decompileBinBEMProc( psBEMProcFileName );	// SAC 10/10/13 - was: sBEMProcFileName );
   if (!bRetVal)
      BEMMessageBox( "decompileBinBEMProc() Failed.", "BEMProc.dll Error", 3 /*error*/ );

	eNumBEMProcsLoaded = (bRetVal ? 1 : 0);
//	blastSecondaryBEMProcs();  - already done inside BEMPX_DeleteAllObjects()

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  void BEMPX_CloseBEMProc()
//
// Purpose ------------------------------------------------------------------
//   To delete all instances of CBEMDataTypes, CBEMRangeChecks, and CBEMObjects
//   which would not get cleaned up automatically when DLL terminated.
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
void BEMPX_CloseBEMProc( bool bShuttingDown /*=true*/, bool bCloseLogFile /*=true*/ )
{
	if (bCloseLogFile)
		BEMPX_CloseLogFile();		// SAC 5/19/14

	bool bInitShuttingDown = eShuttingDown;
	eShuttingDown = bShuttingDown;
	bool bInitDeletingAllObjects = eDeletingAllObjects;
	eDeletingAllObjects = true;

//	// delete any existing user-defined defaults
//   BEMPX_DeleteUserDefaults();

//   // Delete all symbol definitions
//   DeleteAllSymbolLists();

	BEMPX_DeleteModels( true /*bIncludingUserModel*/ );   // SAC 3/24/13

//   sbBothBEMsActive = FALSE;
//	blastSecondaryBEMProcs();  - done inside BEMPX_DeleteModels()

   // blast any current ruleset data
   ruleSet.clear();

	eActiveBEMProcIdx = 0;
	eDeletingAllObjects = bInitDeletingAllObjects;
	eShuttingDown = bInitShuttingDown;
}


/////////////////////////////////////////////////////////////////////////////
// BEMPX_SetRulesetFilename() stuff
/////////////////////////////////////////////////////////////////////////////
void BEMPX_SetRulesetFilename( const char* sRulesetFilename, BEM_PropertyStatus eStatus )
{
   eBEMProc.setCurrentRuleFile( sRulesetFilename );
   eBEMProc.setCurrentRuleFileStatus( eStatus );
	for (int i=0; i<(eNumBEMProcsLoaded-1); i++)
	{	epBEMProcs[i]->setCurrentRuleFile( sRulesetFilename );
		epBEMProcs[i]->setCurrentRuleFileStatus( eStatus );
	}
}


/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
static int ReInitAllObjectAssignments( BEM_ObjType eObjType )
{
   int iRetVal = 0;

   // Search through all PropertyTypes for those that CAN reference this type of object,
   // then check to see if any objects of the type being reset are present, and if so, loop
   // over all objects which have are described by this PropertyType, resetting all references
   // to objects of the selected type.
   // loop over all property types
   for (int iPT=0; iPT<eBEMProc.getNumPropertyTypes(); iPT++)
   {
      // check for this property type being able to reference any type of object
      if ( (eBEMProc.getPropertyType( iPT )->getPropType() == BEMP_Obj) ) 
		{	BOOL bHaveObjs = FALSE;
			for (int iObjCls=0; (!bHaveObjs && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
			{	if (eBEMProc.getPropertyType( iPT )->getObj1ClassIdx( iObjCls ) > 0)
					bHaveObjs = (eBEMProc.getClass( eBEMProc.getPropertyType( iPT )->getObj1ClassIdx( iObjCls ) - 1 )->ObjectCount( eObjType ) > 0);
			}
			if (bHaveObjs)
      	{  // loop over each object type
      	   for (int iOT=0; iOT < BEMO_NumTypes; iOT++)
      	   {
      	      BEM_ObjType eOT = (BEM_ObjType) iOT;
      	      // no need to reset references to objects of type eObjType from other objects of type eObjType
      	      if (eOT != eObjType)
      	      {
      	         // loop over each array element of this property type
      	         for (int iArr=1; iArr <= eBEMProc.getPropertyType( iPT )->getNumValues(); iArr++)
      	         {
      	            long lDBID = BEMPX_GetDBID( eBEMProc.getPropertyType( iPT )->get1ClassIdx(), eBEMProc.getPropertyType( iPT )->get1PropTypeIdx(), iArr );
      	            // loop over all objects of this type
      	            int iNumObj = BEMPX_GetNumObjects( eBEMProc.getPropertyType( iPT )->get1ClassIdx(), eOT );
      	            for (int iObj=0; iObj < iNumObj; iObj++)
      	            {
      	               int iError;
      	               // get property and check if it references an object of type eObjType
      	               BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObj, eOT );
      	               if ( pProp && pProp->getDataStatus() > BEMS_Undefined && pProp->getDataStatus() < BEMS_NumTypes &&
      	                    pProp->getObj() && pProp->getObj()->getObjectType() == eObjType )
      	               {  // Reinitialize property
      	                  pProp->Default( lDBID, iObj, eOT );
      	                  iRetVal++;
      	               }
      	            }
      	         }
      	      }
      	   }
      	}
		}
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_DeleteAllObjects()
//
// Purpose ------------------------------------------------------------------
//   Deletes all objects defined in the building database.
//   
// Arguments ----------------------------------------------------------------
//   BOOL bReInitSymbols    : flag indicating whether or not to reinit the symbol lists
//   int  iOnlyTypeToDelete : -1 for all, otherwise the one BEM_ObjType to delete
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPX_DeleteAllObjects( int iOnlyTypeToDelete, BOOL bReInitSymbols )
{
		int iBEMProcIdx=0;
		if (iBEMProcIdx < 0)
			iBEMProcIdx = eActiveBEMProcIdx;
      BEMProcObject* pBEMProc = getBEMProcPointer( 0 );

      BOOL bDeletingOnlyOne = (iOnlyTypeToDelete >= 0 && iOnlyTypeToDelete < BEMO_NumTypes);
      bool bStartingDeletingAllObjects = eDeletingAllObjects;
      if (!bDeletingOnlyOne)
			eDeletingAllObjects = true;

      if (bDeletingOnlyOne && iBEMProcIdx == 0)
         // we are only to delete ONE type of object, so first we should loop over all OTHER
         // objects, reinitializing all references to objects of the type being deleted
         ReInitAllObjectAssignments( (BEM_ObjType) iOnlyTypeToDelete );

      // loop over all classes
      for (int i1Class=1; i1Class<=pBEMProc->getNumClasses(); i1Class++)
      {
         int iError;
         // get pointer to class and verify its intgrity
         BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
         assert( (iError >= 0 && pClass) );  // Error - getting class pointer
         if (bDeletingOnlyOne)
         {  // reinit m_pCurrentParent only of it points to an object of the deleted type
            if (pClass->getCurrentParent() && pClass->getCurrentParent()->getObjectType() == (BEM_ObjType) iOnlyTypeToDelete)
               pClass->setCurrentParent( NULL );

            // remove all objects in the selected object list
            pClass->RemoveObjects( (BEM_ObjType) iOnlyTypeToDelete );
         }
         else
         {  // remove all objects in each object list
            pClass->RemoveObjects( BEMO_User );
            pClass->RemoveObjects( BEMO_UserLib );
            pClass->RemoveObjects( BEMO_RuleLib );
            pClass->setCurrentParent( NULL );
         }
      }

      if (!bDeletingOnlyOne)
	      eDeletingAllObjects = bStartingDeletingAllObjects;

		eActiveBEMProcIdx = 0;
      if (bReInitSymbols)
         // Initialize symbol lists of symbolic values/strings
         pBEMProc->decompileBinBEMProc( NULL, TRUE );

	eNumBEMProcsLoaded = std::min( eNumBEMProcsLoaded, 1 );
	blastSecondaryBEMProcs();
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_DeleteObject()
//
// Purpose ------------------------------------------------------------------
//   Delete a single building database object.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj  : pointer to the object to be deleted
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPX_DeleteObject( BEMObject* pObj, int iBEMProcIdx /*=-1*/ )
{
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;
   if (pObj)
   {
      int iDelObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx );
      int i1ClassIdx = pObj->getClass()->get1BEMClassIdx();
      int iNumObjsOfSameType = BEMPX_GetNumObjects( i1ClassIdx, pObj->getObjectType(), iBEMProcIdx );

		// REMOVE this object from the lists of children of it's Parent
		if (pObj->getParent())
		{	if (!pObj->getParent()->RemoveChild( pObj ))		// in place of VERIFY()
				throw std::runtime_error(boost::str(boost::format("Error removing %1 '%2' child from parent %3 '%4'.") %
										pObj->getClass()->getShortName().toLocal8Bit().constData() % pObj->getName().toLocal8Bit().constData() %
										pObj->getParent()->getClass()->getShortName().toLocal8Bit().constData() % pObj->getParent()->getName().toLocal8Bit().constData() ));
		}

      // reset active object data if the active object = the one being deleted
      int iError;
      BEMObject* pActvObj = BEMPX_GetObjectByClass( i1ClassIdx, iError, -1, BEMO_User, iBEMProcIdx );
      if (pObj == pActvObj && iNumObjsOfSameType <= (iDelObjIdx+1))
      {
         int iNewObjIdx = -1;
         BEM_ObjType eNewObjType = pObj->getObjectType();
         if (iDelObjIdx > 0)
            // if the deleted object index > 0, then simply make the previous object active
            iNewObjIdx = iDelObjIdx-1;
         else
         {  // set the active object to the first one in the first object list containing objects
            for (int i=0; (iNewObjIdx == -1 && i<BEMO_NumTypes); i++)
            {
               if (BEMPX_GetNumObjects( i1ClassIdx, (BEM_ObjType) i, iBEMProcIdx ))
               {
                  iNewObjIdx = 0;
                  eNewObjType = (BEM_ObjType) i;
               }
            }
         }

         if (iNewObjIdx >= 0)  // found new active object
            BEMPX_SetActiveObjectIndex( i1ClassIdx, iNewObjIdx, eNewObjType, iBEMProcIdx );
         else
         {  // no other objects of this class exist, so re-init active object stuff
            pObj->getClass()->setCurrentBEM0ObjIdx( 0 );
            pObj->getClass()->setCurrentBEMObjType( BEMO_User );
         }
      }

      // reset any other class' m_pCurrentParent pointers which may reference this object
      if (pObj->getObjectType() == BEMO_User)
         ResetCurrentParentPointers( pObj, 0, iBEMProcIdx );

	// SAC 2/27/17 - test fix to remove this object from the ModelMappedObject lsits of OTHER loaded model copies
		for (int iBP=0; iBP < eNumBEMProcsLoaded; iBP++)
			if (iBP != iBEMProcIdx)
			{	BEMProcObject* pChkBEMProc = getBEMProcPointer( iBP );			assert( pChkBEMProc );
				if (pChkBEMProc)
				{	int iChkNumObjs = pChkBEMProc->getClass( i1ClassIdx-1 )->ObjectCount( pObj->getObjectType() );
					for (int iChkObj=0; iChkObj < iChkNumObjs; iChkObj++)
					{	BEMObject* pChkObj = pChkBEMProc->getClass( i1ClassIdx-1 )->GetObject( pObj->getObjectType(), iChkObj );		assert( pChkObj );
						if (pChkObj)
						{	for (int iChkMdl=0; iChkMdl < eNumBEMProcsLoaded; iChkMdl++)
							{	if (pChkObj->getModelMappedObject( iChkMdl ) == pObj)
									pChkObj->setModelMappedObject( iChkMdl, NULL );  // REMOVE this object from ModelMapped lists of this object from other model copies
						}	}
			}	}	}

	// added new call to ensure no other properties reference this deleted object (following its deletion)
		CountObjectAssignments( pObj, false /*bCheckMaxRefs*/, false /*bStopAfterFirst*/, true /*bCheckUserRefLibObjs*/,
										false /*bTreeCtrlCall*/, false /*bCopyDupRefs*/, iBEMProcIdx, true /*bResetAllRefs*/ );

      // finally...delete the object
      delete pObj;
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CountOrResetObjectRefs()
//
// Purpose ------------------------------------------------------------------
//   Reset or count all standard object assignments to the specified object.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj        : pointer to the object to count the assignments of.
//   BOOL       bCountRefs  : TRUE if we are counting assignments, FALSE if we
//                            wish to reset all assignments.
//   BEMObject* pReplaceObj : pointer to object to replace assignments with.
//   
// Return Value -------------------------------------------------------------
//   >= 0 : the number of object assignments found (and reset if selected).
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_CountOrResetObjectRefs( BEMObject* pObj, bool bCountRefs, BEMObject* pReplaceObj,
                                  std::vector<BEMObject*>* pObjArray /*=NULL*/, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   if (pObj)  // confirm pObj OK
   {
      int i1ClassIdx = pObj->getClass()->get1BEMClassIdx();

      // loop over all classes
      for (int i1Class=1; i1Class <= pBEMProc->getNumClasses(); i1Class++)
      {
         // Loop through all property types for this class and collect an
         // array of all property types which reference objects of the type
         // passed into this function
         int iStartPT = pBEMProc->getClass( i1Class-1 )->getFirstPropID();
         int iLastPT = iStartPT + pBEMProc->getClass( i1Class-1 )->getNumProps() - 1;
		   std::vector<int>	iaPTs;
			int i0PT = 0;
         for (i0PT = iStartPT; i0PT <= iLastPT; i0PT++)
         {
            if (pBEMProc->getPropertyType( i0PT )->getPropType() == BEMP_Obj)
				{	BOOL bFoundMatch = FALSE;
					for (int iObjCls=0; (!bFoundMatch && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
						if (pBEMProc->getPropertyType( i0PT )->getObj1ClassIdx(iObjCls) == i1ClassIdx)
						{	bFoundMatch = TRUE;
		               iaPTs.push_back( i0PT );
						}
				}
         }

         // If property types found which reference this object type, then
         // loop over all objects, get all properties corresponding to the
         // property types found and check for them being equal to the passed in obj
         if (iaPTs.size() > 0)
         {
            for (int iObjType = 0; iObjType < BEMO_NumTypes; iObjType++)
            {
               BEM_ObjType eObjType = (BEM_ObjType) iObjType;
               int iNumObjs = BEMPX_GetNumObjects( i1Class, eObjType, iBEMProcIdx );
               for (int iObj = 0; iObj < iNumObjs; iObj++)
                for (i0PT=0; i0PT < (int) iaPTs.size(); i0PT++)
                 for (int i0Arr=0; i0Arr<pBEMProc->getPropertyType( iaPTs[i0PT] )->getNumValues(); i0Arr++)
                  {
                     long lDBID = BEMPX_GetDBID( i1Class, (iaPTs[i0PT] - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1), (i0Arr+1) );  // SAC 7/18/01
                     int iError;
                     BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObj, eObjType, iBEMProcIdx );
                     if (iError >= 0 && pProp && pProp->getObj() == pObj)
                     {  // object assignment found
                        iRetVal++;
                        if (!bCountRefs)
                        {
                           if (pReplaceObj)  // should be an identical object => no further defaulting SHOULD be necessary
                              pProp->setObj( pReplaceObj );
                           else
                              pProp->Default( lDBID, iObj, eObjType, FALSE, iBEMProcIdx );
                        }
                        else if (pObjArray)
                        {  // if the pObjArray argument is not NULL, then add this object to the array (if it isn't already there)
                           BEMObject* pRefObj = BEMPX_GetObjectByClass( i1Class, iError, iObj, eObjType, iBEMProcIdx );
                           assert( pRefObj );
                           BOOL bFoundPA = FALSE;
                           for (int iPA=0; (!bFoundPA && iPA < (int) pObjArray->size()); iPA++)
                              bFoundPA = (pRefObj == (BEMObject*) pObjArray->at(iPA));
                           if (!bFoundPA)
                              pObjArray->push_back( pRefObj );
                        }
                     }
                  }
            }
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  CountObjectAssignments()
//
// Purpose ------------------------------------------------------------------
//   This function counts object assignments (=> number of times pObj is assigned
//   to other objects' properties).  The four boolean arguments describe exactly
//   how the counting is performed.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj                 : Pointer to the object we are counting the assignments of
//   BOOL       bCheckMaxRefs        : TRUE if we are checking to see if the maximum
//                                     number of object references is going to be exceeded
//   BOOL       bStopAfterFirst,     : TRUE if we need only confirm that a single assignment exists
//   BOOL       bCheckUserRefLibObjs : TRUE if we are to check user and ruleset library objects
//                                     (as well as generic user defined objects) for assignments
//   BOOL       bTreeCtrlCall        : TRUE if this call is from the tree control population
//                                     routine in which case we should ignore assignments via
//                                     properties where m_iUseForTrees = FALSE
//   BOOL       bCopyDupRefs         : TRUE if we are to recreate assignments 2-N in order to
//                                     ensure component assignment uniqueness
//   
// Return Value -------------------------------------------------------------
//   The number of object assignment found (always >= 0).
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int CountObjectAssignments( BEMObject* pObj, bool bCheckMaxRefs, bool bStopAfterFirst, bool bCheckUserRefLibObjs,
												bool bTreeCtrlCall, bool bCopyDupRefs, int iBEMProcIdx, bool bResetAllRefs )		// SAC 5/12/15 - added bResetAllRefs to fix bug in DeleteObject
{
   int iRetVal = 0;

   // SAC 8/12/99 - added code to provide access to second BEMProc
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // confirm object pointer not NULL
   if (pObj)
   {
      int iMaxRefs = 10000;
      if (bCheckMaxRefs)
      {  // set iMaxRefs if we are to check for max refs being exceeded
         if (pObj->getClass() && pObj->getClass()->getMaxReferences() > 0)
            iMaxRefs = pObj->getClass()->getMaxReferences();
      }

      // Must search through all PropertyTypes for those that can reference
      // this type of object, then get all objects which are of the class which
      // that PropertyType describes and count the number of references to this
      // particular object.
      bool bDone = FALSE;
      int i1BEMClass = pObj->getClass()->get1BEMClassIdx();
//      int iNumPropTypes = BEMPX_GetNumPropertyTypes();
      // loop over all property types
      for (int i=0; (!bDone && iRetVal < iMaxRefs && i<pBEMProc->getNumPropertyTypes()); i++)
      {
         // check for this property type being able to reference objects of the selected class
         // (as well as checking for tree compatibility)
         if ( pBEMProc->getPropertyType( i )->getPropType() == BEMP_Obj &&
              //pBEMProc->getPropertyType( i ).m_i1ObjClassIdx == i1BEMClass &&
              (!bTreeCtrlCall || pBEMProc->getPropertyType( i )->getUseForTrees()) )
         {
				int iFoundObjClsIdx = -1;
				for (int iObjCls=0; (iFoundObjClsIdx < 0 && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
				{	if (pBEMProc->getPropertyType( i )->getObj1ClassIdx(iObjCls) == i1BEMClass)
						iFoundObjClsIdx = iObjCls;
				}
				if (iFoundObjClsIdx >= 0)
				{
            	int i1PropIdx = i - pBEMProc->getClass( pBEMProc->getPropertyType( i )->get1ClassIdx() - 1 )->getFirstPropID() + 1;
            	int iEndObjType = (int) (bCheckUserRefLibObjs ? BEMO_UserLib : BEMO_User);
            	// loop over desired object types
            	for (int iOT=0; (!bDone && iRetVal < iMaxRefs && iOT <= iEndObjType); iOT++)
            	{
            	   BEM_ObjType eRetrieveObjType = (BEM_ObjType) iOT;
            	   // get number of objects of this type that are described by this property type
            	   int iNumRefObj = BEMPX_GetNumObjects( pBEMProc->getPropertyType( i )->get1ClassIdx(), eRetrieveObjType, iBEMProcIdx );
            	   for (int iRefObjIdx=0; (!bDone && iRetVal < iMaxRefs && iRefObjIdx < iNumRefObj); iRefObjIdx++)
            	   {
            	      int iError;
            	      // get the object which MAY reference pObj
            	      BEMObject* pTempObj = BEMPX_GetObjectByClass( pBEMProc->getPropertyType( i )->get1ClassIdx(), iError, iRefObjIdx,
            	                                           eRetrieveObjType, iBEMProcIdx );
            	      if ( eRetrieveObjType == BEMO_User ||
            	           (iError >= 0 && pTempObj && pTempObj->getUserReferenced()) )
            	      {
            	         // check all array elements for assignment to pObj
            	         for (int iArr=1; (!bDone && iRetVal < iMaxRefs &&
            	                             iArr <= pBEMProc->getPropertyType( i )->getNumValues()); iArr++)
            	         {
            	            long lDBID = BEMPX_GetDBID( pBEMProc->getPropertyType( i )->get1ClassIdx(), i1PropIdx, iArr );
            	            int iSpecialVal;
            	            // get the pointer to the object currently assigned
            	            BEMObject* pRefObj = BEMPX_GetObjectPtr( lDBID, iSpecialVal, iError,
            	                                                             iRefObjIdx, eRetrieveObjType, iBEMProcIdx );
            	            if (iError >= 0 && pRefObj && pRefObj == pObj)
            	            {  // assignment exists and pObj is the assigned object
            	               iRetVal++;
            	               bDone = bStopAfterFirst;
            	
            	               if ( (bCopyDupRefs && iRetVal > 1) || bResetAllRefs )
            	               {  // recreate this object and reset this assignment to ensure assignment uniqueness
            	                  int iTmpError;
            	                  BEMProperty* pProp = BEMPX_GetProperty( lDBID, iTmpError, iRefObjIdx, eRetrieveObjType, iBEMProcIdx );
            	                  if (iTmpError >= 0 && pProp && pProp->getObj())
            	                  {	if (bCopyDupRefs && iRetVal > 1)
            	                  		pProp->CopyAssignedObject( FALSE, iBEMProcIdx );
            	                  	else
            	                  		pProp->Default( lDBID, iRefObjIdx, eRetrieveObjType, FALSE, iBEMProcIdx );
            	               }	}
            	            }
            	         }
            	      }
            	   }
            	}
				}
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CountObjectAssignments()
//
// Purpose ------------------------------------------------------------------
//   Count the number of times a single object is assigned to other objects.
//   
// Arguments ----------------------------------------------------------------
//   BOOL       bCheckMaxRefs        : Check for maximum number of references being exceeded
//   int        i1BEMClass            : 1-based class (component type) index
//   int        iObjIdx              : (default = -1) index of object to check assignments of (-i => active object)
//   BEM_ObjType eObjType             : (default = BEMO_User) type of object to check assignments of
//   BOOL       bStopAfterFirst      : (default = TRUE) only confirm first assignment
//   BOOL       bCheckUserRefLibObjs : (default = FALSE) check library objects for references
//   BOOL       bTreeCtrlCall        : (default = TRUE) called from tree control population routines
//   BOOL       bCopyDupRefs         : (default = FALSE) TRUE if we are to recreate assignments 2-N in order to
//                                                       ensure component assignment uniqueness
//   
// Return Value -------------------------------------------------------------
//   The number of times the selected object is assigned to other objects
//   (always >= 0 and dependent on all function arguments).
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_CountObjectAssignments( bool bCheckMaxRefs, int i1BEMClass, int iObjIdx,
                                  BEM_ObjType eObjType, bool bStopAfterFirst,
                                  bool bCheckUserRefLibObjs, bool bTreeCtrlCall, bool bCopyDupRefs, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = 0;
   int iError;

	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;

  // get pointer to class and confirm that it is OK
   BEMClass* pClass = BEMPX_GetClass( i1BEMClass, iError );
   if ( iError == 0 && pClass )
   {
      // get pointer to object and confirm that it is OK
      BEMObject* pObj = BEMPX_GetObjectByClass( i1BEMClass, iError, iObjIdx, eObjType, iBEMProcIdx );
      if ( iError == 0 && pObj )
      {
         // call static routine to perform the object assignment counting
         iRetVal = CountObjectAssignments( pObj, bCheckMaxRefs, bStopAfterFirst, bCheckUserRefLibObjs,
                                           bTreeCtrlCall, bCopyDupRefs, iBEMProcIdx, false );
      }
   }
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CanAssignObject()
//
// Purpose ------------------------------------------------------------------
//   To determine if a selected building component (object) can be assigned
//   to another object.
//   
// Arguments ----------------------------------------------------------------
//   int  i1BEMClass : 1-based class (component type) index of selected object
//   int& iError    : Address of an error code value set by the function
//   int  iObjIdx   : (default = -1) index of selected object
//   
// Return Value -------------------------------------------------------------
//   Returns TRUE if the class and object pointers are valid and either there
//   is no maximum number of references or there are fewer existing references
//   than the maximum allowed.  Otherwise, returns FALSE.
//   iError is passed on to the BEMPX_GetClass() and BEMPX_GetObject... functions
//   and will be set to a negative value in the event either of these functions
//   fail to perform their objectives.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_CanAssignObject( int i1BEMClass, int& iError, int iObjIdx, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = FALSE;

	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   // get pointer to class and confirm that it is OK
   BEMClass* pClass = BEMPX_GetClass( i1BEMClass, iError );
   if ( iError == 0 && pClass )
   {
      // get pointer to the selected object and confirm that it is OK
      BEMObject* pObj = BEMPX_GetObjectByClass( i1BEMClass, iError, iObjIdx, BEMO_User, iBEMProcIdx );
      if ( iError == 0 && pObj )
      {
         if (pClass->getMaxReferences() == 0)
            bRetVal = TRUE;  // => no limit on number of references
         else if (pClass->getMaxReferences() > CountObjectAssignments( pObj, TRUE, FALSE, FALSE, FALSE, FALSE, iBEMProcIdx, false ))
            bRetVal = TRUE;  // => max # references not yet achieved
      }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_PurgeUnreferencedComponents()
//
// Purpose ------------------------------------------------------------------
//   Purge user-defined non-parent/child components which are not referenced
//   in order to streamline execution of (and prevent errors in) simulation.
//   
// Arguments ----------------------------------------------------------------
//   None.
//   
// Return Value -------------------------------------------------------------
//   None.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
//static char szPurge01[] = "Glass";
//static char szPurge02[] = "Cons";
//static char szPurge03[] = "Layers";
//static char szPurge04[] = "Mat";
//static const char* pszPurgeClasses[] = { szPurge01, szPurge02, szPurge03, szPurge04, NULL };
BOOL BEMPX_PurgeUnreferencedComponents( int iBEMProcIdx /*=-1*/, int* piNumObjectsDeleted /*=NULL*/ )  // SAC 9/18/13 - added piNumObjectsDeleted argument
{
   BOOL bRetVal = TRUE;

	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

	if (piNumObjectsDeleted)
		*piNumObjectsDeleted = 0;

//   int idx = 0;
//   while (pszPurgeClasses[idx])
//   {
//      int i1Class = BEMPX_GetDBComponentID( pszPurgeClasses[idx++] );
//      if (i1Class < 1)
//      {
//         bRetVal = FALSE;
//         SString sMsg;
//         sMsg = QString( "Error getting purge class '%1'." ).arg( pszPurgeClasses[idx-1] );
//         BEMMessageBox( sMsg, "BEMPX_PurgeUnreferencedComponents() Error", 3 /*error*/ );
//      }
//      else
//      {

   // initialize each CBEMClass' m_iFirstPropID & other stuff
	for (int i1Class=1; i1Class <= pBEMProc->getNumClasses(); i1Class++)
   {
      if (pBEMProc->getClass( i1Class-1 )->getPurgeUnrefCompsBeforeSim())
      {
         // loop over all user-defined objects of this type
         int iError;
         for (int iObj = BEMPX_GetNumObjects( i1Class, BEMO_User, iBEMProcIdx )-1; iObj >= 0; iObj--)
         {
            // get pointer to object and confirm that it is OK & check for # assignments
            BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iObj, BEMO_User, iBEMProcIdx );
            if ( iError == 0 && pObj &&
                 CountObjectAssignments( pObj, FALSE, TRUE, TRUE, FALSE, FALSE, iBEMProcIdx, false ) == 0 )
            {
// vvv TEMPORARY vvv
//         CString sMsg;
//         sMsg.Format( "Purging %s Object '%s'.", pszPurgeClasses[idx-1], pObj->m_sObjectName );
//         BEMMessageBox( sMsg, "BEMPX_PurgeUnreferencedComponents()", 3 /*error*/ );
// ^^^ TEMPORARY ^^^
               BEMPX_DeleteObject( pObj, iBEMProcIdx );

					if (piNumObjectsDeleted)		// SAC 9/18/13
						*piNumObjectsDeleted += 1;
            }
         }
      }
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SumChildren()
//
// Purpose ------------------------------------------------------------------
//   Sums numeric database values across all children of a single object of a
//   particular child class.
//   
// Arguments ----------------------------------------------------------------
//   long       lChildDBID  : 6 digit database ID CCPPAA (comp/property/array) of child component
//   long       lParDBID    : 6 digit database ID CCPPAA (comp/property/array) of parent component
//   int        iParOccur   : parent object occurrence index
//   BEM_ObjType eParObjType : (default = BEMO_User) parent object type
//   
// Return Value -------------------------------------------------------------
//   Numeric value equal to the sum of a specified database parameter across
//   all child objects of a specified type.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
double BEMPX_SumChildren( long lChildDBID, long lParDBID, int iParOccur, BEM_ObjType eParObjType )
{
   double fRetVal = 0.0;

   // get various pointers and database IDs used throughout the function
   int i1ParClass     = BEMPX_GetClassID( lParDBID );
   int i1ChildClass   = BEMPX_GetClassID( lChildDBID );
   int iChildDataType = BEMPX_GetDataType( lChildDBID );
   int iError = 0;
   BEMObject* pParObj = BEMPX_GetObjectByClass( i1ParClass, iError, iParOccur, eParObjType );
   // confirm that all pointers and IDs are valid
   if ( (iError >= 0) && (pParObj != NULL) && (i1ChildClass > 0) &&
        ((iChildDataType == BEMP_Int) || (iChildDataType == BEMP_Flt)) )
   {
		int iNumChildren = pParObj->getChildCount();
		for (int iC=0; (iError >= 0 && iC < iNumChildren); iC++)
		{
			BEMObject* pChildObj = pParObj->getChild( iC );
         // confirm child not NULL
         if (pChildObj == NULL)
            iError = -1;  // Error - retrieving child
         // check that child of correct class
         else if (pChildObj->getClass()->get1BEMClassIdx() == i1ChildClass)
         {
            int iChildOccur = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );

            int iStatus, iSpecialVal;
            // get child data
      //      void* pData = BEMPX_GetData( lChildDBID, iTempDT, iSpecialVal, iError,
      //                                   iChildOccur, pChildObj->getObjectType() );
		// SAC 9/8/16 - replaced above w/ following (during open source conversions)
				long lData=0;		double dData=0.0;
				if (iChildDataType == BEMP_Int)
					lData = BEMPX_GetIntegerAndStatus( lChildDBID, iStatus, iSpecialVal, iError, iChildOccur, pChildObj->getObjectType() );
				else if (iChildDataType == BEMP_Flt)
					dData = BEMPX_GetFloatAndStatus(   lChildDBID, iStatus, iSpecialVal, iError, iChildOccur, pChildObj->getObjectType() );

            // sum retrieved child data into return value (once we have confirmed that it is valid)
            if (iError < 0 || iStatus < 1)
            {  }
            else if (iChildDataType == BEMP_Int)
               // Get long data
               fRetVal += (double) lData;
            else if (iChildDataType == BEMP_Flt)
               // Get long data
               fRetVal += dData;
            else
               iError = -1;  // Error - data retrieved but it is not nueric
         }
      }

      // report if error occurred
      if (iError < 0)
      {
         BEMMessageBox( "BEMPX_SumChildren(): Error Retrieving Child Data", "Error", 3 /*error*/ );
      }
   }

   return fRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SumAll()
//
// Purpose ------------------------------------------------------------------
//   Sums numeric database values across all objects of a particular class.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   Numeric value equal to the sum of a specified database parameter across
//   all objects of a specified type.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
double BEMPX_SumAll( long lDBID )
{
   double fRetVal = 0.0;

   // get various pointers and database IDs used throughout the function
   int i1Class   = BEMPX_GetClassID( lDBID );
   int iDataType = BEMPX_GetDataType( lDBID );
   int iError = 0;
   BEMClass* pClass = BEMPX_GetClass( i1Class, iError );
   // confirm that all pointers and IDs are valid
   if ( (iError >= 0) && (pClass != NULL) && (i1Class > 0) &&
        ((iDataType == BEMP_Int) || (iDataType == BEMP_Flt)) )
   {
      // loop over all database objects
		int ibNum = pClass->ObjectCount( BEMO_User );
		for (int ib=0; (iError >= 0 && ib < ibNum); ib++)
		{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );			assert( pObj );
         if (pObj == NULL)
            iError = -1;  // Error - retrieving object pointer
         else
         {
            int iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj );

            int iStatus, iSpecialVal;
            // retrieve value from database
      //      void* pData = BEMPX_GetData( lDBID, iTempDT, iSpecialVal, iError, iOccur );
		// SAC 9/8/16 - replaced above w/ following (during open source conversions)
				long lData=0;		double dData=0.0;
				if (iDataType == BEMP_Int)
					lData = BEMPX_GetIntegerAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur );
				else if (iDataType == BEMP_Flt)
					dData = BEMPX_GetFloatAndStatus(   lDBID, iStatus, iSpecialVal, iError, iOccur );

            if (iError < 0 || iStatus < 1)
            {  }
            else if (iDataType == BEMP_Int)
               // Get long data
               fRetVal += (double) lData;
            else if (iDataType == BEMP_Flt)
               // Get long data
               fRetVal += dData;
            else
               iError = -1;  // Error - data retrieved but not integer or double
         }
      }

      // report if error occurred
      if (iError < 0)
      {
         BEMMessageBox( "BEMPX_SumAll(): Error Retrieving Object Data", "Error", 3 /*error*/ );
      }
   }

   return fRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumChildren()
//
// Purpose ------------------------------------------------------------------
//   Count the number of children attached to a building component
//   (children of either of a specific class or of any class)
//   
// Arguments ----------------------------------------------------------------
//   long       lParDBID     : 6 digit database ID CCPPAA (comp/property/array) of parent component
//   int        iParOccur    : occurence index of parent object
//   BEM_ObjType eParObjType  : type of parent object
//   int        i1ChildClass : (default = 0) 1-based class of child to count the number of
//   
// Return Value -------------------------------------------------------------
//   Number of child object assigned to the specified parent object and of a
//   specific or any class.
//   
// Notes --------------------------------------------------------------------
//    (i1ChildClass == 0) => count ALL children, irrespective of their class
//   
/////////////////////////////////////////////////////////////////////////////
double BEMPX_GetNumChildren( long lParDBID, int iParOccur, BEM_ObjType eParObjType, int i1ChildClass /*=0*/, int iBEMProcIdx /*=-1*/ )
{
   double fRetVal = 0;

   // get parent class index and object pointer
   int i1ParClass = (lParDBID <= eBEMProc.getNumClasses()) ? (int) lParDBID : BEMPX_GetClassID( lParDBID );
   int iError = 0;
   BEMObject* pParObj = BEMPX_GetObjectByClass( i1ParClass, iError, iParOccur, eParObjType, iBEMProcIdx );
   // confirm parent object OK
   if (iError >= 0 && pParObj)
   {
		int iNumChildren = pParObj->getChildCount();
		for (int iC=0; (iError >= 0 && iC < iNumChildren); iC++)
		{
			BEMObject* pChildObj = pParObj->getChild( iC );
         if (pChildObj == NULL)
            iError = -1;  // Error - retrieving child object
         else if ( i1ChildClass == 0 ||
                   pChildObj->getClass()->get1BEMClassIdx() == i1ChildClass )
            fRetVal += 1.0f;  // incrament return value
      }

      // report if error occurred
      if (iError < 0)
      {
         BEMMessageBox( "BEMPX_GetNumChildren(): Error Retrieving Child Component", "Error", 3 /*error*/ );
      }
   }

   return fRetVal;
}



/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumClasses()
//
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetNumClasses()
{  return eBEMProc.getNumClasses();
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetClass()
//
// Purpose ------------------------------------------------------------------
//   Get the pointer to the BEMClass array element corresponding to the
//   1-based array index argument.
//   
// Arguments ----------------------------------------------------------------
//   int   i1ClassIdx  : 1-based array index of desired BEMClass element
//   int&  iError      : Integral error code 
//   
// Return Value -------------------------------------------------------------
//   NULL if invalid i1ClassIdx argument, otherwise pointer to desired BEMClass
//   
// Notes --------------------------------------------------------------------
//   None
//
/////////////////////////////////////////////////////////////////////////////
BEMClass* BEMPX_GetClass( int i1ClassIdx, int& iError, int iBEMProcIdx /*=-1*/ )
{
   iError = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

	if (i1ClassIdx <= 0 || i1ClassIdx > pBEMProc->getNumClasses())
   {
      // Set error flag and return NULL if i1ClassIdx is invalid
		iError = -1;
      return NULL;
   }
   else
      // return pointer to desired BEMClass
   	return pBEMProc->getClass( i1ClassIdx - 1 );
}


////////////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetPropertyType()
//
// Purpose ------------------------------------------------------------------
//   Returns a pointer to a particular property type for the specified class.
//   
// Arguments ----------------------------------------------------------------
//   int i1Class   : 1-based class (component type) index
//   int i1PropIdx : 1-based property index from start of THAT class' property types
//   
// Return Value -------------------------------------------------------------
//   NULL if either argument is invalid, else a pointer to the desired property type.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMPropertyType* BEMPX_GetPropertyType( int i1Class, int i1PropIdx, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   if ( pBEMProc && i1Class > 0 && i1Class <= pBEMProc->getNumClasses() &&
        i1PropIdx > 0 && i1PropIdx <= pBEMProc->getClass( i1Class-1 )->getNumProps() )
      return pBEMProc->getPropertyType( pBEMProc->getClass( i1Class-1 )->getFirstPropID() + i1PropIdx - 1 );
   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetPropertyTypeIndexByShortName()
//
// Purpose ------------------------------------------------------------------
//   Get the 0-based index of a certain property type which describes the
//   specified class (component type).
//   
// Arguments ----------------------------------------------------------------
//   int    i1Class  : 1-based class (component type) index
//   LPCSTR lpszName : name of property type te return the index of
//   
// Return Value -------------------------------------------------------------
//   >=0 : 0-based from start of that components property types
//    -1 : invalid class index argument OR property type index not found
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetPropertyTypeIndexByShortName(int i1Class, LPCSTR lpszName, int iBEMProcIdx /*=-1*/)
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
	if (pBEMProc == NULL || lpszName == NULL)
		return -1;

   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses())
   {	int index;
      int iStart = pBEMProc->getClass( i1Class-1 )->getFirstPropID();
      int iEnd   = iStart + pBEMProc->getClass( i1Class-1 )->getNumProps();
      iEnd = (iEnd > pBEMProc->getNumPropertyTypes()) ? pBEMProc->getNumPropertyTypes() : iEnd;
      // loop over all property types for this class
   	for (index = iStart; index < iEnd; index++)
   	{  // return the 0-based index if the property type name matches lpszName
   		if (pBEMProc->getPropertyType( index )->getShortName().compare( lpszName, Qt::CaseInsensitive ) == 0)		// SAC 1/23/12 - switched to case INsensitive check
   			return (index - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1);
   	}

	// second round to catch properties that have been renamed - SAC 8/6/15
		QString sName = lpszName;
   	for (index = iStart; index < iEnd; index++)
   	{	if (pBEMProc->getPropertyType( index )->PreviousNameMatch( sName ))
	   		return (index - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1);
   	}
   }
	
	return -1;
}

int BEMPX_GetPropertyTypeIndexByName(int i1Class, LPCSTR lpszName, int iBEMProcIdx /*=-1*/)		// SAC 7/9/12
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
	if (pBEMProc == NULL)
		return NULL;

   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses())
   {	int index;
      int iStart = pBEMProc->getClass( i1Class-1 )->getFirstPropID();
      int iEnd   = iStart + pBEMProc->getClass( i1Class-1 )->getNumProps();
      iEnd = (iEnd > pBEMProc->getNumPropertyTypes()) ? pBEMProc->getNumPropertyTypes() : iEnd;
      // loop over all property types for this class
   	for (index = iStart; index < iEnd; index++)
   	{	if (pBEMProc->getPropertyType( index )->getShortName().compare( lpszName, Qt::CaseInsensitive ) == 0)
   			return (index - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1);
   	}
   	for (index = iStart; index < iEnd; index++)
   	{	if (!pBEMProc->getPropertyType( index )->getDescription().isEmpty() && 
				  pBEMProc->getPropertyType( index )->getDescription().compare( lpszName, Qt::CaseInsensitive ) == 0)
   			return (index - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1);
   	}

	// third round to catch properties that have been renamed - SAC 8/6/15
		QString sName = lpszName;
   	for (index = iStart; index < iEnd; index++)
  		{  if (pBEMProc->getPropertyType( index )->PreviousNameMatch( sName ))
	   		return (index - pBEMProc->getClass( i1Class-1 )->getFirstPropID() + 1);
   	}
   }
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetPropertyTypeFromDBID()
//
// Purpose ------------------------------------------------------------------
//   Convert a 6 digit database ID to a property type pointer.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   int& iError : Address of an error code value set by the function
//   
// Return Value -------------------------------------------------------------
//   NULL if either argument is invalid, else a pointer to the desired property type.
//   iError =  0 : OK
//            -1 : invalid class
//            -2 : invalid property index
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMPropertyType* BEMPX_GetPropertyTypeFromDBID( long lDBID, int& iError, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc)
	{
   	long l1Class = BEMPX_GetClassID(    lDBID );  // was: lDBID / 10000;
   	long l1Prop  = BEMPX_GetPropertyID( lDBID );  // was: (lDBID - (l1Class * 10000)) / 100;
   	iError = 0;
   	if (l1Class < 1 || l1Class > pBEMProc->getNumClasses())
   	{  // invalid class index
   	   iError = -1;
   	   return NULL;
   	}
   	else if (l1Prop < 1 || l1Prop > pBEMProc->getClass( l1Class-1 )->getNumProps())
   	{  // invalid property index
   	   iError = -2;
   	   return NULL;
   	}
   	else
   	   return BEMPX_GetPropertyType( (int) l1Class, (int) l1Prop, iBEMProcIdx );
	}
   return NULL;
}


bool BEMPX_InsertPropertyType( QString& sErrMsg, int iObjTypeID, int iPropID, const char* sPropNameShort, long lDBID, int iPropType,
	  									 int iPropTypeObjID /*=-1*/, const char* sPropNameLong /*=NULL*/, const char* sUnits /*=NULL*/,
	  									 int iBEMProcIdx /*=-1*/, BOOL bDefinedByRuleset /*=FALSE*/, int iReportPrecision /*=-9*/ )   // SAC 7/7/12  SAC 1/30/13  SAC 8/6/14	SAC 1/11/15  SAC 2/4/15
{	bool bRetVal = false;			lDBID;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc == NULL)
		sErrMsg = QString( "Error retrieving BEMProcObject pointer (idx %1)." ).arg( QString::number(iBEMProcIdx) );
	else if (iObjTypeID <= 0 || iObjTypeID > pBEMProc->getNumClasses())
		sErrMsg = QString( "Invalid iObjTypeID (%1) specified." ).arg( QString::number(iObjTypeID) );
   else if (iPropID != (pBEMProc->getClass(iObjTypeID-1)->getNumProps() + 1))
		sErrMsg = QString( "Invalid %1 iPropID (%2) specified (expecting 1-%3)." ).arg( pBEMProc->getClass(iObjTypeID-1)->getShortName(), QString::number(iPropID), QString::number(pBEMProc->getClass(iObjTypeID-1)->getNumProps() + 1) );
   else if (iPropType < BEMP_Int || iPropType > BEMP_Obj)
		sErrMsg = QString( "Invalid %1 iPropType (%2) specified (expecting %3-%4)." ).arg( pBEMProc->getClass(iObjTypeID-1)->getShortName(), QString::number(iPropType), QString::number(BEMP_Int), QString::number(BEMP_Obj) );
	else
	{	BEMPropertyType* pPT = new BEMPropertyType;					assert( pPT );
		if (pPT == NULL)
			sErrMsg = QString( "Error allocating new BEMPropertyType (%1:%2)." ).arg( pBEMProc->getClass(iObjTypeID-1)->getShortName(), sPropNameShort );
		else
		{	int iNewGlobalPropTypeIdx = pBEMProc->getClass(iObjTypeID-1)->getFirstPropID() + pBEMProc->getClass(iObjTypeID-1)->getNumProps();
			assert( iNewGlobalPropTypeIdx >= 0 && iNewGlobalPropTypeIdx < pBEMProc->getNumPropertyTypes() );

      	// initialize new BEMPropertyType data
      	pPT->setData(	sPropNameShort,		// name of this property type (need only be unique within the property types which describe each type of building component)
      						iPropType,				// => BEMP_Int / BEMP_Flt / BEMP_Sym / BEMP_Str / BEMP_Obj
      						(iPropType == BEMP_Obj && iPropTypeObjID > 0 ? iPropTypeObjID : 0), 0, 0,
      						1,							// Number of array elements for numeric, symbolic AND string types
      						((sUnits && strlen(sUnits) > 0) ? sUnits : ""),		// unit label used to label the UI control which displays this data - SAC 8/6/14
      						1,							// only for prop types of type BEMP_Obj - whether or not to follow obj refs when constructing tree ctrl - 0 => ignore when constructing tree  1 => use when constructing tree (default)
      						0,							// item help system ID
      						iObjTypeID,				// 1-Based index of the class which this property type describes
      						iPropID,					// 1-Based index of this PropType in the array which describe this class
      						(iPropID==1 ? 0 : pBEMProc->getPropertyType(iNewGlobalPropTypeIdx-1)->getSumOfPreviousProperties() +
      												pBEMProc->getPropertyType(iNewGlobalPropTypeIdx-1)->getNumValues()),	// Sum of getNumValues() for all previous BEMPropertyTypes that describe this class
      						FALSE,					// (file ver 2) added to indicate whether or not array indices are to be written to output XML files
      						0,							// 0-Never write to sim export, 1-Write to sim export whenever defined (default, rule, library...), 2-Write to sim export only if USER defined (or UsrDflt, UsrLib)
      						iReportPrecision,
      						((sPropNameLong && strlen(sPropNameLong) > 0) ? sPropNameLong : sPropNameShort),		// string used to label dynamically created UI controls in primary data dialogs
      						bDefinedByRuleset );	// facilitate processing specific to ruleset-defined properties.  No BEMBase.bin file I/O (at least for now)

			// insert new BEMPropertyType into array of prop types
	//		pBEMProc->m_pPropTypes.InsertAt( iNewGlobalPropTypeIdx, pPT );
			pBEMProc->insertPropertyType( iNewGlobalPropTypeIdx, &pPT );
			//pBEMProc->incNumPropertyTypes();

			// adjust other data to accommodate the newly inserted prop type
			pBEMProc->getClass(iObjTypeID-1)->incNumProps();
			for (int iCls = iObjTypeID; iCls < pBEMProc->getNumClasses(); iCls++)
				pBEMProc->getClass(iCls)->incFirstPropID();   // increment 0-based index of first property which describes each SUBSEQUENT class

#ifdef _DEBUG
			QString sCompParam;
			sCompParam = QString( "%1:%2" ).arg( pBEMProc->getClass(iObjTypeID-1)->getShortName(), sPropNameShort );
			assert( lDBID == BEMPX_GetDatabaseID( sCompParam ) );
#endif

			bRetVal = true;
		}
	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SetPropertyTypeDetails()
//
// Purpose ------------------------------------------------------------------
//   Called by rules processor to setup data type members for the specified
//   property type based on settings defined in the selected compliance ruleset.
//   This function presents a message box if an error is encountered.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID     : 8 digit database ID CCPPPAAA (comp/property/array)
//   int  eCompDT   : the compliance type/classification
//   BOOL bPrim     : TRUE if this property/array element is a Primary variable
//   BOOL bEdit     : TRUE if the user is allowed to edit this property/array element
//   BOOL bUserDef  : TRUE if the property/array element may be defaulted using user-defined defaults
//   BOOL bDispInp  : TRUE if this property/array element is to be displayed in the "User Input" interface mode
//   BOOL bDispProp : TRUE if this property/array element is to be displayed in the "Proposed" interface mode
//   BOOL bDispBudg : TRUE if this property/array element is to be displayed in the "Budget" interface mode
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////

// error message strings displayed in a message box if an error occurs
static char szSDTErrGen[] = "BEMPX_SetPropertyTypeDetails() Error:  ";
static char szSDTErr0[]   = "Invalid DBID = ";
static char szSDTErr1[]   = "Invalid array index in DBID = ";
static char szSDTErr2[]   = "DataType Not Found for DBID = ";
static const char* pszSDTErr[] = { szSDTErr0, szSDTErr1, szSDTErr2 };

void BEMPX_SetPropertyTypeDetails( long lDBID, int eCompDT, bool bPrim, bool bEdit,			// was: BEMPX_SetDataTypes()
										bool bUserDef, bool bDispInp, bool bDispProp, bool bDispBudg,
										int iNotInputMode, const char* pszNotInputMsg )	// SAC 8/13/15 - added to facilitate ruleset-based data model backward compatible
{
   int i1Class = BEMPX_GetClassID(    lDBID );
   int i1Param = BEMPX_GetPropertyID( lDBID );
   int i1Array = BEMPX_GetArrayID(    lDBID );
   // get the selected CBEMPropertyType
   BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Param );

   int iError = -1;  // => all OK
   if ( (i1Class <= 0) || (i1Param <= 0) || (i1Array < 0) || (pPropType == NULL) )
      iError = 0;  // Error - invalid DBID
   else
   {
      int iStartIdx = 0, iEndIdx = 0;
      if (i1Array == 0)  // "ALL"
         iEndIdx = pPropType->getNumValues() - 1;  // setting ALL array elements
      else if (i1Array <= pPropType->getNumValues())
         iStartIdx = iEndIdx = i1Array - 1;  // setting a single array element
      else
         iError = 1;  // Error - invalid array idx

		assert( iEndIdx < pPropType->getNumPropTypeDetails() );
      for (int i=iStartIdx; (iError < 0) && (i <= iEndIdx); i++)
      {
			BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( i );		assert( pPTD );
         if (pPTD == NULL)
            iError = 2;  // Error - CBEMDataType not found
			else
				pPTD->setData( eCompDT, bPrim, bEdit, bUserDef, bDispInp,
									bDispProp, bDispBudg, iNotInputMode, pszNotInputMsg );
      }

      // SAC 7/28/02 - Added code to set the DataType info for all components that are MIRRORs of the current class
      if (iError == -1)  // => all OK
      {
         int iNumClasses = BEMPX_GetNumClasses();
         for (int i1MirrorClass = i1Class+1; i1MirrorClass <= iNumClasses;  i1MirrorClass++)
         {
            int iTmpErr;
            BEMClass* pClass = BEMPX_GetClass( i1MirrorClass, iTmpErr );					assert( pClass );
            if (pClass && pClass->get1MirrorClassIdx() == i1Class)
					BEMPX_SetPropertyTypeDetails( BEMPX_GetDBID( i1MirrorClass, i1Param, i1Array ), eCompDT, 
								bPrim, bEdit, bUserDef, bDispInp, bDispProp, bDispBudg, iNotInputMode, pszNotInputMsg );		// SAC 8/13/15
         }
      }
   }

   // if an error has occurred, display the corresponding error message in a message box
   if (iError >= 0)
   {
      QString sErr = QString( "%1%2%3" ).arg( szSDTErrGen, pszSDTErr[iError], QString::number( lDBID ) );
   //   QString sNum;
   //   sNum.Format( "%ld", lDBID );
   //   CString sErr = szSDTErrGen;
   //   sErr += pszSDTErr[iError];
   //   sErr += sNum;
      BEMMessageBox( sErr, NULL, 2 /*warning*/ );
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumPropertyTypes()
//
// Purpose ------------------------------------------------------------------
//   Retrieves either the TOTAL number of property types across all classes
//   (component types) or the number of property types which describe a
//   specific class.
//   
// Arguments ----------------------------------------------------------------
//   int i1Class  : (default = 0) 1-based class (component type) index (0 => ALL classes)
//   
// Return Value -------------------------------------------------------------
//   The number of property types for all or a specified class, or zero if
//   the i1Class argument is invalid.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetNumPropertyTypes( int i1Class /*=0*/ )
{
   int iRetVal = 0;
   if (i1Class == 0)
      iRetVal = eBEMProc.getNumPropertyTypes();
   else if (i1Class > 0 && i1Class <= eBEMProc.getNumClasses())
      iRetVal = eBEMProc.getClass( i1Class-1 )->getNumProps();
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumPropertyTypeElements()
//
// Purpose ------------------------------------------------------------------
//   Get the number of array elements associated with a particular property type.
//   
// Arguments ----------------------------------------------------------------
//   int i1Class   : 1-based class (component type) index
//   int i1PropIdx : 1-based property index from start of THAT class' property types
//   
// Return Value -------------------------------------------------------------
//   >=0 : number of array elements for the desired property type
//    -1 : invalid class index argument
//    -2 : invalid property index argument
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetNumPropertyTypeElementsFromDBID( long lDBID, int iBEMProcIdx /*=-1*/ )
{	return BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID(lDBID), BEMPX_GetPropertyID(lDBID), iBEMProcIdx );
}
int BEMPX_GetNumPropertyTypeElements( int i1Class, int i1PropIdx, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc == NULL)
      iRetVal = -3;
   else if (i1Class < 1 || i1Class > pBEMProc->getNumClasses())
      iRetVal = -1;
   else if (i1PropIdx < 1 || i1PropIdx > pBEMProc->getClass( i1Class-1 )->getNumProps())
      iRetVal = -2;
   else
   {
      int iGlob0PropIdx = pBEMProc->getClass( i1Class-1 )->getFirstPropID() + i1PropIdx - 1;
      iRetVal = pBEMProc->getPropertyType( iGlob0PropIdx )->getNumValues();
   }

   return iRetVal;
}

//////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDatabaseID()
//
// Purpose ------------------------------------------------------------------
//   Conversion of "<component/class>:<parameter/property type>" character string
//   or a "<parameter/property type>" char string and component ID to a 6 digit database ID.
//   
// Arguments ----------------------------------------------------------------
//   const char* psDBCompParam : character string to parse into database ID
//   long        iCompID       : (default = 0) component type to get parameter of
//                               (0 => char string has both comp and param portions while
//                                >0 => char string has only param portion)
//   
// Return Value -------------------------------------------------------------
//  > 0 && < 1,000,000  =>  6 digit database ID
//  > 999,999  =>  lowest 6 digits are database ID while upper are component ID of next param(s) in string
//   -1  =>  Invalid iCompID parameter
//   -2  =>  String param must contain Comp:Param since iCompID == 0
//   -3  =>  Component name portion of psDBCompParam string doesn't match any valid component
//   -4  =>  Parameter name portion of psDBCompParam string doesn't match any valid parameter
//           for the designated component
//   -5  =>  Nested parameter name in psDBCompParam does not point to another building component
//           (=> is not of type BEMP_Obj)
//   -6  =>  Second nested parameter name in psDBCompParam is not a property of the referenced object
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
// Note: piRefCompID may identify only the first of possible several object types that this property can reference
// added piNumRefComps argument to count the number of individual component types that have valid DBIDs associated w/ RefProperty:Property
long BEMPX_GetDatabaseID( QString sOrigCompParam, long iCompID, BOOL bTreatParentAsObject, int* piRefCompID /*=NULL*/, int* piNumRefComps /*=NULL*/ )
{
   long lRetVal = 0;

	// added local var to keep track of original iCompID to prevent recursive calling loop below
   long iOrigCompID = iCompID;

   if (piRefCompID)
      *piRefCompID = 0;
	if (piNumRefComps)
		*piNumRefComps = 0;

	QString sCompParam = sOrigCompParam;
   int iColon = sCompParam.indexOf( QChar(':') );

   if ( (iCompID < 0) || (iCompID > eBEMProc.getNumClasses()) )
      lRetVal = -1;
   else if ( (iColon < 0) && (iCompID < 1) )
      lRetVal = -2;
   else
   {
      if (iCompID == 0)   // first portion of CompParam string must contain a Comp
      {
         QString sComp = sCompParam.left( iColon );
         iCompID = BEMPX_GetDBComponentID( sComp.toLocal8Bit().constData() );
         // Extract first portion of string so that it starts with a parameter name
         // corresponding to the iCompID component
         sCompParam = sCompParam.right( sCompParam.length() - iColon - 1 );
      }

      if (iCompID < 1)
         lRetVal = -3;
      else
      {  // check for second ':' => multiple references are contained in psDBCompParam string
			QString sNextParam;  // may want to determine how many possible unique DBIDs could resolve to 
         iColon = sCompParam.indexOf( ':' );
         if (iColon >= 0)
         {	if (piNumRefComps || piRefCompID)
				{	sNextParam = sCompParam.right( sCompParam.length() - iColon - 1 );
					if (sNextParam.indexOf(':') > 0)
						sNextParam = sNextParam.left( sNextParam.indexOf(':') );
				}
			   sCompParam = sCompParam.left( iColon );
			}

         // if statement to allow report variables to reference Parent data
         if (bTreatParentAsObject && sCompParam == "Parent")
         {
            assert( piRefCompID ); 
            lRetVal = (iCompID * BEM_COMP_MULT) + BEM_PARAM0_PARENT;

            // now search for first valid parent component type and incorporate that class idx into the return value
            BOOL bDone = FALSE;
         	for (int i0Class=0; (piRefCompID != NULL && !bDone && i0Class < eBEMProc.getNumClasses()); i0Class++)
              	for (int iChild=0; (!bDone && iChild < BEM_MAX_CHILD_TYPES); iChild++)
                  if (eBEMProc.getClass( i0Class )->getChildType( iChild ) == (iCompID-1))
                  {
                  	if (sNextParam.isEmpty() || BEMP_GetDBParameterID( sNextParam, i0Class+1 ) > 0)  // SAC 8/27/12 - only register this match if we are not referencing another object or if THIS parent has a corresponding property
							{	if (piNumRefComps)
								{	if (*piNumRefComps==0)
									{  *piRefCompID = i0Class+1;
										*piNumRefComps = 1;
									}
									else if (*piRefCompID != i0Class+1)
										*piNumRefComps += 1;           // count up number of 
								}
								else
	                  	{  *piRefCompID = i0Class+1;  // SAC 7/17/01
	                  	   bDone = TRUE;  // only finish after first
								}
							}
                  }
         }
         else
         {
            long lParamID = BEMP_GetDBParameterID( sCompParam, iCompID );
            if (lParamID < 1)
            {  // added reference to local var that keeps track of original iCompID to prevent recursive loop
               if (iColon >= 0 && iOrigCompID != 0)
               {
//                  lRetVal = BEMPX_GetDatabaseID( psDBCompParam, 0, bTreatParentAsObject, piRefCompID, piNumRefComps );  // Note: piRefCompID may identify only the first of possible several object types that this property can reference
                  lRetVal = BEMPX_GetDatabaseID( sOrigCompParam, 0, bTreatParentAsObject, piRefCompID, piNumRefComps );  // Note: piRefCompID may identify only the first of possible several object types that this property can reference
                  if (lRetVal < 0)
                     lRetVal = -4;
               }
               else
                  lRetVal = -4;
            }
            else
            {  // lParam will deal with first parameter (and its array index if one provided)
               // in sCompParam.  It's >= BEM_COMP_MULT's digits will equal the iCompID of the component
               // which this parameter points to.
               lRetVal = ((iCompID) * BEM_COMP_MULT) + (lParamID % BEM_COMP_MULT);

               // If this parameter points to an object and there is more than just a single
               // parameter provided in the string, then set the piRefCompID argument to the iCompID
               // of the object pointed to by the parameter.
               if (iColon >= 0 && piRefCompID)  // SAC 2/14/14 - added check for piRefCompID valid
               {
                  long lRefComp = lParamID / BEM_COMP_MULT;
                  if (lRefComp <= 0)
                     lRetVal = -5;
                  else
						{	if (piNumRefComps)
							{	int iError;
								BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lRetVal, iError );				assert( pPropType );
								if (pPropType)
								{	for (int iPTO=0; iPTO < BEM_MAX_PROPTYPE_OBJREFCLASSES; iPTO++)
										if (pPropType->getObj1ClassIdx(iPTO) > 0 && BEMP_GetDBParameterID( sNextParam, pPropType->getObj1ClassIdx(iPTO) ) > 0)
										{	if (*piNumRefComps==0)
											{	*piRefCompID = (int) pPropType->getObj1ClassIdx(iPTO);  // Note: piRefCompID may identify only the first of possible several object types that this property can reference
												*piNumRefComps = 1;
											}
											else if (pPropType->getObj1ClassIdx(iPTO) != *piRefCompID)
												*piNumRefComps += 1;
										}
									if (*piNumRefComps < 1)  // SAC 8/13/13
			                     lRetVal = -6;
								}
							}
							else
                  		*piRefCompID = lRefComp;  // SAC 7/17/01  // Note: piRefCompID may identify only the first of possible several object types that this property can reference
						}
               }
            }
         }
      }
   }

   return lRetVal;
}

long long BEMPX_GetModelDatabaseID( int i1ModelIdx, const char* psDBCompParam, long iCompID /*=0*/, BOOL bTreatParentAsObject /*=FALSE*/,
																				int* piRefCompID /*=NULL*/, int* piNumRefComps /*=NULL*/ )
{	long long lMDBID = BEMPX_GetDatabaseID( psDBCompParam, iCompID, bTreatParentAsObject, piRefCompID, piNumRefComps );
	if (lMDBID > 0 && i1ModelIdx > 0)
		lMDBID = BEMPX_DBIDtoMDBID( i1ModelIdx, lMDBID );
	return lMDBID;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetClassIndexByLongName()
//
// Purpose ------------------------------------------------------------------
//   Gets the 1-based BEMClass array index of the component type with the 
//   LONG name of lpszName
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR lpszName  : Long name of component type to return the 1-based index of
//   
// Return Value -------------------------------------------------------------
//   1-based BEMClass array index of the component type with the long name of lpszName
//   (returns -1 if no BEMClass matches the lpszName argument)
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetClassIndexByLongName(LPCSTR lpszName)
{	QString sName = lpszName;
	return BEMP_GetClassIndexByLongName( sName );
}

int BEMP_GetClassIndexByLongName( QString& sName )
{
  	for (int index = 0; index < eBEMProc.getNumClasses(); index++)
  	{	// check for matching long class name
  		if (sName.compare( eBEMProc.getClass( index )->getLongName(), Qt::CaseInsensitive ) == 0)		// SAC 7/10/12 - switched to NoCase comparison
  			return (index+1);
  	}
	return -1;
}

static int GetClassIndexByShortName( QString& sName )
{
  	for (int index = 0; index < eBEMProc.getNumClasses(); index++)
  	{	// check for matching short class name
  		if (sName.compare( eBEMProc.getClass( index )->getShortName(), Qt::CaseInsensitive ) == 0)		// SAC 7/10/12 - switched to NoCase comparison
//  		if (eBEMProc.getClass( index )->getShortName().CompareNoCase( lpszName ) == 0)		// SAC 7/10/12 - switched to NoCase comparison
  			return (index+1);
  	}
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDBComponentID()
//
// Purpose ------------------------------------------------------------------
//   Conversion from component type string to class ID.
//   
// Arguments ----------------------------------------------------------------
//   const char* psDBComp  : charactrer string containing component type
//   
// Return Value -------------------------------------------------------------
//   > 0 =>  1-based component type (class) index
//   -1  =>  No Component name match found
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetDBComponentID( const char* psDBComp )
{	QString sDBComp = psDBComp;
	return BEMP_GetDBComponentID( sDBComp );
}

int BEMP_GetDBComponentID( QString& sDBComp )
{
   // first try matching against short names
   int iRetVal = GetClassIndexByShortName( sDBComp );
   if (iRetVal <= 0)  // check against long names only if short name match not found
      iRetVal = BEMP_GetClassIndexByLongName( sDBComp );
   return iRetVal;
}


int BEMP_GetPropertyTypeIndexByName( int i1Class, QString& sName, int iBEMProcIdx /*=-1*/ )		// SAC 7/9/12
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return NULL;

   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses())
   {	int index;
      int iStart = pBEMProc->getClass( i1Class-1 )->getFirstPropID();
      int iEnd   = iStart + pBEMProc->getClass( i1Class-1 )->getNumProps();
      iEnd = (iEnd > pBEMProc->getNumPropertyTypes()) ? pBEMProc->getNumPropertyTypes() : iEnd;
      // loop over all property types for this class
   	for (index = iStart; index < iEnd; index++)
   	{	if (sName.compare( pBEMProc->getPropertyType( index )->getShortName(), Qt::CaseInsensitive ) == 0)
			return (index - iStart + 1);
   	}
   	for (index = iStart; index < iEnd; index++)
   	{	if (sName.compare( pBEMProc->getPropertyType( index )->getDescription(), Qt::CaseInsensitive ) == 0)
			return (index - iStart + 1);
   	}

	// third round to catch properties that have been renamed - SAC 8/6/15
   	for (int index = iStart; index < iEnd; index++)
   	{	if (pBEMProc->getPropertyType( index )->PreviousNameMatch( sName ))
   			return (index - iStart + 1);
   	}
   }
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDBParameterID()
//
// Purpose ------------------------------------------------------------------
//   Parse a property (parameter) type string and component (class) index into
//   a 6 digit database ID.
//   
// Arguments ----------------------------------------------------------------
//   const char* psDBParam : parameter (property type) string
//   long        iCompID   : 1-based component type (class) index
//   
// Return Value -------------------------------------------------------------
//   > 0  =>  6 digit database ID
//    -1  =>  iCompID out of range
//    -2  =>  No parameter name match found
//    -3  =>  Array index contained in square brackets out of range
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
long BEMPX_GetDBParameterID( const char* psDBParam, long iCompID )
{	QString sInputParam = psDBParam;
	return BEMP_GetDBParameterID( sInputParam, iCompID );
}

long BEMP_GetDBParameterID( QString& sInputParam, long iCompID )
{
   long lRetVal = 0;

   if ( (iCompID < 1) || (iCompID > eBEMProc.getNumClasses()) )
      lRetVal = -1;
   else
   {
      //QString sInputParam = psDBParam;
      if (sInputParam.compare( "Active", Qt::CaseInsensitive ) == 0)
         lRetVal = BEM_PARAM0_ACTIVE;
      else if (sInputParam.compare( "Name", Qt::CaseInsensitive ) == 0)
         lRetVal = BEM_PARAM0_NAME;
      else if (sInputParam.compare( "Parent", Qt::CaseInsensitive ) == 0)
         lRetVal = BEM_PARAM0_PARENT;
      else if (sInputParam.compare( "PClass", Qt::CaseInsensitive ) == 0)
         lRetVal = BEM_PARAM0_PARCLAS;
      else if (sInputParam.compare( "Action", Qt::CaseInsensitive ) == 0)  // SAC 3/20/99
         lRetVal = BEM_PARAM0_ACTION;
      else if (sInputParam.compare( "Create", Qt::CaseInsensitive ) == 0)  // SAC 6/13/00
         lRetVal = BEM_PARAM0_CREATE;
      else if (sInputParam.compare( "Delete", Qt::CaseInsensitive ) == 0)  // SAC 6/13/00
         lRetVal = BEM_PARAM0_DELETE;
      else if (sInputParam.compare( "Cr8Option", Qt::CaseInsensitive ) == 0)  // SAC 9/18/13
         lRetVal = BEM_PARAM0_CR8OPT;
      else if (sInputParam.compare( "UserLib", Qt::CaseInsensitive ) == 0)  // SAC 9/18/13
         lRetVal = BEM_PARAM0_USERLIB;
      else if (sInputParam.compare( "RuleLib", Qt::CaseInsensitive ) == 0)  // SAC 9/18/13
         lRetVal = BEM_PARAM0_RULELIB;
      else
      {
         int iSqrBracket = sInputParam.indexOf( '[' );
         QString sParamOnly;

         if (iSqrBracket < 0)
            sParamOnly = sInputParam;
         else
            sParamOnly = sInputParam.left( iSqrBracket );

         long lPropTypeIdx = BEMP_GetPropertyTypeIndexByName( (int) iCompID, sParamOnly );  // SAC 7/9/12 - checks both short & long names AND case insensitive
         if (lPropTypeIdx <= 0)
            lRetVal = -2;
         else
         {
            int iTotPropTypeIdx = (int) lPropTypeIdx-1 + eBEMProc.getClass( iCompID-1 )->getFirstPropID();

            // Set lRetVal 100's to 1-based property type index
            lRetVal += (lPropTypeIdx * BEM_PARAM_MULT);

            // if this property type is of type object, set the BEM_COMP_MULT's digits to the 1-based
            // index of the DBClass which this object data points to
				// SAC 6/15/12 - Return only the FIRST of possible multiple object types that can be refernced by the property
				//					  which means that calling routines will have to deal w/ determining and dealing with the subsequent compatible object types
            if (eBEMProc.getPropertyType( iTotPropTypeIdx )->getPropType() == BEMP_Obj)
               lRetVal += (((long) eBEMProc.getPropertyType( iTotPropTypeIdx )->getObj1ClassIdx(0)) * BEM_COMP_MULT);

            // If no array index provided, calc return value w/ array index = 1
            if (iSqrBracket < 0)
               lRetVal += 1;
            else
            {  // we should have a 1-based array index (or "ALL") inside the square brackets
               QString sArrIdx = sInputParam.right( sInputParam.length() - iSqrBracket - 1 );
               if (sArrIdx.compare( "ALL]", Qt::CaseInsensitive ) == 0)
               {  // do nothing - a zero value for array idx => "ALL"
               }
               else
               {
                  int iArrIdx = atoi( sArrIdx.toLocal8Bit().constData() );
                  if ( (iArrIdx < 1) || (iArrIdx > eBEMProc.getPropertyType( iTotPropTypeIdx )->getNumValues()) )
                     lRetVal = -3;
                  else
                     lRetVal += iArrIdx;
               }
            }
         }
      }
   }

   return lRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// SAC - 3/12/98 - Added to enable RulPrc to access Comp:Param[Arr] strings
//                 from a DBID
/////////////////////////////////////////////////////////////////////////////
void BEMPX_DBIDToDBCompParamString( long lDBID, QString& sCompParam, bool bLongNames /*=false*/ )	// SAC 8/13/13
{
   sCompParam.clear();
   int iClass = BEMPX_GetClassID(    lDBID );
   int iProp  = BEMPX_GetPropertyID( lDBID );
   int iArray = BEMPX_GetArrayID(    lDBID );
   if (iClass < 1 || iClass > eBEMProc.getNumClasses())
      sCompParam = QString("DBID=%1 Not Found").arg(QString::number(lDBID));
   else
   {
      sCompParam = (bLongNames ? eBEMProc.getClass( iClass-1 )->getLongName() : eBEMProc.getClass( iClass-1 )->getShortName());		// SAC 8/13/13
      sCompParam += ':';
      if (iProp > 0)
      {
         int i0PropIdx = eBEMProc.getClass( iClass-1 )->getFirstPropID() + iProp - 1;
         if (i0PropIdx < 0 || i0PropIdx >= eBEMProc.getNumPropertyTypes())
            sCompParam += "UnknownParam";
         else
         {
            sCompParam += (bLongNames ? eBEMProc.getPropertyType( i0PropIdx )->getDescription() : eBEMProc.getPropertyType( i0PropIdx )->getShortName());		// SAC 8/13/13
            if (eBEMProc.getPropertyType( i0PropIdx )->getNumValues() > 1)
              // append array index within square brackets
      			sCompParam += QString("[%1]").arg(QString::number(iArray));
         }
      }
      else if (iProp == 0)
         switch (iArray)
         {
            case BEM_PARAM0_ACTIVE  :   sCompParam += "Active";      break;  
            case BEM_PARAM0_NAME    :   sCompParam += "Name";        break;  
            case BEM_PARAM0_PARENT  :   sCompParam += "Parent";      break;  
            case BEM_PARAM0_NEWPAR  :   sCompParam += "NewParent";   break;  
            case BEM_PARAM0_NEWCOPY :   sCompParam += "NewCopy";     break;  
            case BEM_PARAM0_PARCLAS :   sCompParam += "PClass";      break;  
            case BEM_PARAM0_ACTION  :   sCompParam += "Action";      break;  
            case BEM_PARAM0_CREATE  :   sCompParam += "Create";      break;    // SAC 6/13/00
            case BEM_PARAM0_DELETE  :   sCompParam += "Delete";      break;    // SAC 6/13/00
            case BEM_PARAM0_CR8OPT  :   sCompParam += "Cr8Option";   break;    // SAC 9/18/13
            case BEM_PARAM0_USERLIB :   sCompParam += "UserLib";     break;    // SAC 9/18/13
            case BEM_PARAM0_RULELIB :   sCompParam += "RuleLib";     break;    // SAC 9/18/13
            default                 :   sCompParam += "UnknownParam";   break;  
         }
      else
         sCompParam += "UnknownParam";
   }
}


/////////////////////////////////////////////////////////////////////////////
// Access to BEMObjects

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CanCreateAnotherUserObject()
//
// Purpose ------------------------------------------------------------------
//   Check to see if it is OK to create another component of the specified type
//   
// Arguments ----------------------------------------------------------------
//   int i1Class  : 1-based class (component type) index
//   
// Return Value -------------------------------------------------------------
//   TRUE if another component of this type can be created, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_CanCreateAnotherUserObject( int i1Class, int iNumObjs, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

//#ifdef _DEBUG
//   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses() &&
//       (pBEMProc->getClass( i1Class-1 )->m_bdObjects.GetCount() + iNumObjs) >
//       pBEMProc->getClass( i1Class-1 )->m_iMaxDefinable)
//      BEMMessageBox( QString( "Cannot create another " + pBEMProc->getClass( i1Class-1 )->getShortName() ),
//                    "BEMProc:BEMPX_CanCreateAnotherUserObject() Error", 3 /*error*/ );
//#endif

   return ( ( i1Class < 1 || i1Class > pBEMProc->getNumClasses() ||
              (pBEMProc->getClass( i1Class-1 )->getAutoCreate()) ) ? FALSE :
				  		(pBEMProc->getClass( i1Class-1 )->getMaxDefinable() == 0 ? TRUE :	  // SAC 1/23/12 - enable m_iMaxDefinable==0 to enable unlimited creations
                      ( (pBEMProc->getClass( i1Class-1 )->getMaxDefinable() - iNumObjs -
                         pBEMProc->getClass( i1Class-1 )->ObjectCount( BEMO_User )) >= 0 ) ) );
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CanCreateAnotherChildObject()
//
// Purpose ------------------------------------------------------------------
//   Check to see if it is OK to create another component of the specified type
//   and to be attached to the specified parent object.
//   
// Arguments ----------------------------------------------------------------
//   int        i1Class : 1-based class (component type) index
//   BEMObject* pParObj : pointer to proposed parent object
//   
// Return Value -------------------------------------------------------------
//   TRUE if another component of this type can be created as a child of the
//   specified parent object, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_CanCreateAnotherChildObject( int i1Class, BEMObject* pParObj, int iNumChildren, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // first confirm that another of this class can be created, irregardless of the parent
   if (pParObj && BEMPX_CanCreateAnotherUserObject( i1Class, iNumChildren, iBEMProcIdx ))
   {
      // return TRUE if there are no MaxChild limits on this class OR if the specified parent
      // has fewer that the MaxChild children (regardless of child class IDs)
      if ( pBEMProc->getClass( i1Class-1 )->getMaxChildren() < 0 ||
           (pParObj->getChildCount() + iNumChildren) <= pBEMProc->getClass( i1Class-1 )->getMaxChildren() )
         return TRUE;
      else
      {  // there IS a MaxChild limit for this class and the specified parent MAY already
         // have the maximum assigned, so we need to loop through all children of the specified
         // parent to see if the count of children of THIS class meets or exceeds the maximum
         int iNumChildrenOfThisClass = pParObj->countChildrenOfClass( i1Class );
   //      int iNumChildrenOfThisClass = 0;
   //      for (POSITION pos = pParObj->m_children.GetHeadPosition(); pos != NULL; )
   //      {
   //         BEMObject* pChildObj = (BEMObject*) pParObj->m_children.GetNext( pos );
   //         if (pChildObj && pChildObj->getClass() &&
   //             pChildObj->getClass()->get1BEMClassIdx() == i1Class)
   //            iNumChildrenOfThisClass++;
   //      }

         if ((iNumChildrenOfThisClass + iNumChildren) <= pBEMProc->getClass( i1Class-1 )->getMaxChildren())
            return TRUE;
      }
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SetActiveObjectIndex()
//
// Purpose ------------------------------------------------------------------
//   Set the active object index for the specified class (component type) so
//   that all future data retrieval or edits happen to desired component.
//   
// Arguments ----------------------------------------------------------------
//   int        i1Class  : 1-based class (component type) index
//   int        i0ObjIdx : 0-based object index to be made the active object
//   BEM_ObjType objType  : (default = BEMO_User) object type of object to be made active
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPX_SetActiveObjectIndex( int i1Class, int i0ObjIdx, BEM_ObjType objType, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // first confirm that class and object indices are valid
   if ( i1Class > 0 && i1Class <= pBEMProc->getNumClasses() &&
        i0ObjIdx >= 0 && i0ObjIdx < pBEMProc->getClass_NumObjects( i1Class-1, objType ) )
   {
      // set active object and type flags for this class
      pBEMProc->getClass( i1Class-1 )->setCurrentBEM0ObjIdx( i0ObjIdx );
      pBEMProc->getClass( i1Class-1 )->setCurrentBEMObjType( objType  );

      // if this object is of type User, then also find and set active parent object
      // for all classes where the parent could be the new active object's parent object
      if (objType == BEMO_User)
      {
         int iError = 0;
         BEMObject* pParObj = BEMPX_GetObjectByClass( i1Class, iError, i0ObjIdx, BEMO_User, iBEMProcIdx );
         if (pParObj)
         {
            int i0Class = i1Class-1;
            for (int i1TempClass=1; i1TempClass<=pBEMProc->getNumClasses(); i1TempClass++)
            {
               if ( pBEMProc->getClass( i1TempClass-1 )->ClassInParentList( i0Class+1 ) &&
							// make sure this parent's children don't already max out their MaxChild settings before setting
                    BEMPX_CanCreateAnotherChildObject( i1TempClass, pParObj, 1, iBEMProcIdx ) )
                  pBEMProc->getClass( i1TempClass-1 )->setCurrentParent( pParObj );
            }
         }
      }
   }
}


long BEMPX_GetClassMaxDefinable( int i1Class, int iBEMProcIdx /*=-1*/ )		// SAC 7/10/12
{	int iError;
   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
   if (pClass)
		return pClass->getMaxDefinable();
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CreateObject()
//
// Purpose ------------------------------------------------------------------
//   This function is called to create a new building component.  Virtually
//   all the work is actually done by the BEMClass member function CreateBEMObject().
//   
// Arguments ----------------------------------------------------------------
//   int        i1Class        : 1-based class (component type) index
//   LPCSTR     lpszName       : name of new building component
//   BEMObject* pParent        : (default = NULL) parent of new building component
//   BEM_ObjType objType        : (default = BEMO_User) object type of new building component
//   BOOL       bDefaultParent : (default = TRUE) TRUE only if the default parent for this
//                               component type is to be installed as this object's parent
//   BOOL       bAutoCreate    : (default = TRUE) TRUE only if all referenced classes which
//                               are tagged as AutoCreate should be created automatically
//   
// Return Value -------------------------------------------------------------
//   NULL if an error occurred when creating the new object, otherwise a pointer
//   to the newly created object (building component).
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
// SAC 5/29/14 - added i0ChildIdx in place of BOOL bMakeFirstChild = FALSE
BEMObject* BEMPX_CreateObject( int i1Class, LPCSTR lpszName, BEMObject* pParent, BEM_ObjType objType, bool bDefaultParent,
											bool bAutoCreate, int iBEMProcIdx /*=-1*/, BOOL bIgnoreMaxDefinable, int i0ChildIdx /*=-1*/ )
{
   BEMObject* pRetVal = NULL;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses())
   {
      QString sDefName;
      if (lpszName == NULL || strlen( lpszName ) < 1)
         BEMPX_GetDefaultComponentName( i1Class, sDefName, iBEMProcIdx );
      else
         sDefName = lpszName;

      pRetVal = pBEMProc->getClass( i1Class-1 )->CreateBEMObject( sDefName, objType, pParent, bDefaultParent,
                                                                 bAutoCreate, iBEMProcIdx, bIgnoreMaxDefinable, i0ChildIdx );  // SAC 5/29/14
   }
   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_CopyComponent()
//
// Purpose ------------------------------------------------------------------
//   Calls the BEMObject member function CopyObject() to copy the contents
//   of the pSrcObj into the pDestObj
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pDestObj : pointer to destination object (copy data TO)
//   BEMObject* pSrcObj  : pointer to source object (copy data FROM)
//   
// Return Value -------------------------------------------------------------
//   TRUE if copy successful, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   This function does not touch parent/child stuff, only local properties
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_CopyComponent( BEMObject* pDestObj, BEMObject* pSrcObj, int iBEMProcIdx /*=-1*/,
									bool bCopyPrimaryDefaultDataAsUserDefined /*=false*/ )		// SAC 6/8/15 - CBECC issue 1061
{	return (pDestObj && pDestObj->CopyObject( pSrcObj, (iBEMProcIdx < 0 ? eActiveBEMProcIdx : iBEMProcIdx), bCopyPrimaryDefaultDataAsUserDefined ));
}


/////////////////////////////////////////////////////////////////////////////

int BEMPX_CheckObjectNames(	char* pcNotAllowedInObjNames, QString& sNameViolationMsg, int iBEMProcIdx /*=-1*/,
										BOOL bAllowTrailingSpaces /*=TRUE*/, BOOL bPerformRenames /*=TRUE*/, BOOL bLogRenames /*=TRUE*/ )
{
	int iNumNameViolations = 0;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
	if (pBEMProc && pcNotAllowedInObjNames)
	{	QString sViolationChars, sNewObjName;
		int iError, idx, iBadCharIdx;
		BOOL bTrailingSpcViolation;
		for (int i1Class=1; i1Class <= pBEMProc->getNumClasses(); i1Class++)
		{	// loop over all user-defined objects of this type
			int iNumObjs = BEMPX_GetNumObjects( i1Class, BEMO_User, iBEMProcIdx );
			for (int iObj = 0; iObj < iNumObjs; iObj++)
			{	// get pointer to object to check name of
				BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iObj, BEMO_User, iBEMProcIdx );
				if (iError == 0 && pObj)
				{	idx=-1;		bTrailingSpcViolation = FALSE;
					sViolationChars.clear();		sNewObjName.clear();
					while (pcNotAllowedInObjNames[++idx] != NULL)
					{	iBadCharIdx = pObj->getName().indexOf( pcNotAllowedInObjNames[idx] );
						if (iBadCharIdx >= 0)
						{	sViolationChars += pcNotAllowedInObjNames[idx];
							if (sViolationChars.length()==1)
								sNewObjName = pObj->getName();
							//RemoveCharFromString( sNewObjName, sNewObjName.Find( pcNotAllowedInObjNames[idx] ) );
							sNewObjName.remove( pcNotAllowedInObjNames[idx] );
						}
					}
					if (!bAllowTrailingSpaces && pObj->getName()[ pObj->getName().length()-1 ] == ' ')
					{	bTrailingSpcViolation = TRUE;
						if (sViolationChars.isEmpty())
							sNewObjName = pObj->getName();
						sNewObjName = sNewObjName.trimmed();		// note - trims left & right - was: sNewObjName.TrimRight( ' ' );
					}
					if (bTrailingSpcViolation || !sViolationChars.isEmpty())
					{	iNumNameViolations++;
						QString sRenameMsg;
						if (!bPerformRenames)
							sRenameMsg = QString( "Warning:  %1 '%2' violates object naming rules due to: " ).arg( pObj->getClass()->getShortName(), pObj->getName() );
						else
						{	if (sNewObjName.isEmpty())
							{	assert( FALSE );		// name includes ONLY violation chars ??
								BEMPX_GetDefaultComponentName( i1Class, sNewObjName, iBEMProcIdx );
							}
							if (BEMPX_GetComponentByNameQ( sNewObjName, FALSE, iBEMProcIdx ) != NULL)
							{	// revise new name to ensure uniqueness
								QString sSaveNewObjName = sNewObjName;
								idx = 1;
								do
								{
									idx++;
									sNewObjName = QString( " %1" ).arg( QString::number(idx) );
									sNewObjName = sSaveNewObjName + sNewObjName;
								} while (BEMPX_GetComponentByNameQ( sNewObjName, FALSE, iBEMProcIdx ) != NULL);
							}
							sRenameMsg = QString( "Warning:  %1 '%2' renamed to '%3' due to: " ).arg( pObj->getClass()->getShortName(), pObj->getName(), sNewObjName );

						// RENAME object						
							int iSetRetVal = BEMPX_SetBEMData(	BEMPX_GetDBID( pObj->getClass()->get1BEMClassIdx(), 0, BEM_PARAM0_NAME ), BEMP_QStr, (void*) &sNewObjName,
																			pObj->getObjectType() /*eObjType*/, iObj, BEMS_UserDefined, BEMO_User /*eObjType*/, TRUE /*bPerformResets*/, iBEMProcIdx );		assert( iSetRetVal >= 0 );
						}
						// complete name violation message
						if (!sViolationChars.isEmpty())
						{	sRenameMsg += "presence of illegal char(s): ";		sRenameMsg += sViolationChars;
							if (bTrailingSpcViolation)
								sRenameMsg += " and ";
						}
						if (bTrailingSpcViolation)
							sRenameMsg += "trailing space character";
						sNameViolationMsg += sRenameMsg;
						sNameViolationMsg += "\n";
						if (bLogRenames)
							BEMPX_WriteLogFile( sRenameMsg, NULL, FALSE, TRUE /*bSupressAllMessageBoxes*/ );
					}	// end of: if name is errant
				}	// end of: if valid Obj
	}	}	}

	return iNumNameViolations;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumObjects()
//
// Purpose ------------------------------------------------------------------
//   Get the number of objects for a particular class and of a specified type.
//   
// Arguments ----------------------------------------------------------------
//   int        i1BEMClass : 1-based class (component type) index
//   BEM_ObjType eObjType  : Type of objects to return the count of
//   
// Return Value -------------------------------------------------------------
//   >= 0  =>  Number of objects
//     -1  =>  invalid class index argument
//     -2  =>  invalid eObjType argument
//   
// Notes --------------------------------------------------------------------
//   if eObjType == BEMO_NumTypes then this function returns the sum across ALL object types
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetNumObjects( int i1BEMClass, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   if (i1BEMClass < 1 || i1BEMClass > pBEMProc->getNumClasses())
      iRetVal = -1;
   else if (eObjType >= BEMO_User && eObjType < BEMO_NumTypes)
      iRetVal = pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( eObjType );
   else if (eObjType == BEMO_NumTypes)
      iRetVal = pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( BEMO_User    ) +
                pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( BEMO_RuleLib ) +
                pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( BEMO_UserLib );
   else
      iRetVal = -2;
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDefaultComponentName()
//
/////////////////////////////////////////////////////////////////////////////
// SAC 6/25/02 - Added fourth argument to enable naming index to begin with something other than the current component index
// SAC 6/6/03 - Added final three arguments to facilitate default naming to ensure BOTH name uniqueness for new component AND subordinate components
int BEMPX_GetDefaultComponentName( int i1Class, QString& sDefName, int iBEMProcIdx /*=-1*/, int iFirstIndex,
                                   const char* pszCompPfx1, const char* pszCompPfx2, const char* pszCompPfx3 )
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   int idx = 1;
   BOOL bDefNamePassedIn = (!sDefName.isEmpty());
   QString sDefault;
   int iError;
   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );

   if (!sDefName.isEmpty())
      sDefault = sDefName;
   else if (iError >= 0 && pClass)
      sDefault = pClass->getDefaultName();
   else
      sDefault = "Component";

   // First, if only one component can be created of this class, try the
   // default name alone, without any index at all
   if (pClass && pClass->getMaxDefinable() == 1 && BEMPX_GetComponentByNameQ( sDefault, FALSE, iBEMProcIdx ) == NULL)  // SAC 1/23/12 - enable m_iMaxDefinable==0 to enable unlimited creations
      sDefName = sDefault;
   // SAC 7/6/01 - added code to prevent appending index of passed in name already unique
   else if (bDefNamePassedIn && BEMPX_GetComponentByNameQ( sDefName, FALSE, iBEMProcIdx ) == NULL)
   {  }  // do nothing, as sDefName already set
   else
   {
      if (iFirstIndex >= 1)
         idx = iFirstIndex - 1;
      else
         // start by setting idx to the number of components already defined for this class
         idx = BEMPX_GetNumObjects( i1Class, BEMO_User, iBEMProcIdx );
      // continue to incrament idx until a unique name using it is found, then we're done
      QString sSubCompPrefix;  // SAC 6/6/03
      do
      {
         idx++;
         sDefName.clear();
         sDefName = QString( "%1 %2" ).arg( sDefault, QString::number(idx) );

         if (pszCompPfx1 && idx < 10)
            //sSubCompPrefix.Format( pszCompPfx1, idx );
            sSubCompPrefix = QString( pszCompPfx1 ).arg( QString::number(idx) );
         else if (pszCompPfx2 && idx < 100)
            sSubCompPrefix = QString( pszCompPfx2 ).arg( QString::number(idx) );
         else if (pszCompPfx3 && idx < 1000)
            sSubCompPrefix = QString( pszCompPfx3 ).arg( QString::number(idx) );
         else
            sSubCompPrefix.clear();
      } while ( BEMPX_GetComponentByNameQ( sDefName, FALSE, iBEMProcIdx ) != NULL  &&
                (sSubCompPrefix.isEmpty() || BEMPX_GetComponentByNameQ( sSubCompPrefix, FALSE, iBEMProcIdx, FALSE, TRUE ) != NULL) );
   }

   return idx;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetComponentByName()
//
// Purpose ------------------------------------------------------------------
//   Check to see if a particular component name is unique and therefore can
//   be used to name a new building component.
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR lpszName       : name to be checked for uniqueness
//   BOOL   bCheckLibsOnly : TRUE if we are to only check through libraries for object
//   
// Return Value -------------------------------------------------------------
//   A pointer to the existing object by this name, else NULL.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* BEMPX_GetComponentByName( LPCSTR lpszName, BOOL bCheckLibsOnly, int iBEMProcIdx /*=-1*/,
                                   BOOL bSkipCheckingRuleLib, BOOL bNameIsPrefix /*=FALSE*/ )
{	QString sName = lpszName;
	return BEMPX_GetComponentByNameQ( sName, bCheckLibsOnly, iBEMProcIdx, bSkipCheckingRuleLib, bNameIsPrefix );
}

BEMObject* BEMPX_GetComponentByNameQ( QString& sName, BOOL bCheckLibsOnly, int iBEMProcIdx /*=-1*/,
                                   BOOL bSkipCheckingRuleLib, BOOL bNameIsPrefix /*=FALSE*/ )
{
   int iError;
   // loop over all object types
   for (int iType = (bCheckLibsOnly ? 1 : 0); iType < BEMO_NumTypes; iType++)
      // last argument (bSkipCheckingRuleLib) to implement new unique name checking which allows user/rulelib dup names
      if (!bSkipCheckingRuleLib  ||  iType != BEMO_RuleLib)
      {
         BEM_ObjType eObjType = (BEM_ObjType) iType;

         // loop over all classes, attempting to find a component by this type and name
         //assert( iBEMProcIdx >= 0 && iBEMProcIdx < BEMO_NumBEMProcObjects );
         for (int i1Class = 1; i1Class <= eBEMProc.getNumClasses(); i1Class++)
         {
            BEMObject* pObj = BEMPX_GetObjectByName( i1Class, iError, sName.toLocal8Bit().constData(), eObjType, iBEMProcIdx, bNameIsPrefix ); 
            if (pObj)
               return pObj;
         }
      }

   return NULL;
}

// static function to convert "Component Name (Copy??)" -> "Component Name"
static void GetBaseComponentName( QString sFullName, QString& sBaseName )
{
   int iCopyIdx = sFullName.indexOf( "(Copy" );
   while (iCopyIdx > 0)
   {
      // Confirm that this '(Copy' is near enought to end of name to be a copy indicator and not
      // just a part of the actual component name
      if (sFullName.length() <= (iCopyIdx+10))
      {
         if (sFullName[ iCopyIdx-1 ] == ' ')
            iCopyIdx--;  // Remove the space before '(Copy' if one exists

         sBaseName = sFullName.left( iCopyIdx );  // set base name
         return;
      }
      // perhaps the NEXT occurence of '(Copy' is the one we are looking for
      iCopyIdx = sFullName.indexOf( "(Copy", iCopyIdx+1 );
   }

   sBaseName = sFullName;
   return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SetObjectCopyName()
//
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_SetObjectCopyName( QString& sCopyName, LPCSTR lpszOriginalName, BOOL bCheckFirst, int iBEMProcIdx /*=-1*/ )
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;

   sCopyName = lpszOriginalName;
   if (bCheckFirst && BEMPX_GetComponentByNameQ( sCopyName, FALSE, iBEMProcIdx, TRUE ) == NULL)
      return true;  // return true if original name already unique
   else
   {
      QString sRoot;
      GetBaseComponentName( sCopyName, sRoot );
      sCopyName = sRoot;
      sCopyName += "-2";	// was:  += " (Copy)";
      int i=3;  // 2;
      while (i < 10000 && BEMPX_GetComponentByNameQ( sCopyName, FALSE, iBEMProcIdx, TRUE ) != NULL)
         sCopyName = QString("%1-%2").arg( sRoot, QString::number(i++) );

      return (i<10000);
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetObjectByClass()
//
// Purpose ------------------------------------------------------------------
//   Get a pointer to an object (building component).
//   
// Arguments ----------------------------------------------------------------
//   int        i1BEMClass : 1-based class (component type) index
//   int&       iError    : Address of an error code value set by the function
//   int        iObjIdx   : (default = -1) index of object to get the pointer of (-1 => active object)
//   BEM_ObjType eObjType  : (default = BEMO_User) type of object to get the pointer of
//   
// Return Value -------------------------------------------------------------
//   NULL if an error occurs, otherwise a pointer to the desired object.
//   iError is set to the following values:
//        0  =>  OK
//       -1  =>  invalid class argument
//       -2  =>  invalid object index argument
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* BEMPX_GetObjectByClass( int i1BEMClass, int& iError, int iObjIdx, BEM_ObjType eObjType,
                          int iBEMProcIdx /*=-1*/ )
{
   BEMObject* pRetVal = NULL;
   iError = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // set iObjIdx and eObjType for default case => getting 'active' user defined object
	if (eObjType == BEMO_User && iObjIdx == -1)
	{	iObjIdx  = pBEMProc->getClass( i1BEMClass-1 )->getCurrentBEM0ObjIdx();
		eObjType = pBEMProc->getClass( i1BEMClass-1 )->getCurrentBEMObjType();
	}

   // get total number of objects of this type
   int iCount = BEMPX_GetNumObjects( i1BEMClass, eObjType, iBEMProcIdx );
   if (iCount < 0)
      iError = iCount;
   else
   {  // i1BEMClass must be valid
      if (eObjType != BEMO_User && iObjIdx == -1)
         iObjIdx = pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( eObjType ) - 1;
      if (iObjIdx >= iCount)
         iError = -2;
      else
      {	pRetVal = pBEMProc->getClass( i1BEMClass-1 )->GetObject( eObjType, iObjIdx );					assert( pRetVal );
      }
   }

   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetObjectByName()
//
// Purpose ------------------------------------------------------------------
//   Get the pointer to an object of a specified class, type and name.
//   
// Arguments ----------------------------------------------------------------
//   int         i1BEMClass : 1-based class (component type) index
//   int&        iError    : Address of an error code value set by the function
//   const char* pObjName  : Name of object to return pointer to
//   BEM_ObjType  eObjType  : (default = BEMO_User) Type of object to return pointer to
//   
// Return Value -------------------------------------------------------------
//   NULL if an error occurred or if the object was not found, else a pointer
//   to the desired object.
//   iError is set to:  0 : OK
//                     -1 : invalid class
//                     -2 : no objects of this type exist
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
// bNameIsPrefix argument to enable checking for components for which the lpszName is only the beginning of a component name
BEMObject* BEMPX_GetObjectByName(	int i1BEMClass, int& iError, const char* pObjName,
												BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/, BOOL bNameIsPrefix )
{	QString qsObjName = pObjName;
	return BEMPX_GetObjectByNameQ(	i1BEMClass, iError, qsObjName, eObjType, iBEMProcIdx, bNameIsPrefix );
}

BEMObject* BEMPX_GetObjectByNameQ(	int i1BEMClass, int& iError, QString& qsObjName,
												BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/, BOOL bNameIsPrefix )
{
   BEMObject* pRetVal = NULL;
   iError = 0;
   // get the total number of objects of this class and type
   int iCount = BEMPX_GetNumObjects( i1BEMClass, eObjType, iBEMProcIdx );
   if (iCount < 0)
      iError = iCount;
   else if (iCount == 0)
      iError = -2;
   else
   {  BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   	//QString qsObjName = pObjName;

      // i1BEMClass must be valid and there are at least one object of the desired type
		int iNumObjs = pBEMProc->getClass( i1BEMClass-1 )->ObjectCount( eObjType );
		for (int ib=0; (pRetVal == NULL && ib < iNumObjs); ib++)
		{	BEMObject* pObj = pBEMProc->getClass( i1BEMClass-1 )->GetObject( eObjType, ib );			assert( pObj );
         // check for object valid and name match
         if ( pObj != NULL  &&
              ( (!bNameIsPrefix && qsObjName.compare( pObj->getName(), Qt::CaseInsensitive ) == 0) ||
                ( bNameIsPrefix && qsObjName.compare( pObj->getName().left( qsObjName.length() ), Qt::CaseInsensitive ) == 0) ) )
            pRetVal = pObj;  // set return value to object pointer
      }
   }

   return pRetVal;  
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetParentObjectByName()
//
// Purpose ------------------------------------------------------------------
//   Get the pointer to an object of a specified type and name which is a legal
//   parent for a specified class (component type) of child object.
//   
// Arguments ----------------------------------------------------------------
//   int         i1ChildClass : 1-based class (component type) index of child
//   int&        iError       : Address of an error code value set by the function
//   const char* pObjName     : Name of parent object to get the pointer of
//   BEM_ObjType  eObjType     : (default = BEMO_User) Type of parent object to get the pointer of
//   
// Return Value -------------------------------------------------------------
//   NULL if an error occurred or if the object was not found, else a pointer
//   to the desired object.
//   iError is set to:  0 : OK
//                     -1 : invalid child class
//                     -2 : no objects of this type exist
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* BEMPX_GetParentObjectByName( int i1ChildClass, int& iError, const char* pObjName,
                                      BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{	QString qsObjName = pObjName;
	return BEMPX_GetParentObjectByNameQ( i1ChildClass, iError, qsObjName, eObjType, iBEMProcIdx );
}

BEMObject* BEMPX_GetParentObjectByNameQ( int i1ChildClass, int& iError, QString& qsObjName,
                                      BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   BEMObject* pRetVal = NULL;
   iError = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // confirm that the child class index is valid
   if (i1ChildClass < 1 && i1ChildClass > pBEMProc->getNumClasses())
      iError = -1;
   // If pObjName has zero length, then keep iError = 0 and simply return NULL
   else if (qsObjName.length() <= 0)  // strlen(pObjName) <= 0)
   {  }
   else
   {
      // loop over all parent classes of this child class
      for (int iPar=0; (pRetVal == NULL &&				// SAC 8/18/12 - remove 'iError >= 0' condition since it can fail on parent types prior to the active/pertinent one
                          iPar < BEM_MAX_PARENT_TYPES && 
                          pBEMProc->getClass( i1ChildClass-1 )->getParentType( iPar ) > -1); iPar++)
      {
         // Get object pointer from the class, name and type values
         pRetVal = BEMPX_GetObjectByNameQ( pBEMProc->getClass( i1ChildClass-1 )->getParentType( iPar ) + 1,
                                        iError, qsObjName, eObjType, iBEMProcIdx );
      }
   }

   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetObjectIndex()
//
// Purpose ------------------------------------------------------------------
//   Get the index of either the active object for a particular class or for
//   a specified object.
//   
// Arguments ----------------------------------------------------------------
//   BEMClass*  pClass  : Pointer to the class from which the object index is desired
//   BEMObject* pObject : (default = NULL) NULL if active object is desired, OR object pointer
//   
// Return Value -------------------------------------------------------------
//   >=0 : 0-Based object index 
//    -1 : invalid class
//    -3 : no objects of this type exist
//    -4 : object not found
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetObjectIndex( BEMClass* pClass, BEMObject* pObject, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = -4;
   if (pClass == NULL)
      iRetVal = -1;  // Error - invalid class pointer
   else
   {
      if (pObject == NULL)
         iRetVal = pClass->getCurrentBEM0ObjIdx();  // return value = active object's index
      else
      {
         // get total number of objects for this class and type
         int iCount = BEMPX_GetNumObjects( pClass->get1BEMClassIdx(), pObject->getObjectType(), iBEMProcIdx );
         if (iCount < 0)
            iRetVal = iCount;  // Error - getting number of objects
         else if (iCount == 0)
            iRetVal = -3;  // Error - no objects of this class and type exist
         else
         {  // there are at least one object of the desired type
            int iError = 0;
            // loop over all objects of this class and type searching for a pObject match
            for (int i=0; (iRetVal==-4 && iError==0 && i<iCount); i++)
            {
               BEMObject* pObj = BEMPX_GetObjectByClass( pClass->get1BEMClassIdx(), iError, i, pObject->getObjectType(), iBEMProcIdx );
               if (pObj == pObject)
                  iRetVal = i;  // found pObject match
            }
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetChildObjectIndex()
//
// Purpose ------------------------------------------------------------------
//   Gets the object type and index of a certain child of a specified object.
//   
// Arguments ----------------------------------------------------------------
//   int         i1BEMClass     : 1-based class (component type) index
//   int         i1ChildClass  : 1-based class (component type) index of child
//   int&        iError        : Address of an error code value set by the function
//   BEM_ObjType& eChildObjType : Address of an object type variable to be set
//                               to the desired child object's type
//   int         i1ChildIdx    : (default = 1) 1-based index of the child object to get
//   int         iObjIdx       : (default = -1) 0-based Object index of the parent object (-1 => active object)
//   BEM_ObjType  eObjType      : (default = BEMO_User) Object type of the parent object
//   
// Return Value -------------------------------------------------------------
//   -1 if an error has occurred, else the integer index of the desired child object.
//   In addition to the return value being set, the eChildObjType argument is also
//   set to the type of object the desired child is.
//   iError is passed to the BEMPX_GetObjectByClass() function and returns negative if
//   an error occurred in getting the parent object pointer.  iError is set to
//   -1 later in the BEMPX_GetChildObjectIndex() if an error occurs.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetChildObjectIndex( int i1BEMClass, int i1ChildClass, int& iError, BEM_ObjType& eChildObjType,
                               int i1ChildIdx, int iObjIdx, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = -1;

   // get parent object pointer
   BEMObject* pObj = BEMPX_GetObjectByClass( i1BEMClass, iError, iObjIdx, eObjType, iBEMProcIdx );
   if (iError >= 0 && pObj && i1ChildClass > 0)
   {
		int iNumChildren = pObj->getChildCount();
		for (int iC=0; (iError >= 0 && iRetVal == -1 && iC < iNumChildren); iC++)
		{
			BEMObject* pChildObj = pObj->getChild( iC );

         if (pChildObj == NULL)
            iError = -1;  // Error - getting child object pointer
         else if (pChildObj->getClass()->get1BEMClassIdx() == i1ChildClass)
         {
            if (i1ChildIdx > 1)
               i1ChildIdx--;  // decrement child index until it = 1
            else
            {  // found proper child obj, now get it's object index
               iRetVal = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj, iBEMProcIdx );

               if (iRetVal < 0)
                  iError = -1;  // Error - getting child's object index
               else
                  eChildObjType = pChildObj->getObjectType();
            }
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetCurrentObjectType()
//
// Purpose ------------------------------------------------------------------
//   Gets the type of object currently designated as the active object of a
//   specified class.
//   
// Arguments ----------------------------------------------------------------
//   int i1BEMClass  : 1-based class (component type) index
//   
// Return Value -------------------------------------------------------------
//   The type of the active object (or BEMO_NumTypes if there is no active object).
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEM_ObjType BEMPX_GetCurrentObjectType( int i1BEMClass, int iObjIdx, int iBEMProcIdx /*=-1*/ )
{
   BEM_ObjType eRetVal = BEMO_NumTypes;
   int iError;
   // get pointer to class and confirm that it is OK
	BEMClass* pClass = BEMPX_GetClass( i1BEMClass, iError, iBEMProcIdx );
   if ( iError == 0 && pClass != NULL )
   {
      if (iObjIdx < 0 || iObjIdx >= pClass->ObjectCount( BEMO_User ))
         eRetVal = pClass->getCurrentBEMObjType();
      else
      {
         BEMObject* pObj = BEMPX_GetObjectByClass( i1BEMClass, iError, iObjIdx, BEMO_User, iBEMProcIdx );
         if (iError >= 0 && pObj != NULL)
            eRetVal = pObj->getObjectType();
      }
   }
   return eRetVal;
}



/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetProperty()
//
// Purpose ------------------------------------------------------------------
//   Gets the pointer to a property identified by the function arguments.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : 6 digit database ID CCPPAA (comp/property/array)
//   int&       iError   : Address of an error code value set by the function
//   int        iOccur   : (default = -1) 0-based index into list of objects (-1 => "current")
//   BEM_ObjType eObjType : (default = BEMO_User) object type for which property is being returned
//   
// Return Value -------------------------------------------------------------
//   NULL if error occurred in getting property, else pointer to desired property.
//   iError set to:  0 : All OK
//                  -1 : invalid class
//                  -2 : invalid property index
//                  -3 : invalid array index
//                  -4 : invalid iOccur
//                  -5 : error retrieving object at specified occurence
//                  -6 : error retrieving property
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BEMProperty* BEMPX_GetProperty( long lDBID, int& iError, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   BEMProperty* pRetVal = NULL;
   iError = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // get the various DB IDs and property type pointer from the lDBID
   int i1Class = BEMPX_GetClassID(    lDBID );
   int i1Param = BEMPX_GetPropertyID( lDBID );
   int i1Array = BEMPX_GetArrayID(    lDBID );
   BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Param, iBEMProcIdx );

   if (i1Class < 1 || i1Class > pBEMProc->getNumClasses())
      iError = -1;
   else if (i1Param < 1 || i1Param > pBEMProc->getClass( i1Class-1 )->getNumProps())
      iError = -2;
   else
   {
      if (pPropType == NULL || i1Array < 1 || i1Array > pPropType->getNumValues())
         iError = -3;
      else
      {
         BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iOccur, eObjType, iBEMProcIdx );
         if (pObj == NULL)
            iError = -5;
         else
         {
            int iPropListIdx = pPropType->getSumOfPreviousProperties() + i1Array - 1;
            if (iPropListIdx < 0 || iPropListIdx >= pObj->getPropertiesSize())
               iError = -6;
            else
				{	pRetVal = (BEMProperty*) pObj->getProperty( iPropListIdx );						assert( pRetVal );
				}
	}	}	}

   return pRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  PostDataModReset()
//
// Purpose ------------------------------------------------------------------
//   Called following a user data mod or restore default to cause all data
//   which gets reset as a result of this mod to get reset and then to
//   default the object which it describes.
//   
// Arguments ----------------------------------------------------------------
//   
// Return Value -------------------------------------------------------------
//   None.
//   
// Notes --------------------------------------------------------------------
//   Created from BEMPX_SetBEMData()
//   
/////////////////////////////////////////////////////////////////////////////
static void PostDataModReset( BEMProperty* pProp, long lDBID, BEM_PropertyStatus eStatus, int i1Class,
                              int iOccur, BEM_ObjType eObjType, BOOL bDataModified, BOOL bPerformResets, int iBEMProcIdx /*=-1*/ )
{
   int iError;

   // reinitialize all data in this property's ResetData list if this modification is a user input
   if (pProp && eStatus == BEMS_UserDefined && bPerformResets)
      pProp->ReinitResetData( lDBID, (iOccur >= 0 ? iOccur :
                                      BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ) )) );

   // re-default object w/ UserDefined default flag FALSE so that only hard-coded defaulting will occur
   BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iOccur, eObjType, iBEMProcIdx );
   if (pObj != NULL)
      pObj->DefaultObject( iOccur, FALSE, lDBID, eStatus, bDataModified );
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_DefaultProperty()
//
// Purpose ------------------------------------------------------------------
//   Default a particular property of the specified object.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : 6 digit database ID CCPPAA (comp/property/array)
//   int&       iError   : Address of an error code value set by the function
//   int        iOccur   : (default = -1) 0-based occurence index of object
//                         who's property is tp be defaulted (-1 => "Active" object)
//   BEM_ObjType eObjType : (default = BEMO_User) type of object being defaulted
//   
// Return Value -------------------------------------------------------------
//   TRUE if OK, else FALSE (=> the lDBID didn't translate into valid object
//   and property pointers OR the BEMProperty::Default() function returned FALSE).
//   iError set by BEMPX_GetObjectByClass() and BEMPX_GetProperty() indicating errors
//   occurring in those functions.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_DefaultProperty(	long lDBID, int& iError, int iOccur,
										BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   bool bRetVal = FALSE;
   // get class index from lDBID
   int i1Class = BEMPX_GetClassID( lDBID );
   // get object pointer from class and occurrence indices
   BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iOccur, eObjType, iBEMProcIdx );
   if (iError >= 0)
   {
      // get property pointer from lDBID and occurrence index
      BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );
      if (iError >= 0 && pObj && pProp)
      {
         if (iOccur == -1)  // must have actual iOccur for property->Default()
            iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx );	// SAC 4/28/14 - added iBEMProcIdx to args passed
			if (iOccur >= 0)
         {	// default property value
         	bRetVal = pProp->Default( lDBID, iOccur, pObj->getObjectType(), FALSE /*bReinitializing*/, iBEMProcIdx );	// SAC 4/28/14 - added iBEMProcIdx to args passed

         	// cause ruleset Resets to occur
         	PostDataModReset( pProp, lDBID, BEMS_UserDefined, i1Class, iOccur, eObjType, TRUE, TRUE, iBEMProcIdx );
			}
			else
			{	assert( false );
      }	}
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDataStatus()
//
// Purpose ------------------------------------------------------------------
//   Get the status flag of a database property.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID    : 6 digit database ID CCPPAA (comp/property/array)
//   int        iOccur   : (default = -1) 0-based index into list of objects (-1 => "current")
//   BEM_ObjType eObjType : (default = BEMO_User ) Type of object to retrieve the data status from
//   
// Return Value -------------------------------------------------------------
//   Successful return values:
//       (refer to enum BEM_PropertyStatus values)
//   Errors:
//      -1 : invalid class
//      -2 : invalid property index
//      -3 : invalid array index
//      -4 : invalid iOccur
//      -5 : error retrieving object at specified occurence index
//      -6 : could not get database property
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetDataStatus( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = -6;
   int iError;
   int i1Class = BEMPX_GetClassID( lDBID );
   if (i1Class > 0 && i1Class <= eBEMProc.getNumClasses())
   {
      if (BEMPX_GetPropertyID( lDBID ) == 0)
      {  // data status for Active, Name, Parent
         iRetVal = BEMS_UserDefined;
      }
      else
      {  // data status for standard database variables
         BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );
         if (iError < 0)
            iRetVal = iError;
         else if (pProp != NULL)
            iRetVal = pProp->getDataStatus();
      }
   }
   return iRetVal;
}



/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetDataType()
//
// Purpose ------------------------------------------------------------------
//   Gets the data type flag for a particular database variable.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   integer >= 0 if OK (BEMP_Int, BEMP_Flt, BEMP_Sym, BEMP_Str or BEMP_Obj), OR
//             -1 if an error has occurred.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetDataType( long lDBID )
{
   int iRetVal = -1;
   int i1Class = BEMPX_GetClassID( lDBID );
   if (i1Class > 0 && i1Class <= eBEMProc.getNumClasses())
   {
      int i1Prop  = BEMPX_GetPropertyID( lDBID );
      if (i1Prop == 0)
      {  // datatype for Active, Name, Parent
         iRetVal = BEMP_Str;
      }
      else
      {  // datatype for standard database variables
         BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Prop );
         if (pPropType != NULL)
            iRetVal = pPropType->getPropType();
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetData()
//
// Purpose ------------------------------------------------------------------
//   Retrieve data from the database, typically to populate an interface control
//   or to evaluate a compliance rule.
//   
// Arguments ----------------------------------------------------------------
//   long       lDBID       : 6 digit database ID CCPPAA (comp/property/array)
//   int&       iDataType   : address of integer to populate with type of data being retrieved
//   int&       iSpecialVal : address of integer to populate with 'special value'
//   int&       iError      : Address of an error code value set by the function
//   int        iOccur      : (default = -1) occurence number of object to retrieve data from (-1 => active object)
//   BEM_ObjType eObjType    : (default = BEMO_User) type of object to retrieve data from
//   
// Return Value -------------------------------------------------------------
//   Pointer to the data stored in the requested property, or NULL if an error occurred.
//   iError is passed on to BEMPX_GetObject() and BEMPX_GetProperty() and therefore
//   will be populated with an informative error code describing what prevented
//   the successful completion of this function.
//
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
//void* BEMPX_GetData( long lDBID, int& iDataType, int& iSpecialVal, int& iError, int iOccur,
//                     BEM_ObjType eObjType, BOOL bReturnParentObject, int iBEMProcIdx /*=-1*/ )
//{	int iStatus;
//	return BEMPX_GetDataAndStatus( lDBID, iStatus, iDataType, iSpecialVal, iError, iOccur, eObjType, bReturnParentObject, iBEMProcIdx );
//}
// SAC 4/4/16 - replaced above routine that returned generic pointer to BEM data w/ the following routines to return more BEM data by type
long BEMPX_GetInteger( long lDBID, int& iSpecialVal, int& iError, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{	int iStatus;
	return BEMPX_GetIntegerAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcIdx );
}
BOOL BEMPX_GetInteger( long lDBID, long& lData, long lDefault /*=0*/, int /*iDispDataType=-1*/,		// for backward compatibility with BEMPX_SetDataInteger
										int iOccur /*=-1*/, int iObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{	int iStatus, iSpecialVal, iError;
	lData = BEMPX_GetIntegerAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, (BEM_ObjType) iObjType, iBEMProcIdx );
	if (iStatus < 1)
		lData = lDefault;
	return (iStatus > 0);
}

double BEMPX_GetFloat( long lDBID, int& iSpecialVal, int& iError, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/,
                               bool bAllowNonFloatDataTypes /*=false*/, double dDefault /*=-1.0*/ )
{	int iStatus;
	return BEMPX_GetFloatAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcIdx, bAllowNonFloatDataTypes, dDefault );
}
BOOL BEMPX_GetFloat(   long lDBID, double& fData, double fDefault /*=0*/, int iDispDataType /*=-1*/,
										int iOccur /*=-1*/, int iObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{	int iStatus, iSpecialVal, iError;
	fData = BEMPX_GetFloatAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, (BEM_ObjType) iObjType, iBEMProcIdx, (iDispDataType != BEMP_Flt), fDefault );
	return (iStatus > 0);
}

QString BEMPX_GetString( long lDBID, int& iSpecialVal, int& iError, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/,
                               BOOL bAddCommas /*=TRUE*/, int iPrecision /*=0*/, const char* pszDefault /*=NULL*/, long lDBID2 /*=0*/ )
{	int iStatus;
	return BEMPX_GetStringAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcIdx, bAddCommas, iPrecision, pszDefault, lDBID2 );
}
BOOL BEMPX_GetString(  long lDBID, QString& sStr, BOOL bAddCommas /*=TRUE*/, int iPrecision /*=0*/,		// for backward compatibility with BEMPX_SetDataString
										int /*iDispDataType=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/,
										const char* pszDefault /*=NULL*/, long lDBID2 /*=0*/, int iBEMProcIdx /*=-1*/ )
{	int iStatus, iSpecialVal, iError;
	sStr = BEMPX_GetStringAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, (BEM_ObjType) iObjType, iBEMProcIdx, bAddCommas, iPrecision, pszDefault, lDBID2 );
	return (iStatus > 0);
}

BEMObject* BEMPX_GetObjectPtr( long lDBID, int& iSpecialVal, int& iError, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{	int iStatus;
	return BEMPX_GetObjectAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, eObjType, iBEMProcIdx );
}
BOOL BEMPX_GetObject( long lDBID, BEMObject*& pObj, int /*iDispDataType=-1*/, int iOccur /*=-1*/,		// for backward compatibility with BEMPX_SetDataObject
										int iObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{	int iStatus, iSpecialVal, iError;
	pObj = BEMPX_GetObjectAndStatus( lDBID, iStatus, iSpecialVal, iError, iOccur, (BEM_ObjType) iObjType, iBEMProcIdx );
	return (iStatus > 0);
}


// SAC 1/9/14 - added new GetBEMData routine to return both data & status
//void* BEMPX_GetDataAndStatus( long lDBID, int& iStatus, int& iDataType, int& iSpecialVal, int& iError, int iOccur /*=-1*/,
//                     BEM_ObjType eObjType /*=BEMO_User*/, BOOL bReturnParentObject /*=FALSE*/, int iBEMProcIdx /*=-1*/ )
long    BEMPX_GetIntegerAndStatus( long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                               int iOccur /*=-1*/, BEM_ObjType eObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{	long lRetVal = -1;
	iStatus = 0;
   iSpecialVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   int l1Class = BEMPX_GetClassID( lDBID );
   int l1Prop  = BEMPX_GetPropertyID( lDBID );
   if (l1Class > 0 && l1Class <= pBEMProc->getNumClasses())
   {	if (l1Prop == 0)
   	{	if (BEMPX_GetArrayID( lDBID ) == BEM_PARAM0_ACTION)
			{   }  // do nothing 
			else
			{	assert( false );		// no other Prop=0 data can be described as Integer
			}
		}
		else	// liProp > 0
		{	BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );
			if (iError >= 0 && pProp)
			{	iSpecialVal = pProp->getSpecialValue();
				switch (pProp->getType()->getPropType())
				{	case BEMP_Int	:
					case BEMP_Sym	:	iStatus = pProp->getDataStatus();
											if (iStatus > 0)
												lRetVal = pProp->getInt();
											break;
					default			:	assert( false );		// invalid data type for retrieval of Integer
											break;
			}	}
			else
			{	assert( eObjType == BEMO_RuleLib );		// invalid property - CAN happen during rule library read/parse
			}
		}
	}
	else
	{	assert( false );		// invalid class
	}
	return lRetVal;
}

//	iStatus remains 0 unless number returned
double  BEMPX_GetFloatAndStatus(   long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                               int iOccur /*=-1*/, BEM_ObjType eObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/,
                               bool bAllowNonFloatDataTypes /*=false*/, double dDefault /*=-1.0*/ )
{	double dRetVal = dDefault;
	iStatus = 0;
   iSpecialVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   int l1Class = BEMPX_GetClassID( lDBID );
   int l1Prop  = BEMPX_GetPropertyID( lDBID );
   if (l1Class > 0 && l1Class <= pBEMProc->getNumClasses())
   {	if (l1Prop == 0)
   	{	if (BEMPX_GetArrayID( lDBID ) == BEM_PARAM0_ACTION)
			{   }  // do nothing 
			else
			{	assert( false );		// no other Prop=0 data can be described as Integer
			}
		}
		else	// liProp > 0
		{	BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );
			if (iError >= 0 && pProp)
			{	iSpecialVal = pProp->getSpecialValue();
				switch (pProp->getType()->getPropType())
				{	case BEMP_Flt	:	iStatus = pProp->getDataStatus();
											if (iStatus > 0)
												dRetVal = pProp->getDouble();
											break;
					case BEMP_Int	:
					case BEMP_Sym	:	if (!bAllowNonFloatDataTypes)
											{	assert( false );
											}
											else
											{	iStatus = pProp->getDataStatus();
												if (iStatus > 0)
													dRetVal = (double) pProp->getInt();
											}
											break;
					case BEMP_Obj	:	if (!bAllowNonFloatDataTypes)
											{	assert( false );
											}
											else
											{	BEMObject* pObj = pProp->getObj();
												if (pObj && pObj->getClass())
												{	iStatus = pProp->getDataStatus();
													if (iStatus > 0)
														dRetVal = (double) (BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx ) + 1);
											}	}
											break;
					default			:	assert( false );		// invalid data type for retrieval of Float
											break;
			}	}
			else
			{	assert( false );		// invalid property
			}
		}
	}
	else
	{	assert( false );		// invalid class
	}
	return dRetVal;
}

int BEMPX_GetFloatArray( long lDBID, double* pdData, int iMaxValues, double dDefault /*=0*/,
						int iDispDataType /*=-1*/, int iOccur /*=-1*/, int iObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{
   int iNumValuesSet = 0;
   if (iDispDataType < 0)
      iDispDataType = BEMPX_GetDataType( lDBID );
// SAC 8/7/00 - Modified code to return 1-based component index if the data type == BEMP_Obj
   if ( iDispDataType == BEMP_Flt || iDispDataType == BEMP_Int || iDispDataType == BEMP_Sym || iDispDataType == BEMP_Obj )
   {
      int iError, iStatus, iSpecialVal;
      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
      int i1Array = BEMPX_GetArrayID( lDBID );
      if (pPropType  &&  i1Array > 0  &&  i1Array <= pPropType->getNumValues())
      {
         int iNumItemsToGet = std::min( iMaxValues, pPropType->getNumValues() - i1Array + 1 );
         BOOL bOK = TRUE;		double dData;
         for (int iArr=0; (bOK && iArr<iNumItemsToGet); iArr++)
         {
            dData = BEMPX_GetFloatAndStatus( lDBID+iArr, iStatus, iSpecialVal, iError, iOccur,
																(BEM_ObjType) iObjType, iBEMProcIdx, true /*bAllowNonFloatDataTypes*/ );
				if (iStatus > 0)
				{	pdData[iArr] = dData;
					iNumValuesSet++;
				}
	         else
					bOK = FALSE;
         }
      }
   }
   for (int i=iNumValuesSet; i<iMaxValues; i++)
      pdData[i] = dDefault;

   return iNumValuesSet;
}

QString BEMPX_GetStringAndStatus(  long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                               int iOccur /*=-1*/, BEM_ObjType eObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/,
                               BOOL bAddCommas /*=TRUE*/, int iPrecision /*=0*/, const char* pszDefault /*=NULL*/, long lDBID2 /*=0*/ )
{	QString sRetVal;
	iStatus = 0;
   iSpecialVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   int l1Class = BEMPX_GetClassID( lDBID );
   int l1Prop  = BEMPX_GetPropertyID( lDBID );
   if (l1Class > 0 && l1Class <= pBEMProc->getNumClasses())
   {	if (l1Prop == 0)
   	{	int l1Array = BEMPX_GetArrayID( lDBID );
			if ( l1Array == BEM_PARAM0_ACTIVE || l1Array == BEM_PARAM0_NEWCOPY ||
				  l1Array == BEM_PARAM0_NEWPAR )
			{
				iError = 0;
				BEMObject* pObj = NULL;
				if (l1Array == BEM_PARAM0_NEWPAR)
				{  // if we are grabbing the proposed new parent name, then confirm the getCurrentParent()
					// pointer not NULL and that that object can handle another child of this type
					if (pBEMProc->getClass( l1Class-1 )->getCurrentParent() && 
						 BEMPX_CanCreateAnotherChildObject( l1Class, pBEMProc->getClass( l1Class-1 )->getCurrentParent(), 1, iBEMProcIdx ))
						pObj = pBEMProc->getClass( l1Class-1 )->getCurrentParent();
					else
						// reset l1Class to grab currently active object below
						l1Class = pBEMProc->getClass( l1Class-1 )->getParentType(0) + 1;
				}
				// set pointer to object if it is currently NULL
				if (pObj == NULL)
					pObj = BEMPX_GetObjectByClass( (int) l1Class, iError, -1, BEMO_User, iBEMProcIdx );
				if (iError >= 0 && pObj)
				{  // set the return value to be a pointer to the object's name string
					iStatus = BEMS_UserDefined;
					if (iStatus > 0)
						sRetVal = pObj->getName();
				}
			}
			else if (l1Array == BEM_PARAM0_PARCLAS)
			{
				int i0ParClassIdx = pBEMProc->getClass( l1Class-1 )->getParentType(0);
				if (i0ParClassIdx >= 0)
				{  iStatus = BEMS_UserDefined;
					iError = 0;
					sRetVal = pBEMProc->getClass( i0ParClassIdx )->getLongName();
				}
			}
			else if (l1Array == BEM_PARAM0_ACTION)
			{	}  // do nothing
			else
			{
				BEMObject* pObj = BEMPX_GetObjectByClass( (int) l1Class, iError, iOccur, eObjType, iBEMProcIdx );
				if (iError >= 0 && pObj)
				{
					iStatus = BEMS_UserDefined;
					if (l1Array == BEM_PARAM0_NAME)
						sRetVal = pObj->getName();
					else if (l1Array == BEM_PARAM0_PARENT && pObj->getParent())
						sRetVal = pObj->getParent()->getName();
				}
			}
		}
		else	// liProp > 0
		{	BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );

			if (pProp && pProp->getType()->getPropType() == BEMP_Obj && pProp->getObj() && lDBID2 > 0)
			{	// actual data to be retrieved is from lDBID2 (of the object identified by lDBID)
				iOccur = BEMPX_GetObjectIndex( pProp->getObj()->getClass(), pProp->getObj(), iBEMProcIdx );
				pProp = BEMPX_GetProperty( lDBID2, iError, iOccur, pProp->getObj()->getObjectType(), iBEMProcIdx );
			}

			if (iError >= 0 && pProp)
			{	iSpecialVal = pProp->getSpecialValue();
				switch (pProp->getType()->getPropType())
				{
					case BEMP_Sym :	iStatus = pProp->getDataStatus();	// SAC 9/23/16 - fix bug where string not returning when not already loaded into pProp->m_strValue
											if (iStatus > 0)
												sRetVal = BEMPX_GetSymbolString( (int) pProp->getInt(), lDBID, iOccur, eObjType, iBEMProcIdx );
											break;
					case BEMP_Str :	iStatus = pProp->getDataStatus();
											if (iStatus > 0)
												sRetVal = pProp->getString();
											break;
					case BEMP_Obj : 	iStatus = pProp->getDataStatus();
											if (iStatus > 0 && pProp->getObj())		// SAC 9/25/16 - added check to prevent access violation
												sRetVal = pProp->getObj()->getName();
											else
												sRetVal.clear();
											break;
					case BEMP_Int : 	if (iPrecision == -1 || iPrecision == -2)  // format value as DATE
											{	if (pProp->getInt() > 0)
												{
													time_t time = (time_t) pProp->getInt();
											//		tm* pTM = localtime( &time );
											//		char timeStr[32];
											//		strftime( timeStr, 31, (iPrecision == -1 ? "%H:%M, %a, %b %d, %Y" : "%m/%d/%y"), pTM );
											//		sRetVal = timeStr;
													QDateTime dt;	dt.setTime_t( time );
													sRetVal = dt.toString( (iPrecision == -1 ? "HH:mm, ddd, MMM dd, yyyy" : "MM/dd/yy") );
													iStatus = pProp->getDataStatus();
											}	}
											else // not a date/time precision value
											{	iStatus = pProp->getDataStatus();
												if (iStatus > 0)
													sRetVal = BEMPX_FloatToString( (double) pProp->getInt(), 0, bAddCommas );
											}
											break;
					case BEMP_Flt : 	iStatus = pProp->getDataStatus();
											if (iStatus > 0)
												sRetVal = BEMPX_FloatToString( pProp->getDouble(), iPrecision, bAddCommas );
											break;
					default		  :	assert( false );		// invalid data type for retrieval of String
											break;
				}
		//		// DEAL WITH SPECIALVAL
		//		if (iSpecialVal > 0)
		//			sRetVal = pszSpecial[ iSpecialVal-1 ];
			}
	}	}
	return sRetVal;
}

BEMObject* BEMPX_GetObjectAndStatus(  long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                               int iOccur /*=-1*/, BEM_ObjType eObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{
   BEMObject* pRetVal = NULL;
	iStatus = 0;
   iSpecialVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
   int l1Class = BEMPX_GetClassID( lDBID );
   int l1Prop  = BEMPX_GetPropertyID( lDBID );
   if (l1Class > 0 && l1Class <= pBEMProc->getNumClasses())
   {	if (l1Prop == 0)
	  	{	int l1Array = BEMPX_GetArrayID( lDBID );
			if ( l1Array == BEM_PARAM0_ACTIVE || l1Array == BEM_PARAM0_NEWCOPY ||
				  l1Array == BEM_PARAM0_NEWPAR )
			{	iError = 0;
				BEMObject* pObj = NULL;
				if (l1Array == BEM_PARAM0_NEWPAR)
				{  // if we are grabbing the proposed new parent name, then confirm the getCurrentParent()
					// pointer not NULL and that that object can handle another child of this type
					if (pBEMProc->getClass( l1Class-1 )->getCurrentParent() && 
						 BEMPX_CanCreateAnotherChildObject( l1Class, pBEMProc->getClass( l1Class-1 )->getCurrentParent(), 1, iBEMProcIdx ))
						pObj = pBEMProc->getClass( l1Class-1 )->getCurrentParent();
					else
						// reset l1Class to grab currently active object below
						l1Class = pBEMProc->getClass( l1Class-1 )->getParentType(0) + 1;
				}
				// set pointer to object if it is currently NULL
				if (pObj == NULL)
					pObj = BEMPX_GetObjectByClass( (int) l1Class, iError, -1, BEMO_User, iBEMProcIdx );
				if (iError >= 0 && pObj)
				{  // set the return value to be a pointer to the object's name string
					iStatus = BEMS_UserDefined;
					pRetVal = pObj;
				}
			}
			else if (l1Array == BEM_PARAM0_PARCLAS)
			{	}	// do nothing
			else if (l1Array == BEM_PARAM0_ACTION)
			{	}  // do nothing
			else
			{
				BEMObject* pObj = BEMPX_GetObjectByClass( (int) l1Class, iError, iOccur, eObjType, iBEMProcIdx );
				if (iError >= 0 && pObj)
				{
					iStatus = BEMS_UserDefined;
					if (l1Array == BEM_PARAM0_NAME)
						pRetVal = pObj;
					else if (l1Array == BEM_PARAM0_PARENT && pObj->getParent())
						pRetVal = pObj->getParent();
				}
		}	}
	   else  // retrieving standard database data
	   {
			BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iOccur, eObjType, iBEMProcIdx );
			if (iError >= 0 && pProp)
			{	iSpecialVal = pProp->getSpecialValue();
				switch (pProp->getType()->getPropType())
				{
					case BEMP_Obj	:	iStatus = pProp->getDataStatus();
											if (iStatus > 0)
												pRetVal = pProp->getObj();
											break;
					default			:	assert( false );		// invalid data type for retrieval of Object
											break;
			}	}
		}
	}
	return pRetVal;
}


////////////////////////////////////////////////////////////////////////////////

//#define  MAX_FLOAT_FORMAT  10
//static char szFmt0[]  = "%.0f";
//static char szFmt1[]  = "%.1f";
//static char szFmt2[]  = "%.2f";
//static char szFmt3[]  = "%.3f";
//static char szFmt4[]  = "%.4f";
//static char szFmt5[]  = "%.5f";
//static char szFmt6[]  = "%.6f";
//static char szFmt7[]  = "%.7f";
//static char szFmt8[]  = "%.8f";
//static char szFmt9[]  = "%.9f";
//static char szFmt10[] = "%.10f";
//const char FAR* szFmtStr[] = { szFmt0, szFmt1, szFmt2, szFmt3, szFmt4,
//                               szFmt5, szFmt6, szFmt7, szFmt8, szFmt9, szFmt10 };

static QLocale qtLocale;
//void QLocale::setNumberOptions(NumberOptions options)
//enum QLocale::FloatingPointPrecisionOption - This enum defines constants that can be given as precision to QString::number(), QByteArray::number(), and QLocale::toString() when converting floats or doubles, in order to express a variable number of digits as precision.

QString BEMPX_FloatToString( double dNum, int nRtOfDec /*=0*/, BOOL bAddCommas /*=TRUE*/,
                        int iZeroFillLeftToLength /*=0*/, BOOL bTrimTrailingDecZeroes /*=FALSE*/ )		// SAC 1/19/13 - added bTrimTrailingDecZeroes
{	QString string;

	bool bRtOfDecAdjusted = false;
	if (nRtOfDec < 0 || nRtOfDec > 10)
	{	string = QString( "%1" ).arg( QString::number( dNum ) );
		nRtOfDec = (string.indexOf('.') < 0 ? 0 : string.length() - string.indexOf('.') - 1);
	}
//	else
//		nRtOfDec = (nRtOfDec > 0 || (nRtOfDec==0 && fabs(dNum) > 0.9) ? nRtOfDec : (fabs(dNum) > 0.0001 ? 6 /*QT default*/ : 10));
	else if (nRtOfDec==0 && fabs(dNum) < 0.9)
	{	nRtOfDec = (fabs(dNum) > 0.0001 ? 6 /*QT default*/ : 10);
		bRtOfDecAdjusted = true;
	}

   if (bAddCommas)
   	string = qtLocale.toString( dNum, ((bRtOfDecAdjusted && fabs(dNum) < 0.0001) ? 'g' : 'f'), nRtOfDec );
   else
   	string = QString( "%1" ).arg( QString::number( dNum, ((bRtOfDecAdjusted && fabs(dNum) < 0.0001) ? 'g' : 'f'), nRtOfDec ) );

//   if (eiLocaleNumericNumGroupChars < 0)  // -1 here indicates Locale settings not yet loaded
//      LoadLocaleSettings();
//
//   if (nRtOfDec < 0) //  ||  nRtOfDec > MAX_FLOAT_FORMAT)
//   {
//      string = QString( "%1" ).arg( QString::number(fabs(dNum), 'g') );
//      nRtOfDec = (string.Find('.') < 0 ? 0 : string.length() - string.Find('.') - 1);
//   }
//   else
//   	//string.Format( szFmtStr[nRtOfDec], QString::number(fabs(dNum), 'f', nRtOfDec) );
//   	string = QString( "%1" ).arg( QString::number(fabs(dNum), 'f', nRtOfDec) );

	if (bTrimTrailingDecZeroes && nRtOfDec > 0)  // SAC 1/19/13 - added new argument to trim trailing 0s to right of decimal point (acts to minimize str length)
	{	int iNumLen = string.length();
		while (nRtOfDec > 0 && iNumLen > 0 && string[ iNumLen-1 ] == '0')
		{	nRtOfDec--;
			string = string.left( --iNumLen );
		}
		if (iNumLen > 0 && string[ iNumLen-1 ] == '.')  // trim trailing '.' if we removed all 0s to right of decimal
		{	assert( nRtOfDec==0 );
			string = string.left( --iNumLen );
		}
	}

//   int nLtOfDec = (string.Find('.') < 0 ? string.length() : string.Find('.'));
//// SAC 1/5/01 - apply eszLocaleNumericDecimalChars Locale setting
//   if (nLtOfDec > 0  &&  nRtOfDec > 0)
//      string = string.left( nLtOfDec ) + eszLocaleNumericDecimalChars + string.Right( nRtOfDec );
//   else if (nRtOfDec > 0)
//      string = eszLocaleNumericDecimalChars + string.Right( nRtOfDec );
//
//// SAC 1/5/01 - apply ebLocaleNumericLeadingZero Locale setting
//   if (!ebLocaleNumericLeadingZero  &&  fabs(dNum) < 1  &&  nLtOfDec == 1)
//   {
//      assert( string[0] == '0' );
//      string = string.Right( string.length()-1 );
//      nLtOfDec = 0;
//   }
//
//// SAC 1/5/01 - apply eiLocaleNumericDigitsInGroup and eszLocaleNumericGroupChars Locale settings
//   if (bAddCommas  &&  nLtOfDec > eiLocaleNumericDigitsInGroup[0])
//   {
//      int iGrpIdx = -1;
//      while (nLtOfDec > eiLocaleNumericDigitsInGroup[ max( ++iGrpIdx, 3 ) ])
//      {
//         nLtOfDec -= eiLocaleNumericDigitsInGroup[ max( iGrpIdx, 3 ) ];
//         string.Insert( nLtOfDec, eszLocaleNumericGroupChars );
//      }
//   }
//
//// SAC 1/5/01 - apply eiLocaleNumericNegativeMode and eszLocaleNumericNegativeSign Locale settings
//   if (dNum < 0)
//      switch (eiLocaleNumericNegativeMode)   // 0=>"(1.1)"  1=>"-1.1"  2=>"- 1.1"  3=>"1.1-"  4=>"1.1 -"
//      {
//         case  0:  string  = '(' + string + ')';                       break;
//         case  2:  string  = " " + string;
//                   string  = eszLocaleNumericNegativeSign + string;    break;
//         case  3:  string += eszLocaleNumericNegativeSign;             break;
//         case  4:  string += " ";
//                   string += eszLocaleNumericNegativeSign;             break;
//         default:  string  = eszLocaleNumericNegativeSign + string;    break;
//      }
//// SAC 1/5/01 - apply eszLocaleNumericPositiveSign Locale setting
//   else if (strlen( eszLocaleNumericPositiveSign ) > 0)
//      string = eszLocaleNumericPositiveSign + string;

// SAC 2/28/01 - Added code to zero fill left to achieve an overall length equivalent to new iZeroFillLeftToLength argument
   while (string.length() < iZeroFillLeftToLength)
      string = '0' + string;

   return string;
}


long BEMPX_StringToLong( const char* psLong )
{	QString sLong = psLong;
	return BEMP_StringToLong( sLong );
}
long BEMP_StringToLong( QString& sLong )
{	bool bOK;
	int iRetVal = qtLocale.toInt( sLong, &bOK );
	assert( bOK );
	return (bOK ? iRetVal : 0);
}

double BEMPX_StringToFloat( const char* psFlt )
{	QString sFlt = psFlt;
	return BEMP_StringToFloat( sFlt );
}
double BEMP_StringToFloat( QString& sFlt )
{	bool bOK;
	double dRetVal = qtLocale.toDouble( sFlt, &bOK );
	assert( bOK );
	return (bOK ? dRetVal : 0);
}


/////////////////////////////////////////////////////////////////////////////
//
// Function:  SetUserReferencedFlag()
//
// Purpose ------------------------------------------------------------------
//   Recursive function to set user referenced flag which indicates whether or
//   not a library object is directly (or indirectly) referenced by a user
//   defined object.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj  : Object to set the user referenced flag of
//   BOOL       bFlag : user referenced flag value
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void SetUserReferencedFlag( BEMObject* pObj, bool bFlag, int iBEMProcIdx )
{
   if ( pObj && pObj->getObjectType() != BEMO_User &&
        ( ( bFlag && !pObj->getUserReferenced() ) ||
          (!bFlag &&  pObj->getUserReferenced() &&
           CountObjectAssignments( pObj, FALSE, TRUE, TRUE, FALSE, FALSE, iBEMProcIdx, false ) == 0) ) )
   {	int i;
      pObj->setUserReferenced( bFlag );

      // recursively call for each child object
		int iNumChildren = pObj->getChildCount();
		for (i=0; i<iNumChildren; i++)
		{	BEMObject* pChildObj = pObj->getChild( i );						assert( pChildObj );
			if (pChildObj)
            SetUserReferencedFlag( pChildObj, bFlag, iBEMProcIdx );
      }

      // recursively call for each referenced object
		int iNumProps = pObj->getPropertiesSize();
		for (i=0; i<iNumProps; i++)
		{	BEMProperty* pProp = pObj->getProperty( i );						assert( pProp );
			if (pProp && pProp->getType())
			{	if (pProp->getType()->getPropType() == BEMP_Obj && pProp->getObj() != NULL)
					SetUserReferencedFlag( pProp->getObj(), bFlag, iBEMProcIdx );
		}	}
   }
}


/////////////////////////////////////////////////////////////////////////////

static inline void AppendEllipsis( char* pszMsg, int iMsgLen )
{	pszMsg[iMsgLen-4] = '.';
	pszMsg[iMsgLen-3] = '.';
	pszMsg[iMsgLen-2] = '.';
	pszMsg[iMsgLen-1] = '\0';
}

/////////////////////////////////////////////////////////////////////////////
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
// SAC 4/25/14 - switched prev BOOL bImportUniqueRuleLibObjects to int iImportUniqueRuleLibObjOption, w/ options:
//		0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
//		1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
//		2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
int BEMPX_SetBEMData( long lDBID, int iDataType, void* pData, BEM_ObjType eObjFrom,
                     int iOccur, BEM_PropertyStatus eStatus, BEM_ObjType eObjType, BOOL bPerformResets, int iBEMProcIdx /*=-1*/,
						   int iImportUniqueRuleLibObjOption /*=2*/,  // SAC 3/10/13	// SAC 4/25/14
							const char* pszImportRuleLibParentName /*=NULL*/,  // SAC 3/17/13 - name of parent of rule lib object to import
							char* pszErrMsg /*=NULL*/, int iErrMsgLen /*=0*/ )  // SAC 4/10/13 - error message return
{
   int iRetVal = 0;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   int i1Class = BEMPX_GetClassID( lDBID );
   int i1Prop  = BEMPX_GetPropertyID( lDBID );
   BEMProperty* pProp = NULL;
   BOOL bDataModified = FALSE;
   int iError;
   if (i1Class > 0 && i1Class <= pBEMProc->getNumClasses() && i1Prop == 0)
   {  // i1Prop == 0 => select active or parent object or rename object
      long l1Array = BEMPX_GetArrayID( lDBID );  // SAC 7/17/01 - was: lDBID % 100;
      if (l1Array == BEM_PARAM0_ACTIVE)
      {  // Reset currently active object
         BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
         if (iError >= 0 && pClass)
         {
            if (iDataType == BEMP_Str || iDataType == BEMP_QStr)  // data is string, so convert to object then set active stuff
            {	QString sObjName = (iDataType == BEMP_Str ? (const char*) pData : *((QString*) pData));
               BEMObject* pObj = BEMPX_GetObjectByNameQ( i1Class, iError, sObjName, eObjFrom, iBEMProcIdx );
            //   BEMObject* pObj = BEMPX_GetObjectByName( i1Class, iError, (const char*) pData, eObjFrom, iBEMProcIdx );
               if (iError >= 0 && pObj)
               {
                  int iObjIdx = BEMPX_GetObjectIndex( pClass, pObj, iBEMProcIdx );
                  if (iObjIdx >= 0)
                  {
                     bDataModified = (pClass->getCurrentBEM0ObjIdx() != iObjIdx ||
                                      pClass->getCurrentBEMObjType() != eObjFrom);
                     pClass->setCurrentBEM0ObjIdx( iObjIdx );
                     pClass->setCurrentBEMObjType( eObjFrom );
                  }
               }
            }
            else if (iDataType == BEMP_Int)  // data is integer => new active object index
            {
               long lNewIdx = *((long*) pData);
               int iNumObjs = BEMPX_GetNumObjects( i1Class, eObjType, iBEMProcIdx );
               if (lNewIdx >= 0 && lNewIdx < iNumObjs)
               {
                  bDataModified = (pClass->getCurrentBEM0ObjIdx() != lNewIdx ||
                                   pClass->getCurrentBEMObjType() != eObjType);
                  pClass->setCurrentBEM0ObjIdx( (int) lNewIdx );
                  pClass->setCurrentBEMObjType( eObjType );
               }
            }
         }
      }
      else if ( l1Array == BEM_PARAM0_NEWPAR  ||
                l1Array == BEM_PARAM0_NEWCOPY ||
                l1Array == BEM_PARAM0_ACTION  )
      {  }  // do nothing for NEWPAR(ent), NEWCOPY & ACTION
      // SAC - 2/25/98 - Modified to allow assignment of parent by object pointer
      else if (iDataType == BEMP_Str || iDataType == BEMP_QStr || iDataType == BEMP_Obj)
      {
         BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iOccur, eObjType, iBEMProcIdx );
         if (iError >= 0 && pObj)
         {
            if (l1Array == BEM_PARAM0_PARENT)
            {  // Get a pointer to the new parent object
            //   BEMObject* pNewParObj = (iDataType == BEMP_Obj) ? (BEMObject*) pData :
            //                              BEMPX_GetParentObjectByName( i1Class, iError, 
            //                                                         (const char*) pData, eObjType, iBEMProcIdx );
               BEMObject* pNewParObj = NULL;
               QString sObjName;
               if (iDataType == BEMP_Obj)
               	pNewParObj = (BEMObject*) pData;
               else
               {	sObjName = (iDataType == BEMP_Str ? (const char*) pData : *((QString*) pData));
               	pNewParObj = BEMPX_GetParentObjectByNameQ( i1Class, iError, sObjName, eObjType, iBEMProcIdx );
               }

               if (iError >= 0)
               {  // Reassign parent object
                  // First remove this object from previous parent's list of children
                  bool bFndAndRmvdChild = ( pObj->haveParent() && pObj->getParent()->RemoveChild( pObj ) );		bFndAndRmvdChild;

                  // And finally set the parent object pointer
                  bDataModified = (pObj->getParent() != pNewParObj);
                  pObj->setParent( pNewParObj );
                  pObj->addChildToParent();

                  // if the parent object is the getCurrentParent() AND this parent can't accept any more children
                  // of this type, then reassign the getCurrentParent() pointer
                  if (pObj->getClass() && pNewParObj == pObj->getClass()->getCurrentParent() &&
                      !BEMPX_CanCreateAnotherChildObject( pObj->getClass()->get1BEMClassIdx(), pNewParObj, 1, iBEMProcIdx ))
                     ResetCurrentParentPointers( pNewParObj, pObj->getClass()->get1BEMClassIdx(), iBEMProcIdx );
               }
               else  // couldn't find parent object
               {	iRetVal = -11;
						if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
						{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unable to find parent object '%s' (class ID %d)", sObjName /*(const char*) pData*/, i1Class ) == -1)
								AppendEllipsis( pszErrMsg, iErrMsgLen );
					}	}
            }
            else if (l1Array == BEM_PARAM0_NAME && (iDataType == BEMP_Str || iDataType == BEMP_QStr))
            {  // Rename object
            	QString sObjName = (iDataType == BEMP_Str ? (const char*) pData : *((QString*) pData));
               bDataModified = (pObj->getName() != sObjName);
               pObj->setName( sObjName );
            }
      }	}
   }
   else  // setting normal database data
   {
      pProp = BEMPX_GetProperty( lDBID, iRetVal, iOccur, eObjType, iBEMProcIdx );
      if (iRetVal < 0 || pProp == NULL)
		{	if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
			{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unable to find object property DBID=%ld, Occur=%d", lDBID, iOccur ) == -1)
					AppendEllipsis( pszErrMsg, iErrMsgLen );
		}	}
      else  // if (iRetVal >= 0 && pProp)
      {
         // Store away previous values in certain conditions in order to facilitate
         // hard-coded defaulting (i.e. Oreintation/Azimuth values)
			if (iBEMProcIdx < 0)
				iBEMProcIdx = eActiveBEMProcIdx;
      //   if (iBEMProcIdx == 0)
      //      StoreSelectedPreviousValues( i1Class, lDBID, eStatus, pData, pProp );

         int iPropType = pProp->getType()->getPropType();
         if (iPropType == BEMP_Sym)  // setting symbol value
         {
            long iSymVal = -999;   // SAC 3/16/07 - make consistent w/ "symbol not found" value changed back on 3/14/02.  was previously: -1;
            if (iDataType == BEMP_Int || iDataType == BEMP_Sym)
            {
               bDataModified = (pProp->getInt() != *((long*) pData));
               iSymVal = *((long*) pData);
               pProp->setInt( *((long*) pData) );
            }
            else if (iDataType == BEMP_Str || iDataType == BEMP_QStr)
            {  // must convert string symbol to integer value, then set data
					// // SAC 6/27/06 - added code to handle defaulting of symbols defined via CSV file tables
               // int iSymTableIdx = BEMPX_GetIndexOfSymbolTable( lDBID, iBEMProcIdx );
               // if (iSymTableIdx >= 0)
               // {
               //    iSymVal = BEMPX_GetSymbolTableValue( lDBID, (const char*) pData, iSymTableIdx, iOccur, iBEMProcIdx );
               //    if (iSymVal != -999)
               //    {
               //       bDataModified = (pProp->getInt() != iSymVal);
               //       pProp->setInt( iSymVal );
               //    }
               // }
               if (iSymVal == -999)  // SAC 3/16/07 - switched from 'else' to 'if (iSymVal...' to catch case where symbols defined BOTH as SymbolTable
               {                     //               AND in SymbolList data, which occurs in some cases to facilitate backward compatibility
                  BEMSymbolList* pSymList = GetSymbolList( lDBID );                 assert( pSymList != NULL );  // SAC 6/27/06
                  if (pSymList != NULL)
                  {
	// note: BEMP_QStr not fully integrated here. Strings using special characters will not function properly until further mods
                     iSymVal = pSymList->GetSymbolValue( lDBID, iOccur, eObjType, (iDataType == BEMP_Str ? (const char*) pData : ((QString*) pData)->toLocal8Bit().constData()), FALSE, iBEMProcIdx );
                     if (iSymVal != -999)  // SAC 3/14/02 - Switched "symbol not found" value from -1 to -999
                     {
                        bDataModified = (pProp->getInt() != iSymVal);
                        pProp->setInt( iSymVal );
                     }
							else
							{	iRetVal = -10;
								if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
								{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unable to find enumeration '%s' (DBID=%ld, Occur=%d)",
																(iDataType == BEMP_Str ? (const char*) pData : ((QString*) pData)->toLocal8Bit().constData()), lDBID, iOccur ) == -1)
										AppendEllipsis( pszErrMsg, iErrMsgLen );
							}	}
                  }
               }
            }
            else
				{	iRetVal = -10;
					if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
					{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Invalid data type - enumeration can be set with integer or string data only (DBID=%ld, DataType=%d)", lDBID, iDataType ) == -1)
							AppendEllipsis( pszErrMsg, iErrMsgLen );
				}	}

				//// SAC 11/27/99 - added call to initiate the reset of certain other symbol lists to file lists
            //if (bDataModified && iSymVal >= 0)
            //   ResetSymbolFileListIfNecessary( (DWORD) lDBID, (DWORD) iSymVal, iOccur, eObjType, iBEMProcIdx );
         }
         else if (iPropType == BEMP_Obj)  // setting object assignment
         {
            BEMObject* pPrevObj = pProp->getObj();
            BEMObject* pNewObj = NULL;
            if (iDataType == BEMP_Obj)
               pNewObj = (BEMObject*) pData;
            else if (iDataType == BEMP_Str || iDataType == BEMP_QStr)
            {  // must convert string object name to object pointer, then set data
					QString sObjName = (iDataType == BEMP_Str ? (const char*) pData : *((QString*) pData));
               if (!sObjName.isEmpty())  // ((const char*) pData)[0] != '\0')
               {
                  BEMObject* pObj = NULL;
						for (int iObjCls=0; (pObj==NULL && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
                  {	if (pProp->getType()->getObj1ClassIdx(iObjCls) > 0)
								pObj = BEMPX_GetObjectByNameQ( pProp->getType()->getObj1ClassIdx(iObjCls), iError, sObjName /*(const char*) pData*/, eObjFrom, iBEMProcIdx );
						}

                  if (pObj)
                     pNewObj = pObj;
                  else
						{	iRetVal = -10;
							if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
							{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unable to find object '%s' (DBID=%ld, Occur=%d)", sObjName /*(const char*) pData*/, lDBID, iOccur ) == -1)
									AppendEllipsis( pszErrMsg, iErrMsgLen );
						}	}
               }
            }
            else
				{	iRetVal = -10;
					if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
					{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Invalid data type - object assignment can be set with object pointer or string data only (DBID=%ld, DataType=%d)", lDBID, iDataType ) == -1)
							AppendEllipsis( pszErrMsg, iErrMsgLen );
				}	}

            if (iRetVal >= 0)
            {
               BOOL bMustCopyAssignedObject = FALSE;
               if (pNewObj && pNewObj->getClass() && pNewObj->getClass()->getUniqueAssignment())
                  // Determine of this object is already assigned elsewhere
						// SAC 5/27/99 - fixed bug where library components were not getting copied since they were not directly referenced by current user components
                  bMustCopyAssignedObject = ( pNewObj->getObjectType() == BEMO_RuleLib || pNewObj->getObjectType() == BEMO_UserLib ||
                                              CountObjectAssignments( pNewObj, FALSE, TRUE, TRUE, FALSE, FALSE, iBEMProcIdx, false ) > 0 );

					// SAC 1/28/99 - added to imp feature to create new user objects whenever a library object is being assigned to a user object
               BOOL bAssigningLibObjToUserObj = FALSE;
               if (pNewObj && !bMustCopyAssignedObject)
                  bAssigningLibObjToUserObj = ((eObjFrom == BEMO_RuleLib || eObjFrom == BEMO_UserLib) && eObjType == BEMO_User);

               // SET property's object pointer
               bDataModified = (pProp->getObj() != pNewObj);
               pProp->setObj( pNewObj );

               // Copy the assigned object and reset assignment if necessary
               if (bMustCopyAssignedObject || bAssigningLibObjToUserObj)
                  pProp->CopyAssignedObject( bAssigningLibObjToUserObj, iBEMProcIdx, iImportUniqueRuleLibObjOption,   // SAC 3/10/13	// SAC 4/25/14
															pszImportRuleLibParentName );  // SAC 3/17/13 - name of parent of rule lib object to import

               // Set/unset user referenced flags
               if (eObjType == BEMO_User)
               {
                  // Set new referenced lib object's m_userReferenced flag
                  if (pProp->getObj() != NULL)
                     SetUserReferencedFlag( pProp->getObj(), TRUE, iBEMProcIdx );

                  // Unset previous referenced lib object's m_userReferenced flag
                  if (pPrevObj != NULL)
                     SetUserReferencedFlag( pPrevObj, FALSE, iBEMProcIdx );
               }
            }
         }
         else if (iPropType == iDataType ||  // setting string, integer or double
         			(iPropType == BEMP_Str && iDataType == BEMP_QStr))
         {
            if (iPropType == BEMP_Int)
            {
               bDataModified = (pProp->getInt() != *((long*) pData));
               pProp->setInt( *((long*) pData) );
            }
            else if (iPropType == BEMP_Flt)
            {
               bDataModified = (pProp->getDouble() != *((double*) pData));
               pProp->setDouble( *((double*) pData) );
            }
            else if (iPropType == BEMP_Str)
         //   {	QString sData = (iDataType == BEMP_Str ? (const char*) pData : *((QString*) pData));
            {	QString sData = (iDataType == BEMP_Str ? QString::fromLatin1((const char*) pData) : *((QString*) pData));	// SAC 9/29/16 - modified to preserve special characters like '°' & '²'
               bDataModified = (pProp->getString() == sData);
               pProp->setString( sData );
            }
            else
				{	iRetVal = -10;
					if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
					{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unrecognized data type %d (DBID=%ld, Occur=%d)", iPropType, lDBID, iOccur ) == -1)
							AppendEllipsis( pszErrMsg, iErrMsgLen );
				}	}
         }
         else
			{	iRetVal = -10;
				if (pszErrMsg && iErrMsgLen > 4)  // SAC 4/10/13 - error message return
				{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, "Unable to reconcile input data type with property being set (DBID=%ld, Occur=%d, DataType=%d)", lDBID, iOccur, iDataType ) == -1)
						AppendEllipsis( pszErrMsg, iErrMsgLen );
			}	}

         if (iRetVal >= 0)
         {
            pProp->setDataStatus( eStatus );
            pProp->setSpecialValue( 0 );
         }
      }
   }

   if (iRetVal >= 0)
      PostDataModReset( pProp, lDBID, eStatus, i1Class, iOccur, eObjType, bDataModified, bPerformResets, iBEMProcIdx );

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_SetBEMSpecialValue()
//
// Purpose ------------------------------------------------------------------
//   Set special flag in property to inform simulation module to use "NONE" or
//   the simulation default when constructing the simulation input.
//   
// Arguments ----------------------------------------------------------------
//   long              lDBID       : 6 digit database ID CCPPAA (comp/property/array)
//   int               iSpecialVal : special simulation flag value
//   int               iOccur      : (default = -1) occurrence index of object beign edited
//   BEM_PropertyStatus eStatus     : (default = BEMS_UserDefined) status flag indicating origin of this value
//   BEM_ObjType        eObjType    : (default = BEMO_User) type of object being edited
//   
// Return Value -------------------------------------------------------------
//   integer value:  >= 0  : OK
//                   <  0  : error value returned from BEMPX_GetProperty()
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_SetBEMSpecialValue( long lDBID, int iSpecialVal, int iOccur,
                             BEM_PropertyStatus eStatus, BEM_ObjType eObjType, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = 0;
//   int iError;
   BEMProperty* pProp = NULL;
   BOOL bDataModified = FALSE;
   if (iSpecialVal > 0)
   {
      pProp = BEMPX_GetProperty( lDBID, iRetVal, iOccur, eObjType );
      if ((iRetVal >= 0) && (pProp != NULL) && (pProp->getSpecialValue() == 0))
      {
         int iPropType = pProp->getType()->getPropType();
         if ( (iPropType == BEMP_Sym) || (iPropType == BEMP_Int) )
            pProp->setInt( 0 );
         else if (iPropType == BEMP_Obj)
         {
            BEMObject* pPrevObj = pProp->getObj();
            pProp->setObj( NULL );

            // Set/unset user referenced flags
            if (eObjType == BEMO_User)
            {
               // Unset previous referenced lib object's m_bUserReferenced flag
               if (pPrevObj != NULL)
                  SetUserReferencedFlag( pPrevObj, FALSE, 0 );
            }
         }
         else if (iPropType == BEMP_Flt)
            pProp->setDouble( 0 );
         else if (iPropType == BEMP_Str)
            pProp->clearString();
      }

		if (pProp)  // SAC 7/12/12 - prevent NULL pointer use
      {	pProp->setDataStatus( eStatus );
      	bDataModified = (pProp->getSpecialValue() != iSpecialVal);
      	pProp->setSpecialValue( iSpecialVal );
		}
   }

   if (iRetVal >= 0)
   {
      PostDataModReset( pProp, lDBID, eStatus, BEMPX_GetClassID( lDBID ), iOccur, eObjType, bDataModified, TRUE, iBEMProcIdx );
//      // reinitialize all data in this property's ResetData list if this modification is a user input
//      if (pProp && eStatus == BEMS_UserDefined)
//         pProp->ReinitResetData( lDBID );
//
//      // re-default object w/ UserDefined default flag FALSE so that only hard-coded defaulting will occur
//      int i1Class = BEMPX_GetClassID( lDBID );
//      BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, iOccur, eObjType );
//      if (pObj != NULL)
//         pObj->DefaultObject( iOccur, FALSE, lDBID, eStatus, bDataModified );
   }

   return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

// SAC 12/19/01 - Added to facilitate more intelligent rule parsing by allowing Parent*() functions to be parsed at compile time
int BEMPX_GetParentComponentType( int i1Class, int iNumGenerations, int iBEMProcIdx /*=-1*/ )
{
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );					assert( pBEMProc );
   while (pBEMProc && i1Class > 0 && i1Class <= pBEMProc->getNumClasses() && --iNumGenerations >= 0)
   {
      BOOL bSingleParentClass = TRUE;
      for (int i=0; (bSingleParentClass && i < BEM_MAX_PARENT_TYPES); i++)
         bSingleParentClass = ( (i == 0 && pBEMProc->getClass(i1Class-1)->getParentType(i) >= 0) ||
                                (i  > 0 && pBEMProc->getClass(i1Class-1)->getParentType(i) <  0) );

      i1Class = (bSingleParentClass ? pBEMProc->getClass(i1Class-1)->getParentType(0)+1 : 0);
   }

   return i1Class;
}

static inline int IndexInArray( std::vector<int>& iArray, int iVal )
{	int i=0; 
	for (; i < (int) iArray.size(); i++)
		if (iArray[i] == iVal)
			return i;
	return -1;
}

// SAC 8/27/12 - added secondary check to see if first property name listed in argument exists for only a SINGLE possible Parent* object type
int BEMPX_GetParentComponentTypeForProperty( int i1Class, const char* pszPropName, int iNumGenerations, int iBEMProcIdx /*=-1*/ )
{	int iRetVal = -1;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );					assert( pBEMProc );
	if (pBEMProc)
	{
		std::vector<int> iaCompTypes[2];
		iaCompTypes[0].push_back( i1Class );
		int iCT, iAddTo=0, iReadFrom=1;
   	while (iaCompTypes[iAddTo].size() > 0 && --iNumGenerations >= 0)
   	{	iAddTo = iReadFrom;
			iReadFrom = (iAddTo==0 ? 1 : 0);
			iaCompTypes[iAddTo].clear();
			for (iCT=0; iCT < (int) iaCompTypes[iReadFrom].size(); iCT++)
   	   	for (int iPT=0; iPT < BEM_MAX_PARENT_TYPES; iPT++)
					if (iaCompTypes[iReadFrom].at(iCT) > 0 && pBEMProc->getClass(iaCompTypes[iReadFrom].at(iCT)-1) && 
						 pBEMProc->getClass(iaCompTypes[iReadFrom].at(iCT)-1)->getParentType(iPT) >= 0 &&
						 IndexInArray( iaCompTypes[iAddTo], pBEMProc->getClass(iaCompTypes[iReadFrom].at(iCT)-1)->getParentType(iPT)+1 ) < 0)
						iaCompTypes[iAddTo].push_back( pBEMProc->getClass(iaCompTypes[iReadFrom].at(iCT)-1)->getParentType(iPT)+1 );
   	}

		assert( iaCompTypes[iAddTo].size() > 0 );		// this would imply an errant situation where there are no parents types as far back as iNumGenerations was looking
		if (iaCompTypes[iAddTo].size() > 0)
		{	for (iCT=0; iCT < (int) iaCompTypes[iAddTo].size(); iCT++)
			{	long lDBID = BEMPX_GetDatabaseID( pszPropName, iaCompTypes[iAddTo].at(iCT) );
				if (lDBID > BEM_COMP_MULT)
				{	if (iRetVal < 0)
						iRetVal = BEMPX_GetClassID( lDBID );  // get Parent object type
					else
					{	iRetVal = -1;
						break;			// more than one Parent object type includes the specified Property
					}
				}
			}
		}
	}
   return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

static BEMObject* CheckForReplacementParent( int iChildClass, int iCurParObjClass, int iRepObjIdx, int iBEMProcIdx )
{
   int iError;
   BEMObject* pObj = BEMPX_GetObjectByClass( iCurParObjClass, iError, iRepObjIdx, BEMO_User, iBEMProcIdx );
   if (pObj && BEMPX_CanCreateAnotherChildObject( iChildClass, pObj, 1, iBEMProcIdx ))
      return pObj;
   return NULL;
}

void ResetCurrentParentPointers( BEMObject* pCurParObj, int i1BEMClass, int iBEMProcIdx )
{
   int iCurParObjIdx = BEMPX_GetObjectIndex( pCurParObj->getClass(), pCurParObj, iBEMProcIdx );
   int iCurParObjClass = pCurParObj->getClass()->get1BEMClassIdx();
   int iNumParUserObjs = BEMPX_GetNumObjects( iCurParObjClass, BEMO_User, iBEMProcIdx );
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   int iStart = (i1BEMClass > 0) ? i1BEMClass-1 : 0;
   int iEnd   = (i1BEMClass > 0) ? i1BEMClass-1 : pBEMProc->getNumClasses()-1;
   for (int i0TempClass = iStart; i0TempClass <= iEnd; i0TempClass++)
   {
      if (pBEMProc->getClass( i0TempClass )->getCurrentParent() == pCurParObj)
      {  // first try resetting it to another object of the same type
         BEMObject* pReplacementParObj = NULL;
         int iRepObjIdx = iCurParObjIdx;
         // first try subsequent objects
         while (++iRepObjIdx < iNumParUserObjs && pReplacementParObj == NULL)
            pReplacementParObj = CheckForReplacementParent( i0TempClass+1, iCurParObjClass, iRepObjIdx, iBEMProcIdx );

         iRepObjIdx = iCurParObjIdx;
         // then try previous objects (if we haven't already got a replacement parent)
         while (--iRepObjIdx >= 0 && pReplacementParObj == NULL)
            pReplacementParObj = CheckForReplacementParent( i0TempClass+1, iCurParObjClass, iRepObjIdx, iBEMProcIdx );

         // if no replacement is found, resort to trying to set it to an object of another class
         // which can be a parent of the child class
         if (pReplacementParObj == NULL)
         {
            for (int i=0; (pReplacementParObj == NULL && i<BEM_MAX_PARENT_TYPES); i++)
               if (pBEMProc->getClass( i0TempClass )->getParentType(i) != (pCurParObj->getClass()->get1BEMClassIdx()-1) &&
                   pBEMProc->getClass( i0TempClass )->getParentType(i) >= 0)
               {
                  iNumParUserObjs = BEMPX_GetNumObjects( pBEMProc->getClass( i0TempClass )->getParentType(i)+1, BEMO_User, iBEMProcIdx );
                  for (int iObj=0; (pReplacementParObj == NULL && iObj<iNumParUserObjs); iObj++)
                     pReplacementParObj = CheckForReplacementParent( i0TempClass+1,
                                                    pBEMProc->getClass( i0TempClass )->getParentType(i)+1, iObj, iBEMProcIdx );
               }
         }

         // reset the parent regardles of whether we actually FOUND a new valid parent object
         pBEMProc->getClass( i0TempClass )->setCurrentParent( pReplacementParObj );
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetCompDataType()
//
// Purpose ------------------------------------------------------------------
//   Get the value of the compliance data type member of the compliance data
//   for a selected property type.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   The compliance data type for the selected property type (refer to the 
//   definition of the enum BEM_CompDataType),
//   OR -1 if an error occurred retrieving the BEMDataType instance.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetCompDataType( long lDBID )
{
   int iRetVal = -1;
   int iPropID = BEMPX_GetPropertyID( lDBID );
   if (iPropID > 0)	// could be 0 => 'Action'
	{	BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lDBID ), iPropID );			assert( pPropType );
		if (pPropType)
		{	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( BEMPX_GetArrayID( lDBID )-1 );
			if (pPTD)
				iRetVal = pPTD->getCompDataType();
	}	}
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetCompIsEditable()
//
// Purpose ------------------------------------------------------------------
//   Get the value of the data is editable flag member of the compliance data
//   for a selected property type.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   The is editable flag for the selected property type's compliance data,
//   OR TRUE if an error occurred retrieving the BEMDataType instance.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_GetCompIsEditable( long lDBID )
{
   bool bRetVal = TRUE;
   int iPropID = (lDBID < BEM_COMP_MULT ? 0 : BEMPX_GetPropertyID( lDBID ));
   if (iPropID > 0)	// could be 0 => 'Action'
	{	BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lDBID ), iPropID );			assert( pPropType );
		if (pPropType)
		{	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( BEMPX_GetArrayID( lDBID )-1 );		assert( pPTD );
			if (pPTD)
				bRetVal = pPTD->isEditable();
	}	}
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetCompDisplay()
//
// Purpose ------------------------------------------------------------------
//   Get the value of the displayflag member of the compliance data
//   for a selected property type and interface display mode.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID     : 6 digit database ID CCPPAA (comp/property/array)
//   int  iDispMode : User interface display mode (0-Input, 1-Proposed, 2-Budget)
//   
// Return Value -------------------------------------------------------------
//   The display flag for the selected property type's compliance data and
//   user interface mode,
//   OR TRUE if an error occurred retrieving the BEMDataType instance or if the
//   iDispMode argument is invalid.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPX_GetCompDisplay( long lDBID, int iDispMode )
{
   bool bRetVal = TRUE;
   int iPropID = (lDBID < BEM_COMP_MULT ? 0 : BEMPX_GetPropertyID( lDBID ));
   if (iPropID > 0)	// could be 0 => 'Action'
	{	BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lDBID ), iPropID );			assert( pPropType );
		if (pPropType)
		{	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( BEMPX_GetArrayID( lDBID )-1 );		assert( pPTD );
			if (pPTD)
	      {	// set return value based on iDispMode argument
   	   	switch (iDispMode)
      		{  case 0 : bRetVal = pPTD->getDisplayInput();     break;
      		   case 1 : bRetVal = pPTD->getDisplayProposed();  break;
      	   	case 2 : bRetVal = pPTD->getDisplayBudget();    break;
	      }	}
   }	}
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetNumberOfPrimaryProperties()
//
// Purpose ------------------------------------------------------------------
//   Gets the number of Primary data variables for a specified class (component type).
//   
// Arguments ----------------------------------------------------------------
//   int i1BEMClass  : 1-based class (component type) index
//   
// Return Value -------------------------------------------------------------
//   the number of Primary properties for this class
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GetNumberOfPrimaryProperties( int i1BEMClass )
{
   int iRetVal = 0;
   // check for valid class ID
   if (i1BEMClass > 0 && i1BEMClass <= eBEMProc.getNumClasses())
   {  // loop over all property types for this class
      for (int i1PropIdx = 1; i1PropIdx <= eBEMProc.getClass( i1BEMClass-1 )->getNumProps(); i1PropIdx++)
      {  // get pointer to current property type
         BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1BEMClass, i1PropIdx );
         if (pPropType != NULL)
         {  // get number of array elements (if not string)
            for (int i0Array = 0; i0Array < pPropType->getNumValues(); i0Array++)
            {	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( i0Array );			assert( pPTD );
					if (pPTD && pPTD->isPrimary())
						iRetVal++;  // incrament iRetVal if this property is Primary
		}	}	}
   }
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetPrimaryPropertyDBID()
//
// Purpose ------------------------------------------------------------------
//   Gets the database ID of the specified Primary property and class.
//   
// Arguments ----------------------------------------------------------------
//   int i1BEMClass    : 1-based class (component type) index
//   int iPrimPropIdx : 0-based index of desired Primary DBID
//   
// Return Value -------------------------------------------------------------
//   The DBID of the 'iPrimPropIdx+1'th Primary property for the specfied class,
//   OR 0 if the primary property was not found.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
long BEMPX_GetPrimaryPropertyDBID( int i1BEMClass, int iPrimPropIdx )
{
   long lRetVal = 0;
   // check for valid class ID
   if (i1BEMClass > 0 && i1BEMClass <= eBEMProc.getNumClasses())
   {  // loop over all property types for this class
      for (int i1PropIdx = 1; (lRetVal == 0 && i1PropIdx <= eBEMProc.getClass( i1BEMClass-1 )->getNumProps()); i1PropIdx++)
      {  // get pointer to current property type
         BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1BEMClass, i1PropIdx );
         if (pPropType != NULL)
         {  // get number of array elements (if not string)
            for (int i0Array = 0; (lRetVal == 0 && i0Array < pPropType->getNumValues()); i0Array++)
            {	BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( i0Array );			assert( pPTD );
					if (pPTD && pPTD->isPrimary())
					{	// decrement iPrimPropIdx if it is > 0
                  if (iPrimPropIdx > 0)
                     iPrimPropIdx--;
                  else  // this is the one we are looking for, so get the lDBID
                     lRetVal = BEMPX_GetDBID( i1BEMClass, i1PropIdx, (i0Array+1) );
      }	}	}	}
   }
   return lRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool BEMPX_DeleteModels( bool bIncludingUserModel /*false*/ )
{
	bool bRetVal = true;
	bool bInitDeletingAllObjects = eDeletingAllObjects;
	eDeletingAllObjects = true;
	int i, bdClass, ib, iMdl;

	int iMinModel = (bIncludingUserModel ? 0 : 1);
   for (i=eNumBEMProcsLoaded-1; i >= iMinModel; i--)  // SAC 3/13/13 - added multi-model support  3/24/13 - reverse order to blast main model LAST
   {
      BEMProcObject* pBEMProc = getBEMProcPointer( i );
		if (pBEMProc)
			pBEMProc->clear();
// SAC 10/4/16 - below replaced w/ above, allowing BEMProcObject::clear() to handle clean-up
//   	for (int bdPropType = 0; bdPropType < pBEMProc->getNumPropertyTypes(); bdPropType++)
//   	{
//			pBEMProc->getPropertyType( bdPropType )->clearRangeChecks();
//			pBEMProc->getPropertyType( bdPropType )->clearPropTypeDetails();
//      //	// Delete all Compliance DataType objects
//   	//	while (pBEMProc->getPropertyType( bdPropType )->getNumPropTypeDetails())
//   	//	{
//      //      BEMDataType* pDT = (BEMDataType*)pBEMProc->getPropertyType( bdPropType )->m_olDataTypes.RemoveTail();
//   	//		delete pDT;
//   	//	}
//      //   // Delete all Range Check objects
//   	//	while (pBEMProc->getPropertyType( bdPropType )->m_olRanges.GetCount())
//   	//	{
//      //      BEMRangeCheck* pRC = (BEMRangeCheck*)pBEMProc->getPropertyType( bdPropType )->m_olRanges.RemoveTail();
//   	//		delete pRC;
//   	//	}
//      //   // Delete all Compliance Reset objects
//   	//	while (pBEMProc->getPropertyType( bdPropType )->m_olResetData.GetCount())
//   	//	{
//      //      BEMReset* pR = (BEMReset*)pBEMProc->getPropertyType( bdPropType )->m_olResetData.RemoveTail();
//   	//		delete pR;
//   	//	}
//      }
//
//   	for (int bdClass = pBEMProc->getNumClasses()-1; bdClass >= 0; bdClass--)
//   		pBEMProc->getClass( bdClass )->clear();
   }

	if (!bIncludingUserModel)
	{	// remove all pointers to model mapped objects for the remaining user model objects
      BEMProcObject* pBEMProc = getBEMProcPointer( 0 );			assert( pBEMProc );
		if (pBEMProc)
   	{	for (bdClass = pBEMProc->getNumClasses()-1; bdClass >= 0; bdClass--)
				for (i=0; i<3; i++)
					for (ib = pBEMProc->getClass( bdClass )->ObjectCount( (BEM_ObjType) i )-1; ib >= 0; ib--)
					{	BEMObject* pObj = pBEMProc->getClass( bdClass )->GetObject( (BEM_ObjType) i, ib );		assert( pObj );
						if (pObj)
						{	for (iMdl=0; iMdl < eNumBEMProcsLoaded; iMdl++)
								pObj->setModelMappedObject( iMdl, NULL );
					}	}
				//{	std::vector<BEMObject*>* pObArr = NULL;
				//	switch (i)
				//	{	case 0 :	pObArr = &pBEMProc->getClass( bdClass )->m_bdObjects;    break;
				//		case 1 :	pObArr = &pBEMProc->getClass( bdClass )->m_rlObjects;    break;
				//		case 2 :	pObArr = &pBEMProc->getClass( bdClass )->m_ulObjects;    break;
				//	}										assert( pObArr );
				//	if (pObArr)
				//	{	for (int ib=0; ib < pObArr->size(); ib++)
				//		{	BEMObject* pObj = (BEMObject*) pObArr->at(ib);				assert( pObj );
				//			if (pObj)
				//			{	for (iMdl=0; iMdl < eNumBEMProcsLoaded; iMdl++)
				//					pObj->setModelMappedObject( iMdl, NULL );
				//				//	pObj->m_paModelMappedObjects[iMdl] = NULL;
				//			}
				//		}
				//	}
				//}
		}
	}

	blastSecondaryBEMProcs();	// SAC 5/14/15 - added to delete old BEMProcObject objects

	eNumBEMProcsLoaded = iMinModel;
	eDeletingAllObjects = bInitDeletingAllObjects;
	return bRetVal;
}

static int CopyObjectsAcrossModels( long* plDBIDsToBypass, int iFromBEMProcIdx, int iToBEMProcIdx /*=-1*/ );

bool BEMPX_AddModel( int iBEMProcIdxToCopy /*=0*/, long* plDBIDsToBypass /*=NULL*/, bool bSetActiveBEMProcToNew /*=true*/ )		// SAC 3/13/13 - added multiple model support
{
  bool bRetVal = false;															assert( eNumBEMProcsLoaded < BEMPROC_MAXMODELS );
	if (eNumBEMProcsLoaded < BEMPROC_MAXMODELS)
	{
		BEMProcObject* pNewBEMProcObj = NULL;
      try
      {
			pNewBEMProcObj = new BEMProcObject();
			if (pNewBEMProcObj)
			{	epBEMProcs[eNumBEMProcsLoaded-1] = pNewBEMProcObj;
				assert( iBEMProcIdxToCopy < eNumBEMProcsLoaded );
				bRetVal = (iBEMProcIdxToCopy < eNumBEMProcsLoaded && pNewBEMProcObj->copy( getBEMProcPointer( iBEMProcIdxToCopy ), FALSE /*bCopyObjects*/ ));

				if (bRetVal)
				{	if (bSetActiveBEMProcToNew)
						eActiveBEMProcIdx = eNumBEMProcsLoaded;
					eNumBEMProcsLoaded++;

				// Copy over OBJECTS from the source model to the destination model, establishing linkages between the two
					if (CopyObjectsAcrossModels( plDBIDsToBypass, iBEMProcIdxToCopy, eNumBEMProcsLoaded-1 ) != 0)
					{	assert( false );
					}
			}	}
      }
      catch (std::bad_alloc& ba)
		{	QString sErrMsg = QString( "Error (bad_alloc caught) adding new model via BEMProc BEMPX_AddModel() - model to copy: %1 - %2" ).arg( QString::number(iBEMProcIdxToCopy), ba.what() );
	      BEMPX_WriteLogFile( sErrMsg );		assert( FALSE );
			//std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		}
      catch( ... )
      {	QString sErrMsg = QString( "Error encountered adding new model via BEMProc BEMPX_AddModel() - model to copy: %1." ).arg( QString::number(iBEMProcIdxToCopy) );
	      BEMPX_WriteLogFile( sErrMsg );		assert( FALSE );
      }
	}
	return bRetVal;
}

bool BEMPX_SetActiveModel( int i0ActiveBEMProcIdx )		// SAC 3/13/13 - added multiple model support
{
	bool bRetVal = (i0ActiveBEMProcIdx < eNumBEMProcsLoaded);				assert( bRetVal );
	if (bRetVal)
		eActiveBEMProcIdx = i0ActiveBEMProcIdx;
	return bRetVal;
}

int BEMPX_GetActiveModel()		// SAC 3/14/13
{	return eActiveBEMProcIdx;
}

int BEMPX_GetModelCount()			// SAC 3/15/13
{	return eNumBEMProcsLoaded;
}

int BEMPX_GetObjectIndexAcrossModels( int i1Class, int iOutModel, BEM_ObjType eObjType, int iInOccur, int iInModel /*=-1*/ )		// SAC 3/14/13
{	int iOutOccur = -1;
	if (iInModel < 0)
		iInModel = eActiveBEMProcIdx;

	if (iOutModel == iInModel)
		iOutOccur = iInOccur;
	else if (iOutModel > iInModel)
	{	assert( FALSE );		// object linkages only look back to previous models
	}
	else
	{  int iError;
		BEMObject* pInObj = BEMPX_GetObjectByClass( i1Class, iError, iInOccur, eObjType, iInModel );				assert( pInObj );
		if (pInObj)
		{	BEMObject* pOutObj = pInObj->getModelMappedObject(iOutModel);										
			if (pOutObj == NULL)		// SAC 9/24/15 - code to check through all valid cross-referenced objects to see if THEY reference an object in the target transform
			{	for (int i1=0; (i1<BEMPROC_MAXMODELS && pOutObj == NULL); i1++)
				{	if (pInObj->getModelMappedObject(i1) && pInObj->getModelMappedObject(i1)->getModelMappedObject(iOutModel))
						pOutObj = pInObj->getModelMappedObject(i1)->getModelMappedObject(iOutModel);
			}	}
																																		assert( pOutObj && pOutObj->getClass() );
			if (pOutObj && pOutObj->getClass())
				iOutOccur = BEMPX_GetObjectIndex( pOutObj->getClass(), pOutObj, iOutModel );
		}
	}
	return iOutOccur;
}


int BEMPX_CopyClassObjectsAcrossModels( int i1Class, int iFromBEMProcIdx, int iToBEMProcIdx )
{
	assert( iFromBEMProcIdx >= 0 && iFromBEMProcIdx < eNumBEMProcsLoaded );
	assert(   iToBEMProcIdx >= 0 &&   iToBEMProcIdx < eNumBEMProcsLoaded );
   BEMProcObject* pFromBEMProc = getBEMProcPointer( iFromBEMProcIdx );				assert( pFromBEMProc );
   BEMProcObject*   pToBEMProc = getBEMProcPointer(   iToBEMProcIdx );				assert(   pToBEMProc );
   // SAC 4/30/15 - fixing bug where parent mapped object arrays are insufficient when BEMProc initialization (via copying BEMProcs) is not incremental
	int iIdxOfToBEMProcSrc = (pToBEMProc->getSrcBEMProcObj() == NULL ? 0 : getBEMProcIndex( pToBEMProc->getSrcBEMProcObj() ));		assert( iIdxOfToBEMProcSrc <= iFromBEMProcIdx );

   int iRetVal = (pFromBEMProc==NULL ? 1 : (pToBEMProc==NULL ? 2 : (i1Class > pFromBEMProc->getNumClasses() ? 8 : 0)));
   if (iRetVal == 0)
	{	int iOT, ib;
		for (iOT=0; (iRetVal==0 && iOT < 3); iOT++)
      	if (TRUE)
      	{
				for (ib=0; (iRetVal==0 && ib < pFromBEMProc->getClass( i1Class-1 )->ObjectCount( (BEM_ObjType) iOT )); ib++)
				{	BEMObject* pObj = pFromBEMProc->getClass( i1Class-1 )->GetObject( (BEM_ObjType) iOT, ib );					assert( pObj );
//      	if (TRUE)
//      	{
//            CObArray* pObArr = NULL;
//				switch (iOT)
//				{	case  1 :  pObArr = &pFromBEMProc->getClass( i1Class-1 )->m_rlObjects;		break;	// rule library objects
//					case  2 :  pObArr = &pFromBEMProc->getClass( i1Class-1 )->m_ulObjects;		break;	// user library objects
//					default :  pObArr = &pFromBEMProc->getClass( i1Class-1 )->m_bdObjects;		break;	// user objects
//				}
//				for (int ib=0; (iRetVal==0 && ib < pObArr->GetSize()); ib++)
//				{	BEMObject* pObj = (BEMObject*) pObArr->GetAt(ib);								assert( pObj );
               if (pObj == NULL)
                  iRetVal = 3;
               else
               {	try
						{  // allocate new object
							BEMObject* pNewObject = new BEMObject;
							if (pNewObject == NULL)
   					      iRetVal = 5;
							else
							{
								if (!pNewObject->CopyObjectBetweenModels( pObj, iToBEMProcIdx, iFromBEMProcIdx ))
						         iRetVal = 6;
								else
   					   		// add this object to the appropriate list of objects
						   		pToBEMProc->getClass( i1Class-1 )->AddObject( pNewObject, (BEM_ObjType) iOT );
									//switch (iOT)
									//{	case  1 :  pToBEMProc->getClass( i1Class-1 )->m_rlObjects.Add(pNewObject);		break;	// rule library objects
									//	case  2 :  pToBEMProc->getClass( i1Class-1 )->m_ulObjects.Add(pNewObject);		break;	// user library objects
									//	default :  pToBEMProc->getClass( i1Class-1 )->m_bdObjects.Add(pNewObject);		break;	// user objects
									//}
							}
						}
						catch (...)
						{	// fall through
   					   iRetVal = 4;
						}
               }
            }	// end of:  while loop over objects in list
         }	// end of:  for loops over object type lists (User / RuleLib / UserLib)

	// SECOND loop over classes & object types to resolve all parent (child) & object references
	// all object pointers SHOULD be defineable based solely on the new m_paModelMappedObjects[*] pointers added to the BEMObject class
		for (iOT=0; (iRetVal==0 && iOT < 3); iOT++)
		{	for (ib=0; (iRetVal==0 && ib < pToBEMProc->getClass( i1Class-1 )->ObjectCount( (BEM_ObjType) iOT )); ib++)
			{	BEMObject* pToObj = pToBEMProc->getClass( i1Class-1 )->GetObject( (BEM_ObjType) iOT, ib );					assert( pToObj );
//		{  CObArray* pObArr = NULL;
//		 	switch (iOT)
//		 	{	case  1 :  pObArr = &pToBEMProc->getClass( i1Class-1 )->m_rlObjects;		break;	// rule library objects
//		 		case  2 :  pObArr = &pToBEMProc->getClass( i1Class-1 )->m_ulObjects;		break;	// user library objects
//		 		default :  pObArr = &pToBEMProc->getClass( i1Class-1 )->m_bdObjects;		break;	// user objects
//		 	}
//			for (int ib=0; (iRetVal==0 && ib < pObArr->GetSize()); ib++)
//			{	BEMObject* pToObj = (BEMObject*) pObArr->GetAt(ib);								assert( pToObj );
				if (	pToObj && pToObj->getModelMappedObject(iFromBEMProcIdx) &&
						pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent() &&
						pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iToBEMProcIdx) )
				{
               pToObj->setParent( pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iToBEMProcIdx) );
               pToObj->getParent()->addChild( pToObj );
				 	pToObj->clearArchiveParentName();   // just clean-up - not really needed (??)
				}
				else if (iIdxOfToBEMProcSrc < iFromBEMProcIdx &&
							pToObj && pToObj->getModelMappedObject(iFromBEMProcIdx) &&
							pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent() &&
							pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iIdxOfToBEMProcSrc) &&
							pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iIdxOfToBEMProcSrc)->getModelMappedObject(iToBEMProcIdx) )
				{	pToObj->setParent( pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iIdxOfToBEMProcSrc)->getModelMappedObject(iToBEMProcIdx) );
					pToObj->getParent()->addChild( pToObj );
					pToObj->clearArchiveParentName();   // just clean-up - not really needed (??)
				}
				else
				{	assert( pToObj->getArchiveParentName().isEmpty() || pToObj->getClass()->getParentType(0)==0 );		// or could this still be a valid scenario when objects are not copied due to the class exclusion list...
				}

            // now deal w/ restoring object assignments
				BEMObject* pFromObj = pToObj->getModelMappedObject(iFromBEMProcIdx);
            for (int iProp=0; (iRetVal==0 && iProp<pToObj->getPropertiesSize()); iProp++)
            {
               BEMProperty* pToProp = pToObj->getProperty(iProp);						assert( pToProp );
               if (pToProp == NULL)
                  iRetVal = 7;
               else if (pToProp->getType()  &&  pToProp->getType()->getPropType() == BEMP_Obj  &&  !pToProp->getString().isEmpty())
               {	if (pFromObj == NULL || pFromObj->getPropertiesSize() <= iProp)
						{	assert( FALSE );
						}
						else
						{	BEMProperty* pFromProp = pFromObj->getProperty(iProp);
							if (	 pFromProp->getType()  &&  pFromProp->getType()->getPropType() == BEMP_Obj && pFromProp->getObj() &&
									!pFromProp->getObj()->getName().compare( pToProp->getString() ) &&
									 pFromProp->getObj()->getModelMappedObject(iToBEMProcIdx) )
								pToProp->setObj( pFromProp->getObj()->getModelMappedObject(iToBEMProcIdx) );
							else
							{	//assert( FALSE );		// or could this still be a valid scenario when objects are not copied due to the class exclusion list...
							}
						}
					}
				}
			}	// end of:  while (loop over objects)
		}	// end of:  loop over classes & object types

	}
   return iRetVal;
}


static inline BOOL ClassIdxInList( int iCheck, long* plIntList )
{
   int i=-1;
   while (plIntList[++i] > 0)
   {
      if (iCheck == (int) plIntList[i])
         return TRUE;
   }
   return FALSE;
}

static inline long GetDBIDfromBypassDBIDList( int iCheck, long* plIntList )		// SAC 3/27/14
{
   int i=-1;
   while (plIntList[++i] > 0)
   {
      if (plIntList[i] > BEM_COMP_MULT && iCheck == (int) BEMPX_GetClassID( plIntList[i] ))
         return plIntList[i];
   }
   return 0;
}

static inline BOOL ObjectPtrInArray( BEMObject* pObjToCheck, QVector<BEMObject*>& paObjs )
{
	for (int i=0; i<paObjs.size(); i++)
	{	if (pObjToCheck == paObjs[i])
         return TRUE;
	}
   return FALSE;
}

int CopyObjectsAcrossModels( long* plDBIDsToBypass, int iFromBEMProcIdx, int iToBEMProcIdx )
{
	assert( iFromBEMProcIdx >= 0 && iFromBEMProcIdx < eNumBEMProcsLoaded );
	assert(   iToBEMProcIdx >= 0 &&   iToBEMProcIdx < eNumBEMProcsLoaded );
   BEMProcObject* pFromBEMProc = getBEMProcPointer( iFromBEMProcIdx );				assert( pFromBEMProc );
   BEMProcObject*   pToBEMProc = getBEMProcPointer(   iToBEMProcIdx );				assert(   pToBEMProc );
	QVector<BEMObject*> povObjectsNotCopied;
   int iRetVal = (pFromBEMProc==NULL ? 1 : (pToBEMProc==NULL ? 2 : 0));
   if (iRetVal == 0)
   {	int iCls=0, iOT=0;
      for (; (iRetVal==0 && iCls<pFromBEMProc->getNumClasses()); iCls++)
			for (iOT=0; (iRetVal==0 && iOT < 3); iOT++)
         	if (iOT > 0 || plDBIDsToBypass == NULL || !ClassIdxInList( iCls+1, plDBIDsToBypass ))  // bypass copying of USER objects in list of classes to bypass
         	{
					long lExcludeDBID = (plDBIDsToBypass==NULL ? 0 : GetDBIDfromBypassDBIDList( iCls+1, plDBIDsToBypass ));		// SAC 3/27/14
					for (int ib=0; (iRetVal==0 && ib < pFromBEMProc->getClass( iCls )->ObjectCount( (BEM_ObjType) iOT )); ib++)
					{	BEMObject* pObj = pFromBEMProc->getClass( iCls )->GetObject( (BEM_ObjType) iOT, ib );					assert( pObj );
//               CObArray* pObArr = NULL;
//					switch (iOT)
//					{	case  1 :  pObArr = &pFromBEMProc->getClass( iCls )->m_rlObjects;		break;	// rule library objects
//						case  2 :  pObArr = &pFromBEMProc->getClass( iCls )->m_ulObjects;		break;	// user library objects
//						default :  pObArr = &pFromBEMProc->getClass( iCls )->m_bdObjects;		break;	// user objects
//					}
//					for (int ib=0; (iRetVal==0 && ib < pObArr->GetSize()); ib++)
//					{	BEMObject* pObj = (BEMObject*) pObArr->GetAt(ib);							assert( pObj );
                  if (pObj == NULL)
                     iRetVal = 3;
                  else
                  {	// scan parent hierarchy for presence of an ignored class BEFORE copying object
							BOOL bParentInBypassList = FALSE;
							BEMObject* pParObj = pObj->getParent();
							while (pParObj && !bParentInBypassList)
							{
								if (pParObj->getClass() && plDBIDsToBypass)
									bParentInBypassList = ClassIdxInList( pParObj->getClass()->get1BEMClassIdx(), plDBIDsToBypass );
								if (!bParentInBypassList && povObjectsNotCopied.size() > 0)
									bParentInBypassList = ObjectPtrInArray( pParObj, povObjectsNotCopied );
								pParObj = pParObj->getParent();
							}
					//		if (!bParentInBypassList && povObjectsNotCopied.GetSize() > 0)
					//			bParentInBypassList = ObjectPtrInArray( pObj, povObjectsNotCopied );

							if (!bParentInBypassList && lExcludeDBID > BEM_COMP_MULT)		// SAC 3/27/14 - added code to check specified Exclude property for whether or not to copy object over
							{	int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iFromBEMProcIdx );						assert( iObjIdx >= 0 );
								if (iObjIdx >= 0)
								{	double fData;
									if (BEMPX_GetFloat( lExcludeDBID, fData, 0, -1, iObjIdx, iOT, iFromBEMProcIdx ) && !WithinMargin( fData, 0.0, 0.01 ))
									{	bParentInBypassList = TRUE;
										povObjectsNotCopied.push_back( pObj );
								}	}
							}

							if (!bParentInBypassList)
							{	try
								{  // allocate new object
									BEMObject* pNewObject = new BEMObject;
									if (pNewObject == NULL)
   							      iRetVal = 5;
									else
									{
										if (!pNewObject->CopyObjectBetweenModels( pObj, iToBEMProcIdx, iFromBEMProcIdx ))
								         iRetVal = 6;
										else
   							   		// add this object to the appropriate list of objects
   							   		pToBEMProc->getClass( iCls )->AddObject( pNewObject, (BEM_ObjType) iOT );
											//switch (iOT)
											//{	case  1 :  pToBEMProc->getClass( iCls )->m_rlObjects.Add(pNewObject);		break;	// rule library objects
											//	case  2 :  pToBEMProc->getClass( iCls )->m_ulObjects.Add(pNewObject);		break;	// user library objects
											//	default :  pToBEMProc->getClass( iCls )->m_bdObjects.Add(pNewObject);		break;	// user objects
											//}
									}
								}
								catch (...)
								{	// fall through
		   					   iRetVal = 4;
								}
							}
                  }
               }	// end of:  while loop over objects in list
            }	// end of:  for loops over classes & object types

	// SECOND loop over classes & object types to resolve all parent (child) & object references
	// all object pointers SHOULD be defineable based solely on the new m_paModelMappedObjects[*] pointers added to the BEMObject class
      for (iCls=0; (iRetVal==0 && iCls<pToBEMProc->getNumClasses()); iCls++)
		{	for (iOT=0; (iRetVal==0 && iOT < 3); iOT++)
			{	for (int ib=0; (iRetVal==0 && ib < pToBEMProc->getClass( iCls )->ObjectCount( (BEM_ObjType) iOT )); ib++)
				{	BEMObject* pToObj = pToBEMProc->getClass( iCls )->GetObject( (BEM_ObjType) iOT, ib );					assert( pToObj );
//         {  CObArray* pObArr = NULL;
//			 	switch (iOT)
//			 	{	case  1 :  pObArr = &pToBEMProc->getClass( iCls )->m_rlObjects;		break;	// rule library objects
//			 		case  2 :  pObArr = &pToBEMProc->getClass( iCls )->m_ulObjects;		break;	// user library objects
//			 		default :  pObArr = &pToBEMProc->getClass( iCls )->m_bdObjects;		break;	// user objects
//			 	}
//				for (int ib=0; (iRetVal==0 && ib < pObArr->GetSize()); ib++)
//				{	BEMObject* pToObj = (BEMObject*) pObArr->GetAt(ib);						assert( pToObj );
					if (	pToObj && pToObj->getModelMappedObject(iFromBEMProcIdx) &&
							pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent() &&
							pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iToBEMProcIdx) )
					{
            	   pToObj->setParent( pToObj->getModelMappedObject(iFromBEMProcIdx)->getParent()->getModelMappedObject(iToBEMProcIdx) );
            	   pToObj->getParent()->addChild( pToObj );
					 	pToObj->clearArchiveParentName();   // just clean-up - not really needed (??)
					}
					else
					{	assert( pToObj->getArchiveParentName().isEmpty() );		// or could this still be a valid scenario when objects are not copied due to the class exclusion list...
					}

            	// now deal w/ restoring object assignments
					BEMObject* pFromObj = pToObj->getModelMappedObject(iFromBEMProcIdx);
            	for (int iProp=0; (iRetVal==0 && iProp<pToObj->getPropertiesSize()); iProp++)
            	{
            	   BEMProperty* pToProp = pToObj->getProperty(iProp);						assert( pToProp );
            	   if (pToProp == NULL)
            	      iRetVal = 7;
            	   else if (pToProp->getType()  &&  pToProp->getType()->getPropType() == BEMP_Obj  &&  !pToProp->getString().isEmpty())
            	   {	if (pFromObj == NULL || pFromObj->getPropertiesSize() <= iProp)
							{	assert( FALSE );
							}
							else
							{	BEMProperty* pFromProp = pFromObj->getProperty(iProp);
								if (	 pFromProp->getType()  &&  pFromProp->getType()->getPropType() == BEMP_Obj && pFromProp->getObj() &&
										!pFromProp->getObj()->getName().compare( pToProp->getString() ) &&
										 pFromProp->getObj()->getModelMappedObject(iToBEMProcIdx) )
									pToProp->setObj( pFromProp->getObj()->getModelMappedObject(iToBEMProcIdx) );
								else
								{	//assert( FALSE );		// or could this still be a valid scenario when objects are not copied due to the class exclusion list...
								}
							}
						}
					}
				}
			}	// end of:  loop over classes & object types

		// SAC 5/13/15 - mods to ensure that each class's m_pCurrentParent pointers point to objects in the destination BEMProcObject 
			if (pFromBEMProc->getClass( iCls )->getCurrentParent() && pFromBEMProc->getClass( iCls )->getCurrentParent()->getModelMappedObject(iToBEMProcIdx))
				pToBEMProc->getClass( iCls )->setCurrentParent( pFromBEMProc->getClass( iCls )->getCurrentParent()->getModelMappedObject(iToBEMProcIdx) );
		}
	}
   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static int LocStringInArray( QStringList& saStrs, QString& sStr ) 
{
   int iSize = (int) saStrs.size();
   for (int i=0; i<iSize; i++)
   {  if (saStrs[i].compare( sStr, Qt::CaseInsensitive ) == 0)
         return i;
   }
   return -1;
}

/////////////////////////////////////////////////////////////////////////////
//
// BEMP_ResolveAllReferences()
//
// Purpose ------------------------------------------------------------------
//   Function to resolve all object references following project or library
//   data read.  This function is necessary since object assignments can
//   preceed their definitions in both library and project files.
//   
// Arguments ----------------------------------------------------------------
//   BEM_ObjType eObjType    : (default = BEMO_User) the type of object to resolve references for
//   QFile*     pErrorFile  : (default = NULL) file to write error messages to
//   BOOL       bPostErrors : (default = TRUE) whether or not to post error messages
//                            to the pErrorFile (if not NULL) or MessageBox.
//   
// Return Value -------------------------------------------------------------
//   The number of references NOT resolved => 0 means all references resolved
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMP_ResolveAllReferences( BEM_ObjType eObjType, QFile* pErrorFile, BOOL bPostErrors, int iBEMProcIdx /*=-1*/,
                               BOOL bSupressAllMessageBoxes /*=FALSE*/ ) 
{
   int iRetVal = 0;
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

   // loop over all classes
	QStringList saErrantObjRefs;  // SAC 10/22/13 - added to track names of first 10 or so unresolved object references
	std::vector<int> iaErrantObjRefCounts;
	int iErrObjRefIdx, iNumErrantObjsSkipped=0;
#define  BEM_MAX_REF_ERRANT_OBJECTS_TO_REPORT  10
	int i1Class=1;
   for (; i1Class<=pBEMProc->getNumClasses(); i1Class++)
   {
      int iError;
      // get pointer to class and confirm that it is OK
      BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
      if (iError >= 0 && pClass)
      {
         // Cruise thru list of BEM objects for this class and of the specified type
         int nObjs = BEMPX_GetNumObjects( i1Class, eObjType, iBEMProcIdx );
         for ( int obj = 0; obj < nObjs; obj++ )
         {
            // get pointer to object and confirm that it is OK
            BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, obj, eObjType, iBEMProcIdx );
            if (iError >= 0 && pObj)
            {
               // loop over all properties describing this object
               for (int iProp=0; iProp<pObj->getPropertiesSize(); iProp++)
               {
                  BEMProperty* pProp = (BEMProperty*) pObj->getProperty(iProp);			assert( pProp && pProp->getType() != NULL );

                  // check for property type of the type which assigns an object with a
                  // non-zero length string and no object yet assigned => the string is the
                  // name of the object which needs to be assigned to this property.
                  if ( (pProp->getType()->getPropType() == BEMP_Obj) &&
                       (pProp->getString().length() > 0) && (pProp->getObj() == NULL) )
                  {
                     BEMObject* pRefObj = NULL;
							for (int iObjCls=0; (pRefObj==NULL && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
                     {	if (pProp->getType()->getObj1ClassIdx(iObjCls) > 0)
								{	// get object to be assigned to this property
                     		pRefObj = BEMPX_GetObjectByName( pProp->getType()->getObj1ClassIdx(iObjCls), iError, 
                     		                                  (const char*) pProp->getString().toLocal8Bit().constData(), eObjType, iBEMProcIdx );
                     		// if getting User object, also allow RuleLib or UserLib objects to be referenced
                     		if (pRefObj == NULL && eObjType == BEMO_User)
                     		   pRefObj = BEMPX_GetObjectByName( pProp->getType()->getObj1ClassIdx(iObjCls), iError, 
                     		                                  (const char*) pProp->getString().toLocal8Bit().constData(), BEMO_RuleLib, iBEMProcIdx );
                     		if (pRefObj == NULL && eObjType == BEMO_User)
                     		   pRefObj = BEMPX_GetObjectByName( pProp->getType()->getObj1ClassIdx(iObjCls), iError, 
                     		                                  (const char*) pProp->getString().toLocal8Bit().constData(), BEMO_UserLib, iBEMProcIdx );
								}
							}

                     if (pRefObj == NULL)
                     {  // object assignment not found
                        if (pProp->getString().compare( "- none -" ) == 0)  // OK if string indicates no assignment
                           pProp->setObj( NULL );
                        else
                        {
                           iRetVal++;  // incrament retval => number of missing assignments
                           if (bPostErrors)
                           {
                              QString errMsg = QString("Unresolved component reference: '%1'").arg( pProp->getString() );
                              if (pErrorFile != NULL)
                              {  // write message to error file
                                 errMsg += "\n\n";
                                 pErrorFile->write( errMsg.toLocal8Bit().constData(), errMsg.length() );
                              }
                              else
                              {
											iErrObjRefIdx = LocStringInArray( saErrantObjRefs, pProp->getString() );
											if (iErrObjRefIdx < 0)
											{	if (saErrantObjRefs.size() > BEM_MAX_REF_ERRANT_OBJECTS_TO_REPORT)
													iNumErrantObjsSkipped++;
												else
												{	saErrantObjRefs.push_back( pProp->getString() );
													iaErrantObjRefCounts.push_back( 1 );
											}	}
											else
												iaErrantObjRefCounts[iErrObjRefIdx] += 1;
                              }
                           }
                        }
                     }
                     else
                     {  // found the matching object
                        pProp->setObj( pRefObj );  // set property's object assignment
                        // Set user-referenced object's m_bUserReferenced flag (if appropriate)
                        if (eObjType == BEMO_User && pRefObj->getObjectType() != BEMO_User)
                           SetUserReferencedFlag( pRefObj, TRUE, iBEMProcIdx );
                     }
                  }
						// code to re-default symbol assignments in case some data that this item's symbollist 
						// depends on has been changed since the property was initially defaulted.
                  else if ( pProp->getType()->getPropType() == BEMP_Sym  &&
                            ( pProp->getDataStatus() == BEMS_Undefined  || 
                              pProp->getDataStatus() == BEMS_ProgDefault ) )
                     pProp->Default( BEMPX_GetDBID( i1Class, pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() ),
                                     obj, eObjType, FALSE, iBEMProcIdx );
               }
            }
            else
               assert( FALSE );
         }
      }
      else
         assert( FALSE );
   }

   // Report errors (if one or more objects were not found)
   if (iRetVal > 0)
   {
      QString sErr = QString::number(iRetVal);
      QString sMsg = "Error resolving ";
      if (eObjType == BEMO_User)
         sMsg += "project";
      else if (eObjType == BEMO_RuleLib)
         sMsg += "rule library";
      else // if (eObjType == BEMO_UserLib)
         sMsg += "user library";
      sMsg += " component references: ";
      sMsg += sErr;
      sMsg += " not found.";
      BEMPX_WriteLogFile( sMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03

		QString sMsg2;	
		for (int iEr=0; iEr < (int) saErrantObjRefs.size(); iEr++)
		{	if (iaErrantObjRefCounts[iEr] == 1)
				sMsg2 = QString( "      '%1' (once)" ).arg( saErrantObjRefs[iEr] );
			else
				sMsg2 = QString( "      '%1' (%2 times)" ).arg( saErrantObjRefs[iEr], QString::number(iaErrantObjRefCounts[iEr]) );
	      BEMPX_WriteLogFile( sMsg2, NULL, FALSE, bSupressAllMessageBoxes );
		}
		if (iNumErrantObjsSkipped > 0)
		{	sMsg2 = QString( "      (plus %1 other object reference(s))" ).arg( QString::number(iNumErrantObjsSkipped) );
	      BEMPX_WriteLogFile( sMsg2, NULL, FALSE, bSupressAllMessageBoxes );
		}
      if (!bSupressAllMessageBoxes)  // SAC 4/27/03
         BEMMessageBox( sMsg, "Building Database Error", 3 /*error*/ );
   }

	// code to ensure component name uniqueness - and if non-unique components found, ensure that neither is referenced via BEMP_Obj assignments
   if (iRetVal == 0)
   {  QStringList saDupCompNames, saDupCompNames_Refed;
      // loop over all classes
      for (i1Class=1; i1Class<=pBEMProc->getNumClasses(); i1Class++)
      {
         int iError;
         // get pointer to class and confirm that it is OK
         BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
         if (iError >= 0 && pClass)
         {
            // Cruise thru list of BEM objects for this class and of the specified type
            int nObjs = BEMPX_GetNumObjects( i1Class, eObjType, iBEMProcIdx );
            for ( int obj = 0; obj < nObjs; obj++ )
            {
               // get pointer to object and confirm that it is OK
               BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, obj, eObjType, iBEMProcIdx );
               if (iError >= 0 && pObj && !pObj->getName().isEmpty() && LocStringInArray( saDupCompNames_Refed, pObj->getName() ) < 0)
               {
                  BOOL bRenameObj = (LocStringInArray( saDupCompNames, pObj->getName() ) >= 0);
                  if (!bRenameObj)
                  {
                     BEMObject* pObj2 = BEMPX_GetComponentByNameQ( pObj->getName(), FALSE /*bCheckLibsOnly*/, 0 /*iBEMProcIdx*/, FALSE /*bSkipCheckingRuleLib*/, FALSE /*bNameIsPrefix*/ );
                     if (pObj2 != pObj)
                     {
                     // check for ANY references to a component of this name
                        int iNumRefs = 0;
                        for (int i1Class2=1; i1Class2<=pBEMProc->getNumClasses(); i1Class2++)
                           if (BEMPX_GetClass( i1Class2, iError, iBEMProcIdx ) != NULL && iError >= 0)
                           {
                              // Cruise thru list of BEM objects for this class and of the specified type
                              int nObjs2 = BEMPX_GetNumObjects( i1Class2, eObjType, iBEMProcIdx );
                              for ( int obj2 = 0; obj2 < nObjs2; obj2++ )
                              {
                                 // get pointer to object and confirm that it is OK
                                 BEMObject* pObj2 = BEMPX_GetObjectByClass( i1Class2, iError, obj2, eObjType, iBEMProcIdx );      assert( iError >= 0 && pObj2 );
                                 if (iError >= 0 && pObj2)
                                 {
                                    // loop over all properties describing this object
                                    for (int iProp2=0; iProp2<pObj2->getPropertiesSize(); iProp2++)
                                    {
                                       BEMProperty* pProp2 = (BEMProperty*) pObj2->getProperty(iProp2);                assert( pProp2 && pProp2->getType() );
                                       // check for properties assigned to an object by the name of this dup object
                                       if (pProp2 && pProp2->getType() && pProp2->getType()->getPropType() == BEMP_Obj && 
                                       	 pProp2->getObj() != NULL && pProp2->getObj()->getName().compare( pObj->getName() ) == 0)
                                       {  assert( FALSE );
                                          iNumRefs++;
                                       }
                                    }
                                 }
                              }
                           }

                        if (iNumRefs < 1)
                        {  bRenameObj = TRUE;
                           saDupCompNames.push_back( pObj->getName() );
                        }
                        else
                           saDupCompNames_Refed.push_back( pObj->getName() );
                     }  // end of if (object w/ same name exists)
                  }

                  if (bRenameObj)
                  {
                     QString sNewObjName = pObj->getName();
                     BEMPX_GetDefaultComponentName( i1Class, sNewObjName, iBEMProcIdx, 2 /*iFirstIndex=-1*/ );
                     pObj->setName( sNewObjName );
                  }
               }
            }
         }
      }

		if (saDupCompNames_Refed.size() > 0 && bPostErrors)  // SAC 10/29/12 - added reporting of multiple dup object name warning
      {	QString errMsg = "Error:  Multiple referenced objects found with the same name:  ";
			for (i1Class = 0; i1Class < (int) saDupCompNames_Refed.size(); i1Class++)
			{	errMsg += "| ";
				errMsg += saDupCompNames_Refed[i1Class];
			}
         if (pErrorFile != NULL)
         {  // write message to error file
            errMsg += "\n\n";
            pErrorFile->write( errMsg.toLocal8Bit().constData(), errMsg.length() );
         }
         else
            BEMPX_WriteLogFile( errMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03
      }
   }

   return iRetVal;
}                     


////////////////////////////////////////////////////////////////////////////////

// SAC 2/23/15 - routine borrowing second hal of above routine designed to check for (and either fix or report) duplicate object names in model
int BEMPX_CheckForDuplicateObjectNames( char* pszErrMsg, int iErrMsgLen, BOOL bWriteErrorsToLog, BOOL bSupressAllMessageBoxes /*=FALSE*/,
														BEM_ObjType eObjType /*=BEMO_User*/, int iBEMProcIdx /*=-1*/ )
{
   int iRetVal = 0;
	if (iBEMProcIdx < 0) 
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );
	int i1Class;

      QStringList saDupCompNames, saDupCompNames_Refed;
      // loop over all classes
      for (i1Class=1; i1Class<=pBEMProc->getNumClasses(); i1Class++)
      {
         int iError;
         // get pointer to class and confirm that it is OK
         BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
         if (iError >= 0 && pClass)
         {
            // Cruise thru list of BEM objects for this class and of the specified type
            int nObjs = BEMPX_GetNumObjects( i1Class, eObjType, iBEMProcIdx );
            for ( int obj = 0; obj < nObjs; obj++ )
            {
               // get pointer to object and confirm that it is OK
               BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iError, obj, eObjType, iBEMProcIdx );
               if (iError >= 0 && pObj && !pObj->getName().isEmpty() && LocStringInArray( saDupCompNames_Refed, pObj->getName() ) < 0)
               {
                  BOOL bRenameObj = (LocStringInArray( saDupCompNames, pObj->getName() ) >= 0);
                  if (!bRenameObj)
                  {
                     BEMObject* pObj2 = BEMPX_GetComponentByNameQ( pObj->getName(), FALSE /*bCheckLibsOnly*/, /*0*/ iBEMProcIdx, FALSE /*bSkipCheckingRuleLib*/, FALSE /*bNameIsPrefix*/ );
                     if (pObj2 != pObj)
                     {
                     // check for ANY references to a component of this name
                        int iNumRefs = 0;
                        for (int i1Class2=1; i1Class2<=pBEMProc->getNumClasses(); i1Class2++)
                           if (BEMPX_GetClass( i1Class2, iError, iBEMProcIdx ) != NULL && iError >= 0)
                           {
                              // Cruise thru list of BEM objects for this class and of the specified type
                              int nObjs2 = BEMPX_GetNumObjects( i1Class2, eObjType, iBEMProcIdx );
                              for ( int obj2 = 0; obj2 < nObjs2; obj2++ )
                              {
                                 // get pointer to object and confirm that it is OK
                                 BEMObject* pObj2 = BEMPX_GetObjectByClass( i1Class2, iError, obj2, eObjType, iBEMProcIdx );      assert( iError >= 0 && pObj2 );
                                 if (iError >= 0 && pObj2)
                                 {
                                    // loop over all properties describing this object
                                    for (int iProp2=0; iProp2<pObj2->getPropertiesSize(); iProp2++)
                                    {
                                       BEMProperty* pProp2 = pObj2->getProperty(iProp2);                assert( pProp2 != NULL && pProp2->getType() != NULL );
                                       // check for properties assigned to an object by the name of this dup object
                                       if (pProp2 && pProp2->getType() && pProp2->getType()->getPropType() == BEMP_Obj && 
                                       	 pProp2->getObj() && pProp2->getObj()->getName().compare( pObj->getName() ) == 0)
                                       {  assert( FALSE );
                                          iNumRefs++;
                                       }
                                    }
                                 }
                              }
                           }

                        if (iNumRefs < 1)
                        {  bRenameObj = TRUE;
                           saDupCompNames.push_back( pObj->getName() );
                        }
                        else
								{	saDupCompNames_Refed.push_back( pObj->getName() );
									iRetVal++;
								}
                     }  // end of if (object w/ same name exists)
                  }

                  if (bRenameObj)
                  {
                     QString sNewObjName = pObj->getName();
                     BEMPX_GetDefaultComponentName( i1Class, sNewObjName, iBEMProcIdx, 2 /*iFirstIndex=-1*/ );
                     pObj->setName( sNewObjName );
                  }
               }
            }
         }
      }

		if (saDupCompNames_Refed.size() > 0)
      {	QString errMsg = "Error:  Multiple referenced objects found with the same name: ";
			for (i1Class = 0; i1Class < saDupCompNames_Refed.size(); i1Class++)
			{	errMsg += " | ";
				errMsg += saDupCompNames_Refed[i1Class];
			}
			errMsg += " |";

			if (pszErrMsg && iErrMsgLen > 0)
			{	if (_snprintf_s( pszErrMsg, iErrMsgLen, _TRUNCATE, errMsg.toLocal8Bit().constData() ) == -1)
					AppendEllipsis( pszErrMsg, iErrMsgLen );
			}
         if (bWriteErrorsToLog)
            BEMPX_WriteLogFile( errMsg, NULL, FALSE, bSupressAllMessageBoxes );
      }

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_FloatConditionTrue()
//
// Function(s) to evaluate conditions (for screen control toggling and range checking)
/////////////////////////////////////////////////////////////////////////////

BOOL BEMPX_FloatConditionTrue( double fLtValue, int iCondition, double fRtValue, long lRtDBID, int iOccur )
{
   BOOL bRetVal = TRUE;

   if (lRtDBID > 0)
   {
      int iError, iSpecialVal;
      int iDispDataType = BEMPX_GetDataType( lRtDBID );
      int iStatus = BEMPX_GetDataStatus( lRtDBID, iOccur );  // SAC 8/4/02 - Pass in iOccur
      if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
      {
//         void* pData = BEMPX_GetData( lRtDBID, iDataType, iSpecialVal, iError, iOccur );  // SAC 8/4/02 - Pass in iOccur
			if (iDispDataType == BEMP_Flt || iDispDataType == BEMP_Int || iDispDataType == BEMP_Sym)
				fRtValue = BEMPX_GetFloat( lRtDBID, iSpecialVal, iError, iOccur, BEMO_User, -1, true /*bAllowNonFloatDataTypes*/ );
//         if ( (iError >= 0) && pData )
//         {
//            if ( (iDispDataType == BEMP_Int) || (iDispDataType == BEMP_Sym) )
//               // Check current value vs. conditional value and bActive state
//               fRtValue = (double) *((long*) pData);
//            else if (iDispDataType == BEMP_Flt)
//               // Check current value vs. conditional value and bActive state
//               fRtValue = *((double*) pData);
//            else
//               bRetVal = FALSE;
//         }
         else
            bRetVal = FALSE;
      }
      else
         bRetVal = FALSE;
   }

   if (bRetVal)
   {
      switch (iCondition)
      {
         case BEMC_Equal       :   bRetVal = (fLtValue == fRtValue);   break; 
         case BEMC_LessOrEqual :   bRetVal = (fLtValue <= fRtValue);   break; 
         case BEMC_GrtrOrEqual :   bRetVal = (fLtValue >= fRtValue);   break; 
         case BEMC_Less        :   bRetVal = (fLtValue <  fRtValue);   break; 
         case BEMC_Greater     :   bRetVal = (fLtValue >  fRtValue);   break; 
         case BEMC_NotEqual    :   bRetVal = (fLtValue != fRtValue);   break; 
      }
   }

   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_ConditionTrue()
//
// Function(s) to evaluate conditions (for screen control toggling and range checking)
/////////////////////////////////////////////////////////////////////////////

BOOL BEMPX_ConditionTrue( long lCondDBID, int iCondition, double fRtValue, long lRtDBID, int iOccur, long lCondDBID2 )
{
   BOOL bRetVal = TRUE;
   double fLtValue = 0;

   int iError, iSpecialVal;
   int iDispDataType = BEMPX_GetDataType( lCondDBID );
   int iStatus = BEMPX_GetDataStatus( lCondDBID, iOccur );
	if (iDispDataType == BEMP_Obj && lCondDBID2 > 0 && iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
	{
		BEMObject* pObj = BEMPX_GetObjectPtr( lCondDBID, iSpecialVal, iError, iOccur );			assert( pObj );
		if (pObj && pObj->getClass())
		{	lCondDBID = lCondDBID2;
			iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
			iDispDataType = BEMPX_GetDataType( lCondDBID2 );
			iStatus = BEMPX_GetDataStatus( lCondDBID2, iOccur, pObj->getObjectType() );
	}	}
   if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
   {
//      void* pData = BEMPX_GetData( lCondDBID, iDataType, iSpecialVal, iError, iOccur );
//
//      // SAC 3/4/99 - Added code to enable retrieval of referenced component data
//      if ( lCondDBID2 > 0 && iError >= 0 && pData )
//      {
//         ASSERT( iDispDataType == BEMP_Obj );
//         iDispDataType = BEMPX_GetDataType( lCondDBID2 );
//
//         BEMObject* pObj = (BEMObject*) pData;
//         ASSERT( pObj->getClass() );
//
//         iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
//         iStatus = BEMPX_GetDataStatus( lCondDBID2, iOccur, pObj->getObjectType() );
//         if ( iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes )
//            pData = BEMPX_GetData( lCondDBID2, iDataType, iSpecialVal, iError, iOccur, pObj->getObjectType() );
//         else
//            pData = NULL;
//      }
		if (iDispDataType == BEMP_Flt || iDispDataType == BEMP_Int || iDispDataType == BEMP_Sym)
			fLtValue = BEMPX_GetFloat( lCondDBID, iSpecialVal, iError, iOccur, BEMO_User, -1, true /*bAllowNonFloatDataTypes*/ );
//      if ( iError >= 0 && pData )
//      {
//         if (iDispDataType == BEMP_Int || iDispDataType == BEMP_Sym)
//            // Check current value vs. conditional value and bActive state
//            fLtValue = (double) *((long*) pData);
//         else if (iDispDataType == BEMP_Flt)
//            // Check current value vs. conditional value and bActive state
//            fLtValue = *((double*) pData);
//         else
//            bRetVal = FALSE;
//      }
      else
         bRetVal = FALSE;
   }
   else
      bRetVal = FALSE;

   if (bRetVal)
      bRetVal = BEMPX_FloatConditionTrue( fLtValue, iCondition, fRtValue, lRtDBID, iOccur );  // SAC 8/4/02 - pass iOccur into BEMPX_FloatConditionTrue()

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetBEMUnitsLabel()
//
// Purpose ------------------------------------------------------------------
//   Get the units label for a specified database variable.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   NULL if units label not found, else a pointer to the label string.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
QString BEMPX_GetBEMUnitsLabel( long lDBID )
{
   int i1Class = BEMPX_GetClassID( lDBID );
   if (i1Class > 0 && i1Class <= eBEMProc.getNumClasses())
   {
      int i1Prop  = BEMPX_GetPropertyID( lDBID );
      if (i1Prop == 0)
         return NULL;  // units index for Active, Name, Parent
      else
      {  // units index for standard database variables
         BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Prop );
         if (pPropType != NULL)
            return pPropType->getUnitsLabel();
      }
   }
   return "";
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetItemHelpID()
//
// Purpose ------------------------------------------------------------------
//   Get the item help ID for the specified property type.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   0 if the item help ID not found, otherwise > 0 item help ID.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
UINT BEMPX_GetItemHelpID(  long lDBID )
{
   UINT uiRetVal = 0;
   int iError;
   // get pointer to property type from lDBID
   BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
   if ( (iError >= 0) && (pPropType != NULL) )
      uiRetVal = pPropType->getHelpID();
   // SAC 6/30/99 - added the following to enable Active, Name and Parent to have item help IDs by component type
   else
   {
      uiRetVal = BEMPX_GetTopicHelpID( lDBID );
      int iArray = BEMPX_GetArrayID( lDBID );
      if (uiRetVal > 0 && iArray > 0)
         uiRetVal += (UINT) iArray;
   }
   return uiRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GetTopicHelpID()
//
// Purpose ------------------------------------------------------------------
//   Get the topic help ID for the specified class.
//   
// Arguments ----------------------------------------------------------------
//   long lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   
// Return Value -------------------------------------------------------------
//   0 if the topic help ID not found, otherwise > 0 topic help ID.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
UINT BEMPX_GetTopicHelpID( long lDBID )
{
   UINT uiRetVal = 0;
   int iError;
   // get pointer to class from lDBID
   BEMClass* pClass = BEMPX_GetClass( BEMPX_GetClassID( lDBID ), iError );
   if ( (iError >= 0) && (pClass != NULL) )
      uiRetVal = pClass->getHelpID();
   return uiRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// classes to facilitate rulelist evaluation debugging

BEMCompNameTypeProp::BEMCompNameTypeProp( BEMCompNameTypeProp* pCNTP )
{  assert( pCNTP );
   if (pCNTP)
   {
      m_compName     = pCNTP->m_compName;
      m_compType     = pCNTP->m_compType;
      m_propertyType = pCNTP->m_propertyType;
      m_array        = pCNTP->m_array;
   }
}

BEMCompNameTypeProp::~BEMCompNameTypeProp()
{
   m_compName.clear();
}

BOOL BEMCompNameTypeProp::Matches( int iBEMClass, long lDBID, BEMObject* pObj )
{
   return ( (m_compType == -1 && !m_compName.isEmpty() && !pObj->getName().compare( m_compName, Qt::CaseInsensitive )) ||		// SAC 11/18/14 - was case sensitive:  !pObj->getName().Compare( m_compName )) ||
            (m_compType == iBEMClass  &&  
             ( (!m_compName.isEmpty()  &&  pObj  &&  !pObj->getName().compare( m_compName, Qt::CaseInsensitive )  &&				// SAC 11/18/14 - was case sensitive:  !pObj->getName().Compare( m_compName )  &&
                                            (m_propertyType < 0 || m_propertyType == BEMPX_GetPropertyID(lDBID))  &&  (m_array < 0 || m_array == BEMPX_GetArrayID(lDBID)) )  ||
               ( m_compName.isEmpty()  &&  (m_propertyType < 0 || m_propertyType == BEMPX_GetPropertyID(lDBID))  &&  (m_array < 0 || m_array == BEMPX_GetArrayID(lDBID)) ) )) );
}

// class __declspec(dllexport) BEMCompNameTypePropArray : public CObject
//    CArray<BEMCompNameTypeProp*, BEMCompNameTypeProp*> m_paItems;

BEMCompNameTypePropArray::~BEMCompNameTypePropArray()
{
   DeleteContents();
}

void BEMCompNameTypePropArray::DeleteContents()
{
   int size = (int) m_items.size();
   for (int i=size-1; i>=0; i--)
      delete (BEMCompNameTypeProp*) m_items.at(i);
   m_items.clear();

   m_rulelistNames.clear();   // SAC 9/14/10
   m_dataFileName.clear();  // SAC 8/5/10 - members to track whether or not data from specified file has already been read in
   m_fileTime = 0;
   m_fileSize = 0;
   m_verboseFlag = 0;       // SAC 8/5/10 - used for rulelist verbose (debugging) output...
   m_logRuleListEval = 0;
}

BOOL BEMCompNameTypePropArray::ReadData( const char* pszBEMCompNameTypePropListFile, int& iVerboseFlag, int& iLogRuleListEval )
{
   BOOL bRetVal = FALSE;
   if (pszBEMCompNameTypePropListFile == NULL || strlen( pszBEMCompNameTypePropListFile ) < 1)  // clear out all array data if no file specified to read from
   {
      DeleteContents();
      iVerboseFlag = 0;
      iLogRuleListEval = 0;
      bRetVal = TRUE;  // valid return, even though nothing read
   }
   else if (FileExists( pszBEMCompNameTypePropListFile ))
   {
      BOOL bContinueLoadingFile = TRUE;
//      CFileStatus status;        // SAC 8/5/10 - added code to prevent re-loading BEMCompNameTypePropArray data (if already loaded)
//      if (CFile::GetStatus( pszBEMCompNameTypePropListFile, status ))      
//      {
//         CTime     fileTime = status.m_mtime;
//         ULONGLONG fileSize = status.m_size;
		QFileInfo fi( pszBEMCompNameTypePropListFile );
		if (fi.exists())
		{	qint64 fileSize = fi.size();
			UINT   fileTime = fi.lastModified().toTime_t();
         if (m_dataFileName.isEmpty())
         {
            m_dataFileName = pszBEMCompNameTypePropListFile;  // SAC 8/5/10 - members to track whether or not data from specified file has already been read in
            m_fileTime = fileTime;
            m_fileSize = fileSize;
         }
         else if (!m_dataFileName.compare( pszBEMCompNameTypePropListFile, Qt::CaseInsensitive ) && m_fileTime == fileTime && m_fileSize == fileSize)
         {
            bRetVal = TRUE;  // valid return, even though nothing read
            iVerboseFlag     = m_verboseFlag;
            iLogRuleListEval = m_logRuleListEval;
            bContinueLoadingFile = FALSE;
         }
      }   

      if (bContinueLoadingFile)
      {
			QString sErrMsg;
         try
         {  // open file
            BEMTextIO file( pszBEMCompNameTypePropListFile, BEMTextIO::load );
            try
            {
               bRetVal = TRUE;
               int iFileVersion;
               file >> iFileVersion;                              file.PostReadToken();
               file >> iVerboseFlag;                              file.PostReadToken();
               file >> iLogRuleListEval;                          file.PostReadToken();  // not sure what the purpose of this was ??
               m_verboseFlag     = iVerboseFlag;      // SAC 8/5/10
               m_logRuleListEval = iLogRuleListEval;

               QString sRecString;
               sRecString = file.ReadCSVString();                 file.PostReadToken();

               if (iFileVersion > 1)   // SAC 9/14/10
               {  // first list of strings is a list of rulelist names 
                  while (sErrMsg.isEmpty() && sRecString.compare( "END-OF-RULELISTS", Qt::CaseInsensitive ))
                  {
                     m_rulelistNames.push_back( sRecString );
                     sRecString = file.ReadCSVString();           file.PostReadToken();
                  }
                     sRecString = file.ReadCSVString();           file.PostReadToken();   // read next string FOLLOWING 'END-OF-RULELISTS'
               }

               BEMCompNameTypeProp bdbCNTP;
               while (sErrMsg.isEmpty() && sRecString.compare( "END-OF-FILE", Qt::CaseInsensitive ))
               {	QString sOrigRecStr = sRecString;
                  int iLastQuoteIdx  = sRecString.lastIndexOf('\"');
                  int iFirstColonIdx = sRecString.indexOf(':');
                  int iLastColonIdx  = sRecString.lastIndexOf(':');
                  if (sRecString[0] == '\"' && iLastQuoteIdx > 0)
                  {
                     bdbCNTP.setCompName( sRecString.mid( 1, iLastQuoteIdx-1 ) );
                     if (sRecString.length() > iLastQuoteIdx+2)
                     {
                        sRecString = sRecString.right( sRecString.length() - iLastQuoteIdx - 1 - (iLastQuoteIdx == iFirstColonIdx-1 ? 1 : 0) );
                        iLastQuoteIdx  = -1;
                        iFirstColonIdx = sRecString.indexOf(':');
                        iLastColonIdx  = sRecString.lastIndexOf(':');
                     }
                     else
                     {
                        sRecString.clear();
                        iLastQuoteIdx = iFirstColonIdx = iLastColonIdx = -1;
                     }
                  }
                                                                                             assert( sRecString.isEmpty() || sRecString.indexOf('\"') < 0 );
                  if (sRecString[0] == ':')
                  {
                     sRecString = sRecString.right( sRecString.length()-1 );
                     iLastQuoteIdx  = sRecString.lastIndexOf('\"');
                     iFirstColonIdx = sRecString.indexOf(':');
                     iLastColonIdx  = sRecString.lastIndexOf(':');
                  }

                  if (iLastQuoteIdx >= 0 || iFirstColonIdx == 0)
                     sErrMsg = QString( "Error reading BEMProc component name/type/property data '%1' from record #%2 of file\n   %3" ).arg( sOrigRecStr, QString::number(file.GetLineCount()), pszBEMCompNameTypePropListFile );

                  if (sErrMsg.isEmpty()  &&  iFirstColonIdx < iLastColonIdx)
                  {  // 2 colons => both comp name & type
                     bdbCNTP.setCompName( sRecString.left( iFirstColonIdx ) );
                     sRecString = sRecString.right( sRecString.length() - iFirstColonIdx - 1 );
                     iFirstColonIdx = sRecString.indexOf(':');
                     iLastColonIdx  = sRecString.lastIndexOf(':');
                     if (iFirstColonIdx != iLastColonIdx && iFirstColonIdx >= 0)
                        sErrMsg = QString( "Error reading BEMProc component name/type/property data (too many colons in '%1') from record #%2 of file\n   %3" ).arg( sOrigRecStr, QString::number(file.GetLineCount()), pszBEMCompNameTypePropListFile );
                  }

                  if (sErrMsg.isEmpty()  &&  iFirstColonIdx == iLastColonIdx  &&  iFirstColonIdx < 0)
                  {  // NO colons, so must be either component name or component type
                     int iCompID = BEMPX_GetDBComponentID( sRecString.toLocal8Bit().constData() );
                     if (iCompID > 0)
                     {
                        bdbCNTP.setCompType( iCompID );
                        bdbCNTP.setPropertyType( -1 );
                        bdbCNTP.setArray(        -1 );
                     }
                     else if (bdbCNTP.getCompName().isEmpty())
                     {
                        bdbCNTP.setCompName( sRecString );
                        bdbCNTP.setCompType(     -1 );
                        bdbCNTP.setPropertyType( -1 );
                        bdbCNTP.setArray(        -1 );
                     }
                     else
                        sErrMsg = QString( "Error reading BEMProc component name/type/property data (invalid component type '%1') from record #%2 of file\n   %3" ).arg( sOrigRecStr, QString::number(file.GetLineCount()), pszBEMCompNameTypePropListFile );
                  }

                  if (sErrMsg.isEmpty()  &&  iFirstColonIdx == iLastColonIdx  &&  iFirstColonIdx > 0)
                  {
                     long lDBID = BEMPX_GetDatabaseID( sRecString );
                     if (lDBID <= 0)
                        sErrMsg = QString( "Error reading BEMProc component name/type/property data (invalid Comp:Prop string '%1') from record #%2 of file\n   %3" ).arg( sOrigRecStr, QString::number(file.GetLineCount()), pszBEMCompNameTypePropListFile );
                     else
                     {
                        bdbCNTP.setCompType(     BEMPX_GetClassID(    lDBID ) );
                        bdbCNTP.setPropertyType( BEMPX_GetPropertyID( lDBID ) );
                        bdbCNTP.setArray(        BEMPX_GetArrayID(    lDBID ) );
                        if (bdbCNTP.getArray() < 1)
                           bdbCNTP.setArray( -1 );
                     }
                  }

                  if (sErrMsg.isEmpty())
                  {
                     BEMCompNameTypeProp* pBEMCNTP = new BEMCompNameTypeProp( &bdbCNTP );            assert( pBEMCNTP );
                     if (pBEMCNTP)
                        m_items.push_back( pBEMCNTP );
                     else
                        sErrMsg = QString( "Error reading BEMProc component name/type/property data (initializing BEMCompNameTypeProp '%1') from record #%2 of file\n   %3" ).arg( sOrigRecStr, QString::number(file.GetLineCount()), pszBEMCompNameTypePropListFile );
                  }

                  sRecString = file.ReadCSVString();              file.PostReadToken();
               }

               if (!sErrMsg.isEmpty())
               {
                  bRetVal = FALSE;
                  BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
               }
            }
//            catch( BEMTextioException& err )
//            {
//               bRetVal = FALSE;
//               BEMMessageBox( QString("Error Reading BEMProc Component Name/Type/Property data.\nFrom File: %1\n\n\t%2\n\n").arg( pszBEMCompNameTypePropListFile, err->m_strError ), "", 2 /*warning*/ );
//               THROW_LAST();
//            }
				catch (std::exception& e)
				{
	            bRetVal = FALSE;
					BEMMessageBox( QString( "Warning: Error Reading BEMProc Component Name/Type/Property data - cause: %1" ).arg( e.what() ), "", 2 /*warning*/ );
				}
			 	catch (...)
			  	{
	            bRetVal = FALSE;
					BEMMessageBox( "Error Reading BEMProc Component Name/Type/Property data.", "", 2 /*warning*/ );
			  	}
         }
//         catch (std::exception& e)
//         {
//            QString msg = QString( "Error opening file: " ) + pszBEMCompNameTypePropListFile;
//				std::cout << msg.toLocal8Bit().constData() << '\n';
//            BEMMessageBox( msg, "", 2 /*warning*/ );
//            bRetVal = FALSE;
//         }
		 	catch (...)
		  	{
            bRetVal = FALSE;
            BEMMessageBox( QString( "Error opening file: %1" ).arg( pszBEMCompNameTypePropListFile ), "", 2 /*warning*/ );
		  	}
      }
   }
   return bRetVal;
}

//   std::vector<BEMCompNameTypeProp*> m_items;
//   QStringList m_rulelistNames;   // SAC 9/14/10 - added new member to facilitate echoing of each rule in a specified list of rulelists
//   QString  m_dataFileName;  // SAC 8/5/10 - members to track whether or not data from specified file has already been read in
//	UINT		m_fileTime;
//	qint64	m_fileSize;
//   int m_verboseFlag;       // SAC 8/5/10 - used for rulelist verbose (debugging) output...
//   int m_logRuleListEval;


BOOL BEMCompNameTypePropArray::Copy( BEMCompNameTypePropArray* pCNTPA )
{  assert( pCNTPA );
   BOOL bRetVal = TRUE;
   if (pCNTPA)
   {
      DeleteContents();

      int i;
      int size = pCNTPA->m_items.size();
      for (i=0; (bRetVal && i<size); i++)
      {
         BEMCompNameTypeProp* pObj = new BEMCompNameTypeProp( pCNTPA->m_items[i] );         assert( pObj );
         if (pObj)
            m_items.push_back( pObj );
         else
            bRetVal = FALSE;
      }

      size = pCNTPA->m_rulelistNames.size();   // SAC 9/14/10
      for (i=0; (bRetVal && i<size); i++)
         m_rulelistNames.push_back( pCNTPA->m_rulelistNames[i] );
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}

BOOL BEMCompNameTypePropArray::MatchExists( long lDBID, int iOccur /*=-1*/, int iBEMProcIdx /*=-1*/ )
{
   BOOL bRetVal = FALSE;
   int iBEMClass = BEMPX_GetClassID( lDBID );
   if (iBEMClass > 0)
   {  int iError;
      BEMObject* pObj = (iOccur < -1.5 ? NULL : BEMPX_GetObjectByClass( iBEMClass, iError, iOccur, BEMO_User, iBEMProcIdx ));
      int size = (int) m_items.size();
      for (int i=0; (!bRetVal && i < size); i++)
      {
         BEMCompNameTypeProp* pCNTP = m_items.at(i);              assert( pCNTP );
         if (pCNTP)
            bRetVal = pCNTP->Matches( iBEMClass, lDBID, pObj );
      }
   }
   return bRetVal;
}

BOOL BEMCompNameTypePropArray::RulelistMatchExists( const char* pszRulelistName )   // SAC 9/14/10
{
   BOOL bRetVal = FALSE;
   QString sRulelistName = pszRulelistName;
   int iRulelistNameLen = sRulelistName.length();
   int iSize = m_rulelistNames.size();
   for (int i=0; (!bRetVal && i < iSize); i++)
   {
      QString sRulelistNameChk = m_rulelistNames[i];
      int iRulelistNameChkLen = sRulelistNameChk.length();
      if (iRulelistNameChkLen > 0)
      {
         if (sRulelistNameChk[0] == '*' && sRulelistNameChk[iRulelistNameChkLen-1] == '*' && iRulelistNameChkLen > 2 && iRulelistNameLen >= (iRulelistNameChkLen-2))
            // match MIDDLE portion of rulelist name
            bRetVal = (sRulelistName.indexOf( sRulelistNameChk.mid( 1, iRulelistNameChkLen-2 ) ) >= 0);
         else if (sRulelistNameChk[0] == '*' && iRulelistNameChkLen > 1 && iRulelistNameLen >= (iRulelistNameChkLen-1))
            // match only RIGHT portion of rulelist name
            bRetVal = (sRulelistNameChk.right( iRulelistNameChkLen-1 ).compare( sRulelistName.right( iRulelistNameChkLen-1 ), Qt::CaseInsensitive ) == 0);
         else if (sRulelistNameChk[iRulelistNameChkLen-1] == '*' && iRulelistNameChkLen > 1)
            // match only LEFT portion of rulelist name
            bRetVal = (sRulelistNameChk.left(  iRulelistNameChkLen-1 ).compare( sRulelistName.left(  iRulelistNameChkLen-1 ), Qt::CaseInsensitive ) == 0);
         else
            // straight comparison of entire rulelist name
            bRetVal = (sRulelistNameChk.compare( sRulelistName, Qt::CaseInsensitive ) == 0);
      }
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

UINT GetDefaultMsgBoxButton( UINT nAllBtns, UINT nDefault )
{	UINT sbDefault = QMessageBox::NoButton;
		if (nDefault > 0)   sbDefault = nDefault;
		else if (nAllBtns & QMessageBox::Ok			)   sbDefault = QMessageBox::Ok			;
		else if (nAllBtns & QMessageBox::Open		)   sbDefault = QMessageBox::Open		;
		else if (nAllBtns & QMessageBox::Yes		)   sbDefault = QMessageBox::Yes		  ;
		else if (nAllBtns & QMessageBox::YesToAll	)   sbDefault = QMessageBox::YesToAll	;
		else if (nAllBtns & QMessageBox::Retry		)   sbDefault = QMessageBox::Retry		;
		else if (nAllBtns & QMessageBox::Save		)   sbDefault = QMessageBox::Save		;
		else if (nAllBtns & QMessageBox::SaveAll	)   sbDefault = QMessageBox::SaveAll	;
		else if (nAllBtns & QMessageBox::Apply		)   sbDefault = QMessageBox::Apply		;
		else if (nAllBtns & QMessageBox::Reset		)   sbDefault = QMessageBox::Reset		;
		else if (nAllBtns & QMessageBox::RestoreDefaults)   sbDefault = QMessageBox::RestoreDefaults;
		else if (nAllBtns & QMessageBox::Ignore	)   sbDefault = QMessageBox::Ignore	  ;
		else if (nAllBtns & QMessageBox::Cancel	)   sbDefault = QMessageBox::Cancel	  ;
		else if (nAllBtns & QMessageBox::Close		)   sbDefault = QMessageBox::Close		;
		else if (nAllBtns & QMessageBox::Discard	)   sbDefault = QMessageBox::Discard	;
		else if (nAllBtns & QMessageBox::No			)   sbDefault = QMessageBox::No			;
		else if (nAllBtns & QMessageBox::NoToAll	)   sbDefault = QMessageBox::NoToAll	;
		else if (nAllBtns & QMessageBox::Abort		)   sbDefault = QMessageBox::Abort		;
		else if (nAllBtns & QMessageBox::Help		)   sbDefault = QMessageBox::Help		;
	return sbDefault;
}

int BEMMessageBox(const TCHAR* msg, const TCHAR* caption /*=NULL*/, UINT nIcon /*=0*/, UINT nType /*=1024*/, UINT nDefault /*=0*/ )
{	int iRetVal = -1;
#ifdef BEM_QTGUI
		QApplication* pqApp = NULL;
		if (QCoreApplication::instance() == NULL)
		{	int argc = 0;
			pqApp = new QApplication( argc, NULL );
		}

		UINT sbDefault = GetDefaultMsgBoxButton( nType, nDefault );

					// display report issues dialog
					QString qsDlgCaption;
					if (caption && strlen( caption ) > 0)
						qsDlgCaption = caption;
					else
						qsDlgCaption = "BEMProc Message";

					QMessageBox msgBox;
					msgBox.setWindowTitle( qsDlgCaption );
					msgBox.setIcon( (QMessageBox::Icon) nIcon ); 
		//			msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
					msgBox.setText( msg );
		//			msgBox.setDetailedText( qsRptIssuesDlgDetails );
					msgBox.setStandardButtons( (QMessageBox::StandardButtons) nType );		// QMessageBox::Ok );
		//			msgBox.addButton( QMessageBox::Abort );
					if (sbDefault != QMessageBox::NoButton)
						msgBox.setDefaultButton( (QMessageBox::StandardButton) sbDefault );
		//			bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);
					iRetVal = msgBox.exec();

		if (pqApp)
			delete pqApp;
#endif
	return iRetVal;
}

int BEMMessageBox( QString msg, QString caption /*=""*/, UINT nIcon /*=0*/, UINT nType /*=1024*/, UINT nDefault /*=0*/ )
{	int iRetVal = -1;
#ifdef BEM_QTGUI
		QApplication* pqApp = NULL;
		if (QCoreApplication::instance() == NULL)
		{	int argc = 0;
			pqApp = new QApplication( argc, NULL );
		}

		UINT sbDefault = GetDefaultMsgBoxButton( nType, nDefault );

					// display report issues dialog
					if (caption.isEmpty())
						caption = "BEMProc Message";

					QMessageBox msgBox;
					msgBox.setWindowTitle( caption );
					msgBox.setIcon( (QMessageBox::Icon) nIcon ); 
		//			msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
					msgBox.setText( msg );
		//			msgBox.setDetailedText( qsRptIssuesDlgDetails );
					msgBox.setStandardButtons( (QMessageBox::StandardButtons) nType );		// QMessageBox::Ok );
		//			msgBox.addButton( QMessageBox::Abort );
					if (sbDefault != QMessageBox::NoButton)
						msgBox.setStandardButtons( (QMessageBox::StandardButton) sbDefault );		// QMessageBox::Ok );
		//			bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);
					iRetVal = msgBox.exec();

		if (pqApp)
			delete pqApp;
#endif
	return iRetVal;
}

