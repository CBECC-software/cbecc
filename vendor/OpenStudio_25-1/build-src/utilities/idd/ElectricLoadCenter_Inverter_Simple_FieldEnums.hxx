/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_SIMPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_SIMPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Inverter_SimpleFields
 *  \brief Enumeration of ElectricLoadCenter:Inverter:Simple's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Inverter_SimpleFields, )
#else
class ElectricLoadCenter_Inverter_SimpleFields: public ::EnumBase<ElectricLoadCenter_Inverter_SimpleFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, InverterEfficiency,   };
  ElectricLoadCenter_Inverter_SimpleFields()
   : EnumBase<ElectricLoadCenter_Inverter_SimpleFields>(Name) {} 
  ElectricLoadCenter_Inverter_SimpleFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Inverter_SimpleFields>(t_name) {} 
  ElectricLoadCenter_Inverter_SimpleFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Inverter_SimpleFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Inverter_SimpleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Inverter_SimpleFields>::integer_value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Inverter_SimpleFields>;
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
{ ElectricLoadCenter_Inverter_SimpleFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Inverter_SimpleFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Inverter_SimpleFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Inverter_SimpleFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_Inverter_SimpleFields::InverterEfficiency, "InverterEfficiency", "Inverter Efficiency"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Inverter_SimpleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Inverter_SimpleFields> OptionalElectricLoadCenter_Inverter_SimpleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_SIMPLE_FIELDENUMS_HXX
