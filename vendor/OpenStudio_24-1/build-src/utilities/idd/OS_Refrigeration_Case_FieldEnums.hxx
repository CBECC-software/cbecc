/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
