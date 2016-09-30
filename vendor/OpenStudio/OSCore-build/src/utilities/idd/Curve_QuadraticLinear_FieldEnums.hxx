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

#ifndef UTILITIES_IDD_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_QuadraticLinearFields
 *  \brief Enumeration of Curve:QuadraticLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_QuadraticLinearFields, )
#else
class Curve_QuadraticLinearFields: public ::EnumBase<Curve_QuadraticLinearFields> {
 public: 
  enum domain 
  {
Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4y, Coefficient5x_TIMES_y, Coefficient6x_POW_2_TIMES_y, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, InputUnitTypeforY, OutputUnitType,   };
  Curve_QuadraticLinearFields()
   : EnumBase<Curve_QuadraticLinearFields>(Name) {} 
  Curve_QuadraticLinearFields(const std::string &t_name) 
   : EnumBase<Curve_QuadraticLinearFields>(t_name) {} 
  Curve_QuadraticLinearFields(int t_value) 
   : EnumBase<Curve_QuadraticLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_QuadraticLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_QuadraticLinearFields>::value()); }
   private:
    friend class EnumBase<Curve_QuadraticLinearFields>;
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
{ Curve_QuadraticLinearFields::Name, "Name", "Name"},
{ Curve_QuadraticLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ Curve_QuadraticLinearFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ Curve_QuadraticLinearFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ Curve_QuadraticLinearFields::Coefficient4y, "Coefficient4y", "Coefficient4 y"},
{ Curve_QuadraticLinearFields::Coefficient5x_TIMES_y, "Coefficient5x_TIMES_y", "Coefficient5 x*y"},
{ Curve_QuadraticLinearFields::Coefficient6x_POW_2_TIMES_y, "Coefficient6x_POW_2_TIMES_y", "Coefficient6 x**2*y"},
{ Curve_QuadraticLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_QuadraticLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_QuadraticLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ Curve_QuadraticLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ Curve_QuadraticLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_QuadraticLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_QuadraticLinearFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Curve_QuadraticLinearFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ Curve_QuadraticLinearFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_QuadraticLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_QuadraticLinearFields> OptionalCurve_QuadraticLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX
