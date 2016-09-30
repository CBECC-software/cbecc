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

#ifndef UTILITIES_IDD_OS_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeaderedPumps_ConstantSpeedFields
 *  \brief Enumeration of OS:HeaderedPumps:ConstantSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeaderedPumps_ConstantSpeedFields, )
#else
class OS_HeaderedPumps_ConstantSpeedFields: public ::EnumBase<OS_HeaderedPumps_ConstantSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, TotalRatedFlowRate, NumberofPumpsinBank, FlowSequencingControlScheme, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, PumpControlType, PumpFlowRateSchedule, ThermalZone, SkinLossRadiativeFraction,   };
  OS_HeaderedPumps_ConstantSpeedFields()
   : EnumBase<OS_HeaderedPumps_ConstantSpeedFields>(Handle) {} 
  OS_HeaderedPumps_ConstantSpeedFields(const std::string &t_name) 
   : EnumBase<OS_HeaderedPumps_ConstantSpeedFields>(t_name) {} 
  OS_HeaderedPumps_ConstantSpeedFields(int t_value) 
   : EnumBase<OS_HeaderedPumps_ConstantSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeaderedPumps_ConstantSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeaderedPumps_ConstantSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_HeaderedPumps_ConstantSpeedFields>;
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
{ OS_HeaderedPumps_ConstantSpeedFields::Handle, "Handle", "Handle"},
{ OS_HeaderedPumps_ConstantSpeedFields::Name, "Name", "Name"},
{ OS_HeaderedPumps_ConstantSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_HeaderedPumps_ConstantSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_HeaderedPumps_ConstantSpeedFields::TotalRatedFlowRate, "TotalRatedFlowRate", "Total Rated Flow Rate"},
{ OS_HeaderedPumps_ConstantSpeedFields::NumberofPumpsinBank, "NumberofPumpsinBank", "Number of Pumps in Bank"},
{ OS_HeaderedPumps_ConstantSpeedFields::FlowSequencingControlScheme, "FlowSequencingControlScheme", "Flow Sequencing Control Scheme"},
{ OS_HeaderedPumps_ConstantSpeedFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ OS_HeaderedPumps_ConstantSpeedFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ OS_HeaderedPumps_ConstantSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_HeaderedPumps_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ OS_HeaderedPumps_ConstantSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ OS_HeaderedPumps_ConstantSpeedFields::PumpFlowRateSchedule, "PumpFlowRateSchedule", "Pump Flow Rate Schedule"},
{ OS_HeaderedPumps_ConstantSpeedFields::ThermalZone, "ThermalZone", "Thermal Zone"},
{ OS_HeaderedPumps_ConstantSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeaderedPumps_ConstantSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeaderedPumps_ConstantSpeedFields> OptionalOS_HeaderedPumps_ConstantSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX
