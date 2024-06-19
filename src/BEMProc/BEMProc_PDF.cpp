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


int BEMPX_GeneratePDF( const char* pszPDFPathFile, const char* pszRptGraphicsPath, int iPDFID, int iBEMProcIdx )
//int Testing( const char* pszPDFPathFile, int iPDFID, int iBEMProcIdx )
{
   HPDF_Doc  pdf;
   HPDF_Page page;
   //char fname[256];
   HPDF_Font font, fontBold;
   float angle1;
   float angle2;
   float rad1;
   float rad2;
   //HPDF_REAL page_height;
   HPDF_Rect rect;
   int i;

   iPDFID;
   iBEMProcIdx;

// //   const char* SAMP_TXT = "The quick brown fox jumps over the lazy dog. ";
//    //strcpy (fname, argv[0]);
//    //strcat (fname, ".pdf");
//    pdf = HPDF_New (error_handler, NULL);
//    if (!pdf) {
//        printf ("error: cannot create PdfDoc object\n");
//        return 1;
//    }
//    if (setjmp(env)) {
//        HPDF_Free (pdf);
//        return 1;
//    }
//    /* add a new page object. */
//    page = HPDF_AddPage (pdf);
//    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_PORTRAIT);    // letter 612 x 792
//    //page_height = HPDF_Page_GetHeight (page);
// 
// 
//    font = HPDF_GetFont (pdf, "Helvetica", NULL);
//    fontBold = HPDF_GetFont (pdf, "Helvetica-Bold", NULL);
//    HPDF_Page_SetTextLeading (page, 20);
// 
// 
//    /* text_rect method */
//    /* HPDF_TALIGN_LEFT */
//    rect.left = 25;
//    rect.top = 545;
//    rect.right = 200;
//    rect.bottom = rect.top - 40;
// //   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
// //               rect.top - rect.bottom);
// 
//    HPDF_Page_Stroke (page);
//    HPDF_Page_BeginText (page);
// 
//    HPDF_Page_SetFontAndSize (page, fontBold, 6);
//    //HPDF_Page_TextOut (page, rect.left, rect.top + 3, "STATE OF CALIFORNIA");
//    HPDF_Page_TextOut (page, 40, 730, "STATE OF CALIFORNIA");
// 
//    HPDF_Page_SetFontAndSize (page, fontBold, 10);
//    //HPDF_Page_TextOut (page, rect.left, rect.top + 3, "STATE OF CALIFORNIA");
//    HPDF_Page_TextOut (page, 40, 710, "CALIFORNIA ENERGY COMMISSION");
// //   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
// //               SAMP_TXT, HPDF_TALIGN_LEFT, NULL);


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
   //HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
   HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_PORTRAIT);

//   print_grid  (pdf, page);
   //page_height = HPDF_Page_GetHeight (page);

   font     = HPDF_GetFont (pdf, "Helvetica", NULL);
   fontBold = HPDF_GetFont (pdf, "Helvetica-Bold", NULL);

   int iPgTop = HPDF_Page_GetHeight (page);
   int iCurY = iPgTop, iCurX = 50;

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
   HPDF_Page_TextOut (page, iCurX, iCurY, "Draft Submittal Report");
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
      rect.right = 560;
      rect.bottom = iCurY-2;
      HPDF_Page_SetFontAndSize (page, fontBold, 8);
      tw1 = HPDF_Page_TextWidth (page, qsRunDateFmt.toLocal8Bit().constData());
      tw2 = HPDF_Page_TextWidth (page, "Page 1 of 3");
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, 505-(tw1/2), iCurY,    qsRunDateFmt.toLocal8Bit().constData());
      HPDF_Page_TextOut (page, 505-(tw2/2), iCurY-12, "Page 1 of 3");
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
   tw1 = HPDF_Page_TextWidth (page, "Draft Submittal" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-(tw1/2), iCurY, "Draft Submittal" );
   HPDF_Page_EndText (page);




   iCurX = 520;
   iCurY = 672;
   HPDF_Page_SetFontAndSize (page, fontBold, 10);     // SAC 10/30/22
   tw1 = HPDF_Page_TextWidth (page, "Generated by TCAC Approved" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-tw1, iCurY, "Generated by TCAC Approved" );
   HPDF_Page_EndText (page);


   iCurX = 560;
   iCurY -= 13;
   tw1 = HPDF_Page_TextWidth (page, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, iCurX-tw1, iCurY, "California Utility Allowance Calculator (CUAC)" );
   HPDF_Page_EndText (page);



   iCurX = 520;
   iCurY -= 18;
   HPDF_Page_SetFontAndSize (page, font, 8);      // SAC 10/30/22
   QString qsLabel;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:SoftwareVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
   }

   iCurY -= 13;
   if (BEMPX_GetString( BEMPX_GetDatabaseID( "Proj:CompManagerVersion" ), qsLabel, FALSE, 0, -1, 0, BEMO_User, NULL, 0, iBEMProcIdx ) && !qsLabel.isEmpty())
   {  tw1 = HPDF_Page_TextWidth (page, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_BeginText (page);
      HPDF_Page_TextOut (page, iCurX-tw1, iCurY, qsLabel.toLocal8Bit().constData() );
      HPDF_Page_EndText (page);
   }





   HPDF_Page_SetFontAndSize (page, fontBold, 24);
   HPDF_Page_BeginText (page);
   HPDF_Page_TextOut (page, 150, 450, "Report Under Development");
   HPDF_Page_EndText (page);




//    HPDF_Page_SetTextLeading (page, 20);
// 
//    /* text_rect method */
//    /* HPDF_TALIGN_LEFT */
//    rect.left = 25;
//    rect.top = 545;
//    rect.right = 200;
//    rect.bottom = rect.top - 40;
// //   HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left, rect.top - rect.bottom);   // REQUIRED
// 
//    HPDF_Page_Stroke (page);
//    HPDF_Page_BeginText (page);
//    HPDF_Page_SetFontAndSize (page, font, 10);
//    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_LEFT");
// //   HPDF_Page_SetFontAndSize (page, font, 13);
// //   HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
// //               SAMP_TXT, HPDF_TALIGN_LEFT, NULL);
//    HPDF_Page_EndText (page);




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
    HPDF_Page_SetGrayStroke (page, 0.8);

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

            HPDF_Page_SetGrayStroke (page, 0.8);
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

            HPDF_Page_SetGrayStroke (page, 0.8);
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

