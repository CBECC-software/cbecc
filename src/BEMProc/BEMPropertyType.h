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

#ifndef __BEMPROPERTYTYPE_H__
#define __BEMPROPERTYTYPE_H__

#include "BEMProc.h"
#include "BEMSymbols.h"
#include "expRanges.h"

class CryptoFile;
class BEMTextIO;

/////////////////////////////////////////////////////////////////////////////
// BEMPropertyType
//    An instance of this class is created ...
/////////////////////////////////////////////////////////////////////////////

#define  BEM_MAX_PROPTYPE_OBJREFCLASSES  5   // SAC 6/14/12 - switched from single value to array of up to 5

enum BEMDT_NotInputModes { DTNotInp_AllowUIReset, DTNotInp_IgnoreUserInput, DTNotInp_ErrorIfInput, DTNotInp_Num };		// SAC 8/13/15

class BEMPROC_API BEMPropTypeDetails
{
public:
	BEMPropTypeDetails()		{	m_compDataType = BEMD_NDataTypes;
										m_primary = false;
										m_editable = false;
										m_userDefault = false;
										m_displayInput = false;
										m_displayProposed = false;
										m_displayBudget = false;
										m_notInputMode = DTNotInp_AllowUIReset;	}
	~BEMPropTypeDetails()	{	}

// Operations
public:
	int 	getNumResetDBIDs()			{	return (int) m_resetDBIDs.size();	}
	long	getResetDBID( int idx )		{	return ((idx >= 0 && idx < (int) m_resetDBIDs.size()) ? m_resetDBIDs[idx] : 0);  }
	void  addResetDBID( long lDBID )	{	m_resetDBIDs.push_back( lDBID );  }

	void	copy( BEMPropTypeDetails* pCopyFrom );
	void	setData( int compDataType, bool primary, bool editable, bool userDefault, bool displayInput,
						bool displayProposed, bool displayBudget, int notInputMode, QString notInputMsg )
									{	m_compDataType = compDataType;
										m_primary = primary;
										m_editable = editable;
										m_userDefault = userDefault;
										m_displayInput = displayInput;
										m_displayProposed = displayProposed;
										m_displayBudget = displayBudget;
										m_notInputMode = notInputMode;
										m_notInputMsg = notInputMsg;	}

	int	getCompDataType()			{	return m_compDataType;		}
	bool	isPrimary()					{	return m_primary;				}
	bool	isEditable()				{	return m_editable;			}
	bool	isUserDefaultable()		{	return m_userDefault;		}
	bool	getDisplayInput()			{	return m_displayInput;		}
	bool	getDisplayProposed()		{	return m_displayProposed;	}
	bool	getDisplayBudget()		{	return m_displayBudget;		}
	int	getNotInputMode()			{	return m_notInputMode;		}
	QString getNotInputMsg()		{	return m_notInputMsg;		}

// Attributes
private:
	// data originating from CBEMDataType
	int	m_compDataType;     // the compliance type/classification defined by the enums BEM_CompDataType (defined above)
	bool	m_primary;          // boolean flag set to TRUE if this property/array element is a Primary variable
	bool	m_editable;         // boolean flag set to TRUE if the user is allowed to edit this value
	bool	m_userDefault;      // boolean flag set to TRUE if the value may be defaulted using user-defined defaults
	bool	m_displayInput;     // boolean flag set to TRUE if this variable is to be displayed in the "User Input" interface mode
	bool	m_displayProposed;  // boolean flag set to TRUE if this variable is to be displayed in the "Proposed" interface mode
	bool	m_displayBudget;    // boolean flag set to TRUE if this variable is to be displayed in the "Budget" interface mode
	int	m_notInputMode;		// SAC 8/12/15 - added to facilitate ruleset-based data model backward compatible
	QString m_notInputMsg;		// SAC 8/12/15

   std::vector<long>  m_resetDBIDs;		// was:  CObList  m_resetData;  CBEMResetData
};


class BEMPROC_API BEMPropertyType
{
public:
	BEMPropertyType();
	~BEMPropertyType();

	void ReadText( BEMTextIO& file, int iFileVersion );
	void Write( CryptoFile& file );

// Operations
public:
   void clear();

//   void InitDataTypeList();   - now: initPropTypeDetails()
   void InitResetDataList();

//	CBEMProperty* CreateBEMProperty( int i0Arr );  - no longer needed?
	
	BOOL Copy( BEMPropertyType* pPT );

	int NumberOfDistinctObjectTypesReferenced();

	bool PreviousNameMatch( QString& sName );

	QString	getShortName()						{	return m_shortName;	}
	void		setShortName( QString s )		{	m_shortName = s;  return;	}
	QString	getDescription()					{	return m_description;	}
	void		setDescription( QString s )	{	m_description = s;  return;	}
	QString	getUnitsLabel()					{	return m_unitsLabel;	}
	void		setUnitsLabel( QString s )		{	m_unitsLabel = s;  return;	}

	int	getPropType()				{	return m_propType;	}
	void	setPropType( int i )		{	m_propType = i;  return;	}
	int	getNumValues()				{	return m_numValues;	}
	void	setNumValues( int i )	{	m_numValues = i;  return;	}

	int	getUseForTrees()			{	return m_useForTrees;	}
	void	setUseForTrees( int i )	{	m_useForTrees = i;  return;	}

	int	get1ClassIdx()					{	return m_1ClassIdx;		}
	void	set1ClassIdx( int i )		{	m_1ClassIdx = i;  return;	}
	int	get1PropTypeIdx()				{	return m_1PropTypeIdx;	}
	void	set1PropTypeIdx( int i )	{	m_1PropTypeIdx = i;  return;	}

	int	getSumOfPreviousProperties()			{	return m_sumOfPreviousProperties;	}
	void	setSumOfPreviousProperties( int i)	{	m_sumOfPreviousProperties = i;  return;	}

	int	getObj1ClassIdx( int idx )				{	assert(  idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES );
																return ((idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES) ? m_obj1ClassIdx[idx] : -1);		}
	void	setObj1ClassIdx( int idx, int i )	{	if (     idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES )
																	m_obj1ClassIdx[idx] = i;
																else
																{	assert( false );	}	}
	int	getObjTypeDBID( int idx )				{	assert(  idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES );
																return ((idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES) ? m_objTypeDBID[idx] : -1);		}
	void	setObjTypeDBID( int idx, long i )	{	if (     idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES )
																	m_objTypeDBID[idx] = i;
																else
																{	assert( false );	}	}
	long	getObjTypeValue( int idx )				{	assert( idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES );
																return (idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES ) ? m_objTypeValue[idx] : -1;  }
	void	setObjTypeValue( int idx, long i )	{	if (     idx >= 0 && idx < BEM_MAX_PROPTYPE_OBJREFCLASSES )
																	m_objTypeValue[idx] = i;
																else
																{	assert( false );	}	}
	bool	setObjClassDataFromStrings();

	UINT	getHelpID()						{	return m_helpID;	}
	void	setHelpID( UINT i )			{	m_helpID = i;  return;	}
	BOOL	getXMLWriteArrayIndices()				{	return m_XMLWriteArrayIndices;	}
	void	setXMLWriteArrayIndices( BOOL b )	{	m_XMLWriteArrayIndices = b;  return;	}
	long	getWriteSimulationFlag()				{	return m_writeSimulationFlag;	}
	void	setWriteSimulationFlag( long i )		{	m_writeSimulationFlag = i;  return;	}
	int	getReportPrecision()						{	return m_reportPrecision;	}
	void	setReportPrecision( int i )			{	m_reportPrecision = i;  return;	}
	QString	getInputClassInfo()					{	return m_inputClassInfo;	}
	void		setInputClassInfo( QString s )	{	m_inputClassInfo = s;  return;	}
	QString	getPreviousName( int idx )			{	return m_previousNames[idx];	}
	void		addPreviousName( QString s )		{	m_previousNames.push_back( s );  return;	}
	BOOL	getDefinedByRuleset()					{	return m_definedByRuleset;		}
	void	setDefinedByRuleset( BOOL b )			{	m_definedByRuleset = b;  return;	}

	BEMSymbolList* getSymbolList()		{	return &m_symbolList;	}

	void initPropTypeDetails();
	int  getNumPropTypeDetails()			{	return (int) m_details.size();  }
	BEMPropTypeDetails* getPropTypeDetails( int i0ArrIdx )	{	return ((i0ArrIdx >= 0 && i0ArrIdx < (int) m_details.size()) ?
																																&m_details.at( i0ArrIdx ) : NULL);  }
	int	getNumResetDBIDs( int i0ArrIdx )						{	return ((i0ArrIdx >= 0 && i0ArrIdx < (int) m_details.size()) ? m_details.at( i0ArrIdx ).getNumResetDBIDs() : 0);	}
	long	getResetDBID(     int i0ArrIdx, int i0RIdx )		{	return ((i0ArrIdx >= 0 && i0ArrIdx < (int) m_details.size()) ? m_details.at( i0ArrIdx ).getResetDBID( i0RIdx ) : 0);	}
	void  clearPropTypeDetails();

	int	getNumRangeChecks()								{	return (int) m_ranges.size();  }
	BEMRangeCheck*	getRangeCheck(int iR)				{	return ((iR >= 0 && iR < (int) m_ranges.size()) ? &m_ranges.at(iR) : NULL);  }
	void	addRangeCheck(BEMRangeCheck* pR);
	void  clearRangeChecks();

	void	setData(	const char* shortname, int propType, int objClassIdx, long objTypeDBID, long objTypeValue, int numValues,
						const char* unitsLabel, int useForTrees, UINT helpID, int classIdx, int propTypeIdx, int sumOfPreviousProperties,
						BOOL xmlWriteArrayIndices, int writeSimulationFlag, int reportPrecision, const char* descrip, BOOL definedByRuleset )
								{	m_shortName       = shortname;
									m_propType        = propType;
									m_obj1ClassIdx[0] = objClassIdx;
						   		m_objTypeDBID[ 0] = objTypeDBID;
						   		m_objTypeValue[0] = objTypeValue;
						   		m_numValues       = numValues;
						   		m_unitsLabel      = unitsLabel;
						   		m_useForTrees     = useForTrees;
						   		m_helpID          = helpID;
						   		m_1ClassIdx       = classIdx;
						   		m_1PropTypeIdx    = propTypeIdx;
									m_sumOfPreviousProperties = sumOfPreviousProperties;
									m_XMLWriteArrayIndices    = xmlWriteArrayIndices;
									m_writeSimulationFlag     = writeSimulationFlag;
									m_reportPrecision = reportPrecision;
						 			m_description     = descrip;
									m_inputClassInfo.clear();
									m_previousNames.clear();
									initPropTypeDetails();
									m_definedByRuleset = definedByRuleset;  }

// Attributes
private:
	QString  m_shortName;      // name of this property type (need only be unique within the property types
                              // which describe each type of building component)
	int		m_propType;       // => BEMP_Int / BEMP_Flt / BEMP_Sym / BEMP_Str / BEMP_Obj

	int   	m_obj1ClassIdx[BEM_MAX_PROPTYPE_OBJREFCLASSES];  // 1-Based Class index of referenced object (only valid for m_iPropType = BEMP_Obj)
	QString	m_obj1ClassStr[BEM_MAX_PROPTYPE_OBJREFCLASSES];  // Class name of referenced object (only valid for m_iPropType = BEMP_Obj)
   long     m_objTypeDBID[ BEM_MAX_PROPTYPE_OBJREFCLASSES];  // DBID of property which defines a specific TYPE of component that can be referenced
   QString  m_objPropStr[  BEM_MAX_PROPTYPE_OBJREFCLASSES];  // Name of property which defines a specific TYPE of component that can be referenced
   long     m_objTypeValue[BEM_MAX_PROPTYPE_OBJREFCLASSES];  // Value of property which defines a specific TYPE of component that can be referenced

   int		m_numValues;      // Number of array elements for numeric, symbolic AND string types
   QString	m_unitsLabel;     // unit label used to label the UI control which displays this data
   int		m_useForTrees;    // flag used only for prop types of type BEMP_Obj - used to indicate whether or not
                              // to follow object references when constructing tree control elements.
                              // 0 => ignore when constructing tree controls
                              // 1 => take into account when constructing tree controls
                              // almost always = 1, except for prop types which reference the same component type
                              // as the one which this prop type describes, like Space:NextTo and Zone:IndAirZone.
   UINT     m_helpID;         // item help system ID
	
   int    m_1ClassIdx;     // 1-Based index of the class which this property type describes
   int    m_1PropTypeIdx;  // 1-Based index of this PropType in the array which describe this class

   int    m_sumOfPreviousProperties;  // SAC 1/22/02 - Sum of m_iNumValues for all previous CBEMPropertyTypes that describe this class

	BOOL   m_XMLWriteArrayIndices;		// SAC 1/24/12 - (file ver 2) added to indicate whether or not array indices are to be written to output XML files

	long   m_writeSimulationFlag;  // SAC 5/22/12 - 0-Never write to sim export, 1-Write to sim export whenever defined (default, rule, library...), 2-Write to sim export only if USER defined (or UsrDflt, UsrLib)

 	QString m_description; // string used to label dynamically created UI controls in primary data dialogs
 	QString m_inputClassInfo; // SAC 3/3/14 - added separate description of input class for when it varies based on other BEMBase property data

   int      m_reportPrecision;  // SAC 2/4/15 - property to facilitate rounding of numeric results for compliance reporting - rounding only for output of non-User models written to analysis results XML file
   										//					-9 = default/unused, 3 for 0.xxx, 2 for 0.xx, 1 for 0.x, 0 for x, -1 for x0, -2 for x00, -3 for x000, etc.

	QStringList	m_previousNames;	// SAC 8/6/15 - to facilitate data model backward compatibility by tracking re-named properties
   int		m_userSpecification;		// default property type classification (default/prescribed/optional/etc.)

	BEMSymbolList m_symbolList;

   std::vector<BEMPropTypeDetails>  m_details;		// combines  m_resetData & m_dataTypes - SAC 4/1/16

	std::vector<BEMRangeCheck>			m_ranges;      // list of range check definitions (not tied to individual array elements) - SAC 9/24/16 - switched to object array (from ptrs)

	BOOL    m_definedByRuleset;		// SAC 1/11/15 - added to facilitate processing specific to ruleset-defined properties.  No BEMBase.bin file I/O (at least for now)
};

/////////////////////////////////////////////////////////////////////////////

extern void SetUserReferencedFlag( BEMObject* pObj, bool bFlag, int iBEMProcIdx );

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMPROPERTYTYPE_H__
