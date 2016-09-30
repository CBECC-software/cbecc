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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields
 *  \brief Enumeration of OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields, )
#else
class OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields: public ::EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields> {
 public: 
  enum domain 
  {
Handle, Name, WatertoRefrigerantHXWaterInletNodeName, WatertoRefrigerantHXWaterOutletNodeName, IndoorAirInletNodeName, IndoorAirOutletNodeName, NominalSpeedLevel, GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, RatedAirFlowRateAtSelectedNominalSpeedLevel, RatedWaterFlowRateAtSelectedNominalSpeedLevel, NominalTimeforCondensatetoBeginLeavingtheCoil, InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, UseHotGasReheat, EnergyPartLoadFractionCurveName, SpeedDataList,   };
  OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields()
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields>(Handle) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields>(t_name) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields>;
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
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterInletNodeName, "WatertoRefrigerantHXWaterInletNodeName", "Water-to-Refrigerant HX Water Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterOutletNodeName, "WatertoRefrigerantHXWaterOutletNodeName", "Water-to-Refrigerant HX Water Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName, "IndoorAirInletNodeName", "Indoor Air Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName, "IndoorAirOutletNodeName", "Indoor Air Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, "GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel", "Gross Rated Total Cooling Capacity At Selected Nominal Speed Level"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "RatedAirFlowRateAtSelectedNominalSpeedLevel", "Rated Air Flow Rate At Selected Nominal Speed Level"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, "RatedWaterFlowRateAtSelectedNominalSpeedLevel", "Rated Water Flow Rate At Selected Nominal Speed Level"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalTimeforCondensatetoBeginLeavingtheCoil, "NominalTimeforCondensatetoBeginLeavingtheCoil", "Nominal Time for Condensate to Begin Leaving the Coil"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, "InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity", "Initial Moisture Evaporation Rate Divided by Steady-State AC Latent Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::UseHotGasReheat, "UseHotGasReheat", "Use Hot Gas Reheat"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::EnergyPartLoadFractionCurveName, "EnergyPartLoadFractionCurveName", "Energy Part Load Fraction Curve Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::SpeedDataList, "SpeedDataList", "Speed Data List"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields> OptionalOS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX
