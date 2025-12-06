/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_EXTERIOR_WATEREQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EXTERIOR_WATEREQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Exterior_WaterEquipmentFields
 *  \brief Enumeration of OS:Exterior:WaterEquipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Exterior_WaterEquipmentFields, )
#else
class OS_Exterior_WaterEquipmentFields: public ::EnumBase<OS_Exterior_WaterEquipmentFields> {
 public: 
  enum domain 
  {
Handle, Name, ExteriorWaterEquipmentDefinitionName, ScheduleName, Multiplier, EndUseSubcategory,   };
  OS_Exterior_WaterEquipmentFields()
   : EnumBase<OS_Exterior_WaterEquipmentFields>(Handle) {} 
  OS_Exterior_WaterEquipmentFields(const std::string &t_name) 
   : EnumBase<OS_Exterior_WaterEquipmentFields>(t_name) {} 
  OS_Exterior_WaterEquipmentFields(int t_value) 
   : EnumBase<OS_Exterior_WaterEquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Exterior_WaterEquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Exterior_WaterEquipmentFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Exterior_WaterEquipmentFields>;
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
{ OS_Exterior_WaterEquipmentFields::Handle, "Handle", "Handle"},
{ OS_Exterior_WaterEquipmentFields::Name, "Name", "Name"},
{ OS_Exterior_WaterEquipmentFields::ExteriorWaterEquipmentDefinitionName, "ExteriorWaterEquipmentDefinitionName", "Exterior Water Equipment Definition Name"},
{ OS_Exterior_WaterEquipmentFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_Exterior_WaterEquipmentFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_Exterior_WaterEquipmentFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Exterior_WaterEquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Exterior_WaterEquipmentFields> OptionalOS_Exterior_WaterEquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EXTERIOR_WATEREQUIPMENT_FIELDENUMS_HXX
