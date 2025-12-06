/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
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
Name, InitialIndoorAirTemperature, InteriorHorizontalInsulationMaterialName, InteriorHorizontalInsulationDepth, InteriorHorizontalInsulationWidth, InteriorVerticalInsulationMaterialName, InteriorVerticalInsulationDepth, ExteriorHorizontalInsulationMaterialName, ExteriorHorizontalInsulationDepth, ExteriorHorizontalInsulationWidth, ExteriorVerticalInsulationMaterialName, ExteriorVerticalInsulationDepth, WallHeightAboveGrade, WallDepthBelowSlab, FootingWallConstructionName, FootingMaterialName, FootingDepth,   };
  Foundation_KivaFields()
   : EnumBase<Foundation_KivaFields>(Name) {} 
  Foundation_KivaFields(const std::string &t_name) 
   : EnumBase<Foundation_KivaFields>(t_name) {} 
  Foundation_KivaFields(int t_value) 
   : EnumBase<Foundation_KivaFields>(t_value) {} 
  static std::string enumName() 
  { return "Foundation_KivaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Foundation_KivaFields>::integer_value()); }
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
{ Foundation_KivaFields::InitialIndoorAirTemperature, "InitialIndoorAirTemperature", "Initial Indoor Air Temperature"},
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
  domain value() const { return static_cast<domain>(EnumBase<Foundation_KivaExtensibleFields>::integer_value()); }
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
