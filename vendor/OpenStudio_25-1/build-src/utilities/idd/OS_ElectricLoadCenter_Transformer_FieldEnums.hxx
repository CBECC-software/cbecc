/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricLoadCenter_TransformerFields
 *  \brief Enumeration of OS:ElectricLoadCenter:Transformer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricLoadCenter_TransformerFields, )
#else
class OS_ElectricLoadCenter_TransformerFields: public ::EnumBase<OS_ElectricLoadCenter_TransformerFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, TransformerUsage, ZoneName, RadiativeFraction, RatedCapacity, Phase, ConductorMaterial, FullLoadTemperatureRise, FractionofEddyCurrentLosses, PerformanceInputMethod, RatedNoLoadLoss, RatedLoadLoss, NameplateEfficiency, PerUnitLoadforNameplateEfficiency, ReferenceTemperatureforNameplateEfficiency, PerUnitLoadforMaximumEfficiency, ConsiderTransformerLossforUtilityCost,   };
  OS_ElectricLoadCenter_TransformerFields()
   : EnumBase<OS_ElectricLoadCenter_TransformerFields>(Handle) {} 
  OS_ElectricLoadCenter_TransformerFields(const std::string &t_name) 
   : EnumBase<OS_ElectricLoadCenter_TransformerFields>(t_name) {} 
  OS_ElectricLoadCenter_TransformerFields(int t_value) 
   : EnumBase<OS_ElectricLoadCenter_TransformerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricLoadCenter_TransformerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricLoadCenter_TransformerFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricLoadCenter_TransformerFields>;
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
{ OS_ElectricLoadCenter_TransformerFields::Handle, "Handle", "Handle"},
{ OS_ElectricLoadCenter_TransformerFields::Name, "Name", "Name"},
{ OS_ElectricLoadCenter_TransformerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ElectricLoadCenter_TransformerFields::TransformerUsage, "TransformerUsage", "Transformer Usage"},
{ OS_ElectricLoadCenter_TransformerFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_ElectricLoadCenter_TransformerFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ OS_ElectricLoadCenter_TransformerFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ OS_ElectricLoadCenter_TransformerFields::Phase, "Phase", "Phase"},
{ OS_ElectricLoadCenter_TransformerFields::ConductorMaterial, "ConductorMaterial", "Conductor Material"},
{ OS_ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise, "FullLoadTemperatureRise", "Full Load Temperature Rise"},
{ OS_ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses, "FractionofEddyCurrentLosses", "Fraction of Eddy Current Losses"},
{ OS_ElectricLoadCenter_TransformerFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ OS_ElectricLoadCenter_TransformerFields::RatedNoLoadLoss, "RatedNoLoadLoss", "Rated No Load Loss"},
{ OS_ElectricLoadCenter_TransformerFields::RatedLoadLoss, "RatedLoadLoss", "Rated Load Loss"},
{ OS_ElectricLoadCenter_TransformerFields::NameplateEfficiency, "NameplateEfficiency", "Nameplate Efficiency"},
{ OS_ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency, "PerUnitLoadforNameplateEfficiency", "Per Unit Load for Nameplate Efficiency"},
{ OS_ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency, "ReferenceTemperatureforNameplateEfficiency", "Reference Temperature for Nameplate Efficiency"},
{ OS_ElectricLoadCenter_TransformerFields::PerUnitLoadforMaximumEfficiency, "PerUnitLoadforMaximumEfficiency", "Per Unit Load for Maximum Efficiency"},
{ OS_ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost, "ConsiderTransformerLossforUtilityCost", "Consider Transformer Loss for Utility Cost"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricLoadCenter_TransformerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricLoadCenter_TransformerFields> OptionalOS_ElectricLoadCenter_TransformerFields ;
#endif

/** \class OS_ElectricLoadCenter_TransformerExtensibleFields
 *  \brief Enumeration of OS:ElectricLoadCenter:Transformer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ElectricLoadCenter_TransformerExtensibleFields, )
#else
class OS_ElectricLoadCenter_TransformerExtensibleFields: public ::EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields> {
 public: 
  enum domain 
  {
MeterName,   };
  OS_ElectricLoadCenter_TransformerExtensibleFields()
   : EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields>(MeterName) {} 
  OS_ElectricLoadCenter_TransformerExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields>(t_name) {} 
  OS_ElectricLoadCenter_TransformerExtensibleFields(int t_value) 
   : EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricLoadCenter_TransformerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricLoadCenter_TransformerExtensibleFields>;
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
{ OS_ElectricLoadCenter_TransformerExtensibleFields::MeterName, "MeterName", "Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricLoadCenter_TransformerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricLoadCenter_TransformerExtensibleFields> OptionalOS_ElectricLoadCenter_TransformerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX
