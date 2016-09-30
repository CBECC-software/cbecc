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

#ifndef UTILITIES_IDD_OS_SPACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SPACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SpaceFields
 *  \brief Enumeration of OS:Space's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SpaceFields, )
#else
class OS_SpaceFields: public ::EnumBase<OS_SpaceFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceTypeName, DefaultConstructionSetName, DefaultScheduleSetName, DirectionofRelativeNorth, XOrigin, YOrigin, ZOrigin, BuildingStoryName, ThermalZoneName, PartofTotalFloorArea, DesignSpecificationOutdoorAirObjectName,   };
  OS_SpaceFields()
   : EnumBase<OS_SpaceFields>(Handle) {} 
  OS_SpaceFields(const std::string &t_name) 
   : EnumBase<OS_SpaceFields>(t_name) {} 
  OS_SpaceFields(int t_value) 
   : EnumBase<OS_SpaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SpaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SpaceFields>::value()); }
   private:
    friend class EnumBase<OS_SpaceFields>;
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
{ OS_SpaceFields::Handle, "Handle", "Handle"},
{ OS_SpaceFields::Name, "Name", "Name"},
{ OS_SpaceFields::SpaceTypeName, "SpaceTypeName", "Space Type Name"},
{ OS_SpaceFields::DefaultConstructionSetName, "DefaultConstructionSetName", "Default Construction Set Name"},
{ OS_SpaceFields::DefaultScheduleSetName, "DefaultScheduleSetName", "Default Schedule Set Name"},
{ OS_SpaceFields::DirectionofRelativeNorth, "DirectionofRelativeNorth", "Direction of Relative North"},
{ OS_SpaceFields::XOrigin, "XOrigin", "X Origin"},
{ OS_SpaceFields::YOrigin, "YOrigin", "Y Origin"},
{ OS_SpaceFields::ZOrigin, "ZOrigin", "Z Origin"},
{ OS_SpaceFields::BuildingStoryName, "BuildingStoryName", "Building Story Name"},
{ OS_SpaceFields::ThermalZoneName, "ThermalZoneName", "Thermal Zone Name"},
{ OS_SpaceFields::PartofTotalFloorArea, "PartofTotalFloorArea", "Part of Total Floor Area"},
{ OS_SpaceFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SpaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SpaceFields> OptionalOS_SpaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SPACE_FIELDENUMS_HXX
