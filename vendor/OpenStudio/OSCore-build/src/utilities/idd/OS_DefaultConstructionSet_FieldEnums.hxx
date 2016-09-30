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

#ifndef UTILITIES_IDD_OS_DEFAULTCONSTRUCTIONSET_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DEFAULTCONSTRUCTIONSET_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_DefaultConstructionSetFields
 *  \brief Enumeration of OS:DefaultConstructionSet's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_DefaultConstructionSetFields, )
#else
class OS_DefaultConstructionSetFields: public ::EnumBase<OS_DefaultConstructionSetFields> {
 public: 
  enum domain 
  {
Handle, Name, DefaultExteriorSurfaceConstructionsName, DefaultInteriorSurfaceConstructionsName, DefaultGroundContactSurfaceConstructionsName, DefaultExteriorSubSurfaceConstructionsName, DefaultInteriorSubSurfaceConstructionsName, InteriorPartitionConstructionName, SpaceShadingConstructionName, BuildingShadingConstructionName, SiteShadingConstructionName,   };
  OS_DefaultConstructionSetFields()
   : EnumBase<OS_DefaultConstructionSetFields>(Handle) {} 
  OS_DefaultConstructionSetFields(const std::string &t_name) 
   : EnumBase<OS_DefaultConstructionSetFields>(t_name) {} 
  OS_DefaultConstructionSetFields(int t_value) 
   : EnumBase<OS_DefaultConstructionSetFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DefaultConstructionSetFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DefaultConstructionSetFields>::value()); }
   private:
    friend class EnumBase<OS_DefaultConstructionSetFields>;
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
{ OS_DefaultConstructionSetFields::Handle, "Handle", "Handle"},
{ OS_DefaultConstructionSetFields::Name, "Name", "Name"},
{ OS_DefaultConstructionSetFields::DefaultExteriorSurfaceConstructionsName, "DefaultExteriorSurfaceConstructionsName", "Default Exterior Surface Constructions Name"},
{ OS_DefaultConstructionSetFields::DefaultInteriorSurfaceConstructionsName, "DefaultInteriorSurfaceConstructionsName", "Default Interior Surface Constructions Name"},
{ OS_DefaultConstructionSetFields::DefaultGroundContactSurfaceConstructionsName, "DefaultGroundContactSurfaceConstructionsName", "Default Ground Contact Surface Constructions Name"},
{ OS_DefaultConstructionSetFields::DefaultExteriorSubSurfaceConstructionsName, "DefaultExteriorSubSurfaceConstructionsName", "Default Exterior SubSurface Constructions Name"},
{ OS_DefaultConstructionSetFields::DefaultInteriorSubSurfaceConstructionsName, "DefaultInteriorSubSurfaceConstructionsName", "Default Interior SubSurface Constructions Name"},
{ OS_DefaultConstructionSetFields::InteriorPartitionConstructionName, "InteriorPartitionConstructionName", "Interior Partition Construction Name"},
{ OS_DefaultConstructionSetFields::SpaceShadingConstructionName, "SpaceShadingConstructionName", "Space Shading Construction Name"},
{ OS_DefaultConstructionSetFields::BuildingShadingConstructionName, "BuildingShadingConstructionName", "Building Shading Construction Name"},
{ OS_DefaultConstructionSetFields::SiteShadingConstructionName, "SiteShadingConstructionName", "Site Shading Construction Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DefaultConstructionSetFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DefaultConstructionSetFields> OptionalOS_DefaultConstructionSetFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DEFAULTCONSTRUCTIONSET_FIELDENUMS_HXX
