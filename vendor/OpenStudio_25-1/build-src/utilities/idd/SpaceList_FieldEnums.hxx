/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SPACELIST_FIELDENUMS_HXX
#define UTILITIES_IDD_SPACELIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SpaceListFields
 *  \brief Enumeration of SpaceList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SpaceListFields, )
#else
class SpaceListFields: public ::EnumBase<SpaceListFields> {
 public: 
  enum domain 
  {
Name,   };
  SpaceListFields()
   : EnumBase<SpaceListFields>(Name) {} 
  SpaceListFields(const std::string &t_name) 
   : EnumBase<SpaceListFields>(t_name) {} 
  SpaceListFields(int t_value) 
   : EnumBase<SpaceListFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceListFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceListFields>;
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
{ SpaceListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceListFields> OptionalSpaceListFields ;
#endif

/** \class SpaceListExtensibleFields
 *  \brief Enumeration of SpaceList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SpaceListExtensibleFields, )
#else
class SpaceListExtensibleFields: public ::EnumBase<SpaceListExtensibleFields> {
 public: 
  enum domain 
  {
SpaceName,   };
  SpaceListExtensibleFields()
   : EnumBase<SpaceListExtensibleFields>(SpaceName) {} 
  SpaceListExtensibleFields(const std::string &t_name) 
   : EnumBase<SpaceListExtensibleFields>(t_name) {} 
  SpaceListExtensibleFields(int t_value) 
   : EnumBase<SpaceListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceListExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceListExtensibleFields>;
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
{ SpaceListExtensibleFields::SpaceName, "SpaceName", "Space Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceListExtensibleFields> OptionalSpaceListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SPACELIST_FIELDENUMS_HXX
