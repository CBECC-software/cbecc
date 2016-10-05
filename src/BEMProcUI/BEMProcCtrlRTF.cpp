// BEMProcCtrlRTF.cpp : implementation file
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

#include "stdafx.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "Screens.h"
#include "BEMProcCtrlRTF.h"
#include "BEMProcUIX.h"
#include "memLkRpt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CBEMProcCtrlRTF, CRichEditCtrl )

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlRTF

CBEMProcCtrlRTF::CBEMProcCtrlRTF()
{
}

CBEMProcCtrlRTF::~CBEMProcCtrlRTF()
{
}


BEGIN_MESSAGE_MAP(CBEMProcCtrlRTF, CRichEditCtrl)
	//{{AFX_MSG_MAP(CBEMProcCtrlRTF)
// 	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBEMProcCtrlRTF message handlers

BOOL CBEMProcCtrlRTF::Create( CWnd* pParentWnd, CBEMPUIControl* pControl,
										BOOL bTabbedDlgShift /*=FALSE*/, BOOL bScale /*=FALSE*/ )
{
   BOOL temp = FALSE;

   DWORD winStyle = WS_CHILD|WS_BORDER|WS_VSCROLL | ES_MULTILINE | ES_READONLY;
//   DWORD winStyle = WS_CHILD|WS_TABSTOP|WS_BORDER|WS_VSCROLL | ES_MULTILINE | ES_READONLY;
//    CONTROL         "",IDC_WHATNOW_RTF,"RICHEDIT",ES_MULTILINE | ES_READONLY | WS_BORDER | WS_VSCROLL | WS_TABSTOP,5,5,255,115

   double xScale = (bScale ? appXRatio : 1.0);  // 1.0;
   double yScale = (bScale ? appYRatio : 1.0);  // 1.0;
   CSize size( FontX( (int) (((double) pControl->m_iWidth ) * xScale) ),
               FontY( (int) (((double) pControl->m_iHeight) * yScale) ) );
   CPoint pos( FontX( (int) (((double) pControl->m_iX     ) * xScale) ),
               FontY( (int) (((double) pControl->m_iY     ) * yScale) ) );

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

//   // SAC - 1/6/98 - make adjustments to align w/ adjacent combos
//   pos.x   -= 1;   pos.y   -= 1;
//   size.cx += 2;   size.cy += (fntHtBase == fntHtSys ? 1 : -2);

//   temp = CWnd::CreateEx( WS_EX_CLIENTEDGE, "SysListView32", "", winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   temp = CRichEditCtrl::Create( winStyle, CRect(pos, size), pParentWnd, pControl->m_uiCtrlID );
   if (temp)
   {
      m_lDBID           = pControl->m_lDBID;
      m_iDBClass        = BEMPX_GetClassID( m_lDBID );
      m_bCalledCreate 	= TRUE;
      m_sStatusMsg 		= pControl->m_sStatusMsg;
      
      m_iItemHelpID     = BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID    = BEMPX_GetTopicHelpID( m_lDBID );

// SAC 7/15/00 - set background color to BTNFACE
      SetBackgroundColor( FALSE, ::GetSysColor( COLOR_BTNFACE ) );

      m_sLoadedRTFFile.Empty();
   }
   return temp;
}

void CBEMProcCtrlRTF::PostNcDestroy() 
{
	if (m_bCalledCreate)
		delete this;
}


// HBRUSH CBEMProcCtrlRTF::CtlColor(CDC* pDC, UINT nCtlColor) 
// {
// 	// Change any attributes of the DC here
//    pDC->SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
//    return buttonBrush;
// 	
// 	// Return a non-NULL brush if the parent's handler should not be called
// //	return NULL;
// }


static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CFile* pFile = (CFile*) dwCookie;
   *pcb = pFile->Read(pbBuff, cb);
   return 0;
}

LONG CBEMProcCtrlRTF::OnDisplayData(UINT, LONG)
{
//   if (!m_bUpdatingList  &&  !m_bSettingHighlight  &&  m_iDBClass > 0)
//   {
//      m_bUpdatingList = TRUE;
//
//      SetRedraw( FALSE );
//
//      m_bUpdatingList = FALSE;
//
//      SetRedraw();
//      Invalidate();
//   }

   BOOL bClearAll = FALSE;
   CString sRTFFileName;
//   if (BEMPX_SetDataString( m_lDBID, sRTFFileName )  &&  !sRTFFileName.IsEmpty())
// SAC 2/10/01 - replaced above line of code w/ following that plugs in temporary RTF file
   if (m_lDBID < 1)
      sRTFFileName = "Test.rtf";
   else if (!BEMPX_SetDataString( m_lDBID, sRTFFileName ))
      sRTFFileName.Empty();
   if (!sRTFFileName.IsEmpty())
   {
      sRTFFileName = esRTFFilePath + sRTFFileName;
      if (sRTFFileName.CompareNoCase( m_sLoadedRTFFile ) == 0)
      {
         // RTF file already loaded
      }
      else if (FileExists(sRTFFileName))
      {
         CFile cFile( sRTFFileName, CFile::modeRead | CFile::shareDenyWrite );
         EDITSTREAM es;
         es.dwCookie = (DWORD) &cFile;
         es.pfnCallback = MyStreamInCallback; 
         StreamIn(SF_RTF, es);

         // SAC 7/15/00 - store last loaded filename to prevent re-loading same file multiple times
         m_sLoadedRTFFile = sRTFFileName;
      }
      else
      {
// ???
// ??? WHAT TO DO IF FILE DOES NOT EXIST ???
// ???
         bClearAll = TRUE;
      }
   }
   else
   {
// ???
// ??? WHAT TO DO IF BEMPROC PROPERTY ISN'T PROPERLY SET ???
// ???
      bClearAll = TRUE;
   }

   if (bClearAll)
   {
      if (GetLineCount() > 0)
      {
         SetReadOnly( FALSE );
         SetSel(0, -1);
         Clear();
         SetReadOnly( TRUE );
      }
      m_sLoadedRTFFile.Empty();
   }
//??   Invalidate();

   return 1;
}
