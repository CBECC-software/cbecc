// MainFrm.cpp : implementation of the CMainFrame class
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

#include "stdafx.h"
#include "ComplianceUI.h"

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProperty.h"
#include "MainFrm.h"

#include "ComplianceUIDoc.h"
// #include "ComplianceUIView.h"
#include "MainView.h"
#include "CUILibView.h"
#include "..\BEMProcUI\BEMProcDialog.h"

#include "CUIGlobl.h"

#ifdef UI_CANRES
#include "..\BEMCmpMgr\BEMCmpMgrCom.h"
#elif UI_CARES
#include "..\BEMCmpMgr\BEMCmpMgrRes.h"
#else
#include "..\BEMCmpMgr\BEMCmpMgrRes.h"
#endif

#include "TextProgressCtrl.h"

#include "DlgCompType.h"
#include "DlgCreate.h"
// #include "DlgWizard.h"
//#include "DlgAnalysis.h"
#include "DlgBDBErrors.h"
//#include "DlgAnalDone.h"

#include "..\BEMProcUI\BEMProcUIX.h"
#include "..\BEMProcUI\SACDlg.h"

#include "CUIVersionString.h"

//#include "DlgWeatherMissing.h"
#include "DlgEvaluateRulelist.h"
// #include "DlgRTFDisplay.h"  - SAC 1/1/01 - replaced w/ call to help file
#include "DlgStartLoad.h"  // SAC 1/1/01
#include "PersistentWaitCursor.h"	// SAC 11/12/15
#include "XMessageBox.h"		// SAC 11/18/15

#include <io.h>
#include <direct.h>

#include <QtWidgets/QMessageBox>

#ifdef UI_CARES
#include "XMLParse.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static bool sbBarsCreated = FALSE;

// various .INI file section and entry strings
static char BASED_CODE szPaths[]    = "paths";
//static char BASED_CODE szProgPath[] = "ProgramPath";
static char BASED_CODE szProjPath[] = "ProjectsPath";
//static char BASED_CODE szWthrPath[] = "WeatherPath";
static char BASED_CODE szSimPath[]  = "SimulationPath";

//#include <stdio.h>
//#include <time.h>
//void delay(int milliseconds)
//{
//    long pause;
//    clock_t now,then;
//    pause = milliseconds*(CLOCKS_PER_SEC/1000);
//    now = then = clock();
//    while( (now-then) < pause )
//        now = clock();
//}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_EDITCOMPONENT, OnEditComponent)
	ON_UPDATE_COMMAND_UI(IDM_EDITCOMPONENT, OnUpdateEditComponent)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(IDM_WRITEANNSIMINP, OnWriteAnnualSimulationInput)
	ON_COMMAND(IDM_WRITEDDSIMINP, OnWriteDesignDaySimulationInput)
	ON_COMMAND(IDM_CREATECOMP, OnCreateComponent)
	ON_COMMAND(IDM_RELOADSCREENS, OnReloadScreens)
	ON_COMMAND(IDM_PERFORMANALYSIS, OnMPerformAnalysis)
	ON_COMMAND(IDM_PERFORMAPIANALYSIS, OnPerformAPIAnalysis)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SWITCHRULESET_1, OnUpdateEditSwitchRuleset1)
	ON_COMMAND(IDM_CHECKDBASE, OnCheckBldgDBase)
	ON_UPDATE_COMMAND_UI(ID_TOOL_WIZARD, OnUpdateToolWizard)
	ON_COMMAND(ID_TOOL_WIZARD, OnToolWizard)
	ON_UPDATE_COMMAND_UI(ID_TOOL_ANALYSIS, OnUpdateToolAnalysis)
	ON_COMMAND(ID_TOOL_ANALYSIS, OnToolAnalysis)
	ON_UPDATE_COMMAND_UI(ID_TOOL_REPORTS, OnUpdateToolReports)
	ON_COMMAND(ID_TOOL_REPORTS, OnToolReports)
	ON_COMMAND(IDM_DELETECOMP, OnDeleteComponent)
	ON_UPDATE_COMMAND_UI(IDM_DELETECOMP, OnUpdateDeleteComponent)
	ON_COMMAND(IDM_DISPLAYALLCTRLS, OnDisplayAllUIControls)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAYALLCTRLS, OnUpdateDisplayAllUIControls)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUT, OnUpdateViewInput)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_PROPOSED, OnUpdateViewProposed)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_BUDGET, OnUpdateViewBudget)
	ON_COMMAND(IDM_VIEW_INPUT, OnViewInput)
	ON_COMMAND(IDM_VIEW_PROPOSED, OnViewProposed)
	ON_COMMAND(IDM_VIEW_BUDGET, OnViewBudget)
	ON_UPDATE_COMMAND_UI(IDM_WRITEINPDETAILS, OnUpdateWriteInputDetails)
	ON_COMMAND(IDM_WRITEINPDETAILS, OnWriteInputDetails)
	ON_UPDATE_COMMAND_UI(IDM_WRITEALLINPUTS, OnUpdateWriteAllInputs)
	ON_COMMAND(IDM_WRITEALLINPUTS, OnWriteAllInputs)
	ON_UPDATE_COMMAND_UI(IDM_REWRITEINPUT, OnUpdateRewriteInput)
	ON_COMMAND(IDM_REWRITEINPUT, OnRewriteInput)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTHPXML_SGL, OnUpdateExportHPXML_Single)
	ON_COMMAND(IDM_EXPORTHPXML_SGL, OnExportHPXML_Single)
	ON_UPDATE_COMMAND_UI(IDM_CREATECOMP, OnUpdateCreateComponent)
	ON_UPDATE_COMMAND_UI(IDM_PERFORMANALYSIS, OnUpdatePerformAnalysis)
	ON_UPDATE_COMMAND_UI(IDM_PERFORMAPIANALYSIS, OnUpdatePerformAPIAnalysis)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(IDM_TOOLS_EVALLIST, OnToolsEvalRulelist)
	ON_UPDATE_COMMAND_UI(IDM_REVIEWRESULTS, OnUpdateToolsReviewResults)
	ON_COMMAND(IDM_REVIEWRESULTS, OnToolsReviewResults)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_REVIEWUMLH, OnUpdateToolsUMLHViolations)
	ON_COMMAND(IDM_TOOLS_REVIEWUMLH, OnToolsUMLHViolations)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWCSEERR, OnUpdateToolsViewCSEErrors)
	ON_COMMAND(IDM_TOOLS_VIEWCSEERR, OnToolsViewCSEErrors)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWCSERPT, OnUpdateToolsViewCSEReports)
	ON_COMMAND(IDM_TOOLS_VIEWCSERPT, OnToolsViewCSEReports)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWT24COMPRPT, OnUpdateToolsViewT24ComplianceReport)
	ON_COMMAND(IDM_TOOLS_VIEWT24COMPRPT, OnToolsViewT24ComplianceReport)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWT24STDRPT, OnUpdateToolsViewT24StandardModelReport)
	ON_COMMAND(IDM_TOOLS_VIEWT24STDRPT, OnToolsViewT24StandardModelReport)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_T24COMPRPT, OnUpdateToolsT24ComplianceReport)
	ON_COMMAND(IDM_TOOLS_T24COMPRPT, OnToolsT24ComplianceReport)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_T24STDRPT, OnUpdateToolsT24StandardModelReport)
	ON_COMMAND(IDM_TOOLS_T24STDRPT, OnToolsT24StandardModelReport)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_CAHPRPT, OnUpdateToolsCAHPReport)
	ON_COMMAND(IDM_TOOLS_CAHPRPT, OnToolsCAHPReport)
	ON_UPDATE_COMMAND_UI(IDM_CHECKRPTGENACCESS, OnUpdateToolsCheckReportGenAccess)
	ON_COMMAND(IDM_CHECKRPTGENACCESS, OnToolsCheckReportGenAccess)
	ON_UPDATE_COMMAND_UI(IDM_RPT_BLDGSUMMARY, OnUpdateToolsReport_BuildingSummary)
	ON_COMMAND(IDM_RPT_BLDGSUMMARY, OnToolsReport_BuildingSummary)
	ON_UPDATE_COMMAND_UI(IDM_RPT_BLDGSUMMARYT24, OnUpdateToolsReport_BuildingSummary_T24)
	ON_COMMAND(IDM_RPT_BLDGSUMMARYT24, OnToolsReport_BuildingSummary_T24)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_BATCH, OnUpdateToolsBatchProcessing)
	ON_COMMAND(IDM_TOOLS_BATCH, OnToolsBatchProcessing)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_FILEHASH, OnUpdateToolsGenerateFileHashes)
	ON_COMMAND(IDM_TOOLS_FILEHASH, OnToolsGenerateFileHashes)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_PUBLICKEY, OnUpdateToolsGeneratePublicKey)
	ON_COMMAND(IDM_TOOLS_PUBLICKEY, OnToolsGeneratePublicKey)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_KEYPREP, OnUpdateToolsKeyPrep)
	ON_COMMAND(IDM_TOOLS_KEYPREP, OnToolsKeyPrep)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_GENMECH1RECS, OnUpdateToolsGenerateMECH1ReportRecords)
	ON_COMMAND(IDM_TOOLS_GENMECH1RECS, OnToolsGenerateMECH1ReportRecords)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_GENDHWRECS, OnUpdateToolsGenerateDHWEquipReportRecords)
	ON_COMMAND(IDM_TOOLS_GENDHWRECS, OnToolsGenerateDHWEquipReportRecords)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_GENIAQRECS, OnUpdateToolsGenerateIAQVentReportRecords)
	ON_COMMAND(IDM_TOOLS_GENIAQRECS, OnToolsGenerateIAQVentReportRecords)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_OPTIONS, OnUpdateToolsOptions)
	ON_COMMAND(IDM_TOOLS_OPTIONS, OnToolsOptions)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_PROXY, OnUpdateToolsProxy)
	ON_COMMAND(IDM_TOOLS_PROXY, OnToolsProxy)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_GENMODEL, OnUpdateToolsGenerateModel)
	ON_COMMAND(IDM_TOOLS_GENMODEL, OnToolsGenerateModel)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWFOLDER, OnUpdateToolsViewFolder)
	ON_COMMAND(IDM_TOOLS_VIEWFOLDER, OnToolsViewFolder)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_VIEWLOG, OnUpdateToolsViewLog)
	ON_COMMAND(IDM_TOOLS_VIEWLOG, OnToolsViewLog)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_DELETELOG, OnUpdateToolsDeleteLog)
	ON_COMMAND(IDM_TOOLS_DELETELOG, OnToolsDeleteLog)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_WINDOWSHADES, OnUpdateToolsGenerateWindowShades)
	ON_COMMAND(IDM_TOOLS_WINDOWSHADES, OnToolsGenerateWindowShades)
	ON_UPDATE_COMMAND_UI(IDM_TOOLS_PURGEUNREFOBJ, OnUpdateToolsPurgeUnreferencedObjects)
	ON_COMMAND(IDM_TOOLS_PURGEUNREFOBJ, OnToolsPurgeUnreferencedObjects)
	ON_COMMAND(IDM_ANALRANGECHECKS, OnAnalysisRangeChecks)
	ON_UPDATE_COMMAND_UI(IDM_ANALRANGECHECKS, OnUpdateAnalysisRangeChecks)
	ON_COMMAND(IDM_HELP_OVERVIEW, OnHelpOverview)
	ON_UPDATE_COMMAND_UI(IDM_HELP_OVERVIEW, OnUpdateHelpOverview)
	ON_COMMAND(IDM_HELP_USERMANUAL, OnHelpUserManual)
	ON_UPDATE_COMMAND_UI(IDM_HELP_USERMANUAL, OnUpdateHelpUserManual)
	ON_COMMAND(IDM_HELP_MANDREQASSEM, OnHelpMandatoryRequirementsForAssemblies)
	ON_UPDATE_COMMAND_UI(IDM_HELP_MANDREQASSEM, OnUpdateHelpMandatoryRequirementsForAssemblies)
	ON_COMMAND(IDM_HELP_CSEDOCU, OnHelpCSEDocumentation)
	ON_UPDATE_COMMAND_UI(IDM_HELP_CSEDOCU, OnUpdateHelpCSEDocumentation)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(IDM_POSTWIZHELP, OnUpdatePostHizHelpChecklist)
	ON_COMMAND(IDM_POSTWIZHELP, OnPostHizHelpChecklist)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORTMODEL, OnUpdateFileImportModel)
	ON_COMMAND(ID_FILE_IMPORTMODEL, OnFileImportModel)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORTRESGEOM, OnUpdateFileImportResGeometry)
	ON_COMMAND(ID_FILE_IMPORTRESGEOM, OnFileImportResGeometry)
	ON_UPDATE_COMMAND_UI(IDM_HELP_COMPFORMS_NEW, OnUpdateHelpCompFormChecklist_New)
	ON_COMMAND(IDM_HELP_COMPFORMS_NEW, OnHelpCompFormChecklist_New)
	ON_UPDATE_COMMAND_UI(IDM_HELP_COMPFORMS_ALTER, OnUpdateHelpCompFormChecklist_Alterations)
	ON_COMMAND(IDM_HELP_COMPFORMS_ALTER, OnHelpCompFormChecklist_Alterations)
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(IDM_FILELIST_01, OnUpdateFileList_01)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_02, OnUpdateFileList_02)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_03, OnUpdateFileList_03)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_04, OnUpdateFileList_04)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_05, OnUpdateFileList_05)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_06, OnUpdateFileList_06)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_07, OnUpdateFileList_07)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_08, OnUpdateFileList_08)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_09, OnUpdateFileList_09)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_10, OnUpdateFileList_10)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_11, OnUpdateFileList_11)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_12, OnUpdateFileList_12)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_13, OnUpdateFileList_13)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_14, OnUpdateFileList_14)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_15, OnUpdateFileList_15)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_16, OnUpdateFileList_16)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_17, OnUpdateFileList_17)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_18, OnUpdateFileList_18)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_19, OnUpdateFileList_19)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_20, OnUpdateFileList_20)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_21, OnUpdateFileList_21)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_22, OnUpdateFileList_22)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_23, OnUpdateFileList_23)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_24, OnUpdateFileList_24)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_25, OnUpdateFileList_25)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_26, OnUpdateFileList_26)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_27, OnUpdateFileList_27)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_28, OnUpdateFileList_28)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_29, OnUpdateFileList_29)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_30, OnUpdateFileList_30)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_31, OnUpdateFileList_31)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_32, OnUpdateFileList_32)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_33, OnUpdateFileList_33)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_34, OnUpdateFileList_34)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_35, OnUpdateFileList_35)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_36, OnUpdateFileList_36)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_37, OnUpdateFileList_37)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_38, OnUpdateFileList_38)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_39, OnUpdateFileList_39)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_40, OnUpdateFileList_40)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_41, OnUpdateFileList_41)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_42, OnUpdateFileList_42)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_43, OnUpdateFileList_43)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_44, OnUpdateFileList_44)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_45, OnUpdateFileList_45)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_46, OnUpdateFileList_46)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_47, OnUpdateFileList_47)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_48, OnUpdateFileList_48)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_49, OnUpdateFileList_49)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_50, OnUpdateFileList_50)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_51, OnUpdateFileList_51)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_52, OnUpdateFileList_52)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_53, OnUpdateFileList_53)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_54, OnUpdateFileList_54)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_55, OnUpdateFileList_55)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_56, OnUpdateFileList_56)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_57, OnUpdateFileList_57)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_58, OnUpdateFileList_58)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_59, OnUpdateFileList_59)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_60, OnUpdateFileList_60)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_61, OnUpdateFileList_61)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_62, OnUpdateFileList_62)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_63, OnUpdateFileList_63)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_64, OnUpdateFileList_64)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_65, OnUpdateFileList_65)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_66, OnUpdateFileList_66)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_67, OnUpdateFileList_67)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_68, OnUpdateFileList_68)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_69, OnUpdateFileList_69)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_70, OnUpdateFileList_70)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_71, OnUpdateFileList_71)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_72, OnUpdateFileList_72)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_73, OnUpdateFileList_73)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_74, OnUpdateFileList_74)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_75, OnUpdateFileList_75)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_76, OnUpdateFileList_76)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_77, OnUpdateFileList_77)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_78, OnUpdateFileList_78)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_79, OnUpdateFileList_79)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_80, OnUpdateFileList_80)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_81, OnUpdateFileList_81)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_82, OnUpdateFileList_82)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_83, OnUpdateFileList_83)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_84, OnUpdateFileList_84)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_85, OnUpdateFileList_85)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_86, OnUpdateFileList_86)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_87, OnUpdateFileList_87)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_88, OnUpdateFileList_88)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_89, OnUpdateFileList_89)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_90, OnUpdateFileList_90)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_91, OnUpdateFileList_91)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_92, OnUpdateFileList_92)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_93, OnUpdateFileList_93)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_94, OnUpdateFileList_94)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_95, OnUpdateFileList_95)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_96, OnUpdateFileList_96)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_97, OnUpdateFileList_97)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_98, OnUpdateFileList_98)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_99, OnUpdateFileList_99)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_100, OnUpdateFileList_100)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_101, OnUpdateFileList_101)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_102, OnUpdateFileList_102)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_103, OnUpdateFileList_103)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_104, OnUpdateFileList_104)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_105, OnUpdateFileList_105)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_106, OnUpdateFileList_106)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_107, OnUpdateFileList_107)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_108, OnUpdateFileList_108)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_109, OnUpdateFileList_109)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_110, OnUpdateFileList_110)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_111, OnUpdateFileList_111)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_112, OnUpdateFileList_112)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_113, OnUpdateFileList_113)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_114, OnUpdateFileList_114)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_115, OnUpdateFileList_115)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_116, OnUpdateFileList_116)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_117, OnUpdateFileList_117)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_118, OnUpdateFileList_118)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_119, OnUpdateFileList_119)
	ON_UPDATE_COMMAND_UI(IDM_FILELIST_120, OnUpdateFileList_120)
	ON_COMMAND(IDM_FILELIST_01, OnFileList_01)
	ON_COMMAND(IDM_FILELIST_02, OnFileList_02)
	ON_COMMAND(IDM_FILELIST_03, OnFileList_03)
	ON_COMMAND(IDM_FILELIST_04, OnFileList_04)
	ON_COMMAND(IDM_FILELIST_05, OnFileList_05)
	ON_COMMAND(IDM_FILELIST_06, OnFileList_06)
	ON_COMMAND(IDM_FILELIST_07, OnFileList_07)
	ON_COMMAND(IDM_FILELIST_08, OnFileList_08)
	ON_COMMAND(IDM_FILELIST_09, OnFileList_09)
	ON_COMMAND(IDM_FILELIST_10, OnFileList_10)
	ON_COMMAND(IDM_FILELIST_11, OnFileList_11)
	ON_COMMAND(IDM_FILELIST_12, OnFileList_12)
	ON_COMMAND(IDM_FILELIST_13, OnFileList_13)
	ON_COMMAND(IDM_FILELIST_14, OnFileList_14)
	ON_COMMAND(IDM_FILELIST_15, OnFileList_15)
	ON_COMMAND(IDM_FILELIST_16, OnFileList_16)
	ON_COMMAND(IDM_FILELIST_17, OnFileList_17)
	ON_COMMAND(IDM_FILELIST_18, OnFileList_18)
	ON_COMMAND(IDM_FILELIST_19, OnFileList_19)
	ON_COMMAND(IDM_FILELIST_20, OnFileList_20)
	ON_COMMAND(IDM_FILELIST_21, OnFileList_21)
	ON_COMMAND(IDM_FILELIST_22, OnFileList_22)
	ON_COMMAND(IDM_FILELIST_23, OnFileList_23)
	ON_COMMAND(IDM_FILELIST_24, OnFileList_24)
	ON_COMMAND(IDM_FILELIST_25, OnFileList_25)
	ON_COMMAND(IDM_FILELIST_26, OnFileList_26)
	ON_COMMAND(IDM_FILELIST_27, OnFileList_27)
	ON_COMMAND(IDM_FILELIST_28, OnFileList_28)
	ON_COMMAND(IDM_FILELIST_29, OnFileList_29)
	ON_COMMAND(IDM_FILELIST_30, OnFileList_30)
	ON_COMMAND(IDM_FILELIST_31, OnFileList_31)
	ON_COMMAND(IDM_FILELIST_32, OnFileList_32)
	ON_COMMAND(IDM_FILELIST_33, OnFileList_33)
	ON_COMMAND(IDM_FILELIST_34, OnFileList_34)
	ON_COMMAND(IDM_FILELIST_35, OnFileList_35)
	ON_COMMAND(IDM_FILELIST_36, OnFileList_36)
	ON_COMMAND(IDM_FILELIST_37, OnFileList_37)
	ON_COMMAND(IDM_FILELIST_38, OnFileList_38)
	ON_COMMAND(IDM_FILELIST_39, OnFileList_39)
	ON_COMMAND(IDM_FILELIST_40, OnFileList_40)
	ON_COMMAND(IDM_FILELIST_41, OnFileList_41)
	ON_COMMAND(IDM_FILELIST_42, OnFileList_42)
	ON_COMMAND(IDM_FILELIST_43, OnFileList_43)
	ON_COMMAND(IDM_FILELIST_44, OnFileList_44)
	ON_COMMAND(IDM_FILELIST_45, OnFileList_45)
	ON_COMMAND(IDM_FILELIST_46, OnFileList_46)
	ON_COMMAND(IDM_FILELIST_47, OnFileList_47)
	ON_COMMAND(IDM_FILELIST_48, OnFileList_48)
	ON_COMMAND(IDM_FILELIST_49, OnFileList_49)
	ON_COMMAND(IDM_FILELIST_50, OnFileList_50)
	ON_COMMAND(IDM_FILELIST_51, OnFileList_51)
	ON_COMMAND(IDM_FILELIST_52, OnFileList_52)
	ON_COMMAND(IDM_FILELIST_53, OnFileList_53)
	ON_COMMAND(IDM_FILELIST_54, OnFileList_54)
	ON_COMMAND(IDM_FILELIST_55, OnFileList_55)
	ON_COMMAND(IDM_FILELIST_56, OnFileList_56)
	ON_COMMAND(IDM_FILELIST_57, OnFileList_57)
	ON_COMMAND(IDM_FILELIST_58, OnFileList_58)
	ON_COMMAND(IDM_FILELIST_59, OnFileList_59)
	ON_COMMAND(IDM_FILELIST_60, OnFileList_60)
	ON_COMMAND(IDM_FILELIST_61, OnFileList_61)
	ON_COMMAND(IDM_FILELIST_62, OnFileList_62)
	ON_COMMAND(IDM_FILELIST_63, OnFileList_63)
	ON_COMMAND(IDM_FILELIST_64, OnFileList_64)
	ON_COMMAND(IDM_FILELIST_65, OnFileList_65)
	ON_COMMAND(IDM_FILELIST_66, OnFileList_66)
	ON_COMMAND(IDM_FILELIST_67, OnFileList_67)
	ON_COMMAND(IDM_FILELIST_68, OnFileList_68)
	ON_COMMAND(IDM_FILELIST_69, OnFileList_69)
	ON_COMMAND(IDM_FILELIST_70, OnFileList_70)
	ON_COMMAND(IDM_FILELIST_71, OnFileList_71)
	ON_COMMAND(IDM_FILELIST_72, OnFileList_72)
	ON_COMMAND(IDM_FILELIST_73, OnFileList_73)
	ON_COMMAND(IDM_FILELIST_74, OnFileList_74)
	ON_COMMAND(IDM_FILELIST_75, OnFileList_75)
	ON_COMMAND(IDM_FILELIST_76, OnFileList_76)
	ON_COMMAND(IDM_FILELIST_77, OnFileList_77)
	ON_COMMAND(IDM_FILELIST_78, OnFileList_78)
	ON_COMMAND(IDM_FILELIST_79, OnFileList_79)
	ON_COMMAND(IDM_FILELIST_80, OnFileList_80)
	ON_COMMAND(IDM_FILELIST_81, OnFileList_81)
	ON_COMMAND(IDM_FILELIST_82, OnFileList_82)
	ON_COMMAND(IDM_FILELIST_83, OnFileList_83)
	ON_COMMAND(IDM_FILELIST_84, OnFileList_84)
	ON_COMMAND(IDM_FILELIST_85, OnFileList_85)
	ON_COMMAND(IDM_FILELIST_86, OnFileList_86)
	ON_COMMAND(IDM_FILELIST_87, OnFileList_87)
	ON_COMMAND(IDM_FILELIST_88, OnFileList_88)
	ON_COMMAND(IDM_FILELIST_89, OnFileList_89)
	ON_COMMAND(IDM_FILELIST_90, OnFileList_90)
	ON_COMMAND(IDM_FILELIST_91, OnFileList_91)
	ON_COMMAND(IDM_FILELIST_92, OnFileList_92)
	ON_COMMAND(IDM_FILELIST_93, OnFileList_93)
	ON_COMMAND(IDM_FILELIST_94, OnFileList_94)
	ON_COMMAND(IDM_FILELIST_95, OnFileList_95)
	ON_COMMAND(IDM_FILELIST_96, OnFileList_96)
	ON_COMMAND(IDM_FILELIST_97, OnFileList_97)
	ON_COMMAND(IDM_FILELIST_98, OnFileList_98)
	ON_COMMAND(IDM_FILELIST_99, OnFileList_99)
	ON_COMMAND(IDM_FILELIST_100, OnFileList_100)
	ON_COMMAND(IDM_FILELIST_101, OnFileList_101)
	ON_COMMAND(IDM_FILELIST_102, OnFileList_102)
	ON_COMMAND(IDM_FILELIST_103, OnFileList_103)
	ON_COMMAND(IDM_FILELIST_104, OnFileList_104)
	ON_COMMAND(IDM_FILELIST_105, OnFileList_105)
	ON_COMMAND(IDM_FILELIST_106, OnFileList_106)
	ON_COMMAND(IDM_FILELIST_107, OnFileList_107)
	ON_COMMAND(IDM_FILELIST_108, OnFileList_108)
	ON_COMMAND(IDM_FILELIST_109, OnFileList_109)
	ON_COMMAND(IDM_FILELIST_110, OnFileList_110)
	ON_COMMAND(IDM_FILELIST_111, OnFileList_111)
	ON_COMMAND(IDM_FILELIST_112, OnFileList_112)
	ON_COMMAND(IDM_FILELIST_113, OnFileList_113)
	ON_COMMAND(IDM_FILELIST_114, OnFileList_114)
	ON_COMMAND(IDM_FILELIST_115, OnFileList_115)
	ON_COMMAND(IDM_FILELIST_116, OnFileList_116)
	ON_COMMAND(IDM_FILELIST_117, OnFileList_117)
	ON_COMMAND(IDM_FILELIST_118, OnFileList_118)
	ON_COMMAND(IDM_FILELIST_119, OnFileList_119)
	ON_COMMAND(IDM_FILELIST_120, OnFileList_120)

	ON_COMMAND_EX_RANGE(ID_EDIT_SWITCHRULESET_1, ID_EDIT_SWITCHRULESET_25, OnEditSwitchRuleset)

	// Global help commands
// SAC 1/15/13 - commented out access to help for now
//	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
//	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
//	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)

   ON_COMMAND( IDQM_ITEMHELP,  OnQuickItemHelp  )
   ON_COMMAND( IDQM_TOPICHELP, OnQuickTopicHelp )
   ON_COMMAND( IDQM_DEFAULT,   OnQuickDefault   )
   ON_COMMAND( IDQM_COMMENT,   OnQuickComment   )
   ON_COMMAND( IDQM_CREATE,    OnQuickCreate    )
   ON_COMMAND( IDQM_EDIT,      OnQuickEdit      )
   ON_COMMAND( IDQM_DELETE,    OnQuickDelete    )
   ON_UPDATE_COMMAND_UI( IDQM_ITEMHELP,  OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_TOPICHELP, OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_DEFAULT,   OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_COMMENT,   OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_CREATE,    OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_EDIT,      OnUpdateQuickMenu )
   ON_UPDATE_COMMAND_UI( IDQM_DELETE,    OnUpdateQuickMenu )

   ON_MESSAGE( WM_DATAMODIFIED, OnDataModified )
   ON_MESSAGE( WM_UPDATETREE,   OnUpdateTree )
   ON_MESSAGE( WM_POPLIBTREE,   OnPopulateLibraryTree )
   ON_MESSAGE( WM_EVALPROPOSED, OnEvaluateProposedRules )
   ON_MESSAGE( WM_COMPANALYSIS, OnPerformAnalysis )

   ON_MESSAGE( WM_BUTTONPRESSED,    OnButtonPressed )
   ON_MESSAGE( WM_QUICKMENU,        OnQuickMenu )
   ON_MESSAGE( WM_SETSTATUSMESSAGE, OnSetStatusMessage )
   ON_MESSAGE( WM_CREATECOMPONENT,  OnCreateBldgComponent )
   ON_MESSAGE( WM_LOADSCREENFILES,  OnLoadScreenData )
   ON_MESSAGE( WM_CHECKCOMPAT,      OnCheckCompat )
END_MESSAGE_MAP()

static UINT indicators[] =
{
   ID_SEPARATOR,        // status line indicator
   ID_INDICATOR_DATASTATUS,
   ID_INDICATOR_DATATYPE,
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
   m_bDoingWizard = FALSE;
   m_bDoingSummaryReport = FALSE;  // SAC 6/19/13
   m_bPerformingAnalysis = FALSE;	// SAC 4/1/15
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//16    RegisterControls();

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   SetExternals(this);

//   if (bFirstTime)
//   {
//      // Initialize Wizard stuff
//      // Need to do it here because we need a window to get system font info from
//      CString sRulePN = ReadProgString( "paths", "RulesetPath", "", TRUE );
//      CString sScrnFN = sRulePN + ReadProgString( "files", "ScreenDefinitions", "", FALSE );
//      CString sTTipFN = sRulePN + ReadProgString( "files", "ToolTipMessages", "", FALSE );
//      CString sGrphPN = ReadProgString( "paths", "MetafilePath", "", TRUE );
//      BOOL bWizOK = BEMPUIX_ScreenData( this, sScrnFN, sTTipFN, sGrphPN );
//      SetBDBWTextColors();
//
//      bFirstTime = FALSE;
//   }

   if (!m_wndToolBar.Create(this) ||
       !m_wndToolBar.LoadToolBar( (eiDeveloperMenu == 0 ? IDR_MAINFRAME : IDR_MAINFRAMEDEV) ))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
   else
   {
      // Set Status Bar style
      UINT id;
      UINT style;
      int width;
      m_wndStatusBar.GetPaneInfo(0, id, style, width);
      m_wndStatusBar.SetPaneInfo(0, id, SBPS_STRETCH, 0);
      m_wndStatusBar.GetPaneInfo(1, id, style, width);
      m_wndStatusBar.SetPaneInfo(1, id, style, FontX(120));
      m_wndStatusBar.GetPaneInfo(2, id, style, width);
      m_wndStatusBar.SetPaneInfo(2, id, style, FontX(190));
   }

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

// SAC 11/19/13 - dynamic addition to menu of files stored in a particular directory
	CMenu* pMenu = GetMenu();			ASSERT( pMenu );
	m_iNumFileListMenuItems = 0;
	bool bFileListSetup = false;
	if (pMenu)
	{	int iMenuIdx = 0;
		CMenu* pSubMenu = pMenu->GetSubMenu( iMenuIdx );
		while (!bFileListSetup && pSubMenu)
		{	bFileListSetup = SetupFileListMenu( pSubMenu );
			pSubMenu = pMenu->GetSubMenu( ++iMenuIdx );
		}
	}

   sbBarsCreated = TRUE;

	return 0;
}

bool CMainFrame::SetupFileListMenu( CMenu* pSubMenu )
{	bool bRetVal = false;
	ASSERT(pSubMenu);
	ASSERT(::IsMenu(pSubMenu->GetSafeHmenu()));
	if (pSubMenu)
	{	int iCount = pSubMenu->GetMenuItemCount();
		for (int i=0; (!bRetVal && i<iCount); i++)
		{
			UINT uiItemID = pSubMenu->GetMenuItemID(i);
			if (uiItemID == IDM_FILELIST_01)
			{	CString sFileList;
				VERIFY( pSubMenu->GetMenuString( i, sFileList, MF_BYPOSITION ) );  // grab menu label for existing item - will be used to label POP-UP menu
				pSubMenu->RemoveMenu( i, MF_BYPOSITION );  // REMOVE existing 

		// check for existence of directory BEFORE adding pop-up menu
				CString sFileListPathDefault = "MenuFileList";
#ifdef UI_CANRES
				sFileListPathDefault = "ComplianceForms";
#endif
				CString sFileListPath = ReadProgString( "paths", "MenuFileList", sFileListPathDefault, TRUE );
				if (!sFileListPath.IsEmpty() && DirectoryExists( sFileListPath ))
				{	CMenu menuFileList;
					if (menuFileList.CreatePopupMenu())
					{
						AddFileListToMenu( &menuFileList, sFileListPath );
						pSubMenu->InsertMenu( i, MF_BYPOSITION|MF_POPUP, (UINT)menuFileList.Detach(), sFileList );
					}
				}
				bRetVal = true;
			}
		}
	}
	return bRetVal;
}

#define  MAX_MENUFILELISTITEMS  120
int CMainFrame::AddFileListToMenu( CMenu* pPopupMenu, CString sFileListPath )  // SAC 11/19/13
{
	m_iNumFileListMenuItems = 0;
	m_saFileListPathFiles.RemoveAll();
	CString sFN, sMenuItem, sFileFilter = sFileListPath + CString("*.*");
	struct _finddata_t c_file;
	try
	{	long hFile = _findfirst( sFileFilter, &c_file );
		if (hFile != -1)
		{	do
			{	sFN = c_file.name;
				if (sFN.Compare(".") && sFN.Compare("..") && sFN.GetLength() > 3)
				{	m_saFileListPathFiles.Add( sFileListPath + sFN );
					int iDotIdx = sFN.ReverseFind('.');
					if (iDotIdx < 1)
						sMenuItem = sFN;
					else
						sMenuItem = sFN.Left(iDotIdx) + CString(" (") + sFN.Right(sFN.GetLength()-iDotIdx-1) + CString(")");
					if (m_iNumFileListMenuItems < MAX_MENUFILELISTITEMS)
						pPopupMenu->AppendMenu( MF_STRING|MF_ENABLED, IDM_FILELIST_01 + m_iNumFileListMenuItems, sMenuItem );
					m_iNumFileListMenuItems++;
				}
			}
			while ( _findnext( hFile, &c_file ) == 0);
			_findclose( hFile );
		}
	}
	catch( ... )
	{	MessageBox( "Unknown exception thrown from CMainFrame::AddFileListToMenu()." );
	}
	if (m_iNumFileListMenuItems > MAX_MENUFILELISTITEMS)
	{	sMenuItem.Format( "Maximum number of menu file list items exceeded (%d found, max is %d) in directory:\n   %s", m_iNumFileListMenuItems, MAX_MENUFILELISTITEMS, sFileListPath );
		MessageBox( sMenuItem );
	}
	return m_iNumFileListMenuItems;
}

BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
//	BOOL bCr8RetVal = m_wndSplitter.Create( this,
//   		1, 2,                 // TODO: adjust the number of rows, columns
//   		CSize( 10, 10 ),      // TODO: adjust the minimum pane size
//   		pContext, WS_CHILD | WS_VISIBLE | SPLS_DYNAMIC_SPLIT );
//   if (bCr8RetVal)
//   {
//      m_wndSplitter.SetColumnInfo( 0, 200, 50 );
//      m_wndSplitter.SetColumnInfo( 1, 200, 50 );
//   }

	// create a splitter with 2 row, 1 columns
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

   int iViewHt = GetSystemMetrics(SM_CYFULLSCREEN) - GetSystemMetrics(SM_CYMENU) - GetSystemMetrics(SM_CYCAPTION) -
                 50;  // estimated sum of toolbar (32) and status bar (18) heights
//   int iTopSplitHt = (int) (iViewHt * 0.85);
//   int iBotSplitHt = iViewHt - iTopSplitHt;
   // SAC 6/30/99 - replaced the above code with the following to allow the initial library view height to be specified via the .INI file
   int iPercentLibView = ReadProgInt( "options", "LibViewPercent", 0 );
   int iBotSplitHt = iViewHt * iPercentLibView / 100;
   int iTopSplitHt = iViewHt - iBotSplitHt;

	// add the first splitter pane - the default view in row 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(50, iTopSplitHt), pContext))
//		RUNTIME_CLASS( CMainView ), CSize(50, iTopSplitHt), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
   else
   {
      CView* pView = (CView*) m_wndSplitter.GetPane(0,0);		pView;
//      if (pView && pView->IsKindOf(RUNTIME_CLASS(CComplianceUIView)))
//         ((CComplianceUIView*)pView)->m_sViewTitle = "Project Components";
   }

	// add the second splitter pane - an input view in row 1
	if (!m_wndSplitter.CreateView(1, 0,
		//RUNTIME_CLASS(CInputView), CSize(0, 0), pContext))
//		pContext->m_pNewViewClass, CSize(50, iBotSplitHt), pContext))
		RUNTIME_CLASS( CCUILibView ), CSize(50, iBotSplitHt), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
   else
   {
      CView* pView = (CView*) m_wndSplitter.GetPane(1,0);
      if (pView && pView->IsKindOf(RUNTIME_CLASS(CCUILibView)))
         ((CCUILibView*)pView)->m_sViewTitle = "Library Components";
   }

   m_wndSplitter.SetColumnInfo( 0, 640, 100 );
   m_wndSplitter.SetRowInfo( 0, iTopSplitHt, 100 );
   m_wndSplitter.SetRowInfo( 1, iBotSplitHt, 100 );

	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

   return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
   cs.lpszClass = _T("CBECC");

	return CFrameWnd::PreCreateWindow(cs);
}


static BOOL sbFirstTime = TRUE;
void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
   if (sbFirstTime)
   {
      sbFirstTime = FALSE;

      if (ebOpeningCommandLineFile)
		{	CDocument* pDoc = GetActiveDocument();		// SAC 9/5/14 - added call to perform model checking & defaulting to ensure consistent operation for models that are opened via command line specification
			if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
				VERIFY( ((CComplianceUIDoc*) pDoc)->CheckAndDefaultModel() );
		}
		else
      {
// // SAC 1/3/01 - Added code to start-up the reporting application right off the bat in hopes that this will prevent showing report population later
//          CString sReportApp = ReadProgString( "files", "ReportApp", "", TRUE );
//          // now we must CLEAR OUT the name of the current .BBD file in the CUIRpt.INI file
//          CString sRptINI = sReportApp;
//          sRptINI = sRptINI.Left( sRptINI.GetLength()-3 );
//          sRptINI += "INI";
//    	   if ( !FileExists( sRptINI )  ||  !WritePrivateProfileString( "files", "ResultsFile", "", sRptINI ) )
//          {
//             sRptINI = "Error:  Writing to or finding CUIRpt INI file '" + sRptINI;
//             sRptINI += "'.";
//             MessageBox( sRptINI );
//          }
//          CWnd* pCUIRpt = FindWindow( "CUIREPORT", NULL );
//          if (pCUIRpt == NULL  &&  FileExists( sReportApp ))
//          {
//             CString sProgDir = esProgramPath; //ReadProgString( szPaths, szProgPath, "" );
//             LPTSTR lptCommandLine = NULL;
// 
//             STARTUPINFO si;
//             memset(&si, 0, sizeof( STARTUPINFO ));
//             si.cb = sizeof( STARTUPINFO );
// //            si.dwFlags = STARTF_USESHOWWINDOW;
// //            si.wShowWindow = SW_MAXIMIZE;
//             PROCESS_INFORMATION pi;
//             if (!CreateProcess( sReportApp, lptCommandLine, NULL, NULL, FALSE, 0, NULL, sProgDir, &si, &pi ))
//             {
//                /* report failure to the user. */
//                DWORD dwError = GetLastError ();
//                CString sMsg;
//                sMsg.Format( "GetLastError = 0x%lx", (int)dwError );
//                MessageBox( sMsg, "CreateProcess()" );
//             }
//          }
// // SAC 1/3/01 - END OF - Added code to start-up the reporting application right off the bat in hopes that this will prevent showing report population later

         // Switch active directory to default Project path
         ChangeProgDir( szPaths, szProjPath );
			SetStatusBarStrings( "", 1 );		// SAC 10/29/15 - display software ID in second status bar pane

         CDlgStartLoad startDlg( this );
         startDlg.DoModal();

         if (startDlg.m_iOption >= 0)          // Open Recent File
         {
            BOOL bLoaded = FALSE;
            CWinApp* pApp = AfxGetApp();
            if (pApp && epMRU && epMRU->GetSize() > startDlg.m_iOption)
            {
               CString sRecentFile = (*epMRU)[startDlg.m_iOption];
               if (sRecentFile.GetLength() > 0 && FileExists( sRecentFile ))
                  bLoaded = (pApp->OpenDocumentFile( sRecentFile ) != NULL);
            }
            if (!bLoaded)
               MessageBox( "Error loading recent file." );
         }
         else if (startDlg.m_iOption == -1)    // Open Existing
            PostMessage( WM_COMMAND, ID_FILE_OPEN, 0L );
         else if (startDlg.m_iOption == -2)    // New Simplified Geometry Project
      	   PostMessage( WM_COMMAND, ID_FILE_NEW, 0L );
         else if (startDlg.m_iOption == -3)    // Blank Slate
			{	ebInitiateProjectCreation = FALSE;
				PostMessage( WM_COMMAND, ID_FILE_NEW, 0L );
			}
         //	{  }
         else                                  // Exit
            PostMessage( WM_COMMAND, ID_APP_EXIT, 0L );
      }
   }
	
	// Do not call CFrameWnd::OnPaint() for painting messages
}


/////////////////////////////////////////////////////////////////////////////
// Message-Initiated Status Bar Message Updating

LONG CMainFrame::OnSetStatusMessage( UINT /*wParam*/, LONG /*lParam*/ )
{
// SAC 10/29/15 - status bar no longer used to display property info
//   CString* pStr = (CString*) wParam;
//   if (pStr && pStr->GetLength() > 0)
//      SetStatusBarStrings( *pStr, lParam );
//   else
////      SetStatusBarStrings( "", 0 );
//      // SAC 4/22/99 - replaced above w/ below so that even if no message exists, the status and type strings still display
//      SetStatusBarStrings( "", lParam );
   return 0;
}

void CMainFrame::SetStatusBarStrings(CString sStr, long lDBID)
{
	if (lDBID == 0)
	{   if (sStr.GetLength() > 0)
	      m_wndStatusBar.SetPaneText( 0, sStr );
	//   else if (lDBID == 0)  // if string empty AND lDBID == 0, then set string to default message
	   // SAC 4/22/99 - Replaced above w/ below so that the default message is displayed whenever the message string is empty
	   else // if string empty, then set string to default message
	      m_wndStatusBar.SetPaneText( 0, "Ready" );
	}
// SAC 10/29/15 - status bar panes 1 & 2 now used to display software and ruleset version IDs
	else if (lDBID == 1) 	// update second pane w/ software version ID
	{	CString sProgVer;
		GetProgramVersion( sProgVer, FALSE /*PrependName*/ );		ASSERT( !sProgVer.IsEmpty() );
		if (sProgVer.IsEmpty())
			m_wndStatusBar.SetPaneText( 1, " " );
		else
			m_wndStatusBar.SetPaneText( 1, sProgVer );
	}
	else if (lDBID == 2) 	// update third pane w/ ruleset version ID
	{	CString sRuleVer;
#ifdef UI_CANRES
		VERIFY( BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), sRuleVer ) && !sRuleVer.IsEmpty() );
#elif UI_CARES
		VERIFY( BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:CompMgrVersion"     ), sRuleVer ) && !sRuleVer.IsEmpty() );
#endif
		if (sRuleVer.IsEmpty())
			m_wndStatusBar.SetPaneText( 2, " " );
		else
			m_wndStatusBar.SetPaneText( 2, sRuleVer );
	}

// SAC 10/29/15 - status bar no longer used to display property info
//// SAC 8/7/00 - Reversed order of Status and DataType strings and added strings corresponding to "no field selected"
//   if (lDBID == 0)   // => erase status bar message
//   {  // Data Status
//      m_wndStatusBar.SetPaneText( 1, " ");
//      // Compliance 
////      m_wndStatusBar.SetPaneText( 2, " ");
//      m_wndStatusBar.SetPaneText( 2, "No field selected");
//   }
//   else
//   {  // Data Status
//      m_wndStatusBar.SetPaneText( 1, GetCompDataTypeString( lDBID ) );
//      // Compliance 
//      m_wndStatusBar.SetPaneText( 2, GetDataStatusString( lDBID ) );
//   }
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// Button Processing
/////////////////////////////////////////////////////////////////////////////

static int siSubordTabbedDlgsDisplayed = 0;	// SAC 10/29/14 - added to prevent too many subordinate tabbed dialogs from being displayed at a time - max ~2 (?)

LONG CMainFrame::OnButtonPressed( UINT wParam, LONG lParam )
{
   long lRetVal = 1;
   if (wParam > 0 && lParam)
   {
// SAC 6/22/00 - added split of wParam into Action & Secondary to enable more flexible processing
      WORD wAction = LOWORD( wParam );
      //WORD wSecID  = HIWORD( wParam );
		CWnd* pDlg = (CWnd*) lParam;

      if (wAction == 999)
      {
		//	CString sMsg;		sMsg.Format( "OnButtonPressed( %ld, %ld )", wParam, lParam );
		//	AfxMessageBox(sMsg);
      	CString sBtnErr;
			int iError, i1ClassToEdit = 0;
			CWnd* pCtrl = GetFocus();
			if (pCtrl == NULL)
				sBtnErr.Format( "%s button processing error:  Unable to access active button.", esProgramName );
			else
			{	long lDBID = pCtrl->SendMessage( WM_GETCTRLDBID );
				if (lDBID <= BEM_COMP_MULT)
					sBtnErr.Format( "%s button processing error:  Database ID not available from active button.", esProgramName );
				else
				{	int iDBInst = (int) pCtrl->SendMessage( WM_GETCTRLDBINST );
					if (iDBInst < -1)
						sBtnErr.Format( "%s button processing error:  Database object index not available from active button.", esProgramName );
					else
					{	QString sObjProp;
						BEMPX_DBIDToDBCompParamString( lDBID, sObjProp, false /*bLongNames*/ );
						BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
						if (pPropType == NULL)
							sBtnErr.Format( "%s button processing error:  Unable to access database property info from active button (%s).", esProgramName, sObjProp.toLatin1().constData() );
						else if (pPropType->getPropType() != BEMP_Obj)
							sBtnErr.Format( "%s button processing error:  Active button database ID isn't for an object reference property (%s, PropType = %d).", esProgramName, sObjProp.toLatin1().constData(), pPropType->getPropType() );
						else
						{	CString sBtnObjID = "<unknown>";
							BEMObject* pBtnObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lDBID ), iError, iDBInst );
							if (pBtnObj && pBtnObj->getClass())
								sBtnObjID.Format( "%s '%s'", pBtnObj->getClass()->getShortName().toLatin1().constData(), pBtnObj->getName().toLatin1().constData() );
							BEMObject* pObj = NULL;
							if (!BEMPX_SetDataObject( lDBID, pObj, BEMP_Obj, iDBInst ) || pObj == NULL || pObj->getClass() == NULL)
								sBtnErr.Format( "Unable to access object referenced by the %s property of %s.", sObjProp.toLatin1().constData(), sBtnObjID );	// not really an error - expected if/when the property is unassigned
							else
							{	i1ClassToEdit = pObj->getClass()->get1BEMClassIdx();
								CString sObjID;	sObjID.Format( "%s '%s'", pObj->getClass()->getShortName().toLatin1().constData(), pObj->getName().toLatin1().constData() );
								int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );		ASSERT( iObjIdx );
								if (iObjIdx < 0 || iObjIdx >= BEMPX_GetNumObjects( i1ClassToEdit ))
									sBtnErr.Format( "%s button processing error:  Unable to retrieve index of %s referenced by the %s property of %s.", esProgramName, sObjID, sObjProp.toLatin1().constData(), sBtnObjID );
								else if (siSubordTabbedDlgsDisplayed >= 2)
									sBtnErr.Format( "Unable to view/edit %s (referenced by the %s property of %s) due to a limit on the number of tabbed dialogs allowed at one time.", sObjID, sObjProp.toLatin1().constData(), sBtnObjID );
								else
									BEMPX_SetActiveObjectIndex( i1ClassToEdit, iObjIdx );
			}	}	}	}	}
			if (!sBtnErr.IsEmpty())
				MessageBox( sBtnErr );
			else
			{	int iTabCtrlWd, iTabCtrlHt;
				VERIFY( GetDialogTabDimensions( i1ClassToEdit, iTabCtrlWd, iTabCtrlHt ) );
				CString sDialogCaption;
				GetDialogCaption( i1ClassToEdit, sDialogCaption );
				siSubordTabbedDlgsDisplayed++;
            CSACBEMProcDialog td( i1ClassToEdit, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), this,
                              0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, BEMPUIX_GetNumConsecutiveDialogTabIDs( i1ClassToEdit, 0 /*iUIMode*/ ) /*iMaxTabs*/,
                              (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
										NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
										NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
										ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
            if (td.DoModal() == IDOK)
            {}
            siSubordTabbedDlgsDisplayed--;
				pCtrl->SetFocus();	// restore focus to original button that activated the dialog...
         }
         lRetVal = 0;	// no data modified by this call alone, so don't perform Data Modified stuff (?)
      }
      else if (wAction >= 2000 && wAction <= 2300)
		{	// CREATE NEW CartesianPt child of current PolyLp object
			int iError;
			int iPolyLpObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( eiBDBCID_PolyLp, iError ) );			ASSERT( iPolyLpObjIdx >= 0 );
			if (iPolyLpObjIdx >= 0)
			{	BEMObject* pPolyLpObj = BEMPX_GetObjectByClass( eiBDBCID_PolyLp, iError, iPolyLpObjIdx );			ASSERT( pPolyLpObj );
				if (pPolyLpObj)
				{	if (!BEMPX_CanCreateAnotherChildObject( eiBDBCID_CartesianPt, pPolyLpObj, 1 /*iNumChildren*/ ))
					{	CString sErrMsg;		sErrMsg.Format( "The BEM database manager will not allow creation of another CartesianPt child of PolyLp '%s'.", pPolyLpObj->getName() );
						MessageBox( sErrMsg );
					}
					else
					{	int iNewCartPtChildIdx = (int) wAction - 2000;
						BEMObject* pCartPtObj = BEMPX_CreateObject( eiBDBCID_CartesianPt, NULL /*lpszName*/, pPolyLpObj, BEMO_User, FALSE /*bDefaultParent*/,
																					true /*bAutoCreate*/, -1 /*iBEMProcIdx*/, FALSE /*bIgnoreMaxDefinable*/, iNewCartPtChildIdx );		ASSERT( pCartPtObj );
						if (pCartPtObj)
						{	// RE-default the PolyLp's Area property to ensure that the next round of defaulting will re-calculate Area & other related properties
							BEMPX_DefaultProperty( elDBID_PolyLp_Area, iError, iPolyLpObjIdx );
							lRetVal = 1;  // ensure ret val is > 0 to cause WM_DATAMODIFIED to get thrown

							int iNumCartPts = (int) BEMPX_GetNumChildren( eiBDBCID_PolyLp, iPolyLpObjIdx, BEMO_User /*eParObjType*/, eiBDBCID_CartesianPt );
							if (iNumCartPts > 3)
							{	// when we have MORE than three vertices, initialize the new vertex to the midpoint between the points on either side of it
								BEM_ObjType eChildObjType=BEMO_User;
								int iPtObjIdx[] = {	BEMPX_GetChildObjectIndex( eiBDBCID_PolyLp, eiBDBCID_CartesianPt, iError, eChildObjType, (iNewCartPtChildIdx==0 ?     iNumCartPts : iNewCartPtChildIdx  ) ),
															BEMPX_GetChildObjectIndex( eiBDBCID_PolyLp, eiBDBCID_CartesianPt, iError, eChildObjType, (iNewCartPtChildIdx==(iNumCartPts-1) ? 1 : iNewCartPtChildIdx+2) ) };
								double faPt1[3], faPt2[3];
								long lCoordDBID = BEMPX_GetDatabaseID( "Coord", eiBDBCID_CartesianPt );
								if (	BEMPX_SetDataFloatArray( lCoordDBID, faPt1, 3, -999 /*fDefault*/, -1, iPtObjIdx[0] ) != 3 ||
										BEMPX_SetDataFloatArray( lCoordDBID, faPt2, 3, -999 /*fDefault*/, -1, iPtObjIdx[1] ) != 3 )
								{	ASSERT( FALSE ); // error retrieving coordinates on either side
								}
								else
								{	int iNewCartPtObjIdx = BEMPX_GetObjectIndex( pCartPtObj->getClass(), pCartPtObj );								ASSERT( iNewCartPtObjIdx >= 0 );
									if (iNewCartPtObjIdx >= 0 )
									{	faPt1[0] += faPt2[0];					faPt1[1] += faPt2[1];					faPt1[2] += faPt2[2];
										faPt1[0] = (float) (faPt1[0]/2.0);	faPt1[1] = (float) (faPt1[1]/2.0);	faPt1[2] = (float) (faPt1[2]/2.0);
										if (	BEMPX_SetBEMData( lCoordDBID  , BEMP_Flt, (void*) &faPt1[0], BEMO_User, iNewCartPtObjIdx ) < 0 ||
												BEMPX_SetBEMData( lCoordDBID+1, BEMP_Flt, (void*) &faPt1[1], BEMO_User, iNewCartPtObjIdx ) < 0 ||
												BEMPX_SetBEMData( lCoordDBID+2, BEMP_Flt, (void*) &faPt1[2], BEMO_User, iNewCartPtObjIdx ) < 0 )
										{	ASSERT( FALSE );
										}
			}	}	}	}	}	}	}
		}		
		else if (wAction >= 3001 && wAction <= 3020)		// SAC 2/22/17 - added 3014 and moved out from within elif UI_CANRES to access in CARES
		{	// Access PolyLp objects
			CWnd* pWnd = GetFocus();
			int iPLObjIdx = -1;   int iError;	BEM_ObjType eChildObjType = BEMO_User;
			if (wAction >= 3016 && wAction <= 3020)	// SAC 3/1/17
			{	// access to PolyLps describing Res PV arrays
				int iPV0ArrIdx = (int) wAction - 3016;
				CString sPVPolyErrMsg;
				// evaluate rulelist to setup PolyLp first
				long lPVWGeomSpecMethod;
				if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "PVWGeomSpecMethod", eiBDBCID_Proj )+iPV0ArrIdx, lPVWGeomSpecMethod ))
					sPVPolyErrMsg.Format( "Error retrieving Proj:PVWGeomSpecMethod[%d].", iPV0ArrIdx+1 );
				else
				{	if (lPVWGeomSpecMethod == 0)    // "azimuth and tilt"
					{	// need to first call rulelist to CREATE PolyLp
						CString sPLRLName;	sPLRLName.Format( "Create_PVArrayPolyLp_%d", iPV0ArrIdx+1 );
						BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);
						if (!CMX_EvaluateRuleset( "Delete_Proj_PolyLp_Children", bLogRuleEvaluation, FALSE /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ ))
							sPVPolyErrMsg.Format( "Error encountered evaluating '%s' rulelist.", "Delete_Proj_PolyLp_Children" );
						else if (!CMX_EvaluateRuleset( sPLRLName, bLogRuleEvaluation, FALSE /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ ))
							sPVPolyErrMsg.Format( "Error encountered evaluating '%s' rulelist.", sPLRLName );
					}
					if (sPVPolyErrMsg.IsEmpty())
					{	BEMObject* pPolyLpObj = NULL;
					   if (!BEMPX_GetObject( BEMPX_GetDatabaseID( "PVWGeomPolyLpRef", eiBDBCID_Proj )+iPV0ArrIdx, pPolyLpObj ) || pPolyLpObj==NULL)
							sPVPolyErrMsg.Format( "Error retrieving Proj:PVWGeomPolyLpRef[%d].", iPV0ArrIdx+1 );
						else
						{	iPLObjIdx = BEMPX_GetObjectIndex( pPolyLpObj->getClass(), pPolyLpObj );
							if (iPLObjIdx < 0)
								sPVPolyErrMsg.Format( "Error retrieving object index of Proj:PVWGeomPolyLpRef[%d].", iPV0ArrIdx+1 );
				}	}	}
				if (!sPVPolyErrMsg.IsEmpty())
               MessageBox( sPVPolyErrMsg );
			}
			else
			{	// Access PolyLp child of <various> object
				CString sClassName;
				switch (wAction)
				{	case 3001 :	sClassName = "Spc"       ;		break;
					case 3002 :	sClassName = "Ceiling"   ;		break;
					case 3003 :	sClassName = "ExtFlr"    ;		break;
					case 3004 :	sClassName = "ExtWall"   ;		break;
					case 3005 :	sClassName = "IntFlr"    ;		break;
					case 3006 :	sClassName = "IntWall"   ;		break;
					case 3007 :	sClassName = "Roof"      ;		break;
					case 3008 :	sClassName = "UndgrFlr"  ;		break;
					case 3009 :	sClassName = "UndgrWall" ;		break;
					case 3010 :	sClassName = "Window"    ;		break;
					case 3011 :	sClassName = "Skylight"  ;		break;
					case 3012 :	sClassName = "Door"      ;		break;
					case 3013 :	sClassName = "ExtShdgObj";		break;
					case 3014 :	sClassName = "Shade"     ;		break;
					case 3015 :	sClassName = "PVArrayGeom";	break;
				}
				int iParClassID = (sClassName.IsEmpty() ? 0 : BEMPX_GetDBComponentID( sClassName ));
				if (iParClassID > 0)
				{	iPLObjIdx = BEMPX_GetChildObjectIndex( iParClassID, eiBDBCID_PolyLp, iError, eChildObjType, 1 /*i1ChildIdx*/, -1 /*iObjIdx*/ );
					if (iPLObjIdx < 0)
					{	CString sCr8Msg;	sCr8Msg.Format( "No child PolyLp found for this %s.\nWould you like to create a new PolyLp to describe this %s's geometry?", sClassName, sClassName );
				//		if (BEMMessageBox( sCr8Msg, "Create New PolyLp?", 3 /*error*/, MB_YESNO|MB_DEFBUTTON2 ) == IDYES)
						if (BEMMessageBox( sCr8Msg, "Create New PolyLp?", 3 /*error*/, (QMessageBox::Yes | QMessageBox::No), QMessageBox::No ) == QMessageBox::Yes)
						{
							CreateBuildingComponent( eiBDBCID_PolyLp, 0, FALSE /*bEditNewComponent*/, pWnd, 0, 0, -1, BEMPX_GetObjectByClass( iParClassID, iError, -1 /*iParObjIdx*/ ) );
							iPLObjIdx = BEMPX_GetChildObjectIndex( iParClassID, eiBDBCID_PolyLp, iError, eChildObjType, 1 /*i1ChildIdx*/, -1 /*iObjIdx*/ );		ASSERT( iPLObjIdx >= 0 );
							if (iPLObjIdx >= 0)
							{	// check for at least one vertex in new PolyLp, and if not, create one
								int iCartPtObjIdx = BEMPX_GetChildObjectIndex( eiBDBCID_PolyLp, eiBDBCID_CartesianPt, iError, eChildObjType, 1 /*i1ChildIdx*/, iPLObjIdx /*iObjIdx*/ );
								if (iCartPtObjIdx < 0)
								{	// create a first CartesianPt child of the new PolyLp if one doesn't already exist
									BEMObject* pPolyLpObj = BEMPX_GetObjectByClass( eiBDBCID_PolyLp, iError, iPLObjIdx );				ASSERT( pPolyLpObj );
									BEMObject* pCartPtObj = BEMPX_CreateObject( eiBDBCID_CartesianPt, NULL /*lpszName*/, pPolyLpObj, BEMO_User, FALSE /*bDefaultParent*/ );		ASSERT( pCartPtObj );
									if (pCartPtObj)
									{	long lNumOfPts = 1;
										BEMPX_SetBEMData( BEMPX_GetDatabaseID( "NumOfPts", eiBDBCID_PolyLp ), BEMP_Int, (void*) &lNumOfPts, BEMO_User, iPLObjIdx, BEMS_ProgDefault );
						}	}	}	}
					}
			}	}
			if (iPLObjIdx >= 0)
			{	BEMPX_SetActiveObjectIndex( eiBDBCID_PolyLp, iPLObjIdx, eChildObjType );
				int iTabCtrlWd, iTabCtrlHt;
				VERIFY( GetDialogTabDimensions( eiBDBCID_PolyLp, iTabCtrlWd, iTabCtrlHt ) );
				CString sDialogCaption;
				GetDialogCaption( eiBDBCID_PolyLp, sDialogCaption );
				CSACBEMProcDialog td( eiBDBCID_PolyLp, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
										0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, BEMPUIX_GetNumConsecutiveDialogTabIDs( eiBDBCID_PolyLp, 0 /*iUIMode*/ ) /*iMaxTabs*/,
										(sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
										NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
										NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
										ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
				if (td.DoModal() == IDOK)
				{}
			}
		}
		else if (wAction == 3051)
		{
			CString sBrowsePath, sFileDescrip, sFileExt, sInitString;
			long lDBID_File = 0;
			BOOL bOpenDlg = TRUE;
			CString sCurrentProjPath = "";
			CDocument* pDoc = GetActiveDocument();
			if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
			{	CString sCurrentProjFile = pDoc->GetPathName();
				if (sCurrentProjFile.ReverseFind('\\') > 0)
					sCurrentProjPath = sCurrentProjFile.Left( sCurrentProjFile.ReverseFind('\\')+1 );
			}

			if (wAction == 3051)
			{	sBrowsePath  = sCurrentProjPath;
				sFileDescrip = _T("EnergyPlus input file (*.idf)|*.idf||");
				sFileExt	    = _T("idf");
				lDBID_File	 = BEMPX_GetDatabaseID( "ExcptDsgnModelFile", eiBDBCID_Proj );			ASSERT( lDBID_File > 0 );
			}

			if (lDBID_File <= 0 || !DirectoryExists( sBrowsePath ))
			{  ASSERT( FALSE );
			}
			else
			{	CreateAndChangeDirectory( sBrowsePath );
				CFileDialog dlg( bOpenDlg, sFileExt, sInitString, (bOpenDlg ? OFN_FILEMUSTEXIST | OFN_HIDEREADONLY : OFN_HIDEREADONLY), sFileDescrip, pDlg );
				if (dlg.DoModal()==IDOK)
				{	CString sSelectedFile = dlg.GetPathName();
					// Store filename to BEMBase
					int iSetDataRetVal = BEMPX_SetBEMData( lDBID_File, BEMP_Str, (void*) ((const char*) sSelectedFile) );
					if (iSetDataRetVal >= 0)
					{	if (pDoc)
							pDoc->SetModifiedFlag();
						lRetVal = 1;  // ensure ret val is > 0 to cause WM_DATAMODIFIED to get thrown
			}	}	}
		}

#ifdef UI_CARES
      else if (wAction >= 171 && wAction <= 188)
      {	int iDlgHt = 600, iDlgWd = 770;  // Present dialog to collect Multifamily Dwelling Unit data
      	if (wAction == 187)	// SAC 1/15/15 - Present dialog to collect properties defaulted based on Proj:SimSpeedOption
      	{	iDlgHt = 400;
      		iDlgWd = 410;
      	}
      	else if (wAction == 188)	// SAC 2/2/15 - Present dialog to review/edit AirNet effective leakage area properties
      	{	iDlgHt = 300;
      		iDlgWd = 400;
      	}
			CString sDialogCaption;
			GetDialogCaption( eiBDBCID_Proj, sDialogCaption );
         CSACDlg dlgProj( pDlg, eiBDBCID_Proj, 0 /* lDBID_ScreenIdx */, (long) wAction /* lDBID_ScreenID */, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDialogCaption /*pszDialogCaption*/,
									iDlgHt /*Ht*/, iDlgWd /*Wd*/, 10 /*iBaseMarg*/,
                           0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/,
                           // SAC 10/27/02 - Added new argument to trigger use of new graphical Help/Prev/Next/Done buttons
                           FALSE /*bBypassChecksOnCancel*/, FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/,
									ebIncludeLongCompParamStrInToolTip );
         dlgProj.DoModal();
      }
      else if (wAction == 3030)	// SAC 2/22/17 - updated from 3008->3030 due to overlap in range used to present PolyLp dialog (now shared between NRes & Res)
      {
			CString sDialogCaption;
			GetDialogCaption( eiBDBCID_HVACSys, sDialogCaption );
         // Present dialog to collect Multifamily Dwelling Unit data
         CSACDlg dlgDwlgUnit( pDlg, eiBDBCID_HVACSys, 0 /* lDBID_ScreenIdx */, (long) wAction /* lDBID_ScreenID */, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDialogCaption /*pszDialogCaption*/,
									270 /*Ht*/, 470 /*Wd*/, 10 /*iBaseMarg*/,
                           0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/,
                           // SAC 10/27/02 - Added new argument to trigger use of new graphical Help/Prev/Next/Done buttons
                           FALSE /*bBypassChecksOnCancel*/, FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/,
									ebIncludeLongCompParamStrInToolTip );
         dlgDwlgUnit.DoModal();
      }
      else if (wAction >= 3031 && wAction <= 3035)		// SAC 2/22/17 - PV array orientation & location screen
		{
			int iDlgHt = 600, iDlgWd = 770;
			CString sDialogCaption;
			GetDialogCaption( eiBDBCID_Proj, sDialogCaption );
         CSACDlg dlgProj( pDlg, eiBDBCID_Proj, 0 /* lDBID_ScreenIdx */, (long) wAction /* lDBID_ScreenID */, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDialogCaption /*pszDialogCaption*/,
									iDlgHt /*Ht*/, iDlgWd /*Wd*/, 10 /*iBaseMarg*/,
                           0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/,
                           // SAC 10/27/02 - Added new argument to trigger use of new graphical Help/Prev/Next/Done buttons
                           FALSE /*bBypassChecksOnCancel*/, FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/,
									ebIncludeLongCompParamStrInToolTip );
         dlgProj.DoModal();
		}

#elif UI_CANRES
	// SAC 5/29/14 - code to create & delete CartesianPt children of PolyLp objects
      else if (wAction >= 1001 && wAction <= 1300)
		{	// DELETE CartesianPt child of current PolyLp object
			int iError;
			int iPolyLpObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( eiBDBCID_PolyLp, iError ) );			ASSERT( iPolyLpObjIdx >= 0 );
			if (iPolyLpObjIdx >= 0)
			{	BEM_ObjType eChildObjType=BEMO_User;
				int iChildCartPtObjIdx = BEMPX_GetChildObjectIndex( eiBDBCID_PolyLp, eiBDBCID_CartesianPt, iError, eChildObjType, (wAction-1000) );			ASSERT( iChildCartPtObjIdx >= 0 );
				if (iChildCartPtObjIdx > 0)
				{	BEMObject* pCartPtObj = BEMPX_GetObjectByClass( eiBDBCID_CartesianPt, iError, iChildCartPtObjIdx );		ASSERT( pCartPtObj );
					if (pCartPtObj)
					{	if (BEMMessageBox( "Deleting a PolyLp point can cause the PolyLp to no longer be valid.\n\nContinue deleting this point?",
											//		eszWarning, 3 /*error*/, MB_YESNO|MB_DEFBUTTON2 ) == IDYES)
													eszWarning, 3 /*error*/, (QMessageBox::Yes | QMessageBox::No), QMessageBox::No ) == QMessageBox::Yes)
						{	BEMPX_DeleteObject( pCartPtObj );
							// RE-default the PolyLp's Area property to ensure that the next round of defaulting will re-calculate Area & other related properties
							BEMPX_DefaultProperty( elDBID_PolyLp_Area, iError, iPolyLpObjIdx );
							lRetVal = 1;  // ensure ret val is > 0 to cause WM_DATAMODIFIED to get thrown
			}	}	}	}
		}
      else if (wAction == 3050)
      {
			CString sDialogCaption;
			GetDialogCaption( eiBDBCID_Window, sDialogCaption );
         // Present dialog to collect Multifamily Dwelling Unit data
         CSACDlg dlgWinShadesDiagram( pDlg, eiBDBCID_Window, 0 /* lDBID_ScreenIdx */, (long) wAction /* lDBID_ScreenID */, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDialogCaption /*pszDialogCaption*/,
									585 /*Ht*/, 900 /*Wd*/, 10 /*iBaseMarg*/,
                           0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/,
                           // SAC 10/27/02 - Added new argument to trigger use of new graphical Help/Prev/Next/Done buttons
                           FALSE /*bBypassChecksOnCancel*/, FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/,
									ebIncludeLongCompParamStrInToolTip );
         dlgWinShadesDiagram.DoModal();
      }

#endif  // UI_CARES or UI_CANRES

   }
   return lRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers - Quick Menu Stuff

#define  NUM_QUICK_ITEMS   7
#define  QUICK_CREATE_IDX  NUM_QUICK_ITEMS-3
#define  QUICK_EDIT_IDX    NUM_QUICK_ITEMS-2
#define  QUICK_DELETE_IDX  NUM_QUICK_ITEMS-1

static UINT suiaQMIDs[]   = { IDQM_ITEMHELP, IDQM_TOPICHELP, IDQM_DEFAULT, IDQM_COMMENT, IDQM_CREATE, IDQM_EDIT, IDQM_DELETE };

static char BASED_CODE szQM1[] = "&Item Help";
static char BASED_CODE szQM2[] = "&Topic Help";
static char BASED_CODE szQM3[] = "Restore &Default";
static char BASED_CODE szQM4[] = "&Critical Default Comment";
static char BASED_CODE szQM5[] = "Create &New ";  // SAC 2/12/01 - reset back to original - was: "&Replace ";  // "Create &New ";
static char BASED_CODE szQM6[] = "&Edit ";  // "&Edit Selected ";
static char BASED_CODE szQM7[] = "Delete ";  // "Delete Selected ";
static const char* pszQMStrs[] = { szQM1, szQM2, szQM3, szQM4, szQM5, szQM6, szQM7 };

static char BASED_CODE szQM26[] = "&View ";  // "&View Selected ";
static const char* pszQM2Strs[] = { szQM1, szQM2, szQM3, szQM4, szQM5, szQM26, szQM7 };

static UINT suiaQMFlags[] = { QMI_ITEMHELP, QMI_TOPICHELP, QMI_DEFAULT, QMI_COMMENT, QMI_CREATE, QMI_EDIT, QMI_DELETE };

static BOOL sbaQMActive[ NUM_QUICK_ITEMS ];
static DWORD sdwItemHelpID   = 0;
static DWORD sdwTopicHelpID  = 0;
static long  slQuickDBID     = 0;
static int siQuickDBInstance = -1;
static int siQuickCr8Class   = 0;
static long  slQuickObjTypeDBID  = 0;
static long  slQuickObjTypeValue = 0;

LONG CMainFrame::OnQuickMenu( UINT, LONG lParam )
{
   QuickMenuInfo* pQMInfo = (QuickMenuInfo*) lParam;
   if (pQMInfo && pQMInfo->m_lDBID > 0)
   {
      UINT uiQuickMask = 0;

      if (pQMInfo->m_uiItemHelpID > 0)
         uiQuickMask |= QMI_ITEMHELP;
      if (pQMInfo->m_uiTopicHelpID > 0)
         uiQuickMask |= QMI_TOPICHELP;

      if (pQMInfo->m_bEditable)
      {
         int iStatus = BEMPX_GetDataStatus( pQMInfo->m_lDBID, pQMInfo->m_iDBInstance );
         int iPropID = BEMPX_GetPropertyID(   pQMInfo->m_lDBID );
         if (iStatus == BEMS_UserDefined && iPropID > 0)
            uiQuickMask |= QMI_DEFAULT;

         if (pQMInfo->m_bObjectAssign)  // Combo box which assigns an object
            uiQuickMask |= (QMI_CREATE | QMI_EDIT | QMI_DELETE);
      }

      DoQuickMenu( pQMInfo->m_iLeft, pQMInfo->m_iRight, pQMInfo->m_iTop, uiQuickMask,
                   pQMInfo->m_uiItemHelpID, pQMInfo->m_uiTopicHelpID, pQMInfo->m_lDBID,
                   pQMInfo->m_bObjectAssign, pQMInfo->m_iDBInstance );
   }
   return 1;
}

void CMainFrame::DoQuickMenu( int iLeft, int iRight, int iTop, UINT uiQuickMask,
                              DWORD dwItemHlpID, DWORD dwTopicHlpID, long lDBID,
                              BOOL bObjectAssign, int iDBInstance )
{
   sdwItemHelpID   = 0;
   sdwTopicHelpID  = 0;
   slQuickDBID     = 0;
   siQuickDBInstance = -1;
   siQuickCr8Class = 0;
   slQuickObjTypeDBID  = 0;
   slQuickObjTypeValue = 0;

   CMenu menu;
   if (menu.CreatePopupMenu())
   {
      sdwItemHelpID   = dwItemHlpID;
      sdwTopicHelpID  = dwTopicHlpID;
      slQuickDBID     = lDBID;
      siQuickDBInstance = iDBInstance;

      for (int i=0; i<QUICK_CREATE_IDX; i++)
      {
         if (i == 2 || i == 3)
         {
            if (!menu.AppendMenu( MF_SEPARATOR ))
               MessageBox( "AppendMenu( Separator ) Failed." );
         }

         // Append quick menu item
         sbaQMActive[i] = TRUE;
         if (!menu.AppendMenu( MF_STRING, suiaQMIDs[i], pszQMStrs[i] ))
            MessageBox( "AppendMenu( ... ) Failed." );
         else if (!(uiQuickMask & suiaQMFlags[i]) ||
                  (suiaQMFlags[i] == QMI_DEFAULT && eInterfaceMode != IM_INPUT))
            sbaQMActive[i] = FALSE;
//            menu.EnableMenuItem( suiaQMIDs[i], MF_GRAYED );
      }

// SAC 3/4/14 - DISABLE item & topic help in quick menus
      sbaQMActive[ 0 ] = FALSE;
      sbaQMActive[ 1 ] = FALSE;

      // Add "Create...", "Edit..." and "Delete..." only under certain conditions
      sbaQMActive[ QUICK_CREATE_IDX ] = FALSE;
      sbaQMActive[ QUICK_EDIT_IDX   ] = FALSE;
      sbaQMActive[ QUICK_DELETE_IDX ] = FALSE;
//      if (uiQuickMask & QMI_CREATE || uiQuickMask & QMI_EDIT || uiQuickMask & QMI_DELETE)
      if (bObjectAssign)
      {
         int iError;
         BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
         if (pPropType && (iError >= 0) && (pPropType->getPropType() == BEMP_Obj))
         {
            // Set static creation class index, used by menu handler if user selects this item
				ASSERT( pPropType->getObj1ClassIdx(1) < 1 );  // SAC 6/15/12 - need revisions to handle more than one type of object to create here
            siQuickCr8Class     = pPropType->getObj1ClassIdx(0);  // 1-Based BDB class index
            slQuickObjTypeDBID  = pPropType->getObjTypeDBID( 0); 
            slQuickObjTypeValue = pPropType->getObjTypeValue(0);

            // prepare Create..., Edit... and Delete... menu item strings
            BOOL bIsEditable    = BEMPX_GetCompIsEditable( lDBID );
            CString sCr8Str = (eInterfaceMode == IM_INPUT && bIsEditable ? pszQMStrs[ QUICK_CREATE_IDX ] : pszQM2Strs[ QUICK_CREATE_IDX ]);
            CString sEdtStr = (eInterfaceMode == IM_INPUT && bIsEditable ? pszQMStrs[ QUICK_EDIT_IDX   ] : pszQM2Strs[ QUICK_EDIT_IDX   ]);
            CString sDelStr = (eInterfaceMode == IM_INPUT && bIsEditable ? pszQMStrs[ QUICK_DELETE_IDX ] : pszQM2Strs[ QUICK_DELETE_IDX ]);
            BEMClass* pCr8Class = BEMPX_GetClass( siQuickCr8Class, iError );
            if (pCr8Class)
            {
               sCr8Str += pCr8Class->getLongName().toLatin1().constData();
               sEdtStr += pCr8Class->getLongName().toLatin1().constData();
               sDelStr += pCr8Class->getLongName().toLatin1().constData();
            }
            else
            {
               sCr8Str += "Building Component";
               sEdtStr += "Building Component";
               sDelStr += "Building Component";
            }
            sCr8Str += " (and apply only here)...";  // SAC 2/12/01 - replaced: " (this one only)...";  // "...";
            sEdtStr += " (all with this name)...";  // "...";
            sDelStr += "...";

            // add separator & Create... menu item
            if (!menu.AppendMenu( MF_SEPARATOR ))
               MessageBox( "AppendMenu( Separator ) Failed." );
            else
            {
               BOOL bCanCr8Another = BEMPX_CanCreateAnotherUserObject( siQuickCr8Class );
         //      int iError, iSV;
         //      BEMObject* pCurSelObj = BEMPX_GetObject( lDBID, iSV, iError );
					BEMObject* pCurSelObj = NULL;
					BOOL bObjOK = BEMPX_GetObject( lDBID, pCurSelObj );

               if (uiQuickMask & QMI_CREATE)
               {
                  if (!menu.AppendMenu( MF_STRING, suiaQMIDs[ QUICK_CREATE_IDX ], sCr8Str ))
                     MessageBox( "AppendMenu( Replace... ) Failed." );
                  else if (eInterfaceMode == IM_INPUT && bIsEditable && bCanCr8Another)
                     // only set this menu item to enabled if it is added successfully,
                     // it is user editable AND another one of these components can be created
                     sbaQMActive[ QUICK_CREATE_IDX ] = TRUE;
               }
               if (uiQuickMask & QMI_EDIT)
               {
                  if (!menu.AppendMenu( MF_STRING, suiaQMIDs[ QUICK_EDIT_IDX   ], sEdtStr ))
                     MessageBox( "AppendMenu( Edit... ) Failed." );
                  else if (bObjOK && pCurSelObj)
                     // only set this menu item to enabled if it is added successfully, and
                     // it is user editable
                     sbaQMActive[ QUICK_EDIT_IDX ] = TRUE;
               }
               if (uiQuickMask & QMI_DELETE)
               {
                  if (!menu.AppendMenu( MF_STRING, suiaQMIDs[ QUICK_DELETE_IDX ], sDelStr ))
                     MessageBox( "AppendMenu( Delete... ) Failed." );
                  else if (eInterfaceMode == IM_INPUT && bIsEditable && bObjOK && pCurSelObj &&
                           pCurSelObj->getObjectType() == BEMO_User)
                     // only set this menu item to enabled if it is added successfully, and
                     // it is user editable
                     sbaQMActive[ QUICK_DELETE_IDX ] = TRUE;
               }
            }
         }
      }

      int iX;
      UINT fuFlags;
      if (iRight > (appCXFullScreen/2))
      {
         iX = iLeft;
         fuFlags = TPM_RIGHTALIGN;
      }
      else
      {
         iX = iRight;
         fuFlags = TPM_LEFTALIGN;
      }

      menu.TrackPopupMenu( fuFlags | TPM_RIGHTBUTTON, iX, iTop, this );
   }
}


void CMainFrame::OnUpdateQuickMenu(CCmdUI* pCmdUI)
{
   int index = pCmdUI->m_nID - IDQM_ITEMHELP;
   if ( (index >= 0) && (index < NUM_QUICK_ITEMS) )
      pCmdUI->Enable( sbaQMActive[ index ] );
}


void CMainFrame::OnQuickItemHelp()
{
   CWnd* pWnd = GetFocus();
   WinHelp( sdwItemHelpID );
   pWnd->SetFocus();
}

void CMainFrame::OnQuickTopicHelp()
{
   CWnd* pWnd = GetFocus();
   WinHelp( sdwTopicHelpID );
   pWnd->SetFocus();
}

void CMainFrame::OnQuickDefault()
{
   CWnd* pWnd = GetFocus();
   if (pWnd && slQuickDBID > 0)
      pWnd->GetParent()->PostMessage( WM_QMRESTOREDEFAULT, siQuickDBInstance+1, slQuickDBID );

//   int iError;
//   BEMPX_DefaultProperty( slQuickDBID, iError );
//   if (iError >= 0)
//   {
//      SetDataModifiedFlag( TRUE );
//
//      // execute compliance rulelist #1
//      SendMessage( WM_EVALPROPOSED );
//
//      // send a message to the main view's tree control via CMainFrame in case the tree requires updating
//      SendMessage( WM_UPDATETREE, 0, slQuickDBID );
//
//      // redisplay all currently displayed database data
//      CWnd* pWnd = GetFocus();
//      if (pWnd)
//         pWnd->GetParent()->PostMessage( WM_DISPLAYMODS );
////         pWnd->SetFocus();
//
//      SetStatusBarStrings( "", slQuickDBID );
//   }
}

void CMainFrame::OnQuickComment()
{
// slQuickDBID
}

void CMainFrame::OnQuickCreate()
{
   CWnd* pWnd = GetFocus();
	int iError;
	int iAssignmentObjIdx = (slQuickDBID > 0 ? BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( slQuickDBID ), iError ) ) : -1);		ASSERT( iAssignmentObjIdx >= -1 );  // SAC 5/29/13
   CreateBuildingComponent( siQuickCr8Class, slQuickDBID, TRUE, pWnd, slQuickObjTypeDBID, slQuickObjTypeValue, iAssignmentObjIdx );

   if (pWnd)
   {
      pWnd->GetParent()->PostMessage( WM_DISPLAYMODS );
      pWnd->SetFocus();
   }
}

void CMainFrame::OnQuickEdit()
{
//   int iError, iSV;
//   BEMObject* pCurSelObj = BEMPX_GetObject( slQuickDBID, iSV, iError );
//   if (pCurSelObj)
   BEMObject* pCurSelObj = NULL;
   if (BEMPX_GetObject( slQuickDBID, pCurSelObj ) && pCurSelObj)
   {  // set the selected component as the active one so that when the tabbed dialog is presented,
      // it provides access to the appropriate component
      int iObjIdx = BEMPX_GetObjectIndex( pCurSelObj->getClass(), pCurSelObj );
      ASSERT( iObjIdx >= 0 );
      BEMPX_SetActiveObjectIndex( pCurSelObj->getClass()->get1BEMClassIdx(), iObjIdx, pCurSelObj->getObjectType() );

		int iTabCtrlWd, iTabCtrlHt;
		VERIFY( GetDialogTabDimensions( siQuickCr8Class, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
		CString sDialogCaption;
		GetDialogCaption( siQuickCr8Class, sDialogCaption );   // SAC 1/8/12
      CWnd* pWnd = GetFocus();
//      CBEMDialog td( siQuickCr8Class, pWnd );
      CSACBEMProcDialog td( siQuickCr8Class, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
// SAC 1/2/01 - added several arguments in order to pass in "OK" button label
                        0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, 99 /*iMaxTabs*/,
                        (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
								NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
								NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
								ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );   // SAC 1/19/12
      if (td.DoModal() == IDOK)
      {}

      if (pWnd)
      {
         pWnd->GetParent()->PostMessage( WM_DISPLAYMODS );
         pWnd->SetFocus();
      }
   }
}

void CMainFrame::OnQuickDelete()
{
//   int iError, iSV;
//   BEMObject* pCurSelObj = BEMPX_GetObject( slQuickDBID, iSV, iError );
//   if (pCurSelObj)
   BEMObject* pCurSelObj = NULL;
   if (BEMPX_GetObject( slQuickDBID, pCurSelObj ) && pCurSelObj)
   {
      CWnd* pWnd = GetFocus();
      DeleteBuildingComponent( pCurSelObj, pWnd->GetParent() );

      if (pWnd)
      {
         pWnd->GetParent()->PostMessage( WM_DISPLAYMODS );
         pWnd->SetFocus();
      }
   }
}


/////////////////////////////////////////////////////////////////////////////

LONG CMainFrame::OnCheckCompat( UINT wParam, LONG lParam )
{	LONG lRetVal = 1;
	if (wParam == 0)	// check to see if it is OK to create new component of type lParam = 1-based class index
	{
		if (lParam < 1 || !BEMPX_CanCreateAnotherUserObject( lParam ))
			lRetVal = 0;

#ifdef UI_CARES
		else if (lParam == eiBDBCID_HVACSys)		// SAC 9/4/15 - prevent creation of HVACSys objects via combobox '- create new HVACSys -' options (-Res GC #353)
		{	long lIsMultiFam;
			if (BEMPX_SetDataInteger( elDBID_Proj_IsMultiFamily, lIsMultiFam ) && lIsMultiFam > 0)
				lRetVal = 0;
		}
#endif // UI_CARES

	}
	return lRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame Help Stuff

// Copied directly from MFC
void CMainFrame::WinHelp(DWORD dwData, UINT nCmd)
{
	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	ASSERT(pApp->m_pszHelpFilePath != NULL);

	CWaitCursor wait;
// SAC 9/2/99 - added code to reset the help ID depending on what control in the main frame the user is requesting assistance on
   POINT point;
   if (dwData == 131277 && GetCursorPos( &point ))
   {
      CRect rect;
      // See if cursor is inside on of the splitter window panes - and if so...
      for (int iView=0; (iView<2 && dwData == 131277); iView++)
      {
         CWnd* pWnd = m_wndSplitter.GetPane( iView, 0 );
         if (pWnd && pWnd->IsWindowVisible())
         {
            pWnd->GetWindowRect( &rect );
            // ScreenToClient( &rect ); - 'point' is in screen coords
            if (rect.PtInRect( point ))
            {
               switch (iView)
               {
                  case 0 : {  dwData = 1000;  // default to building tabs
                              if (pWnd->IsKindOf(RUNTIME_CLASS( CMainView )))
                              {
                                 CRect treeRect;
                                 ((CMainView*)pWnd)->m_BDBTree.GetWindowRect( &treeRect );
                                 if (point.y >= treeRect.top)
                                    dwData = 1003;  // point below top of tree control => set help ID to Building Tree
                              }
                              break;
                           }
                  case 1 :    dwData = 1004;  break;  // Library tree
               }
            }
         }
      }
   }
// SAC 9/2/99 - END OF - added code to reset the help ID depending on...

	if (IsFrameWnd())
	{
		// CFrameWnd windows should be allowed to exit help mode first
		CFrameWnd* pFrameWnd = (CFrameWnd*)this;
		pFrameWnd->ExitHelpMode();
	}

	// cancel any tracking modes
	SendMessage(WM_CANCELMODE);
	SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = GetTopLevelParent();
	pWnd->SendMessage(WM_CANCELMODE);
	pWnd->SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// attempt to cancel capture
	HWND hWndCapture = ::GetCapture();
	if (hWndCapture != NULL)
		::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);

	TRACE3("WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n",
		pApp->m_pszHelpFilePath, dwData, nCmd);

	// finally, run the Windows Help engine
	if (!::WinHelp(pWnd->m_hWnd, pApp->m_pszHelpFilePath, nCmd, dwData))
		AfxMessageBox(AFX_IDP_FAILED_TO_LAUNCH_HELP);
}

void CMainFrame::OnHelpFinder() 
{
   AfxGetApp()->WinHelp(0L, HELP_FINDER);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers - File I/O

void CMainFrame::WriteToLogFile( UINT /*uiViewMsg*/, const char* output, const char* psNewLogFileName,
                                 BOOL bBlankFile )
{
   if (output != NULL)
      BEMPX_WriteLogFile( output, psNewLogFileName, (bBlankFile != FALSE) );

//   CView* pView = GetActiveView();
//   if ( (pView != NULL) && (uiViewMsg > 0) )  // update main view's RTF control
//      pView->SendMessage( uiViewMsg );
}


void CMainFrame::OnFileOpen()
{
   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (pDoc->SaveModified()) )
   {
      ChangeProgDir( szPaths, szProjPath );
//#ifdef UI_CANRES
//      CFileDialog dlg( TRUE, _T("cibd"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
//                    //   _T("Input Files (*.cibd)|*.cibd|Proposed Files (*.cpbd)|*.cpbd|Budget Files (*.cbbd)|*.cbbd||"), this );
//                       _T("Project Files (*.cibd)|*.cibd|SDD XML Project Files (*.xml)|*.xml|All Files (*.*)|*.*||"), this );
//#elif UI_CARES
//      CFileDialog dlg( TRUE, _T("ribd"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
//                    //   _T("Input Files (*.ribd)|*.ribd|Proposed Files (*.rpbd)|*.rpbd|Budget Files (*.rbbd)|*.rbbd||"), this );
//                       _T("Project Files (*.ribd)|*.ribd|Res XML Project Files (*.xml)|*.xml|All Files (*.*)|*.*||"), this );
//#else
//      CFileDialog dlg( TRUE, _T("ibd"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
//                       _T("Input Files (*.ibd)|*.ibd|Proposed Files (*.pbd)|*.pbd|Budget Files (*.bbd)|*.bbd||"), this );
//#endif
		CString sOpenFileExt, sOpenFileOpt;
		LoadFileExtensionString( sOpenFileExt, false /*bUseProjectData*/ );	// SAC 10/29/15
		LoadFileOptionString( sOpenFileOpt, false /*bUseProjectData*/, true /*bFileOpen*/ );
      CFileDialog dlg( TRUE, (LPCTSTR) sOpenFileExt, NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                       (LPCTSTR) sOpenFileOpt, this );

      if (dlg.DoModal()==IDOK)
      {
         CPathName sInputFile = dlg.GetPathName(); // Copy the filename into a CPathName so we can get the extension.
//         if (OpenTheFile( sInputFile ))
//            OnUpdateFrameTitle(TRUE);
         ((CComplianceUIDoc*)pDoc)->OpenTheFile( sInputFile );
      }

// Previous method prevented the dialog from begin centered
//      CPathName sProjDir; // = ReadProgString( "paths", "ProjectsPath", "" );
//      CPathName sInputFile;
//      OPENFILENAME ofn;
//      memset( &ofn, 0, sizeof(OPENFILENAME) );
//      ofn.lStructSize = sizeof(OPENFILENAME);
//      ofn.hwndOwner = m_hWnd;
//      ofn.hInstance = ehCBECCInstance;
//      ofn.lpstrFilter = "Input Files(*.IBD)\0*.IBD\0Proposed Files(*.PBD)\0*.PBD\0"
//                        "Budget Files(*.BBD)\0*.BBD\0";
//      ofn.lpstrFile = sInputFile.GetBuffer( _MAX_PATH );
//      ofn.lpstrInitialDir = sProjDir.GetBuffer( _MAX_PATH );
//      ofn.nMaxFile = _MAX_PATH;
//      ofn.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
//      if ( ::GetOpenFileName( &ofn ) )
//      {
//         sInputFile = ofn.lpstrFile; // Copy the filename out of the OPENFILENAME structure
//                                     // into a CPathName so we can get the extension.
//         if (OpenTheFile( sInputFile ))
//            OnUpdateFrameTitle(TRUE);
//      }
//
//      sInputFile.ReleaseBuffer();
//      sProjDir.ReleaseBuffer();
   }
}


//static char BASED_CODE szFiles[]   = "files";
//static char BASED_CODE szDefRule[] = "DefaultRuleFile";
//
//BOOL CMainFrame::OpenTheFile( CPathName sInputFile, BOOL bWriteToLog, BOOL bRestore )
//{
//   BOOL bRetVal = FALSE;
//
//   BeginWaitCursor();
//
//   if ( sInputFile.IsEmpty() )
//      return FALSE;
//
//   CString sExt;
//   sInputFile.MakeUpper();
//   sInputFile.GetExt( sExt );
//   if ( sExt.CompareNoCase( ".IBD" ) == 0 )
//      eInterfaceMode = IM_INPUT;
//   else if ( sExt.CompareNoCase( ".PBD" ) == 0 )
//      eInterfaceMode = IM_PROPOSED;
//   else if ( sExt.CompareNoCase( ".BBD" ) == 0 )
//      eInterfaceMode = IM_BUDGET;
//   else
//      AfxMessageBox( "Bad input file type" );
//
//   // SAC - 3/3/98 - get ruleset filename from project file and load the ruleset
//   BOOL bRulesetOK = LoadRuleset( BEMPX_GetRulesetFilenameFromProjectFile( sInputFile ) );
//
//   if ( BEMPX_ReadProjectFile( sInputFile, (eInterfaceMode == IM_INPUT ? BEMFM_INPUT : BEMFM_DETAIL), (bRestore != FALSE) ) )
//   {
//      m_sCurrentFileName = sInputFile;
//
//      // TODO: Do we need to refresh the interface?
////      AfxGetApp()->AddToRecentFileList( sInputFile );   
//      CDocument* pDoc = GetActiveDocument();
//      if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) )
//      {
//         pDoc->SetPathName( sInputFile );
//         pDoc->SetModifiedFlag( FALSE );
//      }
//
//      if (eInterfaceMode == IM_INPUT)  // execute compliance rulelist #1
//         SendMessage( WM_EVALPROPOSED, (!bWriteToLog) );
//
////      if (bWriteToLog)
////         WriteToLogFile();
//
//      CMainView* pMainView = (CMainView*) m_wndSplitter.GetPane(0,0);
//      if (pMainView != NULL)            // update main view's tree control(s)
//      {
//         pMainView->SendMessage( WM_DISPLAYDATA );
//
//         CView* pLibView = (CView*) m_wndSplitter.GetPane(1,0);
//         if (pLibView != NULL)            // update main view's tree control(s)
//            pLibView->SendMessage( WM_POPLIBTREE, eiCurrentTab );
//      }
//
//      eiCurAnalysisStep = AS_None;
//
//      bRetVal = TRUE;
//   }
//
//   EndWaitCursor();
//
//   return bRetVal;
//}


// SAC 6/26/13 - added ModDate override to enable analysis results validity checking
void CMainFrame::SaveFile( const char* /*psFileName*/, long lModDate /*=-1*/, bool bSetSoftwareVer /*=true*/ )		// SAC 1/12/15 - added bSetSoftwareVer to facilitate old project file cleanup
{
	CWaitCursor wait;

// SAC - 3/9/98
//   m_sCurrentFileName = psFileName;
//   if (!FileExists( m_sCurrentFileName ))
//   {
//      CString sErr = "Current project file '";
//      sErr += m_sCurrentFileName;
//      sErr += "' not found.  Use File / Save As option to save the project data.";
//      AfxMessageBox ( sErr );
//   }
//   else if (BEMPX_WriteProjectFile( m_sCurrentFileName, BEMFM_INPUT /*TRUE*/ ))
//   {
//      WriteToLogFile( WM_LOGUPDATED, "Project Saved" );
//
//      CDocument* pDoc = GetActiveDocument();
//      if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) )
//         pDoc->SetModifiedFlag( FALSE );
//   }
   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) )
   {
      CString sCurrentFileName = pDoc->GetPathName();

		int iLastSlash = std::max( sCurrentFileName.ReverseFind('/'), sCurrentFileName.ReverseFind('\\') );
		int iLastDot   = 		 sCurrentFileName.ReverseFind('.');
		CString sCurrExt = (iLastDot > iLastSlash ? sCurrentFileName.Right( (sCurrentFileName.GetLength() - iLastDot) ) : "");
		CString sDfltExt;		LoadFileExtensionString( sDfltExt, true /*bUseProjectData*/, (!sCurrExt.IsEmpty() && IsXMLFileExt( sCurrExt )) /*bXML*/ );			ASSERT( !sDfltExt.IsEmpty() );
		sDfltExt = '.' + sDfltExt;
		// SAC 11/2/15 - add check for valid file extension, and if OK, go ahead and save the project file even though one doesn't exist yet
      //if (!FileExists( sCurrentFileName ))
      if (!FileExists( sCurrentFileName ) && sDfltExt.CompareNoCase( sCurrExt ))
      {
         CString sErr = "Current project file '";
         sErr += sCurrentFileName;
         sErr += "' not found.  Use File / Save As option to save the project data.";
         AfxMessageBox ( sErr );
      }
      else
		{
			if (bSetSoftwareVer)		// SAC 1/12/15
			{	UpdateSoftwareVersionString();		// SAC 9/17/12
				SetBEMVersionID();						// SAC 9/17/12
			}
#ifdef UI_CARES
			long lRetainRuleDefaults = 0;
			if (ReadProgInt( "options", "ClassifyEditableDefaultsAsUserData", 1 /*default*/ ) > 0 &&
						 (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID("Proj:RetainRuleDefaults"), lRetainRuleDefaults, 0 ) || lRetainRuleDefaults == 0))	// SAC 2/4/16
				VERIFY( BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ ) >= 0 );
#endif
			bool bFileSaveAllDefinedProperties = (ReadProgInt( "options", "FileSaveAllDefinedProperties", 0 /*default*/ ) > 0);  // SAC 3/17/13
			bool bFileSaveOnlyValidInputs = (ReadProgInt( "options", "FileSaveOnlyValidInputs", 0 /*default*/ ) > 0);  // SAC 4/16/14          

			// SAC 11/2/15 - new check to cover all valid XML file extensions
			//int iFileType = (sCurrentFileName.Right(3).CompareNoCase("xml")==0 ? BEMFT_XML : BEMFT_Std);
			int iFileType = (IsXMLFileExt( sCurrExt ) ? BEMFT_XML : BEMFT_Std);
			if (BEMPX_WriteProjectFile( sCurrentFileName, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/,
													iFileType, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lModDate, bFileSaveOnlyValidInputs ))  // SAC 6/26/13
      	{
      	   WriteToLogFile( WM_LOGUPDATED, "Project Saved" );
      	   pDoc->SetModifiedFlag( FALSE );
      	}
		}
   }
}


void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

static char BASED_CODE szSaveErr1[] = "You cannot manually save Proposed or Budget databases.  ";
static char BASED_CODE szSaveErr2[] = "Select 'View' from the menu bar and switch into ";
static char BASED_CODE szSaveErr3[] = "'User Design' mode before attempting to save this file.";

static char BASED_CODE szRestoreInp[] = "The Analysis option 'Restore User Design' must be selected before this file can be saved.";

void CMainFrame::OnFileSave()
{
   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) )
   {
      CString sCurrentFileName = pDoc->GetPathName();

      if (eInterfaceMode != IM_INPUT)
      {
         CString sMsg = szSaveErr1;
         sMsg += szSaveErr2;
         sMsg += szSaveErr3;
         AfxMessageBox ( sMsg );
      }
      else if (eiCurAnalysisStep != AS_None)
      {
         AfxMessageBox ( szRestoreInp );
      }
      else
		{	BOOL bWriteUserModel = (BEMPX_GetActiveModel() == 0);		// SAC 3/24/13 - prevent storage of non-User model as normap project input file
			if (!bWriteUserModel)
			{	if (MessageBox( "The active building description is not the user input model, probably due to partial analysis being performed.\n\n"
										"Press 'OK' to save (and switch to) the user input model, or 'Cancel' to abort the save action.", NULL, MB_OKCANCEL ) == IDOK)
				{	if (!BEMPX_SetActiveModel( 0 ))
						MessageBox( "Error switching active building description to the user input model." );
					else
						bWriteUserModel = TRUE;
				}
			}
			if (bWriteUserModel)
			{
				if (sCurrentFileName.GetLength() <= 0)
      		   OnFileSaveAs();
      		else
				{	// SAC 11/2/15 - code to check for current filename having extension consistent w/ loaded ruleset, and if NOT then automatically update the extension (and inform the user)
					CString sUserMessage;		bool bInitiateSaveAs = false;
					int iLastSlash = std::max( sCurrentFileName.ReverseFind('/'), sCurrentFileName.ReverseFind('\\') );
					int iLastDot   = 		 sCurrentFileName.ReverseFind('.');
					CString sCurrExt = (iLastDot > iLastSlash ? sCurrentFileName.Right( (sCurrentFileName.GetLength() - iLastDot) ) : "");
					CString sDfltExt;		LoadFileExtensionString( sDfltExt, true /*bUseProjectData*/, (!sCurrExt.IsEmpty() && IsXMLFileExt( sCurrExt )) /*bXML*/ );			ASSERT( !sDfltExt.IsEmpty() );
					sDfltExt = '.' + sDfltExt;
					if (iLastSlash > iLastDot || iLastDot < 1)
					{	// current filename includes NO file extension, so add the default one and set message to inform user following Save
						sCurrentFileName += sDfltExt;
      	         pDoc->SetPathName( sCurrentFileName );
						sUserMessage.Format( "The prior project filename excluded a valid file extension, so the default extension (%s) has been added.  Project data saved to:\n%s", sDfltExt, sCurrentFileName );
					}
					else if (!sCurrExt.IsEmpty() && !sDfltExt.IsEmpty() && !sDfltExt.CompareNoCase( sCurrExt ))
					{	// do nothing - file extension correct as is, so move forward w/ Save action
					}
					else if (ReadProgInt( "options", "EnableStorageToCustomFileExtensions", 0 /*default*/ ) == 0)  // SAC 2/28/17 - prevent Save As when INI file allows for custom file extensions to be used (Com tic #1524)
					{	sUserMessage.Format( "The project file extension is inconsistent with the selected compliance ruleset.  File extension should be '%s'.", sDfltExt );
   	   			bInitiateSaveAs = true;
			//			CString sChkFN = sCurrentFileName.Left( iLastDot ) + sDfltExt;
			//			if (!FileExists( sChkFN ))
			//			{	// file extension needs switch and file by new name doesn't exist, so change the filename, save it and inform the user
			//				sCurrentFileName = sChkFN;
   	   //	         pDoc->SetPathName( sCurrentFileName );
			//				sUserMessage.Format( "The project file extension has been updated to reflect the selected ruleset.  Project data saved to:\n%s", sCurrentFileName );
			//			}
			//			else
			//			{	// a file already exists by the name w/ the default file extension, so initiate a SaveAs action using that new name (w/ the proper file extension)
			//				sCurrentFileName = sChkFN;
   	   //	         pDoc->SetPathName( sCurrentFileName );
			//				sUserMessage.Format( "The project file extension has been updated to reflect the selected ruleset, but a file already exists with the updated extension:\n%s", sCurrentFileName );
   	   //	         bInitiateSaveAs = true;
   	   //	   	}
   	   	   }

					if (bInitiateSaveAs)
					{	if (!sUserMessage.IsEmpty())
							AfxMessageBox ( sUserMessage );
						OnFileSaveAs();
					}
					else
					{	SaveFile( sCurrentFileName );
						if (!sUserMessage.IsEmpty())
							AfxMessageBox ( sUserMessage );
					}
			}	}
		}
   }
}


void CMainFrame::OnFileSaveAs()
{
   if (eInterfaceMode != IM_INPUT)
   {
      CString sMsg = szSaveErr1;
      sMsg += szSaveErr2;
      sMsg += szSaveErr3;
      AfxMessageBox ( sMsg );
   }
   else if (eiCurAnalysisStep != AS_None)
   {
      AfxMessageBox ( szRestoreInp );
   }
   else
   {
		BOOL bWriteUserModel = (BEMPX_GetActiveModel() == 0);		// SAC 3/24/13 - prevent storage of non-User model as normap project input file
		if (!bWriteUserModel)
		{	if (MessageBox( "The active building description is not the user input model, probably due to partial analysis being performed.\n\n"
									"Press 'OK' to save (and switch to) the user input model, or 'Cancel' to abort the save action.", NULL, MB_OKCANCEL ) == IDOK)
			{	if (!BEMPX_SetActiveModel( 0 ))
					MessageBox( "Error switching active building description to the user input model." );
				else
					bWriteUserModel = TRUE;
			}
		}
		if (bWriteUserModel)
		{
// SAC 1/3/01 - Added code to default directory & filename to current loaded file (if available)
      	CString sProjFileName;
      	CDocument* pDoc = GetActiveDocument();
      	CString sDfltExt;
      	if ( pDoc  &&  pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) )
			{
      	   sProjFileName = pDoc->GetPathName();
	      	if (sProjFileName.GetLength() > 1)
				{	// SAC 11/2/15 - further mods to help ensure use of new ruleset-specific file extensions
					int iLastSlash = std::max( sProjFileName.ReverseFind('/'), sProjFileName.ReverseFind('\\') );
					int iLastDot   = 		 sProjFileName.ReverseFind('.');
					CString sCurrExt = (iLastDot > iLastSlash ? sProjFileName.Right( (sProjFileName.GetLength() - iLastDot) ) : "");
					LoadFileExtensionString( sDfltExt, true /*bUseProjectData*/, (!sCurrExt.IsEmpty() && IsXMLFileExt( sCurrExt )) /*bXML*/ );			ASSERT( !sDfltExt.IsEmpty() );
					sDfltExt = CString('.') + sDfltExt;
					if (iLastDot <= iLastSlash)
						// no initial file extension, so add the default
						sProjFileName += sDfltExt;
					else if (!sDfltExt.IsEmpty() && sDfltExt.CompareNoCase( sCurrExt ))
						// WRONG initial file extension, so replace it with the default
						sProjFileName  = sProjFileName.Left( iLastDot ) + sDfltExt;
				}
			}
			if (sDfltExt.IsEmpty())
				LoadFileExtensionString( sDfltExt, true /*bUseProjectData*/ );

      	if (sProjFileName.GetLength() < 1)
      	{
      	   ChangeProgDir( szPaths, szProjPath );
      	   BEMPX_SetDataString( elDBID_Proj_Name, sProjFileName );
      	   RemoveIncompatibleFileNameCharacters( sProjFileName );
				sProjFileName += CString('.') + sDfltExt;		// SAC 11/2/15
      	}

//#ifdef UI_CANRES
//      	CFileDialog dlg( FALSE, _T("cibd"), sProjFileName, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
//      	                 _T("Input Files (*.cibd)|*.cibd|SDD XML Project Files (*.xml)|*.xml||"), this );
//#elif UI_CARES
//      	CFileDialog dlg( FALSE, _T("ribd"), sProjFileName, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
//      	                 _T("Input Files (*.ribd)|*.ribd|XML Project Files (*.xml)|*.xml||"), this );
//#else
//      	CFileDialog dlg( FALSE, _T("ibd"), sProjFileName, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
//      	                 _T("Input Files (*.ibd)|*.ibd|XML Project Files (*.xml)|*.xml||"), this );
//#endif
////                       _T("Input Files (*.ibd)|*.ibd||"), this );
			CString sSAFileExt, sSAFileOption;
			LoadFileExtensionString( sSAFileExt, true );
			LoadFileOptionString( sSAFileOption, true );
      	CFileDialog dlg( FALSE, (LPCTSTR) sSAFileExt, sProjFileName, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
      	                 (LPCTSTR) sSAFileOption, this );
      	if (dlg.DoModal()==IDOK)
      	{
				UpdateSoftwareVersionString();		// SAC 9/17/12
				SetBEMVersionID();						// SAC 9/17/12

				bool bFileSaveAllDefinedProperties = (ReadProgInt( "options", "FileSaveAllDefinedProperties", 0 /*default*/ ) > 0);  // SAC 3/17/13
				bool bFileSaveOnlyValidInputs = (ReadProgInt( "options", "FileSaveOnlyValidInputs", 0 /*default*/ ) > 0);  // SAC 4/16/14
				BOOL bPostInputSaveProcessing = FALSE;
      	   CString sInputFile = dlg.GetPathName();
		//		CString sExt = sInputFile.Right( 4 );
	   		int iLastDotIdx = sInputFile.ReverseFind('.');			ASSERT( iLastDotIdx > 0 );
	   		CString sExt = sInputFile.Right( sInputFile.GetLength()-iLastDotIdx );
				if (iLastDotIdx <= 0 || !FileExtensionAllowsSave( sExt ))
					// invalid or missing file extension, so append the default one
					sInputFile += sDfltExt;

				//if (sExt.CompareNoCase( ".xml" ) == 0)		// SAC 10/27/11 - testing XML project file writing
				if (IsXMLFileExt( sExt ))		// SAC 10/27/11 - testing XML project file writing
				{	CWaitCursor wait;
					// following Prog Int setting toggles writing of XML files designed for project storage (0) vs. simulation (1)
					UINT uiWriteSimExport = ReadProgInt( "options", "WriteSimulationXML", 0 );
#ifdef UI_CARES
					long lRetainRuleDefaults = 0;
					if (uiWriteSimExport == 0 && ReadProgInt( "options", "ClassifyEditableDefaultsAsUserData", 1 /*default*/ ) > 0 &&
						 (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID("Proj:RetainRuleDefaults"), lRetainRuleDefaults, 0 ) || lRetainRuleDefaults == 0))	// SAC 2/4/16
						VERIFY( BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ ) >= 0 );
#endif
      	   	if (BEMPX_WriteProjectFile( sInputFile, (uiWriteSimExport ? BEMFM_SIM : BEMFM_INPUT) /*TRUE*/, FALSE /*bUseLogFileName*/,
															bFileSaveAllDefinedProperties /*bWriteAllProperties*/, FALSE, BEMFT_XML /*iFileType*/,
															false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, -1 /*lModDate*/, bFileSaveOnlyValidInputs ))
						// add log file output and document naming stuff once available to users...
						bPostInputSaveProcessing = (uiWriteSimExport == 0);
				}
				else
				{
//#ifdef UI_CANRES
//					CString sUIExt = ".cibd";
//#elif UI_CARES
//					CString sUIExt = ".ribd";
//#else
//					CString sUIExt = ".ibd";
//#endif
					if (!IsRecognizedFileExt( sExt ))
      	   	{	CString sUIExt;
						LoadFileExtensionString( sUIExt, true );	// SAC 10/29/15
      	   	   CPathName sTempPath = sInputFile;
      	   	//   sTempPath.SetExt( sUIExt.Right( sUIExt.GetLength()-1 ) );
      	   	   sTempPath.SetExt( sUIExt );
      	   	   sInputFile = sTempPath;   // sTempPath.GetData();
      	   	}
         	
      			CWaitCursor wait;
#ifdef UI_CARES
					long lRetainRuleDefaults = 0;
					if (ReadProgInt( "options", "ClassifyEditableDefaultsAsUserData", 1 /*default*/ ) > 0 &&
						 (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID("Proj:RetainRuleDefaults"), lRetainRuleDefaults, 0 ) || lRetainRuleDefaults == 0))	// SAC 2/4/16
						VERIFY( BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ ) >= 0 );
#endif
      	   	if (BEMPX_WriteProjectFile( sInputFile, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/,
															FALSE /*bSupressAllMessageBoxes*/, 0 /*iFileType*/, false /*bAppend*/, NULL /*pszModelName*/,
															true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, -1 /*lModDate*/, bFileSaveOnlyValidInputs ))
						bPostInputSaveProcessing = TRUE;
				}

				if (bPostInputSaveProcessing)
      	   {
      	      CString sNewLogFile;
      	      const char* psLogFileName = NULL;
// SAC - 3/9/98
//    	        if (m_sCurrentFileName.CompareNoCase( sInputFile ) != 0)
//    	        {
      	         sNewLogFile = sInputFile.Left( sInputFile.ReverseFind('.')+1 );
      	         sNewLogFile += "log";
      	         psLogFileName = (const char*) sNewLogFile;
//    	        }

// SAC - 3/9/98
//    	        m_sCurrentFileName = sInputFile;

//      	      WriteToLogFile( WM_LOGUPDATED, "Project Saved", psLogFileName );
					WriteToLogFile( WM_LOGUPDATED, "-----------------------------------------------------------------------------", psLogFileName );  // SAC 1/14/17
		   		int iLastSlashIdx = std::max( sInputFile.ReverseFind('\\'), sInputFile.ReverseFind('/') );			ASSERT( iLastSlashIdx > 0 );
		   		CString sLogMsg;   sLogMsg.Format( "Project Saved as '%s'", sInputFile.Right( sInputFile.GetLength()-iLastSlashIdx-1 ) );
      	      VERIFY( BEMPX_WriteLogFile( sLogMsg, NULL, false /*bBlankFile*/ ) );

      	      // TODO: Do we need to refresh the interface?
//    	        AfxGetApp()->AddToRecentFileList( sInputFile );
      	      CDocument* pDoc = GetActiveDocument();
      	      if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) )
      	      {
      	         pDoc->SetPathName( sInputFile );
      	         pDoc->SetModifiedFlag( FALSE );
      	      }
      	   }
      	}
		}
   }
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers - Ruleset Evaluation & Analysis

afx_msg LONG CMainFrame::OnDataModified(UINT /*wEval*/, LONG lDBID)
{
	BOOL bSetDataModifiedFlag = TRUE;

	// INI setting stuff that spans all UIs
	if (eiBDBCID_INISettings > 0 && lDBID > 0 && BEMPX_GetClassID( lDBID ) == eiBDBCID_INISettings)
	{	int iError;
		BEMPropertyType* pINIPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError /*, int iBEMProcIdx=-1*/ );		ASSERT( pINIPropType );
		if (pINIPropType)
		{	CStringA sINISection = (pINIPropType->getShortName().indexOf("Proxy") >= 0 ? "proxy" : "options");		// SAC 1/5/17
			BOOL bEncodeString   = (pINIPropType->getShortName().indexOf("ProxyServerCred") >= 0);		// SAC 1/5/17
			if (pINIPropType->getPropType() == BEMP_Int || pINIPropType->getPropType() == BEMP_Sym)
			{	// for Int & Sym data - INI file settings assumed to be Integer values
				long iINIVal = 0;
				if (!BEMPX_SetDataInteger( lDBID, iINIVal, 9999 ) || iINIVal == 9999)
				{	ASSERT( FALSE );	// error retrieving INIVal from BEMProc
				}
				else
				{	VERIFY( WriteProgInt( sINISection, pINIPropType->getShortName().toLatin1().constData(), (int) iINIVal ) );
			}	}
			else if (pINIPropType->getPropType() == BEMP_Str)
			{	// for Str data - INI file settings assumed to be character strings
				CStringA sINIStr = "default-string";
				if (!BEMPX_SetDataString( lDBID, sINIStr, TRUE, 0, -1, -1, BEMO_User, "default-string" ) || sINIStr.Compare("default-string") == 0)
				{	ASSERT( FALSE );	// error retrieving INIStr from BEMProc
				}
				else
				{	CString sNewINIOptName = pINIPropType->getShortName().toLatin1().constData();
					if (bEncodeString)		// SAC 1/5/17 - string encoding for security
					{	bool bCMSecure = CMX_SecureExecutable();
						sNewINIOptName = (bCMSecure ? "Sec" : "Ins") + sNewINIOptName;  // secure vs. insecure (documenting encoding)
						char strEncoded[1024];
						memset( strEncoded, 0, sizeof(char)*1024 );
						long lEncdRet = CMX_EncodeBase64( (const unsigned char*) ((const char*) sINIStr), sINIStr.GetLength(), strEncoded, 1024, true );
						ASSERT( lEncdRet > 0 );
						if (lEncdRet > 0)
							sINIStr = strEncoded;
						else
							sINIStr.Empty();
					}
					if (!sINIStr.IsEmpty())
						VERIFY( WriteProgString( sINISection, sNewINIOptName, sINIStr ) );
			}	}
			else
			{	ASSERT( FALSE );	// unexpected INISettings property type (BEMP_Flt or BEMP_Obj) - unsure how to map to program INI settings...
		}	}
	}

#ifdef UI_CANRES
	// SAC 5/29/14 - added logic to blast PolyLp:Area whenever CartesianPt:Coord[*] modified for any of its children - enabling subsequent rule evaluation to update Area and other PolyLp data
	if (lDBID >= elDBID_CartesianPt_Coord && lDBID < (elDBID_CartesianPt_Coord+4))
	{	int iError;
		BEMObject* pCartPtObj = BEMPX_GetObjectByClass( eiBDBCID_CartesianPt, iError, -1 /*iObjIdx*/ );			ASSERT( pCartPtObj && pCartPtObj->getParent() && pCartPtObj->getParent()->getClass() );
		if (pCartPtObj && pCartPtObj->getParent() && pCartPtObj->getParent()->getClass())
		{	int iCartPtParentPolyLpObjIdx = BEMPX_GetObjectIndex( pCartPtObj->getParent()->getClass(), pCartPtObj->getParent() );		ASSERT( iCartPtParentPolyLpObjIdx >= 0 );
			if (iCartPtParentPolyLpObjIdx >= 0)
			{	// RE-default the PolyLp's Area property to ensure that the next round of defaulting will re-calculate Area & other related properties
				BEMPX_DefaultProperty( elDBID_PolyLp_Area, iError, iCartPtParentPolyLpObjIdx );
		}	}
	}
#endif

   // set flag indicating project has been modified
	if (bSetDataModifiedFlag)
		SetDataModifiedFlag( TRUE );

   return 1;
}

afx_msg LONG CMainFrame::OnUpdateTree(UINT wParam, LONG lDBIDModified)
{
   CView* pView = (CView*)m_wndSplitter.GetPane(0,0);
   if (pView != NULL)            // update main view's tree control(s)
      pView->SendMessage( WM_UPDATETREE, wParam, lDBIDModified );
   return 1;
}

afx_msg LONG CMainFrame::OnPopulateLibraryTree(UINT uiTreeMode, LONG)
{
   CView* pLibView = (CView*)m_wndSplitter.GetPane(1,0);
   if (pLibView != NULL)            // update main view's tree control(s)
      pLibView->SendMessage( WM_POPLIBTREE, uiTreeMode );
   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers - Building Database Checking

void CMainFrame::OnCheckBldgDBase() 
{	CheckBuildingModel(); 
}

void CMainFrame::CheckBuildingModel( BOOL bReportModelOK /*=TRUE*/, BOOL bPerformRangeChecks /*=TRUE*/ ) 
{
	BOOL bIsUIActive = (BEMPX_GetUIActiveFlag());		// SAC 5/2/14 - toggle messagebox display OFF for batch processing
	int iUserInpChk = BEM_UserInpChk_DisallowNotInput;
	if (ReadProgInt( "options", "DisallowPrescribedProperties", 0 /*default*/ ) > 0)		// SAC 12/29/14 - to enable more detailed checks of properties not documented in Input Data Model...
		iUserInpChk = BEM_UserInpChk_DisallowPrescribed;

   // SAC 6/4/99 - added argument to prevent properties tagged as "Required" from being reported as errors when undefined
   // SAC 1/3/01 - added 2nd argument to prevent reporting errors for properties flagged as "simulation default"
	// SAC 5/1/14 - expanded check to catch data classified as user input but that shouldn't be
   if (!BEMPX_PerformErrorCheck( FALSE /*bRequireRequiredData*/, FALSE /*bReportSimDefaultErrors*/, TRUE /*bPerformReqdClassCheck*/,
											FALSE /*bPostRangeWarnings*/, iUserInpChk /*iUserInpChk*/, bPerformRangeChecks ))
   {  // report errors (if any occurred)
      ASSERT( BEMPX_GetNumErrors() > 0 );

		if (bIsUIActive)
		{	CDlgBDBErrors errDlg( NULL, this );
			errDlg.DoModal();
		}
   }
   else if (bReportModelOK && bIsUIActive)
      MessageBox( "Building Model OK." );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers - Ruleset Evaluation & Analysis

typedef struct
{  char*       sINIOptionName;
   char*       sOptionName;
   int         iDefaultVal;
} AnalysisOption;

BOOL CMainFrame::PopulateAnalysisOptionsString( CString& sOptionsCSVString, bool bBatchMode )		// SAC 1/29/14
{	BOOL bRetVal = TRUE;
	sOptionsCSVString.Empty();
	CString sOptTemp;

	// SAC 9/5/13 - added proxy server INI options (spanning both -Res & -Com versions
		CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
		if (ReadProgInt( "proxy", "UseProxyServerSettings", 1 /*default*/ ) > 0)		// SAC 8/12/14
		{	sProxyServerAddress		= ReadProgString( "proxy", "ProxyServerAddress"    , "", FALSE );
			//sProxyServerCredentials	= ReadProgString( "proxy", "ProxyServerCredentials", "", FALSE );
			GetEncodedSetting( "proxy", "ProxyServerCredentials", sProxyServerCredentials );
			sProxyServerType      	= ReadProgString( "proxy", "ProxyServerType"       , "", FALSE );
		}
		CString sProxyINIOptions, sProxyTemp;
		if (!sProxyServerAddress.IsEmpty())
			sProxyINIOptions.Format( "ProxyServerAddress,\"%s\",", sProxyServerAddress );
		if (!sProxyServerCredentials.IsEmpty())
		{	sProxyTemp.Format( "ProxyServerCredentials,\"%s\",", sProxyServerCredentials );
			sProxyINIOptions += sProxyTemp;
		}
		if (!sProxyServerType.IsEmpty())
		{	sProxyTemp.Format( "ProxyServerType,\"%s\",", sProxyServerType );
			sProxyINIOptions += sProxyTemp;
		}
		CString sNetComLibrary;		// SAC 11/5/15
		sNetComLibrary = "";   // SAC 1/4/17 - no longer an option - ReadProgString( "proxy", "NetComLibrary", "", FALSE );
		if (!sNetComLibrary.IsEmpty())
		{	sProxyTemp.Format( "NetComLibrary,%s,", sNetComLibrary );
			sProxyINIOptions += sProxyTemp;
		}

		CString sDebugRuleEvalCSV = ReadProgString( "options", "DebugRuleEvalCSV", "", TRUE );		// SAC 12/12/13 - added ability to specify targeted rule eval debug info
		CString sDebugRuleEvalCSVNoPath = ReadProgString( "options", "DebugRuleEvalCSV", "", FALSE );	// SAC 12/4/14 - mod to prevent path-only file references from showing up in analysis options
		if (!sDebugRuleEvalCSVNoPath.IsEmpty() && !sDebugRuleEvalCSV.IsEmpty() && FileExists( sDebugRuleEvalCSV ))
			sDebugRuleEvalCSV = "DebugRuleEvalCSV,\"" + sDebugRuleEvalCSV + CString("\",");
		else
			sDebugRuleEvalCSV.Empty();

		CComplianceUIApp* pApp = (CComplianceUIApp*)AfxGetApp();  // SAC 11/11/13 - moved outside sector-specific sections
		BOOL bPerformSimulations = pApp->PerformSimulations();		
		bPerformSimulations &= (m_bDoingSummaryReport == FALSE);  // SAC 6/19/13

	// SAC 4/5/15 - added new option to disable analysis Abort button
		if (!BEMPX_GetUIActiveFlag())
			sOptionsCSVString = "AllowAnalysisAbort,0,";

#ifdef UI_CANRES
		AnalysisOption saCECNonResAnalOpts[] =	{	{  "LogRuleEvaluation"           ,  "Verbose"                     ,    0   },
																{  "MaxNumErrorsReportedPerType" ,  "MaxNumErrorsReportedPerType" ,    5   },
																{  "BypassInputChecks"           ,  "BypassInputChecks"           ,    0   },
																{  "BypassUMLHChecks"            ,  "BypassUMLHChecks"            ,    0   },
																{  "BypassCheckSimRules"         ,  "BypassCheckSimRules"         ,    0   },
																{  "BypassCheckCodeRules"        ,  "BypassCheckCodeRules"        ,    0   },
																{  "BypassValidFileChecks"       ,  "BypassValidFileChecks"       ,    0   },  // SAC 11/11/13
																{  "StoreBEMDetails"             ,  "StoreBEMDetails"             ,    0   },
																{  "DurationStats"               ,  "DurationStats"               ,    0   },
																{  "AnalysisThruStep"            ,  "AnalysisThruStep"            ,  100   },  // or 11 (?)
																{  "BypassOpenStudio_zp"         ,  "BypassOpenStudio_zp"         ,    0   },
																{  "BypassOpenStudio_zb"         ,  "BypassOpenStudio_zb"         ,    0   },
																{  "BypassOpenStudio_ap"         ,  "BypassOpenStudio_ap"         ,    0   },
																{  "BypassOpenStudio_ab"         ,  "BypassOpenStudio_ab"         ,    0   },
																{  "BypassOpenStudio_all"        ,  "BypassOpenStudio_all"        ,    0   },  // SAC 12/9/14
													//			{  "BypassSimulation_pz"         ,  "BypassSimulation_pz"         ,    (bPerformSimulations ? 0 : 1)   },
													//			{  "BypassSimulation_bz"         ,  "BypassSimulation_bz"         ,    (bPerformSimulations ? 0 : 1)   },
													//			{  "BypassSimulation_p"          ,  "BypassSimulation_p"          ,    (bPerformSimulations ? 0 : 1)   },
													//			{  "BypassSimulation_b"          ,  "BypassSimulation_b"          ,    (bPerformSimulations ? 0 : 1)   },
																{  "OverrideAutosize_zp"         ,  "OverrideAutosize_zp"         ,   -1   },
																{  "OverrideAutosize_zb"         ,  "OverrideAutosize_zb"         ,   -1   },
																{  "OverrideAutosize_ap"         ,  "OverrideAutosize_ap"         ,   -1   },
																{  "OverrideAutosize_ab"         ,  "OverrideAutosize_ab"         ,   -1   },
																{  "IgnoreFileReadErrors"        ,  "IgnoreFileReadErrors"        ,    0   },  // SAC 6/28/13
																{  "DontAbortOnErrorsThruStep"   ,  "DontAbortOnErrorsThruStep"   ,    0   },  // SAC 7/25/13
																{  "PurgeUnreferencedObjects"    ,  "PurgeUnreferencedObjects"    ,    1   },  // SAC 8/12/13
																{  "ModelRpt_ALL"                ,  "ModelRpt_ALL"                ,    0   },  // SAC 8/24/13
																{  "SendRptSignature"            ,  "SendRptSignature"            ,    1   },  // SAC 9/14/13
																{  "ComplianceReportPDF"         ,  "ComplianceReportPDF"         ,    0   },  // SAC 9/14/13
																{  "ComplianceReportXML"         ,  "ComplianceReportXML"         ,    0   },  // SAC 9/14/13
																{  "ComplianceReportStd"         ,  "ComplianceReportStd"         ,    0   },  // SAC 11/13/15
																{  "BypassRecircDHW"             ,  "BypassRecircDHW"             ,    (bPerformSimulations ? 0 : 1)   },  // SAC 11/11/13
																{  "SimulationStorage"           ,  "SimulationStorage"           ,    1   },  // SAC 1/23/14
																{  "AnalysisStorage"             ,  "AnalysisStorage"             ,    2   },  // SAC 1/23/14
																{  "FileSaveOnlyValidInputs"     ,  "FileSaveOnlyValidInputs"     ,    0   },  // SAC 4/18/14
																{  "ParallelSimulations"         ,  "ParallelSimulations"         ,    1   },  // SAC 4/18/14
																{  "LogWritingMode"         		,  "LogWritingMode"         		,    2   },  // SAC 5/20/14
																{  "LogReportRuleEvaluation"     ,  "LogReportRuleEvaluation" 		,    0   },  // SAC 5/20/14
                                                {  "ExportHourlyResults_All"     ,  "ExportHourlyResults_All"     ,    0   },  // SAC 8/21/14 - hourly results export
                                                {  "ExportHourlyResults_ap"      ,  "ExportHourlyResults_ap"      ,    0   },  // SAC 8/21/14
                                                {  "ExportHourlyResults_ab"      ,  "ExportHourlyResults_ab"      ,    0   },  // SAC 8/21/14
                                                {  "QuickAnalysis"               ,  "QuickAnalysis"               ,   -1   },  // SAC 11/8/14
                                                {  "WriteRulePropsToResultsXML"  ,  "WriteRulePropsToResultsXML"  ,    0   },  // SAC 1/12/15		// SAC 2/18/15 - toggled default to 0
                                                {  "EnableRptGenStatusChecks"    ,  "EnableRptGenStatusChecks"    ,    1   },  // SAC 2/20/15
                                                {  "LogRecircDHWSimulation"      ,  "LogRecircDHWSimulation"      ,    0   },  // SAC 6/4/15
                                                {  "SimOutputVariablesToCSV_All" ,  "SimOutputVariablesToCSV_All" ,    0   },  // SAC 4/11/16 - using ReadVarsESO to export E+ output variables to CSV file(s)
                                                {  "SimOutputVariablesToCSV_ap"  ,  "SimOutputVariablesToCSV_ap"  ,    0   },  // SAC 4/11/16
                                                {  "SimOutputVariablesToCSV_ab"  ,  "SimOutputVariablesToCSV_ab"  ,    0   },  // SAC 4/11/16
                                                {  "SimOutputVariablesToCSV_zp"  ,  "SimOutputVariablesToCSV_zp"  ,    0   },  // SAC 4/11/16
                                                {  "SimOutputVariablesToCSV_zb"  ,  "SimOutputVariablesToCSV_zb"  ,    0   },  // SAC 4/11/16
																{  NULL, NULL, -1  }  };

		int iAnalOptIdx = -1;
		while (saCECNonResAnalOpts[++iAnalOptIdx].sINIOptionName != NULL)
		{	int iOpt = ReadProgInt( "options", saCECNonResAnalOpts[iAnalOptIdx].sINIOptionName, saCECNonResAnalOpts[iAnalOptIdx].iDefaultVal );
			if (iOpt != saCECNonResAnalOpts[iAnalOptIdx].iDefaultVal)
			{	sOptTemp.Format( "%s,%d,", saCECNonResAnalOpts[iAnalOptIdx].sOptionName, iOpt );
				sOptionsCSVString += sOptTemp;
			}
		}
      if (ReadProgInt( "options",   "PromptUserUMLHWarning",   1 /*default*/ ) > 0)		// SAC 3/11/15 - special handling since CBECC-Com default = 1 while CompMgr analysis routine default is 0
         sOptionsCSVString +=       "PromptUserUMLHWarning,1,";
	// new, valid, temporary (?) option:  WriteUMLHViolationsToFile - default to 1		// SAC 3/18/15

      int iCompReportWarningOption = ReadProgInt( "options", "CompReportWarningOption", (bBatchMode ? 0 : 5) /*default*/ );
      if (iCompReportWarningOption >= 0)		// SAC 7/5/16 - pass regardless of value, since default varies by mode
			{	sOptTemp.Format( "CompReportWarningOption,%d,", iCompReportWarningOption );
				sOptionsCSVString += sOptTemp;
			}

	// Add loop to check/add rule-based reporting options based on the enumerations currently available in the ruleset data model
		long lDBID_Proj_RuleReportType = BEMPX_GetDatabaseID( "RuleReportType", BEMPX_GetDBComponentID( "Proj" ) );					ASSERT( lDBID_Proj_RuleReportType > 0 );
		if (lDBID_Proj_RuleReportType > 0)
		{	// load array of possible enumerations (report types)
			int iNumSyms;		long iSymValue;
			CStringArray saRuleReportTypeEnums;
	//		CArray<BEMSymbol*, BEMSymbol*>* pSymArray = BEMPX_GetSymbolListPointer( iNumSyms, lDBID_Proj_RuleReportType );		ASSERT( pSymArray );
			BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, lDBID_Proj_RuleReportType );		ASSERT( pSymDepSet );
			if (pSymDepSet)
			{	for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
	//			{	CString str = BEMPX_GetSymbolData( iSymValue, pSymArray, iSymIdx );
				{	QString qstr;
					BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet, iSymIdx );
					if (qstr.length() > 0)
					{	int iOpt = ReadProgInt( "options", qstr.toLatin1().constData(), 0 );
						if (iOpt > 0)
						{	sOptTemp.Format( "%s,%d,", qstr.toLatin1().constData(), iOpt );
							sOptionsCSVString += sOptTemp;
			}	}	}	}
		}

		if (!sProxyINIOptions.IsEmpty())		// SAC 9/5/13 - add proxy server settings
			sOptionsCSVString += sProxyINIOptions;
		if (!sDebugRuleEvalCSV.IsEmpty())  // SAC 1/9/14 - mods to share rule debug CSV INI option accross res & com
			sOptionsCSVString += sDebugRuleEvalCSV;

	// SAC 1/25/14 - added new INI option to force simulation of a certain IDF file, regardless of the model/OSM(s) generated during analysis
		CString sIDFToSimulate, sIDFToSimfromINI = ReadProgString( "options", "IDFToSimulate", "", TRUE );
		CString sIDFToSimfromININoPath = ReadProgString( "options", "IDFToSimulate", "", FALSE );		// SAC 12/4/14 - mod to prevent path-only file references from getting passed as analyis options
		if (!sIDFToSimfromININoPath.IsEmpty() && !sIDFToSimfromINI.IsEmpty() && FileExists( sIDFToSimfromINI ))
		{	sIDFToSimulate.Format( "IDFToSimulate,\"%s\",", sIDFToSimfromINI );
			sOptionsCSVString += sIDFToSimulate;
		}

		bBatchMode;		// otherwise unreferenced - any differences to AnalOpts for batch mode ??

#elif UI_CARES

		CString sTemp;
		if (!bBatchMode)
		{	// only specify FullComplianceAnalysis option if NOT in batch mode
			long lAnalysisType;
			VERIFY( BEMPX_SetDataInteger( elDBID_Proj_AnalysisType, lAnalysisType ) );   // SAC 9/12/11
			ASSERT( lAnalysisType == 0 || lAnalysisType == 12 || lAnalysisType == 13 ||  // 0-Research, 12-ProposedOnly, 13-PropAndStd
					  lAnalysisType == 2 );	// SAC 10/26/16 - 2-Existing Building EDR
			BOOL bFullComplianceAnalysis = (lAnalysisType == 13);
			if (!bFullComplianceAnalysis)		// default in ...Analysis...() routine switched to TRUE
				sOptionsCSVString += "FullComplianceAnalysis,0,";
		}

		int iVerbose = ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ );
		BOOL bStoreBEMProcDetails = (ReadProgInt( "options", "StoreBEMDetails", 0) > 0);
		//BOOL bPerformSimulations = (m_bDoingSummaryReport == FALSE);  // SAC 6/19/13

		//if (!bInitHourlyResults)
		//	sOptionsCSVString += "InitHourlyResults,0,";
		if (bStoreBEMProcDetails)
			sOptionsCSVString += "StoreBEMProcDetails,1,";
		if (iVerbose > 0)
		{	sTemp.Format( "Verbose,%d,", iVerbose );
			sOptionsCSVString += sTemp;
		}
		//if (!bPerformRangeChecks)
		//	sOptionsCSVString += "PerformRangeChecks,0,";
		if (!bPerformSimulations)
			sOptionsCSVString += "PerformSimulations,0,";
		//if (bDurationStats)
		//	sOptionsCSVString += "DurationStats,1,";
      // more recent options:
		if (ReadProgInt( "options",	"BypassCSE", 0 /*default*/ ) > 0)
			sOptionsCSVString +=			"BypassCSE,1,";
		if (ReadProgInt( "options",	"BypassDHW", 0 /*default*/ ) > 0)
			sOptionsCSVString +=			"BypassDHW,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_All",   0 /*default*/ ) > 0)		// SAC 9/5/13
         sOptionsCSVString +=       "ExportHourlyResults_All,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_u",   0 /*default*/ ) > 0)		// SAC 8/5/13
         sOptionsCSVString +=       "ExportHourlyResults_u,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_p",   0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_p,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_p_N", 0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_p_N,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_p_E", 0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_p_E,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_p_S", 0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_p_S,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_p_W", 0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_p_W,1,";
      if (ReadProgInt( "options",   "ExportHourlyResults_s",   0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ExportHourlyResults_s,1,";
      if (ReadProgInt( "options",   "ComplianceReportPDF",     0 /*default*/ ) > 0)		// SAC 8/14/13
         sOptionsCSVString +=       "ComplianceReportPDF,1,";
      if (ReadProgInt( "options",   "ComplianceReportXML",     0 /*default*/ ) > 0)
         sOptionsCSVString +=       "ComplianceReportXML,1,";
      if (ReadProgInt( "options",   "SendRptSignature",        1 /*default*/ ) < 1)		// SAC 9/12/13
         sOptionsCSVString +=       "SendRptSignature,0,";
		if (!sProxyINIOptions.IsEmpty())		// SAC 9/5/13 - add proxy server settings
			sOptionsCSVString += sProxyINIOptions;
		if (!sDebugRuleEvalCSV.IsEmpty())  // SAC 1/9/14 - mods to share rule debug CSV INI option accross res & com
			sOptionsCSVString += sDebugRuleEvalCSV;
    //  if (ReadProgInt( "options",   "BypassRuleLimits",     0 /*default*/ ) > 0)		// SAC 3/11/14 - when =1 should cause certain rule-based compliance checks/limits to be bypassed
    //     sOptionsCSVString +=       "BypassRuleLimits,1,";
      int iBypassRuleLimits = ReadProgInt( "options", "BypassRuleLimits", 0 /*default*/ );	// SAC 4/20/15 - switched BypassRuleLimits from boolean to integer (to allow values > 1)
		if (iBypassRuleLimits > 0)
		{	sOptTemp.Format( "BypassRuleLimits,%d,", iBypassRuleLimits );
			sOptionsCSVString += sOptTemp;
		}
      int iEnableResearchMode = ReadProgInt( "options", "EnableResearchMode", 0 /*default*/ );	// SAC 5/14/16 - 
		if (iEnableResearchMode > 0)
		{	sOptTemp.Format( "EnableResearchMode,%d,", iEnableResearchMode );
			sOptionsCSVString += sOptTemp;
		}
      if (ReadProgInt( "options",   "BypassValidFileChecks",     0 /*default*/ ) > 0)		// SAC 5/3/14
         sOptionsCSVString +=       "BypassValidFileChecks,1,";
		if (!ebAnalysisRangeChecks)
         sOptionsCSVString +=       "PerformRangeChecks,0,";
      if (ReadProgInt( "options",   "PerformDupObjNameCheck",     1 /*default*/ ) < 1)		// SAC 2/23/15
         sOptionsCSVString +=       "PerformDupObjNameCheck,0,";
      int iSimSpeedOption = ReadProgInt( "options", "SimSpeedOption", -1 /*default*/ );	// SAC 1/14/15
		if (iSimSpeedOption >= 0)
		{	sOptTemp.Format( "SimSpeedOption,%d,", iSimSpeedOption );
			sOptionsCSVString += sOptTemp;
		}
      int iLogWritingMode = ReadProgInt( "options", "LogWritingMode", 1000 /*default*/ );		// SAC 5/20/14
		if (iLogWritingMode != 1000)
		{	sOptTemp.Format( "LogWritingMode,%d,", iLogWritingMode );
			sOptionsCSVString += sOptTemp;
		}
      int iSimLoggingOption = ReadProgInt( "options", "SimLoggingOption", 0 /*default*/ );	// SAC 1/12/15
		if (iSimLoggingOption > 0)
		{	sOptTemp.Format( "SimLoggingOption,%d,", iSimLoggingOption );
			sOptionsCSVString += sOptTemp;
		}
      int iSimReportDetailsOption = ReadProgInt( "options", "SimReportDetailsOption", 1 /*default*/ );	// SAC 1/12/15
		if (iSimReportDetailsOption != 1)
		{	sOptTemp.Format( "SimReportDetailsOption,%d,", iSimReportDetailsOption );
			sOptionsCSVString += sOptTemp;
		}
      int iSimErrorDetailsOption = ReadProgInt( "options", "SimErrorDetailsOption", 1 /*default*/ );	// SAC 1/12/15
		if (iSimErrorDetailsOption != 1)
		{	sOptTemp.Format( "SimErrorDetailsOption,%d,", iSimErrorDetailsOption );
			sOptionsCSVString += sOptTemp;
		}
      int iEnableRptGenStatusChecks = ReadProgInt( "options", "EnableRptGenStatusChecks", 1 /*default*/ );	// SAC 2/20/15
		if (iEnableRptGenStatusChecks < 1)
		{	sOptTemp.Format( "EnableRptGenStatusChecks,%d,", iEnableRptGenStatusChecks );
			sOptionsCSVString += sOptTemp;
		}
      int iStoreResultsToModelInput = ReadProgInt( "options", "StoreResultsToModelInput", 1 /*default*/ );	// SAC 5/12/15
		if (iStoreResultsToModelInput > 0)
		{	sOptTemp.Format( "StoreResultsToModelInput,%d,", iStoreResultsToModelInput );
			sOptionsCSVString += sOptTemp;
		}
      int iDHWCalcMethod = ReadProgInt( "options", "DHWCalcMethod", -1 /*default*/ );	// SAC 7/14/15
		if (iDHWCalcMethod >= 0)
		{	sOptTemp.Format( "DHWCalcMethod,%d,", iDHWCalcMethod );
			sOptionsCSVString += sOptTemp;
		}

#endif

	return bRetVal;
}

// returns:  sRptList populated w/ each report abbrev & return value equal total number of reports to be generated
int CMainFrame::CheckWhichReportsToGenerate( CString& sRptList )	// SAC 2/19/15		// SAC 11/13/15
{	int iRetVal = 0;
	long lRptPDF=0, lRptFull=0, lRptStd=0;

#ifdef UI_CANRES
	if (ReadProgInt( "options", "ComplianceReportPDF", 0 /*default*/ ) > 0 ||
			(BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompReportPDF" ), lRptPDF ) && lRptPDF > 0))
	{	lRptPDF  = 1;	iRetVal++;	}
	if (ReadProgInt( "options", "ComplianceReportXML", 0 /*default*/ ) > 0 ||
			(BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompReportXML" ), lRptFull ) && lRptFull > 0))
	{	lRptFull = 1;	iRetVal++;	}
	if (ReadProgInt( "options", "ComplianceReportStd", 0 /*default*/ ) > 0 ||
			(BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompReportStd" ), lRptStd ) && lRptStd > 0))
	{	lRptStd  = 1;	iRetVal++;	}
#elif UI_CARES
	long lAnalType=0;
	if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:AnalysisType" ), lAnalType ) && lAnalType != 13)
		return 0;		// SAC 10/27/16 - ignore report gen check if analysis NOT full compliance
	if (ReadProgInt( "options", "ComplianceReportPDF", 0 /*default*/ ) > 0 ||
			(BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ComplianceReportPDF" ), lRptPDF ) && lRptPDF > 0))
	{	lRptPDF  = 1;	iRetVal++;	}
	if (ReadProgInt( "options", "ComplianceReportXML", 0 /*default*/ ) > 0 ||
			(BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ComplianceReportXML" ), lRptFull ) && lRptFull > 0))
	{	lRptFull = 1;	iRetVal++;	}
#endif

	sRptList.Empty();
	if (lRptPDF)
	{	sRptList = "PDF";
		if (lRptFull && lRptStd)
			sRptList += ", ";
		else if (lRptFull || lRptStd)
			sRptList += " and ";
	}
	if (lRptFull)
	{	sRptList += "Full/XML";
		if (lRptStd)
			sRptList += " and ";
	}
	if (lRptStd)
		sRptList += "Std";

	return iRetVal;
}


void CMainFrame::OnUpdateToolsBatchProcessing(CCmdUI* pCmdUI)		// SAC 5/22/13
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnToolsBatchProcessing()		// SAC 5/22/13
{
	BatchProcessing();
}

void CMainFrame::BatchProcessing( bool bOLDRules /*=false*/ )		// SAC 4/2/14
{
	// proxy server INI options (spanning both -Res & -Com versions
	CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
	if (ReadProgInt( "proxy", "UseProxyServerSettings", 1 /*default*/ ) > 0)		// SAC 8/12/14
	{	sProxyServerAddress		= ReadProgString( "proxy", "ProxyServerAddress"    , "", FALSE );
		//sProxyServerCredentials	= ReadProgString( "proxy", "ProxyServerCredentials", "", FALSE );
		GetEncodedSetting( "proxy", "ProxyServerCredentials", sProxyServerCredentials );
		sProxyServerType      	= ReadProgString( "proxy", "ProxyServerType"       , "", FALSE );
	}
	CString sProxyINIOptions, sProxyTemp;
	if (!sProxyServerAddress.IsEmpty())
		sProxyINIOptions.Format( "ProxyServerAddress,\"%s\",", sProxyServerAddress );
	if (!sProxyServerCredentials.IsEmpty())
	{	sProxyTemp.Format( "ProxyServerCredentials,\"%s\",", sProxyServerCredentials );
		sProxyINIOptions += sProxyTemp;
	}
	if (!sProxyServerType.IsEmpty())
	{	sProxyTemp.Format( "ProxyServerType,\"%s\",", sProxyServerType );
		sProxyINIOptions += sProxyTemp;
	}
	CString sNetComLibrary;		// SAC 11/5/15
	sNetComLibrary = "";   // SAC 1/4/17 - no longer an option - ReadProgString( "proxy", "NetComLibrary", "", FALSE );
	if (!sNetComLibrary.IsEmpty())
	{	sProxyTemp.Format( "NetComLibrary,\"%s\",", sNetComLibrary );
		sProxyINIOptions += sProxyTemp;
	}
	CString sTemp, sOptionsCSVString;

#ifdef UI_CANRES
   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (((CComplianceUIDoc*) pDoc)->CUISaveModified( "batch processing" )) )
   {
		ChangeProgDir( szPaths, szProjPath );
		CFileDialog dlg( TRUE, _T("csv"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		                 _T("Batch Definition Files (*.csv)|*.csv||"), this );
		if (dlg.DoModal()==IDOK)
		{
			CString sBatchPathFile = dlg.GetPathName();

			//char pszRuleErr[1024];
			//CString sProcessingPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('.') );
			//CString sProjFileBase = sProcessingPath.Right( sProcessingPath.GetLength() - sProcessingPath.ReverseFind('\\') - 1 );     ASSERT( !sProjFileBase.IsEmpty() );
			//sProcessingPath += " - run\\";
			CString sBEMPathFile = ReadProgString( "files", "BEMFile", "", TRUE );
			CString sRulePathFile = ReadProgString( "paths", "RulesetPath", "", TRUE );
			sRulePathFile += ReadProgString( "files", "RulesetFile", "" );
			char pszBatchErr[1024];
			pszBatchErr[0] = '\0';

			CString sUIVersionString;
			GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );
		   CString sWthrPath = ReadProgString( "paths", "WeatherPath", "EPW\\", TRUE );
	// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
			VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString, true /*bBatchMode*/ ) );		// SAC 1/29/14

			int iBatchResult = CMX_PerformBatchAnalysis_CECNonRes(	sBatchPathFile, esProjectsPath, sBEMPathFile, sRulePathFile,
																			sWthrPath /*pszSimWeatherPath*/,
																			NULL /*pszCompMgrDLLPath*/, NULL /*pszDHWWeatherPath*/,
																		//	sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
																			NULL /*pszLogPathFile*/, sUIVersionString, 
																			sOptionsCSVString, pszBatchErr, 1024, true /*bDisplayProgress*/, GetSafeHwnd() /*HWND hWnd*/, bOLDRules );
			CString sResult;
			if (strlen( pszBatchErr ) > 0)
				sResult.Format( "CMX_PerformBatchAnalysis_CECNonRes() returned %d:\n\n%s", iBatchResult, pszBatchErr );
			else
				sResult.Format( "CMX_PerformBatchAnalysis_CECNonRes() returned %d", iBatchResult );
			AfxMessageBox( sResult );
		}
	}
#elif UI_CARES
   CDocument* pDoc = GetActiveDocument();			bOLDRules;
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (((CComplianceUIDoc*) pDoc)->CUISaveModified( "batch processing" )) )
   {
		ChangeProgDir( szPaths, szProjPath );
		CFileDialog dlg( TRUE, _T("csv"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		                 _T("Batch Definition Files (*.csv)|*.csv||"), this );
		if (dlg.DoModal()==IDOK)
		{
			CString sBatchPathFile = dlg.GetPathName();

			CString sBEMPathFile = ReadProgString( "files", "BEMFile", "", TRUE );
			CString sRulePathFile = ReadProgString( "paths", "RulesetPath", "", TRUE );
			sRulePathFile += ReadProgString( "files", "RulesetFile", "" );
			char pszBatchErr[1024];
			pszBatchErr[0] = '\0';

			CString sCSEPath = esProgramPath + "CSE\\";
			sCSEPath = ReadProgString( szPaths, "CSEPath", sCSEPath, TRUE );  // in case there is one in the INI to override the default
			CString sT24DHWPath = esProgramPath + "T24DHW\\";
			sT24DHWPath = ReadProgString( szPaths, "T24DHWPath", sT24DHWPath, TRUE );  // in case there is one in the INI to override the default

			CString sUIVersionString;
			GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );

	// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
			VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString, true /*bBatchMode*/ ) );		// SAC 1/29/14

			const char* pszAnalOpts = NULL;
			if (!sOptionsCSVString.IsEmpty())
				pszAnalOpts = (const char*) sOptionsCSVString;

			int iBatchResult = CMX_PerformBatchAnalysis_CECRes( sBatchPathFile, esProjectsPath, sBEMPathFile, sRulePathFile,
														sCSEPath, sCSEPath, sT24DHWPath, NULL /*pszDHWWeatherPath*/, NULL /*pszLogPathFile*/,
														sUIVersionString, pszAnalOpts, pszBatchErr, 1024, true /*bDisplayProgress*/,
														GetSafeHwnd() /*HWND hWnd*/, 1 /*SecKeyIndex*/, esSecurityKey );
			CString sResult;
			if (strlen( pszBatchErr ) > 0)
				sResult.Format( "CMX_PerformBatchAnalysis_CECRes() returned %d:\n\n%s", iBatchResult, pszBatchErr );
			else
				sResult.Format( "CMX_PerformBatchAnalysis_CECRes() returned %d", iBatchResult );
			AfxMessageBox( sResult );
		}
	}
#else
	AfxMessageBox( "Batch processing not available in this UI mode." );
#endif
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateFileImportModel(CCmdUI* pCmdUI)		// SAC 1/10/14
{
#ifdef UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnFileImportModel()    // SAC 1/10/14
{
#ifdef UI_CANRES
   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) && pDoc->SaveModified())
   {
      ChangeProgDir( szPaths, szProjPath );

      CFileDialog dlg( TRUE, _T("xml"), NULL, /*OFN_SHOWHELP |*/ OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                       _T("Green Building XML Files (*.xml)|*.xml|EnergyPlus Input Files (*.idf)|*.idf|OpenStudio Model Files (*.osm)|*.osm||"), this );
      if (dlg.DoModal()==IDOK && dlg.m_pOFN)
      {
         CPathName sInputFile = dlg.GetPathName(); // Copy the filename into a CPathName so we can get the extension.
			int iImpFileType = -1;
			switch (dlg.m_pOFN->nFilterIndex)
			{	case  1:	iImpFileType = CMX_OSWFT_GBXML;		break;
				case  2:	iImpFileType = CMX_OSWFT_EPlus;		break;
				case  3:	iImpFileType = CMX_OSWFT_OSM;			break;
			}
			if (iImpFileType < 0)
			{	ASSERT( FALSE );
			}
			else
			{	CString sOutputPathFile = sInputFile;
				int iLastDotIdx = sOutputPathFile.ReverseFind('.');
				if (iLastDotIdx > 0)
					sOutputPathFile = sOutputPathFile.Left( iLastDotIdx );
				sOutputPathFile += "SDD.xml";
				if (FileExists( sOutputPathFile ))
				{	// if output file already exists, prompt for new output file (w/ prompt for overwrite)
		      	CFileDialog dlgSvAs( FALSE, _T("xml"), sOutputPathFile, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
   		   	                 _T("SDD XML Project Files (*.xml)|*.xml||"), this );
      			if (dlgSvAs.DoModal()==IDOK)
      			   sOutputPathFile = dlgSvAs.GetPathName();
					else
      			   sOutputPathFile.Empty();
				}
				if (!sOutputPathFile.IsEmpty())
				{	int iImportRetVal = CMX_TranslateToSDD( sInputFile, sOutputPathFile, iImpFileType );  // SAC 1/10/14
					if (iImportRetVal != 0)
					{	ASSERT( FALSE );
					}
					else if (!FileExists( sOutputPathFile ))
					{	ASSERT( FALSE );
					}
					else
						((CComplianceUIDoc*)pDoc)->OpenTheFile( sOutputPathFile );
				}
			}
      }
	}
//#else
#endif
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateFileImportResGeometry(CCmdUI* pCmdUI)		// SAC 2/20/17
{
#ifdef UI_CARES
		long lEnergyCodeYr;
		BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYr );
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && lEnergyCodeYr > 18) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnFileImportResGeometry()    // SAC 2/20/17
{
#ifdef UI_CARES
   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) && pDoc->SaveModified())
   {
//      ChangeProgDir( szPaths, szProjPath );

		int iNumPVArraysCr8 = 0, iNumInitPVArrays = BEMPX_GetNumObjects( eiBDBCID_PVArrayGeom );
		int iNumShadesCr8   = 0, iNumInitShades   = BEMPX_GetNumObjects( eiBDBCID_Shade );
		BOOL bContinue = TRUE;
		long lEnergyCodeYr;
		BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYr );
		BOOL bPVWInputsActive = (lEnergyCodeYr >= 19);
		if (lEnergyCodeYr == 16)
		{	long lAllow, lDRCalcs;
			bPVWInputsActive = ( BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:AllowDesignRating" ), lAllow   ) && lAllow > 0 &&
				                  BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:DesignRatingCalcs" ), lDRCalcs ) && lDRCalcs > 0 );
		}

		if (iNumInitPVArrays > 0 || iNumInitShades > 0)
		{	CString sUsrMsg;
			if (iNumInitPVArrays > 0 && iNumInitShades > 0)
				sUsrMsg.Format( "%d PVArrayGeom and %d Shade objects are present in the model.", iNumInitPVArrays, iNumInitShades );
			else if (iNumInitPVArrays > 0)
				sUsrMsg.Format( "%d PVArrayGeom object(s) are present in the model.", iNumInitPVArrays );
			else
				sUsrMsg.Format( "%d Shade object(s) are present in the model.", iNumInitShades );
			sUsrMsg += "\n\nChoose 'Replace' to delete existing geometry objects before importing, or\n'Add' to add the geometry import to the existing model, or\n'Abort' to cancel the geometry import.";

			XMSGBOXPARAMS xmbp;
			sprintf( xmbp.szCustomButtons, "Replace Geometry\nAdd Geometry\nAbort Import" );
		//	xmbp.nIdIcon = uiIcon;
			int iUserChoice = XMessageBox( GetSafeHwnd(), sUsrMsg, "Add or Replace Geometry?", MB_DEFBUTTON1 | MB_ICONQUESTION, &xmbp );
			switch (iUserChoice)
			{	case IDCUSTOM1 :	{	// DELETE all existing geometry objects before importing new ones
											int iError, idx=-1;
											int* piNumObjs[] = {  &iNumInitPVArrays,     &iNumInitShades,  0  };
											int  iObjCls[]   = {  eiBDBCID_PVArrayGeom,  eiBDBCID_Shade,   0  };
											while (iObjCls[++idx] > 0)
											{	if (*piNumObjs[idx] > 0)
												{	for (int iDO = *piNumObjs[idx]-1; iDO >= 0; iDO--)
													{	BEMObject* pDObj = BEMPX_GetObjectByClass( iObjCls[idx], iError, iDO );		ASSERT( pDObj );
														if (pDObj)
															BEMPX_DeleteObject( pDObj );
													}
													*piNumObjs[idx] = 0;
											}	}
										}	break;
				case IDCUSTOM2 :	{	// do nothing - we will simply ADD new geometry to the existing model
										}	break;
				case IDCUSTOM3 :	{	bContinue = FALSE;
										}	break;
				default			:	ASSERT( FALSE );		break;
			}
		}

		if (bContinue)
		{
	      CFileDialog dlg( TRUE, _T("xml"), NULL, /*OFN_SHOWHELP |*/ OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
	                       _T("Green Building XML Files (*.xml)|*.xml||"), this );
	      if (dlg.DoModal()==IDOK && dlg.m_pOFN)
	      {
	         CPathName sInputFile = dlg.GetPathName(); // Copy the filename into a CPathName so we can get the extension.
				int iImpFileType = -1;
				switch (dlg.m_pOFN->nFilterIndex)
				{	case  1:	iImpFileType = 0;		break;
				}
				if (iImpFileType < 0)
				{	ASSERT( FALSE );
				}
				else
				{	CString sOutputPathFile = sInputFile;

					QDomDocument doc("mydocument");
					QFile file( (const char*) sOutputPathFile );
					if (!file.open(QIODevice::ReadOnly))
					    return;
					if (!doc.setContent(&file)) {
					    file.close();
					    return;
					}
					file.close();

					QDomElement docElem = doc.documentElement();

					QString qsXMLMsg = "XML contents:\n";
					int iNumCompsImported = ProcessXMLElement( Schema_GBXML, docElem, 0, qsXMLMsg );
					QString sUsrMsg;
					if (iNumCompsImported < 1)
						sUsrMsg = QString( "No compatible geometric objects found in XML file:\n   %1" ).arg( (const char*) sOutputPathFile );
					else
					{
						iNumPVArraysCr8 = BEMPX_GetNumObjects( eiBDBCID_PVArrayGeom ) - iNumInitPVArrays;
						iNumShadesCr8   = BEMPX_GetNumObjects( eiBDBCID_Shade )       - iNumInitShades;			ASSERT( iNumPVArraysCr8 > 0 || iNumShadesCr8 > 0 );
						QString sPVA = (iNumPVArraysCr8 > 1 ? "PVArrayGeoms" : "PVArrayGeom");
						QString sShd = (iNumShadesCr8   > 1 ? "Shades"       : "Shade");
						if (iNumPVArraysCr8 > 0 && iNumShadesCr8 > 0)
							sUsrMsg = QString( "%1 geometric objects (%2 %3 and %4 %5) imported from XML file:\n   %6" ).arg( QString::number(iNumCompsImported),
																		QString::number( iNumPVArraysCr8 ), sPVA, QString::number( iNumShadesCr8 ), sShd, (const char*) sOutputPathFile );
						else if (iNumPVArraysCr8 > 0)
							sUsrMsg = QString( "%1 geometric (PVArrayGeom) object(s) imported from XML file:\n   %2" ).arg( QString::number(iNumPVArraysCr8), (const char*) sOutputPathFile );
						else
							sUsrMsg = QString( "%1 geometric (Shade) object(s) imported from XML file:\n   %2" ).arg( QString::number(iNumShadesCr8), (const char*) sOutputPathFile );

// TO DO - if PV arrays defined and any do not have specific locations then add to message -> "\n\nLocation details must be specified for all PV arrays in order to perform analysis on model containing Shade objects."

#ifdef _DEBUG
						sUsrMsg += "\n\n";	sUsrMsg += qsXMLMsg;
#endif
					}

					BOOL bInstallOverwrite = FALSE;
					BOOL bInstallAppend = FALSE;
					CArray<int,int> iaPVGeomAdds;
					if (iNumPVArraysCr8 < 1 || !bPVWInputsActive)
						BEMMessageBox( sUsrMsg );  // present dialog w/ summary of components read from gbXML file
					else
					{	CArray<int,int> iaCFI, iaDet, iaDetPVGeom;
						long lPVWInps, lCFI, lGSM;  double dDCSz;
						int iMaxIdx = (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:PVWInputs" ), lPVWInps ) && lPVWInps > 0) ? 4 : 0;
						for (int idx=0; idx<=iMaxIdx; idx++)
						{	if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:PVWDCSysSize" )+idx, dDCSz ) && dDCSz > 0)
							{	if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:PVWCalFlexInstall" )+idx, lCFI ) && lCFI > 0)
									iaCFI.Add(idx);
								else if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:PVWGeomSpecMethod" )+idx, lGSM ) && lGSM > 0)
									iaDetPVGeom.Add(idx);
								else
									iaDet.Add(idx);
						}	}

						if (lPVWInps == 0 || (iaCFI.GetSize() < 1 && iaDetPVGeom.GetSize() < 1 && iaDet.GetSize() < 1))
						{	// PV inputs = 'Simplified' => no geometry present for any PV item
							QString sPVItems = (iNumPVArraysCr8 > 5 ? "first 5 imported PVArrayGeom objects as PV systems" : 
													 (iNumPVArraysCr8 == 1 ? "imported PVarrayGeom object as a PV system" : QString( "%1 imported PVArrayGeom objects as PV systems" ).arg( QString::number( iNumPVArraysCr8 ) ) ));
							QString sPVMode = (lPVWInps == 0 ? " switch project into Detailed PV input mode and " : " ");
							sUsrMsg += QString( "\n\nChoose 'Install' to%1add the %2, or\n"
													  "'Skip Install' to return to the user interface." ).arg( sPVMode, sPVItems );
							XMSGBOXPARAMS xmbp;
							sprintf( xmbp.szCustomButtons, "Install PV Arrays\nSkip Install" );
						//	xmbp.nIdIcon = uiIcon;
							int iUserChoice = XMessageBox( GetSafeHwnd(), sUsrMsg.toLatin1().constData(), "Further Geometry Processing", MB_DEFBUTTON1 | MB_ICONQUESTION, &xmbp );
							switch (iUserChoice)
							{	case IDCUSTOM1 :	{	// Install new PV arrays to project PVW inputs...
															bInstallOverwrite = TRUE;
														}	break;
								case IDCUSTOM2 :	{	// do nothing - return to the UI
														}	break;
								default			:	ASSERT( FALSE );		break;
						}	}
						else
						{	// more complex options
							int iPossibleToAppend = 5 - iaCFI.GetSize() - iaDetPVGeom.GetSize() - iaDet.GetSize();
							sUsrMsg += "\n\nSummary of current PV array inputs:\n";
							if (iaCFI.GetSize() > 0)
								sUsrMsg += QString( "   %1 array(s) defined as CFI (w/ no geometry)\n" ).arg( QString::number( iaCFI.GetSize() ) );
							if (iaDetPVGeom.GetSize() > 0)
								sUsrMsg += QString( "   %1 array(s) that already reference PVArrayGeom geometry\n" ).arg( QString::number( iaDetPVGeom.GetSize() ) );
							if (iaDet.GetSize() > 0)
								sUsrMsg += QString( "   %1 array(s) that could be described using PVArrayGeom geometry\n" ).arg( QString::number( iaDet.GetSize() ) );

							if (iNumInitShades > 0 || iNumShadesCr8 > 0)
								sUsrMsg += "\nNote: All PV arrays must be defined with 3D geometry when Shade objects are defined (as is the case currently for this model).\n";

							QString sPVItems = (iNumPVArraysCr8 > 5 ? "first 5 imported PVArrayGeom objects as PV systems" : 
													 (iNumPVArraysCr8 == 1 ? "imported PVarrayGeom object as a PV system" : QString( "%1 imported PVArrayGeom objects as PV systems" ).arg( QString::number( iNumPVArraysCr8 ) ) ));
							sUsrMsg += QString( "\nChoose 'Replace' to overwrite existing PV array inputs with the %1, or\n" ).arg( sPVItems );
							if (iPossibleToAppend > 0)
							{	QString sAppPVItems = (iNumPVArraysCr8 > iPossibleToAppend ? QString( "first %1 imported PVArrayGeom objects as PV systems" ).arg( QString::number( iPossibleToAppend ) ) : 
															 (iNumPVArraysCr8 == 1 ? "imported PVarrayGeom object as a PV system" : QString( "%1 imported PVArrayGeom objects as PV systems" ).arg( QString::number( iNumPVArraysCr8 ) ) ));
								sUsrMsg += QString( "'Append' to add the %1 (leaving existing PV inputs as is), or\n" ).arg( sAppPVItems );
							}
							sUsrMsg += "'Skip Install' to return to the user interface.";

							XMSGBOXPARAMS xmbp;
							if (iPossibleToAppend > 0)
								sprintf( xmbp.szCustomButtons, "Replace PV Arrays\nAppend PV Arrays\nSkip Install" );
							else
								sprintf( xmbp.szCustomButtons, "Replace PV Arrays\nSkip Install" );
						//	xmbp.nIdIcon = uiIcon;
							int iUserChoice = XMessageBox( GetSafeHwnd(), sUsrMsg.toLatin1().constData(), "Further Geometry Processing", MB_DEFBUTTON1 | MB_ICONQUESTION, &xmbp );
							switch (iUserChoice)
							{	case IDCUSTOM1 :	{	// Install new PV arrays to project PVW inputs...
															bInstallOverwrite = TRUE;
														}	break;
								case IDCUSTOM2 :	{	// Append or Skip
															if (iPossibleToAppend > 0)
																bInstallAppend = TRUE;
														}	break;
								case IDCUSTOM3 :	{	// do nothing - return to the UI
														}	break;
								default			:	ASSERT( FALSE );		break;
						}	}

						if (bInstallOverwrite || bInstallAppend)
						{	SendMessage( WM_EVALPROPOSED /*, (!bWriteToLog)*/ );  // default model...
							// first toggle PVWInputs to 'Detailed' (if necessary)
							if (lPVWInps == 0)
							{	lPVWInps = 1;
								VERIFY( BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:PVWInputs" ), BEMP_Int, (void*) &lPVWInps ) >= 0 );
							}
							// then install PV array data
							long lZero = 0, lGSMPV = 1;		double dZeroPt1 = 0.1;
							int iError, iPVGeomIdx = iNumInitPVArrays;
							BOOL bDoneInstallingPVs = FALSE;
							for (int idx=0; (!bDoneInstallingPVs && idx < 5); idx++)
							{	if (bInstallOverwrite || (BEMPX_GetFloat( BEMPX_GetDatabaseID( "Proj:PVWDCSysSize" )+idx, dDCSz ) && dDCSz < 0.01))
								{
									BEMObject* pPVAGObj = BEMPX_GetObjectByClass( eiBDBCID_PVArrayGeom, iError, iPVGeomIdx++ );		ASSERT( pPVAGObj );
									if (pPVAGObj)
									{	// toggle ON this PV array by entering a very small PV DC SysSize
										if (BEMPX_GetFloat(          BEMPX_GetDatabaseID( "Proj:PVWDCSysSize"      )+idx, dDCSz ) && dDCSz < 0.01)
											VERIFY( BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:PVWDCSysSize"      )+idx, BEMP_Flt, (void*) &dZeroPt1 ) >= 0 );
										// if this element is flagged as CFI, then remove that
										if (BEMPX_SetDataInteger(    BEMPX_GetDatabaseID( "Proj:PVWCalFlexInstall" )+idx, lCFI ) && lCFI > 0)
											VERIFY( BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:PVWCalFlexInstall" )+idx, BEMP_Int, (void*) &lZero ) >= 0 );
										// then set GeomSpecMethod to "reference PVArrayGeom object" (1)
										VERIFY( BEMPX_SetBEMData(    BEMPX_GetDatabaseID( "Proj:PVWGeomSpecMethod" )+idx, BEMP_Int, (void*) &lGSMPV ) >= 0 );
										// and install reference to newly-imported PV array
										VERIFY( BEMPX_SetBEMData(    BEMPX_GetDatabaseID( "Proj:PVWPVArrGeomRef"   )+idx, BEMP_Obj, (void*) pPVAGObj ) >= 0 );

										iaPVGeomAdds.Add( idx+1 );
										bDoneInstallingPVs = ((iPVGeomIdx - iNumInitPVArrays) == iNumPVArraysCr8);
									}
							}	}
						}
						if (iaPVGeomAdds.GetSize() > 0)
						{	// inform user of PV installs and the need to enter additional PV system inputs
							sUsrMsg = QString( "%1 PV array geometry object(s) have been installed as PV systems. Visit the PV tab of the Project Data tabbed dialog "
													 "to specify other required data to ensure proper PV simulation." ).arg( QString::number( iaPVGeomAdds.GetSize() ) );
							BEMMessageBox( sUsrMsg );  
						}
					}

					SendMessage( WM_EVALPROPOSED /*, (!bWriteToLog)*/ );
					pDoc->SetModifiedFlag( TRUE );
		         CMainView* pMainView = (CMainView*) m_wndSplitter.GetPane(0,0);
		         if (pMainView != NULL)            // update main view's tree control(s)
		         {
//#ifdef UI_CARES
						pMainView->SendMessage( WM_UPDATETREE, 0, elDBID_Proj_IsMultiFamily );		// SAC 7/29/16 - ensure access/non-access to DwellUnit* objects based on whether model is multifamily
//#endif
		            pMainView->SendMessage( WM_DISPLAYDATA );

						if (iaPVGeomAdds.GetSize() > 0)
						{	int iTabCtrlWd, iTabCtrlHt, iBDBClass = eiBDBCID_Proj;
							VERIFY( GetDialogTabDimensions( iBDBClass, iTabCtrlWd, iTabCtrlHt ) );
							CString sDialogCaption;
							GetDialogCaption( iBDBClass, sDialogCaption );   // SAC 1/8/12
			            CSACBEMProcDialog td( iBDBClass, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), this,
			                              0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, BEMPUIX_GetNumConsecutiveDialogTabIDs( iBDBClass, 0 /*iUIMode*/ ) /*iMaxTabs*/,
			                              (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
													NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
													NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
													ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
			            if (td.DoModal() == IDOK)
			            {}
						}

		            //CView* pLibView = (CView*) m_wndSplitter.GetPane(1,0);
		            //if (pLibView != NULL)            // update main view's tree control(s)
		            //   pLibView->SendMessage( WM_POPLIBTREE, eiCurrentTab );
		         }
			}	}
		}
	}
//#else
#endif
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsGenerateFileHashes(CCmdUI* pCmdUI)		// SAC 9/2/13
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnToolsGenerateFileHashes()		// SAC 9/2/13
{
		ChangeProgDir( esProgramPath );
		CFileDialog dlg( TRUE, _T("csv"), NULL, OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		                 _T("File Listing CSV Files (*.csv)|*.csv||"), this );
		if (dlg.DoModal()==IDOK)
		{
			CString sHashFileListCSVPathFile = dlg.GetPathName();
			CString sHashOutputPathFile = sHashFileListCSVPathFile.Left( sHashFileListCSVPathFile.ReverseFind('.') );
			sHashOutputPathFile += " - out.csv";

			int iFileHashResult = CMX_GenerateFileHashesFromCSV( sHashFileListCSVPathFile, sHashOutputPathFile, esProgramPath );

			CString sResult;
			if (iFileHashResult >= 0)
				sResult.Format( "CMX_GenerateFileHashesFromCSV() returned - %d file hashes generated.", iFileHashResult );
			else
				sResult.Format( "CMX_GenerateFileHashesFromCSV() returned error code %d ", iFileHashResult );
			AfxMessageBox( sResult );
		}
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsGeneratePublicKey(CCmdUI* pCmdUI)		// SAC 9/27/13
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnToolsGeneratePublicKey()		// SAC 9/27/13
{
	QString sSecKeyRulelistName = "SetReportKeys";
#ifdef UI_CANRES
	sSecKeyRulelistName = "rl_SECURITYKEYS";
#endif
	QString sPubKey, sMsg;
	if (CMX_RetrievePublicKey( sSecKeyRulelistName, true /*bConvertBinHex*/, sPubKey, sMsg ))
	{	//sTemp.Format( "Public Key:  '%s'", sPubKey );
						VERIFY( BEMPX_WriteLogFile( QString("Public Key:  '%1'").arg(sPubKey).toLatin1().constData(), NULL, false /*bBlankFile*/ ) );
		sMsg = "Public key written to project log file.";
	}
	else
	{	if (!sMsg.isEmpty())
			sMsg = "Error encountered generating public key:  " + sMsg;
		else
			sMsg = "Unknown error encountered generating public key.";
	}
	AfxMessageBox( sMsg.toLatin1().constData() );
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsKeyPrep(CCmdUI* pCmdUI)		// SAC 1/10/17
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnToolsKeyPrep()		// SAC 1/10/17
{
	CString sKPFN = esProgramPath, sKPOutFN = esProgramPath;
	sKPFN += "KeyPrep.txt";
	sKPOutFN += "KeyPrep-out.txt";
	if (!FileExists( sKPFN ))
		AfxMessageBox( "KeyPrep file missing" );
	else
	{	CString sMsg;
		sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to abort the %s.", "key prep output", sKPOutFN, "key prep action" );
		if (OKToWriteOrDeleteFile( sKPOutFN, sMsg ))
	   {	CStdioFile inFile, outFile;
			if (inFile.Open( sKPFN, CFile::modeRead ) == 0)
				AfxMessageBox( "Error opening KeyPrep input file" );
			else if (outFile.Open( sKPOutFN, CFile::modeCreate | CFile::modeWrite ) == 0)
				AfxMessageBox( "Error opening KeyPrep-out file" );
			else
			{	char strSwap[132];
				CString str;
				int len, i=0;
				while (++i < 200)
				{	inFile.ReadString( str );
					len = str.GetLength();
					if (len != 64)
						break;
					else
					{
						memcpy( strSwap, str, len );		strSwap[len]='\n';		strSwap[len+1]=0;
						TweakString( strSwap, len );
		         	outFile.WriteString( strSwap );
				}	}
				sMsg.Format( "%d keys processed", i-1 );
				AfxMessageBox( sMsg );
	}	}	}
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsGenerateMECH1ReportRecords(CCmdUI* pCmdUI)
{
#ifdef UI_CARES
	pCmdUI->Enable( (	eInterfaceMode == IM_INPUT && eiBDBCID_SCSysRpt > 0 &&
							eiBDBCID_Proj    > 0 && BEMPX_GetNumObjects( eiBDBCID_Proj    ) > 0 &&
							eiBDBCID_HVACSys > 0 && BEMPX_GetNumObjects( eiBDBCID_HVACSys ) > 0 ) );
#else
	pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsGenerateMECH1ReportRecords()
{
#ifdef UI_CARES
	BOOL bGenSCSysRpts = (BEMPX_GetNumObjects( eiBDBCID_SCSysRpt ) < 1);
	if (!bGenSCSysRpts)
   {	if (MessageBox( "This action will cause all existing HVAC system report data to be deleted and re-generated.\n\n"
								"Press 'OK' to continue with HVACSys report re-generation, or 'Cancel' to leave HVAC reporting data as is.", NULL, MB_OKCANCEL ) == IDOK)
			bGenSCSysRpts = TRUE;
	}
	if (bGenSCSysRpts)
	{	BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);   // SAC 8/22/11
		CWaitCursor wait;
		BOOL bEvalSuccessful = CMX_EvaluateRuleset( "Setup_SCSysRptReportingObjects", bLogRuleEvaluation, FALSE /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ );
		// Construct message to display
		CString sMsg = (bEvalSuccessful ? "HVAC System Report Setup Successful." : "HVAC System Report Setup Failed.");
		MessageBox( sMsg );

		CDocument* pDoc = GetActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
			pDoc->SetModifiedFlag( TRUE );

		CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
		if (pView != NULL)            // update main view's tree control(s)
			pView->SendMessage( WM_DISPLAYDATA, eiBDBCID_SCSysRpt );
	}
#else
	// do nothing
#endif
}


void CMainFrame::OnUpdateToolsGenerateDHWEquipReportRecords(CCmdUI* pCmdUI)
{
#ifdef UI_CARES
	pCmdUI->Enable( (	eInterfaceMode == IM_INPUT && eiBDBCID_DHWSysRpt > 0 &&
							eiBDBCID_Proj   > 0 && BEMPX_GetNumObjects( eiBDBCID_Proj   ) > 0 &&
							eiBDBCID_DHWSys > 0 && BEMPX_GetNumObjects( eiBDBCID_DHWSys ) > 0 ) );
#else
	pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsGenerateDHWEquipReportRecords()
{
#ifdef UI_CARES
	BOOL bGenDHWSysRpts = (BEMPX_GetNumObjects( eiBDBCID_DHWSysRpt ) < 1);
	if (!bGenDHWSysRpts)
   {	if (MessageBox( "This action will cause all existing DHWSysRpt report data to be deleted and re-generated.\n\n"
								"Press 'OK' to continue with DHWSysRpt re-generation, or 'Cancel' to leave DHWSysRpt data as is.", NULL, MB_OKCANCEL ) == IDOK)
			bGenDHWSysRpts = TRUE;
	}
	if (bGenDHWSysRpts)
	{	BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);   // SAC 8/22/11
		CWaitCursor wait;
		BOOL bEvalSuccessful = CMX_EvaluateRuleset( "Setup_DHWSysReportingObjects", bLogRuleEvaluation, FALSE /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ );
		// Construct message to display
		CString sMsg = (bEvalSuccessful ? "DHW System Report Setup Successful." : "DHW System Report Setup Failed.");
		MessageBox( sMsg );

		CDocument* pDoc = GetActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
			pDoc->SetModifiedFlag( TRUE );

		CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
		if (pView != NULL)            // update main view's tree control(s)
			pView->SendMessage( WM_DISPLAYDATA, eiBDBCID_DHWSysRpt );
	}
#else
	// do nothing
#endif
}


void CMainFrame::OnUpdateToolsGenerateIAQVentReportRecords(CCmdUI* pCmdUI)
{
#ifdef UI_CARES
	pCmdUI->Enable( (	eInterfaceMode == IM_INPUT && eiBDBCID_IAQVentRpt > 0 &&
							eiBDBCID_Proj    > 0 && BEMPX_GetNumObjects( eiBDBCID_Proj    ) > 0 ) );
#else
	pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsGenerateIAQVentReportRecords()
{
#ifdef UI_CARES
	BOOL bGenIAQVentRpts = (BEMPX_GetNumObjects( eiBDBCID_IAQVentRpt ) < 1);
	if (!bGenIAQVentRpts)
   {	if (MessageBox( "This action will cause all existing IAQVentRpt report data to be deleted and re-generated.\n\n"
								"Press 'OK' to continue with IAQVentRpt re-generation, or 'Cancel' to leave IAQVentRpt data as is.", NULL, MB_OKCANCEL ) == IDOK)
			bGenIAQVentRpts = TRUE;
	}
	if (bGenIAQVentRpts)
	{	BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);   // SAC 8/22/11
		CWaitCursor wait;
		BOOL bEvalSuccessful = CMX_EvaluateRuleset( "Setup_IAQVentReportingObjects", bLogRuleEvaluation, FALSE /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ );
		// Construct message to display
		CString sMsg = (bEvalSuccessful ? "IAQ Ventilation Report Setup Successful." : "IAQ Ventilation Report Setup Failed.");
		MessageBox( sMsg );

		CDocument* pDoc = GetActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
			pDoc->SetModifiedFlag( TRUE );

		CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
		if (pView != NULL)            // update main view's tree control(s)
			pView->SendMessage( WM_DISPLAYDATA, eiBDBCID_IAQVentRpt );
	}
#else
	// do nothing
#endif
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsOptions(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( (eiBDBCID_INISettings > 0) );
}
void CMainFrame::OnToolsOptions()
{
	int iTabCtrlWd, iTabCtrlHt;
	VERIFY( GetDialogTabDimensions( eiBDBCID_INISettings, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
	OnINISettings( 0, iTabCtrlWd, iTabCtrlHt, "Program INI Settings", "options" );
}

void CMainFrame::OnUpdateToolsProxy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( (eiBDBCID_INISettings > 0) );
}
void CMainFrame::OnToolsProxy()
{
	OnINISettings( 2, 410 /*DlgWd*/, 235 /*DlgHt*/, "Proxy Server Settings", "proxy" );
}

void CMainFrame::OnINISettings( int iDlgIDOffset, int iDlgWd, int iDlgHt, CString sDlgCaption, CString sINISection )
{
	CDocument* pDoc = GetActiveDocument();
	if (eiBDBCID_INISettings > 0 && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{	BOOL bInitDocModifiedFlag = pDoc->IsModified();
		int iError;
		int iNumINISettingsObjs = BEMPX_GetNumObjects( eiBDBCID_INISettings );			ASSERT( iNumINISettingsObjs < 1 );
		while (iNumINISettingsObjs > 0)
		{	
			BEMObject* pISObj = BEMPX_GetObjectByClass( eiBDBCID_INISettings, iError, iNumINISettingsObjs-1 );		ASSERT( pISObj );
			if (pISObj)
				BEMPX_DeleteObject( pISObj );
			iNumINISettingsObjs--;
		}

		bool bOKToCr8 = BEMPX_CanCreateAnotherUserObject( eiBDBCID_INISettings );		ASSERT( bOKToCr8 );
		if (bOKToCr8)
		{	BEMObject* pINIObj = BEMPX_CreateObject( eiBDBCID_INISettings, NULL /*lpszName*/, NULL /*pParent*/ );		ASSERT( pINIObj );
			if (pINIObj)
			{	// initialize ALL properties of the new INISettings object to the settings present in the current INI file
				int iNumINIPropTypes = BEMPX_GetNumPropertyTypes( eiBDBCID_INISettings );
				for (int i1PTIdx=1; i1PTIdx <= iNumINIPropTypes; i1PTIdx++)
				{	BEMPropertyType* pPropType = BEMPX_GetPropertyType( eiBDBCID_INISettings, i1PTIdx );		ASSERT( pPropType );
					if (pPropType && !pPropType->getShortName().isEmpty())
					{	// grab INI setting corresponding to this property (if any is specified) and post it to the INISettings object
						if (pPropType->getPropType() == BEMP_Int || pPropType->getPropType() == BEMP_Sym)
						{	// for Int & Sym data - INI file settings assumed to be Integer values
							long iINIVal = (long) ReadProgInt( sINISection, pPropType->getShortName().toLatin1().constData(), 9999 );
							if (iINIVal != 9999)
								VERIFY( BEMPX_SetBEMData( BEMPX_GetDBID( eiBDBCID_INISettings, i1PTIdx, 1 ), BEMP_Int, (void*) &iINIVal ) >= 0 );
						}
						else if (pPropType->getPropType() == BEMP_Str)
						{	// for Str data - INI file settings assumed to be character strings
							CString sINIStr;
							CString sNewINIOptName = pPropType->getShortName().toLatin1().constData();
							BOOL bEncodeString    = (pPropType->getShortName().indexOf("ProxyServerCred") >= 0);		// SAC 1/5/17
							if (bEncodeString)
							{	if (!GetEncodedSetting( sINISection, sNewINIOptName, sINIStr ))
									sINIStr = "default-string";
							}
							else
								sINIStr = ReadProgString( sINISection, pPropType->getShortName().toLatin1().constData(), "default-string" );
							if (sINIStr.Compare("default-string") != 0)
								VERIFY( BEMPX_SetBEMData( BEMPX_GetDBID( eiBDBCID_INISettings, i1PTIdx, 1 ), BEMP_Str, (void*) ((const char*) sINIStr) ) >= 0 );
						}
						else
						{	ASSERT( FALSE );	// unexpected INISettings property type (BEMP_Flt or BEMP_Obj) - unsure how to map to program INI settings...
						}
				}	}

				// INISettings object now reflects data in current INI file, so now preset the dialog
				//if (TRUE)
//					int iTabCtrlWd, iTabCtrlHt;
//					VERIFY( GetDialogTabDimensions( eiBDBCID_INISettings, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
					CWnd* pWnd = GetFocus();
//					CSACBEMProcDialog td( eiBDBCID_INISettings, 0 /*iCurrentTab*/, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
//									0 /*iDlgMode*/, iDlgWd, iDlgHt, BEMPUIX_GetNumConsecutiveDialogTabIDs( eiBDBCID_INISettings, 0 /*iUIMode*/ ) /*iMaxTabs*/,
//									"CBECC Program INI Settings" /*pszCaptionText*/, "OK", NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/,
//									NULL /*pszExitingRulelist*/, NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMsgToParent*/,
//									ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
//					if (td.DoModal() == IDOK)
//					{}

					int iDlgID = BEMPUIX_GetFirstDialogTabID( eiBDBCID_INISettings, 0 /*iUIMode*/ ) + iDlgIDOffset;
		         CSACDlg dlgNewObj( pWnd /*this*/, eiBDBCID_INISettings, 0 /* lDBID_ScreenIdx */, iDlgID, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDlgCaption,
									iDlgHt, iDlgWd, 10 /*iBaseMarg*/, 0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/, FALSE /*bBypassChecksOnCancel*/,
                           FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/, ebIncludeLongCompParamStrInToolTip );
      		   dlgNewObj.DoModal();

				// no need to post process INISettings data - any data modified by user in the dialog should get psoted directly to the INI file after each edit
				// finally, delete INISettings object we created to edit in the dialog
				BEMPX_DeleteObject( pINIObj );
		}	}

	// reset document modified flag to FALSE if that is how it started - since no data stored in the Project/input file has been changed
		if (!bInitDocModifiedFlag)
			pDoc->SetModifiedFlag( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsGenerateModel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( (BEMPX_GetNumObjects( BEMPX_GetDBComponentID("Model") ) > 0) );
}
void CMainFrame::OnToolsGenerateModel()
{
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{
		int iCID_Model = BEMPX_GetDBComponentID("Model");
      CMX_EvaluateRuleset( "Default_Model", ebVerboseInputLogging, FALSE, ebVerboseInputLogging, NULL, NULL, NULL, epInpRuleDebugInfo );  // epszRLs[0] );

		CWnd* pWnd = GetFocus();

//		int iDlgID = BEMPUIX_GetFirstDialogTabID( iCID_Model, 0 /*iUIMode*/ );
//		CSACDlg dlgNewObj( pWnd /*this*/, iCID_Model, 0 /* lDBID_ScreenIdx */, iDlgID, 0, 0, 0,
//                  "Default_Model" /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, "Model Description",
//						400 /*iDlgHt*/, 700 /*iDlgWd*/, 10 /*iBaseMarg*/, 0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
//						0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
//						0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
//                  FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/, FALSE /*bBypassChecksOnCancel*/,
//                  FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/, ebIncludeLongCompParamStrInToolTip );
//      if (dlgNewObj.DoModal() == IDOK)

		int iTabCtrlWd=750, iTabCtrlHt=550;
		//VERIFY( GetDialogTabDimensions( iCID_Model, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
		CString sDialogCaption = "Model Description";
		//GetDialogCaption( iCID_Model, sDialogCaption );   // SAC 1/8/12
	CString sSaveDataModRulelist = esDataModRulelist;
	esDataModRulelist = "Default_Model";
      CSACBEMProcDialog td( iCID_Model, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd /*this*/,
                        0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, BEMPUIX_GetNumConsecutiveDialogTabIDs( iCID_Model, 0 /*iUIMode*/ ) /*iMaxTabs*/,
                        (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "Generate",
								NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
								NULL /*pszDataModRulelist - no effect*/, FALSE /*bPostHelpMessageToParent*/,
								ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );   // SAC 1/19/12
      bool bGenModel = (td.DoModal() == IDOK);
	esDataModRulelist = sSaveDataModRulelist;

		if (bGenModel)
      {
         CMX_EvaluateRuleset( "GenerateModel", ebVerboseInputLogging, FALSE, ebVerboseInputLogging, NULL, NULL, NULL, epInpRuleDebugInfo );  // epszRLs[0] );
			SendMessage( WM_EVALPROPOSED /*, (!bWriteToLog)*/ );
			SendMessage( WM_EVALPROPOSED /*, (!bWriteToLog)*/ );
			pDoc->SetModifiedFlag( TRUE );

			//SetStatusBarStrings( "", 2 );		// SAC 10/29/15 - display ruleset ID in third status bar pane

         CMainView* pMainView = (CMainView*) m_wndSplitter.GetPane(0,0);
         if (pMainView != NULL)            // update main view's tree control(s)
         {
#ifdef UI_CARES
				pMainView->SendMessage( WM_UPDATETREE, 0, elDBID_Proj_IsMultiFamily );		// SAC 7/29/16 - ensure access/non-access to DwellUnit* objects based on whether model is multifamily
#endif
            pMainView->SendMessage( WM_DISPLAYDATA );

            //CView* pLibView = (CView*) m_wndSplitter.GetPane(1,0);
            //if (pLibView != NULL)            // update main view's tree control(s)
            //   pLibView->SendMessage( WM_POPLIBTREE, eiCurrentTab );
         }
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsViewFolder(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( DirectoryExists( esProjectsPath ) );
}
void CMainFrame::OnToolsViewFolder()
{	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{	CString sProjFolder = pDoc->GetPathName();
		if (sProjFolder.IsEmpty() || sProjFolder.Find("Untitled") >= 0)
			sProjFolder = esProjectsPath;
		else if (sProjFolder.ReverseFind('\\') > 0)
			sProjFolder = sProjFolder.Left( sProjFolder.ReverseFind('\\')+1 );

		if (DirectoryExists( sProjFolder ))
		{	CString sCommandLineParams;
			sCommandLineParams.Format( "/n, /e, %s", sProjFolder );
			ShellExecute( GetSafeHwnd(), "open", "explorer.exe", sCommandLineParams, sProjFolder, SW_SHOWNORMAL );
		}
		else
		{	sProjFolder = "Project folder not found:\n" + sProjFolder;
			AfxMessageBox( sProjFolder );
	}	}
}


BOOL CMainFrame::GetLogPathFile( CString& sLPF )
{	sLPF.Empty();
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{	sLPF = pDoc->GetPathName();
		sLPF = sLPF.Left( sLPF.ReverseFind('.')+1 );
		sLPF += "log";
	}
	return !sLPF.IsEmpty();
}

BOOL CMainFrame::LogFileExists()
{
	BOOL bLFEx = FALSE;
	CString sLPF;
	if (GetLogPathFile( sLPF ))
	{	BEMPX_RefreshLogFile( false /*bReOpenLog*/ );	// flush & close log file (in case it is open)
		bLFEx = FileExists( sLPF );
	}
	return bLFEx;
}

void CMainFrame::OnUpdateToolsViewLog(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( LogFileExists() );
}
void CMainFrame::OnToolsViewLog()
{
	CString sLPF;
	if (GetLogPathFile( sLPF ))
	{	BEMPX_RefreshLogFile( false /*bReOpenLog*/ );	// flush & close log file (in case it is open)
		OpenFileViaShellExecute( sLPF, "Project Log" /*FileDescrip*/ );
		//	int idx = sLPF.ReverseFind('\\');
		//	CString sLPFPath = (idx > 0 ? sLPF.Left( idx ) : "");
		//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sLPF, NULL, sLPFPath, SW_SHOWNORMAL );		hinstShellExec;
	}
}

void CMainFrame::OnUpdateToolsDeleteLog(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( LogFileExists() );
}
void CMainFrame::OnToolsDeleteLog()
{
	CString sLPF;
	if (GetLogPathFile( sLPF ))
	{	BEMPX_RefreshLogFile( false /*bReOpenLog*/ );	// flush & close log file (in case it is open)
		CString sDelLogFileMsg;
		sDelLogFileMsg.Format( "Are you sure you wish to delete the following project log file?\n\n%s", sLPF );
	//	if (BEMMessageBox( sDelLogFileMsg, eszWarning, 3 /*error*/, MB_YESNO|MB_DEFBUTTON2 ) == IDYES)
		if (BEMMessageBox( sDelLogFileMsg, eszWarning, 3 /*error*/, (QMessageBox::Yes | QMessageBox::No), QMessageBox::No ) == QMessageBox::Yes)
		{	DeleteFile( sLPF );
	}	}
}


/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsPurgeUnreferencedObjects(CCmdUI* pCmdUI)		// SAC 9/18/13
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnToolsPurgeUnreferencedObjects()		// SAC 9/18/13
{
   CDocument* pDoc = GetActiveDocument();
   if ( pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) &&
        ((CComplianceUIDoc*) pDoc)->CUISaveModified( "unreferenced object purge" ) )
   {
		int iNumObjectsDeleted = 0;
		VERIFY( BEMPX_PurgeUnreferencedComponents( -1 /*iBEMProcIdx*/, &iNumObjectsDeleted ) );

		if (iNumObjectsDeleted > 0)
		{
         SetDataModifiedFlag( TRUE );
			CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
			if (pView != NULL)            // update main view's tree control(s)
				pView->SendMessage( WM_DISPLAYDATA, 0 /*iClass*/ );

			CString sUserMsg;
			sUserMsg.Format( "%d unreferenced objects deleted from building model.  Save project data to same or new file after confirmation of changes.", iNumObjectsDeleted );
			AfxMessageBox( sUserMsg );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateToolsGenerateWindowShades(CCmdUI* pCmdUI)		// SAC 12/18/14
{
#ifdef UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsGenerateWindowShades()		// SAC 12/18/14
{
#ifdef UI_CANRES
   CDocument* pDoc = GetActiveDocument();
	CString sCurrentFileNameNoExt = (pDoc ? pDoc->GetPathName() : "");
   if ( pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) &&
   	  !sCurrentFileNameNoExt.IsEmpty() && sCurrentFileNameNoExt.ReverseFind('.') > 0 &&
        ((CComplianceUIDoc*) pDoc)->CUISaveModified( "generate window shades" ) )
	{	bool bStoreBEMDetails = (ReadProgInt( "options", "StoreBEMDetails", 0) > 0);
		bool bVerbose = bStoreBEMDetails;
		bool bSilent = false;
		int iRetVal = 0, iGenWinShadesRetVal = 0;
		CString sLogMsg, sErrMsg, sDbgFileName;
      sCurrentFileNameNoExt = sCurrentFileNameNoExt.Left( sCurrentFileNameNoExt.ReverseFind('.') );

		long lNumWinsHavingShades=0;
		if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:NumWinsHavingShades" ), lNumWinsHavingShades ) && lNumWinsHavingShades > 0)
		{						if (bVerbose)
								{	sLogMsg.Format( "  Generating shades for %d model windows", lNumWinsHavingShades );
									VERIFY( BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
								}
			QString sGenWinShadesErrMsg;
		//	if (!RuleProcInitializeGeometryIDs( sGenWinShadesErrMsg ))
		//	{	if (sGenWinShadesErrMsg.IsEmpty())
		//			sErrMsg = "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades)";
		//		else
		//			sErrMsg.Format( "ERROR:  Building geometry DBID initialization failed (prior to CMX_GenerateWindowShades):  %s", sGenWinShadesErrMsg );
		//		iRetVal = -100;
		//	}
		//	else
		//	{
 																		if (bStoreBEMDetails)
 																		{	sDbgFileName = sCurrentFileNameNoExt + CString(".ibd-Detail-preWinShades");
    																		BEMPX_WriteProjectFile( sDbgFileName, BEMFM_DETAIL /*FALSE*/ );
 																		}
 				iGenWinShadesRetVal = CMX_GenerateWindowShades_CECNonRes( bVerbose, bStoreBEMDetails, bSilent, sGenWinShadesErrMsg );
 				if (iGenWinShadesRetVal < 0)
 				{	sErrMsg.Format( "%s  - Unable to generate window shade (return code %d)", 
 													sGenWinShadesErrMsg.toLatin1().constData(), iGenWinShadesRetVal );
 					iRetVal = -101;
 				}
 																		if (bStoreBEMDetails)
 																		{	sDbgFileName = sCurrentFileNameNoExt + CString(".ibd-Detail-postWinShades");
    																		BEMPX_WriteProjectFile( sDbgFileName, BEMFM_DETAIL /*FALSE*/ );
 																		}
		//	}
		}

		if (iRetVal != 0)
		{
         SetDataModifiedFlag( TRUE );
			CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
			if (pView != NULL)            // update main view's tree control(s)
				pView->SendMessage( WM_DISPLAYDATA, 0 /*iClass*/ );

			CString sUserMsg;
			if (iRetVal > 0)
				sUserMsg.Format( "%d window shade objects created.", iRetVal );
			else
				sUserMsg.Format( "Window shade generation failed (return code %d).", iGenWinShadesRetVal );
			AfxMessageBox( sUserMsg );
		}
	}
#else
	AfxMessageBox( "Generate Window Shades feature not available in this product." );
#endif
}

/////////////////////////////////////////////////////////////////////////////

static int StringInArray( CStringArray& saStrs, CString& sStr )
{
   int iSize = (int) saStrs.GetSize();
   for (int i=0; i<iSize; i++)
   {
      if (saStrs[i].CompareNoCase( sStr ) == 0)
         return i;
   }
   return -1;
}

/////////////////////////////////////////////////////////////////////////////

afx_msg LONG CMainFrame::OnEvaluateProposedRules(UINT /*uiDontSwitchToLog*/, LONG)
{
//   CMX_EvaluateRuleset( (m_bDoingWizard ? epszWRLs[0] : epszRLs[0]), FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, ebVerboseInputLogging );
   CMX_EvaluateRuleset( esDataModRulelist, FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, ebVerboseInputLogging, NULL, NULL, NULL, epInpRuleDebugInfo );

//CString sEvalMsg;		sEvalMsg.Format( "OnEvaluateProposedRules() -> '%s' rulelist", esDataModRulelist );
//AfxMessageBox( sEvalMsg );

//   if (!uiDontSwitchToLog)
//      WriteToLogFile( WM_SETTOLOGMODE );

   return 0;
}

/////////////////////////////////////////////////////////////////////////////

// Analysis progress tracking callback function
// 	return value of callback function:   0 => Proceed with analysis
// 	                                    >0 => Abort analysis - return error code will indicate callback return value as cause (BEMAnal_CECRes_AbortViaCallback, ...)
//const int analysisProgressType_Processing        = 0;		// => second argument has no use - typically 0
//const int analysisProgressType_PercentProgress   = 1;		// => second argument is percent progress (0-100)
//typedef long (CALLBACK* PAnalysisProgressCallbackFunc)( long lAnalProgType, long lData );
//	static long slClbkCnt = 0;
long CALLBACK AnalysisProgressCallbackFunc( long lAnalProgType, long lData )
{	long lRetVal = 0;
	if (lAnalProgType == analysisProgressType_PercentProgress)
	{	//	if (++slClbkCnt > 10)
		//		lRetVal = 1; // abort
		CString sProgMsg;
		sProgMsg.Format( "         AnalysisProgressCallbackFunc( wAnalProgType=%ld, lData=%ld ) - returning %ld", lAnalProgType, lData, lRetVal );
		VERIFY( BEMPX_WriteLogFile( sProgMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
	}
	return lRetVal;
}

static int siNonResAnalCallbackCount = 0;
long CALLBACK NonResAnalysisProgressCallbackFunc( long lProgressID, long lPercent )
{	long lRetVal = 0;
		siNonResAnalCallbackCount++;
				if (siNonResAnalCallbackCount >= 23)		// test abort via callback
					lRetVal = siNonResAnalCallbackCount;
		CString sProgMsg;
		sProgMsg.Format( "         NonResAnalysisProgressCallbackFunc( lProgressID=%ld, lPercent=%ld ) - call # %d - returning %ld", lProgressID, lPercent, siNonResAnalCallbackCount, lRetVal );
		VERIFY( BEMPX_WriteLogFile( sProgMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
	return lRetVal;
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::PromptToDisplayPDFs( CString sCaption, CString sMsg, CString sBtn2File, CString sBtn2Label,
													CString sBtn3File, CString sBtn3Label, CString sBtn4File, CString sBtn4Label,
													CString sAllLabel, UINT uiIcon /*=MB_DEFBUTTON1 | MB_ICONQUESTION*/ )
{	// prompt user to view one or more PDF report(s)
			XMSGBOXPARAMS xmbp;
			if ((sBtn3File.IsEmpty() || sBtn3Label.IsEmpty()) && (sBtn4File.IsEmpty() || sBtn4Label.IsEmpty()))
				sprintf( xmbp.szCustomButtons, "Continue\nView %s", (const char*) sBtn2Label );
			else if (sBtn4File.IsEmpty() || sBtn4Label.IsEmpty())
				sprintf( xmbp.szCustomButtons, "Continue\nView %s\nView %s\nView %s", (const char*) sBtn2Label, (const char*) sBtn3Label, (const char*) sAllLabel );
			else
				sprintf( xmbp.szCustomButtons, "Continue\nView %s\nView %s\nView %s", (const char*) sBtn2Label, (const char*) sBtn3Label, (const char*) sBtn4Label );
		//	xmbp.nIdIcon = uiIcon;
			int iUserChoice = XMessageBox( GetSafeHwnd(), sMsg, sCaption, /*MB_DEFBUTTON1 | MB_ICONEXCLAMATION*/ /*MB_ICONQUESTION*/ uiIcon, &xmbp );
			switch (iUserChoice)
			{	case IDCUSTOM1 :	{	// do nothing - this is always 'Continue' button
										}	break;
				case IDCUSTOM2 :	{	OpenFileViaShellExecute( sBtn2File, sBtn2Label /*FileDescrip*/ );
										}	break;
				case IDCUSTOM3 :	{	OpenFileViaShellExecute( sBtn3File, sBtn3Label /*FileDescrip*/ );
										}	break;
				case IDCUSTOM4 :	if (!sBtn4File.IsEmpty() && !sBtn4Label.IsEmpty())
										{	OpenFileViaShellExecute( sBtn4File, sBtn4Label /*FileDescrip*/ );
										}
										else
										{	OpenFileViaShellExecute( sBtn3File, sBtn3Label /*FileDescrip*/ );
											OpenFileViaShellExecute( sBtn2File, sBtn2Label /*FileDescrip*/ );
										}	break;
				default			:	ASSERT( FALSE );		break;
			}
	// was:
	//		//if (BEMMessageBox( "PDF compliance report successfully generated.\n\nWould you like to view the report?", "Compliance Report", MB_YESNO ) == IDYES)
	//		if (BEMMessageBox( "PDF compliance report successfully generated.\n\nWould you like to view the report?", "Compliance Report", (QMessageBox::Yes | QMessageBox::No) ) == QMessageBox::Yes)
	//		{	OpenFileViaShellExecute( sPDFRptFN, "Compliance Report" /*FileDescrip*/ );
	//			//	int idx = sPDFRptFN.ReverseFind('/');
	//			//	CString sPDFPath = (idx > 0 ? sPDFRptFN.Left( idx ) : "");
	//			//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sPDFRptFN, NULL, sPDFPath, SW_SHOWNORMAL );		hinstShellExec;
	//		}
}

/////////////////////////////////////////////////////////////////////////////

static char BASED_CODE szPerfBeg[]    = "Compliance Analysis Selected";
static char BASED_CODE szPerfDone[]   = "Compliance Analysis Completed (";
static char BASED_CODE szDoneNoRes[]  = "No Result)";
static char BASED_CODE szDonePass[]   = "Passed)";
static char BASED_CODE szDoneFail[]   = "Failed)";
static char BASED_CODE szPerfErr1[]   = "Compliance Analysis Failed:\n";
static char BASED_CODE szPerfErrSp[]  = "                     ";
static char BASED_CODE szPerfErr2[]   = "User must save the building data to a file before performing the compliance analysis.\n";
static char BASED_CODE szPerfErr3[]   = "Save the building data by selecting File / Save As... from the menu bar.";
static char BASED_CODE szPerfWthr1[]  = "Weather File '";
static char BASED_CODE szPerfWthr2[]  = "' Not Found.";

#define  CSV_RESULTSLENGTH  2560
static char pszCSVResultSummary[ CSV_RESULTSLENGTH ];

afx_msg LONG CMainFrame::OnPerformAnalysis(UINT, LONG)
{
   LONG lRetVal = 1;  // default to 'failure'

	if (m_bPerformingAnalysis)		// SAC 4/1/15 - prevent initiation of analysis if analysis already underway
	{	MessageBeep( MB_OK );
	   return lRetVal;
	}
	m_bPerformingAnalysis = TRUE;

	UpdateSoftwareVersionString();		// SAC 9/17/12
	CComplianceUIApp* pApp = (CComplianceUIApp*)AfxGetApp();  // SAC 11/11/13 - moved outside sector-specific sections

	BOOL bContinue = FALSE;
   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (((CComplianceUIDoc*) pDoc)->CUISaveModified( "compliance analysis" )) )
   	bContinue = TRUE;

	bool bRptGenOfflineConfirmed = false;
	if (bContinue && BEMPX_GetUIActiveFlag() && ReadProgInt( "options", "EnableRptGenStatusChecks", 1 /*default*/ ) > 0)
	{	CString sNoRptGenMsg;
		int iRptsToGen = CheckWhichReportsToGenerate( sNoRptGenMsg );
		if (iRptsToGen > 0 && !CheckReportGenAccess( false ))
		{	// check whether user still wishes to perform analysis even if report gen not available...
			sNoRptGenMsg += " compliance report";
			sNoRptGenMsg += (iRptsToGen > 1 ? "s are" : " is");
			sNoRptGenMsg += " selected for generation following analysis, but report generation is currently offline."
									"\nIf your network provides web access via a proxy server, make sure the proxy address "
									"and credentials are correct.  You can find these settings in:  "
									"Tools > Proxy Server Settings.\n\nWould you like to continue performing analysis?";
	//		if (BEMMessageBox( sNoRptGenMsg, "Compliance Analysis", MB_YESNO ) == IDNO)
			if (BEMMessageBox( sNoRptGenMsg, "Compliance Analysis", 4 /*question*/, (QMessageBox::Yes | QMessageBox::No) ) == QMessageBox::No)
		   	bContinue = FALSE;
		   else
		   	bRptGenOfflineConfirmed = true;
	}	}

	if (bContinue)
	{	CString sMsg, sTemp, sOptionsCSVString;
      CString sCurrentFileName = pDoc->GetPathName();
      CString sOriginalFileName = sCurrentFileName;
      CString sProjectPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('\\') + 1 );
		char pszAnalysisErr[2056] = "\0";
      CTime time = CTime::GetCurrentTime();
//      long lTime = (long) time.GetTime();

		BOOL bPerformSimulations = pApp->PerformSimulations();		
		bPerformSimulations &= (m_bDoingSummaryReport == FALSE);  // SAC 6/19/13


#ifdef UI_CARES

//		int iError;
//		AfxMessageBox( "CMainFrame::OnPerformAnalysis() - Run CSE Engine" );
		CString sCSEPath = esProgramPath + "CSE\\";
		sCSEPath = ReadProgString( szPaths, "CSEPath", sCSEPath, TRUE );  // in case there is one in the INI to override the default
		CString sT24DHWPath = esProgramPath + "T24DHW\\";
		sT24DHWPath = ReadProgString( szPaths, "T24DHWPath", sT24DHWPath, TRUE );  // in case there is one in the INI to override the default

		long lAnalysisType;
		VERIFY( BEMPX_SetDataInteger( elDBID_Proj_AnalysisType, lAnalysisType ) );   // SAC 9/12/11
		ASSERT( lAnalysisType == 0 || lAnalysisType == 12 || lAnalysisType == 13 ||  // 0-Research, 12-ProposedOnly, 13-PropAndStd
				  lAnalysisType == 2 );	// SAC 10/26/16 - 2-Existing Building EDR
	//		BOOL bFullComplianceAnalysis = (lAnalysisType == 13);

	// SAC 1/13/16 - code to append trailing '13', '16', ... to processing directory name in case there are both 2013 & 2016 project files w/ the same name in the same directory
		CString sAppendEnergyCodeYrAbbrev;
		BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:EnergyCodeYear" ), sAppendEnergyCodeYrAbbrev );
		if (sAppendEnergyCodeYrAbbrev.GetLength() == 4)
			sAppendEnergyCodeYrAbbrev = sAppendEnergyCodeYrAbbrev.Right(2);
		else
			sAppendEnergyCodeYrAbbrev.Empty();

		CString sProcessingPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('.') );
		CString sProjFileBase = sProcessingPath.Right( sProcessingPath.GetLength() - sProcessingPath.ReverseFind('\\') - 1 );     ASSERT( !sProjFileBase.IsEmpty() );
//		CString sRunName, sRunIDProcFile, sRunAbbrev;
		if (lAnalysisType == 0)
		{	sProcessingPath += " - CSE\\";
//			sRunName = "User";			sRunIDProcFile = " - User";		sRunAbbrev = "u";
		}
		else if (lAnalysisType == 2)	// SAC 10/26/16 - Existing Building EDR
			sProcessingPath += " - ExEDR\\";
		else
		{	sProcessingPath += " - Comp";
			sProcessingPath += sAppendEnergyCodeYrAbbrev;	// SAC 1/13/16
			sProcessingPath += "\\";	// SAC 1/13/16
//			sRunName = "Proposed";		sRunIDProcFile = " - Prop";  		sRunAbbrev = "p";
		}

		CString sUIVersionString;
		GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );

		int iVerbose = ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ );
	//		BOOL bStoreBEMProcDetails = (ReadProgInt( "options", "StoreBEMDetails", 0) > 0);

		// Always generate summary report during analysis ??
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "AnalysisReport", eiBDBCID_Proj ), BEMP_Str, (void*) "Building Summary (csv)" );

	// storage of ProjFileName
      CString sProjFileName = sCurrentFileName.Right( sCurrentFileName.GetLength() - sProjectPath.GetLength() );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjFileName", eiBDBCID_Proj ), BEMP_Str, (void*) ((const char*) sProjFileName) );

	// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
		VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString ) );		// SAC 1/29/14

		const char* pszAnalOpts = NULL;
		if (!sOptionsCSVString.IsEmpty())
			pszAnalOpts = (const char*) sOptionsCSVString;

					EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
		int iSimResult = CMX_PerformAnalysisCB_CECRes(	NULL /*pszBEMBasePathFile*/, NULL /*pszRulesetPath*/,	sCSEPath /*pszCSEEXEPath*/, sCSEPath /*pszCSEWeatherPath*/,
																	sT24DHWPath /*pszDHWDLLPath*/, NULL /*pszDHWWeatherPath*/,
																	sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/, NULL /*pszLogPathFile*/,
																	sUIVersionString, false /*bLoadModelFile*/, pszAnalOpts, pszAnalysisErr, 2056, true /*bDisplayProgress*/,
																	1 /*SecKeyIndex*/, esSecurityKey, NULL /*callback func ptr*/ );
					//												/*GetSafeHwnd() HWND hWnd,*/ (PAnalysisProgressCallbackFunc) AnalysisProgressCallbackFunc );
					EnableWindow( TRUE );
   	lRetVal = iSimResult;

	// Populate string w/ summary results of analysis
		if ((iSimResult == 0 || iSimResult >= BEMAnal_CECRes_MinErrorWithResults) && bPerformSimulations)
		{
			// SAC 11/15/13 - results format #2  - SAC 8/24/14 - fmt 2->3  - SAC 11/24/14 - fmt 3->4  - SAC 3/31/15 - fmt 4->5  - SAC 2/2/16 - 5->6  - SAC 3/16/16 - 6->7  - SAC 10/7/16 - 7->8  - SAC 2/13/17 - 8->9
			int iCSVResVal = CMX_PopulateCSVResultSummary_CECRes(	pszCSVResultSummary, CSV_RESULTSLENGTH, NULL /*pszRunOrientation*/,
																					9 /*iResFormatVer*/, sOriginalFileName );
			if (iCSVResVal == 0)
			{
				char pszCSVColLabel1[1280], pszCSVColLabel2[2560], pszCSVColLabel3[2560];
				VERIFY( CMX_PopulateResultsHeader_Res( pszCSVColLabel1, 1280, pszCSVColLabel2, 2560, pszCSVColLabel3, 2560 ) == 0 );	// SAC 5/10/15
				const char* szaCSVColLabels[4]	=	{ pszCSVColLabel1, pszCSVColLabel2, pszCSVColLabel3, NULL };

				CString sCSVResultSummary = pszCSVResultSummary;
//				sCSVResultSummary += CString("\"") + sOriginalFileName + CString("\"");  // append full project path/file to CSV record
				// WRITE result summary to PROJECT and GENERIC DATA CSV result logs - ALONG WITH COLUMN TITLES (if log doesn't previously exist)
			//	CString sCSVLogFN = BEMPX_GetLogFilename( true );				ASSERT( !sCSVLogFN.IsEmpty() );
				QString qsCSVLogFN = BEMPX_GetLogFilename( true );		CString sCSVLogFN = qsCSVLogFN.toLatin1().constData();		ASSERT( !sCSVLogFN.IsEmpty() );
				if (!sCSVLogFN.IsEmpty())
				{	sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
					             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
									 "(once the file is closed), or \n'Cancel' to abort the %s.", "CSV results log", sCSVLogFN, "writing of results to the file" );
					if (OKToWriteOrDeleteFile( sCSVLogFN, sMsg, (!BEMPX_GetUIActiveFlag()) ))
						VERIFY( BEMPX_WriteLogFile( sCSVResultSummary, NULL, false /*bBlankFile*/, FALSE /*bSupressAllMessageBoxes*/,
																false /*bAllowCopyOfPreviousLog*/, szaCSVColLabels /*ppCSVColumnLabels*/ ) );
				}

				// SAC 11/15/13 - results format #2  - SAC 8/24/14 - fmt 2->3  - SAC 11/24/14 - fmt 3->4  - SAC 2/2/16 - fmt 5->6  - SAC 3/16/16 - fmt 6->7  - SAC 10/7/16 - fmt 7->8  - SAC 2/13/17 - fmt 8->9
				CString sCSVResultsLogFN = ReadProgString( "files", "CSVResultsLog", "AnalysisResults-v9.csv", TRUE /*bGetPath*/ );
				VERIFY( AppendToTextFile( sCSVResultSummary, sCSVResultsLogFN, "CSV results log", "writing of results to the file", szaCSVColLabels ) );
			}
			else
			{	CString sErrResultMsg;		ASSERT( FALSE );
				sErrResultMsg.Format( "Error encountered retrieving results summary data.  CMX_PopulateCSVResultSummary_CECRes() returned %d.", iCSVResVal );
				if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent error messagebox when GUI deactivated
					AfxMessageBox( sErrResultMsg );
				else
					VERIFY( BEMPX_WriteLogFile( sErrResultMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
			}
		}

	// check for existence of CSE sim output for possible access by user
		CString sCSERptPathFile, sCSEErrPathFile;
		if (bPerformSimulations && BEMPX_GetUIActiveFlag())
		{	long lCSERpt_HaveReports, lEnableResearchMode, lEnableRptIncFile;
			QString qsReportIncludeFile;
			sCSERptPathFile = sOriginalFileName.Left( sOriginalFileName.ReverseFind('.') );
			sCSEErrPathFile = sCSERptPathFile;
			sCSERptPathFile += " - CSE Reports.txt";
			if (!FileExists( sCSERptPathFile ))
				sCSERptPathFile.Empty();
			else if ( (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:CSERpt_HaveReports" ), lCSERpt_HaveReports ) && lCSERpt_HaveReports > 0) ||
						 ( ( (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EnableResearchMode" ), lEnableResearchMode ) && lEnableResearchMode > 0) ||
						     (BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:EnableRptIncFile"   ), lEnableRptIncFile   ) && lEnableRptIncFile   > 0) ) &&
						 	(BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ReportIncludeFile" ), qsReportIncludeFile ) && !qsReportIncludeFile.isEmpty()) ) )
			{	}	// User SHOULD be prompted to review CSE Reports output
			else
				sCSERptPathFile.Empty();	// don't prompt user to review Reports if 

			sCSEErrPathFile += " - CSE Errors.txt";
			if (!FileExists( sCSEErrPathFile ))
				sCSEErrPathFile.Empty();
		}

	// Prompt user to view generated PDF compliance report (if analysis successful & PDF written)
		if (iSimResult == 0 && bPerformSimulations)
		{	long lCompRptPDFWritten=0;
			if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompRptPDFWritten" ), lCompRptPDFWritten ) && lCompRptPDFWritten > 0 &&
					BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent report review prompt when GUI deactivated
			{
			// SAC 11/8/16 - revisions to accommodate review of compliance report(s) OR CSE output
				CString sPTDMsg, sBtnFile[3], sBtnLabel[3];
				int iNumViewBtns=0;

				CString sPDFRptFN = sOriginalFileName.Left( sOriginalFileName.ReverseFind('.') );
				sPDFRptFN += " - AnalysisResults-BEES.pdf";
				if (!FileExists( sPDFRptFN ))
				{	// report to log  that PDF was expected but not found...
					sMsg.Format( "PDF compliance report not found:  %s", sPDFRptFN );
					VERIFY( BEMPX_WriteLogFile( sMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
				}
				else
				{	sPTDMsg = "PDF compliance report successfully generated during analysis.";
					sBtnFile[iNumViewBtns] = sPDFRptFN;   sBtnLabel[iNumViewBtns++] = "Compliance Report";
				}
				if (!sCSERptPathFile.IsEmpty() && !sCSEErrPathFile.IsEmpty())
				{	if (!sPTDMsg.IsEmpty())
						sPTDMsg += "\n\n";
					sPTDMsg += "CSE simulation report and error outputs are available for review.";
				}
				else if (!sCSERptPathFile.IsEmpty())
				{	if (!sPTDMsg.IsEmpty())
						sPTDMsg += "\n\n";
					sPTDMsg += "CSE simulation report output is available for review.";
				}
				else if (!sCSEErrPathFile.IsEmpty())
				{	if (!sPTDMsg.IsEmpty())
						sPTDMsg += "\n\n";
					sPTDMsg += "CSE simulation error output is available for review.";
				}
				if (!sCSERptPathFile.IsEmpty())
				{	sBtnFile[iNumViewBtns] = sCSERptPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Reports";
				}
				if (!sCSEErrPathFile.IsEmpty())
				{	sBtnFile[iNumViewBtns] = sCSEErrPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Errors";
				}

				if (!sPTDMsg.IsEmpty())
				{	// prompt user to view PDF report (and/or other files)
			//		//if (BEMMessageBox( "PDF compliance report successfully generated.\n\nWould you like to view the report?", "Compliance Report", MB_YESNO ) == IDYES)
			//		if (BEMMessageBox( "PDF compliance report successfully generated.\n\nWould you like to view the report?", "Compliance Report", (QMessageBox::Yes | QMessageBox::No) ) == QMessageBox::Yes)
			//		{	OpenFileViaShellExecute( sPDFRptFN, "Compliance Report" /*FileDescrip*/ );
			//			//	int idx = sPDFRptFN.ReverseFind('/');
			//			//	CString sPDFPath = (idx > 0 ? sPDFRptFN.Left( idx ) : "");
			//			//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sPDFRptFN, NULL, sPDFPath, SW_SHOWNORMAL );		hinstShellExec;
			//		}
					// prompt user to view one or more PDF report(s) (or other files)
					PromptToDisplayPDFs( "Analysis Output", sPTDMsg, sBtnFile[0], sBtnLabel[0], sBtnFile[1], sBtnLabel[1], sBtnFile[2], sBtnLabel[2], "All Files" );
				}
			}
		// SAC 11/17/16 - prompt user of CSE Reports access if they specified report output and they are present
			else if (BEMPX_GetUIActiveFlag())
			{
				CString sPTDMsg, sBtnFile[2], sBtnLabel[2];
				int iNumViewBtns=0;

				if (!sCSERptPathFile.IsEmpty() && !sCSEErrPathFile.IsEmpty())
					sPTDMsg += "CSE simulation report and error outputs are available for review.";
				else if (!sCSERptPathFile.IsEmpty())
					sPTDMsg += "CSE simulation report output is available for review.";
				else if (!sCSEErrPathFile.IsEmpty())
					sPTDMsg += "CSE simulation error output is available for review.";

				if (!sCSERptPathFile.IsEmpty())
				{	sBtnFile[iNumViewBtns] = sCSERptPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Reports";
				}
				if (!sCSEErrPathFile.IsEmpty())
				{	sBtnFile[iNumViewBtns] = sCSEErrPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Errors";
				}

				if (!sPTDMsg.IsEmpty())
					PromptToDisplayPDFs( "Analysis Output", sPTDMsg, sBtnFile[0], sBtnLabel[0], sBtnFile[1], sBtnLabel[1], "", "", "All Files" );
			}
		}

	// SAC 5/16/12 - added reporting of analysis results
		BOOL bSimResultsDisplayed = FALSE;
		if (bPerformSimulations)
		{	//int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
			if ((iSimResult == 0 || iSimResult >= BEMAnal_CECRes_MinErrorWithResults) && eiBDBCID_EUseSummary > 0 && BEMPX_GetNumObjects( eiBDBCID_EUseSummary ))
			{	bSimResultsDisplayed = TRUE;
				if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) > 1)	// SAC 9/13/13 - added to ensure first (worst case) EUseSummary object is ALWAYS the active obejct as dialog presented
					BEMPX_SetActiveObjectIndex( eiBDBCID_EUseSummary, 0 );
				CString sDialogCaption;
				GetDialogCaption( eiBDBCID_EUseSummary, sDialogCaption );
				CWnd* pWnd = GetFocus();
				CSACBEMProcDialog td( eiBDBCID_EUseSummary, 0 /*eiCurrentTab*/, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
				                  0 /*iDlgMode*/, 810 /*iTabCtrlWd*/, 440 /*iTabCtrlHt*/, 99 /*iMaxTabs*/,
				                  (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "Done",
										NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
										NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
										ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
				if (BEMPX_GetUIActiveFlag())
					td.DoModal();
			}
		}

		if (iSimResult != 0 || (bPerformSimulations && !bSimResultsDisplayed))
		{	CString sErrResultMsg;
			if (iSimResult == BEMAnal_CECRes_UserAbortedAnalysis || iSimResult == BEMAnal_CECRes_AbortViaCallback)		// unique return value indicating user aborted analysis -OR- callback return value caused abort
				sErrResultMsg.Format( "Analysis aborted by user (code %d).", iSimResult );
			else		
			{	int iNumErrors = BEMPX_GetRulesetErrorCount();
				if (iNumErrors > 0)
				{	char pszRuleErr[1024];
					CString sErrTmp;
					CStringArray saErrors;
					//sErrResultMsg.Format( "%d Error(s) encountered performing analysis (error code %d).", iNumErrors, iSimResult );
					int iErr, iErrCount = 0;
					for (iErr=1; iErr<=iNumErrors; iErr++)
					{	if (BEMPX_GetRulesetErrorMessage( iErr, pszRuleErr, 1024 ))
						{	// filter out generic messages that indicate certain rulelists failing
							if (	_strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rulelist 'ProposedModel", 60 ) == 0 )		// ProposedModelCodeCheck / SimulationCheck / CodeAdditions
							{	// do not report these errors which are always accommpanied by error messages, even when in Verbose mode...
							}
							else if (iVerbose > 0 || _strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rule", 41 ) != 0)
							{	iErrCount += 1;
								sErrTmp = pszRuleErr;
								if (iVerbose == 0)
								{	// if verbose flag NOT set, then strip off details of rule where error occurred
									int iRuleDetailIdx = sErrTmp.Find( "evaluating rule: Rule" );
									if (iRuleDetailIdx > 0)
										sErrTmp = sErrTmp.Left( iRuleDetailIdx );
								}
								saErrors.Add( sErrTmp );
							}
						}
						else
						{	ASSERT( FALSE );
						}
					}	ASSERT( (iErrCount > 0 || saErrors.GetSize()==0) );
					for (iErr=1; iErr<=iErrCount; iErr++)
					{	if (iErrCount < 2)
							sErrTmp.Format( "\n\n%s", saErrors[iErr-1] );
						else
							sErrTmp.Format( "\n\n(%d) %s", iErr, saErrors[iErr-1] );
						sErrResultMsg += sErrTmp;
					}

					if (sErrResultMsg.IsEmpty())
						sErrResultMsg.Format( "%d Error(s) encountered performing analysis (error code %d).", iNumErrors, iSimResult );
					else if (iErrCount == 1)
					{	sErrTmp.Format( "\n\nAnalysis returned error code %d.", iSimResult );
						sErrResultMsg = sErrResultMsg.Right( sErrResultMsg.GetLength()-2 );  // strip off leading newlines
						sErrResultMsg += sErrTmp;
					}
					else
					{	sErrTmp.Format( "%d Error(s) encountered performing analysis (error code %d):", iErrCount, iSimResult );
						sErrResultMsg = sErrTmp + sErrResultMsg;
					}
				}
				else if (bRptGenOfflineConfirmed && iSimResult == BEMAnal_CECRes_CompRptWriteError)		// don't report error here if only problem was report generator that user was already alerted of
					sErrResultMsg.Empty();
				else
					sErrResultMsg.Format( "Error encountered performing analysis (error code %d).", iSimResult );
			}
			if (!sErrResultMsg.IsEmpty())
			{	if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent error messagebox when GUI deactivated
				{
					if (sCSERptPathFile.IsEmpty() && sCSEErrPathFile.IsEmpty())
						AfxMessageBox( sErrResultMsg );
					else
					{	int iNumViewBtns=0;
						CString sBtnFile[2], sBtnLabel[2];
						if (!sCSERptPathFile.IsEmpty() && !sCSEErrPathFile.IsEmpty())
							sErrResultMsg += "\n\nCSE simulation error and report outputs are available for review.";
						else if (!sCSEErrPathFile.IsEmpty())
							sErrResultMsg += "\n\nCSE simulation error output is available for review.";
						else if (!sCSERptPathFile.IsEmpty())
							sErrResultMsg += "\n\nCSE simulation report output is available for review.";
						if (!sCSEErrPathFile.IsEmpty())
						{	sBtnFile[iNumViewBtns] = sCSEErrPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Errors";
						}
						if (!sCSERptPathFile.IsEmpty())
						{	sBtnFile[iNumViewBtns] = sCSERptPathFile;   sBtnLabel[iNumViewBtns++] = "CSE Reports";
						}
						// prompt user to view one or more PDF report(s) (or other files)
						PromptToDisplayPDFs( "Analysis Error", sErrResultMsg, sBtnFile[0], sBtnLabel[0], sBtnFile[1], sBtnLabel[1], "", "", "Both Files", MB_DEFBUTTON1 | MB_ICONEXCLAMATION );  // MB_ICONEXCLAMATION );
//			case MB_ICONEXCLAMATION: lpIcon = (LPTSTR)IDI_EXCLAMATION; break;
				}	}
				else
					VERIFY( BEMPX_WriteLogFile( sErrResultMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
		}	}

	// ONLY RESTORE project data if analysis failed
		if (iSimResult != 0)
		   ((CComplianceUIDoc*) pDoc)->OpenTheFile( sOriginalFileName, TRUE /*bWriteToLog*/, FALSE /*bRestore*/, NULL /*pszNewRuleFile*/,
            													-1 /*lRulesetSymVal*/, FALSE /*bNormalRulesetUpdates*/ );	// SAC 11/17/15
		else
		{	// delete all building models except the first (user) model
			VERIFY( BEMPX_DeleteModels( false /*bIncludingUserModel*/ ) );
			VERIFY( BEMPX_SetActiveModel( 0 ) );
		}

#endif

#ifdef UI_CANRES
//   CStringArray sRulelistNames;
//   int iNumLists = CMX_GetRulelistNames( sRulelistNames );

	if (bContinue)  // always true
   {
      long lTime = (long) time.GetTime();
		int iVerbose = ReadProgInt( "options", "LogRuleEvaluation", 0);
		CString sProcessingPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('.') );
		//CString sProjFileBase = sProcessingPath.Right( sProcessingPath.GetLength() - sProcessingPath.ReverseFind('\\') - 1 );     ASSERT( !sProjFileBase.IsEmpty() );
		sProcessingPath += " - run\\";
		CString sUIVersionString;
		GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );
	   CString sWthrPath = ReadProgString( "paths", "WeatherPath", "EPW\\", TRUE );
	// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
		VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString ) );		// SAC 1/29/14

	// storage of ProjFileName - added to non-res processing from res
      CString sProjFileName = sCurrentFileName.Right( sCurrentFileName.GetLength() - sProjectPath.GetLength() );
		BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjFileName", BEMPX_GetDBComponentID( "Proj" ) ), BEMP_Str, (void*) ((const char*) sProjFileName) );
		int iSimResult = 0;

enum CodeType	{	CT_T24N,		CT_S901G,	CT_ECBC,		CT_NumTypes  };	// SAC 10/2/14
		int iCodeType = CT_T24N;		// SAC 10/2/14 - added to facilitate code-specific processing
		QString sLoadedRuleSetID, sLoadedRuleSetVer;
		if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))
		{	if (sLoadedRuleSetID.indexOf( "CA " ) == 0)
				iCodeType = CT_T24N;
			else if (sLoadedRuleSetID.indexOf( "ASH" ) == 0 && sLoadedRuleSetID.indexOf( "90.1" ) > 0 && sLoadedRuleSetID.indexOf( " G" ) > 0)
				iCodeType = CT_S901G;
			else if (sLoadedRuleSetID.indexOf( "ECBC" ) >= 0)
				iCodeType = CT_ECBC;
			else
			{	ASSERT( FALSE );	// what ruleset is this ??
		}	}


// vvv TEMPORARY vvv
// vvv TEMPORARY vvv
// vvv TEMPORARY vvv
	BOOL bHaveSizingPropRL = FALSE;
   QVector<QString> saRulelistNames;
   int iNumRulelists = CMX_GetRulelistNames( saRulelistNames );
   for (int iRL=0; (!bHaveSizingPropRL && iRL<iNumRulelists); iRL++)
      bHaveSizingPropRL = (saRulelistNames[iRL].compare( "rl_SIZING_PROPOSED", Qt::CaseInsensitive ) == 0);

	pszCSVResultSummary[0] = '\0';
	ASSERT( bHaveSizingPropRL );
	//	if (!bHaveSizingPropRL)
	//			iSimResult = CMX_PerformAnalysis_CECNonRes_OLD(	NULL /*pszBEMBasePathFile*/, NULL /*pszRulesetPath*/, sWthrPath /*pszSimWeatherPath*/,
	//																		NULL /*pszCompMgrDLLPath -> WAS: sT24DHWPath*/, NULL /*pszDHWWeatherPath*/,
	//																		sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
	//																		NULL /*pszLogPathFile*/, sUIVersionString, false /*bLoadModelFile*/, sOptionsCSVString,
	//																		pszAnalysisErr, 2056, true /*bDisplayProgress*/, GetSafeHwnd() /*HWND hWnd*/ );
	//	else
// ^^^ TEMPORARY ^^^
// ^^^ TEMPORARY ^^^
// ^^^ TEMPORARY ^^^
					EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
			iSimResult = CMX_PerformAnalysis_CECNonRes(	NULL /*pszBEMBasePathFile*/, NULL /*pszRulesetPath*/, sWthrPath /*pszSimWeatherPath*/,
																		NULL /*pszCompMgrDLLPath -> WAS: sT24DHWPath*/, NULL /*pszDHWWeatherPath*/,
																		sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
																		NULL /*pszLogPathFile*/, sUIVersionString, false /*bLoadModelFile*/, sOptionsCSVString,
																		pszAnalysisErr, 2056, true /*bDisplayProgress*/, GetSafeHwnd() /*HWND hWnd*/,
																		pszCSVResultSummary, CSV_RESULTSLENGTH, 1 /*SecKeyIndex*/, esSecurityKey );   // SAC 1/12/17
					EnableWindow( TRUE );
   	lRetVal = iSimResult;

	// Populate string w/ summary results of analysis  - SAC 5/19/14 - added similar to -Res
		if (iSimResult == 0 && bPerformSimulations && strlen( pszCSVResultSummary ) > 0)
		{
			//CString sCSVResultSummary = pszResultsRecord;
			//sCSVResultSummary += CString("\"") + sOriginalFileName + CString("\"");  // append full project path/file to CSV record
			// WRITE result summary to PROJECT and GENERIC DATA CSV result logs - ALONG WITH COLUMN TITLES (if log doesn't previously exist)
		//	CString sCSVLogFN = BEMPX_GetLogFilename( true );				ASSERT( !sCSVLogFN.IsEmpty() );
			QString qsCSVLogFN = BEMPX_GetLogFilename( true );		CString sCSVLogFN = qsCSVLogFN.toLatin1().constData();		ASSERT( !sCSVLogFN.IsEmpty() );

			char pszCSVColLabel1[512], pszCSVColLabel2[1024], pszCSVColLabel3[2048];
			VERIFY( CMX_PopulateResultsHeader_NonRes( pszCSVColLabel1, 512, pszCSVColLabel2, 1024, pszCSVColLabel3, 2048, iCodeType ) == 0 );	// SAC 12/3/14
			const char* szaCSVColLabels[4]	=	{ pszCSVColLabel1, pszCSVColLabel2, pszCSVColLabel3, NULL };
			if (!sCSVLogFN.IsEmpty())
			{	sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
				             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
								 "(once the file is closed), or \n'Cancel' to abort the %s.", "CSV results log", sCSVLogFN, "writing of results to the file" );
				if (OKToWriteOrDeleteFile( sCSVLogFN, sMsg, (!BEMPX_GetUIActiveFlag()) ))
					VERIFY( BEMPX_WriteLogFile( pszCSVResultSummary, NULL, false /*bBlankFile*/, FALSE /*bSupressAllMessageBoxes*/,
															false /*bAllowCopyOfPreviousLog*/, szaCSVColLabels /*ppCSVColumnLabels*/ ) );
			}

			// SAC 10/10/16 - updated default T24N CSVResultsLog filename adding '-v2' for new CSV format that includes electric demand results
			// SAC 2/7/17 - updated default T24N CSVResultsLog filename adding '-v3' for new CSV format that includes process motors results
			// SAC 2/19/17 - updated default T24N CSVResultsLog filename adding '-v4' for new CSV format that includes total & cond flr areas, unregulated TDV results plus TDV by fuel type (for 2019.0.1 release)
			CString sAnalResDefault = (iCodeType == CT_S901G ? "AnalysisResults_S901G-v4.csv" : (iCodeType == CT_ECBC ? "AnalysisResults_ECBC-v4.csv" : "AnalysisResults-v4.csv"));
			CString sCSVResultsLogFN = ReadProgString( "files", "CSVResultsLog", sAnalResDefault, TRUE /*bGetPath*/ );
			VERIFY( AppendToTextFile( pszCSVResultSummary, sCSVResultsLogFN, "CSV results log", "writing of results to the file", szaCSVColLabels ) );
		}

	// Prompt user to view generated PDF compliance report (if analysis successful & PDF written)
		if (iSimResult == 0 && bPerformSimulations)
		{	long lCompRptPDFWritten=0, lCompRptStdWritten=0;
			BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompReportPDFWritten" ), lCompRptPDFWritten );
			BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:CompReportStdWritten" ), lCompRptStdWritten );
			if ( (lCompRptPDFWritten > 0 || lCompRptStdWritten > 0) && BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent report file review prompt when GUI deactivated
			{	CString sPDFRptFN = sOriginalFileName.Left( sOriginalFileName.ReverseFind('.') );
				CString sStdRptFN = sPDFRptFN;
				sPDFRptFN += " - AnalysisResults-BEES.pdf";
				sStdRptFN += " - AnalysisResults-BEES-Std.pdf";
				bool bHaveCompRpt = (lCompRptPDFWritten > 0 && FileExists( sPDFRptFN ));
				bool bHaveStdRpt  = (lCompRptStdWritten > 0 && FileExists( sStdRptFN ));
				if (lCompRptPDFWritten > 0 && !bHaveCompRpt)
				{	// report to log that PDF was expected but not found...
					sMsg.Format( "PDF compliance report not found:  %s", sPDFRptFN );
					VERIFY( BEMPX_WriteLogFile( sMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
				}
				if (lCompRptStdWritten > 0 && !bHaveStdRpt)
				{	// report to log that PDF was expected but not found...
					sMsg.Format( "PDF standard model report not found:  %s", sStdRptFN );
					VERIFY( BEMPX_WriteLogFile( sMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
				}

				if (bHaveCompRpt || bHaveStdRpt)
				{	// prompt user to view one or more PDF report(s)
					CString sBtn2File, sBtn3File, sBtn2Label, sBtn3Label, sAllLabel;
					if (bHaveCompRpt && !bHaveStdRpt)
					{	sMsg = "PDF compliance report successfully generated during analysis.";
						sBtn2File = sPDFRptFN;		sBtn2Label = "Compliance Report";
					}
					else if (!bHaveCompRpt && bHaveStdRpt)
					{	sMsg = "PDF standard model report successfully generated during analysis.";
						sBtn2File = sStdRptFN;		sBtn2Label = "Standard Model Report";
					}
					else
					{	sMsg = "PDF compliance and standard model reports successfully generated during analysis.";
						sBtn2File = sPDFRptFN;		sBtn2Label = "Compliance Report";
						sBtn3File = sStdRptFN;		sBtn3Label = "Standard Model Report";		sAllLabel = "Both Reports";
					}
					PromptToDisplayPDFs( "Analysis Report(s)", sMsg, sBtn2File, sBtn2Label, sBtn3File, sBtn3Label, "", "", sAllLabel );
				}
		}	}

		BOOL bSimResultsDisplayed = FALSE;
//		int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );
		int iNumEUseSummaryObjs = BEMPX_GetNumObjects( eiBDBCID_EUseSummary );
		if (iSimResult < 1)
		{	if (eiBDBCID_EUseSummary > 0 && iNumEUseSummaryObjs > 0)
			{	bSimResultsDisplayed = TRUE;
				//int iTabCtrlWd, iTabCtrlHt;
				//VERIFY( GetDialogTabDimensions( siQuickCr8Class, iTabCtrlWd, iTabCtrlHt ) );
				if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) > 1)	// SAC 9/13/13 - added to ensure first (worst case) EUseSummary obejct is ALWAYS the active obejct as dialog presented
					BEMPX_SetActiveObjectIndex( eiBDBCID_EUseSummary, 0 );

				CString sDialogCaption;
				GetDialogCaption( eiBDBCID_EUseSummary, sDialogCaption );
      		CWnd* pWnd = GetFocus();
      		CSACBEMProcDialog td( eiBDBCID_EUseSummary, 0 /*eiCurrentTab*/, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
      		                  0 /*iDlgMode*/, 810 /*iTabCtrlWd*/, 495 /*iTabCtrlHt*/, 99 /*iMaxTabs*/,
      		                  (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "Done",
										NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
										NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
										ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
				if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent results display when GUI deactivated
   	   		if (td.DoModal() == IDOK)
      			{}
			}
			else if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent error messagebox when GUI deactivated
				AfxMessageBox( "No analysis results available to display." );  // was: "Analysis succeeded but results retrieval error is preventing their display." );
		}
		else if (iSimResult != 66)		// SAC 7/6/16 - logic to prevent showing error dialog if return value => 66 : Analysis aborted - user chose to abort due to compliance reporting issue(s)
	//	{	CString sAnalRetVal;		sAnalRetVal.Format( "CMX_PerformAnalysis_CECNonRes() returned %d  -  %s", iSimResult, (iSimResult < 1 ? "SUCCESS!" : "user aborted and/or errors occurred.") );
	//		MessageBox( sAnalRetVal );
	// SAC 7/28/13 - added code from res analysis to display analysis error messages
		{	CString sErrResultMsg, sErrTmp;
			int iMaxErrCount = 10;  // SAC 7/28/13 - max # errors to display following analysis
			if (iSimResult == 33)		// unique return value indicating user aborted analysis
			{	sErrResultMsg.Format( "Analysis aborted by user (error code %d).", iSimResult );
				iMaxErrCount--;
			}
//				if (strlen( pszAnalysisErr ) > 1)
//					AfxMessageBox( pszAnalysisErr );
			if (strlen( pszAnalysisErr ) > 0)
			{	if (!sErrResultMsg.IsEmpty())
					sErrResultMsg += "\n\n";
				sErrResultMsg += pszAnalysisErr;
				iMaxErrCount -= std::min( 1, std::max( 6, (int) (strlen( pszAnalysisErr )/120) ) );
			}
			if (iMaxErrCount > 0)
			{	int iNumErrors = BEMPX_GetRulesetErrorCount();
				if (iNumErrors > 0)
				{	CString sRuleErrMsg;
					char pszRuleErr[1024];
					//sErrResultMsg.Format( "%d Error(s) encountered performing analysis (error code %d).", iNumErrors, iSimResult );
					int iErrCount = 0;
					for (int iErr=1; iErr<=iNumErrors; iErr++)
					{	if (BEMPX_GetRulesetErrorMessage( iErr, pszRuleErr, 1024 ))
						{	// filter out generic messages that indicate certain rulelists failing
							if (	_strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rulelist 'ProposedModel", 60 ) == 0 )		// ProposedModelCodeCheck / SimulationCheck / CodeAdditions
							{	// do not report these errors which are always accommpanied by error messages, even when in Verbose mode...
							}
							else if (iVerbose > 0 || _strnicmp( pszRuleErr, "ERROR:  Error encountered evaluating rule", 41 ) != 0)
							{	iErrCount += 1;
								if (iErrCount <= iMaxErrCount)
								{	if (iNumErrors < 2)
										sErrTmp.Format( "\n\n%s", pszRuleErr );
									else
										sErrTmp.Format( "\n\n(%d) %s", iErrCount, pszRuleErr );
									if (iVerbose == 0)
									{	// if verbose flag NOT set, then strip off details of rule where error occurred
										int iRuleDetailIdx = sErrTmp.Find( "evaluating rule: Rule" );
										if (iRuleDetailIdx > 0)
											sErrTmp = sErrTmp.Left( iRuleDetailIdx );
									}
									sRuleErrMsg += sErrTmp;
								}
							}
						}
						else
						{	ASSERT( FALSE );
						}
					}	ASSERT( (iErrCount > 0 || sRuleErrMsg.IsEmpty()) );
					if (sRuleErrMsg.IsEmpty())
						sRuleErrMsg.Format( "%d Error(s) encountered performing analysis (error code %d).", iNumErrors, iSimResult );
					else
					{	if (iErrCount <= iMaxErrCount)
							sErrTmp.Format( "%d Error(s) encountered performing analysis (error code %d):", iErrCount, iSimResult );
						else
							sErrTmp.Format( "%d Error(s) encountered performing analysis (error code %d):\n     (first %d reported below, all are listed in project log file)", iErrCount, iSimResult, iMaxErrCount );
						sRuleErrMsg = sErrTmp + sRuleErrMsg;
					}
					if (!sRuleErrMsg.IsEmpty())
					{	if (!sErrResultMsg.IsEmpty())
							sErrResultMsg += "\n\n";
						sErrResultMsg += sRuleErrMsg;
					}
			}	}
			if (sErrResultMsg.IsEmpty())
				sErrResultMsg.Format( "Error encountered performing analysis (error code %d).", iSimResult );
			if (BEMPX_GetUIActiveFlag()) 		// SAC 2/24/14 - prevent error messagebox when GUI deactivated
				AfxMessageBox( sErrResultMsg );
			else
				VERIFY( BEMPX_WriteLogFile( sErrResultMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
		}

	// SAC 6/3/13 - added code to initiate re-load of original project data (following prompt if in debug mode of verbose analysis is selected)
	//	BOOL bReloadProjectFile = ( ReadProgInt( "options", "LogRuleEvaluation",  0 /*default*/ ) == 0  &&
	//										 ReadProgInt( "options", "AnalysisThruStep" ,  8 /*default*/ ) >= 8 );		// SAC 6/11/14 - switched default and value checked for from 11 to 8
	// SAC 6/12/14 - added separate INI file option to determine whether or not to prompt user to re-open project file
		BOOL bReloadProjectFile = ( ReadProgInt( "options", "PromptToReloadProjectFile", 0 /*default*/ ) == 0 );
#ifdef _DEBUG
		bReloadProjectFile = FALSE;
#endif
		if (!bReloadProjectFile &&
				(!BEMPX_GetUIActiveFlag() || 		// SAC 2/24/14 - prevent user prompt when GUI deactivated
				  MessageBox( "Project data currently available in the user interface reflects the final state of the analysis, not the original (user-defined) building model.\n\n"
									"Would you like to reload the original project file?", "Reload Project?", MB_YESNO ) == IDYES))
			bReloadProjectFile = TRUE;
		if (bReloadProjectFile)
		{
			QVector<QString> saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles, saNewEUseSumObjs;
	// SAC 10/3/14 - mod to store EUseSummary obejcts to project file regardless of whether sim results were displayed
	//		if (bSimResultsDisplayed)
				VERIFY( CMX_SaveAnalysisResultsToTempFiles( saProjEUseSumObjs, saUniqueEUseSumObjs, saTempPathFiles ) == 0 );  // SAC 2/1/14

			((CComplianceUIDoc*) pDoc)->OpenTheFile( sOriginalFileName, TRUE /*bWriteToLog*/, FALSE /*bRestore*/, NULL /*pszNewRuleFile*/,
            													-1 /*lRulesetSymVal*/, FALSE /*bNormalRulesetUpdates*/ );	// SAC 11/17/15

// PROMPT USER TO STORE RESULTS TO PROJECT FOR LATER REVIEW ????

		// SAC 6/25/13 - AFTER restoring original project file, Import EUseSummary objects from temporary files to facilitate subsequent results display
	// SAC 10/3/14 - mod to store EUseSummary obejcts to project file regardless of whether sim results were displayed
	//		if (bSimResultsDisplayed && saUniqueEUseSumObjs.GetSize())
			int iNumEUseSUmObjs = BEMPX_GetNumObjects( eiBDBCID_EUseSummary );
			if (saUniqueEUseSumObjs.size() || iNumEUseSUmObjs > 0)
			{	int iError;
				if (saUniqueEUseSumObjs.size())
					VERIFY( CMX_RestoreAnalysisResultsFromTempFiles( saUniqueEUseSumObjs, saTempPathFiles ) == 0 );  // SAC 2/1/14
				else	// if no EUseSummary objects in model following analysis, then delete those in the user model prior to re-saving the project (so OLD results don't hang around in the latest project file)
					for (int iEUSidx=0; iEUSidx < iNumEUseSUmObjs; iEUSidx++)
					{	BEMObject* pEUSObj = BEMPX_GetObjectByClass( eiBDBCID_EUseSummary, iError, iEUSidx );			ASSERT( pEUSObj );
						if (pEUSObj)
							BEMPX_DeleteObject( pEUSObj );
					}

				// ALSO store RunDate to be help verify whether results are "current"
				ASSERT( lTime > 0);
				if (lTime > 0)
					BEMPX_SetBEMData( elDBID_Proj_RunDate, BEMP_Int, (void*) &lTime );

			// SAVE PROJECT FILE
				SaveFile( NULL, lTime-1 );
			}
		}
   }


#endif


   }
	m_bPerformingAnalysis = FALSE;

   return lRetVal;
}

void CMainFrame::OnPerformAPIAnalysis()
{
//	UpdateSoftwareVersionString();		// SAC 9/17/12		// SAC 1/13/15 - prevent unnecessarily modifying project file before analysis, so that proj files can flow into analysis unchanged
	if (m_bPerformingAnalysis)		// SAC 4/1/15 - prevent initiation of analysis if analysis already underway
	{	MessageBeep( MB_OK );
	   return;
	}
	m_bPerformingAnalysis = TRUE;

   CDocument* pDoc = GetActiveDocument();
   if ( (pDoc != NULL) && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) &&
        (((CComplianceUIDoc*) pDoc)->CUISaveModified( "compliance analysis" )) )
   {
      CString sMsg, sTemp, sOptionsCSVString;
      CString sCurrentFileName = pDoc->GetPathName();
      CString sOriginalFileName = sCurrentFileName;
      CString sProjectPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('\\') + 1 );
		char pszAnalysisErr[2056] = "\0";
      CTime time = CTime::GetCurrentTime();
//      long lTime = (long) time.GetTime();

		CComplianceUIApp* pApp = (CComplianceUIApp*)AfxGetApp();  // SAC 11/11/13 - moved outside sector-specific sections
		BOOL bPerformSimulations = pApp->PerformSimulations();		
		bPerformSimulations &= (m_bDoingSummaryReport == FALSE);  // SAC 6/19/13

		CString sProcessingPath = sCurrentFileName.Left( sCurrentFileName.ReverseFind('.') );
		sProcessingPath += " - runAPI\\";
		CString sUIVersionString;
		GetProgramVersion( sUIVersionString );																													ASSERT( !sUIVersionString.IsEmpty() );
	   CString sWthrPath = ReadProgString( "paths", "WeatherPath", "EPW\\", TRUE );
		// SAC 1/29/14 - consolidated all options string population into single routine shared by live & batch analyses functions
		VERIFY( PopulateAnalysisOptionsString( sOptionsCSVString ) );		// SAC 1/29/14

		CString sBEMBasePathFile = ReadProgString( "files", "BEMFile", "", TRUE );						ASSERT( FileExists( sBEMBasePathFile ) );
		CString sRulePathFile = ReadProgString( "paths", "RulesetPath", "", TRUE );					ASSERT( !sRulePathFile.IsEmpty() );
		CString sRuleFile = ReadProgString( "files", "RulesetFile", "" );									ASSERT( !sRuleFile.IsEmpty() );
		sRulePathFile += sRuleFile;																					ASSERT( FileExists( sRulePathFile ) );

		int iAnalysisResult = 0;

#ifdef UI_CARES

		const char* pszAnalOpts = NULL;
		if (!sOptionsCSVString.IsEmpty())
			pszAnalOpts = (const char*) sOptionsCSVString;

		CString sCSEPath = esProgramPath + "CSE\\";
		sCSEPath = ReadProgString( szPaths, "CSEPath", sCSEPath, TRUE );  // in case there is one in the INI to override the default
		CString sT24DHWPath = esProgramPath + "T24DHW\\";
		sT24DHWPath = ReadProgString( szPaths, "T24DHWPath", sT24DHWPath, TRUE );  // in case there is one in the INI to override the default

			CString sLogAnalArg = "Arguments of CMX_PerformAnalysisCB_CECRes();";			BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   BEMBasePathFile  = %s", sBEMBasePathFile );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   RulesetPathFile  = %s", sRulePathFile );					BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   CSEEXEPath       = %s", sCSEPath );							BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   CSEWeatherPath   = %s", sCSEPath );							BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   DHWDLLPath       = %s", sT24DHWPath );						BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   DHWWeatherPath   = (null)" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   ProcessingPath   = %s", sProcessingPath );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   ModelPathFile    = %s", sCurrentFileName );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   LogPathFile      = (null)" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   UIVersionString  = %s", sUIVersionString );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   LoadModelFile    = true" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   OptionsCSVString = %s", pszAnalOpts );						BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   pszAnalysisErr   = (ptr to str)" );							BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   AnalysisErrLen   = 2056" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   DisplayProgress  = true" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   ProgCallbackFunc = (null)" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );

//int DLLAPI __cdecl CMX_PerformAnalysisCB_CECRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile, const char* pszCSEEXEPath, const char* pszCSEWeatherPath,
//												const char* pszDHWDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath, const char* pszModelPathFile, const char* pszLogPathFile,
//												const char* pszUIVersionString,
//												bool bLoadModelFile=true, const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0,
//												bool bDisplayProgress=false, PAnalysisProgressCallbackFunc pAnalProgCallbackFunc=NULL );

					EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
		iAnalysisResult = CMX_PerformAnalysisCB_CECRes( sBEMBasePathFile /*pszBEMBasePathFile*/, sRulePathFile /*pszRulesetPathFile*/,	sCSEPath /*pszCSEEXEPath*/, sCSEPath /*pszCSEWeatherPath*/,
																	sT24DHWPath /*pszDHWDLLPath*/, NULL /*pszDHWWeatherPath*/, sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
																	NULL /*pszLogPathFile*/, sUIVersionString, true /*bLoadModelFile*/, pszAnalOpts, pszAnalysisErr, 2056, true /*bDisplayProgress*/, 
																	1 /*SecKeyIndex*/, esSecurityKey, NULL /*callback func ptr*/ );
					EnableWindow( TRUE );
#elif UI_CANRES

	// storage of ProjFileName - added to non-res processing from res
   //   CString sProjFileName = sCurrentFileName.Right( sCurrentFileName.GetLength() - sProjectPath.GetLength() );
	//	BEMPX_SetBEMData( BEMPX_GetDatabaseID( "ProjFileName", BEMPX_GetDBComponentID( "Proj" ) ), BEMP_Str, (void*) ((const char*) sProjFileName) );

				BOOL bHaveSizingPropRL = FALSE;
   		   QVector<QString> saRulelistNames;
   			int iNumRulelists = CMX_GetRulelistNames( saRulelistNames );
   			for (int iRL=0; (!bHaveSizingPropRL && iRL<iNumRulelists); iRL++)
   			   bHaveSizingPropRL = (saRulelistNames[iRL].compare( "rl_SIZING_PROPOSED", Qt::CaseInsensitive ) == 0);
				ASSERT( bHaveSizingPropRL );

			CString sLogAnalArg = "Arguments of CMX_PerformAnalysisCB_NonRes();";			BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   BEMBasePathFile  = %s", sBEMBasePathFile );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   RulesetPathFile  = %s", sRulePathFile );					BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   SimWeatherPath   = %s", sWthrPath );						BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   CompMgrDLLPath   = %s", esProgramPath );					BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   DHWWeatherPath   = (null)" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   ProcessPath      = %s", sProcessingPath );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   ModelPathFile    = %s", sCurrentFileName );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   LogPathFile      = (null)" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   UIVersionString  = %s", sUIVersionString );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   LoadModelFile    = true" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   OptionsCSVString = %s", sOptionsCSVString );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   pszAnalysisErr   = (ptr to str)" );							BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   AnalysisErrLen   = 2056" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   DisplayProgress  = true" );									BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );
			sLogAnalArg.Format( "   hWnd             = (valid MainFrm hWnd)" );				BEMPX_WriteLogFile( sLogAnalArg, NULL, FALSE /*bBlank*/, TRUE /*bSupressMsgBxs*/, FALSE /*bCopyPrevLog*/ );

		pszCSVResultSummary[0] = '\0';
	siNonResAnalCallbackCount = 0;
					EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
		iAnalysisResult = CMX_PerformAnalysisCB_NonRes(	sBEMBasePathFile, sRulePathFile, sWthrPath /*pszSimWeatherPath*/,
																	esProgramPath /*pszCompMgrDLLPath*/, NULL /*pszDHWWeatherPath*/,
																	sProcessingPath /*pszProcessPath*/, sCurrentFileName /*pszModelPathFile*/,
																	NULL /*pszLogPathFile*/, sUIVersionString, true /*bLoadModelFile*/, sOptionsCSVString,
																	pszAnalysisErr, 2056, true /*bDisplayProgress*/, /*GetSafeHwnd(),*/ pszCSVResultSummary, CSV_RESULTSLENGTH, 
																	1 /*SecKeyIndex*/, esSecurityKey,   // SAC 1/10/17
																	(PAnalysisProgressCallbackFunc) NonResAnalysisProgressCallbackFunc );
					EnableWindow( TRUE );
#endif

		CString sRetMsg;
		if (iAnalysisResult == 0)
			sRetMsg = "Analysis completed successfully!";
		else
			sRetMsg.Format( "Analysis failed - return code %d.  Examine log file for more information:\n%s", iAnalysisResult, sCurrentFileName );
		sRetMsg += "\n\nPress OK to exit the application.";
		AfxMessageBox( sRetMsg );
		PostMessage( WM_COMMAND, ID_APP_EXIT, 0L );

   }
	m_bPerformingAnalysis = FALSE;

//   return lRetVal;
}

void CMainFrame::OnUpdatePerformAnalysis(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnUpdatePerformAPIAnalysis(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}

void CMainFrame::OnMPerformAnalysis() 
{
   OnPerformAnalysis(0,0);
}


void CMainFrame::OnUpdateToolsUMLHViolations(CCmdUI* pCmdUI)		// SAC 3/18/15
{
	BOOL bEnable = FALSE;
#ifdef UI_CANRES
	bEnable = (eInterfaceMode == IM_INPUT);
	CDocument* pDoc = GetActiveDocument();
	if (bEnable && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	CString sUMLHFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sUMLHFileName += " - UMLH Zones.txt";
			bEnable = FileExists( sUMLHFileName );
	}	}
//#elif UI_CARES
//   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#endif
   pCmdUI->Enable( bEnable );
}

void CMainFrame::OnToolsUMLHViolations()		// SAC 3/18/15
{	CString sErrMsg;
	CDocument* pDoc = GetActiveDocument();
	if (pDoc==NULL || !pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
		sErrMsg = "No project loaded.";
	else
	{  CString sProjFileName = pDoc->GetPathName();
		if (sProjFileName.IsEmpty() || sProjFileName.ReverseFind('.') < 2)
			sErrMsg = "Current project data has not yet saved or analyzed, so UMLH violations are not available.";
		else
		{	CString sUMLHFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sUMLHFileName += " - UMLH Zones.txt";
			if (!FileExists( sUMLHFileName ))
				sErrMsg.Format( "UMLH violations text file not found, because either the project has not been analyzed or no UMLH violations were found:\n   %s", sUMLHFileName );
			else
				OpenFileViaShellExecute( sUMLHFileName, "Compliance Report" /*FileDescrip*/ );
	}	}
	if (!sErrMsg.IsEmpty())
		AfxMessageBox( sErrMsg );
}


void CMainFrame::OnUpdateToolsViewCSEErrors(CCmdUI* pCmdUI)
{
	BOOL bFileExists = FALSE;
	CString sRptFileName;
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sRptFileName += " - CSE Errors.txt";
			bFileExists = FileExists( sRptFileName );
	}	}

#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && bFileExists) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && bFileExists) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnUpdateToolsViewCSEReports(CCmdUI* pCmdUI)
{
	BOOL bFileExists = FALSE;
	CString sRptFileName;
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sRptFileName += " - CSE Reports.txt";
			bFileExists = FileExists( sRptFileName );
	}	}

#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && bFileExists) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && bFileExists) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsViewCSEErrors()
{
	CString sRptFileName;
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sRptFileName += " - CSE Errors.txt";
			if (FileExists( sRptFileName ))
				OpenFileViaShellExecute( sRptFileName, "CSE Errors output" );
	}	}
}

void CMainFrame::OnToolsViewCSEReports()
{
	CString sRptFileName;
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sRptFileName += " - CSE Reports.txt";
			if (FileExists( sRptFileName ))
				OpenFileViaShellExecute( sRptFileName, "CSE Reports output" );
	}	}
}


void CMainFrame::OnUpdateToolsReviewResults(CCmdUI* pCmdUI)		// SAC 6/25/13
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsReviewResults()		// SAC 6/26/13
{
#ifdef UI_CARES
//	int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );						ASSERT( iCID_EUseSummary > 0 );
	if (eiBDBCID_EUseSummary < 1)
		AfxMessageBox( "Error identifying EUseSummary class ID." );
	else if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) < 1)
		AfxMessageBox( "Analysis results not found for this project.\nYou must perform the analysis (via calculator button) before reviewing analysis results." );
	else
	{	CDocument* pDoc = GetActiveDocument();
		BOOL bResultsCurrent = (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) && !((CComplianceUIDoc*) pDoc)->IsModified());
		if (bResultsCurrent)
		{	long lModDate, lRunDate = 0;
			VERIFY( BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ) );
			VERIFY( BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate ) );
			bResultsCurrent = (lRunDate > 1 && lRunDate >= lModDate);
		}	// now we know (more or less) whether the results stored in project data are 'current'
		if (!bResultsCurrent)
			// if results are NOT current, then mark them as such
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ResultsCurrentMsg" ), BEMP_Str, (void*) ((const char*) "(not current)") );

		if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) > 1)	// SAC 9/13/13 - added to ensure first (worst case) EUseSummary obejct is ALWAYS the active obejct as dialog presented
			BEMPX_SetActiveObjectIndex( eiBDBCID_EUseSummary, 0 );

		CString sDialogCaption;
		GetDialogCaption( eiBDBCID_EUseSummary, sDialogCaption );
		CWnd* pWnd = GetFocus();
		CSACBEMProcDialog td( eiBDBCID_EUseSummary, 0 /*eiCurrentTab*/, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
		                  0 /*iDlgMode*/, 810 /*iTabCtrlWd*/, 440 /*iTabCtrlHt*/, 99 /*iMaxTabs*/,
		                  (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "Done",
								NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
								NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
								ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
		if (td.DoModal() == IDOK)
		{}
	}
#elif UI_CANRES
//	int iCID_EUseSummary = BEMPX_GetDBComponentID( "EUseSummary" );						ASSERT( iCID_EUseSummary > 0 );
	if (eiBDBCID_EUseSummary < 1)
		AfxMessageBox( "Error identifying EUseSummary class ID." );
	else if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) < 1)
		AfxMessageBox( "Analysis results not found for this project.\nYou must perform the analysis (via calculator button) before reviewing analysis results." );
	else
	{	CDocument* pDoc = GetActiveDocument();
		BOOL bResultsCurrent = (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) && !((CComplianceUIDoc*) pDoc)->IsModified());
		if (bResultsCurrent)
		{	long lModDate, lRunDate = 0;
			VERIFY( BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ) );
			VERIFY( BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:RunDate" ), lRunDate ) );
			bResultsCurrent = (lRunDate > 1 && lRunDate >= lModDate);
		}	// now we know (more or less) whether the results stored in project data are 'current'
		if (!bResultsCurrent)
			// if results are NOT current, then mark them as such
			BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:ResultsCurrentMessage" ), BEMP_Str, (void*) ((const char*) "(not current)") );

		if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) > 1)
			BEMPX_SetActiveObjectIndex( eiBDBCID_EUseSummary, 0 );

		CString sDialogCaption;
		GetDialogCaption( eiBDBCID_EUseSummary, sDialogCaption );
		CWnd* pWnd = GetFocus();
		CSACBEMProcDialog td( eiBDBCID_EUseSummary, 0 /*eiCurrentTab*/, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pWnd,
		                  0 /*iDlgMode*/, 810 /*iTabCtrlWd*/, 495 /*iTabCtrlHt*/, 99 /*iMaxTabs*/,
		                  (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "Done",
								NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
								NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
								ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );
		if (td.DoModal() == IDOK)
		{}
	}
#else
	AfxMessageBox( "Review analysis results only available in 2013 Residential Title-24 mode." );
#endif
}


void CMainFrame::ViewReport( int iReportID /*=0*/ )		// SAC 11/18/15
{

//// TESTING
//	char *toEncode = "String_To-Encode!?";
//
////	char  strEncrypted[50];		strEncrypted[0]=0;
////	long lEncRetVal = CMX_Encrypt( (const unsigned char*) toEncode, strlen(toEncode), strEncrypted, 50 );		lEncRetVal;
//
//	char  strEncoded[30];	strEncoded[0]=0;
//	char  strDecoded[30];	strDecoded[0]=0;
//	char  strScrEncoded[2048];	strScrEncoded[0]=0;
//	char  strScrDecoded[2048];	strScrDecoded[0]=0;
//	long lEncdRet = CMX_EncodeBase64( (const unsigned char*) toEncode, strlen(toEncode), strEncoded, 30 );
//	int  iDecdRet = CMX_DecodeBase64( strDecoded, strEncoded );
//	memset( strScrEncoded, 0, sizeof(char)*2048 );
//	memset( strScrDecoded, 0, sizeof(char)*2048 );
//	long lScrEncdRet = CMX_EncodeBase64( (const unsigned char*) toEncode, strlen(toEncode), strScrEncoded, 2048, true );
//	int  iScrDecdRet = CMX_DecodeBase64( strScrDecoded, strScrEncoded, true );
//	CString sBEMExeSecure = (BEMPX_SecureExecutable() ? "Secure" : "NOT Secure" );
//	CString sCMExeSecure  = (  CMX_SecureExecutable() ? "Secure" : "NOT Secure" );
//	CString sTestMsg;
//	sTestMsg.Format( "Executable Security:\n   BEMProc:  %s\n   BEMCmpMgr:  %s\n\nEncoding '%s'\nNOT Secure --\n   Encode returned %d:  %s\n   Decode returned %d:  %s\n"
//																																	"SECURE --\n   Encode returned %d:  %s\n   Decode returned %d:  %s",
//							sBEMExeSecure, sCMExeSecure, toEncode, lEncdRet, strEncoded, iDecdRet, strDecoded, lScrEncdRet, strScrEncoded, iScrDecdRet, strScrDecoded );
//	AfxMessageBox( sTestMsg );
//
//	memset( strScrEncoded, 0, sizeof(char)*2048 );
//	memset( strScrDecoded, 0, sizeof(char)*2048 );
//	int iEncrRet = CMX_Encrypt( (unsigned char*) toEncode, strlen(toEncode)+1, (unsigned char*) strScrEncoded );
//	int iDecrRet = CMX_Decrypt( (unsigned char*) strScrEncoded, iEncrRet, (unsigned char*) strScrDecoded );
//	sTestMsg.Format( "Encrypt/decrypt test:\n   Encoding '%s'\n   Encrypt returned %d:  %s\n   Decrypt returned %d:  %s",
//							toEncode, iEncrRet, strScrEncoded, iDecrRet, strScrDecoded );
//	AfxMessageBox( sTestMsg );

	CString sAppendForResults = " - AnalysisResults.xml";
#ifdef UI_CARES
	ASSERT( iReportID == 0 );
	CString sReportLabel  = "Compliance Report";
	CString sRptDBIDName  = "Proj:CompReportPDF";
	CString sAppendForPDF = " - AnalysisResults-BEES.pdf";
	CString sAppendForXML = " - AnalysisResults-BEES.xml";  // SAC 11/29/16
#elif UI_CANRES
	CString sReportLabel  = (iReportID == 3 ? "Standard Model Report"					: "Compliance Report" );
	CString sRptDBIDName  = (iReportID == 3 ? "Proj:CompReportStd"						: "Proj:CompReportPDF" );
	CString sAppendForPDF = (iReportID == 3 ? " - AnalysisResults-BEES-Std.pdf"	: " - AnalysisResults-BEES.pdf" );
	CString sAppendForXML = (iReportID == 3 ? ""                               	: " - AnalysisResults-BEES.xml" );
#else
	AfxMessageBox( "Report viewing only available in California Title-24 CBECC-* programs." );
	return;
#endif
	CString sProjFileName, sRptFileName, sResXMLFileName, sUserPrompt, sRptXMLFileName;
	int iActionToPerform = 0;
	CDocument* pDoc = GetActiveDocument();
	CString sErrMsg = "Project data must be stored to a valid file and analysis performed before viewing a compliance report.";
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	{  sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sErrMsg.Empty();
			sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			if (!sAppendForXML.IsEmpty())  // SAC 11/29/16
				sRptXMLFileName = sRptFileName + sAppendForXML;
			sRptFileName += sAppendForPDF;
			if (FileExists( sRptFileName ))
				iActionToPerform = 1;
			else if (!sRptXMLFileName.IsEmpty() && FileExists( sRptXMLFileName ) &&		// SAC 11/29/16 - added to extract PDF from report XML file (if XML present but PDF not)
						CMX_ExtractTitle24ReportFromXML( sRptXMLFileName, sRptFileName ))  //, const char* rptElemName /*=NULL*/, BOOL bSupressAllMessageBoxes /*=FALSE*/ )
				iActionToPerform = 1;
			else
			{	sResXMLFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
				sResXMLFileName += sAppendForResults;
				if (FileExists( sResXMLFileName ))
				{	// prompt user to generate PDF report
					sUserPrompt.Format( "Report file not found:\n%s\n\nWould you like to generate a new report based on the following analysis results file?\n%s", sRptFileName, sResXMLFileName );
					if (MessageBox( sUserPrompt, sReportLabel, MB_YESNO ) == IDYES)
						iActionToPerform = 2;
				}
				else
				{	// prompt user to perform analysis if neither a report nor results XML is found
					sUserPrompt = "Neither report or analysis results files were found.\nWould you like to initiate analysis for this project?";
					if (MessageBox( sUserPrompt, sReportLabel, MB_YESNO ) == IDYES)
						iActionToPerform = 3;
	}	}	}	}

	switch (iActionToPerform)
	{	case  1 :	OpenFileViaShellExecute( sRptFileName, sReportLabel /*FileDescrip*/ );		break;		// Open report PDF 
		case  2 :	if (iReportID == 3)
							OnToolsT24StandardModelReport();		// SAC 11/18/15
						else
							OnToolsT24ComplianceReport();															break;		// Generate T-24 report
		case  3 :	// before initiating analysis, make sure PDf report generation toggled on							// Perform analysis
					{	long lCompRptPDF=0;
						if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( sRptDBIDName ), lCompRptPDF ) && lCompRptPDF < 1)
						{	lCompRptPDF=1;
							VERIFY( BEMPX_SetBEMData( BEMPX_GetDatabaseID( sRptDBIDName ), BEMP_Int, (void*) &lCompRptPDF ) >= 0 );	// set Proj flag to ensure report output
						}
						OnPerformAnalysis(0,0);
					}	break;
		default :	if (!sErrMsg.IsEmpty())
							AfxMessageBox( sErrMsg );
	}
}

void CMainFrame::OnUpdateToolsViewT24ComplianceReport(CCmdUI* pCmdUI)		// SAC 9/2/14
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsViewT24ComplianceReport()		// SAC 9/2/14
{
	ViewReport( 0 );
}

void CMainFrame::OnUpdateToolsViewT24StandardModelReport(CCmdUI* pCmdUI)		// SAC 11/18/15
{
#ifdef UI_CARES
   pCmdUI->Enable( FALSE );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}
void CMainFrame::OnToolsViewT24StandardModelReport()		// SAC 11/18/15
{
	ViewReport( 3 );
}


void CMainFrame::OnUpdateToolsT24ComplianceReport(CCmdUI* pCmdUI)		// SAC 5/17/13
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}
void CMainFrame::OnToolsT24ComplianceReport()		// SAC 5/17/13
{
#ifdef UI_CARES
	int iReportID = 0;
#elif UI_CANRES
	int iReportID = 1;
#else
	int iReportID = -1;
	AfxMessageBox( "Title-24 compliance report generation only available in 2013 Title-24 mode." );
#endif
	if (iReportID >= 0)
		GenerateReport( iReportID );
}

void CMainFrame::OnUpdateToolsT24StandardModelReport(CCmdUI* pCmdUI)		// SAC 11/18/15
{
#ifdef UI_CARES
   pCmdUI->Enable( FALSE );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}
void CMainFrame::OnToolsT24StandardModelReport()		// SAC 11/18/15
{
#ifdef UI_CARES
	int iReportID = -1;
	AfxMessageBox( "Title-24 standard model report generation only available in Title-24 Nonresidential mode." );
#elif UI_CANRES
	int iReportID = 3;
#else
	int iReportID = -1;
	AfxMessageBox( "Title-24 standard model report generation only available in California Title-24 mode." );
#endif
	if (iReportID >= 0)
		GenerateReport( iReportID );
}


void CMainFrame::OnUpdateToolsCAHPReport(CCmdUI* pCmdUI)	
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}
void CMainFrame::OnToolsCAHPReport()		// SAC 10/8/14
{
#ifdef UI_CARES
	// check to ensure this IS a CAHP project and there are some CAHP results before generating report
	CString sRptGenCompReport;		BEMObject* pEUseSumObj;		int iEUseSumObjIdx, iError;		double fCAHPIncFinal=-999;
	BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:CAHPReportID" ), sRptGenCompReport );
//	BEMPX_SetDataObject( BEMPX_GetDatabaseID( "Proj:ResultSummary[1]" ), pEUseSumObj );
// SAC 5/28/15 - instead of retriving the EUseSummayr obejct assigned to the Proj, simply grab the first available one (since it MAY nto be assiged to the Proj at this point)
	pEUseSumObj = BEMPX_GetObjectByClass( eiBDBCID_EUseSummary, iError, 0 /*iObjIdx*/ );  // , BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
	if (pEUseSumObj && pEUseSumObj->getClass())
	{	iEUseSumObjIdx = BEMPX_GetObjectIndex( pEUseSumObj->getClass(), pEUseSumObj );
		if (iEUseSumObjIdx >= 0)
			BEMPX_GetFloat( BEMPX_GetDatabaseID( "EUseSummary:CAHPIncFinal" ), fCAHPIncFinal, -999, -1, iEUseSumObjIdx );
	}
	if (sRptGenCompReport.GetLength() < 1)
		AfxMessageBox( "CAHP/CMFNH report generation not available when CAHP/CMFNH program not selected.\nCAHP/CMFNH options must be specified in Project > CAHP/CMFNH dialog tab and analysis performed before this report can be generated." );
	else if (fCAHPIncFinal == -999)
		AfxMessageBox( "Cannot generate report due to lack of CAHP/CMFNH results.\nSuccessful analysis must be performed before this report can be generated." );
	else
		GenerateReport( 2 /*iReportID*/ );
#else
	AfxMessageBox( "CAHP/CMFNH report generation only available in 2013 Title-24 mode." );
#endif
}


BOOL CMainFrame::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	if (CPersistentWaitCursor::WaitCursorShown())
	{	// We want to be showing the wait cursor
		RestoreWaitCursor();
		return TRUE;
	}
	// Let the base class deal with this one
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

// iReportID  =>	0 : CARES2013
//						1 : CANRES2013
//						2 : CAHP/CMFNH
void CMainFrame::GenerateReport( int iReportID )		// SAC 10/8/14
{
	if (iReportID >= 0)
	{
		BOOL bIsUIActive = BEMPX_GetUIActiveFlag();		// was: (pApp ? pApp->IsUIActive() : TRUE);				// SAC 5/2/14 - toggle messagebox display OFF for batch processing
		CString sErrMsg, sResXMLFileName;
	   CDocument* pDoc = GetActiveDocument();
	   CString sProjFileName;
	   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
	   {  sProjFileName = pDoc->GetPathName();
			if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
			{	sResXMLFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
				sResXMLFileName += " - AnalysisResults.xml";
			}
			if (!FileExists( sResXMLFileName ))
				sErrMsg.Format( "Analysis results file not found:  %s", sResXMLFileName );
		}
		else
			sErrMsg = "Error locating/identifying project data.  Make sure project data is saved and analysis performed prior to selecting this option.";

		if (!sErrMsg.IsEmpty())
			AfxMessageBox( sErrMsg );
		else
		{	sErrMsg.Empty();
			CString sAppendToFN, sRptGenCompReport, sRptType, sRptTypeLong;
			switch (iReportID)
			{	case  2 :	BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:CAHPReportID" ), sRptGenCompReport );
			      			if (sRptGenCompReport.IsEmpty())
			      				sErrMsg = "The ruleset selected for this project does not define a Standard Model report ID (Proj:CAHPReportID) and therefore the report cannot be generated.";
								sAppendToFN.Format( " - %s.pdf", (sRptGenCompReport.IsEmpty() ? "CAHP-CMFNH" : sRptGenCompReport) );
								sRptType = "CAHP/CMFNH";			sRptTypeLong = "CAHP/CMFNH Report";
								break;
				case  3 :	// T-24 Nonres Standard Model report - SAC 11/18/15
			      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenStdReport" ), sRptGenCompReport );
			      			if (sRptGenCompReport.IsEmpty())
			      				sErrMsg = "The ruleset selected for this project does not define a Standard Model report ID (Proj:RptGenStdReport) and therefore the report cannot be generated.";
								sAppendToFN = " - AnalysisResults-BEES-Std.pdf";
								sRptType = "standard model";		sRptTypeLong = "Standard Model Report";
								break;
				default :	sAppendToFN = " - AnalysisResults-BEES.pdf";
								sRptType = "compliance";			sRptTypeLong = "Compliance Report";
								break;
			}

			CString sMsg, sOutRptFN = (sProjFileName.ReverseFind('.') > 0 ? sProjFileName.Left( sProjFileName.ReverseFind('.') ) : sProjFileName);
			sOutRptFN += sAppendToFN;
			sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
			             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
							 "(once the file is closed), or \n'Cancel' to abort the %s.", "PDF", sOutRptFN, "report generation" );
			if (!sErrMsg.IsEmpty())
				AfxMessageBox( sErrMsg );
			else if (OKToWriteOrDeleteFile( sOutRptFN, sMsg ))
		   {
			// SAC 6/15/16 - added logic to check report generator availability PRIOR to report generation (depending on EnableRptGenStatusChecks INI option)
				bool bContinue = true;
				if (bIsUIActive && ReadProgInt( "options", "EnableRptGenStatusChecks", 1 /*default*/ ) > 0 && !CheckReportGenAccess( false ))
				{	CString sNoRptGenMsg;
					// check whether user still wishes to generate a report even if report gen not available...
					sNoRptGenMsg.Format( "The report generator is currently offline.\nIf your network provides web access via a proxy server, "
												"make sure the proxy address and credentials are correct.  You can find these settings in:  "
												"Tools > Proxy Server Settings.\n\nWould you still like to generate a %s report?", sRptType );
			//		if (BEMMessageBox( sNoRptGenMsg, "Report Generation", MB_YESNO | MB_DEFBUTTON2 ) == IDNO)
					if (BEMMessageBox( sNoRptGenMsg, "Report Generation", 4 /*question*/, (QMessageBox::Yes | QMessageBox::No), QMessageBox::No ) == QMessageBox::No)
				   	bContinue = false;
				}

				if (bContinue)
				{
					CString sCACertPath = esProgramPath;
					if (sCACertPath[sCACertPath.GetLength()-1] == '\\')
						sCACertPath = sCACertPath.Left( sCACertPath.GetLength()-1 );

					int iRptGenRetVal = 0;
					if (iReportID >= 0)	// always true here
					{
				   //	CWaitCursor wait;
						CPersistentWaitCursor wait;

						//sResFN = sResFN.Left( sResFN.GetLength()-4 );
						//sProjPath.Replace( "\\", "/" );
						//sResFN.Replace( "\\", "/" );
						//sCACertPath.Replace( "\\", "/" );
						bool bVerbose = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);
		//				bool bSendRptSignature = (ReadProgInt( "options", "SendRptSignature", 1 /*default*/ ) > 0);		// SAC 9/12/13
					//	iRptGenRetVal = CMX_GenerateReport_CEC( iReportID, sProjPath, sResFN, "pdf", sCACertPath, bVerbose );
			//			iRptGenRetVal = CMX_GenerateReport_CEC( sResXMLFileName /*sProjPath, sResFN*/, sCACertPath, (iReportID==0 ? "CF1R_NCB_PRF" : "NRCC_PRF_01"), "CBECC", (iReportID==0 ? "Res" : "Com"),
			//														"none" /*Signature*/, "none" /*PublicKey*/, "true" /*sDebugRpt*/, bVerbose, false /*bSilent*/ );
			// SAC 9/4/13 - added proxy server settings
						CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
						if (ReadProgInt( "proxy", "UseProxyServerSettings", 1 /*default*/ ) > 0)		// SAC 8/12/14
						{	sProxyServerAddress		= ReadProgString( "proxy", "ProxyServerAddress"    , "", FALSE );
							//sProxyServerCredentials	= ReadProgString( "proxy", "ProxyServerCredentials", "", FALSE );
							GetEncodedSetting( "proxy", "ProxyServerCredentials", sProxyServerCredentials );
							sProxyServerType       	= ReadProgString( "proxy", "ProxyServerType"       , "", FALSE );
						}
						const char* pszProxyServerAddress     = (sProxyServerAddress.IsEmpty()     ? NULL : (const char*) sProxyServerAddress    );
						const char* pszProxyServerCredentials = (sProxyServerCredentials.IsEmpty() ? NULL : (const char*) sProxyServerCredentials);
						const char* pszProxyServerType        = (sProxyServerType.IsEmpty()        ? NULL : (const char*) sProxyServerType       );
						CString sNetComLibrary;
						sNetComLibrary = "";   // SAC 1/4/17 - no longer an option - ReadProgString( "proxy", "NetComLibrary", "", FALSE );
						const char* pszNetComLibrary = (sNetComLibrary.IsEmpty() ? NULL : (const char*) sNetComLibrary );

	//					CString sReportName = (iReportID==0 ? "CF1R_NCB_PRF" : "NRCC_PRF_01");
	//#ifdef UI_CARES
	//					long lProjRunScope = 1;		// 1 => "Newly Constructed" / 2 => "Addition and/or Alteration"		// SAC 12/3/13
	//					if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:RunScope" ), lProjRunScope ) && lProjRunScope == 2)
	//						sReportName = "CF1R_ALT_PRF";
	//#endif
	//					iRptGenRetVal = CMX_GenerateReport_Proxy_CEC( sResXMLFileName /*sProjPath, sResFN*/, sCACertPath, sReportName, "CBECC", (iReportID==0 ? "Res" : "Com"),
	//																"none" /*Signature*/, "none" /*PublicKey*/, pszProxyServerAddress, pszProxyServerCredentials, "true" /*sDebugRpt*/, bVerbose, false /*bSilent*/ );  //, bSendRptSignature );
	// SAC 6/10/14 - replaced above w/ the following that reference the latest report generator URL and ruleset-based report ID
						CString sRptGenUIApp, sRptGenUIVer, /*sRptGenCompReport,*/ sRptGenCompRptID, sRptGenServer, sRptGenApp, sRptGenService, sSecKeyRLName;
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenUIApp"      ), sRptGenUIApp      );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenUIVer"      ), sRptGenUIVer      );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenCompRptID"  ), sRptGenCompRptID  );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenServer"     ), sRptGenServer     );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenApp"        ), sRptGenApp        );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenService"    ), sRptGenService    );
	      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:SecKeyRLName"     ), sSecKeyRLName     );
						if (sRptGenCompReport.IsEmpty())
		      			BEMPX_SetDataString( BEMPX_GetDatabaseID( "Proj:RptGenCompReport" ), sRptGenCompReport );

						EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
						iRptGenRetVal = CMX_GenerateReport_Proxy_CEC( sResXMLFileName /*sProjPath, sResFN*/, sCACertPath, sRptGenCompReport, sRptGenUIApp, sRptGenUIVer,
																	"none" /*Signature*/, "none" /*PublicKey*/, pszProxyServerAddress, pszProxyServerCredentials, "true" /*sDebugRpt*/, bVerbose, false /*bSilent*/,
																	sRptGenCompRptID, sRptGenServer, sRptGenApp, sRptGenService, sSecKeyRLName, sOutRptFN, pszProxyServerType, pszNetComLibrary );		// SAC 8/7/14 - added final arguments to fix -Res rpt gen issue #355		// SAC 11/5/15
						EnableWindow( TRUE );
					}

					if (iRptGenRetVal != 0)
					{	if (iRptGenRetVal == 10)
							sErrMsg.Format( "An error occurred attempting to generate the %s report:\nUnable to establish a connection with the report generator website."
										 "\n\nIf your network provides web access via a proxy server, make sure the proxy address and credentials are correct.  You can find these settings in: "
										 "Tools > Proxy Server Settings.", sRptType );
						else
							sErrMsg.Format( "CMX_GenerateReport_CEC() returned error code %d", iRptGenRetVal );
	               MessageBox( sErrMsg );
					}
					else
					{	//sErrMsg.Format( "CMX_GenerateReport_CEC() SUCCEEDED - report file:  %s/%s-BEES.pdf", sProjPath, sResFN );
			//			CString sRptPathFile = sResXMLFileName;
			//			int iLastDot = sRptPathFile.ReverseFind('.');					ASSERT( iLastDot > 0 );
			//			if (iLastDot > 0)
			//			{	sRptPathFile  = sRptPathFile.Left( iLastDot );
			//				sRptPathFile += "-BEES.pdf";
							//sProjPath += '/';
							//sProjPath += sResFN;
							//sProjPath += "-BEES.pdf";
							//sProjPath.Replace( "/", "\\" );
							if (FileExists( sOutRptFN ))
							{
							// log messages identifying file generated and describing reason for report watermark
								sErrMsg.Format( "PDF %s report generated:  %s", sRptType, sOutRptFN );
								VERIFY( BEMPX_WriteLogFile( sErrMsg,	NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
								if (iReportID <= 1)
									VERIFY( BEMPX_WriteLogFile( "Compliance report marked as 'not usable for compliance' since valid reports cannot be generated outside the compliance analysis sequence.",
																					NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );

								if (MessageBox( "Report successfully generated.\n\nWould you like to view the report?", "Report Generated", MB_YESNO ) == IDYES)
								{	OpenFileViaShellExecute( sOutRptFN, sRptTypeLong /*FileDescrip*/ );
									//	int idx = sOutRptFN.ReverseFind('\\');   // sProjPath.ReverseFind('/');
									//	CString sPDFPath = (idx > 0 ? sOutRptFN.Left( idx ) : "");
									//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sOutRptFN, NULL, sPDFPath, SW_SHOWNORMAL );		hinstShellExec;
								}
							}
							else
							{  sErrMsg.Format( "CMX_GenerateReport_CEC() succeeded but report file not found:\n   %s", sOutRptFN );
		            	   MessageBox( sErrMsg );
							}
			//			}
					}
				}
			}
		}
	}
}


void CMainFrame::OnUpdateToolsCheckReportGenAccess(CCmdUI* pCmdUI)
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#elif UI_CANRES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsCheckReportGenAccess()
{
	CheckReportGenAccess( true );
}

bool CMainFrame::CheckReportGenAccess( bool bDisplayResult )
{
	CString sCACertPath = esProgramPath;
	if (sCACertPath[sCACertPath.GetLength()-1] == '\\')
		sCACertPath = sCACertPath.Left( sCACertPath.GetLength()-1 );

	CWaitCursor wait;
	bool bVerbose = (ReadProgInt( "options", "ReportGenVerbose", 0 /*default*/ ) > 0);		// SAC 11/30/15 - was: LogRuleEvaluation
	CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
	if (ReadProgInt( "proxy", "UseProxyServerSettings", 1 /*default*/ ) > 0)		// SAC 8/12/14
	{	sProxyServerAddress		= ReadProgString( "proxy", "ProxyServerAddress"    , "", FALSE );
		//sProxyServerCredentials	= ReadProgString( "proxy", "ProxyServerCredentials", "", FALSE );
		GetEncodedSetting( "proxy", "ProxyServerCredentials", sProxyServerCredentials );
		sProxyServerType       	= ReadProgString( "proxy", "ProxyServerType"       , "", FALSE );
	}
	const char* pszProxyServerAddress     = (sProxyServerAddress.IsEmpty()     ? NULL : (const char*) sProxyServerAddress    );
	const char* pszProxyServerCredentials = (sProxyServerCredentials.IsEmpty() ? NULL : (const char*) sProxyServerCredentials);
	const char* pszProxyServerType        = (sProxyServerType.IsEmpty()        ? NULL : (const char*) sProxyServerType       );

	CString sNetComLibrary;		// SAC 11/5/15
	sNetComLibrary = "";   // SAC 1/4/17 - no longer an option - ReadProgString( "proxy", "NetComLibrary", "", FALSE );
	const char* pszNetComLibrary = (sNetComLibrary.IsEmpty() ? NULL : (const char*) sNetComLibrary );

	char pszErrMsg[2056] = "\0";
	CString sSiteObjProp = "Proj:RptGenCheckURL";		// same for ALL existing programs

	int iRptGenRetVal = CMX_CheckSiteAccess( sSiteObjProp, sCACertPath, pszProxyServerAddress, pszProxyServerCredentials, pszErrMsg, 2056, bVerbose, pszProxyServerType, pszNetComLibrary );

	if (bDisplayResult)
	{	CString sResultMsg;		BOOL bIncludeProxyInfo = FALSE;
		if (iRptGenRetVal < 0)
		{			//		Return Values:	  -1 =>	SUCCESS  (using no proxy server settings)
					//							  -2 =>	SUCCESS  (using supplied proxy server settings)
					//							  -3 =>	SUCCESS  (using proxy server settings retrieved from operating system)
					//						 -11-13 =>	SUCCESS  (same codes as above (minus 10) but ALSO 'true' returned in file from server, indicating report gen site up and functioning)
			sResultMsg = "Site accecssed";
			if (iRptGenRetVal > -11)
				sResultMsg += ", but report generator is offline";
			else
				sResultMsg += " and report generator is available";
			if (iRptGenRetVal == -2 || iRptGenRetVal == -12)
				sResultMsg += " (via supplied proxy server credentials).";
			else if (iRptGenRetVal == -3 || iRptGenRetVal == -13)
				sResultMsg += " (via retrieved proxy server credentials).";
			else
				sResultMsg += ".";
		}
		else
		{	bIncludeProxyInfo = TRUE;
			sResultMsg = "Report generator website not accecssed.  ";			CString sTempMsg;
			switch (iRptGenRetVal)
			{	case   1 : sTempMsg.Format( "Error initializing %s on first attempt.", (sNetComLibrary.IsEmpty() ? "QT" : sNetComLibrary) );
																	sResultMsg += sTempMsg;		break;                                                          
				case   2 : sTempMsg.Format( "Error initializing %s on secondary attempt.", (sNetComLibrary.IsEmpty() ? "QT" : sNetComLibrary) );
																	sResultMsg += sTempMsg;		break;                                                       
				case   3 : sResultMsg += "No direct connection available and unable to retrieve proxy server settings.";		break;                         
				case   4 : sResultMsg += "Direct connection attempt failed.";		break;                                                                   
				case   5 : sResultMsg += "Connection attempt using supplied proxy server settings failed.";		break;                                     
				case   6 : sResultMsg += "Connection attempt using proxy server settings retrieved from the operating system failed.";		break;          
				case   7 : 	break;	// sResultMsg += "Unable to connect either directly or via proxy server settings retrieved from the operating system.";		break; 
				case   8 : sResultMsg += "Unable to connect via supplied proxy server settings.";		break;                                              
				case   9 : sResultMsg += "Error initializing temporary file path to copy site status to.";		bIncludeProxyInfo = FALSE;		break;                                     
				case  10 : sResultMsg += "Error initializing temporary file to copy site status to.";				bIncludeProxyInfo = FALSE;		break;                                           
				case  11 : sResultMsg += "Error opening temporary file to copy site status to.";						bIncludeProxyInfo = FALSE;		break;                                                 
				case  12 : sResultMsg += "CACertificate file not provided.";			bIncludeProxyInfo = FALSE;		break;                                                                   
				case  13 : sResultMsg += "Path to CACertificate file not found.";		bIncludeProxyInfo = FALSE;		break;                                                                
				case  14 : sResultMsg += "CACertificate file not found.";				bIncludeProxyInfo = FALSE;		break;
				default  :	sResultMsg.Format( "Report generator website not accecssed - CMX_CheckSiteAccess() error code %d.", iRptGenRetVal );		break;
		}	}
		if (strlen( pszErrMsg ) > 0)	// SAC 11/30/15
		{	sResultMsg += "\n\n";
			sResultMsg += pszErrMsg;
		}
		if (bIncludeProxyInfo)
			sResultMsg += "\n\nIf your network provides web access via a proxy server, make sure the proxy address and credentials are correct.  "
								"You can find these settings in:  Tools > Proxy Server Settings.";
  		AfxMessageBox( sResultMsg );
	}

	return (iRptGenRetVal < -10);
}


void CMainFrame::OnUpdateToolsReport_BuildingSummary(CCmdUI* pCmdUI)		// SAC 6/9/13
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
//#elif UI_CANRES
//   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnUpdateToolsReport_BuildingSummary_T24(CCmdUI* pCmdUI)		// SAC 6/19/13
{
#ifdef UI_CARES
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
//#elif UI_CANRES
//   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnToolsReport_BuildingSummary()		// SAC 6/9/13
{
	for (int i=0; i < (int) saReportRulelistNames.size(); i++)
	{	std::string strRL = saReportRulelistNames[i];
		size_t idxBldgSmry = strRL.find( "Building_Summary" );
		if (idxBldgSmry != std::string::npos)
		{
			CString sRptSel = saReportRulelistSelections[i].c_str();
			sRptSel.Replace( " ", NULL );
			int iParenIdx = sRptSel.ReverseFind('(');												ASSERT( iParenIdx > 0 );
			int iExtLen = sRptSel.ReverseFind(')') - iParenIdx - 1;							ASSERT( iExtLen > 0 );
			if (iParenIdx > 2 && iExtLen > 0)
			{	CString sRptFileName;
		   	CDocument* pDoc = GetActiveDocument();
		   	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
		   	{  CString sProjFileName = pDoc->GetPathName();
					if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
					{	sRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );


		bool bVerbose = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);
      char szGenRptPathFile[ _MAX_PATH ];
					EnableWindow( FALSE );		// SAC 11/12/15 - disable window/UI actions during processing
		int iGenRptRetVal = CMX_GenerateRulesetModelReport( sRptFileName, saReportRulelistSelections[i].c_str(), szGenRptPathFile, _MAX_PATH, bVerbose, false /*bSilent*/ );
					EnableWindow( TRUE );
		if (iGenRptRetVal == 0)
		{	sRptFileName = szGenRptPathFile;


//						sRptFileName += " - ";
//						sRptFileName += sRptSel.Left( iParenIdx );
//						sRptFileName += '.';
//						sRptFileName += sRptSel.Mid( iParenIdx+1, iExtLen );
//AfxMessageBox( sRptFileName );
//
//						CString sMsg;
//						sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
//						             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
//										 "(once the file is closed), or \n'Cancel' to abort the %s.", "output report", sRptFileName, "report generation" );
//						if (OKToWriteOrDeleteFile( sRptFileName, sMsg ))
//						{
//							bool bVerbose = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);
//							if (RuleProcWriteFileFromRulelist( sRptFileName, strRL.c_str(), bVerbose ))  // SAC 6/9/13
//							{


								if (MessageBox( "Building Summary successfully generated.\n\nWould you like to view the report?", "Building Summary Report", MB_YESNO ) == IDYES)
								{	OpenFileViaShellExecute( sRptFileName, "Building Summary Report" /*FileDescrip*/ );
									//	int idx = sRptFileName.ReverseFind('\\');
									//	CString sRptPath = (idx > 0 ? sRptFileName.Left( idx ) : "");
									//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sRptFileName, NULL, sRptPath, SW_SHOWNORMAL );		hinstShellExec;
								}


//							}
//						}


		}


					}
				}
			}


//				{	saReportRulelistNames.push_back(      ((const char*) sRulelistNames[i]) );
//					saReportRulelistSelections.push_back( ((const char*) sReportSelection)  );

//	ON_UPDATE_COMMAND_UI(IDM_RPT_BLDGSUMMARY, OnUpdateToolsReport_BuildingSummary)
//	ON_COMMAND(IDM_RPT_BLDGSUMMARY, OnToolsReport_BuildingSummary)

		}
	}
}

void CMainFrame::OnToolsReport_BuildingSummary_T24()		// SAC 6/19/13
{
	CString sAT;
	VERIFY( BEMPX_SetDataString( BEMPX_GetDatabaseID( "AnalysisType", BEMPX_GetDBComponentID( "Proj" ) ), sAT ) );
	BOOL bInclProp = (sAT.Find("Proposed") >= 0);
	BOOL bInclStd  = (sAT.Find("Standard") >= 0);

   m_bDoingSummaryReport = TRUE;		// causes simulations to be skipped during analysis
   LONG lPerfAnalRetVal = OnPerformAnalysis(0,0);
   m_bDoingSummaryReport = FALSE;

//CString sDbgMsg;
//sDbgMsg.Format( "lPerfAnalRetVal = %d / bInclProp = %s / bInclStd = %s", lPerfAnalRetVal, (bInclProp ? "T" : "F"), (bInclStd ? "T" : "F") );		MessageBox( sDbgMsg );
	if (lPerfAnalRetVal == 0 && (bInclProp || bInclStd))
	{	CDocument* pDoc = GetActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
		{  CString sProjFileName = pDoc->GetPathName();
			if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
			{	CString sPropRptFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
				CString  sStdRptFileName = sPropRptFileName;
				sPropRptFileName += " - Prop - BuildingSummary.csv";
				 sStdRptFileName +=  " - Std - BuildingSummary.csv";
				BOOL bHaveProp = (bInclProp && FileExists( sPropRptFileName ));
				BOOL bHaveStd  = (bInclStd  && FileExists(  sStdRptFileName ));
//sDbgMsg.Format( "sPropRptFileName %s exist:  %s\nsStdRptFileName %s exist:  %s", (bHaveProp ? "DOES" : "does NOT"), sPropRptFileName, (bHaveStd ? "DOES" : "does NOT"), sStdRptFileName );		MessageBox( sDbgMsg );
				if (!bHaveProp)
					sPropRptFileName.Empty();
				if (!bHaveStd)
					sStdRptFileName.Empty();

				if (bHaveProp && bHaveStd &&
							MessageBox( "Proposed & Standard Design Building Summaries successfully generated.\n\nWould you like to view the reports?", "Building Summary Report", MB_YESNO ) == IDNO)
				{	sPropRptFileName.Empty();
					sStdRptFileName.Empty();
				}
				else if (bHaveProp && !bHaveStd &&  
							MessageBox( "Proposed Design Building Summary successfully generated.\n\nWould you like to view the report?", "Building Summary Report", MB_YESNO ) == IDNO)
					sPropRptFileName.Empty();
				else if (!bHaveProp && bHaveStd &&
							MessageBox( "Standard Design Building Summary successfully generated.\n\nWould you like to view the report?", "Building Summary Report", MB_YESNO ) == IDNO)
					sStdRptFileName.Empty();

				if (!sPropRptFileName.IsEmpty())
					OpenFileViaShellExecute( sPropRptFileName, "Proposed Model Report" /*FileDescrip*/ );
				if (!sStdRptFileName.IsEmpty())
					OpenFileViaShellExecute( sStdRptFileName,  "Standard Model Report" /*FileDescrip*/ );
				//	if (!sPropRptFileName.IsEmpty())
				//	{	int idx = sPropRptFileName.ReverseFind('\\');
				//		CString sRptPath = (idx > 0 ? sPropRptFileName.Left( idx ) : "");
				//		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sPropRptFileName, NULL, sRptPath, SW_SHOWNORMAL );		hinstShellExec;
				//	}
				//	if (!sStdRptFileName.IsEmpty())
				//	{	int idx = sStdRptFileName.ReverseFind('\\');
				//		CString sRptPath = (idx > 0 ? sStdRptFileName.Left( idx ) : "");
				//		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sStdRptFileName, NULL, sRptPath, SW_SHOWNORMAL );		hinstShellExec;
				//	}
			}
		}
	}
}


LONG CMainFrame::OnCreateBldgComponent( UINT wParam, LONG )
{
   CreateComponentInfo* pCI = (CreateComponentInfo*) wParam;
   if (pCI && pCI->m_i1BEMClass > 0)
	{	int iError;
		int iAssignmentObjIdx = (pCI->m_lAssignmentDBID > 0 ? BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( pCI->m_lAssignmentDBID ), iError ) ) : -1);		ASSERT( iAssignmentObjIdx >= -1 );  // SAC 5/29/13
		CreateBuildingComponent( pCI->m_i1BEMClass, pCI->m_lAssignmentDBID, pCI->m_bEditNewComponent,
                               pCI->m_pParentWnd, pCI->m_lObjTypeDBID, pCI->m_lObjTypeValue, iAssignmentObjIdx );
	}
// struct CreateComponentInfo
// {
//    int   m_i1BDBClass;
//    long  m_lAssignmentDBID;
//    BOOL  m_bEditNewComponent;
//    CWnd* m_pParentWnd;
//    long  m_lObjTypeDBID;
//    long  m_lObjTypeValue;
// };
   return 1;
}


void CMainFrame::CreateBuildingComponent( int i1BDBClass, long lAssignmentDBID, BOOL bEditNewComponent,
                                          CWnd* pParentWnd, long lObjTypeDBID, long lObjTypeValue,
														int iAssignmentObjIdx /*=-1*/,   // SAC 5/29/13 - added new argument to ensure that assignment of new object occurs to correct assigning object (assigns new to self when assignee & assigner the same object type)
														BEMObject* pParentBEMObject /*=NULL*/ )	// SAC 5/29/14 - added to enable specification of parent for newly created object
{
   // First ensure that more of this type of component CAN be created
   BOOL bSuccess = FALSE;
   if (pParentWnd == NULL)
      pParentWnd = this;

   int iError;
   if (!BEMPX_CanCreateAnotherUserObject( i1BDBClass ))
   {
      CString sMsg = "No more ";
      BEMClass* pClass = BEMPX_GetClass( i1BDBClass, iError );
      if (pClass)
      {
         sMsg += pClass->getLongName().toLatin1().constData();
         sMsg += " components";
      }
      else
         sMsg += "components of this type";
      sMsg += " can be created.";
      AfxMessageBox( sMsg );
   }
   else
   {  // Present Create Component dialog box
      CDlgCreate cr8Dlg( i1BDBClass, lObjTypeDBID, lObjTypeValue, pParentWnd, Cr8DlgOpt_New, pParentBEMObject );	// SAC 5/29/14
      bSuccess = (cr8Dlg.DoModal() == IDOK);
   }

   if (bSuccess)
   {
      // Done creating component, now assign it to the desired DBID
      // Must do this BEFORE editing since user may change active object while in the edit dialog
      if (lAssignmentDBID > 0)
      {
         BEMObject* pNewObj = BEMPX_GetObjectByClass( i1BDBClass, iError );
         if (pNewObj && (BEMPX_SetBEMData( lAssignmentDBID, BEMP_Obj, (void*) pNewObj, BEMO_User, iAssignmentObjIdx ) >= 0) )
            SendMessage( WM_EVALPROPOSED );
      }

      // then go edit the new component
      if (bEditNewComponent)
      {
			int iTabCtrlWd, iTabCtrlHt;
			VERIFY( GetDialogTabDimensions( i1BDBClass, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
			CString sDialogCaption;
			GetDialogCaption( i1BDBClass, sDialogCaption );   // SAC 1/8/12
//         CBEMDialog td( i1BDBClass, pParentWnd );
         CSACBEMProcDialog td( i1BDBClass, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), pParentWnd,
// SAC 1/2/01 - added several arguments in order to pass in "OK" button label
                           0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, 99 /*iMaxTabs*/,
                           (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
									NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
									NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
									ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );   // SAC 1/19/12
         if (td.DoModal() == IDOK)
         {}
      }

      // First update mainview's tree
//      CView* pView = GetActiveView();
      CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
      if (pView != NULL)            // update main view's tree control(s)
         pView->SendMessage( WM_DISPLAYDATA, i1BDBClass );
   }
}

bool CMainFrame::ConvertBuildingComponent( int iFromBEMClass, int iFromObjIdx, int iToBEMClass )	// SAC 10/13/15
{			ASSERT( iFromBEMClass > 0 && iFromObjIdx >= 0 && iToBEMClass > 0 );
	CString sErrMsg, sNewNameAppend, sDlgCaption;
	CStringArray saFromProps, saToProps;
   int iError, iErr2, iDlgID=-1, iDlgWd, iDlgHt;
	long lNewObjAssignDBID, lNewConsAssmAssignDBID;
#ifdef UI_CANRES
   BEMObject* pPolyLpChildObj = NULL;
#endif
   BEMObject* pObj = BEMPX_GetObjectByClass( iFromBEMClass, iError, iFromObjIdx );
   BEMClass* pToBEMClass = BEMPX_GetClass( iToBEMClass, iErr2 );
	GetObjectConversionInfo( iFromBEMClass, iToBEMClass, iDlgID, iDlgWd, iDlgHt, sNewNameAppend, lNewObjAssignDBID, lNewConsAssmAssignDBID, sDlgCaption, saFromProps, saToProps );  // SAC 10/14/15
   if (iError < 0 || pObj == NULL)
   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to retrieve object pointer for class %d, object index %d", iFromBEMClass, iFromObjIdx );
   else if (pToBEMClass == NULL)
   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to retrieve class pointer for class %d", iToBEMClass );
   else if (iDlgID < 1)
   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to load object conversion info for conversion from %s to %s", pObj->getClass()->getLongName().toLatin1().constData(), pToBEMClass->getLongName().toLatin1().constData() );
   else
   {
 // first confirm conversion in case that might involve deletion of one or more children (otehr than the geometry (PolyLp))
 		//CArray<BEMObject*,BEMObject*> paDelObjs;
 		CArray<BEMObject*,BEMObject*> paReassignObjs;
 		CString sChildDelMsg, sChildReassignMsg, sTemp;
// 	  for (int i=0; i < pObj->m_children.GetCount(); i++)
// 	  {  POSITION pos = pObj->m_children.FindIndex( i );
// 	     BEMObject* pChildObj = (BEMObject*) pObj->m_children.GetAt( pos );
		int iNumChldrn = pObj->getChildCount();
		for (int i=0; i < iNumChldrn; i++)
		{	BEMObject* pChildObj = pObj->getChild(i);			ASSERT( pChildObj );
 	      if (pChildObj && pChildObj->getClass() )
 	      {
#ifdef UI_CANRES
				if (pChildObj->getClass()->get1BEMClassIdx() == eiBDBCID_PolyLp)	// add PolyLp to delete list w/out prompt to user
					pPolyLpChildObj = pChildObj;	// don't log child deletion - was:	paDelObjs.Add( pChildObj );
				else
				{
#endif
					sTemp.Format( "    %s '%s'", pChildObj->getClass()->getLongName().toLatin1().constData(), pChildObj->getName().toLatin1().constData() );
					if (pToBEMClass->GetChildClassID( pChildObj->getClass()->getShortName().toLatin1().constData() ) >= 0)
					{	paReassignObjs.Add( pChildObj );
						if (!sChildReassignMsg.IsEmpty())
							sChildReassignMsg += "\n";
						sChildReassignMsg += sTemp;
					}
					else
					{	//paDelObjs.Add( pChildObj );
						if (!sChildDelMsg.IsEmpty())
							sChildDelMsg += "\n";
						sChildDelMsg += sTemp;
					}
#ifdef UI_CANRES
				}
#endif
 	   }	}
	   if (sErrMsg.IsEmpty() && !sChildDelMsg.IsEmpty())
	   {	sChildDelMsg = "In the process of converting this object, the following chil object(s) will be deleted:\n" + sChildDelMsg;
	   	if (!sChildReassignMsg.IsEmpty())
	   	{	sTemp.Format( "\n\nAnd the following children will be re-assigned to the newly created %s:\n%s", pToBEMClass->getLongName().toLatin1().constData(), sChildReassignMsg );
	   		sChildDelMsg += sTemp;
	   	}
	   	sChildDelMsg += "\n\nPress 'OK' to continue the conversion, or 'Cancel' to abort it.";
			if (MessageBox( sChildDelMsg, NULL, MB_OKCANCEL ) != IDOK)
				sErrMsg.Format( "User aborted conversion of %s '%s' to %s.", pObj->getClass()->getLongName().toLatin1().constData(), pObj->getName().toLatin1().constData(), pToBEMClass->getLongName().toLatin1().constData() );
		}

	// create new object
		BEMObject* pNewObj = NULL;
		int iNewObjIdx = -1;
	   if (sErrMsg.IsEmpty())
	   {	CString sName = pObj->getName().toLatin1().constData();
	   	sName += sNewNameAppend;
			if (BEMPX_GetComponentByName( sName ) != NULL)
				sName.Empty();		// allow name to default if this default name is not unique

			pNewObj = BEMPX_CreateObject( iToBEMClass, sName, pObj->getParent(), BEMO_User, FALSE /*default parent*/ );
			if (pNewObj == NULL)
		   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to create new %s in converting from %s '%s'", pToBEMClass->getLongName().toLatin1().constData(), pObj->getClass()->getLongName().toLatin1().constData(), pObj->getName().toLatin1().constData() );
		   else
		   {	iNewObjIdx = BEMPX_GetObjectIndex( pNewObj->getClass(), pNewObj );
		   	if (lNewObjAssignDBID > 0)
					VERIFY( BEMPX_SetBEMData( lNewObjAssignDBID, BEMP_Obj, (void*) pNewObj, BEMO_User, iFromObjIdx ) >= 0 );
				SetDataModifiedFlag( TRUE );
			}
		}

#ifdef UI_CANRES
	// create PolyLp for new object
		if (sErrMsg.IsEmpty() && pNewObj && pPolyLpChildObj)
		{	//	iImportUniqueRuleLibObjOption => 0-ImportOnlyIfUnique / 1-ImportAlways / 2-EnsureLibraryName
			BEMObject* pNewPolyLp = BEMPX_CopyComponentWithAssignments( pPolyLpChildObj, pNewObj, FALSE /*bLibToUser*/, 
																							-1 /*iImportUniqueRuleLibObjOption*/, NULL /*pszImportRuleLibParentName*/ );
			if (pNewPolyLp == NULL)
		   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to create new PolyLp child of %s '%s'", pObj->getClass()->getLongName().toLatin1().constData(), pObj->getName().toLatin1().constData() );
		}
		BEMObject* pNewConsAssmObj = NULL;
		long lConsAssmRefDBID = -1;
#endif

	// copy original object data to new object
		if (sErrMsg.IsEmpty())
		{	long lFromDBID, lToDBID;		BEMProperty *pFromProp, *pToProp;
			for (int i=0; (i<saFromProps.GetSize() && sErrMsg.IsEmpty()); i++)
			{	lFromDBID = BEMPX_GetDatabaseID( saFromProps[i], iFromBEMClass );
				lToDBID   = BEMPX_GetDatabaseID( saToProps[i]  , iToBEMClass   );
				pFromProp = BEMPX_GetProperty( lFromDBID, iError, iFromObjIdx );			ASSERT( pFromProp );
				if (pFromProp && pFromProp->getDataStatus() >= BEMS_UserLibrary && pFromProp->getDataStatus() <= BEMS_UserDefined)
				{	// only copy property if it is user-defined
					pToProp = BEMPX_GetProperty( lToDBID, iError, iNewObjIdx );				ASSERT( pToProp );
					if (pToProp)
					{	// copy over contents of property - but NOT pointer to PropertyType
				      pToProp->setDataStatus(    pFromProp->getDataStatus()  );
				      pToProp->setSpecialValue(  pFromProp->getSpecialValue());
			//	      pToProp->m_iCritDefIdx   = pFromProp->m_iCritDefIdx  ;
				      pToProp->set1ArrayIdx(     pFromProp->get1ArrayIdx()   );
				      QString qsFromStr = pFromProp->getString();
				   	pToProp->setString(        qsFromStr      );
				      switch (pToProp->getType()->getPropType())
				      {  case BEMP_Int :   pToProp->setInt(    pFromProp->getInt()    );   break; 
				         case BEMP_Sym :   pToProp->setInt(    pFromProp->getInt()    );   break; 
				         case BEMP_Flt :   pToProp->setDouble( pFromProp->getDouble() );   break; 
				         case BEMP_Obj :   pToProp->setObj(    pFromProp->getObj()    );   break; 
				      }
					// switched this call to above in order to prevent copying of PorpertyType pointer:  pToProp->CopyProperty( pFromProp );
#ifdef UI_CANRES
						if (	pFromProp->getType() && pFromProp->getType()->getPropType() == BEMP_Obj && 
								pFromProp->getType()->getObj1ClassIdx(0) == eiBDBCID_ConsAssm &&
								pFromProp->getType()->getObj1ClassIdx(0) == pToProp->getType()->getObj1ClassIdx(0) && 
								pFromProp->getType()->getObjTypeValue(0) != pToProp->getType()->getObjTypeValue(0) )
						{	// COPY existing ConsAssm
							QString sName = pFromProp->getObj()->getName();
					   	sName += sNewNameAppend;
							if (BEMPX_GetComponentByName( sName.toLatin1().constData() ) != NULL)
								sName.clear();		// allow name to default if this default name is not unique

							pNewConsAssmObj = BEMPX_CreateObject( eiBDBCID_ConsAssm, sName.toLatin1().constData(), NULL, BEMO_User, FALSE /*default parent*/ );
							if (pNewConsAssmObj == NULL)
						   	sErrMsg.Format( "ConvertBuildingComponent() error: unable to create new %s in converting from %s '%s'", pToBEMClass->getLongName().toLatin1().constData(), pObj->getClass()->getLongName().toLatin1().constData(), pObj->getName().toLatin1().constData() );
						   else
						   {	// copy contents of 'From' surface ConsAssm to new ConsAssm
						   	VERIFY( pNewConsAssmObj->CopyObject( pFromProp->getObj() ) );

						   	int iNewConsAssmIdx = BEMPX_GetObjectIndex( pNewConsAssmObj->getClass(), pNewConsAssmObj );
						   	// change ConsAssm type
						   	long lObjTypeVal = pToProp->getType()->getObjTypeValue(0);
						   	VERIFY( BEMPX_SetBEMData( pToProp->getType()->getObjTypeDBID(0), BEMP_Int, (void*) &lObjTypeVal, BEMO_User, iNewConsAssmIdx ) >= 0 );
						   	// assign new ConsAssm to 'To' object
						   	lConsAssmRefDBID = lToDBID;
						   	VERIFY( BEMPX_SetBEMData( lToDBID, BEMP_Obj, (void*) pNewConsAssmObj, BEMO_User, iNewObjIdx ) >= 0 );
						   	VERIFY( BEMPX_SetBEMData( lNewConsAssmAssignDBID, BEMP_Obj, (void*) pNewConsAssmObj, BEMO_User, iFromObjIdx ) >= 0 );
		//		lNewConsAssmAssignDBID = BEMPX_GetDatabaseID( "ConvToIntWallConsRef", iBEMClassFrom );
							}
						}
#endif
			}	}	}
		}

	// reassign remaining children to the newly-created parent
		if (sErrMsg.IsEmpty() && paReassignObjs.GetSize() > 0)
		{
			for (int i=0; (i<paReassignObjs.GetSize() && sErrMsg.IsEmpty()); i++)
			{	BEMObject* pChildObj = paReassignObjs[i];
				if (pChildObj && pChildObj->getClass() && pChildObj->getClass()->get1BEMClassIdx() > 0)
					BEMPX_SetBEMData( BEMPX_GetDBID( pChildObj->getClass()->get1BEMClassIdx(), 0, BEM_PARAM0_PARENT ), BEMP_Obj, (void*) pNewObj );
			}
		}

	// default building model & display dialog allowing view/edit of conversion
		if (sErrMsg.IsEmpty())
		{	SendMessage( WM_EVALPROPOSED );

         CSACDlg dlgNewObj( this, iFromBEMClass, 0 /* lDBID_ScreenIdx */, iDlgID, 0, 0, 0,
                           esDataModRulelist /*pszMidProcRulelist*/, "" /*pszPostProcRulelist*/, sDlgCaption,
									iDlgHt, iDlgWd, 10 /*iBaseMarg*/, 0 /*uiIconResourceID*/, TRUE /*bEnableToolTips*/, FALSE /*bShowPrevNextButtons*/, 0 /*iSACWizDlgMode*/,
									0 /*lDBID_CtrlDBIDOffset*/, "&Done" /*pszFinishButtonText*/, NULL /*plCheckCharDBIDs*/, 0 /*iNumCheckCharDBIDs*/,
									0 /*lDBID_ScreenIDArray*/, TRUE /*bPostHelpMessageToParent*/, ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip,
                           FALSE /*bUsePageIDForCtrlTopicHelp*/, 100000 /*iHelpIDOffset*/, 0 /*lDBID_DialogHeight*/, FALSE /*bBypassChecksOnCancel*/,
                           FALSE /*bEnableCancelBtn*/, TRUE /*bGraphicalButtons*/, 90 /*iFinishBtnWd*/, ebIncludeLongCompParamStrInToolTip );
         dlgNewObj.DoModal();
		}

#ifdef UI_CANRES
	// if user assigned a ConsAssm to the new surface OTHER THAN the one created from the original surface, then DELETE the newly created (and now unassigned) ConsAssm
		if (sErrMsg.IsEmpty() && pNewObj && pNewConsAssmObj && lConsAssmRefDBID > 0)
		{	BEMObject* pCurConsAssmObj = NULL;
			if (BEMPX_SetDataObject( lConsAssmRefDBID, pCurConsAssmObj, -1, iNewObjIdx ) && pCurConsAssmObj && pCurConsAssmObj != pNewConsAssmObj )
				BEMPX_DeleteObject( pNewConsAssmObj );
		}
#endif

	// delete original object
		if (sErrMsg.IsEmpty())
			BEMPX_DeleteObject( pObj );

		//paDelObjs.RemoveAll();
		paReassignObjs.RemoveAll();
	}

	if (!sErrMsg.IsEmpty())
   	AfxMessageBox( sErrMsg );
   return (sErrMsg.IsEmpty());
}

// SAC 2/28/14 - added to handle setup of new simplified geometry project in 
void CMainFrame::SetupNewProject()
{
	// SAC 6/18/14 - added RE-load of BEM CIDs & DBIDs to account for special conditions, such as UI_CANRES 2D/simplified geometry
	InitBEMDBIDs();

	// ruleset should be newly re-loaded (via CComplianceUIDoc::OnNewDocument())
#ifdef UI_CANRES
	CreateBuildingComponent( eiBDBCID_Proj );
	if (BEMPX_GetNumObjects( eiBDBCID_Proj ) > 0)
	{	CreateBuildingComponent( eiBDBCID_Building );
		if (BEMPX_GetNumObjects( eiBDBCID_Building ) > 0)
		{	CreateBuildingComponent( eiBDBCID_Story );
			if (BEMPX_GetNumObjects( eiBDBCID_Story ) > 0)
				CreateBuildingComponent( eiBDBCID_Space );
	}	}
#endif

	SetStatusBarStrings( "", 2 );		// SAC 10/29/15 - display ruleset ID in third status bar pane

	return;
}


static char BASED_CODE szDelStd1[] = "The building component being deleted ";
static char BASED_CODE szDelRef1[] = "is referenced ";
static char BASED_CODE szDelRef2[] = " times by other";
static char BASED_CODE szDelChl1[] = "has ";
static char BASED_CODE szDelChl2[] = " child";
static char BASED_CODE szDelChl3[] = " component(s) and has ";
static char BASED_CODE szDelStd2[] = " component(s).  If this component is deleted, then all ";
static char BASED_CODE szDelChl4[] = "its children will also be deleted and all references to the ";
static char BASED_CODE szDelChl5[] = "component being deleted or any of its children";
static char BASED_CODE szDelRef3[] = " references to it";
static char BASED_CODE szDelStd3[] = " will be reinitialized.  ";
static char BASED_CODE szDelStd4[] = "Are you sure you want to delete the ";

BOOL CMainFrame::DeleteBuildingComponent( BEMObject* pObj, CWnd* pParentWnd )
{
   BOOL bRetVal = FALSE;

   if (pParentWnd == NULL)
      pParentWnd = this;

   if (pObj)
   {
       int iNumObjRefs  = BEMPX_CountOrResetObjectRefs( pObj, TRUE );
       int iNumChildren = pObj->getChildCount();
 
       // Assemble component deletion confirmation message
       CString sMsg;
       if ( (iNumObjRefs > 0) || (iNumChildren > 0) )
       {
          CString sTemp;
          sMsg = szDelStd1;
          if (iNumObjRefs > 0)
          {
             sMsg += szDelRef1;
             sTemp.Format( "%d", iNumObjRefs );
             sMsg += sTemp;
             sMsg += szDelRef2;
          }
 
          if (iNumChildren > 0)
          {
             if (iNumObjRefs > 0)
                sMsg += szDelChl3;
             else
                sMsg += szDelChl1;
             sTemp.Format( "%d", iNumChildren );
             sMsg += sTemp;
             sMsg += szDelChl2;
          }
 
          sMsg += szDelStd2;
 
          if (iNumChildren > 0)
          {
             sMsg += szDelChl4;
             sMsg += szDelChl5;
          }
          else  // refs only
             sMsg += szDelRef3;
 
          sMsg += szDelStd3;
       }
 
       sMsg += szDelStd4;
       int iClass = 0;
       if (pObj->getClass() != NULL)
       {
          sMsg += pObj->getClass()->getLongName().toLatin1().constData();
          iClass = pObj->getClass()->get1BEMClassIdx();
       }
       else
          sMsg += "building component";
 
       if (pObj->getName().length() > 0)
       {
          sMsg += " '";
          sMsg += pObj->getName().toLatin1().constData();
          sMsg += "'";
       }
       sMsg += "?";
 
       if (pParentWnd->MessageBox( sMsg, "Delete Building Component",
                                   MB_ICONSTOP | MB_YESNO | MB_DEFBUTTON2 ) == IDYES)
       {
          BEMPX_DeleteObject( pObj );
          SetDataModifiedFlag( TRUE );
          bRetVal = TRUE;
 
          // SAC 8/7/00 - Added call to re-evaluate ruleset
          SendMessage( WM_EVALPROPOSED );
 
          CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
          if (pView != NULL)            // update main view's tree control(s)
             pView->SendMessage( WM_DISPLAYDATA, iClass );
       }
   }

   return bRetVal;
}


void CMainFrame::OnEditComponent()
{
   CDlgCompType ct( CTDM_Edit, this );
   if (ct.DoModal() == IDOK)
   {
      int i1SelClassIdx = BEMPX_GetClassIndexByLongName( ct.m_sSelectedCompType );
      if (i1SelClassIdx > 0)
      {
			int iTabCtrlWd, iTabCtrlHt;
			VERIFY( GetDialogTabDimensions( i1SelClassIdx, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
			CString sDialogCaption;
			GetDialogCaption( i1SelClassIdx, sDialogCaption );   // SAC 1/8/12
//         CBEMDialog td( i1SelClassIdx, this );
         CSACBEMProcDialog td( i1SelClassIdx, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), this,
// SAC 1/2/01 - added several arguments in order to pass in "OK" button label
                           0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, 99 /*iMaxTabs*/,
                           (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
									NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
									NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
									ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip );   // SAC 1/19/12
         if (td.DoModal() == IDOK)
         {}

         // Update the mainview's tree only if required
         CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
         if (pView != NULL)            // update main view's tree control(s)
            pView->SendMessage( WM_DISPLAYDATA, i1SelClassIdx, 1 );
      }
   }
}

void CMainFrame::OnUpdateEditComponent(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eiDeveloperMenu != 0) );
}


void CMainFrame::OnCreateComponent() 
{
   CDlgCompType ct( CTDM_Create, this );
   if (ct.DoModal() == IDOK)
   {
      int i1SelClassIdx = BEMPX_GetClassIndexByLongName( ct.m_sSelectedCompType );
      if (i1SelClassIdx > 0)
         CreateBuildingComponent( i1SelClassIdx );
   }
}

void CMainFrame::OnUpdateCreateComponent(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eiDeveloperMenu != 0 && eInterfaceMode == IM_INPUT) );
}


void CMainFrame::OnDeleteComponent() 
{
   CDlgCompType ct( CTDM_Delete, this );
   if (ct.DoModal() == IDOK)
   {
      if (ct.m_iClass < 1)
         // Report Error
         MessageBox( "CMainFrame::OnDeleteComponent() Error: Class not found." );
      else
      {
         int iError;
         BEMObject* pObj = BEMPX_GetObjectByName( ct.m_iClass, iError, ct.m_sSelectedComponent );
         if (iError < 0 || pObj == NULL)
            // Report Error
            MessageBox( "CMainFrame::OnDeleteComponent() Error: Object not found." );
         else
            DeleteBuildingComponent( pObj );
      }
   }
}

void CMainFrame::OnUpdateDeleteComponent(CCmdUI* pCmdUI) 
{
   int iTotNumObjects = 0;
   int iNumClasses = BEMPX_GetNumClasses();
   for (int iCls=1; (iTotNumObjects == 0 && iCls <= iNumClasses); iCls++)
      iTotNumObjects += BEMPX_GetNumObjects( iCls );
   // Enable "Delete..." only if one or more user-defined components exist
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && iTotNumObjects > 0) );
}


static BOOL sbFirstScreenDataLoad = TRUE;

LRESULT CMainFrame::OnLoadScreenData( WPARAM, LPARAM )
{
   BOOL bBDBScrnsOK = FALSE;

   // Initialize tabbed dialog page data
	CWaitCursor wait;

   // reset BEMProcUI Screen Data
   CString sRulePN = ReadProgString( "paths", "RulesetPath", "", TRUE );
   QString sScrnFN, sTTipFN;
   if (!CMX_GetRulesetScreenFiles( sScrnFN, sTTipFN ))
      MessageBox( "Error retrieving screen and tooltip filenames from ruleset.", "CMainFrame::OnLoadScreenData()" );
   else
   {
      sScrnFN = sRulePN + sScrnFN;
      sTTipFN = sRulePN + sTTipFN;
      if (!FileExists( sScrnFN ))
         MessageBox( "Screens file not found.", "CMainFrame::OnLoadScreenData()" );
      else if (!FileExists( sTTipFN ))
         MessageBox( "ToolTips file not found.", "CMainFrame::OnLoadScreenData()" );
      else
      {
         if (sbFirstScreenDataLoad)
         {
            sbFirstScreenDataLoad = FALSE;
            CString sScrnPN = sScrnFN.left( sScrnFN.lastIndexOf('\\')+1 ).toLatin1().constData();   // ReadProgString( "paths", "MetafilePath", "", TRUE );
            bBDBScrnsOK = BEMPUIX_ScreenData( this, sScrnFN.toLatin1().constData(), sTTipFN.toLatin1().constData(), sScrnPN, sScrnPN, sScrnPN );
            SetBDBWTextColors();
				VERIFY( SetCharsNotAllowedInObjNamesToBEMProcUI() );	// SAC 8/20/14 - enable product-specific illegal object name characters
         }
         else
            bBDBScrnsOK = BEMPUIX_ResetScreenData( sScrnFN.toLatin1().constData(), sTTipFN.toLatin1().constData() );

         // Update the mainview's tabs
         CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
         if (pView)
            pView->SendMessage( WM_UPDATETABS );
      }
   }

   return (bBDBScrnsOK ? 1 : 0);
}

void CMainFrame::OnReloadScreens() 
{
   OnLoadScreenData(0,0);
}


BOOL CMainFrame::UpdateSoftwareVersionString()		// SAC 9/17/12
{	BOOL bRetVal = FALSE;
	CString sSoftwareVer;
	if (GetProgramVersion( sSoftwareVer ) && !sSoftwareVer.IsEmpty())
	{	long lDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "SoftwareVersion", eiBDBCID_Proj );
		CString sProjSoftwareVer;
		if (lDBID_Proj_SoftwareVersion > 0 &&
				(!BEMPX_SetDataString( lDBID_Proj_SoftwareVersion, sProjSoftwareVer ) || sProjSoftwareVer.IsEmpty() || sSoftwareVer.Compare( sProjSoftwareVer ) != 0) )
		{  BEMPX_SetBEMData( lDBID_Proj_SoftwareVersion, BEMP_Str, (void*) ((const char*) sSoftwareVer) );
			// set flag indicating project has been modified
			SetDataModifiedFlag( TRUE );
			bRetVal = TRUE;
		}
	}
	return bRetVal;
}

BOOL CMainFrame::SetBEMVersionID()		// SAC 9/17/12
{	BOOL bRetVal = FALSE;
	long lBEMVerID = (eiBDBCID_BEMVersion > 0 ? BEMPX_GetNumPropertyTypes( (int) eiBDBCID_BEMVersion ) : 0);
	if (lBEMVerID > 0)
	{	long lCurBEMVer = 0;
		if (elDBID_Proj_BEMVersion > 0 && 
				(!BEMPX_SetDataInteger( elDBID_Proj_BEMVersion, lCurBEMVer ) || lCurBEMVer != lBEMVerID) )
		{  BEMPX_SetBEMData( elDBID_Proj_BEMVersion, BEMP_Int, (void*) &lBEMVerID );
			// set flag indicating project has been modified
			SetDataModifiedFlag( TRUE );
			bRetVal = TRUE;
		}
	}
	return bRetVal;
}


static char BASED_CODE szWSIOK[]  = "Simulation input file written to 'SIMULATE.INP' in the CBECC program directory.";
static char BASED_CODE szWSIErr[] = "Error writing simulation input file.";

void CMainFrame::WriteSimulationInput( SimulationType /*eSimType*/ ) 
{
//   CString sProgDir = esProjectsPath;  //ReadProgString( szPaths, szProgPath, "" );
//   sProgDir += "SIMULATE.INP";
//   CString sRateDir = ReadProgString( szPaths, "RatesPath", "", TRUE );
//
//   // 0 for DOE-2.1E, 1 for DOE-2.2 (Geometry Only)
//   int iSimVer = ReadProgInt( "options", "SimulationVersion", 0 );
//
//   BeginWaitCursor();
//
//   BOOL bInpOK = CMX_WriteSimulationInput( eSimType, (const char*) sProgDir, (const char*) sRateDir, iSimVer );
//
//   EndWaitCursor();
//
//   AfxMessageBox( (bInpOK ? szWSIOK : szWSIErr) );

#ifdef UI_CANRES

	CString sSimFileName;
   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {  CString sProjFileName = pDoc->GetPathName();
		if (!sProjFileName.IsEmpty() && sProjFileName.ReverseFind('.') > 0)
		{	sSimFileName = sProjFileName.Left( sProjFileName.ReverseFind('.') );
			sSimFileName += " - AnnualSim.xml";
		}
	}
   if (sSimFileName.IsEmpty())
		AfxMessageBox( "Must have valid, saved project file to write a simulation (SDDXML) input file." );
	else
	{	// proxy server INI options (spanning both -Res & -Com versions
		CString sProxyServerAddress, sProxyServerCredentials, sProxyServerType;
		if (ReadProgInt( "proxy", "UseProxyServerSettings", 1 /*default*/ ) > 0)		// SAC 11/3/15
		{	sProxyServerAddress		= ReadProgString( "proxy", "ProxyServerAddress"    , "", FALSE );
			//sProxyServerCredentials	= ReadProgString( "proxy", "ProxyServerCredentials", "", FALSE );
			GetEncodedSetting( "proxy", "ProxyServerCredentials", sProxyServerCredentials );
			sProxyServerType      	= ReadProgString( "proxy", "ProxyServerType"       , "", FALSE );
		}
		const char* pszProxyServerAddress     = (sProxyServerAddress.IsEmpty()     ? NULL : (const char*) sProxyServerAddress    );
		const char* pszProxyServerCredentials = (sProxyServerCredentials.IsEmpty() ? NULL : (const char*) sProxyServerCredentials);
		const char* pszProxyServerType        = (sProxyServerType.IsEmpty()        ? NULL : (const char*) sProxyServerType       );

		QString sWthrFileErrMsg;   // SAC 3/8/13 - added weather file prep routine
	   CString sWthrPath = ReadProgString( "paths", "WeatherPath", "EPW\\", TRUE );
		if (CMX_SetupAnalysisWeatherPaths( sWthrPath, true /*bAnnual*/, true /*bDDY*/, sWthrFileErrMsg, true /*bAllowWthrDownload*/,
														pszProxyServerAddress, pszProxyServerCredentials, pszProxyServerType ) != 0)
		{	if (sWthrFileErrMsg.isEmpty())
				sWthrFileErrMsg = "Error encountered initializing weather file locations & names.";
			sWthrFileErrMsg += "\n\nContinuing to write simulation input.";
			AfxMessageBox( sWthrFileErrMsg.toLatin1().constData() );
		}

		CString sMsg;
		sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
		             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
						 "(once the file is closed), or \n'Cancel' to abort the %s.", "SDD XML", sSimFileName, "analysis" );
		if (OKToWriteOrDeleteFile( sSimFileName, sMsg ))
		{  // SAC 6/26/13 - added code to PREVENT ModDate from getting incremented each time project file is written in non-input mode
			long lModDate;
			if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
				lModDate = -1;

			VERIFY( BEMPX_WriteProjectFile( sSimFileName, BEMFM_SIM, FALSE, FALSE, FALSE, BEMFT_XML /*iFileType*/, false /*bAppend*/,
															NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lModDate ) );
		}
	}

#else

	AfxMessageBox( "CMainFrame::WriteSimulationInput()" );

#endif
}


void CMainFrame::OnWriteAnnualSimulationInput() 
{
   WriteSimulationInput( ST_ProposedFinal );
}

void CMainFrame::OnWriteDesignDaySimulationInput() 
{
   WriteSimulationInput( ST_ProposedDesign );
}


// SAC 8/22/11 - remove access to Tools - Bldg Wizard menu option
//void CMainFrame::OnUpdateBldgWizard(CCmdUI* pCmdUI) 
//{
//   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
//}
//
//static char BASED_CODE szBWCap1[] = "Wizard Warning";
//static char BASED_CODE szBWMsg1[] = "Using the Building Creation Wizard will overwrite changes made using the main program"
//                                    " interface.\nPress 'OK' to use the Wizard, or 'Cancel' to return to the main program"
//                                    " interface.\n(See 'Wizard Caution' in Help.)";
//// SAC 4/27/00 - replaced w/ above message per RSB's request
////static char BASED_CODE szBWMsg1[] = "Using the Building Wizard will overwrite any changes you have made to the project"
////                                    " description outside of the wizard.\nPress 'OK' to initiate the Building Wizard, or"
////                                    " 'Cancel' to return to the existing project description.";
//// SAC 9/2/99 - replaced w/ above message per RSB's request
////static char BASED_CODE szBWMsg1[] = "One or more components already exist for this project.  If you run the Building Wizard"
////                                    " then all existing project information will be lost and the wizard will create a new"
////                                    " building description in its place.\nPress 'OK' to initiate the Building Wizard, or"
////                                    " 'Cancel' to return to the existing project description.";
//
//void CMainFrame::OnBldgWizard() 
//{
//   BOOL bOK = TRUE;
//
//   // if a project component exists, then confirm the user wishes to continue before initiating the wizard
//   if (BEMPX_GetNumObjects( eiBDBCID_Proj ) > 0)
//      bOK = (MessageBox( szBWMsg1, szBWCap1, MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2 ) == IDOK);
//// SAC 4/27/00 - switched from MB_ICONSTOP to MB_ICONWARNING per RSB's request
////      bOK = (MessageBox( szBWMsg1, szBWCap1, MB_OKCANCEL | MB_ICONSTOP | MB_DEFBUTTON2 ) == IDOK);
//
//   if (bOK)
//   {
//      m_bDoingWizard = TRUE;
//      BOOL bWizCompsCr8ed = (BEMPX_GetNumObjects( eiBDBCID_Wizard ) < 1 || BEMPX_GetNumObjects( eiBDBCID_HVACWiz ) < 1);
//      if (BEMPX_GetNumObjects( eiBDBCID_Wizard ) < 1)
//      {
//         CString sDefName;
//         DefaultProjectName( sDefName );
//         bOK = (BEMPX_CreateObject( eiBDBCID_Wizard, sDefName ) != NULL);
//         if (!bOK)
//            MessageBox( "Error creating wizard component." );
//      }
//      else
//      {
//// What if the current project ruleset is different than the
//// ruleset defined for in the wizard component ???
//      }
//
//      if (BEMPX_GetNumObjects( eiBDBCID_AreaWiz ) < 1)
//      {
//         bOK = (BEMPX_CreateObject( eiBDBCID_AreaWiz ) != NULL);
//         if (!bOK)
//            MessageBox( "Error creating activity area wizard component." );
//      }
//      else
//      {
//// What if the current project ruleset is different than the
//// ruleset defined for in the wizard component ???
//      }
//
//      if (BEMPX_GetNumObjects( eiBDBCID_HVACWiz ) < 1)
//      {
//         bOK = (BEMPX_CreateObject( eiBDBCID_HVACWiz ) != NULL);
//         if (!bOK)
//            MessageBox( "Error creating HVAC wizard component." );
//      }
//      else
//      {
//// What if the current project ruleset is different than the
//// ruleset defined for in the wizard component ???
//      }
//
//// SAC 5/26/00 - added
//      if (BEMPX_GetNumObjects( eiBDBCID_PlantWiz ) < 1)
//      {
//         bOK = (BEMPX_CreateObject( eiBDBCID_PlantWiz ) != NULL);
//         if (!bOK)
//            MessageBox( "Error creating Plant wizard component." );
//      }
//      else
//      {
//// What if the current project ruleset is different than the
//// ruleset defined for in the wizard component ???
//      }
//
//      // SAC 7/7/99 - moved this out of if statement below so that it gets executed even when no wizard components are created above
//      if (bOK)
//         SendMessage( WM_EVALPROPOSED );
//
//      if (bWizCompsCr8ed && bOK)
//         SetDataModifiedFlag( TRUE );
//
//      if (bOK)
//      {
////#ifdef _DEBUG
////         // Declare the variables needed for memory leak detection
////         CMemoryState oldMemState, newMemState, diffMemState;
////         oldMemState.Checkpoint();
////#endif
////         if (MessageBox( "Yes => New Wizard\nNo  => Old Wizard", "OnBldgWizard()", MB_ICONSTOP | MB_YESNO ) == IDYES)
////         {
//            BEMPUIX_SetWMFDatabaseIDs( elDBID_Wiz_FootprintWMF, elDBID_Wiz_FPOrientXFrac,
//                                    elDBID_Wiz_FPOrientYFrac, elDBID_Wiz_Orientation );
////            SetBDBWTextColors();
//
//      	   CSACWizardDlg dlgWiz( this, eiBDBCID_Wizard, elDBID_Wiz_ScreenIdx, elDBID_Wiz_ScreenID,
//                                  elDBID_Wiz_PrevScreenID, elDBID_Wiz_NextScreenID, elDBID_Wiz_EnableFinishBtn, "WizardInput",
//                                  NULL, "Building Creation Wizard", 400 /*dlg ht*/, 620 /*dlg wd*/,
////                                  "PostWizardInput", "Building Creation Wizard", 400 /*dlg ht*/, 620 /*dlg wd*/ );
//                                  10, IDI_WIZARD );
//            // SAC 4/27/00 - Created wizard icon resource and added to CSACWizardDlg constructor arguments for display in wizard dialog caption bar
//            bOK = (dlgWiz.DoModal() == IDOK);
////         }
////         else
////         {
////            CDlgWizard wizDlg( this );
////            bOK = (wizDlg.DoModal() == IDOK);
////         }
////#ifdef _DEBUG
////         newMemState.Checkpoint();
////         if( diffMemState.Difference( oldMemState, newMemState ) )
////         {
////            TRACE( "Memory leaked from CBECC's CMainFrame::OnBldgWizard()!\n" );
////            diffMemState.DumpStatistics();
////         }
////#endif
//      }
//      m_bDoingWizard = FALSE;
//
//      if (bOK)
//      {
//         // grab DOE-2.2 polygon output file name from .INI file (if it exists)
////         CString sD22PolyFileName = ReadProgString( "files", "D22Poly", "", TRUE );
////         const char* pszD22PFN = (sD22PolyFileName.GetLength() > 0) ? (const char*) sD22PolyFileName : NULL;
//
//      	CWaitCursor wait;
////         MessageBox( "Create Building From Wizard" );
//			ASSERT( FALSE );
////         if (!BEMPX_PopulateProjectFromWizard( pszD22PFN ))
////            MessageBox( "Population of building description from wizard data FAILED." );
//
//         // evaluate PostWizardInput rulelist
//         CMX_EvaluateRuleset( epszWRLs[1], FALSE, TRUE );
//
//         if (!BEMPX_SetAllOrientations())
//            MessageBox( "Error setting building orientation values following project population." );
//
//         // set flag indicating project has been modified
//         SetDataModifiedFlag( TRUE );
//         // execute compliance rulelist #1
//         SendMessage( WM_EVALPROPOSED );
//
//         // update mainview's tree
//         CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
//         if (pView != NULL)            // update main view's tree control(s)
//            pView->SendMessage( WM_DISPLAYDATA );
//
//         // SAC 6/29/00 - added code to display RTF-based help following wizard
//         if (ebShowHelpFollowingWizard)  // SAC 2/14/01 - was:  if (ReadProgInt( "options", "ShowHelpFollowingWizard", 1 ) > 0)
//         {
////            CString sWizardHelpFile = ReadProgString( "files", "WizardHelpRTF", "Screens\\WizHelp.rtf", TRUE );
////            if (!FileExists( sWizardHelpFile ))
////            {
////               sWizardHelpFile = "Wizard Help File '" + sWizardHelpFile;
////               sWizardHelpFile += "' Not Found.";
////               MessageBox( sWizardHelpFile );
////            }
////            else
////            {
////               CDlgRTFDisplay dlgHelp( this, sWizardHelpFile );
////               dlgHelp.DoModal();
////            }
//            // SAC 1/1/00 - Swapped out RTF file display w/ automatic presentation of help file
////            AfxGetApp()->WinHelp( (DWORD) ReadProgInt( "options", "PostWizardHelpID", 123320 ), HELP_CONTEXT );
//            WinHelp( (DWORD) ReadProgInt( "options", "PostWizardHelpID", 123320 ) );
//         }
//      }
//   }
//}

BOOL CMainFrame::OnEditSwitchRuleset(UINT nID)
{
	ASSERT_VALID(this);

	ASSERT(nID >= ID_EDIT_SWITCHRULESET_1);		nID;
	ASSERT(nID < ID_EDIT_SWITCHRULESET_1 + (UINT)eiNumRulesetsAvailable);

//   MessageBox( "Dynamic ruleset switching not currently enabled.", "Switch Ruleset" );
   int nIndex = nID - ID_EDIT_SWITCHRULESET_1;
	CString sRuleSwitchDisallowedMsg, sRulesetFileString;
	if (!MenuRulesetSelectionAllowed( nIndex, sRuleSwitchDisallowedMsg ))
	{	if (!sRuleSwitchDisallowedMsg.IsEmpty())
			MessageBox( sRuleSwitchDisallowedMsg, "Ruleset Switch" );
	}
   else if (MenuRulesetSelection( this, nIndex, sRulesetFileString ))
   {
		CDocument* pDoc = GetActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) &&
			  (((CComplianceUIDoc*)pDoc)->CUISaveModified( "ruleset switch" )) )
		{
			CString sCurrentFileName = pDoc->GetPathName();

			// Call OpenTheFile() to BOTH load the new ruleset AND restore original project file, since ruleset refresh will clear out the database
			((CComplianceUIDoc*)pDoc)->OpenTheFile( sCurrentFileName, TRUE /*bWriteToLog*/, FALSE /*bRestore*/, sRulesetFileString, nIndex, FALSE /*bNormalRulesetUpdates*/ );	// SAC 11/17/15

//			// send a message to the main view's tree control via CMainFrame in case the tree requires updating
//			pWnd->SendMessage( WM_UPDATETREE, 0, elDBID_Proj_Ruleset );

			// Ruleset modified, so update the mainview's tree
			CView* pView = (CView*) m_wndSplitter.GetPane(0,0);
			if (pView != NULL)				// update main view's tree control(s)
				pView->SendMessage( WM_DISPLAYDATA );

			MessageBox( eszPostRulesetSwitch, "Ruleset Switch Completed" );
	}	}

	return TRUE;
}

void CMainFrame::OnUpdateEditSwitchRuleset1(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(this);
	if (eiNumRulesetsAvailable <= 0) // no Rulesets
		pCmdUI->Enable(FALSE);
	else
      UpdateRulesetMenu( pCmdUI );
}



void CMainFrame::OnUpdateToolWizard(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( FALSE );
//   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );     -- SAC 8/17/11 - removed access to bldg wizard
}
void CMainFrame::OnToolWizard() 
{
	ASSERT( FALSE );
//   OnBldgWizard();
}


void CMainFrame::OnUpdateToolAnalysis(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT) );
}
void CMainFrame::OnToolAnalysis() 
{
   OnPerformAnalysis(0,0);
}


void CMainFrame::OnUpdateToolReports(CCmdUI* pCmdUI) 
{
// SAC 1/14/03 - Modified to enable Report button only when document is unchanged and results file exists
   BOOL bEnableReportButton = FALSE;
//   BOOL bEnableReportButton = (eInterfaceMode == IM_INPUT);     -- SAC 8/17/11 - removed access to compliance reporting application (for the time being)
   if (bEnableReportButton)
   {
      bEnableReportButton = FALSE;
      CDocument* pDoc = GetActiveDocument();
      if (pDoc && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) && !pDoc->IsModified())
      {
         CString sBBDFileName = pDoc->GetPathName();
         if (sBBDFileName.GetLength() > 3)
         {
            sBBDFileName = sBBDFileName.Left( sBBDFileName.GetLength()-3 );
            sBBDFileName += "BBD";
            bEnableReportButton = (FileExists( sBBDFileName ));
         }
      }
   }

   pCmdUI->Enable( bEnableReportButton );
}

void CMainFrame::OnToolReports() 
{
	AfxMessageBox( "CMainFrame::OnToolReports() " );
//   // Get current project's .BBD filename
//   CDocument* pDoc = GetActiveDocument();
//   CString sReportApp = ReadProgString( "files", "ReportApp", "", TRUE );
//   BOOL bContinue = FALSE;
//   if (pDoc && (pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))))
//   {
//      if ( !pDoc->IsModified()  ||
//           (MessageBox( "The building description has changed, and the compliance reports may not be correct.\n\nPress 'OK' to "
//                        "view anyway, or 'Cancel' to return to CBECC to perform analysis.", NULL, MB_OKCANCEL ) == IDOK) )
//      {
//         CString sBBDFileName = pDoc->GetPathName();
//         if (sBBDFileName.GetLength() == 0)
//            MessageBox( "You must save your project and perform the compliance analysis before viewing the compliance reports." );
//         else
//         {
//            sBBDFileName = sBBDFileName.Left( sBBDFileName.GetLength()-3 );
//            sBBDFileName += "BBD";
//            if (!FileExists( sBBDFileName ))
//            {
//               sBBDFileName = "Error:  Budget building results file '" + sBBDFileName;
//               sBBDFileName += "' not found.";
//               MessageBox( sBBDFileName );
//            }
//            else
//            {
//               // now we must write the name of the current .BBD file to the CUIRpt.INI file
//               CString sRptINI = sReportApp;
//               sRptINI = sRptINI.Left( sRptINI.GetLength()-3 );
//               sRptINI += "INI";
//   	         if ( FileExists( sRptINI ) &&
//   	              WritePrivateProfileString( "files", "ResultsFile", sBBDFileName, sRptINI ) )
//                  bContinue = TRUE;
//               else
//               {
//                  sRptINI = "Error:  Writing to or finding CUIRpt INI file '" + sRptINI;
//                  sRptINI += "'.";
//                  MessageBox( sRptINI );
//               }
//            }
//         }
//      }
//   }
//
//   if (bContinue)
//   {
//      CWnd* pCUIRpt = FindWindow( "CUIREPORT", NULL );
//      if (pCUIRpt != NULL)
//      {
//         // send message to cause CUIRpt to refresh its reports BEFORE switching apps
//// TO DO - ONLY POST THIS MESSAGE IF THE REPORT REQUIRES UPDATING, OTHERWISE DON'T POST THIS MESSAGE
//   	   CWaitCursor wait;
//         pCUIRpt->SendMessage( WM_RELOADREPORT );
//
//         CWnd* popup = pCUIRpt->GetLastActivePopup();
//         if (pCUIRpt->IsIconic())
//            pCUIRpt->ShowWindow( SW_SHOWMAXIMIZED );
//         else
//            pCUIRpt->BringWindowToTop();
//         if (pCUIRpt != popup)
//            popup->BringWindowToTop();   // if CUIRpt has active popup window
//      }
//      else
//      {
//         if (!FileExists( sReportApp ))
//         {
//            CString sErr = "Reporting application specified in the .INI file as [files] ReportApp = '";
//            sErr += sReportApp;
//            sErr += "' not found.  Fix the [files] ReportApp entry in the .INI file in order to navigate to the reporting application.";
//            MessageBox( sErr );
//         }
//         else
//         {
//            CString sProgDir = esProgramPath; //ReadProgString( szPaths, szProgPath, "" );
//            LPTSTR lptCommandLine = NULL;
//
//            STARTUPINFO si;
//            memset(&si, 0, sizeof( STARTUPINFO ));
//            si.cb              = sizeof( STARTUPINFO );
//            PROCESS_INFORMATION pi;
//            BOOL bCr8Ret = CreateProcess( sReportApp, lptCommandLine, NULL, NULL, FALSE, 0, NULL, sProgDir, &si, &pi );
//
//            if (bCr8Ret)
//            {
//            }
//            else
//            {
//               /* report failure to the user. */
//               DWORD dwError = GetLastError ();
//               CString sMsg;
//               sMsg.Format( "GetLastError = 0x%lx", (int)dwError );
//               MessageBox( sMsg, "CreateProcess()" );
//            }
//         }
//      }
//   }
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - Tools - Display All UI Controls stuff

void CMainFrame::OnDisplayAllUIControls() 
{
   ebDisplayAllUIControls = !ebDisplayAllUIControls;
}

void CMainFrame::OnUpdateDisplayAllUIControls(CCmdUI* pCmdUI) 
{
//   pCmdUI->Enable( TRUE );
   // SAC 4/27/00 - replaced above w/ below to ensure INI file flag set prior to enabling display of detailed inputs
   pCmdUI->Enable( (eiAllowDisplayOfDetailedInputs > 0) );
   pCmdUI->SetCheck( (ebDisplayAllUIControls ? 1 : 0) );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - Tools - Toggle for performing range checks at beginning of analysis

void CMainFrame::OnAnalysisRangeChecks() 
{
   ebAnalysisRangeChecks = !ebAnalysisRangeChecks;
   WriteProgInt( "options", "AnalysisRangeChecks", (ebAnalysisRangeChecks ? 1 : 0) );
}

void CMainFrame::OnUpdateAnalysisRangeChecks(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( (eiDeveloperMenu > 0) );
   pCmdUI->SetCheck( (ebAnalysisRangeChecks ? 1 : 0) );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - Help - view misc. documentation

void CMainFrame::OnHelpOverview() 
{
	if (!esOverviewPDF.IsEmpty())
		OpenFileViaShellExecute( esOverviewPDF, "Quick Start Guide" /*FileDescrip*/ );
	//	//CString sHelpPDF = esProgramPath + "CBECC-Res_QuickStartGuide.pdf";
	//	if (!esOverviewPDF.IsEmpty() && FileExists( esOverviewPDF ))
	//	{	int idx = esOverviewPDF.ReverseFind('\\');
	//		CString sOverviewPath = (idx > 0 ? esOverviewPDF.Left( idx ) : "");
	//		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", esOverviewPDF, NULL, sOverviewPath, SW_SHOWNORMAL );		hinstShellExec;
	//	}
	//	else
	//	{	CString sPDFNotFound = CString("Program overview documentation not found:\n   ") + esOverviewPDF;
	//		AfxMessageBox( sPDFNotFound );
	//	}
}
void CMainFrame::OnUpdateHelpOverview(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( TRUE );
}

void CMainFrame::OnHelpUserManual() 
{
	if (!esUserManualPDF.IsEmpty())
		OpenFileViaShellExecute( esUserManualPDF, "User Manual" /*FileDescrip*/ );
	//	if (!esUserManualPDF.IsEmpty() && FileExists( esUserManualPDF ))
	//	{	int idx = esUserManualPDF.ReverseFind('\\');
	//		CString sUserManualPath = (idx > 0 ? esUserManualPDF.Left( idx ) : "");
	//		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", esUserManualPDF, NULL, sUserManualPath, SW_SHOWNORMAL );		hinstShellExec;
	//	}
	//	else
	//	{	CString sPDFNotFound = CString("User manual documentation not found:\n   ") + esUserManualPDF;
	//		AfxMessageBox( sPDFNotFound );
	//	}
}
void CMainFrame::OnUpdateHelpUserManual(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( !esUserManualPDF.IsEmpty() );
}


// SAC 4/22/14 - new routines providing access to 
void CMainFrame::OnHelpMandatoryRequirementsForAssemblies() 
{
//	CString sPDF = ReadProgString( "files", "MandReqsAssembliesPDF", "Documents\\Mandatory Requirements for Assemblies.pdf", TRUE );
// SAC 3/24/16 - modified routine to handle 2013 vs. 16 PDFs
	CString sPDF = ReadProgString( "files", "MandReqsAssembliesPDF", "xxx", TRUE );
	if (!FileExists( sPDF ))
	{	CString sCodeYearAbbrev;
		CodeYearAbbrev( sCodeYearAbbrev, false );
		CString sDefPDF;
		if (sCodeYearAbbrev.IsEmpty())	// no project loaded
#ifdef UI_PROGYEAR2016
			sDefPDF = "Documents\\2016 Mandatory Requirements for Assemblies.pdf";
#else
			sDefPDF = "Documents\\Mandatory Requirements for Assemblies.pdf";
#endif
		else if (!sCodeYearAbbrev.Compare("13"))
			sDefPDF = "Documents\\Mandatory Requirements for Assemblies.pdf";
		else
			sDefPDF.Format( "Documents\\20%s Mandatory Requirements for Assemblies.pdf", sCodeYearAbbrev );
		sPDF = ReadProgString( "files", "MandReqsAssembliesPDF_NOT", sDefPDF, TRUE );
	}
	if (!sPDF.IsEmpty())
		OpenFileViaShellExecute( sPDF, "Mandatory Requirements for Assemblies" /*FileDescrip*/ );
	//	if (!sPDF.IsEmpty() && FileExists( sPDF ))
	//	{	int idx = sPDF.ReverseFind('\\');
	//		CString sPDFPath = (idx > 0 ? sPDF.Left( idx ) : "");
	//		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sPDF, NULL, sPDFPath, SW_SHOWNORMAL );		hinstShellExec;
	//	}
	//	else
	//	{	CString sPDFNotFound = CString("Mandatory Requirements for Assemblies document not found:\n   ") + sPDF;
	//		AfxMessageBox( sPDFNotFound );
	//	}
}

void CMainFrame::OnUpdateHelpMandatoryRequirementsForAssemblies(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( TRUE );
}


void CMainFrame::OnHelpCSEDocumentation()		// SAC 11/30/16
{
//	OpenFileViaShellExecute( "https://cse-sim.github.io/cse/index.html", "CSE Simulation Engine Documentation" /*FileDescrip*/ );
	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", "https://cse-sim.github.io/cse/index.html", NULL, "" /*sFilePath*/, SW_SHOWNORMAL );
	hinstShellExec;
}

void CMainFrame::OnUpdateHelpCSEDocumentation(CCmdUI* pCmdUI)
{
   pCmdUI->Enable( TRUE );
}


// SAC 8/19/14 - routines providing access to CBECC-Com compliance form checklist PDFs
void CMainFrame::OnHelpCompFormChecklist_New() 
{	CString sPDF = ReadProgString( "files", "CompFormChecklistNewPDF", "ComplianceForms\\2013 Nonres New Construction Compliance Form checklist.pdf", TRUE );
	if (!sPDF.IsEmpty())
		OpenFileViaShellExecute( sPDF, "Compliance Form Checklist for New Construction projects" /*FileDescrip*/ );
}
void CMainFrame::OnUpdateHelpCompFormChecklist_New(CCmdUI* pCmdUI) 
{	pCmdUI->Enable( TRUE );
}

void CMainFrame::OnHelpCompFormChecklist_Alterations() 
{	CString sPDF = ReadProgString( "files", "CompFormChecklistAlterPDF", "ComplianceForms\\2013 Nonres Alterations Compliance Form checklist.pdf", TRUE );
	if (!sPDF.IsEmpty())
		OpenFileViaShellExecute( sPDF, "Compliance Form Checklist for Alterations projects" /*FileDescrip*/ );
}
void CMainFrame::OnUpdateHelpCompFormChecklist_Alterations(CCmdUI* pCmdUI) 
{	pCmdUI->Enable( TRUE );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - Tools - Toggle for displaying post-wizard compliance checklist help item

void CMainFrame::OnPostHizHelpChecklist() 
{
   ebShowHelpFollowingWizard = !ebShowHelpFollowingWizard;
   WriteProgInt( "options", "ShowHelpFollowingWizard", (ebShowHelpFollowingWizard ? 1 : 0) );
}

void CMainFrame::OnUpdatePostHizHelpChecklist(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( TRUE );
   pCmdUI->SetCheck( (ebShowHelpFollowingWizard ? 1 : 0) );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - Tools - Write Input Details File stuff

void CMainFrame::OnUpdateWriteInputDetails(CCmdUI* pCmdUI) 
{
   CDocument* pDoc = GetActiveDocument();
   if (eInterfaceMode == IM_INPUT && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
      CString sCurrentFileName = pDoc->GetPathName();
      pCmdUI->Enable( FileExists( sCurrentFileName ) );
   }
   else
      pCmdUI->Enable( FALSE );
}

void CMainFrame::OnWriteInputDetails() 
{
	CWaitCursor wait;

   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
      CString sFileName = pDoc->GetPathName();
//      sFileName.SetAt( sFileName.GetLength()-1, '2' );  // should switch .*IBD -> .*IB2
// SAC 1/7/16 - switch file extension mod to simply append "-detail"
		sFileName += "-detail";

		// SAC 6/26/13 - added code to PREVENT ModDate from getting incremented each time project file is written in non-input mode
		long lModDate;
		if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
			lModDate = -1;

      //BEMPX_WriteProjectFile( sFileName, BEMFM_DETAIL /*FALSE*/ );
      BEMPX_WriteProjectFile( sFileName, BEMFM_DETAIL /*FALSE*/, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/,
												0 /*iFileType*/, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, lModDate );

// TESTING
#ifdef _DEBUG
#ifdef UI_CARES
	   CString sDMExportPathFile = ReadProgString( "paths", "RulesetPath", "", TRUE );
	   sDMExportPathFile += "CA Res - Input Data Model from UI.txt";
	   BEMPX_WriteDataModelExport( BEMDMX_INPMP, sDMExportPathFile );		// SAC 10/31/13 - switched from BEMDMX_INP to BEMDMX_INPMP to prevent outputting Prescribed properties
#elif UI_CANRES
	   CString sDMExportPathFile = ReadProgString( "paths", "RulesetPath", "", TRUE );
	   sDMExportPathFile += "CEC NonRes - Input Data Model from UI.txt";
	   BEMPX_WriteDataModelExport( BEMDMX_INPMP, sDMExportPathFile );
#endif
#endif
   }
}


void CMainFrame::OnUpdateWriteAllInputs(CCmdUI* pCmdUI) 
{
   CDocument* pDoc = GetActiveDocument();
   if (eInterfaceMode == IM_INPUT && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
      CString sCurrentFileName = pDoc->GetPathName();
      pCmdUI->Enable( FileExists( sCurrentFileName ) );
   }
   else
      pCmdUI->Enable( FALSE );
}

// SAC 2/6/15 - added new function to mark ALL valid inputable properties as User Input and then store a project file
void CMainFrame::OnWriteAllInputs() 
{
	CDocument* pDoc = GetActiveDocument();
	bool bExitProgram = false;
	if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) && pDoc->SaveModified())
   {
	   CString sCurrentFileName = pDoc->GetPathName();
	   CString sOrigFN = sCurrentFileName;
	   int iLastDotIdx = sCurrentFileName.ReverseFind('.');			ASSERT( iLastDotIdx > 0 );
	   CString sFileExt = sCurrentFileName.Right( sCurrentFileName.GetLength()-iLastDotIdx );
		int iFileType = BEMFT_Std;
		CString sBaseExt, sCodeYr;
		BaseFileExt( sBaseExt );
		CodeYearAbbrev( sCodeYr );	
	   if (!sFileExt.IsEmpty() && IsXMLFileExt( sFileExt ))
		{	sFileExt.Format( ".%s%sx", sBaseExt, sCodeYr );
			iFileType = BEMFT_XML;
		}
	   else
			sFileExt.Format( ".%s%s", sBaseExt, sCodeYr );

		sCurrentFileName = sCurrentFileName.Left( iLastDotIdx ) + CString( " - AllInputs" ) + sFileExt;

	//		if (bSetSoftwareVer)		// SAC 1/12/15
	//		{	UpdateSoftwareVersionString();		// SAC 9/17/12
	//			SetBEMVersionID();						// SAC 9/17/12
	//		}
	//		if (ReadProgInt( "options", "ClassifyEditableDefaultsAsUserData", 1 /*default*/ ) > 0)
				VERIFY( BEMPX_SetPropertiesToUserDefined( /*iBEMProcIdx=-1*/ ) >= 0 );

			bool bFileSaveAllDefinedProperties	= 0;  // (ReadProgInt( "options", "FileSaveAllDefinedProperties", 0 /*default*/ ) > 0);  // SAC 3/17/13
			bool bFileSaveOnlyValidInputs			= 0;  // (ReadProgInt( "options", "FileSaveOnlyValidInputs", 0 /*default*/ ) > 0);  // SAC 4/16/14          

			if (BEMPX_WriteProjectFile( sCurrentFileName, BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/, bFileSaveAllDefinedProperties /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/,
													iFileType, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/, -1 /*lModDate*/, bFileSaveOnlyValidInputs ))  // SAC 6/26/13
      	{
   //   	   WriteToLogFile( WM_LOGUPDATED, "Project Saved" );

				int iUserAction = AfxMessageBox( "All user-inputable data has been re-classified as User Defined.\nSelect 'Yes' to make this the currently active project, "
															"'No' to re-load the original project or 'Cancel' to exit the program.", MB_YESNOCANCEL /*, AFX_IDP_ASK_TO_SAVE*/ );
				switch (iUserAction)
				{	case IDCANCEL:		bExitProgram = true;		// exit application if user chooses
															break;
					case IDYES:
					case IDOK:			pDoc->SetPathName( sCurrentFileName );
											pDoc->SetModifiedFlag( FALSE );
															break;
					case IDNO:			if (((CComplianceUIDoc*)pDoc)->OpenTheFile( sOrigFN, TRUE /*bWriteToLog*/, FALSE /*bRestore*/, NULL /*pszNewRuleFile*/,
            																						-1 /*lRulesetSymVal*/, FALSE /*bNormalRulesetUpdates*/ ))	// SAC 11/17/15
											{ }
															break;
					default:				ASSERT(FALSE);
															break;
				}
			}
			else
				bExitProgram = true;	// exit application if error encountered saving filw
	}
	if (bExitProgram)
		PostMessage( WM_COMMAND, ID_APP_EXIT, 0L );
}


void CMainFrame::OnUpdateRewriteInput(CCmdUI* pCmdUI) 
{
   CDocument* pDoc = GetActiveDocument();
   if (eInterfaceMode == IM_INPUT && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
      CString sCurrentFileName = pDoc->GetPathName();
      pCmdUI->Enable( FileExists( sCurrentFileName ) );
   }
   else
      pCmdUI->Enable( FALSE );
}

void CMainFrame::OnRewriteInput() 
{
	CWaitCursor wait;
   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
		long lModDate;
		if (!BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
		{	ASSERT( FALSE );
			lModDate = -1;
		}
	// SAVE PROJECT FILE
		SaveFile( NULL, lModDate, false /*bSetSoftwareVer*/ );
   }
}


void CMainFrame::OnUpdateExportHPXML_Single(CCmdUI* pCmdUI) 
{
#ifdef UI_CARES
   CDocument* pDoc = GetActiveDocument();
   pCmdUI->Enable( (eInterfaceMode == IM_INPUT && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc))) );
#else
   pCmdUI->Enable( FALSE );
#endif
}

void CMainFrame::OnExportHPXML_Single() 
{	CString sMsg;
   CDocument* pDoc = GetActiveDocument();
   if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
		CWaitCursor wait;

		BOOL bLogRuleEvaluation = (ReadProgInt( "options", "LogRuleEvaluation", 0 /*default*/ ) > 0);   // SAC 8/22/11
		BOOL bMarkRuleDataUserDefined = (ReadProgInt( "options", "MarkRuleDataUserDefined", 0 /*default*/ ) > 0);  // SAC 3/17/13
	   BOOL bEvalSuccessful = CMX_EvaluateRuleset( "HPXML", bLogRuleEvaluation, bMarkRuleDataUserDefined /*bTagDataAsUserDefined*/, bLogRuleEvaluation /*bVerboseOutput*/ );  // , NULL, NULL, NULL, epInpRuleDebugInfo );
		if (!bEvalSuccessful)
	//	{	CString sLogFN = BEMPX_GetLogFilename();				ASSERT( !sLogFN.IsEmpty() );
		{	QString qsLogFN = BEMPX_GetLogFilename();		CString sLogFN = qsLogFN.toLatin1().constData();		ASSERT( !sLogFN.IsEmpty() );
			if (sLogFN.IsEmpty())
				sMsg = "HPXML translation rule evaluation failed.";
			else
				sMsg.Format( "HPXML translation rule evaluation failed.  Check project log file for error messages:\n   %s", sLogFN );
		}
		else
		{
	      CString sFileName = pDoc->GetPathName();
	      int iDotIdx = sFileName.ReverseFind('.');
	      if (iDotIdx > 0)
	      	sFileName = sFileName.Left( iDotIdx );
   	   sFileName += " - sgl hpxml.xml";
			if (FileExists( sFileName ))
			{	// if output file already exists, prompt for new output file (w/ prompt for overwrite)
	      	CFileDialog dlgSvAs( FALSE, _T("xml"), sFileName, OFN_OVERWRITEPROMPT | OFN_SHOWHELP | OFN_HIDEREADONLY,
  		   	                 _T("HPXML Files (*.xml)|*.xml||"), this );
     			if (dlgSvAs.DoModal()==IDOK)
     			   sFileName = dlgSvAs.GetPathName();
				else
     			   sFileName.Empty();
			}
			if (sFileName.IsEmpty())
				sMsg = "HPXML translation rule evaluation failed - no export path/file selected.";
			else
			{	if (BEMPX_WriteProjectFile( sFileName, BEMFM_INPUT /*FALSE*/, FALSE /*bUseLogFileName*/, FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/,
														BEMFT_HPXML1 /*iFileType*/, false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/ ))
						//	#define  BEMFM_INPUT   0  // SAC 5/22/12 - added new "simulation" mode
						//	#define  BEMFM_DETAIL  1
						//	#define  BEMFM_SIM     2
						//	
						//	#define  BEMFT_Std    0
						//	#define  BEMFT_CSE    1
						//	#define  BEMFT_XML    2    // SAC 10/26/11
						//	#define  BEMFT_HPXML1 3    // SAC 12/2/15
						//	#define  BEMFT_HPXML2 4    // SAC 12/2/15
						//	#define BEMPX_IsHPXML( iFileType )  (int)  (iFileType == BEMFT_HPXML1 || iFileType == BEMFT_HPXML2)
						//	#define BEMPX_IsXML(   iFileType )  (int)  (iFileType == BEMFT_HPXML1 || iFileType == BEMFT_HPXML2 || iFileType == BEMFT_XML)
					sMsg.Format( "HPXML export succeeded to file:\n   %s", sFileName );
				else
					sMsg.Format( "HPXML export failed - writing to file:\n   %s", sFileName );
			}
		}
	}
	else
		sMsg = "HPXML export failed - valid compliance project/document not loaded.";
	if (!sMsg.IsEmpty())
		MessageBox( sMsg );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame - View Input/Proposed/Budget building stuff

static char BASED_CODE szDFOK1a[] = "You must select File - Save to save the current project and then";
static char BASED_CODE szDFOK2a[] = "You must";
static char BASED_CODE szDFOK3a[] = "This project's compliance results are out of date.  You must";
static char BASED_CODE szDFOK4a[] = "Error retrieving file status.  ";
static char BASED_CODE szDFOKb[]  = " perform a compliance check before you can view the compliance report.";

BOOL CMainFrame::DetailedFileOK( CString& sFileName, BOOL bProposed, BOOL bPromptUser )
{
   CString sError;
   CDocument* pDoc = GetActiveDocument();
   if (pDoc)
   {
      CString sInputFile = pDoc->GetPathName();
      if (sInputFile.GetLength() > 4)
         sInputFile.SetAt( sInputFile.GetLength()-3, 'I' );

      if ( ( pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)) &&
             (((CComplianceUIDoc*) pDoc)->IsModified()) ) ||
           (sInputFile.GetLength() < 5) || (!FileExists( sInputFile )) )
         sError = szDFOK1a;
      else
      {
         sFileName = pDoc->GetPathName();
         sFileName.SetAt( sFileName.GetLength()-3, (bProposed ? 'P' : 'B') );
         if (!FileExists( sFileName ))
            sError = szDFOK2a;
         else
         {
            CFileStatus inpStatus, outStatus;
            if ( (CFile::GetStatus( sInputFile, inpStatus )) &&
                 (CFile::GetStatus(  sFileName, outStatus )) )
            {
               if (inpStatus.m_mtime > outStatus.m_mtime)
                  sError = szDFOK3a;
            }
            else
            {
               sError = szDFOK4a;
               sError += szDFOK1a;
            }
         }
      }
   }

   if ( (sError.GetLength() > 0) && (bPromptUser) )
   {
      sError += szDFOKb;
      AfxMessageBox( sError );
   }

   return (sError.GetLength() == 0);
}


void CMainFrame::UpdateViewOption(InterfaceMode eIntMode, CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck( (eInterfaceMode == eIntMode) );

   if (eIntMode == IM_INPUT)
      pCmdUI->Enable( TRUE );  // User can ALWAYS switch to IM_INPUT mode
   else
   {  // Enable only if this project has a valid detailed file of the desired type
      CString sTemp;
      pCmdUI->Enable( DetailedFileOK( sTemp, (eIntMode == IM_PROPOSED), FALSE ) );
   }
}


void CMainFrame::SwitchViewOption( InterfaceMode eIntMode )
{
   CDocument* pDoc = GetActiveDocument();
   if (eInterfaceMode != eIntMode && pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
   {
      CString sFileName = pDoc->GetPathName();
      if (sFileName.GetLength() > 0 && FileExists( sFileName ))
      {
         // Import and Display eIntMode version of current project
         sFileName = sFileName.Left( sFileName.GetLength()-3 ) + pszCUIFileExt[ eIntMode ];
         if (FileExists( sFileName ))
            ((CComplianceUIDoc*)pDoc)->OpenTheFile( sFileName, TRUE /*bWriteToLog*/, FALSE /*bRestore*/, NULL /*pszNewRuleFile*/,
            														-1 /*lRulesetSymVal*/, FALSE /*bNormalRulesetUpdates*/ );	// SAC 11/17/15
      }
   }
}

void CMainFrame::OnToolsEvalRulelist() 
{
   CDlgEvaluateRulelist dlg( this );
   dlg.DoModal();
}


////////////////////////////////////////////////////////////////////////////////
// routines supporting access to documents stored in a particular directory
////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUpdateFileList(CCmdUI* pCmdUI, int i1FileListID)
{	pCmdUI->Enable( (i1FileListID <= m_iNumFileListMenuItems) );
}

void CMainFrame::OnFileList( int i1FileListID )
{
	CString sMsg;
	if (i1FileListID > m_iNumFileListMenuItems || i1FileListID > m_saFileListPathFiles.GetSize())
		sMsg.Format( "Unable to display file - invalid file index (%d).", i1FileListID );
	else if (m_saFileListPathFiles[i1FileListID-1].IsEmpty())
		sMsg.Format( "Unable to display file - path to file %d not loaded.", i1FileListID );
	else if (!FileExists( m_saFileListPathFiles[i1FileListID-1] ))
		sMsg.Format( "Unable to display file - file %d not found: '%s'.", i1FileListID, m_saFileListPathFiles[i1FileListID-1] );
	else
	{	OpenFileViaShellExecute( m_saFileListPathFiles[i1FileListID-1], "Disk" /*FileDescrip*/ );
		//	int idx = m_saFileListPathFiles[i1FileListID-1].ReverseFind('\\');
		//	CString sFileListPath = (idx > 0 ? m_saFileListPathFiles[i1FileListID-1].Left( idx ) : "");
		//	HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", m_saFileListPathFiles[i1FileListID-1], NULL, sFileListPath, SW_SHOWNORMAL );		hinstShellExec;
	}
	if (!sMsg.IsEmpty())
		MessageBox( sMsg );
}

/////////////////////////////////////////////////////////////////////////////

bool CMainFrame::OpenFileViaShellExecute( CString sFile, const char* pszFileDescrip )
{	bool bRetVal = false;
	if (!sFile.IsEmpty() && FileExists( sFile ))
	{	int idx = sFile.ReverseFind('\\');
		CString sFilePath = (idx > 0 ? sFile.Left( idx ) : "");
		bRetVal = true;
		HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sFile, NULL, sFilePath, SW_SHOWNORMAL );		hinstShellExec;
	}
	else if (!sFile.IsEmpty())
	{	CString sFileNotFound;
		sFileNotFound.Format( "%s file not found:\n   ", pszFileDescrip, sFile );
		AfxMessageBox( sFileNotFound );
	}
	return bRetVal;
}
