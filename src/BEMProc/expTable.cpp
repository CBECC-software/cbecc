// table.cpp - implementation of BEMTable and BEMTableList classes
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
#include "expTable.h"
#include "expRuleList.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMTable
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMTable Class Function:  ~BEMTable()
//
// Purpose ------------------------------------------------------------------
//   Destructor - deletes all the look-up table data
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
BEMTable::~BEMTable()
{
	int i;
	for (i = m_rowIndepCells.size()-1; i >= 0; i--)
	{	assert( m_rowIndepCells.at(i) );
		if (m_rowIndepCells.at(i))
			delete [] m_rowIndepCells.at(i);
	}
	m_rowIndepCells.clear();

	for (i = m_data.size()-1; i >= 0; i--)
	{	assert( m_data.at(i) );
		if (m_data.at(i))
			delete [] m_data.at(i);
	}
	m_data.clear();
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTable Class Function:  Lookup()
//
// Purpose ------------------------------------------------------------------
//   Performs a table look-up and sets the value found to the address of the
//   pfValue function argument.
//   
// Arguments ----------------------------------------------------------------
//   float* pfParams : pointed to an array of m_iNParams independent variable values
//   int    iCol     : column of dependent data to return
//   float* pfValue  : pointer to address where look-up result to be posted (only if found)
//   
// Return Value -------------------------------------------------------------
//   TRUE if table look-up is successful (value is found), else FALSE.
//   If the return value is TRUE, the result of the table look-up is copied
//   to the address pointed to by the pfValue function argument.
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     Simple linear serch for now -
//     loop over array of rows
//        loop over nparams searching for matches
//           if found set fValue to iCol's value and return TRUE
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMTable::Lookup( double* pfParams, int iCol, double* pfValue, BOOL bVerboseOutput )  // SAC 9/25/02
{
   bool found = FALSE;

   // SAC 9/25/02
   if (bVerboseOutput)
   {	QString sDebug  = QString( "            Table Lookup '%1'  Param(s):  " ).arg( m_name );
      for ( int param = 0; param < m_nParams; param++ )
      {	if (param > 0)
				sDebug += ",  ";
			sDebug += QString("%1").arg( QString::number(pfParams[ param ]) );
      }
      BEMPX_WriteLogFile( sDebug );
   }

   // loop over all rows of the table
   assert( m_rowIndepCells.size()== 0 );     // storage of row look-up data
   for ( int i = 0; ( i < (int) m_data.size() ) && !found; i++ )
   {
      bool bMatch = TRUE;
      // look for matches between all columns of idep vars and the pfParams argument
      for ( int param = 0; ( param < m_nParams ) && bMatch; param++ )
      {
			// SAC 10/25/98 - Implement "-99" independent variable values which always pass as matching
			// SAC 11/21/03 - Added similar "-99" mechanism allowing argument of table lookup function equalling -99 to match table record regardless of the independent's value
			// SAC 10/11/12 - revise for new table cell class
			assert( ((BEMTableCell*)m_data[ i ])[ param ].isFloat() || ((BEMTableCell*)m_data[ i ])[ param ].isWildCard() || ((BEMTableCell*)m_data[ i ])[ param ].isMissing() );
			if ( ((BEMTableCell*)m_data[ i ])[ param ].isWildCard() || ((BEMTableCell*)m_data[ i ])[ param ].isMissing() || pfParams[ param ] == -99 )
         {	//bMatch = TRUE;
			}
			else if ( !((BEMTableCell*)m_data[ i ])[ param ].isMatch( pfParams[ param ] ) )
				bMatch = FALSE;
      }   
      // if this row's indep vars match pfParams, then we've found the value
      if ( bMatch && ((BEMTableCell*)m_data[ i ])[ iCol + m_nParams - 1 ].isFloat() )
      {
         found = TRUE;
         *pfValue = (double) ((BEMTableCell*)m_data[ i ])[ iCol + m_nParams - 1 ].getValue();
      }
   }

   return found;
}


bool BEMTable::GrabRecord( int i1RecNum, int iCol, double* pdValue, bool bIgnoreIndepCols /*=false*/ )  //, BOOL bVerboseOutput /*=FALSE*/ )  // SAC 5/15/12
{
   bool found = FALSE;

//   if (bVerboseOutput)
//   {  QString sDebug;
//      sDebug.Format( "            Table Record Grab '%s'  Rec#: %d  Col: %d", m_name, i1RecNum, iCol );
//      BEMPX_WriteLogFile( sDebug );
//   }

   /*assert( (bIgnoreIndepCols || m_rowIndepCells.size()==0) );*/		bIgnoreIndepCols;     // storage of row look-up data
	if (i1RecNum <= (int) m_data.size() && iCol <= m_nCols && ((BEMTableCell*)m_data[ i1RecNum-1 ])[ iCol + m_nParams - 1 ].isFloat())
	{
      found = TRUE;
      *pdValue = ((BEMTableCell*)m_data[ i1RecNum-1 ])[ iCol + m_nParams - 1 ].getValue();
	}
   return found;
}


BEMTableCell* BEMTable::LookupCell( int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
											vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL /*bVerboseOutput=FALSE*/ )  // SAC 10/17/12
{	BEMTableCell* pRetCell = NULL;
	int iIndep, i0Col, iRow;
	vector<bool> iaIndepsChecked;   // array of bools indicating whether or not each independent (lookup argument) value was checked for matches either via row- or column-specified independents
	for (iIndep=0; iIndep < (int) saIndepNames.size(); iIndep++)
		iaIndepsChecked.push_back( false );

	int iTotNumCols = (int) m_columnTitles.size();
	bool bLookupValid = false;  // SAC 9/5/13 - new variable designed to ensure that at least SOME independent checking found matches
	// FIRST select the COLUMN by evaluating independents defined in the rows immediately below the top column titles
	string sColTtl = (iRetColID <= iTotNumCols ? m_columnTitles[iRetColID-1] : "");
	//assert( iRetColID > 1 );  - SAC 9/5/13 - removed assert as mods being made to allow return of columns of data to LEFT of those checked as independents...
	int i0SelCol = (m_rowTitles.size() > 0 ? -1 : iRetColID-1);
	// iRetColID should be the FIRST column w/ the selected column name, so no need to check prior columns
	for (i0Col=iRetColID-1; (i0SelCol < 0 && i0Col < iTotNumCols); i0Col++)
		if (i0Col==iRetColID-1 || boost::iequals( m_columnTitles[i0Col], sColTtl ))
		{	bool bColMatch = true;
			for (iRow=0; (i0Col > 0 && bColMatch && iRow < (int) m_rowTitles.size()); iRow++)
			{	bool bFoundIndep = false;
				for (iIndep=0; (!bFoundIndep && iIndep < (int) saIndepNames.size()); iIndep++)
					if (boost::iequals( m_rowTitles[iRow], saIndepNames[iIndep] ))
					{	bFoundIndep = true;
						iaIndepsChecked[iIndep] = true;
						//BEMTableCell* pRowIndepCell = (BEMTableCell*) m_rowIndepCells[i0Col-1];			assert( pRowIndepCell );
					// SAC 3/10/13 - replaced above line w/ following 3 lines to fix bug where RowIndepCell not properly accessed
						BEMTableCell* pRowIndepCellGrp = (BEMTableCell*) m_rowIndepCells[iRow];				assert( pRowIndepCellGrp );
						if (pRowIndepCellGrp)
						{	BEMTableCell* pRowIndepCell = &pRowIndepCellGrp[i0Col-1];								assert( pRowIndepCell );
							if (pRowIndepCell)
							{	if (pRowIndepCell->isWildCard() || pRowIndepCell->isMissing())
								{	// automatic match
									bLookupValid = true;  // SAC 9/5/13
								}
								else if (pRowIndepCell->isFloat() && baIndepNumeric[iIndep])
								{	bColMatch = pRowIndepCell->isMatch( faIndepValues[iIndep] );
									if (bColMatch)
										bLookupValid = true;  // SAC 9/5/13
								}
								else if (pRowIndepCell->isString() && !baIndepNumeric[iIndep])
								{	bColMatch = pRowIndepCell->isMatch( saIndepStrings[iIndep] );
									if (bColMatch)
										bLookupValid = true;  // SAC 9/5/13
								}
								else
								{	// incompatible row conditions vs. lookup arguments
									assert( FALSE );
									if (baIndepNumeric[iIndep])
										sErrMsg = boost::str( boost::format( "Incompatible table row (%s %s) and lookup (numeric %g) data" ) % m_rowTitles[iRow] % pRowIndepCell->cellTypeDescription() % faIndepValues[iIndep] );
									else
										sErrMsg = boost::str( boost::format( "Incompatible table row (%s %s) and lookup (string '%s') data" ) % m_rowTitles[iRow] % pRowIndepCell->cellTypeDescription() % saIndepStrings[iIndep] );
									bColMatch = false;
								}
							}
						}
					}
				assert( bFoundIndep );  // if not, then input argument did not
			}
			if (bColMatch)
				i0SelCol = i0Col;
		}
	assert( i0SelCol >= 0 );

	// NOW that we have a column selected, search for the ROW to return data from
	// (looking only at rows to the LEFT of the row selected for return)
	bool bErrorEncountered = false;  // SAC 9/5/13
	if (i0SelCol >= 0)
	{	// first develop mapping of independents to table columns
		vector<int> iaIndepColIdx;
		for (iIndep=0; iIndep < (int) saIndepNames.size(); iIndep++)
		{	iaIndepColIdx.push_back( -1 );
			// SAC 9/5/13 - modified code to search ALL columns for independents to return - allowing for return of data to LEFT of independent column(s)
			//for (i0Col=0; i0Col < i0SelCol; i0Col++)
			for (i0Col=0; i0Col < iTotNumCols; i0Col++)
				if (boost::iequals( m_columnTitles[i0Col], saIndepNames[iIndep] ))	// this will causing checking of indep w/ only the FIRST column matching the indep name when selecting the row of data to return
				{	iaIndepColIdx[iIndep] = i0Col;
					break;
				}
			// check to make sure each independent has a valid column index - SAC 9/5/13
			// NOT A VALID CHECK - because this error gets triggered when independents are resolved via records listed @ top of table differentiating colums w/ same title
			if (!iaIndepsChecked[iIndep] && iaIndepColIdx[iIndep] < 0)
			{	sErrMsg = boost::str( boost::format( "No table column (or header row) found to be consistent with independent '%s'" ) % saIndepNames[iIndep] );
				bErrorEncountered = true;
				break;
			}
		}

	   for (iRow = 0; (!bErrorEncountered && pRetCell == NULL && iRow < (int) m_data.size()); iRow++)
		{	bool bRowMatches = true;
			for (iIndep=0; (!bErrorEncountered && bRowMatches && iIndep < (int) iaIndepColIdx.size()); iIndep++)  // SAC 1/10/13 - fixed bug where first non-matching cell not blowing out of loop over independents
				if (iaIndepColIdx[iIndep] >= 0)
				{	BEMTableCell* pRowIndepCell = &((BEMTableCell*) m_data[iRow])[ iaIndepColIdx[iIndep] ];				assert( pRowIndepCell );
					if (pRowIndepCell)
					{	if (pRowIndepCell->isWildCard() || pRowIndepCell->isMissing())
						{	// automatic match
							bLookupValid = true;  // SAC 9/5/13
						}
						else if (pRowIndepCell->isFloat() && baIndepNumeric[iIndep])
						{	bRowMatches = pRowIndepCell->isMatch( faIndepValues[iIndep] );
							if (bRowMatches)
								bLookupValid = true;  // SAC 9/5/13
						}
						else if (pRowIndepCell->isString() && !baIndepNumeric[iIndep])
						{	bRowMatches = pRowIndepCell->isMatch( saIndepStrings[iIndep] );
							if (bRowMatches)
								bLookupValid = true;  // SAC 9/5/13
						}
						else
						{	// incompatible row conditions vs. lookup arguments
							//assert( FALSE );
							bErrorEncountered = true;  // SAC 9/5/13
							if (sErrMsg.length() < 1)
							{	if (baIndepNumeric[iIndep])
									sErrMsg = boost::str( boost::format( "Incompatible table row (#%d %s) and lookup (numeric %g) data" ) % (iRow+1) % pRowIndepCell->cellTypeDescription() % faIndepValues[iIndep] );
								else
									sErrMsg = boost::str( boost::format( "Incompatible table row (#%d %s) and lookup (string '%s') data" ) % (iRow+1) % pRowIndepCell->cellTypeDescription() % saIndepStrings[iIndep] );
							}
							bRowMatches = false;
						}
					}
				}
			//assert( bRowMatches );

			if (bRowMatches && bLookupValid)
			{	// FOUND MATCHING ROW
				pRetCell = &((BEMTableCell*) m_data[iRow])[ i0SelCol ];
				switch (pRetCell->getCellType())
				{	case BEMTCT_Error     :	{	//string sCellStr = pRetCell->getString();		assert( sCellStr.length() > 0 );
														//sErrMsg = GetErrorMessage( sCellStr );
														sErrMsg = GetErrorMessage( pRetCell->getMessageID() );
													}	break;
				   case BEMTCT_Warning   :	{	//string sCellStr = pRetCell->getString();		assert( sCellStr.length() > 0 );
														//sErrMsg = GetWarningMessage( sCellStr );
														sErrMsg = GetWarningMessage( pRetCell->getMessageID() );
													}	break;
				}
			}
		}
		if (pRetCell == NULL && sErrMsg.length() < 1)
			sErrMsg = "Table row match not found";
	}
	else if (sErrMsg.length() < 1)
		sErrMsg = "Table column match not found";

	return pRetCell;
}

std::string	BEMTable::GetErrorMessage(   string& sErrorLabel )
{	assert( sErrorLabel.length() > 0 );
	for (int i=0; i < (int) m_errorLabels.size(); i++)
		if (boost::iequals( m_errorLabels[i], sErrorLabel ))
		{	assert( (int) m_errorMessages.size() > i );
			if ((int) m_errorMessages.size() > i)
				return m_errorMessages[i];
			break;
		}
	return "";
}

std::string	BEMTable::GetErrorMessage( int i0MsgIndex )
{	assert( i0MsgIndex >= 0 && i0MsgIndex < (int) m_errorLabels.size() );
	if (i0MsgIndex >= 0 && i0MsgIndex < (int) m_errorLabels.size())
		return m_errorMessages[i0MsgIndex];
	return "";
}

std::string	BEMTable::GetWarningMessage( string& sWarningLabel )
{	assert( sWarningLabel.length() > 0 );
	for (int i=0; i < (int) m_warningLabels.size(); i++)
		if (boost::iequals( m_warningLabels[i], sWarningLabel ))
		{	assert( (int) m_warningMessages.size() > i );
			if ((int) m_warningMessages.size() > i)
				return m_warningMessages[i];
			break;
		}
	return "";
}
std::string	BEMTable::GetWarningMessage( int i0MsgIndex )
{	assert( i0MsgIndex >= 0 && i0MsgIndex < (int) m_warningMessages.size() );
	if (i0MsgIndex >= 0 && i0MsgIndex < (int) m_warningMessages.size())
		return m_warningMessages[i0MsgIndex];
	return "";
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTable Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a single table data file into this instance.
//   
// Arguments ----------------------------------------------------------------
//   QFile& errorFile : a file to write error message to.
//   
// Return Value -------------------------------------------------------------
//   TRUE if table read and stored without any errors, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   pseudocode:
//     open the table file
//     loop over rows
//        loop over columns
//           read each value
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMTable::Read( QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( m_fileName.toLocal8Bit().constData(), BEMTextIO::load );

      // write message to error file indicating that we are reading this table file
      QString readMsg = QString("Reading table file: %1\n\n").arg( m_fileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

		BOOL bInBetweenReadingRecords=TRUE;  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
//      float* newData = NULL;
      BEMTableCell* newData = NULL;
      try
      {
         try
         {
            int row = 0;
				double fVal;
            // loop over all rows of data
            while ( TRUE ) // EOF handled in catch block 
            {
//#ifdef _DEBUG
//               readMsg.Format( "%d", row+1 );
//               readMsg = "   record: " + readMsg;
//               readMsg += "\n";
//               errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
//#endif
               // create the storage area for this row of data
               newData = new BEMTableCell[ m_nParams + m_nCols ];
               // loop over all columns of data, reading each into newData
               for ( int col = 0; col < ( m_nCols + m_nParams ); col++ )
               //{	file.Double( newData[ col ], 12 );
               {	file.Double( fVal, 12 );
						newData[ col ].setValue( fVal );

               	if (col == 0)
							bInBetweenReadingRecords = FALSE;  // SAC 6/25/12
                  if (col < ( m_nCols + m_nParams -1))
							file.PostReadToken();  // don't read past final float in record until record data added to m_data and bInBetweenReadingRecords flag set
               }
               m_data.push_back( newData );  // add this row of data to m_data array
					bInBetweenReadingRecords = TRUE;  // SAC 6/25/12
               row++;
					file.PostReadToken();  // added final PostReadToken here now that this record's data is stored away and we have logged that we are in between record reads

// no column or row title stuff in original Read() routine
//	vector<string> m_columnTitles;
//	vector<string> m_rowTitles;
//	vector<int> 	m_iaRowConditions;
            }
         }
//         catch( BEMTextioException& err )
//         {
//            if ( err->m_cause == BEMTextioException::endOfFile )
//               // delete the last allocation of new data which was never populated
//               delete [] newData; // we're done, no problem
////            else
////               THROW_LAST();
//         }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}
      }
//      catch( BEMTextioException& err )
//      {
//			if (bInBetweenReadingRecords)  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
//			{	if (newData)  // delete the last allocation of new data which was never populated
//               delete [] newData; // we're done, no problem
//			}
//			else
//			{	QString msg = QString("Error Reading table: ") + m_name + QString( "\n" );
//         	msg += QString("From File: ") + m_fileName + QString( "\n" );
//         	msg += QString("\n\t") + QString( err->m_strError ) + QString("\n") + QString("\n");
//
//         	errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
//         	bRetVal = FALSE;
//
//         	BEMMessageBox( err->m_strError, NULL, 2 /*warning*/ );
//         	THROW_LAST();
//			}
//      }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}
   }
//   catch( CFileException, error )
//   {
//      QString msg = QString( "Error opening file: " ) + m_fileName;
//      BEMMessageBox( msg, "", 2 /*warning*/ );
//
//      errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
//      bRetVal = FALSE;
//   }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}

   return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

// SAC 10/11/12 - routine to read in new-format table from CSV file
bool BEMTable::ReadV2( const char* fileName, QFile& errorFile, int& iNextTableRecord )  // SAC 2/7/14
{
   bool bRetVal = TRUE;
	QString sLogMsg;
   try
   {  // open file
      BEMTextIO file( fileName, BEMTextIO::load );

      // write message to error file indicating that we are reading this table file
      QString readMsg;
		if (iNextTableRecord > 1)
			readMsg = QString( "Reading table file (beginning @ record %1):  %2\n\n" ).arg( QString::number(iNextTableRecord), fileName );
		else
			readMsg = QString( "Reading table file:  %1\n\n" ).arg( fileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

		bool bTableReadComplete = false;
		while (--iNextTableRecord >= 0)
			file.GetLine();
		iNextTableRecord = -1;

		BOOL bInBetweenReadingRecords=TRUE;  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
      BEMTableCell* pNewData = NULL;
      try
      {
         try
         {
				QString sField = file.ReadCSVString( TRUE /*bReadToFollowingDelimeter*/, TRUE /*bSkipBlankEntries*/, NULL /*BOOL* pbStrQuoted*/ );
				int iFound = sField.indexOf( "TABLE" );		assert( iFound >= 0 );
				if (iFound < 0)	// SAC 1/19/14 - added error message output when 'TABLE' not first field of data in table
				{	readMsg = QString( "\t'TABLE' entry not found to be first (uncommented) data (on line %1) in table file:  %2\n\n" ).arg( QString::number( file.GetLineCount() ), fileName );
					errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
					bRetVal = FALSE;
				}
				else if (sField.indexOf( "ENDTABLE" ) < 0)
				{	sField = sField.right( sField.length() - iFound - 5 );
					TrimLeft( sField );
					iFound = sField.indexOf( ' ' );			assert( iFound < 0 || iFound > 2 );
					if (iFound < 0 || iFound > 2)
					{	if (iFound > 2)
							sField = sField.left( iFound );
						m_name		= sField;
						m_fileName	= fileName;
						file.GetLine();
						file.Advance( FALSE /*bSkipLeadingDelimeters*/ );
					   int iColLabelLine = file.GetLineCount();
						vector<bool> baIsDataColumn;	// allows for gaps in data columns (column in table that are ignored in terms of data read from table)
						int iCurLine = iColLabelLine;
						int iLastDataCol = -1;
						int iFieldIdx = -1;
						bInBetweenReadingRecords=FALSE;
						while (iCurLine == iColLabelLine)
						{
							sField = file.ReadCSVString( TRUE /*bReadToFollowingDelimeter*/, FALSE /*bSkipBlankEntries*/, NULL /*BOOL* pbStrQuoted*/ );
							iCurLine = file.GetLineCount();
							if (iCurLine == iColLabelLine)
							{	TrimLeft( sField );			TrimRight( sField );
								iFieldIdx++;
								if (sField.isEmpty())
									baIsDataColumn.push_back( false );
								else
								{	baIsDataColumn.push_back( true );
									iLastDataCol = iFieldIdx;
									m_columnTitles.push_back( (const char*) sField.toLocal8Bit().constData() );
								}
							}
							else
								file.SkipToBeginningOfLine();	// SAC 10/19/12
						}
						bInBetweenReadingRecords=TRUE;
						// file should be positioned at beginning of line FOLLOWING the column label line
						file.Advance( FALSE /*bSkipLeadingDelimeters*/ );	// should skip past comment lines
						if (m_columnTitles.size() < 2)
						{	sLogMsg = QString( "Only one column title found in table (on line %1)." ).arg( QString::number(file.GetLineCount()-1) );						assert( FALSE );
						   bRetVal = FALSE;
						}
						else
						{
							m_nParams = 0;
							m_nCols   = m_columnTitles.size();
							int i=0;
							//BOOL bRecordMayBeIndepCheckRow = TRUE;
							BOOL bFirstDataRecordRead = FALSE;
							QStringList saFields;  //, saErrorCells, saWarningCells;
							while (bRetVal && !file.FoundInCurrentLine( "ENDTABLE", 30 /*??-how many reord-leading chars do we expect ENDTABLE to be in-??*/ ))
							{
								saFields.clear();
								bInBetweenReadingRecords=FALSE;
								int iThisDataRow = file.GetLineCount();
								iCurLine = iThisDataRow;
								for (i=0; (iCurLine == iThisDataRow && i <= iLastDataCol); i++)
								{	sField = file.ReadCSVString( TRUE /*bReadToFollowingDelimeter*/, FALSE /*bSkipBlankEntries*/, NULL /*BOOL* pbStrQuoted*/ );
									iCurLine = file.GetLineCount();
									if (baIsDataColumn[i] && iCurLine == iThisDataRow)
									{	TrimLeft( sField );			TrimRight( sField );
										saFields.push_back( sField );
									}
								}
								if (iCurLine == iThisDataRow)
								{	file.SkipToEndOfLine();
									file.GetLine();
								}
								else
									file.SkipToBeginningOfLine();
								file.Advance( FALSE /*bSkipLeadingDelimeters*/ );  // in case the next record begins w/ a comment
								// file now positioned @ beginning of NEXT row of data
								if (saFields.size() < m_nCols)
								{	assert( FALSE );	// partial record of fields ??? just fill remaining fields w/ blank/missing data ???
									while (saFields.size() < m_nCols)
										saFields.push_back( "" );
								}

								// now PROCESS the fields in this record...
								BOOL bIsIndepCellsRow = FALSE;
								BOOL bAddRecord = FALSE;
               			pNewData = NULL;   // new BEMTableCell[ m_nCols ];
								int iNumColsData = m_nCols;
								if (!bFirstDataRecordRead && !saFields[0].isEmpty() && saFields[0][saFields[0].length()-1]=='=')
								{	// This row contains INDEPENDENT values to be checked to determine a variable return column
									bIsIndepCellsRow = TRUE;
									//saFields[0] = saFields[0].left( saFields[0].length()-1 );
									TrimRight( saFields[0], " \t=" );
									if (saFields[0].isEmpty())
									{	sLogMsg = QString( "Invalid label for row of independent look-up values (on line %1)." ).arg( QString::number(file.GetLineCount()-1) );			assert( FALSE );
									   bRetVal = FALSE;		// throw an error here
									}
									else
									{	iNumColsData--;
										m_rowTitles.push_back( (const char*) saFields[0].toLocal8Bit().constData() );
										saFields.removeAt(0);
									}
								}
								else
								{	bFirstDataRecordRead = TRUE;
									if (!saFields[0].isEmpty() && saFields[0][saFields[0].length()-1]=='=')
									{	sLogMsg = QString( "Label row w/ independent look-up values found AFTER having read a row of look-up DATA (on line %d)." ).arg( QString::number(file.GetLineCount()-1) );	assert( FALSE );
									   bRetVal = FALSE;		// throw an error here
									}
								}
               			
								if (bRetVal)
								{	pNewData = new BEMTableCell[ iNumColsData ];
									bAddRecord = TRUE;
									for (i=0; (bRetVal && bAddRecord && i < iNumColsData); i++)
									{	if (saFields[i].length()==1 && saFields[i].indexOf('*')==0)
           								pNewData[i].setWildCard();
										else if (saFields[i].isEmpty())
           								pNewData[i].setMissing();
										else if (!saFields[i].left(5).compare( "Error", Qt::CaseInsensitive ) || !saFields[i].left(7).compare( "Warning", Qt::CaseInsensitive ))
										{	assert( !bIsIndepCellsRow );  // error/warning labels should not be found in row indep look-up rows
											int iMsgType = (!saFields[i].left(5).compare( "Error", Qt::CaseInsensitive ) ? BEMTCT_Error : BEMTCT_Warning);
											if (i==0)
											{	// if this is a record where the user is defining an error/warning message, then the beginning of the message may be present toward the end of saFields[0], we truncate it @ the first spc/tab
												int iTruncLen = saFields[i].indexOf(' ');
												if (iTruncLen < 0 || (saFields[i].indexOf('\t') > 0 && saFields[i].indexOf('\t') < iTruncLen))
													iTruncLen = saFields[i].indexOf('\t');
												if (iTruncLen > 0)
													saFields[i] = saFields[i].left( iTruncLen );
											}
											int iGetMsgIndex = AddOrReturnLabelIndex( iMsgType, saFields[i].toLocal8Bit().constData() );				assert( iGetMsgIndex >= 0 );
											if (i==0)
											{	// this is NOT a record w/ table cells, but rather a row w/ error/warning messages
												bAddRecord = FALSE;
																								assert( saFields.size() > i+1 );
												QString sMsg = saFields[i+1];			assert( !sMsg.isEmpty() );
												//	QString sMsg = file.GetCurrentLine();
												//	int iMsgLabelIdx = sMsg.indexOf( saFields[i] );			assert( iMsgLabelIdx >= 0 );
												//	if (iMsgLabelIdx >= 0)
												//		sMsg = sMsg.right( sMsg.length() - iMsgLabelIdx - saFields[i].length() );
												//	TrimLeft( sMsg );
												ProcessStringForQuoteAndComment( sMsg );
												if (iGetMsgIndex >= 0)
												{	SetMessage( iMsgType, iGetMsgIndex, sMsg.toLocal8Bit().constData() );
													break;
												}
											}
											else
            								pNewData[i].setMessage( iMsgType, iGetMsgIndex );
										}
										else
										{	QString sThisFld = saFields[i];
											int iCond = TrimBEMCondition( sThisFld );    // returns index of condition present at the BEGINNING of the string AND removes condition (and any following spaces) from the QString
											if (iCond >= 0 && StringExclusivelyNumber( sThisFld ))
            								pNewData[i].setValue( atof( sThisFld.toLocal8Bit().constData() ), iCond );
											else if (StringExclusivelyNumber( sThisFld ))
            								pNewData[i].setValue( atof( sThisFld.toLocal8Bit().constData() ) );
											else
											{	assert( iCond < 0 );		// assert here means there is a condition listed prior to a character string field - which MAY be valid for enumeration strings that include a preceding condition symbol...
            								pNewData[i].setString( saFields[i].toLocal8Bit().constData() );
											}
										}
									}
								}
               			
								if (bAddRecord)
								{	if (bIsIndepCellsRow)
		         			   	m_rowIndepCells.push_back( pNewData );  // add this row of data to m_rowIndepCells array
									else
		         			   	m_data.push_back( pNewData );  // add this row of data to m_data array
								}
								else if (pNewData)
									delete [] pNewData;
								pNewData = NULL;
								bInBetweenReadingRecords=TRUE;
							}	// end of: WHILE searching for ENDTABLE

							if (bRetVal)  // SAC 2/7/14
							{	bTableReadComplete = true;
								do
								{	sField = file.ReadCSVString( TRUE /*bReadToFollowingDelimeter*/, TRUE /*bSkipBlankEntries*/, NULL /*BOOL* pbStrQuoted*/ );
								} while (sField.indexOf( "NDTABLE" ) >= 0 || !sField.compare(","));
								if (sField.indexOf( "TABLE" ) >= 0)
								   iNextTableRecord = file.GetLineCount();
							}

						}	// end of: if valid number of column titles found
					}
					else
						bRetVal = FALSE;
				}
				else
					bRetVal = FALSE;
         }
//         catch( BEMTextioException, err )
//         {
//            if ( err->m_cause == BEMTextioException::endOfFile || bTableReadComplete )
//				{	if (pNewData)  // delete the last allocation of new data which was never populated
//   	            delete [] pNewData; // we're done, no problem
//				}
//            else
//               THROW_LAST();
//         }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}
      }
//      catch( BEMTextioException, err )
//      {
//			if (bInBetweenReadingRecords || bTableReadComplete)  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
//			{	if (pNewData)  // delete the last allocation of new data which was never populated
//               delete [] pNewData; // we're done, no problem
//			}
//			else
//			{	QString msg = QString("Error Reading table: ") + m_name + QString( "\n" );
//         	msg += QString("From File: ") + m_fileName + QString( "\n" );
//         	msg += QString("\n\t") + QString( err->m_strError ) + QString("\n") + QString("\n");
//
//         	errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
//         	bRetVal = FALSE;
//
//         	BEMMessageBox( err->m_strError, NULL, 2 /*warning*/ );
//         	THROW_LAST();
//			}
//      }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}
   }
//   catch( CFileException, error )
//   {
//      QString msg = QString( "Error opening file: " ) + m_fileName;
//      BEMMessageBox( msg, "", 2 /*warning*/ );
//
//      errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
//      bRetVal = FALSE;
//   }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}

	if (!sLogMsg.isEmpty())
	{	QString msg;
		msg = QString( "Error Reading table: '%s'  from file: '%s'\n\t%s\n\n" ).arg( m_name, m_fileName, sLogMsg );
		errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
	}

   return bRetVal;
}

// SAC 10/12/12 - routine to read in new-format table from Rules text file
bool BEMTable::ReadV2( BEMTextIO& file, QFile& errorFile )
{
   bool bRetVal = TRUE;
	BOOL bInBetweenReadingRecords=TRUE;  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
   BEMTableCell* pNewData = NULL;
   try
   {  // file already opened - launch directly into reading the table and then return w/out closing the file
		file.Advance();
	   int iColLabelLine = file.GetLineCount();
		int iCurLine = iColLabelLine;
		vector<int> iaColBegins, iColEnds;
		QString sColTitle;
		bInBetweenReadingRecords=FALSE;
		while (iCurLine == iColLabelLine)
		{	iaColBegins.push_back( file.GetCharacterIndex() );
			sColTitle.clear();
			//sColTitle = file.ReadString( FALSE /*bReadPastEOL*/ );
			sColTitle = file.ReadToken( TRUE /*bAllowLeadingDigit*/, FALSE /*bSkipLeadingDelimeters*/, TRUE /*bAllowMidHyphen*/ );		assert( !sColTitle.isEmpty() );
			m_columnTitles.push_back( sColTitle.toLocal8Bit().constData() );
			file.Advance();
		   iCurLine = file.GetLineCount();
		}
		bInBetweenReadingRecords=TRUE;

		if (m_columnTitles.size() < 2)
		{	assert( FALSE );
		   bRetVal = FALSE;
		}
		else
		{
			m_nParams = 0;
			m_nCols   = iaColBegins.size();
			int i=0;
			for (; i < m_nCols; i++)
			{	if (i == (m_nCols-1))
					iColEnds.push_back( iaColBegins[i] + 100 );
				else
					iColEnds.push_back( iaColBegins[i+1] - 1 );
			}

			//BOOL bRecordMayBeIndepCheckRow = TRUE;
			BOOL bFirstDataRecordRead = FALSE;
			QStringList saFields;  //, saErrorCells, saWarningCells;
			while (bRetVal && !file.FoundInCurrentLine( "ENDTABLE", iaColBegins[0]+9 ))
			{
				bInBetweenReadingRecords=FALSE;
			   int iParseRetVal = file.ParseColumnarRecord( saFields, iaColBegins, iColEnds, "ENDTABLE" );
				if (iParseRetVal == -1)
					break;  // at EOF
				else if (iParseRetVal != m_nCols)
				{	assert( FALSE );		// INCORRECT number of fields in record
				   bRetVal = FALSE;		// throw an error when unexpected number of fields found on record - or simply ignore this record and move on to next ??
				}
				else
				{	BOOL bIsIndepCellsRow = FALSE;
					BOOL bAddRecord = FALSE;
               pNewData = NULL;   // new BEMTableCell[ m_nCols ];
					int iNumColsData = m_nCols;
					if (!bFirstDataRecordRead && !saFields[0].isEmpty() && saFields[0][saFields[0].length()-1]=='=')
					{	// This row contains INDEPENDENT values to be checked to determine a variable return column
						bIsIndepCellsRow = TRUE;
						//saFields[0] = saFields[0].left( saFields[0].length()-1 );
						TrimRight( saFields[0], " \t=" );
						if (saFields[0].isEmpty())
						{	assert( FALSE );		// bogus label for row of independent look-up values
						   bRetVal = FALSE;		// throw an error here
						}
						else
						{	iNumColsData--;
							m_rowTitles.push_back( saFields[0].toLocal8Bit().constData() );
							saFields.removeAt(0);
						}
					}
					else
					{	bFirstDataRecordRead = TRUE;
						if (!saFields[0].isEmpty() && saFields[0][saFields[0].length()-1]=='=')
						{	assert( FALSE );		// label for row of independent look-up values found AFTER having read a row of look-up DATA
						   bRetVal = FALSE;		// throw an error here
						}
					}

					if (bRetVal)
					{	pNewData = new BEMTableCell[ iNumColsData ];
						bAddRecord = TRUE;
						for (i=0; (bRetVal && bAddRecord && i < iNumColsData); i++)
						{	if (saFields[i].length()==1 && saFields[i].indexOf('*')==0)
           					pNewData[i].setWildCard();
							else if (saFields[i].isEmpty())
           					pNewData[i].setMissing();
							else if (!saFields[i].left(5).compare( "Error", Qt::CaseInsensitive ) || !saFields[i].left(7).compare( "Warning", Qt::CaseInsensitive ))
							{	assert( !bIsIndepCellsRow );  // error/warning labels should not be found in row indep look-up rows
								int iMsgType = (!saFields[i].left(5).compare( "Error", Qt::CaseInsensitive ) ? BEMTCT_Error : BEMTCT_Warning);
								if (i==0)
								{	// if this is a record where the user is defining an error/warning message, then the beginning of the message may be present toward the end of saFields[0], we truncate it @ the first spc/tab
									int iTruncLen = saFields[i].indexOf(' ');
									if (iTruncLen < 0 || (saFields[i].indexOf('\t') > 0 && saFields[i].indexOf('\t') < iTruncLen))
										iTruncLen = saFields[i].indexOf('\t');
									if (iTruncLen > 0)
										saFields[i] = saFields[i].left( iTruncLen );
								}
								int iGetMsgIndex = AddOrReturnLabelIndex( iMsgType, saFields[i].toLocal8Bit().constData() );				assert( iGetMsgIndex >= 0 );
								if (i==0)
								{	// this is NOT a record w/ table cells, but rather a row w/ error/warning messages
									bAddRecord = FALSE;
									QString sMsg = file.GetCurrentLine();
									int iMsgLabelIdx = sMsg.indexOf( saFields[i] );			assert( iMsgLabelIdx >= 0 );
									if (iMsgLabelIdx >= 0)
										sMsg = sMsg.right( sMsg.length() - iMsgLabelIdx - saFields[i].length() );
									TrimLeft( sMsg );
									ProcessStringForQuoteAndComment( sMsg );
									if (iGetMsgIndex >= 0)
									{	SetMessage( iMsgType, iGetMsgIndex, sMsg.toLocal8Bit().constData() );
										break;
									}
								}
								else
            					pNewData[i].setMessage( iMsgType, iGetMsgIndex );
							}
							else
							{	QString sThisFld = saFields[i];
								int iCond = TrimBEMCondition( sThisFld );    // returns index of condition present at the BEGINNING of the string AND removes condition (and any following spaces) from the QString
								if (iCond >= 0 && StringExclusivelyNumber( sThisFld ))
            					pNewData[i].setValue( atof( sThisFld.toLocal8Bit().constData() ), iCond );
								else if (StringExclusivelyNumber( sThisFld ))
            					pNewData[i].setValue( atof( sThisFld.toLocal8Bit().constData() ) );
								else
								{	assert( iCond < 0 );		// assert here means there is a condition listed prior to a character string field - which MAY be valid for enumeration strings that include a preceding condition symbol...
            					pNewData[i].setString( saFields[i].toLocal8Bit().constData() );
								}
							}
						}
					}

					if (bAddRecord)
					{	if (bIsIndepCellsRow)
		            	m_rowIndepCells.push_back( pNewData );  // add this row of data to m_rowIndepCells array
						else
		            	m_data.push_back( pNewData );  // add this row of data to m_data array
					}
					else if (pNewData)
						delete [] pNewData;
					pNewData = NULL;

					bInBetweenReadingRecords = TRUE;
					file.GetLine();
					file.Advance();
				   iCurLine = file.GetLineCount();
				}
				bInBetweenReadingRecords = TRUE;
			}	// end of: while loop over each record in table
		}  // end of: if valid # of column titles
	}
//   catch( BEMTextioException, err )
//   {
//		if (bInBetweenReadingRecords)  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
//		{	if (pNewData)  // delete the last allocation of new data which was never populated
//            delete [] pNewData; // we're done, no problem
//		}
//		else
//		{	QString msg = QString("Error Reading v2 table: ") + m_name + QString( "\n" );
//      	msg += QString("From File: ") + m_fileName + QString( "\n" );
//      	msg += QString("\n\t") + QString( err->m_strError ) + QString("\n") + QString("\n");
//
//      	errorFile.write( msg.toLocal8Bit().constData(), msg.length() );
//      	bRetVal = FALSE;
//
//      	BEMMessageBox( err->m_strError, NULL, 2 /*warning*/ );
//      	THROW_LAST();
//		}
//   }
					catch (std::exception &e)
					{	std::cout << "unexpected exception " << e.what() << '\n';
					}
					catch (...)
					{	std::cout << "unexpected exception\n";
					}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTable Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads Table data from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to read the table data from
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMTable::Read( CryptoFile& file )
{
   int nRows;

   //int length;
   //file.Read( &length, sizeof( int ) );              // read length of table name
   //file.Read( (void*) m_name.toLocal8Bit().constData(), length ); // read table name
   file.ReadQString( m_name );

   file.Read( &nRows,      sizeof( int ) );   // read # rows of data
   file.Read( &m_nParams, sizeof( int ) );   // read # indep var columns
   file.Read( &m_nCols,   sizeof( int ) );   // read # dep var columns

	// reading of new column/row data
	int iCount, iNum, iCond;
	QString	str;
	string sstr;
   file.Read( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{  file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		m_columnTitles.push_back( sstr );
	}

	file.Read( &iCount, sizeof( int ) );
	for ( iNum = 0; iNum < iCount; iNum++ )
	{  //file.Read( &iCond, sizeof( int ) );
		file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		//m_iaRowConditions.push_back( iCond );
		m_rowTitles.push_back( sstr );
	}
	int		iType;
	double	fValue;
	for ( iNum = 0; iNum < (int) m_rowTitles.size(); iNum++ )
   {	BEMTableCell* pNewData = new BEMTableCell[ m_nParams + m_nCols - 1 ];
      for ( int col = 0; col < ( m_nCols + m_nParams - 1 ); col++ )
      {  file.Read( &iType , sizeof( int    ) );
         file.Read( &iCond , sizeof( int    ) );
         file.Read( &fValue, sizeof( double ) );
         file.ReadQString( str );
			pNewData[ col ].set( iType, fValue, str.toLocal8Bit().constData(), iCond );
      }
      m_rowIndepCells.push_back( pNewData );  // add this row of look-up data to m_rowIndepCells array
	}

   file.Read( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{  file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		m_errorLabels.push_back( sstr );
	}
   file.Read( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{  file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		m_errorMessages.push_back( sstr );
	}

   file.Read( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{  file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		m_warningLabels.push_back( sstr );
	}
   file.Read( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{  file.ReadQString( str );
		sstr = str.toLocal8Bit().constData();
		m_warningMessages.push_back( sstr );
	}

   // loop over all rows of table data
   for ( int row = 0; row < nRows; row++ )
   {
      // create the storage area for this row of data
      BEMTableCell* pNewData = new BEMTableCell[ m_nParams + m_nCols ];
      // loop over all columns of table data, reading each value in
      for ( int col = 0; col < ( m_nCols + m_nParams ); col++ )
      {
         file.Read( &iType , sizeof( int    ) );
         file.Read( &iCond , sizeof( int    ) );
         file.Read( &fValue, sizeof( double ) );
         file.ReadQString( str );
			pNewData[ col ].set( iType, fValue, str.toLocal8Bit().constData(), iCond );
      }
      m_data.push_back( pNewData );  // add this row of data to m_data array
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMTable Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Writes Table data to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CryptoFile& file : the binary encrypted ruleset file to write the table data to
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void BEMTable::Write( CryptoFile& file, QFile& errorFile )
#else
void BEMTable::Write( CryptoFile& file, QFile& /*errorFile*/ )
#endif
{
//   int length = m_name.length();
//   file.Write( &length, sizeof( int ) );              // write length of table name
//   file.Write( m_name.toLocal8Bit().constData(), length ); // write table name
	file.WriteQString( m_name );

   int nRows  = (int) m_data.size();
   file.Write( &nRows,     sizeof( int ) );  // write number of rows of data
   file.Write( &m_nParams, sizeof( int ) );  // write # indep var columns
   file.Write( &m_nCols,   sizeof( int ) );  // write # dep var columns

#ifdef _DEBUG
   QString dbgMsg = QString( " - %1 rows of data.\n" ).arg( QString::number(nRows) );
   errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
#endif

	// reading of new column/row data
	QString str;
	int iNum, iCond, iCount = m_columnTitles.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	str = m_columnTitles[iNum].c_str();
	   file.WriteQString( str );
	}

	iCount = m_rowTitles.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	//iCond = m_iaRowConditions[iNum];
		str = m_rowTitles[iNum].c_str();
	   //file.Write( &iCond, sizeof( int ) );
	   file.WriteQString( str );
	}
	int		iType;
	double	fValue;
   for ( int row = 0; row < iCount; row++ )
   {  BEMTableCell* pData = (BEMTableCell*)m_rowIndepCells[row];
      for ( int col = 0; col < ( m_nCols + m_nParams - 1 ); col++ )
      {  pData[ col ].get( iType, fValue, str, iCond );
		   file.Write( &iType , sizeof( int ) );
		   file.Write( &iCond , sizeof( int ) );
		   file.Write( &fValue, sizeof( double ) );
		   file.WriteQString( str );
		}
   }

	iCount = m_errorLabels.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	str = m_errorLabels[iNum].c_str();
	   file.WriteQString( str );
	}
	iCount = m_errorMessages.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	str = m_errorMessages[iNum].c_str();
	   file.WriteQString( str );
	}

	iCount = m_warningLabels.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	str = m_warningLabels[iNum].c_str();
	   file.WriteQString( str );
	}
	iCount = m_warningMessages.size();
   file.Write( &iCount, sizeof( int ) );
   for ( iNum = 0; iNum < iCount; iNum++ )
	{	str = m_warningMessages[iNum].c_str();
	   file.WriteQString( str );
	}

   // loop over all rows of table, writing each value to file
   for ( int row = 0; row < nRows; row++ )
   {
      BEMTableCell* pData = (BEMTableCell*)m_data[row];
      for ( int col = 0; col < ( m_nCols + m_nParams ); col++ )
      {  pData[ col ].get( iType, fValue, str, iCond );
		   file.Write( &iType , sizeof( int ) );
		   file.Write( &iCond , sizeof( int ) );
		   file.Write( &fValue, sizeof( double ) );
		   file.WriteQString( str );
		}
   }
}


/////////////////////////////////////////////////////////////////////////////

int BEMTable::AddOrReturnLabelIndex( int iLabelType, const char* szLabel )
{  int iRetVal = -1;
	int iNumLbls = (iLabelType == BEMTCT_Error ? m_errorLabels.size() : m_warningLabels.size());
	string strLbl = szLabel;
	for (int i=0; (iRetVal < 0 && i < iNumLbls); i++)
	{	if (boost::iequals( (iLabelType == BEMTCT_Error ? m_errorLabels[i] : m_warningLabels[i]), strLbl ))
			iRetVal = i;
	}
	if (iRetVal < 0)
	{	if (iLabelType == BEMTCT_Error)
		{	m_errorLabels.push_back( strLbl );
			iRetVal = m_errorLabels.size()-1;
		}
		else
		{	m_warningLabels.push_back( strLbl );
			iRetVal = m_warningLabels.size()-1;
		}
	}
	assert( iRetVal >= 0 );
	return iRetVal;
}

bool BEMTable::SetMessage( int iLabelType, int i0MsgIdx, const char* szMessage )
{	bool bRetVal = true;
	string strMsg = szMessage;
	switch (iLabelType)
	{	case BEMTCT_Error   : {	int iNumLbls = m_errorMessages.size();
										if (i0MsgIdx < iNumLbls)
										{	if (m_errorMessages[i0MsgIdx].length() > 0)
											{	assert( FALSE );
												bRetVal = false;
											}
											m_errorMessages[i0MsgIdx] = strMsg;
										}
										else
										{	for (int i=iNumLbls; i < i0MsgIdx; i++)
												m_errorMessages.push_back( "" );
											m_errorMessages.push_back( strMsg );
										}
									 }	break;
		case BEMTCT_Warning : {	int iNumLbls = m_warningMessages.size();
										if (i0MsgIdx < iNumLbls)
										{	if (m_warningMessages[i0MsgIdx].length() > 0)
											{	assert( FALSE );
												bRetVal = false;
											}
											m_warningMessages[i0MsgIdx] = strMsg;
										}
										else
										{	for (int i=iNumLbls; i < i0MsgIdx; i++)
												m_warningMessages.push_back( "" );
											m_warningMessages.push_back( strMsg );
										}
									 }	break;
	}
	return bRetVal;
}


int BEMTable::GetColumnIndex( const char* pszColTitle )	// 0 if no col titles exist, -1 if col title not found, otherwise 1-based index of column
{	int iRetVal = (m_columnTitles.size()==0 ? 0 : -1);
	string sColTitle = pszColTitle;
	for (int i=0; (iRetVal < 0 && i < (int) m_columnTitles.size()); i++)
	{	if (boost::iequals( m_columnTitles[i], sColTitle ))
			iRetVal = i+1;
	}
	return iRetVal;
}


std::string BEMTable::GetColumnName( int i1ColID )
{
	if (i1ColID > 0 && i1ColID <= (int) m_columnTitles.size())
		return m_columnTitles[i1ColID-1];
	else
	{	assert( FALSE );
	}
	return "";
}


//	/////////////////////////////////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// class BEMTableList
//	//
//	/////////////////////////////////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  ~BEMTableList()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Destructor - removes all tables from tablelist
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   None
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	BEMTableList::~BEMTableList()
//	{
//	   RemoveAll();
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  InitTables()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Initializes tablelist by removing all tables from the list
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   None
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	void BEMTableList::InitTables()
//	{
//	   RemoveAll();
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  RemoveAll()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Removes all tables from the list, deleting each as we go.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   None
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	void BEMTableList::RemoveAll()
//	{
//	   POSITION pos = GetHeadPosition();
//	
//	   while ( pos != NULL )
//	      delete (BEMTable*)GetNext( pos );
//	   CObList::RemoveAll();
//	}


/////////////////////////////////////////////////////////////////////////////
//
// Ruleset Function:  sddTable()
//
// Purpose ------------------------------------------------------------------
//   Adds a table to the list of tables.
//   
// Arguments ----------------------------------------------------------------
//   QString& name      : name of table
//   QString& fileName  : path/filename where table located
//   int      nParams   : # of independent (search) variable columns in table
//   int      nCols     : # of dependent (return value) variable columns in table
//   QFile&   errorFile : file to write error message to
//   
// Return Value -------------------------------------------------------------
//   Return value from BEMTable::Read( QFile& errorFile ) function.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleSet::addTable( const char* name, const char* fileName, int nParams, int nCols, QFile& errorFile )
{
	bool bRetVal = true;
	int iNextTableRecord = 1;  // SAC 2/7/14
	while (bRetVal && iNextTableRecord > 0)
   {	// create new table
   	BEMTable* newTable = new BEMTable( name, fileName, nParams, nCols );
   	// read new table data from file
		if (nParams==0 && nCols==0)
   	   bRetVal = newTable->ReadV2( fileName, errorFile, iNextTableRecord );
		else
   	{  bRetVal = newTable->Read( errorFile );
			iNextTableRecord = -1;
		}
   	// add new table to tablelist
   	m_tables.push_back( newTable );
	}
   return bRetVal;
}

bool RuleSet::addTable( const char* name, const char* fileName, BEMTextIO& file, QFile& errorFile )
{
   // create new table
   BEMTable* newTable = new BEMTable( name, fileName, 0 /*nParams*/, 0 /*nCols*/ );
   // read new table data from file
   bool bRetVal = newTable->ReadV2( file, errorFile );
   // add new table to tablelist
   m_tables.push_back( newTable );
   return bRetVal;
}

bool RuleSet::addTable( const char* fileName, QFile& errorFile )
{
	bool bRetVal = true;
	int iNextTableRecord = 1;  // SAC 2/7/14
	while (bRetVal && iNextTableRecord > 0)
   {	// create new table
   	BEMTable* newTable = new BEMTable( "TemporaryTableName", fileName, 0 /*nParams*/, 0 /*nCols*/ );
   	// read new table data from file
   	bRetVal = newTable->ReadV2( fileName, errorFile, iNextTableRecord );
   	// add new table to tablelist
   	m_tables.push_back( newTable );
	}
   return bRetVal;
}


//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  GetValue()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Performs a table look-up on the desired table contained in the tablelist.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   int    tableID    : 1-based integer index of desired table in tablelist
//	//   float* paramArray : array of independent var values to find matching table row
//	//   int    col        : column of dependent value to return
//	//   float* pfValue    : address of memory to populate with table look-up result
//	//   
//	// Return Value -------------------------------------------------------------
//	//   FALSE if the table corresponding to the tableID argument os not found,
//	//   else the return value of the BEMTable::Lookup() function.
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	bool BEMTableList::GetValue( int tableID, float* paramArray, int col, float* pfValue, BOOL bVerboseOutput )  // SAC 9/25/02
//	{
//	   bool bRetVal = FALSE;
//	   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
//	   if ( tableID > GetCount() || tableID < 1 )
//	      return bRetVal;
//	
//	   int id = 1;
//	   POSITION pos = GetHeadPosition();
//	   BEMTable* table = (BEMTable*)GetNext( pos );
//	   // loop over tablelist until desired table is found
//	   while ( id < tableID && pos != NULL )
//	   {
//	      table = (BEMTable*)GetNext( pos );
//	      id++;
//	   }
//	
//	   // perform look-up on desired table
//	   if ( table != NULL )
//		{	assert( table->m_columnTitles.size()==0 );  // should be OLD style table w/ no column titles
//	      bRetVal = table->Lookup( paramArray, col, pfValue, bVerboseOutput );  // SAC 9/25/02
//		}
//	
//	   return bRetVal;
//	}
//	
//	
//	BEMTableCell* BEMTableList::GetTableCell( int iTableID, int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
//												vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput /*=FALSE*/ )		// SAC 10/17/12
//	{	BEMTableCell* pRetCell = NULL;
//	   // return NULL right off the bat if the list does not contain as many table as tableID argument requires
//	   if ( iTableID > GetCount() || iTableID < 1 || iRetColID < 1 )
//		{	assert( FALSE );
//			if (iTableID > GetCount())
//				sErrMsg = boost::str( boost::format( "Table not found (table ID %d exceeds max %d)" ) % iTableID % GetCount() );
//			else if (iTableID < 1)
//				sErrMsg = boost::str( boost::format( "Table not found (table ID %d must be > 0)" ) % iTableID );
//			else if (iRetColID < 1)
//				sErrMsg = boost::str( boost::format( "Column not found (column ID %d must be > 0)" ) % iRetColID );
//	      return NULL;
//		}
//	
//	   int id = 1;
//	   POSITION pos = GetHeadPosition();
//	   BEMTable* table = (BEMTable*)GetNext( pos );
//	   // loop over tablelist until desired table is found
//	   while ( id < iTableID && pos != NULL )
//	   {
//	      table = (BEMTable*)GetNext( pos );
//	      id++;
//	   }
//	
//	   // perform look-up on desired table
//	   if ( table != NULL )
//		{	assert( (int) table->m_columnTitles.size() >= iRetColID );
//			if ((int) table->m_columnTitles.size() >= iRetColID)
//		      pRetCell = table->LookupCell( iRetColID, saIndepNames, saIndepStrings, faIndepValues, baIndepNumeric, sErrMsg, bVerboseOutput );
//		}
//	   return pRetCell;
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////
//	int BEMTableList::GetTableDimension( int tableID, BOOL bParams /*=TRUE*/ )   // SAC 12/19/05
//	{
//	   int iRetVal = -1;
//	   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
//	   if ( tableID > GetCount() || tableID < 1 )
//	      return iRetVal;
//	
//	   int id = 1;
//	   POSITION pos = GetHeadPosition();
//	   BEMTable* table = (BEMTable*)GetNext( pos );
//	   // loop over tablelist until desired table is found
//	   while ( id < tableID && pos != NULL )
//	   {
//	      table = (BEMTable*)GetNext( pos );
//	      id++;
//	   }
//	
//	   // perform look-up on desired table
//	   if ( table != NULL )
//	      iRetVal = (bParams ? table->m_nParams : table->getNCols());
//	
//	   return iRetVal;
//	}
//	
//	
//	int BEMTableList::GetTableName( int tableID, QString& sTableName )  // SAC 12/27/07
//	{
//	   sTableName.Empty();
//	   int iRetVal = -1;
//	   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
//	   if ( tableID > GetCount() || tableID < 1 )
//	      return iRetVal;
//	
//	   int id = 1;
//	   POSITION pos = GetHeadPosition();
//	   BEMTable* table = (BEMTable*)GetNext( pos );
//	   // loop over tablelist until desired table is found
//	   while ( id < tableID && pos != NULL )
//	   {
//	      table = (BEMTable*)GetNext( pos );
//	      id++;
//	   }
//	
//	   // perform look-up on desired table
//	   if ( table != NULL )
//	   {
//	      sTableName = table->m_name;
//	      iRetVal = tableID;
//	   }
//	
//	   return iRetVal;
//	}
//	
//	
//	int BEMTableList::GetTableColumnName( int tableID, int columnID, string& sColumnName )  // SAC 10/18/12
//	{
//		sColumnName.clear();
//	
//	   int iRetVal = -1;
//	   // return FALSE right off the bat if the list does not contain as many table as tableID argument requires
//	   if ( tableID > GetCount() || tableID < 1 )
//	      return iRetVal;
//	
//	   int id = 1;
//	   POSITION pos = GetHeadPosition();
//	   BEMTable* table = (BEMTable*)GetNext( pos );
//	   // loop over tablelist until desired table is found
//	   while ( id < tableID && pos != NULL )
//	   {
//	      table = (BEMTable*)GetNext( pos );
//	      id++;
//	   }
//	
//	   // perform look-up on desired table
//	   if ( table != NULL )
//	   {
//			sColumnName = table->getColumnName( columnID );
//	      if (sColumnName.length() > 0)
//				iRetVal = columnID;
//	   }
//	
//	   return iRetVal;
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  GetTableID()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Gets the 1-based array index of the table of the name tablename.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   const char* tableName : the name of the table for which the index is desired
//	//   
//	// Return Value -------------------------------------------------------------
//	//   The 1-based index of the desired table in the tablelist, or
//	//   -1 if the table is not found.
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	int BEMTableList::GetTableID( const char* tableName )
//	{
//		int iRetVal = -1;
//		BOOL bDone = FALSE;
//		QString sTbl, sVar;
//		const char* szTblName = tableName;
//		const char* szVarName = NULL;
//		if (strchr( tableName, ':' ))   // iff the table name includes a colon, split tableName into table and variable (column label) portions for individual look-ups
//		{	sTbl = tableName;
//			sVar = sTbl.right( sTbl.length() - sTbl.indexOf(':') - 1 );			assert( !sVar.isEmpty() );
//			if (sVar.indexOf(':') >= 0)
//				bDone = TRUE;	// not a valid table name if there are MORE than 1 ':'
//			else
//			{
//				sTbl = sTbl.left( sTbl.indexOf(':') );											assert( !sTbl.isEmpty() && sTbl.indexOf(':') < 0 );
//				szTblName = (const char*) sTbl;
//				szVarName = (const char*) sVar;
//			}
//		}
//		
//	   // loop over list of tables
//	   int id = 1;
//		BEMTable* pSelTable = NULL;
//	   POSITION pos = GetHeadPosition();
//	   while ( pos != NULL && !bDone && iRetVal < 0 )
//	   {
//	      BEMTable* table = (BEMTable*)GetNext( pos );
//	      // return id if table with matching name found
//	      if ( table->m_name.CompareNoCase( szTblName ) == 0 )
//	      {  iRetVal = id * BEMP_TABLEID_MULT;
//				pSelTable = table;
//			}
//	      id++;
//	   }
//	
//		if (pSelTable && iRetVal > 0 && !sVar.isEmpty())
//		{	int iColumnID = pSelTable->getColumnIndex( szVarName );
//			if (iColumnID < 0)
//			{	assert( FALSE );   // found table, but did not find column label
//				iRetVal = -1;
//			}
//			else
//				iRetVal += iColumnID;
//		}
//	
//	   return iRetVal;
//	}
//	
//	BEMTable* BEMTableList::GetTablePtr( const char* tableName )  // SAC 5/15/12
//	{
//	   POSITION pos = GetHeadPosition();
//	   // loop over list of tables
//	   while ( pos != NULL )
//	   {
//	      BEMTable* table = (BEMTable*)GetNext( pos );
//	      // return id if table with matching name found
//	      if ( table->m_name.CompareNoCase( tableName ) == 0 )
//	         return table;
//	   }
//	   return NULL;  // => table not found
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  Read()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Reads the Table List from the binary encrypted ruleset file.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   CryptoFile& file : binary encrypted ruleset file to read the table list from
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	void BEMTableList::Read( CryptoFile& file )
//	{
//	   InitTables();  // initializes tablelist
//	   
//	   int nTables;
//	   file.Read( &nTables, sizeof( int ) );  // read the number of tables contained in this file
//	
//	   for ( int tab = 0; tab < nTables; tab++ )
//	   {  // create new BEMTable
//	      BEMTable* newTable = new BEMTable();
//	      // read table data from file
//	      newTable->Read( file );
//	      // add new BEMTable to tablelist
//	      AddTail( newTable );
//	   }   
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMTableList Class Function:  Write()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Writes the Table List to the binary encrypted ruleset file.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   CryptoFile& file : binary encrypted ruleset file to write the table list to
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	void BEMTableList::Write( CryptoFile& file, QFile& errorFile )
//	{
//	   int nTables = (int) GetCount();
//	   file.Write( &nTables, sizeof( int ) );  // write number of tables to file
//	
//	#ifdef _DEBUG
//	   QString dbgMsg;   dbgMsg = QString( "%d" ).arg( QString::number(nTables) );
//	   dbgMsg = "\n   Writing list of " + dbgMsg;   dbgMsg += " tables.\n";
//	   errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
//	#endif
//	
//	   int iTableIdx = 1;
//	   POSITION pos = GetHeadPosition();
//	   while ( pos != NULL )
//	   {  // get next table
//	      BEMTable *table = (BEMTable*)GetNext( pos );
//	      if (table)
//	      {
//	#ifdef _DEBUG
//	         dbgMsg = QString( "%d" ).arg( QString::number(iTableIdx++) );
//	         dbgMsg = "      Table: " + dbgMsg;
//	         dbgMsg += " '";   dbgMsg += table->m_name;   dbgMsg += "'";
//	         errorFile.write( dbgMsg.toLocal8Bit().constData(), dbgMsg.length() );
//	#endif
//	         // write table data to file
//	         table->Write( file, errorFile );
//	      }
//	   }   
//	}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int BEMPX_GetTableColumn( double* pData, int iNumRecords, const char* pszTableName, int i1TableCol, char* pszErrMsgBuffer, int iErrMsgBufferLen )
{	int iRetVal = 0;
	QString sErrMsg;
	BEMTable* pTable = ruleSet.getTablePtr( pszTableName );
	if (pTable == NULL)
	{	iRetVal = 1;
		sErrMsg = QString( "Error in BEMPX_GetTableColumn():  Table '%1' not found." ).arg( pszTableName );
	}
	else if (i1TableCol > pTable->getNCols())
	{	iRetVal = 2;
		sErrMsg = QString( "Error in BEMPX_GetTableColumn():  Unable to retrieve column %1 from table '%2' (table includes %3 columns)." ).arg( 
												QString::number(i1TableCol), pszTableName, QString::number(pTable->getNCols()) );
	}
   else
	{	double dTblVal;
		for (int iRecIdx=0; iRecIdx < iNumRecords; iRecIdx++)
		{	if (pTable->GrabRecord( iRecIdx+1, i1TableCol, &dTblVal ))  //, BOOL bVerboseOutput=FALSE );  // SAC 5/15/12
				pData[iRecIdx] = dTblVal;
			else
			{	iRetVal = 2;
				sErrMsg = QString( "Error in BEMPX_GetTableColumn():  Unable to retrieve table record %1 from table '%2', column %3." ).arg( 
												QString::number(iRecIdx+1), pszTableName, QString::number(i1TableCol) );
				break;
			}
		}
	}
	if (!sErrMsg.isEmpty() && pszErrMsgBuffer && iErrMsgBufferLen > 0)
	{
#pragma warning(disable : 4996)
		strncpy( pszErrMsgBuffer, sErrMsg.toLocal8Bit().constData(), iErrMsgBufferLen-1 );
		pszErrMsgBuffer[iErrMsgBufferLen-1] = '\0';
#pragma warning(default : 4996)
	}
	return iRetVal;
}
