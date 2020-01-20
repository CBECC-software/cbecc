// table.h - header file for CTable and CTableList class definitions
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

#ifndef __TABLE_H__
#define __TABLE_H__

#include "expCrypFile.h"
#include "expTextIO.h"
#include "BEMProc.h"

using std::string;
using std::vector;

#define  BEMP_TABLEID_MULT  100


/////////////////////////////////////////////////////////////////////////////
//	CTableCell
//    An instance of this class is created for each individual look-up
//    table CELL.
/////////////////////////////////////////////////////////////////////////////

// enum used to identify the origin of each component in the database
enum BEMTbl_CellType
{
   BEMTCT_Float,
   BEMTCT_String,
   BEMTCT_Error,		// m_float holds ID of table error string, message returned to calling applicaiton & written to log file / analysis will be aborted   
   BEMTCT_Warning,	// m_float holds ID of table warning string, message returned to calling applicaiton & written to log file / analysis will continue
   BEMTCT_WildCard,	// wild card value (presence of an asterisk) -> 
   BEMTCT_Missing,	// no messaging provided, data simply not present and therefore table look-up will not return a valid value
   BEMTCT_Undefined,	// cell data not yet defined
   BEMTCT_NumTypes
};

class BEMTableCell
{
protected:
	int		m_type;
	int		m_condition;  // one of BEM_Condition:  BEMC_Equal/LessOrEqual/GrtrOrEqual/Less/Greater/NotEqual  (equal is default action)
	string	m_string;
	double	m_value;

public:
	BEMTableCell()														{	init();		}
	BEMTableCell( int iType )										{	m_type = iType;
																				m_condition = BEMC_Equal;
																				m_value = 0.f;		}
	BEMTableCell( double fValue, int iCond=BEMC_Equal )	{	m_type = BEMTCT_Float;
																				m_condition = iCond;
																				m_value = fValue;		}
	BEMTableCell( string str )										{	m_type = BEMTCT_String;
																				m_condition = BEMC_Equal;
																				m_string = str;
																				m_value = 0.f;		}
	BEMTableCell( int iMsgType, int iMsgID )					{	m_type = iMsgType;
																				m_condition = BEMC_Equal;
																				m_value = (double) iMsgID;		}
	BEMTableCell( int iType, double fValue, const char* pszStr, int iCond=BEMC_Equal )
																			{	set( iType, fValue, pszStr, iCond );		}
//	~BEMTableCell()													{	}  // m_string.clear();		}

	void init()															{	m_type = BEMTCT_Undefined;
																				m_condition = BEMC_Equal;
																				m_value = 0.f;
																			}
	void set( int iType, double fValue, const char* pszStr, int iCond=BEMC_Equal )
																			{	m_type = iType;
																				m_value = fValue;
																				m_string = pszStr;
																				m_condition = iCond;			}	// SAC 6/2/13 - fixed bug - was:  m_condition = BEMC_Equal;		}
	void get( int& iType, double& fValue, QString& str, int& iCond )
																			{	iType  = m_type;
																				fValue = m_value;
																				str    = m_string.c_str();
																				iCond	 = m_condition;			}

	int getCellType() 		{	return m_type;									}
	bool isFloat() 			{	return (m_type == BEMTCT_Float    );	}
	bool isString() 			{	return (m_type == BEMTCT_String   );	}
	bool isError() 			{	return (m_type == BEMTCT_Error    );	}
	bool isWarning() 			{	return (m_type == BEMTCT_Warning  );	}
	bool isWildCard() 		{	return (m_type == BEMTCT_WildCard );	}
	bool isMissing() 			{	return (m_type == BEMTCT_Missing  );	}
	bool isDefined() 			{	return (m_type != BEMTCT_Undefined);	}

	bool isMatch( double fValue ) 		{	return (m_type == BEMTCT_WildCard ||
																 (m_type == BEMTCT_Float &&
																 	 (	(m_condition == BEMC_Equal       && fValue == m_value) ||
																		(m_condition == BEMC_LessOrEqual && fValue <= m_value) ||
																		(m_condition == BEMC_GrtrOrEqual && fValue >= m_value) ||
																		(m_condition == BEMC_Less        && fValue <  m_value) ||
																		(m_condition == BEMC_Greater     && fValue >  m_value) ||
																		(m_condition == BEMC_NotEqual    && fValue != m_value) ) ));	}
	bool isMatch( string str ) 			{	return (m_type == BEMTCT_WildCard || (m_type == BEMTCT_String && boost::iequals(m_string, str) ));	}  // case INsensitive comparison

	void setValue( double fValue, int iCond=BEMC_Equal ) 	{	m_type = BEMTCT_Float;
																				m_condition = iCond;
																				m_value = fValue;
																			}
	void setString( string str )		 							{	m_type = BEMTCT_String;
																				m_condition = BEMC_Equal;
																				m_string = str;
																			}
	void setMessage( int iType, int iMsgID ) 					{	m_type = iType;
																				m_condition = BEMC_Equal;
																				m_value = (double) iMsgID;
																			}
	void setWildCard() 												{	m_type = BEMTCT_WildCard;
																			}
	void setMissing() 												{	m_type = BEMTCT_Missing;
																			}

	// returns floating point cell value
	int getCondition()	 	{	return m_condition;
									}
	// returns floating point cell value
	double getValue() 		{	assert( m_type == BEMTCT_Float );
										return m_value;
									}
	// returns string cell value
	std::string	getString()	{	assert( m_type == BEMTCT_String );
										return m_string;
									}
	// returns error or warning emssage ID
	int getMessageID()		{	assert( m_type == BEMTCT_Error || m_type == BEMTCT_Warning );
										return (int) m_value;
									}
	std::string	cellTypeDescription()	{	switch (m_type)
														{	case BEMTCT_Float     :  return "numeric";
														   case BEMTCT_String    :  return "string";
														   case BEMTCT_Error     :  return "error";
														   case BEMTCT_Warning   :  return "warning";
														   case BEMTCT_WildCard  :  return "wildcard";
														   case BEMTCT_Missing   :  return "missing";
														   case BEMTCT_Undefined :  return "undefined";
														}
														return "";
													}
	// returns string description of cell contents
	std::string	getStringRegardlessOfType()		// SAC 1/14/20
									{	string strRet;
										switch (m_type)
										{	case BEMTCT_Float     :  if (m_condition > BEMC_Equal)
																			 {	switch (m_condition)
																			 	{	case BEMC_LessOrEqual : strRet = "<= ";	break;
																			 		case BEMC_GrtrOrEqual : strRet = ">= ";	break;
																			 		case BEMC_Less        : strRet = "< ";		break;
																			 		case BEMC_Greater     : strRet = "> ";		break;
																			 		case BEMC_NotEqual    : strRet = "!= ";	break;
																			 }	}
																			 strRet += boost::str( boost::format( "%g" ) % m_value );	break;
										   case BEMTCT_String    :  strRet = m_string;		break;
										   case BEMTCT_Error     :  strRet = boost::str( boost::format( "error (%g)"   ) % m_value );	break;
										   case BEMTCT_Warning   :  strRet = boost::str( boost::format( "warning (%g)" ) % m_value );	break;
										   case BEMTCT_WildCard  :  strRet = "wildcard";	break;
										   case BEMTCT_Missing   :  strRet = "missing";		break;
										   case BEMTCT_Undefined :  strRet = "undefined";	break;
										}
										return strRet;
									}
};


/////////////////////////////////////////////////////////////////////////////
//	BEMTable
//    An instance of this class is created for each look-up table defined
//    for the selected compliance ruleset.
/////////////////////////////////////////////////////////////////////////////

class BEMTable
{
protected:
   QString m_name;      // look-up table name
   QString m_fileName;  // path & filename of file which contains the tables data
   int     m_nParams;   // number of independent (search) variables
   int     m_nCols;     // number of dependent (return value) variables
	vector<string> m_columnTitles;

	vector<string> m_rowTitles;
   std::vector<BEMTableCell*>  m_rowIndepCells;     // storage of row look-up data
   std::vector<BEMTableCell*>  m_data;     // storage of the table data

	vector<string> m_errorLabels;
	vector<string> m_errorMessages;

	vector<string> m_warningLabels;
	vector<string> m_warningMessages;

public:
   BEMTable()			{	}
   BEMTable( const char* name, int nParams, int nCols )
							{	m_name = name;
								m_nParams = nParams;
								m_nCols = nCols;			}
   BEMTable( const char* name, const char* fileName, int nParams, int nCols )
							{	m_name = name;
								m_fileName = fileName;
								m_nParams = nParams;
								m_nCols = nCols;			}
   ~BEMTable();
   void clear();

	QString	getName()								{	return m_name;	}
//	void		setName( QString& str )				{	m_name = str;		}
//	void		setName( const char* pszStr )		{	m_name = pszStr;		}

	int		getColumnTitleCount()				{	return (int) m_columnTitles.size();  }

	int		getNParams()				{	return m_nParams;	}
	int		getNCols()					{	return m_nCols;	}

	int	AddOrReturnLabelIndex( int iLabelType, const char* szLabel );
	bool	SetMessage( int iLabelType, int iMsgIdx, const char* szMessage );

   bool  Read( QFile& errorFile );
   bool  ReadV2( const char* fileName, QFile& errorFile, int& iNextTableRecord );  // SAC 10/11/12 - routine to read in new-format table from CSV file  // SAC 2/7/14 - added iNextTableRecord
   bool  ReadV2( BEMTextIO& file, QFile& errorFile );  // SAC 10/12/12 - routine to read in new-format table from Rules text file
   void  Read( CryptoFile& file );
   void  Write( CryptoFile& file, QFile& errorFile );
   bool  Lookup( double* pfParams, int iCol, double* pfValue, BOOL bVerboseOutput=FALSE );  // SAC 9/25/02
   bool  GrabRecord( int i1RecNum, int iCol, double* pdValue, bool bIgnoreIndepCols=false );  //, BOOL bVerboseOutput=FALSE );  // SAC 5/15/12
	int	GetColumnIndex( const char* pszColTitle );	// 0 if no col titles exist, -1 if col title not found, otherwise 1-based index of column
	std::string GetColumnName( int i1ColID );
	BEMTableCell* LookupCell( int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
											vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput=FALSE );  // SAC 10/17/12
	std::string	GetErrorMessage(   string& sErrorLabel );
	std::string	GetErrorMessage(   int i0MsgIndex );
	std::string	GetWarningMessage( string& sWarningLabel );
	std::string	GetWarningMessage( int i0MsgIndex );
};


//	/////////////////////////////////////////////////////////////////////////////
//	//	CTableList
//	//    An instance of this class is created for each list of look-up tables.
//	//    For now, there is only one such list for each ruleset.
//	////////////////////////////////////////////////////////////////////////////
//	
//	class CTableList : public CObList
//	{
//	public: 
//	   ~CTableList();
//	   void RemoveAll();
//	
//	   bool  AddTable( const char* name, const char* fileName, int nParams, int nCols, QFile& errorFile );
//	   bool  AddTable( const char* fileName, QFile& errorFile );  // SAC 10/18/12 - new structure, CSV format
//	   void  InitTables();
//	   void  Read( CryptoFile& file );
//	   void  Write( CryptoFile& file, QFile& errorFile );
//	   bool  GetValue( int tableID, float* paramArray, int col, float* pfValue, BOOL bVerboseOutput=FALSE );  // SAC 9/25/02
//	   int   GetTableID( const char* tableName );
//		CTable* GetTablePtr( const char* tableName );  // SAC 5/15/12
//	   int   GetTableDimension( int tableID, BOOL bParams=TRUE );  // SAC 12/19/05
//	   int   GetTableName( int tableID, QString& sTableName );  // SAC 12/27/07
//		int	GetTableColumnName( int tableID, int columnID, string& sColumnName );  // SAC 10/18/12
//		CBEMTableCell* GetTableCell( int iTableID, int iRetColID, vector<string>& saIndepNames, vector<string>& saIndepStrings,
//													vector<double>& faIndepValues, vector<bool>& baIndepNumeric, string& sErrMsg, BOOL bVerboseOutput=FALSE );		// SAC 10/17/12
//	};


/////////////////////////////////////////////////////////////////////////////

#endif // __TABLE_H__
