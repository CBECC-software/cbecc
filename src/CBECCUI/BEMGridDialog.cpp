// BEMGridDialog.cpp : implementation file
//
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

#include "stdafx.h"
#include "ComplianceUI.h"
#include "..\BEMProc\BEMClass.h"
#include "..\BEMProc\BEMPropertyType.h"
#include "..\BEMProc\BEMProperty.h"
#include "..\BEMProc\BEMProc.h"
#include "BEMGridDialog.h"

#include "CUIGlobl.h"
#include "MainFrm.h"
#include "ComplianceUIDoc.h"
#include "..\BEMProcUI\BEMProcUIX.h"

#include <QtWidgets/QGridLayout>
#include <QtWinExtras/QtWin>
#include <QtGui/QKeyEvent>
#include <QtGui/QClipboard>
#include <QtGui/QBrush>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char BASED_CODE szNone[] = "- none -";


/////////////////////////////////////////////////////////////////////////////
// BEMGridColumn

BEMGridColumn::BEMGridColumn( QString sTitle, QString sToolTipMsg,
						long dbid, int propType, int width, int height, long decPrec,
						void* bemEditableCondition, void* bemDisplayCondition )
{	qsTitle      = sTitle;
	qsToolTipMsg = sToolTipMsg;
	lDBID     = dbid;
	iPropType = propType;
	iWidth    = width;
	iHeight   = height;
	lDecPrec  = decPrec;
	pBEMEditableCondition = bemEditableCondition;
	pBEMDisplayCondition  = bemDisplayCondition;

	// Set cmbxMode
	cmbxMode = 0;
	int iPropID = BEMPX_GetPropertyID( dbid );
	int iArrID  = BEMPX_GetArrayID(	  dbid );
	cmbxIncludeNone = FALSE;
	if ( dbid > 0 && iPropID == 0 )
	{	if (iArrID == BEM_PARAM0_PARENT)
			cmbxMode = GCMBX_PARENT;
	}
	else if (propType == BEMP_Obj)
	{	cmbxMode = GCMBX_OBJECT;
		cmbxIncludeNone = TRUE;
		int iError, iObjCls;
		// handle an ARRAY of m_lObjTypeDBIDs, since there may be multiple possible assigned object types
		BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( dbid, iError );
		if (iError == 0 && pPropType)
			for (iObjCls=0; iObjCls<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjCls++)
			{	if (pPropType->getObj1ClassIdx(iObjCls) > 0 || pPropType->getObjTypeValue(iObjCls) != 0)
				{	cmbxObjClassID.push_back(	 pPropType->getObj1ClassIdx(iObjCls) );
					cmbxObjTypeDBID.push_back(  pPropType->getObjTypeDBID( iObjCls) ); 
					cmbxObjTypeValue.push_back( pPropType->getObjTypeValue(iObjCls) );
				}
			}						ASSERT( cmbxObjClassID.size() > 0 );

		// prevent "- none -" from appearing in lists where the input is required
		int iCompDataType = BEMPX_GetCompDataType( dbid );
		if (iCompDataType == BEMD_Compulsory || iCompDataType == BEMD_Required)
			cmbxIncludeNone = FALSE;
	}
	else if (propType == BEMP_Sym)
		cmbxMode = GCMBX_SYMBOL;
	//	// flag value to override default availability "None", "Create" & perhaps other options
	//	if (cmbxIncludeNone && m_dwListOptionFlag & PREVENT_ENTRY_NONE)
	//		cmbxIncludeNone = FALSE;
	//	// prevent excessive list re-loading for combos w/ very long lists
	//	if (m_lDependentDBID > 0)
	//	{
	//		long lDBID = GetParent()->SendMessage( WM_CTRLIDTODBID, (UINT) m_lDependentDBID );
	//		if (lDBID > 0  &&  BEMPX_GetClassID( lDBID ) > 0)
	//			m_lDependentDBID = lDBID;
	//	}
}


/////////////////////////////////////////////////////////////////////////////
// BEMGridMod

static QLocale qtLocale;

BEMGridMod::BEMGridMod( int iRow, int iCol, BEMGridColumn* pGC, QString qsData, int iOccur )
{	row = iRow;
	col = iCol;
	pGridCol = pGC;
	sNewData = qsData;
	iObjIdx = iOccur;
	lDBID = pGC->getDBID();
	int iClass = BEMPX_GetClassID( lDBID );
	bEditableBEM =  BEMPX_GetCompIsEditable( lDBID );
	bEditableCondition = BEMPUIX_BEMConditionMissingOrTrue( pGC->getConditionEditable(), iClass, iOccur );
	int iSpecVal, iError, iPrec = (pGC->getPropertyType() == BEMP_Flt ? pGC->getDecPrec() : 0);
	sPrevData = BEMPX_GetStringAndStatus( lDBID, iPrevStatus, iSpecVal, iError, iOccur /*iOccur*/, BEMO_User,
															-1 /*iBEMProcIdx*/, TRUE /*bAddCommas*/, iPrec );  //, const char* pszDefault=NULL, long lDBID2=0 );
	if (sPrevData.isEmpty() && pGC->cmbxMode > 0 && pGC->cmbxIncludeNone)
		sPrevData = szNone;
	iSetKey = iNewParentClass = 0;
	bIgnoreMod = false;
	iToggleStatusTo = -1;
	bModApplied = false;

	BEMPropertyType* pPropType = NULL;
	if (sNewData.isEmpty() &&
		 (sPrevData.isEmpty() || !bEditableCondition))
		bIgnoreMod = true;	// => DO NOT bother modifiying BEM data
	else if (!sNewData.isEmpty() && !sPrevData.isEmpty() &&
				!sNewData.compare( sPrevData ))
	{	// new data identical to old...
		if (!bEditableBEM)
			bIgnoreMod = true;	// => DO NOT bother modifiying BEM data
		else
			iToggleStatusTo = BEMS_UserDefined;
	}
	else
	{	int iError;		QString sErrMsgEnd;
		BEMClass* pClass = BEMPX_GetClass( iClass, iError );			assert( pClass );
		if (pClass == NULL)
		{	iSetKey = GM_InvalidDBID_NoClass;
			sSetMsg = QString( "Invalid class for DBID %1." ).arg( QString::number( lDBID ) );
		}
		else if (!bEditableBEM)
		{	iSetKey = GM_NotEditable_BEMBase;
			sErrMsgEnd = "cannot be set due to classification of this property in the ruleset database.";
		}
		else if (!bEditableCondition)
		{	iSetKey = GM_NotEditable_Condition;
			sErrMsgEnd = "cannot be set due to editable condition in screen definitions not met.";
		}
		else if (pGC->cmbxMode == GCMBX_PARENT)
		{	BEMObject *pSelObj = NULL;
			if (sNewData.isEmpty())
				iSetKey = GM_InvalidInput_ParentNotSpecified;
			else
			{	BEMObject *pParObj = NULL;
				for (int iPT=0; (pParObj == NULL && iPT < BEM_MAX_PARENT_TYPES); iPT++)
				{	int iParCls = pClass->getParentType(iPT)+1;
					if (iParCls > 0)
						pParObj = BEMPX_GetObjectByNameQ( iParCls, iError, sNewData );
				}
				if (pParObj == NULL)
				{	pSelObj = BEMPX_GetObjectByNameQ( -1, iError, sNewData );
					if (pSelObj)
						iSetKey = GM_InvalidInput_ParentNotCompat;
					else
						iSetKey = GM_InvalidInput_ParentNotFound;
			}	}
			if (iSetKey > 0)
			{	QString sParTypes;
				for (int iPT=0; iPT < BEM_MAX_PARENT_TYPES; iPT++)
				{	int iParCls = pClass->getParentType(iPT)+1;
					if (iParCls > 0)
					{	BEMClass* pParClass = BEMPX_GetClass( iParCls, iError );			assert( pParClass );
						if (iPT > 0)
							sParTypes += '/';
						sParTypes += pParClass->getShortName();
				}	}
				switch (iSetKey)
				{	case  GM_InvalidInput_ParentNotSpecified  :  sErrMsgEnd = QString( "not specified - must be object of type %1." ).arg( sParTypes );   break;
					case  GM_InvalidInput_ParentNotFound      :  sErrMsgEnd = QString( "object not found - must be object of type %1." ).arg( sParTypes );   break;
					case  GM_InvalidInput_ParentNotCompat     :  sErrMsgEnd = QString( "%1 object not compatible - must be object of type %2." ).arg( pSelObj->getClass()->getShortName(), sParTypes );   break;
			}	}
		}
		else if (pGC->getPropertyType() == BEMP_Int || pGC->getPropertyType() == BEMP_Flt)
		{	double dData = -999;		bool bNumberOK=true;
			if (pGC->getPropertyType() == BEMP_Int)
				dData = (double) qtLocale.toInt( sNewData, &bNumberOK );
			else
				dData = qtLocale.toDouble( sNewData, &bNumberOK );
			if (!bNumberOK)
			{	if (pGC->getPropertyType() == BEMP_Int)
				{	iSetKey = GM_InvalidInput_NotInteger;
					sErrMsgEnd = "cannot be interpretted as an integer value.";
				}
				else
				{	iSetKey = GM_InvalidInput_NotFloat;
					sErrMsgEnd = "cannot be interpretted as an floating point value.";
			}	}
			else
			{	int iRangeRetVal = BEMPX_PerformRangeCheck( lDBID, dData, TRUE /*bSilent*/, &sErrMsgEnd, iOccur ); 
				if (iRangeRetVal == 1)
				{	iSetKey = GM_InvalidInput_RangeError;
					assert( !sErrMsgEnd.isEmpty() );
				}
				else if (iRangeRetVal > 0)
				{	iSetKey = GM_RangeWarning;		// 2-Warning, 3-Message
					assert( !sErrMsgEnd.isEmpty() );
				}
				if (iRangeRetVal > 0 && sErrMsgEnd.indexOf("Value being") == 0)
				{	int idxFirstSentenceEnd = sErrMsgEnd.indexOf(".  ");   // strip off leading sentence echoing value being checked...
					if (idxFirstSentenceEnd > 0)
						sErrMsgEnd = sErrMsgEnd.right( sErrMsgEnd.length()-idxFirstSentenceEnd-3 );
			}	}
		}
		else
		{	switch (pGC->getPropertyType())
			{	case  BEMP_Sym  :	{	int iNumSyms;
											BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, lDBID );			ASSERT( pSymDepSet );
											if (pSymDepSet)
											{	long lSymVal = pSymDepSet->GetSymbolValue( (const char*) sNewData.toLatin1().constData() );
												if (lSymVal == -999)
												{	iSetKey = GM_InvalidInput_NotEnum;
													sErrMsgEnd = "does not match any valid enumeration selection.";
											}	}
										}	break;
				case  BEMP_Obj  :	{	pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
											BEMObject* pObj = NULL;
											int iObjClsIdx = 0;
											for (; (pObj==NULL && iObjClsIdx<BEM_MAX_PROPTYPE_OBJREFCLASSES); iObjClsIdx++)  // SAC 6/14/12 - revised to handle ARRAY of compatible referenced object classes
											{	if (pPropType->getObj1ClassIdx(iObjClsIdx) > 0)
													pObj = BEMPX_GetObjectByNameQ( pPropType->getObj1ClassIdx(iObjClsIdx), iError, sNewData );
											}
											if (pObj == NULL)
											{	QString sObjTypes;
												for (iObjClsIdx=0; iObjClsIdx<BEM_MAX_PROPTYPE_OBJREFCLASSES; iObjClsIdx++)
												{	if (pPropType->getObj1ClassIdx(iObjClsIdx) > 0)
													{	BEMClass* pObjClass = BEMPX_GetClass( pPropType->getObj1ClassIdx(iObjClsIdx), iError );		assert( pObjClass );
														if (iObjClsIdx > 0)
															sObjTypes += '/';
														sObjTypes += pObjClass->getShortName();
												}	}
												pObj = BEMPX_GetObjectByNameQ( -1, iError, sNewData );
												if (pObj)
												{	iSetKey = GM_InvalidInput_ObjNotCompat;
													sErrMsgEnd = QString( "%1 object not compatible - must be object of type %2." ).arg( pObj->getClass()->getShortName(), sObjTypes );
												}
												else
												{	iSetKey = GM_InvalidInput_NotObject;
													sErrMsgEnd = QString( "object not found - must be object of type %1." ).arg( sObjTypes );
											}	}
										}	break;
			//	case  BEMP_Str or BEMP_QStr 5	 - no checks
			}
		}

		if (iSetKey > GM_InvalidDBID_NoClass)
			sSetMsg = QString( "%1 setting %2 to '%3':  %4" ).arg(
										(iSetKey < GM_MinWarning ? "Error" : "Warning"), getDescription(), sNewData, sErrMsgEnd );
	}
//	int  cmbxMode;		// GCMBX_SYMBOL, GCMBX_OBJECT, GCMBX_PARENT
}

QString BEMGridMod::getDescription()
{	int iError;
	int iClass   = BEMPX_GetClassID(    lDBID );
	int iPropIdx = BEMPX_GetPropertyID( lDBID );
	int iArrIdx  = BEMPX_GetArrayID(    lDBID );
	QString sPT;
	if (iPropIdx < 1)
	{	switch (iArrIdx)
		{	case  BEM_PARAM0_NAME   :  sPT = "Name";				break;
			case  BEM_PARAM0_PARENT :  sPT = "Parent";			break;
			default                 :  sPT = "unknown0prop";	break;
	}	}
	else
	{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( lDBID, iError );
		sPT = (pPropType ? pPropType->getShortName() : "Property");
		if (pPropType && pPropType->getNumValues() > 1)
			sPT += QString( "[%1]" ).arg( QString::number( iArrIdx ) );
	}
	BEMClass*  pClass  = BEMPX_GetClass( iClass, iError );						assert( pClass );
	BEMObject* pLocObj = BEMPX_GetObjectByClass( iClass, iError, iObjIdx );
	return QString( "row %1 (%2 '%3'), column %4 (%5)" ).arg(
								QString::number(row+1), (pClass ? pClass->getShortName() : "Object"),
								(pLocObj ? pLocObj->getName() : ""), QString::number(col+1), sPT );
}

bool BEMGridMod::apply( QString& sSetMsg )
{	bModApplied = false;
	if (bIgnoreMod)
	{	// do nothing
	}
	else if (iToggleStatusTo >= 0)
	{	int iSDS = BEMPX_SetDataStatus( lDBID, iObjIdx, (BEM_PropertyStatus) iToggleStatusTo );
		if (iSDS < 0)
			sSetMsg = QString( "Error setting %1 data status to %2 (error code %3)." ).arg(
										getDescription(), QString::number(iToggleStatusTo), QString::number(iSDS) );
		else
			bModApplied = true;
	}
	else if (!sNewData.isEmpty())
	{	int iPropIdx = BEMPX_GetPropertyID( lDBID );
		int iArrIdx  = BEMPX_GetArrayID(    lDBID );
		if (iPropIdx < 1 && iArrIdx == BEM_PARAM0_NAME)
		{	if (BEMPX_GetComponentByNameQ( sNewData, FALSE, 0, TRUE ) != NULL)
				sSetMsg = QString( "Error setting %1 to '%2': component name not unique." ).arg(
											getDescription(), sNewData );
		}
		if (sSetMsg.isEmpty())
		{	int iSetDataRetVal = -99;			bool bNumberOK=true;
			if (pGridCol->getPropertyType() == BEMP_Int)
			{	long lData = qtLocale.toInt( sNewData, &bNumberOK );
				if (bNumberOK)
					iSetDataRetVal = BEMPX_SetBEMData( lDBID, BEMP_Int, (void*) &lData, BEMO_User, iObjIdx );
			}
			else if (pGridCol->getPropertyType() == BEMP_Flt)
			{	double dData = qtLocale.toDouble( sNewData, &bNumberOK );
				if (bNumberOK)
					iSetDataRetVal = BEMPX_SetBEMData( lDBID, BEMP_Flt, (void*) &dData, BEMO_User, iObjIdx );
			}
			else
				iSetDataRetVal = BEMPX_SetBEMData( lDBID, BEMP_QStr, (void*) &sNewData, BEMO_User, iObjIdx );
			if (iSetDataRetVal < 0)
				sSetMsg = QString( "Error setting %1 to '%2' (error code %3)." ).arg(
											getDescription(), sNewData, QString::number(iSetDataRetVal) );
			else
				bModApplied = true;
	}	}
	else
	{	// redefault data where input string is empty
		int iPropIdx = BEMPX_GetPropertyID( lDBID );
		int iArrIdx  = BEMPX_GetArrayID(    lDBID );
		if (iPropIdx < 1 && iArrIdx == BEM_PARAM0_NAME)
			sSetMsg = QString( "Error setting %1 to <blank>: object name cannot be zero length." ).arg( getDescription() );
		else  if (iPropIdx < 1 && iArrIdx == BEM_PARAM0_NAME)
			sSetMsg = QString( "Error setting %1 to <blank>: parent object must be assigned." ).arg( getDescription() );
		else
		{	int iError;
			BEMPX_DefaultProperty( lDBID, iError, iObjIdx );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			bModApplied = true;
	}	}

//			if (sData.length() > 0)
//			{
//				// SET data to BEMBase
//				int iRangeViolation = RangeCheckViolation( pGC->getDBID(), iObjIdx, pGC->getPropertyType(), sData, FALSE /*bSilent*/, NULL /*QString**/ );  // will display error/warning/message
//				// prevent setting values which cause RANGE_ERRORs
//				if (iRangeViolation == RANGE_ERROR)
//					itemDisplayData( item, pGC );
//				else
//				{
//					void* pData = NULL;
//					long lData;
//					double fData;
//					int iDataType = pGC->getPropertyType();
//					if (iDataType == BEMP_Int)
//					{  lData = BEMPX_StringToLong( sData.toLatin1().constData() ); 
//						pData = &lData;
//					}
//					else if (iDataType == BEMP_Flt)
//					{  fData = BEMPX_StringToFloat( sData.toLatin1().constData() );
//						pData = &fData;
//					}
//					else
//					{
//						iDataType = BEMP_QStr;
//						pData = (void*) &sData;
//	
//			//			// set flag to update frame title if project name modified
//			//			if (slProjNameDBID == 0)
//			//				slProjNameDBID = BEMPX_GetDatabaseID( "Proj:Name" );
//			//			if (m_lUseDBID == slProjNameDBID)
//			//				bUpdateFrameTitle = TRUE;
//
//						// prevent storage of names which are not unique within user and userlib components
//						if (iArray == BEM_PARAM0_NAME)
//						{
//							if (/*newStr != m_sCurrStr  &&*/  BEMPX_GetComponentByNameQ( sData, FALSE, 0, TRUE ) != NULL)
//							{	pData = NULL;
//								gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString(szErrNameNotUnique) );
//							}
//					}	}
//	
//					if (pData != NULL)
//						iSetDataRetVal = BEMPX_SetBEMData( pGC->getDBID(), iDataType, pData, BEMO_User, iObjIdx );
//					else
//						itemDisplayData( item, pGC );
//				}
//			}
//			else
//			{	// BLAST BEMBase data
//				if (iArray == BEM_PARAM0_NAME)
//				{	gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString(szErrZeroLengthName) );
//					itemDisplayData( item, pGC );
//				}
//				else
//				{	BEMPX_DefaultProperty( pGC->getDBID(), iError, iObjIdx );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
//					iSetDataRetVal = 0;
//				}
//			}

	return bModApplied;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// BEMGrid

// dark gray sample
//		"QWidget {"
//		"    background-color: #333333;"
//		"    color: #fffff8;"
//		"}"
//		"QHeaderView::section {"
//		"    background-color: #646464;"
//		"    padding: 4px;"
//		"    border: 1px solid #fffff8;"
//		"    font-size: 14pt;"
//		"}"
//		""
//		"QTableWidget {"
//		"    gridline-color: #fffff8;"
//		"    font-size: 12pt;"
//		"}"
//		""
//		"QTableWidget QTableCornerButton::section {"
//		"    background-color: #646464;"
//		"    border: 1px solid #fffff8;"
//		"}";

static const char* pszStyleSheet = 
"QWidget {"
"    background-color: white;"
"    color: black;"
"}"
"QHeaderView::section {"
"    background-color: lightGray;"
"    color: #0f0f0f;"
"    padding: 3px;"
//"    border: 1px solid darkGray;"
"    border: 1px solid darkGray;"
"    font-size: 9pt;"
"}"
"QTableWidget {"
//"    background-color: lightGray;"
"    gridline-color: gray;"
"    alternate-background-color: #fffff0;"
"    font-size: 9pt;"
"}"
"QTableWidget QTableCornerButton::section {"
"    background-color: lightGray;"
"    border: 1px solid darkGray;"
"}"

"QScrollBar:horizontal {"
"    border: 1px solid grey;"  // 2px solid grey;"
"    background: lightGray;"   // #32CC99;"
"    height: 18px;"
"    margin: 0px 19px 0 19px;"
"}"
"QScrollBar::handle:horizontal {"
"    background: white;"
"    min-width: 20px;"
"}"
"QScrollBar::add-line:horizontal {"
"    border: 1px solid grey;"
"    background: lightGray;"   // #32CC99;"
"    width: 18px;"
"    subcontrol-position: right;"
"    subcontrol-origin: margin;"
"}"
"QScrollBar::sub-line:horizontal {"
"    border: 1px solid grey;"
"    background: lightGray;"   // #32CC99;"
"    width: 18px;"
"    subcontrol-position: left;"
"    subcontrol-origin: margin;"
"}"
//"QScrollBar:left-arrow:horizontal"
//"{"
//"  image: url(:/BarIcon/Icons/leftarrow.png);"
//"}"
//"QScrollBar::right-arrow:horizontal "
//"{"
//"  image: url(:/BarIcon/Icons/rightarrow.png);"
//"}"
//"QScrollBar:left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
//"    border: 2px solid grey;"
//"    width: 4px;"
//"    height: 4px;"
//"    background: white;"
//"}"
//"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
//"    background: none;"
//"}"

"QScrollBar:vertical {"
"    border: 1px solid grey;"
"    background: lightGray;"
"    width: 18px;"
"    margin: 19px 0px 19px 0px;"
"}"
"QScrollBar::handle:vertical {"
"    background: white;"
"    min-height: 15px;"
"}"
"QScrollBar::add-line:vertical {"
"    border: 1px solid grey;"
"    background: lightGray;"
"    height: 18px;"
"    subcontrol-position: bottom;"
"    subcontrol-origin: margin;"
"}"
"QScrollBar::sub-line:vertical {"
"    border: 1px solid grey;"
"    background: lightGray;"
"    height: 18px;"
"    subcontrol-position: top;"
"    subcontrol-origin: margin;"
"}"
"QPushButton {"
"    border: none;"    // 2px solid #8f8f91;"
//"    border-radius: 6px;"
//"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
//"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);"
//"    min-width: 80px;"
"}"
//"QPushButton:pressed {"
//"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
//"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);"
//"}"
"QPushButton:flat {"
"    border: none; /* no border for a flat push button */"
"}"
"QPushButton:default {"
"    border-color: black;"  // navy; /* make the default button prominent */"
"}";


BEMGrid::BEMGrid(QWidget *parent, CMainFrame* pMainFrm, QPixmap* pIcon, QFont* pFont)
	: QTableWidget(parent)
{
	beingInitialized = false;
	idClass = -1;
	idTopic = -1;
	idxSelObject = -1;
	if (pIcon)
		pxmIcon = *pIcon;
	if (pFont)
		font = *pFont;
	else
	{	font.setFamily( "Verdana" );
		font.setPointSize( 9 );
	}
	mainFrm = pMainFrm;
	confirmMsgBox = NULL;

//	colGray   = new QColor( 128, 128, 128 );
//	brushGray = new QBrush( *colGray );
	brushGray = new QBrush( Qt::gray );

	rowHeadersInclNames = false;
	cmbxRow = cmbxCol = -1;
	cmbx = NULL;

	// Options...

	setAlternatingRowColors(true);
	setStyleSheet( pszStyleSheet );

	connect( this, SIGNAL(itemChanged(QTableWidgetItem*)),
				this, SLOT(itemChangedLocal(QTableWidgetItem*)));
	connect( this, SIGNAL(cellActivated(int,int)),
				this, SLOT(cellActivatedLocal(int,int)));
	connect( this, SIGNAL(cellClicked(int,int)),
				this, SLOT(cellClickedLocal(int,int)));
	connect( this, SIGNAL(cellEntered(int,int)),
				this, SLOT(cellEnteredLocal(int,int)));
	connect( horizontalScrollBar(), SIGNAL(valueChanged(int)),
				this, SLOT(horzScrollValueChanged()));


//    //![assignModel]
//    m_view->setModel(m_model);
//    //![assignModel]
//
//    m_view->setSelectionModel(new QItemSelectionModel(m_model, m_model));
//    QObject::connect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::selectionChanged);



}

BEMGrid::~BEMGrid()
{	clearColumnData();
	clearModData();
	delete brushGray;
	if (cmbxRow >= 0 && cmbxCol >= 0 && cmbx)
		delete cmbx;
	if (confirmMsgBox)
		delete confirmMsgBox;
}


void BEMGrid::setDefaultOptionInp(  long data )
{	elDefaultOptionInp  = data;
	BEMPX_SetBEMData( elDBID_Proj_DefaultOptionInp , BEMP_Int, (void*) &elDefaultOptionInp );
}
void BEMGrid::setDefaultOptionObj(  long data )
{	elDefaultOptionObj  = data;
	BEMPX_SetBEMData( elDBID_Proj_DefaultOptionObj , BEMP_Int, (void*) &elDefaultOptionObj );
}
void BEMGrid::setDefaultOptionDone( long data )
{	elDefaultOptionDone = data;
	BEMPX_SetBEMData( elDBID_Proj_DefaultOptionDone, BEMP_Int, (void*) &elDefaultOptionDone );
}


//void MainWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
//{
//    Q_UNUSED(deselected);
//    bool value = selected.count();
//    m_removeButton->setEnabled(value);
//    m_toggleButton->setEnabled(value);
//}


bool BEMGrid::addColumn( QString sTitle, QString sToolTipMsg,
						long dbid, int propType, int width, int height, long decPrec,
						void* bemEditableCondition, void* bemDisplayCondition )
{	bool bRetVal = false;
	BEMGridColumn* pGridCol;
	try
	{	pGridCol = new BEMGridColumn( sTitle, sToolTipMsg,
									dbid, propType, width, height, decPrec,
									bemEditableCondition, bemDisplayCondition );
		if (pGridCol)
		{	colData.push_back( pGridCol );
			bRetVal = true;
	}	}
	catch( ... ) {
		assert( false );  // sErrMsg.sprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
	}
	return bRetVal;
}

void BEMGrid::clearColumnData()
{	for (int i=colData.size()-1; i>=0; i--)
	{	BEMGridColumn* pGridCol = colData[i];
		if (pGridCol)
			delete pGridCol;
	}
	colData.clear();
}

BEMGridMod* BEMGrid::addMod( int iRow, int iCol, QString qsData, BEMGridColumn* pGC, int iOccur )
{	BEMGridMod* pMod = NULL;
	if (pGC == NULL && iCol >= 0 && iCol < (int) colData.size())
		pGC = colData[iCol];
	ASSERT( iOccur>=0 );
	//if (iOccur < 0)
	//	iOccur = iRow;
	try
	{	pMod = new BEMGridMod( iRow, iCol, pGC, qsData, iOccur );
		if (pMod)
			modData.push_back( pMod );
	}
	catch( ... ) {
		assert( false );  // sErrMsg.sprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
	}
	return pMod;
}

void BEMGrid::clearModData()
{	for (int i=modData.size()-1; i>=0; i--)
	{	BEMGridMod* pMod = modData[i];
		if (pMod)
			delete pMod;
	}
	modData.clear();
}

int BEMGrid::modSummary( int& iNumErrors, int& iNumWarnings )
{	int iNumMods = 0;
	iNumErrors = iNumWarnings = 0;
	for (int i=0; i < (int) modData.size(); i++)
	{	BEMGridMod* pMod = modData[i];
		if (pMod && !pMod->getIgnoreMod())
		{	iNumMods++;
			if (pMod->getSetKey() > 0 && pMod->getSetKey() < GM_MinWarning)
				iNumErrors++;
			else if (pMod->getSetKey() >= GM_MinWarning)
				iNumWarnings++;
	}	}
	return iNumMods;
}

bool BEMGrid::confirmMods()
{	bool confirmed = false;
	int iNumErrors, iNumWarnings;
	int iNumMods = modSummary( iNumErrors, iNumWarnings );
	QString qsMsg;
	bool includeApplyBtn = true;
	if (iNumErrors > 0 && iNumErrors == iNumMods)
	{	includeApplyBtn = false;
		if (iNumMods > 1)
			qsMsg = QString( "None of the %1 modified values can be posted to the building." ).arg( QString::number(iNumMods) );
		else
			qsMsg = QString( "The modified value cannot be posted to the building." );
	}
	else if (iNumWarnings > 0 && iNumWarnings == iNumMods)
	{	if (iNumMods > 1)
			qsMsg = QString( "Each of the %1 modified values resulted in warning messages." ).arg( QString::number(iNumMods) );
		else
			qsMsg = QString( "The modified value resulted in a warning message.\n\n%1" ).arg( modData[0]->getSetMsg() );
	}
	else if (iNumErrors > 0 && iNumWarnings > 0)
		qsMsg = QString( "The %1 values being posted to the building include %2 error(s) and %3 warning(s).\n"
							  "If confirmed, all values other than those classified as errant will be posted to the building.\n\n"
							  "Press 'Apply' to post the %4 non-errant value(s) to the building." ).arg(
								QString::number(iNumMods), QString::number(iNumErrors), QString::number(iNumWarnings), QString::number(iNumMods-iNumErrors) );
	else if (iNumErrors > 0)
		qsMsg = QString( "The %1 values being posted to the building include %2 error(s).\n"
							  "If confirmed, all values other than those classified as errant will be posted to the building.\n\n"
							  "Press 'Apply' to post the %3 non-errant value(s) to the building." ).arg(
								QString::number(iNumMods), QString::number(iNumErrors), QString::number(iNumMods-iNumErrors) );
	else if (iNumWarnings > 0)
		qsMsg = QString( "The %1 values being posted to the building include %2 warning(s).\n"
							  "If confirmed, all %3 modified value(s) will be posted to the building.\n\n"
							  "Press 'Apply' to post the %4 modified value(s) to the building." ).arg(
								QString::number(iNumMods), QString::number(iNumWarnings), QString::number(iNumMods), QString::number(iNumMods) );
	if (!qsMsg.isEmpty())
	{	// confirmation of mods required if errors or warnings are present
		QString qsDetails, qsCaption;
		int count=0;
		if (iNumErrors > 0)
		{	qsCaption = "Building Data Error(s)";
			if (iNumErrors > 1)
				qsDetails = QString( "%1 Errors:\n" ).arg( QString::number(iNumErrors) );
			for (int i=0; i < (int) modData.size(); i++)
			{	BEMGridMod* pMod = modData[i];
				if (pMod && !pMod->getIgnoreMod() && pMod->getSetKey() > 0 && pMod->getSetKey() < GM_MinWarning)
				{	if (iNumErrors > 1)
						qsDetails += QString( "%1) %2\n" ).arg( QString::number(++count), pMod->getSetMsg() );
					else
						qsDetails += QString( "%1\n" ).arg( pMod->getSetMsg() );
		}	}	}
		else
			qsCaption = "Building Data Issue(s)";
		if (iNumWarnings > 0)
		{	count=0;
			if (!qsDetails.isEmpty())
				qsDetails += "\n";
			if (iNumWarnings > 1)
				qsDetails += QString( "%1 Warnings:\n" ).arg( QString::number(iNumWarnings) );
			for (int i=0; i < (int) modData.size(); i++)
			{	BEMGridMod* pMod = modData[i];
				if (pMod && !pMod->getIgnoreMod() && pMod->getSetKey() >= GM_MinWarning)
				{	if (iNumWarnings > 1)
						qsDetails += QString( "%1) %2\n" ).arg( QString::number(++count), pMod->getSetMsg() );
					else
						qsDetails += QString( "%1\n" ).arg( pMod->getSetMsg() );
		}	}	}

		try
		{	confirmMsgBox = new QMessageBox();
			if (confirmMsgBox)
			{	confirmMsgBox->setWindowTitle( qsCaption );
				confirmMsgBox->setIcon( (iNumErrors > 0 ? QMessageBox::Critical : QMessageBox::Warning) ); 
				confirmMsgBox->setTextFormat(Qt::RichText); //this is what makes the links clickable
				confirmMsgBox->setText( qsMsg );
				confirmMsgBox->setDetailedText( qsDetails );
				confirmMsgBox->setWindowIcon( QIcon( pxmIcon ) );
				confirmMsgBox->setStandardButtons( (includeApplyBtn ? QMessageBox::Apply : QMessageBox::NoButton) | QMessageBox::Cancel );
				confirmMsgBox->setDefaultButton( (iNumErrors > 0 ? QMessageBox::Cancel : QMessageBox::Apply) );
				confirmed = (confirmMsgBox->exec() == QMessageBox::Apply);
				delete confirmMsgBox;
		}	}
		catch( ... ) {
			assert( false );  // sErrMsg.sprintf( "Unknown error writing hourly CSV results file:  %s", pszHourlyResultsPathFile );
		}
		confirmMsgBox = NULL;
	}
	else
		confirmed = true;

	return confirmed;
}

int BEMGrid::applyMods()
{	int i, iNumModErrors=0;
	QString sModsMsg;
	std::vector<long> laModDBIDs;
	std::vector<int> iaModOccurs;
	for (i=0; i < (int) modData.size(); i++)
	{	BEMGridMod* pMod = modData[i];
		if (pMod && !pMod->getIgnoreMod())
		{	QString sThisModMsg;
			if (pMod->apply( sThisModMsg ))
			{	laModDBIDs.push_back( pMod->getDBID());
				iaModOccurs.push_back(pMod->getObjIdx());
			}
			else
			{	iNumModErrors++;
				if (!sThisModMsg.isEmpty())
				{	if (!sModsMsg.isEmpty())
						sModsMsg += "\n";
					sModsMsg += sThisModMsg;
			}	}
		}
		if (pMod)
		{	QTableWidgetItem *pTWI = item( pMod->getRow(), pMod->getCol() );
			if (pTWI && pMod->getGridCol())
				itemDisplayData( pTWI, pMod->getGridCol() );
		}
	}

	int iNumModsApplied = (int) laModDBIDs.size();

	// process mods via MainFrm, incl. setting flag indicating project data modified
	for (i=0; (mainFrm && i < (int) modData.size()); i++)
	{	BEMGridMod* pMod = modData[i];
		if (pMod && pMod->bemModified())
			mainFrm->DataModified( pMod->getDBID(), pMod->getObjIdx() );
	}
//			if (iSetDataRetVal >= 0)
//			{	// Post-processing following mods
//				//GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );
//				if (mainFrm)
//					mainFrm->SendMessage( WM_DATAMODIFIED, 1, pGC->getDBID() );
//
//	//			CFrameWnd* pFrame = GetParentFrame();
//	//			if (pFrame)
//	//			{	// redisplay status bar strings
//	//				pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//	//
//	//				//if (bUpdateFrameTitle)
//	//				//	pFrame->OnUpdateFrameTitle(TRUE);
//	//			}
//			}

	int iDfltFollowingMods = defaultSettingFollowingMod();
	if (mainFrm && iNumModsApplied > 0 && iDfltFollowingMods > DefaultOption_Nothing)
	{
		//mainFrm->SendMessage( WM_EVALPROPOSED /*, (!bWriteToLog)*/ );
	   CMX_EvaluateRuleset( esDataModRulelist, FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/, ebVerboseInputLogging,
   								NULL, NULL, NULL, epInpRuleDebugInfo, NULL /*QStringList* psaWarningMsgs*/,
   								0 /*iEvalOnlyClass*/, -1 /*iEvalOnlyObjIdx*/, 0 /*iEvalOnlyObjType*/ );		// SAC 4/3/18 - added to enable targeted model defaulting

		// send a message to the main view's tree control via CMainFrame in case the tree requires updating
	//	mainFrm->SendMessage( WM_UPDATETREE, 0, m_lDBID );
	}

	return iNumModsApplied;
}


QString BEMGrid::GetPropertyString( BEMGridColumn* pGC, bool& bEditableCell, bool& bDisplayCell, int& iStatus, int& iError, int iOccur )
{	QString qsData;
	bEditableCell = bDisplayCell = FALSE;
	iStatus = iError = 0;
	if (pGC && pGC->getDBID() > 0)
	{
		int iSpecialVal, iPrec = (pGC->getPropertyType() == BEMP_Flt ? pGC->getDecPrec() : 0);
		//  BEMP_Int  0 /   BEMP_Flt  1 /   BEMP_Sym  2 /   BEMP_Str  3 /   BEMP_Obj  4 /   BEMP_QStr 5			// types of property (BEMPropertyType)
		bEditableCell = BEMPUIX_BEMConditionMissingOrTrue( pGC->getConditionEditable(), idClass, iOccur );
		bDisplayCell  = BEMPUIX_BEMConditionMissingOrTrue( pGC->getConditionDisplay() , idClass, iOccur );
		if (bDisplayCell)
			qsData = BEMPX_GetStringAndStatus( pGC->getDBID(), iStatus, iSpecialVal, iError, iOccur /*iOccur*/, BEMO_User,
															-1 /*iBEMProcIdx*/, TRUE /*bAddCommas*/, iPrec );  //, const char* pszDefault=NULL, long lDBID2=0 );
		if (qsData.isEmpty() && pGC->cmbxMode > 0 && pGC->cmbxIncludeNone)
			qsData = szNone;
	}
	return qsData;
}

void BEMGrid::CreateAndAssignTableWidgetItem( BEMGridColumn* pGC, QString qsData, bool bEditableCell, int iStatus, int row, int col, int iObjIdx )
{
	if (pGC)
	{
		QTableWidgetItem* qtwi = new QTableWidgetItem( qsData, QTableWidgetItem::Type );		ASSERT( qtwi );
		if (pGC->getPropertyType() == BEMP_Flt || pGC->getPropertyType() == BEMP_Int)
			qtwi->setTextAlignment( Qt::AlignRight|Qt::AlignVCenter );
		if (!bEditableCell)
		{	qtwi->setForeground( *brushGray );
			qtwi->setFlags( (qtwi->flags() ^ Qt::ItemIsEditable) );
		}
		else if (iStatus >= 0)
			qtwi->setForeground( *BEMTextQBrush( iStatus + NUM_RESERVED_TEXT_COLORS ) );	// SAC 3/23/18
		if (pGC->getToolTipMsg().length() > 0)
			qtwi->setData( Qt::ToolTipRole, QVariant( pGC->getToolTipMsg() ) );
	//	qtwi->setProperty( "objIdx", QVariant(ir) );
		qtwi->setData( Qt::UserRole, iObjIdx );  // row );
		bool bSaveBeingInitialized = beingInitialized;
		beingInitialized = true;	// ensure beingInitialized true to prevent this call from SETTING data (or status) to BEMBase
		setItem( row, col, qtwi );
		beingInitialized = bSaveBeingInitialized;
	}
}


#define  NUM_AUTO_COLUMNS  15
#define  MIN_COLUMN_WIDTH  85

void BEMGrid::initGrid( int iClass, int iTopic /*=0*/, int iNumCtrls /*=0*/, int iFirstCtrlIdx /*=0*/, int iSelObjectIdx /*=-1*/ )
{	ASSERT( iClass > 0 );
//	qslColTitles.clear();
//	lvColDBIDs.clear();
//	ivColWidths.clear();
//	ivColDecPrecs.clear();
	clearColumnData();
	clearModData();

	clear();
	setSortingEnabled(0);	// start out w/ sorting DISABLED
//QScrollBar *bar = ui->scrollArea->horizontalScrollBar();
//bar->setValue(bar->maximum()/2);
//bar->update();
//ui->scrollArea->update();

	rowHeadersInclNames = false;
	beingInitialized = true;
	int iSelObjRow = -1;
	int iError, iNumObjs = BEMPX_GetNumObjects( iClass );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
	BEMClass* pClass = BEMPX_GetClass( iClass, iError );
	int iNumPTs = BEMPX_GetNumPropertyTypes( iClass );
	if (iNumObjs > 0 && pClass && iNumPTs > 0)
	{	idClass = iClass;
		QStringList qslColTitles;
		//qslColTitles.push_back( "Name" );
		//lvColDBIDs.push_back(  BEMPX_GetDBID( iClass, 0, BEM_PARAM0_NAME ) );
		//ivColWidths.push_back( 120 );
		//ivColDecPrecs.push_back( 0 );
		addColumn( "Name", QString( "name of %1 object" ).arg( pClass->getLongName() ),
						BEMPX_GetDBID( iClass, 0, BEM_PARAM0_NAME ), BEMP_Str, 200 /*width*/, 25 /*height*/, 0 /*decPrec*/, NULL, NULL );
		qslColTitles.push_back( "Name" );
		if (pClass->getParentType(0) >= 0)
		{	addColumn( "Parent", QString( "parent object" ),
							BEMPX_GetDBID( iClass, 0, BEM_PARAM0_PARENT ), BEMP_Str, 200 /*width*/, 25 /*height*/, 0 /*decPrec*/, NULL, NULL );
			qslColTitles.push_back( "Parent" );
		}

		if (iTopic > 0 && iNumCtrls > 0 && iFirstCtrlIdx >= 0)
		{	int iLastCtrlIdx = iFirstCtrlIdx + iNumCtrls - 1;
			for (int ctrl=iFirstCtrlIdx; ctrl <= iLastCtrlIdx; ctrl++)
			{	QString sTitle, sToolTipMsg;
				int width=0, height=0, iCtrlType=-1;   long decPrec=0, dbid=0;
				void *bemEditableCondition=NULL, *bemDisplayCondition=NULL;
				if (BEMPUIX_GetUIControlDataByIndex( ctrl, iCtrlType, dbid, width, height, decPrec, sTitle,
																	sToolTipMsg, bemEditableCondition, bemDisplayCondition ) &&
					 dbid > 0 && (iCtrlType == TDCT_Edit || iCtrlType == TDCT_Combo || iCtrlType == TDCT_Check ||
									  iCtrlType == TDCT_ExtCmb))
								//   TDCT_RadioG,   TDCT_Radio,
								//   TDCT_Button,   TDCT_Date,   TDCT_Time,  TDCT_WMF,   TDCT_Floor,   TDCT_Line,   TDCT_Label,    TDCT_Spread,
								//   TDCT_List,   TDCT_Rect,   TDCT_ChkLst,   TDCT_RTF,   TDCT_ClrBar,   TDCT_HlpBtn,
				{	BEMPropertyType* pPropType = BEMPX_GetPropertyTypeFromDBID( dbid, iError );
					if (pPropType)
					{	if (sTitle.length() < 2 && pPropType)
						{	sTitle = pPropType->getShortName();
							if (pPropType->getNumValues() > 1)
								sTitle += QString( "[%1]" ).arg( QString::number( BEMPX_GetArrayID(dbid) ) );
						}
						if (sTitle.length() > 0 && sTitle[sTitle.length()-1] == ':')
							sTitle = sTitle.left( sTitle.length()-1 );
						if (sTitle.length() > 0 && sTitle[sTitle.length()-1] != ')' &&
							 pPropType->getUnitsLabel().length() > 0)
							sTitle += QString( " (%1)" ).arg( pPropType->getUnitsLabel() );
						if (width < MIN_COLUMN_WIDTH)
							width  = MIN_COLUMN_WIDTH;

//	int	getReportPrecision()						{	return m_reportPrecision;	}

						addColumn( sTitle, sToolTipMsg, dbid, pPropType->getPropType(), width, height, decPrec,
										bemEditableCondition, bemDisplayCondition );
						qslColTitles.push_back( sTitle );
		}	}	}	}
		else
		{	for (int pt=1; (pt <= iNumPTs && colData.size() <= NUM_AUTO_COLUMNS); pt++)
			{	BEMPropertyType* pPropType = BEMPX_GetPropertyType( iClass, pt );
				if (pPropType && pPropType->getPropTypeDetails(0) &&
					 pPropType->getPropTypeDetails(0)->isEditable())
				{	QString sTitle, sToolTipMsg;
					int width=0, height=0;   long decPrec=0;
					void *bemEditableCondition=NULL, *bemDisplayCondition=NULL;
					long dbid = BEMPX_GetDBID( iClass, pt, 1 );
					if (BEMPUIX_GetUIControlDataByDBID( dbid, width, height, decPrec, sTitle, sToolTipMsg,
																		bemEditableCondition, bemDisplayCondition ))
					{
						if (sTitle.length() < 2)
						{	sTitle = pPropType->getShortName();
							if (pPropType->getNumValues() > 1)
								sTitle += QString( "[%1]" ).arg( QString::number( BEMPX_GetArrayID(dbid) ) );
						}
						if (sTitle.length() > 0 && sTitle[sTitle.length()-1] == ':')
							sTitle = sTitle.left( sTitle.length()-1 );
						if (sTitle.length() > 0 && sTitle[sTitle.length()-1] != ')' &&
							 pPropType->getUnitsLabel().length() > 0)
							sTitle += QString( " (%1)" ).arg( pPropType->getUnitsLabel() );
						if (width < MIN_COLUMN_WIDTH)
							width  = MIN_COLUMN_WIDTH;

//	int	getReportPrecision()						{	return m_reportPrecision;	}

						addColumn( sTitle, sToolTipMsg, dbid, pPropType->getPropType(), width, height, decPrec,
										bemEditableCondition, bemDisplayCondition );
						qslColTitles.push_back( sTitle );
				}	}
		}	}
		qslColTitles.push_back( "#" );

//QStringList qslRowTitles;

		if (colData.size() > 1)
		{	if (iSelObjectIdx < 0)
				iSelObjectIdx = BEMPX_GetObjectIndex( pClass );

			setColumnCount( (int) qslColTitles.size() );
			setRowCount( iNumObjs );

			setHorizontalHeaderLabels( qslColTitles );

//			horizontalHeader()->setDefaultAlignment( Qt::TextWordWrap );
//			horizontalHeader()->setFixedHeight( 50 );
			horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );

		// making column labels clickable for sorting - SAC 4/24/18
			setSortingEnabled(1);
			horizontalHeader()->setSectionsClickable(1);
			sortByColumn( columnCount()-1, Qt::AscendingOrder );	// SAC 4/26/18

//I would try QTableWidgetItem::setTextAlignment with Qt::TextWordWrap (merge it with alignment flags if you need).

	// no change
	//		verticalHeader()->setSectionResizeMode( QHeaderView::Interactive );
	//		horizontalHeader()->setSectionResizeMode( QHeaderView::Interactive );

			int ir=-1, ic;
			for (ic=0; ic<(int) colData.size(); ic++)
			{	BEMGridColumn* pGC = colData[ic];					ASSERT( pGC );
				if (pGC)
					setColumnWidth( ic, std::max( pGC->getWidth(), 80 ) );
			}
			setColumnWidth( qslColTitles.size()-1, 40 );  // '#' (index) column

			int iStatus, iError;
			int iObjIdxDigits = (iNumObjs > 99999 ? 6 : (iNumObjs > 9999 ? 5 : (iNumObjs > 999 ? 4 : (iNumObjs > 99 ? 3 : (iNumObjs > 9 ? 2 : 1)))));
			for (int iObjIdx=0; iObjIdx < iNumObjs; iObjIdx++)
			{
				bool bAddObject = true;

// TO DO - add code to determine if THIS object meets criteria for inclusion in grid

				if (bAddObject)
				{	ir++;
					if (iSelObjectIdx == iObjIdx)
						iSelObjRow = ir;

					for (ic=0; ic < (int) colData.size(); ic++)
					{	BEMGridColumn* pGC = colData[ic];					ASSERT( pGC && pGC->getDBID() > 0 );
			//			QTableWidgetItem* pTWI = item( ir, ic );			ASSERT( pTWI );
						if (pGC && pGC->getDBID() > 0)
						{
							bool bEditableCell, bDisplayCell;
							QString qsData = GetPropertyString( pGC, bEditableCell, bDisplayCell, iStatus, iError, iObjIdx );

//if (ic==0)
//	qslRowTitles.push_back( QString( "%1 - %2" ).arg( QString::number(ir+1), qsData ) );

								CreateAndAssignTableWidgetItem( pGC, qsData, bEditableCell, iStatus, ir, ic, iObjIdx );

					}	}
					// '#' (index) column
					//QTableWidgetItem* qtwi = new QTableWidgetItem( QString("%1").arg(QString::number(ir+1)), QTableWidgetItem::Type );		ASSERT( qtwi );
					QTableWidgetItem* qtwi = new QTableWidgetItem( QString("%1").arg( iObjIdx+1, iObjIdxDigits, 10, QChar('0') ), QTableWidgetItem::Type );		ASSERT( qtwi );
					qtwi->setTextAlignment( Qt::AlignCenter );
					qtwi->setForeground( *brushGray );
					qtwi->setFlags( (qtwi->flags() ^ Qt::ItemIsEditable) );
					setItem( ir, (int) colData.size(), qtwi );
			}	}
		}

// Qt::ItemFlags:
//		Qt::NoItemFlags	0	It does not have any properties set.
//		Qt::ItemIsSelectable	1	It can be selected.
//		Qt::ItemIsEditable	2	It can be edited.
//		Qt::ItemIsDragEnabled	4	It can be dragged.
//		Qt::ItemIsDropEnabled	8	It can be used as a drop target.
//		Qt::ItemIsUserCheckable	16	It can be checked or unchecked by the user.
//		Qt::ItemIsEnabled	32	The user can interact with the item.

//Qt::white	3	White (#ffffff)
//Qt::black	2	Black (#000000)
//Qt::gray	5	Gray (#a0a0a4)
//Qt::darkGray	4	Dark gray (#808080)
//Qt::lightGray	6	Light gray (#c0c0c0)

//			tview->model()->setHeaderData(0,Qt::Horizontal,QBrush(QColor("red")),Qt::BackgroundRole);
//
//m_ui->teamTableWidget->setColumnCount(m_ui->teamTableWidget->columnCount()+1);
//    QTableWidgetItem* qtwi = new QTableWidgetItem(QString("Last"),QTableWidgetItem::Type);
//    m_ui->teamTableWidget->setHorizontalHeaderItem(0,qtwi);
//
//
//    for (int c = 0; c < cols; ++c) {
//        QString character(QChar('A' + c));
//        table->setHorizontalHeaderItem(c, new QTableWidgetItem(character));
//    }
//
//
//
//    foreach (QTableWidgetItem *i, selected) {
//        if (i)
//            i->setBackgroundColor(col);



	}	// end of if iNumObjs > 0 && ...

	horizontalScrollBar()->setValue( horizontalScrollBar()->minimum() );
	if (iSelObjRow >= 0)
	{
// scroll to & highlight specific row
		//QList<QTableWidgetItem *> list = findItems(item->text(),Qt::MatchExactly);
		//QTableWidgetItem *foundItem = list[0];
		//QModelIndex index = model()->index(foundItem->row(), foundItem->column());
		QModelIndex index = model()->index( iSelObjRow, 0 );
		scrollTo(index, QAbstractItemView::PositionAtCenter);
	}
	else
		verticalScrollBar()->setValue( verticalScrollBar()->minimum() );

	beingInitialized = false;

	setMouseTracking(true);


//bool BEMPUIX_BEMConditionMissingOrTrue( void* pBEMCondition, int iClass, int iOccur )   // SAC 3/9/18

//int  __declspec(dllexport) __cdecl BEMPUIX_GetFirstDialogTabID( int iBEMClass, int iUIMode );	// SAC 1/5/17

//	QString	getDescription()					{	return m_description;	}
//	void		setDescription( QString s )	{	m_description = s;  return;	}
//	QString	getUnitsLabel()					{	return m_unitsLabel;	}
//	void		setUnitsLabel( QString s )		{	m_unitsLabel = s;  return;	}
//
//	int	getPropType()				{	return m_propType;	}
//	void	setPropType( int i )		{	m_propType = i;  return;	}
//	int	getNumValues()				{	return m_numValues;	}
//	void	setNumValues( int i )	{	m_numValues = i;  return;	}
//
//	int	getUseForTrees()			{	return m_useForTrees;	}
//	void	setUseForTrees( int i )	{	m_useForTrees = i;  return;	}
//
//
//	UINT	getHelpID()						{	return m_helpID;	}
//	void	setHelpID( UINT i )			{	m_helpID = i;  return;	}
//	BOOL	getXMLWriteArrayIndices()				{	return m_XMLWriteArrayIndices;	}
//	void	setXMLWriteArrayIndices( BOOL b )	{	m_XMLWriteArrayIndices = b;  return;	}
//	long	getWriteSimulationFlag()				{	return m_writeSimulationFlag;	}
//	void	setWriteSimulationFlag( long i )		{	m_writeSimulationFlag = i;  return;	}
//	int	getReportPrecision()						{	return m_reportPrecision;	}


//	int idClass;
//	int idTopic;
//	int idxSelObject;

}


int BEMGrid::getBEMObjectIndex( int row )
{	int iRetVal = -1;
	if (row >= 0 && rowCount() > row && columnCount() > 1)
	{	QTableWidgetItem *pTWI = item( row, columnCount()-1 );		ASSERT( pTWI );	// SAC 4/25/18
		QString sData = (pTWI ? pTWI->text() : "");						ASSERT( !sData.isEmpty() );
		if (!sData.isEmpty())
			iRetVal = sData.toInt() - 1;
	}	ASSERT( iRetVal >= 0 );
	return iRetVal;
}


void BEMGrid::horzScrollValueChanged()
{
	int iFirstCol = columnAt(0);
	if (!beingInitialized &&
	    (( rowHeadersInclNames && iFirstCol < 1) ||
		  (!rowHeadersInclNames && iFirstCol > 0)))
		SwitchRowTitles( (rowHeadersInclNames ? false : true) );
}

void BEMGrid::SwitchRowTitles( bool bInclNames )
{
	int numRows = rowCount();
	if (numRows > 0 && bInclNames != rowHeadersInclNames)
	{
		QStringList qslRowTitles;
		for (int ir=1; ir <= numRows; ir++)
		{
			if (!bInclNames)
				qslRowTitles.push_back( QString( "%1"      ).arg( QString::number( ir ) ) );
			else
				qslRowTitles.push_back( QString( "%1 - %2" ).arg( QString::number( ir ), item(ir-1,0)->text() ) );
		}
		setVerticalHeaderLabels( qslRowTitles );
		rowHeadersInclNames = bInclNames;
	}
}


void BEMGrid::ClearComboboxCell()
{
	if (cmbxRow >= 0 && cmbxCol >= 0 && cmbx)
	{			assert( cmbxCol < (int) colData.size() );
		removeCellWidget( cmbxRow, cmbxCol );  // should alo delete the combobox
		if (cmbxCol < (int) colData.size())
		{
			bool bEditableCell=false;		int iStatus=0, iError;
			QString qsData;
			BEMGridColumn* pGC = colData[cmbxCol];					ASSERT( pGC && pGC->getDBID() > 0 );
			int iObjIdx = getBEMObjectIndex( cmbxRow );			ASSERT( iObjIdx>=0 );	// SAC 4/25/18
			if (pGC && pGC->getDBID() > 0)
			{
				bool bDisplayCell;
				qsData = GetPropertyString( pGC, bEditableCell, bDisplayCell, iStatus, iError, iObjIdx );
			}
			CreateAndAssignTableWidgetItem( pGC, qsData, bEditableCell, iStatus, cmbxRow, cmbxCol, iObjIdx );
		}
		cmbxRow = -1;
		cmbxCol = -1;
		cmbx = NULL;
	}
}


void BEMGrid::SwitchCellToCombobox_IfAppropriate( int row, int col )
{
	// user has shifted focus AWAY from any current combobox cell, so start by removing that
	if (cmbxRow >= 0 && cmbxCol >= 0 && cmbx)
		ClearComboboxCell();

	if (row >= 0 && col >= 0 && col < (int) colData.size())
	{
		BEMGridColumn* pGC = colData[col];					ASSERT( pGC && pGC->getDBID() > 0 );
		int iObjIdx = getBEMObjectIndex( row );			ASSERT( iObjIdx>=0 );	// SAC 4/25/18
		if (pGC && pGC->getDBID() > 0)
		{
			bool bEditableCell, bDisplayCell;		int iStatus, iError;
			QString qsData = GetPropertyString( pGC, bEditableCell, bDisplayCell, iStatus, iError, iObjIdx );

			if ((pGC->getPropertyType() == BEMP_Sym || pGC->getPropertyType() == BEMP_Obj ||
			     (BEMPX_GetPropertyID( pGC->getDBID() ) == 0 && BEMPX_GetArrayID( pGC->getDBID() ) == BEM_PARAM0_PARENT)) &&
				 bDisplayCell && bEditableCell)
			{	// create BEMGridComboBox in cell
				BEMGridComboBox* qcmbx = new BEMGridComboBox( this, pGC->getDBID(), iObjIdx );				ASSERT( qcmbx );
				if (qcmbx)
				{	qcmbx->setFrame( false );
					qcmbx->setFont( font );
					if (iStatus >= 0)
						qcmbx->setStyleSheet( QString( "QComboBox { color: rgb(%1, %2, %3); }" ).arg(
														QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 0 ) ),
														QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 1 ) ),
														QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 2 ) ) ) );
			//			qcmbx->setForeground( *BEMTextQBrush( iStatus + NUM_RESERVED_TEXT_COLORS ) );	// SAC 3/23/18
					LoadComboBoxStrings( qcmbx, pGC, iObjIdx );
					if (qsData.length() > 0)
					{	beingInitialized = true;
						qcmbx->setCurrentText( qsData );
						beingInitialized = false;
					}
					setCellWidget ( row, col, qcmbx );
					cmbxRow = row;
					cmbxCol = col;
					cmbx = qcmbx;
					connect( qcmbx, SIGNAL(currentIndexChanged(int)),
								this, SLOT(cmbxIndexChanged(int)) );
					connect( qcmbx, SIGNAL(currentIndexChanged(const QString & text)),
								this, SLOT(cmbxIndexChanged(const QString &text)) );
			}	}
	}	}
}


static inline int IndexInLongArray( std::vector<long>& iArray, long iVal )
{	int i=0; 
	for (; i < (int) iArray.size(); i++)
		if (iArray[i] == iVal)
			return i;
	return -1;
}

bool BEMGrid::ObjectTypeIsCompatible( BEMGridColumn* pGC, int i1ClassID, int iObjIdx, int iCurObjIdx )
{
   int iError, iSV;
   BEM_ObjType eObjType = BEMO_User;
	if (pGC->cmbxObjClassID.size() == 1 && pGC->cmbxObjClassID[0] == 0)  // handle situation where pGC->cmbxObjTypeDBID/Value used for something other than defining object referencing compatibility
		return true;
	bool bIncompatEntry = false;
	bool bCompatEntry = false;
	for (int iObjCls=0; iObjCls < (int) pGC->cmbxObjClassID.size(); iObjCls++)
		if (i1ClassID == pGC->cmbxObjClassID[iObjCls])
		{	if (pGC->cmbxObjTypeDBID[iObjCls] == 0)
				bCompatEntry = true;
			else
			{	long lObjType = BEMPX_GetInteger( pGC->cmbxObjTypeDBID[iObjCls], iSV, iError, iObjIdx, eObjType );
				if (iError >= 0 && lObjType == pGC->cmbxObjTypeValue[iObjCls])
					bCompatEntry = true;
				else if (iError >= 0 && pGC->cmbxObjTypeValue[iObjCls] == -99)
				{	// handle case where the property of the object being loaded has to match a corresponding property in the local/current object
					BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( pGC->cmbxObjTypeDBID[iObjCls], iError );
					if (pObjTypePropType && !pObjTypePropType->getShortName().isEmpty())
					{	long lLocTypeDBID = BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( pGC->getDBID() ) );			ASSERT( lLocTypeDBID > BEM_COMP_MULT );
						long lLocTypeVal = 0;
						if (lLocTypeDBID > BEM_COMP_MULT && BEMPX_SetDataInteger( lLocTypeDBID, lLocTypeVal, 0 /*default*/, -1 /*iDispDataType*/, iCurObjIdx ))
						{	if (lLocTypeVal == lObjType)
								bCompatEntry = true;
							else
								bIncompatEntry = true;
						}
						else
						{	ASSERT( false );
							bIncompatEntry = true;
						}
					}
					else
					{	ASSERT( false );
						bIncompatEntry = true;
					}
				}
				else // if (iError >= 0 && plObjType && *plObjType != pGC->cmbxObjTypeValue[iObjCls])
					bIncompatEntry = true;
			}
		}
	return (bCompatEntry ? true : (bIncompatEntry ? false : true));
}

void BEMGrid::LoadComboBoxObjectNames( QComboBox* qcmbx, BEMGridColumn* pGC, int i1ClassID, int iObjIdx )
{
	int iNumObjects = BEMPX_GetNumObjects( i1ClassID );
	int iCmbbClass = BEMPX_GetClassID( pGC->getDBID() );
	int iError, iSpecialVal;
	BEMObject* pCurSelObj = NULL;
	// if this combo is for assigning the parent of an EXISTING (and current) component, then set
	// pCurSelObj to be the parent of the current object for which this combo's DBID describes
	if (pGC->cmbxMode == GCMBX_PARENT)
	{	if (BEMPX_GetArrayID( pGC->getDBID() ) == BEM_PARAM0_PARENT)
		{	BEMObject* pCurObj = BEMPX_GetObjectByClass( iCmbbClass, iError, iObjIdx );
			if (pCurObj && pCurObj->getParent())
				pCurSelObj = pCurObj->getParent();
		}
		// else - the alternative is that this combo assigns the parent of a component which
		//		  is in the process of being created - in which case we leave pCurSelObj = NULL
	}
	else
		pCurSelObj = BEMPX_GetObjectPtr( pGC->getDBID(), iSpecialVal, iError, iObjIdx );

	// to load only those component names PREVIOUS to the one being edited
	int iUserObjsToLoad = iNumObjects;
	// variable to prevent the loading of the currently active component
	int iDontLoadObjIdx = -1;
	if (pGC->cmbxMode == GCMBX_OBJECT && iCmbbClass == i1ClassID && pGC->cmbxObjTypeDBID.size() > 0 && pGC->cmbxObjTypeDBID[0] == 0 && pGC->cmbxObjTypeValue[0] != 0)  // probably OK to only check first m_lObjTypeDBID
	{	if (pGC->cmbxObjTypeValue[0] == -1)
		{	if (iObjIdx >= 0)
				iUserObjsToLoad = iObjIdx;
			else
				iUserObjsToLoad = BEMPX_GetObjectIndex( BEMPX_GetClass( iCmbbClass, iError ) );
		}
		else if (pGC->cmbxObjTypeValue[0] == -2)
		{	if (iObjIdx >= 0)
				iDontLoadObjIdx = iObjIdx;
			else
				iDontLoadObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( iCmbbClass, iError ) );
	}	}

	for (int iObj=0; iObj < iUserObjsToLoad; iObj++)
	{	BEMObject* pObj = BEMPX_GetObjectByClass( i1ClassID, iError, iObj );
		bool bLoadIt = false;
		if ( iError == 0  &&  pObj  &&  iObj != iDontLoadObjIdx )  // SAC 6/22/04
		{	if (pGC->cmbxMode == GCMBX_PARENT)
				// if this combo provides for the assignment of a parent component, then only add
				// this item if it IS the current parent OR if this component CAN become a child of this parent
				bLoadIt = ( pCurSelObj == pObj || BEMPX_CanCreateAnotherChildObject( iCmbbClass, pObj ) );
			else
				bLoadIt = ( pCurSelObj == pObj ||
								( BEMPX_CanAssignObject( i1ClassID, iError, iObj ) &&
								  (pGC->cmbxObjTypeDBID.size() == 0 || ObjectTypeIsCompatible( pGC, i1ClassID, iObj, iObjIdx )) ) );	// handle multiple referenced object types
		}
		if (bLoadIt)
		{	if (pGC->cmbxMode == GCMBX_PARENT)
				qcmbx->addItem( pObj->getName(), QVariant( i1ClassID ) );
			else
				qcmbx->addItem( pObj->getName(), QVariant( BEMO_User ) );
	}	}
}

static bool LoadComboBoxEnumList( QComboBox* qcmbx, long lDBID, int iObjIdx )		// SAC 4/6/18
{	bool bRetVal = false;
		int iNumSyms;
		BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, lDBID, iObjIdx );
		if (pSymDepSet)
		{	std::vector<long> iaSymVal;  // SAC 8/29/02 - added code to prevent multiple symbols w/ same value from getting added to the list
													//					(necessary to ensure backward compatibility for certain symbols (RoofSecInsType))
			for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
			{	long iSymValue;
				QString qstr;
				BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet, iSymIdx );
				if (qstr.length() > 0 && IndexInLongArray( iaSymVal, iSymValue ) < 0)
				{	qcmbx->addItem( qstr, QVariant( iSymValue ) );
					iaSymVal.push_back( iSymValue );
			}	}
			bRetVal = (iaSymVal.size() > 0);
		}
	return bRetVal;
}

void BEMGrid::LoadComboBoxStrings( QComboBox* qcmbx, BEMGridColumn* pGC, int iObjIdx )
{
	qcmbx->clear();
	if (pGC->cmbxIncludeNone)
		qcmbx->addItem( QString( szNone ), QVariant( 0 ) );

	int iError;
	if (pGC->cmbxMode == GCMBX_SYMBOL)
	{
		if (!LoadComboBoxEnumList( qcmbx, pGC->getDBID(), iObjIdx ))
		{	QString sErrMsg, sObjProp;	
			BEMPX_DBIDToDBCompParamString( pGC->getDBID(), sObjProp, false /*bLongNames*/ );
			sErrMsg = QString( "Error loading enumeration list for %1.\n(BEMGrid::LoadComboBoxStrings - Col: %2)" ).arg( sObjProp, pGC->getTitle() );
			BEMMessageBox( sErrMsg );
		}
	//	int iNumSyms;
	//	BEMSymDependencySet* pSymDepSet = BEMPX_GetSymbolListPointer( iNumSyms, pGC->getDBID(), iObjIdx );
	//	if (!pSymDepSet)
	//	{	QString sErrMsg, sObjProp;	
	//		BEMPX_DBIDToDBCompParamString( pGC->getDBID(), sObjProp, false /*bLongNames*/ );
	//		sErrMsg = QString( "Error loading enumeration list for %1.\n(BEMGrid::LoadComboBoxStrings - Col: %2)" ).arg( sObjProp, pGC->getTitle() );
	//		BEMMessageBox( sErrMsg );
	//	}
	//	else
	//	{	std::vector<long> iaSymVal;  // SAC 8/29/02 - added code to prevent multiple symbols w/ same value from getting added to the list
	//												//					(necessary to ensure backward compatibility for certain symbols (RoofSecInsType))
	//		for (int iSymIdx=0; iSymIdx<iNumSyms; iSymIdx++)
	//		{	long iSymValue;
	//			QString qstr;
	//			BEMPX_GetSymbolData( iSymValue, qstr, pSymDepSet, iSymIdx );
	//			if (qstr.length() > 0 && IndexInLongArray( iaSymVal, iSymValue ) < 0)
	//			{	qcmbx->addItem( qstr, QVariant( iSymValue ) );
	//				iaSymVal.push_back( iSymValue );
	//	}	}	}
	}
	else if (pGC->cmbxMode == GCMBX_OBJECT)
	{	int i1ClassID = 0;
		if (iObjIdx < 0)
			iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( BEMPX_GetClassID( pGC->getDBID() ), iError ) );

	// SAC 3/21/18 - bail on "Create..." options within grid comboboxes FOR NOW
	//	// if this item is editable and another object of this type can be created, then add an item to allow the user to create a new one
	//	if ( m_bAllowEdits && m_bEditable && 
	//						//  // flag value to override default availability "None", "Create" & perhaps other options
	//		  true )	 //  !(m_dwListOptionFlag & PREVENT_ENTRY_CREATE) )
	//	{
	//		int iProp  = BEMPX_GetPropertyID( pGC->getDBID() );
	//		int iArray = BEMPX_GetArrayID( pGC->getDBID() );
	//		// if prop == 0 => reserved/custom data => only allow ACTIVE or PARENT (not NEWPAR or NEWCOPY)
	//		if ( iProp > 0 || iArray == BEM_PARAM0_PARENT )
	//		{	int iLoopEnd = (iProp == 0 ? 1 : pGC->cmbxObjClassID.size());
	//			//	multiple class IDs are allowed - but we want only 1 occurrence of each class to have a "- create ..." entry added to the list for
	//			CString sLastCr8Str;
	//			int iLast1ClassID = 0;
	//			for (int iObjCls=0; iObjCls < iLoopEnd; iObjCls++)		// SAC 6/15/12 - enable multiple object types to be created...
	//			{	if (iProp > 0)
	//					i1ClassID = pGC->cmbxObjClassID[iObjCls];
	//			// SAC 9/4/15 - added code to check w/ parent frame before contionuing to facilitate object creation (to enable product-specific restrictions)
	//					bool bOKToCr8 = true;		// SAC 11/11/15 - new variable to avoid resetting i1ClassID which screws things up below the creation code
	//					if (i1ClassID > 0)
	//					{	CFrameWnd* pFrame = GetParentFrame();
	//						if (pFrame && pFrame->SendMessage( WM_CHECKCOMPAT, 0, i1ClassID ) == 0)
	//							//i1ClassID = 0;		// indicates new component should NOT be created
	//							bOKToCr8 = false;		// SAC 11/11/15
	//					}
	//					if (bOKToCr8 && i1ClassID > 0 && BEMPX_CanCreateAnotherUserObject( i1ClassID ))
	//					{
	//						CString sCr8Typ, sCr8Str = (CompatibleLibraryObjectExists( i1ClassID ) ? szCr8Imp : szCr81);
	//				// add specification of the TYPE of this object that can be referenced by this property - SAC 9/19/13
	//						if (iProp > 0 && cmbxObjTypeDBID.size() > iObjCls && cmbxObjTypeDBID[iObjCls] > 0)
	//						{	sCr8Typ.Empty();
	//							if (pGC->cmbxObjTypeValue[iObjCls] == -99)
	//							{	// load the compatible type string based on the Type of this LOCAL object (used in syncing day/week/annual schedule types
	//								BEMPropertyType* pObjTypePropType = BEMPX_GetPropertyTypeFromDBID( cmbxObjTypeDBID[iObjCls], iError );				ASSERT( pObjTypePropType );
	//								if (pObjTypePropType && !pObjTypePropType->getShortName().isEmpty())
	//								{	long lLocTypeDBID = BEMPX_GetDatabaseID( pObjTypePropType->getShortName(), BEMPX_GetClassID( pGC->getDBID() ) );		ASSERT( lLocTypeDBID > BEM_COMP_MULT );
	//									if (lLocTypeDBID > BEM_COMP_MULT)
	//									{	VERIFY( BEMPX_SetDataString( lLocTypeDBID, sCr8Typ, FALSE, 0, iObjIdx ) );									ASSERT( !sCr8Typ.IsEmpty() );
	//									}
	//								}
	//							}
	//							else
	//							{	// load string describing Type of object that is compatible w/ this reference
	//								// 	(get the symbol string corresponding to this value (regardless of what dependency list it is in))
	//								QString qsSymStr = BEMPX_GetSymbolString(	pGC->cmbxObjTypeValue[iObjCls], cmbxObjTypeDBID[iObjCls], -1, BEMO_User, -1,
	//																						FALSE /*bOnlyFromCurrentSymDepSet*/ );												//ASSERT( !sCr8Typ.IsEmpty() ); - may not be dependent on enumeration property...
	//								sCr8Typ = qsSymStr.toLatin1().constData();
	//							}
	//							if (!sCr8Typ.IsEmpty() && (CompatibleLibraryObjectExists( i1ClassID ) || sCr8Typ.CompareNoCase("New")))  // SAC 7/19/17 - prevent item string "- Create new New ... (Res tic #861)
	//							{	sCr8Str += sCr8Typ;
	//								sCr8Str += ' ';
	//							}
	//						}
	//
	//						BEMClass* pCr8Class = BEMPX_GetClass( i1ClassID, iError );
	//						if (pCr8Class)
	//							sCr8Str += pCr8Class->getLongName().toLatin1().constData();
	//						else
	//							sCr8Str += "Building Component";
	//						//sCr8Str += szCr82;
	//						if (pGC->cmbxMode == GCMBX_ACTIVE)  // SAC 1/3/12 - Added alternative secondary string for "active" component selections (that are not being "applied" to an attribute)
	//							sCr8Str += szCr82b;
	//						else
	//							sCr8Str += szCr82;
	//
	//						if ( sLastCr8Str.IsEmpty() ||	// SAC 7/19/17 - avoid consecutive identical selections (Res tic #861)
	//							  (sLastCr8Str.Compare( sCr8Str ) && (iLast1ClassID != i1ClassID || !sCr8Typ.IsEmpty())) )
	//						{	qcmbx->addItem( QString( sCr8Str ), QVariant( (iProp > 0 ? sdwCreateData+1+iObjCls : sdwCreateData+100+i1ClassID) ) );
	//							sLastCr8Str = sCr8Str;
	//							iLast1ClassID = i1ClassID;
	//						}
	//					}
	//			}
	//		}
	//	}

		// load the existing object names into the list
		if (pGC->cmbxMode != GCMBX_OBJECT)		// ensure objects of ALL compatible types are listed
		{	ASSERT( i1ClassID );
			LoadComboBoxObjectNames( qcmbx, pGC, i1ClassID, iObjIdx );
		}
		else
		{  std::vector<long> iaClassesLoaded;
			for (int iObjCls=0; iObjCls < (int) pGC->cmbxObjClassID.size(); iObjCls++)
				if (pGC->cmbxObjClassID[iObjCls] > 0 && IndexInLongArray( iaClassesLoaded, pGC->cmbxObjClassID[iObjCls] ) < 0)
				{	LoadComboBoxObjectNames( qcmbx, pGC, pGC->cmbxObjClassID[iObjCls], iObjIdx );
					iaClassesLoaded.push_back( pGC->cmbxObjClassID[iObjCls] );
		}		}
	}
	else if (pGC->cmbxMode == GCMBX_PARENT)
	{	int i1ClassID = BEMPX_GetClassID( pGC->getDBID() );
		BEMClass* pClass = BEMPX_GetClass( i1ClassID, iError );
		if (iError >= 0 && pClass)
		{	for (int iPar=0; (iPar < BEM_MAX_PARENT_TYPES) &&
								  (pClass->getParentType(iPar) > -1); iPar++)
				LoadComboBoxObjectNames( qcmbx, pGC, pClass->getParentType(iPar)+1, iObjIdx );
		}
	}
	else  // invalid pGC->cmbxMode value
	{	QString sErrMsg, sObjProp;
		BEMPX_DBIDToDBCompParamString( pGC->getDBID(), sObjProp, false /*bLongNames*/ );
		sErrMsg = QString( "Property %1 (DBID %2) not compatible with dropdown list control.\n(BEMGrid::LoadComboBoxStrings() - Col: %3)" ).arg(
									sObjProp, QString::number( pGC->getDBID() ), pGC->getTitle() );
		BEMMessageBox( sErrMsg );
	}
}


void BEMGrid::gridMessageBox( bool beep, QMessageBox::Icon icon, const QString &title, const QString &text,
										QMessageBox::StandardButtons buttons /*=QMessageBox::NoButton*/ )
{	if (beep)
		MessageBeep( MB_OK );
	QMessageBox msgBox( icon, title, text, buttons, parentWidget() );
	msgBox.setWindowIcon( QIcon( pxmIcon ) );
	msgBox.exec();
}


static char BASED_CODE szErrorCaption[] = "Grid Input Error";
static char BASED_CODE szErrZeroLengthName[] = "Component names must contain at least one character.";
static char BASED_CODE szErrNameNotUnique[]  = "This name is already in use, enter a unique name for this component.";

void BEMGrid::itemDisplayData(QTableWidgetItem *item, BEMGridColumn* pGC /*=NULL*/)
{																							ASSERT( item && idClass > 0 );
	if (item && idClass > 0)
	{
		if (pGC==NULL)
		{	int iCol = item->column();												ASSERT( iCol >= 0 && iCol < (int) colData.size() );
			if (iCol >= 0 && iCol < (int) colData.size())
				pGC = colData[iCol];
		}
		if (pGC)
		{
	//		int iObjIdx = item->property( "objIdx" ).toInt();				ASSERT( iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ) );
			int iObjIdx = item->data( Qt::UserRole ).toInt();				ASSERT( iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ) );
			if (iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ))
			{
				int iStatus, iSpecialVal, iError;
				int iPrec = (pGC->getPropertyType() == BEMP_Flt ? pGC->getDecPrec() : 0);
				//  BEMP_Int  0 /   BEMP_Flt  1 /   BEMP_Sym  2 /   BEMP_Str  3 /   BEMP_Obj  4 /   BEMP_QStr 5			// types of property (BEMPropertyType)
				QString qsData;
				BOOL bEditableCell = BEMPUIX_BEMConditionMissingOrTrue( pGC->getConditionEditable(), idClass, iObjIdx );
				BOOL bDisplayCell  = BEMPUIX_BEMConditionMissingOrTrue( pGC->getConditionDisplay() , idClass, iObjIdx );
				if (bDisplayCell)
					qsData = BEMPX_GetStringAndStatus( pGC->getDBID(), iStatus, iSpecialVal, iError, iObjIdx /*iOccur*/, BEMO_User,
																	-1 /*iBEMProcIdx*/, TRUE /*bAddCommas*/, iPrec );  //, const char* pszDefault=NULL, long lDBID2=0 );
	beingInitialized = true;
				if (!bEditableCell)
				{	item->setForeground( *brushGray );
					item->setFlags( (item->flags() ^ Qt::ItemIsEditable) );
				}
				else if (iStatus >= 0)
					item->setForeground( *BEMTextQBrush( iStatus + NUM_RESERVED_TEXT_COLORS ) );	// SAC 5/3/18
				item->setText( qsData );
	beingInitialized = false;
		}	}
	}
}

void BEMGrid::itemChangedLocal(QTableWidgetItem *item)
{
	if (!beingInitialized && item && idClass)
	{
		int iCol = item->column();
		if (iCol < 0 || iCol >= (int) colData.size())
		{	ASSERT( FALSE );
			return;
		}
//		int iError, iSetDataRetVal = -1;
		int iNumModsApplied = 0;
		BEMGridColumn* pGC = colData[iCol];											ASSERT( pGC );
		if (pGC)
		{
			int iObjIdx = item->data( Qt::UserRole ).toInt();					ASSERT( iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ) );
			if (iObjIdx < 0 || iObjIdx >= BEMPX_GetNumObjects( idClass ))
			{	ASSERT( FALSE );
				return;
			}

			int iArray = BEMPX_GetArrayID( pGC->getDBID() );
			QString sData = item->data(Qt::DisplayRole).toString();

			clearModData();
			BEMGridMod* pMod = addMod( item->row(), iCol, sData, pGC, iObjIdx );
			if (confirmMods())
				iNumModsApplied = applyMods();
			else
				itemDisplayData( item, pGC );

//			if (sData.length() > 0)
//			{
//				// SET data to BEMBase
//				int iRangeViolation = RangeCheckViolation( pGC->getDBID(), iObjIdx, pGC->getPropertyType(), sData, FALSE /*bSilent*/, NULL /*QString**/ );  // will display error/warning/message
//				// prevent setting values which cause RANGE_ERRORs
//				if (iRangeViolation == RANGE_ERROR)
//					itemDisplayData( item, pGC );
//				else
//				{
//					void* pData = NULL;
//					long lData;
//					double fData;
//					int iDataType = pGC->getPropertyType();
//					if (iDataType == BEMP_Int)
//					{  lData = BEMPX_StringToLong( sData.toLatin1().constData() ); 
//						pData = &lData;
//					}
//					else if (iDataType == BEMP_Flt)
//					{  fData = BEMPX_StringToFloat( sData.toLatin1().constData() );
//						pData = &fData;
//					}
//					else
//					{
//						iDataType = BEMP_QStr;
//						pData = (void*) &sData;
//	
//			//			// set flag to update frame title if project name modified
//			//			if (slProjNameDBID == 0)
//			//				slProjNameDBID = BEMPX_GetDatabaseID( "Proj:Name" );
//			//			if (m_lUseDBID == slProjNameDBID)
//			//				bUpdateFrameTitle = TRUE;
//
//						// prevent storage of names which are not unique within user and userlib components
//						if (iArray == BEM_PARAM0_NAME)
//						{
//							if (/*newStr != m_sCurrStr  &&*/  BEMPX_GetComponentByNameQ( sData, FALSE, 0, TRUE ) != NULL)
//							{	pData = NULL;
//								gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString(szErrNameNotUnique) );
//							}
//					}	}
//	
//					if (pData != NULL)
//						iSetDataRetVal = BEMPX_SetBEMData( pGC->getDBID(), iDataType, pData, BEMO_User, iObjIdx );
//					else
//						itemDisplayData( item, pGC );
//				}
//			}
//			else
//			{	// BLAST BEMBase data
//				if (iArray == BEM_PARAM0_NAME)
//				{	gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString(szErrZeroLengthName) );
//					itemDisplayData( item, pGC );
//				}
//				else
//				{	BEMPX_DefaultProperty( pGC->getDBID(), iError, iObjIdx );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
//					iSetDataRetVal = 0;
//				}
//			}
//
//			if (iSetDataRetVal >= 0)
//			{	// Post-processing following mods
//				//GetParent()->SendMessage( WM_DATAMODIFIED, 1, m_lUseDBID );
//				if (mainFrm)
//					mainFrm->SendMessage( WM_DATAMODIFIED, 1, pGC->getDBID() );
//
//	//			CFrameWnd* pFrame = GetParentFrame();
//	//			if (pFrame)
//	//			{	// redisplay status bar strings
//	//				pFrame->SendMessage( WM_SETSTATUSMESSAGE, (WPARAM) &m_sStatusMsg, m_lUseDBID );
//	//
//	//				//if (bUpdateFrameTitle)
//	//				//	pFrame->OnUpdateFrameTitle(TRUE);
//	//			}
//			}
		}

		// The general purpose roles (and the associated types) are:
		//		Qt::DisplayRole	0	The key data to be rendered in the form of text. (QString)
		//		Qt::DecorationRole	1	The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)
		//		Qt::EditRole	2	The data in a form suitable for editing in an editor. (QString)
		//		Qt::ToolTipRole	3	The data displayed in the item's tooltip. (QString)
		//		Qt::StatusTipRole	4	The data displayed in the status bar. (QString)
		//		Qt::WhatsThisRole	5	The data displayed for the item in "What's This?" mode. (QString)
		//		Qt::SizeHintRole	13	The size hint for the item that will be supplied to views. (QSize)
	}
}

void BEMGrid::setCmbxData( QString sData )
{
	if (!beingInitialized && idClass && cmbxCol >= 0 && cmbxRow >= 0 && cmbx && !sData.isEmpty())
	{	int iCol = cmbxCol;  //item->column();
		if (iCol < 0 || iCol >= (int) colData.size())
		{	ASSERT( FALSE );
			MessageBeep( MB_OK );
			return;
		}
		int iNumModsApplied = 0;
		BEMGridColumn* pGC = colData[iCol];											ASSERT( pGC );
		if (pGC)
		{
			//int iObjIdx = item->data( Qt::UserRole ).toInt();					ASSERT( iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ) );
			int iObjIdx = cmbx->objIdx();												ASSERT( iObjIdx >= 0 && iObjIdx < BEMPX_GetNumObjects( idClass ) );
			if (iObjIdx < 0 || iObjIdx >= BEMPX_GetNumObjects( idClass ))
			{	ASSERT( FALSE );
				MessageBeep( MB_OK );
				return;
			}

			int iArray = BEMPX_GetArrayID( cmbx->dbid() );  //pGC->getDBID() );
			//QString sData = cmbx->currentText();  //item->data(Qt::DisplayRole).toString();

			clearModData();
			BEMGridMod* pMod = addMod( cmbxRow /*item->row()*/, iCol, sData, pGC, iObjIdx );
			if (confirmMods())
				iNumModsApplied = applyMods();
			else
			{	//itemDisplayData( item, pGC );
				MessageBeep( MB_OK );
			}
	}	}
}

void BEMGrid::cmbxIndexChanged(int /*index*/)
{
//	if (!beingInitialized)
//		MessageBeep( MB_OK );
	if (!beingInitialized && idClass && cmbxCol >= 0 && cmbxRow >= 0 && cmbx)
		setCmbxData( cmbx->currentText() );
}

void BEMGrid::cmbxIndexChanged(const QString &text)
{
	if (!text.isEmpty() && !beingInitialized)
		setCmbxData( text );
//		MessageBeep( MB_OK );
}


void BEMGrid::SwitchCellToCombobox(int row, int col, QString signal)
{
	if (cmbxRow >= 0 && cmbxCol >= 0 && (cmbxRow != row || cmbxCol != col))
		ClearComboboxCell();		// under no circumstances does a combobox stick around following a change to the active cell ??

int iNumIdxs = (int) selectedIndexes().size();
	if (selectedIndexes().size() == 1)
	{
		int row = (int) selectedIndexes().at(0).row();
		int col = (int) selectedIndexes().at(0).column();
		SwitchCellToCombobox_IfAppropriate( row, col );
	}

//	QTableWidgetItem* pTWI = item(row, col);
//	BEMGridColumn* pGC = colData[col];											ASSERT( pGC );
//	if (pTWI && pGC && (pGC->getPropertyType() == BEMP_Sym ||
//							  pGC->getPropertyType() == BEMP_Obj))
//	{
//		QWidget* pCW = cellWidget(row, col);
//		if (pCW == NULL || pCW->metaObject() == NULL ||
//			 QString( pCW->metaObject()->className() ).compare("BEMGridComboBox"))
//		{
//			gridMessageBox( true /*beep*/, QMessageBox::NoIcon, QString("Alert"), QString( "switch %1 to BEMGridComboBox due to signal %2" ).arg( ((pCW == NULL || pCW->metaObject() == NULL) ? "<unknown>" : pCW->metaObject()->className()), signal ) );
//
//	}	}


//setCellWidget(int row, int column, QWidget *widget)

//QWidget *QTableWidget::cellWidget(int row, int column)
//widget->metaObject()->className()
}

void BEMGrid::cellActivatedLocal(int row, int column)
{	SwitchCellToCombobox(row, column, "cellActivated");
}
void BEMGrid::cellClickedLocal(int row, int column)
{	SwitchCellToCombobox(row, column, "cellClicked");
}
void BEMGrid::cellEnteredLocal(int row, int column)
{	SwitchCellToCombobox(row, column, "cellEntered");
}

int  BEMGrid::defaultSettingFollowingMod()
{	return elDefaultOptionInp;
}
int  BEMGrid::defaultSettingAfterObjectChange()
{	return elDefaultOptionObj;
}
int  BEMGrid::defaultSettingOnClose()
{	return elDefaultOptionDone;
}


void BEMGrid::keyPressEvent(QKeyEvent *event)
{
	// at least one entire row selected
	QModelIndexList selectedRows = selectionModel()->selectedRows();
	if(!selectedRows.isEmpty())
	{
		if(event->key() == Qt::Key_Insert)
// no ROW insertion/deletion
//			model()->insertRows(selectedRows.at(0).row(), selectedRows.size());
			gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString("Row Insert not implemented.") );
		else if(event->key() == Qt::Key_Delete)
// no ROW insertion/deletion
//			model()->removeRows(selectedRows.at(0).row(), selectedRows.size());
			gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString("Row Delete not implemented.") );
	}

	// at least one cell selected
	if(!selectedIndexes().isEmpty())
	{
			// Qt::Key_Home	0x01000010	 
			// Qt::Key_End	0x01000011	 
			// Qt::Key_Left	0x01000012	 
			// Qt::Key_Up	0x01000013	 
			// Qt::Key_Right	0x01000014	 
			// Qt::Key_Down	0x01000015	 
			// Qt::Key_PageUp	0x01000016	 
			// Qt::Key_PageDown	0x01000017	 
		if(event->key() >= Qt::Key_Home && event->key() <= Qt::Key_PageDown)
		{
			// capture selected cell prior to move  ??

			ClearComboboxCell();		// under no circumstances does a combobox stick around following an arrow key event ??

			QTableWidget::keyPressEvent(event);

			// and cell after move
	int iNumIdxs = (int) selectedIndexes().size();
			if (selectedIndexes().size() == 1)
			{
				int row = (int) selectedIndexes().at(0).row();
				int col = (int) selectedIndexes().at(0).column();

	//		QItemSelectionRange range = selectionModel()->selection().first();
	//		if (selectionModel()->selection().size() == 1)
	//		{
	//			SwitchCellToCombobox_IfAppropriate( (int) range.top(), (int) range.left() );

				SwitchCellToCombobox_IfAppropriate( row, col );
			}
//			MessageBeep( MB_OK );
		}
		else if(event->key() == Qt::Key_Delete)
		{
			gridMessageBox( true /*beep*/, QMessageBox::Warning, QString(szErrorCaption), QString("Cell Deletion not implemented.") );
		//	foreach (QModelIndex index, selectedIndexes())
		//		model()->setData(index, QString());
		}
		else if(event->matches(QKeySequence::Copy))
		{
			copySelectionToClipboard();
		}
		else if(event->matches(QKeySequence::Paste))
		{
			pasteSelectionFromClipboard();
		}
		else
			QTableWidget::keyPressEvent(event);
	}
}


bool BEMGrid::haveSelection()
{	return selectedIndexes().isEmpty();
}

int BEMGrid::getSelectionBounds( int& maxRow, int& minRow, int& maxCol, int& minCol, int& numCells )
{	QList<QTableWidgetSelectionRange> qlSelRanges = selectedRanges();
	if (qlSelRanges.size() < 1)
		return 0;
	maxRow=-1;  minRow=99999;   maxCol=-1;  minCol=9999;  numCells=0;
	for (int iSR=0; iSR < (int) qlSelRanges.size(); iSR++)
	{	if (qlSelRanges.at(iSR).bottomRow() > maxRow)
			maxRow = qlSelRanges.at(iSR).bottomRow();
		if (qlSelRanges.at(iSR).topRow() < minRow)
			minRow = qlSelRanges.at(iSR).topRow();
		if (qlSelRanges.at(iSR).rightColumn() > maxCol)
			maxCol = qlSelRanges.at(iSR).rightColumn();
		if (qlSelRanges.at(iSR).leftColumn() < minCol)
			minCol = qlSelRanges.at(iSR).leftColumn();
		numCells += ((qlSelRanges.at(iSR).bottomRow()  -qlSelRanges.at(iSR).topRow()    +1) *
						 (qlSelRanges.at(iSR).rightColumn()-qlSelRanges.at(iSR).leftColumn()+1));
	}
	return ((maxRow-minRow+1) * (maxCol-minCol+1));
}

bool BEMGrid::copySelectionToClipboard()
{
	QString text;
//			QItemSelectionRange range = selectionModel()->selection().first();
//			for (auto i = range.top(); i <= range.bottom(); ++i)
//			{
//				QStringList rowContents;
//				for (auto j = range.left(); j <= range.right(); ++j)
//					rowContents << model()->index(i,j).data().toString();
//				text += rowContents.join("\t");
//				text += "\n";
//			}
//			QApplication::clipboard()->setText(text);
//	gridMessageBox( true /*beep*/, QMessageBox::NoIcon, QString("Copied to clipboard"), text );

	int maxRow, minRow, maxCol, minCol, numCells;
	int boundingCells = getSelectionBounds( maxRow, minRow, maxCol, minCol, numCells );
//	int maxRow=-1, minRow=99999, maxCol=-1, minCol=9999, numCells=0;
//	QList<QTableWidgetSelectionRange> qlSelRanges = selectedRanges();
//	for (int iSR=0; iSR < (int) qlSelRanges.size(); iSR++)
//	{	if (qlSelRanges.at(iSR).bottomRow() > maxRow)
//			maxRow = qlSelRanges.at(iSR).bottomRow();
//		if (qlSelRanges.at(iSR).topRow() < minRow)
//			minRow = qlSelRanges.at(iSR).topRow();
//		if (qlSelRanges.at(iSR).rightColumn() > maxCol)
//			maxCol = qlSelRanges.at(iSR).rightColumn();
//		if (qlSelRanges.at(iSR).leftColumn() < minCol)
//			minCol = qlSelRanges.at(iSR).leftColumn();
//		numCells += ((qlSelRanges.at(iSR).bottomRow()  -qlSelRanges.at(iSR).topRow()    +1) *
//						 (qlSelRanges.at(iSR).rightColumn()-qlSelRanges.at(iSR).leftColumn()+1));
//	}
//	int boundingCells = ((maxRow-minRow+1) * (maxCol-minCol+1));
	if (boundingCells > 0)
	{	if (numCells != boundingCells)
		{	gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Clipboard Copy Error"),
								QString( "The clipboard copy feature is available only for a single, rectangular selection region." ) );
//								QString( "Number of individual selected cells (%1) not equal to overall bounding cell selection (%2)." ).arg(
//									QString::number( numCells ), QString::number( boundingCells ) ) );
		}
		else
		{	for (int i = minRow; i <= maxRow; i++)
			{	QStringList rowContents;
				for (int j = minCol; j <= maxCol; j++)
					rowContents << model()->index(i,j).data().toString();
				text += rowContents.join("\t");
				text += "\n";
			}
			QApplication::clipboard()->setText(text);
	}	}

	return !text.isEmpty();
}

bool BEMGrid::pasteSelectionFromClipboard()
{	bool bRetVal = false;
	QString text = QApplication::clipboard()->text();
//	int curRow = currentRow();
//	int curCol = currentColumn();
//		gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Pasting"), QString("Row: %1  -  Col: %2").arg( QString::number(curRow), QString::number(curCol) ) );
	if (text.isEmpty())
		gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), QString("No text available from clipboard to paste.") );
	else if (!selectionModel()->hasSelection())
		gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), QString("No cell selected as top-left for paste.") );
	else
	{	QStringList rowContents = text.split("\n", QString::SkipEmptyParts);
		QStringList columnContents;
//		QModelIndex initIndex = selectedIndexes().at(0);
//		auto initRow = initIndex.row();
//		auto initCol = initIndex.column();
		int maxRow, minRow, maxCol, minCol, numCells;
		int boundingCells = getSelectionBounds( maxRow, minRow, maxCol, minCol, numCells );
		int numTxtRows = (int) rowContents.size(), numTxtCols=0;
		for (auto i = 0; i < rowContents.size(); ++i)
		{	columnContents = rowContents.at(0).split("\t");
			if (numTxtCols < (int) columnContents.size())
				 numTxtCols = (int) columnContents.size();
		}
		bool copyDown=false, copyRight=false;
		QString sErrMsg;

//		int rowsPastBottom = initRow + numRows - rowCount();
//		int colsPastRight  = initCol + numCols - columnCount();
		int rowsPastBottom = minRow + numTxtRows - rowCount();
		int colsPastRight  = minCol + numTxtCols - columnCount();
		if (rowsPastBottom > 0 || colsPastRight > 0)
		{	if (rowsPastBottom > 0 && colsPastRight > 0)
				sErrMsg = QString( "Pasting clipboard contents would extend %1 row(s) past the bottom of the grid and %2 column(s) past the right edge." ).arg(
											QString::number(rowsPastBottom), QString::number(colsPastRight) );
			else if (rowsPastBottom > 0)
				sErrMsg = QString( "Pasting clipboard contents would extend %1 row(s) past the bottom of the grid." ).arg( QString::number(rowsPastBottom) );
			else
				sErrMsg = QString( "Pasting clipboard contents would extend %1 column(s) past the right edge of the grid." ).arg( QString::number(colsPastRight) );
		}
		else
		{

//	QString sPasteMsg = "Pasting from clipboard:";
//			for (auto i = 0; i < rowContents.size(); ++i)
//			{
//	sPasteMsg += QString( "\n   row %1:" ).arg( QString::number( initRow + i ) );
//				columnContents = rowContents.at(i).split("\t");
//				for (auto j = 0; j < columnContents.size(); ++j)
//				{
//	sPasteMsg += QString( "   %1-%2" ).arg( QString::number( initCol + j ), columnContents.at(j) );
////					model()->setData( model()->index( initRow + i, initCol + j ), columnContents.at(j) );
//				}
//			}
//	gridMessageBox( true /*beep*/, QMessageBox::NoIcon, QString("Paste from clipboard"), sPasteMsg );

			int textSelArea = numTxtRows * numTxtCols;
			if (numTxtRows == 1 && numTxtCols == 1)
			{	// a single clipboard value can be copied down AND right
				if (maxRow > minRow)
					copyDown = true;
				if (maxCol > minCol)
					copyRight = true;
			}
			else if (numTxtRows == 1 && numTxtCols > 1 &&
						numTxtCols == (maxCol-minCol+1))
				// a row of clipboard values can be copied down across all selected rows in grid
				copyDown = true;
			else if (numTxtCols == 1 && numTxtRows > 1 &&
						numTxtRows == (maxRow-minRow+1))
				// a column of clipboard values can be copied to the right across all selected columns in grid
				copyRight = true;
			else if ( ((maxCol-minCol+1) > 1 || (maxRow-minRow+1) > 1) &&
						 (numTxtCols != (maxCol-minCol+1) || numTxtRows != (maxRow-minRow+1)) )
				sErrMsg = QString( "Clipboard contents (%1 rows, %2 columns) must meet the dimensions of the selected grid region (%3 rows, %4 columns)." ).arg(
												QString::number(numTxtRows), QString::number(numTxtCols), QString::number(maxRow-minRow+1), QString::number(maxCol-minCol+1) );
		}
		if (!sErrMsg.isEmpty())
			gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), sErrMsg );
		else
		{	int iNumModsApplied = 0;		BEMGridMod* pMod;
			clearModData();
			for (auto i = 0; i < rowContents.size(); ++i)
			{	columnContents = rowContents.at(i).split("\t");
				int iObjIdx = getBEMObjectIndex( minRow + i );			ASSERT( iObjIdx>=0 );	// SAC 4/25/18
				for (auto j = 0; j < columnContents.size(); ++j)
				{	int iCol = minCol + j;
					if (iCol < (int) colData.size())
						pMod = addMod( minRow + i, iCol, columnContents.at(j), colData[iCol], iObjIdx );
					if (copyRight && (j==0 || copyDown))
					{	for (int j2 = (minCol+1); j2 <= maxCol; j2++)
							pMod = addMod( minRow + i, j2, columnContents.at(j), colData[j2], iObjIdx );
				}	}
				if (copyDown && i==0)
				{	for (int i2 = (minRow+1); i2 <= maxRow; i2++)
					{	iObjIdx = getBEMObjectIndex( i2 );			ASSERT( iObjIdx>=0 );	// SAC 4/25/18
						for (auto j2 = 0; j2 < columnContents.size(); ++j2)
						{	int iCol = minCol + j2;
							if (iCol < (int) colData.size())
								pMod = addMod( i2, iCol, columnContents.at(j2), colData[iCol], iObjIdx );
							if (copyRight && j2==0)
							{	for (int j3 = (minCol+1); j3 <= maxCol; j3++)
									pMod = addMod( i2, j3, columnContents.at(j2), colData[j3], iObjIdx );
							}
				}	}	}
			}
			if (confirmMods())
				iNumModsApplied = applyMods();

			bRetVal = (iNumModsApplied > 0);
		}
	}
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// BEMGridComboBox

BEMGridComboBox::BEMGridComboBox(QWidget *parent, long dbid, int objIdx)	// SAC 5/1/18
	: QComboBox(parent)
{	lDBID   = dbid;
	iObjIdx = objIdx;
	parentGrid = (BEMGrid*) parent;

//	connect( this, SIGNAL(currentIndexChanged(const QString & text)),
//				this, SLOT(currIndexChanged(const QString &text)) );
}

void BEMGridComboBox::keyPressEvent(QKeyEvent *event)  // to enable clipboard copy/paste
{
	if (event && event->matches(QKeySequence::Copy))
	{	QString text = currentText();
		if (!text.isEmpty())
			QApplication::clipboard()->setText(text);
	}
	else if (event && event->matches(QKeySequence::Paste))
	{	QString text = QApplication::clipboard()->text();
		if (!text.isEmpty())
			text = text.trimmed();
		if (text.isEmpty())
			gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), QString("No text available from clipboard to paste.") );
		else if (lDBID <= BEM_COMP_MULT || iObjIdx < 0)
			gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), QString("Lacking information needed to paste clipboard text to building model.") );
		else
		{	int iSelIdx = findText( text, Qt::MatchFixedString );  // case INsensitive match - for case sensitive replace w/ ( Qt::MatchExactly | Qt::MatchCaseSensitive )
			if (iSelIdx < 0)
				gridMessageBox( true /*beep*/, QMessageBox::Critical, QString("Paste Error"), QString("Clipboard text '%1' not found in list of selections.").arg(text) );
			else if (iSelIdx != currentIndex())
				setCurrentIndex( iSelIdx );
	}	}
	else
		QComboBox::keyPressEvent(event);
}

void BEMGridComboBox::gridMessageBox( bool beep, QMessageBox::Icon icon, const QString &title, const QString &text,
										QMessageBox::StandardButtons buttons /*=QMessageBox::NoButton*/ )
{	if (beep)
		MessageBeep( MB_OK );
	QMessageBox msgBox( icon, title, text, buttons, parentWidget() );
	//msgBox.setWindowIcon( QIcon( pxmIcon ) );
	msgBox.exec();
}

//void BEMGridComboBox::currIndexChanged(const QString &text)
//{
//	if (!text.isEmpty() && parentGrid && !parentGrid->isBeingInitialized())
//		MessageBeep( MB_OK );
//}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static QString GetBEMStringAndStatus( long lDBID, int& iStatus, int& iError, int iObjIdx, int iDecPrec, bool bCouldBeNoneEnum )
{	QString qsData;
	iStatus = iError = 0;
	if (lDBID > 0)
	{	int iSpecialVal;
		//  BEMP_Int  0 /   BEMP_Flt  1 /   BEMP_Sym  2 /   BEMP_Str  3 /   BEMP_Obj  4 /   BEMP_QStr 5			// types of property (BEMPropertyType)
		qsData = BEMPX_GetStringAndStatus( lDBID, iStatus, iSpecialVal, iError, iObjIdx, BEMO_User,
														-1 /*iBEMProcIdx*/, TRUE /*bAddCommas*/, iDecPrec );  //, const char* pszDefault=NULL, long lDBID2=0 );
		if (qsData.isEmpty() && bCouldBeNoneEnum)
			qsData = szNone;
	}
	return qsData;
}

static QComboBox* InitComboEnums( long lDBID, int iObjIdx, const QFont &font, QWidget* parent )
{	QComboBox *qcmbx = NULL;
	if (lDBID > 0)
	{	qcmbx = new QComboBox( parent );
		if (qcmbx)
		{	//qcmbx->setFrame( false );
			qcmbx->setFont( font );
			int iStatus, iError;
			QString qsData = GetBEMStringAndStatus( lDBID, iStatus, iError, iObjIdx, 0, false );
			if (iStatus >= 0)
				qcmbx->setStyleSheet( QString( "QComboBox { color: rgb(%1, %2, %3); }" ).arg(
												QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 0 ) ),
												QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 1 ) ),
												QString::number( GetCUITextRGB( iStatus + NUM_RESERVED_TEXT_COLORS, 2 ) ) ) );
			//			qcmbx->setForeground( *BEMTextQBrush( iStatus + NUM_RESERVED_TEXT_COLORS ) );	// SAC 3/23/18
			if (LoadComboBoxEnumList( qcmbx, lDBID, iObjIdx ))
			{	if (qsData.length() > 0)
					qcmbx->setCurrentText( qsData );
			}
			else
			{	assert( false );
		}	}
		else
		{	assert( false );
	}	}
	return qcmbx;
}


/////////////////////////////////////////////////////////////////////////////
//  BEMGridOptionsDialog
/////////////////////////////////////////////////////////////////////////////

BEMGridOptionsDialog::BEMGridOptionsDialog(BEMGrid *pGrid, QWidget *parent)
	: QDialog(parent)
{
//	font.setFamily( "MS Sans Serif" );
	font.setFamily( "Verdana" );
	font.setPointSize( 9 );
	setFont( font );
//	fontBold.setFamily( "MS Sans Serif" );
	fontBold.setFamily( "Verdana" );
	fontBold.setPointSize( 10 );
	fontBold.setBold( true );

	setSizeGripEnabled(false);

	uiBeingInitialized = true;
	grid = pGrid;

	QLabel *lblFilter         = new QLabel(tr("Filter Objects to Include in Grid"));
	QLabel *lblFilterProperty = new QLabel(tr("   Property to Filter On:"));
	QLabel *lblFilterValue    = new QLabel(tr("   Condition to Include Object:"));
//	QComboBox *cbFilterProperty;     
//	QComboBox *cbFilterCondition;  
//	QComboBox *cbFilterSelection;  
//	QTextEdit *txtFilterValue;
	lblFilterSpace = new QLabel(tr("   "));

//	// 0-"Nothing"  1-"Modified Object"  (future? 2-"Object Family")  3-"Entire Model"
	cbDfltAfterMod      = InitComboEnums( elDBID_Proj_DefaultOptionInp , 0 /*iObjIdx*/, font, this );
	cbDfltAfterObject   = InitComboEnums( elDBID_Proj_DefaultOptionObj , 0 /*iObjIdx*/, font, this );
	cbDfltClosingDialog = InitComboEnums( elDBID_Proj_DefaultOptionDone, 0 /*iObjIdx*/, font, this );
	lblDefaults          = new QLabel(tr("Program Default Refresh"));
	lblDfltAfterMod      = new QLabel(tr("   Following Each Modification:"));
	lblDfltAfterObject   = new QLabel(tr("   When Changing Object Type or Topic:"));
	lblDfltClosingDialog = new QLabel(tr("   When Closing Dialog:"));
	lblDefaults->setFont( fontBold );
	lblDfltAfterMod->setFont( font );
	lblDfltAfterObject->setFont( font );
	lblDfltClosingDialog->setFont( font );
	lblDfltSpace = new QLabel(tr("   "));

	btns = new QDialogButtonBox( QDialogButtonBox::Ok );

	QGridLayout *optsLayout = new QGridLayout;
	optsLayout->addWidget(lblFilter, 0, 0);
	optsLayout->addWidget(lblFilterProperty, 1, 0);
//	optsLayout->addWidget(cbFilterProperty, 1, 1, 1, 2);
	optsLayout->addWidget(lblFilterValue, 2, 0);
//	optsLayout->addWidget(cbFilterCondition, 2, 1);
//	optsLayout->addWidget(cbFilterSelection, 2, 2);
//	optsLayout->addWidget(txtFilterValue, 2, 2);
	optsLayout->addWidget(lblFilterSpace, 3, 2);

	optsLayout->addWidget(lblDefaults, 4, 0);
	optsLayout->addWidget(lblDfltAfterMod, 5, 0);
	optsLayout->addWidget(cbDfltAfterMod, 5, 1, 1, 2);
	optsLayout->addWidget(lblDfltAfterObject, 6, 0);
	optsLayout->addWidget(cbDfltAfterObject, 6, 1, 1, 2);
	optsLayout->addWidget(lblDfltClosingDialog, 7, 0);
	optsLayout->addWidget(cbDfltClosingDialog, 7, 1, 1, 2);
	optsLayout->addWidget(lblDfltSpace, 8, 2);
	optsLayout->addWidget(btns, 9, 2);
//	optsLayout->setColumnStretch(2, 0);
//	window->layout()->setSizeConstraint( QLayout::SetFixedSize );
	optsLayout->setSizeConstraint( QLayout::SetFixedSize );
	setLayout(optsLayout);

	setWindowTitle( tr("Grid Options") );
	setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );  // removes '?' icon button

	if (cbDfltAfterMod)
		connect( cbDfltAfterMod, SIGNAL(currentIndexChanged(int)),
					this, SLOT(updateDefaultAfterMod()) );
	if (cbDfltAfterObject)
		connect( cbDfltAfterObject, SIGNAL(currentIndexChanged(int)),
					this, SLOT(updateDefaultAfterObject()) );
	if (cbDfltClosingDialog)
		connect( cbDfltClosingDialog, SIGNAL(currentIndexChanged(int)),
					this, SLOT(updateDefaultClosingDialog()) );
	if (btns)
		connect(btns, &QDialogButtonBox::accepted, this, &QDialog::accept);

	uiBeingInitialized = false;
}

void BEMGridOptionsDialog::updateDefaultAfterMod()
{	if (!uiBeingInitialized && grid && cbDfltAfterMod)
		grid->setDefaultOptionInp( cbDfltAfterMod->currentData().toInt() );
}
void BEMGridOptionsDialog::updateDefaultAfterObject()
{	if (!uiBeingInitialized && grid && cbDfltAfterObject)
		grid->setDefaultOptionObj( cbDfltAfterObject->currentData().toInt() );
}
void BEMGridOptionsDialog::updateDefaultClosingDialog()
{	if (!uiBeingInitialized && grid && cbDfltClosingDialog)
		grid->setDefaultOptionDone( cbDfltClosingDialog->currentData().toInt() );
}


/////////////////////////////////////////////////////////////////////////////
//  BEMGridDialog
/////////////////////////////////////////////////////////////////////////////


BEMGridDialog::BEMGridDialog(CMainFrame* pMainFrm, int iBEMClass, int iOccur, QWidget *parent)
	: QDialog(parent)
{
//	bemClass = iBEMClass;
	gridBEMClass = -1;
	gridTopic = 0;
	mainFrm = pMainFrm;
	refreshingTopicList = false;

	menuOptions = NULL;
	actionCopy = NULL;
	actionPaste = NULL;
	actionOptions = NULL;

//	font.setFamily( "MS Sans Serif" );
	font.setFamily( "Verdana" );
	font.setPointSize( 9 );
	setFont( font );
//	fontBold.setFamily( "MS Sans Serif" );
	fontBold.setFamily( "Verdana" );
	fontBold.setPointSize( 10 );
	fontBold.setBold( true );

	setSizeGripEnabled(true);

// QWidget::setWindowIcon( QIcon );
	HICON hIcon = (HICON)LoadImage( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDR_MAINFRAME ), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADTRANSPARENT );
//	setWindowIcon( QIcon( QtWin::fromHICON( hIcon ) ) );
	pxmIcon = QtWin::fromHICON( hIcon );
	setWindowIcon( QIcon( pxmIcon ) );
	::DestroyIcon( hIcon );

//	lblObjectType = new QLabel(tr("Object Type:"));
//	lblTopic = new QLabel(tr("   Topic:"));
	cbObjectType = createComboBox();
	cbTopic = createComboBox();
	btnMenu = createIconButton(IDI_MENU);
	grid = createBEMGrid();

//	lblObjectType->setFont( font );
//	lblTopic->setFont( font );
	cbObjectType->setFont( font );
	cbTopic->setFont( font );
	grid->setFont( font );

	initObjectTypeList( iBEMClass );

	QGridLayout *mainLayout = new QGridLayout;
//	mainLayout->addWidget(lblObjectType, 0, 0);
//	mainLayout->addWidget(cbObjectType, 0, 1);
//	mainLayout->addWidget(lblTopic, 0, 2);
//	mainLayout->addWidget(cbTopic, 0, 3);
	mainLayout->addWidget(cbObjectType, 0, 0);
	mainLayout->addWidget(cbTopic, 0, 1);
	mainLayout->addWidget(btnMenu, 0, 2);
	mainLayout->addWidget(grid, 1, 0, 3, 3);
	mainLayout->setColumnStretch(2, 0);
	setLayout(mainLayout);

	CString sProgName;
	if (!GetProgramVersion( sProgName, TRUE /*bPrependName*/, FALSE /*bLongVer*/ ))
		sProgName = esProgramName;
	sProgName = "Grid - " + sProgName;
	setWindowTitle( ((const char*) sProgName) );
	setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );

	resize(1000, 540);
	if (iBEMClass < 1)
		iBEMClass = getObjectType();
	gridBEMClass = iBEMClass;
//	gridTopic    = getTopic();
//	grid->initGrid( gridBEMClass, gridTopic, iOccur /*iSelObjectIdx1*/ );

	connect( cbObjectType, SIGNAL(currentIndexChanged(int)),
				this, SLOT(updateObjectType()) );
	connect( cbTopic, SIGNAL(currentIndexChanged(int)),
				this, SLOT(updateTopic()) );

	initTopicList( 0 );
	updateTopic();
}

void BEMGridDialog::closeEvent(QCloseEvent *e)
{
	int iGotHere=1;
	if (mainFrm)
		mainFrm->PostBEMGridClose();
	QDialog::closeEvent(e);
}
//void BEMGridDialog::finished(int result)
//{
//	int iGotHere=1;
//	QDialog::finished(result);
//}

void BEMGridDialog::updateObjectType()
{
	int iCurObjType = getObjectType();
	if (iCurObjType != gridBEMClass)
	{	gridBEMClass = iCurObjType;
		initTopicList( 0 );
		gridTopic = -1;
		updateTopic();
	}
}

void BEMGridDialog::updateTopic()
{
	if (!refreshingTopicList)
	{	gridTopic = getTopic();
		if (gridTopic > 0)
		{
			int iTIdx = cbTopic->currentIndex();
			if (iTIdx >= 0 && iTIdx < (int) topicNumControls.size())
			{	grid->clear();
				grid->initGrid( gridBEMClass, gridTopic, topicNumControls[iTIdx], topicFirstCtrlIdx[iTIdx], -1 /*iSelObjectIdx1*/ );
	}	}	}
}


QComboBox *BEMGridDialog::createComboBox()
{
	QComboBox *comboBox = new QComboBox();
//	QFontMetrics fm( font );
//	comboBox->setFixedHeight( fm.height()+10 );
	return comboBox;
}

QPushButton *BEMGridDialog::createIconButton(int iconID)  //, const char *member)
{
	//QPushButton *button = new QPushButton(text);
	QPushButton *button = new QPushButton("");

	HICON hIcon = (HICON)LoadImage( GetModuleHandle( nullptr ), MAKEINTRESOURCE( iconID ), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADTRANSPARENT );
	pxmMenuIcon = QtWin::fromHICON( hIcon );
	button->setIcon( QIcon( pxmMenuIcon ) );
	::DestroyIcon( hIcon );

	menuOptions = new QMenu(this);
	connect(menuOptions, SIGNAL(aboutToShow()),
				this, SLOT(aboutToShowOptionsMenu()));
	connect(menuOptions, SIGNAL(triggered(QAction*)),
				this, SLOT(triggeredOption(QAction*)));
	actionCopy = new QAction(tr("Copy Selection"), this);
	actionCopy->setEnabled(false);
	menuOptions->addAction(actionCopy);
	actionPaste = new QAction(tr("Paste"), this);
	actionPaste->setEnabled(false);
	menuOptions->addAction(actionPaste);
	actionRestoreOrder = new QAction(tr("Restore Row Order"), this);
	actionRestoreOrder->setEnabled(false);
	menuOptions->addAction(actionRestoreOrder);
	actionOptions = new QAction(tr("Options..."), this);
	actionOptions->setEnabled(true);
	menuOptions->addAction(actionOptions);
	button->setMenu(menuOptions);

	button->setFixedHeight( 26 );
	button->setFixedWidth(  45 );
	button->setFlat( true );

	return button;
}

void BEMGridDialog::aboutToShowOptionsMenu()
{
	if (!actionCopy || !actionPaste || !actionOptions || !actionRestoreOrder || !grid)
	{	assert( false );
	}
	else
	{
		actionCopy->setEnabled( !grid->haveSelection() );
		actionPaste->setEnabled( !QApplication::clipboard()->text().isEmpty() );
		actionRestoreOrder->setEnabled( true );  // only if some alternative sort order is currently active ??
		actionOptions->setEnabled( true );
	}
//	else if (actionCopy->isEnabled())
//	{	actionCopy->setEnabled(false);
//		actionPaste->setEnabled(true);
//	}
//	else
//	{	actionCopy->setEnabled(true);
//		actionPaste->setEnabled(false);
//	}
}

void BEMGridDialog::triggeredOption(QAction *action)
{
	if (grid && action == actionCopy)
		grid->copySelectionToClipboard();
	else if (grid && action == actionPaste)
		grid->pasteSelectionFromClipboard();
	else if (grid && action == actionRestoreOrder)
		grid->sortByColumn( grid->columnCount()-1, Qt::AscendingOrder );
	else if (grid && action == actionOptions)
	{	BEMGridOptionsDialog *optsDialog = new BEMGridOptionsDialog( grid, this );
		optsDialog->exec();
		delete optsDialog;
	}
	else
		BEMMessageBox( "unknown action..." );
}

BEMGrid *BEMGridDialog::createBEMGrid()
{
	BEMGrid *bemGrid = new BEMGrid(this, mainFrm, &pxmIcon, &font);
	return bemGrid;
}

int BEMGridDialog::getObjectType()
{	if (cbObjectType)
		return cbObjectType->currentData().toInt();
	return -1;
}

void BEMGridDialog::initObjectTypeList( int bemClass )
{
	if (cbObjectType)
	{	cbObjectType->clear();
		int iError, idx=0, iSelIdx=-1, iNumClasses = BEMPX_GetNumClasses();
		for (int ic=1; ic <= iNumClasses; ic++)
		{	int iNumObjs = BEMPX_GetNumObjects( ic );  //, BEM_ObjType eObjType=BEMO_User, int iBEMProcIdx=-1 );
			BEMClass* pClass = BEMPX_GetClass( ic, iError );
			//if (iNumObjs > 1 && pClass)
			if (iNumObjs > 0 && pClass)
			//if (iNumObjs > 0 && pClass && (pClass->getMaxDefinable()==0 || pClass->getMaxDefinable() > 1))  // SAC 8/8/18 - revised to include classes w/ only 1 object defined (as long as more can be created)
			{	if (bemClass < 0)
					bemClass = ic;
				if (bemClass == ic)
					iSelIdx = idx;
				QString  itemText = pClass->getLongName();
				QVariant itemData = ic;
				cbObjectType->addItem( itemText, itemData );
				idx++;
		}	}
		if (iSelIdx >= 0)
			cbObjectType->setCurrentIndex( iSelIdx );
		cbObjectType->setMaxVisibleItems( 30 );
	}
}

int BEMGridDialog::getTopic()
{	if (cbTopic)
		return cbTopic->currentData().toInt();
	return -1;
}

void BEMGridDialog::initTopicList( int idx )
{
	if (cbTopic)
	{	refreshingTopicList = true;
		cbTopic->clear();
		topicNumControls.clear();
		topicFirstCtrlIdx.clear();
		int iNumTabs    = BEMPUIX_GetNumConsecutiveDialogTabIDs( gridBEMClass, 0 /*iUIMode*/ );
		int iFirstTabID = BEMPUIX_GetFirstDialogTabID( gridBEMClass, 0 /*iUIMode*/ );
		if (iNumTabs > 0 && iFirstTabID)
		{	QString qsCaption;
			int iPageID, iModules, iNumControls, iFirstCtrlIdx, iLastCtrlIdx;
			for (int i=0; i < iNumTabs; i++)
				if (BEMPUIX_GetUIPageData( gridBEMClass, i, 0 /*iUIMode*/, !ebDisplayAllUIControls,
													qsCaption, iPageID, iModules, iNumControls, iFirstCtrlIdx, iLastCtrlIdx ))
				{	QVariant itemData = iPageID;
					cbTopic->addItem( qsCaption.trimmed(), itemData );
					topicNumControls.push_back(  iNumControls  );
					topicFirstCtrlIdx.push_back( iFirstCtrlIdx );
				}
		}
		if (idx >= 0 && idx < (int) topicNumControls.size())
			cbTopic->setCurrentIndex( idx );
		cbTopic->setMaxVisibleItems( 30 );
		refreshingTopicList = false;
	}
}





//   for (int i=0; (i<iNumPages && i<m_iMaxTabs); i++)
//   {
//      CBEMPUIPage* pPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, i, m_iUIMode );
//      if (pPage && (m_bDisplayAllUIControls || eScreenData.PageHasActiveControls( pPage )))
//      {
//         TabCtrlItem.pszText = pPage->m_sCaption.GetBuffer( 0 );
//      	m_BEMProcTabCtrl.InsertItem( iPg++, &TabCtrlItem );
//         pPage->m_sCaption.ReleaseBuffer();
//         // SAC 6/29/00 - added to provide map from actual tab index to index of tab in screen data.
//         //               This is necessary since middle screen data tabs may NOT be present while later ones are.
//         m_waValidPageIdxs.Add( (WORD) i );


//struct CBEMPUIPage
//{
//// Attributes
//   // Page Data
//   CString  m_sBEMClass;
//   int      m_iPageId;
//   int      m_iModules;
//   CString  m_sCaption;
//   int      m_iNumCtrls;
//   // Other Page Data set by Init function
//   int      m_iFirstCtrlIdx;
//   int      m_iLastCtrlIdx;
//   int      m_iClassId;


//   // Create controls for one of the component-specific pages
//   m_pTDPage = eScreenData.GetPageByClassAndIndex( m_iBEMClass, m_waValidPageIdxs[ iPage ], m_iUIMode );
//   if (m_pTDPage)
//   {
//      CWaitCursor wait;
//      m_lContextHelpID = 0;
//	  int i=m_pTDPage->m_iFirstCtrlIdx;
//      for (; i<=m_pTDPage->m_iLastCtrlIdx; i++)
//      {
//         CBEMPUIControl* pCtrl = eScreenData.GetControlByIndex( i );
//         if ( pCtrl && (m_bDisplayAllUIControls || BEMPX_GetCompDisplay( pCtrl->m_lDBID, 0 )) )
//         {
//            // SAC 9/10/00 - added non-editable DBID stuff
//            BOOL bAllowEdits = m_bAllowEdits;
//            for (int j=0; (bAllowEdits && j < m_dwaNonEditableDBIDs.GetSize()); j++)
//            {
//               if ((DWORD) pCtrl->m_lDBID == m_dwaNonEditableDBIDs[j])
//                  bAllowEdits = FALSE;
//            }
//
//            pCtrl->m_bActive = TRUE;
//            if (pCtrl->m_uiCtrlType == TDCT_Edit)
//            {
//               CEditCtl* pEdit = new CEditCtl();
//               pEdit->Create( this, pCtrl, bAllowEdits );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_Combo)
//            {
//               CComboBoxCtl* pCmbb = new CComboBoxCtl();
//               pCmbb->Create( this, pCtrl, bAllowEdits );
//            }
//            else if ( (pCtrl->m_uiCtrlType == TDCT_Button) ||
//                      (pCtrl->m_uiCtrlType == TDCT_Check)  || 
//                      (pCtrl->m_uiCtrlType == TDCT_RadioG) ||
//                      (pCtrl->m_uiCtrlType == TDCT_Radio)  )
//            {
//               CButtonCtl* pBtn = new CButtonCtl();
//               pBtn->Create( this, pCtrl, bAllowEdits );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_WMF)
//            {
//               CWMFCtl* pWMF = new CWMFCtl();
//               pWMF->Create( this, pCtrl, 0, m_iTabCtrlHt /*m_iFrmHeight*/, m_iTabCtrlWd /*m_iFrmWidth*/, ::GetSysColor( COLOR_WINDOW ), TRUE );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_Date)
//            {
//                CDateTimeCtl* pDate = new CDateTimeCtl();
//                pDate->Create( this, pCtrl, bAllowEdits );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_Spread)  // SAC 6/17/01
//            {
//               MessageBox( "CSACDlg Error:  Spreadsheet control not available." );
//               pCtrl->m_bActive = FALSE;
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_List)   // SAC 1/19/12
//            {
//                CBEMProcCtrlList* pList = new CBEMProcCtrlList();
//                pList->Create( this, pCtrl );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_ChkLst)   // SAC 1/19/12
//            {
//                CBEMProcCtrlCheckListBox* pChkList = new CBEMProcCtrlCheckListBox();
//                pChkList->Create( this, pCtrl );
//            }
//            else if (pCtrl->m_uiCtrlType == TDCT_RTF)   // SAC 1/19/12
//            {
//                CBEMProcCtrlRTF* pRTF = new CBEMProcCtrlRTF();
//                pRTF->Create( this, pCtrl, TRUE /*bTabbedDlgShift*/ );
//            }
//            else
//               pCtrl->m_bActive = FALSE;



