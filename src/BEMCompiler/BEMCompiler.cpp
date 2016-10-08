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

#include <QtWidgets/qapplication.h>
#include <QtWidgets/QtWidgets>

#include "BEMCompiler.h"
#include "../BEMProc/BEMProc.h"
#include "../BEMProc/BEMProcCompile.h"
#include "memLkRpt.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
#ifdef CBECC_RES16
	QApplication::setApplicationName("BEMCompiler - Residential 2016");
	QApplication::setApplicationVersion("1.0");
#else		// CBECC-Com
	QApplication::setApplicationName("BEMCompiler - Commercial 2016");
	QApplication::setApplicationVersion("1.0");
#endif

	QCommandLineParser parser;
	parser.setApplicationDescription("Test helper");
	parser.addHelpOption();
	parser.addVersionOption();

	// add command line options
	QCommandLineOption bemBaseTxtOption( "bemBaseTxt",
				QCoreApplication::translate("main", "Set data model definitions file <bembasetxt>."),
				QCoreApplication::translate("main", "bembasetxt"));
		parser.addOption(bemBaseTxtOption);
	QCommandLineOption bemEnumsTxtOption( "bemEnumsTxt",
				QCoreApplication::translate("main", "Set data model enumerations file <bemenumstxt>."),
				QCoreApplication::translate("main", "bemenumstxt"));
		parser.addOption(bemEnumsTxtOption);
	QCommandLineOption bemBaseBinOption( "bemBaseBin",
				QCoreApplication::translate("main", "Set compiled data model file <bembasebin>."),
				QCoreApplication::translate("main", "bembasebin"));
		parser.addOption(bemBaseBinOption);

	QCommandLineOption rulesTxtOption( "rulesTxt",
				QCoreApplication::translate("main", "Set primary ruleset source file <rulestxt>."),
				QCoreApplication::translate("main", "rulestxt"));
		parser.addOption(rulesTxtOption);
	QCommandLineOption rulesBinOption( "rulesBin",
				QCoreApplication::translate("main", "Set compiled ruleset file <rulesbin>."),
				QCoreApplication::translate("main", "rulesbin"));
		parser.addOption(rulesBinOption);
	QCommandLineOption rulesLogOption( "rulesLog",
				QCoreApplication::translate("main", "Set ruleset log/error file <ruleslog>."),
				QCoreApplication::translate("main", "ruleslog"));
		parser.addOption(rulesLogOption);

	QCommandLineOption compileDMOption("compileDM", QCoreApplication::translate("main", "Compile data model source"));
	parser.addOption(compileDMOption);
	QCommandLineOption compileRulesOption("compileRules", QCoreApplication::translate("main", "Compile BEM ruleset source"));
	parser.addOption(compileRulesOption);
	// Process the actual command line arguments given by the user
	parser.process(app);

//BEMCompiler16c.exe --bemBaseTxt="../Com/Rules/src/CEC 2013 NonRes BEMBase.txt" --bemEnumsTxt="../Com/Rules/src/CEC 2013 NonRes BEMEnums.txt" --bemBaseBin="../Com/Rules/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin"
//   --rulesTxt="../Com/Rules/src/Rules/CEC 2016 NonRes.txt" --rulesBin="../Com/Rules/CEC 2016 NonRes.bin" --rulesLog="../Com/Rules/src/Rules/Rules-2016 Log.out" --compileDM --compileRules

//BEMCompiler16c.exe --bemBaseTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMBase.txt" --bemEnumsTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMEnums.txt" --bemBaseBin="Data-os/Rulesets/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin"
//   --rulesTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/CEC 2016 NonRes.txt" --rulesBin="Data-os/Rulesets/CEC 2016 NonRes.bin" --rulesLog="../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/Rules-2016 Log.out" --compileDM --compileRules

// create main UI dialog
	BEMCompiler bemCmplr;

// before applying command line path/file settings, default all
#ifdef CBECC_RES16
//// to compile rules relative to Debug/Release exe -> bin\Res\rule source locations
//	bemCmplr.SetBEMBaseText(  "../Res/Rules/src/CAR13 BEMBase.txt" );
//	bemCmplr.SetBEMEnumsText( "../Res/Rules/src/CAR16 BEMEnums.txt" );
//	bemCmplr.SetBEMBaseBin(   "../Res/Rules/CA Res 2016/CAR16 BEMBase.bin" );
//	bemCmplr.SetRuleText(     "../Res/Rules/src/Rules/Rules-2016.txt" );
//	bemCmplr.SetRuleBin(      "../Res/Rules/CA Res 2016.bin" );
//	bemCmplr.SetRuleLog(      "../Res/Rules/src/Rules/Rules Log.out" );

// to compile rules relative to SVN exe->rule source locations
	bemCmplr.SetBEMBaseText(  "../RulesetDev/Rulesets/CA Res/CAR13 BEMBase.txt" );
	bemCmplr.SetBEMEnumsText( "../RulesetDev/Rulesets/CA Res/CAR16 BEMEnums.txt" );
	bemCmplr.SetBEMBaseBin(   "Data/Rulesets/CA Res 2016/CAR16 BEMBase.bin" );
	bemCmplr.SetRuleText(     "../RulesetDev/Rulesets/CA Res/Rules/Rules-2016.txt" );
	bemCmplr.SetRuleBin(      "Data/Rulesets/CA Res 2016.bin" );
	bemCmplr.SetRuleLog(      "../RulesetDev/Rulesets/CA Res/Rules/Rules-2016-os Log.out" );
#else		// CBECC-Com
//// to compile rules relative to Debug/Release exe -> bin\Com\rule source locations
//	bemCmplr.SetBEMBaseText(  "../Com/Rules/src/CEC 2013 NonRes BEMBase.txt" );
//	bemCmplr.SetBEMEnumsText( "../Com/Rules/src/CEC 2013 NonRes BEMEnums.txt" );
//	bemCmplr.SetBEMBaseBin(   "../Com/Rules/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin" );
//	bemCmplr.SetRuleText(     "../Com/Rules/src/Rules/CEC 2016 NonRes.txt" );
//	bemCmplr.SetRuleBin(      "../Com/Rules/CEC 2016 NonRes.bin" );
//	bemCmplr.SetRuleLog(      "../Com/Rules/src/Rules/Rules-2016 Log.out" );

// to compile rules relative to SVN exe->rule source locations
	bemCmplr.SetBEMBaseText(  "../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMBase.txt" );
	bemCmplr.SetBEMEnumsText( "../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMEnums.txt" );
	bemCmplr.SetBEMBaseBin(   "Data-os/Rulesets/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin" );
	bemCmplr.SetRuleText(     "../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/CEC 2016 NonRes.txt" );
	bemCmplr.SetRuleBin(      "Data-os/Rulesets/CEC 2016 NonRes.bin" );
	bemCmplr.SetRuleLog(      "../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/Rules-2016 Log.out" );
#endif

// now apply command line path/file arguments
	QString qsBT = parser.value(bemBaseTxtOption);
	if (!qsBT.isEmpty())
		bemCmplr.SetBEMBaseText( qsBT );
	QString qsBET = parser.value(bemEnumsTxtOption);
	if (!qsBET.isEmpty())
		bemCmplr.SetBEMEnumsText( qsBET );
	QString qsBB = parser.value(bemBaseBinOption);
	if (!qsBB.isEmpty())
		bemCmplr.SetBEMBaseBin( qsBB );

	QString qsRT = parser.value(rulesTxtOption);
	if (!qsRT.isEmpty())
		bemCmplr.SetRuleText( qsRT );
	QString qsRB = parser.value(rulesBinOption);
	if (!qsRB.isEmpty())
		bemCmplr.SetRuleBin( qsRB );
	QString qsRL = parser.value(rulesLogOption);
	if (!qsRL.isEmpty())
		bemCmplr.SetRuleLog( qsRL );

	bool compileDM = parser.isSet(compileDMOption);
	bool compileRules = parser.isSet(compileRulesOption);

	bemCmplr.show();

//	if (compileDM || compileRules)
//		app.exit( bemCmplr.compileAll( compileDM, compileRules, true /*bCommandLine*/ ) );
//	return app.exec();

	int iRetVal = 0;
	if (compileDM || compileRules)
		iRetVal = bemCmplr.compileAll( compileDM, compileRules, true /*bCommandLine*/ );
	else
		iRetVal = app.exec();

	return iRetVal;
//	return app.exec();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GetFullPath( QString& sFilePath, QString sDir )
{
	if ( sFilePath.indexOf("//")==0 || sFilePath.indexOf("\\\\")==0 ||
		  sFilePath.indexOf(':')==1 )
		return;	// sFilePath is complete on its own

	int iLastSlash = std::max( sDir.lastIndexOf('/'), sDir.lastIndexOf('\\') );
	if (iLastSlash < 1)
	{	assert( false );
		return;
	}
	else if (iLastSlash == (int) sDir.length()-1)
		sDir = sDir.left( sDir.length()-1 );

//	while (sFilePath.indexOf("..") == 0)
//	{	sFilePath = sFilePath.right( sFilePath.length()-3 );
//		iLastSlash = std::max( sDir.lastIndexOf('/'), sDir.lastIndexOf('\\') );
//		if (iLastSlash < 1)
//		{	assert( false );
//			return;
//		}
//		else
//			sDir = sDir.left( iLastSlash );
//	}
	sFilePath = sDir + QChar('/') + sFilePath;
	sFilePath = QDir::cleanPath(sFilePath);
}

////////////////////////////////////////////////////////////////////////////////

//! [0]
BEMCompiler::BEMCompiler(QWidget *parent)
	: QWidget(parent)
{
	font.setFamily( "MS Sans Serif" );
	font.setPointSize( 10 );
	setFont( font );
	fontBold.setFamily( "MS Sans Serif" );
	fontBold.setPointSize( 10 );
	fontBold.setBold( true );

	dmDefsBrowseButton = createButton(tr("..."), SLOT(browseDMDefs()));
	dmEnumsBrowseButton = createButton(tr("..."), SLOT(browseDMEnums()));
	dmCompiledBrowseButton = createButton(tr("..."), SLOT(browseDMCompiled()));
	dmCompileButton = createButton(tr("  Compile &Data Model  "), SLOT(compileDataModel()));
	rlPrimBrowseButton = createButton(tr("..."), SLOT(browseRLPrim()));
	rlCompiledBrowseButton = createButton(tr("..."), SLOT(browseRLCompiled()));
	rlLogBrowseButton = createButton(tr("..."), SLOT(browseRLLog()));
	rlCompileButton = createButton(tr("  Compile &Ruleset  "), SLOT(compileRuleset()));

	dmDefsTextEdit = createTextEdit();
	dmEnumsTextEdit = createTextEdit();
	dmCompiledTextEdit = createTextEdit();
	rlPrimTextEdit = createTextEdit();
	rlCompiledTextEdit = createTextEdit();
	rlLogTextEdit = createTextEdit();

	dmCompilerLabel = new QLabel(tr("Data Model Compiler"));
	dmDefsLabel = new QLabel(tr("   Data Model Definitions File:"));
	dmEnumsLabel = new QLabel(tr("   Data Model Enumerations File:"));
	dmCompiledLabel = new QLabel(tr("   Compiled Data Model File:"));
	dmSpacerLabel = new QLabel(tr("   "));
	rlCompilerLabel = new QLabel(tr("Ruleset Compiler"));
	rlPrimLabel = new QLabel(tr("   Primary Ruleset File:"));
	rlCompiledLabel = new QLabel(tr("   Compiled Ruleset File:"));
	rlLogLabel = new QLabel(tr("   Ruleset Log/Error File:"));
	rlSpacerLabel = new QLabel(tr("   "));
//! [0]

	dmCompilerLabel->setFont( fontBold );
	dmCompileButton->setFont( fontBold );
	rlCompilerLabel->setFont( fontBold );
	rlCompileButton->setFont( fontBold );

	QFontMetrics fm( font );
	int iBrowseBtnWd = fm.width("...")+10;
	dmDefsBrowseButton->setFixedWidth( iBrowseBtnWd );
	dmEnumsBrowseButton->setFixedWidth( iBrowseBtnWd );
	dmCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlPrimBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlLogBrowseButton->setFixedWidth( iBrowseBtnWd );

	int iFileLabelWd = fm.width("   Data Model Enumerations File:")+10;
	dmDefsLabel->setFixedWidth( iFileLabelWd );
	dmEnumsLabel->setFixedWidth( iFileLabelWd );
	dmCompiledLabel->setFixedWidth( iFileLabelWd );
	rlPrimLabel->setFixedWidth( iFileLabelWd );
	rlCompiledLabel->setFixedWidth( iFileLabelWd );
	rlLogLabel->setFixedWidth( iFileLabelWd );

//// populate strings from default and/or command line arguments to text fields
//	dmDefsTextEdit->setPlainText(     sBEMBaseText );
//	dmEnumsTextEdit->setPlainText(    sBEMEnumsText );
//	dmCompiledTextEdit->setPlainText( sBEMBaseBin );
//	rlPrimTextEdit->setPlainText(     sRuleText );
//	rlCompiledTextEdit->setPlainText( sRuleBin );
//	rlLogTextEdit->setPlainText(      sRuleLog );

//! [1]
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(dmCompilerLabel, 0, 0);
	mainLayout->addWidget(dmDefsLabel, 1, 0);
	mainLayout->addWidget(dmDefsTextEdit, 1, 1, 1, 2);
	mainLayout->addWidget(dmDefsBrowseButton, 1, 3);
	mainLayout->addWidget(dmEnumsLabel, 2, 0);
	mainLayout->addWidget(dmEnumsTextEdit, 2, 1, 1, 2);
	mainLayout->addWidget(dmEnumsBrowseButton, 2, 3);
	mainLayout->addWidget(dmCompiledLabel, 3, 0);
	mainLayout->addWidget(dmCompiledTextEdit, 3, 1, 1, 2);
	mainLayout->addWidget(dmCompiledBrowseButton, 3, 3);
	mainLayout->addWidget(dmCompileButton, 4, 2, 1, 2);
	mainLayout->addWidget(dmSpacerLabel, 5, 2);
	mainLayout->addWidget(rlCompilerLabel, 6, 0);
	mainLayout->addWidget(rlPrimLabel, 7, 0);
	mainLayout->addWidget(rlPrimTextEdit, 7, 1, 1, 2);
	mainLayout->addWidget(rlPrimBrowseButton, 7, 3);
	mainLayout->addWidget(rlCompiledLabel, 8, 0);
	mainLayout->addWidget(rlCompiledTextEdit, 8, 1, 1, 2);
	mainLayout->addWidget(rlCompiledBrowseButton, 8, 3);
	mainLayout->addWidget(rlLogLabel, 9, 0);
	mainLayout->addWidget(rlLogTextEdit, 9, 1, 1, 2);
	mainLayout->addWidget(rlLogBrowseButton, 9, 3);
	mainLayout->addWidget(rlCompileButton, 10, 2, 1, 2);
	mainLayout->addWidget(rlSpacerLabel, 11, 2);
	setLayout(mainLayout);

	setWindowTitle(tr("Data Model & Ruleset Compiler"));
	resize(800, 540);
}
//! [1]

//! [2]
void BEMCompiler::browseDMDefs()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Data Model Definitions File"), QDir::currentPath(), tr("*.txt"));
		//	getOpenFileName(QWidget *parent = Q_NULLPTR, 
		//		const QString &caption = QString(), 
		//		const QString &dir = QString(), 
		//		const QString &filter = QString(), 
		//		QString *selectedFilter = Q_NULLPTR, 
		//		Options options = Options())
	if (!file.isEmpty())
		dmDefsTextEdit->setText(file);
}
//! [2]

//! [3]
void BEMCompiler::browseDMEnums()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Data Model Enumerations File"), QDir::currentPath(), tr("*.txt"));
	if (!file.isEmpty())
		dmEnumsTextEdit->setText(file);
}
//! [3]

//! [4]
void BEMCompiler::browseDMCompiled()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Compiled Data Model (binary) File"), QDir::currentPath(), tr("*.bin"));
	if (!file.isEmpty())
		dmCompiledTextEdit->setText(file);
}
//! [4]

//! [5]
void BEMCompiler::compileDataModel()
{
	compileAll( true /*bDataModel*/, false /*bRuleset*/, false /*bCommandLine*/ );
}
//! [5]

//! [6]
void BEMCompiler::browseRLPrim()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Primary Ruleset Source File"), QDir::currentPath(), tr("*.txt"));
	if (!file.isEmpty())
		rlPrimTextEdit->setText(file);
}
//! [6]

//! [7]
void BEMCompiler::browseRLCompiled()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Compiled Ruleset (binary) File"), QDir::currentPath(), tr("*.bin"));
	if (!file.isEmpty())
		rlCompiledTextEdit->setText(file);
}
//! [7]

//! [8]
void BEMCompiler::browseRLLog()
{
	QString file = QFileDialog::getOpenFileName( this, 
					tr("Select Ruleset Log/Error File"), QDir::currentPath(), tr("*.*"));
	if (!file.isEmpty())
		rlLogTextEdit->setText(file);
}
//! [8]

//! [9]
void BEMCompiler::compileRuleset()
{
	compileAll( false /*bDataModel*/, true /*bRuleset*/, false /*bCommandLine*/ );
}
//! [9]

//! [10]
QTextEdit *BEMCompiler::createTextEdit(const QString &text)
{
	QTextEdit *textEdit = new QTextEdit(text);
	QFontMetrics fm( font );
//	textEdit->setFixedHeight( fm.lineSpacing()+10 );
	textEdit->setFixedHeight( fm.height()+10 );
	return textEdit;
}
//! [10]

//! [11]
QPushButton *BEMCompiler::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}
//! [11]


// main data model & ruleset compilation routine
// return values:
//		 0 - success
//		 1 - one or more data model fields left unspecified
//		 2 - Data Model Definitions file not found
//		 3 - Data Model Enumerations file not found
//		 4 - Data model compilation failed, see details
//		11 - one or more ruleset fields left unspecified
//		12 - Primary Ruleset (source) file not found
//		13 - Binary data model file not found
//		14 - Ruleset compilation failed, see log file for details
int BEMCompiler::compileAll( bool bDataModel, bool bRuleset, bool bCommandLine )
{	int iRetVal = 0;
	QString sMsg, sDetails, sCaption;

	if (bDataModel && bRuleset)
		sCaption = "Data Model and Ruleset Compilation";
	else if (bDataModel)
		sCaption = "Data Model Compilation";
	else
		sCaption = "BEM Ruleset Compilation";

	QString qAppDir = QCoreApplication::applicationDirPath();
	qAppDir = QDir::cleanPath(qAppDir);
	// data model binary needed for BOTH compilation options
	QString fileDMCmpld = dmCompiledTextEdit->toPlainText();
	GetFullPath( fileDMCmpld, qAppDir );

	if (bDataModel)
	{	QString fileDefs  = dmDefsTextEdit->toPlainText();
		QString fileEnums = dmEnumsTextEdit->toPlainText();
		GetFullPath( fileDefs, qAppDir );
		GetFullPath( fileEnums, qAppDir );
		if (fileDefs.isEmpty() || fileEnums.isEmpty() || fileDMCmpld.isEmpty())
		{	iRetVal = 1;
			sMsg = "All Data Model fields above must be provided before the data model can be compiled.";
		}
		else if (!QFile::exists(fileDefs))
		{	iRetVal = 2;
			sMsg = QString( "Data Model Definitions file not found:\n%1" ).arg( fileDefs );
		}
		else if (!QFile::exists(fileEnums))
		{	iRetVal = 3;
			sMsg = QString( "Data Model Enumerations file not found:\n%1" ).arg( fileEnums );
		}
	//	else if (!CFile::exists(fileDefs))
	//		sErrMsg = QString( "Data Model Definitions file not found:\n%1" ).arg( fileDefs );
		else
		{	//CBEMPCmplApp *pApp = (CBEMPCmplApp*)AfxGetApp();
			//BOOL bReportBEMStats = pApp && pApp->IsUIActive();
			//BOOL bReportBEMStats = TRUE;
			QApplication::setOverrideCursor(Qt::BusyCursor);
			QApplication::processEvents();

			BOOL bCompOK = BEMPX_CompileDataModel(	fileDefs.toLocal8Bit().constData(), fileEnums.toLocal8Bit().constData(),
																fileDMCmpld.toLocal8Bit().constData(), &sDetails );

			QApplication::restoreOverrideCursor();
			QApplication::processEvents();

			sMsg = QString( "Data Model compilation:  %1" ).arg( (bCompOK ? "Succeeded" : "Failed") );
			if (!bCompOK)
				iRetVal = 4;
		}
	}	// end of data model compilation


	if (iRetVal==0 && bRuleset)
	{	bool bDataModelCompiled = (!sMsg.isEmpty());
		QString filePrim  = rlPrimTextEdit->toPlainText();
		QString fileCmpld = rlCompiledTextEdit->toPlainText();
		QString fileLog = rlLogTextEdit->toPlainText();
		GetFullPath( filePrim, qAppDir );
		GetFullPath( fileCmpld, qAppDir );
		GetFullPath( fileLog, qAppDir );
		if (bDataModelCompiled)
			sMsg += "\n\n";
		if (filePrim.isEmpty() || fileCmpld.isEmpty() || fileLog.isEmpty())
		{	iRetVal = 11;
			sMsg += "All Ruleset File fields above must be provided before the ruleset can be compiled.";
		}
		else if (!QFile::exists(filePrim))
		{	iRetVal = 12;
			sMsg += QString( "Primary Ruleset (source) file not found:\n%1" ).arg( filePrim );
		}
		else if (!QFile::exists(fileDMCmpld))
		{	iRetVal = 13;
			sMsg += QString( "Binary data model file not found:\n%1" ).arg( fileDMCmpld );
		}
		else
		{
			QApplication::setOverrideCursor(Qt::BusyCursor);
			QApplication::processEvents();

			QString sRuleDetails;
			BOOL bCompOK = BEMPX_CompileRuleset( fileDMCmpld.toLocal8Bit().constData(), filePrim.toLocal8Bit().constData(),
															 fileCmpld.toLocal8Bit().constData(), fileLog.toLocal8Bit().constData(), &sRuleDetails );

			QApplication::restoreOverrideCursor();
			QApplication::processEvents();

			if (!sRuleDetails.isEmpty())
			{	if (bDataModelCompiled)
					sDetails += "\n\nRuleset Compilation Details:\n";
				sDetails += sRuleDetails;
			}
			sMsg += QString( "BEM Ruleset compilation:  %1" ).arg( (bCompOK ? "Succeeded" : "Failed") );
			if (!bCompOK)
				iRetVal = 14;
		}
	}	// end of ruleset compilation

	if (!sMsg.isEmpty())
	{
			QMessageBox msgBox;
			msgBox.setWindowTitle( sCaption );
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
	return iRetVal;
}
