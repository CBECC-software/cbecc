/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
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

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_VAV_REHEAT_VARIABLESPEEDFAN_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_VAV_REHEAT_VARIABLESPEEDFAN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields
 *  \brief Enumeration of AirTerminal:SingleDuct:VAV:Reheat:VariableSpeedFan's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields, )
#else
class AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields: public ::EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumCoolingAirFlowRate, MaximumHeatingAirFlowRate, ZoneMinimumAirFlowFraction, AirInletNodeName, AirOutletNodeName, HeatingCoilAirInletNodeName, HotWaterorSteamInletNodeName, FanObjectType, FanName, HeatingCoilObjectType, HeatingCoilName, MaximumHotWaterorSteamFlowRate, MinimumHotWaterorSteamFlowRate, HeatingConvergenceTolerance,   };
  AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields()
   : EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields>(Name) {} 
  AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields>(t_name) {} 
  AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields>;
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
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, "MaximumCoolingAirFlowRate", "Maximum Cooling Air Flow Rate"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, "MaximumHeatingAirFlowRate", "Maximum Heating Air Flow Rate"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::ZoneMinimumAirFlowFraction, "ZoneMinimumAirFlowFraction", "Zone Minimum Air Flow Fraction"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilAirInletNodeName, "HeatingCoilAirInletNodeName", "Heating Coil Air Inlet Node Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HotWaterorSteamInletNodeName, "HotWaterorSteamInletNodeName", "Hot Water or Steam Inlet Node Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanObjectType, "FanObjectType", "Fan Object Type"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName, "FanName", "Fan Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, "MaximumHotWaterorSteamFlowRate", "Maximum Hot Water or Steam Flow Rate"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate, "MinimumHotWaterorSteamFlowRate", "Minimum Hot Water or Steam Flow Rate"},
{ AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields> OptionalAirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_VAV_REHEAT_VARIABLESPEEDFAN_FIELDENUMS_HXX
