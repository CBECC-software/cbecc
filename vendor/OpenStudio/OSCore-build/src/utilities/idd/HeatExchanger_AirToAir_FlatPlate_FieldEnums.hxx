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

#ifndef UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_FLATPLATE_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_FLATPLATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_AirToAir_FlatPlateFields
 *  \brief Enumeration of HeatExchanger:AirToAir:FlatPlate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatExchanger_AirToAir_FlatPlateFields, )
#else
class HeatExchanger_AirToAir_FlatPlateFields: public ::EnumBase<HeatExchanger_AirToAir_FlatPlateFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FlowArrangementType, EconomizerLockout, RatioofSupplytoSecondaryhAValues, NominalSupplyAirFlowRate, NominalSupplyAirInletTemperature, NominalSupplyAirOutletTemperature, NominalSecondaryAirFlowRate, NominalSecondaryAirInletTemperature, NominalElectricPower, SupplyAirInletNodeName, SupplyAirOutletNodeName, SecondaryAirInletNodeName, SecondaryAirOutletNodeName,   };
  HeatExchanger_AirToAir_FlatPlateFields()
   : EnumBase<HeatExchanger_AirToAir_FlatPlateFields>(Name) {} 
  HeatExchanger_AirToAir_FlatPlateFields(const std::string &t_name) 
   : EnumBase<HeatExchanger_AirToAir_FlatPlateFields>(t_name) {} 
  HeatExchanger_AirToAir_FlatPlateFields(int t_value) 
   : EnumBase<HeatExchanger_AirToAir_FlatPlateFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatExchanger_AirToAir_FlatPlateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatExchanger_AirToAir_FlatPlateFields>::value()); }
   private:
    friend class EnumBase<HeatExchanger_AirToAir_FlatPlateFields>;
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
{ HeatExchanger_AirToAir_FlatPlateFields::Name, "Name", "Name"},
{ HeatExchanger_AirToAir_FlatPlateFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ HeatExchanger_AirToAir_FlatPlateFields::FlowArrangementType, "FlowArrangementType", "Flow Arrangement Type"},
{ HeatExchanger_AirToAir_FlatPlateFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HeatExchanger_AirToAir_FlatPlateFields::RatioofSupplytoSecondaryhAValues, "RatioofSupplytoSecondaryhAValues", "Ratio of Supply to Secondary hA Values"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirFlowRate, "NominalSupplyAirFlowRate", "Nominal Supply Air Flow Rate"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirInletTemperature, "NominalSupplyAirInletTemperature", "Nominal Supply Air Inlet Temperature"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalSupplyAirOutletTemperature, "NominalSupplyAirOutletTemperature", "Nominal Supply Air Outlet Temperature"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirFlowRate, "NominalSecondaryAirFlowRate", "Nominal Secondary Air Flow Rate"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalSecondaryAirInletTemperature, "NominalSecondaryAirInletTemperature", "Nominal Secondary Air Inlet Temperature"},
{ HeatExchanger_AirToAir_FlatPlateFields::NominalElectricPower, "NominalElectricPower", "Nominal Electric Power"},
{ HeatExchanger_AirToAir_FlatPlateFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ HeatExchanger_AirToAir_FlatPlateFields::SupplyAirOutletNodeName, "SupplyAirOutletNodeName", "Supply Air Outlet Node Name"},
{ HeatExchanger_AirToAir_FlatPlateFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
{ HeatExchanger_AirToAir_FlatPlateFields::SecondaryAirOutletNodeName, "SecondaryAirOutletNodeName", "Secondary Air Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatExchanger_AirToAir_FlatPlateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatExchanger_AirToAir_FlatPlateFields> OptionalHeatExchanger_AirToAir_FlatPlateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_AIRTOAIR_FLATPLATE_FIELDENUMS_HXX
