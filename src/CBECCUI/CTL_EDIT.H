// CTL_EDIT.H    :  Declare the class for edit controls.
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#ifndef __CTL_EDIT_H__
#define __CTL_EDIT_H__


#define SEGMENT_SIZE 4096

/////////////////////////////////////////////////////////////////////////////
// CEditCtl

class CEditCtl : public CEdit
{
   DECLARE_DYNAMIC( CEditCtl )
private:
//16    HGLOBAL m_ghEditDS;

	BOOL    m_bCreatedByClassName;
	BOOL    m_bCalledCreate;

public:
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   
   long    m_lDBID;
   int     m_iDataType;

   int     m_iFont;
   int     m_iPrecOrLen;
   CString m_sStatusMsg;

   CString m_sCurrStr;
   BOOL    m_bChkChr;

   BOOL    m_bUnused;
   BOOL    m_bEditable;

// SAC 8/7/00 - added following m_bNameDBID stuff
   BOOL    m_bNameDBID;

protected:
//16	static WNDPROC pfnSuperWndProc;
//16	virtual WNDPROC* GetSuperWndProcAddr() {return &pfnSuperWndProc;}

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
   CMainFrame* GetMainFrame();

   CEditCtl() : m_bCreatedByClassName(FALSE) {}

// SAC 7/30/99 - added final bForceEditable argument to enable the parent to force the property to be editable
//               (necessary for displaying Primary Data dialogs)
   BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                int iFont, int iPrecOrLen, const char FAR* lpMsg, long lDBID, 
                int iDT = -1, UINT uiIHelpID=0, UINT uiTHelpID=0, BOOL chkChr=FALSE,
                BOOL bForceEditable=FALSE );
                
	// Member function to register a window class
//16 	static BOOL RegisterMyClass();

   afx_msg LONG OnDisplayData(UINT, LONG);
   afx_msg LONG OnUpdateData( UINT, LONG);

	CWnd* SetFocus();

   int RangeCheckViolation( BOOL bSilent=FALSE, CString* psMsg=NULL );

//16 private:
//16 	static LONG CALLBACK EXPORT
//16 	FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

protected:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

//16    virtual BOOL PreCreateWindow(CREATESTRUCT &cs);

	virtual void PostNcDestroy();

                                        // for character validation
   afx_msg void OnChar(       UINT nChar, UINT nRepCnt, UINT nFlags );
   afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

   afx_msg void OnRButtonDown(   UINT nFlags, CPoint point );

   afx_msg void OnKillFocus( CWnd* pNewWnd );
   afx_msg void OnSetFocus(  CWnd* pOldWnd );

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

   void DoQuickMenu();

   afx_msg long OnGetDataStatus(UINT, LONG);
   afx_msg long OnGetTextColor(UINT, LONG);
   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   DECLARE_MESSAGE_MAP()
};

inline CMainFrame* CEditCtl::GetMainFrame()
{ return (CMainFrame*)GetParentFrame(); };

	
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __CTL_EDIT_H__
