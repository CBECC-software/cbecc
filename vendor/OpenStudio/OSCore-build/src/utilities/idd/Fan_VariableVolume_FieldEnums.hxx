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

#ifndef UTILITIES_IDD_FAN_VARIABLEVOLUME_FIELDENUMS_HXX
#define UTILITIES_IDD_FAN_VARIABLEVOLUME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Fan_VariableVolumeFields
 *  \brief Enumeration of Fan:VariableVolume's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_VariableVolumeFields, )
#else
class Fan_VariableVolumeFields: public ::EnumBase<Fan_VariableVolumeFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FanTotalEfficiency, PressureRise, MaximumFlowRate, FanPowerMinimumFlowRateInputMethod, FanPowerMinimumFlowFraction, FanPowerMinimumAirFlowRate, MotorEfficiency, MotorInAirstreamFraction, FanPowerCoefficient1, FanPowerCoefficient2, FanPowerCoefficient3, FanPowerCoefficient4, FanPowerCoefficient5, AirInletNodeName, AirOutletNodeName, EndUseSubcategory,   };
  Fan_VariableVolumeFields()
   : EnumBase<Fan_VariableVolumeFields>(Name) {} 
  Fan_VariableVolumeFields(const std::string &t_name) 
   : EnumBase<Fan_VariableVolumeFields>(t_name) {} 
  Fan_VariableVolumeFields(int t_value) 
   : EnumBase<Fan_VariableVolumeFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_VariableVolumeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_VariableVolumeFields>::value()); }
   private:
    friend class EnumBase<Fan_VariableVolumeFields>;
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
{ Fan_VariableVolumeFields::Name, "Name", "Name"},
{ Fan_VariableVolumeFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Fan_VariableVolumeFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ Fan_VariableVolumeFields::PressureRise, "PressureRise", "Pressure Rise"},
{ Fan_VariableVolumeFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, "FanPowerMinimumFlowRateInputMethod", "Fan Power Minimum Flow Rate Input Method"},
{ Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, "FanPowerMinimumFlowFraction", "Fan Power Minimum Flow Fraction"},
{ Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, "FanPowerMinimumAirFlowRate", "Fan Power Minimum Air Flow Rate"},
{ Fan_VariableVolumeFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Fan_VariableVolumeFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ Fan_VariableVolumeFields::FanPowerCoefficient1, "FanPowerCoefficient1", "Fan Power Coefficient 1"},
{ Fan_VariableVolumeFields::FanPowerCoefficient2, "FanPowerCoefficient2", "Fan Power Coefficient 2"},
{ Fan_VariableVolumeFields::FanPowerCoefficient3, "FanPowerCoefficient3", "Fan Power Coefficient 3"},
{ Fan_VariableVolumeFields::FanPowerCoefficient4, "FanPowerCoefficient4", "Fan Power Coefficient 4"},
{ Fan_VariableVolumeFields::FanPowerCoefficient5, "FanPowerCoefficient5", "Fan Power Coefficient 5"},
{ Fan_VariableVolumeFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Fan_VariableVolumeFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Fan_VariableVolumeFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_VariableVolumeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_VariableVolumeFields> OptionalFan_VariableVolumeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAN_VARIABLEVOLUME_FIELDENUMS_HXX
