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

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_MULTIPLESURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_MULTIPLESURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields
 *  \brief Enumeration of OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields, )
#else
class OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields: public ::EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields> {
 public: 
  enum domain 
  {
Handle, SurfaceType, ConvectionCoefficient1Location, ConvectionCoefficient1Type, ConvectionCoefficient1, ConvectionCoefficient1ScheduleName, ConvectionCoefficient1UserCurveName, ConvectionCoefficient2Location, ConvectionCoefficient2Type, ConvectionCoefficient2, ConvectionCoefficient2ScheduleName, ConvectionCoefficient2UserCurveName,   };
  OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields()
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields>(Handle) {} 
  OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields>(t_name) {} 
  OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields>;
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
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::SurfaceType, "SurfaceType", "Surface Type"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Location, "ConvectionCoefficient1Location", "Convection Coefficient 1 Location"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Type, "ConvectionCoefficient1Type", "Convection Coefficient 1 Type"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1, "ConvectionCoefficient1", "Convection Coefficient 1"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1ScheduleName, "ConvectionCoefficient1ScheduleName", "Convection Coefficient 1 Schedule Name"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1UserCurveName, "ConvectionCoefficient1UserCurveName", "Convection Coefficient 1 User Curve Name"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Location, "ConvectionCoefficient2Location", "Convection Coefficient 2 Location"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Type, "ConvectionCoefficient2Type", "Convection Coefficient 2 Type"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2, "ConvectionCoefficient2", "Convection Coefficient 2"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2ScheduleName, "ConvectionCoefficient2ScheduleName", "Convection Coefficient 2 Schedule Name"},
{ OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2UserCurveName, "ConvectionCoefficient2UserCurveName", "Convection Coefficient 2 User Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields> OptionalOS_SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_MULTIPLESURFACE_FIELDENUMS_HXX
