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

#ifndef __BEMPROC_H__
#define __BEMPROC_H__


#include <string>
#include <vector>
#include "BEMProcAPI.h"



inline bool equals(double d1, double d2)
{ return (d1 < (d2+0.000001) && d1 > (d2-0.000001)); }

inline bool WithinMargin(double d1, double d2, double d3)  // SAC 1/29/02 - Added to facilitate less precise checking due to float rounding
{ return (d1 < (d2+d3) && d1 > (d2-d3)); }


// enum used to identify the origin of the current database
enum BEMProcType
{
   BEMT_CBECC,
   BEMT_Other,			// if/when modified from value of '1', make corresponding change BEMCmpMgr*
   BEMT_NumTypes
};

// enum used to identify the origin of each component in the database
enum BEM_ObjType
{
   BEMO_User,
   BEMO_RuleLib,
   BEMO_UserLib,   
   BEMO_NumTypes
};

// enum used to identify the status of each property in the database
enum BEM_PropertyStatus
{
   BEMS_Undefined,
   BEMS_ProgDefault,
   BEMS_RuleDefault,
   BEMS_RuleLibrary,
   BEMS_RuleDefined,
   BEMS_UserDefault,
   BEMS_UserLibrary,
   BEMS_UserDefined,
   BEMS_SimResult,
   BEMS_NumTypes
};

// enum used to establish conditions under which screen controls are displayed or range checks are performed
enum BEM_Condition
{
   BEMC_Equal,
   BEMC_LessOrEqual,
   BEMC_GrtrOrEqual,
   BEMC_Less,
   BEMC_Greater,
   BEMC_NotEqual,
   BEMC_NumConditions
};

// enum used to identify the compliance category for each property type
// in the database (defined by the compliance ruleset)
enum BEM_CompDataType
{
   BEMD_Compulsory,
   BEMD_Required,
   BEMD_CondRequired,	// SAC 2/11/15 - added to better identify properties that MAY (or may not) be Required
   BEMD_Optional,
   BEMD_Default,
   BEMD_CriticalDef,
   BEMD_Prescribed,
   BEMD_NotInput,
   BEMD_NDataTypes
};

// special reserved array indices for parameter idx == 0
#define  BEM_PARAM0_ACTIVE   1
#define  BEM_PARAM0_NAME     2
#define  BEM_PARAM0_PARENT   3
#define  BEM_PARAM0_NEWPAR   4  // combo for assigning parent to object not yet created
#define  BEM_PARAM0_NEWCOPY  5  // combo for selecting an object to copy data from
#define  BEM_PARAM0_PARCLAS  6  // used to label parent assignment combos
#define  BEM_PARAM0_ACTION   7  // SAC 3/20/99 - used to allow ruleset to perform actions
#define  BEM_PARAM0_CREATE   8  // SAC 6/13/00 - used to allow screen button to initiate a component creation
#define  BEM_PARAM0_DELETE   9  // SAC 6/13/00 - used to allow screen button to delete the active component of a certain type
#define  BEM_PARAM0_CR8OPT  10  // SAC 9/18/13 - combo for selecting whether to import library object or create new object
#define  BEM_PARAM0_USERLIB 11  // SAC 9/18/13 - combo for selecting which user library object to import
#define  BEM_PARAM0_RULELIB 12  // SAC 9/18/13 - combo for selecting which rule library object to import

#define  BEMP_Int  0		// types of property (BEMPropertyType)
#define  BEMP_Flt  1
#define  BEMP_Sym  2
#define  BEMP_Str  3
#define  BEMP_Obj  4
#define  BEMP_QStr 5		// NOT unique storage type in database, only used in conjunction w/ BEMPX_SetBEMData() to pass QString directly in (since casting to const char* blasts special characters)


// -----------------------------------------------------------------------------
// File I/O
// -----------------------------------------------------------------------------

// SAC 10/18/01 - Added structures to facilitate mapping of old BEMProc Comp:Param entries from old files into new components and properties
struct BEMComponentMap
{
   int     iVersionCutoff;
   int     iCompTypeID;
   LPCSTR  szOldCompType;
   LPCSTR  szNewCompType[5];
};

struct BEMPropertyMap
{
   int     iVersionCutoff;
   int     iCompTypeID;
   LPCSTR  szOldPropType;
   LPCSTR  szNewCompType;
   LPCSTR  szNewPropType;
   BOOL    bPostMappedData;
};

struct BEMStraightMap  // SAC 11/14/01 - added another method of mapping old properties to new
{
   int     iVersionCutoff;
   LPCSTR  szClassName;		// SAC 1/27/14 - switched from int* pi1Class to NAME of class/object type
   LPCSTR  szOldPropType;
   LPCSTR  szNewPropType;
   BOOL    bPostMappedData;
};


// -----------------------------------------------------------------------------
// Rule Evaluation Error/Warning/Message Callback Function defines
// -----------------------------------------------------------------------------

// Msg/Warning/Error logging callback function mechanism
const int logMsgERROR   = 2;		// error (analysis should be aborted)
const int logMsgWARNING = 1;		// warning ()
const int logMsgMESSAGE = 0;		// message (fyi ...)
typedef void (CALLBACK* PLogMsgCallbackFunc) ( int iClassification, const char* pszErrorMsg, const char* pszHelpKey );
// end of - Msg/Warning/Error logging callback function mechanism

// ruleset error exports
int  BEMPROC_API __cdecl BEMPX_GetRulesetErrorCount();
bool BEMPROC_API __cdecl BEMPX_GetRulesetErrorMessage( int i1ErrMsgIdx, char* pszErrMsg, int iMsgBufferLen );
void BEMPROC_API __cdecl BEMPX_ClearRulesetErrors();
void BEMPROC_API __cdecl BEMPX_AddRulesetError( const char* pszErrMsg );

// SAC 3/27/20 - routines to clear and add to mapping of Transform to BEMProcIdx (needed for enabling DataModel rules in Procedural rulsets)
void BEMPROC_API __cdecl BEMPX_ClearTransformBEMProcMap();
void BEMPROC_API __cdecl BEMPX_AddTransformBEMProcMap( int i1TransID, int i0BEMProcIdx );


extern BEMPROC_API int nBEMProc;

BEMPROC_API int fnBEMProc(void);


bool BEMPROC_API __cdecl BEMPX_GetUIActiveFlag();
void BEMPROC_API __cdecl BEMPX_SetUIActiveFlag( bool bActiveUI );


// Used to ensure consistent BEMProc version between ruleset and interface (started @ 22 for BEMProc vs. older versions)
//  22 -> 23 : SAC 1/24/12 - (text file ver 2) Addition of several Class and Property fields to facilitate cleaner/tighter XML interface, more parent types per class & default component naming
//  23 -> 24 : SAC 5/22/12 - (text file ver 3) Addition of new Property field to enable special handling of property exortation to simulation inputs (IBD or XML)
//  24 -> 25 : SAC 6/14/12 - (text file ver 4) Addition of multiple referencing object Class/TypeDBID/TypeValue combinations (1->5) (plus increased of class max child types 10->15)
//  25 -> 26 : SAC 3/3/14  - (text file ver 6) Addition of character string m_sInputClassInfo member to CBEMPropertyType to document properties whose input class varies based on BEMBase property data
//  26 -> 27 : SAC 2/4/15  - (no text file upd) Addition of integer m_iReportPrecision member to CBEMPropertyType to round values for output to compliance reports (export to analysis results XML files)
//  27 -> 28 : SAC 8/6/15  - (no text file upd) Addition of CStringArray member m_saPreviousNames of CBEMPropertyType to facilitate data model backward compatibility by tracking previous property names
//  28 -> 29 : SAC 12/29/16- (no text file upd) Addition of flag near beginning of file documenting whether BEMBroc was compiled by a "secure" version of code
//  29 -> 30 : SAC 9/11/18 - (text file ver 7) Increased max # class parent types from 15 to 20
#define  BEMPROC_VERSION  30


class  BEMClass;
class  BEMPropertyType;
class  BEMObject;
class  BEMProperty;
class  BEMSymDependencySet;

/////////////////////////////////////////////////////////////////////////////
// classes to facilitate rulelist evaluation debugging
class BEMPROC_API BEMCompNameTypeProp
{
public:
   BEMCompNameTypeProp() { m_compType = 0;  m_propertyType = 0;  m_array = 0; };
   BEMCompNameTypeProp( BEMCompNameTypeProp* pCNTP );
   ~BEMCompNameTypeProp();

public:
   BOOL Matches( int iBEMClass, long lDBID, BEMObject* pObj );

	QString getCompName()					{	return m_compName;  }
	void setCompName( QString sCN )		{	m_compName = sCN;  return;  }

	void setCompType( int iCT )			{	m_compType = iCT;  return;  }

	void setPropertyType( int iPT )		{	m_propertyType = iPT;  return;  }

	int  getArray()							{	return m_array;  }
	void setArray( int iA )					{	m_array = iA;  return;  }

private:
   QString m_compName;
   int     m_compType;
   int     m_propertyType;
   int     m_array;
};

class BEMPROC_API BEMCompNameTypePropArray
{
public:
   BEMCompNameTypePropArray() {  };
   ~BEMCompNameTypePropArray();

   void DeleteContents();

public:
   BOOL ReadData( const char* pszBEMCompNameTypePropListFile, int& iVerboseFlag, int& iLogRuleListEval );
   BOOL Copy( BEMCompNameTypePropArray* pCNTPA );
   BOOL MatchExists( long lDBID, int iOccur=-1, int iBEMProcIdx=-1 );
   BOOL RulelistMatchExists( const char* pszRulelistName );   // SAC 9/14/10

	int  getCompNameTypePropCount()								{	return (int) m_items.size();  }
	BEMCompNameTypeProp* getCompNameTypeProp( int idx )	{	return m_items.at(idx);  }

private:
   std::vector<BEMCompNameTypeProp*> m_items;

   QStringList m_rulelistNames;   // SAC 9/14/10 - added new member to facilitate echoing of each rule in a specified list of rulelists

   QString	m_dataFileName;  // SAC 8/5/10 - members to track whether or not data from specified file has already been read in
	UINT		m_fileTime;
	qint64	m_fileSize;

   int m_verboseFlag;       // SAC 8/5/10 - used for rulelist verbose (debugging) output...
   int m_logRuleListEval;
};


#define BEM_MODEL_MULT 1000000000   // added MODEL multiplier to facilitate longlong DBID (MDBID) values to identify which model to set/retrieve data to/from
#define BEM_COMP_MULT     1000000
#define BEM_PARAM_MULT       1000
#define BEM_MAX_COMP_ID       300  // SAC 4/13/19 - was:  214	// SAC 5/11/16
#define BEMPX_GetModelID(    lDBID )  (int)  (lDBID / BEM_MODEL_MULT)
#define BEMPX_GetClassID(    lDBID )  (int)  ((lDBID - ((lDBID / BEM_MODEL_MULT) * BEM_MODEL_MULT)) / BEM_COMP_MULT )
#define BEMPX_GetPropertyID( lDBID )  (int)  ((lDBID - ((lDBID / BEM_COMP_MULT ) * BEM_COMP_MULT )) / BEM_PARAM_MULT)
#define BEMPX_GetArrayID(    lDBID )  (int)  (lDBID % BEM_PARAM_MULT)
#define BEMPX_MDBIDtoDBID(  lMDBID )  (long) (lMDBID - ((lMDBID / BEM_MODEL_MULT) * BEM_MODEL_MULT))
#define BEMPX_DBIDtoMDBID( l0Model, lDBID )  (long long) ( ((long long) l0Model * BEM_MODEL_MULT) + (long long) lDBID )
#define BEMPX_GetDBID(           l1Class, l1Property, l1Array )  (long)      ( (l1Class * BEM_COMP_MULT) + (l1Property * BEM_PARAM_MULT) + l1Array )
#define BEMPX_GetMDBID( l0Model, l1Class, l1Property, l1Array )  (long long) ( ((long long) l1Class * BEM_COMP_MULT) + ((long long) l1Property * BEM_PARAM_MULT) + (long long) l1Array + ((long long) l0Model * BEM_MODEL_MULT) )

// Log file routines
void BEMPROC_API __cdecl BEMPX_EnableLogTimeStamps( bool bEnableTimeStamps );
bool BEMPROC_API __cdecl BEMPX_GetLogTimeStamps();
#define  BEMDEF_MAXLOGFILELINE  256
bool BEMPROC_API __cdecl BEMPX_WriteLogFile(   const char* output, const char* psNewLogFileName = NULL,
                                                          bool bBlankFile=false, BOOL bSupressAllMessageBoxes=FALSE,    // SAC 4/27/03 - added to prevent MessageBoxes during processing
																			 bool bAllowCopyOfPreviousLog=true,     // SAC 9/18/12 - new arg to allow/prevent log file copying
																			 const char** ppCSVColumnLabels=NULL );   // SAC 12/19/12 - new array of const char* ptrs (ending in a NULL) to facilitate project-based CSV analysis result archival
bool BEMPROC_API __cdecl BEMPX_WriteLogFile(   QString& output, const char* psNewLogFileName = NULL,
                                                          bool bBlankFile=false, BOOL bSupressAllMessageBoxes=FALSE,    // SAC 4/27/03 - added to prevent MessageBoxes during processing
																			 bool bAllowCopyOfPreviousLog=true,     // SAC 9/18/12 - new arg to allow/prevent log file copying
																			 const char** ppCSVColumnLabels=NULL );   // SAC 12/19/12 - new array of const char* ptrs (ending in a NULL) to facilitate project-based CSV analysis result archival
QString BEMPROC_API __cdecl BEMPX_GetLogFilename( bool bCSVLog=false );  // SAC 12/19/12
//const char*      __cdecl BEMPX_GetLogFilename( bool bCSVLog=false );  // SAC 12/19/12

void BEMPROC_API __cdecl BEMPX_OpenLogFile( const char* pszLogPathFile, bool bBlankFile=false );		// SAC 5/19/14
void BEMPROC_API __cdecl BEMPX_RefreshLogFile( bool bReOpenLog=true );	// SAC 5/19/14
void BEMPROC_API __cdecl BEMPX_CloseLogFile();		// SAC 5/19/14

void BEMPROC_API __cdecl BEMPX_CloseBEMProc( bool bShuttingDown=true, bool bCloseLogFile=true );

bool BEMPROC_API __cdecl BEMPX_SecureExecutable();

int  BEMPROC_API __cdecl BEMPX_CheckDataModelBin( const char* pszBinFileName );	// 0-OK, >0-error
BOOL BEMPROC_API __cdecl BEMPX_LoadDataModel(	const char* psBEMProcFileName = NULL, int iBEMType = BEMT_Other,		// was: BEMPX_InitBEMProc()
																const char* psInitLogFileName = NULL );

BOOL BEMPROC_API __cdecl BEMPX_LoadRuleset( LPCSTR fileName, BOOL bDeleteAllObjects=TRUE );							// was: RuleProcRead()
BOOL BEMPROC_API __cdecl BEMPX_ReadRulesetID( LPCSTR fileName, QString& sRuleSetID, QString& sRuleSetVer );		// was: RuleProcReadRulesetID()
BOOL BEMPROC_API __cdecl BEMPX_ReadBEMBaseFile( LPCSTR fileName, QString& sBEMBaseFile );								// was: RuleProcReadBEMBaseFile()
void BEMPROC_API __cdecl BEMPX_GetBEMBaseFile( QString& sBEMBaseFile, int iBEMProcIdx=-1 );	// was: BEMPX_GetBEMProcPathFile()

BOOL BEMPROC_API __cdecl BEMPX_GetRulesetID( QString& sRuleSetID, QString& sRuleSetVer );		// was: RuleProcGetRulesetID
BOOL BEMPROC_API __cdecl BEMPX_GetScreenFiles( QString& sScreensFN, QString& sToolTipsFN );	// was: RuleProcGetScreenFiles()
#define  RULESETORG_PROCEDURAL  1
#define  RULESETORG_DATAMODEL   2
int  BEMPROC_API __cdecl BEMPX_GetRulesetOrganization();	// was: RuleProcGetRulesetOrganization()

const char* __cdecl BEMPX_GetRulesetFilenameFromProjectFile( const char* fileName );

void BEMPROC_API __cdecl BEMPX_SetRulesetFilename( const char* fileName, BEM_PropertyStatus eStatus=BEMS_UserDefault );

int  BEMPROC_API __cdecl BEMPX_GetNumRuleToolTips();		// was: RuleProcGetNumRuleToolTips()
bool BEMPROC_API __cdecl BEMPX_GetRuleToolTipData( int i0TTIdx, QString& sTTText, long& lDBID, int idx=0 );	// was: RuleProcGetRuleToolTipData()

#define  BEMDMX_SIM    0  // SAC 8/23/12 - added export of simulation data model to facilitate synchronization of data model w/ other program modules
#define  BEMDMX_INP    1  // SAC 2/26/13 - added input version of DM export
#define  BEMDMX_INPMP  2  // SAC 10/31/13 - added input version of DM export that EXCLUDES Prescribed properties (MP-minus precribed)
bool BEMPROC_API __cdecl BEMPX_WriteDataModelExport( int iExportType, const char* pszDataModelOutFile );

int  BEMPROC_API __cdecl BEMPX_SetPropertiesToUserDefined( int iBEMProcIdx=-1 );

#define  BEMFM_INPUT   0  // SAC 5/22/12 - added new "simulation" mode
#define  BEMFM_DETAIL  1
#define  BEMFM_SIM     2
bool BEMPROC_API __cdecl BEMPX_ReadProjectFile(  const char* fileName, int iFileMode /*bool bIsInputMode*/, bool bRestore=FALSE,
                                                          bool bResultsOnly=FALSE, const char* pszLogFileExt=NULL,
                                                          int iBEMProcIdx=-1, long lDBIDVersion=0,
                                                          // SAC 5/12/00 - added following args to enable UI reporting of failed data setting
                                                          int iMaxDBIDSetFailures=0, int* piDBIDSetFailures=NULL,
                                                          BEMStraightMap* pStraightMap=NULL,  // SAC 11/14/01 - added another method of mapping old properties to new
                                                          // SAC 10/18/01 - Added new arguments to facilitate mapping of old BEMProc Comp:Param entries from old files into new ones
                                                          BEMComponentMap* pCompMap=NULL, BEMPropertyMap* pPropMap=NULL,
                                                          BOOL bSupressAllMessageBoxes=FALSE,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
                                                          int* piObjIdxSetFailures=NULL, QStringList* psaDataSetFailures=NULL,   // SAC 7/10/03 - added to facilitate more informative error reporting
																			 BOOL bLogDurations=FALSE, const char* pszClassPrefix=NULL );  // SAC 10/24/13 - added duration logging  // SAC 10/24/18 - added pszClassPrefix

// SAC 1/15/03 - Added argument to re-enable output of Undefined data when writing non-user input mode files (for backward compatibility)
// SAC 8/30/11 - added new argument to facilitate the writing of CSE input files directly from BEMProc databases
#define  BEMFT_Std     0
#define  BEMFT_CSE     1
#define  BEMFT_XML     2    // SAC 10/26/11
#define  BEMFT_HPXML1  3    // SAC 12/2/15
#define  BEMFT_HPXML2  4    // SAC 12/2/15
#define  BEMFT_CF1RXML 5    // SAC 3/6/18
#define  BEMFT_RNXML   6    // SAC 5/20/20 - RESNET ResXSD
#define BEMPX_IsHPXML(     iFileType )  (int)  (iFileType == BEMFT_HPXML1 || iFileType == BEMFT_HPXML2)
#define BEMPX_IsCF1RXML(   iFileType )  (int)  (iFileType == BEMFT_CF1RXML)
#define BEMPX_IsRESNETXML( iFileType )  (int)  (iFileType == BEMFT_RNXML)
#define BEMPX_IsXML(       iFileType )  (int)  (iFileType == BEMFT_HPXML1 || iFileType == BEMFT_HPXML2 || iFileType == BEMFT_CF1RXML || iFileType == BEMFT_RNXML || iFileType == BEMFT_XML)
#define  BEMF_ClassIDMult  1000    // SAC 12/14/18
bool BEMPROC_API __cdecl BEMPX_WriteProjectFile( const char* fileName, int iFileMode /*bool bIsInputMode*/, bool bUseLogFileName=false, bool bWriteAllProperties=false,
                                                          BOOL bSupressAllMessageBoxes=FALSE,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
																			 int iFileType = 0,    // SAC 8/30/11 - added iFileType argument
																			 bool bAppend = false, const char* pszModelName = NULL, bool bWriteTerminator = true,	// SAC 2/19/13 - added 3 args
																			 int iBEMProcIdx=-1, long lModDate=-1, bool bOnlyValidInputs=false,  // SAC 3/18/13  // SAC 6/26/13  // SAC 4/16/14
																			 bool bAllowCreateDateReset=true,		// SAC 1/12/15 - added bAllowCreateDateReset to prevent resetting this flag when storing detailed version of input file
																			 int iPropertyCommentOption=0, 			// SAC 12/5/16 - added to enable files to include comments: 0-none / 1-units & long name / 
																			 std::vector<long>* plaClsObjIndices=NULL,		// SAC 12/14/18 - added to facilitate writing of specific object type/index elements to CSE input files (initially for HPWH sizing runs - HPWHSIZE)
																			 bool bReportInvalidEnums=true );		// SAC 5/20/19 - prevent logging errors associated w/ invalid enums (for writing of .ribd##i inputs during analysis)

BEMObject*       __cdecl BEMPX_ReadProjectComponent(  const char* fileName, int i1BEMClass, int iBEMProcIdx=-1 );
bool BEMPROC_API __cdecl BEMPX_WriteProjectComponent( const char* fileName, BEMObject *pObj, int iBEMProcIdx=-1, bool bWriteAllProperties=false,
																			bool bWritePrimaryDefaultData=false );

////////////////////////////////////////////////////////////////////////////////
// Access to CBEMClasses
int BEMPROC_API __cdecl BEMPX_GetNumClasses();
BEMClass* __cdecl BEMPX_GetClass( int i1ClassIdx, int& iError, int iBEMProcIdx=-1 );
int BEMPROC_API __cdecl BEMPX_GetClassIndexByLongName(LPCSTR lpszName);

// Access to BEMObjects
bool BEMPROC_API __cdecl BEMPX_CanCreateAnotherUserObject(  int i1Class, int iNumObjs=1, int iBEMProcIdx=-1 );
bool BEMPROC_API __cdecl BEMPX_CanCreateAnotherChildObject( int i1Class, BEMObject* pParObj, int iNumChildren=1, int iBEMProcIdx=-1 );
void BEMPROC_API __cdecl BEMPX_SetActiveObjectIndex(			int i1Class, int i0ObjIdx, BEM_ObjType objType=BEMO_User, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetActiveObjectIndex( int i1Class, int iBEMProcIdx=-1 );  // SAC 4/12/18
long BEMPROC_API __cdecl BEMPX_GetClassMaxDefinable( int i1Class, int iBEMProcIdx=-1 );  // SAC 7/10/12
		// fourth argument to enable naming index to begin with something other than the current component index
		// final three arguments to facilitate default naming to ensure BOTH name uniqueness for new component AND subordinate components
int  BEMPROC_API __cdecl BEMPX_GetDefaultComponentName(		int i1Class, QString& sDefName, int iBEMProcIdx=-1, int iFirstIndex=-1,
																				const char* pszCompPfx1=NULL, const char* pszCompPfx2=NULL, const char* pszCompPfx3=NULL );
		// last argument (bSkipCheckingRuleLib) to implement new unique name checking which allows user/rulelib dup names
		// bNameIsPrefix argument to enable checking for components for which the lpszName is only the beginning of a component name
BEMObject* __cdecl BEMPX_GetComponentByName( LPCSTR lpszName, BOOL bCheckLibsOnly=FALSE, int iBEMProcIdx=-1,
															BOOL bSkipCheckingRuleLib=FALSE, BOOL bNameIsPrefix=FALSE );
BEMObject* __cdecl BEMPX_GetComponentByNameQ( QString& sName, BOOL bCheckLibsOnly=FALSE, int iBEMProcIdx=-1,
                                               BOOL bSkipCheckingRuleLib=FALSE, BOOL bNameIsPrefix=FALSE );
bool BEMPROC_API __cdecl BEMPX_SetObjectCopyName(	QString& sCopyName, LPCSTR lpszOriginalName,
																	BOOL bCheckFirst=TRUE, int iBEMProcIdx=-1 );

		// to ensure valid object names prior to performing analysis
int  BEMPROC_API __cdecl BEMPX_CheckObjectNames( char* pcNotAllowedInObjNames, QString& sNameViolationMsg, int iBEMProcIdx=-1,
																BOOL bAllowTrailingSpaces=TRUE, BOOL bPerformRenames=TRUE, BOOL bLogRenames=TRUE );
int  BEMPROC_API __cdecl BEMPX_GetNumObjects(   int i1BEMClass, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
BEMObject*       __cdecl BEMPX_GetObjectByClass( int i1BEMClass, int& iError, int iObjIdx=-1,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
																// bNameIsPrefix argument to enable checking for components for which the lpszName is only the beginning of a component name
BEMObject*       __cdecl BEMPX_GetObjectByName( int i1BEMClass, int& iError, const char* pObjName,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
																BOOL bNameIsPrefix=FALSE );
BEMObject*       __cdecl BEMPX_GetObjectByNameQ( int i1BEMClass, int& iError, QString& qsObjName,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
																BOOL bNameIsPrefix=FALSE );
BEMObject*       __cdecl BEMPX_GetParentObjectByName( int i1ChildClass, int& iError, const char* pObjName,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
BEMObject*       __cdecl BEMPX_GetParentObjectByNameQ( int i1ChildClass, int& iError, QString& qsObjName,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetObjectIndex(  BEMClass* pClass, BEMObject* pObject=NULL, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetChildObjectIndex( int i1BEMClass, int i1ChildClass, int& iError,
                                                              BEM_ObjType& eChildObjType, int i1ChildIdx=1, int iObjIdx=-1,
                                                              BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );

BEM_ObjType BEMPROC_API __cdecl BEMPX_GetCurrentObjectType( int i1BEMClass, int iObjIdx=-1, int iBEMProcIdx=-1 );

BEMObject*       __cdecl BEMPX_CreateObject( int i1Class, LPCSTR lpszName = NULL, BEMObject* pParent = NULL,
																BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE,
																bool bAutoCreate = TRUE, int iBEMProcIdx=-1, BOOL bIgnoreMaxDefinable=FALSE,
																int i0ChildIdx =-1 );  // SAC 5/29/14 - added i0ChildIdx in place of BOOL bMakeFirstChild = FALSE );
      // BEMPX_CopyComponent does not touch parent/child stuff, only local properties
bool BEMPROC_API __cdecl BEMPX_CopyComponent( BEMObject* pDestObj, BEMObject* pSrcObj, int iBEMProcIdx=-1,
																bool bCopyPrimaryDefaultDataAsUserDefined=false );		// SAC 6/8/15 - CBECC issue 1061

//		0 - ImportOnlyIfUnique - only import object if no user object contains the same data as that which describes the library item
//		1 - ImportAlways - always import library object, regardless of whether duplicate objects already exist in the user model
//		2 - EnsureLibraryName - import lib object if no equiovalent object found in user model BY THE SAME NAME as the library object
BEMObject* __cdecl BEMPX_CopyComponentWithAssignments( BEMObject* pObj, BEMObject* pParentObj, BOOL bLibToUser, int iImportUniqueRuleLibObjOption,
																const char* pszImportRuleLibParentName, int iBEMProcIdx=-1 );  // SAC 10/14/15

BEMObject* __cdecl BEMPX_ImportLibraryObjectToUserModel( BEMObject* pLibObj, BOOL bImportUniqueRuleLibObjects=FALSE,
																			const char* pszImportRuleLibParentName=NULL, int iBEMProcIdx=-1 );

		// routine to create a PolyLp based on various 2D geometry inputs		// SAC 1/7/15 - added pdFurthestFromXYOrig for window shade processing	// SAC 1/10/15 - child Hgt/X/Y also for window shades
int  BEMPROC_API __cdecl BEMPX_CreatePolyLoop( double dArea, double dAzimuth, double dTilt, double dZ, int iPolyType=0,
														double dArg6=-1, double dArg7=-1, int iBEMProcIdx=-1, double* pdFurthestFromXYOrig=NULL,
														double dDX=0, double dDY=0, double dDZ=0, double dChldHgt=-1, double dChldX=-1, double dChldY=-1,
														double dCentX=-999, double dCentY=-999, double dCentZ=-999 );	// SAC 3/1/17 - added centroid args

void BEMPROC_API __cdecl BEMPX_DeleteAllObjects( int iOnlyTypeToDelete=-1, BOOL bReInitSymbols=TRUE );
void BEMPROC_API __cdecl BEMPX_DeleteObject( BEMObject* pObj, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_CountOrResetObjectRefs(	BEMObject* pObj, bool bCountRefs, BEMObject* pReplaceObj=NULL,
																			std::vector<BEMObject*>* pObjArray=NULL, int iBEMProcIdx=-1 );

int  BEMPROC_API __cdecl BEMPX_CountObjectAssignments( bool bCheckMaxRefs, int i1BEMClass, int iObjIdx=-1,
                                                              BEM_ObjType eObjType=BEMO_User, bool bStopAfterFirst=TRUE,
                                                              bool bCheckUserRefLibObjs=FALSE, bool bTreeCtrlCall=TRUE,
                                                              bool bCopyDupRefs=FALSE, int iBEMProcIdx=-1 );
bool BEMPROC_API __cdecl BEMPX_CanAssignObject( int i1BEMClass, int& iError, int iObjIdx=-1, int iBEMProcIdx=-1 );
BOOL BEMPROC_API __cdecl BEMPX_PurgeUnreferencedComponents( int iBEMProcIdx=-1, int* piNumObjectsDeleted=NULL ); 

double BEMPROC_API __cdecl BEMPX_SumChildren(    long lChildDBID, long lParDBID, int iParOccur,
                                                        BEM_ObjType eParObjType=BEMO_User );
double BEMPROC_API __cdecl BEMPX_SumAll(         long lDBID );
double BEMPROC_API __cdecl BEMPX_GetNumChildren( long lParDBID, int iParOccur, BEM_ObjType eParObjType,
                                                        int i1ChildClass=0, int iBEMProcIdx=-1 );

// Access to CBEMPropertyTypes
int  BEMPROC_API __cdecl BEMPX_GetNumPropertyTypes(             int i1Class=0 );
int  BEMPROC_API __cdecl BEMPX_GetNumPropertyTypeElements(      int i1Class, int i1PropIdx, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetNumPropertyTypeElementsFromDBID( long lDBID, int iBEMProcIdx=-1 );
BEMPropertyType* __cdecl BEMPX_GetPropertyType(                 int i1Class, int i1PropIdx, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetPropertyTypeIndexByShortName( int i1Class, LPCSTR lpszName, int iBEMProcIdx=-1 );
//int BEMPROC_API __cdecl BEMPX_GetPropertyTypeIndexByLongName(  int i1Class, LPCSTR lpszName );
int  BEMPROC_API __cdecl BEMPX_GetPropertyTypeIndexByName(      int i1Class, LPCSTR lpszName, int iBEMProcIdx=-1 );
BEMPropertyType*                      __cdecl BEMPX_GetPropertyTypeFromDBID(         long lDBID, int& iError, int iBEMProcIdx=-1 );
bool BEMPROC_API __cdecl BEMPX_InsertPropertyType( QString& sErrMsg, int iObjTypeID, int iPropID, const char* sPropNameShort,
																long lDBID, int iPropType, int iPropTypeObjID=-1, const char* sPropNameLong=NULL,
																const char* sUnits=NULL, int iBEMProcIdx=-1, BOOL bDefinedByRuleset=FALSE, int iReportPrecision=-9 );   // SAC 7/7/12  SAC 1/30/13  SAC 8/6/14	SAC 1/11/15  SAC 2/4/15
void BEMPROC_API __cdecl BEMPX_SetPropertyTypeDetails( long lDBID, int eCompDT, bool bPrim, bool bEdit,			// was: BEMPX_SetDataTypes()
																		bool bUserDef, bool bDispInp, bool bDispProp, bool bDispBudg,
																		int iNotInputMode, const char* pszNotInputMsg );	// SAC 8/13/15 - added to facilitate ruleset-based data model backward compatible

// piNumRefComps argument counts the number of individual component types that have valid DBIDs associated w/ RefProperty:Property
long BEMPROC_API __cdecl BEMPX_GetDatabaseID(    QString sCompParam, long iCompID=0, BOOL bTreatParentAsObject=FALSE,
																				int* piRefCompID=NULL, int* piNumRefComps=NULL );
long long BEMPROC_API __cdecl BEMPX_GetModelDatabaseID( int i1ModelIdx, const char* psDBCompParam, long iCompID=0,
																BOOL bTreatParentAsObject=FALSE, int* piRefCompID=NULL, int* piNumRefComps=NULL );
int  BEMPROC_API __cdecl BEMPX_GetDBComponentID( const char* psDBComp );
long BEMPROC_API __cdecl BEMPX_GetDBParameterID( const char* psDBParam, long iCompID );
void BEMPROC_API __cdecl BEMPX_DBIDToDBCompParamString( long lDBID, QString& sCompParam, bool bLongNames=false );

bool BEMPROC_API __cdecl BEMPX_AddModel( int iBEMProcIdxToCopy=0, long* plDBIDsToBypass=NULL, bool bSetActiveBEMProcToNew=true );	// SAC 3/13/13 - added multiple model support
bool BEMPROC_API __cdecl BEMPX_SetActiveModel( int i0ActiveBEMProcIdx );		// SAC 3/13/13 - added multiple model support
int  BEMPROC_API __cdecl BEMPX_GetActiveModel();		// SAC 3/14/13
int  BEMPROC_API __cdecl BEMPX_GetModelCount();			// SAC 3/15/13
int  BEMPROC_API __cdecl BEMPX_GetObjectIndexAcrossModels( int i1Class, int iOutModel, BEM_ObjType eObjType, int iInOccur, int iInModel=-1 );		// SAC 3/14/13
bool BEMPROC_API __cdecl BEMPX_DeleteModels( bool bIncludingUserModel=false );
bool BEMPROC_API __cdecl BEMPX_DeleteLastModels( int iNumModelsToDelete=1 );
int  BEMPROC_API __cdecl BEMPX_CopyClassObjectsAcrossModels( int i1Class, int iFromBEMProcIdx, int iToBEMProcIdx );  // SAC 5/11/13


// Access to CBEMProperty
BEMProperty*     __cdecl BEMPX_GetProperty(		long lDBID, int& iError, int iOccur=-1,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );

bool BEMPROC_API __cdecl BEMPX_DefaultProperty(	long lDBID, int& iError, int iOccur=-1,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
																BEMCompNameTypePropArray* pTargetedDebugInfo=NULL );	// SAC 9/25/19 - added pTargetedDebugInfo to enable logging of resets for targeted debug DBIDs

int  BEMPROC_API __cdecl BEMPX_SetDataStatus( long lDBID, int iOccur=-1, BEM_PropertyStatus eStatus=BEMS_UserDefined,
																BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_GetDataStatus( long lDBID, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );	// was: BEMPX_GetBEMDataStatus()
int  BEMPROC_API __cdecl BEMPX_GetDataType( long lDBID );

//void*            __cdecl BEMPX_GetData( long lDBID, int& iDataType, int& iSpecialVal, int& iError, int iOccur=-1,
//                                                   BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
long    BEMPROC_API __cdecl BEMPX_GetInteger( long lDBID, int& iSpecialVal, int& iError,
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
BOOL    BEMPROC_API __cdecl BEMPX_GetInteger( long lDBID, long& lData, long lDefault=0, int iDispDataType=-1,		// for backward compatibility with BEMPX_SetDataInteger
																	int iOccur=-1, int iObjType=BEMO_User, int iBEMProcIdx=-1 );
double  BEMPROC_API __cdecl BEMPX_GetFloat(   long lDBID, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
																	bool bAllowNonFloatDataTypes=false, double dDefault=-1.0 );
BOOL    BEMPROC_API __cdecl BEMPX_GetFloat(      long lDBID, double& fData, double fDefault=0, int iDispDataType=-1,		// for backward compatibility with BEMPX_SetDataFloat
																	int iOccur=-1, int iObjType=BEMO_User, int iBEMProcIdx=-1 );
QString BEMPROC_API __cdecl BEMPX_GetString(  long lDBID, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
                                                   BOOL bAddCommas=TRUE, int iPrecision=0, const char* pszDefault=NULL, long lDBID2=0 );
BOOL    BEMPROC_API __cdecl BEMPX_GetString(  long lDBID, QString& sStr, BOOL bAddCommas=TRUE, int iPrecision=0,		// for backward compatibility with BEMPX_SetDataString
																	int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
																	const char* pszDefault=NULL, long lDBID2=0, int iBEMProcIdx=-1 );
BEMObject*          __cdecl BEMPX_GetObjectPtr(  long lDBID, int& iSpecialVal, int& iError,
																	int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
BOOL    BEMPROC_API __cdecl BEMPX_GetObject(  long lDBID, BEMObject*& pObj, int iDispDataType=-1, int iOccur=-1,		// for backward compatibility with BEMPX_SetDataObject
																	int iObjType=BEMO_User, int iBEMProcIdx=-1 );
int     BEMPROC_API __cdecl BEMPX_GetFloatArray( long lDBID, double* pdData, int iMaxValues, double dDefault=0,
																	int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User, int iBEMProcIdx=-1 );
								// GetBEMData routine to return both data & status
//void*            __cdecl BEMPX_GetDataAndStatus( long lDBID, int& iStatus, int& iDataType, int& iSpecialVal, int& iError, int iOccur=-1,
//                                                   BEM_ObjType eObjType=BEMO_User, BOOL bReturnParentObject=FALSE, int iBEMProcIdx=-1 );
long    BEMPROC_API __cdecl BEMPX_GetIntegerAndStatus( long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
double  BEMPROC_API __cdecl BEMPX_GetFloatAndStatus(   long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
																	bool bAllowNonFloatDataTypes=false, double dDefault=-1.0 );
QString BEMPROC_API __cdecl BEMPX_GetStringAndStatus(  long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
                                                   BOOL bAddCommas=TRUE, int iPrecision=0, const char* pszDefault=NULL, long lDBID2=0 );
BEMObject*          __cdecl BEMPX_GetObjectAndStatus(  long lDBID, int& iStatus, int& iSpecialVal, int& iError, 
                                                   int iOccur=-1, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );

QString BEMPROC_API __cdecl BEMPX_FloatToString( double dNum, int nRtOfDec=0, BOOL bAddCommas=TRUE,
                                                      int iZeroFillLeftToLength=0, BOOL bTrimTrailingDecZeroes=FALSE );
long    BEMPROC_API __cdecl BEMPX_StringToLong(  const char* psLong );
double  BEMPROC_API __cdecl BEMPX_StringToFloat( const char* psFlt );

int  BEMPROC_API __cdecl BEMPX_SetBEMData(   long lDBID, int iDataType, void* pData, BEM_ObjType eObjFrom=BEMO_User,
                                                     int iOccur=-1, BEM_PropertyStatus eStatus=BEMS_UserDefined,
                                                     BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1,
																	  int iImportUniqueRuleLibObjOption=2,  // SAC 3/10/13	// SAC 4/25/14
																	  const char* pszImportRuleLibParentName=NULL,   // SAC 3/17/13 - name of parent of rule lib object to import
																	  char* pszErrMsg=NULL, int iErrMsgLen=0,  // SAC 4/10/13 - error message return
																	  BEMCompNameTypePropArray* pTargetedDebugInfo=NULL );	// SAC 9/25/19 - added pTargetedDebugInfo to enable logging of resets for targeted debug DBIDs

int  BEMPROC_API __cdecl BEMPX_SetBEMSpecialValue( long lDBID, int iSpecialVal, int iOccur=-1,
                                                           BEM_PropertyStatus eStatus=BEMS_UserDefined,
                                                           BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
                                                           BEMCompNameTypePropArray* pTargetedDebugInfo=NULL );	// SAC 9/25/19 - added pTargetedDebugInfo to enable logging of resets for targeted debug DBIDs

// tracking for BEM data mods since last full model defaulting - SAC 4/11/18
void BEMPROC_API     __cdecl BEMPX_InitModsSinceModelDefaulted();
void BEMPROC_API     __cdecl BEMPX_IncrementModsSinceModelDefaulted();
long BEMPROC_API     __cdecl BEMPX_GetNumModsSinceModelDefaulted();

// SAC 12/19/01 - Added to facilitate more intelligent rule parsing by allowing Parent*() functions to be parsed at compile time
int  BEMPROC_API __cdecl BEMPX_GetParentComponentType( int i1Class, int iNumGenerations=1, int iBEMProcIdx=-1 );
// SAC 8/27/12 - added secondary check to see if first property name listed in argument exists for only a SINGLE possible Parent* object type
int  BEMPROC_API __cdecl BEMPX_GetParentComponentTypeForProperty( int i1Class, const char* pszPropName, int iNumGenerations=1, int iBEMProcIdx=-1 );

int  BEMPROC_API __cdecl BEMPX_CheckForDuplicateObjectNames( char* pszErrMsg=NULL, int iErrMsgLen=0, BOOL bWriteErrorsToLog=TRUE, BOOL bSupressAllMessageBoxes=FALSE,
																			BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );

// Symbol & SymbolList data
void BEMPROC_API     __cdecl BEMPX_SymbolToRuleFile( QString& sString );
BEMSymDependencySet* __cdecl BEMPX_GetSymbolListPointer(	int& iNumSymbols, long lDBID, int iOccur=-1, BEM_ObjType eObjType=BEMO_User,
																			int iBEMProcIdx=-1, BOOL* pbSymListArrayDependent=NULL );
QString              __cdecl BEMPX_GetSymbolString(	long iSymVal, long lDBID, int iOccur=-1, BEM_ObjType eObjType=BEMO_User,
																		int iBEMProcIdx=-1, BOOL bOnlyFromCurrentSymDepSet=TRUE );
int  BEMPROC_API     __cdecl BEMPX_GetSymbolData( long& iSymValue, QString& sSymString, BEMSymDependencySet* pSymDepSet, int iSymIdx=0 );

// enable rule processor to override BEMProc symbol definitions based on the contents of the compliance ruleset being loaded
void*            __cdecl BEMPX_OverwriteSymbolList( long lDBID, int iSource=BEMS_ProgDefault );
void*            __cdecl BEMPX_AddSymbolDepList( void* pvBEMSymList, long iDefaultVal, long lDBID1, double fDepVal1,
																 long lDBID2, double fDepVal2, long lDBID3=0, double fDepVal3=0 );
BOOL BEMPROC_API __cdecl BEMPX_AddSymbol( void* pvBEMSymDepList, long iSymVal, const char* pszSymString );

// SAC 11/27/98 - Added to allow ruleset to default a symbolic value of the current value does not exist for the symbol list
// SAC 8/11/06 - added bReturnDefaultSymVal argument to enable return of (0/1) indicating whether or not existing symbol value maps to a valid symbol string
long BEMPROC_API __cdecl BEMPX_GetDefaultSymbolIfInvalid( long lDBID, int iOccur, BEM_ObjType eObjType, BOOL bReturnDefaultSymVal = TRUE, int iBEMProcIdx=-1 );

// BEMProc Error setting and getting functions
class BEMError;
#define  BEM_UserInpChk_DisallowNotInput    1	// SAC 5/1/14 - added #defs to specify checks of data classified as user input but that shouldn't be
#define  BEM_UserInpChk_DisallowPrescribed  2
BOOL BEMPROC_API __cdecl BEMPX_PerformErrorCheck( BOOL bRequireRequiredData=TRUE, BOOL bReportSimDefaultErrors=TRUE, BOOL bPerformReqdClassCheck=TRUE,
															BOOL bPostRangeWarnings=FALSE, int iUserInpChk=0, BOOL bPerformRangeChecks=TRUE );   // SAC 11/18/04   // SAC 5/1/14
#define  BEM_UserInpFix_NotInput    1	// SAC 5/5/14 - added #defs to specify which user input corrections to make
int  BEMPROC_API __cdecl BEMPX_BlastInvalidUserInputs( int iUserInpFix /*=BEM_UserInpFix_NotInput*/ );
void BEMPROC_API __cdecl BEMPX_ResetErrorListing();
BOOL BEMPROC_API __cdecl BEMPX_LogError( const char* sMessage, int iSeverity, int iErrorCode, int iModule,
                                                 long lDBID=0, BEM_ObjType eObjectType=BEMO_User, int i0ObjectIdx=0,
                                                 BOOL bWriteToProjectLog=TRUE );
int BEMPROC_API __cdecl BEMPX_GetNumErrors();
const BEMError* __cdecl BEMPX_GetErrorPtr( int idx );

QString         __cdecl BEMPX_GetBEMUnitsLabel( long lDBID );

// RangeCheck function(s)
int  BEMPROC_API __cdecl BEMPX_PerformRangeCheck( long lDBID, double dValue, BOOL bSilent=FALSE, QString* psMsg=NULL, int iOccur=-1 );
int  BEMPROC_API __cdecl BEMPX_GenerateRangeMessage( long lDBID, QString* psMsg, int iOccur = -1, BOOL bIncludeUnits = TRUE );

// get PropertyType info
int  BEMPROC_API __cdecl BEMPX_GetCompDataType(          long lDBID );
bool BEMPROC_API __cdecl BEMPX_GetCompIsEditable(        long lDBID );
bool BEMPROC_API __cdecl BEMPX_GetCompDisplay(           long lDBID, int iDispMode );
int  BEMPROC_API __cdecl BEMPX_GetNumberOfPrimaryProperties( int i1BEMClass );
long BEMPROC_API __cdecl BEMPX_GetPrimaryPropertyDBID(       int i1BEMClass, int iPrimPropIdx );

////////////////////////////////////////////////////////////////
// Key to arguments of BEMMessageBox():
//		nIcon options include:
//				0 - no icon (default)
//				1 - Information icon
//				2 - Warning icon
//				3 - Error icon
//				4 - Question icon
//		nType = sum of values below for each button desired:
//			    1,024 - OK	    (0x00000400) (the default)
//			4,194,304 - Cancel (0x00400000)
//			   16,384 - Yes    (0x00004000)
//			   65,536 - No     (0x00010000)
//			  262,144 - Abort  (0x00040000)
//			  524,288 - Retry  (0x00080000)
//			1,048,576 - Ignore (0x00100000)
//			- for other options search:  QMessageBox::StandardButtons
//		nDefault = single value corresponding to the default button (from above list)
//		details - added - SAC 6/30/20
int  BEMPROC_API __cdecl BEMMessageBox(const TCHAR* msg, const TCHAR* caption = NULL, UINT nIcon = 0, UINT nType = 1024,
														UINT nDefault = 0, const TCHAR* details = NULL);
int  BEMPROC_API __cdecl BEMMessageBox( QString msg, QString caption = "", UINT nIcon = 0, UINT nType = 1024,
														UINT nDefault = 0, QString details = "" );

// Function(s) to evaluate conditions (for screen control toggling and range checking)
BOOL BEMPROC_API __cdecl BEMPX_FloatConditionTrue( double fLtValue, int iCondition, double fRtValue, long lRtDBID=0,
																	int iOccur=-1, long lChkDBID=0, double dChkValue=0 ); 
BOOL BEMPROC_API __cdecl BEMPX_ConditionTrue( long lCondDBID, int iCondition, double fRtValue, long lRtDBID=0,
                                              int iOccur=-1, long lCondDBID2=0, long lChkDBID=0, double dChkValue=0 );

// SAC 5/15/12 - added new export to facilitate reading/parsing of CSE hourly results
void BEMPROC_API __cdecl BEMPX_InitializeHourlyResults( int iBEMProcIdx=-1 );
BOOL BEMPROC_API __cdecl BEMPX_SetupResultRun( int iRunIdx, const char* pszRunName, const char* pszRunAbbrev, int iBEMProcIdx=-1 );
int  BEMPROC_API __cdecl BEMPX_RetrieveCSEHourlyResults( const char* pszFilename, const char* pResMeter, const char** ppResEnduses, 
																double* pdHourlyResults, double* pdResultMult=NULL );		// SAC 5/3/20
int  BEMPROC_API __cdecl BEMPX_ReadCSEHourlyResults( const char* pszFilename, int iRunIdx, const char* pszRunName, const char* pszRunAbbrev, int iBEMProcIdx=-1,
																const char** ppResMeters=NULL, const char** ppMetersMap=NULL, double* pdMetersMult=NULL,  // SAC 6/1/16
																const char** ppResEnduses=NULL, const char** ppEnduseMap=NULL, bool bInitResults=true );	// SAC 5/31/16  // SAC 7/23/18
double BEMPROC_API __cdecl BEMPX_GetHourlyResultSum( char* pszErrMsgBuffer, int iErrMsgBufferLen, const char* pszRunName, const char* pszMeterName,
																					const char* pszEnduse1,      const char* pszEnduse2=NULL, const char* pszEnduse3=NULL,
																					const char* pszEnduse4=NULL, const char* pszEnduse5=NULL, const char* pszEnduse6=NULL,
																					const char* pszEnduse7=NULL, const char* pszEnduse8=NULL, int iBEMProcIdx=-1 );
double BEMPROC_API __cdecl BEMPX_GetHourlyResultArray( char* pszErrMsgBuffer, int iErrMsgBufferLen, double* pDbl, const char* pszRunName,
																					  const char* pszMeterName,    const char* pszEnduse1,      const char* pszEnduse2=NULL,
																					  const char* pszEnduse3=NULL, const char* pszEnduse4=NULL, const char* pszEnduse5=NULL,
																					  const char* pszEnduse6=NULL, const char* pszEnduse7=NULL, const char* pszEnduse8=NULL, int iBEMProcIdx=-1 );
int    BEMPROC_API __cdecl BEMPX_GetHourlyResultArrayPtr( double** ppDbl, char* pszErrMsgBuffer, int iErrMsgBufferLen, const char* pszRunName,
																						  const char* pszMeterName, const char* pszEnduse, int iBEMProcIdx=-1 );
double BEMPROC_API __cdecl BEMPX_AddHourlyResultArray( double* pDbl, const char* pszRunName, const char* pszMeterName, const char* pszEnduse, int iBEMProcIdx=-1, BOOL bAddIfNotExist=FALSE );
double BEMPROC_API __cdecl BEMPX_SumIntoHourlyResultArray( double* pDbl, const char* pszRunName, const char* pszMeterName, const char* pszEnduse, int iBEMProcIdx=-1, BOOL bAddIfNotExist=FALSE );
int    BEMPROC_API __cdecl BEMPX_WriteHourlyResultsSummary( const char* pszHourlyResultsPathFile, bool bSilent, int iBEMProcIdx );  // SAC 8/5/13

// SAC 5/7/13 - routine to retrieve 0-based index of transform based on short name
int    BEMPROC_API __cdecl BEMPX_GetTransformIndex( LPCSTR sShortTransformName );		// was: RuleProcGetTransformIndex()
// SAC 3/15/13 - added routines to load information about a model transformation to be made and to evalaute rules for a given transform
int    BEMPROC_API __cdecl BEMPX_GetTransformInitializationInfo(	LPCSTR sShortTransformName, int* pi1BEMProcIdxToCopy,		// was: RuleProcGetTransformInitializationInfo()
																						long* plDBIDsToBypassCopy, int iMaxBypassClasses );
int    BEMPROC_API __cdecl BEMPX_EvaluateTransform(	LPCSTR sShortTransformName, BOOL bVerboseOutput=FALSE, void* pvTargetedDebugInfo=NULL,		// was: RuleProcEvaluateTransform()
																		long* plNumRuleEvals=NULL, double* pdNumSeconds=NULL );

bool   BEMPROC_API __cdecl BEMPX_WriteFileFromRulelist( LPCSTR sFileName, LPCSTR sRulelistName, bool bVerbose=false );	// was: RuleProcWriteFileFromRulelist()

// SAC 10/24/13 - added to facilitate analysis & rule evaluation duration tracking/logging
void   BEMPROC_API __cdecl BEMPX_SetDurationMark( int i1MarkIdx );													// was: RuleProcSetDurationMark()
double BEMPROC_API __cdecl BEMPX_GetDurationSinceMark( int i1SinceMarkIdx, bool bResetMark=false );		// was: RuleProcGetDurationSinceMark()

// SAC 5/27/00 - added to retrieve the names of each rulelist in the ruleset
int    BEMPROC_API __cdecl BEMPX_GetRulelistNames( QVector<QString>& sRulelistNames );		// was: RuleProcGetRulelistNames()
bool   BEMPROC_API __cdecl BEMPX_RulelistExists( LPCSTR listName );		// SAC 2/27/17
void   BEMPROC_API __cdecl BEMPX_DeleteTrailingRuleLists( int iNumListsToDelete=1 );	// SAC 1/29/18

/* called to evaluate rule lists */
bool   BEMPROC_API __cdecl BEMPX_EvaluateRuleList( LPCSTR listName, BOOL bTagDataAsUserDefined=FALSE, int iEvalOnlyClass=0,		// was: RuleProcEvalList()
														int iEvalOnlyObjIdx=-1, int iEvalOnlyObjType=0, BOOL bVerboseOutput=FALSE,
														void* pvTargetedDebugInfo=NULL, long* plNumRuleEvals=NULL, double* pdNumSeconds=NULL, 
														PLogMsgCallbackFunc pLogMsgCallbackFunc=NULL,
														QStringList* psaWarningMsgs=NULL );		// SAC 3/2/18 - added to enable Warning message tracking during normal list evaluation

// SAC 5/21/01 - Added function similar to RuleProcEvalList(), only the rules therein are designed to populate the error and warning message lists
bool   BEMPROC_API __cdecl BEMPX_EvalErrorCheckList( LPCSTR listName, QStringList& saErrorMsgs, QStringList& saWarningMsgs,		// was: RuleProcEvalErrorCheckList()
                                                               int iEvalOnlyClass=0, int iEvalOnlyOccur=-1 );

// SAC 8/6/13 - get/set flags indiciating that rule processing was/should be aborted
bool   BEMPROC_API __cdecl BEMPX_AbortRuleEvaluation();											// was: RuleProcAbortRuleEvaluation();
void   BEMPROC_API __cdecl BEMPX_SetAbortRuleEvaluationFlag( bool bAbortRuleEval );		// was: RuleProcSetAbortRuleEvaluationFlag( bool bAbortRuleEval );

bool   BEMPROC_API __cdecl BEMPX_InitGeometryIDs( QString& sErrMsg );		// was: RuleProcInitializeGeometryIDs()

double BEMPROC_API __cdecl BEMPX_GetRulesetSimulateFlagValue( double fDefault=1 );

int    BEMPROC_API __cdecl BEMPX_GetTableColumn( double* pData, int iNumRecords, const char* pszTableName, int i1TableCol,
																	char* pszErrMsgBuffer, int iErrMsgBufferLen );
double BEMPROC_API __cdecl BEMPX_RuleTableLookupFloat( const char* pszTableAndColumnName, std::vector<std::string>& saIndepNames,			// was: RuleProcTableLookup_Float()
														std::vector<std::string>& saIndepStrings, std::vector<double>& faIndepValues,
														std::vector<bool>& baIndepNumeric, std::string& sErrMsg, BOOL bVerboseOutput=FALSE );

double BEMPROC_API __cdecl BEMPX_ApplyHourlyMultipliersFromTable( double* dHrlyVals, LPCSTR sTableName,	// was: RuleProcApplyHourlyMultipliersFromTable()
														int iTableColumn, bool bVerbose=false );

int    BEMPROC_API __cdecl BEMPX_ParseRuleListFile( const char* sRuleListFileName, QStringList& saRuleListNames,
														const char* sLogFileName=NULL, QString* psRuleCompileMsg=NULL, bool bParseRules=false );

// Functions to retrieve Help IDs
UINT   BEMPROC_API __cdecl BEMPX_GetItemHelpID(  long lDBID );
UINT   BEMPROC_API __cdecl BEMPX_GetTopicHelpID( long lDBID );

int    BEMPROC_API __cdecl BEMPX_ExportSVG( const char* pszSVGFileName, int iBEMClass, int iObjIdx=-1, int iWhatToPlot=1,  // SAC 11/27/13
															int iDayltMethod=1 );  // SAC 7/29/18

/////////////////////////////////////////////////////////////////////////////
// AnalysisAction

#define  BEMAnalActPhase_LoadModel            1
#define  BEMAnalActPhase_ProposedSizing      11
#define  BEMAnalActPhase_ProposedAnnual      12
#define  BEMAnalActPhase_BaselineSizing      13
#define  BEMAnalActPhase_BaselineAnnual      14
#define  BEMAnalActPhase_End                  2

#define  BEMAnalActWhen_LoadModel_BeforeDefaulting         1
#define  BEMAnalActWhen_LoadModel_AfterDefaulting          2
#define  BEMAnalActWhen_End_BeforeAnalPostProc            11
#define  BEMAnalActWhen_End_AfterAnalPostProc             12
#define  BEMAnalActWhen_Transform_BeforeModelSetupRules   21
#define  BEMAnalActWhen_Transform_AfterModelSetupRules    22
#define  BEMAnalActWhen_Transform_FollowingResultsProc    23
#define  BEMAnalActWhen_Transform_ActOnEPlusSimInput      31	// SAC 3/10/20
#define  BEMAnalActWhen_Transform_ActOnCSESimInput        32

int  BEMPROC_API __cdecl BEMPX_PostAnalysisActionRulesetPropertiesToDatabase();		// SAC 1/26/20
int  BEMPROC_API __cdecl BEMPX_ApplyAnalysisActionToDatabase( long iAnalPhase, long iBeforeAfter,
																					QString& sErrorMsg, bool bVerbose=false, 		// SAC 1/30/20
																					const char* pszSimPathFileName=NULL );			// SAC 3/10/20

/////////////////////////////////////////////////////////////////////////////
//	BEMError
//    An instance of this class is created for each error logged to the BEMProc.

#define  ERR_MODULE_BEMPROC      0
#define  ERR_MODULE_SIMULATION  1
#define  ERR_MODULE_RULESET     2

#define  ERR_SEVERITY_ERROR     1
#define  ERR_SEVERITY_WARNING   2
#define  ERR_SEVERITY_MESSAGE   3

#define  ERR_CODE_NOCOMPS       0
#define  ERR_CODE_REQDATA       1
#define  ERR_CODE_NOPARENT      2
#define  ERR_CODE_MAXCHILD      3
#define  ERR_CODE_GETOBJECT     4
#define  ERR_CODE_DTNOTFOUND    5
#define  ERR_CODE_RANGECHECK    6

class BEMPROC_API BEMError
{
public:
   BEMError()		{ }
   BEMError( int iMod, long lDBID, BEM_ObjType eOTyp, 
   			 int iOIdx, int iSev, int iCode,
   			 QString sMsg )
						{	m_iModule     = iMod;
							m_lDBID       = lDBID;
							m_eObjectType = eOTyp;
							m_i0ObjectIdx = iOIdx;
							m_iSeverity   = iSev;
							m_iErrorCode  = iCode;
							m_sMessage    = sMsg;	}
   ~BEMError()		{ }

   int       m_iModule;      // module error occurred in (ERR_MODULE_*)
   long        m_lDBID;        // DBID of errant parameter
   BEM_ObjType  m_eObjectType;  // type of object which error occurred in
   int       m_i0ObjectIdx;  // 0-based index of object which error occurred in
   int       m_iSeverity;    // severity of error (ERR_SEVERITY_*)
   int       m_iErrorCode;   // error code (ERR_CODE_*)
   QString   m_sMessage;     // error message
};


/////////////////////////////////////////////////////////////////////////////

class  QFile;
class  QXmlStreamWriter;

// BEMXMLWriter
class BEMPROC_API BEMXMLWriter
{
public:
   BEMXMLWriter( const char* pszFileName=NULL, int iBEMProcIdx=-1, int iFileType=-1 );
   ~BEMXMLWriter();

public:
	QFile					*mp_file;
	QXmlStreamWriter	*mp_stream;

public:
	bool WriteModel(	bool bWriteAllProperties, BOOL bSupressAllMessageBoxes, const char* pszModelName, int iBEMProcIdx=-1, bool bOnlyValidInputs=false,
							int iNumClassIDsToIgnore=0, int* piClassIDsToIgnore=NULL, bool bWritePropertiesDefinedByRuleset=true, bool bUseReportPrecisionSettings=false,
							int iFileType=BEMFT_XML );
	bool WriteCF1RPRF01E(	int iBEMClassID, bool bWriteAllProperties, BOOL bSupressAllMessageBoxes, int iBEMProcIdx=-1, bool bOnlyValidInputs=false,
									bool bWritePropertiesDefinedByRuleset=true, bool bUseReportPrecisionSettings=false, int iFileType=BEMFT_XML );
	void Close();
};

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMPROC_H__
