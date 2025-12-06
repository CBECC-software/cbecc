/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_DEFINITION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_DEFINITION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricEquipment_ITE_AirCooled_DefinitionFields
 *  \brief Enumeration of OS:ElectricEquipment:ITE:AirCooled:Definition's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricEquipment_ITE_AirCooled_DefinitionFields, )
#else
class OS_ElectricEquipment_ITE_AirCooled_DefinitionFields: public ::EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields> {
 public: 
  enum domain 
  {
Handle, Name, AirFlowCalculationMethod, DesignPowerInputCalculationMethod, WattsperUnit, WattsperSpaceFloorArea, CPUPowerInputFunctionofLoadingandAirTemperatureCurveName, DesignFanPowerInputFraction, DesignFanAirFlowRateperPowerInput, AirFlowFunctionofLoadingandAirTemperatureCurveName, FanPowerInputFunctionofFlowCurveName, DesignEnteringAirTemperature, EnvironmentalClass, AirInletConnectionType, DesignRecirculationFraction, RecirculationFunctionofLoadingandSupplyTemperatureCurveName, DesignElectricPowerSupplyEfficiency, ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName, FractionofElectricPowerSupplyLossestoZone, SupplyTemperatureDifference, SupplyTemperatureDifferenceSchedule, ReturnTemperatureDifference, ReturnTemperatureDifferenceSchedule,   };
  OS_ElectricEquipment_ITE_AirCooled_DefinitionFields()
   : EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields>(Handle) {} 
  OS_ElectricEquipment_ITE_AirCooled_DefinitionFields(const std::string &t_name) 
   : EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields>(t_name) {} 
  OS_ElectricEquipment_ITE_AirCooled_DefinitionFields(int t_value) 
   : EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricEquipment_ITE_AirCooled_DefinitionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields>;
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
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::Handle, "Handle", "Handle"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::Name, "Name", "Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::AirFlowCalculationMethod, "AirFlowCalculationMethod", "Air Flow Calculation Method"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignPowerInputCalculationMethod, "DesignPowerInputCalculationMethod", "Design Power Input Calculation Method"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::WattsperUnit, "WattsperUnit", "Watts per Unit"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::WattsperSpaceFloorArea, "WattsperSpaceFloorArea", "Watts per Space Floor Area"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::CPUPowerInputFunctionofLoadingandAirTemperatureCurveName, "CPUPowerInputFunctionofLoadingandAirTemperatureCurveName", "CPU Power Input Function of Loading and Air Temperature Curve Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignFanPowerInputFraction, "DesignFanPowerInputFraction", "Design Fan Power Input Fraction"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignFanAirFlowRateperPowerInput, "DesignFanAirFlowRateperPowerInput", "Design Fan Air Flow Rate per Power Input"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::AirFlowFunctionofLoadingandAirTemperatureCurveName, "AirFlowFunctionofLoadingandAirTemperatureCurveName", "Air Flow Function of Loading and Air Temperature Curve Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::FanPowerInputFunctionofFlowCurveName, "FanPowerInputFunctionofFlowCurveName", "Fan Power Input Function of Flow Curve Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::EnvironmentalClass, "EnvironmentalClass", "Environmental Class"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::AirInletConnectionType, "AirInletConnectionType", "Air Inlet Connection Type"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignRecirculationFraction, "DesignRecirculationFraction", "Design Recirculation Fraction"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::RecirculationFunctionofLoadingandSupplyTemperatureCurveName, "RecirculationFunctionofLoadingandSupplyTemperatureCurveName", "Recirculation Function of Loading and Supply Temperature Curve Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::DesignElectricPowerSupplyEfficiency, "DesignElectricPowerSupplyEfficiency", "Design Electric Power Supply Efficiency"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName, "ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName", "Electric Power Supply Efficiency Function of Part Load Ratio Curve Name"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::FractionofElectricPowerSupplyLossestoZone, "FractionofElectricPowerSupplyLossestoZone", "Fraction of Electric Power Supply Losses to Zone"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::SupplyTemperatureDifference, "SupplyTemperatureDifference", "Supply Temperature Difference"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::SupplyTemperatureDifferenceSchedule, "SupplyTemperatureDifferenceSchedule", "Supply Temperature Difference Schedule"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::ReturnTemperatureDifference, "ReturnTemperatureDifference", "Return Temperature Difference"},
{ OS_ElectricEquipment_ITE_AirCooled_DefinitionFields::ReturnTemperatureDifferenceSchedule, "ReturnTemperatureDifferenceSchedule", "Return Temperature Difference Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricEquipment_ITE_AirCooled_DefinitionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricEquipment_ITE_AirCooled_DefinitionFields> OptionalOS_ElectricEquipment_ITE_AirCooled_DefinitionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICEQUIPMENT_ITE_AIRCOOLED_DEFINITION_FIELDENUMS_HXX
