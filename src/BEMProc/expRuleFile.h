// expRuleFile.h - header file for RuleFile class definition
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
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#include "expTextIO.h"
#include "expRuleList.h"

extern void FormatMultilineString( QString& str );

/////////////////////////////////////////////////////////////////////////////
//	RuleFile
//    An instance of this class is created to import an ASCII ruleset.
/////////////////////////////////////////////////////////////////////////////

class RuleFile
{
public:
   enum { DataTypeList, RangesList, SymbolList, MaxChildList, ResetList, UniqueList, NListTypes };

public:
   RuleFile( QString& fileName, QStringList* pslAltPaths=NULL );
   ~RuleFile();

   bool Read( QFile& errorFile );
   bool ReadRuleList( int ruleListIndex, QFile& errorFile, int iFileStructVer, int i1RuleFileIndex=0,
   							BEMTextIO* pFile=NULL, const char* pszFileName=NULL, int iHardwireEnumStrVal=-1 );
   bool ReadTableList( QFile& errorFile );
   bool ReadListFile( QString sFileName, QFile& errorFile, int iListType );
	bool ReadRuleFile( const char* pszRulePathFile, QStringList& saReservedStrs,
								std::vector<RuleList*>& paTransformRulelists, QFile& errorFile,
								int iRuleFileReadIteration, int i1RuleFileIdx=0 );
	bool ReadRuleFile( const char* pszRulePathFileName, int i1RuleFileIdx, int& ruleListIndex,
								QFile& errorFile, int iFileStructVer );

   void ReadRuleID( QString& sId, int ruleListIndex, int ruleIndex,
   							BEMTextIO* pFile=NULL, const char* pszRuleFileName=NULL );
   void EnsureValidPath_AltPaths( QString sFileWithPath, QString& sFileToCheck );

private:
   BEMTextIO  m_file;
//   CPathName m_fileName;
	QString    m_fileName;
   QStringList  m_slFilePaths;    // SAC 08/06/21 (MFam)
};
