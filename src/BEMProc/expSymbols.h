// expSymbols.h - header file for SymLstList, SymLst, SymDepLst and Sym class definitions
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

#ifndef __EXPSYMBOLS_H__
#define __EXPSYMBOLS_H__

#include "expCrypFile.h"  
//#include "BEMTextIO.h"

/////////////////////////////////////////////////////////////////////////////
//	Sym
//    An instance of this class is created for each symbol definition
//    contained in the selected compliance ruleset.
/////////////////////////////////////////////////////////////////////////////

class Sym
{
public:
   Sym();
   Sym( const char* pszString, long iValue );
   ~Sym();

   long    m_iValue;    // numeric value of this symbol   - SAC 10/22/12 - int->long
   QString m_sString;   // symbol string to be displayed in drop-down listboxes for selection by user

public:
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


/////////////////////////////////////////////////////////////////////////////
//	SymDepLst
//    An instance of this class is created for each dependency list of
//    symbol definitions contained in the selected compliance ruleset.
/////////////////////////////////////////////////////////////////////////////

// SAC 7/21/05 - moved from CompileAscii to here & switched from 2 -> 3
#define  MAX_DEP_DBIDS_PER_LIST  3

class SymDepLst
{
public:
   SymDepLst( long iDefault=0 );
   ~SymDepLst();

   long     m_iDefaultValue;                        // numeric value of the default symbol
   int      m_iNumDepDBIDs;                         // the number of dependencies (0-2)
   long     m_lDBID[     MAX_DEP_DBIDS_PER_LIST ];  // lDBID of up to two dependencies
   double   m_fDepValue[ MAX_DEP_DBIDS_PER_LIST ];  // floating point values for dependency check(s)
   std::vector<Sym*>  m_olSymbols;                  // list of Sym

public:
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


/////////////////////////////////////////////////////////////////////////////
//	SymLst
//    An instance of this class is created for each list of symbol dependency
//    list for a single set of lDBIDs.
/////////////////////////////////////////////////////////////////////////////

#define  MAX_DBIDS_PER_LIST  5

class SymLst
{
public:
   SymLst();
   ~SymLst();

   int      m_iNumDBIDs;                    // the number of DBIDs (1-MAX_DBIDS_PER_LIST)
   long     m_lDBID[ MAX_DBIDS_PER_LIST ];  // lDBIDs which this symbol list describe
   std::vector<SymDepLst*>  m_olSymDepLists;                // list of SymDepLst

public:
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


// /////////////////////////////////////////////////////////////////////////////
// //	SymLstList
// //    An instance of this class is created for each list of symbol
// //    definitions.  For now, there is only one such list for each ruleset.
// /////////////////////////////////////////////////////////////////////////////
// 
// class SymLstList
// {
// public: 
//    ~SymLstList();
//    void RemoveAll();
// 
//    bool ReadText( QString sFileName, QFile& errorFile );
//    bool Read( CryptoFile& file ); 
//    bool Write( CryptoFile& file );
// 
//    bool PostSymbolsToDatabase();
// 
// private:
// 	std::vector<SymLst*>  m_symLists;
// };
// 
// /////////////////////////////////////////////////////////////////////////////

#endif // __EXPSYMBOLS_H__
