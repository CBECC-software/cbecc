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

/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <assert.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QtWidgets>
#include <QtGui\5.3.2\QtGui\qpa/qplatformnativeinterface.h>

#include "BEMTest.h"
#include "../BEMProc/BEMProc.h"
#include "../BEMCmpMgr/BEMCmpMgrCom.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	BEMTest bemTestUI;
	bemTestUI.show();
	return app.exec();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GetFullPath( QString& sFilePath, QString sDir )
{	int iLastSlash = std::max( sDir.lastIndexOf('/'), sDir.lastIndexOf('\\') );
	if (iLastSlash < 1)
	{	assert( false );
		return;
	}
	else if (iLastSlash == (int) sDir.length()-1)
		sDir = sDir.left( sDir.length()-1 );

	while (sFilePath.indexOf("..") == 0)
	{	sFilePath = sFilePath.right( sFilePath.length()-3 );
		iLastSlash = std::max( sDir.lastIndexOf('/'), sDir.lastIndexOf('\\') );
		if (iLastSlash < 1)
		{	assert( false );
			return;
		}
		else
			sDir = sDir.left( iLastSlash );
	}
	sFilePath = sDir + QChar('/') + sFilePath;
}

////////////////////////////////////////////////////////////////////////////////

//! [0]
BEMTest::BEMTest(QWidget *parent)
	: QWidget(parent)
{
	font.setFamily( "MS Sans Serif" );
	font.setPointSize( 10 );
	setFont( font );
	fontBold.setFamily( "MS Sans Serif" );
	fontBold.setPointSize( 10 );
	fontBold.setBold( true );


	dmCompiledBrowseButton = createButton(tr("..."), SLOT(browseDMCompiled()));
	rlCompiledBrowseButton = createButton(tr("..."), SLOT(browseRLCompiled()));
	inpModelBrowseButton = createButton(tr("..."), SLOT(browseInpModel()));
	loadButton = createButton(tr("  &Load && Default Model  "), SLOT(loadModel()));

	wthrDirBrowseButton = createButton(tr("..."), SLOT(browseWthrDir()));
	analLoadedFile = createButton(tr("  Analyze Loaded Bldg  "), SLOT(analyzeLoadedFile()));
	analFileViaAPI = createButton(tr("  Analyze Bldg via API  "), SLOT(analyzeFileViaAPI()));


	dmCompiledTextEdit = createTextEdit();
	rlCompiledTextEdit = createTextEdit();
	inpModelTextEdit = createTextEdit();
	wthrDirTextEdit = createTextEdit();
	analOptsTextEdit = createTextEdit();


	dmCompiledLabel = new QLabel(tr("   Compiled Data Model File:"));
	rlCompiledLabel = new QLabel(tr("   Compiled Ruleset File:"));
	inpModelLabel = new QLabel(tr("   Building Model File:"));
	loadSpacerLabel = new QLabel(tr("   "));
	loadModelLabel = new QLabel(tr("Load & Default Model"));

	analysisLabel = new QLabel(tr("Single Model Analysis"));
	wthrDirLabel = new QLabel(tr("   Weather File Directory:"));
	analOptsLabel = new QLabel(tr("   Ruleset Log/Error File:"));
	rlSpacerLabel = new QLabel(tr("   "));
//! [0]


	loadModelLabel->setFont( fontBold );
	loadButton->setFont( fontBold );
	analysisLabel->setFont( fontBold );
	analLoadedFile->setFont( fontBold );
	analFileViaAPI->setFont( fontBold );


	QFontMetrics fm( font );
	int iBrowseBtnWd = fm.width("...")+10;
	dmCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	inpModelBrowseButton->setFixedWidth( iBrowseBtnWd );
	wthrDirBrowseButton->setFixedWidth( iBrowseBtnWd );


	int iFileLabelWd = fm.width("   Data Model Enumerations File:")+10;
	dmCompiledLabel->setFixedWidth( iFileLabelWd );
	rlCompiledLabel->setFixedWidth( iFileLabelWd );
	inpModelLabel->setFixedWidth( iFileLabelWd );

	wthrDirLabel->setFixedWidth( iFileLabelWd );
	analOptsLabel->setFixedWidth( iFileLabelWd );


//	dmCompiledTextEdit->setPlainText( "C:/WSF/devLibs/CompMgr/RuleDev/Rulesets/CAR13 BEMBase-os.bin" );
//	rlCompiledTextEdit->setPlainText( "C:/WSF/devLibs/CompMgr/RuleDev/Rulesets/CA Res 2013-os.bin" );
//	inpModelTextEdit->setPlainText(   "C:/WSF/devLibs/CompMgr/src/BEM-open/bin/Projects-Res/1StoryExample19.ribd" );
//	wthrDirTextEdit->setPlainText(    "../Com/EPW/"
//	analOptsTextEdit->setPlainText(   "StoreBEMDetails,1,AnalysisThruStep,8,ModelRpt_ALL,1,ComplianceReportPDF,1,ExportHourlyResults_All,1,PromptUserUMLHWarning,1,CompReportWarningOption,5,ProxyServerType,Http," );

	dmCompiledTextEdit->setPlainText( "../Com/Rules/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin" );
	rlCompiledTextEdit->setPlainText( "../Com/Rules/CEC 2016 NonRes.bin" );
	inpModelTextEdit->setPlainText(   "../Com/Projects/SMTs2016/020012-OffSml-CECStd.cibd16" );
	wthrDirTextEdit->setPlainText(    "../Com/EPW/" );
	analOptsTextEdit->setPlainText( "StoreBEMDetails,1,AnalysisThruStep,8,ModelRpt_ALL,1,ComplianceReportPDF,1,ExportHourlyResults_All,1,PromptUserUMLHWarning,1,CompReportWarningOption,5,ProxyServerType,Http," );


			// void QGridLayout::addWidget(QWidget * widget, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = 0)
//! [1]
	QGridLayout *mainLayout = new QGridLayout;
	int iRow=-1;
	mainLayout->addWidget(dmCompiledLabel, ++iRow, 0);
	mainLayout->addWidget(dmCompiledTextEdit, iRow, 1, 1, 2);
	mainLayout->addWidget(dmCompiledBrowseButton, iRow, 3);

	mainLayout->addWidget(rlCompiledLabel, ++iRow, 0);
	mainLayout->addWidget(rlCompiledTextEdit, iRow, 1, 1, 2);
	mainLayout->addWidget(rlCompiledBrowseButton, iRow, 3);

	mainLayout->addWidget(inpModelLabel, ++iRow, 0);
	mainLayout->addWidget(inpModelTextEdit, iRow, 1, 1, 2);
	mainLayout->addWidget(inpModelBrowseButton, iRow, 3);

	mainLayout->addWidget(loadModelLabel, ++iRow, 0);
	mainLayout->addWidget(loadButton, iRow, 1, 1, 2);

	mainLayout->addWidget(loadSpacerLabel, ++iRow, 2);

	mainLayout->addWidget(wthrDirLabel, ++iRow, 0);
	mainLayout->addWidget(wthrDirTextEdit, iRow, 1, 1, 2);
	mainLayout->addWidget(wthrDirBrowseButton, iRow, 3);
	mainLayout->addWidget(analOptsLabel, ++iRow, 0);
	mainLayout->addWidget(analOptsTextEdit, iRow, 1, 1, 2);
	mainLayout->addWidget(analysisLabel, ++iRow, 0);
	mainLayout->addWidget(analLoadedFile, iRow, 1, 1, 1);
	mainLayout->addWidget(analFileViaAPI, iRow, 2, 1, 1);
//	mainLayout->addWidget(rlSpacerLabel, ++iRow, 2);
	setLayout(mainLayout);

	setWindowTitle(tr("CEC Commercial Test UI"));
	resize(900, 540);
}
//! [1]

//! [2]
void BEMTest::browseDMCompiled()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Compiled Data Model (binary) File"), QDir::currentPath(), tr("*.bin"));
	if (!file.isEmpty())
		dmCompiledTextEdit->setText(file);
}
//! [2]

//! [3]
void BEMTest::browseRLCompiled()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Compiled Ruleset (binary) File"), QDir::currentPath(), tr("*.bin"));
	if (!file.isEmpty())
		rlCompiledTextEdit->setText(file);
}
//! [3]

//! [4]
void BEMTest::browseInpModel()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Building Input Model File"), QDir::currentPath(), tr("*.*"));
	if (!file.isEmpty())
		inpModelTextEdit->setText(file);
}
//! [4]

//! [5]
void BEMTest::loadModel()
{
	QString fileDMCmpld = dmCompiledTextEdit->toPlainText();
	QString fileRlCmpld = rlCompiledTextEdit->toPlainText();
	QString fileInpModl = inpModelTextEdit->toPlainText();

	QString qAppDir = QCoreApplication::applicationDirPath();
	qAppDir = QDir::cleanPath(qAppDir);
	if (fileDMCmpld.indexOf("..") == 0)
		GetFullPath( fileDMCmpld, qAppDir );
	if (fileRlCmpld.indexOf("..") == 0)
		GetFullPath( fileRlCmpld, qAppDir );
	if (fileInpModl.indexOf("..") == 0)
		GetFullPath( fileInpModl, qAppDir );

	QString sMsg, sDetails;
	if (fileDMCmpld.isEmpty() || fileRlCmpld.isEmpty() || fileInpModl.isEmpty())
		sMsg = "All Load Model fields above must be provided before the model can be loaded.";
	else if (!QFile::exists(fileDMCmpld))
		sMsg = QString( "Data Model file not found:\n   %1" ).arg( fileDMCmpld );
	else if (!QFile::exists(fileRlCmpld))
		sMsg = QString( "Ruleset file not found:\n   %1" ).arg( fileRlCmpld );
	else if (!QFile::exists(fileInpModl))
		sMsg = QString( "Building model description file not found:\n   %1" ).arg( fileInpModl );
	else
	{	//CBEMPCmplApp *pApp = (CBEMPCmplApp*)AfxGetApp();
		//BOOL bReportBEMStats = pApp && pApp->IsUIActive();
		//BOOL bReportBEMStats = TRUE;
//		BOOL bCompOK = BEMPX_CompileDataModel(	fileDefs.toLocal8Bit().constData(), fileEnums.toLocal8Bit().constData(),
//															fileCmpld.toLocal8Bit().constData(), &sDetails );
//		sMsg = QString( "Data Model compilation:  %1" ).arg( (bCompOK ? "Succeeded" : "Failed") );

#define  MAX_BEMBASE_DATA_SET_ERRORS  100
		int i;
		// enable the UI reporting of all (up to MAX_BEMBASE_DATA_SET_ERRORS) BEMBase project file data setting errors
   	int iaFailedBEMBaseDBIDs[   MAX_BEMBASE_DATA_SET_ERRORS ];
	   int iaFailedBEMBaseObjIdxs[ MAX_BEMBASE_DATA_SET_ERRORS ];  // facilitate more informative error reporting
   	for (i=0; i<MAX_BEMBASE_DATA_SET_ERRORS; i++)
	   {
   	   iaFailedBEMBaseDBIDs[i] = 0;
      	iaFailedBEMBaseObjIdxs[i] = -1;
	   }
   	QStringList saFailedBEMBaseData;  // facilitate more informative error reporting
   	QStringList saWarningsForUser;  // issues not designated as read failures, but worthy of user attention

bool bKeepLogFileOpen = true;

		int iLM = CMX_LoadModel( fileDMCmpld.toLocal8Bit().constData(), fileRlCmpld.toLocal8Bit().constData(),
										 fileInpModl.toLocal8Bit().constData(), MAX_BEMBASE_DATA_SET_ERRORS, iaFailedBEMBaseDBIDs,
										 false /*bSupressAllMsgBoxes*/, iaFailedBEMBaseObjIdxs, &saFailedBEMBaseData,
										 false /*bLogDurations*/, NULL /*pszLogPathFile*/, bKeepLogFileOpen,
										 &saWarningsForUser, true /*bCalledFromUI*/ );

		if (iLM==0)
			sMsg = QString( "Building model read/parse successful\n" );
		else
			sMsg = QString( "Building model read/parse failed, returned %1\n" ).arg( QString::number(iLM) );

		if (TRUE)	// store copy of model before any defaulting occurs
		{	long lModDate;
			if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
				lModDate = -1;

			QString sDbgFileName = fileInpModl.left( fileInpModl.lastIndexOf('.') );
			sDbgFileName += " - post open-b4 dflt.ibd-Detail";
			BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/, FALSE /*bUseLogFileName*/,
												FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
												false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/,
												lModDate, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );
		}

// code to echo error messages to log/user
//		int iNumBEMBaseErrors = 0, iNumBEMBaseErrMsgs = 0;
//		CString sRdProjErr;
//	   for (i=0; i<MAX_BEMBASE_DATA_SET_ERRORS; i++)
//		{	if (iaFailedBEMBaseDBIDs[i] > 0 && iaFailedBEMBaseDBIDs[i] != lBEMBaseDBIDErrorToIgnore[0] && iaFailedBEMBaseDBIDs[i] != lBEMBaseDBIDErrorToIgnore[1])
//				iNumBEMBaseErrors++;
//			if (saFailedBEMBaseData.GetSize() > i && saFailedBEMBaseData[i].GetLength() > 3)
//				iNumBEMBaseErrMsgs++;
//		}
//		int iNumErrsInclInRdProjErr = 0;		CString sLoadModelErr;
//		if (iNumBEMBaseErrors > 0 || iLoadModelRetVal != 0)
//		{	switch (iLoadModelRetVal)
//			{	case  1 :	sLoadModelErr = "Input file not found";													break;
//				case  2 :	sLoadModelErr = "Building energy data model (BEMBin) file not found";			break;
//				case  3 :	sLoadModelErr = "Ruleset file not found";													break;
//				case  4 :	sLoadModelErr = "Initialization of building energy model database failed";		break;
//				case  5 :	sLoadModelErr = "Unable to load ruleset file";											break;
//				case  6 :	sLoadModelErr = "Unable to read/parse building energy model file";				break;
//				default :	sLoadModelErr = "(unrecognized error code)";												break;
//			}
//			if (iNumBEMBaseErrors > 0 && iLoadModelRetVal != 0)
//				sRdProjErr.Format( "%d error(s) encountered (return code %d: %s) reading project file:  %s", iNumBEMBaseErrors, iLoadModelRetVal, sLoadModelErr, sInputFile );
//			else if (iNumBEMBaseErrors > 0)
//				sRdProjErr.Format( "%d error(s) encountered reading project file:  %s", iNumBEMBaseErrors, sInputFile );
//			else
//				sRdProjErr.Format( "Error(s) encountered (return code %d: %s) reading project file:  %s", iLoadModelRetVal, sLoadModelErr, sInputFile );
//		   BEMPX_WriteLogFile( sRdProjErr );
//	
//		// SAC 6/30/16 - included echo of first 6 error messages in the string presented to the user in a messagebox
//			int iMaxErrsToIncl = 6;
//			int iErrMsgIdx=-1, iFindIdx;
//			while (iNumErrsInclInRdProjErr < iMaxErrsToIncl && ++iErrMsgIdx < saFailedBEMBaseData.GetSize())
//				if (saFailedBEMBaseData[iErrMsgIdx].GetLength() > 3)
//				{	iNumErrsInclInRdProjErr++;
//					if ((iFindIdx = saFailedBEMBaseData[iErrMsgIdx].Find( "ERROR - reading file: " )) >= 0)
//						sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx].Right( saFailedBEMBaseData[iErrMsgIdx].GetLength()-iFindIdx-22 ) );
//					else if ((iFindIdx = saFailedBEMBaseData[iErrMsgIdx].Find( "ERROR - " )) >= 0)
//						sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx].Right( saFailedBEMBaseData[iErrMsgIdx].GetLength()-iFindIdx-8 ) );
//					else
//						sLoadModelErr.Format( "\n\n(%d) %s", iNumErrsInclInRdProjErr, saFailedBEMBaseData[iErrMsgIdx] );
//					sRdProjErr += sLoadModelErr;
//				}
//	
//			CString sLogFN = BEMPX_GetLogFilename();
//			if (!sLogFN.IsEmpty())
//			{	sRdProjErr += "\n\nFor more information, refer to the project log file";
//				if (iNumErrsInclInRdProjErr > 0)
//				{	if (iNumErrsInclInRdProjErr < iNumBEMBaseErrMsgs)
//						sLoadModelErr.Format( " to review the above (and %d additional) error messages", iNumBEMBaseErrMsgs-iNumErrsInclInRdProjErr );
//					else
//						sLoadModelErr = " which echoes the above listed error(s)";
//					sRdProjErr += sLoadModelErr;
//				}
//				sRdProjErr += ":  ";
//				sRdProjErr += sLogFN;
//			}
//	      // AfxMessageBox( sRdProjErr );  - moved down to ensure that ALL messages (incl. new warnings) are written before user alerted to log message errors
//		}
//		CComplianceUIApp* pApp = (CComplianceUIApp*)AfxGetApp();
//		bool bUIActive = (pApp == NULL || pApp->IsUIActive());
//		if (saWarningsForUser.GetSize() > 0)	// SAC 7/8/14 - log file-read issues not designated as failures, but worthy of logging
//		{	bool bPrevErrsLogged = (!sRdProjErr.IsEmpty());
//			if (bPrevErrsLogged)
//				sRdProjErr += "\n";
//			int iMaxWarnMsgs = (bPrevErrsLogged ? 6-iNumErrsInclInRdProjErr : 8);
//			for (int iFRWIdx=0; iFRWIdx < saWarningsForUser.GetSize(); iFRWIdx++)
//			{	VERIFY( BEMPX_WriteLogFile( saWarningsForUser[iFRWIdx], NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
//				sLoadModelErr.Empty();
//				if (iFRWIdx == 0 && iMaxWarnMsgs <= 0)
//					sLoadModelErr.Format( "\n%d warning message(s) also written to project log file.", saWarningsForUser.GetSize() );
//				else if (iFRWIdx == iMaxWarnMsgs)
//					sLoadModelErr = "\n(additional warning message(s) written to project log file)";
//				else if (iFRWIdx < iMaxWarnMsgs)
//					sLoadModelErr.Format( "\n%s", saWarningsForUser[iFRWIdx] );
//				if (!sLoadModelErr.IsEmpty())
//					sRdProjErr += sLoadModelErr;
//			}
//			if (!bPrevErrsLogged)
//			{	if (bUIActive)
//			      AfxMessageBox( sRdProjErr );
//				sRdProjErr.Empty();
//		}	}
//		if (!sRdProjErr.IsEmpty() && bUIActive)		// SAC 7/8/14 - moved down here to ensure that ALL messages (incl. new warnings) are written before user alerted to log message errors
//			AfxMessageBox( sRdProjErr );
// END OF - code to echo error messages to log/user


// potentailly perform same checks as in CBECC-*
//		void CMainFrame::CheckBuildingModel( BOOL bReportModelOK /*=TRUE*/, BOOL bPerformRangeChecks /*=TRUE*/ ) 


	// toggle OFF log file timestamps
		BEMPX_EnableLogTimeStamps( false );

		if (CMX_RulesetOrganizationIsProcedural())		// ASSUME ruleset is RESIDENTIAL 
		{	// apply various database settings consistent w/ CBECC-Res
		   long lEnableResearchMode = 0;		// ReadProgInt( "options", "EnableResearchMode", 0 );
			long lDBID_Proj_EnableResearchMode = BEMPX_GetDatabaseID( "EnableResearchMode", BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_EnableResearchMode > 0 );
			long lDBID_Proj_AnalysisType       = BEMPX_GetDatabaseID( "AnalysisType"      , BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_AnalysisType       > 0 );
			if (lDBID_Proj_EnableResearchMode > 0 && lDBID_Proj_AnalysisType > 0)
			{	long lERM, lAT;
				if (!BEMPX_GetInteger( lDBID_Proj_EnableResearchMode, lERM, -1 ))
					lERM = -1;
				if (!BEMPX_GetInteger( lDBID_Proj_AnalysisType      , lAT , -1 ))
					lAT  = -1;
				if (lEnableResearchMode == 0 && lERM < 0.5 && lAT == 0)
					// This file was last SAVED IN RESEARCH MODE, but current INI file does not include research mode enabling setting
					sMsg += "\nResearch mode is selected in this project file but not available in the current software installation.";
				else if (lERM < -0.5)	// SAC 2/4/16 - only reset EnableResearchMode to INI setting if NOT specified in input file
			      BEMPX_SetBEMData( lDBID_Proj_EnableResearchMode, BEMP_Int, (void*) &lEnableResearchMode, BEMO_User, -1, BEMS_ProgDefault );
			}

			long lEnableRptIncFile    = 1  /*ReadProgInt( "options", "EnableRptIncFile"  , 0 )*/,	lDBID_Proj_EnableRptIncFile   = BEMPX_GetDatabaseID( "EnableRptIncFile"  , BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_EnableRptIncFile   > 0 );
			long lEnableVarFlowOAV    = 1  /*ReadProgInt( "options", "EnableVarFlowOAV"  , 1 )*/,	lDBID_Proj_EnableVarFlowOAV   = BEMPX_GetDatabaseID( "EnableVarFlowOAV"  , BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_EnableVarFlowOAV   > 0 );
			long lEnableFixedFlowOAV  = 1  /*ReadProgInt( "options", "EnableFixedFlowOAV", 1 )*/,	lDBID_Proj_EnableFixedFlowOAV = BEMPX_GetDatabaseID( "EnableFixedFlowOAV", BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_EnableFixedFlowOAV > 0 );
			long lBypassRuleLimits    = 2  /*ReadProgInt( "options", "BypassRuleLimits"  , 0 )*/,	lDBID_Proj_BypassRuleLimits   = BEMPX_GetDatabaseID( "BypassRuleLimits"  , BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_BypassRuleLimits   > 0 );
			if (lEnableRptIncFile > 0 &&		lDBID_Proj_EnableRptIncFile   > 0)
		      				BEMPX_SetBEMData( lDBID_Proj_EnableRptIncFile  , BEMP_Int, (void*) &lEnableRptIncFile  , BEMO_User, -1, BEMS_ProgDefault );
			if (lEnableVarFlowOAV > 0 &&		lDBID_Proj_EnableVarFlowOAV   > 0)
		      				BEMPX_SetBEMData( lDBID_Proj_EnableVarFlowOAV  , BEMP_Int, (void*) &lEnableVarFlowOAV  , BEMO_User, -1, BEMS_ProgDefault );
			if (lEnableFixedFlowOAV > 0 &&	lDBID_Proj_EnableFixedFlowOAV > 0)
		      				BEMPX_SetBEMData( lDBID_Proj_EnableFixedFlowOAV, BEMP_Int, (void*) &lEnableFixedFlowOAV, BEMO_User, -1, BEMS_ProgDefault );
			if (lBypassRuleLimits > 0 &&	   lDBID_Proj_BypassRuleLimits > 0)
		      				BEMPX_SetBEMData( lDBID_Proj_BypassRuleLimits  , BEMP_Int, (void*) &lBypassRuleLimits  , BEMO_User, -1, BEMS_ProgDefault );

			long lSimSpeedOption = -1  /*ReadProgInt( "options", "SimSpeedOption", -1 )*/,		lDBID_Proj_SimSpeedOption = BEMPX_GetDatabaseID( "SimSpeedOption", BEMPX_GetDBComponentID( "Proj" ) );			assert( lDBID_Proj_SimSpeedOption > 0 );
			if (lSimSpeedOption >= 0 &&	lDBID_Proj_SimSpeedOption > 0)
		   	BEMPX_SetBEMData( lDBID_Proj_SimSpeedOption, BEMP_Int, (void*) &lSimSpeedOption, BEMO_User, -1, BEMS_ProgDefault );
		}	// END OF - apply various database settings consistent w/ CBECC-Res


	   CMX_EvaluateRuleset( "ProposedInput", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/,
	   							TRUE /*VerboseInputLogging*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );
      BEMPX_WriteLogFile( "   first round of defaulting complete", NULL, FALSE, TRUE /*bSupressAllMessageBoxes*/ );

	   CMX_EvaluateRuleset( "ProposedInput", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/,
	   							TRUE /*VerboseInputLogging*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );

	   CMX_EvaluateRuleset( "ProposedInput", FALSE /*bReportToLog*/, FALSE /*bTagDataAsUserDefined*/,
	   							TRUE /*VerboseInputLogging*/, NULL, NULL, NULL, NULL /*pCompRuleDebugInfo*/ );


		// store detailed models
		if (TRUE)  // ReadProgInt( "options", "StoreBEMDetails", 0) > 0 && sInputFile.ReverseFind('.') > 0)
		{  // SAC 6/26/13 - added code to PREVENT ModDate from getting incremented each time project file is written in non-input mode
			long lModDate;
			if (!BEMPX_GetInteger( BEMPX_GetDatabaseID( "Proj:ModDate" ), lModDate ))
				lModDate = -1;

			QString sDbgFileName = fileInpModl.left( fileInpModl.lastIndexOf('.') );
			sDbgFileName += " - post open.ibd-Detail";
			BEMPX_WriteProjectFile( sDbgFileName.toLocal8Bit().constData(), BEMFM_DETAIL /*FALSE*/, FALSE /*bUseLogFileName*/,
												FALSE /*bWriteAllProperties*/, FALSE /*bSupressAllMsgBoxes*/, 0 /*iFileType*/,
												false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/,
												lModDate, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );

			QString sXMLFileName = fileInpModl.left( fileInpModl.lastIndexOf('.') );
			sXMLFileName += " - post open.xml";
			BEMPX_WriteProjectFile( sXMLFileName.toLocal8Bit().constData(), BEMFM_INPUT /*TRUE*/, FALSE /*bUseLogFileName*/,
												TRUE /*bWriteAllProperties*/, FALSE /*bSupressAllMessageBoxes*/, BEMFT_XML /*iFileType*/,
												false /*bAppend*/, NULL /*pszModelName*/, true /*bWriteTerminator*/, -1 /*iBEMProcIdx*/,
												lModDate, false /*bOnlyValidInputs*/, false /*bAllowCreateDateReset*/ );
		}
	}
	if (!sMsg.isEmpty())
	{
			QMessageBox msgBox;
			msgBox.setWindowTitle( "Building Model Load" );
	//		msgBox.setIcon( QMessageBox::Warning ); 
	//		msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
			msgBox.setText( sMsg );
			msgBox.setDetailedText( sDetails );
	//		msgBox.setStandardButtons( QMessageBox::Ok );
	//		msgBox.addButton( QMessageBox::Abort );
	//		msgBox.setDefaultButton( QMessageBox::Ok );
	//		bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);

		// adding spacer item enables some manual MessageBox re-sizing (larger)
			QSpacerItem* horizontalSpacer = new QSpacerItem( 400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding );
			QGridLayout* layout = (QGridLayout*) msgBox.layout();
			layout->addItem( horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount() );
		// adjusting the 'details' text edit control further enables size customization
			QTextEdit *textEdit = msgBox.findChild<QTextEdit *>();
			if (textEdit)
			{	textEdit->setMinimumHeight( 320 );
				textEdit->setMaximumHeight( QWIDGETSIZE_MAX );
				textEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
			}

			msgBox.exec();
	}
}
//! [5]

//! [6]
void BEMTest::browseWthrDir()
{
	QString dir = QFileDialog::getExistingDirectory( this, 
					tr("Select Simulation Weather File Directory"), QDir::currentPath(), 
					QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
	if (!dir.isEmpty())
		wthrDirTextEdit->setText(dir);
}
//! [6]

#define  CSV_RESULTSLENGTH  2560
static char pszCSVResultSummary[ CSV_RESULTSLENGTH ];

//! [7]
void BEMTest::analyzeLoadedFile()
{
	QString fileDMCmpld = dmCompiledTextEdit->toPlainText();
	QString fileRlCmpld = rlCompiledTextEdit->toPlainText();
	QString fileInpModl = inpModelTextEdit->toPlainText();
	QString dirWthr  = wthrDirTextEdit->toPlainText();
	QString analOpts = analOptsTextEdit->toPlainText();

	QString qAppDir = QCoreApplication::applicationDirPath();
	qAppDir = QDir::cleanPath(qAppDir);
	if (fileDMCmpld.indexOf("..") == 0)
		GetFullPath( fileDMCmpld, qAppDir );
	if (fileRlCmpld.indexOf("..") == 0)
		GetFullPath( fileRlCmpld, qAppDir );
	if (fileInpModl.indexOf("..") == 0)
		GetFullPath( fileInpModl, qAppDir );
	if (dirWthr.indexOf("..") == 0)
		GetFullPath( dirWthr, qAppDir );
	int iLastInpModelSlashIdx = std::max( fileInpModl.lastIndexOf('\\'), fileInpModl.lastIndexOf('/') );
	int iLastInpModelDotIdx   = fileInpModl.lastIndexOf('.');
	char pszAnalysisErr[2056] = "\0";
	pszCSVResultSummary[0] = '\0';

	QString sMsg, sDetails;
	if (fileDMCmpld.isEmpty() || fileRlCmpld.isEmpty() || fileInpModl.isEmpty())
		sMsg = "All Load Model fields above must be provided before the model can be loaded.";
	else if (!QFile::exists(fileDMCmpld))
		sMsg = QString( "Data Model file not found:\n   %1" ).arg( fileDMCmpld );
	else if (!QFile::exists(fileRlCmpld))
		sMsg = QString( "Ruleset file not found:\n   %1" ).arg( fileRlCmpld );
	else if (!QFile::exists(fileInpModl))
		sMsg = QString( "Building model description file not found:\n   %1" ).arg( fileInpModl );
	else if (iLastInpModelDotIdx < 3 || iLastInpModelSlashIdx < 3 || iLastInpModelDotIdx < iLastInpModelSlashIdx)
		sMsg = QString( "Building model description path or file extension missing:\n   %1" ).arg( fileInpModl );
	else if (!QDir(dirWthr).exists())
		sMsg = QString( "Simulation weather directory not found:\n   %1" ).arg( dirWthr );
	else
	{
		QString dirProcess = fileInpModl.left( iLastInpModelDotIdx );
		dirProcess += " - run\\";
		if (dirWthr[ dirWthr.length()-1 ] != '/' && dirWthr[ dirWthr.length()-1 ] != '\\')
			dirWthr += '\\';

//#include <QWindow>
//#include <qpa/qplatformnativeinterface.h>
//widget->show();
		HWND hwnd  = NULL;
//  //		if (const QWindow *w = widget->windowHandle())
//  		if (const QWindow *w = windowHandle())
//  			hwnd = (HWND)QGuiApplication::platformNativeInterface()->nativeResourceForWindow(QByteArrayLiteral("handle"), w);

		int iSimResult = CMX_PerformAnalysis_CECNonRes(	NULL /*pszBEMBasePathFile*/, NULL /*pszRulesetPath*/, dirWthr.toLatin1().constData(),
																		NULL /*pszCompMgrDLLPath -> WAS: sT24DHWPath*/, NULL /*pszDHWWeatherPath*/,
																		dirProcess.toLatin1().constData() /*pszProcessPath*/, fileInpModl.toLatin1().constData() /*pszModelPathFile*/,
																		NULL /*pszLogPathFile*/, "CEC Com Test v1.0", false /*bLoadModelFile*/, 
																		analOpts.toLatin1().constData(), pszAnalysisErr, 2056, true /*bDisplayProgress*/,
																		hwnd /*HWND hWnd*/, pszCSVResultSummary, CSV_RESULTSLENGTH );

// analysis inputs w/ model already loaded -
//     PerfAnal_NRes - starting, w/ arguments:
//          BEMBasePathFile    = (null)          RulesetPathFile    = (null)
//          SimWeatherPath     = C:\Apps\CBECC-Com16 2-1-4377\Data\EPW\
//          CompMgrDLLPath     = (null)          DHWWeatherPath     = (null)
//          ProcessingPath     = C:\Apps\CBECC-Com16 2-1-4377\Projects\StandardModelTests2016\020012-OffSml-CECStd-sv - run\
//          ModelPathFile      = C:\Apps\CBECC-Com16 2-1-4377\Projects\StandardModelTests2016\020012-OffSml-CECStd-sv.cibd16
//          LogPathFile        = (null)
//          UIVersionString    = CBECC-Com 2016.2.1 (868)
//          LoadModelFile      = false
//          OptionsCSV         = StoreBEMDetails,1,AnalysisThruStep,8,ModelRpt_ALL,1,ComplianceReportPDF,1,ExportHourlyResults_All,1,PromptUserUMLHWarning,1,CompReportWarningOption,5,ProxyServerType,"Http",
//          ErrorMsg           = (assumed to be initialized)          ErrorMsgLen        = 2056
//          DisplayProgress    = true
//          ResultsSummary     = (empty)          ResultsSummaryLen  = 2560
//          pProgCallbackFunc  = (null)

//  int  BEMCMPMGR_API __cdecl CMX_PerformAnalysis_CECNonRes(	const char* pszBEMBasePathFile, const char* pszRulesetPathFile,
//  												const char* pszSimWeatherPath, const char* pszCompMgrDLLPath, const char* pszDHWWeatherPath, const char* pszProcessingPath,
//  												const char* pszModelPathFile, const char* pszLogPathFile, const char* pszUIVersionString, bool bLoadModelFile=true,
//  												const char* pszOptionsCSV=NULL, char* pszErrorMsg=NULL, int iErrorMsgLen=0, bool bDisplayProgress=false, HWND hWnd=NULL,
//  												char* pszResultsSummary=NULL, int iResultsSummaryLen=0 );		// SAC 5/16/14

		// Populate string w/ summary results of analysis  - SAC 5/19/14 - added similar to -Res
		if (iSimResult == 0)		//  && bPerformSimulations
		{
			sMsg = "Analysis Success";
			if (strlen( pszCSVResultSummary ) > 0)
				sDetails = pszCSVResultSummary;
		}
		else
		{
			sMsg = QString( "Analysis Failed - return value: %1" ).arg( QString::number(iSimResult) );
			if (strlen( pszAnalysisErr ) > 0)
				sDetails = pszAnalysisErr;
		}
	}


			QMessageBox msgBox;
			msgBox.setWindowTitle( "Single Run Analysis" );
	//		msgBox.setIcon( QMessageBox::Warning ); 
	//		msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
			msgBox.setText( sMsg );
			msgBox.setDetailedText( sDetails );
	//		msgBox.setStandardButtons( QMessageBox::Ok );
	//		msgBox.addButton( QMessageBox::Abort );
	//		msgBox.setDefaultButton( QMessageBox::Ok );
	//		bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);

		// adding spacer item enables some manual MessageBox re-sizing (larger)
			QSpacerItem* horizontalSpacer = new QSpacerItem( 400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding );
			QGridLayout* layout = (QGridLayout*) msgBox.layout();
			layout->addItem( horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount() );
		// adjusting the 'details' text edit control further enables size customization
			QTextEdit *textEdit = msgBox.findChild<QTextEdit *>();
			if (textEdit)
			{	textEdit->setMinimumHeight( 320 );
				textEdit->setMaximumHeight( QWIDGETSIZE_MAX );
				textEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
			}

			msgBox.exec();


//  		int iNumEUseSummaryObjs = BEMPX_GetNumObjects( eiBDBCID_EUseSummary );
//  		if (iSimResult < 1)
//  		{	if (eiBDBCID_EUseSummary > 0 && iNumEUseSummaryObjs > 0)
//  			{	bSimResultsDisplayed = TRUE;
//  				//int iTabCtrlWd, iTabCtrlHt;
//  				//VERIFY( GetDialogTabDimensions( siQuickCr8Class, iTabCtrlWd, iTabCtrlHt ) );
//  				if (BEMPX_GetNumObjects( eiBDBCID_EUseSummary ) > 1)	// SAC 9/13/13 - added to ensure first (worst case) EUseSummary obejct is ALWAYS the active obejct as dialog presented
//  					BEMPX_SetActiveObjectIndex( eiBDBCID_EUseSummary, 0 );

}
//! [7]

//! [8]
void BEMTest::analyzeFileViaAPI()
{
	QString fileDMCmpld = dmCompiledTextEdit->toPlainText();
	QString fileRlCmpld = rlCompiledTextEdit->toPlainText();
	QString fileInpModl = inpModelTextEdit->toPlainText();
	QString dirWthr  = wthrDirTextEdit->toPlainText();
	QString analOpts = analOptsTextEdit->toPlainText();

	QString qAppDir = QCoreApplication::applicationDirPath();
	qAppDir = QDir::cleanPath(qAppDir);
	if (fileDMCmpld.indexOf("..") == 0)
		GetFullPath( fileDMCmpld, qAppDir );
	if (fileRlCmpld.indexOf("..") == 0)
		GetFullPath( fileRlCmpld, qAppDir );
	if (fileInpModl.indexOf("..") == 0)
		GetFullPath( fileInpModl, qAppDir );
	if (dirWthr.indexOf("..") == 0)
		GetFullPath( dirWthr, qAppDir );
	int iLastInpModelSlashIdx = std::max( fileInpModl.lastIndexOf('\\'), fileInpModl.lastIndexOf('/') );
	int iLastInpModelDotIdx   = fileInpModl.lastIndexOf('.');
	char pszAnalysisErr[2056] = "\0";
	pszCSVResultSummary[0] = '\0';

	QString sMsg, sDetails;
	if (fileDMCmpld.isEmpty() || fileRlCmpld.isEmpty() || fileInpModl.isEmpty())
		sMsg = "All Load Model fields above must be provided before the model can be loaded.";
	else if (!QFile::exists(fileDMCmpld))
		sMsg = QString( "Data Model file not found:\n   %1" ).arg( fileDMCmpld );
	else if (!QFile::exists(fileRlCmpld))
		sMsg = QString( "Ruleset file not found:\n   %1" ).arg( fileRlCmpld );
	else if (!QFile::exists(fileInpModl))
		sMsg = QString( "Building model description file not found:\n   %1" ).arg( fileInpModl );
	else if (iLastInpModelDotIdx < 3 || iLastInpModelSlashIdx < 3 || iLastInpModelDotIdx < iLastInpModelSlashIdx)
		sMsg = QString( "Building model description path or file extension missing:\n   %1" ).arg( fileInpModl );
	else if (!QDir(dirWthr).exists())
		sMsg = QString( "Simulation weather directory not found:\n   %1" ).arg( dirWthr );
	else
	{
		QString dirProcess = fileInpModl.left( iLastInpModelDotIdx );
		dirProcess += " - runAPI\\";
		if (dirWthr[ dirWthr.length()-1 ] != '/' && dirWthr[ dirWthr.length()-1 ] != '\\')
			dirWthr += '\\';




// analysis inputs w/ model already loaded -
//     PerfAnal_NRes - starting, w/ arguments:
//          BEMBasePathFile    = C:\Apps\CBECC-Com16 2-1-4377\Data\Rulesets\CEC 2016 NonRes\CEC 2016 NonRes BEMBase.bin
//          RulesetPathFile    = C:\Apps\CBECC-Com16 2-1-4377\Data\Rulesets\CEC 2016 NonRes.bin
//          SimWeatherPath     = C:\Apps\CBECC-Com16 2-1-4377\Data\EPW\
//          CompMgrDLLPath     = C:\Apps\CBECC-Com16 2-1-4377\
//          DHWWeatherPath     = (null)
//          ProcessingPath     = C:\Apps\CBECC-Com16 2-1-4377\Projects\StandardModelTests2016\020012-OffSml-CECStd-API - runAPI\
//          ModelPathFile      = C:\Apps\CBECC-Com16 2-1-4377\Projects\StandardModelTests2016\020012-OffSml-CECStd-API.cibd16
//          LogPathFile        = (null)
//          UIVersionString    = CBECC-Com 2016.2.1 (868)
//          LoadModelFile      = true
//          OptionsCSV         = StoreBEMDetails,1,AnalysisThruStep,8,ModelRpt_ALL,1,ComplianceReportPDF,1,ExportHourlyResults_All,1,PromptUserUMLHWarning,1,CompReportWarningOption,5,ProxyServerType,"Http",
//          ErrorMsg           = (assumed to be initialized)
//          ErrorMsgLen        = 2056
//          DisplayProgress    = true
//          ResultsSummary     = (empty)
//          ResultsSummaryLen  = 2560
//          pProgCallbackFunc  = (assumed to be initialized)




//		sMsg = QString( "BEM Ruleset compilation:  %1" ).arg( (bCompOK ? "Succeeded" : "Failed") );
	}

	if (!sMsg.isEmpty())
	{
			QMessageBox msgBox;
			msgBox.setWindowTitle( "BEM Ruleset Compilation" );
	//		msgBox.setIcon( QMessageBox::Warning ); 
	//		msgBox.setTextFormat(Qt::RichText); //this is what makes the links clickable
			msgBox.setText( sMsg );
			msgBox.setDetailedText( sDetails );
	//		msgBox.setStandardButtons( QMessageBox::Ok );
	//		msgBox.addButton( QMessageBox::Abort );
	//		msgBox.setDefaultButton( QMessageBox::Ok );
	//		bRptIssueAbort = (msgBox.exec() == QMessageBox::Abort);

		// adding spacer item enables some manual MessageBox re-sizing (larger)
			QSpacerItem* horizontalSpacer = new QSpacerItem( 400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding );
			QGridLayout* layout = (QGridLayout*) msgBox.layout();
			layout->addItem( horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount() );
		// adjusting the 'details' text edit control further enables size customization
			QTextEdit *textEdit = msgBox.findChild<QTextEdit *>();
			if (textEdit)
			{	textEdit->setMinimumHeight( 320 );
				textEdit->setMaximumHeight( QWIDGETSIZE_MAX );
				textEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
			}

			msgBox.exec();
	}
}
//! [8]

//! [9]
QTextEdit *BEMTest::createTextEdit(const QString &text)
{
	QTextEdit *textEdit = new QTextEdit(text);
	QFontMetrics fm( font );
//	textEdit->setFixedHeight( fm.lineSpacing()+10 );
	textEdit->setFixedHeight( fm.height()+10 );
	return textEdit;
}
//! [9]

//! [10]
QPushButton *BEMTest::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}
//! [10]

