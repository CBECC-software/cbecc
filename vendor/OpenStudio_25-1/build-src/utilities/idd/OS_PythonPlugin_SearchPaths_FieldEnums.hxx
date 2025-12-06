/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PythonPlugin_SearchPathsFields
 *  \brief Enumeration of OS:PythonPlugin:SearchPaths's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PythonPlugin_SearchPathsFields, )
#else
class OS_PythonPlugin_SearchPathsFields: public ::EnumBase<OS_PythonPlugin_SearchPathsFields> {
 public: 
  enum domain 
  {
Handle, AddCurrentWorkingDirectorytoSearchPath, AddInputFileDirectorytoSearchPath, AddepinEnvironmentVariabletoSearchPath,   };
  OS_PythonPlugin_SearchPathsFields()
   : EnumBase<OS_PythonPlugin_SearchPathsFields>(Handle) {} 
  OS_PythonPlugin_SearchPathsFields(const std::string &t_name) 
   : EnumBase<OS_PythonPlugin_SearchPathsFields>(t_name) {} 
  OS_PythonPlugin_SearchPathsFields(int t_value) 
   : EnumBase<OS_PythonPlugin_SearchPathsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PythonPlugin_SearchPathsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PythonPlugin_SearchPathsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_PythonPlugin_SearchPathsFields>;
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
{ OS_PythonPlugin_SearchPathsFields::Handle, "Handle", "Handle"},
{ OS_PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath, "AddCurrentWorkingDirectorytoSearchPath", "Add Current Working Directory to Search Path"},
{ OS_PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath, "AddInputFileDirectorytoSearchPath", "Add Input File Directory to Search Path"},
{ OS_PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath, "AddepinEnvironmentVariabletoSearchPath", "Add epin Environment Variable to Search Path"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PythonPlugin_SearchPathsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PythonPlugin_SearchPathsFields> OptionalOS_PythonPlugin_SearchPathsFields ;
#endif

/** \class OS_PythonPlugin_SearchPathsExtensibleFields
 *  \brief Enumeration of OS:PythonPlugin:SearchPaths's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_PythonPlugin_SearchPathsExtensibleFields, )
#else
class OS_PythonPlugin_SearchPathsExtensibleFields: public ::EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields> {
 public: 
  enum domain 
  {
SearchPath,   };
  OS_PythonPlugin_SearchPathsExtensibleFields()
   : EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields>(SearchPath) {} 
  OS_PythonPlugin_SearchPathsExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields>(t_name) {} 
  OS_PythonPlugin_SearchPathsExtensibleFields(int t_value) 
   : EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PythonPlugin_SearchPathsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_PythonPlugin_SearchPathsExtensibleFields>;
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
{ OS_PythonPlugin_SearchPathsExtensibleFields::SearchPath, "SearchPath", "Search Path"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PythonPlugin_SearchPathsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PythonPlugin_SearchPathsExtensibleFields> OptionalOS_PythonPlugin_SearchPathsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX
