// textio.cpp - implementation of the CTextioException and CTextIO classes
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
#include "textio.h"
//#include "memLkRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Special characters
static const char Quote      = '\"';     // Used to delimit string data
static const char CommentChr = ';';      // Rest of line will be a comment
static const char SlashChr   = '/';      // SAC 6/21/12 - added to facilitate C-style comments => Rest of line will be a comment

static const char Delimiter_NonCSV  = ' ';      // Data delimiter
static const char Delimiter_CSV     = ',';      // SAC 10/9/05 - switched from space to comma


// Tests for legal character from character set for data type.
inline bool IsInt(char c)
{ return isdigit(c) || c =='-'; }

inline bool IsFloat(char c)
{ return isdigit(c) || c =='-' || c =='+' || c == '.' || c == 'e' || c=='E'; }

inline BOOL IsDelimiter(bool bIsCSV, char c)  // SAC 10/9/05
{ return ( (!bIsCSV && c == Delimiter_NonCSV) ||
           ( bIsCSV && c == Delimiter_CSV   ) ); }

inline char GetDelimiter(bool bIsCSV)  // SAC 10/14/05
{ return (bIsCSV ? Delimiter_CSV : Delimiter_NonCSV); }

inline BOOL IsAnySpecialChar(char c)
{ return (	c == Quote            ||
				c == CommentChr       ||
				c == SlashChr         ||
				c == Delimiter_NonCSV ||
				c == Delimiter_CSV    );
}

int IndexInStringArray( CStringArray& saStrings, CString& str )
{	for (int i=0; i < saStrings.GetSize(); i++)
	{	if (!saStrings[i].Compare( str ))
			return i;
	}
	return -1;
}

void TrimLeadingSpaces( CString& str )
{	int iStrLen = str.GetLength();
	int iNumSpcs = 0;
	while (iNumSpcs < iStrLen && isspace((unsigned char) str[iNumSpcs]))
		iNumSpcs++;
	if (iNumSpcs > 0 && iNumSpcs < iStrLen)
		str = str.Right( str.GetLength()-iNumSpcs );
}

bool IsAllSpaces( CString& str )
{	int iStrLen = str.GetLength();
	int idx = 0;
	while (idx < iStrLen && isspace((unsigned char) str[idx]))
		idx++;
	return (idx == iStrLen);
}


void OurThrowTextioExceptionOld(int cause, const char* fileName, UINT line, UINT column, const char* lastError/*=NULL*/)
{
   CTextioException* pException = new CTextioException(cause, fileName, line, column, lastError);
   TRACE1("%s\r\n", (const char*)pException->m_strError);
   THROW(pException);
}

ICTextIO* CreateCTextIO(const char* path, UINT nMode)
{
	return new CTextIO(path, nMode);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class CTextioException
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifdef COMPILE_BEMPROC
IMPLEMENT_DYNAMIC(CTextioException, CException)
#endif

/////////////////////////////////////////////////////////////////////////////
//
// CTextioException Class Function:  CTextioException()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initializes members and builds error string.
//   
// Arguments ----------------------------------------------------------------
//   int         cause    : value to init m_cause member to
//   const char* fileName : string to init m_fileName member to
//   UINT        line     : value to init m_line member to
//   UINT        column   : value to init m_column member to
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CTextioException::CTextioException(int cause, const char* fileName, UINT line, UINT column, const char* lastError/*=NULL*/)
   : m_cause(cause), m_fileName(fileName), m_line(line), m_column(column), m_strLastError(lastError), m_bNotified( FALSE)
{
   BuildErrorString();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextioException Class Function:  ~CTextioException()
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
CTextioException::~CTextioException()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextioException Class Function:  BuildErrorString()
//
// Purpose ------------------------------------------------------------------
//   Builds error string based on member variables and sets m_strError member.
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
void CTextioException::BuildErrorString()
{
   static const char BASED_CODE szXQuote[]          = "Expected Quote";
   static const char BASED_CODE szXInt[]            = "Expected Integer";
   static const char BASED_CODE szXFloat[]          = "Expected Floating Point Number";
   static const char BASED_CODE szEOF[]             = "Unexpected End Of File";
   static const char BASED_CODE szFormat[]          = "File Format Error";
   static const char BASED_CODE szBadPropType[]     = "Bad Property Type";
   static const char BASED_CODE szXEquals[]         = "Expected Equals Sign";
   static const char BASED_CODE szXOpenParen[]      = "Expected Open Parenthesis";
   static const char BASED_CODE szBadPropTypeType[] = "Bad Property Type Type";
   static const char BASED_CODE szXComma[]          = "Expected Comma";
   static const char BASED_CODE szXHeader[]         = "Expected New Record Header";
   
   static LPCSTR causes[] = { szXQuote, szXInt, szXFloat, szEOF, szFormat, szBadPropType,
                              szXEquals, szXOpenParen, szBadPropTypeType, szXComma, szXHeader };
   
   static const char BASED_CODE szMsg1[] = "Error Reading File\r\n%s\r\nLine Number: %d\r\nColumn Number: %d\r\n%s";
   
   CString msg;
   msg.Format( szMsg1, (const char*)m_fileName, m_line, m_column, causes[m_cause] );
   if (!m_strLastError.IsEmpty())
      msg += "\r\n" + m_strLastError;  
   m_strError = msg;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class CTextIO
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  CTextIO()
//
// Purpose ------------------------------------------------------------------
//   Constructor - initializes data members to zero
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
CTextIO::CTextIO()
{
	InitBufferAndCounters();
}

void CTextIO::InitBufferAndCounters()
{
   m_lineCount  = 0;
   m_buffer[0]  = '\0';
   m_chrIndex   = 0;
   m_lineLength = 0;
	m_bAtEOF = FALSE;  // SAC 6/21/12
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  CTextIO()
//
// Purpose ------------------------------------------------------------------
//   Constructor - calls Open() and throws an exception if an error occurs.
//   
// Arguments ----------------------------------------------------------------
//   const char* path  : path and filename of file to open
//   UINT        nMode : mode to open file in (read vs. write)
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CTextIO::CTextIO(const char* path, UINT nMode)
{
   CFileException e;
   if (!Open(path, nMode, &e))
      AfxThrowFileException(e.m_cause, e.m_lOsError);
	m_bAtEOF = FALSE;  // SAC 6/21/12
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Open()
//
// Purpose ------------------------------------------------------------------
//   Opens a file and initializes the various data members.
//   
// Arguments ----------------------------------------------------------------
//   const char*     path       : path and filename of file to open
//   UINT            nMode      : mode to open file in (read vs. write)
//   CFileException* pException : exception to throw in case of an error
//   
// Return Value -------------------------------------------------------------
//   Return value from call to CSdtioFile::Open().
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool CTextIO::Open(const char* path, UINT nMode, CFileException* pException)
{
   bool ok;
   if (nMode == CTextIO::load)
   {
      m_reading = TRUE;
      ok = (m_file.Open(path, CStdioFile::modeRead | CStdioFile::shareDenyWrite, pException) != 0);
   }
   else
   {
      m_reading = FALSE;
      ok = (m_file.Open(path, CStdioFile::modeCreate|CStdioFile::modeWrite, pException) != 0);
   }

   m_fileName   = path;      
   m_lineCount  = 0;
   m_buffer[0]  = '\0';
   m_chrIndex   = 0;
   m_lineLength = 0;

   m_bIsCSVFile = (m_fileName.Right(4).CompareNoCase( ".csv" ) == 0);   // SAC 10/14/05
	m_bAtEOF = FALSE;  // SAC 6/21/12
   
   return ok;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Abort()
//
// Purpose ------------------------------------------------------------------
//   Closes file for input or output without the possibility of an exception
//   being thrown or an assert failing (as with Close()).
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
void CTextIO::Abort()
{
   m_file.Abort();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Close()
//
// Purpose ------------------------------------------------------------------
//   Closes file for input or output.
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
void CTextIO::Close()
{
   m_file.Close();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  GetLineCount()
//
// Purpose ------------------------------------------------------------------
//   Returns the line number of the file currently being processed.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The value of the m_lineCount member variable.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
int CTextIO::GetLineCount()
{
   return m_lineCount;
}

int CTextIO::GetCharacterIndex()
{
   return m_chrIndex;
}

BOOL CTextIO::FoundInCurrentLine( const char* pszFindStr, int iMaxSearchLen /*=TextioMaxLineOld-1*/, BOOL bCaseSensitive /*=FALSE*/ )
{	static char szSrchIn[TextioMaxLineOld];
	static char szLocFindStr[TextioMaxLineOld];
	BOOL bRetVal = FALSE;
	if (pszFindStr == NULL || ((int) strlen(pszFindStr)) > iMaxSearchLen)
	{	ASSERT( FALSE );
		return FALSE;
	}
	strncpy_s( szSrchIn, TextioMaxLineOld, m_buffer, iMaxSearchLen );
	if (bCaseSensitive)
		return (strstr( szSrchIn, pszFindStr ) != NULL);
	else
	{	//return (strcasestr( szSrchIn, pszFindStr ) != NULL);
		if (strstr( szSrchIn, pszFindStr ) != NULL)
			return TRUE;
		else
		{	strcpy_s( szLocFindStr, TextioMaxLineOld, pszFindStr );
			_strlwr_s( szLocFindStr, strlen(szLocFindStr)+1 );
			_strlwr_s( szSrchIn    , strlen(szSrchIn    )+1 );
			bRetVal = (strstr( szSrchIn, szLocFindStr ) != NULL);
		}
	}
	return bRetVal;
}

const char* CTextIO::GetCurrentLine()
{	return m_buffer;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ThrowFormatException()
//
// Purpose ------------------------------------------------------------------
//   Throws a format-related file exception.
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
void CTextIO::ThrowFormatException(const char* lastError/*=NULL*/ )
{
   OurThrowTextioExceptionOld(CTextioException::badFormat, m_fileName, m_lineCount, m_chrIndex, lastError);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ThrowTextIOException()
//
// Purpose ------------------------------------------------------------------
//   Throws a file exception.
//   
// Arguments ----------------------------------------------------------------
//   int iCause  : The CTextioException::*** exception to throw
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::ThrowTextIOException( int iCause )
{
   OurThrowTextioExceptionOld(iCause, m_fileName, m_lineCount, m_chrIndex);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  String()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a string from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   CString& string     : reference to the string to either read or write
//   UINT     fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::String(CString& string, UINT fieldWidth)
{
   if (m_reading)
      string = ReadString();
   else
   {
      if (fieldWidth == DefStrLenOld)
         fieldWidth = string.GetLength()+2;
      WriteString(string, fieldWidth);
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Int()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes an integer from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   int& value      : reference to the integer to either read or write
//   UINT fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::Int(int& value, UINT fieldWidth)
{
   if (m_reading)
      value = (int)ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  UInt()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a UINT from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   UINT& value      : reference to the UINT to either read or write
//   UINT  fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::UInt(UINT& value, UINT fieldWidth)
{
   if (m_reading)
      value = (UINT)ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  LongInt()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a long int from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   long& value      : reference to the long int to either read or write
//   UINT  fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::LongInt(long& value,  UINT fieldWidth)
{
   if (m_reading)
      value = ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Float()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a float number from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   float& value      : reference to the float value to either read or write
//   UINT   fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::Float(float& value, UINT fieldWidth)
{
   if (m_reading)
      value = ReadFloat();
   else
      WriteFloat(value, fieldWidth);
}


void CTextIO::Double(double& value, UINT fieldWidth)
{
   if (m_reading)
      value = ReadDouble();
   else
      WriteDouble(value, fieldWidth);
}


BOOL StringExclusivelyNumber( CString& sPossibleNumber )
{	for (int i=0; i<sPossibleNumber.GetLength(); i++)
		if (!IsFloat(sPossibleNumber[i]) && sPossibleNumber[i] != ' ' && sPossibleNumber[i] != '\t' && sPossibleNumber[i] != '.')  // SAC 6/2/13 - added check for '.'
			return FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CRuleFile Class Function:  ReadArray()
//
/////////////////////////////////////////////////////////////////////////////
void CTextIO::ReadArray( CString& sId )
{  // read array index thru closing square bracket
   sId += '[';
   char ch = GetChr();
   while ( ch != ']' && !AtEOL() )
   {
      sId += ch;
      ch = GetChr();
   }
   if ( ch == ']' )
      sId += ch;
   else
      ; // TO DO: throw exception, missing ']'
}


/////////////////////////////////////////////////////////////////////////////
//
// CRuleFile Class Function:  ReadBEMProcParam()
//
// Purpose ------------------------------------------------------------------
//   Read building database parameter out of the file.
//   
// Arguments ----------------------------------------------------------------
//   CString& sId  : string to populate with database parameter read from file
//   BOOL bAllowLeadingDigit : 
//   
// Return Value -------------------------------------------------------------
//   1 if the token (parameter) is "DEFAULT" (used for DataType processing),
//   otherwise 0.
//   
// Notes --------------------------------------------------------------------
//   This string could be as simple as "token:token" or as complex as
//   "token:token[number]:token[number]:token[number]...".
//   This function was added to CTextIO 2/28/98 by SAC.
//   
/////////////////////////////////////////////////////////////////////////////
long CTextIO::ReadBEMProcParam( CString& sId, BOOL bAllowLeadingDigit )
{
   sId = ReadToken( bAllowLeadingDigit );  // reads string up to first ':'

   // return '1' if the token is "DEFAULT" (used in DataType processing)
   if ( sId.CompareNoCase( "DEFAULT" ) == 0 )
      return 1;

   char ch = GetChr();

   // SAC - 4/1/98 - added to handle params starting w/ param & not comp (i.e. 'Param[2]')
   if (ch == '[')
   {  // read array index thru closing square bracket
      ReadArray( sId );
      ch = GetChr();
   }

   // continue reading and appending to parameter string thru the last segment
   while ( ch == ':' )
   {
      sId += ":" + ReadToken( bAllowLeadingDigit );  // reads and appends the next portion of the parameter string
      ch = GetChr();

      while ( ch == ' ' )  // advance past spaces
         ch = GetChr();
      if ( ch == ',' || ch == '=' || ch == '<' || ch == '>' || ch == '!' )
      {  // ',' or '=' ends parameter string
         UnGetChr();
         return 0;
      }
      if ( ch == '[' )
      {  // read array index thru closing square bracket
         ReadArray( sId );
//         sId += ch;
//         ch = GetChr();
//         while ( ch != ']' && !AtEOL() )
//         {
//            sId += ch;
//            ch = GetChr();
//         }
//         if ( ch == ']' )
//            sId += ch;
//         else
//            ; // TO DO: throw exception, missing ']'

         // SAC - 4/23/97 - Added to handle Comp:Param[#]:Param[#]
         ch = GetChr();
      }
   //   ch = GetChr();
   }
   if ( ch == ',' )
      UnGetChr();

   return 0;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadBEMCondition()
//
/////////////////////////////////////////////////////////////////////////////
static char BASED_CODE szTDCC_Eq[]  = "=";
static char BASED_CODE szTDCC_LEq[] = "<=";
static char BASED_CODE szTDCC_GEq[] = ">=";
static char BASED_CODE szTDCC_L[]   = "<";
static char BASED_CODE szTDCC_G[]   = ">";
static char BASED_CODE szTDCC_NEq[] = "!=";
static const char* pszConds[] = { szTDCC_Eq, szTDCC_LEq, szTDCC_GEq, szTDCC_L, szTDCC_G, szTDCC_NEq, NULL };

int StrToBEMCondition( const char* pszCond )    // SAC 7/29/06 - added to facilitate parsing of string -> CCP Condition
{
   CString sCond = pszCond;
   int iCond=-1;
   while (pszConds[++iCond] != NULL)
   {
      if (sCond == pszConds[iCond])
         return iCond;
   }
   return iCond;
}

int TrimBEMCondition( CString& str )    // returns index of condition present at the BEGINNING of the string AND removes condition (and any following spaces) from the CString
{  int iRetVal = -1;
   int iCond=-1;
   while (pszConds[++iCond] != NULL && iRetVal < 0)
   {  if (str.Find( pszConds[iCond] ) == 0)
         iRetVal = iCond;
   }
	if (iRetVal >= 0)
	{	str = str.Right( str.GetLength() - strlen( pszConds[iRetVal] ) );
		str.TrimLeft();
	}
   return iRetVal;
}

int CTextIO::ReadBEMCondition()
{
   CString sToken;
   char ch;
   ch = GetChr();
   while ( ch == '=' || ch == '>' || ch == '<' || ch == '!' )
   {
      sToken += ch;
      ch = GetChr();
   }
//   file.UnGetChr();
//   PostReadToken( file );
   while ( ch == ' ' || ch == ',' )
      ch = GetChr();
   UnGetChr();

   return StrToBEMCondition( sToken );    // SAC 7/29/06 - added to facilitate parsing of string -> CCP Condition
//   int iCond=-1;
//   while (pszConds[++iCond] != NULL)
//   {
//      if (sToken == pszConds[iCond])
//         return iCond;
//   }
//   return iCond;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  YesNo()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a boolean value from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   bool& value  : reference to the bool to either read or write
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::YesNo(bool& value)
{
   if (m_reading)
   {
      CString input = ReadString();
      ASSERT(input.GetLength() == 1);
      value = input[0] == 'Y' || input[0] == 'y';
   }
   else
   {
      static const char BASED_CODE szYes[]  = "Y";
      static const char BASED_CODE szNo[]   = "N";
      static const int             fieldLen = 5;      // 3 chars + 2 spaces
      WriteString(value ? szYes : szNo, fieldLen);
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  NewLine()
//
// Purpose ------------------------------------------------------------------
//   Writes a newline to the file, but only if the file was opened for writing.
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
void CTextIO::NewLine()
{
   if (!m_reading)
      PutLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Comment()
//
// Purpose ------------------------------------------------------------------
//   Writes a comment to the file, but only if the file was opened for writing.
//   
// Arguments ----------------------------------------------------------------
//   const char* comment  : comment to write to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::Comment(const char* comment)
{
   if (!m_reading)
   {
      PutChr(CommentChr);

      while(*comment)
         PutChr(*comment++);
      
      NewLine();
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  CommentBlock()
//
// Purpose ------------------------------------------------------------------
//   Writes a comment block to the file, but only if the file was opened for writing.
//   
// Arguments ----------------------------------------------------------------
//   const char* comment  : comment block string to write to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::CommentBlock(const char* comment)
{
   if (!m_reading)
   {
      if (m_chrIndex != 0)
         NewLine();
         
      for (int x = 0; x < 79; x++)
         PutChr(CommentChr);
      NewLine();

      PutChr(CommentChr); 
      PutChr(CommentChr);
      PutChr(' ');
      while (*comment)
         PutChr(*comment++);

      NewLine();
      NewLine();
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadString()
//
// Purpose ------------------------------------------------------------------
//   Reads a character string from the file.  The character string must be
//   enclosed in double quotes.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The character string read from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CString CTextIO::ReadString( BOOL bReadPastEOL /*=FALSE*/ )
{
   Advance();

   char chr = GetChr();
   if (chr != Quote)
      OurThrowTextioExceptionOld(CTextioException::xQuote, m_fileName, m_lineCount, m_chrIndex);

   CString string;
   
   chr = GetChr();
//   while (chr != Quote && !AtEOL())
//   {
//      string += chr;
//      chr = GetChr();
//   }
   while (chr != Quote && (bReadPastEOL || !AtEOL()))  // SAC 6/17/01 - Added ability to read BEYOND EOLs
   {
      if (bReadPastEOL && AtEOL())
         string += '\n';
      else
         string += chr;
      chr = GetChr();
   }
   
   if (chr != Quote)
      OurThrowTextioExceptionOld(CTextioException::xQuote, m_fileName, m_lineCount, m_chrIndex);
      
   return string;   
}


/////////////////////////////////////////////////////////////////////////////
static inline CString ExtractLeadingToken( CString& str )
{
	CString sRetStr;
	int iStrLen = str.GetLength();
	int idx = 0;
	while (idx < iStrLen && isspace((unsigned char) str[idx]))
		idx++;
	if (idx < iStrLen && !isalpha((unsigned char) str[idx]))
	{	// assumption is that token always begins w/ an alphabetic character, so return an empty string if the first non-space char in this string is not alphabetic
	}
	else
	{	while (idx < iStrLen && (!isspace((unsigned char) str[idx]) && !IsAnySpecialChar(str[idx])))  // SAC 10/24/12 - added cast to unsigned char to prevent ASSERT in isctype.c ((unsigned)(c+1) <= 256)
		{	sRetStr += str[idx];
			idx++;
		}
	}
	return sRetStr;
}

CString CTextIO::ReadToNextToken( CStringArray& saTokens, BOOL bReadPastEOL /*=TURE*/ )
{
   CString string, sLine;
	while (!m_bAtEOF && (sLine.IsEmpty() || IsAllSpaces(sLine)))
		sLine = ReadLine( FALSE /*bAdvanceFirst*/ );

	if (!m_bAtEOF)
	{
		CString sTokenCheck = ExtractLeadingToken( sLine );			// NOTE - token expected to be the FIRST THING on the line
		int iTokenStrIdx = IndexInStringArray( saTokens, sTokenCheck );
		int iNumLines = 0;
		while (!m_bAtEOF && iTokenStrIdx < 0)
		{	string += sLine;
         string += '\n';
			iNumLines++;
			if (!bReadPastEOL)
				iTokenStrIdx = 100;
			else
			{	sLine = ReadLine( FALSE /*bAdvanceFirst*/ );
				sTokenCheck = ExtractLeadingToken( sLine );			// NOTE - token expected to be the FIRST THING on the line
				iTokenStrIdx = IndexInStringArray( saTokens, sTokenCheck );
			}
		}

		if (iNumLines == 1)	// if the return string contains only a single line of text, then trim leading spaces off
		{	TrimLeadingSpaces( string );
			ASSERT( !string.IsEmpty() );
			if (!string.IsEmpty())
				string = string.Left( string.GetLength()-1 );  // trim trailing '\n' added above
		}

		if (iTokenStrIdx >= 0 && (bReadPastEOL || iNumLines == 0))
		{	// this line of text begins w/ a token, so BACKUP to beginning of line before returning to calling routine
			int iLineLen = sLine.GetLength();
			for (int i=0; i<=iLineLen; i++)
				UnGetChr();
		}
	}
	return string;

//    u:ExteriorWallConstructType

//    IF AVERAGE(u:PolyLoop:CartesianPoint:Coordinate[3]) > -2 THEN   //average of the Z coordinate. Assumes 0.00 is at grade.
//      True
//    ELSE
//      False
//    ENDIF

//    IF IsOnGrade THEN
//      // For heated slab floors, the F-factor shall be no higher than 0.91 
//      // for climate zones 1-15 and 0.78 for climate zone 16.
//      IF u:ConsType=Heated THEN
//        IF u:proj:ClimateZone = 16 THEN
//          MIN(u:Ffactor,0.78)
//        ELSE
//          MIN(u:Ffactor,0.91)
//        ENDIF
//      ELSE
//        u:Ffactor
//      ENDIF
//    ELSE
//      u:Ffactor
//    ENDIF
}

/////////////////////////////////////////////////////////////////////////////
// Added new function to enable reading of strings that may or may NOT be quote delimited
// SAC 2/9/04 - Added new bSkipBlankEntries argument to prevent skipping of blank CSV file entries
// SAC 1/27/12 - added pbStrQuoted argument to pass back info re: whether or not the string is quoted
CString CTextIO::ReadCSVString( BOOL bReadToFollowingDelimeter /*=TRUE*/, BOOL bSkipBlankEntries /*=TRUE*/, BOOL* pbStrQuoted /*=NULL*/ )
{
   if (bSkipBlankEntries)  // don't advance if checking for blank CSV entries (could throw exception upon hitting EOL/EOF
      Advance();

   CString string;
   char chr = GetChr();

// SAC 2/9/04 - Added code to prevent skipping of blank CSV file entries
   if (!bSkipBlankEntries && (IsDelimiter(m_bIsCSVFile, chr) || AtEOL()))
      return string;   

	if (pbStrQuoted)  // SAC 1/27/12
		*pbStrQuoted = (chr == Quote);

   BOOL bEndWithQuote = (chr == Quote);
   if (!bEndWithQuote)
      string += chr;

   chr = GetChr();
   while (!AtEOL()  &&  (!bEndWithQuote || chr != Quote)  &&  (bEndWithQuote || !IsDelimiter(m_bIsCSVFile, chr)))
   {
      string += chr;
      chr = GetChr();
   }
   
   if (bEndWithQuote && bReadToFollowingDelimeter && !AtEOL() && !IsDelimiter(m_bIsCSVFile, chr))
   {
      do
         chr = GetChr();
      while(!IsDelimiter(m_bIsCSVFile, chr) && !AtEOL());
   }

   return string;   
}


int CTextIO::ParseCSVRecord( CStringArray& saCSVFields )  // SAC 2/29/12
{
	saCSVFields.RemoveAll();

   CString string;
   char chr = GetChr();
	BOOL bQuoteOpen=FALSE, bQuoteClosed=FALSE;
	while (!m_bAtEOF && !AtEOL())
	{
		if (chr == Quote)
		{	if (!bQuoteOpen)
			{	// at beginning of quoted field
				bQuoteOpen = TRUE;
				bQuoteClosed = FALSE;
				if (!string.IsEmpty())
				{	ASSERT( FALSE );		// string should be empty if/when we encounter an opening quote
					string.Empty();		// blast data loaded into string prior to encountering an opening quote ???
				}
			}
			else if (!bQuoteClosed)
			{	// at the end of quoted field
				bQuoteClosed = TRUE;
				saCSVFields.Add( string );
				string.Empty();
			}
			else
			{	ASSERT( FALSE );	// quote found after end of quoted field but before following delimiter!!!
			}
		}
   	else if (IsDelimiter(TRUE, chr))
		{	if (bQuoteOpen && !bQuoteClosed)
				string = string + chr;		// delimeter included in quoted string...
			else if (bQuoteOpen && bQuoteClosed)
			{	// string already added to arry (@ closing quote), so all we need do here is reset to the quote BOOLs
				bQuoteOpen   = FALSE;
				bQuoteClosed = FALSE;
			}
			else if (!bQuoteOpen && !bQuoteClosed)
			{	// add unquoted string to array
				saCSVFields.Add( string );
				string.Empty();
			}
			else
			{	ASSERT( FALSE );			// invalid condition where:  !bQuoteOpen && bQuoteClosed
			}
		}
		else if (bQuoteOpen && bQuoteClosed)
		{	ASSERT( chr == ' ' );		// allow for space chars to follow a quoted string (and preceding a delimeter or EOL)??
		}
		else
			string = string + chr;		// add character to string...
   
	   chr = GetChr();
	}

	if (!string.IsEmpty())	// add trailing field (numeric, not followed by comma)
		saCSVFields.Add( string );
	
	return (saCSVFields.GetSize() > 0 ? saCSVFields.GetSize() : (m_bAtEOF ? -1 : 0));
}


char* SubStr( const char *pszStr, int i0Start, int iNumChars )
{
	char* pcNew = new char[ iNumChars+1 ];
	strncpy_s( pcNew, iNumChars+1, pszStr + i0Start, iNumChars );
	pcNew[iNumChars] = '\0';
	return pcNew;
}

void ProcessStringForQuoteAndComment( CString& string )
{
	if (string[0] == '\"')
	{	string = string.Right( string.GetLength()-1 );
		// field quoted, so end string following closing quote
		if (string.Find('\"') > 0)
			string = string.Left( string.Find('\"') );
		else if (string.Find('\"') == 0)
			string.Empty();
		else
		{	ASSERT( FALSE );  // no closing quote ???
		}
	}
	else
	{	// field data is not quoted, so trim right and then see if there are any comments imbedded in the string
		string.TrimRight();
		if (string.Find(' ') > 0 || string.Find('\t') > 0)
		{	int iSpc = string.Find(' ');
			int iTab = string.Find('\t');
			int iPossibleFldEnd = ((iSpc > 0 && iTab > 0) ? std::min( iSpc, iTab) : (iSpc > 0 ? iSpc : iTab));
			int iCommentSemi = string.Find( CommentChr, iPossibleFldEnd+1 );
			int iCommentDbl  = string.Find( "//", iPossibleFldEnd+1 );
			int iCommentPart = string.Find( "/*", iPossibleFldEnd+1 );
			if (iCommentSemi > 0 || iCommentDbl > 0 || iCommentPart > 0)
			{	// Field includes comment
				//ASSERT( (i==iNumFields-1) );   // not sure if we should ALLOW comments overlapping in fields (except perhaps the final field in a row)
				int iTrimRight = (iCommentSemi > 0 ? iCommentSemi : string.GetLength());
				if (iCommentDbl > 0 && iCommentDbl < iTrimRight)
					iTrimRight = iCommentDbl;
				if (iCommentPart > 0 && iCommentPart < iTrimRight)
					iTrimRight = iCommentPart;
				string = string.Left( iTrimRight );
				string.TrimRight();  // re-trim, since field likely had spaces prior to comment
			}
		}
	}
}

int CTextIO::ParseColumnarRecord( CStringArray& saFields, std::vector<int>& ia0ColBegins, std::vector<int>& ia0ColEnds, const char* pszTerminate )
{
	saFields.RemoveAll();
   Advance();

	if (pszTerminate && strlen(pszTerminate) > 0 && FoundInCurrentLine( pszTerminate, ia0ColBegins[0]+strlen(pszTerminate)+1 ))
	{	//return 0;
   }
	else
	{	int iNumFields = ia0ColBegins.size();
		for (int i=0; i<iNumFields; i++)
		{	CString string;
			if ((int) strlen(m_buffer) > ia0ColBegins[i])
			{
				char* pSubStr = SubStr( m_buffer, ia0ColBegins[i], ia0ColEnds[i]-ia0ColBegins[i]+1 );
				string = pSubStr;
				string.TrimLeft();  // trims leading newline, space & tab chars
				if (!string.IsEmpty())
					ProcessStringForQuoteAndComment( string );
				if (pSubStr && strlen(pSubStr) > 0)
					delete [] pSubStr;
			}
			saFields.Add( string );
		}
	}
   	
	return (saFields.GetSize() > 0 ? saFields.GetSize() : (m_bAtEOF ? -1 : 0));
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadToken()
//
// Purpose ------------------------------------------------------------------
//   Reads a 'token' from the file.  Tokens are character strings that begin
//   with either a character or '_' and contain letters, underscores or
//   digits ('0'-'9').  Tokens should not be enclosed in double quotes and
//   cannot contain any spaces or other symbols not listed above.
//   
// Arguments ----------------------------------------------------------------
//   BOOL bAllowLeadingDigit
//   
// Return Value -------------------------------------------------------------
//   The character string which makes up the token read from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CString CTextIO::ReadToken( BOOL bAllowLeadingDigit, BOOL bSkipLeadingDelimeters /*=FALSE*/, BOOL bAllowMidHyphen /*=FALSE*/, BOOL bAllowNewLineRead /*=TRUE*/ )  // SAC 10/9/05		// SAC 9/11/14 - added bAllowNewLineRead arg
{
   CString string;
   Advance( bSkipLeadingDelimeters, bAllowNewLineRead );
	if (!m_bAtEOF && (bAllowNewLineRead || !AtEOL()))
	{
	   char chr = GetChr( bAllowNewLineRead );
		if (!m_bAtEOF && (bAllowNewLineRead || !AtEOL()))
		{
			if ( !( isalpha( chr ) || chr == '_' || chr == ':' || (bAllowLeadingDigit && isdigit( chr )) ) )
   		   OurThrowTextioExceptionOld(CTextioException::xQuote, m_fileName, m_lineCount, m_chrIndex);
   		
   		string += chr;
   		
   		chr = GetChr();
   		while (!m_bAtEOF && (__iscsym( chr ) || (bAllowMidHyphen && chr == '-')) && !AtEOL() )
   		{
   		   string += chr;
   		   chr = GetChr();
   		}
   	
			if (!m_bAtEOF)   	
		   	UnGetChr();
		}
	}
      
   return string;   
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  PostReadToken()
//
/////////////////////////////////////////////////////////////////////////////
void CTextIO::PostReadToken()
{
   char ch;
   do
      ch = GetChr();
   while ( ch == ' ' || ch == ',' ); 
   UnGetChr();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadLine()
//
// Purpose ------------------------------------------------------------------
//   Reads the next entire line of text from the file.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   a character string consisting of the entire line of text from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CString CTextIO::ReadLine( BOOL bAdvanceFirst /*=TRUE*/ )
{
   // Read whole line of text
   if (bAdvanceFirst)
		Advance();

   CString string;

   char chr = GetChr();
   while ( !AtEOL() )
   {
      string += chr;
      chr = GetChr();
   }
   
   return string;   
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadLong()
//
// Purpose ------------------------------------------------------------------
//   Reads the next long integer value from the file.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The value of the long integer read from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
long CTextIO::ReadLong()
{
   Advance();
   
   char chr = GetChr();
   if (!IsInt(chr))
      OurThrowTextioExceptionOld(CTextioException::xInt, m_fileName, m_lineCount, m_chrIndex);

   CString token;
   do
   {
      token += chr;
      chr = GetChr();
   }
   while(IsInt(chr));
   
   UnGetChr();
   
   return atol(token);
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  ReadFloat()
//
// Purpose ------------------------------------------------------------------
//   Reads the next float value from the file.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The value of the float read from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
double CTextIO::ReadDouble()
{
   Advance();
	if (m_bAtEOF)
	{	OurThrowTextioExceptionOld(CTextioException::xFloat, m_fileName, m_lineCount, m_chrIndex);
	   return -999;
	}

   char chr = GetChr();;
   if (!IsFloat(chr))
      OurThrowTextioExceptionOld(CTextioException::xFloat, m_fileName, m_lineCount, m_chrIndex);

   CString token;
   do
   {
      token += chr;
      chr = GetChr();
   }
   while(IsFloat(chr));
   
   UnGetChr();
   
   return atof(token);
}


float CTextIO::ReadFloat()
{
   return (float)ReadDouble();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  IgnoreRestOfLine()
//
/////////////////////////////////////////////////////////////////////////////
BOOL CTextIO::IgnoreRestOfLine( char chr )
{
	if (chr == CommentChr)
		return TRUE;
	else if (chr == SlashChr)
	{	chr = GetChr();
		if (chr == SlashChr)
		{	//UnGetChr();
			return TRUE;
		}
		else
			UnGetChr();
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  Advance()
//
// Purpose ------------------------------------------------------------------
//   Advances the file pointer beyond any white space or comments.
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
void CTextIO::Advance( BOOL bSkipLeadingDelimeters /*=FALSE*/, BOOL bAllowNewLineRead /*=TRUE*/ )  // SAC 10/9/05		// SAC 9/11/14 - added bAllowNewLineRead arg
{
   char chr;
	BOOL bSkippedToNextLine = FALSE;
   do
   {	
		bSkippedToNextLine = FALSE;

      chr = GetChr( bAllowNewLineRead );
      while (!m_bAtEOF && (isspace((unsigned char) chr) || (bSkipLeadingDelimeters && IsDelimiter(m_bIsCSVFile, chr))) && (bAllowNewLineRead || !AtEOL()))
         chr = GetChr( bAllowNewLineRead );

		if (m_bAtEOF || (!bAllowNewLineRead && AtEOL()))
		{
		}
// SAC 10/21/05 - Added new code to enable comment cells to be enclosed in double quotes => '";' would trigger comment in addition to simply ';'
      else if (chr == Quote)
      {
         chr = GetChr( bAllowNewLineRead );
         //if (chr == CommentChr)
      	if (IgnoreRestOfLine(chr))  // SAC 6/21/12
         {
            SkipToEndOfLine();
            GetLine();										ASSERT( bAllowNewLineRead );
				bSkippedToNextLine = TRUE;
         }
         else
         {
            UnGetChr();
            UnGetChr();
         }
      }
      //else if (chr == CommentChr)
      else if (IgnoreRestOfLine(chr))  // SAC 6/21/12
      {
         SkipToEndOfLine();  // SAC 6/15/05
         GetLine();											ASSERT( bAllowNewLineRead );
			bSkippedToNextLine = TRUE;
      }
      else
         UnGetChr();

//	   while (AtEOL())  // SAC 6/21/12 - skip past blank lines
//	      GetLine();
   }
   //while (chr == CommentChr);
   while (!m_bAtEOF && (bSkippedToNextLine || IgnoreRestOfLine(chr)) && (bAllowNewLineRead || !AtEOL()));  // SAC 6/21/12
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  GetChr()
//
// Purpose ------------------------------------------------------------------
//   Reads the next character from the file.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The character read from the file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
char CTextIO::GetChr( BOOL bAllowNewLineRead /*=TRUE*/ )		// SAC 9/11/14 - added bAllowNewLineRead arg
{
	if (!bAllowNewLineRead && !m_bAtEOF && AtEOL())
	{	// do nothing (prevent calling GetLine())
	   return m_buffer[m_chrIndex];
	}
	else
   {	while (!m_bAtEOF && AtEOL())
   	   GetLine();
	   return m_buffer[m_chrIndex++];
	}
}

// SAC 1/27/12 - routine to return next NON-WHITE SPACE character on the current line
char CTextIO::NextCharacterOnLine()   
{
	char cRet = '\0';
	int iCharsRead = 0;
   //while (!AtEOL() && cRet != CommentChr)
   while (!AtEOL() && !IgnoreRestOfLine(cRet))  // SAC 6/21/12
	{	iCharsRead++;
		cRet = GetChr();
		if (cRet != ' ' && cRet != '\t')
			break;
	}
	for (int i=0; i<iCharsRead; i++)
		UnGetChr();
	return cRet;
}

/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  UnGetChr()
//
// Purpose ------------------------------------------------------------------
//   decrements the m_chrIndex which effectively moves the file pointer back
//   in the file by one character.
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
void CTextIO::UnGetChr()
{
   if (m_chrIndex > 0)
      m_chrIndex--;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  GetLine()
//
// Purpose ------------------------------------------------------------------
//   Reads an entire line of text from the file, stores the text in m_buffer
//   and initializes the other member variables.
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
void CTextIO::GetLine()
{
   LPTSTR pReadRet = m_file.ReadString(m_buffer, TextioMaxLineOld);
   m_lineLength = (UINT) strlen(m_buffer);
   
   // If m_buffer is empty, we tried to read past the end of the file
   if (m_lineLength == 0 || pReadRet == NULL)
      //OurThrowTextioExceptionOld(CTextioException::endOfFile, m_fileName, m_lineCount, m_chrIndex);
		m_bAtEOF = TRUE;  // SAC 6/21/12

   m_chrIndex = 0;
   m_lineCount++;
}


void CTextIO::SkipToBeginningOfLine()	// SAC 10/19/12
{
   m_chrIndex = 0;
}

// SAC 6/15/05 - added new routine to enable comment lines that exceed TextioMaxLineOld in length
void CTextIO::SkipToEndOfLine()
{
   while (m_lineLength == TextioMaxLineOld-1  &&  m_buffer[m_lineLength-1] != 10)
   {
      m_chrIndex += m_lineLength;
      LPTSTR pReadRet = m_file.ReadString(m_buffer, TextioMaxLineOld);
      m_lineLength = (UINT) strlen(m_buffer);
   
      // If m_buffer is empty, we tried to read past the end of the file
      if (m_lineLength == 0 || pReadRet == NULL)
         OurThrowTextioExceptionOld(CTextioException::endOfFile, m_fileName, m_lineCount, m_chrIndex);
   }
}


// SAC 10/12/12 - added new routine to jump back to beginning of file, for iterative reading routines
void CTextIO::SkipToBeginningOfFile()
{
	m_file.SeekToBegin();
	InitBufferAndCounters();  // re-initialize buffer & line/character counters
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  WriteToken()
//
// Purpose ------------------------------------------------------------------
//   Writes a token value out to the file.  Tokens are character strings that
//   begin with either a character or '_' and contain letters, underscores or
//   digits ('0'-'9').  Tokens should not be enclosed in double quotes and
//   cannot contain any spaces or other symbols not listed above.
//   
// Arguments ----------------------------------------------------------------
//   const char* string     : token string to write to the file.
//   UINT        fieldWidth : width of field in which to write the token string
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::WriteToken(const char* string, UINT fieldWidth)
{
// SAC 4/21/00 - Added if statement to ensure fieldWidth > 0
   if (fieldWidth > 0)
   {
      if(fieldWidth > TextioMaxLineOld-1) 
         fieldWidth = TextioMaxLineOld-1;

      char format[16];
      sprintf(format, "%%-.%ds", fieldWidth);
//      sprintf(format, "%%-.%ds", fieldWidth-2);
   
      char line[TextioMaxLineOld+1];
      sprintf(line, format, string);

      if (fieldWidth + m_chrIndex >= TextioMaxLineOld)
         NewLine();

	  UINT i=0;
      for (; line[i] != '\0'; i++)
         PutChr(line[i]);

      for (; i < fieldWidth-1; i++)
         PutChr(' ');

//      PutDelimiter();
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  WriteString()
//
// Purpose ------------------------------------------------------------------
//   Writes a character string to the file, followed by a delimiter.
//   The fieldWidth includes space for the starting and ending double quote marks.
//   
// Arguments ----------------------------------------------------------------
//   const char* string     : the string to write to the file
//   UINT        fieldWidth : width of field in which to write the string
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::WriteString(const char* string, UINT fieldWidth)
{
   if(fieldWidth > TextioMaxLineOld-1) 
      fieldWidth = TextioMaxLineOld-1;

   char format[16];
   sprintf(format, "%%-.%ds", fieldWidth-2);
   
   char line[TextioMaxLineOld+1];
   sprintf(line, format, string);

   if (fieldWidth + m_chrIndex >= TextioMaxLineOld)
      NewLine();

   PutChr(Quote);
   UINT i=0;
   for (; line[i] != '\0'; i++)
      PutChr(line[i]);
   PutChr(Quote);

   for (; i < fieldWidth-1; i++)
      PutChr(' ');

   PutDelimiter();
}


void CTextIO::WriteWholeRecord(const char *string)   // SAC 10/10/05 - added to facilitate output of entire lines to CSV file (with line counting)
{
   m_file.WriteString( string );
   PutLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  WriteQuotedString()
//
// Purpose ------------------------------------------------------------------
//   Writes a character string to the file, followed by a delimiter.
//   The fieldWidth is the maximum width of the string itself and DOES NOT
//   include space for the starting and ending double quote marks.
//   
// Arguments ----------------------------------------------------------------
//   const char* string     : the string to write to the file
//   UINT        fieldWidth : width of field in which to write the string
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::WriteQuotedString(const char *string, UINT fieldWidth)
{
   if(fieldWidth > TextioMaxLineOld-1) 
      fieldWidth = TextioMaxLineOld-1;

   char format[16];
   sprintf(format, "%%-.%ds", fieldWidth);
   
   char line[TextioMaxLineOld+1];
   sprintf(line, format, string);

   if (fieldWidth + m_chrIndex >= TextioMaxLineOld)
      NewLine();

   PutChr(Quote);
   UINT i=0;
   for (; line[i] != '\0'; i++)
      PutChr(line[i]);
   PutChr(Quote);

   for (; i <= fieldWidth; i++)
      PutChr(' ');

   PutDelimiter();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  WriteLong()
//
// Purpose ------------------------------------------------------------------
//   Write a long integer value to the file, followed by a delimiter.
//   
// Arguments ----------------------------------------------------------------
//   long value      : the long integer to write to the file
//   UINT fieldWidth : width of field in which to write the long integer
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::WriteLong(long value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dld", fieldWidth);
   
   char string[TextioMaxLineOld+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if(fieldWidth + m_chrIndex >= TextioMaxLineOld)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++ )
      PutChr(string[i]);

   PutDelimiter();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  WriteFloat()
//
// Purpose ------------------------------------------------------------------
//   Write a floating point number to the file, followed by a delimiter.
//   
// Arguments ----------------------------------------------------------------
//   float value      : the float to write to the file
//   UINT  fieldWidth : width of field in which to write the float value
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::WriteFloat(float value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dg", fieldWidth);
   
   char string[TextioMaxLineOld+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if (fieldWidth + m_chrIndex >= TextioMaxLineOld)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++)
      PutChr(string[i]);

   PutDelimiter();
}


void CTextIO::WriteDouble(double value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dg", fieldWidth);
   
   char string[TextioMaxLineOld+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if (fieldWidth + m_chrIndex >= TextioMaxLineOld)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++)
      PutChr(string[i]);

   PutDelimiter();
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  PutChr()
//
// Purpose ------------------------------------------------------------------
//   Writes a single character to the file and incraments the chrIndex member.
//   
// Arguments ----------------------------------------------------------------
//   char chr  : the character to write to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CTextIO::PutChr(char chr)
{
   m_file.Write(&chr, 1);
   m_chrIndex++;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  PutLine()
//
// Purpose ------------------------------------------------------------------
//   Writes a newline character to the file, then initializes m_chrIndex and
//   incraments m_lineCount.
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
void CTextIO::PutLine()
{
   char nl = '\n';
   
   m_file.Write(&nl, 1);
   m_chrIndex = 0;
   m_lineCount++;
}


/////////////////////////////////////////////////////////////////////////////
//
// CTextIO Class Function:  PutDelimiter()
//
// Purpose ------------------------------------------------------------------
//   Writes a delimiter to the file (typically ',').
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
void CTextIO::PutDelimiter()
{
//   PutChr(Delimiter);
   PutChr( GetDelimiter( m_bIsCSVFile ) );  // SAC 10/14/05
}

