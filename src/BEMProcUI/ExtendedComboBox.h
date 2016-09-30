// ExtendedComboBox.h : header file
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

class CExtendedComboBox;

/////////////////////////////////////////////////////////////////////////////
// CListBoxInsideComboBox window

class CListBoxInsideComboBox : public CWnd
{
// Construction
public:
	CListBoxInsideComboBox();

// Attributes
public:
	CExtendedComboBox *m_Parent;
	void SetParent(CExtendedComboBox *);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxInsideComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxInsideComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxInsideComboBox)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox window

class CExtendedComboBox : public CComboBox
{
   DECLARE_DYNAMIC( CExtendedComboBox )
// Construction
public:
	CExtendedComboBox();
// ???   CComboBoxCtl() : m_bCreatedByClassName(FALSE) {}

// Attributes
public:

// SAC 6/1/01
   UINT     m_iItemHelpID;
   UINT     m_iTopicHelpID;
   
   int      m_iDataType;
   int      m_iFont;
   
   int      m_iClosedHt;
   int      m_iOriginalWidth;

	BOOL     m_bCreatedByClassName;
	BOOL     m_bCalledNew;

   long     m_lDBID;
   int      m_iDBInstance;  // SAC 3/3/99 - Added 0-based BEMProc class instance index

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

   long     m_lDBIDScreenIDArray;  // SAC 2/1/00 - Added additional DBID for new CM_SCREEN mode list population

   // SAC 3/9/01 - Added flag to cause quick return following update for other scenarios other than m_iComboMode == CM_SCREEN
   BOOL     m_bBailQuicklyFollowingUpdate;

   long     m_lDependentDBID;  // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
   long     m_lDependentVal;


   BOOL         m_bAllowSelectionOfDisabledItems;  // SAC 6/4/01
   long         m_lDBIDCompatItemArray;            // SAC 6/4/01
   int          m_iCompatCompInstance;             // SAC 6/4/01
   CDWordArray  m_dwaCompatItemArray;              // SAC 6/4/01
   long         m_lDBIDCompatError;                // SAC 6/4/01
   CString      m_sCompatRulelist;                 // SAC 6/4/01
   DWORD        m_dwCurSelData;                    // SAC 6/4/01
   long         m_lCompatModVal;                   // SAC 1/12/05 - Added to prevent "% 100" for arrays exceeding 100 elements


   void GenericCreate( BOOL bScaleToScreenRes, double dYScale, DWORD dwWinStyle, UINT uiCtrlID );

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits=TRUE, long lDBIDOffset=0, BOOL bTabbedDlgShift=TRUE,
                BOOL scaleToSysFont = TRUE, BOOL scaleToScreenRes = FALSE, long lDBIDScreenIDArray = 0,
                UINT uiTopicHelp = 0, UINT uiItemHelp = 0 );

	// default implementation uses LSB of item data; override to get other behaviour
	virtual BOOL IsItemEnabled(UINT) const;

protected:
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_strSavedText;	// saves text between OnSelendok and OnRealSelEndOK calls
	CListBoxInsideComboBox m_ListBox;

// Operations
public:
   BOOL ObjectTypeIsCompatible( int i1ClassID, int iObjIdx=-1, BEM_ObjType eObjType=BEMO_User );  // SAC 6/15/12 - revised to handle objects of multiple classes

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



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendedComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendedComboBox)
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	afx_msg void OnSelendok();
	//}}AFX_MSG

	LRESULT OnCtlColor(WPARAM,LPARAM lParam);
	afx_msg LRESULT OnRealSelEndOK(WPARAM,LPARAM);



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
//   afx_msg long OnGetTextColor(UINT, LONG);
   afx_msg long OnGetDBID(UINT, LONG);
   afx_msg long OnGetDBInstance(UINT, LONG);

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);



	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

