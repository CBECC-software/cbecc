/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PythonPlugin_OutputVariableFields
 *  \brief Enumeration of OS:PythonPlugin:OutputVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PythonPlugin_OutputVariableFields, )
#else
class OS_PythonPlugin_OutputVariableFields: public ::EnumBase<OS_PythonPlugin_OutputVariableFields> {
 public: 
  enum domain 
  {
Handle, Name, PythonPluginVariableName, TypeofDatainVariable, UpdateFrequency, Units, ResourceType, GroupType, EndUseCategory, EndUseSubcategory,   };
  OS_PythonPlugin_OutputVariableFields()
   : EnumBase<OS_PythonPlugin_OutputVariableFields>(Handle) {} 
  OS_PythonPlugin_OutputVariableFields(const std::string &t_name) 
   : EnumBase<OS_PythonPlugin_OutputVariableFields>(t_name) {} 
  OS_PythonPlugin_OutputVariableFields(int t_value) 
   : EnumBase<OS_PythonPlugin_OutputVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PythonPlugin_OutputVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PythonPlugin_OutputVariableFields>::integer_value()); }
   private:
    friend class EnumBase<OS_PythonPlugin_OutputVariableFields>;
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
{ OS_PythonPlugin_OutputVariableFields::Handle, "Handle", "Handle"},
{ OS_PythonPlugin_OutputVariableFields::Name, "Name", "Name"},
{ OS_PythonPlugin_OutputVariableFields::PythonPluginVariableName, "PythonPluginVariableName", "Python Plugin Variable Name"},
{ OS_PythonPlugin_OutputVariableFields::TypeofDatainVariable, "TypeofDatainVariable", "Type of Data in Variable"},
{ OS_PythonPlugin_OutputVariableFields::UpdateFrequency, "UpdateFrequency", "Update Frequency"},
{ OS_PythonPlugin_OutputVariableFields::Units, "Units", "Units"},
{ OS_PythonPlugin_OutputVariableFields::ResourceType, "ResourceType", "Resource Type"},
{ OS_PythonPlugin_OutputVariableFields::GroupType, "GroupType", "Group Type"},
{ OS_PythonPlugin_OutputVariableFields::EndUseCategory, "EndUseCategory", "End-Use Category"},
{ OS_PythonPlugin_OutputVariableFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PythonPlugin_OutputVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PythonPlugin_OutputVariableFields> OptionalOS_PythonPlugin_OutputVariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX
