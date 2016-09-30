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

#ifndef UTILITIES_IDD_CURVE_CUBICLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_CUBICLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_CubicLinearFields
 *  \brief Enumeration of Curve:CubicLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_CubicLinearFields, )
#else
class Curve_CubicLinearFields: public ::EnumBase<Curve_CubicLinearFields> {
 public: 
  enum domain 
  {
Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4x_POW_3, Coefficient5y, Coefficient6x_TIMES_y, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, InputUnitTypeforY, OutputUnitType,   };
  Curve_CubicLinearFields()
   : EnumBase<Curve_CubicLinearFields>(Name) {} 
  Curve_CubicLinearFields(const std::string &t_name) 
   : EnumBase<Curve_CubicLinearFields>(t_name) {} 
  Curve_CubicLinearFields(int t_value) 
   : EnumBase<Curve_CubicLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_CubicLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_CubicLinearFields>::value()); }
   private:
    friend class EnumBase<Curve_CubicLinearFields>;
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
{ Curve_CubicLinearFields::Name, "Name", "Name"},
{ Curve_CubicLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ Curve_CubicLinearFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ Curve_CubicLinearFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ Curve_CubicLinearFields::Coefficient4x_POW_3, "Coefficient4x_POW_3", "Coefficient4 x**3"},
{ Curve_CubicLinearFields::Coefficient5y, "Coefficient5y", "Coefficient5 y"},
{ Curve_CubicLinearFields::Coefficient6x_TIMES_y, "Coefficient6x_TIMES_y", "Coefficient6 x*y"},
{ Curve_CubicLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_CubicLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_CubicLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ Curve_CubicLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ Curve_CubicLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_CubicLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_CubicLinearFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Curve_CubicLinearFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ Curve_CubicLinearFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_CubicLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_CubicLinearFields> OptionalCurve_CubicLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_CUBICLINEAR_FIELDENUMS_HXX
