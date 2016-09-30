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

#ifndef UTILITIES_IDD_OS_CURVE_BIQUADRATIC_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_BIQUADRATIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_BiquadraticFields
 *  \brief Enumeration of OS:Curve:Biquadratic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_BiquadraticFields, )
#else
class OS_Curve_BiquadraticFields: public ::EnumBase<OS_Curve_BiquadraticFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4y, Coefficient5y_POW_2, Coefficient6x_TIMES_y, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, InputUnitTypeforY, OutputUnitType,   };
  OS_Curve_BiquadraticFields()
   : EnumBase<OS_Curve_BiquadraticFields>(Handle) {} 
  OS_Curve_BiquadraticFields(const std::string &t_name) 
   : EnumBase<OS_Curve_BiquadraticFields>(t_name) {} 
  OS_Curve_BiquadraticFields(int t_value) 
   : EnumBase<OS_Curve_BiquadraticFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_BiquadraticFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_BiquadraticFields>::value()); }
   private:
    friend class EnumBase<OS_Curve_BiquadraticFields>;
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
{ OS_Curve_BiquadraticFields::Handle, "Handle", "Handle"},
{ OS_Curve_BiquadraticFields::Name, "Name", "Name"},
{ OS_Curve_BiquadraticFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ OS_Curve_BiquadraticFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ OS_Curve_BiquadraticFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ OS_Curve_BiquadraticFields::Coefficient4y, "Coefficient4y", "Coefficient4 y"},
{ OS_Curve_BiquadraticFields::Coefficient5y_POW_2, "Coefficient5y_POW_2", "Coefficient5 y**2"},
{ OS_Curve_BiquadraticFields::Coefficient6x_TIMES_y, "Coefficient6x_TIMES_y", "Coefficient6 x*y"},
{ OS_Curve_BiquadraticFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_BiquadraticFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_BiquadraticFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ OS_Curve_BiquadraticFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ OS_Curve_BiquadraticFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_BiquadraticFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_BiquadraticFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ OS_Curve_BiquadraticFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ OS_Curve_BiquadraticFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_BiquadraticFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_BiquadraticFields> OptionalOS_Curve_BiquadraticFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_BIQUADRATIC_FIELDENUMS_HXX
