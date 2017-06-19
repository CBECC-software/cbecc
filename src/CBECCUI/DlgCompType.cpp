// DlgCompType.cpp : implementation file
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
#include "DlgCompType.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCompType dialog


CDlgCompType::CDlgCompType(CompTypeDlgMode eCTDM, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCompType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCompType)
	m_sSelectedCompType = _T("");
	m_sSelCompTypeLbl = _T("Select the type of building component to ");
	m_sSelCompLbl = _T("");
	m_sSelectedComponent = _T("");
	//}}AFX_DATA_INIT

   m_eMode = eCTDM;
   switch (m_eMode)
   {
      case CTDM_Edit   : m_sSelCompTypeLbl += _T("edit:"  );   break;
      case CTDM_Create : m_sSelCompTypeLbl += _T("create:");   break;
      case CTDM_Delete : m_sSelCompTypeLbl += _T("delete:");
	                      m_sSelCompLbl     += _T("Select the building component to delete:");   break;
   }
}


void CDlgCompType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCompType)
	DDX_Control(pDX, IDC_CTD_COMPONENT, m_cmbbComponent);
	DDX_Control(pDX, IDC_COMPTYPE, m_cmbbCompType);
	DDX_CBString(pDX, IDC_COMPTYPE, m_sSelectedCompType);
	DDV_MaxChars(pDX, m_sSelectedCompType, 32);
	DDX_Text(pDX, IDC_LBL_COMPTYPE, m_sSelCompTypeLbl);
	DDX_Text(pDX, IDC_LBL_COMPONENT, m_sSelCompLbl);
	DDX_CBString(pDX, IDC_CTD_COMPONENT, m_sSelectedComponent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCompType, CDialog)
	//{{AFX_MSG_MAP(CDlgCompType)
	ON_CBN_SELCHANGE(IDC_COMPTYPE, OnSelChangeCompType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCompType message handlers

BOOL CDlgCompType::OnInitDialog() 
{
	CDialog::OnInitDialog();

   m_cmbbCompType.ResetContent();
   int iError, iClassIdx = 1;
   BEMClass* pClass = BEMPX_GetClass( iClassIdx, iError );
   while (pClass)
   {
      if (m_eMode != CTDM_Delete || BEMPX_GetNumObjects( iClassIdx ) > 0)
      {
         m_cmbbCompType.AddString( pClass->getLongName().toLatin1().constData() );
         m_cmbbCompType.SetItemData( m_cmbbCompType.GetCount()-1, iClassIdx );
      }

      pClass = BEMPX_GetClass( ++iClassIdx, iError );
   }

   if (m_cmbbCompType.GetCount() > 0)  // at least one component type added to listing
      m_cmbbCompType.SetCurSel( 0 );

   if (m_eMode == CTDM_Delete)
      OnSelChangeCompType();
   else
      m_cmbbComponent.ShowWindow( SW_HIDE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCompType::OnSelChangeCompType() 
{
   if (m_eMode == CTDM_Delete)
   {
      m_cmbbComponent.ResetContent();

      int iClass = (int) m_cmbbCompType.GetItemData( m_cmbbCompType.GetCurSel() );
      if (iClass > 0)
      {
         int iError;
         int iNumObjects = BEMPX_GetNumObjects( iClass );
         for (int iObj=0; iObj < iNumObjects; iObj++)
         {
            BEMObject* pObj = BEMPX_GetObjectByClass( iClass, iError, iObj );
            if ( iError >= 0 && pObj )
               m_cmbbComponent.AddString( pObj->getName().toLatin1().constData() );
         }

         if (m_cmbbComponent.GetCount() > 0)
            m_cmbbComponent.SetCurSel( m_cmbbComponent.GetCount()-1 );
      }
   }
}

void CDlgCompType::OnOK() 
{
   m_iClass = (int) m_cmbbCompType.GetItemData( m_cmbbCompType.GetCurSel() );
	
	CDialog::OnOK();
}
