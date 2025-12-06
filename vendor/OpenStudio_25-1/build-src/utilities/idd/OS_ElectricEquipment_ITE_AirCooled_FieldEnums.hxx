/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricEquipment_ITE_AirCooledFields
 *  \brief Enumeration of OS:ElectricEquipment:ITE:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricEquipment_ITE_AirCooledFields, )
#else
class OS_ElectricEquipment_ITE_AirCooledFields: public ::EnumBase<OS_ElectricEquipment_ITE_AirCooledFields> {
 public: 
  enum domain 
  {
Handle, Name, ElectricEquipmentITEAirCooledDefinitionName, SpaceorSpaceTypeName, DesignPowerInputScheduleName, CPULoadingScheduleName, Multiplier, CPUEndUseSubcategory, FanEndUseSubcategory, ElectricPowerSupplyEndUseSubcategory,   };
  OS_ElectricEquipment_ITE_AirCooledFields()
   : EnumBase<OS_ElectricEquipment_ITE_AirCooledFields>(Handle) {} 
  OS_ElectricEquipment_ITE_AirCooledFields(const std::string &t_name) 
   : EnumBase<OS_ElectricEquipment_ITE_AirCooledFields>(t_name) {} 
  OS_ElectricEquipment_ITE_AirCooledFields(int t_value) 
   : EnumBase<OS_ElectricEquipment_ITE_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricEquipment_ITE_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricEquipment_ITE_AirCooledFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricEquipment_ITE_AirCooledFields>;
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
{ OS_ElectricEquipment_ITE_AirCooledFields::Handle, "Handle", "Handle"},
{ OS_ElectricEquipment_ITE_AirCooledFields::Name, "Name", "Name"},
{ OS_ElectricEquipment_ITE_AirCooledFields::ElectricEquipmentITEAirCooledDefinitionName, "ElectricEquipmentITEAirCooledDefinitionName", "Electric Equipment ITE AirCooled Definition Name"},
{ OS_ElectricEquipment_ITE_AirCooledFields::SpaceorSpaceTypeName, "SpaceorSpaceTypeName", "Space or SpaceType Name"},
{ OS_ElectricEquipment_ITE_AirCooledFields::DesignPowerInputScheduleName, "DesignPowerInputScheduleName", "Design Power Input Schedule Name"},
{ OS_ElectricEquipment_ITE_AirCooledFields::CPULoadingScheduleName, "CPULoadingScheduleName", "CPU Loading Schedule Name"},
{ OS_ElectricEquipment_ITE_AirCooledFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory, "CPUEndUseSubcategory", "CPU End-Use Subcategory"},
{ OS_ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory, "FanEndUseSubcategory", "Fan End-Use Subcategory"},
{ OS_ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory, "ElectricPowerSupplyEndUseSubcategory", "Electric Power Supply End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricEquipment_ITE_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricEquipment_ITE_AirCooledFields> OptionalOS_ElectricEquipment_ITE_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX
