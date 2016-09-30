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

#ifndef UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_Desiccant_BalancedFlowFields
 *  \brief Enumeration of HeatExchanger:Desiccant:BalancedFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatExchanger_Desiccant_BalancedFlowFields, )
#else
class HeatExchanger_Desiccant_BalancedFlowFields: public ::EnumBase<HeatExchanger_Desiccant_BalancedFlowFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RegenerationAirInletNodeName, RegenerationAirOutletNodeName, ProcessAirInletNodeName, ProcessAirOutletNodeName, HeatExchangerPerformanceObjectType, HeatExchangerPerformanceName, EconomizerLockout,   };
  HeatExchanger_Desiccant_BalancedFlowFields()
   : EnumBase<HeatExchanger_Desiccant_BalancedFlowFields>(Name) {} 
  HeatExchanger_Desiccant_BalancedFlowFields(const std::string &t_name) 
   : EnumBase<HeatExchanger_Desiccant_BalancedFlowFields>(t_name) {} 
  HeatExchanger_Desiccant_BalancedFlowFields(int t_value) 
   : EnumBase<HeatExchanger_Desiccant_BalancedFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatExchanger_Desiccant_BalancedFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatExchanger_Desiccant_BalancedFlowFields>::value()); }
   private:
    friend class EnumBase<HeatExchanger_Desiccant_BalancedFlowFields>;
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
{ HeatExchanger_Desiccant_BalancedFlowFields::Name, "Name", "Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirInletNodeName, "RegenerationAirInletNodeName", "Regeneration Air Inlet Node Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirOutletNodeName, "RegenerationAirOutletNodeName", "Regeneration Air Outlet Node Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirInletNodeName, "ProcessAirInletNodeName", "Process Air Inlet Node Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirOutletNodeName, "ProcessAirOutletNodeName", "Process Air Outlet Node Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceObjectType, "HeatExchangerPerformanceObjectType", "Heat Exchanger Performance Object Type"},
{ HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName, "HeatExchangerPerformanceName", "Heat Exchanger Performance Name"},
{ HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatExchanger_Desiccant_BalancedFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatExchanger_Desiccant_BalancedFlowFields> OptionalHeatExchanger_Desiccant_BalancedFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_FIELDENUMS_HXX
