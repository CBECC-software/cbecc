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

#ifndef UTILITIES_IDD_OS_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatExchanger_AirToAir_SensibleAndLatentFields
 *  \brief Enumeration of OS:HeatExchanger:AirToAir:SensibleAndLatent's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatExchanger_AirToAir_SensibleAndLatentFields, )
#else
class OS_HeatExchanger_AirToAir_SensibleAndLatentFields: public ::EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, NominalSupplyAirFlowRate, SensibleEffectivenessat100_HeatingAirFlow, LatentEffectivenessat100_HeatingAirFlow, SensibleEffectivenessat75_HeatingAirFlow, LatentEffectivenessat75_HeatingAirFlow, SensibleEffectivenessat100_CoolingAirFlow, LatentEffectivenessat100_CoolingAirFlow, SensibleEffectivenessat75_CoolingAirFlow, LatentEffectivenessat75_CoolingAirFlow, SupplyAirInletNode, SupplyAirOutletNode, ExhaustAirInletNode, ExhaustAirOutletNode, NominalElectricPower, SupplyAirOutletTemperatureControl, HeatExchangerType, FrostControlType, ThresholdTemperature, InitialDefrostTimeFraction, RateofDefrostTimeFractionIncrease, EconomizerLockout,   };
  OS_HeatExchanger_AirToAir_SensibleAndLatentFields()
   : EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields>(Handle) {} 
  OS_HeatExchanger_AirToAir_SensibleAndLatentFields(const std::string &t_name) 
   : EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields>(t_name) {} 
  OS_HeatExchanger_AirToAir_SensibleAndLatentFields(int t_value) 
   : EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatExchanger_AirToAir_SensibleAndLatentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields>::value()); }
   private:
    friend class EnumBase<OS_HeatExchanger_AirToAir_SensibleAndLatentFields>;
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
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::Handle, "Handle", "Handle"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::Name, "Name", "Name"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, "NominalSupplyAirFlowRate", "Nominal Supply Air Flow Rate"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_HeatingAirFlow, "SensibleEffectivenessat100_HeatingAirFlow", "Sensible Effectiveness at 100% Heating Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_HeatingAirFlow, "LatentEffectivenessat100_HeatingAirFlow", "Latent Effectiveness at 100% Heating Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat75_HeatingAirFlow, "SensibleEffectivenessat75_HeatingAirFlow", "Sensible Effectiveness at 75% Heating Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat75_HeatingAirFlow, "LatentEffectivenessat75_HeatingAirFlow", "Latent Effectiveness at 75% Heating Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_CoolingAirFlow, "SensibleEffectivenessat100_CoolingAirFlow", "Sensible Effectiveness at 100% Cooling Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_CoolingAirFlow, "LatentEffectivenessat100_CoolingAirFlow", "Latent Effectiveness at 100% Cooling Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat75_CoolingAirFlow, "SensibleEffectivenessat75_CoolingAirFlow", "Sensible Effectiveness at 75% Cooling Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat75_CoolingAirFlow, "LatentEffectivenessat75_CoolingAirFlow", "Latent Effectiveness at 75% Cooling Air Flow"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNode, "SupplyAirInletNode", "Supply Air Inlet Node"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNode, "SupplyAirOutletNode", "Supply Air Outlet Node"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNode, "ExhaustAirInletNode", "Exhaust Air Inlet Node"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNode, "ExhaustAirOutletNode", "Exhaust Air Outlet Node"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::NominalElectricPower, "NominalElectricPower", "Nominal Electric Power"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletTemperatureControl, "SupplyAirOutletTemperatureControl", "Supply Air Outlet Temperature Control"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::HeatExchangerType, "HeatExchangerType", "Heat Exchanger Type"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::FrostControlType, "FrostControlType", "Frost Control Type"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature, "ThresholdTemperature", "Threshold Temperature"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::InitialDefrostTimeFraction, "InitialDefrostTimeFraction", "Initial Defrost Time Fraction"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::RateofDefrostTimeFractionIncrease, "RateofDefrostTimeFractionIncrease", "Rate of Defrost Time Fraction Increase"},
{ OS_HeatExchanger_AirToAir_SensibleAndLatentFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatExchanger_AirToAir_SensibleAndLatentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatExchanger_AirToAir_SensibleAndLatentFields> OptionalOS_HeatExchanger_AirToAir_SensibleAndLatentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX
