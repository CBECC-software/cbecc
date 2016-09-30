/* Screens.h
*/
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

#ifndef __BEMPUISCREENS_H__
#define __BEMPUISCREENS_H__

#include "textio.h"


struct CBEMPUIControl;
struct CBEMPUIPage;


///////////////////////////////////////////////////////////////
// CBEMCondition
///////////////////////////////////////////////////////////////

#define  MAX_BEM_CONDITIONS  5

struct CBEMCondition
{
   // Constructor
   CBEMCondition();

   // Data
   int    m_iNumConditions;
   BOOL   m_bConditionsAND;

   long   m_lConditionalDBID[ MAX_BEM_CONDITIONS ];
   int    m_iCondition[       MAX_BEM_CONDITIONS ];
   float  m_fConditionValue[  MAX_BEM_CONDITIONS ];

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   long   m_lCondDBIDOffset[  MAX_BEM_CONDITIONS ];

   // SAC 3/3/99 - added to enable specific DB class instance references
   int    m_iCondDBInstance[  MAX_BEM_CONDITIONS ];

   // SAC 3/4/99 - Added second array of DBIDs to enable access to referenced component data
   long   m_lCondDBID2[       MAX_BEM_CONDITIONS ];
   long   m_lCondDBIDOffset2[ MAX_BEM_CONDITIONS ];

   // Functions
   void   Init();
   BOOL   Read( CTextIO& file, CBEMPUIPage* pPage, const char* psCondType );
   BOOL   MissingOrTrue();
   BOOL   Present();

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   void SetupDBIDOffsets( int iClassID, long lDBIDOffset );
};

inline BOOL CBEMCondition::Present()
   {  return (m_iNumConditions > 0);  }


///////////////////////////////////////////////////////////////
// SAC 10/18/02 - added help item class stuff

///////////////////////////////////////////////////////////////
//                   CBEMHelpItem                             //
///////////////////////////////////////////////////////////////

class CBEMHelpItem : public CObject
{
public:
   CBEMHelpItem();
   ~CBEMHelpItem();

   // Spreadsheet Column Data
   CString       m_sText;
   long          m_lHelpID;
   CBEMCondition m_cCondition;

   DECLARE_SERIAL(CBEMHelpItem)
   
   BOOL ReadText( CTextIO& file, CBEMPUIPage* pPage );

   BOOL HaveCondition();

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif
};

inline BOOL CBEMHelpItem::HaveCondition()
   {  return (m_cCondition.Present());  }


///////////////////////////////////////////////////////////////
//                   CBEMHelpItemArray                        //
///////////////////////////////////////////////////////////////

class CBEMHelpItemArray : public CObject
{
public:
   CBEMHelpItemArray();
   ~CBEMHelpItemArray();

   void DeleteContents();

   int             Add( CObject* obj );
   CBEMHelpItem*&  ElementAt( int index );
   CBEMHelpItem*   GetAt( int index );
   void            RemoveAll();
   int             GetSize() const;

   DECLARE_SERIAL(CBEMHelpItemArray)

//   virtual void Serialize(CArchive& ar, int iFileVer);
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

private:
   CObArray array;
};

inline int            CBEMHelpItemArray::Add( CObject* obj )  {return                 array.Add(obj);         }
inline CBEMHelpItem*& CBEMHelpItemArray::ElementAt(int index) {return (CBEMHelpItem*&) array.ElementAt(index);}
inline CBEMHelpItem*  CBEMHelpItemArray::GetAt(int index)     {return (CBEMHelpItem*)  array.GetAt(index);    }
inline void           CBEMHelpItemArray::RemoveAll()          {                       array.RemoveAll();      }
inline int            CBEMHelpItemArray::GetSize( ) const     {return                 array.GetSize();        }


///////////////////////////////////////////////////////////////
//                   CBEMHelpItemGroup                       //
///////////////////////////////////////////////////////////////

class CBEMHelpItemGroup : public CObject
{
public:
   CBEMHelpItemGroup();
   ~CBEMHelpItemGroup();

   CBEMHelpItemArray  m_aHelpItems;

   DECLARE_SERIAL(CBEMHelpItemGroup)

//   virtual void Serialize(CArchive& ar, int iFileVer);

   BOOL ReadText( CTextIO& file, int iNumHelpItems, CBEMPUIPage* pPage, int iFileStructVersion );
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif
};

///////////////////////////////////////////////////////////////
//                   CBEMHelpItemGroupArray                  //
///////////////////////////////////////////////////////////////

class CBEMHelpItemGroupArray : public CObject
{
public:
   CBEMHelpItemGroupArray();
   ~CBEMHelpItemGroupArray();

   void DeleteContents();

   int                 Add( CObject* obj );
   CBEMHelpItemGroup*& ElementAt( int index );
   CBEMHelpItemGroup*   GetAt( int index );
   void                RemoveAll();
   int                 GetSize() const;

   DECLARE_SERIAL(CBEMHelpItemGroupArray)

//   virtual void Serialize(CArchive& ar, int iFileVer);
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

private:
   CObArray array;
};

inline int                 CBEMHelpItemGroupArray::Add( CObject* obj )  {return                      array.Add(obj);        }
inline CBEMHelpItemGroup*& CBEMHelpItemGroupArray::ElementAt(int index) {return (CBEMHelpItemGroup*&)array.ElementAt(index);}
inline CBEMHelpItemGroup*  CBEMHelpItemGroupArray::GetAt(int index)     {return (CBEMHelpItemGroup*) array.GetAt(index);    }
inline void                CBEMHelpItemGroupArray::RemoveAll()          {                            array.RemoveAll();     }
inline int                 CBEMHelpItemGroupArray::GetSize( ) const     {return                      array.GetSize();       }


///////////////////////////////////////////////////////////////
// SAC 6/5/00 - added spreadsheet class stuff

///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadCol                          //
///////////////////////////////////////////////////////////////

class CBEMPUISpreadCol : public CObject
{
public:
   CBEMPUISpreadCol();
   ~CBEMPUISpreadCol();

   // Spreadsheet Column Data
   CString   m_sTitle;
   int       m_iWidth;
   int       m_iMisc;
   BOOL      m_bDispUnits;
   BOOL      m_bEditable;
   long      m_lDBID;
   int       m_iDataType;   // => BEMP_Int, BEMP_Flt, BEMP_Sym, BEMP_Str, or BEMP_Obj
   int       m_iItemHelp;
   CString   m_sStatusMsg;
// RW 11/4/02 - Added to allow for rulelist generated tooltip messages
   CString   m_sTooltipRulelistName;

   // Conditional display of cells
   CBEMCondition m_cDisplayCondition;

   // Conditional editing of cells
   CBEMCondition m_cEditCondition;  // SAC 12/11/00

   DECLARE_SERIAL(CBEMPUISpreadCol)
   
//   virtual void Serialize(CArchive& ar, int iFileVer);

   BOOL ReadText( CTextIO& file, int i1ClassIdx, CBEMPUIPage* pPage );

   BOOL HaveDisplayCondition();
   BOOL HaveEditCondition();  // SAC 12/11/00

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif
};

inline BOOL CBEMPUISpreadCol::HaveDisplayCondition()
   {  return (m_cDisplayCondition.Present());  }

inline BOOL CBEMPUISpreadCol::HaveEditCondition()
   {  return (m_cEditCondition.Present());  }


///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadColArray                     //
///////////////////////////////////////////////////////////////

class CBEMPUISpreadColArray : public CObject
{
public:
   CBEMPUISpreadColArray();
   ~CBEMPUISpreadColArray();

   void DeleteContents();

   int                 Add( CObject* obj );
   CBEMPUISpreadCol*&  ElementAt( int index );
   CBEMPUISpreadCol*   GetAt( int index );
   void                RemoveAll();
   int                 GetSize() const;

   DECLARE_SERIAL(CBEMPUISpreadColArray)

//   virtual void Serialize(CArchive& ar, int iFileVer);
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

private:
   CObArray array;
};

inline int                CBEMPUISpreadColArray::Add( CObject* obj )  {return                     array.Add(obj);        }
inline CBEMPUISpreadCol*& CBEMPUISpreadColArray::ElementAt(int index) {return (CBEMPUISpreadCol*&)array.ElementAt(index);}
inline CBEMPUISpreadCol*  CBEMPUISpreadColArray::GetAt(int index)     {return (CBEMPUISpreadCol*) array.GetAt(index);    }
inline void               CBEMPUISpreadColArray::RemoveAll()          {                           array.RemoveAll();     }
inline int                CBEMPUISpreadColArray::GetSize( ) const     {return                     array.GetSize();       }


///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadConfig                       //
///////////////////////////////////////////////////////////////

class CBEMPUISpreadConfig : public CObject
{
public:
   CBEMPUISpreadConfig( long lCompDBID=0 );  // SAC 9/10/01 - added lCompDBID argument
   ~CBEMPUISpreadConfig();

   // Spreadsheet Config Data
   int     m_i1ClassIdx;
   int     m_iLockedCols;
   
   int     m_iConfigMode;   // 0=>Normal, 1=>Transpose

   int     m_iRowHdr;
   int     m_iRowHdrFont;
   int     m_iRowHdrHeight;
   int     m_iRowHdrColWidth;

   long    m_lNumRowsDBID;  // SAC 6/8/00 - added to dynamically adjust number of displayed rows

   long    m_iRowGrouping;  // SAC 2/1/01 - Added to enable modified row labels and lines to separate row groups

   long    m_lCompDBID;     // SAC 9/10/01 - Added to enable display/edit of referenced components (for EEM UI)

   CString m_sTopLeftHdrLabel;  // SAC 8/9/02 - Added to enable header string above row numbers
   int     m_iAllowRowDeletion; // RW 8/23/02 - Added to determine whether or not the user has the ability to delete rows

   CBEMPUISpreadColArray  m_aColumns;

   DECLARE_SERIAL(CBEMPUISpreadConfig)

//   virtual void Serialize(CArchive& ar, int iFileVer);

   BOOL ReadText( CTextIO& file, int i1ClassIdx, CBEMPUIPage* pPage, int iFileStructVersion );
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif
};

///////////////////////////////////////////////////////////////
//                   CBEMPUISpreadConfigArray                  //
///////////////////////////////////////////////////////////////

class CBEMPUISpreadConfigArray : public CObject
{
public:
   CBEMPUISpreadConfigArray();
   ~CBEMPUISpreadConfigArray();

   void DeleteContents();

   int                    Add( CObject* obj );
   CBEMPUISpreadConfig*&  ElementAt( int index );
   CBEMPUISpreadConfig*   GetAt( int index );
   void                   RemoveAll();
   int                    GetSize() const;

   DECLARE_SERIAL(CBEMPUISpreadConfigArray)

//   virtual void Serialize(CArchive& ar, int iFileVer);
   
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

private:
   CObArray array;
};

inline int                   CBEMPUISpreadConfigArray::Add( CObject* obj )  {return                        array.Add(obj);        }
inline CBEMPUISpreadConfig*& CBEMPUISpreadConfigArray::ElementAt(int index) {return (CBEMPUISpreadConfig*&)array.ElementAt(index);}
inline CBEMPUISpreadConfig*  CBEMPUISpreadConfigArray::GetAt(int index)     {return (CBEMPUISpreadConfig*) array.GetAt(index);    }
inline void                  CBEMPUISpreadConfigArray::RemoveAll()          {                              array.RemoveAll();     }
inline int                   CBEMPUISpreadConfigArray::GetSize( ) const     {return                        array.GetSize();       }


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CBEMPUIScreenData
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

// SAC 8/28/00 - increased from 3000 to 3500
// SAC 4/ 9/01 - increased from 3500 to 4000
// SAC 1/26/02 - increased from 4000 to 4500
// SAC 4/28/02 - increased from 4500 to 5000
// SAC 10/6/02 - increased from 5000 to 5500
#define  MAX_TAB_CONTROLS  5500
// SAC  1/26/02 - increased from 100 to 150
// SAC 10/30/02 - increased from 150 to 250
#define  MAX_TAB_PAGES      250

class CBEMPUIScreenData : public CObject
{
public:
   CBEMPUIScreenData();
   ~CBEMPUIScreenData();

public:
   CString         m_sScreenDataFileName;

   int             m_iNumControls;
   CBEMPUIControl* m_apControls[ MAX_TAB_CONTROLS ];

   int             m_iNumPages;
   CBEMPUIPage*    m_apPages[ MAX_TAB_PAGES ];

   int             m_iMainScreenTabs;

   CBEMPUISpreadConfigArray  m_aSpreadConfigs;  // SAC 6/5/00

   CBEMHelpItemGroupArray    m_aHelpItemGroups;  // SAC 10/18/02

public:
   void DeleteData();
   BOOL Init( const char* pszScreenDataFileName = NULL, BOOL bReportResults=FALSE );

   BOOL ReadMainScreenInfo( CTextIO& file, int iFileStructVersion=1 );
   BOOL ReadScreenControl(  CTextIO& file, int iFileStructVersion=1 );
   BOOL ReadScreenPage(     CTextIO& file, int iFileStructVersion=1 );

   int             GetNumPagesByClass( int iClass, int iUIMode=1 );
   CBEMPUIPage*    GetPageByClassAndIndex( int iClass, int iPageIdx, int iUIMode=1 );
   CBEMPUIPage*    GetPageByID( int iPageID );
   CBEMPUIControl* GetControlByIndex( int idx );
   CBEMPUIControl* GetControlByPageAndID( CBEMPUIPage* pPage, UINT uiID );
   UINT            GetControlIDByIndex( int idx );

   BOOL PageHasActiveControls( CBEMPUIPage* pPage );

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   void SetupControlConditionDBIDOffsets( CBEMPUIPage* pPage, long lDBIDOffset );
};

extern CBEMPUIScreenData eScreenData;


///////////////////////////////////////////////////////////////
// CBEMPUIControl
///////////////////////////////////////////////////////////////

struct CBEMPUIControl
{
// Constructors
//   CBEMPUIControl();

// Attributes
   // Control Data
   CString  m_sBEMParam;
   UINT     m_uiCtrlID;
   UINT     m_uiCtrlType;     // Edit, Combo, Button, CheckBox, Radio...
   int      m_iX;
   int      m_iY;
   int      m_iHeight;
   int      m_iWidth;
   long     m_lValue;         // Radio: Value to set when radio button selected
                              // Edits: dec precision or max string length
                              // Spread: row height
// SAC 6/17/00 - added m_iFill* & m_iBound* for TDCT_Rect implementation
union{  int m_iFont;   int m_iBoundThickness;  };

   CString  m_sLbl;
   UINT     m_uiLblJust;
union{  int m_iLblDX;   int m_iFillRed;  };
union{  int m_iLblDY;   int m_iFillGreen;  };

   BOOL     m_bUnitDisp;
   UINT     m_uiUnitJust; 
union{  int m_iUnitDX;  int m_iFillBlue;  };
union{  int m_iUnitDY;  int m_iBoundRed;  };

   // Conditional display (existence) of UI controls
   CBEMCondition m_cDisplayCondition;
union{  int m_iLeftEraseX;   int m_iBoundGreen;  };
union{  int m_iRightEraseX;  int m_iBoundBlue;  };

   // Conditional editability of UI controls
   CBEMCondition m_cEditableCondition;

   CString  m_sErrorCheckRulelistName;  // SAC 5/21/01
// RW 11/4/02 - Added to allow for rulelist generated tooltip messages
   CString  m_sTooltipRulelistName;  // RW 11/4/01

   CString  m_sStatusMsg;

   // Other Control Data set by Init function
   long     m_lDBID;
   CBEMPUIPage* m_pPage;
   BOOL     m_bLabelRequiringRefresh;

   // Other Control Data set at runtime corresponding to current control state
   BOOL     m_bActive;

   // SAC 3/3/99 - Added 0-based BEMProc class instance index (set by Init function)
   int      m_iDBInstance;

   // SAC 3/3/99 - Added second DBID to allow display of referenced component data
   long     m_lDBID2;
	int		m_i1ChildIdx;	// SAC 5/28/14 - added to facilitate UI access to properties of CHILD objects

   int      m_iSpreadConfigIdx;   // SAC 6/5/00 - added to implement spreadsheet stuff

   int      m_iHelpGroupIdx;  // SAC 10/18/02

// Operations
   void InitControl( CBEMPUIPage* pPage, int iLine );

   BOOL ToggleControl();

   BOOL CanDisplay();
   BOOL IsEditable();

   BOOL HaveDisplayCondition();
   BOOL HaveEditableCondition();

   // SAC 3/2/99 - added to enable DBID offsets for a single page control to allow access to an array of values
   void SetupConditionDBIDOffsets( int iClassID, long lDBIDOffset );
};

inline BOOL CBEMPUIControl::HaveDisplayCondition()
   {  return (m_cDisplayCondition.Present());  }
inline BOOL CBEMPUIControl::HaveEditableCondition()
   {  return (m_cEditableCondition.Present());  }


///////////////////////////////////////////////////////////////
// CBEMPUIPage
///////////////////////////////////////////////////////////////

struct CBEMPUIPage
{
// Constructors
//   CBEMPUIPage();

// Attributes
   // Page Data
   CString  m_sBEMClass;
   int      m_iPageId;
   int      m_iModules;
   CString  m_sCaption;
   int      m_iNumCtrls;

   // Other Page Data set by Init function
   int      m_iFirstCtrlIdx;
   int      m_iLastCtrlIdx;
   int      m_iClassId;

// Operations
//   void InitPage( CBEMPUIPage* pPrevPage );
};


/////////////////////////////////////////////////////////////////////////////

extern void WriteLineToDC( CDC* pDC, BOOL bColor, int fromX, int fromY, int toX, int toY, int iThickness );
extern void WriteLineCtrlToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset=0 );
extern void WriteLabelToDC( CDC* pDC, CBEMPUIControl* pCtrl, long lCtrlDBIDOffset, int iYOffset=0 );
extern void WriteOpaqueTextToDC( CDC* pDC, int iX, int iY, UINT uiJustify, CString& sLabel );  // SAC 1/3/12
extern void WriteRectToDC( CDC* pDC, CBEMPUIControl* pCtrl, int iYOffset=0 );

/////////////////////////////////////////////////////////////////////////////

#endif
