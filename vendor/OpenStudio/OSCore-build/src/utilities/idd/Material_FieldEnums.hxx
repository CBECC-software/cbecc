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

#ifndef UTILITIES_IDD_MATERIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialFields
 *  \brief Enumeration of Material's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialFields, )
#else
class MaterialFields: public ::EnumBase<MaterialFields> {
 public: 
  enum domain 
  {
Name, Roughness, Thickness, Conductivity, Density, SpecificHeat, ThermalAbsorptance, SolarAbsorptance, VisibleAbsorptance,   };
  MaterialFields()
   : EnumBase<MaterialFields>(Name) {} 
  MaterialFields(const std::string &t_name) 
   : EnumBase<MaterialFields>(t_name) {} 
  MaterialFields(int t_value) 
   : EnumBase<MaterialFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialFields>::value()); }
   private:
    friend class EnumBase<MaterialFields>;
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
{ MaterialFields::Name, "Name", "Name"},
{ MaterialFields::Roughness, "Roughness", "Roughness"},
{ MaterialFields::Thickness, "Thickness", "Thickness"},
{ MaterialFields::Conductivity, "Conductivity", "Conductivity"},
{ MaterialFields::Density, "Density", "Density"},
{ MaterialFields::SpecificHeat, "SpecificHeat", "Specific Heat"},
{ MaterialFields::ThermalAbsorptance, "ThermalAbsorptance", "Thermal Absorptance"},
{ MaterialFields::SolarAbsorptance, "SolarAbsorptance", "Solar Absorptance"},
{ MaterialFields::VisibleAbsorptance, "VisibleAbsorptance", "Visible Absorptance"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialFields> OptionalMaterialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIAL_FIELDENUMS_HXX
