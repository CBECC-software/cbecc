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

#if !defined(AFX_BEMPROCCTRLRTF_H__8699285F_59BC_11D4_8B4D_00C04FA0DCC9__INCLUDED_)
#define AFX_BEMPROCCTRLRTF_H__8699285F_59BC_11D4_8B4D_00C04FA0DCC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BEMProcCtrlRTF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlRTF window

class CBEMProcCtrlRTF : public CRichEditCtrl
{
   DECLARE_DYNAMIC( CBEMProcCtrlRTF )
// Construction
public:
	CBEMProcCtrlRTF();

// Attributes
public:
	BOOL    m_bCalledCreate;
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   long    m_lDBID;
   int     m_iDBClass;
   int     m_iFont;
   CString m_sStatusMsg;

   CString m_sLoadedRTFFile;

// Operations
public:
	BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl,
						BOOL bTabbedDlgShift=FALSE, BOOL bScale=FALSE );

   afx_msg LRESULT OnDisplayData(WPARAM, LPARAM);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBEMProcCtrlRTF)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBEMProcCtrlRTF();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBEMProcCtrlRTF)
// 	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEMPROCCTRLRTF_H__8699285F_59BC_11D4_8B4D_00C04FA0DCC9__INCLUDED_)
