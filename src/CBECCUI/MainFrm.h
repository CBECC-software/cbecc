// MainFrm.h : interface of the CMainFrame class
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

#if !defined(AFX_MAINFRM_H__245352C9_5683_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_MAINFRM_H__245352C9_5683_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\BEMCmpMgr\BEMCmpMgr.h"
#include "CUIGlobl.h"
#include "BEMGridDialog.h"

// Quick Menu Flag IDs
#define QMI_ITEMHELP    0x0001
#define QMI_TOPICHELP   0x0002
#define QMI_DEFAULT     0x0004
#define QMI_COMMENT     0x0008
#define QMI_CREATE      0x0010
#define QMI_EDIT        0x0020
#define QMI_DELETE      0x0040


class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
//protected:
//	CSplitterWnd m_wndSplitter;
public:
	CSplitterWnd m_wndSplitter;
//   CString      m_sCurrentFileName;  
   BOOL  m_bDoingWizard;
   BOOL  m_bDoingSummaryReport;
   BOOL  m_bPerformingAnalysis;	// SAC 4/1/15
   BOOL  m_bPerformingCUACAnalysis;	// SAC 08/19/22 (CUAC)
   BOOL  m_bDoingCustomRuleEval;	// SAC 1/28/18
   int   m_iNumInitRESNETBldgObjs;	// SAC 9/29/20

	int   m_iNumFileListMenuItems;  // SAC 11/19/13
	CStringArray m_saFileListPathFiles;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	// SAC 6/26/13 - added ModDate override to enable analysis results validity checking 
	void SaveFile( const char* psFileName, long lModDate=-1, bool bSetSoftwareVer=true );		// SAC 1/12/15 - added bSetSoftwareVer to facilitate old project file cleanup
//   BOOL OpenTheFile( CPathName sInputFile, BOOL bWriteToLog=TRUE, BOOL bRestore=FALSE );

   void WriteToLogFile( UINT uiViewMsg = WM_DISPLAYDATA, const char* output = NULL, 
                        const char* psNewLogFileName = NULL, BOOL bBlankFile = FALSE );

   void WriteSimulationInput( SimulationType eSimType );

	BOOL UpdateSoftwareVersionString();		// SAC 9/17/12
	BOOL SetBEMVersionID();						// SAC 9/17/12

	int  GenerateReport( int iReportID, bool bSilent=false );		// SAC 10/8/14  // SAC 04/13/21  // void->int SAC 11/02/22
	void ViewReport( int iReportID=0 );		// SAC 11/18/15

	bool CheckReportGenAccess( bool bDisplayResult );		// SAC 2/19/15

	void CheckBuildingModel( BOOL bReportModelOK=TRUE, BOOL bPerformRangeChecks=TRUE );	// SAC 5/1/14 

	BOOL PopulateAnalysisOptionsString( CString& sOptionsCSVString, bool bBatchMode=false, const char* pszAltOptsName=NULL );		// SAC 1/29/14  // SAC 6/21/18

	int CheckWhichReportsToGenerate( CString& sRptList );	// SAC 2/19/15

   void CreateBuildingComponent( int i1BDBClass, long lAssignmentDBID=0, BOOL bEditNewComponent=TRUE,
                                 CWnd* pParentWnd=NULL, long lObjTypeDBID=0, long lObjTypeValue=0,
											int iAssignmentObjIdx=-1,   // SAC 5/29/13 - added new argument to ensure that assignment of new object occurs to correct assigning object (assigns new to self when assignee & assigner the same object type)
											BEMObject* pParentBEMObject = NULL );		// SAC 5/29/14 - new argument to specify parent of new object being create
	bool ConvertBuildingComponent( int iFromBEMClass, int iFromObjIdx, int iToBEMClass );	// SAC 10/13/15
   BOOL DeleteBuildingComponent( BEMObject* pObj, CWnd* pParentWnd=NULL );
	void SetupNewProject();		// SAC 2/28/14

	bool OpenFileViaShellExecute( CString sFile, const char* pszFileDescrip );		// SAC 8/19/14

   void SetStatusBarStrings(CString sStr, long lDBID);

   void DoQuickMenu( int iLeft, int iRight, int iTop, UINT uiQuickMask,
                     DWORD dwItemHlpID=0, DWORD dwTopicHlpID=0, long lDBID=0,
                     BOOL bObjectAssign=FALSE, int iDBInstance=-1 );

	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	long DataModified(long lDBID, int iObjIdx=-1);

   void PostBEMGridClose( UINT wClass=0, LONG l1Occur=0);
   void PostBEMGridUpdate(UINT wClass=0, LONG l1Occur=0);

	void AutoSaveAsPrecheck( int iBDBClass );
	void ExecuteAutoSaveAs(  int iBDBClass );

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BEMGridDialog* gridDialog;		// SAC 3/9/18

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditComponent();
	afx_msg void OnUpdateEditComponent(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnWriteAnnualSimulationInput();
	afx_msg void OnWriteDesignDaySimulationInput();
	afx_msg void OnCreateComponent();
	afx_msg void OnReloadScreens();
	afx_msg void OnMPerformAnalysis();
	afx_msg void OnPerformAPIAnalysis();
	afx_msg void OnUpdateEditSwitchRuleset1(CCmdUI* pCmdUI);
	afx_msg void OnCheckBldgDBase();
	afx_msg void OnUpdateToolWizard(CCmdUI* pCmdUI);
	afx_msg void OnToolWizard();
	afx_msg void OnUpdateToolAnalysis(CCmdUI* pCmdUI);
	afx_msg void OnToolAnalysis();
	afx_msg void OnUpdateToolReports(CCmdUI* pCmdUI);
	afx_msg void OnToolReports();
	afx_msg void OnUpdateToolResults(CCmdUI* pCmdUI);
	afx_msg void OnToolResults();
	afx_msg void OnDeleteComponent();
	afx_msg void OnUpdateDeleteComponent(CCmdUI* pCmdUI);
	afx_msg void OnDisplayAllUIControls();
	afx_msg void OnUpdateDisplayAllUIControls(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewInput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewProposed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewBudget(CCmdUI* pCmdUI);
	afx_msg void OnViewInput();
	afx_msg void OnViewProposed();
	afx_msg void OnViewBudget();
	afx_msg void OnUpdateWriteInputDetails(CCmdUI* pCmdUI);
	afx_msg void OnWriteInputDetails();
	afx_msg void OnUpdateWriteAllInputs(CCmdUI* pCmdUI);
	afx_msg void OnWriteAllInputs();
	afx_msg void OnUpdateRewriteInput(CCmdUI* pCmdUI);
	afx_msg void OnRewriteInput();
	afx_msg void OnUpdateExportHPXML_Single(CCmdUI* pCmdUI);
	afx_msg void OnExportHPXML_Single();
	afx_msg void OnUpdateCreateComponent(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePerformAnalysis(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePerformAPIAnalysis(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnToolsApplyCustomRules();
	afx_msg void OnUpdateApplyCustomRules(CCmdUI* pCmdUI); 
	afx_msg void OnToolsShowModelGrid();
	afx_msg void OnUpdateShowModelGrid(CCmdUI* pCmdUI); 
	afx_msg void OnToolsEvalRulelist();
	afx_msg void OnAnalysisRangeChecks();
	afx_msg void OnUpdateAnalysisRangeChecks(CCmdUI* pCmdUI);
   afx_msg void OnHelpOverview(); 
   afx_msg void OnUpdateHelpOverview(CCmdUI* pCmdUI);
   afx_msg void OnHelpUserManual(); 
   afx_msg void OnUpdateHelpUserManual(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnUpdatePostHizHelpChecklist(CCmdUI* pCmdUI);
	afx_msg void OnPostHizHelpChecklist();
	afx_msg void OnUpdateToolsReviewResults(CCmdUI* pCmdUI);
	afx_msg void OnToolsReviewResults();
	afx_msg void OnUpdateToolsUMLHViolations(CCmdUI* pCmdUI);
	afx_msg void OnToolsUMLHViolations();
	afx_msg void OnUpdateToolsViewCSEErrors(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewCSEErrors();
	afx_msg void OnUpdateToolsViewCSEReports(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewCSEReports();
	afx_msg void OnUpdateToolsViewT24ComplianceReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewT24ComplianceReport();
	afx_msg void OnUpdateToolsViewT24StandardModelReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewT24StandardModelReport();
	afx_msg void OnUpdateToolsT24ComplianceReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsT24ComplianceReport();
	afx_msg void OnUpdateToolsT24StandardModelReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsT24StandardModelReport();
	afx_msg void OnUpdateToolsCAHPReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsCAHPReport();
	afx_msg void OnUpdateToolsViewCUACSubmittalReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewCUACSubmittalReport();
	afx_msg void OnUpdateToolsViewCUACDetailsReport(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewCUACDetailsReport();
	afx_msg void OnUpdateToolsViewCUACDetailsCSV(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewCUACDetailsCSV();
	afx_msg void OnUpdateToolsCheckReportGenAccess(CCmdUI* pCmdUI);
	afx_msg void OnToolsCheckReportGenAccess();
	afx_msg void OnUpdateToolsReport_BuildingSummary(CCmdUI* pCmdUI);
	afx_msg void OnToolsReport_BuildingSummary();
	afx_msg void OnUpdateToolsReport_BuildingSummary_T24(CCmdUI* pCmdUI);
	afx_msg void OnToolsReport_BuildingSummary_T24();
	afx_msg void OnUpdateToolsBatchProcessing(CCmdUI* pCmdUI);
	afx_msg void OnToolsBatchProcessing();
	afx_msg void OnUpdateToolsCommSlrOptOut(CCmdUI* pCmdUI);
	afx_msg void OnToolsCommSlrOptOut();
	afx_msg void OnUpdateToolsRunTest(CCmdUI* pCmdUI);
	afx_msg void OnToolsRunTest();
	afx_msg void OnUpdateToolsGenerateFileHashes(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateFileHashes();
	afx_msg void OnUpdateToolsGenerateMECH1ReportRecords(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateMECH1ReportRecords();
	afx_msg void OnUpdateToolsGenerateDHWEquipReportRecords(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateDHWEquipReportRecords();
	afx_msg void OnUpdateToolsGenerateIAQVentReportRecords(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateIAQVentReportRecords();
	afx_msg void OnUpdateToolsOptions(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions();
	afx_msg void OnUpdateToolsProxy(CCmdUI* pCmdUI);
	afx_msg void OnToolsProxy();
	afx_msg void OnUpdateToolsGenerateModel(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateModel();
	afx_msg void OnUpdateToolsViewFolder(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewFolder();
	afx_msg void OnUpdateToolsViewLog(CCmdUI* pCmdUI);
	afx_msg void OnToolsViewLog();
	afx_msg void OnUpdateToolsDeleteLog(CCmdUI* pCmdUI);
	afx_msg void OnToolsDeleteLog();
	afx_msg void OnUpdateToolsPurgeUnreferencedObjects(CCmdUI* pCmdUI);
	afx_msg void OnToolsPurgeUnreferencedObjects();
	afx_msg void OnUpdateToolsGenerateWindowShades(CCmdUI* pCmdUI);
	afx_msg void OnToolsGenerateWindowShades();
	afx_msg void OnUpdateToolsGeneratePublicKey(CCmdUI* pCmdUI);
	afx_msg void OnToolsGeneratePublicKey();
	afx_msg void OnUpdateToolsKeyPrep(CCmdUI* pCmdUI);
	afx_msg void OnToolsKeyPrep();
	afx_msg void OnUpdateFileImportModel(CCmdUI* pCmdUI);
	afx_msg void OnFileImportModel();
	afx_msg void OnUpdateFileImportResGeometry(CCmdUI* pCmdUI);
	afx_msg void OnFileImportResGeometry();
	afx_msg void OnUpdateFileImportNonResGeometry(CCmdUI* pCmdUI);
	afx_msg void OnFileImportNonResGeometry();
   afx_msg void OnHelpMandatoryRequirementsForAssemblies();
   afx_msg void OnUpdateHelpMandatoryRequirementsForAssemblies(CCmdUI* pCmdUI);
   afx_msg void OnHelpCSEDocumentation();
   afx_msg void OnUpdateHelpCSEDocumentation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpCompFormChecklist_New(CCmdUI* pCmdUI);
	afx_msg void OnHelpCompFormChecklist_New();
	afx_msg void OnUpdateHelpCompFormChecklist_Alterations(CCmdUI* pCmdUI);
	afx_msg void OnHelpCompFormChecklist_Alterations();
   afx_msg void OnTimer( UINT_PTR nIDEvent );		// SAC 10/21/20 - setup timer to prevent system sleep during analysis
	//}}AFX_MSG

	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );

	afx_msg void OnUpdateFileList_01(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  1 );	};
	afx_msg void OnUpdateFileList_02(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  2 );	};
	afx_msg void OnUpdateFileList_03(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  3 );	};
	afx_msg void OnUpdateFileList_04(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  4 );	};
	afx_msg void OnUpdateFileList_05(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  5 );	};
	afx_msg void OnUpdateFileList_06(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  6 );	};
	afx_msg void OnUpdateFileList_07(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  7 );	};
	afx_msg void OnUpdateFileList_08(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  8 );	};
	afx_msg void OnUpdateFileList_09(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI,  9 );	};
	afx_msg void OnUpdateFileList_10(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 10 );	};
	afx_msg void OnUpdateFileList_11(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 11 );	};
	afx_msg void OnUpdateFileList_12(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 12 );	};
	afx_msg void OnUpdateFileList_13(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 13 );	};
	afx_msg void OnUpdateFileList_14(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 14 );	};
	afx_msg void OnUpdateFileList_15(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 15 );	};
	afx_msg void OnUpdateFileList_16(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 16 );	};
	afx_msg void OnUpdateFileList_17(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 17 );	};
	afx_msg void OnUpdateFileList_18(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 18 );	};
	afx_msg void OnUpdateFileList_19(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 19 );	};
	afx_msg void OnUpdateFileList_20(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 20 );	};
	afx_msg void OnUpdateFileList_21(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 21 );	};
	afx_msg void OnUpdateFileList_22(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 22 );	};
	afx_msg void OnUpdateFileList_23(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 23 );	};
	afx_msg void OnUpdateFileList_24(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 24 );	};
	afx_msg void OnUpdateFileList_25(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 25 );	};
	afx_msg void OnUpdateFileList_26(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 26 );	};
	afx_msg void OnUpdateFileList_27(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 27 );	};
	afx_msg void OnUpdateFileList_28(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 28 );	};
	afx_msg void OnUpdateFileList_29(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 29 );	};
	afx_msg void OnUpdateFileList_30(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 30 );	};
	afx_msg void OnUpdateFileList_31(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 31 );	};
	afx_msg void OnUpdateFileList_32(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 32 );	};
	afx_msg void OnUpdateFileList_33(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 33 );	};
	afx_msg void OnUpdateFileList_34(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 34 );	};
	afx_msg void OnUpdateFileList_35(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 35 );	};
	afx_msg void OnUpdateFileList_36(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 36 );	};
	afx_msg void OnUpdateFileList_37(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 37 );	};
	afx_msg void OnUpdateFileList_38(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 38 );	};
	afx_msg void OnUpdateFileList_39(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 39 );	};
	afx_msg void OnUpdateFileList_40(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 40 );	};
	afx_msg void OnUpdateFileList_41(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 41 );	};
	afx_msg void OnUpdateFileList_42(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 42 );	};
	afx_msg void OnUpdateFileList_43(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 43 );	};
	afx_msg void OnUpdateFileList_44(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 44 );	};
	afx_msg void OnUpdateFileList_45(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 45 );	};
	afx_msg void OnUpdateFileList_46(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 46 );	};
	afx_msg void OnUpdateFileList_47(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 47 );	};
	afx_msg void OnUpdateFileList_48(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 48 );	};
	afx_msg void OnUpdateFileList_49(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 49 );	};
	afx_msg void OnUpdateFileList_50(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 50 );	};
	afx_msg void OnUpdateFileList_51(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 51 );	};
	afx_msg void OnUpdateFileList_52(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 52 );	};
	afx_msg void OnUpdateFileList_53(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 53 );	};
	afx_msg void OnUpdateFileList_54(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 54 );	};
	afx_msg void OnUpdateFileList_55(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 55 );	};
	afx_msg void OnUpdateFileList_56(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 56 );	};
	afx_msg void OnUpdateFileList_57(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 57 );	};
	afx_msg void OnUpdateFileList_58(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 58 );	};
	afx_msg void OnUpdateFileList_59(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 59 );	};
	afx_msg void OnUpdateFileList_60(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 60 );	};
	afx_msg void OnUpdateFileList_61(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 61 );	};
	afx_msg void OnUpdateFileList_62(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 62 );	};
	afx_msg void OnUpdateFileList_63(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 63 );	};
	afx_msg void OnUpdateFileList_64(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 64 );	};
	afx_msg void OnUpdateFileList_65(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 65 );	};
	afx_msg void OnUpdateFileList_66(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 66 );	};
	afx_msg void OnUpdateFileList_67(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 67 );	};
	afx_msg void OnUpdateFileList_68(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 68 );	};
	afx_msg void OnUpdateFileList_69(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 69 );	};
	afx_msg void OnUpdateFileList_70(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 70 );	};
	afx_msg void OnUpdateFileList_71(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 71 );	};
	afx_msg void OnUpdateFileList_72(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 72 );	};
	afx_msg void OnUpdateFileList_73(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 73 );	};
	afx_msg void OnUpdateFileList_74(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 74 );	};
	afx_msg void OnUpdateFileList_75(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 75 );	};
	afx_msg void OnUpdateFileList_76(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 76 );	};
	afx_msg void OnUpdateFileList_77(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 77 );	};
	afx_msg void OnUpdateFileList_78(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 78 );	};
	afx_msg void OnUpdateFileList_79(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 79 );	};
	afx_msg void OnUpdateFileList_80(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 80 );	};
	afx_msg void OnUpdateFileList_81(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 81 );	};
	afx_msg void OnUpdateFileList_82(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 82 );	};
	afx_msg void OnUpdateFileList_83(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 83 );	};
	afx_msg void OnUpdateFileList_84(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 84 );	};
	afx_msg void OnUpdateFileList_85(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 85 );	};
	afx_msg void OnUpdateFileList_86(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 86 );	};
	afx_msg void OnUpdateFileList_87(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 87 );	};
	afx_msg void OnUpdateFileList_88(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 88 );	};
	afx_msg void OnUpdateFileList_89(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 89 );	};
	afx_msg void OnUpdateFileList_90(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 90 );	};
	afx_msg void OnUpdateFileList_91(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 91 );	};
	afx_msg void OnUpdateFileList_92(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 92 );	};
	afx_msg void OnUpdateFileList_93(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 93 );	};
	afx_msg void OnUpdateFileList_94(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 94 );	};
	afx_msg void OnUpdateFileList_95(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 95 );	};
	afx_msg void OnUpdateFileList_96(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 96 );	};
	afx_msg void OnUpdateFileList_97(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 97 );	};
	afx_msg void OnUpdateFileList_98(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 98 );	};
	afx_msg void OnUpdateFileList_99(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 99 );	};
	afx_msg void OnUpdateFileList_100(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 100 );	};
	afx_msg void OnUpdateFileList_101(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 101 );	};
	afx_msg void OnUpdateFileList_102(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 102 );	};
	afx_msg void OnUpdateFileList_103(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 103 );	};
	afx_msg void OnUpdateFileList_104(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 104 );	};
	afx_msg void OnUpdateFileList_105(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 105 );	};
	afx_msg void OnUpdateFileList_106(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 106 );	};
	afx_msg void OnUpdateFileList_107(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 107 );	};
	afx_msg void OnUpdateFileList_108(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 108 );	};
	afx_msg void OnUpdateFileList_109(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 109 );	};
	afx_msg void OnUpdateFileList_110(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 110 );	};
	afx_msg void OnUpdateFileList_111(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 111 );	};
	afx_msg void OnUpdateFileList_112(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 112 );	};
	afx_msg void OnUpdateFileList_113(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 113 );	};
	afx_msg void OnUpdateFileList_114(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 114 );	};
	afx_msg void OnUpdateFileList_115(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 115 );	};
	afx_msg void OnUpdateFileList_116(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 116 );	};
	afx_msg void OnUpdateFileList_117(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 117 );	};
	afx_msg void OnUpdateFileList_118(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 118 );	};
	afx_msg void OnUpdateFileList_119(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 119 );	};
	afx_msg void OnUpdateFileList_120(CCmdUI* pCmdUI)	{	OnUpdateFileList( pCmdUI, 120 );	};
	afx_msg void OnFileList_01()	{  OnFileList(  1 ); };
	afx_msg void OnFileList_02()  {  OnFileList(  2 ); };
	afx_msg void OnFileList_03()  {  OnFileList(  3 ); };
	afx_msg void OnFileList_04()  {  OnFileList(  4 ); };
	afx_msg void OnFileList_05()  {  OnFileList(  5 ); };
	afx_msg void OnFileList_06()  {  OnFileList(  6 ); };
	afx_msg void OnFileList_07()  {  OnFileList(  7 ); };
	afx_msg void OnFileList_08()  {  OnFileList(  8 ); };
	afx_msg void OnFileList_09()  {  OnFileList(  9 ); };
	afx_msg void OnFileList_10()  {  OnFileList( 10 ); };
	afx_msg void OnFileList_11()  {  OnFileList( 11 ); };
	afx_msg void OnFileList_12()  {  OnFileList( 12 ); };
	afx_msg void OnFileList_13()  {  OnFileList( 13 ); };
	afx_msg void OnFileList_14()  {  OnFileList( 14 ); };
	afx_msg void OnFileList_15()  {  OnFileList( 15 ); };
	afx_msg void OnFileList_16()  {  OnFileList( 16 ); };
	afx_msg void OnFileList_17()  {  OnFileList( 17 ); };
	afx_msg void OnFileList_18()  {  OnFileList( 18 ); };
	afx_msg void OnFileList_19()  {  OnFileList( 19 ); };
	afx_msg void OnFileList_20()  {  OnFileList( 20 ); };
	afx_msg void OnFileList_21()  {  OnFileList( 21 ); };
	afx_msg void OnFileList_22()  {  OnFileList( 22 ); };
	afx_msg void OnFileList_23()  {  OnFileList( 23 ); };
	afx_msg void OnFileList_24()  {  OnFileList( 24 ); };
	afx_msg void OnFileList_25()  {  OnFileList( 25 ); };
	afx_msg void OnFileList_26()  {  OnFileList( 26 ); };
	afx_msg void OnFileList_27()  {  OnFileList( 27 ); };
	afx_msg void OnFileList_28()  {  OnFileList( 28 ); };
	afx_msg void OnFileList_29()  {  OnFileList( 29 ); };
	afx_msg void OnFileList_30()  {  OnFileList( 30 ); };
	afx_msg void OnFileList_31()  {  OnFileList( 31 ); };
	afx_msg void OnFileList_32()  {  OnFileList( 32 ); };
	afx_msg void OnFileList_33()  {  OnFileList( 33 ); };
	afx_msg void OnFileList_34()  {  OnFileList( 34 ); };
	afx_msg void OnFileList_35()  {  OnFileList( 35 ); };
	afx_msg void OnFileList_36()  {  OnFileList( 36 ); };
	afx_msg void OnFileList_37()  {  OnFileList( 37 ); };
	afx_msg void OnFileList_38()  {  OnFileList( 38 ); };
	afx_msg void OnFileList_39()  {  OnFileList( 39 ); };
	afx_msg void OnFileList_40()  {  OnFileList( 40 ); };
	afx_msg void OnFileList_41()  {  OnFileList( 41 ); };
	afx_msg void OnFileList_42()  {  OnFileList( 42 ); };
	afx_msg void OnFileList_43()  {  OnFileList( 43 ); };
	afx_msg void OnFileList_44()  {  OnFileList( 44 ); };
	afx_msg void OnFileList_45()  {  OnFileList( 45 ); };
	afx_msg void OnFileList_46()  {  OnFileList( 46 ); };
	afx_msg void OnFileList_47()  {  OnFileList( 47 ); };
	afx_msg void OnFileList_48()  {  OnFileList( 48 ); };
	afx_msg void OnFileList_49()  {  OnFileList( 49 ); };
	afx_msg void OnFileList_50()  {  OnFileList( 50 ); };
	afx_msg void OnFileList_51()  {  OnFileList( 51 ); };
	afx_msg void OnFileList_52()  {  OnFileList( 52 ); };
	afx_msg void OnFileList_53()  {  OnFileList( 53 ); };
	afx_msg void OnFileList_54()  {  OnFileList( 54 ); };
	afx_msg void OnFileList_55()  {  OnFileList( 55 ); };
	afx_msg void OnFileList_56()  {  OnFileList( 56 ); };
	afx_msg void OnFileList_57()  {  OnFileList( 57 ); };
	afx_msg void OnFileList_58()  {  OnFileList( 58 ); };
	afx_msg void OnFileList_59()  {  OnFileList( 59 ); };
	afx_msg void OnFileList_60()  {  OnFileList( 60 ); };
	afx_msg void OnFileList_61()  {  OnFileList( 61 ); };
	afx_msg void OnFileList_62()  {  OnFileList( 62 ); };
	afx_msg void OnFileList_63()  {  OnFileList( 63 ); };
	afx_msg void OnFileList_64()  {  OnFileList( 64 ); };
	afx_msg void OnFileList_65()  {  OnFileList( 65 ); };
	afx_msg void OnFileList_66()  {  OnFileList( 66 ); };
	afx_msg void OnFileList_67()  {  OnFileList( 67 ); };
	afx_msg void OnFileList_68()  {  OnFileList( 68 ); };
	afx_msg void OnFileList_69()  {  OnFileList( 69 ); };
	afx_msg void OnFileList_70()  {  OnFileList( 70 ); };
	afx_msg void OnFileList_71()  {  OnFileList( 71 ); };
	afx_msg void OnFileList_72()  {  OnFileList( 72 ); };
	afx_msg void OnFileList_73()  {  OnFileList( 73 ); };
	afx_msg void OnFileList_74()  {  OnFileList( 74 ); };
	afx_msg void OnFileList_75()  {  OnFileList( 75 ); };
	afx_msg void OnFileList_76()  {  OnFileList( 76 ); };
	afx_msg void OnFileList_77()  {  OnFileList( 77 ); };
	afx_msg void OnFileList_78()  {  OnFileList( 78 ); };
	afx_msg void OnFileList_79()  {  OnFileList( 79 ); };
	afx_msg void OnFileList_80()  {  OnFileList( 80 ); };
	afx_msg void OnFileList_81()  {  OnFileList( 81 ); };
	afx_msg void OnFileList_82()  {  OnFileList( 82 ); };
	afx_msg void OnFileList_83()  {  OnFileList( 83 ); };
	afx_msg void OnFileList_84()  {  OnFileList( 84 ); };
	afx_msg void OnFileList_85()  {  OnFileList( 85 ); };
	afx_msg void OnFileList_86()  {  OnFileList( 86 ); };
	afx_msg void OnFileList_87()  {  OnFileList( 87 ); };
	afx_msg void OnFileList_88()  {  OnFileList( 88 ); };
	afx_msg void OnFileList_89()  {  OnFileList( 89 ); };
	afx_msg void OnFileList_90()  {  OnFileList( 90 ); };
	afx_msg void OnFileList_91()  {  OnFileList( 91 ); };
	afx_msg void OnFileList_92()  {  OnFileList( 92 ); };
	afx_msg void OnFileList_93()  {  OnFileList( 93 ); };
	afx_msg void OnFileList_94()  {  OnFileList( 94 ); };
	afx_msg void OnFileList_95()  {  OnFileList( 95 ); };
	afx_msg void OnFileList_96()  {  OnFileList( 96 ); };
	afx_msg void OnFileList_97()  {  OnFileList( 97 ); };
	afx_msg void OnFileList_98()  {  OnFileList( 98 ); };
	afx_msg void OnFileList_99()  {  OnFileList( 99 ); };
	afx_msg void OnFileList_100()	{  OnFileList( 100 ); };
	afx_msg void OnFileList_101() {  OnFileList( 101 ); };
	afx_msg void OnFileList_102() {  OnFileList( 102 ); };
	afx_msg void OnFileList_103() {  OnFileList( 103 ); };
	afx_msg void OnFileList_104() {  OnFileList( 104 ); };
	afx_msg void OnFileList_105() {  OnFileList( 105 ); };
	afx_msg void OnFileList_106() {  OnFileList( 106 ); };
	afx_msg void OnFileList_107() {  OnFileList( 107 ); };
	afx_msg void OnFileList_108() {  OnFileList( 108 ); };
	afx_msg void OnFileList_109() {  OnFileList( 109 ); };
	afx_msg void OnFileList_110() {  OnFileList( 110 ); };
	afx_msg void OnFileList_111() {  OnFileList( 111 ); };
	afx_msg void OnFileList_112() {  OnFileList( 112 ); };
	afx_msg void OnFileList_113() {  OnFileList( 113 ); };
	afx_msg void OnFileList_114() {  OnFileList( 114 ); };
	afx_msg void OnFileList_115() {  OnFileList( 115 ); };
	afx_msg void OnFileList_116() {  OnFileList( 116 ); };
	afx_msg void OnFileList_117() {  OnFileList( 117 ); };
	afx_msg void OnFileList_118() {  OnFileList( 118 ); };
	afx_msg void OnFileList_119() {  OnFileList( 119 ); };
	afx_msg void OnFileList_120()	{  OnFileList( 120 ); };

	afx_msg void OnHelpFinder();
   afx_msg void OnUpdateQuickMenu(CCmdUI* pCmdUI);
   afx_msg void OnQuickItemHelp();
   afx_msg void OnQuickTopicHelp();
   afx_msg void OnQuickDefault();
   afx_msg void OnQuickComment();
   afx_msg void OnQuickCreate();
   afx_msg void OnQuickEdit();
   afx_msg void OnQuickDelete();
   afx_msg void OnQuickRefreshDefaults_Object();
   afx_msg void OnQuickRefreshDefaults_Model();
	afx_msg void OnToolbarRefreshDefaults();
	afx_msg void OnUpdateToolbarRefreshDefaults(CCmdUI* pCmdUI);
	afx_msg BOOL OnEditSwitchRuleset(UINT nID);
   afx_msg LRESULT OnEvaluateProposedRules(WPARAM uiDefaultAction, LPARAM lDBID);		// SAC 4/12/18 - first arg was: uiDontSwitchToLog
   afx_msg LRESULT OnDataModified(WPARAM wEval, LPARAM lDBID);
   afx_msg LRESULT OnUpdateTree(WPARAM wParam, LPARAM lDBIDModified);
   afx_msg LRESULT OnPopulateLibraryTree(WPARAM uiTreeMode, LPARAM);
   afx_msg LRESULT OnPerformAnalysis(WPARAM, LPARAM);
   afx_msg LRESULT OnPerformAPIAnalysisMsg(WPARAM, LPARAM);
   afx_msg LRESULT OnQuickMenu( WPARAM, LPARAM lParam );
   afx_msg LRESULT OnCheckCompat( WPARAM wParam, LPARAM lParam );
   afx_msg LRESULT OnSetStatusMessage( WPARAM wParam, LPARAM lParam );
   afx_msg LRESULT OnCreateBldgComponent( WPARAM wParam, LPARAM );
   afx_msg LRESULT OnButtonPressed( WPARAM wParam, LPARAM lParam );
   afx_msg LRESULT OnDlgCloseAction( WPARAM wParam, LPARAM lParam );    // SAC 08/19/22 (CUAC)
   afx_msg LRESULT OnLoadScreenData( WPARAM, LPARAM );
   afx_msg LRESULT OnBEMGridOpen(  WPARAM wClass, LPARAM l1Occur);   // SAC 3/15/18
   afx_msg LRESULT OnBEMGridClose( WPARAM wClass, LPARAM l1Occur);
   afx_msg LRESULT OnBEMGridUpdate(WPARAM wClass, LPARAM l1Occur);
   afx_msg LRESULT OnAutoSaveAs(WPARAM wID, LPARAM lParam );		// SAC 9/29/20

   BOOL DetailedFileOK( CString& sFileName, BOOL bProposed, BOOL bPromptUser );
   void UpdateViewOption(InterfaceMode eIntMode, CCmdUI* pCmdUI);
   void SwitchViewOption( InterfaceMode eIntMode );
	bool SetupFileListMenu( CMenu* pSubMenu );  // SAC 11/19/13 - added to enable dynamic file list access (compliance forms)
	int  AddFileListToMenu( CMenu* pPopupMenu, CString sFileListPath );
	void OnUpdateFileList( CCmdUI* pCmdUI, int i1FileListID );
	void OnFileList( int i1FileListID );
	void BatchProcessing( bool bOLDRules=false );		// SAC 4/2/14
	BOOL BatchUIDefaulting();		// SAC 11/10/17
	BOOL GenerateBatchInput( CString& sBatchDefsPathFile, CString& sBatchLogPathFile, CString& sBatchResultsPathFile  );		// SAC 11/10/17
   void CommunitySolarOptOut();		// SAC 03/28/23
	BOOL GetLogPathFile( CString& sLPF );
	BOOL LogFileExists();
	void PromptToDisplayPDFs( CString sCaption, CString sMsg, CString sBtn2File, CString sBtn2Label,
										CString sBtn3File, CString sBtn3Label, CString sBtn4File, CString sBtn4Label,
										CString sAllLabel, UINT uiIcon = MB_DEFBUTTON1 | MB_ICONQUESTION );
	void OnINISettings( int iDlgIDOffset, int iDlgWd, int iDlgHt, CString sDlgCaption, CString sINISection );
	int  RefreshCustomRulelistEnum( QString qsSelectedRulelist );
	void ProcessCustomRulelistFile();
	void EvalProposedRules( int iEvalOnlyClass, int iEvalOnlyObjIdx, CString* pDurationStr );
	void RefreshDefaultsButtonPressed( int iBEMClassID, CWnd* pButton );
   bool CUACAnalysisAvailable();		// SAC 01/20/23
   void LoadCUACOutputFilename( long lDBID_CUAC_RptOption, const char* pszFileExt, const char* pszRptType, QString& qsPathFile );   // SAC 01/20/23
   bool ViewCUACOuput( const char* pszOutPathFileProp, long lDBID_CUAC_RptOption, const char* pszFileExt, const char* pszRptType, const char* pszFileType );  // SAC 01/20/23

	void PreventSystemSleepDuringAnalysis();		// SAC 10/21/20 - setup timer to prevent system sleep during analysis
	void RestoreSystemSleepFollowingAnalysis();

	void FileSaveAsCore( CString sProjFile );		// SAC 9/30/20

	DECLARE_MESSAGE_MAP()
};


inline void CMainFrame::OnUpdateViewInput(CCmdUI* pCmdUI)    { UpdateViewOption( IM_INPUT, pCmdUI ); }
inline void CMainFrame::OnUpdateViewProposed(CCmdUI* pCmdUI) { UpdateViewOption( IM_PROPOSED, pCmdUI ); }
inline void CMainFrame::OnUpdateViewBudget(CCmdUI* pCmdUI)   { UpdateViewOption( IM_BUDGET, pCmdUI ); }

inline void CMainFrame::OnViewInput()     { SwitchViewOption( IM_INPUT    ); }
inline void CMainFrame::OnViewProposed()  { SwitchViewOption( IM_PROPOSED ); }
inline void CMainFrame::OnViewBudget()    { SwitchViewOption( IM_BUDGET   ); }


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__245352C9_5683_11D1_9002_0080C732DDC2__INCLUDED_)
