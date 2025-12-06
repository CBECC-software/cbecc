/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_EquationFit_CoolingFields
 *  \brief Enumeration of HeatPump:WaterToWater:EquationFit:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_EquationFit_CoolingFields, )
#else
class HeatPump_WaterToWater_EquationFit_CoolingFields: public ::EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, ReferenceLoadSideFlowRate, ReferenceSourceSideFlowRate, ReferenceCoolingCapacity, ReferenceCoolingPowerConsumption, CoolingCapacityCurveName, CoolingCompressorPowerCurveName, ReferenceCoefficientofPerformance, SizingFactor, CompanionHeatingHeatPumpName,   };
  HeatPump_WaterToWater_EquationFit_CoolingFields()
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(Name) {} 
  HeatPump_WaterToWater_EquationFit_CoolingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(t_name) {} 
  HeatPump_WaterToWater_EquationFit_CoolingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_EquationFit_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>::integer_value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>;
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
{ HeatPump_WaterToWater_EquationFit_CoolingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, "ReferenceLoadSideFlowRate", "Reference Load Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, "ReferenceSourceSideFlowRate", "Reference Source Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, "ReferenceCoolingCapacity", "Reference Cooling Capacity"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, "ReferenceCoolingPowerConsumption", "Reference Cooling Power Consumption"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCurveName, "CoolingCapacityCurveName", "Cooling Capacity Curve Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCurveName, "CoolingCompressorPowerCurveName", "Cooling Compressor Power Curve Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName, "CompanionHeatingHeatPumpName", "Companion Heating Heat Pump Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_EquationFit_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_EquationFit_CoolingFields> OptionalHeatPump_WaterToWater_EquationFit_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
