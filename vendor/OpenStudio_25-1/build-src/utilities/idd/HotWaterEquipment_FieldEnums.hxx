/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HOTWATEREQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_HOTWATEREQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HotWaterEquipmentFields
 *  \brief Enumeration of HotWaterEquipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HotWaterEquipmentFields, )
#else
class HotWaterEquipmentFields: public ::EnumBase<HotWaterEquipmentFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListorSpaceorSpaceListName, ScheduleName, DesignLevelCalculationMethod, DesignLevel, PowerperFloorArea, PowerperPerson, FractionLatent, FractionRadiant, FractionLost, EndUseSubcategory,   };
  HotWaterEquipmentFields()
   : EnumBase<HotWaterEquipmentFields>(Name) {} 
  HotWaterEquipmentFields(const std::string &t_name) 
   : EnumBase<HotWaterEquipmentFields>(t_name) {} 
  HotWaterEquipmentFields(int t_value) 
   : EnumBase<HotWaterEquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "HotWaterEquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HotWaterEquipmentFields>::integer_value()); }
   private:
    friend class EnumBase<HotWaterEquipmentFields>;
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
{ HotWaterEquipmentFields::Name, "Name", "Name"},
{ HotWaterEquipmentFields::ZoneorZoneListorSpaceorSpaceListName, "ZoneorZoneListorSpaceorSpaceListName", "Zone or ZoneList or Space or SpaceList Name"},
{ HotWaterEquipmentFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ HotWaterEquipmentFields::DesignLevelCalculationMethod, "DesignLevelCalculationMethod", "Design Level Calculation Method"},
{ HotWaterEquipmentFields::DesignLevel, "DesignLevel", "Design Level"},
{ HotWaterEquipmentFields::PowerperFloorArea, "PowerperFloorArea", "Power per Floor Area"},
{ HotWaterEquipmentFields::PowerperPerson, "PowerperPerson", "Power per Person"},
{ HotWaterEquipmentFields::FractionLatent, "FractionLatent", "Fraction Latent"},
{ HotWaterEquipmentFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ HotWaterEquipmentFields::FractionLost, "FractionLost", "Fraction Lost"},
{ HotWaterEquipmentFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const HotWaterEquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HotWaterEquipmentFields> OptionalHotWaterEquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HOTWATEREQUIPMENT_FIELDENUMS_HXX
