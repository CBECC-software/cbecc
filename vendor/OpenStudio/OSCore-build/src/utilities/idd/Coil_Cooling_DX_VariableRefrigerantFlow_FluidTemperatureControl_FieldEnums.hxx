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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields
 *  \brief Enumeration of Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields, )
#else
class Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields: public ::EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CoilAirInletNode, CoilAirOutletNode, RatedTotalCoolingCapacity, RatedSensibleHeatRatio, IndoorUnitReferenceSuperheating, IndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, NameofWaterStorageTankforCondensateCollection,   };
  Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields()
   : EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields>(Name) {} 
  Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields>(t_name) {} 
  Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields>;
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
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode, "CoilAirInletNode", "Coil Air Inlet Node"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode, "CoilAirOutletNode", "Coil Air Outlet Node"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalCoolingCapacity, "RatedTotalCoolingCapacity", "Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedSensibleHeatRatio, "RatedSensibleHeatRatio", "Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSuperheating, "IndoorUnitReferenceSuperheating", "Indoor Unit Reference Superheating"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, "IndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName", "Indoor Unit Evaporating Temperature Function of Superheating Curve Name"},
{ Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::NameofWaterStorageTankforCondensateCollection, "NameofWaterStorageTankforCondensateCollection", "Name of Water Storage Tank for Condensate Collection"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields> OptionalCoil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX
