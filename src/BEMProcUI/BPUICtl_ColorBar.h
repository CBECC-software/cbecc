// BPUICtl_ColorBar.H    :  Declare the class for color bar control.
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
/*  (c) Copyright 2002, SAC Software Solutions, Inc.                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#ifndef __BPUICtl_COLORBAR_H__
#define __BPUICtl_COLORBAR_H__


#define  CCB_LMOUSE_DOWN  0
#define  CCB_LMOUSE_UP    1
#define  CCB_MOUSE_MOVE   2


/////////////////////////////////////////////////////////////////////////////
// CColorBarCtl

class CColorBarCtl : public CWnd
{
   DECLARE_DYNAMIC( CColorBarCtl )
public:

   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;

   long    m_lDBID;
   int     m_iDataType;

   int     m_iMode;

   CString m_sStatusMsg;

   DWORD   m_dwBckgrndColor;

   BOOL    m_bCalledNew;

   int     m_iNumSections;     // SAC 5/1/02 - Added ColorBar-specific properties
   int     m_iSectionWidth;

   int     m_iMouseMoveDelta;  // SAC 5/2/02 - mods to facilitate click-drag processing
   BOOL    m_bMouseDown;
   int     m_iLastMouseX;
   int     m_iLastSectionSet;

protected:

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
   CColorBarCtl();
   ~CColorBarCtl();

   void SizeAndPos( int iX, int iY, int iWd, int iHt, int winHt, int winWd, int iMode,
                    BOOL scaleToSysFont, BOOL scaleToScreenRes, CSize& size, CPoint& pos );

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl,
                int winHt, int winWd, DWORD dwBckColor, BOOL bTabbedDlgShift=TRUE,
                BOOL scaleToSysFont=TRUE, BOOL scaleToScreenRes=FALSE,
                BOOL bUseVerdanaFonts=FALSE, UINT uiTopicHelp = 0, UINT uiItemHelp = 0 );

//   CPoint    GetViewportOrigin(CRect winRect, OLDRECT objRect);
   
protected:
   afx_msg LRESULT OnDisplayData(WPARAM, LPARAM);

   afx_msg void OnPaint();

   afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
   afx_msg void OnLButtonUp(   UINT nFlags, CPoint point );
   afx_msg void OnMouseMove(   UINT nFlags, CPoint point );
   afx_msg void OnTimer( UINT_PTR nIDEvent );
   afx_msg void OnRButtonDown( UINT nFlags, CPoint point );  // SAC 12/9/02

	virtual void PostNcDestroy();

   void DoQuickMenu();  // SAC 12/9/02

   void ProcessMouseAction( UINT& nFlags, CPoint& point, int iClickType );
   void PostProcessMouseMods();

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __BPUICtl_COLORBAR_H__

