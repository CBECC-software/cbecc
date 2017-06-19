// ComplianceUI.cpp : Defines the class behaviors for the application.
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
#include "ComplianceUI.h"

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "MainFrm.h"
#include "ComplianceUIDoc.h"
// #include "ComplianceUIView.h"
#include "MainView.h"
#include "..\BEMCmpMgr\BEMCmpMgr.h"
#include "CUIGlobl.h"
// #include "Screens.h"
// #include "ToolTips.h"
#include <afxadv.h>

// SAC 3/29/00 - replaced previous dynamic version string stuff with static one
//#include "FileVersion.h"
#include "CUIVersionString.h"

#include "memRptHook.h"

//#include <ShellScalingAPI.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char BASED_CODE szPaths[] = "paths";
static char BASED_CODE szFiles[] = "files";

static char BASED_CODE szPath1[] = "ProjectsPath";
//static char BASED_CODE szPath2[] = "SimulationPath";
//static char BASED_CODE szPath3[] = "SimProcessPath";
//static char BASED_CODE szPath4[] = "SimResultsPath";
//static char BASED_CODE szPath5[] = "RatesPath";
//static char BASED_CODE szPath6[] = "RulesetPath";
static const char* pszPaths[] = { szPath1, /*szPath2, szPath3, szPath4, szPath5, szPath6,*/ NULL };

static char BASED_CODE szFile1[] = "BEMFile";
//static char BASED_CODE szFile2[] = "Defaults";
//static char BASED_CODE szFile3[] = "ScreenDefinitions";
static const char* pszFiles[] = { szFile1, /*szFile2,*/ /*szFile3,*/ NULL };

static char BASED_CODE szPFErr1[] = "The following entry in the [";
static char BASED_CODE szPFErr2[] = "] section of the ";
static char BASED_CODE szPFErr3[] = " file must be corrected prior to running CBECC:\n\n";


/////////////////////////////////////////////////////////////////////////////
// CComplianceUIApp

BEGIN_MESSAGE_MAP(CComplianceUIApp, CWinApp)
	//{{AFX_MSG_MAP(CComplianceUIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplianceUIApp construction

//HRESULT WINAPI setDPIAwareRetVal;

CComplianceUIApp::CComplianceUIApp() :
	m_bPerformSimulations( TRUE), m_bPerformAnalsysis( FALSE), m_bPerformSave( FALSE)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
//	setDPIAwareRetVal = SetProcessDpiAwareness( PROCESS_DPI_UNAWARE );  // PROCESS_DPI_UNAWARE = 0, PROCESS_SYSTEM_DPI_AWARE = 1, PROCESS_PER_MONITOR_DPI_AWARE = 2
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CComplianceUIApp object

CComplianceUIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CComplianceUIApp initialization

void CComplianceUIApp::InitBEMProcINIData()
{
   int i1Class = 1;
   int iError;
   BEMClass* pClass = BEMPX_GetClass( i1Class, iError );
   while ((iError >= 0) && (pClass != NULL))
   {
      int iMaxDefs = ReadProgInt( "limits", pClass->getShortName().toLatin1().constData(), -1 );
      if (iMaxDefs > -1)
         pClass->setMaxDefinable( iMaxDefs );

      CString sDefName = ReadProgString( "DefaultNames", pClass->getShortName().toLatin1().constData(), "");
      if (sDefName.GetLength() != 0)
         pClass->setDefaultName( QString(sDefName) );

      pClass = BEMPX_GetClass( ++i1Class, iError );
   }
}

static void PresentPFError( const char* pszSection, const char* pszEntry, const char* pszItem )
{
   CString sMsg = szPFErr1;
   sMsg += pszSection;
   sMsg += szPFErr2;
   sMsg += iniFileName;
   sMsg += szPFErr3;
   sMsg += pszEntry;
   sMsg += " = ";
   sMsg += pszItem;
   AfxMessageBox( sMsg );
}

BOOL CComplianceUIApp::InitInstance()
{
   WNDCLASSEX wndcls;
   memset(&wndcls, 0, sizeof(WNDCLASSEX));
   wndcls.style         = CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
   wndcls.lpfnWndProc   = AfxWndProc;
   wndcls.hInstance     = m_hInstance;
   wndcls.hIcon         = ::LoadIcon(m_hInstance, MAKEINTRESOURCE( IDR_MAINFRAME ));
   wndcls.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
   wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wndcls.lpszClassName = _T("CBECC");
   // Added elements for Windows 95:
   wndcls.cbSize        = sizeof(WNDCLASSEX);
   wndcls.hIconSm       = NULL;  // LoadIcon(m_hInstance, "SMALL");
   ATOM regRetVal = ::RegisterClassEx(&wndcls);			regRetVal;

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	AfxInitRichEdit();  // required in order to allow dialogs to contain CRichEditCtrls

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("SAC Software"));

//	SetDialogBkColor();         // Set dialog background color to gray
	LoadStdProfileSettings(6);  // Load standard INI file options (including MRU)

#ifdef _DEBUG
//	_crtBreakAlloc = 476326;  // set breakpoint @ memory allocation
#endif

// SAC 3/19/99 - moved up from below in order to be able to grab something out of the .INI file
//               PRIOR to supplying the menu resource ID in the CSingleDocTemplate constructor
	// Parse command line for standard shell commands, DDE, file open
	CUICommandLineInfo cmdInfo;		// was: CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

   // Get .INI file name from command line
   GetProgramPath();
	if (esProgramFName.IsEmpty())   // SAC 8/19/11
		esProgramFName = "CBECC";
	
   CString cmdLine = m_lpCmdLine;
   cmdLine.MakeUpper();
   int iIniIdx = cmdLine.Find( ".INI" );
   if (iIniIdx != -1)
   {
      int iLastChar = iIniIdx + 4;
      while ( (iIniIdx >= 0) && (cmdLine[ iIniIdx ] != ' ') )
         iIniIdx--;
      if ( (iIniIdx < 0) ||
           ( (iIniIdx >= 0) && (cmdLine[ iIniIdx ] == ' ') ) )
         iIniIdx++;
      CString sTempIniName = cmdLine.Mid( iIniIdx, (iLastChar - iIniIdx) );
      if (FileExists( sTempIniName ))
         iniFileName = sTempIniName;
      else
         iniFileName = esProgramFName + ".ini";   // SAC 8/19/11
   }
   else
      iniFileName = esProgramFName + ".ini";   // SAC 8/19/11
// END - SAC 3/19/99 - moved up from below...
	esProgINIPathFile = esProgramPath + iniFileName;
	esDataPath = ReadProgString( "paths", "DataPath", NULL, TRUE );  // this FIRST call to ReadProgString() will only work to get DataPath from the program dir's INI (since the data INI not yet defined)
	esDataINIPathFile = esDataPath + iniFileName;
	esProxyINIPathFile = esDataPath + "proxy.ini";
	esProjectsPath = ReadProgString( "paths", "ProjectsPath", NULL, TRUE );

   // SAC 3/19/99 - added call to grab menu option from .INI file
   eiDeveloperMenu = ReadProgInt( "options", "DeveloperMenu", 0 );

   // SAC 4/27/00 - added to require INI file option in order to enable access to detailed inputs
   eiAllowDisplayOfDetailedInputs = ReadProgInt( "options", "EnableDetailedInputs", 0 );

   // SAC 8/11/00
   ebAnalysisRangeChecks = (ReadProgInt( "options", "AnalysisRangeChecks", 1 ) > 0);

   // SAC 2/14/01
   ebShowHelpFollowingWizard = ReadProgInt( "options", "ShowHelpFollowingWizard", 1 );

	// SAC 1/19/12
	ebIncludeCompParamStrInToolTip = (ReadProgInt( "options", "IncludeCompParamStrInToolTip", 0 ) > 0);
	ebIncludeLongCompParamStrInToolTip = (ReadProgInt( "options", "IncludeLongCompParamStrInToolTip", 0 ) > 0);
	ebIncludeStatusStrInToolTip    = (ReadProgInt( "options", "IncludeStatusStrInToolTip", 1 ) > 0);
	ebVerboseInputLogging 			 = (ReadProgInt( "options", "VerboseInputLogging", 0 ) > 0);   // SAC 3/5/12

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		(eiDeveloperMenu == 0 ? IDR_MAINFRAME : IDR_MAINFRAMEDEV),
		RUNTIME_CLASS(CComplianceUIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
//		RUNTIME_CLASS(CComplianceUIView));
		RUNTIME_CLASS(CMainView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

   ebOpeningCommandLineFile = !cmdInfo.m_strFileName.IsEmpty();  // SAC 1/1/01

// SAC 3/19/99 - moved up
//	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);
//
//   // Get .INI file name from command line
//   GetProgramPath();
//   CString cmdLine = m_lpCmdLine;
//   cmdLine.MakeUpper();
//   int iIniIdx = cmdLine.Find( ".INI" );
//   if (iIniIdx != -1)
//   {
//      int iLastChar = iIniIdx + 4;
//      while ( (iIniIdx >= 0) && (cmdLine[ iIniIdx ] != ' ') )
//         iIniIdx--;
//      if ( (iIniIdx < 0) ||
//           ( (iIniIdx >= 0) && (cmdLine[ iIniIdx ] == ' ') ) )
//         iIniIdx++;
//      CString sTempIniName = cmdLine.Mid( iIniIdx, (iLastChar - iIniIdx) );
//      if (FileExists( sTempIniName ))
//         iniFileName = sTempIniName;
//      else
//         iniFileName = "CBECC.INI";
//   }
//   else
//      iniFileName = "CBECC.INI";

   // store away CBECC Instance Handle
   ehCBECCInstance = AfxGetResourceHandle();

//#ifdef UI_CARES	// SAC 10/21/14 - wrapped in CARES2103 ifdef since no longer included in latest MFC
//	// SAC 6/25/12 - install fix for bug where thrown exception in one place/DLL not addressed and causes bomb later in execution - http://connect.microsoft.com/VisualStudio/feedback/details/563622/mfc-default-exception-handling-causes-problems-with-activation-context
//	//afxAmbientActCtx = FALSE;
//	AfxSetAmbientActCtx(FALSE);
//#endif

// TESTING/DEBUGGING
//CString sDbgPaths;
//sDbgPaths.Format( " iniFileName = %s\n esProgINIPathFile = %s\n esDataINIPathFile = %s\n esDataPath = %s\n esProjectsPath = %s\n", iniFileName, esProgINIPathFile, esDataINIPathFile, esDataPath, esProjectsPath );
//AfxMessageBox( sDbgPaths );

// TESTING/DEBUGGING
//CString sDbgDPIMsg;		sDbgDPIMsg.Format( "SetProcessDpiAwareness() returned:  %s", (setDPIAwareRetVal==S_OK ? "OK" : (setDPIAwareRetVal==E_INVALIDARG ? "Invalid Arg" : (setDPIAwareRetVal==E_ACCESSDENIED ? "Access Denied" : "unrecognized"))) );
//AfxMessageBox( sDbgDPIMsg );

	// SAC 9/2/14 - added preliminary checks for program & data INI files - more fundamental then other required INI options
	if (!FileExists( esProgINIPathFile ))
	{	CString sErrMsg;
		sErrMsg.Format( "The main %s program INI file was not found:\n%s\n\nThis file must be present, accessible and contain a valid entry for 'DataPath'"
							 " (in the [paths] section) in order to run %s.", esProgramName, esProgINIPathFile, esProgramName );
		AfxMessageBox( sErrMsg );
		return FALSE;
	}
	else if (!FileExists( esDataINIPathFile ))
	{	CString sErrMsg;
		sErrMsg.Format( "The %s 'data' INI file was not found:\n%s\n\nThe path to this file is specified in the 'DataPath' entry of the [paths] section in"
							 " the main program INI file:\n%s\n\nThis file must be present, accessible and contain a number of program options in order to run %s.", 
							 esProgramName, esDataINIPathFile, esProgINIPathFile, esProgramName );
		AfxMessageBox( sErrMsg );
		return FALSE;
	}

   // confirm existience of all required .INI paths
   int idx = -1;
   while (pszPaths[ ++idx ] != NULL)
   {
	   CString sTemp = ReadProgString( szPaths, pszPaths[ idx ], "", TRUE );
      if (!DirectoryExists( sTemp ))
      {
         PresentPFError( szPaths, pszPaths[ idx ], sTemp );
         return FALSE;
      }
   }
   // confirm existience of all required .INI files
   idx = -1;
   while (pszFiles[ ++idx ] != NULL)
   {
	   CString sTemp = ReadProgString( szFiles, pszFiles[ idx ], "", TRUE );
      if (!FileExists( sTemp ))
      {
         PresentPFError( szFiles, pszFiles[ idx ], sTemp );
         return FALSE;
      }
   }
   // transfer Proxy settings from Data INI file into Proxy-specific file (w/ encryption) - SAC 1/4/17
   TransferProxyINISettings();

	// Initialize building database & other DLLs
	CString sInitBDBFileName = ReadProgString( szFiles, "BEMFile", "", TRUE );
	CString sInitLogFileName = ReadProgString( szPaths, "ProjectsPath", "", TRUE );
	sInitLogFileName += "untitled.log";
	if (!LoadDataModel( sInitBDBFileName, BEMT_CBECC, sInitLogFileName ))	// SAC 1/3/17
		return FALSE;
// ??    InitBEMCmpMgrDLL( TRUE );

   // Load user default file
//   CString sUserDefFileName = ReadProgString( szFiles, "Defaults", "", TRUE );
//   if ( (sUserDefFileName.GetLength() > 0) &&
//        (!BEMPX_ReadUserDefaults( sUserDefFileName )) )
//      AfxMessageBox( "Error loading user default file." );

   BEMPX_WriteLogFile( "Program Startup" );

// SAC - 3/3/98 - moved into CUIGlobl function which is called upon each File-New or File-Open
//   CString sRuleName = ReadProgString( szFiles, "DefaultRuleFile", "" );
//   if (sRuleName.GetLength() > 0)
//   {
//      if (!FileExists( sRuleName ))
//      {
//         CString sErr = "Default Compliance Ruleset File '";
//         sErr += sRuleName;
//         sErr += "' Not Found";
//         AfxMessageBox( sErr );
//      }
//      else if (!CMX_LoadRuleset( sRuleName ))
//      {
//         CString sErr = "Default Compliance Ruleset File '";
//         sErr += sRuleName;
//         sErr += "' Version Compatibility Error";
//         AfxMessageBox( sErr );
//      }
//   }

   // call func to initialize BEMProc maximum number of components based on .INI file entries
   InitBEMProcINIData();

//    // Initialize tabbed dialog page data
//    BeginWaitCursor();
// 	CString sScreenFileName = ReadProgString( szFiles, "ScreenDefinitions", "", TRUE );
//    eScreenData.Init( sScreenFileName );
//    ReadToolTipFile();
//    EndWaitCursor();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

   epMRU = m_pRecentFileList;  // SAC 1/2/01
   ebAppInitialized = TRUE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);   // SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	if (PerformAnalysis())
	{	m_pMainWnd->SendMessage(WM_COMPANALYSIS);
		return FALSE;
	}

	if (PerformSave())
	{	((CMainFrame*)m_pMainWnd)->OnFileSave();
		return FALSE;
	}

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// class CUICommandLineInfo

/* virtual*/ void CUICommandLineInfo::ParseParam(	// process command line params
	const char* pszParam,		// parameter or flag
	BOOL bFlag,					// TRUE if parameter (!) (else flag)
	BOOL bLast)					// TRUE iff last param/flag on command line
{
	CComplianceUIApp* pApp = (CComplianceUIApp*)AfxGetApp();
	if (pApp)
	{	if (!pApp->ParseParam(pszParam, bFlag, bLast))
			CCommandLineInfo::ParseParam( pszParam, bFlag, bLast);
	}
}				// CWCommandLineInfo::ParseParam


/////////////////////////////////////////////////////////////////////////////
// CComplianceUIApp commands

int CComplianceUIApp::ExitInstance() 
{
//   BeginWaitCursor();
//   DeleteTabDlgData();
//   EndWaitCursor();

//   // Close CUIRpt application (if open)
//   HWND hWndCUIRpt = FindWindow( "CUIREPORT", NULL );
//   if (hWndCUIRpt)
//      ::PostMessage( hWndCUIRpt, WM_CLOSE, 0, 0L );

//	// Clear out building database & ruleset
//	BEMPX_CloseBEMProc();
//	// Closes down Qt app (if created via CBECC-* analysis)
//	CMX_ExitBEMCmpMgrDLL();
	// shuts down both BEMProc & BEMCmpMgr libraries
	CMX_ExitBEMProcAndCmpMgrDLLs();

#if defined(WIN32) && defined(_DEBUG)
	setFilterDebugHook();
#endif

//	return CBEMApp::ExitInstance();
	return CWinApp::ExitInstance();
}

static BOOL LocalParseParam( const char* pszParam, BOOL bFlag, BOOL /*bLast*/ )
{
//	returns TRUE if processed, FALSE if not
	// -nogui = No GUI
	if (bFlag && !_tcsnicmp( pszParam, _T("nogui"), 5))
	{	//m_bIsUIActive = FALSE;
   	BEMPX_SetUIActiveFlag( false );
		return TRUE;
	}
	return FALSE;
}

/*virtual*/ BOOL CComplianceUIApp::ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast)
//	returns TRUE if processed, FALSE if not
{
//	BOOL bRet = CBEMApp::ParseParam( pszParam, bFlag, bLast);
	BOOL bRet = LocalParseParam( pszParam, bFlag, bLast);
	if (!bRet)
	{	// -nosim = No Simulation
		if (bFlag && !_tcsnicmp( pszParam, _T("nosim"), 5))
		{	m_bPerformSimulations = FALSE;
			bRet = TRUE;
		}
		else if (bFlag && !_tcsnicmp( pszParam, _T("pa"), 2))
		{	m_bPerformAnalsysis = TRUE;
			bRet = TRUE;
		}
		else if (bFlag && !_tcsnicmp( pszParam, _T("save"), 4))
		{	m_bPerformSave = TRUE;
			bRet = TRUE;
		}
	}
	return bRet;
}


void CComplianceUIApp::OnFileNew()
{
	if (ebAppInitialized)
	{	CComplianceUIDoc* pCUIDoc = ((m_pMainWnd == NULL  ||  !m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) ?
											 		NULL : (CComplianceUIDoc*) ((CMainFrame*)m_pMainWnd)->GetActiveDocument());
		if (pCUIDoc)
		{	if (!pCUIDoc->CUISaveModified())
				return;
			else
				pCUIDoc->SetModifiedFlag( FALSE );
	}	}

   CWinApp::OnFileNew();

	if (ebAppInitialized)
	{	if (ebInitiateProjectCreation && m_pMainWnd && m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
			((CMainFrame*)m_pMainWnd)->SetupNewProject();
		ebInitiateProjectCreation = TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////

static DWORD CALLBACK EditStreamCallBack( DWORD dwCookie, LPBYTE pbBuff, LONG cb,
                                          LONG *pcb )
{
   CString *pstr = (CString *)dwCookie;

   if( pstr->GetLength() < cb )
   {
      *pcb = pstr->GetLength();
      memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
      pstr->Empty();
   }
   else
   {
      *pcb = cb;
      memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
      *pstr = pstr->Right( pstr->GetLength() - cb );
   }
   return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CRichEditCtrl	m_rtfLicense;
	CString	m_sVersionString;
	//}}AFX_DATA

   BOOL m_bLicenseLoaded;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//m_sVersionString = CUI_VERSION_STRING;  - replaced w/ following
	GetProgramVersion( m_sVersionString );		ASSERT( !m_sVersionString.IsEmpty() );
	//}}AFX_DATA_INIT

// SAC 3/29/00 - replaced previous dynamic version string stuff with static one
//   m_sVersionString = "CBECC, Version ";
//   CFileVersion fileVer;
//   char filePath[ _MAX_PATH  ];
//   if ( ::GetModuleFileName( AfxGetResourceHandle(), filePath, _MAX_PATH ) &&
//        fileVer.Open( filePath ) )
//      m_sVersionString += fileVer.GetPDProductVersion( FALSE );
//   else
//      m_sVersionString += "???";
//   m_sVersionString += "  (Build ";
//   m_sVersionString += BUILDCOUNT_STR;
//   m_sVersionString += ')';

   m_bLicenseLoaded = FALSE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LICENSERTF, m_rtfLicense);
	DDX_Text(pDX, IDC_VERSIONSTRING, m_sVersionString);
	DDV_MaxChars(pDX, m_sVersionString, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CComplianceUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CComplianceUIApp::OnOpenRecentFile(UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList != NULL);

	ASSERT(nID >= ID_FILE_MRU_FILE1);
	ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(LPCTSTR)(*m_pRecentFileList)[nIndex]);

//	if (OpenDocumentFile((*m_pRecentFileList)[nIndex]) == NULL)
//		m_pRecentFileList->Remove(nIndex);
   CDocument* pDoc = ((CMainFrame*)m_pMainWnd)->GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (pDoc->SaveModified()) )
   {
//      if (((CMainFrame*)m_pMainWnd)->OpenTheFile( (*m_pRecentFileList)[nIndex] ))
      if (((CComplianceUIDoc*)pDoc)->OpenTheFile( (*m_pRecentFileList)[nIndex] ))
      { }
   }

	return TRUE;
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   if (!m_bLicenseLoaded)
   {
      // Stuff License text into RTF control
      m_bLicenseLoaded = TRUE;
      
      // Notes re: RTF text file -> following string:
      //   first convert all '\' into '\\'
      //   then convert all '"' into '\"'
      //   then enclose entire file in double quotes
      CString sLicText =
// Based on "CUI EULA 11-08.rtf" -
			//"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset0 Arial;}{\\f1\\fswiss\\fprq2 Arial;}{\\f2\\froman\\fprq2 Times New Roman;}}"
			//"{\\*\\generator Msftedit 5.41.21.2509;}\\viewkind4\\uc1\\pard\\qc\\b\\f0\\fs20 CBECC Interface \\f1 End-User License Agreement (EULA)\\par"
			//"\\par"
			//"\\pard\\f0 <open source license text>\\f1\\par"
			//"\\b0\\f2\\par"
			//"}";
#ifdef UI_CANRES
			"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}"
			"{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sl240\\slmult1\\lang9\\f0\\fs22 CBECC-Com LICENSE AGREEMENT     (modified BSD)\\par "
			"\\par "
			"Copyright (c) 2012-2017, California Energy Commission\\par "
			"Copyright (c) 2012-2017, Wrightsoft Corporation\\par "
			"All rights reserved.\\par "
			"Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:\\par "
			"* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.\\par "
			"* Redistributions in binary form must reproduce the above copyright notice, this list of conditions, the following disclaimer in the documentation and/or other materials provided with the distribution.\\par "
			"* Neither the name of the California Energy Commission nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.\\par "
			"\\par "
			"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
			" PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION, WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF THIS SOFTWARE"
			" (COLLECTIVELY, THE \"AUTHORS\") BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;"
			" LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY"
			" WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING"
			" TO THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES, STRICT LIABILITY OR OTHERWISE.\\par "
			"}";
#elif UI_CARES
			"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}"
			"{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sl240\\slmult1\\lang9\\f0\\fs22 CBECC-Res LICENSE AGREEMENT     (modified BSD)\\par "
			"\\par "
			"Copyright (c) 2012-2017, California Energy Commission\\par "
			"Copyright (c) 2012-2017, Wrightsoft Corporation\\par "
			"All rights reserved.\\par "
			"Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:\\par "
			"* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.\\par "
			"* Redistributions in binary form must reproduce the above copyright notice, this list of conditions, the following disclaimer in the documentation and/or other materials provided with the distribution.\\par "
			"* Neither the name of the California Energy Commission nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.\\par "
			"\\par "
			"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
			" PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION, WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF THIS SOFTWARE"
			" (COLLECTIVELY, THE \"AUTHORS\") BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;"
			" LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY"
			" WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING"
			" TO THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES, STRICT LIABILITY OR OTHERWISE.\\par "
			"}";
		//	"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}"
		//	"{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sa200\\sl276\\slmult1\\lang9\\f0\\fs22 CBECC-Res 2013 LICENSE AGREEMENT   (modified BSD)\\par"
		//	"\\par"
      //   "Copyright (c) 2013, California Energy Commission\\par"
      //   "Copyright (c) 2012 Wrightsoft Corporation\\par"
      //   "All rights reserved.\\par"
      //   "Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:\\par"
      //   "* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.\\par"
      //   "* Redistributions in binary form must reproduce the above copyright notice, this list of conditions, the following disclaimer in the documentation and/or other materials provided with the distribution.\\par"
      //   "* Neither the name of the California Energy Commission nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.\\par"
		//	"\\par"
      //   "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
		//	" PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION, WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF THIS SOFTWARE"
		//	" (COLLECTIVELY, THE \"AUTHORS\") BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS"
		//	" OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT"
		//	" OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING TO THIS"
		//	" SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES, STRICT LIABILITY OR OTHERWISE.\\par"
		//	"}";
#else
			"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}"
			"{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sl240\\slmult1\\lang9\\f0\\fs22 CBECC LICENSE AGREEMENT     (modified BSD)\\par "
			"\\par "
			"Copyright (c) 2012-2017, California Energy Commission\\par "
			"Copyright (c) 2012-2017, Wrightsoft Corporation\\par "
			"All rights reserved.\\par "
			"Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:\\par "
			"* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.\\par "
			"* Redistributions in binary form must reproduce the above copyright notice, this list of conditions, the following disclaimer in the documentation and/or other materials provided with the distribution.\\par "
			"* Neither the name of the California Energy Commission nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.\\par "
			"\\par "
			"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
			" PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION, WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF THIS SOFTWARE"
			" (COLLECTIVELY, THE \"AUTHORS\") BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;"
			" LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY"
			" WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING"
			" TO THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES, STRICT LIABILITY OR OTHERWISE.\\par "
			"}";
#endif   // UI_CARES

      EDITSTREAM es = { (DWORD)&sLicText, 0, EditStreamCallBack };
      m_rtfLicense.StreamIn( SF_RTF | SFF_SELECTION, es );
      // Set word wrap to window
      m_rtfLicense.SetTargetDevice(NULL, 0);
	}

	// Do not call CDialog::OnPaint() for painting messages
}
