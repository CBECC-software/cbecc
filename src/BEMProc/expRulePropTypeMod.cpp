// RulePropTypeMod.cpp - implementation of BEMPropTypeMod and BEMPropTypeModList classes
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

#include "stdafx.h"
#include "BEMProc.h"
#include "expRulePropTypeMod.h"
#include "expRuleList.h"
#include "BEMPropertyType.h"
#include "memLkRpt.h"


static int StringInArray( QStringList& saStrs, QString& sStr )  // SAC 8/25/03
{
   int iSize = (int) saStrs.size();
   for (int i=0; i<iSize; i++)
   {
      if (saStrs[i].compare( sStr, Qt::CaseInsensitive ) == 0)
         return i;
   }
   return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// class BEMPropTypeMod
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// BEMPropTypeMod Class Function:  Read()
//
// Purpose ------------------------------------------------------------------
//   Read a RulePropTypeMod assignment entry from a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CCryptoFile& file : the binary encrypted ruleset file to read the RulePropTypeMod entry from.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPropTypeMod::Read( CryptoFile& file )
{
   file.Read( &m_dbid,    	sizeof( long ) );
   file.Read( &m_reportPrecision,   sizeof( int  ) );

	// SAC 8/12/15 - to facilitate data model backward compatibility by tracking re-named properties
	int iNumPrevNames, iPrevNameIdx;		QString sPrevName;
	file.Read( &iNumPrevNames, sizeof( int ) );
	for (iPrevNameIdx=0; iPrevNameIdx<iNumPrevNames; iPrevNameIdx++)
	{	file.ReadQString( sPrevName );
		m_previousNames.push_back( sPrevName );
	}
}


/////////////////////////////////////////////////////////////////////////////
//
// BEMPropTypeMod Class Function:  Write()
//
// Purpose ------------------------------------------------------------------
//   Write a RulePropTypeMod assignment entry to a binary encrypted ruleset file.
//   
// Arguments ----------------------------------------------------------------
//   CCryptoFile& file : the binary encrypted ruleset file to write the RulePropTypeMod entry to.
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void BEMPropTypeMod::Write( CryptoFile& file )
{
   file.Write( &m_dbid,    	sizeof( long ) );
   file.Write( &m_reportPrecision,  sizeof( int  ) );

	int iNumPrevNames = m_previousNames.size();	// SAC 8/12/15
   file.Write( &iNumPrevNames, sizeof( int ));
   for (int i=0; i<iNumPrevNames; i++)
   	file.WriteQString( m_previousNames[i] );
}


//	/////////////////////////////////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// class BEMPropTypeModList
//	//
//	/////////////////////////////////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMPropTypeModList Class Function:  ~BEMPropTypeModList()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Removes all RulePropTypeMod entries from the list.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   None
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	BEMPropTypeModList::~BEMPropTypeModList()
//	{
//	   RemoveAll();
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMPropTypeModList Class Function:  RemoveAll()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Removes all the RulePropTypeMod entries from the list, deleting each as we go.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   None
//	//   
//	// Return Value -------------------------------------------------------------
//	//   None
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	void BEMPropTypeModList::RemoveAll()
//	{
//	   POSITION pos = GetHeadPosition();
//	   while ( pos != NULL )
//	      delete (BEMPropTypeMod*)GetNext( pos );
//	   CObList::RemoveAll();
//	}
//	
//	


void RuleSet::postRulePropTypeModsToDatabase()
{
	// any need to INITIALIZE existing PropTypeMod data in BEMPROC ??

	int iError;
	for (int i=0; i < (int) m_rulePropTypeMods.size(); i++)
	{	BEMPropTypeMod* pRPTM = m_rulePropTypeMods[i];			assert( pRPTM && pRPTM->m_dbid > 0 );
		if (pRPTM && pRPTM->m_dbid > 0)
		{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( pRPTM->m_dbid, iError /*, iBEMProcIdx=-1*/ );		assert( pPropType );
			if (pPropType)
			{	pPropType->setReportPrecision( pRPTM->m_reportPrecision );
				for (int j=0; j < (int) pRPTM->m_previousNames.size(); j++)
					pPropType->addPreviousName( pRPTM->m_previousNames[j] );
	}	}	}
}


//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMPropTypeModList Class Function:  Read()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Reads the RulePropTypeMod definitions from a binary encrypted ruleset file.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   CCryptoFile& file : the binary encrypted ruleset file to read the RulePropTypeMod definitions from.
//	//   
//	// Return Value -------------------------------------------------------------
//	//   TRUE always
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	bool BEMPropTypeModList::Read( CCryptoFile& file )
//	{
//	   int count = 0;
//	   // read number of RulePropTypeMod definitions stored in file
//	   file.Read( &count, sizeof( int ) );
//	
//	   // loop over each entry, creating a new BEMPropTypeMod, reading it and adding it to the list
//	   for ( int i = 0; i < count; i++ )
//	   {
//	      BEMPropTypeMod* pRulePropTypeMod = new BEMPropTypeMod;
//	      pRulePropTypeMod->Read( file );
//	      AddRulePropTypeMod( pRulePropTypeMod );
//	   }
//	
//	   // call BEMProc to reinitialize all RulePropTypeMod flags
//	   BEMPX_SetClassMaxChildrenFlag( -1, -1 );  
//	
//	   // Post RulePropTypeMod information to Building Database for access by user interface module
//	   POSITION pos = GetHeadPosition();
//	   while ( pos != NULL )
//	   {
//	      BEMPropTypeMod* pRPTM = (BEMPropTypeMod*) GetAt( pos );
//	      if (pRPTM)
//	      {	int iError;
//	         if (pRPTM->m_dbid > 0)
//				{	CBEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( pRPTM->m_dbid, iError /*, iBEMProcIdx=-1*/ );			ASSERT( pPropType );
//					if (pPropType)
//					{	pPropType->m_reportPrecision = pRPTM->m_reportPrecision;
//						int iNumPrevNames = pRPTM->m_previousNames.GetSize();		// SAC 8/12/15
//						for (int i=0; i<iNumPrevNames; i++)
//						{	if (StringInArray( pPropType->m_previousNames, pRPTM->m_previousNames[i] ) < 0)
//								pPropType->m_previousNames.Add( pRPTM->m_previousNames[i] );
//					}	}
//				}
//	         GetNext( pos );
//	      }
//	      else
//	         ASSERT( FALSE );
//	   }
//	
//	   return TRUE;
//	}
//	
//	
//	/////////////////////////////////////////////////////////////////////////////
//	//
//	// BEMPropTypeModList Class Function:  Write()
//	//
//	// Purpose ------------------------------------------------------------------
//	//   Writes the RulePropTypeMod definitions to a binary encrypted ruleset file.
//	//   
//	// Arguments ----------------------------------------------------------------
//	//   CCryptoFile& file : the binary encrypted ruleset file to write the RulePropTypeMod definitions to.
//	//   
//	// Return Value -------------------------------------------------------------
//	//   TRUE always
//	//   
//	// Notes --------------------------------------------------------------------
//	//   None
//	//   
//	/////////////////////////////////////////////////////////////////////////////
//	bool BEMPropTypeModList::Write( CCryptoFile& file )
//	{
//	   int count = (int) GetCount();
//	   // write the number of RulePropTypeMod definitions
//	   file.Write( &count, sizeof( int ) );
//	
//	   POSITION pos = GetHeadPosition();
//	   // loop over entire list, writing each to the file
//	   while ( pos != NULL )
//	   {
//	      BEMPropTypeMod* pRulePropTypeMod = (BEMPropTypeMod*)GetNext( pos );
//	      pRulePropTypeMod->Write( file );
//	   }
//	
//	   return TRUE;
//	}


/////////////////////////////////////////////////////////////////////////////
//
// RuleSet Class Function:  addRulePropTypeMod()
//
// Purpose ------------------------------------------------------------------
//   Adds a BEMPropTypeMod instance onto the end of the list.
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
void RuleSet::addRulePropTypeMod( BEMPropTypeMod* pRulePropTypeMod )
{
   m_rulePropTypeMods.push_back( pRulePropTypeMod );
}

void RuleSet::addRulePropTypeMod( long lDBID, int iReportPrecision )
{
   bool bFound = false;
	int iCount = m_rulePropTypeMods.size();
	for (int i=0; (!bFound && i < iCount); i++)
	{	if (m_rulePropTypeMods.at(i) && m_rulePropTypeMods.at(i)->m_dbid == lDBID)
		{	m_rulePropTypeMods.at(i)->m_reportPrecision = iReportPrecision;
      	bFound = true;
   }	}
   if (!bFound)
   {	BEMPropTypeMod* pRulePropTypeMod = new BEMPropTypeMod( lDBID, iReportPrecision );
		m_rulePropTypeMods.push_back( pRulePropTypeMod );
   }
}

void RuleSet::addRulePropTypeMod( long lDBID, const char* pszPrevName )
{
   bool bFound = false;
   QString sPrevName = pszPrevName;
	int iCount = m_rulePropTypeMods.size();
	for (int i=0; (!bFound && i < iCount); i++)
	{	if (m_rulePropTypeMods.at(i) && m_rulePropTypeMods.at(i)->m_dbid == lDBID)
		{	if (!m_rulePropTypeMods.at(i)->m_previousNames.contains( sPrevName ))
				m_rulePropTypeMods.at(i)->m_previousNames.push_back( sPrevName );
      	bFound = true;
   }	}
   if (!bFound)
   {	BEMPropTypeMod* pRulePropTypeMod = new BEMPropTypeMod( lDBID, -9, pszPrevName );
		m_rulePropTypeMods.push_back( pRulePropTypeMod );
   }
}

