/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_METEREDOUTPUTVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_METEREDOUTPUTVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_EnergyManagementSystem_MeteredOutputVariableFields
 *  \brief Enumeration of OS:EnergyManagementSystem:MeteredOutputVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_EnergyManagementSystem_MeteredOutputVariableFields, )
#else
class OS_EnergyManagementSystem_MeteredOutputVariableFields: public ::EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields> {
 public: 
  enum domain 
  {
Handle, Name, EMSVariableName, UpdateFrequency, EMSProgramorSubroutineName, ResourceType, GroupType, EndUseCategory, EndUseSubcategory, Units,   };
  OS_EnergyManagementSystem_MeteredOutputVariableFields()
   : EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields>(Handle) {} 
  OS_EnergyManagementSystem_MeteredOutputVariableFields(const std::string &t_name) 
   : EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields>(t_name) {} 
  OS_EnergyManagementSystem_MeteredOutputVariableFields(int t_value) 
   : EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EnergyManagementSystem_MeteredOutputVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields>::integer_value()); }
   private:
    friend class EnumBase<OS_EnergyManagementSystem_MeteredOutputVariableFields>;
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
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::Handle, "Handle", "Handle"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::Name, "Name", "Name"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::EMSVariableName, "EMSVariableName", "EMS Variable Name"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::UpdateFrequency, "UpdateFrequency", "Update Frequency"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::EMSProgramorSubroutineName, "EMSProgramorSubroutineName", "EMS Program or Subroutine Name"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::ResourceType, "ResourceType", "Resource Type"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::GroupType, "GroupType", "Group Type"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::EndUseCategory, "EndUseCategory", "End-Use Category"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_EnergyManagementSystem_MeteredOutputVariableFields::Units, "Units", "Units"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EnergyManagementSystem_MeteredOutputVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EnergyManagementSystem_MeteredOutputVariableFields> OptionalOS_EnergyManagementSystem_MeteredOutputVariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_METEREDOUTPUTVARIABLE_FIELDENUMS_HXX
