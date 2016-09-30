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

#ifndef UTILITIES_IDD_OS_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_DX_VariableRefrigerantFlowFields
 *  \brief Enumeration of OS:Coil:Heating:DX:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_DX_VariableRefrigerantFlowFields, )
#else
class OS_Coil_Heating_DX_VariableRefrigerantFlowFields: public ::EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, RatedTotalHeatingCapacity, RatedAirFlowRate, CoilAirInletNode, CoilAirOutletNode, HeatingCapacityRatioModifierFunctionofTemperatureCurve, HeatingCapacityModifierFunctionofFlowFractionCurve,   };
  OS_Coil_Heating_DX_VariableRefrigerantFlowFields()
   : EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields>(Handle) {} 
  OS_Coil_Heating_DX_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields>(t_name) {} 
  OS_Coil_Heating_DX_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_DX_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_DX_VariableRefrigerantFlowFields>;
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
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::Name, "Name", "Name"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::RatedTotalHeatingCapacity, "RatedTotalHeatingCapacity", "Rated Total Heating Capacity"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, "CoilAirInletNode", "Coil Air Inlet Node"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, "CoilAirOutletNode", "Coil Air Outlet Node"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofTemperatureCurve, "HeatingCapacityRatioModifierFunctionofTemperatureCurve", "Heating Capacity Ratio Modifier Function of Temperature Curve"},
{ OS_Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityModifierFunctionofFlowFractionCurve, "HeatingCapacityModifierFunctionofFlowFractionCurve", "Heating Capacity Modifier Function of Flow Fraction Curve"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_DX_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_DX_VariableRefrigerantFlowFields> OptionalOS_Coil_Heating_DX_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
