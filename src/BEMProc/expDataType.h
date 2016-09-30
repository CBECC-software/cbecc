// datatype.h - header file for CDataType and CDataTypeList class definitions
//
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

#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include "expCrypFile.h"  
#include "expTextIO.h"

extern int StringToDataTypeEnum( QString& sType );

/////////////////////////////////////////////////////////////////////////////
//	BEMPropertyDataType
//    An instance of this class is created for each data type assignment
//    which is defined for the selected compliance ruleset
/////////////////////////////////////////////////////////////////////////////

class BEMPropertyDataType
{
public:
   enum { Compulsory, Required, CondRequired, Optional, Default,
          CriticalDef, Prescribed, NotInput, NDataTypes };
   enum { NotInp_AllowUIReset, NotInp_IgnoreUserInput, NotInp_ErrorIfInput, NotInp_Num };		// SAC 8/13/15
public:
   BEMPropertyDataType()		{	}
	BEMPropertyDataType( long lDBID, int eCompDataType = 3, bool bPrimary = FALSE, bool bEditable = TRUE, bool bUserDefault = TRUE,
				  bool bDisplayInput = TRUE, bool bDisplayProposed = TRUE, bool bDisplayBudget = TRUE,
				  int iNotInputMode = NotInp_AllowUIReset, const char* pszNotInputMsg = NULL )
				  						{	m_dbid            = lDBID           ;   
											m_compDataType    = eCompDataType   ;     // 3 => BEMD_Optional
											m_primary         = bPrimary        ;   
											m_editable        = bEditable       ;   
											m_userDefault     = bUserDefault    ;   
											m_displayInput    = bDisplayInput   ;   
											m_displayProposed = bDisplayProposed;   
											m_displayBudget   = bDisplayBudget  ;   
											m_notInputMode    = iNotInputMode;		// SAC 8/12/15
											m_notInputMsg     = pszNotInputMsg;		}
   ~BEMPropertyDataType()		{	}

   long m_dbid;             // DBID of parameter this instance describes
   int  m_compDataType;     // compliance data type (see enum just above)
   bool m_primary;          // TRUE if this is a Primary variable, else FALSE
   bool m_editable;         // TRUE if this variable is editable by the user
   bool m_userDefault;      // TRUE if the user-defined defaults are allowed for this variable
   bool m_displayInput;     // TRUE if this variable may be displayed when in the user input interface mode
   bool m_displayProposed;  // TRUE if this variable may be displayed when in the propsed design interface mode
   bool m_displayBudget;    // TRUE if this variable may be displayed when in the budget design interface mode
   int  m_notInputMode;		// SAC 8/12/15 - 0-AllowUIReset, 1-IgnoreUserInput or 2-ErrorIfInput
   QString m_notInputMsg;		// SAC 8/12/15

public:
   bool Read( BEMTextIO& file, QFile& errorFile );
   void Read( CryptoFile& file );
   void Write( CryptoFile& file );
   bool GetNextBool( BEMTextIO& file );

	long		getDBID()								{	return m_dbid;		}
//	void		setDBID( long lDBID )				{	m_dbid = lDBID;	}
};


//	/////////////////////////////////////////////////////////////////////////////
//	//	BEMPropertyDataTypeList
//	//    An instance of this class is created for each list of data type
//	//    assignments defined.  For now, there is only one such list for each
//	//    compliance ruleset.
//	/////////////////////////////////////////////////////////////////////////////
//	
//	class BEMPropertyDataTypeList : public CObList
//	{
//	public: 
//	   ~BEMPropertyDataTypeList();
//	   void RemoveAll();
//	
//	   void InitDataTypeList();
//	   void AddDataType( BEMPropertyDataType* dataType );
//	   void InitDataTypeList( QString& sFileName );
//	   bool ReadText( QString sFileName, CFile& errorFile );
//	   bool Read( CryptoFile& file ); 
//	   bool Read( QString& fileName );
//	
//	   bool Write( CryptoFile& file );
//	   BEMPropertyDataType* GetDataType( long lDBID );  // SAC 9/17/14
//	};


/////////////////////////////////////////////////////////////////////////////

#endif // __DATATYPE_H__
