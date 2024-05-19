// Reset.h - header file for  CResetLst and CResetLstList class definitions
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1998, Regional Economic Research, Inc. and         */
/*                      SAC Software                                 */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#ifndef __RESET_H__
#define __RESET_H__

#include "expCrypFile.h"  
#include "expTextIO.h"

/////////////////////////////////////////////////////////////////////////////
//	BEMResetData
//    An instance of this class is created for each list of reset definitions
//    for a single set of lDBIDs.
/////////////////////////////////////////////////////////////////////////////

//#define  MAX_DBIDS_PER_LIST  5

class BEMResetData
{
public:
   BEMResetData()		{	}
   ~BEMResetData()	{	}

   std::vector<long>  m_modDBIDs;
   std::vector<long>  m_resetDBIDs;

public:
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


//	/////////////////////////////////////////////////////////////////////////////
//	//	CResetLstList
//	//    An instance of this class is created for each list of reset
//	//    definitions.  For now, there is only one such list for each ruleset.
//	/////////////////////////////////////////////////////////////////////////////
//	
//	class CResetLstList : public CObList
//	{
//	public: 
//	   ~CResetLstList();
//	   void RemoveAll();
//	
//	   bool ReadText( CString sFileName, CFile& errorFile );
//	   bool Read( CCryptoFile& file ); 
//	   bool Write( CCryptoFile& file );
//	};


/////////////////////////////////////////////////////////////////////////////

#endif // __RESET_H__
