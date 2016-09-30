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

#ifndef UTILITIES_IDD_COIL_HEATING_STEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_STEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_SteamFields
 *  \brief Enumeration of Coil:Heating:Steam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_SteamFields, )
#else
class Coil_Heating_SteamFields: public ::EnumBase<Coil_Heating_SteamFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumSteamFlowRate, DegreeofSubCooling, DegreeofLoopSubCooling, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, CoilControlType, TemperatureSetpointNodeName,   };
  Coil_Heating_SteamFields()
   : EnumBase<Coil_Heating_SteamFields>(Name) {} 
  Coil_Heating_SteamFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_SteamFields>(t_name) {} 
  Coil_Heating_SteamFields(int t_value) 
   : EnumBase<Coil_Heating_SteamFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_SteamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_SteamFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_SteamFields>;
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
{ Coil_Heating_SteamFields::Name, "Name", "Name"},
{ Coil_Heating_SteamFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_SteamFields::MaximumSteamFlowRate, "MaximumSteamFlowRate", "Maximum Steam Flow Rate"},
{ Coil_Heating_SteamFields::DegreeofSubCooling, "DegreeofSubCooling", "Degree of SubCooling"},
{ Coil_Heating_SteamFields::DegreeofLoopSubCooling, "DegreeofLoopSubCooling", "Degree of Loop SubCooling"},
{ Coil_Heating_SteamFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Heating_SteamFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Heating_SteamFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_SteamFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_SteamFields::CoilControlType, "CoilControlType", "Coil Control Type"},
{ Coil_Heating_SteamFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_SteamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_SteamFields> OptionalCoil_Heating_SteamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_STEAM_FIELDENUMS_HXX
