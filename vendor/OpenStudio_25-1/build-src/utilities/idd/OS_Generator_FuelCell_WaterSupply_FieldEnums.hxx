/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_WATERSUPPLY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_WATERSUPPLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_WaterSupplyFields
 *  \brief Enumeration of OS:Generator:FuelCell:WaterSupply's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_WaterSupplyFields, )
#else
class OS_Generator_FuelCell_WaterSupplyFields: public ::EnumBase<OS_Generator_FuelCell_WaterSupplyFields> {
 public: 
  enum domain 
  {
Handle, Name, ReformerWaterFlowRateFunctionofFuelRateCurveName, ReformerWaterPumpPowerFunctionofFuelRateCurveName, PumpHeatLossFactor, WaterTemperatureModelingMode, WaterTemperatureReferenceNodeName, WaterTemperatureScheduleName,   };
  OS_Generator_FuelCell_WaterSupplyFields()
   : EnumBase<OS_Generator_FuelCell_WaterSupplyFields>(Handle) {} 
  OS_Generator_FuelCell_WaterSupplyFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_WaterSupplyFields>(t_name) {} 
  OS_Generator_FuelCell_WaterSupplyFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_WaterSupplyFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_WaterSupplyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_WaterSupplyFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_WaterSupplyFields>;
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
{ OS_Generator_FuelCell_WaterSupplyFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_WaterSupplyFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_WaterSupplyFields::ReformerWaterFlowRateFunctionofFuelRateCurveName, "ReformerWaterFlowRateFunctionofFuelRateCurveName", "Reformer Water Flow Rate Function of Fuel Rate Curve Name"},
{ OS_Generator_FuelCell_WaterSupplyFields::ReformerWaterPumpPowerFunctionofFuelRateCurveName, "ReformerWaterPumpPowerFunctionofFuelRateCurveName", "Reformer Water Pump Power Function of Fuel Rate Curve Name"},
{ OS_Generator_FuelCell_WaterSupplyFields::PumpHeatLossFactor, "PumpHeatLossFactor", "Pump Heat Loss Factor"},
{ OS_Generator_FuelCell_WaterSupplyFields::WaterTemperatureModelingMode, "WaterTemperatureModelingMode", "Water Temperature Modeling Mode"},
{ OS_Generator_FuelCell_WaterSupplyFields::WaterTemperatureReferenceNodeName, "WaterTemperatureReferenceNodeName", "Water Temperature Reference Node Name"},
{ OS_Generator_FuelCell_WaterSupplyFields::WaterTemperatureScheduleName, "WaterTemperatureScheduleName", "Water Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_WaterSupplyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_WaterSupplyFields> OptionalOS_Generator_FuelCell_WaterSupplyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_WATERSUPPLY_FIELDENUMS_HXX
