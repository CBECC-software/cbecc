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

#ifndef UTILITIES_IDD_OS_WINDOWMATERIAL_SHADE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWMATERIAL_SHADE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowMaterial_ShadeFields
 *  \brief Enumeration of OS:WindowMaterial:Shade's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowMaterial_ShadeFields, )
#else
class OS_WindowMaterial_ShadeFields: public ::EnumBase<OS_WindowMaterial_ShadeFields> {
 public: 
  enum domain 
  {
Handle, Name, SolarTransmittance, SolarReflectance, VisibleTransmittance, VisibleReflectance, ThermalHemisphericalEmissivity, ThermalTransmittance, Thickness, Conductivity, ShadetoGlassDistance, TopOpeningMultiplier, BottomOpeningMultiplier, LeftSideOpeningMultiplier, RightSideOpeningMultiplier, AirflowPermeability,   };
  OS_WindowMaterial_ShadeFields()
   : EnumBase<OS_WindowMaterial_ShadeFields>(Handle) {} 
  OS_WindowMaterial_ShadeFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_ShadeFields>(t_name) {} 
  OS_WindowMaterial_ShadeFields(int t_value) 
   : EnumBase<OS_WindowMaterial_ShadeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_ShadeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_ShadeFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_ShadeFields>;
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
{ OS_WindowMaterial_ShadeFields::Handle, "Handle", "Handle"},
{ OS_WindowMaterial_ShadeFields::Name, "Name", "Name"},
{ OS_WindowMaterial_ShadeFields::SolarTransmittance, "SolarTransmittance", "Solar Transmittance"},
{ OS_WindowMaterial_ShadeFields::SolarReflectance, "SolarReflectance", "Solar Reflectance"},
{ OS_WindowMaterial_ShadeFields::VisibleTransmittance, "VisibleTransmittance", "Visible Transmittance"},
{ OS_WindowMaterial_ShadeFields::VisibleReflectance, "VisibleReflectance", "Visible Reflectance"},
{ OS_WindowMaterial_ShadeFields::ThermalHemisphericalEmissivity, "ThermalHemisphericalEmissivity", "Thermal Hemispherical Emissivity"},
{ OS_WindowMaterial_ShadeFields::ThermalTransmittance, "ThermalTransmittance", "Thermal Transmittance"},
{ OS_WindowMaterial_ShadeFields::Thickness, "Thickness", "Thickness"},
{ OS_WindowMaterial_ShadeFields::Conductivity, "Conductivity", "Conductivity"},
{ OS_WindowMaterial_ShadeFields::ShadetoGlassDistance, "ShadetoGlassDistance", "Shade to Glass Distance"},
{ OS_WindowMaterial_ShadeFields::TopOpeningMultiplier, "TopOpeningMultiplier", "Top Opening Multiplier"},
{ OS_WindowMaterial_ShadeFields::BottomOpeningMultiplier, "BottomOpeningMultiplier", "Bottom Opening Multiplier"},
{ OS_WindowMaterial_ShadeFields::LeftSideOpeningMultiplier, "LeftSideOpeningMultiplier", "Left-Side Opening Multiplier"},
{ OS_WindowMaterial_ShadeFields::RightSideOpeningMultiplier, "RightSideOpeningMultiplier", "Right-Side Opening Multiplier"},
{ OS_WindowMaterial_ShadeFields::AirflowPermeability, "AirflowPermeability", "Airflow Permeability"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_ShadeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_ShadeFields> OptionalOS_WindowMaterial_ShadeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWMATERIAL_SHADE_FIELDENUMS_HXX
