/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONECAPACITANCEMULTIPLIER_RESEARCHSPECIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONECAPACITANCEMULTIPLIER_RESEARCHSPECIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneCapacitanceMultiplier_ResearchSpecialFields
 *  \brief Enumeration of OS:ZoneCapacitanceMultiplier:ResearchSpecial's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneCapacitanceMultiplier_ResearchSpecialFields, )
#else
class OS_ZoneCapacitanceMultiplier_ResearchSpecialFields: public ::EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields> {
 public: 
  enum domain 
  {
Handle, TemperatureCapacityMultiplier, HumidityCapacityMultiplier, CarbonDioxideCapacityMultiplier,   };
  OS_ZoneCapacitanceMultiplier_ResearchSpecialFields()
   : EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields>(Handle) {} 
  OS_ZoneCapacitanceMultiplier_ResearchSpecialFields(const std::string &t_name) 
   : EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields>(t_name) {} 
  OS_ZoneCapacitanceMultiplier_ResearchSpecialFields(int t_value) 
   : EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneCapacitanceMultiplier_ResearchSpecialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields>;
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
{ OS_ZoneCapacitanceMultiplier_ResearchSpecialFields::Handle, "Handle", "Handle"},
{ OS_ZoneCapacitanceMultiplier_ResearchSpecialFields::TemperatureCapacityMultiplier, "TemperatureCapacityMultiplier", "Temperature Capacity Multiplier"},
{ OS_ZoneCapacitanceMultiplier_ResearchSpecialFields::HumidityCapacityMultiplier, "HumidityCapacityMultiplier", "Humidity Capacity Multiplier"},
{ OS_ZoneCapacitanceMultiplier_ResearchSpecialFields::CarbonDioxideCapacityMultiplier, "CarbonDioxideCapacityMultiplier", "Carbon Dioxide Capacity Multiplier"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneCapacitanceMultiplier_ResearchSpecialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneCapacitanceMultiplier_ResearchSpecialFields> OptionalOS_ZoneCapacitanceMultiplier_ResearchSpecialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONECAPACITANCEMULTIPLIER_RESEARCHSPECIAL_FIELDENUMS_HXX
