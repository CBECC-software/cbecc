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

#ifndef UTILITIES_IDD_OS_FAN_VARIABLEVOLUME_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FAN_VARIABLEVOLUME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Fan_VariableVolumeFields
 *  \brief Enumeration of OS:Fan:VariableVolume's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Fan_VariableVolumeFields, )
#else
class OS_Fan_VariableVolumeFields: public ::EnumBase<OS_Fan_VariableVolumeFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, FanEfficiency, PressureRise, MaximumFlowRate, FanPowerMinimumFlowRateInputMethod, FanPowerMinimumFlowFraction, FanPowerMinimumAirFlowRate, MotorEfficiency, MotorInAirstreamFraction, FanPowerCoefficient1, FanPowerCoefficient2, FanPowerCoefficient3, FanPowerCoefficient4, FanPowerCoefficient5, AirInletNodeName, AirOutletNodeName, EndUseSubcategory,   };
  OS_Fan_VariableVolumeFields()
   : EnumBase<OS_Fan_VariableVolumeFields>(Handle) {} 
  OS_Fan_VariableVolumeFields(const std::string &t_name) 
   : EnumBase<OS_Fan_VariableVolumeFields>(t_name) {} 
  OS_Fan_VariableVolumeFields(int t_value) 
   : EnumBase<OS_Fan_VariableVolumeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Fan_VariableVolumeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Fan_VariableVolumeFields>::value()); }
   private:
    friend class EnumBase<OS_Fan_VariableVolumeFields>;
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
{ OS_Fan_VariableVolumeFields::Handle, "Handle", "Handle"},
{ OS_Fan_VariableVolumeFields::Name, "Name", "Name"},
{ OS_Fan_VariableVolumeFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Fan_VariableVolumeFields::FanEfficiency, "FanEfficiency", "Fan Efficiency"},
{ OS_Fan_VariableVolumeFields::PressureRise, "PressureRise", "Pressure Rise"},
{ OS_Fan_VariableVolumeFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ OS_Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, "FanPowerMinimumFlowRateInputMethod", "Fan Power Minimum Flow Rate Input Method"},
{ OS_Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, "FanPowerMinimumFlowFraction", "Fan Power Minimum Flow Fraction"},
{ OS_Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, "FanPowerMinimumAirFlowRate", "Fan Power Minimum Air Flow Rate"},
{ OS_Fan_VariableVolumeFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Fan_VariableVolumeFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ OS_Fan_VariableVolumeFields::FanPowerCoefficient1, "FanPowerCoefficient1", "Fan Power Coefficient 1"},
{ OS_Fan_VariableVolumeFields::FanPowerCoefficient2, "FanPowerCoefficient2", "Fan Power Coefficient 2"},
{ OS_Fan_VariableVolumeFields::FanPowerCoefficient3, "FanPowerCoefficient3", "Fan Power Coefficient 3"},
{ OS_Fan_VariableVolumeFields::FanPowerCoefficient4, "FanPowerCoefficient4", "Fan Power Coefficient 4"},
{ OS_Fan_VariableVolumeFields::FanPowerCoefficient5, "FanPowerCoefficient5", "Fan Power Coefficient 5"},
{ OS_Fan_VariableVolumeFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Fan_VariableVolumeFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Fan_VariableVolumeFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Fan_VariableVolumeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Fan_VariableVolumeFields> OptionalOS_Fan_VariableVolumeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FAN_VARIABLEVOLUME_FIELDENUMS_HXX
