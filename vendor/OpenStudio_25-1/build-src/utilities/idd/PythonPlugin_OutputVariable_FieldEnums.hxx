/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PythonPlugin_OutputVariableFields
 *  \brief Enumeration of PythonPlugin:OutputVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PythonPlugin_OutputVariableFields, )
#else
class PythonPlugin_OutputVariableFields: public ::EnumBase<PythonPlugin_OutputVariableFields> {
 public: 
  enum domain 
  {
Name, PythonPluginVariableName, TypeofDatainVariable, UpdateFrequency, Units, ResourceType, GroupType, EndUseCategory, EndUseSubcategory,   };
  PythonPlugin_OutputVariableFields()
   : EnumBase<PythonPlugin_OutputVariableFields>(Name) {} 
  PythonPlugin_OutputVariableFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_OutputVariableFields>(t_name) {} 
  PythonPlugin_OutputVariableFields(int t_value) 
   : EnumBase<PythonPlugin_OutputVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_OutputVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_OutputVariableFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_OutputVariableFields>;
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
{ PythonPlugin_OutputVariableFields::Name, "Name", "Name"},
{ PythonPlugin_OutputVariableFields::PythonPluginVariableName, "PythonPluginVariableName", "Python Plugin Variable Name"},
{ PythonPlugin_OutputVariableFields::TypeofDatainVariable, "TypeofDatainVariable", "Type of Data in Variable"},
{ PythonPlugin_OutputVariableFields::UpdateFrequency, "UpdateFrequency", "Update Frequency"},
{ PythonPlugin_OutputVariableFields::Units, "Units", "Units"},
{ PythonPlugin_OutputVariableFields::ResourceType, "ResourceType", "Resource Type"},
{ PythonPlugin_OutputVariableFields::GroupType, "GroupType", "Group Type"},
{ PythonPlugin_OutputVariableFields::EndUseCategory, "EndUseCategory", "End-Use Category"},
{ PythonPlugin_OutputVariableFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_OutputVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_OutputVariableFields> OptionalPythonPlugin_OutputVariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PYTHONPLUGIN_OUTPUTVARIABLE_FIELDENUMS_HXX
