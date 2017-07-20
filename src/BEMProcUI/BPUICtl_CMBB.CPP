// BPUICtl_CMBB.CPP  :  Contains CComboBoxCtl routines
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
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "Screens.h"
#include "BPUICtl_Cmbb.h" 
#include "BEMProcUIX.h"

#include <afxtempl.h>
#include "memLkRpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// SAC 7/30/02 - Added in the process of implementing new EEM run mechansim - causes resetting of BEMProc symbol list upon each refresh of combobox

static CArray<long, long> slaDBID_RefreshSymProp;
static CArray<long, long> slaDBID_RefreshSymProp_NumItems;
static CArray<long, long> slaDBID_RefreshSymProp_Strings;
static CArray<long, long> slaDBID_RefreshSymProp_Allow;
static CArray<long, long> slaDBID_RefreshSymProp_Values;

static inline int DBIDRequiresSymbolListRefresh( long lDBID )
{
   int iSize = slaDBID_RefreshSymProp.GetSize();
   for (int i=0; i<iSize; i++)
      if (lDBID == slaDBID_RefreshSymProp[i])
         return i;
   return -1;
}

void BEMPUIX_AddAutoSymbolListRefreshDBIDs( long lDBID_Prop, long lDBID_NumItems, long lDBID_Strings, long lDBID_Allow, long lDBID_Values )
{
   if (DBIDRequiresSymbolListRefresh( lDBID_Prop ) < 0)  // make sure it is not already in the list
   {
      slaDBID_RefreshSymProp.Add(          lDBID_Prop     );
      slaDBID_RefreshSymProp_NumItems.Add( lDBID_NumItems );
      slaDBID_RefreshSymProp_Strings.Add(  lDBID_Strings  );
      slaDBID_RefreshSymProp_Allow.Add(    lDBID_Allow    );
      slaDBID_RefreshSymProp_Values.Add(   lDBID_Values   );
   }
}

// Return Value:   -1 => SymbolList does not require resetting
//                  0 => SymbolList successfully reset
//                  1 => Error Overwriting SymbolList
//                  2 => Error creating new SymbolDepList
//                  3 => Error retrieving NumItems
//                  4 => Error retrieving Allow flag value
//                  5 => Error retrieving symbol value or string
//                  6 => Error adding symbol to list
static int RefreshSymbolListIfNecessary( long lDBID, int iDBInstance )
{
   int iRSPIdx = DBIDRequiresSymbolListRefresh( lDBID );
   int iRetVal = (iRSPIdx >= 0 ? 0 : -1);
   if (iRetVal == 0)
   {
      void* pSL = BEMPX_OverwriteSymbolList( lDBID );
      if (pSL == NULL)
         iRetVal = 1;
      else
      {
         void* pSDL = BEMPX_AddSymbolDepList( pSL, 0, 0, -1.0, 0, -1.0 );
         if (pSDL == NULL)
            iRetVal = 2;
         else
         {
            long lDBID_RSP_NumItems  = slaDBID_RefreshSymProp_NumItems[ iRSPIdx ];
            long lDBID_RSP_Strings   = slaDBID_RefreshSymProp_Strings[  iRSPIdx ];
            long lDBID_RSP_Allow     = slaDBID_RefreshSymProp_Allow[    iRSPIdx ];
            long lDBID_RSP_Values    = slaDBID_RefreshSymProp_Values[   iRSPIdx ];

            long lNumItems;
            if (!BEMPX_SetDataInteger( lDBID_RSP_NumItems, lNumItems, 0, -1, iDBInstance ))
               iRetVal = 3;
            else
               for (int i=0; (iRetVal == 0 && i<lNumItems); i++)
               {
                  long lAllow = 1;
                  if (lDBID_RSP_Allow > 0)
                  {
                     if (!BEMPX_SetDataInteger( lDBID_RSP_Allow + i, lAllow, 0, -1, iDBInstance ))
                        iRetVal = 4;
                  }

                  if (iRetVal == 0 && lAllow > 0)
                  {
                     long lValue = i+1;  // default value is 1-based array index in item array
                     CString sString;
                     if ((lDBID_RSP_Values > 0 && !BEMPX_SetDataInteger( lDBID_RSP_Values + i, lValue, 0, -1, iDBInstance ))  ||
                         !BEMPX_SetDataString( lDBID_RSP_Strings + i, sString, FALSE, 0, -1, iDBInstance ) )
                        iRetVal = 5;
                     else if (!BEMPX_AddSymbol( pSDL, lValue, sString ))
                        iRetVal = 6;
                  }
               }
         }
      }
   }

   return iRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

static CArray<long, long> slaDBID_AutoComplete;

void BEMPUIX_SetAutoCompleteComboboxDBIDs( int iNumDBIDs, long* laAutoCompleteDBIDs )
{
   slaDBID_AutoComplete.RemoveAll();
   if (iNumDBIDs > 0)
   {
      slaDBID_AutoComplete.SetSize( iNumDBIDs );
      for (int i=0; i<iNumDBIDs; i++)
         slaDBID_AutoComplete[i] = laAutoCompleteDBIDs[i];
   }
}

BOOL DBIDIsAutoComplete( long lDBID )
{
   for (int i=0; i < slaDBID_AutoComplete.GetSize(); i++)
      if (lDBID == slaDBID_AutoComplete[i])
         return TRUE;
   return FALSE;
}

/////////////////////////////////////////////////////////////////////////////


// String for indicating no object assigned
static char BASED_CODE szNone[] = "- none -";
static char BASED_CODE szBaselineRun[] = "- baseline run -";  // SAC 7/30/02

// Data and strings for accessing ability to create a new component
// SAC 6/15/12 - revision to use of sdwCreateData:
//						cmbbData = sdwCreateData + (1 - 5(or up to 100)) => value above sdwCreateData = index into array of m_saObjCompID to be created
//						cmbbData > sdwCreateData + 100  =>  class ID of object to be created = cmbbData - (sdwCreateData + 100)
static DWORD sdwCreateData = 999999000;
static char BASED_CODE szCr81[] = "- create new ";
static char BASED_CODE szCr8Imp[] = "- create/import ";  // SAC 9/19/13
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

// SAC 4/9/02 - Added #defines to track new bitwise flag values that toggle on/off availability of certain list options
#define  PREVENT_ENTRY_NONE                      0x0001
#define  PREVENT_ENTRY_CREATE                    0x0002
#define  BASELINERUN_INPLACEOF_NONE              0x0004    // SAC 7/30/02

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

	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditUpdate)  // SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

   ON_MESSAGE(WM_GETDATASTATUS, OnGetDataStatus)
//   ON_MESSAGE(WM_GETTEXTCOLOR,  OnGetTextColor)
   ON_MESSAGE(WM_GETCTRLDBID,   OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)

	ON_WM_HELPINFO()
END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////

// SAC 8/1/02 - Added new DBID & Instance to support referenced components (lDBID2)
void CComboBoxCtl::ResolveUseDBValues()
{
   if (m_lDBID2 < BEM_COMP_MULT)
   {
      m_lUseDBID       = m_lDBID      ;
      m_iUseDBInstance = m_iDBInstance;
   }
   else
   {
      m_lUseDBID       = 0;
      m_iUseDBInstance = 0;

		int iDT = BEMPX_GetDataType( m_lDBID );
		BEMObject* pObj = NULL;
		if (iDT == BEMP_Obj && BEMPX_GetObject( m_lDBID, pObj, -1, m_iDBInstance ) &&
				pObj && pObj->getClass())
		{	
         m_iUseDBInstance = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
         if (m_iUseDBInstance >= 0)
            m_lUseDBID = m_lDBID2;
		}
   }
}


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
                                  UINT /*uiCtrlID*/ )
{
   SetFont( GetWizFont(m_iFont), TRUE );

//   SetItemHeight( -1, 16 );  // FontY( (int) (((double) m_iClosedHt) * dYScale) ) );

   if (m_lUseDBID == 0)  // SAC 8/1/02 - Install defaults if m_lUseDBID invalid
   {
      m_bEditable = FALSE;
      m_bAutoComplete = TRUE;
      m_bNone = FALSE;
      m_iComboMode = CM_OBJECT;
      m_bBailQuicklyFollowingUpdate = FALSE;
   }
   else
   {
// SAC 10/13/07 - added logic to prevent calling BEMPX_GetCompIsEditable() w/ a bogus DBID
      m_bEditable = ((m_lUseDBID < BEM_COMP_MULT || BEMPX_GetCompIsEditable( m_lUseDBID )) && m_cEditableCondition.MissingOrTrue());

      m_bAutoComplete = TRUE;   // SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

      // Set m_iComboMode
      int iPropID = BEMPX_GetPropertyID( m_lUseDBID );
      int iArrID  = BEMPX_GetArrayID(    m_lUseDBID );

      m_bNone = FALSE;
      // SAC 2/1/00 - New CM_SCREEN mode stuff
      if (m_lDBIDScreenIDArray > 0)
         m_iComboMode = CM_SCREEN;
      else if ( m_lUseDBID > 0 && iPropID == 0 )
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
//            m_bNone = TRUE;     - SAC 11/20/13 - prevent "none" from appearing in Parent lists
         }
         else if (iArrID == BEM_PARAM0_PARENT)
         {
            m_iComboMode = CM_PARENT;
//            m_bNone = TRUE;     - SAC 11/20/13 - prevent "none" from appearing in Parent lists
         }
      }
      else if (m_iDataType == BEMP_Obj)
      {
         m_iComboMode = CM_OBJECT;
         m_bNone = TRUE;

         int iError, iObjCls;
      	// SAC 6/15/12 - revised to handle an ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
      	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( m_lUseDBID, iError );
      	if (iError == 0 && pPropType)
				for (iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)
      	   {	if (pPropType->getObj1ClassIdx(iObjCls) > 0 || pPropType->getObjTypeValue(iObjCls) != 0)
					{	m_iaObjCompID.Add(    pPropType->getObj1ClassIdx(iObjCls) );
			         m_laObjTypeDBID.Add(  pPropType->getObjTypeDBID( iObjCls) ); 
			         m_laObjTypeValue.Add( pPropType->getObjTypeValue(iObjCls) );
					}
				}
      	ASSERT( m_iaObjCompID.GetSize() > 0 );
#if 0	//	eps 8/21/12 - no longer needed, see LoadStrings() line 976
x#ifdef _DEBUG
x				for (iObjCls=0; iObjCls<m_iaObjCompID.GetSize(); iObjCls++)
x				{	for (int i2ObjCls=iObjCls+1; i2ObjCls<m_iaObjCompID.GetSize(); i2ObjCls++)
x						ASSERT( m_iaObjCompID[iObjCls] != m_iaObjCompID[i2ObjCls] );
x						// further edits required to properly identify the TYPE of component the user wishes to create - otherwise, object creation entries will show duplicate class types
x				}
x#endif
#endif

// SAC 3/3/99 - UGLY (but functional) - this is to prevent EEMRun:OperateOn list from containing "- none -"
         if (m_laObjTypeDBID.GetSize() > 0 && m_laObjTypeDBID[0] == 0 && m_laObjTypeValue[0] == -1 && !(m_dwListOptionFlag & BASELINERUN_INPLACEOF_NONE))  // SAC 7/30/02
            m_bNone = FALSE;
// SAC 8/7/00 - Added code to prevent "- none -" from appearing in lists where the input is required
         else
         {
            int iCompDataType = BEMPX_GetCompDataType( m_lUseDBID );
            if (iCompDataType == BEMD_Compulsory || iCompDataType == BEMD_Required)
               m_bNone = FALSE;
         }
      }
      else if (m_iDataType == BEMP_Sym)
         m_iComboMode = CM_SYMBOL;
      else if (m_iDataType == BEMP_Int)  // SAC 3/25/02 - Added in order to accomodate multiple Screen ID combos
         m_iComboMode = CM_SCREEN;
      else
      {
         //ASSERT( FALSE );
         // SAC 3/17/99 - replaced ASSERT above w/ following error message
         CString sErrMsg;
         sErrMsg.Format( "CComboBoxCtl::GenericCreate(), Ctrl ID=%d, DBID=%d:  Incompatible variable type.", GetDlgCtrlID(), m_lUseDBID );
         BEMMessageBox( sErrMsg );
      }

      // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options
      if (m_bNone && m_dwListOptionFlag & PREVENT_ENTRY_NONE)
         m_bNone = FALSE;

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
}


BOOL CComboBoxCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits, long lDBIDOffset,
                           BOOL bTabbedDlgShift, BOOL scaleToSysFont, BOOL scaleToScreenRes, long lDBIDScreenIDArray,
                           UINT uiTopicHelp, UINT uiItemHelp )
{
   ASSERT( pControl );

// SAC 8/1/02 - Moved setting of m_lDBID & m_iDBInstance up here from below, added setting of m_lDBID2 and func call to resolve these to UseDB* values
   m_lDBID          = pControl->m_lDBID + lDBIDOffset;
   m_iDBInstance    = pControl->m_iDBInstance;  // SAC 3/3/99
   m_lDBID2         = pControl->m_lDBID2;
   ResolveUseDBValues();

// SAC - 8/25/98
//   DWORD winStyle = WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL;
// SAC 6/1/01
   DWORD winStyle = ( DBIDIsAutoComplete( m_lUseDBID ) ?
                        WS_CHILD|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWN    |CBS_AUTOHSCROLL  :
                        WS_CHILD|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL );

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
      m_iDataType      = BEMPX_GetDataType( m_lUseDBID );
      m_iFont          = pControl->m_iFont;
      m_iClosedHt      = (int) (pControl->m_lValue % 100);  // SAC 4/9/02 - Added mod 100 to enable value to also carry other information
      m_iOriginalWidth = size.cx;
      m_bCalledNew     = TRUE;
      m_sStatusMsg     = pControl->m_sStatusMsg;

      m_iItemHelpID    = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lUseDBID ) : uiItemHelp);
      m_iTopicHelpID   = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lUseDBID ) : uiTopicHelp);

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

      m_dwListOptionFlag = (DWORD) (pControl->m_lValue / 100);  // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options

      GenericCreate( scaleToScreenRes, yScale, winStyle, pControl->m_uiCtrlID );
   }
   return retVal;
}


BOOL CComboBoxCtl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
                				int iFont, int iClosedHt, const char FAR* lpMsg, 
                				long lDBID, int iDT, BOOL scaleToSysFont, BOOL scaleToScreenRes,
                				UINT uiIHelpID, UINT uiTHelpID, long lObjTypeDBID, long lObjTypeValue,
                           int iDBInstance )
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

   BOOL retVal = CComboBox::Create( dwStyle, CRect(pos, size), pParentWnd, nID );
   if (retVal)
   {
      m_lDBID          = lDBID;
      m_iDBInstance    = iDBInstance;  // SAC 3/3/99

      m_lDBID2         = 0;  // SAC 8/1/02
      ResolveUseDBValues();

      m_iDataType  	  = (iDT >= 0) ? iDT : BEMPX_GetDataType( m_lUseDBID );
      m_iFont          = iFont;
      m_iClosedHt      = iClosedHt;
      m_iOriginalWidth = size.cx;
      m_bCalledNew     = TRUE;
      m_sStatusMsg     = lpMsg;

      m_iItemHelpID    = (uiIHelpID > 0) ? uiIHelpID : BEMPX_GetItemHelpID(  m_lUseDBID );
      m_iTopicHelpID   = (uiTHelpID > 0) ? uiTHelpID : BEMPX_GetTopicHelpID( m_lUseDBID );

      m_bUnused        = FALSE;

		// SAC 6/15/12 - implement as ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
      //m_lObjTypeDBID  = lObjTypeDBID;
      //m_lObjTypeValue = lObjTypeValue;
		ASSERT( lObjTypeDBID == 0 && lObjTypeValue == 0 );  // if assert thrown, need to deal w/ scenario where object assignment DBID/Value passed in and not initialized based on PropertyType members
		lObjTypeDBID;		lObjTypeValue;

      m_bAllowEdits = TRUE;

      // SAC 2/1/00 - New CM_SCREEN mode stuff
      m_lDBIDScreenIDArray = 0;

      // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
      m_lDependentDBID = 0;
      m_lDependentVal  = -1;

      m_dwListOptionFlag = 0;  // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options

      GenericCreate( scaleToScreenRes, yScale, dwStyle, nID );
   }
   return retVal;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxCtl - Grey out control background when the data is not editable

HBRUSH CComboBoxCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
   pDC->SetTextColor( GetBEMPUITextColor( (m_iComboMode == CM_SCREEN ?
                                         -1 : BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance )) ) );

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
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, NULL, 0 );
//   GetMainFrame()->SetStatusBarStrings( "", 0 );

   CComboBox::OnKillFocus( pNewWnd );
}


void CComboBoxCtl::OnSetFocus( CWnd* pOldWnd )
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//   GetMainFrame()->SetStatusBarStrings( m_sStatusMsg, m_lUseDBID );

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
	//		{	long* plObjType = (long*) BEMPX_GetBEMData( m_laObjTypeDBID[iObjCls], iDT, iSV, iError, iObjIdx, eObjType );
	//			if (iError >= 0 && plObjType && *plObjType == m_laObjTypeValue[iObjCls])
			{	long lObjType = BEMPX_GetInteger( m_laObjTypeDBID[iObjCls], iSV, iError, iObjIdx, eObjType );
				if (iError >= 0 && lObjType == m_laObjTypeValue[iObjCls])
					bCompatEntry = TRUE;
				else if (iError >= 0 && m_laObjTypeValue[iObjCls] == -99)
				{	// SAC 11/8/12 - handle case where the property of the object being loaded has to match a corresponding property in the local/current object
					BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( m_laObjTypeDBID[iObjCls], iError );
					if (pObjTypePropType && !pObjTypePropType->getShortName().isEmpty())
					{	long lLocTypeDBID = BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( m_lUseDBID ) );			ASSERT( lLocTypeDBID > BEM_COMP_MULT );
						long lLocTypeVal = 0;
						if (lLocTypeDBID > BEM_COMP_MULT && BEMPX_SetDataInteger( lLocTypeDBID, lLocTypeVal, 0 /*default*/, -1 /*iDispDataType*/, m_iUseDBInstance ))
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

   int iCmbbClass = BEMPX_GetClassID( m_lUseDBID );
   int iError, iSpecialVal;
   BEMObject* pCurSelObj = NULL;
   // if this combo is for assigning the parent of an EXISTING (and current) component, then set
   // pCurSelObj to be the parent of the current object for which this combo's DBID describes
   if (m_iComboMode == CM_PARENT)
   {
      if (BEMPX_GetArrayID( m_lUseDBID ) == BEM_PARAM0_PARENT)
      {
         BEMObject* pCurObj = BEMPX_GetObjectByClass( iCmbbClass, iError, m_iUseDBInstance );
         if (pCurObj && pCurObj->getParent())
            pCurSelObj = pCurObj->getParent();
      }
      // else - the alternative is that this combo assigns the parent of a component which
      //        is in the process of being created - in which case we leave pCurSelObj = NULL
   }
   else
   //   pCurSelObj = (BEMObject*) BEMPX_GetBEMData( m_lUseDBID, iDataType, iSpecialVal, iError, m_iUseDBInstance );
      pCurSelObj = BEMPX_GetObjectPtr( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );

   // SAC 3/3/99 - added to load only those component names PREVIOUS to the one being edited
   int iUserObjsToLoad = iNumObjects;
   // SAC 6/22/04 - added new variable to prevent the loading of the currently active component
   int iDontLoadObjIdx = -1;
//   if (m_iComboMode == CM_OBJECT && iCmbbClass == i1ClassID && m_lObjTypeDBID == 0 && m_lObjTypeValue == -1)
   if (m_iComboMode == CM_OBJECT && iCmbbClass == i1ClassID && m_laObjTypeDBID.GetSize() > 0 && m_laObjTypeDBID[0] == 0 && m_laObjTypeValue[0] != 0)  // probably OK to only check first m_lObjTypeDBID
   {
      if (m_laObjTypeValue[0] == -1)
      {
         if (m_iUseDBInstance >= 0)
            iUserObjsToLoad = m_iUseDBInstance;
         else
            iUserObjsToLoad = BEMPX_GetObjectIndex( BEMPX_GetClass( iCmbbClass, iError ) );
      }
      else if (m_laObjTypeValue[0] == -2)  // SAC 6/22/04
      {
         if (m_iUseDBInstance >= 0)
            iDontLoadObjIdx = m_iUseDBInstance;
         else
            iDontLoadObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( iCmbbClass, iError ) );
      }
   }

   for (int iObj=0; iObj < iUserObjsToLoad; iObj++)
   {
      BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj );
      BOOL bLoadIt = FALSE;
//      if ( (iError == 0) && pObj )
      if ( iError == 0  &&  pObj  &&  iObj != iDontLoadObjIdx )  // SAC 6/22/04
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
                          (m_laObjTypeDBID.GetSize() == 0 || ObjectTypeIsCompatible( i1ClassID, iObj )) ) );   // SAC 6/15/12 - revised to handle multiple referenced object types
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

// SAC 9/19/13 - REMOVED rule & user library items from miscellaneous comboboxes
//	   if (m_iComboMode != CM_PARENT)
//	   {
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
//	                    pObj->getUserReferenced() ) ) )
//	            {
//	               CString sEntry = pObj->getName();
//	               sEntry += pszAppend[ eType ];
//	               AddString( sEntry );
//	
//	               SetItemData( GetCount() - 1, (DWORD) eType );
//	            }
//	         }
//	      }
//	   }
}


// SAC 2/1/00 - New CM_SCREEN mode stuff
void CComboBoxCtl::LoadScreenStrings()
{
// SAC 3/25/02 - Replaced ASSERT() w/ if statement to enable Screen ID combos for multiple components, only one of which should be accessible at a time
//   ASSERT( m_lDBIDScreenIDArray > 0 );
   if (m_lDBIDScreenIDArray < 1)
   {
      AddString( "n/a" );
      SetItemData( 0, 0 );
   }
   else
   {
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
               sItemString.Format( "%d of %d  -  %s", l0ScreenIdx+1, iTotNumScreens, pPage->m_sCaption );
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

   SetRedraw( FALSE );

   ResetContent();
   int idx = 0;

   if (m_bNone)
   {
//      AddString( szNone );
      AddString( ((m_dwListOptionFlag & BASELINERUN_INPLACEOF_NONE) ? szBaselineRun : szNone) );  // SAC 7/30/02
      SetItemData( GetCount() - 1, 0 );
   }

   if (m_iComboMode == CM_SYMBOL)
   {
      int iNumSyms;
//      CArray<BEMSymbol*, BEMSymbol*>* pSymArray = BEMPX_GetSymbolListPointer( iNumSyms, m_lUseDBID, m_iUseDBInstance );
		BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, m_lUseDBID, m_iUseDBInstance );
      if (!pSymDepSet)
		{	//BEMMessageBox( "CComboBoxCtl::LoadStrings(): Error loading symbol data" );
			CString sErrMsg;	QString sObjProp;		// SAC 11/18/13 - more informative error messages
			BEMPX_DBIDToDBCompParamString( m_lUseDBID, sObjProp, false /*bLongNames*/ );
			sErrMsg.Format( "Error loading enumeration list for %s.\n(CComboBoxCtl::LoadStrings - Ctrl ID=%d)", sObjProp.toLatin1().constData(), GetDlgCtrlID() );
			BEMMessageBox( sErrMsg );
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

   else if (m_iComboMode == CM_ACTIVE || m_iComboMode == CM_OBJECT)
   {
      int i1ClassID = 0;
      int iError;
      if (m_iComboMode == CM_ACTIVE)
         i1ClassID = BEMPX_GetClassID( m_lUseDBID );
      else
      {
         m_iCurObjIdx = (m_iUseDBInstance >= 0 ? m_iUseDBInstance : BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( m_lUseDBID ), iError ) ));
      }

      // SAC - 3/11/98 - if this item is editable and another object of this type
      // can be created, then add an item to allow the user to create a new one
      //if ( m_bAllowEdits && i1ClassID > 0 && m_bEditable &&
      //     // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options
      //     !(m_dwListOptionFlag & PREVENT_ENTRY_CREATE) && BEMPX_CanCreateAnotherUserObject( i1ClassID ) )
      if ( m_bAllowEdits && m_bEditable &&   // SAC 6/15/12 replaced above w/ this version since i1ClassID not yet valid when iProp > 0
           // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options
           !(m_dwListOptionFlag & PREVENT_ENTRY_CREATE) )
      {
         int iProp  = BEMPX_GetPropertyID( m_lUseDBID );
         int iArray = BEMPX_GetArrayID( m_lUseDBID );
         // if prop == 0 => reserved/custom data => only allow ACTIVE or PARENT (not NEWPAR or NEWCOPY)
         if ( iProp > 0 || iArray == BEM_PARAM0_ACTIVE ||
                           iArray == BEM_PARAM0_PARENT )
         {	int iLoopEnd = (iProp == 0 ? 1 : m_iaObjCompID.GetSize());
				//	multiple class IDs are allowed - but we want only 1 occurrence of each class to have a "- create ..." entry added to the list for
	// SAC 9/19/13 - revised creation list population to allow for MULTIPLE create entries for each referenced class -AND- specify the Type dependence for each reference
	//						w/out this update, object creation is hard-wired to create an object of only the first compatible type defined...
	//			CArray<int> caClassIds;
	//			caClassIds.SetSize( iLoopEnd);
				CString sLastCr8Str;
		      int iLast1ClassID = 0;
				for (int iObjCls=0; iObjCls < iLoopEnd; iObjCls++)		// SAC 6/15/12 - enable multiple object types to be created...
				{	if (iProp > 0)
						i1ClassID = m_iaObjCompID[iObjCls];
	//				BOOL bFoundOne = FALSE;
	//				for (int iCI = 0; iCI < caClassIds.GetSize(); ++iCI)
	//					if (i1ClassID == caClassIds[iCI])
	//						bFoundOne = TRUE;
	//				if (bFoundOne == FALSE)
	//				{
	//					caClassIds.Add(i1ClassID);

				// SAC 9/4/15 - added code to check w/ parent frame before contionuing to facilitate object creation (to enable product-specific restrictions)
						bool bOKToCr8 = true;		// SAC 11/11/15 - new variable to avoid resetting i1ClassID which screws things up below the creation code
						if (i1ClassID > 0)
						{	CFrameWnd* pFrame = GetParentFrame();
							if (pFrame && pFrame->SendMessage( WM_CHECKCOMPAT, 0, i1ClassID ) == 0)
								//i1ClassID = 0;		// indicates new component should NOT be created
								bOKToCr8 = false;		// SAC 11/11/15
						}
						if (bOKToCr8 && i1ClassID > 0 && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
						{
		            	//CString sCr8Str = szCr81;
		            	CString sCr8Typ, sCr8Str = (CompatibleLibraryObjectExists( i1ClassID ) ? szCr8Imp : szCr81);  // SAC 9/19/13

					// add specification of the TYPE of this object that can be referenced by this property - SAC 9/19/13
							if (iProp > 0 && m_laObjTypeDBID.GetSize() > iObjCls && m_laObjTypeDBID[iObjCls] > 0)
							{	sCr8Typ.Empty();
								if (m_laObjTypeValue[iObjCls] == -99)
								{	// load the compatible type string based on the Type of this LOCAL object (used in syncing day/week/annual schedule types
									BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( m_laObjTypeDBID[iObjCls], iError );				ASSERT( pObjTypePropType );
									if (pObjTypePropType && !pObjTypePropType->getShortName().isEmpty())
									{	long lLocTypeDBID = BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( m_lUseDBID ) );		ASSERT( lLocTypeDBID > BEM_COMP_MULT );
										if (lLocTypeDBID > BEM_COMP_MULT)
										{	VERIFY( BEMPX_SetDataString( lLocTypeDBID, sCr8Typ, FALSE, 0, m_iUseDBInstance ) );									ASSERT( !sCr8Typ.IsEmpty() );
										}
									}
								}
								else
								{	// load string describing Type of object that is compatible w/ this reference
									// 	(get the symbol string corresponding to this value (regardless of what dependency list it is in))
						//			sCr8Typ = BEMPX_GetSymbolString( m_laObjTypeValue[iObjCls], m_laObjTypeDBID[iObjCls], -1, BEMO_User, -1,
						//															FALSE /*bOnlyFromCurrentSymDepSet*/ );														//ASSERT( !sCr8Typ.IsEmpty() ); - may not be dependent on enumeration property...
									QString qsSymStr = BEMPX_GetSymbolString(	m_laObjTypeValue[iObjCls], m_laObjTypeDBID[iObjCls], -1, BEMO_User, -1,
																							FALSE /*bOnlyFromCurrentSymDepSet*/ );												//ASSERT( !sCr8Typ.IsEmpty() ); - may not be dependent on enumeration property...
									sCr8Typ = qsSymStr.toLatin1().constData();
								}
								if (!sCr8Typ.IsEmpty() && (CompatibleLibraryObjectExists( i1ClassID ) || sCr8Typ.CompareNoCase("New")))  // SAC 7/19/17 - prevent item string "- Create new New ... (Res tic #861)
								{	sCr8Str += sCr8Typ;
									sCr8Str += ' ';
								}
							}

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

							if ( sLastCr8Str.IsEmpty() ||   // SAC 7/19/17 - avoid consecutive identical selections (Res tic #861)
								  (sLastCr8Str.Compare( sCr8Str ) && (iLast1ClassID != i1ClassID || !sCr8Typ.IsEmpty())) )
            			{	AddString( sCr8Str );
								// SAC 6/15/12 - revision to use of sdwCreateData
   	         			//SetItemData( GetCount() - 1, sdwCreateData+i1ClassID );
      	      			SetItemData( GetCount() - 1, (iProp > 0 ? sdwCreateData+1+iObjCls : sdwCreateData+100+i1ClassID) );
      	      			sLastCr8Str = sCr8Str;
      	      			iLast1ClassID = i1ClassID;
      	      		}
						}
	//				}
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
      int i1ClassID = BEMPX_GetClassID( m_lUseDBID );
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

   // SAC 2/1/00 - New CM_SCREEN mode stuff
   else if (m_iComboMode == CM_SCREEN)
      LoadScreenStrings();

   else  // invalid m_iComboMode value
   {
      //ASSERT( FALSE );
      // SAC 3/17/99 - replaced ASSERT above w/ following error message
		CString sErrMsg;	QString sObjProp;		// SAC 11/18/13 - more informative error messages
		BEMPX_DBIDToDBCompParamString( m_lUseDBID, sObjProp, false /*bLongNames*/ );
      //sErrMsg.Format( "CComboBoxCtl::LoadStrings(), Ctrl ID=%d, DBID=%d:  Incompatible variable type.", GetDlgCtrlID(), m_lUseDBID );
      sErrMsg.Format( "Property %s (DBID %d) not compatible with dropdown list control.\n(CComboBoxCtl::LoadStrings() - Ctrl ID=%d)", sObjProp.toLatin1().constData(), m_lUseDBID, GetDlgCtrlID() );
      BEMMessageBox( sErrMsg );
   }

   SetRedraw( TRUE );

   // Resize dropdown ListBox width if necessary to fit contents of listing
   ResizeToFitContent();

   return TRUE;
}


LONG CComboBoxCtl::OnGetDataStatus(UINT, LONG)
{
   return (long) BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
}

//LONG CComboBoxCtl::OnGetTextColor(UINT, LONG)
//{
//   return (long) (BEMPX_GetDataStatus( m_lUseDBID ) + NUM_RESERVED_TEXT_COLORS);
//}


LONG CComboBoxCtl::OnGetDBID(UINT, LONG)
{
   return m_lUseDBID;
}

LONG CComboBoxCtl::OnGetDBInstance(UINT, LONG)
{
   return m_iUseDBInstance;
}


LONG CComboBoxCtl::OnDisplayData(UINT, LONG)
{
   ResolveUseDBValues();  // SAC 8/1/02 - reset UseDB* values upon each display in case referenced component has changed

// SAC 10/7/04 - Added code to prevent problems when # components < 1
   int i1Class = BEMPX_GetClassID( m_lUseDBID );

   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iUseDBInstance );
   int iNumComps = (i1Class > 0 ? BEMPX_GetNumObjects( i1Class, eObjType ) : 0);
   if (iNumComps < 1)
   {
      ResetContent();
      return 1;
   }
      
      
// SAC 10/13/07 - added logic to prevent calling BEMPX_GetCompIsEditable() w/ a bogus DBID
   m_bEditable = ((m_lUseDBID < BEM_COMP_MULT || BEMPX_GetCompIsEditable( m_lUseDBID )) && m_cEditableCondition.MissingOrTrue());

   // SAC 3/10/01 - Added to prevent excessive list re-loading for combos w/ very long lists
   BOOL bPerformLoad = TRUE;
//   if (m_lDependentDBID > 0)
// SAC 7/30/02 - Revised the above code to handle new automatic SymbolList resetting
   int iRSLRetVal = RefreshSymbolListIfNecessary( m_lUseDBID, m_iUseDBInstance );
   ASSERT( iRSLRetVal < 1 );
   if (iRSLRetVal == -1 && m_lDependentDBID > BEM_COMP_MULT)  // iRSLRetVal == 0 => SymbolList was reset => we need to reload strings
   {
      long lLastVal = m_lDependentVal;
      if (BEMPX_SetDataInteger( m_lDependentDBID, m_lDependentVal, 0, -1, m_iDBInstance )  &&  lLastVal == m_lDependentVal)
         bPerformLoad = FALSE;
   }

   // Moved LoadStrings() call here in order to ensure that the currently
   // displayed listbox strings are compatible with the dependency restrictions
   // defined in the symbol data
   BOOL loadOK = (bPerformLoad ? LoadStrings() : TRUE);		loadOK;

   SetCurSel( -1 );
   if ( m_lUseDBID > 0 && m_iDataType >= 0 && eObjType != BEMO_NumTypes &&
        ( iNumComps /*BEMPX_GetNumObjects( i1Class, eObjType )*/ > 0 || m_iComboMode == CM_PARENT ) )
   {
      int sel = -1;
      int iStatus = BEMPX_GetDataStatus( m_lUseDBID, m_iUseDBInstance );
      if (iStatus > BEMS_Undefined && iStatus < BEMS_NumTypes)
      {
         int iError, iSpecialVal = 0;
         // SAC 2/1/00 - New CM_SCREEN mode stuff
			if ((m_iComboMode == CM_SYMBOL && m_iDataType == BEMP_Sym) || m_iComboMode == CM_SCREEN)
			{	// select string based on symbol VALUE
				long lNewVal = BEMPX_GetInteger( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );
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
					BEMObject* pObj = BEMPX_GetObjectPtr( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );
					if (iError >= 0 && pObj)
					{
						sSelStr = pObj->getName().toLatin1().constData();
						if (pObj->getObjectType() != BEMO_User)
						{	ASSERT( FALSE );  // don't think we should ever get here...
							sSelStr += pszAppend[ (int) pObj->getObjectType() ];
						}
					}
					else if (iError >= 0)
//                  sSelStr = szNone;
                  sSelStr = ((m_dwListOptionFlag & BASELINERUN_INPLACEOF_NONE) ? szBaselineRun : szNone);  // SAC 7/30/02
				}
				else // if ( (m_iComboMode == CM_ACTIVE) || (m_iComboMode == CM_PARENT) )
				{	// select string based on string data
					QString qsStr = BEMPX_GetString( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );
					if (iError >= 0 && qsStr.length() > 0)
					{
						sSelStr = qsStr.toLatin1().constData();

						// what if current object is from a library??
                  BEMObject* pObj = BEMPX_GetObjectByClass( BEMPX_GetClassID( m_lUseDBID ), iError, m_iUseDBInstance );
                  if (iError >= 0 && pObj && pObj->getObjectType() != BEMO_User &&
                       // this last part ensures we don't paste trailing "(... Lib)" into NEWPAR selected string
                       (BEMPX_GetPropertyID( m_lUseDBID ) != 0 || BEMPX_GetArrayID( m_lUseDBID ) != BEM_PARAM0_NEWPAR) )
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
	long lNewVal = BEMPX_GetInteger( m_lUseDBID, iSpecialVal, iError, m_iUseDBInstance );
   if (iError >= 0)
   {
      QString qsCurRuleset = BEMPX_GetSymbolString( (int) lNewVal, m_lUseDBID, m_iUseDBInstance );
      CString sCurRuleset = qsCurRuleset.toLatin1().constData();
      CString sSelRuleset;
      GetLBText( GetCurSel(), sSelRuleset );
      sbNewRulesetSelected = (sSelRuleset != sCurRuleset);
   }
   return sbNewRulesetSelected;
}

LONG CComboBoxCtl::OnUpdateData( UINT, LONG )
{
   int iSetDataRetVal = -1;
   BOOL bEvalRules = TRUE;

   int i1Class = BEMPX_GetClassID( m_lUseDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iUseDBInstance );
   if ( m_lUseDBID > 0 && m_iDataType >= 0 && eObjType != BEMO_NumTypes &&
        BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
   {
      int iPropID = BEMPX_GetPropertyID( m_lUseDBID );
      int iArrID  = BEMPX_GetArrayID(    m_lUseDBID );
      DWORD dwSelData = GetItemData( GetCurSel() );
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
                ObjectIsFromLibrary( m_lUseDBID, m_iUseDBInstance ) )  // SAC 8/1/02 - Added m_iUseDBInstance argument
      {
         OnDisplayData(0,0);
      }
      else if ( m_lUseDBID > 0 && iPropID == 0 &&
                ( iArrID == BEM_PARAM0_NEWPAR  ||
                  iArrID == BEM_PARAM0_NEWCOPY ) )
      {  // Do nothing since this data is only grabbed and used if the user
      }  // chooses to create the new component for which this data is being defined
      else
      {
// SAC 7/30/04 - Added code to check w/ parent frame BEFORE setting data to BEMProc, to enable the user to be warned about ramifications of the change before installing the new value
         BOOL bContinue = TRUE;
         if ( ((m_iComboMode == CM_SYMBOL  &&  m_iDataType == BEMP_Sym) || (m_iComboMode == CM_SCREEN))  ||
              dwSelData <= sdwCreateData )
         {
            CFrameWnd* pFrame = GetParentFrame();
            if (pFrame == NULL)
            {
               ASSERT( FALSE );
               bContinue = FALSE;
            }
//            else if (pFrame->SendMessage( WM_OKTOMODIFY, (WPARAM) m_iUseDBInstance, m_lUseDBID ) == 0)
//               bContinue = FALSE;
         }

         if (!bContinue)
            OnDisplayData(0,0);
         else
         {
            int iDataType = m_iDataType;

            // First handle selection based on integer value (symbol value)
            // SAC 2/1/00 - New CM_SCREEN mode stuff
            if ( (m_iComboMode == CM_SYMBOL  &&  m_iDataType == BEMP_Sym) || (m_iComboMode == CM_SCREEN) )
            {
               long lNewVal = (long) dwSelData;

               if (m_iUseDBInstance >= 0)
                  BEMPX_SetActiveObjectIndex( i1Class, m_iUseDBInstance );

               iSetDataRetVal = BEMPX_SetBEMData( m_lUseDBID, iDataType, (void*) &lNewVal );
            }
            // Now deal with the selection of "- create new ... -"
            else if (dwSelData > sdwCreateData)
            {
               // SAC 4/9/02 - Added flag value to override default availability "None", "Create" & perhaps other options
               ASSERT( !(m_dwListOptionFlag & PREVENT_ENTRY_CREATE) );

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
						{	createInfo.m_lAssignmentDBID   = (m_iComboMode == CM_OBJECT) ? m_lUseDBID : 0;
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
                  if ( /*m_iComboMode != CM_STRING &&*/ m_iComboMode != CM_PARENT && iObjFrom != 0 ) // => not user-defined object
                     sSelStr = sSelStr.Left( sSelStr.GetLength() - 12 );

//                  if (sSelStr.Compare( szNone ) == 0)
                  if (sSelStr.Compare( ((m_dwListOptionFlag & BASELINERUN_INPLACEOF_NONE) ? szBaselineRun : szNone) ) == 0)  // SAC 7/30/02
                     sSelStr.Empty();

                  if (m_iUseDBInstance >= 0)
                     BEMPX_SetActiveObjectIndex( i1Class, m_iUseDBInstance );

                  iSetDataRetVal = BEMPX_SetBEMData( m_lUseDBID, iDataType, (void*) ((const char*) sSelStr),
                                                  (BEM_ObjType) iObjFrom );

                  if (m_iComboMode == CM_ACTIVE)
                     bEvalRules = FALSE;
               }
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
         GetParent()->PostMessage( WM_DATAMODIFIED, wEval, m_lUseDBID );
         return 1;  // bail out quickly
      }

      // Post-processing following mods
      WORD wEval = (bEvalRules ? 1 : 0);
      GetParent()->SendMessage( WM_DATAMODIFIED, wEval, m_lUseDBID );

      // redisplay status bar strings
      CFrameWnd* pFrame = GetParentFrame();
      if (pFrame)
         pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
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
      qmInfo.m_lDBID  = m_lUseDBID;
      qmInfo.m_iDBInstance = m_iUseDBInstance;
      qmInfo.m_bEditable = m_bEditable;
      qmInfo.m_bObjectAssign = (m_iComboMode == CM_OBJECT);
      qmInfo.m_iDBaseType = QMI_DBASETYPE_BEMPROC;
      qmInfo.m_dwFlags = 0;

      pFrame->SendMessage( WM_QUICKMENU, NULL, (LPARAM) &qmInfo );
   }
}


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


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CComboBoxCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CComboBox::OnHelpInfo(pHelpInfo);
}


/////////////////////////////////////////////////////////////////////////////
// SAC 6/7/01 - Added in the process of implementing Auto-Complete mechansim

BOOL CComboBoxCtl::PreTranslateMessage(MSG* pMsg)
{
	// Need to check for backspace/delete. These will modify the text in
	// the edit box, causing the auto complete to just add back the text
	// the user has just tried to delete. 

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboBoxCtl::OnEditUpdate() 
{
   // if we are not to auto update the text, get outta here
   if (!m_bAutoComplete) 
       return;

   // Get the text in the edit box
   CString str;
   GetWindowText(str);
   int nLength = str.GetLength();
  
   // Currently selected range
   DWORD dwCurSel = GetEditSel();
   WORD dStart = LOWORD(dwCurSel);
   WORD dEnd   = HIWORD(dwCurSel);

   // Search for, and select in, and string in the combo box that is prefixed
   // by the text in the edit box
   if (SelectString(-1, str) == CB_ERR)
//   {
//       SetWindowText(str);		// No text selected, so restore what was there before
//       if (dwCurSel != CB_ERR)
//         SetEditSel(dStart, dEnd);	//restore cursor postion
//   }
   {
      MessageBeep( MB_OK );
      OnDisplayData(0,0);
   }
   else
      OnUpdateData(0,0);

   // Set the text selection as the additional text that we have added
   if (dEnd < nLength && dwCurSel != CB_ERR)
       SetEditSel(dStart, dEnd);
   else
       SetEditSel(nLength, -1);
}
