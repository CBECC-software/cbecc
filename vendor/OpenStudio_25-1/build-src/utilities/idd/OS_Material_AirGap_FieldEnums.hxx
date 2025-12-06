/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIAL_AIRGAP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIAL_AIRGAP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Material_AirGapFields
 *  \brief Enumeration of OS:Material:AirGap's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Material_AirGapFields, )
#else
class OS_Material_AirGapFields: public ::EnumBase<OS_Material_AirGapFields> {
 public: 
  enum domain 
  {
Handle, Name, ThermalResistance,   };
  OS_Material_AirGapFields()
   : EnumBase<OS_Material_AirGapFields>(Handle) {} 
  OS_Material_AirGapFields(const std::string &t_name) 
   : EnumBase<OS_Material_AirGapFields>(t_name) {} 
  OS_Material_AirGapFields(int t_value) 
   : EnumBase<OS_Material_AirGapFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Material_AirGapFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Material_AirGapFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Material_AirGapFields>;
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
{ OS_Material_AirGapFields::Handle, "Handle", "Handle"},
{ OS_Material_AirGapFields::Name, "Name", "Name"},
{ OS_Material_AirGapFields::ThermalResistance, "ThermalResistance", "Thermal Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Material_AirGapFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Material_AirGapFields> OptionalOS_Material_AirGapFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIAL_AIRGAP_FIELDENUMS_HXX
