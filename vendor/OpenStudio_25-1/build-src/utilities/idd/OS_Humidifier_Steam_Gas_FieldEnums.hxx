/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Humidifier_Steam_GasFields
 *  \brief Enumeration of OS:Humidifier:Steam:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Humidifier_Steam_GasFields, )
#else
class OS_Humidifier_Steam_GasFields: public ::EnumBase<OS_Humidifier_Steam_GasFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RatedCapacity, RatedGasUseRate, ThermalEfficiency, ThermalEfficiencyModifierCurveName, RatedFanPower, AuxiliaryElectricPower, AirInletNodeName, AirOutletNodeName, WaterStorageTankName, InletWaterTemperatureOption,   };
  OS_Humidifier_Steam_GasFields()
   : EnumBase<OS_Humidifier_Steam_GasFields>(Handle) {} 
  OS_Humidifier_Steam_GasFields(const std::string &t_name) 
   : EnumBase<OS_Humidifier_Steam_GasFields>(t_name) {} 
  OS_Humidifier_Steam_GasFields(int t_value) 
   : EnumBase<OS_Humidifier_Steam_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Humidifier_Steam_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Humidifier_Steam_GasFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Humidifier_Steam_GasFields>;
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
{ OS_Humidifier_Steam_GasFields::Handle, "Handle", "Handle"},
{ OS_Humidifier_Steam_GasFields::Name, "Name", "Name"},
{ OS_Humidifier_Steam_GasFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Humidifier_Steam_GasFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ OS_Humidifier_Steam_GasFields::RatedGasUseRate, "RatedGasUseRate", "Rated Gas Use Rate"},
{ OS_Humidifier_Steam_GasFields::ThermalEfficiency, "ThermalEfficiency", "Thermal Efficiency"},
{ OS_Humidifier_Steam_GasFields::ThermalEfficiencyModifierCurveName, "ThermalEfficiencyModifierCurveName", "Thermal Efficiency Modifier Curve Name"},
{ OS_Humidifier_Steam_GasFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ OS_Humidifier_Steam_GasFields::AuxiliaryElectricPower, "AuxiliaryElectricPower", "Auxiliary Electric Power"},
{ OS_Humidifier_Steam_GasFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Humidifier_Steam_GasFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Humidifier_Steam_GasFields::WaterStorageTankName, "WaterStorageTankName", "Water Storage Tank Name"},
{ OS_Humidifier_Steam_GasFields::InletWaterTemperatureOption, "InletWaterTemperatureOption", "Inlet Water Temperature Option"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Humidifier_Steam_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Humidifier_Steam_GasFields> OptionalOS_Humidifier_Steam_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HUMIDIFIER_STEAM_GAS_FIELDENUMS_HXX
