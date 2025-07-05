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

#ifndef UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeCooler_Direct_ResearchSpecialFields
 *  \brief Enumeration of EvaporativeCooler:Direct:ResearchSpecial's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeCooler_Direct_ResearchSpecialFields, )
#else
class EvaporativeCooler_Direct_ResearchSpecialFields: public ::EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CoolerDesignEffectiveness, EffectivenessFlowRatioModifierCurveName, PrimaryAirDesignFlowRate, RecirculatingWaterPumpDesignPower, WaterPumpPowerSizingFactor, WaterPumpPowerModifierCurveName, AirInletNodeName, AirOutletNodeName, SensorNodeName, WaterSupplyStorageTankName, DriftLossFraction, BlowdownConcentrationRatio, EvaporativeOperationMinimumDrybulbTemperature, EvaporativeOperationMaximumLimitWetbulbTemperature, EvaporativeOperationMaximumLimitDrybulbTemperature,   };
  EvaporativeCooler_Direct_ResearchSpecialFields()
   : EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields>(Name) {} 
  EvaporativeCooler_Direct_ResearchSpecialFields(const std::string &t_name) 
   : EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields>(t_name) {} 
  EvaporativeCooler_Direct_ResearchSpecialFields(int t_value) 
   : EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeCooler_Direct_ResearchSpecialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields>::value()); }
   private:
    friend class EnumBase<EvaporativeCooler_Direct_ResearchSpecialFields>;
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
{ EvaporativeCooler_Direct_ResearchSpecialFields::Name, "Name", "Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::CoolerDesignEffectiveness, "CoolerDesignEffectiveness", "Cooler Design Effectiveness"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::EffectivenessFlowRatioModifierCurveName, "EffectivenessFlowRatioModifierCurveName", "Effectiveness Flow Ratio Modifier Curve Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, "PrimaryAirDesignFlowRate", "Primary Air Design Flow Rate"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, "RecirculatingWaterPumpDesignPower", "Recirculating Water Pump Design Power"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerSizingFactor, "WaterPumpPowerSizingFactor", "Water Pump Power Sizing Factor"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerModifierCurveName, "WaterPumpPowerModifierCurveName", "Water Pump Power Modifier Curve Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::DriftLossFraction, "DriftLossFraction", "Drift Loss Fraction"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMinimumDrybulbTemperature, "EvaporativeOperationMinimumDrybulbTemperature", "Evaporative Operation Minimum Drybulb Temperature"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitWetbulbTemperature, "EvaporativeOperationMaximumLimitWetbulbTemperature", "Evaporative Operation Maximum Limit Wetbulb Temperature"},
{ EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitDrybulbTemperature, "EvaporativeOperationMaximumLimitDrybulbTemperature", "Evaporative Operation Maximum Limit Drybulb Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeCooler_Direct_ResearchSpecialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeCooler_Direct_ResearchSpecialFields> OptionalEvaporativeCooler_Direct_ResearchSpecialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
