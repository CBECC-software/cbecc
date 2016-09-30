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

#ifndef UTILITIES_IDD_CURVE_FUNCTIONAL_PRESSUREDROP_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_FUNCTIONAL_PRESSUREDROP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_Functional_PressureDropFields
 *  \brief Enumeration of Curve:Functional:PressureDrop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_Functional_PressureDropFields, )
#else
class Curve_Functional_PressureDropFields: public ::EnumBase<Curve_Functional_PressureDropFields> {
 public: 
  enum domain 
  {
Name, Diameter, MinorLossCoefficient, Length, Roughness, FixedFrictionFactor,   };
  Curve_Functional_PressureDropFields()
   : EnumBase<Curve_Functional_PressureDropFields>(Name) {} 
  Curve_Functional_PressureDropFields(const std::string &t_name) 
   : EnumBase<Curve_Functional_PressureDropFields>(t_name) {} 
  Curve_Functional_PressureDropFields(int t_value) 
   : EnumBase<Curve_Functional_PressureDropFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_Functional_PressureDropFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_Functional_PressureDropFields>::value()); }
   private:
    friend class EnumBase<Curve_Functional_PressureDropFields>;
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
{ Curve_Functional_PressureDropFields::Name, "Name", "Name"},
{ Curve_Functional_PressureDropFields::Diameter, "Diameter", "Diameter"},
{ Curve_Functional_PressureDropFields::MinorLossCoefficient, "MinorLossCoefficient", "Minor Loss Coefficient"},
{ Curve_Functional_PressureDropFields::Length, "Length", "Length"},
{ Curve_Functional_PressureDropFields::Roughness, "Roughness", "Roughness"},
{ Curve_Functional_PressureDropFields::FixedFrictionFactor, "FixedFrictionFactor", "Fixed Friction Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_Functional_PressureDropFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_Functional_PressureDropFields> OptionalCurve_Functional_PressureDropFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_FUNCTIONAL_PRESSUREDROP_FIELDENUMS_HXX
