// CUIGlobl.h : header file for CBECC External Objects
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

#ifndef __CUIGLOBL_H__
#define __CUIGLOBL_H__


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//     UI MODE TOGGLE
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//#define  UI_ASHRAE901E
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Application wide externals

//extern const char* szCUIVersion;

extern HINSTANCE ehCBECCInstance;
extern int       eiDeveloperMenu;
extern int       eiAllowDisplayOfDetailedInputs;

extern int appCXFullScreen, appCYFullScreen,
           appXScreenBase, appYScreenBase;

extern float appXRatio, appYRatio;

extern BOOL ebAppInitialized;
extern BOOL ebInitiateProjectCreation;
extern BOOL ebInitiateBatchProcViaStartDlg;	// SAC 11/14/17
extern BOOL ebDisplayAllUIControls;
extern BOOL ebAnalysisRangeChecks;
extern BOOL ebShowHelpFollowingWizard;  // SAC 2/14/01
extern BOOL ebIncludeCompParamStrInToolTip;   // SAC 1/19/12
extern BOOL ebIncludeLongCompParamStrInToolTip;   // SAC 8/13/13
extern BOOL ebIncludeStatusStrInToolTip;      // SAC 1/19/12
extern BOOL ebVerboseInputLogging;       // SAC 3/5/12
extern BOOL ebLogProjectOpen;		// SAC 4/15/18

extern int eiCurrentTab;

extern int eiTabDlgCtrlDY;
extern int eiTabDlgCtrlMarg;

extern UINT euiBDBObjClipFormat;

extern BOOL ebOpeningCommandLineFile;  // SAC 1/1/01
extern CRecentFileList* epMRU;  // SAC 1/2/01

extern CString esDataModRulelist;  // SAC 10/24/12

enum InterfaceMode {
      IM_INPUT,
      IM_PROPOSED,
      IM_BUDGET,
      NUM_INTERFACE_MODES };

extern InterfaceMode eInterfaceMode;
extern const char* pszCUIFileExt[ NUM_INTERFACE_MODES ];

extern const char* szErrIntModeNotInp;
extern const char* szErrNotEditable;

// Analysis Status Enum
enum AnalysisStatus
{  AS_None,
   AS_EvalPropInput,
   AS_EvalPostPropInput,
   AS_SimPropDesign,
   AS_ReadPropDesign,
   AS_EvalPropHVAC,
   AS_EvalPropFinal,
   AS_SimPropFinal,
   AS_ReadPropFinal,
   AS_StoreProp,
   AS_EvalBudgetConv,
   AS_SimBudgetDesign,
   AS_ReadBudgetDesign,
   AS_EvalBudgetHVAC,
   AS_EvalBudgetFinal,
   AS_SimBudgetFinal,
   AS_ReadBudgetFinal,
   AS_EvalFinalComp,
   AS_StoreBudget,
   AS_RestoreInput,
   AS_NUM_STEPS
};
extern int eiCurAnalysisStep;

extern const char* szErrRestoreInp;

//	extern const char* epszRLs[];
//	extern const char* epszWRLs[];

/////////////////////////////////////////////////////////////////////////////
// X,Y Conversion Functions for System Font Size

extern int fntHtBase, fntWdBase, fntHtSys, fntWdSys;  
extern int sysFntSize;												// in tenths of a point.
extern int eiFontScalePct;

#define FontX(x)    ( (x*fntWdSys *eiFontScalePct)/(fntWdBase*100) )
#define FontY(y)    ( (y*fntHtSys *eiFontScalePct)/(fntHtBase*100) )
#define InvFontX(x) ( (x*fntWdBase*100)/(fntWdSys*eiFontScalePct)  )
#define InvFontY(y) ( (y*fntHtBase*100)/(fntHtSys*eiFontScalePct)  )


/////////////////////////////////////////////////////////////////////////////
// External Pens

extern CPen windowPen;
extern CPen dialogPen;
extern CPen blackDotPen;
extern CPen blackPen;
//extern CPen greyPen;
extern CPen btnHighlightPen;
extern CPen btnShadowPen;


/////////////////////////////////////////////////////////////////////////////
// External Brushes

extern CBrush buttonBrush;
extern CBrush whiteBrush;
extern CBrush blackBrush;
extern CBrush greyBrush;
extern CBrush darkGreyBrush;


/////////////////////////////////////////////////////////////////////////////
// External Fonts

extern CFont menuFont;
extern CFont toolBarFont;
extern CFont vSmallFont;
extern CFont stdFont;
extern CFont boldFont;
extern CFont unitsFont;
extern CFont dataTypeFont;
extern CFont vDataTypeFont;
extern CFont underlineFont;
extern CFont italicFont;
extern CFont italicUndFont;

enum CUIFontType
{
   FNT_MENU,
   FNT_TOOLBAR,
   FNT_VSMALL,
   FNT_STD,
   FNT_BOLD,
   FNT_UNITS,
   FNT_DATATYPE,
   FNT_VDATATYPE,
   FNT_UNDERLINE,
   FNT_ITALIC,
   FNT_ITALUNDER,
   FNT_NUMFONTS
};

//extern void DrawWin95Shadow( CDC* pDC, int left, int top, int right, int bottom );

extern CFont* GetCUIFont( int fontType );

extern int    GetCUIFontHeight( int fontType );

/////////////////////////////////////////////////////////////////////////////
// Misc Extern Strings

extern CString esProgramPath;
extern CString esDataPath;
extern CString esBEMBasePath;    // SAC 10/28/22 (CUAC)
extern CString esProjectsPath;
extern CString esAltWeatherPath;	// SAC 6/3/20
extern CString esProgramFName;   // SAC 8/19/11
extern CString esProgramName;    // SAC 9/2/14
extern CString iniFileName;
extern CString esProgINIPathFile;
extern CString esDataINIPathFile;
extern CString esProxyINIPathFile;	// SAC 1/4/17
extern CString esCUIVersion;
extern CString esOverviewPDF;		// SAC 6/3/13
extern CString esUserManualPDF;	// SAC 7/8/13
extern CString esSecurityKey;		// SAC 1/10/17


/////////////////////////////////////////////////////////////////////////////
// .INI file reading functions

extern void    GetProgramPath();
extern BOOL		ResolvePathIndirections( CString& sPath );  // SAC 10/23/12

extern UINT    ReadProgInt(    LPCSTR section, LPCSTR entry, int def);
extern CString ReadProgString( LPCSTR section, LPCSTR entry, LPCSTR def, BOOL bGetPath=FALSE);
extern BOOL 	WriteProgInt(   LPCSTR section, LPCSTR entry, int value);
extern BOOL		WriteProgString(LPCSTR section, LPCSTR entry, LPCSTR string); 

extern void TransferProxyINISettings();	// transfer Proxy settings from Data INI file into Proxy-specific file (w/ encryption) - SAC 1/4/17
extern BOOL GetEncodedSetting( LPCSTR section, LPCSTR entry, CString& sOption );

int ParseCSVRecord( const char* pszParseStr, CStringArray& saCSVFields );		// SAC 10/16/20


/////////////////////////////////////////////////////////////////////////////
// Change Program Directory

extern void    ChangeProgDir( CString& mtrDir );
extern void    ChangeProgDir( LPCSTR section, LPCSTR entry );


/////////////////////////////////////////////////////////////////////////////
// Get program version ID

extern BOOL GetProgramVersion( CString& sProgVer, BOOL bPrependName=TRUE, BOOL bLongVer=TRUE );


/////////////////////////////////////////////////////////////////////////////
// String Resource Retrieval

LPTSTR GetStringResource( int id );


/////////////////////////////////////////////////////////////////////////////
// Check for file existence

extern BOOL FileExists( QString& qsFileName );
extern BOOL FileExists( const char* pszFileName );
extern BOOL DirectoryExists( const char* pszDirName );
extern void CreateAndChangeDirectory( const char* pszDirName, BOOL bRemoveDir = FALSE );
extern BOOL OKToWriteOrDeleteFile( const char* pszFileName, const char* pszUserMsg, bool bSilent=false );
extern bool AppendToTextFile(	const char* output, const char* psFileName, const char* psFileType, const char* psWriteAction,
										const char** ppCSVColumnLabels=NULL, bool bBlankFile=false, BOOL bSupressAllMessageBoxes=FALSE,
                              int iHeaderSubstID=0 );    // added iHeaderSubstID - SAC 01/30/23


/////////////////////////////////////////////////////////////////////////////
// Function(s) to initialize externals

//16 extern void RegisterControls();
extern void SetExternals( CWnd* pWnd );

extern BOOL LoadVersionInfoString( CString& sReturnString, const char* pszInfoID,
                                   const char* pszPre=NULL, const char* pszPost=NULL );


/////////////////////////////////////////////////////////////////////////////
// QT UI initialization

extern QApplication* sq_app;	// SAC 3/8/18
extern bool sbQtAppInited;
extern bool QAppInitialized();
extern void BlastQApp();


/////////////////////////////////////////////////////////////////////////////
// Numeric String Comma insertion and removal

//extern void  AddCommaToStringLong(  CString& string, long lNum );
//extern void  AddCommaToStringFloat( CString& string, float fNum, int nRtOfDec );

// SAC 1/7/01 - moved to BEMProc (BEMPX_StringToLong() & BEMPX_StringToFloat())
//extern long  RemoveCommasAndConvertToLong(  CString sLong );
//extern float RemoveCommasAndConvertToFloat( CString sFlt );


/////////////////////////////////////////////////////////////////////////////
// String Manipulation

extern void  RemoveIncompatibleFileNameCharacters( CString& sFileName );

extern bool CharacterNotAllowedInObjectname( char c );	// SAC 8/20/14 - routines to enable product-specific illegal object name characters
extern bool SetCharsNotAllowedInObjNamesToBEMProcUI();


/////////////////////////////////////////////////////////////////////////////
// Routines to facilitate migration to new open source compliance engine libraries

#include "..\BEMProc\BEMProc.h"

extern BOOL BEMPX_SetDataString(  long lDBID, CStringA& sStr, BOOL bAddCommas=TRUE, int iPrecision=0,
                                        int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                        const char* pszDefault=NULL, long lDBID2=0, int iBEMProcIdx=-1 );
 extern BOOL BEMPX_SetDataInteger( long lDBID, long& lData, long lDefault=0,
                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                         int iBEMProcIdx=-1 );
// extern BOOL BEMPX_SetDataFloat(   long lDBID, float& fData, float fDefault=0,
//                                         int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
//                                         int iBEMProcIdx=-1 );
extern int BEMPX_SetDataFloatArray( long lDBID, double* pfData, int iMaxValues, double fDefault=0,
                                        int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                        int iBEMProcIdx=-1 );
extern BOOL BEMPX_SetDataObject(  long lDBID, BEMObject*& pObj,
                                        int iDispDataType=-1, int iOccur=-1, int iObjType=BEMO_User,
                                        int iBEMProcIdx=-1 );

extern long BEMPX_GetDatabaseID(    const char* psDBCompParam, long iCompID=0, BOOL bTreatParentAsObject=FALSE,
																				int* piRefCompID=NULL, int* piNumRefComps=NULL );

// END OF - Routines to facilitate migration to new open source compliance engine libraries
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// BEMProc-related functions

extern BOOL CtrlDataIsNumber( int iDataType );

//extern void SetBDBDataString( long lDBID, int iPrecOrLen, CString& sStr, int iDispDataType=-1,
//                              int iOccur=-1, int iObjType=0 );

extern const char* GetDataStatusString(   long lDBID, int iDBInstance=-1 );
extern const char* GetCompDataTypeString( long lDBID );

//extern COLORREF GetCompDataTypeTextColor( long lDBID );
#define  NUM_RESERVED_TEXT_COLORS   1
#define  RANGEERROR_TEXT_COLOR_IDX  0
extern COLORREF GetCUITextColor( int iDS );
extern int      GetCUITextRGB(   int iDS, int idxRGB );		// SAC 3/23/18 - for grid text colors
extern QBrush*  BEMTextQBrush(   int iDS );		// SAC 3/23/18 - for grid text colors
extern void SetBDBWTextColors();

extern BOOL ObjectIsFromLibrary( long lDBID );

extern void DefaultProjectName( CString& sProjName );

/////////////////////////////////////////////////////////////////////////////
// Ruleset Switching/Loading stuff

extern char BASED_CODE eszWarning[];
extern char BASED_CODE eszRulesetSwitch[];
extern char BASED_CODE eszPostRulesetSwitch[];

extern BOOL LoadDataModel(	const char* psBEMProcFileName = NULL, int iBEMType = BEMT_Other,
									const char* psInitLogFileName = NULL, BOOL bMsgBox = TRUE );	// SAC 1/3/17

extern int eiNumRulesetsAvailable;

extern int RulesetFilenameToIndex( const char* pszRulesetFN );	// SAC 4/10/19
extern void UpdateRulesetMenu( CCmdUI* pCmdUI );
extern BOOL MenuRulesetSelectionAllowed( int idx, CString& sRuleSwitchDisallowedMsg );
extern BOOL MenuRulesetSelection( CWnd* pWnd, int idx, CString& sRulesetFileString );
extern BOOL LoadRuleset( const char* pszRulesetFileName=NULL, BOOL bDeleteAllObjects=TRUE );
extern void LoadRulesetListIfNotLoaded();
extern BOOL CodeYearRulesetAvailable( CString sCodeYear );

// Ruleset Report Generation stuff     - SAC 6/9/13
extern std::vector<std::string> saReportRulelistNames;
extern std::vector<std::string> saReportRulelistSelections;

// ruleset code year  - SAC 6/12/19
extern long elRulesetCodeYear;
extern void SetRulesetCodeYear();

/////////////////////////////////////////////////////////////////////////////
// Global Data and Routine to enable targeted rule evaluation logging when evaluating input/defaulting rules	- SAC 11/22/14
extern void* epInpRuleDebugInfo;
extern void LoadTargetedInputRuleDebugInfo();

extern void TweakString( char* lpBuf, int length );


/////////////////////////////////////////////////////////////////////////////
// Units Functions

//extern const char* GetUnitsString(  long lDBID );

/////////////////////////////////////////////////////////////////////////////

extern void InitBEMDBIDs();

#ifdef UI_CANRES
extern void AdjustDataModelForGeometryInpType();
#endif   // UI_CANRES

extern int eiBDBCID_Proj;
extern long elDBID_Proj_Ruleset;
extern long elDBID_Wiz_Ruleset;
extern int eiBDBCID_BEMVersion;			// SAC 9/17/12
extern long elDBID_Proj_BEMVersion;		// SAC 9/17/12
extern int eiBDBCID_INISettings;			// SAC 5/31/14
extern long elDBID_Proj_StdsVersion;	// SAC 8/15/14
extern long elDBID_Proj_DefaultOptionInp;		// SAC 4/11/18
extern long elDBID_Proj_DefaultOptionObj;
extern long elDBID_Proj_DefaultOptionDone;

extern long elDBID_Proj_AnalysisVersion;     // SAC 05/30/22
extern long elProjAnalysisVersion;  

// BEM Defaulting Options...
#define  DefaultOption_Nothing   0
#define  DefaultOption_Object    1
#define  DefaultOption_Family    2  // NYI
#define  DefaultOption_Model     3
extern long elDefaultOptionInp;
extern long elDefaultOptionObj;
extern long elDefaultOptionDone;
#define  DefaultAction_DataMod   	1
#define  DefaultAction_OpenDialog   2
#define  DefaultAction_CloseDialog  3
#define  DefaultAction_InitAnalysis	4

#ifdef UI_ASHRAE901E
extern int eiBDBCID_Run;
extern int eiBDBCID_Site;
extern int eiBDBCID_Bldg;
extern int eiBDBCID_Bshade;
extern int eiBDBCID_Block;
extern int eiBDBCID_Floor;
extern int eiBDBCID_Space;
extern int eiBDBCID_ActArea;
extern int eiBDBCID_LtSys;
extern int eiBDBCID_LtFix;
extern int eiBDBCID_ExtWall;
extern int eiBDBCID_ExtRoof;
extern int eiBDBCID_IntWall;
extern int eiBDBCID_IntCeil;
extern int eiBDBCID_UndWall;
extern int eiBDBCID_FlrWall;
extern int eiBDBCID_Win;
extern int eiBDBCID_Skylt;
extern int eiBDBCID_Door;
extern int eiBDBCID_Cons;
extern int eiBDBCID_Layers;
extern int eiBDBCID_Mat;
extern int eiBDBCID_HVACSys;
extern int eiBDBCID_Size;
extern int eiBDBCID_HtPump;
extern int eiBDBCID_AirCond;
extern int eiBDBCID_Furn;
extern int eiBDBCID_Econ;
extern int eiBDBCID_Plant;
extern int eiBDBCID_Fan;
extern int eiBDBCID_ClTower;
extern int eiBDBCID_Chiller;
extern int eiBDBCID_Boiler;
extern int eiBDBCID_Pump;
extern int eiBDBCID_Curve;
extern int eiBDBCID_Sched;
extern int eiBDBCID_WkSch;
extern int eiBDBCID_DaySch;
extern int eiBDBCID_ResSch;
extern int eiBDBCID_DResSch;
extern int eiBDBCID_Wizard;
extern int eiBDBCID_AreaWiz;
extern int eiBDBCID_HVACWiz;
extern int eiBDBCID_PlantWiz;  // SAC 5/26/00 - added

extern long elDBID_Proj_Name;
extern long elDBID_Proj_ArchTreeOption;
extern long elDBID_Proj_FinalResult;
extern long elDBID_Proj_RunDate;
extern long elDBID_Proj_RulesetName;
extern long elDBID_Proj_RulesetVersion;
extern long elDBID_Proj_SoftwareVersion;  // SAC 8/19/11 - changed var name

extern long elDBID_Site_WeatherFile;

extern long elDBID_Spc_HVACSystem;
extern long elDBID_Spc_Fan;          // SAC 6/30/00
extern long elDBID_Spc_ExhaustFan;   // SAC 6/30/00

extern long elDBID_FWall_Type;

extern long elDBID_LtSys_Fixture1;
extern long elDBID_LtSys_Fixture2;
extern long elDBID_LtSys_Fixture3;
extern long elDBID_LtSys_Fixture4;

extern long elDBID_Sys_HtPump;
extern long elDBID_Sys_AirCond;
extern long elDBID_Sys_Furnace;
extern long elDBID_Sys_AirEcon;
extern long elDBID_Sys_SupplyFan;
extern long elDBID_Sys_ReturnFan;

extern long elDBID_CTwr_TowerPump;

extern long elDBID_Chlr_CHWPump;
extern long elDBID_Chlr_CWPump;   // SAC 6/20/00 - added

extern long elDBID_Boil_HWPump;

extern long elDBID_Plant_CHWPump;
extern long elDBID_Plant_CWPump;
extern long elDBID_Plant_HPCircPump;
extern long elDBID_Plant_HWPump;

extern long elDBID_Wiz_ScreenIdx;
extern long elDBID_Wiz_ScreenID;
extern long elDBID_Wiz_PrevScreenID;
extern long elDBID_Wiz_NextScreenID;
extern long	elDBID_Wiz_FootprintWMF;
extern long	elDBID_Wiz_FPOrientXFrac;
extern long	elDBID_Wiz_FPOrientYFrac;
extern long	elDBID_Wiz_Orientation;
extern long	elDBID_Wiz_EnableFinishBtn;  // SAC 1/2/01
#endif   // UI_ASHRAE901E

#ifdef UI_CANRES
extern int eiBDBCID_Project;
extern int eiBDBCID_SchDay;
extern int eiBDBCID_ThrmlEngyStorModeSchDay;  // SAC 2/27/17
extern int eiBDBCID_SchWeek;
extern int eiBDBCID_Schedule;
extern int eiBDBCID_ConsAssm;
extern int eiBDBCID_Mat;
extern int eiBDBCID_FenCons;
extern int eiBDBCID_DrCons;
extern int eiBDBCID_SpcFuncDefaults;
extern int eiBDBCID_Lum;
extern int eiBDBCID_CrvLin;
extern int eiBDBCID_CrvQuad;
extern int eiBDBCID_CrvCubic;
extern int eiBDBCID_CrvDblQuad;
extern int eiBDBCID_EUseSummary;
extern int eiBDBCID_PVArray;
extern int eiBDBCID_PVArrayGeom;
extern int eiBDBCID_PVArrayShade;
extern int eiBDBCID_Battery;

extern int eiBDBCID_ResProj;     // SAC 10/20/21 (MFam)
extern int eiBDBCID_CUAC;        // SAC 07/26/22 (CUAC)
extern int eiBDBCID_Building;
extern int eiBDBCID_Story;
extern int eiBDBCID_Space;
extern int eiBDBCID_IntLtgSys;
extern int eiBDBCID_DayltgCtrl;
extern int eiBDBCID_Ceiling;
extern int eiBDBCID_CeilingBelowAttic;
extern int eiBDBCID_ExtFlr;
extern int eiBDBCID_ExtWall;
extern int eiBDBCID_FlrAboveCrawlSpc;
extern int eiBDBCID_IntFlr;
extern int eiBDBCID_IntWall;
extern int eiBDBCID_Roof;
extern int eiBDBCID_UndgrFlr;
extern int eiBDBCID_UndgrWall;
extern int eiBDBCID_Window;
extern int eiBDBCID_Skylight;
extern int eiBDBCID_Door;
extern int eiBDBCID_PolyLp;
extern int eiBDBCID_CartesianPt;
extern int eiBDBCID_ExtShdgObj;

extern int eiBDBCID_ThrmlZn;
extern int eiBDBCID_AirSys;
extern int eiBDBCID_VRFSys;		// SAC 8/14/15
extern int eiBDBCID_ZnSys;
extern int eiBDBCID_AirSeg;
extern int eiBDBCID_EvapClr;
extern int eiBDBCID_CoilClg;
extern int eiBDBCID_CoilHtg;
extern int eiBDBCID_Fan;
extern int eiBDBCID_TrmlUnit;
extern int eiBDBCID_OACtrl;
extern int eiBDBCID_FluidSys;
extern int eiBDBCID_FluidSeg;
extern int eiBDBCID_Chiller;
extern int eiBDBCID_Boiler;
extern int eiBDBCID_HtRej;
extern int eiBDBCID_Pump;
extern int eiBDBCID_RfrgEqp;
extern int eiBDBCID_HtRcvry;
extern int eiBDBCID_PrehtCoil;
extern int eiBDBCID_ThrmlEngyStor;
extern int eiBDBCID_HX;
extern int eiBDBCID_ResDHWSys;
extern int eiBDBCID_ResDWHRSys;	// SAC 1/24/19
extern int eiBDBCID_ResWtrHtr;
extern int eiBDBCID_ResLpTankHtr;		// SAC 1/12/20 (Com tic #3156)
extern int eiBDBCID_DHWSolarSys;		// SAC 1/31/20 (Com tic #3157)
extern int eiBDBCID_ResSpcDHWFeatures;	// SAC 1/23/19

extern int eiBDBCID_ProcLd;
extern int eiBDBCID_StorTank;
extern int eiBDBCID_WtrHtr;
//extern int eiBDBCID_BlrHtPump;			// SAC 10/23/20      // removed BlrHtPump... - SAC 05/14/21

extern long elDBID_Proj_Name;
extern long elDBID_Proj_RunDate;
extern long elDBID_Proj_SoftwareVersion;
extern long elDBID_Proj_WeatherPath;       
extern long elDBID_Proj_WeatherStation;    
extern long elDBID_Proj_DDWeatherFile;     
extern long elDBID_Proj_AnnualWeatherFile; 
extern long elDBID_Proj_ExcptDsgnModelFile; 

extern long elDBID_PolyLp_Area;			// SAC 5/29/14 
extern long elDBID_CartesianPt_Coord;	// SAC 5/29/14 

extern long elDBID_Spc_ResSpcDHWFeaturesRef;		// SAC 1/23/19

//extern long elDBID_ThermalZone_ThermalZoneCoolingSystem;                // "AirSystem",  
//extern long elDBID_ThermalZone_ThermalZoneSupplementalCoolingSystem;    // "AirSystem",  
//extern long elDBID_ThermalZone_ThermalZoneHeatingSystem;                // "AirSystem",  
//extern long elDBID_ThermalZone_ThermalZoneSupplementalHeatingSystem;    // "AirSystem",  
//extern long elDBID_ThermalZone_ThermalZoneVentilationSystem;            // "AirSystem",  
//extern long elDBID_ThermalZone_ThermalZoneExhaustSystem;                // "AirSystem",  
extern long elDBID_ThrmlZn_ClgSys;        // "AirSys", 
extern long elDBID_ThrmlZn_SuppClgSys;    // "AirSys", 
extern long elDBID_ThrmlZn_HtgSys;        // "AirSys", 
extern long elDBID_ThrmlZn_SuppHtgSys;    // "AirSys", 
extern long elDBID_ThrmlZn_VentSys;       // "AirSys", 
extern long elDBID_ThrmlZn_ExhSys;        // "AirSys", 

//extern long elDBID_AirSegment_AirSegmentMakeupAirSystem;                // "AirSystem",  
//extern long elDBID_AirSegment_AirSegmentMakeupThermalZone;              // "ThermalZone",
extern long elDBID_AirSeg_MakeupAirSys;       // "AirSys",        
extern long elDBID_AirSeg_MakeupThrmlZn;      // "ThrmlZn",       

extern long elDBID_CoilClg_FluidSegInRef;                         // "FluidSeg", 
extern long elDBID_CoilClg_FluidSegOutRef;                        // "FluidSeg", 

extern long elDBID_CoilHtg_FluidSegInRef;                         // "FluidSeg", 
extern long elDBID_CoilHtg_FluidSegOutRef;                        // "FluidSeg", 

//extern long elDBID_TerminalUnit_TerminalUnitZoneServed;                 // "ThermalZone", 
//extern long elDBID_TerminalUnit_TerminalUnitPrimaryFlowSegment;         // "AirSegment",  
//extern long elDBID_TerminalUnit_TerminalUnitHotDuctFlowSegment;         // "AirSegment",  
//extern long elDBID_TerminalUnit_TerminalUnitInducedAirZone;             // "ThermalZone", 
extern long elDBID_TrmlUnit_ZnServedRef;         // "ThrmlZn", 
extern long elDBID_TrmlUnit_PriFlowSegRef;       // "AirSeg",  
extern long elDBID_TrmlUnit_HotDuctFlowSegRef;   // "AirSeg",  
extern long elDBID_TrmlUnit_InducedAirZnRef;     // "ThrmlZn", 

//extern long elDBID_OAControl_OAControlReturnFlow;                       // "AirSegment",  
//extern long elDBID_OAControl_OAControlSupplyFlow;                       // "AirSegment",  
extern long elDBID_OACtrl_AirSegSupRef;      // "AirSeg",                 
extern long elDBID_OACtrl_AirSegRetRef;      // "AirSeg",                 

extern long elDBID_FluidSeg_PriSegRef;		  // "FluidSeg"
extern long elDBID_Chiller_CndsrInRef;      // "FluidSeg"
extern long elDBID_Chiller_CndsrOutRef;     // "FluidSeg"
extern long elDBID_Chiller_EvapInRef;       // "FluidSeg"
extern long elDBID_Chiller_EvapOutRef;      // "FluidSeg"
extern long elDBID_Boiler_FluidFlowInRef;   // "FluidSeg"
extern long elDBID_Boiler_FluidFlowOutRef;  // "FluidSeg"
//extern long elDBID_BlrHtPump_FluidSegInRef;     // "FluidSeg"	SAC 10/23/20
//extern long elDBID_BlrHtPump_FluidSegOutRef;    // "FluidSeg"

extern long elDBID_ResDHWSys_CentralSysType;	// SAC 1/31/20 (Com tic #3156)
extern long elDBID_ResDHWSys_DHWSolarSysRef;	// SAC 1/31/20 (Com tic #3157)
extern long elDBID_ResDHWSys_DHWHeater1;     // SAC 10/12/21 (MFam)
extern long elDBID_ResDHWSys_DHWHeater2;
extern long elDBID_ResDHWSys_DHWHeater3;
extern long elDBID_ResDHWSys_DHWHeater4;
extern long elDBID_ResDHWSys_DHWHeater5;
extern long elDBID_ResDHWSys_DHWHeater6;

extern long elDBID_INISettings_ProxyServerCredentials;		// SAC 1/9/17
extern long elDBID_INISettings_ShowProxyServerCredentials;	// SAC 1/9/17

extern int eiBDBCID_BatchRuns;
extern long elDBID_BatchRuns_BatchDefsCSV;        // BEMP_Str "CSV file containing definitions of all batch runs (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_BatchName;           // BEMP_Str "Name used as basis of log and results filenames" 
extern long elDBID_BatchRuns_ProjDirectory;       // BEMP_Str "Directory of projects to be batch processed (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_IncludeSubdirs;      // BEMP_Int "Flag indicating whether BatchDefsCSV file defined and exists" 
extern long elDBID_BatchRuns_ProjFileNames;       // BEMP_Str "Character string identifying projects to be processed (including wildcard '*')" 
extern long elDBID_BatchRuns_StoreProjToSepDir;   // BEMP_Int "Whether or not to store processed projects to separate directory" 
extern long elDBID_BatchRuns_OutputProjDir;       // BEMP_Str "Directory where processed projects will be placed (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_RunsSpanClimates;    // BEMP_Int "Whether or not to process each project across ALL 16 climate zones (appends 'CZ#' to output project filenames and run titles)" - SAC 1/4/19 
extern long elDBID_BatchRuns_RunSetFile;          // BEMP_Str "(relative path and) name of RunSet CSV file"     ; SAC 10/06/20
extern long elDBID_BatchRuns_RunSetFileStatus;    // BEMP_Int "status of RunSet file (0-blank, 1-not found, 2-invalid, 3-OK)"
extern long elDBID_BatchRuns_RunSetDescrip;       // BEMP_Str "Description of batch processing from RunSet file"

// integration of CBECC-Res into CBECC-Com - SAC 04/27/21
extern int eiBDBCID_ResZnGrp;       // SAC 08/11/21
extern int eiBDBCID_ResConsAssm;
extern int eiBDBCID_ResMat;
extern int eiBDBCID_ResWinType;
extern int eiBDBCID_ResZn;
extern int eiBDBCID_DwellUnitType;
extern int eiBDBCID_DwellUnit;
extern int eiBDBCID_ResOtherZn;
extern int eiBDBCID_ResAttic;
//extern int eiBDBCID_ResGarage;
extern int eiBDBCID_ResCrawlSpc;
extern int eiBDBCID_ResExtWall;
extern int eiBDBCID_ResIntWall;
extern int eiBDBCID_ResUndgrWall;
extern int eiBDBCID_ResCathedralCeiling;
extern int eiBDBCID_ResCeilingBelowAttic;
extern int eiBDBCID_ResIntCeiling;
extern int eiBDBCID_ResSlabFlr;
extern int eiBDBCID_ResExtFlr;
extern int eiBDBCID_ResFlrOverCrawlSpc;
extern int eiBDBCID_ResIntFlr;
extern int eiBDBCID_ResUndgrFlr;
extern int eiBDBCID_ResOpening;
extern int eiBDBCID_ResWin;
extern int eiBDBCID_ResSkylt;
extern int eiBDBCID_ResDr;
extern int eiBDBCID_ResHVACSys;     // SAC 11/02/21
extern int eiBDBCID_ResHtgSys;      // SAC 08/18/21
extern int eiBDBCID_ResClgSys;
extern int eiBDBCID_ResHtPumpSys;
extern int eiBDBCID_ResCentralHtgClgSys;  // SAC 12/31/21 (MFam)
extern int eiBDBCID_ResDistSys;
extern int eiBDBCID_ResDuctSeg;
extern int eiBDBCID_ResFanSys;
extern int eiBDBCID_ResIAQFan;
extern int eiBDBCID_ResCentralVentSys;    // SAC 12/31/21 (MFam)
extern int eiBDBCID_ResClVentFan;

#endif   // UI_CANRES

#ifdef UI_CARES
extern int eiBDBCID_RESNETBldg;		// SAC 9/27/20
extern int eiBDBCID_DwellUnitType;	// SAC 6/18/14
extern int eiBDBCID_DwellUnit;
extern int eiBDBCID_Zone;
extern int eiBDBCID_OtherZone;	// SAC 9/3/19 - MFamProto
extern int eiBDBCID_Garage;
extern int eiBDBCID_Attic;
extern int eiBDBCID_CrawlSpace;
extern int eiBDBCID_ExtWall;
extern int eiBDBCID_IntWall;
extern int eiBDBCID_UndWall;
extern int eiBDBCID_UndFloor;
//extern int eiBDBCID_AtticRoof;
extern int eiBDBCID_CathedralCeiling;
extern int eiBDBCID_CeilingBelowAttic;
extern int eiBDBCID_SlabFloor;
extern int eiBDBCID_ExteriorFloor;
extern int eiBDBCID_FloorOverCrawl;
extern int eiBDBCID_InteriorFloor;
extern int eiBDBCID_InteriorCeiling;
extern int eiBDBCID_Opening;	// SAC 7/30/20 - MFamProto
extern int eiBDBCID_Win;
extern int eiBDBCID_Skylt;
extern int eiBDBCID_Door;
extern int eiBDBCID_Cons;
extern int eiBDBCID_Mat;
extern int eiBDBCID_WindowType;  // SAC 8/27/13
extern int eiBDBCID_PVArrayGeom;
extern int eiBDBCID_Shade;
extern int eiBDBCID_PolyLp;
extern int eiBDBCID_CartesianPt;
extern int eiBDBCID_HVACSys;
extern int eiBDBCID_HVACHeat;
extern int eiBDBCID_HVACCool;
extern int eiBDBCID_HVACHtPump;
extern int eiBDBCID_HVACDist;
extern int eiBDBCID_HVACFan;
extern int eiBDBCID_IAQFan;
extern int eiBDBCID_ClVentFan;
extern int eiBDBCID_DHWSys;
extern int eiBDBCID_DHWSolarSys;		// SAC 1/12/20 (Res tic #1013)
extern int eiBDBCID_DWHRSys;	// SAC 12/23/18  // SAC 1/5/19 - renamed (was DWHX)
extern int eiBDBCID_DHWHeater;
extern int eiBDBCID_DHWLoopTankHeater;	// SAC 11/14/19
extern int eiBDBCID_SCSysRpt;
extern int eiBDBCID_DHWSysRpt;
extern int eiBDBCID_IAQVentRpt;
extern int eiBDBCID_EUseSummary;

extern long elDBID_Proj_Name;
extern long elDBID_Proj_RunDate;
extern long elDBID_Proj_SoftwareVersion;
extern long elDBID_Proj_SoftwareVersionDetail;	// SAC 2/13/20 (tic #1192)
extern long elDBID_Proj_AnalysisType;    // SAC 9/12/11
extern long elDBID_Proj_IsMultiFamily;   // SAC 7/29/16
extern long elDBID_Proj_RunTitle;    // SAC 1/8/12
extern long elDBID_Proj_ElecMETER;			// SAC 6/19/12
extern long elDBID_Proj_NatGasMETER;		// SAC 6/19/12
extern long elDBID_Proj_OtherFuelMETER;	// SAC 6/19/12
extern long elDBID_Proj_RHERSEnabled;		// SAC 9/28/20
//extern long elDBID_Site_WeatherFile;
	// SAC 12/9/13 - added several Zone properties to enhance tree display to confirm to E+A+A assignments
extern long elDBID_Zone_HVACSysStatus;			//	BEMP_Sym,   0,                            3008, "Status of HVAC System - New, Altered or Existing"                                      
extern long elDBID_Zone_HVACSysVerified;		// BEMP_Int,   0,                            3008, "existing HVAC System will be HERS verified"
extern long elDBID_Zone_HVACSystem;				// BEMP_Obj,   1, "HVACSys",  3, "Status",   3006, "New HVAC system assignment" 
extern long elDBID_Zone_AltHVACSystem;			// BEMP_Obj,   1, "HVACSys",  2, "Status",   3006, "Altered HVAC system assignment" 
extern long elDBID_Zone_exHVACSystem;			// BEMP_Obj,   1, "HVACSys",  1, "Status",   3006, "Existing HVAC system assignment" 
extern long elDBID_Zone_DHWSys1Status;			// BEMP_Sym,   0,                            3008, "Status of DHW System 1 - New, Altered or Existing"                                      
extern long elDBID_Zone_DHWSys1Verified;		// BEMP_Int,   0,                            3008, "existing DHW System 1 will be HERS verified"
extern long elDBID_Zone_DHWSys1;					// BEMP_Obj,   1, "DHWSys",  3, "Status",    1003, "DHW System 1 assignment" 
extern long elDBID_Zone_AltDHWSys1;				// BEMP_Obj,   1, "DHWSys",  2, "Status",    3006, "Altered DHW1 system assignment" 
extern long elDBID_Zone_exDHWSys1;				// BEMP_Obj,   1, "DHWSys",  1, "Status",    3006, "Existing DHW1 system assignment" 
extern long elDBID_Zone_DHWSys2Status;			// BEMP_Sym,   0,                            3008, "Status of DHW System 2 - New, Altered or Existing"                                      
extern long elDBID_Zone_DHWSys2Verified;		// BEMP_Int,   0,                            3008, "existing DHW System 2 conditions will be HERS verified"
extern long elDBID_Zone_DHWSys2;					// BEMP_Obj,   1, "DHWSys",  3, "Status",    1003, "DHW System 2 assignment" 
extern long elDBID_Zone_AltDHWSys2;				// BEMP_Obj,   1, "DHWSys",  2, "Status",    3006, "Altered DHW2 system assignment" 
extern long elDBID_Zone_exDHWSys2;				// BEMP_Obj,   1, "DHWSys",  1, "Status",    3006, "Existing DHW2 system assignment" 
//extern long elDBID_SURFACE_sfType;
extern long elDBID_Attic_Construction;
extern long elDBID_ExtWall_Construction;
extern long elDBID_IntWall_Construction;
extern long elDBID_UndWall_Construction;
//extern long elDBID_AtticRoof_Construction;
extern long elDBID_CathedralCeiling_Construction;
extern long elDBID_CeilingBelowAttic_Construction;
extern long elDBID_ExteriorFloor_Construction;
extern long elDBID_FloorOverCrawl_Construction;
extern long elDBID_InteriorFloor_Construction;
extern long elDBID_InteriorCeiling_Construction;
extern long elDBID_PVArrayGeom_IsBldgAttached;     // BEMP_Int  - SAC 3/2/17
extern long elDBID_Shade_Type;            // BEMP_Sym ->  0:"- select type -"  1:"Site Shade"  2:"Building Shade"   - SAC 2/21/17
extern long elDBID_PolyLp_Area;			   // SAC 2/24/17
extern long elDBID_CartesianPt_Coord;     // BEMP_Flt,  3,  0,  1, "ft",  "X, Y, Z coordinates of polyloop vertex"   - SAC 2/21/17
extern long elDBID_Cons_Materials1;
extern long elDBID_Cons_Materials2;
extern long elDBID_Cons_Materials3;
extern long elDBID_Cons_Materials4;
extern long elDBID_Cons_Materials5;
extern long elDBID_Cons_Materials6;
extern long elDBID_Cons_Materials7;
extern long elDBID_Cons_Materials8;
extern long elDBID_Cons_Materials9;
extern long elDBID_Cons_Materials10;
extern long elDBID_HVAC_HeatSystem1; 
extern long elDBID_HVAC_HeatSystem2; 
extern long elDBID_HVAC_HeatSystem3; 
extern long elDBID_HVAC_HeatSystem4; 
extern long elDBID_HVAC_HeatSystem5; 
extern long elDBID_HVAC_HeatSystem6; 
extern long elDBID_HVAC_HeatSystem7; 
extern long elDBID_HVAC_HeatSystem8; 
extern long elDBID_HVAC_HeatSystem9; 
extern long elDBID_HVAC_HeatSystem10;
extern long elDBID_HVAC_CoolSystem1; 
extern long elDBID_HVAC_CoolSystem2; 
extern long elDBID_HVAC_CoolSystem3; 
extern long elDBID_HVAC_CoolSystem4; 
extern long elDBID_HVAC_CoolSystem5; 
extern long elDBID_HVAC_CoolSystem6; 
extern long elDBID_HVAC_CoolSystem7; 
extern long elDBID_HVAC_CoolSystem8; 
extern long elDBID_HVAC_CoolSystem9; 
extern long elDBID_HVAC_CoolSystem10;
extern long elDBID_HVAC_HtPumpSystem1; 
extern long elDBID_HVAC_HtPumpSystem2; 
extern long elDBID_HVAC_HtPumpSystem3; 
extern long elDBID_HVAC_HtPumpSystem4; 
extern long elDBID_HVAC_HtPumpSystem5; 
extern long elDBID_HVAC_HtPumpSystem6; 
extern long elDBID_HVAC_HtPumpSystem7; 
extern long elDBID_HVAC_HtPumpSystem8; 
extern long elDBID_HVAC_HtPumpSystem9; 
extern long elDBID_HVAC_HtPumpSystem10;
extern long elDBID_HVAC_DistribSystem;
extern long elDBID_HVAC_Fan;
extern long elDBID_HVACHeat_CHWHeater;
extern long elDBID_DHWSys_DHWSolarSysRef;	// SAC 1/12/20 (Res tic #1013)
extern long elDBID_DHWSys_DHWHeater1;
extern long elDBID_DHWSys_DHWHeater2;
extern long elDBID_DHWSys_DHWHeater3;
extern long elDBID_DHWSys_DHWHeater4;
extern long elDBID_DHWSys_DHWHeater5;
extern long elDBID_DHWSys_DHWHeater6;
extern long elDBID_DHWSys_LoopHeater;	// SAC 11/19/19
extern long elDBID_DHWSys_CentralDHWType;	// SAC 1/21/20
extern long elDBID_INISettings_ProxyServerCredentials;		// SAC 1/9/17
extern long elDBID_INISettings_ShowProxyServerCredentials;	// SAC 1/9/17

extern int eiBDBCID_BatchRuns;
extern long elDBID_BatchRuns_BatchDefsCSV;        // BEMP_Str "CSV file containing definitions of all batch runs (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_BatchName;           // BEMP_Str "Name used as basis of log and results filenames" 
extern long elDBID_BatchRuns_ProjDirectory;       // BEMP_Str "Directory of projects to be batch processed (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_IncludeSubdirs;      // BEMP_Int "Flag indicating whether BatchDefsCSV file defined and exists" 
extern long elDBID_BatchRuns_ProjFileNames;       // BEMP_Str "Character string identifying projects to be processed (including wildcard '*')" 
extern long elDBID_BatchRuns_StoreProjToSepDir;   // BEMP_Int "Whether or not to store processed projects to separate directory" 
extern long elDBID_BatchRuns_OutputProjDir;       // BEMP_Str "Directory where processed projects will be placed (complete path or relative to Projects folder)" 
extern long elDBID_BatchRuns_RunsSpanClimates;    // BEMP_Int "Whether or not to process each project across ALL 16 climate zones (appends 'CZ#' to output project filenames and run titles)" - SAC 1/4/19 
extern long elDBID_BatchRuns_RunSetFile;          // BEMP_Str "(relative path and) name of RunSet CSV file"     ; SAC 10/21/20
extern long elDBID_BatchRuns_RunSetFileStatus;    // BEMP_Int "status of RunSet file (0-blank, 1-not found, 2-invalid, 3-OK)"
extern long elDBID_BatchRuns_RunSetDescrip;       // BEMP_Str "Description of batch processing from RunSet file"
#endif   // UI_CARES

extern BOOL GetDialogTabDimensions( int iBDBClass, int& iTabCtrlWd, int& iTabCtrlHt );   // SAC 8/29/11 - enable class-specific dialog tab dimensions

extern void GetDialogCaption( int iBDBClass, CString& sDialogCaption );  // SAC 1/8/13 - enable application-specific dialog captions

extern void GetObjectConversionInfo( int iBEMClassFrom, int iBEMClassTo, int& iDlgID, int& iDlgWd, int& iDlgHt, CString& sNewNameAppend, 
													long& lNewObjAssignDBID, long& lNewConsAssmAssignDBID, CString& sDlgCaption, CStringArray& saFromProps, CStringArray& saToProps );  // SAC 10/14/15

/////////////////////////////////////////////////////////////////////////////

#endif
