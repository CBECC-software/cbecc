/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
