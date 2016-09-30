// MaxChild.cpp - implementation of CToolTipMsg and CToolTipMsgList classes
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1997, SAC Software                                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "..\BEMProc\BEMProc.h"
//#include "..\BEMProc\BEMRulPrcX.h"
#include "ToolTips.h"
#include "BEMProcUI_Globals.h"
#include "BEMProcUIX.h"

static CToolTipMsgList sttml;


void BEMPUIX_GetToolTipMessage( CString& sMsg, long lDBID )
{
//   const char* pStr = NULL;
   sMsg.Empty();
   if (sttml.GetCount() > 0 && lDBID > 0)
   {
      int iClass = BEMPX_GetClassID( lDBID );
      int iProp  = BEMPX_GetPropertyID( lDBID );
      int iArray = BEMPX_GetArrayID( lDBID );
      // create and perform comparisons to a secondary DBID which corresponds
      // to the first of potentially several array elements as a fall-back string
      // This means that if user is asking for string for Class:Property[3] but
      // a string exists for "[1] but not "[3], then the string for "[1] would be returned
      long  lSecDBID = (iProp < 1 || iArray == 1) ? 0 : BEMPX_GetDBID( iClass, iProp, 1 );

      for (POSITION pos = sttml.GetHeadPosition(); pos != NULL; )
      {
         CToolTipMsg* pTTM = (CToolTipMsg*) sttml.GetNext( pos );
         if (pTTM)
         {
            if (pTTM->m_lDBID == lDBID)
            {  // exact match found, so return it
//               return (const char*) pTTM->m_sMessage;
               sMsg = pTTM->m_sMessage;
               return;
            }
            else if (pTTM->m_lDBID == lSecDBID)  // SAC 3/4/02 - fixed bug by replacing "lDBID ==" w/ "pTTM->m_lDBID =="
               // secondary match found, so store it for return later if
               // exact lDBID match not found
//               pStr = (const char*) pTTM->m_sMessage;
               sMsg = pTTM->m_sMessage;
         }
      }
   }
//   return pStr;
   return;
}


BOOL ReadToolTipFile( const char* pszToolTipFileName )
{
   BOOL bRetVal = TRUE;  // allow there to be no ToolTip message text file
   if (FileExists( pszToolTipFileName ))
   {
      TRY
      {  // open file
         CTextIO file( pszToolTipFileName, CTextIO::load );

         TRY
         {
            // clear out any existing ToolTip messages
            sttml.RemoveAll();

            TRY
            {
               BOOL bFileEndFound = FALSE;  // SAC 6/25/12
            	while ( !bFileEndFound )   //TRUE ) // EOF handled in catch block 
               {  // create new CToolTipMsg
                  CToolTipMsg* newData = new CToolTipMsg();

                  // read ToolTip definition from file
                  bRetVal = ((newData->Read( file )) && (bRetVal));
					   if (newData->m_lDBID == -999)  // SAC 6/25/12 - check for lDBID set to special value denoting END of ToolTip file
						{	bFileEndFound = TRUE;
							delete newData;
						}
						else
						{	// add this new CToolTipMsg to list
                  	sttml.AddTail( (CObject*) newData );
                  	file.Advance();
						}
               }
            }
            CATCH( CTextioException, err )
            {
               if ( err->m_cause == CTextioException::endOfFile )
                  ; // we're done, no problem
               else
                  THROW_LAST();
            }
            END_CATCH
         }
         CATCH( CTextioException, err )
         {  // ERROR occurred
            CString msg = CString("Error Reading MaxChild data\r\n");
            msg += CString("From File: ") + CString(pszToolTipFileName) + CString( "\r\n" );
            msg += CString("\r\n\t") + CString( err->m_strError ) + CString("\r\n") + CString("\r\n");
            bRetVal = FALSE;

            ::MessageBox( NULL, msg, NULL, MB_ICONEXCLAMATION );
            THROW_LAST();
         }
         END_CATCH
      }
      CATCH( CFileException, error )
      {
         CString msg = CString( "Error opening file: " ) + CString(pszToolTipFileName);
         ::MessageBox( NULL, msg, NULL, MB_ICONEXCLAMATION );
         bRetVal = FALSE;
      }
      END_CATCH
   }
   
   return bRetVal;
}


BOOL LoadToolTipsFromRuleset()	// SAC 5/11/14
{
   BOOL bRetVal = TRUE;
	QString sTTText;
	long lTTDBID;
	int iNumRuleToolTips = BEMPX_GetNumRuleToolTips();
	for (int i=0; i < iNumRuleToolTips; i++)
	{
		if (BEMPX_GetRuleToolTipData(i, sTTText, lTTDBID))
		{
			CToolTipMsg* newData = new CToolTipMsg();
			if (newData)
			{
				newData->m_sMessage = sTTText.toLocal8Bit().constData();
				newData->m_lDBID    = lTTDBID;
				sttml.AddTail( (CObject*) newData );	// add this new CToolTipMsg to list
			}
			else
			{	ASSERT( FALSE );
			}
		}
		else
		{	ASSERT( FALSE );		// RuleProcGetRuleToolTipData() failed
		}
	}
   return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class CToolTipMsg
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// CToolTipMsg Class Function:  CToolTipMsg()
//
// Purpose ------------------------------------------------------------------
//   Constructor - does nothing for now
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CToolTipMsg::CToolTipMsg()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// CToolTipMsg Class Function:  ~CToolTipMsg()
//
// Purpose ------------------------------------------------------------------
//   Destructor - does nothing for now
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CToolTipMsg::~CToolTipMsg()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// CMaxChild Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Reads a ToolTip message definition from a CTextIO file into this class
//   instance.
//   
// Arguments ----------------------------------------------------------------
//   CTextIO& file      : text file to read the ToolTip data from
//   CFile&   errorFile : file to write error messages to
//   
// Return Value -------------------------------------------------------------
//   TRUE if ToolTip successfully read from file, else FALSE.
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
BOOL CToolTipMsg::Read( CTextIO& file )
{
   // sName includes <bldg component name>:<parameter name>([<array index>])
   CString sName;
   file.ReadBEMProcParam( sName );
   m_lDBID = BEMPX_GetDatabaseID( sName );

   if (m_lDBID <= 0 && sName.IsEmpty())  // SAC 6/25/12 - set lDBID to special value denoting END of ToolTip file
      m_lDBID = -999;
   else
	{	if (m_lDBID <= 0)  // Post error to error listing
		{  CString sLine;
   	   sLine.Format( "%d", file.GetLineCount() );
   	   CString sErr;
   	   sErr.Format( "\tParameter '%s' Not Found on line: ", sName );
   	   sErr += sLine;
   	   sErr += CString("\r\n");
   	   ::MessageBox( NULL, sErr, NULL, MB_ICONEXCLAMATION );
   	   return FALSE;
   	}

   	file.PostReadToken();
   	m_sMessage = file.ReadString( TRUE /*bReadPastEOL*/ );	// SAC 2/11/15 - enable TT strings to span lines
   	if (!m_sMessage.IsEmpty())
   		m_sMessage += "\n";		// SAC 2/11/15 - insert a line after message and before trailing data type, range and status info
	}

   return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class CToolTipMsgList
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// CToolTipMsgList Class Function:  ~CToolTipMsgList()
//
// Purpose ------------------------------------------------------------------
//   Removes all MaxChild entries from the list.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
CToolTipMsgList::~CToolTipMsgList()
{
   RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
//
// CToolTipMsgList Class Function:  RemoveAll()
//
// Purpose ------------------------------------------------------------------
//   Removes all the MaxChild entries from the list, deleting each as we go.
//   
// Arguments ----------------------------------------------------------------
//   None
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CToolTipMsgList::RemoveAll()
{
   POSITION pos = GetHeadPosition();

   while ( pos != NULL )
      delete (CToolTipMsg*)GetNext( pos );
   CObList::RemoveAll();
}



