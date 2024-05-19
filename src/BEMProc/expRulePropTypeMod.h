// RulePropTypeMod.h - header file for BEMPropTypeMod and BEMPropTypeModList class definitions
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

#ifndef __RulePropTypeMod_H__
#define __RulePropTypeMod_H__

#include "expCrypfile.h"  
#include "expTextIO.h"


/////////////////////////////////////////////////////////////////////////////
//	BEMPropTypeMod
//    An instance of this class is created for each entry property needing
//    adjustments based on ruleset source.
/////////////////////////////////////////////////////////////////////////////

class BEMPropTypeMod
{
public:
   BEMPropTypeMod( long lDBID=0, int iReportPrecision=-9, const char* pszPrevName=NULL )
									{	m_dbid				= lDBID;
										m_reportPrecision	= iReportPrecision;	// -9 = default/unused, 3 for 0.xxx, 2 for 0.xx, 1 for 0.x, 0 for x, -1 for x0, -2 for x00, -3 for x000, etc.
										if (pszPrevName && strlen( pszPrevName ) > 0)	// SAC 8/12/15
											m_previousNames.push_back( pszPrevName );		}
   ~BEMPropTypeMod()			{		}

	long	m_dbid;					// database ID of the property that will be modified
	int	m_reportPrecision;	// SAC 2/4/15 - property to facilitate rounding of numeric results for compliance reporting - rounding only for output of non-User models written to analysis results XML file
   									//					-9 = default/unused, 3 for 0.xxx, 2 for 0.xx, 1 for 0.x, 0 for x, -1 for x0, -2 for x00, -3 for x000, etc.
	QStringList	m_previousNames;	// SAC 8/12/15 - to facilitate data model backward compatibility by tracking re-named properties

public:
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
};


//	/////////////////////////////////////////////////////////////////////////////
//	//	BEMPropTypeModList
//	//    An instance of this class is created for each list of BEMPropTypeMod
//	//    assignments defined.  For now, there is only one such list for each
//	//    compliance ruleset.
//	/////////////////////////////////////////////////////////////////////////////
//	
//	class BEMPropTypeModList : public CObList
//	{
//	public: 
//	   ~BEMPropTypeModList();
//	   void RemoveAll();
//	
//	   bool Read( CCryptoFile& file ); 
//	   bool Write( CCryptoFile& file );
//	};


/////////////////////////////////////////////////////////////////////////////

#endif // __RulePropTypeMod_H__
