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

#ifndef __BEMSYMBOLS_H__
#define __BEMSYMBOLS_H__

#include "BEMProc.h"



/////////////////////////////////////////////////////////////////////////////
//	BEMSymbol
//    An instance of this structure is created for each individual symbol.
//    All instances are stored in a single long array, with all the various
//    symbol lists pointing into the array at the entries which describe them.
/////////////////////////////////////////////////////////////////////////////

class BEMPROC_API BEMSymbol
{
public:
// Constructors
	BEMSymbol()							{	m_value  = 0;
												m_string = "";		};
	BEMSymbol( BEMSymbol* pSym )	{	if (pSym)
												{	m_value  = pSym->m_value;
													m_string = pSym->m_string;
												}  };
	BEMSymbol( long val, QString str )	{	m_value  = val;
														m_string = str;  };
	~BEMSymbol()	{	};

private:
// Attributes
	long 		m_value;   // numeric value associated with the symbol - must be unique within each symbol list   - SAC 10/22/12 - int->long
	QString	m_string;  // the symbol's identifying character string - should also be unique within each symbol list

public:
// Operations
	long				getValue()		{	return m_value;	};
	const QString	getString()		{	return m_string;	};
};


/////////////////////////////////////////////////////////////////////////////
//	BEMSymDependencySet
//    One or more instances of this class is created for each CBEMSymbolList.
//    The symbols associated with each instance are not stored within this
//    class.  Instead, this class contains an index and number of entries
//    which identify which symbols in the single global symbol array
//    correspond to this set of symbols.
/////////////////////////////////////////////////////////////////////////////

#define  MAX_DEP_DBIDS_PER_SYMBOL_LIST  3

class BEMPROC_API BEMSymDependencySet
{
public:
// Constructors
	BEMSymDependencySet();
	~BEMSymDependencySet();
   void Init( long iDefaultValue, // int iCompID,
	           LPCSTR lpszDepVar1=NULL, double dDepVal1=-1,
	           LPCSTR lpszDepVar2=NULL, double dDepVal2=-1,
	           LPCSTR lpszDepVar3=NULL, double dDepVal3=-1 );
   void Init( long iDefaultValue, long lDepVar1, double dDepVal1,
                                  long lDepVar2, double dDepVal2,
	                               long lDepVar3, double dDepVal3 );

private:
// Attributes             // FIRST Component/Parameter dependency
   long   m_compParam[ MAX_DEP_DBIDS_PER_SYMBOL_LIST ];   // Identifier of component type (Class) AND parameter (PropertyType)
   long   m_comp[      MAX_DEP_DBIDS_PER_SYMBOL_LIST ];   // Identifier of component type (Class)
   long   m_dataType[  MAX_DEP_DBIDS_PER_SYMBOL_LIST ];   // Type of data which describes the above component/parameter
   double m_depValue[  MAX_DEP_DBIDS_PER_SYMBOL_LIST ];   // Dependent value

   long   m_defaultValue;    // Numeric value corresponding to the default symbol

   std::vector<BEMSymbol>  m_symbols;		// was:  CArray<CBEMSymbol*, CBEMSymbol*>  m_symbols;

public:
// Operations
	int	getNumSymbols()							{	return (int) m_symbols.size();	}
	std::vector<BEMSymbol>*	getSymbolArray()	{	return &m_symbols;				}
	BEMSymbol*			getSymbol( int idx )		{	return &m_symbols.at(idx);		}

	long	getDefaultValue()		{	return m_defaultValue;  }

   bool PassesDepChecks(    long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx=-1 );
   bool HasArrayDependency( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx=-1 );
   long     GetSymbolValue(  const char* pSymStr );
   QString  GetSymbolString( long iSymVal );
	BEMSymbol*  CreateBEMSymbol( long iSymValue, LPCSTR lpszSymString );

   long   getCompParam( int i )		{	if (i < 0 || i >= MAX_DEP_DBIDS_PER_SYMBOL_LIST)		// Identifier of component type (Class) AND parameter (PropertyType)
   												{	assert( false );
   													return -1;
   												}
   												return m_compParam[ i ];
   											}
   long   getComp( int i )				{	if (i < 0 || i >= MAX_DEP_DBIDS_PER_SYMBOL_LIST)		// Identifier of component type (Class)
   												{	assert( false );
   													return -1;
   												}
   												return m_comp[ i ];
   											}
   long   getDataType( int i )		{	if (i < 0 || i >= MAX_DEP_DBIDS_PER_SYMBOL_LIST)		// Type of data which describes the above component/parameter
   												{	assert( false );
   													return -1;
   												}
   												return m_dataType[ i ];
   											}
   double getDepValue( int i )		{	if (i < 0 || i >= MAX_DEP_DBIDS_PER_SYMBOL_LIST)   	// Dependent value
   												{	assert( false );
   													return -99999;
   												}
   												return m_depValue[ i ];
   											}

   BOOL Copy( BEMSymDependencySet* pSymDepSet );
};


/////////////////////////////////////////////////////////////////////////////
//	BEMSymbolList
//    An instance of this structure is created for each list of symbols.
//    Each list of symbols contains all possible values for a single
//    PropertyType.
//    Each BEMSymbolList is made up of one or more sub-symbol lists, which
//    allow us to vary the possible symbol selections for the corresponding
//    PropertyType based on other current database values.  For example, 
//    the available symbol selections that define the PropertyType ClimateZone
//    is dependent on which compliance ruleset is defined -> there is one
//    list of symbols for the CEC ruleset, and other symbol lists for other
//    compatible rulesets.
/////////////////////////////////////////////////////////////////////////////

class BEMSymbolList
{
public:
// Constructors
	BEMSymbolList()		{	};
	~BEMSymbolList()		{	clear();		};

	void Init( int iSource=BEMS_ProgDefault )		{	clear();
																	m_source = iSource;	};

private:
// Attributes
   int      m_source;       // this flag is set to a BEM_PropertyStatus value such as BEMS_ProgDefault or BEMS_RuleDefault
                            // and indentifies what module defined the symbol list (and symbol default)
   std::vector<BEMSymDependencySet>  m_depSets;		// Array of CBEMSymDependencySet - only one in most cases => a single symbol list no matter
																	// what other database variables are set to.  Multiple list entries are defined when the
																	// symbol list options depend on other database values.
																	// was:  CArray<CBEMSymDependencySet*, CBEMSymDependencySet*>  m_oaDepSets;
public:
// Operations
   void clear()		{	m_depSets.resize(0);
   							m_source = BEMS_ProgDefault;	};
	//BEMSymDependencySet* CreateBEMSymDepSet( long iDefaultIndex,
   //                                        LPCSTR lpszDepVar1=NULL, float fDepVal1=-1,
   //                                        LPCSTR lpszDepVar2=NULL, float fDepVal2=-1,
   //                                        LPCSTR lpszDepVar3=NULL, float fDepVal3=-1 ); 

	int	getSource()		{	return m_source;  }

	int	getNumSymDependencySets()									{	return (int) m_depSets.size();	}
	BEMSymDependencySet* addSymDependencySet( long iDefaultValue,
															long lDepVar1, double dDepVal1,
				                                 long lDepVar2, double dDepVal2,
															long lDepVar3, double dDepVal3  )
									{	BEMSymDependencySet sds;
										sds.Init( iDefaultValue, lDepVar1, dDepVal1, lDepVar2, dDepVal2, lDepVar3, dDepVal3 );
										m_depSets.push_back(sds);
										return &(m_depSets.back());  }
	BEMSymDependencySet* getSymDependencySet( int idx )		{	return &m_depSets.at(idx);			}

   BEMSymDependencySet* GetSymbolDepSet( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx=-1,
                                         int* pIdx=NULL ); 
   bool  SymbolDepSetArrayDependent( long lDBID, int iOccur, BEM_ObjType eObjType, int iBEMProcIdx=-1 );
   long  GetSymbolValue( long lDBID, int iOccur, BEM_ObjType eObjType, const char* pSymStr,
                         BOOL bOnlyFromCurrentSymDepSet=FALSE, int iBEMProcIdx=-1 );
   QString GetSymbolString( long lDBID, int iOccur, BEM_ObjType eObjType, long iSymVal, int iBEMProcIdx=-1,
                            BOOL bOnlyFromCurrentSymDepSet=TRUE );

   BOOL Copy( BEMSymbolList* pSymList );
};


/////////////////////////////////////////////////////////////////////////////

#endif // __BEMSYMBOLS_H__
