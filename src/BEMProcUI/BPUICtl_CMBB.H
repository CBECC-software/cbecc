// BPUICtl_CMBB.H    :  Declare the class for the RER combobox control.
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

#ifndef __BPUICtl_CMBB_H__
#define __BPUICtl_CMBB_H__


enum ComboMode
{
   CM_ACTIVE,
   CM_PARENT,
   CM_OBJECT,
   CM_SYMBOL,
   CM_SCREEN,
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
   // SAC 3/3/99 - Added 0-based BEMProc class instance index
   int      m_iDBInstance;

// SAC 8/1/02 - Added new DBID & Instance to support referenced components (lDBID2)
   long     m_lDBID2;
   long     m_lUseDBID;
   int      m_iUseDBInstance;

	CArray<int, int>		m_iaObjCompID;		// SAC 6/15/12 - re-vamped object referencing and component creation stuff to handle properties that can reference mulitple object types
	CArray<long, long>	m_laObjTypeDBID; 
	CArray<long, long>	m_laObjTypeValue;
   
   int      m_iComboMode;
   int      m_iCurObjIdx;

   CString  m_sStatusMsg;

   BOOL     m_bNone;

   BOOL     m_bUnused;
   BOOL     m_bEditable;
   BOOL     m_bAllowEdits;
   CBEMCondition m_cEditableCondition;

   // SAC 2/1/00 - Added additional DBID for new CM_SCREEN mode list population
   long     m_lDBIDScreenIDArray;

   // SAC 3/9/01 - Added flag to cause quick return following update for other scenarios other than m_iComboMode == CM_SCREEN
   BOOL     m_bBailQuicklyFollowingUpdate;

   // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
   long     m_lDependentDBID;
   long     m_lDependentVal;

	BOOL m_bAutoComplete;  // SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

   DWORD    m_dwListOptionFlag;  // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options

protected:
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
// TO DO ??
//   CMainFrame* GetMainFrame();

   CComboBoxCtl() : m_bCreatedByClassName(FALSE) {}

	virtual BOOL PreTranslateMessage(MSG* pMsg);  // SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

   void GenericCreate( BOOL bScaleToScreenRes, double dYScale, DWORD dwWinStyle,
                       UINT uiCtrlID );

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits=TRUE, long lDBIDOffset=0, BOOL bTabbedDlgShift=TRUE,
                BOOL scaleToSysFont = TRUE, BOOL scaleToScreenRes = FALSE, long lDBIDScreenIDArray = 0,
                UINT uiTopicHelp = 0, UINT uiItemHelp = 0 );
   BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                int iFont, int iClosedHt, const char FAR* lpMsg, 
                long lDBID, int iDT = -1, BOOL scaleToSysFont = TRUE, BOOL scaleToScreenRes = FALSE,
                UINT uiIHelpID=0, UINT uiTHelpID=0, long lObjTypeDBID=0, long lObjTypeValue=0,
                int iDBInstance=-1 );

   BOOL ObjectTypeIsCompatible( int i1ClassID, int iObjIdx=-1, BEM_ObjType eObjType=BEMO_User );  // SAC 6/15/12 - revised to handle objects of multiple classes
	BOOL CompatibleLibraryObjectExists( int i1ClassID );  // SAC 9/19/13 - added to determine whether library import is an option for this object assignment

   int CalcMaxStringWidth();
   int ResizeToFitContent( int nDropDownHeight=0 );

   BOOL LoadStrings();
   void LoadObjectNames( int i1ClassID, BOOL bLoadAll );
   // SAC 2/1/00 - New CM_SCREEN mode stuff
   void LoadScreenStrings();

   afx_msg LONG OnDisplayData(UINT, LONG);
   afx_msg LONG OnUpdateData( UINT, LONG);
   afx_msg void OnKillFocus( CWnd* pNewWnd );
   afx_msg void OnSetFocus(  CWnd* pOldWnd );

protected:
	virtual void PostNcDestroy();

// SAC 8/1/02 - Added to support referenced components (lDBID2)
   void ResolveUseDBValues();

   // Perform automatic list display or selection
   void ResetFocus( BOOL prev );
   afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditUpdate();  // SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim
   // Alt-F1 -or- Rt Mouse Click -> Quick Menu stuff
   afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
   afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
   void DoQuickMenu();
   BOOL UserSelectedNewRuleset();

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	afx_msg void OnSelchange();

   afx_msg long OnGetDataStatus(UINT, LONG);
//   afx_msg long OnGetTextColor(UINT, LONG);
   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

   DECLARE_MESSAGE_MAP()
};

// TO DO ??
//inline CMainFrame* CComboBoxCtl::GetMainFrame()
//{ return (CMainFrame*)GetParentFrame(); };
	
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __BPUICtl_CMBB_H__
