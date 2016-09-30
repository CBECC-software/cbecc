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

#ifndef UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Pump_ConstantSpeedFields
 *  \brief Enumeration of Pump:ConstantSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Pump_ConstantSpeedFields, )
#else
class Pump_ConstantSpeedFields: public ::EnumBase<Pump_ConstantSpeedFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignFlowRate, DesignPumpHead, DesignPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, PumpControlType, PumpFlowRateScheduleName, PumpCurveName, ImpellerDiameter, RotationalSpeed, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead,   };
  Pump_ConstantSpeedFields()
   : EnumBase<Pump_ConstantSpeedFields>(Name) {} 
  Pump_ConstantSpeedFields(const std::string &t_name) 
   : EnumBase<Pump_ConstantSpeedFields>(t_name) {} 
  Pump_ConstantSpeedFields(int t_value) 
   : EnumBase<Pump_ConstantSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Pump_ConstantSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Pump_ConstantSpeedFields>::value()); }
   private:
    friend class EnumBase<Pump_ConstantSpeedFields>;
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
{ Pump_ConstantSpeedFields::Name, "Name", "Name"},
{ Pump_ConstantSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ Pump_ConstantSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ Pump_ConstantSpeedFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ Pump_ConstantSpeedFields::DesignPumpHead, "DesignPumpHead", "Design Pump Head"},
{ Pump_ConstantSpeedFields::DesignPowerConsumption, "DesignPowerConsumption", "Design Power Consumption"},
{ Pump_ConstantSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ Pump_ConstantSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ Pump_ConstantSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ Pump_ConstantSpeedFields::PumpCurveName, "PumpCurveName", "Pump Curve Name"},
{ Pump_ConstantSpeedFields::ImpellerDiameter, "ImpellerDiameter", "Impeller Diameter"},
{ Pump_ConstantSpeedFields::RotationalSpeed, "RotationalSpeed", "Rotational Speed"},
{ Pump_ConstantSpeedFields::ZoneName, "ZoneName", "Zone Name"},
{ Pump_ConstantSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ Pump_ConstantSpeedFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ Pump_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ Pump_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
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
  inline std::ostream &operator<<(std::ostream &os, const Pump_ConstantSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Pump_ConstantSpeedFields> OptionalPump_ConstantSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
