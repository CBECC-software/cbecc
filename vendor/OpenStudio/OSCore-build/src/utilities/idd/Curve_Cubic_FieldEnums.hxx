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

#ifndef UTILITIES_IDD_CURVE_CUBIC_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_CUBIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_CubicFields
 *  \brief Enumeration of Curve:Cubic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_CubicFields, )
#else
class Curve_CubicFields: public ::EnumBase<Curve_CubicFields> {
 public: 
  enum domain 
  {
Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4x_POW_3, MinimumValueofx, MaximumValueofx, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, OutputUnitType,   };
  Curve_CubicFields()
   : EnumBase<Curve_CubicFields>(Name) {} 
  Curve_CubicFields(const std::string &t_name) 
   : EnumBase<Curve_CubicFields>(t_name) {} 
  Curve_CubicFields(int t_value) 
   : EnumBase<Curve_CubicFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_CubicFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_CubicFields>::value()); }
   private:
    friend class EnumBase<Curve_CubicFields>;
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
{ Curve_CubicFields::Name, "Name", "Name"},
{ Curve_CubicFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ Curve_CubicFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ Curve_CubicFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ Curve_CubicFields::Coefficient4x_POW_3, "Coefficient4x_POW_3", "Coefficient4 x**3"},
{ Curve_CubicFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_CubicFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_CubicFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_CubicFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_CubicFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Curve_CubicFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_CubicFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_CubicFields> OptionalCurve_CubicFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_CUBIC_FIELDENUMS_HXX
