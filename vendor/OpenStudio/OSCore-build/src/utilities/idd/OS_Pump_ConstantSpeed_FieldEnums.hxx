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

#ifndef UTILITIES_IDD_OS_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PUMP_CONSTANTSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Pump_ConstantSpeedFields
 *  \brief Enumeration of OS:Pump:ConstantSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Pump_ConstantSpeedFields, )
#else
class OS_Pump_ConstantSpeedFields: public ::EnumBase<OS_Pump_ConstantSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, RatedFlowRate, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, PumpControlType, PumpFlowRateSchedule, PumpCurve, ImpellerDiameter, RotationalSpeed, Zone, SkinLossRadiativeFraction,   };
  OS_Pump_ConstantSpeedFields()
   : EnumBase<OS_Pump_ConstantSpeedFields>(Handle) {} 
  OS_Pump_ConstantSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Pump_ConstantSpeedFields>(t_name) {} 
  OS_Pump_ConstantSpeedFields(int t_value) 
   : EnumBase<OS_Pump_ConstantSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Pump_ConstantSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Pump_ConstantSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Pump_ConstantSpeedFields>;
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
{ OS_Pump_ConstantSpeedFields::Handle, "Handle", "Handle"},
{ OS_Pump_ConstantSpeedFields::Name, "Name", "Name"},
{ OS_Pump_ConstantSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_Pump_ConstantSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_Pump_ConstantSpeedFields::RatedFlowRate, "RatedFlowRate", "Rated Flow Rate"},
{ OS_Pump_ConstantSpeedFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ OS_Pump_ConstantSpeedFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ OS_Pump_ConstantSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ OS_Pump_ConstantSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ OS_Pump_ConstantSpeedFields::PumpFlowRateSchedule, "PumpFlowRateSchedule", "Pump Flow Rate Schedule"},
{ OS_Pump_ConstantSpeedFields::PumpCurve, "PumpCurve", "Pump Curve"},
{ OS_Pump_ConstantSpeedFields::ImpellerDiameter, "ImpellerDiameter", "Impeller Diameter"},
{ OS_Pump_ConstantSpeedFields::RotationalSpeed, "RotationalSpeed", "Rotational Speed"},
{ OS_Pump_ConstantSpeedFields::Zone, "Zone", "Zone"},
{ OS_Pump_ConstantSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Pump_ConstantSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Pump_ConstantSpeedFields> OptionalOS_Pump_ConstantSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
