/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Chiller_Electric_ReformulatedEIRFields
 *  \brief Enumeration of OS:Chiller:Electric:ReformulatedEIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Chiller_Electric_ReformulatedEIRFields, )
#else
class OS_Chiller_Electric_ReformulatedEIRFields: public ::EnumBase<OS_Chiller_Electric_ReformulatedEIRFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceCapacity, ReferenceCOP, ReferenceLeavingChilledWaterTemperature, ReferenceLeavingCondenserWaterTemperature, ReferenceChilledWaterFlowRate, ReferenceCondenserWaterFlowRate, CoolingCapacityFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, MinimumUnloadingRatio, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, FractionofCompressorElectricConsumptionRejectedbyCondenser, LeavingChilledWaterLowerTemperatureLimit, ChillerFlowMode, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, SizingFactor, CondenserHeatRecoveryRelativeCapacityFraction, HeatRecoveryInletHighTemperatureLimitScheduleName, HeatRecoveryLeavingTemperatureSetpointNodeName, EndUseSubcategory, CondenserFlowControl, CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName, TemperatureDifferenceAcrossCondenserScheduleName, CondenserMinimumFlowFraction, ThermosiphonCapacityFractionCurveName, ThermosiphonMinimumTemperatureDifference,   };
  OS_Chiller_Electric_ReformulatedEIRFields()
   : EnumBase<OS_Chiller_Electric_ReformulatedEIRFields>(Handle) {} 
  OS_Chiller_Electric_ReformulatedEIRFields(const std::string &t_name) 
   : EnumBase<OS_Chiller_Electric_ReformulatedEIRFields>(t_name) {} 
  OS_Chiller_Electric_ReformulatedEIRFields(int t_value) 
   : EnumBase<OS_Chiller_Electric_ReformulatedEIRFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Chiller_Electric_ReformulatedEIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Chiller_Electric_ReformulatedEIRFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Chiller_Electric_ReformulatedEIRFields>;
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
{ OS_Chiller_Electric_ReformulatedEIRFields::Handle, "Handle", "Handle"},
{ OS_Chiller_Electric_ReformulatedEIRFields::Name, "Name", "Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceCOP, "ReferenceCOP", "Reference COP"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, "ReferenceLeavingChilledWaterTemperature", "Reference Leaving Chilled Water Temperature"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature, "ReferenceLeavingCondenserWaterTemperature", "Reference Leaving Condenser Water Temperature"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, "ReferenceChilledWaterFlowRate", "Reference Chilled Water Flow Rate"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, "ReferenceCondenserWaterFlowRate", "Reference Condenser Water Flow Rate"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CoolingCapacityFunctionofTemperatureCurveName, "CoolingCapacityFunctionofTemperatureCurveName", "Cooling Capacity Function of Temperature Curve Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Type"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ OS_Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ OS_Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ OS_Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, "MinimumUnloadingRatio", "Minimum Unloading Ratio"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, "FractionofCompressorElectricConsumptionRejectedbyCondenser", "Fraction of Compressor Electric Consumption Rejected by Condenser"},
{ OS_Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, "LeavingChilledWaterLowerTemperatureLimit", "Leaving Chilled Water Lower Temperature Limit"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ OS_Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ OS_Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ OS_Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, "HeatRecoveryInletHighTemperatureLimitScheduleName", "Heat Recovery Inlet High Temperature Limit Schedule Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, "HeatRecoveryLeavingTemperatureSetpointNodeName", "Heat Recovery Leaving Temperature Setpoint Node Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserFlowControl, "CondenserFlowControl", "Condenser Flow Control"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName, "CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName", "Condenser Loop Flow Rate Fraction Function of Loop Part Load Ratio Curve Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::TemperatureDifferenceAcrossCondenserScheduleName, "TemperatureDifferenceAcrossCondenserScheduleName", "Temperature Difference Across Condenser Schedule Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::CondenserMinimumFlowFraction, "CondenserMinimumFlowFraction", "Condenser Minimum Flow Fraction"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ThermosiphonCapacityFractionCurveName, "ThermosiphonCapacityFractionCurveName", "Thermosiphon Capacity Fraction Curve Name"},
{ OS_Chiller_Electric_ReformulatedEIRFields::ThermosiphonMinimumTemperatureDifference, "ThermosiphonMinimumTemperatureDifference", "Thermosiphon Minimum Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Chiller_Electric_ReformulatedEIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Chiller_Electric_ReformulatedEIRFields> OptionalOS_Chiller_Electric_ReformulatedEIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX
