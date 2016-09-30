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
