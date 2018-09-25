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

#ifndef __EXPRULE_H__
#define __EXPRULE_H__

#include "expRuleList.h"

// SAC 5/21/01 - added pointers to string arrays to facilitate detailed, rule-based BEMProc error/range checking
extern QStringList* pssaErrorMsgs;
extern QStringList* pssaWarningMsgs;

extern int GetValue( ExpNode* result, const ExpNode* node, void* data );

extern void BEMPFunction( ExpStack* stack, int op, int nArgs,
                          void* pEvalData, ExpError* error );

extern bool LocalSetBEMProcData( ExpEvalStruct* pEval, BOOL bTagDataAsUserDefined,
                                 BOOL bPerformSetBEMDataResets, ExpNode& node, ExpError& expError );

//////////////////////////////////////////////////////////////////////
// These functions declared as exported in order to facilitate passing a pointer
// to it into one or more expression DLL functions.
int __declspec(dllexport) __cdecl GetNodeType( const char* name, int* pVar, int crntFunc, void* data );
int __declspec(dllexport) __cdecl SelectFunctionByArgument( const char* name, int crntFunc, ExpError* pError );  // SAC 6/3/13 - added pError argument
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// CCompID Class code - this class tracks the current component ID
class CCompID
{
public:
   int GetCurrentCompID();
   void SetCurrentCompID( int id );

   long GetCurrentLocalDBID();
   void SetCurrentLocalDBID( long lDBID );

   void GetCurrentRulelistName( QString& sRLName );
   void SetCurrentRulelistName( const char* pszRLName );

private:
   int  m_currentID;
	long m_lLocalDBID;	// SAC 7/9/12
	QString m_sRulelistName;	// SAC 9/25/13
};

extern CCompID crntCompID;  // declare an instance of this class which will be referenced throughout this module
//////////////////////////////////////////////////////////////////////

extern QString ScheduleSum( int iNumScheds, QString sSchNamePrefix, ExpNode** pNodeList, void* pEvalData, ExpError* pError );

//////////////////////////////////////////////////////////////////////

#endif // __EXPRULE_H__
