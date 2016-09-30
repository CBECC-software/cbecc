// DlgErrorList.h: interface for the CDlgErrorList class.
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

#if !defined(AFX_DlgErrorList_H__83116F16_3334_4B5F_B4F3_C0FB4DBC936D__INCLUDED_)
#define AFX_DlgErrorList_H__83116F16_3334_4B5F_B4F3_C0FB4DBC936D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ResizableDialog/ResizableDialog.h"

class CViewErrorList;

class __declspec(dllexport) CDlgErrorList : public CResizableDialog  
{
public:
   CDlgErrorList( CPoint ptTopLeftOffset, CPoint ptBottomRightOffset,
                  CString sTitle, int iParentCID = -1, CRect* pRect = NULL, CWnd* pParent = NULL, const char* pszRangeLabel = NULL,
                  const char* pszRangePrompt = NULL, BOOL bAllowContinue = TRUE, int iDlgMode=0, UINT uiIconResourceID=0 );
	virtual ~CDlgErrorList();

// Members
   CRect m_wndRect;
   CString m_sSection;
   CString m_sKey;
	//{{AFX_DATA(CDlgErrorList)
	enum { IDD = IDD_ERRORLIST };
   BOOL  m_bCreateControls;
	//}}AFX_DATA

   BOOL     m_bContinue;
   CString  m_sRangeLabel;   // IDC_RANGE_LABEL
   CString  m_sRangePrompt;  // IDC_RANGE_PROMPT
   BOOL     m_bAllowContinue;
   CString  m_sDlgCaption;  
   int    m_iParentCID;

   int      m_iDialogMode;  // SAC 12/17/02 - Added to handle child control font selection

   UINT     m_uiIconResourceID;   // SAC 7/31/03 - Added Icon resource ID to enable display of program icon vs. generic Windows default

// View display members
   CRuntimeClass* m_pViewClass;
   CDocument* m_pDoc;
   CViewErrorList*   m_pView;
   CPoint m_ptTopLeftViewOffset;
   CPoint m_ptBottomRightViewOffset;

// Routines
public:
   void AllowContinue(BOOL bAllow = TRUE);
   BOOL AllWarningsCommented();
   void ClearDefaults();
// RW 11/26/02 New routines to determine if Warnings and/or Errors are being displayed in the dialog
   BOOL WarningsPresent();
   BOOL ErrorsPresent();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgErrorList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgErrorList)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();                                   
	//}}AFX_MSG

   afx_msg void OnOK();
   afx_msg void OnCancel();
   afx_msg void OnApplyDefault();

   void LoadWindowRect();
	void SaveWindowRect();
	void EnableSaveRestore(LPCTSTR pszSection, LPCTSTR pszEntry);	// section and entry in app's profile

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_DlgErrorList_H__83116F16_3334_4B5F_B4F3_C0FB4DBC936D__INCLUDED_)
