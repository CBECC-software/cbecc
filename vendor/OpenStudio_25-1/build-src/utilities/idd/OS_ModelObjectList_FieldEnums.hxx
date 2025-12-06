/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MODELOBJECTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MODELOBJECTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ModelObjectListFields
 *  \brief Enumeration of OS:ModelObjectList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ModelObjectListFields, )
#else
class OS_ModelObjectListFields: public ::EnumBase<OS_ModelObjectListFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_ModelObjectListFields()
   : EnumBase<OS_ModelObjectListFields>(Handle) {} 
  OS_ModelObjectListFields(const std::string &t_name) 
   : EnumBase<OS_ModelObjectListFields>(t_name) {} 
  OS_ModelObjectListFields(int t_value) 
   : EnumBase<OS_ModelObjectListFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ModelObjectListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ModelObjectListFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ModelObjectListFields>;
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
{ OS_ModelObjectListFields::Handle, "Handle", "Handle"},
{ OS_ModelObjectListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ModelObjectListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ModelObjectListFields> OptionalOS_ModelObjectListFields ;
#endif

/** \class OS_ModelObjectListExtensibleFields
 *  \brief Enumeration of OS:ModelObjectList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ModelObjectListExtensibleFields, )
#else
class OS_ModelObjectListExtensibleFields: public ::EnumBase<OS_ModelObjectListExtensibleFields> {
 public: 
  enum domain 
  {
ModelObject,   };
  OS_ModelObjectListExtensibleFields()
   : EnumBase<OS_ModelObjectListExtensibleFields>(ModelObject) {} 
  OS_ModelObjectListExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ModelObjectListExtensibleFields>(t_name) {} 
  OS_ModelObjectListExtensibleFields(int t_value) 
   : EnumBase<OS_ModelObjectListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ModelObjectListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ModelObjectListExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ModelObjectListExtensibleFields>;
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
{ OS_ModelObjectListExtensibleFields::ModelObject, "ModelObject", "Model Object"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ModelObjectListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ModelObjectListExtensibleFields> OptionalOS_ModelObjectListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MODELOBJECTLIST_FIELDENUMS_HXX
