/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MaterialProperty_PhaseChangeFields
 *  \brief Enumeration of OS:MaterialProperty:PhaseChange's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialProperty_PhaseChangeFields, )
#else
class OS_MaterialProperty_PhaseChangeFields: public ::EnumBase<OS_MaterialProperty_PhaseChangeFields> {
 public: 
  enum domain 
  {
Handle, MaterialName, TemperatureCoefficientforThermalConductivity,   };
  OS_MaterialProperty_PhaseChangeFields()
   : EnumBase<OS_MaterialProperty_PhaseChangeFields>(Handle) {} 
  OS_MaterialProperty_PhaseChangeFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_PhaseChangeFields>(t_name) {} 
  OS_MaterialProperty_PhaseChangeFields(int t_value) 
   : EnumBase<OS_MaterialProperty_PhaseChangeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_PhaseChangeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_PhaseChangeFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_PhaseChangeFields>;
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
{ OS_MaterialProperty_PhaseChangeFields::Handle, "Handle", "Handle"},
{ OS_MaterialProperty_PhaseChangeFields::MaterialName, "MaterialName", "Material Name"},
{ OS_MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity, "TemperatureCoefficientforThermalConductivity", "Temperature Coefficient for Thermal Conductivity"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_PhaseChangeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_PhaseChangeFields> OptionalOS_MaterialProperty_PhaseChangeFields ;
#endif

/** \class OS_MaterialProperty_PhaseChangeExtensibleFields
 *  \brief Enumeration of OS:MaterialProperty:PhaseChange's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialProperty_PhaseChangeExtensibleFields, )
#else
class OS_MaterialProperty_PhaseChangeExtensibleFields: public ::EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields> {
 public: 
  enum domain 
  {
Temperature, Enthalpy,   };
  OS_MaterialProperty_PhaseChangeExtensibleFields()
   : EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields>(Temperature) {} 
  OS_MaterialProperty_PhaseChangeExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields>(t_name) {} 
  OS_MaterialProperty_PhaseChangeExtensibleFields(int t_value) 
   : EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_PhaseChangeExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_PhaseChangeExtensibleFields>;
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
{ OS_MaterialProperty_PhaseChangeExtensibleFields::Temperature, "Temperature", "Temperature"},
{ OS_MaterialProperty_PhaseChangeExtensibleFields::Enthalpy, "Enthalpy", "Enthalpy"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_PhaseChangeExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_PhaseChangeExtensibleFields> OptionalOS_MaterialProperty_PhaseChangeExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX
