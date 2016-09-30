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

#ifndef UTILITIES_IDD_OS_CURVE_TRIQUADRATIC_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_TRIQUADRATIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_TriquadraticFields
 *  \brief Enumeration of OS:Curve:Triquadratic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_TriquadraticFields, )
#else
class OS_Curve_TriquadraticFields: public ::EnumBase<OS_Curve_TriquadraticFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1Constant, Coefficient2x_POW_2, Coefficient3x, Coefficient4y_POW_2, Coefficient5y, Coefficient6z_POW_2, Coefficient7z, Coefficient8x_POW_2_TIMES_y_POW_2, Coefficient9x_TIMES_y, Coefficient10x_TIMES_y_POW_2, Coefficient11x_POW_2_TIMES_y, Coefficient12x_POW_2_TIMES_z_POW_2, Coefficient13x_TIMES_z, Coefficient14x_TIMES_z_POW_2, Coefficient15x_POW_2_TIMES_z, Coefficient16y_POW_2_TIMES_z_POW_2, Coefficient17y_TIMES_z, Coefficient18y_TIMES_z_POW_2, Coefficient19y_POW_2_TIMES_z, Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2, Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z, Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2, Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2, Coefficient24x_POW_2_TIMES_y_TIMES_z, Coefficient25x_TIMES_y_POW_2_TIMES_z, Coefficient26x_TIMES_y_TIMES_z_POW_2, Coefficient27x_TIMES_y_TIMES_z, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumValueofz, MaximumValueofz, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, InputUnitTypeforY, InputUnitTypeforZ, OutputUnitType,   };
  OS_Curve_TriquadraticFields()
   : EnumBase<OS_Curve_TriquadraticFields>(Handle) {} 
  OS_Curve_TriquadraticFields(const std::string &t_name) 
   : EnumBase<OS_Curve_TriquadraticFields>(t_name) {} 
  OS_Curve_TriquadraticFields(int t_value) 
   : EnumBase<OS_Curve_TriquadraticFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_TriquadraticFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_TriquadraticFields>::value()); }
   private:
    friend class EnumBase<OS_Curve_TriquadraticFields>;
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
{ OS_Curve_TriquadraticFields::Handle, "Handle", "Handle"},
{ OS_Curve_TriquadraticFields::Name, "Name", "Name"},
{ OS_Curve_TriquadraticFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ OS_Curve_TriquadraticFields::Coefficient2x_POW_2, "Coefficient2x_POW_2", "Coefficient2 x**2"},
{ OS_Curve_TriquadraticFields::Coefficient3x, "Coefficient3x", "Coefficient3 x"},
{ OS_Curve_TriquadraticFields::Coefficient4y_POW_2, "Coefficient4y_POW_2", "Coefficient4 y**2"},
{ OS_Curve_TriquadraticFields::Coefficient5y, "Coefficient5y", "Coefficient5 y"},
{ OS_Curve_TriquadraticFields::Coefficient6z_POW_2, "Coefficient6z_POW_2", "Coefficient6 z**2"},
{ OS_Curve_TriquadraticFields::Coefficient7z, "Coefficient7z", "Coefficient7 z"},
{ OS_Curve_TriquadraticFields::Coefficient8x_POW_2_TIMES_y_POW_2, "Coefficient8x_POW_2_TIMES_y_POW_2", "Coefficient8 x**2*y**2"},
{ OS_Curve_TriquadraticFields::Coefficient9x_TIMES_y, "Coefficient9x_TIMES_y", "Coefficient9 x*y"},
{ OS_Curve_TriquadraticFields::Coefficient10x_TIMES_y_POW_2, "Coefficient10x_TIMES_y_POW_2", "Coefficient10 x*y**2"},
{ OS_Curve_TriquadraticFields::Coefficient11x_POW_2_TIMES_y, "Coefficient11x_POW_2_TIMES_y", "Coefficient11 x**2*y"},
{ OS_Curve_TriquadraticFields::Coefficient12x_POW_2_TIMES_z_POW_2, "Coefficient12x_POW_2_TIMES_z_POW_2", "Coefficient12 x**2*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient13x_TIMES_z, "Coefficient13x_TIMES_z", "Coefficient13 x*z"},
{ OS_Curve_TriquadraticFields::Coefficient14x_TIMES_z_POW_2, "Coefficient14x_TIMES_z_POW_2", "Coefficient14 x*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient15x_POW_2_TIMES_z, "Coefficient15x_POW_2_TIMES_z", "Coefficient15 x**2*z"},
{ OS_Curve_TriquadraticFields::Coefficient16y_POW_2_TIMES_z_POW_2, "Coefficient16y_POW_2_TIMES_z_POW_2", "Coefficient16 y**2*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient17y_TIMES_z, "Coefficient17y_TIMES_z", "Coefficient17 y*z"},
{ OS_Curve_TriquadraticFields::Coefficient18y_TIMES_z_POW_2, "Coefficient18y_TIMES_z_POW_2", "Coefficient18 y*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient19y_POW_2_TIMES_z, "Coefficient19y_POW_2_TIMES_z", "Coefficient19 y**2*z"},
{ OS_Curve_TriquadraticFields::Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2, "Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2", "Coefficient20 x**2*y**2*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z, "Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z", "Coefficient21 x**2*y**2*z"},
{ OS_Curve_TriquadraticFields::Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2, "Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2", "Coefficient22 x**2*y*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2, "Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2", "Coefficient23 x*y**2*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient24x_POW_2_TIMES_y_TIMES_z, "Coefficient24x_POW_2_TIMES_y_TIMES_z", "Coefficient24 x**2*y*z"},
{ OS_Curve_TriquadraticFields::Coefficient25x_TIMES_y_POW_2_TIMES_z, "Coefficient25x_TIMES_y_POW_2_TIMES_z", "Coefficient25 x*y**2*z"},
{ OS_Curve_TriquadraticFields::Coefficient26x_TIMES_y_TIMES_z_POW_2, "Coefficient26x_TIMES_y_TIMES_z_POW_2", "Coefficient26 x*y*z**2"},
{ OS_Curve_TriquadraticFields::Coefficient27x_TIMES_y_TIMES_z, "Coefficient27x_TIMES_y_TIMES_z", "Coefficient27 x*y*z"},
{ OS_Curve_TriquadraticFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_TriquadraticFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_TriquadraticFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ OS_Curve_TriquadraticFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ OS_Curve_TriquadraticFields::MinimumValueofz, "MinimumValueofz", "Minimum Value of z"},
{ OS_Curve_TriquadraticFields::MaximumValueofz, "MaximumValueofz", "Maximum Value of z"},
{ OS_Curve_TriquadraticFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_TriquadraticFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_TriquadraticFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ OS_Curve_TriquadraticFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ OS_Curve_TriquadraticFields::InputUnitTypeforZ, "InputUnitTypeforZ", "Input Unit Type for Z"},
{ OS_Curve_TriquadraticFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_TriquadraticFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_TriquadraticFields> OptionalOS_Curve_TriquadraticFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_TRIQUADRATIC_FIELDENUMS_HXX
