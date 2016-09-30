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

#ifndef UTILITIES_IDD_STEAMEQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_STEAMEQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SteamEquipmentFields
 *  \brief Enumeration of SteamEquipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SteamEquipmentFields, )
#else
class SteamEquipmentFields: public ::EnumBase<SteamEquipmentFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, ScheduleName, DesignLevelCalculationMethod, DesignLevel, PowerperZoneFloorArea, PowerperPerson, FractionLatent, FractionRadiant, FractionLost, EndUseSubcategory,   };
  SteamEquipmentFields()
   : EnumBase<SteamEquipmentFields>(Name) {} 
  SteamEquipmentFields(const std::string &t_name) 
   : EnumBase<SteamEquipmentFields>(t_name) {} 
  SteamEquipmentFields(int t_value) 
   : EnumBase<SteamEquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "SteamEquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SteamEquipmentFields>::value()); }
   private:
    friend class EnumBase<SteamEquipmentFields>;
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
{ SteamEquipmentFields::Name, "Name", "Name"},
{ SteamEquipmentFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ SteamEquipmentFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ SteamEquipmentFields::DesignLevelCalculationMethod, "DesignLevelCalculationMethod", "Design Level Calculation Method"},
{ SteamEquipmentFields::DesignLevel, "DesignLevel", "Design Level"},
{ SteamEquipmentFields::PowerperZoneFloorArea, "PowerperZoneFloorArea", "Power per Zone Floor Area"},
{ SteamEquipmentFields::PowerperPerson, "PowerperPerson", "Power per Person"},
{ SteamEquipmentFields::FractionLatent, "FractionLatent", "Fraction Latent"},
{ SteamEquipmentFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ SteamEquipmentFields::FractionLost, "FractionLost", "Fraction Lost"},
{ SteamEquipmentFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const SteamEquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SteamEquipmentFields> OptionalSteamEquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_STEAMEQUIPMENT_FIELDENUMS_HXX
