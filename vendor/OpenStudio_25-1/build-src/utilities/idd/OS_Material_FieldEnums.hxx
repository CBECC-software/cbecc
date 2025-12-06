/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIAL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MaterialFields
 *  \brief Enumeration of OS:Material's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialFields, )
#else
class OS_MaterialFields: public ::EnumBase<OS_MaterialFields> {
 public: 
  enum domain 
  {
Handle, Name, Roughness, Thickness, Conductivity, Density, SpecificHeat, ThermalAbsorptance, SolarAbsorptance, VisibleAbsorptance,   };
  OS_MaterialFields()
   : EnumBase<OS_MaterialFields>(Handle) {} 
  OS_MaterialFields(const std::string &t_name) 
   : EnumBase<OS_MaterialFields>(t_name) {} 
  OS_MaterialFields(int t_value) 
   : EnumBase<OS_MaterialFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialFields>;
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
{ OS_MaterialFields::Handle, "Handle", "Handle"},
{ OS_MaterialFields::Name, "Name", "Name"},
{ OS_MaterialFields::Roughness, "Roughness", "Roughness"},
{ OS_MaterialFields::Thickness, "Thickness", "Thickness"},
{ OS_MaterialFields::Conductivity, "Conductivity", "Conductivity"},
{ OS_MaterialFields::Density, "Density", "Density"},
{ OS_MaterialFields::SpecificHeat, "SpecificHeat", "Specific Heat"},
{ OS_MaterialFields::ThermalAbsorptance, "ThermalAbsorptance", "Thermal Absorptance"},
{ OS_MaterialFields::SolarAbsorptance, "SolarAbsorptance", "Solar Absorptance"},
{ OS_MaterialFields::VisibleAbsorptance, "VisibleAbsorptance", "Visible Absorptance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialFields> OptionalOS_MaterialFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIAL_FIELDENUMS_HXX
