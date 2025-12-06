/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricLoadCenter_Storage_SimpleFields
 *  \brief Enumeration of OS:ElectricLoadCenter:Storage:Simple's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricLoadCenter_Storage_SimpleFields, )
#else
class OS_ElectricLoadCenter_Storage_SimpleFields: public ::EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, ZoneName, RadiativeFractionforZoneHeatGains, NominalEnergeticEfficiencyforCharging, NominalDischargingEnergeticEfficiency, MaximumStorageCapacity, MaximumPowerforDischarging, MaximumPowerforCharging, InitialStateofCharge,   };
  OS_ElectricLoadCenter_Storage_SimpleFields()
   : EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields>(Handle) {} 
  OS_ElectricLoadCenter_Storage_SimpleFields(const std::string &t_name) 
   : EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields>(t_name) {} 
  OS_ElectricLoadCenter_Storage_SimpleFields(int t_value) 
   : EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricLoadCenter_Storage_SimpleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricLoadCenter_Storage_SimpleFields>;
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
{ OS_ElectricLoadCenter_Storage_SimpleFields::Handle, "Handle", "Handle"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::Name, "Name", "Name"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains, "RadiativeFractionforZoneHeatGains", "Radiative Fraction for Zone Heat Gains"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging, "NominalEnergeticEfficiencyforCharging", "Nominal Energetic Efficiency for Charging"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency, "NominalDischargingEnergeticEfficiency", "Nominal Discharging Energetic Efficiency"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::MaximumStorageCapacity, "MaximumStorageCapacity", "Maximum Storage Capacity"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforDischarging, "MaximumPowerforDischarging", "Maximum Power for Discharging"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforCharging, "MaximumPowerforCharging", "Maximum Power for Charging"},
{ OS_ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge, "InitialStateofCharge", "Initial State of Charge"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricLoadCenter_Storage_SimpleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricLoadCenter_Storage_SimpleFields> OptionalOS_ElectricLoadCenter_Storage_SimpleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX
