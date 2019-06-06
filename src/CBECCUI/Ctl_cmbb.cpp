// CTL_CMBB.CPP  :  Contains CComboBoxCtl routines
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

#include "stdafx.h"
#include "resource.h"
#include "CUIGlobl.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "mainfrm.h"
// #include "Screens.h"
#include "ctl_cmbb.h" 
// #include "quick.h" 
#include "ComplianceUIDoc.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// String for indicating no object assigned
static char BASED_CODE szNone[] = "- none -";

// Data and strings for accessing ability to create a new component
// SAC 6/15/12 - revision to use of sdwCreateData:
//						cmbbData = sdwCreateData + (1 - 5(or up to 100)) => value above sdwCreateData = index into array of m_saObjCompID to be created
//						cmbbData > sdwCreateData + 100  =>  class ID of object to be created = cmbbData - (sdwCreateData + 100)
static DWORD sdwCreateData = 999999000;
static char BASED_CODE szCr81[]   = "- create new ";
static char BASED_CODE szCr8Imp[] = "- create/import ";
static char BASED_CODE szCr82[]   = " (and apply only here) -";  // SAC 2/12/01 - Added more text to creation string

static char BASED_CODE szErrorCaption[] = "Combo-Box Control Error";

static char BASED_CODE szUserDef[] = "";
static char BASED_CODE szRuleLib[] = "  (rule lib)";
static char BASED_CODE szUserLib[] = "  (user lib)";
static const char* pszAppend[] = { szUserDef, szRuleLib, szUserLib };

// Special Value strings
static char BASED_CODE szSpecSimDef[] = "- sim default -";
static char BASED_CODE szSpecNone[]   = "- none -";
static const char* pszSpecial[] = { szSpecSimDef, szSpecNone };

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CComboBoxCtl, CComboBox )

/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl

BEGIN_MESSAGE_MAP(CComboBoxCtl, CComboBox)
   ON_WM_GETDLGCODE()
   ON_WM_KEYDOWN()
   ON_WM_CHAR()
   ON_WM_SYSKEYDOWN()
   ON_WM_RBUTTONDOWN()
   ON_WM_KILLFOCUS()
   ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR_REFLECT()

	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)

   ON_MESSAGE(WM_GETDATASTATUS, OnGetDataStatus)
   ON_MESSAGE(WM_GETTEXTCOLOR,  OnGetTextColor)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)
END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////
//
// There are four distinct ComboBox scenarios to cover, which will
// be identified by the value of the member variable m_iComboMode:
//
//  0. Combo used as an active element navigation tool:
//       =>  m_iDataType = BEMP_Obj.
//       =>  Both parameter and array portion of m_lDBID == 0.
//       =>  Load ALL user defined occurrences of the class identified
//           by m_lDBID.
//       =>  Load only user-referenced rule library and user library
//           occurrences of the class identified by m_lDBID.
//       =>  ItemData = BEM_ObjType =>  BEMO_User, BEMO_RuleLib or BEMO_UserLib
//       =>  ItemData unused (?) - data set using character string.
//
//  1. Combo used to select an object's Parent:
//       =>  m_iDataType = BEMP_Obj.
//       =>  Both parameter and array portion of m_lDBID == 99.
//       =>  Load ALL occurences of all classes which are legal 
//           parents of the class identified by m_lDBID (this means
//           we should also include the text "Class:  " at the beginning
//           of each string).
//       =>  ItemData set to i1ClassID of parent object.
//
//  2. Combo used to attach/assign one class object to another:
//       =>  m_iDataType = BEMP_Obj.
//       =>  Both parameter and array portion of m_lDBID != 0 or 99.
//       =>  Must take into account max number of legal assignments
//           when populating the lists for these combos (i.e. don't
//           include objects which can only be referenced once and
//           have already been referenced elsewhere).
//       =>  Aside from number of reference restrictions, load ALL user
//           defined, user library AND rule library occurrences of the
//           class identified by m_lDBID.
//       =>  ItemData = BEM_ObjType =>  BEMO_User, BEMO_RuleLib or BEMO_UserLib
//       =>  Data set using character string.
//
//  3. Combo used to set a symbolic value:
//       =>  m_iDataType = BEMP_Sym.
//       =>  Both parameter and array portion of m_lDBID != 0 or 99.
//       =>  Populate list with symbols corresponding to current m_lDBID.
//       =>  ItemData populated with integer symbol value and used to
//           SetBEMData() upon user selection.
//
////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Create Functions

// This function is called at the end of each Create() function to perform
// initialization which is the same for each Create() function.
void CComboBoxCtl::GenericCreate( BOOL /*bScaleToScreenRes*/, double /*dYScale*/, DWORD /*dwWinStyle*/,
                                  UINT /*uiCtrlID*/, BOOL bForceEditable )
{
   SetFont( GetCUIFont(m_iFont), TRUE );

//   SetItemHeight( -1, 16 );  // FontY( (int) (((double) m_iClosedHt) * dYScale) ) );

   m_bEditable = (bForceEditable || BEMPX_GetCompIsEditable( m_lDBID ));

   // Set m_iComboMode
   int iPropID = BEMPX_GetPropertyID( m_lDBID );
   int iArrID  = BEMPX_GetArrayID(    m_lDBID );

   m_bNone = FALSE;
   if ( (m_lDBID > 0) && (iPropID == 0) )
   {
      if (iArrID == BEM_PARAM0_ACTIVE )
         m_iComboMode = CM_ACTIVE;
      else if (iArrID == BEM_PARAM0_NEWCOPY)
      {
         m_iComboMode = CM_ACTIVE;
         m_bNone = TRUE;
      }
      else if (iArrID == BEM_PARAM0_NEWPAR)
      {
         m_iComboMode = CM_PARENT;
//         m_bNone = TRUE;     - SAC 11/20/13 - prevent "none" from appearing in Parent lists
      }
      else if (iArrID == BEM_PARAM0_PARENT)
      {
         m_iComboMode = CM_PARENT;
//         m_bNone = TRUE;     - SAC 11/20/13 - prevent "none" from appearing in Parent lists
      }
      else if (iArrID == BEM_PARAM0_CR8OPT  ||
					iArrID == BEM_PARAM0_USERLIB ||
					iArrID == BEM_PARAM0_RULELIB )
      {
         m_iComboMode = CM_OTHER;
         m_bNone = FALSE;
      }
   }
   else if (m_iDataType == BEMP_Obj)
   {
      m_iComboMode = CM_OBJECT;
      m_bNone = TRUE;

      int iError, iObjCls;
      // SAC 6/15/12 - revised to handle an ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( m_lDBID, iError );
      if (iError == 0 && pPropType)
			for (iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)
         {	if (pPropType->getObj1ClassIdx(iObjCls) > 0)
				{	m_iaObjCompID.Add(    pPropType->getObj1ClassIdx(iObjCls) );
		         m_laObjTypeDBID.Add(  pPropType->getObjTypeDBID( iObjCls) ); 
		         m_laObjTypeValue.Add( pPropType->getObjTypeValue(iObjCls) );
				}
			}
      ASSERT( m_iaObjCompID.GetSize() > 0 );
#ifdef _DEBUG
			for (iObjCls=0; iObjCls<m_iaObjCompID.GetSize(); iObjCls++)
			{	for (int i2ObjCls=iObjCls+1; i2ObjCls<m_iaObjCompID.GetSize(); i2ObjCls++)
					ASSERT( m_iaObjCompID[iObjCls] != m_iaObjCompID[i2ObjCls] );
					// further edits required to properly identify the TYPE of component the user wishes to create - otherwise, object creation entries will show duplicate class types
			}
#endif

// SAC 8/7/00 - Added code to prevent "- none -" from appearing in lists where the input is required
      int iCompDataType = BEMPX_GetCompDataType( m_lDBID );
      if (iCompDataType == BEMD_Compulsory || iCompDataType == BEMD_Required)
         m_bNone = FALSE;
   }
   else if (m_iDataType == BEMP_Sym)
      m_iComboMode = CM_SYMBOL;
   else
      ASSERT( FALSE );

// SAC - 3/25/98 - Causes multiple list resets
//   if ( (dwWinStyle & WS_VISIBLE) )
//      BOOL dispOK = (OnDisplayData(0,0)!=0);
}


BOOL CComboBoxCtl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                				int iFont, int iClosedHt, const char FAR* lpMsg, 
                				long lDBID, int iDT, BOOL scaleToSysFont, BOOL scaleToScreenRes,
                				UINT uiIHelpID, UINT uiTHelpID, long lObjTypeDBID, long lObjTypeValue,
                           BOOL bForceEditable )
{
   double xScale = (scaleToScreenRes ? appXRatio : 1.0);
   double yScale = (scaleToScreenRes ? appYRatio : 1.0);
   CSize size( (int) (((double) rect.right-rect.left) * xScale),
               (int) (((double) rect.bottom-rect.top) * yScale) );
   CPoint pos( (int) (((double) rect.left           ) * xScale),
               (int) (((double) rect.top            ) * yScale) );

   iClosedHt = (int) (((double) iClosedHt) * yScale);

   if (scaleToSysFont)
   {
      size.cx = FontX( size.cx );
      size.cy = FontY( size.cy );
      pos.x   = FontX( pos.x );
      pos.y   = FontY( pos.y );
      iClosedHt = FontY( iClosedHt );
   }

//   // shift for Win95 tabbed dialog class
//   pos.x += eiTabDlgCtrlMarg;
//   pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;

   BOOL retVal = CComboBox::Create( dwStyle, CRect(pos, size), pParentWnd, nID );
   if (retVal)
   {
      m_lDBID        = lDBID;
      m_iDataType  	= (iDT >= 0) ? iDT : BEMPX_GetDataType( m_lDBID );
      m_iFont        = iFont;
      m_iClosedHt    = iClosedHt;
      m_iOriginalWidth = size.cx;
      m_bCalledNew   = TRUE;
      m_sStatusMsg   = lpMsg;

      m_iItemHelpID  = (uiIHelpID > 0) ? uiIHelpID : BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID = (uiTHelpID > 0) ? uiTHelpID : BEMPX_GetTopicHelpID( m_lDBID );

      m_bUnused      = FALSE;

		// SAC 6/15/12 - implement as ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
		// SAC 9/19/13 - ALLOW single compatible DBID/Value options here, as assignment option should be narrowed to a single pair when populating lists in the creation dialog comboboxes
		int iPropID = BEMPX_GetPropertyID( m_lDBID );
		int iArrID  = BEMPX_GetArrayID(    m_lDBID );
		if (lObjTypeDBID > 0 && m_lDBID > 0 && iPropID == 0 && (iArrID == BEM_PARAM0_NEWCOPY || iArrID == BEM_PARAM0_USERLIB || iArrID == BEM_PARAM0_RULELIB) )
      {	m_iaObjCompID.Add( BEMPX_GetClassID( lObjTypeDBID ) );
			m_laObjTypeDBID.Add(  lObjTypeDBID ); 
			m_laObjTypeValue.Add( lObjTypeValue );
		}
		else
      {	//m_lObjTypeDBID  = lObjTypeDBID;
      	//m_lObjTypeValue = lObjTypeValue;
			ASSERT( lObjTypeDBID == 0 && lObjTypeValue == 0 );  // if assert thrown, need to deal w/ scenario where object assignment DBID/Value passed in and not initialized based on PropertyType members
		}

      GenericCreate( scaleToScreenRes, yScale, dwStyle, nID, bForceEditable );
   }
   return retVal;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Grey out control background when the data is not editable

HBRUSH CComboBoxCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
	// TODO: Change any attributes of the DC here
	if (!m_bEditable)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
	   return buttonBrush;
//      pDC->SetBkColor( RGB(192,192,192) );
//      return greyBrush;
   }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - OnChar

void CComboBoxCtl::ResetFocus( BOOL prev )
{
   CWnd* pFocus = GetParent()->GetNextDlgTabItem( this, prev );
   if (pFocus != NULL)
   {
      if (pFocus->IsKindOf(RUNTIME_CLASS(CComboBoxCtl)))
         ((CComboBoxCtl*) pFocus)->SetFocus();
      else
         pFocus->SetFocus();
   }
}

UINT CComboBoxCtl::OnGetDlgCode()
{
   return DLGC_WANTMESSAGE;
}

void CComboBoxCtl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   if (nChar == VK_RETURN)
   {
      if (GetDroppedState())
      {
         ShowDropDown( FALSE );
         // Call Update Data Here !!! - Must for navigation, may otherwise as well
      }
      else
         ShowDropDown( TRUE );
   }
   else if (nChar == VK_TAB)
      ResetFocus( (GetKeyState(VK_SHIFT) < 0) );
   else
      CComboBox::OnKeyDown( nChar, nRepCnt, nFlags );
}



/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Focus Stuff

void CComboBoxCtl::OnKillFocus( CWnd* pNewWnd )
{
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings( "", 0 );

   CComboBox::OnKillFocus( pNewWnd );
}


void CComboBoxCtl::OnSetFocus( CWnd* pOldWnd )
{
	// SAC 10/29/15 - status bar no longer used to display property info
	//   GetMainFrame()->SetStatusBarStrings( m_sStatusMsg, m_lDBID );

   CComboBox::OnSetFocus( pOldWnd );
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Width Resizing Stuff

int CComboBoxCtl::CalcMaxStringWidth()
{
	CWindowDC dc(this);

	// Make sure we use the correct font.
	CFont* pOldFont = dc.SelectObject(GetFont());
	
	CRect rectText;
	CString strLBText;

	const int cyVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	const int cxPadding = ::GetSystemMetrics(SM_CXFIXEDFRAME);

	int nWidth = -1;

	const int nCount = GetCount();

	for (int i=0; i < nCount; i++)
	{
		GetLBText(i, strLBText);

		rectText.SetRectEmpty();
		dc.DrawText(strLBText, rectText, DT_CALCRECT);
	
		nWidth = std::max(nWidth, rectText.Width() + (cxPadding * 2));
	}

	// Add the scroll bar.
	//
	// TODO: Save the fact that we have a vertical scroll
	// bar in PreCreateWindow or PreSubclassWindow and use
	// that here.
	nWidth += cyVScroll;

	dc.SelectObject(pOldFont);

	return nWidth;
}

int CComboBoxCtl::ResizeToFitContent(int nDropDownHeight)
{
	CRect rcDropDown;
	GetDroppedControlRect(rcDropDown);
	nDropDownHeight = (nDropDownHeight > 0) ? nDropDownHeight : rcDropDown.Height();

	int nWidth = CalcMaxStringWidth();
   nWidth = std::max( nWidth, m_iOriginalWidth );

   // Only resize if new width is WIDER than initial one
//	if ((nWidth > 0) && (nDropDownHeight > 0) && (nWidth > rcDropDown.Width()))
	if ((nWidth > 0) && (nDropDownHeight > 0) && (nWidth != rcDropDown.Width()))
	{
      SetDroppedWidth( nWidth );
//		VERIFY(SetWindowPos(NULL, 0, 0, nWidth, nDropDownHeight,
//			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER));
	}

	return nWidth;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Display & Update Data Stuff

void CComboBoxCtl::OnSelchange() 
{
	// TODO: Add your control notification handler code here
   OnUpdateData(0,0);
}


BOOL CComboBoxCtl::ObjectTypeIsCompatible( int i1ClassID, int iObjIdx, BEM_ObjType eObjType )  // SAC 6/15/12 - revised to handle objects of multiple classes
{
   int iError, iSV;
	if (m_iaObjCompID.GetSize() == 1 && m_iaObjCompID[0] == 0)  // handle situation where m_laObjTypeDBID/Value used for something other than defining object referencing compatibility
		return TRUE;
	BOOL bIncompatEntry = FALSE;
	BOOL bCompatEntry = FALSE;
	for (int iObjCls=0; iObjCls < m_iaObjCompID.GetSize(); iObjCls++)
		if (i1ClassID == m_iaObjCompID[iObjCls])
		{	if (m_laObjTypeDBID[iObjCls] == 0)
				bCompatEntry = TRUE;
			else
			{	long lObjType = BEMPX_GetInteger( m_laObjTypeDBID[iObjCls], iSV, iError, iObjIdx, eObjType );
				if (iError >= 0 && lObjType == m_laObjTypeValue[iObjCls])
					bCompatEntry = TRUE;
				else // if (iError >= 0 && plObjType && *plObjType != m_laObjTypeValue[iObjCls])
					bIncompatEntry = TRUE;
			}
		}
	return (bCompatEntry ? TRUE : (bIncompatEntry ? FALSE : TRUE));
}

BOOL CComboBoxCtl::CompatibleLibraryObjectExists( int i1ClassID )  // SAC 9/19/13 - added to determine whether library import is an option for this object assignment
{
	int iError;
	BEMObject* pObj = NULL;
      for (int eType=(int) BEMO_RuleLib; eType < (int) BEMO_NumTypes; eType++)
      {  int iNumObjects = BEMPX_GetNumObjects( i1ClassID, (BEM_ObjType) eType );
         for (int iObj=0; iObj < iNumObjects; iObj++)
         {
            pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj, (BEM_ObjType) eType );
            if ( iError == 0 && pObj &&
                 (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType )) )
					return TRUE; 
         }
      }
	return FALSE;
}


void CComboBoxCtl::LoadObjectNames( int i1ClassID, BOOL /*bLoadAll*/ )
{
   int iNumObjects = BEMPX_GetNumObjects( i1ClassID );

   int iCmbbClass = BEMPX_GetClassID( m_lDBID );
   int iError;
   int iArray = BEMPX_GetArrayID( m_lDBID );
   BEMObject* pCurSelObj = NULL;
   // if this combo is for assigning the parent of an EXISTING (and current) component, then set
   // pCurSelObj to be the parent of the current object for which this combo's DBID describes
   if (m_iComboMode == CM_PARENT)
   {
      if (iArray == BEM_PARAM0_PARENT)
      {
         BEMObject* pCurObj = BEMPX_GetObjectByClass( iCmbbClass, iError );
         if (pCurObj && pCurObj->getParent())
            pCurSelObj = pCurObj->getParent();
      }
      // else - the alternative is that this combo assigns the parent of a component which
      //        is in the process of being created - in which case we leave pCurSelObj = NULL
   }
   else
   //   pCurSelObj = BEMPX_GetObject( m_lDBID, iSpecialVal, iError );
      BEMPX_GetObject( m_lDBID, pCurSelObj );

   for (int iObj=0; iObj < iNumObjects; iObj++)
   {
      BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj );
      BOOL bLoadIt = FALSE;
      if ( (iError == 0) && pObj )
      {
         if (m_iComboMode == CM_PARENT)
            // if this combo provides for the assignment of a parent component, then only add
            // this item if it IS the current parent OR if this component CAN become a child of this parent
            bLoadIt = ( pCurSelObj == pObj || BEMPX_CanCreateAnotherChildObject( iCmbbClass, pObj ) );
         else
            bLoadIt = ( pCurSelObj == pObj ||
                        ( m_iComboMode == CM_ACTIVE &&
                          (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj )) ) ||   // SAC 6/15/12 - revised to handle multiple referenced object types
                        ( BEMPX_CanAssignObject( i1ClassID, iError, iObj ) &&
                          (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj )) ) );
      }

      if (bLoadIt)
      {
         AddString( pObj->getName().toLatin1().constData() );

         if (m_iComboMode == CM_PARENT)
            SetItemData( GetCount() - 1, (DWORD) i1ClassID );
         else
            SetItemData( GetCount() - 1, (DWORD) BEMO_User );
      }
   }

   if (m_iComboMode != CM_PARENT)
   {
// SAC 9/18/13 - REMOVED rule & user library items from miscellaneous comboboxes
//	      for (int eType=(int) BEMO_RuleLib; eType < (int) BEMO_NumTypes; eType++)
//	      {
//	         int iNumObjects = BEMPX_GetNumObjects( i1ClassID, (BEM_ObjType) eType );
//	         for (int iObj=0; iObj < iNumObjects; iObj++)
//	         {
//	            int iError;
//	            BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj, (BEM_ObjType) eType );
//	            if ( (iError == 0) && (pObj != NULL) &&
//	                 ( (m_iComboMode == CM_OBJECT && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType ))) ||   // SAC 6/15/12 - revised to handle multiple referenced object types
//	                   (m_iComboMode == CM_ACTIVE && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType )) &&
//	// SAC 1/28/99 - Added NEWCOPY portion of this if statement
//	                    (pObj->getUserReferenced() || iArray == BEM_PARAM0_NEWCOPY) ) ) )
//	            {
//	               CString sEntry = pObj->getName();
//	               sEntry += pszAppend[ eType ];
//	               AddString( sEntry );
//	
//	               SetItemData( GetCount() - 1, (DWORD) eType );
//	            }
//	         }
//	      }
   }
}


static BOOL ValueInArray_Long( CArray<long,long>* piArray, long iVal )  // SAC 8/29/02
{
   ASSERT( piArray );
   if (piArray != NULL)
   {
      int iSize = piArray->GetSize();
      for (int i=0; i<iSize; i++)
         if (iVal == piArray->GetAt(i))
            return TRUE;
   }
   return FALSE;
}

BOOL CComboBoxCtl::LoadStrings()
{
	CWaitCursor wait;

   ResetContent();
   int idx = 0;

   if (m_bNone)
   {
      AddString( szNone );
      SetItemData( GetCount() - 1, 0 );
   }

   if (m_iComboMode == CM_SYMBOL)
   {
      int iNumSyms;
//      CArray<BEMSymbol*, BEMSymbol*>* pSymArray = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID /*, m_iUseDBInstance*/ );
		BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID /*, m_iUseDBInstance*/ );
      if (!pSymDepSet)
		{	//AfxMessageBox( "CComboBoxCtl::LoadStrings(): Error loading symbol data" );
			CString sErrMsg;	QString sObjProp;		// SAC 11/18/13 - more informative error messages
			BEMPX_DBIDToDBCompParamString( m_lDBID, sObjProp, false /*bLongNames*/ );
			sErrMsg.Format( "Error loading enumeration list for %s.\n(CComboBoxCtl::LoadStrings - Ctrl ID=%d)", sObjProp.toLatin1().constData(), GetDlgCtrlID() );
			AfxMessageBox( sErrMsg );
		}
      else
      {
         CArray<long, long> iaSymVal;  // SAC 8/29/02 - added code to prevent multiple symbols w/ same value from getting added to the list
                                       //               (necessary to ensure backward compatibility for certain symbols (RoofSecInsType))
         for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
         {
            long iSymValue;
            QString qstr;
            BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet /*pSymList*/, iSymIdx );   // SAC 3/23/07
            if (qstr.length() > 0 && !ValueInArray_Long( &iaSymVal, iSymValue ))  // SAC 8/29/02
            {
               AddString( qstr.toLatin1().constData() );
               SetItemData( idx++, (DWORD) iSymValue );
               iaSymVal.Add( iSymValue );  // SAC 8/29/02
            }
         }
         iaSymVal.RemoveAll();  // SAC 8/29/02
      }
   }

   else if ( (m_iComboMode == CM_ACTIVE) || (m_iComboMode == CM_OBJECT) )
   {
      int i1ClassID = 0;
      int iError;
      if (m_iComboMode == CM_ACTIVE)
         i1ClassID = BEMPX_GetClassID( m_lDBID );
      else
      {
         m_iCurObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( m_lDBID ), iError ) );
      }

      // SAC - 3/11/98 - if this item is editable and another object of this type
      // can be created, then add an item to allow the user to create a new one
      //if (eInterfaceMode == IM_INPUT && i1ClassID > 0 && m_bEditable && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
      if (eInterfaceMode == IM_INPUT && m_bEditable)   // SAC 6/15/12 replaced above w/ this version since i1ClassID not yet valid when iProp > 0
      {
         int iProp  = BEMPX_GetPropertyID( m_lDBID );
         int iArray = BEMPX_GetArrayID(    m_lDBID );
         // if prop == 0 => reserved/custom data => only allow ACTIVE or PARENT (not NEWPAR or NEWCOPY)
         if ( (iProp > 0) || (iArray == BEM_PARAM0_ACTIVE) ||
                             (iArray == BEM_PARAM0_PARENT) )
         {	int iLoopEnd = (iProp == 0 ? 1 : m_iaObjCompID.GetSize());
				for (int iObjCls=0; iObjCls < iLoopEnd; iObjCls++)		// SAC 6/15/12 - enable multiple object types to be created...
				{	if (iProp > 0)
						i1ClassID = m_iaObjCompID[iObjCls];
			      if (i1ClassID > 0 && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
					{
		            //CString sCr8Str = szCr81;
		            CString sCr8Str = (CompatibleLibraryObjectExists( i1ClassID ) ? szCr8Imp : szCr81);  // SAC 9/19/13
            		BEMClass* pCr8Class = BEMPX_GetClass( i1ClassID, iError );
            		if (pCr8Class)
            		   sCr8Str += pCr8Class->getLongName().toLatin1().constData();
            		else
            		   sCr8Str += "Building Component";
            		sCr8Str += szCr82;

            		AddString( sCr8Str );
						// SAC 6/15/12 - revision to use of sdwCreateData
            		//SetItemData( GetCount() - 1, sdwCreateData+i1ClassID );
            		SetItemData( GetCount() - 1, (iProp > 0 ? sdwCreateData+1+iObjCls : sdwCreateData+100+i1ClassID) );
					}
				}
         }
      }

      // load the existing object names into the list
	   if (m_iComboMode != CM_OBJECT)		// SAC 6/15/12 - revised to ensure objects of ALL compatible types are listed
		{	ASSERT( i1ClassID );
	      LoadObjectNames( i1ClassID, FALSE );
		}
		else
		{  CArray<long, long> iaClassesLoaded;
			for (int iObjCls=0; iObjCls < m_iaObjCompID.GetSize(); iObjCls++)
				if (m_iaObjCompID[iObjCls] > 0 && !ValueInArray_Long( &iaClassesLoaded, m_iaObjCompID[iObjCls] ))
				{
					LoadObjectNames( m_iaObjCompID[iObjCls], TRUE );
					iaClassesLoaded.Add( m_iaObjCompID[iObjCls] );
				}
			iaClassesLoaded.RemoveAll();
		}
   }

   else if (m_iComboMode == CM_PARENT)
   {
      int i1ClassID = BEMPX_GetClassID( m_lDBID );
      int iError;
      BEMClass* pClass = BEMPX_GetClass( i1ClassID, iError );
      if ( (iError >= 0) && (pClass != NULL) )
      {
         for (int iPar=0; (iPar < BEM_MAX_PARENT_TYPES) &&
                          (pClass->getParentType(iPar) > -1); iPar++)
         {
            LoadObjectNames( pClass->getParentType(iPar)+1, FALSE );
         }
      }
   }

   else if (m_iComboMode == CM_OTHER)
	{	int i1ClassID = BEMPX_GetClassID( m_lDBID );
		int iArray    = BEMPX_GetArrayID( m_lDBID );
		if (iArray == BEM_PARAM0_CR8OPT)
		{
         	AddString( "Create New Object" );					SetItemData( 0, 0 );
			if (BEMPX_GetNumObjects( i1ClassID, BEMO_UserLib ) > 0)
         {	AddString( "Import User Library Object" );		SetItemData( 1, 1 );
			}
			if (BEMPX_GetNumObjects( i1ClassID, BEMO_RuleLib ) > 0)
         {	AddString( "Import Rule Library Object" );		SetItemData( GetCount()-1, 2 );
			}
		}
		else if (iArray == BEM_PARAM0_USERLIB ||
					iArray == BEM_PARAM0_RULELIB)
		{	BEM_ObjType eObjType = (iArray == BEM_PARAM0_USERLIB ? BEMO_UserLib : BEMO_RuleLib);
			int iError, iNumObjects = BEMPX_GetNumObjects( i1ClassID, eObjType );
			for (int iObj=0; iObj < iNumObjects; iObj++)
			{	BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj, eObjType );
				if ( iError == 0 && pObj &&
					  (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, eObjType )) )
					  //( (m_iComboMode == CM_OBJECT && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType ))) ||	// SAC 6/15/12 - revised to handle multiple referenced object types
					  //  (m_iComboMode == CM_ACTIVE && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType )) &&
					  //   (pObj->getUserReferenced() || iArray == BEM_PARAM0_NEWCOPY) ) ) )
				{
					CString sEntry = pObj->getName().toLatin1().constData();
					//sEntry += pszAppend[ eType ];
					AddString( sEntry );
					SetItemData( GetCount() - 1, (DWORD) iObj );
				}
			}
		}
		else
	   {  ASSERT( FALSE );
		}
	}

   else  // invalid m_iComboMode value
   {  ASSERT( FALSE );
	}

   // Resize dropdown ListBox width if necessary to fit contents of listing
   ResizeToFitContent();

   return TRUE;
}


LRESULT CComboBoxCtl::OnGetDataStatus(WPARAM, LPARAM)
{
   return (long) BEMPX_GetDataStatus( m_lDBID );
}

LRESULT CComboBoxCtl::OnGetTextColor(WPARAM, LPARAM)
{
   return (long) (BEMPX_GetDataStatus( m_lDBID ) + NUM_RESERVED_TEXT_COLORS);
}


LRESULT CComboBoxCtl::OnGetDBID(WPARAM, LPARAM)
{
   return m_lDBID;
}

LRESULT CComboBoxCtl::OnGetDBInstance(WPARAM, LPARAM)
{
   return -1;
}


LRESULT CComboBoxCtl::OnDisplayData(WPARAM, LPARAM)
{
   // Moved LoadStrings() call here in order to ensure that the currently
   // displayed listbox strings are compatible with the dependency restrictions
   // defined in the symbol data
   BOOL loadOK = LoadStrings();			loadOK;

   SetCurSel( -1 );
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class );
   if ( (m_lDBID > 0) && (m_iDataType >= 0) &&
        (eObjType != BEMO_NumTypes) &&
        ( (BEMPX_GetNumObjects( i1Class, eObjType ) > 0) ||
          (m_iComboMode == CM_PARENT) ) )
   {
      int sel = -1;
      int iStatus = BEMPX_GetDataStatus( m_lDBID );
      if ( (iStatus > BEMS_Undefined) && (iStatus < BEMS_NumTypes) )
      {
//         // reload object list if user has changed active object since last LoadStrings() call
//         if (m_iComboMode == CM_OBJECT)
//         {
//            int iError;
//            int iCurObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( m_lDBID ), iError ) );
//            if (m_iCurObjIdx != iCurObjIdx)
//               LoadStrings();
//         }

         int iError, iSpecialVal = 0;
			if (m_iComboMode == CM_SYMBOL && m_iDataType == BEMP_Sym)
			{	// select string based on symbol VALUE
				long lNewVal = BEMPX_GetInteger( m_lDBID, iSpecialVal, iError );
				if (iError >= 0)
				{	// for now, assume ValLength = 1 => first value (data[0]) is the only value
					for (int i=0; (sel==-1 && i<GetCount()); i++)
						sel = (GetItemData(i) == (DWORD) lNewVal) ? i : -1;
			}	}
			else
			{
				CString sSelStr;
				if (m_iComboMode == CM_OBJECT)
				{	// select string based on object name
					BEMObject* pObj = BEMPX_GetObjectPtr( m_lDBID, iSpecialVal, iError );
					if (iError >= 0 && pObj)
					{
						sSelStr = pObj->getName().toLatin1().constData();
						if (pObj->getObjectType() != BEMO_User)
						{	ASSERT( FALSE );  // don't think we should ever get here...
							sSelStr += pszAppend[ (int) pObj->getObjectType() ];
						}
					}
					else if (iError >= 0)
						sSelStr = szNone;
				}
				else // if ( (m_iComboMode == CM_ACTIVE) || (m_iComboMode == CM_PARENT) )
				{	// select string based on string data
					QString qsStr = BEMPX_GetString( m_lDBID, iSpecialVal, iError );
					if (iError >= 0 && qsStr.length() > 0)
					{
						sSelStr = qsStr.toLatin1().constData();

						// what if current object is from a library??
                  BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( m_lDBID ), iError );
                  if (iError >= 0 && pObj && pObj->getObjectType() != BEMO_User &&
                       // this last part ensures we don't paste trailing "(... Lib)" into NEWPAR selected string
                       (BEMPX_GetPropertyID( m_lDBID ) != 0 || BEMPX_GetArrayID( m_lDBID ) != BEM_PARAM0_NEWPAR) )
                  {	ASSERT( FALSE );  // don't think we should ever get here...
                     sSelStr += pszAppend[ (int) pObj->getObjectType() ];
						}
					}
				}

            if (sSelStr.GetLength() > 0)
            {  CString sItemStr;
               for (int i=0; (sel==-1) && (i<GetCount()); i++)
               {  GetLBText( i, sItemStr );
                  sel = (sSelStr.Compare( sItemStr ) == 0) ? i : -1;
               }
            }

            // DEAL WITH SPECIALVAL
            if (iSpecialVal > 0)
            {
               sel = FindString( -1, pszSpecial[ iSpecialVal-1 ] );
               if (sel == CB_ERR)
               {
                  AddString( pszSpecial[ iSpecialVal-1 ] );
                  sel = GetCount() - 1;
                  SetItemData( sel, 0 );
               }
            }
         }

         if ( (sel < 0) && (m_bNone) )
            sel = 0;
      }
      // SAC 8/8/00 - added else statement to enable display of "- none -" for undefined data as opposed to leaving the selection blank
      else if (m_bNone)
         sel = 0;

      if (sel >= 0)
         SetCurSel( sel );
   }

   return 1;
}


static BOOL sbNewRulesetSelected = FALSE;

BOOL CComboBoxCtl::UserSelectedNewRuleset()
{
   sbNewRulesetSelected = TRUE;  // default to TRUE in order to prevent some mishap from missing a ruleset switch
   int iError, iSpecialVal;
   long lNewVal = BEMPX_GetInteger( m_lDBID, iSpecialVal, iError );
   if (iError >= 0)
   {
      CString sCurRuleset = BEMPX_GetSymbolString( (int) lNewVal, m_lDBID ).toLatin1().constData();
      CString sSelRuleset;
      GetLBText( GetCurSel(), sSelRuleset );
      sbNewRulesetSelected = (sSelRuleset != sCurRuleset);
   }
   return sbNewRulesetSelected;
}

LRESULT CComboBoxCtl::OnUpdateData( WPARAM, LPARAM )
{
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class );
   if ( (m_lDBID > 0) && (m_iDataType >= 0) &&
        (eObjType != BEMO_NumTypes) &&
        (BEMPX_GetNumObjects( i1Class, eObjType ) > 0) )
   {
      int iPropID = BEMPX_GetPropertyID( m_lDBID );
      int iArrID  = BEMPX_GetArrayID(    m_lDBID );
      DWORD dwSelData = GetItemData( GetCurSel() );
      if (!m_bEditable)
      {
//         ::MessageBox( NULL, szErrNotEditable, szErrorCaption, MB_ICONSTOP );
         MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
         OnDisplayData(0,0);
      }
      else if ( (eInterfaceMode != IM_INPUT) && (m_iComboMode != CM_ACTIVE) )
      {
//         ::MessageBox( NULL, szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
         MessageBox( szErrIntModeNotInp, szErrorCaption, MB_ICONSTOP );
         OnDisplayData(0,0);
      }
      else if ( (eiCurAnalysisStep != AS_None) && (m_iComboMode != CM_ACTIVE) )
      {
//         ::MessageBox( NULL, szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
         MessageBox( szErrRestoreInp, szErrorCaption, MB_ICONSTOP );
         OnDisplayData(0,0);
      }
      else if ( (m_iComboMode != CM_ACTIVE) && (iArrID != BEM_PARAM0_NEWPAR) && (iArrID != BEM_PARAM0_NEWCOPY) &&
					 (iArrID != BEM_PARAM0_CR8OPT) && (iArrID != BEM_PARAM0_USERLIB) && (iArrID != BEM_PARAM0_RULELIB) &&
                (ObjectIsFromLibrary( m_lDBID )) )
      {
         OnDisplayData(0,0);
      }
      else if ( (m_lDBID > 0) && (iPropID == 0) &&
                ( (iArrID == BEM_PARAM0_NEWPAR ) ||
                  (iArrID == BEM_PARAM0_NEWCOPY) ||
                  (iArrID == BEM_PARAM0_USERLIB) ||
                  (iArrID == BEM_PARAM0_RULELIB) ) )
      {  // Do nothing since this data is only grabbed and used if the user
      }  // chooses to create the new component for which this data is being defined
      else if ( (m_lDBID > 0) && (iPropID == 0) &&
                (  iArrID == BEM_PARAM0_CR8OPT   ) )
		{  // refresh parent dialog
         GetParent()->PostMessage( WM_DISPLAYMODS );
		}
      else if ( (m_lDBID == elDBID_Proj_Ruleset || m_lDBID == elDBID_Wiz_Ruleset) && UserSelectedNewRuleset() &&
                (MessageBox( eszRulesetSwitch, eszWarning, MB_YESNO|MB_DEFBUTTON2|MB_ICONSTOP ) == IDNO) )
      {  // User chose to CANCEL the selection of a different compliance ruleset
         OnDisplayData(0,0);
      }
      else
      {
         int iSetDataRetVal = -1;
         BOOL bEvalRules = TRUE;
         int iDataType = m_iDataType;

         // First handle selection based on integer value (symbol value)
         if ( (m_iComboMode == CM_SYMBOL) && (m_iDataType == BEMP_Sym) )
         {
            long lNewVal = (long) dwSelData;

            iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*) &lNewVal );
         }
         // Now deal with the selection of "- create new ... -"
         else if (dwSelData > sdwCreateData)
         {
            bEvalRules = FALSE;
            CMainFrame* pMainFrm = (CMainFrame*) GetParentFrame();
            if (pMainFrm)
            {
					// SAC 6/15/12 - revision to use of sdwCreateData
               //int iCreateClass  = (int) (dwSelData - sdwCreateData);
					if (dwSelData > (sdwCreateData+100))
					{	// parent or active object selection
	               int iCreateClass  = (int) (dwSelData - sdwCreateData-100);
	               long lAssignDBID  = (m_iComboMode == CM_OBJECT) ? m_lDBID : 0;
	               BOOL bEditNewComp = (m_iComboMode != CM_ACTIVE);
						int iAOIError;
						int iAssignmentObjIdx = (lAssignDBID > 0 ? BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( lAssignDBID ), iAOIError ) ) : -1);		ASSERT( iAssignmentObjIdx >= -1 );  // SAC 5/29/13
	               pMainFrm->CreateBuildingComponent( iCreateClass, lAssignDBID, bEditNewComp,
   	                                               GetParent(), 0 /*m_lObjTypeDBID*/, 0 /*m_lObjTypeValue*/, iAssignmentObjIdx );
					}
					else
					{	int iObjClsIdx = dwSelData - sdwCreateData - 1;
						ASSERT( iObjClsIdx >= 0 && m_iaObjCompID.GetSize() > iObjClsIdx );
						if (    iObjClsIdx >= 0 && m_iaObjCompID.GetSize() > iObjClsIdx )
						{	int iAOIError;
							int iAssignmentObjIdx = (m_lDBID > 0 ? BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( m_lDBID ), iAOIError ) ) : -1);		ASSERT( iAssignmentObjIdx >= -1 );  // SAC 5/29/13
		               pMainFrm->CreateBuildingComponent( m_iaObjCompID[ iObjClsIdx ], m_lDBID, TRUE /*bEditNewComp*/,
      		                                            GetParent(), m_laObjTypeDBID[ iObjClsIdx ], m_laObjTypeValue[ iObjClsIdx ], iAssignmentObjIdx );
						}
					}
               iSetDataRetVal = 1;
            }
         }
         else  // all other types set via selected item's character string
         {
            iDataType = BEMP_Str;
            CString sSelStr;
            int iCurSel = GetCurSel();
            if (iCurSel >= 0)
            {
               GetLBText( iCurSel, sSelStr );

               int iObjFrom = (int) dwSelData;
               if ( (m_iComboMode != CM_PARENT) &&
                    (iObjFrom != 0) ) // => not user-defined object
                  sSelStr = sSelStr.Left( sSelStr.GetLength() - 12 );

               if (sSelStr.Compare( szNone ) == 0)
                  sSelStr.Empty();

               iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*) ((const char*) sSelStr),
                                               (BEM_ObjType) iObjFrom );

               if (m_iComboMode == CM_ACTIVE)
                  bEvalRules = FALSE;
            }
         }

         if (iSetDataRetVal >= 0)
         {
            // User switched compliance rulesets
            if ( (m_lDBID == elDBID_Proj_Ruleset || m_lDBID == elDBID_Wiz_Ruleset) && (sbNewRulesetSelected) )
            {
                CString sRulesetSymbol;
                GetLBText( GetCurSel(), sRulesetSymbol );
                QString qsRulesetSym = sRulesetSymbol;
                BEMPX_SymbolToRuleFile( qsRulesetSym );
                LoadRuleset( qsRulesetSym.toLatin1().constData(), FALSE );
            }

            // set data modified flag & execute compliance rulelist #1
            if (bEvalRules)
            {
               SetDataModifiedFlag( TRUE );
					GetParentFrame()->SendMessage( WM_DATAMODIFIED, 0, m_lDBID );		// SAC 4/12/18
               GetParentFrame()->SendMessage( WM_EVALPROPOSED, DefaultAction_DataMod, m_lDBID );
            }
            // send a message to the main view's tree control via CMainFrame in case the tree requires updating
            GetParentFrame()->SendMessage( WM_UPDATETREE, 0, m_lDBID );

            // redisplay all currently displayed database data
            GetParent()->PostMessage( WM_DISPLAYMODS );

            // redisplay status bar strings
	// SAC 10/29/15 - status bar no longer used to display property info
	//            GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);
         }
      }
   }

   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Quick Menu Stuff

void CComboBoxCtl::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      DoQuickMenu();
   else
      CComboBox::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CComboBoxCtl::OnRButtonDown( UINT /*nFlags*/, CPoint /*point*/ )
{
   SetFocus();
   DoQuickMenu();
}

void CComboBoxCtl::DoQuickMenu()
{
   UINT uiQuickMask = QMI_ITEMHELP | QMI_TOPICHELP;
   int iStatus = BEMPX_GetDataStatus( m_lDBID );
   int iPropID = BEMPX_GetPropertyID( m_lDBID );
   if ( (iStatus == BEMS_UserDefined) && (iPropID > 0) )
      uiQuickMask |= QMI_DEFAULT;

//   int iError = 0;
//   int iCritDefIdx = BEMPX_GetCriticalDefaultIndex( m_lDBID, iError );
//   if ( (iError >= 0) && (iCritDefIdx > 0) )
//      uiQuickMask |= QMI_COMMENT;

// TO DO - code to get at class index of object which is assigned by this combo in order to add
// a creation entry to the quick menu
   if (m_iComboMode == CM_OBJECT)
      uiQuickMask |= (QMI_CREATE | QMI_EDIT | QMI_DELETE);

   CRect winRect;
   GetWindowRect( winRect );
   GetMainFrame()->DoQuickMenu( winRect.left, winRect.right, winRect.top, uiQuickMask,
                                m_iItemHelpID, m_iTopicHelpID, m_lDBID );
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Class Registration Stuff

//16 // Define statics
//16 WNDPROC CComboBoxCtl::pfnSuperWndProc = NULL ;
//16 
//16 
//16 LONG CALLBACK __export
//16 CComboBoxCtl::FirstMsgOnlyWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
//16 {
//16 	//
//16 	// Construct the object and then attach the hWnd to it.
//16 	//
//16 	CComboBoxCtl* pWnd = new CComboBoxCtl;
//16 	pWnd->Attach(hWnd);
//16 
//16 	pWnd->m_bCreatedByClassName = TRUE;
//16 
//16 	//
//16 	// Subclass the window by changing the window procedure to AfxWndProc
//16 	// and pass the current message to it.
//16 	//
//16 	::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);
//16 
//16 #ifdef STRICT
//16 	return ::CallWindowProc((WNDPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//16 #else
//16 	return ::CallWindowProc((FARPROC)AfxWndProc, hWnd, msg, wParam, lParam);
//16 #endif
//16 	//DER
//16 }
//16 
//16 
//16 BOOL CComboBoxCtl::RegisterMyClass()
//16 {
//16 	WNDCLASS wcls;
//16 
//16 	if(!::GetClassInfo(NULL, "combobox", &wcls) )
//16 	{
//16 		return FALSE;
//16 	}
//16 
//16 	if (pfnSuperWndProc == NULL) 
//16 		pfnSuperWndProc = wcls.lpfnWndProc;
//16 
//16 	ASSERT( pfnSuperWndProc == wcls.lpfnWndProc);
//16 
//16 	static const char szClassName[] = "ctlcombobox";
//16 	if(::GetClassInfo(AfxGetInstanceHandle(), szClassName, &wcls))
//16 	{
//16 		return (wcls.lpfnWndProc == CComboBoxCtl::FirstMsgOnlyWndProc);
//16 	}
//16 
//16 	wcls.lpfnWndProc = CComboBoxCtl::FirstMsgOnlyWndProc;
//16 	wcls.hInstance = AfxGetInstanceHandle();
//16 	wcls.lpszClassName = szClassName;
//16 
//16 	return (RegisterClass(&wcls) !=0);
//16 }


void CComboBoxCtl::PostNcDestroy()
{
	if ( (m_bCreatedByClassName) || (m_bCalledNew) )
		delete this;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Diagnostics

#ifdef _DEBUG
void CComboBoxCtl::AssertValid() const
{
	CComboBox::AssertValid();
}

void CComboBoxCtl::Dump(CDumpContext& dc) const
{
	CComboBox::Dump(dc);
}
#endif //_DEBUG

