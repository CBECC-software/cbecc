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

#ifndef UTILITIES_IDD_OS_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_EvaporativeCooler_Direct_ResearchSpecialFields
 *  \brief Enumeration of OS:EvaporativeCooler:Direct:ResearchSpecial's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_EvaporativeCooler_Direct_ResearchSpecialFields, )
#else
class OS_EvaporativeCooler_Direct_ResearchSpecialFields: public ::EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, CoolerEffectiveness, RecirculatingWaterPumpPowerConsumption, PrimaryAirDesignFlowRate, AirInletNodeName, AirOutletNodeName, SensorNodeName, DriftLossFraction, BlowdownConcentrationRatio, EffectivenessFlowRatioModifierCurveName, WaterPumpPowerSizingFactor, WaterPumpPowerModifierCurveName,   };
  OS_EvaporativeCooler_Direct_ResearchSpecialFields()
   : EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields>(Handle) {} 
  OS_EvaporativeCooler_Direct_ResearchSpecialFields(const std::string &t_name) 
   : EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields>(t_name) {} 
  OS_EvaporativeCooler_Direct_ResearchSpecialFields(int t_value) 
   : EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EvaporativeCooler_Direct_ResearchSpecialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields>::value()); }
   private:
    friend class EnumBase<OS_EvaporativeCooler_Direct_ResearchSpecialFields>;
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
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::Handle, "Handle", "Handle"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::Name, "Name", "Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::CoolerEffectiveness, "CoolerEffectiveness", "Cooler Effectiveness"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpPowerConsumption, "RecirculatingWaterPumpPowerConsumption", "Recirculating Water Pump Power Consumption"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, "PrimaryAirDesignFlowRate", "Primary Air Design Flow Rate"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::DriftLossFraction, "DriftLossFraction", "Drift Loss Fraction"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::EffectivenessFlowRatioModifierCurveName, "EffectivenessFlowRatioModifierCurveName", "Effectiveness Flow Ratio Modifier Curve Name"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerSizingFactor, "WaterPumpPowerSizingFactor", "Water Pump Power Sizing Factor"},
{ OS_EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerModifierCurveName, "WaterPumpPowerModifierCurveName", "Water Pump Power Modifier Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EvaporativeCooler_Direct_ResearchSpecialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EvaporativeCooler_Direct_ResearchSpecialFields> OptionalOS_EvaporativeCooler_Direct_ResearchSpecialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EVAPORATIVECOOLER_DIRECT_RESEARCHSPECIAL_FIELDENUMS_HXX
