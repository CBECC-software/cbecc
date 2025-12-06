/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_PlantLoop_EIR_CoolingFields
 *  \brief Enumeration of HeatPump:PlantLoop:EIR:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_PlantLoop_EIR_CoolingFields, )
#else
class HeatPump_PlantLoop_EIR_CoolingFields: public ::EnumBase<HeatPump_PlantLoop_EIR_CoolingFields> {
 public: 
  enum domain 
  {
Name, LoadSideInletNodeName, LoadSideOutletNodeName, CondenserType, SourceSideInletNodeName, SourceSideOutletNodeName, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, CompanionHeatPumpName, LoadSideReferenceFlowRate, SourceSideReferenceFlowRate, HeatRecoveryReferenceFlowRate, ReferenceCapacity, ReferenceCoefficientofPerformance, SizingFactor, CapacityModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, ControlType, FlowMode, MinimumPartLoadRatio, MinimumSourceInletTemperature, MaximumSourceInletTemperature, MinimumSupplyWaterTemperatureCurveName, MaximumSupplyWaterTemperatureCurveName, MaximumHeatRecoveryOutletTemperature, HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ThermosiphonCapacityFractionCurveName, ThermosiphonMinimumTemperatureDifference,   };
  HeatPump_PlantLoop_EIR_CoolingFields()
   : EnumBase<HeatPump_PlantLoop_EIR_CoolingFields>(Name) {} 
  HeatPump_PlantLoop_EIR_CoolingFields(const std::string &t_name) 
   : EnumBase<HeatPump_PlantLoop_EIR_CoolingFields>(t_name) {} 
  HeatPump_PlantLoop_EIR_CoolingFields(int t_value) 
   : EnumBase<HeatPump_PlantLoop_EIR_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_PlantLoop_EIR_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_PlantLoop_EIR_CoolingFields>::integer_value()); }
   private:
    friend class EnumBase<HeatPump_PlantLoop_EIR_CoolingFields>;
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
{ HeatPump_PlantLoop_EIR_CoolingFields::Name, "Name", "Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, "CondenserType", "Condenser Type"},
{ HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName, "CompanionHeatPumpName", "Companion Heat Pump Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, "LoadSideReferenceFlowRate", "Load Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, "SourceSideReferenceFlowRate", "Source Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, "HeatRecoveryReferenceFlowRate", "Heat Recovery Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_PlantLoop_EIR_CoolingFields::CapacityModifierFunctionofTemperatureCurveName, "CapacityModifierFunctionofTemperatureCurveName", "Capacity Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, "ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName", "Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ControlType, "ControlType", "Control Type"},
{ HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, "FlowMode", "Flow Mode"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, "MinimumSourceInletTemperature", "Minimum Source Inlet Temperature"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, "MaximumSourceInletTemperature", "Maximum Source Inlet Temperature"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MinimumSupplyWaterTemperatureCurveName, "MinimumSupplyWaterTemperatureCurveName", "Minimum Supply Water Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MaximumSupplyWaterTemperatureCurveName, "MaximumSupplyWaterTemperatureCurveName", "Maximum Supply Water Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, "MaximumHeatRecoveryOutletTemperature", "Maximum Heat Recovery Outlet Temperature"},
{ HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, "HeatRecoveryCapacityModifierFunctionofTemperatureCurveName", "Heat Recovery Capacity Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Heat Recovery Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonCapacityFractionCurveName, "ThermosiphonCapacityFractionCurveName", "Thermosiphon Capacity Fraction Curve Name"},
{ HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference, "ThermosiphonMinimumTemperatureDifference", "Thermosiphon Minimum Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_PlantLoop_EIR_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_PlantLoop_EIR_CoolingFields> OptionalHeatPump_PlantLoop_EIR_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX
