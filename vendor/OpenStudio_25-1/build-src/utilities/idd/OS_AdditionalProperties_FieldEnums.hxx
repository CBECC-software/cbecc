/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ADDITIONALPROPERTIES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ADDITIONALPROPERTIES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AdditionalPropertiesFields
 *  \brief Enumeration of OS:AdditionalProperties's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AdditionalPropertiesFields, )
#else
class OS_AdditionalPropertiesFields: public ::EnumBase<OS_AdditionalPropertiesFields> {
 public: 
  enum domain 
  {
Handle, ObjectName,   };
  OS_AdditionalPropertiesFields()
   : EnumBase<OS_AdditionalPropertiesFields>(Handle) {} 
  OS_AdditionalPropertiesFields(const std::string &t_name) 
   : EnumBase<OS_AdditionalPropertiesFields>(t_name) {} 
  OS_AdditionalPropertiesFields(int t_value) 
   : EnumBase<OS_AdditionalPropertiesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AdditionalPropertiesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AdditionalPropertiesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AdditionalPropertiesFields>;
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
{ OS_AdditionalPropertiesFields::Handle, "Handle", "Handle"},
{ OS_AdditionalPropertiesFields::ObjectName, "ObjectName", "Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AdditionalPropertiesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AdditionalPropertiesFields> OptionalOS_AdditionalPropertiesFields ;
#endif

/** \class OS_AdditionalPropertiesExtensibleFields
 *  \brief Enumeration of OS:AdditionalProperties's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AdditionalPropertiesExtensibleFields, )
#else
class OS_AdditionalPropertiesExtensibleFields: public ::EnumBase<OS_AdditionalPropertiesExtensibleFields> {
 public: 
  enum domain 
  {
FeatureName, FeatureDataType, FeatureValue,   };
  OS_AdditionalPropertiesExtensibleFields()
   : EnumBase<OS_AdditionalPropertiesExtensibleFields>(FeatureName) {} 
  OS_AdditionalPropertiesExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AdditionalPropertiesExtensibleFields>(t_name) {} 
  OS_AdditionalPropertiesExtensibleFields(int t_value) 
   : EnumBase<OS_AdditionalPropertiesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AdditionalPropertiesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AdditionalPropertiesExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AdditionalPropertiesExtensibleFields>;
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
{ OS_AdditionalPropertiesExtensibleFields::FeatureName, "FeatureName", "Feature Name"},
{ OS_AdditionalPropertiesExtensibleFields::FeatureDataType, "FeatureDataType", "Feature Data Type"},
{ OS_AdditionalPropertiesExtensibleFields::FeatureValue, "FeatureValue", "Feature Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AdditionalPropertiesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AdditionalPropertiesExtensibleFields> OptionalOS_AdditionalPropertiesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ADDITIONALPROPERTIES_FIELDENUMS_HXX
