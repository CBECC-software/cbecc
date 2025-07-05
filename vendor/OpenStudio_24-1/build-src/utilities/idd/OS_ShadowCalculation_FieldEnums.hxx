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

#ifndef UTILITIES_IDD_OS_SHADOWCALCULATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SHADOWCALCULATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ShadowCalculationFields
 *  \brief Enumeration of OS:ShadowCalculation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadowCalculationFields, )
#else
class OS_ShadowCalculationFields: public ::EnumBase<OS_ShadowCalculationFields> {
 public: 
  enum domain 
  {
Handle, ShadingCalculationMethod, ShadingCalculationUpdateFrequencyMethod, ShadingCalculationUpdateFrequency, MaximumFiguresinShadowOverlapCalculations, PolygonClippingAlgorithm, PixelCountingResolution, SkyDiffuseModelingAlgorithm, OutputExternalShadingCalculationResults, DisableSelfShadingWithinShadingZoneGroups, DisableSelfShadingFromShadingZoneGroupstoOtherZones,   };
  OS_ShadowCalculationFields()
   : EnumBase<OS_ShadowCalculationFields>(Handle) {} 
  OS_ShadowCalculationFields(const std::string &t_name) 
   : EnumBase<OS_ShadowCalculationFields>(t_name) {} 
  OS_ShadowCalculationFields(int t_value) 
   : EnumBase<OS_ShadowCalculationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadowCalculationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadowCalculationFields>::value()); }
   private:
    friend class EnumBase<OS_ShadowCalculationFields>;
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
{ OS_ShadowCalculationFields::Handle, "Handle", "Handle"},
{ OS_ShadowCalculationFields::ShadingCalculationMethod, "ShadingCalculationMethod", "Shading Calculation Method"},
{ OS_ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod, "ShadingCalculationUpdateFrequencyMethod", "Shading Calculation Update Frequency Method"},
{ OS_ShadowCalculationFields::ShadingCalculationUpdateFrequency, "ShadingCalculationUpdateFrequency", "Shading Calculation Update Frequency"},
{ OS_ShadowCalculationFields::MaximumFiguresinShadowOverlapCalculations, "MaximumFiguresinShadowOverlapCalculations", "Maximum Figures in Shadow Overlap Calculations"},
{ OS_ShadowCalculationFields::PolygonClippingAlgorithm, "PolygonClippingAlgorithm", "Polygon Clipping Algorithm"},
{ OS_ShadowCalculationFields::PixelCountingResolution, "PixelCountingResolution", "Pixel Counting Resolution"},
{ OS_ShadowCalculationFields::SkyDiffuseModelingAlgorithm, "SkyDiffuseModelingAlgorithm", "Sky Diffuse Modeling Algorithm"},
{ OS_ShadowCalculationFields::OutputExternalShadingCalculationResults, "OutputExternalShadingCalculationResults", "Output External Shading Calculation Results"},
{ OS_ShadowCalculationFields::DisableSelfShadingWithinShadingZoneGroups, "DisableSelfShadingWithinShadingZoneGroups", "Disable Self-Shading Within Shading Zone Groups"},
{ OS_ShadowCalculationFields::DisableSelfShadingFromShadingZoneGroupstoOtherZones, "DisableSelfShadingFromShadingZoneGroupstoOtherZones", "Disable Self-Shading From Shading Zone Groups to Other Zones"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadowCalculationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadowCalculationFields> OptionalOS_ShadowCalculationFields ;
#endif

/** \class OS_ShadowCalculationExtensibleFields
 *  \brief Enumeration of OS:ShadowCalculation's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadowCalculationExtensibleFields, )
#else
class OS_ShadowCalculationExtensibleFields: public ::EnumBase<OS_ShadowCalculationExtensibleFields> {
 public: 
  enum domain 
  {
ShadingZoneGroup,   };
  OS_ShadowCalculationExtensibleFields()
   : EnumBase<OS_ShadowCalculationExtensibleFields>(ShadingZoneGroup) {} 
  OS_ShadowCalculationExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ShadowCalculationExtensibleFields>(t_name) {} 
  OS_ShadowCalculationExtensibleFields(int t_value) 
   : EnumBase<OS_ShadowCalculationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadowCalculationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadowCalculationExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ShadowCalculationExtensibleFields>;
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
{ OS_ShadowCalculationExtensibleFields::ShadingZoneGroup, "ShadingZoneGroup", "Shading Zone Group"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadowCalculationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadowCalculationExtensibleFields> OptionalOS_ShadowCalculationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SHADOWCALCULATION_FIELDENUMS_HXX
