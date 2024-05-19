/* BEMCondition.h
*/
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
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#ifndef __BEMCONDITION_H__
#define __BEMCONDITION_H__

#include "textio.h"

struct CBEMPUIPage;

///////////////////////////////////////////////////////////////
// CBEMCondition
///////////////////////////////////////////////////////////////

#define  MAX_BEM_CONDITIONS  10    // 5->10 - SAC 07/26/21

struct CBEMCondition
{
   // Constructor
   CBEMCondition();

   // Data
   int    m_iNumConditions;
   BOOL   m_bConditionsAND;

   long   m_lConditionalDBID[ MAX_BEM_CONDITIONS ];
   int    m_iCondition[       MAX_BEM_CONDITIONS ];
   float  m_fConditionValue[  MAX_BEM_CONDITIONS ];

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   long   m_lCondDBIDOffset[  MAX_BEM_CONDITIONS ];

   // SAC 3/3/99 - added to enable specific DB class instance references
   int    m_iCondDBInstance[  MAX_BEM_CONDITIONS ];

   // SAC 3/4/99 - Added second array of DBIDs to enable access to referenced component data
   long   m_lCondDBID2[       MAX_BEM_CONDITIONS ];
   long   m_lCondDBIDOffset2[ MAX_BEM_CONDITIONS ];

   // Functions
   void   Init();
   BOOL   Read( CTextIO& file, CBEMPUIPage* pPage, const char* psCondType );
   BOOL   MissingOrTrue();
   BOOL   Present();

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   void SetupDBIDOffsets( int iClassID, long lDBIDOffset );
};

inline BOOL CBEMCondition::Present()
   {  return (m_iNumConditions > 0);  }


#endif
