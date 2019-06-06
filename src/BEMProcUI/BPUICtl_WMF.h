// BPUICtl_WMF.H    :  Declare the class for metafiles.
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

#ifndef __BPUICtl_WMF_H__
#define __BPUICtl_WMF_H__


#pragma pack(1)

typedef struct tagOLDRECT
{
    int   left;
    int   top;
    int   right;
    int   bottom;
} OLDRECT;

typedef struct _metafileheader
{
   DWORD  key;
//   HANDLE hmf;
   WORD   hmf;
//   RECT   bbox;
   OLDRECT   bbox;
   WORD   inch;
   DWORD  reserved;
   WORD   checksum;
} METAFILEHEADER;

#pragma pack()


/////////////////////////////////////////////////////////////////////////////

#define HIMETRIC_INCH 2540

BOOL DrawImage(CDC*    pDC,         //Device context
               CString csFile,      //Pathname to image file
               CPoint  ptCenter,    //Center point for image
               HWND    hWnd,        //Handle to view window
               CRect   rectImage);  //Display area rectangle

BOOL GetImageSize(CDC*    pDC,       //Device context
                  LPCTSTR szFile,    //Pathname to image file
                  int*    pnHeight,  //Height to return
                  int*    pnWidth);  //Width to return

BOOL LoadPictureFile(LPCTSTR    szFile,      //Image file pathname
                     LPPICTURE* pgpPicture); //Ptr to PICTURE for image

/////////////////////////////////////////////////////////////////////////////
// CWMFCtl

class CWMFCtl : public CWnd
{
   DECLARE_DYNAMIC( CWMFCtl )
public:

   UINT    m_iItemHelpID;
   UINT    m_iTopicHelpID;

   long    m_lDBID;
   int     m_iDataType;

   CString m_sStatusMsg;

   DWORD   m_dwBckgrndColor;

   BOOL    m_bCalledNew;

protected:

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

public:
   CWMFCtl();
   ~CWMFCtl();

   void SizeAndPos( int iX, int iY, int iWd, int iHt, int winHt, int winWd,
                    BOOL scaleToSysFont, BOOL scaleToScreenRes, CSize& size, CPoint& pos );

   BOOL Create( CWnd* pParentWnd, CBEMPUIControl* pControl, long lDBIDOffset,
                int winHt, int winWd, DWORD dwBckColor, BOOL bTabbedDlgShift=TRUE,
                BOOL scaleToSysFont=TRUE, BOOL scaleToScreenRes=FALSE );

   HMETAFILE RenderMetafile(int fh, METAFILEHEADER* pMetafileHeader);
   CPoint    GetViewportOrigin(CRect winRect, OLDRECT objRect);
   
protected:
   afx_msg LRESULT OnDisplayData(WPARAM, LPARAM);

   afx_msg void OnPaint();

	virtual void PostNcDestroy();

   // SAC 1/29/99 - added for F1 and Shift-F1 (arrow) context help functionality
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif // __BPUICtl_WMF_H__

