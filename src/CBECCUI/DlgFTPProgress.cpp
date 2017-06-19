// DlgFTPProgress.cpp : implementation file
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
#include "ComplianceUI.h"
#include "DlgFTPProgress.h"
#include "CUIGlobl.h"

#include <direct.h>
#include <stdio.h>
#include <io.h>
#include <lzexpand.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// various .INI file section and entry strings
static char BASED_CODE szPaths[]   = "paths";
static char BASED_CODE szOptions[] = "options";
static char BASED_CODE szSDSI[]    = "StoreDesignSimInput";
static char BASED_CODE szSDSO[]    = "StoreDesignSimOutput";
static char BASED_CODE szSASI[]    = "StoreAnnualSimInput";
static char BASED_CODE szSASO[]    = "StoreAnnualSimOutput";


static char BASED_CODE szBS01[] = "Finding resource...";
static char BASED_CODE szBS02[] = "Connecting...";
static char BASED_CODE szBS03[] = "Redirecting...";
static char BASED_CODE szBS04[] = "Begin download data";
static char BASED_CODE szBS05[] = "Downloading data...";
static char BASED_CODE szBS06[] = "End download data";
static char BASED_CODE szBS07[] = "Begin download components";
static char BASED_CODE szBS08[] = "Installing components...";
static char BASED_CODE szBS09[] = "End download components";
static char BASED_CODE szBS10[] = "Using cached copy...";
static char BASED_CODE szBS11[] = "Sending request...";
static char BASED_CODE szBS12[] = "Class ID available";
static char BASED_CODE szBS13[] = "MIME type available";
static char BASED_CODE szBS14[] = "Cache filename available";
static char BASED_CODE szBS15[] = "Begin sync operation";
static char BASED_CODE szBS16[] = "End sync operation";
static char BASED_CODE szBS17[] = "Begin upload data";
static char BASED_CODE szBS18[] = "Uploading data...";
static char BASED_CODE szBS19[] = "End upload data";
static char BASED_CODE szBS20[] = "Protocol class ID";
static char BASED_CODE szBS21[] = "Encoding...";
static char BASED_CODE szBS22[] = "Verfied MIME type available";
static char BASED_CODE szBS23[] = "Class install location";
static char BASED_CODE szBS24[] = "Decoding...";
static char BASED_CODE szBS25[] = "???";

static char* pszBindStatus[] = { szBS01, szBS02, szBS03, szBS04, szBS05, szBS06, szBS07, szBS08, szBS09, szBS10,
                                 szBS11, szBS12, szBS13, szBS14, szBS15, szBS16, szBS17, szBS18, szBS19, szBS20,
                                 szBS21, szBS22, szBS23, szBS24, szBS25 };


//static CDlgFTPProgress* spAnalDlg = NULL;

//long CALLBACK EXPORT UpdateDialog( BOOL bUpdateMsgs, const char* pszMsg1, const char* pszMsg2, int iProgress )
//{
//   ASSERT( spAnalDlg );
//   if (bUpdateMsgs)
//   {
//   	spAnalDlg->m_sMessage1 = pszMsg1;
//   	spAnalDlg->m_sMessage2 = pszMsg2;
//      spAnalDlg->UpdateData( FALSE );
//   }
//
//   if (iProgress != spAnalDlg->m_iCurrentProgress)
//   {
//      spAnalDlg->m_iCurrentProgress = iProgress;
//      spAnalDlg->m_pcProgress.SetPos( spAnalDlg->m_iCurrentProgress );
//   }
//
//   spAnalDlg->ProcessMessages();
//
//   return (spAnalDlg->m_bAbort) ? 1 : 0;
//}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CBSCallbackImpl

CBSCallbackImpl::CBSCallbackImpl(HWND hWnd, HANDLE hEventStop)
{
	m_hWnd = hWnd;  // the window handle to display status

	m_hEventStop = hEventStop;  // the event object to signal to stop

	m_ulObjRefCount = 1;
}

STDMETHODIMP CBSCallbackImpl::QueryInterface(REFIID riid, void **ppvObject)
{
	TRACE(_T("IUnknown::QueryInterface\n"));

	*ppvObject = NULL;
	
	// IUnknown
	if (::IsEqualIID(riid, __uuidof(IUnknown)))
	{
		TRACE(_T("IUnknown::QueryInterface(IUnknown)\n"));

		*ppvObject = this;
	}
	// IBindStatusCallback
	else if (::IsEqualIID(riid, __uuidof(IBindStatusCallback)))
	{
		TRACE(_T("IUnknown::QueryInterface(IBindStatusCallback)\n"));

		*ppvObject = static_cast<IBindStatusCallback *>(this);
	}

	if (*ppvObject)
	{
		(*reinterpret_cast<LPUNKNOWN *>(ppvObject))->AddRef();

		return S_OK;
	}
	
	return E_NOINTERFACE;
}                                             

STDMETHODIMP_(ULONG) CBSCallbackImpl::AddRef()
{
	TRACE(_T("IUnknown::AddRef\n"));

	return ++m_ulObjRefCount;
}

STDMETHODIMP_(ULONG) CBSCallbackImpl::Release()
{
	TRACE(_T("IUnknown::Release\n"));

	return --m_ulObjRefCount;
}

STDMETHODIMP CBSCallbackImpl::OnStartBinding(DWORD, IBinding *)
{
	TRACE(_T("IBindStatusCallback::OnStartBinding\n"));

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::GetPriority(LONG *)
{
	TRACE(_T("IBindStatusCallback::GetPriority\n"));

	return E_NOTIMPL;
}

STDMETHODIMP CBSCallbackImpl::OnLowResource(DWORD)
{
	TRACE(_T("IBindStatusCallback::OnLowResource\n"));

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::OnProgress(ULONG ulProgress,
										 ULONG ulProgressMax,
										 ULONG ulStatusCode,
										 LPCWSTR szStatusText)
{
	static const LPCTSTR plpszStatus[] = 
	{
		_T("BINDSTATUS_FINDINGRESOURCE"),  // 1
		_T("BINDSTATUS_CONNECTING"),
		_T("BINDSTATUS_REDIRECTING"),
		_T("BINDSTATUS_BEGINDOWNLOADDATA"),
		_T("BINDSTATUS_DOWNLOADINGDATA"),
		_T("BINDSTATUS_ENDDOWNLOADDATA"),
		_T("BINDSTATUS_BEGINDOWNLOADCOMPONENTS"),
		_T("BINDSTATUS_INSTALLINGCOMPONENTS"),
		_T("BINDSTATUS_ENDDOWNLOADCOMPONENTS"),
		_T("BINDSTATUS_USINGCACHEDCOPY"),
		_T("BINDSTATUS_SENDINGREQUEST"),
		_T("BINDSTATUS_CLASSIDAVAILABLE"),
		_T("BINDSTATUS_MIMETYPEAVAILABLE"),
		_T("BINDSTATUS_CACHEFILENAMEAVAILABLE"),
		_T("BINDSTATUS_BEGINSYNCOPERATION"),
		_T("BINDSTATUS_ENDSYNCOPERATION"),
		_T("BINDSTATUS_BEGINUPLOADDATA"),
		_T("BINDSTATUS_UPLOADINGDATA"),
		_T("BINDSTATUS_ENDUPLOADINGDATA"),
		_T("BINDSTATUS_PROTOCOLCLASSID"),
		_T("BINDSTATUS_ENCODING"),
		_T("BINDSTATUS_VERFIEDMIMETYPEAVAILABLE"),
		_T("BINDSTATUS_CLASSINSTALLLOCATION"),
		_T("BINDSTATUS_DECODING"),
		_T("???")  // unexpected
	};

	TRACE(_T("IBindStatusCallback::OnProgress\n"));

	TRACE(_T("ulProgress: %lu, ulProgressMax: %lu\n"),
		  ulProgress, ulProgressMax);
	
	TRACE(_T("ulStatusCode: %lu "), ulStatusCode);

	if (ulStatusCode < BINDSTATUS_FINDINGRESOURCE ||
		ulStatusCode > BINDSTATUS_DECODING)
		ulStatusCode = BINDSTATUS_DECODING + 1;
	
	TRACE(_T("(%s), szStatusText: %ls\n"),
		  plpszStatus[ulStatusCode - BINDSTATUS_FINDINGRESOURCE],
		  szStatusText);

	if (m_hWnd != NULL)
	{
		// inform the dialog box to display current status,
		// don't use PostMessage
		CDlgFTPProgress::DOWNLOADSTATUS downloadStatus =
			{ ulProgress, ulProgressMax, ulStatusCode, szStatusText };
		::SendMessage(m_hWnd, WM_DISPLAYFTPSTATUS,
					  0, reinterpret_cast<LPARAM>(&downloadStatus));
	}

	if (m_hEventStop != NULL)
	{
		if (::WaitForSingleObject(m_hEventStop, 0) == WAIT_OBJECT_0)
		{
			TRACE(_T("Canceled.\n"));
			::SendMessage(m_hWnd, WM_DISPLAYFTPSTATUS, 0, NULL);
			return E_ABORT;  // canceled by the user
		}
	}

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::OnStopBinding(HRESULT, LPCWSTR)
{
	TRACE(_T("IBindStatusCallback::OnStopBinding\n"));

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::GetBindInfo(DWORD *, BINDINFO *)
{
	TRACE(_T("IBindStatusCallback::GetBindInfo\n"));

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::OnDataAvailable(DWORD, DWORD,
											  FORMATETC *, STGMEDIUM *)
{
	TRACE(_T("IBindStatusCallback::OnDataAvailable\n"));

	return S_OK;
}

STDMETHODIMP CBSCallbackImpl::OnObjectAvailable(REFIID, IUnknown *)
{
	TRACE(_T("IBindStatusCallback::OnObjectAvailable\n"));

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDlgFTPProgress dialog


CDlgFTPProgress::CDlgFTPProgress( const char* pszFTP_URL, const char* pszDestinationFilename,
                                  int iMaxProgressRange, CWnd* pParent /*=NULL*/ )
	: CDialog(CDlgFTPProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFTPProgress)
	m_sMessage1 = _T("Initializing File Download...");
	//}}AFX_DATA_INIT

   m_bDownloadInitiated = FALSE;
   m_iCurrentProgress = -1;
   m_sFTP_URL = pszFTP_URL;
   m_sDestinationFilename = pszDestinationFilename;
   m_iMaxProgressRange = iMaxProgressRange;
	m_pDownloadThread = NULL;
   m_bUserAbort = FALSE;
   m_bDownloadSuccessful = FALSE;
}


void CDlgFTPProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFTPProgress)
	DDX_Control(pDX, IDC_FTPPROGRESS, m_pcProgress);
	DDX_Text(pDX, IDC_MESSAGE1, m_sMessage1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFTPProgress, CDialog)
	//{{AFX_MSG_MAP(CDlgFTPProgress)
	ON_BN_CLICKED(IDC_ABORTFTP, OnAbort)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

   ON_MESSAGE(WM_INITFTPDOWNLOAD, OnInitDownload)
	ON_MESSAGE(WM_ENDFTPDOWNLOAD, OnEndDownload)
	ON_MESSAGE(WM_DISPLAYFTPSTATUS, OnDisplayStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFTPProgress message handlers

BOOL CDlgFTPProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();

   CWnd* pWnd = GetDlgItem( IDC_MESSAGE1 );
   if (pWnd)
      pWnd->SetFont( GetCUIFont(FNT_STD), TRUE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// sent when the downloading thread ends
// wParam and lParam: not used
// return value: not used
LRESULT CDlgFTPProgress::OnEndDownload(WPARAM, LPARAM)
{
	ASSERT(m_pDownloadThread != NULL);
	ASSERT_KINDOF(CWinThread, m_pDownloadThread);

	TRACE(_T("OnEndDownload()\n"));

	// wait until the thread terminates
	DWORD dwExitCode;
	if (::GetExitCodeThread(m_pDownloadThread->m_hThread, &dwExitCode) &&
		dwExitCode == STILL_ACTIVE)
		::WaitForSingleObject(m_pDownloadThread->m_hThread, INFINITE);

	delete m_pDownloadThread;
	m_pDownloadThread = NULL;

	// display the result
	if (m_bUserAbort && m_iCurrentProgress < m_iMaxProgressRange)
      ::AfxMessageBox( "File download aborted by user." );
	else if (m_iCurrentProgress == -1)
		::AfxMessageBox( "Unable to connect to web/FTP site." );
	else if (m_iCurrentProgress == 0 || m_downloadParam.strFileName.IsEmpty())
      ::AfxMessageBox( "File download failed." );
	else if (m_iCurrentProgress > 0 && m_iCurrentProgress < m_iMaxProgressRange)
      ::AfxMessageBox( "File only partially downloaded." );
   else if (!FileExists( m_downloadParam.strFileName ))
      ::AfxMessageBox( "Cache file not found." );
   else if (m_sDestinationFilename.GetLength() <= 0)
      ::AfxMessageBox( "Invalid destination filename." );
   else
   {  // copy cache file into intended name
      OFSTRUCT ofsSrc, ofsDest;
      HFILE    hfSrc , hfDest ;
      hfSrc  = LZOpenFile( (LPTSTR)(LPCTSTR) m_downloadParam.strFileName, &ofsSrc , OF_READ );
      hfDest = LZOpenFile( (LPTSTR)(LPCTSTR) m_sDestinationFilename     , &ofsDest, OF_CREATE );
      if (LZCopy( hfSrc, hfDest ) <= 0)
      {
         AfxMessageBox( "Error encountered copying cache file to desired location." );
         m_bDownloadSuccessful = FALSE;
      }
      LZClose( hfSrc );
      LZClose( hfDest );

      // post success message and set success flag
   	::AfxMessageBox( "File downloaded successfully!", MB_OK | MB_ICONINFORMATION );
      m_bDownloadSuccessful = TRUE;
   }

   if (!m_bDownloadSuccessful && FileExists( m_downloadParam.strFileName ))
   {  // delete cache file if transfer was unsuccessful for any reason
//      CString sErrMsg = "About to delete cache file:  ";
//      sErrMsg += m_downloadParam.strFileName;
//      ::AfxMessageBox( sErrMsg );
      TRY
      {
         CFile::Remove( m_downloadParam.strFileName );
      }
      CATCH( CFileException, e )
      {
         AfxMessageBox( "Error deleting cache file." );
#ifdef _DEBUG
         afxDump << "File " << m_downloadParam.strFileName << " cannot be removed\n";
#endif
      }
      END_CATCH
   }

//	// change the UI
//	this->ChangeUIDownloading(false);
   // Terminate dialog gracefully
   OnOK();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// sent from the downloading thread to the dialog box to display the progress
// wParam: not used
// lParam: DOWNLOADSTATUS *, NULL if canceled
//		   {
//			   ULONG ulProgress - IN
//			   ULONG ulProgressMax - IN
//			   ULONG ulStatusCode - IN
//			   LPCWSTR szStatusText - IN
//		   }
// return value: not used
LRESULT CDlgFTPProgress::OnDisplayStatus(WPARAM, LPARAM lParam)
{
	const DOWNLOADSTATUS *const pDownloadStatus =
		reinterpret_cast<DOWNLOADSTATUS *>(lParam);

	// form the status text
	if (pDownloadStatus != NULL)
	{
		ASSERT(::AfxIsValidAddress(pDownloadStatus, sizeof(DOWNLOADSTATUS)));

//		strStatus.LoadString(pDownloadStatus->ulStatusCode -
//							 BINDSTATUS_FINDINGRESOURCE +
//							 IDS_BINDSTATUS01);
      ASSERT( pDownloadStatus->ulStatusCode > 0 && pDownloadStatus->ulStatusCode <= (BINDSTATUS_DECODING+1) );
		m_sMessage1  = pszBindStatus[ pDownloadStatus->ulStatusCode-1 ];

//		m_sMessage1 += _T("  ");
//		m_sMessage1 += pDownloadStatus->szStatusText;
//
//		CString strProgress;
//		strProgress.Format( "  %lu of %lu",
//						        pDownloadStatus->ulProgress,
//						        m_iMaxProgressRange );
////						        pDownloadStatus->ulProgressMax);
//
////      // SAC 9/4/99 - added code to calculate %done progress specifically geared towards DOE-2 weather files
////      //   only append progress indicator if it is within 105% of done - otherwise, probably NOT downloading a weather file
////      if (pDownloadStatus->ulProgress < (int) (148992 * 1.05))
////      {
////         float fPercentDone = min( 100, (100 * (float) pDownloadStatus->ulProgress / 148992) );
////         CString sPctDone;
////         sPctDone.Format( " - %.1f%% done.", fPercentDone );
////         strProgress += sPctDone;
////      }
//
//		m_sMessage1 += strProgress;

      // SAC 9/7/99 - set progress control
      m_iCurrentProgress = pDownloadStatus->ulProgress;
      m_pcProgress.SetPos( m_iCurrentProgress );
	}
	else
		m_sMessage1 = _T("Canceled.");

   // update dialog static control containing Message1
   UpdateData( FALSE );

//#if 1
//	// place a caret at the end of the text and append the text to the edit box
//	const int nLen = m_editProgress.GetWindowTextLength();
//	m_editProgress.SetSel(nLen, nLen);
//	m_editProgress.ReplaceSel(strStatus);
//#else
//	// retrieve the status text
//	this->UpdateData();
//	
//	// append the text
//	m_strProgress += strStatus;
//
//	// update the edit box
//	this->UpdateData(FALSE);
//#endif

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
LONG CDlgFTPProgress::OnInitDownload(UINT, LONG)
{
   // set progress bar range to 0 - m_iMaxProgressRange
   m_pcProgress.SetRange( 0, m_iMaxProgressRange );

	// check if the URL is valid
	USES_CONVERSION;
	if (m_sFTP_URL.IsEmpty() ||
		::IsValidURL(NULL, T2CW(m_sFTP_URL), 0) != S_OK)
	{
      CString sErrMsg = _T("Invalid FTP URL:  '");
      sErrMsg += m_sFTP_URL;
      sErrMsg += "'";
		::AfxMessageBox( sErrMsg, MB_OK | MB_ICONSTOP );

		// Bail
      OnOK();
		return 0;
	}

	// parameters to be passed to the thread
	m_downloadParam.hWnd = this->GetSafeHwnd();

	m_eventStop.ResetEvent();  // nonsignaled
	m_downloadParam.hEventStop = m_eventStop;

	m_downloadParam.strURL = m_sFTP_URL;

   m_downloadParam.strFileName.Empty();
//   m_downloadParam.strFileName = m_sDestinationFilename;

	// create a thread to download, but don't start yet
	m_pDownloadThread = ::AfxBeginThread(CDlgFTPProgress::Download,
										 &m_downloadParam,
										 THREAD_PRIORITY_NORMAL,
										 0,
										 CREATE_SUSPENDED);
	if (m_pDownloadThread != NULL)
	{
		TRACE(_T("AfxBeginThread: 0x%08lX\n"),
			  m_pDownloadThread->m_nThreadID);

		/* 
			Set the m_bAutoDelete data member to FALSE. This allows
			the CWinThread object to survive after the thread has been
			terminated. You can then access the m_hThread data member
			after the thread has been terminated. If you use this
			technique, however, you are responsible for destroying the
			CWinThread object as the framework will not automatically
			delete it for you.
		*/
		m_pDownloadThread->m_bAutoDelete = FALSE;

//		// change the UI
//		this->ChangeUIDownloading();

		// start
		m_pDownloadThread->ResumeThread();
	}
	else
	{
		::AfxMessageBox( _T("Could not create the thread."), MB_OK | MB_ICONSTOP );

//		// change the UI
//		this->ChangeUIDownloading(false);

		// Bail
      OnOK();
		return 0;
	}

   return 0;
}


/////////////////////////////////////////////////////////////////////////////
void CDlgFTPProgress::ProcessMessages()
{
   // Retrieve and dispatch all messages coming to this window
   MSG msg;
   HWND hWnd = GetSafeHwnd();
   while (::PeekMessage( &msg, hWnd, 0, 0, PM_REMOVE))
   {
      ::TranslateMessage( &msg );
      ::DispatchMessage( &msg );
   }
}


/////////////////////////////////////////////////////////////////////////////
// Exit button, Alt-F4 key, Close menu or Close button
void CDlgFTPProgress::OnCancel()
{
	if (m_pDownloadThread != NULL)
		return;  // Don't exit while downloading
	
	CDialog::OnCancel();
}


/////////////////////////////////////////////////////////////////////////////
void CDlgFTPProgress::OnAbort() 
{
	// Stop
   m_bUserAbort = TRUE;
	m_eventStop.SetEvent();  // signaled
}


/////////////////////////////////////////////////////////////////////////////
void CDlgFTPProgress::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
   if (!m_bDownloadInitiated)
   {
      m_bDownloadInitiated = TRUE;
      PostMessage( WM_INITFTPDOWNLOAD );
   }
}


/////////////////////////////////////////////////////////////////////////////
// static member function - the controlling function for the worker thread
// pParam: DOWNLOADPARAM *
//		   {
//			   HWND hWnd - IN				the window handle to display status
//			   HANDLE hEventStop - IN		the event object to signal to stop
//			   CString strURL - IN			the URL of the file to be downloaded
//			   CString strFileName - OUT	the filename of the downloaded file
//		   }
// return value: not used
UINT CDlgFTPProgress::Download(LPVOID pParam)
{
	DOWNLOADPARAM *const pDownloadParam = static_cast<DOWNLOADPARAM *>(pParam);
	ASSERT(pDownloadParam != NULL);
	ASSERT(::AfxIsValidAddress(pDownloadParam, sizeof(DOWNLOADPARAM)));

	/*
		URLDownloadToCacheFile is a blocking function. Even though the data is
		downloaded asynchronously the function does not return until all the
		data is downloaded. If complete asynchronous downloading is desired,
		one of the other UOS functions, such as URLOpenStream, or perhaps
		general URL monikers would be more appropriate.
	*/

	CBSCallbackImpl bsc(pDownloadParam->hWnd, pDownloadParam->hEventStop);

//   ASSERT( pDownloadParam->strFileName.GetLength() > 0 );
//   const HRESULT hr = ::URLDownloadToFile(NULL,
//   											pDownloadParam->strURL,
//   											pDownloadParam->strFileName,
//   											0,
//   											&bsc);
   const HRESULT hr = ::URLDownloadToCacheFile(NULL,
   											pDownloadParam->strURL,
   											pDownloadParam->strFileName.
   												GetBuffer(MAX_PATH),
   											URLOSTRM_GETNEWESTVERSION,
   											0,
   											&bsc);
   // empty the filename string if failed or canceled
   pDownloadParam->strFileName.ReleaseBuffer(SUCCEEDED(hr) ? -1 : 0);

   /*
   	The resource from the cache is used for the second and subsequent
   	calls to URLDownloadToCacheFile during the session of the program
   	unless the following setting is selected, in which case, every call
   	to URLDownloadToCacheFile downloads the resource from the Internet.

   	Control Panel/Internet/General/Temporary Internet files/Settings/
   	Check for newer versions of stored pages -> Every visit to the page
   */
   
   TRACE(_T("URLDownloadToFile ends: 0x%08lX\nFile name: %s\n"),
   	  hr, pDownloadParam->strFileName);

	// let the dialog box know it is done
	::PostMessage(pDownloadParam->hWnd, WM_ENDFTPDOWNLOAD, 0, 0);

	return 0;
}
