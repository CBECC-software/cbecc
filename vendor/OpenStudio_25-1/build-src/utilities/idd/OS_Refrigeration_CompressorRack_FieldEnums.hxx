/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_CompressorRackFields
 *  \brief Enumeration of OS:Refrigeration:CompressorRack's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_CompressorRackFields, )
#else
class OS_Refrigeration_CompressorRackFields: public ::EnumBase<OS_Refrigeration_CompressorRackFields> {
 public: 
  enum domain 
  {
Handle, Name, HeatRejectionLocation, DesignCompressorRackCOP, CompressorRackCOPFunctionofTemperatureCurveName, DesignCondenserFanPower, CondenserFanPowerFunctionofTemperatureCurveName, CondenserType, WaterCooledCondenserInletNodeName, WaterCooledCondenserOutletNodeName, WaterCooledLoopFlowType, WaterCooledCondenserOutletTemperatureScheduleName, WaterCooledCondenserDesignFlowRate, WaterCooledCondenserMaximumFlowRate, WaterCooledCondenserMaximumWaterOutletTemperature, WaterCooledCondenserMinimumWaterInletTemperature, EvaporativeCondenserAvailabilityScheduleName, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, BasinHeaterCapacity, BasinHeaterSetpointTemperature, DesignEvaporativeCondenserWaterPumpPower, EvaporativeWaterSupplyTankName, CondenserAirInletNodeName, EndUseSubcategory, RefrigeratedCaseAndWalkInListName, HeatRejectionZoneName,   };
  OS_Refrigeration_CompressorRackFields()
   : EnumBase<OS_Refrigeration_CompressorRackFields>(Handle) {} 
  OS_Refrigeration_CompressorRackFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_CompressorRackFields>(t_name) {} 
  OS_Refrigeration_CompressorRackFields(int t_value) 
   : EnumBase<OS_Refrigeration_CompressorRackFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_CompressorRackFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_CompressorRackFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Refrigeration_CompressorRackFields>;
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
{ OS_Refrigeration_CompressorRackFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_CompressorRackFields::Name, "Name", "Name"},
{ OS_Refrigeration_CompressorRackFields::HeatRejectionLocation, "HeatRejectionLocation", "Heat Rejection Location"},
{ OS_Refrigeration_CompressorRackFields::DesignCompressorRackCOP, "DesignCompressorRackCOP", "Design Compressor Rack COP"},
{ OS_Refrigeration_CompressorRackFields::CompressorRackCOPFunctionofTemperatureCurveName, "CompressorRackCOPFunctionofTemperatureCurveName", "Compressor Rack COP Function of Temperature Curve Name"},
{ OS_Refrigeration_CompressorRackFields::DesignCondenserFanPower, "DesignCondenserFanPower", "Design Condenser Fan Power"},
{ OS_Refrigeration_CompressorRackFields::CondenserFanPowerFunctionofTemperatureCurveName, "CondenserFanPowerFunctionofTemperatureCurveName", "Condenser Fan Power Function of Temperature Curve Name"},
{ OS_Refrigeration_CompressorRackFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName, "WaterCooledCondenserInletNodeName", "Water-Cooled Condenser Inlet Node Name"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName, "WaterCooledCondenserOutletNodeName", "Water-Cooled Condenser Outlet Node Name"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, "WaterCooledLoopFlowType", "Water-Cooled Loop Flow Type"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserOutletTemperatureScheduleName, "WaterCooledCondenserOutletTemperatureScheduleName", "Water-Cooled Condenser Outlet Temperature Schedule Name"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, "WaterCooledCondenserDesignFlowRate", "Water-Cooled Condenser Design Flow Rate"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, "WaterCooledCondenserMaximumFlowRate", "Water-Cooled Condenser Maximum Flow Rate"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature, "WaterCooledCondenserMaximumWaterOutletTemperature", "Water-Cooled Condenser Maximum Water Outlet Temperature"},
{ OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature, "WaterCooledCondenserMinimumWaterInletTemperature", "Water-Cooled Condenser Minimum Water Inlet Temperature"},
{ OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAvailabilityScheduleName, "EvaporativeCondenserAvailabilityScheduleName", "Evaporative Condenser Availability Schedule Name"},
{ OS_Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ OS_Refrigeration_CompressorRackFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, "DesignEvaporativeCondenserWaterPumpPower", "Design Evaporative Condenser Water Pump Power"},
{ OS_Refrigeration_CompressorRackFields::EvaporativeWaterSupplyTankName, "EvaporativeWaterSupplyTankName", "Evaporative Water Supply Tank Name"},
{ OS_Refrigeration_CompressorRackFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ OS_Refrigeration_CompressorRackFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_Refrigeration_CompressorRackFields::RefrigeratedCaseAndWalkInListName, "RefrigeratedCaseAndWalkInListName", "Refrigerated CaseAndWalkInList Name"},
{ OS_Refrigeration_CompressorRackFields::HeatRejectionZoneName, "HeatRejectionZoneName", "Heat Rejection Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_CompressorRackFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_CompressorRackFields> OptionalOS_Refrigeration_CompressorRackFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX
