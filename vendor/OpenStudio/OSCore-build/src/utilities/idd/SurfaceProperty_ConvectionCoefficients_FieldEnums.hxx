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

#ifndef UTILITIES_IDD_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_ConvectionCoefficientsFields
 *  \brief Enumeration of SurfaceProperty:ConvectionCoefficients's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_ConvectionCoefficientsFields, )
#else
class SurfaceProperty_ConvectionCoefficientsFields: public ::EnumBase<SurfaceProperty_ConvectionCoefficientsFields> {
 public: 
  enum domain 
  {
SurfaceName, ConvectionCoefficient1Location, ConvectionCoefficient1Type, ConvectionCoefficient1, ConvectionCoefficient1ScheduleName, ConvectionCoefficient1UserCurveName, ConvectionCoefficient2Location, ConvectionCoefficient2Type, ConvectionCoefficient2, ConvectionCoefficient2ScheduleName, ConvectionCoefficient2UserCurveName,   };
  SurfaceProperty_ConvectionCoefficientsFields()
   : EnumBase<SurfaceProperty_ConvectionCoefficientsFields>(SurfaceName) {} 
  SurfaceProperty_ConvectionCoefficientsFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_ConvectionCoefficientsFields>(t_name) {} 
  SurfaceProperty_ConvectionCoefficientsFields(int t_value) 
   : EnumBase<SurfaceProperty_ConvectionCoefficientsFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_ConvectionCoefficientsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_ConvectionCoefficientsFields>::value()); }
   private:
    friend class EnumBase<SurfaceProperty_ConvectionCoefficientsFields>;
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
{ SurfaceProperty_ConvectionCoefficientsFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location, "ConvectionCoefficient1Location", "Convection Coefficient 1 Location"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type, "ConvectionCoefficient1Type", "Convection Coefficient 1 Type"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1, "ConvectionCoefficient1", "Convection Coefficient 1"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1ScheduleName, "ConvectionCoefficient1ScheduleName", "Convection Coefficient 1 Schedule Name"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1UserCurveName, "ConvectionCoefficient1UserCurveName", "Convection Coefficient 1 User Curve Name"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location, "ConvectionCoefficient2Location", "Convection Coefficient 2 Location"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type, "ConvectionCoefficient2Type", "Convection Coefficient 2 Type"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2, "ConvectionCoefficient2", "Convection Coefficient 2"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2ScheduleName, "ConvectionCoefficient2ScheduleName", "Convection Coefficient 2 Schedule Name"},
{ SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2UserCurveName, "ConvectionCoefficient2UserCurveName", "Convection Coefficient 2 User Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_ConvectionCoefficientsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_ConvectionCoefficientsFields> OptionalSurfaceProperty_ConvectionCoefficientsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX
