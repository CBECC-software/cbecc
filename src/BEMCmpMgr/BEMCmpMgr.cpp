// BEMCmpMgr.cpp : Defines the initialization routines for the DLL.
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

#include "stdafx.h"

#include <direct.h>  			// Directory related system routines
#include <stdio.h>
#include <io.h>

// TO DO  #include <openssl/crypto.h>	// SAC 10/16/13

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "CSERunMgr.h"
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include "memLkRpt.h"


/////////////////////////////////////////////////////////////////////////////

void CMX_ExitBEMProcAndCmpMgrDLLs()
{	// Clear out building database & ruleset
	BEMPX_CloseBEMProc();
	CMX_ExitBEMCmpMgrDLL();
}

void CMX_ExitBEMCmpMgrDLL()
{
#ifdef CM_QTGUI		// SAC 11/11/15 - blast QtApp originally initialized during DLL init
	if (sbQtAppDuringInit && sq_app)
	{	delete sq_app;
		sq_app = NULL;
		sbQtAppDuringInit = false;
	}
#endif
//	FreeCSEDLLIfLoaded();
}


/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
bool CMX_GetUIActiveFlag()
{	return BEMPX_GetUIActiveFlag();
}

void CMX_SetUIActiveFlag( bool bActiveUI )
{	BEMPX_SetUIActiveFlag( bActiveUI );
	return;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  CMX_LoadRuleset()
//
// Purpose ------------------------------------------------------------------
//   Call a rule processor function which clears out the ruleset definition
//   which is currently in memory and imports the one identified by the
//   filename argument.
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR fileName  : the path and filename of the binary encrypted ruleset
//                      file to import
//   
// Return Value -------------------------------------------------------------
//   The return value of the rule processor function called to perform this action.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_LoadRuleset( LPCSTR fileName, BOOL bDeleteAllObjects )
{	return BEMPX_LoadRuleset( fileName, bDeleteAllObjects );		// was: RuleProcRead( fileName, bDeleteAllObjects );
}

BOOL CMX_GetRulesetBEMBaseFile( LPCSTR fileName, QString& sBEMBaseFN )	// SAC 8/15/14 - added to facilitate dynamic ruleset switching (w/ BEMBase refresh)
{	return BEMPX_ReadBEMBaseFile( fileName, sBEMBaseFN );		// was: RuleProcReadBEMBaseFile( fileName, sBEMBaseFN );
}

/////////////////////////////////////////////////////////////////////////////
// CMX_GetRulesetID()
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_GetRulesetID( QString& sRuleSetID, QString& sRuleSetVer )
{	return BEMPX_GetRulesetID(sRuleSetID, sRuleSetVer );
}

/////////////////////////////////////////////////////////////////////////////
// CMX_ReadRulesetID()
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_ReadRulesetID( LPCSTR fileName, QString& sRuleSetID, QString& sRuleSetVer )
{	return BEMPX_ReadRulesetID( fileName, sRuleSetID, sRuleSetVer );		// was: RuleProcReadRulesetID( fileName, sRuleSetID, sRuleSetVer );
}

/////////////////////////////////////////////////////////////////////////////
// CMX_GetRulesetScreenFiles()
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_GetRulesetScreenFiles( QString& sScreensFN, QString& sToolTipsFN )
{	return BEMPX_GetScreenFiles( sScreensFN, sToolTipsFN );		// was: RuleProcGetScreenFiles( sScreensFN, sToolTipsFN );
}

/////////////////////////////////////////////////////////////////////////////
// Ruleset Organization exports
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_RulesetOrganizationIsProcedural()
{	return (BEMPX_GetRulesetOrganization() == RULESETORG_PROCEDURAL);
}

BOOL CMX_RulesetOrganizationIsDataModel()
{	return (BEMPX_GetRulesetOrganization() == RULESETORG_DATAMODEL);
}

int CMX_GetRulesetOrganization()
{	return BEMPX_GetRulesetOrganization();
}


/////////////////////////////////////////////////////////////////////////////

int GetBEMBaseCompID( QString& sErr, const char* szComp )
{	int iCompID = BEMPX_GetDBComponentID( szComp );
	if (iCompID <= 0)
	{	if (sErr.length() > 0)
			sErr += ", ";
		sErr += szComp;
	}
	return iCompID;
}

long GetBEMBaseDBID( QString& sErr, const char* szProp, int iCompID )
{	long lDBID = 0;
	if (iCompID > 0)
	{	lDBID = BEMPX_GetDatabaseID( szProp, iCompID );
		if (lDBID <= 0)
		{	if (sErr.length() > 0)
				sErr += ", ";
			sErr += QString( "%1:%2" ).arg( QString::number(iCompID), szProp );
	}	}
	return lDBID;
}


/////////////////////////////////////////////////////////////////////////////
// File Utilities

bool FileExists( QString& sFileName )
{	return (boost::filesystem::exists(sFileName.toLocal8Bit().constData()));
}
bool FileExists( const char* pszFileName )
{	return (boost::filesystem::exists(pszFileName));	//	PathFileExists( (LPCTSTR) pszFileName ) != FALSE);
}


BOOL DirectoryExists( QString sDirName )
{
   int len = sDirName.length();
   if (len > 0)
   {
      if (sDirName[len-1] != '\\' && sDirName[len-1] != '/')
         sDirName += '\\';
      sDirName += '.';

      struct _finddata_t c_file;
      long hFile = _findfirst( sDirName.toLocal8Bit().constData(), &c_file );
      if (hFile != -1)
      {
         _findclose( hFile );
         return TRUE;
      }
   }
   return FALSE;
}


void CreateAndChangeDirectory( const char* pszDirName, BOOL bRemoveDir /*=FALSE*/ )  // SAC 2/12/07 - added argument to facilitate directory deletion
{
   QString mtrDir = pszDirName;
   if(mtrDir.length() != 0)
   {
		char drive[_MAX_DRIVE], dir[_MAX_DIR];
      _splitpath_s( pszDirName, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0 );

		BOOL bDriveOK = (strlen( drive ) < 1);		// SAC 9/2/14 - modified code the ALLOW for drive to be blank (network drive paths)
      if (!bDriveOK)
      {
         int nDrive = drive[0] - ( (drive[0] <= 'Z') ? 'A' : 'a' ) + 1;			assert( nDrive > 0 && nDrive < 27 );
         if (_chdrive( nDrive ) == 0)
				bDriveOK = TRUE;
		}
      if (bDriveOK && strlen( dir ) > 0)
      {
         int nChars = strlen( dir );
         if ( (nChars > 1) && (dir[ nChars-1 ] == '\\' || dir[ nChars-1 ] == '/') )
         {  nChars--;
         	dir[ nChars ] = '\0';
         }

         if (bRemoveDir && DirectoryExists( dir ))   // SAC 2/12/07 - added code to facilitate directory deletion
         {
            if (_rmdir( dir ) != 0)
            {
               QString sMsg = QString( "Error removing directory: %1" ).arg( pszDirName );
               BEMMessageBox( sMsg );
            }
         }
         else if (!bRemoveDir)
         {
            if (!DirectoryExists( dir ))
            {
// SAC 9/8/01 - Note:  the following call is capable of making only ONE new directory (per call)
               if (_mkdir( dir ) != 0)
               {
                  QString sMsg = QString( "Error creating directory: %1" ).arg( pszDirName );
                  BEMMessageBox( sMsg );
               }
            }
            _chdir( dir );
         }
      }
   }
}

BOOL FileWriteable( const char* pszFileName )		// abbreviated form of following routine
{	BOOL bRetVal = FALSE;
	if (FileExists( pszFileName ))
	{
//         DWORD dwFA = GetFileAttributes( pszFileName);
//		 // EAC 3/5/2014 if file is read-only, attempt to clear read-only attribute
//         if (dwFA&FILE_ATTRIBUTE_READONLY)
//            SetFileAttributes( pszFileName, dwFA &= ~FILE_ATTRIBUTE_READONLY);
//
////BEMMessageBox( "About to try opening file...", "" );
//         FILE *pfTempFile = fopen( pszFileName, "r+" );
//         if (pfTempFile != NULL)
//         {
////BEMMessageBox( "File opened OK.", "" );
//            fclose( pfTempFile );
//            bRetVal = TRUE;
//         }

			QFile file(pszFileName);
			if (file.open(QIODevice::WriteOnly | QIODevice::Append))
			{	file.close();
				bRetVal = TRUE;
			}
	}
	return bRetVal;
}

// SAC 3/23/09 - added to handle prompting of user to close file needing to be written
BOOL OKToWriteOrDeleteFile( const char* pszFileName, QString sUserMsg, bool bSilent /*=false*/ )
{
   BOOL bRetVal = (!FileExists( pszFileName ));  // if file doesn't yet exist -> return TRUE
   BOOL bAbort = FALSE;
   while (!bRetVal && !bAbort)
   {
      if (!FileExists( pszFileName ))  // SAC 8/17/06
         bRetVal = TRUE;  // user deleted or renamed file since last check -> return TRUE
      else
      {
//         DWORD dwFA = GetFileAttributes( pszFileName);
//		 // EAC 3/5/2014 if file is read-only, attempt to clear read-only attribute
//         if (dwFA&FILE_ATTRIBUTE_READONLY)
//            SetFileAttributes( pszFileName, dwFA &= ~FILE_ATTRIBUTE_READONLY);
//
////BEMMessageBox( "About to try opening file...", "" );
//         FILE *pfTempFile = fopen( pszFileName, "r+" );
//         if (pfTempFile != NULL)
//         {
////BEMMessageBox( "File opened OK.", "" );
//            fclose( pfTempFile );
//            bRetVal = TRUE;
//         }
			QFile file(pszFileName);
			if (file.open(QIODevice::WriteOnly | QIODevice::Append))
			{	file.close();
				bRetVal = TRUE;
			}

			if (bSilent)
			   bAbort = TRUE;
         else if (!bRetVal)
         {
         //   bAbort = (BEMMessageBox(sUserMsg, "", 3 /*error*/, MB_RETRYCANCEL)  == IDCANCEL);
            bAbort = (BEMMessageBox(sUserMsg, "", 3 /*error*/, (QMessageBox::Retry | QMessageBox::Cancel) )  == QMessageBox::Cancel );
         }
      }
   }

   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

// SAC 5/22/13 - Based on BEMTextIO::ParseCSVRecord()
int ParseCSVRecord( const char* pszParseStr, QVector<QString>* psaCSVFields )
{
	int iRetVal = 0;
	int iParseLen = strlen( pszParseStr );			assert( iParseLen > 0 );
	if (iParseLen > 0 && psaCSVFields)
	{	QString string;
		psaCSVFields->clear();
		int iChrIdx = 0;
   	char chr;
		BOOL bQuoteOpen=FALSE, bQuoteClosed=FALSE;
		while (iChrIdx <= (iParseLen-1))
		{
		   chr = pszParseStr[iChrIdx++];
			if (chr == '\"')
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
					psaCSVFields->push_back( string );
					string.clear();
				}
				else
				{	assert( FALSE );	// quote found after end of quoted field but before following delimiter!!!
				}
			}
   		else if (chr == ',')
			{	if (bQuoteOpen && !bQuoteClosed)
					string = string + chr;		// delimeter included in quoted string...
				else if (bQuoteOpen && bQuoteClosed)
				{	// string already added to arry (@ closing quote), so all we need do here is reset to the quote BOOLs
					bQuoteOpen   = FALSE;
					bQuoteClosed = FALSE;
				}
				else if (!bQuoteOpen && !bQuoteClosed)
				{	// add unquoted string to array
					psaCSVFields->push_back( string );
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
		}

		if (!string.isEmpty())	// add trailing field (numeric, not followed by comma)
			psaCSVFields->push_back( string );

		iRetVal = (psaCSVFields->size() > 0 ? psaCSVFields->size() : 0);
	}
	
	return iRetVal;
}

int GetCSVOptionValue( const char* pszOptName, int iDefault, QVector<QString>& saCSVOptions )
{	int iRetVal = iDefault;
	assert( (saCSVOptions.size() % 2) == 0 );  // should be EVEN # of option strings .... option/value/option/value...
	int i=0;
	bool bFound = false;
	while (!bFound && i < saCSVOptions.size())
	{	if (saCSVOptions[i].compare( pszOptName, Qt::CaseInsensitive ) == 0 && saCSVOptions.size() > i+1)
		{	iRetVal = atoi( saCSVOptions[i+1].toLocal8Bit().constData() );
			bFound = true;
		}
		i += 2;
	}
	return iRetVal;
}

int GetCSVOptionString( const char* pszOptName, QString& sOptString, QVector<QString>& saCSVOptions )
{	int iRetVal = 0;
	assert( (saCSVOptions.size() % 2) == 0 );  // should be EVEN # of option strings .... option/value/option/value...
	int i=0;
	bool bFound = false;
	while (!bFound && i < saCSVOptions.size())
	{	if (saCSVOptions[i].compare( pszOptName, Qt::CaseInsensitive ) == 0 && saCSVOptions.size() > i+1)
		{	iRetVal = i+1;
			sOptString = saCSVOptions[i+1];
			bFound = true;
		}
		i += 2;
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Static Function:  CopySimFile()
//
// Purpose ------------------------------------------------------------------
//   Copies the contents of a simulation output file to a new directory and
//   filename, where the filename is the same as the current projects and the
//   extension indicates exactly which complaince simulation run it is storing.
//   
// Arguments ----------------------------------------------------------------
//   const char* sSrc    : path and filename of the file simulation file TO BE COPIED
//   const char* sTarget : path and filename of the current project (minus extension)
//   const char* sExt    : file extension to be appended onto the target filename
//   int   iNum          : decimal number to be appended onto the end of the target file's extension
//   
// Return Value -------------------------------------------------------------
//   FALSE if the iNum argument is out of range, otherwise the return value of
//   the CopyTextFile() function which is called to perform the file copy action.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BOOL CopySimFile( const char* sSrc, const char* sTarget, const char* sExt, int iNum )
{
   // prevent iNum from being >= 10
   if (iNum < 10 && FileExists( sSrc ))
   {
      QString sFullTarget = sTarget;
      sFullTarget += sExt;
      // only append iNum onto target file extension if it is greater than 0
      if (iNum > 0)
         sFullTarget += QString::number(iNum);

      // report this action to the current project's log file (if flag TRUE)
      QString sMsg = QString("Copying file: %1 -> %2").arg( sSrc, sFullTarget );
      BEMPX_WriteLogFile( sMsg );

      // call the CopyTextFile() function to actually perform the copy
//      return CopyTextFile( sSrc, sFullTarget, TRUE );
      return CopyFile( sSrc, sFullTarget.toLocal8Bit().constData(), FALSE );
   }

   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////

BOOL GetBEMCmpMgrVersion( QString& sProgVer, BOOL bPrependName, BOOL bLongVer )
{
	BOOL bRetVal = FALSE;
	sProgVer.clear();

//	QString sProgPathFile = esProgramPath + esProgramFName;
//	sProgPathFile += ".exe";
	// get the .exe path
   char szFullPath[MAX_PATH+1];
   GetModuleFileName ( NULL, szFullPath, sizeof(szFullPath) );
	QString sProgPathFile = szFullPath;

	DWORD  verHandle = NULL;
	UINT   size	  = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = GetFileVersionInfoSize( sProgPathFile.toLocal8Bit().constData(), &verHandle);
	int major, minor, build;
	if (verSize != NULL)
	{	LPSTR verData = new char[verSize];
		if (GetFileVersionInfo( sProgPathFile.toLocal8Bit().constData(), verHandle, verSize, verData))
		{	if (VerQueryValue(verData,"\\",(VOID FAR* FAR*)&lpBuffer,&size))
			{	if (size)
				{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{	major = HIWORD(verInfo->dwFileVersionMS);
						minor = LOWORD(verInfo->dwFileVersionMS);
						build = verInfo->dwFileVersionLS;
						bRetVal = TRUE;
					}
				}
			}
		}
		delete[] verData;
	}
	if (bRetVal)
	{	QString sVerLetter;
		while (minor > 26)
		{	sVerLetter += 'z';
			minor -= 26;
		}
		sVerLetter += char('a' + minor - 1);

		if (bLongVer)
			sProgVer = QString( "%1%2 (%3)" ).arg( QString::number(major), sVerLetter, QString::number(build) );
		else
			sProgVer = QString( "%1%2" ).arg( QString::number(major), sVerLetter );

		if (bPrependName)
			sProgVer = "BEMCmpMgr " + sProgVer;
	}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////

#ifdef CM_QTGUI
QApplication* sq_app = NULL;
bool sbQtAppDuringInit = false;
#endif

QString ssEXEPath;
void StoreEXEPath()
{  // get the .exe path
//   char szFullPath[MAX_PATH+1];
//   GetModuleFileName( BEMCmpMgrDLL.hModule, szFullPath, sizeof(szFullPath) );	// SAC 3/6/14 - find directory of DLL, not calling application (.exe)
//	ssEXEPath = szFullPath;				assert( ssEXEPath.lastIndexOf('\\') > 0 );
//	if (ssEXEPath.lastIndexOf('\\') > 0)
//		ssEXEPath = ssEXEPath.left( ssEXEPath.lastIndexOf('\\')+1 );
assert( false );
	if (sq_app)
	{	ssEXEPath = sq_app->applicationDirPath();
	}
	else
		ssEXEPath.clear();
}

bool RelativeToCompletePath_IfNeeded( QString& sPathFile )
{	bool bRetVal = true;
	sPathFile.replace( '/', '\\' );		// SAC 9/23/16 - ensure all backslash paths
	if (sPathFile.isEmpty() || sPathFile.indexOf(':') > 0 || sPathFile.indexOf('\\') == 0)		// sPathFile is empty or is a complete path, so DO NOTHING
	{
	}
	else if (ssEXEPath.isEmpty())
	{	assert( FALSE );  // path needs augmenting, but EXE path not loaded
		bRetVal = false;
	}
	else
	{	QString sNewRoot = ssEXEPath;
		while (sPathFile.indexOf("..\\") == 0)
		{	if (sNewRoot.indexOf('\\') == sNewRoot.lastIndexOf('\\'))
			{	assert( FALSE );  // can't backup any further...
				bRetVal = false;
				break;
			}
			else
			{	sPathFile = sPathFile.right( sPathFile.length()-3 );		// remove leading "..\" from path argument
				sNewRoot = sNewRoot.left( sNewRoot.length()-1 );         // trim trailing '\' from EXE path
				sNewRoot = sNewRoot.left( sNewRoot.lastIndexOf('\\')+1 );	// trim right side of EXE path to the new last '\'
			}
		}
		sPathFile = sNewRoot + sPathFile;
	}
	return bRetVal;
}


// Analysis Progress Tracking stuff
const char* pszCSEProgressMsgs[] = { " Input", " Warmup", " Jan", " Feb", " Mar", " Apr", " May", " Jun", " Jul", " Aug", " Sep", " Oct", " Nov", " Dec", " Reports",  NULL  };
float       faCSEProgressVals[]  = {     2,         2,        2,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,        1		};
float       fCSEProgressValSum   =       2 +        2 +       2 +     1 +     1 +     1 +     1 +     1 +     1 +     1 +     1 +     1 +     1 +     1 +       1		 ;

PAnalysisProgressCallbackFunc spAnalProgCallbackFunc = NULL;
long slAnalysisProgressCallbackRetVal = 0;
long slCurrentProgress = 0;


/////////////////////////////////////////////////////////////////////////////
// QT Progress Dialog stuff
int siNumProgressErrors = 0;
int si1ProgressRunNum = 1;
int siNumProgressRuns = 1;
#ifdef CM_QTGUI
QWidget* sqt_win = NULL;
QProgressDialog* sqt_progress = NULL;
#ifdef OSWRAPPER
Qt_URLFile	surlFile;		// SAC 9/18/14
#endif

static QString sqsProgressMsgStart      = "Performing Analysis:                              \n\n                ";
static QString sqsProgressMsgEndNoErr   = "...          \n\n                  ";
static QString sqsProgressMsgEndErrors1 =   "...          \n                     (";
static QString sqsProgressMsgEndErrors2 = " errors encountered)\n                 ";
QString sqProgressRunName;
QString sqProgressMsg;
void SetProgressMessage( QString str, bool bBatchMode )
{	bool bDash = !sqsProgressMsgStart.isEmpty() && !sqProgressRunName.isEmpty();
	QString qsSeparator = bDash ? "-" : "";

	QString qsProgMsgStart;		// SAC 5/28/15 - unique batch processing message
	if (bBatchMode && si1ProgressRunNum > 0 && siNumProgressRuns >= si1ProgressRunNum)
		qsProgMsgStart = QString("Batch Run %1 of %2:                              \n\n                ").arg( QString::number(si1ProgressRunNum), QString::number(siNumProgressRuns) );
	else
		qsProgMsgStart = sqsProgressMsgStart;

	if (siNumProgressErrors < 1)
		sqProgressMsg = QString("%1%2 %3%4%5").arg( qsProgMsgStart, sqProgressRunName, qsSeparator, str, sqsProgressMsgEndNoErr );
	else
		sqProgressMsg = QString("%1%2 %3%4%5%6%7").arg( qsProgMsgStart, sqProgressRunName, qsSeparator, str, sqsProgressMsgEndErrors1, QString::number(siNumProgressErrors), sqsProgressMsgEndErrors2 );
//QString("%1/%2-%3.txt").arg("~", "Tom", QString::number(1));
}
#endif


/////////////////////////////////////////////////////////////////////////////
// CSE DLL interface & callback stuff

// SAC 9/17/16 - DLL interface no longer used
// static HMODULE hmAshwatDLL = NULL;
// static HMODULE hmCSEDLL = NULL;
// typedef int CSEMSGCALLBACK( int level, const char* msg);
// typedef int (__cdecl *PCSEZ)( const char*, const char*, CSEMSGCALLBACK* );
// typedef int (__cdecl *PCSEProgInfo)( char*, size_t );
// static PCSEZ pCSEZFunc = NULL;
// static PCSEProgInfo pCSEProgInfoFunc = NULL;  // SAC 12/20/12
// 
// bool LoadCSEDLLs( const char* pszCSEPathFile, const char* pszsCSEAshwat )
// {	bool bLibLoaded = false;
// 	if (hmAshwatDLL == NULL)
// 		hmAshwatDLL = LoadLibrary( pszsCSEAshwat );
// 	if (hmCSEDLL == NULL)
// 	{	hmCSEDLL = LoadLibrary( pszCSEPathFile );
// 		bLibLoaded = true;
// 	}
// 	if (bLibLoaded && hmCSEDLL == NULL)
// 	{	pCSEZFunc = NULL;
// 		pCSEProgInfoFunc = NULL;
// 	}
// 	if (hmCSEDLL && (bLibLoaded || pCSEZFunc == NULL))
// 		pCSEZFunc = (PCSEZ) GetProcAddress( hmCSEDLL, "CSEZ" );
// 	if (hmCSEDLL && (bLibLoaded || pCSEProgInfoFunc == NULL))
// 		pCSEProgInfoFunc = (PCSEProgInfo) GetProcAddress( hmCSEDLL, "CSEProgInfo" );
// 
// 	return (hmAshwatDLL && hmCSEDLL && pCSEZFunc && pCSEProgInfoFunc);
// }
// 
// void FreeCSEDLLIfLoaded()
// {	if (hmCSEDLL)
// 	{	FreeLibrary( hmCSEDLL );
// 		hmCSEDLL = NULL;
// 	}
// 	if (hmAshwatDLL)
// 	{	FreeLibrary( hmAshwatDLL );
// 		hmAshwatDLL = NULL;
// 	}
// }

double sfPctDoneFollowingSimulations = 98;  // SAC 8/19/13 - added to enable slower progress reporting when generating reports
bool sbLogCSECallbacks = true;
int siCallbackCount = 0;
bool sbAllowCallbackAbort = true;	// SAC 4/5/15
bool sbFreezeProgress = false;	// SAC 5/31/16
std::map<std::string, int> mapCSECallback;
char szCSECallbackMsg[1024];
int CSE_ProcessMessage( int level, const char* msg, int iRun/*=-1*/, const CSERunMgr* pCSERunMgr/*=NULL*/)
{
	siCallbackCount++;
	QString sCSERun;
	if (iRun >= 0)
		sCSERun = QString("[%1]").arg(QString::number(iRun));
	if (msg && strlen(msg) > 2 && (msg[0] != '-' || msg[1] != '-' || msg[2] != '-') && (msg[0] != ' ' || msg[1] != ' ' || msg[2] != ' '))
		sprintf_s( szCSECallbackMsg, 1024, "      CSE%s callback #%d, lvl= %d, msg= %s", sCSERun.toLocal8Bit().constData(), siCallbackCount, level, msg );
	else
		sprintf_s( szCSECallbackMsg, 1024, "      CSE%s callback #%d, lvl= %d", sCSERun.toLocal8Bit().constData(), siCallbackCount, level );
	if (sbLogCSECallbacks)
		BEMPX_WriteLogFile( szCSECallbackMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	//QString sMsg;
	//sMsg.sprintf( "      CSE_MsgCallback( lvll= %d, msg= %s )", level, msg );
	//BEMMessageBox( sMsg, "" );
//	return ((siCallbackCount % 40) == 0 ? CSE_ABORT : CSE_CONTINUE);
	int iRetVal = CSE_CONTINUE;

	bool bCalcProgress = (spAnalProgCallbackFunc != NULL);		// SAC 6/5/14 - progress reporting update
#ifdef CM_QTGUI
	if (!bCalcProgress && sqt_win && sqt_progress)
		bCalcProgress = true;
#endif

	if (bCalcProgress && pCSERunMgr)
	{	bCalcProgress =
			mapCSECallback.find(msg) != mapCSECallback.end() &&
			++mapCSECallback[msg] == pCSERunMgr->GetNumProgressRuns();
	}

	if (bCalcProgress)
	{	int i=-1;
		bool bFound=false, bError=false, bIncrementProgress=false;
		float fValSumThusFar = 0;
		long iProgVal = 0;
		while (!bFound && pszCSEProgressMsgs[++i] != NULL)
		{	fValSumThusFar += faCSEProgressVals[i];
			if (!strncmp(  pszCSEProgressMsgs[  i], msg, strlen(pszCSEProgressMsgs[i]) ))  // SAC 8/19/13 - fix bug where 'msg', when set to ' Reports' includes a trailing LF character
			{	bFound = true;
				iProgVal = (long) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((fValSumThusFar / fCSEProgressValSum / siNumProgressRuns) * sfPctDoneFollowingSimulations /*98*/));
				//		if (sbLogCSECallbacks)  // SAC 5/5/17 - debugging progress of iterating runs
				//			BEMPX_WriteLogFile( QString( "              si1ProgressRunNum: %1  siNumProgressRuns: %2  fValSumThusFar: %3  fCSEProgressValSum: %4  sfPctDoneFollowingSimulations: %5" ).arg( 
				//						QString::number(si1ProgressRunNum), QString::number(siNumProgressRuns), QString::number(fValSumThusFar), QString::number(fCSEProgressValSum),
				//						QString::number(sfPctDoneFollowingSimulations) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
		}
		if (!bFound && !strncmp( msg, "Error", 5 ))
		{	bError = true;
			siNumProgressErrors++;
		}
	//	if (sbLogCSECallbacks)  // SAC 5/5/17 - debugging progress of iterating runs
	//		BEMPX_WriteLogFile( QString( "              iProgVal: %1  slCurrentProgress: %2  sbFreezeProgress: %3" ).arg( QString::number(iProgVal), QString::number(slCurrentProgress), (sbFreezeProgress ? "true" : "false") ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

		// prevent progress from slipping backwards
		if (iProgVal > slCurrentProgress && !sbFreezeProgress)
		{	slCurrentProgress = iProgVal;
			bIncrementProgress = true;
		}
		else
			iProgVal = slCurrentProgress;

// QT Progress Dialog stuff
#ifdef CM_QTGUI
		if (sqt_win && sqt_progress)
		{	if (bFound)
			{	if (bIncrementProgress)
				{	sqt_progress->setValue( (int) iProgVal );
					SetProgressMessage( msg, false /*bBatchMode*/ );
					sqt_progress->setLabelText( sqProgressMsg );
				}
				sqt_win->repaint();
				if (sbAllowCallbackAbort && sqt_progress->wasCanceled())
					iRetVal = CSE_ABORT;
			}
			else if (bError)
			{	SetProgressMessage( msg, false /*bBatchMode*/ );
				sqt_progress->setLabelText( sqProgressMsg );
				sqt_win->repaint();
		}	}
#endif

	// SAC 6/5/14 - new callback mechanism
		if (iRetVal == CSE_CONTINUE && spAnalProgCallbackFunc != NULL)
		{	long lP = (bFound ? analysisProgressType_PercentProgress : analysisProgressType_Processing);
			if (lP == analysisProgressType_PercentProgress && slAnalysisProgressCallbackRetVal > 0)	// SAC 6/10/14 - avoid reporting "Reports" progress value following abort
				iProgVal = 0;
			long lCBRetVal = spAnalProgCallbackFunc( lP, iProgVal );
			if (lCBRetVal > 0)
			{	iRetVal = CSE_ABORT;
				slAnalysisProgressCallbackRetVal = lCBRetVal;
		}	}
	}	// end of - if (bCalcProgress)

//	// QT Progress Dialog stuff
//	#ifdef CM_QTGUI
//		if (sqt_win && sqt_progress)
//		{	int i=-1;
//			bool bFound=false;
//			float fValSumThusFar = 0;
//			while (!bFound && pszCSEProgressMsgs[++i] != NULL)
//			{	fValSumThusFar += faCSEProgressVals[i];
//	//			if (!strcmp(   pszCSEProgressMsgs[  i], msg ))
//				if (!strncmp(  pszCSEProgressMsgs[  i], msg, strlen(pszCSEProgressMsgs[i]) ))  // SAC 8/19/13 - fix bug where 'msg', when set to ' Reports' includes a trailing LF character
//				{	bFound = true;
//	
//	//QString sLogMsg;	sLogMsg.sprintf( "setting progress pct to %.1f:  %s", ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((fValSumThusFar / fCSEProgressValSum / siNumProgressRuns) * sfPctDoneFollowingSimulations /*98*/)), msg );
//	//BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//	
//					sqt_progress->setValue( (int) ((100 * (si1ProgressRunNum-1) / siNumProgressRuns) + ((fValSumThusFar / fCSEProgressValSum / siNumProgressRuns) * sfPctDoneFollowingSimulations /*98*/)) );
//					SetProgressMessage( msg );
//					sqt_progress->setLabelText( sqProgressMsg );
//					sqt_win->repaint();
//					if (sqt_progress->wasCanceled())
//						iRetVal = CSE_ABORT;
//				}
//			}
//			if (!bFound && !strncmp( msg, "Error", 5 ))
//			{	siNumProgressErrors++;
//				SetProgressMessage( msg );
//				sqt_progress->setLabelText( sqProgressMsg );
//				sqt_win->repaint();
//			}
//		}
//	#endif

	return iRetVal;
}

int /*CALLBACK*/ CSE_MsgCallback( int level, const char* msg )
{
	return CSE_ProcessMessage( level, msg);
}


/////////////////////////////////////////////////////////////////////////////

BOOL CMX_LoadDataModel(		const char* psBEMProcFileName /*=NULL*/, int iBEMType /*=BEMT_Other*/,
									const char* psInitLogFileName /*=NULL*/ )
{	assert( BEMT_Other == 1 );  // if not, then default iBEMType needs modification
	// Re-load and initialize the database definition
	return BEMPX_LoadDataModel( psBEMProcFileName, iBEMType, psInitLogFileName );
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  CMX_EvaluateRuleset()
//
// Purpose ------------------------------------------------------------------
//   Call a rule processor function which evaluates the compliance rulelist
//   identified by the filename argument for the currently loaded ruleset.
//   This function also reports the beginning and result of the rulelist
//   evaluation if instructed to (via the bReportToLog function argument).
//   
// Arguments ----------------------------------------------------------------
//   LPCSTR rulelistName  : the name of the rulelist to evaluate
//   BOOL   bReportToLog  : a flag indicating whether or not to report the
//                          beginning and result of the rulelist evaluation
//                          to the current project's log file.
//   
// Return Value -------------------------------------------------------------
//   The return value of the rule processor function called to evaluate the rulelist.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
static char szEval1[] = "Evaluating Compliance Rulelist '";
static char szEval2[] = "Evaluation of Rulelist '";
static char szSucs[]  = "' Completed Successfully";
static char szFail[]  = "' Failed";

BOOL CMX_EvaluateRuleset( LPCSTR rulelistName, BOOL bReportToLog, BOOL bTagDataAsUserDefined,
						        BOOL bVerboseOutput /*=FALSE*/,    // SAC 8/23/11
								  long* plNumRuleEvals /*=NULL*/, double* pdNumSeconds /*=NULL*/,   // SAC 10/12/11 - added to facilitate rule evaluation duration stats
                          PLogMsgCallbackFunc pLogMsgCallbackFunc /*=NULL*/,
								  void* pCompRuleDebugInfo /*=NULL*/ )  // SAC 12/12/13 - added pCompRuleDebugInfo argument
{
	QString sRLName = rulelistName;
	// SAC 7/11/12 - KLUDGE to convert ProposedInput rulelist name to rl_DEFAULT for DataModel rulesets
	if (BEMPX_GetRulesetOrganization() == RULESETORG_DATAMODEL && !sRLName.compare( "ProposedInput", Qt::CaseInsensitive ))
		sRLName = "rl_DEFAULT";

   if (bReportToLog)
   {
      QString sMsg = QString( "%1%2'..." ).arg( szEval1, rulelistName );
      BEMPX_WriteLogFile( sMsg );
		if (pLogMsgCallbackFunc)
			pLogMsgCallbackFunc( logMsgMESSAGE, (const char*) sMsg.toLocal8Bit().constData(), NULL );
   }

	int iInitErrCount = BEMPX_GetRulesetErrorCount();
   BOOL bRetVal = BEMPX_EvaluateRuleList( sRLName.toLocal8Bit().constData(), bTagDataAsUserDefined, 0 /*iEvalOnlyClass*/,
												-1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/, bVerboseOutput, pCompRuleDebugInfo,
												plNumRuleEvals, pdNumSeconds, pLogMsgCallbackFunc );

   if (bReportToLog)
   {
      QString sMsg;
		if (plNumRuleEvals == NULL || pdNumSeconds == NULL)
			sMsg = QString( "%1%2%3" ).arg( szEval2, rulelistName, (bRetVal ? szSucs : szFail) );
		else
			sMsg = QString( "%1%2%3   (%4 rules evaluated in %5 seconds => %6 rule evaluations/sec)" ).arg( szEval2, rulelistName, (bRetVal ? szSucs : szFail),
											QString::number(*plNumRuleEvals), QString::number(*pdNumSeconds), QString::number(*plNumRuleEvals / *pdNumSeconds) );
											//lNumRuleEvals, dNumSeconds, (lNumRuleEvals/dNumSeconds) );
      BEMPX_WriteLogFile( sMsg );
		if (pLogMsgCallbackFunc)
			pLogMsgCallbackFunc( logMsgMESSAGE, (const char*) sMsg.toLocal8Bit().constData(), NULL );
   }
   return (bRetVal && BEMPX_GetRulesetErrorCount() == iInitErrCount);
}


/////////////////////////////////////////////////////////////////////////////
//		return values:		0 => Success
//								1 => Unrecognized pszCompParam
//								2 => Component by the name pszCompName not found
static inline int ParseCompParamAndName( const char* pszCompParam, const char* pszCompName, long& lDBID, int& iOccur )
{	int iRetVal = 0;
	lDBID = BEMPX_GetDatabaseID( pszCompParam );   //, long iCompID=0, BOOL bTreatParentAsObject=FALSE, int* piRefCompID=NULL );
	if (lDBID < BEM_COMP_MULT)
		iRetVal = 1;
	else
	{	iOccur = -1;
		int iError;
		if (pszCompName && strlen( pszCompName ) > 0)
		{	int iClassID = BEMPX_GetClassID( lDBID );
			BEMObject* pObj = BEMPX_GetObjectByName( iClassID, iError, pszCompName );
			if (pObj == NULL || pObj->getClass() == NULL)
				iRetVal = 2;
			else
			{	iOccur = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
				if (iOccur < 0)
				{	assert( FALSE );   // shouldn't EVER happen, since the DBID and object name are both valid
					iRetVal = 2;
				}
			}
	}	}
	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////
// CMX_GetDataString()
//---------------------------------------------------------------------------
//		return values:		0 => Success
//								1 => Unrecognized pszCompParam
//								2 => Component by the name pszCompName not found
//								3 => Error retrieving string from BEMProc
//								4 => Concatenated string returned - char* string passed into routine was too small to handle the return string
/////////////////////////////////////////////////////////////////////////////
int CMX_GetDataString( char* sReturnStr, int iRetStrLen, const char* pszCompParam, const char* pszCompName /*=NULL*/, 
							  BOOL bAddCommas /*=TRUE*/, int iPrecision /*=0*/, const char* pszDefault /*=NULL*/ )
{	long lDBID;		int iOccur;
	int iRetVal = ParseCompParamAndName( pszCompParam, pszCompName, lDBID, iOccur );
	if (iRetVal == 0)
	{	QString sRetStr;
		if (!BEMPX_GetString( lDBID, sRetStr, bAddCommas, iPrecision, -1 /*iDispDataType*/, iOccur,
										  BEMO_User /*iObjType*/, pszDefault ))
			iRetVal = 3;
		else
		{	if (sRetStr.length() > iRetStrLen-1)
				iRetVal = 4;
	//		strncpy_s( sReturnStr, iRetStrLen, sRetStr.toLocal8Bit().constData(), iRetStrLen-1 );
			const QByteArray local8Str = sRetStr.toLocal8Bit();		// ensure transmittance of special chars such as superscript '2' ??
			strncpy_s( sReturnStr, iRetStrLen, local8Str.constData(), iRetStrLen-1 );
			sReturnStr[iRetStrLen-1] = '\0';
		}
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMX_GetDataInteger()
//---------------------------------------------------------------------------
//		return values:		0 => Success
//								1 => Unrecognized pszCompParam
//								2 => Component by the name pszCompName not found
//								3 => Error retrieving integer from BEMProc
/////////////////////////////////////////////////////////////////////////////
int CMX_GetDataInteger( long* pReturnInt, const char* pszCompParam,
								const char* pszCompName /*=NULL*/, long lDefault /*=0*/ )
{	long lDBID;		int iOccur;
	int iRetVal = ParseCompParamAndName( pszCompParam, pszCompName, lDBID, iOccur );
	if (iRetVal == 0)
	{	long lRetVal;
		if (!BEMPX_GetInteger( lDBID, lRetVal, lDefault, -1 /*iDispDataType*/, iOccur ))
			iRetVal = 3;
		else
			*pReturnInt = lRetVal;
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMX_GetDataFloat()
//---------------------------------------------------------------------------
//		return values:		0 => Success
//								1 => Unrecognized pszCompParam
//								2 => Component by the name pszCompName not found
//								3 => Error retrieving float from BEMProc
/////////////////////////////////////////////////////////////////////////////
int CMX_GetDataFloat( double* pReturnFlt, const char* pszCompParam,
							 const char* pszCompName /*=NULL*/, float fDefault /*=0*/ )
{	long lDBID;		int iOccur;
	int iRetVal = ParseCompParamAndName( pszCompParam, pszCompName, lDBID, iOccur );
	if (iRetVal == 0)
	{	double fRetVal;
		if (!BEMPX_GetFloat( lDBID, fRetVal, fDefault, -1 /*iDispDataType*/, iOccur ))
			iRetVal = 3;
		else
			*pReturnFlt = fRetVal;
	}
	return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////

double DeltaTime( boost::posix_time::ptime& tmStart )
{	//boost::posix_time::ptime tNow(boost::posix_time::microsec_clock::local_time());
	//boost::posix_time::time_duration td = tNow - tmStart;
	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStart;
	return ((double) td.total_microseconds()) / 1000000.0;
}

int LocalEvaluateRuleset( QString& sErrMsg, int iErrRetVal, const char* pszRulelistName, BOOL bVerbose, void* pCompRuleDebugInfo )
{
	int iRetVal = 0;
			            //BOOL __declspec(dllexport) __cdecl CMX_EvaluateRuleset( LPCSTR rulelistName, BOOL bReportToLog=FALSE, BOOL bTagDataAsUserDefined=FALSE,
	                  //																		  BOOL bVerboseOutput=FALSE,    // SAC 8/23/11
							//																		  long* plNumRuleEvals=NULL, double* pdNumSeconds=NULL,   // SAC 10/12/11 - added to facilitate rule evaluation duration stats
							//																		  PLogMsgCallbackFunc pLogMsgCallbackFunc=NULL,
							//																		  void* pCompRuleDebugInfo=NULL );  // SAC 12/12/13 - added pCompRuleDebugInfo argument - void pointer to BEMCompNameTypePropArray object
	if (!CMX_EvaluateRuleset( pszRulelistName, bVerbose /*bLogRuleEvaluation*/, FALSE /*bTagDataAsUserDefined*/, bVerbose /*bVerboseOutput*/,
										NULL /*plNumRuleEvals*/, NULL /*pdNumSeconds*/, NULL /*PLogMsgCallbackFunc*/, pCompRuleDebugInfo ))
	{	assert( FALSE );
		sErrMsg = QString( "ERROR:  Error encountered evaluating rulelist '%1'" ).arg( pszRulelistName );
		iRetVal = iErrRetVal;
	}
	return iRetVal;
}


static char szTrans1[]   = "Generating '%s' transformation...  ";
static char szTrans2[]   = "Evaluating '%s' transformation Rules...  ";
static char szTrnsSucs[] = "success";
static char szTrsnErr[]  = "ERROR(s) encountered";

BOOL CMX_TransformModel(	LPCSTR sShortTransformName, BOOL bEvalRules, BOOL bReportToLog /*=FALSE*/,
	  								BOOL bVerboseOutput /*=FALSE*/, const char* pszBEMBaseDetailsPathFile /*=NULL*/,
									BOOL bLogDurationStats /*=FALSE*/, void* pCompRuleDebugInfo /*=NULL*/ )  // SAC 1/9/14 - added pCompRuleDebugInfo argument - void pointer to BEMCompNameTypePropArray object
{
	BOOL bRetVal = TRUE;

			if (bLogDurationStats)
   			BEMPX_SetDurationMark( 2 );

	int iModelCount = BEMPX_GetModelCount();
	int iBEMProcIdxToCopy = 0;
	long laDBIDsToBypassCopy[21] = {  0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,  0 };
   int iTransIdx = BEMPX_GetTransformInitializationInfo( sShortTransformName, &iBEMProcIdxToCopy, laDBIDsToBypassCopy, 20 );
	assert( iTransIdx == iModelCount );
	if (iTransIdx < 0)
	{
// ERROR loading transformation stuff
		bRetVal = FALSE;
	}
	else
	{
      QString sMsg;
	   if (bReportToLog)
	      sMsg.sprintf( szTrans1, sShortTransformName );

		bRetVal = BEMPX_AddModel( iBEMProcIdxToCopy, laDBIDsToBypassCopy, true /*bSetActiveBEMProcToNew*/ );
      if (!bRetVal)
		{
		   if (bReportToLog)
				sMsg += szTrsnErr;
			assert( FALSE );
// ERROR generating transformation
		}
		else if (bReportToLog)
			sMsg += szTrnsSucs;
	   if (bReportToLog)
	      BEMPX_WriteLogFile( sMsg );

		if (/*iTransIdx == 1 &&*/ pszBEMBaseDetailsPathFile && strlen( pszBEMBaseDetailsPathFile ) > 0)
		{	QString sDbgDtlFN = pszBEMBaseDetailsPathFile + QString( "-B4Eval" );
			BEMPX_WriteProjectFile( sDbgDtlFN.toLocal8Bit().constData(), BEMFM_DETAIL );
		}

		if (bRetVal && bEvalRules)
			bRetVal = CM_EvaluateModelRules( sShortTransformName, bReportToLog, bVerboseOutput, pszBEMBaseDetailsPathFile, bLogDurationStats, pCompRuleDebugInfo );

			if (bLogDurationStats)
			{	QString sEvalTransSecsMsg;
				sEvalTransSecsMsg.sprintf( "      Model transformation '%s' duration:  %.2f seconds", sShortTransformName, BEMPX_GetDurationSinceMark( 2 ) );
		      BEMPX_WriteLogFile( sEvalTransSecsMsg );
			}
	}

	return bRetVal;
}

BOOL CM_EvaluateModelRules(	LPCSTR sShortTransformName, BOOL bReportToLog /*=FALSE*/,
	  									BOOL bVerboseOutput /*=FALSE*/, const char* pszBEMBaseDetailsPathFile /*=NULL*/,
										BOOL bLogDurationStats /*=FALSE*/, void* pCompRuleDebugInfo /*=NULL*/ )  // SAC 1/9/14 - added pCompRuleDebugInfo argument - void pointer to BEMCompNameTypePropArray object
{
	BOOL bRetVal = TRUE;

      QString sMsg;
//		if (bRetVal)
//		{
		   if (bReportToLog)
		      sMsg.sprintf( szTrans2, sShortTransformName );

			if (bLogDurationStats)
   		{	BEMPX_SetDurationMark( 3 );
   			BEMPX_SetDurationMark( 4 );
			}

   		int iEvalTransRetVal = BEMPX_EvaluateTransform( sShortTransformName, bVerboseOutput, pCompRuleDebugInfo );
									// int BEMPX_EvaluateTransform(	LPCSTR sShortTransformName, BOOL bVerboseOutput /*=FALSE*/, void* pvTargetedDebugInfo /*=NULL*/,
									// 											long* plNumRuleEvals /*=NULL*/, double* pdNumSeconds /*=NULL*/ )
			if (bLogDurationStats)
			{	QString sEvalTransSecsMsg;
				sEvalTransSecsMsg.sprintf( "         Transform '%s' rule evaluation duration:  %.2f seconds", sShortTransformName, BEMPX_GetDurationSinceMark( 3 ) );
		      BEMPX_WriteLogFile( sEvalTransSecsMsg );
			}

			if (iEvalTransRetVal < 0)
			{	
			   if (bReportToLog)
					sMsg += szTrsnErr;
				assert( FALSE );
// ERROR evaluating transformation rules
				bRetVal = FALSE;
			}
			else if (bReportToLog)
				sMsg += szTrnsSucs;
		   if (bReportToLog)
		      BEMPX_WriteLogFile( sMsg );

//QString sDbgDetailWrite;	sDbgDetailWrite.sprintf( "pszBEMBaseDetailsPathFile = %s -%s writing BEM details file",
//										((pszBEMBaseDetailsPathFile==NULL || strlen( pszBEMBaseDetailsPathFile ) < 1) ? "blank" : pszBEMBaseDetailsPathFile), 
//										((pszBEMBaseDetailsPathFile==NULL || strlen( pszBEMBaseDetailsPathFile ) < 1) ? " NOT" : "") );			BEMMessageBox( sDbgDetailWrite, "" );
			if (pszBEMBaseDetailsPathFile && strlen( pszBEMBaseDetailsPathFile ) > 0)
				BEMPX_WriteProjectFile( pszBEMBaseDetailsPathFile, BEMFM_DETAIL );
//		}

	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
//
// Exported Function:  CMX_WriteSimulationInput()
//
// Purpose ------------------------------------------------------------------
//   Call a simulation DLL function which causes a simulation input file to be
//   written based on the current contents of the building database.
//   
// Arguments ----------------------------------------------------------------
//   SimulationType eSimType        : the type of simulation input file to write (design day vs. annual)
//   const char*    pszInputFile    : the path and filename to store the simulation input as
//   const char*    pszUtilRatesDir : the path to the directory where the utility rate input files are stored
//   
// Return Value -------------------------------------------------------------
//   The return value of the simulation DLL function called to write the input file.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BOOL CMX_WriteSimulationInput( SimulationType /*eSimType*/,
                               const char* /*pszInputFile*/,
                               const char* /*pszUtilRatesDir*/, int /*iSimVer*/ )
{
   // Call the simulation DLL function to write the simulation input file
	                         BEMMessageBox( "Call to CS32_WriteSimulationInput()", "" );
   BOOL bRetVal = TRUE;  // CS32_WriteSimulationInput( eSimType, pszInputFile, pszUtilRatesDir, iSimVer, TRUE );
   // Close all files to ensure that all data is written before proceeding
   _flushall();

   return bRetVal;
}


// needed? /////////////////////////////////////////////////////////////////////////////
// needed? //
// needed? // Callback Function:  CMX_SimCallbackFunc()
// needed? //
// needed? /////////////////////////////////////////////////////////////////////////////
// needed? 
// needed? typedef long (CALLBACK EXPORT* PCMUICallbackFunc)( BOOL, const char*, const char*, int );
// needed? 
// needed? static PCMUICallbackFunc slpfnCallback;
// needed? 
// needed? static float sfCurProgress = 0;
// needed? static float sfIncProgress = 0;
// needed? static float sfMaxProgress = 0;
// needed? 
// needed? //#ifdef _DEBUG
// needed? static QString sDbgFileName;
// needed? //#endif
// needed? 
// needed? long CALLBACK CMX_SimCallbackFunc( long l1, long l2, long l3, long l4, long l5 )
// needed? {
// needed?    long lRetVal = 0;
// needed? 
// needed?    if (sfCurProgress < sfMaxProgress)
// needed?       sfCurProgress += sfIncProgress;
// needed?    else
// needed?       sfCurProgress = sfMaxProgress;
// needed? 
// needed? //   assert (slpfnCallback);
// needed?    if (slpfnCallback)
// needed?       lRetVal = slpfnCallback( FALSE, NULL, NULL, (int) sfCurProgress );
// needed? 
// needed? //#ifdef _DEBUG
// needed?          CFile dbgFile;
// needed?          // open debug file
// needed?          if (dbgFile.Open( sDbgFileName, CFile::modeWrite ))
// needed?          {
// needed?             dbgFile.SeekToEnd();
// needed?             QString sTmp;
// needed?             sTmp.sprintf( "l1: %2d,  l2: %2d,  l3: %2d,  l4: %2d,  l5: %4d,  sfCurProgress: %f\n",
// needed?                          l1, l2, l3, l4, l5, sfCurProgress );
// needed?             dbgFile.Write( sTmp.GetBuffer( sTmp.length() ), sTmp.length() );
// needed?             dbgFile.Close();
// needed?          }
// needed? //#endif
// needed? 
// needed?    return lRetVal;
// needed? }


/////////////////////////////////////////////////////////////////////////////

// SAC 6/19/14 - moved from OpenStudioInterface
int CopyAnalysisResultsObjects( QString& sErrMsg, const char* pszRunID, int iBEMProcIdxSrc, int iBEMProcIdxDest, bool bIncludeEnergyUseObjs )
{	int iRetVal = 0;
	if (iBEMProcIdxSrc >= 0 && iBEMProcIdxDest >= 0 && iBEMProcIdxSrc != iBEMProcIdxDest)
	{	// copy EUseSummary & EnergyUse objects from previous hourly results storage run (iBEMProcIdxSrc) into the current model (iBEMProcIdxDest)
		int iObjClsToCopy[3] = { BEMPX_GetDBComponentID( "EUseSummary" ), (bIncludeEnergyUseObjs ? BEMPX_GetDBComponentID( "EnergyUse" ) : 0), 0 };
												assert( iObjClsToCopy[0] > 0 && (iObjClsToCopy[1] > 0 || !bIncludeEnergyUseObjs) );
		int iObjClsIdx=-1, iError;
		while (iObjClsToCopy[++iObjClsIdx] > 0)
		{  // first blast all objects of this type in the target model
			int iNumObjsToDel = BEMPX_GetNumObjects( iObjClsToCopy[iObjClsIdx], BEMO_User, iBEMProcIdxDest );
			for (int iDelObjIdx = iNumObjsToDel-1; iDelObjIdx >= 0; iDelObjIdx--)
			{	BEMObject* pDelObj = BEMPX_GetObjectByClass( iObjClsToCopy[iObjClsIdx], iError, iDelObjIdx, BEMO_User, iBEMProcIdxDest );		assert( pDelObj );
				if (pDelObj)
					BEMPX_DeleteObject( pDelObj, iBEMProcIdxDest );
			}
			int iCopyRetVal  = (iObjClsToCopy[iObjClsIdx] <= 0 ? 0 : BEMPX_CopyClassObjectsAcrossModels( iObjClsToCopy[iObjClsIdx], iBEMProcIdxSrc, iBEMProcIdxDest ));
			if (iObjClsToCopy[iObjClsIdx] < 1)
			{	sErrMsg.sprintf( "Invalid results object types (%s model (%d))", pszRunID, iObjClsIdx );
//											34 : Invalid results object types
				iRetVal = 34;
				//	if ((iRun==0 && iDontAbortOnErrorsThruStep < 1) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 9))  // check flag to bypass errors
				//		iRetVal = (iRetVal > 0 ? iRetVal : 34);		// DO abort
			}
			else if (iCopyRetVal != 0)
			{	sErrMsg.sprintf( "Error copying results objects from model %d to %d (%d class)", iBEMProcIdxSrc, iBEMProcIdxDest, iObjClsToCopy[iObjClsIdx] );
//											35 : Error copying results objects from a previous model
				iRetVal = 35;
				//	if ((iRun==0 && iDontAbortOnErrorsThruStep < 1) || (iRun==1 && iDontAbortOnErrorsThruStep < 3) || (iRun==2 && iDontAbortOnErrorsThruStep < 6) || (iRun==3 && iDontAbortOnErrorsThruStep < 9))  // check flag to bypass errors
				//		iRetVal = (iRetVal > 0 ? iRetVal : 35);		// DO abort
			}
	}	}
	else
	{	assert( FALSE );	// invalid iBEMProcIdxSrc and/or iBEMProcIdxDest
	}
	return iRetVal;
}

int CM_CopyAnalysisResultsObjects_CECNonRes( QString& sErrMsg, const char* pszRunID, int iBEMProcIdxSrc, int iBEMProcIdxDest )
{	return CopyAnalysisResultsObjects( sErrMsg, pszRunID, iBEMProcIdxSrc, iBEMProcIdxDest, true );
}

/////////////////////////////////////////////////////////////////////////////

bool AppendMessage( char* pszMsg, int iMsgLen, const char* pszMsgToAppend )
{	bool bRetVal = false;
	if (pszMsg && iMsgLen > 0 && (int) strlen(pszMsg) < iMsgLen && pszMsgToAppend)
	{	int iExistStrLen = strlen(pszMsg);
		int iLenToAppend = strlen( pszMsgToAppend );
		if (iExistStrLen > 0)
			iLenToAppend += 2;
		if ((iExistStrLen + iLenToAppend) < iMsgLen)
		{	if (iExistStrLen < 1)
				strncpy_s( pszMsg, iMsgLen, pszMsgToAppend, iLenToAppend );
			else
			{	strcat_s( pszMsg, iMsgLen, "\n" );
				strcat_s( pszMsg, iMsgLen, pszMsgToAppend );
			}
			bRetVal = true;
		}
	}
	return bRetVal;
}

void PrependPathIfNecessary( std::string& sFileName, std::string& sPath )
{	int iColonPos = sFileName.find(':');
	int iSlashPos = sFileName.find('\\');
	if ((iColonPos > 0 && iColonPos < 3) || iSlashPos == 0)
	{	// do nothing - path already specified
	}
	else
		sFileName = sPath + sFileName;
}

/////////////////////////////////////////////////////////////////////////////

void ParseCSV(const std::string& csvSource, std::vector<std::vector<std::string> >& lines)
{
	bool inQuote(false);
	bool newLine(false);
	std::string field;
	lines.clear();
	std::vector<std::string> line;

	std::string::const_iterator aChar = csvSource.begin();
	while (aChar != csvSource.end())
	{
		switch (*aChar)
		{	case '"':	newLine = false;
							inQuote = !inQuote;
							break;
			case ',':	newLine = false;
							if (inQuote == true)
							{	field += *aChar;
							}
							else
							{	line.push_back(field);
								field.clear();
							}
							break;
			case '\n':
			case '\r':	if (inQuote == true)
							{	field += *aChar;
							}
							else
							{	if (newLine == false)
								{	line.push_back(field);
									lines.push_back(line);
									field.clear();
									line.clear();
									newLine = true;
								}
							}
							break;
			default:		newLine = false;
							field.push_back(*aChar);
							break;
		}
		aChar++;
	}

	if (field.size())
		line.push_back(field);

	if (line.size())
		lines.push_back(line);
}

/////////////////////////////////////////////////////////////////////////////

void ProcessAnalysisError( QString& sErrMsg, bool& bAbort, int& iRetVal, int iErrID, bool bErrCausesAbort, bool bWriteToLog, char* pszErrorMsg, int iErrorMsgLen, int iDontAbortOnErrorsThruStep, int iStepCheck )
{
	if (!AppendMessage( pszErrorMsg, iErrorMsgLen, sErrMsg.toLocal8Bit().constData() ))
		BEMPX_AddRulesetError( sErrMsg.toLocal8Bit().constData() );	// only log ruleset error if sErrMsg NOT appended onto return error message (pszErrorMsg)
	if (bWriteToLog)
		BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	if (iDontAbortOnErrorsThruStep < iStepCheck)  // check flag to bypass errors
	{	iRetVal = (iRetVal > 0 ? iRetVal : iErrID);		// DO abort
		if (!bAbort && bErrCausesAbort)
			bAbort = true;
	}
	sErrMsg.clear();
}

/////////////////////////////////////////////////////////////////////////////

// SAC 6/10/13 - added to facilitate generation of ruleset-defined building model reports/summaries
//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:
//											 1 : No report save path/file specified
//											 2 : No report selection specified
//											 3 : Report selection didn't include file extension in trailing parentheses (as expected)
//											 4 : Report file cannot be written to, or user chose not to overwrite it
//											 5 : Error evaluating report generation rulelist
//											 6 : Error generating full path from relative path for file being written
//											 7 : Generated report path/filename too long to be copied into pszFinalReportPathFile argument
int CMX_GenerateRulesetModelReport(	const char* pszReportSavePathFileNoExt, const char* pszReportSelection,
	 											char* pszFinalReportPathFile, int iFinalReportPathFileLength,
	 											bool bVerbose /*=false*/, bool bSilent /*=false*/ )
{	int iRetVal = 0;
	QString sRptSel = pszReportSelection;
	sRptSel.replace( " ", NULL );
	int iParenIdx = sRptSel.lastIndexOf('(');												assert( iParenIdx > 0 );
	int iExtLen = sRptSel.lastIndexOf(')') - iParenIdx - 1;							assert( iExtLen > 0 );
	if (pszReportSavePathFileNoExt == NULL || strlen( pszReportSavePathFileNoExt ) < 1)
		iRetVal = 1;
	else if (sRptSel.isEmpty())
		iRetVal = 2;
	else if (iParenIdx < 3 || iExtLen < 1)
		iRetVal = 3;
	else
	{	QString sRptPathFile = pszReportSavePathFileNoExt;
		sRptPathFile += " - ";
		sRptPathFile += sRptSel.left( iParenIdx );
		sRptPathFile += '.';
		sRptPathFile += sRptSel.mid( iParenIdx+1, iExtLen );
//BEMMessageBox( sRptPathFile, "" );

			QString sRptRL = pszReportSelection;
			sRptRL.replace( " ", "_" );
			sRptRL.replace( "(", NULL );
			sRptRL.replace( ")", NULL );
			sRptRL = "ReportMaster_" + sRptRL;

				if (bVerbose)  // SAC 2/10/14
				{	QString sLogMsg;
					sLogMsg.sprintf( "         generating report '%s' via rulelist '%s' to file:  %s", pszReportSelection, sRptRL.toLocal8Bit().constData(), sRptPathFile.toLocal8Bit().constData() );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}

			iRetVal = Local_GenerateRulesetModelReport( sRptPathFile, sRptRL, bVerbose, bSilent );
			if (iRetVal == 0 && pszFinalReportPathFile)
			{	if (iFinalReportPathFileLength <= sRptPathFile.length())
					iRetVal = 7;
				else
					strncpy_s( pszFinalReportPathFile, iFinalReportPathFileLength, sRptPathFile.toLocal8Bit().constData(), sRptPathFile.length() );
			}
	}
	return iRetVal;
}

int Local_GenerateRulesetModelReport( QString sRptPathFile, QString sRptRL,
	 											bool bVerbose /*=false*/, bool bSilent /*=false*/ )
{	int iRetVal = 0;

	// SAC 2/10/14 - added code to expand relative path to full/absolute path, since opening of file via relative path in BEMPX_WriteFileFromRulelist() is failing
		char pszFullPath[_MAX_PATH];
		if (_fullpath( pszFullPath, sRptPathFile.toLocal8Bit().constData(), _MAX_PATH ) == NULL)
			iRetVal = 6;
		else
		{	sRptPathFile = pszFullPath;

			QString sMsg;
			sMsg.sprintf( "The %s file '%s' is opened in another application.  This file must be closed in that "
			             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
							 "(once the file is closed), or \n'Cancel' to abort the %s.", "report", sRptPathFile.toLocal8Bit().constData(), "report generation" );
			if (!OKToWriteOrDeleteFile( sRptPathFile.toLocal8Bit().constData(), sMsg, bSilent ))
				iRetVal = 4;
			else
			{	//bool bVerbose = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);
				if (!BEMPX_WriteFileFromRulelist( sRptPathFile.toLocal8Bit().constData(), sRptRL.toLocal8Bit().constData(), bVerbose ))  // SAC 6/9/13
					iRetVal = 5;
			}
		}

	return iRetVal;
}

/////////////////////////////////////////////////////////////////////////////

// SAC 5/27/00 - added to retrieve the names of each rulelist in the ruleset
int CMX_GetRulelistNames( QVector<QString>& sRulelistNames )
{	return BEMPX_GetRulelistNames( sRulelistNames );
}


/////////////////////////////////////////////////////////////////////////////
// Returns the last Win32 error, in string format. 
std::string GetLastErrorAsString( std::string sPrepend )
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if(errorMessageID == 0)
		return sPrepend; //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
											NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	std::string message(messageBuffer, size);
	//Free the message buffer.
	LocalFree(messageBuffer);

	if (sPrepend.size() > 0)
		message = sPrepend + message;

	return message;
}

/////////////////////////////////////////////////////////////////////////////

bool GetDLLPath( QString& sDLLPath )
{	char path[_MAX_PATH];
	HMODULE hm = NULL;
	if (!GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
										(LPCSTR) &GetDLLPath, &hm))
	{	//	int ret = GetLastError();
		//	fprintf(stderr, "GetModuleHandle returned %d\n", ret);
	}
	else
	{	GetModuleFileNameA( hm, path, sizeof path );
		if (strlen( path ) > 0)
		{	sDLLPath = path;
			sDLLPath = sDLLPath.left( sDLLPath.lastIndexOf( '\\' ) + 1 );
		}
	}
	return (!sDLLPath.isEmpty() && sDLLPath[sDLLPath.length()-1] == '\\');
}

/////////////////////////////////////////////////////////////////////////////

QString GenerateTempFileName()
{
   char pszTempPath[MAX_PATH], pszTempFile[MAX_PATH];
   pszTempFile[0] = '\0';
   
   DWORD dwRes = GetTempPath( MAX_PATH, pszTempPath );
   if ( !dwRes )
   {
		throw std::runtime_error( GetLastErrorAsString( "Error getting temporary path: " ) );
   }

   dwRes = GetTempFileName( pszTempPath, "CUI", 0, pszTempFile );
   if ( !dwRes ) 
   {
		throw std::runtime_error( GetLastErrorAsString( "Error getting temporary filename: " ) );
   }
   return QString( pszTempFile );
}

// SAC 2/1/14 - 
int CMX_SaveAnalysisResultsToTempFiles( QVector<QString>& saProjEUseSumObjs, QVector<QString>& saUniqueEUseSumObjs, QVector<QString>& saTempPathFiles )
{
	int iRetVal = 0;

		// SAC 11/11/13 - BEFORE restoring original project file, Write temporary files for each EUseSummary object for later import into project immediately after re-opening the project.
		int iError, iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
		int iNumEUseSummaryObjs = BEMPX_GetNumObjects( iCID_EUseSummary );

//			QVector<QString> saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles, saNewEUseSumObjs;
			int iRS;
			if (iCID_EUseSummary > 0 && iNumEUseSummaryObjs > 0)
			{	QString sTempPathFile;
				BEMObject* pResSumObj;
				for (iRS=0; iRS < iNumEUseSummaryObjs; iRS++)
				{	BOOL bObjWritten = FALSE;
					pResSumObj = BEMPX_GetObjectByClass( iCID_EUseSummary, iError, iRS );
					if (pResSumObj && !pResSumObj->getName().isEmpty())
					{	if (StringInArray( saProjEUseSumObjs, pResSumObj->getName() ) < 0)
						{	sTempPathFile = GenerateTempFileName();
							if (BEMPX_WriteProjectComponent( sTempPathFile.toLocal8Bit().constData(), pResSumObj, -1 /*iBEMProcIdx*/, true /*bWriteAllProperties*/ ))		// WRITE EUseSummary object (ALL properties) to temporary file
							{	bObjWritten = TRUE;
								saUniqueEUseSumObjs.push_back( pResSumObj->getName() );
								saTempPathFiles.push_back( sTempPathFile );
							}
							else
							{	//throw std::runtime_error( GetLastErrorAsString( "Error writing project component: " ) );  <- results in warning C4700
								assert( false );
							}
						}
					}
					assert( bObjWritten || pResSumObj==NULL );
					//saProjEUseSumObjs.push_back( (bObjWritten && pResSumObj==NULL ? "" : pResSumObj->getName()) );   // maps to array elements of Proj:ResultSummary[*]
					if (!bObjWritten || pResSumObj==NULL)
						saProjEUseSumObjs.push_back( "" );
					else
						saProjEUseSumObjs.push_back( pResSumObj->getName() );
				}
			}

	return iRetVal;
}

int CMX_RestoreAnalysisResultsFromTempFiles( QVector<QString>& saUniqueEUseSumObjs, QVector<QString>& saTempPathFiles )
{
	int iRetVal = 0;
	int iRS, iError, iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
	QVector<QString> saNewEUseSumObjs;

		// SAC 6/25/13 - AFTER restoring original project file, Import EUseSummary objects from temporary files to facilitate subsequent results display
			if (saUniqueEUseSumObjs.size())
			{	// start by deleting any EUseSummary obejcts that might exist in current project
				int iNumEUseSumObjs = BEMPX_GetNumObjects( iCID_EUseSummary /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );
				for (iRS=iNumEUseSumObjs-1; iRS >= 0; iRS--)
				{	BEMObject* pEUseSumObj = BEMPX_GetObjectByClass( iCID_EUseSummary, iError, iRS /*, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1*/ );		assert( pEUseSumObj );
					if (pEUseSumObj)
						BEMPX_DeleteObject( pEUseSumObj /*, int iBEMProcIdx=-1*/ );
				}
	         // then read EUseSummary objects from temporary file(s)
				int iNumResSum = saUniqueEUseSumObjs.size();
				for (iRS=0; iRS < iNumResSum; iRS++)
				{	BEMObject* pNewEUseSumObj = BEMPX_ReadProjectComponent( saTempPathFiles[iRS].toLocal8Bit().constData(), iCID_EUseSummary /*, int iBEMProcIdx=-1*/ );    // IMPORT EUseSummary objects from temporary files
					if (pNewEUseSumObj && !pNewEUseSumObj->getName().isEmpty())
						saNewEUseSumObjs.push_back( pNewEUseSumObj->getName() );
					else
						saNewEUseSumObjs.push_back( "" );
					DeleteFile( saTempPathFiles[iRS].toLocal8Bit().constData() );
				}
				//	// and then store assignments of these objects to Proj component
				//	QString sNewSumObjName;
				//	for (iRS=0; iRS < iResSumArrLen; iRS++)
				//		if (!saProjEUseSumObjs[iRS].isEmpty())
				//		{	int iUnqSumIdx = StringInArray( saUniqueEUseSumObjs, saProjEUseSumObjs[iRS] );		assert( iUnqSumIdx >= 0 && iUnqSumIdx < saNewEUseSumObjs.size() );
				//			if (iUnqSumIdx >= 0 && iUnqSumIdx < saNewEUseSumObjs.size())
				//			{	sNewSumObjName = saNewEUseSumObjs[iUnqSumIdx];												assert( !sNewSumObjName.isEmpty() );
				//				if (!sNewSumObjName.isEmpty())
				//					BEMPX_SetBEMData( lDBID_Proj_ResultSummary + iRS, BEMP_QStr, (void*) &sNewSumObjName );
				//			}
				//		}

		//		// ALSO store RunDate to be help verify whether results are "current"
		//		assert( lTime > 0);
		//		if (lTime > 0)
		//			BEMPX_SetBEMData( elDBID_Proj_RunDate, BEMP_Int, (void*) &lTime );

			}

	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// SAC 11/4/15 - 
static Qt_URLFile surlSiteChk;

int CheckSiteAccessViaQt(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy
										const char* pszProxyType, char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bVerbose /*=false*/ )
{	int iRetVal = 0;
	TCHAR szTempFileName[MAX_PATH];
	QString qsVerbose;
															if (bVerbose && (pszErrorMsg == NULL || iErrorMsgLen < 1))
																bVerbose = false;
															if (bVerbose)
																qsVerbose = "\nCheckSiteAccessViaQt() - ";

	bool bQAppInit = (sq_app == NULL);
	if (bQAppInit)
	{	assert( sq_app == NULL && sqt_win == NULL && sqt_progress == NULL );
		int argc = 0;
		sq_app = new QApplication( argc, NULL );
		if (sq_app)
			ssEXEPath = sq_app->applicationDirPath();
	}

//																		QMessageBox msgBox;
//																		msgBox.setWindowTitle( "CheckSiteAccessViaQt()" );
//																		msgBox.setIcon( QMessageBox::Warning ); 
//																		msgBox.setText( QString("Site: %1\nProxy Address: %2\nProxy Cred: %3\nProxy Type: %4\nErrMsg Length: %L5\nVerbose: %6").arg(pszSite).arg(pszProxyAddress).arg(pszProxyCredentials).arg(pszProxyType).arg(iErrorMsgLen).arg((bVerbose?"true":"false")) );
//																		msgBox.exec();

	int iFirstTry = (pszProxyAddress && strlen( pszProxyAddress ) > 0) ? 0 : 1;   // if proxy server settings passed in, then ONLY try that method
	int iLastTry  = (iFirstTry == 0) ? 0 : 2;  // was: 100;
	for (int i=iFirstTry; (iRetVal == 0 && i <= iLastTry); i++)
	{
		// PROXY SETUP
			const char *pszUseProxyAddress=NULL, *pszUseProxyCredentials=NULL, *pszUseProxyType=NULL;
			if (i == 0)	// first time through, use Proxy settings passed into function
			{	pszUseProxyAddress = pszProxyAddress;
				if (pszProxyCredentials && strlen( pszProxyCredentials ) > 0)
					pszUseProxyCredentials = pszProxyCredentials;
				if (pszProxyType && strlen( pszProxyType ) > 0)
					pszUseProxyType = pszProxyType;
			}
			else if (i > 1)   // i==1 attempts DIRECT connection
			{
	// retrieve default proxy server settings from Windows  ???
			}

			if (iRetVal == 0)
			{	TCHAR lpTempPathBuffer[MAX_PATH];
				DWORD dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer );
				if (dwRetVal > MAX_PATH || (dwRetVal == 0))
				{	iRetVal = 9;
				}
				else
				{	UINT uRetVal = GetTempFileName( lpTempPathBuffer, TEXT("CmpMgrSiteChk"), // temp file name prefix 
																0 /*create unique name*/, szTempFileName );  // buffer for name 
    				if (uRetVal == 0)
					{	iRetVal = 10;
					}
					else
					{	//int ErrorCode = fopen_s( &fp_Out, szTempFileName, "wb" );
						//if (ErrorCode != 0)
						//{	iRetVal = 11;
				}	}	//}
			}

			if (iRetVal == 0)
			{	int iDnldRetVal = surlSiteChk.DownloadFile( pszSite, szTempFileName, pszCACertPath, pszUseProxyAddress, pszUseProxyCredentials, pszUseProxyType,
																			NULL /*pszDataToPost*/, 0 /*iPostDataLen*/, pszErrorMsg, iErrorMsgLen, bVerbose );
				if (iDnldRetVal > 0)
				{	//assert( FALSE );
					iRetVal = iDnldRetVal;
					//switch (iDnldRetVal)
					//{	case  1 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - invalid storage path:  %s", sWthrZipPathFile );					break;
					//	case  2 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - error downloading file:  %s", sWeatherFileDownloadURL );			break;		// this error occurs when NORESCO proxy not able to be negotiated
					//	case  3 :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed - user chose not to overwrite file:  %s  -->>  %s", sWeatherFileDownloadURL, sWthrZipPathFile );		break;
					//	default :	sErrMsg.sprintf( "CMX_SetupAnalysisWeatherPaths() Error:  Hourly simulation weather file download failed:  %s  -->>  %s", sWeatherFileDownloadURL, sWthrZipPathFile );	break;
				}	//}
				else
				{	// download SUCCESS
					iRetVal = (i==0 ? -2 : (i==1 ? -1 : -3));
//		Return Values:	  -1 =>	SUCCESS  (using no proxy server settings)
//							  -2 =>	SUCCESS  (using supplied proxy server settings)
//							  -3 =>	SUCCESS  (using proxy server settings retrieved from operating system)
				}

																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "CheckSiteAccessViaQt()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("back from surlSiteChk.DownloadFile() - Download RetVal: %L1 - Func RetVal: %L2\nTemp File: %3").arg(iDnldRetVal).arg(iRetVal).arg(szTempFileName) );
																//		msgBox.exec();
			}

			if (iRetVal >= 0 && FileExists( szTempFileName ))		// if still looping or errant return code, then DELETE the temp file site status was written to
				DeleteFile( szTempFileName );
	}														if (bVerbose)
																qsVerbose += QString("download loop retval %L1 >> ").arg(iRetVal);

	// CHECK FOR OUTPUT FILE containing 'true' - indicating report gen site up and functioning
	if (iRetVal < 0 && FileExists( szTempFileName ))
	{

																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "CheckSiteAccessViaQt()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("About to open Temp File - Func RetVal: %L1\nTemp File: %2").arg(iRetVal).arg(szTempFileName) );
																//		msgBox.exec();

		FILE* fp_Out = _fsopen( szTempFileName, "rb", _SH_DENYNO /*_SH_DENYWR*/ );
		if (fp_Out==NULL) 
		{ }	//	iRetVal = 19;		//	19 : Error opening output file following report generation
		else
		{	char buff[32];
			int nread = fread( buff, sizeof(char), 20, fp_Out );  // first 20 chars of file should do it...
			if (nread < 4)
			{ }	//	iRetVal = 20;		//	20 : Error reading data from output file following report generation
			else
			{	buff[20] = '\0';
				QString sHdrText = buff;
				sHdrText = sHdrText.toLower();
															if (bVerbose)
																qsVerbose += QString("file starts '%1' >> ").arg(sHdrText);
				if (sHdrText.indexOf("true") >= 0)
				{	iRetVal -= 10;		// adjust retval to reflect 'true' response
				}
			}
			fclose( fp_Out );
		}

																	//	QMessageBox msgBox;
																	//	msgBox.setWindowTitle( "CheckSiteAccessViaQt()" );
																	//	msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("About to delete Temp File: %1").arg(szTempFileName) );
																//		msgBox.exec();

	   DeleteFile( szTempFileName );
	}

	if (iRetVal == 0)
		iRetVal = (iFirstTry==0 ? 8 : 7);
//											 7 : Unable to connect either directly or via proxy server settings retrieved from the operating system
//											 8 : Unable to connect via supplied proxy server settings

//	QString sDbgMsg;	sDbgMsg.sprintf( "CheckSiteAccessViaQt() %s - returning %d.", (iRetVal < 0 ? "SUCCESS" : "Failed"), iRetVal );
//	AfxMessageBox( sDbgMsg );
															if (bVerbose)
															{	qsVerbose += QString("returning %L1").arg(iRetVal);
																int iToAdd = iErrorMsgLen - 1 - strlen( pszErrorMsg );
																strcat_s( pszErrorMsg, iErrorMsgLen, qsVerbose.left(iToAdd).toLocal8Bit() );
															}

	if (bQAppInit)
	{	delete sq_app;
		sq_app = NULL;
	}

	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// SAC 11/5/15 - 
static Qt_URLFile surlRptGen;

int GenerateReportViaQt(	const char* pszOutPathFile, const char* pszURL, const char* pszCACertPath, const char* pszRptData, int iRptDataLen,
									const char* pszProxyAddress, const char* pszProxyCredentials, const char* pszProxyType,		// pass NULLs for no proxy
									char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bVerbose /*=false*/ )
{	int iRetVal = 0;

	bool bQtAppInitHere = false;	// SAC 11/11/15
	if (sq_app == NULL)
	{	assert( sq_app == NULL && sqt_win == NULL && sqt_progress == NULL );
		QCoreApplication* pQCA = QCoreApplication::instance();
		if (pQCA)
			sq_app = (QApplication*) pQCA;
		else
		{	int argc = 0;
			sq_app = new QApplication( argc, NULL );
			bQtAppInitHere = true;
		}
		if (sq_app)
		{	ssEXEPath = sq_app->applicationDirPath();
			ssEXEPath = QDir::cleanPath(ssEXEPath);
			if (ssEXEPath[ssEXEPath.length()-1] != '/' &&
				 ssEXEPath[ssEXEPath.length()-1] != '\\')
				ssEXEPath += '/';  // ensure trailing slash
	}	}

	int iDnldRetVal = surlRptGen.DownloadFile( pszURL, pszOutPathFile, pszCACertPath, pszProxyAddress, pszProxyCredentials, pszProxyType,
																pszRptData, iRptDataLen, pszErrorMsg, iErrorMsgLen, bVerbose );
	if (iDnldRetVal > 0)
	{	assert( FALSE );
		iRetVal = iDnldRetVal;
	}

	if (bQtAppInitHere)
	{	delete sq_app;
		sq_app = NULL;
	}

	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CECRPTGEN

bool CMX_ExtractTitle24ReportFromXML( const char* xmlFileName, const char* pdfFileName, const char* rptElemName /*=NULL*/, BOOL bSupressAllMessageBoxes /*=FALSE*/ )
{	return ParseTitle24ReportXML( xmlFileName, pdfFileName, rptElemName, bSupressAllMessageBoxes );
}

#endif // CECRPTGEN
////////////////////////////////////////////////////////////////////////////////////////////////////










