// CBECC-CLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "CBECC-CLI.h"

#include <stdio.h>
#include <io.h>
#include <direct.h>

#include <QtCore/QDirIterator>

#include "../BEMProc/BEMProc.h"
#include "../BEMProc/BEMProcCompile.h"
#include "../BEMCmpMgr/BEMCmpMgrCom.h"
#include "../BEMCmpMgr/BEMCmpMgrRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// new CLI app to facilitate non-UI access to ruleset compilation and compliance analysis - SAC 10/18/24

// The one and only application object
CWinApp theApp;

using namespace std;
using namespace boost;

#define  CSV_RESULTSLENGTH  3200
static char pszCSVResultSummary[ CSV_RESULTSLENGTH ];

enum CodeType	{	CT_T24N,		CT_S901G,	CT_ECBC,	CT_360,		CT_NumTypes  };

static int ProcessCommandLineArgs( int &iPrimaryFunction, QString &qsBEMTxtFileName, QString &qsEnumsTxtFileName,
                                   QString &qsBEMBinFileName, QStringList &qslAltPaths, QString &qsRuleTxtFileName,
                                   QString &qsRuleBinFileName, QString &qsLogFileName, QString &qsWeatherPath,
                                   QString &qsProcessingPath, QString &qsModelInput, QString &qsOptionsCSV,
                                   QString &qsModelInputPath, QString &qsBatchRunDefsFile );

static BOOL FileExists( const char* pszFileName );
static BOOL OKToWriteOrDeleteFile( const char* pszFileName );  // , const char* pszUserMsg, bool bSilent /*=false*/ )

static BOOL GenerateBatchInput( CString& sBatchDefsPathFile, CString& sBatchLogPathFile, CString& sBatchResultsPathFile, // ported to CBECC-CLI - SAc 02/12/25
                                 QString& qsErrMsg, QString qsLogFileName, QString qsProcessingPath, QString qsOptionsCSV,
                                 QString qsModelInputPath, QString qsBatchRunDefsFile, bool bSFam, long lRunsSpanClimates );

static int ParseCSVRecord( const char* pszParseStr, QVector<QString>* psaCSVFields );      // SAC 11/13/25
static int GetCSVOptionValue( const char* pszOptName, int iDefault, QVector<QString>& saCSVOptions );
static int GetCSVOptionString( const char* pszOptName, QString& sOptString, QVector<QString>& saCSVOptions );
static int StripOutCSVOptions( QString& sRecOptionCSV, QVector<QString>* psaClrOptions, QString sReplace );

static BOOL GetProgramVersion(CString& sProgVer, BOOL bPrependName, BOOL bLongVer);

#define ResSmryColLblLen1  2176
#define ResSmryColLblLen2  4096
#define ResSmryColLblLen3  3328


////////////////////////////////////////////////////////////////////////////////

// return codes:
//    0     - success
//    1     - Fatal Error: MFC initialization failed
//    2     - Fatal Error: GetModuleHandle failed
//    3     - Data model compilation failed
//    4     - Ruleset compilation failed
//    5     - Unrecognized primary function
//    6     - Batch processing error: unable to generate batch input/directives file
//  >1000   - Compliance analysis failed - 1000 + return value from: CMX_PerformAnalysisCB_NonRes()
//  >2000   - Batch processing failed - 2000 + return value from: CMX_PerformBatchAnalysis_CECNonRes()

int main()
{
   int nRetCode = 0;

   HMODULE hModule = ::GetModuleHandle(nullptr);

   if (hModule != nullptr)
   {
      //LPTSTR cmdLine = ::GetCommandLine();

      // initialize MFC and print and error on failure
      if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
      {
         // TODO: code your application's behavior here.
         wprintf(L"Fatal Error: MFC initialization failed\n");
         nRetCode = 1;
      }
      else
      {
         // TODO: code your application's behavior here.

         QString qsBEMTxtFileName, qsEnumsTxtFileName, qsBEMBinFileName, qsProcessingMsg,
                 qsRuleTxtFileName, qsRuleBinFileName, qsLogFileName, qsWeatherPath,
                 qsProcessingPath, qsModelInput, qsOptionsCSV, qsModelInputPath, qsBatchRunDefsFile;
         QStringList qslAltPaths;
         int iPrimaryFunction=0;  // 1:CompileDataModel / 2:CompileRuleset / 3:Compliance / 4:BatchRuns / 5:SFamCompliance / 6:SFamBatchRuns
         ProcessCommandLineArgs( iPrimaryFunction, qsBEMTxtFileName, qsEnumsTxtFileName, qsBEMBinFileName,
                                 qslAltPaths, qsRuleTxtFileName, qsRuleBinFileName, qsLogFileName, qsWeatherPath,
                                 qsProcessingPath, qsModelInput, qsOptionsCSV, qsModelInputPath, qsBatchRunDefsFile );

         printf("    processing...\n");
//         BEMPX_SetAllowWindowsUIFlag( false /*bFlagVal*/ );

         //TCHAR exepath[MAX_PATH+1];
         //std::string sEXEName = (0 == GetModuleFileName(0, exepath, MAX_PATH+1)) ? "CBECC-CLI" : exepath;      // SAC 11/13/25
         //size_t iEXEName_LastSlashIdx = sEXEName.find_last_of( "\\/" );
         //if (iEXEName_LastSlashIdx != std::string::npos && iEXEName_LastSlashIdx < (sEXEName.length()-1))      // SAC 11/14/25
         //   sEXEName = sEXEName.substr( iEXEName_LastSlashIdx+1, sEXEName.length()-iEXEName_LastSlashIdx-1 );
         //size_t iEXEName_LastDotIdx = sEXEName.rfind( '.' );
         //if (iEXEName_LastDotIdx != std::string::npos && iEXEName_LastDotIdx > 0)      // SAC 11/14/25
         //   sEXEName = sEXEName.substr( 0, iEXEName_LastDotIdx );
         CString sProgNameAndVer;
         GetProgramVersion( sProgNameAndVer, TRUE, TRUE );        assert( !sProgNameAndVer.IsEmpty() );

         QVector<QString> saCSVOptions;      // SAC 11/13/25
         if (qsOptionsCSV.length() > 0)
         {  if (ParseCSVRecord( qsOptionsCSV.toLocal8Bit().constData(), &saCSVOptions ) < 2)
            {	assert( false );
         }  }
         long iOptionsCSV_CUACReportID = GetCSVOptionValue( "CUACReportID", 0, saCSVOptions );		// value > 0 -OR- corresponding property specified in project input => doing CUAC analysis & reporting - SAC 11/13/25
         long lRunsSpanClimates = GetCSVOptionValue( "RunsSpanClimates", 0, saCSVOptions );		// value 0/1 - batch processing option (only valid for SFam) - SAC 11/14/25

         switch (iPrimaryFunction)
         {  case  1 : { // Compile Data Model
                        // cbecc-cli22 -CompileDataModel -sharedPath "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/RulesetDev/Rulesets/shared/" -BEMBaseTxt "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/RulesetDev/Rulesets/BEMBase.txt" -BEMEnumsTxt "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/RulesetDev/Rulesets/T24N/T24N_2022 BEMEnums.txt" -BEMBaseBin "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/Rulesets/T24N_2022/T24N_2022 BEMBase.bin"
                        if (!BEMPX_CompileDataModel(  qsBEMTxtFileName.toLocal8Bit().constData(),     //"C:\\CBECC\\SVN\\branches\\CBECC-Com_MFamRestructure\\RulesetDev\\Rulesets\\BEMBase.txt",
                                                      qsEnumsTxtFileName.toLocal8Bit().constData(),   //"C:\\CBECC\\SVN\\branches\\CBECC-Com_MFamRestructure\\RulesetDev\\Rulesets\\T24N\\T24N_2022 BEMEnums.txt",
                                                      qsBEMBinFileName.toLocal8Bit().constData(),     //"C:\\CBECC\\SVN\\branches\\CBECC-Com_MFamRestructure\\CBECC-Com64\\Data\\Rulesets\\T24N_2022\\T24N_2022 BEMBase.bin",
                                                      &qsProcessingMsg, &qslAltPaths ))
                        {  printf("Data model compilation failed  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );
                           nRetCode = 3;
                        }
                        else
                           printf("Data model compilation successful  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );  //  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );
                      } break;
            case  2 : { // Compile Ruleset
                        // cbecc-cli22 -CompileRuleset -sharedPath "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/RulesetDev/Rulesets/shared/" -BEMBaseBin "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/Rulesets/T24N_2022/T24N_2022 BEMBase.bin" -RulesetTxt "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/RulesetDev/Rulesets/T24N/Rules/T24N_2022.txt" -RulesetBin "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/Rulesets/T24N_2022.bin" -LogFile "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/_T24N-2022 Rules Log.out"
                        if (!BEMPX_CompileRuleset( qsBEMBinFileName.toLocal8Bit().constData(),  qsRuleTxtFileName.toLocal8Bit().constData(),
                                                   qsRuleBinFileName.toLocal8Bit().constData(), qsLogFileName.toLocal8Bit().constData(),
                                                   &qsProcessingMsg, &qslAltPaths ))
                        {  printf("Ruleset compilation failed  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );
                           nRetCode = 4;
                        }
                        else
                           printf("Ruleset compilation successful  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );  //  --  %s\n", qsProcessingMsg.toLocal8Bit().constData() );
                      } break;
            case  3 : { // Compliance (NRMF or SFam -and- T24 or CUAC) - SAC 01/19/25
                        QString qsModelExt = qsModelInput.right( qsModelInput.length() - (qsModelInput.lastIndexOf( '.' )+1) );
                        bool bSFamComp = ( qsModelExt[0] == 'r' || qsModelExt[0] == 'R' );
                        char pszAnalysisErr[2056] = "\0";      pszCSVResultSummary[0] = '\0';
                        if (bSFamComp)    // SAC 11/13/25 - cbecc-cli25 -Compliance -BEMBaseBin "C:/CBECC/git-vscode/CBECC-Dev/CBECC/Data/Rulesets/CA Res 2025/CAR25 BEMBase.bin" -RulesetBin "C:/CBECC/git-vscode/CBECC-Dev/CBECC/Data/Rulesets/CA Res 2025.bin" -WeatherPath "C:/CBECC/git-vscode/CBECC-Dev/Weather/2025/" -ProcessingPath "C:/CBECC/test/CBECC-CLI/SFamCompliance/0/1storyExample - run/" -ModelInput "C:/CBECC/test/CBECC-CLI/SFamCompliance/0/1storyExample.ribd25" -OptionsCSV "Silent,1,ReportGenVerbose,1,LogAnalysisMsgs,1,StoreBEMDetails,1,ModelRpt_ALL,1,SimulationStorage,4,AnalysisStorage,3,ExportHourlyResults_All,1,"
                        {
                           int iCompRetVal = CMX_PerformAnalysisCB_CECRes(	qsBEMBinFileName.toLocal8Bit().constData(), qsRuleBinFileName.toLocal8Bit().constData(),
                                       NULL /*pszCSEEXEPath*/, qsWeatherPath.toLocal8Bit().constData(), NULL /*pszDHWDLLPath*/, NULL /*pszDHWWeatherPath*/,
                                       qsProcessingPath.toLocal8Bit().constData(), qsModelInput.toLocal8Bit().constData(), qsLogFileName.toLocal8Bit().constData(), 
                                       sProgNameAndVer, true /*bLoadModelFile*/, qsOptionsCSV.toLocal8Bit().constData(), pszAnalysisErr, 2056, false /*bDisplayProgress*/,
                                       0 /*iSecurityKeyIndex*/, NULL /*pszSecurityKey*/, NULL /*PAnalysisProgressCallbackFunc pAnalProgCallbackFunc*/ );
                           printf("SFam Compliance analysis returned %d\n", iCompRetVal );
                           if (strlen( pszAnalysisErr ) > 0)
                              printf("Error msg:  %s\n", pszAnalysisErr );

                           if (iCompRetVal == 0 || iCompRetVal >= BEMAnal_CECRes_MinErrorWithResults)
                           {  bool bPerformedCUAC = (iOptionsCSV_CUACReportID > 0);
                              long lCUAC_RptOption=0, lDBID_CUAC_RptOption = BEMPX_GetDatabaseID( "CUAC:RptOption" );
                              if (!bPerformedCUAC && lDBID_CUAC_RptOption > 0 && BEMPX_GetInteger( lDBID_CUAC_RptOption, lCUAC_RptOption ) && lCUAC_RptOption > 0)
                                 bPerformedCUAC = true;
                              if (!bPerformedCUAC)   // write to CSV summary only if NOT doing CUAC analysis
                              {
                                 long lAllOrientations;
                              	BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:AllOrientations" ), lAllOrientations ); 
                                 // Populate string w/ summary results of analysis
                        		   if (iCompRetVal == 0 || iCompRetVal >= BEMAnal_CECRes_MinErrorWithResults)
                        		   {
                                    CString sOriginalFileName = qsModelInput.toLocal8Bit().constData();
                                    long lEnergyCodeYear;
                        		   	BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYear );
                        		   	const char* pszOrientation[] = {  NULL,  "N", "E", "S", "W", NULL };
                                    int iAllOrientationsResultsCSV = GetCSVOptionValue( "AllOrientationsResultsCSV", 1 /*default*/, saCSVOptions );
                                    int iMaxCSVOrient = (lAllOrientations > 0 && (iAllOrientationsResultsCSV > 0) ? 4 : 0);
                                                //CString sDbgCSVMsg;    sDbgCSVMsg.Format( "About to populate/write CSV results - AllOrients = %ld, INI AllOrientationsResultsCSV = %d, iMaxCSVOrient = %d", lAllOrientations, iAllOrientationsResultsCSV, iMaxCSVOrient );   AfxMessageBox( sDbgCSVMsg );
                        		   	for (int iO=0; iO<=iMaxCSVOrient; iO++)
                        		   	{	// SAC 08/06/24 - appended 4 cols: PV Exports / Prop & Std / kWh/yr & % - request from CEC (26->27)
                                       // SAC 10/29/25 - major overhaul removing dozens of no-longer-used columns and adding a few more for 2025+ analysis (27->28) (dev #506)
                                       int iResSummaryCSVFormatVer = (lEnergyCodeYear < 2025 ? 27 : 28);    // SAC 10/29/25 (dev #506)
                        		   		//CString sDfltResFN;  // = "AnalysisResults-v27.csv";  // (bHaveCDRs ? "AnalysisResults-v19cdr.csv" : "AnalysisResults-v19.csv");
                                       //sDfltResFN.Format( "AnalysisResults-v%d.csv", iResSummaryCSVFormatVer );
                        		   		int iCSVResVal = CMX_PopulateCSVResultSummary_CECRes(	pszCSVResultSummary, CSV_RESULTSLENGTH, pszOrientation[iO] /*pszRunOrientation*/,
                        		   																				iResSummaryCSVFormatVer, sOriginalFileName );
                        		   		if (iCSVResVal == 0)
                        		   		{
                        		   			char pszCSVColLabel1[ResSmryColLblLen1], pszCSVColLabel2[ResSmryColLblLen2], pszCSVColLabel3[ResSmryColLblLen3];
                        		   			VERIFY( CMX_PopulateResultsHeader_Res( pszCSVColLabel1, ResSmryColLblLen1, pszCSVColLabel2, ResSmryColLblLen2, pszCSVColLabel3, ResSmryColLblLen3, iResSummaryCSVFormatVer ) == 0 );	// SAC 5/10/15
                        		   			const char* szaCSVColLabels[4]	=	{ pszCSVColLabel1, pszCSVColLabel2, pszCSVColLabel3, NULL };
                        		   			CString sCSVResultSummary = pszCSVResultSummary;
                        		   			// WRITE result summary to PROJECT and GENERIC DATA CSV result logs - ALONG WITH COLUMN TITLES (if log doesn't previously exist)
                        		   			QString qsCSVLogFN = BEMPX_GetLogFilename( true );		CString sCSVLogFN = qsCSVLogFN.toLatin1().constData();		ASSERT( !sCSVLogFN.IsEmpty() );

                                          QString qsFullRecord, qsSubst;      // string substitutions to support rule-defined compliance metric labels - SAC 01/31/23
                                          if (lEnergyCodeYear >= 2025 && BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompMetricLbl_Short" ), qsSubst ) && !qsSubst.isEmpty())
                                          {  qsFullRecord = QString( pszCSVColLabel1 ).arg( qsSubst, qsSubst, qsSubst, qsSubst );
                                             strncpy_s( pszCSVColLabel1, qsFullRecord.toLocal8Bit().constData(), ResSmryColLblLen1 );    pszCSVColLabel1[ResSmryColLblLen1-1] = '\0'; 
                                             qsFullRecord = QString( pszCSVColLabel2 ).arg( qsSubst, qsSubst, qsSubst );
                                             strncpy_s( pszCSVColLabel2, qsFullRecord.toLocal8Bit().constData(), ResSmryColLblLen2 );    pszCSVColLabel2[ResSmryColLblLen2-1] = '\0'; 
                                          }

                        		   			if (!sCSVLogFN.IsEmpty())
                        		   			{	//sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
                        		   				//             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                        		   				// 			 "(once the file is closed), or \n'Cancel' to abort the %s.", "CSV results log", (const char*) sCSVLogFN, "writing of results to the file" );
                        		   				if (OKToWriteOrDeleteFile( sCSVLogFN ))   // , sMsg, (!BEMPX_GetUIActiveFlag()) ))
                        		   					VERIFY( BEMPX_WriteLogFile( sCSVResultSummary, NULL, false /*bBlankFile*/, FALSE /*bSupressAllMessageBoxes*/,
                        		   															false /*bAllowCopyOfPreviousLog*/, szaCSVColLabels /*ppCSVColumnLabels*/ ) );
                        		   			}
                        		   			// CString sCSVResultsLogFN = ReadProgString( "files", "CSVResultsLog", sDfltResFN, TRUE /*bGetPath*/ );
                                          // // revise call to AppendToTextFile() to handle primary compliance metric label substitutions - SAC 01/30/23
                        		   			// VERIFY( AppendToTextFile( sCSVResultSummary, sCSVResultsLogFN, "CSV results log", "writing of results to the file", szaCSVColLabels, false, FALSE, 0 ) );  // subst already made above - was: (lEnergyCodeYear >= 2025 ? 1 : 0) ) );
                        		   		}
                        		   		else
                        		   		{	CString sErrResultMsg;		ASSERT( FALSE );
                        		   			sErrResultMsg.Format( "Error encountered retrieving results summary data.  CMX_PopulateCSVResultSummary_CECRes() returned %d.", iCSVResVal );
                        		   			// if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent error messagebox when GUI deactivated
                        		   			// 	AfxMessageBox( sErrResultMsg );
                        		   			// else
                        		   				VERIFY( BEMPX_WriteLogFile( sErrResultMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
                        		   	}	}
                       		   }  }
                           }
                           nRetCode = (iCompRetVal == 0 ? 0 : 1000+iCompRetVal);
                        }
                        else
                        {  // cbecc-cli22 -Compliance -BEMBaseBin "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/Rulesets/T24N_2022/T24N_2022 BEMBase.bin" -RulesetBin "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/Rulesets/T24N_2022.bin" -WeatherPath "C:/CBECC/SVN/branches/CBECC-Com_MFamRestructure/CBECC-Com64/Data/EPW/" -ProcessingPath "C:/CBECC/test/CBECC-CLI/CompAnal/1/020012-OffSml-CECStd - run/" -ModelInput "C:/CBECC/test/CBECC-CLI/CompAnal/1/020012-OffSml-CECStd.cibd22" -OptionsCSV "Silent,1,ReportGenVerbose,1,LogAnalysisMsgs,1,StoreBEMDetails,1,AnalysisThruStep,8,ModelRpt_ALL,1,SimulationStorage,4,AnalysisStorage,3,ExportHourlyResults_All,1,PreAnalysisCheckPromptOption,3,CompReportWarningOption,5,AnalysisDialogTimeout,20,"
//int  BEMCMPMGR_API __cdecl CMX_PerformAnalysisCB_NonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
//												const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath,
//												const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile=true,
//												const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false,
//												char* pszResultsSummary=NULL, int iResultsSummaryLen=0, int iSecurityKeyIndex=0, const char* pszSecurityKey=NULL,		// SAC 5/16/14   // SAC 1/10/17
//												PAnalysisProgressCallbackFunc pAnalProgCallbackFunc=NULL );		// SAC 5/28/15

                           int iCompRetVal = CMX_PerformAnalysisCB_NonRes(	qsBEMBinFileName.toLocal8Bit().constData(), qsRuleBinFileName.toLocal8Bit().constData(),
                                       qsWeatherPath.toLocal8Bit().constData(), NULL, NULL, qsProcessingPath.toLocal8Bit().constData(),
                                       qsModelInput.toLocal8Bit().constData(), qsLogFileName.toLocal8Bit().constData(), 
                                       sProgNameAndVer, true /*bLoadModelFile*/, qsOptionsCSV.toLocal8Bit().constData(),
                                       pszAnalysisErr, 2056, false /*bDisplayProgress*/, pszCSVResultSummary, CSV_RESULTSLENGTH,
                                       0 /*iSecurityKeyIndex*/, NULL /*pszSecurityKey*/, NULL /*PAnalysisProgressCallbackFunc pAnalProgCallbackFunc*/ );
                           printf("NRMF Compliance analysis returned %d\n", iCompRetVal );
                           if (strlen( pszAnalysisErr ) > 0)
                              printf("Error msg:  %s\n", pszAnalysisErr );

                           // Populate string w/ summary results of analysis  - SAC 5/19/14 - added similar to -Res
                           if (iCompRetVal == 0 && strlen( pszCSVResultSummary ) > 0)
                           {
                              int iCodeType = CT_T24N;
                              QString qsCSVLogFN = qsModelInput.left( qsModelInput.lastIndexOf( '.' )+1 );     qsCSVLogFN += "log.csv";
                              CString sCSVLogFN = qsCSVLogFN.toLatin1().constData();      ASSERT( !sCSVLogFN.IsEmpty() );

                              char pszCSVColLabel1[768], pszCSVColLabel2[1280], pszCSVColLabel3[3328];   // SAC 7/20/18 - inc #3 2048->2304 due to truncation   // SAC 6/28/19 - 560 / 968 / 2706 chars   // SAC 11/4/19 - 616 / 1068 / 3019 chars   // SAC 9/17/20 - 704 / 1280 / 3136 chars   // 768/1280/3328 - SAC 10/30/23
                              VERIFY( CMX_PopulateResultsHeader_NonRes( pszCSVColLabel1, 768, pszCSVColLabel2, 1280, pszCSVColLabel3, 3328, iCodeType ) == 0 );   // SAC 12/3/14
                              //if (lEnergyCodeYearNum >= 2025)     // updated TDV units in AnalysisResults column titles from kTDV to $ for 2025+ analysis - SAC 10/25/22
                              //{  int col2strlen = strlen( pszCSVColLabel2 );
                              //   char *pszKTDV = strstr( pszCSVColLabel2, "kTDV" );
                              //   while (pszKTDV != NULL)
                              //   {  int iKTDVpos = pszKTDV - pszCSVColLabel2;    assert( iKTDVpos > 0 );
                              //      pszCSVColLabel2[iKTDVpos] = '$';
                              //      for (int i=iKTDVpos+4; i<col2strlen+2; i++)  // shift right portion of string incl. trailing NULL
                              //         pszCSVColLabel2[i-3] = pszCSVColLabel2[i];
                              //      col2strlen = strlen( pszCSVColLabel2 );
                              //      pszKTDV = strstr( pszCSVColLabel2, "kTDV" );
                              //}  }
                              const char* szaCSVColLabels[4]   =   { pszCSVColLabel1, pszCSVColLabel2, pszCSVColLabel3, NULL };
                              bool bWroteToLogCSV = false;
                              if (!sCSVLogFN.IsEmpty())
                              {  //sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
                                 //             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                                 //             "(once the file is closed), or \n'Cancel' to abort the %s.", "CSV results log", sCSVLogFN, "writing of results to the file" );
                                 if (OKToWriteOrDeleteFile( sCSVLogFN ))   // , sMsg, (!BEMPX_GetUIActiveFlag()) ))
                                 {   VERIFY( BEMPX_WriteLogFile( pszCSVResultSummary, (const char*) sCSVLogFN /*NULL*/, false /*bBlankFile*/, FALSE /*bSupressAllMessageBoxes*/,
                                                                  false /*bAllowCopyOfPreviousLog*/, szaCSVColLabels /*ppCSVColumnLabels*/ ) );
                                    bWroteToLogCSV = true;
                              }   }

                              //long lCustomMeterOption=0;    // SAC 11/06/23
                              //BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CustomMeterOption" ), lCustomMeterOption, -1 );
                              //if (lCustomMeterOption > 0)
                              //{  CString sCustMtrCSVLogFN = sCSVLogFN;
                              //   sCustMtrCSVLogFN.Insert( sCSVLogFN.GetLength()-8, "-CustomMeter" );
                              //   sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
                              //                "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
                              //                "(once the file is closed), or \n'Cancel' to abort the %s.", "CustomMeter CSV results log", sCustMtrCSVLogFN, "writing of results to the file" );
                              //   if (OKToWriteOrDeleteFile( sCustMtrCSVLogFN, sMsg, (!BEMPX_GetUIActiveFlag()) ))
                              //   {  int iWriteCustomMeterCSVRetVal = CMX_WriteCustomMeterCSVResultSummary_NonRes( sCustMtrCSVLogFN, sCurrentFileName );
                              //      if (iWriteCustomMeterCSVRetVal != 0)
                              //      {   assert( FALSE );  // error writing CustomMeter CSV export
                              //   }  }
                              //}

                              //// export CSV results for subsequent results sets (when multiple EUseSummary objects present)
                              //int iCSVRetVal = 0;
                              //long lNumResultsSets=0;
                              //BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:NumResultsSets" ), lNumResultsSets );      // SAC 11/04/19
                              //// check for consistency between lNumResultsSets & number of EUseSummary objects??
                              //for (int iResSet = 1; (iResSet < lNumResultsSets && iCSVRetVal < 1); iResSet++)
                              //{   iCSVRetVal = CMX_PopulateCSVResultSummary_NonRes(   pszCSVResultSummary, CSV_RESULTSLENGTH, sCurrentFileName, sWthrPath, iResSet );      // SAC 11/04/19
                              //   if (iCSVRetVal < 1)
                              //   {   VERIFY( AppendToTextFile( pszCSVResultSummary, sCSVResultsLogFN, "CSV results log", "writing of results to the file", szaCSVColLabels ) );
                              //      if (bWroteToLogCSV)
                              //         VERIFY( BEMPX_WriteLogFile( pszCSVResultSummary, NULL, false /*bBlankFile*/, FALSE /*bSupressAllMessageBoxes*/,
                              //                                    false /*bAllowCopyOfPreviousLog*/, szaCSVColLabels /*ppCSVColumnLabels*/ ) );
                              //}   }
                           }

                           nRetCode = (iCompRetVal == 0 ? 0 : 1000+iCompRetVal);
                        }
                      } break;

            case  4 :   // BatchRuns            - SAC 02/12/25
            case  5 : { // SFamBatchRuns        - SAC 11/14/25
                              // scenarios
                              //    - (default) qsModelInputPath is path to input project files / qsModelInput & qsBatchRunDefsFile empty / qsProcessingPath optional
                              //                      processes all files in dir/subdirs of qsModelInputPath - output to same dir or qsProcessingPath if specified
                              //    - qsBatchRunDefsFile specified / qsModelInputPath is path to input project files / qsModelInput empty / qsProcessingPath optional
                              //                      processes all files in dir/subdirs of qsModelInputPath BASED ON qsBatchRunDefsFile contents - output to same dir or qsProcessingPath if specified
                              //    - qsModelInput specified / qsModelInputPath, qsBatchRunDefsFile & qsProcessingPath empty/unused
                              //                      processes all files based on contents of qsModelInput (an old-style batch CSV file)
                        CString sBatchPathFile, sBatchLogPathFile, sBatchResultsPathFile;      QString qsErrMsg;
                        bool bSFam = (iPrimaryFunction == 5);
                        if ( !GenerateBatchInput( sBatchPathFile, sBatchLogPathFile, sBatchResultsPathFile, qsErrMsg, qsLogFileName,
                                                  qsProcessingPath, qsOptionsCSV, qsModelInputPath, qsBatchRunDefsFile, bSFam, lRunsSpanClimates ) ||
                             sBatchPathFile.IsEmpty() || !FileExists( sBatchPathFile ) )
                        {  nRetCode = 6;
                           printf("Error generating %s batch input/directives file\n", (bSFam ? "SFam" : "NRMF") );
                           if (!qsErrMsg.isEmpty())
                           {  qsErrMsg += "\n";
                              printf( qsErrMsg.toLatin1().constData() );
                        }  }
                        else
                        {
                            	CString sBEMPathFile  = qsBEMBinFileName.toLatin1().constData();       // ReadProgString( "files", "BEMFile", "", TRUE );
                              CString sRulePathFile = qsRuleBinFileName.toLatin1().constData();      // ReadProgString( "paths", "RulesetPath", "", TRUE );
                              //sRulePathFile += ReadProgString( "files", "RulesetFile", "" );
                              char pszBatchErr[1024];
                              pszBatchErr[0] = '\0';
                              char pszBatchReturn[128];
                              pszBatchReturn[0] = '\0';
                     
                              //CString sUIVersionString = "CBECC-CLI";
                              //GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );
                     
                              //long lEnergyCodeYearNum=0;
                              //BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum" ), lEnergyCodeYearNum );      // SAC 10/24/22
                              //CString sDefaultEPWSubdir = (lEnergyCodeYearNum == 2025 ? "EPW25\\" : "EPW\\" );    // SAC 10/24/22
                              CString sWthrPath = qsWeatherPath.toLatin1().constData();      // ReadProgString( "paths", "WeatherPath", sDefaultEPWSubdir /*"EPW\\"*/, TRUE );
                              //// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
                              //VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString, true /*bBatchMode*/ ) );		// SAC 1/29/14
                              CString sOptionsCSVString = qsOptionsCSV.toLatin1().constData();
                     
                              //int iCEDAUD = ReadProgInt( "options", "ClassifyEditableDefaultsAsUserData", 0 );		// SAC 2/21/20
                              //if (iCEDAUD > 0)
                              //{	sTemp.Format( "ClassifyEditableDefaultsAsUserData,%d,", iCEDAUD );		sOptionsCSVString += sTemp;
                              //}
                     
                              //const char* pszAnalOpts = NULL;
                              //if (!sOptionsCSVString.IsEmpty())
                              //   pszAnalOpts = (const char*) sOptionsCSVString;
                     
                              //PreventSystemSleepDuringAnalysis();			// SAC 10/21/20 - setup timer to prevent system sleep during analysis
                              // To prevent your Windows system from going to sleep while executing a command line interface (CLI) command, you can use the "powercfg" command in the command prompt to set the sleep settings to "Never" within the power plan you are currently using. 

                              int iBatchResult=0;
                              if (bSFam)
                                 iBatchResult = CMX_PerformBatchAnalysis_CECRes( sBatchPathFile, qsModelInputPath.toLatin1().constData() /*esProjectsPath*/, sBEMPathFile, sRulePathFile,
                                                         NULL /*sCSEPath*/, sWthrPath /*sCSEPath*/, NULL /*sT24DHWPath*/, NULL /*pszDHWWeatherPath*/, sBatchLogPathFile /*pszLogPathFile*/,
                                                         sProgNameAndVer, sOptionsCSVString, pszBatchErr, 1024, false /*bDisplayProgress*/,
                                                         NULL /*HWND hWnd*/, 1 /*SecKeyIndex*/, NULL /*esResSecurityKey*/, pszBatchReturn, 128, NULL /*sProxyINIOptions*/, true /*bSilent*/ );  // separate out Proxy settings since can't communicate these via CSV file (nested quoted strings) - SAC 10/09/21
                              else
                                 iBatchResult = CMX_PerformBatchAnalysis_CECNonRes(	sBatchPathFile, qsModelInputPath.toLatin1().constData() /*esProjectsPath*/, sBEMPathFile, sRulePathFile,
                                                                              sWthrPath /*pszSimWeatherPath*/, NULL /*pszCompMgrDLLPath*/, NULL /*pszDHWWeatherPath*/,
                                                                           //	sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
                                                                              NULL /*pszLogPathFile*/, sProgNameAndVer, sOptionsCSVString, pszBatchErr, 1024,
                                                                              false /*bDisplayProgress*/, NULL /*GetSafeHwnd()*/ /*HWND hWnd*/, false /*bOLDRules*/, 1 /*SecKeyIndex*/, NULL /*esSecurityKey*/,
                                                                              pszBatchReturn, 128, NULL /*sProxyINIOptions*/, true /*bSilent*/ );     // added bSilent - SAC 02/13/25

                              //RestoreSystemSleepFollowingAnalysis();		// SAC 10/21/20 - kill timer used to prevent system sleep during analysis
                              CString sResult;
                              if (strlen( pszBatchErr ) > 0)
                                 sResult.Format( "%s Batch processing routine returned %d:\n   %s\n", (bSFam ? "SFam" : "NRMF"), iBatchResult, pszBatchErr );
                              else if (iBatchResult == 0)
                              {	if (strlen( pszBatchReturn ) > 0)
                                    sResult.Format( "%s Batch processing successful:\n   %s\n", (bSFam ? "SFam" : "NRMF"), pszBatchReturn );
                                 else
                                    sResult.Format( "%s Batch processing successful.\n", (bSFam ? "SFam" : "NRMF") );
                              }
                              else
                              {	if (strlen( pszBatchReturn ) > 0)
                                    sResult.Format( "%s Batch processing routine returned error code %d:\n   %s\n", (bSFam ? "SFam" : "NRMF"), iBatchResult, pszBatchReturn );
                                 else
                                    sResult.Format( "%s Batch processing routine returned error code %d.\n", (bSFam ? "SFam" : "NRMF"), iBatchResult );
                              }
                              //BOOL bHaveLogOutput = (!sBatchLogPathFile.IsEmpty() && FileExists( sBatchLogPathFile ));
                              //BOOL bHaveResOutput = (!sBatchResultsPathFile.IsEmpty() && FileExists( sBatchResultsPathFile ));
                              nRetCode = (iBatchResult == 0 ? 0 : 2000+iBatchResult);
                              printf( sResult );
                        }
                      } break;

            default :   nRetCode = 5;
                        printf("Unrecognized primary function\n" );

         }


//                  FILE *fp_test;  int iTestErrorCode;
//                  try
//                  {
//#ifdef _DEBUG
//                     iTestErrorCode = fopen_s( &fp_test, "C:\\dev\\CBECC-VS19\\bin\\Debug_VC142x64\\CBECC-CLI22-out.txt", "w" );
//#else
//                     iTestErrorCode = fopen_s( &fp_test, "C:\\CBECC\\SVN\branches\\CBECC-Com_MFamRestructure\\CBECC-Com64\\CBECC-CLI22-out.txt", "w" );
//#endif
//                     fprintf( fp_test, "Test Output...\n" );
//                     fprintf( fp_test, "   next line...\n" );
//                     fflush(  fp_test );
//                     fclose(  fp_test );
//                  }
//                  catch(const std::exception& e)
//                  {
//                     std::cerr << e.what() << '\n';
//                  }
                  

      }
   }
   else
   {
      // TODO: change error code to suit your needs
      printf("Fatal Error: GetModuleHandle failed\n");
      nRetCode = 2;
   }

   return nRetCode;
}



static void get_command_line_args( int * argc, char *** argv );

// enable command line processing and expand analysis to include both data model and ruleset compilation - SAC 10/19/24
int ProcessCommandLineArgs( int &iPrimaryFunction, QString &qsBEMTxtFileName, QString &qsEnumsTxtFileName,
                                 QString &qsBEMBinFileName, QStringList &qslAltPaths, QString &qsRuleTxtFileName,
                                 QString &qsRuleBinFileName, QString &qsLogFileName, QString &qsWeatherPath,
                                 QString &qsProcessingPath, QString &qsModelInput, QString &qsOptionsCSV, 
                                 QString &qsModelInputPath, QString &qsBatchRunDefsFile )
{  int iNumArgs = 0;

         //wprintf(L"command line:  %hs\n", cmdLine );
         int     argc;
         char ** argv;
         get_command_line_args( &argc, &argv );
         for (int n = 1;  n < argc;  n++)
         {  int iArgsToPrint = 1;
            if (     boost::iequals( argv[n], "-CompileDataModel" ))
               iPrimaryFunction = 1;
            else if (boost::iequals( argv[n], "-CompileRuleset" ))
               iPrimaryFunction = 2;
            else if (boost::iequals( argv[n], "-Compliance" ))
               iPrimaryFunction = 3;
            else if (boost::iequals( argv[n], "-BatchRuns" ))     // SAC 02/12/25
               iPrimaryFunction = 4;
            //else if (boost::iequals( argv[n], "-CUAC" ))
            //   iPrimaryFunction = 5;
            else if (boost::iequals( argv[n], "-SFamBatchRuns" ))
               iPrimaryFunction = 5;
            else if (boost::iequals( argv[n], "-sharedPath" ) && n < (argc-1))
            {  qslAltPaths.append( argv[n+1] );                iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-BEMBaseTxt" ) && n < (argc-1))
            {  qsBEMTxtFileName = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-BEMEnumsTxt" ) && n < (argc-1))
            {  qsEnumsTxtFileName = argv[n+1];                 iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-BEMBaseBin" ) && n < (argc-1))
            {  qsBEMBinFileName = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-RulesetTxt" ) && n < (argc-1))
            {  qsRuleTxtFileName = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-RulesetBin" ) && n < (argc-1))
            {  qsRuleBinFileName = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-LogFile" ) && n < (argc-1))
            {  qsLogFileName = argv[n+1];                       iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-WeatherPath" ) && n < (argc-1))
            {  qsWeatherPath = argv[n+1];                      iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-ProcessingPath" ) && n < (argc-1))
            {  qsProcessingPath = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-ModelInput" ) && n < (argc-1))
            {  qsModelInput = argv[n+1];                       iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-OptionsCSV" ) && n < (argc-1))
            {  qsOptionsCSV = argv[n+1];                       iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-ModelInputPath" ) && n < (argc-1))     // for BatchRuns - SAC 02/12/25
            {  qsModelInputPath = argv[n+1];                   iArgsToPrint = 2;
            }
            else if (boost::iequals( argv[n], "-BatchRunDefs" ) && n < (argc-1))       // for BatchRuns - SAC 02/12/25
            {  qsBatchRunDefsFile = argv[n+1];                 iArgsToPrint = 2;
            }
            else
               iArgsToPrint = 0;

            if (iArgsToPrint == 1)
            {  printf( "  %d : %s\n", n, argv[n] );   iNumArgs++;
            }
            else if (iArgsToPrint == 2)
            {  printf( "  %d-%d : %s = %s\n", n, n+1, argv[n], argv[n+1] );      iNumArgs++;  n++;
            }
            else
               printf( "  %d : %s   (--unrecognized--)\n", n, argv[n] );
         }

         free( argv );

   return iNumArgs;
}


void get_command_line_args( int * argc, char *** argv )
{
  // Get the command line arguments as wchar_t strings
  wchar_t ** wargv = CommandLineToArgvW( GetCommandLineW(), argc );
  if (!wargv) { *argc = 0; *argv = NULL; return; }
  
  // Count the number of bytes necessary to store the UTF-8 versions of those strings
  int n = 0;
  for (int i = 0;  i < *argc;  i++)
    n += WideCharToMultiByte( CP_UTF8, 0, wargv[i], -1, NULL, 0, NULL, NULL ) + 1;
  
  // Allocate the argv[] array + all the UTF-8 strings
  *argv = (char**) malloc( (*argc + 1) * sizeof(char *) + n );
  if (!*argv) { *argc = 0; return; }
  
  // Convert all wargv[] --> argv[]
  char * arg = (char *)&((*argv)[*argc + 1]);
  for (int i = 0;  i < *argc;  i++)
  {
    (*argv)[i] = arg;
    arg += WideCharToMultiByte( CP_UTF8, 0, wargv[i], -1, arg, n, NULL, NULL ) + 1;
  }
  (*argv)[*argc] = NULL;
}



BOOL FileExists( const char* pszFileName )
{  LPCTSTR lpPath = TEXT(pszFileName);
   return (PathFileExists( lpPath ) != FALSE);
}

BOOL DirectoryExists( const char* pszDirName )
{  DWORD dwAttrib = GetFileAttributes(pszDirName);
   return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
          (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL OKToWriteOrDeleteFile( const char* pszFileName )  // , const char* pszUserMsg, bool bSilent /*=false*/ )
{
   BOOL bRetVal = (!FileExists( pszFileName ));  // if file doesn't yet exist -> return TRUE

   BOOL bAbort = FALSE;
   while (!bRetVal && !bAbort)
   {
      if (!FileExists( pszFileName ))  // SAC 8/17/06
         bRetVal = TRUE;  // user deleted or renamed file since last check -> return TRUE
      else
      {
               //AfxMessageBox( "About to try opening file..." );
         //FILE *pfTempFile = fopen( pszFileName, "r+" );
         //if (pfTempFile != NULL)
         //{
         //      //AfxMessageBox( "File opened OK." );
         //   fclose( pfTempFile );
         //   bRetVal = TRUE;
         //}
         // replaced above w/ following to address compiler complaint - SAC 11/19/25
         FILE *pfTempFile = NULL;
         int iFileErrorCode=0;
         try
         {  iFileErrorCode = fopen_s( &pfTempFile, pszFileName, "r+" );
            if (iFileErrorCode == 0)
            {
               fclose( pfTempFile );
               bRetVal = TRUE;
            }
         }
         catch(const std::exception& e)
         {
            std::cerr << e.what() << '\n';
            //BEMPX_WriteLogFile( QString("   file exception thrown"), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
         }

			//if (bSilent)
			   bAbort = TRUE;
         //if (!bRetVal)
         //{
         //   // CString sMsg = "The ";
         //   // sMsg += szFileDescription;
         //   // sMsg += " file '";
         //   // sMsg += sFileName;
         //   // sMsg += "' is opened in another application.  This file must be closed in that application before an updated file can be written.";
         //   // sMsg += "\n\nSelect 'Retry' to update the file (once the file is closed), or \n'Cancel' to abort the file writing process.";
         //   // bAbort = (AfxMessageBox( sMsg, MB_RETRYCANCEL | MB_ICONSTOP ) == IDCANCEL);
         //   bAbort = (AfxMessageBox( pszUserMsg, MB_RETRYCANCEL | MB_ICONSTOP ) == IDCANCEL);
         //}
      }
   }

   return bRetVal;
}

void CreateAndChangeDirectory( const char* pszDirName, BOOL bRemoveDir /*=FALSE*/ )  // SAC 2/12/07 - added argument to facilitate directory deletion
{
   CString mtrDir = pszDirName;
   if(mtrDir.GetLength() != 0)
   {
      CString drive;
      CString dir;

      //_splitpath( (const char *) mtrDir, drive.GetBuffer( _MAX_DRIVE ), dir.GetBuffer( _MAX_DIR ), NULL, NULL );
      _splitpath_s( (const char *) mtrDir, drive.GetBuffer( _MAX_DRIVE ), _MAX_DRIVE, dir.GetBuffer( _MAX_DIR ), _MAX_DIR, NULL, 0, NULL, 0 );
      drive.ReleaseBuffer();
      dir.ReleaseBuffer();

		BOOL bDriveOK = drive.IsEmpty();		// SAC 9/2/14 - modified code the ALLOW for drive to be blank (network drive paths)
      if (!bDriveOK)
      {
         int nDrive = drive[0] - ( (drive[0] <= 'Z') ? 'A' : 'a' ) + 1;			ASSERT( nDrive > 0 && nDrive < 27 );
         if (_chdrive( nDrive ) == 0)
				bDriveOK = TRUE;
		}
      if (bDriveOK && dir.GetLength() > 0)
      {
         int nChars = dir.GetLength();
         if ( (nChars > 1) && (dir[ nChars-1 ] == '\\') )
            nChars--;

         if (bRemoveDir && DirectoryExists( dir ))   // SAC 2/12/07 - added code to facilitate directory deletion
         {
            if (_rmdir( dir.Left(nChars).GetBuffer(0) ) != 0)
            {
               CString sMsg;
               sMsg.Format( "Error removing directory: %s", pszDirName );
               //AfxMessageBox( sMsg );
               printf( sMsg );
            }
            dir.ReleaseBuffer();
         }
         else if (!bRemoveDir)
         {
            if (!DirectoryExists( dir ))
            {  // SAC 9/8/01 - Note:  the following call is capable of making only ONE new directory (per call)
               if (_mkdir( dir.Left(nChars).GetBuffer(0) ) != 0)
               {
                  CString sMsg;
                  sMsg.Format( "Error creating directory: %s", pszDirName );
                  //AfxMessageBox( sMsg );
                  printf( sMsg );
               }
               dir.ReleaseBuffer();
            }

            _chdir( dir.Left(nChars).GetBuffer(0) );
            dir.ReleaseBuffer();
         }
      }
   }
}

// SAC 10/16/20 - based on BEMCmpMgr -- SAC 5/22/13 - Based on BEMTextIO::ParseCSVRecord()  // ported to CBECC-CLI - SAC 02/13/25
int ParseCSVRecord( const char* pszParseStr, CStringArray& saCSVFields )
{	int iRetVal = 0;
	int iParseLen = (int) strlen( pszParseStr );			assert( iParseLen > 0 );
	if (iParseLen > 0)
	{	CString string;
		saCSVFields.RemoveAll();
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
					if (!string.IsEmpty())
					{	assert( FALSE );		// string should be empty if/when we encounter an opening quote
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
				{	assert( FALSE );	// quote found after end of quoted field but before following delimiter!!!
				}
			}
   		else if (chr == ',')
			{	if (bQuoteOpen && !bQuoteClosed)
					string += chr;		// delimeter included in quoted string...
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
				{	assert( FALSE );			// invalid condition where:  !bQuoteOpen && bQuoteClosed
				}
			}
			else if (bQuoteOpen && bQuoteClosed)
			{	assert( chr == ' ' );		// allow for space chars to follow a quoted string (and preceding a delimeter or EOL)??
			}
			else
				string += chr;		// add character to string...
		}

		if (!string.IsEmpty())	// add trailing field (numeric, not followed by comma)
			saCSVFields.Add( string );

		iRetVal = (saCSVFields.GetSize() > 0 ? saCSVFields.GetSize() : 0);
	}
	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Batch Processing routines
////////////////////////////////////////////////////////////////////////////////

long ParseBatchRunSetDescription( CString &sRunSetPathFile, QString qsModelInputPath, QString qsBatchRunDefsFile )     // SAC 10/07/20   // ported into CBECC-CLI - SAC 02/13/25
{  long lRSFStatus=-1;
	//if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "BatchRuns:RunSetFileStatus" ), lRSFStatus, -1 ) || lRSFStatus < 0)
   //{
	CString sRunSetFile, sRunSetFileDescrip;		//int iSV, iErr;    
   sRunSetFile = qsBatchRunDefsFile.toLatin1().constData();
	if (/*!BEMPX_SetDataString( BEMPX_GetDatabaseID( "BatchRuns:RunSetFile" ), sRunSetFile ) ||*/ sRunSetFile.IsEmpty())
      lRSFStatus = 0;   // RunSetFile not set
   else
   {  sRunSetPathFile = sRunSetFile;
      if (sRunSetPathFile.Find(':') < 1 && sRunSetPathFile[0] != '\\' && sRunSetPathFile[0] != '/')
      {  // sRunSetFile excludes path, so look for it in expected places
         //CString sINIPath = ReadProgString( "paths", "ProjectsPath", "", TRUE );
         //if (!sINIPath.IsEmpty())
         //   sRunSetPathFile = sINIPath + CString( "BatchRunSets\\" ) + sRunSetFile;
         sRunSetPathFile  = qsModelInputPath.toLatin1().constData();
         sRunSetPathFile += qsBatchRunDefsFile.toLatin1().constData();
         //if (!FileExists( sRunSetPathFile ))
         //{  if (BEMPX_SetDataString( BEMPX_GetDatabaseID( "BatchRuns:FullProjDirectory" ), sINIPath ) && !sINIPath.IsEmpty())
         //      sRunSetPathFile = sINIPath + sRunSetFile;
         //}
      }

      if (!FileExists( sRunSetPathFile ))
         lRSFStatus = 1;   // RunSetFile not found
      else
      {	CStdioFile inFile;
			if (inFile.Open( sRunSetPathFile, CFile::modeRead ) == 0)
         {  lRSFStatus = 2;   // RunSetFile invalid
            sRunSetFileDescrip.Format( "Error opening RunSet definitions file:  %s", sRunSetPathFile );
         }
         else
         {	CString str;
				int i=0, iFormatVer=0, iComma;
				while (++i < 200 && lRSFStatus < 2)
				{	inFile.ReadString( str );
               if (str.IsEmpty() || str[0] == ';' || (str[0] == '\"' && str[1] == ';'))
               {  // skip to next line
               }
               else if (iFormatVer < 1)
               {  iComma = str.Find( ',' );
                  if (iComma > 0)
                     str = str.Left(iComma);
                  iFormatVer = atoi( (const char*) str );
                  if (iFormatVer > 0)
                  {  // skip to next line
                  }
                  else
                  {  lRSFStatus = 2;   // RunSetFile invalid
                     sRunSetFileDescrip.Format( "Error:  invalid RunSet definitions file Format Version #:  %s", str );
               }  }
               else
               {  if (str[0] == '\"')
                  {  str = str.Right( str.GetLength()-1 );
                     iComma = str.Find( '\"' );
                     if (iComma > 0)
                        str = str.Left(iComma);
                  }
                  else
                  {  iComma = str.Find( ',' );
                     if (iComma > 0)
                        str = str.Left(iComma);
                  }
                  if (str.IsEmpty())
                  {  lRSFStatus = 2;   // RunSetFile invalid
                     sRunSetFileDescrip.Format( "Error:  RunSet description not found" );
                  }
                  else
                  {  lRSFStatus = 3;   // RunSetFile OK
                     sRunSetFileDescrip = str;
               }  }
            }  // end of While loop
            if (i >= 200 || lRSFStatus == 0)
            {  lRSFStatus = 2;   // RunSetFile invalid
               sRunSetFileDescrip.Format( "Error:  RunSet description not found" );
            }
         }
      }
   }
	//BEMPX_SetBEMData( BEMPX_GetDatabaseID( "BatchRuns:RunSetFileStatus" ), BEMP_Int,
	//	   					(void*) &lRSFStatus, BEMO_User, -1, BEMS_ProgDefault );
  	//BEMPX_SetBEMData( BEMPX_GetDatabaseID( "BatchRuns:RunSetDescrip" ), BEMP_Str,
	//	   					(void*) ((const char*) sRunSetFileDescrip), BEMO_User, -1, BEMS_ProgDefault );
   //}
   return lRSFStatus;
}

//#ifdef UI_CARES
//static int siBatchDefsFileVer = 2;		// SAC 10/28/20 - 1->2
////static const char* pszBatchDefsColLabel1 = ";   1,2,3,4,5,6,7,8,9,10,11,12\n";
//static const char* pszBatchDefsColLabel2  = "; Process,Existing,New or Save As,,,,,,Multiple,Front,PV Sys,Battery,Target,";
//static const char* pszBatchDefsColLabel22 = "Program,Processing\n";
//static const char* pszBatchDefsColLabel3  = "; Record,File Name,File Name,Run Title,Climate Zone,Analysis Type,Standards Ver,Sim Report File,Orientation,Orientation,Size,Size,EDR,";
//static const char* pszBatchDefsColLabel32 = "Output,Options\n";
//static const char* pszCZs[] = {  "CZ1  (Arcata)", "CZ2  (Santa Rosa)", "CZ3  (Oakland)", "CZ4  (San Jose)", "CZ5  (Santa Maria)", "CZ6  (Torrance)", "CZ7  (San Diego)", "CZ8  (Fullerton)",
//											"CZ9  (Burbank)", "CZ10  (Riverside)", "CZ11  (Red Bluff)", "CZ12  (Sacramento)", "CZ13  (Fresno)", "CZ14  (Palmdale)", "CZ15  (Palm Springs)", "CZ16  (Blue Canyon)" };
//#elif UI_CANRES
//static int siBatchDefsFileVer = 3;
//static const char* pszBatchDefsColLabel1 = ";   1,2,3,4,5,6,7,8,9,10,11\n";
//static const char* pszBatchDefsColLabel2  = "; Process,Existing,New or Save As,Path to Copy,Path to Copy,,";
//static const char* pszBatchDefsColLabel22 = "Override AutoSize Flag,,,Program,Processing\n";
//static const char* pszBatchDefsColLabel3  = "; Record,Project or File Name (full path or relative to \\Projects),Project or File Name,SDD XML files to,CSE files to,Run Title,";
//static const char* pszBatchDefsColLabel32 = "p,bz,b,Output,Options\n";
//static const char* pszCZs[] = {  "ClimateZone1", "ClimateZone2", "ClimateZone3", "ClimateZone4", "ClimateZone5", "ClimateZone6", "ClimateZone7", "ClimateZone8",
//											"ClimateZone9", "ClimateZone10", "ClimateZone11", "ClimateZone12", "ClimateZone13", "ClimateZone14", "ClimateZone15", "ClimateZone16" };
//#endif

BOOL GenerateBatchInput( CString& sBatchDefsPathFile, CString& sBatchLogPathFile, CString& sBatchResultsPathFile,  	// SAC 11/10/17  // ported to CBECC-CLI - SAc 02/12/25
                           QString& qsErrMsg, QString qsLogFileName, QString qsProcessingPath, QString qsOptionsCSV,
                           QString qsModelInputPath, QString qsBatchRunDefsFile, bool bSFam, long lRunsSpanClimates )      // added bSFam - SAC 11/14/25
{  int iBatchDefsFileVer=0;
   std::string sBatchDefsColLabel2, sBatchDefsColLabel22, sBatchDefsColLabel3, sBatchDefsColLabel32, sCZs[16];
   if (bSFam)         // single Res/Com app - SAC 08/31/25 (gh dev #433)
   {  iBatchDefsFileVer = 2;
      sBatchDefsColLabel2  = "; Process,Existing,New or Save As,,,,,,Multiple,Front,PV Sys,Battery,Target,";
      sBatchDefsColLabel22 = "Program,Processing\n";
      sBatchDefsColLabel3  = "; Record,File Name,File Name,Run Title,Climate Zone,Analysis Type,Standards Ver,Sim Report File,Orientation,Orientation,Size,Size,EDR,";
      sBatchDefsColLabel32 = "Output,Options\n";
      sCZs[0] = "CZ1  (Arcata)";    sCZs[1] = "CZ2  (Santa Rosa)";  sCZs[2] = "CZ3  (Oakland)";    sCZs[3] = "CZ4  (San Jose)";  sCZs[4] = "CZ5  (Santa Maria)";
      sCZs[5] = "CZ6  (Torrance)";  sCZs[6] = "CZ7  (San Diego)";   sCZs[7] = "CZ8  (Fullerton)";  sCZs[8] = "CZ9  (Burbank)";   sCZs[9] = "CZ10  (Riverside)";  
      sCZs[10] = "CZ11  (Red Bluff)";  sCZs[11] = "CZ12  (Sacramento)";  sCZs[12] = "CZ13  (Fresno)";  sCZs[13] = "CZ14  (Palmdale)";  sCZs[14] = "CZ15  (Palm Springs)";  sCZs[15] = "CZ16  (Blue Canyon)";
   }
   else // if (ebUI_CANRES)
   {  iBatchDefsFileVer = 3;
      sBatchDefsColLabel2  = "; Process,Existing,New or Save As,Path to Copy,Path to Copy,,";
      sBatchDefsColLabel22 = "Override AutoSize Flag,,,Program,Processing\n";
      sBatchDefsColLabel3  = "; Record,Project or File Name (full path or relative to \\Projects),Project or File Name,SDD XML files to,CSE files to,Run Title,";
      sBatchDefsColLabel32 = "p,bz,b,Output,Options\n";
      sCZs[0] = "ClimateZone1";  sCZs[1] = "ClimateZone2";  sCZs[2] = "ClimateZone3";  sCZs[3] = "ClimateZone4";  sCZs[4] = "ClimateZone5";
      sCZs[5] = "ClimateZone6";  sCZs[6] = "ClimateZone7";  sCZs[7] = "ClimateZone8";  sCZs[8] = "ClimateZone9";  sCZs[9] = "ClimateZone10";
      sCZs[10] = "ClimateZone11";  sCZs[11] = "ClimateZone12";  sCZs[12] = "ClimateZone13";  sCZs[13] = "ClimateZone14";  sCZs[14] = "ClimateZone15";  sCZs[15] = "ClimateZone16";
   }

   qsErrMsg.clear();
//#if defined(UI_CARES) || defined(UI_CANRES)
	if (FALSE)  // !BatchUIDefaulting())
		qsErrMsg = "Error performing batch defaulting.";
	else
	{	//int iSV, iErr;
		long lNumProjInputs = 1;  // BEMPX_GetInteger( BEMPX_GetDatabaseID( "BatchRuns:NumProjInputs" ), iSV, iErr );
		if (lNumProjInputs < 1)
			qsErrMsg = "No batch runs identified.";
		else
		{	BOOL bIsUIActive = (FALSE /*BEMPX_GetUIActiveFlag()*/);		CString sFileMsg;		QString qsFileDescrip;
			long lStoreProjToSepDir = (!qsProcessingPath.isEmpty() ? 1 : 0);     // BEMPX_GetInteger( elDBID_BatchRuns_StoreProjToSepDir, iSV, iErr );
			// long lRunsSpanClimates  = 0;                                         // BEMPX_GetInteger( elDBID_BatchRuns_RunsSpanClimates , iSV, iErr );    // SAC 1/4/19   - now an argument - SAC 11/14/25
			QString qsOutputLogFN   = qsLogFileName;                             // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:LogFileName"       ), iSV, iErr );
			QString qsFullProjDir   = qsModelInputPath;                          // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:FullProjDirectory" ), iSV, iErr );
			QString qsOutputProjDir;                                             // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:FullOutputProjDir" ), iSV, iErr );
			QString qsResultsCSVFN;                                              // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:ResultsFileName"   ), iSV, iErr );
			QString qsSDDXMLFilePath, qsCSEFilePath, qsAnalOptsINI;
         if (!qsProcessingPath.isEmpty())
            qsOutputProjDir = qsProcessingPath;
         else
            qsOutputProjDir = qsModelInputPath;
         qsResultsCSVFN  = qsLogFileName.left( qsLogFileName.length()-4 ) + QString( " Results.csv" ); 
         if (!bSFam)
         {  qsSDDXMLFilePath = "XML\\";               // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:SDDXMLFilePath"    ), iSV, iErr );
            qsCSEFilePath    = "CSE\\";               // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:CSEFilePath"       ), iSV, iErr );
         }
         qsAnalOptsINI    = qsOptionsCSV;          // BEMPX_GetString( BEMPX_GetDatabaseID( "BatchRuns:AnalOptsINISection"), iSV, iErr );

// QString &qsLogFileName,   QString &qsProcessingPath, QString &qsOptionsCSV,    QString &qsModelInputPath, QString &qsBatchRunDefsFile
// 
// int ProcessCommandLineArgs( int &iPrimaryFunction, QString &qsBEMTxtFileName, QString &qsEnumsTxtFileName,
//    QString &qsBEMBinFileName, QStringList &qslAltPaths, QString &qsRuleTxtFileName,
//    QString &qsRuleBinFileName, QString &qsWeatherPath, QString &qsModelInput )

			if (!bSFam && lRunsSpanClimates > 0)		// SAC 1/4/19
			{	qsErrMsg = "Batch processing option 'RunsSpanClimates' only compatible with SFam CBECC.";		// batch definitions CSV format change required to enable this in CBECC-Com
				//BEMMessageBox( qsErrMsg, "Batch Processing", 3 /*error*/ );
            printf( qsErrMsg.toLatin1().constData() );      // SAC 11/14/25
				return FALSE;
			}

			//CString sCompareApp;
			//if (lStoreProjToSepDir > 0 && !qsOutputProjDir.isEmpty() && qsOutputProjDir.compare( qsFullProjDir, Qt::CaseInsensitive ) != 0 && 
			//	 BEMPX_SetDataString( BEMPX_GetDatabaseID( "BatchRuns:Comparison" ), sCompareApp ) &&
			//	 !sCompareApp.IsEmpty() && FileExists( sCompareApp ))
			//{	// store current comparison app file path to INI for future use - SAC 11/20/17
			//	VERIFY( WriteProgString( "files", "CompareApp", sCompareApp ) );
			//}

			if (lStoreProjToSepDir > 0 && qsOutputProjDir.isEmpty())
				qsErrMsg = "Store Processed Projects in Separate Folder selected but no folder specified.";
			else if (qsOutputLogFN.isEmpty())
				qsErrMsg = "Batch Processing Log filename must be specified.";
			else if (qsResultsCSVFN.isEmpty())
				qsErrMsg = "Summary Results CSV filename must be specified.";
			else
			{	if (lStoreProjToSepDir > 0 && !DirectoryExists( qsOutputProjDir.toLatin1().constData() ))
					CreateAndChangeDirectory( qsOutputProjDir.toLatin1().constData(), FALSE );
				if (qsOutputProjDir.isEmpty())
					qsErrMsg = "No output folder found/defined.";
				else if (!DirectoryExists( qsOutputProjDir.toLatin1().constData() ))
					qsErrMsg = QString( "Error encountered creating output directory:  %1" ).arg( qsOutputProjDir );
			}

			if (qsErrMsg.isEmpty())
			{	if (qsOutputProjDir.right(1) != "\\" && qsOutputProjDir.right(1) != "/")
					qsOutputProjDir += '\\';

				if (qsOutputLogFN.indexOf(':') > 0 || qsOutputLogFN.indexOf('\\') == 0 || qsOutputLogFN.indexOf('/') == 0)
				{	// full path already specified - do nothing
				}
				//else if (qsOutputLogFN.indexOf('\\') > 0 || qsOutputLogFN.indexOf('/') > 0)
				//	// prepend default Projects path
				//	qsOutputLogFN = (const char*) esProjectsPath + qsOutputLogFN;
				else
					// no path at all specified, so write to Output dir
					qsOutputLogFN = qsOutputProjDir + qsOutputLogFN;

				//qsFileDescrip = "batch processing log";
				//sFileMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
				//             "application before an updated file can be written.\n\nSelect 'Retry' "
				//				 "once the file is closed, or \n'Cancel' to abort processing.", qsFileDescrip.toLatin1().constData(), qsOutputLogFN.toLatin1().constData() );
				if (!OKToWriteOrDeleteFile( qsOutputLogFN.toLatin1().constData() ))  //, sFileMsg, (!bIsUIActive) ))
				{	if (!bIsUIActive)
						qsErrMsg = QString( "Unable to open %1 file:  %2" ).arg( qsFileDescrip, qsOutputLogFN );
					else
						qsErrMsg = QString( "User chose not to use/reference %1 file:  %2" ).arg( qsFileDescrip, qsOutputLogFN );
			}	}

			if (qsErrMsg.isEmpty())
			{	if (qsResultsCSVFN.indexOf(':') > 0 || qsResultsCSVFN.indexOf('\\') == 0 || qsResultsCSVFN.indexOf('/') == 0)
				{	// full path already specified - do nothing
				}
				//else if (qsResultsCSVFN.indexOf('\\') > 0 || qsResultsCSVFN.indexOf('/') > 0)
				//	// prepend default Projects path
				//	qsResultsCSVFN = (const char*) esProjectsPath + qsResultsCSVFN;
				else
					// no path at all specified, so write to Output dir
					qsResultsCSVFN = qsOutputProjDir + qsResultsCSVFN;

				//qsFileDescrip = "summary results CSV";
				//sFileMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
				//             "application before an updated file can be written.\n\nSelect 'Retry' "
				//				 "once the file is closed, or \n'Cancel' to abort processing.", qsFileDescrip.toLatin1().constData(), qsResultsCSVFN.toLatin1().constData() );
				if (!OKToWriteOrDeleteFile( qsResultsCSVFN.toLatin1().constData() ))  //, sFileMsg, (!bIsUIActive) ))
				{	if (!bIsUIActive)
						qsErrMsg = QString( "Unable to open %1 file:  %2" ).arg( qsFileDescrip, qsResultsCSVFN );
					else
						qsErrMsg = QString( "User chose not to use/reference %1 file:  %2" ).arg( qsFileDescrip, qsResultsCSVFN );
			}	}

		   // reading & parsing of RunSet definitions file - SAC 10/16/20 (tic #3228)
			int iNumRunSetDataElements=0, iNumRunSetRecords=0;
			CStringArray saRunSetDataElementLabels;
			std::vector<std::vector<std::string>> saaRunSetRecords;
			std::vector<std::vector<std::string>> saaRunSetAnalysisActionRecords;
			std::vector<int> iaAnalActPathFile;		// SAC 11/14/20
			CString sRunSetFile, sRunSetPathFile, sRunSetPathOnly;		long lRSFStatus = 0;
         if (!qsBatchRunDefsFile.isEmpty())     // SAC 02/13/25
         {  sRunSetFile = qsBatchRunDefsFile.toLatin1().constData();
            lRSFStatus = ParseBatchRunSetDescription( sRunSetPathFile, qsModelInputPath, qsBatchRunDefsFile );
         }
         if (qsErrMsg.isEmpty() &&
				 /*BEMPX_SetDataString(  BEMPX_GetDatabaseID( "BatchRuns:RunSetFile"       ), sRunSetFile ) &&*/ !sRunSetFile.IsEmpty() &&
				 /*BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "BatchRuns:RunSetFileStatus" ), lRSFStatus  ) &&*/ lRSFStatus > 2)
			{	// ensure complete & valid sRunSetPathFile
				//sRunSetPathFile = sRunSetFile;
		      //if (sRunSetPathFile.Find(':') < 1 && sRunSetPathFile[0] != '\\' && sRunSetPathFile[0] != '/')
		      //{  // sRunSetFile excludes path, so look for it in expected places
		      //   CString sINIPath = ReadProgString( "paths", "ProjectsPath", "", TRUE );
		      //   if (!sINIPath.IsEmpty())
		      //      sRunSetPathFile = sINIPath + CString( "BatchRunSets\\" ) + sRunSetFile;
		      //   if (!FileExists( sRunSetPathFile ))
		      //   {  if (!qsFullProjDir.isEmpty())
		      //      {  sRunSetPathFile  = qsFullProjDir.toLatin1().constData();
		      //         sRunSetPathFile += sRunSetFile;
		      //   }	}
		      //}
		      //if (!FileExists( sRunSetPathFile ))
		      //{	assert( false );
		      //}
		      //else
		      //{	
               CStdioFile inFile;
					if (inFile.Open( sRunSetPathFile, CFile::modeRead ) == 0)
		         {	assert( false );
		         }
		         else
		         {	int iRSPathEndIdx = std::max( sRunSetPathFile.ReverseFind('/'), sRunSetPathFile.ReverseFind('\\') );		// SAC 11/14/20
		         	if (iRSPathEndIdx > 0)
		         		sRunSetPathOnly = sRunSetPathFile.Left( iRSPathEndIdx+1 );
		         	CString str;		CStringArray saCSVdata;
						int i=0, iFormatVer=0, iReadMode=0, iNumCSVElements=0, iRunSetFileLineNum=0, iComma;
						while (++i < 1000 && iReadMode >= 0 && iReadMode < 5)
						{	inFile.ReadString( str );
							iRunSetFileLineNum++;
		               if (str.IsEmpty() || str[0] == ';' || (str[0] == '\"' && str[1] == ';'))
		               {  // skip past comment line
		               }
		               else
		               {	switch (iReadMode)
		               	{	case  0 : {	// reading iFormatVer
								               iComma = str.Find( ',' );
								               if (iComma > 0)
								                  str = str.Left(iComma);
								               iFormatVer = atoi( (const char*) str );
								               if (iFormatVer > 0)
								               	iReadMode = 1;		// then skip to next line
								               else
								               	iReadMode = -1;
												 }	break;
									case  1 : { // reading RunSetDescription
													if (str[0] == '\"')
								               {  str = str.Right( str.GetLength()-1 );
								                  iComma = str.Find( '\"' );
								                  if (iComma > 0)
								                     str = str.Left(iComma);
								               }
								               else
								               {  iComma = str.Find( ',' );
								                  if (iComma > 0)
								                     str = str.Left(iComma);
								               }
								               if (str.IsEmpty())
								               	iReadMode = -2;
								               else
								                  iReadMode = 2;		// then skip to next line
								   			 }	break;
									case  2 : { // reading RunSet Column Labels Record
													iNumCSVElements = ParseCSVRecord( (const char*) str, saCSVdata );
													if (iNumCSVElements < 3)
													{	iReadMode = -3;
														qsErrMsg = QString( "Error encountered parsing RunSet CSV file:  RunSet table column labels (%1 found, 3 or more expected) on line %2" ).arg( QString::number( iNumCSVElements ), QString::number( iRunSetFileLineNum ) );
													}
													else
													{	if (saCSVdata.GetSize() > 3)		// first three are: InputFN, OutSubDir, AppendOutFN
														{	for (int icsv=3; icsv<saCSVdata.GetSize(); icsv++)
															{	if (saCSVdata[icsv].Find(';')==0 || saCSVdata[icsv].Find("\";")==0)
																	icsv = saCSVdata.GetSize();
																else
																	saRunSetDataElementLabels.Add( saCSVdata[icsv] );
														}	}
														iNumRunSetDataElements = saRunSetDataElementLabels.GetSize();
								                  iReadMode = 3;		// then skip to next line
													}
								   			 }	break;
									case  3 : { // reading RunSetRecords
													iNumCSVElements = ParseCSVRecord( (const char*) str, saCSVdata );
													if (iNumCSVElements < 1)
													{	// do nothing - continue onto next record (?)
													}
													else if (!saCSVdata[0].CompareNoCase("END_RUN_SET") || saCSVdata[0].Find("END_RUN_SET")==0)
													{	if (saaRunSetRecords.size() < 1)
														{	iReadMode = -4;
															qsErrMsg = QString( "Error encountered parsing RunSet CSV file:  RunSet table includes no records (line %1)" ).arg( QString::number( iRunSetFileLineNum ) );
														}
														else
									               {	iNumRunSetRecords = (int) saaRunSetRecords.size();
									                  iReadMode = 4;		// then skip to next section
													}	}
													else
													{	std::vector<std::string> saRunSetRec;
														int iNumRunSetCols = iNumRunSetDataElements + 3;
														for (int icsv=0; icsv < iNumRunSetCols; icsv++)
														{	if (icsv < saCSVdata.GetSize())
															{	if (saCSVdata[icsv].Find(',') >= 0 && saCSVdata[icsv][0] != '\"')
																	saCSVdata[icsv] = CString("\"") + saCSVdata[icsv] + CString("\"");	// add leading & trailing quotes for CSV fields containing commas - SAC 10/22/20
																saRunSetRec.push_back( (const char*) saCSVdata[icsv] );
															}
															else
																saRunSetRec.push_back( "" );
														}
														saaRunSetRecords.push_back( saRunSetRec );
													}
								   			 }	break;
									case  4 : { // reading AnalysisActionRecords
													iNumCSVElements = ParseCSVRecord( (const char*) str, saCSVdata );
													if (iNumCSVElements < 1)
													{	// do nothing - continue onto next record (?)
													}
													else if (!saCSVdata[0].CompareNoCase("END") || saCSVdata[0].Find("END")==0)
													{	if (saaRunSetAnalysisActionRecords.size() < 1)
														{	iReadMode = -5;
															qsErrMsg = QString( "Error encountered parsing RunSet CSV file:  AnalysisAction table includes no records (line %1)" ).arg( QString::number( iRunSetFileLineNum ) );
														}
														else
									                  iReadMode = 5;		// done!
													}
													else
													{	std::vector<std::string> saAnalActRec;
														for (int icsv=0; icsv < 6; icsv++)
														{	if (icsv < saCSVdata.GetSize())
															{	if (saCSVdata[icsv].Find(',') >= 0 && saCSVdata[icsv][0] != '\"')
																	saCSVdata[icsv] = CString("\"") + saCSVdata[icsv] + CString("\"");	// add leading & trailing quotes for CSV fields containing commas - SAC 10/22/20
																saAnalActRec.push_back( (const char*) saCSVdata[icsv] );
															}
															else
																saAnalActRec.push_back( "" );
														}
														saaRunSetAnalysisActionRecords.push_back( saAnalActRec );
													}
								   			 }	break;
								}	// end of RunSet file reading switch statement

		            }	}  // end of else & While loop
						if (iReadMode < 5)
						{	assert( false );	// some read error
							iNumRunSetDataElements = 0;
							if (qsErrMsg.isEmpty())
								qsErrMsg = QString( "Error encountered parsing RunSet CSV file (error code %1)" ).arg( QString::number( iReadMode ) );
						}
			}	}	//}	// end of code reading/parsing RunSet CSV file

			if (qsErrMsg.isEmpty())
			{	sBatchLogPathFile = qsOutputLogFN.toLatin1().constData();
				sBatchResultsPathFile = qsResultsCSVFN.toLatin1().constData();
				int iLastSlash = std::max( qsOutputLogFN.lastIndexOf('\\'), qsOutputLogFN.lastIndexOf('/') );
				if (qsOutputLogFN.lastIndexOf('.') > iLastSlash)
					sBatchDefsPathFile.Format( "%s.csv", qsOutputLogFN.left( qsOutputLogFN.lastIndexOf('.') ).toLatin1().constData() );
				else
					sBatchDefsPathFile.Format( "%s.csv", qsOutputLogFN.toLatin1().constData() );
				if (FileExists( sBatchDefsPathFile ))
				{	// batch input file already exists, so revise until unique
					CString sDefsBase = sBatchDefsPathFile.Left( sBatchDefsPathFile.GetLength()-4 );
					int idx=1;
					do
					{	sBatchDefsPathFile.Format( "%s-%d.csv", sDefsBase, ++idx );
					}	while (FileExists( sBatchDefsPathFile ));
				}

				QString qsProjFileNames = (bSFam ? "*.ribd*" : "*.cibd*");   // BEMPX_GetString(   elDBID_BatchRuns_ProjFileNames       , iSV, iErr );
				long lIncludeSubdirs    = 1;           // BEMPX_GetInteger(  elDBID_BatchRuns_IncludeSubdirs       , iSV, iErr );
				bool bOutDirSameAsIn = (qsFullProjDir.compare( qsOutputProjDir, Qt::CaseInsensitive ) == 0);
		      CStdioFile defsFile;
		      // open file
	         bool ok = (defsFile.Open( sBatchDefsPathFile, CFile::modeCreate | CFile::modeWrite ) != 0);
		      if (!ok)
		      	qsErrMsg = QString( "Error encountered attempting to open batch definitions CSV file:\n   %s" ).arg( (const char*) sBatchDefsPathFile );
	   	   else
				{	CString sBatchAnalOpts;
					if (qsAnalOptsINI.length() > 0)
						//VERIFY( PopulateAnalysisOptionsString( sBatchAnalOpts, true /*bBatchMode*/, qsAnalOptsINI.toLatin1().constData() ) );		// SAC 1/29/14  // SAC 2/1/19 - switched BatchMode argument from false->true (seemed wrong)
                  sBatchAnalOpts = qsAnalOptsINI.toLatin1().constData();

               bool bHaveRunSetData = (iNumRunSetDataElements > 0 && iNumRunSetRecords > 0);
					int iUseBatchDefsFileVer = (bHaveRunSetData ? 4 : iBatchDefsFileVer);

					CString str, str2;
					defsFile.WriteString( "; Fmt Ver,Summary Results File\n" );
					str.Format( "%d,\"%s\"\n", iUseBatchDefsFileVer, qsResultsCSVFN.toLatin1().constData() );		defsFile.WriteString( str );

					CString sRunSetColLbls2, sRunSetColLbls3;
					if (bHaveRunSetData)
					{	// write AnalysisAction data records into batch defs CSV
						defsFile.WriteString( ";\n" );
						defsFile.WriteString( ";\n" );
						defsFile.WriteString( ";Type,AnalysisPhase,BeforeAfterPhase,Obj:Prop,Obj to alter,,Run Col Label\n" );
						for (int iAAidx=0; (qsErrMsg.isEmpty() && iAAidx < (int) saaRunSetAnalysisActionRecords.size()); iAAidx++)
						{	str.Format( "%s,%s,%s,%s,%s,;,%s\n", saaRunSetAnalysisActionRecords[iAAidx][0].c_str(), saaRunSetAnalysisActionRecords[iAAidx][1].c_str(), saaRunSetAnalysisActionRecords[iAAidx][2].c_str(),
																			 saaRunSetAnalysisActionRecords[iAAidx][3].c_str(), saaRunSetAnalysisActionRecords[iAAidx][4].c_str(), saaRunSetAnalysisActionRecords[iAAidx][5].c_str() );
							defsFile.WriteString( str );
							sRunSetColLbls2 += ",";
							sRunSetColLbls3 += (CString(saaRunSetAnalysisActionRecords[iAAidx][5].c_str()) + CString(","));
							iaAnalActPathFile.push_back( ((saaRunSetAnalysisActionRecords[iAAidx][0].find("PathFile") != std::string::npos) ? 1 : 0) );		// SAC 11/14/20
						}
						defsFile.WriteString( "END,\n" );
					}

					defsFile.WriteString( ";\n" );
					defsFile.WriteString( ";\n" );
					//defsFile.WriteString( pszBatchDefsColLabel1 );
					str.Format( "%s%s%s", sBatchDefsColLabel2, sRunSetColLbls2, sBatchDefsColLabel22 );
					defsFile.WriteString( str );
					str.Format( "%s%s%s", sBatchDefsColLabel3, sRunSetColLbls3, sBatchDefsColLabel32 );
					defsFile.WriteString( str );

					int iRunNum=0;
					if (bHaveRunSetData)
					{	// very different process for populating individual run records when RunSet data present
						ASSERT( iNumRunSetRecords == (int) saaRunSetRecords.size() );
						for (int iRunSet=0; (qsErrMsg.isEmpty() && iRunSet < iNumRunSetRecords); iRunSet++)
						{
							QString qsInpFiles = saaRunSetRecords[iRunSet][0].c_str();		// SAC 10/28/20
							if (qsInpFiles.indexOf('.') < 0)
							{	int iDotIdx = qsProjFileNames.indexOf('.');
								if (iDotIdx >= 0)
									qsInpFiles += qsProjFileNames.right( qsProjFileNames.length()-iDotIdx );
							}
							QStringList filters;
							filters << qsInpFiles;
							QDirIterator it( qsFullProjDir, filters, QDir::Files, (lIncludeSubdirs ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags) );
							QString qsFile, qsOutDir;
							while (it.hasNext() && qsErrMsg.isEmpty())
							{	qsFile = it.next();
								qsOutDir.clear();
								iRunNum++;

								if (bOutDirSameAsIn)
								{	//str.Format( "1,\"%s\",\"%s\",", qsFile.toLatin1().constData(), qsFile.toLatin1().constData() );
									int iLastSlash = std::max( qsFile.lastIndexOf( "\\" ), qsFile.lastIndexOf( "/" ) );
									if (iLastSlash > 0)
										qsOutDir = qsFile.left( iLastSlash+1 );
								}
								else
								{	qsOutDir = qsOutputProjDir + qsFile.right( qsFile.length()-qsFullProjDir.length() );
									int iLastSlash = std::max( qsOutDir.lastIndexOf( "\\" ), qsOutDir.lastIndexOf( "/" ) );
									if (iLastSlash > qsOutputProjDir.length())
									{	QDir dir( qsOutDir.left( iLastSlash ) );
										if (!dir.exists())
											dir.mkpath(".");
										if (!dir.exists() && qsErrMsg.isEmpty())
											qsErrMsg = QString( "Unable to create run #%1 output directory:\n   %2" ).arg( QString::number(iRunNum), qsOutDir.left( iLastSlash ) );
									}
									//str.Format( "1,\"%s\",\"%s%s\",", qsFile.toLatin1().constData(), qsOutputProjDir.toLatin1().constData(),
									//											 qsFile.right( qsFile.length()-qsFullProjDir.length() ).toLatin1().constData() );
									if (iLastSlash > 0)
										qsOutDir = qsOutDir.left( iLastSlash+1 );
								}
								QString qsOutSubdir = saaRunSetRecords[iRunSet][1].c_str();
								if (!qsOutSubdir.isEmpty())
									qsOutDir += QString( "%1/" ).arg( qsOutSubdir );
								QString qsOutFilename = qsFile.right( qsFile.length()-qsFullProjDir.length() );
								QString qsRunSetOutFile = saaRunSetRecords[iRunSet][2].c_str();
								if (!qsRunSetOutFile.isEmpty())
								{	if ((qsRunSetOutFile.left(1).compare("…")==0 || qsRunSetOutFile.left(3).compare("...")==0) &&
										 qsOutFilename.lastIndexOf('.') > 0)
									{	// insert string @ end of default output filename (before extension)
										int iNumCharsToAppend = qsRunSetOutFile.length() - (qsRunSetOutFile.left(1).compare("…")==0 ? 1 : 3);
										qsOutFilename.insert( qsOutFilename.lastIndexOf('.'), qsRunSetOutFile.right(iNumCharsToAppend) );
									}
									else
										// replace output filename
										qsOutFilename = QString( "%1.%2" ).arg( qsRunSetOutFile, qsOutFilename.right( qsOutFilename.length()-qsOutFilename.lastIndexOf('.')-1 ) );
								}
								str.Format( "1,\"%s\",\"%s%s\",", qsFile.toLatin1().constData(), qsOutDir.toLatin1().constData(), qsOutFilename.toLatin1().constData() );

                        if (bSFam)
                           str2 = ",,,,,,,,,,";
                        else
                           str2.Format( "\"%s%s\",\"%s%s\",,", qsOutDir.toLatin1().constData(), qsSDDXMLFilePath.toLatin1().constData(),
                                                               qsOutDir.toLatin1().constData(), qsCSEFilePath.toLatin1().constData() );
								str += str2;

								for (int iAAidx=0; (qsErrMsg.isEmpty() && iAAidx < iNumRunSetDataElements); iAAidx++)
								{	QString qsRunSetVal = saaRunSetRecords[iRunSet][3+iAAidx].c_str();
									QString qsAppend = ",";
									if (!qsRunSetVal.isEmpty())
									{	//if (qsRunSetVal.indexOf(',') >= 0)
										//	qsAppend = QString( "\"%1\"," ).arg( qsRunSetVal );
										//else
										if (iaAnalActPathFile[iAAidx] > 0 && qsRunSetVal.indexOf(':') < 1 &&
											 qsRunSetVal[0]!='\\' && qsRunSetVal[0]!='/')
										{	// this is a *PathFile column but data not a complete path
											QString sAAItemFullPath = qsFullProjDir + qsRunSetVal;
											if (FileExists( sAAItemFullPath.toLatin1().constData() ))						// first check for *PathFile in Input project directory - SAC 11/14/20
												qsRunSetVal = sAAItemFullPath;
											else
											{	sAAItemFullPath = sRunSetPathOnly + qsRunSetVal;
												if (FileExists( sAAItemFullPath.toLatin1().constData() ))					// next check for *PathFile in RunSet file directory - SAC 11/14/20
													qsRunSetVal = sAAItemFullPath;
												else
													qsErrMsg = QString( "Unable to find %1 '%2' in following locations for run #%3:  '%4'  '%5'" ).arg(		// SAC 11/14/20
																		saaRunSetAnalysisActionRecords[iAAidx][0].c_str(), qsRunSetVal, QString::number(iRunNum), qsFullProjDir, (const char*) sRunSetPathOnly );
										}	}
										qsAppend = QString( "%1," ).arg( qsRunSetVal );
									}
									str += qsAppend.toLatin1().constData();
								}

                        if (bSFam)
                           str2 = "CumCSV,,\n";
                        else
                           str2.Format( ",,,CumCSV,\"%s\",\n", sBatchAnalOpts );
								str += str2;
								defsFile.WriteString( str );
							}	// end of:  while (it.hasNext())
						}	// end of:  for (int iRunSet=...
					}
					else
					{
						QStringList filters;
						filters << qsProjFileNames;
						QDirIterator it( qsFullProjDir, filters, QDir::Files, (lIncludeSubdirs ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags) );
						QString qsFile, qsOutDir;
						while (it.hasNext())
						{	qsFile = it.next();
							qsOutDir.clear();
							iRunNum++;

							if (lRunsSpanClimates > 0)		// SAC 1/4/19
							{	int iCZ=1;
								for (; (qsErrMsg.isEmpty() && iCZ<=16); iCZ++)
								{
									int iLastSlashIn = std::max( qsFile.lastIndexOf( "\\" ), qsFile.lastIndexOf( "/" ) );
									int iLastDotIn   = qsFile.lastIndexOf( "." );		ASSERT( iLastDotIn > (iLastSlashIn+1) );
									QString qsRunTitle = qsFile.mid( iLastSlashIn+1, std::max( 1, (iLastDotIn-iLastSlashIn-1) ) );
									QString qsFileExt  = qsFile.right( qsFile.length()-iLastDotIn ); // includes leading '.'
									if (bOutDirSameAsIn)
									{	str.Format( "1,\"%s\",\"%s-CZ%.2i%s\",", qsFile.toLatin1().constData(), qsFile.left(iLastDotIn).toLatin1().constData(), iCZ, qsFileExt.toLatin1().constData() );
										if (iLastSlashIn > 0)
											qsOutDir = qsFile.left( iLastSlashIn+1 );
									}
									else
									{	qsOutDir = qsOutputProjDir + qsFile.right( qsFile.length()-qsFullProjDir.length() );
										int iLastSlashOut = std::max( qsOutDir.lastIndexOf( "\\" ), qsOutDir.lastIndexOf( "/" ) );
										if (iLastSlashOut > qsOutputProjDir.length())
										{	QDir dir( qsOutDir.left( iLastSlashOut ) );
											if (!dir.exists())
												dir.mkpath(".");
											if (!dir.exists() && qsErrMsg.isEmpty())
												qsErrMsg = QString( "Unable to create run #%1 output directory:\n   %2" ).arg( QString::number(iRunNum), qsOutDir.left( iLastSlashOut ) );
										}
										str.Format( "1,\"%s\",\"%s%s-CZ%.2i%s\",", qsFile.toLatin1().constData(), qsOutputProjDir.toLatin1().constData(),
														qsFile.mid( qsFullProjDir.length(), qsFile.length()-qsFullProjDir.length()-qsFileExt.length() ).toLatin1().constData(), iCZ, qsFileExt.toLatin1().constData() );
										if (iLastSlashOut > 0)
											qsOutDir = qsOutDir.left( iLastSlashOut+1 );
									}

                           if (bSFam)
                              str2.Format( "\"%s-CZ%.2i\",\"%s\",,,,,,,,,CumCSV,,\n", qsRunTitle.toLatin1().constData(), iCZ, sCZs[iCZ-1] );		// fix column alignment of Output (CumCSV) entry - SAC 01/04/21
                           else
                              str2.Format( "\"%s%s\",\"%s%s\",,,,,CumCSV,\"%s\",\n", qsOutDir.toLatin1().constData(), qsSDDXMLFilePath.toLatin1().constData(),
                                                qsOutDir.toLatin1().constData(), qsCSEFilePath.toLatin1().constData(), sBatchAnalOpts );		//ASSERT( FALSE );  // need to incorporate CZ detail
									str += str2;
									defsFile.WriteString( str );
							}	}
							else	// runs DON'T span all CZs 
							{	if (bOutDirSameAsIn)
								{	str.Format( "1,\"%s\",\"%s\",", qsFile.toLatin1().constData(), qsFile.toLatin1().constData() );
									int iLastSlash = std::max( qsFile.lastIndexOf( "\\" ), qsFile.lastIndexOf( "/" ) );
									if (iLastSlash > 0)
										qsOutDir = qsFile.left( iLastSlash+1 );
								}
								else
								{	qsOutDir = qsOutputProjDir + qsFile.right( qsFile.length()-qsFullProjDir.length() );
									int iLastSlash = std::max( qsOutDir.lastIndexOf( "\\" ), qsOutDir.lastIndexOf( "/" ) );
									if (iLastSlash > qsOutputProjDir.length())
									{	QDir dir( qsOutDir.left( iLastSlash ) );
										if (!dir.exists())
											dir.mkpath(".");
										if (!dir.exists() && qsErrMsg.isEmpty())
											qsErrMsg = QString( "Unable to create run #%1 output directory:\n   %2" ).arg( QString::number(iRunNum), qsOutDir.left( iLastSlash ) );
									}
									str.Format( "1,\"%s\",\"%s%s\",", qsFile.toLatin1().constData(), qsOutputProjDir.toLatin1().constData(),
																				 qsFile.right( qsFile.length()-qsFullProjDir.length() ).toLatin1().constData() );
									if (iLastSlash > 0)
										qsOutDir = qsOutDir.left( iLastSlash+1 );
								}

                        if (bSFam)
                           str2 = ",,,,,,,,,,CumCSV,,\n";
                        else
                           str2.Format( "\"%s%s\",\"%s%s\",,,,,CumCSV,\"%s\",\n", qsOutDir.toLatin1().constData(), qsSDDXMLFilePath.toLatin1().constData(),
                                                qsOutDir.toLatin1().constData(), qsCSEFilePath.toLatin1().constData(), sBatchAnalOpts );
								str += str2;
								defsFile.WriteString( str );
							}
						}
					}

					defsFile.WriteString( "-1\n" );
					defsFile.Close();
				}
		}	}
	}

	if (!qsErrMsg.isEmpty())
	{	qsErrMsg = "Batch processing aborting -\n\n" + qsErrMsg;
		//BEMMessageBox( qsErrMsg, "Batch Processing", 3 /*error*/ );
      printf( qsErrMsg.toLatin1().constData() );      // SAC 11/14/25
		sBatchDefsPathFile.Empty();	sBatchLogPathFile.Empty();
	}
//#else
//	sBatchDefsPathFile.Empty();		sBatchLogPathFile.Empty();		sBatchResultsPathFile.Empty();
//	qsErrMsg = "Batch processing via UI only available in CBECC-Res.";
//#endif

	return qsErrMsg.isEmpty();
}


/////////////////////////////////////////////////////////////////////////////

// SAC 5/22/13 - Based on BEMTextIO::ParseCSVRecord()  - copied from BEMCmpMgr.cpp - SAC 11/13/25
int ParseCSVRecord( const char* pszParseStr, QVector<QString>* psaCSVFields )
{
	int iRetVal = 0;
	int iParseLen = (int) strlen( pszParseStr );			assert( iParseLen > 0 );
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

int StripOutCSVOptions( QString& sRecOptionCSV, QVector<QString>* psaClrOptions, QString sReplace )
{	int iNumReplaced = 0;
	QVector<QString> saOptions;
	if (!sRecOptionCSV.isEmpty() && ParseCSVRecord( sRecOptionCSV.toLocal8Bit().constData(), &saOptions ) >= 2)
		for (int i=0; i<psaClrOptions->size(); i++)
		{	QString sFind;
			GetCSVOptionString( psaClrOptions->at(i).toLocal8Bit().constData(), sFind, saOptions );
			if (!sFind.isEmpty())
			{	sRecOptionCSV = sRecOptionCSV.replace( sFind, sReplace );
				if (!sRecOptionCSV.isEmpty())
					iNumReplaced++;
		}	}
	return iNumReplaced;
}


///////////////////////////////////////////////////////////////////////////// SAC 11/14/25

BOOL GetProgramVersion(CString& sProgVer, BOOL bPrependName, BOOL bLongVer)
{
	BOOL bRetVal = FALSE;
	sProgVer.Empty();

	//CString sProgPathFile = esProgramPath + esProgramFName;
	//sProgPathFile += ".exe";

   //TCHAR exepath[MAX_PATH+1];
   //CString sProgPathFile = GetModuleFileName( 0, exepath, MAX_PATH+1 );      // SAC 11/14/25
   vector<TCHAR> pathBuf; 
   DWORD copied = 0;
   do 
   {  pathBuf.resize(pathBuf.size()+MAX_PATH);
      copied = GetModuleFileName( 0, &pathBuf.at(0), (DWORD) pathBuf.size() );
   } while( copied >= pathBuf.size() );
   pathBuf.resize(copied);
   std::string sProgPathFile( pathBuf.begin(), pathBuf.end() );

   std::string sProgramName = "CBECC-CLI";
   //std::string sProgramName = sProgPathFile;
   //size_t iProgName_LastSlashIdx = sProgramName.find_last_of( "\\/" );
   //if (iProgName_LastSlashIdx != std::string::npos && iProgName_LastSlashIdx < (sProgramName.length()-1))      // SAC 11/14/25
   //   sProgramName = sProgramName.substr( iProgName_LastSlashIdx+1, sProgramName.length()-iProgName_LastSlashIdx-1 );
   //size_t iProgName_LastDotIdx = sProgramName.rfind( '.' );
   //if (iProgName_LastDotIdx != std::string::npos && iProgName_LastDotIdx > 0)      // SAC 11/14/25
   //   sProgramName = sProgramName.substr( 0, iProgName_LastDotIdx );

   DWORD  verHandle = NULL;
	UINT   size	  = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = GetFileVersionInfoSize( sProgPathFile.c_str(), &verHandle );
	int major=0, minor=0, minor2=0, build=0;
	if (verSize != NULL)
	{	LPSTR verData = new char[verSize];
		if (GetFileVersionInfo( sProgPathFile.c_str(), verHandle, verSize, verData))
		{	if (VerQueryValue(verData,"\\",(VOID FAR* FAR*)&lpBuffer,&size))
			{	if (size)
				{	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{	major = HIWORD(verInfo->dwFileVersionMS);
						minor = LOWORD(verInfo->dwFileVersionMS);
						build = verInfo->dwFileVersionLS;
						//build = verInfo->dwFileVersionLS;
                  minor2 = HIWORD(verInfo->dwFileVersionLS);      // SAC 11/20/25 (dev #617)
                  build  = LOWORD(verInfo->dwFileVersionLS);
						bRetVal = TRUE;
               }
				}
			}
		}
		delete[] verData;
	}
	if (bRetVal)
	{
		//CString sCodeYr = "2022";
   	// SAC 10/29/15 - implemented new numbering scheme - defined in CEC LF e-mail 10/2/15
	   // SAC 11/27/18 - altered to allow 2-digit iMinorNum (by increasing iMiddleNum multiplier *10)
		int iMiddleNum = (int) floor( minor / 1000.0 );
		int iMinorNum = (int) floor( minor / 10.0 ) - (iMiddleNum * 100);
		int iAlphBeta = minor % 10;
		CString sAlphBeta;
		switch (iAlphBeta)
		{	case  0 :	break;
			case  1 :	sAlphBeta = " Alpha";		break;
			case  2 :	sAlphBeta = " Alpha 2";		break;
			case  3 :	sAlphBeta = " Alpha 3";		break;
			case  4 :	sAlphBeta = " Beta";			break;
			case  5 :	sAlphBeta = " Beta 2";		break;
			case  6 :	sAlphBeta = " RV";			break;	// SAC 12/22/17
			case  7 :	sAlphBeta = " RC";			break;
			case  8 :	sAlphBeta = " SP1";			break;
			case  9 :	sAlphBeta = " SP2";			break;
			default :	sAlphBeta = " ????" ;		break;
		}
		if (bLongVer)
      {  if (minor2 > 0)
			   sProgVer.Format( "%d.%d.%d.%d%s (%d)", major, iMiddleNum, iMinorNum, minor2, sAlphBeta, build );
			else
            sProgVer.Format( "%d.%d.%d%s (%d)", major, iMiddleNum, iMinorNum, sAlphBeta, build );
      }
		else
      {  if (minor2 > 0)
            sProgVer.Format( "%d.%d.%d.%d%s", major, iMiddleNum, iMinorNum, minor2, sAlphBeta );
			else
            sProgVer.Format( "%d.%d.%d%s", major, iMiddleNum, iMinorNum, sAlphBeta );
      }

		if (bPrependName)
			sProgVer = sProgramName.c_str() + CString(" ") + sProgVer;
	}
	return bRetVal;
}
