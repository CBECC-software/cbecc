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

#ifndef UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Pump_VariableSpeedFields
 *  \brief Enumeration of OS:Pump:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Pump_VariableSpeedFields, )
#else
class OS_Pump_VariableSpeedFields: public ::EnumBase<OS_Pump_VariableSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, RatedFlowRate, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, Coefficient1ofthePartLoadPerformanceCurve, Coefficient2ofthePartLoadPerformanceCurve, Coefficient3ofthePartLoadPerformanceCurve, Coefficient4ofthePartLoadPerformanceCurve, MinimumFlowRate, PumpControlType, PumpFlowRateScheduleName, PumpCurveName, ImpellerDiameter, VFDControlType, PumprpmScheduleName, MinimumPressureSchedule, MaximumPressureSchedule, MinimumRPMSchedule, MaximumRPMSchedule,   };
  OS_Pump_VariableSpeedFields()
   : EnumBase<OS_Pump_VariableSpeedFields>(Handle) {} 
  OS_Pump_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Pump_VariableSpeedFields>(t_name) {} 
  OS_Pump_VariableSpeedFields(int t_value) 
   : EnumBase<OS_Pump_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Pump_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Pump_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Pump_VariableSpeedFields>;
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
{ OS_Pump_VariableSpeedFields::Handle, "Handle", "Handle"},
{ OS_Pump_VariableSpeedFields::Name, "Name", "Name"},
{ OS_Pump_VariableSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_Pump_VariableSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_Pump_VariableSpeedFields::RatedFlowRate, "RatedFlowRate", "Rated Flow Rate"},
{ OS_Pump_VariableSpeedFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ OS_Pump_VariableSpeedFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ OS_Pump_VariableSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ OS_Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, "Coefficient1ofthePartLoadPerformanceCurve", "Coefficient 1 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, "Coefficient2ofthePartLoadPerformanceCurve", "Coefficient 2 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, "Coefficient3ofthePartLoadPerformanceCurve", "Coefficient 3 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, "Coefficient4ofthePartLoadPerformanceCurve", "Coefficient 4 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::MinimumFlowRate, "MinimumFlowRate", "Minimum Flow Rate"},
{ OS_Pump_VariableSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ OS_Pump_VariableSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ OS_Pump_VariableSpeedFields::PumpCurveName, "PumpCurveName", "Pump Curve Name"},
{ OS_Pump_VariableSpeedFields::ImpellerDiameter, "ImpellerDiameter", "Impeller Diameter"},
{ OS_Pump_VariableSpeedFields::VFDControlType, "VFDControlType", "VFD Control Type"},
{ OS_Pump_VariableSpeedFields::PumprpmScheduleName, "PumprpmScheduleName", "Pump rpm Schedule Name"},
{ OS_Pump_VariableSpeedFields::MinimumPressureSchedule, "MinimumPressureSchedule", "Minimum Pressure Schedule"},
{ OS_Pump_VariableSpeedFields::MaximumPressureSchedule, "MaximumPressureSchedule", "Maximum Pressure Schedule"},
{ OS_Pump_VariableSpeedFields::MinimumRPMSchedule, "MinimumRPMSchedule", "Minimum RPM Schedule"},
{ OS_Pump_VariableSpeedFields::MaximumRPMSchedule, "MaximumRPMSchedule", "Maximum RPM Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Pump_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Pump_VariableSpeedFields> OptionalOS_Pump_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX
