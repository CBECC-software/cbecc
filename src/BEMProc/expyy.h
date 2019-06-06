/* yy.h - Declares the interface between the yacc and c/cpp
 */
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

#ifndef YY_H
#define YY_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning (disable:4102)   /* disable unreferenced label warning */
#pragma warning (disable:4101)   /* disable unreferenced local variable warning */

extern int  yyparse();
extern int  yylex();
extern int  yyerror(const char*);

extern void ExpAddConstantNode(double value);
extern void ExpAddStringNode(void* object);
extern void ExpAddUnOpNode(int op);
extern void ExpAddBinOpNode(int op);
extern void ExpAddErrNode(int op);
extern void ExpAddKeyWordNode(long keyword);
extern void ExpAddBldgElemNode(long long dbId);
extern void ExpAddObjectNode(void* object, int tokenType);
extern void* ExpGetFuncTablePtrByOpType( int iOpType, int* pnArgs );  // SAC 7/13/12
extern const char* ExpGetFuncTableNameByOpType( int iOpType );  // SAC 8/31/16
extern void ExpAddFunctionNodeByOpType( int iOpType, int nArgs );  /* SAC 7/9/12 */
extern void ExpAddFunctionNode(void* func, int nArgs);  // SAC 2/25/19 - was: long function, int nArgs);
extern void ExpAddTableNode(long table, int nArgs);
extern void ExpAddRefFuncNode(void* func, int nArgs);  // SAC 2/25/19 - was: long function, int nArgs);
extern void ExpAddAddrNode(void* object, int tokenType);
extern void ExpAddBEMIndex(void* command, void* keyword, int tokenType);
extern void ExpAddControlNode(int tokenType);
extern void ExpAddVarArgString(void* object);
extern void ExpAddVarArgConst(double value);
extern void ExpPostParserMsg(const char* msg);

extern int  GetnArgs();
extern void AddnArg();
extern void PushnArgs();

#ifdef __cplusplus
}
#endif

#endif   /* YY_H */
