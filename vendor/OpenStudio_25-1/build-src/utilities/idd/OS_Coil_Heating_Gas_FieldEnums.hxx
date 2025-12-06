/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_HEATING_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_GasFields
 *  \brief Enumeration of OS:Coil:Heating:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_GasFields, )
#else
class OS_Coil_Heating_GasFields: public ::EnumBase<OS_Coil_Heating_GasFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, GasBurnerEfficiency, NominalCapacity, AirInletNodeName, AirOutletNodeName, TemperatureSetpointNodeName, OnCycleParasiticElectricLoad, PartLoadFractionCorrelationCurveName, OffCycleParasiticGasLoad, FuelType,   };
  OS_Coil_Heating_GasFields()
   : EnumBase<OS_Coil_Heating_GasFields>(Handle) {} 
  OS_Coil_Heating_GasFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_GasFields>(t_name) {} 
  OS_Coil_Heating_GasFields(int t_value) 
   : EnumBase<OS_Coil_Heating_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_GasFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_GasFields>;
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
{ OS_Coil_Heating_GasFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_GasFields::Name, "Name", "Name"},
{ OS_Coil_Heating_GasFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_Heating_GasFields::GasBurnerEfficiency, "GasBurnerEfficiency", "Gas Burner Efficiency"},
{ OS_Coil_Heating_GasFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ OS_Coil_Heating_GasFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Heating_GasFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Heating_GasFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
{ OS_Coil_Heating_GasFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ OS_Coil_Heating_GasFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_Coil_Heating_GasFields::OffCycleParasiticGasLoad, "OffCycleParasiticGasLoad", "Off Cycle Parasitic Gas Load"},
{ OS_Coil_Heating_GasFields::FuelType, "FuelType", "Fuel Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_GasFields> OptionalOS_Coil_Heating_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_GAS_FIELDENUMS_HXX
