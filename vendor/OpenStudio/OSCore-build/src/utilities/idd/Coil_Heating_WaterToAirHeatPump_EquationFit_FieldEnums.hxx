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

#ifndef UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_WaterToAirHeatPump_EquationFitFields
 *  \brief Enumeration of Coil:Heating:WaterToAirHeatPump:EquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_WaterToAirHeatPump_EquationFitFields, )
#else
class Coil_Heating_WaterToAirHeatPump_EquationFitFields: public ::EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, RatedAirFlowRate, RatedWaterFlowRate, GrossRatedHeatingCapacity, GrossRatedHeatingCOP, HeatingCapacityCoefficient1, HeatingCapacityCoefficient2, HeatingCapacityCoefficient3, HeatingCapacityCoefficient4, HeatingCapacityCoefficient5, HeatingPowerConsumptionCoefficient1, HeatingPowerConsumptionCoefficient2, HeatingPowerConsumptionCoefficient3, HeatingPowerConsumptionCoefficient4, HeatingPowerConsumptionCoefficient5,   };
  Coil_Heating_WaterToAirHeatPump_EquationFitFields()
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(Name) {} 
  Coil_Heating_WaterToAirHeatPump_EquationFitFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(t_name) {} 
  Coil_Heating_WaterToAirHeatPump_EquationFitFields(int t_value) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_WaterToAirHeatPump_EquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>;
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
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::Name, "Name", "Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "RatedWaterFlowRate", "Rated Water Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP, "GrossRatedHeatingCOP", "Gross Rated Heating COP"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCoefficient1, "HeatingCapacityCoefficient1", "Heating Capacity Coefficient 1"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCoefficient2, "HeatingCapacityCoefficient2", "Heating Capacity Coefficient 2"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCoefficient3, "HeatingCapacityCoefficient3", "Heating Capacity Coefficient 3"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCoefficient4, "HeatingCapacityCoefficient4", "Heating Capacity Coefficient 4"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCoefficient5, "HeatingCapacityCoefficient5", "Heating Capacity Coefficient 5"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCoefficient1, "HeatingPowerConsumptionCoefficient1", "Heating Power Consumption Coefficient 1"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCoefficient2, "HeatingPowerConsumptionCoefficient2", "Heating Power Consumption Coefficient 2"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCoefficient3, "HeatingPowerConsumptionCoefficient3", "Heating Power Consumption Coefficient 3"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCoefficient4, "HeatingPowerConsumptionCoefficient4", "Heating Power Consumption Coefficient 4"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCoefficient5, "HeatingPowerConsumptionCoefficient5", "Heating Power Consumption Coefficient 5"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_WaterToAirHeatPump_EquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_WaterToAirHeatPump_EquationFitFields> OptionalCoil_Heating_WaterToAirHeatPump_EquationFitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
