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

#ifndef UTILITIES_IDD_OS_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowProperty_FrameAndDividerFields
 *  \brief Enumeration of OS:WindowProperty:FrameAndDivider's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowProperty_FrameAndDividerFields, )
#else
class OS_WindowProperty_FrameAndDividerFields: public ::EnumBase<OS_WindowProperty_FrameAndDividerFields> {
 public: 
  enum domain 
  {
Handle, Name, FrameWidth, FrameOutsideProjection, FrameInsideProjection, FrameConductance, RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, FrameSolarAbsorptance, FrameVisibleAbsorptance, FrameThermalHemisphericalEmissivity, DividerType, DividerWidth, NumberofHorizontalDividers, NumberofVerticalDividers, DividerOutsideProjection, DividerInsideProjection, DividerConductance, RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, DividerSolarAbsorptance, DividerVisibleAbsorptance, DividerThermalHemisphericalEmissivity, OutsideRevealDepth, OutsideRevealSolarAbsorptance, InsideSillDepth, InsideSillSolarAbsorptance, InsideRevealDepth, InsideRevealSolarAbsorptance,   };
  OS_WindowProperty_FrameAndDividerFields()
   : EnumBase<OS_WindowProperty_FrameAndDividerFields>(Handle) {} 
  OS_WindowProperty_FrameAndDividerFields(const std::string &t_name) 
   : EnumBase<OS_WindowProperty_FrameAndDividerFields>(t_name) {} 
  OS_WindowProperty_FrameAndDividerFields(int t_value) 
   : EnumBase<OS_WindowProperty_FrameAndDividerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowProperty_FrameAndDividerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowProperty_FrameAndDividerFields>::value()); }
   private:
    friend class EnumBase<OS_WindowProperty_FrameAndDividerFields>;
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
{ OS_WindowProperty_FrameAndDividerFields::Handle, "Handle", "Handle"},
{ OS_WindowProperty_FrameAndDividerFields::Name, "Name", "Name"},
{ OS_WindowProperty_FrameAndDividerFields::FrameWidth, "FrameWidth", "Frame Width"},
{ OS_WindowProperty_FrameAndDividerFields::FrameOutsideProjection, "FrameOutsideProjection", "Frame Outside Projection"},
{ OS_WindowProperty_FrameAndDividerFields::FrameInsideProjection, "FrameInsideProjection", "Frame Inside Projection"},
{ OS_WindowProperty_FrameAndDividerFields::FrameConductance, "FrameConductance", "Frame Conductance"},
{ OS_WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, "RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance", "Ratio of Frame-Edge Glass Conductance to Center-Of-Glass Conductance"},
{ OS_WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance, "FrameSolarAbsorptance", "Frame Solar Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance, "FrameVisibleAbsorptance", "Frame Visible Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity, "FrameThermalHemisphericalEmissivity", "Frame Thermal Hemispherical Emissivity"},
{ OS_WindowProperty_FrameAndDividerFields::DividerType, "DividerType", "Divider Type"},
{ OS_WindowProperty_FrameAndDividerFields::DividerWidth, "DividerWidth", "Divider Width"},
{ OS_WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers, "NumberofHorizontalDividers", "Number of Horizontal Dividers"},
{ OS_WindowProperty_FrameAndDividerFields::NumberofVerticalDividers, "NumberofVerticalDividers", "Number of Vertical Dividers"},
{ OS_WindowProperty_FrameAndDividerFields::DividerOutsideProjection, "DividerOutsideProjection", "Divider Outside Projection"},
{ OS_WindowProperty_FrameAndDividerFields::DividerInsideProjection, "DividerInsideProjection", "Divider Inside Projection"},
{ OS_WindowProperty_FrameAndDividerFields::DividerConductance, "DividerConductance", "Divider Conductance"},
{ OS_WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, "RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance", "Ratio of Divider-Edge Glass Conductance to Center-Of-Glass Conductance"},
{ OS_WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance, "DividerSolarAbsorptance", "Divider Solar Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance, "DividerVisibleAbsorptance", "Divider Visible Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity, "DividerThermalHemisphericalEmissivity", "Divider Thermal Hemispherical Emissivity"},
{ OS_WindowProperty_FrameAndDividerFields::OutsideRevealDepth, "OutsideRevealDepth", "Outside Reveal Depth"},
{ OS_WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance, "OutsideRevealSolarAbsorptance", "Outside Reveal Solar Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::InsideSillDepth, "InsideSillDepth", "Inside Sill Depth"},
{ OS_WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance, "InsideSillSolarAbsorptance", "Inside Sill Solar Absorptance"},
{ OS_WindowProperty_FrameAndDividerFields::InsideRevealDepth, "InsideRevealDepth", "Inside Reveal Depth"},
{ OS_WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance, "InsideRevealSolarAbsorptance", "Inside Reveal Solar Absorptance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowProperty_FrameAndDividerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowProperty_FrameAndDividerFields> OptionalOS_WindowProperty_FrameAndDividerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWPROPERTY_FRAMEANDDIVIDER_FIELDENUMS_HXX
