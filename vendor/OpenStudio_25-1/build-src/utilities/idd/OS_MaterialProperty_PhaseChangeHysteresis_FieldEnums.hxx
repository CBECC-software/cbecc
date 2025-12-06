/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MaterialProperty_PhaseChangeHysteresisFields
 *  \brief Enumeration of OS:MaterialProperty:PhaseChangeHysteresis's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialProperty_PhaseChangeHysteresisFields, )
#else
class OS_MaterialProperty_PhaseChangeHysteresisFields: public ::EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields> {
 public: 
  enum domain 
  {
Handle, MaterialName, LatentHeatduringtheEntirePhaseChangeProcess, LiquidStateThermalConductivity, LiquidStateDensity, LiquidStateSpecificHeat, HighTemperatureDifferenceofMeltingCurve, PeakMeltingTemperature, LowTemperatureDifferenceofMeltingCurve, SolidStateThermalConductivity, SolidStateDensity, SolidStateSpecificHeat, HighTemperatureDifferenceofFreezingCurve, PeakFreezingTemperature, LowTemperatureDifferenceofFreezingCurve,   };
  OS_MaterialProperty_PhaseChangeHysteresisFields()
   : EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields>(Handle) {} 
  OS_MaterialProperty_PhaseChangeHysteresisFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields>(t_name) {} 
  OS_MaterialProperty_PhaseChangeHysteresisFields(int t_value) 
   : EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_PhaseChangeHysteresisFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_PhaseChangeHysteresisFields>;
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
{ OS_MaterialProperty_PhaseChangeHysteresisFields::Handle, "Handle", "Handle"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::MaterialName, "MaterialName", "Material Name"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LatentHeatduringtheEntirePhaseChangeProcess, "LatentHeatduringtheEntirePhaseChangeProcess", "Latent Heat during the Entire Phase Change Process"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LiquidStateThermalConductivity, "LiquidStateThermalConductivity", "Liquid State Thermal Conductivity"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LiquidStateDensity, "LiquidStateDensity", "Liquid State Density"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LiquidStateSpecificHeat, "LiquidStateSpecificHeat", "Liquid State Specific Heat"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofMeltingCurve, "HighTemperatureDifferenceofMeltingCurve", "High Temperature Difference of Melting Curve"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::PeakMeltingTemperature, "PeakMeltingTemperature", "Peak Melting Temperature"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofMeltingCurve, "LowTemperatureDifferenceofMeltingCurve", "Low Temperature Difference of Melting Curve"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::SolidStateThermalConductivity, "SolidStateThermalConductivity", "Solid State Thermal Conductivity"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::SolidStateDensity, "SolidStateDensity", "Solid State Density"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::SolidStateSpecificHeat, "SolidStateSpecificHeat", "Solid State Specific Heat"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofFreezingCurve, "HighTemperatureDifferenceofFreezingCurve", "High Temperature Difference of Freezing Curve"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::PeakFreezingTemperature, "PeakFreezingTemperature", "Peak Freezing Temperature"},
{ OS_MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofFreezingCurve, "LowTemperatureDifferenceofFreezingCurve", "Low Temperature Difference of Freezing Curve"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_PhaseChangeHysteresisFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_PhaseChangeHysteresisFields> OptionalOS_MaterialProperty_PhaseChangeHysteresisFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX
