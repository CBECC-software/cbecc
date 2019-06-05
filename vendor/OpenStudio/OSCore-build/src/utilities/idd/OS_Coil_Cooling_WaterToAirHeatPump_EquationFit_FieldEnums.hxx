/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields
 *  \brief Enumeration of OS:Coil:Cooling:WaterToAirHeatPump:EquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields, )
#else
class OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields: public ::EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, RatedAirFlowRate, RatedWaterFlowRate, RatedTotalCoolingCapacity, RatedSensibleCoolingCapacity, RatedCoolingCoefficientofPerformance, TotalCoolingCapacityCoefficient1, TotalCoolingCapacityCoefficient2, TotalCoolingCapacityCoefficient3, TotalCoolingCapacityCoefficient4, TotalCoolingCapacityCoefficient5, SensibleCoolingCapacityCoefficient1, SensibleCoolingCapacityCoefficient2, SensibleCoolingCapacityCoefficient3, SensibleCoolingCapacityCoefficient4, SensibleCoolingCapacityCoefficient5, SensibleCoolingCapacityCoefficient6, CoolingPowerConsumptionCoefficient1, CoolingPowerConsumptionCoefficient2, CoolingPowerConsumptionCoefficient3, CoolingPowerConsumptionCoefficient4, CoolingPowerConsumptionCoefficient5, NominalTimeforCondensateRemovaltoBegin, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,   };
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields()
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(Handle) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(t_name) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>;
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
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "RatedWaterFlowRate", "Rated Water Flow Rate"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedTotalCoolingCapacity, "RatedTotalCoolingCapacity", "Rated Total Cooling Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedSensibleCoolingCapacity, "RatedSensibleCoolingCapacity", "Rated Sensible Cooling Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedCoolingCoefficientofPerformance, "RatedCoolingCoefficientofPerformance", "Rated Cooling Coefficient of Performance"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCoefficient1, "TotalCoolingCapacityCoefficient1", "Total Cooling Capacity Coefficient 1"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCoefficient2, "TotalCoolingCapacityCoefficient2", "Total Cooling Capacity Coefficient 2"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCoefficient3, "TotalCoolingCapacityCoefficient3", "Total Cooling Capacity Coefficient 3"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCoefficient4, "TotalCoolingCapacityCoefficient4", "Total Cooling Capacity Coefficient 4"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCoefficient5, "TotalCoolingCapacityCoefficient5", "Total Cooling Capacity Coefficient 5"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient1, "SensibleCoolingCapacityCoefficient1", "Sensible Cooling Capacity Coefficient 1"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient2, "SensibleCoolingCapacityCoefficient2", "Sensible Cooling Capacity Coefficient 2"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient3, "SensibleCoolingCapacityCoefficient3", "Sensible Cooling Capacity Coefficient 3"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient4, "SensibleCoolingCapacityCoefficient4", "Sensible Cooling Capacity Coefficient 4"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient5, "SensibleCoolingCapacityCoefficient5", "Sensible Cooling Capacity Coefficient 5"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCoefficient6, "SensibleCoolingCapacityCoefficient6", "Sensible Cooling Capacity Coefficient 6"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCoefficient1, "CoolingPowerConsumptionCoefficient1", "Cooling Power Consumption Coefficient 1"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCoefficient2, "CoolingPowerConsumptionCoefficient2", "Cooling Power Consumption Coefficient 2"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCoefficient3, "CoolingPowerConsumptionCoefficient3", "Cooling Power Consumption Coefficient 3"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCoefficient4, "CoolingPowerConsumptionCoefficient4", "Cooling Power Consumption Coefficient 4"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCoefficient5, "CoolingPowerConsumptionCoefficient5", "Cooling Power Consumption Coefficient 5"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields> OptionalOS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
