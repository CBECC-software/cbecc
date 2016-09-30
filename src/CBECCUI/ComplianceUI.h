// ComplianceUI.h : main header file for the ComplianceUI application
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

#if !defined(AFX_ComplianceUI_H__245352C5_5683_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_ComplianceUI_H__245352C5_5683_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../BEMProc/BEMProc.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////

class CUICommandLineInfo : public CCommandLineInfo
{
public:
	CUICommandLineInfo() {}
	virtual ~CUICommandLineInfo() {};
    virtual void ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast);
};				// class CBEMCommandLineInfo


/////////////////////////////////////////////////////////////////////////////
// CComplianceUIApp:
// See ComplianceUI.cpp for the implementation of this class
//

class CComplianceUIApp : public CWinApp
// class CComplianceUIApp : public CBEMApp
{
public:
	CComplianceUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComplianceUIApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast);
	virtual BOOL PerformSimulations() const { return m_bPerformSimulations; }
	virtual BOOL PerformAnalysis() const { return m_bPerformAnalsysis; }
	virtual BOOL PerformSave() const { return m_bPerformSave; }
	//}}AFX_VIRTUAL
protected:
	BOOL m_bPerformSimulations;	// -nosim command line option sets FALSE (default TRUE)
	BOOL m_bPerformAnalsysis;	// -pa command line option sets TRUE (default FALSE)
	BOOL m_bPerformSave;		// -save command line option sets TRUE (default FALSE)

// Implementation

	void InitBEMProcINIData();

	//{{AFX_MSG(CComplianceUIApp)
	afx_msg void OnFileNew();
	afx_msg void OnAppAbout();
	afx_msg BOOL OnOpenRecentFile(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ComplianceUI_H__245352C5_5683_11D1_9002_0080C732DDC2__INCLUDED_)
