/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_EquationFit_HeatingFields
 *  \brief Enumeration of HeatPump:WaterToWater:EquationFit:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_EquationFit_HeatingFields, )
#else
class HeatPump_WaterToWater_EquationFit_HeatingFields: public ::EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, ReferenceLoadSideFlowRate, ReferenceSourceSideFlowRate, ReferenceHeatingCapacity, ReferenceHeatingPowerConsumption, HeatingCapacityCurveName, HeatingCompressorPowerCurveName, ReferenceCoefficientofPerformance, SizingFactor, CompanionCoolingHeatPumpName,   };
  HeatPump_WaterToWater_EquationFit_HeatingFields()
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(Name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_EquationFit_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>::integer_value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>;
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
{ HeatPump_WaterToWater_EquationFit_HeatingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, "ReferenceLoadSideFlowRate", "Reference Load Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, "ReferenceSourceSideFlowRate", "Reference Source Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, "ReferenceHeatingCapacity", "Reference Heating Capacity"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, "ReferenceHeatingPowerConsumption", "Reference Heating Power Consumption"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCurveName, "HeatingCapacityCurveName", "Heating Capacity Curve Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCurveName, "HeatingCompressorPowerCurveName", "Heating Compressor Power Curve Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName, "CompanionCoolingHeatPumpName", "Companion Cooling Heat Pump Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_EquationFit_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_EquationFit_HeatingFields> OptionalHeatPump_WaterToWater_EquationFit_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
