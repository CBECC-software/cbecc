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

#ifndef UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX
#define UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Humidifier_Steam_ElectricFields
 *  \brief Enumeration of Humidifier:Steam:Electric's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Humidifier_Steam_ElectricFields, )
#else
class Humidifier_Steam_ElectricFields: public ::EnumBase<Humidifier_Steam_ElectricFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RatedCapacity, RatedPower, RatedFanPower, StandbyPower, AirInletNodeName, AirOutletNodeName, WaterStorageTankName,   };
  Humidifier_Steam_ElectricFields()
   : EnumBase<Humidifier_Steam_ElectricFields>(Name) {} 
  Humidifier_Steam_ElectricFields(const std::string &t_name) 
   : EnumBase<Humidifier_Steam_ElectricFields>(t_name) {} 
  Humidifier_Steam_ElectricFields(int t_value) 
   : EnumBase<Humidifier_Steam_ElectricFields>(t_value) {} 
  static std::string enumName() 
  { return "Humidifier_Steam_ElectricFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Humidifier_Steam_ElectricFields>::value()); }
   private:
    friend class EnumBase<Humidifier_Steam_ElectricFields>;
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
{ Humidifier_Steam_ElectricFields::Name, "Name", "Name"},
{ Humidifier_Steam_ElectricFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Humidifier_Steam_ElectricFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ Humidifier_Steam_ElectricFields::RatedPower, "RatedPower", "Rated Power"},
{ Humidifier_Steam_ElectricFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Humidifier_Steam_ElectricFields::StandbyPower, "StandbyPower", "Standby Power"},
{ Humidifier_Steam_ElectricFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Humidifier_Steam_ElectricFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Humidifier_Steam_ElectricFields::WaterStorageTankName, "WaterStorageTankName", "Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Humidifier_Steam_ElectricFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Humidifier_Steam_ElectricFields> OptionalHumidifier_Steam_ElectricFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HUMIDIFIER_STEAM_ELECTRIC_FIELDENUMS_HXX
