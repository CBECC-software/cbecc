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

#ifndef UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EnergyRecoveryVentilatorFields
 *  \brief Enumeration of ZoneHVAC:EnergyRecoveryVentilator's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EnergyRecoveryVentilatorFields, )
#else
class ZoneHVAC_EnergyRecoveryVentilatorFields: public ::EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, HeatExchangerName, SupplyAirFlowRate, ExhaustAirFlowRate, SupplyAirFanName, ExhaustAirFanName, ControllerName, VentilationRateperUnitFloorArea, VentilationRateperOccupant, AvailabilityManagerListName,   };
  ZoneHVAC_EnergyRecoveryVentilatorFields()
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(Name) {} 
  ZoneHVAC_EnergyRecoveryVentilatorFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(t_name) {} 
  ZoneHVAC_EnergyRecoveryVentilatorFields(int t_value) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EnergyRecoveryVentilatorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>;
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
{ ZoneHVAC_EnergyRecoveryVentilatorFields::Name, "Name", "Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName, "HeatExchangerName", "Heat Exchanger Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, "SupplyAirFlowRate", "Supply Air Flow Rate"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, "ExhaustAirFlowRate", "Exhaust Air Flow Rate"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName, "ExhaustAirFanName", "Exhaust Air Fan Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName, "ControllerName", "Controller Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, "VentilationRateperUnitFloorArea", "Ventilation Rate per Unit Floor Area"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, "VentilationRateperOccupant", "Ventilation Rate per Occupant"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EnergyRecoveryVentilatorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EnergyRecoveryVentilatorFields> OptionalZoneHVAC_EnergyRecoveryVentilatorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX
