/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_PERFORMANCE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_PERFORMANCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_CurveFit_PerformanceFields
 *  \brief Enumeration of Coil:Cooling:DX:CurveFit:Performance's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_CurveFit_PerformanceFields, )
#else
class Coil_Cooling_DX_CurveFit_PerformanceFields: public ::EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields> {
 public: 
  enum domain 
  {
Name, CrankcaseHeaterCapacity, CrankcaseHeaterCapacityFunctionofTemperatureCurveName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, UnitInternalStaticAirPressure, CapacityControlMethod, EvaporativeCondenserBasinHeaterCapacity, EvaporativeCondenserBasinHeaterSetpointTemperature, EvaporativeCondenserBasinHeaterOperatingScheduleName, CompressorFuelType, BaseOperatingMode, AlternativeOperatingMode1, AlternativeOperatingMode2,   };
  Coil_Cooling_DX_CurveFit_PerformanceFields()
   : EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields>(Name) {} 
  Coil_Cooling_DX_CurveFit_PerformanceFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields>(t_name) {} 
  Coil_Cooling_DX_CurveFit_PerformanceFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_CurveFit_PerformanceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_CurveFit_PerformanceFields>;
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
{ Coil_Cooling_DX_CurveFit_PerformanceFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, "CrankcaseHeaterCapacityFunctionofTemperatureCurveName", "Crankcase Heater Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::UnitInternalStaticAirPressure, "UnitInternalStaticAirPressure", "Unit Internal Static Air Pressure"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterCapacity, "EvaporativeCondenserBasinHeaterCapacity", "Evaporative Condenser Basin Heater Capacity"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterSetpointTemperature, "EvaporativeCondenserBasinHeaterSetpointTemperature", "Evaporative Condenser Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName, "EvaporativeCondenserBasinHeaterOperatingScheduleName", "Evaporative Condenser Basin Heater Operating Schedule Name"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType, "CompressorFuelType", "Compressor Fuel Type"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::BaseOperatingMode, "BaseOperatingMode", "Base Operating Mode"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode1, "AlternativeOperatingMode1", "Alternative Operating Mode 1"},
{ Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode2, "AlternativeOperatingMode2", "Alternative Operating Mode 2"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_CurveFit_PerformanceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_CurveFit_PerformanceFields> OptionalCoil_Cooling_DX_CurveFit_PerformanceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_PERFORMANCE_FIELDENUMS_HXX
