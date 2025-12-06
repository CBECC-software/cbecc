/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterUse_EquipmentFields
 *  \brief Enumeration of OS:WaterUse:Equipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterUse_EquipmentFields, )
#else
class OS_WaterUse_EquipmentFields: public ::EnumBase<OS_WaterUse_EquipmentFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterUseEquipmentDefinitionName, SpaceName, FlowRateFractionScheduleName,   };
  OS_WaterUse_EquipmentFields()
   : EnumBase<OS_WaterUse_EquipmentFields>(Handle) {} 
  OS_WaterUse_EquipmentFields(const std::string &t_name) 
   : EnumBase<OS_WaterUse_EquipmentFields>(t_name) {} 
  OS_WaterUse_EquipmentFields(int t_value) 
   : EnumBase<OS_WaterUse_EquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterUse_EquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterUse_EquipmentFields>::integer_value()); }
   private:
    friend class EnumBase<OS_WaterUse_EquipmentFields>;
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
{ OS_WaterUse_EquipmentFields::Handle, "Handle", "Handle"},
{ OS_WaterUse_EquipmentFields::Name, "Name", "Name"},
{ OS_WaterUse_EquipmentFields::WaterUseEquipmentDefinitionName, "WaterUseEquipmentDefinitionName", "Water Use Equipment Definition Name"},
{ OS_WaterUse_EquipmentFields::SpaceName, "SpaceName", "Space Name"},
{ OS_WaterUse_EquipmentFields::FlowRateFractionScheduleName, "FlowRateFractionScheduleName", "Flow Rate Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterUse_EquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterUse_EquipmentFields> OptionalOS_WaterUse_EquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_FIELDENUMS_HXX
