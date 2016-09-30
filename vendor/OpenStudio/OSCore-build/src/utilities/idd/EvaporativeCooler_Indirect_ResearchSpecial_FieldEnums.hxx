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

#ifndef UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeCooler_Indirect_ResearchSpecialFields
 *  \brief Enumeration of EvaporativeCooler:Indirect:ResearchSpecial's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeCooler_Indirect_ResearchSpecialFields, )
#else
class EvaporativeCooler_Indirect_ResearchSpecialFields: public ::EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CoolerWetbulbDesignEffectiveness, WetbulbEffectivenessFlowRatioModifierCurveName, CoolerDrybulbDesignEffectiveness, DrybulbEffectivenessFlowRatioModifierCurveName, RecirculatingWaterPumpDesignPower, WaterPumpPowerSizingFactor, WaterPumpPowerModifierCurveName, SecondaryAirDesignFlowRate, SecondaryAirFlowScalingFactor, SecondaryAirFanDesignPower, SecondaryAirFanSizingSpecificPower, SecondaryAirFanPowerModifierCurveName, PrimaryAirInletNodeName, PrimaryAirOutletNodeName, PrimaryAirDesignFlowRate, DewpointEffectivenessFactor, SecondaryAirInletNodeName, SecondaryAirOutletNodeName, SensorNodeName, ReliefAirInletNodeName, WaterSupplyStorageTankName, DriftLossFraction, BlowdownConcentrationRatio, EvaporativeOperationMinimumLimitSecondaryAirDrybulbTemperature, EvaporativeOperationMaximumLimitOutdoorWetbulbTemperature, DryOperationMaximumLimitOutdoorDrybulbTemperature,   };
  EvaporativeCooler_Indirect_ResearchSpecialFields()
   : EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields>(Name) {} 
  EvaporativeCooler_Indirect_ResearchSpecialFields(const std::string &t_name) 
   : EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields>(t_name) {} 
  EvaporativeCooler_Indirect_ResearchSpecialFields(int t_value) 
   : EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeCooler_Indirect_ResearchSpecialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields>::value()); }
   private:
    friend class EnumBase<EvaporativeCooler_Indirect_ResearchSpecialFields>;
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
{ EvaporativeCooler_Indirect_ResearchSpecialFields::Name, "Name", "Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerWetbulbDesignEffectiveness, "CoolerWetbulbDesignEffectiveness", "Cooler Wetbulb Design Effectiveness"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::WetbulbEffectivenessFlowRatioModifierCurveName, "WetbulbEffectivenessFlowRatioModifierCurveName", "Wetbulb Effectiveness Flow Ratio Modifier Curve Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerDrybulbDesignEffectiveness, "CoolerDrybulbDesignEffectiveness", "Cooler Drybulb Design Effectiveness"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::DrybulbEffectivenessFlowRatioModifierCurveName, "DrybulbEffectivenessFlowRatioModifierCurveName", "Drybulb Effectiveness Flow Ratio Modifier Curve Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, "RecirculatingWaterPumpDesignPower", "Recirculating Water Pump Design Power"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerSizingFactor, "WaterPumpPowerSizingFactor", "Water Pump Power Sizing Factor"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerModifierCurveName, "WaterPumpPowerModifierCurveName", "Water Pump Power Modifier Curve Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, "SecondaryAirDesignFlowRate", "Secondary Air Design Flow Rate"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFlowScalingFactor, "SecondaryAirFlowScalingFactor", "Secondary Air Flow Scaling Factor"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanDesignPower, "SecondaryAirFanDesignPower", "Secondary Air Fan Design Power"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, "SecondaryAirFanSizingSpecificPower", "Secondary Air Fan Sizing Specific Power"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanPowerModifierCurveName, "SecondaryAirFanPowerModifierCurveName", "Secondary Air Fan Power Modifier Curve Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirInletNodeName, "PrimaryAirInletNodeName", "Primary Air Inlet Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirOutletNodeName, "PrimaryAirOutletNodeName", "Primary Air Outlet Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, "PrimaryAirDesignFlowRate", "Primary Air Design Flow Rate"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::DewpointEffectivenessFactor, "DewpointEffectivenessFactor", "Dewpoint Effectiveness Factor"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirOutletNodeName, "SecondaryAirOutletNodeName", "Secondary Air Outlet Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::ReliefAirInletNodeName, "ReliefAirInletNodeName", "Relief Air Inlet Node Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::DriftLossFraction, "DriftLossFraction", "Drift Loss Fraction"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::EvaporativeOperationMinimumLimitSecondaryAirDrybulbTemperature, "EvaporativeOperationMinimumLimitSecondaryAirDrybulbTemperature", "Evaporative Operation Minimum Limit Secondary Air Drybulb Temperature"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::EvaporativeOperationMaximumLimitOutdoorWetbulbTemperature, "EvaporativeOperationMaximumLimitOutdoorWetbulbTemperature", "Evaporative Operation Maximum Limit Outdoor Wetbulb Temperature"},
{ EvaporativeCooler_Indirect_ResearchSpecialFields::DryOperationMaximumLimitOutdoorDrybulbTemperature, "DryOperationMaximumLimitOutdoorDrybulbTemperature", "Dry Operation Maximum Limit Outdoor Drybulb Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeCooler_Indirect_ResearchSpecialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeCooler_Indirect_ResearchSpecialFields> OptionalEvaporativeCooler_Indirect_ResearchSpecialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
