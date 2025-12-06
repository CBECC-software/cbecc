/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COILSYSTEM_COOLING_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_COILSYSTEM_COOLING_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoilSystem_Cooling_WaterFields
 *  \brief Enumeration of CoilSystem:Cooling:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoilSystem_Cooling_WaterFields, )
#else
class CoilSystem_Cooling_WaterFields: public ::EnumBase<CoilSystem_Cooling_WaterFields> {
 public: 
  enum domain 
  {
Name, AirInletNodeName, AirOutletNodeName, AvailabilityScheduleName, CoolingCoilObjectType, CoolingCoilName, DehumidificationControlType, RunonSensibleLoad, RunonLatentLoad, MinimumAirToWaterTemperatureOffset, EconomizerLockout, MinimumWaterLoopTemperatureForHeatRecovery, CompanionCoilUsedForHeatRecovery,   };
  CoilSystem_Cooling_WaterFields()
   : EnumBase<CoilSystem_Cooling_WaterFields>(Name) {} 
  CoilSystem_Cooling_WaterFields(const std::string &t_name) 
   : EnumBase<CoilSystem_Cooling_WaterFields>(t_name) {} 
  CoilSystem_Cooling_WaterFields(int t_value) 
   : EnumBase<CoilSystem_Cooling_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "CoilSystem_Cooling_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoilSystem_Cooling_WaterFields>::integer_value()); }
   private:
    friend class EnumBase<CoilSystem_Cooling_WaterFields>;
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
{ CoilSystem_Cooling_WaterFields::Name, "Name", "Name"},
{ CoilSystem_Cooling_WaterFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ CoilSystem_Cooling_WaterFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ CoilSystem_Cooling_WaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ CoilSystem_Cooling_WaterFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ CoilSystem_Cooling_WaterFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ CoilSystem_Cooling_WaterFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ CoilSystem_Cooling_WaterFields::RunonSensibleLoad, "RunonSensibleLoad", "Run on Sensible Load"},
{ CoilSystem_Cooling_WaterFields::RunonLatentLoad, "RunonLatentLoad", "Run on Latent Load"},
{ CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, "MinimumAirToWaterTemperatureOffset", "Minimum Air To Water Temperature Offset"},
{ CoilSystem_Cooling_WaterFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, "MinimumWaterLoopTemperatureForHeatRecovery", "Minimum Water Loop Temperature For Heat Recovery"},
{ CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery, "CompanionCoilUsedForHeatRecovery", "Companion Coil Used For Heat Recovery"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoilSystem_Cooling_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoilSystem_Cooling_WaterFields> OptionalCoilSystem_Cooling_WaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COILSYSTEM_COOLING_WATER_FIELDENUMS_HXX
