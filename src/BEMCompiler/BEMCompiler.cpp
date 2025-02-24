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
#ifdef CBECC_RES19
	QApplication::setApplicationName("BEMCompiler - Residential 2019");
	QApplication::setApplicationVersion("1.0");
#elif CBECC_RES22
	QApplication::setApplicationName("BEMCompiler - Residential 2022");
	QApplication::setApplicationVersion("1.0");
#else		// CBECC-Com
	QApplication::setApplicationName("BEMCompiler - Commercial");
	QApplication::setApplicationVersion("1.0");
#endif

	QCommandLineParser parser;
	parser.setApplicationDescription("Test helper");
	parser.addHelpOption();
	parser.addVersionOption();

	// add command line options
	QCommandLineOption sharedPath1Option( "sharedPath1",        // SAC 08/02/21 (MFam)
				QCoreApplication::translate("main", "Set shared data model and rule file path #1 <sharedpath1>."),
				QCoreApplication::translate("main", "sharedpath1"));
		parser.addOption(sharedPath1Option);
	QCommandLineOption sharedPath2Option( "sharedPath2",
				QCoreApplication::translate("main", "Set shared data model and rule file path #2 <sharedpath2>."),
				QCoreApplication::translate("main", "sharedpath2"));
		parser.addOption(sharedPath2Option);
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
	QCommandLineOption guiOptionNoResult("noResultGUI", QCoreApplication::translate("main", "Prevent any display of processing result"));		// SAC 1/23/17
	parser.addOption(guiOptionNoResult);
	QCommandLineOption guiOptionNoSuccess("noSuccessGUI", QCoreApplication::translate("main", "Prevent display of processing result success message"));		// SAC 1/23/17
	parser.addOption(guiOptionNoSuccess);
	// Process the actual command line arguments given by the user
	parser.process(app);

//BEMCompiler16c.exe --bemBaseTxt="../Com/Rules/src/CEC 2013 NonRes BEMBase.txt" --bemEnumsTxt="../Com/Rules/src/CEC 2013 NonRes BEMEnums.txt" --bemBaseBin="../Com/Rules/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin"
//   --rulesTxt="../Com/Rules/src/Rules/CEC 2016 NonRes.txt" --rulesBin="../Com/Rules/CEC 2016 NonRes.bin" --rulesLog="../Com/Rules/src/Rules/Rules-2016 Log.out" --compileDM --compileRules

//BEMCompiler16c.exe --bemBaseTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMBase.txt" --bemEnumsTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMEnums.txt" --bemBaseBin="Data-os/Rulesets/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin"
//   --rulesTxt="../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/CEC 2016 NonRes.txt" --rulesBin="Data-os/Rulesets/CEC 2016 NonRes.bin" --rulesLog="../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/Rules-2016 Log.out" --compileDM --compileRules

// create main UI dialog
	BEMCompiler bemCmplr;

// before applying command line path/file settings, default all
#ifdef CBECC_RES19
// to compile rules relative to Debug/Release exe -> bin\Res\rule source locations
	bemCmplr.SetSP1Text(      "../Res/RuleDev/shared/" );
	bemCmplr.SetBEMBaseText(  "../Res/RuleDev/T24R/CAR13 BEMBase.txt" );
	bemCmplr.SetBEMEnumsText( "../Res/RuleDev/T24R/CAR19 BEMEnums.txt" );
	bemCmplr.SetBEMBaseBin(   "../Res/Rulesets/CA Res 2019/CAR19 BEMBase.bin" );
	bemCmplr.SetRuleText(     "../Res/RuleDev/T24R/Rules/Rules-2016.txt" );
	bemCmplr.SetRuleBin(      "../Res/Rulesets/CA Res 2019.bin" );
	bemCmplr.SetRuleLog(      "../Res/RuleDev/T24R/Rules/Rules19 Log.out" );

//// to compile rules relative to SVN exe->rule source locations
//	bemCmplr.SetBEMBaseText(  "../RulesetDev/Rulesets/CA Res/CAR13 BEMBase.txt" );
//	bemCmplr.SetBEMEnumsText( "../RulesetDev/Rulesets/CA Res/CAR16 BEMEnums.txt" );
//	bemCmplr.SetBEMBaseBin(   "Data/Rulesets/CA Res 2016/CAR16 BEMBase.bin" );
//	bemCmplr.SetRuleText(     "../RulesetDev/Rulesets/CA Res/Rules/Rules-2016.txt" );
//	bemCmplr.SetRuleBin(      "Data/Rulesets/CA Res 2016.bin" );
//	bemCmplr.SetRuleLog(      "../RulesetDev/Rulesets/CA Res/Rules/Rules-2016-os Log.out" );

//// to compile rules relative to SVN exe->rule source locations
//	bemCmplr.SetBEMBaseText(  "../../RuleDev/Rulesets/CA RESNET/CAR13 BEMBase.txt" );
//	bemCmplr.SetBEMEnumsText( "../../RuleDev/Rulesets/CA RESNET/CAR19 BEMEnums.txt" );
//	bemCmplr.SetBEMBaseBin(   "../Res/Rules/CA Res 2019/CAR19 BEMBase.bin" );
//	bemCmplr.SetRuleText(     "../../RuleDev/Rulesets/CA RESNET/Rules/Rules-2019-2-0.txt" );
//	bemCmplr.SetRuleBin(      "../Res/Rules/CA Res 2019.bin" );
//	bemCmplr.SetRuleLog(      "../../RuleDev/Rulesets/CA RESNET/Rules/Rules-2019-RESNET dbg Log.out" );
#else		// CBECC-Com
// to compile rules relative to Debug/Release exe -> bin\Com\rule source locations
	bemCmplr.SetSP1Text(      "../Com/RuleDev/src/shared/" );
	bemCmplr.SetBEMBaseText(  "../Com/RuleDev/src/BEMBase.txt" );
	bemCmplr.SetBEMEnumsText( "../Com/RuleDev/src/T24N/T24N_2022 BEMEnums.txt" );
	bemCmplr.SetBEMBaseBin(   "../Com/Rulesets/T24N_2022/T24N_2022 BEMBase.bin" );
	bemCmplr.SetRuleText(     "../Com/RuleDev/src/T24N/Rules/T24N_2022.txt" );
	bemCmplr.SetRuleBin(      "../Com/Rulesets/T24N_2022.bin" );
	bemCmplr.SetRuleLog(      "_Rules-2022 Log.out" );

//// to compile rules relative to SVN exe->rule source locations
//	bemCmplr.SetBEMBaseText(  "../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMBase.txt" );
//	bemCmplr.SetBEMEnumsText( "../RulesetDev/Rulesets/CEC 2013 Nonres/CEC 2013 NonRes BEMEnums.txt" );
//	bemCmplr.SetBEMBaseBin(   "Data-os/Rulesets/CEC 2016 NonRes/CEC 2016 NonRes BEMBase.bin" );
//	bemCmplr.SetRuleText(     "../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/CEC 2016 NonRes.txt" );
//	bemCmplr.SetRuleBin(      "Data-os/Rulesets/CEC 2016 NonRes.bin" );
//	bemCmplr.SetRuleLog(      "../RulesetDev/Rulesets/CEC 2013 Nonres/Rules/Rules-2016 Log.out" );
#endif

// now apply command line path/file arguments
	QString qsSP1 = parser.value(sharedPath1Option);      // SAC 08/02/21 (MFam)
	if (!qsSP1.isEmpty())
		bemCmplr.SetSP1Text( qsSP1 );
	QString qsSP2 = parser.value(sharedPath2Option);
	if (!qsSP2.isEmpty())
		bemCmplr.SetSP2Text( qsSP2 );
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
	int iGUIOption = (parser.isSet(guiOptionNoResult) ? 0 : (parser.isSet(guiOptionNoSuccess) ? 1 : 2));		// SAC 1/3/17

	bemCmplr.show();

//	if (compileDM || compileRules)
//		app.exit( bemCmplr.compileAll( compileDM, compileRules, true /*bCommandLine*/ ) );
//	return app.exec();

	int iRetVal = 0;
	if (compileDM || compileRules)
		iRetVal = bemCmplr.compileAll( compileDM, compileRules, true /*bCommandLine*/, iGUIOption /*2*/ );
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

	sp1BrowseButton = createButton(tr("..."), SLOT(browseSP1()));
	sp2BrowseButton = createButton(tr("..."), SLOT(browseSP2()));
	dmDefsBrowseButton = createButton(tr("..."), SLOT(browseDMDefs()));
	dmEnumsBrowseButton = createButton(tr("..."), SLOT(browseDMEnums()));
	dmCompiledBrowseButton = createButton(tr("..."), SLOT(browseDMCompiled()));
	dmCompileButton = createButton(tr("  Compile &Data Model  "), SLOT(compileDataModel()));
	rlPrimBrowseButton = createButton(tr("..."), SLOT(browseRLPrim()));
	rlCompiledBrowseButton = createButton(tr("..."), SLOT(browseRLCompiled()));
	rlLogBrowseButton = createButton(tr("..."), SLOT(browseRLLog()));
	rlCompileButton = createButton(tr("  Compile &Ruleset  "), SLOT(compileRuleset()));

	sp1TextEdit = createTextEdit();
	sp2TextEdit = createTextEdit();
	dmDefsTextEdit = createTextEdit();
	dmEnumsTextEdit = createTextEdit();
	dmCompiledTextEdit = createTextEdit();
	rlPrimTextEdit = createTextEdit();
	rlCompiledTextEdit = createTextEdit();
	rlLogTextEdit = createTextEdit();

	spLabel = new QLabel(tr("Shared File Path(s):"));
	spSpacerLabel = new QLabel(tr("   "));
	spSpacer2Label = new QLabel(tr("   "));
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

//	spSpacerLabel->setFont( font );
//	dmSpacerLabel->setFont( font );
//	rlSpacerLabel->setFont( font );
	spLabel->setFont( fontBold );
	dmCompilerLabel->setFont( fontBold );
	dmCompileButton->setFont( fontBold );
	rlCompilerLabel->setFont( fontBold );
	rlCompileButton->setFont( fontBold );

	QFontMetrics fm( font );
	int iBrowseBtnWd = fm.horizontalAdvance("...")+10;
	sp1BrowseButton->setFixedWidth( iBrowseBtnWd );
	sp2BrowseButton->setFixedWidth( iBrowseBtnWd );
	dmDefsBrowseButton->setFixedWidth( iBrowseBtnWd );
	dmEnumsBrowseButton->setFixedWidth( iBrowseBtnWd );
	dmCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlPrimBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlCompiledBrowseButton->setFixedWidth( iBrowseBtnWd );
	rlLogBrowseButton->setFixedWidth( iBrowseBtnWd );

	int iFileLabelWd = fm.horizontalAdvance("   Data Model Enumerations File:")+10;
	spLabel->setFixedWidth( iFileLabelWd );
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

	mainLayout->addWidget(spSpacerLabel, 0, 0);     // added for shared paths - SAC 07/31/21 (MFam)
	mainLayout->addWidget(spLabel, 1, 0);
	mainLayout->addWidget(sp1TextEdit, 1, 1, 1, 2);
	mainLayout->addWidget(sp1BrowseButton, 1, 3);
	mainLayout->addWidget(sp2TextEdit, 2, 1, 1, 2);
	mainLayout->addWidget(sp2BrowseButton, 2, 3);
	mainLayout->addWidget(spSpacer2Label, 3, 0); 

	mainLayout->addWidget(dmCompilerLabel, 4, 0);
	mainLayout->addWidget(dmDefsLabel, 5, 0);
	mainLayout->addWidget(dmDefsTextEdit, 5, 1, 1, 2);
	mainLayout->addWidget(dmDefsBrowseButton, 5, 3);
	mainLayout->addWidget(dmEnumsLabel, 6, 0);
	mainLayout->addWidget(dmEnumsTextEdit, 6, 1, 1, 2);
	mainLayout->addWidget(dmEnumsBrowseButton, 6, 3);
	mainLayout->addWidget(dmCompiledLabel, 7, 0);
	mainLayout->addWidget(dmCompiledTextEdit, 7, 1, 1, 2);
	mainLayout->addWidget(dmCompiledBrowseButton, 7, 3);
	mainLayout->addWidget(dmCompileButton, 8, 2, 1, 2);
	mainLayout->addWidget(dmSpacerLabel, 9, 2);
	mainLayout->addWidget(rlCompilerLabel, 10, 0);
	mainLayout->addWidget(rlPrimLabel, 11, 0);
	mainLayout->addWidget(rlPrimTextEdit, 11, 1, 1, 2);
	mainLayout->addWidget(rlPrimBrowseButton, 11, 3);
	mainLayout->addWidget(rlCompiledLabel, 12, 0);
	mainLayout->addWidget(rlCompiledTextEdit, 12, 1, 1, 2);
	mainLayout->addWidget(rlCompiledBrowseButton, 12, 3);
	mainLayout->addWidget(rlLogLabel, 13, 0);
	mainLayout->addWidget(rlLogTextEdit, 13, 1, 1, 2);
	mainLayout->addWidget(rlLogBrowseButton, 13, 3);
	mainLayout->addWidget(rlCompileButton, 14, 2, 1, 2);
	mainLayout->addWidget(rlSpacerLabel, 15, 2);
	setLayout(mainLayout);

	setWindowTitle(tr("Data Model & Ruleset Compiler"));
	resize(800, 660);
}
//! [1]

void BEMCompiler::browseSP1()
{
	QString dir = QFileDialog::getExistingDirectory( this, 
					tr("Select Shared File Path #1"), QDir::currentPath(),
               QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty())
		sp1TextEdit->setText(dir);
}

void BEMCompiler::browseSP2()
{
	QString dir = QFileDialog::getExistingDirectory( this, 
					tr("Select Shared File Path #1"), QDir::currentPath(),
               QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty())
		sp2TextEdit->setText(dir);
}

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
int BEMCompiler::compileAll( bool bDataModel, bool bRuleset, bool /*bCommandLine*/, int iGUIOption /*2*/ )
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

	QString fileEnums = dmEnumsTextEdit->toPlainText();
	GetFullPath( fileEnums, qAppDir );
   bool bWritePrevNamesToIDMTxt = (!fileEnums.isEmpty() && fileEnums.indexOf("19") >= 0);    // SAC 08/05/21

   QStringList qslSharedPaths;
	QString sp[2] = { sp1TextEdit->toPlainText(), sp2TextEdit->toPlainText() };
   for (int iSP=0; iSP<2; iSP++)
      if (sp[iSP].length() > 0)
      {
	      GetFullPath( sp[iSP], qAppDir );
         if (sp[iSP].lastIndexOf("//") != sp[iSP].length()-1 &&
             sp[iSP].lastIndexOf("/" ) != sp[iSP].length()-1)
            sp[iSP] += "/";
         qslSharedPaths.append(sp[iSP]);
      }

	if (bDataModel)
	{	QString fileDefs  = dmDefsTextEdit->toPlainText();
		GetFullPath( fileDefs, qAppDir );
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
		{
         //CBEMPCmplApp *pApp = (CBEMPCmplApp*)AfxGetApp();
			//BOOL bReportBEMStats = pApp && pApp->IsUIActive();
			//BOOL bReportBEMStats = TRUE;
			QApplication::setOverrideCursor(Qt::BusyCursor);
			QApplication::processEvents();

			BOOL bCompOK = BEMPX_CompileDataModel(	fileDefs.toLocal8Bit().constData(), fileEnums.toLocal8Bit().constData(),
																fileDMCmpld.toLocal8Bit().constData(), &sDetails,
                                                (qslSharedPaths.size() > 0 ? &qslSharedPaths : NULL) );

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
															 fileCmpld.toLocal8Bit().constData(), fileLog.toLocal8Bit().constData(),
                                              &sRuleDetails, (qslSharedPaths.size() > 0 ? &qslSharedPaths : NULL) );

		// SAC 10/12/16 - added code to create and store data model documentaiton files
			if (bCompOK)
			{	QString sSimDataModelOutFile = fileCmpld.left( fileCmpld.lastIndexOf('.') );
				QString sInpDataModelOutFile = sSimDataModelOutFile + " - Input Data Model.txt";
				sSimDataModelOutFile += " - Sim Data Model.txt";
				if (!BEMPX_LoadDataModel( fileDMCmpld.toLocal8Bit().constData(), BEMT_CBECC ))
				{	assert( false );	// initialization of BEM failed
				}
				else if (!BEMPX_LoadRuleset( fileCmpld.toLocal8Bit().constData(), TRUE /*bDeleteAllObjects*/ ))
				{	assert( false );	// error loading (newly compiled) ruleset binary file
				}
				else
				{	BEMPX_WriteDataModelExport( BEMDMX_INPMP, sInpDataModelOutFile.toLocal8Bit().constData(), bWritePrevNamesToIDMTxt );
					BEMPX_WriteDataModelExport( BEMDMX_SIM  , sSimDataModelOutFile.toLocal8Bit().constData(), bWritePrevNamesToIDMTxt );
			}	}

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

	if (!sMsg.isEmpty() && (iGUIOption >= 2 || (iGUIOption == 1 && iRetVal > 0)))		// SAC 1/3/17
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
