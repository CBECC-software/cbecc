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

#if !defined(AFX_TREEBDB_H__C42D0E61_8C04_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_TREEBDB_H__C42D0E61_8C04_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeBDB.h : header file
//

#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"

// enum used to identify the various tree modes
enum TM_TreeModes
{
   TM_Project,
   TM_Architecture,
   TM_Lighting,
   TM_Mechanical,
   TM_NumModes,
};

enum TDC_DropCodes
{
   TDC_Child,
   TDC_Reference,
   TDC_ReverseRef,
   TDC_NumCodes
};

#define  MAX_DROP_CONNECTIONS  5

extern CString GenerateTempFileName();

/////////////////////////////////////////////////////////////////////////////
// CTreeBDB window

class CTreeBDB : public CTreeCtrl
{
// Construction
public:
	CTreeBDB();

// Attributes
public:
   int        m_iTreeMode;
   HTREEITEM  m_htiRootItem;
   BOOL       m_bProjectTree;

   int**       m_iapModes;   // siaModes[]  = { siaMode0,  siaMode1,  siaMode2,  siaMode3 };
   int***      m_iappModes;  // siapModes[] = { siapMode0, siapMode1, siapMode2, siapMode3 };
   int***      m_iappFolders;// siapFolders[] = { ...
   HTREEITEM*  m_hapModes;   // shaModes[] = { TVI_LAST, TVI_LAST, TVI_LAST, TVI_LAST };

   DWORD       m_dwMinValidRef;
   DWORD       m_dwMaxValidRef;

   BOOL        m_bTreeCurrent;
   BOOL        m_bDeletingBDBItems;
   long        m_lIgnoreNextExpansion;

   HTREEITEM   m_hitemPossiblyDrag;

   int         m_iOLEDragging;  // 0=>No, 1=>Left(move), 2=>Right(copy)

   BOOL        m_bDragCanCopy;
   CString     m_sDragCompString;
   HTREEITEM   m_hitemDrag;
   HTREEITEM   m_hitemDragParent;

   struct DATASOURCE {
      int      iBDBClass;
      int      iParentBDBClass;
   };
   DATASOURCE  m_dragInfo;

   int           m_iDropIdx;
   int           m_iDragDropIdx;
   int           m_iDragDropNumber;
   TDC_DropCodes m_eDragDropCode[  MAX_DROP_CONNECTIONS ];
   int           m_iDragDropClass[ MAX_DROP_CONNECTIONS ];
   long          m_lDragDropDBID[  MAX_DROP_CONNECTIONS ];

   HTREEITEM   m_hitemDrop;
   HTREEITEM   m_hitemLastBadDrop;
   CImageList  *m_pimagelist;

   CDWordArray m_dwaItemData;
   CDWordArray m_dwaItemDBIDs;
   CWordArray  m_waItemCodes;

	CStringArray 		saTreeFolderLabels;		// SAC 2/3/12 - added to establish relationship between tree folders & BEMProc classes
	CArray<int, int>	iaTreeFolderClassID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeBDB)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, BOOL bProjTree=TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
   void InitDragInfo();
   BEMObject* DoPasteNative( COleDataObject *pDataObject, int iBDBClass=0 );
	void DoPasteItem( HTREEITEM hItem, COleDataObject *pDataObject );
	void GetNativeClipboardData( HTREEITEM htiItem, BEMObject *, COleDataSource *pDataSource );
   BOOL SetDragInfo( COleDataObject* pDataObject );
   int  GetDragClassFromClipboard();
   BOOL OKToPaste( DWORD dwData );
	virtual ~CTreeBDB();

   // functions to manage lists of ItemData/DBID/Code information
   void ResetArrayData();
   void AddToArrayData( DWORD dwData, DWORD dwDBID, WORD wCode );
   void DeleteArrayData( DWORD dwData );
   BOOL ArrayDataMatch( DWORD dwData, DWORD dwDBID, WORD wCode );

   BOOL ClassIsCompatibleWithMode( int iBDBClassIdx );
	BOOL IsFolderClass( int iBDBClassIdx );   // SAC 12/29/11
	int  GetFolderClassFromTreeItem( HTREEITEM htiTreeItem );	// SAC 2/3/12 - added to establish relationship between tree folders & BEMProc classes

   void AddProjectComponent( BOOL bAddItem );
   HTREEITEM AddComponent( HTREEITEM hParent, int iBDBClass, int iObjOccur, int iSource, BEMObject* pObj,
                           long lDBID=0, TDC_DropCodes eCode=TDC_Child );
   void SetupTreeMode();
   void SetHighlight( int iBDBClassToHighlight=0 );
   void PopulateProjectTree( int iBDBClassToHighlight );
   void PopulateLibraryTree( int iBDBClassToHighlight );
   void PopulateBDBTree( int iTreeMode, int iBDBClassToHighlight=0, BOOL bOnlyIfRequired=FALSE );

   BOOL DeleteAllBDBItems();
   BOOL ItemIsExpanded( HTREEITEM hItem );
   BOOL DBIDInList( long lCheckDBID, long** plDBID );
   HTREEITEM BDBObjectToTreeItem( BEMObject* pObj );
   BEMObject* DataToBDBObject( DWORD dwData );

   void AddReverseReferencingChildren( HTREEITEM hParent, BEMObject* pParentObj,
                                       int i1ChildClass, long lChildDBID, int iChildSource );
   void AddAssignedChildren( HTREEITEM hParent, int iParClass, int iParObjIdx, int iParSrc, long** plBDID );

   BOOL OKToAddSpecialObjectToRoot( int i1Class, int i0ObjIdx );

   void CreateComponent( int iChildClassIdx );
   void ConvertComponent( int iConvertClassIdx );	// SAC 9/28/15

   void SetDragStatusMessage();
	void BeginDrag(NMHDR* pNMHDR, LRESULT* pResult, int iButton);
   void BeginOleDrag(NMHDR* pNMHDR, LRESULT* pResult, int iButton);
	void OnButtonUp( int iButton );
   BOOL IsCopying();
   void SetDropCompElement( TDC_DropCodes eCode, int iClass, long lDBID );
   void SetDropCompatibilityInfo();
   BOOL DropOK( HTREEITEM hitem );
   void DropItemBeingDragged( COleDataObject* pDataObject );
   BEMObject* CopyBDBComponent( BEMObject* pCopyObj, BEMObject* pParentObj=NULL );
   void SetNextPossibleDragItem();

   int  GetBitmapID( int iBDBClass, int iObjOccur=-1 );
   bool EnableViewFootprint( int iBDBClass, int iObjOccur=-1 );  // SAC 11/26/13

   HTREEITEM CheckChildrenForDataMatch( HTREEITEM hti, DWORD dwItemData );
   HTREEITEM GetItemFromData( DWORD dwItemData, BOOL bAllowRoot=TRUE );
   HTREEITEM GetHandleToCurrentlyActive( int iClass, BEMClass* pClass=NULL );
   void CheckAndUpdateTree( long lDBIDModified );

   void PresentQuickMenu( HTREEITEM htiSelItem=NULL );

	void ChildMove( bool bMoveUp=true );

	// Generated message map functions
protected:
	DROPEFFECT DragOverScroll( CWnd *pWnd, CPoint point );
	void DeleteDragImageList();
	static CLIPFORMAT g_cfPrivate;
   static CLIPFORMAT g_cfDatasource;

	//{{AFX_MSG(CTreeBDB)
	afx_msg void OnDestroy();
   afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBeginRDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnQuickEdit();
	afx_msg void OnQuickRename();
	afx_msg void OnQuickDelete();
	afx_msg void OnQuickExpCon();
	afx_msg void OnQuickCreate1();
	afx_msg void OnQuickCreate2();
	afx_msg void OnQuickCreate3();
	afx_msg void OnQuickCreate4();
	afx_msg void OnQuickCreate5();
	afx_msg void OnQuickCreate6();
	afx_msg void OnQuickCreate7();
	afx_msg void OnQuickCreate8();
	afx_msg void OnQuickCreate9();
	afx_msg void OnQuickCreate10();
	afx_msg void OnQuickCreate11();
	afx_msg void OnQuickCreate12();
	afx_msg void OnQuickCreate13();
	afx_msg void OnQuickCreate14();
	afx_msg void OnQuickCreate15();
	afx_msg void OnQuickCreate16();
	afx_msg void OnQuickCreate17();
	afx_msg void OnQuickCreate18();
	afx_msg void OnQuickCreate19();
	afx_msg void OnQuickCreate20();
	afx_msg void OnQuickMoveUp();
	afx_msg void OnQuickMoveDown();
	afx_msg void OnQuickConvert1();
	afx_msg void OnQuickConvert2();
	afx_msg void OnQuickConvert3();
	afx_msg void OnQuickConvert4();
	afx_msg void OnQuickConvert5();
	afx_msg void OnQuickConvert6();
	afx_msg void OnQuickConvert7();
	afx_msg void OnQuickConvert8();
	afx_msg void OnQuickConvert9();
	afx_msg void OnQuickConvert10();
	afx_msg void OnTVNSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNMReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTVNItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTVNItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnViewFootprint();
	//}}AFX_MSG
   afx_msg LONG OnEditTreeItem(UINT, LONG);

   // These are forwarded from the nested drop site
   virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
   virtual void OnDragLeave( CWnd* pWnd );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );

   // Nested class for the drop site for this tree, forwards all notifications
   // back to its tree
   class CDropTarget : public COleDropTarget {
      // Attributes
   public:
      CTreeBDB *m_pTree;
      // Overrides
   public:
      virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
      { return m_pTree->OnDragEnter( pWnd, pDataObject, dwKeyState, point ); }
      virtual void OnDragLeave( CWnd* pWnd )
      { m_pTree->OnDragLeave( pWnd ); }
	   virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
      { return m_pTree->OnDragOver( pWnd, pDataObject, dwKeyState, point ); }
	   virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point )
      { return m_pTree->OnDrop(pWnd, pDataObject, dropEffect, point); }
   };
   friend class CDropTarget;
   CDropTarget m_dropTarget;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEBDB_H__C42D0E61_8C04_11D1_9002_0080C732DDC2__INCLUDED_)
