// XMLParse.h : implementation of XML parsing functions (based on Qt)
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

#include "stdafx.h"
#include "ComplianceUI.h"

#include "ComplianceUIDoc.h"
#include "CUIGlobl.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMCmpMgr\BEMCmpMgr.h"

#include "XMLParse.h"

#include <QtXml/QtXml>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool getSubElem( QDomElement& elem, QDomElement& subElem, QString sSubElem )
{	bool bRetVal=false;
	QDomNodeList nodeList = elem.elementsByTagName( sSubElem );
	if (nodeList.count() > 0)
	{	assert( nodeList.count() == 1 );
		QDomNode node = nodeList.item(0);
		subElem = node.toElement();
		bRetVal=true;
	}
	return bRetVal;
}

QString getSubElemString( QDomElement& elem, QString sSubElem )
{	QString sRetVal;
	QDomNodeList nodeList = elem.elementsByTagName( sSubElem );
	if (nodeList.count() > 0)
	{	assert( nodeList.count() == 1 );
		QDomNode node = nodeList.item(0);
		QDomElement subElem = node.toElement();
		sRetVal = subElem.text();
	}
	return sRetVal;
}


//int eiBDBCID_PolyLp     = 0;
//int eiBDBCID_CartesianPt = 0;
//	elDBID_CartesianPt_Coord  = BEMPX_GetDatabaseID( "Coord",    eiBDBCID_CartesianPt );       // BEMP_Flt,  3,  0,  1, "ft",  "X, Y, Z coordinates of polyloop vertex"   - SAC 2/21/17

//extern long elDBID_Plane_Type;            // BEMP_Sym ->  3:"PV Array"   - SAC 2/21/17
//extern long elDBID_Plane_PolyLpRef;       // BEMP_Obj -> PolyLp   - SAC 2/21/17
//extern long elDBID_Shade_Type;            // BEMP_Sym ->  0:"- select type -"  1:"Site Shade"  2:"Building Shade"   - SAC 2/21/17
//extern long elDBID_Shade_PolyLpRef;       // BEMP_Obj -> PolyLp   - SAC 2/21/17

int ProcessXMLElement_Shade( int /*iSchema*/, QDomElement& elem, int lvl, QString& qsXMLMsg )
{
	QString sName = getSubElemString( elem, "Name" );
	if (sName.isEmpty())
		sName = elem.attribute( "id" );
	assert( !sName.isEmpty() );

	QString sFamNm = getSubElemString( elem, "FamilyName" );
	bool bFamInclPV   = (!sFamNm.isEmpty() && sFamNm.indexOf("Photovoltaic") >= 0);
	bool bFamInclBldg = (!sFamNm.isEmpty() && sFamNm.indexOf("Building") >= 0);
	long iShadeType = (bFamInclBldg ? 2 : 1);

	int iNumPolyLpVerts = 0;
	QDomElement elemPlanarGeom;
	if (getSubElem( elem, elemPlanarGeom, "PlanarGeometry" ))
	{
		if (bFamInclPV)
			sName += (bFamInclBldg ? " (bldg pv)" : (sFamNm.indexOf("Site") >= 0 ? " (site pv)" : " (pv)"));

		BEMObject* pShadeObj = BEMPX_CreateObject( eiBDBCID_Shade, sName.toLatin1().constData() );		assert( pShadeObj );
		if (pShadeObj)
		{	sName = pShadeObj->getName();
			int iShadeObjIdx = BEMPX_GetObjectIndex( pShadeObj->getClass(), pShadeObj );						assert( iShadeObjIdx >= 0 );
			BEMPX_SetBEMData( elDBID_Shade_Type, BEMP_Int, &iShadeType, BEMO_User, iShadeObjIdx );

			int iCPIdx = -1;
			BEMObject* pPLObj = NULL;
			QDomElement ePL;
			if (getSubElem( elemPlanarGeom, ePL, "PolyLoop" ))
		//	QDomNode nPL = elem.firstChild();							assert( !nPL.isNull() );
		//	if (!nPL.isNull())
			{	bool bDblOK;
		//		QDomElement ePL = nPL.toElement();
				QDomNode nCP = ePL.firstChild();							assert( !nCP.isNull() );
				while(!nCP.isNull())
				{	QDomElement eCP = nCP.toElement();
					iCPIdx++;
					if (iCPIdx==0)
	//				{	QString sPLNm = (bObjPlane ? "plane " : "shd ");   sPLNm += sName;   sPLNm += " poly";
					{	QString sPLNm = "shd ";   sPLNm += sName;   sPLNm += " poly";
						pPLObj = BEMPX_CreateObject( eiBDBCID_PolyLp, sPLNm.toLatin1().constData(), pShadeObj );		assert( pPLObj );
					}

					BEMObject* pCPObj = BEMPX_CreateObject( eiBDBCID_CartesianPt, NULL, pPLObj /*parent*/ );			assert( pCPObj );
					if (pCPObj)
					{	iNumPolyLpVerts++;
						iCPIdx = BEMPX_GetObjectIndex( pCPObj->getClass(), pCPObj );											assert( iCPIdx >= 0 );
						int iCoordIdx = 0;
						QDomNode nCoord = eCP.firstChild();								assert( !nCoord.isNull() );
						while(!nCoord.isNull())
						{	QDomElement eCoord = nCoord.toElement();
							QString sCoord = eCoord.text();
							double dCoord = sCoord.toDouble( &bDblOK );				assert( bDblOK && iCoordIdx < 3 );
							if (bDblOK && iCoordIdx < 3)
								BEMPX_SetBEMData( elDBID_CartesianPt_Coord + iCoordIdx++, BEMP_Flt, &dCoord, BEMO_User, iCPIdx );

							nCoord = nCoord.nextSibling();
						}
					}
					nCP = nCP.nextSibling();
			 	}

//#define  BEMP_Int  0		// types of property (BEMPropertyType)
//#define  BEMP_Flt  1
//#define  BEMP_Sym  2
//#define  BEMP_Str  3
//#define  BEMP_Obj  4
//#define  BEMP_QStr 5		// NOT unique storage type in database, only used in conjunction w/ BEMPX_SetBEMData() to pass QString directly in (since casting to const char* blasts special characters)
			}
	}	}

	QString spc = "   ";
	for (int i=0; i<lvl; i++)
		spc += "   ";
	QString sObjTyp = (bFamInclBldg ? "Bldg " : (sFamNm.indexOf("Site") >= 0 ? "Site " : ""));
	sObjTyp += "Shade";
	qsXMLMsg += QString( "%1created %2 '%3' with %4 PolyLp vertices\n" ).arg( spc, sObjTyp, sName, QString::number(iNumPolyLpVerts) );
	return (iNumPolyLpVerts > 0 ? 1 : 0);
}

BEMObject* ParsePolyLpXML( int iSchema, QDomElement& elem )
{	BEMObject* pObj = NULL;
	if (iSchema == Schema_GBXML)
	{
		QString sTag = elem.tagName();
	}
	return pObj;
}

////////////////////////////////////////////////////////////////////////////////

int ProcessXMLElement( int iSchema, QDomElement& elem, int lvl, QString& qsXMLMsg )
{	int iRetVal=0;
	QString spc = "   ";
	for (int i=0; i<lvl; i++)
		spc += "   ";
	qsXMLMsg += QString( "%1%2\n" ).arg( spc, elem.tagName() );

	bool bSkip = (elem.tagName().compare("Location")==0 || elem.tagName().compare("Building")==0 || elem.tagName().compare("Construction")==0);
	if (!bSkip)
	{
		int iProcSurfType = 0;
		if (elem.tagName().compare("Surface")==0)
		{	QString sAtt = elem.attribute( "surfaceType" );
			if (sAtt.compare("Shade")==0)
				iProcSurfType = 1;
		}
		switch (iProcSurfType)
		{	case  1 : iRetVal += ProcessXMLElement_Shade( iSchema, elem, lvl+1, qsXMLMsg );  break;
			default : {	QDomNode n = elem.firstChild();
							while(!n.isNull())
							{	QDomElement e = n.toElement(); // try to convert the node to an element.
								iRetVal += ProcessXMLElement( iSchema, e, lvl+1, qsXMLMsg );
								n = n.nextSibling();
						 }	}  break;
		}
	}


/*
QString qsXMLMsg = "XML contents:\n";  int iNumNodes=0, iNumChild=0, iNumGChild=0;
QDomNode n = docElem.firstChild();
while(!n.isNull()) {
    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull()) {
//        cout << qPrintable(e.tagName()) << endl; // the node really is an element.
		qsXMLMsg += QString( "   %1\n" ).arg( e.tagName() );
		iNumNodes++;

		QDomNode n2 = e.firstChild();
		bool bSkip2 = false;
		while(!n2.isNull()) {
		    QDomElement e2 = n2.toElement(); // try to convert the node to an element.
		    bSkip2 = (e2.tagName().compare("Location")==0 || e2.tagName().compare("Building")==0 || e2.tagName().compare("Construction")==0);
		    if(!bSkip2 && !e2.isNull()) {
// 		       cout << qPrintable(e.tagName()) << endl; // the node really is an element.
				qsXMLMsg += QString( "      %1" ).arg( e2.tagName() );
				if (e2.tagName().compare("Surface")==0)
				{	QString sAtt = e2.attribute( "id" );
					if (!sAtt.isEmpty())
						qsXMLMsg += QString( "  id = '%1'" ).arg( sAtt );
					sAtt = e2.attribute( "surfaceType" );
					if (!sAtt.isEmpty())
						qsXMLMsg += QString( "  surfaceType = '%1'" ).arg( sAtt );
					bool bIsShade = (sAtt.compare("Shade")==0);

					if (bIsShade)
					{	QDomNodeList famNodeList = e2.elementsByTagName("FamilyName");
						if (famNodeList.count() > 0)
						{	assert( famNodeList.count() == 1 );
							QDomNode famNode = famNodeList.item(0);
							QDomElement famElem = famNode.toElement();
							QString sFamNm = famElem.text();
							if (sFamNm.compare("Photovoltaic Panel")==0)
								qsXMLMsg += "  shadeType = 'PV Array'";
							else
								qsXMLMsg += QString( "  shadeType = 'Site Shade' (FamNm='%1')" ).arg( sFamNm );
						}
						else
							qsXMLMsg += "  shadeType = 'Site Shade'";
					}
					else
						qsXMLMsg += "  not a shade";

				}
				qsXMLMsg += "\n";
				iNumChild++;

				QDomNode n3 = e2.firstChild();
				while(!n3.isNull()) {
				    QDomElement e3 = n3.toElement(); // try to convert the node to an element.
				    if(!e3.isNull()) {
// 				       cout << qPrintable(e.tagName()) << endl; // the node really is an element.
						qsXMLMsg += QString( "         %1\n" ).arg( e3.tagName() );
						iNumGChild++;
				    }
				    n3 = n3.nextSibling();
				 }

		    }
		    n2 = n2.nextSibling();
		}

    }
    n = n.nextSibling();
}

qsXMLMsg += QString( "%1 nodes, %2 children, %3 grand children" ).arg( QString::number( iNumNodes ), QString::number( iNumChild ), QString::number( iNumGChild ) );
BEMMessageBox( qsXMLMsg );
*/
	return iRetVal;
}


