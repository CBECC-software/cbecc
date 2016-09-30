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

#ifndef UTILITIES_IDD_OS_BUILDING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_BUILDING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_BuildingFields
 *  \brief Enumeration of OS:Building's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_BuildingFields, )
#else
class OS_BuildingFields: public ::EnumBase<OS_BuildingFields> {
 public: 
  enum domain 
  {
Handle, Name, BuildingSectorType, NorthAxis, NominalFloortoFloorHeight, SpaceTypeName, DefaultConstructionSetName, DefaultScheduleSetName, StandardsNumberofStories, StandardsNumberofAboveGroundStories, StandardsBuildingType, StandardsNumberofLivingUnits, Relocatable, NominalFloortoCeilingHeight,   };
  OS_BuildingFields()
   : EnumBase<OS_BuildingFields>(Handle) {} 
  OS_BuildingFields(const std::string &t_name) 
   : EnumBase<OS_BuildingFields>(t_name) {} 
  OS_BuildingFields(int t_value) 
   : EnumBase<OS_BuildingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_BuildingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_BuildingFields>::value()); }
   private:
    friend class EnumBase<OS_BuildingFields>;
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
{ OS_BuildingFields::Handle, "Handle", "Handle"},
{ OS_BuildingFields::Name, "Name", "Name"},
{ OS_BuildingFields::BuildingSectorType, "BuildingSectorType", "Building Sector Type"},
{ OS_BuildingFields::NorthAxis, "NorthAxis", "North Axis"},
{ OS_BuildingFields::NominalFloortoFloorHeight, "NominalFloortoFloorHeight", "Nominal Floor to Floor Height"},
{ OS_BuildingFields::SpaceTypeName, "SpaceTypeName", "Space Type Name"},
{ OS_BuildingFields::DefaultConstructionSetName, "DefaultConstructionSetName", "Default Construction Set Name"},
{ OS_BuildingFields::DefaultScheduleSetName, "DefaultScheduleSetName", "Default Schedule Set Name"},
{ OS_BuildingFields::StandardsNumberofStories, "StandardsNumberofStories", "Standards Number of Stories"},
{ OS_BuildingFields::StandardsNumberofAboveGroundStories, "StandardsNumberofAboveGroundStories", "Standards Number of Above Ground Stories"},
{ OS_BuildingFields::StandardsBuildingType, "StandardsBuildingType", "Standards Building Type"},
{ OS_BuildingFields::StandardsNumberofLivingUnits, "StandardsNumberofLivingUnits", "Standards Number of Living Units"},
{ OS_BuildingFields::Relocatable, "Relocatable", "Relocatable"},
{ OS_BuildingFields::NominalFloortoCeilingHeight, "NominalFloortoCeilingHeight", "Nominal Floor to Ceiling Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_BuildingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_BuildingFields> OptionalOS_BuildingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_BUILDING_FIELDENUMS_HXX
