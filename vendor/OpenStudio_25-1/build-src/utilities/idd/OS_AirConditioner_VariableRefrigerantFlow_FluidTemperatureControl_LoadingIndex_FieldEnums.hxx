/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_LOADINGINDEX_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_LOADINGINDEX_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields
 *  \brief Enumeration of OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields, )
#else
class OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields: public ::EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields> {
 public: 
  enum domain 
  {
Handle, Name, CompressorSpeed, EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, CompressorPowerMultiplierFunctionofTemperatureCurveName,   };
  OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields()
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields>(Handle) {} 
  OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields(const std::string &t_name) 
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields>(t_name) {} 
  OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields(int t_value) 
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields>;
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
{ OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields::Handle, "Handle", "Handle"},
{ OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields::Name, "Name", "Name"},
{ OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields::CompressorSpeed, "CompressorSpeed", "Compressor Speed"},
{ OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields::EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields::CompressorPowerMultiplierFunctionofTemperatureCurveName, "CompressorPowerMultiplierFunctionofTemperatureCurveName", "Compressor Power Multiplier Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields> OptionalOS_AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_LoadingIndexFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_LOADINGINDEX_FIELDENUMS_HXX
