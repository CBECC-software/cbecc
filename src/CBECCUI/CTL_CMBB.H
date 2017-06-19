// CTL_CMBB.H    :  Declare the class for the RER combobox control.
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

#ifndef __CTL_CMBB_H__
#define __CTL_CMBB_H__


enum ComboMode
{
   CM_ACTIVE,
   CM_PARENT,
   CM_OBJECT,
   CM_SYMBOL,
   CM_OTHER,
   CM_NUM
};

/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl

class CComboBoxCtl : public CComboBox
{
   DECLARE_DYNAMIC( CComboBoxCtl )
public:
   UINT     m_iItemHelpID;
   UINT     m_iTopicHelpID;
   
   int      m_iDataType;
   int      m_iFont;
   
   int      m_iClosedHt;
   int      m_iOriginalWidth;

	BOOL     m_bCreatedByClassName;
	BOOL     m_bCalledNew;

   long     m_lDBID;

	CArray<int, int>		m_iaObjCompID;		// SAC 6/15/12 - re-vamped object referencing and component creation stuff to handle properties that can reference mulitple object types
	CArray<long, long>	m_laObjTypeDBID; 
	CArray<long, long>	m_laObjTypeValue;
   
   int      m_iComboMode;
   int      m_iCurObjIdx;

   CString  m_sStatusMsg;

   BOOL     m_bNone;

   BOOL     m_bUnused;
   BOOL     m_bEditable;

protected:
//16 	static WNDPROC pfnSuperWndProc;
//16 	virtual WNDPROC* GetSuperWndProcAddr() {return &pfnSuperWndProc;}

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
   CMainFrame* GetMainFrame();

   CComboBoxCtl() : m_bCreatedByClassName(FALSE) {}

   void GenericCreate( BOOL bScaleToScreenRes, double dYScale, DWORD dwWinStyle,
                       UINT uiCtrlID, BOOL bForceEditable );

// SAC 7/30/99 - added final bForceEditable argument to enable the parent to force the property to be editable
//               (necessary for displaying Primary Data dialogs)
   BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                int iFont, int iClosedHt, const char FAR* lpMsg, 
                long lDBID, int iDT = -1, BOOL scaleToSysFont = TRUE, BOOL scaleToScreenRes = FALSE,
                UINT uiIHelpID=0, UINT uiTHelpID=0, long lObjTypeDBID=0, long lObjTypeValue=0,
                BOOL bForceEditable=FALSE );

//16 	// Member function to register a window class
//16 	static BOOL RegisterMyClass();

   BOOL ObjectTypeIsCompatible( int i1ClassID, int iObjIdx=-1, BEM_ObjType eObjType=BEMO_User );  // SAC 6/15/12 - revised to handle objects of multiple classes
	BOOL CompatibleLibraryObjectExists( int i1ClassID );  // SAC 9/19/13 - added to determine whether library import is an option for this object assignment

   BOOL LoadStrings();
   void LoadObjectNames( int i1ClassID, BOOL bLoadAll );

   int CalcMaxStringWidth();
   int ResizeToFitContent( int nDropDownHeight=0 );

   afx_msg LONG OnDisplayData(UINT, LONG);
   afx_msg LONG OnUpdateData( UINT, LONG);
   afx_msg void OnKillFocus( CWnd* pNewWnd );
   afx_msg void OnSetFocus(  CWnd* pOldWnd );

private:
//16 	static LONG CALLBACK __export
//16 	FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

protected:
	virtual void PostNcDestroy();

   // Perform automatic list display or selection
   void ResetFocus( BOOL prev );
   afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   // Alt-F1 -or- Rt Mouse Click -> Quick Menu stuff
   afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
   afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
   void DoQuickMenu();
   BOOL UserSelectedNewRuleset();

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	afx_msg void OnSelchange();

   afx_msg long OnGetDataStatus(UINT, LONG);
   afx_msg long OnGetTextColor(UINT, LONG);
   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   DECLARE_MESSAGE_MAP()
};

inline CMainFrame* CComboBoxCtl::GetMainFrame()
{ return (CMainFrame*)GetParentFrame(); };
	
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __CTL_CMBB_H__
