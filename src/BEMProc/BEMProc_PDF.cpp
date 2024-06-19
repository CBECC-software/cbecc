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
   for (iCol=4; iCol<=15; iCol++)
      HPDF_Page_TextOut (page, iTblColLeftX[iCol] + iTableColMid - (HPDF_Page_TextWidth (page, pszMoLabel[iCol-4] )/2),  iCurY + 4, pszMoLabel[iCol-4] );
   HPDF_Page_EndText (page);
   return;
}

#define  Num_Elec_Enduses  11
const char*  pszElecEnduseName[]  = { "Cooking", "Cooling", "DHW", "Dishwasher", "Dryer", "Heating", "IAQ Vent.", "Lighting", "Plug Loads", "Refrigerator", "Washer",  NULL  };
const char*  pszElecEnduseProps[] = { "CUACResults:CkgElecUse", "CUACResults:ClgElecUse", "CUACResults:DHWElecUse", "CUACResults:DishElecUse", "CUACResults:DryerElecUse", "CUACResults:HtgElecUse",
                                      "CUACResults:IAQVentElecUse", "CUACResults:LtgElecUse", "CUACResults:PlugLdsElecUse", "CUACResults:RfrgElecUse", "CUACResults:WashElecUse",  NULL  };
int iaEnduseDetailsArrIdx[] = {  13, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };

void GenerateTable_UnitDetails_ElecTable( HPDF_Page& page, HPDF_Font& font, HPDF_Font& fontBold, int& iCurY,      // SAC 01/23/23
                                          int* iTblColWds, int* iTblColLeftX, int iPgLeft, int iPgRight, int iPgCenter, int iResObjIdx )
{






//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,%s,Cooking,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",     UnitTypeLabels[#U], CUACResultsRef[#U]:CkgElecUse[14], CUACResultsRef[#U]:CkgElecUse[13],
//                              CUACResultsRef[#U]:CkgElecUse[1], CUACResultsRef[#U]:CkgElecUse[2], CUACResultsRef[#U]:CkgElecUse[3], CUACResultsRef[#U]:CkgElecUse[4],  CUACResultsRef[#U]:CkgElecUse[5],  CUACResultsRef[#U]:CkgElecUse[6],
//                              CUACResultsRef[#U]:CkgElecUse[7], CUACResultsRef[#U]:CkgElecUse[8], CUACResultsRef[#U]:CkgElecUse[9], CUACResultsRef[#U]:CkgElecUse[10], CUACResultsRef[#U]:CkgElecUse[11], CUACResultsRef[#U]:CkgElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Cooling,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                           CUACResultsRef[#U]:ClgElecUse[14], CUACResultsRef[#U]:ClgElecUse[13],
//                              CUACResultsRef[#U]:ClgElecUse[1], CUACResultsRef[#U]:ClgElecUse[2], CUACResultsRef[#U]:ClgElecUse[3], CUACResultsRef[#U]:ClgElecUse[4],  CUACResultsRef[#U]:ClgElecUse[5],  CUACResultsRef[#U]:ClgElecUse[6],
//                              CUACResultsRef[#U]:ClgElecUse[7], CUACResultsRef[#U]:ClgElecUse[8], CUACResultsRef[#U]:ClgElecUse[9], CUACResultsRef[#U]:ClgElecUse[10], CUACResultsRef[#U]:ClgElecUse[11], CUACResultsRef[#U]:ClgElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,DHW,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                               CUACResultsRef[#U]:DHWElecUse[14], CUACResultsRef[#U]:DHWElecUse[13],
//                              CUACResultsRef[#U]:DHWElecUse[1], CUACResultsRef[#U]:DHWElecUse[2], CUACResultsRef[#U]:DHWElecUse[3], CUACResultsRef[#U]:DHWElecUse[4],  CUACResultsRef[#U]:DHWElecUse[5],  CUACResultsRef[#U]:DHWElecUse[6],
//                              CUACResultsRef[#U]:DHWElecUse[7], CUACResultsRef[#U]:DHWElecUse[8], CUACResultsRef[#U]:DHWElecUse[9], CUACResultsRef[#U]:DHWElecUse[10], CUACResultsRef[#U]:DHWElecUse[11], CUACResultsRef[#U]:DHWElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Dishwasher,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                            CUACResultsRef[#U]:DishElecUse[14], CUACResultsRef[#U]:DishElecUse[13],
//                              CUACResultsRef[#U]:DishElecUse[1], CUACResultsRef[#U]:DishElecUse[2], CUACResultsRef[#U]:DishElecUse[3], CUACResultsRef[#U]:DishElecUse[4],  CUACResultsRef[#U]:DishElecUse[5],  CUACResultsRef[#U]:DishElecUse[6],
//                              CUACResultsRef[#U]:DishElecUse[7], CUACResultsRef[#U]:DishElecUse[8], CUACResultsRef[#U]:DishElecUse[9], CUACResultsRef[#U]:DishElecUse[10], CUACResultsRef[#U]:DishElecUse[11], CUACResultsRef[#U]:DishElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Dryer,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                                     CUACResultsRef[#U]:DryerElecUse[14], CUACResultsRef[#U]:DryerElecUse[13],
//                              CUACResultsRef[#U]:DryerElecUse[1], CUACResultsRef[#U]:DryerElecUse[2], CUACResultsRef[#U]:DryerElecUse[3], CUACResultsRef[#U]:DryerElecUse[4],  CUACResultsRef[#U]:DryerElecUse[5],  CUACResultsRef[#U]:DryerElecUse[6],
//                              CUACResultsRef[#U]:DryerElecUse[7], CUACResultsRef[#U]:DryerElecUse[8], CUACResultsRef[#U]:DryerElecUse[9], CUACResultsRef[#U]:DryerElecUse[10], CUACResultsRef[#U]:DryerElecUse[11], CUACResultsRef[#U]:DryerElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Heating,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                           CUACResultsRef[#U]:HtgElecUse[14], CUACResultsRef[#U]:HtgElecUse[13],
//                              CUACResultsRef[#U]:HtgElecUse[1], CUACResultsRef[#U]:HtgElecUse[2], CUACResultsRef[#U]:HtgElecUse[3], CUACResultsRef[#U]:HtgElecUse[4],  CUACResultsRef[#U]:HtgElecUse[5],  CUACResultsRef[#U]:HtgElecUse[6],
//                              CUACResultsRef[#U]:HtgElecUse[7], CUACResultsRef[#U]:HtgElecUse[8], CUACResultsRef[#U]:HtgElecUse[9], CUACResultsRef[#U]:HtgElecUse[10], CUACResultsRef[#U]:HtgElecUse[11], CUACResultsRef[#U]:HtgElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,IAQ Ventilation,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                                   CUACResultsRef[#U]:IAQVentElecUse[14], CUACResultsRef[#U]:IAQVentElecUse[13],
//                              CUACResultsRef[#U]:IAQVentElecUse[1], CUACResultsRef[#U]:IAQVentElecUse[2], CUACResultsRef[#U]:IAQVentElecUse[3], CUACResultsRef[#U]:IAQVentElecUse[4],  CUACResultsRef[#U]:IAQVentElecUse[5],  CUACResultsRef[#U]:IAQVentElecUse[6],
//                              CUACResultsRef[#U]:IAQVentElecUse[7], CUACResultsRef[#U]:IAQVentElecUse[8], CUACResultsRef[#U]:IAQVentElecUse[9], CUACResultsRef[#U]:IAQVentElecUse[10], CUACResultsRef[#U]:IAQVentElecUse[11], CUACResultsRef[#U]:IAQVentElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Lighting,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                          CUACResultsRef[#U]:LtgElecUse[14], CUACResultsRef[#U]:LtgElecUse[13],
//                              CUACResultsRef[#U]:LtgElecUse[1], CUACResultsRef[#U]:LtgElecUse[2], CUACResultsRef[#U]:LtgElecUse[3], CUACResultsRef[#U]:LtgElecUse[4],  CUACResultsRef[#U]:LtgElecUse[5],  CUACResultsRef[#U]:LtgElecUse[6],
//                              CUACResultsRef[#U]:LtgElecUse[7], CUACResultsRef[#U]:LtgElecUse[8], CUACResultsRef[#U]:LtgElecUse[9], CUACResultsRef[#U]:LtgElecUse[10], CUACResultsRef[#U]:LtgElecUse[11], CUACResultsRef[#U]:LtgElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Plug Loads,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                                        CUACResultsRef[#U]:PlugLdsElecUse[14], CUACResultsRef[#U]:PlugLdsElecUse[13],
//                              CUACResultsRef[#U]:PlugLdsElecUse[1], CUACResultsRef[#U]:PlugLdsElecUse[2], CUACResultsRef[#U]:PlugLdsElecUse[3], CUACResultsRef[#U]:PlugLdsElecUse[4],  CUACResultsRef[#U]:PlugLdsElecUse[5],  CUACResultsRef[#U]:PlugLdsElecUse[6],
//                              CUACResultsRef[#U]:PlugLdsElecUse[7], CUACResultsRef[#U]:PlugLdsElecUse[8], CUACResultsRef[#U]:PlugLdsElecUse[9], CUACResultsRef[#U]:PlugLdsElecUse[10], CUACResultsRef[#U]:PlugLdsElecUse[11], CUACResultsRef[#U]:PlugLdsElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Refrigerator,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                          CUACResultsRef[#U]:RfrgElecUse[14], CUACResultsRef[#U]:RfrgElecUse[13],
//                              CUACResultsRef[#U]:RfrgElecUse[1], CUACResultsRef[#U]:RfrgElecUse[2], CUACResultsRef[#U]:RfrgElecUse[3], CUACResultsRef[#U]:RfrgElecUse[4],  CUACResultsRef[#U]:RfrgElecUse[5],  CUACResultsRef[#U]:RfrgElecUse[6],
//                              CUACResultsRef[#U]:RfrgElecUse[7], CUACResultsRef[#U]:RfrgElecUse[8], CUACResultsRef[#U]:RfrgElecUse[9], CUACResultsRef[#U]:RfrgElecUse[10], CUACResultsRef[#U]:RfrgElecUse[11], CUACResultsRef[#U]:RfrgElecUse[12] )  }
//   "Write CUAC I/O CSV inputs"   for:#U=(1to1)   CUAC:Action =
//               {  WriteToExportFile( InOutCSVFileIdx, ",,,Washer,%.2f,%.0f,,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",                                CUACResultsRef[#U]:WashElecUse[14], CUACResultsRef[#U]:WashElecUse[13],
//                              CUACResultsRef[#U]:WashElecUse[1], CUACResultsRef[#U]:WashElecUse[2], CUACResultsRef[#U]:WashElecUse[3], CUACResultsRef[#U]:WashElecUse[4],  CUACResultsRef[#U]:WashElecUse[5],  CUACResultsRef[#U]:WashElecUse[6],
//                              CUACResultsRef[#U]:WashElecUse[7], CUACResultsRef[#U]:WashElecUse[8], CUACResultsRef[#U]:WashElecUse[9], CUACResultsRef[#U]:WashElecUse[10], CUACResultsRef[#U]:WashElecUse[11], CUACResultsRef[#U]:WashElecUse[12] )  }

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
   QString qsLabel, qsLabel2, qsLabel3, qsTemp;
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
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Gas   Utility"      ), iCurY - (iProjInfoRowHt *  8), "Gas   Utility"       );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  9), "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt * 10), "Tariff"              );

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
   for (iRow=1; iRow <= 10; iRow++)
   {  switch (iRow)
      {  case  1 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:StAddress"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerName"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  2 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:City"          ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerAddress"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  3 :  BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:ZipCode"       ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerCity"      ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  4 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType"      ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerState"     ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  5 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"   ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OwnerZIPCode"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  6 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTerritory" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"    ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  7 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariff"    ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactPhone"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  8 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"    ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactEMail"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  9 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTerritory"  ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:APN"            ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case 10 :  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariff"     ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:OtherProjectID" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
      } 
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iProjInfoLeftX , iCurY - (iProjInfoRowHt * iRow),  qsLabel.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, iProjInfoRightX, iCurY - (iProjInfoRowHt * iRow), qsLabel2.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

      HPDF_Page_MoveTo  (page, iProjInfoLeftX -2, iCurY - (iProjInfoRowHt * iRow)-3 );     HPDF_Page_LineTo  (page, iProjInfoLeftX +iProjInfoLeftLen , iCurY - (iProjInfoRowHt * iRow)-3 );
      HPDF_Page_MoveTo  (page, iProjInfoRightX-2, iCurY - (iProjInfoRowHt * iRow)-3 );     HPDF_Page_LineTo  (page, iProjInfoRightX+iProjInfoRightLen, iCurY - (iProjInfoRowHt * iRow)-3 );
      HPDF_Page_Stroke  (page);
   }
   iCurY -= ((iProjInfoRowHt * 10) + 30);


   // export of Allowance results - SAC 01/05/23
#define  NumDwellingMeters   7
   int iCUAC_BEMProcIdx = -1;  // ???
   int iMtr, iSpecVal, iErr, iCol;
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
                     qsLabel.clear();
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
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 2) -3, "Gas"      );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 4) -6, "Trash"    );
   HPDF_Page_TextOut (page, iPgLeft, iCurY - (iProjInfoRowHt * 5) -9, "Water"    );
   HPDF_Page_EndText (page);

   iProjInfoLeftX = 130;   iProjInfoRightX = 630;     int iProjInfoLeftX2 = 370;
   HPDF_Page_SetFontAndSize (page, font, 8); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Utility"            ), iCurY                          , "Utility"             );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  1)  , "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt *  1)  , "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Utility"            ), iCurY - (iProjInfoRowHt *  2)-3, "Utility"             );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Territory"          ), iCurY - (iProjInfoRowHt *  3)-3, "Territory"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Tariff"             ), iCurY - (iProjInfoRowHt *  3)-3, "Tariff"              );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Rate Type"          ), iCurY - (iProjInfoRowHt *  4)-6, "Rate Type"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Monthly Charge"     ), iCurY - (iProjInfoRowHt *  4)-6, "Monthly Charge"      );
   HPDF_Page_TextOut (page, iProjInfoLeftX  - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Rate Type"          ), iCurY - (iProjInfoRowHt *  5)-9, "Rate Type"           );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Monthly Charge"     ), iCurY - (iProjInfoRowHt *  5)-9, "Monthly Charge"      );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Water $/Gallon"     ), iCurY - (iProjInfoRowHt *  6)-9, "Water $/Gallon"      );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Space Heating"      ), iCurY                          , "Space Heating"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Water Heating"      ), iCurY - (iProjInfoRowHt *  1)  , "Water Heating"       );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Cooking"            ), iCurY - (iProjInfoRowHt *  2)  , "Cooking"             );
   HPDF_Page_TextOut (page, iProjInfoRightX - iProjInfoMarginX - HPDF_Page_TextWidth (page, "Clothes Dryer"      ), iCurY - (iProjInfoRowHt *  3)  , "Clothes Dryer"       );
   HPDF_Page_EndText (page);

   HPDF_Page_SetLineWidth (page, 0.25);
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY -3 );                          HPDF_Page_LineTo  (page, 480, iCurY -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, 320, iCurY - iProjInfoRowHt -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3, iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, 480, iCurY - iProjInfoRowHt -3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY - (iProjInfoRowHt*2) -3-3 );   HPDF_Page_LineTo  (page, 480, iCurY - (iProjInfoRowHt*2) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY - (iProjInfoRowHt*3) -3-3 );   HPDF_Page_LineTo  (page, 320, iCurY - (iProjInfoRowHt*3) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3, iCurY - (iProjInfoRowHt*3) -3-3 );   HPDF_Page_LineTo  (page, 480, iCurY - (iProjInfoRowHt*3) -3-3 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY - (iProjInfoRowHt*4) -3-6 );   HPDF_Page_LineTo  (page, 280, iCurY - (iProjInfoRowHt*4) -3-6 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3, iCurY - (iProjInfoRowHt*4) -3-6 );   HPDF_Page_LineTo  (page, 480, iCurY - (iProjInfoRowHt*4) -3-6 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX -3, iCurY - (iProjInfoRowHt*5) -3-9 );   HPDF_Page_LineTo  (page, 280, iCurY - (iProjInfoRowHt*5) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3, iCurY - (iProjInfoRowHt*5) -3-9 );   HPDF_Page_LineTo  (page, 480, iCurY - (iProjInfoRowHt*5) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoLeftX2-3, iCurY - (iProjInfoRowHt*6) -3-9 );   HPDF_Page_LineTo  (page, 480, iCurY - (iProjInfoRowHt*6) -3-9 );
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3, iCurY -3 );                          HPDF_Page_LineTo  (page, 720, iCurY -3 );                     
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3, iCurY -  iProjInfoRowHt    -3 );     HPDF_Page_LineTo  (page, 720, iCurY -  iProjInfoRowHt    -3 );
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3, iCurY - (iProjInfoRowHt*2) -3 );     HPDF_Page_LineTo  (page, 720, iCurY - (iProjInfoRowHt*2) -3 );
   HPDF_Page_MoveTo  (page, iProjInfoRightX-3, iCurY - (iProjInfoRowHt*3) -3 );     HPDF_Page_LineTo  (page, 720, iCurY - (iProjInfoRowHt*3) -3 );
   HPDF_Page_Stroke (page);

   HPDF_Page_SetFontAndSize (page, font, 9);    // SAC 01/07/23
   HPDF_Page_BeginText (page);
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"   ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTerritory" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariff"    ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY                        , qsLabel.toLocal8Bit().constData()  );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  1), qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  1), qsLabel3.toLocal8Bit().constData() );

   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"    ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTerritory"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariff"     ), qsLabel3, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  2)-3, qsLabel.toLocal8Bit().constData()  );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  3)-3, qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  3)-3, qsLabel3.toLocal8Bit().constData() );

   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TrashRateType"    ), qsLabel , FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:TrashMonthlyCost" ), qsTemp  ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );      qsLabel2 = QString( "$ %1" ).arg( qsTemp );
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  4)-6,  qsLabel.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  4)-6, qsLabel2.toLocal8Bit().constData() );

   BEMPX_GetString(    BEMPX_GetDatabaseID( "CUAC:WaterRateType"    ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );
   BEMPX_GetString(    BEMPX_GetDatabaseID( "CUAC:WaterMonthlyCost" ), qsTemp ,  TRUE, 2, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel2 = QString( "$ %1" ).arg( qsTemp );
   if (qsLabel.indexOf("Usage")==0)
   {  BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:WaterVolumeCost"  ), qsTemp , TRUE, 11, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );    qsLabel3 = QString( "$ %1" ).arg( qsTemp );
   }
   else
      qsLabel3.clear();
   HPDF_Page_TextOut (page, iProjInfoLeftX  , iCurY - (iProjInfoRowHt *  5)-9,  qsLabel.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  5)-9, qsLabel2.toLocal8Bit().constData() );
   HPDF_Page_TextOut (page, iProjInfoLeftX2 , iCurY - (iProjInfoRowHt *  6)-9, qsLabel3.toLocal8Bit().constData() );
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


   iCurY -= ((iProjInfoRowHt *  6)+9 + 22);        // SAC 01/08/23
   qsLabel = "Apartments Inventory";
   HPDF_Page_SetFontAndSize (page, fontBold, 10); 
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() )/2), iCurY, qsLabel.toLocal8Bit().constData());
   HPDF_Page_EndText (page);

   iRectHt = 28;     // SAC 01/08/23
   iCurY -= (iRectHt+8);
   int iTblColWds[] = { 120, 80, 80 };
   int iTblColLeftX[16];
   iTblColLeftX[0] = iPgCenter - ((iTblColWds[0] + iTblColWds[1] + iTblColWds[2]) / 2);
   iTblColLeftX[1] = iTblColLeftX[0] + iTblColWds[0];
   iTblColLeftX[2] = iTblColLeftX[1] + iTblColWds[1];
   HPDF_Page_SetGrayFill (page, (HPDF_REAL) 0.9);
   HPDF_Page_Rectangle (page, iTblColLeftX[0], iCurY, iTblColWds[0], iRectHt );
   HPDF_Page_Rectangle (page, iTblColLeftX[1], iCurY, iTblColWds[1], iRectHt );
   HPDF_Page_Rectangle (page, iTblColLeftX[2], iCurY, iTblColWds[2], iRectHt );
   HPDF_Page_FillStroke (page);

   HPDF_Page_SetGrayFill (page, 0);
   HPDF_Page_SetFontAndSize (page, font, 8);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iTblColLeftX[0] + 4,  iCurY + 5, "Apartment Type"    );
   HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "# Affordable"  )/2), iCurY + 16, "# Affordable"  );
   HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]/2) - (HPDF_Page_TextWidth (page, "Housing Units" )/2), iCurY +  5, "Housing Units" );
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "# Market Rate" )/2), iCurY + 16, "# Market Rate" );
   HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]/2) - (HPDF_Page_TextWidth (page, "Housing Units" )/2), iCurY +  5, "Housing Units" );
   HPDF_Page_EndText (page);

   HPDF_Page_SetFontAndSize (page, font, 10);      // SAC 01/08/23
   iRectHt = 15;
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
            HPDF_Page_TextOut (page, iTblColLeftX[0]+4, iCurY+4, qsLabel.toLocal8Bit().constData() );

            qsLabel = QString::number( laNumUnitsByBedrms[iMtrIdx] );
            HPDF_Page_TextOut (page, iTblColLeftX[1] + (iTblColWds[1]*2/3) -HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData()), iCurY+4, qsLabel.toLocal8Bit().constData() );
            qsLabel = QString::number( laNumMktRateUnitsByBedrms[iMtrIdx] );
            HPDF_Page_TextOut (page, iTblColLeftX[2] + (iTblColWds[2]*2/3) -HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData()), iCurY+4, qsLabel.toLocal8Bit().constData() );
            HPDF_Page_EndText (page);
      }  }

   iCurY -= 4;
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




// RESTORE ONCE DONE - SAC 01/23/23
// 
// //   GenerateTable_Details_StartNewPage( pdf, page, image, font, fontBold, iCurX, iCurY, false, false, iPgTop, iPgLeft, iPgCenter, ++iPageNum, qsProjID, qsRunDateFmt, qsProjNameTitle );
//    ///////////////////////////////////////////------------------------------------------------------------------------------------------------------------
//    /////              PAGE 4             /////
//    ///////////////////////////////////////////
//    int iPgNum = 3;  // will increment before writing...
//    QString qsPgNumLabel;
//    page = HPDF_AddPage (pdf);     // SAC 01/12/23
//    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
// 
// //   print_grid  (pdf, page);
// 
//    iCurY = iPgTop;
//    iCurX = iPgLeft;
//    HPDF_Page_SetFontAndSize (page, fontBold, 6);
//    iCurY -= 25;
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 12;
//    HPDF_Page_SetFontAndSize (page, fontBold, 10);
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 3;
//    HPDF_Page_SetGrayFill (page, 0);  // 0.5);
//    HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
//    HPDF_Page_SetLineWidth (page, 1.25);
//    HPDF_Page_MoveTo  (page, iCurX, iCurY );
//    HPDF_Page_LineTo  (page,   230, iCurY );
//    HPDF_Page_Stroke (page);
// 
//    iCurY -= 11;
//    HPDF_Page_SetFontAndSize (page, fontBold, 8);
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
//    HPDF_Page_EndText (page);
// 
//    iCurY -= 13;
//    if (!qsProjID.isEmpty())
//    {  HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
//       HPDF_Page_EndText (page);
//    }
//    HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23
// 
//    qsPgNumLabel = QString("Page %1").arg(QString::number(++iPgNum));
//    if (!qsRunDateFmt.isEmpty())
//    {  iCurY = iPgTop - 56;
//       int iMidX = 690;   // 505;    - landscaoe vs. portrait
//       HPDF_Page_SetFontAndSize (page, fontBold, 8);
//       tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
//       tw2 = HPDF_Page_TextWidth (page, qsPgNumLabel.toLocal8Bit().constData());
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
//       HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPgNumLabel.toLocal8Bit().constData());
//       HPDF_Page_EndText (page);
//    }
// 
//    HPDF_Page_SetFontAndSize (page, fontBold, 10); 
//    iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
//    HPDF_Page_BeginText (page);
//    HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
//    HPDF_Page_EndText (page);
// 
// 
//    int iDetTblColWds[16], iDetTblColLeftX[16];
//    GenerateTable_UnitDetails_Header( page, font, fontBold, iCurY, "Electric kWh Usage by End Use Summary", &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter );
// 
//    int iNumUnitTypesThisPg = (lNumUnitTypes <= 3 ? lNumUnitTypes : 3);
//    for (iMtr=0; iMtr < iNumUnitTypesThisPg; iMtr++)
//       if (iaPosUnitTypeIdxs[iMtr] >= 0)
//       {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
//          int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
//          if (iResObjIdx >= 0)
//          {
//             GenerateTable_UnitDetails_ElecTable( page, font, fontBold, iCurY, &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter, iResObjIdx );
// 
//       }  }
// 
//    if (iNumUnitTypesThisPg < lNumUnitTypes)
//    {  // need additional page to complete Electric kWh Usage by End Use Summary tables - SAC 01/23/23
//       page = HPDF_AddPage (pdf);     // SAC 01/12/23
//       HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
//       //   print_grid  (pdf, page);
// 
//       iCurY = iPgTop;
//       iCurX = iPgLeft;
//       HPDF_Page_SetFontAndSize (page, fontBold, 6);
//       iCurY -= 25;
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iCurX, iCurY, "STATE OF CALIFORNIA");
//       HPDF_Page_EndText (page);
// 
//       iCurY -= 12;
//       HPDF_Page_SetFontAndSize (page, fontBold, 10);
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iCurX, iCurY, "CALIFORNIA ENERGY COMMISSION");
//       HPDF_Page_EndText (page);
// 
//       iCurY -= 3;
//       HPDF_Page_SetGrayFill (page, 0);  // 0.5);
//       HPDF_Page_SetGrayStroke (page, 0);  // 0.8);
//       HPDF_Page_SetLineWidth (page, 1.25);
//       HPDF_Page_MoveTo  (page, iCurX, iCurY );
//       HPDF_Page_LineTo  (page,   230, iCurY );
//       HPDF_Page_Stroke (page);
// 
//       iCurY -= 11;
//       HPDF_Page_SetFontAndSize (page, fontBold, 8);
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iCurX, iCurY, "UTILITY Allowance Calculation Tool");
//       HPDF_Page_EndText (page);
// 
//       iCurY -= 13;
//       if (!qsProjID.isEmpty())
//       {  HPDF_Page_BeginText (page);
//          HPDF_Page_TextOut (page, iCurX, iCurY, qsProjID.toLocal8Bit().constData() );   
//          HPDF_Page_EndText (page);
//       }
//       HPDF_Page_DrawImage (page, image, 240, iPgTop-76, 58, 53 );  // HPDF_Image_GetWidth (image), HPDF_Image_GetHeight (image));   - raised logo by 15 - SAC 01/13/23
// 
//       qsPgNumLabel = QString("Page %1").arg(QString::number(++iPgNum));
//       if (!qsRunDateFmt.isEmpty())
//       {  iCurY = iPgTop - 56;
//          int iMidX = 690;   // 505;    - landscaoe vs. portrait
//          HPDF_Page_SetFontAndSize (page, fontBold, 8);
//          tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
//          tw2 = HPDF_Page_TextWidth (page, qsPgNumLabel.toLocal8Bit().constData());
//          HPDF_Page_BeginText (page);
//          HPDF_Page_TextOut (page, iMidX-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
//          HPDF_Page_TextOut (page, iMidX-(tw2/2), iCurY-12, qsPgNumLabel.toLocal8Bit().constData());
//          HPDF_Page_EndText (page);
//       }
// 
//       HPDF_Page_SetFontAndSize (page, fontBold, 10); 
//       iCurY = iPgTop - 95;      // raised by 15 - SAC 01/13/23
//       HPDF_Page_BeginText (page);
//       HPDF_Page_TextOut (page, iPgCenter-(HPDF_Page_TextWidth (page, qsProjNameTitle.toLocal8Bit().constData() )/2), iCurY, qsProjNameTitle.toLocal8Bit().constData());
//       HPDF_Page_EndText (page);
// 
//       GenerateTable_UnitDetails_Header( page, font, fontBold, iCurY, "Electric kWh Usage by End Use Summary", &iDetTblColWds[0], &iDetTblColLeftX[0], iPgLeft, iPgRight, iPgCenter );
// 
//       for (iMtr=0; iMtr < iNumUnitTypesThisPg; iMtr++)
//          if (iaPosUnitTypeIdxs[iMtr] >= 0)
//          {  BEMObject* pUnitResultsObj = BEMPX_GetObjectPtr( lDBID_ResRef+iaPosUnitTypeIdxs[iMtr], iSpecVal, iErr, 0, BEMO_User, iCUAC_BEMProcIdx );
//             int iResObjIdx = (pUnitResultsObj == NULL ? -1 : BEMPX_GetObjectIndex( pUnitResultsObj->getClass(), pUnitResultsObj, iCUAC_BEMProcIdx ));       assert( iResObjIdx >= 0 );
//             if (iResObjIdx >= 0)
//             {
// 
// 
// 
//          }  }
//    }
// 


//CUAC   User: "CUAC Inputs"  
//   AffordableUnitsByBedrms[1] = RVal: 0
//   AffordableUnitsByBedrms[2] = RVal: 0
//   AffordableUnitsByBedrms[3] = RVal: 4
//   AffordableUnitsByBedrms[4] = RVal: 0
//   AffordableUnitsByBedrms[5] = RVal: 0
//   AffordableUnitsByBedrms[6] = RVal: 0
//   AffordableUnitsByBedrms[7] = RVal: 0
//   AffordableUnitsByBedrms[8] = RVal: 0
//   NumAffordableDwellingUnits = RVal: 4



//CUACResults   User: "2bedrm results"  
//   TotCosts[1] = UVal: 748.32
//   TotCosts[2] = UVal: 62.36
//   ElecCosts[1] = UVal: 190.2
//   ElecCosts[2] = UVal: 15.85
//   ElecCosts[3] = UVal: 56.1565
//   ElecCosts[4] = UVal: 13.7885
//   ElecCosts[5] = UVal: 7.53
//   ElecCosts[6] = UVal: 7.53
//   ElecCosts[7] = UVal: 7.53
//   ElecCosts[8] = UVal: 7.53
//   ElecCosts[9] = UVal: 7.53
//   ElecCosts[10] = UVal: 7.53
//   ElecCosts[11] = UVal: 7.53
//   ElecCosts[12] = UVal: 7.53
//   ElecCosts[13] = UVal: 7.53
//   ElecCosts[14] = UVal: 52.5334
//   GasCosts[1] = UVal: 69
//   GasCosts[2] = UVal: 5.75
//   GasCosts[3] = UVal: 5.75
//   GasCosts[4] = UVal: 5.75
//   GasCosts[5] = UVal: 5.75
//   GasCosts[6] = UVal: 5.75
//   GasCosts[7] = UVal: 5.75
//   GasCosts[8] = UVal: 5.75
//   GasCosts[9] = UVal: 5.75
//   GasCosts[10] = UVal: 5.75
//   GasCosts[11] = UVal: 5.75
//   GasCosts[12] = UVal: 5.75
//   GasCosts[13] = UVal: 5.75
//   GasCosts[14] = UVal: 5.75
//   WaterCosts[1] = UVal: 345.12
//   WaterCosts[2] = UVal: 28.76
//   WaterCosts[3] = UVal: 29.1575
//   WaterCosts[4] = UVal: 27.11
//   WaterCosts[5] = UVal: 29.1575
//   WaterCosts[6] = UVal: 28.475
//   WaterCosts[7] = UVal: 29.1575
//   WaterCosts[8] = UVal: 28.475
//   WaterCosts[9] = UVal: 29.1575
//   WaterCosts[10] = UVal: 29.1575
//   WaterCosts[11] = UVal: 28.475
//   WaterCosts[12] = UVal: 29.1575
//   WaterCosts[13] = UVal: 28.475
//   WaterCosts[14] = UVal: 29.1575
//   TrashMonthlyCost = UVal: 12
//   Allowances[1] = UVal: 1.36278
//   Allowances[2] = UVal: 0
//   Allowances[3] = UVal: 0.740492
//   Allowances[4] = UVal: 0
//   Allowances[5] = UVal: 0.836024
//   Allowances[6] = UVal: 9.6113
//   Allowances[7] = UVal: 5.75
//   Allowances[8] = UVal: 0.839719
//   Allowances[9] = UVal: 2.45969
//   Allowances[10] = UVal: 0
//   Allowances[11] = UVal: 28.76
//   Allowances[12] = UVal: 0
//   Allowances[13] = UVal: 12
//   CkgElecUse[1] = UVal: 24.6712
//   CkgElecUse[2] = UVal: 21.693
//   CkgElecUse[3] = UVal: 24.2211
//   CkgElecUse[4] = UVal: 19.4015
//   CkgElecUse[5] = UVal: 20.0935
//   CkgElecUse[6] = UVal: 20.4056
//   CkgElecUse[7] = UVal: 22.3933
//   CkgElecUse[8] = UVal: 20.7473
//   CkgElecUse[9] = UVal: 20.1435
//   CkgElecUse[10] = UVal: 20.7481
//   CkgElecUse[11] = UVal: 24.6158
//   CkgElecUse[12] = UVal: 26.34
//   CkgElecUse[13] = UVal: 265.474
//   CkgElecUse[14] = UVal: 0.727326
//   CkgGasUse[1] = UVal: 0
//   CkgGasUse[2] = UVal: 0
//   CkgGasUse[3] = UVal: 0
//   CkgGasUse[4] = UVal: 0
//   CkgGasUse[5] = UVal: 0
//   CkgGasUse[6] = UVal: 0
//   CkgGasUse[7] = UVal: 0
//   CkgGasUse[8] = UVal: 0
//   CkgGasUse[9] = UVal: 0
//   CkgGasUse[10] = UVal: 0
//   CkgGasUse[11] = UVal: 0
//   CkgGasUse[12] = UVal: 0
//   CkgGasUse[13] = UVal: 0
//   CkgGasUse[14] = UVal: 0
//   ClgElecUse[1] = UVal: 0
//   ClgElecUse[2] = UVal: 0
//   ClgElecUse[3] = UVal: 0
//   ClgElecUse[4] = UVal: 2.11948
//   ClgElecUse[5] = UVal: 23.2346
//   ClgElecUse[6] = UVal: 52.2667
//   ClgElecUse[7] = UVal: 84.0011
//   ClgElecUse[8] = UVal: 95.8213
//   ClgElecUse[9] = UVal: 31.1031
//   ClgElecUse[10] = UVal: 12.5014
//   ClgElecUse[11] = UVal: 0
//   ClgElecUse[12] = UVal: 0
//   ClgElecUse[13] = UVal: 301.048
//   ClgElecUse[14] = UVal: 0.824788
//   DHWElecUse[1] = UVal: 114.885
//   DHWElecUse[2] = UVal: 94.175
//   DHWElecUse[3] = UVal: 84.1252
//   DHWElecUse[4] = UVal: 83.1511
//   DHWElecUse[5] = UVal: 63.3173
//   DHWElecUse[6] = UVal: 54.2993
//   DHWElecUse[7] = UVal: 48.2529
//   DHWElecUse[8] = UVal: 45.7722
//   DHWElecUse[9] = UVal: 51.8244
//   DHWElecUse[10] = UVal: 61.0234
//   DHWElecUse[11] = UVal: 71.6346
//   DHWElecUse[12] = UVal: 109.363
//   DHWElecUse[13] = UVal: 881.823
//   DHWElecUse[14] = UVal: 2.41595
//   DHWGasUse[1] = UVal: 0
//   DHWGasUse[2] = UVal: 0
//   DHWGasUse[3] = UVal: 0
//   DHWGasUse[4] = UVal: 0
//   DHWGasUse[5] = UVal: 0
//   DHWGasUse[6] = UVal: 0
//   DHWGasUse[7] = UVal: 0
//   DHWGasUse[8] = UVal: 0
//   DHWGasUse[9] = UVal: 0
//   DHWGasUse[10] = UVal: 0
//   DHWGasUse[11] = UVal: 0
//   DHWGasUse[12] = UVal: 0
//   DHWGasUse[13] = UVal: 0
//   DHWGasUse[14] = UVal: 0
//   DishElecUse[1] = UVal: 7.61383
//   DishElecUse[2] = UVal: 8.33958
//   DishElecUse[3] = UVal: 7.97669
//   DishElecUse[4] = UVal: 9.24581
//   DishElecUse[5] = UVal: 6.70768
//   DishElecUse[6] = UVal: 7.43261
//   DishElecUse[7] = UVal: 8.33885
//   DishElecUse[8] = UVal: 6.70725
//   DishElecUse[9] = UVal: 9.42717
//   DishElecUse[10] = UVal: 9.42752
//   DishElecUse[11] = UVal: 7.6139
//   DishElecUse[12] = UVal: 7.97683
//   DishElecUse[13] = UVal: 96.8077
//   DishElecUse[14] = UVal: 0.265227
//   DryerElecUse[1] = UVal: 69.4884
//   DryerElecUse[2] = UVal: 70.1847
//   DryerElecUse[3] = UVal: 59.5295
//   DryerElecUse[4] = UVal: 61.1679
//   DryerElecUse[5] = UVal: 66.079
//   DryerElecUse[6] = UVal: 61.7129
//   DryerElecUse[7] = UVal: 68.8131
//   DryerElecUse[8] = UVal: 81.9186
//   DryerElecUse[9] = UVal: 62.8059
//   DryerElecUse[10] = UVal: 64.9901
//   DryerElecUse[11] = UVal: 62.8068
//   DryerElecUse[12] = UVal: 64.0358
//   DryerElecUse[13] = UVal: 793.533
//   DryerElecUse[14] = UVal: 2.17406
//   DryerGasUse[1] = UVal: 0
//   DryerGasUse[2] = UVal: 0
//   DryerGasUse[3] = UVal: 0
//   DryerGasUse[4] = UVal: 0
//   DryerGasUse[5] = UVal: 0
//   DryerGasUse[6] = UVal: 0
//   DryerGasUse[7] = UVal: 0
//   DryerGasUse[8] = UVal: 0
//   DryerGasUse[9] = UVal: 0
//   DryerGasUse[10] = UVal: 0
//   DryerGasUse[11] = UVal: 0
//   DryerGasUse[12] = UVal: 0
//   DryerGasUse[13] = UVal: 0
//   DryerGasUse[14] = UVal: 0
//   HtgElecUse[1] = UVal: 156.346
//   HtgElecUse[2] = UVal: 106.643
//   HtgElecUse[3] = UVal: 4.48889
//   HtgElecUse[4] = UVal: 13.8163
//   HtgElecUse[5] = UVal: 0
//   HtgElecUse[6] = UVal: 0
//   HtgElecUse[7] = UVal: 0
//   HtgElecUse[8] = UVal: 0
//   HtgElecUse[9] = UVal: 0
//   HtgElecUse[10] = UVal: 0.829458
//   HtgElecUse[11] = UVal: 38.3426
//   HtgElecUse[12] = UVal: 168.104
//   HtgElecUse[13] = UVal: 488.57
//   HtgElecUse[14] = UVal: 1.33855
//   HtgGasUse[1] = UVal: 0
//   HtgGasUse[2] = UVal: 0
//   HtgGasUse[3] = UVal: 0
//   HtgGasUse[4] = UVal: 0
//   HtgGasUse[5] = UVal: 0
//   HtgGasUse[6] = UVal: 0
//   HtgGasUse[7] = UVal: 0
//   HtgGasUse[8] = UVal: 0
//   HtgGasUse[9] = UVal: 0
//   HtgGasUse[10] = UVal: 0
//   HtgGasUse[11] = UVal: 0
//   HtgGasUse[12] = UVal: 0
//   HtgGasUse[13] = UVal: 0
//   HtgGasUse[14] = UVal: 0
//   IAQVentElecUse[1] = UVal: 24.5076
//   IAQVentElecUse[2] = UVal: 22.1359
//   IAQVentElecUse[3] = UVal: 24.5076
//   IAQVentElecUse[4] = UVal: 23.717
//   IAQVentElecUse[5] = UVal: 24.5076
//   IAQVentElecUse[6] = UVal: 23.717
//   IAQVentElecUse[7] = UVal: 24.5076
//   IAQVentElecUse[8] = UVal: 24.5076
//   IAQVentElecUse[9] = UVal: 23.717
//   IAQVentElecUse[10] = UVal: 24.5076
//   IAQVentElecUse[11] = UVal: 23.717
//   IAQVentElecUse[12] = UVal: 24.5076
//   IAQVentElecUse[13] = UVal: 288.557
//   IAQVentElecUse[14] = UVal: 0.790567
//   LtgElecUse[1] = UVal: 30.309
//   LtgElecUse[2] = UVal: 25.5355
//   LtgElecUse[3] = UVal: 25.9841
//   LtgElecUse[4] = UVal: 22.9211
//   LtgElecUse[5] = UVal: 21.3938
//   LtgElecUse[6] = UVal: 19.7189
//   LtgElecUse[7] = UVal: 20.8863
//   LtgElecUse[8] = UVal: 22.4153
//   LtgElecUse[9] = UVal: 24.1569
//   LtgElecUse[10] = UVal: 27.2543
//   LtgElecUse[11] = UVal: 28.5842
//   LtgElecUse[12] = UVal: 30.5637
//   LtgElecUse[13] = UVal: 299.723
//   LtgElecUse[14] = UVal: 0.821159
//   PlugLdsElecUse[1] = UVal: 159.244
//   PlugLdsElecUse[2] = UVal: 132.572
//   PlugLdsElecUse[3] = UVal: 140.904
//   PlugLdsElecUse[4] = UVal: 133.674
//   PlugLdsElecUse[5] = UVal: 129.534
//   PlugLdsElecUse[6] = UVal: 120.328
//   PlugLdsElecUse[7] = UVal: 129.633
//   PlugLdsElecUse[8] = UVal: 134.393
//   PlugLdsElecUse[9] = UVal: 137.098
//   PlugLdsElecUse[10] = UVal: 150.545
//   PlugLdsElecUse[11] = UVal: 151.69
//   PlugLdsElecUse[12] = UVal: 160.859
//   PlugLdsElecUse[13] = UVal: 1680.47
//   PlugLdsElecUse[14] = UVal: 4.60403
//   RfrgElecUse[1] = UVal: 38.5306
//   RfrgElecUse[2] = UVal: 34.9586
//   RfrgElecUse[3] = UVal: 40.6822
//   RfrgElecUse[4] = UVal: 38.9557
//   RfrgElecUse[5] = UVal: 42.1271
//   RfrgElecUse[6] = UVal: 43.3674
//   RfrgElecUse[7] = UVal: 45.1996
//   RfrgElecUse[8] = UVal: 45.7174
//   RfrgElecUse[9] = UVal: 43.1302
//   RfrgElecUse[10] = UVal: 42.6618
//   RfrgElecUse[11] = UVal: 38.6775
//   RfrgElecUse[12] = UVal: 38.486
//   RfrgElecUse[13] = UVal: 492.494
//   RfrgElecUse[14] = UVal: 1.3493
//   WashElecUse[1] = UVal: 8.20571
//   WashElecUse[2] = UVal: 8.2709
//   WashElecUse[3] = UVal: 7.04294
//   WashElecUse[4] = UVal: 7.23677
//   WashElecUse[5] = UVal: 7.81781
//   WashElecUse[6] = UVal: 7.30125
//   WashElecUse[7] = UVal: 8.14128
//   WashElecUse[8] = UVal: 9.69179
//   WashElecUse[9] = UVal: 7.43057
//   WashElecUse[10] = UVal: 7.68898
//   WashElecUse[11] = UVal: 7.43068
//   WashElecUse[12] = UVal: 7.6242
//   WashElecUse[13] = UVal: 93.8829
//   WashElecUse[14] = UVal: 0.257213
//   PVSysElecUse[1] = UVal: -286.122
//   PVSysElecUse[2] = UVal: -479.759
//   PVSysElecUse[3] = UVal: -619.557
//   PVSysElecUse[4] = UVal: -756.433
//   PVSysElecUse[5] = UVal: -892.696
//   PVSysElecUse[6] = UVal: -834.838
//   PVSysElecUse[7] = UVal: -910.395
//   PVSysElecUse[8] = UVal: -871.47
//   PVSysElecUse[9] = UVal: -771.253
//   PVSysElecUse[10] = UVal: -624.246
//   PVSysElecUse[11] = UVal: -456.289
//   PVSysElecUse[12] = UVal: -316.085
//   PVSysElecUse[13] = UVal: -7819.14
//   PVSysElecUse[14] = UVal: -21.4223
//   TotalElecUse[1] = UVal: 347.68
//   TotalElecUse[2] = UVal: 44.7484
//   TotalElecUse[3] = UVal: -200.095
//   TotalElecUse[4] = UVal: -341.027
//   TotalElecUse[5] = UVal: -487.884
//   TotalElecUse[6] = UVal: -424.289
//   TotalElecUse[7] = UVal: -450.228
//   TotalElecUse[8] = UVal: -383.778
//   TotalElecUse[9] = UVal: -360.417
//   TotalElecUse[10] = UVal: -202.069
//   TotalElecUse[11] = UVal: -1.17568
//   TotalElecUse[12] = UVal: 321.775
//   TotalElecUse[13] = UVal: -2136.76
//   TotalElecUse[14] = UVal: -5.85413
//   TotalGasUse[1] = UVal: 0
//   TotalGasUse[2] = UVal: 0
//   TotalGasUse[3] = UVal: 0
//   TotalGasUse[4] = UVal: 0
//   TotalGasUse[5] = UVal: 0
//   TotalGasUse[6] = UVal: 0
//   TotalGasUse[7] = UVal: 0
//   TotalGasUse[8] = UVal: 0
//   TotalGasUse[9] = UVal: 0
//   TotalGasUse[10] = UVal: 0
//   TotalGasUse[11] = UVal: 0
//   TotalGasUse[12] = UVal: 0
//   TotalGasUse[13] = UVal: 0
//   TotalGasUse[14] = UVal: 0
//   BillingElecUse[1] = UVal: 347.68
//   BillingElecUse[2] = UVal: 44.7484
//   BillingElecUse[3] = UVal: -200.095
//   BillingElecUse[4] = UVal: -341.027
//   BillingElecUse[5] = UVal: -487.884
//   BillingElecUse[6] = UVal: -424.289
//   BillingElecUse[7] = UVal: -450.228
//   BillingElecUse[8] = UVal: -383.778
//   BillingElecUse[9] = UVal: -360.417
//   BillingElecUse[10] = UVal: -202.069
//   BillingElecUse[11] = UVal: -1.17568
//   BillingElecUse[12] = UVal: 321.775
//   BillingElecUse[13] = UVal: -2136.76
//   BillingElecUse[14] = UVal: -5.85413
//   WaterUse[1] = UVal: 6045
//   WaterUse[2] = UVal: 5460
//   WaterUse[3] = UVal: 6045
//   WaterUse[4] = UVal: 5850
//   WaterUse[5] = UVal: 6045
//   WaterUse[6] = UVal: 5850
//   WaterUse[7] = UVal: 6045
//   WaterUse[8] = UVal: 6045
//   WaterUse[9] = UVal: 5850
//   WaterUse[10] = UVal: 6045
//   WaterUse[11] = UVal: 5850
//   WaterUse[12] = UVal: 6045
//   WaterUse[13] = UVal: 71175
//   WaterUse[14] = UVal: 195






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
   iCurY -= 13;
   tw1 = HPDF_Page_TextWidth (page, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-tw1, iCurY, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_EndText (page);


   iCurX = 520;
   iCurY -= 18;
   QString qsSoftwareVersion, qsCompManagerVersion;
   HPDF_Page_SetFontAndSize (page, font, 8);      // SAC 10/30/22
   QString qsLabel, qsLabel2, qsLabel3;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
      qsSoftwareVersion = qsLabel;
   }

   iCurY -= 13;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
      qsCompManagerVersion = qsLabel;
   }


   iCurX = iPgLeft;             // address, signature blocks, proj ID, date, ... - SAC 11/11/22
   iCurY -= 25;
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
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 1], "Natural Gas"  );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 2], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 3], "Natural Gas"  );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 4], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 5], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 6], "Natural Gas"  );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 7], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 8], "Electric"     );
   HPDF_Page_TextOut (page, iCurX + iLblXMarg, iaAllowY[ 9], "Natural Gas"  );
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
   for (iRow=0; iRow < 10; iRow++)
   {  switch (iRow)
      {  case  0 :  qsLabel = "Software Version:";       qsLabel2 = qsSoftwareVersion;   break;
         case  1 :  qsLabel = "Calculation Engine:";     qsLabel2 = qsCompManagerVersion;   break;
         case  2 :  qsLabel = "Printed Timestamp:";      qsLabel2 = qsRunDateFmt;   break;
         case  3 :  qsLabel = "Project Name:";           BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:Name"          ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  4 :  qsLabel = "Site Street Address:";    qsLabel2 = qsAddCityStZip;  break;
         case  5 :  qsLabel = "Site Contact:";           BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ContactName"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  6 :  qsLabel = "Electric Utility:";       BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecUtility"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  7 :  qsLabel = "Elec. Territory:";        BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTerritory" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  8 :  qsLabel = "Gas Utility:";            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasUtility"    ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         case  9 :  qsLabel = "Gas Territory:";          BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTerritory"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
   //      case  8 :  qsLabel = "Tariff Type:";            BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariff"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
      } 
      HPDF_Page_SetFontAndSize (page, fontBold, 9);
      HPDF_Page_BeginText (page);
      tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, 155-tw1, iCurY - (iTxtLnDY * iRow), qsLabel.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

      HPDF_Page_SetFontAndSize (page, font, 9);
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, 165, iCurY - (iTxtLnDY * iRow), qsLabel2.toLocal8Bit().constData());
      HPDF_Page_EndText (page);

      if (iRow == 5 || iRow == 7 || iRow == 9)
      {  switch (iRow)
         {  case  5 :  qsLabel = "Project Type:";    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:UnitType"   ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
            case  7 :  qsLabel = "Elec. Tariff:";    BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:ElecTariff" ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
            case  9 :  qsLabel = "Gas Tariff:";      BEMPX_GetString( BEMPX_GetDatabaseID( "CUAC:GasTariff"  ), qsLabel2, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx );   break;
         }
         HPDF_Page_SetFontAndSize (page, fontBold, 9);
         HPDF_Page_BeginText (page);
         tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData());
         HPDF_Page_TextOut (page, 465-tw1, iCurY - (iTxtLnDY * iRow), qsLabel.toLocal8Bit().constData());
         HPDF_Page_EndText (page);

         HPDF_Page_SetFontAndSize (page, font, 9);
         HPDF_Page_BeginText (page);
         HPDF_Page_TextOut (page, 475, iCurY - (iTxtLnDY * iRow), qsLabel2.toLocal8Bit().constData());
         HPDF_Page_EndText (page);

         HPDF_Page_MoveTo  (page, 161, iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, 385,      iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_MoveTo  (page, 471, iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, iPgRight, iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_Stroke (page);
      }
      else
      {
         HPDF_Page_MoveTo  (page, 161, iCurY - (iTxtLnDY * iRow)-4 );     HPDF_Page_LineTo  (page, iPgRight, iCurY - (iTxtLnDY * iRow)-4 );
         HPDF_Page_Stroke (page);
      }
   }


   iCurY -= ((iTxtLnDY * 10) + 15);
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   tw1 = HPDF_Page_TextWidth (page, "Utility Allowance Calculator Results");
   HPDF_Page_TextOut (page, iPgCenter-(tw1/2), iCurY, "Utility Allowance Calculator Results");
   HPDF_Page_EndText (page);


   iCurY -= (iTxtLnDY + 10);
   HPDF_Page_SetFontAndSize (page, font, 10);

   HPDF_Page_Rectangle (page, iPgLeft, iCurY, (iPgRight-iPgLeft), 18 );
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


   iCurY -= (((6-lNumUnitTypes) * iRectHt) + 40);     // SAC 12/05/22
   HPDF_Page_SetFontAndSize (page, fontBold, 10);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iPgLeft + 60, iCurY, "I attest that the inputs to the Project Specific Utility Allowance Calculator are accurate.");
   iRectHt = 27;
   int iLeftColX  = iPgLeft + 70;   int iSignColWd = 210;
   int iRightColX = iLeftColX + iSignColWd + 15;
   iCurY -= 25;
   tw1 = HPDF_Page_TextWidth (page, "Energy Consultant");   HPDF_Page_TextOut (page, iLeftColX  + (iSignColWd/2) - (tw1/2), iCurY, "Energy Consultant" );
   tw1 = HPDF_Page_TextWidth (page, "Project Owner"    );   HPDF_Page_TextOut (page, iRightColX + (iSignColWd/2) - (tw1/2), iCurY, "Project Owner"     );
   HPDF_Page_EndText (page);
   iCurY -= 12;

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

