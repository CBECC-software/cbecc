// BEMProcUI.cpp : Defines the initialization routines for the DLL.
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
#include <afxdllx.h>

#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "ToolTips.h"
#include "BEMProcUIX.h"

#include "..\BEMProc\BEMProc.h"
//#include "..\BEMProc\BEMRulPrcX.h"

#include "BPUICtl_WMF.h" 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE BEMProcUIDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("BEMProcUI* DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(BEMProcUIDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(BEMProcUIDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("BEMProcUI* DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(BEMProcUIDLL);
	}
	return 1;   // ok
}


/////////////////////////////////////////////////////////////////////////////
// Exports for managing CSACWizardDlg dialog data

BOOL BEMPUIX_InitBEMProcUI(CWinApp* pApp, HINSTANCE hInst)
{
	AfxSetResourceHandle( BEMProcUIDLL.hModule);
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	if (pModuleState)
	{	pModuleState->m_pCurrentWinApp = pApp;
		pModuleState->m_hCurrentInstanceHandle = hInst;
	}
	return TRUE;
}

BOOL BEMPUIX_ScreenData( CWnd* pParentWnd, const char* psScreenFN, const char* psToolTipFN,
                      const char* psGraphicsPN, const char* psScreensPN, const char* psRTFPN )
{
   BOOL bRetVal = TRUE;

   CString sErrorMsg;
   if (!FileExists( psScreenFN ))
   {
      sErrorMsg += "\n   Screen Definitions File: ";
      sErrorMsg += psScreenFN;
   }
   if (!FileExists( psToolTipFN ))
   {
      sErrorMsg += "\n   ToolTip Definitions File: ";
      sErrorMsg += psToolTipFN;
   }

   if (sErrorMsg.GetLength() > 0)
   {
      sErrorMsg = "The following required Wizard files were not found:" + sErrorMsg;
      BEMMessageBox( sErrorMsg );
      return FALSE;
   }
   else
   {
      // Setup font and other external data
      SetExternals( pParentWnd );

      // Read wizard dialog definitions
      if (!eScreenData.Init( psScreenFN ))
      {
         CString sMsg;
         sMsg.Format( "Error loading screen definitions file '%s'.", psScreenFN );
         BEMMessageBox( sMsg );
         return FALSE;
      }

      // Read UI control ToolTip definitions
      if (!ReadToolTipFile( psToolTipFN ))
      {
         CString sMsg;
         sMsg.Format( "Error loading ToolTip definitions file '%s'.", psToolTipFN );
         BEMMessageBox( sMsg );
      }

      esGraphicsPath = psGraphicsPN;
      esScreensPath = psScreensPN;  // SAC 7/15/00

      esRTFFilePath = (psRTFPN ? psRTFPN : psScreensPN);  // SAC 2/10/01 - Added separate RTF file path
   }

   return bRetVal;
}


BOOL BEMPUIX_ResetScreenData( const char* psScreenFN, const char* psToolTipFN,
                           BOOL bReportResults )
{
   BOOL bRetVal = TRUE;

   CString sErrorMsg;
   if (!FileExists( psScreenFN ))
   {
      sErrorMsg += "\n   Screen Definitions File: ";
      sErrorMsg += psScreenFN;
   }
   if (!FileExists( psToolTipFN ))
   {
      sErrorMsg += "\n   ToolTip Definitions File: ";
      sErrorMsg += psToolTipFN;
   }

   if (sErrorMsg.GetLength() > 0)
   {
      sErrorMsg = "The following required Wizard files were not found:" + sErrorMsg;
      BEMMessageBox( sErrorMsg );
      return FALSE;
   }
   else
   {
      // Read wizard dialog definitions
      if (!eScreenData.Init( psScreenFN, bReportResults ))
      {
         CString sMsg;
         sMsg.Format( "Error loading screen definitions file '%s'.", psScreenFN );
         BEMMessageBox( sMsg );
         return FALSE;
      }

      // Read UI control ToolTip definitions
      if (!ReadToolTipFile( psToolTipFN ))
      {
         CString sMsg;
         sMsg.Format( "Error loading ToolTip definitions file '%s'.", psToolTipFN );
         BEMMessageBox( sMsg );
      }

	// SAC 5/11/14 - added access to ruleset-based tool tips
      if (!LoadToolTipsFromRuleset())
      {
         BEMMessageBox( "Error loading ToolTips defined in compliance ruleset." );
      }
   }

   return bRetVal;
}


int BEMPUIX_GetMainScreenInfo()
{
   return eScreenData.m_iMainScreenTabs;
}


int BEMPUIX_GetNumConsecutiveDialogTabIDs( int iBEMClass, int iUIMode )
{	int iRetVal = 0;
   int iNumPages = eScreenData.GetNumPagesByClass( iBEMClass, iUIMode );
   CBEMPUIPage* pPage = eScreenData.GetPageByClassAndIndex( iBEMClass, 0, iUIMode );
   int iPgID = (pPage ? pPage->m_iPageId : -1);
	if (iPgID > 0)
	{
		BOOL bConsecutive = TRUE;
		iRetVal++;
   	for (int i=1; (bConsecutive && i<iNumPages); i++)
   	{	iPgID++;
   	   pPage = eScreenData.GetPageByClassAndIndex( iBEMClass, i, iUIMode );
			if (pPage && pPage->m_iPageId == iPgID)
				iRetVal++;
			else
				bConsecutive = FALSE;
		}
	}
	return iRetVal;
}


//void BEMPUIX_SetWMFDatabaseIDs( long lDBID_FootprintWMF, long lDBID_FPOrientXFrac,
//                             long lDBID_FPOrientYFrac, long lDBID_Orientation )
//{
//   elDBID_FootprintWMF  = lDBID_FootprintWMF ;
//   elDBID_FPOrientXFrac = lDBID_FPOrientXFrac;
//   elDBID_FPOrientYFrac = lDBID_FPOrientYFrac;
//   elDBID_Orientation   = lDBID_Orientation  ;
//}


//void BEMPUIX_SetFloorPlanDatabaseIDs( long lDBID_Footprint, long lDBID_X, long lDBID_Y,
//                                   long lDBID_Orientation )
//{
//   elFPDBID_Footprint   = lDBID_Footprint  ;
//   elFPDBID_X           = lDBID_X          ;
//   elFPDBID_Y           = lDBID_Y          ;
//   elFPDBID_Orientation = lDBID_Orientation;
//}


// SAC 10/19/02 - Added new export to retrieve info included in new help button stuff
int  BEMPUIX_GetHelpGroupItemInfo( CDWordArray& dwaHelpItemIDs, CStringArray& saHelpItemStrings, int iHelpGroupIdx )
{
   int iRetVal = 0;
   if (iHelpGroupIdx >= 0 && iHelpGroupIdx < eScreenData.m_aHelpItemGroups.GetSize())
   {
      CBEMHelpItemGroup* pHIG = eScreenData.m_aHelpItemGroups.GetAt( iHelpGroupIdx );
      if (pHIG)
      {
         int iNumHelpItems = pHIG->m_aHelpItems.GetSize();
         for (int i=0; i<iNumHelpItems; i++)
         {
            CBEMHelpItem* pHI = pHIG->m_aHelpItems.GetAt(i);
            if (pHI && pHI->m_cCondition.MissingOrTrue())
            {
               iRetVal++;
               dwaHelpItemIDs.Add( (DWORD) pHI->m_lHelpID );
               saHelpItemStrings.Add(      pHI->m_sText );
            }
         }
      }
   }
   return iRetVal;
}


