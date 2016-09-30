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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_CASE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_CASE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_CaseFields
 *  \brief Enumeration of OS:Refrigeration:Case's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_CaseFields, )
#else
class OS_Refrigeration_CaseFields: public ::EnumBase<OS_Refrigeration_CaseFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, ZoneName, RatedAmbientTemperature, RatedAmbientRelativeHumidity, RatedTotalCoolingCapacityperUnitLength, RatedLatentHeatRatio, RatedRuntimeFraction, CaseLength, CaseOperatingTemperature, LatentCaseCreditCurveType, LatentCaseCreditCurveName, StandardCaseFanPowerperUnitLength, OperatingCaseFanPowerperUnitLength, StandardCaseLightingPowerperUnitLength, InstalledCaseLightingPowerperUnitLength, CaseLightingScheduleName, FractionofLightingEnergytoCase, CaseAntiSweatHeaterPowerperUnitLength, MinimumAntiSweatHeaterPowerperUnitLength, AntiSweatHeaterControlType, HumidityatZeroAntiSweatHeaterEnergy, CaseHeight, FractionofAntiSweatHeaterEnergytoCase, CaseDefrostPowerperUnitLength, CaseDefrostType, CaseDefrostScheduleName, CaseDefrostDripDownScheduleName, DefrostEnergyCorrectionCurveType, DefrostEnergyCorrectionCurveName, UnderCaseHVACReturnAirFraction, RefrigeratedCaseRestockingScheduleName, CaseCreditFractionScheduleName, DesignEvaporatorTemperatureorBrineInletTemperature, AverageRefrigerantChargeInventory, NumberOfDoors, RatedTotalCoolingCapacityperDoor, StandardCaseFanPowerperDoor, OperatingCaseFanPowerperDoor, StandardCaseLightingPowerperDoor, InstalledCaseLightingPowerperDoor, CaseAntiSweatHeaterPowerperDoor, MinimumAntiSweatHeaterPowerperDoor, CaseDefrostPowerperDoor, UnitType, CaseDefrostCycleParametersName,   };
  OS_Refrigeration_CaseFields()
   : EnumBase<OS_Refrigeration_CaseFields>(Handle) {} 
  OS_Refrigeration_CaseFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_CaseFields>(t_name) {} 
  OS_Refrigeration_CaseFields(int t_value) 
   : EnumBase<OS_Refrigeration_CaseFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_CaseFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_CaseFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_CaseFields>;
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
{ OS_Refrigeration_CaseFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_CaseFields::Name, "Name", "Name"},
{ OS_Refrigeration_CaseFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Refrigeration_CaseFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_Refrigeration_CaseFields::RatedAmbientTemperature, "RatedAmbientTemperature", "Rated Ambient Temperature"},
{ OS_Refrigeration_CaseFields::RatedAmbientRelativeHumidity, "RatedAmbientRelativeHumidity", "Rated Ambient Relative Humidity"},
{ OS_Refrigeration_CaseFields::RatedTotalCoolingCapacityperUnitLength, "RatedTotalCoolingCapacityperUnitLength", "Rated Total Cooling Capacity per Unit Length"},
{ OS_Refrigeration_CaseFields::RatedLatentHeatRatio, "RatedLatentHeatRatio", "Rated Latent Heat Ratio"},
{ OS_Refrigeration_CaseFields::RatedRuntimeFraction, "RatedRuntimeFraction", "Rated Runtime Fraction"},
{ OS_Refrigeration_CaseFields::CaseLength, "CaseLength", "Case Length"},
{ OS_Refrigeration_CaseFields::CaseOperatingTemperature, "CaseOperatingTemperature", "Case Operating Temperature"},
{ OS_Refrigeration_CaseFields::LatentCaseCreditCurveType, "LatentCaseCreditCurveType", "Latent Case Credit Curve Type"},
{ OS_Refrigeration_CaseFields::LatentCaseCreditCurveName, "LatentCaseCreditCurveName", "Latent Case Credit Curve Name"},
{ OS_Refrigeration_CaseFields::StandardCaseFanPowerperUnitLength, "StandardCaseFanPowerperUnitLength", "Standard Case Fan Power per Unit Length"},
{ OS_Refrigeration_CaseFields::OperatingCaseFanPowerperUnitLength, "OperatingCaseFanPowerperUnitLength", "Operating Case Fan Power per Unit Length"},
{ OS_Refrigeration_CaseFields::StandardCaseLightingPowerperUnitLength, "StandardCaseLightingPowerperUnitLength", "Standard Case Lighting Power per Unit Length"},
{ OS_Refrigeration_CaseFields::InstalledCaseLightingPowerperUnitLength, "InstalledCaseLightingPowerperUnitLength", "Installed Case Lighting Power per Unit Length"},
{ OS_Refrigeration_CaseFields::CaseLightingScheduleName, "CaseLightingScheduleName", "Case Lighting Schedule Name"},
{ OS_Refrigeration_CaseFields::FractionofLightingEnergytoCase, "FractionofLightingEnergytoCase", "Fraction of Lighting Energy to Case"},
{ OS_Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperUnitLength, "CaseAntiSweatHeaterPowerperUnitLength", "Case Anti-Sweat Heater Power per Unit Length"},
{ OS_Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperUnitLength, "MinimumAntiSweatHeaterPowerperUnitLength", "Minimum Anti-Sweat Heater Power per Unit Length"},
{ OS_Refrigeration_CaseFields::AntiSweatHeaterControlType, "AntiSweatHeaterControlType", "Anti-Sweat Heater Control Type"},
{ OS_Refrigeration_CaseFields::HumidityatZeroAntiSweatHeaterEnergy, "HumidityatZeroAntiSweatHeaterEnergy", "Humidity at Zero Anti-Sweat Heater Energy"},
{ OS_Refrigeration_CaseFields::CaseHeight, "CaseHeight", "Case Height"},
{ OS_Refrigeration_CaseFields::FractionofAntiSweatHeaterEnergytoCase, "FractionofAntiSweatHeaterEnergytoCase", "Fraction of Anti-Sweat Heater Energy to Case"},
{ OS_Refrigeration_CaseFields::CaseDefrostPowerperUnitLength, "CaseDefrostPowerperUnitLength", "Case Defrost Power per Unit Length"},
{ OS_Refrigeration_CaseFields::CaseDefrostType, "CaseDefrostType", "Case Defrost Type"},
{ OS_Refrigeration_CaseFields::CaseDefrostScheduleName, "CaseDefrostScheduleName", "Case Defrost Schedule Name"},
{ OS_Refrigeration_CaseFields::CaseDefrostDripDownScheduleName, "CaseDefrostDripDownScheduleName", "Case Defrost Drip-Down Schedule Name"},
{ OS_Refrigeration_CaseFields::DefrostEnergyCorrectionCurveType, "DefrostEnergyCorrectionCurveType", "Defrost Energy Correction Curve Type"},
{ OS_Refrigeration_CaseFields::DefrostEnergyCorrectionCurveName, "DefrostEnergyCorrectionCurveName", "Defrost Energy Correction Curve Name"},
{ OS_Refrigeration_CaseFields::UnderCaseHVACReturnAirFraction, "UnderCaseHVACReturnAirFraction", "Under Case HVAC Return Air Fraction"},
{ OS_Refrigeration_CaseFields::RefrigeratedCaseRestockingScheduleName, "RefrigeratedCaseRestockingScheduleName", "Refrigerated Case Restocking Schedule Name"},
{ OS_Refrigeration_CaseFields::CaseCreditFractionScheduleName, "CaseCreditFractionScheduleName", "Case Credit Fraction Schedule Name"},
{ OS_Refrigeration_CaseFields::DesignEvaporatorTemperatureorBrineInletTemperature, "DesignEvaporatorTemperatureorBrineInletTemperature", "Design Evaporator Temperature or Brine Inlet Temperature"},
{ OS_Refrigeration_CaseFields::AverageRefrigerantChargeInventory, "AverageRefrigerantChargeInventory", "Average Refrigerant Charge Inventory"},
{ OS_Refrigeration_CaseFields::NumberOfDoors, "NumberOfDoors", "Number Of Doors"},
{ OS_Refrigeration_CaseFields::RatedTotalCoolingCapacityperDoor, "RatedTotalCoolingCapacityperDoor", "Rated Total Cooling Capacity per Door"},
{ OS_Refrigeration_CaseFields::StandardCaseFanPowerperDoor, "StandardCaseFanPowerperDoor", "Standard Case Fan Power per Door"},
{ OS_Refrigeration_CaseFields::OperatingCaseFanPowerperDoor, "OperatingCaseFanPowerperDoor", "Operating Case Fan Power per Door"},
{ OS_Refrigeration_CaseFields::StandardCaseLightingPowerperDoor, "StandardCaseLightingPowerperDoor", "Standard Case Lighting Power per Door"},
{ OS_Refrigeration_CaseFields::InstalledCaseLightingPowerperDoor, "InstalledCaseLightingPowerperDoor", "Installed Case Lighting Power per Door"},
{ OS_Refrigeration_CaseFields::CaseAntiSweatHeaterPowerperDoor, "CaseAntiSweatHeaterPowerperDoor", "Case Anti-Sweat Heater Power per Door"},
{ OS_Refrigeration_CaseFields::MinimumAntiSweatHeaterPowerperDoor, "MinimumAntiSweatHeaterPowerperDoor", "Minimum Anti-Sweat Heater Power per Door"},
{ OS_Refrigeration_CaseFields::CaseDefrostPowerperDoor, "CaseDefrostPowerperDoor", "Case Defrost Power per Door"},
{ OS_Refrigeration_CaseFields::UnitType, "UnitType", "Unit Type"},
{ OS_Refrigeration_CaseFields::CaseDefrostCycleParametersName, "CaseDefrostCycleParametersName", "Case Defrost Cycle Parameters Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_CaseFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_CaseFields> OptionalOS_Refrigeration_CaseFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_CASE_FIELDENUMS_HXX
