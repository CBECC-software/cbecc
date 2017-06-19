// CTL_BUTN.H    :  Declare the class for multi-font button.
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

#ifndef __CTL_BUTN_H__
#define __CTL_BUTN_H__

#include "MainFrm.h"
// #include "Screens.h"
#include "CUIGlobl.h"

/////////////////////////////////////////////////////////////////////////////
// CButtonCtl

class CButtonCtl : public CButton
{
   DECLARE_DYNAMIC( CButtonCtl )
   
private:
    BOOL   m_bCreatedByClassName;
   
public:
   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;
   
   int     m_iDataType;
   int     m_uiCtrlType;
   int     m_iFont;
   
   long    m_lDBID;
   
   long    m_lNavOrVal;
   CString m_sStatusMsg;

   BOOL   m_bPressed;
   BOOL   m_bCalledNew;

   BOOL   m_bScaleFontToScreenRes;

   BOOL   m_bEditable;

protected:
//16    static WNDPROC pfnSuperWndProc;
//16    virtual WNDPROC* GetSuperWndProcAddr() {return &pfnSuperWndProc;}

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
   CMainFrame* GetMainFrame();

   CButtonCtl() : m_bCreatedByClassName(FALSE) {}

   BOOL Create( const char FAR* lpCaption, DWORD dwStyle, const RECT& rect,
                CWnd* pParentWnd, UINT nID, UINT uiCtrlType, int iFont, 
                const char FAR* lpMsg, long lDBID, BOOL calledNew, BOOL scaleToSysFont, BOOL scaleToScreenRes, 
                long lNavOrValue = -1); 

//16    // Member function to register a window class
//16    static BOOL RegisterMyClass();

   // Functions to catch quick-menu calls (rt mouse button or Alt-F1)
   afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
   afx_msg void OnSysKeyDown(  UINT nChar, UINT nRepCnt, UINT nFlags );

   afx_msg void OnKillFocus( CWnd* pNewWnd );
   afx_msg void OnSetFocus(  CWnd* pOldWnd );

   void DoQuickMenu();

   BOOL HasVerticalFont()
        {  return (m_iFont == FNT_VSMALL);  }

   BOOL IsPressed()
        {  return m_bPressed;  }
   void SetPressed( BOOL pressed )
        {  m_bPressed = pressed;   return;  }

//   virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

   void SetInitialState();
   BOOL ButtonSelected();

private:
//16    static LONG CALLBACK __export
//16    FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

protected:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

//   afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );

   // override to catch enter key as a button selection
   afx_msg UINT OnGetDlgCode();
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyUp(  UINT nChar, UINT nRepCnt, UINT nFlags);
   void ResetFocus( BOOL prev );

//	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

   afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
   afx_msg void OnLButtonUp( UINT nFlags, CPoint point );

    virtual void PostNcDestroy();

   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   DECLARE_MESSAGE_MAP()
};

inline CMainFrame* CButtonCtl::GetMainFrame()
{ return (CMainFrame*)GetParentFrame(); };

    
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __CTL_BUTN_H__
