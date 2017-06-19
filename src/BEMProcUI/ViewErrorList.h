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

#if !defined(AFX_VIEWERRORLIST_H__235E17D9_AA80_4A2B_9C94_D79B3DCCB804__INCLUDED_)
#define AFX_VIEWERRORLIST_H__235E17D9_AA80_4A2B_9C94_D79B3DCCB804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewErrorList.h : header file
//

#include "resource.h"
                                            
class CEditCtl;
/////////////////////////////////////////////////////////////////////////////
// CViewErrorList view

class CViewErrorList : public CFormView 
{
protected:
	CViewErrorList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewErrorList)

// Attributes
public:
	//{{AFX_DATA(CViewErrorList)
	enum { IDD = IDD_BLANKFORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
   CArray< CEditCtl*, CEditCtl*> m_aWarningComments;
   int m_iParentCID;  // If this member is set to -1 then we do all of the 

   // CRect that contains the current size of the CEditCtls (in FontX() and FontY() converted units)
   CSize m_szEdit;

   // static variable that has the starting ID for all of the edit controls to be created
   static UINT editStartID;

// Operations
public:
   void SetCommentFocus(int iCtrlIdx);
   void ApplyDefault();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewErrorList)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   void DrawMessage( CDC* pDC, CString sText, CRect& outputRect, UINT nFormat = DT_SINGLELINE|DT_BOTTOM|DT_LEFT );

// Implementation
protected:
	virtual ~CViewErrorList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewErrorList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
   afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
   afx_msg void OnChangeComment(UINT nID);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERRORLIST_H__235E17D9_AA80_4A2B_9C94_D79B3DCCB804__INCLUDED_)
