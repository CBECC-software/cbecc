/* formula.h - header file defining a variety of enums, structures and
 *             functions used to parse and evaluate expressions.
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

#ifndef FORMULA_H
#define FORMULA_H

#include "expParser.h"

#ifndef NULL
#define NULL 0
#endif

typedef int BOOL;

#ifndef FALSE
#define FALSE 0
#define TRUE  1
#endif

#define BEMProcErr_MSGLEN 512   /* SAC 1/22/14 - error msg length 160->256 */ /* SAC 12/24/07 - increased error msg length from 80 to 160 chars */ /* SAC 9/4/14 - doubled err msg len to 512 */

#define MAXSYMBOLLENGTH   100
#define MAXEQUATIONLENGTH 256

#define VAR_ARGS -1  /* nArgs for variable argument functions */

typedef enum optypes_   /* types other than what the parser generates */
{                       /* must be > 0 and < 255 */
   OP_Log,        /*  0 */
   OP_Exp,        /*  1 */
   OP_Pow,        /*  2 */
   OP_Abs,        /*  3 */
   OP_Upr,        /*  4 */
   OP_Lwr,        /*  5 */
   OP_Min,        /*  6 */
   OP_Max,        /*  7 */
   OP_Int,        /*  8 */
   OP_Log10,      /*  9 */
   OP_Sin,        /* 10 */
   OP_ASin,       /* 11 */
   OP_Cos,        /* 12 */
   OP_ACos,       /* 13 */
   OP_Tan,        /* 14 */
   OP_ATan,       /* 15 */
   OP_Sqrt,       /* 16 */
   OP_Ftoa,       /* 17 */
   OP_Mod,        /* 18 */  /* SAC 2/18/01 - added mod() function */
   OP_SLen,       /* 19 */  /* SAC 2/11/03 - added strlen() function */
   OP_Find,       /* 20 */  /* SAC 2/4/13 - added find() function */
   OP_FindN,      /* 21 */  /* SAC 2/4/13 - added findnocase() function */
   OP_Atof,       /* 22 */  /* SAC 2/23/16 - added atof() */
   OP_Round,      /* 23 */  /* SAC 11/13/17 - added round() - round to specified digits */
   OP_ErrorExp,   /* 24 */

   BF_Global,        /*  25 */
   BF_Local,         /*  26 */
   BF_Parent,        /*  27 */
   BF_Parent2,       /*  28 */
   BF_Parent3,       /*  29 */
   BF_LocalRef,      /*  30 */
   BF_ParentRef,     /*  31 */
   BF_Parent2Ref,    /*  32 */
   BF_Parent3Ref,    /*  33 */
   BF_SymValue,      /*  34 */
   BF_SumChld,       /*  35 */
   BF_SumAll,        /*  36 */
   BF_RuleLib,       /*  37 */
   BF_ChildRef,      /*  38 */
   BF_Lookup,        /*  39 */
   BF_ChildCnt,      /*  40 */
   BF_SumRevRef,     /*  41 */
   BF_MaxChild,      /*  42 */
   BF_MaxAll,        /*  43 */
   BF_MaxRevRef,     /*  44 */
   BF_CurTime,       /*  45 */
   BF_Date,          /*  46 */
   BF_CheckSym,      /*  47 */
   BF_EvalRules,     /*  48 */
   BF_Cr8Child,      /*  49 */
   BF_DelChild,      /*  50 */
   BF_Cr8Comp,       /*  51 */
   BF_DelComp,       /*  52 */
   BF_DelAllComps,   /*  53 */
   BF_StoreBEMProc,  /*  54 */
   BF_LCompAssign,   /*  55 */
   BF_PCompAssign,   /*  56 */
   BF_LIsDefault,    /*  57 */
   BF_PIsDefault,    /*  58 */
   BF_CurYear,       /*  59 */
   BF_MinChild,      /*  60 */
   BF_MinAll,        /*  61 */
   BF_MinRevRef,     /*  62 */
   BF_FltToStr,      /*  63 */
   BF_LocSymStr,     /*  64 */
   BF_CompIdx,       /*  65 */
   BF_ChildIdx,      /*  66 */
   BF_MoDaShift,     /*  67 */
   BF_ShiftProf,     /*  68 */
   BF_Format,        /*  69 */  /* SAC  5/14/01 - added */
   BF_LocStatus,     /*  70 */  /* SAC  5/16/01 - added */
   BF_ParStatus,     /*  71 */  /* SAC  5/16/01 - added */
   BF_PostError,     /*  72 */  /* SAC  5/21/01 - added */
   BF_PostWarn,      /*  73 */  /* SAC  5/21/01 - added */
   BF_CompExists,    /*  74 */  /* SAC  7/ 6/01 - added */
   BF_GlobSymStr,    /*  75 */  /* SAC  7/25/01 - added */
   BF_WizZoning,     /*  76 */  /* SAC  8/23/01 - added */
   BF_GlobStatus,    /*  77 */  /* SAC  8/24/01 - added */
   BF_AllocAreas,    /*  78 */  /* SAC 12/16/01 - added */
   BF_CountRefs,     /*  79 */  /* SAC  1/ 3/02 - added */
   BF_CompName,      /*  80 */  /* SAC  1/ 3/02 - added */
   BF_CountUPRefs,   /*  81 */  /* SAC  1/ 4/02 - added */
   BF_CountNoRefs,   /*  82 */  /* SAC  1/ 4/02 - added */
   BF_MaxRevRefC,    /*  83 */  /* SAC  1/ 9/02 - added */
   BF_MaxAllComp,    /*  84 */  /* SAC  1/24/02 - added */
   BF_PosShell,      /*  85 */  /* SAC  3/26/02 - added */
   BF_CompCnt,       /*  86 */  /* SAC  4/ 1/02 - added */
   BF_BitMatchCmp,   /*  87 */  /* SAC  4/ 2/02 - added */
   BF_BitMatchCnt,   /*  88 */  /* SAC  4/ 2/02 - added */
   BF_UnqCompName,   /*  89 */  /* SAC  4/ 9/02 - added */
   BF_ZBAZoning,     /*  90 */  /* SAC  6/25/02 - added */
   BF_DfltAdiabat,   /*  91 */  /* SAC  7/15/02 - added */
   BF_MoDaNumDays,   /*  92 */  /* SAC 10/24/02 - added */
   BF_StrUnique,     /*  93 */  /* SAC  8/25/03 - added */
   BF_FileExists,    /*  94 */  /* SAC  1/ 6/04 - added */
   BF_ImportComp,    /*  95 */  /* SAC  1/ 6/04 - added */
   BF_EnsureChild,   /*  96 */  /* SAC  4/27/04 - added */
   BF_SplitPath,     /*  97 */  /* SAC  11/5/04 - added */
   BF_MaxRevRefA,    /*  98 */  /* SAC 11/10/04 - added */
   BF_CountOccur,    /*  99 */  /* SAC 9/28/07 - added */
   BF_SumToArray,    /* 100 */  /* SAC 9/28/07 - added */
   BF_SumRevRefEx,   /* 101 */  /* SAC 9/28/07 - added */
   BF_LocSymInv,     /* 102 */  /* SAC 9/28/07 - added */ 
   BF_MsgBox,        /* 103 */  /* SAC 9/29/06 - added */
   BF_GlobalRef,     /* 104 */  /* SAC 9/28/07 - added */
   BF_BEMProcDBID,   /* 105 */  /* SAC 6/14/07 - added */
   BF_PostLogMsg,    /* 106 */  /* SAC 10/30/07 - added */
   BF_FindInStr,     /* 107 */  /* SAC 7/2/09 - added */
   BF_RplcInStr,     /* 108 */  /* SAC 11/20/09 - added */
   BF_LocMxStrLen,   /* 109 */  /* SAC 11/20/09 - added */
   BF_ParStrAElem,   /* 110 */  /* SAC 11/20/09 - added */
   BF_ParCompType,   /* 111 */  /* SAC 2/16/10 - added */
   BF_LocArrIdx,     /* 112 */  /* SAC 3/3/10 - added */
   BF_CompArray,     /* 113 */  /* SAC 3/7/11 - added */
   BF_GCompAssign,   /* 114 */  /* SAC 5/12/12 - added */
   BF_HrlyResSum,    /* 115 */  /* SAC 5/15/12 - added */
   BF_HrlyResMult,   /* 116 */  /* SAC 5/15/12 - added */
   BF_CompType,      /* 117 */  /* SAC 8/20/10 - added */
   BF_SumAcrsIf,     /* 118 */  /* SAC 2/15/13 - added */
   BF_SumChldIf,     /* 119 */  /* SAC 2/15/13 - added */
   BF_PolyLpArea,    /* 120 */  /* SAC 5/28/13 - added */
   BF_ScalePolyLp,   /* 121 */  /* SAC 5/28/13 - added */
   BF_WriteToFile,   /* 122 */  /* SAC 6/6/13 - added */
   BF_ConsUFctr,     /* 123 */  /* SAC 6/12/13 - added */
   BF_DayltArea,     /* 124 */  /* SAC 10/1/13 - added */
   BF_LogDuration,   /* 125 */  /* SAC 10/24/13 - added */
   BF_InitPolyLp,    /* 126 */  /* SAC 10/29/13 - added */
   BF_GlobalVal,     /* 127 */  /* SAC 2/13/14 - added */
   BF_LocalVal,      /* 128 */  /* SAC 2/13/14 - added */
   BF_ParentVal,     /* 129 */  /* SAC 2/13/14 - added */
   BF_Parent2Val,    /* 130 */  /* SAC 2/13/14 - added */
   BF_Parent3Val,    /* 131 */  /* SAC 2/13/14 - added */
   BF_IfValidAnd,    /* 132 */  /* SAC 2/13/14 - added */
   BF_Cr8PolyLp,     /* 133 */  /* SAC 2/18/14 - added */
   BF_ConsUFctrR,    /* 134 */  /* SAC 2/21/14 - added */
   BF_Cr8SCSysRpt,   /* 135 */  /* SAC 3/10/14 - added */
   BF_AsgnCr8Comp,   /* 136 */  /* SAC 3/11/14 - added */
   BF_Cr8DHWRpt,     /* 137 */  /* SAC 3/14/14 - added */
   BF_Cr8IAQRpt,     /* 138 */  /* SAC 3/26/14 - added */
   BF_ValidOr,       /* 139 */  /* SAC 4/1/14 - added */
   BF_LocRefSymStr,  /* 140 */  /* SAC 4/10/14 - added */
   BF_ParSymStr,     /* 141 */  /* SAC 4/10/14 - added */
   BF_ParRefSymStr,  /* 142 */  /* SAC 4/10/14 - added */
   BF_Par2SymStr,    /* 143 */  /* SAC 4/10/14 - added */
   BF_Par2RefSymStr, /* 144 */  /* SAC 4/10/14 - added */
   BF_Par3SymStr,    /* 145 */  /* SAC 4/10/14 - added */
   BF_Par3RefSymStr, /* 146 */  /* SAC 4/10/14 - added */
   BF_SymString,     /* 147 */  /* SAC 4/10/14 - added */
   BF_Cr8DUHVAC,     /* 148 */  /* SAC 6/28/14 - added */
   BF_MaxChildC,     /* 149 */  /* SAC 10/18/14 - added */
   BF_MinChildC,     /* 150 */  /* SAC 10/18/14 - added */
   BF_YrMoDa2Date,   /* 151 */  /* SAC 10/31/14 - added */
   BF_Date2WkDay,    /* 152 */  /* SAC 10/31/14 - added */
   BF_Date2Mo,       /* 153 */  /* SAC 10/31/14 - added */
   BF_Date2Yr,       /* 154 */  /* SAC 10/31/14 - added */
   BF_YrMoDa2DOW,    /* 155 */  /* SAC 10/31/14 - added */
   BF_Cr8DURpt,      /* 156 */  /* SAC 11/15/14 - added */
   BF_ListRevRef,    /* 157 */  /* SAC 1/26/15 - added */
   BF_ListRevRefIf,  /* 158 */  /* SAC 1/26/15 - added */
   BF_OpenExpFile,   /* 159 */  /* SAC 9/15/15 - added */
   BF_WriteExpFile,  /* 160 */  /* SAC 9/15/15 - added */
   BF_CloseExpFile,  /* 161 */  /* SAC 9/15/15 - added */
   BF_StrToFlt,      /* 162 */  /* SAC 2/23/16 - added */
   BF_Cr8DUWHtr,     /* 163 */  /* SAC 5/29/16 - added */
   BF_AddCSERptCol,  /* 164 */  /* SAC 11/14/16 - added */
   BF_HrlyResMltNEM, /* 165 */  /* SAC 1/23/17 - added */
   BF_HrlyResMltNeg, /* 166 */  /* SAC 10/4/17 - added */
   BF_CopyHrlyRes,   /* 167 */  /* SAC 10/5/17 - added */
   BF_GlobRefSymStr, /* 168 */  /* SAC 4/4/18 - added */
   BF_SchSum,        /* 169 */  /* SAC 8/17/18 - added */
} OpTypes;

typedef enum fmerrorcode_
{
   EXP_None,          /* No error */
   EXP_NoMem,         /* Out of memory */
   EXP_Underflow,     /* Evaluation stack underflow */
   EXP_Overflow,      /* Evaluation stack overflow */
   EXP_ZeroDiv,       /* Division by zero */
   EXP_NegLog,        /* Log of non-positive number */
   EXP_NegSqrt,       /* Sqrt of a negative number */
   EXP_Trig,          /* Trig parameter out of range */
   EXP_Syntax,        /* Syntax error */
   EXP_BadName,       /* Undefined name */
   EXP_NoParser,      /* Undefined parse function */
   EXP_NoFormula,     /* No formula string to parse */
   EXP_BadArgs,       /* Wrong number of arguments */
   EXP_UndefArg,      /* An arithmetic argument is undefined */   /* SAC 2/12/14 */
   EXP_RuleProc,      /*  (string passed in from RuleProc)  */
   EXP_RuleWarn,      /*  (string passed in from RuleProc) - Warning only => evaluation doesn't fail  */
} ExpErrorCode;

typedef enum
{                  /* each expression node must be of one of these types */
   EXP_Invalid,
   EXP_Value,
   EXP_String,
   EXP_Index,
   EXP_Keyword,
   EXP_BldgRule,
   EXP_Expression,
   EXP_Function,
   EXP_LookupFunc,
   EXP_If,
   EXP_Else,
   EXP_Endif,
   EXP_Switch,
   EXP_Default,
   EXP_Case,
   EXP_EndSwitch
} ExpNodeType;

typedef enum functypes_   /* types other than what the parser generates */
{
   EXP_Unary,
   EXP_Binary,
   EXP_ErrorFunc,
   EXP_BEMPFunc,
   EXP_TableLookup
} FuncTypes;

/* structure used to communicate expression errors */
typedef struct
{
   ExpErrorCode code;                /* error code (enum value) */
   char        string[ BEMProcErr_MSGLEN ];  /* character string describing error */
} ExpError;

#define EXP_ERRORCODE(e) ((e).code)
#define EXP_ERRORMSG(e)  ((e).string)


/* An instance of this structure is created for each and every
 * node in a parsed expression
 */
typedef struct ExpNode
{
   ExpNodeType type;     /* node type */
/*   union    - SAC 4/20/17 - removed union in favor of individual members to avoid some if check issues */
/*   { */
      void* pValue;      /* pointer to a value, typically a character string */
      /* SAC 9/23/99 - switched from float to double */
      double fValue;      /* a floating point value */
      struct
      {
         int function;   /* function ID */
         int op;         /* operation ID */
         int nArgs;      /* this keeps track of the number of function
                          * arguments for variable argument functions  */
      } fn;
/*   } info; */
   /* Note: There is code for saving parsed expressions which 
      depends on pNext being the last thing in this struct. */
   struct ExpNode *pNext;  /* pointer to the next node in list */
   struct ExpNode *pPrev;  /* pointer to the previous node in list */
} ExpNode;
extern ExpNode* ExpNode_new();  /* SAC 4/21/17 - added constructor-like routine to ensure member initialization */
extern void ExpNode_init( ExpNode* pNode );

/* Various function pointer types which get passed in via several exported functions */
typedef void (*PFErrorFunc)( const int type, const int num, const char* string );
typedef int  (*PFSelectFunction)( const char* name, int crntFunc, ExpError* pError );   /* SAC 8/14/12 - SAC 6/3/13 */
typedef BOOL (*PFGetVar)( const char* name, int* type, int crntFunc, void* data );
typedef BOOL (*PFGetValue)( ExpNode* result, const ExpNode* node, void* data );

/* structure which holds a list of expression nodes */
typedef struct
{
   int count;
   ExpNode* head;
   ExpNode* tail;
} ExpNodeList;

/* structure which keeps track of an expression stack */
typedef struct
{
   ExpNode* top;
} ExpStack;

typedef void (*PFFormulaFunction)( ExpStack*, int, int, void*, ExpError * );

/* structure which makes up a parsed expression */
typedef struct
{
   ExpNodeList* nodeList;
} ParsedExpression;

/* Various expression parsing and evaluation functions */
extern void ParseExpression( const char* psTextExp, ParsedExpression* pCompExp, 
                             PFGetVar pfGetNodeType, PFSelectFunction pfSelectFunc, ExpError* pError );
extern void EvaluateExpression( ParsedExpression* pExp, PFGetValue pfGetValue,
                                PFFormulaFunction pfBEMPFunc, void* pData, 
                                void* pResult, ExpError* pError );
extern BOOL CheckExpDependence( ParsedExpression* pExp, long lBEMPFunc, char* pParamName,
                                ExpError* pError );
extern void ExpSetError( ExpError* pError, ExpErrorCode code, const char* text );
extern BOOL SetErrorFunc( PFErrorFunc pFunc );
   
extern void ExpListDelete( ParsedExpression *pParsed );

extern long ParsedToBlob( ParsedExpression* pExp, void** blob, long maxSize );
extern BOOL BlobToParsed( ParsedExpression* pExp, void* blob );
extern long int GetBlobSize( ParsedExpression* pExp );
extern BOOL MakeBlob( ParsedExpression* pExp, void* blob, long size );

extern void NodeToValue( ExpNode* node, double fVal );

extern BOOL ResetCurrentFunctionTracking();  /* SAC 2/14/14 - added to track function nesting */
extern int eiParseCount_IfValidAnd;		/* SAC 1/30/15 - added to ensure all arguments evaluate via *Valid() functions */
extern int eiParseCount_ValidOr;

/* stack functions needed by 2nd level */
extern void ExpNodeDelete( ExpNode* node );
extern BOOL ExpNodeCopy( ExpNode* target, ExpNode* node );
extern void ExpStackPush( ExpStack* stack, ExpNode* node );
extern BOOL ExpStackPushCopy( ExpStack* stack, ExpNode* node );
extern ExpNode* ExpStackPop( ExpStack* stack );

extern int ExpListCount( ParsedExpression *pParsed );
extern ExpNode* ExpListHead( ParsedExpression *pParsed );
extern ExpNode* ExpListNext( ParsedExpression *pParsed, ExpNode* node );
extern ExpNode* ExpListTail( ParsedExpression *pParsed );
extern ExpNode* ExpListPrev( ParsedExpression *pParsed, ExpNode* node );

#endif /* FORMULA_H */
