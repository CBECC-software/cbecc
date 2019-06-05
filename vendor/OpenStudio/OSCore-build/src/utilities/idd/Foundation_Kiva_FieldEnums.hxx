/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_FOUNDATION_KIVA_FIELDENUMS_HXX
#define UTILITIES_IDD_FOUNDATION_KIVA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Foundation_KivaFields
 *  \brief Enumeration of Foundation:Kiva's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Foundation_KivaFields, )
#else
class Foundation_KivaFields: public ::EnumBase<Foundation_KivaFields> {
 public: 
  enum domain 
  {
Name, InteriorHorizontalInsulationMaterialName, InteriorHorizontalInsulationDepth, InteriorHorizontalInsulationWidth, InteriorVerticalInsulationMaterialName, InteriorVerticalInsulationDepth, ExteriorHorizontalInsulationMaterialName, ExteriorHorizontalInsulationDepth, ExteriorHorizontalInsulationWidth, ExteriorVerticalInsulationMaterialName, ExteriorVerticalInsulationDepth, WallHeightAboveGrade, WallDepthBelowSlab, FootingWallConstructionName, FootingMaterialName, FootingDepth,   };
  Foundation_KivaFields()
   : EnumBase<Foundation_KivaFields>(Name) {} 
  Foundation_KivaFields(const std::string &t_name) 
   : EnumBase<Foundation_KivaFields>(t_name) {} 
  Foundation_KivaFields(int t_value) 
   : EnumBase<Foundation_KivaFields>(t_value) {} 
  static std::string enumName() 
  { return "Foundation_KivaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Foundation_KivaFields>::value()); }
   private:
    friend class EnumBase<Foundation_KivaFields>;
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
{ Foundation_KivaFields::Name, "Name", "Name"},
{ Foundation_KivaFields::InteriorHorizontalInsulationMaterialName, "InteriorHorizontalInsulationMaterialName", "Interior Horizontal Insulation Material Name"},
{ Foundation_KivaFields::InteriorHorizontalInsulationDepth, "InteriorHorizontalInsulationDepth", "Interior Horizontal Insulation Depth"},
{ Foundation_KivaFields::InteriorHorizontalInsulationWidth, "InteriorHorizontalInsulationWidth", "Interior Horizontal Insulation Width"},
{ Foundation_KivaFields::InteriorVerticalInsulationMaterialName, "InteriorVerticalInsulationMaterialName", "Interior Vertical Insulation Material Name"},
{ Foundation_KivaFields::InteriorVerticalInsulationDepth, "InteriorVerticalInsulationDepth", "Interior Vertical Insulation Depth"},
{ Foundation_KivaFields::ExteriorHorizontalInsulationMaterialName, "ExteriorHorizontalInsulationMaterialName", "Exterior Horizontal Insulation Material Name"},
{ Foundation_KivaFields::ExteriorHorizontalInsulationDepth, "ExteriorHorizontalInsulationDepth", "Exterior Horizontal Insulation Depth"},
{ Foundation_KivaFields::ExteriorHorizontalInsulationWidth, "ExteriorHorizontalInsulationWidth", "Exterior Horizontal Insulation Width"},
{ Foundation_KivaFields::ExteriorVerticalInsulationMaterialName, "ExteriorVerticalInsulationMaterialName", "Exterior Vertical Insulation Material Name"},
{ Foundation_KivaFields::ExteriorVerticalInsulationDepth, "ExteriorVerticalInsulationDepth", "Exterior Vertical Insulation Depth"},
{ Foundation_KivaFields::WallHeightAboveGrade, "WallHeightAboveGrade", "Wall Height Above Grade"},
{ Foundation_KivaFields::WallDepthBelowSlab, "WallDepthBelowSlab", "Wall Depth Below Slab"},
{ Foundation_KivaFields::FootingWallConstructionName, "FootingWallConstructionName", "Footing Wall Construction Name"},
{ Foundation_KivaFields::FootingMaterialName, "FootingMaterialName", "Footing Material Name"},
{ Foundation_KivaFields::FootingDepth, "FootingDepth", "Footing Depth"},
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
  inline std::ostream &operator<<(std::ostream &os, const Foundation_KivaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Foundation_KivaFields> OptionalFoundation_KivaFields ;
#endif

/** \class Foundation_KivaExtensibleFields
 *  \brief Enumeration of Foundation:Kiva's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Foundation_KivaExtensibleFields, )
#else
class Foundation_KivaExtensibleFields: public ::EnumBase<Foundation_KivaExtensibleFields> {
 public: 
  enum domain 
  {
CustomBlockMaterialName, CustomBlockDepth, CustomBlockXPosition, CustomBlockZPosition,   };
  Foundation_KivaExtensibleFields()
   : EnumBase<Foundation_KivaExtensibleFields>(CustomBlockMaterialName) {} 
  Foundation_KivaExtensibleFields(const std::string &t_name) 
   : EnumBase<Foundation_KivaExtensibleFields>(t_name) {} 
  Foundation_KivaExtensibleFields(int t_value) 
   : EnumBase<Foundation_KivaExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Foundation_KivaExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Foundation_KivaExtensibleFields>::value()); }
   private:
    friend class EnumBase<Foundation_KivaExtensibleFields>;
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
{ Foundation_KivaExtensibleFields::CustomBlockMaterialName, "CustomBlockMaterialName", "Custom Block Material Name"},
{ Foundation_KivaExtensibleFields::CustomBlockDepth, "CustomBlockDepth", "Custom Block Depth"},
{ Foundation_KivaExtensibleFields::CustomBlockXPosition, "CustomBlockXPosition", "Custom Block X Position"},
{ Foundation_KivaExtensibleFields::CustomBlockZPosition, "CustomBlockZPosition", "Custom Block Z Position"},
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
  inline std::ostream &operator<<(std::ostream &os, const Foundation_KivaExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Foundation_KivaExtensibleFields> OptionalFoundation_KivaExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FOUNDATION_KIVA_FIELDENUMS_HXX
