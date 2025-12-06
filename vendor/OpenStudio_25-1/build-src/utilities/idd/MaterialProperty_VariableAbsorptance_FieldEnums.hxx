/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_MATERIALPROPERTY_VARIABLEABSORPTANCE_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_VARIABLEABSORPTANCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_VariableAbsorptanceFields
 *  \brief Enumeration of MaterialProperty:VariableAbsorptance's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_VariableAbsorptanceFields, )
#else
class MaterialProperty_VariableAbsorptanceFields: public ::EnumBase<MaterialProperty_VariableAbsorptanceFields> {
 public: 
  enum domain 
  {
Name, ReferenceMaterialName, ControlSignal, ThermalAbsorptanceFunctionName, ThermalAbsorptanceScheduleName, SolarAbsorptanceFunctionName, SolarAbsorptanceScheduleName,   };
  MaterialProperty_VariableAbsorptanceFields()
   : EnumBase<MaterialProperty_VariableAbsorptanceFields>(Name) {} 
  MaterialProperty_VariableAbsorptanceFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_VariableAbsorptanceFields>(t_name) {} 
  MaterialProperty_VariableAbsorptanceFields(int t_value) 
   : EnumBase<MaterialProperty_VariableAbsorptanceFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_VariableAbsorptanceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_VariableAbsorptanceFields>::integer_value()); }
   private:
    friend class EnumBase<MaterialProperty_VariableAbsorptanceFields>;
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
{ MaterialProperty_VariableAbsorptanceFields::Name, "Name", "Name"},
{ MaterialProperty_VariableAbsorptanceFields::ReferenceMaterialName, "ReferenceMaterialName", "Reference Material Name"},
{ MaterialProperty_VariableAbsorptanceFields::ControlSignal, "ControlSignal", "Control Signal"},
{ MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceFunctionName, "ThermalAbsorptanceFunctionName", "Thermal Absorptance Function Name"},
{ MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceScheduleName, "ThermalAbsorptanceScheduleName", "Thermal Absorptance Schedule Name"},
{ MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceFunctionName, "SolarAbsorptanceFunctionName", "Solar Absorptance Function Name"},
{ MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceScheduleName, "SolarAbsorptanceScheduleName", "Solar Absorptance Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_VariableAbsorptanceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_VariableAbsorptanceFields> OptionalMaterialProperty_VariableAbsorptanceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_VARIABLEABSORPTANCE_FIELDENUMS_HXX
