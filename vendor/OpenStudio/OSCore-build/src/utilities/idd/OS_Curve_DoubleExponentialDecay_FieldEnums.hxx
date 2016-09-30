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

#ifndef UTILITIES_IDD_OS_CURVE_DOUBLEEXPONENTIALDECAY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_DOUBLEEXPONENTIALDECAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_DoubleExponentialDecayFields
 *  \brief Enumeration of OS:Curve:DoubleExponentialDecay's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_DoubleExponentialDecayFields, )
#else
class OS_Curve_DoubleExponentialDecayFields: public ::EnumBase<OS_Curve_DoubleExponentialDecayFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1C1, Coefficient2C2, Coefficient3C3, Coefficient3C4, Coefficient3C5, MinimumValueofx, MaximumValueofx, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforx, OutputUnitType,   };
  OS_Curve_DoubleExponentialDecayFields()
   : EnumBase<OS_Curve_DoubleExponentialDecayFields>(Handle) {} 
  OS_Curve_DoubleExponentialDecayFields(const std::string &t_name) 
   : EnumBase<OS_Curve_DoubleExponentialDecayFields>(t_name) {} 
  OS_Curve_DoubleExponentialDecayFields(int t_value) 
   : EnumBase<OS_Curve_DoubleExponentialDecayFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_DoubleExponentialDecayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_DoubleExponentialDecayFields>::value()); }
   private:
    friend class EnumBase<OS_Curve_DoubleExponentialDecayFields>;
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
{ OS_Curve_DoubleExponentialDecayFields::Handle, "Handle", "Handle"},
{ OS_Curve_DoubleExponentialDecayFields::Name, "Name", "Name"},
{ OS_Curve_DoubleExponentialDecayFields::Coefficient1C1, "Coefficient1C1", "Coefficient1 C1"},
{ OS_Curve_DoubleExponentialDecayFields::Coefficient2C2, "Coefficient2C2", "Coefficient2 C2"},
{ OS_Curve_DoubleExponentialDecayFields::Coefficient3C3, "Coefficient3C3", "Coefficient3 C3"},
{ OS_Curve_DoubleExponentialDecayFields::Coefficient3C4, "Coefficient3C4", "Coefficient3 C4"},
{ OS_Curve_DoubleExponentialDecayFields::Coefficient3C5, "Coefficient3C5", "Coefficient3 C5"},
{ OS_Curve_DoubleExponentialDecayFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_DoubleExponentialDecayFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_DoubleExponentialDecayFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_DoubleExponentialDecayFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_DoubleExponentialDecayFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ OS_Curve_DoubleExponentialDecayFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_DoubleExponentialDecayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_DoubleExponentialDecayFields> OptionalOS_Curve_DoubleExponentialDecayFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_DOUBLEEXPONENTIALDECAY_FIELDENUMS_HXX
