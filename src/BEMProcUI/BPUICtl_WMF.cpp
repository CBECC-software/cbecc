// BPUICtl_WMF.CPP  :  Contains CWMFCtl routines
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
#include "resource.h"
#include "BEMProcUI_Globals.h"
#include "..\BEMProc\BEMProc.h"
#include "Screens.h"
#include "BPUICtl_WMF.h" 
#include "memLkRpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC( CWMFCtl, CWnd )

/////////////////////////////////////////////////////////////////////////////
// CWMFCtl

BEGIN_MESSAGE_MAP(CWMFCtl, CWnd)

   ON_MESSAGE(WM_DISPLAYDATA, OnDisplayData)
   ON_WM_PAINT()

	ON_WM_HELPINFO()

END_MESSAGE_MAP()


CWMFCtl::CWMFCtl()
	: CWnd()
{
	//{{AFX_DATA_INIT(CWMFCtl)
	//}}AFX_DATA_INIT
   m_bCalledNew = FALSE;
}


CWMFCtl::~CWMFCtl()
{
}


void CWMFCtl::SizeAndPos( int iX, int iY, int iWd, int iHt, int winHt, int winWd,
                              BOOL scaleToSysFont, BOOL scaleToScreenRes, CSize& size, CPoint& pos )
{
   double dScale = (scaleToScreenRes ? __min(appXRatio,appYRatio) : 1.0);
   
   int sizeX = (int)((double) iWd * dScale);
   int sizeY = (int)((double) iHt * dScale);
   
   int x = (int)((double) iX * dScale);
   int y = (int)((double) iY * dScale);
   
   if (iWd < 0)
   {
      sizeX = abs( sizeX );
      x += ((winWd - sizeX) / 2);
   }
   if (iHt < 0)
   {
      sizeY = abs( sizeY );
      y += ((winHt - sizeY) / 2);
   }
   
   if (scaleToSysFont)
   {
      sizeX = FontX( sizeX );
      sizeY = FontY( sizeY );
      x     = FontX( x );
      y     = FontY( y );
   }

   x = __max( 2, x );
   y = __max( 2, y );

   if ( ((x + sizeX) > (winWd-2)) ||   // if picture is going to exceed window
        ((y + sizeY) > (winHt-2)) )    // dimensions, then scale it until it won't
   {
      double d2XScale = ((double) (winWd-2 - x)) / ((double) sizeX);
      double d2YScale = ((double) (winHt-2 - y)) / ((double) sizeY);

      double d2Scale = __min( d2XScale, d2YScale );

      sizeX = (int) ((double) sizeX * d2Scale);
      sizeY = (int) ((double) sizeY * d2Scale);
   }

   size.cx = sizeX;         
   size.cy = sizeY;         
   pos.x   = x;
   pos.y   = y;
}


BOOL CWMFCtl::Create( CWnd* pParentWnd, CBEMPUIControl* pControl, long lDBIDOffset,
                          int winHt, int winWd, DWORD dwBckColor, BOOL bTabbedDlgShift,
                          BOOL scaleToSysFont, BOOL scaleToScreenRes )
{
// SAC - 8/25/98
//   DWORD winStyle = WS_CHILD|WS_VISIBLE|WS_BORDER;
   DWORD winStyle = WS_CHILD|WS_BORDER;

   CSize size;
   CPoint pos;
   SizeAndPos( pControl->m_iX, pControl->m_iY, pControl->m_iWidth, pControl->m_iHeight,
               winHt, winWd, scaleToSysFont, scaleToScreenRes, size, pos );

   if (bTabbedDlgShift)
   {  // shift for Win95 tabbed dialog class
      pos.x += eiTabDlgCtrlMarg;
      pos.y += eiTabDlgCtrlDY + eiTabDlgCtrlMarg;
   }

   BOOL retVal = CWnd::CreateEx( WS_EX_CLIENTEDGE, NULL, pControl->m_sLbl, winStyle, CRect(pos, size),
                                 pParentWnd, pControl->m_uiCtrlID );
   if (retVal)
   {
      m_lDBID      	= pControl->m_lDBID + lDBIDOffset;
      m_sStatusMsg 	= pControl->m_sStatusMsg;

      ASSERT( pControl->m_iDBInstance < 0 );  // SAC 3/3/99 - not yet implemented for this control type

      m_iDataType   	= BEMPX_GetDataType(  m_lDBID );
      m_iItemHelpID  = BEMPX_GetItemHelpID(  m_lDBID );
      m_iTopicHelpID = BEMPX_GetTopicHelpID( m_lDBID );

      m_dwBckgrndColor = dwBckColor;
      m_bCalledNew = TRUE;
   }
   return retVal;
}


void CWMFCtl::PostNcDestroy()
{
	if (m_bCalledNew)
		delete this;
}


/////////////////////////////////////////////////////////////////////////////
// CWMFCtl diagnostics

#ifdef _DEBUG
void CWMFCtl::AssertValid() const
{
	CWnd::AssertValid();
}

void CWMFCtl::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CWMFCtl OnDisplayData()

LONG CWMFCtl::OnDisplayData(UINT, LONG)
{
   RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
   return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CWMFCtl Painting

static char BASED_CODE szErrWmfNA[] = "Drawing Not Available";
static char BASED_CODE szErrWmf[] = "Metafile File Not Found:";

void CWMFCtl::OnPaint()
{
   CString sBEMFN;
   int iStatus = BEMPX_GetDataStatus( m_lDBID );
   if ( (iStatus > BEMS_Undefined) && (iStatus < BEMS_NumTypes) )
   {
      int iError, iSpecialVal;
		QString qsBEMFN = BEMPX_GetString( m_lDBID, iSpecialVal, iError );
		if (iError >= 0)
         sBEMFN = qsBEMFN.toLatin1().constData();
   }

   CString fileName;
   BOOL bFileNameLoaded = TRUE;
   if (sBEMFN.GetLength() < 4)
      bFileNameLoaded = FALSE;
   else
   {
      fileName = esGraphicsPath;
      fileName += sBEMFN;
   }

   if (bFileNameLoaded && FileExists(fileName))
   {
      CRect rect;
      GetWindowRect( &rect );

   	CWaitCursor wait;

   	CPaintDC dc(this);

      CRect tempRect;
      GetClientRect( tempRect );
      dc.SetBkColor( m_dwBckgrndColor );
      dc.ExtTextOut( 8, 0, ETO_OPAQUE, tempRect, " ", 1, NULL);

		if (fileName.Right(3).CompareNoCase("WMF"))
		{	// NOT a WMF file, so use new OleLoadPicture method
			VERIFY( DrawImage( &dc, fileName, CPoint( rect.Width()/2, rect.Height()/2 )/*Center point for image*/,
										GetSafeHwnd(), tempRect /*Display area rectangle*/ ) );
		}
		else
		{
	      OFSTRUCT of;
	      METAFILEHEADER metafileHeader;
	      unsigned fh = OpenFile ( fileName, (LPOFSTRUCT)&of, OF_READ );
	    
	      HMETAFILE hmf = RenderMetafile(fh, &metafileHeader);
	    
	      ScreenToClient(&rect);
	      CPoint origin = GetViewportOrigin(rect, metafileHeader.bbox);
	      
	      dc.SetMapMode(MM_ISOTROPIC);
	      dc.SetWindowExt(rect.Width(), rect.Height());
	      dc.SetViewportExt(rect.Width(), rect.Height());
	      dc.SetViewportOrg(origin.x, origin.y);
	    
	      dc.PlayMetaFile(hmf);
	      DeleteMetaFile(hmf);
		}
   }
   else
   {
      CPaintDC dc(this);

      // Erase screen
      CRect rect;
      GetWindowRect( &rect );

      dc.FillRect( CRect(0,0,rect.Width(),rect.Height()), &buttonBrush );
      dc.SetBkMode( TRANSPARENT );
      dc.SetTextColor(RGB(0, 0, 0));
      dc.SelectObject( GetWizFont( FNT_STD ) );
      dc.SetTextAlign( TA_CENTER | TA_TOP );

      int iX = rect.Width()/2;
      int iFontHt = GetWizFontHeight( FNT_STD ) + 4;
      int iY = (rect.Height()/2) - iFontHt;

      CString sErr;
      if (!bFileNameLoaded)
         sErr = szErrWmfNA;
      else
         sErr = szErrWmf;

      dc.TextOut( iX, iY, sErr );
      fileName.MakeLower();
      dc.TextOut( iX, iY+iFontHt, fileName );
   }
}


HMETAFILE CWMFCtl::RenderMetafile(int fh, METAFILEHEADER* pMetafileHeader)
{   
   ///////////////////////////////////////////////////////////////////////////       
   // This function creates a memory-based Windows metafile from a placeable 
   // metafile that will work with the metafile functions provided by Windows. 
   ///////////////////////////////////////////////////////////////////////////       
   HMETAFILE      hmf;
   HANDLE         hData;
   LPSTR          lpData;
   DWORD          offsetToMeta;
   METAHEADER     mfHeader;
   
   offsetToMeta = sizeof(METAFILEHEADER);
   
   // Seek to beginning of the file and read the placeable metafile header.
   _llseek(fh, 0, 0);
   if (!_lread(fh, (LPSTR)pMetafileHeader, sizeof(METAFILEHEADER)))
      // Error in reading the file
      return FALSE;
      
   // Return to read metafile header.
   _llseek(fh, offsetToMeta, 0);
   if ((!_lread(fh, (LPSTR)&mfHeader, sizeof(METAHEADER))))
      // Error in reading
      return FALSE;
         
   // Allocate memory for memory based metafile
	hData = GlobalAlloc(GHND, (mfHeader.mtSize * 2L));
   if (!hData)      
      return FALSE;
         
   // Were we successful?
	lpData = (char*)GlobalLock(hData);
   if (!lpData)         
   {
      // Error in allocation
      GlobalFree(hData);
      return FALSE;
   }
   
   // Read metafile bits
   _llseek(fh, offsetToMeta, 0);
   if (!_lread(fh, lpData,(UINT)(mfHeader.mtSize * 2L)))
   {
      // Error in reading
      GlobalUnlock(hData);
      GlobalFree(hData);
      return FALSE;
   }
   
   // Create the metafile with the bits we read in.
   DWORD dwSize = GlobalSize(hData);
	hmf = SetMetaFileBitsEx( dwSize, (CONST BYTE*) lpData );
   if (!hmf)
      return FALSE;
      
   GlobalUnlock(hData);
   
   // Close the file
   _lclose(fh);   
   
   return hmf;
}   


CPoint CWMFCtl::GetViewportOrigin(CRect winRect, OLDRECT objRect)
{
   CPoint origin;
   float objHtWd = ((float)objRect.bottom - (float)objRect.top) / ((float)objRect.right - (float)objRect.left);
   float winHtWd = (float)winRect.Height() / (float)winRect.Width();
   
   if (objHtWd > winHtWd)
   {
      origin.x = (int)((float)winRect.left + (((float)winRect.Width() - ((float)winRect.Height() / objHtWd)) / 2));
      origin.y = winRect.top;
   }
   else
   {
      origin.x = winRect.left;
      origin.y = (int)((float)winRect.top + ((float)(winRect.Height() - ((float)winRect.Width() * objHtWd)) / 2));
   }
   return origin;
}   


/////////////////////////////////////////////////////////////////////////////
// SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality

BOOL CWMFCtl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
// SAC 10/16/02 - Added code to prevent calling help system for help IDs of 0
   if (m_iItemHelpID <= 0)
      return FALSE;

   GetParent()->SendMessage( WM_SETCONTEXTHELPID, m_iItemHelpID );
	
   return CWnd::OnHelpInfo(pHelpInfo);
}

/////////////////////////////////////////////////////////////////////////////
// JPG and other image display

BOOL DrawImage(CDC*    pDC,
               CString csFile,
               CPoint  ptCenter,
               HWND    hWnd,
               CRect   rectImage)
{
    if (pDC == NULL || csFile.IsEmpty() || hWnd == NULL)
        return FALSE;
    
    LPPICTURE gpPicture = NULL;
        
    if (LoadPictureFile((LPCTSTR)csFile,&gpPicture))
    {
        //Get width and height of picture
        long hmWidth  = 0;
        long hmHeight = 0;

        gpPicture->get_Width (&hmWidth);
        gpPicture->get_Height(&hmHeight);

        //Use to get height and width for display
        CRect rectI = rectImage;
        rectI.NormalizeRect();

        int nWidth = rectI.Width();
        int nHeight= rectI.Height();

        CPoint ptUL(ptCenter.x-(nWidth /2),
                    ptCenter.y+(nHeight/2));

		RECT rc;
		GetClientRect(hWnd, &rc);

        HRESULT hrP = NULL;
        
        hrP =
        gpPicture->Render(pDC->m_hDC,
                          ptUL.x,
                          ptUL.y,
                          nWidth,
                          -nHeight,
                          0,
                          0,          // hmHeight,
                          hmWidth,
                          hmHeight,   // -hmHeight,
                          &rc);

        gpPicture->Release();

        if (SUCCEEDED(hrP))
            return TRUE;
    }

    return FALSE;
}


BOOL GetImageSize(CDC*       pDC,
                  LPCTSTR    szFile,
                  int*       pnHeight,
                  int*       pnWidth)
{
    LPPICTURE gpPicture = NULL;

    if (!LoadPictureFile(szFile,&gpPicture))
        return FALSE;

    //Get width and height of picture
    long hmWidth  = 0;
    long hmHeight = 0;

    gpPicture->get_Width (&hmWidth);
    gpPicture->get_Height(&hmHeight);

    int nPixX = pDC->GetDeviceCaps(LOGPIXELSX);
    int nPixY = pDC->GetDeviceCaps(LOGPIXELSY);

    //For printers, pixels per inch is really DPI, so be careful!
    if (pDC->IsPrinting())
    {
		nPixX = 96;
        nPixY = 96;
    }

    //Convert to device units
    *pnWidth  = MulDiv(hmWidth,  nPixX, HIMETRIC_INCH);
    *pnHeight = MulDiv(hmHeight, nPixY, HIMETRIC_INCH);

    return TRUE;
}


BOOL LoadPictureFile(LPCTSTR    szFile,
                     LPPICTURE* pgpPicture)
{
    // open file
    HANDLE hFile = CreateFile(szFile,
                              GENERIC_READ,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              0,
                              NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        BEMMessageBox ("Could not read file");
        return FALSE;
    }

    // get file size
    DWORD dwFileSize = GetFileSize(hFile, NULL);

    if (dwFileSize == (DWORD)-1)
    {
        CloseHandle(hFile);
        BEMMessageBox ("File seems to be empty");
        return FALSE;
    }

    LPVOID pvData = NULL;

    // alloc memory based on file size
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);

    if (hGlobal == NULL)
    {
        CloseHandle(hFile);
        BEMMessageBox ("Could not allocate memory for image");
        return FALSE;
    }

    pvData = GlobalLock(hGlobal);

    if (pvData == NULL)
    {
        GlobalUnlock(hGlobal);
        CloseHandle(hFile);
        BEMMessageBox ("Could not lock memory for image");
        return FALSE;
    }

    DWORD dwBytesRead = 0;

    // read file and store in global memory
    BOOL bRead = ReadFile(hFile,
                          pvData,
                          dwFileSize,
                          &dwBytesRead,
                          NULL);

    GlobalUnlock(hGlobal);
    CloseHandle(hFile);

    if (!bRead)
    {
        BEMMessageBox ("Could not read file");
        return FALSE;
    }

    LPSTREAM pstm = NULL;

    // create IStream* from global memory
    HRESULT hr = CreateStreamOnHGlobal(hGlobal,
                                       TRUE,
                                       &pstm);

    if (!(SUCCEEDED(hr)))
    {
        BEMMessageBox ("CreateStreamOnHGlobal() failed");

        if (pstm != NULL)
            pstm->Release();
            
        return FALSE;
    }

    else if (pstm == NULL)
    {
        BEMMessageBox ("CreateStreamOnHGlobal() failed");
        return FALSE;
    }

	// Create IPicture from image file
	if (*pgpPicture)
		(*pgpPicture)->Release();

    hr = ::OleLoadPicture(pstm,
                          dwFileSize,
                          FALSE,
                          IID_IPicture,
                          (LPVOID *)&(*pgpPicture));

    if (!(SUCCEEDED(hr)))
    {
    	pstm->Release();
        BEMMessageBox("Could not load image (hr failure)");
        return FALSE;
    }

    else if (*pgpPicture == NULL)
    {
    	pstm->Release();
        BEMMessageBox("Could not load image (pgpPicture failure)");
        return FALSE;
    }

    pstm->Release();

    return TRUE;  //Made it ...!
}

