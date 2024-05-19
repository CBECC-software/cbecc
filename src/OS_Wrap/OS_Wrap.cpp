// This is the main DLL file.
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

#include "OS_Wrap.h"
#include "Windows.h"

#pragma warning(disable : 4100 4127 4512)
#include <model/Model.hpp>
#include <model/WeatherFile.hpp>
#include <model/Facility.hpp>
#include <model/Facility_Impl.hpp>
#include <model/OutputMeter.hpp>
#include <model/OutputMeter_Impl.hpp>
#include <model/MeterCustom.hpp>
#include <model/MeterCustom_Impl.hpp>
#include <model/RunPeriod.hpp>
#include <model/RunPeriod_Impl.hpp>
//#include <model/SimulationControl.hpp>
//#include <model/SimulationControl_Impl.hpp>

#include <model/PlanarSurface.hpp>		// SAC 5/23/14 - added to facilitate polygon vertex re-ordering
#include <model/PlanarSurface_Impl.hpp>
#include <model/Surface.hpp>
#include <model/Surface_Impl.hpp>
//#include <model/SubSurface.hpp>
//#include <model/SubSurface_Impl.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Point3d.hpp>
//#include <utilities/geometry/Vector3d.hpp>

#include <energyplus/ErrorFile.hpp>
#include <energyplus/ReverseTranslator.hpp>
#include <energyplus/ForwardTranslator.hpp>

#include <gbxml/ReverseTranslator.hpp>

#include <utilities/core/CommandLine.hpp>
#include <utilities/core/Path.hpp>
#include <utilities/core/PathHelpers.hpp>
#include <utilities/core/UnzipFile.hpp>
#include <utilities/data/EndUses.hpp>

#include <sdd/ReverseTranslator.hpp>
#include <sdd/ForwardTranslator.hpp>

//#include <runmanager/lib/JobFactory.hpp>
//#include <runmanager/lib/RunManager.hpp>
//#include <runmanager/lib/Workflow.hpp>
//#include <runmanager/lib/ConfigOptions.hpp>
////#include <runmanager/lib/RubyJobUtils.hpp>

//3-12 //#include <ruleset/UserScriptArgument.hpp>

//#include <utilities/core/Application.hpp>
//#include <utilities/core/System.hpp>
#include <utilities/filetypes/EpwFile.hpp>
#include <utilities/sql/SqlFile.hpp>
#include <utilities/sql/SqlFile_Impl.hpp>
#include <utilities/idf/IdfFile.hpp>
#include <utilities/idd/RunPeriod_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_Meter_FieldEnums.hxx>		// SAC 9/30/15
#include <utilities/idd/Output_Variable_FieldEnums.hxx>		// SAC 9/30/15

#include <OpenStudio.hxx>	// SAC 8/22/14 - access to OpenStudio version ID

//#include <QDir>
#include <QMessageBox>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/optional/optional_io.hpp>   //VS19 - SAC 10/14/20
//#include <boost/algorithm/string.hpp>
//#include <algorithm>
//#include <string>
#pragma warning(default : 4100 4127 4512)
#include "memLkRpt.h"

//#include <io.h>     //VS19 - SAC 10/20/20
#include <iostream>     //VS19 - SAC 10/20/20
#include <fstream>

using namespace OS_Wrap;
//using boost::format;


const char* pszaEplusEnduses[][2] = {	{	"InteriorLights",          ""                   },	//  0   (sum)
													{	"ExteriorLights",          ""                   },	//  1
													{	"InteriorEquipment",       ""                   },	//  2   (sum)
													{	"ExteriorEquipment",       ""                   },	//  3
													{	"Fans",                    ""                   },	//  4
													{	"Pumps",                   ""                   },	//  5
													{	"Heating",                 ""                   },	//  6
													{	"Cooling",                 ""                   },	//  7
													{	"HeatRejection",           ""                   },	//  8
													{	"Humidifier",              ""                   },	//  9
													{	"HeatRecovery",            ""                   },	// 10
													{	"WaterSystems",            ""                   },	// 11
													{	"Cogeneration",            ""                   },	// 12
													{	"Refrigeration",           ""                   },	// 13
										//			{	"Miscellaneous",           ""                   },	// --
													{	"HeatingCoils",            ""                   },	// 14
													{	"CoolingCoils",            ""                   },	// 15
													{	"Boilers",                 ""                   },	// 16
													{	"Baseboard",               ""                   },	// 17
													{	"HeatRecoveryForCooling",  ""                   },	// 18
													{	"HeatRecoveryForHeating",  ""                   },	// 19
													{	"InteriorLights",          "ComplianceLtg"      },	// 20		// SAC 11/7/15 - 'Reg Ltg' -> 'ComplianceLtg' (SF tic 544)        
													{	"InteriorLights",          "NonComplianceLtg"   },	// 21		// SAC 11/7/15 - 'NonReg Ltg' -> 'NonComplianceLtg' (SF tic 544)  
													{	"InteriorEquipment",       "Receptacle"         },	// 22
													{	"InteriorEquipment",       "Process"            },	// 23
													{	"InteriorEquipment",       "Refrig"             },	// 24
													{	"InteriorEquipment",       "Internal Transport" },	// 25
													{	"Fans",                    "ProcessMotors"      },	// 26		// SAC 1/30/17 - 'NonReg Fans' -> remove from straight Fans and add into Process  // SAC 8/14/17 - switched ParkingGarageFans to ProcessMotors
													{	"<unknown enduse>",        ""                   }, };
#define  HrlyEUs_LastUniqueEU  19
// #define  OSWrap_NumEPlusEnduses  25


//OSWrapLib::OSWrapLib()
//{
//}


// return values:  0 => SUCCESS
//                >0 => 
//                -1 => 
long OSWrapLib::SDDtoOSM( const char* pszSDDXMLFileName )
{
	long lRetVal = 0;

	std::string inputPathString;
	inputPathString = pszSDDXMLFileName;  // "E:\\dev\\CBECC-vs08\\src\\CBECC-OS\\data\\CustomPrimarySchool_JulyPAC_Proposed.xml";
	openstudio::path inputPath = openstudio::toPath(inputPathString);

	openstudio::sdd::ReverseTranslator reverseTranslator;
	boost::optional<openstudio::model::Model> model = reverseTranslator.loadModel(inputPath);
	if(model)
	{
		openstudio::path osmPath = inputPath.replace_extension(openstudio::toPath("osm").string());
		model->save(osmPath, true);
	}
	else
		lRetVal = 1;

   return lRetVal;
}


// return values:  0 => SUCCESS
//                 1 => Unrecognized input model file type
//                10 => Error loading input OpenStudio model file
//                11 => Error converting OpenStudio model to SDD XML file
//                20 => Error converting input EnergyPlus (IDF) file to OSM (OpenStudio Model)
//                21 => Error converting OpenStudio model to SDD XML file (following import of EnergyPlus IDF)
//                30 => Error converting input GBXML file to OSM (OpenStudio Model)
//                31 => Error converting OpenStudio model to SDD XML file (following import of GBXML)
long OSWrapLib::TranslateToSDD( const char* pszInputPathFile, const char* pszOutputPathFile, int iInputType )
{
	long lRetVal = 0;

	std::string inputPathString  = pszInputPathFile;
	std::string outputPathString = pszOutputPathFile;
	openstudio::path inputOSPathFile  = openstudio::toPath(inputPathString);
	openstudio::path outputOSPathFile = openstudio::toPath(outputPathString);
	switch (iInputType)
	{	case	OSWFT_OSM	:	{	// load OSM model and forward translate to SDD XML
										openstudio::OptionalIdfFile idfFile = openstudio::IdfFile::load( inputOSPathFile );  // previously ended:  , openstudio::IddFileType::OpenStudio );
										if (!idfFile)
											lRetVal = 10;
										else
										{	//openstudio::Workspace inWorkspace( *idfFile );
											//openstudio::energyplus::ReverseTranslator reverseTranslator;
											//openstudio::model::Model model = reverseTranslator.translateWorkspace(inWorkspace);
											openstudio::model::Model model( *idfFile );
											openstudio::sdd::ForwardTranslator forwardTranslator;
											if (!forwardTranslator.modelToSDD( model, outputOSPathFile ))
												lRetVal = 11;
										}
									}	break;

		case	OSWFT_EPlus	:	{	// reverse translate EnergyPlus input file to OSM, then forward translate to SDD XML


	// Allow OpenStudio to use whatever version of EnergyPlus is loadde on the user's machine - OR perhaps attempt to use the 
   //------------------------- 
	//	TEST_F(EnergyPlusFixture,IddFile)
	//	{
	//	  boost::optional<openstudio::IddFile> iddFile = openstudio::IddFile::load(resourcesPath() / openstudio::toPath("energyplus/ProposedEnergy+.idd"));
	//	  ASSERT_TRUE(iddFile);
	//	}
   //------------------------- 
	//	openstudio::path idfPath = resourcesPath() / toPath("energyplus/BestestEx/in.idf");
	//	OptionalIdfFile idfFile = IdfFile::load(idfPath, IddFileType::EnergyPlus);
	//	ASSERT_TRUE(idfFile);
	//	Workspace inWorkspace(*idfFile);
	//	
	//	ReverseTranslator reverseTranslator;
	//	Model model = reverseTranslator.translateWorkspace(inWorkspace);
	//	model.save( resourcesPath() / toPath("energyplus/BestestEx/in.osm"), true);
	//	
	//	ForwardTranslator forwardTranslator;
	//	Workspace workspace = forwardTranslator.translateModel(model);
	//	workspace.save( resourcesPath() / toPath("energyplus/BestestEx/in2.idf"), true);
   //------------------------- 
	//	openstudio::path p = resourcesPath() / toPath("resultsviewer/SmallOffice/SmallOffice.idf");
	//	Workspace ws = Workspace::load(p).get();
	//	ReverseTranslator rt;
	//	Model model = rt.translateWorkspace(ws);
	//	
	//	OptionalSubSurface osub = model.getModelObjectByName<SubSurface>("Perimeter_ZN_1_wall_south_door");
	//	ASSERT_TRUE(osub);
	//	EXPECT_EQ("GlassDoor",osub->subSurfaceType());
   //------------------------- 

										openstudio::OptionalIdfFile idfFile = openstudio::IdfFile::load( inputOSPathFile );  // previously ended:  , openstudio::IddFileType::EnergyPlus );
										if (!idfFile)
											lRetVal = 20;
										else
										{	openstudio::Workspace inWorkspace( *idfFile );
											openstudio::energyplus::ReverseTranslator reverseTranslator;
											openstudio::model::Model model = reverseTranslator.translateWorkspace(inWorkspace);
											openstudio::sdd::ForwardTranslator forwardTranslator;
											if (!forwardTranslator.modelToSDD( model, outputOSPathFile ))
												lRetVal = 21;
										}

//											openstudio::energyplus::ReverseTranslator reverseTranslator;
//	
//	// NOTE - need to check that input model (IDF?) was for a valid/supported version of EnergyPlus
//	
//											boost::optional<openstudio::model::Model> model = reverseTranslator.loadModel(inputOSPathFile);
//											if (!model)
//												lRetVal = 20;
//											else
//											{	openstudio::sdd::ForwardTranslator forwardTranslator;
//												if (!forwardTranslator.modelToSDD( *model, outputOSPathFile ))
//													lRetVal = 21;
//											}
									}	break;

		case	OSWFT_GBXML	:	{	// reverse translate Green Building XML file to OSM, then forward translate to SDD XML
										openstudio::gbxml::ReverseTranslator reverseTranslator;
										boost::optional<openstudio::model::Model> model = reverseTranslator.loadModel(inputOSPathFile);
										if (!model)
											lRetVal = 30;
										else
										{	openstudio::sdd::ForwardTranslator forwardTranslator;
											if (!forwardTranslator.modelToSDD( *model, outputOSPathFile ))
												lRetVal = 31;
										}
									}	break;

		default				:		lRetVal = 1;
										break;
	}

   return lRetVal;
}


std::string OSWrapLib::GetOpenStudioVersion( bool bLongVersion )	// SAC 8/22/14
{	return (bLongVersion ? openStudioLongVersion()
								: openStudioVersion() );
}

// return values: <0 => Error(s) encountered
//                >0 => EnergyPlus version <Major>.<Minor>
double OSWrapLib::EnergyPlusVersion( const char* pszEPlusPath )
{
	double dRetVal = -1.0;
//QMessageBox msgBox;
//msgBox.setText("in OSWrapLib::EnergyPlusVersion() - About to construct ConfigOptions");		msgBox.exec();
std::string sMsg;
	try
 	{	//openstudio::runmanager::ConfigOptions co;
		openstudio::path epdir;
		boost::optional<int> iMajor, iMinor;
		if (pszEPlusPath && strlen( pszEPlusPath ) > 0)
		{	epdir = openstudio::toPath(pszEPlusPath);
			if (!boost::filesystem::is_directory(epdir))
				dRetVal = -4.0;
			else	// SAC 4/26/16 - revise to grab version of EPlus version located in the directory specified
			{
			//	co.makeTools( epdir, openstudio::path(), openstudio::path(), openstudio::path(), openstudio::path() );
sMsg = boost::str( boost::format("in OSWrapLib::EnergyPlusVersion() - checking EPlus version from: %s") % pszEPlusPath );
//				co.findTools(false,false,false,false);

// SAC 2/19/19 - replacement??
//				openstudio::runmanager::Tools tools = openstudio::runmanager::ConfigOptions::makeTools( epdir,
//																			openstudio::path(), openstudio::path(), openstudio::path(), openstudio::path() );
//				iMajor = tools.getTool("energyplus").version.getMajor();
//				iMinor = tools.getTool("energyplus").version.getMinor();
		}	}
		else
		{
// SAC 2/19/19 - replacement??
//			openstudio::runmanager::ConfigOptions co;
////msgBox.setText("in OSWrapLib::EnergyPlusVersion() - About to call co.fastFindEnergyPlus()");		msgBox.exec();
//			co.fastFindEnergyPlus();
////msgBox.setText("in OSWrapLib::EnergyPlusVersion() - Back from co.fastFindEnergyPlus()");		msgBox.exec();
//sMsg = "in OSWrapLib::EnergyPlusVersion() - checking EPlus version based on co.fastFindEnergyPlus()";
//
//			iMajor = co.getTools().getTool("energyplus").version.getMajor();
////msgBox.setText("in OSWrapLib::EnergyPlusVersion() - Back from retrieving Major ver #");		msgBox.exec();
//			iMinor = co.getTools().getTool("energyplus").version.getMinor();
		}

		if (dRetVal == -1.0)
		{
			//openstudio::path epwdir = co.getDefaultEPWLocation();
			//openstudio::path epdir = epwdir.parent_path();
			//openstudio::path idfdir = co.getDefaultIDFLocation();
//			boost::optional<int> iMajor = co.getTools().getTool("energyplus").version.getMajor();
//msgBox.setText("in OSWrapLib::EnergyPlusVersion() - Back from retrieving Major ver #");		msgBox.exec();
//			boost::optional<int> iMinor = co.getTools().getTool("energyplus").version.getMinor();
			if (!iMajor)
				dRetVal = -1.0;
			else if (!iMinor)
				dRetVal = -2.0;
			else if (iMinor > 999)
				dRetVal = -3.0;
			else
			{	dRetVal = (double) *iMajor;
				if (iMinor < 10)
					dRetVal += ((double) *iMinor / 10.0);
				else if (iMinor < 100)
					dRetVal += ((double) *iMinor / 100.0);
				else
					dRetVal += ((double) *iMinor / 1000.0);
		}	}
	}
	catch (...) {}

sMsg += boost::str( boost::format("\nreturn %g") % dRetVal );
//msgBox.setText( QString( sMsg.c_str() ) );		msgBox.exec();

	return dRetVal;
}

//bool OSWrapLib::EnergyPlusVersionInstalled( int iMajor, int iMinor /*=-1*/, int iBuild /*=-1*/ )  // SAC 12/27/13
//{
//	bool bRetVal = false;
//	try
// 	{	openstudio::runmanager::ConfigOptions co;
//		co.reset();
//		if (iMinor >= 0 && iBuild >= 0)
//		{	openstudio::runmanager::ToolVersion e1( iMajor, iMinor, iBuild );
//
//// latest version:
////  class RUNMANAGER_API ToolLocationInfo
////      ToolLocationInfo(const ToolType &t_type, 
////                       const openstudio::path &t_bindir);
//			openstudio::runmanager::ToolLocationInfo p1 = openstudio::runmanager::ToolLocationInfo( openstudio::runmanager::ToolType("EnergyPlus"), openstudio::toPath("e1"), openstudio::path());
//			co.setToolLocation( e1, p1 );
//			openstudio::runmanager::Tools tools = co.getTools();
//			if (tools.getTool("energyplus").version == e1)
//				bRetVal = true;
//		}
//		else if (iMinor >= 0)
//		{	openstudio::runmanager::ToolVersion e1( iMajor, iMinor );
//			openstudio::runmanager::ToolLocationInfo p1 = openstudio::runmanager::ToolLocationInfo( openstudio::runmanager::ToolType("EnergyPlus"), openstudio::toPath("e1"), openstudio::path());
//			co.setToolLocation( e1, p1 );
//			openstudio::runmanager::Tools tools = co.getTools();
////QMessageBox msgBox;
////std::string sDbgMsg = boost::str( boost::format("EP: major %d, minor %d / Chk: major %d, minor %d") % *tools.getTool("energyplus").version.getMajor() % *tools.getTool("energyplus").version.getMinor() % *e1.getMajor() % *e1.getMinor() );
////msgBox.setText(sDbgMsg.c_str());		msgBox.exec();
//			if (tools.getTool("energyplus").version == e1)
//				bRetVal = true;
//
//		}
//		else
//		{	openstudio::runmanager::ToolVersion e1( iMajor );
//			openstudio::runmanager::ToolLocationInfo p1 = openstudio::runmanager::ToolLocationInfo( openstudio::runmanager::ToolType("EnergyPlus"), openstudio::toPath("e1"), openstudio::path());
//			co.setToolLocation( e1, p1 );
//			openstudio::runmanager::Tools tools = co.getTools();
//			if (tools.getTool("energyplus").version == e1)
//				bRetVal = true;
//		}
//	}
//	catch (...) {}
//
//	return bRetVal;
//}


void OSWrapLib::InitHourlyResults( int iRunIdx )		// SAC 4/17/14
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
								int iFl, iEU;
								for (iFl=0; (pLocRunData && iFl<3); iFl++)
								{	for (iEU=0; iEU<OSWrap_NumEPlusEnduses; iEU++)
										pLocRunData->daHourlyResults[iFl][iEU].resize( 8760, 0.0 );  // Fuel / Enduse
								}
}

void OSWrapLib::SumIntoHourlyResult( int iRunIdx, int iFuel, int iEnduse, int iHr, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
		pLocRunData->daHourlyResults[iFuel][iEnduse][iHr] += dVal;
}

void OSWrapLib::AdjustAndSumHourlyResults( int iRunIdx, double* daFuelConvert )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	pLocRunData->bHourlyResultsCurrent = true;
		int iFl, iEU, hr;

	// SAC 2/1/17 - hard-coded subtraction of OSEU_Fans_PrkgGar Elec from OSEU_Fans (tic #2033)  // SAC 8/14/17 - switched OSEU_Fans_PrkgGar to OSEU_Fans_ProcMtrs
		double dFans=0.0, dPGFans=0.0;
		for (hr=0; hr<8760; hr++)
		{	dFans   += pLocRunData->daHourlyResults[OSF_Elec][OSEU_Fans         ][hr];
			dPGFans += pLocRunData->daHourlyResults[OSF_Elec][OSEU_Fans_ProcMtrs][hr];
		}
		if (dPGFans > 0 && dFans > 0)
		{	assert( dPGFans <= dFans );
			for (hr=0; hr<8760; hr++)
				pLocRunData->daHourlyResults[OSF_Elec][OSEU_Fans][hr] -= pLocRunData->daHourlyResults[OSF_Elec][OSEU_Fans_ProcMtrs][hr];
		}

		for (iFl=0; iFl<3; iFl++)
			for (iEU=0; iEU<OSWrap_NumEPlusEnduses; iEU++)
			{	pLocRunData->daHourlyResultsSum[iFl][iEU] = 0.0;
				for (hr=0; hr<8760; hr++)
				{	pLocRunData->daHourlyResults[   iFl][iEU][hr] *= daFuelConvert[iFl];
					pLocRunData->daHourlyResultsSum[iFl][iEU]     += pLocRunData->daHourlyResults[iFl][iEU][hr];
				}
	}		}
}

int OSWrapLib::InitZoneData( int iRunIdx )
{	int iNumZones = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	iNumZones = (int) pLocRunData->saZone.size();
		if (iNumZones > 0)
		{
			pLocRunData->daZone_UMLHClg.resize( iNumZones, -1.0 );
			pLocRunData->daZone_UMLHHtg.resize( iNumZones, -1.0 );
         pLocRunData->daZone_ClgDsgnLd.resize( iNumZones, -1.0 );
         pLocRunData->daZone_HtgDsgnLd.resize( iNumZones, -1.0 );
         pLocRunData->daZone_ClgDsgnFlow.resize( iNumZones, -1.0 );
         pLocRunData->daZone_HtgDsgnFlow.resize( iNumZones, -1.0 );
	}	}
	return iNumZones;
}

std::string OSWrapLib::GetZoneName( int iRunIdx, int idx )
{	std::string sZnName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saZone.size())
		sZnName = pLocRunData->saZone[idx];
	return sZnName;
}

void OSWrapLib::SetZoneData( int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saZone.size())
		switch (iDataIdx)
		{	case  0 :	pLocRunData->daZone_UMLHClg[    idx] = dVal;		break;
			case  1 :	pLocRunData->daZone_UMLHHtg[    idx] = dVal;		break;
			case  2 :	pLocRunData->daZone_ClgDsgnLd[  idx] = dVal;		break;
			case  3 :	pLocRunData->daZone_HtgDsgnLd[  idx] = dVal;		break;
			case  4 :	pLocRunData->daZone_ClgDsgnFlow[idx] = dVal;		break;
			case  5 :	pLocRunData->daZone_HtgDsgnFlow[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitFanData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumFans = (int) pLocRunData->saFan.size();
		if (iNumFans > 0)
			pLocRunData->daFan_FlowCap.resize( iNumFans, -1.0 );
		return iNumFans;
	}
	return 0;
}

std::string OSWrapLib::GetFanName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saFan.size())
		sName = pLocRunData->saFan[idx];
	return sName;
}

void OSWrapLib::SetFanData(     int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saFan.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daFan_FlowCap[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitCoilClgData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumCoilClgs = (int) pLocRunData->saCoilClg.size();
		if (iNumCoilClgs > 0)
		{	pLocRunData->daCoilClg_TotCap.resize(  iNumCoilClgs, -1.0 );
			pLocRunData->daCoilClg_SensCap.resize( iNumCoilClgs, -1.0 );
	//		pLocRunData->daCoilClg_FluidLdDsgn.resize( iNumCoilClgs, -1.0 );
			pLocRunData->daCoilClg_FluidFlowRtDsgnSim.resize( iNumCoilClgs, -1.0 );
		}
		return iNumCoilClgs;
	}
	return 0;
}

std::string OSWrapLib::GetCoilClgName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saCoilClg.size())
		sName = pLocRunData->saCoilClg[idx];
	return sName;
}


int OSWrapLib::InitCoilHtgData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumCoilHtgs = (int) pLocRunData->saCoilHtg.size();
		if (iNumCoilHtgs > 0)
		{	pLocRunData->daCoilHtg_TotCap.resize( iNumCoilHtgs, -1.0 );
	//		pLocRunData->daCoilHtg_FluidLdDsgn.resize( iNumCoilHtgs, -1.0 );
			pLocRunData->daCoilHlg_FluidFlowRtDsgnSim.resize( iNumCoilHtgs, -1.0 );
		}
		return iNumCoilHtgs;
	}
	return 0;
}

void OSWrapLib::SetCoilClgData( int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saCoilClg.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daCoilClg_TotCap[idx]             = dVal;		break;
			case  1 :	pLocRunData->daCoilClg_SensCap[idx]            = dVal;		break;
			case  2 :	pLocRunData->daCoilClg_FluidFlowRtDsgnSim[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}

std::string OSWrapLib::GetCoilHtgName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saCoilHtg.size())
		sName = pLocRunData->saCoilHtg[idx];
	return sName;
}

void OSWrapLib::SetCoilHtgData( int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saCoilHtg.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daCoilHtg_TotCap[idx]             = dVal;		break;
			case  1 :	pLocRunData->daCoilHlg_FluidFlowRtDsgnSim[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitBlrData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumBoilers = (int) pLocRunData->saBlr.size();
		if (iNumBoilers > 0)
			pLocRunData->daBlr_CapRtd.resize( iNumBoilers, -1.0 );
		return iNumBoilers;
	}
	return 0;
}

std::string OSWrapLib::GetBlrName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saBlr.size())
		sName = pLocRunData->saBlr[idx];
	return sName;
}

void OSWrapLib::SetBlrData(     int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saBlr.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daBlr_CapRtd[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitChlrData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumChillers = (int) pLocRunData->saChlr.size();
		if (iNumChillers > 0)
			pLocRunData->daChlr_CapRtd.resize( iNumChillers, -1.0 );
		return iNumChillers;
	}
	return 0;
}

std::string OSWrapLib::GetChlrName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saChlr.size())
		sName = pLocRunData->saChlr[idx];
	return sName;
}

void OSWrapLib::SetChlrData(    int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saChlr.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daChlr_CapRtd[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitHtRejData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumClgTowers = (int) pLocRunData->saHtRej.size();
		if (iNumClgTowers > 0)
			pLocRunData->daHtRej_CapRtd.resize( iNumClgTowers, -1.0 );
		return iNumClgTowers;
	}
	return 0;
}

std::string OSWrapLib::GetHtRejName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saHtRej.size())
		sName = pLocRunData->saHtRej[idx];
	return sName;
}

void OSWrapLib::SetHtRejData(   int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saHtRej.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daHtRej_CapRtd[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


int OSWrapLib::InitPumpData( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData)
	{	int iNumPumps = (int) pLocRunData->saPump.size();
		if (iNumPumps > 0)
			pLocRunData->daPump_FlowCap.resize( iNumPumps, -1.0 );
		return iNumPumps;
	}
	return 0;
}

std::string OSWrapLib::GetPumpName( int iRunIdx, int idx )
{	std::string sName;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saPump.size())
		sName = pLocRunData->saPump[idx];
	return sName;
}

void OSWrapLib::SetPumpData(    int iRunIdx, int idx, int iDataIdx, double dVal )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData && idx >= 0 && idx < (int) pLocRunData->saPump.size())
		switch (iDataIdx)
		{  case  0 :	pLocRunData->daPump_FlowCap[idx] = dVal;		break;
			default :	OS_ASSERT( false );		break;
		}
}


std::string ParseEnergyPlusTablesForVersionID( std::string sTblOutputPathFile )	// SAC 5/19/14
{
	std::string sRetVal;
	FILE* file = NULL;
	int ErrorCode;
	try
	{
		//file = fopen( pszPathFile, "r" );
		ErrorCode = fopen_s( &file, sTblOutputPathFile.c_str(), "r" );
		if (file)
		{
			char sOutRec[1024];
			int iRecCount = 0;
			while (sRetVal.length() < 1 && ++iRecCount < 20 && fgets( sOutRec, 1024, file ) != NULL)
			{	if (strlen( sOutRec ) > 30)
				{	char* pChrProgVer = strstr( sOutRec, "Program Version:<b>EnergyPlus-" );
					if (pChrProgVer)
					{	char* pChrComma = strchr( pChrProgVer, ',' );
						if (pChrComma)
						{	pChrProgVer += strlen("Program Version:<b>EnergyPlus-");
							int iLen = pChrComma-pChrProgVer;
							if (iLen > 10 && iLen < 40)
							{
								sRetVal.assign( pChrProgVer, (size_t) iLen );
//<p>Program Version:<b>EnergyPlus-Windows-32 8.0.0.008, YMD=2014.05.14 09:27</b></p>
				}	}	}	}
         }
			fclose(file);
		}
	}
//	catch(CException e) {
//		BEMMessageBox( "Unexpected error ..." );
//	}
	catch( ... )
	{	//ASSERT( FALSE );
		//VERIFY( BEMPX_WriteLogFile( "Unknown error ...", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
		//	if (!bSilent)
		//		BEMMessageBox( "Unknown error ..." );
	}
	return sRetVal;
}


//#define  MAX_NUM_QANALPERIODS      12
typedef struct
{
	long	m_iNumQuickAnalysisPeriods;
	std::string  m_sRunPeriodName[         MAX_NUM_QANALPERIODS ];
	int          m_iRunPeriodYrHourOffset[ MAX_NUM_QANALPERIODS ];
} QuickAnalysisRunPeriodInfo;

// SAC 10/28/15 - added iRptFuelUseAs argument
bool ProcessSimulationResults( OSWrapLib* pOSWrap, long& lRetVal, int iRunIdx, boost::optional<openstudio::model::Model> resModel, std::string sProcessingPath,
										/*std::string sSDDXMLFile,*/ std::string sEPlusSubdir, const char* pszRunSubdir, char* pszSQLOutPathFile, int iMaxLenSQLOutPathFile,
										double* pdResults, bool bStoreHourlyResults, bool bWriteHourlyDebugCSV, bool bWriteCustomMetersHourlyCSV,      // SAC 10/04/21
                              const char* pszIDFFile, bool bFirstRunOfGroup, bool bLastRunOfGroup, QuickAnalysisRunPeriodInfo* pQSimRunPeriodInfo,
                              double fResultMult, int iRptFuelUseAs, const char* pszEPlusPath, double dEPlusVerNum, OSWRAP_MSGCALLBACK* pMsgCallback /*=NULL*/ )
{	bool bRetVal = true;

	// kludge until we gain access to the E+ Job
				std::string sEPlusOutputSQLPathFile = sProcessingPath;
				if (pszRunSubdir && strlen( pszRunSubdir ) > 0)
				{	sEPlusOutputSQLPathFile += pszRunSubdir;
					sEPlusOutputSQLPathFile += '\\';
				}
				sEPlusOutputSQLPathFile += sEPlusSubdir;
				sEPlusOutputSQLPathFile += "\\eplusout.sql";
				openstudio::path pathEPlusOutputSQL = openstudio::toPath(sEPlusOutputSQLPathFile);
				double dEPlusVer = (dEPlusVerNum > 0 ? dEPlusVerNum : 0.0);		// SAC 3/1/19
				if (dEPlusVer < 1 && pOSWrap)
					dEPlusVer = pOSWrap->EnergyPlusVersion( pszEPlusPath );
				OS_ASSERT( dEPlusVer > 0 );

				if (!boost::filesystem::exists(pathEPlusOutputSQL))
					lRetVal = (iRunIdx == 0 ? OSWrap_SimSDD_OSSimSQLOutNotFound : OSWrap_SimSDD_OSSimSQL2OutNotFound);  // did not find SQL output
				else if (!resModel)
					lRetVal = (iRunIdx == 0 ? OSWrap_SimSDD_OSModelNotValid : OSWrap_SimSDD_OSModel2NotValid);  // lost track of model
				else
				{
              try {   //VS19

					if (pszSQLOutPathFile && iMaxLenSQLOutPathFile > (int) sEPlusOutputSQLPathFile.length())	// SAC 4/2/13
						strcpy_s( pszSQLOutPathFile, iMaxLenSQLOutPathFile, sEPlusOutputSQLPathFile.c_str() );

#ifdef _DEBUG  //VS19 - SAC 10/14/20
		if (pMsgCallback)
			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, boost::str( boost::format("      inside ProcessSimulationResults() - about to open E+ SQL results file:  %s") % sEPlusOutputSQLPathFile ).c_str(), 0 ); 
#else
      pMsgCallback;  // make sure it is referenced before end of routine
#endif  //VS19

//sqlite3_initialize();   // workaround for sqlite3 bug in OpenStudio - SAC 10/21/20

//					Sleep( 10000 );
#ifdef _DEBUG  //VS19 - SAC 10/21/20
		if (pMsgCallback)
      {
        std::fstream myfile (sEPlusOutputSQLPathFile.c_str(), std::ios::in | std::ios::binary );
        if (myfile.is_open())
        {   char testRead[11];
            myfile.read( testRead, 10 );
            testRead[10] = '\0';
         			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, boost::str( boost::format("      inside ProcessSimulationResults() - E+ SQL file begins:  %s") % testRead ).c_str(), 0 ); 
          myfile.close();
        }
        else
         			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, boost::str( boost::format("      inside ProcessSimulationResults() - E+ SQL file NOT writable:  %s") % pathEPlusOutputSQL ).c_str(), 0 ); 
      }
#endif  //VS19


					openstudio::SqlFile sqlFile(pathEPlusOutputSQL);  //.fullPath);
					//ASSERT_TRUE(sqlFile.connectionOpen());
					//bool bSQLConOpen = sqlFile.connectionOpen();

					resModel->setSqlFile(sqlFile);

					//ModelFixture, FacilityTest
					boost::optional<openstudio::model::Facility> facility = resModel->getOptionalUniqueModelObject<openstudio::model::Facility>();
					// -or-  Facility facility = resModel.getUniqueModelObject<Facility>();
					if (!facility)
					{	lRetVal = (iRunIdx == 0 ? OSWrap_SimSDD_OSFacilityNotValid : OSWrap_SimSDD_OSFacility2NotValid);  // unable to retrieve model::Facility following simulation
               }
					else
					{
			//			// Returns an EndUse object containing all end uses for the simulation.
			//			boost::optional<openstudio::EndUses> endUses = facility->endUses();
			// SAC 1/17/14 - replaced the above line w/ the following to avoid ASSERTs thrown related to summary results set to IP units
			//						code below based on:  openstudiocore\src\utilities\sql\SqlFile_Impl.cpp / boost::optional<EndUses> SqlFile_Impl::endUses() const
						int iNumEndUsesFromTbl = 0;
						openstudio::EndUses endUses;
						for(openstudio::EndUseFuelType fuelType : endUses.fuelTypes()){
			// we don't care what units are reported in this table, since the hourly results are ALWAYS in SI, as the code below assumes...
			//				std::string units = result.getUnitsForFuelType(fuelType);
							for(openstudio::EndUseCategoryType category : endUses.categories()){
								std::string query = "SELECT Value from tabulardatawithstrings where (reportname = 'AnnualBuildingUtilityPerformanceSummary') and (ReportForString = 'Entire Facility') and (TableName = 'End Uses'  ) and (ColumnName ='" + \
			//													fuelType.valueDescription() + "') and (RowName ='" + category.valueDescription() + "') and (Units = '" + units + "')";
																fuelType.valueDescription() + "') and (RowName ='" + category.valueDescription() + "')";

                        boost::optional<double> value = sqlFile.execAndReturnFirstDouble(query);

//                        boost::optional<double> value;
//  try {
//								value = sqlFile.execAndReturnFirstDouble(query);
//			//					OS_ASSERT(value);    ------------>>>  (where assert is thrown)
//  } catch (std::runtime_error& e) {
//		if (pMsgCallback)
//			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, boost::str( boost::format("      inside ProcessSimulationResults() - SQL query threw exception:  %s") % std::string{e.what()} ).c_str(), 0 ); 
////    std::string expectedError("Error creating prepared statement: SELECT * FROM NonExistantTable; with error code 1, extended code 1, errmsg: no such table: NonExistantTable");
////    EXPECT_EQ(expectedError, std::string{e.what()});
//  }

								if (value && *value != 0.0)
								{	iNumEndUsesFromTbl++;
									endUses.addEndUse(*value, fuelType, category);
								}
							}
						}

//						if (endUses)
						if (iNumEndUsesFromTbl > 0)
						{

//  /// Returns the underlying Attribute of the EndUse object.
//  /// Attribute name: endUsesAttribute
//  boost::optional<Attribute> endUsesAttribute() const;

//  endUses.addEndUse(25.0, EndUseFuelType::Gas, EndUseCategoryType::Heating);
//  endUses.addEndUse(2.0, EndUseFuelType::Electricity, EndUseCategoryType::Cooling);
//  endUses.addEndUse(1.0, EndUseFuelType::Electricity, EndUseCategoryType::InteriorLights);
//  endUses.addEndUse(10.0, EndUseFuelType::Electricity, EndUseCategoryType::Fans, "Fan Energy");
//  endUses.addEndUse(10.0, EndUseFuelType::Water, EndUseCategoryType::Humidifier);

							std::vector<openstudio::EndUseFuelType> allFuelTypes = endUses.fuelTypes();
							std::vector<openstudio::EndUseCategoryType> allCategories = endUses.categories();
							std::vector<std::string> subCategories = endUses.subCategories();

							// figure out which fuel types are used
							std::vector<openstudio::EndUseFuelType> fuelTypes;
							for(const openstudio::EndUseFuelType& fuelType : allFuelTypes){
							  if (endUses.getEndUseByFuelType(fuelType) != 0){
							    fuelTypes.push_back(fuelType);
							  }
							}

							// figure out which categories are used
							std::vector<openstudio::EndUseCategoryType> categories;
							for(const openstudio::EndUseCategoryType& category : allCategories){
							  if (endUses.getEndUseByCategory(category) != 0){
							    categories.push_back(category);
							  }
							}

							//EXPECT_EQ(static_cast<unsigned>(3), fuelTypes.size());
							//EXPECT_EQ(static_cast<unsigned>(5), categories.size());
							//EXPECT_EQ(static_cast<unsigned>(2), subCategories.size());

							for(const openstudio::EndUseFuelType& fuelType : fuelTypes){
							  std::string units = endUses.getUnitsForFuelType(fuelType);
							  for(const openstudio::EndUseCategoryType& category : categories){
							    for(const std::string& subCategory : subCategories){
							      double value = endUses.getEndUse(fuelType, category, subCategory);
									if (value != 0.0 && fuelType.value() < 5 && category.value() < 14)
				// SAC 1/17/14 - units -> IP  (enduse totals here ARE effected by IP/SI unit selection)
				//						pdResults[ (fuelType.value() * 14) + category.value() ] = (value * 947.817);				// convert from GJ to kBtu
										pdResults[ (fuelType.value() * 14) + category.value() ] = ( value * fResultMult ) ;		// data already in kBtu
							      // barchart(value, units) ??
							    }
							  }
							}

					// storage of HOURLY RESULTS
							if (bStoreHourlyResults)
							{
								int iFl, iEU;
								if (bFirstRunOfGroup)
									pOSWrap->InitHourlyResults( iRunIdx );		// SAC 4/17/14
								//	for (iFl=0; iFl<3; iFl++)
								//	{	for (iEU=0; iEU<OSWrap_NumEPlusEnduses; iEU++)
								//			pRunData->daHourlyResults[iFl][iEU].resize( 8760, 0.0 );  // Fuel / Enduse
								//	}

										   FILE *dbgFile = NULL;
											char sDbg[512];
											if (bWriteHourlyDebugCSV)
											{	std::string sDbgFN = pszIDFFile;
												sDbgFN = sDbgFN.substr( 0, sDbgFN.rfind('.') );
												sDbgFN += " - HrlyMtr.csv";
											   dbgFile = fopen( sDbgFN.c_str(), "wt" );
											   if (dbgFile)
											   {	sprintf( sDbg, "#,MeterName,EndUseType,SpecificEndUse,FuelType,Frequency\n" );
													fprintf( dbgFile, sDbg );
												}
											}

								int iNumHrlyStreamsRetrieved = 0;
								double daFuelConvert[3] = {	(947.817 / 3412140000),			// G(?)J -> kWh
																		(947.817 / 100000000000),		// G(?)J -> therms
																		(947.817 / 100000000000)   };

						      // for loop over Run Period objects, which is need to retrieve hourly results
								bool bHaveQSimRunPeriods = (pQSimRunPeriodInfo && pQSimRunPeriodInfo->m_iNumQuickAnalysisPeriods > 0);
								for (int iRP=0; iRP < (bHaveQSimRunPeriods ? pQSimRunPeriodInfo->m_iNumQuickAnalysisPeriods : 1); iRP++)
								{
									std::string sRPName;
									if (!bHaveQSimRunPeriods)
									{	openstudio::model::RunPeriod runPeriod = resModel->getUniqueModelObject<openstudio::model::RunPeriod>();
										sRPName = runPeriod.name().get();
									}
									else
										sRPName = pQSimRunPeriodInfo->m_sRunPeriodName[iRP];
									std::transform( sRPName.begin(), sRPName.end(), sRPName.begin(), ::toupper );
									int iYrHourOffset = (!bHaveQSimRunPeriods ? 0 : pQSimRunPeriodInfo->m_iRunPeriodYrHourOffset[iRP]);
									unsigned hr;

									std::string sFreq, sStatus, sEU, sFuel, sSpecEnduse;
									//std::string sEU, sFuel, sFreq, sStatus;
									openstudio::model::OutputMeterVector meters = resModel->getModelObjects<openstudio::model::OutputMeter>();

                           std::vector<std::string> saCustomMtrs;
                           std::vector<int> etaCustomEnduses;
                           std::vector<int> ftaCustomFuels;
                           int iNumCustomMtrs = 0;
									for(const openstudio::model::OutputMeter& chkMeter : meters)      // enable substitution of default meters with custom meter results - SAC 08/05/21 (HtPumpBlr)
                           {
                              std::string sMtrName = chkMeter.name();
  												//if (dbgFile)
  												//{  snprintf( sDbg, 512, ",\"%s\",initial meter checks...\n", sMtrName.c_str() );
  												//   fprintf( dbgFile, sDbg );
                                    //}
                              if (boost::iequals( sMtrName, "Custom Space Heating Electricity"))
                              {  iNumCustomMtrs++;
                                 saCustomMtrs.push_back(     sMtrName );
                                 etaCustomEnduses.push_back(  6 );  // openstudio::EndUseType::Heating );
                                 ftaCustomFuels.push_back(    0 );  // openstudio::FuelType::Electricity );
                              }
                              else if (boost::iequals( sMtrName, "Custom Water Systems Electricity"))
                              {  iNumCustomMtrs++;
                                 saCustomMtrs.push_back(     sMtrName );
                                 etaCustomEnduses.push_back( 11 );  // openstudio::EndUseType::WaterSystems );
                                 ftaCustomFuels.push_back(    0 );  // openstudio::FuelType::Electricity );
                              }
                           }

									for(const openstudio::model::OutputMeter& meter : meters)
									{
										bool bSuccess = false;			sStatus = "unknown";
										iEU = -1;	sEU.erase();		iFl = -1;	sFuel.erase();
				
										sSpecEnduse.erase();
										boost::optional<std::string> soSpecEnduse;  //, soSpecLocation;
										soSpecEnduse   = meter.specificEndUse();         
										if (soSpecEnduse)
											sSpecEnduse = *soSpecEnduse;
										//soSpecLocation = meter.specificInstallLocation();

										//std::string sEU = meter.endUseType();
										boost::optional<openstudio::EndUseType> euType = meter.endUseType();
										boost::optional<openstudio::FuelType> fType = meter.fuelType();
                              std::string sMtrName = meter.name();
										sFreq = meter.reportingFrequency();

                              bool bThisMtrCustom = false;
                              bool bThisMtrReplacedByCustom = false;
                              int iCM;
                              for (iCM=0; (!bThisMtrCustom && iCM < iNumCustomMtrs); iCM++)    // check for this being a custom meter - SAC 08/05/21
                              {  if (boost::iequals( sMtrName, saCustomMtrs.at(iCM).c_str() ))
                                 {  bThisMtrCustom = true;
                                    iEU = etaCustomEnduses[iCM];
                                    iFl = ftaCustomFuels[iCM];    sFuel = "Electricity";
                                    //*euType = (openstudio::EndUseType) etaCustomEnduses[iCM];
                                    //*fType  = (openstudio::FuelType) ftaCustomFuels[iCM];
  												if (dbgFile)
  												{	snprintf( sDbg, 512, ",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",found custom meter...\n", sMtrName.c_str(), pszaEplusEnduses[iEU][0], sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str() );
  													fprintf( dbgFile, sDbg );
                                 }  }
                              }

                              if (!bThisMtrCustom)
										{
                                 if (!euType)
										   	sEU = "enduse uninitialized";
										   else
										   {	//std::string sEU = openstudio::model::OutputMeter::EndUseType(*euType).valueName();
										   	     if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.empty()                                                )   {  iEU =  0;  }  // sEU = "InteriorLights";          iEU =  6;  }
										   	else if (*euType == openstudio::EndUseType::ExteriorLights         && sSpecEnduse.empty()                                                )   {  iEU =  1;  }  // sEU = "ExteriorLights";          iEU = 10;  }
										   	else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.empty()                                                )   {  iEU =  2;  }  // sEU = "InteriorEquipment";       iEU =  7;  }
										   	else if (*euType == openstudio::EndUseType::ExteriorEquipment      && sSpecEnduse.empty()                                                )   {  iEU =  3;  }  // sEU = "ExteriorEquipment";       iEU = 10;  }
										   	else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.empty()                                                )   {  iEU =  4;  }  // sEU = "Fans";                    iEU =  2;  }
										   	else if (*euType == openstudio::EndUseType::Pumps                  && sSpecEnduse.empty()                                                )   {  iEU =  5;  }  // sEU = "Pumps";                   iEU =  4;  }
										   	else if (*euType == openstudio::EndUseType::Heating                && sSpecEnduse.empty()                                                )   {  iEU =  6;  }  // sEU = "Heating";                 iEU =  0;  }
										   	else if (*euType == openstudio::EndUseType::Cooling                && sSpecEnduse.empty()                                                )   {  iEU =  7;  }  // sEU = "Cooling";                 iEU =  1;  }
										   	else if (*euType == openstudio::EndUseType::HeatRejection          && sSpecEnduse.empty()                                                )   {  iEU =  8;  }  // sEU = "HeatRejection";           iEU =  3;  }
										   	else if (*euType == openstudio::EndUseType::Humidifier             && sSpecEnduse.empty()                                                )   {  iEU =  9;  }  // sEU = "Humidifier";              iEU = -1;  }  // ??
										   	else if (*euType == openstudio::EndUseType::HeatRecovery           && sSpecEnduse.empty()                                                )   {  iEU = 10;  }  // sEU = "HeatRecovery";            iEU = -1;  }  // ??
										   	else if (*euType == openstudio::EndUseType::WaterSystems           && sSpecEnduse.empty()                                                )   {  iEU = 11;  }  // sEU = "DHW";                     iEU =  5;  }
										   	else if (*euType == openstudio::EndUseType::Cogeneration           && sSpecEnduse.empty()                                                )   {  iEU = 12;  }  // sEU = "Cogeneration";            iEU = -1;  }  // ??
										   	else if (*euType == openstudio::EndUseType::Refrigeration          && sSpecEnduse.empty()                                                )   {  iEU = 13;  }  // sEU = "Refrigeration";           iEU =  8;  }  // ??
									//	   	else if (*euType == openstudio::EndUseType::Miscellaneous          && sSpecEnduse.empty()                                                )   {  iEU = 14;  }  // sEU = "Miscellaneous";           iEU =  7;  }
										   	else if (*euType == openstudio::EndUseType::HeatingCoils           && sSpecEnduse.empty()                                                )   {  iEU = 14;  }  // sEU = "HeatingCoils";            iEU =  0;  }
										   	else if (*euType == openstudio::EndUseType::CoolingCoils           && sSpecEnduse.empty()                                                )   {  iEU = 15;  }  // sEU = "CoolingCoils";            iEU =  1;  }
										   	else if (*euType == openstudio::EndUseType::Boilers                && sSpecEnduse.empty()                                                )   {  iEU = 16;  }  // sEU = "Boilers";                 iEU =  8;  }  // ??
										   	else if (*euType == openstudio::EndUseType::Baseboard              && sSpecEnduse.empty()                                                )   {  iEU = 17;  }  // sEU = "Baseboard";               iEU =  0;  }
										   	else if (*euType == openstudio::EndUseType::HeatRecoveryForCooling && sSpecEnduse.empty()                                                )   {  iEU = 18;  }  // sEU = "HeatRecoveryForCooling";  iEU =  1;  }  // ??
										   	else if (*euType == openstudio::EndUseType::HeatRecoveryForHeating && sSpecEnduse.empty()                                                )   {  iEU = 19;  }  // sEU = "HeatRecoveryForHeating";  iEU =  0;  }  // ??
										   	else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+1][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+1;  }  // sEU = "InteriorLights",     "ComplianceLtg"        iEU =  6;  }	// SAC 11/7/15 - 'Reg Ltg' -> 'ComplianceLtg' (SF tic 544)       
										   	else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+2][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+2;  }  // sEU = "InteriorLights",     "NonComplianceLtg"     iEU =  6;  }	// SAC 11/7/15 - 'NonReg Ltg' -> 'NonComplianceLtg' (SF tic 544) 
										   	else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+3][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+3;  }  // sEU = "InteriorEquipment",  "Receptacle"           iEU =  6;  }
										   	else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+4][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+4;  }  // sEU = "InteriorEquipment",  "Process"              iEU =  6;  }
										   	else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+5][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+5;  }  // sEU = "InteriorEquipment",  "Refrig"               iEU =  6;  }
										   	else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+6][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+6;  }  // sEU = "InteriorEquipment",  "Internal Transport"   iEU =  6;  }
										   	else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+7][1])==0)   {  iEU = HrlyEUs_LastUniqueEU+7;  }  // sEU = "Fans",               "ProcessMotors"    iEU = ;  }  // SAC 1/30/17  // SAC 8/14/17
										   	else  {	sEU = "not found";		}		//		ASSERT( FALSE );     }	//	sEU = "<unknown_EndUseType>";		ASSERT( FALSE );		}
                                 }

										   if (!fType)
										   	sFuel = "fuel uninitialized";
										   else
										   {	//std::string sFuel;  // = openstudio::model::OutputMeter::FuelType(*fType).valueName();
										   	     if (*fType == openstudio::FuelType::Electricity    )   {  iFl =  0;   sFuel = "Electricity";      }  
										   	else if (*fType == openstudio::FuelType::Gas            )   {  iFl = (iRptFuelUseAs < 0 ? 1 : iRptFuelUseAs);   sFuel = "Gas";              }	// SAC 10/28/15 - iRptFuelUseAs
										   	else if (*fType == openstudio::FuelType::Gasoline       )   {  iFl = (iRptFuelUseAs < 0 ? 2 : iRptFuelUseAs);   sFuel = "Gasoline";         }   
										   	else if (*fType == openstudio::FuelType::Diesel         )   {  iFl = (iRptFuelUseAs < 0 ? 2 : iRptFuelUseAs);   sFuel = "Diesel";           }   
										   	else if (*fType == openstudio::FuelType::FuelOil_1      )   {  iFl = (iRptFuelUseAs < 0 ? 2 : iRptFuelUseAs);   sFuel = "FuelOil_1";        }   
										   	else if (*fType == openstudio::FuelType::FuelOil_2      )   {  iFl = (iRptFuelUseAs < 0 ? 2 : iRptFuelUseAs);   sFuel = "FuelOil_2";        }   
										   	else if (*fType == openstudio::FuelType::Propane        )   {  iFl = (iRptFuelUseAs < 0 ? 2 : iRptFuelUseAs);   sFuel = "Propane";          }   
										   	else if (*fType == openstudio::FuelType::Water          )   {  iFl = -1;   sFuel = "Water";            }  // ??
										   	else if (*fType == openstudio::FuelType::Steam          )   {  iFl = -1;   sFuel = "Steam";            }  // ??
										   	else if (*fType == openstudio::FuelType::DistrictCooling)   {  iFl = -1;   sFuel = "DistrictCooling";  }  // ??
										   	else if (*fType == openstudio::FuelType::DistrictHeating)   {  iFl = -1;   sFuel = "DistrictHeating";  }  // ??
										   	else if (*fType == openstudio::FuelType::EnergyTransfer )   {  iFl = -1;   sFuel = "EnergyTransfer";   }  // ??
										   	else  {	sFuel = "not found";		}		//		ASSERT( FALSE );     }	//	sFuel = "<unknown_FuelType>";			ASSERT( FALSE );		}
										   }

                                 for (iCM=0; (!bThisMtrReplacedByCustom && iCM < iNumCustomMtrs); iCM++)    // check for this being a meter REPLACED by a custom meter - SAC 08/05/21
                                    if (iEU == etaCustomEnduses[iCM] && iFl == ftaCustomFuels[iCM])
                                    {  bThisMtrReplacedByCustom = true;
   												if (dbgFile)
   												{	snprintf( sDbg, 512, ",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",found meter being replaced by custom mtr...\n", sMtrName.c_str(), (sEU.size() > 0 ? sEU.c_str() : pszaEplusEnduses[iEU][0]), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str() );
   													fprintf( dbgFile, sDbg );
                                    }  }
                              }

										double dEUTot=0.0;
										if (iFl >= 0 && iEU >= 0 && boost::iequals( sFreq, "hourly"))
										{
											boost::optional<openstudio::TimeSeries> timeSeries = meter.getData( sRPName );  // runPeriod.name().get());
											if (timeSeries)
											{
												openstudio::Vector values = timeSeries->values();
												unsigned numValues = (unsigned) values.size();
												//ASSERT( numValues==0 || numValues==8760 );
												if (numValues > 0 && (numValues + iYrHourOffset) <= 8760)		// numValues == 8760)
												{
													//dEUTot=0.0;
													for (hr = 0; hr < numValues; ++hr)
													{
														if (!bThisMtrReplacedByCustom)
                                             pOSWrap->SumIntoHourlyResult( iRunIdx, iFl, iEU, (hr + iYrHourOffset), (values(hr) * fResultMult) );
														//pRunData->daHourlyResults[iFl][iEU][hr] += values(hr);
														dEUTot += (values(hr) * fResultMult);
													}

													sStatus = "success";
                                       if (bThisMtrReplacedByCustom)
                                          sStatus += " (replaced by custom mtr)";
													bSuccess = true;
													iNumHrlyStreamsRetrieved++;
												}
												else
												{	//ASSERT( FALSE );
													sStatus = boost::str( boost::format("NumHrlyVals = %d") % numValues );
												}
											}
											else
												sStatus = "error retrieving TimeSeries";
										}

                              //else if (boost::iequals( sFreq, "hourly"))     // DEBUGGING - retrieve results regardless of iFl & iEU settings - SAC 08/05/21
                              //{
										//	boost::optional<openstudio::TimeSeries> timeSeries = meter.getData( sRPName );  // runPeriod.name().get());
										//	if (timeSeries)
                              //   {
										//		openstudio::Vector values = timeSeries->values();
										//		unsigned numValues = (unsigned) values.size();
										//		if (numValues > 0 && (numValues + iYrHourOffset) <= 8760)		// numValues == 8760)
										//		{
										//			for (hr = 0; hr < numValues; ++hr)
										//			{
										//			//	pOSWrap->SumIntoHourlyResult( iRunIdx, iFl, iEU, (hr + iYrHourOffset), (values(hr) * fResultMult) );
										//				dEUTot += (values(hr) * fResultMult);
										//			}
										//			sStatus = "success (unknown enduse or fuel)";
										//			bSuccess = true;
										//			iNumHrlyStreamsRetrieved++;
										//		}
										//		else
										//		{	//ASSERT( FALSE );
										//			sStatus = boost::str( boost::format("NumHrlyVals = %d") % numValues );
										//		}
                              //   }
                              //}

												if (dbgFile)
												{	if (bSuccess)
														snprintf( sDbg, 512, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%s,%g\n", iNumHrlyStreamsRetrieved, sMtrName.c_str(), (sEU.size() > 0 ? sEU.c_str() : pszaEplusEnduses[iEU][0]), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str(), dEUTot );
													else
														snprintf( sDbg, 512, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%s\n"   , iNumHrlyStreamsRetrieved, sMtrName.c_str(), (sEU.size() > 0 ? sEU.c_str() : pszaEplusEnduses[iEU][0]), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str() );
													//							(sSpecEnduse ? sSpecEnduse->c_str() : ""), (sSpecLocation ? sSpecLocation->c_str() : "") );
													fprintf( dbgFile, sDbg );
												}
									}
								}	// end of for() loop over Run Periods

								if (iNumHrlyStreamsRetrieved < 1)
								{	//ASSERT( FALSE );
								}
								else
								{	if (bLastRunOfGroup)
										pOSWrap->AdjustAndSumHourlyResults( iRunIdx, daFuelConvert );
									//	pRunData->bHourlyResultsCurrent = true;
									//	for (iFl=0; iFl<3; iFl++)
									//		for (iEU=0; iEU<OSWrap_NumEPlusEnduses; iEU++)
									//		{	pRunData->daHourlyResultsSum[iFl][iEU] = 0.0;
									//			for (hr=0; hr<8760; hr++)
									//			{	pRunData->daHourlyResults[   iFl][iEU][hr] *= daFuelConvert[iFl];
									//				pRunData->daHourlyResultsSum[iFl][iEU]     += pRunData->daHourlyResults[iFl][iEU][hr];
									//			}
									//		}
								}

											   if (dbgFile)
											   {  fflush( dbgFile );
											      fclose( dbgFile );
											   }


            						//		for(const openstudio::EndUseFuelType& fuelType : fuelTypes){
            						//		  std::string units = endUses.getUnitsForFuelType(fuelType);
            						//		  for(const openstudio::EndUseCategoryType& category : categories){
            						//		    for(const std::string& subCategory : subCategories)
            						//			 {
            						//		      double value = endUses.getEndUse(fuelType, category, subCategory);
            						//				if (value != 0.0 && fuelType.value() < 5 && category.value() < 14)
            						//					pdResults[ (fuelType.value() * 14) + category.value() ] = (value * 947.817);   // convert from GJ to kBtu
            						//		      // barchart(value, units) ??
            						//		    }
            						//		  }
            						//		}


                        // storage of custom meter hourly CSV export - SAC 09/29/21
                        if (bWriteCustomMetersHourlyCSV &&
                            (pQSimRunPeriodInfo==NULL || pQSimRunPeriodInfo->m_iNumQuickAnalysisPeriods < 1))
                        {
									openstudio::model::RunPeriod runPeriod = resModel->getUniqueModelObject<openstudio::model::RunPeriod>();
									std::string sRPName = runPeriod.name().get();
									std::transform( sRPName.begin(), sRPName.end(), sRPName.begin(), ::toupper );

   								double daExpFuelConvert[] = {	(947.817 / 3412140000),		// J -> kWh
      																	(947.817 / 1000000000)	};	// J -> kBtu
                           const char* pszCustMtrFuelLbls[] = { "(kWh),", "(kBtu)," };

#define NumCustMeters  6
                           const char* pszCustMtrColLbls[] = { "Nonresidential Electricity,,,,,,,,,,", "Residential Electricity,,,,,,,,,,", "Mixed Electricty,,,,,,,,,,", "Nonresidential Gas,,,,,", "Residential Gas,,,,,", "Mixed Gas,,,,,"      };
                           const char* pszCustMtrNames[]   = { "NONRESELECMETER"           , "RESELECMETER"           , "MIXEDELECMETER"  , "NONRESGASMETER"    , "RESGASMETER"    , "MIXEDGASMETER"  };
                           int iaCustMtrFuelIdx[]          = {         0                   ,      0                   ,        0          ,        1            ,     1            ,       1          };
                           int iaFirstCustMtrColIdx[]      = {        -1                   ,     -1                   ,       -1          ,       -1            ,    -1            ,      -1          };  // set during processing
#define NumCustMtrEnduses     8
#define NumCustGasMtrEnduses  3
                           const char* pszMtrEUColLbls[]   = { "Spc Heat,", "Spc Cool,", "Indr Fans,", "Heat Rej,", "Pump&Misc,", "Dom HW,", "Lighting,", "Process,", "Comp Tot,", "TOTAL,"      };
                           const char* pszMtrEnduseNames[] = { "SPCHEAT"  , "SPCCOOL"  , "INDRFANS"  , "HEATREJ"  , "PUMPMISC"  , "DOMHW"  , "LIGHTING" , "PROCESS"  };
                           int iaMtrGasUseIdx[]            = {     0      ,    -1      ,    -1       ,    -1      ,    -1       ,     1    ,    -1      ,     2      };
                           bool baComplianceEnduse[]       = {   true     ,   true     ,   true      ,   true     ,   true      ,   true   ,   true     ,   false    };

                           //double daCustMtrHrlyRes[              (3*(NumCustMtrEnduses+2)) + (3*(NumCustGasMtrEnduses+2)) ][8760];
                           int iMtr, iTotNumCustMtrHrlyResCols = (3*(NumCustMtrEnduses+2)) + (3*(NumCustGasMtrEnduses+2));
                           double* dpCustMtrHrlyRes = (double*) malloc( (iTotNumCustMtrHrlyResCols * 8760 * sizeof(double)) );

                                    //std::string sDbg2 = boost::str( boost::format("iTotNumCustMtrHrlyResCols = %d") % iTotNumCustMtrHrlyResCols );
                                    //if (pMsgCallback)
                                    //   pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, sDbg2.c_str(), 0 ); 

                           for (iMtr=0; iMtr < iTotNumCustMtrHrlyResCols; iMtr++)
                           {  for (unsigned hr=0; hr<8760; hr++)
                                 //daCustMtrHrlyRes[ iMtr ][hr] = 0.0;
                                 dpCustMtrHrlyRes[ (iMtr*8760)+hr ] = 0.0;
                           }
                           bool bAbortCustMtrExport = false;
                           int iCurExportDataColIdx = 0, iNumCustMtrHrlyStreamsRetrieved = 0;
                           for (iMtr=0; (!bAbortCustMtrExport && iMtr < NumCustMeters); iMtr++)
                           {
                              int iCompTotEUColIdx = (iaCustMtrFuelIdx[iMtr] == 0 ? NumCustMtrEnduses : NumCustGasMtrEnduses);
                              int iDataColIdx = -1;
                              for (int iEnduse=0; (!bAbortCustMtrExport && iEnduse < NumCustMtrEnduses); iEnduse++)
                              {  int iEUColIdx = (iaCustMtrFuelIdx[iMtr] == 0 ? iEnduse : iaMtrGasUseIdx[iEnduse]);
                                 if (iEUColIdx >= 0)
                                 {
         									std::string sMtrName, sStatus;
                                    sMtrName = boost::str( boost::format("%s:%s") % pszCustMtrNames[iMtr] % pszMtrEnduseNames[iEnduse]);
         									double dVal, dEUTot=0.0;
                                    int iNumValues=0;
                                          //sStatus = boost::str( boost::format("attempting to retrieve horuly results for '%s' (%d col idx)") % sMtrName.c_str() % iDataColIdx );
                     					boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sRPName, "Hourly", sMtrName.c_str(), "" );
                     					if (timeSeries)
         									{
                                       if (iaFirstCustMtrColIdx[iMtr] < 0)
                                          iaFirstCustMtrColIdx[iMtr] = iCurExportDataColIdx;
                                       iDataColIdx = iaFirstCustMtrColIdx[iMtr] + iEUColIdx;
         										openstudio::Vector values = timeSeries->values();
         										unsigned numValues = (unsigned) values.size();
                                       iNumValues = (int) numValues;
         										if (numValues > 0 && numValues <= 8760)		// numValues == 8760)
         										{
         											for (unsigned hr = 0; hr < numValues; ++hr)
         											{
                                             dVal = (values(hr) * daExpFuelConvert[iaCustMtrFuelIdx[iMtr]] * fResultMult);
                                             dEUTot += dVal;
                                             dpCustMtrHrlyRes[ (iDataColIdx*8760)+hr ] = dVal;
                                             if (baComplianceEnduse[iEnduse])
                                                dpCustMtrHrlyRes[(iaFirstCustMtrColIdx[iMtr]+iCompTotEUColIdx  )*8760+hr] += dVal;   // CompTotal
                                             dpCustMtrHrlyRes[   (iaFirstCustMtrColIdx[iMtr]+iCompTotEUColIdx+1)*8760+hr] += dVal;   // TOTAL

                                             //daTempHrlyRes[hr] = (values(hr) * daExpFuelConvert[iaCustMtrFuelIdx[iMtr]] * fResultMult);
         												//dEUTot += daTempHrlyRes[hr];

                                             //daCustMtrHrlyRes[iDataColIdx][hr] = dVal;
                                             //daCustMtrHrlyRes[iDataColIdx][0] = dVal;
         												//dEUTot += (values(hr) * daExpFuelConvert[iaCustMtrFuelIdx[iMtr]] * fResultMult);
                                             //if (baComplianceEnduse[iEnduse])
                                             //   daCustMtrHrlyRes[iaFirstCustMtrColIdx[iMtr]+iCompTotEUColIdx  ][hr] += daCustMtrHrlyRes[iDataColIdx][hr];   // CompTotal
                                             //daCustMtrHrlyRes[   iaFirstCustMtrColIdx[iMtr]+iCompTotEUColIdx+1][hr] += daCustMtrHrlyRes[iDataColIdx][hr];   // TOTAL
         											}
         											sStatus = boost::str( boost::format("success - '%s' (%d values, %d col idx) annual use = %g") % sMtrName.c_str() % numValues % iDataColIdx % dEUTot );
         											iNumCustMtrHrlyStreamsRetrieved++;
         										}
         										else
         											sStatus = boost::str( boost::format("TimeSeries '%s' NumHrlyVals = %d") % sMtrName.c_str() % numValues );
         									}
         									else
         										sStatus = boost::str( boost::format("   TimeSeries not found for meter '%s'") % sMtrName.c_str() );

                              		if (pMsgCallback)
                              			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, sStatus.c_str(), 0 ); 
                                 }
                              }
                              if (iDataColIdx >= 0)
                                 iCurExportDataColIdx += (iCompTotEUColIdx+2);
                           }

                           if (iNumCustMtrHrlyStreamsRetrieved > 0 && !bAbortCustMtrExport)
                           {  // EXPORT CSV FILE

                                 std::string sCustMtrErr, sCustMtrCSVFN = pszIDFFile;
											sCustMtrCSVFN = sCustMtrCSVFN.substr( 0, sCustMtrCSVFN.rfind('.') );
											sCustMtrCSVFN += " - HrlyCustomMtrResults.csv";
                              	FILE *fp_CMCSV;
                           		int iErrorCode;
                           		try
                           		{  iErrorCode = fopen_s( &fp_CMCSV, sCustMtrCSVFN.c_str(), "wb" );
                           			if (iErrorCode != 0 || fp_CMCSV == NULL)
                           			{	//iRetVal = 3;
                           				sCustMtrErr = boost::str( boost::format( "Error encountered opening custom meter hourly CSV results file:  %s") % sCustMtrCSVFN );
                           			}
                           			else
                           			{  char pszMtrRec[1024];
                           			   fprintf( fp_CMCSV, "7,4,Row/Col hourly results data begin\n" );
                           			   fprintf( fp_CMCSV, "\"Hourly CustomMeter Results For Nonresidential, Residential, and Mixed Systems\"\n" );
                           			   fprintf( fp_CMCSV, "\n" );

                                       strcpy_s( pszMtrRec, 1024, ",,," );
                                       for (iMtr=0; (!bAbortCustMtrExport && iMtr < NumCustMeters); iMtr++)
                                       {  if (iaFirstCustMtrColIdx[iMtr] >= 0)
                                             strcat_s( pszMtrRec, 1024, pszCustMtrColLbls[iMtr] );
                                       }  strcat_s( pszMtrRec, 1024, "\n" );
                           			   fprintf( fp_CMCSV, pszMtrRec );

                                       strcpy_s( pszMtrRec, 1024, ",,," );
                                       for (iMtr=0; (!bAbortCustMtrExport && iMtr < NumCustMeters); iMtr++)
                                       {  if (iaFirstCustMtrColIdx[iMtr] >= 0)
                                          {  for (int iEnduse=0; (!bAbortCustMtrExport && iEnduse < (NumCustMtrEnduses+2)); iEnduse++)
                                             {  if (iEnduse >= NumCustMtrEnduses || iaCustMtrFuelIdx[iMtr] == 0 || iaMtrGasUseIdx[iEnduse] >= 0)
                                                   strcat_s( pszMtrRec, 1024, pszMtrEUColLbls[iEnduse] );
                                          }  }
                                       }  strcat_s( pszMtrRec, 1024, "\n" );
                           			   fprintf( fp_CMCSV, pszMtrRec );

                                       strcpy_s( pszMtrRec, 1024, "Mo,Da,Hr," );
                                       for (iMtr=0; (!bAbortCustMtrExport && iMtr < NumCustMeters); iMtr++)
                                       {  if (iaFirstCustMtrColIdx[iMtr] >= 0)
                                          {  for (int iEnduse=0; (!bAbortCustMtrExport && iEnduse < (NumCustMtrEnduses+2)); iEnduse++)
                                             {  if (iEnduse >= NumCustMtrEnduses || iaCustMtrFuelIdx[iMtr] == 0 || iaMtrGasUseIdx[iEnduse] >= 0)
                                                   strcat_s( pszMtrRec, 1024, pszCustMtrFuelLbls[ iaCustMtrFuelIdx[iMtr] ] );
                                          }  }
                                       }  strcat_s( pszMtrRec, 1024, "\n" );
                           			   fprintf( fp_CMCSV, pszMtrRec );

                                       char pszVal[32];
                                       int iNumDaysInMonth[12] = {  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };
                        					int iYrHr = -1;
                        					int iMo, iDa, iHr;
                        					for (iMo=1; iMo<13; iMo++)
                        						for (iDa=1; iDa <= iNumDaysInMonth[iMo-1]; iDa++)
                        							for (iHr=1; iHr<25; iHr++)
                        							{	iYrHr++;
                                                sprintf_s( pszMtrRec, 1024, "%d,%d,%d,", iMo, iDa, iHr );
                                                for (long lCol=0; lCol<iCurExportDataColIdx; lCol++)
                                                {  sprintf_s( pszVal, 32, "%g,", dpCustMtrHrlyRes[(lCol*8760)+iYrHr] );
                                                   strcat_s( pszMtrRec, 1022, pszVal );
                                                }
                                                strcat_s( pszMtrRec, 1024, "\n" );
                                       			fprintf( fp_CMCSV, pszMtrRec );
                                             }
                           				fflush( fp_CMCSV );
                           				fclose( fp_CMCSV );
                           			}
                           		}
                           		catch( ... )
                           		{	//iRetVal = 4;
                           			sCustMtrErr = boost::str( boost::format( "Unknown error writing hourly CSV results file header:  %s") % sCustMtrCSVFN );
                           		}
                                 if (sCustMtrErr.length() > 0 && pMsgCallback)
                                    pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, sCustMtrErr.c_str(), 0 ); 
                           }
                           else
                           {	if (pMsgCallback)
                           		pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, "error exporting custom meter hourly results CSV - no hourly results retrieved", 0 ); 
                           }

                           if (dpCustMtrHrlyRes)
                              free( dpCustMtrHrlyRes );


                           //const char* pszCustMtrNamesTest[] = { "NONRESELECMETER:LIGHTING", "NONRESELECMETER:PROCESS", NULL };
                           //int iaExpFuelIdx[]            = {         0                       ,            0                          };
                           //int iCustMtrIdx = -1;
                           //while (pszCustMtrNamesTest[++iCustMtrIdx])
                           //{
   								//	std::string sStatus;
   								//	double dEUTot=0.0;
               				//	boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sRPName, "Hourly", pszCustMtrNamesTest[iCustMtrIdx], "" );
               				//	if (timeSeries)
   								//	{
   								//		openstudio::Vector values = timeSeries->values();
   								//		unsigned numValues = (unsigned) values.size();
   								//		//ASSERT( numValues==0 || numValues==8760 );
   								//		if (numValues > 0 && numValues <= 8760)		// numValues == 8760)
   								//		{
   								//			//dEUTot=0.0;
   								//			for (unsigned hr = 0; hr < numValues; ++hr)
   								//			{
   								//				//if (!bThisMtrReplacedByCustom)
                           //            //   pOSWrap->SumIntoHourlyResult( iRunIdx, iFl, iEU, (hr + iYrHourOffset), (values(hr) * fResultMult) );
   								//				dEUTot += (values(hr) * daExpFuelConvert[iaExpFuelIdx[iCustMtrIdx]] * fResultMult);
   								//			}
   								//			sStatus = boost::str( boost::format("success - '%s' annual use = %g") % pszCustMtrNamesTest[iCustMtrIdx] % dEUTot );
   								//			//bSuccess = true;
   								//			//iNumHrlyStreamsRetrieved++;
   								//		}
   								//		else
   								//		{	//ASSERT( FALSE );
   								//			sStatus = boost::str( boost::format("TimeSeries '%s' NumHrlyVals = %d") % pszCustMtrNamesTest[iCustMtrIdx] % numValues );
   								//		}
   								//	}
   								//	else
   								//		sStatus = boost::str( boost::format("error retrieving TimeSeries '%s'") % pszCustMtrNamesTest[iCustMtrIdx] );;
                        	//	if (pMsgCallback)
                        	//		pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, sStatus.c_str(), 0 ); 
                           //}
                        }  // end of:  storage of custom meter hourly CSV export - SAC 09/29/21
							}	// end of:  if (pRunData && bStoreHourlyResults)

						}


						//boost::optional<SqlFile> sqlFile = openstudio::model::Model::sqlFile();

// Retrieve unmet zone load hours --
						//ASSERT( pRunData );
						//if (pRunData)
						{	int iObj;
							std::string sObj, s;

							int iNumZones = pOSWrap->InitZoneData( iRunIdx );;
						//	int iNumZones = (int) pRunData->saZone.size();
							if (iNumZones > 0)
							{
						//		pRunData->daZone_UMLHClg.resize( iNumZones, -1.0 );
						//		pRunData->daZone_UMLHHtg.resize( iNumZones, -1.0 );
                  //		pRunData->daZone_ClgDsgnLd.resize( iNumZones, -1.0 );
                  //		pRunData->daZone_HtgDsgnLd.resize( iNumZones, -1.0 );
                  //		pRunData->daZone_ClgDsgnFlow.resize( iNumZones, -1.0 );
                  //		pRunData->daZone_HtgDsgnFlow.resize( iNumZones, -1.0 );

//	bool bFirstRunOfGroup, bool bLastRunOfGroup, int iYrHourOffset, double fResultMult )
								for (iObj=0; iObj < iNumZones; iObj++)
								{
									sObj = pOSWrap->GetZoneName( iRunIdx, iObj );
							//		sObj = pRunData->saZone[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{
									//{	std::string s = "SELECT Value FROM tabulardatawithstrings WHERE "
									//	                "ReportName='SystemSummary' AND "
									//	                "ReportForString='Entire Facility' AND "
									//	                "TableName='Time Setpoint Not Met' AND "
									//	                "RowName='";
									//	s += sObj;
									//	s += "' AND "
									//	                "ColumnName='During Occupied Cooling' AND "
									//	                "Units='hr'";  
									//	if ( boost::optional<double> unmetHrsClg = sqlFile.execAndReturnFirstDouble(s) )
							//			boost::optional<double> unmetHrsClg = sqlFile.execAndReturnFirstDouble("SELECT Value FROM TabularDataWithStrings WHERE (ReportName='SystemSummary') AND (ReportForString='Entire Facility') AND (TableName='Time Setpoint Not Met') AND (RowName = 'COMMON_CORRIDOR_ZN') AND (ColumnName='During Heating') AND (Units = 'hr')");
										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='SystemSummary') AND (ReportForString='Entire Facility') AND (TableName='Time Setpoint Not Met') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP  (no change)
										s += "') AND (ColumnName='During Occupied Cooling') AND (Units = 'hr')";
										boost::optional<double> unmetHrsClg = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 0, (unmetHrsClg ? *unmetHrsClg : 0.0) );
								//		pRunData->daZone_UMLHClg[iObj] = (unmetHrsClg ? *unmetHrsClg : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='SystemSummary') AND (ReportForString='Entire Facility') AND (TableName='Time Setpoint Not Met') AND (RowName='";
										s += sObj;
					// SAC 1/11/14 - units -> IP  (no change)
										s += "') AND (ColumnName='During Occupied Heating') AND (Units='hr')";  
										boost::optional<double> unmetHrsHtg = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 1, (unmetHrsHtg ? *unmetHrsHtg : 0.0) );
								//		pRunData->daZone_UMLHHtg[iObj] = (unmetHrsHtg ? *unmetHrsHtg : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='HVACSizingSummary') AND (ReportForString='Entire Facility') AND (TableName='";
										s += (dEPlusVer >= 8.5 ? "Zone Sensible Cooling" : "Zone Cooling");	// SAC 4/20/16
										s += "') AND (RowName='";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Calculated Design Load') AND (Units='W')";  
										s += "') AND (ColumnName='Calculated Design Load') AND (Units='Btu/h')";  
										boost::optional<double> clgDsgnLd = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 2, (clgDsgnLd ? *clgDsgnLd : 0.0) );
								//		pRunData->daZone_ClgDsgnLd[iObj] = (clgDsgnLd ? *clgDsgnLd : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='HVACSizingSummary') AND (ReportForString='Entire Facility') AND (TableName='";
										s += (dEPlusVer >= 8.5 ? "Zone Sensible Heating" : "Zone Heating");	// SAC 4/20/16
										s += "') AND (RowName='";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Calculated Design Load') AND (Units='W')";  
										s += "') AND (ColumnName='Calculated Design Load') AND (Units='Btu/h')";  
										boost::optional<double> htgDsgnLd = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 3, (htgDsgnLd ? *htgDsgnLd : 0.0) );
								//		pRunData->daZone_HtgDsgnLd[iObj] = (htgDsgnLd ? *htgDsgnLd : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='HVACSizingSummary') AND (ReportForString='Entire Facility') AND (TableName='";
										s += (dEPlusVer >= 8.5 ? "Zone Sensible Cooling" : "Zone Cooling");	// SAC 4/20/16
										s += "') AND (RowName='";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Calculated Design Air Flow') AND (Units='m3/s')";  
										s += "') AND (ColumnName='Calculated Design Air Flow') AND (Units='ft3/min')";  
										boost::optional<double> clgDsgnFlow = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 4, (clgDsgnFlow ? *clgDsgnFlow : 0.0) );
								//		pRunData->daZone_ClgDsgnFlow[iObj] = (clgDsgnFlow ? *clgDsgnFlow : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='HVACSizingSummary') AND (ReportForString='Entire Facility') AND (TableName='";
										s += (dEPlusVer >= 8.5 ? "Zone Sensible Heating" : "Zone Heating");	// SAC 4/20/16
										s += "') AND (RowName='";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Calculated Design Air Flow') AND (Units='m3/s')";  
										s += "') AND (ColumnName='Calculated Design Air Flow') AND (Units='ft3/min')";  
										boost::optional<double> htgDsgnFlow = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetZoneData( iRunIdx, iObj, 5, (htgDsgnFlow ? *htgDsgnFlow : 0.0) );
								//		pRunData->daZone_HtgDsgnFlow[iObj] = (htgDsgnFlow ? *htgDsgnFlow : 0.0);
									}
								}
							}

							int iNumFans = pOSWrap->InitFanData( iRunIdx );		// (int) pRunData->saFan.size();
							if (iNumFans > 0)
							{	//pRunData->daFan_FlowCap.resize( iNumFans, -1.0 );
								for (iObj=0; iObj < iNumFans; iObj++)
								{	sObj = pOSWrap->GetFanName(  iRunIdx, iObj );		// pRunData->saFan[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{	s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Fans') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Max Air Flow Rate') AND (Units = 'm3/s')";
										s += "') AND (ColumnName='Max Air Flow Rate') AND (Units = 'ft3/min')";
										boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetFanData(     iRunIdx, iObj, 0, (data ? *data : 0.0) );     // pRunData->daFan_FlowCap[iObj] = (data ? *data : 0.0);
									}
								}
							}

							int iNumCoilClgs = pOSWrap->InitCoilClgData( iRunIdx );		// (int) pRunData->saCoilClg.size();
							if (iNumCoilClgs > 0)
							{	//pRunData->daCoilClg_TotCap.resize(  iNumCoilClgs, -1.0 );
								//pRunData->daCoilClg_SensCap.resize( iNumCoilClgs, -1.0 );
	//							//pRunData->daCoilClg_FluidLdDsgn.resize( iNumCoilClgs, -1.0 );
								//pRunData->daCoilClg_FluidFlowRtDsgnSim.resize( iNumCoilClgs, -1.0 );
								for (iObj=0; iObj < iNumCoilClgs; iObj++)
								{	sObj = pOSWrap->GetCoilClgName(  iRunIdx, iObj );		// pRunData->saCoilClg[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{	s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Cooling Coils') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Nominal Total Capacity') AND (Units = 'W')";
										s += "') AND (ColumnName='Nominal Total Capacity') AND (Units = 'Btu/h')";
										boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetCoilClgData( iRunIdx, iObj, 0, (data ? *data : 0.0) );      // pRunData->daCoilClg_TotCap[iObj] = (data ? *data : 0.0);

										s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Cooling Coils') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Nominal Sensible Capacity') AND (Units = 'W')";
										s += "') AND (ColumnName='Nominal Sensible Capacity') AND (Units = 'Btu/h')";
										boost::optional<double> data2 = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetCoilClgData( iRunIdx, iObj, 1, (data2 ? *data2 : 0.0) );      // pRunData->daCoilClg_SensCap[iObj] = (data2 ? *data2 : 0.0);

	//									s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Cooling Coils') AND (RowName = '";
	//									s += sObj;
	//									s += "') AND (ColumnName='Design Coil Load') AND (Units = 'W')";
	//									boost::optional<double> data3 = sqlFile.execAndReturnFirstDouble(s);
	//									pRunData->daCoilClg_FluidLdDsgn[iObj] = (data3 ? *data3 : 0.0);
				// ComponentSizes will ALWAYS be written in SI units
										s = "SELECT Value FROM ComponentSizes WHERE (CompType='Coil:Cooling:Water') AND (CompName = '";
										s += sObj;
							// SAC 6/10/14 - updated for EnergyPlus v8.1
							//			s += "') AND (Description='Design Water Flow Rate') AND (Units = 'm3/s')";
										s += "') AND (Description='Design Size Design Water Flow Rate') AND (Units = 'm3/s')";
										boost::optional<double> data3 = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetCoilClgData( iRunIdx, iObj, 2, (data3 ? *data3 : 0.0) );      // pRunData->daCoilClg_FluidFlowRtDsgnSim[iObj] = (data3 ? *data3 : 0.0);
									}
								}
							}

							int iNumCoilHtgs = pOSWrap->InitCoilHtgData( iRunIdx );		// (int) pRunData->saCoilHtg.size();
							if (iNumCoilHtgs > 0)
							{	//pRunData->daCoilHtg_TotCap.resize( iNumCoilHtgs, -1.0 );
	//							//pRunData->daCoilHtg_FluidLdDsgn.resize( iNumCoilHtgs, -1.0 );
								//pRunData->daCoilHlg_FluidFlowRtDsgnSim.resize( iNumCoilHtgs, -1.0 );
								for (iObj=0; iObj < iNumCoilHtgs; iObj++)
								{
									sObj = pOSWrap->GetCoilHtgName(  iRunIdx, iObj );		// pRunData->saCoilHtg[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{	s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Heating Coils') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Nominal Total Capacity') AND (Units = 'W')";
										s += "') AND (ColumnName='Nominal Total Capacity') AND (Units = 'Btu/h')";
										boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetCoilHtgData( iRunIdx, iObj, 0, (data ? *data : 0.0) );		// pRunData->daCoilHtg_TotCap[iObj] = (data ? *data : 0.0);

	//									s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Heating Coils') AND (RowName = '";
	//									s += sObj;
	//									s += "') AND (ColumnName='Design Coil Load') AND (Units = 'W')";
	//									boost::optional<double> data2 = sqlFile.execAndReturnFirstDouble(s);
	//									pRunData->daCoilHtg_FluidLdDsgn[iObj] = (data2 ? *data2 : 0.0);
				// ComponentSizes will ALWAYS be written in SI units
										s = "SELECT Value FROM ComponentSizes WHERE (CompType='Coil:Heating:Water') AND (CompName = '";
										s += sObj;
										s += "') AND (Description='Maximum Water Flow Rate') AND (Units = 'm3/s')";
										boost::optional<double> data2 = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetCoilHtgData( iRunIdx, iObj, 1, (data2 ? *data2 : 0.0) );		// pRunData->daCoilHlg_FluidFlowRtDsgnSim[iObj] = (data2 ? *data2 : 0.0);
									}
								}
							}

					// SAC 12/10/13 - grab run's environmentperiods for any hourly results retrieval
							std::vector<std::string> saEnvPeriods = sqlFile.availableEnvPeriods();
							std::string sHrly = "Hourly";

					// SAC 8/28/13 - added Blr, Chlr, HtRej & Pump results
							int iNumBoilers = pOSWrap->InitBlrData( iRunIdx );		// (int) pRunData->saBlr.size();
							if (iNumBoilers > 0)
							{	//pRunData->daBlr_CapRtd.resize( iNumBoilers, -1.0 );
								for (iObj=0; iObj < iNumBoilers; iObj++)
								{
									sObj = pOSWrap->GetBlrName(  iRunIdx, iObj );		// pRunData->saBlr[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{
				//						s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Central Plant') AND (RowName = '";
				//						s += sObj;
				//						s += "') AND (ColumnName='Nominal Capacity') AND (Units = 'W')";
				//						boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
				//						pRunData->daBlr_CapRtd[iObj] = (data ? *data : 0.0);
				// SAC 12/10/13 - storage of daBlr_CapRtd from non-hourly results (above) replaced by hourly results (below)
										double dPkVal = -99999.;
										std::string sVarName = "Boiler Heating Rate";
										for(const std::string& sEnvPer : saEnvPeriods)
										{	boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sEnvPer, sHrly, sVarName, sObj );
											if (timeSeries)
											{	openstudio::Vector values = timeSeries->values();
												unsigned numValues = (unsigned) values.size();
												for (unsigned i = 0; i < numValues; ++i)
												{	if (values(i) > dPkVal)
														dPkVal = values(i);
										}	}	}
										pOSWrap->SetBlrData(     iRunIdx, iObj, 0, (dPkVal > -99999. ? dPkVal : 0.0) );		// pRunData->daBlr_CapRtd[iObj] = (dPkVal > -99999. ? dPkVal : 0.0);
									}
							}	}

							int iNumChillers = pOSWrap->InitChlrData( iRunIdx );		// (int) pRunData->saChlr.size();
							if (iNumChillers > 0)
							{	//pRunData->daChlr_CapRtd.resize( iNumChillers, -1.0 );
								for (iObj=0; iObj < iNumChillers; iObj++)
								{
									sObj = pOSWrap->GetChlrName(  iRunIdx, iObj );		// pRunData->saChlr[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{
				//						s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Central Plant') AND (RowName = '";
				//						s += sObj;
				//						s += "') AND (ColumnName='Nominal Capacity') AND (Units = 'W')";
				//						boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
				//						pRunData->daChlr_CapRtd[iObj] = (data ? *data : 0.0);
				// SAC 12/10/13 - storage of daChlr_CapRtd from non-hourly results (above) replaced by hourly results (below)
										double dPkVal = -99999.;
										std::string sVarName = "Chiller Evaporator Cooling Rate";
										for(const std::string& sEnvPer : saEnvPeriods)
										{	boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sEnvPer, sHrly, sVarName, sObj );
											if (timeSeries)
											{	openstudio::Vector values = timeSeries->values();
												unsigned numValues = (unsigned) values.size();
												for (unsigned i = 0; i < numValues; ++i)
												{	if (values(i) > dPkVal)
														dPkVal = values(i);
										}	}	}
										pOSWrap->SetChlrData(    iRunIdx, iObj, 0, (dPkVal > -99999. ? dPkVal : 0.0) );		// pRunData->daChlr_CapRtd[iObj] = (dPkVal > -99999. ? dPkVal : 0.0);
									}
							}	}

							int iNumClgTowers = pOSWrap->InitHtRejData( iRunIdx );		// (int) pRunData->saHtRej.size();
							if (iNumClgTowers > 0)
							{	//pRunData->daHtRej_CapRtd.resize( iNumClgTowers, -1.0 );
								for (iObj=0; iObj < iNumClgTowers; iObj++)
								{
									sObj = pOSWrap->GetHtRejName(  iRunIdx, iObj );		// pRunData->saHtRej[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{
				//						s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Central Plant') AND (RowName = '";
				//						s += sObj;
				//						s += "') AND (ColumnName='Nominal Capacity') AND (Units = 'W')";
				//						boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
				//						pRunData->daHtRej_CapRtd[iObj] = (data ? *data : 0.0);
				// SAC 12/10/13 - storage of daHtRej_CapRtd from non-hourly results (above) replaced by hourly results (below)
										double dPkVal = -99999.;
										std::string sVarName = "Cooling Tower Heat Transfer Rate";
										for(const std::string& sEnvPer : saEnvPeriods)
										{	boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sEnvPer, sHrly, sVarName, sObj );
											if (timeSeries)
											{	openstudio::Vector values = timeSeries->values();
												unsigned numValues = (unsigned) values.size();
												for (unsigned i = 0; i < numValues; ++i)
												{	if (values(i) > dPkVal)
														dPkVal = values(i);
										}	}	}
										pOSWrap->SetHtRejData(   iRunIdx, iObj, 0, (dPkVal > -99999. ? dPkVal : 0.0) );		// pRunData->daHtRej_CapRtd[iObj] = (dPkVal > -99999. ? dPkVal : 0.0);
									}
							}	}

							int iNumPumps = pOSWrap->InitPumpData( iRunIdx );		// (int) pRunData->saPump.size();
							if (iNumPumps > 0)
							{	//pRunData->daPump_FlowCap.resize( iNumPumps, -1.0 );
								for (iObj=0; iObj < iNumPumps; iObj++)
								{
									sObj = pOSWrap->GetPumpName(  iRunIdx, iObj );		// pRunData->saPump[iObj];
									boost::to_upper(sObj);
									if (sObj.length() > 0)
									{	s = "SELECT Value FROM TabularDataWithStrings WHERE (ReportName='EquipmentSummary') AND (ReportForString='Entire Facility') AND (TableName='Pumps') AND (RowName = '";
										s += sObj;
					// SAC 1/11/14 - units -> IP
					//					s += "') AND (ColumnName='Water Flow') AND (Units = 'm3/s')";
										s += "') AND (ColumnName='Water Flow') AND (Units = 'gal/min')";
										boost::optional<double> data = sqlFile.execAndReturnFirstDouble(s);
										pOSWrap->SetPumpData(    iRunIdx, iObj, 0, (data ? *data : 0.0) );		// pRunData->daPump_FlowCap[iObj] = (data ? *data : 0.0);
									}
								}
							}

						}  // if pRunData is valid

					}  // if facility is valid

					sqlFile.close();		// SAC 4/28/19 - close file to ensure subsequent clean-up can delete it
					//Sleep(500);				// SAC 4/29/19 - additional code to pause because close alone not releasing file in time in all cases

              } catch (std::runtime_error& e) {    //VS19
         		if (pMsgCallback)
         			pMsgCallback( 0 /*iCodeType*/, 0 /*level*/, boost::str( boost::format("      inside ProcessSimulationResults() - threw exception:  %s") % std::string{e.what()} ).c_str(), 0 ); 
//             std::string expectedError("Error creating prepared statement: SELECT * FROM NonExistantTable; with error code 1, extended code 1, errmsg: no such table: NonExistantTable");
//             EXPECT_EQ(expectedError, std::string{e.what()});
              }
				}
//			}

	return bRetVal;
}



// SAC 9/5/14 - experiment w/ tracking simulation status
//#include <QObject>
//#include <utilities/core/UUID.hpp>
//#include <runmanager/lib/RunManagerWatcher.hpp>
//static openstudio::runmanager::RunManagerWatcher *spRunMgrWatcher = NULL;
//static openstudio::UUID suuidRunMgrJobs[6];

// 				total # hours thru months:   Jan   Feb   Mar   Apr   May   Jun   Jul   Aug   Sep   Oct   Nov   Dec
static int siaPriorMonthsHours[] = {  0, 0, 744, 1416, 2160, 2880, 3624, 4344, 5088, 5832, 6552, 7296, 8016, 8760 };

// return values:  0 => SUCCESS
//                >0 => user abort or error - refer to #defines listed in OS_Wrap.h
long OSWrapLib::SimulateSDD(	const char* pszEPlusPath, const char* pszProcessingPath,
									// RUN #1 data
										const char* pszSDDXMLFile, const char* pszRunSubdir,
										const char* pszWeatherPathFile, double* pdResults, bool bSimulateModel /*=true*/,
										bool bStoreHourlyResults /*=true*/, char* pszSQLOutPathFile /*=NULL*/, int iMaxLenSQLOutPathFile /*=0*/,
										bool bWriteHourlyDebugCSV /*=false*/, const char* pszIDFToSimulate /*=NULL*/,  // SAC 1/25/14
									   QuickAnalysisInfo* pQuickAnalysisInfo /*=NULL*/, int iProgressModel /*=0*/,	// SAC 11/6/14
									// RUN #2 data
										const char* pszSDDXMLFile2 /*=NULL*/, const char* pszRunSubdir2 /*=NULL*/,
										const char* pszWeatherPathFile2 /*=NULL*/, double* pdResults2 /*=NULL*/, bool bSimulateModel2 /*=true*/,
										bool bStoreHourlyResults2 /*=true*/, char* pszSQLOutPathFile2 /*=NULL*/, int iMaxLenSQLOutPathFile2 /*=0*/,
										bool bWriteHourlyDebugCSV2 /*=false*/, const char* pszIDFToSimulate2 /*=NULL*/,  // SAC 1/25/14
									   QuickAnalysisInfo* pQuickAnalysisInfo2 /*=NULL*/, int iProgressModel2 /*=0*/,	// SAC 11/6/14
									// general data
										OSWRAP_MSGCALLBACK* pMsgCallback /*=NULL*/, int iMsgCallbackType /*=0*/,
										double* pdTranslationTime /*=NULL*/, double* /*pdSimulationTime =NULL*/,  // SAC 1/23/14
										char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/,  // SAC 1/30/14
										bool bOutputDiagnostics /*=false*/, int iCodeType /*=0*/ )		// SAC 4/2/15
{
	long lRetVal = 0;
	bool bAbort = false;
	std::string strErrMsg, sCallbackMsg, sRunName;

	std::string sProcessingPath = pszProcessingPath;
	openstudio::path procPath   = openstudio::toPath(pszProcessingPath);
	openstudio::path epdir      = openstudio::toPath(pszEPlusPath);

	std::string sSDDXMLFile[2];				sSDDXMLFile[0] = pszSDDXMLFile;
	std::string inputPathString[2];			inputPathString[0] = sProcessingPath + sSDDXMLFile[0];
	openstudio::path inputPathFile[2];		inputPathFile[0] = openstudio::toPath(inputPathString[0]);
	openstudio::path wthrPathFile[2];		wthrPathFile[0] = openstudio::toPath(pszWeatherPathFile);

	bool bHaveRun2 = (pszSDDXMLFile2 && strlen( pszSDDXMLFile2 ) > 0);
	if (bHaveRun2)
	{	sSDDXMLFile[1] = pszSDDXMLFile2;
		inputPathString[1] = sProcessingPath + sSDDXMLFile[1];
		inputPathFile[1] = openstudio::toPath(inputPathString[1]);
		wthrPathFile[1]  = openstudio::toPath(pszWeatherPathFile2);
	}

	if (!boost::filesystem::exists(inputPathFile[0]))
		lRetVal = OSWrap_SimSDD_InputFileNotFound;
	else if (!boost::filesystem::exists(wthrPathFile[0]))
		lRetVal = OSWrap_SimSDD_WthrFileNotFound;
	else if (!boost::filesystem::is_directory(procPath))
		lRetVal = OSWrap_SimSDD_ProcPathNotValid;
	else if (!boost::filesystem::is_directory(epdir))
		lRetVal = OSWrap_SimSDD_SimEXEPathNotValid;
	else if (bHaveRun2 && !boost::filesystem::exists(inputPathFile[1]))
		lRetVal = OSWrap_SimSDD_InputFile2NotFound;
	else if (bHaveRun2 && !boost::filesystem::exists(wthrPathFile[1]))
		lRetVal = OSWrap_SimSDD_WthrFile2NotFound;
	else
	{
		boost::posix_time::ptime	tmStartTime = boost::posix_time::microsec_clock::local_time();  // SAC 1/23/14
		boost::optional<openstudio::model::Model> model[2];

//// SAC 11/5/14 - moved up from below
//			openstudio::removeDirectory(procPath/openstudio::toPath(pszRunSubdir));
//			if (bHaveRun2)
//				openstudio::removeDirectory(procPath/openstudio::toPath(pszRunSubdir2));

		openstudio::path osmPath[2];

	// expanded arrays to handle QuickAnalysis runs
		int iNumEPSims = 0, iNumSimsToExecute = 0;
		openstudio::path idfPath[24];
		int iaRunIdx[24]       = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		bool baFirstQSRun[24]  = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
		bool baLastQSRun[24]   = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
		//int iaYrHourOffset[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		double faResultMult[24] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		bool baSimulate[24]    = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
		std::string saRunSubdir[24];
		std::string sEPlusSubdir = "EnergyPlus";		// std::string saEPlusSubdir[24];  // = { "EnergyPlus", "EnergyPlus" };

		QuickAnalysisRunPeriodInfo* pqsRunPeriodInfo[24] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
		QuickAnalysisRunPeriodInfo qsRunPeriodInfo[2];
				qsRunPeriodInfo[0].m_iNumQuickAnalysisPeriods = 0;
				qsRunPeriodInfo[1].m_iNumQuickAnalysisPeriods = 0;

		int iNumRuns = (bHaveRun2 ? 2 : 1);
		for (int iRun=0; (lRetVal == 0 && iRun < iNumRuns); iRun++)
		{	if (!bHaveRun2)
				sRunName = " ";
			else if (iRun==0)
				sRunName = " (1st of pair) ";
			else
				sRunName = " (2nd of pair) ";
			int iProgModel = (iRun==0 ? iProgressModel : iProgressModel2);

			try		// SAC 1/22/14 - added try/catch block to attempt more graceful handling of errors encountered in OpenStudio
			{	QuickAnalysisInfo* pQSim = (iRun==0 ? pQuickAnalysisInfo : pQuickAnalysisInfo2);
				openstudio::sdd::ReverseTranslator reverseTranslator;

										if (pMsgCallback)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Loading SDD model%sinto reverse translator..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  1 /*action*/ ) == -1);
										}

				model[iRun] = reverseTranslator.loadModel( inputPathFile[iRun], /*true /allowGUI/,*/ NULL /*ProgressBar**/ );  // second argument true will collect BCL key
				if(model[iRun] && !bAbort)
				{
										if (pMsgCallback && !bAbort)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Saving OSM%sfile..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  2 /*action*/ ) == -1);
										}

// SAC 5/23/14 - BEFORE saving OSM, go through each surface to ensure that the polygon vertices are in the order that EnergyPlus will expect
					for( openstudio::model::PlanarSurface planarSurface : model[iRun]->getModelObjects<openstudio::model::PlanarSurface>() )
					{	openstudio::Point3dVector vertices = openstudio::reorderULC(planarSurface.vertices());
						planarSurface.setVertices(vertices);
					}

					osmPath[iRun] = inputPathFile[iRun].replace_extension(openstudio::toPath("osm").string());
					try
					{	model[iRun]->save(osmPath[iRun], true);

						int iIDFBaseLastDot = (int) inputPathString[iRun].rfind('.');
						std::string sIDFBasePath = (iIDFBaseLastDot > 0 ? inputPathString[iRun].substr( 0, iIDFBaseLastDot ) : sIDFBasePath = inputPathString[iRun] );


//				// logic to loop over QuickAnalysis run periods (when appropriate)
//						bool bInstallQSimRunPeriod = (bStoreHourlyResults && pQSim && pQSim->m_iNumQuickAnalysisPeriods > 0 &&
//																((iRun==0 && (pszIDFToSimulate==NULL || strlen( pszIDFToSimulate )<1)) || (iRun==1 && (pszIDFToSimulate2==NULL || strlen( pszIDFToSimulate2 )<1))));
//						int iNumRunPeriods = (bInstallQSimRunPeriod ? pQSim->m_iNumQuickAnalysisPeriods : 1);
//						for (int iRP=0; iRP < iNumRunPeriods; iRP++)
//						{
//							if (!bHaveRun2)
//							{	if (bInstallQSimRunPeriod)
//									sRunName = boost::str( boost::format(" QS%d ") % (iRP+1) );
//								else
//									sRunName = " ";
//							}
//							else
//							{	if (bInstallQSimRunPeriod)
//									sRunName = boost::str( boost::format(" (run %d/%d, QS%d) ") % (iRun+1) % iNumRuns % (iRP+1) );
//								else
//									sRunName = boost::str( boost::format(" (run %d/%d) ") % (iRun+1) % iNumRuns );
//							}
//							iaRunIdx[  iNumEPSims] = iRun;
//							baSimulate[iNumEPSims] = ((iRun==0 && bSimulateModel) || (iRun==1 && bSimulateModel2));
//							if (baSimulate[iNumEPSims])
//								iNumSimsToExecute++;
//
//										if (pMsgCallback)
//										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Loading OpenStudio model%sinto forward translator (to IDF)..." ) % sRunName );
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), 1 /*action*/ ) == -1);
//										}
//
//			// SET RUN PERIOD
//							if (bInstallQSimRunPeriod)
//							{
//								baFirstQSRun[  iNumEPSims] = (iRP == 0);
//								baLastQSRun[   iNumEPSims] = (iRP == iNumRunPeriods-1);
//								iaYrHourOffset[iNumEPSims] = siaPriorMonthsHours[pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP]] + ((pQSim->m_iQuickAnalysisPeriodBeginDay[iRP] - 1) * 24);		// hours in year PRIOR to begin of run period
//								faResultMult[  iNumEPSims] = pQSim->m_fQuickAnalysisResultsMult;
//								//saEPlusSubdir[ iNumEPSims] = boost::str( boost::format("EnergyPlus-qs%d") % (iRP+1) );
//								saRunSubdir[   iNumEPSims] = boost::str( boost::format("%s-qs%d") % (iRun==0 ? pszRunSubdir : pszRunSubdir2) % (iRP+1) );
//
//								openstudio::model::RunPeriod runPeriod = model[iRun]->getUniqueModelObject<openstudio::model::RunPeriod>();
//								runPeriod.setBeginMonth(      pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP] );
//								runPeriod.setBeginDayOfMonth( pQSim->m_iQuickAnalysisPeriodBeginDay[  iRP] );
//								runPeriod.setEndMonth(        pQSim->m_iQuickAnalysisPeriodEndMonth[  iRP] );
//								runPeriod.setEndDayOfMonth(   pQSim->m_iQuickAnalysisPeriodEndDay[    iRP] );
//	// TO DO - install begin period Day Of Week
//	//	long	m_iQuickAnalysisPeriodBeginDOWk[  MAX_NUM_QANALPERIODS ];  // DayOfWeek
//							}
//							else
//							{	//saEPlusSubdir[iNumEPSims] = "EnergyPlus";
//								saRunSubdir[  iNumEPSims] = (iRun==0 ? pszRunSubdir : pszRunSubdir2);
//							}
//
//							if (baSimulate[iNumEPSims])
//								openstudio::removeDirectory(procPath/openstudio::toPath( saRunSubdir[iNumEPSims] ));
//
//						// code added to ALSO translate and write IDF file, while we still have OSM loaded (rather than re-loading OSM later to generate IDF)
//							openstudio::energyplus::ForwardTranslator forwardTranslator;
//							forwardTranslator.setKeepRunControlSpecialDays(true);
//							forwardTranslator.setIPTabularOutput(true);
//							forwardTranslator.setExcludeLCCObjects(true);
//							openstudio::Workspace workspace = forwardTranslator.translateModel( *model[iRun] );
//					//		EXPECT_EQ(0u, forwardTranslator.errors().size());
//					//		EXPECT_EQ(1u,workspace.getObjectsByType(IddObjectType::Version).size());
//							idfPath[iNumEPSims] = (bInstallQSimRunPeriod ?	openstudio::toPath( boost::str( boost::format("%s-qs%d.idf") % sIDFBasePath % (iRP+1) ) ) :
//																							openstudio::toPath( boost::str( boost::format("%s.idf")      % sIDFBasePath           ) ) );
//
//										if (pMsgCallback && !bAbort)
//										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Saving IDF%sfile..." ) % sRunName );
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), 2 /*action*/ ) == -1);
//										}
//
//							try
//							{	workspace.save( idfPath[iNumEPSims], true /*overwrite*/ );
//							}
// REPLACED ABOVE W/ BELOW

										if (pMsgCallback)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Loading OpenStudio model%sinto forward translator (to IDF)..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  1 /*action*/ ) == -1);
										}

					// code added to ALSO translate and write IDF file, while we still have OSM loaded (rather than re-loading OSM later to generate IDF)
						openstudio::energyplus::ForwardTranslator forwardTranslator;
						forwardTranslator.setKeepRunControlSpecialDays(true);
						forwardTranslator.setIPTabularOutput(true);
						forwardTranslator.setExcludeLCCObjects(true);
						openstudio::Workspace workspace = forwardTranslator.translateModel( *model[iRun] );

						if (bOutputDiagnostics)		// SAC 4/2/15
						{	openstudio::IdfObject idfOutDiag( openstudio::IddObjectType::Output_Diagnostics );
							idfOutDiag.setString( 0, "DisplayExtraWarnings" );
							workspace.addObject( idfOutDiag );
						}

				//		EXPECT_EQ(0u, forwardTranslator.errors().size());
				//		EXPECT_EQ(1u,workspace.getObjectsByType(IddObjectType::Version).size());
						idfPath[     iNumEPSims] = openstudio::toPath( boost::str( boost::format("%s.idf") % sIDFBasePath ) );
						saRunSubdir[ iNumEPSims] = (iRun==0 ? pszRunSubdir : pszRunSubdir2);
						iaRunIdx[    iNumEPSims] = iRun;
						baSimulate[ iNumEPSims] = ((iRun==0 && bSimulateModel) || (iRun==1 && bSimulateModel2));
						if (baSimulate[iNumEPSims])
							iNumSimsToExecute++;
						if (baSimulate[iNumEPSims])
							openstudio::removeDirectory(procPath/openstudio::toPath( saRunSubdir[iNumEPSims] ));
						pqsRunPeriodInfo[iNumEPSims] = &qsRunPeriodInfo[iRun];

						bool bInstallQSimRunPeriod = (bStoreHourlyResults && pQSim && pQSim->m_iNumQuickAnalysisPeriods > 0 &&
																((iRun==0 && (pszIDFToSimulate==NULL || strlen( pszIDFToSimulate )<1)) || (iRun==1 && (pszIDFToSimulate2==NULL || strlen( pszIDFToSimulate2 )<1))));
						if (bInstallQSimRunPeriod)
						{
							faResultMult[iNumEPSims] = pQSim->m_fQuickAnalysisResultsMult;

			// REMOVE any existing Run Periods (should always be just one)
							std::vector<openstudio::WorkspaceObject> runPeriods = workspace.getObjectsByType(openstudio::IddObjectType::RunPeriod);
							for(auto runPeriod : runPeriods)
							{	runPeriod.remove();
							}

			// loop over QuickAnalysis run periods and create new E+ RunPeriods
							qsRunPeriodInfo[iRun].m_iNumQuickAnalysisPeriods = pQSim->m_iNumQuickAnalysisPeriods;
							for (int iRP=0; iRP < pQSim->m_iNumQuickAnalysisPeriods; iRP++)
							{
						//		baFirstQSRun[  iNumEPSims] = (iRP == 0);
						//		baLastQSRun[   iNumEPSims] = (iRP == pQSim->m_iNumQuickAnalysisPeriods-1);
						//		iaYrHourOffset[iNumEPSims] = siaPriorMonthsHours[pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP]] + ((pQSim->m_iQuickAnalysisPeriodBeginDay[iRP] - 1) * 24);		// hours in year PRIOR to begin of run period
						//		faResultMult[  iNumEPSims] = pQSim->m_fQuickAnalysisResultsMult;
						//		//saEPlusSubdir[ iNumEPSims] = boost::str( boost::format("EnergyPlus-qs%d") % (iRP+1) );
						//		saRunSubdir[   iNumEPSims] = boost::str( boost::format("%s-qs%d") % (iRun==0 ? pszRunSubdir : pszRunSubdir2) % (iRP+1) );

								qsRunPeriodInfo[iRun].m_sRunPeriodName[iRP] = boost::str( boost::format("QuickAnalysis%d Run Period") % (iRP+1) );
								qsRunPeriodInfo[iRun].m_iRunPeriodYrHourOffset[iRP] = siaPriorMonthsHours[pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP]] + ((pQSim->m_iQuickAnalysisPeriodBeginDay[iRP] - 1) * 24);		// hours in year PRIOR to begin of run period
			// SET RUN PERIOD
								boost::optional<openstudio::WorkspaceObject> runPeriod = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::RunPeriod));
								OS_ASSERT(runPeriod);
								runPeriod->setString( 0, qsRunPeriodInfo[iRun].m_sRunPeriodName[iRP] );
								runPeriod->setInt(    1, pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP] );
								runPeriod->setInt(    2, pQSim->m_iQuickAnalysisPeriodBeginDay[  iRP] );
								runPeriod->setInt(    3, pQSim->m_iQuickAnalysisPeriodEndMonth[  iRP] );
								runPeriod->setInt(    4, pQSim->m_iQuickAnalysisPeriodEndDay[    iRP] );
								switch (pQSim->m_iQuickAnalysisPeriodBeginDOWk[iRP])
								{	case  2 :	runPeriod->setString( 5, "Monday"    );	break;
									case  3 :	runPeriod->setString( 5, "Tuesday"   );	break;
									case  4 :	runPeriod->setString( 5, "Wednesday" );	break;
									case  5 :	runPeriod->setString( 5, "Thursday"  );	break;
									case  6 :	runPeriod->setString( 5, "Friday"    );	break;
									case  7 :	runPeriod->setString( 5, "Saturday"  );	break;
									default :	runPeriod->setString( 5, "Sunday"    );	break;
								}
								runPeriod->setString(  6, "No"  );		// !- Use Weather File Holidays and Special Days
								runPeriod->setString(  7, "No"  );		// !- Use Weather File Daylight Saving Period
								runPeriod->setString(  8, "Yes" );		// !- Apply Weekend Holiday Rule
								runPeriod->setString(  9, "Yes" );		// !- Use Weather File Rain Indicators
								runPeriod->setString( 10, "Yes" );		// !- Use Weather File Snow Indicators
								runPeriod->setInt(    11,  1    );		// !- Number of Times Runperiod to be Repeated
						}	}

// SAC 9/30/15 - from OpenStudio code - a work around for E+ v8.3 bug to ensure hourly results output for all defined Meters
			      // this is a workaround for issue #1699
			      bool needsdetailedvariable = false;
			      bool needstimestepvariable = true; // we add these at the bottom of the file
			      bool needshourlyvariable = false;
			      bool needsdailyvariable = false;
			      bool needsmonthlyvariable = false;
			      bool needsrunperiodvariable = false;
			        // this is a workaround for issue #1699
			        // get all the meter requests
			        std::vector<openstudio::WorkspaceObject> meterobjs;
			        std::vector<openstudio::WorkspaceObject> tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_MeterFileOnly);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_Cumulative);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_Cumulative_MeterFileOnly);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        for (const openstudio::WorkspaceObject& meterobj : meterobjs)
			        { // DLM: same index for all types of meters
			          boost::optional<std::string> reportingFrequency = meterobj.getString(openstudio::Output_MeterFields::ReportingFrequency, true);
			          OS_ASSERT(reportingFrequency);
			          if (openstudio::istringEqual(*reportingFrequency, "Detailed")){
			            needsdetailedvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Timestep")){
			            needstimestepvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Hourly")){
			            needshourlyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Daily")){
			            needsdailyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Monthly")){
			            needsmonthlyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "RunPeriod") || openstudio::istringEqual(*reportingFrequency, "Environment") || openstudio::istringEqual(*reportingFrequency, "Annual")){
			            needsrunperiodvariable = true;
			          }
			        }
			        // get all the variable requests
			        std::vector<openstudio::WorkspaceObject> variableobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Variable);
			        for (const openstudio::WorkspaceObject& variableobj : variableobjs)
			        { boost::optional<std::string> reportingFrequency = variableobj.getString(openstudio::Output_VariableFields::ReportingFrequency, true);
			          OS_ASSERT(reportingFrequency);
			          if (openstudio::istringEqual(*reportingFrequency, "Detailed")){
			            needsdetailedvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Timestep")){
			            needstimestepvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Hourly")){
			            needshourlyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Daily")){
			            needsdailyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Monthly")){
			            needsmonthlyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "RunPeriod") || openstudio::istringEqual(*reportingFrequency, "Environment") || openstudio::istringEqual(*reportingFrequency, "Annual")){
			            needsrunperiodvariable = false;
			          }
			        }
//        ofs << "    HeatRejection:DistrictCooling,  !- Variable or Meter 9 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 9" << std::endl;
//        ofs << "    Humidifier:DistrictCooling,  !- Variable or Meter 10 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 10" << std::endl;
//        ofs << "    HeatRecovery:DistrictCooling,!- Variable or Meter 11 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 11" << std::endl;
//        ofs << "    WaterSystems:DistrictCooling,!- Variable or Meter 12 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 12" << std::endl;
//        ofs << "    Cogeneration:DistrictCooling,!- Variable or Meter 13 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum;            !- Aggregation Type for Variable or Meter 13" << std::endl;

//OS:Output:Variable,
//  {53396c41-2d2b-4372-9510-246eddcf8b43}, !- Handle
//  Output Variable 1,                      !- Name
//  *,                                      !- Key Value
//  Zone Outdoor Air Drybulb Temperature;   !- Variable Name

//    IddObjectType objType(IddObjectType::Output_Variable);
//    OptionalIddObject oObj = IddObject::load("Output:Variable",
//                                             "Output Reporting",
//                                             ss.str(),
//                                             objType);

			      if (needsdetailedvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Detailed;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Detailed" );
			      }
			      if (needstimestepvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Timestep;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Timestep" );
			      }
			      if (needshourlyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Hourly;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Hourly" );
			      }
			      if (needsdailyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Daily;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Daily" );
			      }
			      if (needsmonthlyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Monthly;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Monthly" );
			      }
			      if (needsrunperiodvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,RunPeriod;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "RunPeriod" );
			      }
// SAC 9/30/15 - (end of) from OpenStudio code - a work around for E+ v8.3 bug to ensure hourly results output for all defined Meters

										if (pMsgCallback && !bAbort)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Saving IDF%sfile..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  2 /*action*/ ) == -1);
										}

						try
						{	workspace.save( idfPath[iNumEPSims], true /*overwrite*/ );
						}
						catch (std::exception& e)
						{	strErrMsg = boost::str( boost::format("openstudio::Workspace::save() failed%sbecause '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
							lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSSaveIDFError : OSWrap_SimSDD_OSSaveIDF2Error);
						}
						catch (...)
						{	strErrMsg = boost::str( boost::format("openstudio::Workspace::save() failed on%sfile:  %s" ) % sRunName % inputPathString );
							lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSSaveIDFError : OSWrap_SimSDD_OSSaveIDF2Error);
						}
						iNumEPSims++;
					}
					catch (std::exception& e)
					{	strErrMsg = boost::str( boost::format("openstudio::model::Model::save() failed%sbecause '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
						lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSSaveOSMError : OSWrap_SimSDD_OSSaveOSM2Error);
					}
					catch (...)
					{	strErrMsg = boost::str( boost::format("openstudio::model::Model::save() failed on%sfile:  %s" ) % sRunName % inputPathString );
						lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSSaveOSMError : OSWrap_SimSDD_OSSaveOSM2Error);
				}	}
				else if (!bAbort && lRetVal < 1)
					lRetVal = (iRun > 0 ? OSWrap_SimSDD_OSModel2CreateError : OSWrap_SimSDD_OSModelCreateError);  // failure to create OSM (model)
			}
			catch (std::exception& e)
			{	strErrMsg = boost::str( boost::format("openstudio::sdd::ReverseTranslator::loadModel()%sfailed because '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
				lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSLoadModelError : OSWrap_SimSDD_OSLoadModel2Error);
			}
			catch (...)
			{	strErrMsg = boost::str( boost::format("openstudio::sdd::ReverseTranslator::loadModel() failed on%sfile:  %s" ) % sRunName % inputPathString );
				lRetVal = (iRun == 0 ? OSWrap_SimSDD_OSLoadModelError : OSWrap_SimSDD_OSLoadModel2Error);
			}
		}	// end of for loop over runs

		if (pdTranslationTime)  // SAC 1/23/14
		{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStartTime;
			*pdTranslationTime = ((double) td.total_microseconds()) / 1000000.0;
		}

		if(iNumSimsToExecute > 0 && !bAbort && lRetVal < 1)
		{
//			bool bSimulatePredefinedIDF[2] = { false, false };  // SAC 1/25/14
////			std::string saEPlusSubdir[2] = { "ModelToIdf\\EnergyPlus-0", "ModelToIdf\\EnergyPlus-0" };
//			std::string saEPlusSubdir[2] = { "EnergyPlus", "EnergyPlus" };

			tmStartTime = boost::posix_time::microsec_clock::local_time();  // SAC 1/23/14

// SAC 2/19/19
//		// now have IDF -> proceed w/ workflow to simulate in E+
//			std::string rmDatabasePath = sProcessingPath + "runmanager.db";
//			openstudio::path rmDBPath = openstudio::toPath(rmDatabasePath);
//// ?? initialize UI ??
//			openstudio::runmanager::RunManager rm( rmDBPath, true /*t_new*/, true /*t_paused*/, false /*t_initializeui*/ ); // Create a RunManager with a new database file
//
//			openstudio::runmanager::ConfigOptions co;
//// removed when revising code to reference local EnergyPlus executable
////			co.fastFindEnergyPlus();
////	// check/debug
////			openstudio::path epwdir = co.getDefaultEPWLocation();
////			openstudio::path epdir = epwdir.parent_path();
////			openstudio::path idfdir = co.getDefaultIDFLocation();
////			boost::optional<int> iMjr = co.getTools().getTool("energyplus").version.getMajor();
//
//			openstudio::runmanager::Workflow wf;
////			wf.add(co.getTools());   - must add job FIRST or get NULL ptr error
//			openstudio::runmanager::Tools tools = openstudio::runmanager::ConfigOptions::makeTools( epdir,   // energyPlusExePath().parent_path(), 
//																												openstudio::path(), openstudio::path(), openstudio::path(), openstudio::path());
//																											//	t_energyplus, t_xmlpreproc, t_radiance,t_ruby,t_dakota);
//																	//inline openstudio::path energyPlusExePath()
//																	//  return openstudio::toPath("C:/EnergyPlusV7-0-0/EnergyPlus.exe");
//
//			wf.addJob(	openstudio::runmanager::JobType::EnergyPlus);
//			wf.add(tools);
//
//										if (pMsgCallback && !bAbort)
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - Queing EnergyPlus jobs...", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSim, (iProgressModel + iProgressModel2), 0 ) ) == -1);   // was:  3 /*action*/ ) == -1);
//
//			if (!bAbort)
//			{
//				openstudio::runmanager::Job jobs[24] = {	openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob() };
//				int iNumJobs=0;
//		// LOOP OVER ALL OF EPlus Sims (1-24)
//				for (int iESimIdx=0; (!bAbort && iESimIdx < iNumEPSims); iESimIdx++)
//					if (baSimulate[iESimIdx])
//					{
//						const char* pszIDFToSim = (iaRunIdx[iESimIdx]==0 ? pszIDFToSimulate : pszIDFToSimulate2);
//					// deal w/ PRE-DEFINED IDF files
//						if (pszIDFToSim && strlen( pszIDFToSim ) > 0 && boost::filesystem::exists(openstudio::toPath(pszIDFToSim)))
//						{	int iCITLastDot = sSDDXMLFile[iaRunIdx[iESimIdx]].rfind('.');
//							if (iCITLastDot > 0)
//							{	std::string sCopyIDFTo = sProcessingPath + sSDDXMLFile[iaRunIdx[iESimIdx]].substr( 0, iCITLastDot );
//								sCopyIDFTo += "-fxd.idf";
//								if (boost::filesystem::exists( sCopyIDFTo ))
//									boost::filesystem::remove(  sCopyIDFTo );
//								boost::filesystem::copy_file( pszIDFToSim, sCopyIDFTo );
//								if (boost::filesystem::exists( sCopyIDFTo ))
//								{	//bSimulatePredefinedIDF[0] = true;
//									idfPath[iESimIdx] = openstudio::toPath( sCopyIDFTo );
////									osmPath[0] = openstudio::toPath( sCopyIDFTo );
////									saEPlusSubdir[0] = "EnergyPlus";
//						}	}	}
//						// ?? OS_ASSERT( (!bHaveRun2 || bSimulatePredefinedIDF[0] == bSimulatePredefinedIDF[1]) );	// if this is not the case, then we may need to fiddle w/ the workflow/jobs...
//
//			//			openstudio::runmanager::Job job1 = wf.create( procPath/openstudio::toPath(pszRunSubdir) /*procPath*/, idfPath[0], wthrPathFile[0] /*"path/to/epws"*/ );
//			//			openstudio::runmanager::Job job2 = wf.create( procPath/openstudio::toPath( (bHaveRun2 ? pszRunSubdir2 : pszRunSubdir) ) /*procPath*/, (bHaveRun2 ? idfPath[1] : idfPath[0]),
//			//																												(bHaveRun2 ? wthrPathFile[1] : wthrPathFile[0]) /*"path/to/epws"*/ );
//			//			rm.enqueue(job1, true /*force? */ );
//			//			if (bHaveRun2)
//			//				rm.enqueue(job2, true /*force? */ );
//
//						jobs[iNumJobs] = wf.create( procPath/openstudio::toPath( saRunSubdir[iESimIdx] ) /*procPath*/, idfPath[iESimIdx], wthrPathFile[iaRunIdx[iESimIdx]] /*"path/to/epws"*/ );
//						rm.enqueue(jobs[iNumJobs], true /*force? */ );
//						iNumJobs++;
//					}
//
//// SAC 9/5/14 - experiment w/ tracking simulation status
////	openstudio::runmanager::RunManagerWatcher rmWatch( rm );
////	spRunMgrWatcher = &rmWatch;
////	suuidRunMgrJobs[0] = job1.uuid();
////	suuidRunMgrJobs[1] = (bHaveRun2 ? job2.uuid() : 0);
////	suuidRunMgrJobs[2] = suuidRunMgrJobs[3] = suuidRunMgrJobs[4] = suuidRunMgrJobs[5] = 0;
//
//				rm.setPaused(false);
//				rm.waitForFinished(); // Block until the runamanger has completed running all jobs
//
//// SAC 9/5/14 - experiment w/ tracking simulation status
////	suuidRunMgrJobs[0] = suuidRunMgrJobs[1] = suuidRunMgrJobs[2] = suuidRunMgrJobs[3] = suuidRunMgrJobs[4] = suuidRunMgrJobs[5] = 0;
////	spRunMgrWatcher = NULL;
//
////QMessageBox msgBox;
////msgBox.setText("Back from performing simulation(s) (following waitForFinished())");		msgBox.exec();
//										if (pMsgCallback && !bAbort)
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - Back from ModelToIdf & E+, storing results...", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSimRes, (iProgressModel + iProgressModel2), 0 ) ) == -1);   // was:  4 /*action*/ ) == -1);
//
//				if (pdSimulationTime)  // SAC 1/23/14
//				{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStartTime;
//					*pdSimulationTime = ((double) td.total_microseconds()) / 1000000.0;
//				}
//
//				for (int ij=0; ij < iNumJobs; ij++)
//				{	openstudio::runmanager::JobErrors treeErrors = jobs[ij].treeErrors(); // represents the state of the job tree
//					if (!treeErrors.succeeded())
//					{
//						// something went wrong, look at treeErrors.errors(), treeErrors.warnings(), job.allOutputFiles().getAllByFilename("stderr")
//						// for more info
//				}	}
//			}
		}


//		int iNumEPSims = 0;
//		openstudio::path idfPath[24];
//		int iaRunIdx[24]       = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//		bool baFirstQSRun[24]  = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
//		bool baLastQSRun[24]   = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
//		int iaYrHourOffset[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//		double faResultMult[24] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
//		bool baSimulate[24]    = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };


	// PROCESS SIMULATION RESULTS
		bool bProcResultsOK = false;
		if(iNumSimsToExecute > 0 && !bAbort && lRetVal < 1 && pData)
		{
			for (int iESimIdx=0; (!bAbort && iESimIdx < iNumEPSims); iESimIdx++)
				if (baSimulate[iESimIdx])
				{
		// check for simulation warnings/errors
				//	int iLastDot = sIDFPath.rfind('.');   // sSDDXMLFile[iaRunIdx[iESimIdx]].rfind('.');
				//	int iLastSpc = sIDFPath.rfind(' ');   // sSDDXMLFile[iaRunIdx[iESimIdx]].rfind(' ');

								//	std::string sDbgMsg = boost::str( boost::format("%s / dot @ %d / space @ %d") % sSDDXMLFile % iLastDot % iLastSpc );
								//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );

				//	if (iLastSpc >= (iLastDot-1))
				//	{	//ASSERT( FALSE );
				//		lRetVal = (iaRunIdx[iESimIdx]==0 ? OSWrap_SimSDD_SimErrFileNotValid : OSWrap_SimSDD_SimErrFile2NotValid);  // Unable to determine E+ .err path/file
				//	}
				//	else
				//	{
								OS_ASSERT( iaRunIdx[iESimIdx] >= 0 && iaRunIdx[iESimIdx] < OSW_MaxNumSims );
						std::string sErrPathFile = boost::str( boost::format("%s%s\\%s\\eplusout.err") 
																				% sProcessingPath % saRunSubdir[iESimIdx] % sEPlusSubdir );
						openstudio::path errPathFile = openstudio::toPath( sErrPathFile );
						openstudio::energyplus::ErrorFile errorFile( errPathFile );
						pData[iaRunIdx[iESimIdx]]->sSimErrPathFile   = sErrPathFile;
						pData[iaRunIdx[iESimIdx]]->saSimWarnings     = errorFile.warnings();
						pData[iaRunIdx[iESimIdx]]->saSimSevereErrors = errorFile.severeErrors();
						pData[iaRunIdx[iESimIdx]]->saSimFatalErrors  = errorFile.fatalErrors();
						pData[iaRunIdx[iESimIdx]]->bSimCompleted              = errorFile.completed();
						pData[iaRunIdx[iESimIdx]]->bSimCompletedSuccessfully  = errorFile.completedSuccessfully();
		//		pData[iaRunIdx[iESimIdx]]->bSimCompleted              = true;
		//		pData[iaRunIdx[iESimIdx]]->bSimCompletedSuccessfully  = true;
   
						std::string sTblOutputPathFile = boost::str( boost::format("%s%s\\%s\\eplustbl.htm") 
																				% sProcessingPath % saRunSubdir[iESimIdx] % sEPlusSubdir );
						pData[iaRunIdx[iESimIdx]]->sSimVersionID = ParseEnergyPlusTablesForVersionID( sTblOutputPathFile );
		//		pData[iaRunIdx[iESimIdx]]->sSimVersionID = "Windows-32 8.1.0.009";
   
								//	sDbgMsg = boost::str( boost::format("ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s")
								//									% sErrPathFile % pRunData->saSimWarnings.size() % pRunData->saSimSevereErrors.size() % pRunData->saSimFatalErrors.size()
								//									% (errorFile.completed() ? "TRUE" : "FALSE") % (errorFile.completedSuccessfully() ? "TRUE" : "FALSE") );
								//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );
								
								//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
								//  EXPECT_EQ(static_cast<unsigned>(8),  errorFile.severeErrors().size());
								//  EXPECT_EQ(static_cast<unsigned>(1),  errorFile.fatalErrors().size());
								
								//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
								//  EXPECT_EQ("Output:PreprocessorMessage=\"EPXMLPreProc2\" has the following Warning conditions: Requested glazing exceeds available area for B6CCD5_window_1.  Reducing sill height to fit.", 
								//            errorFile.warnings()[0]);
								//  EXPECT_EQ(static_cast<unsigned>(8), errorFile.severeErrors().size());
								//  EXPECT_EQ(static_cast<unsigned>(1), errorFile.fatalErrors().size());
								//  EXPECT_TRUE(errorFile .completed();
								//  EXPECT_FALSE(errorFile.completedSuccessfully();
   
						if (pData[iaRunIdx[iESimIdx]]->saSimFatalErrors.size() > 0)
							lRetVal = (iaRunIdx[iESimIdx]==0 ? OSWrap_SimSDD_SimFatalError : OSWrap_SimSDD_Sim2FatalError);  // Fatal errors occurred in simulation
						else if (!errorFile.completedSuccessfully())
							lRetVal = (iaRunIdx[iESimIdx]==0 ? OSWrap_SimSDD_SimIncomplete : OSWrap_SimSDD_Sim2Incomplete);  // Simulation did not complete successfully
				//	}

		         if (lRetVal < 1 && !bAbort)
					{	//std::string sIDFFile = openstudio::toString(idfPath[iESimIdx]);
						bProcResultsOK = ProcessSimulationResults( this, lRetVal, iaRunIdx[iESimIdx], model[iaRunIdx[iESimIdx]], sProcessingPath, /*sSDDXMLFile[iaRunIdx[iESimIdx]],*/ sEPlusSubdir,
														saRunSubdir[iESimIdx].c_str(), (iaRunIdx[iESimIdx]==0 ? pszSQLOutPathFile : pszSQLOutPathFile2), (iaRunIdx[iESimIdx]==0 ? iMaxLenSQLOutPathFile : iMaxLenSQLOutPathFile2),
														(iaRunIdx[iESimIdx]==0 ? pdResults : pdResults2), (iaRunIdx[iESimIdx]==0 ? bStoreHourlyResults : bStoreHourlyResults2),
														(iaRunIdx[iESimIdx]==0 ? bWriteHourlyDebugCSV : bWriteHourlyDebugCSV2), false, openstudio::toString(idfPath[iESimIdx]).c_str(),
														baFirstQSRun[iESimIdx], baLastQSRun[iESimIdx], pqsRunPeriodInfo[iESimIdx], faResultMult[iESimIdx], -1 /*iRptFuelUseAs*/, pszEPlusPath, -1, pMsgCallback );			OS_ASSERT( bProcResultsOK );
					}
				}
		}

//	// RUN #2 Results Processing
//			if (bHaveRun2 && lRetVal < 1 && !bAbort)
//			{
//      	   if (bSimulateModel2 && pData2)
//				{
//			// check for simulation warnings/errors
//					int iLastDot = sSDDXMLFile[1].rfind('.');
//					int iLastSpc = sSDDXMLFile[1].rfind(' ');
//
//									//	std::string sDbgMsg = boost::str( boost::format("%s / dot @ %d / space @ %d") % sSDDXMLFile % iLastDot % iLastSpc );
//									//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );
//
//					if (iLastSpc >= (iLastDot-1))
//					{	//ASSERT( FALSE );
//						lRetVal = OSWrap_SimSDD_SimErrFile2NotValid;  // Unable to determine E+ .err path/file
//					}
//					else
//					{	std::string sErrPathFile = boost::str( boost::format("%s%s\\%s\\eplusout.err") 
//																				% sProcessingPath % sSDDXMLFile[1].substr( iLastSpc+1, (iLastDot-iLastSpc-1) ) % sEPlusSubdir[1] );
//						openstudio::path errPathFile = openstudio::toPath( sErrPathFile );
//						openstudio::energyplus::ErrorFile errorFile( errPathFile );
//						pData2->sSimErrPathFile   = sErrPathFile;
//						pData2->saSimWarnings     = errorFile.warnings();
//						pData2->saSimSevereErrors = errorFile.severeErrors();
//						pData2->saSimFatalErrors  = errorFile.fatalErrors();
//						pData2->bSimCompleted              = errorFile.completed();
//						pData2->bSimCompletedSuccessfully  = errorFile.completedSuccessfully();
//	//			pData2->bSimCompleted              = true;
//	//			pData2->bSimCompletedSuccessfully  = true;
//   
//						std::string sTblOutputPathFile = boost::str( boost::format("%s%s\\%s\\eplustbl.htm") 
//																				% sProcessingPath % sSDDXMLFile[1].substr( iLastSpc+1, (iLastDot-iLastSpc-1) ) % sEPlusSubdir[1] );
//						pData2->sSimVersionID = ParseEnergyPlusTablesForVersionID( sTblOutputPathFile );
//	//			pData2->sSimVersionID = "Windows-32 8.1.0.009";
//   
//									//	sDbgMsg = boost::str( boost::format("ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s")
//									//									% sErrPathFile % pRunData->saSimWarnings.size() % pRunData->saSimSevereErrors.size() % pRunData->saSimFatalErrors.size()
//									//									% (errorFile.completed() ? "TRUE" : "FALSE") % (errorFile.completedSuccessfully() ? "TRUE" : "FALSE") );
//									//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );
//								
//									//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
//									//  EXPECT_EQ(static_cast<unsigned>(8),  errorFile.severeErrors().size());
//									//  EXPECT_EQ(static_cast<unsigned>(1),  errorFile.fatalErrors().size());
//								
//									//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
//									//  EXPECT_EQ("Output:PreprocessorMessage=\"EPXMLPreProc2\" has the following Warning conditions: Requested glazing exceeds available area for B6CCD5_window_1.  Reducing sill height to fit.", 
//									//            errorFile.warnings()[0]);
//									//  EXPECT_EQ(static_cast<unsigned>(8), errorFile.severeErrors().size());
//									//  EXPECT_EQ(static_cast<unsigned>(1), errorFile.fatalErrors().size());
//									//  EXPECT_TRUE(errorFile .completed();
//									//  EXPECT_FALSE(errorFile.completedSuccessfully();
//   
//						if (pData2->saSimFatalErrors.size() > 0)
//							lRetVal = OSWrap_SimSDD_Sim2FatalError;  // Fatal errors occurred in simulation
//						else if (!errorFile.completedSuccessfully())
//							lRetVal = OSWrap_SimSDD_Sim2Incomplete;  // Simulation did not complete successfully
//					}
//				}
//
//         	if (!bSimulateModel2 || lRetVal > 0)
//				{	// do nothing more
//				}
//				else if (pData2 && !bAbort)
//				{	bProcResultsOK = ProcessSimulationResults( this, lRetVal, 1, model[1], sProcessingPath, sSDDXMLFile[1], sEPlusSubdir[1], pszRunSubdir2, pszSQLOutPathFile2, iMaxLenSQLOutPathFile2,
//																				pdResults2, bStoreHourlyResults2, bWriteHourlyDebugCSV2, pszSDDXMLFile2 );		OS_ASSERT( bProcResultsOK );
//				}
//			}

	}

										if (pMsgCallback && !bAbort)
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - returning", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSimRes, (iProgressModel + iProgressModel2), 0 ) ) == -1);   // was:  5 /*action*/ ) == -1);

	if (strErrMsg.size() > 0 && pszErrorMsg && iErrorMsgLen > 1)  // SAC 1/30/14
	{	// check error string for paths specific to development machines, and blast that info to reduce size (and for privacy)
		size_t iOSIdx = strErrMsg.find( "\\OpenStudio\\" );
		size_t iPathBeginIdx = (iOSIdx == std::string::npos ? std::string::npos : strErrMsg.rfind( ":\\", iOSIdx-1 ));
	//	// SAC 5/1/14 - added secondary check of iOSIdx because 'iOSIdx == std::string::npos' not always behaving...
	//	size_t iPathBeginIdx = (iOSIdx == std::string::npos ? std::string::npos : ((iOSIdx < 1 || iOSIdx > strErrMsg.size()-12) ? -1 : strErrMsg.rfind( ":\\", iOSIdx-1 )));
		if (iOSIdx != std::string::npos && iPathBeginIdx != std::string::npos)
		{	while (--iPathBeginIdx >= 0 && strErrMsg.at( iPathBeginIdx ) != 39)
			{ }
			if (iPathBeginIdx > 0 && iPathBeginIdx < (iOSIdx-1))
				strErrMsg.replace( iPathBeginIdx+1, iOSIdx-iPathBeginIdx-1, "..." );
			else
			{	OS_ASSERT( false );
		}	}
		strncpy_s( pszErrorMsg, iErrorMsgLen, strErrMsg.c_str(), _TRUNCATE );
	}

   return (bAbort ? OSWrap_SimSDD_UserAbortedAnalysis : lRetVal);
}




#define  MultSim_MaxSims  10		// corresponding define in BEMCmpMgr/OpenStudioInterface.cpp
static const char* pszRunNums[] = {	"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", NULL };
static boost::optional<openstudio::model::Model> model[MultSim_MaxSims];
static openstudio::path idfPath[24];
static QuickAnalysisRunPeriodInfo* pqsRunPeriodInfo[24] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
static QuickAnalysisRunPeriodInfo qsRunPeriodInfo[OSW_MaxNumSims];

// return values:  0 => SUCCESS
//                >0 => user abort or error - refer to #defines listed in OS_Wrap.h
long OSWrapLib::SimulateSDD_Multiple( const char* pszEPlusPath, const char* pszProcessingPath,
								OSWrap_SimInfo** paSDDSimInfo, int iNumSDDSimInfo,
								OSWRAP_MSGCALLBACK* pMsgCallback /*=NULL*/, int iMsgCallbackType /*=0*/, double* pdTranslationTime /*=NULL*/,
								double* /*pdSimulationTime =NULL*/, char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/,
								bool bOutputDiagnostics /*=false*/, int iCodeType /*=0*/, bool bSimViaRunMgr /*=true*/ )		// SAC 7/19/15   // SAC 2/15/19
{

//				pszEPlusPath;
//				pszProcessingPath;
//				paSDDSimInfo;
//				iNumSDDSimInfo;
//				pMsgCallback;
//				iMsgCallbackType;
//				pdTranslationTime;
//				pdSimulationTime;
//				pszErrorMsg;
//				iErrorMsgLen;
//				bOutputDiagnostics;
//
//
//			#define  MAX_NUM_QANALPERIODS      12
//			QuickAnalysisInfo:
//				long	m_iNumQuickAnalysisPeriods;
//				double	m_fQuickAnalysisResultsMult;
//				long	m_iQuickAnalysisPeriodBeginMonth[ MAX_NUM_QANALPERIODS ];	// only populated if NOT standard year (1/1-12/31)
//				long	m_iQuickAnalysisPeriodBeginDay[   MAX_NUM_QANALPERIODS ];
//				long	m_iQuickAnalysisPeriodEndMonth[   MAX_NUM_QANALPERIODS ];
//				long	m_iQuickAnalysisPeriodEndDay[     MAX_NUM_QANALPERIODS ];
//				long	m_iQuickAnalysisPeriodBeginDOWk[  MAX_NUM_QANALPERIODS ];  // DayOfWeek
//			
//			OSWrap_SimInfo:
//				char pszSDDXMLFileName[FILENAME_MAX];
//				char pszRunSubdir[FILENAME_MAX];
//				char pszWeatherPathFile[FILENAME_MAX];
//				char pszSQLOutPathFile[FILENAME_MAX];
//				char pszIDFToSimulate[FILENAME_MAX];
//				double* pdResults;
//				bool bSimulateModel;
//				bool bStoreHourlyResults;
//				bool bWriteHourlyDebugCSV;
//				QuickAnalysisInfo* pQuickAnalysisInfo;
//				int iProgressModel;
//				int iSimReturnValue;
//
//									// RUN #1 data
//										const char* pszSDDXMLFile, const char* pszRunSubdir,
//										const char* pszWeatherPathFile, double* pdResults, bool bSimulateModel /*=true*/,
//										bool bStoreHourlyResults /*=true*/, char* pszSQLOutPathFile /*=NULL*/, int iMaxLenSQLOutPathFile /*=0*/,
//										bool bWriteHourlyDebugCSV /*=false*/, const char* pszIDFToSimulate /*=NULL*/,  // SAC 1/25/14
//									   QuickAnalysisInfo* pQuickAnalysisInfo /*=NULL*/, int iProgressModel /*=0*/,	// SAC 11/6/14
//									// RUN #2 data
//										const char* pszSDDXMLFile2 /*=NULL*/, const char* pszRunSubdir2 /*=NULL*/,
//										const char* pszWeatherPathFile2 /*=NULL*/, double* pdResults2 /*=NULL*/, bool bSimulateModel2 /*=true*/,
//										bool bStoreHourlyResults2 /*=true*/, char* pszSQLOutPathFile2 /*=NULL*/, int iMaxLenSQLOutPathFile2 /*=0*/,
//										bool bWriteHourlyDebugCSV2 /*=false*/, const char* pszIDFToSimulate2 /*=NULL*/,  // SAC 1/25/14
//									   QuickAnalysisInfo* pQuickAnalysisInfo2 /*=NULL*/, int iProgressModel2 /*=0*/,	// SAC 11/6/14


	long lRetVal = 0;
	bool bAbort = false;
	int iRun = 0;
	std::string strErrMsg, sCallbackMsg, sRunName;
	std::string sSDDXMLFile[MultSim_MaxSims];
	std::string inputPathString[MultSim_MaxSims];
	openstudio::path inputPathFile[MultSim_MaxSims];
	openstudio::path wthrPathFile[MultSim_MaxSims];

	std::string sProcessingPath = pszProcessingPath;
	openstudio::path procPath   = openstudio::toPath(pszProcessingPath);
	openstudio::path epdir      = openstudio::toPath(pszEPlusPath);

// various input checks
	if (!boost::filesystem::is_directory(procPath))
		lRetVal = OSWrap_SimSDD_ProcPathNotValid;
	else if (!boost::filesystem::is_directory(epdir))
		lRetVal = OSWrap_SimSDD_SimEXEPathNotValid;
	else if (iNumSDDSimInfo > MultSim_MaxSims)
		lRetVal = OSWrap_SimSDD_TooManySims;
	else
	{	for (iRun=0; (iRun < iNumSDDSimInfo && lRetVal == 0); iRun++)
		{
			if (paSDDSimInfo[iRun] == NULL)
				lRetVal = OSWrap_SimSDD_InvalidSimData + (iRun * 10);
			else if (iRun > 1 && paSDDSimInfo[iRun]->bStoreHourlyResults && paSDDSimInfo[iRun]->pQuickAnalysisInfo &&
							paSDDSimInfo[iRun]->pQuickAnalysisInfo->m_iNumQuickAnalysisPeriods > 0 &&
							(paSDDSimInfo[iRun]->pszIDFToSimulate == NULL || strlen( paSDDSimInfo[iRun]->pszIDFToSimulate ) < 1) )
				lRetVal = OSWrap_SimSDD_NumSimsWithQuickRunErr;
			else
			{	sSDDXMLFile[iRun] = paSDDSimInfo[iRun]->pszSDDXMLFileName;
				inputPathString[iRun] = sProcessingPath + sSDDXMLFile[iRun];
				inputPathFile[iRun] = openstudio::toPath( inputPathString[iRun] );
				wthrPathFile[iRun] = openstudio::toPath( paSDDSimInfo[iRun]->pszWeatherPathFile );

				if (!boost::filesystem::exists(inputPathFile[iRun]))
				{	lRetVal = OSWrap_SimSDD_InputFileNotFound + (iRun * 10);
					paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_InputFileNotFound;
				}
				else if (!boost::filesystem::exists(wthrPathFile[iRun]))
				{	lRetVal = OSWrap_SimSDD_WthrFileNotFound + (iRun * 10);
					paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_WthrFileNotFound;
				}
	}	}	}

	int iProgressModelSum = 0;
	if (lRetVal == 0)
	{
		boost::posix_time::ptime	tmStartTime = boost::posix_time::microsec_clock::local_time();  // SAC 1/23/14
//		boost::optional<openstudio::model::Model> model[MultSim_MaxSims];

		openstudio::path osmPath[MultSim_MaxSims];

	// expanded arrays to handle QuickAnalysis runs
		m_iNumEPSims = 0; 
		int iNumSimsToExecute = 0;
//		openstudio::path idfPath[24];
//		int iaRunIdx[24]       = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//		bool baFirstQSRun[24]  = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
//		bool baLastQSRun[24]   = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
		//int iaYrHourOffset[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//		double faResultMult[24] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		bool baSimulate[24]    = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
//		std::string saRunSubdir[24];
//		std::string sEPlusSubdir = "EnergyPlus";		// std::string saEPlusSubdir[24];  // = { "EnergyPlus", "EnergyPlus" };
		for (iRun=0; iRun<24; iRun++)
		{	pRunData[iRun]->iRunIdx = 0;
			pRunData[iRun]->fResultMult = 1;
			pqsRunPeriodInfo[iRun] = NULL;
		}

//		QuickAnalysisRunPeriodInfo* pqsRunPeriodInfo[24] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
//		QuickAnalysisRunPeriodInfo qsRunPeriodInfo[OSW_MaxNumSims];
				for (int iQSRI=0; iQSRI < OSW_MaxNumSims; iQSRI++)
					qsRunPeriodInfo[iQSRI].m_iNumQuickAnalysisPeriods = 0;

		int iNumRuns = iNumSDDSimInfo;	// was: (bHaveRun2 ? 2 : 1);
		for (iRun=0; (lRetVal == 0 && iRun < iNumRuns); iRun++)
		{	if (iNumRuns < 2)
				sRunName = " ";
			else
				sRunName = boost::str( boost::format( " (%s of %d) " ) % pszRunNums[iRun] % iNumRuns );
			int iProgModel = paSDDSimInfo[iRun]->iProgressModel;
			iProgressModelSum += iProgModel;

			try		// SAC 1/22/14 - added try/catch block to attempt more graceful handling of errors encountered in OpenStudio
			{	QuickAnalysisInfo* pQSim = paSDDSimInfo[iRun]->pQuickAnalysisInfo;
				openstudio::sdd::ReverseTranslator reverseTranslator;

										if (pMsgCallback)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Loading SDD model%sinto reverse translator..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  1 /*action*/ ) == -1);
										}

				model[iRun] = reverseTranslator.loadModel( inputPathFile[iRun], /*true /allowGUI/,*/ NULL /*ProgressBar**/ );  // second argument true will collect BCL key
				if(model[iRun] && !bAbort)
				{
										if (pMsgCallback && !bAbort)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Saving OSM%sfile..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  2 /*action*/ ) == -1);
										}

// SAC 5/23/14 - BEFORE saving OSM, go through each surface to ensure that the polygon vertices are in the order that EnergyPlus will expect
					for( openstudio::model::PlanarSurface planarSurface : model[iRun]->getModelObjects<openstudio::model::PlanarSurface>() )
					{	openstudio::Point3dVector vertices = openstudio::reorderULC(planarSurface.vertices());
						planarSurface.setVertices(vertices);
					}

					osmPath[iRun] = inputPathFile[iRun].replace_extension(openstudio::toPath("osm").string());
					try
					{	model[iRun]->save(osmPath[iRun], true);

						int iIDFBaseLastDot = (int) inputPathString[iRun].rfind('.');
						std::string sIDFBasePath = (iIDFBaseLastDot > 0 ? inputPathString[iRun].substr( 0, iIDFBaseLastDot ) : inputPathString[iRun] );

										if (pMsgCallback)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Loading OpenStudio model%sinto forward translator (to IDF)..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  1 /*action*/ ) == -1);
										}

					// code added to ALSO translate and write IDF file, while we still have OSM loaded (rather than re-loading OSM later to generate IDF)
						openstudio::energyplus::ForwardTranslator forwardTranslator;
						forwardTranslator.setKeepRunControlSpecialDays(true);
						forwardTranslator.setIPTabularOutput(true);
						forwardTranslator.setExcludeLCCObjects(true);
						openstudio::Workspace workspace = forwardTranslator.translateModel( *model[iRun] );

						if (bOutputDiagnostics)		// SAC 4/2/15
						{	openstudio::IdfObject idfOutDiag( openstudio::IddObjectType::Output_Diagnostics );
							idfOutDiag.setString( 0, "DisplayExtraWarnings" );
							workspace.addObject( idfOutDiag );
						}

				//		EXPECT_EQ(0u, forwardTranslator.errors().size());
				//		EXPECT_EQ(1u,workspace.getObjectsByType(IddObjectType::Version).size());
						idfPath[     m_iNumEPSims] = openstudio::toPath( boost::str( boost::format("%s.idf") % sIDFBasePath ) );
						pRunData[m_iNumEPSims]->sRunSubdir = paSDDSimInfo[iRun]->pszRunSubdir;
						pRunData[m_iNumEPSims]->iRunIdx = iRun;
						baSimulate[ m_iNumEPSims] = (paSDDSimInfo[iRun]->bSimulateModel);
						if (baSimulate[m_iNumEPSims])
							iNumSimsToExecute++;
						if (baSimulate[m_iNumEPSims])
							openstudio::removeDirectory(procPath/openstudio::toPath( pRunData[m_iNumEPSims]->sRunSubdir ));
						pqsRunPeriodInfo[m_iNumEPSims] = &qsRunPeriodInfo[iRun];

						bool bInstallQSimRunPeriod = (paSDDSimInfo[iRun]->bStoreHourlyResults && pQSim && pQSim->m_iNumQuickAnalysisPeriods > 0 &&
																(paSDDSimInfo[iRun]->pszIDFToSimulate==NULL || strlen( paSDDSimInfo[iRun]->pszIDFToSimulate )<1) );
						if (bInstallQSimRunPeriod)
						{
							pRunData[m_iNumEPSims]->fResultMult = pQSim->m_fQuickAnalysisResultsMult;

			// REMOVE any existing Run Periods (should always be just one)
							std::vector<openstudio::WorkspaceObject> runPeriods = workspace.getObjectsByType(openstudio::IddObjectType::RunPeriod);
							for(auto runPeriod : runPeriods)
							{	runPeriod.remove();
							}

			// loop over QuickAnalysis run periods and create new E+ RunPeriods
							qsRunPeriodInfo[iRun].m_iNumQuickAnalysisPeriods = pQSim->m_iNumQuickAnalysisPeriods;
							for (int iRP=0; iRP < pQSim->m_iNumQuickAnalysisPeriods; iRP++)
							{
								qsRunPeriodInfo[iRun].m_sRunPeriodName[iRP] = boost::str( boost::format("QuickAnalysis%d Run Period") % (iRP+1) );
								qsRunPeriodInfo[iRun].m_iRunPeriodYrHourOffset[iRP] = siaPriorMonthsHours[pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP]] + ((pQSim->m_iQuickAnalysisPeriodBeginDay[iRP] - 1) * 24);		// hours in year PRIOR to begin of run period
			// SET RUN PERIOD
								boost::optional<openstudio::WorkspaceObject> runPeriod = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::RunPeriod));
								OS_ASSERT(runPeriod);
								int iRPField=0;
								runPeriod->setString( iRPField++, qsRunPeriodInfo[iRun].m_sRunPeriodName[iRP] );
								runPeriod->setInt(    iRPField++, pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP] );
								runPeriod->setInt(    iRPField++, pQSim->m_iQuickAnalysisPeriodBeginDay[  iRP] );
					runPeriod->setInt(    iRPField++, paSDDSimInfo[iRun]->lRunPeriodYear );		// EPlus 9.0.1 - Begin Year
								runPeriod->setInt(    iRPField++, pQSim->m_iQuickAnalysisPeriodEndMonth[  iRP] );
								runPeriod->setInt(    iRPField++, pQSim->m_iQuickAnalysisPeriodEndDay[    iRP] );
					runPeriod->setInt(    iRPField++, paSDDSimInfo[iRun]->lRunPeriodYear );		// EPlus 9.0.1 - End Year
								switch (pQSim->m_iQuickAnalysisPeriodBeginDOWk[iRP])
								{	case  2 :	runPeriod->setString( iRPField++, "Monday"    );	break;
									case  3 :	runPeriod->setString( iRPField++, "Tuesday"   );	break;
									case  4 :	runPeriod->setString( iRPField++, "Wednesday" );	break;
									case  5 :	runPeriod->setString( iRPField++, "Thursday"  );	break;
									case  6 :	runPeriod->setString( iRPField++, "Friday"    );	break;
									case  7 :	runPeriod->setString( iRPField++, "Saturday"  );	break;
									default :	runPeriod->setString( iRPField++, "Sunday"    );	break;
								}
								runPeriod->setString( iRPField++, "No"  );		// !- Use Weather File Holidays and Special Days
								runPeriod->setString( iRPField++, "No"  );		// !- Use Weather File Daylight Saving Period
								runPeriod->setString( iRPField++, "Yes" );		// !- Apply Weekend Holiday Rule
								runPeriod->setString( iRPField++, "Yes" );		// !- Use Weather File Rain Indicators
								runPeriod->setString( iRPField++, "Yes" );		// !- Use Weather File Snow Indicators
					runPeriod->setString( iRPField++, "No"  );		// !- Treat Weather as Actual				// EPlus 9.0.1
					//			runPeriod->setInt(    iRPField++,  1    );		// !- Number of Times Runperiod to be Repeated
			// OLD EPlus
			//					runPeriod->setInt(    1, pQSim->m_iQuickAnalysisPeriodBeginMonth[iRP] );
			//					runPeriod->setInt(    2, pQSim->m_iQuickAnalysisPeriodBeginDay[  iRP] );
			//					runPeriod->setInt(    3, pQSim->m_iQuickAnalysisPeriodEndMonth[  iRP] );
			//					runPeriod->setInt(    4, pQSim->m_iQuickAnalysisPeriodEndDay[    iRP] );
			//					switch (pQSim->m_iQuickAnalysisPeriodBeginDOWk[iRP])
			//					{	case  2 :	runPeriod->setString( 5, "Monday"    );	break;
			//						case  3 :	runPeriod->setString( 5, "Tuesday"   );	break;
			//						case  4 :	runPeriod->setString( 5, "Wednesday" );	break;
			//						case  5 :	runPeriod->setString( 5, "Thursday"  );	break;
			//						case  6 :	runPeriod->setString( 5, "Friday"    );	break;
			//						case  7 :	runPeriod->setString( 5, "Saturday"  );	break;
			//						default :	runPeriod->setString( 5, "Sunday"    );	break;
			//					}
			//					runPeriod->setString(  6, "No"  );		// !- Use Weather File Holidays and Special Days
			//					runPeriod->setString(  7, "No"  );		// !- Use Weather File Daylight Saving Period
			//					runPeriod->setString(  8, "Yes" );		// !- Apply Weekend Holiday Rule
			//					runPeriod->setString(  9, "Yes" );		// !- Use Weather File Rain Indicators
			//					runPeriod->setString( 10, "Yes" );		// !- Use Weather File Snow Indicators
			//					runPeriod->setInt(    11,  1    );		// !- Number of Times Runperiod to be Repeated
						}	}

// SAC 9/30/15 - from OpenStudio code - a work around for E+ v8.3 bug to ensure hourly results output for all defined Meters
			      // this is a workaround for issue #1699
			      bool needsdetailedvariable = false;
			      bool needstimestepvariable = true; // we add these at the bottom of the file
			      bool needshourlyvariable = false;
			      bool needsdailyvariable = false;
			      bool needsmonthlyvariable = false;
			      bool needsrunperiodvariable = false;
			        // this is a workaround for issue #1699
			        // get all the meter requests
			        std::vector<openstudio::WorkspaceObject> meterobjs;
			        std::vector<openstudio::WorkspaceObject> tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_MeterFileOnly);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_Cumulative);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        tempobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Meter_Cumulative_MeterFileOnly);
			        meterobjs.insert(meterobjs.end(), tempobjs.begin(), tempobjs.end());
			        for (const openstudio::WorkspaceObject& meterobj : meterobjs)
			        { // DLM: same index for all types of meters
			          boost::optional<std::string> reportingFrequency = meterobj.getString(openstudio::Output_MeterFields::ReportingFrequency, true);
			          OS_ASSERT(reportingFrequency);
			          if (openstudio::istringEqual(*reportingFrequency, "Detailed")){
			            needsdetailedvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Timestep")){
			            needstimestepvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Hourly")){
			            needshourlyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Daily")){
			            needsdailyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Monthly")){
			            needsmonthlyvariable = true;
			          } else if (openstudio::istringEqual(*reportingFrequency, "RunPeriod") || openstudio::istringEqual(*reportingFrequency, "Environment") || openstudio::istringEqual(*reportingFrequency, "Annual")){
			            needsrunperiodvariable = true;
			          }
			        }
			        // get all the variable requests
			        std::vector<openstudio::WorkspaceObject> variableobjs = workspace.getObjectsByType(openstudio::IddObjectType::Output_Variable);
			        for (const openstudio::WorkspaceObject& variableobj : variableobjs)
			        { boost::optional<std::string> reportingFrequency = variableobj.getString(openstudio::Output_VariableFields::ReportingFrequency, true);
			          OS_ASSERT(reportingFrequency);
			          if (openstudio::istringEqual(*reportingFrequency, "Detailed")){
			            needsdetailedvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Timestep")){
			            needstimestepvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Hourly")){
			            needshourlyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Daily")){
			            needsdailyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "Monthly")){
			            needsmonthlyvariable = false;
			          } else if (openstudio::istringEqual(*reportingFrequency, "RunPeriod") || openstudio::istringEqual(*reportingFrequency, "Environment") || openstudio::istringEqual(*reportingFrequency, "Annual")){
			            needsrunperiodvariable = false;
			          }
			        }
//        ofs << "    HeatRejection:DistrictCooling,  !- Variable or Meter 9 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 9" << std::endl;
//        ofs << "    Humidifier:DistrictCooling,  !- Variable or Meter 10 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 10" << std::endl;
//        ofs << "    HeatRecovery:DistrictCooling,!- Variable or Meter 11 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 11" << std::endl;
//        ofs << "    WaterSystems:DistrictCooling,!- Variable or Meter 12 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum,            !- Aggregation Type for Variable or Meter 12" << std::endl;
//        ofs << "    Cogeneration:DistrictCooling,!- Variable or Meter 13 Name" << std::endl;
//        ofs << "    ValueWhenMaximumOrMinimum;            !- Aggregation Type for Variable or Meter 13" << std::endl;

//OS:Output:Variable,
//  {53396c41-2d2b-4372-9510-246eddcf8b43}, !- Handle
//  Output Variable 1,                      !- Name
//  *,                                      !- Key Value
//  Zone Outdoor Air Drybulb Temperature;   !- Variable Name

//    IddObjectType objType(IddObjectType::Output_Variable);
//    OptionalIddObject oObj = IddObject::load("Output:Variable",
//                                             "Output Reporting",
//                                             ss.str(),
//                                             objType);

			      if (needsdetailedvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Detailed;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Detailed" );
			      }
			      if (needstimestepvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Timestep;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Timestep" );
			      }
			      if (needshourlyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Hourly;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Hourly" );
			      }
			      if (needsdailyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Daily;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Daily" );
			      }
			      if (needsmonthlyvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,Monthly;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "Monthly" );
			      }
			      if (needsrunperiodvariable){
			        //ofs << "    Output:Variable,*,Site Outdoor Air Drybulb Temperature,RunPeriod;" << std::endl;
						boost::optional<openstudio::WorkspaceObject> outVar = workspace.addObject(openstudio::IdfObject(openstudio::IddObjectType::Output_Variable));		OS_ASSERT(outVar);
						outVar->setString( 0, "*" );		outVar->setString( 1, "Site Outdoor Air Drybulb Temperature" );		outVar->setString( 2, "RunPeriod" );
			      }
// SAC 9/30/15 - (end of) from OpenStudio code - a work around for E+ v8.3 bug to ensure hourly results output for all defined Meters

										if (pMsgCallback && !bAbort)
										{	sCallbackMsg = boost::str( boost::format("    OSWrap - Saving IDF%sfile..." ) % sRunName );
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sCallbackMsg.c_str(), OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MTrans, iProgModel, 0 ) ) == -1);   // was:  2 /*action*/ ) == -1);
										}

						try
						{	workspace.save( idfPath[m_iNumEPSims], true /*overwrite*/ );
						}
						catch (std::exception& e)
						{	strErrMsg = boost::str( boost::format("openstudio::Workspace::save() failed%sbecause '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
							lRetVal = OSWrap_SimSDD_OSSaveIDFError + (iRun * 10);
							paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSSaveIDFError;
						}
						catch (...)
						{	strErrMsg = boost::str( boost::format("openstudio::Workspace::save() failed on%sfile:  %s" ) % sRunName % inputPathString );
							lRetVal = OSWrap_SimSDD_OSSaveIDFError + (iRun * 10);
							paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSSaveIDFError;
						}
						m_iNumEPSims++;
					}
					catch (std::exception& e)
					{	strErrMsg = boost::str( boost::format("openstudio::model::Model::save() failed%sbecause '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
						lRetVal = OSWrap_SimSDD_OSSaveOSMError + (iRun * 10);
						paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSSaveOSMError;
					}
					catch (...)
					{	strErrMsg = boost::str( boost::format("openstudio::model::Model::save() failed on%sfile:  %s" ) % sRunName % inputPathString );
						lRetVal = OSWrap_SimSDD_OSSaveOSMError + (iRun * 10);
						paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSSaveOSMError;
				}	}
				else if (!bAbort && lRetVal < 1)
				{	lRetVal = OSWrap_SimSDD_OSModelCreateError + (iRun * 10);  // failure to create OSM (model)
					paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSModelCreateError;
				}
			}
			catch (std::exception& e)
			{	strErrMsg = boost::str( boost::format("openstudio::sdd::ReverseTranslator::loadModel()%sfailed because '%s' on file:  %s" ) % sRunName % e.what() % inputPathString );
				lRetVal = OSWrap_SimSDD_OSLoadModelError + (iRun * 10);
				paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSLoadModelError;
			}
			catch (...)
			{	strErrMsg = boost::str( boost::format("openstudio::sdd::ReverseTranslator::loadModel() failed on%sfile:  %s" ) % sRunName % inputPathString );
				lRetVal = OSWrap_SimSDD_OSLoadModelError + (iRun * 10);
				paSDDSimInfo[iRun]->iSimReturnValue = OSWrap_SimSDD_OSLoadModelError;
			}
		}	// end of for loop over runs

		if (pdTranslationTime)  // SAC 1/23/14
		{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStartTime;
			*pdTranslationTime = ((double) td.total_microseconds()) / 1000000.0;
		}

		if (iNumSimsToExecute > 0 && !bAbort && lRetVal < 1 && bSimViaRunMgr)	// SAC 2/15/19
		{
			lRetVal = OSWrap_SimSDD_InvalidSimData + (iRun * 10);		// SAC 2/19/19 - Invalid simulation input data
// SAC 2/19/19 - sims via openstudio::runmanager no longer an option
//			tmStartTime = boost::posix_time::microsec_clock::local_time();  // SAC 1/23/14
//
//		// now have IDF -> proceed w/ workflow to simulate in E+
//			std::string rmDatabasePath = sProcessingPath + "runmanager.db";
//			openstudio::path rmDBPath = openstudio::toPath(rmDatabasePath);
//// ?? initialize UI ??
//			openstudio::runmanager::RunManager rm( rmDBPath, true /*t_new*/, true /*t_paused*/, false /*t_initializeui*/ ); // Create a RunManager with a new database file
//
//			openstudio::runmanager::ConfigOptions co;
//
//			openstudio::runmanager::Workflow wf;
////			wf.add(co.getTools());   - must add job FIRST or get NULL ptr error
//			openstudio::runmanager::Tools tools = openstudio::runmanager::ConfigOptions::makeTools( epdir,   // energyPlusExePath().parent_path(), 
//																												openstudio::path(), openstudio::path(), openstudio::path(), openstudio::path());
//																											//	t_energyplus, t_xmlpreproc, t_radiance,t_ruby,t_dakota);
//																	//inline openstudio::path energyPlusExePath()
//																	//  return openstudio::toPath("C:/EnergyPlusV7-0-0/EnergyPlus.exe");
//
//			wf.addJob(	openstudio::runmanager::JobType::EnergyPlus);
//			wf.add(tools);
//
//										if (pMsgCallback && !bAbort)
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - Queing EnergyPlus jobs...", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSim, iProgressModelSum, 0 ) ) == -1);   // was:  3 /*action*/ ) == -1);
//
//			if (!bAbort)
//			{
//				openstudio::runmanager::Job jobs[24] = {	openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(),
//																		openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob(), openstudio::runmanager::JobFactory::createNullJob() };
//				int iNumJobs=0;
//		// LOOP OVER ALL OF EPlus Sims (1-24)
//				for (int iESimIdx=0; (!bAbort && iESimIdx < m_iNumEPSims); iESimIdx++)
//					if (baSimulate[iESimIdx])
//					{
//						const char* pszIDFToSim = paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->pszIDFToSimulate;
//					// deal w/ PRE-DEFINED IDF files
//						if (pszIDFToSim && strlen( pszIDFToSim ) > 0 && boost::filesystem::exists(openstudio::toPath(pszIDFToSim)))
//						{	int iCITLastDot = sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].rfind('.');
//							if (iCITLastDot > 0)
//							{	std::string sCopyIDFTo = sProcessingPath + sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].substr( 0, iCITLastDot );
//								sCopyIDFTo += "-fxd.idf";
//								if (boost::filesystem::exists( sCopyIDFTo ))
//									boost::filesystem::remove(  sCopyIDFTo );
//								boost::filesystem::copy_file( pszIDFToSim, sCopyIDFTo );
//								if (boost::filesystem::exists( sCopyIDFTo ))
//								{	//bSimulatePredefinedIDF[0] = true;
//									idfPath[iESimIdx] = openstudio::toPath( sCopyIDFTo );
////									osmPath[0] = openstudio::toPath( sCopyIDFTo );
////									saEPlusSubdir[0] = "EnergyPlus";
//						}	}	}
//						// ?? OS_ASSERT( (!bHaveRun2 || bSimulatePredefinedIDF[0] == bSimulatePredefinedIDF[1]) );	// if this is not the case, then we may need to fiddle w/ the workflow/jobs...
//
//			//			openstudio::runmanager::Job job1 = wf.create( procPath/openstudio::toPath(pszRunSubdir) /*procPath*/, idfPath[0], wthrPathFile[0] /*"path/to/epws"*/ );
//			//			openstudio::runmanager::Job job2 = wf.create( procPath/openstudio::toPath( (bHaveRun2 ? pszRunSubdir2 : pszRunSubdir) ) /*procPath*/, (bHaveRun2 ? idfPath[1] : idfPath[0]),
//			//																												(bHaveRun2 ? wthrPathFile[1] : wthrPathFile[0]) /*"path/to/epws"*/ );
//			//			rm.enqueue(job1, true /*force? */ );
//			//			if (bHaveRun2)
//			//				rm.enqueue(job2, true /*force? */ );
//
//						jobs[iNumJobs] = wf.create( procPath/openstudio::toPath( pRunData[iESimIdx]->sRunSubdir ) /*procPath*/, idfPath[iESimIdx], wthrPathFile[pRunData[iESimIdx]->iRunIdx] /*"path/to/epws"*/ );
//						rm.enqueue(jobs[iNumJobs], true /*force? */ );
//						iNumJobs++;
//					}
//
//// SAC 9/5/14 - experiment w/ tracking simulation status
////	openstudio::runmanager::RunManagerWatcher rmWatch( rm );
////	spRunMgrWatcher = &rmWatch;
////	suuidRunMgrJobs[0] = job1.uuid();
////	suuidRunMgrJobs[1] = (bHaveRun2 ? job2.uuid() : 0);
////	suuidRunMgrJobs[2] = suuidRunMgrJobs[3] = suuidRunMgrJobs[4] = suuidRunMgrJobs[5] = 0;
//
//				rm.setPaused(false);
//				rm.waitForFinished(); // Block until the runamanger has completed running all jobs
//
//// SAC 9/5/14 - experiment w/ tracking simulation status
////	suuidRunMgrJobs[0] = suuidRunMgrJobs[1] = suuidRunMgrJobs[2] = suuidRunMgrJobs[3] = suuidRunMgrJobs[4] = suuidRunMgrJobs[5] = 0;
////	spRunMgrWatcher = NULL;
//
////QMessageBox msgBox;
////msgBox.setText("Back from performing simulation(s) (following waitForFinished())");		msgBox.exec();
//										if (pMsgCallback && !bAbort)
//											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - Back from ModelToIdf & E+, storing results...", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSimRes, iProgressModelSum, 0 ) ) == -1);   // was:  4 /*action*/ ) == -1);
//
//				if (pdSimulationTime)  // SAC 1/23/14
//				{	boost::posix_time::time_duration td = boost::posix_time::microsec_clock::local_time() - tmStartTime;
//					*pdSimulationTime = ((double) td.total_microseconds()) / 1000000.0;
//				}
//
//				for (int ij=0; ij < iNumJobs; ij++)
//				{	openstudio::runmanager::JobErrors treeErrors = jobs[ij].treeErrors(); // represents the state of the job tree
//					if (!treeErrors.succeeded())
//					{
//						// something went wrong, look at treeErrors.errors(), treeErrors.warnings(), job.allOutputFiles().getAllByFilename("stderr")
//						// for more info
//				}	}
//			}
		}
	}

	if (strErrMsg.size() > 0 && pszErrorMsg && iErrorMsgLen > 1)  // SAC 1/30/14
	{	// check error string for paths specific to development machines, and blast that info to reduce size (and for privacy)
		size_t iOSIdx = strErrMsg.find( "\\OpenStudio\\" );
		size_t iPathBeginIdx = (iOSIdx == std::string::npos ? std::string::npos : strErrMsg.rfind( ":\\", iOSIdx-1 ));
		if (iOSIdx != std::string::npos && iPathBeginIdx != std::string::npos)
		{	while (--iPathBeginIdx >= 0 && strErrMsg.at( iPathBeginIdx ) != 39)
			{ }
			if (iPathBeginIdx > 0 && iPathBeginIdx < (iOSIdx-1))
				strErrMsg.replace( iPathBeginIdx+1, iOSIdx-iPathBeginIdx-1, "..." );
			else
			{	OS_ASSERT( false );
		}	}
		strncpy_s( pszErrorMsg, iErrorMsgLen, strErrMsg.c_str(), _TRUNCATE );
	}

   return (bAbort ? OSWrap_SimSDD_UserAbortedAnalysis : lRetVal);
}


// return values:  0 => SUCCESS
//                >0 => user abort or error - refer to #defines listed in OS_Wrap.h
long OSWrapLib::ProcessResults_Multiple(	const char* pszEPlusPath, const char* pszProcessingPath,
														OSWrap_SimInfo** paSDDSimInfo, int iNumSDDSimInfo,
														OSWRAP_MSGCALLBACK* pMsgCallback /*=NULL*/, int iMsgCallbackType /*=0*/,
														char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, int iCodeType /*=0*/, double dEPlusVerNum /*=-1*/ )
{
	long lRetVal = 0;
	bool bAbort = false;
	int iRun = 0;

	std::string sProcessingPath = pszProcessingPath;
	std::string sEPlusSubdir = "EnergyPlus";		// std::string saEPlusSubdir[24];  // = { "EnergyPlus", "EnergyPlus" };
	std::string strErrMsg;
#ifdef _DEBUG  //VS19 - SAC 10/14/20
   	std::string sDbg = boost::str( boost::format("      inside OSWrapLib::ProcessResults_Multiple() on %d run(s)") % iNumSDDSimInfo );
		if (pMsgCallback && !bAbort)
			bAbort = (pMsgCallback( iCodeType, 0 /*level*/, sDbg.c_str(), 0 ) == -1); 
#endif  //VS19

		bool baFirstQSRun[24]  = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };
		bool baLastQSRun[24]   = { true, true, true, true, true, true, true, true, true, true, true, true,   true, true, true, true, true, true, true, true, true, true, true, true };

		int iProgressModelSum = 0;
		for (iRun=0; (lRetVal == 0 && iRun < iNumSDDSimInfo); iRun++)
		{	iProgressModelSum += paSDDSimInfo[iRun]->iProgressModel;
		}

	// PROCESS SIMULATION RESULTS
		bool bProcResultsOK = false;
//		if(iNumSimsToExecute > 0 && !bAbort && lRetVal < 1 && pData[0])
		if (pData[0])
		{
			for (int iESimIdx=0; (!bAbort && iESimIdx < m_iNumEPSims); iESimIdx++)
//				if (baSimulate[iESimIdx])
				if (paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->bSimulateModel)
				{
		// check for simulation warnings/errors
				//	int iLastDot = sIDFPath.rfind('.');   // sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].rfind('.');
				//	int iLastSpc = sIDFPath.rfind(' ');   // sSDDXMLFile[pRunData[iESimIdx]->iRunIdx].rfind(' ');

								//	std::string sDbgMsg = boost::str( boost::format("%s / dot @ %d / space @ %d") % sSDDXMLFile % iLastDot % iLastSpc );
								//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );

								OS_ASSERT( pRunData[iESimIdx]->iRunIdx >= 0 && pRunData[iESimIdx]->iRunIdx < OSW_MaxNumSims );
						std::string sErrPathFile = boost::str( boost::format("%s%s\\%s\\eplusout.err") 
																				% sProcessingPath % pRunData[iESimIdx]->sRunSubdir % sEPlusSubdir );
						openstudio::path errPathFile = openstudio::toPath( sErrPathFile );
						openstudio::energyplus::ErrorFile errorFile( errPathFile );
						pData[pRunData[iESimIdx]->iRunIdx]->sSimErrPathFile   = sErrPathFile;
						pData[pRunData[iESimIdx]->iRunIdx]->saSimWarnings     = errorFile.warnings();
						pData[pRunData[iESimIdx]->iRunIdx]->saSimSevereErrors = errorFile.severeErrors();
						pData[pRunData[iESimIdx]->iRunIdx]->saSimFatalErrors  = errorFile.fatalErrors();
						pData[pRunData[iESimIdx]->iRunIdx]->bSimCompleted              = errorFile.completed();
						pData[pRunData[iESimIdx]->iRunIdx]->bSimCompletedSuccessfully  = errorFile.completedSuccessfully();
		//		pData[pRunData[iESimIdx]->iRunIdx]->bSimCompleted              = true;
		//		pData[pRunData[iESimIdx]->iRunIdx]->bSimCompletedSuccessfully  = true;
   
						std::string sTblOutputPathFile = boost::str( boost::format("%s%s\\%s\\eplustbl.htm") 
																				% sProcessingPath % pRunData[iESimIdx]->sRunSubdir % sEPlusSubdir );
						pData[pRunData[iESimIdx]->iRunIdx]->sSimVersionID = ParseEnergyPlusTablesForVersionID( sTblOutputPathFile );
		//		pData[pRunData[iESimIdx]->iRunIdx]->sSimVersionID = "Windows-32 8.1.0.009";

#ifdef _DEBUG  //VS19 - SAC 10/14/20
		if (pMsgCallback && !bAbort)
			bAbort = (pMsgCallback( iCodeType, 0 /*level*/, boost::str( boost::format("      sim info: iESimIdx %d | Warn/Severe/Fatal %d/%d/%d | Completed/Success %d/%d")
                                       % iESimIdx % pData[pRunData[iESimIdx]->iRunIdx]->saSimWarnings.size() % pData[pRunData[iESimIdx]->iRunIdx]->saSimSevereErrors.size() % pData[pRunData[iESimIdx]->iRunIdx]->saSimFatalErrors.size()
                                       % pData[pRunData[iESimIdx]->iRunIdx]->bSimCompleted % pData[pRunData[iESimIdx]->iRunIdx]->bSimCompletedSuccessfully ).c_str(), 0 ) == -1); 
#endif  //VS19

								//	sDbgMsg = boost::str( boost::format("ERR file: %s\n# Warnings:  %d\n# Severe Errors:  %d\n# Fatal Errors:  %d\nSim Completed:  %s\nSim Successful:  %s")
								//									% sErrPathFile % pRunData->saSimWarnings.size() % pRunData->saSimSevereErrors.size() % pRunData->saSimFatalErrors.size()
								//									% (errorFile.completed() ? "TRUE" : "FALSE") % (errorFile.completedSuccessfully() ? "TRUE" : "FALSE") );
								//	::MessageBox( NULL, sDbgMsg.c_str(), NULL, MB_ICONEXCLAMATION );
								
								//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
								//  EXPECT_EQ(static_cast<unsigned>(8),  errorFile.severeErrors().size());
								//  EXPECT_EQ(static_cast<unsigned>(1),  errorFile.fatalErrors().size());
								
								//  ASSERT_EQ(static_cast<unsigned>(46), errorFile.warnings().size());
								//  EXPECT_EQ("Output:PreprocessorMessage=\"EPXMLPreProc2\" has the following Warning conditions: Requested glazing exceeds available area for B6CCD5_window_1.  Reducing sill height to fit.", 
								//            errorFile.warnings()[0]);
								//  EXPECT_EQ(static_cast<unsigned>(8), errorFile.severeErrors().size());
								//  EXPECT_EQ(static_cast<unsigned>(1), errorFile.fatalErrors().size());
								//  EXPECT_TRUE(errorFile .completed();
								//  EXPECT_FALSE(errorFile.completedSuccessfully();
   
						if (pData[pRunData[iESimIdx]->iRunIdx]->saSimFatalErrors.size() > 0)
						{	lRetVal = OSWrap_SimSDD_SimFatalError + (pRunData[iESimIdx]->iRunIdx * 5);  // Fatal errors occurred in simulation
							paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->iSimReturnValue = OSWrap_SimSDD_SimFatalError;
						}
						else if (!errorFile.completedSuccessfully())
						{	lRetVal = OSWrap_SimSDD_SimIncomplete + (pRunData[iESimIdx]->iRunIdx * 5);  // Simulation did not complete successfully
							paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->iSimReturnValue = OSWrap_SimSDD_SimIncomplete;
						}

		         if (lRetVal < 1 && !bAbort)
					{	//std::string sIDFFile = openstudio::toString(idfPath[iESimIdx]);
						bProcResultsOK = ProcessSimulationResults( this, lRetVal, pRunData[iESimIdx]->iRunIdx, model[pRunData[iESimIdx]->iRunIdx], sProcessingPath, /*sSDDXMLFile[pRunData[iESimIdx]->iRunIdx],*/ sEPlusSubdir,
														pRunData[iESimIdx]->sRunSubdir.c_str(), paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->pszSQLOutPathFile, FILENAME_MAX,
														paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->pdResults, paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->bStoreHourlyResults,
														paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->bWriteHourlyDebugCSV, paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->bWriteCustomMetersHourlyCSV,     // SAC 10/04/21
                                          openstudio::toString(idfPath[iESimIdx]).c_str(),
														baFirstQSRun[iESimIdx], baLastQSRun[iESimIdx], pqsRunPeriodInfo[iESimIdx], pRunData[iESimIdx]->fResultMult,
														paSDDSimInfo[pRunData[iESimIdx]->iRunIdx]->lRptFuelUseAs, pszEPlusPath, dEPlusVerNum, pMsgCallback );								OS_ASSERT( bProcResultsOK );

#ifdef _DEBUG  //VS19 - SAC 10/14/20
		if (pMsgCallback && !bAbort)
			bAbort = (pMsgCallback( iCodeType, 0 /*level*/, boost::str( boost::format("      inside OSWrapLib::ProcessResults_Multiple() - back from ProcessSimulationResults(), returned %d") % bProcResultsOK ).c_str(), 0 ) == -1); 
#endif  //VS19

					}
				}
		}
//	}

										if (pMsgCallback && !bAbort)
											bAbort = (pMsgCallback( iCodeType, 0 /*level*/, "    OSWrap - returning", OSW_NRP_ComplianceProgressID( iMsgCallbackType, OSW_NRP_Step_MSimRes, iProgressModelSum, 0 ) ) == -1);   // was:  5 /*action*/ ) == -1);

	if (strErrMsg.size() > 0 && pszErrorMsg && iErrorMsgLen > 1)  // SAC 1/30/14
	{	// check error string for paths specific to development machines, and blast that info to reduce size (and for privacy)
		size_t iOSIdx = strErrMsg.find( "\\OpenStudio\\" );
		size_t iPathBeginIdx = (iOSIdx == std::string::npos ? std::string::npos : strErrMsg.rfind( ":\\", iOSIdx-1 ));
		if (iOSIdx != std::string::npos && iPathBeginIdx != std::string::npos)
		{	while (--iPathBeginIdx >= 0 && strErrMsg.at( iPathBeginIdx ) != 39)
			{ }
			if (iPathBeginIdx > 0 && iPathBeginIdx < (iOSIdx-1))
				strErrMsg.replace( iPathBeginIdx+1, iOSIdx-iPathBeginIdx-1, "..." );
			else
			{	OS_ASSERT( false );
		}	}
		strncpy_s( pszErrorMsg, iErrorMsgLen, strErrMsg.c_str(), _TRUNCATE );
	}

   return (bAbort ? OSWrap_SimSDD_UserAbortedAnalysis : lRetVal);
}


long OSWrapLib::HourlyResultsRetrieval( const char* pszOSMPathFile, const char* pszSQLPathFile )
{  long lRetVal = 0;
//	boost::optional<openstudio::model::Model> model = reverseTranslator.loadModel( inputPathFile, /*true /allowGUI/,*/ NULL /*ProgressBar**/ );  // second argument true will collect BCL key
//  static boost::optional<Model> load(const path& p);
	openstudio::path osmPathFile = openstudio::toPath(pszOSMPathFile);
	openstudio::path sqlPathFile = openstudio::toPath(pszSQLPathFile);
	if (!boost::filesystem::exists(osmPathFile))
		lRetVal = -1;
	else if (!boost::filesystem::exists(sqlPathFile))
		lRetVal = -2;
	else
	{	boost::optional<openstudio::model::Model> locModel = openstudio::model::Model::load( osmPathFile );
		if(locModel)
		{

//sqlite3_initialize();   // workaround for sqlite3 bug in OpenStudio - SAC 10/21/20

			openstudio::SqlFile sqlFile( sqlPathFile );  //.fullPath);
			//ASSERT_TRUE(sqlFile.connectionOpen());

			locModel->setSqlFile(sqlFile);

	std::string sDbgFN = pszOSMPathFile;
	sDbgFN = sDbgFN.substr( 0, sDbgFN.rfind('.') );
	sDbgFN += " - HrlyMtr.csv";
   FILE *dbgFile = fopen( sDbgFN.c_str(), "wt" ); 
	char sDbg[128];
   if (dbgFile)
   {	sprintf( sDbg, "#,EndUseType,SpecificEndUse,FuelType,Frequency\n" );
		fprintf( dbgFile, sDbg );
	}

			openstudio::model::RunPeriod runPeriod = locModel->getUniqueModelObject<openstudio::model::RunPeriod>();
			std::string sRPName;
			sRPName = runPeriod.name().get();
		//	boost:to_upper(sRPName);
			std::transform( sRPName.begin(), sRPName.end(), sRPName.begin(), ::toupper );

			std::string sEU, sFuel, sFreq, sStatus;
	//		double daFuelConvert[3] = {	(947.817 / 3412140000),			// G(?)J -> kWh
	//												(947.817 / 100000000000),		// G(?)J -> therms
	//												(947.817 / 100000000000) };
		//	boost::optional<std::string> soSpecEnduse;  //, soSpecLocation;
			std::string sSpecEnduse;  //, sSpecLocation;
			openstudio::model::OutputMeterVector meters = locModel->getModelObjects<openstudio::model::OutputMeter>();
			for(const openstudio::model::OutputMeter& meter : meters)
			{
				bool bSuccess = false;
				sStatus = "unknown";
//				if (meter.installLocationType() && (InstallLocationType::Building == meter.installLocationType().get().value())){
//					result.push_back(meter);

				sSpecEnduse.erase();
				boost::optional<std::string> soSpecEnduse;  //, soSpecLocation;
				soSpecEnduse   = meter.specificEndUse();         
				if (soSpecEnduse)
					sSpecEnduse = *soSpecEnduse;
//				soSpecLocation = meter.specificInstallLocation();

				//std::string sEU = meter.endUseType();
				boost::optional<openstudio::EndUseType> euType = meter.endUseType();
				int iEU = -1;
				//std::string sEU = openstudio::model::OutputMeter::EndUseType(*euType).valueName();
				     if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.empty()                                                )   {  sEU = "InteriorLights";             iEU =  0;  }  //  6;  }
				else if (*euType == openstudio::EndUseType::ExteriorLights         && sSpecEnduse.empty()                                                )   {  sEU = "ExteriorLights";             iEU =  1;  }  // 10;  }
				else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.empty()                                                )   {  sEU = "InteriorEquipment";          iEU =  2;  }  //  7;  }
				else if (*euType == openstudio::EndUseType::ExteriorEquipment      && sSpecEnduse.empty()                                                )   {  sEU = "ExteriorEquipment";          iEU =  3;  }  // 10;  }
				else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.empty()                                                )   {  sEU = "Fans";                       iEU =  4;  }  //  2;  }
				else if (*euType == openstudio::EndUseType::Pumps                  && sSpecEnduse.empty()                                                )   {  sEU = "Pumps";                      iEU =  5;  }  //  4;  }
				else if (*euType == openstudio::EndUseType::Heating                && sSpecEnduse.empty()                                                )   {  sEU = "Heating";                    iEU =  6;  }  //  0;  }
				else if (*euType == openstudio::EndUseType::Cooling                && sSpecEnduse.empty()                                                )   {  sEU = "Cooling";                    iEU =  7;  }  //  1;  }
				else if (*euType == openstudio::EndUseType::HeatRejection          && sSpecEnduse.empty()                                                )   {  sEU = "HeatRejection";              iEU =  8;  }  //  3;  }
				else if (*euType == openstudio::EndUseType::Humidifier             && sSpecEnduse.empty()                                                )   {  sEU = "Humidifier";                 iEU =  9;  }  // -1;  }  // ??
				else if (*euType == openstudio::EndUseType::HeatRecovery           && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecovery";               iEU = 10;  }  // -1;  }  // ??
				else if (*euType == openstudio::EndUseType::WaterSystems           && sSpecEnduse.empty()                                                )   {  sEU = "DHW";                        iEU = 11;  }  //  5;  }
				else if (*euType == openstudio::EndUseType::Cogeneration           && sSpecEnduse.empty()                                                )   {  sEU = "Cogeneration";               iEU = 12;  }  // -1;  }  // ??
				else if (*euType == openstudio::EndUseType::Refrigeration          && sSpecEnduse.empty()                                                )   {  sEU = "Refrigeration";              iEU = 13;  }  //  8;  }  // ??
		//		else if (*euType == openstudio::EndUseType::Miscellaneous          && sSpecEnduse.empty()                                                )   {  sEU = "Miscellaneous";              iEU = 14;  }  //  7;  }
				else if (*euType == openstudio::EndUseType::HeatingCoils           && sSpecEnduse.empty()                                                )   {  sEU = "HeatingCoils";               iEU = 14;  }  //  0;  }
				else if (*euType == openstudio::EndUseType::CoolingCoils           && sSpecEnduse.empty()                                                )   {  sEU = "CoolingCoils";               iEU = 15;  }  //  1;  }
				else if (*euType == openstudio::EndUseType::Boilers                && sSpecEnduse.empty()                                                )   {  sEU = "Boilers";                    iEU = 16;  }  //  8;  }  // ??
				else if (*euType == openstudio::EndUseType::Baseboard              && sSpecEnduse.empty()                                                )   {  sEU = "Baseboard";                  iEU = 17;  }  //  0;  }
				else if (*euType == openstudio::EndUseType::HeatRecoveryForCooling && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecoveryForCooling";     iEU = 18;  }  //  1;  }  // ??
				else if (*euType == openstudio::EndUseType::HeatRecoveryForHeating && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecoveryForHeating";     iEU = 19;  }  //  0;  }  // ??
				else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+1][1])==0)   {  sEU = "InteriorLights-Comp";        iEU = HrlyEUs_LastUniqueEU+1;  }  // sEU = "InteriorLights",     "ComplianceLtg"       iEU =  6;  }	// SAC 11/7/15 - 'Reg Ltg' -> 'ComplianceLtg' (SF tic 544)      
				else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+2][1])==0)   {  sEU = "InteriorLights-NonComp";     iEU = HrlyEUs_LastUniqueEU+2;  }  // sEU = "InteriorLights",     "NonComplianceLtg"    iEU =  6;  }	// SAC 11/7/15 - 'NonReg Ltg' -> 'NonComplianceLtg' (SF tic 544)
				else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+3][1])==0)   {  sEU = "InteriorEquipment-Recept.";  iEU = HrlyEUs_LastUniqueEU+3;  }  // sEU = "InteriorEquipment",  "Receptacle"          iEU =  6;  }
				else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+4][1])==0)   {  sEU = "InteriorEquipment-Process";  iEU = HrlyEUs_LastUniqueEU+4;  }  // sEU = "InteriorEquipment",  "Process"             iEU =  6;  }
				else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+5][1])==0)   {  sEU = "InteriorEquipment-Refrig" ;  iEU = HrlyEUs_LastUniqueEU+5;  }  // sEU = "InteriorEquipment",  "Refrig"              iEU =  6;  }
				else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+6][1])==0)   {  sEU = "InteriorEquipment-IntTrans"; iEU = HrlyEUs_LastUniqueEU+6;  }  // sEU = "InteriorEquipment",  "Internal Transport"  iEU =  6;  }
				else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+7][1])==0)   {  sEU = "Fans-ProcessMotors";         iEU = HrlyEUs_LastUniqueEU+7;  }  // sEU = "Fans",               "ProcessMotors"   iEU =  7;  }  // SAC 1/30/17  // SAC 8/14/17
				else  {	sEU = "<unknown_EndUseType>";		}  // ASSERT( FALSE );		}

				boost::optional<openstudio::FuelType> fType = meter.fuelType();
				int iFl = -1;
				//std::string sFuel = openstudio::model::OutputMeter::FuelType(*fType).valueName();
				     if (*fType == openstudio::FuelType::Electricity    )   {  sFuel = "Electricity";      iFl =  0;  } 
				else if (*fType == openstudio::FuelType::Gas            )   {  sFuel = "Gas";              iFl =  1;  } 
				else if (*fType == openstudio::FuelType::Gasoline       )   {  sFuel = "Gasoline";         iFl =  2;  }   
				else if (*fType == openstudio::FuelType::Diesel         )   {  sFuel = "Diesel";           iFl =  2;  }   
				else if (*fType == openstudio::FuelType::FuelOil_1      )   {  sFuel = "FuelOil_1";        iFl =  2;  }   
				else if (*fType == openstudio::FuelType::FuelOil_2      )   {  sFuel = "FuelOil_2";        iFl =  2;  }   
				else if (*fType == openstudio::FuelType::Propane        )   {  sFuel = "Propane";          iFl =  2;  }   
				else if (*fType == openstudio::FuelType::Water          )   {  sFuel = "Water";            iFl = -1;  }  // ??
				else if (*fType == openstudio::FuelType::Steam          )   {  sFuel = "Steam";            iFl = -1;  }  // ??
				else if (*fType == openstudio::FuelType::DistrictCooling)   {  sFuel = "DistrictCooling";  iFl = -1;  }  // ??
				else if (*fType == openstudio::FuelType::DistrictHeating)   {  sFuel = "DistrictHeating";  iFl = -1;  }  // ??
				else if (*fType == openstudio::FuelType::EnergyTransfer )   {  sFuel = "EnergyTransfer";   iFl = -1;  }  // ??
				else  {	sFuel = "<unknown_FuelType>";			}  // ASSERT( FALSE );		}

				sSpecEnduse = "<none>";
				sFreq = meter.reportingFrequency();
//        if (istringEqual(meter.reportingFrequency(),reportingFrequency)) {
//  EXPECT_EQ("Hourly", meter.reportingFrequency());

				double dEUTot=0.0;
				if (boost::iequals( sFreq, "hourly"))
				{
					boost::optional<openstudio::TimeSeries> timeSeries = meter.getData( sRPName );  // runPeriod.name().get());
					if (timeSeries)
					{
						openstudio::Vector values = timeSeries->values();
						unsigned numValues = (unsigned) values.size();
						//ASSERT( numValues==0 || numValues==8760 );
						//pData->daHourlyResults[0][0];  // Fuel / Enduse
						if (numValues != 8760)
						{	//ASSERT( FALSE );
							//int iErrHere = 1;
							sStatus = boost::str( boost::format("NumHrlyVals = %d") % numValues );
						}
						else
						{	dEUTot=0.0;
							for (unsigned i = 0; i < numValues; ++i)
							{
								dEUTot += values(i);
		//						pData->daHourlyResults[iFl][iEU][i] = values(i);
							}

							sStatus = "success";
							bSuccess = true;
							lRetVal++;

						}
					}
					else
						sStatus = "error retrieving TimeSeries";
				}
				else
					sStatus = boost::str( boost::format("MtrFreq = '%s'") % sFreq );


   if (dbgFile)
	{	if (bSuccess)
			sprintf( sDbg, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",%s,%g\n", lRetVal, sEU.c_str(), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str(), dEUTot );
		else
			sprintf( sDbg, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",%s\n", lRetVal, sEU.c_str(), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str() );
//									(sSpecEnduse ? sSpecEnduse->c_str() : ""), (sSpecLocation ? sSpecLocation->c_str() : "") );
		fprintf( dbgFile, sDbg );
	}


//	OPENSTUDIO_ENUM(FuelType,
//	  ((Electricity))
//	  ((Gas)(NaturalGas))
//	  ((Gasoline))
//	  ((Diesel))
//	  ((FuelOil_1))
//	  ((FuelOil_2))
//	  ((Propane))
//	  ((Water))
//	  ((Steam))
//	  ((DistrictCooling))
//	  ((DistrictHeating))
//	  ((EnergyTransfer)));


//std::string Meter::getName(const boost::optional<std::string>& specificEndUseType,
//                           const boost::optional<EndUseType>& endUseType,
//                           const boost::optional<FuelType>& fuelType,
//                           const boost::optional<InstallLocationType>& installLocationType,
//                           const boost::optional<std::string>& specificInstallLocation)
//{
//  std::string result;
//
//  if (specificEndUseType && !specificEndUseType->empty()){
//    result += *specificEndUseType;
//  }
//  if (endUseType){
//    if (!result.empty()){
//      result += ":";
//    }
//    result += EndUseType(*endUseType).valueName();
			}

   if (dbgFile)
   {  fflush( dbgFile );
      fclose( dbgFile );
   }

			sqlFile.close();		// SAC 4/28/19 - close file to ensure subsequent clean-up can delete it
			//Sleep(500);				// SAC 4/29/19 - additional code to pause because close alone not releasing file in time in all cases
		}
	}
	return lRetVal;
}


//  boost::optional<Meter> Facility_Impl::getMeterByFuelType(
//    const FuelType& fuelType,
//    const std::string& reportingFrequency,
//    const boost::optional<EndUseType>& endUseType,
//    const boost::optional<std::string>& specificEndUse) const
//  {
//    OptionalMeter result;
//    for(const Meter& meter : this->meters()) {
//      if (meter.fuelType() && (meter.fuelType() == fuelType)) {
//        if (istringEqual(meter.reportingFrequency(),reportingFrequency)) {
//          OptionalEndUseType meterEndUseType = meter.endUseType();
//          if ((!endUseType && !meterEndUseType) || 
//              (endUseType && meterEndUseType && (*meterEndUseType == *endUseType))) 
//          {
//            OptionalString meterSpecificEndUse = meter.specificEndUse();
//            if ((!specificEndUse && !meterSpecificEndUse) ||
//                (specificEndUse && meterSpecificEndUse && istringEqual(*meterSpecificEndUse,*specificEndUse)))


std::vector<double>* OSWrapLib::GetHourlyResultArray( int iRunIdx, int iFuel, int iEnduse, double* pdTotal )
{
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData != NULL && pLocRunData->bHourlyResultsCurrent)
	{	if (pdTotal)
			*pdTotal = pLocRunData->daHourlyResultsSum[iFuel][iEnduse];
		return &pLocRunData->daHourlyResults[iFuel][iEnduse];
	}
	return NULL;
}


//model = OpenStudio::Model::Model.load( OpenStudio::Path.new('00100-SchoolPrimary-CustomStd-hrlyres - p.osm') ).get()
//
//sql = OpenStudio::SqlFile.new( OpenStudio::Path.new('eplusout.sql') )
//
//model.setSqlFile sql
//
//meters = model.getMeters
//
//meter = nil
//
//meters.each do |m|
//  if m.endUseType.is_initialized and m.fuelType.is_initialized
//    if m.endUseType.get() == OpenStudio::EndUseType.new('InteriorLights')
//      if m.fuelType.get() == OpenStudio::FuelType.new('Electricity')
//        meter = m
//        break
//      end
//    end
//  end
//end
//
//if meter
//  puts meter.name
//
//  # Note the upcase. It is important.
//  time_series = meter.getData(model.getRunPeriod.name.get.upcase)
//
//  puts time_series.get().values
//end
// ----------------------------------------------------------------------


long OSWrapLib::ExportHourlyCustomMeters( const char* pszOSMPathFile, const char* pszSQLPathFile )    // SAC 09/28/21
{  long lRetVal = 0;


//	openstudio::path sqlPathFile = openstudio::toPath(pszSQLPathFile);
//	if (!boost::filesystem::exists(sqlPathFile))
//		lRetVal = -2;
//	else
//	{	   //sqlite3_initialize();   // workaround for sqlite3 bug in OpenStudio - SAC 10/21/20
//			openstudio::SqlFile sqlFile( sqlPathFile );  //.fullPath);
//			//ASSERT_TRUE(sqlFile.connectionOpen());


	openstudio::path osmPathFile = openstudio::toPath(pszOSMPathFile);
	openstudio::path sqlPathFile = openstudio::toPath(pszSQLPathFile);
	if (!boost::filesystem::exists(osmPathFile))
		lRetVal = -1;
	else if (!boost::filesystem::exists(sqlPathFile))
		lRetVal = -2;
	else
	{	boost::optional<openstudio::model::Model> locModel = openstudio::model::Model::load( osmPathFile );
		if(locModel)
		{
         //sqlite3_initialize();   // workaround for sqlite3 bug in OpenStudio - SAC 10/21/20
			openstudio::SqlFile sqlFile( sqlPathFile );  //.fullPath);
			//ASSERT_TRUE(sqlFile.connectionOpen());

			locModel->setSqlFile(sqlFile);

               	std::string sDbgFN = pszOSMPathFile;
               	sDbgFN = sDbgFN.substr( 0, sDbgFN.rfind('.') );
               	sDbgFN += " - CustomMtr.csv";
                  FILE *dbgFile = fopen( sDbgFN.c_str(), "wt" ); 
               	char sDbg[128];
                  if (dbgFile)
                  {	sprintf( sDbg, "#,EndUseType,SpecificEndUse,FuelType,Frequency\n" );
               		fprintf( dbgFile, sDbg );
               	}

			openstudio::model::RunPeriod runPeriod = locModel->getUniqueModelObject<openstudio::model::RunPeriod>();
			std::string sRPName;
			sRPName = runPeriod.name().get();
		   //	boost:to_upper(sRPName);
			std::transform( sRPName.begin(), sRPName.end(), sRPName.begin(), ::toupper );

			std::string sEU, sFuel, sFreq, sStatus, sMtrName;
      	//		double daFuelConvert[3] = {	(947.817 / 3412140000),			// G(?)J -> kWh
      	//												(947.817 / 100000000000),		// G(?)J -> therms
      	//												(947.817 / 100000000000) };
		   //	boost::optional<std::string> soSpecEnduse;  //, soSpecLocation;
			std::string sSpecEnduse;  //, sSpecLocation;
			openstudio::model::MeterCustomVector meters = locModel->getModelObjects<openstudio::model::MeterCustom>();
			for(const openstudio::model::MeterCustom& meter : meters)
			{
				bool bSuccess = false;
				sStatus = "unknown";
				//if (meter.installLocationType() && (InstallLocationType::Building == meter.installLocationType().get().value())){
				//	result.push_back(meter);

            //sMtrName = meter.getName();  // "<meter name>";
            sMtrName = "NonResElecMeter:InteriorLights";

				sSpecEnduse.erase();
				//boost::optional<std::string> soSpecEnduse;  //, soSpecLocation;
				//soSpecEnduse   = meter.specificEndUse();         
				//if (soSpecEnduse)
				//	sSpecEnduse = *soSpecEnduse;

				//boost::optional<openstudio::EndUseType> euType = meter.endUseType();
				//int iEU = -1;
				////std::string sEU = openstudio::model::MeterCustom::EndUseType(*euType).valueName();
				//     if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.empty()                                                )   {  sEU = "InteriorLights";             iEU =  0;  }  //  6;  }
				//else if (*euType == openstudio::EndUseType::ExteriorLights         && sSpecEnduse.empty()                                                )   {  sEU = "ExteriorLights";             iEU =  1;  }  // 10;  }
				//else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.empty()                                                )   {  sEU = "InteriorEquipment";          iEU =  2;  }  //  7;  }
				//else if (*euType == openstudio::EndUseType::ExteriorEquipment      && sSpecEnduse.empty()                                                )   {  sEU = "ExteriorEquipment";          iEU =  3;  }  // 10;  }
				//else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.empty()                                                )   {  sEU = "Fans";                       iEU =  4;  }  //  2;  }
				//else if (*euType == openstudio::EndUseType::Pumps                  && sSpecEnduse.empty()                                                )   {  sEU = "Pumps";                      iEU =  5;  }  //  4;  }
				//else if (*euType == openstudio::EndUseType::Heating                && sSpecEnduse.empty()                                                )   {  sEU = "Heating";                    iEU =  6;  }  //  0;  }
				//else if (*euType == openstudio::EndUseType::Cooling                && sSpecEnduse.empty()                                                )   {  sEU = "Cooling";                    iEU =  7;  }  //  1;  }
				//else if (*euType == openstudio::EndUseType::HeatRejection          && sSpecEnduse.empty()                                                )   {  sEU = "HeatRejection";              iEU =  8;  }  //  3;  }
				//else if (*euType == openstudio::EndUseType::Humidifier             && sSpecEnduse.empty()                                                )   {  sEU = "Humidifier";                 iEU =  9;  }  // -1;  }  // ??
				//else if (*euType == openstudio::EndUseType::HeatRecovery           && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecovery";               iEU = 10;  }  // -1;  }  // ??
				//else if (*euType == openstudio::EndUseType::WaterSystems           && sSpecEnduse.empty()                                                )   {  sEU = "DHW";                        iEU = 11;  }  //  5;  }
				//else if (*euType == openstudio::EndUseType::Cogeneration           && sSpecEnduse.empty()                                                )   {  sEU = "Cogeneration";               iEU = 12;  }  // -1;  }  // ??
				//else if (*euType == openstudio::EndUseType::Refrigeration          && sSpecEnduse.empty()                                                )   {  sEU = "Refrigeration";              iEU = 13;  }  //  8;  }  // ??
				////else if (*euType == openstudio::EndUseType::Miscellaneous          && sSpecEnduse.empty()                                                )   {  sEU = "Miscellaneous";              iEU = 14;  }  //  7;  }
				//else if (*euType == openstudio::EndUseType::HeatingCoils           && sSpecEnduse.empty()                                                )   {  sEU = "HeatingCoils";               iEU = 14;  }  //  0;  }
				//else if (*euType == openstudio::EndUseType::CoolingCoils           && sSpecEnduse.empty()                                                )   {  sEU = "CoolingCoils";               iEU = 15;  }  //  1;  }
				//else if (*euType == openstudio::EndUseType::Boilers                && sSpecEnduse.empty()                                                )   {  sEU = "Boilers";                    iEU = 16;  }  //  8;  }  // ??
				//else if (*euType == openstudio::EndUseType::Baseboard              && sSpecEnduse.empty()                                                )   {  sEU = "Baseboard";                  iEU = 17;  }  //  0;  }
				//else if (*euType == openstudio::EndUseType::HeatRecoveryForCooling && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecoveryForCooling";     iEU = 18;  }  //  1;  }  // ??
				//else if (*euType == openstudio::EndUseType::HeatRecoveryForHeating && sSpecEnduse.empty()                                                )   {  sEU = "HeatRecoveryForHeating";     iEU = 19;  }  //  0;  }  // ??
				//else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+1][1])==0)   {  sEU = "InteriorLights-Comp";        iEU = HrlyEUs_LastUniqueEU+1;  }  // sEU = "InteriorLights",     "ComplianceLtg"       iEU =  6;  }	// SAC 11/7/15 - 'Reg Ltg' -> 'ComplianceLtg' (SF tic 544)      
				//else if (*euType == openstudio::EndUseType::InteriorLights         && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+2][1])==0)   {  sEU = "InteriorLights-NonComp";     iEU = HrlyEUs_LastUniqueEU+2;  }  // sEU = "InteriorLights",     "NonComplianceLtg"    iEU =  6;  }	// SAC 11/7/15 - 'NonReg Ltg' -> 'NonComplianceLtg' (SF tic 544)
				//else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+3][1])==0)   {  sEU = "InteriorEquipment-Recept.";  iEU = HrlyEUs_LastUniqueEU+3;  }  // sEU = "InteriorEquipment",  "Receptacle"          iEU =  6;  }
				//else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+4][1])==0)   {  sEU = "InteriorEquipment-Process";  iEU = HrlyEUs_LastUniqueEU+4;  }  // sEU = "InteriorEquipment",  "Process"             iEU =  6;  }
				//else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+5][1])==0)   {  sEU = "InteriorEquipment-Refrig" ;  iEU = HrlyEUs_LastUniqueEU+5;  }  // sEU = "InteriorEquipment",  "Refrig"              iEU =  6;  }
				//else if (*euType == openstudio::EndUseType::InteriorEquipment      && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+6][1])==0)   {  sEU = "InteriorEquipment-IntTrans"; iEU = HrlyEUs_LastUniqueEU+6;  }  // sEU = "InteriorEquipment",  "Internal Transport"  iEU =  6;  }
				//else if (*euType == openstudio::EndUseType::Fans                   && sSpecEnduse.compare(pszaEplusEnduses[HrlyEUs_LastUniqueEU+7][1])==0)   {  sEU = "Fans-ProcessMotors";         iEU = HrlyEUs_LastUniqueEU+7;  }  // sEU = "Fans",               "ProcessMotors"   iEU =  7;  }  // SAC 1/30/17  // SAC 8/14/17
				//else  {	sEU = "<unknown_EndUseType>";		}  // ASSERT( FALSE );		}

				//boost::optional<openstudio::FuelType> fType = meter.fuelType();
				//int iFl = -1;
				////std::string sFuel = openstudio::model::MeterCustom::FuelType(*fType).valueName();
				//     if (*fType == openstudio::FuelType::Electricity    )   {  sFuel = "Electricity";      iFl =  0;  } 
				//else if (*fType == openstudio::FuelType::Gas            )   {  sFuel = "Gas";              iFl =  1;  } 
				//else if (*fType == openstudio::FuelType::Gasoline       )   {  sFuel = "Gasoline";         iFl =  2;  }   
				//else if (*fType == openstudio::FuelType::Diesel         )   {  sFuel = "Diesel";           iFl =  2;  }   
				//else if (*fType == openstudio::FuelType::FuelOil_1      )   {  sFuel = "FuelOil_1";        iFl =  2;  }   
				//else if (*fType == openstudio::FuelType::FuelOil_2      )   {  sFuel = "FuelOil_2";        iFl =  2;  }   
				//else if (*fType == openstudio::FuelType::Propane        )   {  sFuel = "Propane";          iFl =  2;  }   
				//else if (*fType == openstudio::FuelType::Water          )   {  sFuel = "Water";            iFl = -1;  }  // ??
				//else if (*fType == openstudio::FuelType::Steam          )   {  sFuel = "Steam";            iFl = -1;  }  // ??
				//else if (*fType == openstudio::FuelType::DistrictCooling)   {  sFuel = "DistrictCooling";  iFl = -1;  }  // ??
				//else if (*fType == openstudio::FuelType::DistrictHeating)   {  sFuel = "DistrictHeating";  iFl = -1;  }  // ??
				//else if (*fType == openstudio::FuelType::EnergyTransfer )   {  sFuel = "EnergyTransfer";   iFl = -1;  }  // ??
				//else  {	sFuel = "<unknown_FuelType>";			}  // ASSERT( FALSE );		}
            sFuel.erase();
            boost::optional<std::string> soFuel = meter.fuelType();
				if (soFuel)
					sFuel = *soFuel;

				sSpecEnduse = "<none>";
				sFreq = "hourly";    //meter.reportingFrequency();
            //if (istringEqual(meter.reportingFrequency(),reportingFrequency)) {
            //  EXPECT_EQ("Hourly", meter.reportingFrequency());

				double dEUTot=0.0;
				if (boost::iequals( sFreq, "hourly"))
				{
					//boost::optional<openstudio::TimeSeries> timeSeries = meter.getData( sRPName );  // runPeriod.name().get());
					boost::optional<openstudio::TimeSeries> timeSeries = sqlFile.timeSeries( sRPName, "Hourly", sMtrName, "");
					if (timeSeries)
					{
						openstudio::Vector values = timeSeries->values();
						unsigned numValues = (unsigned) values.size();
						//ASSERT( numValues==0 || numValues==8760 );
						//pData->daHourlyResults[0][0];  // Fuel / Enduse
						if (numValues != 8760)
						{	//ASSERT( FALSE );
							//int iErrHere = 1;
							sStatus = boost::str( boost::format("NumHrlyVals = %d") % numValues );
						}
						else
						{	dEUTot=0.0;
							for (unsigned i = 0; i < numValues; ++i)
							{
								dEUTot += values(i);
								//pData->daHourlyResults[iFl][iEU][i] = values(i);
							}

							sStatus = "success";
							bSuccess = true;
							lRetVal++;

						}
					}
					else
						sStatus = "error retrieving TimeSeries";
				}
				else
					sStatus = boost::str( boost::format("MtrFreq = '%s'") % sFreq );


                     if (dbgFile)
                  	{	if (bSuccess)
                  			sprintf( sDbg, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",%s,%g\n", lRetVal, sEU.c_str(), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str(), dEUTot );
                  		else
                  			sprintf( sDbg, "%ld,\"%s\",\"%s\",\"%s\",\"%s\",%s\n", lRetVal, sEU.c_str(), sSpecEnduse.c_str(), sFuel.c_str(), sFreq.c_str(), sStatus.c_str() );
                           //						(sSpecEnduse ? sSpecEnduse->c_str() : ""), (sSpecLocation ? sSpecLocation->c_str() : "") );
                  		fprintf( dbgFile, sDbg );
                  	}

                  //	OPENSTUDIO_ENUM(FuelType,
                  //	  ((Electricity))
                  //	  ((Gas)(NaturalGas))
                  //	  ((Gasoline))
                  //	  ((Diesel))
                  //	  ((FuelOil_1))
                  //	  ((FuelOil_2))
                  //	  ((Propane))
                  //	  ((Water))
                  //	  ((Steam))
                  //	  ((DistrictCooling))
                  //	  ((DistrictHeating))
                  //	  ((EnergyTransfer)));
			}

                  if (dbgFile)
                  {  fflush( dbgFile );
                     fclose( dbgFile );
                  }

			sqlFile.close();		// SAC 4/28/19 - close file to ensure subsequent clean-up can delete it
			//Sleep(500);				// SAC 4/29/19 - additional code to pause because close alone not releasing file in time in all cases
		}
	}
	return lRetVal;
}
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
//		Simulation Message Retrieval
// ----------------------------------------------------------------------
int  OSWrapLib::GetNum_Warnings( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? -1 : (int) pLocRunData->saSimWarnings.size());
}

int  OSWrapLib::GetNum_SevereErrors( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? -1 : (int) pLocRunData->saSimSevereErrors.size());
}

int  OSWrapLib::GetNum_FatalErrors( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? -1 : (int) pLocRunData->saSimFatalErrors.size());
}

std::string  OSWrapLib::GetMsg_Warning( int iRunIdx, int idx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL || (int) pLocRunData->saSimWarnings.size() <= idx ? "" : pLocRunData->saSimWarnings[idx]);
}

std::string  OSWrapLib::GetMsg_SevereError( int iRunIdx, int idx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL || (int) pLocRunData->saSimSevereErrors.size() <= idx ? "" : pLocRunData->saSimSevereErrors[idx]);
}

std::string  OSWrapLib::GetMsg_FatalError( int iRunIdx, int idx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL || (int) pLocRunData->saSimFatalErrors.size() <= idx ? "" : pLocRunData->saSimFatalErrors[idx]);
}


std::string  OSWrapLib::Get_SimErrPathFile( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? "" : pLocRunData->sSimErrPathFile);
}

std::string  OSWrapLib::Get_SimVersionID( int iRunIdx )	// SAC 5/19/14
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? "" : pLocRunData->sSimVersionID);
}

bool  OSWrapLib::GetBool_SimCompleted( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? false : pLocRunData->bSimCompleted);
}

bool  OSWrapLib::GetBool_SimCompletedSuccessfully( int iRunIdx )
{	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	return (pLocRunData == NULL ? false : pLocRunData->bSimCompletedSuccessfully);
}


// ----------------------------------------------------------------------
//		ZONE results retrieval & storage
// ----------------------------------------------------------------------
int  OSWrapLib::AddResult_Zone( int iRunIdx, const char* pszZoneName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszZoneName == NULL || strlen( pszZoneName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saZone.push_back( pszZoneName );
		iRetVal = (int) pLocRunData->saZone.size();
	}
	return iRetVal;
}
double  OSWrapLib::GetResult_ZoneUMLHClg( int iRunIdx, int idx )
{
	double dRetVal;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		dRetVal = -1;
	else if (idx >= (int) pLocRunData->daZone_UMLHClg.size())
		dRetVal = -2;
	else
		dRetVal = pLocRunData->daZone_UMLHClg[idx];
	return dRetVal;
}
double  OSWrapLib::GetResult_ZoneUMLHHtg( int iRunIdx, int idx )
{
	double dRetVal;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		dRetVal = -1;
	else if (idx >= (int) pLocRunData->daZone_UMLHHtg.size())
		dRetVal = -2;
	else
		dRetVal = pLocRunData->daZone_UMLHHtg[idx];
	return dRetVal;
}

// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_Zone( int iRunIdx, int idx, double* pfZoneResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daZone_UMLHClg.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_UMLHClg[idx];
								break;
				case  1 :	if (idx >= (int) pLocRunData->daZone_UMLHHtg.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_UMLHHtg[idx];
								break;
				case  2 :	if (idx >= (int) pLocRunData->daZone_ClgDsgnLd.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_ClgDsgnLd[idx];
								break;
				case  3 :	if (idx >= (int) pLocRunData->daZone_HtgDsgnLd.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_HtgDsgnLd[idx];
								break;
				case  4 :	if (idx >= (int) pLocRunData->daZone_ClgDsgnFlow.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_ClgDsgnFlow[idx];
								break;
				case  5 :	if (idx >= (int) pLocRunData->daZone_HtgDsgnFlow.size())
									iRetVal = -(i+11);
								else
									pfZoneResults[i] = pLocRunData->daZone_HtgDsgnFlow[idx];
								break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}


int  OSWrapLib::AddResult_Fan( int iRunIdx, const char* pszFanName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszFanName == NULL || strlen( pszFanName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saFan.push_back( pszFanName );
		iRetVal = (int) pLocRunData->saFan.size();
	}
	return iRetVal;
}

// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_Fan( int iRunIdx, int idx, double* pfFanResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daFan_FlowCap.size())
									iRetVal = -(i+11);
								else
									pfFanResults[i] = pLocRunData->daFan_FlowCap[idx];
								break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}


int  OSWrapLib::AddResult_CoilClg( int iRunIdx, const char* pszCoilClgName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszCoilClgName == NULL || strlen( pszCoilClgName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saCoilClg.push_back( pszCoilClgName );
		iRetVal = (int) pLocRunData->saCoilClg.size();
	}
	return iRetVal;
}

// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_CoilClg( int iRunIdx, int idx, double* pfCoilClgResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daCoilClg_TotCap.size())
									iRetVal = -(i+11);
								else
									pfCoilClgResults[i] = pLocRunData->daCoilClg_TotCap[idx];
								break;
				case  1 :	if (idx >= (int) pLocRunData->daCoilClg_SensCap.size())
									iRetVal = -(i+11);
								else
									pfCoilClgResults[i] = pLocRunData->daCoilClg_SensCap[idx];
								break;
	//			case  2 :	if (idx >= (int) pLocRunData->daCoilClg_FluidLdDsgn.size())
				case  2 :	if (idx >= (int) pLocRunData->daCoilClg_FluidFlowRtDsgnSim.size())		// SAC 11/26/13 - added
									iRetVal = -(i+11);
								else
	//								pfCoilClgResults[i] = pLocRunData->daCoilClg_FluidLdDsgn[idx];
									pfCoilClgResults[i] = pLocRunData->daCoilClg_FluidFlowRtDsgnSim[idx];
								break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}


int  OSWrapLib::AddResult_CoilHtg( int iRunIdx, const char* pszCoilHtgName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszCoilHtgName == NULL || strlen( pszCoilHtgName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saCoilHtg.push_back( pszCoilHtgName );
		iRetVal = (int) pLocRunData->saCoilHtg.size();
	}
	return iRetVal;
}

// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_CoilHtg( int iRunIdx, int idx, double* pfCoilHtgResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daCoilHtg_TotCap.size())
									iRetVal = -(i+11);
								else
									pfCoilHtgResults[i] = pLocRunData->daCoilHtg_TotCap[idx];
								break;
	//			case  1 :	if (idx >= (int) pLocRunData->daCoilHtg_FluidLdDsgn.size())
				case  1 :	if (idx >= (int) pLocRunData->daCoilHlg_FluidFlowRtDsgnSim.size())    // SAC 11/26/13 - added
									iRetVal = -(i+11);
								else
	//								pfCoilHtgResults[i] = pLocRunData->daCoilHtg_FluidLdDsgn[idx];
									pfCoilHtgResults[i] = pLocRunData->daCoilHlg_FluidFlowRtDsgnSim[idx];
								break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}






// -----------------------------------------------------
// SAC 8/28/13 - added Blr, Chlr, HtRej & Pump results
// -----------------------------------------------------

int  OSWrapLib::AddResult_Blr( int iRunIdx, const char* pszBlrName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszBlrName == NULL || strlen( pszBlrName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saBlr.push_back( pszBlrName );
		iRetVal = (int) pLocRunData->saBlr.size();
	}
	return iRetVal;
}
// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_Blr( int iRunIdx, int idx, double* pfBlrResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daBlr_CapRtd.size())
									iRetVal = -(i+11);
								else
									pfBlrResults[i] = pLocRunData->daBlr_CapRtd[idx];
								break;
	//			case  1 :	if (idx >= (int) pLocRunData->daBlr_HtgRtPk.size())
	//								iRetVal = -(i+11);
	//							else
	//								pfBlrResults[i] = pLocRunData->daBlr_HtgRtPk[idx];
	//							break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}

int  OSWrapLib::AddResult_Chlr( int iRunIdx, const char* pszChlrName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszChlrName == NULL || strlen( pszChlrName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saChlr.push_back( pszChlrName );
		iRetVal = (int) pLocRunData->saChlr.size();
	}
	return iRetVal;
}
// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_Chlr( int iRunIdx, int idx, double* pfChlrResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daChlr_CapRtd.size())
									iRetVal = -(i+11);
								else
									pfChlrResults[i] = pLocRunData->daChlr_CapRtd[idx];
								break;
	//			case  1 :	if (idx >= (int) pLocRunData->daChlr_EvapClgRtPk.size())
	//								iRetVal = -(i+11);
	//							else
	//								pfChlrResults[i] = pLocRunData->daChlr_EvapClgRtPk[idx];
	//							break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}

int  OSWrapLib::AddResult_HtRej( int iRunIdx, const char* pszHtRejName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszHtRejName == NULL || strlen( pszHtRejName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saHtRej.push_back( pszHtRejName );
		iRetVal = (int) pLocRunData->saHtRej.size();
	}
	return iRetVal;
}
// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_HtRej( int iRunIdx, int idx, double* pfHtRejResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daHtRej_CapRtd.size())
									iRetVal = -(i+11);
								else
									pfHtRejResults[i] = pLocRunData->daHtRej_CapRtd[idx];
								break;
	//			case  1 :	if (idx >= (int) pLocRunData->daHtRej_HtTransRtPk.size())
	//								iRetVal = -(i+11);
	//							else
	//								pfHtRejResults[i] = pLocRunData->daHtRej_HtTransRtPk[idx];
	//							break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}

int  OSWrapLib::AddResult_Pump( int iRunIdx, const char* pszPumpName )
{
	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else if (pszPumpName == NULL || strlen( pszPumpName ) < 1)
		iRetVal = -2;
	else
	{	pLocRunData->saPump.push_back( pszPumpName );
		iRetVal = (int) pLocRunData->saPump.size();
	}
	return iRetVal;
}
// return:  < 0 => error code
//				> 0 => num results retrieved
int  OSWrapLib::GetResult_Pump( int iRunIdx, int idx, double* pfPumpResults, int iNumResults )
{	int iRetVal = 0;
	OSWrapLibData* pLocRunData = ((iRunIdx >= 0 && iRunIdx < OSW_MaxNumSims) ? pData[iRunIdx] : NULL);		// was: (iRunIdx==0 ? pData : (iRunIdx==1 ? pData2 : NULL));
	if (pLocRunData == NULL)
		iRetVal = -1;
	else
	{	for (int i=0; (iRetVal >= 0 && i<iNumResults); i++)
		{	switch (i)
			{	case  0 :	if (idx >= (int) pLocRunData->daPump_FlowCap.size())
									iRetVal = -(i+11);
								else
									pfPumpResults[i] = pLocRunData->daPump_FlowCap[idx];
								break;
				default :		iRetVal = -2;		break;
			}
			if (iRetVal >= 0)
				iRetVal++;
		}
	}
	return iRetVal;
}



bool OSWX_UnzipFile( const char* pszZipPathFile, const char* pszFileToUnzip, const char* pszUnzipToPath )
{	bool bRetVal = false;

	std::string zipPathFileString;
	zipPathFileString = pszZipPathFile;
	openstudio::path zipPathFile = openstudio::toPath(zipPathFileString);

	std::string fileToUnzipString;
	fileToUnzipString = pszFileToUnzip;
	openstudio::path fileToUnzip = openstudio::toPath(fileToUnzipString);

	std::string unzipToPathString;
	unzipToPathString = pszUnzipToPath;
	openstudio::path unzipToPath = openstudio::toPath(unzipToPathString);

	try
	{	// unzip 
		openstudio::UnzipFile unzip( zipPathFile );
//		unzip.extractAllFiles( unzipToPath );
		unzip.extractFile( fileToUnzip, unzipToPath );
		bRetVal = true;
	}
	catch(const std::exception&)
	{
//		LOG(Info,"Could not unzip dataPoint.zip file in directory '" << toString(directory()) << "'.");
	}
	return bRetVal;
}
