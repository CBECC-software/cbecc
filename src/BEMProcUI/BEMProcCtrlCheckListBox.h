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

#if !defined(AFX_BEMPROCCTRLCHECKLISTBOX_H__BF8E1EC2_833B_11D2_8BE7_A813DF000000__INCLUDED_)
#define AFX_BEMPROCCTRLCHECKLISTBOX_H__BF8E1EC2_833B_11D2_8BE7_A813DF000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BEMProcCtrlCheckListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlCheckListBox

class CBEMProcCtrlCheckListBox : public CCheckListBox
{
   DECLARE_DYNAMIC( CBEMProcCtrlCheckListBox )
// Construction
public:
	CBEMProcCtrlCheckListBox();

// Attributes
public:
	BOOL    m_bCalledCreate;
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   long    m_lDBID;
   int     m_iDBClass;
   int     m_iFont;
   CString m_sStatusMsg;

   BOOL    m_bUpdatingList;
   BOOL    m_bSettingHighlight;

   int     m_iMarginX;
   int     m_iMarginY;

   long    m_lRTFCtrlID;  // SAC 7/15/00
   CString m_sRuleListName;  // SAc 7/15/00

   // SAC 7/14/00 - Some extra stuff specific to the "Measures" implementation
   long  m_lMsrIsAvailableDBID;
   long  m_lMsrIsCheckedDBID;
   long  m_lMsrOrderDBID;
   int   m_iTotNumMeasures;

// Operations
public:
	BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl );

   void AdjustTextRect( RECT* pRect );

//   virtual CRect OnGetCheckPosition( CRect rectItem, CRect rectCheckBox );

	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

   void SwitchActive();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBEMProcCtrlCheckListBox)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

   afx_msg LONG OnDisplayData(UINT, LONG);

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CBEMProcCtrlCheckListBox)
	afx_msg void OnSelChange();
	afx_msg void OnSetFocus();
	afx_msg void OnCheckChange();
	//}}AFX_MSG

   // SAC 10/16/02 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEMPROCCTRLCHECKLISTBOX_H__BF8E1EC2_833B_11D2_8BE7_A813DF000000__INCLUDED_)
