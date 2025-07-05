/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_THERMALENERGYSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_THERMALENERGYSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_ThermalEnergyStorageFields
 *  \brief Enumeration of PlantEquipmentOperation:ThermalEnergyStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_ThermalEnergyStorageFields, )
#else
class PlantEquipmentOperation_ThermalEnergyStorageFields: public ::EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields> {
 public: 
  enum domain 
  {
Name, OnPeakSchedule, ChargingAvailabilitySchedule, NonChargingChilledWaterTemperature, ChargingChilledWaterTemperature, Component1ObjectType, Component1Name, Component1DemandCalculationNodeName, Component1SetpointNodeName, Component1FlowRate, Component1OperationType, Component2ObjectType, Component2Name, Component2DemandCalculationNodeName, Component2SetpointNodeName, Component2FlowRate, Component2OperationType, Component3ObjectType, Component3Name, Component3DemandCalculationNodeName, Component3SetpointNodeName, Component3FlowRate, Component3OperationType, Component4ObjectType, Component4Name, Component4DemandCalculationNodeName, Component4SetpointNodeName, Component4FlowRate, Component4OperationType, Component5ObjectType, Component5Name, Component5DemandCalculationNodeName, Component5SetpointNodeName, Component5FlowRate, Component5OperationType, Component6ObjectType, Component6Name, Component6DemandCalculationNodeName, Component6SetpointNodeName, Component6FlowRate, Component6OperationType, Component7ObjectType, Component7Name, Component7DemandCalculationNodeName, Component7SetpointNodeName, Component7FlowRate, Component7OperationType, Component8ObjectType, Component8Name, Component8DemandCalculationNodeName, Component8SetpointNodeName, Component8FlowRate, Component8OperationType, Component9ObjectType, Component9Name, Component9DemandCalculationNodeName, Component9SetpointNodeName, Component9FlowRate, Component9OperationType, Component10ObjectType, Component10Name, Component10DemandCalculationNodeName, Component10SetpointNodeName, Component10FlowRate, Component10OperationType,   };
  PlantEquipmentOperation_ThermalEnergyStorageFields()
   : EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields>(Name) {} 
  PlantEquipmentOperation_ThermalEnergyStorageFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields>(t_name) {} 
  PlantEquipmentOperation_ThermalEnergyStorageFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_ThermalEnergyStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_ThermalEnergyStorageFields>;
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
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Name, "Name", "Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::OnPeakSchedule, "OnPeakSchedule", "On-Peak Schedule"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::ChargingAvailabilitySchedule, "ChargingAvailabilitySchedule", "Charging Availability Schedule"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::NonChargingChilledWaterTemperature, "NonChargingChilledWaterTemperature", "Non-Charging Chilled Water Temperature"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::ChargingChilledWaterTemperature, "ChargingChilledWaterTemperature", "Charging Chilled Water Temperature"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1ObjectType, "Component1ObjectType", "Component 1 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1Name, "Component1Name", "Component 1 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1DemandCalculationNodeName, "Component1DemandCalculationNodeName", "Component 1 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1SetpointNodeName, "Component1SetpointNodeName", "Component 1 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1FlowRate, "Component1FlowRate", "Component 1 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component1OperationType, "Component1OperationType", "Component 1 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2ObjectType, "Component2ObjectType", "Component 2 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2Name, "Component2Name", "Component 2 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2DemandCalculationNodeName, "Component2DemandCalculationNodeName", "Component 2 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2SetpointNodeName, "Component2SetpointNodeName", "Component 2 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, "Component2FlowRate", "Component 2 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component2OperationType, "Component2OperationType", "Component 2 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3ObjectType, "Component3ObjectType", "Component 3 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3Name, "Component3Name", "Component 3 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3DemandCalculationNodeName, "Component3DemandCalculationNodeName", "Component 3 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3SetpointNodeName, "Component3SetpointNodeName", "Component 3 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, "Component3FlowRate", "Component 3 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component3OperationType, "Component3OperationType", "Component 3 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4ObjectType, "Component4ObjectType", "Component 4 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4Name, "Component4Name", "Component 4 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4DemandCalculationNodeName, "Component4DemandCalculationNodeName", "Component 4 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4SetpointNodeName, "Component4SetpointNodeName", "Component 4 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, "Component4FlowRate", "Component 4 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component4OperationType, "Component4OperationType", "Component 4 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5ObjectType, "Component5ObjectType", "Component 5 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5Name, "Component5Name", "Component 5 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5DemandCalculationNodeName, "Component5DemandCalculationNodeName", "Component 5 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5SetpointNodeName, "Component5SetpointNodeName", "Component 5 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, "Component5FlowRate", "Component 5 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component5OperationType, "Component5OperationType", "Component 5 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6ObjectType, "Component6ObjectType", "Component 6 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6Name, "Component6Name", "Component 6 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6DemandCalculationNodeName, "Component6DemandCalculationNodeName", "Component 6 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6SetpointNodeName, "Component6SetpointNodeName", "Component 6 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, "Component6FlowRate", "Component 6 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component6OperationType, "Component6OperationType", "Component 6 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7ObjectType, "Component7ObjectType", "Component 7 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7Name, "Component7Name", "Component 7 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7DemandCalculationNodeName, "Component7DemandCalculationNodeName", "Component 7 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7SetpointNodeName, "Component7SetpointNodeName", "Component 7 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, "Component7FlowRate", "Component 7 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component7OperationType, "Component7OperationType", "Component 7 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8ObjectType, "Component8ObjectType", "Component 8 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8Name, "Component8Name", "Component 8 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8DemandCalculationNodeName, "Component8DemandCalculationNodeName", "Component 8 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8SetpointNodeName, "Component8SetpointNodeName", "Component 8 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, "Component8FlowRate", "Component 8 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component8OperationType, "Component8OperationType", "Component 8 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9ObjectType, "Component9ObjectType", "Component 9 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9Name, "Component9Name", "Component 9 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9DemandCalculationNodeName, "Component9DemandCalculationNodeName", "Component 9 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9SetpointNodeName, "Component9SetpointNodeName", "Component 9 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, "Component9FlowRate", "Component 9 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component9OperationType, "Component9OperationType", "Component 9 Operation Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10ObjectType, "Component10ObjectType", "Component 10 Object Type"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10Name, "Component10Name", "Component 10 Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10DemandCalculationNodeName, "Component10DemandCalculationNodeName", "Component 10 Demand Calculation Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10SetpointNodeName, "Component10SetpointNodeName", "Component 10 Setpoint Node Name"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, "Component10FlowRate", "Component 10 Flow Rate"},
{ PlantEquipmentOperation_ThermalEnergyStorageFields::Component10OperationType, "Component10OperationType", "Component 10 Operation Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_ThermalEnergyStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_ThermalEnergyStorageFields> OptionalPlantEquipmentOperation_ThermalEnergyStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_THERMALENERGYSTORAGE_FIELDENUMS_HXX
