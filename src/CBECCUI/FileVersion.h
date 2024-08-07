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

// FileVersion.h: interface for the CFileVersion class.
// by Manuel Laflamme
//////////////////////////////////////////////////////////////////////

#ifndef __FILEVERSION_H_
#define __FILEVERSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFileVersion
{
// Construction
public:
    CFileVersion();

// Operations
public:
    BOOL    Open(LPCTSTR lpszModuleName);
    void    Close();

    CString QueryValue(LPCTSTR lpszValueName, DWORD dwLangCharset = 0);
    CString GetFileDescription()  {return QueryValue(_T("FileDescription")); };
    CString GetFileVersion()      {return QueryValue(_T("FileVersion"));     };
    CString GetInternalName()     {return QueryValue(_T("InternalName"));    };
    CString GetCompanyName()      {return QueryValue(_T("CompanyName"));     };
    CString GetLegalCopyright()   {return QueryValue(_T("LegalCopyright"));  };
    CString GetOriginalFilename() {return QueryValue(_T("OriginalFilename"));};
    CString GetProductName()      {return QueryValue(_T("ProductName"));     };
    CString GetProductVersion()   {return QueryValue(_T("ProductVersion"));  };

    BOOL    GetFixedInfo(VS_FIXEDFILEINFO& vsffi);
    CString GetFixedFileVersion();
    CString GetFixedProductVersion();
    CString GetPDProductVersion( BOOL bIncludeBuild=TRUE );

// Attributes
protected:
    LPBYTE  m_lpVersionData;
    DWORD   m_dwLangCharset;

// Implementation
public:
    ~CFileVersion();
};

#endif  // __FILEVERSION_H_
