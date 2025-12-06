/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ThermalStorage_Ice_DetailedFields
 *  \brief Enumeration of ThermalStorage:Ice:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ThermalStorage_Ice_DetailedFields, )
#else
class ThermalStorage_Ice_DetailedFields: public ::EnumBase<ThermalStorage_Ice_DetailedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, Capacity, InletNodeName, OutletNodeName, DischargingCurveVariableSpecifications, DischargingCurveName, ChargingCurveVariableSpecifications, ChargingCurveName, TimestepoftheCurveData, ParasiticElectricLoadDuringDischarging, ParasiticElectricLoadDuringCharging, TankLossCoefficient, FreezingTemperatureofStorageMedium, ThawProcessIndicator,   };
  ThermalStorage_Ice_DetailedFields()
   : EnumBase<ThermalStorage_Ice_DetailedFields>(Name) {} 
  ThermalStorage_Ice_DetailedFields(const std::string &t_name) 
   : EnumBase<ThermalStorage_Ice_DetailedFields>(t_name) {} 
  ThermalStorage_Ice_DetailedFields(int t_value) 
   : EnumBase<ThermalStorage_Ice_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "ThermalStorage_Ice_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ThermalStorage_Ice_DetailedFields>::integer_value()); }
   private:
    friend class EnumBase<ThermalStorage_Ice_DetailedFields>;
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
{ ThermalStorage_Ice_DetailedFields::Name, "Name", "Name"},
{ ThermalStorage_Ice_DetailedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ThermalStorage_Ice_DetailedFields::Capacity, "Capacity", "Capacity"},
{ ThermalStorage_Ice_DetailedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ ThermalStorage_Ice_DetailedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications, "DischargingCurveVariableSpecifications", "Discharging Curve Variable Specifications"},
{ ThermalStorage_Ice_DetailedFields::DischargingCurveName, "DischargingCurveName", "Discharging Curve Name"},
{ ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications, "ChargingCurveVariableSpecifications", "Charging Curve Variable Specifications"},
{ ThermalStorage_Ice_DetailedFields::ChargingCurveName, "ChargingCurveName", "Charging Curve Name"},
{ ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, "TimestepoftheCurveData", "Timestep of the Curve Data"},
{ ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, "ParasiticElectricLoadDuringDischarging", "Parasitic Electric Load During Discharging"},
{ ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, "ParasiticElectricLoadDuringCharging", "Parasitic Electric Load During Charging"},
{ ThermalStorage_Ice_DetailedFields::TankLossCoefficient, "TankLossCoefficient", "Tank Loss Coefficient"},
{ ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, "FreezingTemperatureofStorageMedium", "Freezing Temperature of Storage Medium"},
{ ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, "ThawProcessIndicator", "Thaw Process Indicator"},
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
  inline std::ostream &operator<<(std::ostream &os, const ThermalStorage_Ice_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ThermalStorage_Ice_DetailedFields> OptionalThermalStorage_Ice_DetailedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX
