// expLibraryIO.cpp - functions to read and write component library from/to encrypted binary file
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
#include "BEMProc.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMProperty.h"
#include "BEMProcObject.h"
#include "BEMProcI.h"
#include "expCrypFile.h"
#include "expLibraryIO.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
//
// Function:  WriteRuleLibrary()
//
// Purpose ------------------------------------------------------------------
//   Writes the contents of the ruleset's component library to the binary
//   encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write the component library to
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void WriteRuleLibrary( CryptoFile& file, QFile& errorFile )
#else
void WriteRuleLibrary( CryptoFile& file, QFile& /*errorFile*/ )
#endif
{
#ifdef _DEBUG
   QString dbgMsg = QString( "\n\n   Writing Rule Library Objects:\n" );
   errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif

   // loop over all database classes
   int iNumClasses = BEMPX_GetNumClasses();
   for (int i1Class=1; i1Class<=iNumClasses; i1Class++ )
   {
      // get and write the number of rule library components of this class which exist
      int nObjs = BEMPX_GetNumObjects( i1Class, BEMO_RuleLib );
      file.Write( &nObjs, sizeof(int) );

      if (nObjs > 0)
      {
#ifdef _DEBUG
         int iClsErr;
         BEMClass* pClass = BEMPX_GetClass( i1Class, iClsErr );
         if (pClass)
         {	dbgMsg = QString( "      writing %1 objects of class %2:\n" ).arg( QString::number(nObjs), pClass->getLongName() );
            errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
         }
#endif

         for ( int iObjIdx=0; iObjIdx < nObjs; iObjIdx++ )
         {  // get each object in order to write it out
            int iObjError = 0;
            BEMObject* pObj = BEMPX_GetObjectByClass( i1Class, iObjError, iObjIdx, BEMO_RuleLib );
            if (pObj != NULL)
            {
               file.WriteQString( pObj->getName() );  // write the object name

               // Get number of properties to store
               std::vector<long> lDBIDArray;
               // loop over all properties of this class
               BEMClass* pClass = eBEMProc.getClass( i1Class-1 );			assert( pClass );

               for (int iPropIdx=1; (pClass && iPropIdx <= pClass->getNumProps()); iPropIdx++)
               {
                  // loop over all property array elements
                  for (int iPropArrIdx=1; iPropArrIdx<=eBEMProc.getPropertyType( iPropIdx-1 + pClass->getFirstPropID() )->getNumValues(); iPropArrIdx++)
                  {
                     long lDBID = BEMPX_GetDBID( i1Class, iPropIdx, iPropArrIdx );  // SAC 7/17/01 - was: ((long)i1Class * 10000) + ((long)iPropIdx * 100) + (long)iPropArrIdx;
                     int iError = 0;
                     // get a pointer to the property
                     BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObjIdx, BEMO_RuleLib );
                     if (pProp && pProp->getDataStatus() == BEMS_RuleLibrary)
                        // add it to the list only if its value is defined by the rule library (not defaulted or blank)
                        lDBIDArray.push_back( lDBID );
                  }
               }

               // Store only those properties which were found to be rule library defined
               int arraySize = (int) lDBIDArray.size();    QString sData;
               file.Write( &arraySize, sizeof(int) );  // write the number of properties beign written to the file
               for (int idx=0; idx<arraySize; idx++)
               {
                  long lDBID = lDBIDArray[idx];
                  int iError = 0;
                  // get the property and write its DBID and value to the file
                  BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObjIdx, BEMO_RuleLib );
                  if (pProp && pProp->getDataStatus() == BEMS_RuleLibrary)
                  {	long iData;  double dData;
                     file.Write( &lDBID, sizeof(long) );
                     switch (pProp->getType()->getPropType())
                     {
                        case BEMP_Int :
                        case BEMP_Sym : 
                        	iData = pProp->getInt();
                           file.Write( &iData, sizeof(long) );
                           break;
                        case BEMP_Flt : 
                        	dData = pProp->getDouble();
                           file.Write( &dData, sizeof(double) );
                           break;
                        case BEMP_Str : 
                        	sData = pProp->getString();
                           file.WriteQString( sData );
                           break;
                        case BEMP_Obj : 
                        	if (pProp->getObj())
                        		sData = pProp->getObj()->getName();
                        	else
                        	{	sData = "(null)";				assert( false ); // ever get here ??
                        	}
                           file.WriteQString( sData );
                           break;
                        default :   
                           break;
                     }
                  }
               }

#ifdef _DEBUG
               dbgMsg = QString( "         '%1' %2 properties\n" ).arg( pObj->getName(), QString::number(arraySize) );
               errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif

               // Store Parent
               sData = (pObj->getParent() != NULL ? pObj->getParent()->getName() : "");
               file.WriteQString( sData );
            }
            else
               ; // pObj == NULL.   Error ??
         }
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Function:  ReadRuleLibrary()
//
// Purpose ------------------------------------------------------------------
//   Reads the ruleset's component library from the binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read the component library from
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void ReadRuleLibrary( CryptoFile& file )
{
   // loop over all database classes
   int iNumClasses = BEMPX_GetNumClasses();
   for ( int l1Class=1; l1Class<=iNumClasses; l1Class++ )
   {
      int nObjs;
      // get the number of objects of this class which are stored in the file
      file.Read( &nObjs, sizeof(int) );
      // loop over this number of objects, retrieving each from the file
      for ( int iObjIdx=0; iObjIdx < nObjs; iObjIdx++ )
      {
         QString objName;
         // read object name from file
         file.ReadQString( objName );
         // create object in building database
         BEMObject* pObj = BEMPX_CreateObject(l1Class, objName.toLocal8Bit().constData(), NULL, BEMO_RuleLib );
         if (pObj != NULL)
         {
            int arraySize;
            // read the number of properties stored which define this object
            file.Read( &arraySize, sizeof(int) );
            // loop over all properties stored for this object
            for ( int idx=0; idx < arraySize; idx++ ) 
            {
               long lDBID;
               // read the DBID of this property
               file.Read( &lDBID, sizeof( long ) );
               int iError = 0;
               // get a pointer to this property from the building database
               BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObjIdx, BEMO_RuleLib );

               if ( pProp == NULL || iError < 0 )
                  BEMMessageBox( QString( "Error reading library entry: %1" ).arg( objName ), "", 3 /*error*/ );
               else 
               {	long iData;  double dData;  QString sData;
                  // set the property's status flag
                  pProp->setDataStatus( BEMS_RuleLibrary );
                  // read from the file and set the value of this property
                  switch (pProp->getType()->getPropType())
                  {
                     case BEMP_Int :
                     case BEMP_Sym : 
                        file.Read( &iData, sizeof(long) );
                        pProp->setInt( iData );
                        break;
                     case BEMP_Flt : 
                        file.Read( &dData, sizeof(double) );
                        pProp->setDouble( dData );
                        break;
                     case BEMP_Str : 
                     case BEMP_Obj :
                        file.ReadQString( sData );
                        pProp->setString( sData );
                        break;
                     default :   
                        break;
                  }
               }
            }

            // Read Parent
            QString strParent;
            file.ReadQString( strParent );
            if ( strParent == "" )
               pObj->setParent( NULL );
            else
            {
               int iError;
               pObj->setParent( BEMPX_GetObjectByName( l1Class, iError, strParent.toLocal8Bit().constData(), BEMO_RuleLib ) );
               if ( pObj->getParent() != NULL )
               	pObj->addChildToParent();
            }
         }
         else
            BEMMessageBox( QString( "Error reading library entry: %1" ).arg( objName ), "", 3 /*error*/ );
      }
   }

   // resolve all references to objects which are stored only by object name during the reading process
   int iNumObjsNotFound = BEMP_ResolveAllReferences( BEMO_RuleLib );		iNumObjsNotFound;
}
