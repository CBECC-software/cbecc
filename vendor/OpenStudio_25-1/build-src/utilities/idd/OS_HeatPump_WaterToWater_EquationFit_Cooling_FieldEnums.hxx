/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatPump_WaterToWater_EquationFit_CoolingFields
 *  \brief Enumeration of OS:HeatPump:WaterToWater:EquationFit:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatPump_WaterToWater_EquationFit_CoolingFields, )
#else
class OS_HeatPump_WaterToWater_EquationFit_CoolingFields: public ::EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields> {
 public: 
  enum domain 
  {
Handle, Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, ReferenceLoadSideFlowRate, ReferenceSourceSideFlowRate, ReferenceCoolingCapacity, ReferenceCoolingPowerConsumption, CoolingCapacityCurveName, CoolingCompressorPowerCurveName, ReferenceCoefficientofPerformance, SizingFactor, CompanionHeatingHeatPumpName,   };
  OS_HeatPump_WaterToWater_EquationFit_CoolingFields()
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields>(Handle) {} 
  OS_HeatPump_WaterToWater_EquationFit_CoolingFields(const std::string &t_name) 
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields>(t_name) {} 
  OS_HeatPump_WaterToWater_EquationFit_CoolingFields(int t_value) 
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatPump_WaterToWater_EquationFit_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields>::integer_value()); }
   private:
    friend class EnumBase<OS_HeatPump_WaterToWater_EquationFit_CoolingFields>;
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
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::Handle, "Handle", "Handle"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::Name, "Name", "Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, "ReferenceLoadSideFlowRate", "Reference Load Side Flow Rate"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, "ReferenceSourceSideFlowRate", "Reference Source Side Flow Rate"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, "ReferenceCoolingCapacity", "Reference Cooling Capacity"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, "ReferenceCoolingPowerConsumption", "Reference Cooling Power Consumption"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCurveName, "CoolingCapacityCurveName", "Cooling Capacity Curve Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCurveName, "CoolingCompressorPowerCurveName", "Cooling Compressor Power Curve Name"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName, "CompanionHeatingHeatPumpName", "Companion Heating Heat Pump Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatPump_WaterToWater_EquationFit_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatPump_WaterToWater_EquationFit_CoolingFields> OptionalOS_HeatPump_WaterToWater_EquationFit_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
