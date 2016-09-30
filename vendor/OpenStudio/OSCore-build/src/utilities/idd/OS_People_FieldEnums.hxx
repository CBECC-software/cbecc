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

#ifndef UTILITIES_IDD_OS_PEOPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PEOPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PeopleFields
 *  \brief Enumeration of OS:People's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PeopleFields, )
#else
class OS_PeopleFields: public ::EnumBase<OS_PeopleFields> {
 public: 
  enum domain 
  {
Handle, Name, PeopleDefinitionName, SpaceorSpaceTypeName, NumberofPeopleScheduleName, ActivityLevelScheduleName, SurfaceName_AngleFactorListName, WorkEfficiencyScheduleName, ClothingInsulationScheduleName, AirVelocityScheduleName, Multiplier,   };
  OS_PeopleFields()
   : EnumBase<OS_PeopleFields>(Handle) {} 
  OS_PeopleFields(const std::string &t_name) 
   : EnumBase<OS_PeopleFields>(t_name) {} 
  OS_PeopleFields(int t_value) 
   : EnumBase<OS_PeopleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PeopleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PeopleFields>::value()); }
   private:
    friend class EnumBase<OS_PeopleFields>;
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
{ OS_PeopleFields::Handle, "Handle", "Handle"},
{ OS_PeopleFields::Name, "Name", "Name"},
{ OS_PeopleFields::PeopleDefinitionName, "PeopleDefinitionName", "People Definition Name"},
{ OS_PeopleFields::SpaceorSpaceTypeName, "SpaceorSpaceTypeName", "Space or SpaceType Name"},
{ OS_PeopleFields::NumberofPeopleScheduleName, "NumberofPeopleScheduleName", "Number of People Schedule Name"},
{ OS_PeopleFields::ActivityLevelScheduleName, "ActivityLevelScheduleName", "Activity Level Schedule Name"},
{ OS_PeopleFields::SurfaceName_AngleFactorListName, "SurfaceName_AngleFactorListName", "Surface Name/Angle Factor List Name"},
{ OS_PeopleFields::WorkEfficiencyScheduleName, "WorkEfficiencyScheduleName", "Work Efficiency Schedule Name"},
{ OS_PeopleFields::ClothingInsulationScheduleName, "ClothingInsulationScheduleName", "Clothing Insulation Schedule Name"},
{ OS_PeopleFields::AirVelocityScheduleName, "AirVelocityScheduleName", "Air Velocity Schedule Name"},
{ OS_PeopleFields::Multiplier, "Multiplier", "Multiplier"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PeopleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PeopleFields> OptionalOS_PeopleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PEOPLE_FIELDENUMS_HXX
