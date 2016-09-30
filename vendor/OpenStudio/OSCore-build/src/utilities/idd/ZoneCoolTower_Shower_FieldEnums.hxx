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

#ifndef UTILITIES_IDD_ZONECOOLTOWER_SHOWER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECOOLTOWER_SHOWER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneCoolTower_ShowerFields
 *  \brief Enumeration of ZoneCoolTower:Shower's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneCoolTower_ShowerFields, )
#else
class ZoneCoolTower_ShowerFields: public ::EnumBase<ZoneCoolTower_ShowerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, WaterSupplyStorageTankName, FlowControlType, PumpFlowRateScheduleName, MaximumWaterFlowRate, EffectiveTowerHeight, AirflowOutletArea, MaximumAirFlowRate, MinimumIndoorTemperature, FractionofWaterLoss, FractionofFlowSchedule, RatedPowerConsumption,   };
  ZoneCoolTower_ShowerFields()
   : EnumBase<ZoneCoolTower_ShowerFields>(Name) {} 
  ZoneCoolTower_ShowerFields(const std::string &t_name) 
   : EnumBase<ZoneCoolTower_ShowerFields>(t_name) {} 
  ZoneCoolTower_ShowerFields(int t_value) 
   : EnumBase<ZoneCoolTower_ShowerFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneCoolTower_ShowerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneCoolTower_ShowerFields>::value()); }
   private:
    friend class EnumBase<ZoneCoolTower_ShowerFields>;
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
{ ZoneCoolTower_ShowerFields::Name, "Name", "Name"},
{ ZoneCoolTower_ShowerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneCoolTower_ShowerFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneCoolTower_ShowerFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
{ ZoneCoolTower_ShowerFields::FlowControlType, "FlowControlType", "Flow Control Type"},
{ ZoneCoolTower_ShowerFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ ZoneCoolTower_ShowerFields::MaximumWaterFlowRate, "MaximumWaterFlowRate", "Maximum Water Flow Rate"},
{ ZoneCoolTower_ShowerFields::EffectiveTowerHeight, "EffectiveTowerHeight", "Effective Tower Height"},
{ ZoneCoolTower_ShowerFields::AirflowOutletArea, "AirflowOutletArea", "Airflow Outlet Area"},
{ ZoneCoolTower_ShowerFields::MaximumAirFlowRate, "MaximumAirFlowRate", "Maximum Air Flow Rate"},
{ ZoneCoolTower_ShowerFields::MinimumIndoorTemperature, "MinimumIndoorTemperature", "Minimum Indoor Temperature"},
{ ZoneCoolTower_ShowerFields::FractionofWaterLoss, "FractionofWaterLoss", "Fraction of Water Loss"},
{ ZoneCoolTower_ShowerFields::FractionofFlowSchedule, "FractionofFlowSchedule", "Fraction of Flow Schedule"},
{ ZoneCoolTower_ShowerFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneCoolTower_ShowerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneCoolTower_ShowerFields> OptionalZoneCoolTower_ShowerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECOOLTOWER_SHOWER_FIELDENUMS_HXX
