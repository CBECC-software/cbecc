/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_BOILER_HOTWATER_FIELDENUMS_HXX
#define UTILITIES_IDD_BOILER_HOTWATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Boiler_HotWaterFields
 *  \brief Enumeration of Boiler:HotWater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Boiler_HotWaterFields, )
#else
class Boiler_HotWaterFields: public ::EnumBase<Boiler_HotWaterFields> {
 public: 
  enum domain 
  {
Name, FuelType, NominalCapacity, NominalThermalEfficiency, EfficiencyCurveTemperatureEvaluationVariable, NormalizedBoilerEfficiencyCurveName, DesignWaterFlowRate, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, BoilerWaterInletNodeName, BoilerWaterOutletNodeName, WaterOutletUpperTemperatureLimit, BoilerFlowMode, OnCycleParasiticElectricLoad, SizingFactor, EndUseSubcategory, OffCycleParasiticFuelLoad,   };
  Boiler_HotWaterFields()
   : EnumBase<Boiler_HotWaterFields>(Name) {} 
  Boiler_HotWaterFields(const std::string &t_name) 
   : EnumBase<Boiler_HotWaterFields>(t_name) {} 
  Boiler_HotWaterFields(int t_value) 
   : EnumBase<Boiler_HotWaterFields>(t_value) {} 
  static std::string enumName() 
  { return "Boiler_HotWaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Boiler_HotWaterFields>::integer_value()); }
   private:
    friend class EnumBase<Boiler_HotWaterFields>;
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
{ Boiler_HotWaterFields::Name, "Name", "Name"},
{ Boiler_HotWaterFields::FuelType, "FuelType", "Fuel Type"},
{ Boiler_HotWaterFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Boiler_HotWaterFields::NominalThermalEfficiency, "NominalThermalEfficiency", "Nominal Thermal Efficiency"},
{ Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable, "EfficiencyCurveTemperatureEvaluationVariable", "Efficiency Curve Temperature Evaluation Variable"},
{ Boiler_HotWaterFields::NormalizedBoilerEfficiencyCurveName, "NormalizedBoilerEfficiencyCurveName", "Normalized Boiler Efficiency Curve Name"},
{ Boiler_HotWaterFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ Boiler_HotWaterFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Boiler_HotWaterFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Boiler_HotWaterFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Boiler_HotWaterFields::BoilerWaterInletNodeName, "BoilerWaterInletNodeName", "Boiler Water Inlet Node Name"},
{ Boiler_HotWaterFields::BoilerWaterOutletNodeName, "BoilerWaterOutletNodeName", "Boiler Water Outlet Node Name"},
{ Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit, "WaterOutletUpperTemperatureLimit", "Water Outlet Upper Temperature Limit"},
{ Boiler_HotWaterFields::BoilerFlowMode, "BoilerFlowMode", "Boiler Flow Mode"},
{ Boiler_HotWaterFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ Boiler_HotWaterFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Boiler_HotWaterFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Boiler_HotWaterFields::OffCycleParasiticFuelLoad, "OffCycleParasiticFuelLoad", "Off Cycle Parasitic Fuel Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const Boiler_HotWaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Boiler_HotWaterFields> OptionalBoiler_HotWaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_BOILER_HOTWATER_FIELDENUMS_HXX
