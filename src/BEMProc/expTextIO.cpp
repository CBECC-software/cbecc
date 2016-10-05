// TextIO.cpp - implementation of the TextioException and TextIO classes
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
#include "expTextIO.h"
#include "memLkRpt.h"


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
inline bool IsFloat(QChar c)
{ return c.isDigit() || c =='-' || c =='+' || c == '.' || c == 'e' || c=='E'; }

inline BOOL IsDelimiter(bool bIsCSV, char c)  // SAC 10/9/05
{ return ( (!bIsCSV && c == Delimiter_NonCSV) ||
           ( bIsCSV && c == Delimiter_CSV   ) ); }

inline char GetDelimiter(bool bIsCSV)  // SAC 10/14/05
{ return (bIsCSV ? Delimiter_CSV : Delimiter_NonCSV); }

inline BOOL IsAnySpecialChar(QChar c)
{ return (	c == Quote            ||
				c == CommentChr       ||
				c == SlashChr         ||
				c == Delimiter_NonCSV ||
				c == Delimiter_CSV    );
}

int IndexInStringArray( QStringList& saStrings, QString& str )
{	for (int i=0; i < saStrings.size(); i++)
	{	if (!saStrings[i].compare( str ))
			return i;
	}
	return -1;
}

void TrimLeadingSpaces( QString& str )
{	int iStrLen = str.length();
	int iNumSpcs = 0;
	while (iNumSpcs < iStrLen && isspace( str[iNumSpcs].unicode() ))
		iNumSpcs++;
	if (iNumSpcs > 0 && iNumSpcs < iStrLen)
		str = str.right( str.length()-iNumSpcs );
}

bool IsAllSpaces( QString& str )
{	int iStrLen = str.length();
	int idx = 0;
	while (idx < iStrLen && isspace( str[idx].unicode() ))
		idx++;
	return (idx == iStrLen);
}

void TrimLeft(  QString& str, QString sRemove )		// SAC 5/4/16
{	if (str.isEmpty())
		return;
	if (sRemove.length() < 1)
		sRemove = " \n\t";
	int idx=0;
	while (idx < str.length() && sRemove.indexOf( str.at(idx) ) >= 0)
		idx++;
	if (idx == 0)
	{ }
	else if (idx == str.length())
		str.clear();
	else if (idx > 0)
		str = str.right( str.length()-idx );
}

void TrimRight( QString& str, QString sRemove )		// SAC 5/4/16
{	if (str.isEmpty())
		return;
	if (sRemove.length() < 1)
		sRemove = " \n\t";
	int idx = str.length()-1;
	while (idx >= 0 && sRemove.indexOf( str.at(idx) ) >= 0)
		idx--;
	if (idx == str.length()-1)
	{ }
	else if (idx < 0)
		str.clear();
	else if (idx > 0)
		str = str.left( idx+1 );
}


void OurThrowTextioException(int cause, const char* fileName, UINT line, UINT column, const char* lastError/*=NULL*/)
{
   throw BEMTextioException(cause, fileName, line, column, lastError);
//   BEMTextioException* pException = new BEMTextioException(cause, fileName, line, column, lastError);
//   TRACE1("%s\n", (const char*)pException->m_strErr---or);
//   THROW(pException);
}

IBEMTextIO* CreateBEMTextIO(const char* path, UINT nMode)
{
	return new BEMTextIO(path, nMode);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMTextioException
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifdef COMPILE_BEMPROC
IMPLEMENT_DYNAMIC(BEMTextioException, CException)
#endif

/////////////////////////////////////////////////////////////////////////////
//
// BEMTextioException Class Function:  BEMTextioException()
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
BEMTextioException::BEMTextioException(int cause, const char* fileName, UINT line, UINT column, const char* lastError/*=NULL*/)
		: std::runtime_error( "file read error" )
//   : m_cause(cause), m_fileName(fileName), m_line(line), m_column(column), m_strLastError(lastError), m_bNotified( FALSE)
{
   m_cause = cause;
   m_fileName = fileName;
   m_line = line;
   m_column = column;
   m_strLastError = lastError;
   m_bNotified = FALSE;
   BuildErrorString();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextioException Class Function:  ~BEMTextioException()
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
BEMTextioException::~BEMTextioException()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextioException Class Function:  BuildErrorString()
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
void BEMTextioException::BuildErrorString()
{
   static const char szXQuote[]          = "Expected Quote";
   static const char szXInt[]            = "Expected Integer";
   static const char szXFloat[]          = "Expected Floating Point Number";
   static const char szEOF[]             = "Unexpected End Of File";
   static const char szFormat[]          = "File Format Error";
   static const char szBadPropType[]     = "Bad Property Type";
   static const char szXEquals[]         = "Expected Equals Sign";
   static const char szXOpenParen[]      = "Expected Open Parenthesis";
   static const char szBadPropTypeType[] = "Bad Property Type Type";
   static const char szXComma[]          = "Expected Comma";
   static const char szXHeader[]         = "Expected New Record Header";
   
   static LPCSTR causes[] = { szXQuote, szXInt, szXFloat, szEOF, szFormat, szBadPropType,
                              szXEquals, szXOpenParen, szBadPropTypeType, szXComma, szXHeader };
   
//   static const char szMsg1[] = "Error Reading File\n%s\nLine Number: %d\nColumn Number: %d\n%s";
//   QString msg;
//   msg.Format( szMsg1, (const char*)m_fileName, m_line, m_column, causes[m_cause] );
   QString msg = QString( "Error Reading File\n%1\nLine Number: %2\nColumn Number: %3\n%4" ).arg( m_fileName,
							QString::number(m_line), QString::number(m_column), causes[m_cause] );
   if (!m_strLastError.isEmpty())
      msg += "\n" + m_strLastError;  
   m_strError = msg;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMTextIO
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  BEMTextIO()
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
BEMTextIO::BEMTextIO()
{
	m_posBegin = 0;		// position of beginning of QFile
	InitBufferAndCounters();
}

void BEMTextIO::InitBufferAndCounters()
{
   m_lineCount  = 0;
   m_buffer[0]  = '\0';
   m_chrIndex   = 0;
   m_lineLength = 0;
	m_bAtEOF = FALSE;  // SAC 6/21/12
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  BEMTextIO()
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
UINT old2QtOpenMode( UINT nMode )
{	switch (nMode)
	{	case BEMTextIO::store     :  return QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate;   break;
		case BEMTextIO::load      :  return QIODevice::Text | QIODevice::ReadOnly  ;   break;
		case BEMTextIO::readWrite :  return QIODevice::Text | QIODevice::ReadWrite ;   break;
	}
	return (QIODevice::Text | QIODevice::ReadOnly);
}

BEMTextIO::BEMTextIO(const char* path, UINT nMode)
		: m_file( path )
{
//   QFileException e;
//   if (!Open(path, nMode, &e))
//      AfxThrowFileException(e.m_cause, e.m_lOsError);
	if (!m_file.open( (QIODevice::OpenMode) old2QtOpenMode( nMode ) ))
	{	assert( FALSE );
		OurThrowTextioException( 0 /*cause*/, path, 0, 0 );
	}

	m_reading = (nMode == BEMTextIO::load);
	m_posBegin = m_file.pos();		// position of beginning of QFile
	m_fileName = path;
	m_lineCount = 0;
	m_buffer[0] = '\0';
	m_chrIndex = 0;
	m_lineLength = 0;
	m_bIsCSVFile = (m_fileName.right(4).compare(".csv", Qt::CaseInsensitive) == 0);   // SAC 10/14/05
	m_bAtEOF = FALSE;  // SAC 6/21/12
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  Open()
//
// Purpose ------------------------------------------------------------------
//   Opens a file and initializes the various data members.
//   
// Arguments ----------------------------------------------------------------
//   const char*     path       : path and filename of file to open
//   UINT            nMode      : mode to open file in (read vs. write)
//   BEMTextioException* pException : exception to throw in case of an error
//   
// Return Value -------------------------------------------------------------
//   Return value from call to CSdtioFile::Open().
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMTextIO::Open(const char* path, UINT nMode, BEMTextioException* /*pException*/)
{
   bool ok;
   m_file.setFileName( path );
   if (nMode == BEMTextIO::load)
   {
      m_reading = TRUE;
      ok = m_file.open( QIODevice::Text | QIODevice::ReadOnly );  // CStdioFile::modeRead | CStdioFile::shareDenyWrite, pException) != 0);
   }
   else
   {
      m_reading = FALSE;
      ok = m_file.open( QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate );  // CStdioFile::modeCreate|CStdioFile::modeWrite, pException) != 0);
   }

	m_posBegin = m_file.pos();		// position of beginning of QFile
   m_fileName   = path;      
   m_lineCount  = 0;
   m_buffer[0]  = '\0';
   m_chrIndex   = 0;
   m_lineLength = 0;

   m_bIsCSVFile = (m_fileName.right(4).compare( ".csv", Qt::CaseInsensitive ) == 0);   // SAC 10/14/05
	m_bAtEOF = FALSE;  // SAC 6/21/12
   
   return ok;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  Close()
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
void BEMTextIO::Close()
{
   m_file.close();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  GetLineCount()
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
int BEMTextIO::GetLineCount()
{
   return m_lineCount;
}

int BEMTextIO::GetCharacterIndex()
{
   return m_chrIndex;
}

BOOL BEMTextIO::FoundInCurrentLine( const char* pszFindStr, int iMaxSearchLen /*=TextioMaxLine-1*/, BOOL bCaseSensitive /*=FALSE*/ )
{	static char szSrchIn[TextioMaxLine];
	static char szLocFindStr[TextioMaxLine];
	BOOL bRetVal = FALSE;
	if (pszFindStr == NULL || ((int) strlen(pszFindStr)) > iMaxSearchLen)
	{	assert( FALSE );
		return FALSE;
	}
	strncpy_s( szSrchIn, TextioMaxLine, m_buffer, iMaxSearchLen );
	if (bCaseSensitive)
		return (strstr( szSrchIn, pszFindStr ) != NULL);
	else
	{	//return (strcasestr( szSrchIn, pszFindStr ) != NULL);
		if (strstr( szSrchIn, pszFindStr ) != NULL)
			return TRUE;
		else
		{	strcpy_s( szLocFindStr, TextioMaxLine, pszFindStr );
			_strlwr_s( szLocFindStr, strlen(szLocFindStr)+1 );
			_strlwr_s( szSrchIn    , strlen(szSrchIn    )+1 );
			bRetVal = (strstr( szSrchIn, szLocFindStr ) != NULL);
		}
	}
	return bRetVal;
}

const char* BEMTextIO::GetCurrentLine()
{	return m_buffer;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  ThrowFormatException()
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
void BEMTextIO::ThrowFormatException(const char* lastError/*=NULL*/ )
{
   OurThrowTextioException(BEMTextioException::badFormat, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex, lastError);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  ThrowTextIOException()
//
// Purpose ------------------------------------------------------------------
//   Throws a file exception.
//   
// Arguments ----------------------------------------------------------------
//   int iCause  : The BEMTextioException::*** exception to throw
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMTextIO::ThrowTextIOException( int iCause )
{
   OurThrowTextioException(iCause, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  String()
//
// Purpose ------------------------------------------------------------------
//   Either reads or writes a string from/to the file based on whether the
//   file was originally opened for reading or writing.
//   
// Arguments ----------------------------------------------------------------
//   QString& string     : reference to the string to either read or write
//   UINT     fieldWidth : default fieldwidth used when writing to the file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMTextIO::String(QString& string, UINT fieldWidth)
{
   if (m_reading)
      string = ReadString();
   else
   {
      if (fieldWidth == DefStrLen)
         fieldWidth = string.length()+2;
      WriteString(string.toLocal8Bit().constData(), fieldWidth);
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  Int()
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
void BEMTextIO::Int(int& value, UINT fieldWidth)
{
   if (m_reading)
      value = (int)ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  UInt()
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
void BEMTextIO::UInt(UINT& value, UINT fieldWidth)
{
   if (m_reading)
      value = (UINT)ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  LongInt()
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
void BEMTextIO::LongInt(long& value,  UINT fieldWidth)
{
   if (m_reading)
      value = ReadLong();
   else
      WriteLong(value, fieldWidth);
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  Float()
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
void BEMTextIO::Float(float& value, UINT fieldWidth)
{
   if (m_reading)
      value = ReadFloat();
   else
      WriteFloat(value, fieldWidth);
}


void BEMTextIO::Double(double& value, UINT fieldWidth)
{
   if (m_reading)
      value = ReadDouble();
   else
      WriteDouble(value, fieldWidth);
}


BOOL StringExclusivelyNumber( QString& sPossibleNumber )
{	for (int i=0; i<sPossibleNumber.length(); i++)
		if (!IsFloat(sPossibleNumber[i]) && sPossibleNumber[i] != ' ' && sPossibleNumber[i] != '\t' && sPossibleNumber[i] != '.')  // SAC 6/2/13 - added check for '.'
			return FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CRuleFile Class Function:  ReadArray()
//
/////////////////////////////////////////////////////////////////////////////
void BEMTextIO::ReadArray( QString& sId )
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
//   QString& sId  : string to populate with database parameter read from file
//   BOOL bAllowLeadingDigit : 
//   
// Return Value -------------------------------------------------------------
//   1 if the token (parameter) is "DEFAULT" (used for DataType processing),
//   otherwise 0.
//   
// Notes --------------------------------------------------------------------
//   This string could be as simple as "token:token" or as complex as
//   "token:token[number]:token[number]:token[number]...".
//   This function was added to BEMTextIO 2/28/98 by SAC.
//   
/////////////////////////////////////////////////////////////////////////////
long BEMTextIO::ReadBEMProcParam( QString& sId, BOOL bAllowLeadingDigit )
{
   sId = ReadToken( bAllowLeadingDigit );  // reads string up to first ':'

   // return '1' if the token is "DEFAULT" (used in DataType processing)
   if ( sId.compare( "DEFAULT", Qt::CaseInsensitive ) == 0 )
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
// BEMTextIO Class Function:  ReadBEMCondition()
//
/////////////////////////////////////////////////////////////////////////////
static char szTDCC_Eq[]  = "=";
static char szTDCC_LEq[] = "<=";
static char szTDCC_GEq[] = ">=";
static char szTDCC_L[]   = "<";
static char szTDCC_G[]   = ">";
static char szTDCC_NEq[] = "!=";
static const char* pszConds[] = { szTDCC_Eq, szTDCC_LEq, szTDCC_GEq, szTDCC_L, szTDCC_G, szTDCC_NEq, NULL };

int StrToBEMCondition( QString& sCond )    // SAC 7/29/06 - added to facilitate parsing of string -> CCP Condition
{
   //QString sCond = pszCond;
   int iCond=-1;
   while (pszConds[++iCond] != NULL)
   {
      if (sCond == pszConds[iCond])
         return iCond;
   }
   return iCond;
}

int TrimBEMCondition( QString& str )    // returns index of condition present at the BEGINNING of the string AND removes condition (and any following spaces) from the QString
{  int iRetVal = -1;
   int iCond=-1;
   while (pszConds[++iCond] != NULL && iRetVal < 0)
   {  if (str.indexOf( pszConds[iCond] ) == 0)
         iRetVal = iCond;
   }
	if (iRetVal >= 0)
	{	str = str.right( str.length() - strlen( pszConds[iRetVal] ) );
		str = str.trimmed();		// was: TrimLeft();
	}
   return iRetVal;
}

int BEMTextIO::ReadBEMCondition()
{
   QString sToken;
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
// BEMTextIO Class Function:  YesNo()
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
void BEMTextIO::YesNo(bool& value)
{
   if (m_reading)
   {
      QString input = ReadString();
      assert(input.length() == 1);
      value = input[0] == 'Y' || input[0] == 'y';
   }
   else
   {
      static const char szYes[]  = "Y";
      static const char szNo[]   = "N";
      static const int             fieldLen = 5;      // 3 chars + 2 spaces
      WriteString(value ? szYes : szNo, fieldLen);
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  NewLine()
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
void BEMTextIO::NewLine()
{
   if (!m_reading)
      PutLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  Comment()
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
void BEMTextIO::Comment(const char* comment)
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
// BEMTextIO Class Function:  CommentBlock()
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
void BEMTextIO::CommentBlock(const char* comment)
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
// BEMTextIO Class Function:  ReadString()
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
QString BEMTextIO::ReadString( BOOL bReadPastEOL /*=FALSE*/ )
{
   Advance();

   char chr = GetChr();
   if (chr != Quote)
      OurThrowTextioException(BEMTextioException::xQuote, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);

   QString string;
   
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
      OurThrowTextioException(BEMTextioException::xQuote, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);
      
   return string;   
}


/////////////////////////////////////////////////////////////////////////////
static inline QString ExtractLeadingToken( QString& str )
{
	QString sRetStr;
	int iStrLen = str.length();
	int idx = 0;
	while (idx < iStrLen && isspace( str[idx].unicode() ))
		idx++;
	if (idx < iStrLen && !isalpha( str[idx].unicode() ))
	{	// assumption is that token always begins w/ an alphabetic character, so return an empty string if the first non-space char in this string is not alphabetic
	}
	else
	{	while (idx < iStrLen && !isspace( str[idx].unicode() ) && !IsAnySpecialChar(str[idx]))  // SAC 10/24/12 - added cast to unsigned char to prevent ASSERT in isctype.c ((unsigned)(c+1) <= 256)
		{	sRetStr += str[idx];
			idx++;
		}
	}
	return sRetStr;
}

QString BEMTextIO::ReadToNextToken( QStringList& saTokens, BOOL bReadPastEOL /*=TURE*/ )
{
   QString string, sLine;
	while (!m_bAtEOF && (sLine.isEmpty() || IsAllSpaces(sLine)))
		sLine = ReadLine( FALSE /*bAdvanceFirst*/ );

	if (!m_bAtEOF)
	{
		QString sTokenCheck = ExtractLeadingToken( sLine );			// NOTE - token expected to be the FIRST THING on the line
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
			assert( !string.isEmpty() );
			if (!string.isEmpty())
				string = string.left( string.length()-1 );  // trim trailing '\n' added above
		}

		if (iTokenStrIdx >= 0 && (bReadPastEOL || iNumLines == 0))
		{	// this line of text begins w/ a token, so BACKUP to beginning of line before returning to calling routine
			int iLineLen = sLine.length();
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
QString BEMTextIO::ReadCSVString( BOOL bReadToFollowingDelimeter /*=TRUE*/, BOOL bSkipBlankEntries /*=TRUE*/, BOOL* pbStrQuoted /*=NULL*/ )
{
   if (bSkipBlankEntries)  // don't advance if checking for blank CSV entries (could throw exception upon hitting EOL/EOF
      Advance();

   QString string;
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


int BEMTextIO::ParseCSVRecord( QStringList& saCSVFields )  // SAC 2/29/12
{
	saCSVFields.clear();

   QString string;
   char chr = GetChr();
	BOOL bQuoteOpen=FALSE, bQuoteClosed=FALSE;
	while (!m_bAtEOF && !AtEOL())
	{
		if (chr == Quote)
		{	if (!bQuoteOpen)
			{	// at beginning of quoted field
				bQuoteOpen = TRUE;
				bQuoteClosed = FALSE;
				if (!string.isEmpty())
				{	assert( FALSE );		// string should be empty if/when we encounter an opening quote
					string.clear();		// blast data loaded into string prior to encountering an opening quote ???
				}
			}
			else if (!bQuoteClosed)
			{	// at the end of quoted field
				bQuoteClosed = TRUE;
				saCSVFields.append( string );
				string.clear();
			}
			else
			{	assert( FALSE );	// quote found after end of quoted field but before following delimiter!!!
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
				saCSVFields.append( string );
				string.clear();
			}
			else
			{	assert( FALSE );			// invalid condition where:  !bQuoteOpen && bQuoteClosed
			}
		}
		else if (bQuoteOpen && bQuoteClosed)
		{	assert( chr == ' ' );		// allow for space chars to follow a quoted string (and preceding a delimeter or EOL)??
		}
		else
			string = string + chr;		// add character to string...
   
	   chr = GetChr();
	}

	if (!string.isEmpty())	// add trailing field (numeric, not followed by comma)
		saCSVFields.append( string );
	
	return (saCSVFields.size() > 0 ? saCSVFields.size() : (m_bAtEOF ? -1 : 0));
}


char* SubStr( const char *pszStr, int i0Start, int iNumChars )
{
	char* pcNew = new char[ iNumChars+1 ];
	strncpy_s( pcNew, iNumChars+1, pszStr + i0Start, iNumChars );
	pcNew[iNumChars] = '\0';
	return pcNew;
}

void ProcessStringForQuoteAndComment( QString& string )
{
	if (string[0] == '\"')
	{	string = string.right( string.length()-1 );
		// field quoted, so end string following closing quote
		if (string.indexOf('\"') > 0)
			string = string.left( string.indexOf('\"') );
		else if (string.indexOf('\"') == 0)
			string.clear();
		else
		{	assert( FALSE );  // no closing quote ???
		}
	}
	else
	{	// field data is not quoted, so trim right and then see if there are any comments imbedded in the string
		string = string.trimmed();		// was: TrimRight();
		if (string.indexOf(' ') > 0 || string.indexOf('\t') > 0)
		{	int iSpc = string.indexOf(' ');
			int iTab = string.indexOf('\t');
			int iPossibleFldEnd = ((iSpc > 0 && iTab > 0) ? std::min( iSpc, iTab) : (iSpc > 0 ? iSpc : iTab));
			int iCommentSemi = string.indexOf( CommentChr, iPossibleFldEnd+1 );
			int iCommentDbl  = string.indexOf( "//", iPossibleFldEnd+1 );
			int iCommentPart = string.indexOf( "/*", iPossibleFldEnd+1 );
			if (iCommentSemi > 0 || iCommentDbl > 0 || iCommentPart > 0)
			{	// Field includes comment
				//assert( (i==iNumFields-1) );   // not sure if we should ALLOW comments overlapping in fields (except perhaps the final field in a row)
				int iTrimRight = (iCommentSemi > 0 ? iCommentSemi : string.length());
				if (iCommentDbl > 0 && iCommentDbl < iTrimRight)
					iTrimRight = iCommentDbl;
				if (iCommentPart > 0 && iCommentPart < iTrimRight)
					iTrimRight = iCommentPart;
				string = string.left( iTrimRight );
				string = string.trimmed();		// was: TrimRight();  // re-trim, since field likely had spaces prior to comment
			}
		}
	}
}

int BEMTextIO::ParseColumnarRecord( QStringList& saFields, std::vector<int>& ia0ColBegins, std::vector<int>& ia0ColEnds, const char* pszTerminate )
{
	saFields.clear();
   Advance();

	if (pszTerminate && strlen(pszTerminate) > 0 && FoundInCurrentLine( pszTerminate, ia0ColBegins[0]+strlen(pszTerminate)+1 ))
	{	//return 0;
   }
	else
	{	int iNumFields = ia0ColBegins.size();
		for (int i=0; i<iNumFields; i++)
		{	QString string;
			if ((int) strlen(m_buffer) > ia0ColBegins[i])
			{
				char* pSubStr = SubStr( m_buffer, ia0ColBegins[i], ia0ColEnds[i]-ia0ColBegins[i]+1 );
				string = pSubStr;
				string = string.trimmed();		// was: TrimLeft();  // trims leading newline, space & tab chars
				if (!string.isEmpty())
					ProcessStringForQuoteAndComment( string );
				if (pSubStr && strlen(pSubStr) > 0)
					delete [] pSubStr;
			}
			saFields.append( string );
		}
	}
   	
	return (saFields.size() > 0 ? saFields.size() : (m_bAtEOF ? -1 : 0));
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  ReadToken()
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
QString BEMTextIO::ReadToken( BOOL bAllowLeadingDigit, BOOL bSkipLeadingDelimeters /*=FALSE*/, BOOL bAllowMidHyphen /*=FALSE*/, BOOL bAllowNewLineRead /*=TRUE*/ )  // SAC 10/9/05		// SAC 9/11/14 - added bAllowNewLineRead arg
{
   QString string;
   Advance( bSkipLeadingDelimeters, bAllowNewLineRead );
	if (!m_bAtEOF && (bAllowNewLineRead || !AtEOL()))
	{
	   char chr = GetChr( bAllowNewLineRead );
		if (!m_bAtEOF && (bAllowNewLineRead || !AtEOL()))
		{
			if ( !( isalpha( chr ) || chr == '_' || chr == ':' || (bAllowLeadingDigit && isdigit( chr )) ) )
   		   OurThrowTextioException(BEMTextioException::xQuote, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);
   		
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
// BEMTextIO Class Function:  PostReadToken()
//
/////////////////////////////////////////////////////////////////////////////
void BEMTextIO::PostReadToken()
{
   char ch;
   do
      ch = GetChr();
   while ( ch == ' ' || ch == ',' ); 
   UnGetChr();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  ReadLine()
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
QString BEMTextIO::ReadLine( BOOL bAdvanceFirst /*=TRUE*/ )
{
   // Read whole line of text
   if (bAdvanceFirst)
		Advance();

   QString string;

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
// BEMTextIO Class Function:  ReadLong()
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
long BEMTextIO::ReadLong()
{
   Advance();
   
   char chr = GetChr();
   if (!IsInt(chr))
      OurThrowTextioException(BEMTextioException::xInt, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);

   QString token;
   do
   {
      token += chr;
      chr = GetChr();
   }
   while(IsInt(chr));
   
   UnGetChr();
   
   return atol(token.toLocal8Bit().constData());
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  ReadFloat()
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
double BEMTextIO::ReadDouble()
{
   Advance();
	if (m_bAtEOF)
	{	OurThrowTextioException(BEMTextioException::xFloat, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);
	   return -999;
	}

   char chr = GetChr();;
   if (!IsFloat(chr))
      OurThrowTextioException(BEMTextioException::xFloat, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);

   QString token;
   do
   {
      token += chr;
      chr = GetChr();
   }
   while(IsFloat(chr));
   
   UnGetChr();
   
   return atof(token.toLocal8Bit().constData());
}


float BEMTextIO::ReadFloat()
{
   return (float)ReadDouble();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  IgnoreRestOfLine()
//
/////////////////////////////////////////////////////////////////////////////
BOOL BEMTextIO::IgnoreRestOfLine( char chr )
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
// BEMTextIO Class Function:  Advance()
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
void BEMTextIO::Advance( BOOL bSkipLeadingDelimeters /*=FALSE*/, BOOL bAllowNewLineRead /*=TRUE*/ )  // SAC 10/9/05		// SAC 9/11/14 - added bAllowNewLineRead arg
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
            GetLine();										assert( bAllowNewLineRead );
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
         GetLine();											assert( bAllowNewLineRead );
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
// BEMTextIO Class Function:  GetChr()
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
char BEMTextIO::GetChr( BOOL bAllowNewLineRead /*=TRUE*/ )		// SAC 9/11/14 - added bAllowNewLineRead arg
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
char BEMTextIO::NextCharacterOnLine()   
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
// BEMTextIO Class Function:  UnGetChr()
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
void BEMTextIO::UnGetChr()
{
   if (m_chrIndex > 0)
      m_chrIndex--;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  GetLine()
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
void BEMTextIO::GetLine()
{
   //LPTSTR pReadRet = m_file.ReadString(m_buffer, TextioMaxLine);
   //m_lineLength = (UINT) strlen(m_buffer);
	qint64 lineLen = m_file.readLine(m_buffer, TextioMaxLine);
	m_lineLength = (lineLen != -1 ? (UINT) lineLen : 0);

// experimenting w/ alternative to ensure consistent encoding/retention of ASCII chars > 127
//	QByteArray qbaLine = m_file.readLine(TextioMaxLine-1);
//	m_lineLength = qbaLine.size();			assert( m_lineLength < TextioMaxLine );
//	for (int iChrIdx=0; iChrIdx < m_lineLength; iChrIdx++)
//	{	m_buffer[iChrIdx] = qbaLine.at(iChrIdx);
//		if (m_buffer[iChrIdx] == 0)
//			break;
//	}
//	m_buffer[m_lineLength] = 0;	// ensure null terminated
   
   // If reading failed, we tried to read past the end of the file
   if (m_lineLength == 0)
      //OurThrowTextioException(BEMTextioException::endOfFile, m_fileName, m_lineCount, m_chrIndex);
		m_bAtEOF = TRUE;  // SAC 6/21/12

   m_chrIndex = 0;
   m_lineCount++;
}


void BEMTextIO::SkipToBeginningOfLine()	// SAC 10/19/12
{
   m_chrIndex = 0;
}

// SAC 6/15/05 - added new routine to enable comment lines that exceed TextioMaxLine in length
void BEMTextIO::SkipToEndOfLine()
{
   while (m_lineLength == TextioMaxLine-1  &&  m_buffer[m_lineLength-1] != 10)
   {
      m_chrIndex += m_lineLength;
      //LPTSTR pReadRet = m_file.ReadString(m_buffer, TextioMaxLine);
      //m_lineLength = (UINT) strlen(m_buffer);
		qint64 lineLen = m_file.readLine(m_buffer, TextioMaxLine);
   	m_lineLength = (lineLen != -1 ? (UINT) lineLen : 0);
   
      // If m_buffer is empty, we tried to read past the end of the file
      if (m_lineLength == 0)
         OurThrowTextioException(BEMTextioException::endOfFile, m_fileName.toLocal8Bit().constData(), m_lineCount, m_chrIndex);
   }
}


// SAC 10/12/12 - added new routine to jump back to beginning of file, for iterative reading routines
void BEMTextIO::SkipToBeginningOfFile()
{
	m_file.seek( m_posBegin );
	InitBufferAndCounters();  // re-initialize buffer & line/character counters
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  WriteToken()
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
#pragma warning (disable:4996)
void BEMTextIO::WriteToken(const char* string, UINT fieldWidth)
{
// SAC 4/21/00 - Added if statement to ensure fieldWidth > 0
   if (fieldWidth > 0)
   {
      if(fieldWidth > TextioMaxLine-1) 
         fieldWidth = TextioMaxLine-1;

      char format[16];
      sprintf(format, "%%-.%ds", fieldWidth);
//      sprintf(format, "%%-.%ds", fieldWidth-2);
   
      char line[TextioMaxLine+1];
      sprintf(line, format, string);

      if (fieldWidth + m_chrIndex >= TextioMaxLine)
         NewLine();

	  UINT i=0;
      for (; line[i] != '\0'; i++)
         PutChr(line[i]);

      for (; i < fieldWidth-1; i++)
         PutChr(' ');

//      PutDelimiter();
   }
}
#pragma warning (default:4996)


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  WriteString()
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
#pragma warning (disable:4996)
void BEMTextIO::WriteString(const char* string, UINT fieldWidth)
{
   if(fieldWidth > TextioMaxLine-1) 
      fieldWidth = TextioMaxLine-1;

   char format[16];
   sprintf(format, "%%-.%ds", fieldWidth-2);
   
   char line[TextioMaxLine+1];
   sprintf(line, format, string);

   if (fieldWidth + m_chrIndex >= TextioMaxLine)
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
#pragma warning (default:4996)


void BEMTextIO::WriteWholeRecord(const char *string)   // SAC 10/10/05 - added to facilitate output of entire lines to CSV file (with line counting)
{
   //m_file.WriteString( string );
   m_file.write( string );
   PutLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  WriteQuotedString()
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
#pragma warning (disable:4996)
void BEMTextIO::WriteQuotedString(const char *string, UINT fieldWidth)
{
   if(fieldWidth > TextioMaxLine-1) 
      fieldWidth = TextioMaxLine-1;

   char format[16];
   sprintf(format, "%%-.%ds", fieldWidth);
   
   char line[TextioMaxLine+1];
   sprintf(line, format, string);

   if (fieldWidth + m_chrIndex >= TextioMaxLine)
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
#pragma warning (default:4996)


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  WriteLong()
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
#pragma warning (disable:4996)
void BEMTextIO::WriteLong(long value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dld", fieldWidth);
   
   char string[TextioMaxLine+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if(fieldWidth + m_chrIndex >= TextioMaxLine)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++ )
      PutChr(string[i]);

   PutDelimiter();
}
#pragma warning (default:4996)


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  WriteFloat()
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
#pragma warning (disable:4996)
void BEMTextIO::WriteFloat(float value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dg", fieldWidth);
   
   char string[TextioMaxLine+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if (fieldWidth + m_chrIndex >= TextioMaxLine)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++)
      PutChr(string[i]);

   PutDelimiter();
}

void BEMTextIO::WriteDouble(double value, UINT fieldWidth)
{
   char format[16];
   sprintf(format, "%%%dg", fieldWidth);
   
   char string[TextioMaxLine+1];
   sprintf(string, format, value);

   fieldWidth = (UINT) strlen(string);
   if (fieldWidth + m_chrIndex >= TextioMaxLine)
      NewLine();

   for (UINT i = 0; i < fieldWidth; i++)
      PutChr(string[i]);

   PutDelimiter();
}
#pragma warning (default:4996)


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  PutChr()
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
void BEMTextIO::PutChr(char chr)
{
   m_file.write(&chr, 1);
   m_chrIndex++;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  PutLine()
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
void BEMTextIO::PutLine()
{
   char nl = '\n';
   m_file.write(&nl, 1);
   m_chrIndex = 0;
   m_lineCount++;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTextIO Class Function:  PutDelimiter()
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
void BEMTextIO::PutDelimiter()
{
//   PutChr(Delimiter);
   PutChr( GetDelimiter( m_bIsCSVFile ) );  // SAC 10/14/05
}

