// ranges.cpp - implementation of BEMRangeCheck class
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
#include "BEMProcI.h"
#include "BEMPropertyType.h"
#include "expRanges.h"
#include "expRuleList.h"
#include "BEMProcObject.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMRangeCheck
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
BEMRangeCheck::BEMRangeCheck( long lDBID, int iCondition, int iSeverity, const char* pszValueOrParam, const char* pszMessage /*=NULL*/ )
{
   m_dbid			= lDBID     ;
   m_condition	= iCondition;
   m_severity		= iSeverity ;

	QString sValueOrParam = pszValueOrParam;
	TrimLeadingSpaces( sValueOrParam );					assert( !sValueOrParam.isEmpty() );
	if (sValueOrParam.isEmpty())
	{  m_condition = BEMC_NumConditions;		// errant condition - pszValueOrParam must either be a numeric value or BEMProc Obj:Prop string
		m_value  = 0.0F;
		m_rtDBID = 0;
	}
	else if (sValueOrParam[0].isDigit() || sValueOrParam[0] =='-' || sValueOrParam[0] =='+' || sValueOrParam[0] == '.')
	{	m_value = (double) atof( sValueOrParam.toLocal8Bit().constData() );
		m_rtDBID = 0;
	}
	else
	{	m_value = 0.0F;
		m_rtDBID = BEMPX_GetDatabaseID( sValueOrParam );
		// Post error to error listing and set bRetVal to FALSE if database ID is invalid
		if (m_rtDBID <= 0)
		{  m_condition = BEMC_NumConditions + 1;		// errant condition - pszValueOrParam not a numeric value or BEMProc Obj:Prop string
			m_value  = 0.0F;
			m_rtDBID = 0;
		}
	}

	if (pszMessage && strlen( pszMessage ) > 0)
		m_message = pszMessage;
	else
	{	QString sSeverityMsg = (m_severity == RANGE_ERROR ? "Error" : (m_severity == RANGE_WARNING ? "" : "Message"));
		QString sCondMsg = "<unknown>";
		switch (m_condition)
		{	case BEMC_Equal       :	sCondMsg = "not equal";                   break;
         case BEMC_LessOrEqual : sCondMsg = "not less than or equal";      break;
         case BEMC_GrtrOrEqual : sCondMsg = "not greater than or equal";	break;
         case BEMC_Less        : sCondMsg = "not less then";               break;
         case BEMC_Greater     : sCondMsg = "not greater then";            break;
         case BEMC_NotEqual    : sCondMsg = "equal";                       break;
		}
		//m_message.Format( "%s if %s to %s", sSeverityMsg, sCondMsg, sValueOrParam );
		m_message = QString( "%1 if %2 to %3" ).arg( sSeverityMsg, sCondMsg, sValueOrParam );
	}

	m_caseDBID = 0;
	m_caseCondition = BEMC_NumConditions;
	m_caseValue = 0.0F;
	m_caseRtDBID = 0;
}


void BEMRangeCheck::copy( BEMRangeCheck* pRC )
{
   m_dbid          = pRC->m_dbid         ;
   m_condition     = pRC->m_condition    ;
   m_value         = pRC->m_value        ;
   m_rtDBID        = pRC->m_rtDBID       ;
   m_severity      = pRC->m_severity     ;
   m_message       = pRC->m_message      ;
   m_caseDBID      = pRC->m_caseDBID     ;
   m_caseCondition = pRC->m_caseCondition;
   m_caseValue     = pRC->m_caseValue    ;
   m_caseRtDBID    = pRC->m_caseRtDBID   ;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMRangeCheck Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a range check definition from a BEMTextIO file into this class instance.
//   
// Arguments ----------------------------------------------------------------
//   BEMTextIO& file      : text file to read range check from
//   QFile&   errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if the database ID is successfully read from file and translated,
//   else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMRangeCheck::Read( BEMTextIO& file, QFile& errorFile )
{
   bool bRetVal = TRUE;
   char ch;

   // sName includes <bldg component name>:<parameter name>([<array index>])
   QString sName;
   file.ReadBEMProcParam( sName );
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

   	// New code added 4/13/98 to import the enhanced range checking structure
   	m_condition = file.ReadBEMCondition();

   	ch = file.GetChr();
   	file.UnGetChr();
   	if (isdigit(ch) || ch =='-' || ch =='+' || ch == '.')
   	{
   	   m_value = file.ReadDouble();   // read numeric value (min or max)
   	   m_rtDBID = 0;
   	}
   	else
   	{
   	   m_value = 0.0F;

   	   file.ReadBEMProcParam( sName );
   	   m_rtDBID = BEMPX_GetDatabaseID( sName );
   	   // Post error to error listing and set bRetVal to FALSE if database ID is invalid
   	   if (m_rtDBID <= 0)
   	   {
	   	   QString sErr = QString( "\tParameter '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number(file.GetLineCount()) );
   	      errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
   	      bRetVal = FALSE;
   	   }
   	}
   	file.PostReadToken();

   	// SAC - 4/13/98 - Added to implement conditional range checks
   	file.ReadBEMProcParam( sName );
   	file.PostReadToken();
   	if (sName.compare( "None", Qt::CaseInsensitive ) != 0)
   	{  // read the case condition stuff
   	   m_caseDBID = BEMPX_GetDatabaseID( sName );
   	   // Post error to error listing and set bRetVal to FALSE if database ID is invalid
   	   if (m_caseDBID <= 0)
   	   {
	   	   QString sErr = QString( "\tCase parameter '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number(file.GetLineCount()) );
   	      errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
   	      bRetVal = FALSE;
   	   }

   	   file.PostReadToken();

   	   // New code added 4/13/98 to import the enhanced range checking structure
   	   m_caseCondition = file.ReadBEMCondition();

   	   ch = file.GetChr();
   	   file.UnGetChr();
   	   if (isdigit(ch) || ch =='-' || ch =='+' || ch == '.')
   	   {
   	      m_caseValue = file.ReadDouble();   // read numeric value (min or max)
   	      m_caseRtDBID = 0;
   	   }
   	   else
   	   {
   	      m_caseValue = 0.0F;

   	      file.ReadBEMProcParam( sName );
   	      m_caseRtDBID = BEMPX_GetDatabaseID( sName );
   	      // Post error to error listing and set bRetVal to FALSE if database ID is invalid
   	      if (m_caseRtDBID <= 0)
   	      {
		   	   QString sErr = QString( "\tCase parameter '%1' Not Found on line: %2\n\n" ).arg( sName, QString::number(file.GetLineCount()) );
   	         errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
   	         bRetVal = FALSE;
   	      }
   	   }
   	   file.PostReadToken();
   	}
   	else
   	{
   	   m_caseDBID = 0;
   	   m_caseCondition = BEMC_NumConditions;
   	   m_caseValue = 0.0F;
   	   m_caseRtDBID = 0;
   	}

   	QString error = file.ReadToken();   // read severity keyword
   	if ( error.compare( "ERROR", Qt::CaseInsensitive ) == 0 )
   	   m_severity = RANGE_ERROR;
   	else if ( error.compare( "WARNING", Qt::CaseInsensitive ) == 0 )
   	   m_severity = RANGE_WARNING;
   	else if ( error.compare( "MESSAGE", Qt::CaseInsensitive ) == 0 )
   	   m_severity = RANGE_MESSAGE;
   	else
   	   ; // TO DO: Throw Exception

   	file.PostReadToken();
   
   	m_message = file.ReadString();   // read range check failure message
   	while ( !file.AtEOL() && ( ch == ' ' || ch == ',' ) ) 
   	   ch = file.GetChr();
	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMRangeCheck Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read this range check definition from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read this range
//                       check definition from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMRangeCheck::Read( CryptoFile& file )
{
   file.Read( &m_dbid,      sizeof( long ) );
   file.Read( &m_condition, sizeof( int ) );
   file.Read( &m_value,     sizeof( double ) );
   file.Read( &m_rtDBID,    sizeof( long ) );

   file.Read( &m_caseDBID,      sizeof( long ) );
   file.Read( &m_caseCondition, sizeof( int ) );
   file.Read( &m_caseValue,     sizeof( double ) );
   file.Read( &m_caseRtDBID,    sizeof( long ) );

   file.Read( &m_severity,  sizeof( int ) );
   file.ReadQString( m_message );
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMRangeCheck Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write this range check definition to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write this range
//                       check definition to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMRangeCheck::Write( CryptoFile& file )
{
   file.Write( &m_dbid,      sizeof( long ) );
   file.Write( &m_condition, sizeof( int ) );
   file.Write( &m_value,     sizeof( double ) );
   file.Write( &m_rtDBID,    sizeof( long ) );

   file.Write( &m_caseDBID,      sizeof( long ) );
   file.Write( &m_caseCondition, sizeof( int ) );
   file.Write( &m_caseValue,     sizeof( double ) );
   file.Write( &m_caseRtDBID,    sizeof( long ) );

   file.Write( &m_severity,  sizeof( int ) );
   file.WriteQString( m_message );
}


// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// //
// // class BEMPropertyRangesList
// //
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  ~BEMPropertyRangesList()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the range check definitions from the list.
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
// BEMPropertyRangesList::~BEMPropertyRangesList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  InitRangesList()
// //
// // Purpose ------------------------------------------------------------------
// //   Initializes the list by removing all range check definitions.
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
// void BEMPropertyRangesList::InitRangesList()
// {
//    RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  RemoveAll()
// //
// // Purpose ------------------------------------------------------------------
// //   Removes all the range check definitions from the list, deleting each as we go.
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
// void BEMPropertyRangesList::RemoveAll()
// {
//    POSITION pos = GetHeadPosition();
//    while ( pos != NULL )
//       delete (BEMRangeCheck*)GetNext( pos );
//    CObList::RemoveAll();
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  AddRanges()
// //
// // Purpose ------------------------------------------------------------------
// //   Adds a BEMRangeCheck instance onto the end of the list.
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
// void BEMPropertyRangesList::AddRanges( BEMRangeCheck* range )
// {
//    AddTail( (CObject*) range );
// }


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyRangesList Class Function:  ReadText()
//
// Purpose ------------------------------------------------------------------
//   Read the range check definitions from a text file.
//   
// Arguments ----------------------------------------------------------------
//   QString sFileName : path/filename of file to read range check definitions from
//   QFile&  errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if all range check definitions are successfully read from the file,
//   else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyRangesList::ReadText( QString sFileName, QFile& errorFile )
bool RuleSet::readRangesText( QString sFileName, QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( sFileName.toLocal8Bit().constData(), BEMTextIO::load );

      QString readMsg = QString("Reading ranges file: %1\n\n").arg( sFileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
      try
      {
         try
         {
				BOOL bFileEndFound = FALSE;  // SAC 6/25/12
            while ( !bFileEndFound )   //TRUE ) // EOF handled in catch block 
            {  // create new BEMRangeCheck
               BEMRangeCheck* newData = new BEMRangeCheck();
               // read range check definition from file
               bRetVal = (newData->Read( file, errorFile ) && bRetVal);
				   if (newData->getDBID() == -999)  // SAC 6/25/12 - check for lDBID set to special value denoting END of Ranges file
					{	bFileEndFound = TRUE;
						delete newData;
					}
					else
					{	// add this new BEMRangeCheck to list
						ruleSet.addRangeCheck( newData );
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
					throw std::runtime_error(boost::str(boost::format("Error reading range checks from text because '%1', from file:  %2") %
																			te.m_strError.toLocal8Bit().constData() % sFileName.toLocal8Bit().constData() ));
         }	}
      }
		catch (BEMTextioException& te)
      {  // ERROR occurred
         QString msg = QString("Error reading range checks\nFrom File: %1\n\n\t%2\n\n").arg( sFileName, te.m_strError );
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
		QString sErrMsg = QString( "Error opening range checks text file: %1\n\t - cause: %2\n\n" ).arg( sFileName, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening range checks text file: %1\n\n" ).arg( sFileName );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
  	}

   return bRetVal;
}


// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  Read()
// //
// // Purpose ------------------------------------------------------------------
// //   Reads the range check definitions from a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CCryptoFile& file : the binary encrypted ruleset file to read the range
// //                       check definitions from.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyRangesList::Read( CCryptoFile& file )
// {
//    int count = 0;
//    // read number of range check definitions stored in file
//    file.Read( &count, sizeof( int ) );
// 
//    // loop over each entry, creating a new BEMRangeCheck, reading it and adding it to the list
//    for ( int i = 0; i < count; i++ )
//    {
//       BEMRangeCheck * range = new BEMRangeCheck;
//       range->Read( file );
//       AddRanges( range);
//    }
// 
// 	postRangeChecksToDatabase();
// 
//    return TRUE;
// }


bool RuleSet::postRangeChecksToDatabase()
{	bool bRetVal = true;
   // Now reset all existing BEMProc RangeChecks which are of source RANGESOURCE_RULESET
   BEMP_ResetRangeChecks();

	int iError;
	for (int iR=0; iR < (int) m_ranges.size(); iR++)	
	{	BEMRangeCheck* pR = m_ranges.at(iR);
      if (pR && pR->getDBID() > 0)
		{
			BEMPropertyType* pPT = BEMPX_GetPropertyTypeFromDBID( pR->getDBID(), iError );
			if (pPT==NULL)
			{	assert( false );
			}
			else
			{	pPT->addRangeCheck( pR );
				//try
				//{	BEMRangeCheck* pNewRC = new BEMRangeCheck( pR->getDBID(), pR->getCondition(), pR->getValue(),
				//								pR->getRtDBID(), pR->getSeverity(), pR->getMessage(), pR->getCaseDBID(),
				//								pR->getCaseCondition(), pR->getCaseValue(), pR->getCaseRtDBID() );		assert( pNewRC );
				//	if (pNewRC)
				//		pPT->addRangeCheck(pNewRC);
				//}
				//catch (std::exception& e)
				//{	std::cout << "Warning: RuleSet::postRangeChecksToDatabase failed to create BEMRangeCheck because " << e.what() << '\n';
				//}
				//catch (...)
				//{  std::cout << "Warning: RuleSet::postRangeChecksToDatabase failed to create BEMRangeCheck\n";
				//}
		}	}
      else
      {	bRetVal = false;			assert( FALSE );
      }
   }
   return bRetVal;
}


// /////////////////////////////////////////////////////////////////////////////
// //
// // BEMPropertyRangesList Class Function:  Write()
// //
// // Purpose ------------------------------------------------------------------
// //   Writes the range check definitions to a binary encrypted ruleset file.
// //   
// // Arguments ----------------------------------------------------------------
// //   CCryptoFile& file : the binary encrypted ruleset file to write the range
// //                       check definitions to.
// //   
// // Return Value -------------------------------------------------------------
// //   TRUE always
// //   
// // Notes --------------------------------------------------------------------
// //   None
// //   
// /////////////////////////////////////////////////////////////////////////////
// bool BEMPropertyRangesList::Write( CCryptoFile& file )
// {
//    int count = (int) GetCount();
//    // write the number of range check definitions
//    file.Write( &count, sizeof( int ) );
// 
//    POSITION pos = GetHeadPosition();
//    // loop over entire list, writing each to the file
//    while ( pos != NULL )
//    {
//       BEMRangeCheck* range= (BEMRangeCheck*)GetNext( pos );
//       range->Write( file );
//    }
// 
//    return TRUE;
// }
// 


/////////////////////////////////////////////////////////////////////////////
// Range Exports
/////////////////////////////////////////////////////////////////////////////

void BEMP_ResetRangeChecks()
{
   // loop over ALL BEMProc property types and clear out the range checks for each
   for (int iProp=0; iProp<eBEMProc.getNumPropertyTypes(); iProp++)
   	eBEMProc.getPropertyType( iProp )->clearRangeChecks();
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_PerformRangeCheck()
//
// Purpose ------------------------------------------------------------------
//   Perform a range check on a user input value and display the range check
//   message in the event the specified value fails the range check.
//   
// Arguments ----------------------------------------------------------------
//   long  lDBID  : 6 digit database ID CCPPAA (comp/property/array)
//   double fValue : numeric value to perform the range check on
//   
// Return Value -------------------------------------------------------------
//   0 if no range check error found, else the integer value corresponding to
//   the severity of the range check error.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////

// message segments pieced together to construct range check violation messages
static char szPRCFail[]  = "Range Check ";
static char szPRCValue[] = "Value being checked = ";

static char szPRCSev1[] = "Error";
static char szPRCSev2[] = "Warning";
static char szPRCSev3[] = "Message";
static const char* pszPRCSev[] = { szPRCSev1, szPRCSev2, szPRCSev3 };

int BEMPX_PerformRangeCheck( long lDBID, double dValue, BOOL bSilent, QString* psMsg, int iOccur )
{
   int iRetVal = 0;

   // get the various DB IDs and property type pointer from the lDBID
   int i1Class = BEMPX_GetClassID(    lDBID );
   int i1Param = BEMPX_GetPropertyID( lDBID );
   int i1Array = BEMPX_GetArrayID(    lDBID );
   BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Param );
	int iNumRanges = (pPropType ? pPropType->getNumRangeChecks() : 0);

   // confirm all IDs and pPropType are valid
   if (i1Class > 0 && i1Param > 0 && i1Array > 0 && pPropType && iNumRanges > 0)
   {
		for (int i=0; i < iNumRanges; i++)
		{	BEMRangeCheck* pRC = pPropType->getRangeCheck(i);				assert(pRC);
			if (pRC && (pRC->getArrayIndex() == 0 || pRC->getArrayIndex() == i1Array))
			{
				// First, confirm that any required conditions are met prior to performing this check
				BOOL bContinue = TRUE;
				if (pRC->getCaseDBID() > 0)
					bContinue = BEMPX_ConditionTrue( pRC->getCaseDBID(), pRC->getCaseCondition(),
																pRC->getCaseValue(), pRC->getCaseRtDBID(), iOccur );
            if (bContinue)
            {
               // perform range check
               if (!BEMPX_FloatConditionTrue( dValue, pRC->getCondition(), pRC->getValue(), pRC->getRtDBID(), iOccur )) 
               {  // Failed RangeCheck
                  if (psMsg || !bSilent)
                  {
                     QString sVal = QString::number( dValue );
                     if (psMsg)  // Load abreviated 1-line message into psMsg
                        *psMsg = QString( "%1%2.  %3" ).arg( szPRCValue, sVal, pRC->getMessage() );

                     if (!bSilent)  // Load full error message and display in messagebox
                        BEMMessageBox( QString( "%1%2:\n%3%4.\n%5" ).arg( szPRCFail, pszPRCSev[ pRC->getSeverity() - 1 ],
                        																	szPRCValue, sVal, pRC->getMessage() ), "", 2 /*warning*/ );
                  }

                  // set return value to FALSE if check fails AND severity = ERROR
                  iRetVal = pRC->getSeverity();
                  if ( (pRC->getSeverity() == RANGE_ERROR) ||
                       (pRC->getSeverity() == RANGE_WARNING) )
                  {
   // TO DO -- Post message to project LOG file
                  }
               }
		}	}	}
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_GenerateRangeMessage()
//
// Purpose ------------------------------------------------------------------
//   Perform a range check on a user input value and display the range check
//   message in the event the specified value fails the range check.
//   
// Arguments ----------------------------------------------------------------
//   long  lDBID  : 6 digit database ID CCPPAA (comp/property/array)
// QString* psMsg : pointer to a QString that will be populated with the gen-
//                  erated range message to be displayed.
//   int iOccur : occurence index for the DBID
//   
// Return Value -------------------------------------------------------------
//   0 - The QString argument pointer is populated with the generated message 
//       if range checks exist for this database ID.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
int BEMPX_GenerateRangeMessage( long lDBID, QString* psMsg, int iOccur /*=-1*/, BOOL bIncludeUnits /*=TRUE*/ ) 
{
   int iRetVal = 0;

   // get the various DB IDs and property type pointer from the lDBID
   int i1Class = BEMPX_GetClassID(    lDBID );
   int i1Param = BEMPX_GetPropertyID( lDBID );
   int i1Array = BEMPX_GetArrayID(    lDBID );
   BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1Param );
	int iNumRanges = (pPropType ? pPropType->getNumRangeChecks() : 0);

   double fEqualErrValue = -999;
   double fMinErrValue = -999;
   double fMaxErrValue = -999;
   double fNotEqualErrValue = -999;
   BOOL bMinErrEqualSet = FALSE;
   BOOL bMaxErrEqualSet = FALSE;

   double fEqualWarnValue = -999;
   double fMinWarnValue = -999;
   double fMaxWarnValue = -999;
   double fNotEqualWarnValue = -999;
   BOOL bMinWarnEqualSet = FALSE;
   BOOL bMaxWarnEqualSet = FALSE;

   // confirm all IDs and pPropType are valid
   if (i1Class > 0 && i1Param > 0 && i1Array > 0 && pPropType && iNumRanges > 0)
	{
		for (int i=0; i < iNumRanges; i++)
		{	BEMRangeCheck* pRC = pPropType->getRangeCheck(i);				assert(pRC);
			if (pRC && (pRC->getArrayIndex() == 0 || pRC->getArrayIndex() == i1Array))
         {
				// First, confirm that any required conditions are met prior to performing this check
				BOOL bContinue = TRUE;
				if (pRC->getCaseDBID() > 0)
					bContinue = BEMPX_ConditionTrue( pRC->getCaseDBID(), pRC->getCaseCondition(),
																pRC->getCaseValue(), pRC->getCaseRtDBID(), iOccur );
            if (bContinue)
            {
               if( pRC->getSeverity() == RANGE_ERROR )
               {
                  switch( pRC->getCondition() )
                  {
                  case BEMC_Equal         :
                     fEqualErrValue = (fEqualErrValue == -999) ? pRC->getValue() : fEqualErrValue; 
                     break;
                  case BEMC_GrtrOrEqual   : 
                     bMinErrEqualSet = (fMinErrValue == -999 || fMinErrValue > pRC->getValue()) ? TRUE : bMinErrEqualSet; 
                  case BEMC_Greater       : 
                     fMinErrValue = (fMinErrValue == -999 || fMinErrValue > pRC->getValue()) ? pRC->getValue() : fMinErrValue; 
                     break;
                  case BEMC_LessOrEqual   : 
                     bMaxErrEqualSet = (fMaxErrValue == -999 || fMaxErrValue < pRC->getValue()) ? TRUE : bMaxErrEqualSet; 
                  case BEMC_Less          : 
                     fMaxErrValue = (fMaxErrValue == -999 || fMaxErrValue < pRC->getValue()) ? pRC->getValue() : fMaxErrValue; 
                     break;
                  case BEMC_NotEqual      :
                     fNotEqualErrValue = (fNotEqualErrValue == -999) ? pRC->getValue() : fNotEqualErrValue; 
                     break;
                  }
               }
               else if( pRC->getSeverity() == RANGE_WARNING )
               {
                  switch( pRC->getCondition() )
                  {
                  case BEMC_Equal         :
                     fEqualWarnValue = (fEqualWarnValue == -999) ? pRC->getValue() : fEqualWarnValue; 
                     break;
                  case BEMC_GrtrOrEqual   : 
                     bMinWarnEqualSet = (fMinWarnValue == -999 || fMinWarnValue > pRC->getValue()) ? TRUE : bMinWarnEqualSet; 
                  case BEMC_Greater       : 
                     fMinWarnValue = (fMinWarnValue == -999 || fMinWarnValue > pRC->getValue()) ? pRC->getValue() : fMinWarnValue; 
                     break;
                  case BEMC_LessOrEqual   : 
                     bMaxWarnEqualSet = (fMaxWarnValue == -999 || fMaxWarnValue < pRC->getValue()) ? TRUE : bMaxWarnEqualSet; 
                  case BEMC_Less          : 
                     fMaxWarnValue = (fMaxWarnValue == -999 || fMaxWarnValue < pRC->getValue()) ? pRC->getValue() : fMaxWarnValue; 
                     break;
                  case BEMC_NotEqual      :
                     fNotEqualWarnValue = (fNotEqualWarnValue == -999) ? pRC->getValue() : fNotEqualWarnValue; 
                     break;
                  }
			}	}	}
      }

      if (psMsg)  // Load message into psMsg
      {
        	psMsg->clear();

         QString sTemp, sUnits;
         if (bIncludeUnits && !pPropType->getUnitsLabel().isEmpty()) 
            sUnits = QString("  (%1)" ).arg( pPropType->getUnitsLabel() );
         if( fEqualErrValue != -999 || fMinErrValue != -999 || fMaxErrValue != -999 || fNotEqualErrValue != -999 )
         {
            // We have an error condition message to generate
            if( fNotEqualErrValue != -999 )
            {  *psMsg += "Error if:  Value = ";
               *psMsg += QString::number( fNotEqualErrValue );
            }
            else
            {  *psMsg += "Error if not:  ";
               if( fEqualErrValue != -999 )
               {  *psMsg += "Value = ";
                  *psMsg += QString::number( fEqualErrValue );
               }
               else
               {
                  if( fMinErrValue != -999 && fMaxErrValue != -999)
                  {
                     *psMsg += QString::number( fMinErrValue );
                     *psMsg += (bMinErrEqualSet ? " <= Value" : " < Value");

                     *psMsg += (bMaxErrEqualSet ? " <= " : " < ");
                     *psMsg += QString::number( fMaxErrValue );
                  }
                  else if( fMinErrValue != -999 )
                  {
                     *psMsg += (bMinErrEqualSet ? "Value >= " : "Value > ");
                     *psMsg += QString::number( fMinErrValue );
                  }
                  else if( fMaxErrValue != -999 )
                  {
                     *psMsg += (bMaxErrEqualSet ? "Value <= " : "Value < ");
                     *psMsg += QString::number( fMaxErrValue );
                  }
            }	}
            *psMsg += sUnits;
         }
         if( fEqualWarnValue != -999 || fMinWarnValue != -999 || fMaxWarnValue != -999 || fNotEqualWarnValue != -999 )
         {
				if (bIncludeUnits)
               *psMsg += "\n"; 
				else
               *psMsg += ",  ";

            // We have an Warning condition message to generate
            if( fNotEqualWarnValue != -999 )
            {
               *psMsg += "Warning if:  ";
               *psMsg += "Value = ";
               *psMsg += QString::number( fNotEqualWarnValue );
            }
            else
            {
               *psMsg += "Warning if not:  ";
               if( fEqualWarnValue != -999 )
               {
                  *psMsg += "Value = ";
                  *psMsg += QString::number( fEqualWarnValue );
               }
               else
               {
                  //BOOL bBoth = FALSE;
                  if( fMinWarnValue != -999 && fMaxWarnValue != -999)
                  {
                     *psMsg += QString::number( fMinWarnValue );
                     *psMsg += (bMinWarnEqualSet ? " <= Value" : " < Value");

                     *psMsg += (bMaxWarnEqualSet ? " <= " : " < ");
                     *psMsg += QString::number( fMaxWarnValue );
                  }
                  else if( fMinWarnValue != -999 )
                  {
                     *psMsg += (bMinWarnEqualSet ? "Value >= " : "Value > ");
                     *psMsg += QString::number( fMinWarnValue );
                  }
                  else if( fMaxWarnValue != -999 )
                  {
                     *psMsg += (bMaxWarnEqualSet ? "Value <= " : "Value < ");
                     *psMsg += QString::number( fMaxWarnValue );
                  }
            }	}
            *psMsg += sUnits;
      }	}
   }
   return iRetVal;
}


 