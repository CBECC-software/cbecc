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
#include <iostream>
#include "BEMProc.h"
#include "BEMPropertyType.h"
#include "BEMProcObject.h"
#include "expTextIO.h"
#include "expCrypFile.h"


/////////////////////////////////////////////////////////////////////////////
// BEMPropTypeDetails
/////////////////////////////////////////////////////////////////////////////

void BEMPropTypeDetails::copy( BEMPropTypeDetails* pCopyFrom )
{	assert( pCopyFrom );
	if (pCopyFrom)
	{	m_compDataType		= pCopyFrom->m_compDataType;
		m_primary			= pCopyFrom->m_primary;
		m_editable			= pCopyFrom->m_editable;
		m_userDefault		= pCopyFrom->m_userDefault;
		m_displayInput		= pCopyFrom->m_displayInput;
		m_displayProposed	= pCopyFrom->m_displayProposed;
		m_displayBudget	= pCopyFrom->m_displayBudget;
		m_notInputMode		= pCopyFrom->m_notInputMode;
		m_notInputMsg		= pCopyFrom->m_notInputMsg;
		m_resetDBIDs = pCopyFrom->m_resetDBIDs;
	}
}


/////////////////////////////////////////////////////////////////////////////
// BEMPropertyType
/////////////////////////////////////////////////////////////////////////////

BEMPropertyType::BEMPropertyType()
{
   clear();
}

BEMPropertyType::~BEMPropertyType()
{
   clear();
}

void BEMPropertyType::clear()
{
	m_shortName.clear();
	m_propType       = BEMP_Int;

	for (int iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)
	{	m_obj1ClassIdx[iObjCls] = 0;
   	m_objTypeDBID[ iObjCls] = 0;
   	m_objTypeValue[iObjCls] = 0;
		m_obj1ClassStr[iObjCls].clear();
   	m_objPropStr[  iObjCls].clear();
	}

   m_numValues      = 0;
   m_unitsLabel.clear();
   m_useForTrees    = 0;
   m_helpID         = 0;
   m_1ClassIdx      = 0;
   m_1PropTypeIdx   = 0;
   m_sumOfPreviousProperties = 0;	// Sum of m_numValues for all previous BEMPropertyTypes that describe this class
	m_XMLWriteArrayIndices = FALSE;	// (file ver 2) added to indicate whether or not array indices are to be written to output XML files
	m_writeSimulationFlag = 1;			// 0-Never write to sim export, 1-Write to sim export whenever defined (default, rule, library...), 2-Write to sim export only if USER defined (or UsrDflt, UsrLib)
 	m_description.clear();
	m_inputClassInfo.clear();			// (file ver 6)
	m_previousNames.clear();		// SAC 8/6/15

	m_definedByRuleset	= FALSE;		// SAC 1/11/15
	m_reportPrecision = -9;				// SAC 2/4/15

	clearPropTypeDetails();
	clearRangeChecks();
}

void BEMPropertyType::clearRangeChecks()
{
	//for (int i = (int) m_ranges.size()-1; i >= 0; i--)	
	//{	assert( m_ranges.at(i) );
	//	if (m_ranges.at(i))
	//		delete m_ranges.at(i);
	//}
	m_ranges.clear();
}

void BEMPropertyType::addRangeCheck(BEMRangeCheck* pR)
{	int iInitSz = (int) m_ranges.size();
	m_ranges.resize( iInitSz+1 );
	m_ranges[iInitSz].copy( pR );
}

void BEMPropertyType::clearPropTypeDetails()
{
	//for (int i = (int) m_details.size()-1; i >= 0; i--)	
	//{	assert( &m_details.at(i) );
	//	if (&m_details.at(i))
	//		delete m_details.at(i);
	//}
	m_details.clear();
}


/////////////////////////////////////////////////////////////////////////////

BOOL BEMPropertyType::Copy( BEMPropertyType* pPT )
{  assert( pPT );
   BOOL bRetVal = TRUE;
   if (pPT)
   {
		int i=0;
	   m_shortName               = pPT->m_shortName;
	   m_propType                = pPT->m_propType;
		for (i=0; i < BEM_MAX_PROPTYPE_OBJREFCLASSES; i++)
		{
	   	m_obj1ClassIdx[i]     = pPT->m_obj1ClassIdx[i];
      	m_objTypeDBID[i]      = pPT->m_objTypeDBID[i];
      	m_objTypeValue[i]     = pPT->m_objTypeValue[i];
		}
      m_numValues               = pPT->m_numValues;
      m_unitsLabel              = pPT->m_unitsLabel;
      m_useForTrees             = pPT->m_useForTrees;
      m_helpID                  = pPT->m_helpID;
      m_1ClassIdx               = pPT->m_1ClassIdx;
      m_1PropTypeIdx            = pPT->m_1PropTypeIdx;
      m_sumOfPreviousProperties = pPT->m_sumOfPreviousProperties;
 	   m_description             = pPT->m_description;
   	m_inputClassInfo          = pPT->m_inputClassInfo;		// (file ver 6)

		m_previousNames.clear();
		int iNumPrevNames = pPT->m_previousNames.count();
		for (int i=0; i<iNumPrevNames; i++)
			m_previousNames.append( pPT->m_previousNames[i] );

		m_XMLWriteArrayIndices	= pPT->m_XMLWriteArrayIndices;
		m_writeSimulationFlag	= pPT->m_writeSimulationFlag ;
		m_definedByRuleset		= pPT->m_definedByRuleset;	
		m_reportPrecision			= pPT->m_reportPrecision; 

      m_symbolList.Copy( &pPT->m_symbolList );

	// BEMPropTypeDetails data
		m_details.clear();
		m_details.resize( m_numValues );
		for (i=0; i<m_numValues; i++)
		{	BEMPropTypeDetails* pThisDet = &m_details.at(i);			assert( pThisDet );
			BEMPropTypeDetails* pCopyDet = &pPT->m_details.at(i);		assert( pCopyDet );
			if (pThisDet && pCopyDet)
				pThisDet->copy( pCopyDet );
		}

	// BEMRangeCheck data
		m_ranges.clear();
		m_ranges.resize( pPT->m_ranges.size() );
		for (i=0; i<(int) m_ranges.size(); i++)
		{	BEMRangeCheck* pThisRC = &m_ranges.at(i);				assert( pThisRC );
			BEMRangeCheck* pCopyRC = &pPT->m_ranges.at(i);		assert( pCopyRC );
			if (pThisRC && pCopyRC)
				pThisRC->copy( pCopyRC );
		}
	//	for (int i=0; i < (int) pPT->m_ranges.size(); i++)	
	//	{	assert( pPT->m_ranges.at(i) );
	//		if (pPT->m_ranges.at(i))
	//		{	BEMRangeCheck* pNewR = NULL;
	//			try
	//			{	pNewR = new BEMRangeCheck( *(pPT->m_ranges.at(i)) );
	//				m_ranges.push_back( pNewR );
	//			}
	//			catch (std::exception& e)
	//			{	std::cout << "Warning: BEMPropertyType::Copy() failed to create BEMRangeCheck because " << e.what() << '\n';
	//				bRetVal = FALSE;
	//				if (pNewR)
	//					delete pNewR;
	//			}
	//		 	catch (...)
	//		  	{  std::cout << "Warning: BEMPropertyType::Copy() failed to create BEMRangeCheck\n";
	//				bRetVal = FALSE;
	//				if (pNewR)
	//					delete pNewR;
	//			}
	//		}
	//	}
	//	// ??? why here ??  m_ranges.clear();
   }
   else
      bRetVal = FALSE;
   return bRetVal;
}

void BEMPropertyType::initPropTypeDetails()
{	// BEMPropTypeDetails data
		m_details.clear();
		m_details.resize( m_numValues );
}

void BEMPropertyType::InitResetDataList()
{
   // Initialize reset data list
   BOOL bFailed = FALSE;
			assert( FALSE );
// TO OPENSRC
//   for (int i=0; (!bFailed) && (i<m_numValues); i++)
//   {
//	   BEMReset* pR = NULL;
//   	TRY
//   	{
//   		pR = new BEMReset;
//         m_resetData.AddTail(pR);
//   	}
//   	CATCH_ALL(e)
//   	{
//         bFailed = TRUE;
//      	TRACE0("Warning: BEMPropertyType::InitResetDataList failed\n");
//
//      	if (pR != NULL)
//      		delete pR;
//   	}
//   	END_CATCH_ALL
//   }
}

/////////////////////////////////////////////////////////////////////////////
//
// BEMPropertyType Class Function:  CreateBEMProperty()
//
// Purpose ------------------------------------------------------------------
//   Allocate memory and call initialization function for a new property
//   
// Arguments ----------------------------------------------------------------
//   int i0Arr  : array index (>=0 for property types w/ m_numValues > 1)
//   
// Return Value -------------------------------------------------------------
//   NULL if it fails, otherwise a pointer to the new BEMProperty
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
// - no longer needed
//BEMProperty* BEMPropertyType::CreateBEMProperty( int i0Arr )
//{
//	BEMProperty* pProperty = NULL;
//	TRY
//	{
//		pProperty = new BEMProperty(this, i0Arr);
//		
//		return pProperty;
//	}
//	CATCH_ALL(e)
//	{
//		// fall through
//	}
//	END_CATCH_ALL
//	
//	TRACE0("Warning: BEMPropertyType::CreateBEMProperty failed\n");
//	if (pProperty != NULL)
//		delete pProperty;
//		
//	return NULL;
//}


/////////////////////////////////////////////////////////////////////////////

int BEMPropertyType::NumberOfDistinctObjectTypesReferenced()
{
	int iNumUniqueObjClasses = 0;
	if (m_propType == BEMP_Obj)
	{	int ia1UniqueObjClassIdx[BEM_MAX_PROPTYPE_OBJREFCLASSES];
		int idx;
		for (idx=0; idx<BEM_MAX_PROPTYPE_OBJREFCLASSES; idx++)
			ia1UniqueObjClassIdx[idx] = 0;
		for (idx=0; idx<BEM_MAX_PROPTYPE_OBJREFCLASSES; idx++)
			if (m_obj1ClassIdx[idx] > 0)
			{
				BOOL bAlreadyFound = FALSE;
				for (int j=0; (!bAlreadyFound && j < iNumUniqueObjClasses); j++)
					bAlreadyFound = (m_obj1ClassIdx[idx] == ia1UniqueObjClassIdx[j]);
				if (!bAlreadyFound)
					ia1UniqueObjClassIdx[iNumUniqueObjClasses++] = m_obj1ClassIdx[idx];
			}
	}
	return iNumUniqueObjClasses;
}


bool BEMPropertyType::PreviousNameMatch( QString& sName )
{	bool bRetVal = false;
	foreach (const QString &str, m_previousNames)
	{	if (sName.compare( str, Qt::CaseInsensitive ) == 0)
		{	bRetVal = true;
			break;
	}	}
	return bRetVal;
}

/////////////////////////////////////////////////////////////////////////////

bool BEMPropertyType::setObjClassDataFromStrings()
{	bool bRetVal = (m_propType == BEMP_Obj);
	for (int iObjCls=0; (bRetVal && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
	{	m_objTypeDBID[iObjCls] = 0;
		if (!m_obj1ClassStr[iObjCls].isEmpty())
		{	m_obj1ClassIdx[iObjCls] = BEMP_GetDBComponentID( m_obj1ClassStr[iObjCls] );
			assert( m_obj1ClassIdx[iObjCls] > 0 );
			if (m_obj1ClassIdx[iObjCls] > 0 && !m_objPropStr[iObjCls].isEmpty())
			{	m_objTypeDBID[iObjCls] = BEMPX_GetDatabaseID( m_objPropStr[iObjCls], m_obj1ClassIdx[iObjCls] );
				assert( m_objTypeDBID[iObjCls] > BEM_COMP_MULT );
			}
			bRetVal = (m_obj1ClassIdx[iObjCls] > 0 && (m_objPropStr[iObjCls].isEmpty() || m_objTypeDBID[iObjCls] > BEM_COMP_MULT));
		}
		else
			m_obj1ClassIdx[iObjCls] = 0;
	}
	return (bRetVal && m_obj1ClassIdx[0] > 0);
}


/////////////////////////////////////////////////////////////////////////////

void BEMPropertyType::ReadText( BEMTextIO& file, int iFileVersion )
{
   m_shortName = file.ReadString();   file.PostReadToken();

   QString sPropType = file.ReadToken();   // read variable type keyword
   if      (sPropType.compare( "BEMP_Int", Qt::CaseInsensitive ) == 0)
      m_propType = BEMP_Int;
   else if (sPropType.compare( "BEMP_Flt", Qt::CaseInsensitive ) == 0)
      m_propType = BEMP_Flt;
   else if (sPropType.compare( "BEMP_Sym", Qt::CaseInsensitive ) == 0)
      m_propType = BEMP_Sym;
   else if (sPropType.compare( "BEMP_Str", Qt::CaseInsensitive ) == 0)
      m_propType = BEMP_Str;
   else if (sPropType.compare( "BEMP_Obj", Qt::CaseInsensitive ) == 0)
      m_propType = BEMP_Obj;
   else
      file.ThrowTextIOException( BEMTextioException::badPropTypeType ); // throw exception
   file.PostReadToken();

   m_numValues = (int) file.ReadLong();   file.PostReadToken();

   if (iFileVersion >= 2)
   {  m_XMLWriteArrayIndices = (BOOL) file.ReadLong();    // SAC 1/24/12 - (file ver 2) added to indicate whether or not array indices are to be written to output XML files
      file.PostReadToken();
   }

   if (iFileVersion >= 3)
   {  m_writeSimulationFlag = file.ReadLong();    // SAC 5/22/12 - (file ver 3)
      file.PostReadToken();
   }

	m_userSpecification = -1;  // SAC 2/25/13 - (file ver 5)
   if (iFileVersion >= 5)
   {  QString sInp = file.ReadToken();   // SAC 5/22/12 - (file ver 3)
   	if      (sInp.compare( "Comp", Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_Compulsory;
   	else if (sInp.compare( "Req" , Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_Required;
   	else if (sInp.compare( "CReq", Qt::CaseInsensitive ) == 0)	// SAC 2/11/15
   	   m_userSpecification = BEMD_CondRequired;
   	else if (sInp.compare( "Opt" , Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_Optional;
   	else if (sInp.compare( "Def" , Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_Default;
   	else if (sInp.compare( "CDef", Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_CriticalDef;
   	else if (sInp.compare( "Pres", Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_Prescribed;
   	else if (sInp.compare( "NInp", Qt::CaseInsensitive ) == 0)
   	   m_userSpecification = BEMD_NotInput;
		else
		{	assert( FALSE );
   	   m_userSpecification = -1;
		}
      file.PostReadToken();
   }

   m_unitsLabel = file.ReadString();			file.PostReadToken();
   m_useForTrees = (int) file.ReadLong();		file.PostReadToken();

   long iNumObjClassEntries = 1;		// SAC 6/15/12 - mods to accommodate a variable number of compatible referenced object names/types/values
	if (iFileVersion >= 4)
	{	iNumObjClassEntries = (int) file.ReadLong();			file.PostReadToken();
	}
	int iObjClsIdx = 0;
	for (; iObjClsIdx < iNumObjClassEntries; iObjClsIdx++)
	{	m_obj1ClassStr[iObjClsIdx] = file.ReadString();		file.PostReadToken();
   	m_objTypeValue[iObjClsIdx] = file.ReadLong();		file.PostReadToken();
   	m_objPropStr[  iObjClsIdx] = file.ReadString();		file.PostReadToken();
	}
	for (iObjClsIdx = iNumObjClassEntries; iObjClsIdx < BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjClsIdx++)
	{	m_obj1ClassStr[iObjClsIdx].clear();
   	m_objTypeValue[iObjClsIdx] = 0;
   	m_objPropStr[  iObjClsIdx].clear();
	}

   m_helpID = (UINT) file.ReadLong();   file.PostReadToken();

//   if (iFileVersion >= 2)
//   {
//      m_sErrorCheckRulelistName = file.ReadString();  // SAC 5/21/01 - Added code to read in new "ErrorCheckRulelistName" member
//      file.PostReadToken();
//   }

   m_description = file.ReadString();
   file.PostReadToken();

	if (iFileVersion >= 6)
   {	m_inputClassInfo = file.ReadString();		// SAC 3/3/14 - (file ver 6)
   	file.PostReadToken();
	}

	m_reportPrecision = -9;  // SAC 2/4/15 - property to facilitate rounding of numeric results for compliance reporting - rounding only for output of non-User models written to analysis results XML file
}

/////////////////////////////////////////////////////////////////////////////

void BEMPropertyType::Write( CryptoFile& file )
{
   file.WriteQString( m_shortName );
   file.Write( &m_propType   , sizeof( int ));
   file.Write( &m_numValues  , sizeof( int ));
   file.WriteQString( m_unitsLabel );
   file.Write( &m_useForTrees, sizeof( int ));

	for (int iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
	{  file.Write( &m_obj1ClassIdx[iObjCls], sizeof( int  ) );
	   file.Write( &m_objTypeDBID[ iObjCls], sizeof( long ) );
	   file.Write( &m_objTypeValue[iObjCls], sizeof( long ) );
	}

   file.Write( &m_helpID, sizeof( UINT ));

//   file.WriteQString( m_sErrorCheckRulelistName );  // SAC 5/21/01 - added writing of new member
   file.Write( &m_XMLWriteArrayIndices, sizeof( BOOL ));	// SAC 1/24/12 - (file ver 2) added to indicate whether or not array indices are to be written to output XML files

   file.Write( &m_writeSimulationFlag, sizeof( long ));	// SAC 5/22/12 - (file ver 3) 

   file.Write( &m_reportPrecision, sizeof( int ));	// SAC 2/4/15 - (no file I/O yet)

   file.Write( &m_userSpecification, sizeof( long ));	// SAC 2/25/13 - (file ver 5)

   file.WriteQString( m_description );
   file.WriteQString( m_inputClassInfo );	// SAC 3/3/14 - (file ver 6)

	int iNumPrevNames = (int) m_previousNames.size();	// SAC 8/6/15 - to facilitate data model backward compatibility by tracking re-named properties
   file.Write( &iNumPrevNames, sizeof( int ));
   for (int i=0; i<iNumPrevNames; i++)
   	file.WriteQString( m_previousNames[i] );

   file.Write( &m_1ClassIdx   , sizeof( int ));
   file.Write( &m_1PropTypeIdx, sizeof( int ));
}

