/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_BIPVT_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_BIPVT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields
 *  \brief Enumeration of SolarCollectorPerformance:PhotovoltaicThermal:BIPVT's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields, )
#else
class SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields: public ::EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields> {
 public: 
  enum domain 
  {
Name, BoundaryConditionsModelName, AvailabilityScheduleName, EffectivePlenumGapThicknessBehindPVModules, PVCellNormalTransmittanceAbsorptanceProduct, BackingMaterialNormalTransmittanceAbsorptanceProduct, CladdingNormalTransmittanceAbsorptanceProduct, FractionofCollectorGrossAreaCoveredbyPVModule, FractionofPVCellAreatoPVModuleArea, PVModuleTopThermalResistance, PVModuleBottomThermalResistance, PVModuleFrontLongwaveEmissivity, PVModuleBackLongwaveEmissivity, GlassThickness, GlassRefractionIndex, GlassExtinctionCoefficient,   };
  SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields()
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields>(Name) {} 
  SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields(const std::string &t_name) 
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields>(t_name) {} 
  SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields(int t_value) 
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields>::integer_value()); }
   private:
    friend class EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields>;
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
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::Name, "Name", "Name"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::BoundaryConditionsModelName, "BoundaryConditionsModelName", "Boundary Conditions Model Name"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::EffectivePlenumGapThicknessBehindPVModules, "EffectivePlenumGapThicknessBehindPVModules", "Effective Plenum Gap Thickness Behind PV Modules"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVCellNormalTransmittanceAbsorptanceProduct, "PVCellNormalTransmittanceAbsorptanceProduct", "PV Cell Normal Transmittance-Absorptance Product"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::BackingMaterialNormalTransmittanceAbsorptanceProduct, "BackingMaterialNormalTransmittanceAbsorptanceProduct", "Backing Material Normal Transmittance-Absorptance Product"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::CladdingNormalTransmittanceAbsorptanceProduct, "CladdingNormalTransmittanceAbsorptanceProduct", "Cladding Normal Transmittance-Absorptance Product"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofCollectorGrossAreaCoveredbyPVModule, "FractionofCollectorGrossAreaCoveredbyPVModule", "Fraction of Collector Gross Area Covered by PV Module"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofPVCellAreatoPVModuleArea, "FractionofPVCellAreatoPVModuleArea", "Fraction of PV Cell Area to PV Module Area"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleTopThermalResistance, "PVModuleTopThermalResistance", "PV Module Top Thermal Resistance"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBottomThermalResistance, "PVModuleBottomThermalResistance", "PV Module Bottom Thermal Resistance"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleFrontLongwaveEmissivity, "PVModuleFrontLongwaveEmissivity", "PV Module Front Longwave Emissivity"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBackLongwaveEmissivity, "PVModuleBackLongwaveEmissivity", "PV Module Back Longwave Emissivity"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassThickness, "GlassThickness", "Glass Thickness"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassRefractionIndex, "GlassRefractionIndex", "Glass Refraction Index"},
{ SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassExtinctionCoefficient, "GlassExtinctionCoefficient", "Glass Extinction Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields> OptionalSolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_BIPVT_FIELDENUMS_HXX
