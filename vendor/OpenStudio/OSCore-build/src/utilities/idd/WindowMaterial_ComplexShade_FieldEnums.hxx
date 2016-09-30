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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_COMPLEXSHADE_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_COMPLEXSHADE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_ComplexShadeFields
 *  \brief Enumeration of WindowMaterial:ComplexShade's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_ComplexShadeFields, )
#else
class WindowMaterial_ComplexShadeFields: public ::EnumBase<WindowMaterial_ComplexShadeFields> {
 public: 
  enum domain 
  {
Name, LayerType, Thickness, Conductivity, IRTransmittance, FrontEmissivity, BackEmissivity, TopOpeningMultiplier, BottomOpeningMultiplier, LeftSideOpeningMultiplier, RightSideOpeningMultiplier, FrontOpeningMultiplier, SlatWidth, SlatSpacing, SlatThickness, SlatAngle, SlatConductivity, SlatCurve,   };
  WindowMaterial_ComplexShadeFields()
   : EnumBase<WindowMaterial_ComplexShadeFields>(Name) {} 
  WindowMaterial_ComplexShadeFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_ComplexShadeFields>(t_name) {} 
  WindowMaterial_ComplexShadeFields(int t_value) 
   : EnumBase<WindowMaterial_ComplexShadeFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_ComplexShadeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_ComplexShadeFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_ComplexShadeFields>;
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
{ WindowMaterial_ComplexShadeFields::Name, "Name", "Name"},
{ WindowMaterial_ComplexShadeFields::LayerType, "LayerType", "Layer Type"},
{ WindowMaterial_ComplexShadeFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_ComplexShadeFields::Conductivity, "Conductivity", "Conductivity"},
{ WindowMaterial_ComplexShadeFields::IRTransmittance, "IRTransmittance", "IR Transmittance"},
{ WindowMaterial_ComplexShadeFields::FrontEmissivity, "FrontEmissivity", "Front Emissivity"},
{ WindowMaterial_ComplexShadeFields::BackEmissivity, "BackEmissivity", "Back Emissivity"},
{ WindowMaterial_ComplexShadeFields::TopOpeningMultiplier, "TopOpeningMultiplier", "Top Opening Multiplier"},
{ WindowMaterial_ComplexShadeFields::BottomOpeningMultiplier, "BottomOpeningMultiplier", "Bottom Opening Multiplier"},
{ WindowMaterial_ComplexShadeFields::LeftSideOpeningMultiplier, "LeftSideOpeningMultiplier", "Left Side Opening Multiplier"},
{ WindowMaterial_ComplexShadeFields::RightSideOpeningMultiplier, "RightSideOpeningMultiplier", "Right Side Opening Multiplier"},
{ WindowMaterial_ComplexShadeFields::FrontOpeningMultiplier, "FrontOpeningMultiplier", "Front Opening Multiplier"},
{ WindowMaterial_ComplexShadeFields::SlatWidth, "SlatWidth", "Slat Width"},
{ WindowMaterial_ComplexShadeFields::SlatSpacing, "SlatSpacing", "Slat Spacing"},
{ WindowMaterial_ComplexShadeFields::SlatThickness, "SlatThickness", "Slat Thickness"},
{ WindowMaterial_ComplexShadeFields::SlatAngle, "SlatAngle", "Slat Angle"},
{ WindowMaterial_ComplexShadeFields::SlatConductivity, "SlatConductivity", "Slat Conductivity"},
{ WindowMaterial_ComplexShadeFields::SlatCurve, "SlatCurve", "Slat Curve"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_ComplexShadeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_ComplexShadeFields> OptionalWindowMaterial_ComplexShadeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_COMPLEXSHADE_FIELDENUMS_HXX
