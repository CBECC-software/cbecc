// BEMCondition.cpp
//
/**********************************************************************
 *  Copyright (c) 2012-2018, California Energy Commission
 *  Copyright (c) 2018, SAC Software Solutions, LLC
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
#include "BEMProcUI_Globals.h"
#include "Screens.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "BEMProcUIX.h"
//#include "memLkRpt.h"
#include "BEMCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CBEMCondition
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

CBEMCondition::CBEMCondition()
{
   Init();
}


void CBEMCondition::Init()
{
   m_iNumConditions = 0;
   m_bConditionsAND = FALSE;
   for (int i=0; i<MAX_BEM_CONDITIONS; i++)
   {
      m_lConditionalDBID[ i ] =  0;
      m_iCondition[       i ] = -1;
      m_fConditionValue[  i ] =  0;
      m_lCondDBIDOffset[  i ] =  0;
      m_iCondDBInstance[  i ] = -1;
      m_lCondDBID2[       i ] =  0;
      m_lCondDBIDOffset2[ i ] =  0;
   }
}


long GetConditionalDBID( const char* psCondDBID, int& iDBInstance, long& lDBID2, int iCondition, CBEMPUIPage* pPage, const char* psSuppMsg, const char* psCondType, int iLine )
{
   long lRetVal = 0;
   if (pPage && psCondDBID && iCondition >= 0)
   {
      // SAC 3/3/99 - Added code to peal off and translate leading 0-based class instance index
      CString sCondDBID = psCondDBID;
      if (isdigit( sCondDBID[0] ))
      {
         int iFirstColon = sCondDBID.Find( ':' );
         ASSERT( iFirstColon > 0 );
         iDBInstance = atoi( sCondDBID.Left( iFirstColon ) );

         // trim leading class instance index
         sCondDBID = sCondDBID.Right( sCondDBID.GetLength()-iFirstColon-1 );
      }
      else
         iDBInstance = -1;

      int iRefCompID = 0;  // SAC 7/17/01
      lRetVal = BEMPX_GetDatabaseID( sCondDBID, pPage->m_iClassId, FALSE, &iRefCompID );
		// Note: when > 0, iRefCompID identifies only the first of possible several object types that this property can reference
// SAC 2/1/00 - no longer needed - handled within the first call to BEMPX_GetDatabaseID()
//      if (lRetVal < 0)
//         lRetVal = BEMPX_GetDatabaseID( sCondDBID );

      // SAC 3/4/99 - Added code to strip off second lDBID for accessing a referenced component's data
      lDBID2 = 0;
      if (iRefCompID > 0)  // lRetVal >= 1000000)
      {	int iError=0;
//         // get secondary class ID from highest order bits of m_lDBID
//         long lSecComp = lRetVal / 1000000;
//         // strip secondary class ID from highest order bits of m_lDBID to make the DBID valid
//         lRetVal = lRetVal % 1000000;

         // now remove leading property name
         ASSERT( sCondDBID.Find(':') > 0 );
         sCondDBID = sCondDBID.Right( sCondDBID.GetLength() - sCondDBID.Find(':') - 1 );

         // get secondary m_lDBID2
// SAC 6/15/12 - this is a particularly challenging mod related to expanding the number of object types a single property can reference
// this mod essentially processes nested DBIDs for each compatible referenced object type, taking into account (potentially) mulitple compatible referenced obejct types
         //lDBID2 = BEMPX_GetDatabaseID( sCondDBID, iRefCompID, FALSE, &iRefCompID );
			BOOL bDBIDValid = FALSE;
		   int i2ndRefCompID = iRefCompID;
			long l2ndDBID = lRetVal;
			BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( l2ndDBID, iError );						ASSERT( iError==0 );		ASSERT( pPropType );
			for (int iObjCls=0; (pPropType && !bDBIDValid && iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
			{	if (pPropType->getObj1ClassIdx(iObjCls) > 0)
				{	l2ndDBID = BEMPX_GetDatabaseID( sCondDBID, pPropType->getObj1ClassIdx(iObjCls), FALSE, &i2ndRefCompID );
					if (l2ndDBID > 0)
						bDBIDValid = TRUE;
				}
			}
			// update original variables, regardless of whether the processing successfully returned a valid DBID
			lDBID2 = l2ndDBID;
			iRefCompID = i2ndRefCompID;
      }

      if (lRetVal < 0 || lDBID2 < 0 || lDBID2 >= ((long) (BEMPX_GetNumClasses()+1) * BEM_COMP_MULT))  // 1000000)
      {
         CString sMsg;
         if (psSuppMsg)
            sMsg = psSuppMsg;
         if (psCondType)
            sMsg += psCondType;
         sMsg += " condition parameter";
            PostReadError( pPage, psCondDBID, sMsg, iLine );
      }
   }
   else
      lRetVal = 0;

   return lRetVal;
}


#define  NUM_COND_ERRS  5
const char* pszCondErr[] = { "first", "second", "third", "fourth", "fifth" };

BOOL CBEMCondition::Read( CTextIO& file, CBEMPUIPage* pPage, const char* psCondType )
{
   BOOL bRetVal = TRUE;

   // initialize before reading
   Init();

   // read first condition
   CString sCond, sAndOr;
   file.ReadBEMProcParam( sCond, TRUE );
   file.PostReadToken();
   if (sCond.CompareNoCase( "None" ) != 0)
   {
      // We HAVE at least a single condition
      BOOL bDone = FALSE;
	  int i=0;
      for (; (!bDone && i < MAX_BEM_CONDITIONS); i++)
      {
         m_iCondition[i] = file.ReadBEMCondition();
         file >> m_fConditionValue[i];
         m_lConditionalDBID[i] = GetConditionalDBID( sCond, m_iCondDBInstance[i], m_lCondDBID2[i], m_iCondition[i], pPage,
                                                     (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType, file.GetLineCount() );
         
         // SAC 7/1/98 - variation on PostReadToken() to catch AND or OR condition if one exists
         char ch;
         do
            ch = file.GetChr();
         while ( ch == ' ' ); // || ch == ',' ); 
         file.UnGetChr();
         if (ch == 'A' || ch == 'O')
         {
            file.ReadBEMProcParam( sAndOr );
            if (i == 0)
               m_bConditionsAND = (sAndOr.CompareNoCase( "AND" ) == 0);
            else if ( ( m_bConditionsAND && sAndOr.CompareNoCase( "AND" ) != 0) ||
                      (!m_bConditionsAND && sAndOr.CompareNoCase( "OR"  ) != 0) )
            {
               // ALL conditions must be alike!!
               CString sErrMsg;
               sErrMsg.Format( "incompatible %s%s condition operator", (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType );
               PostReadError( pPage, sAndOr, sErrMsg, file.GetLineCount() );
            }

            file.PostReadToken();

            // read start of next condition
            file.ReadBEMProcParam( sCond, TRUE );
            file.PostReadToken();
         }
         else
         {
            //ASSERT( (ch == ',') );
            // SAC 3/17/99 - replaced ASSERT (above) with the following error capture
            // SAC 10/19/02 - Added check to allow LF character following the condition
            if (ch != ',' && ch != 10)
            {
               // ALL conditions must be alike!!
               CString sErrMsg;
               sErrMsg.Format( "illegal character '%c' following the %s%s condition", ch, (i < NUM_COND_ERRS ? pszCondErr[i] : NULL), psCondType );
               PostReadError( pPage, NULL, sErrMsg, file.GetLineCount() );
            }

            bDone = TRUE;
         }
      }
      ASSERT( bDone );

      m_iNumConditions = i;
      file.PostReadToken();
   }

   return bRetVal;
}


BOOL BEMPUIX_BEMConditionMissingOrTrue( void* pBEMCondition, int iClass, int iOccur )   // SAC 3/9/18
{	BOOL bRetVal = TRUE;
	if (pBEMCondition)
	{	int i, iSaveInst[MAX_BEM_CONDITIONS];
		for (i=0; i < ((CBEMCondition*)pBEMCondition)->m_iNumConditions; i++)
		{	iSaveInst[i] = -99;
			if (((CBEMCondition*)pBEMCondition)->m_lConditionalDBID[i] > 0 &&
				 BEMPX_GetClassID( ((CBEMCondition*)pBEMCondition)->m_lConditionalDBID[i] ) == iClass)
			{	iSaveInst[i] = ((CBEMCondition*)pBEMCondition)->m_iCondDBInstance[i];
				((CBEMCondition*)pBEMCondition)->m_iCondDBInstance[i] = iOccur;
		}	}

		bRetVal = ((CBEMCondition*)pBEMCondition)->MissingOrTrue();

		for (i=0; i < ((CBEMCondition*)pBEMCondition)->m_iNumConditions; i++)
		{	if (iSaveInst[i] > -99)
				((CBEMCondition*)pBEMCondition)->m_iCondDBInstance[i] = iSaveInst[i];
	}	}
	return bRetVal;
}

BOOL CBEMCondition::MissingOrTrue()
{
   BOOL bRetVal = TRUE;
   if (m_iNumConditions == 0)
   {  }
   else if (m_iNumConditions == 1)
      bRetVal = BEMPX_ConditionTrue( m_lConditionalDBID[0] + m_lCondDBIDOffset[0], m_iCondition[0],
                                   m_fConditionValue[0], 0, m_iCondDBInstance[0], m_lCondDBID2[0] + m_lCondDBIDOffset2[0] );
   else
   {
      bRetVal = m_bConditionsAND;
      for (int i=0; (bRetVal == m_bConditionsAND && i<m_iNumConditions); i++)
      {
         BOOL bCond = BEMPX_ConditionTrue( m_lConditionalDBID[i] + m_lCondDBIDOffset[i], m_iCondition[i],
                                         m_fConditionValue[i], 0, m_iCondDBInstance[i], m_lCondDBID2[i] + m_lCondDBIDOffset2[i] );
         if (m_bConditionsAND && !bCond)
            bRetVal = FALSE;
         else if (!m_bConditionsAND && bCond)
            bRetVal = TRUE;
      }
   }

   return bRetVal;
}


void CBEMCondition::SetupDBIDOffsets( int iClassID, long lDBIDOffset )
{
   for (int i=0; i<m_iNumConditions; i++)
   {
      m_lCondDBIDOffset[ i] = (BEMPX_GetClassID( m_lConditionalDBID[i] ) == iClassID ? lDBIDOffset : 0);
      m_lCondDBIDOffset2[i] = ((m_lCondDBID2[i] > 0 && BEMPX_GetClassID( m_lCondDBID2[i] ) == iClassID) ? lDBIDOffset : 0);
   }
}

