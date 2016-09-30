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

#ifndef UTILITIES_IDD_HEADEREDPUMPS_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_HEADEREDPUMPS_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeaderedPumps_VariableSpeedFields
 *  \brief Enumeration of HeaderedPumps:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeaderedPumps_VariableSpeedFields, )
#else
class HeaderedPumps_VariableSpeedFields: public ::EnumBase<HeaderedPumps_VariableSpeedFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, TotalDesignFlowRate, NumberofPumpsinBank, FlowSequencingControlScheme, DesignPumpHead, DesignPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, Coefficient1ofthePartLoadPerformanceCurve, Coefficient2ofthePartLoadPerformanceCurve, Coefficient3ofthePartLoadPerformanceCurve, Coefficient4ofthePartLoadPerformanceCurve, MinimumFlowRateFraction, PumpControlType, PumpFlowRateScheduleName, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead,   };
  HeaderedPumps_VariableSpeedFields()
   : EnumBase<HeaderedPumps_VariableSpeedFields>(Name) {} 
  HeaderedPumps_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<HeaderedPumps_VariableSpeedFields>(t_name) {} 
  HeaderedPumps_VariableSpeedFields(int t_value) 
   : EnumBase<HeaderedPumps_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "HeaderedPumps_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeaderedPumps_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<HeaderedPumps_VariableSpeedFields>;
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
{ HeaderedPumps_VariableSpeedFields::Name, "Name", "Name"},
{ HeaderedPumps_VariableSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ HeaderedPumps_VariableSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ HeaderedPumps_VariableSpeedFields::TotalDesignFlowRate, "TotalDesignFlowRate", "Total Design Flow Rate"},
{ HeaderedPumps_VariableSpeedFields::NumberofPumpsinBank, "NumberofPumpsinBank", "Number of Pumps in Bank"},
{ HeaderedPumps_VariableSpeedFields::FlowSequencingControlScheme, "FlowSequencingControlScheme", "Flow Sequencing Control Scheme"},
{ HeaderedPumps_VariableSpeedFields::DesignPumpHead, "DesignPumpHead", "Design Pump Head"},
{ HeaderedPumps_VariableSpeedFields::DesignPowerConsumption, "DesignPowerConsumption", "Design Power Consumption"},
{ HeaderedPumps_VariableSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ HeaderedPumps_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ HeaderedPumps_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, "Coefficient1ofthePartLoadPerformanceCurve", "Coefficient 1 of the Part Load Performance Curve"},
{ HeaderedPumps_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, "Coefficient2ofthePartLoadPerformanceCurve", "Coefficient 2 of the Part Load Performance Curve"},
{ HeaderedPumps_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, "Coefficient3ofthePartLoadPerformanceCurve", "Coefficient 3 of the Part Load Performance Curve"},
{ HeaderedPumps_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, "Coefficient4ofthePartLoadPerformanceCurve", "Coefficient 4 of the Part Load Performance Curve"},
{ HeaderedPumps_VariableSpeedFields::MinimumFlowRateFraction, "MinimumFlowRateFraction", "Minimum Flow Rate Fraction"},
{ HeaderedPumps_VariableSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ HeaderedPumps_VariableSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ HeaderedPumps_VariableSpeedFields::ZoneName, "ZoneName", "Zone Name"},
{ HeaderedPumps_VariableSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ HeaderedPumps_VariableSpeedFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ HeaderedPumps_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ HeaderedPumps_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeaderedPumps_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeaderedPumps_VariableSpeedFields> OptionalHeaderedPumps_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEADEREDPUMPS_VARIABLESPEED_FIELDENUMS_HXX
