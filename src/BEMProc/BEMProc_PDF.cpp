/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2022, SAC Software Solutions, LLC
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
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <memory>
#include <sys/timeb.h>
#include <boost/filesystem.hpp>
#include <hpdf.h>

#include "BEMProc.h"
#include "BEMProcI.h"
#include "BEMProc_FileIO.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMProcObject.h"
#include "expTextIO.h"

#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
using namespace boost::posix_time;

#include "expFormula.h"

#pragma warning(disable : 4127)
#include <QtXml/qdom.h>
#include <QtCore/qfile.h>
#include <QtCore/qiodevice.h>
#include <QtCore/qtextstream.h>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#pragma warning(default : 4127)


jmp_buf env;

void error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
   printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
               (HPDF_UINT)detail_no);
   BEMPX_WriteLogFile( QString( "ERROR: error_no=%1, detail_no=%2" ).arg( QString::number( (HPDF_UINT)error_no ), QString::number( (HPDF_UINT)detail_no ) ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
   longjmp(env, 1);
}

int no = 0;

void PrintText(HPDF_Page page)
{
    char buf[512];
    HPDF_Point pos = HPDF_Page_GetCurrentTextPos (page);

    no++;
    #ifdef __WIN32__
    _snprintf (buf, 512, ".[%d]%0.2f %0.2f", no, pos.x, pos.y);
    #else
    snprintf (buf, 512, ".[%d]%0.2f %0.2f", no, pos.x, pos.y);
    #endif
    HPDF_Page_ShowText(page, buf);
}

static void print_grid  (HPDF_Doc pdf, HPDF_Page page);

static int GeneratePDF_CUACSubmittal( const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx );
static int GeneratePDF_CUACDetails(   const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx );

int BEMPX_GeneratePDF( const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx )
//int Testing( const char* pszPDFPathFile, int iPDFID, int iBEMProcIdx )
{
   int iRetVal = -1;

   if (iPDFID < 10)
      iRetVal = GeneratePDF_CUACSubmittal( pszPDFPathFile, pszRptGraphicsPath, iPDFID, iBEMProcIdx );
   else if (iPDFID < 20)
      iRetVal = GeneratePDF_CUACDetails(   pszPDFPathFile, pszRptGraphicsPath, iPDFID, iBEMProcIdx );    // SAC 01/03/23

   return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////

static const char* pszMoLabel[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

void GenerateTable_TypeMonths( HPDF_Page& page, HPDF_Font& font, HPDF_Font& fontBold, int& iCurY, const char* pszTitle, const char* pszCUACResProp,      // SAC 01/12/23
                                 long lNumUnitTypes, int* iaPosUnitTypeIdxs, long lDBID_ResRef, int iBEMProcIdx,
                                 int iPgTop, int iPgLeft, int iPgRight, int iPgCenter )
{  QString qsLabel;
   int iTblColWds[2], iTblColLeftX[13], iTableColMid, iCol, iSpecVal, iErr;
   int iCUAC_BEMProcIdx = -1;  // ???

   iCurY -= 18;
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, pszTitle )/2), iCurY, pszTitle );
   HPDF_Page_EndText (page);

   int iRectHt = 12; 
//   iCurY -= (iRectHt+8);
   iCurY -= (iRectHt+6);
   iTblColWds[0] = 100;
   iTblColWds[1] = (iPgRight - iPgLeft - iTblColWds[0])/12;
   iTblColLeftX[0] = iPgLeft;
   iTblColLeftX[1] = iPgLeft + iTblColWds[0];
   iTableColMid =  iTblColWds[1] / 2;
//   int iTextDY = 4;
   int iTextDY = 3;
   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   for (iCol=0; iCol<=12; iCol++)
   {  if (iCol > 1)
         iTblColLeftX[iCol] = iTblColLeftX[iCol-1] + iTblColWds[1];
      HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 1 ? 1 : iCol)], iRectHt );
   }
   HPDF_Page_FillStroke (page);
   HPDF_Page_SetGrayFill (page, 0);
   HPDF_Page_SetFontAndSize (page, font, 9);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + iTextDY, "Apartment Type" );
   for (iCol=1; iCol<=12; iCol++)
      HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-1] )/2),  iCurY + 4, pszMoLabel[iCol-1] );
   HPDF_Page_EndText (page);

//   HPDF_Page_SetFontAndSize (page, font, 10);      // SAC 01/12/23
   for (int iMtr=0; iMtr < lNumUnitTypes; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  iCurY -= iRectHt;
            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            for (iCol=0; iCol<=12; iCol++)
               HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 1 ? 1 : iCol)], iRectHt );
            HPDF_Page_Stroke (page);

            HPDF_Page_BeginText (page);
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
            HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
            for (iCol=0; iCol<12; iCol++)
            {  BEMPX_GetString( BEMPX_GetDatabaseID( pszCUACResProp )+iCol, qsLabel, TRUE, 1, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );
               HPDF_Page_TextOut (page, iTblColLeftX[iCol+1] + iTableColMid - (HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData())/2), iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
            }
            HPDF_Page_EndText (page);
      }  }
   return;
}

#define NumCols_DetailRpt_FuelDetails  16   // SAC 02/08/23

void GenerateTable_UnitDetails_Header( HPDF_Page& page, HPDF_Font& font, HPDF_Font& fontBold, int& iCurY, const char* pszTitle,     // SAC 01/22/23
                                          int* iTblColWds, int* iTblColLeftX, int iPgLeft, int iPgRight, int iPgCenter )
{  QString qsLabel;
   int iTableColMid, iCol;  //, iSpecVal, iErr;

   iCurY -= 18;
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, pszTitle )/2), iCurY, pszTitle );
   HPDF_Page_EndText (page);

   int iRectHt = 22; 
   iCurY -= (iRectHt+6);
   iTblColWds[0] = 80;
   iTblColWds[1] = 60;
   iTblColWds[2] = 40;
   iTblColWds[3] = 50;
   iTblColWds[4] = (iPgRight - iPgLeft - (iTblColWds[0]+iTblColWds[1]+iTblColWds[2]+iTblColWds[3]))/12;
   iTblColLeftX[0] = iPgLeft;
   iTableColMid =  iTblColWds[4] / 2;
   int iTextDY = 3;
   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   for (iCol=0; iCol<=15; iCol++)
   {  if (iCol > 4)
         iTblColWds[iCol] = iTblColWds[4];
      if (iCol > 0)
         iTblColLeftX[iCol] = iTblColLeftX[iCol-1] + iTblColWds[iCol-1];
      HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[iCol], iRectHt );
   }
   HPDF_Page_FillStroke (page);
   HPDF_Page_SetGrayFill (page, 0);
   HPDF_Page_SetFontAndSize (page, font, 9);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + iTextDY, "Apartment Type" );
   HPDF_Page_TextOut (page, iTblColLeftX[1] + 4,  iCurY + iTextDY, "End Use" );
   HPDF_Page_EndText (page);
   HPDF_Page_SetFontAndSize (page, font, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Daily"  )/2),  iCurY + iTextDY+10, "Daily"  );
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Avg"    )/2),  iCurY + iTextDY   , "Avg"    );
   HPDF_Page_TextOut (page, iTblColLeftX[3] + (iTblColWds[3]/2) - (HPDF_Page_TextWidth (page, "Annual" )/2),  iCurY + iTextDY+10, "Annual" );
   HPDF_Page_TextOut (page, iTblColLeftX[3] + (iTblColWds[3]/2) - (HPDF_Page_TextWidth (page, "Total"  )/2),  iCurY + iTextDY   , "Total"  );
   HPDF_Page_EndText (page);
   HPDF_Page_SetFontAndSize (page, font, 9);
   HPDF_Page_BeginText (page);
   for (iCol=4; iCol<NumCols_DetailRpt_FuelDetails; iCol++)
      HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-4] )/2),  iCurY + 4, pszMoLabel[iCol-4] );
   HPDF_Page_EndText (page);
   return;
}

#define  Num_Elec_Enduses  11
const char*  pszElecEnduseName[]  = { "Cooking", "Cooling", "DHW", "Dishwasher", "Dryer", "Heating", "IAQ Vent.", "Lighting", "Plug Loads", "Refrigerator", "Washer",  NULL  };
const char*  pszElecEnduseProps[] = { "CUACResults:CkgElecUse", "CUACResults:ClgElecUse", "CUACResults:DHWElecUse", "CUACResults:DishElecUse", "CUACResults:DryerElecUse", "CUACResults:HtgElecUse",
                                      "CUACResults:IAQVentElecUse", "CUACResults:LtgElecUse", "CUACResults:PlugLdsElecUse", "CUACResults:RfrgElecUse", "CUACResults:WashElecUse",  NULL  };
int iaEnduseDetailsArrIdx[] = {  13, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };

#define  Num_Gas_Enduses    4
const char*  pszGasEnduseName[]   = { "Cooking", "DHW", "Dryer", "Heating",  NULL  };
const char*  pszGasEnduseProps[]  = { "CUACResults:CkgGasUse", "CUACResults:DHWGasUse", "CUACResults:DryerGasUse", "CUACResults:HtgGasUse",  NULL  };

void GenerateTable_UnitDetails_FuelTable( HPDF_Page& page, HPDF_Font& font, HPDF_Font& fontBold, int& iCurY,      // SAC 01/23/23
                                          int* iTblColWds, int* iTblColLeftX, int iPgLeft, int iPgRight, int iPgCenter, int iResObjIdx, int iMtrIdx, int iBEMProcIdx,
                                          int iNumEnduses, const char** psvaEnduseNames, const char** psvaEnduseProps, int* piaEnduseDetailsArrIdx, double dResultMult )
{  QString qsLabel;
   int iCol, iRow;  //, iSpecVal, iErr;

   int iRectHt = 12;       // SAC 02/08/23
   int iTextDY = 3;
   HPDF_Page_SetLineWidth (page, 0.25);
   for (iCol=0; iCol<NumCols_DetailRpt_FuelDetails; iCol++)
   {  HPDF_Page_MoveTo(page, iTblColLeftX[iCol] + iTblColWds[iCol], iCurY );      HPDF_Page_LineTo(page, iTblColLeftX[iCol] + iTblColWds[iCol], iCurY - (iRectHt * iNumEnduses) );
   }
      HPDF_Page_MoveTo(page, iTblColLeftX[0],                                                                             iCurY - (iRectHt * iNumEnduses) );
      HPDF_Page_LineTo(page, iTblColLeftX[NumCols_DetailRpt_FuelDetails-1] + iTblColWds[NumCols_DetailRpt_FuelDetails-1], iCurY - (iRectHt * iNumEnduses) );
   HPDF_Page_Stroke  (page);

   iCurY -= iRectHt;
   HPDF_Page_SetFontAndSize (page, font, 9);
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
   HPDF_Page_EndText (page);

   double dVal;
   for (iRow=0; iRow < iNumEnduses; iRow++)
   {
      if (iRow < (iNumEnduses-1))
      {  HPDF_Page_MoveTo(page, iTblColLeftX[1],                                                                             iCurY );
         HPDF_Page_LineTo(page, iTblColLeftX[NumCols_DetailRpt_FuelDetails-1] + iTblColWds[NumCols_DetailRpt_FuelDetails-1], iCurY );
         HPDF_Page_Stroke(page);
      }

      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iTblColLeftX[1]+4, iCurY+iTextDY, psvaEnduseNames[iRow] );
      for (iCol=0; iCol < 14; iCol++)
      {  //BEMPX_GetString( BEMPX_GetDatabaseID( psvaEnduseProps[iRow] ) + iaEnduseDetailsArrIdx[iCol], qsLabel, TRUE, 1, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );
         if (BEMPX_GetFloat( BEMPX_GetDatabaseID( psvaEnduseProps[iRow] ) + iaEnduseDetailsArrIdx[iCol], dVal, 0.0, -1, iResObjIdx, BEMO_User, iBEMProcIdx ))     // enable use of dResultMult - SAC 02-09-23
         {  qsLabel = BEMPX_FloatToString( dVal * dResultMult, 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );   // int iZeroFillLeftToLength=0, BOOL bTrimTrailingDecZeroes=FALSE );
            int iTxtX = iTblColLeftX[iCol+2] + iTblColWds[iCol+2] - ((int) HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData())) - 4;
            if (iCol==0)
               iTxtX -= (int) (iTblColWds[iCol+2] * 0.2);
            HPDF_Page_TextOut (page, iTxtX, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
      }  }
      HPDF_Page_EndText (page);
      iCurY -= iRectHt;
   }
   iCurY += iRectHt;
   return;
}


// //void GenerateTable_Details_StartNewPage( HPDF_Doc& pdf, HPDF_Page& page, HPDF_Image& image, HPDF_Font& font, HPDF_Font& fontBold, int& iCurX, int& iCurY,      // SAC 01/22/23
// //void GenerateTable_Details_PageHeader( HPDF_Page& page, HPDF_Image& image, HPDF_Font& font, HPDF_Font& fontBold, int& iCurY,      // SAC 01/22/23
// void GenerateTable_Details_PageHeader( HPDF_Doc& pdf, HPDF_Page& page, HPDF_Font& font, HPDF_Font& fontBold, const char* pszRptGraphicsPath, int& iCurY,      // SAC 01/22/23
//                                     int iPgTop, int iPgLeft, int iPgCenter, int iPageNum, QString qsProjID, QString qsRunDateFmt, QString qsProjNameTitle )
// {
// //   page = HPDF_AddPage (pdf);     // SAC 01/05/23
// //   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, (bPortrait ? HPDF_PAGE_PORTRAIT : HPDF_PAGE_LANDSCAPE) );
// //
// //   if (bPrintGrid)
// //      print_grid  (pdf, page);
// 
//    iCurY = iPgTop;
// //   iCurX = iPgLeft;
// 
//    /* print the title of the page (with positioning center). */
//    HPDF_Page_SetFontAndSize (page, fontBold, 6);
//    //tw = HPDF_Page_TextWidth (page, page_title);
//    iCurY -= 25;
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iPgLeft, iCurY, "STATE OF CALIFORNIA");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 12;
//    HPDF_Page_SetFontAndSize (page, fontBold, 10);
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iPgLeft, iCurY, "CALIFORNIA ENERGY COMMISSION");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 3;
//    HPDF_Page_SetGrayFill (page, 0);  // 0.5);
//    HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
//    HPDF_Page_SetLineWidth (page, 1.25);
//    HPDF_Page_MoveTo  (page, iPgLeft, iCurY );
//    HPDF_Page_LineTo  (page,   230, iCurY );
//    HPDF_Page_Stroke (page);
// 
//    iCurY -= 11;
//    HPDF_Page_SetFontAndSize (page, fontBold, 8);
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iPgLeft, iCurY, "UTILITY Allowance Calculation Tool");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 13;
//    if (!qsProjID.isEmpty())
//    {  HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iPgLeft, iCurY, qsProjID.toLocal8Bit().constData() );   
//       HPDF_Page_EndText (page);
//    }
// 
// ////   image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
// //   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23
// 
//    HPDF_Image image;
//    QString qsLogoPathFN = pszRptGraphicsPath;   qsLogoPathFN += "CEC.jpg";
//    //image = HPDF_LoadJpegImageFromFile (pdf, "D:\\Dev\\svn-CEC\\SF_CBECC-Com\\branches\\CBECC_CUAC\\CBECC-Com64\\Data\\Rulesets\\T24N_2022\\RTF\\CEC.jpg");
//    image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
// //   HPDF_Page_DrawImage (page, image, 240, iPgTop-91, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));
//    HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo - SAC 01/13/23
// 
// 
//    HPDF_REAL tw1, tw2;
//    if (!qsRunDateFmt.isEmpty())
//    {  iCurY = iPgTop - 56;
//       int iMidX = 690;   // 505;    - landscaoe vs. portrait
// //      rect.left = 630;   // 450;    - landscaoe vs. portrait
// //      rect.top = iCurY+12;
// 
//             // TESTING max date/time string
//             //qsRunDateFmt = "12/30/2023 12:33:33 PM";
// //      rect.right = iPgRight;
// //      rect.bottom = iCurY-2;
//       HPDF_Page_SetFontAndSize (page, fontBold, 8);
//       tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
//       QString qsPageNumTitle = QString( "Page %1" ).arg( QString::number( iPageNum ) );
//       tw2 = HPDF_Page_TextWidth (page, qsPageNumTitle.toLocal8Bit().constData());
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
//       HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPageNumTitle.toLocal8Bit().constData());
//       HPDF_Page_EndText (page);
//    }
// 
//    HPDF_Page_SetFontAndSize (page, fontBold, 10); 
//    iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
// 
//    return;
// }


int GeneratePDF_CUACDetails(   const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx )
{
   HPDF_Doc  pdf;
   HPDF_Page page;
   HPDF_Font font, fontBold;
//   HPDF_Rect rect;

   iPDFID;
   iBEMProcIdx;

   //  1 "Draft" / 2 "Final" / 3 "Annual"
   QString sRptType = (iPDFID == 11 ? "Draft" : (iPDFID == 12 ? "Final" : "Annual" ));
   QString sRptName = "Project Details";

   pdf = HPDF_New (error_handler, NULL);
   if (!pdf) {
       printf ("error: cannot create PdfDoc object\n");
       return 1;
   }
   if (setjmp(env)) {
       HPDF_Free (pdf);
       return 1;
   }
   /* add a new page object. */
   page = HPDF_AddPage (pdf);
   //HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);      // SAC 01/03/23

//   print_grid  (pdf, page);

   font     = HPDF_GetFont (pdf, "Helvetica", NULL);
   fontBold = HPDF_GetFont (pdf, "Helvetica-Bold", NULL);

   int iPgTop = HPDF_Page_GetHeight (page);
   int iPgLeft = 45, iPgRight = 745;    // 560;    - landscaoe vs. portrait
   int iPgCenter = (iPgLeft+iPgRight)/2;
   int iCurY = iPgTop, iCurX = iPgLeft;
   QString qsLabel, qsLabel2, qsLabel3, qsLabel4, qsLabel5, qsTemp;
   HPDF_REAL tw1, tw2;

   /* print the title of the page (with positioning center). */
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   //tw = HPDF_Page_TextWidth (page, page_title);
   iCurY -= 25;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
//   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ProjectID" ), qsLabel,  FALSE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   QString qsProjID;
   if (!qsLabel.isEmpty())
   {  qsProjID = QString( "%1 - Project ID:  %2" ).arg( sRptName, qsLabel );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
      HPDF_Page_EndText (page);
   }

   HPDF_Image image;
   QString qsLogoPathFN = pszRptGraphicsPath;   qsLogoPathFN += "CEC.jpg";
   //image = HPDF_LoadJpegImageFromFile (pdf, "D:\\Dev\\svn-CEC\\SF_CBECC-Com\\branches\\CBECC_CUAC\\CBECC-Com64\\Data\\Rulesets\\T24N_2022\\RTF\\CEC.jpg");
   image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
//   HPDF_Page_DrawImage (page, image, 240, iPgTop-91, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));
   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo - SAC 01/13/23

   QString qsRunDateFmt;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), qsRunDateFmt, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 56;
      int iMidX = 690;   // 505;    - landscaoe vs. portrait
//      rect.left = 630;   // 450;    - landscaoe vs. portrait
//      rect.top = iCurY+12;

            // TESTING max date/time string
            //qsRunDateFmt = "12/30/2023 12:33:33 PM";
//      rect.right = iPgRight;
//      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 1" );  // "Page 1 of 6");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, "Page 1" );  // "Page 1 of 6");
      HPDF_Page_EndText (page);
   }

   QString qsProjNameTitle;
   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Name" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      // SAC 01/04/23
   if (qsLabel2.isEmpty())
      qsProjNameTitle = QString( "Project - %1" ).arg( sRptType );
   else
      qsProjNameTitle = QString( "%1 - %2" ).arg( qsLabel2, sRptType );
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   tw1 = HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() );
   iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(tw1/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
   HPDF_Page_EndText (page);


   int iProjInfoLeftX = 150, iProjInfoLeftLen = 290,  iProjInfoRightX = 540, iProjInfoRightLen = 200,  iProjInfoMarginX = 10,  iProjInfoRowHt = 16;      // SAC 01/05/23
   iCurY -= 20;
   HPDF_Page_SetFontAndSize (page, font, 10); 
   tw1 = HPDF_Page_TextWidth (page, "Project Information" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iProjInfoLeftX-iProjInfoMarginX-tw1, iCurY, "Project Information" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iProjInfoLeftX , iCurY, "Site"  );
   HPDF_Page_TextOut (page, iProjInfoRightX, iCurY, "Owner" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 8); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Address"            ), iCurY - (iProjInfoRowHt *  1), "Address"             );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "City"               ), iCurY - (iProjInfoRowHt *  2), "City"                );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Zip"                ), iCurY - (iProjInfoRowHt *  3), "Zip"                 );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Project Type"       ), iCurY - (iProjInfoRowHt *  4), "Project Type"        );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Electric   Utility" ), iCurY - (iProjInfoRowHt *  5), "Electric   Utility"  );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  6), "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt *  7), "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Type"        ), iCurY - (iProjInfoRowHt *  8), "Tariff Type"         );      // SAC 01/25/24
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Adj."        ), iCurY - (iProjInfoRowHt *  9), "Tariff Adj."         );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Gas   Utility"      ), iCurY - (iProjInfoRowHt * 10), "Gas   Utility"       );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt * 11), "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt * 12), "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Type"        ), iCurY - (iProjInfoRowHt * 13), "Tariff Type"         );      // SAC 01/25/24

   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Owner Name"         ), iCurY - (iProjInfoRowHt *  1), "Owner Name"          );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Address"            ), iCurY - (iProjInfoRowHt *  2), "Address"             );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "City"               ), iCurY - (iProjInfoRowHt *  3), "City"                );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "State"              ), iCurY - (iProjInfoRowHt *  4), "State"               );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Zip"                ), iCurY - (iProjInfoRowHt *  5), "Zip"                 );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Contact Name"       ), iCurY - (iProjInfoRowHt *  6), "Contact Name"        );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Contact Phone"      ), iCurY - (iProjInfoRowHt *  7), "Contact Phone"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Contact Email"      ), iCurY - (iProjInfoRowHt *  8), "Contact Email"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "APN"                ), iCurY - (iProjInfoRowHt *  9), "APN"                 );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Other Project ID"   ), iCurY - (iProjInfoRowHt * 10), "Other Project ID"    );
   HPDF_Page_EndText (page);

   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_SetFontAndSize (page, font, 9);
   int iRow;
   for (iRow=1; iRow <= 13; iRow++)
   {  switch (iRow)
      {  case  1 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:StAddress"       ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerName"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  2 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:City"            ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerAddress"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  3 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ZipCode"         ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerCity"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  4 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType"        ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerState"     ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  5 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerZIPCode"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  6 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"    ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  7 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactPhone"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  8 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactEMail"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  9 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj"   ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:APN"            ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case 10 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"      ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OtherProjectID" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case 11 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTerritory"  ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;
         case 12 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTariff"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;
         case 13 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariffType"   ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = " ";   break;     // SAC 01/25/24
      } 
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iProjInfoLeftX , iCurY - (iProjInfoRowHt * iRow),  qsLabel.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iProjInfoRightX, iCurY - (iProjInfoRowHt * iRow), qsLabel2.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

         HPDF_Page_MoveTo  (page, iProjInfoLeftX -2, iCurY - (iProjInfoRowHt * iRow)-3 );     HPDF_Page_LineTo  (page, iProjInfoLeftX +iProjInfoLeftLen , iCurY - (iProjInfoRowHt * iRow)-3 );
      if (iRow <= 10)
      {  HPDF_Page_MoveTo  (page, iProjInfoRightX-2, iCurY - (iProjInfoRowHt * iRow)-3 );     HPDF_Page_LineTo  (page, iProjInfoRightX+iProjInfoRightLen, iCurY - (iProjInfoRowHt * iRow)-3 );  }
      HPDF_Page_Stroke  (page);
   }
   iCurY -= ((iProjInfoRowHt * 13) + 30);


   // export of Allowance results - SAC 01/05/23
#define  NumDwellingMeters   7
   int iCUAC_BEMProcIdx = -1;  // ???
   int iMtr, iSpecVal, iErr, iCol;     double dTemp;
   long laNumUnitsByBedrms[NumDwellingMeters], laNumMktRateUnitsByBedrms[NumDwellingMeters], lTemp, lNumUnitTypes=0;
   int iaPosUnitTypeIdxs[NumDwellingMeters] = {-1,-1,-1,-1,-1,-1,-1};
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:AffordableUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0)
      {  laNumUnitsByBedrms[iMtr] = lTemp;
         iaPosUnitTypeIdxs[lNumUnitTypes] = iMtr;
         lNumUnitTypes++;
         if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResProj:NumDwellingUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp >= laNumUnitsByBedrms[iMtr])
            laNumMktRateUnitsByBedrms[iMtr] = lTemp - laNumUnitsByBedrms[iMtr];
         else
         {  assert( false );
            laNumMktRateUnitsByBedrms[iMtr] = 0;
         }
      }
      else
      {  laNumUnitsByBedrms[iMtr] = 0;
         laNumMktRateUnitsByBedrms[iMtr] = 0;
   }  }

   int iRectHt = 45;     // SAC 12/05/22
   iCurY -= iRectHt;
   int iTableColWd  = (iPgRight-iPgLeft - 190) / 8;
   int iTableColMid =  iTableColWd / 2;
   int iTableLeft   =  iPgRight - (iTableColWd * 8);
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   HPDF_Page_Rectangle (page, iPgLeft, iCurY, (iPgRight-iPgLeft), iRectHt );
   HPDF_Page_FillStroke (page);

   HPDF_Page_Rectangle (page, iTableLeft - 66     , iCurY   ,       66         ,         28 );   // Tot Avg Mo Cost
   HPDF_Page_Rectangle (page, iTableLeft - 66 - 54, iCurY   ,       54         ,         28 );   // Tot Ann Cost
   HPDF_Page_Rectangle (page, iTableLeft          , iCurY+28, (iTableColWd * 8), iRectHt-28 );   // Project Details

   HPDF_Page_Rectangle (page, iTableLeft                , iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+ iTableColWd   , iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*2), iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*3), iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*4), iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*5), iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*6), iCurY, iTableColWd, 28 );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*7), iCurY, iTableColWd, 28 );
   HPDF_Page_Stroke (page);

   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
//   HPDF_Page_TextOut (page, iPgLeft+3  , iCurY+10, "Apartment Type" );
   HPDF_Page_TextOut (page, iPgLeft+ 93, iCurY+33, "Project Summary" );
   HPDF_Page_TextOut (page, iPgLeft+415, iCurY+33, "Project Details" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgLeft    + 35 - (HPDF_Page_TextWidth (page, "Apartment"       )/2), iCurY + 16, "Apartment"        );
   HPDF_Page_TextOut (page, iPgLeft    + 35 - (HPDF_Page_TextWidth (page, "Type"            )/2), iCurY +  5, "Type"             );
   HPDF_Page_TextOut (page, iTableLeft - 93 - (HPDF_Page_TextWidth (page, "Total Annual"    )/2), iCurY + 16, "Total Annual"     );
   HPDF_Page_TextOut (page, iTableLeft - 93 - (HPDF_Page_TextWidth (page, "Cost ($)"        )/2), iCurY +  5, "Cost ($)"         );
   HPDF_Page_TextOut (page, iTableLeft - 33 - (HPDF_Page_TextWidth (page, "Average Monthly" )/2), iCurY + 16, "Average Monthly"  );
   HPDF_Page_TextOut (page, iTableLeft - 33 - (HPDF_Page_TextWidth (page, "Cost ($)"        )/2), iCurY +  5, "Cost ($)"         );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 0) + iTableColMid - (HPDF_Page_TextWidth (page, "Electric"         )/2), iCurY + 16, "Electric"         );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 0) + iTableColMid - (HPDF_Page_TextWidth (page, "Annual Cost ($)"  )/2), iCurY +  5, "Annual Cost ($)"  );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 1) + iTableColMid - (HPDF_Page_TextWidth (page, "Electric"         )/2), iCurY + 16, "Electric"         );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 1) + iTableColMid - (HPDF_Page_TextWidth (page, "Monthly Cost ($)" )/2), iCurY +  5, "Monthly Cost ($)" );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 2) + iTableColMid - (HPDF_Page_TextWidth (page, "Gas"              )/2), iCurY + 16, "Gas"              );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 2) + iTableColMid - (HPDF_Page_TextWidth (page, "Annual Cost ($)"  )/2), iCurY +  5, "Annual Cost ($)"  );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 3) + iTableColMid - (HPDF_Page_TextWidth (page, "Gas"              )/2), iCurY + 16, "Gas"              );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 3) + iTableColMid - (HPDF_Page_TextWidth (page, "Monthly Cost ($)" )/2), iCurY +  5, "Monthly Cost ($)" );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 4) + iTableColMid - (HPDF_Page_TextWidth (page, "Water"            )/2), iCurY + 16, "Water"            );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 4) + iTableColMid - (HPDF_Page_TextWidth (page, "Annual Cost ($)"  )/2), iCurY +  5, "Annual Cost ($)"  );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 5) + iTableColMid - (HPDF_Page_TextWidth (page, "Water"            )/2), iCurY + 16, "Water"            );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 5) + iTableColMid - (HPDF_Page_TextWidth (page, "Monthly Cost ($)" )/2), iCurY +  5, "Monthly Cost ($)" );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 6) + iTableColMid - (HPDF_Page_TextWidth (page, "Trash"            )/2), iCurY + 16, "Trash"            );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 6) + iTableColMid - (HPDF_Page_TextWidth (page, "Annual Cost ($)"  )/2), iCurY +  5, "Annual Cost ($)"  );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 7) + iTableColMid - (HPDF_Page_TextWidth (page, "Trash"            )/2), iCurY + 16, "Trash"            );
   HPDF_Page_TextOut (page, iTableLeft + (iTableColWd * 7) + iTableColMid - (HPDF_Page_TextWidth (page, "Monthly Cost ($)" )/2), iCurY +  5, "Monthly Cost ($)" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 10);     // SAC 01/05/23
   iRectHt = 15;
   int iUnitTypeColWd = iTableLeft - iPgLeft - 120;
   double dVal;
   long lDBID_ResRef = BEMPX_GetDatabaseID( "CUAC:CUACResultsRef" );       assert( lDBID_ResRef > 0 );
   for (iMtr=0; iMtr < lNumUnitTypes; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  iCurY -= iRectHt;
            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            HPDF_Page_Rectangle (page, iPgLeft                   , iCurY, iUnitTypeColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iPgLeft+iUnitTypeColWd    , iCurY, 54, iRectHt );  
            HPDF_Page_Rectangle (page, iPgLeft+iUnitTypeColWd+54 , iCurY, 66, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft                , iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+ iTableColWd   , iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*2), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*3), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*4), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*5), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*6), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*7), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Stroke (page);

            HPDF_Page_BeginText (page);
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
            HPDF_Page_TextOut (page, iPgLeft+3, iCurY+4, qsLabel.toLocal8Bit().constData() );

            const char* pszaColVars[] = { "CUACResults:TotCosts[1]", "CUACResults:TotCosts[2]", "CUACResults:ElecCosts[1]", "CUACResults:ElecCosts[2]", "CUACResults:GasCosts[1]",
                                          "CUACResults:GasCosts[2]", "CUACResults:WaterCosts[1]", "CUACResults:WaterCosts[2]", NULL, "CUACResults:TrashMonthlyCost" };
            int iaColMidX[] = {  iTableLeft - 93, iTableLeft - 33, iTableLeft+iTableColMid, iTableLeft+iTableColMid+iTableColWd,
                                 iTableLeft+iTableColMid+(iTableColWd*2), iTableLeft+iTableColMid+(iTableColWd*3), iTableLeft+iTableColMid+(iTableColWd*4),
                                 iTableLeft+iTableColMid+(iTableColWd*5), iTableLeft+iTableColMid+(iTableColWd*6), iTableLeft+iTableColMid+(iTableColWd*7) };
            for (iCol=0; iCol<10; iCol++)
            {  if (iCol == 8)
               {  dVal = BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:TrashMonthlyCost" ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx );
                  if (dVal > 0)
                     qsLabel = BEMPX_FloatToString( (dVal * 12.0), 2 );
                  else
                     qsLabel = "0.00";   // switched from .clear() to "0.00" to prevent leaving column blank - SAC 09/14/23
               }
               else
                  BEMPX_GetString( BEMPX_GetDatabaseID( pszaColVars[iCol] ), qsLabel, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );
               if (!qsLabel.isEmpty())
                  HPDF_Page_TextOut (page, iaColMidX[iCol] - (HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData())/2), iCurY+4, qsLabel.toLocal8Bit().constData() );
            }
            HPDF_Page_EndText (page);
         }
      }


//   int iPageNum = 1;
//   page = HPDF_AddPage (pdf);     // SAC 01/05/23
//   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
//   GenerateTable_Details_PageHeader( pdf, page, /*image,*/ font, fontBold, pszRptGraphicsPath, iCurY, iPgTop, iPgLeft, iPgCenter, ++iPageNum, qsProjID, qsRunDateFmt, qsProjNameTitle );
   ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
   /////              PAGE 2             /////
   ///////////////////////////////////////////
   page = HPDF_AddPage (pdf);     // SAC 01/05/23
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);

//   print_grid  (pdf, page);

   iCurY = iPgTop;
   iCurX = iPgLeft;

   /* print the title of the page (with positioning center). */
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   //tw = HPDF_Page_TextWidth (page, page_title);
   iCurY -= 25;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
   if (!qsProjID.isEmpty())
   {  HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
      HPDF_Page_EndText (page);
   }

//   image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23

   if (!qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 56;
      int iMidX = 690;   // 505;    - landscaoe vs. portrait
//      rect.left = 630;   // 450;    - landscaoe vs. portrait
//      rect.top = iCurY+12;

            // TESTING max date/time string
            //qsRunDateFmt = "12/30/2023 12:33:33 PM";
//      rect.right = iPgRight;
//      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 2");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, "Page 2");
      HPDF_Page_EndText (page);
   }

   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());


   iCurY -= 18;
   HPDF_Page_TextOut (page, 263/*iPgCenter*/-(HPDF_Page_TextWidth (page, "Utility Information" )/2), iCurY, "Utility Information" ); 
   HPDF_Page_TextOut (page, 620/*iPgCenter*/-(HPDF_Page_TextWidth (page, "Fuels" )/2), iCurY, "Fuels" );
   HPDF_Page_EndText (page);

   iCurY -= 17;
   iProjInfoRowHt = 16;
   HPDF_Page_SetFontAndSize (page, fontBold, 9);         // SAC 01/07/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgLeft, iCurY                          , "Electric" );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 3) -3, "Gas"      );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 6) -6, "Trash"    );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 7) -9, "Water"    );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 9)-13, "Community Solar" );      // SAC 10/03/23
   HPDF_Page_EndText (page);

   iProjInfoLeftX = 130;   iProjInfoRightX = 630;     int iProjInfoLeftX2 = 370, iProjInfoLeftX3 = 290;     // mods to lessen territory & widen tariff length - SAC 09/06/23
   HPDF_Page_SetFontAndSize (page, font, 8); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Utility"            ), iCurY                          , "Utility"             );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  1)  , "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX3 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt *  1)  , "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Type"        ), iCurY - (iProjInfoRowHt *  2)  , "Tariff Type"         );    // SAC 01/25/24
   HPDF_Page_TextOut (page, iProjInfoLeftX3 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Adj."        ), iCurY - (iProjInfoRowHt *  2)  , "Tariff Adj."         );    // SAC 01/10/24
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Utility"            ), iCurY - (iProjInfoRowHt *  3)-3, "Utility"             );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  4)-3, "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX3 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt *  4)-3, "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff Type"        ), iCurY - (iProjInfoRowHt *  5)-3, "Tariff Type"         );    // SAC 01/25/24
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Rate Type"          ), iCurY - (iProjInfoRowHt *  6)-6, "Rate Type"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Monthly Charge"     ), iCurY - (iProjInfoRowHt *  6)-6, "Monthly Charge"      );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Rate Type"          ), iCurY - (iProjInfoRowHt *  7)-9, "Rate Type"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Monthly Charge"     ), iCurY - (iProjInfoRowHt *  7)-9, "Monthly Charge"      );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Water $/Gallon"     ), iCurY - (iProjInfoRowHt *  8)-9, "Water $/Gallon"      );
   HPDF_Page_TextOut (page, iProjInfoLeftX2+70 - iProjInfoMarginX - HPDF_Page_TextWidth(page, "Total Allocation" ), iCurY - (iProjInfoRowHt *  9)-13, "Total Allocation"    );    // SAC 10/03/23
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Space Heating"      ), iCurY                          , "Space Heating"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Water Heating"      ), iCurY - (iProjInfoRowHt *  1)  , "Water Heating"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Cooking"            ), iCurY - (iProjInfoRowHt *  2)  , "Cooking"             );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Clothes Dryer"      ), iCurY - (iProjInfoRowHt *  3)  , "Clothes Dryer"       );
   HPDF_Page_EndText (page);

   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY -3 );                          HPDF_Page_LineTo  (page, 480,                iCurY -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, iProjInfoLeftX3-50, iCurY - iProjInfoRowHt -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX3-3,    iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, 480,                iCurY - iProjInfoRowHt -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*2) -3 );     HPDF_Page_LineTo  (page, iProjInfoLeftX3-50, iCurY - (iProjInfoRowHt*2) -3 );       // SAC 01/25/24
   HPDF_Page_MoveTo  (page, iProjInfoLeftX3-3,    iCurY - (iProjInfoRowHt*2) -3 );     HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*2) -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*3) -3-3 );   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*3) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*4) -3-3 );   HPDF_Page_LineTo  (page, iProjInfoLeftX3-50, iCurY - (iProjInfoRowHt*4) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX3-3,    iCurY - (iProjInfoRowHt*4) -3-3 );   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*4) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*5) -3-3 );   HPDF_Page_LineTo  (page, iProjInfoLeftX3-50, iCurY - (iProjInfoRowHt*5) -3-3 );     // SAC 01/25/24
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*6) -3-6 );   HPDF_Page_LineTo  (page, 280,                iCurY - (iProjInfoRowHt*6) -3-6 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3,    iCurY - (iProjInfoRowHt*6) -3-6 );   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*6) -3-6 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*7) -3-9 );   HPDF_Page_LineTo  (page, 280,                iCurY - (iProjInfoRowHt*7) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3,    iCurY - (iProjInfoRowHt*7) -3-9 );   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*7) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3,    iCurY - (iProjInfoRowHt*8) -3-9 );   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*8) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3,    iCurY - (iProjInfoRowHt*9) -3-13);   HPDF_Page_LineTo  (page, 280+70,             iCurY - (iProjInfoRowHt*9) -3-13);     // SAC 10/03/23
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3+70, iCurY - (iProjInfoRowHt*9) -3-13);   HPDF_Page_LineTo  (page, 480,                iCurY - (iProjInfoRowHt*9) -3-13);
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3,    iCurY                      -3 );     HPDF_Page_LineTo  (page, 720,                iCurY                      -3 );                     
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3,    iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, 720,                iCurY -  iProjInfoRowHt    -3 );
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3,    iCurY - (iProjInfoRowHt*2) -3 );     HPDF_Page_LineTo  (page, 720,                iCurY - (iProjInfoRowHt*2) -3 );
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3,    iCurY - (iProjInfoRowHt*3) -3 );     HPDF_Page_LineTo  (page, 720,                iCurY - (iProjInfoRowHt*3) -3 );
   HPDF_Page_Stroke (page);

   HPDF_Page_SetFontAndSize (page, font, 9);    // SAC 01/07/23
   HPDF_Page_BeginText (page);
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), qsLabel4, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    // SAC 01/25/24
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj"   ), qsLabel5, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    // SAC 01/10/24
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY                        , qsLabel.toLocal8Bit().constData()  );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  1), qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX3 , iCurY - (iProjInfoRowHt *  1), qsLabel3.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  2), qsLabel4.toLocal8Bit().constData() );      // SAC 01/25/24
   HPDF_Page_TextOut (page, iProjInfoLeftX3 , iCurY - (iProjInfoRowHt *  2), qsLabel5.toLocal8Bit().constData() );

   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"      ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTerritory"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTariff"     ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariffType"   ), qsLabel4, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    // SAC 01/25/24
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  3)-3, qsLabel.toLocal8Bit().constData()  );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  4)-3, qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX3 , iCurY - (iProjInfoRowHt *  4)-3, qsLabel3.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  5)-3, qsLabel4.toLocal8Bit().constData() );    // SAC 01/25/24
   long lRateType;
   BEMPX_GetString(      BEMPX_GetDatabaseID( "CUAC:TrashRateType"    ), qsLabel  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:TrashRateType"    ), lRateType,        0, -1, 0, BEMO_User, iBEMProcIdx ) && lRateType > 0)  // prevent reporting invalid trash costs - SAC 09/14/23
      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:TrashMonthlyCost" ), qsTemp   ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   else
      qsTemp = "0.00";
   qsLabel2 = QString( "$ %1" ).arg( qsTemp );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  6)-6,  qsLabel.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  6)-6, qsLabel2.toLocal8Bit().constData() );

   BEMPX_GetString(      BEMPX_GetDatabaseID( "CUAC:WaterRateType"    ), qsLabel  , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:WaterRateType"    ), lRateType,        0, -1, 0, BEMO_User, iBEMProcIdx ) && lRateType > 0)  // prevent reporting invalid water costs - SAC 09/14/23
      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:WaterMonthlyCost" ), qsTemp   ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   else
      qsTemp = "0.00";
   qsLabel2 = QString( "$ %1" ).arg( qsTemp );
   if (qsLabel.indexOf("Usage")==0)
   {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:WaterVolumeCost"  ), qsTemp , TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel3 = QString( "$ %1" ).arg( qsTemp );
   }
   else
      qsLabel3.clear();
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  7)-9,  qsLabel.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  7)-9, qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  8)-9, qsLabel3.toLocal8Bit().constData() );

   bool bHaveComunitySolar = false;    // SAC 10/03/23
   if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:UseCommunitySolar"     ), lTemp, 0, -1, 0, BEMO_User, iBEMProcIdx ) && lTemp > 0 &&
       BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:TotCommunitySolarSize" ), dTemp, 0, -1, 0, BEMO_User, iBEMProcIdx ) && dTemp > 0.1)
   {  bHaveComunitySolar = true;
      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarProject" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      BEMPX_GetString(   BEMPX_GetDatabaseID( "CUAC:TotCommunitySolarSize" ), qsTemp , TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = QString( "%1 kW" ).arg( qsTemp );
   }
   else
   {  qsLabel.clear();
      qsLabel2.clear();
   }
   HPDF_Page_TextOut (page, iProjInfoLeftX     , iCurY - (iProjInfoRowHt *  9)-13,  qsLabel.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 +70, iCurY - (iProjInfoRowHt *  9)-13, qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_EndText (page);

   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:GasType" ), qsTemp, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   QString qsFuelType;
   if (qsTemp.compare("NaturalGas")==0)
      qsFuelType = "Natural Gas";
   else if (qsTemp.compare("None")==0)
      qsFuelType = "Unknown Gas";
   else 
      qsFuelType = qsTemp;

   bool baEnduseFuel[4][2] = { { false, false }, { false, false }, { false, false }, { false, false } };     // SpcHtg / WtrHtg / Cookg / Dryer || HaveElec, HaveGas    // SAC 01/07/23
   for (iMtr=0; iMtr < lNumUnitTypes; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {
            baEnduseFuel[0][0] = (baEnduseFuel[0][0] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:HtgElecUse[13]"   ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) >  5);
            baEnduseFuel[0][1] = (baEnduseFuel[0][1] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:HtgGasUse[13]"    ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) > 15);
            baEnduseFuel[1][0] = (baEnduseFuel[1][0] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:DHWElecUse[13]"   ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) >  5);
            baEnduseFuel[1][1] = (baEnduseFuel[1][1] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:DHWGasUse[13]"    ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) > 15);
            baEnduseFuel[2][0] = (baEnduseFuel[2][0] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:CkgElecUse[13]"   ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) >  5);
            baEnduseFuel[2][1] = (baEnduseFuel[2][1] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:CkgGasUse[13]"    ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) > 15);
            baEnduseFuel[3][0] = (baEnduseFuel[3][0] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:DryerElecUse[13]" ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) >  5);
            baEnduseFuel[3][1] = (baEnduseFuel[3][1] || BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:DryerGasUse[13]"  ), iSpecVal, iErr, iResObjIdx, BEMO_User, iBEMProcIdx ) > 15);
      }  }
   HPDF_Page_BeginText (page);
   for (iRow=0; iRow<4; iRow++)
   {  if      (!baEnduseFuel[iRow][0] && !baEnduseFuel[iRow][1])  qsLabel = "None";
      else if ( baEnduseFuel[iRow][0] && !baEnduseFuel[iRow][1])  qsLabel = "Electricity";
      else if (!baEnduseFuel[iRow][0] &&  baEnduseFuel[iRow][1])  qsLabel = qsFuelType;
      else  qsLabel = "Electric & Gas";
      HPDF_Page_TextOut (page, iProjInfoRightX, iCurY - (iProjInfoRowHt * iRow),  qsLabel.toLocal8Bit().constData() );
   }
   HPDF_Page_EndText (page);


   int iTblColWds[4] = { 80, 64, 64, 0 };     // repoistioned Apts Inventory table to right side under 'Fuels' labels - SAC 02/09/23
   int iTblColLeftX[16];
   //iTblColLeftX[0] = iPgCenter - ((iTblColWds[0] + iTblColWds[1] + iTblColWds[2]) / 2);
   iTblColLeftX[0] = iPgRight - (iTblColWds[0] + iTblColWds[1] + iTblColWds[2]);
   iTblColLeftX[1] = iTblColLeftX[0] + iTblColWds[0];
   iTblColLeftX[2] = iTblColLeftX[1] + iTblColWds[1];

   //iCurY -= ((iProjInfoRowHt *  6)+9 + 22);        // SAC 01/08/23
   iCurY -= ((iProjInfoRowHt * 3) + 24);           // shift table up to eb directly below Fuels labels - SAC 02/09/23
   qsLabel = "Apartments Inventory";
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   //HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() )/2), iCurY, qsLabel.toLocal8Bit().constData());
   HPDF_Page_TextOut (page, ((iTblColLeftX[0]+iTblColLeftX[2]+iTblColWds[2])/2)-(HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() )/2), iCurY, qsLabel.toLocal8Bit().constData());
   HPDF_Page_EndText (page);

   iRectHt = 25;     // SAC 01/08/23
   iCurY -= (iRectHt+6);
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   HPDF_Page_Rectangle (page, iTblColLeftX[0], iCurY, iTblColWds[0], iRectHt );
   HPDF_Page_Rectangle (page, iTblColLeftX[1], iCurY, iTblColWds[1], iRectHt );
   HPDF_Page_Rectangle (page, iTblColLeftX[2], iCurY, iTblColWds[2], iRectHt );
   HPDF_Page_FillStroke (page);

   HPDF_Page_SetGrayFill (page, 0);
   HPDF_Page_SetFontAndSize (page, font, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + 4, "Apartment Type"    );
   HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "# Affordable"  )/2), iCurY + 15, "# Affordable"  );
   HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "Housing Units" )/2), iCurY +  4, "Housing Units" );
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "# Market Rate" )/2), iCurY + 15, "# Market Rate" );
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Housing Units" )/2), iCurY +  4, "Housing Units" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 9);      // SAC 01/08/23
   iRectHt = 12;
   int iAptInventoryRowsTop = iCurY;
   for (iMtr=0; iMtr < lNumUnitTypes; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  iCurY -= iRectHt;
            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            HPDF_Page_Rectangle (page, iTblColLeftX[0], iCurY, iTblColWds[0], iRectHt );
            HPDF_Page_Rectangle (page, iTblColLeftX[1], iCurY, iTblColWds[1], iRectHt );
            HPDF_Page_Rectangle (page, iTblColLeftX[2], iCurY, iTblColWds[2], iRectHt );
            HPDF_Page_Stroke (page);

            HPDF_Page_BeginText (page);
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
            HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+3, qsLabel.toLocal8Bit().constData() );

            qsLabel = QString::number( laNumUnitsByBedrms[iMtrIdx] );
            HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]*2/3) -HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData()), iCurY+3, qsLabel.toLocal8Bit().constData() );
            qsLabel = QString::number( laNumMktRateUnitsByBedrms[iMtrIdx] );
            HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]*2/3) -HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData()), iCurY+3, qsLabel.toLocal8Bit().constData() );
            HPDF_Page_EndText (page);
      }  }
   iCurY = iAptInventoryRowsTop - (iRectHt * 7);  // allow room for max apt inventory table rows



   iCurY -= 18;
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   if (bHaveComunitySolar)
   {  // added Community Solar table - SAC 10/03/23
      HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, "Community Solar Allocation and Bill Credits" )/2), iCurY, "Community Solar Allocation and Bill Credits" );
      HPDF_Page_EndText (page);

      iRectHt = 23; 
      iCurY -= (iRectHt+6);
      iTblColWds[0] = 100;
      iTblColWds[1] =  60;
      iTblColWds[2] =  60;
      iTblColLeftX[0] = iPgLeft + ((iPgRight - iPgLeft)/2) - ((iTblColWds[0]+iTblColWds[1]+iTblColWds[2])/2);
      iTblColLeftX[1] = iTblColLeftX[0] + iTblColWds[0];
      iTblColLeftX[2] = iTblColLeftX[1] + iTblColWds[1];

      int iTextDY = 3;
      HPDF_Page_SetLineWidth (page, 0.25);
      HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
      for (iCol=0; iCol<=3; iCol++)
         HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[iCol], iRectHt );
      HPDF_Page_FillStroke (page);
      HPDF_Page_SetGrayFill (page, 0);
      HPDF_Page_SetFontAndSize (page, font, 9);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + iTextDY, "Apartment Type" );
      HPDF_Page_EndText (page);
      HPDF_Page_SetFontAndSize (page, font, 8);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "kWdc PV"       ) / 2),  iCurY + iTextDY + 11, "kWdc PV"     );
      HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "per Apt"       ) / 2),  iCurY + iTextDY     , "per Apt"     );
      HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Monthly"       ) / 2),  iCurY + iTextDY + 11, "Monthly"     );
      HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Credit"        ) / 2),  iCurY + iTextDY     , "Credit"      );
      HPDF_Page_EndText (page);

      HPDF_Page_SetFontAndSize (page, font, 9);
//      HPDF_Page_BeginText (page);
//      for (iCol=3; iCol<=3; iCol++)
//         HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-3] )/2),  iCurY + 4, pszMoLabel[iCol-3] );
//      HPDF_Page_EndText (page);

      double dCSPV, dCSCred;
      iRectHt = 12; 
      for (int iMtr=0; iMtr < lNumUnitTypes; iMtr++)
         if (iaPosUnitTypeIdxs[iMtr] >= 0)
         {  iCurY -= iRectHt;
            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            for (iCol=0; iCol<=3; iCol++)
               HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[iCol], iRectHt );
            HPDF_Page_Stroke (page);

            HPDF_Page_BeginText (page);
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
            HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );

            if (BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarSizeByBedrms"      )+iMtrIdx, dCSPV  , 0, -1, 0, BEMO_User, iBEMProcIdx ) && dCSPV   > 0.01 &&
                BEMPX_GetFloat(   BEMPX_GetDatabaseID( "CUAC:CommunitySolarAnnCreditByBedrms" )+iMtrIdx, dCSCred, 0, -1, 0, BEMO_User, iBEMProcIdx ) && dCSCred > 0.01)
            {
               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:CommunitySolarSizeByBedrms"      )+iMtrIdx, qsLabel, TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel += " kW";
               HPDF_Page_TextOut (page, iTblColLeftX[2]-(iTblColWds[1]/5)-HPDF_Page_TextWidth(page, qsLabel.toLocal8Bit().constData() ), iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
               //BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:CommunitySolarAnnCreditByBedrms" )+iMtrIdx, qsLabel, TRUE,  2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel += " kW";
               qsLabel = QString( "$ %1" ).arg( dCSCred/12, 0, 'f', 2 );
               HPDF_Page_TextOut (page, iTblColLeftX[2]+(4*iTblColWds[2]/5)-HPDF_Page_TextWidth(page, qsLabel.toLocal8Bit().constData() ), iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
            }
            HPDF_Page_EndText (page);
         }
   }
   else
   {  // inserted PV monthly output by apt type table - SAC 02/09/23
      //int iTblColWds[2], iTblColLeftX[13], iTableColMid, iCol, iSpecVal, iErr;
      HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, "PV Allocation and Monthly kWh Output" )/2), iCurY, "PV Allocation and Monthly kWh Output" );
      HPDF_Page_EndText (page);

      iRectHt = 23; 
      iCurY -= (iRectHt+6);
      iTblColWds[0] =  80;
      iTblColWds[1] =  60;
      iTblColWds[2] =  40;
      iTblColWds[3] = (iPgRight - iPgLeft - iTblColWds[0] - iTblColWds[1] - iTblColWds[2])/12;
      iTblColLeftX[0] = iPgLeft;
      iTblColLeftX[1] = iTblColLeftX[0] + iTblColWds[0];
      iTblColLeftX[2] = iTblColLeftX[1] + iTblColWds[1];
      iTblColLeftX[3] = iTblColLeftX[2] + iTblColWds[2];
      iTableColMid =  iTblColWds[3] / 2;
      int iTextDY = 3;
      HPDF_Page_SetLineWidth (page, 0.25);
      HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
      for (iCol=0; iCol<=14; iCol++)
      {  if (iCol > 3)
            iTblColLeftX[iCol] = iTblColLeftX[iCol-1] + iTblColWds[3];
         HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 3 ? 3 : iCol)], iRectHt );
      }
      HPDF_Page_FillStroke (page);
      HPDF_Page_SetGrayFill (page, 0);
      HPDF_Page_SetFontAndSize (page, font, 9);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + iTextDY, "Apartment Type" );
      HPDF_Page_EndText (page);
      HPDF_Page_SetFontAndSize (page, font, 8);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "% Tenant PV"   ) / 2),  iCurY + iTextDY + 11, "% Tenant PV"   );
      HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "Srvg each Apt" ) / 2),  iCurY + iTextDY     , "Srvg each Apt" );
      HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "kWdc PV"       ) / 2),  iCurY + iTextDY + 11, "kWdc PV"       );
      HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "per Apt"       ) / 2),  iCurY + iTextDY     , "per Apt"       );
      HPDF_Page_EndText (page);

      HPDF_Page_SetFontAndSize (page, font, 9);
      HPDF_Page_BeginText (page);
      for (iCol=3; iCol<=14; iCol++)
         HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-3] )/2),  iCurY + 4, pszMoLabel[iCol-3] );
      HPDF_Page_EndText (page);

      iRectHt = 12; 
      for (int iMtr=0; iMtr < lNumUnitTypes; iMtr++)
         if (iaPosUnitTypeIdxs[iMtr] >= 0)
         {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
            int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
            if (iResObjIdx >= 0)
            {  iCurY -= iRectHt;
               int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
               for (iCol=0; iCol<=14; iCol++)
                  HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 3 ? 3 : iCol)], iRectHt );
               HPDF_Page_Stroke (page);

               HPDF_Page_BeginText (page);
               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
               HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:PctIndivUnitPVByBedrms" )+iMtrIdx, qsLabel, TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel += " %";
               HPDF_Page_TextOut (page, iTblColLeftX[2]-(iTblColWds[1]/5)-HPDF_Page_TextWidth(page, qsLabel.toLocal8Bit().constData() ), iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
               BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:IndivUnitPVByBedrms"    )+iMtrIdx, qsLabel, TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
               HPDF_Page_TextOut (page, iTblColLeftX[3]-(iTblColWds[2]/5)-HPDF_Page_TextWidth(page, qsLabel.toLocal8Bit().constData() ), iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
               double dPVGen;
               for (iCol=0; iCol<12; iCol++)
               {  //BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:PVSysElecUse" )+iCol, qsLabel, TRUE, 1, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );
                  if (BEMPX_GetFloat( BEMPX_GetDatabaseID( "CUACResults:PVSysElecUse" )+iCol, dPVGen, 0.0, -1, iResObjIdx, BEMO_User, iBEMProcIdx )) 
                  {  qsLabel = BEMPX_FloatToString( dPVGen * (-1.0), 1 /*nRtOfDec*/, TRUE /*bAddCommas*/ );   // int iZeroFillLeftToLength=0, BOOL bTrimTrailingDecZeroes=FALSE );
                     HPDF_Page_TextOut (page, iTblColLeftX[iCol+3] + iTblColWds[3] - HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData()) - 4, iCurY+iTextDY, qsLabel.toLocal8Bit().constData() );
               }  }
               HPDF_Page_EndText (page);
         }  }
   }

   iCurY -= 5;
   GenerateTable_TypeMonths( page, font, fontBold, iCurY, "ACM Cooling Monthly kWh Usage", "CUACResults:ClgElecUse", lNumUnitTypes, &iaPosUnitTypeIdxs[0], lDBID_ResRef, iBEMProcIdx, iPgTop, iPgLeft, iPgRight, iPgCenter );



//   GenerateTable_Details_StartNewPage( pdf, page, image, font, fontBold, iCurX, iCurY, false, false, iPgTop, iPgLeft, iPgCenter, ++iPageNum, qsProjID, qsRunDateFmt, qsProjNameTitle );
   ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
   /////              PAGE 3             /////
   ///////////////////////////////////////////
   page = HPDF_AddPage (pdf);     // SAC 01/12/23
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
////   print_grid  (pdf, page);

//   GenerateTable_Details_PageHeader( pdf, page, /*image,*/ font, fontBold, pszRptGraphicsPath, iCurY, iPgTop, iPgLeft, iPgCenter, ++iPageNum, qsProjID, qsRunDateFmt, qsProjNameTitle );

   iCurY = iPgTop;
   iCurX = iPgLeft;

   /* print the title of the page (with positioning center). */
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   //tw = HPDF_Page_TextWidth (page, page_title);
   iCurY -= 25;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
   if (!qsProjID.isEmpty())
   {  HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
      HPDF_Page_EndText (page);
   }

//   image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23

   if (!qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 56;
      int iMidX = 690;   // 505;    - landscaoe vs. portrait
//      rect.left = 630;   // 450;    - landscaoe vs. portrait
//      rect.top = iCurY+12;

            // TESTING max date/time string
            //qsRunDateFmt = "12/30/2023 12:33:33 PM";
//      rect.right = iPgRight;
//      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 3");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, "Page 3");
      HPDF_Page_EndText (page);
   }

   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
   HPDF_Page_EndText (page);



   GenerateTable_TypeMonths( page, font, fontBold, iCurY, "ACM Heating Monthly kWh Usage", "CUACResults:HtgElecUse", lNumUnitTypes, &iaPosUnitTypeIdxs[0], lDBID_ResRef, iBEMProcIdx, iPgTop, iPgLeft, iPgRight, iPgCenter );

//   iCurY -= 22;         // SAC 01/12/23
//   qsLabel = "ACM Heating Monthly kWh Usage";
//   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
//   HPDF_Page_BeginText (page);
//   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() )/2), iCurY, qsLabel.toLocal8Bit().constData());
//   HPDF_Page_EndText (page);
//
//   iRectHt = 15; 
//   iCurY -= (iRectHt+8);
//   iTblColWds[0] = 100;
//   iTblColWds[1] = (iPgRight - iPgLeft - iTblColWds[0])/12;
//   iTblColLeftX[0] = iPgLeft;
//   iTblColLeftX[1] = iPgLeft + iTblColWds[0];
//   iTableColMid =  iTblColWds[1] / 2;
//   HPDF_Page_SetLineWidth (page, 0.25);
//   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
//   for (iCol=0; iCol<=12; iCol++)
//   {  if (iCol > 1)
//         iTblColLeftX[iCol] = iTblColLeftX[iCol-1] + iTblColWds[1];
//      HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 1 ? 1 : iCol)], iRectHt );
//   }
//   HPDF_Page_FillStroke (page);
//   HPDF_Page_SetGrayFill (page, 0);
//   HPDF_Page_SetFontAndSize (page, font, 9);
//   HPDF_Page_BeginText (page);
//   HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + 4, "Apartment Type" );
//   for (iCol=1; iCol<=12; iCol++)
//      HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-1] )/2),  iCurY + 4, pszMoLabel[iCol-1] );
//   HPDF_Page_EndText (page);
//
//   HPDF_Page_SetFontAndSize (page, font, 10);      // SAC 01/12/23
//   for (iMtr=0; iMtr < lNumUnitTypes; iMtr++)
//      if (iaPosUnitTypeIdxs[iMtr] >= 0)
//      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
//         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
//         if (iResObjIdx >= 0)
//         {  iCurY -= iRectHt;
//            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
//            for (iCol=0; iCol<=12; iCol++)
//               HPDF_Page_Rectangle (page, iTblColLeftX[iCol], iCurY, iTblColWds[(iCol > 1 ? 1 : iCol)], iRectHt );
//            HPDF_Page_Stroke (page);
//
//            HPDF_Page_BeginText (page);
//            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
//            HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+4, qsLabel.toLocal8Bit().constData() );
//            for (iCol=0; iCol<12; iCol++)
//            {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:HtgElecUse" )+iCol, qsLabel, TRUE, 1, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );
//               HPDF_Page_TextOut (page, iTblColLeftX[iCol+1] + iTableColMid - (HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData())/2), iCurY+4, qsLabel.toLocal8Bit().constData() );
//            }
//            HPDF_Page_EndText (page);
//      }  }


   GenerateTable_TypeMonths( page, font, fontBold, iCurY, "ACM Heating Monthly kBtu Usage",        "CUACResults:HtgGasUse",  lNumUnitTypes, &iaPosUnitTypeIdxs[0], lDBID_ResRef, iBEMProcIdx, iPgTop, iPgLeft, iPgRight, iPgCenter );

   GenerateTable_TypeMonths( page, font, fontBold, iCurY, "ACM Water Heating Monthly kWh Usage",   "CUACResults:DHWElecUse", lNumUnitTypes, &iaPosUnitTypeIdxs[0], lDBID_ResRef, iBEMProcIdx, iPgTop, iPgLeft, iPgRight, iPgCenter );

   GenerateTable_TypeMonths( page, font, fontBold, iCurY, "ACM Water Heating Monthly kBtu Usage",  "CUACResults:DHWGasUse",  lNumUnitTypes, &iaPosUnitTypeIdxs[0], lDBID_ResRef, iBEMProcIdx, iPgTop, iPgLeft, iPgRight, iPgCenter );




//   GenerateTable_Details_StartNewPage( pdf, page, image, font, fontBold, iCurX, iCurY, false, false, iPgTop, iPgLeft, iPgCenter, ++iPageNum, qsProjID, qsRunDateFmt, qsProjNameTitle );
   ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
   /////              PAGE 4             /////
   ///////////////////////////////////////////
   int iPgNum = 3;  // will increment before writing...
   QString qsPgNumLabel;
   page = HPDF_AddPage (pdf);     // SAC 01/12/23
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);

//   print_grid  (pdf, page);

   iCurY = iPgTop;
   iCurX = iPgLeft;
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   iCurY -= 25;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
   if (!qsProjID.isEmpty())
   {  HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
      HPDF_Page_EndText (page);
   }
   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23

   qsPgNumLabel = QString("Page %1").arg(QString::number(++iPgNum));
   if (!qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 56;
      int iMidX = 690;   // 505;    - landscaoe vs. portrait
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, qsPgNumLabel.toLocal8Bit().constData());
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPgNumLabel.toLocal8Bit().constData());
      HPDF_Page_EndText (page);
   }

   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
   HPDF_Page_EndText (page);


   int iDetTblColWds[16], iDetTblColLeftX[16];
   GenerateTable_UnitDetails_Header( page, font, fontBold, iCurY, "Electric kWh Usage by End Use Summary", &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter );

   int iNumUnitTypesThisPg = (lNumUnitTypes <= 3 ? lNumUnitTypes : 3);
   for (iMtr=0; iMtr < iNumUnitTypesThisPg; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            GenerateTable_UnitDetails_FuelTable( page, font, fontBold, iCurY, &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter, iResObjIdx, iMtrIdx,
                                                 iCUAC_BEMProcIdx, Num_Elec_Enduses, pszElecEnduseName, pszElecEnduseProps, iaEnduseDetailsArrIdx, 1.0 );
      }  }

   if (iNumUnitTypesThisPg < lNumUnitTypes)
   {  // need additional page to complete Electric kWh Usage by End Use Summary tables - SAC 01/23/23
      /////              PAGE 5             /////
      page = HPDF_AddPage (pdf);     // SAC 01/12/23
      HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
      //   print_grid  (pdf, page);

      iCurY = iPgTop;
      iCurX = iPgLeft;
      HPDF_Page_SetFontAndSize (page, fontBold, 6);
      iCurY -= 25;
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
      HPDF_Page_EndText (page);

      iCurY -= 12;
      HPDF_Page_SetFontAndSize (page, fontBold, 10);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
      HPDF_Page_EndText (page);

      iCurY -= 3;
      HPDF_Page_SetGrayFill (page, 0);  // 0.5);
      HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
      HPDF_Page_SetLineWidth (page, 1.25);
      HPDF_Page_MoveTo  (page, iCurX, iCurY );
      HPDF_Page_LineTo  (page,   230, iCurY );
      HPDF_Page_Stroke (page);

      iCurY -= 11;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
      HPDF_Page_EndText (page);

      iCurY -= 13;
      if (!qsProjID.isEmpty())
      {  HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
         HPDF_Page_EndText (page);
      }
      HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23

      qsPgNumLabel = QString("Page %1").arg(QString::number(++iPgNum));
      if (!qsRunDateFmt.isEmpty())
      {  iCurY = iPgTop - 56;
         int iMidX = 690;   // 505;    - landscaoe vs. portrait
         HPDF_Page_SetFontAndSize (page, fontBold, 8);
         tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
         tw2 = HPDF_Page_TextWidth (page, qsPgNumLabel.toLocal8Bit().constData());
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
         HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPgNumLabel.toLocal8Bit().constData());
         HPDF_Page_EndText (page);
      }

      HPDF_Page_SetFontAndSize (page, fontBold, 10); 
      iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

      GenerateTable_UnitDetails_Header( page, font, fontBold, iCurY, "Electric kWh Usage by End Use Summary (cont'd)", &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter );

      for (iMtr=iNumUnitTypesThisPg; iMtr < lNumUnitTypes; iMtr++)
         if (iaPosUnitTypeIdxs[iMtr] >= 0)
         {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
            int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
            if (iResObjIdx >= 0)
            {  int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
               GenerateTable_UnitDetails_FuelTable( page, font, fontBold, iCurY, &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter, iResObjIdx, iMtrIdx,
                                                    iCUAC_BEMProcIdx, Num_Elec_Enduses, pszElecEnduseName, pszElecEnduseProps, iaEnduseDetailsArrIdx, 1.0 );
         }  }
   }


   ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
   /////              PAGE 5/6           /////
   ///////////////////////////////////////////
   page = HPDF_AddPage (pdf);     // SAC 02/08/23
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);

//   print_grid  (pdf, page);

   iCurY = iPgTop;
   iCurX = iPgLeft;
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   iCurY -= 25;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
   if (!qsProjID.isEmpty())
   {  HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
      HPDF_Page_EndText (page);
   }
   HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23

   qsPgNumLabel = QString("Page %1").arg(QString::number(++iPgNum));
   if (!qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 56;
      int iMidX = 690;   // 505;    - landscaoe vs. portrait
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, qsPgNumLabel.toLocal8Bit().constData());
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPgNumLabel.toLocal8Bit().constData());
      HPDF_Page_EndText (page);
   }

   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
   HPDF_Page_EndText (page);


   //int iDetTblColWds[16], iDetTblColLeftX[16];
   GenerateTable_UnitDetails_Header( page, font, fontBold, iCurY, "kBtu Gas Usage by End Use Summary", &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter );

   iNumUnitTypesThisPg = lNumUnitTypes;  // (lNumUnitTypes <= 3 ? lNumUnitTypes : 3);
   for (iMtr=0; iMtr < iNumUnitTypesThisPg; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            GenerateTable_UnitDetails_FuelTable( page, font, fontBold, iCurY, &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter, iResObjIdx, iMtrIdx,
                                                 iCUAC_BEMProcIdx, Num_Gas_Enduses, pszGasEnduseName, pszGasEnduseProps, iaEnduseDetailsArrIdx, 100.0 );
      }  }




   HPDF_SaveToFile (pdf, pszPDFPathFile);
   HPDF_Free (pdf);

   return 0;
}





////////////////////////////////////////////////////////////////////////////////





int GeneratePDF_CUACSubmittal( const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx )
{
   HPDF_Doc  pdf;
   HPDF_Page page;
   HPDF_Font font, fontBold;
   HPDF_Rect rect;

   iPDFID;
   iBEMProcIdx;

   QString qsFuelType, qsTemp;
   BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:GasType" ), qsTemp, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );     // ported (revised) from Details report - SAC 09/21/23
   if (qsTemp.compare("NaturalGas")==0)
      qsFuelType = "Natural Gas";
   else if (qsTemp.compare("None")==0 || qsTemp.isEmpty())
      qsFuelType = "Unknown Gas";
   else 
      qsFuelType = qsTemp;

   //  1 "Draft" / 2 "Final" / 3 "Annual"
   QString sRptName = ((iPDFID == 1 || iPDFID == 4) ? "Draft" : ((iPDFID == 2 || iPDFID == 5) ? "Final" : "Annual" ));
   sRptName += " Submittal";

   pdf = HPDF_New (error_handler, NULL);
   if (!pdf) {
       printf ("error: cannot create PdfDoc object\n");
       return 1;
   }
   if (setjmp(env)) {
       HPDF_Free (pdf);
       return 1;
   }
   /* add a new page object. */
   page = HPDF_AddPage (pdf);
   //HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_PORTRAIT);

//   print_grid  (pdf, page);

   font     = HPDF_GetFont (pdf, "Helvetica", NULL);
   fontBold = HPDF_GetFont (pdf, "Helvetica-Bold", NULL);

   int iPgTop = HPDF_Page_GetHeight (page);
   int iPgLeft = 50, iPgRight = 560;
   int iPgCenter = (iPgLeft+iPgRight)/2;
   int iCurY = iPgTop, iCurX = iPgLeft;

   /* print the title of the page (with positioning center). */
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   //tw = HPDF_Page_TextWidth (page, page_title);
   iCurY -= 45;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
//   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, QString( "%1 Report" ).arg(sRptName).toLocal8Bit().constData() );   // "Draft Submittal Report");
   HPDF_Page_EndText (page);



   HPDF_Image image;
   QString qsLogoPathFN = pszRptGraphicsPath;   qsLogoPathFN += "CEC.jpg";
   //image = HPDF_LoadJpegImageFromFile (pdf, "D:\\Dev\\svn-CEC\\SF_CBECC-Com\\branches\\CBECC_CUAC\\CBECC-Com64\\Data\\Rulesets\\T24N_2022\\RTF\\CEC.jpg");
   image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
   HPDF_Page_DrawImage (page, image, 240, iPgTop-91, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));


   HPDF_REAL tw1, tw2;

   QString qsRunDateFmt;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), qsRunDateFmt, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 71;
      rect.left = 450;
      rect.top = iCurY+12;
      rect.right = iPgRight;
      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 1 of 3");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, 505-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, 505-(tw2/2), iCurY-12, "Page 1 of 2");
      HPDF_Page_EndText (page);
//      HPDF_Page_BeginText (page);
//      HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
//                  qsRunDateFmt.toLocal8Bit().constData(), HPDF_TALIGN_CENTER, NULL);
//      rect.top -= 10;
//      rect.bottom -= 10;
//      HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
//                  "Page 1 of 3", HPDF_TALIGN_CENTER, NULL);
//      HPDF_Page_EndText (page);
   }



   HPDF_Page_SetFontAndSize (page, font, 14);      // SAC 10/30/22
   tw1 = HPDF_Page_TextWidth (page, "Allowances for Tenant-Furnished" );
   tw2 = HPDF_Page_TextWidth (page, "Utilities and Other Services" );
   iCurX = 152;
   iCurY = 672;

   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-(tw1/2), iCurY,    "Allowances for Tenant-Furnished" );
   HPDF_Page_TextOut (page, iCurX-(tw2/2), iCurY-17, "Utilities and Other Services" );
   HPDF_Page_EndText (page);


   iCurY = 672-17-30;
   HPDF_Page_SetFontAndSize (page, fontBold, 16);
   tw1 = HPDF_Page_TextWidth (page, sRptName.toLocal8Bit().constData() );   // "Draft Submittal" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-(tw1/2), iCurY, sRptName.toLocal8Bit().constData() );   // "Draft Submittal" );
   HPDF_Page_EndText (page);



   iCurX = 520;
   iCurY = 672;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);     // SAC 10/30/22
   tw1 = HPDF_Page_TextWidth (page, "Generated by TCAC Approved" );
// removed pending TCAC approval - SAC 11/14/22
//   HPDF_Page_BeginText (page);
//   HPDF_Page_TextOut (page, iCurX-tw1, iCurY, "Generated by TCAC Approved" );
//   HPDF_Page_EndText (page);


   iCurX = iPgRight;
   iCurY -= 10;   // was: 13;
   tw1 = HPDF_Page_TextWidth (page, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-tw1, iCurY, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_EndText (page);


   iCurX = 520;
   iCurY -= 15;   // was: 18;
   QString qsSoftwareVersion, qsCompManagerVersion, qsTariffDate;
   HPDF_Page_SetFontAndSize (page, font, 8);      // SAC 10/30/22
   QString qsLabel, qsLabel2, qsLabel3;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
      qsSoftwareVersion = qsLabel;
   }

   iCurY -= 12;   // was: 13;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
      qsCompManagerVersion = qsLabel;
   }

   iCurY -= 12;   // added - SAC 01/24/24
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TariffDate" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  qsTariffDate = qsLabel;
      qsLabel = "Tariff Date: " + qsTariffDate;
      tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
   }

   iCurX = iPgLeft;             // address, signature blocks, proj ID, date, ... - SAC 11/11/22
   iCurY -= 20;   // was: 25;
   int iLblXMarg = 3, iLblYMarg = 1, iLblHt = 8;
   int iRectHt = 28;
   int iCol1Wd = 195;
   int iCol2Wd = 195;
   int iCol3Wd = iPgRight - iPgLeft - iCol1Wd - iCol2Wd;
   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_SetFontAndSize (page, font, iLblHt);

   HPDF_Page_Rectangle (page, iCurX, iCurY-(iRectHt*2), iCol1Wd, (iRectHt*2) );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iLblXMarg, iCurY-iLblYMarg-iLblHt, "Property Address:" );
      HPDF_Page_EndText (page);

      QString qsAddCityStZip;
      //BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:SiteAddress" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:StAddress" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      if (!qsLabel.isEmpty())
      {  HPDF_Page_SetFontAndSize (page, font, 10);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-18, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
         qsAddCityStZip = qsLabel;
      }

      //BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:SiteCity"    ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      //BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:SiteZIPCode" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:City"    ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:State"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ZipCode" ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      if (!qsLabel.isEmpty() || !qsLabel2.isEmpty() || !qsLabel3.isEmpty())
      {  if (!qsLabel.isEmpty() && !qsLabel2.isEmpty())
            qsLabel += QString( ", %1" ).arg(qsLabel2);
         if (!qsLabel.isEmpty() && !qsLabel3.isEmpty())
            qsLabel += QString( ", %1" ).arg(qsLabel3);
         HPDF_Page_SetFontAndSize (page, font, 10);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-32, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
         if (!qsAddCityStZip.isEmpty())
            qsAddCityStZip += ",  ";
         qsAddCityStZip += qsLabel;
      }


   HPDF_Page_SetFontAndSize (page, font, iLblHt);
   HPDF_Page_Rectangle (page, iCurX+iCol1Wd, iCurY-iRectHt, iCol1Wd, iRectHt );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iLblXMarg, iCurY-iLblYMarg-iLblHt, "Developer Signature:" );
      HPDF_Page_EndText (page);

   HPDF_Page_Rectangle (page, iCurX+iCol1Wd, iCurY-(iRectHt*2), iCol1Wd, iRectHt );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iLblXMarg, iCurY-iRectHt-iLblYMarg-iLblHt, "Qualified Consultant Signature:" );
      HPDF_Page_EndText (page);


   HPDF_Page_Rectangle (page, iCurX+iCol1Wd+iCol2Wd, iCurY-(iRectHt*2), iCol3Wd, (iRectHt*2) );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg, iCurY-iLblYMarg-iLblHt, "CUAC Project ID" );
      tw1 = HPDF_Page_TextWidth (page, "CUAC Project ID" );
      HPDF_Page_SetFontAndSize (page, font, iLblHt-2);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg+tw1, iCurY-iLblYMarg-iLblHt+2, "*" );
      tw2 = HPDF_Page_TextWidth (page, "*" );
      HPDF_Page_SetFontAndSize (page, font, iLblHt);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg+tw1+tw2, iCurY-iLblYMarg-iLblHt, ":" );
      HPDF_Page_EndText (page);

      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ProjectID" ), qsLabel,  FALSE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      if (!qsLabel.isEmpty())
      {  HPDF_Page_SetFontAndSize (page, font, 16);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-24, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
      }


   iCurY -= ((iRectHt*2));
   HPDF_Page_SetFontAndSize (page, font, iLblHt);
   HPDF_Page_Rectangle (page, iCurX, iCurY-iRectHt, iCol1Wd, iRectHt );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iLblXMarg, iCurY-iLblYMarg-iLblHt, "Locality:" );
      HPDF_Page_EndText (page);

      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:Locality" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      if (!qsLabel.isEmpty())
      {  HPDF_Page_SetFontAndSize (page, font, 10);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-14, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
      }

   HPDF_Page_SetFontAndSize (page, font, iLblHt);
   HPDF_Page_Rectangle (page, iCurX+iCol1Wd, iCurY-iRectHt, iCol1Wd, iRectHt );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iLblXMarg, iCurY-iLblYMarg-iLblHt, "Unit Type:" );
      HPDF_Page_EndText (page);

      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType" ), qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
      if (!qsLabel.isEmpty())
      {  HPDF_Page_SetFontAndSize (page, font, 10);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iCol1Wd+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-14, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
      }

   HPDF_Page_SetFontAndSize (page, font, iLblHt);
   HPDF_Page_Rectangle (page, iCurX+iCol1Wd+iCol2Wd, iCurY-iRectHt, iCol3Wd, iRectHt );
   HPDF_Page_Stroke (page);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg, iCurY-iLblYMarg-iLblHt, "Date:" );
      HPDF_Page_EndText (page);

      qsLabel = qsRunDateFmt.left( qsRunDateFmt.indexOf(" ") );
      if (!qsLabel.isEmpty())
      {  HPDF_Page_SetFontAndSize (page, font, 10);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, iCurX+iCol1Wd+iCol2Wd+iLblXMarg+8, iCurY-iLblYMarg-iLblHt-14, qsLabel.toLocal8Bit().constData() );
         HPDF_Page_EndText (page);
      }



   iCurY -= (iRectHt + 6);
   iLblXMarg = 8;
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
//   HPDF_Page_SetGrayStroke (page, 0.8);
   HPDF_Page_Rectangle (page, iCurX, iCurY-iRectHt, iPgRight - iCurX, iRectHt );
//   HPDF_Page_Stroke (page);
//   HPDF_Page_Fill (page);
   HPDF_Page_FillStroke (page);

   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
//   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetFontAndSize (page, fontBold, 9); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, 280, iCurY - 11, "Monthly Allowance" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY-iRectHt +5, "Utility or Service" );
   HPDF_Page_EndText (page);

   iCurY -= (iRectHt -5);
   int iCol1X = 187;
   int iColDX =  53;
   int iUnitColX[] = {  iCol1X             ,  iCol1X +  iColDX   ,  iCol1X + (iColDX*2),  iCol1X + (iColDX*3),
                        iCol1X + (iColDX*4),  iCol1X + (iColDX*5),  iCol1X + (iColDX*6)  };
   HPDF_Page_SetFontAndSize (page, font, 9); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iUnitColX[0], iCurY-2, "0 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[1], iCurY-2, "1 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[2], iCurY-2, "2 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[3], iCurY-2, "3 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[4], iCurY-2, "4 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[5], iCurY-2, "5 Bdrm" );
   HPDF_Page_TextOut (page, iUnitColX[6], iCurY-2, "6 Bdrm" );
   HPDF_Page_EndText (page);


   int iRowYMarg = 4, iTxtLnDY = 12;
   iCurY -= 5;
   HPDF_Page_Rectangle (page, iCurX, iCurY - ((iTxtLnDY*25) + (iRowYMarg*11)), iPgRight - iCurX, (iTxtLnDY*25) + (iRowYMarg*11) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY* 3) +  iRowYMarg    ) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY* 3) +  iRowYMarg    ) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY* 6) + (iRowYMarg* 2)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY* 6) + (iRowYMarg* 2)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY* 8) + (iRowYMarg* 3)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY* 8) + (iRowYMarg* 3)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*11) + (iRowYMarg* 4)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*11) + (iRowYMarg* 4)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*13) + (iRowYMarg* 5)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*13) + (iRowYMarg* 5)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*16) + (iRowYMarg* 6)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*16) + (iRowYMarg* 6)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*18) + (iRowYMarg* 7)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*18) + (iRowYMarg* 7)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*20) + (iRowYMarg* 8)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*20) + (iRowYMarg* 8)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*22) + (iRowYMarg* 9)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*22) + (iRowYMarg* 9)) );
   HPDF_Page_MoveTo  (page, iCurX + 10, iCurY - ((iTxtLnDY*25) + (iRowYMarg*10)) );       HPDF_Page_LineTo  (page, iPgRight - 10, iCurY - ((iTxtLnDY*25) + (iRowYMarg*10)) );
   HPDF_Page_Stroke (page);

   HPDF_Page_SetFontAndSize (page, fontBold, 9); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY -  iTxtLnDY                    , "Heating"  );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY* 4) -  iRowYMarg   , "Cooking"  );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY* 7) - (iRowYMarg*2), "Lighting" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY* 9) - (iRowYMarg*3), "Other"    );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*12) - (iRowYMarg*4), "Air Conditioning" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*14) - (iRowYMarg*5), "Water Heating" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*17) - (iRowYMarg*6), "Water" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*19) - (iRowYMarg*7), "Sewer" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*21) - (iRowYMarg*8), "Trash" );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iCurY - (iTxtLnDY*23) - (iRowYMarg*9), "Rental" );
   HPDF_Page_EndText (page);

   iLblXMarg += 25;
   int iaAllowY[] = {   iCurY - (iTxtLnDY* 2)                ,
                        iCurY - (iTxtLnDY* 3)                ,
                        iCurY - (iTxtLnDY* 5) -  iRowYMarg   ,
                        iCurY - (iTxtLnDY* 6) -  iRowYMarg   ,
                        iCurY - (iTxtLnDY* 8) - (iRowYMarg*2),
                        iCurY - (iTxtLnDY*10) - (iRowYMarg*3),
                        iCurY - (iTxtLnDY*11) - (iRowYMarg*3),
                        iCurY - (iTxtLnDY*13) - (iRowYMarg*4),
                        iCurY - (iTxtLnDY*15) - (iRowYMarg*5),
                        iCurY - (iTxtLnDY*16) - (iRowYMarg*5),
                        iCurY - (iTxtLnDY*18) - (iRowYMarg*6),
                        iCurY - (iTxtLnDY*20) - (iRowYMarg*7),
                        iCurY - (iTxtLnDY*22) - (iRowYMarg*8),
                        iCurY - (iTxtLnDY*24) - (iRowYMarg*9),
                        iCurY - (iTxtLnDY*25) - (iRowYMarg*9)  };
   HPDF_Page_SetFontAndSize (page, font, 9); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 0], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 1], qsFuelType.toLocal8Bit().constData() );     // "Natural Gas" -> specified fuel type - SAC 09/21/23
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 2], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 3], qsFuelType.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 4], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 5], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 6], qsFuelType.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 7], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 8], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 9], qsFuelType.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[10], "Water"        );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[11], "Sewer"        );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[12], "Trash"        );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[13], "Microwave"    );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[14], "Refrigerator" );
   HPDF_Page_EndText (page);


   // export of Allowance results - SAC 11/11/22
#define  NumDwellingMeters   7
   int iCUAC_BEMProcIdx = -1;  // ???
   int iMtr, iSpecVal, iErr;
   long laNumUnitsByBedrms[NumDwellingMeters], laNumMktRateUnitsByBedrms[NumDwellingMeters], lTemp, lNumUnitTypes=0;
   int iaPosUnitTypeIdxs[NumDwellingMeters] = {-1,-1,-1,-1,-1,-1,-1};
   for (iMtr=0; iMtr < NumDwellingMeters; iMtr++)
   {  if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "CUAC:AffordableUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp > 0)
      {  laNumUnitsByBedrms[iMtr] = lTemp;
         iaPosUnitTypeIdxs[lNumUnitTypes] = iMtr;
         lNumUnitTypes++;
         if (BEMPX_GetInteger( BEMPX_GetDatabaseID( "ResProj:NumDwellingUnitsByBedrms" )+iMtr, lTemp, 0, -1, 0, BEMO_User, iCUAC_BEMProcIdx ) && lTemp >= laNumUnitsByBedrms[iMtr])
            laNumMktRateUnitsByBedrms[iMtr] = lTemp - laNumUnitsByBedrms[iMtr];
         else
         {  assert( false );
            laNumMktRateUnitsByBedrms[iMtr] = 0;
         }
      }
      else
      {  laNumUnitsByBedrms[iMtr] = 0;
         laNumMktRateUnitsByBedrms[iMtr] = 0;
   }  }
   long lDBID_Allow  = BEMPX_GetDatabaseID( "CUACResults:Allowances" );    assert( lDBID_Allow > 0  );
   long lDBID_ResRef = BEMPX_GetDatabaseID( "CUAC:CUACResultsRef" );       assert( lDBID_ResRef > 0 );
   double dAllow;
   for (iMtr=0; (lDBID_Allow > 0 && lDBID_ResRef > 0 && iMtr < NumDwellingMeters); iMtr++)
      if (laNumUnitsByBedrms[iMtr] > 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iMtr, iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
            for (int iAllow=0; iAllow < 15; iAllow++)
            {  BEMPX_GetFloat( lDBID_Allow+iAllow, dAllow, 0, -1, iResObjIdx, BEMO_User, iCUAC_BEMProcIdx );
               if (dAllow > 0)
               {  QString qsAllow = QString( "$ %1" ).arg( dAllow, 0, 'f', 2 );
                  tw1 = HPDF_Page_TextWidth (page, qsAllow.toLocal8Bit().constData() );
                  HPDF_Page_BeginText (page);
                  HPDF_Page_TextOut (page, iUnitColX[iMtr] + 27 - tw1, iaAllowY[iAllow], qsAllow.toLocal8Bit().constData() );
                  HPDF_Page_EndText (page);
               }
      }     }


   iCurY -= ((iTxtLnDY*25) + (iRowYMarg*11));

   //HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX  , iCurY-20, "* Note:" );     // SAC 12/05/22
   HPDF_Page_TextOut (page, iCurX+8, iCurY-31, "For compliance for years after construction, the software version number and this number must match the CUAC Project" );
   HPDF_Page_TextOut (page, iCurX+8, iCurY-42, "Number of the original (construction year) submittal, or be accompanied by an explanation to changes on the building's" );
   HPDF_Page_TextOut (page, iCurX+8, iCurY-53, "features or solar (PV) system." );
   HPDF_Page_EndText (page);



   ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
   /////              PAGE 2             /////
   ///////////////////////////////////////////
   page = HPDF_AddPage (pdf);     // SAC 12/05/22
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_PORTRAIT);

   iCurY = iPgTop;  iCurX = iPgLeft;
   HPDF_Page_SetFontAndSize (page, fontBold, 6);
   iCurY -= 45;
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
   HPDF_Page_EndText (page);

   iCurY -= 12;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
   HPDF_Page_EndText (page);

   iCurY -= 3;
   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
   HPDF_Page_SetLineWidth (page, 1.25);
   HPDF_Page_MoveTo  (page, iCurX, iCurY );
   HPDF_Page_LineTo  (page,   230, iCurY );
   HPDF_Page_Stroke (page);

   iCurY -= 11;
   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
   HPDF_Page_EndText (page);

   iCurY -= 13;
//   HPDF_Page_SetFontAndSize (page, fontBold, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX, iCurY, QString( "%1 Report" ).arg(sRptName).toLocal8Bit().constData() );   // "Draft Submittal Report");
   HPDF_Page_EndText (page);

   //QString qsLogoPathFN = pszRptGraphicsPath;   qsLogoPathFN += "CEC.jpg";
   //image = HPDF_LoadJpegImageFromFile (pdf, qsLogoPathFN.toLocal8Bit().constData());
   HPDF_Page_DrawImage (page, image, 240, iPgTop-91, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));

   //QString qsRunDateFmt;
   //if (BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:RunDateFmt" ), qsRunDateFmt, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsRunDateFmt.isEmpty())
   if (!qsRunDateFmt.isEmpty())
   {  iCurY = iPgTop - 71;
      rect.left = 450;
      rect.top = iCurY+12;
      rect.right = iPgRight;
      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 2 of 3");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, 505-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, 505-(tw2/2), iCurY-12, "Page 2 of 2");
      HPDF_Page_EndText (page);
   }


   HPDF_Page_SetLineWidth (page, 0.25);
   iCurY -= 45;    iTxtLnDY = 18;    // 20;     // SAC 12/05/22  // reduced line ht by 2 - SAC 12/10/22
   int iRow;
   for (iRow=0; iRow < 12; iRow++)     // increased 10->11 to add Elec. Tariff Adjustment: - SAC 01/10/24  // 11->12 for GasTariffType - SAC 01/25/24
   {  // indent Tariff Type fields - SAC 01/25/24
      int iIndentCol1X = 0;
      switch (iRow)
      {  case  0 :  qsLabel = "Software Version:";       qsLabel2 = qsSoftwareVersion;   break;
         case  1 :  qsLabel = "Calculation Engine:";     qsLabel2 = qsCompManagerVersion;   break;
         case  2 :  qsLabel = "Printed Timestamp:";      qsLabel2 = qsRunDateFmt;   break;
         case  3 :  qsLabel = "Project Name:";           BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Name"            ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  4 :  qsLabel = "Site Street Address:";    qsLabel2 = qsAddCityStZip;  break;
         case  5 :  qsLabel = "Site Contact:";           BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"     ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  6 :  qsLabel = "Electric Utility:";       BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"     ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  7 :  qsLabel = "Elec. Territory:";        BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTerritory" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  8 :  qsLabel = "Elec. Tariff Type:";      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffType"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   iIndentCol1X = 15;  break;    // SAC 01/25/24
         case  9 :  qsLabel = "Gas Utility:";            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case 10 :  qsLabel = "Gas Territory:";          BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTerritory"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case 11 :  qsLabel = "Gas Tariff Type:";        BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariffType"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   iIndentCol1X = 15;  break;    // SAC 01/25/24
   //      case  8 :  qsLabel = "Tariff Type:";            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"    ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
      } 

      HPDF_Page_SetFontAndSize (page, fontBold, 9);
      HPDF_Page_BeginText (page);
      tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, 155+iIndentCol1X-tw1, iCurY - (iTxtLnDY * iRow), qsLabel.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

      HPDF_Page_SetFontAndSize (page, font, 9);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, 165+iIndentCol1X, iCurY - (iTxtLnDY * iRow), qsLabel2.toLocal8Bit().constData());
      HPDF_Page_EndText (page);
      
      if (iRow == 1 || iRow == 5 || iRow == 7 || iRow == 8 || iRow == 10)
      {  int iRtLineLeft, iLineMargin;     // provide less room for territory, more room for tariff - SAC 09/06/23  // SAC 09/06/23
         switch (iRow)
         {  case  1 :  qsLabel = "Tariff Date:";            iRtLineLeft = 471;  iLineMargin =  85;  qsLabel2 = qsTariffDate;   break;
            case  5 :  qsLabel = "Project Type:";           iRtLineLeft = 471;  iLineMargin =  85;  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
            case  7 :  qsLabel = "Elec. Tariff:";           iRtLineLeft = 356;  iLineMargin =  70;  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2ElecTariff"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
            case  8 :  qsLabel = "Elec. Tariff Adjuster:";  iRtLineLeft = 471;  iLineMargin = 185;  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariffAdj" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;   // SAC 01/10/24
            case 10 :  qsLabel = "Gas Tariff:";             iRtLineLeft = 356;  iLineMargin =  70;  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:G2GasTariff"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         }
         HPDF_Page_SetFontAndSize (page, fontBold, 9);
         HPDF_Page_BeginText (page);
         tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());
         HPDF_Page_TextOut (page, (iRtLineLeft-6)-tw1, iCurY - (iTxtLnDY * iRow), qsLabel.toLocal8Bit().constData());
         HPDF_Page_EndText (page);

         HPDF_Page_SetFontAndSize (page, font, 9);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, (iRtLineLeft+4), iCurY - (iTxtLnDY * iRow), qsLabel2.toLocal8Bit().constData());
         HPDF_Page_EndText (page);

         HPDF_Page_MoveTo  (page, 161+iIndentCol1X, iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, (iRtLineLeft-iLineMargin), iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_MoveTo  (page, iRtLineLeft,      iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, iPgRight,                  iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_Stroke (page);
      }
      else
      {  int iLineRt = (iRow==11 ? 356-70 : iPgRight);
         HPDF_Page_MoveTo  (page, 161+iIndentCol1X, iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, iLineRt, iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_Stroke (page);
      }
   }


   iCurY -= ((iTxtLnDY * 12) + 10);
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   tw1 = HPDF_Page_TextWidth (page, "Utility Allowance Calculator Results");
   HPDF_Page_TextOut (page, iPgCenter-(tw1/2), iCurY, "Utility Allowance Calculator Results");
   HPDF_Page_EndText (page);


   iCurY -= (iTxtLnDY + 9);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_Rectangle (page, iPgLeft, iCurY, (iPgRight-iPgLeft), 17 );
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   tw1 = HPDF_Page_TextWidth (page, "Monthly Usage ($/month)");
   HPDF_Page_TextOut (page, iPgCenter-(tw1/2), iCurY+5, "Monthly Usage ($/month)" );
   HPDF_Page_EndText (page);


   iRectHt = 45;     // SAC 12/05/22
   iCurY -= iRectHt;
   int iTableColWd  = (iPgRight-iPgLeft - 190) / 5;
   int iTableColMid =  iTableColWd / 2;
   int iTableLeft   =  iPgRight - (iTableColWd * 5);
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   HPDF_Page_Rectangle (page, iPgLeft, iCurY, (iPgRight-iPgLeft), iRectHt );
   HPDF_Page_FillStroke (page);

   HPDF_Page_Rectangle (page, iTableLeft - 40     , iCurY, 40, 28 );   // Market Rate
   HPDF_Page_Rectangle (page, iTableLeft - 40 - 56, iCurY, 56, 28 );   // Affordable housing

   HPDF_Page_Rectangle (page, iTableLeft                , iCurY, iTableColWd, iRectHt );
   HPDF_Page_Rectangle (page, iTableLeft+ iTableColWd   , iCurY, iTableColWd, iRectHt );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*2), iCurY, iTableColWd, iRectHt );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*3), iCurY, iTableColWd, iRectHt );
   HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*4), iCurY, iTableColWd, iRectHt );
   HPDF_Page_Stroke (page);

   HPDF_Page_SetGrayFill (page, 0);  // 0.5);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgLeft+3  , iCurY+10, "Apartment Type" );
   HPDF_Page_TextOut (page, iPgLeft+132, iCurY+33, "Units" );
   tw1 = HPDF_Page_TextWidth (page, "Electric");   HPDF_Page_TextOut (page, iTableLeft                +iTableColMid-(tw1/2), iCurY+10, "Electric" );
   tw1 = HPDF_Page_TextWidth (page, "Gas"     );   HPDF_Page_TextOut (page, iTableLeft+ iTableColWd   +iTableColMid-(tw1/2), iCurY+10, "Gas"      );
   tw1 = HPDF_Page_TextWidth (page, "Water"   );   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*2)+iTableColMid-(tw1/2), iCurY+10, "Water"    );
   tw1 = HPDF_Page_TextWidth (page, "Trash"   );   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*3)+iTableColMid-(tw1/2), iCurY+10, "Trash"    );
   tw1 = HPDF_Page_TextWidth (page, "Total"   );   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*4)+iTableColMid-(tw1/2), iCurY+10, "Total"    );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 9);
   HPDF_Page_BeginText (page);
   tw1 = HPDF_Page_TextWidth (page, "Affordable");   HPDF_Page_TextOut (page, iTableLeft - 40 - 28 - (tw1/2), iCurY+16, "Affordable" );
   tw1 = HPDF_Page_TextWidth (page, "Housing"   );   HPDF_Page_TextOut (page, iTableLeft - 40 - 28 - (tw1/2), iCurY+ 4, "Housing"    );
   tw1 = HPDF_Page_TextWidth (page, "Market"    );   HPDF_Page_TextOut (page, iTableLeft - 20      - (tw1/2), iCurY+16, "Market"     );
   tw1 = HPDF_Page_TextWidth (page, "Rate"      );   HPDF_Page_TextOut (page, iTableLeft - 20      - (tw1/2), iCurY+ 4, "Rate"       );
   HPDF_Page_EndText (page);


   HPDF_Page_SetFontAndSize (page, font, 10);     // SAC 12/05/22
   iRectHt = 15;
   int iUnitTypeColWd = iTableLeft - iPgLeft - 40 - 56;
   for (iMtr=0; iMtr < lNumUnitTypes; iMtr++)
      if (iaPosUnitTypeIdxs[iMtr] >= 0)
      {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
         int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
         if (iResObjIdx >= 0)
         {  iCurY -= iRectHt;
            int iMtrIdx = iaPosUnitTypeIdxs[iMtr];
            HPDF_Page_Rectangle (page, iPgLeft                   , iCurY, iUnitTypeColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iPgLeft+iUnitTypeColWd    , iCurY, 56, iRectHt );  
            HPDF_Page_Rectangle (page, iPgLeft+iUnitTypeColWd+56 , iCurY, 40, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft                , iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+ iTableColWd   , iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*2), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*3), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Rectangle (page, iTableLeft+(iTableColWd*4), iCurY, iTableColWd, iRectHt );  
            HPDF_Page_Stroke (page);

            HPDF_Page_BeginText (page);
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitTypeLabels" )+iMtrIdx, qsLabel,  FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
            HPDF_Page_TextOut (page, iPgLeft+3, iCurY+4, qsLabel.toLocal8Bit().constData() );

            qsLabel = QString::number( laNumUnitsByBedrms[iMtrIdx] );
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iPgLeft+iUnitTypeColWd+35   -tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            qsLabel = QString::number( laNumMktRateUnitsByBedrms[iMtrIdx] );
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iPgLeft+iUnitTypeColWd+56+29-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );

            BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:ElecCosts[2]"     ), qsLabel2, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );   qsLabel = QString("$ %1").arg(qsLabel2);
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iTableLeft+ iTableColWd   -15-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:GasCosts[2]"      ), qsLabel2, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );   qsLabel = QString("$ %1").arg(qsLabel2);
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*2)-15-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:WaterCosts[2]"    ), qsLabel2, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );   qsLabel = QString("$ %1").arg(qsLabel2);
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*3)-15-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:TrashMonthlyCost" ), qsLabel2, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );   qsLabel = QString("$ %1").arg(qsLabel2);
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*4)-15-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            BEMPX_GetString( BEMPX_GetDatabaseID( "CUACResults:TotCosts[2]"      ), qsLabel2, TRUE, 2, -1, iResObjIdx, BEMO_User, NULL, 0, iBEMProcIdx );   qsLabel = QString("$ %1").arg(qsLabel2);
            tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iTableLeft+(iTableColWd*5)-15-tw1, iCurY+4, qsLabel.toLocal8Bit().constData() );
            HPDF_Page_EndText (page);
         }
      }


   iCurY -= (((6-lNumUnitTypes) * iRectHt) + 30);     // SAC 12/05/22
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgLeft + 60, iCurY, "I attest that the inputs to the Project Specific Utility Allowance Calculator are accurate.");
   iRectHt = 27;
   int iLeftColX  = iPgLeft + 70;   int iSignColWd = 210;
   int iRightColX = iLeftColX + iSignColWd + 15;
   iCurY -= 20;
   tw1 = HPDF_Page_TextWidth (page, "Energy Consultant");   HPDF_Page_TextOut (page, iLeftColX  + (iSignColWd/2) - (tw1/2), iCurY, "Energy Consultant" );
   tw1 = HPDF_Page_TextWidth (page, "Project Owner"    );   HPDF_Page_TextOut (page, iRightColX + (iSignColWd/2) - (tw1/2), iCurY, "Project Owner"     );
   HPDF_Page_EndText (page);
   iCurY -=  9;

   for (iRow=0; iRow < 7; iRow++)
   {  switch (iRow)
      {  case  0 :  qsLabel = "Signature:";   break;
         case  1 :  qsLabel = "Name:";   break;
         case  2 :  qsLabel = "Title:";   break;
         case  3 :  qsLabel = "Company:";   break;
         case  4 :  qsLabel = "Phone:";   break;
         case  5 :  qsLabel = "CEA Nbr:";   break;
         case  6 :  qsLabel = "Date:";   break;
      }
      iCurY -= iRectHt;
      HPDF_Page_BeginText (page);
      tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());   HPDF_Page_TextOut (page, iLeftColX - 5 - tw1, iCurY+2, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);

      HPDF_Page_MoveTo  (page, iLeftColX , iCurY  );     HPDF_Page_LineTo  (page, iLeftColX  + iSignColWd, iCurY );
      HPDF_Page_MoveTo  (page, iRightColX, iCurY  );     HPDF_Page_LineTo  (page, iRightColX + iSignColWd, iCurY );
      HPDF_Page_Stroke (page);
   }



//   HPDF_Page_SetFontAndSize (page, fontBold, 24);
//   HPDF_Page_BeginText (page);
//   HPDF_Page_TextOut (page, 150, 80, "Report Under Development");
//   HPDF_Page_EndText (page);



   HPDF_SaveToFile (pdf, pszPDFPathFile);
   HPDF_Free (pdf);

   return 0;
}




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//   SAMPLE CODE    - mostly from demo\text_demo2.c
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//static void print_grid  (HPDF_Doc pdf, HPDF_Page page);

int Sample( const char* pszPDFPathFile, int iPDFID, int iBEMProcIdx )
//int BEMPX_GeneratePDF( const char* pszPDFPathFile, int iPDFID, int iBEMProcIdx )
{
    HPDF_Doc  pdf;
    HPDF_Page page;
    //char fname[256];
    HPDF_Font font;
    float angle1;
    float angle2;
    float rad1;
    float rad2;
    HPDF_REAL page_height;
    HPDF_Rect rect;
    int i;

   iPDFID;
   iBEMProcIdx;

   const char* SAMP_TXT = "The quick brown fox jumps over the lazy dog. ";
   //strcpy (fname, argv[0]);
   //strcat (fname, ".pdf");
   pdf = HPDF_New (error_handler, NULL);
   if (!pdf) {
       printf ("error: cannot create PdfDoc object\n");
       return 1;
   }
   if (setjmp(env)) {
       HPDF_Free (pdf);
       return 1;
   }
   /* add a new page object. */
   page = HPDF_AddPage (pdf);
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
   print_grid  (pdf, page);
   page_height = HPDF_Page_GetHeight (page);
   font = HPDF_GetFont (pdf, "Helvetica", NULL);
   HPDF_Page_SetTextLeading (page, 20);
   /* text_rect method */
   /* HPDF_TALIGN_LEFT */
   rect.left = 25;
   rect.top = 545;
   rect.right = 200;
   rect.bottom = rect.top - 40;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_LEFT");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_LEFT, NULL);
   HPDF_Page_EndText (page);
   /* HPDF_TALIGN_RIGTH */
   rect.left = 220;
   rect.right = 395;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_RIGTH");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_RIGHT, NULL);
   HPDF_Page_EndText (page);
   /* HPDF_TALIGN_CENTER */
   rect.left = 25;
   rect.top = 475;
   rect.right = 200;
   rect.bottom = rect.top - 40;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_CENTER");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_CENTER, NULL);
   HPDF_Page_EndText (page);
   /* HPDF_TALIGN_JUSTIFY */
   rect.left = 220;
   rect.right = 395;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_JUSTIFY");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_JUSTIFY, NULL);
   HPDF_Page_EndText (page);
   /* Skewed coordinate system */
   HPDF_Page_GSave (page);
   angle1 = 5;
   angle2 = 10;
   rad1 = angle1 / 180 * 3.141592;
   rad2 = angle2 / 180 * 3.141592;
   HPDF_Page_Concat (page, 1, tan(rad1), tan(rad2), 1, 25, 350);
   rect.left = 0;
   rect.top = 40;
   rect.right = 175;
   rect.bottom = 0;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "Skewed coordinate system");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_LEFT, NULL);
   HPDF_Page_EndText (page);
   HPDF_Page_GRestore (page);
   /* Rotated coordinate system */
   HPDF_Page_GSave (page);
   angle1 = 5;
   rad1 = angle1 / 180 * 3.141592;
   HPDF_Page_Concat (page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), 220, 350);
   rect.left = 0;
   rect.top = 40;
   rect.right = 175;
   rect.bottom = 0;
   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
               rect.top - rect.bottom);
   HPDF_Page_Stroke (page);
   HPDF_Page_BeginText (page);
   HPDF_Page_SetFontAndSize (page, font, 10);
   HPDF_Page_TextOut (page, rect.left, rect.top + 3, "Rotated coordinate system");
   HPDF_Page_SetFontAndSize (page, font, 13);
   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
               SAMP_TXT, HPDF_TALIGN_LEFT, NULL);
   HPDF_Page_EndText (page);
   HPDF_Page_GRestore (page);
   /* text along a circle */
   HPDF_Page_SetGrayStroke (page, 0);
   HPDF_Page_Circle (page, 210, 190, 145);
   HPDF_Page_Circle (page, 210, 190, 113);
   HPDF_Page_Stroke (page);
   angle1 = 360 / (strlen (SAMP_TXT));
   angle2 = 180;
   HPDF_Page_BeginText (page);
   font = HPDF_GetFont (pdf, "Courier-Bold", NULL);
   HPDF_Page_SetFontAndSize (page, font, 30);
   for (i = 0; i < strlen (SAMP_TXT); i++) {
       char buf[2];
       float x;
       float y;
       rad1 = (angle2 - 90) / 180 * 3.141592;
       rad2 = angle2 / 180 * 3.141592;
       x = 210 + cos(rad2) * 122;
       y = 190 + sin(rad2) * 122;
       HPDF_Page_SetTextMatrix(page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), x, y);
       buf[0] = SAMP_TXT[i];
       buf[1] = 0;
       HPDF_Page_ShowText (page, buf);
       angle2 -= angle1;
   }
   HPDF_Page_EndText (page);
   /* save the document to a file */
   HPDF_SaveToFile (pdf, pszPDFPathFile);  // fname);
   /* clean up */
   HPDF_Free (pdf);
   return 0;
}



void print_grid  (HPDF_Doc     pdf,
                  HPDF_Page    page)
{
    HPDF_REAL height = HPDF_Page_GetHeight (page);
    HPDF_REAL width = HPDF_Page_GetWidth (page);
    HPDF_Font font = HPDF_GetFont (pdf, "Helvetica", NULL);
    HPDF_UINT x, y;

    HPDF_Page_SetFontAndSize (page, font, 5);
    HPDF_Page_SetGrayFill (page, 0.5);
    HPDF_Page_SetGrayStroke (page, (HPDF_REAL) 0.8);

    /* Draw horizontal lines */
    y = 0;
    while (y < height) {
        if (y % 10 == 0)
            HPDF_Page_SetLineWidth (page, 0.5);
        else {
            if (HPDF_Page_GetLineWidth (page) != 0.25)
                HPDF_Page_SetLineWidth (page, 0.25);
        }

        HPDF_Page_MoveTo (page, 0, y);
        HPDF_Page_LineTo (page, width, y);
        HPDF_Page_Stroke (page);

        if (y % 10 == 0 && y > 0) {
            HPDF_Page_SetGrayStroke (page, 0.5);

            HPDF_Page_MoveTo (page, 0, y);
            HPDF_Page_LineTo (page, 5, y);
            HPDF_Page_Stroke (page);

            HPDF_Page_SetGrayStroke (page, (HPDF_REAL) 0.8);
        }

        y += 5;
    }


    /* Draw vertical lines */
    x = 0;
    while (x < width) {
        if (x % 10 == 0)
            HPDF_Page_SetLineWidth (page, 0.5);
        else {
            if (HPDF_Page_GetLineWidth (page) != 0.25)
                HPDF_Page_SetLineWidth (page, 0.25);
        }

        HPDF_Page_MoveTo (page, x, 0);
        HPDF_Page_LineTo (page, x, height);
        HPDF_Page_Stroke (page);

        if (x % 50 == 0 && x > 0) {
            HPDF_Page_SetGrayStroke (page, 0.5);

            HPDF_Page_MoveTo (page, x, 0);
            HPDF_Page_LineTo (page, x, 5);
            HPDF_Page_Stroke (page);

            HPDF_Page_MoveTo (page, x, height);
            HPDF_Page_LineTo (page, x, height - 5);
            HPDF_Page_Stroke (page);

            HPDF_Page_SetGrayStroke (page, (HPDF_REAL) 0.8);
        }

        x += 5;
    }

    /* Draw horizontal text */
    y = 0;
    while (y < height) {
        if (y % 10 == 0 && y > 0) {
            char buf[12];

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, 5, y - 2);
#ifdef __WIN32__
            _snprintf (buf, 12, "%u", y);
#else
            snprintf (buf, 12, "%u", y);
#endif
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);
        }

        y += 5;
    }


    /* Draw vertical text */
    x = 0;
    while (x < width) {
        if (x % 50 == 0 && x > 0) {
            char buf[12];

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, x, 5);
#ifdef __WIN32__
            _snprintf (buf, 12, "%u", x);
#else
            snprintf (buf, 12, "%u", x);
#endif
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, x, height - 10);
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);
        }

        x += 5;
    }

    HPDF_Page_SetGrayFill (page, 0);
    HPDF_Page_SetGrayStroke (page, 0);
}

