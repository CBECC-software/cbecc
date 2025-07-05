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

#ifndef UTILITIES_IDD_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Humidifier_Steam_GasFields
 *  \brief Enumeration of Humidifier:Steam:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Humidifier_Steam_GasFields, )
#else
class Humidifier_Steam_GasFields: public ::EnumBase<Humidifier_Steam_GasFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RatedCapacity, RatedGasUseRate, ThermalEfficiency, ThermalEfficiencyModifierCurveName, RatedFanPower, AuxiliaryElectricPower, AirInletNodeName, AirOutletNodeName, WaterStorageTankName, InletWaterTemperatureOption,   };
  Humidifier_Steam_GasFields()
   : EnumBase<Humidifier_Steam_GasFields>(Name) {} 
  Humidifier_Steam_GasFields(const std::string &t_name) 
   : EnumBase<Humidifier_Steam_GasFields>(t_name) {} 
  Humidifier_Steam_GasFields(int t_value) 
   : EnumBase<Humidifier_Steam_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "Humidifier_Steam_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Humidifier_Steam_GasFields>::value()); }
   private:
    friend class EnumBase<Humidifier_Steam_GasFields>;
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
{ Humidifier_Steam_GasFields::Name, "Name", "Name"},
{ Humidifier_Steam_GasFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Humidifier_Steam_GasFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ Humidifier_Steam_GasFields::RatedGasUseRate, "RatedGasUseRate", "Rated Gas Use Rate"},
{ Humidifier_Steam_GasFields::ThermalEfficiency, "ThermalEfficiency", "Thermal Efficiency"},
{ Humidifier_Steam_GasFields::ThermalEfficiencyModifierCurveName, "ThermalEfficiencyModifierCurveName", "Thermal Efficiency Modifier Curve Name"},
{ Humidifier_Steam_GasFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Humidifier_Steam_GasFields::AuxiliaryElectricPower, "AuxiliaryElectricPower", "Auxiliary Electric Power"},
{ Humidifier_Steam_GasFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Humidifier_Steam_GasFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Humidifier_Steam_GasFields::WaterStorageTankName, "WaterStorageTankName", "Water Storage Tank Name"},
{ Humidifier_Steam_GasFields::InletWaterTemperatureOption, "InletWaterTemperatureOption", "Inlet Water Temperature Option"},
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
  inline std::ostream &operator<<(std::ostream &os, const Humidifier_Steam_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Humidifier_Steam_GasFields> OptionalHumidifier_Steam_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX
