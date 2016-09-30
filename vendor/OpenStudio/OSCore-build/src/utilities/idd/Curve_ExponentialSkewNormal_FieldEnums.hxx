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

#ifndef UTILITIES_IDD_CURVE_EXPONENTIALSKEWNORMAL_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_EXPONENTIALSKEWNORMAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_ExponentialSkewNormalFields
 *  \brief Enumeration of Curve:ExponentialSkewNormal's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_ExponentialSkewNormalFields, )
#else
class Curve_ExponentialSkewNormalFields: public ::EnumBase<Curve_ExponentialSkewNormalFields> {
 public: 
  enum domain 
  {
Name, Coefficient1C1, Coefficient2C2, Coefficient3C3, Coefficient4C4, MinimumValueofx, MaximumValueofx, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforx, OutputUnitType,   };
  Curve_ExponentialSkewNormalFields()
   : EnumBase<Curve_ExponentialSkewNormalFields>(Name) {} 
  Curve_ExponentialSkewNormalFields(const std::string &t_name) 
   : EnumBase<Curve_ExponentialSkewNormalFields>(t_name) {} 
  Curve_ExponentialSkewNormalFields(int t_value) 
   : EnumBase<Curve_ExponentialSkewNormalFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_ExponentialSkewNormalFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_ExponentialSkewNormalFields>::value()); }
   private:
    friend class EnumBase<Curve_ExponentialSkewNormalFields>;
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
{ Curve_ExponentialSkewNormalFields::Name, "Name", "Name"},
{ Curve_ExponentialSkewNormalFields::Coefficient1C1, "Coefficient1C1", "Coefficient1 C1"},
{ Curve_ExponentialSkewNormalFields::Coefficient2C2, "Coefficient2C2", "Coefficient2 C2"},
{ Curve_ExponentialSkewNormalFields::Coefficient3C3, "Coefficient3C3", "Coefficient3 C3"},
{ Curve_ExponentialSkewNormalFields::Coefficient4C4, "Coefficient4C4", "Coefficient4 C4"},
{ Curve_ExponentialSkewNormalFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_ExponentialSkewNormalFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_ExponentialSkewNormalFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_ExponentialSkewNormalFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_ExponentialSkewNormalFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ Curve_ExponentialSkewNormalFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_ExponentialSkewNormalFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_ExponentialSkewNormalFields> OptionalCurve_ExponentialSkewNormalFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_EXPONENTIALSKEWNORMAL_FIELDENUMS_HXX
