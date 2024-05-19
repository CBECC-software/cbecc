// Reset.cpp - implementation of BEMResetDataList and BEMResetData class definitions
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
/*  (c) Copyright 1998, Regional Economic Research, Inc. and         */
/*                      SAC Software                                 */
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
#include "BEMProcI.h"
#include "expReset.h"
#include "expRuleList.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMResetData
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMResetData Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read this reset list definition from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CCryptoFile& file : the binary encrypted ruleset file to read this reset
//                       list definition from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMResetData::Read( CryptoFile& file )
{
   long lDBID;
   int iNumDBIDs;

   file.Read( &iNumDBIDs, sizeof( int ) );
   int i=0;
   for (; i < iNumDBIDs; i++)
   {
      file.Read( &lDBID, sizeof( long ) );
      m_modDBIDs.push_back( lDBID );
   }

   file.Read( &iNumDBIDs, sizeof( int ) );
   for (i=0; i < iNumDBIDs; i++)
   {
      file.Read( &lDBID, sizeof( long ) );
      m_resetDBIDs.push_back( lDBID );
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMResetData Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write this reset list definition to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CCryptoFile& file : the binary encrypted ruleset file to write this reset
//                       dep list definition to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMResetData::Write( CryptoFile& file )
{
   int iSize = (int) m_modDBIDs.size();
   file.Write( &iSize, sizeof( int ) );
   int i=0;
   for (; i < iSize; i++)
   {
      long lDBID = m_modDBIDs[i];
      file.Write( &lDBID, sizeof( long ) );
   }

   iSize = (int) m_resetDBIDs.size();
   file.Write( &iSize, sizeof( int ) );
   for (i=0; i < iSize; i++)
   {
      long lDBID = m_resetDBIDs[i];
      file.Write( &lDBID, sizeof( long ) );
   }
}


// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// //
// // class BEMResetDataList
// //
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMResetDataList Class Function:  ~BEMResetDataList()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the reset list definitions from the list.
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
// BEMResetDataList::~BEMResetDataList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMResetDataList Class Function:  RemoveAll()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the reset list definitions from the list, deleting each as we go.
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
// void BEMResetDataList::RemoveAll()
// {
//    POSITION pos = GetHeadPosition();
//    while (pos)
//       delete (BEMResetData*) GetNext( pos );
//    CObList::RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // Static Function:  GetResetDBID()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads a DBID token string from the TextIO file, returning its DBID value
// //   and posting an error to the errorFile in the event the DBID value is bogus.
// //   
// // Arguments ----------------------------------------------------------------
// //   CTextIO& file      : file to read the DBID token from
// //   CFile&   errorFile : file to post error messages to
// //   
// // Return Value -------------------------------------------------------------
// //   the numeric value corresponding to the DBID token string.
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// static long GetResetDBID( CTextIO& file, CFile& errorFile )
// {
//    CString sName;
//    file.ReadBEMProcParam( sName );
//    long lDBID = BEMPX_GetDatabaseID( sName );
// 
//    // Post error to error listing and set bRetVal to FALSE if database ID is invalid
//    if (lDBID <= 0)
//    {
//       CString sLine;
//       sLine.Format( "%d", file.GetLineCount() );
//       CString sErr;
//       sErr.Format( "\tParameter '%s' Not Found on line: ", sName );
//       sErr += sLine;
//       sErr += CString("\n");
//       sErr += CString("\n");
//       errorFile.Write( sErr.GetBuffer( sErr.GetLength() ), sErr.GetLength() );
//       sErr.ReleaseBuffer();
//    }
// 
//    file.PostReadToken();
// 
//    return lDBID;
// }

/////////////////////////////////////////////////////////////////////////////
//
// BEMResetDataList Class Function:  ReadText()
//
// Purpose ------------------------------------------------------------------
//   Read the reset list definitions from a text file.
//   
// Arguments ----------------------------------------------------------------
//   CString sFileName : path/filename of file to read reset list definitions from
//   CFile&  errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if all reset list definitions are successfully read from the file,
//   else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// bool BEMResetDataList::ReadText( CString sFileName, CFile& errorFile )
bool RuleSet::readResetsText( QString sFileName, QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( sFileName.toLocal8Bit().constData(), BEMTextIO::load );

      QString readMsg = QString("Reading resets file: %1\n\n").arg( sFileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
      try
      {
         try
         {
            BEMResetData* pCurResLst = NULL;
            int iRecHdr = (int) file.ReadLong();   // read record header value
            int iLastRecHdr = -1;
            long lDBID;
            while (iRecHdr >= 0)
            {
               file.PostReadToken();
               // read lDBID from reset file
               lDBID = ReadDBID( file );  //GetResetDBID( file, errorFile );

               if (iRecHdr == 0)  // beginning of a reset list
               {
                  if (iLastRecHdr != 0)          // last record was NOT a reset list beginning 
                  {                              // => create a new BEMResetData object & add it to the list
                     pCurResLst = new BEMResetData;
                     m_resets.push_back( pCurResLst );
                  }
               }

               assert(pCurResLst != NULL);
               if (lDBID > 0)
               {
                  if (iRecHdr == 0)
                     pCurResLst->m_modDBIDs.push_back( lDBID );
                  else
                     pCurResLst->m_resetDBIDs.push_back( lDBID );
               }
               else
                  bRetVal = FALSE;

               iLastRecHdr = iRecHdr;
               iRecHdr = (int) file.ReadLong();   // read next record header value
            }

            if (iRecHdr != -1)
               bRetVal = FALSE;
         }
			catch (BEMTextioException& te)
         {
            if ( te.m_cause == BEMTextioException::endOfFile )
               ; // we're done, no problem
            else
				{	bRetVal = FALSE;
               //THROW_LAST();
					throw std::runtime_error(boost::str(boost::format("Error reading resets from text because '%1', from file:  %2") %
																			te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
         }	}
      }
		catch (BEMTextioException& te)
      {  // ERROR occurred
         QString msg = QString("Error reading resets\nFrom File: %1\n\n\t%2\n\n").arg( sFileName, te.m_strError );
         errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
         bRetVal = FALSE;
         BEMMessageBox( msg, "", 2 /*warning*/ );
         //THROW_LAST();
			throw std::runtime_error(boost::str(boost::format("Error reading resets from text because '%1', from file:  %2") %
																	te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
      }
   }
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening resets text file: %1\n\t - cause: %2\n\n" ).arg( sFileName, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening resets text file: %1\n\n" ).arg( sFileName );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
  	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

void RuleSet::addReset( std::vector<long>& modDBIDs, std::vector<long>& resetDBIDs )	// SAC 11/3/16
{
	try
	{	BEMResetData* pReset = new BEMResetData;
		if (pReset)
		{	pReset->m_modDBIDs   = modDBIDs;
			pReset->m_resetDBIDs = resetDBIDs;
			addReset( pReset );
		}
	}
//	catch (std::exception& e)
//	{	assert( false );
//		//QString sErrMsg = QString( "Error creating BEMResetData - cause: %1\n\n" ).arg( e.what() );
//		//errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//	}
 	catch (...)
  	{	assert( false );
		//QString sErrMsg = QString( "Error creating BEMResetData\n\n" );
		//errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
  	}
}

void RuleSet::postResetsToDatabase()
{
//	// First reset all existing BEMProc reset data
//	BEMPX_InitializeResetData();		- unnecessary ??

	int iNumResets = getNumResets();
	for (int j=0; j<iNumResets; j++)
	{	BEMResetData* pReset = m_resets.at(j);			assert( pReset );
		if (pReset && pReset->m_modDBIDs.size() > 0 && pReset->m_resetDBIDs.size() > 0)
		{	for (int i2=0; i2 < (int) pReset->m_modDBIDs.size(); i2++)
			{	long lDBID = pReset->m_modDBIDs[i2];
				// get the selected BEMPropertyType
				BEMPropertyType* pPropType = BEMPX_GetPropertyType( BEMPX_GetClassID( lDBID ), BEMPX_GetPropertyID( lDBID ) );

				int iError = -1;  // => all OK
				if (pPropType == NULL)
				{	iError = 0;  // Error - invalid DBID
					assert( false );
				}
				else
				{
					int i1Array = BEMPX_GetArrayID( lDBID );
					int iStartIdx = 0, iEndIdx = 0;
					if (i1Array == 0)  // "ALL"
						iEndIdx = pPropType->getNumValues() - 1;  // setting ALL array elements
					else if (i1Array <= pPropType->getNumValues())
						iStartIdx = iEndIdx = i1Array - 1;  // setting a single array element
					else
						iError = 1;  // Error - invalid array idx

					assert( iEndIdx < pPropType->getNumPropTypeDetails() );
					for (int i=iStartIdx; (iError < 0 && i <= iEndIdx); i++)
					{
						BEMPropTypeDetails* pPTD = pPropType->getPropTypeDetails( i );		assert( pPTD );
						if (pPTD == NULL)
						{	iError = 2;  // Error - BEMPropTypeDetails not found
							assert( false );
						}
						else
						{	for (int k=0; k < (int) pReset->m_resetDBIDs.size(); k++)
								pPTD->addResetDBID( pReset->m_resetDBIDs[k] );
					}	}
			}	}
	}	}
	return;
}


// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMResetDataList Class Function:  Read()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads the reset list definitions from a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CCryptoFile& file : the binary encrypted ruleset file to read the reset
// //                       list definitions from.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMResetDataList::Read( CCryptoFile& file )
// {
//    int count = 0;
//    // read number of reset list definitions stored in file
//    file.Read( &count, sizeof( int ) );
// 
//    // loop over each entry, creating a new BEMResetData, reading it and adding it to the list
//    int i=0;
//    for (; i < count; i++)
//    {
//       BEMResetData* reslst = new BEMResetData;
//       reslst->Read( file );
//       AddTail( reslst );
//    }
// 
//    // Now reset all existing BEMProc reset data
//    BEMPX_InitializeResetData();
// 
//    // Post reset information to Building Database
//    POSITION pos = GetHeadPosition();
//    while ( pos != NULL )
//    {
//       BEMResetData* pR = (BEMResetData*) GetAt( pos );
// 
//       if (pR != NULL)
//       {
//          ASSERT( pR->m_modDBIDs.size() > 0 );
//          ASSERT( pR->m_resetDBIDs.size() > 0 );
// 
//          for (i=0; i<pR->m_modDBIDs.size(); i++)
//             for (int i2=0; i2<pR->m_resetDBIDs.size(); i2++)
//                BEMPX_AddResetDBID( (long) pR->m_modDBIDs.GetAt(i), pR->m_resetDBIDs.GetAt(i2) );
// 
//          GetNext( pos );
//       }
//       else
//          ASSERT( FALSE );
//    }
// 
//    return TRUE;
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMResetDataList Class Function:  Write()
// //
// // Purpose ------------------------------------------------------------------
// //   Writes the reset list definitions to a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CCryptoFile& file : the binary encrypted ruleset file to write the reset
// //                       list definitions to.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMResetDataList::Write( CCryptoFile& file )
// {
//    int count = (int) GetCount();
//    // write the number of reset list definitions
//    file.Write( &count, sizeof( int ) );
// 
//    POSITION pos = GetHeadPosition();
//    // loop over entire list, writing each to the file
//    while ( pos != NULL )
//    {
//       BEMResetData* reslst = (BEMResetData*) GetNext( pos );
//       reslst->Write( file );
//    }
// 
//    return TRUE;
// }
// 

