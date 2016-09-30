/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields
 *  \brief Enumeration of SurfaceConvectionAlgorithm:Inside:AdaptiveModelSelections's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields, )
#else
class SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields: public ::EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields> {
 public: 
  enum domain 
  {
Name, SimpleBuoyancyVerticalWallEquationSource, SimpleBuoyancyVerticalWallUserCurveName, SimpleBouyancyStableHorizontalEquationSource, SimpleBouyancyStableHorizontalEquationUserCurveName, SimpleBouyancyUnstableHorizontalEquationSource, SimpleBouyancyUnstableHorizontalEquationUserCurveName, SimpleBouyancyStableTiltedEquationSource, SimpleBouyancyStableTiltedEquationUserCurveName, SimpleBouyancyUnstableTiltedEquationSource, SimpleBouyancyUnstableTiltedEquationUserCurveName, SimpleBouyancyWindowsEquationSource, SimpleBouyancyWindowsEquationUserCurveName, FloorHeatCeilingCoolVerticalWallEquationSource, FloorHeatCeilingCoolVerticalWallEquationUserCurveName, FloorHeatCeilingCoolStableHorizontalEquationSource, FloorHeatCeilingCoolStableHorizontalEquationUserCurveName, FloorHeatCeilingCoolUnstableHorizontalEquationSource, FloorHeatCeilingCoolUnstableHorizontalEquationUserCurveName, FloorHeatCeilingCoolHeatedFloorEquationSource, FloorHeatCeilingCoolHeatedFloorEquationUserCurveName, FloorHeatCeilingCoolChilledCeilingEquationSource, FloorHeatCeilingCoolChilledCeilingEquationUserCurveName, FloorHeatCeilingCoolStableTiltedEquationSource, FloorHeatCeilingCoolStableTiltedEquationUserCurveName, FloorHeatCeilingCoolUnstableTiltedEquationSource, FloorHeatCeilingCoolUnstableTiltedEquationUserCurveName, FloorHeatCeilingCoolWindowEquationSource, FloorHeatCeilingCoolWindowEquationUserCurveName, WallPanelHeatingVerticalWallEquationSource, WallPanelHeatingVerticalWallEquationUserCurveName, WallPanelHeatingHeatedWallEquationSource, WallPanelHeatingHeatedWallEquationUserCurveName, WallPanelHeatingStableHorizontalEquationSource, WallPanelHeatingStableHorizontalEquationUserCurveName, WallPanelHeatingUnstableHorizontalEquationSource, WallPanelHeatingUnstableHorizontalEquationUserCurveName, WallPanelHeatingStableTiltedEquationSource, WallPanelHeatingStableTiltedEquationUserCurveName, WallPanelHeatingUnstableTiltedEquationSource, WallPanelHeatingUnstableTiltedEquationUserCurveName, WallPanelHeatingWindowEquationSource, WallPanelHeatingWindowEquationUserCurveName, ConvectiveZoneHeaterVerticalWallEquationSource, ConvectiveZoneHeaterVerticalWallEquationUserCurveName, ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource, ConvectiveZoneHeaterVerticalWallsNearHeaterEquationUserCurveName, ConvectiveZoneHeaterStableHorizontalEquationSource, ConvectiveZoneHeaterStableHorizontalEquationUserCurveName, ConvectiveZoneHeaterUnstableHorizontalEquationSource, ConvectiveZoneHeaterUnstableHorizontalEquationUserCurveName, ConvectiveZoneHeaterStableTiltedEquationSource, ConvectiveZoneHeaterStableTiltedEquationUserCurveName, ConvectiveZoneHeaterUnstableTiltedEquationSource, ConvectiveZoneHeaterUnstableTiltedEquationUserCurveName, ConvectiveZoneHeaterWindowsEquationSource, ConvectiveZoneHeaterWindowsEquationUserCurveName, CentralAirDiffuserWallEquationSource, CentralAirDiffuserWallEquationUserCurveName, CentralAirDiffuserCeilingEquationSource, CentralAirDiffuserCeilingEquationUserCurveName, CentralAirDiffuserFloorEquationSource, CentralAirDiffuserFloorEquationUserCurveName, CentralAirDiffuserWindowEquationSource, CentralAirDiffuserWindowEquationUserCurveName, MechanicalZoneFanCirculationVerticalWallEquationSource, MechanicalZoneFanCirculationVerticalWallEquationUserCurveName, MechanicalZoneFanCirculationStableHorizontalEquationSource, MechanicalZoneFanCirculationStableHorizontalEquationUserCurveName, MechanicalZoneFanCirculationUnstableHorizontalEquationSource, MechanicalZoneFanCirculationUnstableHorizontalEquationUserCurveName, MechanicalZoneFanCirculationStableTiltedEquationSource, MechanicalZoneFanCirculationStableTiltedEquationUserCurveName, MechanicalZoneFanCirculationUnstableTiltedEquationSource, MechanicalZoneFanCirculationUnstableTiltedEquationUserCurveName, MechanicalZoneFanCirculationWindowEquationSource, MechanicalZoneFanCirculationWindowEquationUserCurveName, MixedRegimeBouyancyAssistingFlowonWallsEquationSource, MixedRegimeBouyancyAssistingFlowonWallsEquationUserCurveName, MixedRegimeBouyancyOppossingFlowonWallsEquationSource, MixedRegimeBouyancyOppossingFlowonWallsEquationUserCurveName, MixedRegimeStableFloorEquationSource, MixedRegimeStableFloorEquationUserCurveName, MixedRegimeUnstableFloorEquationSource, MixedRegimeUnstableFloorEquationUserCurveName, MixedRegimeStableCeilingEquationSource, MixedRegimeStableCeilingEquationUserCurveName, MixedRegimeUnstableCeilingEquationSource, MixedRegimeUnstableCeilingEquationUserCurveName, MixedRegimeWindowEquationSource, MixedRegimeWindowEquationUserCurveName,   };
  SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields()
   : EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields>(Name) {} 
  SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields(const std::string &t_name) 
   : EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields>(t_name) {} 
  SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields(int t_value) 
   : EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields>::value()); }
   private:
    friend class EnumBase<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::Name, "Name", "Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyVerticalWallEquationSource, "SimpleBuoyancyVerticalWallEquationSource", "Simple Buoyancy Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyVerticalWallUserCurveName, "SimpleBuoyancyVerticalWallUserCurveName", "Simple Buoyancy Vertical Wall User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyStableHorizontalEquationSource, "SimpleBouyancyStableHorizontalEquationSource", "Simple Bouyancy Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyStableHorizontalEquationUserCurveName, "SimpleBouyancyStableHorizontalEquationUserCurveName", "Simple Bouyancy Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyUnstableHorizontalEquationSource, "SimpleBouyancyUnstableHorizontalEquationSource", "Simple Bouyancy Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyUnstableHorizontalEquationUserCurveName, "SimpleBouyancyUnstableHorizontalEquationUserCurveName", "Simple Bouyancy Unstable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyStableTiltedEquationSource, "SimpleBouyancyStableTiltedEquationSource", "Simple Bouyancy Stable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyStableTiltedEquationUserCurveName, "SimpleBouyancyStableTiltedEquationUserCurveName", "Simple Bouyancy Stable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyUnstableTiltedEquationSource, "SimpleBouyancyUnstableTiltedEquationSource", "Simple Bouyancy Unstable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyUnstableTiltedEquationUserCurveName, "SimpleBouyancyUnstableTiltedEquationUserCurveName", "Simple Bouyancy Unstable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyWindowsEquationSource, "SimpleBouyancyWindowsEquationSource", "Simple Bouyancy Windows Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBouyancyWindowsEquationUserCurveName, "SimpleBouyancyWindowsEquationUserCurveName", "Simple Bouyancy Windows Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolVerticalWallEquationSource, "FloorHeatCeilingCoolVerticalWallEquationSource", "Floor Heat Ceiling Cool Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolVerticalWallEquationUserCurveName, "FloorHeatCeilingCoolVerticalWallEquationUserCurveName", "Floor Heat Ceiling Cool Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableHorizontalEquationSource, "FloorHeatCeilingCoolStableHorizontalEquationSource", "Floor Heat Ceiling Cool Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableHorizontalEquationUserCurveName, "FloorHeatCeilingCoolStableHorizontalEquationUserCurveName", "Floor Heat Ceiling Cool Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableHorizontalEquationSource, "FloorHeatCeilingCoolUnstableHorizontalEquationSource", "Floor Heat Ceiling Cool Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableHorizontalEquationUserCurveName, "FloorHeatCeilingCoolUnstableHorizontalEquationUserCurveName", "Floor Heat Ceiling Cool Unstable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolHeatedFloorEquationSource, "FloorHeatCeilingCoolHeatedFloorEquationSource", "Floor Heat Ceiling Cool Heated Floor Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolHeatedFloorEquationUserCurveName, "FloorHeatCeilingCoolHeatedFloorEquationUserCurveName", "Floor Heat Ceiling Cool Heated Floor Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolChilledCeilingEquationSource, "FloorHeatCeilingCoolChilledCeilingEquationSource", "Floor Heat Ceiling Cool Chilled Ceiling Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolChilledCeilingEquationUserCurveName, "FloorHeatCeilingCoolChilledCeilingEquationUserCurveName", "Floor Heat Ceiling Cool Chilled Ceiling Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableTiltedEquationSource, "FloorHeatCeilingCoolStableTiltedEquationSource", "Floor Heat Ceiling Cool Stable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableTiltedEquationUserCurveName, "FloorHeatCeilingCoolStableTiltedEquationUserCurveName", "Floor Heat Ceiling Cool Stable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableTiltedEquationSource, "FloorHeatCeilingCoolUnstableTiltedEquationSource", "Floor Heat Ceiling Cool Unstable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableTiltedEquationUserCurveName, "FloorHeatCeilingCoolUnstableTiltedEquationUserCurveName", "Floor Heat Ceiling Cool Unstable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolWindowEquationSource, "FloorHeatCeilingCoolWindowEquationSource", "Floor Heat Ceiling Cool Window Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolWindowEquationUserCurveName, "FloorHeatCeilingCoolWindowEquationUserCurveName", "Floor Heat Ceiling Cool Window Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingVerticalWallEquationSource, "WallPanelHeatingVerticalWallEquationSource", "Wall Panel Heating Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingVerticalWallEquationUserCurveName, "WallPanelHeatingVerticalWallEquationUserCurveName", "Wall Panel Heating Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingHeatedWallEquationSource, "WallPanelHeatingHeatedWallEquationSource", "Wall Panel Heating Heated Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingHeatedWallEquationUserCurveName, "WallPanelHeatingHeatedWallEquationUserCurveName", "Wall Panel Heating Heated Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableHorizontalEquationSource, "WallPanelHeatingStableHorizontalEquationSource", "Wall Panel Heating Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableHorizontalEquationUserCurveName, "WallPanelHeatingStableHorizontalEquationUserCurveName", "Wall Panel Heating Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableHorizontalEquationSource, "WallPanelHeatingUnstableHorizontalEquationSource", "Wall Panel Heating Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableHorizontalEquationUserCurveName, "WallPanelHeatingUnstableHorizontalEquationUserCurveName", "Wall Panel Heating Unstable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableTiltedEquationSource, "WallPanelHeatingStableTiltedEquationSource", "Wall Panel Heating Stable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableTiltedEquationUserCurveName, "WallPanelHeatingStableTiltedEquationUserCurveName", "Wall Panel Heating Stable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableTiltedEquationSource, "WallPanelHeatingUnstableTiltedEquationSource", "Wall Panel Heating Unstable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableTiltedEquationUserCurveName, "WallPanelHeatingUnstableTiltedEquationUserCurveName", "Wall Panel Heating Unstable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingWindowEquationSource, "WallPanelHeatingWindowEquationSource", "Wall Panel Heating Window Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingWindowEquationUserCurveName, "WallPanelHeatingWindowEquationUserCurveName", "Wall Panel Heating Window Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallEquationSource, "ConvectiveZoneHeaterVerticalWallEquationSource", "Convective Zone Heater Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallEquationUserCurveName, "ConvectiveZoneHeaterVerticalWallEquationUserCurveName", "Convective Zone Heater Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource, "ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource", "Convective Zone Heater Vertical Walls Near Heater Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallsNearHeaterEquationUserCurveName, "ConvectiveZoneHeaterVerticalWallsNearHeaterEquationUserCurveName", "Convective Zone Heater Vertical Walls Near Heater Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableHorizontalEquationSource, "ConvectiveZoneHeaterStableHorizontalEquationSource", "Convective Zone Heater Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableHorizontalEquationUserCurveName, "ConvectiveZoneHeaterStableHorizontalEquationUserCurveName", "Convective Zone Heater Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableHorizontalEquationSource, "ConvectiveZoneHeaterUnstableHorizontalEquationSource", "Convective Zone Heater Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableHorizontalEquationUserCurveName, "ConvectiveZoneHeaterUnstableHorizontalEquationUserCurveName", "Convective Zone Heater Unstable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableTiltedEquationSource, "ConvectiveZoneHeaterStableTiltedEquationSource", "Convective Zone Heater Stable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableTiltedEquationUserCurveName, "ConvectiveZoneHeaterStableTiltedEquationUserCurveName", "Convective Zone Heater Stable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableTiltedEquationSource, "ConvectiveZoneHeaterUnstableTiltedEquationSource", "Convective Zone Heater Unstable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableTiltedEquationUserCurveName, "ConvectiveZoneHeaterUnstableTiltedEquationUserCurveName", "Convective Zone Heater Unstable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterWindowsEquationSource, "ConvectiveZoneHeaterWindowsEquationSource", "Convective Zone Heater Windows Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterWindowsEquationUserCurveName, "ConvectiveZoneHeaterWindowsEquationUserCurveName", "Convective Zone Heater Windows Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWallEquationSource, "CentralAirDiffuserWallEquationSource", "Central Air Diffuser Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWallEquationUserCurveName, "CentralAirDiffuserWallEquationUserCurveName", "Central Air Diffuser Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserCeilingEquationSource, "CentralAirDiffuserCeilingEquationSource", "Central Air Diffuser Ceiling Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserCeilingEquationUserCurveName, "CentralAirDiffuserCeilingEquationUserCurveName", "Central Air Diffuser Ceiling Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserFloorEquationSource, "CentralAirDiffuserFloorEquationSource", "Central Air Diffuser Floor Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserFloorEquationUserCurveName, "CentralAirDiffuserFloorEquationUserCurveName", "Central Air Diffuser Floor Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWindowEquationSource, "CentralAirDiffuserWindowEquationSource", "Central Air Diffuser Window Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWindowEquationUserCurveName, "CentralAirDiffuserWindowEquationUserCurveName", "Central Air Diffuser Window Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationVerticalWallEquationSource, "MechanicalZoneFanCirculationVerticalWallEquationSource", "Mechanical Zone Fan Circulation Vertical Wall Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationVerticalWallEquationUserCurveName, "MechanicalZoneFanCirculationVerticalWallEquationUserCurveName", "Mechanical Zone Fan Circulation Vertical Wall Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableHorizontalEquationSource, "MechanicalZoneFanCirculationStableHorizontalEquationSource", "Mechanical Zone Fan Circulation Stable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableHorizontalEquationUserCurveName, "MechanicalZoneFanCirculationStableHorizontalEquationUserCurveName", "Mechanical Zone Fan Circulation Stable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableHorizontalEquationSource, "MechanicalZoneFanCirculationUnstableHorizontalEquationSource", "Mechanical Zone Fan Circulation Unstable Horizontal Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableHorizontalEquationUserCurveName, "MechanicalZoneFanCirculationUnstableHorizontalEquationUserCurveName", "Mechanical Zone Fan Circulation Unstable Horizontal Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableTiltedEquationSource, "MechanicalZoneFanCirculationStableTiltedEquationSource", "Mechanical Zone Fan Circulation Stable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableTiltedEquationUserCurveName, "MechanicalZoneFanCirculationStableTiltedEquationUserCurveName", "Mechanical Zone Fan Circulation Stable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableTiltedEquationSource, "MechanicalZoneFanCirculationUnstableTiltedEquationSource", "Mechanical Zone Fan Circulation Unstable Tilted Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableTiltedEquationUserCurveName, "MechanicalZoneFanCirculationUnstableTiltedEquationUserCurveName", "Mechanical Zone Fan Circulation Unstable Tilted Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationWindowEquationSource, "MechanicalZoneFanCirculationWindowEquationSource", "Mechanical Zone Fan Circulation Window Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationWindowEquationUserCurveName, "MechanicalZoneFanCirculationWindowEquationUserCurveName", "Mechanical Zone Fan Circulation Window Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBouyancyAssistingFlowonWallsEquationSource, "MixedRegimeBouyancyAssistingFlowonWallsEquationSource", "Mixed Regime Bouyancy Assisting Flow on Walls Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBouyancyAssistingFlowonWallsEquationUserCurveName, "MixedRegimeBouyancyAssistingFlowonWallsEquationUserCurveName", "Mixed Regime Bouyancy Assisting Flow on Walls Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBouyancyOppossingFlowonWallsEquationSource, "MixedRegimeBouyancyOppossingFlowonWallsEquationSource", "Mixed Regime Bouyancy Oppossing Flow on Walls Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBouyancyOppossingFlowonWallsEquationUserCurveName, "MixedRegimeBouyancyOppossingFlowonWallsEquationUserCurveName", "Mixed Regime Bouyancy Oppossing Flow on Walls Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableFloorEquationSource, "MixedRegimeStableFloorEquationSource", "Mixed Regime Stable Floor Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableFloorEquationUserCurveName, "MixedRegimeStableFloorEquationUserCurveName", "Mixed Regime Stable Floor Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableFloorEquationSource, "MixedRegimeUnstableFloorEquationSource", "Mixed Regime Unstable Floor Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableFloorEquationUserCurveName, "MixedRegimeUnstableFloorEquationUserCurveName", "Mixed Regime Unstable Floor Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableCeilingEquationSource, "MixedRegimeStableCeilingEquationSource", "Mixed Regime Stable Ceiling Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableCeilingEquationUserCurveName, "MixedRegimeStableCeilingEquationUserCurveName", "Mixed Regime Stable Ceiling Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableCeilingEquationSource, "MixedRegimeUnstableCeilingEquationSource", "Mixed Regime Unstable Ceiling Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableCeilingEquationUserCurveName, "MixedRegimeUnstableCeilingEquationUserCurveName", "Mixed Regime Unstable Ceiling Equation User Curve Name"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeWindowEquationSource, "MixedRegimeWindowEquationSource", "Mixed Regime Window Equation Source"},
{ SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeWindowEquationUserCurveName, "MixedRegimeWindowEquationUserCurveName", "Mixed Regime Window Equation User Curve Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields> OptionalSurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACECONVECTIONALGORITHM_INSIDE_ADAPTIVEMODELSELECTIONS_FIELDENUMS_HXX
