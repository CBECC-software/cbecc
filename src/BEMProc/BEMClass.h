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

#ifndef __BEMCLASS_H__
#define __BEMCLASS_H__

#include "BEMProc.h"
//#include "BEMObject.h"
#include "BEMProperty.h"

class BEMObject;
class CryptoFile;
class BEMTextIO;


/////////////////////////////////////////////////////////////////////////////
// BEMClass
//    An instance of this class is created ...
/////////////////////////////////////////////////////////////////////////////

#define  BEM_MAX_PARENT_TYPES  15   // SAC 1/24/12 - increased to 15 from 5
#define  BEM_MAX_CHILD_TYPES   25	// SAC 6/14/12 - increased 10->15 / SAC 9/1/16 - 15->25

// enums to denote values for the new m_iObjectCopyFlag CBEMClass member
enum BEMProc_Class_CopyFlag
{
   BEMCCF_DontCopy,
   BEMCCF_CopyOnlyIfChild,
   BEMCCF_CopyIfChildOrRef,
   BEMCCF_NumValues
};

class BEMPROC_API BEMClass
{
public:
	BEMClass();
	~BEMClass();

	void ReadText( BEMTextIO& file, int iFileVersion );
	void Write( CryptoFile& file );

// Operations
public:
   void clear();

	const QString	getShortName()						{	return m_shortName;	}
	void				setShortName( QString str )	{	m_shortName = str;	}
	const QString	getLongName()						{	return m_longName;	}
	void				setLongName( QString str )		{	m_longName = str;	}
	const QString	getDefaultName()					{	return m_defaultName;	}
	void				setDefaultName( QString str )	{	m_defaultName = str;	}
	const QString	getMirrorClassName()						{	return m_mirrorClassName;	}
	void				setMirrorClassName( QString str )	{	m_mirrorClassName = str;	}

   int	getNumProps()			{	return m_numProps;	}
   void	incNumProps()			{	m_numProps++;  return;	}
   void	setNumProps( int i)	{	m_numProps = i;  return;	}

   int	getFirstPropID()				{	return m_firstPropID;	}
   void	incFirstPropID()				{	m_firstPropID++;  return;	}
   void	setFirstPropID( int i )		{	m_firstPropID = i;  return;	}

	QString getParentTypeStr( int iPT )		{	assert(  iPT >= 0 && iPT < BEM_MAX_PARENT_TYPES );
															return ((iPT >= 0 && iPT < BEM_MAX_PARENT_TYPES) ? m_parentTypeStr[iPT] : "");	}
	int 	getParentType( int iPT )			{	assert(  iPT >= 0 && iPT < BEM_MAX_PARENT_TYPES );
															return ((iPT >= 0 && iPT < BEM_MAX_PARENT_TYPES) ? m_parentType[iPT] : -1);	}
	void	setParentType( int iPT, int i )	{	if (     iPT >= 0 && iPT < BEM_MAX_PARENT_TYPES )
																m_parentType[iPT] = i;
															else
															{	assert( false );  }	}

	int	getNumChildTypes()					{	return m_numChildTypes;  }
	int 	getChildType( int iCT )				{	assert(  iCT >= 0 && iCT < BEM_MAX_CHILD_TYPES  );
															return ((iCT >= 0 && iCT < BEM_MAX_CHILD_TYPES ) ? m_childType[ iCT] : -1);	}
	void	setChildType( int iCT, int i )	{	if (     iCT >= 0 && iCT < BEM_MAX_CHILD_TYPES  )
																m_childType[iCT] = i;
															else
															{	assert( false );  }	}
	bool	addChildType( int iCls )			{	bool bChildAdded = (m_numChildTypes < BEM_MAX_CHILD_TYPES);			//	assert( bChildAdded );
															if (bChildAdded)
																m_childType[m_numChildTypes++] = iCls;
															return bChildAdded;	}
	void	setNumChildTypes( int i )			{	if (i >= 0 && i <= BEM_MAX_CHILD_TYPES)
																m_numChildTypes = i;
															else
															{	assert( false );  }	}

   long	getMaxDefinable()				{	return m_maxDefinable;	}
   void	setMaxDefinable( long i )	{	m_maxDefinable = i;	}
   int	getMaxReferences()			{	return m_maxReferences;	}
   void	setMaxReferences( int i )	{	m_maxReferences = i;	}
   int	getMaxSimComps()				{	return m_maxSimComps;	}
   void	setMaxSimComps( int i )		{	m_maxSimComps = i;	}
   int	getMaxChildren()				{	return m_maxChildren;	}
   void	setMaxChildren( int i )		{	m_maxChildren = i;	}

   int	getAutoCreate()				{	return m_autoCreate;	}
   void	setAutoCreate( int i )		{	m_autoCreate = i;	}

   int	get1BEMClassIdx()				{	return m_1BEMClassIdx;	}
   void	set1BEMClassIdx( int i)		{	m_1BEMClassIdx = i;  return;	}
   int	get1MirrorClassIdx()			{	return m_1MirrorClassIdx;	}
   void	set1MirrorClassIdx( int i)	{	m_1MirrorClassIdx = i;  return;	}

	int	getCurrentBEM0ObjIdx()					{	return m_currentBEM0ObjIdx;	}
	void	setCurrentBEM0ObjIdx( int iCOI )		{	m_currentBEM0ObjIdx = iCOI;	}

	BEM_ObjType	getCurrentBEMObjType()							{	return m_currentBEMObjType;	}
	void			setCurrentBEMObjType( BEM_ObjType iOT )	{	m_currentBEMObjType = iOT;		}

	BEMObject* 	getCurrentParent()								{	return m_currentParent;			}
	void			setCurrentParent( BEMObject* pParent )		{	m_currentParent = pParent;		}

   BOOL			getUniqueAssignment()							{	return m_uniqueAssignment;		}
   void			setUniqueAssignment( BOOL bUA )				{	m_uniqueAssignment = bUA;		}

	int			getUniqueAssignArraySize()						{	return (int) m_uniqueAssignArray.size();	}
	int			getUniqueAssignArray( int i )					{	return m_uniqueAssignArray.at(i);	}

   BOOL			getPurgeUnrefCompsBeforeSim()							{	return m_purgeUnrefCompsBeforeSim;	}
   void			setPurgeUnrefCompsBeforeSim( BOOL b )				{	m_purgeUnrefCompsBeforeSim = b;		}

   UINT			getHelpID()							{	return m_helpID;	}
   void			setHelpID( UINT ui )				{	m_helpID = ui;		}

	int		getObjectCopyFlag()						{	return m_objectCopyFlag;	}
	void		setObjectCopyFlag( int i )				{	m_objectCopyFlag = i;	}
   BOOL		getWriteAsSingleRecord()				{	return m_writeAsSingleRecord;	}
   void		setWriteAsSingleRecord( BOOL b )		{	m_writeAsSingleRecord = b;		}
   BOOL		getXMLIgnoreName()						{	return m_XMLIgnoreName;	}
   void		setXMLIgnoreName( BOOL b )				{	m_XMLIgnoreName = b;		}
	const QString	getDefaultNameTemplate()					{	return m_defaultNameTemplate;	}
	void				setDefaultNameTemplate( QString str )	{	m_defaultNameTemplate = str;	}

	BEMObject* CreateBEMObject( QString sName, BEM_ObjType objType = BEMO_User,
	                           BEMObject* pParent = NULL, bool bDefaultParent = TRUE,
                              bool bAutoCreate = TRUE, int iBEMProcIdx=-1, BOOL bIgnoreMaxDefinable=FALSE, int i0ChildIdx = -1 );  // SAC 5/29/14 - added i0ChildIdx in place of BOOL bMakeFirstChild = FALSE );
   void RemoveObjects( BEM_ObjType eObjType, bool bDeleteObjects=true );
	bool RemoveObject( BEM_ObjType eObjType, int iObjIdx );
   int  ObjectCount( BEM_ObjType eObjType = BEMO_User );
   BEMObject*  GetObject( BEM_ObjType eObjType, int iObjIdx );
   void AddObject( BEMObject* pObj, BEM_ObjType objType = BEMO_User );

   BOOL ClassInParentList( int i1ParentClass );
	void SetParentChildTypesFromStrings();

   BOOL Copy( BEMClass* pClass, BOOL bCopyObjects=TRUE );

	int  GetChildClassID( const char* pszChildClassName );	// SAC 8/15/12

// Attributes
private:
   QString    m_shortName;       // Short name (max 7 characters)
   QString    m_longName;        // Long (more descriptive) name 
   QString    m_defaultName;     // String used to default the name of newly created bldg components: "<DefName> #"
   int        m_numProps;        // number of properties which describe this type of bldg component
   long       m_maxDefinable;    // maximum number of component of this type which can be created   // SAC 1/27/12 - short -> long
   int        m_maxReferences;   // maximum times this component can be referenced by other components
                                 // 0 => no limit, > 0 => don't allow more than that number of references
   int        m_maxSimComps;     // maximum number of components that will be created for simulation from a single BEM component
   int        m_maxChildren;     // maximum occurences of THIS class that can be attached to a single parent component
   int        m_autoCreate;      // flag which is set to 1 if this component is created & deleted
                                 // automatically whenever a component which references this type is created/deleted
                                 // 1 => create automatically

   int        m_parentType[BEM_MAX_PARENT_TYPES];  // 0-based component types of parent
   QString    m_parentTypeStr[BEM_MAX_PARENT_TYPES];  // component types of parent (string - only populated during compilation)
   int        m_childType[ BEM_MAX_CHILD_TYPES];   //  0-based component types of children
   int        m_numChildTypes;

   int        m_bldgPtrIdx;      // NOT USED - delete??
   int        m_firstPropID;     // 0-based index of first property which describes this component type
   UINT       m_helpID;         // topic help system ID

   int          m_1BEMClassIdx;        // 1-based index of this component type within the list of component types
   int          m_1MirrorClassIdx;    // SAC 7/28/02 - 1-based index of the class that this component type is the mirror of
   QString      m_mirrorClassName;    // name of class that this component type is the mirror of
   int          m_currentBEM0ObjIdx;   // 0-based index of object of this type which is currently being edited
   BEM_ObjType  m_currentBEMObjType;   // object type (User, RuleLib, UserLib) of object which is currently being edited
   BEMObject*   m_currentParent;      // pointer to the parent of the of this type which is currently being edited

   std::vector<BEMObject*>  m_bdObjects;	// Array of User-Defined components of this type
   std::vector<BEMObject*>  m_rlObjects;	// Array of Rule Library components of this type
   std::vector<BEMObject*>  m_ulObjects;	// Array of User Library components of this type

   BOOL					m_uniqueAssignment;    // flag indicating whether or not to ensure component assignment uniqueness
   std::vector<int>	m_uniqueAssignArray;   // values of Proj:UniqueAssignFlag which require component assignment uniqueness

   BOOL        m_purgeUnrefCompsBeforeSim;  // flag indicating whether or not components of this type should be purged
                                             // prior to simulation

   int         m_objectCopyFlag;    // Added flag value to indicate whether or not this component should get copied (by default)
   											// when either (or both) its parent or a component that references it is copied
	BOOL    		m_writeAsSingleRecord;	// (file ver 2) added to facilitate tighter IBD & XML file writing
	BOOL    		m_XMLIgnoreName;			// (file ver 2) added to prevent output of component names to XML files
	QString 		m_defaultNameTemplate;	// (file ver 2) added to specify a template for defaulting new component names
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// BEMObject
//    An instance of this class is created for each building component
//    contained in the building database (including both user-defined AND 
//    library-defined components).
/////////////////////////////////////////////////////////////////////////////

// SAC 3/13/13 - added multiple model support
#define  BEMPROC_MAXMODELS  11 

#define  DEFAULT_TREE_STATE  0xFF

class BEMPROC_API BEMObject
{
public:
	BEMObject(	QString sName = "", BEM_ObjType objType = BEMO_User, BEMClass* pClass = NULL,
					BEMObject* pParent = NULL, bool bUserReferenced = false )
							{	m_objectName = sName;
								m_objectType = objType;
								m_class = pClass;
								m_parent = pParent;
								m_userReferenced = bUserReferenced;
								m_objectID = 0;
								m_treeState = DEFAULT_TREE_STATE;
								for (int i=0; i<BEMPROC_MAXMODELS; i++)
									m_modelMappedObjects[i] = NULL;		// storage of pointers to objects in other models that are either copied to or from this object
							};
	~BEMObject()		{	clear();	};

// Operations
public:
   void clear();

	QString			getName()						{	return m_objectName;		}
	void				setName( QString sName )	{	m_objectName = sName;	}

	BEMClass*	getClass()								{	return m_class;	}

	bool			haveParent()							{	return (m_parent != NULL);	}
	BEMObject*	getParent()								{	return m_parent;	}
	void			setParent( BEMObject* pParent )	{	m_parent = pParent;	}

	bool			getUserReferenced()					{	return m_userReferenced;	}
	void			setUserReferenced( bool bURef )	{	m_userReferenced = bURef;	}

   BEM_ObjType getObjectType()						{	return m_objectType;		}

	int			getChildCount()						{	return (int) m_children.size();	}
	BEMObject*	getChild( int idx )					{	return ((idx >= 0 && idx < (int) m_children.size()) ? m_children.at(idx) : NULL);	}
	void			addChild( BEMObject* pChld )		{	m_children.push_back( pChld );	}
   int			countChildrenOfClass( int i1Class )
   							{	int iNumChildrenOfThisClass = 0;
									for (std::vector<BEMObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
									{	BEMObject*& pObj = *it;		assert( pObj );
										if (pObj && pObj->getClass() && pObj->getClass()->get1BEMClassIdx() == i1Class)
											iNumChildrenOfThisClass++;
									}
									return iNumChildrenOfThisClass;		}

	void		addChildToParent( int i0ChildIdx = -1 )
								{	if (m_parent == NULL)
										return;
									else if (i0ChildIdx == 0)		// SAC 5/29/14 - was: bMakeFirstChild )
										m_parent->m_children.insert( m_parent->m_children.begin(), this );
									else if (i0ChildIdx < 0)
										m_parent->m_children.push_back( this );
									else
										m_parent->m_children.insert( m_parent->m_children.begin() + i0ChildIdx, this );		}

	void		initProperties( int iNumProps )		{	m_properties.clear();
																	m_properties.resize( iNumProps );	}
	int						getPropertiesSize()		{	return (int) m_properties.size();	}
//	const BEMProperty*	getProperty( int i )		{	return &m_properties.at(i);			}
	BEMProperty*			getProperty( int i )		{	return &m_properties.at(i);			}
	bool		initProperty( int i, BEMPropertyType* pType = NULL, int i0Arr = 0 )
																{	if (i < 0 || i >= (int) m_properties.size())
																		return false;
																	else
																	{	m_properties[i].setType( pType );
																		m_properties[i].set1ArrayIdx( i0Arr+1 );
																	}
																	return true;	}

	BEMObject* getModelMappedObject( int i0Model )	{	if (i0Model >= 0 && i0Model < BEMPROC_MAXMODELS)
																			return m_modelMappedObjects[ i0Model ];
																		return NULL;  }
	void		setModelMappedObject( int i0Model, BEMObject* pObj )
																	{	if (i0Model >= 0 && i0Model < BEMPROC_MAXMODELS)
																			m_modelMappedObjects[ i0Model ] = pObj;  }

   QString	getArchiveParentName()						{	return m_archiveParentName;  }
   void		setArchiveParentName( QString sRPN )	{	m_archiveParentName = sRPN;  }
   void		clearArchiveParentName()					{	m_archiveParentName.clear();  }

	int		getTreeState()					{	return m_treeState;	}
	void		setTreeState( int iTS )		{	m_treeState = iTS;	}

   bool RemoveChild( BEMObject* pChild );
   bool GetChildIndices( int& i0ChildIdx, int& iNumChildren );	// SAC 7/23/14 - added to facilitate user-defined child ordering
	bool GetParentChildIndices( BEMObject* pChild, int& i0ChildIdx, int& iNumChildren );
	bool ChangeChildIndex( bool bMoveUp=true );		// SAC 7/27/14 - added to facilitate user-defined child ordering
	bool ChangeParentChildIndex( BEMObject* pChild, bool bMoveUp=true );
   bool DefaultObject( int iOccur, bool bApplyUserDefs=TRUE, long lDBID=0, BEM_PropertyStatus ePropStatus=BEMS_Undefined,
                       BOOL bSingleValueModified=FALSE, int iBEMProcIdx=-1 );
   bool CopyObject(    BEMObject* pObj, int iBEMProcIdx=-1,
								bool bCopyPrimaryDefaultDataAsUserDefined=false );		// SAC 6/8/15 - CBECC issue 1061
   bool CopyObjectBetweenModels( BEMObject* pObj, int iThisBEMProcIdx, int iSrcBEMProcIdx );
//   bool ArchiveObject( BEMObject* pObj, bool bRestore=FALSE, int iBEMProcIdx=-1 );  // SAC 7/31/02 - Added to archive baseline design components

	void AutoCreateReferences( int iBEMProcIdx=-1 );
//   void DeleteProperties();		SAC 9/24/16 - removed since no longer sotring properties in array of BEMProperty pointers

   void SetTreeState( int iTreeStateIdx, int iState );
   bool ObjectTreeStateExpanded( int iTreeStateIdx );

   bool EquivalentObject( BEMObject* pObj, bool bIgnoreDataStatus=FALSE );

   bool ObjectIsReferenced( BEMObject* pObj );

   BOOL CopyAllButPropertiesAndChildren( BEMObject* pObj, BEMClass* pClass );

// Attributes
private:
	int			m_objectID;         // NOT USED - delete??
	QString		m_objectName;       // Name of the building component
	QString		m_objSimName;       // Object's Simulation Name (guarenteed unique w/ limited characters)
	QString		m_objSecSimName;    // Object's Secondary Simulation Name (guarenteed unique w/ limited characters)
	QString		m_objTerSimName;    // Object's Tertiary Simulation Name (guarenteed unique w/ limited characters)
                                    // (secondary & tertiary names are only defined for components which may be
                                    //  split into multiple distinct components in order to simulate)
   BEM_ObjType m_objectType;       // User, RuleLib or UserLib-defined 
   bool        m_userReferenced;   // Flag set to TRUE for library components which are referenced
                                    // (either directly or indirectly) by user-defined component(s)
	std::vector<BEMProperty>	m_properties;			// vector of BEMProperty - properties which describe this component
	std::vector<BEMObject*>		m_children;				// vector of BEMObject - child building components
	BEMClass*	m_class;            // Pointer to BEMClass instance which defines this component type
	BEMObject*	m_parent;           // Pointer to this components parent component

   QString		m_archiveParentName;  // SAC 7/31/02 - Added to facilitate archiving of baseline design objects for new EEM run mechanism

   int         m_treeState;         // Flag value where each bit corresponds with a tree mode (0-N) and
                                    // a value (0/1) indicates that item's state (not expanded/expanded)

	BEMObject*	m_modelMappedObjects[ BEMPROC_MAXMODELS ];		// storage of pointers to objects in other models that are either copied to or from this object
};

/////////////////////////////////////////////////////////////////////////////

#endif // __BEMCLASS_H__
