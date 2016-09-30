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

#ifndef UTILITIES_IDD_PUMP_VARIABLESPEED_CONDENSATE_FIELDENUMS_HXX
#define UTILITIES_IDD_PUMP_VARIABLESPEED_CONDENSATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Pump_VariableSpeed_CondensateFields
 *  \brief Enumeration of Pump:VariableSpeed:Condensate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Pump_VariableSpeed_CondensateFields, )
#else
class Pump_VariableSpeed_CondensateFields: public ::EnumBase<Pump_VariableSpeed_CondensateFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignSteamVolumeFlowRate, DesignPumpHead, DesignPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, Coefficient1ofthePartLoadPerformanceCurve, Coefficient2ofthePartLoadPerformanceCurve, Coefficient3ofthePartLoadPerformanceCurve, Coefficient4ofthePartLoadPerformanceCurve, PumpFlowRateScheduleName, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead,   };
  Pump_VariableSpeed_CondensateFields()
   : EnumBase<Pump_VariableSpeed_CondensateFields>(Name) {} 
  Pump_VariableSpeed_CondensateFields(const std::string &t_name) 
   : EnumBase<Pump_VariableSpeed_CondensateFields>(t_name) {} 
  Pump_VariableSpeed_CondensateFields(int t_value) 
   : EnumBase<Pump_VariableSpeed_CondensateFields>(t_value) {} 
  static std::string enumName() 
  { return "Pump_VariableSpeed_CondensateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Pump_VariableSpeed_CondensateFields>::value()); }
   private:
    friend class EnumBase<Pump_VariableSpeed_CondensateFields>;
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
{ Pump_VariableSpeed_CondensateFields::Name, "Name", "Name"},
{ Pump_VariableSpeed_CondensateFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ Pump_VariableSpeed_CondensateFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, "DesignSteamVolumeFlowRate", "Design Steam Volume Flow Rate"},
{ Pump_VariableSpeed_CondensateFields::DesignPumpHead, "DesignPumpHead", "Design Pump Head"},
{ Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, "DesignPowerConsumption", "Design Power Consumption"},
{ Pump_VariableSpeed_CondensateFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Pump_VariableSpeed_CondensateFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ Pump_VariableSpeed_CondensateFields::Coefficient1ofthePartLoadPerformanceCurve, "Coefficient1ofthePartLoadPerformanceCurve", "Coefficient 1 of the Part Load Performance Curve"},
{ Pump_VariableSpeed_CondensateFields::Coefficient2ofthePartLoadPerformanceCurve, "Coefficient2ofthePartLoadPerformanceCurve", "Coefficient 2 of the Part Load Performance Curve"},
{ Pump_VariableSpeed_CondensateFields::Coefficient3ofthePartLoadPerformanceCurve, "Coefficient3ofthePartLoadPerformanceCurve", "Coefficient 3 of the Part Load Performance Curve"},
{ Pump_VariableSpeed_CondensateFields::Coefficient4ofthePartLoadPerformanceCurve, "Coefficient4ofthePartLoadPerformanceCurve", "Coefficient 4 of the Part Load Performance Curve"},
{ Pump_VariableSpeed_CondensateFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ Pump_VariableSpeed_CondensateFields::ZoneName, "ZoneName", "Zone Name"},
{ Pump_VariableSpeed_CondensateFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ Pump_VariableSpeed_CondensateFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ Pump_VariableSpeed_CondensateFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
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
  inline std::ostream &operator<<(std::ostream &os, const Pump_VariableSpeed_CondensateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Pump_VariableSpeed_CondensateFields> OptionalPump_VariableSpeed_CondensateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PUMP_VARIABLESPEED_CONDENSATE_FIELDENUMS_HXX
