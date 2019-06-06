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

#if !defined(AFX_BEMPROCCTRLLIST_H__711335E0_3DDA_11D4_8B4A_00C04FA0DCC9__INCLUDED_)
#define AFX_BEMPROCCTRLLIST_H__711335E0_3DDA_11D4_8B4A_00C04FA0DCC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BEMProcCtrlList.h : header file
//

enum BEMProcCtrlListMode
{
   BEMPCLM_Active,
   BEMPCLM_ActiveChild,    // SAC 3/30/02
   BEMPCLM_NumModes
};

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlList window

class CBEMProcCtrlList : public CListCtrl
{
   DECLARE_DYNAMIC( CBEMProcCtrlList )
// Construction
public:
	CBEMProcCtrlList();

// Attributes
public:
	BOOL    m_bCalledCreate;
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   long    m_lDBID;
   int     m_iDBClass;
   int     m_iDBParentClass;  // SAC 3/30/02
   int     m_iFont;
//   long    m_lValue;
   CString m_sStatusMsg;

   BOOL    m_bUpdatingList;
   BOOL    m_bSettingHighlight;
   int     m_iNumColumns;

   int     m_iListCtrlMode;  // SAC 7/13/00 - added mode enum value for supporting modes other than Active Item

   int     m_iNavigationID;  // SAC 3/31/02 - added to facilitate double click processing that streamlines navigation

// Operations
public:

	BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBEMProcCtrlList)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

   afx_msg LRESULT OnDisplayData(WPARAM, LPARAM);

// Implementation
public:
	virtual ~CBEMProcCtrlList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBEMProcCtrlList)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEMPROCCTRLLIST_H__711335E0_3DDA_11D4_8B4A_00C04FA0DCC9__INCLUDED_)
