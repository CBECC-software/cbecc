// BEMProcDialog.h : header file
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

#if !defined(AFX_SACBEMProcDIALOG_H__39AEB322_7BE6_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_SACBEMProcDIALOG_H__39AEB322_7BE6_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BEMProcTabCtrl.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// This flag keeps track of whether or not the user is currently in the process
// if editing data via the tabbed dialogs - in which case we don't want to reset
// BEM active objects.
//extern int eiCBEMProcDialogInstances;
int  __declspec(dllexport) __cdecl BEMPUIX_NumBEMProcDialogInstances();

void __declspec(dllexport) __cdecl BEMPUIX_SetRulesetDBIDs( long* plRulesetDBIDs, int iNumRulesetDBIDs );

int __declspec(dllexport) __cdecl BEMPUIX_DoBEMProcDialog(
	int iBEMClass=0, int iUIMode=0, BOOL bDisplayAllUIControls=FALSE, BOOL bAllowEdits=TRUE,
	CWnd* pParent = NULL, int iDlgMode=0, int iTabCtrlWd=600, int iTabCtrlHt=350, int iMaxTabs=99,
	const char* pszCaptionText=NULL, const char* pszCloseBtnText=NULL,
	DWORD* dwaNonEditableDBIDs=NULL, int iNumNonEditableDBIDs=0,
	const char* pszExitingRulelist=NULL, const char* pszDataModRulelist=NULL,
	BOOL bPostHelpMessageToParent=FALSE,
	BOOL bIncludeCompParamStrInToolTip=FALSE, BOOL bIncludeStatusStrInToolTip=TRUE, BOOL bIncludeLongCompParamStrInToolTip=FALSE,
	BOOL bShowRefreshDefaultsBtn=FALSE );		// SAC 4/18/18

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CSACBEMProcDialog dialog

struct CBEMPUIPage;
class CBEMProcCtrlIconBtn;

class __declspec(dllexport) CSACBEMProcDialog : public CDialog
{
// Construction
public:
	CSACBEMProcDialog(int iBEMClass=0, int iUIMode=0, BOOL bDisplayAllUIControls=FALSE, BOOL bAllowEdits=TRUE,
                 CWnd* pParent = NULL, int iDlgMode=0, int iTabCtrlWd=600, int iTabCtrlHt=350, int iMaxTabs=99,
                 const char* pszCaptionText=NULL, const char* pszCloseBtnText=NULL,
                 DWORD* dwaNonEditableDBIDs=NULL, int iNumNonEditableDBIDs=0,   // SAC 9/10/00 - added non-editable DBID stuff
                 const char* pszExitingRulelist=NULL, const char* pszDataModRulelist=NULL,  // SAC 6/17/01
                 BOOL bPostHelpMessageToParent=FALSE,  // SAC 7/6/01
                 BOOL bIncludeCompParamStrInToolTip=FALSE, BOOL bIncludeStatusStrInToolTip=TRUE, BOOL bIncludeLongCompParamStrInToolTip=FALSE,    // SAC 1/19/12
                 BOOL bShowRefreshDefaultsBtn=FALSE );	// SAC 4/18/18

// Dialog Data
	//{{AFX_DATA(CSACBEMProcDialog)
	enum { IDD = 105 };  // IDD_SACBEMProcDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

   int         m_iBEMClass;
   int         m_iUIMode;
   BOOL        m_bDisplayAllUIControls;
   BOOL        m_bAllowEdits;

   CSACBEMProcTabCtrl m_BEMProcTabCtrl;

   CBEMPUIPage*  m_pTDPage;

   CString     m_sToolStr;

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   long        m_lContextHelpID;

   CWordArray  m_waValidPageIdxs;  // SAC 6/29/00

   int  m_iDialogMode;  // based on enum SACWizDlgMode - SAC 8/7/00

   int  m_iTabCtrlWd;   // SAC 8/22/00
   int  m_iTabCtrlHt;   // SAC 8/22/00
   int  m_iMaxTabs;     // SAC 8/22/00
   CString  m_sCaptionString;   // SAC 8/22/00
   CString  m_sCloseBtnString;  // SAC 8/22/00

   CDWordArray  m_dwaNonEditableDBIDs;  // SAC 9/10/00

   CString  m_sExitingRulelist;  // SAC 6/17/01
   CString  m_sDataModRulelist;

   BOOL  m_bPostHelpMessageToParent;   // SAC 7/6/01

   BOOL  m_bIncludeCompParamStrInToolTip;   // SAC 1/19/12
   BOOL  m_bIncludeLongCompParamStrInToolTip;   // SAC 8/13/13
   BOOL  m_bIncludeStatusStrInToolTip;   // SAC 1/19/12

	BOOL  m_bShowRefreshDefaultsBtn;		// SAC 4/18/18
	CBEMProcCtrlIconBtn* m_pRefreshDefaultsBtn;

   void DeleteControls();
   BOOL InitControls();

   void PaintTabCtrlStuff( BOOL bUpdateLabelsOnly=FALSE, BOOL bCallDisplayMods=TRUE, BOOL bPaintAllLabels=FALSE );	// SAC 10/16/17
//   BOOL ToggleControlIfNecessary( CBEMPUIControl* pCtrl, BOOL bEraseLabels );
   BOOL ToggleControlIfNecessary( void* pVoidCtrl, BOOL bEraseLabels );

   BOOL CheckData( CString& sMsg, CArray<long,long>* plErrDBIDs, CArray<long,long>* plWarnDBIDs );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSACBEMProcDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// for command hit testing (used for automatic tooltips)
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

// Implementation
protected:

   BOOL OnToolTipNotify( UINT id, NMHDR* pNMHDR, LRESULT* pResult );

   afx_msg LRESULT DisplayMods( WPARAM, LPARAM );

   BOOL RuleBasedErrorCheck();  // SAC 6/17/01

	// Generated message map functions
	//{{AFX_MSG(CSACBEMProcDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG

   afx_msg LRESULT OnQMRestoreDefault( WPARAM uiDBInstP1, LPARAM lDBID );
   afx_msg LRESULT OnDataModified( WPARAM wEval, LPARAM lDBID );

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg LRESULT OnSetContextHelpID( WPARAM wHelpID, LPARAM );
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SACBEMProcDIALOG_H__39AEB322_7BE6_11D1_9002_0080C732DDC2__INCLUDED_)
