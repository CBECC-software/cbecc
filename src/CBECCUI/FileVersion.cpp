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

// FileVersion.cpp: implementation of the CFileVersion class.
// by Manuel Laflamme
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileVersion.h"

#pragma comment(lib, "version")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

CFileVersion::CFileVersion()
{
    m_lpVersionData = NULL;
    m_dwLangCharset = 0;
}

CFileVersion::~CFileVersion()
{
    Close();
}

void CFileVersion::Close()
{
    delete[] m_lpVersionData;
    m_lpVersionData = NULL;
    m_dwLangCharset = 0;
}

BOOL CFileVersion::Open(LPCTSTR lpszModuleName)
{
    ASSERT(_tcslen(lpszModuleName) > 0);
    ASSERT(m_lpVersionData == NULL);

    // Get the version information size for allocate the buffer
    DWORD dwHandle;
    DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)lpszModuleName, &dwHandle);
    if ( dwDataSize == 0 )
        return FALSE;

    // Allocate buffer and retrieve version information
    m_lpVersionData = new BYTE[dwDataSize];
    if (!::GetFileVersionInfo((LPTSTR)lpszModuleName, dwHandle, dwDataSize,
                                  (void**)m_lpVersionData) )
    {
        Close();
        return FALSE;
    }

    // Retrieve the first language and character-set identifier
    UINT nQuerySize;
    DWORD* pTransTable;
    if (!::VerQueryValue(m_lpVersionData, _T("\\VarFileInfo\\Translation"),
                         (void **)&pTransTable, &nQuerySize) )
    {
        Close();
        return FALSE;
    }

    // Swap the words to have lang-charset in the correct format
    m_dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));

    return TRUE;
}

CString CFileVersion::QueryValue(LPCTSTR lpszValueName,
                                 DWORD dwLangCharset /* = 0*/)
{
    // Must call Open() first
    ASSERT(m_lpVersionData != NULL);
    if ( m_lpVersionData == NULL )
        return (CString)_T("");

    // If no lang-charset specified use default
    if ( dwLangCharset == 0 )
        dwLangCharset = m_dwLangCharset;

    // Query version information value
    UINT nQuerySize;
    LPVOID lpData;
    CString strValue, strBlockName;
    strBlockName.Format(_T("\\StringFileInfo\\%08lx\\%s"),
                             dwLangCharset, lpszValueName);
    if ( ::VerQueryValue((void **)m_lpVersionData, strBlockName.GetBuffer(0),
                             &lpData, &nQuerySize) )
        strValue = (LPCTSTR)lpData;

    strBlockName.ReleaseBuffer();

    return strValue;
}

BOOL CFileVersion::GetFixedInfo(VS_FIXEDFILEINFO& vsffi)
{
    // Must call Open() first
    ASSERT(m_lpVersionData != NULL);
    if ( m_lpVersionData == NULL )
        return FALSE;

    UINT nQuerySize;
        VS_FIXEDFILEINFO* pVsffi;
    if ( ::VerQueryValue((void **)m_lpVersionData, _T("\\"),
                         (void**)&pVsffi, &nQuerySize) )
    {
        vsffi = *pVsffi;
        return TRUE;
    }

    return FALSE;
}

CString CFileVersion::GetFixedFileVersion()
{
    CString strVersion;
        VS_FIXEDFILEINFO vsffi;

    if ( GetFixedInfo(vsffi) )
    {
        strVersion.Format ("%u,%u,%u,%u",HIWORD(vsffi.dwFileVersionMS),
            LOWORD(vsffi.dwFileVersionMS),
            HIWORD(vsffi.dwFileVersionLS),
            LOWORD(vsffi.dwFileVersionLS));
    }
    return strVersion;
}

CString CFileVersion::GetFixedProductVersion()
{
    CString strVersion;
        VS_FIXEDFILEINFO vsffi;

    if ( GetFixedInfo(vsffi) )
    {
        strVersion.Format ("%u,%u,%u,%u", HIWORD(vsffi.dwProductVersionMS),
            LOWORD(vsffi.dwProductVersionMS),
            HIWORD(vsffi.dwProductVersionLS),
            LOWORD(vsffi.dwProductVersionLS));
    }
    return strVersion;
}

CString CFileVersion::GetPDProductVersion( BOOL bIncludeBuild )
{
    CString strVersion;
        VS_FIXEDFILEINFO vsffi;

    if ( GetFixedInfo(vsffi) )
    {
        if (bIncludeBuild)
            strVersion.Format ("%u.%u, build %u", HIWORD(vsffi.dwProductVersionMS),
                LOWORD(vsffi.dwProductVersionMS), LOWORD(vsffi.dwProductVersionLS) );
        else
            strVersion.Format ("%u.%u", HIWORD(vsffi.dwProductVersionMS),
                LOWORD(vsffi.dwProductVersionMS) );
    }
    return strVersion;
}
