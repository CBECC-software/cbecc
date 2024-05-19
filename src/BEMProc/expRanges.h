// ranges.h - header file for BEMRangeCheck class definition
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

#ifndef __RANGES_H__
#define __RANGES_H__

#include "expCrypFile.h"  
#include "expTextIO.h"


#define  RANGE_ERROR    1
#define  RANGE_WARNING  2
#define  RANGE_MESSAGE  3


/////////////////////////////////////////////////////////////////////////////
//	BEMRangeCheck
//    An instance of this class is created for each range check definition
//    contained in the selected compliance ruleset.
/////////////////////////////////////////////////////////////////////////////

class BEMRangeCheck
{
public:
   BEMRangeCheck()		{	}
   BEMRangeCheck( long lDBID, int iCondition, int iSeverity,
   						const char* pszValueOrParam, const char* pszMessage = NULL );
   BEMRangeCheck( long lDBID, int iCondition, double dValue, long lRtDBID,
						int iSeverity, QString& sMessage, long lCaseDBID, int iCaseCondition,
						double dCaseValue, long lCaseRtDBID )
							{	m_dbid = lDBID;
								m_condition = iCondition;
								m_value = dValue;
								m_rtDBID = lRtDBID;
								m_severity = iSeverity;
								m_message = sMessage;
								m_caseDBID = lCaseDBID;
								m_caseCondition = iCaseCondition;
								m_caseValue = dCaseValue;
								m_caseRtDBID = lCaseRtDBID; 		return;  }
   ~BEMRangeCheck()	{	}

// Attributes
private:
   long    m_dbid;      // database ID of the parameter this range check is to be performed on
   int     m_condition; // condition enum (BEM_Condition) as defined in BEMProc.h
   double  m_value;     // min or max value that database value is compared with
   long    m_rtDBID;    // database ID of a parameter this range check references
                        //  (or 0 if the range check references a fixed m_fValue)

   int     m_severity;  // severity of this check (see RANGE_* defines above)
   QString m_message;   // message displayed on screen &/or written to log file upon check failure

   // SAC 4/13/98 - Added to have this range check evaluated only under certain conditions
   long    m_caseDBID;      // database ID of the case parameter to be checked prior to performing this range check
   int     m_caseCondition; // condition enum (BEM_Condition) as defined in BEMProc.h for this case
   double  m_caseValue;     // min or max value that case database value is compared with
   long    m_caseRtDBID;    // database ID of a parameter this range check case references
                            //  (or 0 if the range check case references a fixed m_fCaseValue)

public:
	int		getArrayIndex()		{	return BEMPX_GetArrayID(m_dbid);  }
	int		getSeverity()			{	return m_severity;  }
	QString	getMessage()			{	return m_message;  }

	long		getDBID()				{	return m_dbid;  }
	int		getCondition()			{	return m_condition;  }
	double	getValue()				{	return m_value;  }
	long		getRtDBID()				{	return m_rtDBID;  }

	long		getCaseDBID()			{	return m_caseDBID;  }
	int		getCaseCondition()	{	return m_caseCondition;  }
	double	getCaseValue()			{	return m_caseValue;  }
	long		getCaseRtDBID()		{	return m_caseRtDBID;  }

	void copy( BEMRangeCheck* pRC );

   bool Read( BEMTextIO& file, QFile& errorFile );
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


//	/////////////////////////////////////////////////////////////////////////////
//	//	BEMPropertyRangesList
//	//    An instance of this class is created for each list of range check
//	//    definitions.  For now, there is only one such list for each ruleset.
//	/////////////////////////////////////////////////////////////////////////////
//	
//	class BEMPropertyRangesList : public CObList
//	{
//	public: 
//	   ~BEMPropertyRangesList();
//	   void RemoveAll();
//	
//	   void InitRangesList();
//	   void AddRanges( BEMRangeCheck* dataType );
//	   void InitRangesList( CString& sFileName );
//	   bool ReadText( CString sFileName, CFile& errorFile );
//	   bool Read( CCryptoFile& file ); 
//	
//	   bool Write( CCryptoFile& file );
//	
//		void postRangeChecksToDatabase();  // SAC 7/2/12
//	};


/////////////////////////////////////////////////////////////////////////////

#endif // __RANGES_H__
