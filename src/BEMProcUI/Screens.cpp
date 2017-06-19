// Screens.cpp
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
/*  (c) Copyright 1997, SAC Software                                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "BEMProcUIX.h"
//#include "memLkRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CBEMPUIScreenData eScreenData;

static BOOL sbReportErrors = TRUE;  // SAC 2/2/01

static char szTDC_ToolTip[]   = "EvalRulelist:";
static const int iToolTipLen = 13;

#define  SCRNTOKEN_MAIN  0
#define  SCRNTOKEN_TAB   1
#define  SCRNTOKEN_CTRL  2
#define  SCRNTOKEN_VER   3  // SAC 5/21/01
#define  SCRNTOKEN_END   4
static char BASED_CODE szTokenMain[] = "MAINSCREEN";
static char BASED_CODE szTokenTab[]  = "TAB";
static char BASED_CODE szTokenCtrl[] = "CTRL";
static char BASED_CODE szTokenVer[]  = "VERSION";  // SAC 5/21/01

static int ReadScreenToken( CTextIO& file )
{
   CString sToken = file.ReadToken();
   file.PostReadToken();

   if (sToken == szTokenMain)
      return SCRNTOKEN_MAIN;
   else if (sToken == szTokenTab)
      return SCRNTOKEN_TAB;
   else if (sToken == szTokenCtrl)
      return SCRNTOKEN_CTRL;
   else if (sToken == szTokenVer)  // SAC 5/21/01
      return SCRNTOKEN_VER;
   else if (sToken.GetLength() > 0)
      file.ThrowTextIOException( CTextioException::xHeader );

   return SCRNTOKEN_END;
}


static char BASED_CODE szTDCT_Edit[]   = "TDCT_Edit";
static char BASED_CODE szTDCT_Combo[]  = "TDCT_Combo";
static char BASED_CODE szTDCT_Button[] = "TDCT_Button";
static char BASED_CODE szTDCT_Check[]  = "TDCT_Check";
static char BASED_CODE szTDCT_RadioG[] = "TDCT_RadioG";
static char BASED_CODE szTDCT_Radio[]  = "TDCT_Radio";
static char BASED_CODE szTDCT_Date[]   = "TDCT_Date";
static char BASED_CODE szTDCT_Time[]   = "TDCT_Time";
static char BASED_CODE szTDCT_WMF[]    = "TDCT_WMF";
static char BASED_CODE szTDCT_Floor[]  = "TDCT_Floor";
static char BASED_CODE szTDCT_Line[]   = "TDCT_Line";
static char BASED_CODE szTDCT_Label[]  = "TDCT_Label";
static char BASED_CODE szTDCT_Spread[] = "TDCT_Spread";   // SAC 6/ 5/00
static char BASED_CODE szTDCT_List[]   = "TDCT_List";     // SAC 6/ 8/00
static char BASED_CODE szTDCT_Rect[]   = "TDCT_Rect";     // SAC 6/21/00
static char BASED_CODE szTDCT_ChkLst[] = "TDCT_ChkLst";   // SAC 7/14/00
static char BASED_CODE szTDCT_RTF[]    = "TDCT_RTF";      // SAC 7/15/00
static char BASED_CODE szTDCT_ExtCmb[] = "TDCT_ExtCmb";   // SAC 6/ 4/01
static char BASED_CODE szTDCT_ClrBar[] = "TDCT_ClrBar";   // SAC 5/ 1/02 - color bar for defining TOU periods by hour of day
static char BASED_CODE szTDCT_HlpBtn[] = "TDCT_HlpBtn";   // SAC 10/18/02 - added to enable small iconic help buttons throughout interface
static const char* pszCtrlTypes[] = { szTDCT_Edit, szTDCT_Combo, szTDCT_Button, szTDCT_Check,
                                      szTDCT_RadioG, szTDCT_Radio, szTDCT_Date, szTDCT_Time,
                                      szTDCT_WMF, szTDCT_Floor, szTDCT_Line, szTDCT_Label,
                                      szTDCT_Spread, szTDCT_List, szTDCT_Rect, szTDCT_ChkLst,
                                      szTDCT_RTF, szTDCT_ExtCmb, szTDCT_ClrBar, szTDCT_HlpBtn };

static UINT ReadControlType( CTextIO& file )
{
   UINT uiRetVal = TDCT_NumTypes;
   CString sToken = file.ReadToken();
   file.PostReadToken();

   for (UINT i=0; (uiRetVal == TDCT_NumTypes) && (i < TDCT_NumTypes); i++)
   {
      if (sToken == pszCtrlTypes[i])
         uiRetVal = i;
   }

   return uiRetVal;
}


static char BASED_CODE szFNT_MENU[] = "FNT_MENU";
static char BASED_CODE szFNT_TOOLBAR[] = "FNT_TOOLBAR";
static char BASED_CODE szFNT_VSMALL[] = "FNT_VSMALL";
static char BASED_CODE szFNT_STD[] = "FNT_STD";
static char BASED_CODE szFNT_BOLD[] = "FNT_BOLD";
static char BASED_CODE szFNT_UNITS[] = "FNT_UNITS";
static char BASED_CODE szFNT_DATATYPE[] = "FNT_DATATYPE";
static char BASED_CODE szFNT_VDATATYPE[] = "FNT_VDATATYPE";
static char BASED_CODE szFNT_UNDERLINE[] = "FNT_UNDERLINE";
static char BASED_CODE szFNT_ITALIC[] = "FNT_ITALIC";
static char BASED_CODE szFNT_ITALUNDER[] = "FNT_ITALUNDER";
static char BASED_CODE szFNT_DIALOG[] = "FNT_DIALOG";
static char BASED_CODE szFNT_VD_STD[] = "FNT_VD_STD";
static char BASED_CODE szFNT_VD_BOLD[] = "FNT_VD_BOLD";
static const char* pszFonts[] = {  szFNT_MENU, szFNT_TOOLBAR, szFNT_VSMALL, szFNT_STD, szFNT_BOLD, szFNT_UNITS, 
                                   szFNT_DATATYPE, szFNT_VDATATYPE, szFNT_UNDERLINE, szFNT_ITALIC, szFNT_ITALUNDER,
                                   szFNT_DIALOG, szFNT_VD_STD, szFNT_VD_BOLD  };

static int ReadFont( CTextIO& file )
{
   int iRetVal = FNT_NUMFONTS;
   CString sToken = file.ReadToken();
   file.PostReadToken();

   for (int i=0; (iRetVal == FNT_NUMFONTS) && (i < FNT_NUMFONTS); i++)
   {
      if (sToken == pszFonts[i])
         iRetVal = i;
   }

   return iRetVal;
}


static char BASED_CODE szTA_LEFT[]     = "TA_LEFT";
static char BASED_CODE szTA_RIGHT[]    = "TA_RIGHT";
static char BASED_CODE szTA_CENTER[]   = "TA_CENTER";
static char BASED_CODE szTA_TOP[]      = "TA_TOP";
static char BASED_CODE szTA_BOTTOM[]   = "TA_BOTTOM";
static char BASED_CODE szTA_BASELINE[] = "TA_BASELINE";

static UINT ReadJustification( CTextIO& file )
{
   CString sToken = file.ReadToken();
   file.PostReadToken();

   if (sToken == szTA_LEFT)
      return TA_LEFT;
   else if (sToken == szTA_RIGHT)
      return TA_RIGHT;
   else if (sToken == szTA_CENTER)
      return TA_CENTER;
   else if (sToken == szTA_TOP)
      return TA_TOP;
   else if (sToken == szTA_BOTTOM)
      return TA_BOTTOM;
   else if (sToken == szTA_BASELINE)
      return TA_BASELINE;
   else
      return 0;
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CBEMPUIScreenData Class Functions
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

CBEMPUIScreenData::CBEMPUIScreenData()
{
   m_iNumControls = 0;
   m_iNumPages = 0;
   m_iMainScreenTabs = 0xFFFF;
}

CBEMPUIScreenData::~CBEMPUIScreenData()
{
   DeleteData();
}

void CBEMPUIScreenData::DeleteData()
{
   if (m_iNumControls > 0)
   {
      for (int i=0; i<m_iNumControls; i++)
         delete m_apControls[i];
   }

   if (m_iNumPages > 0)
   {
      for (int i=0; i<m_iNumPages; i++)
         delete m_apPages[i];
   }

   int i=0;
   for (; i<MAX_TAB_CONTROLS; i++)
      m_apControls[i] = NULL;
   for (i=0; i<MAX_TAB_PAGES; i++)
      m_apPages[i] = NULL;

   m_iNumControls = 0;
   m_iNumPages = 0;

   m_aSpreadConfigs.DeleteContents();  // SAC 6/5/00

   m_aHelpItemGroups.DeleteContents();  // SAC 10/18/02
}


BOOL CBEMPUIScreenData::ReadMainScreenInfo( CTextIO& file, int /*iFileStructVersion*/ )
{
   file >> m_iMainScreenTabs;
   file.PostReadToken();

   return TRUE;
}


BOOL CBEMPUIScreenData::ReadScreenPage( CTextIO& file, int /*iFileStructVersion*/ )
{
   BOOL bRetVal = FALSE;
   if (m_iNumPages >= MAX_TAB_PAGES)
      BEMMessageBox( "Too Many Pages" );
   else
   {
      m_apPages[ m_iNumPages ] = new CBEMPUIPage;

      if (m_apPages[ m_iNumPages ] != NULL)
      {
         bRetVal = TRUE;   

         // Read data
         m_apPages[ m_iNumPages ]->m_sBEMClass = file.ReadString();
         file.PostReadToken();
         file >> m_apPages[ m_iNumPages ]->m_iPageId;
         file.PostReadToken();
         file >> m_apPages[ m_iNumPages ]->m_iModules;
         file.PostReadToken();
         m_apPages[ m_iNumPages ]->m_sCaption = file.ReadString();

         // Set class ID
         m_apPages[ m_iNumPages ]->m_iClassId = (int) BEMPX_GetDBComponentID( m_apPages[ m_iNumPages ]->m_sBEMClass );

         // Init other data
         m_apPages[ m_iNumPages ]->m_iNumCtrls = 0;
         m_apPages[ m_iNumPages ]->m_iFirstCtrlIdx = m_iNumControls;
         m_apPages[ m_iNumPages ]->m_iLastCtrlIdx = m_iNumControls-1;

         m_iNumPages++;
      }
   }

   return bRetVal;
}


BOOL CBEMPUIScreenData::ReadScreenControl( CTextIO& file, int iFileStructVersion )
{
   BOOL bRetVal = FALSE;
   if (m_iNumControls >= MAX_TAB_CONTROLS)
      BEMMessageBox( "Too Many Controls" );
   else
   {
      m_apControls[ m_iNumControls ] = new CBEMPUIControl;

      if (m_apControls[ m_iNumControls ] != NULL)
      {
         bRetVal = TRUE;   

         m_apControls[ m_iNumControls ]->m_sBEMParam = file.ReadString();
         file.PostReadToken();

         long lCtrlID = file.ReadLong();
         file.PostReadToken();
         m_apControls[ m_iNumControls ]->m_uiCtrlID   = (UINT) lCtrlID;
         m_apControls[ m_iNumControls ]->m_uiCtrlType = ReadControlType( file );
         file >> m_apControls[ m_iNumControls ]->m_iX;
         file.PostReadToken();
         file >> m_apControls[ m_iNumControls ]->m_iY;
         file.PostReadToken();
         file >> m_apControls[ m_iNumControls ]->m_iHeight;
         file.PostReadToken();
         file >> m_apControls[ m_iNumControls ]->m_iWidth;
         file.PostReadToken();
         file >> m_apControls[ m_iNumControls ]->m_lValue;
         file.PostReadToken();
         if (m_apControls[ m_iNumControls ]->m_uiCtrlType != TDCT_Rect)
         {
                              // Edits: dec precision or max string length
            m_apControls[ m_iNumControls ]->m_iFont      = ReadFont( file );

            m_apControls[ m_iNumControls ]->m_sLbl    = file.ReadString();
            file.PostReadToken();
            m_apControls[ m_iNumControls ]->m_uiLblJust  = ReadJustification( file );
            file >> m_apControls[ m_iNumControls ]->m_iLblDX;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iLblDY;
            file.PostReadToken();

            file >> m_apControls[ m_iNumControls ]->m_bUnitDisp;
            file.PostReadToken();
            m_apControls[ m_iNumControls ]->m_uiUnitJust = ReadJustification( file );
            file >> m_apControls[ m_iNumControls ]->m_iUnitDX;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iUnitDY;
            file.PostReadToken();

            // Read editable condition data
            m_apControls[ m_iNumControls ]->m_cEditableCondition.Read( file, m_apPages[ m_iNumPages-1 ], " editable" );
         }
         else
         {  // SAC 6/17/00 - added IO for TDCT_Rect properties
            file >> m_apControls[ m_iNumControls ]->m_iBoundThickness;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iFillRed;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iFillGreen;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iFillBlue;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iBoundRed;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iBoundGreen;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iBoundBlue;
            file.PostReadToken();
         }

         // Read display condition data
         m_apControls[ m_iNumControls ]->m_cDisplayCondition.Read( file, m_apPages[ m_iNumPages-1 ], " display" );

// SAC 5/1/02 - Added code to PREVENT reading of m_iErase* properties which were overwriting m_iBound* values for rectangles
         if (m_apControls[ m_iNumControls ]->m_uiCtrlType != TDCT_Rect)
         {
            file >> m_apControls[ m_iNumControls ]->m_iLeftEraseX;
            file.PostReadToken();
            file >> m_apControls[ m_iNumControls ]->m_iRightEraseX;
            file.PostReadToken();
         }

         if (m_apControls[ m_iNumControls ]->m_uiCtrlType != TDCT_Rect)
         {
            if (iFileStructVersion > 1)  // SAC 5/21/01 - Added code to read in error checking rulelist name from text file
            {
               m_apControls[ m_iNumControls ]->m_sErrorCheckRulelistName = file.ReadString();
               file.PostReadToken();
            }

// RW 11/4/02 - New code in place to set it up for the tooltip message to be generated via ruleset as opposed to statically set in the screen files
//            m_apControls[ m_iNumControls ]->m_sStatusMsg = file.ReadString();
            CString sTooltipMsg = file.ReadString();
            int iRuleNameIdx = sTooltipMsg.Find(szTDC_ToolTip);

            if( iRuleNameIdx < 0 )
            {
               m_apControls[ m_iNumControls ]->m_sStatusMsg = sTooltipMsg;
               m_apControls[ m_iNumControls ]->m_sTooltipRulelistName.Empty();
            }
            else
            {
               m_apControls[ m_iNumControls ]->m_sStatusMsg.Empty();
               m_apControls[ m_iNumControls ]->m_sTooltipRulelistName = sTooltipMsg.Mid(iToolTipLen);
            }
         }

         // Set final control data via Init function
         m_apControls[ m_iNumControls ]->InitControl( m_apPages[ m_iNumPages-1 ], file.GetLineCount() );

         // incrament page's num ctrls & last ctrl idx
         m_apPages[ m_iNumPages-1 ]->m_iNumCtrls++;
         m_apPages[ m_iNumPages-1 ]->m_iLastCtrlIdx++;

         // SAC 6/5/00 - Added code to read Spreadsheet definition stuff
         if (m_apControls[ m_iNumControls ]->m_uiCtrlType == TDCT_Spread)
         {
// SAC 9/10/01 - Added code to translate control's status message to an object-referencing DBID
//               that references the component whose data will be displayed/edited in the control
            long lCompDBID = 0;
            if (!m_apControls[ m_iNumControls ]->m_sStatusMsg.IsEmpty())
            {
               int iTempRefCompID = 0;
               lCompDBID = (std::max)( BEMPX_GetDatabaseID( m_apControls[ m_iNumControls ]->m_sStatusMsg, m_apPages[ m_iNumPages-1 ]->m_iClassId, FALSE, &iTempRefCompID ), 0L );
					// Note: when > 0, iTempRefCompID identifies only the first of possible several object types that this property can reference
               ASSERT( iTempRefCompID <= 0 );  // should NOT be a complex (multi-level indirection) Component:Property string
            }
// SAC 9/10/01 - altered code to use component type from status bar message (if provided)
            int i1SpreadClassIdx = BEMPX_GetClassID( (lCompDBID > 0 ? lCompDBID : m_apControls[ m_iNumControls ]->m_lDBID) );
            ASSERT( i1SpreadClassIdx > 0 );

            m_apControls[ m_iNumControls ]->m_iSpreadConfigIdx = m_aSpreadConfigs.GetSize();
            CBEMPUISpreadConfig* pConfig = new CBEMPUISpreadConfig( lCompDBID );
            // RW 8/23/02 - Added additional parameter to the CBEMPUISpreadConfig ReadText routine to allow for the passing of the File Version
            pConfig->ReadText( file, i1SpreadClassIdx, m_apPages[ m_iNumPages-1 ], iFileStructVersion ); 
            m_aSpreadConfigs.Add( pConfig );
         }
         else
            m_apControls[ m_iNumControls ]->m_iSpreadConfigIdx = -1;

         // SAC 10/18/02 - Added code to read Help Button menu item stuff
         if (m_apControls[ m_iNumControls ]->m_uiCtrlType == TDCT_HlpBtn)
         {
            m_apControls[ m_iNumControls ]->m_iHelpGroupIdx = m_aHelpItemGroups.GetSize();
            CBEMHelpItemGroup* pHelpGroup = new CBEMHelpItemGroup();
            pHelpGroup->ReadText( file, m_apControls[ m_iNumControls ]->m_lValue, m_apPages[ m_iNumPages-1 ], iFileStructVersion ); 
            m_aHelpItemGroups.Add( pHelpGroup );
         }
         else
            m_apControls[ m_iNumControls ]->m_iHelpGroupIdx = -1;

         m_iNumControls++;
      }
   }

   return bRetVal;
}


BOOL CBEMPUIScreenData::Init( const char* pszScreenDataFileName, BOOL bReportResults )
{
   BOOL bRetVal = TRUE;

   CString sScreenFile = ((pszScreenDataFileName) ? pszScreenDataFileName : m_sScreenDataFileName );
   if ( (sScreenFile.GetLength() <= 0) || (!FileExists( sScreenFile )) )
   {
      CString sErr = "Building Database Screen Interface File '";
      sErr += sScreenFile;
      sErr += "' Not Found";
      BEMMessageBox( sErr );
      bRetVal = FALSE;
   }
   else
   {
      m_sScreenDataFileName = sScreenFile;
      DeleteData();

      TRY
      {
         CTextIO file( sScreenFile, CTextIO::load );
         TRY
         {
            TRY
            {
               sbReportErrors = TRUE;  // SAC 2/2/01
               int iToken = ReadScreenToken( file );

               int iFileStructVersion = 1;  // SAc 5/21/01 - Added "VERSION, #" reading functionality
               if (iToken == SCRNTOKEN_VER)
               {
                  iFileStructVersion = (int) file.ReadLong();
                  file.PostReadToken();
                  iToken = ReadScreenToken( file );
               }

               while (iToken != SCRNTOKEN_END) // EOF handled in catch block 
               {
                  switch (iToken)
                  {
                     case SCRNTOKEN_MAIN : bRetVal = ( (ReadMainScreenInfo( file, iFileStructVersion )) && (bRetVal) );  break;
                     case SCRNTOKEN_TAB  : bRetVal = ( (ReadScreenPage(     file, iFileStructVersion )) && (bRetVal) );  break;
                     case SCRNTOKEN_CTRL : bRetVal = ( (ReadScreenControl(  file, iFileStructVersion )) && (bRetVal) );  break;
                     default             : ASSERT( FALSE );  break;
                  }
                  iToken = ReadScreenToken( file );
               }
            }
            CATCH( CTextioException, err )
            {
               if ( err->m_cause == CTextioException::endOfFile )
                  ; // we're done, no problem
               else
                  THROW_LAST();
            }
            END_CATCH
         }
         CATCH( CTextioException, err )
         {
            bRetVal = FALSE;

            CString msg = CString("Error Reading screen data\r\n");
            msg += CString("From File: ") + sScreenFile + CString( "\r\n" );
            msg += CString("\r\n\t") + CString( err->m_strError ) + CString("\r\n") + CString("\r\n");
            // errorFile.Write( msg.GetBuffer( msg.GetLength() ), msg.GetLength() );
            // msg.ReleaseBuffer();
            // BEMMessageBox( msg, NULL, 2 /*warning*/ );
            BEMMessageBox( msg );
            THROW_LAST();
         }
         END_CATCH
      }
      CATCH( CFileException, error )
      {
         bRetVal = FALSE;

         CString msg = CString( "Error opening file: " ) + sScreenFile;
         // BEMMessageBox( msg, NULL, 2 /*warning*/ );
         BEMMessageBox( msg );

         // errorFile.Write( msg.GetBuffer( msg.GetLength() ), msg.GetLength() );
         // msg.ReleaseBuffer();
      }
      END_CATCH
   }

   if (bRetVal  &&  bReportResults)
   {
      CString sMsg;
      sMsg.Format( "BEMProcUI Screen Data Loaded Successfully:\n   # Tabs = %d\n   # UI Controls = %d (of %d max)", m_iNumPages, m_iNumControls, MAX_TAB_CONTROLS );
      BEMMessageBox( sMsg, "" );
   }

   return bRetVal;
}


///////////////////////////////////////////////////////////////
// CBEMPUIScreenData - Misc Interface Functions
///////////////////////////////////////////////////////////////

static BOOL ModuleIsCompatible( int iModule, int iUIMode )
{
   BOOL bRetVal = FALSE;
   switch (iUIMode)
   {
      case 0 :  bRetVal = (iModule & 0x01);  break;
      case 1 :  bRetVal = (iModule & 0x02);  break;
      case 2 :  bRetVal = (iModule & 0x04);  break;
      case 3 :  bRetVal = (iModule & 0x08);  break;
      default:  BEMMessageBox( "ModuleIsCompatible() Error: Invalid UIMode Value." );  break;
   }
   return bRetVal;
}

int CBEMPUIScreenData::GetNumPagesByClass( int iClass, int iUIMode )
{
   int iRetVal = 0;

   for (int i=0; i<m_iNumPages; i++)
   {
      if (m_apPages[i]->m_iClassId == iClass && ModuleIsCompatible( m_apPages[i]->m_iModules, iUIMode ))
         iRetVal++;
   }

   return iRetVal;
}


CBEMPUIPage* CBEMPUIScreenData::GetPageByClassAndIndex( int iClass, int iPageIdx, int iUIMode )
{
   CBEMPUIPage* pRetVal = NULL;

   int iIdxEncountered = -1;
   for (int i=0; (pRetVal == NULL) && (i<m_iNumPages); i++)
   {
      if (m_apPages[i]->m_iClassId == iClass && ModuleIsCompatible( m_apPages[i]->m_iModules, iUIMode ))
      {
         iIdxEncountered++;
         if (iIdxEncountered == iPageIdx)
            pRetVal = m_apPages[i];
      }
   }

   return pRetVal;
}

CBEMPUIPage* CBEMPUIScreenData::GetPageByID( int iPageID )
{
   CBEMPUIPage* pRetVal = NULL;

   for (int i=0; (pRetVal == NULL) && (i<m_iNumPages); i++)
   {
      if (m_apPages[i]->m_iPageId == iPageID)
         pRetVal = m_apPages[i];
   }

   return pRetVal;
}


CBEMPUIControl* CBEMPUIScreenData::GetControlByIndex( int idx )
{
   if ( (idx >= 0) && (idx < m_iNumControls) )
      return m_apControls[idx];
   return NULL;
}

CBEMPUIControl* CBEMPUIScreenData::GetControlByPageAndID( CBEMPUIPage* pPage, UINT uiID )
{
   if (pPage && (pPage->m_iFirstCtrlIdx >= 0) && (pPage->m_iLastCtrlIdx < m_iNumControls) )
   {
      for (int i=pPage->m_iFirstCtrlIdx; i<=pPage->m_iLastCtrlIdx; i++)
      {
         if (m_apControls[i]->m_uiCtrlID == uiID)
            return m_apControls[i];
      }
   }
   return NULL;
}


UINT CBEMPUIScreenData::GetControlIDByIndex( int idx )
{
   if ( (idx >= 0) && (idx < m_iNumControls) )
      return m_apControls[idx]->m_uiCtrlID;
   return 0;
}


BOOL CBEMPUIScreenData::PageHasActiveControls( CBEMPUIPage* pPage )
{
   BOOL bRetVal = FALSE;
   if (pPage && pPage->m_iFirstCtrlIdx >= 0 && pPage->m_iLastCtrlIdx < m_iNumControls &&
       pPage->m_iFirstCtrlIdx <= pPage->m_iLastCtrlIdx)
   {
      for (int i=pPage->m_iFirstCtrlIdx; (!bRetVal && i<=pPage->m_iLastCtrlIdx); i++)
         if (m_apControls[i]->m_lDBID > 0)
         {
            if (BEMPX_GetPropertyID( m_apControls[i]->m_lDBID ) == 0)
               bRetVal = (BEMPX_GetArrayID( m_apControls[i]->m_lDBID ) != BEM_PARAM0_ACTIVE);
            else
               bRetVal = BEMPX_GetCompDisplay( m_apControls[i]->m_lDBID, 0 );
         }
   }
   return bRetVal;
}


void CBEMPUIScreenData::SetupControlConditionDBIDOffsets( CBEMPUIPage* pPage, long lDBIDOffset )
{
   if (pPage && (pPage->m_iFirstCtrlIdx >= 0) && (pPage->m_iLastCtrlIdx < m_iNumControls) )
   {
      for (int i=pPage->m_iFirstCtrlIdx; i<=pPage->m_iLastCtrlIdx; i++)
         m_apControls[i]->SetupConditionDBIDOffsets( pPage->m_iClassId, lDBIDOffset );
   }
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Misc Static Functions
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void PostReadError( CBEMPUIPage* pPage, const char* psText1, const char* psText2, int iLine )
{
   if (pPage)
   {
//      CString sMsg = "Control Definition Error: Dialog Page '";
//      sMsg += pPage->m_sCaption;
//      sMsg += "' for component type '";
//      sMsg += pPage->m_sBEMClass;
//      sMsg += "' (";
//      CString sTemp;
//      sTemp.Format("%d", pPage->m_iClassId);
//      sMsg += sTemp;
//      sMsg += ") and";
//      if (psText2)
//         sMsg += psText2;
//      sMsg += " parameter '";
//      sMsg += psText1;
//      sMsg += "'.";

      if (sbReportErrors)  // SAC 2/2/01
      {
         CString sMsg;
         if (psText1)
            sMsg.Format( "Control Definition Error: Dialog Page '%s' for component type '%s' (%d) and %s '%s' on line %d.",
                         pPage->m_sCaption, pPage->m_sBEMClass, pPage->m_iClassId, psText2, psText1, iLine );
         else
            sMsg.Format( "Control Definition Error: Dialog Page '%s' for component type '%s' (%d) and %s on line %d.",
                         pPage->m_sCaption, pPage->m_sBEMClass, pPage->m_iClassId, psText2, iLine );
         sMsg += "\n\nWould you like further errors reported?";  // SAC 2/2/01
         sbReportErrors = (::MessageBox( NULL, sMsg, "Screen Data Read Error", MB_YESNO|MB_ICONSTOP ) == IDYES);  // SAC 2/2/01
      }
   }
   else
      ASSERT( FALSE );
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CBEMCondition
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

CBEMCondition::CBEMCondition()
{
   Init();
}


void CBEMCondition::Init()
{
   m_iNumConditions = 0;
   m_bConditionsAND = FALSE;
   for (int i=0; i<MAX_BEM_CONDITIONS; i++)
   {
      m_lConditionalDBID[ i ] =  0;
      m_iCondition[       i ] = -1;
      m_fConditionValue[  i ] =  0;
      m_lCondDBIDOffset[  i ] =  0;
      m_iCondDBInstance[  i ] = -1;
      m_lCondDBID2[       i ] =  0;
      m_lCondDBIDOffset2[ i ] =  0;
   }
}


long GetConditionalDBID( const char* psCondDBID, int& iDBInstance, long& lDBID2, int iCondition, CBEMPUIPage* pPage, const char* psSuppMsg, const char* psCondType, int iLine )
{
   long lRetVal = 0;
   if (pPage && psCondDBID && iCondition >= 0)
   {
      // SAC 3/3/99 - Added code to peal off and translate leading 0-based class instance index
      CString sCondDBID = psCondDBID;
      if (isdigit( sCondDBID[0] ))
      {
         int iFirstColon = sCondDBID.Find( ':' );
         ASSERT( iFirstColon > 0 );
         iDBInstance = atoi( sCondDBID.Left( iFirstColon ) );

         // trim leading class instance index
         sCondDBID = sCondDBID.Right( sCondDBID.GetLength()-iFirstColon-1 );
      }
      else
         iDBInstance = -1;

      int iRefCompID = 0;  // SAC 7/17/01
      lRetVal = BEMPX_GetDatabaseID( sCondDBID, pPage->m_iClassId, FALSE, &iRefCompID );
		// Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
// SAC 2/1/00 - no longer needed - handled within the first call to BEMPX_GetDatabaseID()
//      if (lRetVal < 0)
//         lRetVal = BEMPX_GetDatabaseID( sCondDBID );

      // SAC 3/4/99 - Added code to strip off second lDBID for accessing a referenced component's data
      lDBID2 = 0;
      if (iRefCompID > 0)  // lRetVal >= 1000000)
      {	int iError=0;
//         // get secondary class ID from highest order bits of m_lDBID
//         long lSecComp = lRetVal / 1000000;
//         // strip secondary class ID from highest order bits of m_lDBID to make the DBID valid
//         lRetVal = lRetVal % 1000000;

         // now remove leading property name
         ASSERT( sCondDBID.Find(':') > 0 );
         sCondDBID = sCondDBID.Right( sCondDBID.GetLength() - sCondDBID.Find(':') - 1 );

         // get secondary m_lDBID2
// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into account (potentially) mulitple compatible referenced obejct types
         //lDBID2 = BEMPX_GetDatabaseID( sCondDBID, iRefCompID, FALSE, &iRefCompID );
			BOOL bDBIDValid = FALSE;
		   int i2ndRefCompID = iRefCompID;
			long l2ndDBID = lRetVal;
			BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( l2ndDBID, iError );						ASSERT( iError==0 );		ASSERT( pPropType );
			for (int iObjCls=0; (pPropType && !bDBIDValid && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
			{	if (pPropType->getObj1ClassIdx(iObjCls) > 0)
				{	l2ndDBID = BEMPX_GetDatabaseID( sCondDBID, pPropType->getObj1ClassIdx(iObjCls), FALSE, &i2ndRefCompID );
					if (l2ndDBID > 0)
						bDBIDValid = TRUE;
				}
			}
			// update original variables, regardless of whether the processing successfully returned a valid DBID
			lDBID2 = l2ndDBID;
			iRefCompID = i2ndRefCompID;
      }

      if (lRetVal < 0 || lDBID2 < 0 || lDBID2 >= ((long) (BEMPX_GetNumClasses()+1) * BEM_COMP_MULT))  // 1000000)
      {
         CString sMsg;
         if (psSuppMsg)
            sMsg = psSuppMsg;
         if (psCondType)
            sMsg += psCondType;
         sMsg += " condition parameter";
            PostReadError( pPage, psCondDBID, sMsg, iLine );
      }
   }
   else
      lRetVal = 0;

   return lRetVal;
}


#define  NUM_COND_ERRS  5
const char* pszCondErr[] = { "first", "second", "third", "fourth", "fifth" };

BOOL CBEMCondition::Read( CTextIO& file, CBEMPUIPage* pPage, const char* psCondType )
{
   BOOL bRetVal = TRUE;

   // initialize before reading
   Init();

   // read first condition
   CString sCond, sAndOr;
   file.ReadBEMProcParam( sCond, TRUE );
   file.PostReadToken();
   if (sCond.CompareNoCase( "None" ) != 0)
   {
      // We HAVE at least a single condition
      BOOL bDone = FALSE;
	  int i=0;
      for (; (!bDone && i < MAX_BEM_CONDITIONS); i++)
      {
         m_iCondition[i] = file.ReadBEMCondition();
         file >> m_fConditionValue[i];
         m_lConditionalDBID[i] = GetConditionalDBID( sCond, m_iCondDBInstance[i], m_lCondDBID2[i], m_iCondition[i], pPage,
                                                     (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType, file.GetLineCount() );
         
         // SAC 7/1/98 - variation on PostReadToken() to catch AND or OR condition if one exists
         char ch;
         do
            ch = file.GetChr();
         while ( ch == ' ' ); // || ch == ',' ); 
         file.UnGetChr();
         if (ch == 'A' || ch == 'O')
         {
            file.ReadBEMProcParam( sAndOr );
            if (i == 0)
               m_bConditionsAND = (sAndOr.CompareNoCase( "AND" ) == 0);
            else if ( ( m_bConditionsAND && sAndOr.CompareNoCase( "AND" ) != 0) ||
                      (!m_bConditionsAND && sAndOr.CompareNoCase( "OR"  ) != 0) )
            {
               // ALL conditions must be alike!!
               CString sErrMsg;
               sErrMsg.Format( "incompatible %s%s condition operator", (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType );
               PostReadError( pPage, sAndOr, sErrMsg, file.GetLineCount() );
            }

            file.PostReadToken();

            // read start of next condition
            file.ReadBEMProcParam( sCond, TRUE );
            file.PostReadToken();
         }
         else
         {
            //ASSERT( (ch == ',') );
            // SAC 3/17/99 - replaced ASSERT (above) with the following error capture
            // SAC 10/19/02 - Added check to allow LF character following the condition
            if (ch != ',' && ch != 10)
            {
               // ALL conditions must be alike!!
               CString sErrMsg;
               sErrMsg.Format( "illegal character '%c' following the %s%s condition", ch, (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType );
               PostReadError( pPage, NULL, sErrMsg, file.GetLineCount() );
            }

            bDone = TRUE;
         }
      }
      ASSERT( bDone );

      m_iNumConditions = i;
      file.PostReadToken();
   }

   return bRetVal;
}


BOOL CBEMCondition::MissingOrTrue()
{
   BOOL bRetVal = TRUE;
   if (m_iNumConditions == 0)
   {  }
   else if (m_iNumConditions == 1)
      bRetVal = BEMPX_ConditionTrue( m_lConditionalDBID[0] + m_lCondDBIDOffset[0], m_iCondition[0],
                                   m_fConditionValue[0], 0, m_iCondDBInstance[0], m_lCondDBID2[0] + m_lCondDBIDOffset2[0] );
   else
   {
      bRetVal = m_bConditionsAND;
      for (int i=0; (bRetVal == m_bConditionsAND && i<m_iNumConditions); i++)
      {
         BOOL bCond = BEMPX_ConditionTrue( m_lConditionalDBID[i] + m_lCondDBIDOffset[i], m_iCondition[i],
                                         m_fConditionValue[i], 0, m_iCondDBInstance[i], m_lCondDBID2[i] + m_lCondDBIDOffset2[i] );
         if (m_bConditionsAND && !bCond)
            bRetVal = FALSE;
         else if (!m_bConditionsAND && bCond)
            bRetVal = TRUE;
      }
   }

   return bRetVal;
}


void CBEMCondition::SetupDBIDOffsets( int iClassID, long lDBIDOffset )
{
   for (int i=0; i<m_iNumConditions; i++)
   {
      m_lCondDBIDOffset[ i] = (BEMPX_GetClassID( m_lConditionalDBID[i] ) == iClassID ? lDBIDOffset : 0);
      m_lCondDBIDOffset2[i] = ((m_lCondDBID2[i] > 0 && BEMPX_GetClassID( m_lCondDBID2[i] ) == iClassID) ? lDBIDOffset : 0);
   }
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CBEMPUIControl
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void CBEMPUIControl::InitControl( CBEMPUIPage* pPage, int iLine )  //, const char* psCondDBID, const char* psCond2DBID )
{
   if (pPage != NULL)
   {
      m_bLabelRequiringRefresh = FALSE;
      m_pPage = pPage;
      m_lDBID2 = 0;
		m_i1ChildIdx = -1;	// SAC 5/28/14 - added to facilitate UI access to properties of CHILD objects
      if (m_sBEMParam.GetLength() > 0)
      {
         // SAC 3/3/99 - Added code to peal off and translate leading 0-based class instance index
         if (isdigit( m_sBEMParam[0] ))
         {
            int iFirstColon = m_sBEMParam.Find( ':' );
            ASSERT( iFirstColon > 0 );
            m_iDBInstance = atoi( m_sBEMParam.Left( iFirstColon ) );

            // trim leading class instance index
            m_sBEMParam = m_sBEMParam.Right( m_sBEMParam.GetLength()-iFirstColon-1 );
         }
         else
            m_iDBInstance = -1;

         int iRefCompID = 0;  // SAC 7/17/01
         m_lDBID = BEMPX_GetDatabaseID( m_sBEMParam, pPage->m_iClassId, FALSE, &iRefCompID );
			// Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
         if (m_lDBID < 0)
			{	int iPndIdx = m_sBEMParam.Find('#');
				int iColIdx = m_sBEMParam.Find(':');
				if (iPndIdx > 0 && (iPndIdx+1) < iColIdx)
				{	CString sChildNum = m_sBEMParam.Mid( iPndIdx+1, (iColIdx-iPndIdx-1) );
					int iChildNum = atoi( sChildNum );
					if (iChildNum > 0)
					{	CString sRevBEMParam = m_sBEMParam.Left(iPndIdx) + m_sBEMParam.Right( m_sBEMParam.GetLength()-iColIdx );
			         m_lDBID = BEMPX_GetDatabaseID( sRevBEMParam, pPage->m_iClassId, FALSE, &iRefCompID );
			         if (m_lDBID > 0)
						{	m_i1ChildIdx = iChildNum;	// SAC 5/28/14 - added to facilitate UI access to properties of CHILD objects
							m_lDBID2 = pPage->m_iClassId;
						}
			}	}	}

         if (m_lDBID < 0)
            PostReadError( pPage, m_sBEMParam, "parameter", iLine );

         // SAC 3/3/99 - Added code to strip off second lDBID for displaying a referenced component's data
         if (iRefCompID > 0)  // m_lDBID >= 1000000)
         {	int iError=0;
//            // get secondary class ID from highest order bits of m_lDBID
//            long lSecComp = m_lDBID / 1000000;
//            // strip secondary class ID from highest order bits of m_lDBID to make the DBID valid
//            m_lDBID = m_lDBID % 1000000;

            // now remove leading property name
            CString sParam2 = m_sBEMParam;
            ASSERT( sParam2.Find(':') > 0 );
            sParam2 = sParam2.Right( sParam2.GetLength() - sParam2.Find(':') - 1 );

            // get secondary m_lDBID2
// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into account (potentially) mulitple compatible referenced obejct types
            //m_lDBID2 = BEMPX_GetDatabaseID( sParam2, iRefCompID, FALSE, &iRefCompID );
				BOOL bDBIDValid = FALSE;
		      int i2ndRefCompID = iRefCompID;
				long l2ndDBID = m_lDBID;
				BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( l2ndDBID, iError );						ASSERT( iError==0 );		ASSERT( pPropType );
				for (int iObjCls=0; (pPropType && !bDBIDValid && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
				{	if (pPropType->getObj1ClassIdx(iObjCls) > 0)
					{	l2ndDBID = BEMPX_GetDatabaseID( sParam2, pPropType->getObj1ClassIdx(iObjCls), FALSE, &i2ndRefCompID );
						if (l2ndDBID > 0)
							bDBIDValid = TRUE;
					}
				}
				// update original variables, regardless of whether the processing successfully returned a valid DBID
				m_lDBID2 = l2ndDBID;
				iRefCompID = i2ndRefCompID;

            if (m_lDBID2 < 0 || m_lDBID2 >= ((long) (BEMPX_GetNumClasses()+1) * BEM_COMP_MULT))  // 1000000)
               PostReadError( pPage, m_sBEMParam, "parameter", iLine );
         }
      }
      else
         m_lDBID = 0;

      // Set flag so that this label updates with each screen refresh (if appropriate)
      m_bLabelRequiringRefresh = ( m_uiCtrlType == TDCT_Label &&
                                   ( BEMPX_GetPropertyID( m_lDBID ) > 0 ||
                                     HaveDisplayCondition() > 0 ) );
   }
}


BOOL CBEMPUIControl::ToggleControl()
{
   if (HaveDisplayCondition())
      return (m_bActive != m_cDisplayCondition.MissingOrTrue());
   return FALSE;
}


BOOL CBEMPUIControl::CanDisplay()
{
   if (HaveDisplayCondition())
      return m_cDisplayCondition.MissingOrTrue();
   return TRUE;
}


BOOL CBEMPUIControl::IsEditable()
{
   if (HaveEditableCondition())
      return m_cEditableCondition.MissingOrTrue();
   return TRUE;
}


void CBEMPUIControl::SetupConditionDBIDOffsets( int iClassID, long lDBIDOffset )
{
   m_cDisplayCondition.SetupDBIDOffsets(  iClassID, lDBIDOffset );
   m_cEditableCondition.SetupDBIDOffsets( iClassID, lDBIDOffset );
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// SAC 10/18/02 - added help item stuff

///////////////////////////////////////////////////////////////
//                   CBEMHelpItem                          //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMHelpItem, CObject, 1)

CBEMHelpItem::CBEMHelpItem()
{
   m_sText = '\0';
   m_lHelpID = 0;
}

CBEMHelpItem::~CBEMHelpItem()
{
   m_sText.Empty();
}

BOOL CBEMHelpItem::ReadText( CTextIO& file, CBEMPUIPage* pPage )
{
   BOOL bRetVal = TRUE;

   file >> m_lHelpID;
   file.PostReadToken();

   m_sText = file.ReadString();
   file.PostReadToken();

   m_cCondition.Read( file, pPage, " display" );

   return bRetVal;
}

#ifdef _DEBUG
void CBEMHelpItem::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMHelpItem::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif


///////////////////////////////////////////////////////////////
//                   CBEMHelpItemArray                     //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMHelpItemArray, CObject, 1)

CBEMHelpItemArray::CBEMHelpItemArray()
{
}

CBEMHelpItemArray::~CBEMHelpItemArray()
{
}

void CBEMHelpItemArray::DeleteContents()
{
   int size = GetSize();
   for( int i = 0; i < size; i++ )
   {
      CBEMHelpItem* z = GetAt(i);
      delete z;
   }
   RemoveAll();
}

#ifdef _DEBUG
void CBEMHelpItemArray::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMHelpItemArray::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif


///////////////////////////////////////////////////////////////
//                   CBEMHelpItemGroup                       //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMHelpItemGroup, CObject, 1)

CBEMHelpItemGroup::CBEMHelpItemGroup()
{
}

CBEMHelpItemGroup::~CBEMHelpItemGroup()
{
   m_aHelpItems.RemoveAll();
}

BOOL CBEMHelpItemGroup::ReadText( CTextIO& file, int iNumHelpItems, CBEMPUIPage* pPage, int /*iFileStructVersion*/ )
{
   BOOL bRetVal = TRUE;
   ASSERT( iNumHelpItems > 0 );

   for (int iHlpItm=0; (bRetVal && iHlpItm<iNumHelpItems); iHlpItm++)
   {
      CBEMHelpItem* pHI = new CBEMHelpItem();
      bRetVal = pHI->ReadText( file, pPage );
      if (bRetVal)
         m_aHelpItems.Add( pHI );
   }

   return bRetVal;
}

#ifdef _DEBUG
void CBEMHelpItemGroup::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMHelpItemGroup::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif

///////////////////////////////////////////////////////////////
//                   CBEMHelpItemGroupArray                  //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMHelpItemGroupArray, CObject, 1)

CBEMHelpItemGroupArray::CBEMHelpItemGroupArray()
{
}

CBEMHelpItemGroupArray::~CBEMHelpItemGroupArray()
{
}

void CBEMHelpItemGroupArray::DeleteContents()
{
   int size = GetSize();
   for( int i = 0; i < size; i++ )
   {
      CBEMHelpItemGroup* z = GetAt(i);
      z->m_aHelpItems.DeleteContents();
      z->m_aHelpItems.RemoveAll();
      delete z;
   }
   RemoveAll();
}

#ifdef _DEBUG
void CBEMHelpItemGroupArray::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMHelpItemGroupArray::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// SAC 6/5/00 - added spreadsheet class stuff

///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadCol                          //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMPUISpreadCol, CObject, 1)

CBEMPUISpreadCol::CBEMPUISpreadCol()
{
   m_sTitle = '\0';
   m_iWidth = 0;
   m_iMisc = 0;
   m_bDispUnits = 0;
   m_bEditable = 0;
   m_lDBID = 0;
   m_iDataType = 0;
   m_iItemHelp = 0;
   m_sTitle = '\0';
}

CBEMPUISpreadCol::~CBEMPUISpreadCol()
{
   m_sTitle.Empty();
}

//void CBEMPUISpreadCol::Serialize(CArchive& ar, int iFileVer)
//{
//   if (ar.IsStoring())   
//   {
//      ar << m_sTitle;
//      ar << m_iWidth;
//      ar << m_iMisc;  
//      ar << (WORD)m_bDispUnits;
//      ar << (WORD)m_bEditable;
//      ar << m_lDBID;  
//      ar << m_iDataType;  
//      ar << m_iItemHelp;  
//      ar << m_sStatusMsg;
//   }
//   else
//   {
//      WORD binEditable;
//      WORD binDispUnits;
//      
//      ar >> m_sTitle;
//      ar >> m_iWidth;
//      ar >> m_iMisc;
//      ar >> binDispUnits;
//      ar >> binEditable;
//      ar >> m_lDBID;
//      ar >> m_iDataType;
//      ar >> m_iItemHelp;
//      ar >> m_sStatusMsg;
//     
//      m_bDispUnits   = (BOOL)binDispUnits;
//      m_bEditable    = (BOOL)binEditable;
//   }   
//}

BOOL CBEMPUISpreadCol::ReadText( CTextIO& file, int i1ClassIdx, CBEMPUIPage* pPage )
{
   BOOL bRetVal = TRUE;

   m_sTitle = file.ReadString();
   file.PostReadToken();

   file >> m_iWidth;
   file.PostReadToken();
   file >> m_iMisc;
   file.PostReadToken();

   int iFlagVal;
   file >> iFlagVal;
   file.PostReadToken();
   m_bDispUnits = (iFlagVal != 0);
   file >> iFlagVal;
   file.PostReadToken();
   m_bEditable = (iFlagVal != 0);

   CString sProperty = file.ReadString();
   file.PostReadToken();
   m_lDBID = BEMPX_GetDatabaseID( sProperty, i1ClassIdx );
   if (m_lDBID < 0)
      PostReadError( pPage, sProperty, "parameter", file.GetLineCount() );
// return FALSE ??
   else
   {
      int iError;
      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( m_lDBID, iError );
      if (pPropType)
         m_iDataType = pPropType->getPropType();
   }

   file >> m_iItemHelp;
   file.PostReadToken();

   // Conditional editing of cells
   m_cEditCondition.Read( file, pPage, " edit" );  // SAC 12/11/00

   // Read display condition data
   m_cDisplayCondition.Read( file, pPage, " display" );

// RW 11/4/02 - New code in place to set it up for the tooltip message to be generated via ruleset as opposed to statically set in the screen files
//            m_apControls[ m_iNumControls ]->m_sStatusMsg = file.ReadString();
   CString sTooltipMsg = file.ReadString();
   int iRuleNameIdx = sTooltipMsg.Find(szTDC_ToolTip);
   if( iRuleNameIdx < 0 )
   {
      m_sStatusMsg = sTooltipMsg;
      m_sTooltipRulelistName.Empty();
   }
   else
   {
      m_sStatusMsg.Empty();
      m_sTooltipRulelistName = sTooltipMsg.Mid(iToolTipLen);
   }

   file.PostReadToken();

   return bRetVal;
}

#ifdef _DEBUG
void CBEMPUISpreadCol::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMPUISpreadCol::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif


///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadColArray                     //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMPUISpreadColArray, CObject, 1)

CBEMPUISpreadColArray::CBEMPUISpreadColArray()
{
}

CBEMPUISpreadColArray::~CBEMPUISpreadColArray()
{
}

void CBEMPUISpreadColArray::DeleteContents()
{
   int size = GetSize();
   for( int i = 0; i < size; i++ )
   {
      CBEMPUISpreadCol* z = GetAt(i);
      delete z;
   }
   RemoveAll();
}

//void CBEMPUISpreadColArray::Serialize(CArchive& ar, int iFileVer)
//{
//   if (ar.IsStoring())   
//   {
//      int nCol = GetSize();
//      ar << (WORD)nCol;
//      for (int i = 0; i < nCol; i++)
//      {
//         CBEMPUISpreadCol* pCol = GetAt(i);
//         pCol->Serialize(ar, iFileVer);
//      }
//   }
//   else
//   {
//      WORD nCol;
//      ar >> nCol;
//      int numCol = (int)nCol;
//      for (int i = 0; i < numCol; i++)
//      {
//         CBEMPUISpreadCol* pCol = new CBEMPUISpreadCol();
//         pCol->Serialize(ar, iFileVer);
//         Add(pCol);
//      }      
//   }
//}

#ifdef _DEBUG
void CBEMPUISpreadColArray::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMPUISpreadColArray::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif


///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadConfig                       //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMPUISpreadConfig, CObject, 1)

CBEMPUISpreadConfig::CBEMPUISpreadConfig( long lCompDBID /*=0*/ )
{
   m_lCompDBID = lCompDBID;     // SAC 9/10/01 - Added to enable display/edit of referenced components (for EEM UI)
   m_iAllowRowDeletion = 0;
}

CBEMPUISpreadConfig::~CBEMPUISpreadConfig()
{
   m_aColumns.RemoveAll();
}

//void CBEMPUISpreadConfig::Serialize(CArchive& ar, int iFileVer)
//{
//   if (ar.IsStoring())   
//   {
//      ar << m_i1ClassIdx;
//      ar << m_iLockedCols;    
//      ar << m_iConfigMode;
//      ar << m_iRowHdr;
//      ar << m_iRowHdrFont;
//      ar << m_iRowHdrHeight;
//      ar << m_iRowHdrColWidth;
//   }
//   else
//   {
//      ar >> m_i1ClassIdx;
//      ar >> m_iLockedCols;
//      ar >> m_iConfigMode;
//      ar >> m_iRowHdr;
//      ar >> m_iRowHdrFont;
//      ar >> m_iRowHdrHeight;
//      ar >> m_iRowHdrColWidth;
//   }
//   m_aColumns.Serialize(ar, iFileVer);
//}

BOOL CBEMPUISpreadConfig::ReadText( CTextIO& file, int i1ClassIdx, CBEMPUIPage* pPage, int iFileStructVersion )
{
   BOOL bRetVal = TRUE;

   m_i1ClassIdx = i1ClassIdx;

   m_iConfigMode = 0;   // 0=>Normal, 1=>Transpose

// SAC 6/8/00
   CString sNumRowsProperty = file.ReadString();
   file.PostReadToken();
   if (sNumRowsProperty.CompareNoCase( "None" ) == 0)
      m_lNumRowsDBID = 0;
   else
   {
      m_lNumRowsDBID = BEMPX_GetDatabaseID( sNumRowsProperty, i1ClassIdx );
      if (m_lNumRowsDBID < 0)
         PostReadError( pPage, sNumRowsProperty, "NumRows parameter", file.GetLineCount() );
// return FALSE ??
   }

// SAC 8/9/02 - Added to enable header string above row numbers
   m_sTopLeftHdrLabel = file.ReadString();
   file.PostReadToken();

// RW 8/23/02 - Added to check if user has the ability to delete rows   
   if( iFileStructVersion > 2 )
   {
      file >> m_iAllowRowDeletion;
      file.PostReadToken();
   }
   else
      m_iAllowRowDeletion = 0;

   m_iRowHdr = 1;       // 0=>none, 1=>Numbers?
   m_iRowHdrFont = ReadFont( file );
   file >> m_iRowHdrColWidth;
   file.PostReadToken();
   file >> m_iRowHdrHeight;
   file.PostReadToken();

// SAC 2/1/01 - Added to enable modified row labels and lines to separate row groups
   file >> m_iRowGrouping;
   file.PostReadToken();

   file >> m_iLockedCols;
   file.PostReadToken();

   int iNumCols;
   file >> iNumCols;
   file.PostReadToken();
   ASSERT( iNumCols > 0 );
   for (int iCol=0; (bRetVal && iCol<iNumCols); iCol++)
   {
      CBEMPUISpreadCol* pCol = new CBEMPUISpreadCol();
      bRetVal = pCol->ReadText( file, m_i1ClassIdx, pPage );
      if (bRetVal)
         m_aColumns.Add( pCol );
   }

   return bRetVal;
}

#ifdef _DEBUG
void CBEMPUISpreadConfig::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMPUISpreadConfig::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif

///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadConfigArray                  //
///////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBEMPUISpreadConfigArray, CObject, 1)

CBEMPUISpreadConfigArray::CBEMPUISpreadConfigArray()
{
}

CBEMPUISpreadConfigArray::~CBEMPUISpreadConfigArray()
{
}

void CBEMPUISpreadConfigArray::DeleteContents()
{
   int size = GetSize();
   for( int i = 0; i < size; i++ )
   {
      CBEMPUISpreadConfig* z = GetAt(i);
      z->m_aColumns.DeleteContents();
      z->m_aColumns.RemoveAll();
      delete z;
   }
   RemoveAll();
}

//void CBEMPUISpreadConfigArray::Serialize(CArchive& ar, int iFileVer)
//{
//   if (ar.IsStoring())   
//   {
//      int nConfig = GetSize();
//      ar << (WORD)nConfig;
//      for (int i = 0; i < nConfig; i++)
//      {
//         CBEMPUISpreadConfig* pConfig = GetAt(i);
//         pConfig->Serialize(ar, iFileVer);
//      }
//   }
//   else
//   {
//      WORD nConfig;
//      ar >> nConfig;
//      int numConfig = (int)nConfig;
//      for (int i = 0; i < numConfig; i++)
//      {
//         CBEMPUISpreadConfig* pConfig = new CBEMPUISpreadConfig();
//         pConfig->Serialize(ar, iFileVer);
//         Add(pConfig);
//      }
//   }
//}

#ifdef _DEBUG
void CBEMPUISpreadConfigArray::AssertValid() const
{
   CObject::AssertValid();
}
void CBEMPUISpreadConfigArray::Dump( CDumpContext& dc) const
{
   CObject::Dump(dc);
}
#endif
