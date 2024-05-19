// ExtendedComboBox.cpp : implementation file
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

#include "stdafx.h"
//#include "listtest.h"
#include "resource.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "Screens.h"
#include "ExtendedComboBox.h"
#include "BEMProcUIX.h"
#include "BPUICtl_Cmbb.h" 

#include "DlgRangeError.h"
//#include "DlgErrorList.h"  // SAC 2/6/03

#include <afxtempl.h>
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

static CArray<long, long> slaDBID_Combo;
static CArray<long, long> slaDBID_Compat;
static CArray<long, long> slaDBID_CompatError;
static CStringArray ssaCompatRulelists;

void BEMPUIX_SetExtCmbDatabaseIDs( int iNumDBIDPairs, long* laDBID_Combo, long* laDBID_Compatability,
                                long* laDBID_CompatError, const char** pszCompatRuleLists )
{
   slaDBID_Combo.RemoveAll();
   slaDBID_Compat.RemoveAll();
   slaDBID_CompatError.RemoveAll();
   ssaCompatRulelists.RemoveAll();
   for (int i=0; i<iNumDBIDPairs; i++)
   {
      slaDBID_Combo.Add(       laDBID_Combo[i] );
      slaDBID_Compat.Add(      laDBID_Compatability[i] );
      slaDBID_CompatError.Add( laDBID_CompatError[i] );
      ssaCompatRulelists.Add(  pszCompatRuleLists[i] );
   }
}

BOOL GetCompatabilityData( long lModifiedDBID, long& lCompatErrorDBID, CString& sCompatRulelist )
{
   long lModDBID_NoArr = BEMPX_GetDBID( BEMPX_GetClassID( lModifiedDBID ), BEMPX_GetPropertyID( lModifiedDBID ), 1 );
   for (int i=0; i<slaDBID_Combo.GetSize(); i++)
   {
      if (lModDBID_NoArr == slaDBID_Combo[i])
      {
         lCompatErrorDBID = slaDBID_CompatError[i];
         sCompatRulelist  = ssaCompatRulelists[i];
         return TRUE;
      }
   }
   return FALSE;
}

int GetCompatObjectIndex( long lModDBID, long lCompatDBID, int iDefaultInstance )
{
   int iRetVal = iDefaultInstance;

   if (lCompatDBID > 0  &&  BEMPX_GetClassID( lModDBID ) != BEMPX_GetClassID( lCompatDBID ))
   {
      int iError;
      BEMClass* pClass = BEMPX_GetClass( BEMPX_GetClassID( lModDBID ), iError );
      if (pClass != NULL && pClass->ClassInParentList( BEMPX_GetClassID( lCompatDBID ) ))
      {
         BEMObject* pLocalObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( lModDBID ), iError, iRetVal );
         ASSERT( pLocalObj );
         ASSERT( pLocalObj->getParent() );
         ASSERT( pLocalObj->getParent()->getClass() );
         if (pLocalObj && pLocalObj->getParent() && pLocalObj->getParent()->getClass())
            iRetVal = BEMPX_GetObjectIndex( pLocalObj->getParent()->getClass(), pLocalObj->getParent() );
      }
      else
      {  ASSERT( FALSE );  }  // if DBID class is not same, then it MUST correspond to a parent component
   }

   return iRetVal;
}

void ReportCompatibilityIssue( long lCompatErrorDBID, long lCompatVal, int iCompatObjInstance, CString& sCompatRulelist, CWnd* pWnd )
{
   ASSERT( lCompatErrorDBID > 0 );
   ASSERT( !sCompatRulelist.IsEmpty() );
   BEMPX_SetBEMData( lCompatErrorDBID, BEMP_Int, (void*) &lCompatVal, BEMO_User, iCompatObjInstance );

   CString sCumErr;
   BOOL bErrorsFound = FALSE;
   BOOL bWarningsFound = FALSE;
   QStringList saErrors, saWarnings;
   if (!bErrorsFound)	// always true
   {
      CWaitCursor busyCursor;
      VERIFY( BEMPX_EvalErrorCheckList( sCompatRulelist, saErrors, saWarnings, BEMPX_GetClassID( lCompatErrorDBID ), iCompatObjInstance ) );

      bErrorsFound   = (saErrors.size() > 0);
      bWarningsFound = (saWarnings.size() > 0);
      ASSERT( !bWarningsFound );
      for (int iCT=0; iCT<saErrors.size(); iCT++)
      {
         if (iCT > 0)
            sCumErr += "\r\n\r\n";
         sCumErr += saErrors[iCT].toLatin1().constData();
      }
   }

   if (!sCumErr.IsEmpty())
   {
      CDlgRangeError dlgErr( sCumErr, SWDM_Default, pWnd, "Description of incompatibility:", (bErrorsFound ? " " : ""),
                             (!bErrorsFound), "Selection Incompatibility" );
      dlgErr.DoModal();
   }
}

/////////////////////////////////////////////////////////////////////////////


const UINT nMessage=::RegisterWindowMessage("ComboSelEndOK");


// String for indicating no object assigned
static char BASED_CODE szNone[] = "- none -";

// Data and strings for accessing ability to create a new component
// SAC 6/15/12 - revision to use of sdwCreateData:
//						cmbbData = sdwCreateData + (1 - 5(or up to 100)) => value above sdwCreateData = index into array of m_saObjCompID to be created
//						cmbbData > sdwCreateData + 100  =>  class ID of object to be created = cmbbData - (sdwCreateData + 100)
static DWORD sdwCreateData = 999999000;
static char BASED_CODE szCr81[] = "- create new ";
static char BASED_CODE szCr82[] = " (and apply only here) -";  // SAC 2/12/01 - Added more text to creation string
static char BASED_CODE szCr82b[] = " -";  // SAC 1/3/12 - Added alternative secondary string for "active" component selections (that are not being "applied" to an attribute)

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

IMPLEMENT_DYNAMIC( CExtendedComboBox, CComboBox )

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


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
// CExtendedComboBox - Create Functions

// This function is called at the end of each Create() function to perform
// initialization which is the same for each Create() function.
void CExtendedComboBox::GenericCreate( BOOL /*bScaleToScreenRes*/, double /*dYScale*/, DWORD /*dwWinStyle*/, UINT /*uiCtrlID*/ )
{
   SetFont( GetWizFont(m_iFont), TRUE );

//   SetItemHeight( -1, 16 );  // FontY( (int) (((double) m_iClosedHt) * dYScale) ) );

// SAC 6/4/01 - Added code to setup data that will track item (in)compatibility
   m_bAllowSelectionOfDisabledItems = TRUE;
   m_lDBIDCompatItemArray = 0;
   m_lDBIDCompatError = 0;
   m_iCompatCompInstance = m_iDBInstance;
   m_sCompatRulelist.Empty();
   ASSERT( slaDBID_Combo.GetSize() == slaDBID_Compat.GetSize() );
   for (int i=0; (m_lDBIDCompatItemArray == 0 && i<slaDBID_Combo.GetSize()); i++)
   {
      m_lDBIDCompatItemArray = (m_lDBID == slaDBID_Combo[i] ? slaDBID_Compat[i] : 0);
      if (m_lDBIDCompatItemArray > 0)
      {
         m_lDBIDCompatError = slaDBID_CompatError[i];
         m_sCompatRulelist  = ssaCompatRulelists[i];
      }
   }
   m_iCompatCompInstance = GetCompatObjectIndex( m_lDBID, m_lDBIDCompatItemArray, m_iDBInstance );
   m_dwaCompatItemArray.RemoveAll();
   m_dwCurSelData = 0;
   m_lCompatModVal = 100;                   // SAC 1/12/05 - Added to prevent "% 100" for arrays exceeding 100 elements

// SAC 10/13/07 - added logic to prevent calling BEMPX_GetCompIsEditable() w/ a bogus DBID
   m_bEditable = ((m_lDBID < BEM_COMP_MULT || BEMPX_GetCompIsEditable( m_lDBID )) && m_cEditableCondition.MissingOrTrue());

   // Set m_iComboMode
   int iPropID = BEMPX_GetPropertyID( m_lDBID );
   int iArrID  = BEMPX_GetArrayID(    m_lDBID );

   m_bNone = FALSE;
   // SAC 2/1/00 - New CM_SCREEN mode stuff
   if (m_lDBIDScreenIDArray > 0)
      m_iComboMode = CM_SCREEN;
   else if ( m_lDBID > 0 && iPropID == 0 )
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
         m_bNone = TRUE;
      }
      else if (iArrID == BEM_PARAM0_PARENT)
      {
         m_iComboMode = CM_PARENT;
         m_bNone = TRUE;
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
         {	if (pPropType->getObj1ClassIdx(iObjCls) > 0 || pPropType->getObjTypeValue(iObjCls) != 0)
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

      // SAC 3/3/99 - UGLY (but functional) - this is to prevent EEMRun:OperateOn list from containing "- none -"
      if (m_laObjTypeDBID.GetSize() > 0 && m_laObjTypeDBID[0] == 0 && m_laObjTypeValue[0] == -1)  // OK to check only first array element
         m_bNone = FALSE;
      // SAC 8/7/00 - Added code to prevent "- none -" from appearing in lists where the input is required
      else
      {
         int iCompDataType = BEMPX_GetCompDataType( m_lDBID );
         if (iCompDataType == BEMD_Compulsory || iCompDataType == BEMD_Required)
            m_bNone = FALSE;
      }
   }
   else if (m_iDataType == BEMP_Sym)
      m_iComboMode = CM_SYMBOL;
   else
   {
      //ASSERT( FALSE );
      // SAC 3/17/99 - replaced ASSERT above w/ following error message
      CString sErrMsg;
      sErrMsg.Format( "CExtendedComboBox::GenericCreate(), Ctrl ID=%d, DBID=%d:  Incompatible variable type.", GetDlgCtrlID(), m_lDBID );
      BEMMessageBox( sErrMsg );
   }

   // SAC 3/9/01 - Added flag to cause quick return following update for other scenarios other than (m_iComboMode == CM_SCREEN)
   m_bBailQuicklyFollowingUpdate = (m_iComboMode == CM_SCREEN);

   // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
   if (m_lDependentDBID > 0)
   {
      long lDBID = GetParent()->SendMessage( WM_CTRLIDTODBID, (UINT) m_lDependentDBID );
      if (lDBID > 0  &&  BEMPX_GetClassID( lDBID ) > 0)
         m_lDependentDBID = lDBID;
   }
}


BOOL CExtendedComboBox::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits, long lDBIDOffset,
                                BOOL bTabbedDlgShift, BOOL scaleToSysFont, BOOL scaleToScreenRes, long lDBIDScreenIDArray,
                                UINT uiTopicHelp, UINT uiItemHelp )
{
//   DWORD winStyle = WS_CHILD|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL;
//   DWORD winStyle = WS_CHILD|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL | CBS_OWNERDRAWFIXED|CBS_HASSTRINGS;
   DWORD winStyle = WS_CHILD|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED|CBS_HASSTRINGS;

   double xScale = (scaleToScreenRes ? appXRatio : 1.0);
   double yScale = (scaleToScreenRes ? appYRatio : 1.0);
   CSize size( (int) (((double) pControl->m_iWidth ) * xScale),
               (int) (((double) pControl->m_iHeight) * yScale) );
   CPoint pos( (int) (((double) pControl->m_iX     ) * xScale),
               (int) (((double) pControl->m_iY     ) * yScale) );

   if (scaleToSysFont)
   {
      size.cx = FontX( size.cx );
      size.cy = FontY( size.cy );
      pos.x   = FontX( pos.x );
      pos.y   = FontY( pos.y );
   }

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

   BOOL retVal = CComboBox::Create( winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
      m_lDBID          = pControl->m_lDBID + lDBIDOffset;
      m_iDBInstance    = pControl->m_iDBInstance;  // SAC 3/3/99
      m_iDataType      = BEMPX_GetDataType( m_lDBID );
      m_iFont          = pControl->m_iFont;
      m_iClosedHt      = (int) pControl->m_lValue;
      m_iOriginalWidth = size.cx;
      m_bCalledNew     = TRUE;
      m_sStatusMsg     = pControl->m_sStatusMsg;

      m_iItemHelpID    = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lDBID ) : uiItemHelp);
      m_iTopicHelpID   = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lDBID ) : uiTopicHelp);

      m_bUnused        = FALSE;

      //m_lObjTypeDBID   = 0;
      //m_lObjTypeValue  = 0;

      m_cEditableCondition = pControl->m_cEditableCondition;
      m_bAllowEdits = bAllowEdits;

      // SAC 2/1/00 - New CM_SCREEN mode stuff
      m_lDBIDScreenIDArray = lDBIDScreenIDArray;

      // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
      m_lDependentDBID = pControl->m_iUnitDX;
      m_lDependentVal  = -1;

      GenericCreate( scaleToScreenRes, yScale, winStyle, pControl->m_uiCtrlID );
   }
   return retVal;
}


/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox

CExtendedComboBox::CExtendedComboBox()
{
	m_ListBox.SetParent(this);
}

CExtendedComboBox::~CExtendedComboBox()
{
}

// default implementation
BOOL CExtendedComboBox::IsItemEnabled(UINT nIndex) const
{
	if (nIndex>=(DWORD)GetCount())
		return TRUE;	// whatever

//	DWORD uData=GetItemData(nIndex);
//
//	return (uData&1);
//
// SAC 6/4/01 - replaced sample code default (above) with reference to item (in)compatibility tracking data
   DWORD dwItemData = GetItemData( nIndex );
   if (m_dwCurSelData > 0 && m_dwCurSelData == dwItemData)
		return TRUE;	// assume currently selected item always re-selectable

// SAC 1/12/05 - Added to prevent "% 100" for arrays exceeding 100 elements
//   int iData = (int) dwItemData % 100;  // item data mod 100 = array index of compat data
   int iData = (int) dwItemData % m_lCompatModVal;  // item data mod 100 (or perhaps 1000) = array index of compat data
	if (iData < 1 || iData >= m_dwaCompatItemArray.GetSize())
		return TRUE;  // default to compatible ??
   else
      return (m_dwaCompatItemArray[iData-1] == 0);  // compat data value of 0 => COMPATIBLE
}


BEGIN_MESSAGE_MAP(CExtendedComboBox, CComboBox)
	//{{AFX_MSG_MAP(CExtendedComboBox)
	ON_WM_CHARTOITEM()
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CTLCOLORLISTBOX, OnCtlColor)
	ON_REGISTERED_MESSAGE(nMessage, OnRealSelEndOK)


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
//   ON_MESSAGE(WM_GETTEXTCOLOR,  OnGetTextColor)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)

	ON_WM_HELPINFO()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox message handlers

void CExtendedComboBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT((GetStyle()&(CBS_OWNERDRAWFIXED|CBS_HASSTRINGS))==(CBS_OWNERDRAWFIXED|CBS_HASSTRINGS));
	CComboBox::PreSubclassWindow();
}

void CExtendedComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle (lpDrawItemStruct->hDC);

//   TRACE( "ItemID: %ld  Action: %s|%s|%s  State: %s|%s|%s|%s|%s|%s|%s\n", (LONG)(lpDrawItemStruct->itemID),
//                     (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE ? "ODA_DRAWENTIRE" : "-"),
//                     (lpDrawItemStruct->itemAction & ODA_FOCUS      ? "ODA_FOCUS"      : "-"),
//                     (lpDrawItemStruct->itemAction & ODA_SELECT     ? "ODA_SELECT"     : "-"),
//                     (lpDrawItemStruct->itemState & ODS_CHECKED      ? "ODS_CHECKED"      : "-"),
//                     (lpDrawItemStruct->itemState & ODS_DISABLED     ? "ODS_DISABLED"     : "-"),
//                     (lpDrawItemStruct->itemState & ODS_FOCUS        ? "ODS_FOCUS"        : "-"),
//                     (lpDrawItemStruct->itemState & ODS_GRAYED       ? "ODS_GRAYED"       : "-"),
//                     (lpDrawItemStruct->itemState & ODS_SELECTED     ? "ODS_SELECTED"     : "-"),
//                     (lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT ? "ODS_COMBOBOXEDIT" : "-"),
//                     (lpDrawItemStruct->itemState & ODS_DEFAULT      ? "ODS_DEFAULT"      : "-") );

	if (((LONG)(lpDrawItemStruct->itemID) >= 0) &&
		(lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT | ODA_FOCUS)))
	{
		BOOL fDisabled = !IsWindowEnabled () || !IsItemEnabled(lpDrawItemStruct->itemID);

		COLORREF newTextColor = fDisabled ?
			RGB(0x80, 0x80, 0x80) : GetSysColor (COLOR_WINDOWTEXT);  // light gray

		COLORREF oldTextColor = pDC->SetTextColor (newTextColor);

		COLORREF newBkColor = GetSysColor (COLOR_WINDOW);
		COLORREF oldBkColor = pDC->SetBkColor (newBkColor);

		if (newTextColor == newBkColor)
			newTextColor = RGB(0xC0, 0xC0, 0xC0);   // dark gray

// SAC 6/4/01
		if ((m_bAllowSelectionOfDisabledItems || !fDisabled) && ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0))
		{
			pDC->SetTextColor (GetSysColor (COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor (GetSysColor (COLOR_HIGHLIGHT));
		}

		CString strText;
		GetLBText(lpDrawItemStruct->itemID, strText);

		const RECT &rc=lpDrawItemStruct->rcItem;

		pDC->ExtTextOut(rc.left + 2,
//				  rc.top + 2,// + std::max(0, (cyItem - m_cyText) / 2),
				  rc.top + 1,// + std::max(0, (cyItem - m_cyText) / 2),
				  ETO_OPAQUE, &rc,
				  strText, strText.GetLength (), NULL);

//      TRACE( "  - drawing item %ld %s  (state: %s)  ItemData: %ld  \n", (LONG)(lpDrawItemStruct->itemID),
//               (fDisabled ? "DISabled" : "Enabled"), (lpDrawItemStruct->itemState & ODS_SELECTED ? "selected" : "unselected") );

		pDC->SetTextColor (oldTextColor);
		pDC->SetBkColor (oldBkColor);
	}
	else if ((LONG)(lpDrawItemStruct->itemID)<0)	// drawing edit text
	{
		COLORREF newTextColor = GetSysColor (COLOR_WINDOWTEXT);  // light gray
		COLORREF oldTextColor = pDC->SetTextColor (newTextColor);

		COLORREF newBkColor = GetSysColor (COLOR_WINDOW);
		COLORREF oldBkColor = pDC->SetBkColor (newBkColor);

		if ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0)
		{
			pDC->SetTextColor (GetSysColor (COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor (GetSysColor (COLOR_HIGHLIGHT));
		}

		CString strText;
		GetWindowText(strText);
		const RECT &rc=lpDrawItemStruct->rcItem;

		pDC->ExtTextOut(rc.left + 2,
//				  rc.top + 2,// + std::max(0, (cyItem - m_cyText) / 2),
				  rc.top + 1,// + std::max(0, (cyItem - m_cyText) / 2),
				  ETO_OPAQUE, &rc,
				  strText, strText.GetLength (), NULL);

		pDC->SetTextColor (oldTextColor);
		pDC->SetBkColor (oldBkColor);
	}

	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) != 0)
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
	
}

void CExtendedComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
//	UNREFERENCED_PARAMETER(lpMeasureItemStruct);

   ASSERT(lpMeasureItemStruct->CtlType == ODT_COMBOBOX);
   if (lpMeasureItemStruct->itemID == (UINT) -1)  // Closed box height
      lpMeasureItemStruct->itemHeight = FontY( 15 );
//   else  // List item height
//   {
//      LPCTSTR lpszText = (LPCTSTR) lpMeasureItemStruct->itemData;
////      ASSERT(lpszText != NULL);
//      if (lpszText)
//      {
//         CSize   sz;
//         CDC*    pDC = GetDC();
//         sz = pDC->GetTextExtent(lpszText);
//         ReleaseDC(pDC);
//         lpMeasureItemStruct->itemHeight = 3*sz.cy/2;
//      }
//      else
//         lpMeasureItemStruct->itemHeight = FontY( 15 );
//   }
}

int CExtendedComboBox::OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex) 
{
	// TODO: Add your message handler code here and/or call default
	
	int ret=CComboBox::OnCharToItem(nChar, pListBox, nIndex);
// SAC 6/4/01
	if (ret>=0 && !m_bAllowSelectionOfDisabledItems && !IsItemEnabled(ret))
		return -2;
	else
		return ret;
}

void CExtendedComboBox::OnSelendok() 
{
	// TODO: Add your control notification handler code here
	GetWindowText(m_strSavedText);
	PostMessage(nMessage);	
}

LRESULT CExtendedComboBox::OnRealSelEndOK(WPARAM,LPARAM)
{
	CString currentText;
	GetWindowText(currentText);

	int index=FindStringExact(-1,currentText);
// SAC 6/4/01
	if (index>=0 && !m_bAllowSelectionOfDisabledItems && !IsItemEnabled(index))
	{
		SetWindowText(m_strSavedText);
		GetParent()->SendMessage(WM_COMMAND,MAKELONG(GetWindowLong(m_hWnd,GWL_ID),CBN_SELCHANGE),(LPARAM)m_hWnd);
	}

	return 0;
}

LRESULT CExtendedComboBox::OnCtlColor(WPARAM,LPARAM lParam)
{
	if (m_ListBox.m_hWnd==NULL && lParam!=0 && lParam!=(LPARAM)m_hWnd)
		m_ListBox.SubclassWindow((HWND)lParam);

	return Default();
}


void CExtendedComboBox::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
//	m_ListBox.UnsubclassWindow();
	m_ListBox.Detach();
	

//	CComboBox::PostNcDestroy();
	if ( (m_bCreatedByClassName) || (m_bCalledNew) )
		delete this;
}



/////////////////////////////////////////////////////////////////////////////
// CListBoxInsideComboBox

CListBoxInsideComboBox::CListBoxInsideComboBox()
{
	m_Parent=NULL;
}

CListBoxInsideComboBox::~CListBoxInsideComboBox()
{
}


BEGIN_MESSAGE_MAP(CListBoxInsideComboBox, CWnd)
	//{{AFX_MSG_MAP(CListBoxInsideComboBox)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListBoxInsideComboBox message handlers

void CListBoxInsideComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;	GetClientRect(rect);

	if (rect.PtInRect(point))
	{
		BOOL outside=FALSE;
		int index=((CListBox *)this)->ItemFromPoint(point,outside);
// SAC 6/4/01
		if (!outside && !m_Parent->m_bAllowSelectionOfDisabledItems && !m_Parent->IsItemEnabled(index))
			return;	// don't click there
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}


void CListBoxInsideComboBox::SetParent(CExtendedComboBox *ptr)
{
	m_Parent=ptr;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox - Grey out control background when the data is not editable

HBRUSH CExtendedComboBox::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
   pDC->SetTextColor( GetBEMPUITextColor( (m_iComboMode == CM_SCREEN ?
                                         -1 : BEMPX_GetDataStatus( m_lDBID, m_iDBInstance )) ) );

	// TODO: Change any attributes of the DC here
	if (!m_bEditable)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
	   return buttonBrush;
   }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	return NULL;
	return windowBrush;
}


/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox - OnChar

void CExtendedComboBox::ResetFocus( BOOL prev )
{
   CWnd* pFocus = GetParent()->GetNextDlgTabItem( this, prev );
   if (pFocus != NULL)
   {
      if (pFocus->IsKindOf(RUNTIME_CLASS(CExtendedComboBox)))
         ((CExtendedComboBox*) pFocus)->SetFocus();
      else
         pFocus->SetFocus();
   }
}

UINT CExtendedComboBox::OnGetDlgCode()
{
   return DLGC_WANTMESSAGE;
}

void CExtendedComboBox::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
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
// CExtendedComboBox - Focus Stuff

void CExtendedComboBox::OnKillFocus( CWnd* pNewWnd )
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, NULL, 0 );
//   GetMainFrame()->SetStatusBarStrings( "", 0 );

   CComboBox::OnKillFocus( pNewWnd );
}


void CExtendedComboBox::OnSetFocus( CWnd* pOldWnd )
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
//   GetMainFrame()->SetStatusBarStrings( m_sStatusMsg, m_lDBID );

   CComboBox::OnSetFocus( pOldWnd );
}


/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox - Width Resizing Stuff

int CExtendedComboBox::CalcMaxStringWidth()
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

int CExtendedComboBox::ResizeToFitContent(int nDropDownHeight)
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
// CExtendedComboBox - Display & Update Data Stuff

void CExtendedComboBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here
   OnUpdateData(0,0);
}


BOOL CExtendedComboBox::ObjectTypeIsCompatible( int i1ClassID, int iObjIdx, BEM_ObjType eObjType )  // SAC 6/15/12 - revised to handle objects of multiple classes
{
   int iError, iSV;
	// SAC 6/15/12 - revised to handle an ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
   //long* plObjType = (long*) BEMPX_GetBEMData( m_lObjTypeDBID, iDT, iSV, iError, iObjIdx, eObjType );
   //return (iError >= 0 && plObjType && *plObjType == m_lObjTypeValue);
	if (m_iaObjCompID.GetSize() == 1 && m_iaObjCompID[0] == 0)  // handle situation where m_laObjTypeDBID/Value used for something other than defining object referencing compatibility
		return TRUE;
	BOOL bIncompatEntry = FALSE;
	BOOL bCompatEntry = FALSE;
	for (int iObjCls=0; iObjCls < m_iaObjCompID.GetSize(); iObjCls++)
		if (i1ClassID == m_iaObjCompID[iObjCls])
		{	if (m_laObjTypeDBID[iObjCls] == 0)
				bCompatEntry = TRUE;
			else
			{
	//			long* plObjType = (long*) BEMPX_GetBEMData( m_laObjTypeDBID[iObjCls], iDT, iSV, iError, iObjIdx, eObjType );
	//			if (iError >= 0 && plObjType && *plObjType == m_laObjTypeValue[iObjCls])
				long lObjType = BEMPX_GetInteger( m_laObjTypeDBID[iObjCls], iSV, iError, iObjIdx, eObjType );
				if (iError >= 0 && lObjType == m_laObjTypeValue[iObjCls])
					bCompatEntry = TRUE;
				else if (iError >= 0 && m_laObjTypeValue[iObjCls] == -99)
				{	// SAC 11/8/12 - handle case where the property of the object being loaded has to match a corresponding property in the local/current object
					BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( m_laObjTypeDBID[iObjCls], iError );
					if (pObjTypePropType && !pObjTypePropType->getShortName().isEmpty())
					{	long lLocTypeDBID = BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( m_lDBID ) );			ASSERT( lLocTypeDBID > BEM_COMP_MULT );
						long lLocTypeVal = 0;
						if (lLocTypeDBID > BEM_COMP_MULT && BEMPX_SetDataInteger( lLocTypeDBID, lLocTypeVal, 0 /*default*/, -1 /*iDispDataType*/, m_iDBInstance ))
						{	if (lLocTypeVal == lObjType)
								bCompatEntry = TRUE;
							else
								bIncompatEntry = TRUE;
						}
						else
						{	ASSERT( FALSE );
							bIncompatEntry = TRUE;
						}
					}
					else
					{	ASSERT( FALSE );
						bIncompatEntry = TRUE;
					}
				}
				else // if (iError >= 0 && plObjType && *plObjType != m_laObjTypeValue[iObjCls])
					bIncompatEntry = TRUE;
			}
		}
	return (bCompatEntry ? TRUE : (bIncompatEntry ? FALSE : TRUE));
}


void CExtendedComboBox::LoadObjectNames( int i1ClassID, BOOL /*bLoadAll*/ )
{
   int iNumObjects = BEMPX_GetNumObjects( i1ClassID );

   int iCmbbClass = BEMPX_GetClassID( m_lDBID );
   int iError, iSpecialVal;
   BEMObject* pCurSelObj = NULL;
   // if this combo is for assigning the parent of an EXISTING (and current) component, then set
   // pCurSelObj to be the parent of the current object for which this combo's DBID describes
   if (m_iComboMode == CM_PARENT)
   {
      if (BEMPX_GetArrayID( m_lDBID ) == BEM_PARAM0_PARENT)
      {
         BEMObject* pCurObj = BEMPX_GetObjectByClass( iCmbbClass, iError, m_iDBInstance );
         if (pCurObj && pCurObj->getParent())
            pCurSelObj = pCurObj->getParent();
      }
      // else - the alternative is that this combo assigns the parent of a component which
      //        is in the process of being created - in which case we leave pCurSelObj = NULL
   }
   else
      pCurSelObj = BEMPX_GetObjectPtr( m_lDBID, iSpecialVal, iError, m_iDBInstance );

   // SAC 3/3/99 - added to load only those component names PREVIOUS to the one being edited
   int iUserObjsToLoad = iNumObjects;
   if (m_iComboMode == CM_OBJECT && iCmbbClass == i1ClassID && m_laObjTypeDBID.GetSize() > 0 && m_laObjTypeDBID[0] == 0 && m_laObjTypeValue[0] == -1)  // OK for check to be on first m_lObjTypeDBID/Value only
   {
      if (m_iDBInstance >= 0)
         iUserObjsToLoad = m_iDBInstance;
      else
         iUserObjsToLoad = BEMPX_GetObjectIndex( BEMPX_GetClass( iCmbbClass, iError ) );
   }

   for (int iObj=0; iObj < iUserObjsToLoad; iObj++)
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
      for (int eType=(int) BEMO_RuleLib; eType < (int) BEMO_NumTypes; eType++)
      {
         int iNumObjs = BEMPX_GetNumObjects( i1ClassID, (BEM_ObjType) eType );
         for (int iObj=0; iObj < iNumObjs; iObj++)
         {
            int iErr;
            BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iErr, iObj, (BEM_ObjType) eType );
            if ( (iErr == 0) && (pObj != NULL) &&
                 ( (m_iComboMode == CM_OBJECT && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType ))) ||   // SAC 6/15/12 - revised to handle multiple referenced object types
                   (m_iComboMode == CM_ACTIVE && (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj, (BEM_ObjType) eType )) &&
                    pObj->getUserReferenced() ) ) )
            {
               CString sEntry = pObj->getName().toLatin1().constData();
               sEntry += pszAppend[ eType ];
               AddString( sEntry );

               SetItemData( GetCount() - 1, (DWORD) eType );
            }
         }
      }
   }
}


// SAC 2/1/00 - New CM_SCREEN mode stuff
void CExtendedComboBox::LoadScreenStrings()
{
   ASSERT( m_lDBIDScreenIDArray > 0 );
   long lScreenID = 1;
   long l0ScreenIdx = 0;
   // round 1 simply determines the total number of screens there are
   while (BEMPX_SetDataInteger( m_lDBIDScreenIDArray + l0ScreenIdx, lScreenID )  &&  lScreenID != 0)
      l0ScreenIdx++;
   int iTotNumScreens = l0ScreenIdx;
   
   // round 2 populates the combobox's list
   lScreenID = 1;
   int iComboIdx = 0;
   for (l0ScreenIdx = 0; l0ScreenIdx < iTotNumScreens; l0ScreenIdx++)
   {
      if (BEMPX_SetDataInteger( m_lDBIDScreenIDArray + l0ScreenIdx, lScreenID )  &&  lScreenID > 0)
      {
         CString sItemString;
         CBEMPUIPage* pPage = eScreenData.GetPageByID( lScreenID );
         if (pPage)
            sItemString.Format( "%d of %d  -  %s", l0ScreenIdx+1, iTotNumScreens, ((const char*) pPage->m_sCaption) );
         else
            sItemString.Format( "%d of %d  -  Screen #%d Title", l0ScreenIdx+1, iTotNumScreens, l0ScreenIdx+1 );

         if (l0ScreenIdx < 9)
            sItemString = "  " + sItemString;

         // add item string & data
         AddString( sItemString );
         SetItemData( iComboIdx++, l0ScreenIdx );
      }
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


BOOL CExtendedComboBox::LoadStrings()
{
	CWaitCursor wait;

   SetRedraw( FALSE );
   int iError;

// SAC 6/4/01 - Added code to setup data that will track item (in)compatibility
   if (m_lDBIDCompatItemArray > 0)
   {
      int iCompatArraySize = BEMPX_GetNumPropertyTypeElements( BEMPX_GetClassID( m_lDBIDCompatItemArray ), BEMPX_GetPropertyID( m_lDBIDCompatItemArray ) );

      m_lCompatModVal = (iCompatArraySize < 100 ? 100 : (iCompatArraySize < 1000 ? 1000 : 10000));  // SAC 1/12/05 - Added to prevent "% 100" for arrays exceeding 100 elements

      ASSERT( iCompatArraySize > 0 );
      int iCompatDataType = BEMPX_GetDataType( m_lDBIDCompatItemArray );
      ASSERT( iCompatDataType == BEMP_Int || iCompatDataType == BEMP_Sym );
      long lCompatDefault = 0;  // default to COMPATIBLE

      if (m_dwaCompatItemArray.GetSize() > 0 && m_dwaCompatItemArray.GetSize() != iCompatArraySize)
         m_dwaCompatItemArray.RemoveAll();
      if (m_dwaCompatItemArray.GetSize() != iCompatArraySize)
         m_dwaCompatItemArray.SetSize( iCompatArraySize );

      for (int i=0; i<iCompatArraySize; i++)
      {
         long lVal;
         if (BEMPX_SetDataInteger( m_lDBIDCompatItemArray + i, lVal, lCompatDefault, iCompatDataType, m_iCompatCompInstance ))
            m_dwaCompatItemArray[i] = (DWORD) lVal;
         else
            m_dwaCompatItemArray[i] = (DWORD) lCompatDefault;
      }
   }

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
   //   CArray<BEMSymbol*, BEMSymbol*>* pSymArray = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID, m_iDBInstance );
      BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, m_lDBID, m_iDBInstance );
      if (!pSymDepSet)
         BEMMessageBox( "CExtendedComboBox::LoadStrings(): Error loading symbol data" );
      else
      {
         for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
         {
            long iSymValue;
            QString qstr;
            BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet /*pSymList*/, iSymIdx );   // SAC 3/23/07
            if (qstr.length() > 0)
            {
               AddString( qstr.toLatin1().constData() );
               SetItemData( idx++, (DWORD) iSymValue );
            }
         }
      }
   }

   else if (m_iComboMode == CM_ACTIVE || m_iComboMode == CM_OBJECT)
   {
      int i1ClassID = 0;
      if (m_iComboMode == CM_ACTIVE)
         i1ClassID = BEMPX_GetClassID( m_lDBID );
      else
      {
         m_iCurObjIdx = (m_iDBInstance >= 0 ? m_iDBInstance : BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( m_lDBID ), iError ) ));
      }

      // SAC - 3/11/98 - if this item is editable and another object of this type
      // can be created, then add an item to allow the user to create a new one
      //if (m_bAllowEdits && i1ClassID > 0 && m_bEditable && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
      if (m_bAllowEdits && m_bEditable)   // SAC 6/15/12 replaced above w/ this version since i1ClassID not yet valid when iProp > 0
      {
         int iProp  = BEMPX_GetPropertyID( m_lDBID );
         int iArray = BEMPX_GetArrayID( m_lDBID );
         // if prop == 0 => reserved/custom data => only allow ACTIVE or PARENT (not NEWPAR or NEWCOPY)
         if ( iProp > 0 || iArray == BEM_PARAM0_ACTIVE ||
                           iArray == BEM_PARAM0_PARENT )
         {	int iLoopEnd = (iProp == 0 ? 1 : m_iaObjCompID.GetSize());
				for (int iObjCls=0; iObjCls < iLoopEnd; iObjCls++)		// SAC 6/15/12 - enable multiple object types to be created...
				{	if (iProp > 0)
						i1ClassID = m_iaObjCompID[iObjCls];
			      if (i1ClassID > 0 && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
					{
		            CString sCr8Str = szCr81;
            		BEMClass* pCr8Class = BEMPX_GetClass( i1ClassID, iError );
            		if (pCr8Class)
            		   sCr8Str += pCr8Class->getLongName().toLatin1().constData();
            		else
            		   sCr8Str += "Building Component";
            		//sCr8Str += szCr82;
	         		if (m_iComboMode == CM_ACTIVE)  // SAC 1/3/12 - Added alternative secondary string for "active" component selections (that are not being "applied" to an attribute)
	         		   sCr8Str += szCr82b;
						else
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
      //LoadObjectNames( i1ClassID, (m_iComboMode == CM_OBJECT) );
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

   // SAC 2/1/00 - New CM_SCREEN mode stuff
   else if (m_iComboMode == CM_SCREEN)
      LoadScreenStrings();

   else  // invalid m_iComboMode value
   {
      //ASSERT( FALSE );
      // SAC 3/17/99 - replaced ASSERT above w/ following error message
      CString sErrMsg;
      sErrMsg.Format( "CExtendedComboBox::LoadStrings(), Ctrl ID=%d, DBID=%d:  Incompatible variable type.", GetDlgCtrlID(), m_lDBID );
      BEMMessageBox( sErrMsg );
   }

   SetRedraw( TRUE );

   // Resize dropdown ListBox width if necessary to fit contents of listing
   ResizeToFitContent();

   return TRUE;
}


LRESULT CExtendedComboBox::OnGetDataStatus(WPARAM, LPARAM)
{
   return (long) BEMPX_GetDataStatus( m_lDBID, m_iDBInstance );
}

//LONG CExtendedComboBox::OnGetTextColor(UINT, LONG)
//{
//   return (long) (BEMPX_GetDataStatus( m_lDBID ) + NUM_RESERVED_TEXT_COLORS);
//}


LRESULT CExtendedComboBox::OnGetDBID(WPARAM, LPARAM)
{
   return m_lDBID;
}

LRESULT CExtendedComboBox::OnGetDBInstance(WPARAM, LPARAM)
{
   return m_iDBInstance;
}


LRESULT CExtendedComboBox::OnDisplayData(WPARAM, LPARAM)
{
// SAC 10/13/07 - added logic to prevent calling BEMPX_GetCompIsEditable() w/ a bogus DBID
   m_bEditable = ((m_lDBID < BEM_COMP_MULT || BEMPX_GetCompIsEditable( m_lDBID )) && m_cEditableCondition.MissingOrTrue());

   // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
   BOOL bPerformLoad = TRUE;
   if (m_lDependentDBID > BEM_COMP_MULT)
   {
      long lLastVal = m_lDependentVal;
      if (BEMPX_SetDataInteger( m_lDependentDBID, m_lDependentVal, 0, -1, m_iDBInstance )  &&  lLastVal == m_lDependentVal)
         bPerformLoad = FALSE;
   }

   // Moved LoadStrings() call here in order to ensure that the currently
   // displayed listbox strings are compatible with the dependency restrictions
   // defined in the symbol data
   BOOL loadOK = (bPerformLoad ? LoadStrings() : TRUE);			loadOK;

   SetCurSel( -1 );
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iDBInstance );
   if ( m_lDBID > 0 && m_iDataType >= 0 && eObjType != BEMO_NumTypes &&
        ( BEMPX_GetNumObjects( i1Class, eObjType ) > 0 || m_iComboMode == CM_PARENT ) )
   {
      int sel = -1;
      int iStatus = BEMPX_GetDataStatus( m_lDBID, m_iDBInstance );
      if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
      {
         int iError, iSpecialVal = 0;
         // SAC 2/1/00 - New CM_SCREEN mode stuff
			if ((m_iComboMode == CM_SYMBOL && m_iDataType == BEMP_Sym) || m_iComboMode == CM_SCREEN)
			{	// select string based on symbol VALUE
				long lNewVal = BEMPX_GetInteger( m_lDBID, iSpecialVal, iError, m_iDBInstance );
				if (iError >= 0)
				{	// for now, assume ValLength = 1 => first value (data[0]) is the only value
					for (int i=0; (sel==-1 && i<GetCount()); i++)
						sel = (GetItemData(i) == (DWORD) lNewVal) ? i : -1;
			}	}
         // All other types set data based on matching strings
			else
			{
				CString sSelStr;
				if (m_iComboMode == CM_OBJECT)
				{	// select string based on object name
					BEMObject* pObj = BEMPX_GetObjectPtr( m_lDBID, iSpecialVal, iError, m_iDBInstance );
					if (iError >= 0 && pObj)
					{
						sSelStr = pObj->getName().toLatin1().constData();
						if (pObj->getObjectType() != BEMO_User)
						{
							sSelStr += pszAppend[ (int) pObj->getObjectType() ];
						}
					}
					else if (iError >= 0)
                  sSelStr = szNone;
				}
				else // if ( (m_iComboMode == CM_ACTIVE) || (m_iComboMode == CM_PARENT) )
				{	// select string based on string data
					QString qsStr = BEMPX_GetString( m_lDBID, iSpecialVal, iError, m_iDBInstance );
					if (iError >= 0 && qsStr.length() > 0)
					{
						sSelStr = qsStr.toLatin1().constData();

						// what if current object is from a library??
                  BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( m_lDBID ), iError, m_iDBInstance );
                  if (iError >= 0 && pObj && pObj->getObjectType() != BEMO_User &&
                       // this last part ensures we don't paste trailing "(... Lib)" into NEWPAR selected string
                       (BEMPX_GetPropertyID( m_lDBID ) != 0 || BEMPX_GetArrayID( m_lDBID ) != BEM_PARAM0_NEWPAR) )
                     sSelStr += pszAppend[ (int) pObj->getObjectType() ];
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
      {
         SetCurSel( sel );
// SAC 6/4/01 - Added code to setup data that will track item (in)compatibility
         m_dwCurSelData = GetItemData( sel );
      }

   }

   return 1;
}


static BOOL sbNewRulesetSelected = FALSE;

BOOL CExtendedComboBox::UserSelectedNewRuleset()
{
   sbNewRulesetSelected = TRUE;  // default to TRUE in order to prevent some mishap from missing a ruleset switch
   int iError, iSpecialVal;
//   void* pData = BEMPX_GetBEMData( m_lDBID, iDataType, iSpecialVal, iError, m_iDBInstance );
	long lNewVal = BEMPX_GetInteger( m_lDBID, iSpecialVal, iError, m_iDBInstance );
   if (iError >= 0)
   {
      QString qsCurRuleset = BEMPX_GetSymbolString( (int) lNewVal, m_lDBID, m_iDBInstance );
      CString sCurRuleset = qsCurRuleset.toLatin1().constData();
      CString sSelRuleset;
      GetLBText( GetCurSel(), sSelRuleset );
      sbNewRulesetSelected = (sSelRuleset != sCurRuleset);
   }
   return sbNewRulesetSelected;
}

LRESULT CExtendedComboBox::OnUpdateData( WPARAM, LPARAM )
{
   int iSetDataRetVal = -1;
   BOOL bEvalRules = TRUE;

   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iDBInstance );
   if ( m_lDBID > 0 && m_iDataType >= 0 && eObjType != BEMO_NumTypes &&
        BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
   {
      int iPropID = BEMPX_GetPropertyID( m_lDBID );
      int iArrID  = BEMPX_GetArrayID(    m_lDBID );
      DWORD dwSelData = GetItemData( GetCurSel() );
// SAC 6/4/01 - Code to deal w/ selection of incompatible item
//      int iCompatIdx = (int) dwSelData % BEM_PARAM_MULT;  // item data mod BEM_PARAM_MULT = array index of compat data
// SAC 1/12/05 - Added to prevent "% 100" for arrays exceeding 100 elements
//      int iCompatIdx = (int) dwSelData % 100;  // item data mod 100 = array index of compat data
      int iCompatIdx = (int) dwSelData % m_lCompatModVal;  // item data mod 100 (or 1,000) = array index of compat data

// SAC 6/4/01 - Added code to setup data that will track item (in)compatibility
      if (m_dwCurSelData > 0 && m_dwCurSelData == dwSelData)
         return 1;

      if (!m_bEditable)
      {
         MessageBeep( MB_OK );
         MessageBox( szErrNotEditable, szErrorCaption, MB_ICONSTOP );
         OnDisplayData(0,0);
      }
      else if (!m_bAllowEdits && m_iComboMode != CM_ACTIVE)
      {
         MessageBeep( MB_OK );
         MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
         OnDisplayData(0,0);
      }
      else if ( m_iComboMode != CM_ACTIVE && iArrID != BEM_PARAM0_NEWPAR && iArrID != BEM_PARAM0_NEWCOPY &&
                ObjectIsFromLibrary( m_lDBID ) )
      {
         OnDisplayData(0,0);
      }
      else if ( m_lDBID > 0 && iPropID == 0 &&
                ( iArrID == BEM_PARAM0_NEWPAR  ||
                  iArrID == BEM_PARAM0_NEWCOPY ) )
      {  // Do nothing since this data is only grabbed and used if the user
      }  // chooses to create the new component for which this data is being defined

// SAC 6/4/01 - Code to deal w/ selection of incompatible item
      else if (iCompatIdx > 0 && m_dwaCompatItemArray.GetSize() > 0 && iCompatIdx <= m_dwaCompatItemArray.GetSize() &&
               m_dwaCompatItemArray[iCompatIdx-1] > 0)
      {
         long lCompatErr = (long) m_dwaCompatItemArray[iCompatIdx-1];
         ReportCompatibilityIssue( m_lDBIDCompatError, lCompatErr, m_iCompatCompInstance, m_sCompatRulelist, this );

         OnDisplayData(0,0);
      }

      else
      {
         int iDataType = m_iDataType;

         // First handle selection based on integer value (symbol value)
         // SAC 2/1/00 - New CM_SCREEN mode stuff
         if ( (m_iComboMode == CM_SYMBOL  &&  m_iDataType == BEMP_Sym) || (m_iComboMode == CM_SCREEN) )
         {
            long lNewVal = (long) dwSelData;

            if (m_iDBInstance >= 0)
               BEMPX_SetActiveObjectIndex( i1Class, m_iDBInstance );

            iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*) &lNewVal );
         }
         // Now deal with the selection of "- create new ... -"
         else if (dwSelData > sdwCreateData)
         {
            bEvalRules = FALSE;

            CFrameWnd* pFrame = GetParentFrame();
            if (pFrame)
            {
               CreateComponentInfo createInfo;
					// SAC 6/15/12 - revision to use of sdwCreateData
               //createInfo.m_i1BEMClass        = (int) (dwSelData - sdwCreateData);
               //createInfo.m_lObjTypeDBID      = m_lObjTypeDBID;
               //createInfo.m_lObjTypeValue     = m_lObjTypeValue;
					BOOL bAbortCr8 = FALSE;
					if (dwSelData > (sdwCreateData+100))
					{	// parent or active object selection
               	createInfo.m_i1BEMClass     = (int) (dwSelData - sdwCreateData-100);
               	createInfo.m_lObjTypeDBID   = 0;
               	createInfo.m_lObjTypeValue  = 0;
					}
					else
					{	int iObjClsIdx = dwSelData - sdwCreateData - 1;
						ASSERT( iObjClsIdx >= 0 && m_iaObjCompID.GetSize() > iObjClsIdx );
						if (    iObjClsIdx >= 0 && m_iaObjCompID.GetSize() > iObjClsIdx )
						{	createInfo.m_i1BEMClass     = m_iaObjCompID[    iObjClsIdx ];
               		createInfo.m_lObjTypeDBID   = m_laObjTypeDBID[  iObjClsIdx ];
               		createInfo.m_lObjTypeValue  = m_laObjTypeValue[ iObjClsIdx ];
						}
						else
							bAbortCr8 = TRUE;
					}
					if (!bAbortCr8)
					{	createInfo.m_lAssignmentDBID   = (m_iComboMode == CM_OBJECT) ? m_lDBID : 0;
               	createInfo.m_bEditNewComponent = (m_iComboMode != CM_ACTIVE);
               	createInfo.m_pParentWnd        = GetParent();
               	
               	pFrame->SendMessage( WM_CREATECOMPONENT, (WPARAM) &createInfo );
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
               if ( m_iComboMode != CM_PARENT && iObjFrom != 0 ) // => not user-defined object
                  sSelStr = sSelStr.Left( sSelStr.GetLength() - 12 );

               if (sSelStr.Compare( szNone ) == 0)
                  sSelStr.Empty();

               if (m_iDBInstance >= 0)
                  BEMPX_SetActiveObjectIndex( i1Class, m_iDBInstance );

               iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, iDataType, (void*) ((const char*) sSelStr),
                                               (BEM_ObjType) iObjFrom );

               if (m_iComboMode == CM_ACTIVE)
                  bEvalRules = FALSE;
            }
         }
      }
   }

   if (iSetDataRetVal >= 0)
   {
      // SAC 2/1/00 - New CM_SCREEN mode stuff - Post instead of Send msg to avoid returning to control after its destruction
//      if (m_iComboMode == CM_SCREEN)
      // SAC 3/9/01 - Added flag to cause quick return following update for other scenarios other than just (m_iComboMode == CM_SCREEN)
      if (m_bBailQuicklyFollowingUpdate)
      {
         // Post-processing following mods
         WORD wEval = (bEvalRules ? 1 : 0);
         GetParent()->PostMessage( WM_DATAMODIFIED, wEval, m_lDBID );
         return 1;  // bail out quickly
      }

      // Post-processing following mods
      WORD wEval = (bEvalRules ? 1 : 0);
      GetParent()->SendMessage( WM_DATAMODIFIED, wEval, m_lDBID );

      // redisplay status bar strings
      CFrameWnd* pFrame = GetParentFrame();
      if (pFrame)
         pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
   }
   
   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox - Quick Menu Stuff

void CExtendedComboBox::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      DoQuickMenu();
   else
      CComboBox::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CExtendedComboBox::OnRButtonDown( UINT /*nFlags*/, CPoint /*point*/ )
{
   SetFocus();
   DoQuickMenu();
}

void CExtendedComboBox::DoQuickMenu()
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
   {
      CRect winRect;
      GetWindowRect( winRect );
      QuickMenuInfo qmInfo;
      qmInfo.m_iLeft  = winRect.left;
      qmInfo.m_iTop   = winRect.top;
      qmInfo.m_iRight = winRect.right;
      qmInfo.m_uiItemHelpID  = m_iItemHelpID;
      qmInfo.m_uiTopicHelpID = m_iTopicHelpID;
      qmInfo.m_lDBID  = m_lDBID;
      qmInfo.m_iDBInstance = m_iDBInstance;
      qmInfo.m_bEditable = m_bEditable;
      qmInfo.m_bObjectAssign = (m_iComboMode == CM_OBJECT);
      qmInfo.m_iDBaseType = QMI_DBASETYPE_BEMPROC;
      qmInfo.m_dwFlags = 0;

      pFrame->SendMessage( WM_QUICKMENU, NULL, (LPARAM) &qmInfo );
   }
}


//void CExtendedComboBox::PostNcDestroy()
//{
//	if ( (m_bCreatedByClassName) || (m_bCalledNew) )
//		delete this;
//}


/////////////////////////////////////////////////////////////////////////////
// CExtendedComboBox - Diagnostics

#ifdef _DEBUG
void CExtendedComboBox::AssertValid() const
{
	CComboBox::AssertValid();
}

void CExtendedComboBox::Dump(CDumpContext& dc) const
{
	CComboBox::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CExtendedComboBox::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CComboBox::OnHelpInfo(pHelpInfo);
}
