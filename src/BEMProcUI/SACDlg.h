// SACDlg.h : header file
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

#if !defined(AFX_SACDLG_H__0DCDBD41_A46E_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_SACDLG_H__0DCDBD41_A46E_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BEMProcCtrlBtnST.h"  // SAC 12/18/02

// resource definitions corresponding to bitmaps for graphical help/prev/next/done buttons
#define IDB_EQ_HELP32     580
#define IDB_EQ_HELP32G    581
#define IDB_EQ_PREV32     582
#define IDB_EQ_PREV32G    583
#define IDB_EQ_NEXT32     584
#define IDB_EQ_NEXT32G    585
#define IDB_EQ_STAR32     586
#define IDB_EQ_STAR32G    587
#define IDB_EQ_CANC32     588
#define IDB_EQ_CANC32G    589


/////////////////////////////////////////////////////////////////////////////
// CSACDlg dialog

struct CBEMPUIPage;

class __declspec(dllexport) CSACDlg : public CDialog
{
   DECLARE_DYNAMIC( CSACDlg )
// Construction
public:
	CSACDlg( CWnd* pParent = NULL, int iBEMCID_Wizard=0, long lDBID_ScreenIdx=0,
                  long lDBID_ScreenID=0, long lDBID_PrevScreenID=0, long lDBID_NextScreenID=0,
                  long lDBID_EnableFinish=0, const char* pszMidProcRulelist=NULL,
                  const char* pszPostProcRulelist=NULL, const char* pszDialogCaption=NULL,
                  int iBaseHt=400, int iBaseWd=620, int iBaseMarg=10,
                  UINT uiIconResourceID=0, BOOL bEnableToolTips=TRUE,
                  BOOL bShowPrevNextButtons=TRUE, int iSACWizDlgMode=0,
                  long lDBID_CtrlDBIDOffset=0, const char* pszFinishButtonText=NULL,
                  long* plCheckCharDBIDs=NULL, int iNumCheckCharDBIDs=0,
                  long lDBID_ScreenIDArray=0, BOOL bPostHelpMessageToParent=FALSE,
                  BOOL bIncludeCompParamStrInToolTip=FALSE, BOOL bIncludeStatusStrInToolTip=TRUE,
                  BOOL bUsePageHelpIDForCtrlTopicHelp=FALSE, int iHelpIDOffset=100000,
                  long lDBID_DialogHeight=0, BOOL bBypassChecksOnCancel=FALSE, BOOL bEnableCancelBtn=FALSE,
                  BOOL bGraphicalButtons=FALSE, int iFinishBtnWd=60, BOOL bIncludeLongCompParamStrInToolTip=FALSE );

// Dialog Data
	//{{AFX_DATA(CSACDlg)
	enum { IDD = 107 };  //IDD_SACDLG };
	CButton	m_bWizardFrame;
	//}}AFX_DATA

   BOOL    m_bInitializeDialog;

   CString m_sCaption;

   UINT m_uiIconResourceID;

   BOOL m_bEnableToolTips;

   int  m_iDialogMode;  // enum SACWizDlgMode

   // location & dimension variables
   int m_iBaseWidth;
   int m_iBaseHeight;
   int m_iBaseMargin;
   int m_iDlgWidth;
   int m_iDlgHeight;
   int m_iDlgMargin;
   int m_iFrmWidth;
   int m_iFrmHeight;
   int m_iFrmBottom;
   int m_iLeftButtonX;

   // BEMProc IDs
   int  m_iBEMCID_Wizard;
   long m_lDBID_ScreenIdx;
   long m_lDBID_ScreenID;
   long m_lDBID_PrevScreenID;
   long m_lDBID_NextScreenID;
   long m_lDBID_EnableFinish;

   long m_lDBID_CtrlDBIDOffset;   // SAC 2/25/99
   long m_lCtrlDBIDOffset;        // SAC 2/25/99

   long m_lDBID_ScreenIDArray;    // SAC 1/31/00

   // Rules Processing Rulelist Names
   CString m_sMidProcRulelist;
   CString m_sPostProcRulelist;

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   long    m_lContextHelpID;

   // SAC 2/12/99 - added for PNNL to enable Prev/Next button to be hidden
   BOOL    m_bShowPrevNextButtons;

   CString m_sFinishButtonText;   // SAC 2/25/99

   long* m_plCheckCharDBIDs;   // SAC 3/8/99 - added to enable edit control filename entry character checking
   int   m_iNumCheckCharDBIDs;

   BOOL  m_bPostHelpMessageToParent;   // SAC 2/7/00

   BOOL  m_bIncludeCompParamStrInToolTip;   // SAC 6/3/00
   BOOL  m_bIncludeLongCompParamStrInToolTip;   // SAC 8/13/13
   BOOL  m_bIncludeStatusStrInToolTip;   // SAC 9/2/00

   BOOL  m_bUsePageIDForTopicHelp;  // SAC 9/4/00
   int   m_iHelpIDOffset;   // SAC 9/4/00

   long  m_lDBID_DialogHeight;  // SAC 2/10/01
   int   m_iMaxHeight;

   BOOL  m_bBypassChecksOnCancel;  // SAC 6/11/01
   BOOL  m_bEnableCancelBtn;       // SAC 6/12/01

   BOOL  m_bGraphicalButtons;      // SAC 10/27/02
   int   m_iFinishBtnWd;
   CBEMProcCtrlBtnST  m_btnHelp;
   CBEMProcCtrlBtnST  m_btnPrev;
   CBEMProcCtrlBtnST  m_btnNext;
   CBEMProcCtrlBtnST  m_btnOK;
   CBEMProcCtrlBtnST  m_btnCancel;

   BOOL CheckData( CString& sMsg, CArray<long,long>* plErrDBIDs, CArray<long,long>* plWarnDBIDs );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSACDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// for command hit testing (used for automatic tooltips)
// TO DO
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

// Implementation
protected:

   int      m_iCurrentScreenID;
   CBEMPUIPage* m_pTDPage;
   CString  m_sToolStr;

   BOOL CheckEditCtrlCharacters( long lDBID );   // SAC 3/8/99 - added to enable edit control filename entry character checking

   long GetCurrentScreenID( BOOL bVerifyIDInArray );
   void CreateUIControls( BOOL bResetEntireScreen, long lFocusDBID=0 );
   void DeleteUIControls();
   void EraseControlArea();
   void PaintScreenStuff( BOOL bUpdateLabelsOnly=FALSE, BOOL bCallDisplayMods=TRUE );
//   BOOL ToggleControlIfNecessary( CBEMPUIControl* pCtrl, BOOL bEraseLabels );
   BOOL ToggleControlIfNecessary( void* pVoidCtrl, BOOL bEraseLabels );

// TO DO
   BOOL OnToolTipNotify( UINT id, NMHDR* pNMHDR, LRESULT* pResult );

   afx_msg LONG DisplayMods( UINT, LONG );
   BOOL EditControlValuesInRange( int iUserAction );
   BOOL OKToExit();
// RW 11/26/02 - Added reference parameters to determine if any errors or warnings were discovered via the rules based checking
   BOOL RuleBasedErrorCheck(CString& sErrMsg, CWnd* &pFocusCtrl, BOOL& bErrorsFound, BOOL& bWarningsFound);
// RW 09/23/02 - Added this routine to enable the adding of Warning class objects
   void AddWarningObject( long lCtrlDBID, CString sMsg, long lRangeVal );
   void RemoveNonCurrentWarnings();
   void ResetWarningCurrentFlag();

   int  GetScreenID( BOOL bPrevious, BOOL bSetBEMData );
   void ActivateButtons();
   void EvaluateRules(UINT uiList=0);

// SAC 2/10/01 - added this function to handle dynamic (ruleset-defined) dialog height resetting
   void ResetHeight( BOOL bRePaint=TRUE );

	// Generated message map functions
	//{{AFX_MSG(CSACDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPreviousScreen();
	afx_msg void OnWizardHelp();
	afx_msg void OnFinishWizard();
	afx_msg void OnCancelWizard();
	afx_msg void OnNextScreen();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   afx_msg LONG OnQMRestoreDefault( UINT uiDBInstP1, LONG lDBID );

   afx_msg LONG OnDataModified( UINT wEval, LONG lDBID );

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg LONG OnSetContextHelpID( WPARAM wHelpID, LPARAM );
   afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);

#ifdef _INC_SPREAD
	afx_msg LRESULT OnSpreadTextTipFetch(WPARAM wParam, LPARAM lParam);
   afx_msg LONG OnQMDeleteRow( UINT uiDBInstP1, LONG lDBID );
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SACDLG_H__0DCDBD41_A46E_11D1_9002_0080C732DDC2__INCLUDED_)
