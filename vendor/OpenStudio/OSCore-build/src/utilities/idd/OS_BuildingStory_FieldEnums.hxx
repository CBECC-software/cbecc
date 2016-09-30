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

#ifndef UTILITIES_IDD_OS_BUILDINGSTORY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_BUILDINGSTORY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_BuildingStoryFields
 *  \brief Enumeration of OS:BuildingStory's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_BuildingStoryFields, )
#else
class OS_BuildingStoryFields: public ::EnumBase<OS_BuildingStoryFields> {
 public: 
  enum domain 
  {
Handle, Name, NominalZCoordinate, NominalFloortoFloorHeight, DefaultConstructionSetName, DefaultScheduleSetName, GroupRenderingName, NominalFloortoCeilingHeight,   };
  OS_BuildingStoryFields()
   : EnumBase<OS_BuildingStoryFields>(Handle) {} 
  OS_BuildingStoryFields(const std::string &t_name) 
   : EnumBase<OS_BuildingStoryFields>(t_name) {} 
  OS_BuildingStoryFields(int t_value) 
   : EnumBase<OS_BuildingStoryFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_BuildingStoryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_BuildingStoryFields>::value()); }
   private:
    friend class EnumBase<OS_BuildingStoryFields>;
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
{ OS_BuildingStoryFields::Handle, "Handle", "Handle"},
{ OS_BuildingStoryFields::Name, "Name", "Name"},
{ OS_BuildingStoryFields::NominalZCoordinate, "NominalZCoordinate", "Nominal Z Coordinate"},
{ OS_BuildingStoryFields::NominalFloortoFloorHeight, "NominalFloortoFloorHeight", "Nominal Floor to Floor Height"},
{ OS_BuildingStoryFields::DefaultConstructionSetName, "DefaultConstructionSetName", "Default Construction Set Name"},
{ OS_BuildingStoryFields::DefaultScheduleSetName, "DefaultScheduleSetName", "Default Schedule Set Name"},
{ OS_BuildingStoryFields::GroupRenderingName, "GroupRenderingName", "Group Rendering Name"},
{ OS_BuildingStoryFields::NominalFloortoCeilingHeight, "NominalFloortoCeilingHeight", "Nominal Floor to Ceiling Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_BuildingStoryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_BuildingStoryFields> OptionalOS_BuildingStoryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_BUILDINGSTORY_FIELDENUMS_HXX
