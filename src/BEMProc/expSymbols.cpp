// expSymbols.cpp - implementation of SymLstList, SymLst, SymDepLst and Sym class definitions
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
#include "expTextIO.h"
#include "BEMProc.h"
#include "BEMProcI.h"
#include "expSymbols.h"
#include "expRuleList.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class Sym
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Sym Class Function:  Sym()
//
// Purpose ------------------------------------------------------------------
//   Constructor - does nothing for now
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
Sym::Sym()
{
}


Sym::Sym( const char* pszString, long iValue )
{
	m_iValue  = iValue;
	m_sString = pszString;
}


/////////////////////////////////////////////////////////////////////////////
//
// Sym Class Function:  ~Sym()
//
// Purpose ------------------------------------------------------------------
//   Destructor - does nothing for now
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
Sym::~Sym()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// Sym Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read this symbol definition from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read this symbol
//                       definition from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void Sym::Read( CryptoFile& file )
{
   file.Read( &m_iValue, sizeof( long ) );
   file.ReadQString( m_sString );
}


/////////////////////////////////////////////////////////////////////////////
//
// Sym Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write this symbol definition to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write this symbol
//                       definition to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void Sym::Write( CryptoFile& file )
{
   file.Write( &m_iValue, sizeof( long ) );
   file.WriteQString( m_sString );
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class SymDepLst
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// SymDepLst Class Function:  SymDepLst()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initialize members
//   
// Arguments ----------------------------------------------------------------
//   int iDefault : value for m_iDefaultValue
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
SymDepLst::SymDepLst( long iDefault )
{
   m_iDefaultValue = iDefault;
   m_iNumDepDBIDs = 0;
   for (int i=0; i<MAX_DEP_DBIDS_PER_LIST; i++)
   {
      m_lDBID[    i] = 0;
      m_fDepValue[i] = 0;
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// SymDepLst Class Function:  ~SymDepLst()
//
// Purpose ------------------------------------------------------------------
//   Destructor - clears out symbol list
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
SymDepLst::~SymDepLst()
{
	for (int i = (int) m_olSymbols.size()-1; i >= 0; i--)
	{	assert( m_olSymbols.at(i) );
		if (m_olSymbols.at(i))
			delete m_olSymbols.at(i);
	}
	m_olSymbols.clear();
}


/////////////////////////////////////////////////////////////////////////////
//
// SymDepLst Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read this symbol dep list definition from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read this symbol
//                       dep list definition from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void SymDepLst::Read( CryptoFile& file )
{
   file.Read( &m_iDefaultValue, sizeof( int ) );
   file.Read( &m_iNumDepDBIDs, sizeof( int ) );

   int i=0;
   for (; i < m_iNumDepDBIDs; i++)
   {
      file.Read( &m_lDBID[    i], sizeof( long ) );
      file.Read( &m_fDepValue[i], sizeof( double ) );
   }

   int iCount;
   file.Read( &iCount, sizeof( int ) );
   for (i=0; i < iCount; i++)
   {
      Sym* symbol = new Sym;
      symbol->Read( file );
      m_olSymbols.push_back( symbol );
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// SymDepLst Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write this symbol dep list definition to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write this symbol
//                       dep list definition to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void SymDepLst::Write( CryptoFile& file )
{
   file.Write( &m_iDefaultValue, sizeof( int ) );
   file.Write( &m_iNumDepDBIDs, sizeof( int ) );
	int i;
   for (i=0; i < m_iNumDepDBIDs; i++)
   {
      file.Write( &m_lDBID[    i], sizeof( long ) );
      file.Write( &m_fDepValue[i], sizeof( double ) );
   }

   int iCount = (int) m_olSymbols.size();
   file.Write( &iCount, sizeof( int ) );
	for (i=0; i < iCount; i++)
	{	assert( m_olSymbols.at(i) );
		if (m_olSymbols.at(i))
			m_olSymbols.at(i)->Write( file );;
	}
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class SymLst
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// SymLst Class Function:  SymLst()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initialize members
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
SymLst::SymLst()
{
   m_iNumDBIDs = 0;
   for (int i=0; i<MAX_DBIDS_PER_LIST; i++)
      m_lDBID[ i ] = 0;
}


/////////////////////////////////////////////////////////////////////////////
//
// SymLst Class Function:  ~SymLst()
//
// Purpose ------------------------------------------------------------------
//   Destructor - clears out symbol dep list
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
SymLst::~SymLst()
{
	for (int i = (int) m_olSymDepLists.size()-1; i >= 0; i--)
	{	assert( m_olSymDepLists.at(i) );
		if (m_olSymDepLists.at(i))
			delete m_olSymDepLists.at(i);
	}
	m_olSymDepLists.clear();
}


/////////////////////////////////////////////////////////////////////////////
//
// SymLst Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read this symbol list definition from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read this symbol
//                       list definition from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void SymLst::Read( CryptoFile& file )
{
   file.Read( &m_iNumDBIDs, sizeof( int ) );

   int i=0;
   for (; i < m_iNumDBIDs; i++)
      file.Read( &m_lDBID[i], sizeof( long ) );

   int iCount;
   file.Read( &iCount, sizeof( int ) );
   for (i=0; i < iCount; i++)
   {
      SymDepLst* symdeplst = new SymDepLst;
      symdeplst->Read( file );
      m_olSymDepLists.push_back( symdeplst );
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// SymLst Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write this symbol dep list definition to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write this symbol
//                       dep list definition to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void SymLst::Write( CryptoFile& file )
{
   file.Write( &m_iNumDBIDs, sizeof( int ) );
	int i;
   for (i=0; i < m_iNumDBIDs; i++)
      file.Write( &m_lDBID[i], sizeof( long ) );

   int iCount = (int) m_olSymDepLists.size();
   file.Write( &iCount, sizeof( int ) );
	for (i=0; i < iCount; i++)
	{	assert( m_olSymDepLists.at(i) );
		if (m_olSymDepLists.at(i))
			m_olSymDepLists.at(i)->Write( file );;
	}
}


// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// //
// // class SymLstList
// //
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // SymLstList Class Function:  ~SymLstList()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the symbol list definitions from the list.
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
// SymLstList::~SymLstList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // SymLstList Class Function:  RemoveAll()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the symbol list definitions from the list, deleting each as we go.
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
// void SymLstList::RemoveAll()
// {
//    POSITION pos = GetHeadPosition();
//    while (pos)
//       delete (SymLst*) GetNext( pos );
//    CObList::RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // Static Function:  GetSymbolDBID()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads a DBID token string from the TextIO file, returning its DBID value
// //   and posting an error to the errorFile in the event the DBID value is bogus.
// //   
// // Arguments ----------------------------------------------------------------
// //   BEMTextIO& symFile   : file to read the DBID token from
// //   QFile&   errorFile : file to post error messages to
// //   
// // Return Value -------------------------------------------------------------
// //   the numeric value corresponding to the DBID token string.
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// static long GetSymbolDBID( BEMTextIO& symFile, QFile& errorFile )
// {
//    QString sName;
//    symFile.ReadBEMProcParam( sName );
//    long lDBID = BEMPX_GetDatabaseID( sName );
// 
//    // Post error to error listing and set bRetVal to FALSE if database ID is invalid
//    if (lDBID <= 0)
//    {
//       QString sLine;
//       sLine.Format( "%d", symFile.GetLineCount() );
//       QString sErr;
//       sErr.Format( "\tParameter '%s' Not Found on line: ", sName );
//       sErr += sLine;
//       sErr += QString("\n");
//       sErr += QString("\n");
//       errorFile.Write( sErr.GetBuffer( sErr.GetLength() ), sErr.GetLength() );
//       sErr.ReleaseBuffer();
//    }
//    symFile.PostReadToken();
// 
//    return lDBID;
// }

/////////////////////////////////////////////////////////////////////////////
//
// SymLstList Class Function:  ReadText()
//
// Purpose ------------------------------------------------------------------
//   Read the symbol list definitions from a text file.
//   
// Arguments ----------------------------------------------------------------
//   QString sFileName : path/filename of file to read symbol list definitions from
//   QFile&  errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if all symbol list definitions are successfully read from the file,
//   else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// bool SymLstList::ReadText( QString sFileName, QFile& errorFile )
bool RuleSet::readSymbolsText( QString sFileName, QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( sFileName.toLocal8Bit().constData(), BEMTextIO::load );

      QString readMsg = QString("Reading symbols file: %1\n\n").arg( sFileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
      try
      {
         try
         {
            SymDepLst* pCurSymDepLst = NULL;
            SymLst* pCurSymLst = NULL;
            int iRecHdr = (int) file.ReadLong();   // read record header value
            int iLastRecHdr = -1;
            int iLastDefault = 0;
            while (iRecHdr >= 0)
            {
               file.PostReadToken();
               if (iRecHdr == 0)  // beginning of a symbol list
               {
                  if (iLastRecHdr != 0)          // last record was NOT a sym list beginning 
                  {                              // => create a new SymLst object & add it to the list
                     pCurSymLst = new SymLst;
                     m_symbolLists.push_back( pCurSymLst );
                  }

                  assert(pCurSymLst != NULL);
                  assert(pCurSymLst->m_iNumDBIDs < MAX_DBIDS_PER_LIST);
                  // read symbol list's DBID
                  pCurSymLst->m_lDBID[ pCurSymLst->m_iNumDBIDs++ ] = ReadDBID( file );  //, errorFile );
                  iLastDefault = (int) file.ReadLong();  // read default value for this symbol list
               }
               else if (iRecHdr == 1)  // beginning of a symbol dep list
               {
                  assert(pCurSymLst != NULL);
                  if (iLastRecHdr != 1)          // last record was NOT a sym dep list beginning 
                  {                              // => create a new SymDepLst object & add it to the current SymLst
                     pCurSymDepLst = new SymDepLst;
                     pCurSymLst->m_olSymDepLists.push_back( pCurSymDepLst );
                  }

                  assert(pCurSymDepLst->m_iNumDepDBIDs < MAX_DEP_DBIDS_PER_LIST);
                  pCurSymDepLst->m_lDBID[     pCurSymDepLst->m_iNumDepDBIDs   ] = ReadDBID( file );  //, errorFile );
                  pCurSymDepLst->m_fDepValue[ pCurSymDepLst->m_iNumDepDBIDs++ ] = file.ReadDouble();
                  file.PostReadToken();
                  pCurSymDepLst->m_iDefaultValue = (int) file.ReadLong();
               }
               else if (iRecHdr == 2)  // a single symbol definition
               {
                  assert(pCurSymLst != NULL);
                  if (iLastRecHdr == 0)          // last record was a sym list beginning 
                  {                              // => must create a dummy SymDepLst object w/ no dependencies
                     pCurSymDepLst = new SymDepLst( iLastDefault );  // use SymLst default
                     pCurSymLst->m_olSymDepLists.push_back( pCurSymDepLst );
                  }
                  assert(pCurSymDepLst != NULL);
                  Sym* pCurSym = new Sym;
                  pCurSym->m_iValue = file.ReadLong();       // read numeric value of this symbol
                  file.PostReadToken();
                  pCurSym->m_sString = file.ReadString();   // read symbol string
                  pCurSymDepLst->m_olSymbols.push_back( pCurSym );
               }

               iLastRecHdr = iRecHdr;
               iRecHdr = (int) file.ReadLong();   // read next record header value
            }

            if (iRecHdr != -1)
               bRetVal = FALSE;
         }
			catch (BEMTextioException& te)
         //CATCH( BEMTextioException, err )
         {
            if ( te.m_cause == BEMTextioException::endOfFile )
               ; // we're done, no problem
            else
				{	bRetVal = FALSE;
               //THROW_LAST();
					throw std::runtime_error(boost::str(boost::format("Error reading symbols from text because '%1', from file:  %2") %
																			te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
         }	}
      }
		catch (BEMTextioException& te)
      {  // ERROR occurred
         QString msg = QString("Error reading symbols\nFrom File: %1\n\n\t%2\n\n").arg( sFileName, te.m_strError );
         errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
         bRetVal = FALSE;
         BEMMessageBox( msg, "", 2 /*warning*/ );
         //THROW_LAST();
			throw std::runtime_error(boost::str(boost::format("Error reading range checks from text because '%1', from file:  %2") %
																	te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
      }
   }
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening symbols text file: %1\n\t - cause: %2\n\n" ).arg( sFileName, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening symbols text file: %1\n\n" ).arg( sFileName );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
  	}
   
   // Post Symbol information to Building Database for access by user interface module
   if (bRetVal)
      bRetVal = postSymbolsToDatabase();

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// Ruleset Function:  postSymbolsToDatabase()
/////////////////////////////////////////////////////////////////////////////
static char szErr1[] = "The ruleset was prevented from resetting the following symbol lists in order to preserve"
                       " simulation module integrity:\n";
static char szErr2[] = "\nConsult your compliance ruleset and/or simulation module provider for further assistance.";

bool RuleSet::postSymbolsToDatabase()
{
   // Post Symbol information to Building Database for access by user interface module
   std::vector<long> laSymbolsNotOverwritten;
	for (int iS=0; iS < (int) m_symbolLists.size(); iS++)	
	{	SymLst* pSL = m_symbolLists.at(iS);
      if (pSL)
      {
         // Replace existing BEMProc symbol info with that contained in this SymLst
         for (int i=0; i<pSL->m_iNumDBIDs; i++)
         {
            void* pBEMPSL = BEMPX_OverwriteSymbolList( pSL->m_lDBID[i], BEMS_RuleDefault );
            if (pBEMPSL == NULL)
               // BEMProc is preventing us from overwriting this SymbolList - probably due to simulation module
               laSymbolsNotOverwritten.push_back( pSL->m_lDBID[i] );
            else
            {  // loop over entire list, writing each element to the file
					for (std::vector<SymDepLst*>::iterator it = pSL->m_olSymDepLists.begin(); it != pSL->m_olSymDepLists.end(); ++it)
					{	SymDepLst* pSDL = *it;
                  if (pSDL)
                  {
                     void* pBEMPSDL = BEMPX_AddSymbolDepList( pBEMPSL, pSDL->m_iDefaultValue,
                                                           pSDL->m_lDBID[0], pSDL->m_fDepValue[0],
                                                           pSDL->m_lDBID[1], pSDL->m_fDepValue[1],
                                                           pSDL->m_lDBID[2], pSDL->m_fDepValue[2] );
                     if (pBEMPSDL)
                     {  // loop over entire list, writing each element to the file
								for (std::vector<Sym*>::iterator it2 = pSDL->m_olSymbols.begin(); it2 != pSDL->m_olSymbols.end(); ++it2)
								{	Sym* pS = *it2;
                           if (!pS || !BEMPX_AddSymbol( pBEMPSDL, pS->m_iValue, pS->m_sString.toLocal8Bit().constData() ))
									{	assert( FALSE );
                        }	}
                     }
                     else
							{	assert( FALSE );
                  }	}
                  else
						{	assert( FALSE );
               }	}
            }
         }
      }
      else
		{	assert( FALSE );
   }	}

   if (laSymbolsNotOverwritten.size() > 0)
   {  // one or more SymbolLists were not overwritten, so display error message
      QString sTemp, sMsg = szErr1;
      int iSize = (int) laSymbolsNotOverwritten.size();
      for (int i=0; i<iSize; i++)
      {  BEMPX_DBIDToDBCompParamString( laSymbolsNotOverwritten[i], sTemp );
         sMsg += QString( "     %2\n" ).arg( sTemp );
      }
      sMsg += szErr2;
      BEMMessageBox( sMsg, "", 2 /*warning*/ );
      return FALSE;
   }

   return TRUE;
}


// /////////////////////////////////////////////////////////////////////////////
// //
// // SymLstList Class Function:  Read()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads the symbol list definitions from a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CryptoFile& file : the binary encrypted ruleset file to read the symbol
// //                       list definitions from.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool SymLstList::Read( CryptoFile& file )
// {
//    int count = 0;
//    // read number of symbol list definitions stored in file
//    file.Read( &count, sizeof( int ) );
// 
//    // loop over each entry, creating a new SymLst, reading it and adding it to the list
//    for ( int i = 0; i < count; i++ )
//    {
//       SymLst* symlst = new SymLst;
//       symlst->Read( file );
//       push_back( symlst );
//    }
// 
//    // Post Symbol information to Building Database for access by user interface module
//    return PostSymbolsToDatabase();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // SymLstList Class Function:  Write()
// //
// // Purpose ------------------------------------------------------------------
// //   Writes the symbol list definitions to a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CryptoFile& file : the binary encrypted ruleset file to write the symbol
// //                       list definitions to.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool SymLstList::Write( CryptoFile& file )
// {
//    int count = (int) size();
//    // write the number of symbol list definitions
//    file.Write( &count, sizeof( int ) );
// 	for (i=0; i < iCount; i++)
// 	{	assert( m_symbolLists.at(i) );
// 		if (m_symbolLists.at(i))
// 			m_symbolLists.at(i)->Write( file );;
// 	}
// 
//    return TRUE;
// }
// 
