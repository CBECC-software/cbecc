/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_AirToAir_SensibleAndLatentFields
 *  \brief Enumeration of HeatExchanger:AirToAir:SensibleAndLatent's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatExchanger_AirToAir_SensibleAndLatentFields, )
#else
class HeatExchanger_AirToAir_SensibleAndLatentFields: public ::EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, NominalSupplyAirFlowRate, SensibleEffectivenessat100_HeatingAirFlow, LatentEffectivenessat100_HeatingAirFlow, SensibleEffectivenessat75_HeatingAirFlow, LatentEffectivenessat75_HeatingAirFlow, SensibleEffectivenessat100_CoolingAirFlow, LatentEffectivenessat100_CoolingAirFlow, SensibleEffectivenessat75_CoolingAirFlow, LatentEffectivenessat75_CoolingAirFlow, SupplyAirInletNodeName, SupplyAirOutletNodeName, ExhaustAirInletNodeName, ExhaustAirOutletNodeName, NominalElectricPower, SupplyAirOutletTemperatureControl, HeatExchangerType, FrostControlType, ThresholdTemperature, InitialDefrostTimeFraction, RateofDefrostTimeFractionIncrease, EconomizerLockout,   };
  HeatExchanger_AirToAir_SensibleAndLatentFields()
   : EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields>(Name) {} 
  HeatExchanger_AirToAir_SensibleAndLatentFields(const std::string &t_name) 
   : EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields>(t_name) {} 
  HeatExchanger_AirToAir_SensibleAndLatentFields(int t_value) 
   : EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatExchanger_AirToAir_SensibleAndLatentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields>::value()); }
   private:
    friend class EnumBase<HeatExchanger_AirToAir_SensibleAndLatentFields>;
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
{ HeatExchanger_AirToAir_SensibleAndLatentFields::Name, "Name", "Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::NominalSupplyAirFlowRate, "NominalSupplyAirFlowRate", "Nominal Supply Air Flow Rate"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_HeatingAirFlow, "SensibleEffectivenessat100_HeatingAirFlow", "Sensible Effectiveness at 100% Heating Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_HeatingAirFlow, "LatentEffectivenessat100_HeatingAirFlow", "Latent Effectiveness at 100% Heating Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat75_HeatingAirFlow, "SensibleEffectivenessat75_HeatingAirFlow", "Sensible Effectiveness at 75% Heating Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat75_HeatingAirFlow, "LatentEffectivenessat75_HeatingAirFlow", "Latent Effectiveness at 75% Heating Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat100_CoolingAirFlow, "SensibleEffectivenessat100_CoolingAirFlow", "Sensible Effectiveness at 100% Cooling Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat100_CoolingAirFlow, "LatentEffectivenessat100_CoolingAirFlow", "Latent Effectiveness at 100% Cooling Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessat75_CoolingAirFlow, "SensibleEffectivenessat75_CoolingAirFlow", "Sensible Effectiveness at 75% Cooling Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessat75_CoolingAirFlow, "LatentEffectivenessat75_CoolingAirFlow", "Latent Effectiveness at 75% Cooling Air Flow"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName, "SupplyAirOutletNodeName", "Supply Air Outlet Node Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirInletNodeName, "ExhaustAirInletNodeName", "Exhaust Air Inlet Node Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::ExhaustAirOutletNodeName, "ExhaustAirOutletNodeName", "Exhaust Air Outlet Node Name"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::NominalElectricPower, "NominalElectricPower", "Nominal Electric Power"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletTemperatureControl, "SupplyAirOutletTemperatureControl", "Supply Air Outlet Temperature Control"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::HeatExchangerType, "HeatExchangerType", "Heat Exchanger Type"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::FrostControlType, "FrostControlType", "Frost Control Type"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::ThresholdTemperature, "ThresholdTemperature", "Threshold Temperature"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::InitialDefrostTimeFraction, "InitialDefrostTimeFraction", "Initial Defrost Time Fraction"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::RateofDefrostTimeFractionIncrease, "RateofDefrostTimeFractionIncrease", "Rate of Defrost Time Fraction Increase"},
{ HeatExchanger_AirToAir_SensibleAndLatentFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatExchanger_AirToAir_SensibleAndLatentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatExchanger_AirToAir_SensibleAndLatentFields> OptionalHeatExchanger_AirToAir_SensibleAndLatentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_SENSIBLEANDLATENT_FIELDENUMS_HXX
