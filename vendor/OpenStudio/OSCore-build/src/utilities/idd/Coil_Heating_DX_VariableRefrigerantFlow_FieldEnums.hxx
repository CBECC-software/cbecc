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

#ifndef UTILITIES_IDD_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_DX_VariableRefrigerantFlowFields
 *  \brief Enumeration of Coil:Heating:DX:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_DX_VariableRefrigerantFlowFields, )
#else
class Coil_Heating_DX_VariableRefrigerantFlowFields: public ::EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
Name, AvailabilitySchedule, GrossRatedHeatingCapacity, RatedAirFlowRate, CoilAirInletNode, CoilAirOutletNode, HeatingCapacityRatioModifierFunctionofTemperatureCurveName, HeatingCapacityModifierFunctionofFlowFractionCurveName,   };
  Coil_Heating_DX_VariableRefrigerantFlowFields()
   : EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields>(Name) {} 
  Coil_Heating_DX_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields>(t_name) {} 
  Coil_Heating_DX_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_VariableRefrigerantFlowFields>;
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
{ Coil_Heating_DX_VariableRefrigerantFlowFields::Name, "Name", "Name"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, "CoilAirInletNode", "Coil Air Inlet Node"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, "CoilAirOutletNode", "Coil Air Outlet Node"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofTemperatureCurveName, "HeatingCapacityRatioModifierFunctionofTemperatureCurveName", "Heating Capacity Ratio Modifier Function of Temperature Curve Name"},
{ Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityModifierFunctionofFlowFractionCurveName, "HeatingCapacityModifierFunctionofFlowFractionCurveName", "Heating Capacity Modifier Function of Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_VariableRefrigerantFlowFields> OptionalCoil_Heating_DX_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_DX_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
