// datatype.cpp - implementation of BEMPropertyDataType and BEMPropertyDataTypeList classes
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
#include "BEMProc.h"
#include "BEMProcObject.h"
#include "expDataType.h"
#include "expRuleList.h"
//#include "RulPrc.h"
#include "memLkRpt.h"

// DataTypeStrings must be in the same order as the DataType enum
static char* dataTypeStrings[] = 
{ 
   "Compulsory", 
   "Required", 
   "CondRequired",	// SAC 2/11/15 
   "Optional", 
   "Default",
   "CriticalDef", 
   "Prescribed", 
   "NotInput" 
};


int StringToDataTypeEnum( QString& sType )
{	int iRetVal = -1;
	for (int i=0; (iRetVal < 0 && i < BEMPropertyDataType::NDataTypes); i++)
	{  if (sType.compare( dataTypeStrings[ i ], Qt::CaseInsensitive ) == 0)
	      iRetVal = i;
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMPropertyDataType
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyDataType Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a data type definition from a BEMTextIO file into this class instance.
//   
// Arguments ----------------------------------------------------------------
//   BEMTextIO& file      : text file to read datatype from
//   QFile&   errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if datatype successfully read from file, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPropertyDataType::Read( BEMTextIO& file, QFile& errorFile )
{
   bool bRetVal = TRUE;

   // sName includes <bldg component name>:<parameter name>([<array index>])
   QString sName;
   m_dbid = file.ReadBEMProcParam( sName );    // = 1 => DEFAULT
   if (m_dbid == 0)
      m_dbid = BEMPX_GetDatabaseID( sName );

   if (m_dbid <= 0 && sName.isEmpty())  // SAC 6/25/12 - set lDBID to special value denoting END of DataType file
      m_dbid = -999;
   else
	{	if (m_dbid <= 0)  // Post error to error listing
   	{
   	   QString sErr = QString( "\tParameter '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number(file.GetLineCount()) );
   	   errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
   	   bRetVal = FALSE;
   	}
   	file.PostReadToken();

   	QString type = file.ReadToken();  // read compiance datatype string
   	file.PostReadToken();

   	// convert compliance datatype string to enum value
		m_compDataType = StringToDataTypeEnum( type );
   	if (m_compDataType == -1)  // NDataTypes)
   	{  // => DataType string match NOT FOUND
   	   QString sErr = QString( "\tData Type '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number(file.GetLineCount()) );
   	   errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
   	   bRetVal = FALSE;
   	}

   	// read flag values from file
   	m_primary = GetNextBool( file );
   	m_editable = GetNextBool( file );
   	m_userDefault = GetNextBool( file );
   	m_displayInput = GetNextBool( file );
   	m_displayProposed = GetNextBool( file );
   	m_displayBudget = GetNextBool( file );

		m_notInputMode = NotInp_AllowUIReset;		// SAC 8/12/15 - no text file entry for these new members (for now)
		m_notInputMsg.clear();
	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyDataType Class Function:  GetNextBool()
//
// Purpose ------------------------------------------------------------------
//   Gets the next boolean flag value from the file.
//   
// Arguments ----------------------------------------------------------------
//   BEMTextIO& file : file to read the boolean flag from
//   
// Return Value -------------------------------------------------------------
//   TRUE if next value in file == '1', else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPropertyDataType::GetNextBool( BEMTextIO& file )
{
   char ch = file.GetChr();

   if ( ch == ' ' || ch == ',' ) 
   {
      while ( ch == ' ' || ch == ',' ) 
         ch = file.GetChr();
   }

   return ( ch == '1' );
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyDataType Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read a datatype assignment entry from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read the datatype entry from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPropertyDataType::Read( CryptoFile& file )
{
   file.Read( &m_dbid,            sizeof( long ) );
   file.Read( &m_compDataType,    sizeof( int  ) );
   file.Read( &m_primary,         sizeof( bool ) );
   file.Read( &m_editable,        sizeof( bool ) );
   file.Read( &m_userDefault,     sizeof( bool ) );
   file.Read( &m_displayInput,    sizeof( bool ) );
   file.Read( &m_displayProposed, sizeof( bool ) );
   file.Read( &m_displayBudget,   sizeof( bool ) );
   file.Read( &m_notInputMode,    sizeof( int )  );		// SAC 8/12/15
	file.ReadQString( m_notInputMsg );
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyDataType Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write a datatype assignment entry to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write the datatype entry to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPropertyDataType::Write( CryptoFile& file )
{
   file.Write( &m_dbid,            sizeof( long ) );
   file.Write( &m_compDataType,    sizeof( int )  );
   file.Write( &m_primary,         sizeof( bool ) );
   file.Write( &m_editable,        sizeof( bool ) );
   file.Write( &m_userDefault,     sizeof( bool ) );
   file.Write( &m_displayInput,    sizeof( bool ) );
   file.Write( &m_displayProposed, sizeof( bool ) );
   file.Write( &m_displayBudget,   sizeof( bool ) );
   file.Write( &m_notInputMode,    sizeof( int )  );		// SAC 8/12/15
	file.WriteQString( m_notInputMsg );
}


// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// //
// // class BEMPropertyDataTypeList
// //
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  ~BEMPropertyDataTypeList()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all datatype entries from the list.
// //   
// // Arguments ----------------------------------------------------------------
// //   None
// //   
// // Return Value -------------------------------------------------------------
// //   None
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// BEMPropertyDataTypeList::~BEMPropertyDataTypeList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  InitDataTypeList()
// //
// // Purpose ------------------------------------------------------------------
// //   Initializes the list by removing all datatype entries.
// //   
// // Arguments ----------------------------------------------------------------
// //   None
// //   
// // Return Value -------------------------------------------------------------
// //   None
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// void BEMPropertyDataTypeList::InitDataTypeList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  RemoveAll()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the datatype entries from the list, deleting each as we go.
// //   
// // Arguments ----------------------------------------------------------------
// //   None
// //   
// // Return Value -------------------------------------------------------------
// //   None
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// void BEMPropertyDataTypeList::RemoveAll()
// {
//    POSITION pos = GetHeadPosition();
//    while ( pos != NULL )
//       delete (BEMPropertyDataType*)GetNext( pos );
//    CObList::RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  AddDataType()
// //
// // Purpose ------------------------------------------------------------------
// //   Adds a BEMPropertyDataType instance onto the end of the list.
// //   
// // Arguments ----------------------------------------------------------------
// //   None
// //   
// // Return Value -------------------------------------------------------------
// //   None
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// void BEMPropertyDataTypeList::AddDataType( BEMPropertyDataType* dataType )
// {
//    AddTail( (CObject*)dataType );
// }


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyDataTypeList Class Function:  ReadText()
//
// Purpose ------------------------------------------------------------------
//   Read the datatype definitions from a text file.
//   
// Arguments ----------------------------------------------------------------
//   QString sFileName : path/filename of file to read datatype definitions from
//   QFile&  errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if all datatype entries are successfully read from the file, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyDataTypeList::ReadText( QString sFileName, QFile& errorFile )
bool RuleSet::readDataTypesText( QString sFileName, QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( sFileName.toLocal8Bit().constData(), BEMTextIO::load );

      QString readMsg = QString("Reading datatypes file: %1\n\n").arg( sFileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
      try
      {
         try
         {
				BOOL bFileEndFound = FALSE;  // SAC 6/25/12
            while ( !bFileEndFound )   //TRUE ) // EOF handled in catch block 
            {  // create new BEMPropertyDataType
               BEMPropertyDataType* newData = new BEMPropertyDataType();
               // read datatype definition from file
               bRetVal = (newData->Read( file, errorFile ) && bRetVal);
				   if (newData->m_dbid == -999)  // SAC 6/25/12 - check for lDBID set to special value denoting END of DataType file reading
					{	bFileEndFound = TRUE;
						delete newData;
					}
					else
					{	// add this new BEMPropertyDataType to list
						ruleSet.addDataType( newData );
               	file.Advance();
					}
            }
         }
			catch (BEMTextioException& te)
         //CATCH( BEMTextioException, err )
         {
            if ( te.m_cause == BEMTextioException::endOfFile )
               ; // we're done, no problem
            else
				{	bRetVal = FALSE;
               //THROW_LAST();
					throw std::runtime_error(boost::str(boost::format("Error reading data types from text because '%1', from file:  %2") %
																			te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
         }	}
      }
		catch (BEMTextioException& te)
      {  // ERROR occurred
         QString msg = QString("Error reading datatypes\nFrom File: %1\n\n\t%2\n\n").arg( sFileName, te.m_strError );
         errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
         bRetVal = FALSE;
         BEMMessageBox( msg, "", 2 /*warning*/ );
         //THROW_LAST();
			throw std::runtime_error(boost::str(boost::format("Error reading data types from text because '%1', from file:  %2") %
																	te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
      }
   }
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening data types text file: %1\n\t - cause: %2\n\n" ).arg( sFileName, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening data types text file: %1\n\n" ).arg( sFileName );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
  	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Extern Function:  BEMP_InitializeDataTypes()
//
// Purpose ------------------------------------------------------------------
//   Called by rules processor to initialize the data types for ALL property
//   types in the building database based on default settings defined in the
//   selected compliance ruleset.
//   
// Arguments ----------------------------------------------------------------
//   int  eCompDT   : (default = CDT_NotInput) the default compliance type/classification
//   BOOL bPrim     : (default = FALSE) default value for all m_bPrimary flags
//   BOOL bEdit     : (default = FALSE) default value for all m_bEditable flags
//   BOOL bUserDef  : (default = FALSE) default value for all m_bUserDefault flags
//   BOOL bDispInp  : (default = FALSE) default value for all m_bDisplayInput flags
//   BOOL bDispProp : (default = FALSE) default value for all m_bDisplayProposed flags
//   BOOL bDispBudg : (default = FALSE) default value for all m_bDisplayBudget flags
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
void BEMP_InitializeDataTypes( int eCompDT, bool bPrim, bool bEdit, bool bUserDef,
                              bool bDispInp, bool bDispProp, bool bDispBudg,
										int iNotInputMode, QString sNotInputMsg )
{
   //for (int iBEMProcIdx=0; iBEMProcIdx < (sbBothBEMsActive ? 2 : 1); iBEMProcIdx++)
   for (int iBEMProcIdx=0; iBEMProcIdx < eNumBEMProcsLoaded; iBEMProcIdx++)		// SAC 3/13/13 - added multi model support
   {
      // SAC 8/13/99 - added code to provide access to second BEMProc
      BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );

      // loop over ALL property types
		int iNumPropTypes = pBEMProc->getNumPropertyTypes();					assert( iNumPropTypes > 0 );
		for (int i=0; i<iNumPropTypes; i++)
		{	BEMPropertyType* pPT = pBEMProc->getPropertyType( i );			assert( pPT );
			if (pPT)
			{	int iNumPTDetails = pPT->getNumPropTypeDetails();				assert( iNumPTDetails > 0 );
				for (int j=0; j<iNumPTDetails; j++)
				{	BEMPropTypeDetails* pPTD = pPT->getPropTypeDetails( j );		assert( pPTD );
			//		if (pPTD)
					if (pPTD && pPTD->getCompDataType() == BEMD_NDataTypes)	// SAC 10/12/16 - added logic to prevent initialization of data type settings ALREADY initialized (via BEMBase text data)
						pPTD->setData( eCompDT, bPrim, bEdit, bUserDef, bDispInp,
											bDispProp, bDispBudg, iNotInputMode, sNotInputMsg );
		}	}	}
   }
}


// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  Read()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads the datatype definitions from a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CryptoFile& file : the binary encrypted ruleset file to read the datatype definitions from.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyDataTypeList::Read( CryptoFile& file )
// {
//    int count = 0;
//    // read number of datatype definitions stored in file
//    file.Read( &count, sizeof( int ) );
// 
//    // loop over each entry, creating a new BEMPropertyDataType, reading it and adding it to the list
//    for ( int i = 0; i < count; i++ )
//    {
//       BEMPropertyDataType* dataType = new BEMPropertyDataType;
//       dataType->Read( file );
//       AddDataType( dataType );
//    }
// 
//    // Post DataType information to Building Database for access by user interface module
//    bool bFirstOne = TRUE;
//    POSITION pos = GetHeadPosition();
//    while ( pos != NULL )
//    {
//       BEMPropertyDataType* pDT = (BEMPropertyDataType*) GetAt( pos );
// 
//       if (pDT != NULL)
//       {
//          if (bFirstOne)
//          {
//             if (pDT->m_dbid == 1)  // DEFAULT
//                BEMPX_InitializeDataTypes( pDT->m_compDataType, pDT->m_primary,
//                                         pDT->m_editable, pDT->m_userDefault,
//                                         pDT->m_displayInput, pDT->m_displayProposed,
//                                         pDT->m_displayBudget );
//             else // no DEFAULT provided, so default to hard coded defaults
//                BEMPX_InitializeDataTypes();
// 
//             bFirstOne = FALSE;
//          }
// 
//          if (pDT->m_dbid != 1)
//          {
//             BEMPX_SetDataTypes( pDT->m_dbid, pDT->m_compDataType, pDT->m_primary,
//                               pDT->m_editable, pDT->m_userDefault, pDT->m_displayInput,
//                               pDT->m_displayProposed, pDT->m_displayBudget,
// 										pDT->m_notInputMode, pDT->m_notInputMsg );		// SAC 8/12/15
//          }
// 
//          GetNext( pos );
//       }
//       else
//       {
//          ASSERT( FALSE );
//       }
//    }
// 
//    return TRUE;
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyDataTypeList Class Function:  Write()
// //
// // Purpose ------------------------------------------------------------------
// //   Writes the datatype definitions to a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CryptoFile& file : the binary encrypted ruleset file to write the datatype definitions to.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyDataTypeList::Write( CryptoFile& file )
// {
//    int count = (int) GetCount();
//    // write the number of datatype definitions
//    file.Write( &count, sizeof( int ) );
// 
//    POSITION pos = GetHeadPosition();
//    // loop over entire list, writing each to the file
//    while ( pos != NULL )
//    {
//       BEMPropertyDataType* dataType = (BEMPropertyDataType*)GetNext( pos );
//       dataType->Write( file );
//    }
// 
//    return TRUE;
// }
// 
// 
// BEMPropertyDataType* BEMPropertyDataTypeList::GetDataType( long lDBID )  // SAC 9/17/14
// {	BEMPropertyDataType* pDT = NULL;
//    POSITION pos = GetHeadPosition();
//    while ( pos != NULL && pDT == NULL )
//    {
//       BEMPropertyDataType* dataType = (BEMPropertyDataType*)GetNext( pos );
// 		if (dataType && dataType->m_dbid == lDBID)
// 			pDT = dataType;
//    }
//    return pDT;
// }
// 
