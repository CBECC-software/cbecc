// TreeBDB.cpp : implementation file
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

#include "stdafx.h"
#include "ComplianceUI.h"
#include "TreeBDB.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProperty.h"
#include "..\BEMProcUI\BEMProcUIX.h"
#include "..\BEMProcUI\BEMProcDialog.h"
#include "DlgRename.h"
#include "ComplianceUIDoc.h"
#include <memory>
#include <afxadv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// // Key to tree control indexes:  (enum TREECTRLTYPE)
// //       TC_PROJ_FAMILY,     - 0     TC_ZONE_FAMILY,      - 4     TC_PLANT_FAMILY,    - 8
// //       TC_PROJ_REFERENCE,  - 1     TC_ZONE_REFERENCE,   - 5     TC_PLANT_REFERENCE, - 9
// //       TC_SPACE_FAMILY,    - 2     TC_SYSTEM_FAMILY,    - 6
// //       TC_SPACE_REFERENCE, - 3     TC_SYSTEM_REFERENCE, - 7
// 
// // Initialize CLASSES
// //                        SName      LName                NPs   MD  MR  AC   P1  P2  P3  P4  P5    HI   Nav Tree Assignments
// //                       ----------------------------------------------------------------------------------------------------
//    	aClasses[ 0].Init( "Proj",    "Project",            31,    1,  0,  0,  -1, -1, -1, -1, -1,   1000,  0, -1, -1, -1, -1 );
//    	aClasses[ 1].Init( "Run",     "RunResults",         28,    2,  1,  1,  -1, -1, -1, -1, -1,   2000,  0, -1, -1, -1, -1 );
//    	aClasses[ 2].Init( "Site",    "Site",               34,    1,  0,  0,  -1, -1, -1, -1, -1,   3000,  0, -1, -1, -1, -1 );
//    	aClasses[ 3].Init( "Bldg",    "Building",           20,    1,  0,  0,  -1, -1, -1, -1, -1,   4000,  0, -1, -1, -1, -1 );
//    	aClasses[ 4].Init( "Bshade",  "Building Shade",      8,   64,  0,  0,  -1, -1, -1, -1, -1,   4500,  1, -1, -1, -1, -1 );
//    	aClasses[ 5].Init( "Space",   "Space",              59,   30,  0,  0,  14, -1, -1, -1, -1,   5000,  2,  4, -1, -1, -1 );
//    	aClasses[ 6].Init( "ExtWall", "Exterior Wall",      23,  120,  0,  0,   5, -1, -1, -1, -1,   6000,  2, -1, -1, -1, -1 );
//    	aClasses[ 7].Init( "IntWall", "Interior Wall",      11,  120,  0,  0,   5, -1, -1, -1, -1,   7000,  2, -1, -1, -1, -1 );
//    	aClasses[ 8].Init( "UndWall", "Underground Wall",   11,  120,  0,  0,   5, -1, -1, -1, -1,   8000,  2, -1, -1, -1, -1 );
//    	aClasses[ 9].Init( "Win",     "Window",             41,  300,  0,  0,   6, -1, -1, -1, -1,   9000,  2, -1, -1, -1, -1 );
//    	aClasses[10].Init( "Door",    "Door",                9,  100,  0,  0,   6, -1, -1, -1, -1,  10000,  2, -1, -1, -1, -1 );
//    	aClasses[11].Init( "Cons",    "Construction",        6,  100,  0,  0,  -1, -1, -1, -1, -1,  11000,  3, -1, -1, -1, -1 );
//    	aClasses[12].Init( "Layers",  "Layers",              3,  200,  0,  0,  -1, -1, -1, -1, -1,  12000,  3, -1, -1, -1, -1 );
//    	aClasses[13].Init( "Mat",     "Material",            6,  300,  0,  0,  -1, -1, -1, -1, -1,  13000,  3, -1, -1, -1, -1 );
//    	aClasses[14].Init( "Zone",    "Thermal Zone",       30,   30,  0,  0,  15, -1, -1, -1, -1,  14000,  4,  6, -1, -1, -1 );
//    	aClasses[15].Init( "HVACSys", "HVAC System",        37,   30,  0,  0,  21, -1, -1, -1, -1,  15000,  6,  8, -1, -1, -1 );
//    	aClasses[16].Init( "Size",    "Sizing Rules",       16,   30,  1,  1,  -1, -1, -1, -1, -1,  16000,  6, -1, -1, -1, -1 );
//    	aClasses[17].Init( "HtPump",  "Heat Pump",          21,   30,  1,  0,  -1, -1, -1, -1, -1,  18000,  6, -1, -1, -1, -1 );
//    	aClasses[18].Init( "AirCond", "Air Conditioner",    13,   30,  1,  0,  -1, -1, -1, -1, -1,  19000,  6, -1, -1, -1, -1 );
//    	aClasses[19].Init( "Furn",    "Furnace",             8,   30,  1,  0,  -1, -1, -1, -1, -1,  20000,  6, -1, -1, -1, -1 );
//    	aClasses[20].Init( "Econ",    "Economizer",          3,   30,  1,  0,  -1, -1, -1, -1, -1,  21000,  6, -1, -1, -1, -1 );
//    	aClasses[21].Init( "Plant",   "Plant",              22,   30,  0,  0,  -1, -1, -1, -1, -1,  22000,  8, -1, -1, -1, -1 );
//    	aClasses[22].Init( "Fan",     "Fan",                17,  100,  1,  0,  -1, -1, -1, -1, -1,  17000,  6,  8, -1, -1, -1 );
//    	aClasses[23].Init( "ClTower", "Cooling Tower",       6,   30,  0,  0,  21, -1, -1, -1, -1,  23000,  8, -1, -1, -1, -1 );
//    	aClasses[24].Init( "Chiller", "Chiller",            10,   30,  0,  0,  21, -1, -1, -1, -1,  24000,  8, -1, -1, -1, -1 );
//    	aClasses[25].Init( "Boiler",  "Boiler",              9,   30,  0,  0,  21, -1, -1, -1, -1,  25000,  8, -1, -1, -1, -1 );
//    	aClasses[26].Init( "Pump",    "Pump",               12,   30,  1,  0,  -1, -1, -1, -1, -1,  27000,  8, -1, -1, -1, -1 );
//    	aClasses[27].Init( "Curve",   "Curve",               6,  300,  0,  0,  -1, -1, -1, -1, -1,  28000,  7,  9, -1, -1, -1 );
//    	aClasses[28].Init( "Sched",   "Schedule",            4,  100,  0,  0,  -1, -1, -1, -1, -1,  29000,  1,  3,  5,  7,  9 );
//    	aClasses[29].Init( "WkSch",   "Week Schedule",       1,  200,  0,  0,  -1, -1, -1, -1, -1,  30000,  1,  3,  5,  7,  9 );
//    	aClasses[30].Init( "DaySch",  "Day Schedule",        2,  300,  0,  0,  -1, -1, -1, -1, -1,  31000,  1,  3,  5,  7,  9 );
//    	aClasses[31].Init( "ResSch",  "Reset Schedule",      4,  100,  0,  0,  -1, -1, -1, -1, -1,  32000,  5,  7,  9, -1, -1 );
//    	aClasses[32].Init( "DResSch", "Day Reset Schedule",  4,  300,  0,  0,  -1, -1, -1, -1, -1,  33000,  5,  7,  9, -1, -1 );
/////////////////////////////////////////////////////////////////////////////

// Statics which define the contents of each tree based on the tree's "mode"

//   --------------------------------------------------------------------------
//   -------------------------  ASHRAE 90.1E UI Mode  -------------------------
//   --------------------------------------------------------------------------
#ifdef UI_ASHRAE901E

// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
static int siZero = 0;
static int  siaMode0[]  = { 3, 3, 3 };
static int* siapMode0[] = { &eiBDBCID_Proj, &eiBDBCID_Site, &eiBDBCID_Bldg };
static int  siNumArchComps = 14;
static int  siaMode1[]  = { 2, siNumArchComps, siNumArchComps };
static int* siapMode1[] = { &eiBDBCID_Block, &eiBDBCID_Bshade, &eiBDBCID_ActArea, &eiBDBCID_ExtRoof, &eiBDBCID_IntCeil,
                            &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, &eiBDBCID_FlrWall, &eiBDBCID_Win,
                            &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_Floor, &eiBDBCID_Space };
static int  siNumLtComps = 5;
static int  siaMode2[]  = { 1, siNumLtComps, siNumLtComps };
static int* siapMode2[] = { &eiBDBCID_Block, &eiBDBCID_ActArea, &eiBDBCID_LtSys, &eiBDBCID_Floor, &eiBDBCID_Space };
static int  siaMode3[]  = { 1, 11, 12 };
static int* siapMode3[] = { &eiBDBCID_Plant, &eiBDBCID_HVACSys, &eiBDBCID_ClTower, &eiBDBCID_Chiller,
                            &eiBDBCID_Boiler, &eiBDBCID_HtPump, &eiBDBCID_AirCond, &eiBDBCID_Furn,
                            &eiBDBCID_Econ, &eiBDBCID_Fan, &eiBDBCID_Pump, &eiBDBCID_Space };

static int*  siaModes[]  = { siaMode0,  siaMode1,  siaMode2,  siaMode3 };
static int** siapModes[] = { siapMode0, siapMode1, siapMode2, siapMode3 };
static HTREEITEM shaModes[] = { TVI_LAST, TVI_LAST, TVI_LAST, TVI_LAST };

// Same statics for LIBRARY TREE
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
static int  siaLibMode0[]  = { 3, 3, 3 };
static int* siapLibMode0[] = { &eiBDBCID_Proj, &eiBDBCID_Site, &eiBDBCID_Bldg };
static int  siaLibMode1[]  = { 2, siNumArchComps, siNumArchComps };
static int* siapLibMode1[] = { &eiBDBCID_Bshade, &eiBDBCID_Block, &eiBDBCID_Floor, &eiBDBCID_Space, &eiBDBCID_ActArea,
                               &eiBDBCID_ExtRoof, &eiBDBCID_IntCeil, &eiBDBCID_ExtWall, &eiBDBCID_IntWall,
                               &eiBDBCID_UndWall, &eiBDBCID_FlrWall, &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door };
static int  siaLibMode2[]  = { 1, 3, 3 };  //4, 4 };
static int* siapLibMode2[] = { &eiBDBCID_Space, &eiBDBCID_ActArea, &eiBDBCID_LtSys };  //, &eiBDBCID_LtFix };
static int  siaLibMode3[]  = { 1, 11, 11 };
static int* siapLibMode3[] = { &eiBDBCID_Plant, &eiBDBCID_ClTower, &eiBDBCID_Chiller, &eiBDBCID_Boiler,
                               &eiBDBCID_HVACSys, &eiBDBCID_HtPump, &eiBDBCID_AirCond, &eiBDBCID_Furn,
                               &eiBDBCID_Econ, &eiBDBCID_Fan, &eiBDBCID_Pump };

static int*  siaLibModes[]  = { siaLibMode0,  siaLibMode1,  siaLibMode2,  siaLibMode3 };
static int** siapLibModes[] = { siapLibMode0, siapLibMode1, siapLibMode2, siapLibMode3 };
static HTREEITEM shaLibModes[] = { TVI_LAST, TVI_LAST, TVI_LAST, TVI_LAST };

// Arrays of long pointers for adding children to various component types
static long* slapNULL[]    = { NULL };
static long* slapHVACSys[] = { &elDBID_Sys_HtPump, &elDBID_Sys_AirCond, &elDBID_Sys_Furnace,
                               &elDBID_Sys_AirEcon, &elDBID_Sys_SupplyFan, &elDBID_Sys_ReturnFan, NULL };
static long* slapClTower[] = { &elDBID_CTwr_TowerPump, NULL };
static long* slapChiller[] = { &elDBID_Chlr_CHWPump, &elDBID_Chlr_CWPump, NULL };
static long* slapBoiler[]  = { &elDBID_Boil_HWPump, NULL };
// SAC 6/20/00 - added following static array to cause tree to display Pumps which are assigned directly to Plant components
static long* slapPlant[]   = { &elDBID_Plant_CHWPump, &elDBID_Plant_CWPump, &elDBID_Plant_HPCircPump,
                               &elDBID_Plant_HWPump, NULL };
static long* slapLtSys[]   = { &elDBID_LtSys_Fixture1, &elDBID_LtSys_Fixture2,
                               &elDBID_LtSys_Fixture3, &elDBID_LtSys_Fixture4, NULL };
// SAC 6/30/00 - added to show Space:Fan and Space:ExhaustFan connections
static long* slapSpace[]   = { &elDBID_Spc_Fan, &elDBID_Spc_ExhaustFan, NULL };

static long** ClassToDBIDAssignmentList( int iBDBClass )
{
   if      (iBDBClass == eiBDBCID_HVACSys)   return &slapHVACSys[0];
   else if (iBDBClass == eiBDBCID_ClTower)   return &slapClTower[0];
   else if (iBDBClass == eiBDBCID_Chiller)   return &slapChiller[0];
   else if (iBDBClass == eiBDBCID_Boiler )   return &slapBoiler[0];
   else if (iBDBClass == eiBDBCID_Plant  )   return &slapPlant[0];
//   else if (iBDBClass == eiBDBCID_LtSys  )   return &slapLtSys[0];
   else if (iBDBClass == eiBDBCID_Space  )   return &slapSpace[0];
   else                                      return &slapNULL[0];
}

static bool PreventCreationWhenNotDevMenu( int iBDBClass )	// SAC 4/7/16 - prevent certain object types from being create-able in the tree unless DeveloperMenu INI flag is set
{   return false;
}

static int ClassToPopulateChildMode( int iBDBClass )		// SAC 7/27/14 - 0-Class/ChildIndex | 1-ChildIndex
{	return 0;
}

bool DBIDAssignmentCompatible( long lAssignmentDBID, int iBEMClass, int iObjIdx, BEM_ObjType eBEMObjType )	// SAC 12/9/13
{	return true;
}

int CTreeBDB::GetBitmapID( int iBDBClass, int iObjOccur )
{
   if      (iBDBClass == eiBDBCID_Proj    )   return 14;
   else if (iBDBClass == eiBDBCID_Run     )   return 0;
   else if (iBDBClass == eiBDBCID_Site    )   return 16;
   else if (iBDBClass == eiBDBCID_Bldg    )   return 18;
   else if (iBDBClass == eiBDBCID_Bshade  )   return 32;
   else if (iBDBClass == eiBDBCID_Block   )   return 22;
   else if (iBDBClass == eiBDBCID_Floor   )   return 20;
   else if (iBDBClass == eiBDBCID_Space   )   return  2;
   else if (iBDBClass == eiBDBCID_ActArea )   return 24;
   else if (iBDBClass == eiBDBCID_LtSys   )   return 34;
   else if (iBDBClass == eiBDBCID_LtFix   )   return 0;
   else if (iBDBClass == eiBDBCID_ExtWall )   return  4;
   else if (iBDBClass == eiBDBCID_ExtRoof )   return 52;
   else if (iBDBClass == eiBDBCID_IntWall )   return  6;
   else if (iBDBClass == eiBDBCID_IntCeil )   return 54;
   else if (iBDBClass == eiBDBCID_UndWall )   return  8;
   else if (iBDBClass == eiBDBCID_FlrWall )
   {    long lFlrType;
        if (iObjOccur < 0 || 
            !BEMPX_SetDataInteger( elDBID_FWall_Type, lFlrType, 2, -1, iObjOccur ))
                                              return 56;
        else switch( lFlrType)
             {   case 0 /* Exterior */ :      return 60;
                 case 1 /* Interior */ :      return 62;
                 default               :      return 56;
             }
   }
   else if (iBDBClass == eiBDBCID_Win     )   return 10;
   else if (iBDBClass == eiBDBCID_Skylt   )   return 58;
   else if (iBDBClass == eiBDBCID_Door    )   return 12;
   else if (iBDBClass == eiBDBCID_Cons    )   return 0;
   else if (iBDBClass == eiBDBCID_Layers  )   return 0;
   else if (iBDBClass == eiBDBCID_Mat     )   return 0;
   else if (iBDBClass == eiBDBCID_HVACSys )   return 36;
   else if (iBDBClass == eiBDBCID_Size    )   return 0;
   else if (iBDBClass == eiBDBCID_HtPump  )   return 38;
   else if (iBDBClass == eiBDBCID_AirCond )   return 28;
   else if (iBDBClass == eiBDBCID_Furn    )   return 30;
   else if (iBDBClass == eiBDBCID_Econ    )   return 40;
   else if (iBDBClass == eiBDBCID_Plant   )   return 42;
   else if (iBDBClass == eiBDBCID_Fan     )   return 26;
   else if (iBDBClass == eiBDBCID_ClTower )   return 44;
   else if (iBDBClass == eiBDBCID_Chiller )   return 46;
   else if (iBDBClass == eiBDBCID_Boiler  )   return 48;
   else if (iBDBClass == eiBDBCID_Pump    )   return 50;
   else if (iBDBClass == eiBDBCID_Curve   )   return 0;
   else if (iBDBClass == eiBDBCID_Sched   )   return 0;
   else if (iBDBClass == eiBDBCID_WkSch   )   return 0;
   else if (iBDBClass == eiBDBCID_DaySch  )   return 0;
   else if (iBDBClass == eiBDBCID_ResSch  )   return 0;
   else if (iBDBClass == eiBDBCID_DResSch )   return 0;
   else if (iBDBClass == 1001             )   return 0;   // Ruleset Library
   else if (iBDBClass == 1002             )   return 64;  // Generic Folder
   else  return 0;
}

bool CTreeBDB::EnableViewFootprint( int /*iBDBClass*/, int /*iObjOccur =-1*/ )  // SAC 11/26/13
{	return false;
}

static int* siapNULL[]    = { NULL };
static int** ClassToConvertList( int iBDBClass )
{	return &siapNULL[0];
}
#endif   // UI_ASHRAE901E
//   -------------------------  END of:  ASHRAE 90.1E UI Mode  -------------------------


//   --------------------------------------------------------------------------
//   -------------------------  CA NonRes-2013 UI Mode  -----------------------
//   --------------------------------------------------------------------------
#ifdef UI_CANRES


//		;                LName              Template            MD  MR  AC   Parent1    P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14 P15  MC  MS  bP  CF  SR  IN     HI 
//		;               --------------------------------------------------------------------------------------------------------------------------------------------------------
//		0,  "Project", "Project",             "Project <i>",   1,  0,  0, "",        "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   1000
//		
//		0,  "SchDay",   "ScheduleDay",     "Sch Day <i>",    100000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "SchWeek",  "ScheduleWeek",    "Sch Week <i>",    10000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "Schedule", "Schedule",        "Sched <i>",       10000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		
//		0,  "ConsAssm",   "ConstructAssembly",   "Cons. Assembly <i>",    0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,  10000
//		0,  "Mat",       "Material",      "Material <i>",    0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,  10500
//		
//		0,  "FenCons",    "FenestrationConstruction",   "Fen Cons <i>",        0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,  10000
//		
//		0,  "SpcFuncDefaults",  "SpaceUseDefaults",  "Spc Use Dflts <i>",  1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		
//		0,  "Lum",     "Luminaire",    "Luminaire <i>",    1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		
//		0,  "CrvLin",    "CurveLinear",     "Crv-Linear <i>",    1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "CrvQuad",   "CurveQuadratic",  "Crv-Quad <i>",      1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "CrvCubic",  "CurveCubic",      "Crv-Cubic <i>",     1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "CrvDblQuad",   "CurveDoubleQuadratic",  "Crv-DblQuad <i>",   1000,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		
//		0,  "Building", "Building",           "Buidling <i>",     1,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   1500
//		0,  "Story",    "BuildingStory",   "Bldg Story <i>",   100,  0,  0, "Building", "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   2000
//		0,  "Space",    "Space",           "Space <pi>-<c>",   1000,  0,  0, "Story",   "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "IntLtgSys",  "InteriorLightingSystem",  "Int Ltg Sys <pi>-<c>",   1000,  0,  0, "Space",   "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "Ceiling",  "Ceiling",       "Ceiling <p2i>-<pc>-<c>",   10000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   4000
//		0,  "CeilingBelowAttic",  "CeilingBelowAttic",  "Ceiling Blw Attic <p2i>-<pc>-<c>",   1000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   4500
//		0,  "ExtFlr",     "ExteriorFloor",  "Ext Flr <p2i>-<pc>-<c>",   1000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   5000
//		0,  "ExtWall",     "ExteriorWall",  "Ext Wall <p2i>-<pc>-<c>",   10000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   5500
//		0,  "FlrAboveCrawlSpc",     "FloorAboveCrawlSpace", "Flr Abv Crawl Spc <p2i>-<pc>-<c>",   1000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   6000
//		0,  "IntFlr",     "InteriorFloor",    "Int Flr <p2i>-<pc>-<c>",   10000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   6500
//		0,  "IntWall",      "InteriorWall",     "Int Wall <p2i>-<pc>-<c>",   10000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   7000
//		0,  "Roof",              "Roof",              "Roof <p2i>-<pc>-<c>",    1000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   7500
//		0,  "UndgrFlr",     "UndergroundFloor",  "Undgr Flr <p2i>-<pc>-<c>",   1000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   8000
//		0,  "UndgrWall",    "UndergroundWall",   "Undgr Wall <p2i>-<pc>-<c>",   5000,  0,  0, "Space",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   8500
//		0,  "Window",      "Window",   "Window <p3i>-<p2c>-<pc>-<c>",  50000,  0,  0, "ExtWall",    "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   9000
//		0,  "Skylight",    "Skylight", "Skylt <p3i>-<p2c>-<pc>-<c>",    5000,  0,  0, "Roof",   "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   9500
//		0,  "Door",        "Door",     "Door <p3i>-<p2c>-<pc>-<c>",     5000,  0,  0, "ExtWall", "IntWall",  "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   9900
//		
//		0,  "PolyLp",   "PolyLoop",      "poly <i>",      0,  0,  0, "Space", "Ceiling", "CeilingBelowAttic", "ExtFlr", "ExtWall", "FlrAboveCrawlSpc", "IntFlr", "IntWall", "Roof", "UndgrFlr", "UndgrWall", "Window", "Skylight", "Door",  "",  -1,  1,  0,  0,  0,  1,   9000
//		0,  "CartesianPt",    "CartesianPoint",   "pt <pi>-<c>",    0,  0,  0, "PolyLp",   "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  1,  1,   9500
//		
//		0,  "ThrmlZn",    "ThermalZone",     "Thermal Zone <i>",   1000,  0,  0, "Building", "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "AirSys",       "AirSystem",       "Air System <i>",     1000,  0,  0, "Building", "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "AirSeg",    "AirSegment",    "Air Segment <pi>-<c>",   10000,  0,  0, "AirSys",    "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "CoilClg",  "CoilCooling",     "Cooling Coil <p2i>-<pc>-<c>",  10000,  0,  0, "AirSeg", "TrmlUnit", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "CoilHtg",  "CoilHeating",     "Heating Coil <p2i>-<pc>-<c>",  10000,  0,  0, "AirSeg", "TrmlUnit", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "Fan",    "Fan",       "Fan <p2i>-<pc>-<c>-<i>",   10000,  0,  0, "AirSeg", "TrmlUnit", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "TrmlUnit",    "TerminalUnit",   "Terminal Unit <i>",   10000,  0,  0, "AirSys",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		0,  "OACtrl",   "OAControl",     "OA Control <i>",   10000,  0,  0, "AirSys",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  0,  0,  0,  0,   3000
//		
//		
//		
//		   eiBDBCID_Project            = BEMPX_GetDBComponentID( "Project" );
//		   eiBDBCID_SchDay             = BEMPX_GetDBComponentID( "SchDay" );
//		   eiBDBCID_SchWeek            = BEMPX_GetDBComponentID( "SchWeek" );
//		   eiBDBCID_Schedule           = BEMPX_GetDBComponentID( "Schedule" );
//		   eiBDBCID_ConsAssm           = BEMPX_GetDBComponentID( "ConsAssm" );
//		   eiBDBCID_Mat                = BEMPX_GetDBComponentID( "Mat" );
//		   eiBDBCID_FenCons            = BEMPX_GetDBComponentID( "FenCons" );
//		   eiBDBCID_SpcFuncDefaults     = BEMPX_GetDBComponentID( "SpcFuncDefaults" );
//		   eiBDBCID_Lum                = BEMPX_GetDBComponentID( "Lum" );
//		   eiBDBCID_CrvLin             = BEMPX_GetDBComponentID( "CrvLin" );
//		   eiBDBCID_CrvQuad            = BEMPX_GetDBComponentID( "CrvQuad" );
//		   eiBDBCID_CrvCubic           = BEMPX_GetDBComponentID( "CrvCubic" );
//		   eiBDBCID_CrvDblQuad         = BEMPX_GetDBComponentID( "CrvDblQuad" );
//		   
//		   
//		   eiBDBCID_ThrmlZn            = BEMPX_GetDBComponentID( "ThrmlZn" );
//		   eiBDBCID_AirSys             = BEMPX_GetDBComponentID( "AirSys" );
//		   eiBDBCID_AirSeg             = BEMPX_GetDBComponentID( "AirSeg" );
//		   eiBDBCID_CoilClg            = BEMPX_GetDBComponentID( "CoilClg" );
//		   eiBDBCID_CoilHtg            = BEMPX_GetDBComponentID( "CoilHtg" );
//		   eiBDBCID_Fan                = BEMPX_GetDBComponentID( "Fan" );
//		   eiBDBCID_TrmlUnit           = BEMPX_GetDBComponentID( "TrmlUnit" );
//		   eiBDBCID_OACtrl             = BEMPX_GetDBComponentID( "OACtrl" );
//		
//		   elDBID_Proj_Name            = BEMPX_GetDatabaseID( "Name",            eiBDBCID_Project );
//		   elDBID_Proj_RunDate         = BEMPX_GetDatabaseID( "RunDate",         eiBDBCID_Project );
//		   elDBID_Proj_SoftwareVersion = BEMPX_GetDatabaseID( "SoftwareVersion", eiBDBCID_Project );
//		
//			elDBID_ThrmlZn_ClgSys              = BEMPX_GetDatabaseID( "ClgSys",             eiBDBCID_ThrmlZn  ); 
//			elDBID_ThrmlZn_SuppClgSys          = BEMPX_GetDatabaseID( "SuppClgSys",         eiBDBCID_ThrmlZn  ); 
//			elDBID_ThrmlZn_HtgSys              = BEMPX_GetDatabaseID( "HtgSys",             eiBDBCID_ThrmlZn  ); 
//			elDBID_ThrmlZn_SuppHtgSys          = BEMPX_GetDatabaseID( "SuppHtgSys",         eiBDBCID_ThrmlZn  ); 
//			elDBID_ThrmlZn_VentSys             = BEMPX_GetDatabaseID( "VentSys",            eiBDBCID_ThrmlZn  ); 
//			elDBID_ThrmlZn_ExhSys              = BEMPX_GetDatabaseID( "ExhSys",             eiBDBCID_ThrmlZn  ); 
//			elDBID_AirSeg_MakeupAirSys         = BEMPX_GetDatabaseID( "MakeupAirSys",       eiBDBCID_AirSeg   ); 
//			elDBID_AirSeg_MakeupThrmlZn        = BEMPX_GetDatabaseID( "MakeupThrmlZn",      eiBDBCID_AirSeg   ); 
//			elDBID_TrmlUnit_ZnServedRef        = BEMPX_GetDatabaseID( "ZnServedRef",        eiBDBCID_TrmlUnit ); 
//			elDBID_TrmlUnit_PriFlowSegRef      = BEMPX_GetDatabaseID( "PriFlowSegRef",      eiBDBCID_TrmlUnit ); 
//			elDBID_TrmlUnit_HotDuctFlowSegRef  = BEMPX_GetDatabaseID( "HotDuctFlowSegRef",  eiBDBCID_TrmlUnit ); 
//			elDBID_TrmlUnit_InducedAirZnRef    = BEMPX_GetDatabaseID( "InducedAirZnRef",    eiBDBCID_TrmlUnit ); 
//			elDBID_OACtrl_AirSegSupRef         = BEMPX_GetDatabaseID( "AirSegSupRef",       eiBDBCID_OACtrl   ); 
//			elDBID_OACtrl_AirSegRetRef         = BEMPX_GetDatabaseID( "AirSegRetRef",       eiBDBCID_OACtrl   ); 


// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }

static int siZero = 0;
//#ifdef UI_PROGYEAR2019
//static int  siNumArchComps = 32;
//static int  siNumArchFolders = 12;
//static int  siaMode0[]  = { 3, siNumArchComps-siNumArchFolders, siNumArchComps };
//static int* siapMode0[] = { &eiBDBCID_Building, &eiBDBCID_PVArray, &eiBDBCID_Battery, &eiBDBCID_Story, &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
//									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
//									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
//									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
//									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
//									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade };
//static int* siapFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
//										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade, NULL };
//#else
//#endif



// SAC 1/24/19 - added ResDWHRSys (for 2019 program only)
// SAC 2/23/20 - removed ResLpTankHtr from both 2019 & 2022 UIs
#ifdef UI_PROGYEAR2019	// SAC 7/28/18 - shifted PV & Battery objects from Envelope to Mechanical tabs
static int  siNumArchComps = 28;  
static int  siNumArchFolders = 10;  
static int  siaMode0[]  = { 1, siNumArchComps-siNumArchFolders, siNumArchComps };
static int* siapMode0[] = { &eiBDBCID_Building, &eiBDBCID_Story, 
                            &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum
                             };
static int* siapFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, 
                              NULL };

static int  siNumHVACComps = 34;       // removed &eiBDBCID_BlrHtPump... - SAC 05/14/21
static int  siNumHVACFolders = 8;
static int  siaMode1[]  = { 5, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapMode1[] = { &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_Building, &eiBDBCID_PVArray, &eiBDBCID_Battery, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler,
                            &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /* &eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade };
static int* siapFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade, NULL };
#elif UI_PROGYEAR2022 || UI_PROGYEAR2025  	// SAC 6/19/19   // SAC 10/23/22
static int  siNumArchComps = 54;      // was: 28;  before CBECC_Res integration - SAC 04/27/21   // SAC 07/26/22 (CUAC)
static int  siNumArchFolders = 14;    // was: 10;  before CBECC_Res integration - SAC 04/27/21
static int  siaMode0[]  = { 2, siNumArchComps-siNumArchFolders, siNumArchComps };
static int* siapMode0[] = { &eiBDBCID_ResProj, /*&eiBDBCID_CUAC,*/ &eiBDBCID_Building, &eiBDBCID_Story, 
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   &eiBDBCID_ResZnGrp, 
                            &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21   // reordered from top to bottom (consistent w/ CBECC-Res) - SAC 10/21/21 (MFam)
   &eiBDBCID_ResAttic      ,   &eiBDBCID_ResZn       ,   &eiBDBCID_ResOtherZn  ,   /*&eiBDBCID_ResGarage   ,*/   &eiBDBCID_ResCrawlSpc ,   &eiBDBCID_DwellUnit,
   &eiBDBCID_ResCathedralCeiling ,   &eiBDBCID_ResCeilingBelowAttic,    &eiBDBCID_ResIntCeiling,   &eiBDBCID_ResExtWall,   &eiBDBCID_ResOpening,
   &eiBDBCID_ResIntWall    ,   &eiBDBCID_ResUndgrWall,   &eiBDBCID_ResIntFlr   ,   &eiBDBCID_ResExtFlr   ,   &eiBDBCID_ResSlabFlr  ,   &eiBDBCID_ResFlrOverCrawlSpc,
   &eiBDBCID_ResUndgrFlr   ,   &eiBDBCID_ResWin      ,   &eiBDBCID_ResSkylt    ,   &eiBDBCID_ResDr       ,
									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   , &eiBDBCID_DwellUnitType, &eiBDBCID_ResConsAssm, &eiBDBCID_ResMat, &eiBDBCID_ResWinType
                             };
static int* siapFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, 
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   &eiBDBCID_DwellUnitType, &eiBDBCID_ResConsAssm, &eiBDBCID_ResMat, &eiBDBCID_ResWinType,
                              NULL };

static int  siNumHVACComps = 45;
static int  siNumHVACFolders = 18;
static int  siaMode1[]  = { 7, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapMode1[] = { &eiBDBCID_ResProj, /*&eiBDBCID_CUAC,*/ &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_ResHVACSys, &eiBDBCID_Building, &eiBDBCID_PVArray, &eiBDBCID_Battery, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler,
                            &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /* &eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl, &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/
                            &eiBDBCID_ResHtgSys, &eiBDBCID_ResClgSys, &eiBDBCID_ResHtPumpSys, &eiBDBCID_ResCentralHtgClgSys, &eiBDBCID_ResDistSys, &eiBDBCID_ResDuctSeg, &eiBDBCID_ResFanSys, &eiBDBCID_ResIAQFan, &eiBDBCID_ResCentralVentSys, // &eiBDBCID_ResClVentFan,    // SAC 08/18/21
                            &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade };
static int* siapFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, 
                              &eiBDBCID_ResHtgSys, &eiBDBCID_ResClgSys, &eiBDBCID_ResHtPumpSys, &eiBDBCID_ResCentralHtgClgSys, &eiBDBCID_ResDistSys, &eiBDBCID_ResDuctSeg, &eiBDBCID_ResFanSys, &eiBDBCID_ResIAQFan, &eiBDBCID_ResCentralVentSys, // &eiBDBCID_ResClVentFan,    // SAC 08/18/21
                              &eiBDBCID_ResWtrHtr, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade, NULL };
#else
static int  siNumHVACComps = 28;
static int  siNumHVACFolders = 4;
static int  siaMode1[]  = { 3, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapMode1[] = { &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_Building, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler,
                            &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /* &eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad };
static int* siapFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, NULL };
#endif

static int*  siaModes[]  = { siaMode0,  siaMode1 };
static int** siapModes[] = { siapMode0, siapMode1 };
static int** siapFolders[] = { siapFolder0, siapFolder1 };
static HTREEITEM shaModes[] = { TVI_LAST, TVI_LAST };

// Same statics for LIBRARY TREE
#ifdef UI_PROGYEAR2019	// SAC 1/24/19 - shifted PV & Battery objects from Envelope to Mechanical tabs
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
static int  siaLibMode0[]  = { 1, siNumArchComps-siNumArchFolders, siNumArchComps };
static int* siapLibMode0[] = { &eiBDBCID_Building, &eiBDBCID_Story, 
                            &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum
                             };
static int* siapLibFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, 
                              NULL };

static int  siaLibMode1[]  = { 2, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapLibMode1[] = { &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_Building, &eiBDBCID_PVArray, &eiBDBCID_Battery, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler, 
									 &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /*&eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade };
static int* siapLibFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade, NULL };
#elif UI_PROGYEAR2022 || UI_PROGYEAR2025  	// SAC 6/19/19   // SAC 10/23/22
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
static int  siaLibMode0[]  = { 2, siNumArchComps-siNumArchFolders, siNumArchComps };
static int* siapLibMode0[] = { &eiBDBCID_ResProj, /*&eiBDBCID_CUAC,*/ &eiBDBCID_Building, &eiBDBCID_Story, 
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   &eiBDBCID_ResZnGrp, 
                            &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21   // reordered from top to bottom (consistent w/ CBECC-Res) - SAC 10/21/21 (MFam)
   &eiBDBCID_ResAttic      ,   &eiBDBCID_ResZn       ,   &eiBDBCID_ResOtherZn  ,   /*&eiBDBCID_ResGarage   ,*/   &eiBDBCID_ResCrawlSpc ,   &eiBDBCID_DwellUnit,
   &eiBDBCID_ResCathedralCeiling ,   &eiBDBCID_ResCeilingBelowAttic,    &eiBDBCID_ResIntCeiling,   &eiBDBCID_ResExtWall,   &eiBDBCID_ResOpening,
   &eiBDBCID_ResIntWall    ,   &eiBDBCID_ResUndgrWall,   &eiBDBCID_ResIntFlr   ,   &eiBDBCID_ResExtFlr   ,   &eiBDBCID_ResSlabFlr  ,   &eiBDBCID_ResFlrOverCrawlSpc,
   &eiBDBCID_ResUndgrFlr   ,   &eiBDBCID_ResWin      ,   &eiBDBCID_ResSkylt    ,   &eiBDBCID_ResDr       ,
									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   , &eiBDBCID_DwellUnitType, &eiBDBCID_ResConsAssm, &eiBDBCID_ResMat, &eiBDBCID_ResWinType
                             };
static int* siapLibFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, 
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   &eiBDBCID_DwellUnitType, &eiBDBCID_ResConsAssm, &eiBDBCID_ResMat, &eiBDBCID_ResWinType,
                              NULL };

static int  siaLibMode1[]  = { 7, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapLibMode1[] = { &eiBDBCID_ResProj, /*&eiBDBCID_CUAC,*/ &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_ResHVACSys, &eiBDBCID_Building, &eiBDBCID_PVArray, &eiBDBCID_Battery, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler, 
									 &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /*&eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl, &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/
                            &eiBDBCID_ResHtgSys, &eiBDBCID_ResClgSys, &eiBDBCID_ResHtPumpSys, &eiBDBCID_ResCentralHtgClgSys, &eiBDBCID_ResDistSys, &eiBDBCID_ResDuctSeg, &eiBDBCID_ResFanSys, &eiBDBCID_ResIAQFan, &eiBDBCID_ResCentralVentSys, // &eiBDBCID_ResClVentFan,    // SAC 08/18/21
                            &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade };
static int* siapLibFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, 
                                 &eiBDBCID_ResHtgSys, &eiBDBCID_ResClgSys, &eiBDBCID_ResHtPumpSys, &eiBDBCID_ResCentralHtgClgSys, &eiBDBCID_ResDistSys, &eiBDBCID_ResDuctSeg, &eiBDBCID_ResFanSys, &eiBDBCID_ResIAQFan, &eiBDBCID_ResCentralVentSys, // &eiBDBCID_ResClVentFan,    // SAC 08/18/21
                                 &eiBDBCID_ResWtrHtr, &eiBDBCID_ResDWHRSys, &eiBDBCID_DHWSolarSys, &eiBDBCID_PVArrayGeom, &eiBDBCID_PVArrayShade, NULL };
#else
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
static int  siaLibMode0[]  = { 1, siNumArchComps-siNumArchFolders, siNumArchComps };
static int* siapLibMode0[] = { &eiBDBCID_Building, &eiBDBCID_Story, 
   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
                            &eiBDBCID_Space, &eiBDBCID_IntLtgSys, /*&eiBDBCID_DayltgCtrl,*/ &eiBDBCID_Ceiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_ExtFlr, &eiBDBCID_ExtWall, &eiBDBCID_FlrAboveCrawlSpc, &eiBDBCID_IntFlr, &eiBDBCID_IntWall,
									 &eiBDBCID_Roof, &eiBDBCID_UndgrFlr, &eiBDBCID_UndgrWall, &eiBDBCID_Window, &eiBDBCID_Skylight, &eiBDBCID_Door,
									 &eiBDBCID_ExtShdgObj, /*&eiBDBCID_PolyLp, &eiBDBCID_CartesianPoint,*/
									 &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
									 &eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum
                             };
static int* siapLibFolder0[] = { &eiBDBCID_Schedule, &eiBDBCID_SchWeek, &eiBDBCID_SchDay, &eiBDBCID_ThrmlEngyStorModeSchDay,
										&eiBDBCID_ConsAssm, &eiBDBCID_Mat, &eiBDBCID_FenCons, &eiBDBCID_DrCons, &eiBDBCID_SpcFuncDefaults, &eiBDBCID_Lum, 
                              NULL };

static int  siaLibMode1[]  = { 2, siNumHVACComps-siNumHVACFolders, siNumHVACComps };
static int* siapLibMode1[] = { &eiBDBCID_FluidSys, &eiBDBCID_ResDHWSys, &eiBDBCID_Building, /*&eiBDBCID_RfrgEqp,*/ &eiBDBCID_Chiller, &eiBDBCID_Boiler, 
									 &eiBDBCID_HtRej, &eiBDBCID_ThrmlEngyStor, &eiBDBCID_HX,
									 &eiBDBCID_WtrHtr, /*&eiBDBCID_BlrHtPump,*/ &eiBDBCID_ResWtrHtr, /*&eiBDBCID_ResLpTankHtr,*/ &eiBDBCID_FluidSeg, &eiBDBCID_Pump, /*&eiBDBCID_StorTank, &eiBDBCID_ProcLd,*/
									 &eiBDBCID_AirSys, &eiBDBCID_VRFSys, &eiBDBCID_ZnSys, &eiBDBCID_ThrmlZn, &eiBDBCID_AirSeg, &eiBDBCID_EvapClr, &eiBDBCID_TrmlUnit, &eiBDBCID_CoilClg, &eiBDBCID_CoilHtg,
									 &eiBDBCID_Fan, /*&eiBDBCID_PrehtCoil,*/ &eiBDBCID_HtRcvry, &eiBDBCID_OACtrl,
									 &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad };
static int* siapLibFolder1[] = { &eiBDBCID_CrvLin, &eiBDBCID_CrvQuad, &eiBDBCID_CrvCubic, &eiBDBCID_CrvDblQuad, NULL };
#endif

static int*  siaLibModes[]  = { siaLibMode0,  siaLibMode1 };
static int** siapLibModes[] = { siapLibMode0, siapLibMode1 };
static int** siapLibFolders[] = { siapLibFolder0, siapLibFolder1 };
static HTREEITEM shaLibModes[] = { TVI_LAST, TVI_LAST };

// Arrays of long pointers for adding children to various component types
static long* slapNULL[]    = { NULL };
static long* slapThermalZone[] 	= { 	&elDBID_ThrmlZn_ClgSys, &elDBID_ThrmlZn_SuppClgSys, &elDBID_ThrmlZn_HtgSys,
													&elDBID_ThrmlZn_SuppHtgSys, &elDBID_ThrmlZn_VentSys, &elDBID_ThrmlZn_ExhSys, NULL };
static long* slapAirSegment[]  	= { 	&elDBID_AirSeg_MakeupAirSys, &elDBID_AirSeg_MakeupThrmlZn, NULL };
static long* slapCoilCooling[] 	= {   &elDBID_CoilClg_FluidSegInRef, &elDBID_CoilClg_FluidSegOutRef, NULL };
static long* slapCoilHeating[] 	= {   &elDBID_CoilHtg_FluidSegInRef, &elDBID_CoilHtg_FluidSegOutRef, NULL };
static long* slapTerminalUnit[]	= {	&elDBID_TrmlUnit_ZnServedRef, &elDBID_TrmlUnit_PriFlowSegRef, &elDBID_TrmlUnit_HotDuctFlowSegRef,
													&elDBID_TrmlUnit_InducedAirZnRef, NULL };
static long* slapOAControl[]		= {	&elDBID_OACtrl_AirSegSupRef, &elDBID_OACtrl_AirSegRetRef, NULL };
static long* slapFluidSeg[]		= {	&elDBID_FluidSeg_PriSegRef, NULL };
static long* slapChiller[]			= {	&elDBID_Chiller_CndsrInRef, &elDBID_Chiller_CndsrOutRef, &elDBID_Chiller_EvapInRef, &elDBID_Chiller_EvapOutRef, NULL };
static long* slapBoiler[]			= {	&elDBID_Boiler_FluidFlowInRef, &elDBID_Boiler_FluidFlowOutRef, NULL };
//static long* slapBlrHtPump[]		= {	&elDBID_BlrHtPump_FluidSegInRef, &elDBID_BlrHtPump_FluidSegOutRef, NULL };	// SAC 10/23/20
static long* slapResDHWSys[]		= {	&elDBID_ResDHWSys_DHWSolarSysRef, &elDBID_ResDHWSys_DHWHeater1, &elDBID_ResDHWSys_DHWHeater2, &elDBID_ResDHWSys_DHWHeater3,   // SAC 1/31/20 (Com tic #3157)
										         &elDBID_ResDHWSys_DHWHeater4, &elDBID_ResDHWSys_DHWHeater5, &elDBID_ResDHWSys_DHWHeater6, NULL };     // SAC 10/12/21 (MFam)

static long** ClassToDBIDAssignmentList( int iBDBClass )
{
   if (iBDBClass == eiBDBCID_ResDHWSys			)   return &slapResDHWSys[0];       // SAC 10/12/21 (MFam)
// SAC 2/2/20 - debate about desire to list assigned components as children - for now we won't (consistent w/ past versions) (tic #3157)
//   if      (iBDBClass == eiBDBCID_ThrmlZn )   return &slapThermalZone[0]; 
//   else if (iBDBClass == eiBDBCID_AirSeg  )   return &slapAirSegment[0];  
//   else if (iBDBClass == eiBDBCID_CoilClg )   return &slapCoilCooling[0];  
//   else if (iBDBClass == eiBDBCID_CoilHtg )   return &slapCoilHeating[0];  
//   else if (iBDBClass == eiBDBCID_TrmlUnit)   return &slapTerminalUnit[0];
//   else if (iBDBClass == eiBDBCID_OACtrl  )   return &slapOAControl[0];   
//   else if (iBDBClass == eiBDBCID_FluidSeg)   return &slapFluidSeg[0];
//   else if (iBDBClass == eiBDBCID_Chiller )   return &slapChiller[0];
//   else if (iBDBClass == eiBDBCID_Boiler  )   return &slapBoiler[0];
//   else if (iBDBClass == eiBDBCID_BlrHtPump)  return &slapBlrHtPump[0];
//   else if (iBDBClass == eiBDBCID_ResDHWSys)  return &slapResDHWSys[0];		// SAC 1/31/20 (Com tic #3157)
   return &slapNULL[0];
}

static bool PreventCreationWhenNotDevMenu( int iBDBClass )	// SAC 4/7/16 - prevent certain object types from being create-able in the tree unless DeveloperMenu INI flag is set
{	
//   if      (iBDBClass == eiBDBCID_VRFSys )   return true;   - removed to always provide access to VRFSys creation - SAC 03/15/22
   return false;
}

static int ClassToPopulateChildMode( int iBDBClass )		// SAC 7/27/14 - 0-Class/ChildIndex | 1-ChildIndex
{		  if (iBDBClass == eiBDBCID_FluidSys    )		return 1;
	else if (iBDBClass == eiBDBCID_ResDHWSys   )    return 1;
//	else if (iBDBClass == eiBDBCID_Building    )    return 1;
	else if (iBDBClass == eiBDBCID_Chiller     )    return 1;
	else if (iBDBClass == eiBDBCID_Boiler      )    return 1;
	else if (iBDBClass == eiBDBCID_HtRej       )    return 1;
	else if (iBDBClass == eiBDBCID_WtrHtr      )    return 1;
//	else if (iBDBClass == eiBDBCID_BlrHtPump   )    return 1;
	else if (iBDBClass == eiBDBCID_ResWtrHtr   )    return 1;
   else if (iBDBClass == eiBDBCID_ResLpTankHtr)    return 1;	 // SAC 1/12/20 (Com tic #3156)
	else if (iBDBClass == eiBDBCID_FluidSeg    )    return 1;
	else if (iBDBClass == eiBDBCID_Pump        )    return 1;
	else if (iBDBClass == eiBDBCID_AirSys      )    return 1;
	else if (iBDBClass == eiBDBCID_VRFSys      )    return 1;
	else if (iBDBClass == eiBDBCID_ZnSys       )    return 1;
	else if (iBDBClass == eiBDBCID_ThrmlZn     )    return 1;
	else if (iBDBClass == eiBDBCID_AirSeg      )    return 1;
	else if (iBDBClass == eiBDBCID_EvapClr     )    return 1;
	else if (iBDBClass == eiBDBCID_TrmlUnit    )    return 1;
	else if (iBDBClass == eiBDBCID_CoilClg     )    return 1;
	else if (iBDBClass == eiBDBCID_CoilHtg     )    return 1;
	else if (iBDBClass == eiBDBCID_Fan         )    return 1;
	else if (iBDBClass == eiBDBCID_OACtrl      )    return 1;
	return 0;
}

bool DBIDAssignmentCompatible( long lAssignmentDBID, int iBEMClass, int iObjIdx, BEM_ObjType eBEMObjType )	// SAC 12/9/13
{	bool bRetVal = true;
	// SAC 1/31/20 - ensure ResDHWSys assigned children not listed for ResDHWSys where CentralSysType = 'HPWH' (2)  |  further mod to still include DHWSolarSys children (Com tic #3157)
	if (iBEMClass == eiBDBCID_ResDHWSys && elDBID_ResDHWSys_CentralSysType > 0 && lAssignmentDBID != elDBID_ResDHWSys_DHWSolarSysRef)
	{	long lCentralSysType = 0;
		if (BEMPX_SetDataInteger( elDBID_ResDHWSys_CentralSysType, lCentralSysType, 0, -1, iObjIdx, (int) eBEMObjType ) && lCentralSysType == 2)
			bRetVal = false;
	}
	return bRetVal;
}

int CTreeBDB::GetBitmapID( int iBDBClass, int iObjOccur )
{
   if      (iBDBClass == eiBDBCID_Project )              return  14;
   else if (iBDBClass == eiBDBCID_ResProj )              return 132;    // SAC 10/20/21 (MFam)
   else if (iBDBClass == eiBDBCID_CUAC )                 return 132;    // SAC 07/26/22 (CUAC)
   else if (iBDBClass == eiBDBCID_SchDay)                return  82;
   else if (iBDBClass == eiBDBCID_ThrmlEngyStorModeSchDay) return  82;
   else if (iBDBClass == eiBDBCID_SchWeek)               return  80;
   else if (iBDBClass == eiBDBCID_Schedule)              return  78;
   else if (iBDBClass == eiBDBCID_ConsAssm)              return  68;
   else if (iBDBClass == eiBDBCID_Mat)                   return  70;
   else if (iBDBClass == eiBDBCID_FenCons)               return  98;
   else if (iBDBClass == eiBDBCID_DrCons)                return  96;
   else if (iBDBClass == eiBDBCID_SpcFuncDefaults)       return  94;
   else if (iBDBClass == eiBDBCID_Lum)                   return 100;
   else if (iBDBClass == eiBDBCID_CrvLin)                return   0;
   else if (iBDBClass == eiBDBCID_CrvQuad)               return   0;
   else if (iBDBClass == eiBDBCID_CrvCubic)              return   0;
   else if (iBDBClass == eiBDBCID_CrvDblQuad)            return   0;
   else if (iBDBClass == eiBDBCID_Building)              return  18;
   else if (iBDBClass == eiBDBCID_Story)                 return  20;
   else if (iBDBClass == eiBDBCID_Space   )              return   2;
   else if (iBDBClass == eiBDBCID_IntLtgSys)             return  34;
   else if (iBDBClass == eiBDBCID_DayltgCtrl)            return   0;
   else if (iBDBClass == eiBDBCID_Ceiling)               return  54;
   else if (iBDBClass == eiBDBCID_CeilingBelowAttic)     return  54;
   else if (iBDBClass == eiBDBCID_ExtFlr)                return  60;
   else if (iBDBClass == eiBDBCID_ExtWall)               return   4;
   else if (iBDBClass == eiBDBCID_FlrAboveCrawlSpc)      return  60;
   else if (iBDBClass == eiBDBCID_IntFlr)                return  62;
   else if (iBDBClass == eiBDBCID_IntWall)               return   6;
   else if (iBDBClass == eiBDBCID_Roof)                  return  52;
   else if (iBDBClass == eiBDBCID_UndgrFlr)              return  56;
   else if (iBDBClass == eiBDBCID_UndgrWall)             return   8;
   else if (iBDBClass == eiBDBCID_Window  )              return  10;
   else if (iBDBClass == eiBDBCID_Skylight)              return  58;
   else if (iBDBClass == eiBDBCID_Door    )              return  12;
   else if (iBDBClass == eiBDBCID_PolyLp  )              return  76;
   else if (iBDBClass == eiBDBCID_CartesianPt)           return   0;
   else if (iBDBClass == eiBDBCID_ExtShdgObj)            return  32;
   else if (iBDBClass == eiBDBCID_ThrmlZn)               return  22;
   else if (iBDBClass == eiBDBCID_AirSys)                return  36;
   else if (iBDBClass == eiBDBCID_VRFSys)                return  36;		// SAC 8/14/15
   else if (iBDBClass == eiBDBCID_ZnSys)                 return  92;
   else if (iBDBClass == eiBDBCID_AirSeg)
	{	QString sAirSegType;
		if ( BEMPX_GetString( BEMPX_GetDatabaseID( "Type", eiBDBCID_AirSeg ), sAirSegType, FALSE, 0, -1, iObjOccur ) &&
				(sAirSegType.indexOf("Sup") >= 0 || sAirSegType.indexOf("Dual") >= 0 || sAirSegType.indexOf("Makeup") >= 0) )
			return  84;
		else
			return  86;
	}
   else if (iBDBClass == eiBDBCID_EvapClr)               return 108;
   else if (iBDBClass == eiBDBCID_CoilClg)               return  28;
   else if (iBDBClass == eiBDBCID_CoilHtg)               return  30;
   else if (iBDBClass == eiBDBCID_Fan)                   return  26;
   else if (iBDBClass == eiBDBCID_TrmlUnit)              return  88;
   else if (iBDBClass == eiBDBCID_HtRcvry)               return 114;
   else if (iBDBClass == eiBDBCID_OACtrl)                return  40;
   else if (iBDBClass == eiBDBCID_FluidSys)              return  42;
   else if (iBDBClass == eiBDBCID_FluidSeg)              return  90;
   else if (iBDBClass == eiBDBCID_Chiller)               return  46;
   else if (iBDBClass == eiBDBCID_Boiler)                return  48;
   else if (iBDBClass == eiBDBCID_HtRej)                 return  44;
   else if (iBDBClass == eiBDBCID_WtrHtr)                return  74;
//   else if (iBDBClass == eiBDBCID_BlrHtPump)             return  74;	 // SAC 10/23/20
   else if (iBDBClass == eiBDBCID_ResDHWSys)             return  42;  // SAC 9/25/13
   else if (iBDBClass == eiBDBCID_ResDWHRSys)   			return 112;  // SAC 1/24/19 - same as Com HX for now...
   else if (iBDBClass == eiBDBCID_ResWtrHtr)             return  74;
   else if (iBDBClass == eiBDBCID_ResLpTankHtr)          return  74;	 // SAC 1/12/20 (Com tic #3156)
   else if (iBDBClass == eiBDBCID_DHWSolarSys)           return 126;	 // SAC 1/31/20 (Com tic #3157)
   else if (iBDBClass == eiBDBCID_Pump)                  return  50;
   else if (iBDBClass == eiBDBCID_ThrmlEngyStor)         return 116;  // SAC 2/21/17
   else if (iBDBClass == eiBDBCID_HX)                    return 112;  // SAC 10/17/15
   else if (iBDBClass == eiBDBCID_PVArray)               return 118;  // SAC 7/17/18
   else if (iBDBClass == eiBDBCID_PVArrayGeom)           return 124;
   else if (iBDBClass == eiBDBCID_PVArrayShade)          return 122;
   else if (iBDBClass == eiBDBCID_Battery)               return 120;

   // integration of CBECC-Res into CBECC-Com - SAC 04/27/21
   else if (iBDBClass == eiBDBCID_ResZnGrp             )   return 134;  // SAC 12/14/21
   else if (iBDBClass == eiBDBCID_ResConsAssm          )   return  68;
   else if (iBDBClass == eiBDBCID_ResMat               )   return  70; 
   else if (iBDBClass == eiBDBCID_ResWinType           )   return  98;  // SAC 8/27/13
   else if (iBDBClass == eiBDBCID_ResZn                )   return 136;  // SAC 12/14/21
   else if (iBDBClass == eiBDBCID_DwellUnitType        )   return 110;
   else if (iBDBClass == eiBDBCID_DwellUnit            )   return 140;  // SAC 12/14/21
   else if (iBDBClass == eiBDBCID_ResOtherZn           )   return 138;	// SAC 9/3/19 - MFamProto  // SAC 12/14/21
   else if (iBDBClass == eiBDBCID_ResAttic             )   return  66;
//   else if (iBDBClass == eiBDBCID_ResGarage            )   return  66;
   else if (iBDBClass == eiBDBCID_ResCrawlSpc          )   return  66;
   else if (iBDBClass == eiBDBCID_ResExtWall           )   return   4;
   else if (iBDBClass == eiBDBCID_ResIntWall           )   return   6;
   else if (iBDBClass == eiBDBCID_ResUndgrWall         )   return   8;
   else if (iBDBClass == eiBDBCID_ResCathedralCeiling  )   return  52;
   else if (iBDBClass == eiBDBCID_ResCeilingBelowAttic )   return  54;
   else if (iBDBClass == eiBDBCID_ResIntCeiling        )   return  54;  // same as CeilingBelowAttic ??
   else if (iBDBClass == eiBDBCID_ResSlabFlr           )   return  56;
   else if (iBDBClass == eiBDBCID_ResExtFlr            )   return  60;
   else if (iBDBClass == eiBDBCID_ResFlrOverCrawlSpc   )   return  60;
   else if (iBDBClass == eiBDBCID_ResIntFlr            )   return  62;
   else if (iBDBClass == eiBDBCID_ResUndgrFlr          )   return  56;
   else if (iBDBClass == eiBDBCID_ResOpening           )   return 128;	// SAC 7/30/20 - MFamProto
   else if (iBDBClass == eiBDBCID_ResWin               )   return  10;
   else if (iBDBClass == eiBDBCID_ResSkylt             )   return  58;
   else if (iBDBClass == eiBDBCID_ResDr                )   return  12;
	else if (iBDBClass == eiBDBCID_ResHVACSys 			 )   return  36;        // SAC 08/18/21
	else if (iBDBClass == eiBDBCID_ResHtgSys 	   		 )   return  30;   // furnace
	else if (iBDBClass == eiBDBCID_ResClgSys 	   		 )   return  28;   // air cond
	else if (iBDBClass == eiBDBCID_ResHtPumpSys    		 )   return  38;   // heat pump
	else if (iBDBClass == eiBDBCID_ResCentralHtgClgSys	 )   return  36;   // SAC 12/31/21 (MFam)
	else if (iBDBClass == eiBDBCID_ResDistSys 	   	 )   return  42;   // plant
	else if (iBDBClass == eiBDBCID_ResFanSys 	   		 )   return  26;   // fan
	else if (iBDBClass == eiBDBCID_ResIAQFan 	  			 )   return  26;   // fan
	else if (iBDBClass == eiBDBCID_ResCentralVentSys	 )   return  26;   // fan  - SAC 12/31/21 (MFam)
	else if (iBDBClass == eiBDBCID_ResClVentFan 	  		 )   return  26;   // fan
   else if (iBDBClass == 1001)                             return   0;  // Ruleset Library
   else if (iBDBClass == 1002)                             return  64;  // Generic Folder
   else  return 0;
}

bool CTreeBDB::EnableViewFootprint( int iBDBClass, int /*iObjOccur =-1*/ )  // SAC 11/26/13
{	return (eiBDBCID_PolyLp > 0 && (iBDBClass == eiBDBCID_Story || iBDBClass == eiBDBCID_Space));		// SAC 8/12/14 - added 'eiBDBCID_PolyLp > 0' check to prevent enabling view footprint for simplified geom projects (GC #627)
}

// Arrays of int (class ID) pointers for CONVERTING one object type to another
static int* siapNULL[]    = { NULL };
static int* siapConvertExtWall[]		= { 	&eiBDBCID_UndgrWall,	&eiBDBCID_IntWall,	NULL };
static int* siapConvertUndgrWall[]	= {   &eiBDBCID_ExtWall,	&eiBDBCID_IntWall,	NULL };
static int* siapConvertIntWall[]		= {   &eiBDBCID_ExtWall,	&eiBDBCID_UndgrWall,	NULL };

static int** ClassToConvertList( int iBDBClass )
{  if      (iBDBClass == eiBDBCID_ExtWall		)	return &siapConvertExtWall[0]; 
   else if (iBDBClass == eiBDBCID_UndgrWall	)	return &siapConvertUndgrWall[0];  
   else if (iBDBClass == eiBDBCID_IntWall		)	return &siapConvertIntWall[0];  
   return &siapNULL[0];
}
#endif   // UI_CANRES
//   -------------------------  END of:  CA NonRes-2013 UI Mode  -----------------------


//   -----------------------------------------------------------------------------------
//   -------------------------------  CA Res-2013 UI Mode  -----------------------------
//   -----------------------------------------------------------------------------------
#ifdef UI_CARES
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
// SAC 1/14/13 - REMOVED CrawlSpace class ID for the time being
// SAC 1/16/13 - REMOVED Garage class ID for the time being  -- 1/28/13 - RESTORED Garage class
// SAC 12/23/18 - added DWHX (for 2019 program only)  // SAC 1/5/19 - renamed DWHRSys
// SAC 9/3/19 - added OtherZone (MFamProto)    - SAC 2/14/20 - removed OtherZone for 2019 EXE   - SAC 7/30/20 - added Opening to 2022
// SAC 2/23/20 - removed DHWLoopTankHeater from both 2019 & 2022 UIs 
static int siZero = 0;
#ifdef UI_PROGYEAR2019
static int  siNumArchComps = 27;
static int  siaMode0[]  = { 5, siNumArchComps-7, siNumArchComps };
static int* siapMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, &eiBDBCID_DwellUnit, /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
									 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapFolder0[] = { &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaMode1[]  = { 3, 3, 15 };
static int* siapMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
										&eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, NULL };
#elif UI_PROGYEAR2022
static int  siNumArchComps = 25;
static int  siaMode0[]  = { 5, siNumArchComps-6, siNumArchComps };         // removed OtherZone, DwellUnitType & DwellUnit from 2022 Res UI - SAC 01/20/22 (tic #1323)   // removed 'Opening' from 2022 Res UI - SAC 05/26/22
static int* siapMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, /*&eiBDBCID_OtherZone,*/ &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, /*&eiBDBCID_DwellUnit,*/ /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, /*&eiBDBCID_Opening,*/ &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
									 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapFolder0[] = { /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaMode1[]  = { 3, 3, 15 };
static int* siapMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
										&eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, NULL };
#elif UI_PROGYEAR2025      // SAC 11/12/22
static int  siNumArchComps = 25;
static int  siaMode0[]  = { 5, siNumArchComps-6, siNumArchComps };         // removed OtherZone, DwellUnitType & DwellUnit from 2022 Res UI - SAC 01/20/22 (tic #1323)   // removed 'Opening' from 2022 Res UI - SAC 05/26/22
static int* siapMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, /*&eiBDBCID_OtherZone,*/ &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, /*&eiBDBCID_DwellUnit,*/ /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, /*&eiBDBCID_Opening,*/ &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
									 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapFolder0[] = { /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaMode1[]  = { 3, 3, 15 };
static int* siapMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
										&eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_DWHRSys, NULL };
#else
static int  siNumArchComps = 26;
static int  siaMode0[]  = { 4, siNumArchComps-7, siNumArchComps };
static int* siapMode0[] = { &eiBDBCID_Attic, &eiBDBCID_Zone, &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, &eiBDBCID_DwellUnit, /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
									 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapFolder0[] = { &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaMode1[]  = { 3, 3, 13 };
static int* siapMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
										&eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, NULL };
#endif

static int*  siaModes[]  = { siaMode0,  siaMode1 };
static int** siapModes[] = { siapMode0, siapMode1 };
static int** siapFolders[] = { siapFolder0, siapFolder1 };
static HTREEITEM shaModes[] = { TVI_LAST, TVI_LAST };

// Same statics for LIBRARY TREE
// { # Root Classes, # Compatible Classes That MAY Be Root If Have No Parent or Are Not Assigned To Anything, # Total Classes }
// SAC 1/14/13 - REMOVED CrawlSpace class ID for the time being
// SAC 1/16/13 - REMOVED Garage class ID for the time being  -- 1/28/13 - RESTORED Garage class
// SAC 12/23/18 - added DWHX (for 2019 program only)  // SAC 1/5/19 - renamed DWHRSys
// SAC 9/3/19 - added OtherZone (MFamProto)   - SAC 2/14/20 - removed OtherZone for 2019 EXE    - SAC 7/30/20 - added Opening to 2022
#ifdef UI_PROGYEAR2019
static int  siaLibMode0[]  = { 5, siNumArchComps-7, siNumArchComps };
static int* siapLibMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, &eiBDBCID_DwellUnit, /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 	 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
										 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapLibFolder0[] = { &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaLibMode1[]  = { 3, 3, 13 };
static int* siapLibMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
											&eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapLibFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan,  &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ NULL };
#elif UI_PROGYEAR2022
static int  siaLibMode0[]  = { 5, siNumArchComps-6, siNumArchComps };      // removed OtherZone, DwellUnitType & DwellUnit from 2022 Res UI - SAC 01/20/22 (tic #1323)
static int* siapLibMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, /*&eiBDBCID_OtherZone,*/ &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, /*&eiBDBCID_DwellUnit,*/ /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 	 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, /*&eiBDBCID_Opening,*/ &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
										 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapLibFolder0[] = { /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaLibMode1[]  = { 3, 3, 13 };
static int* siapLibMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
											&eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapLibFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan,  &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ NULL };
#elif UI_PROGYEAR2025      // SAC 11/12/22
static int  siaLibMode0[]  = { 5, siNumArchComps-6, siNumArchComps };      // removed OtherZone, DwellUnitType & DwellUnit from 2022 Res UI - SAC 01/20/22 (tic #1323)
static int* siapLibMode0[] = { &eiBDBCID_RESNETBldg, &eiBDBCID_Attic, &eiBDBCID_Zone, /*&eiBDBCID_OtherZone,*/ &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, /*&eiBDBCID_DwellUnit,*/ /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 	 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, /*&eiBDBCID_Opening,*/ &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
										 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapLibFolder0[] = { /*&eiBDBCID_DwellUnitType,*/ &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaLibMode1[]  = { 3, 3, 13 };
static int* siapLibMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
											&eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapLibFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan,  &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWHeater, /*&eiBDBCID_DHWLoopTankHeater,*/ NULL };
#else
static int  siaLibMode0[]  = { 4, siNumArchComps-7, siNumArchComps };
static int* siapLibMode0[] = { &eiBDBCID_Attic, &eiBDBCID_Zone, &eiBDBCID_Garage, &eiBDBCID_CrawlSpace, &eiBDBCID_DwellUnit, /*&eiBDBCID_AtticRoof,*/ &eiBDBCID_CathedralCeiling, &eiBDBCID_CeilingBelowAttic,
									 	 &eiBDBCID_InteriorCeiling, &eiBDBCID_ExtWall, &eiBDBCID_IntWall, &eiBDBCID_UndWall, &eiBDBCID_InteriorFloor, &eiBDBCID_SlabFloor, &eiBDBCID_ExteriorFloor, &eiBDBCID_FloorOverCrawl, &eiBDBCID_UndFloor,
										 &eiBDBCID_Win, &eiBDBCID_Skylt, &eiBDBCID_Door, &eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade };
static int* siapLibFolder0[] = { &eiBDBCID_DwellUnitType, &eiBDBCID_Cons, /*&eiBDBCID_Mat,*/ &eiBDBCID_WindowType, &eiBDBCID_PVArrayGeom, &eiBDBCID_Shade, NULL };
static int  siaLibMode1[]  = { 3, 3, 15 };
static int* siapLibMode1[] = {	&eiBDBCID_HVACSys, &eiBDBCID_DHWSys, &eiBDBCID_IAQVentRpt, &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan, &eiBDBCID_IAQFan,
											&eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, &eiBDBCID_DWHRSys, &eiBDBCID_SCSysRpt, &eiBDBCID_DHWSysRpt };
static int* siapLibFolder1[] = { &eiBDBCID_HVACHeat, &eiBDBCID_HVACCool, &eiBDBCID_HVACHtPump, &eiBDBCID_HVACDist, &eiBDBCID_HVACFan,  &eiBDBCID_IAQFan, &eiBDBCID_ClVentFan, &eiBDBCID_DHWSolarSys, &eiBDBCID_DHWHeater, &eiBDBCID_DWHRSys, NULL };
#endif

static int*  siaLibModes[]  = { siaLibMode0,  siaLibMode1 };
static int** siapLibModes[] = { siapLibMode0, siapLibMode1 };
static int** siapLibFolders[] = { siapLibFolder0, siapLibFolder1 };
static HTREEITEM shaLibModes[] = { TVI_LAST, TVI_LAST };

// Arrays of long pointers for adding children to various component types
static long* slapNULL[]    = { NULL };
static long* slapAttic[]   = { NULL };  // &elDBID_Attic_Construction, NULL };
static long* slapZone[]    = {	&elDBID_Zone_HVACSystem, &elDBID_Zone_AltHVACSystem, &elDBID_Zone_exHVACSystem,
											&elDBID_Zone_DHWSys1, &elDBID_Zone_AltDHWSys1, &elDBID_Zone_exDHWSys1,
											// &elDBID_Zone_DHWSys2, &elDBID_Zone_AltDHWSys2, &elDBID_Zone_exDHWSys2,     // removed Zone:*DHWSys2 assignment stuff - SAC 05/30/22
                               NULL };
static long* slapExtWall[] = { NULL };  // &elDBID_ExtWall_Construction, NULL };
static long* slapIntWall[] = { NULL };  // &elDBID_IntWall_Construction, NULL };
static long* slapUndWall[] = { NULL };  // &elDBID_UndWall_Construction, NULL };
//static long* slapAttcRf[]  = { &elDBID_AtticRoof_Construction, NULL };
static long* slapCathCl[]  = { NULL };  // &elDBID_CathedralCeiling_Construction, NULL };
static long* slapCeilBlw[] = { NULL };  // &elDBID_CeilingBelowAttic_Construction, NULL };
static long* slapExtFlr[]  = { NULL };  // &elDBID_ExteriorFloor_Construction, NULL };
static long* slapIntFlr[]  = { NULL };  // &elDBID_InteriorFloor_Construction, NULL };
static long* slapIntClg[]  = { NULL };  // &elDBID_InteriorCeiling_Construction, NULL };
static long* slapCons[]    = { &elDBID_Cons_Materials1 , &elDBID_Cons_Materials2 , &elDBID_Cons_Materials3 , &elDBID_Cons_Materials4 ,
										 &elDBID_Cons_Materials5 , &elDBID_Cons_Materials6 , &elDBID_Cons_Materials7 , &elDBID_Cons_Materials8 ,
										 &elDBID_Cons_Materials9 , &elDBID_Cons_Materials10, NULL };
static long* slapHVACSys[] = { &elDBID_HVAC_HeatSystem1, &elDBID_HVAC_HeatSystem2, &elDBID_HVAC_HeatSystem3, &elDBID_HVAC_HeatSystem4,
										 &elDBID_HVAC_HeatSystem5, &elDBID_HVAC_HeatSystem6, &elDBID_HVAC_HeatSystem7, &elDBID_HVAC_HeatSystem8,
										 &elDBID_HVAC_HeatSystem9, &elDBID_HVAC_HeatSystem10,
										 &elDBID_HVAC_CoolSystem1, &elDBID_HVAC_CoolSystem2, &elDBID_HVAC_CoolSystem3, &elDBID_HVAC_CoolSystem4,
										 &elDBID_HVAC_CoolSystem5, &elDBID_HVAC_CoolSystem6, &elDBID_HVAC_CoolSystem7, &elDBID_HVAC_CoolSystem8,
										 &elDBID_HVAC_CoolSystem9, &elDBID_HVAC_CoolSystem10,
										 &elDBID_HVAC_HtPumpSystem1, &elDBID_HVAC_HtPumpSystem2, &elDBID_HVAC_HtPumpSystem3, &elDBID_HVAC_HtPumpSystem4,
										 &elDBID_HVAC_HtPumpSystem5, &elDBID_HVAC_HtPumpSystem6, &elDBID_HVAC_HtPumpSystem7, &elDBID_HVAC_HtPumpSystem8,
										 &elDBID_HVAC_HtPumpSystem9, &elDBID_HVAC_HtPumpSystem10,
										 &elDBID_HVAC_DistribSystem,
										 &elDBID_HVAC_Fan, NULL };
static long* slapHVACHeat[]= { &elDBID_HVACHeat_CHWHeater, NULL };
static long* slapDHWSys[] = { &elDBID_DHWSys_DHWSolarSysRef, &elDBID_DHWSys_DHWHeater1, &elDBID_DHWSys_DHWHeater2, &elDBID_DHWSys_DHWHeater3,
										    &elDBID_DHWSys_DHWHeater4, &elDBID_DHWSys_DHWHeater5, &elDBID_DHWSys_DHWHeater6, &elDBID_DHWSys_LoopHeater, NULL };

static long** ClassToDBIDAssignmentList( int iBDBClass )
{
   if      (iBDBClass == eiBDBCID_Attic  				)   return &slapAttic[0];
   else if (iBDBClass == eiBDBCID_ExtWall				)   return &slapExtWall[0];
   else if (iBDBClass == eiBDBCID_IntWall				)   return &slapIntWall[0];
   else if (iBDBClass == eiBDBCID_UndWall				)   return &slapUndWall[0];
//   else if (iBDBClass == eiBDBCID_AtticRoof			)   return &slapAttcRf[0];
   else if (iBDBClass == eiBDBCID_CathedralCeiling	)   return &slapCathCl[0];
   else if (iBDBClass == eiBDBCID_CeilingBelowAttic)   return &slapCeilBlw[0];
   else if (iBDBClass == eiBDBCID_ExteriorFloor		)   return &slapExtFlr[0];
   else if (iBDBClass == eiBDBCID_InteriorFloor		)   return &slapIntFlr[0];
   else if (iBDBClass == eiBDBCID_InteriorCeiling	)   return &slapIntClg[0];
   else if (iBDBClass == eiBDBCID_Cons   				)   return &slapCons[0];
   else if (iBDBClass == eiBDBCID_Zone					)   return &slapZone[0];
   else if (iBDBClass == eiBDBCID_HVACSys				)   return &slapHVACSys[0];
   else if (iBDBClass == eiBDBCID_HVACHeat			)   return &slapHVACHeat[0];
   else if (iBDBClass == eiBDBCID_DHWSys				)   return &slapDHWSys[0];
   else                                      			 return &slapNULL[0];
}

static bool PreventCreationWhenNotDevMenu( int iBDBClass )	// SAC 4/7/16 - prevent certain object types from being create-able in the tree unless DeveloperMenu INI flag is set
{	if (iBDBClass == eiBDBCID_PVArrayGeom || iBDBClass == eiBDBCID_Shade)
	{	long lEnergyCodeYr;
		BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYr );
	   return (lEnergyCodeYr != 0 && lEnergyCodeYr < 2022);		// SAC 1/19/20 - switched year to 2022 that allows PVArrayGeom or Shade w/out Dev menu (Res tic #1012)
	} 
	return false;
}

static int ClassToPopulateChildMode( int /*iBDBClass*/ )		// SAC 7/27/14 - 0-Class/ChildIndex | 1-ChildIndex
{	return 0;
}

bool DBIDAssignmentCompatible( long lAssignmentDBID, int iBEMClass, int iObjIdx, BEM_ObjType eBEMObjType )	// SAC 12/9/13
{	bool bRetVal = true;
	// SAC 12/9/13 - added several Zone properties to enhance tree display to confirm to E+A+A assignments
	if (iBEMClass == eiBDBCID_Zone)
	{	if (lAssignmentDBID == elDBID_Zone_HVACSystem || lAssignmentDBID == elDBID_Zone_AltHVACSystem || lAssignmentDBID == elDBID_Zone_exHVACSystem)
		{	long lHVACSysStatus, lHVACSysVerified;
			if (BEMPX_SetDataInteger( elDBID_Zone_HVACSysStatus,   lHVACSysStatus,   0, -1, iObjIdx, (int) eBEMObjType ))
			{	switch (lHVACSysStatus)
				{	case  3 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_HVACSystem);		break;	// NEW
					case  2 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_AltHVACSystem ||		   // ALTERED (w/ or w/out Verified)
													(lAssignmentDBID == elDBID_Zone_exHVACSystem &&
													 BEMPX_SetDataInteger( elDBID_Zone_HVACSysVerified, lHVACSysVerified, 0, -1, iObjIdx, (int) eBEMObjType ) && lHVACSysVerified > 0));	break;
					case  1 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_exHVACSystem);	break;	// EXISTING
					default :	bRetVal = false;		break;
			}	}
			else
				bRetVal = false;
		}
		else if (lAssignmentDBID == elDBID_Zone_DHWSys1 || lAssignmentDBID == elDBID_Zone_AltDHWSys1 || lAssignmentDBID == elDBID_Zone_exDHWSys1)
		{	long lDHWSys1Status, lDHWSys1Verified;
			if (BEMPX_SetDataInteger( elDBID_Zone_DHWSys1Status,   lDHWSys1Status,   0, -1, iObjIdx, (int) eBEMObjType ))
			{	switch (lDHWSys1Status)
				{	case  3 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_DHWSys1);		break;	// NEW
					case  2 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_AltDHWSys1 ||		   // ALTERED (w/ or w/out Verified)
													(lAssignmentDBID == elDBID_Zone_exDHWSys1 &&
													 BEMPX_SetDataInteger( elDBID_Zone_DHWSys1Verified, lDHWSys1Verified, 0, -1, iObjIdx, (int) eBEMObjType ) && lDHWSys1Verified > 0));	break;
					case  1 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_exDHWSys1);	break;	// EXISTING
					default :	bRetVal = false;		break;
			}	}
			else
				bRetVal = false;
		}
		else if (elProjAnalysisVersion < 190200 && (lAssignmentDBID == elDBID_Zone_DHWSys2 || lAssignmentDBID == elDBID_Zone_AltDHWSys2 || lAssignmentDBID == elDBID_Zone_exDHWSys2))    // removed Zone:*DHWSys2 assignment stuff - SAC 05/30/22
		{	long lDHWSys2Status, lDHWSys2Verified;
			if (BEMPX_SetDataInteger( elDBID_Zone_DHWSys2Status,   lDHWSys2Status,   0, -1, iObjIdx, (int) eBEMObjType ))
			{	switch (lDHWSys2Status)
				{	case  3 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_DHWSys2);		break;	// NEW
					case  2 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_AltDHWSys2 ||		   // ALTERED (w/ or w/out Verified)
													(lAssignmentDBID == elDBID_Zone_exDHWSys2 &&
													 BEMPX_SetDataInteger( elDBID_Zone_DHWSys2Verified, lDHWSys2Verified, 0, -1, iObjIdx, (int) eBEMObjType ) && lDHWSys2Verified > 0));	break;
					case  1 :	bRetVal = 	(lAssignmentDBID == elDBID_Zone_exDHWSys2);	break;	// EXISTING
					default :	bRetVal = false;		break;
			}	}
			else
				bRetVal = false;
		}
	}
	// SAC 12/6/16 - fix bug reported by Ken where user can create HVACHeat or HVACCool children for HtPump HVACSys objects (and vice-versa)
	else if (iBEMClass == eiBDBCID_HVACSys)
	{	long lHVACSysType = 0;
		BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Type", eiBDBCID_HVACSys ), lHVACSysType, 0, -1, iObjIdx, (int) eBEMObjType );
		if (lAssignmentDBID >= elDBID_HVAC_HeatSystem1 && lAssignmentDBID <= elDBID_HVAC_HeatSystem10 && lHVACSysType == 2)
			// cannot assign HVACHeat to HVACSys of Type = HtPump
			bRetVal = false;
		else if (lAssignmentDBID >= elDBID_HVAC_CoolSystem1 && lAssignmentDBID <= elDBID_HVAC_CoolSystem10 && lHVACSysType == 2)
			// cannot assign HVACCool to HVACSys of Type = HtPump
			bRetVal = false;
		else if (lAssignmentDBID >= elDBID_HVAC_HtPumpSystem1 && lAssignmentDBID <= elDBID_HVAC_HtPumpSystem10 && (lHVACSysType == 1 || lHVACSysType == 3))
			// cannot assign HVACHtPump to HVACSys of Type = Other... or Var OAV...
			bRetVal = false;
	}
	// SAC 1/21/20 - ensure DHWSys assigned children not listed for DHWSys where CentralDHWType = 'HPWH' (2)  |  further mod to still include DHWSolarSys children - SAC 1/22/20
	else if (iBEMClass == eiBDBCID_DHWSys && elDBID_DHWSys_CentralDHWType > 0 && lAssignmentDBID != elDBID_DHWSys_DHWSolarSysRef)
	{	long lCentralDHWType = 0;
		if (BEMPX_SetDataInteger( elDBID_DHWSys_CentralDHWType, lCentralDHWType, 0, -1, iObjIdx, (int) eBEMObjType ) && lCentralDHWType == 2)
			bRetVal = false;
	}

	return bRetVal;
}

int CTreeBDB::GetBitmapID( int iBDBClass, int /*iObjOccur*/ )
{
   if      (iBDBClass == eiBDBCID_Proj    )   return 14;
//   else if (iBDBClass == eiBDBCID_Run     )   return  0;
//   else if (iBDBClass == eiBDBCID_Site    )   return 16;
//   else if (iBDBClass == eiBDBCID_Bldg    )   return 18;
//   else if (iBDBClass == eiBDBCID_Zone    )   return  2;

//   else if (iBDBClass == eiBDBCID_SURFACE )
//   {    long lSurfType;
//        if (iObjOccur < 0 || 
//            !BEMPX_SetDataInteger( elDBID_SURFACE_sfType, lSurfType, 0, -1, iObjOccur ))
//                                              return  4;
//        else switch( lSurfType )
//             {   case 1 /* Floor    */ :  return 60;
//                 case 2 /* Wall     */ :  return  4;
//                 case 3 /* Ceiling  */ :  return 54;
//                 case 4 /* IntMass1 */ :  return  6;
//                 case 5 /* IntMass2 */ :  return  6;
//                 default               :  return  4;
//             }
//	}

   else if (iBDBClass == eiBDBCID_RESNETBldg			)   return 130;	// SAC 9/28/20
//   else if (iBDBClass == eiBDBCID_Building 		)   return  18;
   else if (iBDBClass == eiBDBCID_Garage   			)   return  66;
   else if (iBDBClass == eiBDBCID_Attic    			)   return  66;
   else if (iBDBClass == eiBDBCID_CrawlSpace 		)   return  66;
   else if (iBDBClass == eiBDBCID_Zone     			)   return   2;
   else if (iBDBClass == eiBDBCID_OtherZone     	)   return  24;	// SAC 9/3/19 - MFamProto
   else if (iBDBClass == eiBDBCID_ExtWall  			)   return   4;
   else if (iBDBClass == eiBDBCID_IntWall 			)   return   6;
   else if (iBDBClass == eiBDBCID_UndWall				)   return   8;
   else if (iBDBClass == eiBDBCID_UndFloor			)   return  56;
//   else if (iBDBClass == eiBDBCID_AtticRoof			)   return  52;
   else if (iBDBClass == eiBDBCID_CathedralCeiling	)   return  52;
   else if (iBDBClass == eiBDBCID_CeilingBelowAttic)   return  54;
   else if (iBDBClass == eiBDBCID_SlabFloor        )   return  56;
   else if (iBDBClass == eiBDBCID_ExteriorFloor    )   return  60;
   else if (iBDBClass == eiBDBCID_FloorOverCrawl   )   return  60;
   else if (iBDBClass == eiBDBCID_InteriorFloor    )   return  62;
   else if (iBDBClass == eiBDBCID_InteriorCeiling  )   return  54;  // same as CeilingBelowAttic ??
   else if (iBDBClass == eiBDBCID_Opening       	)   return 128;	// SAC 7/30/20 - MFamProto
   else if (iBDBClass == eiBDBCID_Win      			)   return  10;
   else if (iBDBClass == eiBDBCID_Skylt            )   return  58;
   else if (iBDBClass == eiBDBCID_Door     			)   return  12;
   else if (iBDBClass == eiBDBCID_DwellUnitType		)   return 110;
   else if (iBDBClass == eiBDBCID_DwellUnit			)   return  24;
   else if (iBDBClass == eiBDBCID_Cons     			)   return  68;
   else if (iBDBClass == eiBDBCID_Mat      			)   return  70;
   else if (iBDBClass == eiBDBCID_WindowType			)   return  98;  // SAC 8/27/13
   else if (iBDBClass == eiBDBCID_PVArrayGeom		)   return 124;  // SAC 3/2/17   - SAC 7/17/18
   else if (iBDBClass == eiBDBCID_Shade   			)   return 122;  // SAC 2/22/17  - SAC 7/17/18
   else if (iBDBClass == eiBDBCID_PolyLp  			)   return  76;
   else if (iBDBClass == eiBDBCID_HVACSys  			)   return  36;
   else if (iBDBClass == eiBDBCID_DHWSys  			)   return  72;
   else if (iBDBClass == eiBDBCID_DHWSolarSys		)   return 126;	// SAC 1/12/20 (Res tic #1013)
   else if (iBDBClass == eiBDBCID_DWHRSys		   	)   return 112;  // SAC 12/23/18 - same as Com HX for now...
   else if (iBDBClass == eiBDBCID_HVACHeat 			)   return  30;   // furnace
   else if (iBDBClass == eiBDBCID_HVACCool 			)   return  28;   // air cond
   else if (iBDBClass == eiBDBCID_HVACHtPump			)   return  38;   // heat pump
   else if (iBDBClass == eiBDBCID_HVACDist 			)   return  42;   // plant
   else if (iBDBClass == eiBDBCID_HVACFan  			)   return  26;   // fan
   else if (iBDBClass == eiBDBCID_IAQFan           )   return  26;   // fan
   else if (iBDBClass == eiBDBCID_ClVentFan        )   return  26;   // fan
   else if (iBDBClass == eiBDBCID_DHWHeater        )   return  74;
   else if (iBDBClass == eiBDBCID_DHWLoopTankHeater)   return  74;		// SAC 11/14/19
   else if (iBDBClass == eiBDBCID_SCSysRpt         )   return 102;
   else if (iBDBClass == eiBDBCID_DHWSysRpt        )   return 104;
   else if (iBDBClass == eiBDBCID_IAQVentRpt       )   return 106;
   else if (iBDBClass == 1001               			)   return   0;   // Ruleset Library
   else if (iBDBClass == 1002               			)   return  64;  // Generic Folder
   else  return 0;
}

bool CTreeBDB::EnableViewFootprint( int /*iBDBClass*/, int /*iObjOccur =-1*/ )  // SAC 11/26/13
{	return false;
}

static int* siapNULL[]    = { NULL };
static int** ClassToConvertList( int /*iBDBClass*/ )
{	return &siapNULL[0];
}
#endif   // UI_CARES
//   -------------------------  END of:  CA Res-2013 UI Mode  -----------------------------


///////////////////////////////////////////////////////////////////////////////
// reference index functions

//		// a reference index consists of a 6 digit ID unique to each building component
//		// SCCIII where:
//		//    S   is a 0-based object type flag indicating where this object is
//		//        defined (user vs. rule library vs. user library) (see key below)
//		//    CC  is the 1-based builidng database component ID and
//		//    III is a 0-based index to the array of building database components of this type.
//		// SAC 11/11/15 - above coding replaced w/ the following to allow for up to 99,999 objects of a single type and as many as 999 object types
// a reference index consists of a 9 digit ID unique to each building component
// SCCIII where:
//    S     is a 0-based object type flag indicating where this object is
//          defined (user vs. rule library vs. user library) (see key below)
//    CCC   is the 1-based builidng database component ID and
//    IIIII is a 0-based index to the array of building components of this type.
//
// The following functions provide various types of reference index manipulation.
//
// Key to object type stuff:
//      enum BEM_ObjType
//      {
//         BEMO_User,       => 0
//         BEMO_RuleLib,    => 1
//         BEMO_UserLib,    => 2
//         BEMO_NumTypes
//      };

const DWORD sdwObjTypMult = 100000000;
const DWORD sdwObjClsMult = 100000;

DWORD GetReferenceIndex( DWORD lComp, DWORD lIdx, DWORD lSrc )
//{  return ((lSrc * 100000) + (lComp * 1000) + lIdx);  }
{  return ((lSrc * sdwObjTypMult) + (lComp * sdwObjClsMult) + lIdx);  }

DWORD GetReferenceFromObject( BEMObject* pObj )
{
   if ( (pObj != NULL) && (pObj->getClass() != NULL) )
   {
      int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
      if (iObjIdx >= 0)
         return (DWORD) GetReferenceIndex( pObj->getClass()->get1BEMClassIdx(), iObjIdx, (long) pObj->getObjectType() );
   }
   return 0;
}

BEM_ObjType TreeRefToSource( DWORD lRef )
//{  return (BEM_ObjType) (lRef / 100000);  }
{  return (BEM_ObjType) (lRef / sdwObjTypMult);  }

int TreeRefToComponent( DWORD lRef )
//{  return (int) ((lRef % 100000) / 1000);  }
{  return (int) ((lRef % sdwObjTypMult) / sdwObjClsMult);  }

int TreeRefToIndex( DWORD lRef )
//{  return (int) (lRef % 1000);  }
{  return (int) (lRef % sdwObjClsMult);  }


CString GenerateTempFileName()
{
   CString csTempPath;
   DWORD dwRes;

   dwRes = GetTempPath( MAX_PATH, csTempPath.GetBuffer( MAX_PATH ) );
   csTempPath.ReleaseBuffer();
   if ( !dwRes )
   {
      CFileException::ThrowOsError( GetLastError() );
   }

   CString csTempFilePath;
   dwRes = GetTempFileName( csTempPath, _T("CUI"), 0, csTempFilePath.GetBuffer( MAX_PATH ) );
   csTempFilePath.ReleaseBuffer();
   if ( !dwRes ) 
   {
      CFileException::ThrowOsError( GetLastError() );
   }
   return csTempFilePath;
}

static HGLOBAL CreateHGLOBALFromFile( LPCTSTR pszFileName )
{
   CFile fSource( pszFileName, CFile::modeRead | CFile::shareDenyWrite );
   DWORD dwLength = (DWORD) fSource.GetLength();
   HGLOBAL hGlobal = GlobalAlloc( GMEM_DDESHARE, dwLength );
   if ( !hGlobal ) 
   {
      CFileException::ThrowOsError( GetLastError() );
   }
   LPVOID pvGlobal = GlobalLock( hGlobal );
   if ( !pvGlobal ) 
   {
      CFileException::ThrowOsError( GetLastError() );
   }
   fSource.Read( pvGlobal, dwLength );
   GlobalUnlock( hGlobal );
   return hGlobal;
}

static void CreateFileFromHGLOBAL( HGLOBAL hGlobal, LPCTSTR pszFileName )
{
   CFile sDest( pszFileName, CFile::modeCreate | CFile::modeWrite );
   DWORD dwLength = GlobalSize( hGlobal );
   LPVOID pvGlobal = GlobalLock( hGlobal );
   if ( !pvGlobal ) 
   {
      CFileException::ThrowOsError( GetLastError() );
   }
   sDest.Write( pvGlobal, dwLength );
   GlobalUnlock( hGlobal );
}

/////////////////////////////////////////////////////////////////////////////
// CTreeBDB
CLIPFORMAT CTreeBDB::g_cfPrivate;
CLIPFORMAT CTreeBDB::g_cfDatasource;

// if current mode is "Architectural", then grab the BEMProc value for ArchTreeOption and
// reset the siaModes[] & siapModes[] variables based on the BEMProc value
void CTreeBDB::SetupTreeMode()
{
#ifdef UI_ASHRAE901E
   int iStatus = BEMPX_GetDataStatus( elDBID_Proj_ArchTreeOption );
   if ( (iStatus > BEMS_Undefined) && (iStatus < BEMS_NumTypes) )
   {
      int iDataType, iError, iSpecialVal;
		iDataType = BEMPX_GetDataType( elDBID_Proj_ArchTreeOption );
      long lNewVal = (iDataType == BEMP_Sym ? BEMPX_GetInteger( elDBID_Proj_ArchTreeOption, iSpecialVal, iError ) : -1);
      if ( iError >= 0 && iDataType == BEMP_Sym )
      {
         int iTotComps  = ((m_iTreeMode == TM_Architecture) ? siNumArchComps : siNumLtComps);
         int iCurComps  = iTotComps - lNewVal;
         int*  iaModeX  = ((m_iTreeMode == TM_Architecture) ? siaMode1 : siaMode2);
         int** iapModeX = ((m_iTreeMode == TM_Architecture) ? siapMode1 : siapMode2);

         iaModeX[1] = iCurComps;
         iaModeX[2] = iCurComps;

         if (lNewVal == 0)       // "Display Block & Floor Components"
         {
//            siaMode1[1]  = siNumArchComps;
//            siaMode1[2]  = siNumArchComps;
            iapModeX[           0 ] = &eiBDBCID_Block;
            iapModeX[ iTotComps-2 ] = &eiBDBCID_Floor;
            iapModeX[ iTotComps-1 ] = &eiBDBCID_Space;
         }
         else if (lNewVal == 1)  // "Display Floor but not Block Components"
         {
//            siaMode1[1]  = siNumArchComps-1;
//            siaMode1[2]  = siNumArchComps-1;
            iapModeX[           0 ] = &eiBDBCID_Floor;
            iapModeX[ iTotComps-2 ] = &eiBDBCID_Space;
            iapModeX[ iTotComps-1 ] = &siZero;
         }
         else if (lNewVal == 2)  // "Don't Display Block or Floor Components"
         {
//            siaMode1[1]  = siNumArchComps-2;
//            siaMode1[2]  = siNumArchComps-2;
            iapModeX[           0 ] = &eiBDBCID_Space;
            iapModeX[ iTotComps-2 ] = &siZero;
            iapModeX[ iTotComps-1 ] = &siZero;
         }
      }
   }
#endif   // UI_ASHRAE901E
}

void CTreeBDB::InitDragInfo()
{
   m_dragInfo.iBDBClass = 0;
   m_dragInfo.iParentBDBClass = 0;

   m_bDragCanCopy = FALSE;
}

CTreeBDB::CTreeBDB()
{
   m_iTreeMode = -1;
   m_htiRootItem = NULL;

   m_pimagelist = NULL;
   InitDragInfo();

   m_dwMinValidRef = GetReferenceIndex( 1, 0, 0 );
   m_dwMaxValidRef = GetReferenceIndex( 0, 0, BEMO_NumTypes );

   // flag used to determine if tree requires reset following edits to database
   m_bTreeCurrent = TRUE;

   // flag used to prevent active BDB items from getting reset due to tree deletion
   m_bDeletingBDBItems = FALSE;

   // this flag prevents a double-click to cause and expansion or contraction
   // following the edit of a tree item
   m_lIgnoreNextExpansion = 0;

   m_iOLEDragging = 0;
}

CTreeBDB::~CTreeBDB()
{
   ResetArrayData();
}


BEGIN_MESSAGE_MAP(CTreeBDB, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeBDB)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginRDrag)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRClick)
	ON_COMMAND(IDQM_TREEEDIT  ,   OnQuickEdit)
	ON_COMMAND(IDQM_TREERENAME,   OnQuickRename)
	ON_COMMAND(IDQM_TREEDELETE,   OnQuickDelete)
	ON_COMMAND(IDQM_TREEEXPCON,   OnQuickExpCon)
	ON_COMMAND(IDQM_TREECREATE1,  OnQuickCreate1)
	ON_COMMAND(IDQM_TREECREATE2,  OnQuickCreate2)
	ON_COMMAND(IDQM_TREECREATE3,  OnQuickCreate3)
	ON_COMMAND(IDQM_TREECREATE4,  OnQuickCreate4)
	ON_COMMAND(IDQM_TREECREATE5,  OnQuickCreate5)
	ON_COMMAND(IDQM_TREECREATE6,  OnQuickCreate6)
	ON_COMMAND(IDQM_TREECREATE7,  OnQuickCreate7)
	ON_COMMAND(IDQM_TREECREATE8,  OnQuickCreate8)
	ON_COMMAND(IDQM_TREECREATE9,  OnQuickCreate9)
	ON_COMMAND(IDQM_TREECREATE10, OnQuickCreate10)
	ON_COMMAND(IDQM_TREECREATE11, OnQuickCreate11)
	ON_COMMAND(IDQM_TREECREATE12, OnQuickCreate12)
	ON_COMMAND(IDQM_TREECREATE13, OnQuickCreate13)
	ON_COMMAND(IDQM_TREECREATE14, OnQuickCreate14)
	ON_COMMAND(IDQM_TREECREATE15, OnQuickCreate15)
	ON_COMMAND(IDQM_TREECREATE16, OnQuickCreate16)
	ON_COMMAND(IDQM_TREECREATE17, OnQuickCreate17)
	ON_COMMAND(IDQM_TREECREATE18, OnQuickCreate18)
	ON_COMMAND(IDQM_TREECREATE19, OnQuickCreate19)
	ON_COMMAND(IDQM_TREECREATE20, OnQuickCreate20)
	ON_COMMAND(IDQM_TREECOPY,     OnEditCopy)
	ON_COMMAND(IDQM_TREEPASTE,    OnEditPaste)
	ON_COMMAND(IDQM_TREEMOVEUP,   OnQuickMoveUp)
	ON_COMMAND(IDQM_TREEMOVEDOWN, OnQuickMoveDown)
	ON_COMMAND(IDQM_TREECONVERT1,  OnQuickConvert1)
	ON_COMMAND(IDQM_TREECONVERT2,  OnQuickConvert2)
	ON_COMMAND(IDQM_TREECONVERT3,  OnQuickConvert3)
	ON_COMMAND(IDQM_TREECONVERT4,  OnQuickConvert4)
	ON_COMMAND(IDQM_TREECONVERT5,  OnQuickConvert5)
	ON_COMMAND(IDQM_TREECONVERT6,  OnQuickConvert6)
	ON_COMMAND(IDQM_TREECONVERT7,  OnQuickConvert7)
	ON_COMMAND(IDQM_TREECONVERT8,  OnQuickConvert8)
	ON_COMMAND(IDQM_TREECONVERT9,  OnQuickConvert9)
	ON_COMMAND(IDQM_TREECONVERT10, OnQuickConvert10)
	ON_COMMAND(IDQM_TREE_VIEWFOOTPRINT, OnViewFootprint)
 	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTVNSelchanged)
	ON_WM_SYSKEYDOWN()
	ON_NOTIFY_REFLECT(NM_RETURN, OnNMReturn)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnTVNItemExpanded)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnNMDblClk)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnTVNItemExpanding)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP

   ON_MESSAGE( WM_EDITTREEITEM, OnEditTreeItem )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeBDB message handlers

BOOL CTreeBDB::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, BOOL bProjTree)
{
//   DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER| TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;
   DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER| TVS_HASLINES | TVS_HASBUTTONS;

   m_bProjectTree = bProjTree;
   if (m_bProjectTree)
   {
      m_iapModes    = &siaModes[0];
      m_iappModes   = &siapModes[0];
      m_iappFolders = &siapFolders[0];
      m_hapModes    = &shaModes[0];
   }
   else
   {
      m_iapModes    = &siaLibModes[0];
      m_iappModes   = &siapLibModes[0];
      m_iappFolders = &siapLibFolders[0];
      m_hapModes    = &shaLibModes[0];
   }

	CWnd* pWnd = this;
   return pWnd->CreateEx( WS_EX_CLIENTEDGE, "SysTreeView32", "", dwStyle, rect, pParentWnd, nID );
}

void CTreeBDB::OnDestroy()
{
   CImageList* pimagelist = GetImageList(TVSIL_NORMAL);
   if (pimagelist)
   {
      pimagelist->DeleteImageList();
      delete pimagelist;
   }
}


/////////////////////////////////////////////////////////////////////////////
// CTreeBDB - functions to manage lists of ItemData/DBID/Code information

void CTreeBDB::ResetArrayData()
{
   m_dwaItemData.RemoveAll();
   m_dwaItemDBIDs.RemoveAll();
   m_waItemCodes.RemoveAll();
}

void CTreeBDB::AddToArrayData( DWORD dwData, DWORD dwDBID, WORD wCode )
{
   m_dwaItemData.Add(  dwData );
   m_dwaItemDBIDs.Add( dwDBID );
   m_waItemCodes.Add(   wCode );
}

void CTreeBDB::DeleteArrayData( DWORD dwData )
{
   for (int i=0; i<m_dwaItemData.GetSize(); i++)
   {
      if (m_dwaItemData[i] == dwData)
      {
         m_dwaItemData.RemoveAt(  i );
         m_dwaItemDBIDs.RemoveAt( i );
         m_waItemCodes.RemoveAt(  i );
         return;
      }
   }
}

BOOL CTreeBDB::ArrayDataMatch( DWORD dwData, DWORD dwDBID, WORD wCode )
{
   for (int i=0; i<m_dwaItemData.GetSize(); i++)
   {
      if (m_dwaItemData[i] == dwData)
         return (m_dwaItemDBIDs[i] == dwDBID && m_waItemCodes[i] == wCode);
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTreeBDB message handlers

void CTreeBDB::AddProjectComponent( BOOL bAddItem )
{
   int iError;
   BEMObject* pProjObj = BEMPX_GetObjectByClass( 1, iError, 0 );
   DWORD dwItemData = 0;
   CString csText;
   if (pProjObj)
   {
      dwItemData = GetReferenceIndex( 1, 0, 0 );
      csText = "Project:  '";
      csText += pProjObj->getName().toLatin1().constData();
      csText += "'";
   }
   else
      csText = "Press Alt+F to Open an Existing Project";     // SAC 8/17/11 - remove wizard option
//      csText = "Double-Click to Create a New Project via the Wizard or Alt+F to Open an Existing Project";
// SAC 9/2/99 - replaced w/ above string per RSB's request
//      csText = "Double-Click to Create a New Project via the Wizard";

   if (bAddItem)
   {
      int iBmpID = GetBitmapID( 1 );
      m_htiRootItem = InsertItem( csText, iBmpID, iBmpID+1, TVI_ROOT, TVI_SORT );
      if ((m_htiRootItem == NULL) || (!SetItemData( m_htiRootItem, dwItemData )))
         m_htiRootItem = NULL;
#ifdef UI_CARES
		else if (m_iTreeMode == 1)  // mechanical tree
		{	long lIsMultiFam;
			if (BEMPX_SetDataInteger( elDBID_Proj_IsMultiFamily, lIsMultiFam ) && lIsMultiFam > 0)
			{	iBmpID = 64;  // Generic Folder
				HTREEITEM hMsgItem = InsertItem( "Multifamily HVAC equipment assignments made to individual DwellUnitType objects, not here", iBmpID, iBmpID+1, m_htiRootItem, m_hapModes[m_iTreeMode] );
				if (hMsgItem)
					SetItemData( hMsgItem, 0 );
		}	}
#endif   // UI_CARES
   }
   else if (m_htiRootItem)
      SetItemText( m_htiRootItem, csText );

   return;
}


BOOL CTreeBDB::ClassIsCompatibleWithMode( int iBDBClassIdx )
{
   for (int i=0; i < m_iapModes[m_iTreeMode][2]; i++)
   {  if (iBDBClassIdx == *m_iappModes[m_iTreeMode][i])
         return TRUE;
   }
   return FALSE;
}

BOOL CTreeBDB::IsFolderClass( int iBDBClassIdx )   // SAC 12/29/11
{
	int i=-1;
	while (m_iappFolders[m_iTreeMode][++i] != NULL)
   {  if (iBDBClassIdx == *m_iappFolders[m_iTreeMode][i])
         return TRUE;
   }
   return FALSE;
}


void CTreeBDB::AddReverseReferencingChildren( HTREEITEM hParent, BEMObject* pParentObj, int i1ChildClass, long lChildDBID, int iChildSource )
{
   int iNumObjs = BEMPX_GetNumObjects( i1ChildClass, (BEM_ObjType) iChildSource );
   for (int iObj=0; iObj<iNumObjs; iObj++)
   {
      int iError = 0;
      BEMObject* pObj = NULL;

      // Get object data and if it points to parent object, then add tree node
   //   pObj = BEMPX_GetObject( lChildDBID, iSpecialVal, iError, iObj, (BEM_ObjType) iChildSource );
   //   if ( (iError >= 0) && (pObj != NULL) && (pObj == pParentObj) )
      if (BEMPX_GetObject( lChildDBID, pObj, -1, iObj, (BEM_ObjType) iChildSource ) && pObj && pObj == pParentObj)
      {
         BEMObject* pChildObj = BEMPX_GetObjectByClass( i1ChildClass, iError, iObj, (BEM_ObjType) iChildSource );
         if (pChildObj && pChildObj->getClass() &&
             // SAC 7/6/00 - added following check for compatibility with current tree mode
             ClassIsCompatibleWithMode( i1ChildClass ))
            AddComponent( hParent, i1ChildClass, iObj, iChildSource, pChildObj, lChildDBID, TDC_ReverseRef );
      }
   }
}

BOOL CTreeBDB::DBIDInList( long lCheckDBID, long** plDBID )
{
   int i=0;
   while (plDBID[i] != NULL)
   {
      long lDBID = *plDBID[i++];
      if (lDBID == lCheckDBID)
         return TRUE;
   }
   return FALSE;
}

int IndexOfDBIDInList( long lCheckDBID, long** plDBID )
{  int i=0;
   while (plDBID[i] != NULL)
   {  if (*plDBID[i++] == lCheckDBID)
         return i-1;
   }
   return -1;
}

static BOOL ValueInArrayLong( CArray<long,long>* piArray, long iVal )   // SAC 8/20/13
{  ASSERT( piArray );
   if (piArray != NULL)
   {
      int iSize = piArray->GetSize();
      for (int i=0; i<iSize; i++)
         if (iVal == piArray->GetAt(i))
            return TRUE;
   }
   return FALSE;
}

static int IndexOfValueInArrayLong( CArray<long,long>* piArray, long iVal )   // SAC 8/20/13
{  ASSERT( piArray );
   if (piArray != NULL)
   {  int iSize = piArray->GetSize();
      for (int i=0; i<iSize; i++)
         if (iVal == piArray->GetAt(i))
            return i;
   }
   return -1;
}

// added iGParClass to enable custom (assigned) child inclusion below - SAC 12/12/22 (Res tic #1318)
void CTreeBDB::AddAssignedChildren( int iGParClass, HTREEITEM hParent, int iParClass, int iParObjIdx, int iParSrc, long** plDBID )
{
   int i=0;
	CArray<long,long> laChildObjIDs;   // SAC 8/20/13
   while (plDBID[i] != NULL)
   {
      long lDBID = *plDBID[i++];
      BEMObject* pChildObj = NULL;

      // Get object data and if it points to parent object, then add tree node
	//	int iError = 0;
	//   pChildObj = BEMPX_GetObject( lDBID, iSpecialVal, iError, iParObjIdx, (BEM_ObjType) iParSrc );
   //   if ( iError >= 0  &&  pChildObj  &&  pChildObj->getClass()  &&
		// SAC 12/2/16 - fixed bug in call to BEMPX_GetObject() where third (iDispDataType) argument was left off, causing iParObjIdx passed to always = 0
      if ( BEMPX_GetObject( lDBID, pChildObj, -1, iParObjIdx, (BEM_ObjType) iParSrc ) && pChildObj  &&  pChildObj->getClass()  &&
           // SAC 7/6/00 - added following check for compatibility with current tree mode
           ClassIsCompatibleWithMode( pChildObj->getClass()->get1BEMClassIdx() ) )
      {  bool bCustomCompat = true;
         int iChildClassID = pChildObj->getClass()->get1BEMClassIdx();
#ifdef UI_CARES
         if (iGParClass == eiBDBCID_DHWSys && (iChildClassID == eiBDBCID_HVACDist || iChildClassID == eiBDBCID_HVACFan))
            bCustomCompat = false;  // prevent child HVACDist & HVACFan when GrandPar is DHWSys - SAC 12/12/22 (Res tic #1318)
#endif  // UI_CARES
         if (bCustomCompat && DBIDAssignmentCompatible( lDBID, iParClass, iParObjIdx, (BEM_ObjType) iParSrc ))	// SAC 12/9/13
         {	int iChildOccur = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );
				long lChildObjID = (iChildClassID * sdwObjClsMult) + iChildOccur;   // SAC 8/20/13 - added to prevent same child object form appearing multiple times under single parent object
				if (!ValueInArrayLong( &laChildObjIDs, lChildObjID ))
         	{	laChildObjIDs.Add( lChildObjID );
					AddComponent( hParent, iChildClassID, iChildOccur, pChildObj->getObjectType(), pChildObj,
         	   	           lDBID, TDC_Reference );
			}	}
      }
   }
	laChildObjIDs.RemoveAll();
}

//static BOOL sbAppendDBIDsLoaded = FALSE;
static QString sqsAppendDBIDsRuleSetID;
static QString sqsAppendDBIDsRuleSetVer;
static CDWordArray sdwaAppendDBID;
static void LoadAppendDBIDs()
{
	QString sLoadedRuleSetID, sLoadedRuleSetVer;
	if (BEMPX_GetRulesetID( sLoadedRuleSetID, sLoadedRuleSetVer ))	// SAC 1/31/19 - code to refresh the list of AppendDBIDs list when ruleset has changed
	{	if (sqsAppendDBIDsRuleSetID.isEmpty() || sqsAppendDBIDsRuleSetVer.isEmpty() ||
			 sqsAppendDBIDsRuleSetID.compare(  sLoadedRuleSetID  ) ||
			 sqsAppendDBIDsRuleSetVer.compare( sLoadedRuleSetVer ))
		{  int i1Class = 1;
		   int iError;
		   BEMClass* pClass = BEMPX_GetClass( i1Class, iError );
		   sdwaAppendDBID.SetSize( BEMPX_GetNumClasses() );
//CString sLogMsg;
		   while ((iError >= 0) && pClass)
		   {
		      CString sParam = ReadProgString( "AppendToTreeEntries", pClass->getShortName().toLatin1().constData(), "");
		      if (sParam.GetLength() != 0)
		         sdwaAppendDBID[ i1Class-1 ] = (DWORD) BEMPX_GetDatabaseID( sParam, i1Class );
            else if (BEMPX_GetDatabaseID( "TreeDescrip", i1Class ) > 0)
		         sdwaAppendDBID[ i1Class-1 ] = (DWORD) BEMPX_GetDatabaseID( "TreeDescrip", i1Class );
		      else
		         sdwaAppendDBID[ i1Class-1 ] = 0;
//sLogMsg.Format( "   tree append class %d %s param '%s' (%ld)", i1Class, pClass->getShortName().toLatin1().constData(), sParam, sdwaAppendDBID[ i1Class-1 ] );   BEMPX_WriteLogFile( (const char*) sLogMsg );
		      pClass = BEMPX_GetClass( ++i1Class, iError );
		   }
//sLogMsg.Format( "   tree append done @ class %d", i1Class );   BEMPX_WriteLogFile( (const char*) sLogMsg );
			sqsAppendDBIDsRuleSetID  = sLoadedRuleSetID;
			sqsAppendDBIDsRuleSetVer = sLoadedRuleSetVer;
		   //sbAppendDBIDsLoaded = TRUE;
	}	}
}

static void SetItemString( BEMObject* pObj, CString& sEntry )
{
   if (pObj)
   {
// SAC - 3/20/98 - removed short class name prior to each tree entry
//      sEntry  = pObj->getClass()->m_lpszShortName;
//      sEntry += ":  ";
//      sEntry += pObj->getName();
////      sEntry += pszAppend[ (int) eChildType ];  // append source ID string
      if (pObj->getClass()->get1BEMClassIdx() == eiBDBCID_Proj)
         sEntry = pObj->getClass()->getDefaultName().toLatin1().constData();
      else
      {
         sEntry = pObj->getName().toLatin1().constData();

         if (sdwaAppendDBID.GetSize() >= pObj->getClass()->get1BEMClassIdx() &&
         	 sdwaAppendDBID[ pObj->getClass()->get1BEMClassIdx()-1 ] > 0)		// SAC 3/22/14 - make sure sdwaAppendDBID array is setup before referencing it // SAC 1/31/19
         {
            int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
            QString sTemp;
            BEMPX_GetString( (long) sdwaAppendDBID[ pObj->getClass()->get1BEMClassIdx()-1 ],
                               sTemp, TRUE, 0, -1, iObjIdx, (int) pObj->getObjectType() );
            if (sTemp.length() > 0)
            {
               sEntry += "  (";
               sEntry += sTemp.toLatin1().constData();
               sEntry += ")";
            }
//CString sLogMsg;
//if (sTemp.length() > 0)
//	sLogMsg.Format( "   tree entry '%s' (DBID %ld appended: %s)", sEntry, (long) sdwaAppendDBID[ pObj->getClass()->get1BEMClassIdx()-1 ], sTemp );
//else
//	sLogMsg.Format( "   tree entry '%s' (DBID %ld append not defined)", sEntry, (long) sdwaAppendDBID[ pObj->getClass()->get1BEMClassIdx()-1 ] );
//BEMPX_WriteLogFile( (const char*) sLogMsg );
         }
      }
   }
   else
      sEntry = "Error Loading Name";
}

HTREEITEM CTreeBDB::AddComponent( HTREEITEM hParent, int iBDBClass, int iObjOccur, int iSource, BEMObject* pObj,
                                  long lDBID, TDC_DropCodes eCode )
{
   DWORD dwItemData = GetReferenceIndex( iBDBClass, iObjOccur, iSource );

   if (lDBID > 0 && eCode != TDC_Child)
      AddToArrayData( dwItemData, (DWORD) lDBID, (WORD) eCode );

   DWORD dwParentData = GetItemData( hParent );    // to enable custom (assigned) child inclusion below - SAC 12/12/22 (Res tic #1318)
   int iParentClass = TreeRefToComponent( dwParentData );

   CString csText;
   SetItemString( pObj, csText );

   int iBmpID = GetBitmapID( iBDBClass, iObjOccur );
   HTREEITEM hNewItem = InsertItem( csText, iBmpID, iBmpID+1, hParent, m_hapModes[m_iTreeMode] );
   if (hNewItem && SetItemData( hNewItem, dwItemData ))
   {
      // PRIOR TO THE REGULAR CHILDREN: add other assigned or reverse-assigned children to this node

      // populate tree with REGULAR CHILDREN of this node
		int iPopChildMode = ClassToPopulateChildMode( iBDBClass );		// SAC 7/27/14 - 0-Class/ChildIndex | 1-ChildIndex
		if (iPopChildMode == 0)
      {	// SAC - 3/20/98 - added outer loop through each class type for this tree mode to ensure
      	//                 that the children are ordered by class THEN occurence, rather than just occurence
       	for (int iCls=0; iCls < m_iapModes[m_iTreeMode][2]; iCls++)
//       	   for (int i=0; i < pObj->m_children.GetCount(); i++)
//       	   {  POSITION pos = pObj->m_children.FindIndex( i );
//       	      BEMObject* pChildObj = (BEMObject*) pObj->m_children.GetAt( pos );
			{	int iNumChldrn = pObj->getChildCount();
				for (int i=0; i < iNumChldrn; i++)
				{	BEMObject* pChildObj = pObj->getChild(i);			ASSERT( pChildObj );
       	      if ( pChildObj && pChildObj->getClass() &&
       	           pChildObj->getClass()->get1BEMClassIdx() == *m_iappModes[m_iTreeMode][iCls] )
 //    	             (ClassIsCompatibleWithMode( pChildObj->getClass()->get1BEMClassIdx() )) )
       	      {
       	         int iObjOcc = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );
       	         AddComponent( hNewItem, pChildObj->getClass()->get1BEMClassIdx(), iObjOcc, (int) pChildObj->getObjectType(), pChildObj );
       	      }
			}  }
		}
		else if (iPopChildMode == 1)
		{	// populate tree w/ children based solely on order of children in list
//      	   for (int i=0; i < pObj->m_children.GetCount(); i++)
// 			{	POSITION pos = pObj->m_children.FindIndex( i );
// 				BEMObject* pChildObj = (BEMObject*) pObj->m_children.GetAt( pos );
			int iNumChldrn = pObj->getChildCount();
			for (int i=0; i < iNumChldrn; i++)
			{	BEMObject* pChildObj = pObj->getChild(i);			ASSERT( pChildObj );
 				if (pChildObj && pChildObj->getClass())
 				{	bool bChildClsInList = false;
 	      		for (int iCls=0; (!bChildClsInList && iCls < m_iapModes[m_iTreeMode][2]); iCls++)
 						bChildClsInList = (pChildObj->getClass()->get1BEMClassIdx() == *m_iappModes[m_iTreeMode][iCls]);
 					if (bChildClsInList)
 					{	int iObjOcc = BEMPX_GetObjectIndex( pChildObj->getClass(), pChildObj );
 						AddComponent( hNewItem, pChildObj->getClass()->get1BEMClassIdx(), iObjOcc, (int) pChildObj->getObjectType(), pChildObj );
 			}	}	}
		}

      // FOLLOWING THE REGULAR CHILDREN: add other assigned or reverse-assigned children to this node
#ifdef UI_ASHRAE901E
      if (m_iTreeMode == TM_Lighting)
      {  // LIGHTING MODE
         // Add other assigned components
         AddAssignedChildren( iParentClass, hNewItem, iBDBClass, iObjOccur, iSource, ClassToDBIDAssignmentList( iBDBClass ) );
      }
      else if (m_iTreeMode == TM_Mechanical)
      {  // MECHANICAL MODE
         if (iBDBClass == eiBDBCID_HVACSys)
            // Add spaces which assign this HVAC system as children of the system
            AddReverseReferencingChildren( hNewItem, pObj, eiBDBCID_Space, elDBID_Spc_HVACSystem, iSource );

         // Add other assigned HVAC components, such as Pumps, Fans, etc.
         AddAssignedChildren( iParentClass, hNewItem, iBDBClass, iObjOccur, iSource, ClassToDBIDAssignmentList( iBDBClass ) );
      }
#endif  // UI_ASHRAE901E
#ifdef UI_CARES
//      if (m_iTreeMode == TM_Lighting)
//      {  // LIGHTING MODE
//         // Add other assigned components
//         AddAssignedChildren( iParentClass, hNewItem, iBDBClass, iObjOccur, iSource, ClassToDBIDAssignmentList( iBDBClass ) );
//      }
//      else if (m_iTreeMode == TM_Mechanical)
//      {  // MECHANICAL MODE
//         if (iBDBClass == eiBDBCID_HVACSys)
//            // Add spaces which assign this HVAC system as children of the system
//            AddReverseReferencingChildren( hNewItem, pObj, eiBDBCID_Space, elDBID_Spc_HVACSystem, iSource );
//
//         // Add other assigned HVAC components, such as Pumps, Fans, etc.
         // Add other assigned components, regardless of tab
         AddAssignedChildren( iParentClass, hNewItem, iBDBClass, iObjOccur, iSource, ClassToDBIDAssignmentList( iBDBClass ) );
//      }
#endif  // UI_CARES
#ifdef UI_CANRES
         // Add other assigned components, regardless of tab
         AddAssignedChildren( iParentClass, hNewItem, iBDBClass, iObjOccur, iSource, ClassToDBIDAssignmentList( iBDBClass ) );		// SAC 1/31/20 (Com tic #3157)
#endif  // UI_CANRES

      // Expand item if BDBObject says to
      if (pObj->ObjectTreeStateExpanded( m_iTreeMode ))
         Expand( hNewItem, TVE_EXPAND );
   }
   return hNewItem;
}


// Used exclusively for Project (Not Library) trees
BOOL CTreeBDB::OKToAddSpecialObjectToRoot( int /*i1Class*/, int /*i0ObjIdx*/ )
{
   BOOL bRetVal = FALSE;
#ifdef UI_ASHRAE901E
   if ( (m_iTreeMode == TM_Mechanical) && (i1Class == eiBDBCID_Space) )
   {  // Special Case: Spaces in the Mechanical Mode -> Only add to root if no System is assigned
   //   int iError, iSpecialVal;
   //   BEMObject* pData = BEMPX_GetObject( elDBID_Spc_HVACSystem, iSpecialVal, iError, i0ObjIdx );
   //   bRetVal = ( (iError >= 0) && (pData == NULL) );
      BEMObject* pData = NULL;
      bRetVal = (BEMPX_GetObject( elDBID_Spc_HVACSystem, pData, -1, i0ObjIdx ) && pData);
   }
#endif  // UI_ASHRAE901E
   return bRetVal;
}

void CTreeBDB::SetHighlight( int iBDBClassToHighlight )
{
   // Highlight either the currently active item (if a valid BDBClass is passed in)
   // OR the root item (if it exists)
   BOOL bHighlightSet = FALSE;
   if (iBDBClassToHighlight > 0)
   {
      int iError;
      BEMObject* pObj = BEMPX_GetObjectByClass( iBDBClassToHighlight, iError );
      DWORD dwData = GetReferenceFromObject( pObj );
      if (dwData)
      {
         HTREEITEM hItem = GetItemFromData( dwData, FALSE );
         if (hItem)
         {
            EnsureVisible( hItem );
            SelectItem( hItem );
            bHighlightSet = TRUE;
         }
      }
   }
   if (!bHighlightSet && m_htiRootItem)
   {
      Expand( m_htiRootItem, TVE_EXPAND );
      SelectItem( m_htiRootItem );
   }
}

BOOL CTreeBDB::DeleteAllBDBItems()
{
   m_bDeletingBDBItems = TRUE;
   BOOL bRetVal = DeleteAllItems();
   m_bDeletingBDBItems = FALSE;
   return bRetVal;
}

void CTreeBDB::PopulateProjectTree( int iBDBClassToHighlight )
{
   AddProjectComponent( TRUE );

	saTreeFolderLabels.RemoveAll();
	iaTreeFolderClassID.RemoveAll();
   for (int i=0; i < m_iapModes[m_iTreeMode][2]; i++)
   {	int j=0;
      int iError;
      int iNumObjs = BEMPX_GetNumObjects( *m_iappModes[m_iTreeMode][i] );
      for (; j < iNumObjs; j++)
      {  BEMObject* pObj = BEMPX_GetObjectByClass( *m_iappModes[m_iTreeMode][i], iError, j );
         if (pObj && pObj->getClass() &&
             (i < m_iapModes[m_iTreeMode][0] ||
              (i < m_iapModes[m_iTreeMode][1] &&
               ( ( pObj->getClass()->getParentType(0) > -1 && pObj->getParent() == NULL ) ||
                 ( pObj->getClass()->getParentType(0) <  0 &&
                   !BEMPX_CountObjectAssignments( FALSE, *m_iappModes[m_iTreeMode][i], j ) ) )) ||
              (i >= m_iapModes[m_iTreeMode][1] &&
               OKToAddSpecialObjectToRoot( *m_iappModes[m_iTreeMode][i], j ))))
            AddComponent( m_htiRootItem, *m_iappModes[m_iTreeMode][i], j, 0, pObj );
      }

		// SAC 12/29/11 - added folders of assignable components to bottom of tree
		if (IsFolderClass( *m_iappModes[m_iTreeMode][i] ))
		{  BEMClass* pClass = BEMPX_GetClass( *m_iappModes[m_iTreeMode][i], iError );
			if (pClass && pClass->getLongName().length() > 0)
			{  CString sStr;
			   DWORD dwItemData = 1;   // ((BEMO_User + 1) * 100) + *m_iappModes[m_iTreeMode][i];
			   int iBmpID = GetBitmapID( 1002 );  // generic folder bitmap
            sStr = pClass->getLongName().toLatin1().constData();
				if (sStr.GetLength() > 2 && sStr[sStr.GetLength()-1] == 'y' &&
						sStr[sStr.GetLength()-2] != 'a' && sStr[sStr.GetLength()-2] != 'e' && sStr[sStr.GetLength()-2] != 'i' &&
						sStr[sStr.GetLength()-2] != 'o' && sStr[sStr.GetLength()-2] != 'u' )
				{	sStr = sStr.Left( sStr.GetLength()-1 );
					sStr += "ies:";
				}
				else if (sStr.GetLength() > 2 && sStr[sStr.GetLength()-1] != 's')
            	sStr += "s:";
				else
            	sStr += ":";
				saTreeFolderLabels.Add( sStr );		// SAC 2/3/12 - added to establish relationship between tree folders & BEMProc classes
				iaTreeFolderClassID.Add( *m_iappModes[m_iTreeMode][i] );
			   HTREEITEM htiItem = InsertItem( sStr, iBmpID, iBmpID+1, m_htiRootItem, TVI_LAST );
            if (htiItem && SetItemData( htiItem, dwItemData ))
				{  for (j=0; j < iNumObjs; j++)
			      {  BEMObject* pObj = BEMPX_GetObjectByClass( *m_iappModes[m_iTreeMode][i], iError, j );
                  if (pObj && pObj->getName().length() > 0)
                     AddComponent( htiItem, *m_iappModes[m_iTreeMode][i], j, BEMO_User, pObj );
					}
				}
			}
		}
   }

   // Expand root if it isn't already (added because dbl-clicking on project (not from root) - then selecting
   // close on project dialog - then switching tree modes was never displaying more than just the root
   if (m_htiRootItem && !ItemIsExpanded( m_htiRootItem ))
      Expand( m_htiRootItem, TVE_EXPAND );

   SetHighlight( iBDBClassToHighlight );
}

void CTreeBDB::PopulateLibraryTree( int /*iBDBClassToHighlight*/ )
{
   DWORD dwItemData = 1;
   CString sStr;		QString qsStr;
   BEMPX_GetString( elDBID_Proj_Ruleset, qsStr, TRUE, 0, BEMP_Sym );
   if (qsStr.length() > 0)
   {
      sStr = "Ruleset Library:  '" + CString(qsStr.toLatin1().constData());
      sStr += "'";
   }
   else
      sStr = "No Ruleset Library Available";

   int iBmpID = GetBitmapID( 1001 );
   m_htiRootItem = InsertItem( sStr, iBmpID, iBmpID+1, TVI_ROOT, TVI_LAST );
   if ((m_htiRootItem == NULL) || (!SetItemData( m_htiRootItem, dwItemData )))
      m_htiRootItem = NULL;

   int iError;
   HTREEITEM htiItem;
   for (int i=0; i < m_iapModes[m_iTreeMode][2]; i++)
   {
      BEMClass* pClass = BEMPX_GetClass( *m_iappModes[m_iTreeMode][i], iError );
      if (pClass && pClass->getLongName().length() > 0)
      {
         int iNumRuleLibObjs = BEMPX_GetNumObjects( *m_iappModes[m_iTreeMode][i], BEMO_RuleLib );
         if (iNumRuleLibObjs > 0)
         {
            // First create a node for each type of bldg component
			   iBmpID = GetBitmapID( 1002 );  // generic folder bitmap
            //iBmpID = GetBitmapID( *m_iappModes[m_iTreeMode][i] );
            sStr = pClass->getLongName().toLatin1().constData();
            sStr += " Components:";
            htiItem = InsertItem( sStr, iBmpID, iBmpID+1, m_htiRootItem, TVI_LAST );
            if (htiItem && SetItemData( htiItem, dwItemData ))
            {
               // Then create a subordinate node for each library component of this type
               for (int iObj = 0; iObj < iNumRuleLibObjs; iObj++)
               {
                  BEMObject* pObj = BEMPX_GetObjectByClass( *m_iappModes[m_iTreeMode][i], iError, iObj, BEMO_RuleLib );
                  if (pObj && pObj->getName().length() > 0)
                     AddComponent( htiItem, *m_iappModes[m_iTreeMode][i], iObj, BEMO_RuleLib, pObj );
               }
            }
         }
      }
   }

   if (m_htiRootItem)
      Expand( m_htiRootItem, TVE_EXPAND );
}

void CTreeBDB::PopulateBDBTree( int iTreeMode, int iBDBClassToHighlight, BOOL bOnlyIfRequired )
{
         //BEMPX_WriteLogFile( QString("      calling PopulateBDBTree( %1, %2, %3 )").arg( QString::number(iTreeMode), QString::number(iBDBClassToHighlight), QString::number(bOnlyIfRequired) ) );  // SAC 10/21/21
//   if ( !bOnlyIfRequired || !m_bTreeCurrent )
   if (!bOnlyIfRequired)
      // set this to false in case BEMPUIX_NumBDBDialogInstances() != 0 and therefore we don't populate until next round
      m_bTreeCurrent = FALSE;

   if (BEMPUIX_NumBEMProcDialogInstances() == 0 && (!bOnlyIfRequired || !m_bTreeCurrent) )
   {
      m_lIgnoreNextExpansion = 0;
      m_iTreeMode = iTreeMode;

// SAC 2/28/14 - moved to here so that we can confirm that Proj object exists (an indication that RULE NEW vars are available for display)
		if (/*!sbAppendDBIDsLoaded &&*/ eiBDBCID_Proj > 0 && BEMPX_GetNumObjects( eiBDBCID_Proj ) > 0)
			LoadAppendDBIDs();	// SAC 1/31/19 - revised to check for ruleset change before loading...

      ResetArrayData();
      if ( (DeleteAllBDBItems()) && (m_iTreeMode >= 0) && (m_iTreeMode < TM_NumModes) )
      {
         SetIndent( FontX( 35 ) );  // default = 19

         // if current mode is "Architectural", then grab the BEMProc value for ArchTreeOption and
         // reset the siaModes[] & siapModes[] variables based on the BEMProc value
         if (m_iTreeMode == TM_Architecture || m_iTreeMode == TM_Lighting)
            SetupTreeMode();

         // Populate tree based on tree type (Project vs. Library)
         if (m_bProjectTree)
            PopulateProjectTree( iBDBClassToHighlight );
         else
            PopulateLibraryTree( iBDBClassToHighlight );
                  //BEMPX_WriteLogFile( QString("      - tree repopulated") );  // SAC 10/21/21
      }

      m_bTreeCurrent = TRUE;
   }
}


BEMObject* CTreeBDB::DataToBEMObject( DWORD dwData )
{
	if (dwData==0)		// SAC 4/24/18 - code to return BEMObject* for selected object (w/o specifying dwData argument)
   {	HTREEITEM htiSelItem = GetSelectedItem();
		if (htiSelItem)
			dwData = GetItemData( htiSelItem );
	}
   int iBDBClass = TreeRefToComponent( dwData );
   if (iBDBClass > 0 && iBDBClass <= BEMPX_GetNumClasses())
   {
      int iBDBIndex = TreeRefToIndex( dwData );
      BEM_ObjType eBDBCompType = TreeRefToSource( dwData );
      int iError;
      BEMObject* pObj = BEMPX_GetObjectByClass( iBDBClass, iError, iBDBIndex, eBDBCompType );
      if ( (iError >= 0) && (pObj != NULL) )
         return pObj;
   }
   return NULL;
}

BOOL CTreeBDB::ItemIsExpanded( HTREEITEM hItem )
{
   return (GetItemState( hItem, TVIS_EXPANDED ) & TVIS_EXPANDED);
}

void CTreeBDB::OnTVNItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

   if (pNMTreeView->itemNew.lParam >= (long) m_dwMinValidRef &&
       pNMTreeView->itemNew.lParam <= (long) m_dwMaxValidRef)
   {
      BEMObject* pObj = DataToBEMObject( (DWORD) pNMTreeView->itemNew.lParam );
      if (pObj)
         pObj->SetTreeState( m_iTreeMode, ItemIsExpanded(pNMTreeView->itemNew.hItem) );
   }
	
	*pResult = 0;
}


HTREEITEM CTreeBDB::CheckChildrenForDataMatch( HTREEITEM hti, DWORD dwItemData )
{
   if (ItemHasChildren( hti ))
   {
      hti = GetChildItem( hti );
      while (hti)
      {
         // check this item
         DWORD dwData = GetItemData( hti );
         if (dwData == dwItemData)
            return hti;  // return item if match found
         else
         {
            // if has children, check them
            HTREEITEM htiChild = CheckChildrenForDataMatch( hti, dwItemData );
            if (htiChild)
               return htiChild;
            
            // if still not found, move on to next sibling
      	   hti = GetNextItem(hti, TVGN_NEXT);
         }
      }
   }
   return NULL;
}

HTREEITEM CTreeBDB::GetItemFromData( DWORD dwItemData, BOOL bAllowRoot )
{
   // first check selected item
   HTREEITEM hti = GetSelectedItem();
   DWORD dwData = (hti ? GetItemData( hti ) : 0);
   if (dwData == dwItemData)
      return hti;
   else
   {  // if selected item wasn't the one, then try each item in the control
	   hti = GetNextItem(hti, TVGN_ROOT);
      do
      {  // check this item for a match
         dwData = GetItemData( hti );
         if ( (dwData == dwItemData) && (bAllowRoot || (hti != m_htiRootItem)) )
            return hti;  // return item if match found
         else
         {
            // if has children, check them
            HTREEITEM htiChild = CheckChildrenForDataMatch( hti, dwItemData );
            if (htiChild)
               return htiChild;
            
            // if still not found, move on to next sibling of root
      	   hti = GetNextItem(hti, TVGN_NEXT);
         }
         
      }  while (hti);
   }

   return NULL;  // item not found
}

HTREEITEM CTreeBDB::GetHandleToCurrentlyActive( int iClass, BEMClass* pClass )
{
   if (pClass == NULL)
   {
      int iError;
      pClass = BEMPX_GetClass( iClass, iError );
   }

   if (pClass)
   {
      DWORD dwData = GetReferenceIndex( iClass, pClass->getCurrentBEM0ObjIdx(), pClass->getCurrentBEMObjType() );
      return GetItemFromData( dwData );
   }
   return NULL;
}

HTREEITEM CTreeBDB::BDBObjectToTreeItem( BEMObject* pObj )
{
   if (pObj && pObj->getClass())
   {
      int iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
      DWORD dwData  = GetReferenceIndex(  pObj->getClass()->get1BEMClassIdx(), iObjIdx, pObj->getObjectType() );
      return GetItemFromData( dwData );
   }
   return NULL;
}


void CTreeBDB::CheckAndUpdateTree( long lDBIDModified )
{
   int iClass  = BEMPX_GetClassID(    lDBIDModified );
   int iProp   = BEMPX_GetPropertyID( lDBIDModified );
   int i1Array = BEMPX_GetArrayID(    lDBIDModified );
   if (iProp == 0)
   {
      if (i1Array == BEM_PARAM0_PARENT || i1Array == BEM_PARAM0_NAME)
      {  // Either Parent or Name has been edited
         m_bTreeCurrent = FALSE;
      }
   }
   else if ( iClass > 0 && iClass <= BEMPX_GetNumClasses() &&
				 sdwaAppendDBID.GetSize() >= iClass &&	// SAC 3/22/14 - make sure sdwaAppendDBID array is setup before referencing it // SAC 1/31/19
             sdwaAppendDBID[ iClass-1 ] > 0 )  // update tree if user modified a value which gets appended to
      m_bTreeCurrent = FALSE;                  // its component's tree entry label
   else if ( lDBIDModified == elDBID_Proj_Ruleset )         // always update tree if ruleset changed
      m_bTreeCurrent = FALSE;
#ifdef UI_ASHRAE901E
   else if ( lDBIDModified == elDBID_Proj_ArchTreeOption )  // always update tree if ArchTreeOption changed
      m_bTreeCurrent = FALSE;
   else if ( m_iTreeMode == TM_Lighting &&    // LIGHTING MODE
             DBIDInList( lDBIDModified, &slapLtSys[0] ) )
      m_bTreeCurrent = FALSE;
   else if ( m_iTreeMode == TM_Mechanical &&  // MECHANICAL MODE
             ( lDBIDModified == elDBID_Spc_HVACSystem ||
               DBIDInList( lDBIDModified, &slapHVACSys[0]   ) ||
               DBIDInList( lDBIDModified, &slapClTower[0]   ) ||
               DBIDInList( lDBIDModified, &slapChiller[0]   ) ||
               DBIDInList( lDBIDModified, &slapBoiler[0]    ) ||
               //DBIDInList( lDBIDModified, &slapBlrHtPump[0] ) ||
               DBIDInList( lDBIDModified, &slapPlant[0]     ) ||
               DBIDInList( lDBIDModified, &slapSpace[0]     ) ) )
      m_bTreeCurrent = FALSE;
#elif UI_CARES
	else if ( lDBIDModified == elDBID_Proj_IsMultiFamily )	// SAC 7/29/16 - toggle access to DwellUnitType & DwellUnit objects
	{	long lIsMultiFam;
		BEMPX_SetDataInteger( elDBID_Proj_IsMultiFamily, lIsMultiFam );
		if (lIsMultiFam > 0 && (eiBDBCID_DwellUnitType < 1 || eiBDBCID_DwellUnit < 1))
		{	eiBDBCID_DwellUnitType = BEMPX_GetDBComponentID( "DwellUnitType" );
			eiBDBCID_DwellUnit     = BEMPX_GetDBComponentID( "DwellUnit" );
			m_bTreeCurrent = FALSE;
		}
		else if (lIsMultiFam == 0 && (eiBDBCID_DwellUnitType > 1 || eiBDBCID_DwellUnit > 1))
		{	eiBDBCID_DwellUnitType = 0;
			eiBDBCID_DwellUnit     = 0;
			m_bTreeCurrent = FALSE;
		}
	}
	else if ( elDBID_Proj_RHERSEnabled > 1 && lDBIDModified == elDBID_Proj_RHERSEnabled )	// SAC 9/28/20 - toggle access to RESNETBldg object
	{	long lRHERSEnabled;
		BEMPX_SetDataInteger( elDBID_Proj_RHERSEnabled, lRHERSEnabled );
		if (lRHERSEnabled > 0 && eiBDBCID_RESNETBldg < 1)
		{	eiBDBCID_RESNETBldg = BEMPX_GetDBComponentID( "RESNETBldg" );
			m_bTreeCurrent = FALSE;
		}
		else if (lRHERSEnabled == 0 && eiBDBCID_RESNETBldg > 1)
		{	eiBDBCID_RESNETBldg = 0;
			m_bTreeCurrent = FALSE;
		}
	}
#endif  // UI_*
}


void CTreeBDB::SetDragStatusMessage()
{
   CString sMsg;
   CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
   // Set status bar message
   if (pMainFrm)
   {
      if (m_iOLEDragging > 0)
      {
         sMsg = IsCopying() ? "Copying " : "Moving ";
         sMsg += m_sDragCompString;
      }
      else
         sMsg.Empty();

      pMainFrm->SetStatusBarStrings( sMsg, 0 );
   }
}


void CTreeBDB::SetDropCompElement( TDC_DropCodes eCode, int iClass, long lDBID )
{
   if (m_iDragDropNumber < MAX_DROP_CONNECTIONS)
   {
      m_eDragDropCode[  m_iDragDropNumber ] = eCode;
      m_iDragDropClass[ m_iDragDropNumber ] = iClass;
      m_lDragDropDBID[  m_iDragDropNumber ] = lDBID;

      if ( (m_iDragDropIdx < 0) && (iClass == m_dragInfo.iParentBDBClass) )
      {
         if (lDBID == 0)
            m_iDragDropIdx = m_iDragDropNumber;
         else if (ArrayDataMatch( GetItemData(m_hitemDrag), (DWORD) lDBID, (WORD) eCode ))
            m_iDragDropIdx = m_iDragDropNumber;
      }

      m_iDragDropNumber++;
   }
   else
      // Must increase #define MAX_DROP_CONNECTIONS
      ASSERT( TRUE );
}

void CTreeBDB::SetDropCompatibilityInfo()
{
   m_iDragDropIdx    = -1;
   m_iDragDropNumber = 0;

   int i=0;
   int iError;
   // First set any Parent/Child Drag/Drop compatibility codes
   BEMClass* pClass = BEMPX_GetClass( m_dragInfo.iBDBClass, iError );
   if (pClass)
      while (pClass->getParentType(i) >= 0)
         SetDropCompElement( TDC_Child, pClass->getParentType(i++) + 1, 0 );

   // Now set Object Referencing Drag/Drop compatibility codes
   for (i=0; (m_iDragDropNumber < MAX_DROP_CONNECTIONS) && (i < m_iapModes[m_iTreeMode][2]); i++)
   {
      long** plDBIDList = ClassToDBIDAssignmentList( *m_iappModes[m_iTreeMode][i] );
      int j=0;
      while ( (m_iDragDropNumber < MAX_DROP_CONNECTIONS) && (plDBIDList[ j ]) )
      {
         BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( *plDBIDList[ j++ ], iError );
         //if ((iError == 0) && pPropType && (pPropType->m_i1ObjClassIdx == m_dragInfo.iBDBClass))
         //   SetDropCompElement( TDC_Reference, *m_iappModes[m_iTreeMode][i], *plDBIDList[ j-1 ] );
			// SAC 6/15/12 - revised (above) to enable an ARRAY of ObjClassIdxs, since there may be multiple possible assigned object types
         if (iError == 0 && pPropType)
			{	BOOL bObjCompat = FALSE;
				for (int iObjCls=0; (!bObjCompat && iObjCls < BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
					if (pPropType->getObj1ClassIdx(iObjCls) == m_dragInfo.iBDBClass)
					{

	// SAC 12/9/13 - at some point may need to take into account DBID assignment compatibility via - DBIDAssignmentCompatible( long lAssignmentDBID, int iBEMClass, int iObjIdx, BEM_ObjType eBEMObjType )

					 	bObjCompat = TRUE;
		            SetDropCompElement( TDC_Reference, *m_iappModes[m_iTreeMode][i], *plDBIDList[ j-1 ] );
					}
			}
      }
   }

   // Finally, set Reverse Referencing Drag/Drop compatibility codes
#ifdef UI_ASHRAE901E
   if ( (m_iDragDropNumber < MAX_DROP_CONNECTIONS) && (m_iTreeMode == TM_Mechanical) &&
        (m_dragInfo.iBDBClass == eiBDBCID_Space) )
      SetDropCompElement( TDC_ReverseRef, eiBDBCID_HVACSys, elDBID_Spc_HVACSystem );
#endif  // UI_ASHRAE901E
}

// called to start OLE drag and doesn't terminate until item dropped elsewhere
void CTreeBDB::BeginOleDrag(NMHDR* pNMHDR, LRESULT* pResult, int iButton)
{
   NM_TREEVIEW *pnmtv = (NM_TREEVIEW *)pNMHDR;
   if ( pnmtv->itemNew.lParam ) 
   {
      BEMObject* pObj = DataToBEMObject( pnmtv->itemNew.lParam );
      if ( pObj ) 
      {
         COleDataSource *pDataSource = new COleDataSource;
         try 
         {
            CPoint ptAction;
            GetCursorPos(&ptAction);
            ScreenToClient(&ptAction);

            HTREEITEM hitemDrag = m_hitemPossiblyDrag;
            if (!hitemDrag)
            {
               UINT   nFlags;
               hitemDrag = HitTest(ptAction, &nFlags);
            }

            m_hitemDrag = hitemDrag;  // HitTest(ptAction, &nFlags);
            m_hitemDragParent = GetParentItem( m_hitemDrag );
            m_hitemDrop = NULL;
            m_hitemLastBadDrop = NULL;
            m_iOLEDragging = iButton;  // 0=>No, 1=>Left(move), 2=>Right(copy)

            // copy data describing drag object to clipboard
            GetNativeClipboardData( hitemDrag, pObj, pDataSource );

            // m_spDraggedItem = spItem;
            DROPEFFECT dropEffect = pDataSource->DoDragDrop();
            // m_spDraggedItem = NULL;

            InitDragInfo();
            m_hitemDrag = NULL;
            m_hitemDragParent = NULL;
            m_hitemDrop = NULL;
            m_hitemLastBadDrop = NULL;
            m_iOLEDragging = 0;  // 0=>No, 1=>Left(move), 2=>Right(copy)

            if ( DROPEFFECT_MOVE == dropEffect ) 
            {
               // spItem->Parent->Remove( spItem );
            }
            pDataSource->InternalRelease();
         }
         catch ( ... )
         {
            pDataSource->InternalRelease();
            throw;
         }
      }
   }
   *pResult = 0;
}
void CTreeBDB::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // RFH Uncomment this and comment out BeginOleDrag to return to the old drag
//   BeginDrag( pNMHDR, pResult, 1 );
   if (eInterfaceMode == IM_INPUT)
      BeginOleDrag( pNMHDR, pResult, 1 );
}
void CTreeBDB::OnBeginRDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
//   BeginDrag( pNMHDR, pResult, 2 );
   if (eInterfaceMode == IM_INPUT)
      BeginOleDrag( pNMHDR, pResult, 2 );
}

// Recursive function to create a copy of a building component & all of its children
static char BASED_CODE szErrCr8ing[]  = "An error occurred while attempting to create a copy of the ";
static char BASED_CODE szErrCopying[] = "An error occurred while attempting to copy ";

BEMObject* CTreeBDB::CopyBDBComponent( BEMObject* pCopyObj, BEMObject* pParentObj )
{
   BEMObject* pNewObj = NULL;
   if (pCopyObj && pCopyObj->getClass())
   {
//      CString sName = "Copy " + pCopyObj->getName();
      QString sName;
      BOOL bSOCN = BEMPX_SetObjectCopyName( sName, pCopyObj->getName().toLatin1().constData() );		bSOCN;

      pNewObj = BEMPX_CreateObject( pCopyObj->getClass()->get1BEMClassIdx(), sName.toLatin1().constData(), pParentObj, BEMO_User, FALSE );
      if (pNewObj == NULL)
      {
         // report error creating object
         CString sErr = szErrCr8ing;   sErr += pCopyObj->getClass()->getLongName().toLatin1().constData();
         sErr += " '";   sErr += pCopyObj->getName().toLatin1().constData();   sErr += "'.";
         MessageBox( sErr, "CTreeBDB::CopyBDBComponent() Error", MB_ICONSTOP | MB_OK );
      }
      else
      {
         // First copy the data from the CopyObj to the NewObj
         if (!BEMPX_CopyComponent( pNewObj, pCopyObj, -1, true /*bCopyPrimaryDefaultDataAsUserDefined*/ ))		// SAC 6/8/15 - CBECC issue 1061
         {
            // report error creating object
            CString sErr = szErrCopying;   sErr += pCopyObj->getClass()->getLongName().toLatin1().constData();
            sErr += " '";   sErr += pCopyObj->getName().toLatin1().constData();   sErr += "'.";
            MessageBox( sErr, "CTreeBDB::CopyBDBComponent() Error", MB_ICONSTOP | MB_OK );
         }
         else
         {
            // Now, copy all of the copied object's children into the new object's children
//             for (POSITION pos = pCopyObj->m_children.GetHeadPosition(); pos != NULL; )
//             {  BEMObject* pChildObj = (BEMObject*) pCopyObj->m_children.GetNext( pos );
				int iNumChldrn = pCopyObj->getChildCount();
				for (int iC=0; iC < iNumChldrn; iC++)
				{	BEMObject* pChildObj = pCopyObj->getChild(iC);			ASSERT( pChildObj );
                if (pChildObj)
                   CopyBDBComponent( pChildObj, pNewObj );
            }

            // Now, copy all assigned components which can only be referenced by a single component
//            for (int iProp=0; iProp<pCopyObj->m_properties.GetSize(); iProp++)
//            {
//               BEMProperty* pProp = pCopyObj->m_properties[iProp];
//               ASSERT( pProp );  // SAC 1/14/03 - end of new addition
				int iNumProps = pCopyObj->getPropertiesSize();
				for (int iProp=0; iProp<iNumProps; iProp++)
				{	BEMProperty* pProp = pCopyObj->getProperty(iProp);			ASSERT( pProp );
               if ( pProp && pProp->getType() && (pProp->getType()->getPropType() == BEMP_Obj) && pProp->getObj() &&
                    pProp->getObj()->getClass() && (pProp->getObj()->getClass()->getMaxReferences() == 1) )
               {  // copy object
                  BEMObject* pNewAssignedObj = CopyBDBComponent( pProp->getObj() );
                  // now assign new object to equivalent property of NEW main object
                  long lAssignDBID = BEMPX_GetDBID( pProp->getType()->get1ClassIdx(), pProp->getType()->get1PropTypeIdx(),
                                                  pProp->get1ArrayIdx() );
                  if (!pNewAssignedObj || (BEMPX_SetBEMData( lAssignDBID, BEMP_Obj, (void*) pNewAssignedObj,
                                                          BEMO_User, BEMPX_GetObjectIndex(  pNewObj->getClass(), pNewObj ) ) < 0) )
                  {
                     // report error creating object
                     CString sErr = szErrCopying;   sErr += pProp->getObj()->getClass()->getLongName().toLatin1().constData();
                     sErr += " '";   sErr += pProp->getObj()->getName().toLatin1().constData();   sErr += "'.";
                     MessageBox( sErr, "CTreeBDB::CopyBDBComponent() Error", MB_ICONSTOP | MB_OK );
                  }
               }
            }

         }
      }
   }
   return pNewObj;
}


void CTreeBDB::DropItemBeingDragged( COleDataObject* pDataObject )
{
   int iError;

   BOOL bDragLocal = (m_iOLEDragging > 0 && m_hitemDrag != NULL);  // TRUE only if drag began in this tree

   DWORD dwDropData = GetItemData( m_hitemDrop );
   int iDropClass = TreeRefToComponent( dwDropData );
   int iDropIndex = TreeRefToIndex( dwDropData );
   BEM_ObjType otDropType = TreeRefToSource( dwDropData );
   BEMObject* pDropObj = BEMPX_GetObjectByClass( iDropClass, iError, iDropIndex, otDropType );

   DWORD dwDragData      = (!bDragLocal ?        0 : GetItemData( m_hitemDrag ));
   int iDragIndex      = (!bDragLocal ?        0 : TreeRefToIndex( dwDragData ));
   BEM_ObjType otDragType = (!bDragLocal ? BEMO_User : TreeRefToSource( dwDragData ));
   BEMObject* pDragObj   = (!bDragLocal ?     NULL : BEMPX_GetObjectByClass( m_dragInfo.iBDBClass, iError, iDragIndex, otDragType ));

   HTREEITEM htiNewItem = NULL;
   BOOL bDataModified = TRUE;
   long lAddCompDBID = m_lDragDropDBID[ m_iDropIdx ];
   TDC_DropCodes eAddCompCode = m_eDragDropCode[ m_iDropIdx ];
   if (!IsCopying())         // Moving
   {
      // Modify BDB data
      if (pDropObj && pDropObj->getName().length() > 0)
      {
         // Set active object to be the dragged object, since that is the one
         // that is either about to be edited OR will have the focus set to following a full reset
         BEMPX_SetActiveObjectIndex( m_dragInfo.iBDBClass, iDragIndex, otDragType );
         if (m_eDragDropCode[ m_iDropIdx ] == TDC_Child)
            // Reset Parent to be drop target
            BEMPX_SetBEMData( BEMPX_GetDBID( m_dragInfo.iBDBClass, 0, BEM_PARAM0_PARENT ), BEMP_Obj, (void*) pDropObj );
         else if ( (m_eDragDropCode[ m_iDropIdx ] == TDC_Reference) && pDragObj )
         {  // If this item was previously assigned to another object (not the tree's root), then reset that assignment
            if (m_iDragDropIdx >= 0)
            {  // First set active object to be drag object's original parent, since we must 
               // reset that object's assignment of the dragged component
               DWORD dwDragParData = GetItemData( m_hitemDragParent );
               int iDragParIndex = TreeRefToIndex( dwDragParData );
               BEM_ObjType otDragParType = TreeRefToSource( dwDragParData );
               BEMPX_SetActiveObjectIndex( m_dragInfo.iParentBDBClass, iDragParIndex, otDragParType );
               // Then reset the original drag object's parent assignment
               CString sTemp = "";
               BEMPX_SetBEMData( m_lDragDropDBID[ m_iDropIdx ], BEMP_Str, (void*) ((const char*) sTemp) );
            }

            // Now set active object to be the drop target, since that is the one we are about to edit
            BEMPX_SetActiveObjectIndex( iDropClass, iDropIndex, otDropType );
            // Reset original assignment to dragged object
            BEMPX_SetBEMData( m_lDragDropDBID[ m_iDropIdx ], BEMP_Obj, (void*) pDragObj );

            // Reset entire tree in order to ensure that a previously displaced component
            // is removed from the drop target and added to the tree's root
            m_bTreeCurrent = FALSE;
         }
         else if (m_eDragDropCode[ m_iDropIdx ] == TDC_ReverseRef)
            // Reset dragged object's reverse reference to be the drop target
            BEMPX_SetBEMData( m_lDragDropDBID[ m_iDropIdx ], BEMP_Obj, (void*) pDropObj );
      }

      if (m_bTreeCurrent)  // make minor mods by hand, rather than resetting entire tree
      {
         // Now move the tree item by creating a new one and deleting the dragging one
         DeleteArrayData( dwDragData );
         htiNewItem = AddComponent( m_hitemDrop, m_dragInfo.iBDBClass, iDragIndex, otDragType,
                                    BEMPX_GetObjectByClass(m_dragInfo.iBDBClass, iError, iDragIndex, otDragType), lAddCompDBID, eAddCompCode );
         DeleteItem( m_hitemDrag );
      }
   }
   else if (m_bDragCanCopy)  // Copying
   {
      // Copy component, including children
      BEMObject* pNewObj = NULL;
      if (bDragLocal)
      {
         BEMObject* pParObj = (m_eDragDropCode[ m_iDropIdx ] == TDC_Child) ? pDropObj : pDragObj->getParent();
         pNewObj = CopyBDBComponent( pDragObj, pParObj );
      }
      else  // Drag initiated elsewhere => if drop not parent/child, then new component should have no parent
      {
         BEMObject* pParObj = (m_eDragDropCode[ m_iDropIdx ] == TDC_Child) ? pDropObj : NULL;

         if (pDataObject && pDataObject->IsDataAvailable( g_cfPrivate ))
         {
               //BEMPX_WriteLogFile( QString("      about to call DoPasteNative() from within DropItemBeingDragged()") );  // SAC 10/21/21
            pNewObj = DoPasteNative( pDataObject, m_dragInfo.iBDBClass );

            // now manually set parent object pointer
            if (pNewObj)
            {  // pNewObj should already be the "Active" object via its creation
               long lParDBID = BEMPX_GetDBID( m_dragInfo.iBDBClass, 0, BEM_PARAM0_PARENT );
               BEMPX_SetBEMData( lParDBID, BEMP_Obj, (void*) pParObj );
            }
         }
      }

      if (pNewObj)
      {
         if (m_eDragDropCode[ m_iDropIdx ] == TDC_Reference)
         {  // Set active object to be the drop target, since that is the one we are about to edit
            BEMPX_SetActiveObjectIndex( iDropClass, iDropIndex, otDropType );
            // Reset original assignment to dragged object
            BEMPX_SetBEMData( m_lDragDropDBID[ m_iDropIdx ], BEMP_Obj, (void*) pNewObj );

            // Reset entire tree in order to ensure that a previously displaced component
            // is removed from the drop target and added to the tree's root
            m_bTreeCurrent = FALSE;
         }
         else if (m_eDragDropCode[ m_iDropIdx ] == TDC_ReverseRef)
         {
            BEMPX_SetActiveObjectIndex( m_dragInfo.iBDBClass, BEMPX_GetObjectIndex( pNewObj->getClass(), pNewObj ) );
            // Reset dragged object's reverse reference to be the drop target
            BEMPX_SetBEMData( m_lDragDropDBID[ m_iDropIdx ], BEMP_Obj, (void*) pDropObj );
         }

         if (m_bTreeCurrent)
         {  // Create the new tree item
            htiNewItem = AddComponent( m_hitemDrop, m_dragInfo.iBDBClass, BEMPX_GetObjectIndex( pNewObj->getClass(), pNewObj ),
// Is the newly created component's type library if user dragging into the library ??
                                       BEMO_User, pNewObj, lAddCompDBID, eAddCompCode );
         }
      }
   }
   else
      bDataModified = FALSE;

   if (htiNewItem)
   {
      EnsureVisible( htiNewItem );
      SelectItem( htiNewItem );
   }

   if (bDataModified)
   {
      // Set modified flag and evaluate proposed ruleset
      SetDataModifiedFlag( TRUE );
      GetParentFrame()->SendMessage( WM_EVALPROPOSED, DefaultAction_OpenDialog, iDropClass );
   }

   if (!m_bTreeCurrent)
   {
      PopulateBDBTree( m_iTreeMode, m_dragInfo.iBDBClass );
      SetFocus();
   }
}


//void CTreeBDB::OnButtonUp( int iButton )
//{
//	if (m_iDragging == iButton)
//	{
//		ASSERT(m_pimagelist != NULL);
//		m_pimagelist->DragLeave(this);
//		m_pimagelist->EndDrag();
//		delete m_pimagelist;
//		m_pimagelist = NULL;
//
//      if (m_hitemDrag != m_hitemDrop && m_hitemDrop != NULL && m_iDropIdx >= 0)
//         DropItemBeingDragged();
//      else
//         MessageBeep(0);
//
//		ReleaseCapture();
//		m_iDragging = 0;
//		SelectDropTarget(NULL);
//
//      SetDragStatusMessage();
//      m_hitemPossiblyDrag = NULL;
//	}
//}
//void CTreeBDB::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	OnButtonUp( 1 );
//	CTreeCtrl::OnLButtonUp(nFlags, point);
//}
//void CTreeBDB::OnRButtonUp(UINT nFlags, CPoint point)
//{
//	OnButtonUp( 2 );
//	CTreeCtrl::OnRButtonUp(nFlags, point);
//}


BOOL CTreeBDB::IsCopying()
{
   return ( //(m_iDragging == 1 && GetKeyState(VK_CONTROL) <  0) ||
            //(m_iDragging == 2 && GetKeyState(VK_CONTROL) >= 0) ||
            (m_iOLEDragging == 0) ||  // dragging started from another window
            (m_iOLEDragging == 1 && GetKeyState(VK_CONTROL) <  0) ||
            (m_iOLEDragging == 2 && GetKeyState(VK_CONTROL) >= 0) );
}


BOOL CTreeBDB::DropOK( HTREEITEM hitem )
{
   DWORD dwData = GetItemData( hitem );
   int iBDBClass = TreeRefToComponent( dwData );
   m_iDropIdx = -1;
   // must be valid BDB class AND can't drop onto something of the same class as the item being dragged
   if (iBDBClass > 0 && iBDBClass != m_dragInfo.iBDBClass)
   {
      // no need to check further if the user is copying and the drag class cannot be copied
      if (!IsCopying() || m_bDragCanCopy)
      {
         // if the user is dragging over its own parent,
         // then only allow it if the user is COPYING
         if (hitem == m_hitemDragParent)
         {
            m_iDropIdx = ( IsCopying() &&
                           ( (m_eDragDropCode[ m_iDragDropIdx ] != TDC_Child) ||
                             (BEMPX_CanCreateAnotherChildObject(m_dragInfo.iBDBClass, DataToBEMObject(dwData))) ) )
                          ? m_iDragDropIdx : -1;
         }
         else
         {  // Possible drop target is NOT the original drag item's parent
            if ( (iBDBClass == m_dragInfo.iParentBDBClass) &&
                 ( (m_eDragDropCode[ m_iDragDropIdx ] != TDC_Child) ||
                   (BEMPX_CanCreateAnotherChildObject(m_dragInfo.iBDBClass, DataToBEMObject(dwData))) ) )
               // If this drop target is of the same class as the drag parent, then set
               // m_iDropIdx such that the assignment to this drop target will be via the
               // exact same mechanism (lDBID) as that which defines the relationship between
               // the drag object and its parent
               // SAC - 3/10/98 - added code to ensure that if the original connection was parent/child,
               //                 then the new connection (drop) is the same only if the drop item can handle
               //                 another child of this class.
               m_iDropIdx = m_iDragDropIdx;
            else
               // If this drop target is NOT the same class as the drag parent, then simply
               // assume assignment via the first avaiable mechanism
               // SAC - 3/10/98 - added code to ensure that if the proposed new connection is parent/child,
               //                 then the new connection (drop) is OK only if the drop item can handle
               //                 another child of this class.
               for (int i=0; (m_iDropIdx == -1) && (i < m_iDragDropNumber); i++)
                  m_iDropIdx = ( (m_iDragDropClass[i] == iBDBClass) &&
                                 ( (m_eDragDropCode[i] != TDC_Child) ||
                                   (BEMPX_CanCreateAnotherChildObject(m_dragInfo.iBDBClass, DataToBEMObject(dwData))) ) )
                                ? i : -1;
         }
      }
   }

   if (m_iDropIdx == -1)
      m_hitemLastBadDrop = hitem;

   return (m_iDropIdx != -1);
}

//void CTreeBDB::OnMouseMove(UINT nFlags, CPoint point) 
//{
//   if (m_iDragging > 0)
//   {
//      ASSERT(m_pimagelist != NULL);
//      m_pimagelist->DragMove(point);
//
//      UINT      flags;
//      HTREEITEM hitem = HitTest(point, &flags);
//      if (hitem != m_hitemLastBadDrop && hitem != m_hitemDrop)
//      {
//         if (hitem == NULL || !DropOK(hitem))
//            hitem = m_hitemDrag;
//         else
//            m_hitemLastBadDrop = NULL;
//
//         m_pimagelist->DragLeave(this);
//         SelectDropTarget(hitem);
//         m_hitemDrop = hitem;
//         m_pimagelist->DragEnter(this, point);
//      }
//   }
//
//   CTreeCtrl::OnMouseMove(nFlags, point);
//}


void CTreeBDB::OnTVNItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
   if (m_lIgnoreNextExpansion == pNMTreeView->itemNew.lParam ||
       BEMPUIX_NumBEMProcDialogInstances() > 0 ||
       pNMTreeView->itemNew.lParam == 0)
   {
   	*pResult = TRUE;
      if (m_lIgnoreNextExpansion == pNMTreeView->itemNew.lParam)
         m_lIgnoreNextExpansion = 0;
   }
   else
   	*pResult = 0;
}

void CTreeBDB::OnNMDblClk(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
   // set flag to prevent the future expansion or contraction of this tree
   // item caused by this double-click
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem) // && ItemHasChildren( htiSelItem ))
      m_lIgnoreNextExpansion = (long) GetItemData( htiSelItem );

   // edit item (rather than expanding or contracting it)
   PostMessage( WM_EDITTREEITEM );

	*pResult = 0;
}


void CTreeBDB::OnTVNSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   if (m_bProjectTree && !m_bDeletingBDBItems && pNMTreeView && pNMTreeView->itemNew.hItem &&
       BEMPUIX_NumBEMProcDialogInstances() == 0)
   {
      DWORD dwData = GetItemData( pNMTreeView->itemNew.hItem );
      int iBDBClass = TreeRefToComponent( dwData );
      if (iBDBClass > 0)
         BEMPX_SetActiveObjectIndex( iBDBClass, TreeRefToIndex( dwData ), TreeRefToSource( dwData ) );
   }

	*pResult = 0;
}


static int GetArrayIndexOfString( CStringArray& saStr, CString& str )
{	int iArrSize = saStr.GetSize();
	for (int i=0; i<iArrSize; i++)
		if (saStr[i].Compare(str) == 0)
			return i;
	return -1; 
}

// SAC 2/3/12 - added to establish relationship between tree folders & BEMProc classes
int CTreeBDB::GetFolderClassFromTreeItem( HTREEITEM htiTreeItem )
{	int iRetVal = 0;
//	CStringArray 		saTreeFolderLabels;		// SAC 2/3/12 - added to establish relationship between tree folders & BEMProc classes
//	CArray<int, int>	iaTreeFolderClassID;
	CString sItemText = GetItemText( htiTreeItem );
	if (!sItemText.IsEmpty())
	{	int iFolderArray = GetArrayIndexOfString( saTreeFolderLabels, sItemText );					ASSERT( iFolderArray < iaTreeFolderClassID.GetSize() );
		if (iFolderArray >= 0 && iFolderArray < iaTreeFolderClassID.GetSize())
			iRetVal = iaTreeFolderClassID[ iFolderArray ];
	}
	return iRetVal;
}

static CArray<int,int> siaCr8DBIDAssignmentListIndex;   // SAC 9/13/13 - array to track DBIDAssignmentList INDEX of obejct creation menu items

void CTreeBDB::PresentQuickMenu( HTREEITEM htiSelItem )
{
   if (htiSelItem == NULL)
      htiSelItem = GetSelectedItem();

   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
//      if (dwData > 0)
//      {
         int iBDBClass = 0;
			BOOL bIsClassFolder = FALSE;
			if (dwData == 1 && m_bProjectTree)
			{	// check for this tree item being a Folder 
         	iBDBClass = GetFolderClassFromTreeItem( htiSelItem );
				bIsClassFolder = (iBDBClass > 0);
			}
			else
         	iBDBClass = TreeRefToComponent( dwData );
         SelectItem( htiSelItem );
   //      CString sItem = GetItemText( htiSelItem );
   //      CString sMsg = "Item Selected: " + sItem;
   //      MessageBox( sMsg );

         RECT rItemRect;
         if (GetItemRect( htiSelItem, &rItemRect, TRUE ))
         {
   //         CString sMsg;
   //         sMsg.Format( "Item Rect( l:%d, t:%d, r:%d, b:%d )", rItemRect.left, rItemRect.top, rItemRect.right, rItemRect.bottom );
   //         MessageBox( sMsg );

            CMenu menu;
            if (menu.CreatePopupMenu())
            {
               // Edit, Rename & Delete items
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEEDIT, "&Edit" ))
                  MessageBox( "AppendMenu( Edit ) Failed." );
               if (!menu.AppendMenu( MF_STRING, IDQM_TREERENAME, "&Rename" ))
                  MessageBox( "AppendMenu( Rename ) Failed." );
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEDELETE, "&Delete" ))
                  MessageBox( "AppendMenu( Delete ) Failed." );
               if (!menu.AppendMenu( MF_SEPARATOR ))
                  MessageBox( "AppendMenu( Separator ) Failed." );
               if (!menu.AppendMenu( MF_STRING, IDQM_TREECOPY, "&Copy" ))
                  MessageBox( "AppendMenu( Copy ) Failed." );
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEPASTE, "&Paste" ))
                  MessageBox( "AppendMenu( Paste ) Failed." );

               if (htiSelItem == m_htiRootItem || dwData < m_dwMinValidRef ||
                   !m_bProjectTree)
                  menu.EnableMenuItem( IDQM_TREEEDIT  , MF_GRAYED );
               if (htiSelItem == m_htiRootItem || dwData < m_dwMinValidRef ||
                   !m_bProjectTree || eInterfaceMode != IM_INPUT)
               {
                  menu.EnableMenuItem( IDQM_TREERENAME, MF_GRAYED );
                  menu.EnableMenuItem( IDQM_TREEDELETE, MF_GRAYED );
               }
               if (htiSelItem == m_htiRootItem || dwData < m_dwMinValidRef)
                  menu.EnableMenuItem( IDQM_TREECOPY, MF_GRAYED );
               if (!OKToPaste( dwData ) || eInterfaceMode != IM_INPUT)
                  menu.EnableMenuItem( IDQM_TREEPASTE, MF_GRAYED );
               if (!menu.AppendMenu( MF_SEPARATOR ))
                  MessageBox( "AppendMenu( Separator ) Failed." );

				// SAC 7/23/14 - added items to allow user to move objects up/down in list
					BEMObject* pObj = DataToBEMObject( dwData );
					bool bCanMoveUp=false, bCanMoveDown=false;
					if (pObj && pObj->getParent() && pObj->getParent()->getClass() && pObj->getParent()->getClass()->get1BEMClassIdx() > 1)
					{	// parent exists and it is NOT the topmost Proj object...
						int i0ChildIdx, iNumChildren;
						if (pObj->GetChildIndices( i0ChildIdx, iNumChildren ))
						{	bCanMoveUp   = (i0ChildIdx > 0);
							bCanMoveDown = (i0ChildIdx < (iNumChildren-1));
					}	}
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEMOVEUP, "Move &Up in list" ))
                  MessageBox( "AppendMenu( MoveUp ) Failed." );
					else if (!bCanMoveUp)
						menu.EnableMenuItem( IDQM_TREEMOVEUP, MF_GRAYED );
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEMOVEDOWN, "Move &Down in list" ))
                  MessageBox( "AppendMenu( MoveDown ) Failed." );
					else if (!bCanMoveDown)
						menu.EnableMenuItem( IDQM_TREEMOVEDOWN, MF_GRAYED );
               if (!menu.AppendMenu( MF_SEPARATOR ))
                  MessageBox( "AppendMenu( Separator ) Failed." );

               int iError;
               CString sMenuItem;
					if (EnableViewFootprint( iBDBClass ))
					{	BEMClass* pBEMClass = BEMPX_GetClass( iBDBClass, iError );
						if (pBEMClass)
							sMenuItem.Format( "&View %s Footprint", pBEMClass->getLongName().toLatin1().constData() );
						else
							sMenuItem = "&View Object Footprint";
						if (!menu.AppendMenu( MF_STRING, IDQM_TREE_VIEWFOOTPRINT, sMenuItem ))
	                  MessageBox( "AppendMenu( View <> Footprint ) Failed." );
	               if (!menu.AppendMenu( MF_SEPARATOR ))
	                  MessageBox( "AppendMenu( Separator ) Failed." );
					}

               // Expand/Contract item
               if (ItemHasChildren( htiSelItem ) && ItemIsExpanded(htiSelItem))
                     sMenuItem = "&Contract";
               else  sMenuItem = "E&xpand";
               if (!menu.AppendMenu( MF_STRING, IDQM_TREEEXPCON, sMenuItem ))
                  MessageBox( "AppendMenu( Expand/Contract ) Failed." );
               if (!ItemHasChildren( htiSelItem ))
                  menu.EnableMenuItem( IDQM_TREEEXPCON, MF_GRAYED );
               if (!menu.AppendMenu( MF_SEPARATOR ))
                  MessageBox( "AppendMenu( Separator ) Failed." );

			// SAC 9/28/15 - new feature
					// Convert object from one type to another
					int** iapClassConvertList = ClassToConvertList( iBDBClass );
					if (iapClassConvertList[0])
					{	CMenu menuConvert;
						BOOL bConvertMenuOK = menuConvert.CreatePopupMenu();
						if (bConvertMenuOK && m_bProjectTree)
						{	int iCC=-1;
							while (iapClassConvertList[ ++iCC ])
							{	BEMClass* pConvClass = BEMPX_GetClass( *iapClassConvertList[iCC], iError );
								if (pConvClass && pConvClass->getLongName().length() > 0 &&
                            !menuConvert.AppendMenu( MF_STRING, IDQM_TREECONVERT1 + iCC, pConvClass->getLongName().toLatin1().constData() ))
                           MessageBox( "AppendConvertMenu( ... ) Failed." );
                        else if (!BEMPX_CanCreateAnotherUserObject( *iapClassConvertList[iCC] ) ||
                        			(pConvClass && !ClassIsCompatibleWithMode( pConvClass->get1BEMClassIdx() )))
                           // if item added but no more of this comp type can be created, then gray it out
                           menuConvert.EnableMenuItem( IDQM_TREECONVERT1 + iCC, MF_GRAYED );
						}	}

						if (bConvertMenuOK && m_bProjectTree && (menuConvert.GetMenuItemCount() > 0) && eInterfaceMode == IM_INPUT)
						{  // Add Object convert to popup to main quick menu
							if (!menu.AppendMenu( MF_POPUP, (UINT) menuConvert.GetSafeHmenu(), "Con&vert to" ))
								MessageBox( "AppendMenu( Convert t0 ) Failed." );
						}
						else
						{  // Add grayed Convert to entry
							if (!menu.AppendMenu( MF_STRING | MF_GRAYED, 0, "Con&vert to" ))
								MessageBox( "AppendMenu( Convert to ) Failed." );
						}

	               if (!menu.AppendMenu( MF_SEPARATOR ))
   	               MessageBox( "AppendMenu( Separator ) Failed." );
					}

               // Create Child item
               BEMClass* pClass = BEMPX_GetClass( iBDBClass, iError );
               CMenu menuCr8;
               BOOL bCr8MenuOK = menuCr8.CreatePopupMenu();
               if (bCr8MenuOK && m_bProjectTree)
               {
                  if (htiSelItem == m_htiRootItem)
                  {  // ROOT OF TREE
                     if (iBDBClass <= 0)
                     {  // No Project component exists => setup create menu to create only a project
                        pClass = BEMPX_GetClass( eiBDBCID_Proj, iError );
                        if (pClass && pClass->getLongName().length() > 0 &&
                            !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1, pClass->getLongName().toLatin1().constData() ))
                           MessageBox( "AppendCr8Menu( Project ) Failed." );
                        else if (!BEMPX_CanCreateAnotherUserObject( eiBDBCID_Proj ))
                           // if item added but no more of this comp type can be created, then gray it out
                           menuCr8.EnableMenuItem( IDQM_TREECREATE1, MF_GRAYED );
                     }
                     else
                     {  // Project/Root item => add all root comp types to creation list
                        for (int i=0; i < m_iapModes[m_iTreeMode][0]; i++)
                        {
                           BEMClass* pChildClass = BEMPX_GetClass( *m_iappModes[m_iTreeMode][i], iError );
									BOOL bGrayThisItem = FALSE;
#ifdef UI_CARES
									if (*m_iappModes[m_iTreeMode][i] == eiBDBCID_HVACSys)		// SAC 8/22/14 - manually prevent creation of HVACSys obejcts in mech tree of MFam projects (-Res GC #353)
									{	long lIsMultiFam;
										if (BEMPX_SetDataInteger( elDBID_Proj_IsMultiFamily, lIsMultiFam ) && lIsMultiFam > 0)
											bGrayThisItem = TRUE;
									}
#endif // UI_CARES
									if (!bGrayThisItem && eiDeveloperMenu < 1 && PreventCreationWhenNotDevMenu( *m_iappModes[m_iTreeMode][i] ))	// SAC 4/7/16
										bGrayThisItem = TRUE;
                           if (pChildClass && pChildClass->getLongName().length() > 0 &&
                               !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1+i, pChildClass->getLongName().toLatin1().constData() ))
                              MessageBox( "AppendCr8Menu( ... ) Failed." );
                           else if (bGrayThisItem || !BEMPX_CanCreateAnotherUserObject( *m_iappModes[m_iTreeMode][i] ))
                              // if item added but no more of this comp type can be created, then gray it out
                              menuCr8.EnableMenuItem( IDQM_TREECREATE1+i, MF_GRAYED );
                        }
                     }
                  }
                  else if (pClass)
                  {
							if (bIsClassFolder)
							{	// Add creation item only for the tree folder item
                     	if (pClass->getLongName().length() > 0 &&
                     	    !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1, pClass->getLongName().toLatin1().constData() ))
                     	   MessageBox( "AppendCr8Menu( ... ) Failed." );
                     	else if (!BEMPX_CanCreateAnotherUserObject( iBDBClass ) ||
							  				(eiDeveloperMenu < 1 && PreventCreationWhenNotDevMenu( iBDBClass )))  // SAC 6/26/17 - gray items not available when not in dev mode
                     	   // if item added but no more of this comp type can be created, then gray it out
                     	   menuCr8.EnableMenuItem( IDQM_TREECREATE1, MF_GRAYED );
							}
							else
							{	// Add child types to child creation menu
                     	UINT uiCreateID = IDQM_TREECREATE1;
                     	if (pClass->getChildType(0) >= 0)
                     	{  // Add all child types corresponding to selected component type
                     	   for (int i=0; (i < pClass->getNumChildTypes()) && (pClass->getChildType(i) >= 0); i++)
                     	   {
                     	      BEMClass* pChildClass = BEMPX_GetClass( pClass->getChildType(i)+1, iError );
                     	      if (pChildClass && pChildClass->getLongName().length() > 0 &&
                     	          !menuCr8.AppendMenu( MF_STRING, uiCreateID++, pChildClass->getLongName().toLatin1().constData() ))
                     	         MessageBox( "AppendCr8Menu( ... ) Failed." );
                     	      else if ( !BEMPX_CanCreateAnotherChildObject( pClass->getChildType(i)+1, pObj ) ||
                     	                (pChildClass && !ClassIsCompatibleWithMode( pChildClass->get1BEMClassIdx() )) ||
                     	                (eiDeveloperMenu < 1 && PreventCreationWhenNotDevMenu( pChildClass->get1BEMClassIdx() )) )	// SAC 4/7/16
                     	         // if item added but no more of this comp type can be created, then gray it out
                     	         menuCr8.EnableMenuItem( uiCreateID-1, MF_GRAYED );
                     	   }
                     	}
                     	
                     	// Add additional create entries for assigned components
								siaCr8DBIDAssignmentListIndex.RemoveAll();   // SAC 9/13/13
								CArray<long,long> laCr8EnabledCompPropIDs, laCr8DisabledCompPropIDs, laCr8EnabledCompPropIDsActual;   // SAC 9/13/13
                     	long** plDBIDList = ClassToDBIDAssignmentList( iBDBClass );
                     	int iDBIDListIdx = 0;
                     	while (plDBIDList[ iDBIDListIdx ] != NULL)
                     	{
                     	   iError = 0;
                     	   long lAssignmentDBID = *plDBIDList[ iDBIDListIdx++ ];
                     	   BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lAssignmentDBID, iError );
                     	   if ( (iError == 0) && pPropType && pPropType->getDescription().length() > 0 &&
											DBIDAssignmentCompatible( lAssignmentDBID, iBDBClass, TreeRefToIndex( dwData ), TreeRefToSource( dwData ) ) )
                     	   {
						// SAC 9/13/13 - revised code to first check for enable/disabled state - THEN determine whether this is a redundant array element => don't create
										BOOL bEnableCr8Item = TRUE;
                     	      // if an object is already assigned, then gray this selection out
                     	//      int iError, iSpecialVal;
                     	//      BEMObject* pAssignedObj = BEMPX_GetObject( lAssignmentDBID, iSpecialVal, iError );
                     	      BEMObject* pAssignedObj = NULL;
                     	      BEMPX_GetObject( lAssignmentDBID, pAssignedObj );

                     	      //if ( ((iError >= 0) && pData) ||
                     	      //     (!ClassIsCompatibleWithMode( pPropType->m_i1ObjClassIdx )) )
                     	      //   menuCr8.EnableMenuItem( uiCreateID-1, MF_GRAYED );
                              // SAC 6/15/12 - replaced above w/ following to enable MULTIPLE object type assignment
                     	//      if (iError >= 0 && pAssignedObj)
                     	      if (pAssignedObj)
                     	         bEnableCr8Item = FALSE;
										else
										{	BOOL bObjCompat = FALSE;
										  	for (int iObjCls=0; (!bObjCompat && iObjCls < BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjCls++)
										  	{	if (pPropType->getObj1ClassIdx(iObjCls) > 0 && ClassIsCompatibleWithMode( pPropType->getObj1ClassIdx(iObjCls) ) &&
										  				(eiDeveloperMenu > 0 || !PreventCreationWhenNotDevMenu( pPropType->getObj1ClassIdx(iObjCls) )))	// SAC 4/7/16
										  		 	bObjCompat = TRUE;
										  	}
										  	if (!bObjCompat)
	                     	         bEnableCr8Item = FALSE;
										}

										long lAssignCompPropDBID = BEMPX_GetDBID( BEMPX_GetClassID( lAssignmentDBID ), BEMPX_GetPropertyID( lAssignmentDBID ), 1 );  // SAC 9/13/13
										if (	( bEnableCr8Item && !ValueInArrayLong( &laCr8EnabledCompPropIDs , lAssignCompPropDBID )) ||
												(!bEnableCr8Item && !ValueInArrayLong( &laCr8DisabledCompPropIDs, lAssignCompPropDBID )) )
                     	      {	//if (!menuCr8.AppendMenu( MF_STRING, uiCreateID++, pPropType->getDescription().toLatin1().constData() ))
                     	      	//   MessageBox( "AppendCr8Menu( ... ) Failed." );
                     	      	//else
											//{
											//	siaCr8DBIDAssignmentListIndex.Add( iDBIDListIdx-1 );   // SAC 9/13/13
												if (!bEnableCr8Item)
                     	      	   {	//menuCr8.EnableMenuItem( uiCreateID-1, MF_GRAYED );
													laCr8DisabledCompPropIDs.Add( lAssignCompPropDBID );   // SAC 9/13/13
												}
												else
												{	laCr8EnabledCompPropIDs.Add( lAssignCompPropDBID );   // SAC 9/13/13
													laCr8EnabledCompPropIDsActual.Add( lAssignmentDBID );
												}
											//}
                     	      }
                     	   }
                     	}
                  	// SAC 12/6/16 - new separate loop to add menu items so to avoid getting combination of disabled and enabled items for some object types
                  		for (int iCr8Lp=0; iCr8Lp<2; iCr8Lp++)
                  		{	CArray<long,long>* plaCr8CompPropIDs     = (iCr8Lp==0 ? &laCr8EnabledCompPropIDsActual : &laCr8DisabledCompPropIDs);
                  			//CArray<long,long>* plaPrevCr8CompPropIDs = (iCr8Lp==0 ? NULL : &laCr8EnabledCompPropIDs);
	                  		for (int iCr8Item=0; iCr8Item < (int) plaCr8CompPropIDs->GetSize(); iCr8Item++)
									{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( plaCr8CompPropIDs->GetAt(iCr8Item), iError );
										if (pPropType)
										{	if (iCr8Lp==0)
											{	long lAssignCompPropDBID = BEMPX_GetDBID( BEMPX_GetClassID( plaCr8CompPropIDs->GetAt(iCr8Item) ), BEMPX_GetPropertyID( plaCr8CompPropIDs->GetAt(iCr8Item) ), 1 );
												int idxAssignCompPropDBID = IndexOfValueInArrayLong( &laCr8DisabledCompPropIDs, lAssignCompPropDBID );
												if (idxAssignCompPropDBID >= 0)
													laCr8DisabledCompPropIDs[idxAssignCompPropDBID] = 0;
											}
                     	      	if (!menuCr8.AppendMenu( MF_STRING, uiCreateID++, pPropType->getDescription().toLatin1().constData() ))
                     	      	{  MessageBox( "AppendCr8Menu( ... ) Failed." );
                     	      		uiCreateID--;
                     	      	}
                     	      	else
											{	//siaCr8DBIDAssignmentListIndex.Add( iDBIDListIdx-1 );   // SAC 9/13/13
												siaCr8DBIDAssignmentListIndex.Add( IndexOfDBIDInList( plaCr8CompPropIDs->GetAt(iCr8Item), &plDBIDList[0] ) );
												if (iCr8Lp>0)
                     	      	   	menuCr8.EnableMenuItem( uiCreateID-1, MF_GRAYED );
									}	}	}
                  		}
							}

                  }
                  else
                  {  ASSERT( TRUE );
						}
               }

//               if (bCr8MenuOK && m_bProjectTree && pClass &&
//                   ( (pClass->getChildType(0) >= 0) || (htiSelItem == m_htiRootItem) ))
//               {
//                  // Add child types to child creation menu
//                  if (htiSelItem == m_htiRootItem)
//                  {  // Project/Root item => add all root comp types to creation list
//                     for (int i=0; i < m_iapModes[m_iTreeMode][0]; i++)
//                     {
//                        BEMClass* pChildClass = BEMPX_GetClass( *m_iappModes[m_iTreeMode][i], iError );
//                        if (pChildClass && pChildClass->m_lpszLongName.GetLength() > 0 &&
//                            !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1+i, pChildClass->m_lpszLongName ))
//                           MessageBox( "AppendCr8Menu( ... ) Failed." );
//                        else if (!BEMPX_CanCreateAnotherUserObject( *m_iappModes[m_iTreeMode][i] ))
//                           // if item added but no more of this comp type can be created, then gray it out
//                           menuCr8.EnableMenuItem( IDQM_TREECREATE1+i, MF_GRAYED );
//                     }
//                  }
//                  else
//                  {  // Add all child types corresponding to selected component type
//                     for (int i=0; (i < BEM_MAX_CHILD_TYPES) && (pClass->getChildType(i) >= 0); i++)
//                     {
//                        BEMClass* pChildClass = BEMPX_GetClass( pClass->getChildType(i)+1, iError );
//                        if (pChildClass && pChildClass->m_lpszLongName &&
//                            !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1+i, pChildClass->m_lpszLongName ))
//                           MessageBox( "AppendCr8Menu( ... ) Failed." );
//                        else if (!BEMPX_CanCreateAnotherUserObject( pClass->getChildType(i)+1 ))
//                           // if item added but no more of this comp type can be created, then gray it out
//                           menuCr8.EnableMenuItem( IDQM_TREECREATE1+i, MF_GRAYED );
//                     }
//                  }
//               }
//               else if (bCr8MenuOK && m_bProjectTree && (htiSelItem == m_htiRootItem) && (iBDBClass <= 0) )
//               {  // No Project component exists => setup create menu to create only a project
//                  pClass = BEMPX_GetClass( eiBDBCID_Proj, iError );
//                  if (pClass && pClass->m_lpszLongName &&
//                      !menuCr8.AppendMenu( MF_STRING, IDQM_TREECREATE1, pClass->m_lpszLongName ))
//                     MessageBox( "AppendCr8Menu( Project ) Failed." );
//                  else if (!BEMPX_CanCreateAnotherUserObject( eiBDBCID_Proj ))
//                     // if item added but no more of this comp type can be created, then gray it out
//                     menuCr8.EnableMenuItem( IDQM_TREECREATE1, MF_GRAYED );
//               }

               if (bCr8MenuOK && m_bProjectTree && (menuCr8.GetMenuItemCount() > 0) && eInterfaceMode == IM_INPUT)
               {  // Add Child Creation popup to main quick menu
                  if (!menu.AppendMenu( MF_POPUP, (UINT) menuCr8.GetSafeHmenu(), "&Create" ))
                     MessageBox( "AppendMenu( Create ) Failed." );
               }
               else
               {  // Add grayed Create entry
                  if (!menu.AppendMenu( MF_STRING | MF_GRAYED, 0, "&Create" ))
                     MessageBox( "AppendMenu( Create ) Failed." );
               }

               ClientToScreen( &rItemRect );
               menu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                    rItemRect.right, rItemRect.top, this );
            }
            else
               MessageBox( "CreatePopupMenu() Failed." );
         }
         else
            MessageBox( "GetItemRect() Failed." );
//      }
   }
}

void CTreeBDB::OnNMRClick(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
   POINT pnt;
   ::GetCursorPos( &pnt );
   ScreenToClient( &pnt );
   CPoint point( pnt );
	
   UINT uiHitTestFlag;
   HTREEITEM htiSelItem = HitTest( point, &uiHitTestFlag );
   if (htiSelItem && ((uiHitTestFlag == TVHT_ONITEMICON ) ||
                      (uiHitTestFlag == TVHT_ONITEMLABEL)))
      PresentQuickMenu( htiSelItem );

	*pResult = 0;
}


void CTreeBDB::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   if ( (nChar == VK_F1) && (GetKeyState(VK_MENU)) )
      PresentQuickMenu();
   else
      CTreeCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

// Only catching Alt-Enter, not Enter alone
void CTreeBDB::OnNMReturn(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
   PostMessage( WM_EDITTREEITEM );
	*pResult = 0;
}

LRESULT CTreeBDB::OnEditTreeItem(WPARAM, LPARAM)
{
   OnQuickEdit();
   return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeBDB Quick Menu message handlers

void CTreeBDB::OnQuickEdit()
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
      if (dwData == 0)
      {  ASSERT( FALSE );
		   // Blank Project -> start-up wizard
//         CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
//         if (pMainFrm)
//            pMainFrm->OnBldgWizard();
      }
      else
      {
         int iBDBClass = TreeRefToComponent( dwData );
         if (iBDBClass > 0)
         {
   //         BEMPX_SetActiveObjectIndex( iBDBClass, TreeRefToIndex( dwData ), TreeRefToSource( dwData ) );

   // re-install if more post-edit bombs occur (or perhaps move to following edit dialog display)
   //         // Eat spurious TVN_ITEMEXPANDING messages
   //         MSG msg;
   //         while(::PeekMessage(&msg, m_hWnd, TVN_ITEMEXPANDING, TVN_ITEMEXPANDING, PM_REMOVE));


	//		CString sDbgScreen;
	//		sDbgScreen.Format( "  fntHtBase = %d\n  fntWdBase = %d\n  fntHtSys = %d\n  fntWdSys = %d\n  sysFntSize = %d", fntHtBase, fntWdBase, fntHtSys, fntWdSys, sysFntSize );
	//		AfxMessageBox( sDbgScreen );

				int iMaxTabs = 0;
				long lNumUIDialogTabs;	// SAC 11/15/19 - RESNET
				if (BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "NumUIDialogTabs", iBDBClass ), lNumUIDialogTabs ) && lNumUIDialogTabs > 0)
					iMaxTabs = lNumUIDialogTabs;
				else
					iMaxTabs = BEMPUIX_GetNumConsecutiveDialogTabIDs( iBDBClass, 0 /*iUIMode*/ );

				CWnd* pMainWnd = AfxGetMainWnd();
				if (pMainWnd && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) && iBDBClass == eiBDBCID_Proj)
					((CMainFrame*)pMainWnd)->AutoSaveAsPrecheck( iBDBClass );		// SAC 9/30/20

#ifdef UI_CANRES
            int iNumResProjObjs = (iBDBClass == eiBDBCID_Proj && eiBDBCID_ResProj > 0) ? BEMPX_GetNumObjects( eiBDBCID_ResProj ) : -1;    // force tree update when ResProj or CUAC created during Proj dialog display - SAC 07/27/22
            //int iNumCUACObjs    = (iBDBClass == eiBDBCID_Proj && eiBDBCID_CUAC    > 0) ? BEMPX_GetNumObjects( eiBDBCID_CUAC    ) : -1;
#endif
            m_bTreeCurrent = TRUE;
				int iTabCtrlWd, iTabCtrlHt;
				VERIFY( GetDialogTabDimensions( iBDBClass, iTabCtrlWd, iTabCtrlHt ) );  // SAC 8/29/11
				CString sDialogCaption;
				GetDialogCaption( iBDBClass, sDialogCaption );   // SAC 1/8/12
//            CBEMDialog td( iBDBClass, this );
                  //AfxMessageBox ( "accessing dialog from TreeBDB" );
            CSACBEMProcDialog td( iBDBClass, eiCurrentTab, ebDisplayAllUIControls, (eInterfaceMode == IM_INPUT), this,
// SAC 1/2/01 - added several arguments in order to pass in "OK" button label
                           //   0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, 99 /*iMaxTabs*/,
                              0 /*iDlgMode*/, iTabCtrlWd, iTabCtrlHt, iMaxTabs,
                              (sDialogCaption.IsEmpty() ? NULL : (const char*) sDialogCaption) /*pszCaptionText*/, "OK",
										NULL /*dwaNonEditableDBIDs*/, 0 /*iNumNonEditableDBIDs*/, NULL /*pszExitingRulelist*/,
										NULL /*pszDataModRulelist*/, FALSE /*bPostHelpMessageToParent*/,
										ebIncludeCompParamStrInToolTip, ebIncludeStatusStrInToolTip, ebIncludeLongCompParamStrInToolTip,    // SAC 1/19/12
										(elDefaultOptionInp < DefaultOption_Model) );	// SAC 4/18/18
            if (td.DoModal() == IDOK)
            {}

#ifdef UI_CANRES
            if (iBDBClass == eiBDBCID_Proj &&
                ( (iNumResProjObjs == 0 && BEMPX_GetNumObjects( eiBDBCID_ResProj ) > 0) ||
                  false ))   // (iNumCUACObjs    == 0 && BEMPX_GetNumObjects( eiBDBCID_CUAC    ) > 0) ))
               m_bTreeCurrent = false;       // force tree update when ResProj or CUAC created during Proj dialog display - SAC 07/27/22
#endif

            if (!m_bTreeCurrent)
               PopulateBDBTree( m_iTreeMode, iBDBClass );
            else
               SetHighlight( iBDBClass );

				if (pMainWnd && (pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))) && iBDBClass == eiBDBCID_Proj)
					((CMainFrame*)pMainWnd)->ExecuteAutoSaveAs( iBDBClass );		// SAC 9/30/20
         }
      }
   }
   else
      MessageBox( "GetSelectedItem() returned NULL." );
}


static char BASED_CODE szRename1[] = "This component is not user defined.  Renaming it would cause it to be copied";
static char BASED_CODE szRename2[] = " into the group of user defined components with the name you provide.";
static char BASED_CODE szRename3[] = "  The original (non-user defined) component will retain its original name.  Select";
static char BASED_CODE szRename4[] = " OK to continue the renaming procedure, or Cancel to abort this request.";
static char BASED_CODE szCant1[] = "  However, no more components of this type can be created and therefore you";
static char BASED_CODE szCant2[] = " cannot rename this component.";

void CTreeBDB::OnQuickRename()
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
      int iBDBClass = TreeRefToComponent( dwData );
      int iBDBIndex = TreeRefToIndex( dwData );
      BEM_ObjType eBDBCompType = TreeRefToSource( dwData );
      if (iBDBClass > 0)
      {
         BOOL bContinue = TRUE;
         // if this is a non-user def comp, make sure we CAN create a new comp
         // of this type before continuing.
         if ( (eBDBCompType != BEMO_User) && (!BEMPX_CanCreateAnotherUserObject( iBDBClass )) )
         {
            CString sMsg = szRename1;
            sMsg += szRename2;
            sMsg += szCant1;
            sMsg += szCant2;
            MessageBox( sMsg, "Rename Component", MB_ICONSTOP );
            bContinue = FALSE;
         }
         else if (eBDBCompType != BEMO_User)
         {
            CString sMsg = szRename1;
            sMsg += szRename2;
            sMsg += szRename3;
            sMsg += szRename4;
            bContinue = (MessageBox( sMsg, "Rename Component", MB_OKCANCEL ) == IDOK);
         }

         if (bContinue)
         {
            CDlgRename renDlg( iBDBClass, iBDBIndex, eBDBCompType, this );
            if (renDlg.DoModal() == IDOK)
            {
               int iError;
               BEMObject* pObj = BEMPX_GetObjectByClass( iBDBClass, iError, iBDBIndex, eBDBCompType );
               if (pObj && pObj->getClass())
               {
                  CString csText;
                  SetItemString( pObj, csText );
                  SetItemText( htiSelItem, csText );

                  if (iBDBClass == 1)   // Project component => must reload root item's text
                     AddProjectComponent( FALSE );
               }
            }
         }
      }
   }
}


// Moved to MainFrame - 7/23/98
//static char BASED_CODE szDelStd1[] = "The building component being deleted ";
//static char BASED_CODE szDelRef1[] = "is referenced ";
//static char BASED_CODE szDelRef2[] = " times by other";
//static char BASED_CODE szDelChl1[] = "has ";
//static char BASED_CODE szDelChl2[] = " child";
//static char BASED_CODE szDelChl3[] = " component(s) and has ";
//static char BASED_CODE szDelStd2[] = " component(s).  If this component is deleted, then all ";
//static char BASED_CODE szDelChl4[] = "its children will also be deleted and all references to the ";
//static char BASED_CODE szDelChl5[] = "component being deleted or any of its children";
//static char BASED_CODE szDelRef3[] = " references to it";
//static char BASED_CODE szDelStd3[] = " will be reinitialized.  ";
//static char BASED_CODE szDelStd4[] = "Are you sure you want to delete the ";

void CTreeBDB::OnQuickDelete()
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
      int iBDBClass = TreeRefToComponent( dwData );
      int iBDBIndex = TreeRefToIndex( dwData );
      BEM_ObjType eBDBCompType = TreeRefToSource( dwData );
      if (iBDBClass > 0)
      {
         int iError;
         BEMObject* pObj = BEMPX_GetObjectByClass( iBDBClass, iError, iBDBIndex, eBDBCompType );
         CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
         if (iError >= 0 && pObj && pMainFrm)
         {
            if (pMainFrm->DeleteBuildingComponent( pObj ))
            { }
//               PopulateBDBTree( m_iTreeMode, iBDBClass );
         }
      }
   }
   else
      MessageBox( "GetSelectedItem() returned NULL." );
}


void CTreeBDB::OnQuickExpCon()
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
      Expand( htiSelItem, TVE_TOGGLE );
   else
      MessageBox( "GetSelectedItem() returned NULL." );
}


void CTreeBDB::CreateComponent( int iChildClassIdx )
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      int iBDBClass = 0;
      long lAssignmentDBID = 0;
      if (htiSelItem == m_htiRootItem)
      {
         DWORD dwSelItemData = GetItemData( htiSelItem );
         int iSelItemBDBClass = TreeRefToComponent( dwSelItemData );
         if (iSelItemBDBClass <= 0 && iChildClassIdx == 0)
            // No 'Project' component exists, so create one
            iBDBClass = eiBDBCID_Proj;
         else
            // Project/Root item => classes based on tree mode class arrays
            iBDBClass = *m_iappModes[m_iTreeMode][ iChildClassIdx ];
      }
      else
      {  // Component item => get class of child to create from parents class
         int iError;
         BEMClass* pClass = NULL;
      	DWORD dwData = GetItemData( htiSelItem );
			if (dwData == 1 && m_bProjectTree)		// SAC 2/3/12
				// check for this tree item being a Folder 
      		iBDBClass = GetFolderClassFromTreeItem( htiSelItem );
			else
			{
         	pClass = BEMPX_GetClass( TreeRefToComponent( dwData ), iError );
         	if (pClass)
         	{
            	if (iChildClassIdx < pClass->getNumChildTypes())
            	   iBDBClass = pClass->getChildType( iChildClassIdx ) + 1;
            	else if (iChildClassIdx >= pClass->getNumChildTypes())
            	{  // creation of assigned component rather than a child
            	   iChildClassIdx -= pClass->getNumChildTypes();
            	   long** plDBIDList = ClassToDBIDAssignmentList( pClass->get1BEMClassIdx() );
            	   if (plDBIDList[ iChildClassIdx ] != NULL)
            	   {			ASSERT( siaCr8DBIDAssignmentListIndex.GetSize() > iChildClassIdx );
            	      if (siaCr8DBIDAssignmentListIndex.GetSize() > iChildClassIdx)   // SAC 9/13/13
								lAssignmentDBID = *plDBIDList[ siaCr8DBIDAssignmentListIndex[iChildClassIdx] ];
							else
								lAssignmentDBID = *plDBIDList[ iChildClassIdx ];
            	      BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lAssignmentDBID, iError );
            	      if (iError == 0 && pPropType)
							{	ASSERT( pPropType->getObj1ClassIdx(0) < 1 || pPropType->getObj1ClassIdx(1) < 1 );		// if MULITPLE object types are comaptible w/ this PropType, WHICH ONE should be created?
            	         iBDBClass = pPropType->getObj1ClassIdx(0);  // SAC 6/15/12 - for now, assume the first compatible referenced object type is the type to be created
							}
            	   }
            	}
				}
         }
      }

      if (iBDBClass > 0)
      {
         CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
         if (pMainFrm)
			{	int iError;
				int iAssignmentObjIdx = (lAssignmentDBID > 0 ? BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( lAssignmentDBID ), iError ) ) : -1);		ASSERT( iAssignmentObjIdx >= -1 );  // SAC 5/29/13
            pMainFrm->CreateBuildingComponent( iBDBClass, lAssignmentDBID, TRUE, NULL, 0, 0, iAssignmentObjIdx );
			}
      }
   }
}

void CTreeBDB::OnQuickCreate1()
   {  CreateComponent( 0 );  }
void CTreeBDB::OnQuickCreate2()
   {  CreateComponent( 1 );  }
void CTreeBDB::OnQuickCreate3()
   {  CreateComponent( 2 );  }
void CTreeBDB::OnQuickCreate4()
   {  CreateComponent( 3 );  }
void CTreeBDB::OnQuickCreate5()
   {  CreateComponent( 4 );  }
void CTreeBDB::OnQuickCreate6()
   {  CreateComponent( 5 );  }
void CTreeBDB::OnQuickCreate7()
   {  CreateComponent( 6 );  }
void CTreeBDB::OnQuickCreate8()
   {  CreateComponent( 7 );  }
void CTreeBDB::OnQuickCreate9()
   {  CreateComponent( 8 );  }
void CTreeBDB::OnQuickCreate10()
   {  CreateComponent( 9 );  }
void CTreeBDB::OnQuickCreate11()
   {  CreateComponent( 10 );  }
void CTreeBDB::OnQuickCreate12()
   {  CreateComponent( 11 );  }
void CTreeBDB::OnQuickCreate13()
   {  CreateComponent( 12 );  }
void CTreeBDB::OnQuickCreate14()
   {  CreateComponent( 13 );  }
void CTreeBDB::OnQuickCreate15()
   {  CreateComponent( 14 );  }
void CTreeBDB::OnQuickCreate16()
   {  CreateComponent( 15 );  }
void CTreeBDB::OnQuickCreate17()
   {  CreateComponent( 16 );  }
void CTreeBDB::OnQuickCreate18()
   {  CreateComponent( 17 );  }
void CTreeBDB::OnQuickCreate19()
   {  CreateComponent( 18 );  }
void CTreeBDB::OnQuickCreate20()
   {  CreateComponent( 19 );  }

// SAC 9/28/15 - 
void CTreeBDB::ConvertComponent( int iConvertClassIdx )
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {	int iSelBDBClass = 0, iSelObjIdx = -1;
      int iBDBClass = 0;
      if (htiSelItem == m_htiRootItem)
      {	ASSERT( FALSE );
      }
      else
      {  // Component item => get class of child to create from parents class
         int iError;
         BEMClass* pClass = NULL;
      	DWORD dwData = GetItemData( htiSelItem );
			if (dwData == 1 && m_bProjectTree)		// SAC 2/3/12
			{	// check for this tree item being a Folder 
				ASSERT( FALSE );
			}
			else
			{	iSelBDBClass = TreeRefToComponent( dwData );					ASSERT( iSelBDBClass > 0 );
				iSelObjIdx   = TreeRefToIndex(     dwData );					ASSERT( iSelObjIdx  >= 0 );
				pClass = BEMPX_GetClass( iSelBDBClass, iError );
         	if (pClass && pClass->get1BEMClassIdx() > 0)
         	{
					int** iapClassConvertList = ClassToConvertList( pClass->get1BEMClassIdx() );
					if (iapClassConvertList[0])
					{	int iCC=-1;
						while (iapClassConvertList[ ++iCC ] && iConvertClassIdx >= 0)
						{	if (iConvertClassIdx == 0)
								iBDBClass = *iapClassConvertList[iCC];
							iConvertClassIdx--;
						}	ASSERT( iBDBClass > 0 );
					}
					else
					{	ASSERT( FALSE );		// no valid Convert object types
					}
				}
         }
      }

      if (iSelBDBClass > 0 && iSelObjIdx >= 0 && iBDBClass > 0)
      {
			CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
			if (pMainFrm && pMainFrm->ConvertBuildingComponent( iSelBDBClass, iSelObjIdx, iBDBClass ))
				PopulateBDBTree( m_iTreeMode, iBDBClass );
   }	}
}

void CTreeBDB::OnQuickConvert1()
   {  ConvertComponent( 0 );  }
void CTreeBDB::OnQuickConvert2()
   {  ConvertComponent( 1 );  }
void CTreeBDB::OnQuickConvert3()
   {  ConvertComponent( 2 );  }
void CTreeBDB::OnQuickConvert4()
   {  ConvertComponent( 3 );  }
void CTreeBDB::OnQuickConvert5()
   {  ConvertComponent( 4 );  }
void CTreeBDB::OnQuickConvert6()
   {  ConvertComponent( 5 );  }
void CTreeBDB::OnQuickConvert7()
   {  ConvertComponent( 6 );  }
void CTreeBDB::OnQuickConvert8()
   {  ConvertComponent( 7 );  }
void CTreeBDB::OnQuickConvert9()
   {  ConvertComponent( 8 );  }
void CTreeBDB::OnQuickConvert10()
   {  ConvertComponent( 9 );  }


void CTreeBDB::ChildMove( bool bMoveUp /*=true*/ )
{	HTREEITEM htiSelItem = GetSelectedItem();
	if (htiSelItem)
	{	DWORD dwData = GetItemData( htiSelItem );
		int iBDBClass = TreeRefToComponent( dwData );
		int iBDBIndex = TreeRefToIndex( dwData );
		BEM_ObjType eBDBCompType = TreeRefToSource( dwData );
		if (iBDBClass > 1)	// Class == 1 => Proj - can't move that...
		{	int iError;
			BEMObject* pObj = BEMPX_GetObjectByClass( iBDBClass, iError, iBDBIndex, eBDBCompType );
			if (iError >= 0 && pObj)
			{	VERIFY( pObj->ChangeChildIndex( bMoveUp ) );
//		CString sDbgMsg;	sDbgMsg.Format( "Move %s '%s' UP", pObj->getClass()->getShortName().toLatin1().constData(), pObj->getName().toLatin1().constData() );		MessageBox( sDbgMsg );

				// Set modified flag and evaluate proposed ruleset (?)
				SetDataModifiedFlag( TRUE );
			//??	GetParentFrame()->SendMessage( WM_EVALPROPOSED );
				PopulateBDBTree( m_iTreeMode, pObj->getClass()->get1BEMClassIdx() );
			}
	}	}
}
void CTreeBDB::OnQuickMoveUp()
{	ChildMove( true );
}
void CTreeBDB::OnQuickMoveDown()
{	ChildMove( false );
}


void CTreeBDB::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   if (nChar == VK_CONTROL && m_iOLEDragging > 0)
      SetDragStatusMessage();
   CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTreeBDB::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   if (nChar == VK_CONTROL && m_iOLEDragging > 0)
      SetDragStatusMessage();
   CTreeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}


// Storing the selected item each time a mouse button is clicked ensures that
// BeginDrag() operates on the selected item rather than possibly the item above
// or below (where the cursor may be by the time the drag action actually begins)
void CTreeBDB::SetNextPossibleDragItem()
{
   if (m_iOLEDragging == 0 && m_dragInfo.iBDBClass == 0)
   {  // NOT dragging
      CPoint ptAction;
      UINT   nFlags;
      GetCursorPos(&ptAction);
      ScreenToClient(&ptAction);
      m_hitemPossiblyDrag = HitTest(ptAction, &nFlags);
   }
   else
      m_hitemPossiblyDrag = NULL;
}
void CTreeBDB::OnLButtonDown(UINT nFlags, CPoint point) 
{
   SetNextPossibleDragItem();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}
void CTreeBDB::OnRButtonDown(UINT nFlags, CPoint point) 
{
   SetNextPossibleDragItem();
	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CTreeBDB::OnEditCopy() 
{
   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
      BEMObject* pObj = DataToBEMObject( dwData );
      if ( pObj ) 
      {
         std::auto_ptr<COleDataSource> apDataSource( new COleDataSource );
         GetNativeClipboardData( htiSelItem, pObj, apDataSource.get() );
         apDataSource->SetClipboard( );
         apDataSource.release();
      }
   }
}

void CTreeBDB::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
   BOOL bEnable = FALSE;

   HTREEITEM htiSelItem = GetSelectedItem();
   if (htiSelItem)
   {
      DWORD dwData = GetItemData( htiSelItem );
      BEMObject* pObj = DataToBEMObject( dwData );
      if ( pObj ) 
      {
         bEnable = TRUE;
      }
   }
   pCmdUI->Enable( bEnable );
}

// SETS clipboard data based on pObj
void CTreeBDB::GetNativeClipboardData(HTREEITEM htiItem, BEMObject *pObj, COleDataSource * pDataSource)
{
   std::auto_ptr< CImageList > spImageList( CreateDragImage( htiItem ) );
   if ( !spImageList.get() ) 
   {
      AfxThrowMemoryException( );
   }

   CString csTempFileName;
   csTempFileName = GenerateTempFileName();

   if ( !BEMPX_WriteProjectComponent( csTempFileName, pObj, -1, false /*bWriteAllProperties*/, true /*bWritePrimaryDefaultData*/ ) )		// SAC 6/10/15 - CBECC issue 1061
   {
      CFileException::ThrowOsError( GetLastError() );
   }
   HGLOBAL hGlobal;
   hGlobal = CreateHGLOBALFromFile( csTempFileName );
   pDataSource->CacheGlobalData( CF_TEXT, hGlobal );

   hGlobal = CreateHGLOBALFromFile( csTempFileName );
   pDataSource->CacheGlobalData( g_cfPrivate, hGlobal );

   DeleteFile( csTempFileName );

   DATASOURCE ds;
   ds.iBDBClass = pObj->getClass()->get1BEMClassIdx();
   // set ParentBDBClass only if we are dragging a component from this window
   if (htiItem)
      ds.iParentBDBClass = TreeRefToComponent( GetItemData( GetParentItem( htiItem ) ) );
   else
      ds.iParentBDBClass = 0;

   CSharedFile shFile;
   CArchive ar( &shFile, CArchive::store );
   ar << ds.iBDBClass;
   ar << ds.iParentBDBClass;
   spImageList->Write( &ar );
	ar.Close();

   pDataSource->CacheGlobalData( g_cfDatasource, shFile.Detach() );
}

void CTreeBDB::OnEditPaste() 
{
   COleDataObject clipboardData;
   clipboardData.AttachClipboard();
   HTREEITEM hItem = GetSelectedItem( );
   if ( hItem ) {
      DoPasteItem( hItem, &clipboardData );
   }
}

BOOL CTreeBDB::OKToPaste( DWORD dwData ) 
{
   BOOL bOK = FALSE;

   BEMObject* pObj = DataToBEMObject( dwData );
   if ( pObj ) 
   {
      UINT uiCF = EnumClipboardFormats( 0 );  // specifies a known available clipboard format 
      while (uiCF > 0)
      {
         uiCF = EnumClipboardFormats( uiCF );
      }

      bOK = BEMPX_CanCreateAnotherUserObject( GetDragClassFromClipboard() );
//      COleDataObject clipboardData;
//      clipboardData.AttachClipboard();
//      if ( clipboardData.IsDataAvailable( g_cfDatasource) ) 
//      {
//         std::auto_ptr< CFile > spFile( clipboardData.GetFileData( g_cfDatasource ) );
//         CArchive ar( spFile.get(), CArchive::load );
//         DATASOURCE ds;
//         ar >> ds.iBDBClass;
//         ar >> ds.iParentBDBClass;
//
//         bEnable = BEMPX_CanCreateAnotherUserObject( ds.iBDBClass );
//      }
   }
   return bOK;
}

void CTreeBDB::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
   BOOL bEnable = FALSE;
   if ( eInterfaceMode == IM_INPUT && m_bProjectTree )
   {
      HTREEITEM htiSelItem = GetSelectedItem();
      if (htiSelItem)
      {
         DWORD dwData = GetItemData( htiSelItem );
         bEnable = OKToPaste( dwData );
      }
   }
   pCmdUI->Enable( bEnable );
}


void CTreeBDB::DoPasteItem(HTREEITEM /*hItem*/, COleDataObject * pDataObject)
{
   CWaitCursor busyCursor;
   if ( pDataObject->IsDataAvailable( g_cfPrivate ) ) {
//      DoPasteNative( hItem, pDataObject );
      BEMObject* pNewObj = DoPasteNative( pDataObject );
      if (pNewObj)
      {
               //BEMPX_WriteLogFile( QString("      inside DoPasteItem(), new object '%1'").arg( pNewObj->getName() ) );  // SAC 10/21/21
         // Set modified flag and evaluate proposed ruleset
         SetDataModifiedFlag( TRUE );
			BEMPX_IncrementModsSinceModelDefaulted();		// SAC 5/30/18
         GetParentFrame()->SendMessage( WM_EVALPROPOSED, DefaultAction_InitAnalysis /*DefaultAction_OpenDialog*/, pNewObj->getClass()->get1BEMClassIdx() );

         PopulateBDBTree( m_iTreeMode, pNewObj->getClass()->get1BEMClassIdx() );
      }
               //else  BEMPX_WriteLogFile( QString("      inside DoPasteItem(), no object pointer returned...") );  // SAC 10/21/21
   } else {
               //BEMPX_WriteLogFile( QString("      inside DoPasteItem(), invalid data...") );  // SAC 10/21/21
	   AfxThrowNotSupportedException( );
   }
}

//BEMObject* CTreeBDB::DoPasteNative(HTREEITEM hItem, COleDataObject * pDataObject)
BEMObject* CTreeBDB::DoPasteNative( COleDataObject * pDataObject, int iBDBClass )
{
   BEMObject* pNewObj = NULL;

   if (iBDBClass == 0 && pDataObject && pDataObject->IsDataAvailable( g_cfDatasource)) 
   {
      std::auto_ptr< CFile > spFile( pDataObject->GetFileData( g_cfDatasource ) );
      CArchive ar( spFile.get(), CArchive::load );
      ar >> iBDBClass;
   }
         //int iErr;
         //BEMClass* pCls = (iBDBClass > 0 ? BEMPX_GetClass( iBDBClass, iErr ) : NULL);
         //BEMPX_WriteLogFile( QString("      inside DoPasteNative(), BDBClass %1 '%2'").arg( QString::number(iBDBClass), (pCls ? pCls->getShortName() : "unknown") ) );  // SAC 10/21/21

   HGLOBAL hGlobal;
   hGlobal = pDataObject->GetGlobalData( g_cfPrivate );
   if ( hGlobal )
   {
      CString csTempFileName = GenerateTempFileName();
      CreateFileFromHGLOBAL( hGlobal, csTempFileName );
      try 
      {
//         DWORD dwTargetData = GetItemData( hItem );
//         int iTargetClass = TreeRefToComponent( dwTargetData );
//         int iTargetIndex = TreeRefToIndex( dwTargetData );
//         BEM_ObjType otTargetType = TreeRefToSource( dwTargetData );
//
//         BEMPX_SetActiveObjectIndex( iTargetClass, iTargetIndex, otTargetType );
         pNewObj = BEMPX_ReadProjectComponent( csTempFileName, iBDBClass );
               //BEMPX_WriteLogFile( QString("      inside DoPasteNative(), pNewObj %1").arg( (pNewObj ? "Valid" : "NULL") ) );  // SAC 10/21/21
      }
      catch ( ... ) 
      {
         //DeleteFile( csTempFileName );
         //GlobalFree( hGlobal );
         //throw;
               //BEMPX_WriteLogFile( QString("      inside DoPasteNative(), exception thrown...") );  // SAC 10/21/21
      }
      DeleteFile( csTempFileName );
      GlobalFree( hGlobal );
   }
   else 
   {
      ::MessageBeep( 0xFFFFFFFF );
   }
   return pNewObj;
}

int CTreeBDB::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   // RFH Init the private clipboard formats we use
   if ( !g_cfPrivate ) 
   {
      g_cfPrivate = (CLIPFORMAT) ::RegisterClipboardFormat( "CBECC-Objects" );
      if ( !g_cfPrivate ) 
      {
         return -1;
      }
   }
   if ( !g_cfDatasource ) 
   {
      g_cfDatasource = (CLIPFORMAT) ::RegisterClipboardFormat( "CBECC-Datasource" );
      if ( !g_cfDatasource )
      {
         return -1;
      }
   }

// SAC 2/28/14 - moved to tree population routine so that we can confirm that Proj object exists (an indication that RULE NEW vars are available for display)
//   if (!sbAppendDBIDsLoaded)
//      LoadAppendDBIDs();

   m_dropTarget.m_pTree = this;
   m_dropTarget.Register( this );

	return 0;
}

// Called when drag begins and when dragging something from outside into this tree
DROPEFFECT CTreeBDB::OnDragEnter( CWnd* /*pWnd*/, COleDataObject* pDataObject, DWORD /*dwKeyState*/, CPoint point )
{
   if (eInterfaceMode == IM_INPUT)
   {
      ASSERT( !m_pimagelist );
      SetDragInfo( pDataObject );
      if ( m_pimagelist )
      {
         m_pimagelist->BeginDrag( 0, CPoint( 0, 0 ) ); // set nImage and hotspot
         m_pimagelist->DragEnter( this, point );
      }
   }

   return DROPEFFECT_NONE;
}

// Called when dragging something out of this tree
void CTreeBDB::OnDragLeave( CWnd* /*pWnd*/ )
{
   InitDragInfo();
   DeleteDragImageList();
}

// Called on each mouse move while dragging within any tree control
DROPEFFECT CTreeBDB::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD /*dwKeyState*/, CPoint point )
{
   // RFH This allows the item to be dragged out of the library tree and
   // be visible also it moves the drop hilite which give smoother feedback
   // (the drop hilite does not jump around)
   if ( m_pimagelist ) 
   {
      DROPEFFECT dropeffect = DragOverScroll( pWnd, point );
      if ( DROPEFFECT_NONE != dropeffect ) {
         return dropeffect;
      }

      m_pimagelist->DragMove( point );
      UINT      flags;
      HTREEITEM hitem = HitTest(point, &flags);
      HTREEITEM holditem = GetDropHilightItem();
      if ( holditem != hitem ) 
      {
         m_pimagelist->DragLeave( this );
         SelectDropTarget(hitem);
         m_hitemDrop = hitem;
         m_pimagelist->DragEnter( this, point );
      }
   }

   if ( m_bProjectTree )
   {
      if (m_dragInfo.iBDBClass != 0 || SetDragInfo( pDataObject ))
      {
//         ASSERT(m_pimagelist != NULL);
//         m_pimagelist->DragMove( point );

         UINT      flags;
         HTREEITEM hitem = HitTest(point, &flags);
         if ( hitem && !DropOK( hitem ) )
         {
            // RFH By returning DROPEFFECT_NONE here we tell the user that
            // the drop will fail even though we have moved the drop hilite
            // Also, this fixes several bugs that would cause a crash if you
            // tried to drop in a bad place, e.g. empty project drag a library item
            // into the project tree crash.
            return DROPEFFECT_NONE;
         }

         /*
         RFH I think this logic can be deleted, checkout the new stuff and
         if you agree nuke away

         if (hitem != m_hitemLastBadDrop && hitem != m_hitemDrop)
         {
            if (hitem == NULL || !DropOK(hitem))
               if (m_iOLEDragging)
                  // if OLE dragging w/ invalid target, highlight drag item
                  hitem = m_hitemDrag;
               else
                  hitem = m_htiRootItem;
            else
               m_hitemLastBadDrop = NULL;
         }
         */

         return (IsCopying() ? DROPEFFECT_COPY : DROPEFFECT_MOVE);
      }
   }
   return DROPEFFECT_NONE;
}

BOOL CTreeBDB::OnDrop( CWnd* /*pWnd*/, COleDataObject* pDataObject, DROPEFFECT /*dropEffect*/, CPoint /*point*/ )
{
   DeleteDragImageList();

   BOOL bRetVal = FALSE;
   if ( pDataObject->IsDataAvailable( g_cfPrivate ) &&
        m_hitemDrag != m_hitemDrop && m_hitemDrop != NULL )
   {
      DropItemBeingDragged( pDataObject );
      bRetVal = TRUE;

//    pWnd->ClientToScreen( &point );
//    ScreenToClient( &point );
//    HTREEITEM hItem = HitTest( point );
//    if ( hItem ) {
//      DoPasteItem( hItem, pDataObject );
//      PopulateBDBTree( m_iTreeMode );
//      return TRUE;
//    }
  }

  SelectDropTarget(NULL);
  return bRetVal;
}


BOOL CTreeBDB::SetDragInfo( COleDataObject* pDataObject )
{

   BOOL bRetVal = FALSE;

   InitDragInfo();

   if (pDataObject && pDataObject->IsDataAvailable( g_cfDatasource)) 
   {
      std::auto_ptr< CImageList > spImageList( new CImageList );
      std::auto_ptr< CFile > spFile( pDataObject->GetFileData( g_cfDatasource ) );
      CArchive ar( spFile.get(), CArchive::load );
      ar >> m_dragInfo.iBDBClass;
      ar >> m_dragInfo.iParentBDBClass;
      if ( !m_pimagelist ) 
      {
         spImageList->Read( &ar );
         m_pimagelist = spImageList.release();
      }

      m_bDragCanCopy = BEMPX_CanCreateAnotherUserObject( m_dragInfo.iBDBClass );
      SetDropCompatibilityInfo();

      bRetVal = TRUE;
//      MessageBeep(MB_ICONASTERISK);
   }
//   else
//      MessageBeep(0);

   return bRetVal;
}

int CTreeBDB::GetDragClassFromClipboard()
{
   COleDataObject clipboardData;
   clipboardData.AttachClipboard();
   if ( clipboardData.IsDataAvailable( g_cfDatasource) ) 
   {
      std::auto_ptr< CFile > spFile( clipboardData.GetFileData( g_cfDatasource ) );
      CArchive ar( spFile.get(), CArchive::load );
      DATASOURCE ds;
      ar >> ds.iBDBClass;
      ar >> ds.iParentBDBClass;

      return ds.iBDBClass;
   }
   return 0;
}

void CTreeBDB::DeleteDragImageList()
{
   if ( m_pimagelist ) 
   {
		m_pimagelist->DragLeave( this );
		m_pimagelist->EndDrag( );
      delete m_pimagelist;
      m_pimagelist = NULL;
   }
}

DROPEFFECT CTreeBDB::DragOverScroll(CWnd* /*pWnd*/, CPoint point)
{
   CRect rect;
   GetClientRect( &rect );
   // Leave a 10 pixel margin at the top and bottom
   rect.DeflateRect( 0, 10 );
   if ( point.y < rect.top ) 
   {
      HTREEITEM hVis = GetFirstVisibleItem();
      hVis = GetPrevVisibleItem( hVis );
      if ( hVis ) 
      {
         m_pimagelist->DragLeave( this );
         SelectSetFirstVisible( hVis );
         UpdateWindow( );
         m_pimagelist->DragEnter( this, point );
         return DROPEFFECT_SCROLL;
      }
   }
   else if ( point.y > rect.bottom ) 
   {
      HTREEITEM hVis = GetFirstVisibleItem();
      hVis = GetNextVisibleItem( hVis );
      if ( hVis ) 
      {
         m_pimagelist->DragLeave( this );
         SelectSetFirstVisible( hVis );
         UpdateWindow( );
         m_pimagelist->DragEnter( this, point );
         return DROPEFFECT_SCROLL;
      }
   }
   // That is no-scroll
   return DROPEFFECT_NONE;
}


void CTreeBDB::OnViewFootprint() 
{
#ifdef UI_CANRES
	HTREEITEM htiSelItem = GetSelectedItem();
	if (htiSelItem)
	{	DWORD dwData = GetItemData( htiSelItem );											ASSERT( dwData > 0 );
		if (dwData > 0)
		{	int iBEMClass = TreeRefToComponent( dwData );								ASSERT( iBEMClass > 0 );
			if (iBEMClass != eiBDBCID_Story && iBEMClass != eiBDBCID_Space)
			{	ASSERT( FALSE );	// invalid class type - shouldn't ever get here.
			}
			else
			{	int iError;
				BEMClass* pBEMClass = BEMPX_GetClass( iBEMClass, iError );			ASSERT( pBEMClass );
				if (pBEMClass)
				{	int iObjIdx = BEMPX_GetObjectIndex( pBEMClass );					ASSERT( iObjIdx >= 0 );
					CMainFrame* pMainFrm = (CMainFrame*)GetParentFrame();
					if (pMainFrm)
					{	CDocument* pDoc = pMainFrm->GetActiveDocument();				ASSERT( pDoc );
						if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CComplianceUIDoc)))
						{	CString sObjName, sMsg, sSZGFN, sDocFN = pDoc->GetPathName();
							int iDotIdx = sDocFN.ReverseFind('.');							ASSERT( iDotIdx > 0 );
							if (iDotIdx > 0)
								sDocFN = sDocFN.Left( iDotIdx );
							sSZGFN.Format( "%s - %s %d.svg", sDocFN, pBEMClass->getShortName().toLatin1().constData(), iObjIdx+1 );
							sMsg.Format( "The %s file '%s' is opened in another application.  This file must be closed in that "
							             "application before an updated file can be written.\n\nSelect 'Retry' to update the file "
											 "(once the file is closed), or \n'Cancel' to abort the %s.", "SVG", sSZGFN, "SVG exportation" );
							if (OKToWriteOrDeleteFile( sSZGFN, sMsg ))
							{	sMsg.Empty();
								int iWhatToPlot = ReadProgInt( "options", "ViewFootprintOption", 1 );

								int iDayltMethod = 1;	// SAC 7/29/18 - added to fluctuate between 2013/16 & 2019 Dayltg (taking into account Win/Skylt:DisableDayltgImpact)
								long lEnergyCodeYr = 0;
//#ifdef UI_CARES
//								BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EnergyCodeYearNum" ), lEnergyCodeYr );
//#elif UI_CANRES
								BEMPX_SetDataInteger( BEMPX_GetDatabaseID( "Proj:EngyCodeYearNum"   ), lEnergyCodeYr );
//#endif
								if (lEnergyCodeYr >= 2019)
									iDayltMethod = 2;

								int iNumExpObjs = BEMPX_ExportSVG( sSZGFN, iBEMClass, iObjIdx, iWhatToPlot, iDayltMethod );
								if (iNumExpObjs <= 0)
								{	QString qsObjName;
									VERIFY( BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iBEMClass ), qsObjName, FALSE, 0, -1, iObjIdx ) && !qsObjName.isEmpty() );
									sObjName = qsObjName.toLatin1().constData();
								}
								if (iNumExpObjs < 0)
									sMsg.Format( "Error encountered in exporting of SVG file for %s '%s' (return code %d).", pBEMClass->getShortName().toLatin1().constData(), sObjName, iNumExpObjs );
								else if (iNumExpObjs == 0)
									sMsg.Format( "No object boundaries exported to SVG file (%s '%s').", pBEMClass->getShortName().toLatin1().constData(), sObjName );
								if (!sMsg.IsEmpty())
									MessageBox( sMsg );
								else
								{
									int iPathLen = sSZGFN.ReverseFind('\\');
									CString sSVGPath = (iPathLen > 0 ? sSZGFN.Left( iPathLen ) : "");
									HINSTANCE hinstShellExec = ShellExecute( GetSafeHwnd(), "open", sSZGFN, NULL, sSVGPath, SW_SHOWNORMAL );		hinstShellExec;
								}
							}
	}	}	}	}	}	}
#endif
}
