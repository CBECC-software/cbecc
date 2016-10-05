// ErrCheck.cpp : Defines the function which performs the BEMProc check
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
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMProperty.h"
//#include "BEMP_Sym.h"
#include "memLkRpt.h"


// SAC 8/22/11 - removed application-specific component existence checks
//static char BASED_CODE szReqCls1[] = "Proj";
//static char BASED_CODE szReqCls2[] = "Site";
//static char BASED_CODE szReqCls3[] = "Bldg";
//static char BASED_CODE szReqCls4[] = "Space";
//static char BASED_CODE szReqCls5[] = "HVACSys";
//static char BASED_CODE szReqCls6[] = "Plant";
//static const char* pszReqCls[] = { szReqCls1, szReqCls2, szReqCls3,
//                                   szReqCls4, szReqCls5, szReqCls6 };
//#define  NUM_REQ_CLASSES  6
//static int siaReqCls[ NUM_REQ_CLASSES ];

static QVector<BEMError> selErrorList;


// SAC 6/4/99 - added argument to enable properties tagged as "Required" to be reported as errors (or not) when undefined
// SAC 1/3/01 - added 2nd argument to enable properties flagged as "simulation default" to NOT be reported as errant
// SAC 8/18/03 - Added BOOL bPerformReqdClassCheck argument in order to toggle OFF this COMcheck-Plus-specific check
// SAC 11/18/04 - Added new function argument to enable posting of both warnings & errors
// SAC 5/1/14 - added #defs to specify checks of data classified as user input but that shouldn't be (via BEM_UserInpChk_DisallowNotInput & BEM_UserInpChk_DisallowPrescribed)
BOOL BEMPX_PerformErrorCheck( BOOL bRequireRequiredData, BOOL bReportSimDefaultErrors, BOOL /*bPerformReqdClassCheck*/,
										BOOL bPostRangeWarnings, int iUserInpChk /*=0*/, BOOL bPerformRangeChecks /*=TRUE*/ )
{
   QString sMsg;
//   int iError;

   // First reset the error listing
   BEMPX_ResetErrorListing();

   BEMPX_WriteLogFile( "Performing Building Database check..." );

// SAC 8/22/11 - removed application-specific component existence checks
// 1. Check to make sure that all required components are defined
//   if (bPerformReqdClassCheck)  // SAC 8/18/03
//      for (int i0Cls=0; i0Cls<NUM_REQ_CLASSES; i0Cls++)
//      {
//         // Set the required clas index if it hasn't already been
//         if (siaReqCls[i0Cls] == 0)
//            siaReqCls[i0Cls] = BDX_GetDBComponentID( pszReqCls[i0Cls] );
//         assert( siaReqCls[i0Cls] > 0 );
//
//         // Confirm that at least one component exists of this class
//         if (BDX_GetNumObjects( siaReqCls[i0Cls] ) < 1)
//         {  // log error message if no objects of any type found
//            CBDClass* pClass = BDX_GetClass( siaReqCls[i0Cls], iError );
////            QString sMsg = "Error:  At least one ";
//            sMsg = "Error:  At least one ";
//            if (pClass)
//                  sMsg += pClass->getLongName();
//            else  sMsg += "Class Unknown";
//            sMsg += " component must be defined.";
//            BDX_LogError( sMsg, ERR_SEVERITY_ERROR, ERR_CODE_NOCOMPS, ERR_MODULE_BDBASE, siaReqCls[i0Cls] );
//         }
//      }

// 2. While we loop over all the BEMObjects, make sure all those
//    classes which have parent pointers in fact have parent assignments
// 3. Check that each parent component does not exceed the iMaxChild
//    flags for any of it's compatible child types
// 4. Check to make sure that all data tagged by the ruleset as
//    "Required" or "Compulsory" is in fact defined
// 5. Perform ruleset-defined range checks
	int iNumWarnings = 0;  // SAC 11/20/13 - added counter for warnings (separate from errors)
   int iNumClasses = BEMPX_GetNumClasses();
   for (int i1Cls=1; i1Cls<=iNumClasses; i1Cls++)
   {
      int iNumObjects = BEMPX_GetNumObjects( i1Cls );
      for (int i0Obj=0; i0Obj<iNumObjects; i0Obj++)
      {
         int iError;
         BEMObject* pObj = BEMPX_GetObjectByClass( i1Cls, iError, i0Obj );
         if (pObj)
         {
            // Confirm that this component HAS a parent assigned if one is required
            if (pObj->getClass()->getParentType(0) >= 0 && pObj->getParent() == NULL)
            {
               sMsg = QString( "Warning:  %1 '%2' has no parent component assigned." ).arg( pObj->getClass()->getLongName(), pObj->getName() );
               BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_WARNING, ERR_CODE_NOPARENT, ERR_MODULE_BEMPROC, i1Cls, BEMO_User, i0Obj );
					iNumWarnings++;  // SAC 11/20/13
            }

            // Confirm that iMaxChild has not been exceeded for any of this component's child types
            int iCT = 0;
            while (iCT < BEM_MAX_CHILD_TYPES && pObj->getClass()->getChildType(iCT) >= 0)
            {
               BEMClass* pChildClass = BEMPX_GetClass( pObj->getClass()->getChildType(iCT)+1, iError );
               if (pChildClass && pChildClass->getMaxChildren() >= 0 &&
                   ((int) BEMPX_GetNumChildren( i1Cls, i0Obj, BEMO_User, pChildClass->get1BEMClassIdx() ) > pChildClass->getMaxChildren()))
               {  // log iMaxChild error
                  sMsg = QString( "Error:  The %1 '%2' has too many children of type %3 assigned." ).arg( pObj->getClass()->getLongName(),
                  									pObj->getName(), pChildClass->getLongName() );
                  BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_ERROR, ERR_CODE_MAXCHILD, ERR_MODULE_BEMPROC, i1Cls, BEMO_User, i0Obj );
               }
               iCT++;
            }

            // Loop over all properties and confirm that all "Required" or "Compulsory" data is defined
            for (int iProp=0; iProp<pObj->getPropertiesSize(); iProp++)
            {  BEMProperty* pProp = pObj->getProperty(iProp);						assert( pProp != NULL );
               assert( pProp->getType() != NULL );
               long lDBID = BEMPX_GetDBID( i1Cls, pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() );

            //   assert( pProp->getType()->m_olDataTypes.GetCount() >= pProp->get1ArrayIdx() );  // SAC 9/17/01
            //   POSITION posDT = pProp->getType()->m_olDataTypes.FindIndex( pProp->get1ArrayIdx()-1 );
            //   // get pointer to the BEMDataType
            //   BEMDataType* pDT = (BEMDataType*) pProp->getType()->m_olDataTypes.GetAt( posDT );
               BEMPropTypeDetails* pDT = NULL;
               if (pProp->getType()->getNumPropTypeDetails() >= pProp->get1ArrayIdx())
               	pDT = pProp->getType()->getPropTypeDetails( pProp->get1ArrayIdx()-1 );
               if (pDT == NULL)
               {  // Error - BEMPropTypeDetails not found
                  QString sParam;
                  BEMPX_DBIDToDBCompParamString( lDBID, sParam );
                  sMsg = QString( "Error:  Property type details not found for %1 '%2': %3." ).arg( 
                  									pObj->getClass()->getLongName(), pObj->getName(), sParam );
                  BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_ERROR, ERR_CODE_DTNOTFOUND, ERR_MODULE_BEMPROC, lDBID, BEMO_User, i0Obj );
               }
               else if ( ( pDT->getCompDataType() == BEMD_Compulsory ||
                          (pDT->getCompDataType() == BEMD_Required && bRequireRequiredData) ) &&
                         ( pProp->getDataStatus() == BEMS_Undefined  ) )
               {  // Error - data "Required" or "Compulsory" but not defined
                  QString sParam;
                  BEMPX_DBIDToDBCompParamString( lDBID, sParam );
                  sMsg = QString( "Error:  Data classified by the compliance ruleset as %1 not defined for %2 '%3': %4." ).arg(
																(pDT->getCompDataType() == BEMD_Compulsory) ? "Compulsory" : "Required",
																pObj->getClass()->getLongName(), pObj->getName(), sParam );
                  BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_ERROR, ERR_CODE_REQDATA, ERR_MODULE_BEMPROC, lDBID, BEMO_User, i0Obj );
               }
					else if ( pProp->getDataStatus() == BEMS_UserDefined &&			// SAC 5/1/14 - added #defs to specify checks of data classified as user input but that shouldn't be
									( (pDT->getCompDataType() == BEMD_NotInput   && iUserInpChk & BEM_UserInpChk_DisallowNotInput  ) ||
									  (pDT->getCompDataType() == BEMD_Prescribed && iUserInpChk & BEM_UserInpChk_DisallowPrescribed) ) )
               {  // Error - data classified as UserInput, but should not be
						QString sParam;
                  BEMPX_DBIDToDBCompParamString( lDBID, sParam );
                  sMsg = QString( "Error:  Data classified by the compliance ruleset as %1 should not be user-specified: %2 '%3': %4." ).arg(
																(pDT->getCompDataType() == BEMD_NotInput) ? "NotInput" : "Prescribed",
																pObj->getClass()->getLongName(), pObj->getName(), sParam );
                  BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_ERROR, ERR_CODE_REQDATA, ERR_MODULE_BEMPROC, lDBID, BEMO_User, i0Obj );
					}
               else if ( (pProp->getType()->getPropType() == BEMP_Int ||
                          pProp->getType()->getPropType() == BEMP_Flt ||
                          pProp->getType()->getPropType() == BEMP_Obj)  &&   // SAC 8/7/00 - Added ability to range check BEMP_Obj data for > 0
                         // SAC 1/3/01 - added following line of code to enable properties flagged as "simulation default" to NOT be reported as errant
                         (bReportSimDefaultErrors  ||  pProp->getSpecialValue() != SV_Default) )
               {
                  double fData;
                  BOOL bDataOK = BEMPX_GetFloat( lDBID, fData, 0, -1, i0Obj );
// SAC 8/7/00 - Replaced below w/ above, partially to fix a typo bug (WAS checking for iPropType == BEMP_Int as opposed to BEMP_Flt)
//              and partially because separate calls to BEMPX_GetInteger() and BEMPX_GetFloat() were unnecessary
//                   long  lData;
//                   // retrieve data to be range checked
//                   if (pProp->getType()->getPropType() == BEMP_Int &&
//                       BEMPX_GetInteger( lDBID, lData, 0, -1, i0Obj ))
//                   {
//                      fData = (double) lData;
//                      bDataOK = TRUE;
//                   }
//                   else if (pProp->getType()->getPropType() == BEMP_Int &&
//                            BEMPX_GetFloat( lDBID, fData, 0, -1, i0Obj ))
//                      bDataOK = TRUE;
                  // perform range check
//                  if (bDataOK && BEMPX_PerformRangeCheck( lDBID, fData, TRUE, &sMsg, i0Obj ) == RANGE_ERROR)   // SAC 8/4/02 - Added i0Obj argument
//                  {  // Range checking error, sMsg already mostly loaded
// SAC 11/18/04 - Implemented new function argument to enable posting of both warnings & errors
                  if (bDataOK && bPerformRangeChecks)
                  {
                     int iSeverity = BEMPX_PerformRangeCheck( lDBID, fData, TRUE, &sMsg, i0Obj );   // SAC 8/4/02 - Added i0Obj argument
                     if (iSeverity == RANGE_ERROR  ||  (bPostRangeWarnings && iSeverity == RANGE_WARNING))
                     {  // Range checking error (or warning), sMsg already mostly loaded
                        QString sParam;
                        BEMPX_DBIDToDBCompParamString( lDBID, sParam );
                        QString sMsg2 = QString( "%1:  Range check failure on %2 '%3'.  %4 (%5)" ).arg(
                        									(iSeverity == RANGE_WARNING ? "Warning" : "Error"), 
                        									pObj->getClass()->getLongName(), pObj->getName(), sMsg, sParam );
                        BEMPX_LogError( sMsg2.toLocal8Bit().constData(), (iSeverity == RANGE_WARNING ? ERR_SEVERITY_WARNING : ERR_SEVERITY_ERROR),
                                        ERR_CODE_RANGECHECK, ERR_MODULE_BEMPROC, lDBID, BEMO_User, i0Obj );
								if (iSeverity == RANGE_WARNING)
									iNumWarnings++;  // SAC 11/20/13
                     }
                  }
               }
            }
         }
         else
         {  // log error message if no objects of any type found
            BEMClass* pClass = BEMPX_GetClass( i1Cls, iError );
            sMsg = QString( " component %1 of %2" ).arg( QString::number(i0Obj+1), QString::number(iNumObjects) );
            if (pClass)
                  sMsg = pClass->getLongName() + sMsg;
            else  sMsg = "Class Unknown" + sMsg;
            sMsg = "Error:  Unable to retrieve " + sMsg;
            BEMPX_LogError( sMsg.toLocal8Bit().constData(), ERR_SEVERITY_ERROR, ERR_CODE_GETOBJECT, ERR_MODULE_BEMPROC, i1Cls, BEMO_User, i0Obj );
         }
      }
   }

// ?? Check consistency across all ScheduleType assignments between
//    parent/child components

// SAC 5/16/14 - revised messaging to NOT include "error" or "warning" unless errors or warnings are found
   int iNumErrors = BEMPX_GetNumErrors() - iNumWarnings;  // SAC 11/18/04 - revised to return only the number of ERR_SEVERITY_ERRORs, as opposed to total # in list
	if (iNumWarnings < 1 && iNumErrors < 1)
		sMsg = "Building Database check completed, no problems found.";
	else if (iNumWarnings > 0 && iNumErrors > 0)
		sMsg = QString( "Building Database check completed, %1 warning(s) and %2 error(s) found." ).arg( QString::number(iNumWarnings), QString::number(iNumErrors) );
	else if (iNumErrors > 0)
		sMsg = QString( "Building Database check completed, %1 error(s) found." ).arg( QString::number(iNumErrors) );
	else
		sMsg = QString( "Building Database check completed, %1 warning(s) found." ).arg( QString::number(iNumWarnings) );
   BEMPX_WriteLogFile( sMsg );

   return (iNumErrors == 0);
}


int BEMPX_BlastInvalidUserInputs( int iUserInpFix /*=BEM_UserInpFix_NotInput*/ )
{	int iNumMods = 0;
   int iNumClasses = BEMPX_GetNumClasses();
   for (int i1Cls=1; i1Cls<=iNumClasses; i1Cls++)
   {  int iNumObjects = BEMPX_GetNumObjects( i1Cls );
      for (int i0Obj=0; i0Obj<iNumObjects; i0Obj++)
      {  int iError;
         BEMObject* pObj = BEMPX_GetObjectByClass( i1Cls, iError, i0Obj );
         if (pObj)
         {  // Loop over all properties and confirm that all "Required" or "Compulsory" data is defined
            for (int iProp=0; iProp<pObj->getPropertiesSize(); iProp++)
            {  BEMProperty* pProp = pObj->getProperty(iProp);						assert( pProp != NULL );
					if (pProp)
               {	assert( pProp->getType() != NULL );
               	assert( pProp->getType()->getNumPropTypeDetails() >= pProp->get1ArrayIdx() );  // SAC 9/17/01
               	// get pointer to the BEMPropTypeDetails
               	BEMPropTypeDetails* pDT = pProp->getType()->getPropTypeDetails( pProp->get1ArrayIdx()-1 );
               	if (pDT == NULL || pProp->getDataStatus() != BEMS_UserDefined)
               	{	// do nothing
               	}
						else if ((pDT->getCompDataType() == BEMD_NotInput && (iUserInpFix & BEM_UserInpFix_NotInput) ) ||
									(FALSE))
               	{  // blast this user input
							iNumMods++;
							long lDBID = BEMPX_GetDBID( i1Cls, pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() );
							pProp->Default( lDBID, i0Obj /*, BEM_ObjType eObjType=BEMO_User, BOOL bReinitializing=FALSE, int iBEMProcIdx=-1*/ );
						}
	}	}	}	}	}

	QString sLogMsg;
	if (iNumMods > 0)
		sLogMsg = QString( "%1 user input(s) blasted by BEMPX_BlastInvalidUserInputs(%2)" ).arg( QString::number(iNumMods), QString::number(iUserInpFix) );
	else
		sLogMsg = QString( "No user inputs modified by BEMPX_BlastInvalidUserInputs(%1)" ).arg( QString::number(iUserInpFix) );
   BEMPX_WriteLogFile( sLogMsg );

	return iNumMods;
}


/////////////////////////////////////////////////////////////////////////////
// Exported Functions

void BEMPX_ResetErrorListing()
{
   selErrorList.clear();

// vvvvv DEBUGGING vvvvv
#ifdef _DEBUG
#pragma warning(disable : 4996)
   FILE *dbgFile = fopen( "BEMError.dbg", "wt" );
   if (dbgFile)
   {
      fprintf( dbgFile, "Begin Error Listing:\n\n" );
      fflush( dbgFile );
      fclose( dbgFile );
   }
#pragma warning(default : 4996)
#endif
// ^^^^^ DEBUGGING ^^^^^
}


BOOL BEMPX_LogError( const char* sMessage, int iSeverity, int iErrorCode, int iModule,
                     long lDBID, BEM_ObjType eObjectType, int i0ObjectIdx, BOOL bWriteToProjectLog )
{
	int iInitCount = selErrorList.size();
	selErrorList.push_back( BEMError(
                      iModule,      // module error occurred in (ERR_MODULE_*)
                      lDBID,        // DBID of errant parameter
                      eObjectType,  // type of object which error occurred in
                      i0ObjectIdx,  // 0-based index of object which error occurred in
                      iSeverity,    // severity of error (ERR_SEVERITY_*)
                      iErrorCode,   // error code (ERR_CODE_*)
                      sMessage ) );   // error message
	if (selErrorList.size() <= iInitCount)
	{	assert( false );
	}
	else
	{
		if (iSeverity == ERR_SEVERITY_ERROR)
		{	//BEMPX_AddRulesetError( sMessage );  // SAC 1/21/13 - added call to post error messaage to ruleset
			int iObjClass = BEMPX_GetClassID( lDBID );		// SAC 4/23/13 - expanded error logging to include other details
			int iError;
	      BEMObject* pObj  = BEMPX_GetObjectByClass( iObjClass, iError, i0ObjectIdx, eObjectType );
			BEMP_AddRulesetErrorExt( sMessage, iObjClass, lDBID, (pObj ? pObj->getName().toLocal8Bit().constData() : "") );
		}

      if (bWriteToProjectLog)
         BEMPX_WriteLogFile( QString( "   %1" ).arg( sMessage ) );

// vvvvv DEBUGGING vvvvv
#ifdef _DEBUG
#pragma warning(disable : 4996)
      FILE *dbgFile = fopen( "BEMError.dbg", "atc" );
      if (dbgFile)
      {  fprintf( dbgFile, "%s\n", sMessage );
         fflush( dbgFile );
         fclose( dbgFile );
      }
#pragma warning(default : 4996)
#endif
// ^^^^^ DEBUGGING ^^^^^

      return TRUE;
	}
	return FALSE;

//   BEMError* pErr = NULL;
//   try
//   {  // allocate new BEMError
//      pErr = new BEMError(
//                      iModule,      // module error occurred in (ERR_MODULE_*)
//                      lDBID,        // DBID of errant parameter
//                      eObjectType,  // type of object which error occurred in
//                      i0ObjectIdx,  // 0-based index of object which error occurred in
//                      iSeverity,    // severity of error (ERR_SEVERITY_*)
//                      iErrorCode,   // error code (ERR_CODE_*)
//                      sMessage );   // error message
//      assert( pErr != NULL );
//
//      // add new BEMError to the end of olDepSets list
//      selErrorList.push_back( pErr );
//
//		if (iSeverity == ERR_SEVERITY_ERROR)
//		{	//BEMPX_AddRulesetError( sMessage );  // SAC 1/21/13 - added call to post error messaage to ruleset
//			int iObjClass = BEMPX_GetClassID( lDBID );		// SAC 4/23/13 - expanded error logging to include other details
//			int iError;
//	      BEMObject* pObj  = BEMPX_GetObjectByClass( iObjClass, iError, i0ObjectIdx, eObjectType );
//			BEMPX_AddRulesetErrorExt( sMessage, iObjClass, lDBID, (pObj ? pObj->getName() : "") );
//		}
//
//      if (bWriteToProjectLog)
//         BEMPX_WriteLogFile( QString( "   %1" ).arg( sMessage ) );
//
//// vvvvv DEBUGGING vvvvv
//#ifdef _DEBUG
//      FILE *dbgFile = fopen( "BEMError.dbg", "atc" );
//      if (dbgFile)
//      {  fprintf( dbgFile, "%s\n", sMessage );
//         fflush( dbgFile );
//         fclose( dbgFile );
//      }
//#endif
//// ^^^^^ DEBUGGING ^^^^^
//
//      return TRUE;
//   }
//	catch (...)
//	{	assert( false );
//	}
//   assert( false );
//   if (pErr != NULL)
//      delete pErr;
//   return FALSE;
}


int BEMPX_GetNumErrors()
{	return selErrorList.size();
}


const BEMError* BEMPX_GetErrorPtr( int idx )
{
   if (idx >= 0 && idx < selErrorList.size())
   {	return &selErrorList.at(idx);
      //POSITION pos = selErrorList.FindIndex( idx );
      //if (pos)
      //   return (BEMError*) selErrorList.GetAt( pos );
   }
   return NULL;
}


