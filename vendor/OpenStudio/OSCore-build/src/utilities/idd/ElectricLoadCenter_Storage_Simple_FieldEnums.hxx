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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Storage_SimpleFields
 *  \brief Enumeration of ElectricLoadCenter:Storage:Simple's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Storage_SimpleFields, )
#else
class ElectricLoadCenter_Storage_SimpleFields: public ::EnumBase<ElectricLoadCenter_Storage_SimpleFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFractionforZoneHeatGains, NominalEnergeticEfficiencyforCharging, NominalDischargingEnergeticEfficiency, MaximumStorageCapacity, MaximumPowerforDischarging, MaximumPowerforCharging, InitialStateofCharge,   };
  ElectricLoadCenter_Storage_SimpleFields()
   : EnumBase<ElectricLoadCenter_Storage_SimpleFields>(Name) {} 
  ElectricLoadCenter_Storage_SimpleFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Storage_SimpleFields>(t_name) {} 
  ElectricLoadCenter_Storage_SimpleFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Storage_SimpleFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Storage_SimpleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Storage_SimpleFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Storage_SimpleFields>;
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
{ ElectricLoadCenter_Storage_SimpleFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Storage_SimpleFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Storage_SimpleFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Storage_SimpleFields::RadiativeFractionforZoneHeatGains, "RadiativeFractionforZoneHeatGains", "Radiative Fraction for Zone Heat Gains"},
{ ElectricLoadCenter_Storage_SimpleFields::NominalEnergeticEfficiencyforCharging, "NominalEnergeticEfficiencyforCharging", "Nominal Energetic Efficiency for Charging"},
{ ElectricLoadCenter_Storage_SimpleFields::NominalDischargingEnergeticEfficiency, "NominalDischargingEnergeticEfficiency", "Nominal Discharging Energetic Efficiency"},
{ ElectricLoadCenter_Storage_SimpleFields::MaximumStorageCapacity, "MaximumStorageCapacity", "Maximum Storage Capacity"},
{ ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforDischarging, "MaximumPowerforDischarging", "Maximum Power for Discharging"},
{ ElectricLoadCenter_Storage_SimpleFields::MaximumPowerforCharging, "MaximumPowerforCharging", "Maximum Power for Charging"},
{ ElectricLoadCenter_Storage_SimpleFields::InitialStateofCharge, "InitialStateofCharge", "Initial State of Charge"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Storage_SimpleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Storage_SimpleFields> OptionalElectricLoadCenter_Storage_SimpleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_SIMPLE_FIELDENUMS_HXX
