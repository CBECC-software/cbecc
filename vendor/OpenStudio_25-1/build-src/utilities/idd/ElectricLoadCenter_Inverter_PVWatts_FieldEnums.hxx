/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_PVWATTS_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_PVWATTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Inverter_PVWattsFields
 *  \brief Enumeration of ElectricLoadCenter:Inverter:PVWatts's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Inverter_PVWattsFields, )
#else
class ElectricLoadCenter_Inverter_PVWattsFields: public ::EnumBase<ElectricLoadCenter_Inverter_PVWattsFields> {
 public: 
  enum domain 
  {
Name, DCtoACSizeRatio, InverterEfficiency,   };
  ElectricLoadCenter_Inverter_PVWattsFields()
   : EnumBase<ElectricLoadCenter_Inverter_PVWattsFields>(Name) {} 
  ElectricLoadCenter_Inverter_PVWattsFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Inverter_PVWattsFields>(t_name) {} 
  ElectricLoadCenter_Inverter_PVWattsFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Inverter_PVWattsFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Inverter_PVWattsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Inverter_PVWattsFields>::integer_value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Inverter_PVWattsFields>;
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
{ ElectricLoadCenter_Inverter_PVWattsFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Inverter_PVWattsFields::DCtoACSizeRatio, "DCtoACSizeRatio", "DC to AC Size Ratio"},
{ ElectricLoadCenter_Inverter_PVWattsFields::InverterEfficiency, "InverterEfficiency", "Inverter Efficiency"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Inverter_PVWattsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Inverter_PVWattsFields> OptionalElectricLoadCenter_Inverter_PVWattsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_PVWATTS_FIELDENUMS_HXX
