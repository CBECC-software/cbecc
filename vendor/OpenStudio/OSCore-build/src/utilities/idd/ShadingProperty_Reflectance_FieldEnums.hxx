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

#ifndef UTILITIES_IDD_SHADINGPROPERTY_REFLECTANCE_FIELDENUMS_HXX
#define UTILITIES_IDD_SHADINGPROPERTY_REFLECTANCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ShadingProperty_ReflectanceFields
 *  \brief Enumeration of ShadingProperty:Reflectance's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ShadingProperty_ReflectanceFields, )
#else
class ShadingProperty_ReflectanceFields: public ::EnumBase<ShadingProperty_ReflectanceFields> {
 public: 
  enum domain 
  {
ShadingSurfaceName, DiffuseSolarReflectanceofUnglazedPartofShadingSurface, DiffuseVisibleReflectanceofUnglazedPartofShadingSurface, FractionofShadingSurfaceThatIsGlazed, GlazingConstructionName,   };
  ShadingProperty_ReflectanceFields()
   : EnumBase<ShadingProperty_ReflectanceFields>(ShadingSurfaceName) {} 
  ShadingProperty_ReflectanceFields(const std::string &t_name) 
   : EnumBase<ShadingProperty_ReflectanceFields>(t_name) {} 
  ShadingProperty_ReflectanceFields(int t_value) 
   : EnumBase<ShadingProperty_ReflectanceFields>(t_value) {} 
  static std::string enumName() 
  { return "ShadingProperty_ReflectanceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ShadingProperty_ReflectanceFields>::value()); }
   private:
    friend class EnumBase<ShadingProperty_ReflectanceFields>;
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
{ ShadingProperty_ReflectanceFields::ShadingSurfaceName, "ShadingSurfaceName", "Shading Surface Name"},
{ ShadingProperty_ReflectanceFields::DiffuseSolarReflectanceofUnglazedPartofShadingSurface, "DiffuseSolarReflectanceofUnglazedPartofShadingSurface", "Diffuse Solar Reflectance of Unglazed Part of Shading Surface"},
{ ShadingProperty_ReflectanceFields::DiffuseVisibleReflectanceofUnglazedPartofShadingSurface, "DiffuseVisibleReflectanceofUnglazedPartofShadingSurface", "Diffuse Visible Reflectance of Unglazed Part of Shading Surface"},
{ ShadingProperty_ReflectanceFields::FractionofShadingSurfaceThatIsGlazed, "FractionofShadingSurfaceThatIsGlazed", "Fraction of Shading Surface That Is Glazed"},
{ ShadingProperty_ReflectanceFields::GlazingConstructionName, "GlazingConstructionName", "Glazing Construction Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ShadingProperty_ReflectanceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ShadingProperty_ReflectanceFields> OptionalShadingProperty_ReflectanceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SHADINGPROPERTY_REFLECTANCE_FIELDENUMS_HXX
