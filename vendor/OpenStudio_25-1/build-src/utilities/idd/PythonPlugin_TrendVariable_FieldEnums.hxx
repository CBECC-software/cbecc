/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PYTHONPLUGIN_TRENDVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_PYTHONPLUGIN_TRENDVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PythonPlugin_TrendVariableFields
 *  \brief Enumeration of PythonPlugin:TrendVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PythonPlugin_TrendVariableFields, )
#else
class PythonPlugin_TrendVariableFields: public ::EnumBase<PythonPlugin_TrendVariableFields> {
 public: 
  enum domain 
  {
Name, NameofaPythonPluginVariable, NumberofTimestepstobeLogged,   };
  PythonPlugin_TrendVariableFields()
   : EnumBase<PythonPlugin_TrendVariableFields>(Name) {} 
  PythonPlugin_TrendVariableFields(const std::string &t_name) 
   : EnumBase<PythonPlugin_TrendVariableFields>(t_name) {} 
  PythonPlugin_TrendVariableFields(int t_value) 
   : EnumBase<PythonPlugin_TrendVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "PythonPlugin_TrendVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PythonPlugin_TrendVariableFields>::integer_value()); }
   private:
    friend class EnumBase<PythonPlugin_TrendVariableFields>;
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
{ PythonPlugin_TrendVariableFields::Name, "Name", "Name"},
{ PythonPlugin_TrendVariableFields::NameofaPythonPluginVariable, "NameofaPythonPluginVariable", "Name of a Python Plugin Variable"},
{ PythonPlugin_TrendVariableFields::NumberofTimestepstobeLogged, "NumberofTimestepstobeLogged", "Number of Timesteps to be Logged"},
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
  inline std::ostream &operator<<(std::ostream &os, const PythonPlugin_TrendVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PythonPlugin_TrendVariableFields> OptionalPythonPlugin_TrendVariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PYTHONPLUGIN_TRENDVARIABLE_FIELDENUMS_HXX
