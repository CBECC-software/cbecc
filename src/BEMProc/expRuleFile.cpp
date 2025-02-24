// expRuleFile.cpp - RuleFile class definition
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
#include "expRuleFile.h"
#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProc_FileIO.h"
#include "BEMPropertyType.h"
#include "BEMClass.h"
#include "expDataType.h"
#include "expLibraryIO.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////

// NOTE: insert new reserved value strings BEFORE ..._Default, so that Default is immediately before individual TRANSFORM names which are added dynamically to the array of reserved strings referenced @ runtime
#define  DMRuleReserved_DataType			0 
#define  DMRuleReserved_ShortForm		1 
#define  DMRuleReserved_LongForm			2 
#define  DMRuleReserved_Description		3 
#define  DMRuleReserved_Help				4 
#define  DMRuleReserved_Reference		5 
#define  DMRuleReserved_InputClass		6 
#define  DMRuleReserved_Option			7 
#define  DMRuleReserved_Units				8 
#define  DMRuleReserved_ReportPrec		9
#define  DMRuleReserved_CommonMin		10
#define  DMRuleReserved_CommonMax		11
#define  DMRuleReserved_Minimum			12
#define  DMRuleReserved_Maximum			13
#define  DMRuleReserved_EndRule			14
#define  DMRuleReserved_EndRule2			15
#define  DMRuleReserved_PrevNames		16		// SAC 8/6/15
#define  DMRuleReserved_Resets			17		// SAC 11/2/16
#define  DMRuleReserved_Default			18		// --- all reserved words from this point to MAX_NUM assumed to be generic transforms (rulelists) ---
#define  DMRuleReserved_PreAnalCheck	19		// SAC 1/25/19 (com tic #2924)
#define  DMRuleReserved_CheckCode		20
#define  DMRuleReserved_CheckSim			21
#define  DMRuleReserved_FileHashes		22		// SAC 9/14/13
#define  DMRuleReserved_SecurityKeys	23		// SAC 9/14/13
//#define  DMRuleReserved_PrevNames		22		// SAC 8/6/15		// SAC 1/26/19 - moved up to avoid rl_PREVNAMES rulelist creation
#define  DMRuleReserved_Report			24
//#define  DMRuleReserved_Resets			24		// SAC 11/2/16		// SAC 1/26/19 - moved up to avoid rl_RESETS rulelist creation
#define  DMRuleReserved_NRCCPRF			25    // NRCCPRF XML reporting - SAC 11/27/20
#define  DMRuleReserved_MAX_NUM			25

static bool SetAllDataForDMRuleReserved( int iDMRuleRsrvd )		// SAC 8/8/13 - added to enable variation in bSetAllData rulelist property for "reserved" lists
{	return  ( (iDMRuleRsrvd == DMRuleReserved_Default) ? false : true );
}

const char* pszDMRuleReserved[] = {	"DATATYPE",
												"SHORTFORM",
												"LONGFORM",
												"DESCRIPTION",
												"HELP",
												"REFERENCE",
												"INPUTCLASS",
												"OPTION",
                                    "UNITS", 
                                    "REPORTPRECISION", 
                                    "COMMONMINIMUM",
                                    "COMMONMAXIMUM",
                                    "MINIMUM", 
                                    "MAXIMUM", 
												"ENDRULE",
												"ENDRUL",
												"PREVIOUSNAMES",
												"RESETS",
												"DEFAULT",
												"PREANALYSISCHECK",
												"CHECKCODE",
												"CHECKSIM",
												"FILEHASHES",
												"SECURITYKEYS",
									//			"PREVIOUSNAMES",
												"REPORT",
									//			"RESETS" };
                                    "NRCCPRF" };      // NRCCPRF XML reporting - SAC 11/27/20

const char* pszDMRuleDataTypes[] = {	"String",
													"Integer",
													"Float",
													"Enumeration",
													NULL };
static int siaDMRuleDataTypes[] = {	BEMP_Str,
													BEMP_Int,
													BEMP_Flt,
													BEMP_Sym  };
													//BEMP_Obj,

const char* pszDataTypeStrs[] = {	"Integer",
												"Float",
												"Enumeration",
												"String",
												"Object",
												"QString"  };
const char* PropTypeIDToString( int iPTID )
{	const char* pszRetVal = NULL;
	switch (iPTID)
	{	case  BEMP_Int  :  pszRetVal = pszDataTypeStrs[0];		break;
		case  BEMP_Flt  :  pszRetVal = pszDataTypeStrs[1];		break;
		case  BEMP_Sym  :  pszRetVal = pszDataTypeStrs[2];		break;
		case  BEMP_Str  :  pszRetVal = pszDataTypeStrs[3];		break;
		case  BEMP_Obj  :  pszRetVal = pszDataTypeStrs[4];		break;
		case  BEMP_QStr :  pszRetVal = pszDataTypeStrs[5];		break;
	}
	return pszRetVal;
}


/////////////////////////////////////////////////////////////////////////////

void EnsureValidPath( QString sFileWithPath, QString& sFileToCheck )
{  // SAC 10/29/12 - added code to enable sFileToCheck to include a partial path or even a path with indirection (including one or more '..\')
	sFileWithPath.replace('\\', '/');	sFileToCheck.replace('\\', '/');
	if (sFileToCheck.indexOf("../") == 0)
	{	QString sNewRoot = sFileWithPath.left( sFileWithPath.lastIndexOf('/') );
		while (sFileToCheck.indexOf("../") == 0)
		{	if (sNewRoot.indexOf('/') == sNewRoot.lastIndexOf('/'))
			{	assert( FALSE );  // can't backup any further...
				break;
			}
			else
			{	sFileToCheck = sFileToCheck.right( sFileToCheck.length()-3 );		// remove leading "..\" from path argument
				sNewRoot = sNewRoot.left( sNewRoot.length()-1 );         // trim trailing '\' from full path
				sNewRoot = sNewRoot.left( sNewRoot.lastIndexOf('/')+1 );	// trim right side of full path to the new last '\'
			}
		}
		sFileToCheck = sNewRoot + sFileToCheck;
	}
	else if (sFileToCheck.indexOf('/') > 0 && sFileToCheck.indexOf(':') < 0 && 
				!FileExists( sFileToCheck.toLocal8Bit().constData() ) && sFileWithPath.lastIndexOf('/') > 0)
	{	// a portion, but incomplete, path is included inside sFileToCheck, so assume it is RELATIVE to the path portion of sFileWithPath
		sFileToCheck = sFileWithPath.left( sFileWithPath.lastIndexOf('/')+1 ) + sFileToCheck;
	}

	// extract directopry portion of file being checked for path
	QString checkFileDir;
//	sFileToCheck.GetDir( checkFileDir );
	QDir qdFileToCheck( sFileToCheck );
	checkFileDir = qdFileToCheck.path();
	// if no directory portion of filename exists, then create one
	if (checkFileDir.length() == 0)
	{
		QDir qdFileWithPath( sFileWithPath );
		qdFileToCheck.setPath( qdFileWithPath.absolutePath() );
		sFileToCheck = qdFileWithPath.absoluteFilePath( sFileToCheck );
	}
}

void RuleFile::EnsureValidPath_AltPaths( QString sFileWithPath, QString& sFileToCheck )
{
   QString sWorkingFile = sFileToCheck;
   EnsureValidPath( sFileWithPath, sWorkingFile );
   int iFPSize = (int) m_slFilePaths.size();
   for (int i=0; (!FileExists( sWorkingFile.toLocal8Bit().constData() ) && i < iFPSize); i++)
   {
      sWorkingFile  = m_slFilePaths.at(i);
      sWorkingFile += sFileToCheck;
      EnsureValidPath( m_slFilePaths.at(i), sWorkingFile );
   }
   if (FileExists( sWorkingFile.toLocal8Bit().constData() ))
      sFileToCheck = sWorkingFile;
}


/////////////////////////////////////////////////////////////////////////////

//// SAC 5/10/14 - routine to replace CRLF followed by several spaces with a single space character - enabling strings
////						to span multiple lines in ruleset source without impacting their use/display/logging during rule evaluation
//static const char* spszNLTab = "\n\t";
//static const char* spszNLSpc = "\n ";
//void FormatMultilineString( QString& str )
//{
//	int idxNLTab = str.indexOf( spszNLTab );
//	int idxNLSpc = str.indexOf( spszNLSpc );
//	int idxRemove = ( (idxNLTab >= 0 && idxNLSpc >= 0) ? std::min( idxNLTab, idxNLSpc ) : (idxNLTab >= 0 ? idxNLTab : (idxNLSpc >= 0 ? idxNLSpc : -1 )));
//	while (idxRemove >= 0)
//	{	int iRemoveBeforeNL = 0;		// SAC 2/12/15 - added code to remove spaces or tabs PRIOR TO portion of string being removed
//		while (idxRemove > 0 && (str[idxRemove-1] == ' ' || str[idxRemove-1] == '\t'))
//		{	iRemoveBeforeNL++;
//			idxRemove--;
//		}
//		if (iRemoveBeforeNL > 0)
//			str = str.left( idxRemove ) + str.right( str.length()-idxRemove-iRemoveBeforeNL );
//
//		int idxLastSpc = idxRemove+1;
//		int iAdditionalChar = (idxRemove > 0 && str[idxRemove-1] == '\n' ? 0 : 1);  // if 2 newllines in a row, do not save last space or tab in spaced characters
//		while (idxLastSpc < str.length() && (str[idxLastSpc] == ' ' || str[idxLastSpc] == '\t'))
//			idxLastSpc++;
//
//		if (idxLastSpc >= str.length())
//			str = str.left( idxRemove );
//		else
//			str = str.left( idxRemove ) + str.right( str.length()-idxLastSpc+iAdditionalChar );
//
//		idxNLTab = str.indexOf( spszNLTab );
//		idxNLSpc = str.indexOf( spszNLSpc );
//		idxRemove = ( (idxNLTab >= 0 && idxNLSpc >= 0) ? std::min( idxNLTab, idxNLSpc ) : (idxNLTab >= 0 ? idxNLTab : (idxNLSpc >= 0 ? idxNLSpc : -1 )));
//	}
//}
// SAC 2/28/17 - replace above routine in response to Com ticket #1190 which highlighted inconsistencies in how messages are formatted based on white space present and absent from ruleset source
static inline int IndexOfNextNewline( QString& str, int idx, int& iNLLen )
{	int iRetVal = -1;
	iNLLen = 1;
	int idxNL  = str.indexOf( "\n",  idx );
	int idxNL2 = str.indexOf( "\\n", idx );
	if (idxNL >= 0 && idxNL2 >= 0)
	{	if (idxNL2 < idxNL)
		{	iRetVal = idxNL2;
			iNLLen = 2;
		}
		else
			iRetVal = idxNL;
	}
	else if (idxNL2 >= 0)
	{	iRetVal = idxNL2;
		iNLLen = 2;
	}
	else if (idxNL >= 0)
		iRetVal = idxNL;
	return iRetVal;
}

static inline bool InsertSpace( QString& str, int idx )
{	bool bRetVal = true;
	if (idx==0)
		bRetVal = false;
	else if (str[idx-1]=='-' || str[idx-1]==' ')
		bRetVal = false;
	else if (str[idx-1]=='\n' || (idx > 1 && str[idx-1]=='n' && str[idx-2]=='\\'))
		bRetVal = false;
	return bRetVal;
}

void FormatMultilineString( QString& str )
{	int iNLLen;
	int idxNL = IndexOfNextNewline( str, 0, iNLLen );
	while (idxNL >= 0)
	{	int iNumCharsToRemove = 0;
		QString sInsert;
		if (str.length() <= idxNL)
		{ }	// doing nothing here will trim string to everything left of the newline
		else if (str[idxNL+iNLLen] == '\n' || (str.length() > idxNL+iNLLen && str[idxNL+iNLLen] == '\\' && str[idxNL+iNLLen+1] == 'n'))
			// swip over first of double newline and continue
			idxNL += iNLLen;
		else if (str[idxNL+iNLLen] == ' ' || str[idxNL+iNLLen] == '\t')
		{	// when next char is a spc or tab, replace all subsequent spaces/tabs w/ a single space (or no space when preceeding char is '-')
			iNumCharsToRemove += iNLLen;
			while (str.length() > (idxNL+iNumCharsToRemove) && (str[idxNL+iNumCharsToRemove] == ' ' || str[idxNL+iNumCharsToRemove] == '\t'))
				iNumCharsToRemove++;
			sInsert = (InsertSpace( str, idxNL ) ? " " : "");
		}
		else
		{	// replace the newline w/ a single space (or no space when preceeding char is '-')
			iNumCharsToRemove = iNLLen;
			sInsert = (InsertSpace( str, idxNL ) ? " " : "");
		}

		if (str.length() <= idxNL+iNumCharsToRemove)
			str = str.left( idxNL );
		else if (iNumCharsToRemove > 0)
			str = str.left( idxNL ) + sInsert + str.right( str.length()-idxNL-iNumCharsToRemove );

		//idxNL = str.indexOf( '\n', idxNL );
		idxNL = IndexOfNextNewline( str, idxNL, iNLLen );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_LoadRuleset()
//
// Purpose ------------------------------------------------------------------
//   Reads the contents of a binary encrypted ruleset file into memory.
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR fileName  : path/filename of the binary encrypted ruleset file.
//   
// Return Value -------------------------------------------------------------
//   TRUE if this ruleset file matches the current RulPrc file version, else
//   FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_LoadRuleset( LPCSTR fileName, BOOL bDeleteAllObjects )		// was RuleProcRead()
{	BOOL bRetVal = FALSE;
	QString sRuleSetID, sRuleSetVersion, sRdStr;
	int iStructVer, i, iRd;		long lRd;	bool bRulesSecure=false;
   // CryptoFile file( fileName, CFile::modeRead | CFile::shareDenyWrite );  // open file
   CryptoFile file( fileName );
   if (!file.open( QIODevice::ReadOnly ))
	{	//sErrMsg = QString( "Error opening BEMProc ruleset file:  '%s'" ).arg( fileName );
	}
   // confirm RulPrc version match and read in ruleset ID & version strings
   else if (CheckRulesetFileVerAndReadID( file, sRuleSetID, sRuleSetVersion, iStructVer, bRulesSecure ))
   {	// first initialize ruleset data
		ruleSet.clear();
		// then blast either all or just rule library objects...
		int iObjTypeToDelete = (bDeleteAllObjects ? -1 : BEMO_RuleLib);
		BEMPX_DeleteAllObjects( iObjTypeToDelete, FALSE /*re-init symbols*/ );

		ruleSet.setRuleSetID( sRuleSetID );
		ruleSet.setRuleSetVersion( sRuleSetVersion );
		ruleSet.setFileStructVersion( iStructVer );

		if (ruleSet.getFileStructVersion() >= 13)
		{	file.ReadQString( sRdStr );		ruleSet.setBEMBaseFile( sRdStr );	// SAC 8/15/14
		}

      // read Screens and ToolTips text filename strings
      file.ReadQString( sRdStr );			ruleSet.setScreensFile(  sRdStr );
      file.ReadQString( sRdStr );			ruleSet.setToolTipsFile( sRdStr );

		if (ruleSet.getFileStructVersion() > 5)
		{	file.Read( &iRd, sizeof( int ) );		ruleSet.setRulesetOrganization( iRd );
		}

		if (ruleSet.getFileStructVersion() >= 14)
		{	file.Read( &iRd, sizeof( int ) );			// SAC 9/8/14 - labels used to facilitate ruleset source shared by multiple standards/versions
			for (i=0; i<iRd; i++)
			{	file.ReadQString( sRdStr );			assert( !sRdStr.isEmpty() );
				if (!sRdStr.isEmpty())
					ruleSet.addLabel( sRdStr );
		}	}

		if (ruleSet.getFileStructVersion() > 7)
		{	file.Read( &lRd, sizeof( long ) );		ruleSet.setSimulateDBID( lRd );	// SAC 3/18/14
		}
		else
			ruleSet.setSimulateDBID( 0 );

      ruleSet.readRuleLists( file, ruleSet.getFileStructVersion() );            // read rules

	// Read ruleset variables (properties to be added to BEMBase)
	   file.Read( &iRd, sizeof( int ) );			// SAC 7/6/12
		for (i=0; i<iRd; i++)
		{	RuleSetProperty* pRuleProp = new RuleSetProperty();			assert( pRuleProp );
			if (pRuleProp)
			{	pRuleProp->Read( file, ruleSet.getFileStructVersion() );
				ruleSet.addRuleSetProperty( pRuleProp );
		}	}
	// ADD ruleset variables to BEMBase
		QString sRulePropErrs;
		ruleSet.PostRulePropsToDatabase( sRulePropErrs );

      //ruleSet.m_tableList.Read( file ); 
	   file.Read( &iRd, sizeof( int ) );			// read tables
		for (i=0; i<iRd; i++)
		{	BEMTable* pTable = new BEMTable();		assert( pTable );
			if (pTable)
			{	pTable->Read( file );
				ruleSet.addTable( pTable );
		}	}

      //ruleSet.m_dataTypeList.Read( file ); 
	   file.Read( &iRd, sizeof( int ) );			// read data types
		for (i=0; i<iRd; i++)
		{	BEMPropertyDataType* pDT = new BEMPropertyDataType();		assert( pDT );
			if (pDT)
			{	pDT->Read( file );
				ruleSet.addDataType( pDT );
		}	}
		ruleSet.postDataTypesToDatabase();

      //ruleSet.m_rangesList.Read( file );
	   file.Read( &iRd, sizeof( int ) );			// read range checks
		for (i=0; i<iRd; i++)
		{	BEMRangeCheck* pRC = new BEMRangeCheck();		assert( pRC );
			if (pRC)
			{	pRC->Read( file );
				ruleSet.addRangeCheck( pRC );
		}	}
		ruleSet.postRangeChecksToDatabase();

      //ruleSet.m_symbolList.Read( file ); 
	   file.Read( &iRd, sizeof( int ) );			// read symbol (enumeration) definitions
		for (i=0; i<iRd; i++)
		{	SymLst* pSL = new SymLst();		assert( pSL );
			if (pSL)
			{	pSL->Read( file );
				ruleSet.addSymLst( pSL );
		}	}
		ruleSet.postSymbolsToDatabase();

      //ruleSet.m_maxChildList.Read( file );    // read MaxChild definitions

      //ruleSet.m_resetList.Read( file ); 
	   file.Read( &iRd, sizeof( int ) );			// read Reset definitions
		for (i=0; i<iRd; i++)
		{	BEMResetData* pRD = new BEMResetData();		assert( pRD );
			if (pRD)
			{	pRD->Read( file );
				ruleSet.addReset( pRD );
		}	}
		ruleSet.postResetsToDatabase();

      //ruleSet.m_uniqueAssignmentList.Read( file );    // read Unique Assignment definitions

		if (ruleSet.getFileStructVersion() >= 15)			// SAC 2/5/15 - data used to update BEMBase PropertyType objects
		{	//ruleSet.m_rulePropTypeModList.Read( file );
		   file.Read( &iRd, sizeof( int ) );			// read rule property type mod data
			for (i=0; i<iRd; i++)
			{	BEMPropTypeMod* pRPTM = new BEMPropTypeMod();		assert( pRPTM );
				if (pRPTM)
				{	pRPTM->Read( file );
					ruleSet.addRulePropTypeMod( pRPTM );
			}	}
			ruleSet.postRulePropTypeModsToDatabase();
		}

		if (ruleSet.getFileStructVersion() > 10)			// SAC 5/11/14 - read rule-based ToolTip messages
		{	file.Read( &iRd, sizeof( int ) );
			for (i=0; i<iRd; i++)
			{	RuleToolTip* pRuleTT = new RuleToolTip();			assert( pRuleTT );
				if (pRuleTT)
				{	pRuleTT->Read( file );
					ruleSet.addToolTip( pRuleTT );
		}	}	}

		//ruleSet.m_transformations.Read( file );			// SAC 6/21/12
	   file.Read( &iRd, sizeof( int ) );
		for (i=0; i<iRd; i++)
		{	RuleSetTransformation* pTrans = new RuleSetTransformation();			assert( pTrans );
			if (pTrans)
			{	pTrans->Read( file, ruleSet.getFileStructVersion() );
				ruleSet.addTransformation( pTrans );
			}
		}

      ReadRuleLibrary( file );                        // read rule library
      bRetVal = TRUE;
   }
   return bRetVal;
}


int BEMPX_PostAnalysisActionRulesetPropertiesToDatabase()
{
	int iRetVal = 0;		// > 0 Num RulesetProperties added / < 0 error code
	long lDBID_AnalAct_Type = BEMPX_GetDatabaseID( "AnalysisAction:Type" );
	int iCID_AnalAct = (lDBID_AnalAct_Type > BEM_COMP_MULT ? BEMPX_GetClassID( lDBID_AnalAct_Type ) : 0);
	int iNumAnalActs = (iCID_AnalAct > 0 ? BEMPX_GetNumObjects( iCID_AnalAct ) : 0);
	if (iNumAnalActs > 0)
	{
		int iNumInitRuleProps = ruleSet.numRulesetProperties();
		int iNumRulePropsAdded = 0;

		std::vector<int> iaExistingRulePropsByClass;
		int iClassID, iNumClasses = BEMPX_GetNumClasses();
		for (iClassID=1; iClassID<=iNumClasses; iClassID++)
			iaExistingRulePropsByClass.push_back( ruleSet.NumRulesetPropertiesForObject( iClassID ) );

	// scan all AnalysisAction objects for any New properties & add them to the ruleset
		long lDBID_AnalAct_ObjPropertyName = BEMPX_GetDatabaseID( "ObjPropertyName", iCID_AnalAct );			assert( lDBID_AnalAct_ObjPropertyName > BEM_COMP_MULT );
		long lAAType;		QString qsAAObjProp;		int iError;
		
		for (int iAA=0; (iRetVal >= 0 && iAA < iNumAnalActs); iAA++)
		{	if (BEMPX_GetInteger( lDBID_AnalAct_Type, lAAType, 0, -1, iAA ) && lAAType >= 1 && lAAType <= 10 &&		// AAType in range of 1-10 => NewString/Int/Float...
				 BEMPX_GetString(  lDBID_AnalAct_ObjPropertyName, qsAAObjProp, FALSE, 0, -1, iAA ) && !qsAAObjProp.isEmpty())
			{	// this AnalysisAction probably requires addition of a RulesetProperty
				long lAADBID = BEMPX_GetDatabaseID( qsAAObjProp );
				if (lAADBID < 1)
				{	iClassID = 1;  // default to Proj
					int iColonIdx = qsAAObjProp.indexOf( ':' );			assert( iColonIdx < qsAAObjProp.length() );
					if (iColonIdx >= qsAAObjProp.length())
						iRetVal = -1;
					else if (iColonIdx > 1)
					{	QString qsClass = qsAAObjProp.left(iColonIdx);
						iClassID = BEMPX_GetDBComponentID( qsClass.toLocal8Bit().constData() );			assert( iClassID > 0 );
					}
					if (iClassID > 0)
					{
					// add this RulesetProperty
						BEMClass* pObjClass = BEMPX_GetClass( iClassID, iError );			assert( pObjClass );
						int iNewPropID = pObjClass->getNumProps() + ruleSet.NumRulesetPropertiesForObject( iClassID ) - iaExistingRulePropsByClass[iClassID-1] + 1;
						if (iNewPropID >= (BEM_COMP_MULT/BEM_PARAM_MULT))		// SAC 9/22/20 - added error if/when max # properties exceeded w/ a RULE NEW
						{	//sErr = QString( "\n\tError:  Maximum # Properties per Class (%1) exceeded @ RULE NEW property '%2' - rule '%3' found on line: %4\n" ).arg( QString::number((BEM_COMP_MULT/BEM_PARAM_MULT)), sNewPropName, sNewFullPath, QString::number(file.GetLineCount()) );
							//errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
							iRetVal = -4;
						}
						else
						{	QString sNewPropName = qsAAObjProp.right( qsAAObjProp.length() - iColonIdx -1 );
							lAADBID = BEMPX_GetDBID( iClassID, iNewPropID, 1 );
							int iPropType = lAAType-1;
							RuleSetProperty* pNewRuleProp = new RuleSetProperty( iClassID, iNewPropID, sNewPropName, sNewPropName, lAADBID, iPropType );				assert( pNewRuleProp );
							if (!pNewRuleProp)
								iRetVal = -2;
							else
							{	ruleSet.addRuleSetProperty( pNewRuleProp );
								iRetVal++;
						}	}
		}	}	}	}					

		if (iRetVal > 0)		// => ADD "ruleset variables" (RULE NEW items) to BEMBase  - SAC 1/30/20 - finished up implementation of function
		{	QString sErrantRuleProps;
			if (!ruleSet.PostRulePropsToDatabase( sErrantRuleProps, BEMD_NotInput, iNumInitRuleProps ))
			{	//sErrMsg = QString( "   Error encountered inserting ruleset variables (RULE NEWs) into BEMBase: %1\n%2\n" ).arg( m_fileName, sErrantRuleProps );
				//errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
				iRetVal = -3;
		}	}
	}  // end of  if (iNumAnalActs > 0)
	return iRetVal;		// > 0 Num RulesetProperties added / < 0 error code
}


// #define  BEMAnalActPhase_LoadModel            1
// #define  BEMAnalActPhase_ProposedSizing      11
// #define  BEMAnalActPhase_ProposedAnnual      12
// #define  BEMAnalActPhase_BaselineSizing      13
// #define  BEMAnalActPhase_BaselineAnnual      14
// #define  BEMAnalActPhase_End                  2
// 
// #define  BEMAnalActWhen_LoadModel_BeforeDefaulting         1
// #define  BEMAnalActWhen_LoadModel_AfterDefaulting          2
// #define  BEMAnalActWhen_End_BeforeAnalPostProc            11
// #define  BEMAnalActWhen_End_AfterAnalPostProc             12
// #define  BEMAnalActWhen_Transform_BeforeModelSetupRules   21
// #define  BEMAnalActWhen_Transform_AfterModelSetupRules    22
// #define  BEMAnalActWhen_Transform_FollowingResultsProc    23
// #define  BEMAnalActWhen_Transform_ActOnEPlusSimInput      31
// #define  BEMAnalActWhen_Transform_ActOnCSESimInput        32
QString AnalActDescrip( long iAnalPhase, long iBeforeAfter, int iAAIdx )
{	QString str = QString( "#%1" ).arg( QString::number( iAAIdx+1 ) );
	if (iBeforeAfter <= 20)
	{	switch (iBeforeAfter)
		{	case  BEMAnalActWhen_LoadModel_BeforeDefaulting :  str += " (load model, before defaulting)";   break;
			case  BEMAnalActWhen_LoadModel_AfterDefaulting  :  str += " (load model, after defaulting)";   break;
			case  BEMAnalActWhen_End_BeforeAnalPostProc     :  str += " (end, before AnalPostProc)";   break;
			case  BEMAnalActWhen_End_AfterAnalPostProc      :  str += " (end, after AnalPostProc)";   break;
	}	}
	else
	{	// transform-related
		switch (iAnalPhase)
		{	case  BEMAnalActPhase_ProposedSizing :  str += " (PropSz, ";    break;
			case  BEMAnalActPhase_ProposedAnnual :  str += " (PropAnn, ";   break;
			case  BEMAnalActPhase_BaselineSizing :  str += " (BaseSz, ";    break;
			case  BEMAnalActPhase_BaselineAnnual :  str += " (BaseAnn, ";   break;
		}
		switch (iBeforeAfter)
		{	case  BEMAnalActWhen_Transform_BeforeModelSetupRules :  str += "before model setup)";   break;
			case  BEMAnalActWhen_Transform_AfterModelSetupRules  :  str += "after model setup)";   break;
			case  BEMAnalActWhen_Transform_FollowingResultsProc  :  str += "following results proc)";   break;
			case  BEMAnalActWhen_Transform_ActOnEPlusSimInput    :  str += "act on E+ sim input)";   break;
			case  BEMAnalActWhen_Transform_ActOnCSESimInput      :  str += "act on CSE sim input)";   break;
	}	}
	return str;
}
//
//	return value: >= 0 : # of AnalysisActions applied to the database
//						 -1 :  Error applying AnalysisAction XXXX: ObjPropertyName undefined
//						 -2 :  Error applying AnalysisAction XXXX: cannot map 'XXXX' to BEMBase DBID
//						 -3 :  Error applying AnalysisAction XXXX: AlterObjName undefined
//						 -4 :  Error applying AnalysisAction XXXX: Object flagged for alteration 'XXXX' not found
//						 -5 :  Error applying AnalysisAction XXXX: SetValFloat undefined setting XXXX
//						 -6 :  Error applying AnalysisAction XXXX: unable to set XXXX to XXXX for XXXX #X
//						 -7 :  Error applying AnalysisAction XXXX: SetValInteger undefined setting XXXX
//						 -8 :  Error applying AnalysisAction XXXX: unable to set XXXX to XXXX for XXXX #X
//						 -9 :  Error applying AnalysisAction XXXX: SetValString undefined setting XXXX
//						-10 :  Error applying AnalysisAction XXXX: unable to set 'XXXX' to XXXX for XXXX #X
//						-11 :  Error applying AnalysisAction XXXX: unrecognized Type (XXXX)
//						-12 :  Error applying AnalysisAction XXXX: unable to retrieve rulelist name from SetValString
//						-13 :  Error applying AnalysisAction XXXX: evaluation of rulelist 'XXXX' failed
//						-14 :  Error applying AnalysisAction XXXX: too many ruleset export files open:  XXXX
//						-15 :  Error applying AnalysisAction XXXX: unable to open simulaiton input file:  XXXX
//						-16 :  Error applying AnalysisAction XXXX: RulelistPathFile undefined setting XXXX
//						-17 :  Error applying AnalysisAction XXXX: RulelistPathFile file not found:  XXXX
//						-18 :  Error applying AnalysisAction XXXX: RulelistPathFile parsing error:  XXXX
//						-19 :  Error applying AnalysisAction XXXX: TablePathFile undefined setting XXXX
//						-20 :  Error applying AnalysisAction XXXX: TablePathFile file not found:  XXXX
//						-21 :  Error applying AnalysisAction XXXX: error opening TablePathFile parsing log file:  XXXX
//						-22 :  Error applying AnalysisAction XXXX: TablePathFile parsing error:  XXXX
//						-23 :  Error ...
//						-99 :  Error applying AnalysisAction XXXX: XXXX analysis action type not yet implemented
int BEMPX_ApplyAnalysisActionToDatabase( long iAnalPhase, long iBeforeAfter, QString& sErrorMsg, bool bVerbose,
														const char* pszSimPathFileName /*=NULL*/ )			// SAC 3/10/20
{
	int iRetVal = 0;		// > 0 Num AnalysisActions applied to the database / < 0 error code
	long lDBID_AnalAct_Type = BEMPX_GetDatabaseID( "AnalysisAction:Type" );
	if (lDBID_AnalAct_Type > BEM_COMP_MULT)
	{	int iCID_AnalAct = BEMPX_GetClassID( lDBID_AnalAct_Type );				assert( iCID_AnalAct > 0 );
		int iNumAnalActs = (iCID_AnalAct > 0 ? BEMPX_GetNumObjects( iCID_AnalAct ) : 0);
		if (iNumAnalActs > 0)
		{
			QString sLogMsg;   int iError, iStatus, iSpecialVal;
			long lDBID_AnalAct_AnalysisPhase    = BEMPX_GetDatabaseID( "AnalysisAction:AnalysisPhase"    );			assert( lDBID_AnalAct_AnalysisPhase    > 0 );
			long lDBID_AnalAct_BeforeAfterPhase = BEMPX_GetDatabaseID( "AnalysisAction:BeforeAfterPhase" );			assert( lDBID_AnalAct_BeforeAfterPhase > 0 );
			long lDBID_AnalAct_ObjPropertyName = 0;
			long lDBID_AnalAct_AlterObjName    = 0;
			long lDBID_AnalAct_SetValFloat     = 0;
			long lDBID_AnalAct_SetValInteger   = 0;
			long lDBID_AnalAct_SetValString    = 0;
			long lDBID_AnalAct_SetValPathFile  = 0;
			int iSimInputExpFileIdx = -1;
			for (int iAA=0; (iRetVal >= 0 && iAA < iNumAnalActs); iAA++)
			{	long lAAType, lPhase, lWhen;
				if (BEMPX_GetInteger( lDBID_AnalAct_Type            , lAAType, 0, -1, iAA ) && lAAType > 0 &&
					 BEMPX_GetInteger( lDBID_AnalAct_AnalysisPhase   , lPhase , 0, -1, iAA ) && lPhase == iAnalPhase &&		// iAnalPhase matches
					 BEMPX_GetInteger( lDBID_AnalAct_BeforeAfterPhase, lWhen  , 0, -1, iAA ) && lWhen  == iBeforeAfter )		// iBeforeAfter matches
				{
				// APPLY THIS AnalysisAction
					if (iRetVal == 0)
					{	lDBID_AnalAct_ObjPropertyName = BEMPX_GetDatabaseID( "AnalysisAction:ObjPropertyName"  );			assert( lDBID_AnalAct_ObjPropertyName > 0 );
						lDBID_AnalAct_AlterObjName    = BEMPX_GetDatabaseID( "AnalysisAction:AlterObjName"  );				assert( lDBID_AnalAct_AlterObjName    > 0 );
						lDBID_AnalAct_SetValFloat     = BEMPX_GetDatabaseID( "AnalysisAction:SetValFloat"  );				assert( lDBID_AnalAct_SetValFloat     > 0 );
						lDBID_AnalAct_SetValInteger   = BEMPX_GetDatabaseID( "AnalysisAction:SetValInteger"  );			assert( lDBID_AnalAct_SetValInteger   > 0 );
						lDBID_AnalAct_SetValString    = BEMPX_GetDatabaseID( "AnalysisAction:SetValString"  );				assert( lDBID_AnalAct_SetValString    > 0 );
						lDBID_AnalAct_SetValPathFile  = BEMPX_GetDatabaseID( "AnalysisAction:SetValPathFile"  );			assert( lDBID_AnalAct_SetValPathFile  > 0 );
					}

					long lDBID_ToSet = 0;
					int iFirstAlterObjIdx=-1, iLastAlterObjIdx=-1, iNumAlterObjs=0;
					QString qsAAObjProp;
					QString sAlterClassName = "class(?)";
					if (lAAType < 21)
					{	// setting some sort of data to BEMBase
						if (BEMPX_GetString( lDBID_AnalAct_ObjPropertyName, qsAAObjProp, FALSE, 0, -1, iAA ) && !qsAAObjProp.isEmpty())
						{	lDBID_ToSet = BEMPX_GetDatabaseID( qsAAObjProp );
							if (lDBID_ToSet < BEM_COMP_MULT)
							{	iRetVal = -2;
								sErrorMsg = QString( "Error applying AnalysisAction %1: cannot map '%s' to BEMBase DBID" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
						}	}
						else
						{	iRetVal = -1;
							sErrorMsg = QString( "Error applying AnalysisAction %1: ObjPropertyName undefined" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ) );
						}
						if (iRetVal >= 0)
						{	QString qsAlterObj;
							if (BEMPX_GetString( lDBID_AnalAct_AlterObjName, qsAlterObj, FALSE, 0, -1, iAA ) && !qsAlterObj.isEmpty())
							{	int iCID_AlterClass = BEMPX_GetClassID( lDBID_ToSet );			assert( iCID_AlterClass > 0 );
								BEMClass* pClass = (iCID_AlterClass > 0 ? BEMPX_GetClass( iCID_AlterClass, iError ) : NULL);
								if (pClass)
									sAlterClassName = pClass->getShortName();
								if (!qsAlterObj.compare("*"))
								{	iNumAlterObjs = (iCID_AlterClass > 0 ? BEMPX_GetNumObjects( iCID_AlterClass ) : 0);
									if (iNumAlterObjs < 1)
									{	// don't throw error, but do log that no object found so no AnalAct will be processed
										iFirstAlterObjIdx = -2;	// special flag indicating no further processing of this AnalAct
										sLogMsg = QString( "      Warning: AnalysisAction %1 flagged for mod of all %2 objects, but none exist in model" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sAlterClassName );
										BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
									}
									else
									{	iFirstAlterObjIdx = 0;
										iLastAlterObjIdx  = iNumAlterObjs-1;
								}	}
								else
								{	// find iFirstAlterObjIdx for object specified for mod
									BEMObject* pAlterObj = BEMPX_GetObjectByNameQ( iCID_AlterClass, iError, qsAlterObj );
									if (pAlterObj)
									{	iFirstAlterObjIdx = iLastAlterObjIdx = BEMPX_GetObjectIndex( pAlterObj->getClass(), pAlterObj );			assert( iFirstAlterObjIdx >= 0 );
									}
									else
									{	iRetVal = -4;
										sErrorMsg = QString( "Error applying AnalysisAction %1: Object flagged for alteration '%2' not found" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAlterObj );
									}
							}	}
							else
							{	iRetVal = -3;
								sErrorMsg = QString( "Error applying AnalysisAction %1: AlterObjName undefined" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ) );
						}	}
					}
					if (iRetVal >= 0 && iFirstAlterObjIdx > -2)
					{	switch (lAAType)
						{	case   2 :
							case  12 :	{	// set FLOAT to BEMBase
												double dAltVal = BEMPX_GetFloatAndStatus( lDBID_AnalAct_SetValFloat, iStatus, iSpecialVal, iError, iAA );
												if (iStatus < 1)
												{	iRetVal = -5;
													sErrorMsg = QString( "Error applying AnalysisAction %1: SetValFloat undefined setting %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
												}
												else
												{	for (int iObj=iFirstAlterObjIdx; (iRetVal >= 0 && iObj <= iLastAlterObjIdx); iObj++)
													{
														if (BEMPX_SetBEMData( lDBID_ToSet, BEMP_Flt, (void*) &dAltVal, BEMO_User, iObj ) < 0)
														{	iRetVal = -6;
															sErrorMsg = QString( "Error applying AnalysisAction %1: unable to set %2 to %3 for %4 #%5" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ),
																									QString::number( dAltVal ), qsAAObjProp, sAlterClassName, QString::number( iObj+1 ) );
														}
														else
														{	iRetVal++;
															if (bVerbose)
															{	sLogMsg = QString( "      %1 set to obj #%2, %3  by AnalysisAction %4" ).arg(
																												QString::number( dAltVal ), QString::number( iObj+1 ), qsAAObjProp, AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sAlterClassName );
																BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												}	}	}	}
											}  break;
							case   1 :
							case  11 :	{	// set INTEGER to BEMBase
												long lAltVal = BEMPX_GetIntegerAndStatus( lDBID_AnalAct_SetValInteger, iStatus, iSpecialVal, iError, iAA );
												if (iStatus < 1)
												{	iRetVal = -7;
													sErrorMsg = QString( "Error applying AnalysisAction %1: SetValInteger undefined setting %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
												}
												else
												{	for (int iObj=iFirstAlterObjIdx; (iRetVal >= 0 && iObj <= iLastAlterObjIdx); iObj++)
													{
														if (BEMPX_SetBEMData( lDBID_ToSet, BEMP_Int, (void*) &lAltVal, BEMO_User, iObj ) < 0)
														{	iRetVal = -8;
															sErrorMsg = QString( "Error applying AnalysisAction %1: unable to set %2 to %3 for %4 #%5" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ),
																									QString::number( lAltVal ), qsAAObjProp, sAlterClassName, QString::number( iObj+1 ) );
														}
														else
														{	iRetVal++;
															if (bVerbose)
															{	sLogMsg = QString( "      %1 set to obj #%2, %3  by AnalysisAction %4" ).arg(
																												QString::number( lAltVal ), QString::number( iObj+1 ), qsAAObjProp, AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sAlterClassName );
																BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												}	}	}	}
											}  break;
							case   4 :
							case  15 :				// SAC 10/28/20 - added AppendString
							case  14 :	{	// set STRING to BEMBase
												QString qsAltVal = BEMPX_GetStringAndStatus( lDBID_AnalAct_SetValString, iStatus, iSpecialVal, iError, iAA );
												if (iStatus < 1)
												{	iRetVal = -9;
													sErrorMsg = QString( "Error applying AnalysisAction %1: SetValString undefined setting %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
												}
												else
												{	for (int iObj=iFirstAlterObjIdx; (iRetVal >= 0 && iObj <= iLastAlterObjIdx); iObj++)
													{	QString qsSetStr = qsAltVal;
														if (lAAType == 15)	// SAC 10/28/20 - added AppendString
														{	QString qsExStr = BEMPX_GetStringAndStatus( lDBID_ToSet, iStatus, iSpecialVal, iError, iObj );
															if (iStatus > 0 && !qsExStr.isEmpty())
																qsSetStr = qsExStr + qsAltVal;
														}
														if (BEMPX_SetBEMData( lDBID_ToSet, BEMP_QStr, (void*) &qsSetStr, BEMO_User, iObj ) < 0)
														{	iRetVal = -10;
															sErrorMsg = QString( "Error applying AnalysisAction %1: unable to set '%2' to %3 for %4 #%5" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ),
																									qsSetStr, qsAAObjProp, sAlterClassName, QString::number( iObj+1 ) );
														}
														else
														{	iRetVal++;
															if (bVerbose)
															{	sLogMsg = QString( "      '%1' set to obj #%2, %3  by AnalysisAction %4" ).arg(
																												qsSetStr, QString::number( iObj+1 ), qsAAObjProp, AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sAlterClassName );
																BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												}	}	}	}
											}  break;

							case  22 :	{	// EvalRulelist
												if (pszSimPathFileName && iSimInputExpFileIdx < 0)		// SAC 3/10/20
												{  QString qsOpenSimInpError;
                                       iSimInputExpFileIdx = BEMPX_OpenSimInputExportFile( pszSimPathFileName, qsOpenSimInpError );
                                       if (iSimInputExpFileIdx < 0)
                                       {  iRetVal = iSimInputExpFileIdx-12;  // -14 or -15
                                          sErrorMsg = QString( "Error applying AnalysisAction %1: %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsOpenSimInpError );
                                       }
                                    // replaced following code w/ above to enable access to Sim inputs outside of this routine - SAC 04/23/21
                                    //   iSimInputExpFileIdx = ruleSet.nextExportFileIndex();
												//	if (iSimInputExpFileIdx < 0)
												//	{	iRetVal = -14;
												//		sErrorMsg = QString( "Error applying AnalysisAction %1: too many ruleset export files open:  %2" ).arg(
												//												AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), pszSimPathFileName );
												//	}
												//	else
												//	{	int iOpenRetVal = ruleSet.openExportFile( iSimInputExpFileIdx, pszSimPathFileName, "a+" );
												//		if (iOpenRetVal == 0)
												//			ruleSet.setSimInputExpFileIdx( iSimInputExpFileIdx );
												//		else
												//		{	iRetVal = -15;
												//			sErrorMsg = QString( "Error applying AnalysisAction %1: unable to open simulaiton input file:  %2" ).arg(
												//												AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), pszSimPathFileName );
												//	}	}
                                    }
												if (iRetVal >= 0)
												{	QString qsRLName = BEMPX_GetStringAndStatus( lDBID_AnalAct_SetValString, iStatus, iSpecialVal, iError, iAA );
													if (iStatus < 1)
													{	iRetVal = -12;
														sErrorMsg = QString( "Error applying AnalysisAction %1: unable to retrieve rulelist name from SetValString" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ) );
													}
													else
													{	if (!BEMPX_EvaluateRuleList( qsRLName.toLocal8Bit().constData(), FALSE /*bTagDataAsUserDefined*/, 0 /*iEvalOnlyClass*/,
																																	-1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/, bVerbose ))
													//			bool BEMPX_EvaluateRuleList( LPCSTR listName, BOOL bTagDataAsUserDefined=FALSE, int iEvalOnlyClass=0,	
													//							int iEvalOnlyObjIdx=-1, int iEvalOnlyObjType=0, BOOL bVerboseOutput=FALSE,
													//							void* pvTargetedDebugInfo=NULL, long* plNumRuleEvals=NULL, double* pdNumSeconds=NULL, 
													//							PLogMsgCallbackFunc pLogMsgCallbackFunc=NULL,
													//							QStringList* psaWarningMsgs=NULL );		
														{	iRetVal = -13;
															sErrorMsg = QString( "Error applying AnalysisAction %1: evaluation of rulelist '%2' failed" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsRLName );
														}
														else
															iRetVal++;
												}	}
											}  break;

							case  21 :	{	// RulelistPathFile
												//  AnalysisAction:SetValPathFile       BEMP_Str,  1,  0,  0,  Pres,  "",                 0,  0,                           1001, "SetValuePathFile",  "" 
												QString qsRLFile = BEMPX_GetStringAndStatus( lDBID_AnalAct_SetValPathFile, iStatus, iSpecialVal, iError, iAA );
												if (iStatus < 1)
												{	iRetVal = -16;
													sErrorMsg = QString( "Error applying AnalysisAction %1: RulelistPathFile undefined setting %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
												}
												else if (!FileExists( qsRLFile.toLocal8Bit().constData() ))
												{	iRetVal = -17;
													sErrorMsg = QString( "Error applying AnalysisAction %1: RulelistPathFile file not found:  %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsRLFile );
												}
												else
												{	QString sRLLogFilename = BEMPX_GetLogFilename( false /*bCSVLog*/ );
													int iLogFileExtIdx = sRLLogFilename.lastIndexOf('.');
													if (iLogFileExtIdx > 0)		// need to alter log filename since BEMPX_ParseRuleListFile() will always overwrite it - SAC 11/14/20
														sRLLogFilename = QString( "%1-ParseRL%2" ).arg( sRLLogFilename.left( iLogFileExtIdx ), sRLLogFilename.right( sRLLogFilename.length()-iLogFileExtIdx-1 ) );
													QStringList qslRuleListNames;		QString qsRuleCompileMsg, qsParseRLErrorMsg;
													int iNumRLs = BEMPX_ParseRuleListFile(	qsRLFile.toLocal8Bit().constData(), qslRuleListNames,
																										sRLLogFilename.toLocal8Bit().constData(), &qsRuleCompileMsg, true /*bParseRules*/, &qsParseRLErrorMsg );
													if (!qsParseRLErrorMsg.isEmpty())
													{	iRetVal = -18;
														sErrorMsg = QString( "Error applying AnalysisAction %1: RulelistPathFile parsing error:  %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsParseRLErrorMsg );
													}
													else
														BEMPX_WriteLogFile( QString( "batch RulelistPathFile successful, returned %1, file:  %2" ).arg( QString::number(iNumRLs), qsRLFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
												}
											}  break;

							case  23 :	{	// TablePathFile     - SAC 11/16/20
												//  AnalysisAction:SetValPathFile       BEMP_Str,  1,  0,  0,  Pres,  "",                 0,  0,                           1001, "SetValuePathFile",  "" 
												QString qsTblFile = BEMPX_GetStringAndStatus( lDBID_AnalAct_SetValPathFile, iStatus, iSpecialVal, iError, iAA );
												if (iStatus < 1)
												{	iRetVal = -19;
													sErrorMsg = QString( "Error applying AnalysisAction %1: TablePathFile undefined setting %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsAAObjProp );
												}
												else if (!FileExists( qsTblFile.toLocal8Bit().constData() ))
												{	iRetVal = -20;
													sErrorMsg = QString( "Error applying AnalysisAction %1: TablePathFile file not found:  %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), qsTblFile );
												}
												else
												{	QString sTblLogFilename = BEMPX_GetLogFilename( false /*bCSVLog*/ );
													int iLogFileExtIdx = sTblLogFilename.lastIndexOf('.');
													if (iLogFileExtIdx > 0)		// need to alter log filename since BEMPX_ParseRuleListFile() will always overwrite it - SAC 11/14/20
														sTblLogFilename = QString( "%1-ParseTbl%2" ).arg( sTblLogFilename.left( iLogFileExtIdx ), sTblLogFilename.right( sTblLogFilename.length()-iLogFileExtIdx-1 ) );
													bool bTblLogFileExists = FileExists( sTblLogFilename.toLocal8Bit().constData() );
													int iNumInitTables = ruleSet.numTables();
													QFile fileTblLog( sTblLogFilename );
													try
													{
														if (fileTblLog.open( QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append ))
														{	if (bTblLogFileExists)
																fileTblLog.write( "\n---------\n" );
															fileTblLog.write( QString("parsing table file:  %1\n" ).arg( qsTblFile ).toLocal8Bit().constData() );

															if (!ruleSet.addTable( qsTblFile.toLocal8Bit().constData(), fileTblLog ))
															{	iRetVal = -22;
																sErrorMsg = QString( "Error applying AnalysisAction %1: TablePathFile parsing error occurred, refer to log file:  %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sTblLogFilename );
															}

															fileTblLog.close();                  // close log file
														}
														else
															iRetVal = -21;
													}
													catch (std::exception& e)
													{	iRetVal = -21;
														sErrorMsg = QString( "Error applying AnalysisAction %1: TablePathFile parsing error occurred - cause: %2\n" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), e.what() );
													}
												 	catch (...)
												  	{	iRetVal = -21;
												  	}
												  	if (iRetVal == -21 && sErrorMsg.isEmpty())
														sErrorMsg = QString( "Error applying AnalysisAction %1: TablePathFile parsing error occurred, refer to log file:  %2" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), sTblLogFilename );
													else if (iRetVal >= 0)
													{	int iNumTablesAdded = ruleSet.numTables() - iNumInitTables;
														BEMPX_WriteLogFile( QString( "batch TablePathFile successful, %1 table(s) parsed, file:  %2" ).arg( QString::number(iNumTablesAdded), qsTblFile ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
													}
												}
											}  break;

							default  :	{	// Unrecognized Type
												iRetVal = -11;
												sErrorMsg = QString( "Error applying AnalysisAction %1: unrecognized Type (%2)" ).arg( AnalActDescrip( iAnalPhase, iBeforeAfter, iAA ), QString::number( lAAType ) );
											}  break;
						}	// end: switch (lAAType)
					}
				}	// end of if DBIDs valid
			}	// end of:  for (int iAA=0...

			if (iSimInputExpFileIdx >= 0)		// SAC 3/10/20
            BEMPX_CloseSimInputExportFile( iSimInputExpFileIdx );    // SAC 04/23/21
			//{	ruleSet.closeExportFile( iSimInputExpFileIdx, iSimInputExpFileIdx );
			//	ruleSet.setSimInputExpFileIdx( -1 );
			//}
		}	// end of:  if (iNumAnalActs > 0)
	}	// end of:  if (lDBID_AnalAct_Type > BEM_COMP_MULT)

	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// return value:  >=0 => iSimInputExpFileIdx
//                < 0 => error code (and message)
int BEMPX_OpenSimInputExportFile( const char* pszSimPathFileName, QString& sErrorMsg )    // SAC 04/23/21
{  int iSimInputExpFileIdx = -1;
	if (pszSimPathFileName && strlen( pszSimPathFileName ) > 0)	
	{	iSimInputExpFileIdx = ruleSet.nextExportFileIndex();
		if (iSimInputExpFileIdx < 0)
		{	iSimInputExpFileIdx = -2;
			sErrorMsg = QString( "Unable to open SimInput file: too many ruleset export files open (%1):  %2" ).arg( QString::number( NUM_RULE_EXPORTFILES ), pszSimPathFileName );
		}
		else
		{	int iOpenRetVal = ruleSet.openExportFile( iSimInputExpFileIdx, pszSimPathFileName, "a+" );
			if (iOpenRetVal == 0)
				ruleSet.setSimInputExpFileIdx( iSimInputExpFileIdx );
			else
			{	iSimInputExpFileIdx = -3;
				sErrorMsg = QString( "Unable to open simulation input file:  %1" ).arg( pszSimPathFileName );
	}	}	}
   else
      sErrorMsg = "SimInput path/filename not specified.";
   return iSimInputExpFileIdx;
}

void BEMPX_CloseSimInputExportFile( int iSimInputExpFileIdx )    // SAC 04/23/21
{	if (iSimInputExpFileIdx >= 0)		// SAC 3/10/20
	{	ruleSet.closeExportFile( iSimInputExpFileIdx, iSimInputExpFileIdx );
		ruleSet.setSimInputExpFileIdx( -1 );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_ReadRulesetID()
//
// Purpose ------------------------------------------------------------------
//   Reads the ruleset ID and version strings from the ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR   fileName    : path/filename of the binary encrypted ruleset file.
//   QString& sRuleSetID  : string to populate with ruleset ID
//   QString& sRuleSetVer : string to populate with ruleset version
//   
// Return Value -------------------------------------------------------------
//   TRUE if this ruleset file matches the current RulPrc file version, else
//   FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
BOOL BEMPX_ReadRulesetID( LPCSTR fileName, QString& sRuleSetID, QString& sRuleSetVer )		// was: RuleProcReadRulesetID()
{ 
   //CryptoFile file( fileName, CFile::modeRead | CFile::shareDenyWrite );  // open file
   CryptoFile file( fileName );
   if (!file.open( QIODevice::ReadOnly ))
	{	//sErrMsg = QString( "Error opening BEMProc ruleset file:  '%s'" ).arg( fileName );
		return FALSE;
	}

	// confirm RulPrc version match and read in ruleset ID & version strings
	int iFileStructVer;		bool bRulesSecure=false;
	return CheckRulesetFileVerAndReadID( file, sRuleSetID, sRuleSetVer, iFileStructVer, bRulesSecure );
}

// SAC 8/15/14 - added to retrieve BEMBase filename PRIOR to loading ruleset
BOOL BEMPX_ReadBEMBaseFile( LPCSTR fileName, QString& sBEMBaseFile )			// was: RuleProcReadBEMBaseFile()
{
	BOOL bRetVal = FALSE; 
	sBEMBaseFile.clear();
   //CryptoFile file( fileName, CFile::modeRead | CFile::shareDenyWrite );  // open file
   CryptoFile file( fileName );
   if (!file.open( QIODevice::ReadOnly ))
	{	//sErrMsg = QString( "Error opening BEMProc ruleset file:  '%s'" ).arg( fileName );
	}
	else
	{	// confirm RulPrc version match and read in ruleset ID & version strings
		QString sRuleSetID, sRuleSetVer;
		int iFileStructVer;		bool bRulesSecure=false;
		if (CheckRulesetFileVerAndReadID( file, sRuleSetID, sRuleSetVer, iFileStructVer, bRulesSecure ) && iFileStructVer >= 13)
		{	file.ReadQString( sBEMBaseFile );
			bRetVal = (!sBEMBaseFile.isEmpty());
	}	}
	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  RuleFile()
//
// Purpose ------------------------------------------------------------------
//   Constructor - opens the ASCII ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   QString& fileName  : path/filename of the main ASCII ruleset file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
RuleFile::RuleFile( QString& fileName, QStringList* pslAltPaths /*=NULL*/ )
{
   m_file.Open( fileName.toLocal8Bit().constData(), BEMTextIO::load );
   m_fileName = fileName;

   int iPathLen = std::max( fileName.lastIndexOf('\\'), fileName.lastIndexOf('/') );      // SAC 08/06/21
   if (iPathLen > 0)
      m_slFilePaths.append( fileName.left( iPathLen+1 ) );
   if (pslAltPaths)
   {  for (int i=0; i < (int) pslAltPaths->size(); i++)
         m_slFilePaths.append( pslAltPaths->at(i) );
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  ~RuleFile()
//
// Purpose ------------------------------------------------------------------
//   Destructor - closes the main ASCII ruleset file
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
RuleFile::~RuleFile()
{
   m_file.Close();
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  Read()
//
/////////////////////////////////////////////////////////////////////////////
void RemoveComments( QString& str )
{
	int i, iSize = str.length();
	BOOL bIsQuoted = FALSE;
	BOOL bIsComment = FALSE;
	char chr;
	std::vector<int> iaCommentBegin, iaCommentEnd;
	for (i=0; i<iSize; i++)
	{	chr = str.at(i).toLatin1();
		if (bIsComment)
		{	if (chr == 10)
			{	bIsComment = FALSE;
				iaCommentEnd.push_back( i );  // i-1 );
			}
		}
		else if (bIsQuoted)
		{	if (chr == '"')
				bIsQuoted = FALSE;
		}
		else if ( chr == ';' ||
					(chr == '/' && i < (iSize-1) &&  str[i+1] == '/'))
		{	bIsComment = TRUE;
			iaCommentBegin.push_back( i );
		}
		else if (chr == '"')
			bIsQuoted = TRUE;
	}
	if (bIsComment)
	{	bIsComment = FALSE;
		iaCommentEnd.push_back( iSize-1 );  // iSize-2 );
	}	assert( iaCommentBegin.size() == iaCommentEnd.size() );
			
	for (i=((int) iaCommentBegin.size()-1); i>=0; i--)
		if (iaCommentEnd[i] > iaCommentBegin[i])
		{	if (iaCommentBegin[i] > 0 && iaCommentEnd[i] < str.length())
				str = str.left( iaCommentBegin[i] ) + str.right( str.length() - iaCommentEnd[i] - 1 );
			else if (iaCommentBegin[i] == 0 && iaCommentEnd[i] < str.length())
				str = str.right( str.length() - iaCommentEnd[i] - 1 );
			else if (iaCommentBegin[i] > 0 && iaCommentEnd[i] >= str.length())
				str = str.left( iaCommentBegin[i] );
			else
			{	assert( FALSE );
				str.clear();
			}
		}
}

// SAC 9/11/14 - added routine to check for one or more ruleset labels and return a bool indicating whether the label(s) match the current ruleset
// SAC 12/19/17 - switched from BOOL RulesetLabelMatches() to int RulesetLabelIndex() to return 1-based label index (0 if not found)
int RulesetLabelIndex( BEMTextIO& file, QString token, QStringList& saReservedStrs, BOOL& bTokensSpecified )
{	BOOL iLabelIndex = 1;
	if (file.NextCharacterOnLine() == ':')
	{	iLabelIndex = 0;
		bTokensSpecified = TRUE;
		token = file.ReadToken( FALSE /*bAllowLeadingDigit*/, FALSE /*bSkipLeadingDelimeters*/, FALSE /*bAllowMidHyphen*/, FALSE /*bAllowNewLineRead*/ );
		if (!token.compare(":"))
			token = file.ReadToken( FALSE /*bAllowLeadingDigit*/, FALSE /*bSkipLeadingDelimeters*/, FALSE /*bAllowMidHyphen*/, FALSE /*bAllowNewLineRead*/ );
		else if (token.length() > 1 && token[0] == ':')
			token = token.right( token.length()-1 );
		while (iLabelIndex==0 && !token.isEmpty() && IndexInStringArray( saReservedStrs, token ) == -1)
		{	iLabelIndex = ruleSet.LabelIndex( token );
			token = file.ReadToken( FALSE /*bAllowLeadingDigit*/, FALSE /*bSkipLeadingDelimeters*/, FALSE /*bAllowMidHyphen*/, FALSE /*bAllowNewLineRead*/ );
		}
		if (iLabelIndex > 0 && !file.AtEOL())
		{	// continue reading tokens until next valid RULE token found...
			file.SkipToEndOfLine();
			file.GetLine();
		}
		else if (iLabelIndex == 0)
			QString token2 = file.ReadToNextToken( saReservedStrs );
	}
	else
		bTokensSpecified = FALSE;
	return iLabelIndex;
}


bool StringHadAlphaOrNumeric( QString& str )
{
	int iSize = str.length();
	char chr;
	for (int i=0; i<iSize; i++)
	{	chr = str.at(i).toLatin1();
		if ( (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || (chr >= '0' && chr <= '9') )
			return true;
	}
	return false;
}

static inline int IntegerInArray( std::vector<int>& iaVals, int& iVal )  // SAC 1/13/19 - copied from expRule.cpp
{	int iSize = (int) iaVals.size();
	for (int j=0; j<iSize; j++)
	{	if (iaVals[j] == iVal)
			return j;
	}
	return -1;
}

bool RuleFile::ReadRuleFile( const char* pszRulePathFile, QStringList& saReservedStrs,
										std::vector<RuleList*>& paTransformRulelists, QFile& errorFile,
										int iRuleFileReadIteration, int i1RuleFileIdx /*=0*/ )
{
   bool bRetVal = TRUE;
   try
   {  // open file
      BEMTextIO file( pszRulePathFile, BEMTextIO::load );

      // write message to error file indicating that we are reading this table file
      QString readMsg = QString("Reading rule file: %1\n").arg( pszRulePathFile );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

		BOOL bInBetweenReadingRules=FALSE;
      try
      {
         try
         {
				QString sRuleFileNoPath = pszRulePathFile;
				sRuleFileNoPath.replace( '\\', '/' );
				if (sRuleFileNoPath.lastIndexOf('/') > 1)
					sRuleFileNoPath = sRuleFileNoPath.right( sRuleFileNoPath.length() - sRuleFileNoPath.lastIndexOf('/') - 1 );

            //int iRuleIdx = 0;
			   QString token = file.ReadToken();
				QString token2;
				while (!token.isEmpty())
				{	if (token == "RULE")
					{	if (iRuleFileReadIteration != 1)
						{	// skip over RULE reading this time through the file
							QStringList saEndRule;
							saEndRule.push_back( "ENDRULE" );		saEndRule.push_back( "ENDRUL" );
							token2 = file.ReadToNextToken( saEndRule );  // saReservedStrs );
							token2 = file.ReadToken();  // read past ENDRULE token
						}
						else
						{	int iError;
							BOOL bRuleNew = FALSE;
							BOOL bContinue = TRUE;
							// based on Rule members
   						int     iNumIndirections = 1;                     // # of database IDs stored in the following array
   						long    lDatabaseID[ MAX_NUM_INDIRECTIONS ];  // DBIDs used to determine what data in database to set
   						int     iNumAncestors = 0;										// # of object types stored in the following array
   						int     iaAncestorObjTypes[ MAX_NUM_INDIRECTIONS ];	// 1-based indexes of object types that make up the ancestors of object rule to be evaluated on
							QString sFullDBIDStr, sErr;
							RuleSetProperty* pNewRuleProp = NULL;
							for (int iD=0; iD < MAX_NUM_INDIRECTIONS; iD++)
							{	lDatabaseID[iD] = 0;
   							iaAncestorObjTypes[iD] = 0;
							}
							file.ReadBEMProcParam( token );
							if (token.length()==1 && !token.compare(":"))
							{	// this is a generic, blank rule, so skip to end of the rule and search for subsequent rule
								bContinue = FALSE;
							}
							else
							{	int iLastColon, iNextColon;
								if (token.length()==3 && !token.compare("NEW", Qt::CaseInsensitive))
								{	bRuleNew = TRUE;
									file.ReadBEMProcParam( token );
								}
								sFullDBIDStr = token;
								QString sSaveFullDBIDStr = sFullDBIDStr;
								iLastColon = sFullDBIDStr.lastIndexOf(':');				assert( iLastColon > 0 );
								if (iLastColon < 1)
								{	// report error but go ahead and continue parsing file - no need to abort - this property will simply receive the "default" DataType
									sErr = QString( "\n\tError:  Invalid Object:Property rule ID '%1' found on line: %2\n" ).arg( sFullDBIDStr, QString::number( file.GetLineCount() ) );
									errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
                  	      // skip to end of rule
									bContinue = FALSE;
									bRetVal = FALSE;
								}
								else
								{	QString sAncestorStr;
									int iMainRuleObjType = -1;
									QString sObjType;

							// SAC 9/10/14 - code to check for specification of new RULESETS token
									token = file.ReadToken();									assert( token.left(6).compare("ENDRUL", Qt::CaseInsensitive) );	// ensure next token NOT ENDRULE
									if (!token.compare("RULESETS", Qt::CaseInsensitive))
									{	BOOL bRulesetLabelConsistent = FALSE;
										token = file.ReadToken();
										while (!bRulesetLabelConsistent && IndexInStringArray( saReservedStrs, token ) == -1)
										{	bRulesetLabelConsistent = (ruleSet.LabelIndex( token ) > 0);
											token = file.ReadToken();
										}
										if (bRulesetLabelConsistent)
										{	// continue reading tokens until next valid RULE token found...
											while (IndexInStringArray( saReservedStrs, token ) == -1)
												token = file.ReadToken();
											assert( token.left(6).compare("ENDRUL", Qt::CaseInsensitive) );					// next token should NOT be ENDRULE
										}
										else
											bContinue = FALSE;	// this RULE is not to be compiled into this ruleset because the RULESETS token(s) not consistent w/ this ruleset's LABELS
									}

									if (bRuleNew && bContinue)
									{	QString sNewFullPath = sSaveFullDBIDStr;
										QString sNewPropName = sNewFullPath.right( sNewFullPath.length()-iLastColon-1 );
										sNewFullPath = sNewFullPath.left( iLastColon );
										iNextColon = sNewFullPath.lastIndexOf(':');
										sObjType = sNewFullPath.right( sNewFullPath.length()-iNextColon-1 );
										int iObjTypeID = BEMPX_GetDBComponentID( sObjType.toLocal8Bit().constData() );
										if (iObjTypeID < 1)
										{	// report error but go ahead and continue parsing file - no need to abort - this property will simply receive the "default" DataType
											sErr = QString( "\n\tError:  Invalid Object type '%1' in rule '%2' found on line: %3\n" ).arg( sObjType, sNewFullPath, QString::number(file.GetLineCount()) );
											errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
                  	   		   // skip to end of rule
											bContinue = FALSE;
											bRetVal = FALSE;
										}
										else
										{	BEMClass* pObjClass = BEMPX_GetClass( iObjTypeID, iError );			assert( pObjClass );
											if (!pObjClass)
												bContinue = FALSE;
											else if (BEMPX_GetDatabaseID( sNewPropName, iObjTypeID ) > BEM_COMP_MULT)
											{	sErr = QString( "\n\tError:  Invalid RULE NEW property '%1' already exists in data model - rule '%2' found on line: %3\n" ).arg( sNewPropName, sNewFullPath, QString::number(file.GetLineCount()) );
												errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
                  	   		   	// skip to end of rule
												bContinue = FALSE;
												bRetVal = FALSE;
											}
											else
											{	// check for this being a duplicate RULE NEW - which is OK
												int iNumCurRuleProps = ruleSet.numRulesetProperties();
												for (int j=0; (lDatabaseID[0]<1 && j<iNumCurRuleProps); j++)
												{  RuleSetProperty* pRP = ruleSet.getRuleSetProperty(j);       assert( pRP );
												   if (pRP && pRP->getObjTypeID() == iObjTypeID && ( !pRP->getPropName().compare(     sNewPropName, Qt::CaseInsensitive ) ||
																													  !pRP->getPropNameLong().compare( sNewPropName, Qt::CaseInsensitive )))
													{	lDatabaseID[0] = pRP->getDBID();
														pNewRuleProp = pRP;
													}
												}

												if (lDatabaseID[0] < 1)
												{	int iNewPropID = pObjClass->getNumProps() + ruleSet.NumRulesetPropertiesForObject( iObjTypeID ) + 1;
													if (iNewPropID >= (BEM_COMP_MULT/BEM_PARAM_MULT))		// SAC 9/22/20 - added error if/when max # properties exceeded w/ a RULE NEW
													{	sErr = QString( "\n\tError:  Maximum # Properties per Class (%1) exceeded @ RULE NEW property '%2' - rule '%3' found on line: %4\n" ).arg( QString::number((BEM_COMP_MULT/BEM_PARAM_MULT)), sNewPropName, sNewFullPath, QString::number(file.GetLineCount()) );
														errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
            		      	   				bContinue = FALSE;
														bRetVal = FALSE;
													}
													else
													{	lDatabaseID[0] = BEMPX_GetDBID( iObjTypeID, iNewPropID, 1 );
														pNewRuleProp = new RuleSetProperty( iObjTypeID, iNewPropID, sNewPropName, sNewPropName, lDatabaseID[0] );				assert( pNewRuleProp );
														if (!pNewRuleProp)
															bContinue = FALSE;
														else
															ruleSet.addRuleSetProperty( pNewRuleProp );
												}	}

                                    if (bContinue && iNextColon > 0)
												{	sAncestorStr = sNewFullPath.left( iNextColon );	// SAC 4/11/13
													iMainRuleObjType = iObjTypeID;									assert( iMainRuleObjType > 1 );
												}
											}
										}
									}
									else if (bContinue)  // and NOT a RULE NEW
									{
										QString sRuleID = QString( "Rule block setting %1" ).arg( sFullDBIDStr );
										sAncestorStr = sFullDBIDStr;
										if (!ParseRuleDBID( sRuleID, sFullDBIDStr, iNumIndirections, lDatabaseID, errorFile ) || lDatabaseID[0] < 1)  // SAC 5/21/13 - make sure this gets logged as ERROR
                  	   		{	assert( FALSE );
											// skip to end of rule
											bContinue = FALSE;
											bRetVal = FALSE;
											sAncestorStr.clear();
										}
										else if (sAncestorStr.length() > sFullDBIDStr.length()+1)
										{	sAncestorStr = sAncestorStr.left( sAncestorStr.length() - sFullDBIDStr.length() - 1 );		// SAC 4/11/13
											iMainRuleObjType = BEMPX_GetClassID( lDatabaseID[0] );			assert( iMainRuleObjType > 1 );
										}
										else
											sAncestorStr.clear();
									}

							// SAC 4/11/13 - Parse ancestor string for runtime checks on proper Parent/GParent/GGParent ancestry during rule evaluation
									if (!sAncestorStr.isEmpty())
									{	// PARSE ANCESTOR STRING
										int iParObjTypeID = iMainRuleObjType;																assert( iParObjTypeID > 0 );
										QString sAncErrMsg;
										do
										{
											BEMClass* pCurObjClass = (iParObjTypeID < 1 ? NULL : BEMPX_GetClass( iParObjTypeID, iError ));
											if (pCurObjClass == NULL)
												// ERROR - unrecognized object type
												sAncErrMsg = QString( "Unable to load class pointer for object type %1" ).arg( QString::number(iParObjTypeID) );
											else
											{	iNextColon = sAncestorStr.lastIndexOf( ':' );
												sObjType = (iNextColon < 0 ? sAncestorStr : sAncestorStr.right( sAncestorStr.length() - iNextColon - 1 ));
												iParObjTypeID = BEMPX_GetDBComponentID( sObjType.toLocal8Bit().constData() );
												if (iParObjTypeID < 1)
													// ERROR - unrecognized object type
													sAncErrMsg = QString( "Unrecognized object type '%1'" ).arg( sObjType );
												else if (!pCurObjClass->ClassInParentList( iParObjTypeID ))
												{	// ERROR - not a valid parent/child relationship
													BEMClass* pParObjClass = BEMPX_GetClass( iParObjTypeID, iError );			assert( pParObjClass != NULL );
													sAncErrMsg = QString( "'%1' not a valid parent of '%2'" ).arg( (pParObjClass ? pParObjClass->getShortName() : "<unknown>"), pCurObjClass->getShortName() );
												}
												else
												{
   												iaAncestorObjTypes[iNumAncestors++] = iParObjTypeID;
													if (iNextColon > 0)
														sAncestorStr = sAncestorStr.left( iNextColon );
													else
														sAncestorStr.clear();
												}
											}
										} while (sAncErrMsg.isEmpty() && !sAncestorStr.isEmpty() && iNumAncestors < MAX_NUM_INDIRECTIONS);

										if (sAncErrMsg.isEmpty() && iNumAncestors >= MAX_NUM_INDIRECTIONS && !sAncestorStr.isEmpty())
											// ERROR - too many ancestor object types listed !!
											sAncErrMsg = QString( "Too many generations specified, max of %1, '%2' remaining to be parsed" ).arg( QString::number(MAX_NUM_INDIRECTIONS), sAncestorStr );

										if (!sAncErrMsg.isEmpty())
										{
											sErr = QString( "\n\tError:  Unable to parse ancestry of RULE property '%1' - %2  on line: %3\n" ).arg( sSaveFullDBIDStr, sAncErrMsg, QString::number(file.GetLineCount()) );
											errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
                  	   		   // skip to end of rule
											bContinue = FALSE;
											bRetVal = FALSE;
										}
									}
							// SAC 4/11/13 - end of - Parse ancestor string for runtime checks on proper Parent/GParent/GGParent ancestry during rule evaluation
								}
							}
            	
							QStringList saTokensProcessed;
							std::vector<int> iaTokenIndices;
							std::vector<int> iaTransformRulesProcessed;  // SAC 1/13/19 - added secondary transform rulelist idx array to ensure no rule expression duplications
							if (!bContinue)
							{	// this is a generic, blank rule, so skip to end of the rule and search for subsequent rule
								if (!token.left(6).compare("ENDRUL", Qt::CaseInsensitive))
								{	assert( FALSE );		// token sholdn't already be loaded w/ ENDRUL... (??)
								}
								else
								{	QStringList saEndRule;
									saEndRule.push_back( "ENDRULE" );		saEndRule.push_back( "ENDRUL" );
									token2 = file.ReadToNextToken( saEndRule );  // saReservedStrs );
								}
								token2 = file.ReadToken();  // read past ENDRULE token
							}
							else
							{	QString sRuleHelp, sRuleDescrip;
								int iTokenID = IndexInStringArray( saReservedStrs, token );
								while (iTokenID >= 0 && iTokenID != DMRuleReserved_EndRule && iTokenID != DMRuleReserved_EndRule2)		// also ensure bRetVal still TRUE ???		// token != "ENDRULE")
								{
					// SAC 9/11/14 - code to process ruleset labels possibly trailing RULE token -AND- to catch duplicate tokens in single RULE block
									BOOL bTokensSpecified = FALSE;
									int iLabelIndex = RulesetLabelIndex( file, token, saReservedStrs, bTokensSpecified );	// SAC 12/19/17
									BOOL bProcessToken = (iLabelIndex > 0);
									if (bProcessToken)
									{	QString sThisToken = (iTokenID < DMRuleReserved_EndRule ? pszDMRuleReserved[iTokenID] : token);
										int iTokensProcessedIdx = IndexInStringArray( saTokensProcessed, sThisToken );
										if (iTokensProcessedIdx >= 0)
										{	bProcessToken = FALSE;
											int iFileErrLine = file.GetLineCount();
											token2 = file.ReadToNextToken( saReservedStrs );	// skip to next token
											if (iTokenID <= DMRuleReserved_EndRule2 && bTokensSpecified && iLabelIndex <= iaTokenIndices[iTokensProcessedIdx])
											{	// report error re: duplicate tokens found, but allow reading/parsing to continue
												// added logic to only report error if INDEX of token in label list is <= the index stored when this token was first processed,
												// allowing for mroe general (but matching) tokens to follow more specific ones.  - SAC 12/19/17
												sErr = QString( "\n\tERROR:  '%1' can only be specified once per RULE block - duplicate found on line: %2 of '%3'\n" ).arg( sThisToken, QString::number(iFileErrLine), file.FileName() );
												errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );			assert( FALSE );
												bContinue = FALSE;	// skip to end of rule
												bRetVal = FALSE;
											}
											else
											{	// SAC 1/13/19 - added logging of skipped tokens (for debugging purposes initially)
#ifdef _DEBUG
												QString sDbgIssue = QString( "      Duplicate token being skipped '%1' found on line: %2 of '%3'\n" ).arg( sThisToken, QString::number(iFileErrLine), file.FileName() );
												errorFile.write( sDbgIssue.toLocal8Bit().constData(), sDbgIssue.length() );
												sDbgIssue = "            tokens already processed:  ";
												int iDbg;
												for (iDbg=0; iDbg<(int)saTokensProcessed.size(); iDbg++)
													sDbgIssue += QString( "%1 (%2)  /  " ).arg(saTokensProcessed[iDbg], QString::number(iaTokenIndices[iDbg]));
												sDbgIssue += QString( "\n" );
												errorFile.write( sDbgIssue.toLocal8Bit().constData(), sDbgIssue.length() );
												if (iTokenID > DMRuleReserved_EndRule2)
													sDbgIssue = QString( "            continue because iTokenID (%1) > DMRuleReserved_EndRule2 (%2)\n" ).arg( QString::number(iTokenID), QString::number(DMRuleReserved_EndRule2) );
												else if (!bTokensSpecified)
													sDbgIssue = "            continue because !bTokensSpecified\n";
												else if (iLabelIndex > iaTokenIndices[iTokensProcessedIdx])
													sDbgIssue = QString( "            continue because iLabelIndex (%1) > iaTokenIndices[iTokensProcessedIdx] (%2)\n" ).arg( QString::number(iLabelIndex), QString::number(iaTokenIndices[iTokensProcessedIdx]) );
												errorFile.write( sDbgIssue.toLocal8Bit().constData(), sDbgIssue.length() );
#endif
											}
										}
										else
										{	saTokensProcessed.push_back( sThisToken );
											iaTokenIndices.push_back( iLabelIndex );
									}	}

									if (bProcessToken)
									{	switch (iTokenID)
										{	case DMRuleReserved_DataType :		// token == "DATATYPE")
																				{	assert( pNewRuleProp );
																					token2 = file.ReadToNextToken( saReservedStrs );
																					if (pNewRuleProp)
																					{	// assert( pNewRuleProp->getPropType() < 0 );
																						token2 = token2.trimmed();
																						int idx = -1;
																						while (pNewRuleProp->getPropType() < 0 && pszDMRuleDataTypes[++idx] != NULL)
																						{	if (!token2.compare( pszDMRuleDataTypes[idx], Qt::CaseInsensitive ))
																								pNewRuleProp->setPropType( siaDMRuleDataTypes[idx] );
																						}
																						if (pNewRuleProp->getPropType() < 0)
																						{	// must be an Object reference
																							int iCompID = BEMPX_GetDBComponentID( token2.toLocal8Bit().constData() );
																							if (iCompID > 0)
																							{	pNewRuleProp->setPropType( BEMP_Obj );
																								pNewRuleProp->setPropTypeObjID( iCompID );
																							}
																							else
																							{	// report error
																								sErr = QString( "\n\tERROR:  Unrecognized Data Type '%1' found on line: %2 of '%3'\n" ).arg( token2, QString::number(file.GetLineCount()), file.FileName() );
																								errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																								bContinue = FALSE;	// skip to end of rule
																								bRetVal = FALSE;
																							}
																						}
																					}
																					else
																					{	// report error, but allow reading/parsing to continue
																						sErr = QString( "\n\tERROR:  'DATATYPE' can only be specified in RULE NEW rules - found on line: %1 of '%2'\n" ).arg( QString::number(file.GetLineCount()), file.FileName() );
																						errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																						bContinue = FALSE;	// skip to end of rule
																						bRetVal = FALSE;
																					}
																				}	break;
											case DMRuleReserved_ShortForm :		// token == "SHORTFORM"
											case DMRuleReserved_LongForm :		// token == "LONGFORM"
																				{	assert( pNewRuleProp );
																					token2 = file.ReadToNextToken( saReservedStrs );
																					if (pNewRuleProp)
																					{	token2 = token2.trimmed();
																						if (token2.length() <= 0)
																						{	// report error
																							sErr = QString( "\n\tError:  Invalid or missing %1 found on line: %2 of '%3'\n" ).arg( saReservedStrs[iTokenID], QString::number(file.GetLineCount()), file.FileName() );
																							errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																							bContinue = FALSE;	// skip to end of rule
																							bRetVal = FALSE;
																						}
																						else if (iTokenID == DMRuleReserved_ShortForm)
																						{	pNewRuleProp->setPropName( token2 );
																							if (token2.length() > pNewRuleProp->getPropNameLong().length())
																							{	assert( FALSE );
																								sErr = QString( "\n\tWarning:  Property short name '%1' longer than long name '%2' - found on line: %3 of '%4'\n" ).arg( token2, pNewRuleProp->getPropNameLong(), QString::number(file.GetLineCount()), file.FileName() );
																								errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																								//bRetVal = FALSE;   - allow compilation to succeed
																							}
																						}
																						else
																						{	pNewRuleProp->setPropNameLong( token2 );
																							if (token2.length() < pNewRuleProp->getPropName().length())
																							{	assert( FALSE );
																								sErr = QString( "\n\tWarning:  Property long name '%1' shorter than short name '%2' - found on line: %3 of '%4'\n" ).arg( token2, pNewRuleProp->getPropName(), QString::number(file.GetLineCount()), file.FileName() );
																								errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																								//bRetVal = FALSE;   - allow compilation to succeed
																							}
																						}
																					}
																					else
																					{	// report error, but allow reading/parsing to continue
																						//QString sErr;
																						sErr = QString( "\n\tERROR:  '%1' can only be specified in RULE NEW rules - found on line: %2 of '%3'\n" ).arg( saReservedStrs[iTokenID], QString::number(file.GetLineCount()), file.FileName() );
																						errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																						bContinue = FALSE;	// skip to end of rule
																						bRetVal = FALSE;
																					}
																				}	break;
											case DMRuleReserved_Description :		// token == "DESCRIPTION")
																				{	sRuleDescrip = file.ReadString( TRUE /*ReadPastEOL*/ );
																				}	break;
											case DMRuleReserved_Help :		// token == "HELP")
																				{	sRuleHelp = file.ReadString( TRUE /*ReadPastEOL*/ );
																				}	break;
											case DMRuleReserved_Reference :		// token == "REFERENCE")   i.e.  ACM-5.5.4  App5.5C-Table143A  App5.5C-Table143B  App5.5C-Table5.5.1
																				{	token2 = file.ReadToNextToken( saReservedStrs );
																				}	break;
											case DMRuleReserved_InputClass :		// token == "INPUTCLASS")
																				{	token2 = file.ReadToken();
																					if (BEMPX_GetPropertyID( lDatabaseID[iNumIndirections-1] ) == 0)
																					{	// ignore DataType info for special "reserved" properties such as "Name"
																					}
																					else
																					{	int iDataTypeEnum = StringToDataTypeEnum( token2 );
																						if (iDataTypeEnum < 0)
																						{	// report error but go ahead and continue parsing file - no need to abort - this property will simply receive the "default" DataType
																							//QString sErr;
																							sErr = QString( "\n\tERROR:  Unrecognized Input Class '%1' found on line: %2\n" ).arg( token2, QString::number(file.GetLineCount()) );
																							errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																						}
																						else
																						{	int iNotInputMode = BEMPropertyDataType::NotInp_AllowUIReset;		QString sNotInputMsg;
																							if (iDataTypeEnum == BEMPropertyDataType::NotInput)
																							{	// add code to read and process additional BEMPropertyDataType settings (only for NotInput)
																								int iNILineCnt = file.GetLineCount();
																								token2 = file.ReadToNextToken( saReservedStrs );
																								if (token2.length() > 5 && token2[0] != ';' && (token2[0] != '/' || token2[1] != '/'))
																								{	token2 = token2.trimmed();
																									QString sNotInpType;
																									int iDTSpcIdx = token2.indexOf(' ');
																									if (iDTSpcIdx > 0)
																									{	sNotInpType = token2.left( iDTSpcIdx );
																										token2 = token2.right( token2.length()-iDTSpcIdx-1 );
																										token2 = token2.trimmed();		// was: token2.TrimLeft();
																									}
																									else
																									{	sNotInpType = token2;
																										token2.clear();
																									}
																									if (sNotInpType.compare( "IgnoreUserInput", Qt::CaseInsensitive )==0)
																										iNotInputMode = BEMPropertyDataType::NotInp_IgnoreUserInput;
																									else if (sNotInpType.compare( "ErrorIfInput", Qt::CaseInsensitive )==0)
																										iNotInputMode = BEMPropertyDataType::NotInp_ErrorIfInput;
																									else if (sNotInpType.compare( "AllowUIReset", Qt::CaseInsensitive )==0)
																									{	// nothing here
																									}
																									else
																									{	sErr = QString( "\n\tERROR:  Unrecognized NotInput type '%1' found on line: %2  (expecting 'AllowUIReset', 'IgnoreUserInput' or 'ErrorIfInput')\n" ).arg( sNotInpType, QString::number(iNILineCnt) );
																										errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																										bRetVal = FALSE;
																									}

																									if (token2.length() > 2 && token2[0] != ';' && (token2[0] != '/' || token2[1] != '/'))
																									{	assert( token2[0] == '\"' && token2[(token2.length()-1)] == '\"' );
																										if (token2[0] == '\"' && token2[(token2.length()-1)] == '\"')
																										{	sNotInputMsg = token2.mid( 1, token2.length()-2 );
																											FormatMultilineString( sNotInputMsg );
																											sNotInputMsg = sNotInputMsg.trimmed();
																									}	}
																							}	}
																							BEMPropertyDataType* pDT = new BEMPropertyDataType( lDatabaseID[iNumIndirections-1], iDataTypeEnum,
																														(iDataTypeEnum==BEMPropertyDataType::Compulsory) /*bPrimary*/, true /*bEditable*/, 
																														true /*bUserDefault*/, true /*bDisplayInput*/, true /*bDisplayProposed*/, 
																														true /*bDisplayBudget*/, iNotInputMode, sNotInputMsg.toLocal8Bit().constData() );		assert( pDT );
																							if (pDT)
																								ruleSet.addDataType( pDT );
																						}
																					}
																				}	break;
											case DMRuleReserved_Option :		// token == "OPTION")
																				{	SymDepLst* pCurSymDepLst = NULL;
																					if (BEMPX_GetPropertyID( lDatabaseID[iNumIndirections-1] ) == 0)
																					{	// ignore enumeration definitions for special "reserved" properties such as "Name"
																					}
																					else
																					{	SymLst* pCurSymLst = new SymLst;				assert( pCurSymLst );
																						if (pCurSymLst)
																						{	ruleSet.addSymLst( pCurSymLst );		// => create a new SymLst object & add it to the list
																							pCurSymLst->m_lDBID[ pCurSymLst->m_iNumDBIDs++ ] = lDatabaseID[iNumIndirections-1];
																							pCurSymDepLst = new SymDepLst( -1 /*default value*/ );  // default value of -1 should result in no default provided for the list - OK ???
																							assert( pCurSymDepLst );
																							if (pCurSymDepLst)
																								pCurSymLst->m_olSymDepLists.push_back( pCurSymDepLst );
																						}	// symbol list stuff now all setup (or not) - in any case, read each line as new symbol searching for the NEXT reserved ruleset term
																					}
            	                 	
																					token2 = file.ReadToNextToken( saReservedStrs, FALSE /*bReadPastEOL*/ );
																					long iSymbolID = 1;
																					while (!token2.isEmpty())
																					{	if (pCurSymDepLst)
																						{	token2 = token2.trimmed();
																							if (token2.length() > 2 && (token2[0]==';' || (token2[0]=='/' && (token2[1]=='/' || token2[1]=='*'))))
																							{	// ignore symbols that are comments
																								assert( token2[0]!='/' || token2[1]!='*' );  // open-ended comment closure search not currently implemented
																							}
																							else
																							{	Sym* pCurSym = new Sym( token2.toLocal8Bit().constData(), iSymbolID );				assert( pCurSym );
																								if (pCurSym)
																								{	pCurSymDepLst->m_olSymbols.push_back( pCurSym );
																									iSymbolID++;
																								}
																							}
																						}
																						token2 = file.ReadToNextToken( saReservedStrs, FALSE /*bReadPastEOL*/ );
																					}
																					if (iSymbolID > 1 && pNewRuleProp)
																					{	assert( (pNewRuleProp->getPropType() < 0 || pNewRuleProp->getPropType() == BEMP_Sym) );
																						pNewRuleProp->setPropType( BEMP_Sym );
																					}
																				}	break;

											case DMRuleReserved_Resets :		// token == "RESETS")  - SAC 11/3/16
																				{	bool bResetForward = true;
																					std::vector<long> locDBID, listDBIDs;
																					locDBID.push_back( lDatabaseID[iNumIndirections-1] );
																					int iCompID = BEMPX_GetClassID( lDatabaseID[iNumIndirections-1] );			assert( iCompID > 0 );
																					int iResetLineCnt = file.GetLineCount();
																					token2 = file.ReadToNextToken( saReservedStrs, FALSE /*bReadPastEOL*/ );
																					while (!token2.isEmpty())
																					{
																						sErr.clear();
																						if (!token2.compare("ResetTheFollowingWhenThisIsModified", Qt::CaseInsensitive) ||
																							 !token2.compare("ResetThisWhenTheFollowingIsModified", Qt::CaseInsensitive))
																						{	if (listDBIDs.size() > 0)
																							{	if (bResetForward)
																									ruleSet.addReset( locDBID, listDBIDs );
																								else
																									ruleSet.addReset( listDBIDs, locDBID );
																								listDBIDs.clear();
																							}
																							bResetForward = (!token2.compare("ResetTheFollowingWhenThisIsModified", Qt::CaseInsensitive));
																						}
																						else
																						{	int iColon = token2.indexOf( QChar(':') );
																							long lDBID = BEMPX_GetDatabaseID( token2, (iColon > 0 ? 0 : iCompID) );		assert( lDBID > 0 );
																							assert( (iColon < 1 || iCompID == BEMPX_GetClassID( lDBID )) );
																							if (lDBID < 1)
																								sErr = QString( "\n\tERROR:  Unrecognized RESETS property '%1' found on line: %2\n" ).arg( token2, QString::number(iResetLineCnt) );
																							else if (iColon > 0 && iCompID != BEMPX_GetClassID( lDBID ))
																							{	BEMClass* pCls = BEMPX_GetClass( iCompID, iError );
																								sErr = QString( "\n\tERROR:  Invalid RESETS component type '%1' (expecting %2 property) found on line: %3\n" ).arg(
																														token2, (pCls ? pCls->getShortName() : "<unknown>"), QString::number(iResetLineCnt) );
																							}
																							else
																								listDBIDs.push_back( lDBID );
																						}
																						if (!sErr.isEmpty())
																						{	errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																							bRetVal = FALSE;
																						}
																						iResetLineCnt = file.GetLineCount();
																						token2 = file.ReadToNextToken( saReservedStrs, FALSE /*bReadPastEOL*/ );
																					}
																					if (listDBIDs.size() > 0)
																					{	if (bResetForward)
																							ruleSet.addReset( locDBID, listDBIDs );
																						else
																							ruleSet.addReset( listDBIDs, locDBID );
																						listDBIDs.clear();
																					}
																				}	break;

											case DMRuleReserved_PrevNames	:	// token == "PREVIOUSNAMES")  - SAC 8/6/15
																				{	token2 = file.ReadToNextToken( saReservedStrs );
																					if (pNewRuleProp)
																					{	assert( FALSE );		// PrevNames not compatible w/ RULE NEWs
																					}
																					else
																					{	token2 = token2.trimmed();		// was: token2.TrimLeft();
																						int iSpcIdx = token2.indexOf(' ');
																						while (iSpcIdx > 0)
																						{	QString sPrevName = token2.left( iSpcIdx );
																					// ADD sPrevName to prev name array
																							ruleSet.addRulePropTypeMod( lDatabaseID[iNumIndirections-1], sPrevName.toLocal8Bit().constData() );
																							token2 = token2.right( token2.length()-iSpcIdx-1 );
																							token2 = token2.trimmed();		// was: token2.TrimLeft();
																							iSpcIdx = token2.indexOf(' ');
																						}
																						if (!token2.isEmpty())
																							ruleSet.addRulePropTypeMod( lDatabaseID[iNumIndirections-1], token2.toLocal8Bit().constData() );
																					}
																				}	break;
											case DMRuleReserved_Units :		// token == "UNITS")
																				{	token2 = file.ReadToNextToken( saReservedStrs, FALSE /*bReadPastEOL*/ );  // SAC 6/10/18 - don't read past EOL to prevent capturing comment lines following units 
																					if (pNewRuleProp)
																					{	assert( (pNewRuleProp->getPropType() < 0 || pNewRuleProp->getPropType() == BEMP_Flt) );
																						if (pNewRuleProp->getPropType() >= 0 && pNewRuleProp->getPropType() != BEMP_Flt)
																						{	BEMClass* pNRPCls = BEMPX_GetClass( pNewRuleProp->getObjTypeID(), iError );
																							const char* pszPropTypeStr = PropTypeIDToString( pNewRuleProp->getPropType() );
																							sErr = QString( "\n\tWarning:  Property '%1:%2' of type '%3' being assigned units '%4' - found on line: %5 of '%6'\n" ).arg(
																								(pNRPCls ? pNRPCls->getShortName() : "unknown"), pNewRuleProp->getPropName(), (pszPropTypeStr ? pszPropTypeStr : "unknown"),
																								token2, QString::number(file.GetLineCount()), file.FileName() );
																							errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																						}
																						pNewRuleProp->setPropType( BEMP_Flt );
																						pNewRuleProp->setUnits( token2 );		// SAC 8/6/14 - added storage of Units specified in rule new block
																					}
																				}	break;
            	                 	
											case DMRuleReserved_ReportPrec :		// token == "REPORTPRECISION")	SAC 2/5/15
																				{	int iReportPrec = file.ReadLong();								assert( iReportPrec >= -9 && iReportPrec < 9 );
																					token2 = file.ReadToNextToken( saReservedStrs );
																					if (pNewRuleProp)
																						pNewRuleProp->setReportPrecision( iReportPrec );
																					else
																						ruleSet.addRulePropTypeMod( lDatabaseID[iNumIndirections-1], iReportPrec );
																				}	break;
											case DMRuleReserved_CommonMin :		// token == "COMMONMINIMUM")
											case DMRuleReserved_CommonMax :		// token == "COMMONMAXIMUM")
											case DMRuleReserved_Minimum   :		// token == "MINIMUM")
											case DMRuleReserved_Maximum   :		// token == "MAXIMUM")
																				{	token2 = file.ReadToNextToken( saReservedStrs );
																					if (BEMPX_GetPropertyID( lDatabaseID[iNumIndirections-1] ) == 0)
																					{	// ignore Range info for special "reserved" properties such as "Name"
																					}
																					else if (token2.isEmpty())
																					{	// ignore blank range check definitions
																					}
																					else
																					{	int iSeverity = RANGE_ERROR;		//	RANGE_ERROR, RANGE_WARNING, RANGE_MESSAGE
																						if (iTokenID == DMRuleReserved_CommonMin ||
																							 iTokenID == DMRuleReserved_CommonMax)
																							iSeverity = RANGE_WARNING;
																						int iCondition = BEMC_GrtrOrEqual;	// BEMC_Equal, BEMC_LessOrEqual, BEMC_GrtrOrEqual, BEMC_Less, BEMC_Greater, BEMC_NotEqual, BEMC_NumConditions,
																						if (iTokenID == DMRuleReserved_CommonMax ||
																							 iTokenID == DMRuleReserved_Maximum  )
																							iCondition = BEMC_LessOrEqual;
            	                 	
																						BEMRangeCheck* pRng = new BEMRangeCheck( lDatabaseID[iNumIndirections-1], iCondition, iSeverity, token2.toLocal8Bit().constData() );		assert( pRng );
																						if (pRng)
																						{	// add this new BEMRangeCheck to list
																							ruleSet.addRangeCheck( pRng );
																							if (pNewRuleProp)
																							{	assert( (pNewRuleProp->getPropType() < 0 || pNewRuleProp->getPropType() == BEMP_Flt || pNewRuleProp->getPropType() == BEMP_Int) );
																								if (pNewRuleProp->getPropType() != BEMP_Flt && pNewRuleProp->getPropType() != BEMP_Int)  // SAC 5/9/13 - mod to allow range checks on Int properties
																									pNewRuleProp->setPropType( BEMP_Flt );
																							}
																						}
																					}
																				}	break;
											default :  // token should be a TRANSFORMATION name and all text thru following transformation name or end rule represents the rule expression
																				{	RuleList* pRL = NULL;		RuleSetTransformation* pTr = NULL;		int iTr;
																					int iTransRLIdx = iTokenID - DMRuleReserved_Default;
																					int iNumTransforms = ruleSet.getNumTransformations();
																					int iNumRulelists  = (int) paTransformRulelists.size();
																					std::vector<int> iaTransRLIdx;
																					std::vector<int> iaTransRLIdxSKIPPED;  // SAC 1/13/19
																					if (iTransRLIdx >= 0 && iTransRLIdx < iNumRulelists)
																					{	if (IntegerInArray( iaTransformRulesProcessed, iTransRLIdx ) < 0)
																						{	iaTransRLIdx.push_back( iTransRLIdx );
																							iaTransformRulesProcessed.push_back( iTransRLIdx );
																						}
																						else
																							iaTransRLIdxSKIPPED.push_back( iTransRLIdx );
																					}
																					else if (iTransRLIdx >= iNumRulelists)
																					{	// should be a transform GROUP name
																						for (iTr=0; iTr < iNumTransforms; iTr++)
																						{	pTr = (RuleSetTransformation*) ruleSet.getTransformation( iTr );		assert( pTr );
																							//if (pTr && !pTr->m_sGroupLongName.compare( token, Qt::CaseInsensitive ))
																							if (pTr && pTr->LongGroupNameMatch( token ))		// SAC 8/20/15 - switched group names from single strings to arrays
																							{	int iTR2Add = (iTr+(DMRuleReserved_MAX_NUM-DMRuleReserved_Default)+1);
																								if (IntegerInArray( iaTransformRulesProcessed, iTR2Add ) < 0)
																								{	iaTransRLIdx.push_back( iTR2Add );
																									iaTransformRulesProcessed.push_back( iTR2Add );
																								}
																								else
																									iaTransRLIdxSKIPPED.push_back( iTR2Add );
																					}	}	}
                              	
																					if (iaTransRLIdx.size() < 1)
																					{	if (iaTransRLIdxSKIPPED.size() > 0)
																						{	// skipping this rule expression due to it having been processed already, which is probably OK
// #ifdef _DEBUG   - report only when in debug mode once we are confident that this needn't cause errant return or be presented to user
																							int iFileErrLine = file.GetLineCount();
																							QString sDbgIssue = QString( "      Skipping inclusion of rule expression for '%1' found on line: %2 of '%3'\n" ).arg( token, QString::number(iFileErrLine), file.FileName() );
																							errorFile.write( sDbgIssue.toLocal8Bit().constData(), sDbgIssue.length() );
																							sDbgIssue = "            corresponding rulelist(s) already processed:  ";
																							int iDbg;
																							for (iDbg=0; iDbg<(int)iaTransRLIdxSKIPPED.size(); iDbg++)
																							//{	RuleSetTransformation* pRptTr = (RuleSetTransformation*) ruleSet.getTransformation( iaTransRLIdxSKIPPED[iDbg] );		assert( pRptTr );  - not a TRANSFORM index - an index into the RuleLists
																							{	RuleList* pRptRL = paTransformRulelists[ iaTransRLIdxSKIPPED[iDbg] ];		assert( pRptRL );
																								if (pRptRL)
																									sDbgIssue += QString( "%1 (%2)  /  " ).arg( pRptRL->getName(), QString::number( iaTransRLIdxSKIPPED[iDbg] ) );
																								else
																									sDbgIssue += QString( "(%1)  /  " ).arg( QString::number( iaTransRLIdxSKIPPED[iDbg] ) );
																							}
																							sDbgIssue += QString( "\n" );
																							errorFile.write( sDbgIssue.toLocal8Bit().constData(), sDbgIssue.length() );
// #endif
																							token2 = file.ReadToNextToken( saReservedStrs );  // skip over this rule expression
																						}
																						else
																						{	// INVALID iTokenID => no idea which TRANSFORM's rulelist to add this rule to
																							assert( FALSE );
																							//QString sErr;
																							sErr = QString( "\n\tRule syntax error on/near '%1' line: %2\n" ).arg( token, QString::number(file.GetLineCount()) );
																							errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
																							bRetVal = FALSE;
																					}	}
																					else
																					{	int iRuleLineNum = file.GetLineCount();
																						token2 = file.ReadToNextToken( saReservedStrs );
																						RemoveComments( token2 );
																						if (StringHadAlphaOrNumeric( token2 ))
																						{	for (iTr=0; iTr < (int) iaTransRLIdx.size(); iTr++)
																							{	pRL = paTransformRulelists[ iaTransRLIdx[iTr] ];		assert( pRL );
																								if (pRL)
																								{	QString sRuleID = QString( "Set %1 %2  (%3:'%4' line %5)" ).arg( saReservedStrs[ (iaTransRLIdx[iTr]+DMRuleReserved_Default) ],
																																		sFullDBIDStr, QString::number(i1RuleFileIdx), sRuleFileNoPath, QString::number(iRuleLineNum) );
																	//								Rule* pRule = new Rule( sRuleID.toLocal8Bit().constData(), sFullDBIDStr.toLocal8Bit().constData(), token2.toLocal8Bit().constData(),
																									Rule* pRule = new Rule( sRuleID, sFullDBIDStr, token2,
																																	iNumIndirections, lDatabaseID, i1RuleFileIdx, iRuleLineNum, iNumAncestors, iaAncestorObjTypes );	assert( pRule );
																									if (pRule)
																										pRL->addRule( pRule );
																								}
																					}	}	}
																				}	break;
										}	// end switch
									}	// end of if (bProcessToken)
									token = file.ReadToken();
									iTokenID = IndexInStringArray( saReservedStrs, token );
								}

				// SAC 5/11/14 - added code to process help & descrip strings into tooltip & add tooltip to ruleset
								if ((iTokenID == DMRuleReserved_EndRule || iTokenID == DMRuleReserved_EndRule2) && (!sRuleHelp.isEmpty() || !sRuleDescrip.isEmpty()))
								{	// remove NewLine chars and mulitple leading spaces for each subsequent line of text ???
									QString sTTText;
									if (!sRuleDescrip.isEmpty())
									{	FormatMultilineString( sRuleDescrip );
										sRuleDescrip = sRuleDescrip.trimmed();
										if (sRuleDescrip.length() > 4)
											sTTText = sRuleDescrip;
									}
									if (!sRuleHelp.isEmpty())
									{	FormatMultilineString( sRuleHelp );
										sRuleHelp = sRuleHelp.trimmed();
										if (sRuleHelp.length() > 4)
										{	if (!sTTText.isEmpty())
												sTTText += "\n\nHELP:  ";
											sTTText += sRuleHelp;
									}	}
									if (!sTTText.isEmpty())
										sTTText += "\n";

									RuleToolTip* pNewRuleTT = NULL;
									pNewRuleTT = new RuleToolTip( sTTText, iNumIndirections, lDatabaseID, iNumAncestors, iaAncestorObjTypes );		assert( pNewRuleTT );
									if (!pNewRuleTT)
										bContinue = FALSE;
									else
										ruleSet.addToolTip( pNewRuleTT );
								}
							}

							if (pNewRuleProp)
							{
								BEMClass* pRuleNewClass = BEMPX_GetClass( (int) pNewRuleProp->getObjTypeID(), iError );				     assert( pRuleNewClass );
								if (pRuleNewClass)
								{	QString sRuleNewMsg, sRuleNewType;
									if (pNewRuleProp->getPropType() == BEMP_Obj)
									{	BEMClass* pRuleNewObjClass = BEMPX_GetClass( (int) pNewRuleProp->getPropTypeObjID(), iError );		assert( pRuleNewObjClass );
										if (pRuleNewObjClass)
											sRuleNewType = QString( "ObjectRef (%1)" ).arg( pRuleNewObjClass->getShortName() );
										else
											sRuleNewType = "ObjectRef (unknown)";
									}
									else
									{	switch (pNewRuleProp->getPropType())
										{	case  BEMP_Str :	sRuleNewType = "String";       break;
											case  BEMP_Int :	sRuleNewType = "Integer";      break;
											case  BEMP_Flt :	sRuleNewType = "Float";        break;
											case  BEMP_Sym :	sRuleNewType = "Enumeration";  break;
											default			:	sRuleNewType = "unknown!";     break;
										}  
									}
									sRuleNewMsg = QString( "         Rule NEW:  %1:%2 / %3  Type: %4  iPropID:%5  lDBID:%6 \n" ).arg( pRuleNewClass->getShortName(), pNewRuleProp->getPropName(),
																			pNewRuleProp->getPropNameLong(), sRuleNewType, QString::number(pNewRuleProp->getPropID()), QString::number(pNewRuleProp->getDBID()) );
					      		errorFile.write( sRuleNewMsg.toLocal8Bit().constData(), sRuleNewMsg.length() );
								}
							}
						}	// end of: if reading rules this time through
					}
					else if (token == "TABLE")
					{	if (iRuleFileReadIteration != 0)
						{	// skip over each TABLE during this round of rules file reading
							QStringList saEndTable;
							saEndTable.push_back( "ENDTABLE" );
							token2 = file.ReadToNextToken( saEndTable );  // saReservedStrs );
							token2 = file.ReadToken();  // read past ENDTABLE token
						}
						else
						{	// Read table name, followed by call to read table itself
							token2 = file.ReadToken();
							if (!ruleSet.addTable( token2.toLocal8Bit().constData() /*TableName*/, pszRulePathFile, file, errorFile ))
								bRetVal = FALSE;
							else
							{	token = file.ReadToken();				assert( !token.compare("ENDTABLE", Qt::CaseInsensitive) || !token.compare("ENDTABL", Qt::CaseInsensitive) );
							}
						}
					}
					else if (token == "E")
					{	// do nothing - happens if/when EOF immediately after an ENDRULE token...
					}
					else
					{	assert( FALSE );
						QString sErr = QString( "\n\tRule syntax error on/near '%1' line: %2\n" ).arg( token, QString::number(file.GetLineCount()) );
						errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
						bRetVal = FALSE;
					}
            	
					token = file.ReadToken();  // read token beginning next RULE (or perhaps end of file...)
				}
         }
//			catch (std::exception& e)
//			{
//            if ( err->m_cause == BEMTextioException::endOfFile )
//            {	// delete the last allocation of new data which was never populated
//            	//delete [] newData; // we're done, no problem
//            }
//            else
//               THROW_LAST();
		//		QString sErrMsg = QString( "Error writing ruleset compilation log file: %1\n\t - cause: %2\n" ).arg( sLogFileName, e.what() );
		//		std::cout << sErrMsg.toLocal8Bit().constData();
		//		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
//			}
		 	catch (...)
		  	{
		//		QString sErrMsg = QString( "Error writing ruleset compilation log file: %1\n" ).arg( sLogFileName );
		//		std::cout << sErrMsg.toLocal8Bit().constData();
		//		BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
		  	}
      }
		catch (std::exception& e)
		{
			if (bInBetweenReadingRules)  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
			{	//if (newData)  // delete the last allocation of new data which was never populated
            //   delete [] newData; // we're done, no problem
			}
			else
			{	QString sErrMsg = QString( "Error parsing rule file: %1\n\t - cause: %2\n\n" ).arg( pszRulePathFile, e.what() );
				errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
	//			std::cout << sErrMsg.toLocal8Bit().constData();
				bRetVal = FALSE;
				BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
			}
		}
	 	catch (...)
	  	{
			if (bInBetweenReadingRules)  // SAC 6/25/12 - added to prevent exception thrown looking for next float following some number of successful record reads from causing read failure
			{	//if (newData)  // delete the last allocation of new data which was never populated
            //   delete [] newData; // we're done, no problem
			}
			else
			{	QString sErrMsg = QString( "Error parsing rule file: %1\n\n" ).arg( pszRulePathFile );
				errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
	//			std::cout << sErrMsg.toLocal8Bit().constData();
				bRetVal = FALSE;
				BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
			}
	  	}

		readMsg = "         done.\n\n";
		errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
   }
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening rule file: %1\n\t - cause: %2\n\n" ).arg( pszRulePathFile, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening rule file: %1\n\n" ).arg( pszRulePathFile );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
  	}

   return bRetVal;
}


static bool ReadLibraryObject( const char* fileName, BEMTextIO &file, QString sObjType, BEM_ObjType eFileType, QFile* pErrorFile );  // SAC 2/4/18

bool RuleFile::ReadRuleFile( const char* pszRulePathFileName, int i1RuleFileIdx, int& ruleListIndex, QFile& errorFile, int iFileStructVer )
{
	bool bRetVal = true;
	QString sRulePathFileName = pszRulePathFileName;
	int iNumLibObjectsRead = 0;

   try
   {  // open file
      BEMTextIO file( sRulePathFileName.toLocal8Bit().constData(), BEMTextIO::load );

      // write message to error file indicating that we are reading this table file
      QString readMsg = QString( "Reading rule file #%1:  %2\n\n" ).arg( QString::number(i1RuleFileIdx), sRulePathFileName );
      errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );

		QString token = file.ReadToken();
      int iHardwireEnumStrVal = -1;       // -1 (ruleset default) / 0 Value / 1 String - SAC 09/24/21 (MFam)
		while (!token.isEmpty() && token != "ENDFILE" && !file.AtEOF())		// SAC 1/23/20 - added check for EOF
		{	if (token == "ENUM_PROPERTIES_VALUE")
            iHardwireEnumStrVal = 0;
         else if (token == "ENUM_PROPERTIES_STRING")
            iHardwireEnumStrVal = 1;
         else if (token == "RULELIST")
     	      bRetVal = ((ReadRuleList( ruleListIndex++, errorFile, iFileStructVer /*ruleSet.m_iFileStructVersion*/, 
     	      									i1RuleFileIdx, &file, pszRulePathFileName, iHardwireEnumStrVal )) && (bRetVal));
			else
			{	int i1Class = BEMPX_GetDBComponentID( token.toLocal8Bit().constData() );	// SAC 2/4/18 - enable specification of library objects within rulelist files
            if (i1Class > 0)
            {	// assumption is that this is a LIBRARY object
					if (ReadLibraryObject( pszRulePathFileName, file, token, BEMO_RuleLib, &errorFile ))	// SAC 2/4/18
						iNumLibObjectsRead++;
					else
						bRetVal = false;
				}
				else
				{	assert( FALSE );
					QString sErr = QString( "\n\tRule syntax error on/near '%1' line: %2\n" ).arg( token, QString::number(file.GetLineCount()) );
					errorFile.write( sErr.toLocal8Bit().constData(), sErr.length() );
					bRetVal = false;
			}	}
			token = file.ReadToken();  // read token beginning next RULE (or perhaps end of file...)
		}

		readMsg = "         done.\n\n";
		errorFile.write( readMsg.toLocal8Bit().constData(), readMsg.length() );
   }
	catch (BEMTextioException& te)
	{
		if ( te.m_cause == BEMTextioException::endOfFile )
		{	assert( FALSE ); // we're done, no problem (??)
		}
		else
		{	QString sErrMsg = QString( "Error reading rule file: %1\n\t%2" ).arg( sRulePathFileName, te.m_strError.toLocal8Bit().constData() );
		//{	QString sErrMsg = QString( "Error reading rule file because '%1'" ).arg( te.what() );
		//	if (BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
		//		BEMMessageBox( sErrMsg, NULL, 3 /*error*/ );
		//	throw std::runtime_error(boost::str(boost::format("Error reading analysis results from file because '%1") %
		//															te.m_strError.toLocal8Bit().constData() ));
			errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
			bRetVal = FALSE;
	      BEMMessageBox( sErrMsg, "", 3 /*error*/ );
		}
	}
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error opening file: %1\n\t - cause: %2" ).arg( sRulePathFileName, e.what() );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
      BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error opening file: %1" ).arg( sRulePathFileName );
		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
      BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}

	if (bRetVal && iNumLibObjectsRead > 0)	// SAC 2/4/18
	{	int iNumObjsNotFound = BEMP_ResolveAllReferences( BEMO_RuleLib, &errorFile );
		bRetVal = (iNumObjsNotFound == 0);
	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

QString LibFile_ReadNextPropType( BEMTextIO& file )
{  // advance past any spaces to the next character
   file.Advance();
   // if '..' found, then return it, else simply call ReadToken() to read next property type string from file
   if ( file.GetChr() == '.' )
   {  if ( file.GetChr() == '.' )
         return QString( ".." );
      file.UnGetChr();
   }
   file.UnGetChr();
   // '..' not found, so read (and return) next property type string
   return file.ReadToken();
}

/////////////////////////////////////////////////////////////////////////////

void LogLibDataSetError( BEMPropertyType* pPropType, int iSetRetVal, void* pData, QFile* pErrorFile )
{
	QString sErrMsg;
	if (pPropType)
	{	int iError;
		BEMClass* pClass = BEMPX_GetClass( pPropType->get1ClassIdx(), iError );  //, int iBEMProcIdx=-1 );
		QString sClassName = (pClass == NULL ? "<unknown>" : pClass->getShortName());
		if (pData == NULL)
		{	switch ( pPropType->getPropType() )
			{	case BEMP_Int :	sErrMsg = QString( "\nError setting %1:%2 integer library data to database (%3) - invalid data pointer."				).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
				case BEMP_Flt :   sErrMsg = QString( "\nError setting %1:%2 float library data to database (%3) - invalid data pointer."				).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
				case BEMP_Sym :   sErrMsg = QString( "\nError setting %1:%2 enumeration library data to database (%3) - invalid data pointer."		).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
				case BEMP_Str :   sErrMsg = QString( "\nError setting %1:%2 string library data to database (%3) - invalid data pointer."				).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
				case BEMP_Obj :   sErrMsg = QString( "\nError setting %1:%2 object reference library data to database (%3) - invalid data pointer."	).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
				default		  :   sErrMsg = QString( "\nError setting %1:%2 <unknown> library data to database (%3) - invalid data pointer."			).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
			}
		}
		else
		{	switch ( pPropType->getPropType() )
			{	case BEMP_Int : 	{	long lTemp = *((long*) pData);
											sErrMsg = QString( "\nError setting %1:%2 integer library data to database (%3) - value: %4."		).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal), QString::number(lTemp) );
										}	break;
				case BEMP_Flt :   {	double fTemp = *((double*) pData);
											sErrMsg = QString( "\nError setting %1:%2 float library data to database (%3) - value: %4."			).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal), QString::number(fTemp) );
										}	break;
				case BEMP_Sym :   {	QString sTemp = ((const char*) pData);
											sErrMsg = QString( "\nError setting %1:%2 enumeration library data to database (%3) - string '%4'.").arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal), sTemp );
										}	break;
				case BEMP_Str :   {	QString sTemp = ((const char*) pData);
											sErrMsg = QString( "\nError setting %1:%2 string library data to database (%3) - string '%4'."		).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal), sTemp );
										}	break;
				case BEMP_Obj :   {	QString sTemp = ((const char*) pData);
											sErrMsg = QString( "\nError setting %1:%2 object reference library data to database - name '%3'."	).arg( sClassName, pPropType->getShortName(), sTemp );
										}	break;
				default		  :		sErrMsg = QString( "\nError setting %1:%2 <unknown> library data to database (%3)."	).arg( sClassName, pPropType->getShortName(), QString::number(iSetRetVal) );	break;
	}	}	}

	if (pErrorFile)
	{  // write message to error file
		sErrMsg += "\n";
		pErrorFile->write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
	}
}

/////////////////////////////////////////////////////////////////////////////

// end-of-file marker
static char szEnd[] = "END_OF_INPUT";

// SAC 2/4/18 - split out individual library object read/parse into separate routine to enable reading of library obejcts from rulelist files
bool ReadLibraryObject( const char* fileName, BEMTextIO &file, QString sObjType, BEM_ObjType eFileType, QFile* pErrorFile )
{	bool bRetVal = TRUE;
      BEM_PropertyStatus eDataStatus = ((eFileType == BEMO_RuleLib) ? BEMS_RuleLibrary : BEMS_UserLibrary);

      try
      {
            // read component name, get object class and create new instance of that object type
            QString sObjName = file.ReadString();
            int i1Class = BEMPX_GetDBComponentID( sObjType.toLocal8Bit().constData() );
            BEMObject* newObject = BEMPX_CreateObject( i1Class, sObjName.toLocal8Bit().constData(), NULL, eFileType );

            if (newObject != NULL)
            {
               QString sPropType = LibFile_ReadNextPropType( file );
               // read all property types describing this component until '..' encountered
               while ( sPropType != ".." )
               {
                  // look up type
                  int i1PropTypeIdx = BEMPX_GetPropertyTypeIndexByShortName( i1Class, sPropType.toLocal8Bit().constData() );
                  BEMPropertyType* pPropType = BEMPX_GetPropertyType( i1Class, i1PropTypeIdx );
                  if ( pPropType == NULL )
                     file.ThrowTextIOException( BEMTextioException::badPropType ); // throw exception
                  // advance past any spaces to the next character
                  file.Advance();
                  if ( file.GetChr() != '=' )
                     file.ThrowTextIOException( BEMTextioException::xEquals ); // throw exception
                  int nValues = pPropType->getNumValues();
                  // advance past any spaces to the next character
                  file.Advance();
                  if ( nValues > 1 && file.GetChr() != '(' ) // read not called if nVals <1
                     file.ThrowTextIOException( BEMTextioException::xOpenParen ); // throw exception
                  BOOL bDone = FALSE;
                  for ( int i = 0; (!bDone) && (i < nValues); i++ )
                  {
                     // convert class, property type and array index into database ID used to post data to the database
                     long lDBID = BEMPX_GetDBID( i1Class, i1PropTypeIdx, (i + 1) );  // SAC 7/18/01
                     switch ( pPropType->getPropType() )
                     {
                        case BEMP_Int : { long lTemp = file.ReadLong();
                                          int iSet = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lTemp, eFileType, -1, eDataStatus, eFileType );
														if (iSet < 0 && pErrorFile)
															LogLibDataSetError( pPropType, iSet, (void*) &lTemp, pErrorFile );
                                          break;  }
                        case BEMP_Flt : { double fTemp = file.ReadDouble();
                                          int iSet = BEMPX_SetBEMData( lDBID, BEMP_Flt, (void*) &fTemp, eFileType, -1, eDataStatus, eFileType );
														if (iSet < 0 && pErrorFile)
															LogLibDataSetError( pPropType, iSet, (void*) &fTemp, pErrorFile );
                                          break;  }
                        case BEMP_Sym :
                        case BEMP_Str : { QString sTemp = file.ReadString();
                                          int iSet = BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &sTemp,  // BEMP_Str, (void*) sTemp.toLocal8Bit().constData(), 
                                          										eFileType, -1, eDataStatus, eFileType );
														if (iSet < 0 && pErrorFile)
															LogLibDataSetError( pPropType, iSet, (void*) sTemp.toLocal8Bit().constData(), pErrorFile );
                                          break;  }
                        case BEMP_Obj : { QString sTemp = file.ReadString();
                                          // Can't just call SetBEMData() because if the referenced element has not already
                                          // been created, then the obj ptr would get set to NULL and string would be lost.
                                          // Just set string for now, then resolve references once all components are read.
                                          int iError;
                                          BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, -1, eFileType );		assert( pProp != NULL );
														if (pProp)
                                          {	pProp->setString( sTemp );
                                          	pProp->setDataStatus( eDataStatus );
														}
														else
															LogLibDataSetError( pPropType, -1, (void*) sTemp.toLocal8Bit().constData(), pErrorFile );
                                          break;  }
                        default : 
                           file.ThrowTextIOException( BEMTextioException::badPropTypeType ); // throw exception
                           break;
                     }

                     if ( nValues > 1 ) 
                     {   
                        // advance past any spaces to the next character
                        file.Advance();
                        char cNext = file.GetChr();
                        if (cNext == ')')
                           bDone = TRUE;
                        else if (cNext != ',')
                           file.ThrowTextIOException( BEMTextioException::xComma ); // throw exception
                     }
                  }
                  sPropType = LibFile_ReadNextPropType( file );
               }
            }
      }
		catch (std::exception& e)
		{
			QString msg = QString( "Error reading ruleset library data from File: %1\n\t - cause: %2\n" ).arg( fileName, e.what() );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
		}
	 	catch (...)
	  	{
			QString msg = QString( "Error reading ruleset library data from File: %1\n" ).arg( fileName );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
	  	}
	return bRetVal;
}


bool ReadLibraryText( const char* fileName, BEM_ObjType eFileType, QFile* pErrorFile )
{
   bool bRetVal = TRUE;

   // create and open library file
//   CLibFile* file = new CLibFile( fileName, eFileType );
   try
   {  // open file
      BEMTextIO file( fileName, BEMTextIO::load );
      try
      {


      // read library file into the building database
      bool bHitEnd = FALSE;
      // continue reading component definitions until the end-of-file marker is encountered
      while ( !bHitEnd )
      {
         // read component type (or end-of-file marker)
         QString sObjType = file.ReadToken();
         if (sObjType.compare( szEnd ) == 0)
            bHitEnd = TRUE;  // end-of-file marker is encountered
         else
         {

				bRetVal = ReadLibraryObject( fileName, file, sObjType, eFileType, pErrorFile );	// SAC 2/4/18

         }
      }
      // resolve all object references - this is necessary because all object assignments are
      // originally read and stored simply as character string names of the referenced objects.
      // This function resolves those object names to actual object pointers.
      // This object resolving cannot happen during the reading process, since an object
      // can be assigned PRIOR to its definition in the file.
      assert( bRetVal );   // should always be true following read of each object
      int iNumObjsNotFound = BEMP_ResolveAllReferences( eFileType, pErrorFile );
      bRetVal = (iNumObjsNotFound != 0 ? FALSE : bRetVal);


      }
		catch (std::exception& e)
		{
			QString msg = QString( "Error reading ruleset library data from File: %1\n\t - cause: %2\n" ).arg( fileName, e.what() );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
		}
	 	catch (...)
	  	{
			QString msg = QString( "Error reading ruleset library data from File: %1\n" ).arg( fileName );
			std::cout << msg.toLocal8Bit().constData();
         BEMMessageBox( msg, "", 2 /*warning*/ );
         bRetVal = FALSE;
	  	}
   }
	catch (std::exception& e)
	{
		std::cout << "Error opening file: " << fileName << "  - cause: " << e.what() << '\n';
      bRetVal = FALSE;
	}
 	catch (...)
  	{
	   std::cout << "Error opening file: " << fileName << '\n';
      bRetVal = FALSE;
	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads the contents of the main ASCII ruleset file into memory.
//   
// Arguments ----------------------------------------------------------------
//   QFile& errorFile  : file where error messages are written
//   
// Return Value -------------------------------------------------------------
//   TRUE if ruleset imported successfully, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
// SAC 9/3/16 - added to enable postponment of library file reading until all RULE NEWs are processed (and PropertyType array is fixed)
bool ParseLibraryFiles( QStringList& saLibFiles, QFile& errorFile )
{	bool bRetVal = true;
	for (int i=0; i < (int) saLibFiles.size(); i++)
	{	if (!ReadLibraryText( saLibFiles[i].toLocal8Bit().constData(), BEMO_RuleLib, &errorFile ))
			bRetVal = false;
	}
	return bRetVal;
}

bool RuleFile::Read( QFile& errorFile )
{
   bool bRetVal = TRUE;
   try
   {
      // first piece of data should be RULESETID
      QString sErrMsg, token2, token = m_file.ReadToken();

      // SAC 6/12/00 - added new RULESET_STRUCT_VERSION capability to maintain backward compatibility
      long lFileStructVer = 1;
      if ( token == "RULESET_STRUCT_VERSION" || token == "FORMATVERSION" )
      {
         lFileStructVer = m_file.ReadLong();
         // read NEXT token
         token = m_file.ReadToken();
      }
      ruleSet.setFileStructVersion( lFileStructVer );
						// starting w/ FileStructVer = 6, topmost ruleset file header expected to be something like:
						//		FORMATVERSION   6
						//		RULESET
						//		   NAME "CA 2013 Nonresidential"
						//		   FULLNAME "CA 2013 Nonresidential, Vers. 1.0"
						//		   FORMAT  DataModel
						//		ENDRULESET 
		ruleSet.setRulesetOrganization( RULESETORG_PROCEDURAL );  // SAC 6/21/12 - added to differentiate "procedural" vs. "data model" rulesets (default = procedural)
		ruleSet.setDataModelRuleActive( false );  // SAC 5/26/16
		if (ruleSet.getFileStructVersion() >= 6 && token == "RULESET")
		{	// read 'RULESET' block (in no particular order)
			bool bReadingLabels = false;
			token = m_file.ReadToken();
			while (token != "ENDRULESET")
			{	if (token == "NAME")
		      {	token2 = m_file.ReadString();
		      	ruleSet.setRuleSetID( token2 );
					bReadingLabels = false;
				}
				else if (token == "FULLNAME")
		      {	token2 = m_file.ReadString();
		      	ruleSet.setRuleSetVersion( token2 );
					bReadingLabels = false;
				}
				else if (token == "FORMAT")
				{  token = m_file.ReadToken();
					if (!token.compare( "DataModel", Qt::CaseInsensitive))
						ruleSet.setRulesetOrganization( RULESETORG_DATAMODEL );
					ruleSet.setDataModelRuleActive( (ruleSet.IsDataModel() != FALSE) );  // SAC 5/26/16
					bReadingLabels = false;
				}
				else if (token == "BEMBASEFILE")
				{	token2 = m_file.ReadString();
		      	ruleSet.setBEMBaseFile( token2 );		// SAC 8/15/14 - added
					bReadingLabels = false;
				}
				else if (token == "SCREENSFILE")
				{	token2 = m_file.ReadString();
		      	ruleSet.setScreensFile( token2 );
					bReadingLabels = false;
				}
				else if (token == "TOOLTIPSFILE")
				{	token2 = m_file.ReadString();
		      	ruleSet.setToolTipsFile( token2 );
					bReadingLabels = false;
				}
				else if (token == "LABELS")
				{  token = m_file.ReadToken();								assert( !token.isEmpty() );
					if (!token.isEmpty())
					{	ruleSet.addLabel( token );
						bReadingLabels = true;
				}	}
				else if (bReadingLabels && !token.isEmpty())
					ruleSet.addLabel( token );
	         // read NEXT token
   	      token = m_file.ReadToken();
			}
		}
		else if (ruleSet.getFileStructVersion() >= 6)
		{	assert( FALSE );  // file struct ver calls for header to be organized like sample above
         ;// exception
		}
		else
		{  // read header info for format version <= 5
      	if ( token == "RULESETID" )
			{	token2 = m_file.ReadString();
      	   ruleSet.setRuleSetID( token2 );
      	}
      	else
      	   ;// exception

      	// next piece of data should be RULESETVERSION
      	token = m_file.ReadToken();
      	if ( token == "RULESETVERSION" )
			{	token2 = m_file.ReadString();
      	   ruleSet.setRuleSetVersion( token2 );
      	}
      	else
      	   ;// exception
		}

      token = m_file.ReadToken();
		if (ruleSet.IsDataModel())
		{	// handle parsing of remainder of "master" data model ruleset file
	      QString token2, token3, sTransRLName;
	      QStringList saLibFiles;		// SAC 9/3/16 - added this and following bools to ensure that all RULE NEWs are processed and added to BEMBase PRIOR to processing library entries, since ptrs to PropTypes change as rule news are added
	      int iNumRuleFiles=0;
			while (!token.isEmpty())
			{	if (token == "TRANSFORMATIONS")
				{	token = m_file.ReadToken();
					RuleSetTransformation* pActiveTrans = NULL;
					while (token != "ENDTRANSFORMATIONS")
					{	if (!token.compare("Simulate", Qt::CaseInsensitive))		// SAC 3/18/14 - new option to identify global property that determines when a model (transform) is to be simulated
						{	m_file.ReadBEMProcParam( token2 );
							long lSimDBID = BEMPX_GetDatabaseID( token2 );
							if (lSimDBID > BEM_COMP_MULT)
								ruleSet.setSimulateDBID( lSimDBID );
							else
							{	sErrMsg = QString( "   Error: Unable to determine DBID of 'Simulate' property '%1'.\n\n" ).arg( token2 );
								errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
								bRetVal = FALSE;
						}	}
						else if (pActiveTrans && (!token.compare("EXCLUDE", Qt::CaseInsensitive) ||
														  !token.compare("from"   , Qt::CaseInsensitive) ))
						{	m_file.ReadBEMProcParam( token2 );
							if (!token.compare("from", Qt::CaseInsensitive))
							{	int iSrcTransformIdx = -1;
								for (int iTIdx=0; (iSrcTransformIdx < 0 && iTIdx < ruleSet.getNumTransformations()); iTIdx++)
								{	RuleSetTransformation* pChkTrans = ruleSet.getTransformation(iTIdx);
									if (pChkTrans && (pChkTrans->getLongName().compare(token2, Qt::CaseInsensitive)==0 || pChkTrans->getShortName().compare(token2, Qt::CaseInsensitive)==0))
										iSrcTransformIdx = iTIdx;
								}
								if (iSrcTransformIdx >= 0)
									pActiveTrans->setBEMProcIdxToCopy( iSrcTransformIdx );
								else if (token2.compare("none", Qt::CaseInsensitive))
								{	sErrMsg = QString( "   Error: Unable to find previous TRANSFORMATION %1 to serve as the starting point for %2/%3.\n\n" ).arg( token2, pActiveTrans->getLongName(), pActiveTrans->getShortName() );
									errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
									bRetVal = FALSE;
							}	}
							else
							{	long lDBIDToBypassCopy = (token2.indexOf(':') > 0 ? BEMPX_GetDatabaseID( token2 ) : BEMPX_GetDBComponentID( token2.toLocal8Bit().constData() ));	// SAC 3/20/14 - could be EITHER class alone or full DBID
								if (lDBIDToBypassCopy > 0)
									pActiveTrans->addClassOrDBIDToExclude( lDBIDToBypassCopy );
								else
								{	sErrMsg = QString( "   Error: Unable to parse TRANSFORMATION %1/%2 - object type (or DBID) '%3' to exclude during initialization.\n\n" ).arg( pActiveTrans->getLongName(), pActiveTrans->getShortName(), token2 );
									errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
									bRetVal = FALSE;
							}	}
						}
						else if (pActiveTrans && !token.compare( "Or", Qt::CaseInsensitive ))		// SAC 3/27/14 -  added long & short Group names (to allow rule expressions to be specified once but inserted into multiple transforms)
						{	token  = m_file.ReadToken();		assert( !token.isEmpty()  && token.compare( "from", Qt::CaseInsensitive) && token.compare( "EXCLUDE", Qt::CaseInsensitive) );
							token2 = m_file.ReadToken();		assert( !token2.isEmpty() && token2.compare("from", Qt::CaseInsensitive) && token2.compare("EXCLUDE", Qt::CaseInsensitive) && token.length() > token2.length() );		assert( sErrMsg.isEmpty() );
															//			assert( pActiveTrans->m_sGroupLongName.isEmpty() && pActiveTrans->m_sGroupShortName.isEmpty() );		-- now allowing ARRAY of group names
							if (	token.isEmpty()  || !token.compare( "from", Qt::CaseInsensitive) || !token.compare( "EXCLUDE", Qt::CaseInsensitive) ||
									token2.isEmpty() || !token2.compare("from", Qt::CaseInsensitive) || !token2.compare("EXCLUDE", Qt::CaseInsensitive) )
								sErrMsg = QString( "   Error: Expected Group long/short name following 'Or' of transform %1 definition, but instead found '%2'/'%3'.\n\n" ).arg( pActiveTrans->getLongName(), token, token2 );
							else if (token.length() <= token2.length())
								sErrMsg = QString( "   Error: Transform Group long name '%1' <= length of short name '%2' (for transform %3).\n\n" ).arg( token, token2, pActiveTrans->getLongName() );
							else if (token2.length() > TransShortName_MaxLen)
								sErrMsg = QString( "   Error: Transform Group short name '%1' is too long - max length = %2 characters (for transform %3).\n\n" ).arg( token2, QString::number(TransShortName_MaxLen), pActiveTrans->getLongName() );

							if (!sErrMsg.isEmpty())
							{	errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
								bRetVal = FALSE;
							}
							else
							{	pActiveTrans->addGroupLongName(  token  );
								pActiveTrans->addGroupShortName( token2 );
						}	}
						else  // this is a new TRANSFORMATION being defined
						{	token2 = m_file.ReadToken();
							if (token2.length() > TransShortName_MaxLen)
								sErrMsg = QString( "   Error: Transform short name '%1' is too long - max length = %2 characters (for transform %3).\n\n" ).arg( token2, QString::number(TransShortName_MaxLen), token );
							else
							{	int iSrcTransformIdx = ruleSet.getNumTransformations() - 1;
								sTransRLName = QString( "rl_%1" ).arg( token );
								pActiveTrans = new RuleSetTransformation( token, token2, sTransRLName, iSrcTransformIdx );				assert( pActiveTrans );
								if (pActiveTrans)
									ruleSet.addTransformation( pActiveTrans );
								else
									sErrMsg = QString( "   Error: Unable to add TRANSFORMATION %1/%2 to the ruleset.\n\n" ).arg( token, token2 );
							}
							if (!sErrMsg.isEmpty())
							{	errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
								bRetVal = FALSE;
							}
						}
						token = m_file.ReadToken();
					}
				}
				else if (token == "LIBRARYFILES")
				{	token = m_file.ReadCSVString();
					while (token != "ENDLIBRARYFILES")
					{	// parse LIBRARY file
						QString sLibFilePath = token;
						EnsureValidPath_AltPaths( m_fileName, sLibFilePath );
                  if (!FileExists( sLibFilePath.toLocal8Bit().constData() ))
						{	sErrMsg = QString( "   Error: Library file not found: %1\n\n" ).arg( sLibFilePath );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
							saLibFiles.push_back( sLibFilePath );	// archive lib filename for parsing AFTER RULE NEWs have been added to BEMBase
						token = m_file.ReadCSVString();
					}
				}
				else if (token == "TABLEFILES")
				{	token = m_file.ReadCSVString();
					while (token != "ENDTABLEFILES")
					{	// parse LIBRARY file
						QString sTblFilePath = token;
						EnsureValidPath_AltPaths( m_fileName, sTblFilePath );
                  if (!FileExists( sTblFilePath.toLocal8Bit().constData() ))
						{	sErrMsg = QString( "   Error: Table file not found: %1\n\n" ).arg( sTblFilePath );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
		      	      bRetVal = (ruleSet.addTable( sTblFilePath.toLocal8Bit().constData(), errorFile ) && bRetVal);
						token = m_file.ReadCSVString();
					}
				}
				else if (token == "RULEFILES")
				{	// Before 
					int i, iTr;
					QStringList saReservedStrs;
					std::vector<RuleList*> paTransformRulelists;
					for (i=0; i<=DMRuleReserved_MAX_NUM; i++)
						saReservedStrs.push_back( pszDMRuleReserved[i] );

					// before reading individual RULEs, setup each generic TRANSFORM
					for (i=DMRuleReserved_Default; i<=DMRuleReserved_MAX_NUM; i++)
					{	sTransRLName = QString( "rl_%1" ).arg( pszDMRuleReserved[i] );
						ruleSet.addNewRuleList( sTransRLName.toLocal8Bit().constData(), SetAllDataForDMRuleReserved(i) /*FALSE*/ /*bSetAllData*/, FALSE /*bAllowMultEvals*/,
												FALSE /*bTagAllDataAsUserDef*/, m_file.GetLineCount(), m_fileName.toLocal8Bit().constData(), TRUE /*bPerformSetBEMDataResets*/ );   // "default" rulelist
						paTransformRulelists.push_back( (RuleList*) ruleSet.getRuleList( sTransRLName.toLocal8Bit().constData() ) );
					}

					int iNumTransforms = ruleSet.getNumTransformations();
					for (iTr=0; iTr < iNumTransforms; iTr++)
					{	RuleSetTransformation* pTrans = ruleSet.getTransformation( iTr );			assert( pTrans );
						if (pTrans && !pTrans->getRuleListName().isEmpty())
						{	saReservedStrs.push_back( pTrans->getLongName() );
							ruleSet.addNewRuleList( pTrans->getRuleListName().toLocal8Bit().constData(), TRUE /*bSetAllData*/, FALSE /*bAllowMultEvals*/,
												FALSE /*bTagAllDataAsUserDef*/, m_file.GetLineCount(), m_fileName.toLocal8Bit().constData(), TRUE /*bPerformSetBEMDataResets*/ );   // rulelist for each TRANSFORMATION
							paTransformRulelists.push_back( (RuleList*) ruleSet.getRuleList( pTrans->getRuleListName().toLocal8Bit().constData() ) );
						}
					}
					for (iTr=0; iTr < iNumTransforms; iTr++)	// SAC 3/28/14 - add transform GROUP names AFTER all main transform names have been added
					{	RuleSetTransformation* pTrans = ruleSet.getTransformation( iTr );			assert( pTrans );
						if (pTrans)
						{	for (i=0; i<pTrans->numGroupLongNames(); i++)
							{	if (!pTrans->getGroupLongName(i).isEmpty() && IndexInStringArray( saReservedStrs, pTrans->getGroupLongName(i) ) == -1)
									saReservedStrs.push_back( pTrans->getGroupLongName(i) );
						}	}
					}

					// also add single "default" data type instance
					BEMPropertyDataType* pDT = new BEMPropertyDataType( 1 /*iDBID=1 => 'Default'*/ );				assert( pDT );
					if (pDT)
						ruleSet.addDataType( pDT );
					assert( ruleSet.getNumDataTypes() == 1 );

					QStringList saRuleFiles;
					token = m_file.ReadCSVString();
					while (token != "ENDRULEFILES")
					{	// parse RULE file
						QString sRuleFilePath = token;
						EnsureValidPath_AltPaths( m_fileName, sRuleFilePath );
                  if (!FileExists( sRuleFilePath.toLocal8Bit().constData() ))
						{	sErrMsg = QString( "   Error: rule file not found: %1\n\n" ).arg( sRuleFilePath );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
	      	      {	// restrict first round of rule file reading to TABLEs, which need to be read and parsed prior to RULE parsing in order to properly identify table look-up calls
							if (ReadRuleFile( sRuleFilePath.toLocal8Bit().constData(), saReservedStrs, paTransformRulelists, errorFile, 0 ))
								saRuleFiles.push_back( sRuleFilePath );
							else
								bRetVal = FALSE;
						}
						token = m_file.ReadCSVString();
					}

					// SAC 10/12/12 - added second round of rule file reading to handle parsing of RULEs
					for (int iRF=0; iRF < (int) saRuleFiles.size(); iRF++)
					{	if (!ReadRuleFile( saRuleFiles[iRF].toLocal8Bit().constData(), saReservedStrs, paTransformRulelists, errorFile, 1, iRF+1 ))
							bRetVal = FALSE;
					}
					iNumRuleFiles += (int) saRuleFiles.size();
				}
      	   else if ( token == "TABLELIST" )    // enable data-model rulesets to read in old-style (faster, column index-based) tables - SAC 10/18/21 (MFam)
      	      // read listing of look-up table definitions
      	      bRetVal = ((ReadTableList( errorFile )) && (bRetVal));
				else if (token == "RULELISTFILES")
				{	// SAC 5/17/16 - code to handle parsing of procedural rulelist files (to facilitate rule sharing w/ CBECC-Res for CSE DHW)
      			int ruleListIndex = ruleSet.getNumTransformations();
					token = m_file.ReadCSVString();
					while (token != "ENDRULELISTFILES")
					{	// parse procedural RULELIST file
						QString sRuleFilePath = token;
						EnsureValidPath_AltPaths( m_fileName, sRuleFilePath );
                  if (!FileExists( sRuleFilePath.toLocal8Bit().constData() ))
						{	sErrMsg = QString( "   Error: rulelist file not found: %1\n\n" ).arg( sRuleFilePath );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
							bRetVal = (ReadRuleFile( sRuleFilePath.toLocal8Bit().constData(), iNumRuleFiles++, ruleListIndex, errorFile, ruleSet.getFileStructVersion() ) && bRetVal);
						token = m_file.ReadCSVString();
					}
				}
				token = m_file.ReadToken();
			}

			if (ruleSet.numRulesetProperties() > 0)		// => ADD "ruleset variables" (RULE NEW items) to BEMBase prior to overwriting Symbol/enumeration definitions
			{	QString sErrantRuleProps;
				if (!ruleSet.PostRulePropsToDatabase( sErrantRuleProps, BEMD_NotInput ))
				{	sErrMsg = QString( "   Error encountered inserting ruleset variables (RULE NEWs) into BEMBase: %1\n%2\n" ).arg( m_fileName, sErrantRuleProps );
					errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
					bRetVal = FALSE;
				}
			}

			if (ruleSet.getNumSymLsts() > 0)		// => need to "apply" these symbol selections to BEMBase
			{	if (!ruleSet.postSymbolsToDatabase())
				{	sErrMsg = QString( "   Error encountered posting enumeration data to BEMBase: %1\n\n" ).arg( m_fileName );
					errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
					bRetVal = FALSE;
				}
			}

			// Process library files only AFTER all ruleset variables and enumerations have been added to BEMBase (thereby fixing PropertyType array & symbol lists)
			if (saLibFiles.size() > 0)
			{	if (!ParseLibraryFiles( saLibFiles, errorFile ))
					bRetVal = FALSE;
				saLibFiles.clear();
			}

			if (ruleSet.getNumRangeChecks() > 0)		// => need to "apply" range check definitions to BEMBase
				ruleSet.postRangeChecksToDatabase();
		}
		else
		{
      	int ruleListIndex = 1;
      	int i1RuleFileIdx = 1;
			QStringList saReservedStrs;
			std::vector<RuleList*> paTransformRulelists;
			int iNumDMRuleFiles = 0;
      	// Continue reading until "ENDFILE" encountered
      	while ( token != "ENDFILE" )
      	{
				if ( token == "BEMBASEFILE" )
					ruleSet.setBEMBaseFile( m_file.ReadString() );
// need or desire to include ruleset Labels for Procedural rules ???
//   QStringList     m_saLabels;			// SAC 9/8/14 - labels used to facilitate ruleset source shared by multiple standards/versions
      	   else if ( token == "SCREENSFILE" )
      	      // read screens filename
      	      ruleSet.setScreensFile( m_file.ReadString() );
      	   else if ( token == "TOOLTIPSFILE" )
      	      // read tooltips filename
      	      ruleSet.setToolTipsFile( m_file.ReadString() );
      	
      	   else if ( token == "TABLELIST" )
      	      // read listing of look-up table definitions
      	      bRetVal = ((ReadTableList( errorFile )) && (bRetVal));
      	
      	   else if ( token == "DATATYPES" )
      	      // read file containing data type definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, DataTypeList )) && (bRetVal));
      	
      	   else if ( token == "RANGES" )
      	      // read file containing range checking definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, RangesList   )) && (bRetVal));
      	
      	   else if ( token == "SYMBOLS" )
      	      // read file containing symbol list definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, SymbolList   )) && (bRetVal));
      	
      	   else if ( token == "MAXCHILD" )
      	      // read file containing MaxChild list definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, MaxChildList )) && (bRetVal));
      	
      	   else if ( token == "RESETS" )
      	      // read file containing Reset list definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, ResetList    )) && (bRetVal));
      	
      	   else if ( token == "UNIQUEASSIGNMENTS" )
      	      // read file containing unique component assignments list definitions
      	      bRetVal = ((ReadListFile( m_file.ReadString(), errorFile, UniqueList   )) && (bRetVal));
      	
      	   else if ( token == "LIBRARY" || token == "RULEFILE" )		// SAC 9/23/14 - expand to handle RULEFILE as well
      	   {  // read file containing library objects
      	      QString libFileStr = m_file.ReadString();
					//QDir libFile( libFileStr );
      	      //QString libFileDir = libFile.path();
      	      //if (libFileDir.length() == 0)
      	      //{
					//	QDir qdFileWithPath( m_fileName );
					//	libFile.setPath( qdFileWithPath.absolutePath() );
					//	libFileStr = qdFileWithPath.absoluteFilePath( libFileStr );
      	      //}
               // replaced above w/ following to accommodate alternate (shared) rule source paths - SAC 08/31/21 (MFam)
					EnsureValidPath_AltPaths( m_fileName, libFileStr );
               if (!FileExists( libFileStr.toLocal8Bit().constData() ))
					{	sErrMsg = QString( "   Error: %1 file not found: %2\n\n" ).arg( token, libFileStr );
						errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
						bRetVal = FALSE;
					}
					else if ( token == "LIBRARY" )
	      	      bRetVal = ((ReadLibraryText( libFileStr.toLocal8Bit().constData(), BEMO_RuleLib, &errorFile )) && (bRetVal));
	      	   else
						bRetVal = ((ReadRuleFile( libFileStr.toLocal8Bit().constData(), i1RuleFileIdx++, ruleListIndex, errorFile, ruleSet.getFileStructVersion() )) && (bRetVal));	// SAC 9/23/14 - new
      	   }

      	   else if ( token == "RULELIST" )
      	      // read a compliance rulelist
      	      bRetVal = (ReadRuleList( ruleListIndex++, errorFile, ruleSet.getFileStructVersion() ) && bRetVal);

      	   else if ( token == "DATAMODELRULES" )		// SAC 3/24/20 - added ability to specify type of DataModelRule compatibility (initially just CA-HERS
      	   {	token = m_file.ReadToken();  // read next token
					if (token == "CAHERS")
					{	// manually add each CAHERS transform into ruleset
						RuleSetTransformation* pActiveTrans = new RuleSetTransformation( QString("USER"), QString("u"), QString("rl_USER"), 0 /*iSrcTransformIdx*/ );			assert( pActiveTrans );
						if (pActiveTrans == NULL)
						{	sErrMsg = QString( "   Error: Unable to add TRANSFORMATION USER/u to the ruleset.\n\n" );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
						{	ruleSet.addTransformation( pActiveTrans );
							pActiveTrans = new RuleSetTransformation( QString("RATED"), QString("rt"), QString("rl_RATED"), 0 /*iSrcTransformIdx*/ );			assert( pActiveTrans );
							if (pActiveTrans == NULL)
							{	sErrMsg = QString( "   Error: Unable to add TRANSFORMATION RATED/rt to the ruleset.\n\n" );
								errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
								bRetVal = FALSE;
							}
							else
							{	ruleSet.addTransformation( pActiveTrans );
								pActiveTrans->addGroupLongName(  QString("ANNUAL") );
								pActiveTrans->addGroupShortName( QString("a") );
								pActiveTrans = new RuleSetTransformation( QString("REF"), QString("rf"), QString("rl_REF"), 0 /*iSrcTransformIdx*/ );			assert( pActiveTrans );
								if (pActiveTrans == NULL)
								{	sErrMsg = QString( "   Error: Unable to add TRANSFORMATION REF/rf to the ruleset.\n\n" );
									errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
									bRetVal = FALSE;
								}
								else
								{	ruleSet.addTransformation( pActiveTrans );
									pActiveTrans->addGroupLongName(  QString("ANNUAL") );
									pActiveTrans->addGroupShortName( QString("a") );
									pActiveTrans = new RuleSetTransformation( QString("INDEX_RATED"), QString("it"), QString("rl_INDEX_RATED"), 0 /*iSrcTransformIdx*/ );			assert( pActiveTrans );
									if (pActiveTrans == NULL)
									{	sErrMsg = QString( "   Error: Unable to add TRANSFORMATION INDEX_RATED/it to the ruleset.\n\n" );
										errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
										bRetVal = FALSE;
									}
									else
									{	ruleSet.addTransformation( pActiveTrans );
										pActiveTrans->addGroupLongName(  QString("ANNUAL") );
										pActiveTrans->addGroupShortName( QString("a") );
										pActiveTrans = new RuleSetTransformation( QString("INDEX_REF"), QString("if"), QString("rl_INDEX_REF"), 0 /*iSrcTransformIdx*/ );			assert( pActiveTrans );
										if (pActiveTrans == NULL)
										{	sErrMsg = QString( "   Error: Unable to add TRANSFORMATION INDEX_REF/if to the ruleset.\n\n" );
											errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
											bRetVal = FALSE;
										}
										else
										{	ruleSet.addTransformation( pActiveTrans );
											pActiveTrans->addGroupLongName(  QString("ANNUAL") );
											pActiveTrans->addGroupShortName( QString("a") );
						}	}	}	}	}

						if (bRetVal)
						{	int i, iTr;
							QString sTransRLName;
							//QStringList saReservedStrs;
							//std::vector<RuleList*> paTransformRulelists;
							// setup of reserved words/terms & default/reserved rulelists
							for (i=0; i<=DMRuleReserved_MAX_NUM; i++)
								saReservedStrs.push_back( pszDMRuleReserved[i] );

							// before reading individual RULEs, setup each generic TRANSFORM
							for (i=DMRuleReserved_Default; i<=DMRuleReserved_MAX_NUM; i++)
							{	sTransRLName = QString( "rl_%1" ).arg( pszDMRuleReserved[i] );
								ruleSet.addNewRuleList( sTransRLName.toLocal8Bit().constData(), SetAllDataForDMRuleReserved(i) /*FALSE*/ /*bSetAllData*/, FALSE /*bAllowMultEvals*/,
														FALSE /*bTagAllDataAsUserDef*/, m_file.GetLineCount(), m_fileName.toLocal8Bit().constData(), TRUE /*bPerformSetBEMDataResets*/ );   // "default" rulelist
								paTransformRulelists.push_back( (RuleList*) ruleSet.getRuleList( sTransRLName.toLocal8Bit().constData() ) );
							}

							int iNumTransforms = ruleSet.getNumTransformations();
							for (iTr=0; iTr < iNumTransforms; iTr++)
							{	RuleSetTransformation* pTrans = ruleSet.getTransformation( iTr );			assert( pTrans );
								if (pTrans && !pTrans->getRuleListName().isEmpty())
								{	saReservedStrs.push_back( pTrans->getLongName() );
									ruleSet.addNewRuleList( pTrans->getRuleListName().toLocal8Bit().constData(), TRUE /*bSetAllData*/, FALSE /*bAllowMultEvals*/,
														// SAC 4/3/20 - switched bTagAllDataAsUserDef from FALSE to TRUE for CAHERS transform rulelists
														TRUE /*bTagAllDataAsUserDef*/, m_file.GetLineCount(), m_fileName.toLocal8Bit().constData(), TRUE /*bPerformSetBEMDataResets*/ );   // rulelist for each TRANSFORMATION
									paTransformRulelists.push_back( (RuleList*) ruleSet.getRuleList( pTrans->getRuleListName().toLocal8Bit().constData() ) );
								}
							}
							for (iTr=0; iTr < iNumTransforms; iTr++)	// SAC 3/28/14 - add transform GROUP names AFTER all main transform names have been added
							{	RuleSetTransformation* pTrans = ruleSet.getTransformation( iTr );			assert( pTrans );
								if (pTrans)
								{	for (i=0; i<pTrans->numGroupLongNames(); i++)
									{	if (!pTrans->getGroupLongName(i).isEmpty() && IndexInStringArray( saReservedStrs, pTrans->getGroupLongName(i) ) == -1)
											saReservedStrs.push_back( pTrans->getGroupLongName(i) );
								}	}
							}
						}
// DATAMODELRULES  CAHERS
//       ; hardwires rulelists rl_CHECKSIM, rl_CHECKCODE, rl_DEFAULT
//       ; and CA-HERS-specific transformations:
//       ;        RATED  (rt  Or ANNUAL a  From USER (default))
//       ;        INDEX_RATED  (it  Or ANNUAL a  From RATED)
//       ;        REFERENCE  (rf  Or ANNUAL a  From RATED)
//       ;        INDEX_REFERENCE  (if  Or ANNUAL a  From INDEX_RATED)

					}
					else
					{	sErrMsg = QString( "   Error reading main ruleset definition file - unrecognized DATAMODELRULES type '%1': %2\n\n" ).arg( token, m_fileName );
						errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
						bRetVal = FALSE;
				}	}

      	   else if ( token == "DMRULEFILE" )		// SAC 3/24/20 - added ability to specify type of DataModelRule compatibility (initially just CA-HERS
				{	QString sRuleFilePath = m_file.ReadCSVString();
					EnsureValidPath_AltPaths( m_fileName, sRuleFilePath );
               if (!FileExists( sRuleFilePath.toLocal8Bit().constData() ))
					{	sErrMsg = QString( "   Error: rule file not found: %1\n\n" ).arg( sRuleFilePath );
						errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
						bRetVal = FALSE;
					}
					else
      	      {	// restrict first round of rule file reading to TABLEs, which need to be read and parsed prior to RULE parsing in order to properly identify table look-up calls
						if (!ReadRuleFile( sRuleFilePath.toLocal8Bit().constData(), saReservedStrs, paTransformRulelists, errorFile, 0 ))
						{	sErrMsg = QString( "   Error: unable to parse rule file for table(s): %1\n\n" ).arg( sRuleFilePath );
							errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
							bRetVal = FALSE;
						}
						else
						{	if (!ReadRuleFile( sRuleFilePath.toLocal8Bit().constData(), saReservedStrs, paTransformRulelists, errorFile, 1, i1RuleFileIdx++ /*++iNumDMRuleFiles*/ ))
							{	sErrMsg = QString( "   Error: unable to parse rule file: %1\n\n" ).arg( sRuleFilePath );
								errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
								bRetVal = FALSE;
						}	}
				}	}

      	   else  // bogus token encountered
      	   {  assert( FALSE );  }  // throw exception ??
      	
      	   token = m_file.ReadToken();  // read next token
      	}

		// added in rule compilation stuff previously only present in DataModel rules - SAC 3/25/20
			if (ruleSet.numRulesetProperties() > 0)		// => ADD "ruleset variables" (RULE NEW items) to BEMBase prior to overwriting Symbol/enumeration definitions
			{	QString sErrantRuleProps;
				if (!ruleSet.PostRulePropsToDatabase( sErrantRuleProps, BEMD_NotInput ))
				{	sErrMsg = QString( "   Error encountered inserting ruleset variables (RULE NEWs) into BEMBase: %1\n%2\n" ).arg( m_fileName, sErrantRuleProps );
					errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
					bRetVal = FALSE;
				}
			}

			if (ruleSet.getNumSymLsts() > 0)		// => need to "apply" these symbol selections to BEMBase
			{	if (!ruleSet.postSymbolsToDatabase())
				{	sErrMsg = QString( "   Error encountered posting enumeration data to BEMBase: %1\n\n" ).arg( m_fileName );
					errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
					bRetVal = FALSE;
				}
			}

		//	// Process library files only AFTER all ruleset variables and enumerations have been added to BEMBase (thereby fixing PropertyType array & symbol lists)
		//	if (saLibFiles.size() > 0)
		//	{	if (!ParseLibraryFiles( saLibFiles, errorFile ))
		//			bRetVal = FALSE;
		//		saLibFiles.clear();
		//	}

			if (ruleSet.getNumRangeChecks() > 0)		// => need to "apply" range check definitions to BEMBase
				ruleSet.postRangeChecksToDatabase();

		}   
   }
	catch (std::exception& e)
	{
		QString sErrMsg = QString( "Error reading rule file: %1\n\t - cause: %2" ).arg( m_fileName, e.what() );
//		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
      BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
	}
 	catch (...)
  	{
		QString sErrMsg = QString( "Error reading rule file: %1" ).arg( m_fileName );
//		errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
//		std::cout << sErrMsg.toLocal8Bit().constData();
		bRetVal = FALSE;
      BEMMessageBox( sErrMsg, "", 2 /*warning*/ );
  	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  ReadRuleList()
//
// Purpose ------------------------------------------------------------------
//   Reads the contents of a single compliance rulelist from the main ASCII
//   ruleset file into memory.
//   
// Arguments ----------------------------------------------------------------
//   int    ruleListIndex : integer index of this rulelist
//   QFile& errorFile     : file where error messages are written
//   int iHardwireEnumStrVal : -1 (ruleset default) / 0 Value / 1 String - SAC 09/24/21 (MFam)
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   Rule List Format:
//      RULELIST "RuleListName"
//         
//        "RULE1 ID"
//          PARAMETER1 = { EXPRESSION }
//        "RULE2 ID"
//          PARAMETER2 = { EXPRESSION }
//        ...
//      END
//
//   Pseudo-code:
//      Create new list
//      Loop over input file until "END"
//         Read the rule id
//         Read the rule parameter id
//         Read the expression string
//      end loop
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleFile::ReadRuleList( int ruleListIndex, QFile& errorFile, int iFileStructVer, int i1RuleFileIndex /*=0*/,
			  							BEMTextIO* pFile /*=NULL*/, const char* pszFileName /*=NULL*/, int iHardwireEnumStrVal /*=-1*/ )
{
   bool bRetVal = TRUE;
   if (pFile == NULL)
   	pFile = &m_file;
   QString pnFileName;
   if (pszFileName && strlen( pszFileName ) > 0)
   	pnFileName = pszFileName;
   else
   	pnFileName = m_fileName;

   QString token = pFile->ReadString();  // reads new rulelist's name
   long lSetAllData = pFile->ReadLong(); // reads bSetAllData flag

   // SC 6/12/00
   long lAllowMultipleEvaluations = 1;
   if (iFileStructVer > 1)
      lAllowMultipleEvaluations = pFile->ReadLong();

   // SC 4/2/01
   long lTagAllDataAsUserDefined = 0;
   if (iFileStructVer > 2)
      lTagAllDataAsUserDefined = pFile->ReadLong();

   // SAC 9/18/05
   long lDONTPerformSetBEMDataResets = 0;
   if (iFileStructVer > 4)
      lDONTPerformSetBEMDataResets = pFile->ReadLong();

	// SAC 5/26/03 - added int iLineNumber & const char* pszFileName arguments
	pnFileName.replace('\\','/');
   QString sFN = (pnFileName.lastIndexOf('/') > 0 ? pnFileName.right( (pnFileName.length()-pnFileName.lastIndexOf('/')-1) ) : pnFileName);
   ruleSet.addNewRuleList( token.toLocal8Bit().constData(), (lSetAllData != 0), (lAllowMultipleEvaluations != 0), (lTagAllDataAsUserDefined > 0),
                    pFile->GetLineCount(), (const char*) sFN.toLocal8Bit().constData(), (lDONTPerformSetBEMDataResets == 0), iHardwireEnumStrVal );  // Creates new rule list

   int ruleIndex = 1;

   pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file
   QString sRuleID;
   // read the first rule's ID string, then incrament rule index
   ReadRuleID( sRuleID, ruleListIndex, ruleIndex, pFile, sFN.toLocal8Bit().constData() );
	int iRuleFileLineNum = pFile->GetLineCount();
   ruleIndex++;

   while ( sRuleID != "END" && !pFile->AtEOF() )		// SAC 1/23/20 - added check for EOF
   {
      pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file
      QString sParamID;
      QStringList slKeyList;		int iNumKeys=-1;
#define MAX_NUM_KEYS  5
      std::vector<int> iaKeyInts[MAX_NUM_KEYS];
      while ((iNumKeys+1) < MAX_NUM_KEYS && iNumKeys < slKeyList.count())
      {	iNumKeys = slKeyList.count();		sParamID.clear();
      	// read component/parameter string which from left side of equation
      	pFile->ReadBEMProcParam( sParamID, FALSE, &slKeyList, &iaKeyInts[iNumKeys] );
      	pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file
      }
		if (sParamID.length() > 4 && sParamID.left(3).compare( "for:", Qt::CaseInsensitive ) == 0)
		{	assert( false );  }	// too many 'key's specified

      // Skip the '='
      if ( '=' != pFile->GetChr() )
	  {  assert( FALSE );  }   // TO DO: Throw an exception
      pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file

      // Skip the '{'
      if ( '{' != pFile->GetChr() )
      {  assert( FALSE );  }  // TO DO: Throw an exception
      pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file

      // Read the equation/expression
      QString expString;
      char ch = pFile->GetChr();
      // continue reading characters and adding them to expression until close bracket encountered
      while ( ch != '}' )
      {
         // This handles comments embedded in expressions
         if ( ch == ';' )
         {
            pFile->ReadLine();
            ch = pFile->GetChr();
         }

         expString += ch;
         if ( pFile->AtEOL() )
            expString += ' ';

         ch = pFile->GetChr();
      }
      if ( ch != '}' )
      {  assert( FALSE );  }  // TO DO: exception if there isnt a '}'
      pFile->Advance();  // advance past any spaces or comments in ASCII ruleset file

		if (iNumKeys < 1)
		{	// no keys so just do normal rule processing... - SAC 12/10/20
	      // add rule to current rule list
// 	     RuleProcAdd( sRuleID, sParamID, expString, i1RuleFileIndex /*was: 1*/, iRuleFileLineNum /*iRuleLineNum*/ );
//			ruleSet.addRuleToCurrentList( sRuleID.toLocal8Bit().constData(), sParamID.toLocal8Bit().constData(),
//													expString.toLocal8Bit().constData(), i1RuleFileIndex /*was: 1*/,
			ruleSet.addRuleToCurrentList( sRuleID, sParamID,
													expString, i1RuleFileIndex /*was: 1*/,
													iRuleFileLineNum /*iRuleLineNum*/ );
		}
		else		// duplicate rule for however many keys and key values are specified
		{	int iKeyIdx[MAX_NUM_KEYS] = {0,0,0,0,0};
			int iKeyRuleCount=0;
			for (iKeyIdx[0]=0; iKeyIdx[0] < std::max( 1, (int) iaKeyInts[0].size() ); iKeyIdx[0]++)
				for (iKeyIdx[1]=0; iKeyIdx[1] < std::max( 1, (int) iaKeyInts[1].size() ); iKeyIdx[1]++)
					for (iKeyIdx[2]=0; iKeyIdx[2] < std::max( 1, (int) iaKeyInts[2].size() ); iKeyIdx[2]++)
						for (iKeyIdx[3]=0; iKeyIdx[3] < std::max( 1, (int) iaKeyInts[3].size() ); iKeyIdx[3]++)
							for (iKeyIdx[4]=0; iKeyIdx[4] < std::max( 1, (int) iaKeyInts[4].size() ); iKeyIdx[4]++)
							{
								QString sKeyRuleID=sRuleID, sKeyParamID=sParamID, expKeyString=expString, sKeyVal;
								for (int iKey=0; iKey<MAX_NUM_KEYS; iKey++)
									if (iaKeyInts[iKey].size() > 0)
									{	sKeyVal = QString::number( iaKeyInts[iKey][iKeyIdx[iKey]] );
										sKeyRuleID += QString(", %1=%2").arg( slKeyList[iKey], sKeyVal );
										sKeyParamID.replace(  slKeyList[iKey], sKeyVal );
										expKeyString.replace( slKeyList[iKey], sKeyVal );
									}
								// add rule to current rule list
								ruleSet.addRuleToCurrentList( sKeyRuleID, sKeyParamID, expKeyString,
																		i1RuleFileIndex /*was: 1*/, iRuleFileLineNum /*iRuleLineNum*/ );
								iKeyRuleCount++;
#ifdef _DEBUG  // debugging
QString sDbg = QString( "key rule added: rulefileidx %1, line# %2: %3 || %4 || %5\n" ).arg( QString::number(i1RuleFileIndex), QString::number(iRuleFileLineNum), sKeyRuleID, sKeyParamID, expKeyString );
errorFile.write( sDbg.toLocal8Bit().constData(), sDbg.length() );
#endif
		}					}

      // read the next rule's ID string, then incrament rule index
      ReadRuleID( sRuleID, ruleListIndex, ruleIndex, pFile, sFN.toLocal8Bit().constData() );
		iRuleFileLineNum = pFile->GetLineCount();
      ruleIndex++;
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  ReadRuleID()
//
// Purpose ------------------------------------------------------------------
//   Reads the rule ID for the next rule contained in the ASCII ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   QString& sId           : string to fill with rule ID
//   int      ruleListIndex : integer rule list index
//   int      ruleIndex     : rule index (within this rule list)
//   
// Return Value -------------------------------------------------------------
//   None - but sId argument is populated with the rule ID string
//   
// Notes --------------------------------------------------------------------
//   The rule ID may be the END token, so handle that case by testing for '"'.
//   Format return string as: "Rule L#.R#, Line N: <RuleID>"
//      where: L# = RuleList index (1-8),
//             R# = index to rule in RuleList, and 
//             N  = rule file line number.
//   
/////////////////////////////////////////////////////////////////////////////
void RuleFile::ReadRuleID( QString& sId, int ruleListIndex, int ruleIndex,
										BEMTextIO* pFile /*=NULL*/, const char* pszRuleFileName /*=NULL*/ )
{
	if (pFile == NULL)
		pFile = &m_file;

   char ch = pFile->GetChr();
   pFile->UnGetChr();

   if ( ch == '\"' )  // check for starting '"' => next rule's name (vs. END)
   {
      sId = "";
      if (pszRuleFileName && strlen( pszRuleFileName ) > 0)
			// Add "Rule L#.R#, Line N: " before reading and appending the RuleID
			sId = QString( "Rule %1, %2, '%3' Line %4: " ).arg( QString::number(ruleListIndex), QString::number(ruleIndex), pszRuleFileName, QString::number(pFile->GetLineCount()) );
		else
			// Add "Rule L#.R#, Line N: " before reading and appending the RuleID
			sId = QString( "Rule %1, %2, Line %3: " ).arg( QString::number(ruleListIndex), QString::number(ruleIndex), QString::number(pFile->GetLineCount()) );
      sId += pFile->ReadString();
   }
   else
      sId = pFile->ReadToken();
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  ReadTableList()
//
// Purpose ------------------------------------------------------------------
//   Reads the table look-up definitions and table files themselves from the
//   main ASCII ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   QFile& errorFile  : file where error messages are written
//   
// Return Value -------------------------------------------------------------
//   FALSE if any of the table look-up file reads failed, else TRUE.
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleFile::ReadTableList( QFile& errorFile )
{
   bool bRetVal = TRUE;
   QString token = m_file.ReadToken();  // read the name of the first look-up table
   while ( token != "END" )
   {
      char cTemp = '\0';
      while ( cTemp != '(' && !m_file.AtEOL() ) cTemp = m_file.GetChr();

      QString fileName;
      // read table look-up filename
      m_file.String( fileName, _MAX_PATH );
      // extract directopry portion of look-up filename
      QString tableFileDir;


		//QDir qdFileToCheck( fileName );
		//tableFileDir = qdFileToCheck.path();
		//// if no directory portion of filename exists, then create one
		//if (tableFileDir.length() == 0)
		//{	QDir qdFileWithPath( m_fileName );
		//	qdFileToCheck.setPath( qdFileWithPath.absolutePath() );
		//	fileName = qdFileWithPath.absoluteFilePath( fileName );
		//}
		EnsureValidPath_AltPaths( m_fileName, fileName );     // SAC 08/31/21
      if (!FileExists( fileName.toLocal8Bit().constData() ))
		{	QString sErrMsg = QString( "   Error: Table file not found: %1\n\n" ).arg( fileName );
			errorFile.write( sErrMsg.toLocal8Bit().constData(), sErrMsg.length() );
			bRetVal = FALSE;
		}
		else
      {
         cTemp = '\0';
         while ( cTemp != ',' && !m_file.AtEOL() ) cTemp = m_file.GetChr(); // Skip comma
         int nParams;
         m_file.Int( nParams, 10 );  // get # independent variables
         cTemp = '\0';
         while ( cTemp != ',' && !m_file.AtEOL() ) cTemp = m_file.GetChr(); // Skip comma
         int nCols;
         m_file.Int( nCols, 10 );  // get # dependent variables

         m_file.GetLine(); // Skip the rest of this line

         // read the look-up table and add this table definition to the current ruleset
         bRetVal = ((ruleSet.addTable( token.toLocal8Bit().constData(), fileName.toLocal8Bit().constData(), nParams, nCols, errorFile )) && (bRetVal));

         // read the next table's name (or "END")
         token = m_file.ReadToken();
   }  }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// RuleFile Class Function:  ReadListFile()
//
// Purpose ------------------------------------------------------------------
//   Reads the contents of a list file into the current ruleset.
//   
// Arguments ----------------------------------------------------------------
//   QString   pnFileName : path/filename of data type assignment file
//   QFile&    errorFile  : file where error messages are written
//   int       iListType  : integer value identifying the list file to read
//   
// Return Value -------------------------------------------------------------
//   The return value of RuleProcRead*****List()
//   
// Notes --------------------------------------------------------------------
//   
/////////////////////////////////////////////////////////////////////////////
bool RuleFile::ReadListFile( QString pnFileName, QFile& errorFile, int iListType )
{
   QString dtFileDir;
//   // extract directory portion of filename
//   pnFileName.GetDir( dtFileDir );
//   // if no directory portion of filename exists, then create one
//   if ( dtFileDir.length() == 0 )
//   {
//      QString fileDir;
//      QString fileDrive;
//      m_fileName.GetDir( fileDir );
//      m_fileName.GetDrive( fileDrive );
//
//      pnFileName.SetDir( fileDir );
//      pnFileName.SetDrive( fileDrive );
//   }
	QDir qdFileToCheck( pnFileName );
	dtFileDir = qdFileToCheck.path();
	// if no directory portion of filename exists, then create one
	if (dtFileDir.length() == 0)
	{	QDir qdFileWithPath( m_fileName );
		qdFileToCheck.setPath( qdFileWithPath.absolutePath() );
		pnFileName = qdFileWithPath.absoluteFilePath( pnFileName );
	}

   // read contents of data type assignment file into current ruleset
   bool bRetVal = FALSE;
   switch (iListType)
   {
      case DataTypeList : bRetVal = ruleSet.readDataTypesText(    pnFileName, errorFile );   break;
      case RangesList   : bRetVal = ruleSet.readRangesText(       pnFileName, errorFile );   break;
      case SymbolList   : bRetVal = ruleSet.readSymbolsText(      pnFileName, errorFile );   break;
      case MaxChildList : bRetVal = true; /*assert( false );*/	break;		// bRetVal = RuleProcReadMaxChildList(     pnFileName, errorFile );   break;
      case ResetList    : bRetVal = ruleSet.readResetsText(       pnFileName, errorFile );   break;
      case UniqueList   : bRetVal = true; /*assert( false );*/	break;		// bRetVal = RuleProcReadUniqueAssignList( pnFileName, errorFile );   break;
   }
   return bRetVal;
}


