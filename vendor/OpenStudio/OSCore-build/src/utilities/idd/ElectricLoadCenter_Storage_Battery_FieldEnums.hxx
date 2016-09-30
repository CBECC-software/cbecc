/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_BATTERY_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_BATTERY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Storage_BatteryFields
 *  \brief Enumeration of ElectricLoadCenter:Storage:Battery's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Storage_BatteryFields, )
#else
class ElectricLoadCenter_Storage_BatteryFields: public ::EnumBase<ElectricLoadCenter_Storage_BatteryFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, NumberofBatteryModulesinParallel, NumberofBatteryModulesinSeries, MaximumModuleCapacity, InitialFractionalStateofCharge, FractionofAvailableChargeCapacity, ChangeRatefromBoundChargetoAvailableCharge, FullyChargedModuleOpenCircuitVoltage, FullyDischargedModuleOpenCircuitVoltage, VoltageChangeCurveNameforCharging, VoltageChangeCurveNameforDischarging, ModuleInternalElectricalResistance, MaximumModuleDischargingCurrent, ModuleCutoffVoltage, ModuleChargeRateLimit, BatteryLifeCalculation, NumberofCycleBins, BatteryLifeCurveName,   };
  ElectricLoadCenter_Storage_BatteryFields()
   : EnumBase<ElectricLoadCenter_Storage_BatteryFields>(Name) {} 
  ElectricLoadCenter_Storage_BatteryFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Storage_BatteryFields>(t_name) {} 
  ElectricLoadCenter_Storage_BatteryFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Storage_BatteryFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Storage_BatteryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Storage_BatteryFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Storage_BatteryFields>;
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
{ ElectricLoadCenter_Storage_BatteryFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Storage_BatteryFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Storage_BatteryFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Storage_BatteryFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinParallel, "NumberofBatteryModulesinParallel", "Number of Battery Modules in Parallel"},
{ ElectricLoadCenter_Storage_BatteryFields::NumberofBatteryModulesinSeries, "NumberofBatteryModulesinSeries", "Number of Battery Modules in Series"},
{ ElectricLoadCenter_Storage_BatteryFields::MaximumModuleCapacity, "MaximumModuleCapacity", "Maximum Module Capacity"},
{ ElectricLoadCenter_Storage_BatteryFields::InitialFractionalStateofCharge, "InitialFractionalStateofCharge", "Initial Fractional State of Charge"},
{ ElectricLoadCenter_Storage_BatteryFields::FractionofAvailableChargeCapacity, "FractionofAvailableChargeCapacity", "Fraction of Available Charge Capacity"},
{ ElectricLoadCenter_Storage_BatteryFields::ChangeRatefromBoundChargetoAvailableCharge, "ChangeRatefromBoundChargetoAvailableCharge", "Change Rate from Bound Charge to Available Charge"},
{ ElectricLoadCenter_Storage_BatteryFields::FullyChargedModuleOpenCircuitVoltage, "FullyChargedModuleOpenCircuitVoltage", "Fully Charged Module Open Circuit Voltage"},
{ ElectricLoadCenter_Storage_BatteryFields::FullyDischargedModuleOpenCircuitVoltage, "FullyDischargedModuleOpenCircuitVoltage", "Fully Discharged Module Open Circuit Voltage"},
{ ElectricLoadCenter_Storage_BatteryFields::VoltageChangeCurveNameforCharging, "VoltageChangeCurveNameforCharging", "Voltage Change Curve Name for Charging"},
{ ElectricLoadCenter_Storage_BatteryFields::VoltageChangeCurveNameforDischarging, "VoltageChangeCurveNameforDischarging", "Voltage Change Curve Name for Discharging"},
{ ElectricLoadCenter_Storage_BatteryFields::ModuleInternalElectricalResistance, "ModuleInternalElectricalResistance", "Module Internal Electrical Resistance"},
{ ElectricLoadCenter_Storage_BatteryFields::MaximumModuleDischargingCurrent, "MaximumModuleDischargingCurrent", "Maximum Module Discharging Current"},
{ ElectricLoadCenter_Storage_BatteryFields::ModuleCutoffVoltage, "ModuleCutoffVoltage", "Module Cut-off Voltage"},
{ ElectricLoadCenter_Storage_BatteryFields::ModuleChargeRateLimit, "ModuleChargeRateLimit", "Module Charge Rate Limit"},
{ ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCalculation, "BatteryLifeCalculation", "Battery Life Calculation"},
{ ElectricLoadCenter_Storage_BatteryFields::NumberofCycleBins, "NumberofCycleBins", "Number of Cycle Bins"},
{ ElectricLoadCenter_Storage_BatteryFields::BatteryLifeCurveName, "BatteryLifeCurveName", "Battery Life Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Storage_BatteryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Storage_BatteryFields> OptionalElectricLoadCenter_Storage_BatteryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_BATTERY_FIELDENUMS_HXX
