/**********************************************************************
 *  Copyright (c) 2012-2016, California Energy Commission
 *  Copyright (c) 2012-2016, Wrightsoft Corporation
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

/* # line 45 "parser.y" */
typedef union 
{
   double    value;     /* float    value; */
   long long index;     /* long int index; */
   void*     object;
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define EXP_ERROR 257
#define IFF 258      /* SAC 10/2/13 - switched from NE to NEQ to avoid conflict w/ boost tuple library */
#define THEN 259
#define ELSE 260
#define ENDIF 261
#define SWITCH 262
#define CASE 263
#define DEFAULT 264
#define ENDSWITCH 265
#define OR 266
#define AND 267
#define EQ 268
#define NEQ 269		/* SAC 10/2/13 - switched from NE to NEQ to avoid conflict w/ boost polygon library */
#define LT 270
#define GT 271
#define LE 272
#define GE 273
#define POW 274
#define NOT 275
#define POS 276
#define NEG 277
#define CONSTANT 278
#define STRING 279
#define KEYWORD 280
#define FUNCTION 281
#define REFFUNC 282
#define BEMVAR 283
#define BEMPELEM 284
#define BEMPTABLE 285

/* # line 66 "parser.y" */
#include "expyy.h"
/*
 * If pcyacc is invoked with the -t or -T options, yyparse() will attempt to 
 * open a parse tree file.  If fopen() fails, fprintf( stderr,... ) gets 
 * called.  In a Windows DLL stderr is undefined.  The problem is that pcyacc 
 * adds the code to build this file (surrounded by an if(yytflag)) whether or 
 * not the -t or -T option is selected.  Since we are not using the -t or -T 
 * option, fopen() and fprintf( stderr... ) never get called.  If we don't 
 * declare stderr here, we must edit parser.c each time it is built.  
 * Stdio.h will also be included twice.  This code counts on the second 
 * inclusion being ifdef'd out.  This is not likely to be a problem with other 
 * yaccs on other systems.  Pcyacc must not be invoked with the -t or -T 
 * options when we are compliling the DLL under Windows.  The command line 
 * used is : "pcyacc -Dparser.h parser.y"
 */
#include <stdio.h>
#include "memLkRpt.h"
#ifdef _WINDLL
/* SAC - 12/19/97 - removed in order to compile in VC++5.0 */
/* static FILE* stderr = NULL; */
#endif
YYSTYPE yylval, yyval;
#define YYERRCODE 256
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

int yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  -1, 47,
  41, 41,
  -2, 43,
  -1, 58,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 26,
  -1, 59,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 27,
  -1, 60,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 28,
  -1, 61,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 29,
  -1, 62,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 30,
  -1, 63,
  268, 0,
  269, 0,
  270, 0,
  271, 0,
  272, 0,
  273, 0,
  -2, 31,
  0,
};

#define YYNPROD 55
#define YYLAST 345

int yyact[] = {
      19,      27,      25,      16,      26,      17,      28,      90,
      91,      72,      73,      27,      25,      29,      26,      42,
      28,      69,      70,      66,      40,      71,      27,      25,
      99,      26,      27,      28,      96,      84,      82,      28,
     103,     102,     101,     100,      98,      85,      78,      77,
      27,      25,      57,      26,      50,      28,      49,      48,
      47,      27,      25,      76,      26,      75,      28,      13,
      12,      93,      27,      25,      11,      26,      68,      28,
      41,      15,      27,      25,      89,      26,      39,      28,
      14,       6,       5,      92,      27,      25,       4,      26,
       3,      28,       1,       0,       0,       0,       0,       0,
       0,       0,       0,      83,       0,      74,      27,      25,
      86,      26,       0,      28,       0,      87,       2,       0,
      16,      71,       0,       0,       0,       0,       0,       0,
      27,      25,       0,      26,       0,      28,      43,      44,
      45,      46,       0,       0,       0,       0,      51,      52,
      53,      54,      55,      56,       0,      58,      59,      60,
      61,      62,      63,      64,      65,       0,      67,       0,
       0,      17,      18,      19,      24,       0,       0,       0,
      79,      25,      26,      27,      28,      29,      31,      80,
      32,      33,      34,      35,      36,      37,      38,      40,
      81,      50,       0,     107,     108,       0,      88,       0,
     103,      89,       0,       0,       0,      57,      66,      82,
      95,      99,      97,       0,       0,       0,       0,       0,
       0,       0,       0,       0,     106,      84,     105,      96,
       0,       0,       0,      86,       0,       0,       0,      87,
       0,       0,       0,       0,       0,       0,       0,       0,
      30,       0,      23,       0,       0,       0,      24,       0,
     104,      38,      37,      31,      32,      33,      34,      35,
      36,      29,       0,      18,       0,      30,       7,       8,
       9,      20,      22,      29,      10,      21,      38,      37,
      31,      32,      33,      34,      35,      36,      29,      30,
       0,       0,      29,      94,       0,       0,       0,       0,
      38,      37,      31,      32,      33,      34,      35,      36,
      29,      30,      37,      31,      32,      33,      34,      35,
      36,      29,      38,      37,      31,      32,      33,      34,
      35,      36,      29,      30,      31,      32,      33,      34,
      35,      36,      29,       0,      38,      37,      31,      32,
      33,      34,      35,      36,      29,      30,       0,       0,
       0,       0,       0,       0,       0,       0,      38,      37,
      31,      32,      33,      34,      35,      36,      29,      30,
       0,       0,       0,       0,       0,       0,       0,       0,
      38,      37,      31,      32,      33,      34,      35,      36,
      29,
};

int yypact[] = {
     -40,   -1000,      70,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,    -239,    -248,
     -40,     -40,     -40,     -40,       8,   -1000,       6,       4,
     -40,     -40,     -40,     -40,     -40,     -40,       2,     -40,
     -40,     -40,     -40,     -40,     -40,     -40,     -40,    -241,
     -40,    -246,    -269,   -1000,   -1000,   -1000,      52,   -1000,
      -1,   -1000,     -40,      70,     -16,     -16,    -261,    -261,
   -1000,     -40,     -31,     -31,     -31,     -31,     -31,     -31,
      24,       7,     -40,      70,     -28,    -269,   -1000,     -29,
   -1000,   -1000,   -1000,      -4,     -40,     -40,    -271,      34,
      16,      -2,     -40,     -30,     -40,   -1000,      -5,     -20,
      -6,      -7,     -11,     -12,   -1000,   -1000,   -1000,     -41,
     -40,      70,   -1000,     -40,   -1000,   -1000,    -271,    -271,
   -1000,      70,   -1000,   -1000,   -1000,
};

int yypgo[] = {
       0,      82,     101,      80,      78,      74,      73,      72,
      70,      65,      64,      62,      21,      60,      56,      55,
      53,      51,      96,      47,      38,      68,
};

int yyr1[] = {
       0,       1,       2,       2,       2,       2,       4,       7,
       8,       5,      10,      10,      11,      12,      12,       9,
       6,       6,       6,       6,       6,       6,       6,       6,
       6,       6,       6,       6,       6,       6,       6,       6,
       6,       6,       3,       3,       3,       3,       3,       3,
       3,      16,      13,      17,      13,      19,      14,      18,
      18,      20,      15,      21,      21,      21,      21,
};

int yyr2[] = {
       2,       1,       1,       1,       1,       1,       5,       4,
       2,       6,       4,       5,       1,       1,       1,       2,
       3,       3,       3,       3,       3,       5,       2,       2,
       2,       3,       3,       3,       3,       3,       3,       3,
       3,       3,       1,       1,       1,       1,       1,       1,
       1,       0,       4,       0,       5,       0,       5,       1,
       3,       0,       5,       1,       1,       3,       3,
};

int yychk[] = {
   -1000,      -1,      -2,      -3,      -4,      -5,      -6,     278,
     279,     280,     284,     -13,     -14,     -15,      -7,      -9,
      43,      45,     275,      40,     281,     285,     282,     258,
     262,      43,      45,      42,      47,     274,     257,     268,
     269,     270,     271,     272,     273,     267,     266,      -8,
     259,     -10,     263,      -2,      -2,      -2,      -2,      40,
     -19,      40,      40,      -2,      -2,      -2,      -2,      -2,
      -2,      40,      -2,      -2,      -2,      -2,      -2,      -2,
      -2,      -2,     260,      -2,     -11,     263,     264,     -12,
     278,     279,      41,     -16,     -17,      40,     -20,      -2,
      -2,      -2,      58,     -12,      58,      41,     -18,      -2,
     -18,     -21,     278,     279,      41,      41,     261,      -2,
      58,      -2,      41,      44,      41,      41,      44,      44,
     265,      -2,     -18,     -21,     -21,
};

int yydef[] = {
       0,      -2,       1,       2,       3,       4,       5,      34,
      35,      36,      37,      38,      39,      40,       0,       0,
       0,       0,       0,       0,       0,      45,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,      22,      23,      24,       0,      -2,
       0,      49,       0,      15,      16,      17,      18,      19,
      20,       0,      -2,      -2,      -2,      -2,      -2,      -2,
      32,      33,       0,       8,       0,       0,      12,       0,
      13,      14,      25,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,      42,       0,      47,
       0,       0,      51,      52,       7,      21,       6,       0,
       0,      10,      44,       0,      46,      50,       0,       0,
       9,      11,      48,      53,      54,
};

int *yyxi;


/*****************************************************************/
/* PCYACC LALR parser driver routine -- a table driven procedure */
/* for recognizing sentences of a language defined by the        */
/* grammar that PCYACC analyzes. An LALR parsing table is then   */
/* constructed for the grammar and the skeletal parser uses the  */
/* table when performing syntactical analysis on input source    */
/* programs. The actions associated with grammar rules are       */
/* inserted into a switch statement for execution.               */
/*****************************************************************/


#ifndef YYMAXDEPTH
#define YYMAXDEPTH 200
#endif
#ifndef YYREDMAX
#define YYREDMAX 1000
#endif
#define PCYYFLAG -1000
#define WAS0ERR 0
#define WAS1ERR 1
#define WAS2ERR 2
#define WAS3ERR 3
#define yyclearin pcyytoken = -1
#define yyerrok   pcyyerrfl = 0
YYSTYPE yyv[YYMAXDEPTH];     /* value stack */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */

#pragma warning(disable : 4996)		// SAC 8/31/16

int yyparse()
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, tmptoken, *yyps, n;
  YYSTYPE *yypv;


  tmpstate = 0;
  pcyytoken = -1;
#ifdef YYDEBUG
  tmptoken = -1;
  char parseMsg[80];		// SAC 8/31/16
#endif
  pcyyerrct = 0;
  pcyyerrfl = 0;
  yyps = &statestack[-1];
  yypv = &yyv[-1];


  enstack:    /* push stack */
#ifdef YYDEBUG
    _snprintf(parseMsg, 80, "         yyparse: at state %d, next token %d\n", tmpstate, tmptoken);		// SAC 8/31/16
    ExpPostParserMsg(parseMsg);
#endif
    if (++yyps - &statestack[YYMAXDEPTH] > 0) {
      yyerror("pcyacc internal stack overflow");
      return(1);
    }
    *yyps = tmpstate;
    ++yypv;
    *yypv = yyval;


  newstate:
    n = yypact[tmpstate];
    if (n <= PCYYFLAG) goto defaultact; /*  a simple state */


    if (pcyytoken < 0) if ((pcyytoken=yylex()) < 0) pcyytoken = 0;
    if ((n += pcyytoken) < 0 || n >= YYLAST) goto defaultact;


    if (yychk[n=yyact[n]] == pcyytoken) { /* a shift */
#ifdef YYDEBUG
      tmptoken  = pcyytoken;
#endif
      pcyytoken = -1;
      yyval = yylval;
      tmpstate = n;
      if (pcyyerrfl > 0) --pcyyerrfl;
      goto enstack;
    }


  defaultact:


    if ((n=yydef[tmpstate]) == -2) {
      if (pcyytoken < 0) if ((pcyytoken=yylex())<0) pcyytoken = 0;
      for (yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=tmpstate); yyxi += 2);
      while (*(yyxi+=2) >= 0) if (*yyxi == pcyytoken) break;
      if ((n=yyxi[1]) < 0) { /* an accept action */
        if (yytflag) {
          int ti; int tj;
          fopen_s( &yytfilep, yytfilen, "w" );  // SAC 1/12/10 - was: yytfilep = fopen(yytfilen, "w");
          if (yytfilep == NULL) {
            fprintf(stderr, "Can't open t file: %s\n", yytfilen);
            return(0);          }
          for (ti=redcnt-1; ti>=0; ti--) {
            tj = svdprd[redseq[ti]];
            while (strcmp(svdnams[tj], "$EOP"))
              fprintf(yytfilep, "%s ", svdnams[tj++]);
            fprintf(yytfilep, "\n");
          }
          fclose(yytfilep);
        }
        return (0);
      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror("syntax error");
          yyerrlab:
            ++pcyyerrct;
        case WAS1ERR:
        case WAS2ERR:           /* try again */
          pcyyerrfl = 3;
	   /* find a state for a legal shift action */
          while (yyps >= statestack) {
	     n = yypact[*yyps] + YYERRCODE;
	     if (n >= 0 && n < YYLAST && yychk[yyact[n]] == YYERRCODE) {
	       tmpstate = yyact[n];  /* simulate a shift of "error" */
	       goto enstack;
            }
	     n = yypact[*yyps];


	     /* the current yyps has no shift on "error", pop stack */
#ifdef YYDEBUG
            _snprintf(parseMsg, 80, "         yyparse: error: pop state %d, recover state %d\n", *yyps, yyps[-1]);		// SAC 8/31/16
            ExpPostParserMsg(parseMsg);
#endif
	     --yyps;
	     --yypv;
	   }


	   yyabort:
            if (yytflag) {
              int ti; int tj;
              fopen_s( &yytfilep, yytfilen, "w" );  // SAC 1/12/10 - was: yytfilep = fopen(yytfilen, "w");
              if (yytfilep == NULL) {
                fprintf(stderr, "Can't open t file: %s\n", yytfilen);
                return(1);              }
              for (ti=1; ti<redcnt; ti++) {
                tj = svdprd[redseq[ti]];
                while (strcmp(svdnams[tj], "$EOP"))
                  fprintf(yytfilep, "%s ", svdnams[tj++]);
                fprintf(yytfilep, "\n");
              }
              fclose(yytfilep);
            }
	     return(1);


	 case WAS3ERR:  /* clobber input char */
#ifdef YYDEBUG
          _snprintf(parseMsg, 80, "         yyparse: error: discard token %d\n", pcyytoken);		// SAC 8/31/16
          ExpPostParserMsg(parseMsg);
#endif
          if (pcyytoken == 0) goto yyabort; /* quit */
	   pcyytoken = -1;
	   goto newstate;      } /* switch */
    } /* if */


    /* reduction, given a production n */
#ifdef YYDEBUG
    _snprintf(parseMsg, 80, "         yyparse: reduce with rule %d\n", n);		// SAC 8/31/16
    ExpPostParserMsg(parseMsg);
#endif
    if (yytflag && redcnt<YYREDMAX) redseq[redcnt++] = n;
    yyps -= yyr2[n];
    yypvt = yypv;
    yypv -= yyr2[n];
    yyval = yypv[1];
    m = n;
    /* find next state from goto table */
    n = yyr1[n];
    j = yypgo[n] + *yyps + 1;
    if (j>=YYLAST || yychk[ tmpstate = yyact[j] ] != -n) tmpstate = yyact[yypgo[n]];
    switch (m) { /* actions associated with grammar rules */
      
      case 6:
/* # line 136 "parser.y" */
      { ExpAddControlNode(ENDIF); } break;
      case 7:
/* # line 145 "parser.y" */
      { ExpAddControlNode(IFF); } break;
      case 8:
/* # line 149 "parser.y" */
      { ExpAddControlNode(ELSE); } break;
      case 9:
/* # line 199 "parser.y" */
      { ExpAddControlNode(ENDSWITCH); } break;
      case 10:
/* # line 203 "parser.y" */
      { ExpAddControlNode(CASE); } break;
      case 11:
/* # line 204 "parser.y" */
      { ExpAddControlNode(CASE); } break;
      case 12:
/* # line 208 "parser.y" */
      { ExpAddControlNode(DEFAULT); } break;
      case 13:
/* # line 212 "parser.y" */
      { ExpAddConstantNode(yypvt[-0].value); } break;
      case 14:
/* # line 213 "parser.y" */
      { ExpAddStringNode(yypvt[-0].object); } break;
      case 15:
/* # line 217 "parser.y" */
      { ExpAddControlNode(SWITCH); } break;
      case 16:
/* # line 225 "parser.y" */
      { ExpAddBinOpNode('+'); } break;
      case 17:
/* # line 226 "parser.y" */
      { ExpAddBinOpNode('-'); } break;
      case 18:
/* # line 227 "parser.y" */
      { ExpAddBinOpNode('*'); } break;
      case 19:
/* # line 228 "parser.y" */
      { ExpAddBinOpNode('/'); } break;
      case 20:
/* # line 229 "parser.y" */
      { ExpAddBinOpNode(POW); } break;
      case 21:
/* # line 232 "parser.y" */
      { ExpAddErrNode(EXP_ERROR); } break;
      case 23:
/* # line 234 "parser.y" */
      { ExpAddUnOpNode(NEG); } break;
      case 24:
/* # line 235 "parser.y" */
      { ExpAddUnOpNode(NOT); } break;
      case 26:
/* # line 238 "parser.y" */
      { ExpAddBinOpNode(EQ);  } break;
      case 27:
/* # line 239 "parser.y" */
      { ExpAddBinOpNode(NEQ);  } break;
      case 28:
/* # line 240 "parser.y" */
      { ExpAddBinOpNode(LT);  } break;
      case 29:
/* # line 241 "parser.y" */
      { ExpAddBinOpNode(GT);  } break;
      case 30:
/* # line 242 "parser.y" */
      { ExpAddBinOpNode(LE);  } break;
      case 31:
/* # line 243 "parser.y" */
      { ExpAddBinOpNode(GE);  } break;
      case 32:
/* # line 244 "parser.y" */
      { ExpAddBinOpNode(AND); } break;
      case 33:
/* # line 245 "parser.y" */
      { ExpAddBinOpNode(OR);  } break;
      case 34:
/* # line 250 "parser.y" */
      { ExpAddConstantNode(yypvt[-0].value); } break;
      case 35:
/* # line 251 "parser.y" */
      { ExpAddStringNode(yypvt[-0].object);   } break;
      case 36:
/* # line 252 "parser.y" */
      { ExpAddKeyWordNode( (long) yypvt[-0].index );  } break;
      case 37:
/* # line 253 "parser.y" */
      { ExpAddBldgElemNode(yypvt[-0].index); } break;
      case 41:
/* # line 262 "parser.y" */
      { /* PushnArgs(); */ } break;
      case 42:
/* # line 263 "parser.y" */
      { ExpAddFunctionNode( (long) yypvt[-3].index, GetnArgs()); } break;
      case 43:
/* # line 264 "parser.y" */
      { /* PushnArgs(); */ } break;
      case 44:
/* # line 265 "parser.y" */
      { ExpAddFunctionNode( (long) yypvt[-4].index, GetnArgs()); } break;
      case 45:
/* # line 269 "parser.y" */
      { PushnArgs(); } break;
      case 46:
/* # line 270 "parser.y" */
      { ExpAddTableNode( (long) yypvt[-4].index, GetnArgs()); } break;
      case 47:
/* # line 274 "parser.y" */
      { AddnArg(); } break;
      case 48:
/* # line 275 "parser.y" */
      { AddnArg(); } break;
      case 49:
/* # line 280 "parser.y" */
      { PushnArgs(); } break;
      case 50:
/* # line 281 "parser.y" */
      { ExpAddRefFuncNode( (long) yypvt[-4].index, GetnArgs()); } break;
      case 51:
/* # line 284 "parser.y" */
      { AddnArg(); ExpAddVarArgConst(  yypvt[-0].value ); } break;
      case 52:
/* # line 285 "parser.y" */
      { AddnArg(); ExpAddVarArgString( yypvt[-0].object ); } break;
      case 53:
/* # line 286 "parser.y" */
      { AddnArg(); ExpAddVarArgConst(  yypvt[-2].value ); } break;
      case 54:
/* # line 287 "parser.y" */
      { AddnArg(); ExpAddVarArgString( yypvt[-2].object ); } break;    }
    goto enstack;
}

#pragma warning(default : 4996)		// SAC 8/31/16
