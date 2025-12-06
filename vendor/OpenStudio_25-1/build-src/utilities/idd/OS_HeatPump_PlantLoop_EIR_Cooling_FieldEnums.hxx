/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatPump_PlantLoop_EIR_CoolingFields
 *  \brief Enumeration of OS:HeatPump:PlantLoop:EIR:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatPump_PlantLoop_EIR_CoolingFields, )
#else
class OS_HeatPump_PlantLoop_EIR_CoolingFields: public ::EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields> {
 public: 
  enum domain 
  {
Handle, Name, LoadSideInletNodeName, LoadSideOutletNodeName, CondenserType, SourceSideInletNodeName, SourceSideOutletNodeName, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, CompanionHeatPumpName, LoadSideReferenceFlowRate, SourceSideReferenceFlowRate, HeatRecoveryReferenceFlowRate, ReferenceCapacity, ReferenceCoefficientofPerformance, SizingFactor, CapacityModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, ControlType, FlowMode, MinimumPartLoadRatio, MinimumSourceInletTemperature, MaximumSourceInletTemperature, MinimumSupplyWaterTemperatureCurveName, MaximumSupplyWaterTemperatureCurveName, MaximumHeatRecoveryOutletTemperature, HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ThermosiphonCapacityFractionCurveName, ThermosiphonMinimumTemperatureDifference,   };
  OS_HeatPump_PlantLoop_EIR_CoolingFields()
   : EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields>(Handle) {} 
  OS_HeatPump_PlantLoop_EIR_CoolingFields(const std::string &t_name) 
   : EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields>(t_name) {} 
  OS_HeatPump_PlantLoop_EIR_CoolingFields(int t_value) 
   : EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatPump_PlantLoop_EIR_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields>::integer_value()); }
   private:
    friend class EnumBase<OS_HeatPump_PlantLoop_EIR_CoolingFields>;
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
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::Handle, "Handle", "Handle"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::Name, "Name", "Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName, "CompanionHeatPumpName", "Companion Heat Pump Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, "LoadSideReferenceFlowRate", "Load Side Reference Flow Rate"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, "SourceSideReferenceFlowRate", "Source Side Reference Flow Rate"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, "HeatRecoveryReferenceFlowRate", "Heat Recovery Reference Flow Rate"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::CapacityModifierFunctionofTemperatureCurveName, "CapacityModifierFunctionofTemperatureCurveName", "Capacity Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, "ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName", "Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ControlType, "ControlType", "Control Type"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, "FlowMode", "Flow Mode"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, "MinimumSourceInletTemperature", "Minimum Source Inlet Temperature"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, "MaximumSourceInletTemperature", "Maximum Source Inlet Temperature"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MinimumSupplyWaterTemperatureCurveName, "MinimumSupplyWaterTemperatureCurveName", "Minimum Supply Water Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MaximumSupplyWaterTemperatureCurveName, "MaximumSupplyWaterTemperatureCurveName", "Maximum Supply Water Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, "MaximumHeatRecoveryOutletTemperature", "Maximum Heat Recovery Outlet Temperature"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, "HeatRecoveryCapacityModifierFunctionofTemperatureCurveName", "Heat Recovery Capacity Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Heat Recovery Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonCapacityFractionCurveName, "ThermosiphonCapacityFractionCurveName", "Thermosiphon Capacity Fraction Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference, "ThermosiphonMinimumTemperatureDifference", "Thermosiphon Minimum Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatPump_PlantLoop_EIR_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatPump_PlantLoop_EIR_CoolingFields> OptionalOS_HeatPump_PlantLoop_EIR_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_COOLING_FIELDENUMS_HXX
