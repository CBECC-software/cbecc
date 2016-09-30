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

#ifndef UTILITIES_IDD_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeaderedPumps_ConstantSpeedFields
 *  \brief Enumeration of HeaderedPumps:ConstantSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeaderedPumps_ConstantSpeedFields, )
#else
class HeaderedPumps_ConstantSpeedFields: public ::EnumBase<HeaderedPumps_ConstantSpeedFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, TotalDesignFlowRate, NumberofPumpsinBank, FlowSequencingControlScheme, DesignPumpHead, DesignPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, PumpControlType, PumpFlowRateScheduleName, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead,   };
  HeaderedPumps_ConstantSpeedFields()
   : EnumBase<HeaderedPumps_ConstantSpeedFields>(Name) {} 
  HeaderedPumps_ConstantSpeedFields(const std::string &t_name) 
   : EnumBase<HeaderedPumps_ConstantSpeedFields>(t_name) {} 
  HeaderedPumps_ConstantSpeedFields(int t_value) 
   : EnumBase<HeaderedPumps_ConstantSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "HeaderedPumps_ConstantSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeaderedPumps_ConstantSpeedFields>::value()); }
   private:
    friend class EnumBase<HeaderedPumps_ConstantSpeedFields>;
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
{ HeaderedPumps_ConstantSpeedFields::Name, "Name", "Name"},
{ HeaderedPumps_ConstantSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ HeaderedPumps_ConstantSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ HeaderedPumps_ConstantSpeedFields::TotalDesignFlowRate, "TotalDesignFlowRate", "Total Design Flow Rate"},
{ HeaderedPumps_ConstantSpeedFields::NumberofPumpsinBank, "NumberofPumpsinBank", "Number of Pumps in Bank"},
{ HeaderedPumps_ConstantSpeedFields::FlowSequencingControlScheme, "FlowSequencingControlScheme", "Flow Sequencing Control Scheme"},
{ HeaderedPumps_ConstantSpeedFields::DesignPumpHead, "DesignPumpHead", "Design Pump Head"},
{ HeaderedPumps_ConstantSpeedFields::DesignPowerConsumption, "DesignPowerConsumption", "Design Power Consumption"},
{ HeaderedPumps_ConstantSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ HeaderedPumps_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ HeaderedPumps_ConstantSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ HeaderedPumps_ConstantSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ HeaderedPumps_ConstantSpeedFields::ZoneName, "ZoneName", "Zone Name"},
{ HeaderedPumps_ConstantSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ HeaderedPumps_ConstantSpeedFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ HeaderedPumps_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ HeaderedPumps_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeaderedPumps_ConstantSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeaderedPumps_ConstantSpeedFields> OptionalHeaderedPumps_ConstantSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEADEREDPUMPS_CONSTANTSPEED_FIELDENUMS_HXX
