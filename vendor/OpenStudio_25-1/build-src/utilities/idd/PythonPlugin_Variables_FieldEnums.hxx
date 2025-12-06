/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PYTHONPLUGIN_VARIABLES_FIELDENUMS_HXX
#define UTILITIES_IDD_PYTHONPLUGIN_VARIABLES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PythonPlugin_VariablesFields
 *  \brief Enumeration of PythonPlugin:Variables's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PythonPlugin_VariablesFields, )
#else
class PythonPlugin_VariablesFields: public ::EnumBase<PythonPlugin_VariablesFields> {
 public: 
  enum domain 
  {
Name,   };
  PythonPlugin_VariablesFields()
   : EnumBase<PythonPlugin_VariablesFields>(Name) {} 
  PythonPlugin_VariablesFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_VariablesFields>(t_name) {} 
  PythonPlugin_VariablesFields(int t_value) 
   : EnumBase<PythonPlugin_VariablesFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_VariablesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_VariablesFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_VariablesFields>;
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
{ PythonPlugin_VariablesFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_VariablesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_VariablesFields> OptionalPythonPlugin_VariablesFields ;
#endif

/** \class PythonPlugin_VariablesExtensibleFields
 *  \brief Enumeration of PythonPlugin:Variables's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PythonPlugin_VariablesExtensibleFields, )
#else
class PythonPlugin_VariablesExtensibleFields: public ::EnumBase<PythonPlugin_VariablesExtensibleFields> {
 public: 
  enum domain 
  {
VariableName,   };
  PythonPlugin_VariablesExtensibleFields()
   : EnumBase<PythonPlugin_VariablesExtensibleFields>(VariableName) {} 
  PythonPlugin_VariablesExtensibleFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_VariablesExtensibleFields>(t_name) {} 
  PythonPlugin_VariablesExtensibleFields(int t_value) 
   : EnumBase<PythonPlugin_VariablesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_VariablesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_VariablesExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_VariablesExtensibleFields>;
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
{ PythonPlugin_VariablesExtensibleFields::VariableName, "VariableName", "Variable Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_VariablesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_VariablesExtensibleFields> OptionalPythonPlugin_VariablesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PYTHONPLUGIN_VARIABLES_FIELDENUMS_HXX
