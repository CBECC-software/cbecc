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

#ifndef __BEMPROCI_H__
#define __BEMPROCI_H__

#include "expTextIO.h"
#include "expCrypFile.h"
#include "BEMPropertyType.h"

// added to prevent any sort of windows dialog/UI during command line/batch/CLI processing - SAC 10/21/24
extern bool ebAllowWindowsUI;

// Function to resolve all object references following project or library data read
extern int  BEMP_ResolveAllReferences( BEM_ObjType eObjType=BEMO_User, QFile* pErrorFile=NULL,
													BOOL bPostErrors=TRUE, int iBEMProcIdx=-1,
													BOOL bSupressAllMessageBoxes=FALSE );

extern void BEMP_ResetRangeChecks();

extern long    BEMP_StringToLong(  QString& sLong );
extern double  BEMP_StringToFloat( QString& sFlt );

extern long ReadDBID( BEMTextIO& symFile );  //, CFile& errorFile );

extern double PolygonArea( std::vector<double>& faX, std::vector<double>& faY, std::vector<double>& faZ );
extern double PolygonArea_OrderDependent( std::vector<double>& faX, std::vector<double>& faY, std::vector<double>& faZ );

extern bool CheckRulesetFileVerAndReadID( CryptoFile& file, QString& sRuleSetID, QString& sRuleSetVersion,
														int& iStructVer, bool& bRulesetSecure );

extern void BEMP_InitializeDataTypes( int eCompDT = 3, bool bPrim = false, bool bEdit = true, bool bUserDef = true,
													bool bDispInp = true, bool bDispProp = true, bool bDispBudg = true,
													int iNotInputMode = DTNotInp_AllowUIReset, QString sNotInputMsg = "" );

// ruleset error externs
int  BEMP_GetRulesetErrorLocalClass( int i1ErrMsgIdx );
long BEMP_GetRulesetErrorLocalDBID(  int i1ErrMsgIdx );
bool BEMP_GetRulesetErrorLocalObjectName(   int i1ErrMsgIdx, char* pszObjName, int iBufferLen );
int  BEMP_GetRulesetErrorPrimaryClass(      int i1ErrMsgIdx );
bool BEMP_GetRulesetErrorPrimaryObjectName( int i1ErrMsgIdx, char* pszObjName, int iBufferLen );
bool BEMP_PopulateRulesetErrorMessage(      int i1ErrMsgIdx, QString& sErrMsg, bool bVerbose=FALSE );
void BEMP_AddRulesetErrorExt( const char* pszErrMsg, int iLocClass, long lLocDBID, const char* pszLocObjName,
										int iPrimClass=0, const char* pszPrimObjName=NULL );

extern void ExpCryptDecode( char* lpBuf, int length );
extern void ExpCryptEncode( char* lpBuf, int length );

extern void ResetConsDBIDs();		// SAC 9/29/20 - ensure DBIDs reset between each model (re-)load

#endif // __BEMPROCI_H__
