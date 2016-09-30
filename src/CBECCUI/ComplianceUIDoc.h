// ComplianceUIDoc.h : interface of the CComplianceUIDoc class
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

#if !defined(AFX_ComplianceUIDOC_H__245352CB_5683_11D1_9002_0080C732DDC2__INCLUDED_)
#define AFX_ComplianceUIDOC_H__245352CB_5683_11D1_9002_0080C732DDC2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern void SetDataModifiedFlag( BOOL bMod );
extern bool IsXMLFileExt( CString sExt );	// SAC 10/29/15
extern bool IsRecognizedFileExt( CString sExt );	// SAC 10/29/15
extern void BaseFileExt( CString& sExt );	// SAC 10/29/15
extern void LoadFileExtensionString( CString& sSaveAsExt, bool bUseProjectData, bool bXML=false );	// SAC 10/29/15
extern bool FileExtensionAllowsSave( CString sSaveAsExt );		// SAC 11/2/15
extern void LoadFileOptionString( CString& sSaveAs, bool bUseProjectData );	// SAC 10/29/15
extern void CodeYearAbbrev( CString& sCodeYearAbbrev, bool bForFileExtension=true );	// SAC 10/29/15   // SAC 3/24/16

class CComplianceUIDoc : public CDocument
{
protected: // create from serialization only
	CComplianceUIDoc();
	DECLARE_DYNCREATE(CComplianceUIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComplianceUIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComplianceUIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual BOOL SaveModified(); // return TRUE if ok to continue
	BOOL CUISaveModified( const char* pszUserAction=NULL );  // SAC 8/15/14 - was: BOOL bPreAnalysis=FALSE );

   BOOL OpenTheFile( CPathName sInputFile, BOOL bWriteToLog=TRUE, BOOL bRestore=FALSE,
							const char* pszNewRulesetFile=NULL, long lRulesetSymVal=-1,
							BOOL bNormalRulesetUpdates=TRUE );	// SAC 11/17/15
	BOOL CheckAndDefaultModel( BOOL bCheckModel=TRUE, BOOL bWriteToLog=TRUE );		// SAC 9/5/14

protected:
   virtual BOOL OnSaveDocument(const char* pszPathName);

// Generated message map functions
protected:
	//{{AFX_MSG(CComplianceUIDoc)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ComplianceUIDOC_H__245352CB_5683_11D1_9002_0080C732DDC2__INCLUDED_)
