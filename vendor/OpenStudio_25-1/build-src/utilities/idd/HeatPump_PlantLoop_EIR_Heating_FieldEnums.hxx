/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_PlantLoop_EIR_HeatingFields
 *  \brief Enumeration of HeatPump:PlantLoop:EIR:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_PlantLoop_EIR_HeatingFields, )
#else
class HeatPump_PlantLoop_EIR_HeatingFields: public ::EnumBase<HeatPump_PlantLoop_EIR_HeatingFields> {
 public: 
  enum domain 
  {
Name, LoadSideInletNodeName, LoadSideOutletNodeName, CondenserType, SourceSideInletNodeName, SourceSideOutletNodeName, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, CompanionHeatPumpName, LoadSideReferenceFlowRate, SourceSideReferenceFlowRate, HeatRecoveryReferenceFlowRate, ReferenceCapacity, ReferenceCoefficientofPerformance, SizingFactor, CapacityModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, HeatingToCoolingCapacitySizingRatio, HeatPumpSizingMethod, ControlType, FlowMode, MinimumPartLoadRatio, MinimumSourceInletTemperature, MaximumSourceInletTemperature, MinimumSupplyWaterTemperatureCurveName, MaximumSupplyWaterTemperatureCurveName, DryOutdoorCorrectionFactorCurveName, MaximumOutdoorDryBulbTemperatureForDefrostOperation, HeatPumpDefrostControl, HeatPumpDefrostTimePeriodFraction, DefrostEnergyInputRatioFunctionofTemperatureCurveName, TimedEmpiricalDefrostFrequencyCurveName, TimedEmpiricalDefrostHeatLoadPenaltyCurveName, TimedEmpiricalDefrostHeatInputEnergyFractionCurveName, MinimumHeatRecoveryOutletTemperature, HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName,   };
  HeatPump_PlantLoop_EIR_HeatingFields()
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(Name) {} 
  HeatPump_PlantLoop_EIR_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(t_name) {} 
  HeatPump_PlantLoop_EIR_HeatingFields(int t_value) 
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_PlantLoop_EIR_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>::integer_value()); }
   private:
    friend class EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>;
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
{ HeatPump_PlantLoop_EIR_HeatingFields::Name, "Name", "Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, "CondenserType", "Condenser Type"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName, "CompanionHeatPumpName", "Companion Heat Pump Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, "LoadSideReferenceFlowRate", "Load Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, "SourceSideReferenceFlowRate", "Source Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, "HeatRecoveryReferenceFlowRate", "Heat Recovery Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CapacityModifierFunctionofTemperatureCurveName, "CapacityModifierFunctionofTemperatureCurveName", "Capacity Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, "ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName", "Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, "HeatingToCoolingCapacitySizingRatio", "Heating To Cooling Capacity Sizing Ratio"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, "HeatPumpSizingMethod", "Heat Pump Sizing Method"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ControlType, "ControlType", "Control Type"},
{ HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, "FlowMode", "Flow Mode"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, "MinimumSourceInletTemperature", "Minimum Source Inlet Temperature"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, "MaximumSourceInletTemperature", "Maximum Source Inlet Temperature"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MinimumSupplyWaterTemperatureCurveName, "MinimumSupplyWaterTemperatureCurveName", "Minimum Supply Water Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MaximumSupplyWaterTemperatureCurveName, "MaximumSupplyWaterTemperatureCurveName", "Maximum Supply Water Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::DryOutdoorCorrectionFactorCurveName, "DryOutdoorCorrectionFactorCurveName", "Dry Outdoor Correction Factor Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, "MaximumOutdoorDryBulbTemperatureForDefrostOperation", "Maximum Outdoor Dry Bulb Temperature For Defrost Operation"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, "HeatPumpDefrostControl", "Heat Pump Defrost Control"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, "HeatPumpDefrostTimePeriodFraction", "Heat Pump Defrost Time Period Fraction"},
{ HeatPump_PlantLoop_EIR_HeatingFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostFrequencyCurveName, "TimedEmpiricalDefrostFrequencyCurveName", "Timed Empirical Defrost Frequency Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatLoadPenaltyCurveName, "TimedEmpiricalDefrostHeatLoadPenaltyCurveName", "Timed Empirical Defrost Heat Load Penalty Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatInputEnergyFractionCurveName, "TimedEmpiricalDefrostHeatInputEnergyFractionCurveName", "Timed Empirical Defrost Heat Input Energy Fraction Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::MinimumHeatRecoveryOutletTemperature, "MinimumHeatRecoveryOutletTemperature", "Minimum Heat Recovery Outlet Temperature"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, "HeatRecoveryCapacityModifierFunctionofTemperatureCurveName", "Heat Recovery Capacity Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Heat Recovery Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_PlantLoop_EIR_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_PlantLoop_EIR_HeatingFields> OptionalHeatPump_PlantLoop_EIR_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
