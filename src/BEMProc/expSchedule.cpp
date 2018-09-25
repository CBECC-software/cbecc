// expSchedule.cpp - 
//
/**********************************************************************
 *  Copyright (c) 2018, California Energy Commission
 *  Copyright (c) 2018, SAC Software Solutions, LLC
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
#include "expRuleList.h"
#include "BEMProcI.h"
#include "BEMProc.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"
#include "BEMProcObject.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//		;------------------------------------------------------------------------------------------------
//		;                LName              Template             MD  MR  AC   Parent1    P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14 P15  MC  MS  bP  CF  SR  IN     HI 
//		;               --------------------------------------------------------------------------------------------------------------------------------------------------------------
//		0,  "SchDay",   "ScheduleDay",     "Sch Day <i>",         0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  1,  0,  0,  0,   3000
//		;
//		;                              VType     NV  WA  SP    US    UL                 UT  NO  OC            CV  CP      HI    LName                 
//		;                             ------------------------------------------------------------------------------------------
//		1,           "Type",           BEMP_Sym,  1,  0,  1,  Comp,  "",                 0,  0,                           3004, "Type",  "" 
//		1,           "Hr",             BEMP_Flt, 24,  1,  1,  Comp,  "",                 0,  0,                           3004, "Hour",  ""   
//		;------------------------------------------------------------------------------------------------
class BEMSchDay
{
public:
	bool		bValid;
	QString	sName;
	QString	sDupObjName;
	double	daVals[24];

public:
	BEMSchDay()
			{  bValid = false;
			};
	bool init( long lDBID_SchHrVal, int i0SchDayObjIdx=-1 )
			{	int iGetRV = BEMPX_GetFloatArray( lDBID_SchHrVal, daVals, 24 /*iMaxValues*/, 0.0 /*dDefault*/, BEMP_Flt, i0SchDayObjIdx );  //, int iObjType=BEMO_User, int iBEMProcIdx=-1 );
				bValid = (iGetRV==24);
				return bValid;
			};
	void zero()
			{	bValid = true;
				for (int hr=0; hr<24; hr++)
					daVals[hr] = 0.0;
			};

	void applyMin( double dMin )
			{	for (int hr=0; hr<24; hr++)
					daVals[hr] = std::max( daVals[hr], dMin );
			};
	void applyMax( double dMax )
			{	for (int hr=0; hr<24; hr++)
					daVals[hr] = std::min( daVals[hr], dMax );
			};

	bool identical( BEMSchDay* pDay )
			{	bool bMatch=true;
				for (int hr=0; (bMatch && hr<24); hr++)
					bMatch = (daVals[hr] == pDay->daVals[hr]);
				if (bMatch)
					sDupObjName = pDay->sName;
				return bMatch;
			};

	bool createBEMObject( int iSchDayClass, long lDBID_SchDay_Type, long lDBID_SchDay_Hr, QString sType )
			{	int iObjIdx = -1;
				BEMObject* pObj = BEMPX_CreateObject( iSchDayClass, sName.toLocal8Bit().constData() );  //, BEMObject* pParent = NULL, BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE, ...
				if (pObj && pObj->getClass())
				{	iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
					if (iObjIdx >= 0)
					{	BEMPX_SetBEMData( lDBID_SchDay_Type, BEMP_QStr, (void*) &sType, BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
						for (int hr=0; hr<24; hr++)
							BEMPX_SetBEMData( lDBID_SchDay_Hr+hr, BEMP_Flt, &daVals[hr], BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
				}	}
				return (iObjIdx >= 0);
			};
};


//		;------------------------------------------------------------------------------------------------
//		;                LName              Template             MD  MR  AC   Parent1    P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14 P15  MC  MS  bP  CF  SR  IN     HI 
//		;               --------------------------------------------------------------------------------------------------------------------------------------------------------------
//		0,  "SchWeek",  "ScheduleWeek",    "Sch Week <i>",        0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  1,  0,  0,  0,   3000
//		;
//		;                                VType     NV  WA  SP    US    UL                 UT  NO  OC            CV  CP               HI    LName                 
//		;                               ---------------------------------------------------------------------------------------------------------
//		1,           "Type",             BEMP_Sym,  1,  0,  1,  Comp,  "",                 0,  0,                                    3004, "Type",     "" 
//		1,           "SchDaySunRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDaySundayReference",  "" 
//		1,           "SchDayMonRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayMondayReference",  "" 
//		1,           "SchDayTueRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayTuesdayReference",  "" 
//		1,           "SchDayWedRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayWednesdayReference",  "" 
//		1,           "SchDayThuRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayThursdayReference",  "" 
//		1,           "SchDayFriRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayFridayReference",  "" 
//		1,           "SchDaySatRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDaySaturdayReference",  "" 
//		1,           "SchDayHolRef",     BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayHolidayReference",  "" 
//		1,           "SchDayClgDDRef",   BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayCoolingDesignDayReference",  "" 
//		1,           "SchDayHtgDDRef",   BEMP_Obj,  1,  0,  1,   Opt,  "",                 0,  2, "SchDay", -99, "Type",  "ThrmlEngyStorModeSchDay", -99, "Type",    3004, "ScheduleDayHeatingDesignDayReference",  "" 
//		;------------------------------------------------------------------------------------------------
class BEMSchWeek
{
public:
	bool			bValid;
	QString		sName;
	QString		sDupObjName;
	BEMSchDay	days[10];

public:
	BEMSchWeek()
			{  bValid = false;
			};
	bool init( long lDBID_SchDaySunRef, long lDBID_SchHrVal, int i0SchWeekObjIdx=-1 )
			{	bValid = true;
				int iStatus, iSpecialVal, iError;
				for (int i=0; (bValid && i<10); i++)
				{	BEMObject* pSchDayObj = BEMPX_GetObjectAndStatus( lDBID_SchDaySunRef + (i * BEM_PARAM_MULT), iStatus, iSpecialVal, iError, i0SchWeekObjIdx );  //, (BEM_ObjType) iObjType, iBEMProcIdx );
					if (pSchDayObj==NULL || iStatus <= 0)
					{	bValid = false;			assert( false );
					}
					else
					{	int iSchDayObjIdx = BEMPX_GetObjectIndex( pSchDayObj->getClass(), pSchDayObj );  //, int iBEMProcIdx=-1 );
						if (iSchDayObjIdx < 0)
						{	bValid = false;			assert( false );
						}
						else
						{	bValid = days[i].init( lDBID_SchHrVal, iSchDayObjIdx );
							assert( bValid );
						}
				}	}
				return bValid;
			};
	void zero()
			{	bValid = true;
				for (int da=0; da<10; da++)
					days[da].zero();
			};

	bool sumIntoMultVal( BEMSchWeek* pSrcWk, double dMult )
			{	bool bRetVal = true;
				for (int iDa=0; (bRetVal && iDa < 10); iDa++)
				{	for (int hr=0; (bRetVal && hr < 24); hr++)
						days[iDa].daVals[hr] += (pSrcWk->days[iDa].daVals[hr] * dMult);
				}
				return bRetVal;
			};

	bool sumIntoMultSch( BEMSchWeek* pSrcWk, BEMSchWeek* pMultWk )
			{	bool bRetVal = true;
				for (int iDa=0; (bRetVal && iDa < 10); iDa++)
				{	for (int hr=0; (bRetVal && hr < 24); hr++)
						days[iDa].daVals[hr] += (pSrcWk->days[iDa].daVals[hr] * pMultWk->days[iDa].daVals[hr]);
				}
				return bRetVal;
			};

	bool identical( BEMSchWeek* pWk )
			{	bool bMatch=true;
				for (int da=0; (bMatch && da<10); da++)
					bMatch = days[da].identical( &pWk->days[da] );
				if (bMatch)
					sDupObjName = pWk->sName;
				return bMatch;
			};

	bool createBEMObject( int iSchWeekClass, long lDBID_SchWeek_Type, long lDBID_SchWeek_SchDaySunRef, QString sType )
			{	int iObjIdx = -1;
				BEMObject* pObj = BEMPX_CreateObject( iSchWeekClass, sName.toLocal8Bit().constData() );  //, BEMObject* pParent = NULL, BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE, ...
				if (pObj && pObj->getClass())
				{	iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
					if (iObjIdx >= 0)
					{	BEMPX_SetBEMData( lDBID_SchWeek_Type, BEMP_QStr, (void*) &sType, BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
						for (int da=0; da<10; da++)
						{	assert( ( days[da].sName.isEmpty() && !days[da].sDupObjName.isEmpty()) ||
									  (!days[da].sName.isEmpty() &&  days[da].sDupObjName.isEmpty()) );
							QString sDaySchName = (days[da].sName.isEmpty() ? days[da].sDupObjName : days[da].sName);		assert( !sDaySchName.isEmpty() );
							if (!sDaySchName.isEmpty())
								BEMPX_SetBEMData( lDBID_SchWeek_SchDaySunRef + (da * BEM_PARAM_MULT), BEMP_QStr, &sDaySchName, BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
				}	}	}
				return (iObjIdx >= 0);
			};
};


//		;------------------------------------------------------------------------------------------------
//		;                LName              Template             MD  MR  AC   Parent1    P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14 P15  MC  MS  bP  CF  SR  IN     HI 
//		;               --------------------------------------------------------------------------------------------------------------------------------------------------------------
//		0,  "Sch",      "Schedule",        "Sched <i>",           0,  0,  0, "Project",  "", "", "", "", "", "", "", "", "", "", "", "", "", "",  -1,  1,  1,  0,  0,  0,   3000
//		;
//		;                              VType     NV  WA  SP    US    UL                 UT  NO  OC            CV  CP                  HI    LName               
//		;                             ------------------------------------------------------------------------------------------------------------
//		1,           "Type",           BEMP_Sym,  1,  0,  1,  Comp,  "",                 0,  0,                                      3004, "Type",     "" 
//		1,           "EndMonth",       BEMP_Int, 53,  1,  1,   Req,  "",                 0,  0,                                      3004, "EndMonth",  ""   
//		1,           "EndDay",         BEMP_Int, 53,  1,  1,   Req,  "",                 0,  0,                                      3004, "EndDay",  "" 
//		1,           "SchWeekRef",     BEMP_Obj, 53,  1,  1,  Comp,  "",                 0,  1, "SchWeek",  -99, "Type",             3004, "ScheduleWeekReference",  "" 
//		
//		1,           "DischrgSchRef",  BEMP_Obj,  1,  0,  1,  NInp,  "",                 0,  1, "Sch",  2, "Type",        3008, "DischargeScheduleReference",  ""   ; ruleset-generated for TES Mode scheduling
//		1,           "ChrgSchRef",     BEMP_Obj,  1,  0,  1,  NInp,  "",                 0,  1, "Sch",  2, "Type",        3008, "ChargeScheduleReference",  ""   
//		1,           "ChlrOnlySchRef", BEMP_Obj,  1,  0,  1,  NInp,  "",                 0,  1, "Sch",  2, "Type",        3008, "ChillerOnlyScheduleReference",  ""   
//		;------------------------------------------------------------------------------------------------
class BEMSch
{
public:
	bool		bValid;
	QString  sName;
	QString  sType;
	int		iNumWeeks;
	long		lEndMonth[53];
	long		lEndDay[53];
	std::vector<BEMSchWeek> weeks;

public:
	BEMSch()
			{  bValid = false;
				iNumWeeks = 0;
			};
	bool init( QString name, int i0SchObjIdx=-1 )
			{	bValid = true;
				sName = name;
				iNumWeeks = 0;
				long lDBID_Sch_Type    = BEMPX_GetDatabaseID( "Sch:Type" );						assert( lDBID_Sch_Type    > 0 );
				long lDBID_Sch_EndMo   = BEMPX_GetDatabaseID( "Sch:EndMonth" );				assert( lDBID_Sch_EndMo   > 0 );
				long lDBID_Sch_EndDa   = BEMPX_GetDatabaseID( "Sch:EndDay" );					assert( lDBID_Sch_EndDa   > 0 );
				long lDBID_Sch_SchWk   = BEMPX_GetDatabaseID( "Sch:SchWeekRef" );				assert( lDBID_Sch_SchWk   > 0 );
				long lDBID_SchWeek_Sun = BEMPX_GetDatabaseID( "SchWeek:SchDaySunRef" );		assert( lDBID_SchWeek_Sun > 0 );
				long lDBID_SchDay_Hr   = BEMPX_GetDatabaseID( "SchDay:Hr" );					assert( lDBID_SchDay_Hr   > 0 );
				int iStatus, iSpecialVal, iError;
				if (lDBID_Sch_Type < 1 || lDBID_Sch_EndMo < 1 || lDBID_Sch_EndDa < 1 || lDBID_Sch_SchWk < 1 ||
					 lDBID_SchWeek_Sun < 1 || lDBID_SchDay_Hr < 1)
					bValid = false;
				else
				{	sType = BEMPX_GetString( lDBID_Sch_Type, iSpecialVal, iError, i0SchObjIdx );  //BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1,
					bool bWkValid = false;
					do
					{	long lEndMo = BEMPX_GetInteger( lDBID_Sch_EndMo + iNumWeeks, iSpecialVal, iError, i0SchObjIdx );  // BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
						long lEndDa = BEMPX_GetInteger( lDBID_Sch_EndDa + iNumWeeks, iSpecialVal, iError, i0SchObjIdx );  // BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
						BEMObject* pSchWkObj = BEMPX_GetObjectAndStatus( lDBID_Sch_SchWk + iNumWeeks, iStatus, iSpecialVal, iError, i0SchObjIdx );  //, (BEM_ObjType) iObjType, iBEMProcIdx );
						int iSchWkObjIdx = (pSchWkObj==NULL ? -1 : BEMPX_GetObjectIndex( pSchWkObj->getClass(), pSchWkObj ));  //, int iBEMProcIdx=-1 );
						bWkValid = (lEndMo > 0 && lEndMo <= 12 && lEndDa > 0 && lEndDa <= 31 && iSchWkObjIdx >= 0);
											assert( !bWkValid || iNumWeeks == 0 || (lEndMo > lEndMonth[iNumWeeks-1] || (lEndMo == lEndMonth[iNumWeeks-1] && lEndDa > lEndDay[iNumWeeks-1])) );
						if (bWkValid)
						{	BEMSchWeek wk;
							if (!wk.init( lDBID_SchWeek_Sun, lDBID_SchDay_Hr, iSchWkObjIdx ))
								bWkValid = false;
							else
							{	lEndMonth[iNumWeeks] = lEndMo;
								lEndDay[  iNumWeeks] = lEndDa;
								weeks.push_back(wk);
								iNumWeeks++;
						}	}
					} while (iNumWeeks < 53 && bWkValid);
				}
				if (bValid)
					bValid = (iNumWeeks > 0);
				return bValid;
			};

	bool setNextEndMoDa( int iLastEndMo, int iLastEndDa, int& iEndMo, int& iEndDa )
			{	assert( bValid );
				bool bDone=false;
				for (int iWk=0; (!bDone && iWk<iNumWeeks); iWk++)
				{	if ((lEndMonth[iWk] > iLastEndMo || (lEndMonth[iWk] == iLastEndMo && lEndDay[iWk] > iLastEndDa)) &&
						 (lEndMonth[iWk] < iEndMo     || (lEndMonth[iWk] == iEndMo     && lEndDay[iWk] < iEndDa    )))
					{	iEndMo = lEndMonth[iWk];
						iEndDa = lEndDay[iWk];
						bDone = true;
				}	}
				return bDone;
			};

	void incNumWeeks()	{	iNumWeeks++;  };

	BEMSchWeek* getWeekPtr( long lEndMo, long lEndDa )
			{	BEMSchWeek* pWk=NULL;
				for (int iWk=0; (pWk==NULL && iWk < iNumWeeks); iWk++)
				{	if ( (iWk==0 || (lEndMo > lEndMonth[iWk-1] || (lEndMo == lEndMonth[iWk-1] && lEndDa > lEndDay[iWk-1]))) &&
						  (lEndMo < lEndMonth[iWk] || (lEndMo == lEndMonth[iWk] && lEndDa <= lEndDay[iWk])) )
						pWk = &weeks[iWk];
				}
				return pWk;
			};

	bool createBEMObject()
			{	QString sSchClass = "Sch", sSchWeekClass = "SchWeek", sSchDayClass = "SchDay";
				int iSchClass     = BEMP_GetDBComponentID( sSchClass );			assert( iSchClass > 0 );
				int iSchWeekClass = BEMP_GetDBComponentID( sSchWeekClass );		assert( iSchWeekClass > 0 );
				int iSchDayClass  = BEMP_GetDBComponentID( sSchDayClass  );		assert( iSchDayClass > 0 );

				int iWk, iDa;
				bool bOK=true;
				long lDBID_SchDay_Type = BEMPX_GetDatabaseID( "Type", iSchDayClass );					assert( lDBID_SchDay_Type > 0 );
				long lDBID_SchDay_Hr   = BEMPX_GetDatabaseID( "Hr",   iSchDayClass );					assert( lDBID_SchDay_Hr > 0 );
				for (iWk=0; (bOK && iWk < iNumWeeks); iWk++)
				{	for (iDa=0; (bOK && iDa < 10); iDa++)
					{	if (!weeks[iWk].days[iDa].sName.isEmpty())
							bOK = weeks[iWk].days[iDa].createBEMObject( iSchDayClass, lDBID_SchDay_Type, lDBID_SchDay_Hr, sType );
				}	}

				long lDBID_SchWeek_Type         = BEMPX_GetDatabaseID( "Type",         iSchWeekClass );					assert( lDBID_SchWeek_Type > 0 );
				long lDBID_SchWeek_SchDaySunRef = BEMPX_GetDatabaseID( "SchDaySunRef", iSchWeekClass );					assert( lDBID_SchWeek_SchDaySunRef > 0 );
				for (iWk=0; (bOK && iWk < iNumWeeks); iWk++)
				{	if (!weeks[iWk].sName.isEmpty())
						bOK = weeks[iWk].createBEMObject( iSchWeekClass, lDBID_SchWeek_Type, lDBID_SchWeek_SchDaySunRef, sType );
				}

				int iObjIdx = -1;
				if (bOK)
				{	long lDBID_Sch_Type    = BEMPX_GetDatabaseID( "Type",       iSchClass );		assert( lDBID_Sch_Type  > 0 );
					long lDBID_Sch_EndMo   = BEMPX_GetDatabaseID( "EndMonth",   iSchClass );		assert( lDBID_Sch_EndMo > 0 );
					long lDBID_Sch_EndDa   = BEMPX_GetDatabaseID( "EndDay",     iSchClass );		assert( lDBID_Sch_EndDa > 0 );
					long lDBID_Sch_SchWk   = BEMPX_GetDatabaseID( "SchWeekRef", iSchClass );		assert( lDBID_Sch_SchWk > 0 );
					BEMObject* pObj = BEMPX_CreateObject( iSchClass, sName.toLocal8Bit().constData() );  //, BEMObject* pParent = NULL, BEM_ObjType objType = BEMO_User, bool bDefaultParent = TRUE, ...
					if (pObj && pObj->getClass())
					{	iObjIdx = BEMPX_GetObjectIndex( pObj->getClass(), pObj );
						if (iObjIdx >= 0)
						{	BEMPX_SetBEMData( lDBID_Sch_Type, BEMP_QStr, (void*) &sType, BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
							for (iWk=0; (bOK && iWk < iNumWeeks); iWk++)
							{	assert( ( weeks[iWk].sName.isEmpty() && !weeks[iWk].sDupObjName.isEmpty()) ||
										  (!weeks[iWk].sName.isEmpty() &&  weeks[iWk].sDupObjName.isEmpty()) );
								QString sWkSchName = (weeks[iWk].sName.isEmpty() ? weeks[iWk].sDupObjName : weeks[iWk].sName);		assert( !sWkSchName.isEmpty() );
								if (!sWkSchName.isEmpty())
								{	BEMPX_SetBEMData( lDBID_Sch_EndMo + iWk, BEMP_Int,  &lEndMonth[iWk], BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
									BEMPX_SetBEMData( lDBID_Sch_EndDa + iWk, BEMP_Int,  &lEndDay[  iWk], BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
									BEMPX_SetBEMData( lDBID_Sch_SchWk + iWk, BEMP_QStr, &sWkSchName    , BEMO_User, iObjIdx );  // , BEM_PropertyStatus eStatus=BEMS_UserDefined, BEM_ObjType eObjType=BEMO_User, BOOL bPerformResets=TRUE, int iBEMProcIdx=-1, ...
				}	}	}	}	}
				return (iObjIdx >= 0);
			};
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


QString ScheduleSum( int iNumScheds, QString sSchNamePrefix, ExpNode** pNodeList, void* pEvalData, ExpError* pError )
{	QString sNewSchedName, sErr;
   ExpEvalStruct* pEval = (ExpEvalStruct*) pEvalData;

	std::vector<BEMSch> scheds;
	bool baMultIsMult[] = {  true, true, true, true, true,   true, true, true, true, true };
	double daMults[]    = {   1.0,  1.0,  1.0,  1.0,  1.0,    1.0,  1.0,  1.0,  1.0,  1.0 };
	bool bHaveMin = false;   double dSchMin = 0.0;
	bool bHaveMax = false;   double dSchMax = 0.0;
	BEMSch saMultSchs[10];
	QString sSchClass = "Sch";
	int iSchClass = BEMP_GetDBComponentID( sSchClass );		assert( iSchClass > 0 );
	if (iSchClass < 1)
		sErr = QString( "ScheduleSum() Error:  Schedule class '%1' not found in ruleset data model." ).arg( sSchClass );
// debugging
//QString sLogMsg = QString( "ScheduleSum():  %1 scheds, name prefix '%2'" ).arg( QString::number(iNumScheds), sSchNamePrefix );		BEMPX_WriteLogFile( sLogMsg );

	int iSch, iErr, iWk;
	for (iSch=0; (sErr.isEmpty() && iSch < iNumScheds); iSch++)
	{	QString sSchName;
		if (pNodeList[iSch]->type != EXP_String)
			sErr = QString( "Invalid ScheduleSum() function argument #%1: expecting reference to schedule to be summed." ).arg( QString::number(iSch+3) );
		else
		{	sSchName = (char*) pNodeList[iSch]->pValue;
			BEMObject* pSchObj = BEMPX_GetObjectByNameQ( iSchClass, iErr, sSchName );  // , BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1, BOOL bNameIsPrefix=FALSE );
			int iSchObjIdx = (pSchObj==NULL ? -1 : BEMPX_GetObjectIndex( pSchObj->getClass(), pSchObj ));  // , int iBEMProcIdx=-1 );
			if (iSchObjIdx < 0)
				sErr = QString( "ScheduleSum() Error:  Schedule '%1' to be summed (argument #%2) not found." ).arg( sSchName, QString::number(iSch+3) );
			else
			{	BEMSch sch;
				if (!sch.init( sSchName, iSchObjIdx ))
					sErr = QString( "ScheduleSum() error encountered loading schedule '%1' to be summed (argument #%2)." ).arg( sSchName, QString::number(iSch+3) );
				else
					scheds.push_back( sch );
	}	}	}

	for (iSch=0; (sErr.isEmpty() && iSch < iNumScheds); iSch++)
	{	int iMultArgIdx = iNumScheds + iSch;
		if (pNodeList[iMultArgIdx])
		{	if (pNodeList[iMultArgIdx]->type == EXP_Value)
				daMults[iSch] = pNodeList[iMultArgIdx]->fValue;
			else if (pNodeList[iMultArgIdx]->type != EXP_String)
				sErr = QString( "Invalid ScheduleSum() function argument #%1: expecting schedule multiplier in the form of a numeric value or schedule." ).arg( QString::number(iMultArgIdx+3) );
			else
			{	QString sMultSchName = (char*) pNodeList[iMultArgIdx]->pValue;
				BEMObject* pMultSchObj = BEMPX_GetObjectByNameQ( iSchClass, iErr, sMultSchName );  // , BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1, BOOL bNameIsPrefix=FALSE );
				int iMultSchObjIdx = (pMultSchObj==NULL ? -1 : BEMPX_GetObjectIndex( pMultSchObj->getClass(), pMultSchObj ));  // , int iBEMProcIdx=-1 );
				if (iMultSchObjIdx < 0)
					sErr = QString( "ScheduleSum() Error:  Multiplier schedule '%1' (argument #%2) not found." ).arg( sMultSchName, QString::number(iMultArgIdx+3) );
				else
				{	if (!saMultSchs[iSch].init( sMultSchName, iMultSchObjIdx ))
						sErr = QString( "ScheduleSum() error encountered loading schedule '%1', used as a multiplier on schedule #%2 '%3' (argument #%4)." ).arg(
																								sMultSchName, QString::number(iSch+3), scheds[iSch].sName, QString::number(iMultArgIdx+3) );
					else
						baMultIsMult[iSch] = false;
	}	}	}	}

	int iSchMinMaxArgIdx = iNumScheds*2;
	if (sErr.isEmpty() && pNodeList[iSchMinMaxArgIdx])
	{	if (pNodeList[iSchMinMaxArgIdx]->type == EXP_Value)
		{	bHaveMin = true;
			dSchMin = pNodeList[iSchMinMaxArgIdx]->fValue;
		}
		else
			sErr = QString( "Invalid ScheduleSum() function argument #%1: expecting resulting schedule minimum in the form of a numeric value." ).arg( QString::number(iSchMinMaxArgIdx+3) );
	}
	iSchMinMaxArgIdx++;
	if (sErr.isEmpty() && pNodeList[iSchMinMaxArgIdx])
	{	if (pNodeList[iSchMinMaxArgIdx]->type == EXP_Value)
		{	bHaveMax = true;
			dSchMax = pNodeList[iSchMinMaxArgIdx]->fValue;
		}
		else
			sErr = QString( "Invalid ScheduleSum() function argument #%1: expecting resulting schedule maximum in the form of a numeric value." ).arg( QString::number(iSchMinMaxArgIdx+3) );
	}
	if (bHaveMin && bHaveMax && dSchMin > dSchMax)
		sErr = QString( "Invalid ScheduleSum() function arguments %1-%2: schedule minimum (%3) must be <= maximum (%4)." ).arg( QString::number(iSchMinMaxArgIdx+2), QString::number(iSchMinMaxArgIdx+3), QString::number(dSchMin), QString::number(dSchMax) );

	if (sErr.isEmpty())
	{	BEMSch sumSch;
		sumSch.bValid = true;
		sumSch.sType = scheds[0].sType;
		int iLastEndMo=0, iLastEndDa=0, iEndMo=99, iEndDa=99;
		bool bYrEnd=false;
		do
		{	iEndMo = iEndDa = 99;
			if (sumSch.iNumWeeks > 0)
			{	iLastEndMo = sumSch.lEndMonth[sumSch.iNumWeeks-1];
				iLastEndDa = sumSch.lEndDay[  sumSch.iNumWeeks-1];
			}
			for (iSch=0; (sErr.isEmpty() && iSch < iNumScheds); iSch++)
			{	scheds[iSch].setNextEndMoDa( iLastEndMo, iLastEndDa, iEndMo, iEndDa );
				if (!baMultIsMult[iSch])
					saMultSchs[iSch].setNextEndMoDa( iLastEndMo, iLastEndDa, iEndMo, iEndDa );  // need to check both summing & multiplier schedules
			}
			if (sumSch.iNumWeeks < 1 || (sumSch.lEndMonth[sumSch.iNumWeeks-1]  < iEndMo ||
			                            (sumSch.lEndMonth[sumSch.iNumWeeks-1] == iEndMo && sumSch.lEndDay[sumSch.iNumWeeks-1] < iEndDa)))
			{	sumSch.lEndMonth[sumSch.iNumWeeks] = iEndMo;
				sumSch.lEndDay[  sumSch.iNumWeeks] = iEndDa;
				sumSch.incNumWeeks();
				bYrEnd = (iEndMo==12 && iEndDa==31);
				if (!bYrEnd && sumSch.iNumWeeks == 53)
					sErr = QString( "ScheduleSum() error: summed schedule requries too many weeks." );
			}
			else
			{	assert( false );
			}
		} while (!bYrEnd && sErr.isEmpty());

	// perform week summing
		for (iWk=0; (sErr.isEmpty() && iWk < sumSch.iNumWeeks); iWk++)
		{	BEMSchWeek sumWk;
			sumWk.zero();
			for (iSch=0; (sErr.isEmpty() && iSch < iNumScheds); iSch++)
			{	BEMSchWeek* pSrcWk = scheds[iSch].getWeekPtr( sumSch.lEndMonth[iWk], sumSch.lEndDay[iWk] );					assert( pSrcWk );
				if (pSrcWk && baMultIsMult[iSch])
					sumWk.sumIntoMultVal( pSrcWk, daMults[iSch] );
				else if (pSrcWk && !baMultIsMult[iSch] && saMultSchs[iSch].bValid)
				{	BEMSchWeek* pMultWk = saMultSchs[iSch].getWeekPtr( sumSch.lEndMonth[iWk], sumSch.lEndDay[iWk] );		assert( pMultWk );
					if (pMultWk)
						sumWk.sumIntoMultSch( pSrcWk, pMultWk );
					else
					{	sumWk.bValid = false;		assert( false );
				}	}
				else
				{	sumWk.bValid = false;		assert( false );
			}	}
			if (sumWk.bValid)
				sumSch.weeks.push_back( sumWk );
			else
			{	sumSch.bValid = false;
				sErr = QString( "ScheduleSum() error encountered summing week schedule %1 of %2." ).arg( QString::number(iWk+1), QString::number(sumSch.iNumWeeks) );
		}	}

	// apply sched min and/or max - SAC 8/27/18
		if (sumSch.bValid && (bHaveMin || bHaveMax))
		{	for (int iWk=0; (sErr.isEmpty() && iWk < sumSch.iNumWeeks); iWk++)
				for (int iDa=0; (sErr.isEmpty() && iDa < 10); iDa++)
				{	if (bHaveMin)
						sumSch.weeks[iWk].days[iDa].applyMin( dSchMin );
					if (bHaveMax)
						sumSch.weeks[iWk].days[iDa].applyMax( dSchMax );
		}		}

	// create and store new Sch/SchWeek(s)/SchDays
		if (sumSch.bValid)
		{	// first identify the name of the annual sched object
			if (sSchNamePrefix.isEmpty())
				sNewSchedName = "Summed Sched";
			else
				sNewSchedName = sSchNamePrefix;
			BEMPX_GetDefaultComponentName( iSchClass, sNewSchedName );  //, int iBEMProcIdx=-1, int iFirstIndex=-1, ...
			sumSch.sName = sNewSchedName;
// debugging
//sLogMsg = QString( "Storing summed schedule '%1'" ).arg( sNewSchedName );		BEMPX_WriteLogFile( sLogMsg );

			QString sSchWeekClass = "SchWeek", sSchDayClass = "SchDay";
			int iSchWeekClass = BEMP_GetDBComponentID( sSchWeekClass );		assert( iSchWeekClass > 0 );
			int iSchDayClass  = BEMP_GetDBComponentID( sSchDayClass  );		assert( iSchDayClass > 0 );

			// then loop over all weeks & days identifying and naming only those that are unique
			QString sWkName;	int iWk2, iDa, iDa2, iNumUniqueWks=0, iNumUniqueDays=0;
			for (iWk=0; (sErr.isEmpty() && iWk < sumSch.iNumWeeks); iWk++)
			{	bool bIsDup=false;
				for (iWk2=0; (!bIsDup && sErr.isEmpty() && iWk2 < iWk); iWk2++)
					bIsDup = (!sumSch.weeks[iWk2].sName.isEmpty() && sumSch.weeks[iWk].identical( &sumSch.weeks[iWk2] ));
				if (!bIsDup)
				{	iNumUniqueWks++;
					QString sThisWkName = QString( "%1-wk%2" ).arg( sNewSchedName, QString::number(iNumUniqueWks) );
					BEMPX_GetDefaultComponentName( iSchWeekClass, sThisWkName );  //, int iBEMProcIdx=-1, int iFirstIndex=-1, ...
					sumSch.weeks[iWk].sName = sThisWkName;

					for (iDa=0; (sErr.isEmpty() && iDa < 10); iDa++)
					{	bIsDup=false;
						for (iDa2=0; (!bIsDup && sErr.isEmpty() && iDa2 < iDa); iDa2++)
							bIsDup = (!sumSch.weeks[iWk].days[iDa2].sName.isEmpty() && sumSch.weeks[iWk].days[iDa].identical( &sumSch.weeks[iWk].days[iDa2] ));
						for (iWk2=0; (!bIsDup && sErr.isEmpty() && iWk2 < iWk); iWk2++)
						{	for (iDa2=0; (!bIsDup && sErr.isEmpty() && iDa2 < 10); iDa2++)
								bIsDup = (!sumSch.weeks[iWk2].days[iDa2].sName.isEmpty() && sumSch.weeks[iWk].days[iDa].identical( &sumSch.weeks[iWk2].days[iDa2] ));
						}
						if (!bIsDup)
						{	iNumUniqueDays++;
							QString sThisDaName = QString( "%1-da%2" ).arg( sNewSchedName, QString::number(iNumUniqueDays) );
							BEMPX_GetDefaultComponentName( iSchDayClass, sThisDaName );  //, int iBEMProcIdx=-1, int iFirstIndex=-1, ...
							sumSch.weeks[iWk].days[iDa].sName = sThisDaName;
					}	}
			}	}
			// we have now identified & named all unique week & day schedules
			// next create all new Sch objects
			sumSch.createBEMObject();
	}	}

	if (!sErr.isEmpty())
		ExpSetError( pError, EXP_RuleProc, sErr.toLocal8Bit().constData() );

	return sNewSchedName;
}









