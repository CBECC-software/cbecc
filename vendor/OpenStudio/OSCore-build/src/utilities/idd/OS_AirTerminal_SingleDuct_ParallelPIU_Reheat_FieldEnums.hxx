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

#ifndef UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_PARALLELPIU_REHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_PARALLELPIU_REHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields
 *  \brief Enumeration of OS:AirTerminal:SingleDuct:ParallelPIU:Reheat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields, )
#else
class OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields: public ::EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, MaximumPrimaryAirFlowRate, MaximumSecondaryAirFlowRate, MinimumPrimaryAirFlowFraction, FanOnFlowFraction, SupplyAirInletNodeName, SecondaryAirInletNodeName, OutletNodeName, ReheatCoilAirInletNodeName, ZoneMixerName, FanName, ReheatCoilName, MaximumHotWaterorSteamFlowRate, MinimumHotWaterorSteamFlowRate, ConvergenceTolerance,   };
  OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields()
   : EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields>(Handle) {} 
  OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields(const std::string &t_name) 
   : EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields>(t_name) {} 
  OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields(int t_value) 
   : EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields>::value()); }
   private:
    friend class EnumBase<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields>;
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
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::Handle, "Handle", "Handle"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::Name, "Name", "Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, "MaximumPrimaryAirFlowRate", "Maximum Primary Air Flow Rate"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, "MaximumSecondaryAirFlowRate", "Maximum Secondary Air Flow Rate"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "MinimumPrimaryAirFlowFraction", "Minimum Primary Air Flow Fraction"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, "FanOnFlowFraction", "Fan On Flow Fraction"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilAirInletNodeName, "ReheatCoilAirInletNodeName", "Reheat Coil Air Inlet Node Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, "ZoneMixerName", "Zone Mixer Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, "FanName", "Fan Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, "ReheatCoilName", "Reheat Coil Name"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "MaximumHotWaterorSteamFlowRate", "Maximum Hot Water or Steam Flow Rate"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, "MinimumHotWaterorSteamFlowRate", "Minimum Hot Water or Steam Flow Rate"},
{ OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields> OptionalOS_AirTerminal_SingleDuct_ParallelPIU_ReheatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_PARALLELPIU_REHEAT_FIELDENUMS_HXX
