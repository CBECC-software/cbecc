/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PYTHONPLUGIN_INSTANCE_FIELDENUMS_HXX
#define UTILITIES_IDD_PYTHONPLUGIN_INSTANCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PythonPlugin_InstanceFields
 *  \brief Enumeration of PythonPlugin:Instance's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PythonPlugin_InstanceFields, )
#else
class PythonPlugin_InstanceFields: public ::EnumBase<PythonPlugin_InstanceFields> {
 public: 
  enum domain 
  {
Name, RunDuringWarmupDays, PythonModuleName, PluginClassName,   };
  PythonPlugin_InstanceFields()
   : EnumBase<PythonPlugin_InstanceFields>(Name) {} 
  PythonPlugin_InstanceFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_InstanceFields>(t_name) {} 
  PythonPlugin_InstanceFields(int t_value) 
   : EnumBase<PythonPlugin_InstanceFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_InstanceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_InstanceFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_InstanceFields>;
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
{ PythonPlugin_InstanceFields::Name, "Name", "Name"},
{ PythonPlugin_InstanceFields::RunDuringWarmupDays, "RunDuringWarmupDays", "Run During Warmup Days"},
{ PythonPlugin_InstanceFields::PythonModuleName, "PythonModuleName", "Python Module Name"},
{ PythonPlugin_InstanceFields::PluginClassName, "PluginClassName", "Plugin Class Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_InstanceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_InstanceFields> OptionalPythonPlugin_InstanceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PYTHONPLUGIN_INSTANCE_FIELDENUMS_HXX
