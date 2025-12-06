/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_Electric_EIRFields
 *  \brief Enumeration of Chiller:Electric:EIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_Electric_EIRFields, )
#else
class Chiller_Electric_EIRFields: public ::EnumBase<Chiller_Electric_EIRFields> {
 public: 
  enum domain 
  {
Name, ReferenceCapacity, ReferenceCOP, ReferenceLeavingChilledWaterTemperature, ReferenceEnteringCondenserFluidTemperature, ReferenceChilledWaterFlowRate, ReferenceCondenserFluidFlowRate, CoolingCapacityFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, MinimumUnloadingRatio, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, CondenserType, CondenserFanPowerRatio, FractionofCompressorElectricConsumptionRejectedbyCondenser, LeavingChilledWaterLowerTemperatureLimit, ChillerFlowMode, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, CondenserHeatRecoveryRelativeCapacityFraction, HeatRecoveryInletHighTemperatureLimitScheduleName, HeatRecoveryLeavingTemperatureSetpointNodeName, EndUseSubcategory, CondenserFlowControl, CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName, TemperatureDifferenceAcrossCondenserScheduleName, CondenserMinimumFlowFraction, ThermosiphonCapacityFractionCurveName, ThermosiphonMinimumTemperatureDifference,   };
  Chiller_Electric_EIRFields()
   : EnumBase<Chiller_Electric_EIRFields>(Name) {} 
  Chiller_Electric_EIRFields(const std::string &t_name) 
   : EnumBase<Chiller_Electric_EIRFields>(t_name) {} 
  Chiller_Electric_EIRFields(int t_value) 
   : EnumBase<Chiller_Electric_EIRFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_Electric_EIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_Electric_EIRFields>::integer_value()); }
   private:
    friend class EnumBase<Chiller_Electric_EIRFields>;
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
{ Chiller_Electric_EIRFields::Name, "Name", "Name"},
{ Chiller_Electric_EIRFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ Chiller_Electric_EIRFields::ReferenceCOP, "ReferenceCOP", "Reference COP"},
{ Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature, "ReferenceLeavingChilledWaterTemperature", "Reference Leaving Chilled Water Temperature"},
{ Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature, "ReferenceEnteringCondenserFluidTemperature", "Reference Entering Condenser Fluid Temperature"},
{ Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, "ReferenceChilledWaterFlowRate", "Reference Chilled Water Flow Rate"},
{ Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, "ReferenceCondenserFluidFlowRate", "Reference Condenser Fluid Flow Rate"},
{ Chiller_Electric_EIRFields::CoolingCapacityFunctionofTemperatureCurveName, "CoolingCapacityFunctionofTemperatureCurveName", "Cooling Capacity Function of Temperature Curve Name"},
{ Chiller_Electric_EIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ Chiller_Electric_EIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ Chiller_Electric_EIRFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_Electric_EIRFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_Electric_EIRFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_Electric_EIRFields::MinimumUnloadingRatio, "MinimumUnloadingRatio", "Minimum Unloading Ratio"},
{ Chiller_Electric_EIRFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_Electric_EIRFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_Electric_EIRFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_Electric_EIRFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_Electric_EIRFields::CondenserType, "CondenserType", "Condenser Type"},
{ Chiller_Electric_EIRFields::CondenserFanPowerRatio, "CondenserFanPowerRatio", "Condenser Fan Power Ratio"},
{ Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, "FractionofCompressorElectricConsumptionRejectedbyCondenser", "Fraction of Compressor Electric Consumption Rejected by Condenser"},
{ Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit, "LeavingChilledWaterLowerTemperatureLimit", "Leaving Chilled Water Lower Temperature Limit"},
{ Chiller_Electric_EIRFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Chiller_Electric_EIRFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_Electric_EIRFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_Electric_EIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_Electric_EIRFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Chiller_Electric_EIRFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Chiller_Electric_EIRFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ Chiller_Electric_EIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, "HeatRecoveryInletHighTemperatureLimitScheduleName", "Heat Recovery Inlet High Temperature Limit Schedule Name"},
{ Chiller_Electric_EIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, "HeatRecoveryLeavingTemperatureSetpointNodeName", "Heat Recovery Leaving Temperature Setpoint Node Name"},
{ Chiller_Electric_EIRFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Chiller_Electric_EIRFields::CondenserFlowControl, "CondenserFlowControl", "Condenser Flow Control"},
{ Chiller_Electric_EIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName, "CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName", "Condenser Loop Flow Rate Fraction Function of Loop Part Load Ratio Curve Name"},
{ Chiller_Electric_EIRFields::TemperatureDifferenceAcrossCondenserScheduleName, "TemperatureDifferenceAcrossCondenserScheduleName", "Temperature Difference Across Condenser Schedule Name"},
{ Chiller_Electric_EIRFields::CondenserMinimumFlowFraction, "CondenserMinimumFlowFraction", "Condenser Minimum Flow Fraction"},
{ Chiller_Electric_EIRFields::ThermosiphonCapacityFractionCurveName, "ThermosiphonCapacityFractionCurveName", "Thermosiphon Capacity Fraction Curve Name"},
{ Chiller_Electric_EIRFields::ThermosiphonMinimumTemperatureDifference, "ThermosiphonMinimumTemperatureDifference", "Thermosiphon Minimum Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_Electric_EIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_Electric_EIRFields> OptionalChiller_Electric_EIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX
