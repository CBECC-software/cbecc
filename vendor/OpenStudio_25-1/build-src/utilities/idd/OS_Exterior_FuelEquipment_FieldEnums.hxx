/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_EXTERIOR_FUELEQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_EXTERIOR_FUELEQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Exterior_FuelEquipmentFields
 *  \brief Enumeration of OS:Exterior:FuelEquipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Exterior_FuelEquipmentFields, )
#else
class OS_Exterior_FuelEquipmentFields: public ::EnumBase<OS_Exterior_FuelEquipmentFields> {
 public: 
  enum domain 
  {
Handle, Name, ExteriorFuelEquipmentDefinitionName, ScheduleName, FuelUseType, Multiplier, EndUseSubcategory,   };
  OS_Exterior_FuelEquipmentFields()
   : EnumBase<OS_Exterior_FuelEquipmentFields>(Handle) {} 
  OS_Exterior_FuelEquipmentFields(const std::string &t_name) 
   : EnumBase<OS_Exterior_FuelEquipmentFields>(t_name) {} 
  OS_Exterior_FuelEquipmentFields(int t_value) 
   : EnumBase<OS_Exterior_FuelEquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Exterior_FuelEquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Exterior_FuelEquipmentFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Exterior_FuelEquipmentFields>;
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
{ OS_Exterior_FuelEquipmentFields::Handle, "Handle", "Handle"},
{ OS_Exterior_FuelEquipmentFields::Name, "Name", "Name"},
{ OS_Exterior_FuelEquipmentFields::ExteriorFuelEquipmentDefinitionName, "ExteriorFuelEquipmentDefinitionName", "Exterior Fuel Equipment Definition Name"},
{ OS_Exterior_FuelEquipmentFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_Exterior_FuelEquipmentFields::FuelUseType, "FuelUseType", "Fuel Use Type"},
{ OS_Exterior_FuelEquipmentFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_Exterior_FuelEquipmentFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Exterior_FuelEquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Exterior_FuelEquipmentFields> OptionalOS_Exterior_FuelEquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_EXTERIOR_FUELEQUIPMENT_FIELDENUMS_HXX
