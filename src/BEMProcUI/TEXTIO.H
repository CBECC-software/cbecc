// textio.h - header file for CTextException and CTextIO class definitions
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

#ifndef TEXTIO_H
#define TEXTIO_H

#ifdef COMPILE_BEMPROC
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

extern int  StrToBEMCondition( const char* pszCond );    // SAC 7/29/06 - added to facilitate parsing of string -> CCP Condition
extern int  TrimBEMCondition( CStringA& str );    // returns index of condition present at the BEGINNING of the string AND removes condition (and any following spaces) from the CString
extern BOOL StringExclusivelyNumber( CStringA& sPossibleNumber );
extern void ProcessStringForQuoteAndComment( CStringA& string );
extern int  IndexInStringArray( CStringArray& saStrings, CStringA& str );
extern void TrimLeadingSpaces( CStringA& str );

/////////////////////////////////////////////////////////////////////////////
// TEXTIO - Text Based I/O support

// Classes declared in this file

//CException
   class CTextioException;    // i/o error

// Non CObject classes
   class CTextIO;             // Buffered Text File

/////////////////////////////////////////////////////////////////////////////

// Maximum length of data lines used by textio module.  Additional 
// characters after maximum length are ignored.
const int TextioMaxLineOld = 2047;   // SAC 10/20/05 - increased from 1024 -> 2047  -  SAC 8/14/03 - upped limit from 512 to 1024   // 132;

const UINT DefIntLenOld   = 8;
const UINT DefFloatLenOld = 9;
const UINT DefStrLenOld   = 0;        // Use string length by default

/////////////////////////////////////////////////////////////////////////////
//	CTextioException
//    An instance of this class is created each time a CTextIO file exception
//    is thrown.  This exception helps identify CTextIO I/O errors.
/////////////////////////////////////////////////////////////////////////////

class CTextioException : public CException
{
#ifdef COMPILE_BEMPROC
   DECLARE_DYNAMIC(CTextioException)
#endif
// Attributes
public:
   // Exception Causes
   enum { xQuote, xInt, xFloat, endOfFile, badFormat, badPropType, xEquals, xOpenParen,
          badPropTypeType, xComma, xHeader };
   
   int      m_cause;        // cause identifier
   CStringA  m_fileName;    // filename whose I/O caused the exception to be thrown
   UINT     m_line;         // line number error occurred at
   UINT     m_column;       // column of line which error occurred at
   CStringA m_strLastError; // context sensitive error message
   CStringA  m_strError;    // error message
   BOOL m_bNotified;        // indicates if already notified (i.e. message box) to prevent duplicate notification

// Implementation (use OurThrowTextioExceptionOld to create)
public:
   CTextioException(int cause, const char* fileName, UINT line, UINT column, const char* lastError=NULL);

   void BuildErrorString();
   virtual ~CTextioException();
};

void OurThrowTextioExceptionOld(int cause, const char* fileName, UINT line, UINT column, const char* lastError=NULL);

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/////////////////////////////////////////////////////////////////////////////
//	CTextIO
//    An instance of this class is created for each text file which is read
//    and/or written.  This class helps automate many of the I/O functionality
//    we utilize throughout our text file processing.
/////////////////////////////////////////////////////////////////////////////

class ICTextIO
{
public:
	virtual void Close() = 0;
	virtual int ParseCSVRecord( CStringArray& saCSVFields ) = 0;
};

class DLLAPI CTextIO : public ICTextIO
{
public:
   // Open Modes
   enum { store, load, readWrite };
   
   CTextIO();
   CTextIO(const char* path, UINT nMode);
	void InitBufferAndCounters();  // enable initialization of buffer & line/character counters upon construction & jump back to file beginning
   
// Attributes
   bool           IsLoading() const;
   bool           IsStoring() const;
   const CStringA& FileName() const;
   
   bool Open(const char* path, UINT nMode, CFileException* pError = NULL);
   
   void Abort();
   void Close();
   int GetLineCount();
   int GetCharacterIndex();
	BOOL FoundInCurrentLine( const char* pszFindStr, int iMaxSearchLen=TextioMaxLineOld-1, BOOL bCaseSensitive=FALSE );
	const char* GetCurrentLine();
   void ThrowFormatException(const char* lastError=NULL );
   void ThrowTextIOException( int iCause );

public:   
   // insertion operations
   CTextIO& operator<<(const  CStringA& s);
   CTextIO& operator<<(int    i);
   CTextIO& operator<<(UINT   u);
   CTextIO& operator<<(long   l);
   CTextIO& operator<<(float  d);
   CTextIO& operator<<(double d);

   // extraction operations
   CTextIO& operator>>(CStringA& s);
   CTextIO& operator>>(int&     i);
   CTextIO& operator>>(UINT&    u);
   CTextIO& operator>>(long&    l);
   CTextIO& operator>>(float&   d);
   CTextIO& operator>>(double&  d);

   void String(  CStringA& string, UINT fieldWidth = DefStrLenOld);
   void Int(     int&     value,  UINT fieldWidth = DefIntLenOld);
   void UInt(    UINT&    value,  UINT fieldWidth = DefIntLenOld);
   void LongInt( long&    value,  UINT fieldWidth = DefIntLenOld);
   void Float(   float&   value,  UINT fieldWidth = DefFloatLenOld);
   void Double(  double&  value,  UINT fieldWidth = DefFloatLenOld);
   void YesNo(   bool&    value);
   
   void NewLine();
   void Comment(const char* string);
   void CommentBlock(const char* string);

// implementation   
protected:
   // CTextIO objects cannot be copied or assigned
   CTextIO(const CTextIO& file);
   void operator=(const CTextIO& file);

public:
   // Test for end of line condition
   bool AtEOL();

   CStringA ReadString( BOOL bReadPastEOL=FALSE );
   CStringA ReadToNextToken( CStringArray& saTokens, BOOL bReadPastEOL=TRUE );
   CStringA ReadToken( BOOL bAllowLeadingDigit=FALSE, BOOL bSkipLeadingDelimeters=FALSE, BOOL bAllowMidHyphen=FALSE, BOOL bAllowNewLineRead=TRUE );		// SAC 9/11/14 - added bAllowNewLineRead arg
   CStringA ReadLine( BOOL bAdvanceFirst = TRUE );
   long    ReadLong();
   float   ReadFloat();
   double  ReadDouble();
   void    ReadArray( CStringA& sId );
   long    ReadBEMProcParam( CStringA& sId, BOOL bAllowLeadingDigit=FALSE );
   int     ReadBEMCondition();
	// Added new function to enable reading of strings that may or may NOT be quote delimited
   CStringA ReadCSVString( BOOL bReadToFollowingDelimeter = TRUE, BOOL bSkipBlankEntries = TRUE, BOOL* pbStrQuoted = NULL );  // SAC 1/27/12
   int  ParseCSVRecord( CStringArray& saCSVFields );  // SAC 2/29/12
   int  ParseColumnarRecord( CStringArray& saFields, std::vector<int>& ia0ColBegins, std::vector<int>& ia0ColEnds, const char* pszTerminate );

   void PostReadToken();

	BOOL IgnoreRestOfLine( char chr );
   void Advance( BOOL bSkipLeadingDelimeters=FALSE, BOOL bAllowNewLineRead=TRUE );		// SAC 9/11/14 - added bAllowNewLineRead arg
   char GetChr( BOOL bAllowNewLineRead=TRUE );		// SAC 9/11/14 - added bAllowNewLineRead arg
	char NextCharacterOnLine();   // SAC 1/27/12 - routine to return next NON-WHITE SPACE character on the current line
   void UnGetChr();
   void GetLine();
	void SkipToBeginningOfLine();	// SAC 10/19/12
   void SkipToEndOfLine();   // SAC 6/15/05 - added new routine to enable comment lines that exceed TextioMaxLineOld in length
   void SkipToBeginningOfFile();   // SAC 10/12/12 - added new routine to jump back to beginning of file, for iterative reading routines

   void WriteToken(const char *string, UINT fieldWidth);
   void WriteString(const char *string, UINT fieldWidth);
   void WriteQuotedString(const char *string, UINT fieldWidth);
   void WriteLong(long value, UINT fieldWidth);
   void WriteFloat(float value, UINT fieldWidth);
   void WriteDouble(double value, UINT fieldWidth);
   void WriteWholeRecord(const char *string);   // SAC 10/10/05 - added to facilitate output of entire lines to CSV file (with line counting)

   void PutChr(char chr);
   void PutLine();
   void PutDelimiter();

   void Flush();
   
private:   
   CStdioFile  m_file;                     // the file itself (CStdioFile)
   CStringA    m_fileName;                 // the path/filename of the file
   bool        m_reading;                  // flag indicating whether we are reading or writing the file
   UINT        m_lineCount;                // current line being processed
   char        m_buffer[TextioMaxLineOld+1];  // buffer to store the current line's text
   UINT        m_chrIndex;                 // index of current character in m_buffer
   UINT        m_lineLength;               // length of current line stored in m_buffer

   bool        m_bIsCSVFile;   // SAC 10/14/05
	bool			m_bAtEOF;  // SAC 6/21/12
};

DLLAPI ICTextIO* __cdecl CreateCTextIO(const char* path, UINT nMode);

#ifdef __cplusplus
}
#endif

// inline functions
inline bool CTextIO::IsLoading() const
{ return m_reading; }

inline bool CTextIO::IsStoring() const
{ return !m_reading; }

inline const CStringA& CTextIO::FileName() const
{ return m_fileName; }
   
inline CTextIO& CTextIO::operator<<(const CStringA& s)
{ WriteString(s, s.GetLength()+2); return *this; }

inline CTextIO& CTextIO::operator<<(int i)
{ WriteLong(i, DefIntLenOld); return *this; }

inline CTextIO& CTextIO::operator<<(UINT u)
{ WriteLong(u, DefIntLenOld); return *this; }

inline CTextIO& CTextIO::operator<<(long l)
{ WriteLong(l, DefIntLenOld); return *this; }

inline CTextIO& CTextIO::operator<<(float d)
{ WriteFloat(d, DefFloatLenOld); return *this; }

inline CTextIO& CTextIO::operator<<(double d)
{ WriteDouble(d, DefFloatLenOld); return *this; }

inline CTextIO& CTextIO::operator>>(CStringA& s)
{ s = ReadString(); return *this; }

inline CTextIO& CTextIO::operator>>(int& i)
{ i = (int)ReadLong(); return *this; }

inline CTextIO& CTextIO::operator>>(UINT& u)
{ u = (UINT)ReadLong(); return *this; }

inline CTextIO& CTextIO::operator>>(long& l)
{ l = ReadLong(); return *this; }

inline CTextIO& CTextIO::operator>>(float& d)
{ d = ReadFloat(); return *this; }

inline CTextIO& CTextIO::operator>>(double& d)
{ d = ReadDouble(); return *this; }

inline bool CTextIO::AtEOL()
{ return m_chrIndex >= m_lineLength; }

inline void CTextIO::Flush()
{ m_file.Flush();  return; }

/////////////////////////////////////////////////////////////////////////////

#undef DLLAPI

#endif   // TEXTIO_H

