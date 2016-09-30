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

#ifndef UTILITIES_IDD_OS_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ThermalStorage_Ice_DetailedFields
 *  \brief Enumeration of OS:ThermalStorage:Ice:Detailed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ThermalStorage_Ice_DetailedFields, )
#else
class OS_ThermalStorage_Ice_DetailedFields: public ::EnumBase<OS_ThermalStorage_Ice_DetailedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, Capacity, InletNodeName, OutletNodeName, DischargingCurve, ChargingCurve, TimestepoftheCurveData, ParasiticElectricLoadDuringDischarging, ParasiticElectricLoadDuringCharging, TankLossCoefficient, FreezingTemperatureofStorageMedium, ThawProcessIndicator,   };
  OS_ThermalStorage_Ice_DetailedFields()
   : EnumBase<OS_ThermalStorage_Ice_DetailedFields>(Handle) {} 
  OS_ThermalStorage_Ice_DetailedFields(const std::string &t_name) 
   : EnumBase<OS_ThermalStorage_Ice_DetailedFields>(t_name) {} 
  OS_ThermalStorage_Ice_DetailedFields(int t_value) 
   : EnumBase<OS_ThermalStorage_Ice_DetailedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ThermalStorage_Ice_DetailedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ThermalStorage_Ice_DetailedFields>::value()); }
   private:
    friend class EnumBase<OS_ThermalStorage_Ice_DetailedFields>;
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
{ OS_ThermalStorage_Ice_DetailedFields::Handle, "Handle", "Handle"},
{ OS_ThermalStorage_Ice_DetailedFields::Name, "Name", "Name"},
{ OS_ThermalStorage_Ice_DetailedFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_ThermalStorage_Ice_DetailedFields::Capacity, "Capacity", "Capacity"},
{ OS_ThermalStorage_Ice_DetailedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_ThermalStorage_Ice_DetailedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_ThermalStorage_Ice_DetailedFields::DischargingCurve, "DischargingCurve", "Discharging Curve"},
{ OS_ThermalStorage_Ice_DetailedFields::ChargingCurve, "ChargingCurve", "Charging Curve"},
{ OS_ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, "TimestepoftheCurveData", "Timestep of the Curve Data"},
{ OS_ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, "ParasiticElectricLoadDuringDischarging", "Parasitic Electric Load During Discharging"},
{ OS_ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, "ParasiticElectricLoadDuringCharging", "Parasitic Electric Load During Charging"},
{ OS_ThermalStorage_Ice_DetailedFields::TankLossCoefficient, "TankLossCoefficient", "Tank Loss Coefficient"},
{ OS_ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, "FreezingTemperatureofStorageMedium", "Freezing Temperature of Storage Medium"},
{ OS_ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, "ThawProcessIndicator", "Thaw Process Indicator"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ThermalStorage_Ice_DetailedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ThermalStorage_Ice_DetailedFields> OptionalOS_ThermalStorage_Ice_DetailedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_THERMALSTORAGE_ICE_DETAILED_FIELDENUMS_HXX
