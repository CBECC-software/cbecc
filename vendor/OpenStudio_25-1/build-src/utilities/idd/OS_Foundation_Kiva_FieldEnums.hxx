/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_FOUNDATION_KIVA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FOUNDATION_KIVA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Foundation_KivaFields
 *  \brief Enumeration of OS:Foundation:Kiva's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Foundation_KivaFields, )
#else
class OS_Foundation_KivaFields: public ::EnumBase<OS_Foundation_KivaFields> {
 public: 
  enum domain 
  {
Handle, Name, InitialIndoorAirTemperature, InteriorHorizontalInsulationMaterialName, InteriorHorizontalInsulationDepth, InteriorHorizontalInsulationWidth, InteriorVerticalInsulationMaterialName, InteriorVerticalInsulationDepth, ExteriorHorizontalInsulationMaterialName, ExteriorHorizontalInsulationDepth, ExteriorHorizontalInsulationWidth, ExteriorVerticalInsulationMaterialName, ExteriorVerticalInsulationDepth, WallHeightAboveGrade, WallDepthBelowSlab, FootingWallConstructionName, FootingMaterialName, FootingDepth,   };
  OS_Foundation_KivaFields()
   : EnumBase<OS_Foundation_KivaFields>(Handle) {} 
  OS_Foundation_KivaFields(const std::string &t_name) 
   : EnumBase<OS_Foundation_KivaFields>(t_name) {} 
  OS_Foundation_KivaFields(int t_value) 
   : EnumBase<OS_Foundation_KivaFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Foundation_KivaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Foundation_KivaFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Foundation_KivaFields>;
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
{ OS_Foundation_KivaFields::Handle, "Handle", "Handle"},
{ OS_Foundation_KivaFields::Name, "Name", "Name"},
{ OS_Foundation_KivaFields::InitialIndoorAirTemperature, "InitialIndoorAirTemperature", "Initial Indoor Air Temperature"},
{ OS_Foundation_KivaFields::InteriorHorizontalInsulationMaterialName, "InteriorHorizontalInsulationMaterialName", "Interior Horizontal Insulation Material Name"},
{ OS_Foundation_KivaFields::InteriorHorizontalInsulationDepth, "InteriorHorizontalInsulationDepth", "Interior Horizontal Insulation Depth"},
{ OS_Foundation_KivaFields::InteriorHorizontalInsulationWidth, "InteriorHorizontalInsulationWidth", "Interior Horizontal Insulation Width"},
{ OS_Foundation_KivaFields::InteriorVerticalInsulationMaterialName, "InteriorVerticalInsulationMaterialName", "Interior Vertical Insulation Material Name"},
{ OS_Foundation_KivaFields::InteriorVerticalInsulationDepth, "InteriorVerticalInsulationDepth", "Interior Vertical Insulation Depth"},
{ OS_Foundation_KivaFields::ExteriorHorizontalInsulationMaterialName, "ExteriorHorizontalInsulationMaterialName", "Exterior Horizontal Insulation Material Name"},
{ OS_Foundation_KivaFields::ExteriorHorizontalInsulationDepth, "ExteriorHorizontalInsulationDepth", "Exterior Horizontal Insulation Depth"},
{ OS_Foundation_KivaFields::ExteriorHorizontalInsulationWidth, "ExteriorHorizontalInsulationWidth", "Exterior Horizontal Insulation Width"},
{ OS_Foundation_KivaFields::ExteriorVerticalInsulationMaterialName, "ExteriorVerticalInsulationMaterialName", "Exterior Vertical Insulation Material Name"},
{ OS_Foundation_KivaFields::ExteriorVerticalInsulationDepth, "ExteriorVerticalInsulationDepth", "Exterior Vertical Insulation Depth"},
{ OS_Foundation_KivaFields::WallHeightAboveGrade, "WallHeightAboveGrade", "Wall Height Above Grade"},
{ OS_Foundation_KivaFields::WallDepthBelowSlab, "WallDepthBelowSlab", "Wall Depth Below Slab"},
{ OS_Foundation_KivaFields::FootingWallConstructionName, "FootingWallConstructionName", "Footing Wall Construction Name"},
{ OS_Foundation_KivaFields::FootingMaterialName, "FootingMaterialName", "Footing Material Name"},
{ OS_Foundation_KivaFields::FootingDepth, "FootingDepth", "Footing Depth"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Foundation_KivaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Foundation_KivaFields> OptionalOS_Foundation_KivaFields ;
#endif

/** \class OS_Foundation_KivaExtensibleFields
 *  \brief Enumeration of OS:Foundation:Kiva's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Foundation_KivaExtensibleFields, )
#else
class OS_Foundation_KivaExtensibleFields: public ::EnumBase<OS_Foundation_KivaExtensibleFields> {
 public: 
  enum domain 
  {
CustomBlockMaterialName, CustomBlockDepth, CustomBlockXPosition, CustomBlockZPosition,   };
  OS_Foundation_KivaExtensibleFields()
   : EnumBase<OS_Foundation_KivaExtensibleFields>(CustomBlockMaterialName) {} 
  OS_Foundation_KivaExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Foundation_KivaExtensibleFields>(t_name) {} 
  OS_Foundation_KivaExtensibleFields(int t_value) 
   : EnumBase<OS_Foundation_KivaExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Foundation_KivaExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Foundation_KivaExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Foundation_KivaExtensibleFields>;
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
{ OS_Foundation_KivaExtensibleFields::CustomBlockMaterialName, "CustomBlockMaterialName", "Custom Block Material Name"},
{ OS_Foundation_KivaExtensibleFields::CustomBlockDepth, "CustomBlockDepth", "Custom Block Depth"},
{ OS_Foundation_KivaExtensibleFields::CustomBlockXPosition, "CustomBlockXPosition", "Custom Block X Position"},
{ OS_Foundation_KivaExtensibleFields::CustomBlockZPosition, "CustomBlockZPosition", "Custom Block Z Position"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Foundation_KivaExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Foundation_KivaExtensibleFields> OptionalOS_Foundation_KivaExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FOUNDATION_KIVA_FIELDENUMS_HXX
