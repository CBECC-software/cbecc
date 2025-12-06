/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_DESIGNSPECIFICATION_OUTDOORAIR_SPACELIST_FIELDENUMS_HXX
#define UTILITIES_IDD_DESIGNSPECIFICATION_OUTDOORAIR_SPACELIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DesignSpecification_OutdoorAir_SpaceListFields
 *  \brief Enumeration of DesignSpecification:OutdoorAir:SpaceList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DesignSpecification_OutdoorAir_SpaceListFields, )
#else
class DesignSpecification_OutdoorAir_SpaceListFields: public ::EnumBase<DesignSpecification_OutdoorAir_SpaceListFields> {
 public: 
  enum domain 
  {
Name,   };
  DesignSpecification_OutdoorAir_SpaceListFields()
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListFields>(Name) {} 
  DesignSpecification_OutdoorAir_SpaceListFields(const std::string &t_name) 
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListFields>(t_name) {} 
  DesignSpecification_OutdoorAir_SpaceListFields(int t_value) 
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListFields>(t_value) {} 
  static std::string enumName() 
  { return "DesignSpecification_OutdoorAir_SpaceListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DesignSpecification_OutdoorAir_SpaceListFields>::integer_value()); }
   private:
    friend class EnumBase<DesignSpecification_OutdoorAir_SpaceListFields>;
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
{ DesignSpecification_OutdoorAir_SpaceListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DesignSpecification_OutdoorAir_SpaceListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DesignSpecification_OutdoorAir_SpaceListFields> OptionalDesignSpecification_OutdoorAir_SpaceListFields ;
#endif

/** \class DesignSpecification_OutdoorAir_SpaceListExtensibleFields
 *  \brief Enumeration of DesignSpecification:OutdoorAir:SpaceList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DesignSpecification_OutdoorAir_SpaceListExtensibleFields, )
#else
class DesignSpecification_OutdoorAir_SpaceListExtensibleFields: public ::EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields> {
 public: 
  enum domain 
  {
SpaceName, SpaceDesignSpecificationOutdoorAirObjectName,   };
  DesignSpecification_OutdoorAir_SpaceListExtensibleFields()
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields>(SpaceName) {} 
  DesignSpecification_OutdoorAir_SpaceListExtensibleFields(const std::string &t_name) 
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields>(t_name) {} 
  DesignSpecification_OutdoorAir_SpaceListExtensibleFields(int t_value) 
   : EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DesignSpecification_OutdoorAir_SpaceListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<DesignSpecification_OutdoorAir_SpaceListExtensibleFields>;
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
{ DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, "SpaceName", "Space Name"},
{ DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, "SpaceDesignSpecificationOutdoorAirObjectName", "Space Design Specification Outdoor Air Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DesignSpecification_OutdoorAir_SpaceListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DesignSpecification_OutdoorAir_SpaceListExtensibleFields> OptionalDesignSpecification_OutdoorAir_SpaceListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DESIGNSPECIFICATION_OUTDOORAIR_SPACELIST_FIELDENUMS_HXX
