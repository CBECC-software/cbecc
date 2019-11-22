// formula.c
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

#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>     /* strtod */
#include <cfloat>  /* DBL_EPSILON */

#include "expFormula.h"
#include "memLkRpt.h"

#define ISFLOATCHAR(c) (isdigit(c)||(c)=='.')
#define ISNAMECHAR(c)  (isalnum(c)||(c)=='_'||(c)=='#')

#define CLEARERROR(e) (((e)->code=EXP_None),((e)->string[0]='\0'))

//static inline int WithinMarginLoc(double d1, double d2, double d3)
//   {	return (d1 < (d2+d3) && d1 > (d2-d3)); }
//static inline int IsReserved_UNDEFINED( double dVal )
//   {	return WithinMarginLoc( dVal, -99996.0, 0.01 );  };
#define IsReserved_UNDEFINED(d)  (d < -99995.99 && d > -99996.01)

extern int yyparse();               /* in parser.y */
extern void PushnArgs();

#pragma warning(disable : 4996)

/********************************************************************/
/* These 4 are not in the unix libraries so I implemented them here */
/********************************************************************/
static int stricmp_( const char* str1, const char * str2 )
{
   while( *str1 != '\0' && *str2 != '\0' && *str1 == *str2 )
   {
      str1++;
      str2++;
   }
   return( *str2 - *str1 );
}

//static int strnicmp_( const char* str1, const char * str2, int count )
//{
//   while( *str1 != '\0' && *str2 != '\0' && *str1 == *str2 && count )
//   {
//      str1++;
//      str2++;
//      count--;
//   }
//   return( !count ? 0 : *str2 - *str1 );
//}

static void strlwr_( char* str )
{
   while( *str != '\0' )
   {
      if ( *str >= 'A' && *str <= 'Z' )
         *str += 'a' - 'A';
      str++;
   }
}

static void strupr_( char* str )
{
   while( *str != '\0' )
   {
/* SAC 12/26/02 - Fixed bug in evaluation logic causing lowercase letters to be left alone and upper case to get shifted to bogus values */
/*      if ( *str >= 'A' && *str <= 'Z' ) */
      if ( *str >= 'a' && *str <= 'z' )
         *str -= 'a' - 'A';
      str++;
   }
}
/********************************************************************/


/* Here's a little stack for keeping track of nested functions */
typedef struct Nargs  
{
   int nArgs;
   struct Nargs* next;
} Nargs;

static struct Nargs* topNarg;

typedef struct functable_
{
   char *name;
   int   evaluate;
   int   op;
   int   nArgs;
} FuncTable;

typedef struct
{
   char*       tokenString;
   int         opCode;
   ExpNodeType nodeType;
} OperatorTable;

static OperatorTable controlOps[] =
{
   { "if",        IFF,       EXP_If        },
   { "then",      THEN,      0             },
   { "else",      ELSE,      EXP_Else      },
   { "endif",     ENDIF,     EXP_Endif     },
   { "switch",    SWITCH,    EXP_Switch    },
   { "case",      CASE,      EXP_Case      },
   { "default",   DEFAULT,   EXP_Default   },
   { "endswitch", ENDSWITCH, EXP_EndSwitch },
   { "IF",        IFF,       EXP_If        },
   { "THEN",      THEN,      0             },
   { "ELSE",      ELSE,      EXP_Else      },
   { "ENDIF",     ENDIF,     EXP_Endif     },
   { "SWITCH",    SWITCH,    EXP_Switch    },
   { "CASE",      CASE,      EXP_Case      },
   { "DEFAULT",   DEFAULT,   EXP_Default   },
   { "ENDSWITCH", ENDSWITCH, EXP_EndSwitch },
   { "If",        IFF,       EXP_If        },
   { "Then",      THEN,      0             },
   { "Else",      ELSE,      EXP_Else      },
   { "EndIf",     ENDIF,     EXP_Endif     },
   { "Switch",    SWITCH,    EXP_Switch    },
   { "Case",      CASE,      EXP_Case      },
   { "Default",   DEFAULT,   EXP_Default   },
   { "EndSwitch", ENDSWITCH, EXP_EndSwitch },
   { NULL,        0,         0             }
};

static void UnaryFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error );
static void BinaryFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error );
static void ErrorFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error );
static void BEMPFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error );
static void TableLookup( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error );

static FuncTable functable[] =
{
   { "log",      EXP_Unary,     OP_Log,      1 },
   { "exp",      EXP_Unary,     OP_Exp,      1 },
   { "pow",      EXP_Binary,    OP_Pow,      2 }, 
   { "abs",      EXP_Unary,     OP_Abs,      1 }, 
   { "strupper", EXP_Unary,     OP_Upr,      1 }, 
   { "strlower", EXP_Unary,     OP_Lwr,      1 }, 
   { "min",      EXP_Binary,    OP_Min,      2 }, 
   { "max",      EXP_Binary,    OP_Max,      2 }, 
   { "int",      EXP_Unary,     OP_Int,      1 }, 
   { "log10",    EXP_Unary,     OP_Log10,    1 }, 
   { "sin",      EXP_Unary,     OP_Sin,      1 },
   { "asin",     EXP_Unary,     OP_ASin,     1 },
   { "cos",      EXP_Unary,     OP_Cos,      1 },
   { "acos",     EXP_Unary,     OP_ACos,     1 },
   { "tan",      EXP_Unary,     OP_Tan,      1 },
   { "atan",     EXP_Unary,     OP_ATan,     1 },
   { "sqrt",     EXP_Unary,     OP_Sqrt,     1 },
   { "ftoa",     EXP_Unary,     OP_Ftoa,     1 },
   { "mod",      EXP_Binary,    OP_Mod,      2 },  /* SAC 2/18/01 - added mod() function */
   { "strlen",   EXP_Unary,     OP_SLen,     1 },  /* SAC 2/11/03 - added strlen() function */
   { "find",     EXP_Binary,    OP_Find,     2 },  /* SAC 2/4/13 - added find() function */
   { "findnocase", EXP_Binary,  OP_FindN,    2 },  /* SAC 2/4/13 - added findnocase() function */
   { "atof",     EXP_Unary,     OP_Atof,     1 },  /* SAC 2/23/16 - added atof() */
   { "round",    EXP_Binary,    OP_Round,    2 },  /* SAC 11/13/17 - added round() - round to specified digits */

   { "error",    EXP_ErrorFunc, OP_ErrorExp, 3 },
   { "#E",       EXP_ErrorFunc, OP_ErrorExp, 3 },

//   /* BEMProc functions */
//   { "RefIndex",  EXP_BEMPFunc, BF_RefIndex,  0 },
//   { "#RI",       EXP_BEMPFunc, BF_RefIndex,  0 },
//   { "SymIndex",  EXP_BEMPFunc, BF_SymIndex,  1 },
//   { "#SI",       EXP_BEMPFunc, BF_SymIndex,  1 },
   { "SymValue",                   EXP_BEMPFunc, BF_SymValue,    1 },
   {                "#SV",         EXP_BEMPFunc, BF_SymValue,    1 },
   { "SumAll",                     EXP_BEMPFunc, BF_SumAll,      1 },
   {                "#SA",         EXP_BEMPFunc, BF_SumAll,      1 },
   { "ChildCount",                 EXP_BEMPFunc, BF_ChildCnt,    1 },
   {                "#CC",         EXP_BEMPFunc, BF_ChildCnt,    1 },
   { "RuleLibrary",                EXP_BEMPFunc, BF_RuleLib,     VAR_ARGS },  /* SAC 3/9/13 - switched from 2 fixed to variable (2-3) args */
   {                "#RL",         EXP_BEMPFunc, BF_RuleLib,     VAR_ARGS },  /* SAC 3/9/13 - switched from 2 fixed to variable (2-3) args */
   { "ChildRef",                   EXP_BEMPFunc, BF_ChildRef,    2 },
   {                "#CR",         EXP_BEMPFunc, BF_ChildRef,    2 },
   { "Parent",                     EXP_BEMPFunc, BF_Parent,      VAR_ARGS },
   {                "#P",          EXP_BEMPFunc, BF_Parent,      VAR_ARGS },
   { "Parent2",                    EXP_BEMPFunc, BF_Parent2,     VAR_ARGS },
   {                "#P2",         EXP_BEMPFunc, BF_Parent2,     VAR_ARGS },
   { "Parent3",                    EXP_BEMPFunc, BF_Parent3,     VAR_ARGS },
   {                "#P3",         EXP_BEMPFunc, BF_Parent3,     VAR_ARGS },
   { "Local",                      EXP_BEMPFunc, BF_Local,       VAR_ARGS },
   {                "#L",          EXP_BEMPFunc, BF_Local,       VAR_ARGS },
   { "Global",                     EXP_BEMPFunc, BF_Global,      VAR_ARGS },
   {                "#G",          EXP_BEMPFunc, BF_Global,      VAR_ARGS },
   { "SumChildren",                EXP_BEMPFunc, BF_SumChld,     VAR_ARGS },
   {                "#SC",         EXP_BEMPFunc, BF_SumChld,     VAR_ARGS },
   { "LocalRef",                   EXP_BEMPFunc, BF_LocalRef,    VAR_ARGS },
   {                "#LR",         EXP_BEMPFunc, BF_LocalRef,    VAR_ARGS },
   { "ParentRef",                  EXP_BEMPFunc, BF_ParentRef,   VAR_ARGS },
   {                "#PR",         EXP_BEMPFunc, BF_ParentRef,   VAR_ARGS },
   { "Parent2Ref",                 EXP_BEMPFunc, BF_Parent2Ref,  VAR_ARGS },
   {                "#PR2",        EXP_BEMPFunc, BF_Parent2Ref,  VAR_ARGS },
   { "Parent3Ref",                 EXP_BEMPFunc, BF_Parent3Ref,  VAR_ARGS },
   {                "#PR3",        EXP_BEMPFunc, BF_Parent3Ref,  VAR_ARGS },
   { "SumRevRef",                  EXP_BEMPFunc, BF_SumRevRef,   VAR_ARGS },
   {                "#SR",         EXP_BEMPFunc, BF_SumRevRef,   VAR_ARGS },
   { "MaxChild",                   EXP_BEMPFunc, BF_MaxChild,    VAR_ARGS },
   {                "#MC",         EXP_BEMPFunc, BF_MaxChild,    VAR_ARGS },
   { "MaxAll",                     EXP_BEMPFunc, BF_MaxAll,      VAR_ARGS },
   {                "#MA",         EXP_BEMPFunc, BF_MaxAll,      VAR_ARGS },
   { "MaxRevRef",                  EXP_BEMPFunc, BF_MaxRevRef,   VAR_ARGS },
   {                "#MR",         EXP_BEMPFunc, BF_MaxRevRef,   VAR_ARGS },
   { "CurrentTime",                EXP_BEMPFunc, BF_CurTime,     0 },
   {                "#CT",         EXP_BEMPFunc, BF_CurTime,     0 },
   { "Date",                       EXP_BEMPFunc, BF_Date,        3 },
   {                "#D",          EXP_BEMPFunc, BF_Date,        3 },
   { "EnsureSymbolExists",         EXP_BEMPFunc, BF_CheckSym,    0 },
   {                "#ESE",        EXP_BEMPFunc, BF_CheckSym,    0 },
   { "EvalRulelist",               EXP_BEMPFunc, BF_EvalRules,   VAR_ARGS },  /* SAC 5/26/00 - switched from 1 fixed to variable (1 - 2) args */
   {                "#ER",         EXP_BEMPFunc, BF_EvalRules,   VAR_ARGS },  /* SAC 5/26/00 - switched from 1 fixed to variable (1 - 2) args */
   { "CreateChildren",             EXP_BEMPFunc, BF_Cr8Child,    VAR_ARGS },  /* SAC 5/26/00 - switched from 4 fixed to variable (3 - 5) args */
   {                "#CCH",        EXP_BEMPFunc, BF_Cr8Child,    VAR_ARGS },  /* SAC 5/26/00 - switched from 4 fixed to variable (3 - 5) args */
   { "DeleteChildren",             EXP_BEMPFunc, BF_DelChild,    VAR_ARGS },  /* SAC 5/26/00 - switched from 2 fixed to variable (1 - 3) args */
   {                "#DCH",        EXP_BEMPFunc, BF_DelChild,    VAR_ARGS },  /* SAC 5/26/00 - switched from 2 fixed to variable (1 - 3) args */
   { "CreateComp",                 EXP_BEMPFunc, BF_Cr8Comp,     VAR_ARGS },  /* SAC 5/26/00 - switched from 3 fixed to variable (2 - 4) args */ /* SAC 11/19/14 ->5 args */
   {                "#CCO",        EXP_BEMPFunc, BF_Cr8Comp,     VAR_ARGS },  /* SAC 5/26/00 - switched from 3 fixed to variable (2 - 4) args */ /* SAC 11/19/14 ->5 args */
   { "DeleteComp",                 EXP_BEMPFunc, BF_DelComp,     VAR_ARGS },  /* SAC 5/26/00 - switched from 1 fixed to variable (0 - 2) args */
   {                "#DCO",        EXP_BEMPFunc, BF_DelComp,     VAR_ARGS },  /* SAC 5/26/00 - switched from 1 fixed to variable (0 - 2) args */
   { "DeleteAllComps",             EXP_BEMPFunc, BF_DelAllComps, VAR_ARGS },  /* SAC 5/26/00 - switched from 2 fixed to variable (1 - 3) args */
   {                "#DAC",        EXP_BEMPFunc, BF_DelAllComps, VAR_ARGS },  /* SAC 5/26/00 - switched from 2 fixed to variable (1 - 3) args */
   { "StoreBDBase",                EXP_BEMPFunc, BF_StoreBEMProc, 2 },          // retain for backward compatible      
   { "StoreBEMProc",               EXP_BEMPFunc, BF_StoreBEMProc, 2 },          // reflects BDBase->BEMProc name change
   {                "#SB",         EXP_BEMPFunc, BF_StoreBEMProc, 2 },
   { "LocalCompAssigned",          EXP_BEMPFunc, BF_LCompAssign, VAR_ARGS },
   {                "#LCA",        EXP_BEMPFunc, BF_LCompAssign, VAR_ARGS },
   { "ParentCompAssigned",         EXP_BEMPFunc, BF_PCompAssign, VAR_ARGS },
   {                "#PCA",        EXP_BEMPFunc, BF_PCompAssign, VAR_ARGS },
   { "LocalIsDefault",             EXP_BEMPFunc, BF_LIsDefault,  VAR_ARGS },
   {                "#LID",        EXP_BEMPFunc, BF_LIsDefault,  VAR_ARGS },
   { "ParentIsDefault",            EXP_BEMPFunc, BF_PIsDefault,  VAR_ARGS },
   {                "#PID",        EXP_BEMPFunc, BF_PIsDefault,  VAR_ARGS },
   { "CurrentYear",                EXP_BEMPFunc, BF_CurYear,     0 },
   {                "#CY",         EXP_BEMPFunc, BF_CurYear,     0 },
   { "MinChild",                   EXP_BEMPFunc, BF_MinChild,    VAR_ARGS },
   {                "#MIC",        EXP_BEMPFunc, BF_MinChild,    VAR_ARGS },
   { "MinAll",                     EXP_BEMPFunc, BF_MinAll,      VAR_ARGS },
   {                "#MIA",        EXP_BEMPFunc, BF_MinAll,      VAR_ARGS },
   { "MinRevRef",                  EXP_BEMPFunc, BF_MinRevRef,   VAR_ARGS },
   {                "#MIR",        EXP_BEMPFunc, BF_MinRevRef,   VAR_ARGS },
   { "FltToStr",                   EXP_BEMPFunc, BF_FltToStr,    VAR_ARGS },  /* SAC  2/ 8/01 - Added new function -- 2/28/01 - switched to VAR_ARGS */
   {                "#F2S",        EXP_BEMPFunc, BF_FltToStr,    VAR_ARGS },  /* SAC  2/ 8/01 - Added new function */ 
   { "LocalSymbolString",          EXP_BEMPFunc, BF_LocSymStr,   VAR_ARGS },  /* SAC  2/ 8/01 - Added new function */ 
   {                "#LSS",        EXP_BEMPFunc, BF_LocSymStr,   VAR_ARGS },  /* SAC  2/ 8/01 - Added new function */ 
   { "ComponentIndex",             EXP_BEMPFunc, BF_CompIdx,     VAR_ARGS },  /* SAC  2/27/01 - Added new function -- 11/14/16 - switched to VAR_ARGS */
   {                "#COI",        EXP_BEMPFunc, BF_CompIdx,     VAR_ARGS },  /* SAC  2/27/01 - Added new function -- 11/14/16 - switched to VAR_ARGS */
   { "ChildIndex",                 EXP_BEMPFunc, BF_ChildIdx,    VAR_ARGS },  /* SAC  2/27/01 - Added new function -- 11/26/02 - switched to VAR_ARGS */
   {                "#CHI",        EXP_BEMPFunc, BF_ChildIdx,    VAR_ARGS },  /* SAC  2/27/01 - Added new function -- 11/26/02 - switched to VAR_ARGS */
   { "Format",                     EXP_BEMPFunc, BF_Format,      VAR_ARGS },  /* SAC  5/11/01 - added */
   {                "#FMT",        EXP_BEMPFunc, BF_Format,      VAR_ARGS },  /* SAC  5/11/01 - added */
   { "LocalStatus",                EXP_BEMPFunc, BF_LocStatus,   VAR_ARGS },  /* SAC  5/16/01 - added */
   {                "#LST",        EXP_BEMPFunc, BF_LocStatus,   VAR_ARGS },  /* SAC  5/16/01 - added */
   { "ParentStatus",               EXP_BEMPFunc, BF_ParStatus,   VAR_ARGS },  /* SAC  5/16/01 - added */
   {                "#PST",        EXP_BEMPFunc, BF_ParStatus,   VAR_ARGS },  /* SAC  5/16/01 - added */
   { "PostError",                  EXP_BEMPFunc, BF_PostError,   VAR_ARGS },  /* SAC  5/21/01 - added */
   {                "#PE",         EXP_BEMPFunc, BF_PostError,   VAR_ARGS },  /* SAC  5/21/01 - added */
   { "PostWarning",                EXP_BEMPFunc, BF_PostWarn,    VAR_ARGS },  /* SAC  5/21/01 - added */
   {                "#PW",         EXP_BEMPFunc, BF_PostWarn,    VAR_ARGS },  /* SAC  5/21/01 - added */
   { "CompExists",                 EXP_BEMPFunc, BF_CompExists,  2 },         /* SAC  7/ 6/01 - added */
   {                "#CE",         EXP_BEMPFunc, BF_CompExists,  2 },         /* SAC  7/ 6/01 - added */
   { "GlobalSymbolString",         EXP_BEMPFunc, BF_GlobSymStr,  VAR_ARGS },  /* SAC  7/25/01 - added */
   {                "#GSS",        EXP_BEMPFunc, BF_GlobSymStr,  VAR_ARGS },  /* SAC  7/25/01 - added */
   { "GlobalStatus",               EXP_BEMPFunc, BF_GlobStatus,  VAR_ARGS },  /* SAC  8/24/01 - added */
   {                "#GST",        EXP_BEMPFunc, BF_GlobStatus,  VAR_ARGS },  /* SAC  8/24/01 - added */
   { "CountRefs",                  EXP_BEMPFunc, BF_CountRefs,   VAR_ARGS },  /* SAC  1/ 3/02 - added */
   {                "#CRS",        EXP_BEMPFunc, BF_CountRefs,   VAR_ARGS },  /* SAC  1/ 3/02 - added */
   { "CompName",                   EXP_BEMPFunc, BF_CompName,    2 },         /* SAC  1/ 3/02 - added */
   {                "#CN",         EXP_BEMPFunc, BF_CompName,    2 },         /* SAC  1/ 3/02 - added */
   { "CountUniqueParentRefs",      EXP_BEMPFunc, BF_CountUPRefs, VAR_ARGS },  /* SAC  1/ 4/02 - added */
   {                "#CUPRS",      EXP_BEMPFunc, BF_CountUPRefs, VAR_ARGS },  /* SAC  1/ 4/02 - added */
   { "CountNoRefs",                EXP_BEMPFunc, BF_CountNoRefs, VAR_ARGS },  /* SAC  1/ 4/02 - added */
   {                "#CNRS",       EXP_BEMPFunc, BF_CountNoRefs, VAR_ARGS },  /* SAC  1/ 4/02 - added */
   { "MaxRevRefComp",              EXP_BEMPFunc, BF_MaxRevRefC,  VAR_ARGS },  /* SAC  1/ 9/02 - added */
   {                "#MRC",        EXP_BEMPFunc, BF_MaxRevRefC,  VAR_ARGS },  /* SAC  1/ 9/02 - added */
   { "MaxAllComp",                 EXP_BEMPFunc, BF_MaxAllComp,  VAR_ARGS },  /* SAC  1/24/02 - added */
   {                "#MAC",        EXP_BEMPFunc, BF_MaxAllComp,  VAR_ARGS },  /* SAC  1/24/02 - added */
   { "ComponentCount",             EXP_BEMPFunc, BF_CompCnt,     1 },         /* SAC  4/ 1/02 - added */
   {                "#CMPC",       EXP_BEMPFunc, BF_CompCnt,     1 },         /* SAC  4/ 1/02 - added */
   { "FirstBitwiseMatchComp",      EXP_BEMPFunc, BF_BitMatchCmp, VAR_ARGS },  /* SAC  4/ 2/02 - added */
   {                "#FBMC",       EXP_BEMPFunc, BF_BitMatchCmp, VAR_ARGS },  /* SAC  4/ 2/02 - added */
   { "BitwiseMatchCount",          EXP_BEMPFunc, BF_BitMatchCnt, VAR_ARGS },  /* SAC  4/ 2/02 - added */
   {                "#BMC",        EXP_BEMPFunc, BF_BitMatchCnt, VAR_ARGS },  /* SAC  4/ 2/02 - added */
   { "UniqueComponentName",        EXP_BEMPFunc, BF_UnqCompName, VAR_ARGS },  /* SAC  4/ 9/02 - added */
   {                "#UCN",        EXP_BEMPFunc, BF_UnqCompName, VAR_ARGS },  /* SAC  4/ 9/02 - added */
   { "EnsureStringUniqueness",     EXP_BEMPFunc, BF_StrUnique,   VAR_ARGS },  /* SAC  8/25/03 - added */
   {                "#ESU",        EXP_BEMPFunc, BF_StrUnique,   VAR_ARGS },  /* SAC  8/25/03 - added */
   { "FileExists",                 EXP_BEMPFunc, BF_FileExists,  1 },         /* SAC  1/ 6/04 - added */
   {                "#FE",         EXP_BEMPFunc, BF_FileExists,  1 },         /* SAC  1/ 6/04 - added */
   { "ImportComponentFromFile",    EXP_BEMPFunc, BF_ImportComp,  VAR_ARGS },  /* SAC  1/ 6/04 - added */
   {                "#ICFF",       EXP_BEMPFunc, BF_ImportComp,  VAR_ARGS },  /* SAC  1/ 6/04 - added */
   { "EnsureChildAssigned",        EXP_BEMPFunc, BF_EnsureChild, 0 },         /* SAC  4/27/04 - added */
   {                "#ECA",        EXP_BEMPFunc, BF_EnsureChild, 0 },         /* SAC  4/27/04 - added */
   { "SplitPath",                  EXP_BEMPFunc, BF_SplitPath,   2 },         /* SAC  11/5/04 - added */
   {                "#SP",         EXP_BEMPFunc, BF_SplitPath,   2 },         /* SAC  11/5/04 - added */
   { "MaxRevRefArray",             EXP_BEMPFunc, BF_MaxRevRefA,  VAR_ARGS },  /* SAC 11/10/04 - added */
   {                "#MRA",        EXP_BEMPFunc, BF_MaxRevRefA,  VAR_ARGS },  /* SAC 11/10/04 - added */
   { "CountOccurrences",           EXP_BEMPFunc, BF_CountOccur,  2 },         /* SAC 9/28/07 - added */
   {                "#CO",         EXP_BEMPFunc, BF_CountOccur,  2 },         /* SAC 9/28/07 - added */
   { "SumIntoArrayElement",        EXP_BEMPFunc, BF_SumToArray,  3 },         /* SAC 9/28/07 - added */
   {                "#SIA",        EXP_BEMPFunc, BF_SumToArray,  3 },         /* SAC 9/28/07 - added */
   { "SumRevRefEx",                EXP_BEMPFunc, BF_SumRevRefEx, VAR_ARGS },  /* SAC 9/28/07 - added */
   {                "#SRE",        EXP_BEMPFunc, BF_SumRevRefEx, VAR_ARGS },  /* SAC 9/28/07 - added */
   { "LocalSymbolInvalid",         EXP_BEMPFunc, BF_LocSymInv,   VAR_ARGS },  /* SAC 9/28/07 - added */ 
   {                "#LSI",        EXP_BEMPFunc, BF_LocSymInv,   VAR_ARGS },  /* SAC 9/28/07 - added */ 
   { "MessageBox",                 EXP_BEMPFunc, BF_MsgBox,      VAR_ARGS },  /* SAC 9/29/06 - added */
   {                "#MBX",        EXP_BEMPFunc, BF_MsgBox,      VAR_ARGS },  /* SAC 9/29/06 - added */
   { "GlobalRef",                  EXP_BEMPFunc, BF_GlobalRef,   VAR_ARGS },  /* SAC 9/28/07 - added */
   {                "#GR",         EXP_BEMPFunc, BF_GlobalRef,   VAR_ARGS },  /* SAC 9/28/07 - added */
   { "BDBaseDBID",                 EXP_BEMPFunc, BF_BEMProcDBID, 3 },         /* SAC 6/14/07 - added */   // retain for backward compatible
   { "BEMProcDBID",                EXP_BEMPFunc, BF_BEMProcDBID, 3 },         /* SAC 6/14/07 - added */   // reflects BDBase->BEMProc name change
   {                "#DBID",       EXP_BEMPFunc, BF_BEMProcDBID, 3 },         /* SAC 6/14/07 - added */
   { "PostMessageToLog",           EXP_BEMPFunc, BF_PostLogMsg,  VAR_ARGS },  /* SAC 10/30/07 - added */
   {                "#PM2L",       EXP_BEMPFunc, BF_PostLogMsg,  VAR_ARGS },  /* SAC 10/30/07 - added */
   { "FindInString",               EXP_BEMPFunc, BF_FindInStr,   2 },         /* SAC 7/2/09 - added */
   {                "#FIS",        EXP_BEMPFunc, BF_FindInStr,   2 },         /* SAC 7/2/09 - added */
   { "ReplaceInString",            EXP_BEMPFunc, BF_RplcInStr,   2 },         /* SAC 11/20/09 - added */
   {                "#RIS",        EXP_BEMPFunc, BF_RplcInStr,   2 },         /* SAC 11/20/09 - added */
   { "LocalMaxStringLength",       EXP_BEMPFunc, BF_LocMxStrLen, VAR_ARGS },  /* SAC 11/20/09 - added */
   {                "#LMSL",       EXP_BEMPFunc, BF_LocMxStrLen, VAR_ARGS },  /* SAC 11/20/09 - added */
   { "ParentStringArrayElement",   EXP_BEMPFunc, BF_ParStrAElem, 2 },         /* SAC 11/20/09 - added */
   {                "#PSAE",       EXP_BEMPFunc, BF_ParStrAElem, 2 },         /* SAC 11/20/09 - added */
   { "ParentComponentType",        EXP_BEMPFunc, BF_ParCompType, 0 },         /* SAC 2/16/10 - added */
   {                "#PCT",        EXP_BEMPFunc, BF_ParCompType, 0 },         /* SAC 2/16/10 - added */
   { "LocalArrayIndex",            EXP_BEMPFunc, BF_LocArrIdx,   4 },         /* SAC 3/3/10 - added */
   {                "#LAI",        EXP_BEMPFunc, BF_LocArrIdx,   4 },         /* SAC 3/3/10 - added */
   { "ComponentArray",             EXP_BEMPFunc, BF_CompArray,   VAR_ARGS },  /* SAC 3/7/11 - added */
   {                 "#CA",        EXP_BEMPFunc, BF_CompArray,   VAR_ARGS },  /* SAC 3/7/11 - added */
   { "GlobalCompAssigned",         EXP_BEMPFunc, BF_GCompAssign, VAR_ARGS },  /* SAC 5/12/12 - added */
   {                "#GCA",        EXP_BEMPFunc, BF_GCompAssign, VAR_ARGS },  /* SAC 5/12/12 - added */
   { "HourlyResultSum",            EXP_BEMPFunc, BF_HrlyResSum, VAR_ARGS },   /* SAC 5/15/12 - added */
   {                "#HRS",        EXP_BEMPFunc, BF_HrlyResSum, VAR_ARGS },   /* SAC 5/15/12 - added */
   { "ApplyHourlyResultMultipliers", EXP_BEMPFunc, BF_HrlyResMult, VAR_ARGS },  /* SAC 5/15/12 - added */
   {                "#HRM",          EXP_BEMPFunc, BF_HrlyResMult, VAR_ARGS },  /* SAC 5/15/12 - added */
   { "ComponentType",              EXP_BEMPFunc, BF_CompType,   1 },         /* SAC 8/20/10 - added */
   {                "#CTP",        EXP_BEMPFunc, BF_CompType,   1 },         /* SAC 8/20/10 - added */
   { "SumAcrossIf",                EXP_BEMPFunc, BF_SumAcrsIf,  VAR_ARGS },  /* SAC 2/15/13 - added */
   {                "#SAI",        EXP_BEMPFunc, BF_SumAcrsIf,  VAR_ARGS },  /* SAC 2/15/13 - added */
   { "SumChildrenIf",              EXP_BEMPFunc, BF_SumChldIf,  VAR_ARGS },  /* SAC 2/15/13 - added */
   {                "#SCI",        EXP_BEMPFunc, BF_SumChldIf,  VAR_ARGS },  /* SAC 2/15/13 - added */
   { "PolyLoopArea",               EXP_BEMPFunc, BF_PolyLpArea, 0 },         /* SAC 5/28/13 - added */
   {                "#PLA",        EXP_BEMPFunc, BF_PolyLpArea, 0 },         /* SAC 5/28/13 - added */
   { "ScalePolyLoop",              EXP_BEMPFunc, BF_ScalePolyLp, VAR_ARGS }, /* SAC 5/28/13 - added */
   {                "#SPL",        EXP_BEMPFunc, BF_ScalePolyLp, VAR_ARGS }, /* SAC 5/28/13 - added */
   { "WriteToFile",                EXP_BEMPFunc, BF_WriteToFile, VAR_ARGS }, /* SAC 6/6/13 - added */
   {                "#W2F",        EXP_BEMPFunc, BF_WriteToFile, VAR_ARGS }, /* SAC 6/6/13 - added */
   { "ConsAssmUFactor",            EXP_BEMPFunc, BF_ConsUFctr,  1 },         /* SAC 6/12/13 - added */
   {                "#CAUF",       EXP_BEMPFunc, BF_ConsUFctr,  1 },         /* SAC 6/12/13 - added */
   { "DaylightableArea",           EXP_BEMPFunc, BF_DayltArea,  1 },         /* SAC 10/1/13 - added */
   {                "#DA",         EXP_BEMPFunc, BF_DayltArea,  1 },         /* SAC 10/1/13 - added */
   { "LogDuration",                EXP_BEMPFunc, BF_LogDuration, VAR_ARGS }, /* SAC 10/24/13 - added */
   {                "#LD",         EXP_BEMPFunc, BF_LogDuration, VAR_ARGS }, /* SAC 10/24/13 - added */
   { "InitializePolyLoop",         EXP_BEMPFunc, BF_InitPolyLp, 0 },         /* SAC 10/29/13 - added */
   {                "#IPL",        EXP_BEMPFunc, BF_InitPolyLp, 0 },         /* SAC 10/29/13 - added */
   { "GlobalValid",                EXP_BEMPFunc, BF_GlobalVal,   VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#GV",         EXP_BEMPFunc, BF_GlobalVal,   VAR_ARGS }, /* SAC 2/13/14 - added */
   { "LocalValid",                 EXP_BEMPFunc, BF_LocalVal,    VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#LV",         EXP_BEMPFunc, BF_LocalVal,    VAR_ARGS }, /* SAC 2/13/14 - added */
   { "ParentValid",                EXP_BEMPFunc, BF_ParentVal,   VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#PV",         EXP_BEMPFunc, BF_ParentVal,   VAR_ARGS }, /* SAC 2/13/14 - added */
   { "Parent2Valid",               EXP_BEMPFunc, BF_Parent2Val,  VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#PV2",        EXP_BEMPFunc, BF_Parent2Val,  VAR_ARGS }, /* SAC 2/13/14 - added */
   { "Parent3Valid",               EXP_BEMPFunc, BF_Parent3Val,  VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#PV3",        EXP_BEMPFunc, BF_Parent3Val,  VAR_ARGS }, /* SAC 2/13/14 - added */
   { "IfValidAnd",                 EXP_BEMPFunc, BF_IfValidAnd,  VAR_ARGS }, /* SAC 2/13/14 - added */
   {                "#IVA",        EXP_BEMPFunc, BF_IfValidAnd,  VAR_ARGS }, /* SAC 2/13/14 - added */
   { "CreatePolyLoopChild",        EXP_BEMPFunc, BF_Cr8PolyLp,   VAR_ARGS }, /* SAC 2/18/14 - added */
   {                "#CPL",        EXP_BEMPFunc, BF_Cr8PolyLp,   VAR_ARGS }, /* SAC 2/18/14 - added */
   { "ConsUFactorRes",             EXP_BEMPFunc, BF_ConsUFctrR,  1 },        /* SAC 2/21/14 - added */
   {                "#CUFR",       EXP_BEMPFunc, BF_ConsUFctrR,  1 },        /* SAC 2/21/14 - added */
   { "CreateSCSysRptObjects",      EXP_BEMPFunc, BF_Cr8SCSysRpt, 0 },        /* SAC 3/10/14 - added */
   {                "#CSCSO",      EXP_BEMPFunc, BF_Cr8SCSysRpt, 0 },        /* SAC 3/10/14 - added */
   { "AssignOrCreateComp",         EXP_BEMPFunc, BF_AsgnCr8Comp, VAR_ARGS }, /* SAC 3/11/14 - added */
   {                "#ACC",        EXP_BEMPFunc, BF_AsgnCr8Comp, VAR_ARGS }, /* SAC 3/11/14 - added */
   { "CreateDHWRptObjects",        EXP_BEMPFunc, BF_Cr8DHWRpt,   0 },        /* SAC 3/14/14 - added */
   {                "#CDO",        EXP_BEMPFunc, BF_Cr8DHWRpt,   0 },        /* SAC 3/14/14 - added */
   { "CreateIAQRptObjects",        EXP_BEMPFunc, BF_Cr8IAQRpt,   0 },        /* SAC 3/26/14 - added */
   {                "#CIO",        EXP_BEMPFunc, BF_Cr8IAQRpt,   0 },        /* SAC 3/26/14 - added */
   { "ValidOr",                    EXP_BEMPFunc, BF_ValidOr,     VAR_ARGS }, /* SAC 4/1/14 - added */
   {                "#VO",         EXP_BEMPFunc, BF_ValidOr,     VAR_ARGS }, /* SAC 4/1/14 - added */
   { "LocalRefSymbolString",       EXP_BEMPFunc, BF_LocRefSymStr,  VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#LRSS",       EXP_BEMPFunc, BF_LocRefSymStr,  VAR_ARGS },  /* SAC 4/10/14 - added */
   { "ParentSymbolString",         EXP_BEMPFunc, BF_ParSymStr,     VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#PSS",        EXP_BEMPFunc, BF_ParSymStr,     VAR_ARGS },  /* SAC 4/10/14 - added */
   { "ParentRefSymbolString",      EXP_BEMPFunc, BF_ParRefSymStr,  VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#PRSS",       EXP_BEMPFunc, BF_ParRefSymStr,  VAR_ARGS },  /* SAC 4/10/14 - added */
   { "Parent2SymbolString",        EXP_BEMPFunc, BF_Par2SymStr,    VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#P2SS",       EXP_BEMPFunc, BF_Par2SymStr,    VAR_ARGS },  /* SAC 4/10/14 - added */
   { "Parent2RefSymbolString",     EXP_BEMPFunc, BF_Par2RefSymStr, VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#PR2SS",      EXP_BEMPFunc, BF_Par2RefSymStr, VAR_ARGS },  /* SAC 4/10/14 - added */
   { "Parent3SymbolString",        EXP_BEMPFunc, BF_Par3SymStr,    VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#P3SS",       EXP_BEMPFunc, BF_Par3SymStr,    VAR_ARGS },  /* SAC 4/10/14 - added */
   { "Parent3RefSymbolString",     EXP_BEMPFunc, BF_Par3RefSymStr, VAR_ARGS },  /* SAC 4/10/14 - added */
   {                "#PR3SS",      EXP_BEMPFunc, BF_Par3RefSymStr, VAR_ARGS },  /* SAC 4/10/14 - added */
   { "EnumString",                 EXP_BEMPFunc, BF_SymString,     1        },  /* SAC 4/10/14 - added */
   {                "#ES",         EXP_BEMPFunc, BF_SymString,     1        },  /* SAC 4/10/14 - added */
   { "CreateDwellUnitHVACSysObjects", EXP_BEMPFunc, BF_Cr8DUHVAC,  0 },         /* SAC 6/28/14 - added */
   {                "#CDHO",          EXP_BEMPFunc, BF_Cr8DUHVAC,  0 },         /* SAC 6/28/14 - added */
   { "MaxChildComp",               EXP_BEMPFunc, BF_MaxChildC,   VAR_ARGS },    /* SAC 10/18/14 - added */
   {                "#MCC",        EXP_BEMPFunc, BF_MaxChildC,   VAR_ARGS },    /* SAC 10/18/14 - added */
   { "MinChildComp",               EXP_BEMPFunc, BF_MinChildC,   VAR_ARGS },    /* SAC 10/18/14 - added */
   {                "#MICC",       EXP_BEMPFunc, BF_MinChildC,   VAR_ARGS },    /* SAC 10/18/14 - added */
   { "YrMoDaToSerial",             EXP_BEMPFunc, BF_YrMoDa2Date,   3 },         /* SAC 10/31/14 - added */
   {                "#YMD2S",      EXP_BEMPFunc, BF_YrMoDa2Date,   3 },         /* SAC 10/31/14 - added */
   { "SerialDateToDayOfMonth",     EXP_BEMPFunc, BF_Date2WkDay,    1 },         /* SAC 10/31/14 - added */
   {                "#D2D",        EXP_BEMPFunc, BF_Date2WkDay,    1 },         /* SAC 10/31/14 - added */
   { "SerialDateToMonth",          EXP_BEMPFunc, BF_Date2Mo,       1 },         /* SAC 10/31/14 - added */
   {                "#D2M",        EXP_BEMPFunc, BF_Date2Mo,       1 },         /* SAC 10/31/14 - added */
   { "SerialDateToYear",           EXP_BEMPFunc, BF_Date2Yr,       1 },         /* SAC 10/31/14 - added */
   {                "#D2Y",        EXP_BEMPFunc, BF_Date2Yr,       1 },         /* SAC 10/31/14 - added */
   { "YrMoDaToDayOfWeek",          EXP_BEMPFunc, BF_YrMoDa2DOW,    3 },         /* SAC 10/31/14 - added */
   {                "#YMD2DW",     EXP_BEMPFunc, BF_YrMoDa2DOW,    3 },         /* SAC 10/31/14 - added */
   { "CreateDwellUnitRptObjects",  EXP_BEMPFunc, BF_Cr8DURpt,      0 },         /* SAC 11/15/14 - added */
   {                "#CDURO",      EXP_BEMPFunc, BF_Cr8DURpt,      0 },         /* SAC 11/15/14 - added */
   { "ListRevRef",                 EXP_BEMPFunc, BF_ListRevRef,   VAR_ARGS },   /* SAC 1/26/15 - added */
   {                "#LRR",        EXP_BEMPFunc, BF_ListRevRef,   VAR_ARGS },   /* SAC 1/26/15 - added */
   { "ListRevRefIf",               EXP_BEMPFunc, BF_ListRevRefIf, VAR_ARGS },   /* SAC 1/26/15 - added */
   {                "#LRRI",       EXP_BEMPFunc, BF_ListRevRefIf, VAR_ARGS },   /* SAC 1/26/15 - added */
   { "OpenExportFile",             EXP_BEMPFunc, BF_OpenExpFile,  VAR_ARGS },   /* SAC 9/15/15 - added */
   {                "#OXF",        EXP_BEMPFunc, BF_OpenExpFile,  VAR_ARGS },   /* SAC 9/15/15 - added */
   { "WriteToExportFile",          EXP_BEMPFunc, BF_WriteExpFile, VAR_ARGS },   /* SAC 9/15/15 - added */
   {                "#WXF",        EXP_BEMPFunc, BF_WriteExpFile, VAR_ARGS },   /* SAC 9/15/15 - added */
   { "CloseExportFile",            EXP_BEMPFunc, BF_CloseExpFile,  1       },   /* SAC 9/15/15 - added */
   {                "#CXF",        EXP_BEMPFunc, BF_CloseExpFile,  1       },   /* SAC 9/15/15 - added */
   { "StrToFlt",                   EXP_BEMPFunc, BF_StrToFlt,      1       },   /* SAC 2/23/16 - added - takes into account locale-specific formatting */
   {                "#S2F",        EXP_BEMPFunc, BF_StrToFlt,      1       },   /* SAC 2/23/16 - added */ 
   { "CreateDwellUnitDHWHeaters",  EXP_BEMPFunc, BF_Cr8DUWHtr,     0 },         /* SAC 5/29/16 - added */
   {                "#CDUWH",      EXP_BEMPFunc, BF_Cr8DUWHtr,     0 },         /* SAC 5/29/16 - added */
   { "AddCSEReportCol",            EXP_BEMPFunc, BF_AddCSERptCol,  2 },         /* SAC 11/14/16 - added */
   {                "#ACRC",       EXP_BEMPFunc, BF_AddCSERptCol,  2 },         /* SAC 11/14/16 - added */
   { "ApplyHourlyResultMultipliers_NEM", EXP_BEMPFunc, BF_HrlyResMltNEM, VAR_ARGS },  /* SAC 1/23/17 - added */
   {                "#HRMN",             EXP_BEMPFunc, BF_HrlyResMltNEM, VAR_ARGS },  /* SAC 1/23/17 - added */
   { "ApplyHourlyResultMultipliers_Neg", EXP_BEMPFunc, BF_HrlyResMltNeg, VAR_ARGS },  /* SAC 10/4/17 - added */
   {                "#HRMNg",            EXP_BEMPFunc, BF_HrlyResMltNeg, VAR_ARGS },  /* SAC 10/4/17 - added */
   { "CopyHourlyResults",          EXP_BEMPFunc, BF_CopyHrlyRes,   6 },         /* SAC 10/5/17 - added */
   {                "#CHR",        EXP_BEMPFunc, BF_CopyHrlyRes,   6 },         /* SAC 10/5/17 - added */
   { "GlobalRefSymbolString",      EXP_BEMPFunc, BF_GlobRefSymStr, VAR_ARGS },  /* SAC 4/4/18 - added */
   {                "#GRSS",       EXP_BEMPFunc, BF_GlobRefSymStr, VAR_ARGS },  /* SAC 4/4/18 - added */
   { "ScheduleSum",                EXP_BEMPFunc, BF_SchSum,        VAR_ARGS },  /* SAC 8/17/18 - added */
   {                "#SS",         EXP_BEMPFunc, BF_SchSum,        VAR_ARGS },  /* SAC 8/17/18 - added */
   { "UniqueListRevRef",           EXP_BEMPFunc, BF_UListRevRef,   VAR_ARGS },  /* SAC 8/22/19 - added */
   {                "#ULRR",       EXP_BEMPFunc, BF_UListRevRef,   VAR_ARGS },  /* SAC 8/22/19 - added */
   { "UniqueListRevRefIf",         EXP_BEMPFunc, BF_UListRevRefIf, VAR_ARGS },  /* SAC 8/22/19 - added */
   {                "#ULRRI",      EXP_BEMPFunc, BF_UListRevRefIf, VAR_ARGS },  /* SAC 8/22/19 - added */
   { "Parent2ComponentType",       EXP_BEMPFunc, BF_Par2CompType, 0 },          /* SAC 9/5/19 - added */
   {                "#P2CT",       EXP_BEMPFunc, BF_Par2CompType, 0 },          /* SAC 9/5/19 - added */
   { "Parent3ComponentType",       EXP_BEMPFunc, BF_Par3CompType, 0 },          /* SAC 9/5/19 - added */
   {                "#P3CT",       EXP_BEMPFunc, BF_Par3CompType, 0 },          /* SAC 9/5/19 - added */
   { "SchDayHoursString",          EXP_BEMPFunc, BF_SchDayHrsStr, VAR_ARGS },   /* SAC 10/6/19 - added (MFamProto) */
   {                "#SDHS",       EXP_BEMPFunc, BF_SchDayHrsStr, VAR_ARGS },   /* SAC 10/6/19 - added */
   { NULL,                         0,           0,              0 }
};

static BOOL CurrentFunctionAllowsConditionalOperators( int iCurFunc )  // SAC 2/20/13 - 
{	return ( iCurFunc ==  BF_SumAcrsIf    ||
	         iCurFunc ==  BF_SumChldIf    ||
            iCurFunc ==  BF_IfValidAnd   ||
            iCurFunc ==  BF_ListRevRefIf ||
            iCurFunc ==  BF_UListRevRefIf );  // SAC 2/13/14   // SAC 1/26/15   // SAC 8/22/19
}
int eiParseCount_IfValidAnd = 0;		/* SAC 1/30/15 - added to ensure all arguments evaluate via *Valid() functions */
int eiParseCount_ValidOr = 0;

static FuncTable varfunctable[] =
{
/*   { "LocalRef",     EXP_BEMPFunc, BF_LocalRef,  VAR_ARGS }, */
/*   { "#LR",          EXP_BEMPFunc, BF_LocalRef,  VAR_ARGS }, */
/*   { "ParentRef",    EXP_BEMPFunc, BF_ParentRef, VAR_ARGS }, */
/*   { "#PR",          EXP_BEMPFunc, BF_ParentRef, VAR_ARGS }, */

/*   { "ParentRef",    EXP_BEMPFunc, BF_ParentRef, VAR_ARGS }, */
/*   { "#PR",          EXP_BEMPFunc, BF_ParentRef, VAR_ARGS }, */
/*   { "Parameter",    EXP_BEMPFunc, BF_Parameter, VAR_ARGS }, */
/*   { "#Pa",          EXP_BEMPFunc, BF_Parameter, VAR_ARGS }, */

   { NULL,        0,           0,            0 }
};

#define  BEMPFuncIndex  3
PFFormulaFunction evalFunctions[] =
{
   UnaryFunc,
   BinaryFunc,
   ErrorFunc,
   BEMPFunc,
};

/* SAC 8/29/02 - Added preceding .# to each %s entry below to prevent sprintf()s from exceeding the allocated error string length */
/* SAC 12/24/07 - Added 80 chars to error msg length */
/* SAC 5/1/13 - added leading 'ERROR:' to most of the error messages to help track & identify them in logs */
/* SAC 1/22/14 - Added 96 chars to error msg length */
/* SAC 5/16/14 - revised error messages 'ERROR' -> 'Error' and also added a pre-pended 'Error:  ' to the EXP_RuleProc errors */
/* SAC 9/4/14 - Double error msg length (added 256 chars) */
static const char *errorMessages[] =
{
   /* EXP_None        */   "No error",
   /* EXP_NoMem       */   "Error:  Out of memory",
   /* EXP_Underflow   */   "Error:  Evaluation stack underflow",
   /* EXP_Overflow    */   "Error:  Evaluation stack overflow",
   /* EXP_ZeroDiv     */   "Error:  Division by zero",
   /* EXP_NegLog      */   "Error:  Log of non-positive number",
   /* EXP_NegSqrt     */   "Error:  Sqrt of a negative number",
   /* EXP_Trig        */   "Error:  Trig parameter out of range",
   /* EXP_Syntax      */   "Error:  Syntax error near '%.483s'",
   /* EXP_BadName     */   "Error:  Undefined name '%.486s'",
   /* EXP_NoParser    */   "Error:  Undefined parse function",
   /* EXP_NoFormula   */   "Error:  No expression defined",
   /* EXP_BadArgs     */   "Error:  Wrong number of arguments for '%.471s'",
   /* EXP_UndefArg    */   "Error:  Undefined data: %.487s",
   /* EXP_RuleProc    */   "Error:  %.503s",
   /* EXP_RuleWarn    */   "%.511s",
};

static const char       *parseString;
static const char       *parseChar;
static int               parseCurrentLine;
static int               parseStartPos;
static int               parseEndPos;
static ExpError         *parseError;
static PFGetVar          parseGetVar;
static PFSelectFunction  parseSelectFunc;  /* SAC 8/14/12 */
static ParsedExpression *parseList;
static PFErrorFunc       errorFunction = NULL;
static PFFormulaFunction pfBEMPFunctionCall;

static int crntFunc;


static BOOL GetControlKeyword( const char* string, int* token );
static int GetFortranComparisonOp( const char** ppParseString );
static ExpNode* SkipTilNode( ParsedExpression* pExp, ExpNode* node, ExpNodeType nodeType );
static ExpNodeType IsFunction( const char *name, int *type, void* data );

static void StringUnaryFunc( ExpStack* stack, int op, ExpNode* node, void* pData, ExpError* error );
static BOOL IsEqual( ExpNode* node1, ExpNode* node2 );
static void showError( double type, double num, char* string );

/********************************************************************************************/

static void AddNodeTail(ExpNode* pNewNode);
   
static void AddObjectNode(void* pObject, int tokenType);
static void AddKeyWordNode(int keyword);
static void AddFunctionNode(int function, int nArgs);
   
static void ExpListAddHead( ParsedExpression *pParsed, ExpNode* node );
static void ExpListAddTail( ParsedExpression *pParsed, ExpNode* node );

static void ExpStackInit( ExpStack* stack, int count );
static void ExpStackDelete( ExpStack* stack );

/********************************************************************************************/

void ExpNode_init( ExpNode* p )
{	if (p)
	{	p->type = EXP_Invalid;
		p->pValue = NULL;
		p->fValue = 0.0;
		p->fn.function = 0;
		p->fn.op = 0;
		p->fn.nArgs = 0;
		p->pNext = NULL;
		p->pPrev = NULL;
	}
}

ExpNode* ExpNode_new()
{	ExpNode* p = malloc(sizeof(ExpNode));
	if (p)
		ExpNode_init(p);
	return p;
}

/********************************************************************************************
   Expression List handling routines
*********************************************************************************************/

int ExpListCount( ParsedExpression *pParsed )
{ 
   int n = 0;

   if ( pParsed != NULL && pParsed->nodeList != NULL )
      n = pParsed->nodeList->count; 

   return( n );
}

ExpNode* ExpListHead( ParsedExpression *pParsed )
{
   ExpNode* node = NULL;

   if ( pParsed != NULL && pParsed->nodeList != NULL )
      node = pParsed->nodeList->head; 

   return( node );
}

ExpNode* ExpListTail( ParsedExpression *pParsed )
{
   ExpNode* node = NULL;

   if ( pParsed != NULL && pParsed->nodeList != NULL )
      node = pParsed->nodeList->tail; 

   return( node );
}

ExpNode* ExpListNext( ParsedExpression* pParsed, ExpNode* node )
{
   ExpNode* nextNode = NULL;		pParsed;
   if ( node != NULL )
      nextNode = node->pNext;

   return( nextNode ); 
}

ExpNode* ExpListPrev( ParsedExpression* pParsed, ExpNode* node )
{
   ExpNode* prevNode = NULL;			pParsed;
   if ( node != NULL )
      prevNode = node->pPrev;

   return( prevNode ); 
}

void ExpListAddHead( ParsedExpression *pParsed, ExpNode* node )
{ 
   /* TO DO: Speed up the list stuff by allocating nodes in arrays */
   if ( pParsed->nodeList == NULL )
      pParsed->nodeList = (ExpNodeList*)calloc( 1, sizeof( ExpNodeList ) );

   if ( pParsed->nodeList->count == 0 )
   {
      pParsed->nodeList->tail = node;
      node->pNext = NULL;
   }
   node->pPrev = NULL;
   pParsed->nodeList->head->pPrev = node;
   node->pNext = pParsed->nodeList->head;
   pParsed->nodeList->head = node;
   pParsed->nodeList->count++;
}

void ExpListAddTail( ParsedExpression *pParsed, ExpNode* node )
{ 
   if ( pParsed->nodeList == NULL )
      pParsed->nodeList = (ExpNodeList*)calloc( 1, sizeof( ExpNodeList ) );

   if ( pParsed->nodeList->count == 0 )
      pParsed->nodeList->head = node;
   else
      pParsed->nodeList->tail->pNext = node;

   node->pPrev = pParsed->nodeList->tail;
   pParsed->nodeList->tail = node;
   node->pNext = NULL;
   pParsed->nodeList->count++;
}

void ExpListDelete( ParsedExpression *pParsed )
{ 
   if ( pParsed == NULL ) 
      return;

   if ( pParsed->nodeList == NULL ) 
      return;

   while ( pParsed->nodeList->head != NULL )
   {
      ExpNode* next = pParsed->nodeList->head->pNext;

      if ( pParsed->nodeList->head->type == EXP_String )
         free( pParsed->nodeList->head->pValue );

      free( pParsed->nodeList->head );
      pParsed->nodeList->head = next;
   }

   free( pParsed->nodeList );
   pParsed->nodeList = NULL;
}

/********************************************************************************************
   Evaluation Stack handling routines
*********************************************************************************************/

void ExpStackInit( ExpStack* stack, int count )
{	count;
   stack->top = NULL;
}

void ExpStackDelete( ExpStack* stack )
{
   while( stack->top != NULL )
      ExpNodeDelete( ExpStackPop( stack ) );
}

void ExpNodeDelete( ExpNode* node )
{
   if ( node == NULL )
      return;
   if ( node->type == EXP_String )
      free( node->pValue );
   free( (void*)node );
}

BOOL ExpNodeCopy( ExpNode* target, ExpNode* node )
{
   BOOL ok = TRUE;
   if ( target->type == EXP_String )
      free( target->pValue );

   memcpy( (char*) target, (char*) node, sizeof( ExpNode ) );

   if ( node->type == EXP_String )
   {
      if (node->pValue == NULL)    // SAC 10/31/07 - added if statement to handle case where no string is present
         target->pValue = NULL;
      else
      {
         target->pValue = malloc( strlen( node->pValue ) + 1 );
         if ( target->pValue == NULL )
            ok = FALSE;
         else
            strcpy( target->pValue, node->pValue );
      }
   }

   return ok;
}

void ExpStackPush( ExpStack* stack, ExpNode* node )
{
   node->pNext = stack->top;
   stack->top = node;
}

BOOL ExpStackPushCopy( ExpStack* stack, ExpNode* node )
{
   BOOL ok = TRUE;
   ExpNode* newNode = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( newNode == NULL )
      ok = FALSE;
   else
   {
      memcpy( (char*) newNode, (char*) node, sizeof( ExpNode ) );
      if ( node->type == EXP_String )
      {   
         int length = (int) strlen( node->pValue );
         newNode->pValue = malloc( ( length + 1 ) * sizeof( char ) );
         if ( newNode->pValue == NULL )
         {
            ok = FALSE;
            free( (void*)newNode );
            ExpSetError( parseError, EXP_NoMem, NULL );
         }
         else
            strcpy( newNode->pValue, node->pValue );
      }

      if ( ok )
      {
         newNode->pNext = stack->top;
         stack->top = newNode;
      }
   }

   return( ok );
}

ExpNode* ExpStackPop( ExpStack* stack )
{
   ExpNode* node = stack->top;

   if ( stack->top != NULL )
      stack->top = stack->top->pNext;

   return ( node );
}

BOOL ExpInitialize( PFFormulaFunction pfFunc )
{
   pfBEMPFunctionCall = pfFunc; 

   return ( TRUE );
}



int GetnArgs()  /* Called from parser.c */
{
   int nArgs = topNarg->nArgs;
   Nargs* temp = topNarg;

   topNarg = temp->next;
   free( temp );

   crntFunc = 0;

   return( nArgs );
}

void AddnArg()  /* Called from parser.c */
{
   if ( topNarg != NULL )
      topNarg->nArgs++;
}

void PushnArgs()  /* Called from parser.c */
{
   Nargs* newNarg = (Nargs*) malloc( sizeof( Nargs ) );

   if ( newNarg != NULL )
   {
      newNarg->next = topNarg;
      newNarg->nArgs = 0;
      topNarg = newNarg;
   }
   else
      ; /* TO DO: Out of memory */
}

static BOOL GetControlKeyword( const char* string, int* token )
{
   int i = 0;
   BOOL found = FALSE;

   while ( controlOps[ i ].tokenString != NULL && !found )
   {
      if ( stricmp_( controlOps[ i ].tokenString, string ) == 0 )
      {
         found = TRUE;
         *token = controlOps[ i ].opCode;
      }
      i++;
   }

   return found;
}

static int GetFortranComparisonOp( const char** ppParseString )
{
   int token = 0;
   int nChars = 4;  /* For updating pParseString. */

   if ( _strnicmp( *ppParseString, ".OR.", nChars  ) == 0 )  // SAC 10/25/12 - switched from strnicmp_() to _strnicmp() due to comparisons being case-sensitive
      token = OR;
   else if ( _strnicmp( *ppParseString, ".EQ.", nChars ) == 0 )
      token = EQ;
   else if ( _strnicmp( *ppParseString, ".NE.", nChars ) == 0 )
      token = NEQ;
   else if ( _strnicmp( *ppParseString, ".LT.", nChars ) == 0 )
      token = LT;
   else if ( _strnicmp( *ppParseString, ".GT.", nChars ) == 0 )
      token = GT;
   else if ( _strnicmp( *ppParseString, ".LE.", nChars ) == 0 )
      token = LE;
   else if ( _strnicmp( *ppParseString, ".GE.", nChars ) == 0 )
      token = GE;
   else if ( _strnicmp( *ppParseString, ".NOT.", 5 ) == 0 )
   {
      nChars = 5; 
      token = NOT;
   }
   else if ( _strnicmp( *ppParseString, ".AND.", 5 ) == 0 )
   {
      nChars = 5;
      token = AND;
   }
   else  /* Didn't find one, don't advance string pointer. */
      nChars = 0;

   *ppParseString += nChars - 1; /* pParseString gets advanced 1 later. */
   parseEndPos += nChars - 1; /* pParseString gets advanced 1 later. */

   return token; /* token == 0 means we didn't find one. */
}


	
void ExpAddFunctionNode( void* func, int nArgs )
{
   FuncTable *function = (FuncTable*)func;

	/* SAC 1/30/15 - logic to ensure all arguments evaluate via *Valid() functions for certain functions */
	if (function && function->op == BF_IfValidAnd)
		eiParseCount_IfValidAnd = (eiParseCount_IfValidAnd < 1 ? 0 : (eiParseCount_IfValidAnd-1));		
	if (function && function->op == BF_ValidOr)
		eiParseCount_ValidOr = (eiParseCount_ValidOr < 1 ? 0 : (eiParseCount_ValidOr-1));		

   if ( nArgs != function->nArgs && function->nArgs != VAR_ARGS ) 
      ExpSetError( parseError, EXP_BadArgs, function->name );
   else
   {
      ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

      if ( node == NULL )
         ExpSetError( parseError, EXP_NoMem, NULL );
      else
      {
         node->type = EXP_Function;
         node->fn.function = function->evaluate;
         node->fn.op = function->op;
         node->fn.nArgs = nArgs;

         ExpListAddTail( parseList, node );
      }
   }
}

const char* ExpGetFuncTableNameByOpType( int iOpType )  // SAC 8/31/16
{	int idx = -1;
	const char* pName = NULL;
	while (pName == NULL && functable[++idx].name != NULL)
	{	if (functable[idx].op == iOpType)
			pName = functable[idx].name;
	}
	return pName;
}

void* ExpGetFuncTablePtrByOpType( int iOpType, int* pnArgs )  // SAC 7/13/12
{	int idx = -1;
	void* pFunc = NULL;
	while (pFunc == NULL && functable[++idx].name != NULL)
	{	if (functable[idx].op == iOpType)
		{	pFunc = &functable[idx];
			if (pnArgs)
				*pnArgs = functable[idx].nArgs;
		}
	}
	return pFunc;
}

void ExpAddFunctionNodeByOpType( int iOpType, int nArgs )  // SAC 7/9/12
{	int idx = -1;
	void* pFunc = NULL;
	while (pFunc == NULL && functable[++idx].name != NULL)
	{	if (functable[idx].op == iOpType)
			pFunc = &functable[idx];
	}
	//ASSERT( pFunc );
	if (pFunc)
		ExpAddFunctionNode( pFunc, nArgs );
}

void ExpAddTableNode( long table, int nArgs )
{
   if ( nArgs < 2 ) 
      ExpSetError( parseError, EXP_RuleProc, "Error: Too few args for table" );
   else
   {
      ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

      if ( node == NULL )
         ExpSetError( parseError, EXP_NoMem, NULL );
      else
      {
         // In order to use one callback, fn.function is EXP_BEMPFunc.
         // To indicate which table, we will use a negative value for fn.op.
         // ( table id's are 1-based)
         node->type = EXP_Function;
         node->fn.function = EXP_BEMPFunc;
         node->fn.op = (int)-table;
         node->fn.nArgs = nArgs;

         ExpListAddTail( parseList, node );
      }
   }
}

void ExpAddRefFuncNode( void* func, int nArgs )
{
   FuncTable *function = (FuncTable*)func;
   BOOL ok = FALSE;

   ok = TRUE;
//   if ( function->op == BF_Parameter )
//      ok = ParseParameter( parseList, nArgs );
//   else
//   {
//      BOOL bLocal  = ( function->op == BF_LocalRef || function->op == BF_Local );
//      BOOL bRef    = ( function->op == BF_LocalRef || function->op == BF_ParentRef );
//      BOOL bGlobal = ( function->op == BF_Global );
//      int iParseRet = ParseLocParRefGlob( parseList, nArgs, bLocal, bRef, bGlobal );
//      if (iParseRet > -1)
//      {
//         ok = TRUE;
//         if (bRef)
//            function->op += iParseRet;
//      }
//   }
      
   if ( !ok )
      ExpSetError( parseError, EXP_BadArgs, function->name );
   else
   {
      ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

      if ( node == NULL )
         ExpSetError( parseError, EXP_NoMem, NULL );
      else
      {
         node->type = EXP_Function;
         node->fn.function = function->evaluate;
         node->fn.op = function->op;
         node->fn.nArgs = nArgs;

         ExpListAddTail( parseList, node );
      }
   }
}

void ExpAddVarArgString( char* string )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      /* string is pointer into expression string so close quote is still in it. */
      /* This will trim it off. */
      char* quotePtr = strchr( string, '\"' );
      int length = (int) strlen( string );

      if ( quotePtr != NULL )
         length = (int) (quotePtr - string);

      node->type = EXP_String;
      node->pValue = (char*)malloc( length + 1 );
      if ( node->pValue != NULL )
      {
         strncpy( node->pValue, string, length );
         ((char*)node->pValue)[ length ] = '\0';

         ExpListAddTail( parseList, node );
      }
      else
         ExpSetError( parseError, EXP_NoMem, NULL );
   }
}

void ExpAddVarArgConst( double value )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Value;
      node->fValue = value;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddErrNode( void* func, int nArgs )
{
   FuncTable *function = (FuncTable*)func;

   if ( nArgs != function->nArgs && function->nArgs != VAR_ARGS ) 
      ExpSetError( parseError, EXP_BadArgs, function->name );
   else
   {
      ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

      if ( node == NULL )
         ExpSetError( parseError, EXP_NoMem, NULL );
      else
      {
         node->type = EXP_Function;
         node->fn.function = EXP_ErrorFunc;
         node->fn.op = OP_ErrorExp;
         node->fn.nArgs = nArgs;

         ExpListAddTail( parseList, node );
      }
   }
}

void ExpAddBinOpNode( int op )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Function;
      node->fn.function = EXP_Binary;
      node->fn.op = op;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddUnOpNode( int op )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Function;
      node->fn.function = EXP_Unary;
      node->fn.op = op;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddBEMIndex( const char* command, const char* keyword )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Index;
      node->pValue = 0; /* GetComKeyIndex( command, keyword ); */	command;	keyword;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddConstantNode( double value )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Value;
      node->fValue = value;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddKeyWordNode( long keywordIndex )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Keyword;
      node->fValue = (double)keywordIndex;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddBldgElemNode( long long dbId )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      node->type = EXP_Value;
      node->fValue = (double)dbId;

      ExpListAddTail( parseList, node );
   }
}

void ExpAddStringNode( const char* string )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      /* string is pointer into expression string so close quote is still in it. */
      /* This will trim it off. */
      char* quotePtr = strchr( string, '\"' );
      int length = (int) strlen( string );

      if ( quotePtr != NULL )
         length = (int) (quotePtr - string);

      node->type = EXP_String;
      node->pValue = (char*)malloc( length + 1 );
      if ( node->pValue != NULL )
      {
         strncpy( node->pValue, string, length );
         ((char*)node->pValue)[ length ] = '\0';

         ExpListAddTail( parseList, node );
      }
      else
         ExpSetError( parseError, EXP_NoMem, NULL );
   }
}

void ExpAddControlNode( int tokenType )
{
   ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );

   if ( node == NULL )
      ExpSetError( parseError, EXP_NoMem, NULL );
   else
   {
      int i = 0;
      BOOL found = FALSE;
      while ( controlOps[ i ].tokenString != NULL && !found )
      {
         found = controlOps[ i ].opCode == tokenType;
         if ( found )
         {
            node->type = controlOps[ i ].nodeType;
            ExpListAddTail( parseList, node );
         }
         i++;
      }

      if ( !found )
         ExpSetError( parseError, EXP_Syntax, NULL );
   }
}


/********************************************************************************************
   Lexical analyzer
*********************************************************************************************/

static int siInsertFuncMode = 0;   /* SAC 8/14/12 - new Mode variable to facilitate more flexible expression syntax, eliminating the need to
												*						specify certain generic function names such as Local(), Parent(), etc. */

#define  MAX_TRACKCURFUNC  30      /* SAC 2/14/14 - added new variables to track function nesting - used in conjunction with */
static int siTrackCurFuncIdx = 0;  /*                CurrentFunctionAllowsConditionalOperators()  */
static int siaTrackCurFunc[MAX_TRACKCURFUNC] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
BOOL ResetCurrentFunctionTracking()
{	BOOL bRetVal = (siTrackCurFuncIdx >= 0 && siTrackCurFuncIdx <= 1);  // can be 1 if prev rule ended immediately after Comp:Param that has a function call generated for it
	int i;
	siTrackCurFuncIdx = 0;
	siInsertFuncMode = 0;  /* SAC 2/14/14 - added reset of siInsertFuncMode */
	for (i=0; i<MAX_TRACKCURFUNC; i++)
		siaTrackCurFunc[i] = 0;
	return bRetVal;
}
static void AddCurrentFunctionToTracking( int iCurFunc )
{	if (siTrackCurFuncIdx >= 0 && siTrackCurFuncIdx < MAX_TRACKCURFUNC)
		siaTrackCurFunc[siTrackCurFuncIdx] = iCurFunc;
	siTrackCurFuncIdx++;
}
static void ReduceCurrentFunctionToTracking()
{	siTrackCurFuncIdx--;
	if (siTrackCurFuncIdx >= 0 && siTrackCurFuncIdx < MAX_TRACKCURFUNC)
		siaTrackCurFunc[siTrackCurFuncIdx] = 0;
}
static int GetCurrentFunctionTracked()
{	return (siTrackCurFuncIdx > 0 && siTrackCurFuncIdx <= MAX_TRACKCURFUNC ? siaTrackCurFunc[siTrackCurFuncIdx-1] : 0);
}

int yylex()
{
   int token = 0;

   while ( isspace( (unsigned char) *parseChar ) || *parseChar == '\n' )
      parseChar++;

   if ( *parseChar != '\0' )
   {
      if ( isdigit( *parseChar ) || ( *parseChar == '.' && isdigit( parseChar[ 1 ] ) ) )
      {
         const char *begin = parseChar;
         const char* pExp;

         while ( *parseChar != '\0' && ISFLOATCHAR( *parseChar ) )
            parseChar++;

         token        = CONSTANT;
         yylval.value = atof( begin );		// SAC 9/25/16 - was: (float)atof( begin );

         /* atof() uses exponent, we just need to skip it correctly. */
         /* Skips: 1.23E45, 1.23E+45, 1.23E-45, */
         /*        1.23e45, 1.23e+45, 1.23e-45. */
         pExp = parseChar;
         if ( *parseChar == 'E' || *parseChar == 'e' )
         {
            BOOL foundExponent = FALSE;

            pExp++;
            if ( *pExp == '-' || *pExp == '+' )
               pExp++;

            while ( isdigit( *pExp ) )
            {
               foundExponent = TRUE;
               pExp++;
            }
            if ( foundExponent )
               parseChar = pExp;
            else
               ;  /* This is an error, however it will be caught by the parser */
         }

         /* Check for percent constants: e.g. 50% (0.5) */
         if ( *parseChar == '%' )
         {
            yylval.value /= 100;
            parseChar++;
         }      
      }
      else if ( *parseChar == '\"' )
      {
         token         = STRING;
         yylval.object = (void*)++parseChar;
         
         while ( *parseChar != '\0' && *parseChar != '\"' )
            parseChar++;
            
         /* Skip past the closing quote    */
         if ( *parseChar != '\0' )
            parseChar++;   
      }
      else if( (isalpha( *parseChar )) || (*parseChar == '#') )
      {
         // We have to allow tokens that look like <asdf:zxcv[123]:xyz>
         // The code below handles :':' '[' and ']'
         char string[ MAXSYMBOLLENGTH ];
         BOOL found = FALSE;
			const char *saveParseChar = parseChar;  /* SAC 8/14/12 */

         int  i = 0;
         BOOL done = FALSE;
         while ( *parseChar != '\0' && ISNAMECHAR( *parseChar ) )
         {
            if ( i < MAXSYMBOLLENGTH )
               string[ i++ ] = *parseChar;
            parseChar++;
         }
         // Since the syntax allows parameter id's with ':'s or '[#]'s, we need to 
         // scan ahead for them here.  If we find a ':' after "default" or "case" 
         // then it is part of the regular syntax so we should stop here.
         if ( *parseChar == ':' )
         {
            string[ i ] = '\0';
            if ( _stricmp( string, "case" ) == 0 || 
                 _stricmp( string, "default" ) == 0 )
               done = TRUE;
         } 
         else if ( _stricmp( string, "default" ) == 0 )
         {  // SPECIAL CASE for "default": if default is followed by ':' then it's 
            // a control word.  Else it's a keyword.
            const char* temp = parseChar;
            while ( isspace( (unsigned char) *temp ) || *temp == '\n' )
               temp++;
            if ( *temp != ':' )
            {
               yylval.index = (long)1;
               return KEYWORD;
            }
         }

         while ( !done && i < MAXSYMBOLLENGTH )
         {
            if ( *parseChar == ':' || *parseChar == '[' )
            {
               string[ i++ ] = *parseChar;
               if ( *parseChar == '[' )
               {
                  parseChar++;
                  while ( isspace((unsigned char) *parseChar ) || *parseChar == '\n' )
                     parseChar++;
                  while ( isdigit(*parseChar ) && i < MAXSYMBOLLENGTH )
                  {
                     string[ i++ ] = *parseChar;
                     parseChar++;
                  }
                  while ( isspace((unsigned char) *parseChar) || *parseChar == '\n' ) 
                     parseChar++;
                  if ( *parseChar== ']' && i < MAXSYMBOLLENGTH )
                  {
                     string[ i++ ] = *parseChar;
                     parseChar++;
                  }
                  if ( *parseChar == ':' && i < MAXSYMBOLLENGTH )
                  {
                     string[ i++ ] = *parseChar;
                     parseChar++;
                  }
               }
               else
                  parseChar++;
               while ( *parseChar != '\0' && ISNAMECHAR( *parseChar ) )
               {
                  if ( i < MAXSYMBOLLENGTH )
                     string[ i++ ] = *parseChar;
                  parseChar++;
               }
            }
            else
               done = TRUE;
         }
         string[ i ] = '\0';

         if ( _stricmp( string, "error" ) == 0 || _stricmp( string, "#E" ) == 0 )
         {
            yylval.object = &functable[ OP_ErrorExp ];
            token = EXP_ERROR; /* different token type for error because of different syntax */
            found = TRUE;
         }

         if ( !found && (siInsertFuncMode == 2 || siInsertFuncMode == 4) )  /* SAC 8/14/12 */
			{
				token = (siInsertFuncMode == 2 ? '(' : ')');
            found = TRUE;
				if (siInsertFuncMode == 4)
					siInsertFuncMode = 0;
			}
         if ( !found )
         {
            i = 0;
            while ( functable[ i ].name != NULL )
            {
               if( _stricmp( string, functable[ i ].name ) == 0 )
               {
  if (functable[ i ].op == 117)
    token = FUNCTION;
                  crntFunc = functable[ i ].op;
                  yylval.object = &functable[ i ];
                  token = FUNCTION;
                  found = TRUE;
                  PushnArgs(); // Moved this here from parser.y because it must be called
                               // prior to FUNCTION being reduced i.e. prior to arglist being
                               // processed.
                  break;         /* out of "while" loop */
               }
               i++;
            }
         }
         if ( !found )
         {
            i = 0;
            while ( varfunctable[ i ].name != NULL )
            {
               if( _stricmp( string, varfunctable[ i ].name ) == 0 )
               {
                  yylval.object = &varfunctable[ i ];
                  token = REFFUNC;
                  found = TRUE;
                  break;         /* out of "while" loop */
               }
               i++;
            }
         }
         if ( !found )
            found = GetControlKeyword( string, &token );
         if ( !found )
            found = parseGetVar( string, &token, crntFunc, &yylval );
         if ( !found && siInsertFuncMode == 0 )
			{
				/* parseSelectFunc() will determine if 'string' is a valid data model path, and if so, return the OpType value correpsonding to the function that can properly evaluate it */
				int iFuncOpType = parseSelectFunc( string, crntFunc, parseError );  // SAC 6/3/13 - added parseError argument
				if (iFuncOpType >= 0)
				{	int iFTIdx = -1;
					while (functable[++iFTIdx].name != NULL)
					{	if (functable[iFTIdx].op == iFuncOpType)
							break;
					}
					if (functable[iFTIdx].name != NULL)
					{  crntFunc = functable[ iFTIdx ].op;
                  yylval.object = &functable[ iFTIdx ];
                  token = FUNCTION;
                  found = TRUE;
                  PushnArgs(); // Moved this here from parser.y because it must be called
                               // prior to FUNCTION being reduced i.e. prior to arglist being
                               // processed.
						siInsertFuncMode = 1;   /* SAC 8/14/12 */
					}
				}
			}
         if ( !found )
            ;

         if (siInsertFuncMode > 0)  /* SAC 8/14/12 */
			{	parseChar = saveParseChar;  /* reset parseChar to RE-parse the same string again */
				siInsertFuncMode++;  /* inserted function argument parsed as normal */
			}
      }
      else
      {
         switch ( *parseChar )
         {
            case '*' :
            {   
               if ( parseChar[ 1 ] == '*' )
               {
                  token = POW;
                  parseChar++;
               }   
               else 
                  token = '*';
               break;
            }
            case '=' :
            {
               token = EQ;  
               if ( parseChar[1] == '=' ) 
                  parseChar++; /* No assignment op so let's let '=' and '==' be EQ */
               break;
            }

            case '<' :
            {
               if ( parseChar[ 1 ] == '>' )
               {
                  token = NEQ;
                  parseChar++;
               }
               else if ( parseChar[ 1 ] == '=' )
               {
                  token = LE;
                  parseChar++;
               }
               else
                  token = LT;
               break;
            }
            case '>' :
               if ( parseChar[ 1 ] == '=' )
               {
                  token = GE;
                  parseChar++;
               }
               else
                  token = GT;
               break;
            case '&' :
               if ( parseChar[ 1 ] == '&' )
               {
                  token = AND;
                  parseChar++;
               }
               else 
                  token = *parseChar;
               break;
            case '|' :
            {
               if ( parseChar[ 1 ] == '|' )
               {
                  token = OR;
                  parseChar++;
               }
               else
                  token = OR; // TO DO: Implement bitwise or?
               break;
            }
            case '!' :
            {
               if ( parseChar[ 1 ] == '=' )
               {
                  token = NEQ;
                  parseChar++;
               }
               else
                  token = NOT;
               break;
            }

            case '.' :
            {
               token = GetFortranComparisonOp( &parseChar );
               if ( !token )
                  token = *parseChar;
               break;
            }
            default :
               token = *parseChar;
               break;
         }
         parseChar++;

		/*	if (crntFunc > 0 && ( token == EQ || token == NEQ || token == LE || token == LT ||   *
       *                         token == GE || token == GT  ) &&                             *
		 *		 CurrentFunctionAllowsConditionalOperators( crntFunc ))                           */
		/* SAC 2/14/14 - added code to track nested functions */
			if (GetCurrentFunctionTracked() > 0 && ( token == EQ || token == NEQ || token == LE || token == LT ||
                               token == GE || token == GT  ) &&
				 CurrentFunctionAllowsConditionalOperators( GetCurrentFunctionTracked() ))
			{	// SAC 2/20/13 - switch from basic binary operator to an operator that can be evaluated WITHIN BEM function
            //yylval.index = (long) token;
            //token = BEMPELEM;
			   AddnArg();
				ExpAddBldgElemNode( (long long) token );
				token = 44;  // ','
			}
      }
   }

	if (     token == 40)  /* '(' */
		AddCurrentFunctionToTracking( crntFunc );
	else if (token == 41)  /* ')' */
		ReduceCurrentFunctionToTracking();

   return token;
}

/********************************************************************************************
   Expression Parsing routines
*********************************************************************************************/

void ParseExpression( const char* psTextExp, ParsedExpression* pCompExp, 
                      PFGetVar pfGetNodeType, PFSelectFunction pfSelectFunc, ExpError* pError )
{
   if ( pCompExp != NULL )
      ExpListDelete( pCompExp );

   CLEARERROR( pError );

   topNarg = NULL;

   if ( psTextExp == NULL )
      ExpSetError( pError, EXP_NoFormula, NULL  );
   else
   {
      parseList        = pCompExp;
      parseString = parseChar = psTextExp;
      parseGetVar      = pfGetNodeType;
		parseSelectFunc  = pfSelectFunc;  /* SAC 8/14/12 */
      parseCurrentLine = 0;
      parseStartPos    = 0;
      parseEndPos      = 0;
      parseError       = pError;
      yyparse();
   }
   while ( topNarg != NULL )              
      (void)GetnArgs();
}

BOOL SetErrorFunc( PFErrorFunc pFunc )
{
   errorFunction = pFunc;
   return( TRUE );
}

#define ERRORSTRINGLEN 40  	/* SAC 3/14/13 - 20->40 */

int yyerror( const char* string )
{	string;
   if ( EXP_ERRORCODE( *parseError ) == EXP_None )
   {
      static char tmpString[ ERRORSTRINGLEN ];
      int  index = (int) (parseChar - parseString);

      if ( index <= sizeof( tmpString ) / 2 )
         index = 0;
      else
         index -= sizeof( tmpString ) / 2;

      strncpy( tmpString, &parseString[ index ], sizeof( tmpString ) );
      tmpString[ ERRORSTRINGLEN - 1 ] = '\0'; 
/* 
      something = parseCurrentLine;
      something = parseStartPos;
      something = parseEndPos;
*/
      ExpSetError( parseError, EXP_Syntax, tmpString );
   }
   return( 0 );
}

/********************************************************************************************
   Expression Evaluation routines
*********************************************************************************************/

extern void EvaluateExpression( ParsedExpression* pExp, PFGetValue pfGetValue,
                                PFFormulaFunction pfBEMPFunc, void* pData, 
                                void* pResult, ExpError* pError )
{
   ExpNode* firstNode = ExpListHead( pExp );

   pfBEMPFunctionCall = pfBEMPFunc;

   CLEARERROR( pError );

   if ( ExpListCount( pExp ) == 0 )
   {
      ExpSetError( pError, EXP_NoFormula, NULL );
      return;
   }
   if ( ExpListCount( pExp ) == 1 && firstNode->type != EXP_Function )
   {
      if( firstNode->type == EXP_Value || firstNode->type == EXP_String )
      {
         if ( !ExpNodeCopy( pResult, firstNode ) )
            ExpSetError( pError, EXP_NoMem, NULL );
      }
      else
         pfGetValue( pResult, firstNode, pData );
   }
   else
   {
      ExpStack stack;
      ExpNode* node;

      ExpStackInit( &stack, ExpListCount( pExp ) );

      for ( node = ExpListHead( pExp ); 
            node != NULL && EXP_ERRORCODE( *pError ) == EXP_None; 
            node = ExpListNext( pExp, node ) )
      {
         switch ( node->type )
         {
            case EXP_Value :
            case EXP_String :
               if ( !ExpStackPushCopy( &stack, node ) )
                  ExpSetError( pError, EXP_NoMem, NULL );
               break;

            case EXP_If:
            {
               ExpNode* testValue;
               testValue = ExpStackPop( &stack );
               if ( !testValue->fValue )
               {
                  node = SkipTilNode( pExp, node, EXP_Else );
                  /* Skip else node */
               }
               ExpNodeDelete( testValue );
               break;
            }

            case EXP_Else:   /* There is no THEN node, The ELSE node goes after the  */
                             /* then expression and before the ELSE expression. */
               node = SkipTilNode( pExp, node, EXP_Endif ); 
               /* Skip endif node */
               break;

            case EXP_Endif: /* Skip endif node */
               break;

            case EXP_Switch:
            {
               ExpNode* switchValueNode = ExpStackPop( &stack );
               ExpNode* caseValueNode   = ExpListNext( pExp, node );

               while ( !IsEqual( switchValueNode, caseValueNode ) && 
                        caseValueNode->type != EXP_Default )
               {
                  node = SkipTilNode( pExp, ExpListNext( pExp, node ), EXP_Case );
                  caseValueNode = ExpListNext( pExp, node );
               }
               node = ExpListNext( pExp, node );
               ExpNodeDelete( switchValueNode );
               break;
            }

            case EXP_Case:
            case EXP_Default:
               node = SkipTilNode( pExp, node, EXP_EndSwitch ); 
               break;

            case EXP_EndSwitch :
               break;

            case EXP_Function :
               evalFunctions[ node->fn.function ]( &stack, node->fn.op, 
                                                        node->fn.nArgs, pData, pError );
               break;

            default :
            {
               ExpNode newNode;
					ExpNode_init( &newNode );	// SAC 4/21/17
               pfGetValue( &newNode, node, NULL );

               if( !ExpStackPushCopy( &stack, &newNode ) )
                  ExpSetError( pError, EXP_NoMem, NULL );

               if ( newNode.type == EXP_String )
                  free( newNode.pValue );

               break;
            }
         }
      }
      if( EXP_ERRORCODE( *pError ) == EXP_None )
      {
         ExpNode* resultNode = ExpStackPop( &stack );

         if( resultNode == NULL )
            ExpSetError( pError, EXP_Underflow, NULL );
         else 
         {
            if ( !ExpNodeCopy( pResult, resultNode ) )
               ExpSetError( pError, EXP_NoMem, NULL );
            ExpNodeDelete( resultNode );
         }
            
         if( ExpStackPop( &stack ) != NULL )
            ExpSetError( pError, EXP_Overflow, NULL );
      }
      ExpStackDelete( &stack );
   }
}

extern BOOL CheckExpDependence( ParsedExpression* pExp, long lBEMPFunc, char* pParamName,
                                ExpError* pError )
{
   BOOL bRetVal = FALSE;

//   ExpNode* firstNode = ExpListHead( pExp );

   ExpNode* node;

//   BOOL bFoundParam = FALSE;
	lBEMPFunc;	pParamName;

	CLEARERROR( pError );

   if ( ExpListCount( pExp ) == 0 )
   {
      ExpSetError( pError, EXP_NoFormula, NULL );
      return FALSE;
   }

   for ( node = ExpListHead( pExp ); 
         node != NULL && EXP_ERRORCODE( *pError ) == EXP_None; 
         node = ExpListNext( pExp, node ) )
   {
      switch ( node->type )
      {
// Commented this out because BF_Parameter is no longer used 
// and has been removed from the list.

//         case EXP_String :
//         {
//            if ( (lBEMPFunc == BF_Parameter) && (!bFoundParam) &&
//                 (pParamName != NULL) &&
//                 (strcmp( pParamName, node->pValue ) == 0) )
//               bFoundParam = TRUE;
//            break;
//         }
//         case EXP_Function :
//         {
//            if ( (node->fn.function == BEMPFuncIndex) &&
//                 (node->fn.op == lBEMPFunc) &&
//                 ((lBEMPFunc != BF_Parameter) || (bFoundParam)) )
//               bRetVal = TRUE;
//            break;
//         }
         default :
         {
            break;
         }
      }
   }

   if( EXP_ERRORCODE( *pError ) == EXP_None )
   {
      /* Shouldn't have to delete nodes since calling function calls
       * ExpListDelete() upon return.
       */
   }

   return bRetVal;
}


static BOOL IsEqual( ExpNode* node1, ExpNode* node2 )
{
   BOOL isEqual = FALSE;
   if ( node1->type == node2->type )
   {
      if ( node1->type == EXP_Value )
         isEqual = node1->fValue == node2->fValue;
      else if ( node1->type == EXP_String )
         isEqual = stricmp_( (char*)node1->pValue, (char*)node2->pValue ) == 0;
      /* Compare for strings is case insensitive. */
   }
   return isEqual;
}

static ExpNode* SkipTilNode( ParsedExpression* pExp, ExpNode* node, 
                             ExpNodeType nodeType )
{
   int switchCount = 0;
   int ifCount = 0;   
   BOOL done = FALSE;

   while ( !done )
   {
      node = ExpListNext( pExp, node );
      if ( node->type == nodeType )
      {
         /* If either of these are positive, we are inside a new switch or if  */
         /* block.  If this is the case we want to skip the whole block so  */
         /* keep going until the block is closed. */
         if ( switchCount == 0 && ifCount == 0 )
            done = TRUE;
      }
      switch( node->type )
      {   
         case EXP_If:
            ifCount++;
            break;

         case EXP_Endif:
            ifCount--;  /* Should never get negative if the eq parsed right. */
            break;

         case EXP_Switch:
            switchCount++;
            break;

         case EXP_EndSwitch:
            switchCount--;  /* Should never get negative if the eq parsed right. */
            break;

         default: /* Anything else, just skip it. */
            break;
      }
   }

   return( node );
}

void ExpSetError( ExpError* pError, ExpErrorCode code, const char* text )
{
   pError->code = code;
   if( code > 0 && code < ( sizeof( errorMessages ) / sizeof( *errorMessages ) ) )
   {
/* SAC 1/31/01 - Added additional if statement to prevent error caused when errorMessages[ code ] takes no arguments */
      if (text == NULL)
         sprintf( pError->string, errorMessages[ code ] );
      else if (code == EXP_RuleProc)
		{	/* SAC 5/20/14 - avoid redundent 'Error' reporting */
			if (strlen(text) > 5 && (text[0]=='E' || text[0]=='e') &&
											(text[1]=='R' || text[1]=='r') &&
											(text[2]=='R' || text[2]=='r') &&
											(text[3]=='O' || text[3]=='o') &&
											(text[4]=='R' || text[4]=='r') )
	         sprintf( pError->string, errorMessages[EXP_RuleWarn], text );	/* SAC 9/4/14 - was: "%.511s", text ); */
			else
	         sprintf( pError->string, errorMessages[ code ], text );
		}
		else
         sprintf( pError->string, errorMessages[ code ], text );
   }
   else
      strcpy( pError->string, "Invalid error code" );
}
                                      
static void UnaryFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error )
{
   ExpNode* node;				nArgs;

   EXP_ERRORCODE( *error ) = EXP_None;

   if( ( node = ExpStackPop( stack ) ) == NULL )
      ExpSetError( error, EXP_Underflow, NULL );
   else
   {
      if ( node->type == EXP_String )
         StringUnaryFunc( stack, op, node, pData, error );
      else
      {
         char temp[ 80 ];

         switch( op )
         {
            case NEG :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "negation" );
					else
               	node->fValue = -node->fValue;
               break;
            case OP_Log :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "log()" );
               else if( node->fValue <= 0.0 )
                  ExpSetError( error, EXP_NegLog, NULL );
               node->fValue = log( node->fValue );
               break;
            case OP_Exp :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "exp()" );
					else
               	node->fValue = exp( node->fValue );
               break;
            case OP_Abs :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "abs()" );
					else
               	node->fValue = node->fValue >= 0 ? 
               	                    node->fValue : -node->fValue;
               break;
            case OP_Upr:
            case OP_Lwr :
               node->fValue = 0.0;
               break;
            case OP_Int :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "int()" );
					else
               	node->fValue = floor(node->fValue);
               break;
            case OP_Log10 :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "log10()" );
               else if( node->fValue <= 0.0F )
                  ExpSetError( error, EXP_NegLog, NULL );
               node->fValue = log10(node->fValue);
               break;
            case OP_Sin :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "sin()" );
					else
               	node->fValue = sin(node->fValue);
               break;
            case OP_ASin :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "asin()" );
               else if( node->fValue <= -1 || node->fValue >= 1 )
                  ExpSetError( error, EXP_Trig, NULL );
               node->fValue = asin(node->fValue);
               break;
            case OP_Cos :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "cos()" );
					else
               	node->fValue = cos(node->fValue);
               break;
            case OP_ACos :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "acos()" );
               else if( node->fValue <= -1 || node->fValue >= 1 )
                  ExpSetError( error, EXP_Trig, NULL );
               node->fValue = acos(node->fValue);
               break;
            case OP_Tan :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "tan()" );
					else
               	node->fValue = tan(node->fValue);
               break;
            case OP_ATan :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "atan()" );
					else
               	node->fValue = atan(node->fValue);
               break;
            case OP_Sqrt :
					if (IsReserved_UNDEFINED( node->fValue ))
						ExpSetError( error, EXP_UndefArg, "sqrt()" );
               else if( node->fValue < 0 )
                  ExpSetError( error, EXP_NegSqrt, NULL );
					else
               	node->fValue = sqrt(node->fValue);
               break;
            case OP_ErrorExp :
               break;
            case OP_Ftoa:
               sprintf( temp, "%f", node->fValue );
               node->type = EXP_String;
               node->pValue = malloc( strlen( temp ) + 1 );
               if ( node->pValue != NULL )
                  strcpy( node->pValue, temp );
               else
                  ExpSetError( error, EXP_NoMem, NULL );
               break;
            default :
               break;
         }
      }
      if( EXP_ERRORCODE( *error ) == EXP_None ) 
         ExpStackPush( stack, node );
   }
}

static void ErrorFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error )
{
   ExpNode* node1;
   ExpNode* node2;
   ExpNode* node3;				op;	nArgs;	pData;

   EXP_ERRORCODE( *error ) = EXP_None;

   /* Only pop the first operand here.  This will be the "argument" to the  */
   /* "error function". */
   if ( ( node3 = ExpStackPop( stack ) ) == NULL || 
        ( node2 = ExpStackPop( stack ) ) == NULL || 
        ( node1 = ExpStackPop( stack ) ) == NULL )
      ExpSetError( error, EXP_Underflow, NULL );
   else
   {
      if ( node3->type == EXP_String && 
           node2->type == EXP_Value  && 
           node1->type == EXP_Value )
      {
         showError( node1->fValue, node2->fValue, node3->pValue );
         free( node3->pValue );
      }
      else
      {
         showError( 99, 0, "Incorrect types for error function" );
      }
   }
   /* Don't push anything new on the stack */
}

static void showError( double type, double num, char* string )
{
   if ( errorFunction != NULL )
      errorFunction( (int)type, (int)num, string );
   else
      ;
}

static void StringUnaryFunc( ExpStack* stack, int op, ExpNode* node, void* pData, ExpError* error )
{	stack;	pData;	error;
   switch( op )
   {
      case OP_Upr :
         strupr_( node->pValue );
         break;
      case OP_Lwr :
         strlwr_( node->pValue );
         break;
      case OP_SLen :  /* SAC 2/11/03 - added strlen() function */
         NodeToValue( node, ((node->type == EXP_String && node->pValue) ? (double) strlen( node->pValue ) : -1) );
         break;
      case OP_Atof :  /* SAC 2/23/16 - added atof() */
			NodeToValue( node, ((node->type == EXP_String && node->pValue) ? strtod( node->pValue, NULL ) : -1) );
         break;
      case NEG :
      case OP_Log :
      case OP_Exp :
      case OP_Abs :
      case OP_Ftoa :
         node->fValue = 0;
         break;
   }
}

static int AreSame(double a, double b)  /*SAC 4/21/17 - added DBL_EPSILON check to handle float representation issues */
{	return (fabs(a-b) < (10.0*DBL_EPSILON) ? 1 : 0);
}

static void BinaryFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error)
{
   ExpNode* node1;
   ExpNode* node2;			nArgs;	pData;

   EXP_ERRORCODE( *error ) = EXP_None;

   if( ( node2 = ExpStackPop( stack ) ) == NULL || ( node1 = ExpStackPop( stack ) ) == NULL )
      ExpSetError( error, EXP_Underflow, NULL );
   else
   {
      if ( node1->type != node2->type )  /* Can't operate on 2 different types, return 0. */
      {
			char sNode1[90], sNode2[90], sOper[20], sFuncErr[280];	/* SAC 12/10/18 */
			NodeToString( node1, sNode1, 90 );
			NodeToString( node2, sNode2, 90 );
			OperatorToString( op, sOper, 20 );
			_snprintf( sFuncErr, 280, "Error: operator cannot be applied to data of different types:  %s %s %s", sNode1, sOper, sNode2 );

         if (node1->type == EXP_String)
            free( node1->pValue );
         node1->fValue = 0;
         node1->type = EXP_Value;
         //ExpSetError( error, EXP_RuleProc, "Error: operator cannot be applied to data of different types" );  // SAC 8/12/12 - added error descriptor to plug into error message
         ExpSetError( error, EXP_RuleProc, sFuncErr );  // SAC 12/10/18 - revised further to echo attempted operation itself
      }
      else if ( node1->type == EXP_String && node2->type == EXP_String ) /* 2 Strings */
      {
         char* str1 = node1->pValue;
         char* str2 = node2->pValue;
         /* SAC 2/24/99 - Fixed string comparison bug associated w/ EQ,NE,LT,GT,LE & GE operations    */
         /*               (comparsions were being performed AFTER one of the two strings were FREEd!) */
         double fVal = 0;
         switch( op )
         {
            case EQ :
               fVal = stricmp_( str1, str2 ) == 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case NEQ :
               fVal = stricmp_( str1, str2 ) != 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case LT :
               fVal = stricmp_( str1, str2 ) < 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case GT :
               fVal = stricmp_( str1, str2 ) > 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case LE :
               fVal = stricmp_( str1, str2 ) <= 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case GE :
               fVal = stricmp_( str1, str2 ) >= 0 ? 1.0 : 0.0;
               free( node1->pValue );
               node1->fValue = fVal;
               node1->type = EXP_Value;
               break;
            case '+' :
            {
               int length = (int) (strlen( str1 ) + strlen( str2 ));
               char* newStr = malloc( length + 1 );
               if ( newStr == NULL )
                  ExpSetError( error, EXP_Underflow, NULL );
               else
               {
                  strcpy( newStr, str1 );
                  strcat( newStr, str2 );
                  newStr[ length ] = '\0';
               }
               free( node1->pValue );
               node1->pValue = newStr;
               break;
            }
				case OP_Find :			/* SAC 2/4/13 - added find() function */
				case OP_FindN :		/* SAC 2/4/13 - added findnocase() function */
				{	if (str1 == NULL || str2 == NULL || strlen( str2 ) < 1 || strlen( str2 ) > strlen( str1 ))
					{	free( node1->pValue );
						node1->fValue = 0;
					}
					else
					{	char* strN = NULL;
						if (op == OP_FindN)
						{	int iL=0;
							for (; iL<1; iL++)
							{	int iC=-1;
								strN = (iL==0 ? str1 : str2);
								while (strN[++iC] != 0)  // NULL)
								{	if (strN[iC] >= 'A' && strN[iC] <= 'Z')
										strN[iC] += 32;	// convert to all lower case
								}
							}
						}
						strN = strstr( str1, str2 );
						free( node1->pValue );
						node1->fValue = (double) (strN ? strN - str1 + 1 : 0);
					}
					node1->type = EXP_Value;
					break;
				}
            case OR :   /* These operators do not apply to strings */
            case AND :  
            case '-' :
            case '*' :
            case '/' :
            case OP_Pow :
            case POW :
            case OP_Min :
            case OP_Max :
            case OP_Mod :  /* SAC 2/18/01 - added mod() function */
            case OP_Round :  /* SAC 11/13/17 - added round() function */
               free( node1->pValue );
               node1->fValue = 0.0;
               node1->type = EXP_Value;
               ExpSetError( error, EXP_RuleProc, "Error: operator incompatible with string data" );  // SAC 8/12/12 - added error descriptor to plug into error message
               break;
         }
      }
      else /* We have 2 numbers  */
      {
         double result=0.;
         double value1 = node1->fValue;
         double value2 = node2->fValue;
         switch( op )
         {
            case OR :
               result = value1 != 0.0 || value2 != 0.0 ? 1.0 : 0.0;
               break;
            case AND :
               result = value1 != 0.0 && value2 != 0.0 ? 1.0 : 0.0;
               break;
            case EQ :
               /*result = value1 == value2 ? 1.0 : 0.0;*/
               result = AreSame( value1, value2 ) ? 1.0 : 0.0;
               break;
            case NEQ :
               /*result = value1 != value2 ? 1.0 : 0.0;*/
               result = AreSame( value1, value2 )==0 ? 1.0 : 0.0;
               break;
            case LT :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '<'" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '<'" );
					else
						result = (value1 < value2 && AreSame( value1, value2 )==0) ? 1.0 : 0.0;
               break;
            case GT :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '>'" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '>'" );
					else
               	result = (value1 > value2 && AreSame( value1, value2 )==0) ? 1.0 : 0.0;
               break;
            case LE :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '<='" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '<='" );
					else
               	result = (value1 <= value2 || AreSame( value1, value2 )) ? 1.0 : 0.0;
               break;
            case GE :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '>='" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '>='" );
					else
               	result = (value1 >= value2 || AreSame( value1, value2 )) ? 1.0 : 0.0;
               break;
            case '+' :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '+'" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '+'" );
					else
               	result = value1 + value2;
               break;
            case '-' :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '-'" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '-'" );
					else
               	result = value1 - value2;
               break;
            case '*' :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "left side of '*'" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "right side of '*'" );
					else
               	result = value1 * value2;
               break;
            case '/' :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "numerator" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "denominator" );
               else if( value2 == 0.0 )
                  ExpSetError( error, EXP_ZeroDiv, NULL );
               else
                  result = value1 / value2;
               break;
            case OP_Pow :
            case POW :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "first argument of pow()" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "second argument of pow()" );
					else
               	/*
               	 * Need to check for legal values.
               	 */
               	result = pow( value1, value2 );
               break;
            case OP_Min :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "first argument of min()" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "second argument of min()" );
					else
               	result = ( value1 < value2 ) ? value1 : value2;
               break;
            case OP_Max :
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "first argument of max()" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "second argument of max()" );
					else
               	result = ( value1 > value2 ) ? value1 : value2;
               break;
            case OP_Mod :  /* SAC 2/18/01 - added mod() function */
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "first argument of mod()" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "second argument of mod()" );
               else if ( (int) value2 == 0 )
                  ExpSetError( error, EXP_ZeroDiv, NULL );
               else
                  result = (int) value1 % (int) value2;
               break;
            case OP_Round :  /* SAC 11/13/17 - added round() function */
					if (IsReserved_UNDEFINED( value1 ))
						ExpSetError( error, EXP_UndefArg, "first argument of round()" );
					else if (IsReserved_UNDEFINED( value2 ))
						ExpSetError( error, EXP_UndefArg, "second argument of round()" );
               else if ( (int) value2 < 1 )
                  ExpSetError( error, EXP_RuleProc, "Error: second argument must be > 0" );
               else
               {	char sNum[32];
						sprintf( sNum, "%.*g", (int) value2, value1 );
						result = atof( sNum );
					}  break;

            /* These operators do not apply to numerics */
            case OP_Find :      /* SAC 2/4/13 - added find() function */
            case OP_FindN :     /* SAC 2/4/13 - added findnocase() function */
               result = 0;
               ExpSetError( error, EXP_RuleProc, "Error: operator/function incompatible with numeric data" );
               break;
         }
         node1->fValue = result;
      }

/*      if( EXP_ERRORCODE( *error ) == EXP_None ) */
/* SAC 6/30/00 - removed above if statement so that the result node would get pushed back onto the stack even if error occurred (mem leak) */
         ExpStackPush( stack, node1 );   /* Re-use node1 */

      ExpNodeDelete( node2 );
   }
}

static void BEMPFunc( ExpStack* stack, int op, int nArgs, void* pData, ExpError* error )
{
   /* since some of the BEM functions have variable arguments, we won't 
      hide the stack from the 2nd level */
   pfBEMPFunctionCall( stack, op, nArgs, pData, error );
}

/********************************************************************************************
   I/O Routines
*********************************************************************************************/

BOOL BlobToParsed( ParsedExpression* pExp, void* blob )
{
   BOOL ok = TRUE;
   char* buffer = (char*)blob;
   long blobSize = *(long*)buffer;
   long nNodes = *(long*)&buffer[ sizeof( long ) ];
   int n;
   long bufferIndex = sizeof( long ) * 2;
   int savedNodeSize = sizeof( ExpNode ) - 8;

   for ( n = 0; n < nNodes && bufferIndex < blobSize && ok; n++ )
   {
      ExpNode* node = ExpNode_new();  //(ExpNode*)malloc( sizeof( ExpNode ) );
      if ( node == NULL )
         ok = FALSE;
      else
      {
         memcpy( (char*)node, (char*)&buffer[ bufferIndex ], savedNodeSize );
         bufferIndex += savedNodeSize;
         
         switch( node->type )
         {
            long strLen;

            case EXP_String :
               strLen = *(long*)&buffer[ bufferIndex ];
               bufferIndex += sizeof( long );
               node->pValue = malloc( (int)strLen + 1 );
               if ( node->pValue == NULL )
               {
                  ok = FALSE;
                  free( node );
               }
               else
               {
                  strncpy( (char*)node->pValue, &buffer[ bufferIndex ], (int)strLen );
                  ((char*)node->pValue)[ strLen ] = '\0';
                  bufferIndex += strLen;
                  ExpListAddTail( pExp, node );
               }
               break;

            default : 
               ExpListAddTail( pExp, node );
               break;
         }
      }
   }
   return ( TRUE );
}

long ParsedToBlob( ParsedExpression* pExp, void** blob, long maxSize )
{
   long blobSize = GetBlobSize( pExp );
   char* buffer;

   if ( blobSize > maxSize )
      return ( 0 );

   buffer = malloc( (int)blobSize + sizeof( long ) + sizeof( long ) );
   if ( buffer == NULL )
      return( FALSE );
   *blob = buffer;

   if ( MakeBlob( pExp, buffer, blobSize ) == FALSE )
      return ( 0 );
      
   return ( blobSize );
}

long int GetBlobSize( ParsedExpression* pExp )
{
   ExpNode* node;
   long int blobSize = sizeof( long ) * 2;
   int nodeSize = sizeof( ExpNode ) - 8;
   for ( node = ExpListHead( pExp ); node != NULL; node = ExpListNext( pExp, node ) )
   {
      switch ( node->type )
      {
         case EXP_String :
            blobSize += (long) (nodeSize + strlen( node->pValue ) + sizeof( long ));
            break;
         default :
            blobSize += nodeSize;
            break;
      }
   }
   return ( blobSize );
}

/*
   BLOB structure.
   This is the structure of the parsed expression which has been made
   contiguous for the purpose of saving the parsed expression to a file. 

   4 bytes (long) total size of blob
   4 bytes (long) number of nodes in parsed expression
   expression nodes
      expression node
         2 bytes type of node
         6 byte union contains either a void pointer, a float, 
                  or a 3-int structure describing a function.
         8 bytes (pointer) pointer to prev & next node.  This is not
                  used in the BLOB, so it is left out.
         0 or more bytes (variable) if the node type is 
                  String, string data comes next:
            4 bytes (long) number of characters in string.
            xx bytes (variable) the actual characters of the string.
*/

BOOL MakeBlob( ParsedExpression* pExp, void* blob, long size )
{
   ExpNode* node;
   BOOL ok = TRUE;
   long bufferIndex = 0;
   /* Note: sing sizeof(ExpNode) - 8 assumes the unused pointers are the last
      thing in the ExpNode struct.  If ExpNode gets re-arranged, this code may
      not work */
   int nodeSize = sizeof( ExpNode ) - 8;

   char* buffer = (char*)blob;
   /* buffersize + nodecount + nodes */
   *(long*)buffer = size;
   *(long*)&buffer[ sizeof( long ) ] = ExpListCount( pExp );
   bufferIndex = sizeof( long ) * 2;

   for ( node = ExpListHead( pExp ); node != NULL; node = ExpListNext( pExp, node ) )
   {
      switch ( node->type )
      {
         case EXP_String :
            /* Node data followed by strlen followed by strlen chars. */
            memcpy( (char*)&buffer[ bufferIndex ], (char*)node, nodeSize );
            bufferIndex += nodeSize;
            *(long*)&buffer[ bufferIndex ] = (long) strlen( node->pValue );
            bufferIndex += sizeof( long );
            strcpy( (char*)&buffer[ bufferIndex ], node->pValue );
            bufferIndex += (long) strlen( node->pValue );
            break;

         default :
            memcpy( (char*)&buffer[ bufferIndex ], (char*)node, nodeSize );
            bufferIndex += nodeSize;
            break;
      }
   }
   return ok;
}



void NodeToValue( ExpNode* node, double fVal )
{
   if (node->type == EXP_String)
      free( node->pValue );

   node->type = EXP_Value;
   node->fValue = fVal;
}


/* SAC 12/10/18 - routine to populate string with description of an ExpNode */
static const char* pszExpNodeTypeDescrip[] = {
            "(invalid node)",       // EXP_Invalid,     
            "(value node)",         // EXP_Value,       
            "(string node)",        // EXP_String,      
            "(index node)",         // EXP_Index,       
            "(keyword node)",       // EXP_Keyword,     
            "(BldgRule node)",      // EXP_BldgRule,    
            "(expression node)",    // EXP_Expression,  
            "(function node)",      // EXP_Function,    
            "(LookupFunc node)",    // EXP_LookupFunc,  
            "(If node)",            // EXP_If,          
            "(Else node)",          // EXP_Else,        
            "(Endif node)",         // EXP_Endif,       
            "(Switch node)",        // EXP_Switch,      
            "(Default node)",       // EXP_Default,     
            "(Case node)",          // EXP_Case,        
            "(EndSwitch node)"  };  // EXP_EndSwitch    
void NodeToString( ExpNode* node, char* str, int iStrLen )
{	switch (node->type)
	{	case EXP_Value       :  _snprintf( str, iStrLen, "%g %s",   node->fValue, pszExpNodeTypeDescrip[node->type] );   break;
		case EXP_String      :  _snprintf( str, iStrLen, "'%s' %s", node->pValue, pszExpNodeTypeDescrip[node->type] );   break;
	//	case EXP_Invalid     :
	//	case EXP_Index       :
	//	case EXP_Keyword     :
	//	case EXP_BldgRule    :
	//	case EXP_Expression  :
	//	case EXP_Function    :
	//	case EXP_LookupFunc  :
	//	case EXP_If          :
	//	case EXP_Else        :
	//	case EXP_Endif       :
	//	case EXP_Switch      :
	//	case EXP_Default     :
	//	case EXP_Case        :
	//	case EXP_EndSwitch   :
		default              :  _snprintf( str, iStrLen, "%s", pszExpNodeTypeDescrip[node->type] );   break;
	}
}

void OperatorToString( int oper, char* str, int iStrLen )
{	switch (oper)
	{	case  EXP_ERROR :  _snprintf( str, iStrLen, "<error>" );   break;
		case  IFF       :  _snprintf( str, iStrLen, "<if>" );   break;
		case  THEN      :  _snprintf( str, iStrLen, "<then>" );   break;
		case  ELSE      :  _snprintf( str, iStrLen, "<else>" );   break;
		case  ENDIF     :  _snprintf( str, iStrLen, "<endif>" );   break;
		case  SWITCH    :  _snprintf( str, iStrLen, "<switch>" );   break;
		case  CASE      :  _snprintf( str, iStrLen, "<case>" );   break;
		case  DEFAULT   :  _snprintf( str, iStrLen, "<default>" );   break;
		case  ENDSWITCH :  _snprintf( str, iStrLen, "<endswitch>" );   break;
		case  OR        :  _snprintf( str, iStrLen, "<or>" );   break;
		case  AND       :  _snprintf( str, iStrLen, "<and>" );   break;
		case  EQ        :  _snprintf( str, iStrLen, "=" );   break;
		case  NEQ       :  _snprintf( str, iStrLen, "!=" );   break;
		case  LT        :  _snprintf( str, iStrLen, "<" );   break;
		case  GT        :  _snprintf( str, iStrLen, ">" );   break;
		case  LE        :  _snprintf( str, iStrLen, "<=" );   break;
		case  GE        :  _snprintf( str, iStrLen, ">=" );   break;
		case  POW       :  _snprintf( str, iStrLen, "<power>" );   break;
		case  NOT       :  _snprintf( str, iStrLen, "<not>" );   break;
		case  POS       :  _snprintf( str, iStrLen, "<pos>" );   break;
		case  NEG       :  _snprintf( str, iStrLen, "<neg>" );   break;
		case  CONSTANT  :  _snprintf( str, iStrLen, "<constant>" );   break;
		case  STRING    :  _snprintf( str, iStrLen, "<string>" );   break;
		case  KEYWORD   :  _snprintf( str, iStrLen, "<keyword>" );   break;
		case  FUNCTION  :  _snprintf( str, iStrLen, "<function>" );   break;
		case  REFFUNC   :  _snprintf( str, iStrLen, "<ref function>" );   break;
		case  BEMVAR    :  _snprintf( str, iStrLen, "<BEM var>" );   break;
		case  BEMPELEM  :  _snprintf( str, iStrLen, "<BEMP element>" );   break;
		case  BEMPTABLE :  _snprintf( str, iStrLen, "<BEMP table>" );   break;
		default         :  _snprintf( str, iStrLen, "<??>" );   break;
	}
}

#pragma warning(default : 4996)

