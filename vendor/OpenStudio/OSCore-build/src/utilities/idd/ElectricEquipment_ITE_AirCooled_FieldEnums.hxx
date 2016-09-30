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
Name, ZoneName, DesignPowerInputCalculationMethod, WattsperUnit, NumberofUnits, WattsperZoneFloorArea, DesignPowerInputScheduleName, CPULoadingScheduleName, CPUPowerInputFunctionofLoadingandAirTemperatureCurveName, DesignFanPowerInputFraction, DesignFanAirFlowRateperPowerInput, AirFlowFunctionofLoadingandAirTemperatureCurveName, FanPowerInputFunctionofFlowCurveName, DesignEnteringAirTemperature, EnvironmentalClass, AirInletConnectionType, AirInletRoomAirModelNodeName, AirOutletRoomAirModelNodeName, SupplyAirNodeName, DesignRecirculationFraction, RecirculationFunctionofLoadingandSupplyTemperatureCurveName, DesignElectricPowerSupplyEfficiency, ElectricPowerSupplyEfficiencyFunctionofPartLoadRatioCurveName, FractionofElectricPowerSupplyLossestoZone, CPUEndUseSubcategory, FanEndUseSubcategory, ElectricPowerSupplyEndUseSubcategory,   };
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
