// BEMProc.H - Public API exported from 'BEMProc.DLL' and describing
//              all the building database classes.
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

#ifndef __BEMPROPERTY_H__
#define __BEMPROPERTY_H__

#include "BEMProcAPI.h"
//#include <string>
//#include <vector>
//#include <ctype.h>

//using std::vector;
//using std::string;

//namespace BEMProc {

/////////////////////////////////////////////////////////////////////////////
//	BEMProperty
//    An instance of this class is created for each property (variable) which
//    is used to describe each building component contained in the database.
/////////////////////////////////////////////////////////////////////////////

// m_iSpecialValue values
#define  SV_Default  1
#define  SV_None     2

class BEMPROC_API BEMProperty
{
public:
	BEMProperty( BEMPropertyType* pType = NULL, int i0Arr = 0 )
								{	m_type = pType;
									m_dataStatus = 0;
									m_specialValue = 0;
									m_1ArrayIdx = i0Arr+1;
									m_strValue.clear();
									m_obj = NULL;			};
	~BEMProperty();
	
// Attributes
private:
	BEMPropertyType*	m_type;         // pointer to the CBEMPropertyType which defines what this property is
   int   				m_dataStatus;   // this flag defines where the value which is currently set in the property
                                      // came from, using the enums BEM_PropertyStatus defined above
   int             m_specialValue; // flag used to pass simulation special values like defaults and "NONE"
//   int   				iCritDefIdx;   // 1-based index of the critical default comment that the user has entered
   int             m_1ArrayIdx;    // 1-Based index of this Prop in the array which are created by this PropType

	QString		m_strValue;		    // BEMP_Str:  string data
	union
	{
		long	     m_intValue;	    // BEMP_Int, BEMP_Sym:  integer or symbolic value
		double     m_dblValue;	    // BEMP_Flt:  float value
		BEMObject* m_obj;	          // >= 0:  pointer to object assigned to this property
	};

// Operations
public:
	BEMPropertyType* getType()		{	return m_type;			}
	void		setType( BEMPropertyType* pType )	{	m_type = pType;	}

	int		getDataStatus()					{	return m_dataStatus;		}
	void		setDataStatus( int iStatus )	{	m_dataStatus = iStatus;	}

	QString	getString()					{	return m_strValue;	}
	void		setString( QString& s )	{	m_strValue = s;		}
	void		clearString()				{	m_strValue.clear();	}

	long		getInt()					{	return m_intValue;	}
	void		setInt( int i )		{	m_intValue = i;		}

	double	getDouble()					{	return m_dblValue;	}
	void		setDouble( double d )	{	m_dblValue = d;		}

	BEMObject* getObj()				{	return m_obj;			}
	void		setObj( BEMObject* pObj )		{	m_obj = pObj;	}

	int		getSpecialValue()					{	return m_specialValue;		}
	void		setSpecialValue( int iSVal )	{	m_specialValue = iSVal;		}

	int		get1ArrayIdx()						{	return m_1ArrayIdx;		}
	void		set1ArrayIdx( int i1Arr )		{	m_1ArrayIdx = i1Arr;		}

   bool CopyProperty(    BEMProperty* pProp, int iBEMProcIdx=-1, bool bForceNonUniqueCompAssignments=FALSE,
									bool bCopyPrimaryDefaultDataAsUserDefined=false );		// SAC 6/8/15 - CBECC issue 1061
   bool CopyPropertyAcrossModels( BEMProperty* pProp, int iBEMProcIdx=-1 );
//   bool ArchiveProperty( BEMProperty* pProp, bool bRestore=FALSE, int iBEMProcIdx=-1 ); 
   bool Default( long lDBID, int iOccur=-1, BEM_ObjType eObjType=BEMO_User, BOOL bReinitializing=FALSE, int iBEMProcIdx=-1 );
   void ReinitResetData(      long lDBID, int iOccur=-1, BOOL bResetUserDefinedData=TRUE ); 
   void ReinitLocalResetData( std::vector<long>& laResetDBIDs, long lDBID, int iOccur=-1, BOOL bResetUserDefinedData=TRUE ); 
   bool CopyAssignedObject( BOOL bLibToUser=FALSE, int iBEMProcIdx=-1, int iImportUniqueRuleLibObjOption=2, 
										const char* pszImportRuleLibParentName=NULL );
//   bool Identical( CBEMProperty* pProp, const char* pszSymObjStr=NULL ); 
};


//}	// BMEProc

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMPROPERTY_H__
