/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX
#define UTILITIES_IDD_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PythonPlugin_SearchPathsFields
 *  \brief Enumeration of PythonPlugin:SearchPaths's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PythonPlugin_SearchPathsFields, )
#else
class PythonPlugin_SearchPathsFields: public ::EnumBase<PythonPlugin_SearchPathsFields> {
 public: 
  enum domain 
  {
Name, AddCurrentWorkingDirectorytoSearchPath, AddInputFileDirectorytoSearchPath, AddepinEnvironmentVariabletoSearchPath,   };
  PythonPlugin_SearchPathsFields()
   : EnumBase<PythonPlugin_SearchPathsFields>(Name) {} 
  PythonPlugin_SearchPathsFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_SearchPathsFields>(t_name) {} 
  PythonPlugin_SearchPathsFields(int t_value) 
   : EnumBase<PythonPlugin_SearchPathsFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_SearchPathsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_SearchPathsFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_SearchPathsFields>;
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
{ PythonPlugin_SearchPathsFields::Name, "Name", "Name"},
{ PythonPlugin_SearchPathsFields::AddCurrentWorkingDirectorytoSearchPath, "AddCurrentWorkingDirectorytoSearchPath", "Add Current Working Directory to Search Path"},
{ PythonPlugin_SearchPathsFields::AddInputFileDirectorytoSearchPath, "AddInputFileDirectorytoSearchPath", "Add Input File Directory to Search Path"},
{ PythonPlugin_SearchPathsFields::AddepinEnvironmentVariabletoSearchPath, "AddepinEnvironmentVariabletoSearchPath", "Add epin Environment Variable to Search Path"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_SearchPathsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_SearchPathsFields> OptionalPythonPlugin_SearchPathsFields ;
#endif

/** \class PythonPlugin_SearchPathsExtensibleFields
 *  \brief Enumeration of PythonPlugin:SearchPaths's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PythonPlugin_SearchPathsExtensibleFields, )
#else
class PythonPlugin_SearchPathsExtensibleFields: public ::EnumBase<PythonPlugin_SearchPathsExtensibleFields> {
 public: 
  enum domain 
  {
SearchPath,   };
  PythonPlugin_SearchPathsExtensibleFields()
   : EnumBase<PythonPlugin_SearchPathsExtensibleFields>(SearchPath) {} 
  PythonPlugin_SearchPathsExtensibleFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_SearchPathsExtensibleFields>(t_name) {} 
  PythonPlugin_SearchPathsExtensibleFields(int t_value) 
   : EnumBase<PythonPlugin_SearchPathsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_SearchPathsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_SearchPathsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_SearchPathsExtensibleFields>;
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
{ PythonPlugin_SearchPathsExtensibleFields::SearchPath, "SearchPath", "Search Path"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_SearchPathsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_SearchPathsExtensibleFields> OptionalPythonPlugin_SearchPathsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PYTHONPLUGIN_SEARCHPATHS_FIELDENUMS_HXX
