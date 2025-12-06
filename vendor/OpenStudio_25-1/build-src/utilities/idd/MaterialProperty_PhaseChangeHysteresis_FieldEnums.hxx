/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_PhaseChangeHysteresisFields
 *  \brief Enumeration of MaterialProperty:PhaseChangeHysteresis's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_PhaseChangeHysteresisFields, )
#else
class MaterialProperty_PhaseChangeHysteresisFields: public ::EnumBase<MaterialProperty_PhaseChangeHysteresisFields> {
 public: 
  enum domain 
  {
Name, LatentHeatduringtheEntirePhaseChangeProcess, LiquidStateThermalConductivity, LiquidStateDensity, LiquidStateSpecificHeat, HighTemperatureDifferenceofMeltingCurve, PeakMeltingTemperature, LowTemperatureDifferenceofMeltingCurve, SolidStateThermalConductivity, SolidStateDensity, SolidStateSpecificHeat, HighTemperatureDifferenceofFreezingCurve, PeakFreezingTemperature, LowTemperatureDifferenceofFreezingCurve,   };
  MaterialProperty_PhaseChangeHysteresisFields()
   : EnumBase<MaterialProperty_PhaseChangeHysteresisFields>(Name) {} 
  MaterialProperty_PhaseChangeHysteresisFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_PhaseChangeHysteresisFields>(t_name) {} 
  MaterialProperty_PhaseChangeHysteresisFields(int t_value) 
   : EnumBase<MaterialProperty_PhaseChangeHysteresisFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_PhaseChangeHysteresisFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_PhaseChangeHysteresisFields>::integer_value()); }
   private:
    friend class EnumBase<MaterialProperty_PhaseChangeHysteresisFields>;
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
{ MaterialProperty_PhaseChangeHysteresisFields::Name, "Name", "Name"},
{ MaterialProperty_PhaseChangeHysteresisFields::LatentHeatduringtheEntirePhaseChangeProcess, "LatentHeatduringtheEntirePhaseChangeProcess", "Latent Heat during the Entire Phase Change Process"},
{ MaterialProperty_PhaseChangeHysteresisFields::LiquidStateThermalConductivity, "LiquidStateThermalConductivity", "Liquid State Thermal Conductivity"},
{ MaterialProperty_PhaseChangeHysteresisFields::LiquidStateDensity, "LiquidStateDensity", "Liquid State Density"},
{ MaterialProperty_PhaseChangeHysteresisFields::LiquidStateSpecificHeat, "LiquidStateSpecificHeat", "Liquid State Specific Heat"},
{ MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofMeltingCurve, "HighTemperatureDifferenceofMeltingCurve", "High Temperature Difference of Melting Curve"},
{ MaterialProperty_PhaseChangeHysteresisFields::PeakMeltingTemperature, "PeakMeltingTemperature", "Peak Melting Temperature"},
{ MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofMeltingCurve, "LowTemperatureDifferenceofMeltingCurve", "Low Temperature Difference of Melting Curve"},
{ MaterialProperty_PhaseChangeHysteresisFields::SolidStateThermalConductivity, "SolidStateThermalConductivity", "Solid State Thermal Conductivity"},
{ MaterialProperty_PhaseChangeHysteresisFields::SolidStateDensity, "SolidStateDensity", "Solid State Density"},
{ MaterialProperty_PhaseChangeHysteresisFields::SolidStateSpecificHeat, "SolidStateSpecificHeat", "Solid State Specific Heat"},
{ MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofFreezingCurve, "HighTemperatureDifferenceofFreezingCurve", "High Temperature Difference of Freezing Curve"},
{ MaterialProperty_PhaseChangeHysteresisFields::PeakFreezingTemperature, "PeakFreezingTemperature", "Peak Freezing Temperature"},
{ MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofFreezingCurve, "LowTemperatureDifferenceofFreezingCurve", "Low Temperature Difference of Freezing Curve"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_PhaseChangeHysteresisFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_PhaseChangeHysteresisFields> OptionalMaterialProperty_PhaseChangeHysteresisFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGEHYSTERESIS_FIELDENUMS_HXX
