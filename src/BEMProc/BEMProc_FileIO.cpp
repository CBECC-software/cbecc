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

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <memory>
#include <sys/timeb.h>
#include <boost/filesystem.hpp>

#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProc_FileIO.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMProcObject.h"
#include "expTextIO.h"

#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
using namespace boost::posix_time;

#include "expFormula.h"

#pragma warning(disable : 4127)
#include <QtXml/qdom.h>
#include <QtCore/qfile.h>
#include <QtCore/qiodevice.h>
#include <QtCore/qtextstream.h>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#pragma warning(default : 4127)

#define  MAX_COLUMN  78


// -----------------------------------------------------------------------------
// File I/O
// -----------------------------------------------------------------------------

static QString esLogFileName;
static QString esCSVLogFileName;

static char szUser[]    = "User";
static char szRuleLib[] = "RLib";
static char szUserLib[] = "ULib";

static char szUndefined[]   = "Undef";
static char szProgDefault[] = "PDef";
static char szRuleDefault[] = "RDef";
static char szRuleLibrary[] = "RLib";
static char szRuleDefined[] = "RVal";
static char szUserDefault[] = "UDef";
static char szUserLibrary[] = "Ulib";
static char szUserDefined[] = "UVal";
static char szSimResult[]   = "SRes";

static char szJan[] = "Jan";
static char szFeb[] = "Feb";
static char szMar[] = "Mar";
static char szApr[] = "Apr";
static char szMay[] = "May";
static char szJun[] = "Jun";
static char szJul[] = "Jul";
static char szAug[] = "Aug";
static char szSep[] = "Sep";
static char szOct[] = "Oct";
static char szNov[] = "Nov";
static char szDec[] = "Dec";

static char szCritDefComment[] = "CRITDEFCOMMENT";
static char szEndComment[]     = "ENDCOMMENT";

static char szTreeState[] = "TreeState";

static char* szMonth[] =
{
   szJan, szFeb, szMar, szApr, szMay, szJun,
   szJul, szAug, szSep, szOct, szNov, szDec
};   

// end-of-file marker
static char szEnd[] = "END_OF_FILE";
static char szCSE_Run[] = " RUN";		// sac 3/15/12
static char szCSE_End[] = " $EOF";

// ruleset filename marker
static char szRulesetFN[] = "RulesetFilename";

// These are the string tables for reading and writing object types
// and property statuses.  They must be in the same order as the 
// enums in BEMProc.h.

static char* szaObjTypeString[] = 
{
   szUser,
   szRuleLib,
   szUserLib
};

static char* szaPropertyStatusString[] = 
{
   szUndefined,
   szProgDefault,
   szRuleDefault,
   szRuleLibrary,
   szRuleDefined,
   szUserDefault,
   szUserLibrary,
   szUserDefined,
   szSimResult
};

static BEM_PropertyStatus GetStatusFromString(  QString sStatusString );
static BEM_ObjType        GetObjTypeFromString( QString sObjTypeString );


static void SetAtGrow( QStringList* psl, int idx, QString& str )
{	assert( psl );
	if (psl)
	{	int iAdd = (int) psl->size();
		while (iAdd++ < idx)
			psl->push_back( "" );
		if (idx >= (int) psl->size())
			psl->push_back( str );
		else
			psl->replace( idx, str );
	}
}


static inline int IndexInArray( std::vector<int>& iArray, int iVal )
{	int i=0; 
	for (; i < (int) iArray.size(); i++)
		if (iArray[i] == iVal)
			return i;
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//	CProjectFile
//    This class is used to read and write BEM project files.
/////////////////////////////////////////////////////////////////////////////
class CProjectFile
{
public:
   CProjectFile( const char* fileName, int iFileMode = BEMFM_INPUT /*bool bIsInputMode = TRUE*/, long lDBIDVersion = 0,
                 long lVersion = 0, int fileMode = BEMTextIO::load, bool bWriteAllProperties = FALSE,  // SAC 1/15/03
                 BOOL bSupressAllMessageBoxes = FALSE,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
					  int iFileType = 0, bool bOnlyValidInputs = false,   // SAC 8/30/11 - added iFileType argument  // SAC 4/16/14 - added bOnlyValidInputs arg
					  int iPropertyCommentOption = 0, 		// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
					  std::vector<long>* plaClsObjIndices = NULL,		// SAC 12/14/18 - added to facilitate writing of specific object type/index elements to CSE input files (initially for HPWH sizing runs - HPWHSIZE)
					  bool bReportInvalidEnums = true );		// SAC 5/20/19 - prevent logging errors associated w/ invalid enums (for writing of .ribd##i inputs during analysis)
   ~CProjectFile();

// SAC 4/27/03 - Modified function to return BOOL
   BOOL Read( int iBEMProcIdx=0,
              // SAC 5/12/00 - added following args to enable UI reporting of failed data setting
              int iMaxDBIDSetFailures=0, int* piDBIDSetFailures=NULL,
              int* piObjIdxSetFailures=NULL, QStringList* psaDataSetFailures=NULL,   // SAC 7/10/03 - added to facilitate more informative error reporting
              BEMStraightMap* pStraightMap=NULL,  // SAC 11/14/01 - added another method of mapping old properties to new
              // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
              BEMComponentMap* pCompMap=NULL, BEMPropertyMap* pPropMap=NULL, 
				  BOOL bLogDurations=FALSE );  // SAC 10/24/13 - added duration logging
   void ReadResults( int iBEMProcIdx=0 );

   void ReadRulesetFilename( QString& sRulesetFilename );
   void WriteRulesetFilename( int iBEMProcIdx=-1 );

   BEMObject* ReadComponent( int& iDBIDSetFailureIdx, bool bCreateObj = TRUE, const char* psOnlyProp = NULL, int iBEMProcIdx = 0,
                             // SAC 5/12/00 - added the first and following args to enable UI reporting of failed data setting
                             int iMaxDBIDSetFailures=0, int* piDBIDSetFailures=NULL,
                             int* piObjIdxSetFailures=NULL, QStringList* psaDataSetFailures=NULL,   // SAC 7/10/03 - added to facilitate more informative error reporting
                             BEMStraightMap* pStraightMap=NULL,  // SAC 11/14/01 - added another method of mapping old properties to new
                             // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
                             BEMComponentMap* pCompMap=NULL, BEMPropertyMap* pPropMap=NULL, QVector<int>* pivMapCompsCreated=NULL );
   QString ReadNextPropType();
   QString ReadCritDefComment();
   bool IsOpen();
   bool StatusRequiresWrite( BEMProperty* pProp, bool bWritePrimaryDefaultData=false );		// SAC 6/10/15 - CBECC issue 1061
   bool MustWriteProperty(   BEMObject* pObj, BEMProperty* pProp, int iProp, bool bWritePrimaryDefaultData=false );  // SAC 1/22/02 - final argument POSITION pos -> int iProp		// SAC 6/10/15 - CBECC issue 1061
   bool UseParenArrayFormat( BEMObject* pObj, BEMProperty* pProp, int iProp );  // SAC 1/22/02 - final argument POSITION pos -> int iProp
   void PropertyToString( BEMObject* pObj, BEMProperty* pProp, QString& sData, int iBEMProcIdx, BOOL bOnlyFromCurrentSymDepSet=TRUE );		// SAC 6/8/19
   void WriteProperties( BEMObject* pObj, int iBEMProcIdx=-1, bool bWritePrimaryDefaultData=false,		// SAC 6/8/15 - CBECC issue 1061
   								bool bSkipWritingComponentName=false, int iIndentSpcs=0, 	// SAC 3/23/16 - added to enable re-write of "ALTER"ed objects (related to SpecificProperty tracking/writing)
                           bool bWriteOnlyCSEExpressionProperties=false );    // workaround for CSE object COPY bug requiring re-write of expressions - SAC 05/19/21
   void WriteBracketPropertyArray( BEMObject* pObj, BEMProperty* pProp, int& iProp, int iBEMProcIdx, bool bWritePrimaryDefaultData=false, int iIndentSpcs=0 );  // SAC 1/22/02 - final argument POSITION& pos -> int& iProp	// SAC 6/10/15 - CBECC issue 1061
   void WriteParenPropertyArray(   BEMObject* pObj, BEMProperty* pProp, int& iProp, int iBEMProcIdx, int iIndentSpcs=0 );  // SAC 1/22/02 - final argument POSITION& pos -> int& iProp
   void WriteCritDefComment( const char* szComment );
   void WriteAssignedComponents( BEMObject* pObj, int iBEMProcIdx=-1, bool bWritePrimaryDefaultData=false, int iIndentSpcs=0 );		// SAC 6/8/15 - CBECC issue 1061
   void WriteComponent( BEMObject* pObj, int iBEMProcIdx=-1, bool bWritePrimaryDefaultData=false, int iIndentSpcs=0 );		// SAC 6/8/15 - CBECC issue 1061
   void WriteProjectFile( int iBEMProcIdx=-1 );  // SAC 3/18/13
	void WriteComment( QString sDescrip, QString sUnits, int iStartChr, int iWhiteSpc );	// SAC 12/5/16

   void       SkipToEndOfComponent();
   BOOL       NameIsUnique( QString& sObjName, BOOL bCheckLibsOnly, int iBEMProcIdx=-1 );
   BEMObject* ReturnExistingComponent( int i1Class, QString& sObjName, int iBEMProcIdx=-1 );

   void SetWriteLibDataFlag( bool bFlag );
   void SetWriteAssignedCompsFlag( bool bFlag );
   void SetPastingClassFromClipboard( int i1Class );

   void ResetComponentNameList();
   void AddToComponentNameList( QString& sCompName );
   bool InComponentNameList( QString& sCompName );

   void ResetNewComponentNameList();
   void AddToNewComponentNameList( QString& sCompName );
   bool SubstituteComponentName( QString& sCompName );

   void WriteEndOfFileMarker( int iBEMProcIdx=-1 );

	void AppendCSEObjectType( QString& sPartial, BEMObject* pObj );
	void WriteObjectName( QString& sRec, BEMObject* pObj );

	// SAC 3/22/16
	void AddToSpecificProperties( const char* pszSpecPropName )		{	m_bSpecificPropertiesActive = TRUE;
																							m_saSpecificPropNames.push_back( pszSpecPropName );	}
	void RemoveFromSpecificProperties(const char* pszSpecPropName)	{	for (int i = (int) m_saSpecificPropNames.size()-1; i >= 0; i--)
                                                                     {  if (m_saSpecificPropNames[i].compare( pszSpecPropName, Qt::CaseInsensitive )==0)
																							      m_saSpecificPropNames.removeAt( i );
                                                                     }
                                                                     m_bSpecificPropertiesActive = (m_saSpecificPropNames.size() > 0);	}
	BOOL ObjectInSpecificPropObjectArray( BEMObject* pObj )			{	BOOL bFound = FALSE;
																							for (int i=0; (!bFound && i < (int) m_povSpecificPropObjects.size()); i++)
																								bFound = (m_povSpecificPropObjects[i] == pObj);
																							return bFound;		}
	void AddSpecificPropObject( BEMObject* pObj )						{	if (!ObjectInSpecificPropObjectArray( pObj ))
																								m_povSpecificPropObjects.append( pObj );
																							return;	}
	void RemoveSpecificPropObject( BEMObject* pObj )					{  for (int i=0; i < (int) m_povSpecificPropObjects.size(); i++)
                                                                        if (m_povSpecificPropObjects[i] == pObj)
                                                                        {  m_povSpecificPropObjects.removeAt(i);
                                                                           break;
                                                                        }
																							return;	}
	void ResetSpecificProperties()											{	m_bSpecificPropertiesActive = FALSE;
																							m_saSpecificPropNames.clear();
																							m_povSpecificPropObjects.clear();
																							m_bWriteOnlySpecificProps = FALSE;		}
	void SetSpecificPropertyMode( BOOL bWriteOnlySpecificProps )	{	m_bWriteOnlySpecificProps = bWriteOnlySpecificProps;		}
	BOOL PropertyInSpecificList( BEMProperty* pProp )					{	BOOL bRetVal = FALSE;
																							if (m_bSpecificPropertiesActive && pProp && pProp->getType())
																							{	for (int i=0; (!bRetVal && i < (int) m_saSpecificPropNames.size()); i++)
																									bRetVal = ( (pProp->getType()->getShortName().compare(   m_saSpecificPropNames[i], Qt::CaseInsensitive )==0) ||
																													(pProp->getType()->getDescription().compare( m_saSpecificPropNames[i], Qt::CaseInsensitive )==0) );
																							}
																							return bRetVal;  }
	BEMObject* GetSpecificPropObject( int idx )		{	return ((idx >= 0 && idx < (int) m_povSpecificPropObjects.size()) ? m_povSpecificPropObjects[idx] : NULL);	}
	BOOL SpecificPropertiesActive()						{	return m_bSpecificPropertiesActive;  }
	BOOL WriteOnlySpecificProperties()					{	return m_bWriteOnlySpecificProps;  }
	bool ObjectToBeWritten( int i1Class, int i0ObjIdx );		// SAC 12/16/18 - related to CSE HPWHSIZE feature

private:
   BEMTextIO m_file;              // the file itself
   bool    m_isOpen;            // flag indicating whether or not the file is open
   bool    m_bIsUserInputMode;  // flag indicating whether or not the file is of the input type.
                                // when this flag = TRUE, the file contains only the data specified by the user
                                // when this flag = FALSE, the file contains ALL the data and status stored in the BEM
	int     m_iFileMode;			// SAC 5/22/12 - BEMFM_INPUT / BEMFM_DETAIL / BEMFM_SIM
   bool    m_bWriteLibData;     // flag indicating whether or not to write library data
                                //  (used for writing individual components to the clipboard)
   bool    m_bWriteAssignedComponents;  // flag indicating that all assigned components (other than children) should
                                        // be written prior to writing each component to the file
   int   m_iPastingClassFromClipboard;   // class index of component being pasted from the clipboard
   QStringList m_saComponentNames;   // When Writing:  names of components written to the file (only tracked if
                                     //                m_bWriteAssignedComponents == TRUE in order to prevent the same
                                     //                component from being written to the file more than once
                                     // When Reading: names of all the components which are being renamed in the
                                     //               process of importing them
   QStringList m_saNewComponentNames;  // new names for components which are renamed during the reading process

   long m_lDBIDVersion;  // SAC 9/25/99 - added to enable code to perform conversions enabling adjustments to data stored in previous BEMProc versions
   long m_lVersion;
   int  m_iFileType;   // SAC 8/30/11 - added iFileType argument => BEMFT_Std, BEMFT_CSE, ...
	bool m_bOnlyValidInputs;	// SAC 4/16/14
   bool m_bWritePrevNames;    // enable writing of previous class/property names when writing 2019 project files - SAC 08/06/21 (MFam)

// SAC 1/15/03 - Added member to re-enable output of Undefined data when writing non-user input mode file (backward compatibility)
   bool m_bWriteAllProperties;

   BOOL m_bSupressAllMessageBoxes;  // SAC 4/27/03 - added to prevent MessageBoxes during processing

	BOOL m_bSpecificPropertiesActive;		// SAC 3/22/16 - added to write certain CSE objects w/out certain properties for pre-run, then altered following pre-run
	QStringList m_saSpecificPropNames;
	QVector<BEMObject*> m_povSpecificPropObjects;
	BOOL m_bWriteOnlySpecificProps;
	int m_iPropertyCommentOption;		// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
	int m_iChildIndent;					// SAC 12/5/16 - Indents child objects this number of spaces in relation to its parent
	std::vector<long>* m_plaClsObjIndices;		// SAC 12/14/18 - added to facilitate writing of specific object type/index elements to CSE input files (initially for HPWH sizing runs - HPWHSIZE)
	bool m_bReportInvalidEnums;
};


/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::ObjectToBeWritten( int i1Class, int i0ObjIdx )		// SAC 12/16/18 - related to CSE HPWHSIZE feature
{	bool bRetVal = (m_plaClsObjIndices ? false : true);  // ptr NULL => ALL objects are to be written
	if (!bRetVal)
		for (int i=0; (!bRetVal && i < (int) m_plaClsObjIndices->size()); i++)
		{	long lCls  = m_plaClsObjIndices->at(i) / BEMF_ClassIDMult;
			long l1Obj = m_plaClsObjIndices->at(i) - (lCls * BEMF_ClassIDMult);
			bRetVal = (lCls == i1Class &&
						  (i0ObjIdx < 0 || l1Obj < 1 || l1Obj == (i0ObjIdx+1)));
		}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  CProjectFile()
//
// Purpose ------------------------------------------------------------------
//   Constructor - Opens specified file and throws error if one occurs.
//   
// Arguments ----------------------------------------------------------------
//   QString& fileName     : name of file to open
//   BOOL     bIsInputMode : (default = TRUE) flag indicating whether or not we are opening a User Input file
//   int      fileMode     : (default = load) indicates whether we are reading or writing the project file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CProjectFile::CProjectFile( const char* fileName, int iFileMode /*bool bIsInputMode*/, long lDBIDVersion,
                            long lVersion, int fileMode, bool bWriteAllProperties,
                            BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
									 int iFileType /*=0*/, bool bOnlyValidInputs /*=false*/,   // SAC 8/30/11 - added iFileType argument  // SAC 4/16/14
									 int iPropertyCommentOption /*=0*/, 		// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
									 std::vector<long>* plaClsObjIndices /*=NULL*/, 		// SAC 12/14/18 - added to facilitate writing of specific object type/index elements to CSE input files (initially for HPWH sizing runs - HPWHSIZE)
									 bool bReportInvalidEnums /*=true*/ )
{
   // set some member flags
   m_bIsUserInputMode = (iFileMode == BEMFM_INPUT)/*bIsInputMode*/;
	m_iFileMode = iFileMode;	// SAC 5/22/12 - BEMFM_INPUT / BEMFM_DETAIL / BEMFM_SIM
   m_isOpen = FALSE;
   m_bWriteLibData = FALSE;
   m_bWriteAssignedComponents = FALSE;
   m_iPastingClassFromClipboard = 0;

   m_lDBIDVersion = lDBIDVersion;
   m_lVersion = lVersion;
   m_iFileType = iFileType;   // SAC 8/30/11 - added iFileType argument => BEMFT_Std, BEMFT_CSE, ...
	m_bOnlyValidInputs = bOnlyValidInputs;

   m_bWriteAllProperties = bWriteAllProperties;  // SAC 1/15/03

   m_bSupressAllMessageBoxes = bSupressAllMessageBoxes;  // SAC 4/27/03 - added to prevent MessageBoxes during processing

	m_bSpecificPropertiesActive = FALSE;		// SAC 3/22/16 - added to write certain CSE objects w/out certain properties for pre-run, then altered following pre-run
	m_bWriteOnlySpecificProps = FALSE;
	m_iPropertyCommentOption = iPropertyCommentOption;

	m_iChildIndent = (m_iFileType == BEMFT_CSE ? 3 : 0);		// SAC 12/5/16 - Indents child objects this number of spaces in relation to its parent
	m_plaClsObjIndices = plaClsObjIndices;
	m_bReportInvalidEnums = bReportInvalidEnums;

   std::string sFN = fileName;
   int iLastDotIdx = (int) sFN.rfind('.');
   int iVint19Idx  = (int) sFN.rfind("19");
   m_bWritePrevNames = (iLastDotIdx > 0 && iVint19Idx > iLastDotIdx);    // enable writing of previous class/property names when writing 2019 project files - SAC 08/06/21 (MFam)

   try
   {
      // attempt to open file
      m_isOpen = m_file.Open( fileName, fileMode );
      if ( !m_isOpen )
      {
         QString msg = QString( "Error opening file: %1" ).arg( fileName );
         BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
         if (!m_bSupressAllMessageBoxes)  // SAC 4/27/03
            BEMMessageBox( msg, NULL, 2 /*warning*/ );
      }
   }
//   CATCH( CFileException, error )
//   {
//      QString msg = QString( "Error opening file: %1" ).arg( fileName );
//      BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
//      if (!m_bSupressAllMessageBoxes)  // SAC 4/27/03
//         BEMMessageBox( msg, NULL, 2 /*warning*/ );
//   }
//   END_CATCH
	catch (std::exception& e)
	{
		QString msg = QString( "Error opening file '%1' because: " ).arg( fileName, e.what() );
		BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes );
		if (!m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 2 /*warning*/ );
	}
	catch (...)
	{
		QString msg = QString( "Error opening file: %1" ).arg( fileName );
		BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes );
		if (!m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 2 /*warning*/ );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ~CProjectFile()
//
// Purpose ------------------------------------------------------------------
//   Destructor - closes file if open, then sets open flag to FALSE.
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
CProjectFile::~CProjectFile()
{
   // close file if it is open
   if ( IsOpen() )
   {
//      m_file.Flush();  - added to try to fix a bug but this was not the issue
      m_file.Close();
   }
   m_isOpen = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  IsOpen()
//
// Purpose ------------------------------------------------------------------
//   Return the value of the m_isOpen flag
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   m_isOpen flag value
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::IsOpen()
{ return m_isOpen; }


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ReadNextPropType()
//
// Purpose ------------------------------------------------------------------
//   Reads the next property type in the project file (or '..' if encountered).
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   String containing the next property type or '..' which indicates the end
//   of input for a current building component.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
QString CProjectFile::ReadNextPropType()
{
   // advance past any spaces to the next character
   m_file.Advance();
   
   // if '..' found, then return it, else simply call ReadToken() to read next property type string from file
   if ( m_file.GetChr() == '.' )
   {
      if ( m_file.GetChr() == '.' )
      {
         return QString( ".." );
      }
      m_file.UnGetChr();
   }
   m_file.UnGetChr();

   // '..' not found, so read (and return) next property type string
   return m_file.ReadToken();
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ReadCritDefComment()
//
// Purpose ------------------------------------------------------------------
//   Read a critical default comment from the file.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   The critical default comment string contained in the project file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
QString CProjectFile::ReadCritDefComment()
{
   QString strComment;
   // advance past any spaces to the next character
   m_file.Advance();
   bool done = FALSE;

   while ( !done )
   {
      // if first char is double quote, then read this string into comment
      if ( m_file.GetChr() == '"' )
      {
         m_file.UnGetChr();
         strComment += m_file.ReadString();
      }
      else
      {  // look for comment ending token - if not found then throw an exception
         m_file.UnGetChr();
         QString strEnd = m_file.ReadToken();
         if ( strEnd == szEndComment )
            done = TRUE;
         else
            ;// throw exception
      }
      // advance past any spaces to the next character
      m_file.Advance();
   }

   int loc = strComment.indexOf( '~' );  // Change ~s to newlines
   while ( loc != -1 )
   {
      strComment[loc] = '\n';
      loc = strComment.indexOf( '~' );
   }

   loc = strComment.indexOf( '\'' );  // Change single qoutes to double
   while ( loc != -1 )
   {
      strComment[loc] = '"';
      loc = strComment.indexOf( '\'' );
   }

   return strComment;  // return comment string
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::SkipToEndOfComponent()
{
   // skip to the end of the errant component
   BOOL bDone = FALSE;
   char chr;
   do
   {
      chr = m_file.GetChr();
      while ( (chr != '\"') && (chr != '.') && (chr != ';') )
         chr = m_file.GetChr();

      if (chr == ';')
         m_file.GetLine();
      else if (chr == '\"')
      {  // advance past character string thru closing '"'
         chr = m_file.GetChr();
         while (chr != '\"')
            chr = m_file.GetChr();
      }
      else
      {  // check for second '.'
         chr = m_file.GetChr();
         if (chr == '.')
            bDone = TRUE;
      }
   }
   while (!bDone);
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ()
//
/////////////////////////////////////////////////////////////////////////////
BOOL CProjectFile::NameIsUnique( QString& sObjName, BOOL bCheckLibsOnly, int iBEMProcIdx /*=-1*/ )
{
   BEMObject* pObj = BEMPX_GetComponentByNameQ( sObjName, bCheckLibsOnly, iBEMProcIdx );
   if (pObj)
   {
      QString sOldName = sObjName;
      if (BEMPX_SetObjectCopyName( sObjName, sOldName.toLocal8Bit().constData(), FALSE, iBEMProcIdx ))
      {
         AddToComponentNameList( sOldName );
         AddToNewComponentNameList( sObjName );
         return FALSE;
      }
      else
         assert( FALSE );
   }
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ()
//
/////////////////////////////////////////////////////////////////////////////
BEMObject* CProjectFile::ReturnExistingComponent( int i1Class, QString& sObjName, int iBEMProcIdx /*=-1*/ )
{
   int iError;
   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
   if (iError == 0 && pClass)
   {
      // return NULL if we are NOT pasting from the clipboard
      if (m_iPastingClassFromClipboard == 0)
         return NULL;

      // confirm name uniqueness and return NULL if this component is the one being
      // pasted or if this component has at least one parent class associated with it
      if (m_iPastingClassFromClipboard == i1Class || // SAC 6/13/12 - revised parent/child check as follows, was previously: pClass->m_iaParentType[0] >= 0 ||
			// (pClass->m_iaParentType[0] > 0 || pClass->m_iaParentType[1] >= 0 || pClass->m_iaChildType[0] >= 0) ||   // this parent/child check allows for this component to be a child of Project, as long as no other parent/child relationships exist
			// SAC 8/22/14 - removed trailing check "|| pClass->m_iaChildType[0] >= 0" to fix CBECC-Res GC #354/4 - DHWSys objects copied when objects that reference them are copied
			 (pClass->getParentType(0) > 0 || pClass->getParentType(1) >= 0) ||   // this parent/child check allows for this component to be a child of Project, as long as no other parent/child relationships exist
           pClass->getMaxReferences() > 0)
      {
         // check name for uniqueness
         NameIsUnique( sObjName, FALSE, iBEMProcIdx );
         return NULL;
      }

      // we ARE pasting from the clipboard and the component currently being read is
      // not the main one being pasted and has no parent class => this component is
      // one directly (or indirectly) referenced by the component being pasted.
      // THEREFORE: Don't paste it if it already exists in the project, ruleset or user library.
      BEMObject* pObj = BEMPX_GetComponentByNameQ( sObjName, FALSE, iBEMProcIdx );
      if (pObj)
         return pObj;

      // this referenced component does not exist in either library, so go ahead and read
      // it in once we check for name uniqueness
      NameIsUnique( sObjName, FALSE, iBEMProcIdx );
   }

   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ReadComponent()
//
// Purpose ------------------------------------------------------------------
//   Reads all the data which defines a single building component from the file.
//   
// Arguments ----------------------------------------------------------------
//   BOOL        bCreateObj : (default = TRUE) flag indicating whether or not to create a new component
//   const char* psOnlyProp : (default = NULL) the name of the only property value to read (or NUL => read all properties)
//   
// Return Value -------------------------------------------------------------
//   TRUE if the end-of-file marker is encountered, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BEMObject* CProjectFile::ReadComponent( int& iDBIDSetFailureIdx, bool bCreateObj, const char* psOnlyProp, int iBEMProcIdx,
                                        // SAC 5/12/00 - added following args to enable UI reporting of failed data setting
                                        int iMaxDBIDSetFailures, int* piDBIDSetFailures,
                                        int* piObjIdxSetFailures, QStringList* psaDataSetFailures,   // SAC 7/10/03 - added to facilitate more informative error reporting
                                        BEMStraightMap* pStraightMap,  // SAC 11/14/01 - added another method of mapping old properties to new
                                        // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
                                        BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap, QVector<int>* pivMapCompsCreated )
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( 0 );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return NULL;

   BEMObject* newObject = NULL;
   try
   {
      QString sObjType = m_file.ReadToken();
      // if the end-of-file marker is hit, then bail out
      if (sObjType.compare( szEnd ) != 0)
      {
         BEM_ObjType eObjType = BEMO_User;
         if ( !m_bIsUserInputMode )
         {  // if we're NOT in user input mode, then get the object type from the file
            eObjType = GetObjTypeFromString( m_file.ReadToken() );
            if ( m_file.GetChr() != ':' )
               m_file.ThrowFormatException();
         }

         int i1Class = BEMPX_GetDBComponentID( sObjType.toLocal8Bit().constData() );
         // read the object's name from the file
//         QString sObjName = m_file.ReadString();
// SAC 1/27/12 - code to enable components to be listed in IBD files WITHOUT component names
         QString sObjName;
         if (m_file.NextCharacterOnLine() != '\"')
				BEMPX_GetDefaultComponentName( i1Class, sObjName, iBEMProcIdx );
			else
         	sObjName = m_file.ReadString( FALSE /*bReadPastEOL*/, TRUE /*bAllowMidQuote*/ );		// SAC 8/14/19 - mods to allow for mid-string quotes (Com tic #2986)

         int iError;
         int iObjIdx = -1;

         // check to see if we should simply return a pointer to an existing component
         // (this is only a factor when we are pasting from the clipboard)
         newObject = ReturnExistingComponent( i1Class, sObjName, iBEMProcIdx );
         if (newObject)
         {  // continue reading until we reach the terminating "..", then return
            SkipToEndOfComponent();
         }
         else
         {  
// SAC 10/18/01 - Added code to catch and deal with no longer supported component types
            int iBEMMapGroupID = -1;
            int i1BEMMapGroupNewClasses[] = {0,0,0,0,0};
            if (i1Class <= 0 && pCompMap && pPropMap)
            {
               int iCMIdx = -1;
               while (iBEMMapGroupID < 0 && pCompMap[++iCMIdx].iCompTypeID > 0)  // SAC 3/22/05 - modified logic to handle variety of version cutoffs
               {
                  if (pCompMap[iCMIdx].iVersionCutoff >= m_lVersion && sObjType.compare( pCompMap[iCMIdx].szOldCompType ) == 0)  // SAC 5/1/03 - Switched '<=' to '>='
                  {
                     iBEMMapGroupID = pCompMap[iCMIdx].iCompTypeID;
                     int iCMIdx2 = -1;
                     while (iCMIdx2 < 4 && pCompMap[iCMIdx].szNewCompType[++iCMIdx2] != NULL)
                     {
                        i1BEMMapGroupNewClasses[iCMIdx2] = BEMPX_GetDBComponentID( pCompMap[iCMIdx].szNewCompType[iCMIdx2] );
                        assert( i1BEMMapGroupNewClasses[iCMIdx2] > 0 );
// SAC 10/18/01 - This backward comp mapping stuff assumes that only ONE new component of each replacement type is to be created
                        if (i1BEMMapGroupNewClasses[iCMIdx2] > 0)
                        {
						// SAC 4/21/14 - revise code to enable mapping of properties for MULTIPLE objects of the mapped type
						//			if (BEMPX_GetNumObjects( i1BEMMapGroupNewClasses[iCMIdx2], BEMO_User, iBEMProcIdx ) < 1)
									if (BEMPX_CanCreateAnotherUserObject( i1BEMMapGroupNewClasses[iCMIdx2], 1 /*iNumObjs*/, iBEMProcIdx ))
                           {
                              QString sMapObjName = (iCMIdx2 == 0 ? sObjName : pBEMProc->getClass( i1BEMMapGroupNewClasses[iCMIdx2]-1 )->getLongName());
                              BEMObject* pMapObj = BEMPX_CreateObject( i1BEMMapGroupNewClasses[iCMIdx2], sMapObjName.toLocal8Bit().constData(), NULL, eObjType, TRUE, m_bIsUserInputMode, iBEMProcIdx );
                              assert( pMapObj );
                              if (pivMapCompsCreated)
                                 pivMapCompsCreated->append( i1BEMMapGroupNewClasses[iCMIdx2] );
                              if (pMapObj && newObject == NULL)
                              {
                                 i1Class = i1BEMMapGroupNewClasses[iCMIdx2];
                                 newObject = pMapObj;
					                  iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ), newObject, iBEMProcIdx );	// SAC 4/21/14
                              }
                           }
                           else if (newObject == NULL)
                           {
                              i1Class = i1BEMMapGroupNewClasses[iCMIdx2];
                              newObject = BEMPX_GetObjectByClass( i1Class, iError, 0, BEMO_User, iBEMProcIdx );
				                  iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ), newObject, iBEMProcIdx );   // SAC 4/21/14
                           }
                        }
                        assert( newObject != NULL );
                     }
                  }
               }
            }

// SAC 10/18/01 - Removed "i1OtherClass" stuff as the WinDoorWiz component has been removed
//            int i1OtherClass = i1Class;
//            BEMObject* newOtherObject = NULL;
            if (iBEMMapGroupID < 0)
            {
// SAC 10/19/01 - Added code to prevent re-creation of component already created via the backward compatibility mapping mechanism
               if (bCreateObj && pivMapCompsCreated && pivMapCompsCreated->size() > 0)
               {
                  for (int i=0; (bCreateObj && i<(int) pivMapCompsCreated->size()); i++)
                     bCreateObj = (pivMapCompsCreated->at(i) != i1Class);
               }

               if (bCreateObj)  // create new object
               {
                  newObject = BEMPX_CreateObject( i1Class, sObjName.toLocal8Bit().constData(), NULL, eObjType, TRUE, m_bIsUserInputMode, iBEMProcIdx );
               }
               else
               {  // get a pointer to the object with this name that is already stored in the database
                  newObject = BEMPX_GetObjectByName( i1Class, iError, sObjName.toLocal8Bit().constData(), eObjType, iBEMProcIdx );
                  iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ), newObject, iBEMProcIdx );
               }
            }

            if (newObject)
            {
               long lDBID = -1;
               // read first property type string
               QString sPropType = ReadNextPropType();
               // read through ALL property types, until '..' encountered => end of this object's data
               while ( sPropType != ".." )
               {
                  int i1CurClass = i1Class;
                  if ( sPropType.compare( szCritDefComment, Qt::CaseInsensitive ) == 0 )
                  {  // if the property type string => beginning of a critical default comment, then read and store it
                     // with the LAST property that was read from the file.
									assert( false );		// critical default comments not currently implemented
									m_file.ThrowFormatException();
                  //   if ( lDBID == -1 )
                  //      m_file.ThrowFormatException(); // comment can't be first.
                  //   // advance past any spaces to the next character
                  //   m_file.Advance();
                  //   if ( m_file.GetChr() != '=' )
                  //      m_file.ThrowFormatException(); // missing '='
                  //   QString strComment = ReadCritDefComment();  // read the comment string
                  //   // store the critical default comment into the building database
                  //   BEMPX_AddCriticalDefaultComment( strComment, lDBID, iError, iObjIdx, eObjType, iBEMProcIdx );
                  //   lDBID = -1; // ensures not 2 comments in a row.
                  }
                  else if ( sPropType.compare( szTreeState, Qt::CaseInsensitive ) == 0 )
                  {  // Read in UI tree state parameter
                     // advance past any spaces to the next character ('=')
                     m_file.Advance();
                     if ( m_file.GetChr() != '=' )
                        m_file.ThrowFormatException(); // missing '='
                     m_file.Advance();

                     newObject->setTreeState( (int) m_file.ReadLong() );
                  }
// SAC 11/15/04 - Added code to enable "Parent" to be specified within PD2 component properties
                  else if ( sPropType.compare( "Parent", Qt::CaseInsensitive ) == 0 )
                  {
                     // advance past any spaces to the next character
                     m_file.Advance();
                     if ( m_file.GetChr() != '=' )
                        m_file.ThrowFormatException(); // missing '='

                     //QString strParent = m_file.ReadString( TRUE );  // SAC 6/17/01 - added argument to ALLOW reading beyond carriage return
                     // SAC 8/14/19 - revised to DIS-allow reading beyond carriage return and ALLOW mid-name quotes (Com tic #2986)
                     QString strParent = m_file.ReadString( FALSE /*bReadPastEOL*/, TRUE /*bAllowMidQuote*/ );

                     // post the parent name to BEMProc
                     lDBID = (i1CurClass * BEM_COMP_MULT) + BEM_PARAM0_PARENT;
                     if (BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &strParent,  // BEMP_Str, (void*) strParent.toLocal8Bit().constData(),
                                        BEMO_User, iObjIdx, BEMS_UserDefined, eObjType, FALSE, iBEMProcIdx ) < 0)
                     {  // report error in setting parent component type
                        QString sMsg = QString( "   ERROR - reading file: %1 '%2' Parent" ).arg( sObjType, sObjName );
                        if (!strParent.isEmpty())
                        {
                           sMsg += "  =  ";
                           sMsg += strParent;
                        }
                        BEMPX_WriteLogFile( sMsg, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03

                        // SAC 5/12/00 - added this code to enable UI reporting of failed data setting
                        if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
                        {
                           piDBIDSetFailures[ iDBIDSetFailureIdx ] = lDBID;

                           if (piObjIdxSetFailures)
                              piObjIdxSetFailures[ iDBIDSetFailureIdx ] = (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
                           if (psaDataSetFailures)
                              SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, strParent );

                           iDBIDSetFailureIdx++;
                        }
                     }
                  }
                  else
                  {
                     // the bBracketMode flag indicates which mode this property is reading array data in.
                     // bBracketMode = TRUE => 
                     //     An open square bracket immediately follows the property type string, then following
                     //     the open bracket will be a 1-based array index followed by a close bracket.  The
                     //     data following the '=' will be the value for the single array element.
                     //     i.e.:  PropertyType[2] = 5
                     // bBracketMode = FALSE => 
                     //     NO open square bracket immediately follows the property type string.
                     //     This indicates that the property being read is not an array OR that every array
                     //     element will be defined on this one line (comma separated between '()')
                     //     i.e.:  PropertyType = 5  -or-  PropertyType = ( 5, 4, 3 )
                     BOOL bBracketMode = FALSE;
                     int iArrayIdx = 1;
                     if ( m_file.GetChr() == '[' )
                     {
                        iArrayIdx = (int)m_file.ReadLong();
                        if ( m_file.GetChr() != ']' )
                           m_file.ThrowFormatException(); // missing ']'
                        bBracketMode = TRUE;
                     }

                     // get a pointer to the PropertyType
                     int i1PropTypeIdx = -1;
                     BEMPropertyType* pPropType = NULL;
// SAC 10/18/01 - Added code to catch and deal with no longer supported component types & properties
                     BOOL bPostData = TRUE;
// SAC 2/1/02 - Replaced occurences of i1Class with i1CurClass to prevent i1Class from being reset by property redirections and because i1CurClass is what is referenced below
                     if (iBEMMapGroupID >= 0)
                     {
                        int iPMIdx = -1;
                        while (pPropType == NULL && pPropMap[++iPMIdx].iCompTypeID > 0)  // SAC 3/22/05 - modified logic to handle variety of version cutoffs
                           if ( pPropMap[iPMIdx].iVersionCutoff >= m_lVersion  &&   // SAC 5/1/03 - Switched '<=' to '>='
                                pPropMap[iPMIdx].iCompTypeID == iBEMMapGroupID  &&
                                ( pPropMap[iPMIdx].szOldPropType == NULL  ||  sPropType.compare( pPropMap[iPMIdx].szOldPropType ) == 0 ) )
                           {
                              i1CurClass = BEMPX_GetDBComponentID( pPropMap[iPMIdx].szNewCompType );
                              assert( i1CurClass > 0 );
                              newObject = BEMPX_GetObjectByClass( i1CurClass, iError, -1, BEMO_User, iBEMProcIdx );	// SAC 4/21/14 - switched 3rd arg 0->-1 to grab CURRENT object, not always first
                              assert( newObject );
                              iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx );  // SAC 7/10/03 - Added as it seems like errors could occur without it ???
                              QString sMapPropType = ( pPropMap[iPMIdx].szNewPropType == NULL ? sPropType : pPropMap[iPMIdx].szNewPropType );
                              i1PropTypeIdx = BEMPX_GetPropertyTypeIndexByShortName( i1CurClass, sMapPropType.toLocal8Bit().constData(), iBEMProcIdx );
                              pPropType = BEMPX_GetPropertyType( i1CurClass, i1PropTypeIdx, iBEMProcIdx );
                              assert( pPropType );
                              bPostData = pPropMap[iPMIdx].bPostMappedData;
                           }
                     }
                     else
                     {
                        //i1PropTypeIdx = BEMPX_GetPropertyTypeIndexByShortName( i1CurClass, sPropType );
                        i1PropTypeIdx = BEMPX_GetPropertyTypeIndexByName( i1CurClass, sPropType.toLocal8Bit().constData(), iBEMProcIdx );

// SAC 11/14/01 - Added code to reference new BEMStraightMap array to handle simple property maps within the same component
                        if (i1PropTypeIdx < 1 && pStraightMap)
                        {
                           int iSMIdx = -1;
//                           while (i1PropTypeIdx < 1 && pStraightMap[iSMIdx].szOldPropType != NULL && pStraightMap[++iSMIdx].iVersionCutoff <= m_lVersion)
                           while (i1PropTypeIdx < 1 && pStraightMap[++iSMIdx].szOldPropType != NULL)  // SAC 3/22/05 - modified logic to handle variety of version cutoffs
                              if ( pStraightMap[iSMIdx].iVersionCutoff >= m_lVersion  &&    // SAC 5/1/03 - Switched '<=' to '>='
						//						*pStraightMap[iSMIdx].pi1Class == i1CurClass  &&  sPropType.CompareNoCase( pStraightMap[iSMIdx].szOldPropType ) == 0)  // SAC 1/27/14 - "NoCase" comparison
												sPropType.compare( pStraightMap[iSMIdx].szOldPropType, Qt::CaseInsensitive ) == 0 && BEMPX_GetDBComponentID( pStraightMap[iSMIdx].szClassName ) == i1CurClass )  // SAC 1/27/14 - "NoCase" comparison
                              {
										// SAC 6/1/16 - added code to enable pStraightMap[iSMIdx].szNewPropType to include array indices (inside square brackets)
											QString sNewPropName = pStraightMap[iSMIdx].szNewPropType;
											int iSqrBrackIdx = sNewPropName.indexOf("[");
											if (iSqrBrackIdx > 0)
											{	int iRghIdx = sNewPropName.indexOf("]");		assert( iRghIdx > iSqrBrackIdx+1);
												iArrayIdx = atoi( sNewPropName.mid( iSqrBrackIdx+1, iRghIdx-iSqrBrackIdx-1 ).toLocal8Bit().constData() );
												sNewPropName = sNewPropName.left( iSqrBrackIdx );
											}
											i1PropTypeIdx = BEMPX_GetPropertyTypeIndexByShortName( i1CurClass, sNewPropName.toLocal8Bit().constData(), iBEMProcIdx );
                                 if (i1PropTypeIdx > 0)
                                    bPostData = pStraightMap[iSMIdx].bPostMappedData;
                              }
                        }
                        if ( i1PropTypeIdx > 0 )
                           pPropType = BEMPX_GetPropertyType( i1CurClass, i1PropTypeIdx, iBEMProcIdx );
                     }

							bool bHaveSkippedToNextProperty = false;
                     if (!pPropType)
                     {  QString lastError = QString("component %1 '%2' includes unrecognized property '%3'" ).arg( sObjType, sObjName, sPropType);
	                  	if (m_file.GetLineCount() > 0)	// SAC 6/22/16 - improve error reporting by adding project file line #
	                     	lastError += QString( " on line # %1" ).arg( QString::number(m_file.GetLineCount()) );

						// SAC 6/23/16 - modified to log unrecognized property as a more generic error, rather than throwing exception causing file read to abort
                        if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
                        {	lastError = "   ERROR - reading file: " + lastError;
                        	piDBIDSetFailures[ iDBIDSetFailureIdx ] = i1CurClass;		// lDBID;
                           if (piObjIdxSetFailures)
                              piObjIdxSetFailures[ iDBIDSetFailureIdx ] = (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
                           if (psaDataSetFailures)
                              SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, lastError );
                           iDBIDSetFailureIdx++;
		                     BEMPX_WriteLogFile( lastError, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03

                        // NEXT we have to skip past all data that follows the (bogus) property name, prior to the subsequent property name (or '..')
	                     	// advance past any spaces to the next character ('=')
   		                  m_file.Advance();
         		            if ( m_file.GetChr() != '=' )
               		         m_file.ThrowFormatException(); // missing '='
               		      // following the '=' see if we've got data or an array
		                     m_file.Advance();
		                     char ch = m_file.GetChr();		QString sSkipData;	double dSkipDbl;
		                     if (ch == '(')
		                     {	// we have an array - a series of data elements separated by ',' and ending in ')'
										while (ch != ')')
										{	m_file.Advance();
											ch = m_file.GetChr();
											m_file.UnGetChr();
											if (ch == '"')
		               	      		// skip past char string data
												sSkipData = m_file.ReadString( TRUE /*bReadPastEOL=FALSE*/ );
		                     		else if (ch == '-' || ch == '.' || isdigit( ch ))
		                     			dSkipDbl = m_file.ReadDouble();
		                     		else
												sSkipData = m_file.ReadToken( FALSE /*bAllowLeadingDigit=FALSE*/, FALSE /*bSkipLeadingDelimeters=FALSE*/,
																						FALSE /*bAllowMidHyphen=FALSE*/, TRUE /*bAllowNewLineRead=TRUE*/ );
											m_file.Advance();
											ch = m_file.GetChr();
										}
										m_file.SkipToEndOfLine();
										m_file.GetLine();
		                     }
		                     else
		                     {	m_file.UnGetChr();
		                     	if (ch == '"')
		                     		// skip past char string data
											sSkipData = m_file.ReadString( TRUE );
		                     	else
										{	m_file.SkipToEndOfLine();
											m_file.GetLine();
									}	}
                        	bHaveSkippedToNextProperty = true;
                        }
                        else
                           m_file.ThrowFormatException(lastError.toLocal8Bit().constData());
                     }

							if (!bHaveSkippedToNextProperty)
                     {	// advance past any spaces to the next character ('=')
	                     m_file.Advance();
	                     if ( m_file.GetChr() != '=' )
	                        m_file.ThrowFormatException(); // missing '='
	                     int nValues = pPropType->getNumValues();

	                     // confirm that the next character is '(' if this proerty type is an array and we are not in bracket mode
	                     m_file.Advance();
	                     if ( nValues > 1 && !bBracketMode && m_file.GetChr() != '(' ) // read not called if nVals <1
// SAC 3/22/05 - Modified code to allow multiple array element properties to be written w/out square brackets => set only first array element
	                     {  //m_file.ThrowFormatException(); // missing '('
	                        nValues = 1;
	                        m_file.UnGetChr();
	                     }

	                     BOOL bDone = FALSE;
	                     // read ALL available array elements into properties
	                     for ( int i = 0; (!bDone && i < nValues); i++ )
	                     {
	                        if ( bBracketMode )
	                        {  // bracket mode => single array index already read in
	                           i = iArrayIdx - 1;
	                           bDone = TRUE;
	                        }

	                        BEM_PropertyStatus ePropStat = BEMS_UserDefined;
	                        if ( !m_bIsUserInputMode )
	                        {  // if we are not in user input mode, then read the property status ID from the file
	                           ePropStat = GetStatusFromString( m_file.ReadToken() );
	                           if ( m_file.GetChr() != ':' )
	                              m_file.ThrowFormatException(); // missing ':' following status string

	                           // set ePropstat to Undefined to prevent data from being set if we are
	                           // reading only a particular property for this component
	                           if ( (psOnlyProp != NULL) && (sPropType.compare( psOnlyProp, Qt::CaseInsensitive ) != 0) )
	                              ePropStat = BEMS_Undefined;
	                        }

	                        // Set the lDBID which is used to post the data read into the database
	                        lDBID = BEMPX_GetDBID( i1CurClass, i1PropTypeIdx, (i + 1) );  // SAC 7/18/01
	                        int iSet = 0;

							// SAC 8/13/15 - added code to prevent setting of this property based on BEMDataType:m_iNotInputMode (and m_eCompDataType == BEMD_NotInput...
									QString sErrMsg;
									bool bNotInputError = false;
	                        if (ePropStat != BEMS_Undefined && lDBID > 0 && m_bIsUserInputMode)
	                     //   {	assert( pPropType->m_olDataTypes.GetCount() > i );
								//		POSITION pos = pPropType->m_olDataTypes.FindIndex( i );
								//		BEMDataType* pDT = (BEMDataType*) pPropType->m_olDataTypes.GetAt( pos );		assert( pDT );
								//		if (pDT && pDT->m_eCompDataType == BEMD_NotInput && pDT->m_iNotInputMode != DTNotInp_AllowUIReset)
									{	BEMPropTypeDetails* pDT = pPropType->getPropTypeDetails(i);		assert( pDT );
										if (pDT && pDT->getCompDataType() == BEMD_NotInput && pDT->getNotInputMode() != DTNotInp_AllowUIReset)
										{	ePropStat = BEMS_Undefined;
											bNotInputError = (pDT->getNotInputMode() == DTNotInp_ErrorIfInput);
											if (!pDT->getNotInputMsg().isEmpty())
											{	QString sMsg, sMsgEnd;
												if (nValues > 1)
													sMsgEnd = QString( "[%1]" ).arg( QString::number(i+1) );
												else
													sMsgEnd = "";
												if (bNotInputError)
												{	sMsg = QString( "   Error:  %1  (%2 '%3' %4%5, line: %6, column: %7)" ).arg( pDT->getNotInputMsg(), sObjType, sObjName, sPropType, sMsgEnd, QString::number(m_file.GetLineCount()), QString::number(m_file.GetCharacterIndex()) );
													sErrMsg = sMsg;
												}
												else
													sMsg = QString( "   %1  (%2 '%3' %4%5)" ).arg( pDT->getNotInputMsg(), sObjType, sObjName, sPropType, sMsgEnd );
												BEMPX_WriteLogFile( sMsg, NULL, FALSE, m_bSupressAllMessageBoxes );
									}	}	}

	                        // SAC 10/5/00 - Added code to intercept certain DBID that have been converted from BEMP_Int to BEMP_Sym
	                        int iTempPropType = pPropType->getPropType();

	                        QString sErrantData;  // SAC 7/10/03 - added to facilitate more informative error reporting
	                        switch ( iTempPropType )
	                        {  // read the data and post it to the database
	                           case BEMP_Int : {  long lTemp = m_file.ReadLong();

	                                       //      // SAC 9/25/99 - Conversion of special DATE data from GMT to local time
	                                       //      if (pPropType->m_laObjTypeValue[0] == 1 && m_lVersion >= 2)
	                                       //      {
	                                       //         // Get local delta from GMT
	                                       //         struct _timeb tstruct;
	                                       //         _ftime( &tstruct );
	                                       //         lTemp += (tstruct.timezone * 60);
	                                       //      }

	                                             if (bPostData && ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
	                                             {
	                                                iSet = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lTemp,
	                                                                      BEMO_User, iObjIdx, ePropStat, eObjType, FALSE, iBEMProcIdx );
	                                                if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
	                                                   sErrantData = QString( "%1" ).arg( QString::number(lTemp) );
	                                             }

	                                             // SAC 9/25/99 - added to store version number for possible later reference
	                                             if (lDBID == m_lDBIDVersion)
	                                                m_lVersion = lTemp;

	                                             break;  }
	                           case BEMP_Flt : {  double fTemp = m_file.ReadDouble();
	                                             if (bPostData && ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
	                                             {
	                                                iSet = BEMPX_SetBEMData( lDBID, BEMP_Flt, (void*) &fTemp,
	                                                                      BEMO_User, iObjIdx, ePropStat, eObjType, FALSE, iBEMProcIdx );
	                                                if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
	                                                   sErrantData = QString( "%1" ).arg( QString::number(fTemp) );
	                                             }
	                                             break;  }
	                           case BEMP_Sym :
	                           case BEMP_Str : {  QString sTemp = m_file.ReadString( TRUE );  // SAC 6/17/01 - added argument to ALLOW reading beyond carriage return
	                           						bool bNotSymOrNotNull = (iTempPropType != BEMP_Sym || sTemp.compare("(null)")!=0 ? true : false);	// SAC 4/7/16 - prevent storing enums = "(null)"
	                                             if (bPostData && bNotSymOrNotNull && ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
	                                             {
	               //                                 iSet = BEMPX_SetBEMData( lDBID, BEMP_Str, (void*) sTemp.toLocal8Bit().constData(),
	                                                iSet = BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &sTemp,
	                                                                      BEMO_User, iObjIdx, ePropStat, eObjType, FALSE, iBEMProcIdx );
	                                             	if (iSet < 0 && (!pPropType->getShortName().compare("Ruleset", Qt::CaseInsensitive) || !pPropType->getDescription().compare("Ruleset", Qt::CaseInsensitive)))
	                                             		iSet = 0;	// SAC 11/22/15 - ignore read errors where Ruleset not valid or not found
	                                                if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
	                                                   sErrantData = sTemp;
	                                             }
	                                             break;  }
	                           case BEMP_Obj : { // SAC 8/14/19 - mods to allow for mid-string quotes (Com tic #2986)   // SAC 8/15/19 - further mods to fix bug in retrieving array of object references (Com tic #2986) 
	                           						QString sTemp = m_file.ReadString( FALSE /*bReadPastEOL*/, TRUE /*bAllowMidQuote*/, (nValues > 1) /*bMayBeArray*/ );
	                                             // iError;
	                                             if (bPostData && ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
	                                             {
	                                                BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, iObjIdx, eObjType, iBEMProcIdx );
	                                                if (pProp)
	                                                {
	                                                   // if we are pasting from the clipboard, then substitute names
	                                                   // in the event this component naem was changed during the read
	                                                   if (m_iPastingClassFromClipboard > 0)
	                                                      SubstituteComponentName( sTemp );
                                                
	                                                   pProp->setDataStatus( ePropStat );
	                                                   pProp->setString( sTemp );
	                                                   pProp->setObj(  NULL );
	                                                }
	                                             }
	                                             break;  }
	                           default : 
	                              m_file.ThrowFormatException(); // should never happen
	                              break;
	                        }

	                        if (iSet < 0 || bNotInputError)
	                        {  // throw error message if data not successfully posted to database
	                        	if (sErrMsg.isEmpty())
	                           {	sErrMsg = "   ERROR - reading file: ";
	                           	sErrMsg += sObjType;
	                           	sErrMsg += " '";
	                           	sErrMsg += sObjName;
	                           	sErrMsg += "' property ";
	                           	sErrMsg += sPropType;
	                           	if (nValues > 1)
	                           	   sErrMsg += QString( "[%1]" ).arg( QString::number(i+1) );
	                           	if (!sErrantData.isEmpty())  // SAC 7/10/03 - Added echo of new sErrantData string
	                           	{
	                           	   sErrMsg += "  =  '";
	                           	   sErrMsg += sErrantData;
	                           	   sErrMsg += "'";
	                           	}
	                           	if (m_file.GetLineCount() > 0)	// SAC 6/22/16 - improve error reporting by adding project file line #
												sErrMsg += QString( " on line # %1" ).arg( QString::number(m_file.GetLineCount()) );
	                           	if (bNotInputError)
	                           		sErrMsg += "   (property classified as 'NotInput')";
	                           	BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
	                           }

	                           // SAC 5/12/00 - added this code to enable UI reporting of failed data setting
	                           if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
	                           {
	                              piDBIDSetFailures[ iDBIDSetFailureIdx ] = lDBID;

// SAC 7/10/03 - added to facilitate more informative error reporting
	                              if (piObjIdxSetFailures)
	                                 piObjIdxSetFailures[ iDBIDSetFailureIdx ] = (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
	                              if (psaDataSetFailures)
	                                 SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrantData );

	                              iDBIDSetFailureIdx++;  // SAC 7/10/03 - moved down here from within brackets of setting piDBIDSetFailures[] to preserve value for reference in other arrays
	                           }
	                        }

	                        if ( nValues > 1 && !bBracketMode ) 
	                        {   
	                           // advance past any spaces to the next character
	                           m_file.Advance();
	                           char cNext = m_file.GetChr();
	                           if (cNext == ')')  // if next character is ')', then we are done reading array elements
	                              bDone = TRUE;
	                           else if (cNext != ',')
	                              m_file.ThrowFormatException(); // missing ',' separating array elements
	                        }
	                     }
							}
                  }
                  sPropType = ReadNextPropType();
               }
            }
            else
            {  // => error creating object
               QString sError = "   ERROR - unable to create ";
               sError += sObjType;
               sError += " component '";
               sError += sObjName;
               sError += "'.";

               // try to figure out why
               int iError;
               BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
               if ( (iError < 0) || (pClass == NULL) )
               {
                  sError += " Invalid component type '";
                  sError += sObjType;
                  sError += "'.";
               }
               else
               {
                  int iNumDefined = BEMPX_GetNumObjects( i1Class, BEMO_User, iBEMProcIdx );
                  if (pClass->getMaxDefinable() > 0 && iNumDefined >= pClass->getMaxDefinable())  // SAC 1/23/12 - enable getMaxDefinable()==0 to enable unlimited creations
                     sError += QString( " The maximum number of components of this type (%1) are already created." ).arg( QString::number(pClass->getMaxDefinable()) );
                  // else not sure, so just leave it at that
               }
               // notify user of error
               BEMPX_WriteLogFile( sError, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
               if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
               {  piDBIDSetFailures[ iDBIDSetFailureIdx ] = 1000;
	               if (piObjIdxSetFailures)
	                  piObjIdxSetFailures[ iDBIDSetFailureIdx ] = 1000;  // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
	               if (psaDataSetFailures)
	                  SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sError );
	               iDBIDSetFailureIdx++;  // SAC 7/10/03 - moved down here from within brackets of setting piDBIDSetFailures[] to preserve value for reference in other arrays
	            }
               //if (!m_bSupressAllMessageBoxes)  // SAC 4/27/03
               //   BEMMessageBox( sError, NULL, 2 /*warning*/ );

               // skip to the end of the errant component
               SkipToEndOfComponent();
            }
         }
      }
   }
//   CATCH ( CTextioException, except )
//   {                             
//      if ( except->m_cause == CTextioException::endOfFile )
//         ; // If the last thing was a ".." then read is complete
//      else
//      {
//         if (BEMPX_WriteLogFile( except->m_strError, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
//            BEMMessageBox( except->m_strError, NULL, 3 /*error*/ );
//         except->m_bNotified = TRUE; //prevent subsequent catch from notifying
//         THROW_LAST();
//      }
//   }
//   END_CATCH
	catch (BEMTextioException& te)
	{
		if ( te.m_cause == BEMTextioException::endOfFile )
			; // we're done, no problem
		else
		{	QString msg = QString( "Error reading component from file because '%1'" ).arg( te.what() );
			if (te.m_line > 0 && te.m_column > 0)
				msg += QString( ", line %1, column %2" ).arg( QString::number(te.m_line), QString::number(te.m_column) );	// SAC 10/31/19
			if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
				BEMMessageBox( msg, NULL, 3 /*error*/ );
			throw std::runtime_error(boost::str(boost::format("Error reading component from file because '%1") %
																	te.m_strError.toLocal8Bit().constData() ));
		}
	}
	catch (...)
	{
		QString msg = "Error reading component from file";
		if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 3 /*error*/ );
		throw std::runtime_error( "Error reading component from file" );
	}

   return newObject;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read and store the contents of a project file.
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
// SAC 4/27/03 - Modified function to return BOOL
BOOL CProjectFile::Read( int iBEMProcIdx,
                         // SAC 5/12/00 - added following args to enable UI reporting of failed data setting
                         int iMaxDBIDSetFailures, int* piDBIDSetFailures,
                         int* piObjIdxSetFailures, QStringList* psaDataSetFailures,   // SAC 7/10/03 - added to facilitate more informative error reporting
                         BEMStraightMap* pStraightMap,  // SAC 11/14/01 - added another method of mapping old properties to new
                         // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
                         BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap,
								 BOOL bLogDurations /*=FALSE*/ )  // SAC 10/24/13 - added duration logging
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( 0 );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return FALSE;

	ptime t1(microsec_clock::local_time());  // SAC 10/24/13
   BOOL bRetVal = TRUE;
   try
   {

//// DEBUGGING
//QString sDbgMsg = QString( "CProjectFile::Read(...) / eBEMProc.m_iBEMProcType = %1" ).arg( QString::number(eBEMProc.m_iBEMProcType) );
//BEMMessageBox( sDbgMsg, "Debugging", 3 /*error*/ );
//// DEBUGGING

      if (pBEMProc->getType() == BEMT_CBECC)
      {  // first read ruleset filename out of very top of project file
         QString sRulesetFilename;
         ReadRulesetFilename( sRulesetFilename );
      }

      BEMObject* pNewObj = NULL;
      // read all component definitions contained in the file until the end-of-file marker is found
      int iDBIDSetFailureIdx = 0;   // SAC 5/12/00
      QVector<int> ivMapCompsCreated;
      bool bLastErrorBogusCompType = false;	// SAC 6/29/16 - added check to ensure that file reading continues on past an unrecognized object
      do
      {	int iLastSetFailIdx = iDBIDSetFailureIdx;
         pNewObj = ReadComponent( iDBIDSetFailureIdx, TRUE, NULL, iBEMProcIdx, iMaxDBIDSetFailures, piDBIDSetFailures, piObjIdxSetFailures,
                                  psaDataSetFailures, pStraightMap, pCompMap, pPropMap, &ivMapCompsCreated );
      	bLastErrorBogusCompType = (pNewObj == NULL && iMaxDBIDSetFailures > 0 && iDBIDSetFailureIdx > 0 && iDBIDSetFailureIdx > iLastSetFailIdx &&
      										piDBIDSetFailures[iDBIDSetFailureIdx-1] == 1000 && piObjIdxSetFailures[iDBIDSetFailureIdx-1] == 1000);
      } while (pNewObj != NULL || bLastErrorBogusCompType);

		if (bLogDurations)  // SAC 10/24/13 - added duration logging
		{	ptime t2(microsec_clock::local_time());
			time_duration td = t2-t1;
			QString sLogMsg = QString( "         CProjectFile::Read() - elapsed time for initial file parsing: %1" ).arg( QString::number(((double) td.total_microseconds()) / 1000000.0, 'f', 3) );  // -or- %s -> to_simple_string(td).c_str() );
		   BEMPX_WriteLogFile( sLogMsg );
			t1 = t2;
		}

      // resolve all object references - this is necessary because all object assignments are
      // originally read and stored simply as character string names of the referenced objects.
      // This function resolves those object names to actual object pointers.
      // This object resolving cannot happen during the reading process, since an object
      // can be assigned PRIOR to its definition in the file.
      int iNumUnresolvedRefs = BEMP_ResolveAllReferences( BEMO_User, NULL, TRUE, iBEMProcIdx, m_bSupressAllMessageBoxes );  // SAC 4/27/03
      if (iNumUnresolvedRefs > 0)  // SAC 4/27/03
         bRetVal = FALSE;

		if (bLogDurations)  // SAC 10/24/13 - added duration logging
		{	ptime t2(microsec_clock::local_time());
			time_duration td = t2-t1;
			QString sLogMsg = QString( "         CProjectFile::Read() - elapsed time for BEMP_ResolveAllReferences(): %1" ).arg( QString::number(((double) td.total_microseconds()) / 1000000.0, 'f', 3) );  // -or- %s -> to_simple_string(td).c_str() );
		   BEMPX_WriteLogFile( sLogMsg );
		}
   }
//   CATCH ( CTextioException, except )
//   {                             
//      if ( except->m_cause == CTextioException::endOfFile )
//         ; // If the last thing was a ".." then read is complete
//      else
//      {
//         bRetVal = FALSE;  // SAC 4/27/03
//         if (!except->m_bNotified)
//         {  if (BEMPX_WriteLogFile( except->m_strError, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
//               BEMMessageBox( except->m_strError, NULL, 3 /*error*/ );
//         }
//      }
//   }
//   END_CATCH
	catch (BEMTextioException& te)
	{
		if ( te.m_cause == BEMTextioException::endOfFile )
			; // we're done, no problem
		else
		{	bRetVal = FALSE;
			if (!te.m_bNotified)
			{	QString msg = QString( "Error reading building model input file because '%1'" ).arg( te.what() );
				if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
					BEMMessageBox( msg, NULL, 3 /*error*/ );
		}	}
	}
	catch (...)
	{	bRetVal = FALSE;
		QString msg = "Error reading building model input file";
		if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 3 /*error*/ );
	}

   return bRetVal;  // SAC 4/27/03
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ReadResults()
//
// Purpose ------------------------------------------------------------------
//   Read only the results out of the project file.
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
void CProjectFile::ReadResults( int iBEMProcIdx )
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( 0 );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return;

   try
   {
      if (pBEMProc->getType() == BEMT_CBECC)
      {  // first read ruleset filename out of very top of project file
         QString sRulesetFilename;
         ReadRulesetFilename( sRulesetFilename );
      }

      // read only the Project:FinalResults property out of the first project file component
      int iJunk = 0;
      BEMObject* pNewObj = ReadComponent( iJunk, FALSE, "FinalResult", iBEMProcIdx );

      if (pNewObj != NULL)
         pNewObj = ReadComponent( iJunk, FALSE, NULL, iBEMProcIdx );  // Proposed Results

      if (pNewObj != NULL)
         pNewObj = ReadComponent( iJunk, FALSE, NULL, iBEMProcIdx );  // Budget Results
   }
//   CATCH ( CTextioException, except )
//   {                             
//      if ( except->m_cause == CTextioException::endOfFile )
//         ; // If the last thing was a ".." then read is complete
//      else
//      {
//         BEMPX_WriteLogFile( except->m_strError, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
//         if (!m_bSupressAllMessageBoxes)  // SAC 4/27/03
//            BEMMessageBox( except->m_strError, NULL, 3 /*error*/ );
//         THROW_LAST();
//      }
//   }
//   END_CATCH
	catch (BEMTextioException& te)
	{
		if ( te.m_cause == BEMTextioException::endOfFile )
			; // we're done, no problem
		else
		{	QString msg = QString( "Error reading analysis results from file because '%1'" ).arg( te.what() );
			if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
				BEMMessageBox( msg, NULL, 3 /*error*/ );
			throw std::runtime_error(boost::str(boost::format("Error reading analysis results from file because '%1") %
																	te.m_strError.toLocal8Bit().constData() ));
		}
	}
	catch (...)
	{	QString msg = "Error reading analysis results from file";
		if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 3 /*error*/ );
		throw std::runtime_error( "Error reading analysis results from file" );
	}
}


/////////////////////////////////////////////////////////////////////////////
// ReadRulesetFilename()
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::ReadRulesetFilename( QString& sRulesetFilename )
{
   sRulesetFilename.clear();
   try
   {
      QString sObjType = m_file.ReadToken();

//// DEBUGGING
//QString sDbgMsg = QString( "CProjectFile::ReadRulesetFilename(...) / first token read = '%1' (vs. szRulesetFN: '%2')" ).arg( sObjType, szRulesetFN );
//BEMMessageBox( sDbgMsg, "Debugging", 3 /*error*/ );
//// DEBUGGING

      // confirm first token is ruleset filename
      if (sObjType.compare( szRulesetFN ) == 0)
      {
         // read the ruleset filename from the file
         sRulesetFilename = m_file.ReadString();

//// DEBUGGING
//QString sDbgMsg = QString( "CProjectFile::ReadRulesetFilename(...) / sRulesetFilename = '%1'" ).arg( sRulesetFilename );
//BEMMessageBox( sDbgMsg, "Debugging", 3 /*error*/ );
//// DEBUGGING

         // set this string to be the default which will be installed
         // into the next created 'Project' component
         BEMPX_SetRulesetFilename( sRulesetFilename.toLocal8Bit().constData() );
      }
   }
//   CATCH ( CTextioException, except )
//   {                             
//      if ( except->m_cause == CTextioException::endOfFile )
//         ; // If the last thing was a ".." then read is complete
//      else
//      {
//         BEMPX_WriteLogFile( except->m_strError, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
//         if (!m_bSupressAllMessageBoxes)  // SAC 4/27/03
//            BEMMessageBox( except->m_strError, NULL, 3 /*error*/ );
//         THROW_LAST();
//      }
//   }
//   END_CATCH
	catch (BEMTextioException& te)
	{
		if ( te.m_cause == BEMTextioException::endOfFile )
			; // we're done, no problem
		else
		{	QString msg = QString( "Error reading ruleset filename from file because '%1'" ).arg( te.what() );
			if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
				BEMMessageBox( msg, NULL, 3 /*error*/ );
			throw std::runtime_error(boost::str(boost::format("Error reading ruleset filename from file because '%1") %
																	te.m_strError.toLocal8Bit().constData() ));
		}
	}
	catch (...)
	{	QString msg = "Error reading ruleset filename from file";
		if (BEMPX_WriteLogFile( msg, NULL, FALSE, m_bSupressAllMessageBoxes ) && !m_bSupressAllMessageBoxes)
			BEMMessageBox( msg, NULL, 3 /*error*/ );
		throw std::runtime_error( "Error reading ruleset filename from file" );
	}
}


///////////////////////////////////////////////////////////////////////////////
//// SetRulesetFilename()
///////////////////////////////////////////////////////////////////////////////
//BOOL CProjectFile::SetRulesetFilename( QString sRulesetFilename )
//{
//   long lDBID = BEMPX_GetDatabaseID( "Proj:RuleFile" );
//   if ( (lDBID > 0) &&
//        (BEMPX_SetBEMData( lDBID, BEMP_Str, (void*) ((const char*) sRulesetFilename)) >= 0) )
//      return TRUE;
//   return FALSE;
//}


/////////////////////////////////////////////////////////////////////////////
// WriteRulesetFilename()
/////////////////////////////////////////////////////////////////////////////
void RetrieveRulesetFilename( QString& sRulesetFilename, int iBEMProcIdx )
{	sRulesetFilename.clear();
   long lDBID = BEMPX_GetDatabaseID( "Proj:RuleFile" );
   if (lDBID <= 0)
		lDBID = BEMPX_GetDatabaseID( "Project:RuleFile" );   // try alternative spelling
   if (lDBID > 0)
   {
      int iStatus = BEMPX_GetDataStatus( lDBID, -1 /*iOccur*/, BEMO_User /*BEM_ObjType*/, iBEMProcIdx );
      if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
      {
         int iError, iSpecialVal;
      //   void* pData = BEMPX_GetBEMData( lDBID, iDataType, iSpecialVal, iError, -1 /*iOccur*/,
		//												BEMO_User /*eObjType*/, FALSE /*bReturnParentObject*/, iBEMProcIdx );
      //   if ( (iError >= 0) && (pData != NULL) )
      //      sRulesetFilename = (const char*) *((QString*) pData);
			QString str = BEMPX_GetString( lDBID, iSpecialVal, iError, -1, BEMO_User, iBEMProcIdx );
			if (!str.isEmpty())
				sRulesetFilename = str;
      }
   }
   assert (sRulesetFilename.length() > 0);
}

void CProjectFile::WriteRulesetFilename( int iBEMProcIdx /*=-1*/ )
{
   QString sRulesetFilename;
	RetrieveRulesetFilename( sRulesetFilename, iBEMProcIdx );

   // Write:  'RulesetFilename   "filename"'
   QString sTokenString = szRulesetFN;
   int length = sTokenString.length();
   m_file.WriteToken( sTokenString.toLocal8Bit().constData(), length );
   m_file.WriteToken( "   ", 3 );
   // write object name to file
   m_file.WriteQuotedString( sRulesetFilename.toLocal8Bit().constData(), sRulesetFilename.length() );
   m_file.NewLine();
   m_file.NewLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  GetStatusFromString()
//
// Purpose ------------------------------------------------------------------
//   Convert a character string to its property status identifier.
//   
// Arguments ----------------------------------------------------------------
//   QString sStatusString  : the character string describing a property's status
//   
// Return Value -------------------------------------------------------------
//   The BEMS_NumTypes flag value if the status is not found, otherwise it
//   returns the BEM_PropertyStatus matching the argument string.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static BEM_PropertyStatus GetStatusFromString( QString sStatusString )
{      
   for ( int i = 0; i < BEMS_NumTypes; i++ )
   {  // return the BEM_PropertyStatus of the first matching property status string
      if ( sStatusString.compare( szaPropertyStatusString[ i ], Qt::CaseInsensitive ) == 0 )
         return (BEM_PropertyStatus)i;
   }
   return BEMS_NumTypes;
}
       

/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  GetObjTypeFromString()
//
// Purpose ------------------------------------------------------------------
//   Convert a character string to its object type identifier.
//   
// Arguments ----------------------------------------------------------------
//   QString sObjTypeString  : the character string describing an object's type
//   
// Return Value -------------------------------------------------------------
//   The BEMO_NumTypes flag value if the object type is not found, otherwise it
//   returns the BEM_ObjectType matching the argument string.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static BEM_ObjType GetObjTypeFromString( QString sObjTypeString )
{
   for ( int i = 0; i < BEMO_NumTypes; i++ )
   {  // return the BEM_ObjectType of the first matching object type string
      if ( sObjTypeString.compare( szaObjTypeString[ i ], Qt::CaseInsensitive ) == 0 )
         return (BEM_ObjType)i;
   }
   return BEMO_NumTypes;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  StatusRequiresWrite()
//
// Purpose ------------------------------------------------------------------
//   Determine whether or not a property should be written to the project file
//   based solely on that property's status flag (the function argument).
//   
// Arguments ----------------------------------------------------------------
//   int  iStatus       : the status identifier of the property in question.
//   
// Return Value -------------------------------------------------------------
//   TRUE if we are writing a non-user input file (since ALL properties must
//   be wwritten) or if the property has been defined by the user.
//   FALSE only if we are writing a user input file and the status argument
//   indicates that the property has not been defined by the user.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::StatusRequiresWrite( BEMProperty* pProp, bool bWritePrimaryDefaultData /*=false*/ )		// SAC 6/10/15 - CBECC issue 1061
{
//   if ( !m_bIsUserInputMode )
// SAC 2/11/02 - Altered code to prevent output of Undefined data when writing non-user input mode file
// SAC 1/15/03 - Altered code to re-enable output of Undefined data when writing non-user input mode file (backward compatibility)
//   if ( !m_bIsUserInputMode && (m_bWriteAllProperties || iStatus != BEMS_Undefined) )
//      return TRUE;
//   return ( (iStatus == BEMS_UserDefined) ||
//            (m_bWriteLibData && (iStatus == BEMS_RuleLibrary ||
//                                 iStatus == BEMS_UserLibrary) ) );
	assert( (pProp && pProp->getType()) );
	if (pProp==NULL || pProp->getType()==NULL)
		return false;

	bool bRetVal = true;
	if (m_iFileMode == BEMFM_SIM)  // SAC 5/22/12 - added logic to further specify when properties are to be written to SIMULATION export files
	{	switch (pProp->getType()->getWriteSimulationFlag())
		{	case  0 :  bRetVal = false;   break;
			case  2 :  bRetVal = (pProp->getDataStatus() >= BEMS_UserDefault && pProp->getDataStatus() <= BEMS_UserDefined);   break;
			default :  bRetVal = (pProp->getDataStatus() != BEMS_Undefined);   break;
		}
		if (bRetVal && pProp->getType()->getPropType() == BEMP_Sym && pProp->getInt() <= 0)
			bRetVal = false;   // SAC 2/28/13 - prevent writing of symbol data to SIM file if symbol value is <= 0 (to prevent export of things like "- specify -")
	}
	else
	{  bRetVal = false;
		if (bWritePrimaryDefaultData &&																	// SAC 6/10/15 - CBECC issue 1061
					pProp->getDataStatus() >= BEMS_ProgDefault && pProp->getDataStatus() <= BEMS_UserDefault &&
					pProp->getType() && pProp->getType()->getNumPropTypeDetails() >= pProp->get1ArrayIdx())
	//	{	POSITION pos = pProp->getType()->m_olDataTypes.FindIndex( pProp->get1ArrayIdx()-1 );			assert( pos );
	//		if (pos)
	//		{	BEMDataType* pDT = (BEMDataType*) pProp->getType()->m_olDataTypes.GetAt( pos );		assert( pDT );
	//			if (pDT && pDT->m_bPrimary)
	//	   		bRetVal = true;
	//	}	}
		{	BEMPropTypeDetails* pDT = pProp->getType()->getPropTypeDetails( pProp->get1ArrayIdx()-1 );		assert( pDT );
			if (pDT && pDT->isPrimary())
				bRetVal = true;
		}

		if (!bRetVal)
		{	if ( !m_bIsUserInputMode && (m_bWriteAllProperties || pProp->getDataStatus() != BEMS_Undefined) )
		      bRetVal = TRUE;
			else if (m_bIsUserInputMode && m_bWriteAllProperties && pProp->getDataStatus() != BEMS_Undefined)  // SAC 11/11/13 - revised use: write ALL defined data when in Input mode
	   	   bRetVal = TRUE;
			else
		   	bRetVal = ( (pProp->getDataStatus() == BEMS_UserDefined) ||
								((m_iFileType == BEMFT_CSE || BEMPX_IsHPXML( m_iFileType ) || BEMPX_IsCF1RXML( m_iFileType ) || BEMPX_IsNRCCXML( m_iFileType ) || BEMPX_IsRESNETXML( m_iFileType )) && pProp->getDataStatus() > 0) ||					// SAC 1/3/13	// SAC 12/2/15   // SAC 5/20/20
	   		            (m_bWriteLibData && (pProp->getDataStatus() == BEMS_RuleLibrary ||
	   	   	                              pProp->getDataStatus() == BEMS_UserLibrary) ) );
	   }
	}
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  MustWriteProperty()
//
// Purpose ------------------------------------------------------------------
//   Determine whether or not a property should be written to the project file.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject*   pObj  : object who's property is being checked
//   BEMProperty* pProp : pointer to the property in question
//   POSITION     pos   : position of this property within the object's property list
//   
// Return Value -------------------------------------------------------------
//   TRUE if this proerty should be written to the output file, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   For now, if ANY element of the PropertyType array requires writing,
//   we will write the ENTIRE array to the output project file.
//   
/////////////////////////////////////////////////////////////////////////////
bool CSE_IsCommandProperty( QString& sPropName )
{
	int iLastCharToCheck = sPropName.length()-1 - (sPropName.right(2).compare("_x") == 0 ? 2 : 0);
	for (int i=1; i <= iLastCharToCheck; i++)
	{	if (!sPropName[i].isUpper())
			return false;
	}
	return true;
}

bool CProjectFile::MustWriteProperty( BEMObject* pObj, BEMProperty* pProp, int iProp, bool bWritePrimaryDefaultData /*=false*/ )  // SAC 1/22/02 - final argument POSITION pos -> int iProp	// SAC 6/10/15 - CBECC issue 1061
{
 	bool bRetVal = false;

   if (m_iFileType == BEMFT_CSE)  // SAC 8/30/11
	{
//	   bRetVal = ( pProp->getType() && !pProp->getType()->getShortName().isEmpty() && islower( pProp->getType()->getShortName()[0] ) &&
//		            pProp->getDataStatus() > BEMS_Undefined );
	   bRetVal = ( pProp->getType() && !pProp->getType()->getShortName().isEmpty() && pProp->getDataStatus() > BEMS_Undefined &&
					   (pProp->getType()->getShortName()[0].isLower() || CSE_IsCommandProperty( pProp->getType()->getShortName() )) );
	}
	else if (BEMPX_IsHPXML( m_iFileType ))		// SAC 12/2/15
	{
	   bRetVal = ( pProp->getType() && !pProp->getType()->getShortName().isEmpty() && pProp->getDataStatus() > BEMS_Undefined &&
					   pProp->getType()->getShortName()[0].isLower() );
	}
	else
	{
// SAC 4/16/14 - if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
		if (m_iFileMode == BEMFM_INPUT && m_bOnlyValidInputs && pProp && pProp->getType() && pObj && pObj->getClass())
		{	int iCompDT = BEMPX_GetCompDataType( BEMPX_GetDBID( pObj->getClass()->get1BEMClassIdx(), pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() ) );			assert( iCompDT >= 0 );
			if (iCompDT >= BEMD_NotInput)
				return false;
		}

	   // first check to see if the property status (or file mode) dictates that we must output the property
   	bRetVal = StatusRequiresWrite( pProp, bWritePrimaryDefaultData );

   	// If the status and mode doesn't require a property to be written, then we need to
   	// check to confirm that any array elements of the same property type following this one
   	// do require output, in which case this one must also be output.
   	if (!bRetVal)
   	{
      	int iNumProps = pProp->getType()->getNumValues();
      	// check for this property being one of an array of properties of a single property type
      	if (iNumProps > 1)
      	{
         	iProp++;
         	// loop over all following properties in this array until one is found to require output
         	while (iProp < (int) pObj->getPropertiesSize() && !bRetVal && iNumProps > 1)
         	{
         	   pProp = pObj->getProperty(iProp);
        	   	if (pProp != NULL)
        	   	   bRetVal = StatusRequiresWrite( pProp, bWritePrimaryDefaultData );
        	   	else
        	   	{  assert( FALSE );
        	   	}
   	         iProp++;
   	         iNumProps--;
   	      }
   	   }
   	}
	}

	// SAC 3/23/16 - mods to handle SpecificProperty checking and object tracking
	if (bRetVal && SpecificPropertiesActive())
	{	// property must be written BUT first we need to check for whether this is OK based on SpecificProperty writing mode
		if (PropertyInSpecificList( pProp ))
		{	// this property should normally be written AND it is in the list of SpecificProperties
			if (WriteOnlySpecificProperties())
			{	// do nothing - go ahead and write this property
			}
			else
			{	// revise return value to PREVENT writing this proeprty AND add this object to the group that SpecificProperties were excluded from
				bRetVal = FALSE;
				AddSpecificPropObject( pObj );
		}	}
		else
		{	// SpecificProperty checking is active but this property is not in the list
			if (WriteOnlySpecificProperties())
			{	// this property not in SpecificProperty list and we are only writing those properties in that list, so DON'T write this property
				bRetVal = FALSE;
			}
			// else  - this property should normally be written, we are checking for SpecificProperties - but in a mode where we are writing all properties except those in the list
			//				(and since this property is not in the list) - do nothing here - continue to return TRUE
	}	}

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  UseParenArrayFormat()
//
// Purpose ------------------------------------------------------------------
//   Determine whether or not the 'Paren' format for writing an array is
//   required for a particular property.  The Paren format cannot be used if
//   any of the array elements has a critical default comment assigned to it
//   or if any of the array elements is not user defined.
//   The 'Paren' format is desired because it saves space, storing an entire
//   array of values on a single line vs. the bracket format which outputs
//   only one array element per line.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject*   pObj  : object who's property is being checked
//   BEMProperty* pProp : pointer to the property in question
//   POSITION     pos   : position of this property within the object's property list
//   
// Return Value -------------------------------------------------------------
//   FALSE if the property identified by the arguments is in an array and one
//   or more array elements has a critical default comment assigned to it or
//   has a status other than User Defined.  Else, returns TRUE indicating that
//   the Paren array format is acceptable for output of this property.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::UseParenArrayFormat( BEMObject* pObj, BEMProperty* pProp, int iProp )  // SAC 1/22/02 - final argument POSITION pos -> int iProp
{
   int iNumLeft = pProp->getType()->getNumValues();
   // loop over all properties in array, returning FALSE if any found w/ CritDefComment or not user defined
   while ( (iNumLeft > 0) && (iProp < pObj->getPropertiesSize()) )
   {
      pProp = pObj->getProperty(iProp);
      //if ( pProp->m_iCritDefIdx > 0 || ((m_iFileType == BEMFT_CSE ||  BEMPX_IsHPXML( m_iFileType )) && pProp->getDataStatus() == BEMS_Undefined  ) ||   // SAC 9/12/16 - critical default comments not implemented
      if ( ((m_iFileType == BEMFT_CSE ||  BEMPX_IsHPXML( m_iFileType ) ||  BEMPX_IsCF1RXML( m_iFileType ) ||  BEMPX_IsNRCCXML( m_iFileType ) ||  BEMPX_IsRESNETXML( m_iFileType )) && pProp->getDataStatus() == BEMS_Undefined  ) ||   // SAC 8/9/12 - added logic to allow CSE properties to be rule defined (just not undefined)	// SAC 12/2/15   // SAC 5/20/20
		     ( m_iFileType != BEMFT_CSE && !BEMPX_IsHPXML( m_iFileType ) && !BEMPX_IsCF1RXML( m_iFileType ) && !BEMPX_IsNRCCXML( m_iFileType ) && !BEMPX_IsRESNETXML( m_iFileType )  && pProp->getDataStatus() != BEMS_UserDefined) )
         return FALSE;
      iProp++;
      iNumLeft--;
   }
   return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteCritDefComment()
//
// Purpose ------------------------------------------------------------------
//   Writes a critical default comment to the project file.
//   
// Arguments ----------------------------------------------------------------
//   const char* szComment  : critical default comment string
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
const int iCommentWrapLength = 60;
void CProjectFile::WriteCritDefComment( const char* szComment )
{
   m_file.WriteToken( "   ", 3 );
   QString temp = szCritDefComment;
   m_file.WriteToken( temp.toLocal8Bit().constData(), temp.length() );
   m_file.WriteToken( " = ", 3 );

   QString tempStr = szComment;

   int loc = tempStr.indexOf( '\n' ); // Change newlines to ~s
   while ( loc != -1 )
   {
      tempStr[loc] = '~';
      loc = tempStr.indexOf( '\n' ); // Change newlines to ~s
   }

   loc = tempStr.indexOf( '"' ); // Change double quotes to single
   while ( loc != -1 )
   {
      tempStr[loc] = '\'';
      loc = tempStr.indexOf( '"' ); // Change double quotes to single
   }

   int line = 0;
   // write string using however many lines is required to prevent lines longer than the desired length
   while ( tempStr.length() > 0 )
   {
      QString writeStr = tempStr.left( iCommentWrapLength );
      int iCount = tempStr.length() - iCommentWrapLength > -1 ? 
                            tempStr.length() - iCommentWrapLength : 0;

      tempStr = tempStr.right( iCount );
      if ( line > 0 )
         m_file.WriteToken( " ", temp.length() + 6 );
      m_file.WriteString( writeStr.toLocal8Bit().constData(), writeStr.length() + 2 );
      m_file.NewLine();
      line++;
   }
   m_file.WriteToken( "  ", 4 );
   temp = szEndComment;
   m_file.WriteToken( temp.toLocal8Bit().constData(), temp.length() );
   m_file.NewLine();
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  PropertyToString()
//
// Purpose ------------------------------------------------------------------
//   Convert a property value to a character string for output to a project file.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject*   pObj  : object who's property is being converted to a character string
//   BEMProperty* pProp : property who's value is being converted to a character string
//   QString&     sData : QString to populate with character string
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////

void FloatToString_NoExpNotation( QString& string, double fNum )
{
   string = QString( "%1" ).arg( QString::number(fNum, 'f') );
   int nRtOfDec = (string.indexOf('.') < 0 ? 0 : string.length() - string.indexOf('.') - 1);
	if (nRtOfDec > 0)
	{	int iStrLen = string.length();
		int iNumTrailingZeroes = 0;
		while (string[ iStrLen-1 - iNumTrailingZeroes ] == '0')
			iNumTrailingZeroes++;
		if (iNumTrailingZeroes > 0)
		{	if (string[ iStrLen-1 - iNumTrailingZeroes ] == '.')
				iNumTrailingZeroes++;
			string = string.left( iStrLen - iNumTrailingZeroes );
		}
	}
}

static char szNone[] = "- none -";
void CProjectFile::PropertyToString( BEMObject* pObj, BEMProperty* pProp, QString& sData, int iBEMProcIdx, BOOL bOnlyFromCurrentSymDepSet /*=TRUE*/ )
{
   // get the data type of this property
   int iDataType = pProp->getType()->getPropType();
   if ( (iDataType == BEMP_Int) || (iDataType == BEMP_Sym) )
   {  // integer or symbolic data => stored in database as integer
      if (iDataType == BEMP_Int)
      {
         long lTemp = pProp->getInt();

         // SAC 9/25/99 - Conversion of special DATE data from local time to GMT
         if (pProp->getType()->getObjTypeValue(0) == 1)
         {
            // Get local delta from GMT
            struct _timeb tstruct;
#pragma warning(disable : 4996)
            _ftime( &tstruct );
#pragma warning(default : 4996)
            lTemp -= (tstruct.timezone * 60);
         }

         // integer => simple format
         sData = QString( "%1" ).arg( QString::number(lTemp) );
      }
      else // if (iDataType == BEMP_Sym)
      {  // symbol => convert integer value to symbol string and enclose in double quotes
	// SAC 9/23/16 - kludge to replcate MFC behavior where blank symbol strings are written to project file as "(null)"
      	QString qsSym = GetSymbolStringFromPtrs( pProp->getInt(), pObj, pProp, iBEMProcIdx, bOnlyFromCurrentSymDepSet );
      	if (qsSym.isEmpty())
      		qsSym = "(null)";

         if (m_bIsUserInputMode)
            sData = QString( "\"%1\"" ).arg( qsSym );
         else
            sData = QString( "\"%1\"  (%2)" ).arg( qsSym, QString::number(pProp->getInt()) );
      }
   }
   else if (iDataType == BEMP_Flt)
   {  // float => simple format
		if (m_iFileType == BEMFT_CSE || BEMPX_IsHPXML( m_iFileType ) || BEMPX_IsCF1RXML( m_iFileType ) || BEMPX_IsNRCCXML( m_iFileType ) || BEMPX_IsRESNETXML( m_iFileType ))  // SAC 4/11/12 - ensure exponential format NOT used for outputting float data		// SAC 12/2/15   // SAC 5/20/20
			FloatToString_NoExpNotation( sData, pProp->getDouble() );
		else
      	sData = QString( "%1" ).arg( QString::number(pProp->getDouble()) );
   }
   else if (iDataType == BEMP_Str)
   {  // string => simply enclose in double quotes
      sData = pProp->getString();
		if (m_iFileType != BEMFT_CSE || pProp->getType()->getShortName().right(2).compare("_x") != 0)
      {	sData.remove( QChar('"') );
      	sData = QString( "\"%1\"" ).arg( sData );
		}
   }
   else if (iDataType == BEMP_Obj)
   {  // object
      BEMObject* pRefObj = pProp->getObj();
      if (pRefObj != NULL)
         // if object pointer valid, enclose referenced object in double quotes
         sData = QString( "\"%1\"" ).arg( pRefObj->getName() );
      else if (StatusRequiresWrite( pProp ))
         // if object pointer NOT valid but we must output this property, then output "- none -"
         sData = QString( "\"%1\"" ).arg( szNone );
      else  // else don't output property
         sData.clear();
   }
   else
   {
      assert( FALSE );
   }
}

/////////////////////////////////////////////////////////////////////////////

// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
void ReportInvalidEnumerationWrite( BEMObject* pObj, BEMProperty* pProp, int iBEMProcIdx, bool bWritePrevNames /*=false*/ )
{	QString sMsg;
	long lDBID = BEMPX_GetDBID( pObj->getClass()->get1BEMClassIdx(), pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() );
	int iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx );
	QString sOldSym = BEMPX_GetSymbolString( pProp->getInt(), lDBID, iOccur, pObj->getObjectType(), iBEMProcIdx, FALSE /*bOnlyFromCurrentSymDepSet*/ );
   QString qsClsName = (bWritePrevNames && pObj->getClass()->getNumPreviousNames() > 0 ? pObj->getClass()->getPreviousName(0) : pObj->getClass()->getShortName());    // SAC 08/06/21 (MFam)
	QString sArrayInfo;
	if (pProp->getType()->getNumValues() > 1)
		sArrayInfo = QString( "[%1]" ).arg( QString::number(pProp->get1ArrayIdx()) );
	if (sOldSym.isEmpty())
		sMsg = QString( "Error writing enumeration property for %1 '%2', property %3%4" ).arg( qsClsName, pObj->getName(), pProp->getType()->getShortName(), sArrayInfo );
	else
		sMsg = QString( "Error writing enumeration property for %1 '%2', property %3%4 (previously '%5' (?))" ).arg( qsClsName, pObj->getName(), pProp->getType()->getShortName(), sArrayInfo, sOldSym );
   BEMPX_WriteLogFile( sMsg, NULL, FALSE, TRUE /*bSupressAllMessageBoxes*/ );
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteBracketPropertyArray()
//
// Purpose ------------------------------------------------------------------
//   Write a property array in bracket mode => one element per line.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject*   pObj  : object who's property is being written
//   BEMProperty* pProp : pointer to the property being written
//   POSITION&    pos   : position of this property within the object's property list
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteBracketPropertyArray( BEMObject* pObj, BEMProperty* pProp, int& iProp, int iBEMProcIdx /*=-1*/,
																bool bWritePrimaryDefaultData /*=false*/, int iIndentSpcs /*=0*/ )  // SAC 1/22/02 - final argument POSITION& pos -> int& iProp		// SAC 6/8/15 - CBECC issue 1061
{
   // Write array as list of the format "PROP[n] = VALUE" with comments as required
   QString sPropType = pProp->getType()->getShortName();
	if (pProp && m_iFileType == BEMFT_CSE && sPropType.right(2).compare("_x") == 0)  // SAC 1/3/13
		sPropType = sPropType.left( sPropType.length()-2 );
   QString sData;
   //BOOL bDataAlreadyWritten = FALSE;
   int iCount = 1;
	bool bIsCSECommandProperty = ( m_iFileType == BEMFT_CSE && CSE_IsCommandProperty( sPropType ) );  // SAC 1/3/13
   // loop over array elements
   while ( (iCount <= pProp->getType()->getNumValues()) && (iProp < (int) pObj->getPropertiesSize()) )
   {
      pProp = pObj->getProperty(iProp);

      // only write property if we must
      if ( StatusRequiresWrite( pProp, bWritePrimaryDefaultData ) )
      {
         // convert property value to string
         PropertyToString( pObj, pProp, sData, iBEMProcIdx );
			if (sData.length() > 0 && m_bIsUserInputMode && pProp->getType()->getPropType() == BEMP_Sym &&
				 sData.indexOf("(null)") == 1 && !m_bReportInvalidEnums)	// SAC 6/8/19
	         PropertyToString( pObj, pProp, sData, iBEMProcIdx, FALSE /*bOnlyFromCurrentSymDepSet*/ );		// find enumeration string outside current SymDepList

         // if property string not zero length, then write it
         if (sData.length() > 0 && (!m_bIsUserInputMode || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
         {
            // write out property type followed by array element in square brackets
            QString sCount, sLine;
            sCount = QString( "%1" ).arg( QString::number(iCount) );
				if (bIsCSECommandProperty)  // SAC 1/3/13 - for commands within CSE objects, don't write array index OR '=' sign
            	sLine = QString( "%1%2 " ).arg( " ", 3+iIndentSpcs ).arg( sPropType ); 
				else
            	sLine = QString( "%1%2[%3] = " ).arg( " ", 3+iIndentSpcs ).arg( sPropType, sCount ); 

            if ( !m_bIsUserInputMode )
            {  // if we're not in user input mode, then we must write the status string prior to the property's value
               if ( pProp->getDataStatus() >= BEMS_NumTypes )
                  assert( FALSE );
               QString sStatus = szaPropertyStatusString[ (int)(pProp->getDataStatus()) ];

               sLine += sStatus + ": ";
            }
            // write property value string
            sLine += sData;
            m_file.WriteToken( sLine.toLocal8Bit().constData(), sLine.length() );
            m_file.NewLine();
         }
  	      else if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1 && m_bReportInvalidEnums)		// SAC 5/20/19
	      	// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
				ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, m_bWritePrevNames );

         // if this property has a critical default comment, then write it now
         //if ( pProp->m_iCritDefIdx > 0 )
         //   WriteCritDefComment( BEMPX_GetCriticalDefaultCommentFromIndex( pProp->m_iCritDefIdx, iBEMProcIdx ) );
      }
      iCount++;
      // get next property if this is not the last one of this property type
      if ( iCount <= pProp->getType()->getNumValues() )  // SAC 1/22/02
         iProp++;
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteParenPropertyArray()
//
// Purpose ------------------------------------------------------------------
//   Write a property array in parenthesis mode => entire array on one line (if it fits).
//   
// Arguments ----------------------------------------------------------------
//   BEMObject*   pObj  : object who's property is being written
//   BEMProperty* pProp : pointer to the property being written
//   POSITION&    pos   : position of this property within the object's property list
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteParenPropertyArray( BEMObject* pObj, BEMProperty* pProp, int& iProp, int iBEMProcIdx, int iIndentSpcs )  // SAC 1/22/02 - final argument POSITION& pos -> int& iProp
{
   // Write array as list of the format "PROP = ( VALUE1, VALUE2, ... )" with no comments
   //  -or- for CSE input files:  PROP = VAL1, VAL2, VAL3;      - SAC 05/21/22
   int iCount = 0;
   QString sPropType = pProp->getType()->getShortName();
   int iColStart = 3 + sPropType.length() + 4 + iIndentSpcs;
   QString sLine;
   if (m_iFileType != BEMFT_CSE)    // SAC 05/21/22
   {  m_file.WriteToken( "( ", 2 );
      iColStart += 2;
   }

   // loop over all properties in array   
   while ( (iCount < pProp->getType()->getNumValues()) && (iProp < (int) pObj->getPropertiesSize()) )
   {
      pProp = pObj->getProperty(iProp);

      QString sData;
      // convert this property's value to a string
      PropertyToString( pObj, pProp, sData, iBEMProcIdx );
		if (sData.length() > 0 && m_bIsUserInputMode && pProp->getType()->getPropType() == BEMP_Sym &&
			 sData.indexOf("(null)") == 1 && !m_bReportInvalidEnums)	// SAC 6/8/19
         PropertyToString( pObj, pProp, sData, iBEMProcIdx, FALSE /*bOnlyFromCurrentSymDepSet*/ );		// find enumeration string outside current SymDepList

      // if property string not zero length, then write it
      if (sData.length() > 0 && (!m_bIsUserInputMode || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
      {         
         // separate this value from the previous one
         if ( sLine.length() > 0 )
            sLine += ", ";
         // if this value will fit on the line, then add it to the output string
         if ((sData.length() + sLine.length() + iColStart + 4) < MAX_COLUMN)
            sLine += sData;
         else
         {  // this value won't fit on the same line, so write the current line and add this data to the next line
            m_file.WriteToken( sLine.toLocal8Bit().constData(), sLine.length() );
            m_file.NewLine();
            
            m_file.WriteToken( " ", iColStart );
            sLine = sData;
         }
      }
      else 
      {	assert( FALSE );	
			if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1 && m_bReportInvalidEnums)		// SAC 5/20/19
				// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
				ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, m_bWritePrevNames );
		}
      iCount++;
      if ( iCount < pProp->getType()->getNumValues() )
         iProp++;
   }
   // write final line of data to file
   m_file.WriteToken( sLine.toLocal8Bit().constData(), sLine.length() );

   if (m_iFileType == BEMFT_CSE)    // SAC 05/21/22
   {  m_file.WriteToken( ";", 1 );
		if (m_iPropertyCommentOption == 1)
		{	bool bWrtDescrip = (!pProp->getType()->getDescription().isEmpty() &&
										pProp->getType()->getDescription().compare( pProp->getType()->getShortName(), Qt::CaseInsensitive )!=0);
			if (!pProp->getType()->getUnitsLabel().isEmpty() || bWrtDescrip)
				WriteComment( (bWrtDescrip ? pProp->getType()->getDescription() : ""), pProp->getType()->getUnitsLabel(), 40, 4 );
		}
      m_file.NewLine();
   }
   else if ( iCount == pProp->getType()->getNumValues() )
   {  // write closing paren if necessary
      m_file.WriteToken( " )", 2 );
      m_file.NewLine();
   }
}


void CProjectFile::WriteComment( QString sDescrip, QString sUnits, int iStartChr, int iWhiteSpc )
{
	QString sPropComment;
	if (!sUnits.isEmpty() && !sDescrip.isEmpty())
		sPropComment = QString( "%1, %2" ).arg( sDescrip, sUnits );
	else if (!sUnits.isEmpty())
		sPropComment = sUnits;
	else if (!sDescrip.isEmpty())
		sPropComment = sDescrip;
	if (!sPropComment.isEmpty())
	{	int iAddSpaces = iWhiteSpc;
		if (m_file.GetCharacterIndex() < (iStartChr - iWhiteSpc))
			iAddSpaces += iStartChr - iWhiteSpc - m_file.GetCharacterIndex();
		QString sComChrs = (m_iFileType == BEMFT_CSE ? "//" : ";");
		QString sPropComment2 = QString( "%1%2 %3" ).arg( " ", iAddSpaces ).arg( sComChrs, sPropComment );
		m_file.WriteToken( sPropComment2.toLocal8Bit().constData(), sPropComment2.length() );
}	}


/////////////////////////////////////////////////////////////////////////////

#define  MAX_CSE_NAMELENGTH  63		// SAC 6/1/18 (Com tic #2452)

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteProperties()
//
// Purpose ------------------------------------------------------------------
//   Write all the properties for a particular obejct to the project file.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj  : a pointer to the object to write the properties of.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteProperties( BEMObject* pObj, int iBEMProcIdx /*=-1*/, bool bWritePrimaryDefaultData /*=false*/, 		// SAC 6/8/15 - CBECC issue 1061
   								bool bSkipWritingComponentName /*=false*/, int iIndentSpcs /*=0*/, 	   // SAC 3/23/16 - added to enable re-write of "ALTER"ed objects (related to SpecificProperty tracking/writing)
                           bool bWriteOnlyCSEExpressionProperties /*=false*/ )   // workaround for CSE object COPY bug requiring re-write of expressions - SAC 05/19/21
{
   int length;
	BOOL bAbortObjectWrite = FALSE;  // SAC 1/19/13
   QString qsClsName = (m_bWritePrevNames && pObj->getClass()->getNumPreviousNames() > 0 ? pObj->getClass()->getPreviousName(0) : pObj->getClass()->getShortName());    // SAC 08/06/21 (MFam)
   if (!bSkipWritingComponentName && (m_iFileType != BEMFT_CSE || qsClsName.compare("cseTOP") != 0))  // SAC 3/15/12 - prevent writing of "TOP" component type
	{   // Write:  "<Class Name>   <Object Name>"
//	   length = ((QString)pObj->getClass()->m_lpszShortName).length();
	   length = qsClsName.length();
		QString sObjType = qsClsName;
		if (m_iFileType == BEMFT_CSE)
		{	assert( sObjType.indexOf( "cse" ) == 0 );
			length-=3;
			sObjType = sObjType.right( length );
		}
		if (iIndentSpcs > 0)
			sObjType = QString( "%1%2" ).arg( " ", iIndentSpcs ).arg( sObjType );
		sObjType += "   ";  // SAC 1/19/13 - don't write anything to file until we are certain we have a valid object name
	   //m_file.WriteToken( sObjType, length );
	   //m_file.WriteToken( "   ", 3 );
	   if ( !m_bIsUserInputMode )
	   {  // add object type to output file if we are not in user input mode
	      if ( pObj->getObjectType() >= BEMO_NumTypes )
	      {  assert( FALSE );
			}
			else
	      {																						// char* sType = szaObjTypeString[ (int)(pObj->getObjectType()) ];
	      	sObjType += szaObjTypeString[ (int)(pObj->getObjectType()) ];		// m_file.WriteToken( sType, strlen( sType ) );
	      	sObjType += ": ";																// m_file.WriteToken( ": ", 2 );
			}
	   }
	
	   if (m_iFileType == BEMFT_CSE && pObj->getName().length() > MAX_CSE_NAMELENGTH)   // SAC 8/30/11    // SAC 2/18/12 - updated name len limit from 15 to 63
		{	bAbortObjectWrite = TRUE;	// SAC 1/19/13 - added code to ABORT CSE writing of objects w/ names tool long for CSE to handle
			sObjType = "ERROR: CSE object name too long:  " + sObjType;
			sObjType += pObj->getName();
			BEMPX_WriteLogFile( sObjType, NULL, FALSE, m_bSupressAllMessageBoxes );  // SAC 4/27/03
	// ??? not sure if we should log this as a ruleset error or not ???
			BEMPX_AddRulesetError( sObjType.toLocal8Bit().constData() );
			sObjType = "// " + sObjType;
			m_file.WriteToken( sObjType.toLocal8Bit().constData(), sObjType.length() );
		   m_file.NewLine();
		}
		else
	   {  m_file.WriteToken( sObjType.toLocal8Bit().constData(), sObjType.length() );
			// write object name to file
	   	m_file.WriteQuotedString( pObj->getName().toLocal8Bit().constData(), pObj->getName().length() );
		}
	   m_file.NewLine();
	}

	if (!bAbortObjectWrite)
	{
	// SAC 3/25/16 - moved into WriteComponent() so that the current object is logged BEFORE its assigned objects are written (Com tic #628)
	//	// add this component to the list of written components only if m_bWriteAssignedComponents==TRUE
   //	if (m_bWriteAssignedComponents)
   //	   AddToComponentNameList( pObj->getName() );

	   if (m_iFileType == BEMFT_CSE)		// SAC 7/2/15 - added code to export '#include ...' statement when writing CSE files
		{	long lDBID_IncFilePropName = ((pObj == NULL || pObj->getClass() == NULL) ? 0 :
														BEMPX_GetDatabaseID( "IncludeFile", pObj->getClass()->get1BEMClassIdx() ));
			int iObjIdx = ((lDBID_IncFilePropName < 1 || pObj == NULL || pObj->getClass() == NULL) ? -1 :
														BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx ));
			QString sIncFile;									assert( (lDBID_IncFilePropName < 1 || iObjIdx >= 0) );
			if (lDBID_IncFilePropName > 0 && iObjIdx >= 0 &&
					BEMPX_GetString( lDBID_IncFilePropName, sIncFile, FALSE, 0, -1, iObjIdx, BEMO_User, NULL, 0, iBEMProcIdx ) && !sIncFile.isEmpty())
			{	QString sProjFN = m_file.FileName();
				QString sFullIncPathFile = sProjFN.left( sProjFN.lastIndexOf('\\') + 1 );
				sFullIncPathFile += sIncFile;
				if (FileExists( sFullIncPathFile.toLocal8Bit().constData() ))
				{	sProjFN = QString( "#include \"%1\"" ).arg( sIncFile );
					m_file.WriteToken( sProjFN.toLocal8Bit().constData(), sProjFN.length() );
				   m_file.NewLine();
			}	}
		}

   	// Write UI tree state as the first property (if it is not the default value)
   	QString sIndent = QString( "%1" ).arg( " ", 3+iIndentSpcs );
   	if (pObj->getTreeState() != DEFAULT_TREE_STATE && m_iFileType != BEMFT_CSE)   // SAC 8/30/11
   	{
   	   m_file.WriteToken( sIndent.toLocal8Bit().constData(), sIndent.length() );
   	   //m_file.WriteToken( "   ", 3 );
   	   m_file.WriteToken( szTreeState, (int) strlen(szTreeState) );
   	   m_file.WriteToken( " = ", 3 );
   	   QString sTemp;
   	   sTemp = QString( "%1" ).arg( QString::number(pObj->getTreeState()) );
   	   m_file.WriteToken( sTemp.toLocal8Bit().constData(), sTemp.length() );
   	   m_file.NewLine();
   	}
   	
   	// Write Properties in the form: "   <PropType Name> = <Property Value>"
   	for (int iProp=0; iProp < pObj->getPropertiesSize(); iProp++)
   	{
   	   BEMProperty* pProp = pObj->getProperty(iProp);

   	   QString sPropType = pProp->getType()->getShortName();
         bool bContinueWritingProp = (!bWriteOnlyCSEExpressionProperties ||      // workaround for CSE object COPY bug requiring re-write of expressions - SAC 05/19/21
                                      m_iFileType != BEMFT_CSE || (sPropType.right(2).compare("_x") == 0 &&
                                                                   sPropType.indexOf("wsDayUse") < 0));
			if (pProp && m_iFileType == BEMFT_CSE && sPropType.right(2).compare("_x") == 0)
				sPropType = sPropType.left( sPropType.length()-2 );
			if (pProp && m_iFileType == BEMFT_CSE && sPropType.left(6).compare("alter_") == 0)	// SAC 12/4/19 - remove pre-pended 'alter_' from property name written to CSE input
				sPropType = sPropType.right( sPropType.length()-6 );

   	   // if property valid and should be written
   	   if ( bContinueWritingProp && pProp != NULL && MustWriteProperty( pObj, pProp, iProp/*pos*/, bWritePrimaryDefaultData ) )  // SAC 1/22/02
   	   {
   	      // if pProp IS NOT array, just write it out
   	      if (pProp->getType()->getNumValues() == 1)
   	      {
   	         QString sData;
   	         PropertyToString( pObj, pProp, sData, iBEMProcIdx );
					if (sData.length() > 0 && m_bIsUserInputMode && pProp->getType()->getPropType() == BEMP_Sym &&
						 sData.indexOf("(null)") == 1 && !m_bReportInvalidEnums)	// SAC 6/8/19
	         		PropertyToString( pObj, pProp, sData, iBEMProcIdx, FALSE /*bOnlyFromCurrentSymDepSet*/ );		// find enumeration string outside current SymDepList

   	         if (sData.length() > 0 && (!m_bIsUserInputMode || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// prevent writing enums = "(null)"
   	         {
   	   			m_file.WriteToken( sIndent.toLocal8Bit().constData(), sIndent.length() );
	   	         //m_file.WriteToken( "   ", 3 );
   		         m_file.WriteToken( sPropType.toLocal8Bit().constData(), sPropType.length() );
						if (m_iFileType == BEMFT_CSE && sPropType.compare("like", Qt::CaseInsensitive)==0)  // SAC 4/20/12 - special case for CSE "like" property - can't use '='
	   	         	m_file.WriteToken( " ", 1 );
						else
	   	         	m_file.WriteToken( " = ", 3 );
   	
   	            if ( !m_bIsUserInputMode )
   	            {
   	               if ( pProp->getDataStatus() == BEMS_NumTypes )
   	                  assert( FALSE );
   	               char* sStatus = szaPropertyStatusString[ (int)(pProp->getDataStatus()) ];
   	               m_file.WriteToken( sStatus, (int) strlen(sStatus) );
   	               m_file.WriteToken( ": ", 2 );
   	            }

						// SAC 2/24/17 - special case for writing PolyLp vertices to CSE input when CSE property references a PolyLp object
						if (pProp->getType()->getNumValues() == 1 && m_iFileType == BEMFT_CSE && pProp->getType()->getPropType() == BEMP_Obj &&
							 pProp->getObj() && !pProp->getObj()->getClass()->getShortName().compare("PolyLp"))
						{	// loop over PolyLp CartesianPt children and write them to file in special CSE Vertex format
							int iPLObjIdx = BEMPX_GetObjectIndex( pProp->getObj()->getClass(), pProp->getObj() );  // int iBEMProcIdx=-1 );
							int iCartPtClassID = BEMPX_GetDBComponentID( "CartesianPt" );					assert( iCartPtClassID > 0 );
							long lCartPtCoordDBID = BEMPX_GetDatabaseID( "Coord", iCartPtClassID );		assert( lCartPtCoordDBID > 0 );
							int iPLError;		BEM_ObjType ePLObjType = BEMO_User;		double fPLCoords[3];
							int iNumCartPts = (int) BEMPX_GetNumChildren( pProp->getType()->getObj1ClassIdx(0), iPLObjIdx, BEMO_User, iCartPtClassID );
							for (int iCPIdx=1; iCPIdx <= iNumCartPts; iCPIdx++)
							{	int iCartPtObjIdx = BEMPX_GetChildObjectIndex( pProp->getType()->getObj1ClassIdx(0), iCartPtClassID, iPLError, ePLObjType, iCPIdx, iPLObjIdx );		assert( iCartPtObjIdx >= 0 );
								if (iCartPtObjIdx >= 0)
								{	int iNumCoords = BEMPX_GetFloatArray( lCartPtCoordDBID, fPLCoords, 3, 0, BEMP_Flt, iCartPtObjIdx );			assert( iNumCoords == 3 );
									if (iNumCoords == 3)
									{	QString sXYZ;
										if (iCPIdx < iNumCartPts)
											sXYZ = QString( "%1,%2,%3, " ).arg( QString::number(fPLCoords[0]), QString::number(fPLCoords[1]), QString::number(fPLCoords[2]) );
										else
											sXYZ = QString( "%1,%2,%3"   ).arg( QString::number(fPLCoords[0]), QString::number(fPLCoords[1]), QString::number(fPLCoords[2]) );
				   	   			m_file.WriteToken( sXYZ.toLocal8Bit().constData(), sXYZ.length() );
				   	   }	}	}
						}
						else
   	            	m_file.WriteToken( sData.toLocal8Bit().constData(), sData.length() );

					// SAC 12/5/16 - include comments for output properties
						if (m_iPropertyCommentOption == 1)
						{	bool bWrtDescrip = (!pProp->getType()->getDescription().isEmpty() &&
														pProp->getType()->getDescription().compare( pProp->getType()->getShortName(), Qt::CaseInsensitive )!=0);
							if (!pProp->getType()->getUnitsLabel().isEmpty() || bWrtDescrip)
								WriteComment( (bWrtDescrip ? pProp->getType()->getDescription() : ""), pProp->getType()->getUnitsLabel(), 40, 4 );
						}

   	            m_file.NewLine();
   	            //if ( pProp->m_iCritDefIdx > 0 )
   	            //   WriteCritDefComment( BEMPX_GetCriticalDefaultCommentFromIndex( pProp->m_iCritDefIdx, iBEMProcIdx ) );
   	         }
	   	      else if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1 && m_bReportInvalidEnums)		// SAC 5/20/19
   		      	// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
						ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, m_bWritePrevNames );
   	         else
   	         {  assert( FALSE );
					}
   	      }
   	      else  // pProp IS array
   	      {
   	         if ( m_bIsUserInputMode && UseParenArrayFormat( pObj, pProp, iProp/*pos*/ ) )  // SAC 1/22/02
   	         {
   	            //QString sPropType = pProp->getType()->getShortName();
   	            m_file.WriteToken( sIndent.toLocal8Bit().constData(), sIndent.length() );
   	   			//m_file.WriteToken( "   ", 3 );
   	            m_file.WriteToken( sPropType.toLocal8Bit().constData(), sPropType.length() );
   	            m_file.WriteToken( " = ", 3 );
   	            WriteParenPropertyArray( pObj, pProp, iProp/*pos*/, iBEMProcIdx, iIndentSpcs );  // SAC 1/22/02
   	         }
   	         else if (m_iFileType == BEMFT_CSE && pProp->getType()->getNumValues() == 24 &&   // SAC 8/9/12 - special case for CSE hourly profiles that can be written as just a single value
					         pProp->getDataStatus() > BEMS_Undefined)
					{	BEMProperty* pPropNext = pObj->getProperty(iProp+1);
						if (pPropNext->getDataStatus() == BEMS_Undefined)
						{  // write this property as if it is a single property 
   	         		m_file.WriteToken( sIndent.toLocal8Bit().constData(), sIndent.length() );
   	   				//m_file.WriteToken( "   ", 3 );
   	         		m_file.WriteToken( sPropType.toLocal8Bit().constData(), sPropType.length() );
   	         		m_file.WriteToken( " = ", 3 );
   	         		QString sData;
   	         		PropertyToString( pObj, pProp, sData, iBEMProcIdx );
   	         		if (sData.length() > 0)
   	         		{  m_file.WriteToken( sData.toLocal8Bit().constData(), sData.length() );
   	         		   m_file.NewLine();
   	         		}
   	         		else
   	         		{  assert( FALSE );
							}
						}
						else
						{	assert( FALSE );  // situation where first two array elements are defined but at least one subsequent one is not!
						}
   	
			         iProp += (pProp->getType()->getNumValues()-1);
   	   		}
   	         else  
   	            WriteBracketPropertyArray( pObj, pProp, iProp/*pos*/, iBEMProcIdx, bWritePrimaryDefaultData, iIndentSpcs );  // SAC 1/22/02
   	      }
   	   }
   	   else if (pProp == NULL)
   	   {
   	      assert( FALSE );
   	   }
   	   else  // must skip over entire property (which may have multiple elements)
   	   {
    	      iProp += (pProp->getType()->getNumValues()-1);
   	   }
   	}

   	// End of writing properties
		if (m_iFileType != BEMFT_CSE)  // SAC 8/30/11
		{	QString sEnd = QString( "%1.." ).arg( " ", 3+iIndentSpcs );
		   m_file.WriteToken( sEnd.toLocal8Bit().constData(), sEnd.length() );
		   //m_file.WriteToken( "   ..", 5 );
   		m_file.NewLine();
		}
		// SAC 1/29/20 - KLUDGE to force end/close of ExportFile, since CSE likes this to be parent to EXPORT but can't in BEMBase since not allowed to create parent EXPORTFILE for primary CSV output file
		else if (qsClsName.indexOf("cseEXPORTFILE")==0)
		{	m_file.WriteToken( "   endEXPORTFILE", 16 );
			m_file.NewLine();
		}
   	
   	m_file.NewLine();
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteAssignedComponents()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteAssignedComponents( BEMObject* pObj, int iBEMProcIdx /*=-1*/, bool bWritePrimaryDefaultData /*=false*/, int iIndentSpcs /*=0*/ )		// SAC 6/8/15 - CBECC issue 1061
{
   // Search through all properties for each assigned component
   for (int iProp=0; iProp < pObj->getPropertiesSize(); iProp++)
   {
      BEMProperty* pProp = pObj->getProperty(iProp);

      // if property valid and should be written
      if ( (pProp != NULL) && pProp->getType() && (pProp->getType()->getPropType() == BEMP_Obj) && (pProp->getObj() != NULL) &&
           MustWriteProperty( pObj, pProp, iProp/*pos*/, bWritePrimaryDefaultData ) &&  // SAC 1/22/02
           !InComponentNameList( pProp->getObj()->getName() ) ) //&&
           // prevent IntWall:NextTo to write out another Space!!
           //!pObj->getClass()->ClassInParentList( pProp->getType()->m_i1ObjClassIdx ) )
      {	BOOL bClassInParList = FALSE;
			for (int iObjCls=0; (!bClassInParList && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
				bClassInParList = (pProp->getType()->getObj1ClassIdx(iObjCls) > 0 && pObj->getClass()->ClassInParentList( pProp->getType()->getObj1ClassIdx(iObjCls) ));
         // if this property assigns another object, that assignment requires to be written
         // and the assigned object has not already been written, then write it
			if (!bClassInParList)
         	WriteComponent( pProp->getObj(), iBEMProcIdx, bWritePrimaryDefaultData, iIndentSpcs );
		}
   }
}


//static inline BOOL StringAllUpper( QString& str )   // SAC 8/30/11
static inline BOOL StringAllUpper( const char* str )   // SAC 8/30/11
{	BOOL bRetVal = TRUE;
	//int iNumChars = str.length();
	//for (int i=0; (i<iNumChars && bRetVal); i++)
	int i = -1;
	while (bRetVal && str[++i] != NULL)
		bRetVal = isupper( str[i] );
	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteComponent()
//
// Purpose ------------------------------------------------------------------
//   Write a component's definition to the file.
//   
// Arguments ----------------------------------------------------------------
//   BEMObject* pObj  : a pointer to the object being written.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteComponent( BEMObject* pObj, int iBEMProcIdx /*=-1*/, bool bWritePrimaryDefaultData /*=false*/, int iIndentSpcs /*=0*/ )		// SAC 6/8/15 - CBECC issue 1061
{
	// SAC 8/30/11 - added code to abort writing of this object if we are in CSE writing mode and component type has any lower case letters
   //if (m_iFileType == BEMFT_CSE && !StringAllUpper( pObj->getClass()->getShortName() ))
   if (m_iFileType == BEMFT_CSE && (pObj->getClass()->getShortName().indexOf("cse")!=0 ||
   		!StringAllUpper( pObj->getClass()->getShortName().right( pObj->getClass()->getShortName().length()-3 ).toLocal8Bit().constData() )))
		return;

   if (m_bWriteAssignedComponents)
   {	// add this component to the list of written components only if m_bWriteAssignedComponents==TRUE
   	AddToComponentNameList( pObj->getName() );	// SAC 3/25/16 - moved here from inside WriteProperties() to ensure that this object name is logged BEFORE writing assigned objects (Com tic #628)
		WriteAssignedComponents( pObj, iBEMProcIdx, bWritePrimaryDefaultData, iIndentSpcs );
	}

   // first write this component's properties
   WriteProperties( pObj, iBEMProcIdx, bWritePrimaryDefaultData, false, iIndentSpcs );

   // then write each of this component's children (recursively)
   if (pObj->getChildCount() > 0)
   {
      // prevent writing cseGAIN children of cseTOP iff writing CSE input AND specific list of objects to be written is specified AND cseGAIN is not in that list - SAC 01/25/22 (MFam)
      bool bExcludeCSEGainObjs = false;
      int iCID_Gain = -1;
      if (m_iFileType == BEMFT_CSE && m_plaClsObjIndices && pObj->getClass()->getShortName().indexOf("cseTOP")==0)
      {  iCID_Gain = BEMPX_GetDBComponentID( "cseGAIN" );
         if (iCID_Gain > 0 && !ObjectToBeWritten( iCID_Gain, -1 ))
            bExcludeCSEGainObjs = true;
      }

      // SAC 2/19/14 - added special handling for PolyLp objects - we need to write those FIRST, before other child types to ensure they are not written after other valid PolyLp parents
		int iPolyLpCID = BEMPX_GetDBComponentID( "PolyLp" );
		for (int iLp = (iPolyLpCID>0 ? 0 : 1); iLp < 2; iLp++)
		{	int iChildCID		= ( iLp==0                  ? iPolyLpCID : -1);
			int iNotChildCID	= ((iLp==1 && iPolyLpCID>0) ? iPolyLpCID : -1);

      	// Cruise thru list of BEM child objects, writing each out to the file
      //	POSITION pos = pObj->m_children.GetHeadPosition();
      //	while ( pos != NULL )
      //	{
      //	   BEMObject* pChild = (BEMObject*) pObj->m_children.GetAt( pos );
			for (int iCIdx=0; iCIdx < pObj->getChildCount(); iCIdx++)
			{	BEMObject* pChild = pObj->getChild( iCIdx );					assert( pChild );
      	   if (pChild != NULL && (iChildCID < 0 || pChild->getClass()->get1BEMClassIdx() == iChildCID   ) &&	// SAC 2/19/14
																	 pChild->getClass()->get1BEMClassIdx() != iNotChildCID &&
                (!bExcludeCSEGainObjs || pChild->getClass()->get1BEMClassIdx() != iCID_Gain) )     // SAC 01/25/22 (MFam)
      	   {
      	      WriteComponent( pChild, iBEMProcIdx, bWritePrimaryDefaultData, iIndentSpcs+m_iChildIndent );
      	   }
      }	}
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteProjectFile()
//
// Purpose ------------------------------------------------------------------
//   Main function to write out the contents of the database to a file.
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
void CProjectFile::AppendCSEObjectType( QString& sPartial, BEMObject* pObj )  // SAC 3/22/16
{
   QString qsClsName = (m_bWritePrevNames && pObj->getClass()->getNumPreviousNames() > 0 ? pObj->getClass()->getPreviousName(0) : pObj->getClass()->getShortName());    // SAC 08/06/21 (MFam)
   int length = qsClsName.length();
	QString sObjType = qsClsName;
	if (m_iFileType == BEMFT_CSE)
	{	assert( sObjType.indexOf( "cse" ) == 0 );
		length-=3;
		sPartial += sObjType.right( length );
	}
	else
		sPartial += sObjType.right( length );
}

void CProjectFile::WriteObjectName( QString& sRec, BEMObject* pObj )
{	AppendCSEObjectType( sRec, pObj );		sRec += "   ";					assert( pObj->getName().length() <= MAX_CSE_NAMELENGTH );
	m_file.WriteToken( sRec.toLocal8Bit().constData(), sRec.length() );
	m_file.WriteQuotedString( pObj->getName().toLocal8Bit().constData(), pObj->getName().length() );
	m_file.NewLine();
}

void CProjectFile::WriteProjectFile( int iBEMProcIdx /*=-1*/ )  // SAC 3/18/13
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
	BEMProcObject* pBEMProc = getBEMProcPointer( 0 );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return;

   if (pBEMProc->getType() == BEMT_CBECC && m_iFileType == BEMFT_Std)   // SAC 8/30/11 - added iFileType argument
      // first thing to write is the ruleset filename
      WriteRulesetFilename( iBEMProcIdx );

	bool bCSEDHWPreRunReqd = false;
	bool bCSEDHWSolarPreRunReqd = false;	// SAC 1/28/20 (StdSolarSys)
   bool bCSECHPWHSizingRunReqd = false;   // SAC 07/07/21 (Res tic #1275)
   int iNumCSEDHWSysShuffles = 0;         // SAC 05/13/21
	long lDBID_cseDHWSYS_wsDayUse_x=0, lDBID_cseDHWSYS_wsLoadShareDHWSYS=0;
   if (m_iFileType == BEMFT_CSE)   // SAC 8/28/12 - special CSE '#define' writing stuff   - SAC 3/15/16 - and 
	{	int iArr;
		long lProjCommentDBID   = BEMPX_GetDatabaseID( "Proj:CSE_Comment" );
		if (lProjCommentDBID < 1)
			lProjCommentDBID = BEMPX_GetDatabaseID( "Proj:CSEComment" );
		int iMaxArray = (lProjCommentDBID > 0 ? BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lProjCommentDBID ), BEMPX_GetPropertyID( lProjCommentDBID ), iBEMProcIdx ) : -1);
		QString sComment;
		int iNumCommentsWritten = 0;
		for (iArr=0; iArr < iMaxArray; iArr++)
		{	if (BEMPX_GetString(  lProjCommentDBID+iArr, sComment, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sComment.isEmpty())
			{	m_file.WriteToken( sComment.toLocal8Bit().constData(), sComment.length() );
				m_file.NewLine();
				iNumCommentsWritten++;
			}
		}
		if (iNumCommentsWritten > 0)
			m_file.NewLine();

		long lProjDefNameDBID   = BEMPX_GetDatabaseID( "Proj:CSE_DefineName" );
		long lProjDefTypeDBID   = BEMPX_GetDatabaseID( "Proj:CSE_DefineType" );
		long lProjDefFloatDBID  = BEMPX_GetDatabaseID( "Proj:CSE_DefineFloat" );
		long lProjDefStringDBID = BEMPX_GetDatabaseID( "Proj:CSE_DefineString" );
		if (lProjDefNameDBID < 1)		// SAC 5/17/16 - backward compat
			lProjDefNameDBID   = BEMPX_GetDatabaseID( "Proj:DefineName" );
		if (lProjDefTypeDBID < 1)
			lProjDefTypeDBID   = BEMPX_GetDatabaseID( "Proj:DefineType" );
		if (lProjDefFloatDBID < 1)
			lProjDefFloatDBID  = BEMPX_GetDatabaseID( "Proj:DefineFloat" );
		if (lProjDefStringDBID < 1)
			lProjDefStringDBID = BEMPX_GetDatabaseID( "Proj:DefineString" );
		if (lProjDefNameDBID > 0 && lProjDefTypeDBID > 0 && lProjDefFloatDBID > 0 && lProjDefStringDBID > 0)
		{	iMaxArray = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lProjDefNameDBID ), BEMPX_GetPropertyID( lProjDefNameDBID ), iBEMProcIdx );
			QString sDefName, sDefStr, sOutputLine;			long lDefType;			double fDefVal;
			for (iArr=0; iArr < iMaxArray; iArr++)
			{	if (BEMPX_GetString(  lProjDefNameDBID+iArr, sDefName, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sDefName.isEmpty() &&
					 BEMPX_GetInteger( lProjDefTypeDBID+iArr, lDefType, -1, -1, -1, BEMO_User, iBEMProcIdx ) && lDefType >= 0 && lDefType < 4)
				{	// #define type: 0-name only, 1-float, 2-string w/ quotes, 3-string no quotes
					sOutputLine.clear();
					if (lDefType == 0)
						sOutputLine = QString( " #define  %1" ).arg( sDefName );
					else if (lDefType == 1 && BEMPX_GetFloat( lProjDefFloatDBID+iArr, fDefVal, 0, -1, -1, BEMO_User, iBEMProcIdx ))
						sOutputLine = QString( " #define  %1  %2" ).arg( sDefName, QString::number(fDefVal) );
					else if (lDefType >= 2 && lDefType < 4 && BEMPX_GetString( lProjDefStringDBID+iArr, sDefStr, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) &&
								!sDefStr.isEmpty())
					{	if (lDefType == 2)
							sOutputLine = QString( " #define  %1  \"%2\"" ).arg( sDefName, sDefStr );
						else
							sOutputLine = QString( " #define  %1  %2" ).arg( sDefName, sDefStr );
					}
					if (!sOutputLine.isEmpty())
					{	m_file.WriteToken( sOutputLine.toLocal8Bit().constData(), sOutputLine.length() );
				   	m_file.NewLine();
					}
				}
			}
		}

	// Write DHW Use Include file statement - SAC 3/15/16
		long lProjDHWUseIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:CSE_DHWUseIncFile" );
		if (lProjDHWUseIncludeFileDBID < 1)		// // SAC 10/18/21 (MFam)
			lProjDHWUseIncludeFileDBID = BEMPX_GetDatabaseID( "ResProj:DHWUseIncludeFile" );
		if (lProjDHWUseIncludeFileDBID < 1)		// SAC 5/17/16 - backward compat
			lProjDHWUseIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:DHWUseIncludeFile" );
		QString sDHWUseIncFile;
		if (lProjDHWUseIncludeFileDBID > 0 && BEMPX_GetString( lProjDHWUseIncludeFileDBID, sDHWUseIncFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sDHWUseIncFile.isEmpty())
		{	QString sProjFN = m_file.FileName();
			QString sFullIncPathFile = sProjFN.left( std::max( sProjFN.lastIndexOf('\\'), sProjFN.lastIndexOf('/') ) + 1 );
			sFullIncPathFile += sDHWUseIncFile;
			if (FileExists( sFullIncPathFile.toLocal8Bit().constData() ))
			{	sProjFN = QString( "\n#include \"%1\"\n" ).arg( sDHWUseIncFile );
				m_file.WriteToken( sProjFN.toLocal8Bit().constData(), sProjFN.length() );
			   m_file.NewLine();
			}
		}

		long lCSEDHWPreRunReqd = 0;	// SAC 3/22/16
		long lProjCSEDHWPreRunReqdDBID = BEMPX_GetDatabaseID( "ResProj:CSE_DHWPreRunReqd" );   // SAC 10/18/21 (MFam)
		if (lProjCSEDHWPreRunReqdDBID < 1)	
			lProjCSEDHWPreRunReqdDBID = BEMPX_GetDatabaseID( "Proj:CSE_DHWPreRunReqd" );
		if (lProjCSEDHWPreRunReqdDBID < 1)	// SAC 5/17/16 - backward compat
			lProjCSEDHWPreRunReqdDBID = BEMPX_GetDatabaseID( "Proj:CSEDHWPreRunReqd" );
		if (lProjCSEDHWPreRunReqdDBID < 1)
			bCSEDHWPreRunReqd = true;		// always do pre-run for older rulesets
		else if (BEMPX_GetInteger( lProjCSEDHWPreRunReqdDBID, lCSEDHWPreRunReqd, -1, -1, -1, BEMO_User, iBEMProcIdx ) && lCSEDHWPreRunReqd > 0)
			bCSEDHWPreRunReqd = true;

		long lCSEDHWSolarPreRunReqd = 0;	// SAC 1/28/20 (StdSolarSys)
		long lProjCSEDHWSolarPreRunReqdDBID = BEMPX_GetDatabaseID( "Proj:CSE_DHWSolarPreRunReqd" );
		if (lProjCSEDHWSolarPreRunReqdDBID < 1)	// SAC 10/18/21 (MFam)
			lProjCSEDHWSolarPreRunReqdDBID = BEMPX_GetDatabaseID( "ResProj:CSE_DHWSolarPreRunReqd" );
		if (lProjCSEDHWSolarPreRunReqdDBID > 0 && BEMPX_GetInteger( lProjCSEDHWSolarPreRunReqdDBID, lCSEDHWSolarPreRunReqd, -1, -1, -1, BEMO_User, iBEMProcIdx ) && lCSEDHWSolarPreRunReqd > 0)
			bCSEDHWSolarPreRunReqd = true;

      long lDBID_Proj_CSEDHWSizingRunReqd = BEMPX_GetDatabaseID( "Proj:CSE_DHWSizingRunReqd" );    // SAC 07/07/21 (Res tic #1275)
		if (lDBID_Proj_CSEDHWSizingRunReqd < 1)	// SAC 10/18/21 (MFam)
			lDBID_Proj_CSEDHWSizingRunReqd = BEMPX_GetDatabaseID( "ResProj:CSE_DHWSizingRunReqd" );
      long lCSEDHWSizingRunReqd=0;
      bCSECHPWHSizingRunReqd = (lDBID_Proj_CSEDHWSizingRunReqd > 0 && BEMPX_GetInteger( lDBID_Proj_CSEDHWSizingRunReqd, lCSEDHWSizingRunReqd ) && lCSEDHWSizingRunReqd > 0);

		long lShuffleSFamDHWNum = 0;	   // SAC 05/13/21
		long lProjShuffleSFamDHWNumDBID = BEMPX_GetDatabaseID( "Proj:ShuffleSFamDHWNum" );
		if (lProjShuffleSFamDHWNumDBID < 1)	// SAC 10/18/21 (MFam)
			lProjShuffleSFamDHWNumDBID = BEMPX_GetDatabaseID( "ResProj:ShuffleSFamDHWNum" );
		if (lProjShuffleSFamDHWNumDBID > 0 && BEMPX_GetInteger( lProjShuffleSFamDHWNumDBID, lShuffleSFamDHWNum, -1, -1, -1, BEMO_User, iBEMProcIdx ) && lShuffleSFamDHWNum > 0)
			iNumCSEDHWSysShuffles = lShuffleSFamDHWNum;
		lDBID_cseDHWSYS_wsDayUse_x        = BEMPX_GetDatabaseID( "cseDHWSYS:wsDayUse_x" );
		lDBID_cseDHWSYS_wsLoadShareDHWSYS = BEMPX_GetDatabaseID( "cseDHWSYS:wsLoadShareDHWSYS" );
	}

	if (bCSECHPWHSizingRunReqd)		// SAC 07/07/21
	{	AddToSpecificProperties( "wsSolarSys" );
   }
	if (bCSEDHWPreRunReqd)		// SAC 3/22/16
	{	AddToSpecificProperties( "whZone" );
		AddToSpecificProperties( "whTEx_x" );
		AddToSpecificProperties( "whASHPSrcZn" );
		AddToSpecificProperties( "whASHPSrcT_x" );
		AddToSpecificProperties( "alter_whMult_x" );		// SAC 12/4/19 - to facilitate central elec DHWSys autosizing
		AddToSpecificProperties( "alter_whVol_x" );		// SAC 12/4/19 - to facilitate central elec DHWSys autosizing
	}
	if (bCSEDHWSolarPreRunReqd)		// SAC 1/28/20
	{	AddToSpecificProperties( "alter_scMult" );
	}

   // then loop over all classes, writing out the components for each class, one by one
   int iNumClasses = BEMPX_GetNumClasses();
   for (int i1Class=1; i1Class<=iNumClasses; i1Class++)
   {
      int iError;
      BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
      if ( (iError >= 0) && (pClass != NULL) &&
             // don't write class objects tagged as AutoCreate to INPUT file
           ( (!m_bIsUserInputMode) || (!pClass->getAutoCreate()) ) )
      {
         if (pClass->getShortName().compare( "cseIZXFER" )==0)
         {  // BEFORE writing IZXFERs, write doMainSim = "NO", since any/all DHW preruns/runs would have already been listed above - SAC 05/23/22
            long lDBID_cseTOP_DOMainSim = BEMPX_GetDatabaseID( "cseTOP:DOMainSim" );
            QString qsDoMainSim;
            if (lDBID_cseTOP_DOMainSim > 0 && BEMPX_GetString( lDBID_cseTOP_DOMainSim, qsDoMainSim, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsDoMainSim.isEmpty())
            {	m_file.NewLine();
					QString qsWriteDoMainSim = QString( "   doMainSim = \"%1\"" ).arg( qsDoMainSim );
      			m_file.WriteWholeRecord( qsWriteDoMainSim.toLocal8Bit().constData() );
               m_file.NewLine();
         }  }

			// SAC 4/16/14 - if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
			bool bWriteClass = (m_iFileMode == BEMFM_INPUT && m_bOnlyValidInputs) ? false : true;
			if (!bWriteClass)
			{	for (int iP1=0; (!bWriteClass && iP1 < eBEMProc.getClass(i1Class-1)->getNumProps()); iP1++)
   	      {  int iPropDataType = BEMPX_GetCompDataType( BEMPX_GetDBID( i1Class, (iP1+1), 1 /*i1Array*/ ) );
					if (iPropDataType < BEMD_NotInput)
						bWriteClass = true;
			}	}

			// SAC 12/16/18 - enable CSE HPWHSIZE runs by filtering out classes not targeted for output via m_plaClsObjIndices
			if (bWriteClass && m_plaClsObjIndices)
				bWriteClass = ObjectToBeWritten( i1Class, -1 );

			if (bWriteClass)
			{
         	// Cruise thru list of BEM objects for this class
				int ib=0;
				for (; ib < (int) pClass->ObjectCount( BEMO_User ); ib++)
				{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
         	   if (pObj != NULL)
         	   {
         	   	bool bOKToWriteObj = (m_plaClsObjIndices ? ObjectToBeWritten( i1Class, ib ) : true);		// SAC 12/16/18 - CSE HPWHSIZE runs
         	      // only write the component if it doesn't have a parent.
         	      // if it DOES have a parent, then it will be written automatically during the
         	      // course of its parent being written.
         	      if (bOKToWriteObj && pObj->getParent() == NULL)
         	      {
         	         WriteComponent( pObj, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, 0 /*IndentSpcs*/ );
         	      }
         	   }
         	   else
         	   {
         	      assert( FALSE );
         	   }
         	}

            // Write COPIES of DHWSYSs (when needed)
            if (iNumCSEDHWSysShuffles > 1 && pClass->getShortName().compare( "cseDHWSYS" )==0)
   			{	for (ib=0; ib < (int) pClass->ObjectCount( BEMO_User ); ib++)
   				{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
            	   if (pObj != NULL)
            	   {	bool bOKToWriteObj = (m_plaClsObjIndices ? ObjectToBeWritten( i1Class, ib ) : true);		// SAC 12/16/18 - CSE HPWHSIZE runs
            	      if (bOKToWriteObj && pObj->getParent() == NULL)
                     {  QString qsDayUseName, qsLoadShareSysName;
                        int iFirstShuffleNum = 0;
                        if (lDBID_cseDHWSYS_wsDayUse_x > 0 && BEMPX_GetString( lDBID_cseDHWSYS_wsDayUse_x, qsDayUseName, FALSE, 0, -1, ib, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsDayUseName.isEmpty())
                        {  iFirstShuffleNum = (int) atof( qsDayUseName.right(2).toLocal8Bit().constData() );
                           qsDayUseName = qsDayUseName.left( qsDayUseName.length()-2 );
                        }
                        if (lDBID_cseDHWSYS_wsLoadShareDHWSYS > 0)
                           BEMPX_GetString( lDBID_cseDHWSYS_wsLoadShareDHWSYS, qsLoadShareSysName, FALSE, 0, -1, ib, BEMO_User, NULL, 0, iBEMProcIdx );
                        for (int iShuffleNum = 2; iShuffleNum <= iNumCSEDHWSysShuffles; iShuffleNum++)
                        {  QString qsCSECopyLine = QString( "DHWSYS  \"%1-%2\"  COPY  \"%3\"  " ).arg( pObj->getName(), QString::number(iShuffleNum), pObj->getName() );
                           if (iFirstShuffleNum > 0)
                           {  int iThisShuffleNum = iFirstShuffleNum + iShuffleNum - 1;
                              if (iThisShuffleNum > 5)         // prevent shuffles > 5 ??
                                 iThisShuffleNum = (iThisShuffleNum % 5);
                              //qsCSECopyLine += QString( "wsDayUse = %10%2  " ).arg( qsDayUseName, QString::number(iThisShuffleNum) );
                              qsCSECopyLine += QString( "wsDayUse = %1" ).arg( qsDayUseName );
                              qsCSECopyLine += QString( "0%1  " ).arg( QString::number(iThisShuffleNum) );
                           }
                           if (!qsLoadShareSysName.isEmpty())
                              qsCSECopyLine += QString( "wsLoadShareDHWSYS = \"%1-%2\"  " ).arg( qsLoadShareSysName, QString::number(iShuffleNum) );
            					m_file.WriteWholeRecord( qsCSECopyLine.toLocal8Bit().constData() );
                        // now RE-write any properties defined as EXPRESSIONS (to avoid a CSE bug in COPY command) - SAC 05/19/21
								   WriteProperties( pObj, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, true /*bSkipWritingComponentName*/, 0 /*iIndentSpcs*/, true /*bWriteOnlyCSEExpressionProperties*/ );
                        }
         	      		m_file.NewLine();
               }  }  }
            }

			   // SAC 8/19/15 - added code to insert "Run" command following writing of any cseDHWSYS objects (and child heaters) - in order to perform LDEF "PreRun"
         	if (m_iFileType == BEMFT_CSE && pClass->getShortName().compare("cseTOP", Qt::CaseInsensitive)==0 && pClass->ObjectCount( BEMO_User ) > 0)
				{	m_file.WriteWholeRecord( " DELETE Report \"eb\"    // move from end of CSE file" );		// SAC 9/8/15 - move this line UP, immediately following cseTOP command
	      		m_file.NewLine();
	      	}

            // CSE Ecosizer ASHP autosizing mechanism - SAC 07/07/21 (Res tic #1275)
         	if (bCSECHPWHSizingRunReqd && pClass->getShortName().compare("cseDHWSYS", Qt::CaseInsensitive)==0 && pClass->ObjectCount( BEMO_User ) > 0)
         	{	m_file.WriteWholeRecord( " verbose = -1          // suppress progress messages" );
					m_file.WriteWholeRecord( " RUN                   // prerun #1: find daywaste fraction" );
	      		m_file.NewLine();

               // alter each DHWSYS to restore the PreRun calc mode
               QString qsWSCalcMode;   int iCMError, iCMSpecialVal, iNumPreRunRestores=0;
   				for (ib=0; ib < (int) pClass->ObjectCount( BEMO_User ); ib++)
	   			{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
                  qsWSCalcMode = BEMPX_GetString( BEMPX_GetDatabaseID( "cseDHWSYS:wsCalcMode" ), iCMSpecialVal, iCMError, ib, BEMO_User, iBEMProcIdx );
                  qsWSCalcMode = qsWSCalcMode.toUpper();
            	   if (pObj != NULL && !qsWSCalcMode.compare( "PRERUN" ))
                  {  qsWSCalcMode = QString( "ALTER  DHWSYS  \"%1\"" ).arg( pObj->getName() );
      					m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
		      			m_file.WriteWholeRecord( "   wsCalcMode = PreRun" );
				      	m_file.WriteWholeRecord( "endDHWSYS" );
                     iNumPreRunRestores++;
               }  }        assert( iNumPreRunRestores > 0 );

	      		m_file.NewLine();
					m_file.WriteWholeRecord( " RUN                   // prerun #2: Ecosizer load" );
	      		m_file.NewLine();

               // no need to reset wsCalcMode back to PreRun, as following run should be final

               // write ALTERs that set heater tank volume & htg capacity
               long lSysSzgReqd=0, lHtrSzgReqd=0;   int iNumSzgSystems=0;
               int iHtrClassID = BEMPX_GetClassIndexByLongName( "cseDHWHEATER" );      assert( iHtrClassID > 0 );
               int iSysClassID = pClass->get1BEMClassIdx();                            assert( iSysClassID > 0 );
   				for (ib=0; ib < (int) pClass->ObjectCount( BEMO_User ); ib++)
	   			{	BEMObject* pDHWSysObj = pClass->GetObject( BEMO_User, ib );
                  // check for and keep track of SOLARSYSTEM assignments left out of initial CSE object writing
                  QString qsWSSolarSys = BEMPX_GetString( BEMPX_GetDatabaseID( "cseDHWSYS:wsSolarSys" ), iCMSpecialVal, iCMError, ib, BEMO_User, iBEMProcIdx );
                  bool bFoundSzgHtr=false;
        	         if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "cseDHWSYS:CSESizingRunRequired" ), lSysSzgReqd, 0, -1,	ib, BEMO_User, iBEMProcIdx ) && lSysSzgReqd > 0)
                  {  
                     int iNumChildHtrs = (int) BEMPX_GetNumChildren( iSysClassID, ib, BEMO_User, iHtrClassID, iBEMProcIdx );
                     // loop over child DHWHEATERs searching for any requiring autosizing
                     for (int iChild=0; (!bFoundSzgHtr && iChild<iNumChildHtrs); iChild++)
                     {  BEM_ObjType eChildHtrObjType = BEMO_User;
                        int i0ChildHtrObjIdx = BEMPX_GetChildObjectIndex( iSysClassID, iHtrClassID, iCMError, eChildHtrObjType, iChild+1, ib, BEMO_User, iBEMProcIdx );
                        assert( i0ChildHtrObjIdx >= 0 );
                        assert( eChildHtrObjType == BEMO_User );
                        if (i0ChildHtrObjIdx >= 0)
                        {  BEMObject* pDHWHtrObj = BEMPX_GetObjectByClass( iHtrClassID, iCMError, i0ChildHtrObjIdx, BEMO_User, iBEMProcIdx );      assert( pDHWHtrObj );
                           if (pDHWHtrObj && BEMPX_GetInteger( BEMPX_GetDatabaseID( "cseDHWHEATER:CSESizingRunRequired" ), lHtrSzgReqd, 0, -1, i0ChildHtrObjIdx, BEMO_User, iBEMProcIdx ) && lHtrSzgReqd > 0)
                           {  bFoundSzgHtr = true;
                              // NOTE: THIS ASSUMES THERE IS ONLY 1 HEATER TO BE SIZED
                              qsWSCalcMode = QString( "ALTER  DHWSYS  \"%1\"" ).arg( pDHWSysObj->getName() );           m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
                              if (qsWSSolarSys.size() > 0)
                              {  qsWSCalcMode = QString( "   wsSolarSys = \"%1\"" ).arg( qsWSSolarSys );                m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
                              }
                              qsWSCalcMode = QString( "   ALTER  DHWHEATER  \"%1\"" ).arg( pDHWHtrObj->getName() );     m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
                              qsWSCalcMode = QString( "      whVolRunning = @DHWSYS[\"%1\"].volRunningDes" ).arg( pDHWSysObj->getName() );   m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
                              qsWSCalcMode = QString( "      whHeatingCap = @DHWSYS[\"%1\"].heatingCapDes" ).arg( pDHWSysObj->getName() );   m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
         				      	m_file.WriteWholeRecord( "endDHWSYS" );
               	      		m_file.NewLine();
                              iNumSzgSystems++;
                     }  }  }
                  }
                  if (!bFoundSzgHtr && qsWSSolarSys.size() > 0)
                  {  // write wsSolarSys ALTER for systems w/out auto-sized heater(s)
                     qsWSCalcMode = QString( "ALTER  DHWSYS  \"%1\"" ).arg( pDHWSysObj->getName() );        m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
                     qsWSCalcMode = QString( "   wsSolarSys = \"%1\"" ).arg( qsWSSolarSys );                m_file.WriteWholeRecord( qsWSCalcMode.toLocal8Bit().constData() );
         				m_file.WriteWholeRecord( "endDHWSYS" );
               	   m_file.NewLine();
                  }
                  if (qsWSSolarSys.size() > 0)
                     RemoveSpecificPropObject( pDHWSysObj );
               }           assert( iNumSzgSystems > 0 );
  					m_file.WriteWholeRecord( " UNSET verbose         // re-enable progress messages" );
	      		m_file.NewLine();
               RemoveFromSpecificProperties( "wsSolarSys" );
            }

         	if ((bCSEDHWPreRunReqd || bCSEDHWSolarPreRunReqd) && pClass->getShortName().compare("cseDHWSYS", Qt::CaseInsensitive)==0 && pClass->ObjectCount( BEMO_User ) > 0)
         	{	if (!bCSECHPWHSizingRunReqd)
               {  m_file.WriteWholeRecord( " verbose = -1          // suppress progress messages" );
					   m_file.WriteWholeRecord( " RUN                   // perform DHW (or DHWSolar) pre-run calcs" );
   					m_file.WriteWholeRecord( " UNSET verbose         // re-enable progress messages" );
            		//m_file.WriteToken( szCSE_Run, strlen( szCSE_Run ) );
	         		//m_file.NewLine();		m_file.NewLine();
	         		m_file.NewLine();
               }

				// more special pre-run logic - need to write out EXPORT objects and then another RUN command BEFORE the ALTER data - SAC 1/28/20 (StdSolarSys)
					if (bCSEDHWSolarPreRunReqd)
					{
						int i1XClass = BEMPX_GetDBComponentID( "cseEXPORT" );			assert( i1XClass > 0 );
						BEMObject* pXObj = BEMPX_GetObjectByName( i1XClass, iError, "DHWSolarSys Sizing Export" );		assert( pXObj );

      				//BEMClass* pXClass = BEMPX_GetClass( i1XClass, iError, iBEMProcIdx );
						//int ibx=0;
						//for (; ibx < (int) pXClass->ObjectCount( BEMO_User ); ibx++)
						//{	BEMObject* pXObj = pXClass->GetObject( BEMO_User, ibx );
		         	//   if (pXObj != NULL)
		         	//   {  // only write the component if it doesn't have a parent.
		         	//      // if it DOES have a parent, then it will be written automatically during the
		         	//      // course of its parent being written.
		         	//      if (pXObj->getParent() == NULL)
		         	//      {
								if (pXObj)
		         	         WriteComponent( pXObj, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, 0 /*IndentSpcs*/ );
		         	//      }
		         	//   }
		         	//   else
		         	//   {   assert( FALSE );
		         	//}  }
						// and FOLLOW the EXPORT objects by another RUN
						m_file.WriteWholeRecord( " RUN                   // perform DHWSolar round 2 pre-run calcs" );
		      		m_file.NewLine();

					// NOW write alters for each DHWSOLARSYS (and children)
						int i1SolSysClass = BEMPX_GetDBComponentID( "cseDHWSOLARSYS" );							assert( i1SolSysClass > 0 );
      				BEMClass* pSolSysClass = BEMPX_GetClass( i1SolSysClass, iError, iBEMProcIdx );		assert( pSolSysClass );
						// there ARE one or more objects that require ALTERation
						SetSpecificPropertyMode( TRUE /*bWriteOnlySpecificProps*/ );
						QString sCSERec;
						for (ib=0; ib < (int) pSolSysClass->ObjectCount( BEMO_User ); ib++)
						{	BEMObject* pObj = pSolSysClass->GetObject( BEMO_User, ib );
      		   	   if (pObj != NULL)
      		   	   {	BOOL bMainObjWritten = FALSE;
      		   	   	if (ObjectInSpecificPropObjectArray( pObj ))
      		   	   	{	sCSERec = "ALTER ";
									WriteObjectName( sCSERec, pObj );
								   bMainObjWritten = TRUE;
								   WriteProperties( pObj, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, true /*bSkipWritingComponentName*/, 0 /*iIndentSpcs*/ );
								}
							   // then write each of this component's children (recursively)
						   	if (pObj->getChildCount() > 0)
							   {	// Cruise thru list of BEM child objects, writing each out to the file
						      //	POSITION pos = pObj->m_children.GetHeadPosition();
						      //	while ( pos != NULL )
						      //	{	BEMObject* pChild = (BEMObject*) pObj->m_children.GetAt( pos );
									for (int iCIdx=0; iCIdx < pObj->getChildCount(); iCIdx++)
									{	BEMObject* pChild = pObj->getChild( iCIdx );					assert( pChild );
										if (pChild)
						      	   {
			      		   	   	if (ObjectInSpecificPropObjectArray( pChild ))
			      		   	   	{
			      		   	   		if (!bMainObjWritten)
			      		   		   	{	sCSERec = "ALTER ";
													WriteObjectName( sCSERec, pObj );
												   bMainObjWritten = TRUE;
												}

			      		   	   		sCSERec = " ALTER ";
												WriteObjectName( sCSERec, pChild );
											   WriteProperties( pChild, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, true /*bSkipWritingComponentName*/, 0 /*iIndentSpcs*/ );
											}
						      	   }
						      }	}
						}	}
					}

				// go BACK through objects of this type and write properties excluded from the first writing of object - SAC 3/22/16
					if (GetSpecificPropObject(0))
					{	// there ARE one or more objects that require ALTERation
						SetSpecificPropertyMode( TRUE /*bWriteOnlySpecificProps*/ );

						QString sCSERec;
						for (ib=0; ib < (int) pClass->ObjectCount( BEMO_User ); ib++)
						{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
      		   	   if (pObj != NULL)
      		   	   {	BOOL bMainObjWritten = FALSE;
      		   	   	if (ObjectInSpecificPropObjectArray( pObj ))
      		   	   	{	sCSERec = "ALTER ";
									WriteObjectName( sCSERec, pObj );
								   bMainObjWritten = TRUE;
								   WriteProperties( pObj, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, true /*bSkipWritingComponentName*/, 0 /*iIndentSpcs*/ );
								}

							   // then write each of this component's children (recursively)
						   	if (pObj->getChildCount() > 0)
							   {	// Cruise thru list of BEM child objects, writing each out to the file
						      //	POSITION pos = pObj->m_children.GetHeadPosition();
						      //	while ( pos != NULL )
						      //	{	BEMObject* pChild = (BEMObject*) pObj->m_children.GetAt( pos );
									for (int iCIdx=0; iCIdx < pObj->getChildCount(); iCIdx++)
									{	BEMObject* pChild = pObj->getChild( iCIdx );					assert( pChild );
										if (pChild)
						      	   {
			      		   	   	if (ObjectInSpecificPropObjectArray( pChild ))
			      		   	   	{
			      		   	   		if (!bMainObjWritten)
			      		   		   	{	sCSERec = "ALTER ";
													WriteObjectName( sCSERec, pObj );
												   bMainObjWritten = TRUE;
												}

			      		   	   		sCSERec = " ALTER ";
												WriteObjectName( sCSERec, pChild );
											   WriteProperties( pChild, iBEMProcIdx, false /*bWritePrimaryDefaultData*/, true /*bSkipWritingComponentName*/, 0 /*iIndentSpcs*/ );
											}
						      	   }
						      }	}
					}	}	}
//ALTER DHWSYS "DS1"
//  ALTER DHWHEATER "DH1"
//     whZone = "Garage"   // <<< set up actual surround linkage
					ResetSpecificProperties();		// SAC 3/22/16
	      	}
			}
      }
      else if ((iError < 0) && (pClass == NULL))
      {
         assert( FALSE );
      }
   }

   if (m_iFileType == BEMFT_Std || m_iFileType == BEMFT_CSE)   // SAC 8/30/11 - added iFileType argument  - SAC 3/15/12 - added CSE condition
   	WriteEndOfFileMarker( iBEMProcIdx );
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  SetWriteLibDataFlag()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::SetWriteLibDataFlag( bool bFlag )
{
   m_bWriteLibData = bFlag;
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  SetWriteAssignedCompsFlag()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::SetWriteAssignedCompsFlag( bool bFlag )
{
   m_bWriteAssignedComponents = bFlag;
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  SetPastingClassFromClipboard()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::SetPastingClassFromClipboard( int i1Class )
{
   m_iPastingClassFromClipboard = i1Class;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ResetComponentNameList()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::ResetComponentNameList()
{
   m_saComponentNames.clear();

//   // causes future allocates to grab 25 strings at a time to prevent too many reallocations
//   m_saComponentNames.SetSize( 0, 25 );  
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  AddToComponentNameList()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::AddToComponentNameList( QString& sCompName )
{
   m_saComponentNames.push_back( sCompName );
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  InComponentNameList()
//
/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::InComponentNameList( QString& sCompName )
{
   int iSize = (int) m_saComponentNames.size();
   for (int i=0; i<iSize; i++)
   {
      if (m_saComponentNames[i].compare( sCompName ) == 0)
         return TRUE;
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  ResetNewComponentNameList()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::ResetNewComponentNameList()
{
   m_saNewComponentNames.clear();

//   // causes future allocates to grab 25 strings at a time to prevent too many reallocations
//   m_saNewComponentNames.SetSize( 0, 25 );  
}

/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  AddToNewComponentNameList()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::AddToNewComponentNameList( QString& sCompName )
{
   m_saNewComponentNames.push_back( sCompName );
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  SubstituteComponentName()
//
/////////////////////////////////////////////////////////////////////////////
bool CProjectFile::SubstituteComponentName( QString& sCompName )
{
   int iNumNames = (int) m_saComponentNames.size();
   assert( iNumNames == (int) m_saNewComponentNames.size());
   for (int i=0; i<iNumNames; i++)
   {
      if (m_saComponentNames[i].compare( sCompName ) == 0)
      {
         sCompName = m_saNewComponentNames[i];
         return TRUE;
      }
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// CProjectFile Class Function:  WriteEndOfFileMarker()
//
/////////////////////////////////////////////////////////////////////////////
void CProjectFile::WriteEndOfFileMarker( int iBEMProcIdx /*=-1*/ )
{
   if (IsOpen())
   {
	   if (m_iFileType == BEMFT_CSE)   // SAC 3/15/12 - added CSE end of file stuff
		{
		// Write DELETE statements
			long lProjDelCompTypeDBID   = BEMPX_GetDatabaseID( "Proj:CSE_DeleteCompType" );
			long lProjDelCompNameDBID   = BEMPX_GetDatabaseID( "Proj:CSE_DeleteCompName" );
			if (lProjDelCompTypeDBID < 1)		// SAC 5/17/16 - backward compat
				lProjDelCompTypeDBID = BEMPX_GetDatabaseID( "Proj:DeleteCompType" );
			if (lProjDelCompNameDBID < 1)
				lProjDelCompNameDBID = BEMPX_GetDatabaseID( "Proj:DeleteCompName" );
			if (lProjDelCompTypeDBID > 0 && lProjDelCompNameDBID > 0)
			{	int iMaxArray = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lProjDelCompTypeDBID ), BEMPX_GetPropertyID( lProjDelCompTypeDBID ), iBEMProcIdx );
				QString sOutputLine, sDelType, sDelName;
				for (int iArr=0; iArr < iMaxArray; iArr++)
				{	if (BEMPX_GetString( lProjDelCompTypeDBID+iArr, sDelType, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sDelType.isEmpty() &&
						 BEMPX_GetString( lProjDelCompNameDBID+iArr, sDelName, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sDelName.isEmpty() )
					{	sOutputLine = QString( " DELETE %1  \"%2\"" ).arg( sDelType, sDelName );
						m_file.WriteToken( sOutputLine.toLocal8Bit().constData(), sOutputLine.length() );
				   	m_file.NewLine();
					}
				}
			}

		// Write Report Include file statement
			//long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:CSE_RptIncFile" );
			long lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "ResProj:ReportIncludeFile" );     // switch to newer version - SAC 05/13/22
			if (lProjReportIncludeFileDBID < 1)
				lProjReportIncludeFileDBID = BEMPX_GetDatabaseID( "Proj:ReportIncludeFile" );
			QString sRptIncFile;
			if (lProjReportIncludeFileDBID > 0 && BEMPX_GetString( lProjReportIncludeFileDBID, sRptIncFile, FALSE, 0, -1, -1, BEMO_User, NULL, 0, iBEMProcIdx ) && !sRptIncFile.isEmpty())
			{
				QString sProjFN = m_file.FileName();
				QString sFullRptIncPathFile = sProjFN.left( std::max( sProjFN.lastIndexOf('\\'), sProjFN.lastIndexOf('/') ) + 1 );
				sFullRptIncPathFile += sRptIncFile;
				if (FileExists( sFullRptIncPathFile.toLocal8Bit().constData() ))
				{	sProjFN = QString( "#include \"%1\"" ).arg( sRptIncFile );
					m_file.WriteToken( sProjFN.toLocal8Bit().constData(), sProjFN.length() );
				   m_file.NewLine();
				}
			}

      // write end-of-file marker
			m_file.NewLine();
      	m_file.WriteToken( szCSE_Run, (int) strlen( szCSE_Run ) );
      	m_file.NewLine();
      	m_file.WriteToken( szCSE_End, (int) strlen( szCSE_End ) );
      	m_file.NewLine();
		}
		else
		{	m_file.NewLine();
      	m_file.WriteToken( szEnd, (int) strlen( szEnd ) );
      	m_file.NewLine();
		}
   }
}


/////////////////////////////////////////////////////////////////////////////
//  END  OF  CProjectFile  CLASS  FUNCTIONS
/////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////
//
// Function:  InitUntitledLogFile()
//
// Purpose ------------------------------------------------------------------
//   Initializes the untitled project log file name and clears the file out.
//   
// Arguments ----------------------------------------------------------------
//   const char* psInitLogFileName  : name of the untitled log file
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void InitUntitledLogFile( const char* psInitLogFileName )
{
   if (psInitLogFileName != NULL)
   {
      esLogFileName = psInitLogFileName;
		esCSVLogFileName = esLogFileName + ".csv";	// SAC 1/9/13 - update CSV log filename as well...
   //   FILE *pfTempFile = fopen( psInitLogFileName, "w" );
   //   if (pfTempFile != NULL)
   //      fclose( pfTempFile );
		QFile file( esLogFileName );
		if (file.open( QFile::WriteOnly ))
			file.close();
   }
}

QString BEMPX_GetLogFilename( bool bCSVLog /*=false*/ )  // SAC 12/19/12
{	return (bCSVLog ? esCSVLogFileName : esLogFileName);
//const char* BEMPX_GetLogFilename( bool bCSVLog /*=false*/ )  // SAC 12/19/12
//{	return (bCSVLog ? (const char*) esCSVLogFileName.toLocal8Bit().constData() : (const char*) esLogFileName.toLocal8Bit().constData());
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  CopyOtherLogFile()
//
// Purpose ------------------------------------------------------------------
//   Copy the contents of an existing log file into another file.  This
//   function is called when the user saves an existing database as a new
//   file so that the existing project's log is copied into the new project's
//   log file.
//   
// Arguments ----------------------------------------------------------------
//   QFile& logFile       : log file to copy the other log into
//   const char* psLogFileName : name of the log file to copy the contents of
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static void CopyOtherLogFile( QFile& logFile, const char* psLogFileName )
{
   if (strlen( psLogFileName ) > 0 && FileExists( psLogFileName ))
   {
      QFile prevFile( psLogFileName );
      // open the log file to copy from
		if (prevFile.open( QIODevice::Text | QIODevice::ReadOnly ))
      {
#define  LogFileCopyBuffLen  1024
         char buff[ LogFileCopyBuffLen ];
         // read each line from the prev file into the log file
         int iReadRetVal = (int) prevFile.read( buff, LogFileCopyBuffLen-1 );
         while (iReadRetVal > 0)		// SAC 1/14/17 - fixed bug in log file copying
			{	logFile.write( buff, iReadRetVal );
				iReadRetVal = (int) prevFile.read( buff, LogFileCopyBuffLen-1 );
			}
         assert( iReadRetVal==0 );	// if -1, then error reading
      }
      else
      {	assert( FALSE );
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
static bool sbLogTimeStamps = true;
void BEMPX_EnableLogTimeStamps( bool bEnableTimeStamps )   // SAC 11/17/13
{	sbLogTimeStamps = bEnableTimeStamps;
}
bool BEMPX_GetLogTimeStamps()   // SAC 11/17/13
{	return sbLogTimeStamps;
}


/////////////////////////////////////////////////////////////////////////////
//
// Extern Function:  FileExists()
//
// Purpose ------------------------------------------------------------------
//   Determine whether or not a file already exists.
//   
// Arguments ----------------------------------------------------------------
//   const char* pszFileName  : name of the file to check the existance of.
//   
// Return Value -------------------------------------------------------------
//   TRUE if the file already exists, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool FileExists( const char* pszFileName )
{	return (boost::filesystem::exists(pszFileName));	//	PathFileExists( (LPCTSTR) pszFileName ) != FALSE);
}


// SAC 9/2/14 - based on CBECC's OKToWriteOrDeleteFile() - used to allow for delayed log file open
BOOL FileCanBeWrittenTo( const char* pszFileName, BOOL bFileMustExist )
{
   BOOL bRetVal = FALSE, bAbort = FALSE;
	if (!FileExists( pszFileName ))
	{	bAbort = bFileMustExist;
		if (!bFileMustExist)
			bRetVal = TRUE;
	}
	int iCount = 0;
   while (!bRetVal && !bAbort && ++iCount < 50)		// max of 50 iterations =~ 5 secs of sleep time
   {
      if (!FileExists( pszFileName ))  // user deleted or renamed file since last check -> return TRUE
		{	bAbort = bFileMustExist;
			if (!bFileMustExist)
				bRetVal = TRUE;
		}
      else
      {
////AfxMessageBox( "About to try opening file..." );
//         FILE *pfTempFile = fopen( pszFileName, "r+" );
//         if (pfTempFile != NULL)
//         {
////AfxMessageBox( "File opened OK." );
//            fclose( pfTempFile );
//            bRetVal = TRUE;
//         }
			QFile chkFile;
			chkFile.setFileName( pszFileName );
			if (chkFile.open( QIODevice::ReadOnly ))
			{	chkFile.close();
				bRetVal = TRUE;
			}
         if (!bRetVal)
				//std::this_thread::sleep_for( std::chrono::seconds(1) );
				Sleep(100);
      }
   }
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
static QFile fileOpenLog;
static QString ssOpenLogPathFile;

void BEMPX_OpenLogFile( const char* pszLogPathFile, bool bBlankFile /*=false*/ )		// SAC 5/19/14
{	if (pszLogPathFile == NULL || strlen(pszLogPathFile) < 3)
	{	assert( FALSE );
	}
	else
	{	if (!ssOpenLogPathFile.isEmpty() && ssOpenLogPathFile.compare( pszLogPathFile, Qt::CaseInsensitive ) != 0)
		{	fileOpenLog.flush();
			fileOpenLog.close();
		}

		ssOpenLogPathFile.clear();
		fileOpenLog.setFileName( pszLogPathFile );
		bool ok = false;
		if (bBlankFile || !FileExists( pszLogPathFile ))
			ok = fileOpenLog.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
// + QIODevice::Text ??
		else
		{	ok = fileOpenLog.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
			//if (ok)  // get to end of file so as not to add to the beginning of the file
			//	fileOpenLog.SeekToEnd();
		}
		if (ok)
		{	fileOpenLog.setPermissions( QFile::ReadOther | QFile::WriteOwner );
			ssOpenLogPathFile = pszLogPathFile;
	}	}
}

void BEMPX_RefreshLogFile( bool bReOpenLog /*=true*/ )		// SAC 5/19/14
{	if (!ssOpenLogPathFile.isEmpty())
	{	fileOpenLog.flush();
		fileOpenLog.close();
		if (bReOpenLog)
		{	fileOpenLog.setFileName( ssOpenLogPathFile );
			if (!fileOpenLog.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append ))
			{	assert( FALSE );
				ssOpenLogPathFile.clear();
		}	}
		else
			ssOpenLogPathFile.clear();
	}
}

void BEMPX_CloseLogFile()		// SAC 5/19/14
{	if (!ssOpenLogPathFile.isEmpty())
	{	fileOpenLog.close();
		ssOpenLogPathFile.clear();
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_WriteLogFile()
//
// Purpose ------------------------------------------------------------------
//   Adds an entry into the currently selected log file.
//   
// Arguments ----------------------------------------------------------------
//   const char* output           : string to write to log file
//   const char* psNewLogFileName : name of new log file to write to
//   BOOL        bBlankFile       : flag indicating whether or not to clear out the log file before writing to it
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
bool BEMPROC_API __cdecl BEMPX_WriteLogFile(   QString& output, const char* psNewLogFileName /*=NULL*/,
                                                          bool bBlankFile /*=false*/, BOOL bSupressAllMessageBoxes /*=FALSE*/,    // SAC 4/27/03 - added to prevent MessageBoxes during processing
																			 bool bAllowCopyOfPreviousLog /*=true*/,     // SAC 9/18/12 - new arg to allow/prevent log file copying
																			 const char** ppCSVColumnLabels /*=NULL*/ )   // SAC 12/19/12 - new array of const char* ptrs (ending in a NULL) to facilitate project-based CSV analysis result archival
{	return BEMPX_WriteLogFile( output.toLocal8Bit().constData(), psNewLogFileName, bBlankFile,
										bSupressAllMessageBoxes, bAllowCopyOfPreviousLog, ppCSVColumnLabels );
}
bool BEMPX_WriteLogFile( const char* output, const char* psNewLogFileName, bool bBlankFile,
                      BOOL bSupressAllMessageBoxes /*=FALSE*/,  // SAC 4/27/03 - added to prevent MessageBoxes during processing
							 bool bAllowCopyOfPreviousLog /*=true*/,   // SAC 9/18/12 - new arg to allow/prevent log file copying
							 const char** ppCSVColumnLabels /*=NULL*/ )   // SAC 12/19/12 - new arg to facilitate project-based CSV analysis result archival
{
   bool ok = TRUE;
   QString sPrevLogFileName, sThisLogFileName;
   // reset log file variables if new log file name provided
   if (psNewLogFileName != NULL)
   {	sThisLogFileName = psNewLogFileName;
   	if (sThisLogFileName.compare( (ppCSVColumnLabels ? esCSVLogFileName : esLogFileName), Qt::CaseInsensitive ) == 0)
   	{	// do NOT set sPrevLogFileName if new & previous log filenames point to same file (to prevent copying log file onto itself) (Com tic #2482)
   	}
   	else
		{	if (ppCSVColumnLabels)   // SAC 12/19/12 - new arg to facilitate project-based CSV analysis result archival
			{	sPrevLogFileName = esCSVLogFileName;
   	   	esCSVLogFileName = psNewLogFileName;
			}
			else
			{	sPrevLogFileName = esLogFileName;
      		esLogFileName = psNewLogFileName;
				esCSVLogFileName = esLogFileName + ".csv";	// SAC 1/9/13 - update CSV log filename as well...
		}	}
   }
	else
   	sThisLogFileName = (ppCSVColumnLabels ? esCSVLogFileName : esLogFileName);

   if (sThisLogFileName.length() > 0)
   {
      QFile logFile;
      QFile* pLogFile = NULL;	// SAC 5/19/14 - added to facilitate log files that remain open throughout processing
		BOOL bLeaveFileOpen = FALSE;

		if (!ssOpenLogPathFile.isEmpty() && ssOpenLogPathFile.compare( sThisLogFileName, Qt::CaseInsensitive ) == 0)
		{	pLogFile = &fileOpenLog;
			bLeaveFileOpen = TRUE;
		}
		else if (!FileCanBeWrittenTo( sThisLogFileName.toLocal8Bit().constData(), FALSE /*bFileMustExist*/ ))
			ok = FALSE;
		else
      {	// open log file
     	   logFile.setFileName( sThisLogFileName );
      	if ( bBlankFile || !FileExists( sThisLogFileName.toLocal8Bit().constData() ) )
      	{	
      	   //ok = (logFile.Open( sThisLogFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite | CFile::osWriteThrough ) != 0);			assert( ok );
      	   ok = logFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );					assert( ok );
				if (ppCSVColumnLabels)
				{	int idx=-1;
					while (ppCSVColumnLabels[++idx])
	   	      	logFile.write( ppCSVColumnLabels[idx] );
				}
      	}
      	else
      	{
      	   //ok = (logFile.Open( sThisLogFileName, CFile::modeWrite | CFile::shareDenyWrite | CFile::osWriteThrough ) != 0);									assert( ok );
      	   //if (ok)  // get to end of file so as not to add to the beginning of the file
      	   //   logFile.SeekToEnd();
      	   ok = logFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );						assert( ok );
      	}
			if (ok)
			{	fileOpenLog.setPermissions( QFile::ReadOther | QFile::WriteOwner );
				pLogFile = &logFile;
			}
		}

      if ( !ok )
      {  if (!bSupressAllMessageBoxes)  // SAC 4/27/03
            // post error message
            BEMMessageBox( QString( "Error opening file: %1" ).arg( sThisLogFileName ), "", 2 /*warning*/ );
      }
      else
      {	bool bReOpenAndLeaveOpen = false;	// SAC 11/16/18 - revision to retain same log file writing mode when doing SaveAs... (related to copying previous log file)
         // if psNewLogFileName specified, then we first copy contents
         // of old log file into this log file before proceeding
         if ( sPrevLogFileName.length() > 0 && !bBlankFile && bAllowCopyOfPreviousLog )
         {	bReOpenAndLeaveOpen = (!ssOpenLogPathFile.isEmpty() && ssOpenLogPathFile.compare( sPrevLogFileName, Qt::CaseInsensitive ) == 0);		// SAC 11/16/18
            CopyOtherLogFile( *pLogFile, (const char*) sPrevLogFileName.toLocal8Bit().constData() );
         }

			if (ppCSVColumnLabels && strlen(output) > 1 && output[strlen(output)-1] == '\n')
	         pLogFile->write( output );
			else
      	{	QString timeStamp;
				if (!ppCSVColumnLabels && sbLogTimeStamps)  // SAC 11/17/13 - added logic to prevent output of timestamps on regular log messages)
      		{
					QDateTime locTime = QDateTime::currentDateTime();
					timeStamp = locTime.toString("yyyy-MM-dd HH:mm:ss - ");
				}
      		else if (!ppCSVColumnLabels)
					timeStamp = "- ";
			// SAC 1/15/18 - added trailing spaces to timeStamp above and removed from format statements below to prevent space char @ beginning of lines where timeStamp is empty (writes to .log.csv files)

				// write date/time stamp and output string to file
				QString sOut = QString("%1%2\n").arg( timeStamp, output );
         	pLogFile->write( sOut.toLocal8Bit().constData() );

				if (!bLeaveFileOpen)
				{	pLogFile->flush();
					pLogFile->close();
				}
      	}

      	if (bReOpenAndLeaveOpen)	// SAC 11/16/18
				BEMPX_OpenLogFile( sThisLogFileName.toLocal8Bit().constData(), false /*bBlankFile*/ );
      }
   }
	return ok;
}


/////////////////////////////////////////////////////////////////////////////
//  END  OF  CProjectFile  CLASS  FUNCTIONS
/////////////////////////////////////////////////////////////////////////////

#include "memLkRpt.h"

static QString ssRulesetFilename;

static bool ReadXMLFile( const char* fileName, int iFileMode, /*int iBEMProcIdx,*/ long lDBIDVersion, int iBEMProcIdx,
								 QString& sRulesetFilename, BOOL bReturnRulesetFilename,
                         int iMaxDBIDSetFailures, int* piDBIDSetFailures,  // SAC 5/12/00 - enable UI reporting of failed data setting
                         BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
                         int* piObjIdxSetFailures /*=NULL*/, QStringList* psaDataSetFailures /*=NULL*/,   // SAC 7/10/03 - added to facilitate more informative error reporting
								 BOOL bLogDurations /*=FALSE*/, BOOL bStoreData /*=TRUE*/,   // SAC 10/24/13 - added duration logging  // SAC 10/29/13 - added bStoreData
								 int* piObjPropCounts /*=NULL*/, BEMStraightMap* pStraightMap,    // SAC 10/30/13 - added to facilitate bulk memory allocation of CBEMObject & CBEMProperty objects
								 BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap, 			// SAC 5/7/14 - added BEMComponentMap & BEMPropertyMap pointers to handle more comprehensive backward compatibility
								 const char* pszClassPrefix );		// SAC 10/24/18 - added pszClassPrefix

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_ReadProjectFile()
//
// Purpose ------------------------------------------------------------------
//   Read the contents of a project file into the building database
//   
// Arguments ----------------------------------------------------------------
//   const char* fileName      : name of file to read
//   BOOL        bIsInputMode  : flag indicating whether or not a user input file is to be read
//   BOOL        bRestore      : flag indicating user input design is being restored into database
//   BOOL        bResultsOnly  : flag indicating whether or not to only read results from the file
//   const char* pszLogFileExt : file extension used for log (NULL => '.LOG')
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
//#define  BEMFM_INPUT   0  // SAC 5/22/12 - added new "simulation" mode
//#define  BEMFM_DETAIL  1
//#define  BEMFM_SIM     2
bool BEMPX_ReadProjectFile(  const char* fileName, int iFileMode /*bool bIsInputMode*/, bool bRestore /*=FALSE*/,
                             bool bResultsOnly /*=FALSE*/, const char* pszLogFileNameOrExt /*=NULL*/,
                             int iBEMProcIdx /*=-1*/, long lDBIDVersion /*=0*/,
                             // SAC 5/12/00 - added following args to enable UI reporting of failed data setting
                             int iMaxDBIDSetFailures /*=0*/, int* piDBIDSetFailures /*=NULL*/,
                             BEMStraightMap* pStraightMap /*=NULL*/,  // SAC 11/14/01 - added another method of mapping old properties to new
                             // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
                             BEMComponentMap* pCompMap /*=NULL*/, BEMPropertyMap* pPropMap /*=NULL*/,
                             BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
                             int* piObjIdxSetFailures /*=NULL*/, QStringList* psaDataSetFailures /*=NULL*/,   // SAC 7/10/03 - added to facilitate more informative error reporting
										BOOL bLogDurations /*=FALSE*/, const char* pszClassPrefix /*=NULL*/ )  // SAC 10/24/13 - added duration logging
{
   bool bRetVal = TRUE;
	if (iBEMProcIdx < 0)  // SAC 3/13/13
		iBEMProcIdx = eActiveBEMProcIdx;

//   ebAllowAzimuthOrientationDefaulting = FALSE;

	QString sFileName = fileName;
	QString sFileExt  = (sFileName.lastIndexOf('.') > 0 ? sFileName.right( sFileName.length() - sFileName.lastIndexOf('.') - 1 ) : "");

	ptime t1(microsec_clock::local_time());  // SAC 10/24/13 - added duration logging

      // reset log file name
	QString sLoc_esLogFileName;
   QString sLogFileNameOrExt = pszLogFileNameOrExt;
   if (sLogFileNameOrExt.length() > 4 && (sLogFileNameOrExt.lastIndexOf( '\\' ) > 0 || sLogFileNameOrExt.lastIndexOf( '/' ) > 0) && sLogFileNameOrExt.lastIndexOf( '.' ) > 0)
      sLoc_esLogFileName = sLogFileNameOrExt;
   else
   {
      assert( sLogFileNameOrExt.length() <= 4 );  // we will most likely keep log file extensions to 3 or fewer characters (excluding the '.')
      QString logFileName = sFileName;
      int iLastSlashIdx = std::max( logFileName.lastIndexOf( '\\' ), logFileName.lastIndexOf( '/' ) );
      int iLastDotIdx   = logFileName.lastIndexOf( '.' );
      int iBEMFileExtLen = ((iLastSlashIdx > 0 && iLastSlashIdx < iLastDotIdx) ? logFileName.length() - iLastDotIdx : 0);
      sLoc_esLogFileName = logFileName.left( logFileName.length() - iBEMFileExtLen );
      if (pszLogFileNameOrExt == NULL || strlen( pszLogFileNameOrExt ) < 1)
         sLoc_esLogFileName += ".log";
      else
         sLoc_esLogFileName += pszLogFileNameOrExt;
   }

// SAC 11/28/04 - Added some code to provide more informative messages
   QString sFileNameOnly = sFileName;
   if (!sFileNameOnly.isEmpty())
   {
      int iLastSlashIdx = std::max( sFileNameOnly.lastIndexOf( '\\' ), sFileNameOnly.lastIndexOf( '/' ) );
      if (iLastSlashIdx > 10)
      {
         QString sTempPath = sFileNameOnly.left( iLastSlashIdx );
         int iPrevSlashIdx = std::max( sTempPath.lastIndexOf( '\\' ), sTempPath.lastIndexOf( '/' ) );
         if (iPrevSlashIdx > 10  &&  (sFileNameOnly.length() - iPrevSlashIdx) < 80)
            iLastSlashIdx = iPrevSlashIdx;
      }
      sFileNameOnly = sFileNameOnly.right( sFileNameOnly.length() - iLastSlashIdx - 1 );
   }

   QString sMsg;
   int iFileExtLen = sFileExt.length();
	if (sFileExt.compare("xml", Qt::CaseInsensitive) == 0 || (iFileExtLen > 3 && (sFileExt[iFileExtLen-1] == 'x' || sFileExt[iFileExtLen-1] == 'X')))
	{	assert( !bRestore );
		assert( !bResultsOnly );
		assert( iBEMProcIdx == 0 );
		//assert( pCompMap == NULL && pPropMap == NULL );

		if (!sLoc_esLogFileName.isEmpty())
		{	esLogFileName = sLoc_esLogFileName;
			esCSVLogFileName = esLogFileName + ".csv";  // SAC 12/19/12
		}

	   // write message to log file
	   BEMPX_WriteLogFile( "-----------------------------------------------------------------------------", NULL, FALSE, bSupressAllMessageBoxes );  // SAC 1/29/14 - add separator for analysis sessions
      sMsg = QString( "Opening Project '%1'..." ).arg( sFileNameOnly );
	   BEMPX_WriteLogFile( sMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03

	// SAC 3/22/14 - added to ensure that Proj:RuleFile SET during XML file reading process => need to read ruleset filename -> eBEMProc PRIOR to creation of Proj object...
		if (iFileMode == BEMFM_INPUT)
	   {	if (ReadXMLFile( fileName, BEMFM_INPUT /*iFileMode*/, 0 /*lDBIDVersion*/, 0 /*iBEMProcIdx*/, ssRulesetFilename, TRUE /*bReturnRulesetFilename*/, 0 /*iMaxDBIDSetFailures*/,
								NULL /*piDBIDSetFailures*/, FALSE /*bSupressAllMessageBoxes*/, NULL /*piObjIdxSetFailures*/, NULL /*psaDataSetFailures*/, FALSE /*bLogDurations*/,
								TRUE /*bStoreData*/, NULL /*piObjPropCounts*/, NULL /*pStraightMap*/, NULL, NULL, NULL ) && !ssRulesetFilename.isEmpty())
	         BEMPX_SetRulesetFilename( ssRulesetFilename.toLocal8Bit().constData() );
		}

		QString sJunk;
#ifdef _DEBUG
		int iaObjPropCounts[] = {0,0};
	   ReadXMLFile( fileName, iFileMode, /*int iBEMProcIdx,*/ lDBIDVersion, iBEMProcIdx, sJunk, FALSE /*bReturnRulesetFilename*/,
									iMaxDBIDSetFailures, piDBIDSetFailures, bSupressAllMessageBoxes, piObjIdxSetFailures, psaDataSetFailures,
                           bLogDurations, FALSE /*bStoreData*/, iaObjPropCounts, pStraightMap, pCompMap, pPropMap, pszClassPrefix );
	// perform BULK allocation of ALL BEMObject & BEMProperty objects
		if (bLogDurations)
		{  sMsg = QString( "      BEMPX_ReadProjectFile() - allocating %1 objects and %2 properties to import model into" ).arg( QString::number(iaObjPropCounts[0]), QString::number(iaObjPropCounts[1]) );
		   BEMPX_WriteLogFile( sMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03
		}
#endif
	   bRetVal = ReadXMLFile( fileName, iFileMode, /*int iBEMProcIdx,*/ lDBIDVersion, iBEMProcIdx, sJunk, FALSE /*bReturnRulesetFilename*/,
									iMaxDBIDSetFailures, piDBIDSetFailures, bSupressAllMessageBoxes, piObjIdxSetFailures, psaDataSetFailures,
									bLogDurations, TRUE /*bStoreData*/, NULL, pStraightMap, pCompMap, pPropMap, pszClassPrefix );
	}
	else
	{
   	CProjectFile* file = new CProjectFile( sFileName.toLocal8Bit().constData(), iFileMode /*bIsInputMode*/, lDBIDVersion, 0,
   	                                       BEMTextIO::load, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03
   	if ( file->IsOpen() )
   	{
			if (!sLoc_esLogFileName.isEmpty())
			{	esLogFileName = sLoc_esLogFileName;
				esCSVLogFileName = esLogFileName + ".csv";  // SAC 12/19/12
			}

   	   if (bRestore)
   	      sMsg = QString( "Restoring Input Design from '%1'..." ).arg( sFileNameOnly );
   	   else if (bResultsOnly)
   	      sMsg = QString( "Retrieving Results from '%1'..." ).arg( sFileNameOnly );
   	   else
			{	BEMPX_WriteLogFile( "-----------------------------------------------------------------------------", NULL, FALSE, bSupressAllMessageBoxes );  // SAC 1/29/14 - add separator for analysis sessions
   	      sMsg = QString( "Opening Project '%1'..." ).arg( sFileNameOnly );
			}
   	   // write message to log file
   	   BEMPX_WriteLogFile( sMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03

   	   // call appropriate Read function
   	   if (!bResultsOnly)
   	   {
   	      if (!file->Read( iBEMProcIdx, iMaxDBIDSetFailures, piDBIDSetFailures, piObjIdxSetFailures,
   	                       psaDataSetFailures, pStraightMap, pCompMap, pPropMap, bLogDurations ))
   	         bRetVal = FALSE;  // SAC 4/27/03
   	   }
   	   else
   	      file->ReadResults( iBEMProcIdx );
   	}
   	else
   	   bRetVal = FALSE;  // SAC 4/27/03

   	delete file;
	}

//   ebAllowAzimuthOrientationDefaulting = TRUE;

// SAC 3/21/06 - added code to reset all active component indexes to the FIRST in the list, rather than leaving them as the last
   if (bRetVal && !bResultsOnly)
      for (int iCls = BEMPX_GetNumClasses(); iCls >= 0; iCls--)
      {
         if (BEMPX_GetNumObjects( iCls, BEMO_User, iBEMProcIdx ) > 0)
            BEMPX_SetActiveObjectIndex( iCls, 0, BEMO_User, iBEMProcIdx );
      }

	if (bLogDurations)  // SAC 10/24/13 - added duration logging
	{	ptime t2(microsec_clock::local_time());
		time_duration td = t2-t1;
		QString sLogMsg = QString( "      BEMPX_ReadProjectFile() - elapsed time: %1" ).arg( QString::number(((double) td.total_microseconds()) / 1000000.0, 'f', 3) );  // -or- %s -> to_simple_string(td).c_str() );
	   BEMPX_WriteLogFile( sLogMsg );
	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// Exported Function:  BEMPX_WriteProjectFile()
/////////////////////////////////////////////////////////////////////////////

static char sszRulePathFile[MAX_PATH+1];

const char* BEMPX_GetRulesetFilenameFromProjectFile( const char* fileName )
{
	QString sFileName = fileName;
	QString sFileExt  = (sFileName.lastIndexOf('.') > 0 ? sFileName.right( sFileName.length() - sFileName.lastIndexOf('.') - 1 ) : "");

   int iFileExtLen = sFileExt.length();
	if (sFileExt.compare("xml", Qt::CaseInsensitive) == 0 || (iFileExtLen > 3 && (sFileExt[iFileExtLen-1] == 'x' || sFileExt[iFileExtLen-1] == 'X')))	// SAC 10/30/15
	{	ssRulesetFilename.clear();		// SAC 12/4/15 - blast previous ssRulesetFilename in order to ensure that the ruleset filename indeed IS read in (and not ignored)
	   if (!ReadXMLFile( fileName, BEMFM_INPUT /*iFileMode*/, 0 /*lDBIDVersion*/, 0 /*iBEMProcIdx*/, ssRulesetFilename, TRUE /*bReturnRulesetFilename*/,
								0 /*iMaxDBIDSetFailures*/, NULL /*piDBIDSetFailures*/, FALSE /*bSupressAllMessageBoxes*/,
								NULL /*piObjIdxSetFailures*/, NULL /*psaDataSetFailures*/, FALSE /*bLogDurations*/, TRUE /*bStoreData*/, NULL /*piObjPropCounts*/, NULL, NULL, NULL, NULL ))
			ssRulesetFilename.clear();
	}
	else
	{
   	CProjectFile* file = new CProjectFile( fileName );
   	if (file->IsOpen())
   	   file->ReadRulesetFilename( ssRulesetFilename );
   	delete file;
	}

   if (ssRulesetFilename.length() > 0)
	{	assert( ssRulesetFilename.length() <= MAX_PATH );
		if (ssRulesetFilename.length() <= MAX_PATH)
		{
#pragma warning(disable : 4996)
			strncpy( sszRulePathFile, ssRulesetFilename.toLocal8Bit().constData(), MAX_PATH );
			sszRulePathFile[MAX_PATH] = '\0';
#pragma warning(default : 4996)
			return (const char*) sszRulePathFile;
		}
		else
			return NULL;
	}
   else
      return NULL;
}

static bool WriteXMLFile( const char* pszFileName, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, BOOL bSupressAllMessageBoxes,
									bool bAppend, const char* pszModelName, bool bWriteTerminator, int iBEMProcIdx /*=-1*/, bool bOnlyValidInputs );		// SAC 2/19/13 - added trailing arguments to facilitate writing of multiple models into a single XML file  // SAC 4/16/14

/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_WriteProjectFile()
//
// Purpose ------------------------------------------------------------------
//   Write the contents of the database to a project file.
//   
// Arguments ----------------------------------------------------------------
//   const char* fileName     : name of the file to write
//   BOOL        bIsInputMode : flag indicating what mode to write the file in
//   
// Return Value -------------------------------------------------------------
//   TRUE always.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// SAC 8/30/11 - added new argument to facilitate the writing of CSE input files directly from BEMProc databases
//		iFileType Options:	0 => standard (or detailed) BEMProc text file
//									1 => CSE input file w/ following customizations:
//													No "RulesetFilename..." written @ top of file
//													No "END_OF_FILE" @ end of file
//													Only component types whose names are in all caps
//													Only properties that begin w/ a lower case letter get written to CSE components
//													Omit component names that exceed 15 characters in length
//													Write ANY defined properties meeting other restrictions (not just user inputs)
//													Do not write any delimeter ('..') following component definitions
//												(future related changes once this is written as a CSE and not include file)
//													Utilization of DataType flag value denoting which properties are to be written to CSE file
//													Replace component type writing requiring all caps w/one that checks all properties for at least one that is a CSE simulation input
//													Writing of TOP properties w/ no leading component type record
//													Writing of "RUN" at the end of the file
//													Ability to specify "#include" statements at certain points in the CSE file
//									2 => XML file (via Qt) - added 10/26/11
// SAC 4/16/14 - added bOnlyValidInputs argument - when true, checks properties for whether they are "valid input properties" before writing them to the file (shold be true only when writing INPUT files)
bool BEMPX_WriteProjectFile( const char* fileName, int iFileMode /*bool bIsInputMode*/, bool bUseLogFileName, bool bWriteAllProperties,  // SAC 1/15/03
                           BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
								   int iFileType /*=0*/,    // SAC 8/30/11 - added iFileType argument
									bool bAppend /*=false*/, const char* pszModelName /*=NULL*/, bool bWriteTerminator /*=true*/, 		// SAC 2/19/13 - added trailing arguments to facilitate writing of multiple models into a single XML file
									int iBEMProcIdx /*=-1*/, long lModDate /*=-1*/, bool bOnlyValidInputs /*=false*/,    // SAC 3/18/13  // SAC 6/26/13
									bool bAllowCreateDateReset /*=true*/,		// SAC 1/12/15 - added bAllowCreateDateReset to prevent resetting this flag when storing detailed version of input file
									int iPropertyCommentOption /*=0*/, 			// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
									std::vector<long>* plaClsObjIndices /*=NULL*/, 		// SAC 12/14/18 - added to facilitate writing of specific object type/index elements to CSE input files (initially for HPWH sizing runs - HPWHSIZE)
								   bool bReportInvalidEnums /*=true*/ )		// SAC 5/20/19 - prevent logging errors associated w/ invalid enums (for writing of .ribd##i inputs during analysis)
{
	bool bRetVal = true;

   QString sFileName;
   if (bUseLogFileName)
   {  // fileName argument is simply a file extension which should get appended onto the Log filename
      sFileName = esLogFileName.left( esLogFileName.lastIndexOf( '.' )+1 );
      sFileName += fileName;
   }
   else
      sFileName = fileName;

   if (iFileMode == BEMFM_INPUT /*bIsInputMode*/ && iFileType != BEMFT_CSE && !BEMPX_IsHPXML( iFileType ))   // SAC 8/30/11	// SAC 12/2/15
   {
      // Get current time and set last modified and creation dates
   //   CTime time = CTime::GetCurrentTime();
   //   long lTime = (long) (lModDate > 0 ? lModDate : time.GetTime());
		QDateTime current = QDateTime::currentDateTime();
		long lTime = (long) (lModDate > 0 ? lModDate : current.toTime_t());	// seconds since 1970-Jan-01 / valid as long int until 2038-Jan-19 / switching to uint extends valid date range to 2106-Feb-07
      long lModDBID = BEMPX_GetDatabaseID( "Proj:ModDate" );
      if (lModDBID > 0)
         BEMPX_SetBEMData( lModDBID, BEMP_Int, (void*) &lTime, BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, iBEMProcIdx );
      long lCr8DBID = BEMPX_GetDatabaseID( "Proj:CreateDate" );
      if (lCr8DBID > 0 && bAllowCreateDateReset)	// SAC 1/12/15
      {
         BOOL bSetCr8 = (!FileExists( sFileName.toLocal8Bit().constData() ));   // set cr8 time if file doesn't exist yet

         if (!bSetCr8)
         {
      //      int iDT, iSV, iError;
      //      void* pData = BEMPX_GetBEMData( lCr8DBID, iDT, iSV, iError, -1, BEMO_User, FALSE, iBEMProcIdx );
      //      if ( (iError >= 0) && (pData != NULL) )
      //      {
      //         long lNewVal = *((long*) pData);
      //         bSetCr8 = (lNewVal <= 0);   // set cr8 time if current cr8 time = 0
      //      }
				long lNewVal;
				if (BEMPX_GetInteger( lCr8DBID, lNewVal, 1, -1,	-1, BEMO_User, iBEMProcIdx ) && lNewVal <= 0)
					bSetCr8 = TRUE;
         }

         if (bSetCr8)
            BEMPX_SetBEMData( lCr8DBID, BEMP_Int, (void*) &lTime, BEMO_User, -1, BEMS_UserDefined, BEMO_User, TRUE, iBEMProcIdx );
      }
   }

	if (iFileType == BEMFT_CSE)	// SAC 6/1/18 - loop over ALL CSE objects and rename any that have names > 63 chars long (Com tic #2452)
	{
		int iNumClasses = BEMPX_GetNumClasses();
		for (int i1Class=1; i1Class<=iNumClasses; i1Class++)
		{	int iError;
			BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
			if (iError >= 0 && pClass && (iFileMode != BEMFM_INPUT || !pClass->getAutoCreate()))
			{	QString sObjType = pClass->getShortName();
				if (sObjType.indexOf( "cse" ) == 0)
				{	int iMaxNameLen = (sObjType.compare("cseDHWSYS")==0 ? MAX_CSE_NAMELENGTH-3 : MAX_CSE_NAMELENGTH);     // trim DHWSYS names by additional 3 chars to allow space for DayUse shuffle copy names - SAC 05/13/21
               int iNumObjs = (int) pClass->ObjectCount( BEMO_User );
					for (int ib=0; ib < iNumObjs; ib++)
					{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
						QString sObjName = (pObj==NULL ? "" : pObj->getName());
      	   	   if (pObj && sObjName.length() > iMaxNameLen)
         		   {	QString sAppend = QString( "-%1.%2" ).arg( QString::number(i1Class), QString::number(ib+1) );
         		   	sObjName = sObjName.left( iMaxNameLen-sAppend.length() );
         		   	sObjName += sAppend;
         		   	pObj->setName(sObjName);
   	}	}	}	}	}
	}

   if (BEMPX_IsXML( iFileType ))   // SAC 10/26/11
   	bRetVal = WriteXMLFile( sFileName.toLocal8Bit().constData(), iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bSupressAllMessageBoxes,
										bAppend, pszModelName, bWriteTerminator, iBEMProcIdx, bOnlyValidInputs );		// SAC 2/19/13 - added trailing arguments to facilitate writing of multiple models into a single XML file
	else
	{
   	CProjectFile* file = new CProjectFile( sFileName.toLocal8Bit().constData(), iFileMode /*bIsInputMode*/, 0, 0, BEMTextIO::store, bWriteAllProperties,  // SAC 1/15/03
   	                                       bSupressAllMessageBoxes, iFileType, bOnlyValidInputs, iPropertyCommentOption,   // SAC 4/27/03  // SAC 12/5/16
															plaClsObjIndices, bReportInvalidEnums );		// SAC 12/14/18 - writing of specific object type/index elements   // SAC 5/20/19 - bReportInvalidEnums
   	if ( file->IsOpen() )
   	   file->WriteProjectFile( iBEMProcIdx );
   	
   	delete file;
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  BEMPX_()
//
/////////////////////////////////////////////////////////////////////////////
bool  BEMPX_WriteProjectComponent( const char* fileName, BEMObject *pObj, int iBEMProcIdx /*=-1*/, bool bWriteAllProperties /*=false*/,
												bool bWritePrimaryDefaultData /*=false*/ )		// SAC 6/8/15 - CBECC issue 1061
{
//   std::auto_ptr<CProjectFile> file( new CProjectFile( QString(fileName), FALSE, BEMTextIO::store ) );
   std::auto_ptr<CProjectFile> file( new CProjectFile( fileName, BEMFM_INPUT /*TRUE*/, 0, 0, BEMTextIO::store, bWriteAllProperties ) );

   if ( file->IsOpen() )
   {  // set flag to ensure library data will get written out
      file->SetWriteLibDataFlag( TRUE );
      file->SetWriteAssignedCompsFlag( TRUE );
      file->ResetComponentNameList();

      file->WriteComponent( pObj, iBEMProcIdx, bWritePrimaryDefaultData );  // this one call writes the component + all referenced & child components

      file->WriteEndOfFileMarker( iBEMProcIdx );

      return true;
   }
   else
   {
      return false;
   }
}


/////////////////////////////////////////////////////////////////////////////
//
// Imported Function:  BEMPX_()
//
/////////////////////////////////////////////////////////////////////////////
BEMObject* BEMPX_ReadProjectComponent(  const char* fileName, int i1BEMClass, int iBEMProcIdx /*=-1*/ )
{
   BEMObject* pRetVal = NULL;
   BEMObject* pFirstObj = NULL;     // SAC 10/21/21

   std::auto_ptr<CProjectFile> file( new CProjectFile( fileName, BEMFM_INPUT /*TRUE*/ ) );

   if ( file->IsOpen() )
   {
      file->SetPastingClassFromClipboard( i1BEMClass );
      file->ResetComponentNameList();     // reset list of components which were renamed during last read
      file->ResetNewComponentNameList();  // reset list of new names for renamed components during last read

      BEMObject* pNewObj = NULL;
      int iJunk = 0;
      // read all component definitions contained in the file until the end-of-file marker is found
      do
      {
         pNewObj = file->ReadComponent( iJunk );

         if (pNewObj && pFirstObj == NULL)
            pFirstObj = pNewObj;     // return this first object if the main one not found - CAN HAPPEN when pasting across different programs or versions - SAC 10/21/21 (MFam)

         // store this object pointer as the return value if its class matches the function argument
         if ((pRetVal == NULL) && pNewObj && pNewObj->getClass() && pNewObj->getClass()->get1BEMClassIdx() == i1BEMClass)
            pRetVal = pNewObj;

      } while (pNewObj != NULL);

      // resolve all object references - this is necessary because all object assignments are
      // originally read and stored simply as character string names of the referenced objects.
      // This function resolves those object names to actual object pointers.
      // This object resolving cannot happen during the reading process, since an object
      // can be assigned PRIOR to its definition in the file.
      BEMP_ResolveAllReferences( BEMO_User, NULL, TRUE, iBEMProcIdx );
   }

   return (pRetVal ? pRetVal : pFirstObj);
}


/////////////////////////////////////////////////////////////////////////////

const char* pszPropTypeTypes[] = {	"Integer    "		// BEMP_Int  0
											 , "Float      "		// BEMP_Flt  1
											 , "Enumeration"		// BEMP_Sym  2
											 , "String     "		// BEMP_Str  3
											 , "ObjectRef  "		// BEMP_Obj  4
											 };

//#define  BEMDMX_SIM    0  // SAC 8/23/12 - added export of simulation data model to facilitate synchronization of data model w/ other program modules
//#define  BEMDMX_INP    1  // SAC 2/26/13 - added input version of DM export
//#define  BEMDMX_INPMP  2  // SAC 10/31/13 - added input version of DM export that EXCLUDES Prescribed properties (MP-minus precribed)
bool BEMPX_WriteDataModelExport( int iExportType, const char* pszDataModelOutFile, bool bWritePrevNames /*=false*/ )    // bWritePrevNames - SAC 08/05/21 (MFam)
{	bool bRetVal = true;
   QFile file;		file.setFileName( pszDataModelOutFile );
   try
   {  // open file
      //if (file.Open( pszDataModelOutFile, CFile::modeCreate | CFile::modeWrite ) != 0)
      if (file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ))
      {
			//CTime time = CTime::GetCurrentTime();
			//CString sTimeStamp = time.Format("%Y-%b-%d %H:%M:%S\n");
			QDateTime locTime = QDateTime::currentDateTime();
			QString sTimeStamp = locTime.toString("yyyy-MMM-dd HH:mm:ss\n");
			file.write( sTimeStamp.toLocal8Bit().constData() );

         QString sLine, sTemp, sTemp2;
			int iError;
			int iNumPropsWritten = 0;
   	   for (int iC1=0; iC1 < eBEMProc.getNumClasses(); iC1++)
			{	int iNumPropsWrittenThisClass = 0;
				int iNumPropsOfClassToBeWritten = 0, iP1=0;
            for (; iP1 < eBEMProc.getClass(iC1)->getNumProps(); iP1++)
   	      {  int iProp1 = eBEMProc.getClass(iC1)->getFirstPropID() + iP1;
					int iPropDataType = BEMPX_GetCompDataType( BEMPX_GetDBID( (iC1+1), (iP1+1), 1 /*i1Array*/ ) );
					if ( (iExportType == BEMDMX_INP   && iPropDataType < BEMD_NotInput  ) ||	// SAC 4/4/13 - modified to allow Prescribed data to be modified/read/written.  Was:  Prescribed) ||
						  (iExportType == BEMDMX_INPMP && iPropDataType < BEMD_Prescribed) ||	// SAC 10/31/13
						  (iExportType == BEMDMX_SIM   && eBEMProc.getPropertyType(iProp1)->getWriteSimulationFlag() > 0) )
						iNumPropsOfClassToBeWritten++;
				}

				if (iNumPropsOfClassToBeWritten > 0 || eBEMProc.getClass(iC1)->getNumProps() < 1 || eBEMProc.getClass(iC1)->getXMLIgnoreName())	// SAC 1/28/14 - don't write object at all if we have no properties to write (unless this obj has no props at all)
				{
                  QString sClsShortName = (bWritePrevNames && eBEMProc.getClass(iC1)->getNumPreviousNames() > 1 ? eBEMProc.getClass(iC1)->getPreviousName(0) : eBEMProc.getClass(iC1)->getShortName());  // SAC 08/05/21
                  QString sClsLongName  = (bWritePrevNames && eBEMProc.getClass(iC1)->getNumPreviousNames() > 1 ? eBEMProc.getClass(iC1)->getPreviousName(1) : eBEMProc.getClass(iC1)->getLongName( ));
						if (iExportType == BEMDMX_INP || iExportType == BEMDMX_INPMP)
							sLine = QString::asprintf( "\n--------------------\n%-16s  %-32s  #Props:%3d/%3d  MaxDefinable:%5d\n", 
								  /*eBEMProc.getClass(iC1)->m_i1BEMClassIdx,*/ sClsShortName.toLocal8Bit().constData(), sClsLongName.toLocal8Bit().constData(), iNumPropsOfClassToBeWritten, eBEMProc.getClass(iC1)->getNumProps()
								, eBEMProc.getClass(iC1)->getMaxDefinable()	);
						else
							sLine = QString::asprintf( "\n--------------------\n%-16s  %-32s  #Props:%3d/%3d  MaxDefinable:%5d  SingleRecord: %c  XMLIgnoreName: %c\n", 
								  /*eBEMProc.getClass(iC1)->m_i1BEMClassIdx,*/ sClsShortName.toLocal8Bit().constData(), sClsLongName.toLocal8Bit().constData(), iNumPropsOfClassToBeWritten, eBEMProc.getClass(iC1)->getNumProps()
								, eBEMProc.getClass(iC1)->getMaxDefinable(), (eBEMProc.getClass(iC1)->getWriteAsSingleRecord() ? 'T':'F')
								, (eBEMProc.getClass(iC1)->getXMLIgnoreName() ? 'T':'F')
							//	, eBEMProc.getClass(iC1)->, eBEMProc.getClass(iC1)->, eBEMProc.getClass(iC1)->
								);
						file.write( sLine.toLocal8Bit().constData() );
						if (eBEMProc.getClass(iC1)->getParentType(0) > 0)
						{  sTemp = "                               Parent(s):  ";
							for (int iPar=0; (iPar < BEM_MAX_PARENT_TYPES && eBEMProc.getClass(iC1)->getParentType( iPar ) > -1); iPar++)
							{	if (iPar > 0)
									sTemp += "  /  ";
                        if (bWritePrevNames && eBEMProc.getClass( eBEMProc.getClass(iC1)->getParentType( iPar ) )->getNumPreviousNames() > 1)    // SAC 08/05/21
                           sTemp += eBEMProc.getClass( eBEMProc.getClass(iC1)->getParentType( iPar ) )->getPreviousName(0);
                        else
      							sTemp += eBEMProc.getClass( eBEMProc.getClass(iC1)->getParentType( iPar ) )->getShortName();
							}
							sTemp += "\n";
							file.write( sTemp.toLocal8Bit().constData() );
						}
						if (eBEMProc.getClass(iC1)->getChildType(0) > 0)
						{  sTemp = "                               Children:  ";
							for (int iChld=0; (iChld < BEM_MAX_CHILD_TYPES && eBEMProc.getClass(iC1)->getChildType( iChld ) > -1); iChld++)
							{	if (iChld > 0)
									sTemp += "  /  ";
                        if (bWritePrevNames && eBEMProc.getClass( eBEMProc.getClass(iC1)->getChildType( iChld ) )->getNumPreviousNames() > 1)    // SAC 08/05/21
                           sTemp += eBEMProc.getClass( eBEMProc.getClass(iC1)->getChildType( iChld ) )->getPreviousName(0);
								else
                           sTemp += eBEMProc.getClass( eBEMProc.getClass(iC1)->getChildType( iChld ) )->getShortName();
							}
							sTemp += "\n";
							file.write( sTemp.toLocal8Bit().constData() );
						}
						file.write( "\n" );

            	for (iP1=0; iP1 < eBEMProc.getClass(iC1)->getNumProps(); iP1++)
   	      	{  int iProp1 = eBEMProc.getClass(iC1)->getFirstPropID() + iP1;
						long lDBID = BEMPX_GetDBID( (iC1+1), (iP1+1), 1 /*i1Array*/ );
						int iPropDataType = BEMPX_GetCompDataType( lDBID );
						if ( (iExportType == BEMDMX_INP   && iPropDataType < BEMD_NotInput  ) ||	// SAC 4/4/13 - modified to allow Prescribed data to tbe modified/read/written.  Was:  Prescribed) ||
							  (iExportType == BEMDMX_INPMP && iPropDataType < BEMD_Prescribed) ||	// SAC 10/31/13
							  (iExportType == BEMDMX_SIM   && eBEMProc.getPropertyType(iProp1)->getWriteSimulationFlag() > 0) )
						{
							// now write PropertyType
							QString sLongName = eBEMProc.getPropertyType(iProp1)->getDescription();  // mods to prevent overrun of property long name / description
							if (sLongName.length() > 60)
							{	sLongName = sLongName.left(57);
								sLongName += "...";
							}
					      if (iExportType == BEMDMX_INP || iExportType == BEMDMX_INPMP)
							{	QString sDataType, sNumVals, sUnits;
								if (!eBEMProc.getPropertyType(iProp1)->getInputClassInfo().isEmpty())
									sDataType = "(see next line)";
								else
									switch (iPropDataType)
									{	case BEMD_Compulsory   :	sDataType = "Compulsory input";			break;
										case BEMD_Required     :	sDataType = "Required input";				break;
										case BEMD_CondRequired :	sDataType = "CondRequired input";		break;	// SAC 2/11/15
										case BEMD_Optional     :	sDataType = "Optional input";				break;
										case BEMD_Default      :	sDataType = "Defaulted input";			break;
										case BEMD_CriticalDef  :	sDataType = "CriticalDef input";			break;
										case BEMD_Prescribed   :	sDataType = "Prescribed";					break;
										case BEMD_NotInput     :	sDataType = "NotInput";						break;
										default                :	sDataType = "unknown input type";		break; 
									}
								if (eBEMProc.getPropertyType(iProp1)->getNumValues() > 1)
									sNumVals = QString::asprintf( "#Vals:%3d", eBEMProc.getPropertyType(iProp1)->getNumValues() );
								else
									sNumVals = " -  -  - ";
								if (!eBEMProc.getPropertyType(iProp1)->getUnitsLabel().isEmpty())
								//	sUnits = QString::asprintf( "Units: %-17s", eBEMProc.getPropertyType(iProp1)->getUnitsLabel().toLatin1().constData() );
									sUnits = QString( "Units: %1" ).arg( eBEMProc.getPropertyType(iProp1)->getUnitsLabel(), -17 );
								else
									sUnits = " -  -  -  -  -  -  -  - ";
								QString sRangeMsg;
								BEMPX_GenerateRangeMessage( lDBID, &sRangeMsg, -1, FALSE /*bIncludeUnits*/ );
					         sLine = QString( "      %1  %2  %3  %4  %5  %6 %7\n" ).arg( eBEMProc.getPropertyType(iProp1)->getShortName(), -24 ).arg( sLongName, -60 ).arg(
										  pszPropTypeTypes[ eBEMProc.getPropertyType(iProp1)->getPropType() ], sNumVals, sUnits ).arg( sDataType, -18 ).arg( sRangeMsg );
							// avoid sprintf() to preserve special characters in units strings
					      //   sLine = QString::asprintf( "      %-24s  %-60s  %s  %s  %s  %-18s %s\n",    // MaxDefinable:%5d  MaxRefs:%3d", 
							//			  eBEMProc.getPropertyType(iProp1)->getShortName().toLocal8Bit().constData(), sLongName.toLocal8Bit().constData()  //, eBEMProc.getPropertyType(iProp1)->m_i1PropTypeIdx
							//			, pszPropTypeTypes[ eBEMProc.getPropertyType(iProp1)->getPropType() ], sNumVals.toLocal8Bit().constData()
							//			, sUnits.toLatin1().constData(), sDataType.toLocal8Bit().constData(), sRangeMsg.toLocal8Bit().constData()	);
						// SAC 3/3/14 - added subsequent record to write more descriptive info re: input class (when dependent on other BEMBase data)
								if (!eBEMProc.getPropertyType(iProp1)->getInputClassInfo().isEmpty())
								{	file.write( sLine.toLatin1() );
									sLine = QString::asprintf( "      %-24s  %-60s  %-11s  %-9s  %-24s  %s\n", " ", " ", " ", " ", " ", eBEMProc.getPropertyType(iProp1)->getInputClassInfo().toLocal8Bit().constData() );
								}
							}
							else
					         sLine = QString( "      %1  %2  Type: %3  #Vals:%4  Units: %5 WriteSimFlag:%6  WriteXMLArrayIndices: %7\n" ).arg(
										  eBEMProc.getPropertyType(iProp1)->getShortName(), -24 ).arg( sLongName, -60 ).arg(  //, eBEMProc.getPropertyType(iProp1)->m_i1PropTypeIdx
										  pszPropTypeTypes[ eBEMProc.getPropertyType(iProp1)->getPropType() ] ).arg( QString::number( eBEMProc.getPropertyType(iProp1)->getNumValues() ), 3 ).arg(
										  eBEMProc.getPropertyType(iProp1)->getUnitsLabel(), -17 ).arg( QString::number( eBEMProc.getPropertyType(iProp1)->getWriteSimulationFlag() ), 2 ).arg(
										  (eBEMProc.getPropertyType(iProp1)->getXMLWriteArrayIndices() ? 'T':'F') );
							// avoid sprintf() to preserve special characters in units strings
					      //   sLine = QString::asprintf( "      %-24s  %-60s  Type: %s  #Vals:%3d  Units: %-17s WriteSimFlag:%2d  WriteXMLArrayIndices: %c\n",    // MaxDefinable:%5d  MaxRefs:%3d", 
							//			  eBEMProc.getPropertyType(iProp1)->getShortName().toLocal8Bit().constData(), sLongName.toLocal8Bit().constData()  //, eBEMProc.getPropertyType(iProp1)->m_i1PropTypeIdx
							//			, pszPropTypeTypes[ eBEMProc.getPropertyType(iProp1)->getPropType() ], eBEMProc.getPropertyType(iProp1)->getNumValues()
							//			, eBEMProc.getPropertyType(iProp1)->getUnitsLabel().toLatin1().constData(), eBEMProc.getPropertyType(iProp1)->getWriteSimulationFlag()
							//			, (eBEMProc.getPropertyType(iProp1)->getXMLWriteArrayIndices() ? 'T':'F')
							//		//	, eBEMProc.getPropertyType(iProp1)->, eBEMProc.getPropertyType(iProp1)->, eBEMProc.getPropertyType(iProp1)->
							//			);
							//file.write( sLine.toLocal8Bit().constData() );
							// use toLatin1() to preserve special characters in units strings
							file.write( sLine.toLatin1() );
							if (eBEMProc.getPropertyType(iProp1)->getPropType() == BEMP_Obj)
							{	for (int iO=0; iO < BEM_MAX_PROPTYPE_OBJREFCLASSES; iO++)
								{	if (eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO) > 0)
									{
                              QString sRefClsName;
                              if (bWritePrevNames && eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getNumPreviousNames() > 1)    // SAC 08/05/21
                                 sRefClsName = eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getPreviousName(0);
                              else
                                 sRefClsName = eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getShortName();

                              if (eBEMProc.getPropertyType(iProp1)->getObjTypeDBID(iO) > 0)
										{  BEMPX_DBIDToDBCompParamString( eBEMProc.getPropertyType(iProp1)->getObjTypeDBID(iO), sTemp2, false, (bWritePrevNames ? 0 : -1) );
											QString sSymStr;
											if (eBEMProc.getPropertyType(iProp1)->getObjTypeValue(iO) == -99)
											{	// special case where the object dependency is based on the Type of both the referencing and referenced objects being the same
												BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( eBEMProc.getPropertyType(iProp1)->getObjTypeDBID(iO), iError );
												long lLocTypeDBID = ((pObjTypePropType && !pObjTypePropType->getShortName().isEmpty()) ? 
																					BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( lDBID ) ) : 0);
												BEMPropertyType* pLocObjTypePropType = (lLocTypeDBID > 0 ? BEMPX_GetPropertyTypeFromDBID( lLocTypeDBID, iError ) : NULL);
												if (pLocObjTypePropType && !pLocObjTypePropType->getShortName().isEmpty())
												//	sSymStr = QString::asprintf( "%s:%s", eBEMProc.getClass(iC1)->getShortName().toLocal8Bit().constData(), pLocObjTypePropType->getShortName().toLocal8Bit().constData() );
													sSymStr = QString( "%1:%2" ).arg( eBEMProc.getClass(iC1)->getShortName(), pLocObjTypePropType->getShortName() );
											}
											else
												sSymStr = BEMPX_GetSymbolString( eBEMProc.getPropertyType(iProp1)->getObjTypeValue(iO), eBEMProc.getPropertyType(iProp1)->getObjTypeDBID(iO),
																							-1 /*iOccur*/, BEMO_User /*eObjType*/, -1 /*iBEMProcIdx*/, FALSE /*bOnlyFromCurrentSymDepSet*/ );		// SAC 1/15/14 - added final argument to ensure char string reporting
									      if ((iExportType == BEMDMX_INP || iExportType == BEMDMX_INPMP) && !sSymStr.isEmpty())
											{	if (eBEMProc.getPropertyType(iProp1)->getObjTypeValue(iO) == -99)
												//	sTemp = QString::asprintf( "                               %s  (%s = %s)\n", eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getShortName().toLocal8Bit().constData(),
													sTemp = QString( "                               %1  (%2 = %3)\n" ).arg( sRefClsName, sTemp2, sSymStr );
												else
												//	sTemp = QString::asprintf( "                               %s  (%s = \"%s\")\n", eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getShortName().toLocal8Bit().constData(),
													sTemp = QString( "                               %1  (%2 = \"%3\")\n" ).arg( sRefClsName,	sTemp2, sSymStr );
											}
											else
											//	sTemp = QString::asprintf( "                               %s  (%s = %ld)\n", eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getShortName().toLocal8Bit().constData(),
												sTemp = QString( "                               %1  (%2 = %3)\n" ).arg( sRefClsName, sTemp2, QString::number( eBEMProc.getPropertyType(iProp1)->getObjTypeValue(iO) ) );
										}
										else
										//	sTemp = QString::asprintf( "                               %s\n", eBEMProc.getClass(eBEMProc.getPropertyType(iProp1)->getObj1ClassIdx(iO)-1)->getShortName().toLocal8Bit().constData() );
											sTemp = QString( "                               %1\n" ).arg( sRefClsName );
										file.write( sTemp.toLatin1() );
									}
								}
							}
							else if (eBEMProc.getPropertyType(iProp1)->getPropType() == BEMP_Sym)
							{	int iNumSymListsWritten = 0;
								for (int iSDS=0; iSDS < eBEMProc.getPropertyType(iProp1)->getSymbolList()->getNumSymDependencySets(); iSDS++)
								{	BEMSymDependencySet* pSDS = eBEMProc.getPropertyType(iProp1)->getSymbolList()->getSymDependencySet(iSDS);			assert( pSDS );
									if (pSDS && pSDS->getDepValue(0) > -1001)   // dep values < -1000 assumed to be backward compatibility-related, and we don't want to echo those symbol lists here
									{	int i, iNumDeps=0;
										for (i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)		// added prelim loop to check to see if any non-wilcard dependencies are defined - SAC 8/22/17
										{	if (pSDS->getCompParam(i) > 0 && pSDS->getDepValue(i) != -999)
												iNumDeps++;
										}
										if (iNumDeps > 0)
										{	bool bFirstThisRnd = true;
											for (i=0; i<MAX_DEP_DBIDS_PER_SYMBOL_LIST; i++)
   										   if (pSDS->getCompParam(i) > 0 && pSDS->getDepValue(i) != -999)
												{	QString sDepSymStr;
													BEMPropertyType* pDepPropType = BEMPX_GetPropertyTypeFromDBID( pSDS->getCompParam(i), iError );
													if (pDepPropType && pDepPropType->getPropType() == BEMP_Sym)
															sDepSymStr = BEMPX_GetSymbolString( (long) pSDS->getDepValue(i), pSDS->getCompParam(i) );
													BEMPX_DBIDToDBCompParamString( pSDS->getCompParam(i), sTemp2, false, (bWritePrevNames ? 0 : -1) );
											      if ((iExportType == BEMDMX_INP || iExportType == BEMDMX_INPMP) && !sDepSymStr.isEmpty())
													//	sTemp = QString::asprintf( "                               %s  %s = \"%s\"\n", (i==0 ? "When:" : " and:"), sTemp2.toLocal8Bit().constData(), sDepSymStr.toLocal8Bit().constData() );
														sTemp = QString( "                               %1  %2 = \"%3\"\n" ).arg( (bFirstThisRnd ? "When:" : " and:"), sTemp2, sDepSymStr );
													else
													//	sTemp = QString::asprintf( "                               %s  %s = %g\n"  , (i==0 ? "When:" : " and:"), sTemp2.toLocal8Bit().constData(), pSDS->getDepValue(i) );
														sTemp = QString( "                               %1  %2 = %3\n" ).arg( (bFirstThisRnd ? "When:" : " and:"), sTemp2, QString::number( pSDS->getDepValue(i) ) );
													file.write( sTemp.toLatin1() );
													bFirstThisRnd = false;
												}
										}
										else if (iSDS > 0 && iNumSymListsWritten > 0)
											file.write( "                               else:\n" );

										sTemp = QString::asprintf( "                                      default:  %ld\n", pSDS->getDefaultValue() );
										file.write( sTemp.toLatin1() );
										for (i=0; i < pSDS->getNumSymbols(); i++)
										{	BEMSymbol* pSym = pSDS->getSymbol(i);						assert( pSym );
											if (pSym)
											//{	sTemp = QString::asprintf( "                                       %6ld:  \"%s\"\n", pSym->getValue(), pSym->getString().toLocal8Bit().constData() );
											{	sTemp = QString( "                                       %1:  \"%2\"\n" ).arg( QString::number( pSym->getValue() ), 6 ).arg( pSym->getString() );
												file.write( sTemp.toLatin1() );
											}
										}
										iNumSymListsWritten++;
									}
								}
							}

							iNumPropsWrittenThisClass++;
						}
            	}
				}  // end of new if statement preventing ANY writing when no properties to write
				iNumPropsWritten += iNumPropsWrittenThisClass;
			}	// end of loop over classes

			file.flush();
			file.close();
      }
      else
      {		assert( false );	// error opening file
      }
   }
	catch (...)
	{
      BEMMessageBox( QString( "Error writing data model text file: %1" ).arg( pszDataModelOutFile ), "", 3 /*error*/ );
      bRetVal = false;
		//throw std::runtime_error( "Error writing data model text file" );
	}
   									assert( bRetVal );
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

int BEMPX_SetPropertiesToUserDefined( int iBEMProcIdx /*=-1*/ )
{	int iRetVal = 0;
	int iError, iNumClasses = BEMPX_GetNumClasses();
	for (int i1Class=1; i1Class<=iNumClasses; i1Class++)
	{  BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
	   if ( iError >= 0 && pClass )
	   {  // Cruise thru list of BEM objects for this class
			for (int ib=0; ib < pClass->ObjectCount(); ib++)
			{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
	         if (pObj)
	         {	for (int iProp=0; iProp<pObj->getPropertiesSize(); iProp++)
					{	BEMProperty* pProp = pObj->getProperty(iProp);					assert( pProp != NULL && pProp->getType() != NULL );
						if (pProp && pProp->getType() && pProp->getDataStatus() > 0 && pProp->getDataStatus() < BEMS_UserDefined)
						{	// property & prop type are valid and data is rule or library-defined
							assert( pProp->get1ArrayIdx() <= pProp->getType()->getNumPropTypeDetails() );
							if (pProp->get1ArrayIdx() <= pProp->getType()->getNumPropTypeDetails())
							{
						//		POSITION pos = pProp->getType()->m_olDataTypes.FindIndex( pProp->get1ArrayIdx()-1 );			assert( pos );
						//		if (pos)
						//		{	BEMDataType* pDT = (BEMDataType*) pProp->getType()->m_olDataTypes.GetAt( pos );		assert( pDT );
								BEMPropTypeDetails* pDT = pProp->getType()->getPropTypeDetails( pProp->get1ArrayIdx()-1 );	assert( pDT );
									if (pDT && pDT->getCompDataType() >= BEMD_Compulsory && pDT->getCompDataType() <= BEMD_CriticalDef &&
			// SAC 1/15/14 - added check of m_bDisplayBudget - this member has been RE-PURPOSED to control whether or not defaults are reclassified here as user-defined (for CBECC-Res)
											pDT->isEditable() && pDT->getDisplayBudget())
									{	// data type indicates user editability, so change the property's to status to user defined
										// data types that do NOT get toggled to BEMS_UserDefined are:  BEMD_Prescribed & BEMD_NotInput
										pProp->setDataStatus( BEMS_UserDefined );
										iRetVal += 1;
									}
						//		}
							}
	         }	}	}
	         else
	         {  assert( FALSE );
		}	}	}
	   else if (iError < 0 || pClass == NULL)
	   {  assert( FALSE );
	}	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Qt XML Writing mechanism
/////////////////////////////////////////////////////////////////////////////

// SAC 2/28/13 - added to prevent writing of Sim objects w/ NO properties
static bool MustWriteProperties_XML( BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, bool bWritePropertiesDefinedByRuleset );
static bool MustWriteComponent_XML(  BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, bool bWritePropertiesDefinedByRuleset, int iBEMProcIdx );

bool StatusRequiresWrite_XML( BEMProperty* pProp, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties )
{
	assert( (pProp && pProp->getType()) );
	if (pProp==NULL || pProp->getType()==NULL)
		return false;

	assert( (iFileMode != BEMFM_SIM || !bWriteAllProperties) );
   bool bRetVal = ( (pProp->getDataStatus() == BEMS_UserDefined) ||
	                 (pProp->getDataStatus() != BEMS_Undefined && (bWriteAllProperties || BEMPX_IsHPXML( iFileType ) || BEMPX_IsCF1RXML( iFileType ) || BEMPX_IsNRCCXML( iFileType ) ||
																						BEMPX_IsRESNETXML( iFileType ) || iFileMode != BEMFM_INPUT /*!bIsInputMode*/)) );		// SAC 12/2/15   // SAC 5/20/20
	if (iFileMode == BEMFM_SIM)  // SAC 5/22/12 - added logic to further specify when properties are to be written to SIMULATION export files
	{	switch (pProp->getType()->getWriteSimulationFlag())
		{	case  0 :  bRetVal = false;   break;
			case  2 :  bRetVal = (pProp->getDataStatus() >= BEMS_UserDefault && pProp->getDataStatus() <= BEMS_UserDefined);   break;
			default :  bRetVal = (pProp->getDataStatus() != BEMS_Undefined);   break;
		}
		if (bRetVal && pProp->getType()->getPropType() == BEMP_Sym && pProp->getInt() <= 0)
			bRetVal = false;   // SAC 2/28/13 - prevent writing of symbol data to SIM file if symbol value is <= 0 (to prevent export of things like "- specify -")
	}
   return bRetVal;
}

bool MustWriteProperty_XML( BEMObject* pObj, BEMProperty* pProp, int iProp, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, bool bWritePropertiesDefinedByRuleset )
{
 	bool bRetVal = false;

// SAC 1/11/15 - added code to prevent writing properties defined by ruleset when specified via new function argument
		if (!bWritePropertiesDefinedByRuleset && pProp && pProp->getType() && pProp->getType()->getDefinedByRuleset())
			return false;

//		// SAC 5/7/19 - new logic to cause (potentially undefined) properties to get written to 
//		if (iFileMode == BEMFM_INPUT && pProp && pProp->getType() && pProp->getType()->getPropTypeDetails(0) && pProp->getType()->getPropTypeDetails(0)->isPrimary())
//		{
//						QString sDbg = QString("   forcing write of primary property: %1").arg(pProp->getType()->getShortName());
//					   BEMPX_WriteLogFile( sDbg );
//			return true;
//		}

// SAC 4/16/14 - if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
		if (iFileMode == BEMFM_INPUT && bOnlyValidInputs && pProp && pProp->getType() && pObj && pObj->getClass())
		{	int iCompDT = BEMPX_GetCompDataType( BEMPX_GetDBID( pObj->getClass()->get1BEMClassIdx(), pProp->getType()->get1PropTypeIdx(), pProp->get1ArrayIdx() ) );			assert( iCompDT >= 0 );
			if (iCompDT >= BEMD_NotInput)
				return false;
		}

	   // first check to see if the property status (or file mode) dictates that we must output the property
   	bRetVal = StatusRequiresWrite_XML( pProp, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties );

   	// If the status and mode doesn't require a property to be written, then we need to
   	// check to confirm that any array elements of the same property type following this one
   	// do require output, in which case this one must also be output.
   	if (!bRetVal)
   	{
      	int iNumProps = pProp->getType()->getNumValues();
      	// check for this property being one of an array of properties of a single property type
      	if (iNumProps > 1)
      	{
         	iProp++;
         	// loop over all following properties in this array until one is found to require output
      //   	while ( (iProp < pObj->m_properties.GetSize()) && (!bRetVal) && (iNumProps > 1) )
      //   	{
      //   	   pProp = (BEMProperty*) pObj->m_properties[iProp];
         	while ( (iProp < pObj->getPropertiesSize()) && (!bRetVal) && (iNumProps > 1) )
         	{
         	   pProp = pObj->getProperty(iProp);
        	   	if (pProp != NULL)
        	   	   bRetVal = StatusRequiresWrite_XML( pProp, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties );
        	   	else
        	   	{  assert( FALSE );
        	   	}
   	         iProp++;
   	         iNumProps--;
   	      }
   	   }
   	}

   return bRetVal;
}

void RoundIntegerToString( QString& sData, double dVal, int iRoundPrecision )		// 0 for x, -1 for x0, -2 for x00, -3 for x000, etc.
{	assert( iRoundPrecision >= 0 && iRoundPrecision < 10 );		// otherwise not covered below
	double dAdd = (dVal < 0 ? -0.5 : 0.5);
	switch (iRoundPrecision)
	{	case  1 :	dVal = ((int) ((dVal/10.0        ) + dAdd)) * 10         ;		break;
		case  2 :	dVal = ((int) ((dVal/100.0       ) + dAdd)) * 100        ;		break;
		case  3 :	dVal = ((int) ((dVal/1000.0      ) + dAdd)) * 1000       ;		break;
		case  4 :	dVal = ((int) ((dVal/10000.0     ) + dAdd)) * 10000      ;		break;
		case  5 :	dVal = ((int) ((dVal/100000.0    ) + dAdd)) * 100000     ;		break;
		case  6 :	dVal = ((int) ((dVal/1000000.0   ) + dAdd)) * 1000000    ;		break;
		case  7 :	dVal = ((int) ((dVal/10000000.0  ) + dAdd)) * 10000000   ;		break;
		case  8 :	dVal = ((int) ((dVal/100000000.0 ) + dAdd)) * 100000000  ;		break;
		case  9 :	dVal = ((int) ((dVal/1000000000.0) + dAdd)) * 1000000000 ;		break;
		default :	dVal =  (int) ( dVal               + dAdd );							break;
	}
	sData = QString( "%1" ).arg( QString::number(dVal, 'f', 0) );
}

void PropertyToString_XML( BEMObject* pObj, BEMProperty* pProp, QString& sData, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties,
									int iBEMProcIdx, bool bUseReportPrecisionSettings /*=false*/ )
{
   // get the data type of this property
   int iDataType = pProp->getType()->getPropType();
   if ( (iDataType == BEMP_Int) || (iDataType == BEMP_Sym) )
   {  // integer or symbolic data => stored in database as integer
      if (iDataType == BEMP_Int)
      {  long lTemp = pProp->getInt();
         // SAC 9/25/99 - Conversion of special DATE data from local time to GMT
         if (pProp->getType()->getObjTypeValue(0) == 1)
         {  // Get local delta from GMT
            struct _timeb tstruct;
#pragma warning(disable : 4996)
            _ftime( &tstruct );
#pragma warning(default : 4996)
            lTemp -= (tstruct.timezone * 60);
         }

			if (bUseReportPrecisionSettings && pProp->getType()->getReportPrecision() > -9 && pProp->getType()->getReportPrecision() < 0)
				// -1 for x0, -2 for x00, -3 for x000, etc.
				RoundIntegerToString( sData, lTemp, -pProp->getType()->getReportPrecision() );
			else
	         // integer => simple format
   	      sData = QString( "%1" ).arg( QString::number(lTemp) );
      }
      else // if (iDataType == BEMP_Sym)
      {  // symbol => convert integer value to symbol string and enclose in double quotes
            sData = QString( "%1" ).arg( GetSymbolStringFromPtrs( pProp->getInt(), pObj, pProp, iBEMProcIdx ) );
      }
   }
   else if (iDataType == BEMP_Flt)
   {
		if (bUseReportPrecisionSettings && pProp->getType()->getReportPrecision() > -9)
		{	// 3 for 0.xxx, 2 for 0.xx, 1 for 0.x, 0 for x, -1 for x0, -2 for x00, -3 for x000, etc.
			if (pProp->getType()->getReportPrecision() <= 0)
				RoundIntegerToString( sData, pProp->getDouble(), -pProp->getType()->getReportPrecision() );
			else
				sData = BEMPX_FloatToString( pProp->getDouble(), pProp->getType()->getReportPrecision(), FALSE /*bAddCommas*/ );
		}
		else
			// float => simple format
   	   sData = QString( "%1" ).arg( QString::number(pProp->getDouble()) );
   }
   else if (iDataType == BEMP_Str)
   {  // string => simply enclose in double quotes
      sData = pProp->getString();
   }
   else if (iDataType == BEMP_Obj)
   {  // object
      BEMObject* pRefObj = pProp->getObj();
      if (pRefObj != NULL)
      {  // if object pointer valid, enclose referenced object in double quotes
         sData = pRefObj->getName();
      }
      else if (iFileMode != BEMFM_SIM && StatusRequiresWrite_XML( pProp, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties ))  // SAC 8/27/13 - added code to prevent writing of '- none -' object references to simulation XML files
      {  // if object pointer NOT valid but we must output this property, then output "- none -"
         sData = szNone;
      }
      else  // else don't output property
         sData.clear();
   }
   else
   {  assert( FALSE );
   }
}

void WriteBracketPropertyArray_XML( QXmlStreamWriter& stream, BEMObject* pObj, BEMProperty* pProp, int& iProp, int iFileMode /*bool bIsInputMode*/, int iFileType,
												bool bWriteAllProperties, int iBEMProcIdx, bool bUseReportPrecisionSettings /*=false*/, bool bWritePrevNames /*=false*/ )
{  // Write array as list of the format "PROP[n] = VALUE" with comments as required
   //QString sPropType = pProp->getType()->getShortName();
   QString sData;
   //BOOL bDataAlreadyWritten = FALSE;
   int iCount = 1;
   // loop over array elements
   while ( (iCount <= pProp->getType()->getNumValues()) && (iProp < pObj->getPropertiesSize()) )
   {	pProp = pObj->getProperty(iProp);
      // only write property if we must
      if ( StatusRequiresWrite_XML( pProp, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties ) )
      {
         // convert property value to string
         PropertyToString_XML( pObj, pProp, sData, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx, bUseReportPrecisionSettings );

         // if property string not zero length, then write it
         if (sData.length() > 0 && (bWriteAllProperties || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
         {	QString sPropName = pProp->getType()->getShortName();
				if (sPropName.indexOf("afterchildren_")==0)
					sPropName = sPropName.right( sPropName.length()-14 );		// SAC 5/17/19 (res tic #1114)

	         if (pProp->getType()->getXMLWriteArrayIndices())   // SAC 1/24/12 - reference new flag indiciating whether or not to write array indices to XML output
				{	QString sIndex = QString( "%1" ).arg( QString::number(iCount-1) );
		   		stream.writeStartElement( sPropName );
		   		stream.writeAttribute( "index",	QString(sIndex) );
				}
				else
		   		stream.writeStartElement( sPropName );
	   		stream.writeCharacters( QString(sData) );
	   		stream.writeEndElement();
         }
  	      else if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1)
	      	// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
				ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, bWritePrevNames );
      }
      iCount++;
      // get next property if this is not the last one of this property type
      if ( iCount <= pProp->getType()->getNumValues() )  // SAC 1/22/02
         iProp++;
   }
}

void XMLPropertyNameReplacements( QString& sPropName )	// SAC 3/7/18
{  sPropName.replace( "xmlns_", "xmlns:" );
   sPropName.replace( "xsi_",   "xsi:" );
   sPropName.replace( "comp_",  "comp:" );
   return;
}

// retval:  >= 0 => # of properties SKIPPED due to name beginning "afterchildren_"
int WriteProperties_XML( QXmlStreamWriter& stream, BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, int iBEMProcIdx,
									bool bWritePropertiesDefinedByRuleset, bool bUseReportPrecisionSettings /*=false*/, bool bWritePrevNames /*=false*/ )
{	int iNumAfterChildrenProps = 0;
	//QString sClassName = pObj->getClass()->getShortName();
	QString sClassName = (bWritePrevNames && pObj->getClass()->getNumPreviousNames() > 0 ? pObj->getClass()->getPreviousName(0) : pObj->getClass()->getShortName());    // SAC 08/06/21 (MFam)
	if (BEMPX_IsHPXML( iFileType ))
	{	assert( sClassName.left(3).compare("hpx") == 0 );
		if (sClassName.left(3).compare("hpx") == 0)
			sClassName = sClassName.right( sClassName.length()-3 );
	}
	else if (BEMPX_IsCF1RXML( iFileType ))
	{	assert( sClassName.left(4).compare("cf1r") == 0 );
		if (sClassName.left(10).compare("cf1rtblRow") == 0)
			sClassName = "Row";
		else if (sClassName.left(4).compare("cf1r") == 0)
			sClassName = sClassName.right( sClassName.length()-4 );
	}
	else if (BEMPX_IsNRCCXML( iFileType ))       // SAC 11/23/20
	{	assert( sClassName.left(4).compare("nrcc") == 0 );
		if (sClassName.left(10).compare("nrcctblRow") == 0)
			sClassName = "Row";
		else if (sClassName.left(9).compare("nrcccomp_") == 0)         // 'nrcccomp_ObjectType' -->> 'comp:ObjectType' - SAC 04/27/22
			sClassName = "comp:" + sClassName.right( sClassName.length()-9 );
		else if (sClassName.left(4).compare("nrcc") == 0)
			sClassName = sClassName.right( sClassName.length()-4 );
	}
	else if (BEMPX_IsRESNETXML( iFileType ))		// SAC 5/20/20
	{	assert( sClassName.left(3).compare("rnx") == 0 );		// 4->3 char check - SAC 9/29/20
		if (sClassName.left(3).compare("rnx") == 0)
			sClassName = sClassName.right( sClassName.length()-3 );
	}
 	stream.writeStartElement( QString(sClassName) );

	int iFirstProp = 0;
	if (!pObj->getClass()->getXMLIgnoreName())   // SAC 1/24/12 - prevent writing of component names to XML for certain component types
	{	if (BEMPX_IsHPXML( iFileType ))		// SAC 12/2/15 - different method of writing object Name
		{	BEMProperty* pProp = (pObj->getPropertiesSize() < 1 ? NULL : pObj->getProperty(0));
			if (pProp && pProp->getType() && pProp->getType()->getDescription().compare("Name", Qt::CaseInsensitive) == 0)
				iFirstProp++;
	}	}

	int iProp;   std::vector<int> iAttribProps;
   // Write Properties in the form of XML attributes included in opening object type element - SAC 3/7/18
   for (iProp=iFirstProp; iProp<pObj->getPropertiesSize(); iProp++)
   {  BEMProperty* pProp = pObj->getProperty(iProp);
      // if property valid and should be written
      if ( pProp != NULL && pProp->getType()->getShortName().indexOf("attrib_")==0 && pProp->getType()->getNumValues() == 1 && pProp->getType()->getShortName().length() > 7 &&
      	  MustWriteProperty_XML( pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset ) )
      {	iAttribProps.push_back(iProp);
         QString sData;
         PropertyToString_XML( pObj, pProp, sData, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx, bUseReportPrecisionSettings );
         if (sData.length() > 0 && (bWriteAllProperties || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
         {	QString sPropName = pProp->getType()->getShortName().right( pProp->getType()->getShortName().length()-7 );
				XMLPropertyNameReplacements( sPropName );
				stream.writeAttribute( sPropName, sData );
	}	}	}

	if (pObj->getClass()->getWriteAsSingleRecord())  // SAC 1/24/12 - toggle OFF auto-formatting if this component is to be written into a single record of the XML file
		stream.setAutoFormatting(false);

	if (!pObj->getClass()->getXMLIgnoreName())   // SAC 1/24/12 - prevent writing of component names to XML for certain component types
	{	if (BEMPX_IsHPXML( iFileType ))		// SAC 12/2/15 - different method of writing object Name
		{	BEMProperty* pProp = (pObj->getPropertiesSize() < 1 ? NULL : pObj->getProperty(0));
			if (pProp && pProp->getType() && pProp->getType()->getDescription().compare("Name", Qt::CaseInsensitive) == 0)
				stream.writeStartElement( ((const char*) pProp->getType()->getShortName().toLocal8Bit().constData()) );
			else
				stream.writeStartElement("SystemIdentifier");
			stream.writeAttribute("id", QString(pObj->getName()));
			stream.writeEndElement();
		}
		else
		   stream.writeTextElement( "Name", QString(pObj->getName()) );
	}

   // Write Properties in the form: "   <PropType Name> = <Property Value>"
   for (iProp=iFirstProp; iProp<pObj->getPropertiesSize(); iProp++)
   {  BEMProperty* pProp = pObj->getProperty(iProp);
      // if property valid and should be written (and wasn't already written above as an attribute of the object)
      if ( pProp != NULL && IndexInArray( iAttribProps, iProp ) < 0 &&
      	  MustWriteProperty_XML( pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset ) )
      {
         if (pProp->getType()->getShortName().left(12).compare("noXMLoutput_", Qt::CaseInsensitive)==0 &&
             (BEMPX_IsCF1RXML( iFileType ) || BEMPX_IsNRCCXML( iFileType )))
         {  // SKIP writing this property (those whose names begin 'noXMLoutput_') - SAC 01/29/21
         }
			else if (pProp->getType()->getShortName().indexOf("afterchildren_")==0 && !pObj->getClass()->getWriteAsSingleRecord())	// SAC 11/21/18 - code to postpone writing of 'afterchildren_*' properties until after children are written
			{	iNumAfterChildrenProps++;
	         iProp += (pProp->getType()->getNumValues()-1);
	      }
         // if pProp IS NOT array, just write it out
         else if (pProp->getType()->getNumValues() == 1)
         {
            QString sData;
            PropertyToString_XML( pObj, pProp, sData, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx, bUseReportPrecisionSettings );
            if (sData.length() > 0 && (bWriteAllProperties || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
            {	QString sPropName = pProp->getType()->getShortName();
					XMLPropertyNameReplacements( sPropName );
			   	stream.writeTextElement( QString(sPropName), QString(sData) );
            }
   	      else if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1)
 		      	// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
					ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, bWritePrevNames );
            else
				{ //  assert( FALSE );
				}
         }
         else  // pProp IS array
         {
               WriteBracketPropertyArray_XML( stream, pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx,
                                              bUseReportPrecisionSettings, bWritePrevNames );
         }
      }
		// SAC 5/8/19 - new logic to cause properties to get written to XML output even if undefined
		else if (iFileMode == BEMFM_INPUT && pProp && pProp->getType() && pProp->getType()->getPropTypeDetails(0) && pProp->getType()->getPropTypeDetails(0)->isPrimary())
		{		//		QString sDbg = QString("   forcing write of primary property: %1").arg(pProp->getType()->getShortName());
				//	   BEMPX_WriteLogFile( sDbg );
			QString sPropName = pProp->getType()->getShortName();
			XMLPropertyNameReplacements( sPropName );
			stream.writeEmptyElement( QString(sPropName) );
		}
      else if (pProp == NULL)
      {
         assert( FALSE );
      }
      else  // must skip over entire property (which may have multiple elements)
      {
         iProp += (pProp->getType()->getNumValues()-1);
      }
   }

	if (pObj->getClass()->getWriteAsSingleRecord())  // SAC 1/24/12 - toggle back ON auto-formatting if the last component was written into a single record of the XML file
	{	stream.writeEndElement();
		stream.setAutoFormatting(true);
	}
	return iNumAfterChildrenProps;
}

void WritePropertiesAfterChildren_XML( QXmlStreamWriter& stream, BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, int iBEMProcIdx,
									bool bWritePropertiesDefinedByRuleset, bool bUseReportPrecisionSettings /*=false*/, bool bWritePrevNames /*=false*/ )	// SAC 11/21/18 - routine to write 'afterchildren_*' properties (after children are written)
{
   // Write Properties in the form: "   <PropType Name> = <Property Value>"
   for (int iProp=0; iProp<pObj->getPropertiesSize(); iProp++)
   {  BEMProperty* pProp = pObj->getProperty(iProp);
      // if property valid and should be written (and wasn't already written above as an attribute of the object)
      if ( pProp != NULL && pProp->getType()->getShortName().indexOf("afterchildren_")==0 &&
      	  MustWriteProperty_XML( pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset ) )
      {
         // if pProp IS NOT array, just write it out
         if (pProp->getType()->getNumValues() == 1)
         {
            QString sData;
            PropertyToString_XML( pObj, pProp, sData, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx, bUseReportPrecisionSettings );
            if (sData.length() > 0 && (bWriteAllProperties || pProp->getType()->getPropType() != BEMP_Sym || sData.indexOf("(null)") != 1))	// SAC 4/7/16
            {	QString sPropName = pProp->getType()->getShortName();
            	sPropName = sPropName.right( sPropName.length()-14 );  // SAC 11/21/18 - remove leading "afterchildren_"
					//XMLPropertyNameReplacements( sPropName );
			   	stream.writeTextElement( QString(sPropName), QString(sData) );
            }
   	      else if (pProp->getType()->getPropType() == BEMP_Sym && sData.indexOf("(null)") == 1)
 		      	// SAC 4/7/16 - report cases where an enum has no valid string based on current project data
					ReportInvalidEnumerationWrite( pObj, pProp, iBEMProcIdx, bWritePrevNames );
            else
				{ //  assert( FALSE );
				}
         }
         else  // pProp IS array
         {		//assert( false );  // if we get here we will need to trim property name written by the following routine to exclude leading "afterchildren_"
               WriteBracketPropertyArray_XML( stream, pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, iBEMProcIdx,
                                              bUseReportPrecisionSettings, bWritePrevNames );
         }
      }
      else if (pProp == NULL)
      {
         assert( FALSE );
      }
      else  // must skip over entire property (which may have multiple elements)
      {
         iProp += (pProp->getType()->getNumValues()-1);
      }
   }
}

static inline int IndexOfIntInArray( int iVal, int iArraySize, int* piArray )
{	for (int i=0; i<iArraySize; i++)
	{	if (iVal == piArray[i])
			return i;
	}
	return -1;
}

void WriteComponent_XML(	QXmlStreamWriter& stream, BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, int iBEMProcIdx,
									int iNumClassIDsToIgnore /*=0*/, int* piClassIDsToIgnore /*=NULL*/, bool bWritePropertiesDefinedByRuleset /*=true*/, bool bUseReportPrecisionSettings /*=false*/,
                           bool bWritePrevNames /*=false*/ )
{
   // first write this component's properties
   int iNumAfterChildrenProps = WriteProperties_XML( stream, pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx,
                                                     bWritePropertiesDefinedByRuleset, bUseReportPrecisionSettings, bWritePrevNames );

   // then write each of this component's children (recursively)
   if (pObj->getChildCount() > 0)
   {
// SAC 2/19/14 - added special handling for PolyLp objects - we need to write those FIRST, before other child types to ensure they are not written after other valid PolyLp parents
		int iPolyLpCID = BEMPX_GetDBComponentID( "PolyLp" );
		for (int iLp = (iPolyLpCID>0 ? 0 : 1); iLp < 2; iLp++)
		{	int iChildCID		= ( iLp==0                  ? iPolyLpCID : -1);
			int iNotChildCID	= ((iLp==1 && iPolyLpCID>0) ? iPolyLpCID : -1);
			// Cruise thru list of BEM child objects, writing each out to the file
      //	POSITION pos = pObj->m_children.GetHeadPosition();
      //	while ( pos != NULL )
      //	{  BEMObject* pChild = (BEMObject*) pObj->m_children.GetAt( pos );
			for (int iCIdx=0; iCIdx < pObj->getChildCount(); iCIdx++)
			{	BEMObject* pChild = pObj->getChild( iCIdx );					assert( pChild );
      	   if ( pChild != NULL &&
						(iFileMode != BEMFM_SIM || MustWriteComponent_XML( pChild, iFileMode, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset, iBEMProcIdx )) &&  // SAC 2/28/13
						(iChildCID < 0 || pChild->getClass()->get1BEMClassIdx() == iChildCID   ) &&		// SAC 2/19/14
												pChild->getClass()->get1BEMClassIdx() != iNotChildCID  &&
						(iNumClassIDsToIgnore < 1 || !piClassIDsToIgnore || IndexOfIntInArray( pChild->getClass()->get1BEMClassIdx(), iNumClassIDsToIgnore, piClassIDsToIgnore ) < 0) )		// SAC 1/6/15
      	   {
					WriteComponent_XML( stream, pChild, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx, iNumClassIDsToIgnore, piClassIDsToIgnore,
												bWritePropertiesDefinedByRuleset, bUseReportPrecisionSettings, bWritePrevNames );
      	   }
      	   else
      	   {  // assert( FALSE );  - OK for some classes not flagged for simulation - and when tweaking order of child writing
      	   }
      }	}
   }

	if (iNumAfterChildrenProps > 0)  // SAC 1/24/12 - toggle back ON auto-formatting if the last component was written into a single record of the XML file
		WritePropertiesAfterChildren_XML( stream, pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx,
                                        bWritePropertiesDefinedByRuleset, bUseReportPrecisionSettings, bWritePrevNames );

	if (!pObj->getClass()->getWriteAsSingleRecord())  // SAC 1/24/12 - toggle back ON auto-formatting if the last component was written into a single record of the XML file
		stream.writeEndElement();
}


bool MustWriteProperties_XML( BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, bool bWritePropertiesDefinedByRuleset )  // SAC 2/28/13 - added to prevent writing of Sim objects w/ NO properties
{
   bool bRetVal = false;
   for (int iProp=0; (!bRetVal && iProp<pObj->getPropertiesSize()); iProp++)
   {  BEMProperty* pProp = pObj->getProperty(iProp);
      // check if property valid and should be written
      if ( pProp != NULL && MustWriteProperty_XML( pObj, pProp, iProp/*pos*/, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset ) )
			bRetVal = true;
      else if (pProp == NULL)
      {  assert( FALSE );
      }
      else  // must skip over entire property (which may have multiple elements)
			iProp += (pProp->getType()->getNumValues()-1);
   }

	return bRetVal;
}

bool MustWriteComponent_XML( BEMObject* pObj, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, bool bOnlyValidInputs, bool bWritePropertiesDefinedByRuleset, int iBEMProcIdx )  // SAC 2/28/13 - added to prevent writing of Sim objects w/ NO properties
{
   bool bRetVal = true;

   // for Sim XML file writing - exclude objects where ExcludeFromEPlus > 0 - SAC 04/26/22
   if (iFileMode == BEMFM_SIM && iFileType == BEMFT_XML)
   {  long lDBID_ExcludeProp = BEMPX_GetDatabaseID( "ExcludeFromEPlus", pObj->getClass()->get1BEMClassIdx() );
      int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj, iBEMProcIdx );
      if (lDBID_ExcludeProp > 0 && iObjIdx >= 0)
      {  long lExclude;
         if (BEMPX_GetInteger( lDBID_ExcludeProp, lExclude, 0, -1, iObjIdx, BEMO_User, iBEMProcIdx ) && lExclude > 0)
            bRetVal = false;
      }
      // also bail on object output if class type begins 'cf1r' or 'nrcc' (T24 reporting obejcts) - SAC 04-26-22
      if (bRetVal)
      {  QString qsClassName = pObj->getClass()->getShortName();
         if (qsClassName.length() > 4 && (qsClassName.indexOf( "nrcc" )==0 || qsClassName.indexOf( "cf1r" )==0))
            bRetVal = false;
   }  }

   if (bRetVal)
   {  // next check to see if any of this component's properties need writing
      bRetVal = MustWriteProperties_XML( pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset );

      // then write each of this component's children (recursively)
      if (!bRetVal && pObj->getChildCount() > 0)
      {  // Cruise thru list of BEM child objects, writing each out to the file
      //   POSITION pos = pObj->m_children.GetHeadPosition();
      //   while ( !bRetVal && pos != NULL )
      //   {  BEMObject* pChild = (BEMObject*) pObj->m_children.GetAt( pos );
   		for (int iCIdx=0; (!bRetVal && iCIdx < pObj->getChildCount()); iCIdx++)
   		{	BEMObject* pChild = pObj->getChild( iCIdx );					assert( pChild );
            if (pChild != NULL)
               bRetVal = MustWriteComponent_XML( pChild, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset, iBEMProcIdx );
            else
            {  assert( FALSE );
            }
         }
   }  }
	return bRetVal;
}

bool WriteXMLFile( const char* pszFileName, int iFileMode /*bool bIsInputMode*/, int iFileType, bool bWriteAllProperties, BOOL /*bSupressAllMessageBoxes*/,
						 bool bAppend, const char* pszModelName, bool bWriteTerminator, int iBEMProcIdx /*=-1*/, bool bOnlyValidInputs /*=false*/ )		// SAC 2/19/13 - added trailing arguments to facilitate writing of multiple models into a single XML file
{
	if (iBEMProcIdx < 0)
		iBEMProcIdx = eActiveBEMProcIdx;
   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
	if (pBEMProc == NULL)
		return false;

	QString sFileName = pszFileName;
	QFile file( sFileName );
	if (!file.open( (bAppend ? QIODevice::Append : QIODevice::WriteOnly) ))
		return false;
	else
	{
		QXmlStreamWriter stream( &file );
		stream.setAutoFormatting(true);
		stream.setAutoFormattingIndent(2);

      int iLastDotIdx = sFileName.lastIndexOf('.');
      int iVint19Idx  = sFileName.lastIndexOf("19");
      bool bWritePrevNames = (iLastDotIdx > 0 && iVint19Idx > iLastDotIdx);    // enable writing of previous class/property names when writing 2019 project files - SAC 08/06/21 (MFam)

		if (!bAppend)
		{	stream.writeStartDocument();
			//stream.writeDTD("<?xml  version=\"1.0\"  encoding=\"utf-8\" ?>");
			if (BEMPX_IsHPXML( iFileType ))		// SAC 12/2/15
			{
				stream.writeStartElement("HPXML");
				stream.writeAttribute("xmlns", "http://hpxmlonline.com/2014/6");
				stream.writeAttribute("schemaVersion", "2.1");
			}
			else if (BEMPX_IsCF1RXML( iFileType ) || BEMPX_IsNRCCXML( iFileType ))		// SAC 3/6/18
			{	// no specific starting elements for CF1R or NRCC XML files...
			}
			else if (BEMPX_IsRESNETXML( iFileType ))		// SAC 5/20/20
			{	// write RESNET copywrite message ??

			}
			else
			{
				stream.writeStartElement("SDDXML");
				stream.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
				stream.writeAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
				//stream.writeAttribute("version", "1.0");
      	
   			if (pBEMProc->getType() == BEMT_CBECC)
   			{	// first thing to write is the ruleset filename
				   QString sRulesetFilename;
					RetrieveRulesetFilename( sRulesetFilename, iBEMProcIdx );
//					QString qsRulesetFilename = sRulesetFilename
					stream.writeStartElement("RulesetFilename");
					stream.writeAttribute("file", QString(sRulesetFilename));
					stream.writeEndElement();
			}	}
		}

		bool bModelNameWritten = false;
		if (pszModelName && strlen( pszModelName ) > 0)		// SAC 2/19/13 - Write model name to XML file (if specified)
		{	bModelNameWritten = true;
		 	stream.writeStartElement( QString("Model") );
		   stream.writeTextElement( "Name", QString(pszModelName) );
		}

   	// then loop over all classes, writing out the components for each class, one by one
   	int iNumClasses = BEMPX_GetNumClasses();
   	for (int i1Class=1; i1Class<=iNumClasses; i1Class++)
   	{
   	   int iError;
   	   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
   	   if ( (iError >= 0) && (pClass != NULL) &&
   	   	  (!BEMPX_IsHPXML(     iFileType ) || pClass->getShortName().indexOf("hpx" )==0) &&		// SAC 12/2/15 - when in HPXML writing mode, only write objects whose class name begins w/ "hpx"
   	   	  (!BEMPX_IsCF1RXML(   iFileType ) || pClass->getShortName().indexOf("cf1r")==0) &&	   // SAC 3/6/18 - when in CF1RXML writing mode, only write objects whose class name begins w/ "cf1r"
   	   	  (!BEMPX_IsNRCCXML(   iFileType ) || pClass->getShortName().indexOf("nrcc")==0) &&	   // when in NRCCXML writing mode, only write objects whose class name begins w/ "nrcc" - SAC 11/23/20
   	   	  (!BEMPX_IsRESNETXML( iFileType ) || pClass->getShortName().indexOf("rnx" )==0) &&	   // SAC 5/20/20 - when in RESNETXML writing mode, only write objects whose class name begins w/ "rnx"
   	          // don't write class objects tagged as AutoCreate to INPUT file
   	        ( (iFileMode != BEMFM_INPUT /*!bIsInputMode*/) || (!pClass->getAutoCreate()) ) )
   	   {
// SAC 4/16/14 - if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
				bool bWriteClass = (iFileMode == BEMFM_INPUT && bOnlyValidInputs) ? false : true;
				if (!bWriteClass)
				{	for (int iP1=0; (!bWriteClass && iP1 < pBEMProc->getClass( i1Class-1 )->getNumProps()); iP1++)
   	   	   {  int iPropDataType = BEMPX_GetCompDataType( BEMPX_GetDBID( i1Class, (iP1+1), 1 /*i1Array*/ ) );
						if (iPropDataType < BEMD_NotInput)
							bWriteClass = true;
				}	}

				if (bWriteClass)
				{
					for (int ib=0; ib < pClass->ObjectCount(BEMO_User); ib++)
					{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
   	      	   if (pObj != NULL)
   	      	   {  // only write the component if it doesn't have a parent.
   	      	      // if it DOES have a parent, then it will be written automatically during the
   	      	      // course of its parent being written.
   	      	      if ( pObj->getParent() == NULL &&
									(iFileMode != BEMFM_SIM || MustWriteComponent_XML( pObj, iFileMode, iFileType, bWriteAllProperties, bOnlyValidInputs, true /*bWritePropertiesDefinedByRuleset*/, iBEMProcIdx )) )  // SAC 2/28/13
   	      	         WriteComponent_XML( stream, pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx, 0, NULL, true /*bWritePropertiesDefinedByRuleset*/,
                                            false /*bUseReportPrecisionSettings*/, bWritePrevNames );
   	      	   }
   	      	   else
   	      	   {  assert( FALSE );
   	      	   }
   	      }	}
   	   }
   	   else if ((iError < 0) && (pClass == NULL))
   	   {  assert( FALSE );
   	   }
   	}

		if (bModelNameWritten)
			stream.writeEndElement();

		if (bWriteTerminator)
			stream.writeEndDocument();

		file.close();
   }

	return true;
}

////////////////////////////////////////////////////////////

BEMXMLWriter::BEMXMLWriter( const char* pszFileName /*=NULL*/, int iBEMProcIdx /*=-1*/, int iFileType /*=-1*/, bool bWritePrevNames /*=false*/ )
{
	bool bFileOK = false;
	if (pszFileName && strlen( pszFileName ) > 0)
	{	mp_file = new QFile( QString( pszFileName ) );
		if (mp_file->open( QIODevice::WriteOnly ))
			bFileOK = true;
	}
	else
		mp_file = NULL;
   m_bWritePrevNames = bWritePrevNames;

	if (mp_file && bFileOK)
	{	mp_stream = new QXmlStreamWriter( mp_file );
		mp_stream->setAutoFormatting(true);
		mp_stream->setAutoFormattingIndent(2);
      	
		mp_stream->writeStartDocument();
		//mp_stream->writeDTD("<?xml  version=\"1.0\"  encoding=\"utf-8\" ?>");

		if (BEMPX_IsCF1RXML( iFileType ) || BEMPX_IsRESNETXML( iFileType ) || BEMPX_IsNRCCXML( iFileType ))
		{	// SAC 3/6/18 - when in CF1RXML writing mode, don't write SDD and ruleset stuff   // SAC 5/20/20 - same for RESNET   // sane for NRCCXML - SAC 11/23/20
		}
		else
		{	mp_stream->writeStartElement("SDDXML");
			mp_stream->writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
			mp_stream->writeAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
			//mp_stream->writeAttribute("version", "1.0");

			if (iBEMProcIdx < 0)  // SAC 3/18/13
				iBEMProcIdx = eActiveBEMProcIdx;
		   BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
			if (pBEMProc == NULL)
			{	assert( FALSE );
			}
			else if (pBEMProc->getType() == BEMT_CBECC)
   		{	// first thing to write is the ruleset filename
			   QString sRulesetFilename;
				RetrieveRulesetFilename( sRulesetFilename, iBEMProcIdx );
//				QString qsRulesetFilename = sRulesetFilename
				mp_stream->writeStartElement("RulesetFilename");
				mp_stream->writeAttribute("file", QString(sRulesetFilename));
				mp_stream->writeEndElement();
		}	}
	}
	else
		mp_stream = NULL;
}

BEMXMLWriter::~BEMXMLWriter()
{
	Close();
}

void BEMXMLWriter::Close()
{
	if (mp_stream)
		mp_stream->writeEndDocument();
	if (mp_file)
		mp_file->close();

	if (mp_stream)
		delete mp_stream;
	if (mp_file)
		delete mp_file;

	mp_stream = NULL;
	mp_file = NULL;
}

bool BEMXMLWriter::WriteModel(	bool bWriteAllProperties, BOOL /*bSupressAllMessageBoxes*/, const char* pszModelName, int iBEMProcIdx /*=-1*/, bool bOnlyValidInputs /*=false*/,
											int iNumClassIDsToIgnore /*=0*/, int* piClassIDsToIgnore /*=NULL*/, bool bWritePropertiesDefinedByRuleset /*=true*/, bool bUseReportPrecisionSettings /*=false*/,
											int iFileType /*=BEMFT_XML*/ )
{	bool bRetVal = (mp_file && mp_stream);
	if (bRetVal)
	{	int iFileMode = BEMFM_INPUT;

		bool bModelNameWritten = false;
		if (pszModelName && strlen( pszModelName ) > 0)		// SAC 2/19/13 - Write model name to XML file (if specified)
		{	bModelNameWritten = true;
		 	mp_stream->writeStartElement( QString("Model") );
		   //mp_stream->writeTextElement( "Name", QString(pszModelName) );
		   mp_stream->writeAttribute( "Name", QString(pszModelName) );
		}

   	// then loop over all classes, writing out the components for each class, one by one
   	int iNumClasses = BEMPX_GetNumClasses();
   	for (int i1Class=1; i1Class<=iNumClasses; i1Class++)
   	{
   		bool bProcessClass = (iNumClassIDsToIgnore < 1 || !piClassIDsToIgnore || IndexOfIntInArray( i1Class, iNumClassIDsToIgnore, piClassIDsToIgnore ) < 0);
   	   int iError;
   	   BEMClass* pClass = BEMPX_GetClass( i1Class, iError, iBEMProcIdx );
   	   if ( (iError >= 0) && (pClass != NULL) && bProcessClass &&
   	          // don't write class objects tagged as AutoCreate to INPUT file
   	        ( (iFileMode != BEMFM_INPUT /*!bIsInputMode*/) || (!pClass->getAutoCreate()) ) )
   	   {
// SAC 4/16/14 - if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
				bool bWriteClass = (iFileMode == BEMFM_INPUT && bOnlyValidInputs) ? false : true;
				if (!bWriteClass)
				{	for (int iP1=0; (!bWriteClass && iP1 < eBEMProc.getClass( i1Class-1 )->getNumProps()); iP1++)
   	   	   {  int iPropDataType = BEMPX_GetCompDataType( BEMPX_GetDBID( i1Class, (iP1+1), 1 /*i1Array*/ ) );
						if (iPropDataType < BEMD_NotInput)
							bWriteClass = true;
				}	}

				if (bWriteClass)
				{
					for (int ib=0; ib < pClass->ObjectCount(BEMO_User); ib++)
					{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
   	      	   if (pObj != NULL)
   	      	   {  // only write the component if it doesn't have a parent.
   	      	      // if it DOES have a parent, then it will be written automatically during the
   	      	      // course of its parent being written.
   	      	      if ( pObj->getParent() == NULL &&
									(iFileMode != BEMFM_SIM || MustWriteComponent_XML( pObj, iFileMode, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset, iBEMProcIdx )) )  // SAC 2/28/13
   	      	      {
   	      	         WriteComponent_XML( *mp_stream, pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx,
   	      	         							iNumClassIDsToIgnore, piClassIDsToIgnore, bWritePropertiesDefinedByRuleset, bUseReportPrecisionSettings, m_bWritePrevNames );
   	      	      }
   	      	   }
   	      	   else
   	      	   {  assert( FALSE );
   	      	   }
   	      }	}
   	   }
   	   else if ((iError < 0) && (pClass == NULL))
   	   {  assert( FALSE );
   	   }
   	}

		if (bModelNameWritten)
			mp_stream->writeEndElement();
	}

	return bRetVal;
}


bool BEMXMLWriter::WriteCF1RPRF01E(	int iBEMClassID, bool bWriteAllProperties, BOOL bSupressAllMessageBoxes,
							int iBEMProcIdx /*=-1*/, bool bOnlyValidInputs /*=false*/,
							bool bWritePropertiesDefinedByRuleset /*=true*/, bool bUseReportPrecisionSettings /*=false*/, int iFileType /*=BEMFT_XML*/ )
{	bool bRetVal = (mp_file && mp_stream);
	if (bRetVal)
	{	int iFileMode = BEMFM_INPUT;

   	// --NO-- loop over all classes, writing out the components for each class, one by one

   		bool bProcessClass = true;  //(iNumClassIDsToIgnore < 1 || !piClassIDsToIgnore || IndexOfIntInArray( iBEMClassID, iNumClassIDsToIgnore, piClassIDsToIgnore ) < 0);
   	   int iError;
   	   BEMClass* pClass = BEMPX_GetClass( iBEMClassID, iError, iBEMProcIdx );
   	   if ( (iError >= 0) && (pClass != NULL) && bProcessClass &&
   	          // don't write class objects tagged as AutoCreate to INPUT file
   	        ( (iFileMode != BEMFM_INPUT /*!bIsInputMode*/) || (!pClass->getAutoCreate()) ) )
   	   {	// if storing input and m_bOnlyValidInputs = true, then check to confirm that there are valid input properties before writing file
				bool bWriteClass = (iFileMode == BEMFM_INPUT && bOnlyValidInputs) ? false : true;
				if (!bWriteClass)
				{	for (int iP1=0; (!bWriteClass && iP1 < eBEMProc.getClass( iBEMClassID-1 )->getNumProps()); iP1++)
   	   	   {  int iPropDataType = BEMPX_GetCompDataType( BEMPX_GetDBID( iBEMClassID, (iP1+1), 1 /*i1Array*/ ) );
						if (iPropDataType < BEMD_NotInput)
							bWriteClass = true;
				}	}

				if (bWriteClass)
				{	for (int ib=0; ib < pClass->ObjectCount(BEMO_User); ib++)
					{	BEMObject* pObj = pClass->GetObject( BEMO_User, ib );
   	      	   if (pObj != NULL)
   	      	   {  // only write the component if it doesn't have a parent.
   	      	      // if it DOES have a parent, then it will be written automatically during the
   	      	      // course of its parent being written.
   	      	      if ( pObj->getParent() == NULL &&
									(iFileMode != BEMFM_SIM || MustWriteComponent_XML( pObj, iFileMode, iFileType, bWriteAllProperties, bOnlyValidInputs, bWritePropertiesDefinedByRuleset, iBEMProcIdx )) )  // SAC 2/28/13
   	      	      {
   	      	         WriteComponent_XML( *mp_stream, pObj, iFileMode /*bIsInputMode*/, iFileType, bWriteAllProperties, bOnlyValidInputs, iBEMProcIdx,
   	      	         							0 /*iNumClassIDsToIgnore*/, NULL /*piClassIDsToIgnore*/, bWritePropertiesDefinedByRuleset, bUseReportPrecisionSettings, m_bWritePrevNames );
   	      	      }
   	      	   }
   	      	   else
   	      	   {  assert( FALSE );
   	      	   }
   	      }	}
   	   }
   	   else if ((iError < 0) && (pClass == NULL))
   	   {  assert( FALSE );
   	   }

	}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// Qt XML READING mechanism
/////////////////////////////////////////////////////////////////////////////

static int siLastIndent = -1;
static QString ssLastIndentChars;
static int siXMLElementCount = -1;

////////////////////////////////////////////////////////////
bool CharsAreAllSpaces( QString sChars )
{	for (int i=0; i<sChars.length(); i++)
	{	//int iChar = sChars[i];
//		if (sChars[i] != ' ' && sChars[i] != '\t' && sChars[i] != '\0')
		if (sChars[i] != 32 && sChars[i] != 9 && sChars[i] != 10)
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////
void SetIndentString( QString& str, int iNumSpcs )
{	str.clear();
	for (int i=0; i<iNumSpcs; i++)
		str += ' ';
}

////////////////////////////////////////////////////////////
void WriteTokenToLog( QXmlStreamReader& stream )
{	QString sElemDesc, sAttrib;   // sElemName = stream.name().toString();    // QString sElemName = stream.tokenString();
	switch (stream.tokenType())
	{	case QXmlStreamReader::NoToken               :  sElemDesc = QString( "%1NoToken  (line %2)" ).arg( ssLastIndentChars, QString::number(stream.lineNumber()) );           break;
		case QXmlStreamReader::Invalid               :  sElemDesc = QString( "%1Invalid  (line %2)" ).arg( ssLastIndentChars, QString::number(stream.lineNumber()) );           break;
		case QXmlStreamReader::StartDocument         :  sElemDesc = QString( "%1StartDocument, ver '%2', encd '%3', stand alone %4  (line %5)" ).arg( ssLastIndentChars, stream.documentVersion().toLocal8Bit().constData(),
																													stream.documentEncoding().toLocal8Bit().constData(), (stream.isStandaloneDocument() ? "Y":"N"), QString::number(stream.lineNumber()) );   break;
		case QXmlStreamReader::EndDocument           :  sElemDesc = QString( "%1EndDocument  (line %2)" ).arg( ssLastIndentChars, QString::number(stream.lineNumber()) );       break;
		case QXmlStreamReader::StartElement          : {	QXmlStreamAttributes attribs = stream.attributes();
																			int iNumAttribs = attribs.size();
																			sElemDesc = QString( "%1StartElement, name '%2', num attributes %3:  " ).arg( ssLastIndentChars, stream.name().toLocal8Bit().constData(), QString::number(iNumAttribs) );
																			for (int i=0; i< std::min( 3, iNumAttribs ); i++)
																			{	sAttrib = QString( "/ name '%1'  value '%2' /" ).arg( attribs.at(i).name().toLocal8Bit().constData(), attribs.at(i).value().toLocal8Bit().constData() );
																				sElemDesc += sAttrib;
																			}
																			sAttrib = QString( "  (line %1)" ).arg( QString::number(stream.lineNumber()) );
																			sElemDesc += sAttrib;
																		}  break;
		case QXmlStreamReader::EndElement            :  sElemDesc = QString( "%1EndElement,   name '%2'  (line %3)" ).arg( ssLastIndentChars, stream.name().toLocal8Bit().constData(), QString::number(stream.lineNumber()) );   break;
		case QXmlStreamReader::Characters            :  if (CharsAreAllSpaces( stream.text().toLocal8Bit().constData() ))
																		{	siLastIndent = stream.text().length();
																			SetIndentString( ssLastIndentChars, siLastIndent );
																			sElemDesc = QString( "%1Characters,   (indentation of %2)  (line %3)" ).arg( ssLastIndentChars, QString::number(siLastIndent), QString::number(stream.lineNumber()) );
																		}
																		else
																			sElemDesc = QString( "%1Characters,   text '%2' (length %3)  (line %4)" ).arg( ssLastIndentChars, stream.text().toLocal8Bit().constData(), QString::number(stream.text().length()), QString::number(stream.lineNumber()) );
																		break;
		case QXmlStreamReader::Comment               :  sElemDesc = QString( "%1Comment,   text '%2'  (line %3)" ).arg( ssLastIndentChars, stream.text().toLocal8Bit().constData(), QString::number(stream.lineNumber()) );   break;
		case QXmlStreamReader::DTD                   :  sElemDesc = QString( "%1DTD,   text '%2'  (line %3)" ).arg( ssLastIndentChars, stream.text().toLocal8Bit().constData(), QString::number(stream.lineNumber()) );   break;
		case QXmlStreamReader::EntityReference       :  sElemDesc = QString( "%1EntityReference,   name '%2' ).arg( text '%3'  (line %4)" ).arg( ssLastIndentChars, stream.name().toLocal8Bit().constData(), stream.text().toLocal8Bit().constData(), QString::number(stream.lineNumber()) );   break;
		case QXmlStreamReader::ProcessingInstruction :  sElemDesc = QString( "%1ProcessingInstr  (line %2)" ).arg( ssLastIndentChars, QString::number(stream.lineNumber()) );   break;
		default                                      :  sElemDesc = QString( "%1unknown!  (line %2)" ).arg( ssLastIndentChars, QString::number(stream.lineNumber()) );          break;
	}
   BEMPX_WriteLogFile( sElemDesc, NULL, FALSE, FALSE /*m_bSupressAllMessageBoxes*/ );
}

////////////////////////////////////////////////////////////

// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
static int FindOldCompMapGroupID( BEMComponentMap* pCompMap, QString sObjType, long lFileVersion, int* piCMIdx )
{
	int iBEMMapGroupID = -1;
	if (pCompMap)
	{	int iCMIdx = -1;
		while (iBEMMapGroupID < 0 && pCompMap[++iCMIdx].iCompTypeID > 0)
		{	if (pCompMap[iCMIdx].iVersionCutoff >= lFileVersion && sObjType.compare( pCompMap[iCMIdx].szOldCompType ) == 0)
			{	iBEMMapGroupID = pCompMap[iCMIdx].iCompTypeID;
				if (piCMIdx)
					*piCMIdx = iCMIdx;
			}
	}	}
	return iBEMMapGroupID;
}

// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
BEMObject* CreateCompMapObjects( BEMComponentMap* pCompMap, int iBEMMapGroupID, int iCMIdx, int* i1BEMMapGroupNewClasses, int iBEMProcIdx, const char* pszObjName, 
												bool bIsUserInputMode, QVector<int>* pivMapCompsCreated )
{	BEMObject* pNewObj = NULL;
	if (pCompMap == NULL || iBEMMapGroupID < 0 || iCMIdx < 0 || iCMIdx >= 5 )
	{	assert( FALSE );	// invalid arguments
	}
	else
	{	assert( iCMIdx >= 0 && iCMIdx < 5 );
		BEM_ObjType eObjType = BEMO_User;
		int iError, i1Class, iObjIdx;  // not sure if these are needed...?
		BEMProcObject* pBEMProc = getBEMProcPointer( iBEMProcIdx );			assert( pBEMProc );
		int iCMIdx2 = -1;
		while (iCMIdx2 < 4 && pCompMap[iCMIdx].szNewCompType[++iCMIdx2] != NULL)
		{	i1BEMMapGroupNewClasses[iCMIdx2] = BEMPX_GetDBComponentID( pCompMap[iCMIdx].szNewCompType[iCMIdx2] );
			assert( i1BEMMapGroupNewClasses[iCMIdx2] > 0 );
			if (i1BEMMapGroupNewClasses[iCMIdx2] > 0)
			{	if (BEMPX_CanCreateAnotherUserObject( i1BEMMapGroupNewClasses[iCMIdx2], 1 /*iNumObjs*/, iBEMProcIdx ))
				{	QString sMapObjName = (iCMIdx2 == 0 ? pszObjName : pBEMProc->getClass( i1BEMMapGroupNewClasses[iCMIdx2]-1 )->getLongName());
					BEMObject* pMapObj = BEMPX_CreateObject( i1BEMMapGroupNewClasses[iCMIdx2], sMapObjName.toLocal8Bit().constData(), NULL, eObjType, TRUE, bIsUserInputMode, iBEMProcIdx );
					assert( pMapObj );
					if (pivMapCompsCreated)
						pivMapCompsCreated->push_back( i1BEMMapGroupNewClasses[iCMIdx2] );
					if (pMapObj && pNewObj == NULL)
					{	i1Class = i1BEMMapGroupNewClasses[iCMIdx2];
						pNewObj = pMapObj;
						iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ), pNewObj, iBEMProcIdx );	// SAC 4/21/14
				}	}
				else if (pNewObj == NULL)
				{	i1Class = i1BEMMapGroupNewClasses[iCMIdx2];
					pNewObj = BEMPX_GetObjectByClass( i1Class, iError, 0, BEMO_User, iBEMProcIdx );
					iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1Class, iError, iBEMProcIdx ), pNewObj, iBEMProcIdx );	// SAC 4/21/14
			}	}
			assert( pNewObj != NULL );
	}	}
	return pNewObj;
}

////////////////////////////////////////////////////////////

void PostAttributesToObject( BEMObject* pBEMObject, QXmlStreamAttributes* pAttribs, int iBEMProcIdx )
{
	if (pBEMObject && pAttribs)
	{	int iError, iNumAttribs = pAttribs->size();
		for (int iA=0; iA < iNumAttribs; iA++)
		{	QString sAttribName = pAttribs->at(iA).name().toLocal8Bit().constData();
			long lDBID = BEMPX_GetDatabaseID( sAttribName, pBEMObject->getClass()->get1BEMClassIdx() );
			if (lDBID > BEM_COMP_MULT)
			{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError, iBEMProcIdx );
        	   QString sChars = pAttribs->at(iA).value().toLocal8Bit().constData();
				if (pPropType == NULL || sChars.isEmpty())
				{	// ignore
				}
				else
				{
            	   BEM_PropertyStatus ePropStat = BEMS_UserDefined;
            	   int iSet = 0;
            	   int i0ArrIdx = 0;
				// SAC 8/13/15 - added code to prevent setting of this property based on BEMDataType:m_iNotInputMode (and m_eCompDataType == BEMD_NotInput...)
						QString sErrMsg2;
						bool bNotInputError = false;

				      	assert( pPropType->getNumPropTypeDetails() > i0ArrIdx );
							BEMPropTypeDetails* pDT = pPropType->getPropTypeDetails( i0ArrIdx );			assert( pDT );
							if (pDT && pDT->getCompDataType() == BEMD_NotInput && pDT->getNotInputMode() != DTNotInp_AllowUIReset)
							{	ePropStat = BEMS_Undefined;
								bNotInputError = (pDT->getNotInputMode() == DTNotInp_ErrorIfInput);
			//					if (!pDT->getNotInputMsg().isEmpty())
			//					{	QString sMsg, sMsgEnd;
			//						if (i0ArrIdx > 0)
			//							sMsgEnd = QString( "[%1]" ).arg( QString::number(i0ArrIdx+1) );
			//						else
			//							sMsgEnd = "";
			//						if (bNotInputError)
			//						{	sMsg = QString( "   Error:  %1  (%2 '%3' %4%5, line: %6)" ).arg( pDT->getNotInputMsg(), (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, pPropType->getShortName(), sMsgEnd, QString::number(stream.lineNumber()) );
			//							sErrMsg2 = sMsg;
			//						}
			//						else
			//							sMsg = QString( "   %1  (%2 '%3' %4%5)" ).arg( pDT->getNotInputMsg(), (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, pPropType->getShortName(), sMsgEnd );
			//						BEMPX_WriteLogFile( sMsg, NULL, FALSE, FALSE /*m_bSupressAllMessageBoxes*/ );
			//					}
							}

            	   // SAC 10/5/00 - Added code to intercept certain DBID that have been converted from BEMP_Int to BEMP_Sym
            	   int iTempPropType = pPropType->getPropType();
            	   QString sErrantData;  // SAC 7/10/03 - added to facilitate more informative error reporting
            	   switch ( iTempPropType )
            	   {  // read the data and post it to the database
            	      case BEMP_Int : {  long lTemp = atol( sChars.toLocal8Bit().constData() );			// long lTemp = m_file.ReadLong();
            	                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
            	                        {
            	                           iSet = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lTemp,
            	                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
            	                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
            	                              sErrantData = sChars;		// sErrantData.Format( "%d", lTemp );
            	                        }
            	                        break;  }
            	      case BEMP_Flt : {  double fTemp = atof( sChars.toLocal8Bit().constData() );       // float fTemp = m_file.ReadFloat();
            	                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
            	                        {
            	                           iSet = BEMPX_SetBEMData( lDBID, BEMP_Flt, (void*) &fTemp,
            	                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
            	                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
            	                              sErrantData = sChars;		// sErrantData.Format( "%g", fTemp );
            	                        }
            	                        break;  }
            	      case BEMP_Sym :
            	      case BEMP_Str : {  QString sTemp = sChars;		// QString sTemp = m_file.ReadString( TRUE );  // SAC 6/17/01 - added argument to ALLOW reading beyond carriage return
				         						bool bNotSymOrNotNull = (iTempPropType != BEMP_Sym || sTemp.compare("(null)")!=0 ? true : false);	// SAC 4/7/16 - prevent storing enums = "(null)"
            	                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined && bNotSymOrNotNull)  // SAC 10/19/01 - added reference to bPostData
            	                        {
            	                           iSet = BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &sTemp,  // BEMP_Str, (void*) sTemp.toLocal8Bit().constData(),
            	                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
				                           	if (iSet < 0 && (!pPropType->getShortName().compare("Ruleset", Qt::CaseInsensitive) || !pPropType->getDescription().compare("Ruleset", Qt::CaseInsensitive)))
            											iSet = 0;	// SAC 12/3/15 - ignore read errors where Ruleset not valid or not found (port fix from 11/22 made for *ibd files)
            	                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
            	                              sErrantData = sTemp;
            	                        }
            	                        break;  }
            	      case BEMP_Obj : {  QString sTemp = sChars;		// QString sTemp = m_file.ReadString( TRUE );
            	                        // iError;
            	                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined)  // SAC 10/19/01 - added reference to bPostData
            	                        {
            	                           BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, -1 /*iObjIdx*/, BEMO_User /*eObjType*/, iBEMProcIdx );
            	                           if (pProp)
            	                           {
            	                              pProp->setDataStatus( ePropStat );
            	                              pProp->setString( sTemp );
            	                              pProp->setObj( NULL );
            	                           }
            	                        }
            	                        break;  }
            	      default : 
            	         assert( FALSE );		// m_file.ThrowFormatException(); // should never happen
            	         break;
            	   }
			}	}
	}	}
}

////////////////////////////////////////////////////////////
// WARNING:  THIS ROUTINE RECURSIVE, to allow for creation of children within...
bool ReadXMLComponent( const char* fileName, QXmlStreamReader& stream, QString sElemName, int iBEMClassIdx, bool bIsUserInputMode, int iBEMProcIdx,
								QString& sErrMsg, BOOL bStoreData, int* piObjPropCounts /*=NULL*/, BEMStraightMap* pStraightMap, long lDBIDVersion, long& lFileVersion,    // SAC 10/30/13 - added to facilitate bulk memory allocation of BEMObject & BEMProperty objects
								BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap, QVector<int>* pivMapCompsCreated,		// SAC 5/7/14 - added BEMComponentMap & BEMPropertyMap ptrs
								int& iDBIDSetFailureIdx, int iMaxDBIDSetFailures, int* piDBIDSetFailures, int* piObjIdxSetFailures, QStringList* psaDataSetFailures,    // SAC 6/28/16 - added to facilitate more informative error tracking
								QXmlStreamAttributes* pAttribs, const char* pszClassPrefix )   // SAC 10/25/18 - added pAttribs to process component attributes (for non-SDDXML files)
{	bool bRetVal = true;
	int iInitialIndentLevel = siLastIndent;
	int iLocalElementCount = 0;
	//int iNumPropertiesProcessed = 0;
	int iError = 0;
	BOOL bObjectCreated = FALSE;
	QString sObjectName;

	// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
	int iBEMMapGroupID = -1;
	int i1BEMMapGroupNewClasses[] = {0,0,0,0,0};
	int iCMIdx = -1;
	if (iBEMClassIdx <= 0 && pCompMap && pPropMap)
		iBEMMapGroupID = FindOldCompMapGroupID( pCompMap, sElemName, lFileVersion, &iCMIdx );

	BEMObject* pBEMObject = NULL;
	BEMClass* pBEMClass = BEMPX_GetClass( iBEMClassIdx, iError, iBEMProcIdx );					assert( pBEMClass );
	QString sElementName;
	BOOL bElementIsName = FALSE;
	QString sPropertyBeingProcessed;
	BOOL bDoneProcessingComponent = FALSE;
	BOOL bPostDataForThisElement = TRUE;
	long lThisElemDBID=0, lLastElemDBID=0;
	int i0ArrIdx = 0, iNumDataSetFailures = 0;
	QString sErrMsgFirstDataSetFailure;

	while (bRetVal && !bDoneProcessingComponent && sErrMsg.isEmpty() && !stream.atEnd())
	{
		stream.readNext();
		if (stream.error())
		{	bRetVal = false;
			QString sErr = QObject::tr("   ERROR - %1 in file '%2' at line %3, column %4")
														.arg(stream.errorString())
														.arg(fileName)
														.arg(stream.lineNumber())
														.arg(stream.columnNumber());
			sErrMsg = sErr.toLocal8Bit().constData();
			//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
			// SAC 6/28/16 - added more error tracking/reporting code
			if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
			{	piDBIDSetFailures[ iDBIDSetFailureIdx ] = (lThisElemDBID > 0 ? lThisElemDBID : iBEMClassIdx);
				if (piObjIdxSetFailures)
					piObjIdxSetFailures[ iDBIDSetFailureIdx ] = -1; // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
				if (psaDataSetFailures)
					SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrMsg );
				iDBIDSetFailureIdx++;
				BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, true /*m_bSupressAllMessageBoxes*/ );
			}
		}
		else
		{
#ifdef _DEBUG
//			WriteTokenToLog( stream );
#endif
			switch (stream.tokenType())
			{	case QXmlStreamReader::NoToken         : assert( FALSE );   break;  // see what conditions we end up here
				case QXmlStreamReader::Invalid         : assert( FALSE );   break;  // see what conditions we end up here
				case QXmlStreamReader::StartElement    : {	siXMLElementCount++;
																			iLocalElementCount++;
																			sElementName = stream.name().toLocal8Bit().constData();
																			bElementIsName = (sElementName.compare("Name", Qt::CaseInsensitive) == 0);
																			if (!bElementIsName)
																			{	assert( sElementName.compare( szTreeState, Qt::CaseInsensitive ) != 0 ); 		// need to implement TreeState reading compat
																				assert( sElementName.compare( "Parent", Qt::CaseInsensitive ) != 0 );         // need to implement Parent property compat
																				lThisElemDBID = BEMPX_GetDatabaseID( sElementName, iBEMClassIdx );
																				if (lThisElemDBID > BEM_COMP_MULT)
																					bPostDataForThisElement = TRUE;
																				else
																				{
																					if (pszClassPrefix && strlen( pszClassPrefix ) > 0)  // SAC 10/24/18
																						sElementName.prepend( pszClassPrefix );
																					int iNewClassID = BEMPX_GetDBComponentID( sElementName.toLocal8Bit().constData() );
																					int iChildBEMMapGroupID = -1;		// SAC 5/7/14
																					if (iNewClassID < 1)
																						iChildBEMMapGroupID = FindOldCompMapGroupID( pCompMap, sElementName, lFileVersion, NULL );
																									assert( iNewClassID > 0 || iBEMMapGroupID < 0 );	// is it OK to have CHILDREN of objects undergoing component mapping (??) - which object should the new child's PARENT be??
																					if (iNewClassID > 0 || iChildBEMMapGroupID >= 0)
																					{	// Read/process CHILD object
																						if (!bObjectCreated)
																						{	
																							if (bStoreData)  // 11/29/13
																							{	// CREATE OBJECT  (iff it has not yet been created, which will happen only if NO properties are specified (other than Name) prior to encountering a child object in the XML file
																								if (iBEMMapGroupID < 0)
																									pBEMObject = BEMPX_CreateObject( iBEMClassIdx, sObjectName.toLocal8Bit().constData(), NULL /*pParent*/,
																																				BEMO_User /*eObjType*/, TRUE, bIsUserInputMode, iBEMProcIdx );
																								else	// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
																									pBEMObject = CreateCompMapObjects(	pCompMap, iBEMMapGroupID, iCMIdx, i1BEMMapGroupNewClasses, iBEMProcIdx,
																																					sObjectName.toLocal8Bit().constData(), bIsUserInputMode, pivMapCompsCreated );
																								if (pBEMObject)
																								{	bObjectCreated = TRUE;
																									PostAttributesToObject( pBEMObject, pAttribs, iBEMProcIdx );
																							}	}
																							else
																							{	//if (pBEMClass && piObjPropCounts)
																								//	VERIFY( pBEMClass->IncrementPropertyCounts( piObjPropCounts, iBEMProcIdx ) );  // SAC 10/30/13
																								bObjectCreated = TRUE;  // fake it when reading but not storing project data
																							}
																							if (!bObjectCreated)
																							{	assert( FALSE );
																								bRetVal = false;
																								sErrMsg = QString( "ERROR:  Unable to create SDDXML %1 object '%2' (line %3):  %4" ).arg( (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, QString::number(stream.lineNumber()), fileName );
																							}
																						}
																						if (bRetVal)
																						{
																							QXmlStreamAttributes childAttribs = stream.attributes();		// SAC 10/25/18 - enable capture of attributes for non-SDDXML (gbXML) files
																							QXmlStreamAttributes* pChildAttribs = NULL;
																							if (!bIsUserInputMode && childAttribs.size() > 0)
																								pChildAttribs = &childAttribs;
//#ifdef _DEBUG
//			QString sDbg = QString("   reading %1 component - Line %2, column %3").arg(sElementName).arg(stream.lineNumber()).arg(stream.columnNumber());
//		   BEMPX_WriteLogFile( sDbg );
//#endif
																							bRetVal = ReadXMLComponent( fileName, stream, sElementName, iNewClassID, bIsUserInputMode, iBEMProcIdx, sErrMsg, bStoreData, piObjPropCounts, pStraightMap,
																																	lDBIDVersion, lFileVersion, pCompMap, pPropMap, pivMapCompsCreated, iDBIDSetFailureIdx, iMaxDBIDSetFailures, 
																																	piDBIDSetFailures, piObjIdxSetFailures, psaDataSetFailures, pChildAttribs, pszClassPrefix );
																						}
																					}
																					else
																					{  // SAC 3/22/14 - added code to enable backward compatibility via BEMStraightMap* argument
																						bPostDataForThisElement = FALSE;
																						if (pStraightMap)
																						{	int iSMIdx = -1;
																							while (lThisElemDBID < BEM_COMP_MULT && pStraightMap[++iSMIdx].szOldPropType != NULL)
																								if ( pStraightMap[iSMIdx].iVersionCutoff >= lFileVersion  &&
																										sElementName.compare( pStraightMap[iSMIdx].szOldPropType, Qt::CaseInsensitive ) == 0 && BEMPX_GetDBComponentID( pStraightMap[iSMIdx].szClassName ) == iBEMClassIdx )
																								{	lThisElemDBID = BEMPX_GetDatabaseID( pStraightMap[iSMIdx].szNewPropType, iBEMClassIdx );
																									if (lThisElemDBID > BEM_COMP_MULT)
																									{	bPostDataForThisElement = pStraightMap[iSMIdx].bPostMappedData;
																										lLastElemDBID = 0;		// SAC 10/19/15 - prevent this property from being mis-characterized as the same as the last one, simply because it maps to the same property name
																								}	}
																						}
																						// SAC 5/7/14 - handle via Comp/Prop mappings
																						if (lThisElemDBID < BEM_COMP_MULT && iBEMMapGroupID >= 0)
																						{	int iPMIdx = -1;
																							while (lThisElemDBID < BEM_COMP_MULT && pPropMap[++iPMIdx].iCompTypeID > 0)
																								if ( pPropMap[iPMIdx].iVersionCutoff >= lFileVersion  &&
																									  pPropMap[iPMIdx].iCompTypeID == iBEMMapGroupID  &&
																									  ( pPropMap[iPMIdx].szOldPropType == NULL  ||  sElementName.compare( pPropMap[iPMIdx].szOldPropType ) == 0 ) )
																								{	int i1MapClass = BEMPX_GetDBComponentID( pPropMap[iPMIdx].szNewCompType );							assert( i1MapClass > 0 );
																									// BEMObject* pMapObject = BEMPX_GetObjectByClass( i1MapClass, iError, -1, BEMO_User, iBEMProcIdx );	assert( pMapObject );
																									// int iMapObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( i1MapClass, iError, iBEMProcIdx ), pMapObject, iBEMProcIdx );
																									QString sMapPropType = ( pPropMap[iPMIdx].szNewPropType == NULL ? sElementName : pPropMap[iPMIdx].szNewPropType );
																									int i1MapPropTypeIdx = BEMPX_GetPropertyTypeIndexByShortName( i1MapClass, sMapPropType.toLocal8Bit().constData(), iBEMProcIdx );
																									// pPropType = BEMPX_GetPropertyType( i1MapClass, i1MapPropTypeIdx, iBEMProcIdx );						assert( pPropType );
																									lThisElemDBID = BEMPX_GetDBID( i1MapClass, i1MapPropTypeIdx, 1 );
																									bPostDataForThisElement = pPropMap[iPMIdx].bPostMappedData;
																									lLastElemDBID = 0;		// SAC 10/19/15 - prevent this property from being mis-characterized as the same as the last one, simply because it maps to the same property name
																								}
																						}

																						if (lThisElemDBID < BEM_COMP_MULT)
																						{	bRetVal = false;
																							//sErrMsg = QString( "ERROR:  Unrecognized %s property or child object type '%s' (line %ld):  %s", (pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sElementName, (long) stream.lineNumber(), fileName );
																							sErrMsg = QString( "   ERROR - reading file: component %1 '%2' includes unrecognized property '%3' on line # %4" ).arg( 
																															(pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sObjectName, sElementName, QString::number(stream.lineNumber()) );
																							// SAC 6/28/16 - added more error tracking/reporting code
																							if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
																							{	piDBIDSetFailures[ iDBIDSetFailureIdx ] = (lThisElemDBID > 0 ? lThisElemDBID : iBEMClassIdx);
																								if (piObjIdxSetFailures)
																									piObjIdxSetFailures[ iDBIDSetFailureIdx ] = -1; // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
																								if (psaDataSetFailures)
																									SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrMsg );
																								iDBIDSetFailureIdx++;
																								BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, true /*m_bSupressAllMessageBoxes*/ );
																								sErrMsg.clear();  // enable reading/parsing to continue
																								bRetVal = true;
																							}
																						}
																					}
																				}

																				if (lThisElemDBID > BEM_COMP_MULT)
																				{	// check for array index defined via element attributes (... index="0" ...)
																					QXmlStreamAttributes attribs = stream.attributes();
																					int iNumAttribs = attribs.size();
																					int i0AttribArrIdx = -1;
																					for (int iA=0; (i0AttribArrIdx < 0 && iA < iNumAttribs); iA++)
																					{	QString sAttribName = attribs.at(iA).name().toLocal8Bit().constData();
																						if (sAttribName.compare("index", Qt::CaseInsensitive)==0)
																						{	int iTemp = (int) atol( attribs.at(iA).value().toLocal8Bit().constData() );
																							int iArrayLen = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( lThisElemDBID ), BEMPX_GetPropertyID( lThisElemDBID ), iBEMProcIdx );
																							if (iTemp < 0 || iTemp >= iArrayLen)
																							{	bRetVal = false;
																								//sErrMsg.Format( "ERROR:  Invalid array index %d (valid range: 0-%d) specified for %s property '%s' (line %ld):  %s", iTemp, iArrayLen-1,
																								//							(pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sElementName, (long) stream.lineNumber(), fileName );
																								sErrMsg = QString( "   ERROR - invalid array index %1 (valid range: 0-%2) specified for %3 property '%4' on line # %5" ).arg( QString::number(iTemp), QString::number(iArrayLen-1),
																															(pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sElementName, QString::number(stream.lineNumber()) );
																								// SAC 6/28/16 - added more error tracking/reporting code
																								if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
																								{	piDBIDSetFailures[ iDBIDSetFailureIdx ] = (lThisElemDBID > 0 ? lThisElemDBID : iBEMClassIdx);
																									if (piObjIdxSetFailures)
																										piObjIdxSetFailures[ iDBIDSetFailureIdx ] = -1; // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
																									if (psaDataSetFailures)
																										SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrMsg );
																									iDBIDSetFailureIdx++;
																									BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, true /*m_bSupressAllMessageBoxes*/ );
																									sErrMsg.clear();  // enable reading/parsing to continue
																									bRetVal = true;
																								}
																							}
																							else
																								i0AttribArrIdx = iTemp;
																						}
																					}

																					if (i0AttribArrIdx >= 0)
																						i0ArrIdx = i0AttribArrIdx;
																					else if (lThisElemDBID == lLastElemDBID)
																						// same element as last one, so increment the array index
																						i0ArrIdx++;
																					else
																						// processing a NEW property of the loacal component
																						i0ArrIdx = 0;
																				}
																				lLastElemDBID = lThisElemDBID;
																			}
																		}  break;
				case QXmlStreamReader::EndElement      :  {	QString sEndElemName = stream.name().toLocal8Bit().constData();
																			BOOL bEndMainComponent = (pBEMClass && (sEndElemName.compare( pBEMClass->getShortName(), Qt::CaseInsensitive )==0 ||
																																 sEndElemName.compare( pBEMClass->getLongName() , Qt::CaseInsensitive )==0)); 
																			if (bEndMainComponent)
																			{	//assert( iInitialIndentLevel == siLastIndent );  // doesn't necessarily have to be the case...
																				if (!bObjectCreated)
																				{	if (bStoreData)
																					{	// CREATE OBJECT  (iff it has not yet been created, which will happen only if NO properties are specified (other than Name) for this component
																						if (iBEMMapGroupID < 0)
																							pBEMObject = BEMPX_CreateObject( iBEMClassIdx, sObjectName.toLocal8Bit().constData(), NULL /*pParent*/,
																																BEMO_User /*eObjType*/, TRUE, bIsUserInputMode, iBEMProcIdx );
																						else	// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
																							pBEMObject = CreateCompMapObjects(	pCompMap, iBEMMapGroupID, iCMIdx, i1BEMMapGroupNewClasses, iBEMProcIdx,
																																			sObjectName.toLocal8Bit().constData(), bIsUserInputMode, pivMapCompsCreated );
																						if (pBEMObject)
																						{	bObjectCreated = TRUE;
																							PostAttributesToObject( pBEMObject, pAttribs, iBEMProcIdx );
																					}	}
																					else
																					{	//if (pBEMClass && piObjPropCounts)
																						//	VERIFY( pBEMClass->IncrementPropertyCounts( piObjPropCounts, iBEMProcIdx ) );  // SAC 10/30/13
																						bObjectCreated = TRUE;  // fake it when reading but not storing project data
																					}
																					if (!bObjectCreated)
																					{	assert( FALSE );
																						bRetVal = false;
																						sErrMsg = QString( "ERROR:  Unable to create SDDXML %1 object '%2' (line %3):  %4" ).arg( (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, QString::number(stream.lineNumber()), fileName );
																				// abort on this error ??
																					}
																				}
																				bDoneProcessingComponent = TRUE;
																			}
																			else
																			{	//assert( sPropertyBeingProcessed.compare( sElementName )==0 );
																				sElementName.clear();
																				bElementIsName = FALSE;
																				sPropertyBeingProcessed.clear();
																			}
																		}  break;
				case QXmlStreamReader::Characters      :  {	QString sChars = stream.text().toLocal8Bit().constData();
																			if (CharsAreAllSpaces( sChars ))
																			{	siLastIndent = stream.text().length();
																				SetIndentString( ssLastIndentChars, siLastIndent );
																			}
																			else
																			{	// assert( siLastIndent > iInitialIndentLevel ); - fails w/ mult elements on same line, like "Coord"
																				if (bElementIsName)
																				{	//assert( iLocalElementCount < 5 );		// 'Name' should be first element listed - SAC 9/1/13 - revised to allow name to be supplied later in group of elements
																					if (sChars.compare( "unknown", Qt::CaseInsensitive )==0)
																						sObjectName.clear();
																					else
																						sObjectName = sChars;
																				}
																				else
																				{
																					if (!bObjectCreated)
																					{	if (bStoreData)
																						{	// CREATE OBJECT
																							if (iBEMMapGroupID < 0)
																								pBEMObject = BEMPX_CreateObject( iBEMClassIdx, sObjectName.toLocal8Bit().constData(), NULL /*pParent*/,
																																	BEMO_User /*eObjType*/, TRUE, bIsUserInputMode, iBEMProcIdx );
																							else	// SAC 5/7/14 - migrated code from *ibd reading to handle backward compatibility component mappings
																								pBEMObject = CreateCompMapObjects(	pCompMap, iBEMMapGroupID, iCMIdx, i1BEMMapGroupNewClasses, iBEMProcIdx,
																																				sObjectName.toLocal8Bit().constData(), bIsUserInputMode, pivMapCompsCreated );
																							if (pBEMObject)
																							{	bObjectCreated = TRUE;
																								PostAttributesToObject( pBEMObject, pAttribs, iBEMProcIdx );
																						}	}
																						else
																						{	//if (pBEMClass && piObjPropCounts)
																							//	VERIFY( pBEMClass->IncrementPropertyCounts( piObjPropCounts, iBEMProcIdx ) );  // SAC 10/30/13
																							bObjectCreated = TRUE;  // fake it when reading but not storing project data
																						}
																						if (!bObjectCreated)
																						{	assert( FALSE );
																							bRetVal = false;
																							sErrMsg = QString( "ERROR:  Unable to create SDDXML %1 object '%2' (line %3):  %4" ).arg( (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, QString::number(stream.lineNumber()), fileName );
																					// abort on this error ??
																						}
																					}
                                                      	
																					if (bRetVal)
																					{	assert( lThisElemDBID > BEM_COMP_MULT );
																						if (lThisElemDBID > BEM_COMP_MULT)
																						{	if (sChars.compare( "unknown", Qt::CaseInsensitive ) == 0)		// don't bother to set data to BEMBase is the selection is 'unknown'
																							{	assert( FALSE );  // be aware of 'unknown' data...
																								// WRITE WARNING MESSAGE TO PROJECT LOG FILE INDENTIFYING 'UNKNOWN' DATA IN XML FILE
																								QString sLogMsg = QString( "Warning: SDDXML data 'unknown' for property %1, %2 object '%3' (line %4):  %5" ).arg( sElementName, (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, QString::number(stream.lineNumber()), fileName );
																					         BEMPX_WriteLogFile( sLogMsg, NULL, FALSE, FALSE /*m_bSupressAllMessageBoxes*/ );  // SAC 4/27/03
																							}
																							else
																							{
																								BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lThisElemDBID, iError, iBEMProcIdx );
																								if (pPropType == NULL)
																								{	bRetVal = false;
																									//sErrMsg.Format( "ERROR:  Unable to locate %s property '%s' (line %ld):  %s", (pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sElementName, (long) stream.lineNumber(), fileName );
																									sErrMsg = QString( "   ERROR - reading file: component %1 '%2' includes unrecognized property '%3' on line # %4" ).arg(
																																(pBEMClass ? pBEMClass->getShortName() : "<unknown object type>"), sObjectName, sElementName, QString::number(stream.lineNumber()) );
																									// SAC 6/28/16 - added more error tracking/reporting code
																									if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
																									{	piDBIDSetFailures[ iDBIDSetFailureIdx ] = (lThisElemDBID > 0 ? lThisElemDBID : iBEMClassIdx);
																										if (piObjIdxSetFailures)
																											piObjIdxSetFailures[ iDBIDSetFailureIdx ] = -1; // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
																										if (psaDataSetFailures)
																											SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrMsg );
																										iDBIDSetFailureIdx++;
																										BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, true /*m_bSupressAllMessageBoxes*/ );
																										sErrMsg.clear();  // enable reading/parsing to continue
																										bRetVal = true;
																									}
																								}
																								else
																								{
                     																		   BEM_PropertyStatus ePropStat = BEMS_UserDefined;
                     																		
                     																		   // Set the lDBID which is used to post the data read into the database
                     																		   long lDBID = lThisElemDBID + i0ArrIdx;  // + 1;
                     																		   int iSet = 0;

																								// SAC 8/13/15 - added code to prevent setting of this property based on BEMDataType:m_iNotInputMode (and m_eCompDataType == BEMD_NotInput...)
																										QString sErrMsg2;
																										bool bNotInputError = false;
																		                        if (ePropStat != BEMS_Undefined && lThisElemDBID > 0 && bIsUserInputMode)

																		                        {	assert( pPropType->getNumPropTypeDetails() > i0ArrIdx );
																										//	POSITION pos = pPropType->m_olDataTypes.FindIndex( i0ArrIdx );
																										//	BEMDataType* pDT = (BEMDataType*) pPropType->m_olDataTypes.GetAt( pos );		assert( pDT );
																											BEMPropTypeDetails* pDT = pPropType->getPropTypeDetails( i0ArrIdx );			assert( pDT );
																											if (pDT && pDT->getCompDataType() == BEMD_NotInput && pDT->getNotInputMode() != DTNotInp_AllowUIReset)
																											{	ePropStat = BEMS_Undefined;
																												bNotInputError = (pDT->getNotInputMode() == DTNotInp_ErrorIfInput);
																												if (!pDT->getNotInputMsg().isEmpty())
																												{	QString sMsg, sMsgEnd;
																													if (i0ArrIdx > 0)
																														sMsgEnd = QString( "[%1]" ).arg( QString::number(i0ArrIdx+1) );
																													else
																														sMsgEnd = "";
																													if (bNotInputError)
																													{	sMsg = QString( "   Error:  %1  (%2 '%3' %4%5, line: %6)" ).arg( pDT->getNotInputMsg(), (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, pPropType->getShortName(), sMsgEnd, QString::number(stream.lineNumber()) );
																														sErrMsg2 = sMsg;
																													}
																													else
																														sMsg = QString( "   %1  (%2 '%3' %4%5)" ).arg( pDT->getNotInputMsg(), (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, pPropType->getShortName(), sMsgEnd );
																													BEMPX_WriteLogFile( sMsg, NULL, FALSE, FALSE /*m_bSupressAllMessageBoxes*/ );
																										}	}	}

                     																		   // SAC 10/5/00 - Added code to intercept certain DBID that have been converted from BEMP_Int to BEMP_Sym
                     																		   int iTempPropType = pPropType->getPropType();

                     																		   QString sErrantData;  // SAC 7/10/03 - added to facilitate more informative error reporting
                     																		   switch ( iTempPropType )
                     																		   {  // read the data and post it to the database
                     																		      case BEMP_Int : {  long lTemp = atol( sChars.toLocal8Bit().constData() );			// long lTemp = m_file.ReadLong();
                     																		                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined && bStoreData && bPostDataForThisElement)  // SAC 10/19/01 - added reference to bPostData
                     																		                        {
                     																		                           iSet = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lTemp,
                     																		                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
                     																		                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
                     																		                              sErrantData = sChars;		// sErrantData.Format( "%d", lTemp );
                     																		                        }
                     																		                        if (lDBID == lDBIDVersion)
                     																		                           lFileVersion = lTemp;
                     																		                        break;  }
                     																		      case BEMP_Flt : {  double fTemp = atof( sChars.toLocal8Bit().constData() );       // float fTemp = m_file.ReadFloat();
                     																		                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined && bStoreData && bPostDataForThisElement)  // SAC 10/19/01 - added reference to bPostData
                     																		                        {
                     																		                           iSet = BEMPX_SetBEMData( lDBID, BEMP_Flt, (void*) &fTemp,
                     																		                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
                     																		                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
                     																		                              sErrantData = sChars;		// sErrantData.Format( "%g", fTemp );
                     																		                        }
                     																		                        break;  }
                     																		      case BEMP_Sym :
                     																		      case BEMP_Str : {  QString sTemp = sChars;		// QString sTemp = m_file.ReadString( TRUE );  // SAC 6/17/01 - added argument to ALLOW reading beyond carriage return
																		                           						bool bNotSymOrNotNull = (iTempPropType != BEMP_Sym || sTemp.compare("(null)")!=0 ? true : false);	// SAC 4/7/16 - prevent storing enums = "(null)"
                     																		                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined && bNotSymOrNotNull && bStoreData && bPostDataForThisElement)  // SAC 10/19/01 - added reference to bPostData
                     																		                        {
                     																		                           iSet = BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &sTemp,  // BEMP_Str, (void*) sTemp.toLocal8Bit().constData(),
                     																		                                                 BEMO_User, -1 /*iObjIdx*/, ePropStat, BEMO_User /*eObjType*/, FALSE, iBEMProcIdx );
																		                                             	if (iSet < 0 && (!pPropType->getShortName().compare("Ruleset", Qt::CaseInsensitive) || !pPropType->getDescription().compare("Ruleset", Qt::CaseInsensitive)))
                                             																				iSet = 0;	// SAC 12/3/15 - ignore read errors where Ruleset not valid or not found (port fix from 11/22 made for *ibd files)
                     																		                           if (iSet < 0)  // SAC 7/10/03 - added to facilitate more informative error reporting
                     																		                              sErrantData = sTemp;
                     																		                        }
                     																		                        break;  }
                     																		      case BEMP_Obj : {  QString sTemp = sChars;		// QString sTemp = m_file.ReadString( TRUE );
                     																		                        // iError;
                     																		                        if (/*bPostData &&*/ ePropStat != BEMS_Undefined && bStoreData && bPostDataForThisElement)  // SAC 10/19/01 - added reference to bPostData
                     																		                        {
                     																		                           BEMProperty* pProp = BEMPX_GetProperty( lDBID, iError, -1 /*iObjIdx*/, BEMO_User /*eObjType*/, iBEMProcIdx );
                     																		                           if (pProp)
                     																		                           {
                     																		                              pProp->setDataStatus( ePropStat );
                     																		                              pProp->setString( sTemp );
                     																		                              pProp->setObj( NULL );
                     																		                           }
                     																		                        }
                     																		                        break;  }
                     																		      default : 
                     																		         assert( FALSE );		// m_file.ThrowFormatException(); // should never happen
                     																		         break;
                     																		   }
//#ifdef _DEBUG
//			QString sDbg = QString("      just set %1 '%2' %3 - Line %4, column %5").arg((pBEMClass ? pBEMClass->getShortName() : "<unknown type>")).arg(sObjectName).arg(sElementName).arg(stream.lineNumber()).arg(stream.columnNumber());
//		   BEMPX_WriteLogFile( sDbg );
//#endif

                     																		   if (iSet < 0 || bNotInputError)
                     																		   {  // throw error message if data not successfully posted to database
																											//sErrMsg2.Format( "   ERROR - unable to post '%s' to property %s, %s object '%s' on line # %ld", sChars, sElementName,
																											//								(pBEMClass ? pBEMClass->getShortName() : "<unknown type>"), sObjectName, (long) stream.lineNumber() );
																											sErrMsg2 = QString( "   ERROR - reading file: %1 '%2' property %3  =  '%4' on line # %5" ).arg( (pBEMClass ? pBEMClass->getShortName() : "<unknown type>"),
																																			 sObjectName, sElementName, sChars, QString::number(stream.lineNumber()) );
																											// SAC 6/28/16 - added more error tracking/reporting code
																											if (iDBIDSetFailureIdx < iMaxDBIDSetFailures)
																											{	piDBIDSetFailures[ iDBIDSetFailureIdx ] = (lThisElemDBID > 0 ? lThisElemDBID : iBEMClassIdx);
																												if (piObjIdxSetFailures)
																													piObjIdxSetFailures[ iDBIDSetFailureIdx ] = -1; // (iObjIdx >= 0 ? iObjIdx : BEMPX_GetObjectIndex( BEMPX_GetClass( i1CurClass, iError, iBEMProcIdx ), newObject, iBEMProcIdx ));
																												if (psaDataSetFailures)
																													SetAtGrow( psaDataSetFailures, iDBIDSetFailureIdx, sErrMsg2 );
																												iDBIDSetFailureIdx++;
																												BEMPX_WriteLogFile( sErrMsg2, NULL, FALSE, true /*m_bSupressAllMessageBoxes*/ );
																											}
																										}
                                                                        }
                                                                   	}
                                                               	}
																					}
																				}	// end of:  if element NOT Name
																			}  // end of:  if there are characters OTHER THAN space/tab/null
																		}	break;

				case QXmlStreamReader::Comment               :  assert( FALSE );   break;  // see what conditions we end up here
				case QXmlStreamReader::DTD                   :  assert( FALSE );   break;  // see what conditions we end up here
				case QXmlStreamReader::EntityReference       :  assert( FALSE );   break;  // see what conditions we end up here
				case QXmlStreamReader::ProcessingInstruction :  assert( FALSE );   break;  // see what conditions we end up here
				default                                      :  assert( FALSE );   break;  // see what conditions we end up here
			}
			//int iHere = 0;
		}
	}

	assert( ( ( bRetVal &&  sErrMsg.isEmpty()) ||
				 (!bRetVal && !sErrMsg.isEmpty()) ) );   // confirm negative retval w/ error message populated -OR- positive retval w/ no error message

	if (bRetVal && iNumDataSetFailures > 0)	// SAC 8/13/15
	{	bRetVal = false;	// return false if there are any data set failures
		assert( sErrMsg.isEmpty() );	// if here, sErrMsg should still be blank...?
		if (sErrMsg.isEmpty())
		{	if (iNumDataSetFailures < 2)
				sErrMsg = sErrMsgFirstDataSetFailure;
			else
				sErrMsg = QString( "%1  (and %2 other data setting failures listed in log file)" ).arg( sErrMsgFirstDataSetFailure, QString::number(iNumDataSetFailures-1) );
	}	}

	if (!bRetVal && sErrMsg.isEmpty())
	{	QString sErr = QObject::tr("%1\nLine %2, column %3")
													.arg(stream.errorString())
													.arg(stream.lineNumber())
													.arg(stream.columnNumber());
		sErrMsg = sErr.toLocal8Bit().constData();
		//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
	}

// debugging
//if (bRetVal)
//{	assert( pBEMObject );
//	QString sLogMsg = QString( "   done reading %1 '%2' on line %3, column %4" ).arg( pBEMObject->getClass()->getShortName(), pBEMObject->getName(),
//													QString::number(stream.lineNumber()), QString::number(stream.columnNumber()) );
//   BEMPX_WriteLogFile( sLogMsg );
//}

	return bRetVal;
}

////////////////////////////////////////////////////////////
bool ReadXMLFile( const char* fileName, int iFileMode, /*int iBEMProcIdx,*/ long lDBIDVersion, int iBEMProcIdx,
						QString& sRulesetFilename, BOOL bReturnRulesetFilename,
                  int iMaxDBIDSetFailures, int* piDBIDSetFailures,  // SAC 5/12/00 - enable UI reporting of failed data setting
                  BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
                  int* piObjIdxSetFailures /*=NULL*/, QStringList* psaDataSetFailures /*=NULL*/,   // SAC 7/10/03 - added to facilitate more informative error reporting
						BOOL bLogDurations /*=FALSE*/, BOOL bStoreData /*=TRUE*/,   // SAC 10/24/13 - added duration logging  // SAC 10/29/13 - added bStoreData
						int* piObjPropCounts /*=NULL*/, BEMStraightMap* pStraightMap,   // SAC 10/30/13 - added to facilitate bulk memory allocation of BEMObject & BEMProperty objects
						BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap, 
						const char* pszClassPrefix )		// SAC 10/24/18 - added pszClassPrefix
{	bool bRetVal = true;
	ptime t1(microsec_clock::local_time());  // SAC 10/24/13
	QString sFileName = fileName;
	QFile file( sFileName );
	if (!file.open( QFile::ReadOnly | QFile::Text ))
		return false;
	else
	{
		QXmlStreamReader stream( &file );

		QString sErrMsg;
		siXMLElementCount = 0;
		bool bIsUserInputMode = (iFileMode == BEMFM_INPUT);
		bool bDoneProcessingFile = false;
		QString sElemName;
		long lFileVersion = 0;  // SAC 3/22/14
      QVector<int> ivMapCompsCreated;
   	int iDBIDSetFailureIdx = 0;   // SAC 6/28/16
		while (bRetVal && sErrMsg.isEmpty() && !bDoneProcessingFile && !stream.atEnd())
		{
			stream.readNext();
			if (stream.error())
			{	bRetVal = false;
				QString sErr = QObject::tr("Error: %1 in file '%2' at line %3, column %4")
															.arg(stream.errorString())
															.arg(fileName)
															.arg(stream.lineNumber())
															.arg(stream.columnNumber());
				sErrMsg = sErr.toLocal8Bit().constData();
				//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
			}
			else
			{
#ifdef _DEBUG
//				WriteTokenToLog( stream );
#endif
				switch (stream.tokenType())
				{	case QXmlStreamReader::NoToken               : assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::Invalid               : assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::StartElement          : {	siXMLElementCount++;
																						sElemName = stream.name().toLocal8Bit().constData();
																						if (siXMLElementCount == 1 && iFileMode == BEMFM_INPUT &&   // SAC 10/24/18 - added iFileMode to enable gbXML & other file types
																							 sElemName.compare("SDDXML", Qt::CaseInsensitive) != 0)
																						{	// ERROR - not a SDDXML file (??)
																							bRetVal = false;
																							sErrMsg = QString( "ERROR:  File not SDDXML, first element '%1' (expected 'SDDXML' on line %2):  %3" ).arg( sElemName, QString::number(stream.lineNumber()), fileName );
																						}
																						else if (sElemName.compare("SDDXML", Qt::CaseInsensitive) == 0)
																						{	// do nothing here
																						}
																						else if (sElemName.compare("RulesetFilename", Qt::CaseInsensitive) == 0)
																						{	//if (bReturnRulesetFilename)
																							//{	// check for ruleset filename defined via element attributes (... file="..." ...)
																								QXmlStreamAttributes attribs = stream.attributes();
																								int iNumAttribs = attribs.size();
																								for (int iA=0; (sRulesetFilename.isEmpty() && !bDoneProcessingFile && iA < iNumAttribs); iA++)
																								{	QString sAttribName = attribs.at(iA).name().toLocal8Bit().constData();
																									if (sAttribName.compare("file", Qt::CaseInsensitive)==0)
																									{	QString sTempRFN = attribs.at(iA).value().toLocal8Bit().constData();
																										if (!sTempRFN.isEmpty())
																										{	if (!bReturnRulesetFilename)	// SAC 3/22/14
																												// set this string to be the default which will be installed into the next created 'Project' component
																												BEMPX_SetRulesetFilename( sTempRFN.toLocal8Bit().constData() );
																											else
																											{	bDoneProcessingFile = true;
																												if (sTempRFN.compare("unknown", Qt::CaseInsensitive) != 0)
																													sRulesetFilename = sTempRFN;
																										}	}
																								}	}
																							//}
																						}
																						else
																						{	// in this loop we should ONLY encounter BEMBase components (not component properties)
																							QXmlStreamAttributes attribs = stream.attributes();
																							if (pszClassPrefix && strlen( pszClassPrefix ) > 0)  // SAC 10/24/18
																								sElemName.prepend( pszClassPrefix );
																							else
																							{	assert( attribs.size() == 0 );  // only element having attributes is 'RulesetFilename' processed (ignored) above (for SDDXML files)
																							}
																							int iBEMClassIdx = BEMPX_GetDBComponentID( sElemName.toLocal8Bit().constData() );
																							int iBEMMapGroupID = -1;		// SAC 5/7/14
																							if (iBEMClassIdx < 1)
																								iBEMMapGroupID = FindOldCompMapGroupID( pCompMap, sElemName, lFileVersion, NULL );
																							if (iBEMClassIdx < 1 && iBEMMapGroupID < 0)
																							{	bRetVal = false;
																								sErrMsg = QString( "ERROR:  Invalid object type '%1' encountered on line %2 of SDDXML file:  %3" ).arg( sElemName, QString::number(stream.lineNumber()), fileName );
																							}
																							else
																							{	if (bReturnRulesetFilename)
																									bDoneProcessingFile = true;  // if we have reached the point where a BEMBase object is being created, we are beyond where the ruleset filename should be specified
																								else
																								{
//#ifdef _DEBUG
//			QString sDbg = QString("   reading %1 component - Line %2, column %3").arg(sElemName).arg(stream.lineNumber()).arg(stream.columnNumber());
//		   BEMPX_WriteLogFile( sDbg );
//#endif
																									QXmlStreamAttributes* pAttribs = (pszClassPrefix && strlen( pszClassPrefix ) > 0 && attribs.size() > 0) ? &attribs : NULL;   // SAC 10/25/18
																									bRetVal = ReadXMLComponent( fileName, stream, sElemName, iBEMClassIdx, bIsUserInputMode, iBEMProcIdx, sErrMsg, bStoreData, piObjPropCounts,
																																			pStraightMap, lDBIDVersion, lFileVersion, pCompMap, pPropMap, &ivMapCompsCreated, iDBIDSetFailureIdx,
																																			iMaxDBIDSetFailures, piDBIDSetFailures, piObjIdxSetFailures, psaDataSetFailures, pAttribs, pszClassPrefix );
																								}
																							}
																						}
																					}  break;
					case QXmlStreamReader::EndElement            :  {	if (sElemName.compare("SDDXML" , Qt::CaseInsensitive) == 0 || sElemName.compare("RulesetFilename", Qt::CaseInsensitive) == 0 ||
																							 sElemName.compare("Project", Qt::CaseInsensitive) == 0 || sElemName.compare("Proj", Qt::CaseInsensitive) == 0)
																						{	// do nothing here
																						}
																						else
																						{	// assert( FALSE );   - SAC 9/1/13 - triggered by valid (Cons) element end...
																						}
																					}	break;  // see what conditions we end up here
					case QXmlStreamReader::Characters            :  if (CharsAreAllSpaces( stream.text().toLocal8Bit().constData() ))
																					{	siLastIndent = stream.text().length();
																						SetIndentString( ssLastIndentChars, siLastIndent );
																					}
																					break;
					case QXmlStreamReader::Comment               :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::DTD                   :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::EntityReference       :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::ProcessingInstruction :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::StartDocument         :
					case QXmlStreamReader::EndDocument           :  break;   // ignore these
					default                                      :  assert( FALSE );   break;  // see what conditions we end up here
				}
				//int iHere = 0;
			}
		}

		if (bLogDurations)  // SAC 10/24/13 - added duration logging
		{	ptime t2(microsec_clock::local_time());
			time_duration td = t2-t1;
			QString sLogMsg = QString( "         ReadXMLFile() - elapsed time for initial file %1: %2" ).arg( (bStoreData ? "parsing/posting" : "read"),
																	QString::number(((double) td.total_microseconds()) / 1000000.0, 'f', 3) );  // -or- %s -> to_simple_string(td).c_str() );
		   BEMPX_WriteLogFile( sLogMsg );
		}
				
//#ifdef _DEBUG
		if (!bRetVal && sErrMsg.isEmpty())
		{	QString sErr = QObject::tr("%1\nLine %2, column %3")
														.arg(stream.errorString())
														.arg(stream.lineNumber())
														.arg(stream.columnNumber());
			sErrMsg = sErr.toLocal8Bit().constData();
			//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
		}
//#endif

		if (!sErrMsg.isEmpty())
      {  BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03
         if (!bSupressAllMessageBoxes)
            BEMMessageBox( sErrMsg, NULL, 2 /*warning*/ );
		}

		if (bRetVal && !bReturnRulesetFilename && bStoreData)
      {
			t1 = microsec_clock::local_time();

			// resolve all object references - this is necessary because all object assignments are
      	// originally read and stored simply as character string names of the referenced objects.
      	// This function resolves those object names to actual object pointers.
      	// This object resolving cannot happen during the reading process, since an object
      	// can be assigned PRIOR to its definition in the file.
      	int iNumUnresolvedRefs = BEMP_ResolveAllReferences( BEMO_User, NULL, TRUE, iBEMProcIdx, bSupressAllMessageBoxes );
      	if (iNumUnresolvedRefs > 0)  // SAC 4/27/03
      	   bRetVal = FALSE;

			if (bLogDurations)  // SAC 10/24/13 - added duration logging
			{	ptime t2(microsec_clock::local_time());
				time_duration td = t2-t1;
				QString sLogMsg = QString( "         ReadXMLFile() - elapsed time for BEMPX_ResolveAllReferences(): %1" ).arg( QString::number(((double) td.total_microseconds()) / 1000000.0, 'f', 3) );  // -or- %s -> to_simple_string(td).c_str() );
			   BEMPX_WriteLogFile( sLogMsg );
			}
		}
	}
	siLastIndent = -1;
	ssLastIndentChars.clear();

	if (bReturnRulesetFilename)
		bRetVal = (!sRulesetFilename.isEmpty());

	return bRetVal;
}

