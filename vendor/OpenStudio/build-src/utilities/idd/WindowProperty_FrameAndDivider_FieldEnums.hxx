/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowProperty_FrameAndDividerFields
 *  \brief Enumeration of WindowProperty:FrameAndDivider's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowProperty_FrameAndDividerFields, )
#else
class WindowProperty_FrameAndDividerFields: public ::EnumBase<WindowProperty_FrameAndDividerFields> {
 public: 
  enum domain 
  {
Name, FrameWidth, FrameOutsideProjection, FrameInsideProjection, FrameConductance, RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, FrameSolarAbsorptance, FrameVisibleAbsorptance, FrameThermalHemisphericalEmissivity, DividerType, DividerWidth, NumberofHorizontalDividers, NumberofVerticalDividers, DividerOutsideProjection, DividerInsideProjection, DividerConductance, RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, DividerSolarAbsorptance, DividerVisibleAbsorptance, DividerThermalHemisphericalEmissivity, OutsideRevealSolarAbsorptance, InsideSillDepth, InsideSillSolarAbsorptance, InsideRevealDepth, InsideRevealSolarAbsorptance,   };
  WindowProperty_FrameAndDividerFields()
   : EnumBase<WindowProperty_FrameAndDividerFields>(Name) {} 
  WindowProperty_FrameAndDividerFields(const std::string &t_name) 
   : EnumBase<WindowProperty_FrameAndDividerFields>(t_name) {} 
  WindowProperty_FrameAndDividerFields(int t_value) 
   : EnumBase<WindowProperty_FrameAndDividerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowProperty_FrameAndDividerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowProperty_FrameAndDividerFields>::value()); }
   private:
    friend class EnumBase<WindowProperty_FrameAndDividerFields>;
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
{ WindowProperty_FrameAndDividerFields::Name, "Name", "Name"},
{ WindowProperty_FrameAndDividerFields::FrameWidth, "FrameWidth", "Frame Width"},
{ WindowProperty_FrameAndDividerFields::FrameOutsideProjection, "FrameOutsideProjection", "Frame Outside Projection"},
{ WindowProperty_FrameAndDividerFields::FrameInsideProjection, "FrameInsideProjection", "Frame Inside Projection"},
{ WindowProperty_FrameAndDividerFields::FrameConductance, "FrameConductance", "Frame Conductance"},
{ WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, "RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance", "Ratio of Frame-Edge Glass Conductance to Center-Of-Glass Conductance"},
{ WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance, "FrameSolarAbsorptance", "Frame Solar Absorptance"},
{ WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance, "FrameVisibleAbsorptance", "Frame Visible Absorptance"},
{ WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity, "FrameThermalHemisphericalEmissivity", "Frame Thermal Hemispherical Emissivity"},
{ WindowProperty_FrameAndDividerFields::DividerType, "DividerType", "Divider Type"},
{ WindowProperty_FrameAndDividerFields::DividerWidth, "DividerWidth", "Divider Width"},
{ WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers, "NumberofHorizontalDividers", "Number of Horizontal Dividers"},
{ WindowProperty_FrameAndDividerFields::NumberofVerticalDividers, "NumberofVerticalDividers", "Number of Vertical Dividers"},
{ WindowProperty_FrameAndDividerFields::DividerOutsideProjection, "DividerOutsideProjection", "Divider Outside Projection"},
{ WindowProperty_FrameAndDividerFields::DividerInsideProjection, "DividerInsideProjection", "Divider Inside Projection"},
{ WindowProperty_FrameAndDividerFields::DividerConductance, "DividerConductance", "Divider Conductance"},
{ WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, "RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance", "Ratio of Divider-Edge Glass Conductance to Center-Of-Glass Conductance"},
{ WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance, "DividerSolarAbsorptance", "Divider Solar Absorptance"},
{ WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance, "DividerVisibleAbsorptance", "Divider Visible Absorptance"},
{ WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity, "DividerThermalHemisphericalEmissivity", "Divider Thermal Hemispherical Emissivity"},
{ WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance, "OutsideRevealSolarAbsorptance", "Outside Reveal Solar Absorptance"},
{ WindowProperty_FrameAndDividerFields::InsideSillDepth, "InsideSillDepth", "Inside Sill Depth"},
{ WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance, "InsideSillSolarAbsorptance", "Inside Sill Solar Absorptance"},
{ WindowProperty_FrameAndDividerFields::InsideRevealDepth, "InsideRevealDepth", "Inside Reveal Depth"},
{ WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance, "InsideRevealSolarAbsorptance", "Inside Reveal Solar Absorptance"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowProperty_FrameAndDividerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowProperty_FrameAndDividerFields> OptionalWindowProperty_FrameAndDividerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX