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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVACFields
 *  \brief Enumeration of OS:AirLoopHVAC's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVACFields, )
#else
class OS_AirLoopHVACFields: public ::EnumBase<OS_AirLoopHVACFields> {
 public: 
  enum domain 
  {
Handle, Name, ControllerListName, AvailabilitySchedule, AvailabilityManager, DesignSupplyAirFlowRate, BranchListName, ConnectorListName, SupplySideInletNodeName, DemandSideOutletNodeName, DemandSideInletNodeA, SupplySideOutletNodeA, DemandSideInletNodeB, SupplySideOutletNodeB, ReturnAirBypassFlowTemperatureSetpointScheduleName,   };
  OS_AirLoopHVACFields()
   : EnumBase<OS_AirLoopHVACFields>(Handle) {} 
  OS_AirLoopHVACFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVACFields>(t_name) {} 
  OS_AirLoopHVACFields(int t_value) 
   : EnumBase<OS_AirLoopHVACFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVACFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVACFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVACFields>;
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
{ OS_AirLoopHVACFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVACFields::Name, "Name", "Name"},
{ OS_AirLoopHVACFields::ControllerListName, "ControllerListName", "Controller List Name"},
{ OS_AirLoopHVACFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirLoopHVACFields::AvailabilityManager, "AvailabilityManager", "Availability Manager"},
{ OS_AirLoopHVACFields::DesignSupplyAirFlowRate, "DesignSupplyAirFlowRate", "Design Supply Air Flow Rate"},
{ OS_AirLoopHVACFields::BranchListName, "BranchListName", "Branch List Name"},
{ OS_AirLoopHVACFields::ConnectorListName, "ConnectorListName", "Connector List Name"},
{ OS_AirLoopHVACFields::SupplySideInletNodeName, "SupplySideInletNodeName", "Supply Side Inlet Node Name"},
{ OS_AirLoopHVACFields::DemandSideOutletNodeName, "DemandSideOutletNodeName", "Demand Side Outlet Node Name"},
{ OS_AirLoopHVACFields::DemandSideInletNodeA, "DemandSideInletNodeA", "Demand Side Inlet Node A"},
{ OS_AirLoopHVACFields::SupplySideOutletNodeA, "SupplySideOutletNodeA", "Supply Side Outlet Node A"},
{ OS_AirLoopHVACFields::DemandSideInletNodeB, "DemandSideInletNodeB", "Demand Side Inlet Node B"},
{ OS_AirLoopHVACFields::SupplySideOutletNodeB, "SupplySideOutletNodeB", "Supply Side Outlet Node B"},
{ OS_AirLoopHVACFields::ReturnAirBypassFlowTemperatureSetpointScheduleName, "ReturnAirBypassFlowTemperatureSetpointScheduleName", "Return Air Bypass Flow Temperature Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVACFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVACFields> OptionalOS_AirLoopHVACFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_FIELDENUMS_HXX
