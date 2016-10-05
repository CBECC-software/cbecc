// crypfile.cpp - implementation of the CryptoFile class
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
#include "expCrypFile.h"
#include "memLkRpt.h"


static const int MAX_CRYPTOFILE_BUFSIZE = 1024;


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  CryptoFile()
//
// Purpose ------------------------------------------------------------------
//   Cosntructor - calls base class QFile constructor.
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
CryptoFile::CryptoFile() : QFile()
{
   m_lByteCount = 0;
}


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  CryptoFile()
//
// Purpose ------------------------------------------------------------------
//   Constructor - calls base class QFile constructor which opens the specified
//   file in the specified mode.
//   
// Arguments ----------------------------------------------------------------
//   const char* pszFileName : path/filename of the file to open
//   UINT        nOpenFlags  : mode in which to open the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CryptoFile::CryptoFile(const char* pszFileName) : QFile(pszFileName)
{
   m_lByteCount = 0;
}


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a set number of bytes from the file, decrypting each as we go.
//   
// Arguments ----------------------------------------------------------------
//   void* lpBuf  : buffer to store the read bytes in
//   UINT  nCount : number of bytes to read from file
//   
// Return Value -------------------------------------------------------------
//   the number of bytes read from the file and decrypted.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
UINT CryptoFile::Read( void* lpBuf, UINT nCount )
{
   UINT nRead = (UINT) QIODevice::read( (char*) lpBuf, nCount );

   m_lByteCount += nCount;

   return nRead;
}


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Encrypt and write a series of bytes to the file.
//   
// Arguments ----------------------------------------------------------------
//   const void* lpBuf  : buffer containing bytes to write to file
//   UINT        nCount : number of bytes to write to file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CryptoFile::Write( const void* lpBuf, UINT nCount )
{
   static unsigned char buffer[ MAX_CRYPTOFILE_BUFSIZE ];

   UINT start = 0;
   // loop over all bytes in buffer to be written to file (in chunks of MAX_CRYPTOFILE_BUFSIZE)
   while ( start < nCount )
   {
      const unsigned char* temp = &((const unsigned char*)lpBuf)[ start ];
      UINT end = ( nCount - start ) < MAX_CRYPTOFILE_BUFSIZE ? 
                   nCount - start : MAX_CRYPTOFILE_BUFSIZE;

      for ( UINT i = 0; i < end; i++ )
         buffer[ i ] = temp[ i ];
      // write encrypted bytes to the file
      QFile::write( (const char*) buffer, end );
      m_lByteCount += end;
      start += MAX_CRYPTOFILE_BUFSIZE;
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  WriteCString()
//
// Purpose ------------------------------------------------------------------
//   Encrypt and write a CString to the file.
//   
// Arguments ----------------------------------------------------------------
//   const CString& string  : string to be encrypted and written to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CryptoFile::WriteQString( const QString& string )
{
   int length = string.size();
	const QByteArray local8Str = string.toLocal8Bit();
   CryptoFile::Write( &length, sizeof(int) );
   CryptoFile::Write( local8Str.constData(), local8Str.size() );
//   m_lByteCount += (length + sizeof(int)); - SAC 9/3/16 - removed since it double-counts string writing (m_lByteCount incremented inside CryptoFile::Write())
}


/////////////////////////////////////////////////////////////////////////////
//
// CryptoFile Class Function:  ReadCString()
//
// Purpose ------------------------------------------------------------------
//   read and decode a CString from the file.
//   
// Arguments ----------------------------------------------------------------
//   CString& string  : reference to string to read and decode from the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CryptoFile::ReadQString( QString& string )
{
   static char readBuf[ MAX_CRYPTOFILE_BUFSIZE ];
   int length;
   CryptoFile::Read( &length, sizeof(int) );

//			assert( length < MAX_CRYPTOFILE_BUFSIZE );
//   int iToRdLen = (length < MAX_CRYPTOFILE_BUFSIZE ? length : MAX_CRYPTOFILE_BUFSIZE-1 );
//   int iRdLen = CryptoFile::Read( readBuf, iToRdLen );			assert( iRdLen == iToRdLen );
//   readBuf[ iRdLen ] = '\0';
//   string = readBuf;
// SAC 9/23/16 - replaced above w/ below to read strings > MAX_CRYPTOFILE_BUFSIZE
	string.clear();
	int iToRdLen, iRdLen;
	do
	{
		iToRdLen = (length < MAX_CRYPTOFILE_BUFSIZE ? length : MAX_CRYPTOFILE_BUFSIZE-1 );
	   iRdLen = CryptoFile::Read( readBuf, iToRdLen );			assert( iRdLen == iToRdLen );
	   readBuf[ iRdLen ] = '\0';
	//   string += readBuf;
	   string += QString::fromLatin1( readBuf );	// SAC 9/29/16 - modified to preserve special characters like '°' & '²'
	   length -= (MAX_CRYPTOFILE_BUFSIZE-1);
	} while (length > 0);

//   m_lByteCount += (iRdLen + sizeof(int));  - SAC 9/3/16 - removed since it double-counts string reading (m_lByteCount incremented inside CryptoFile::Read())
}
