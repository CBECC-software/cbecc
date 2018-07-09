/**********************************************************************
 *  Copyright (c) 2012-2018, California Energy Commission
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

#if !defined(BEMGRIDDIALOG_H__82C122E1_90B9_11D1_9002_0080C732DDC3__INCLUDED_)
#define BEMGRIDDIALOG_H__82C122E1_90B9_11D1_9002_0080C732DDC3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

//#ifndef __AFXWIN_H__
//	#error include 'stdafx.h' before including this file for PCH
//#endif
//#include "..\BEMProc\BEMProc.h"

#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDialogButtonBox>

class CMainFrame;
class BEMGridColumn;
class BEMGridMod;
class BEMGridComboBox;


/////////////////////////////////////////////////////////////////////////////
// BEMGrid

//#define  GDO_Dflt_FollowingEachMod   1
//#define  GDO_Dflt_EachTopicRefresh   2
//#define  GDO_Dflt_EachObjectRefresh  3
//#define  GDO_Dflt_OnDialogClose      4
//#define  GDO_Dflt_Never              5

class BEMGrid : public QTableWidget
{
	Q_OBJECT
// Construction
public:
	BEMGrid(QWidget *parent, CMainFrame* pMainFrm=NULL, QPixmap* pIcon=NULL, QFont* pFont=NULL);
	~BEMGrid();

// Data
	void initGrid( int iClass, int iTopic=0, int iNumCtrls=0, int iFirstCtrlIdx=0, int iSelObjectIdx=-1 );

	bool addColumn( QString sTitle, QString sToolTipMsg,
						long dbid, int propType, int width, int height, long decPrec,
						void* bemEditableCondition, void* bemDisplayCondition );
	void clearColumnData();
	void itemDisplayData(QTableWidgetItem *item, BEMGridColumn* pGC=NULL);
	int  getBEMObjectIndex( int row );

	BEMGridMod* addMod( int iRow, int iCol, QString qsData, BEMGridColumn* pGC=NULL, int iOccur=-1 );
	void clearModData();
	int  modSummary( int& iNumErrors, int& iNumWarnings );
	bool confirmMods();
	int  applyMods();
	bool isBeingInitialized()		{	return beingInitialized;  }

	void gridMessageBox( bool beep, QMessageBox::Icon icon, const QString &title, const QString &text,
								QMessageBox::StandardButtons buttons = QMessageBox::NoButton );
	QString GetPropertyString( BEMGridColumn* pGC, bool& bEditableCell, bool& bDisplayCell,
										int& iStatus, int& iError, int iOccur );
	void ClearComboboxCell();
	void CreateAndAssignTableWidgetItem( BEMGridColumn* pGC, QString qsData, bool bEditableCell,
														int iStatus, int row, int col, int iObjIdx );
	void SwitchCellToCombobox_IfAppropriate( int row, int col );
	void SwitchRowTitles( bool bInclNames );

	bool haveSelection();
	int  getSelectionBounds( int& maxRow, int& minRow, int& maxCol, int& minCol, int& numCells );
	bool copySelectionToClipboard();
	bool pasteSelectionFromClipboard();

	// 0-"Nothing"  1-"Modified Object"  (future? 2-"Object Family")  3-"Entire Model"
	void setDefaultOptionInp(  long data );
	void setDefaultOptionObj(  long data );
	void setDefaultOptionDone( long data );
	int  defaultSettingFollowingMod();
	int  defaultSettingAfterObjectChange();
	int  defaultSettingOnClose();

private slots:
	void itemChangedLocal(QTableWidgetItem *item);
	void cellActivatedLocal(int row, int column);
	void cellClickedLocal(int row, int column);
	void cellEnteredLocal(int row, int column);
	void horzScrollValueChanged();
	void cmbxIndexChanged(int index);
	void cmbxIndexChanged(const QString &text);

protected:
	void SwitchCellToCombobox(int row, int col, QString signal);
	void keyPressEvent(QKeyEvent *event);  // to enable clipboard copy/paste

	bool ObjectTypeIsCompatible( BEMGridColumn* pGC, int i1ClassID, int iObjIdx, int iCurObjIdx );
	void LoadComboBoxObjectNames( QComboBox* qcmbx, BEMGridColumn* pGC, int i1ClassID, int iObjIdx );
	void LoadComboBoxStrings(     QComboBox* qcmbx, BEMGridColumn* pGC, int iObjIdx );

// Implementation
protected:
	bool beingInitialized;
	bool rowHeadersInclNames;
	int idClass;
	int idTopic;
	int idxSelObject;
	std::vector<BEMGridColumn*> colData;
	std::vector<BEMGridMod*> modData;
	int numBEMModsSinceRefresh;

	QPixmap pxmIcon;
	QFont font;

	CMainFrame* mainFrm;

//	QColor* colGray;
	QBrush* brushGray;

	int cmbxRow;
	int cmbxCol;
	BEMGridComboBox* cmbx;

	QMessageBox* confirmMsgBox;

	// Options...
};


/////////////////////////////////////////////////////////////////////////////
// BEMGridComboBox

class BEMGridComboBox : public QComboBox
{
	Q_OBJECT
// Construction
public:
	BEMGridComboBox(QWidget *parent = Q_NULLPTR, long dbid=0, int objIdx =-1);
	//~BEMGridComboBox();

	void gridMessageBox( bool beep, QMessageBox::Icon icon, const QString &title, const QString &text,
								QMessageBox::StandardButtons buttons = QMessageBox::NoButton );

protected:
	void keyPressEvent(QKeyEvent *event);  // to enable clipboard copy/paste

//private slots:
//	void currIndexChanged(const QString &text);

// Implementation
protected:
	long lDBID;
	int  iObjIdx;
	BEMGrid* parentGrid;
};


/////////////////////////////////////////////////////////////////////////////
// BEMGridColumn

#define  GCMBX_SYMBOL  1
#define  GCMBX_OBJECT  2
#define  GCMBX_PARENT  3

class BEMGridColumn
{
// Construction
public:
	BEMGridColumn( QString sTitle, QString sToolTipMsg,
						long dbid, int propType, int width, int height, long decPrec,
						void* bemEditableCondition, void* bemDisplayCondition );

// Data
	QString getTitle()			{	return qsTitle;   }
	QString getToolTipMsg()		{	return qsToolTipMsg;  }
	long    getDBID()				{	return lDBID;     }
	int     getPropertyType()	{	return iPropType; }
	int     getWidth()			{	return iWidth;    }
	int     getHeight()			{	return iHeight;   }
	long    getDecPrec()			{	return lDecPrec;  }
	void*   getConditionEditable() 	{  return pBEMEditableCondition;  }
	void*   getConditionDisplay() 	{  return pBEMDisplayCondition;   }

// Implementation
protected:
	QString  qsTitle;
	QString  qsToolTipMsg;
	long lDBID;
	int  iPropType;
	int  iWidth;
	int  iHeight;
	long lDecPrec;
	void* pBEMEditableCondition;
	void* pBEMDisplayCondition;

public:
	int  cmbxMode;		// GCMBX_SYMBOL, GCMBX_OBJECT, GCMBX_PARENT
	bool cmbxIncludeNone;
	std::vector<int>  cmbxObjClassID;
	std::vector<long> cmbxObjTypeDBID;
	std::vector<long> cmbxObjTypeValue;
};


/////////////////////////////////////////////////////////////////////////////
// BEMGridMod

#define  GM_InvalidDBID_NoClass               1
#define  GM_NotEditable_BEMBase               2
#define  GM_NotEditable_Condition             3
#define  GM_InvalidInput_NotFloat             4
#define  GM_InvalidInput_NotInteger           5
#define  GM_InvalidInput_NotEnum              6
#define  GM_InvalidInput_NotObject            7
#define  GM_InvalidInput_ObjNotCompat         8
#define  GM_InvalidInput_RangeError           9
#define  GM_InvalidInput_ParentNotSpecified  10
#define  GM_InvalidInput_ParentNotFound      11
#define  GM_InvalidInput_ParentNotCompat     12

#define  GM_MinWarning		21
#define  GM_RangeWarning	21

class BEMGridMod
{
// Construction
public:
	BEMGridMod( int iRow, int iCol, BEMGridColumn* pGC, QString qsData, int iOccur );

	QString getDescription();
	bool apply( QString& sSetMsg );

	int     getRow()			{	return row;			}
	int     getCol()			{	return col;			}
	int     getSetKey()		{	return iSetKey;	}
	QString getSetMsg()		{	return sSetMsg;	}
	bool    getIgnoreMod()	{	return bIgnoreMod;	}
	long    getDBID()			{	return lDBID;		}
	int     getObjIdx()		{	return iObjIdx;	}
	BEMGridColumn* getGridCol()	{	return pGridCol;  }
	bool    bemModified()	{	return (bModApplied && iToggleStatusTo < 0);   }

// Data
//	QString getTitle()			{	return qsTitle;   }
//	long    getDBID()				{	return lDBID;     }
//	int     getPropertyType()	{	return iPropType; }

// Implementation
protected:
	int row;
	int col;
	BEMGridColumn* pGridCol;
	long lDBID;
	int iObjIdx;
	QString sNewData;
	QString sPrevData;
	bool bIgnoreMod;
	int iToggleStatusTo;
	bool bEditableBEM;
	bool bEditableCondition;
	int iPrevStatus;
	int iNewParentClass;
	int iSetKey;
	QString sSetMsg;
	bool bModApplied;
};


/////////////////////////////////////////////////////////////////////////////
// BEMGridOptionsDialog dialog

class BEMGridOptionsDialog : public QDialog
{
	Q_OBJECT
// Construction
public:
	BEMGridOptionsDialog(BEMGrid *pGrid, QWidget *parent = 0);

private slots:
	void updateDefaultAfterMod();
	void updateDefaultAfterObject();
	void updateDefaultClosingDialog();

// Implementation
private:

	BEMGrid *grid;

	QLabel *lblFilter;
	QLabel *lblFilterProperty;
	QLabel *lblFilterValue;
	QComboBox *cbFilterProperty;     
	QComboBox *cbFilterCondition;  
	QComboBox *cbFilterSelection;  
	QTextEdit *txtFilterValue;
	QLabel *lblFilterSpace;

	QLabel *lblDefaults;
	QLabel *lblDfltAfterMod;
	QLabel *lblDfltAfterObject;
	QLabel *lblDfltClosingDialog;
	QComboBox *cbDfltAfterMod;     
	QComboBox *cbDfltAfterObject;  
	QComboBox *cbDfltClosingDialog;
	QLabel *lblDfltSpace;

	QDialogButtonBox *btns;

	QFont font;
	QFont fontBold;

	bool uiBeingInitialized;
};


/////////////////////////////////////////////////////////////////////////////
// BEMGridDialog dialog

class BEMGridDialog : public QDialog
{
	Q_OBJECT
// Construction
public:
	BEMGridDialog(CMainFrame* pMainFrm=NULL, int iBEMClass = -1, int iOccur = -1, QWidget *parent = 0);

// Dialog Data
	int getObjectType();
	int getTopic();

//	bool defaultModelEachMod()			{	return (modelDefaultingOption == GDO_Dflt_FollowingEachMod);  }
//	bool defaultModelTopicRefresh()	{	return (modelDefaultingOption <= GDO_Dflt_EachTopicRefresh);  }
//	bool defaultModelObjectRefresh()	{	return (modelDefaultingOption <= GDO_Dflt_EachObjectRefresh);  }
//	bool defaultModelDialogClose()	{	return (modelDefaultingOption <= GDO_Dflt_OnDialogClose);  }

private slots:
	void updateObjectType();
	void updateTopic();
//	void menuPressed();
	void aboutToShowOptionsMenu();
	void triggeredOption(QAction *action);

protected:
	virtual void closeEvent(QCloseEvent *e);

// Implementation
private:

	QComboBox *createComboBox();
	QPushButton *createIconButton(int iconID);  //, const char *member);
	BEMGrid *createBEMGrid();

//	void finished(int result);

	void initObjectTypeList( int bemClass );
	void initTopicList( int idx );

//	int bemClass;
	int gridBEMClass;
	int gridTopic;

//	QLabel *lblObjectType;
//	QLabel *lblTopic;
	QComboBox *cbObjectType;
	QComboBox *cbTopic;
	QPushButton *btnMenu;
	BEMGrid *grid;
	QPixmap pxmIcon;
	QPixmap pxmMenuIcon;

	QMenu *menuOptions;
	QAction *actionCopy;
	QAction *actionPaste;
	QAction *actionRestoreOrder;
	QAction *actionOptions;

	CMainFrame* mainFrm;

	QFont font;
	QFont fontBold;

	std::vector<int> topicNumControls;
	std::vector<int> topicFirstCtrlIdx;
	bool refreshingTopicList;

	// Options...
//	int modelDefaultingOption;
};

#endif // !defined(BEMGRIDDIALOG_H__82C122E1_90B9_11D1_9002_0080C732DDC3__INCLUDED_)
