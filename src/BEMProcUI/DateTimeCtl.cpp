// DateTimeCtl.cpp : implementation file
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
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "Screens.h"
#include "DateTimeCtl.h"
#include "BEMProcUIX.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CDateTimeCtl, CWnd )

static char BASED_CODE szErrorCaption[] = "Date/Time Control Error";

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl

CDateTimeCtl::CDateTimeCtl()
{
   m_bDroppedDown = FALSE;
   m_iDateType = DT_Full;  // SAC 3/16/01
   m_lYear = 0;
}

CDateTimeCtl::~CDateTimeCtl()
{
}

BOOL CDateTimeCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, BOOL bAllowEdits, long lDBIDOffset,
                           BOOL bTabbedDlgShift, BOOL calledNew, BOOL scaleToSysFont, BOOL scaleToScreenRes,
                           UINT uiTopicHelp, UINT uiItemHelp )
{
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

// SAC - 8/25/98
//   BOOL retVal = CDateTimeCtrl::Create( WS_CHILD|WS_VISIBLE|WS_TABSTOP, CRect(pos, size),
   BOOL retVal = CDateTimeCtrl::Create( WS_CHILD|WS_TABSTOP, CRect(pos, size),
                                        pParentWnd, pControl->m_uiCtrlID );
//   BOOL retVal = CWnd::Create( DATETIMEPICK_CLASS, _T(""), WS_CHILD|WS_VISIBLE|WS_TABSTOP, CRect(pos, size),
//                                        pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
      m_uiCtrlType   = pControl->m_uiCtrlType;
      m_iFont        = pControl->m_iFont;
      m_lDBID        = pControl->m_lDBID + lDBIDOffset;
      m_iDBInstance  = pControl->m_iDBInstance;
//      m_iDataType    = BEMPX_GetDataType( m_lDBID );
//      m_lNavOrVal    = pControl->m_lValue;
      m_sStatusMsg   = pControl->m_sStatusMsg;

      m_iDateType    = (int) pControl->m_lValue;  // SAC 3/16/01

// SAC 2/7/02 - added new, more dynamic mechanism for accessing year, min & max values
      int iError;
      BEMPropertyType* pPT = BEMPX_GetPropertyTypeFromDBID( m_lDBID, iError );
      ASSERT( pPT && pPT->getNumValues() > 3 );
      m_iDBIDArraySize = (pPT ? pPT->getNumValues() : 0);
      m_lBaseDBID = ((long) (m_lDBID / BEM_PARAM_MULT)) * BEM_PARAM_MULT;

      if ( m_iDateType == DT_MoDa  &&
           (m_iDBIDArraySize < 4  ||  !BEMPX_SetDataInteger( m_lBaseDBID + m_iDBIDArraySize-2, m_lYear, 0, -1, m_iDBInstance )) )
         BEMMessageBox( "CDateTimeCtl::Create() Error:  Unable to retrieve Year." );

//      m_bPressed   = FALSE;
      m_bCalledNew = calledNew;
//      m_bCreatedByClassName = FALSE;

//      m_bScaleFontToScreenRes = scaleToScreenRes;

      m_iItemHelpID  = ( uiItemHelp == 0 ? BEMPX_GetItemHelpID(  m_lDBID ) : uiItemHelp);
      m_iTopicHelpID = (uiTopicHelp == 0 ? BEMPX_GetTopicHelpID( m_lDBID ) : uiTopicHelp);

      m_cEditableCondition = pControl->m_cEditableCondition;
      m_bEditable = (BEMPX_GetCompIsEditable( m_lDBID ) && m_cEditableCondition.MissingOrTrue());
      m_bAllowEdits = bAllowEdits;

      SetFont( GetWizFont(m_iFont), TRUE );

      QString sDateTimeFormat = BEMPX_GetBEMUnitsLabel( m_lDBID );
      if (sDateTimeFormat.isEmpty())
         sDateTimeFormat = _T("ddd, MMM dd");
      SetFormat( sDateTimeFormat.toLatin1().constData() );

//      SetMonthCalColour(MCSC_MONTHBK, RGB(220,220,255));

      SetValidRange();

// SAC - 8/25/98
//      BOOL dispOK = (OnDisplayData(0,0)!=0);
   }
   return retVal;
}


BEGIN_MESSAGE_MAP(CDateTimeCtl, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CDateTimeCtl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, OnDateTimeChange)
	ON_NOTIFY_REFLECT(DTN_CLOSEUP, OnCloseUp)
	ON_NOTIFY_REFLECT(DTN_DROPDOWN, OnDropDown)
	ON_WM_RBUTTONDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_MESSAGE(WM_UPDATEDATA,  OnUpdateData)
   ON_MESSAGE(WM_GETCTRLDBID, OnGetDBID)
   ON_MESSAGE(WM_GETCTRLDBINST, OnGetDBInstance)

	ON_WM_HELPINFO()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl message handlers

void CDateTimeCtl::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
    if (m_bCalledNew)  // ( (m_bCreatedByClassName) || (m_bCalledNew) )
        delete this;
	
	CDateTimeCtrl::PostNcDestroy();
}

HBRUSH CDateTimeCtl::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
//VC++ VERSION
//	// TODO: Change any attributes of the DC here
//	
//	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	return NULL;

   pDC->SetTextColor( GetBEMPUITextColor( BEMS_Undefined ) );

	// TODO: Change any attributes of the DC here
	if (!m_bEditable)
   {
      pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
      return buttonBrush;
   }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return windowBrush;
}

void CDateTimeCtl::OnDateTimeChange(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   if (!m_bDroppedDown)
      OnUpdateData(0,0);
	
	*pResult = 0;
}

void CDateTimeCtl::OnCloseUp(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   m_bDroppedDown = FALSE;
   OnUpdateData(0,0);
	
	*pResult = 0;
}

void CDateTimeCtl::OnDropDown(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   m_bDroppedDown = TRUE;
	
	*pResult = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl - Display & Update Data Stuff

LRESULT CDateTimeCtl::OnGetDBID(WPARAM, LPARAM)
{
   return m_lDBID;
}

LRESULT CDateTimeCtl::OnGetDBInstance(WPARAM, LPARAM)
{
   return m_iDBInstance;
}


int CDateTimeCtl::RangeCheckViolation( BOOL bSilent, CString* psMsg )
{	int iRetVal = 0;
   long lData;
   if (BEMPX_SetDataInteger( m_lDBID, lData, 0, -1, m_iDBInstance ))
	{	QString qsMsg;
		iRetVal = BEMPX_PerformRangeCheck( m_lDBID, (double) lData, bSilent, (psMsg==NULL ? NULL : &qsMsg) );
		if (psMsg && !qsMsg.isEmpty())
			*psMsg = qsMsg.toLatin1().constData();
	}
   return iRetVal;
}


void CDateTimeCtl::SetValidRange()
{
   // Set valid date ranges based on second and third array elements of this lDBID
   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iDBInstance );
   if ( m_lDBID > 0 && eObjType != BEMO_NumTypes &&
        BEMPX_GetNumObjects( i1Class, eObjType ) > 0 && m_iDBIDArraySize > 3)  // SAC 2/7/02
   {
//      int iDataType, iError, iSpecialVal;
      long lRange[2] = { 0, 0 };
      for (long i=1; i<3; i++)
      {
//         void* pData = BEMPX_GetBEMData( m_lDBID+i, iDataType, iSpecialVal, iError, m_iDBInstance );
//         if (iError >= 0 && pData)
// SAC 3/16/01 - Updated data retrieval mechanism

// SAC 11/8/02 - Added fix to restore OLD functionality for NON-DT_MoDa arrays
         if (m_iDateType == DT_Full)
         {
            if (!BEMPX_SetDataInteger( m_lDBID+i, lRange[i-1], 0, -1, m_iDBInstance ))
               lRange[i-1] = 0;
         }
         else
         {
//            if (BEMPX_SetDataInteger( m_lDBID+i, lRange[i-1], 0, -1, m_iDBInstance ))
            if (BEMPX_SetDataInteger( m_lBaseDBID+m_iDBIDArraySize-2+i, lRange[i-1], 0, -1, m_iDBInstance ))  // SAC 2/7/02
            {
               ASSERT( m_iDateType == DT_MoDa );  // SAC 11/8/02
//               if (m_iDateType == DT_MoDa)  // SAC 3/16/01
//               {
                  CTime time( m_lYear, lRange[i-1]/100, lRange[i-1]%100, 0, 0, 0 );
                  lRange[i-1] = (long) time.GetTime();
//               }
//               else
//                  lRange[i-1] = *((long*) pData);
            }
            else
               lRange[i-1] = 0;
         }
      }

      if (lRange[0] && lRange[1])
      {
         CTime minTime( (time_t) lRange[0] );
         CTime maxTime( (time_t) lRange[1] );
         SetRange( &minTime, &maxTime );
      }
   }
}


LRESULT CDateTimeCtl::OnDisplayData(WPARAM, LPARAM)
{
   m_bEditable = (BEMPX_GetCompIsEditable( m_lDBID ) && m_cEditableCondition.MissingOrTrue());

   int i1Class = BEMPX_GetClassID( m_lDBID );
   BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iDBInstance );
   if ( m_lDBID > 0  &&  eObjType != BEMO_NumTypes  &&  BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
   {
// SAC 3/16/01 - Updated data retrieval mechanism
      long lData;
      if (BEMPX_SetDataInteger( m_lDBID, lData, 0, -1, m_iDBInstance ))
      {
         if (m_iDateType == DT_MoDa)  // SAC 3/16/01
         {
            ASSERT( m_lYear >= 1970 && m_lYear <= 2037 && lData >= 101 && lData <= 1231 );
            CTime time( m_lYear, lData/100, lData%100, 0, 0, 0 );
            SetTime( &time );
         }
         else
         {
            CTime time( (time_t) lData );
            SetTime( &time );
         }
      }
   }

   return 1;
}


LRESULT CDateTimeCtl::OnUpdateData( WPARAM, LPARAM )
{
   if (!m_bAllowEdits)
   {
      MessageBeep( MB_OK );
      MessageBox( szErrEditsNotAllowed, szErrorCaption, MB_ICONSTOP );
      OnDisplayData(0,0);
   }
   else
   {
      int i1Class = BEMPX_GetClassID( m_lDBID );
      BEM_ObjType eObjType = BEMPX_GetCurrentObjectType( i1Class, m_iDBInstance );
      if ( m_lDBID > 0 && eObjType == BEMO_User &&
           BEMPX_GetNumObjects( i1Class, eObjType ) > 0 )
      {
//         CTime time = GetTime();
         CTime time;
         GetTime( time );
//         long lTime = (long) time.GetTime();
// SAC 3/16/01 - Implemented multiple date storage formats
         long lTime;
         if (m_iDateType == DT_MoDa)
            lTime = (time.GetMonth() * 100) + time.GetDay();
         else
            lTime = (long) time.GetTime();

         if (m_iDBInstance >= 0)
            BEMPX_SetActiveObjectIndex( i1Class, m_iDBInstance );

         int iSetDataRetVal = BEMPX_SetBEMData( m_lDBID, BEMP_Int, &lTime );
         if (iSetDataRetVal >= 0)
         {
            // Post-processing following mods
            GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lDBID );
// SAC 1/27/99 - Replaced w/ above
////            SetDataModifiedFlag( TRUE );
//
//            // execute compliance rulelist #1
//            GetParent()->SendMessage( WM_EVALPROPOSED );
//
////            // send a message to the main view's tree control via CMainFrame in case the tree requires updating
////            GetParentFrame()->SendMessage( WM_UPDATETREE, 0, m_lDBID );
//
//            // redisplay all currently displayed database data
//            GetParent()->PostMessage( WM_DISPLAYMODS );

            // redisplay status bar strings
            CFrameWnd* pFrame = GetParentFrame();
            if (pFrame)
               pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
//            GetMainFrame()->SetStatusBarStrings(m_sStatusMsg, m_lDBID);

// TO DO ??
//         if (bUpdateFrameTitle)
//            GetMainFrame()->OnUpdateFrameTitle(TRUE);
         }
      }
   }

   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl - Quick Menu Stuff

void CDateTimeCtl::OnRButtonDown(UINT /*nFlags*/, CPoint /*point*/ )
{
   SetFocus();
   DoQuickMenu();
//	CDateTimeCtrl::OnRButtonDown(nFlags, point);
}

void CDateTimeCtl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      DoQuickMenu();
   else
   	CDateTimeCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CDateTimeCtl::DoQuickMenu()
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
      qmInfo.m_bObjectAssign = FALSE;
      qmInfo.m_iDBaseType = QMI_DBASETYPE_BEMPROC;
      qmInfo.m_dwFlags = 0;

      pFrame->SendMessage( WM_QUICKMENU, NULL, (LPARAM) &qmInfo );
   }
}


/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtl - Misc Message Handlers

void CDateTimeCtl::OnKillFocus(CWnd* pNewWnd) 
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, NULL, 0 );
//   GetMainFrame()->SetStatusBarStrings( "", 0 );

	CDateTimeCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
}

void CDateTimeCtl::OnSetFocus(CWnd* pOldWnd) 
{
   CFrameWnd* pFrame = GetParentFrame();
   if (pFrame)
      pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lDBID );
//   GetMainFrame()->SetStatusBarStrings( m_sStatusMsg, m_lDBID );

	CDateTimeCtrl::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
}


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CDateTimeCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CDateTimeCtrl::OnHelpInfo(pHelpInfo);
}
