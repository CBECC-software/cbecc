// BPUICtl_BUTN.H    :  Declare the class for multi-font button.
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

#ifndef __BPUICtl_BUTN_H__
#define __BPUICtl_BUTN_H__


enum ButtonActionMode   // SAC 6/13/00
{
   BAC_None,
   BAC_CreateComponent,
   BAC_DeleteComponent,
   BAC_NumActionCodes
};


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
   // SAC 3/3/99 - Added 0-based BEMProc class instance index
   int     m_iDBInstance;

// SAC 8/4/02 - Added new DBID & Instance to support referenced components (lDBID2)
   long     m_lDBID2;
   long     m_lUseDBID;
   int      m_iUseDBInstance;
   
   long    m_lNavOrVal;
   WORD    m_wSecNavID;  // SAC 6/22/00 - added to enable more flexible pushbutton processing
   CString m_sStatusMsg;

   BOOL    m_bPressed;
   BOOL    m_bCalledNew;

   BOOL    m_bScaleFontToScreenRes;

   BOOL    m_bEditable;
   BOOL    m_bAllowEdits;
   CBEMCondition m_cEditableCondition;

   BOOL    m_bUpdatingData;  // SAC 2/5/99

   int     m_iActionCode;  // SAC 6/13/00

protected:
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
// TO DO ??
//   CMainFrame* GetMainFrame();

   CButtonCtl() : m_bCreatedByClassName(FALSE) {}

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits=TRUE, long lDBIDOffset=0,
                BOOL bTabbedDlgShift=TRUE, BOOL calledNew=TRUE, BOOL scaleToSysFont=TRUE, BOOL scaleToScreenRes=FALSE,
                UINT uiTopicHelp = 0, UINT uiItemHelp = 0 );
   BOOL Create( const char FAR* lpCaption, DWORD dwStyle, const RECT& rect,
                CWnd* pParentWnd, UINT nID, UINT uiCtrlType, int iFont, 
                const char FAR* lpMsg, long lDBID, BOOL calledNew, BOOL scaleToSysFont, BOOL scaleToScreenRes, 
                long lNavOrValue = -1, int iDBInstance=-1); 

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

   afx_msg LRESULT OnDisplayData(WPARAM, LPARAM);

   void SetInitialState();
   BOOL ButtonSelected();

   void CreateComponent();  // SAC 6/13/00
   void DeleteComponent();  // SAC 6/13/00

protected:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// SAC 8/4/02 - Added to support referenced components (lDBID2)
   void ResolveUseDBValues();

//   afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );

   // override to catch enter key as a button selection
   afx_msg UINT OnGetDlgCode();
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyUp(  UINT nChar, UINT nRepCnt, UINT nFlags);
   void ResetFocus( BOOL prev );

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

   afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
   afx_msg void OnLButtonUp( UINT nFlags, CPoint point );

    virtual void PostNcDestroy();

   afx_msg LRESULT OnGetDBID(WPARAM, LPARAM);
   afx_msg LRESULT OnGetDBInstance(WPARAM, LPARAM);

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

   DECLARE_MESSAGE_MAP()
};

// TO DO ??
//inline CMainFrame* CButtonCtl::GetMainFrame()
//{ return (CMainFrame*)GetParentFrame(); };

    
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __BPUICtl_BUTN_H__
