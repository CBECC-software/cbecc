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

#if !defined(AFX_DATETIMECTL_H__02EDF1B1_9392_11D2_B6D1_00104B6C110D__INCLUDED_)
#define AFX_DATETIMECTL_H__02EDF1B1_9392_11D2_B6D1_00104B6C110D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateTimeCtl.h : header file
//

enum DateTypes    // SAC 3/16/01
{
   DT_Full,
   DT_MoDa,
   DT_Num
};

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl window

class CDateTimeCtl : public CDateTimeCtrl
{
   DECLARE_DYNAMIC( CDateTimeCtl )

// Construction
public:
	CDateTimeCtl();

// Attributes
public:
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   
   int     m_uiCtrlType;
   int     m_iFont;
   
   long    m_lDBID;
   // SAC 3/3/99 - Added 0-based BEMProc class instance index
   int     m_iDBInstance;

   int     m_iDateType;  // SAC 3/16/01
   long    m_lYear;
   
   CString m_sStatusMsg;

   BOOL    m_bCalledNew;
   BOOL    m_bDroppedDown;

   BOOL    m_bEditable;
   CBEMCondition m_cEditableCondition;
   BOOL    m_bAllowEdits;

   long    m_lBaseDBID;       // SAC 2/7/02
   int     m_iDBIDArraySize;  // SAC 2/7/02

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeCtl)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDateTimeCtl();

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits=TRUE, long lDBIDOffset=0,
                BOOL bTabbedDlgShift=TRUE, BOOL calledNew=TRUE, BOOL scaleToSysFont=TRUE, BOOL scaleToScreenRes=FALSE,
                UINT uiTopicHelp = 0, UINT uiItemHelp = 0 );

   afx_msg LONG OnDisplayData(UINT, LONG);
   afx_msg LONG OnUpdateData( UINT, LONG);

   void SetValidRange();

   int RangeCheckViolation( BOOL bSilent=FALSE, CString* psMsg=NULL );

	// Generated message map functions
protected:
	//{{AFX_MSG(CDateTimeCtl)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnDateTimeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseUp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT  /*nFlags*/, CPoint /*point*/ );
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

   void DoQuickMenu();

   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMECTL_H__02EDF1B1_9392_11D2_B6D1_00104B6C110D__INCLUDED_)
