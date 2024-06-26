/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricEquipment_ITE_AirCooledFields
 *  \brief Enumeration of ElectricEquipment:ITE:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricEquipment_ITE_AirCooledFields, )
#else
class ElectricEquipment_ITE_AirCooledFields: public ::EnumBase<ElectricEquipment_ITE_AirCooledFields> {
 public: 
  enum domain 
  {
Name, ZoneName, AirFlowCalculationMethod, DesignPowerInputCalculationMethod, WattsperUnit, NumberofUnits, WattsperZoneFloorArea, DesignPowerInputScheduleName, CPULoadingScheduleName, CPUPowerInputFunctionofLoadingandAirTemperatureCurveName, DesignFanPowerInputFraction, DesignFanAirFlowRateperPowerInput, AirFlowFunctionofLoadingandAirTemperatureCurveName, FanPowerInputFunctionofFlowCurveName, DesignEnteringAirTemperature, EnvironmentalClass, AirInletConnectionType, AirInletRoomAirModelNodeName, AirOutletRoomAirModelNodeName, SupplyAirNodeName, DesignRecirculationFraction, RecirculationFunctionofLoadingandSupplyTemperatureCurveName, DesignElectricPowerSupplyEfficiency, ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName, FractionofElectricPowerSupplyLossestoZone, CPUEndUseSubcategory, FanEndUseSubcategory, ElectricPowerSupplyEndUseSubcategory, SupplyTemperatureDifference, SupplyTemperatureDifferenceSchedule, ReturnTemperatureDifference, ReturnTemperatureDifferenceSchedule,   };
  ElectricEquipment_ITE_AirCooledFields()
   : EnumBase<ElectricEquipment_ITE_AirCooledFields>(Name) {} 
  ElectricEquipment_ITE_AirCooledFields(const std::string &t_name) 
   : EnumBase<ElectricEquipment_ITE_AirCooledFields>(t_name) {} 
  ElectricEquipment_ITE_AirCooledFields(int t_value) 
   : EnumBase<ElectricEquipment_ITE_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricEquipment_ITE_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricEquipment_ITE_AirCooledFields>::value()); }
   private:
    friend class EnumBase<ElectricEquipment_ITE_AirCooledFields>;
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
{ ElectricEquipment_ITE_AirCooledFields::Name, "Name", "Name"},
{ ElectricEquipment_ITE_AirCooledFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricEquipment_ITE_AirCooledFields::AirFlowCalculationMethod, "AirFlowCalculationMethod", "Air Flow Calculation Method"},
{ ElectricEquipment_ITE_AirCooledFields::DesignPowerInputCalculationMethod, "DesignPowerInputCalculationMethod", "Design Power Input Calculation Method"},
{ ElectricEquipment_ITE_AirCooledFields::WattsperUnit, "WattsperUnit", "Watts per Unit"},
{ ElectricEquipment_ITE_AirCooledFields::NumberofUnits, "NumberofUnits", "Number of Units"},
{ ElectricEquipment_ITE_AirCooledFields::WattsperZoneFloorArea, "WattsperZoneFloorArea", "Watts per Zone Floor Area"},
{ ElectricEquipment_ITE_AirCooledFields::DesignPowerInputScheduleName, "DesignPowerInputScheduleName", "Design Power Input Schedule Name"},
{ ElectricEquipment_ITE_AirCooledFields::CPULoadingScheduleName, "CPULoadingScheduleName", "CPU Loading  Schedule Name"},
{ ElectricEquipment_ITE_AirCooledFields::CPUPowerInputFunctionofLoadingandAirTemperatureCurveName, "CPUPowerInputFunctionofLoadingandAirTemperatureCurveName", "CPU Power Input Function of Loading and Air Temperature Curve Name"},
{ ElectricEquipment_ITE_AirCooledFields::DesignFanPowerInputFraction, "DesignFanPowerInputFraction", "Design Fan Power Input Fraction"},
{ ElectricEquipment_ITE_AirCooledFields::DesignFanAirFlowRateperPowerInput, "DesignFanAirFlowRateperPowerInput", "Design Fan Air Flow Rate per Power Input"},
{ ElectricEquipment_ITE_AirCooledFields::AirFlowFunctionofLoadingandAirTemperatureCurveName, "AirFlowFunctionofLoadingandAirTemperatureCurveName", "Air Flow Function of Loading and Air Temperature Curve Name"},
{ ElectricEquipment_ITE_AirCooledFields::FanPowerInputFunctionofFlowCurveName, "FanPowerInputFunctionofFlowCurveName", "Fan Power Input Function of Flow Curve Name"},
{ ElectricEquipment_ITE_AirCooledFields::DesignEnteringAirTemperature, "DesignEnteringAirTemperature", "Design Entering Air Temperature"},
{ ElectricEquipment_ITE_AirCooledFields::EnvironmentalClass, "EnvironmentalClass", "Environmental Class"},
{ ElectricEquipment_ITE_AirCooledFields::AirInletConnectionType, "AirInletConnectionType", "Air Inlet Connection Type"},
{ ElectricEquipment_ITE_AirCooledFields::AirInletRoomAirModelNodeName, "AirInletRoomAirModelNodeName", "Air Inlet Room Air Model Node Name"},
{ ElectricEquipment_ITE_AirCooledFields::AirOutletRoomAirModelNodeName, "AirOutletRoomAirModelNodeName", "Air Outlet Room Air Model Node Name"},
{ ElectricEquipment_ITE_AirCooledFields::SupplyAirNodeName, "SupplyAirNodeName", "Supply Air Node Name"},
{ ElectricEquipment_ITE_AirCooledFields::DesignRecirculationFraction, "DesignRecirculationFraction", "Design Recirculation Fraction"},
{ ElectricEquipment_ITE_AirCooledFields::RecirculationFunctionofLoadingandSupplyTemperatureCurveName, "RecirculationFunctionofLoadingandSupplyTemperatureCurveName", "Recirculation Function of Loading and Supply Temperature Curve Name"},
{ ElectricEquipment_ITE_AirCooledFields::DesignElectricPowerSupplyEfficiency, "DesignElectricPowerSupplyEfficiency", "Design Electric Power Supply Efficiency"},
{ ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName, "ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName", "Electric Power Supply Efficiency Function of Part Load Ratio Curve Name"},
{ ElectricEquipment_ITE_AirCooledFields::FractionofElectricPowerSupplyLossestoZone, "FractionofElectricPowerSupplyLossestoZone", "Fraction of Electric Power Supply Losses to Zone"},
{ ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory, "CPUEndUseSubcategory", "CPU End-Use Subcategory"},
{ ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory, "FanEndUseSubcategory", "Fan End-Use Subcategory"},
{ ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory, "ElectricPowerSupplyEndUseSubcategory", "Electric Power Supply End-Use Subcategory"},
{ ElectricEquipment_ITE_AirCooledFields::SupplyTemperatureDifference, "SupplyTemperatureDifference", "Supply Temperature Difference"},
{ ElectricEquipment_ITE_AirCooledFields::SupplyTemperatureDifferenceSchedule, "SupplyTemperatureDifferenceSchedule", "Supply Temperature Difference Schedule"},
{ ElectricEquipment_ITE_AirCooledFields::ReturnTemperatureDifference, "ReturnTemperatureDifference", "Return Temperature Difference"},
{ ElectricEquipment_ITE_AirCooledFields::ReturnTemperatureDifferenceSchedule, "ReturnTemperatureDifferenceSchedule", "Return Temperature Difference Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricEquipment_ITE_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricEquipment_ITE_AirCooledFields> OptionalElectricEquipment_ITE_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICEQUIPMENT_ITE_AIRCOOLED_FIELDENUMS_HXX
