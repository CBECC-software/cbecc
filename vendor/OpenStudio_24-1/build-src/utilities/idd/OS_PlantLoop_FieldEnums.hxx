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

#ifndef UTILITIES_IDD_OS_PLANTLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PLANTLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PlantLoopFields
 *  \brief Enumeration of OS:PlantLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PlantLoopFields, )
#else
class OS_PlantLoopFields: public ::EnumBase<OS_PlantLoopFields> {
 public: 
  enum domain 
  {
Handle, Name, FluidType, GlycolConcentration, UserDefinedFluidType, PlantEquipmentOperationHeatingLoad, PlantEquipmentOperationCoolingLoad, PrimaryPlantEquipmentOperationScheme, LoopTemperatureSetpointNodeName, MaximumLoopTemperature, MinimumLoopTemperature, MaximumLoopFlowRate, MinimumLoopFlowRate, PlantLoopVolume, PlantSideInletNodeName, PlantSideOutletNodeName, PlantSideBranchListName, DemandSideInletNodeName, DemandSideOutletNodeName, DemandSideBranchListName, DemandSideConnectorListName, LoadDistributionScheme, AvailabilityManagerListName, PlantLoopDemandCalculationScheme, CommonPipeSimulation, PressureSimulationType, PlantEquipmentOperationHeatingLoadSchedule, PlantEquipmentOperationCoolingLoadSchedule, PrimaryPlantEquipmentOperationSchemeSchedule, ComponentSetpointOperationSchemeSchedule, DemandMixerName, DemandSplitterName, SupplyMixerName, SupplySplitterName,   };
  OS_PlantLoopFields()
   : EnumBase<OS_PlantLoopFields>(Handle) {} 
  OS_PlantLoopFields(const std::string &t_name) 
   : EnumBase<OS_PlantLoopFields>(t_name) {} 
  OS_PlantLoopFields(int t_value) 
   : EnumBase<OS_PlantLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantLoopFields>::value()); }
   private:
    friend class EnumBase<OS_PlantLoopFields>;
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
{ OS_PlantLoopFields::Handle, "Handle", "Handle"},
{ OS_PlantLoopFields::Name, "Name", "Name"},
{ OS_PlantLoopFields::FluidType, "FluidType", "Fluid Type"},
{ OS_PlantLoopFields::GlycolConcentration, "GlycolConcentration", "Glycol Concentration"},
{ OS_PlantLoopFields::UserDefinedFluidType, "UserDefinedFluidType", "User Defined Fluid Type"},
{ OS_PlantLoopFields::PlantEquipmentOperationHeatingLoad, "PlantEquipmentOperationHeatingLoad", "Plant Equipment Operation Heating Load"},
{ OS_PlantLoopFields::PlantEquipmentOperationCoolingLoad, "PlantEquipmentOperationCoolingLoad", "Plant Equipment Operation Cooling Load"},
{ OS_PlantLoopFields::PrimaryPlantEquipmentOperationScheme, "PrimaryPlantEquipmentOperationScheme", "Primary Plant Equipment Operation Scheme"},
{ OS_PlantLoopFields::LoopTemperatureSetpointNodeName, "LoopTemperatureSetpointNodeName", "Loop Temperature Setpoint Node Name"},
{ OS_PlantLoopFields::MaximumLoopTemperature, "MaximumLoopTemperature", "Maximum Loop Temperature"},
{ OS_PlantLoopFields::MinimumLoopTemperature, "MinimumLoopTemperature", "Minimum Loop Temperature"},
{ OS_PlantLoopFields::MaximumLoopFlowRate, "MaximumLoopFlowRate", "Maximum Loop Flow Rate"},
{ OS_PlantLoopFields::MinimumLoopFlowRate, "MinimumLoopFlowRate", "Minimum Loop Flow Rate"},
{ OS_PlantLoopFields::PlantLoopVolume, "PlantLoopVolume", "Plant Loop Volume"},
{ OS_PlantLoopFields::PlantSideInletNodeName, "PlantSideInletNodeName", "Plant Side Inlet Node Name"},
{ OS_PlantLoopFields::PlantSideOutletNodeName, "PlantSideOutletNodeName", "Plant Side Outlet Node Name"},
{ OS_PlantLoopFields::PlantSideBranchListName, "PlantSideBranchListName", "Plant Side Branch List Name"},
{ OS_PlantLoopFields::DemandSideInletNodeName, "DemandSideInletNodeName", "Demand Side Inlet Node Name"},
{ OS_PlantLoopFields::DemandSideOutletNodeName, "DemandSideOutletNodeName", "Demand Side Outlet Node Name"},
{ OS_PlantLoopFields::DemandSideBranchListName, "DemandSideBranchListName", "Demand Side Branch List Name"},
{ OS_PlantLoopFields::DemandSideConnectorListName, "DemandSideConnectorListName", "Demand Side Connector List Name"},
{ OS_PlantLoopFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
{ OS_PlantLoopFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ OS_PlantLoopFields::PlantLoopDemandCalculationScheme, "PlantLoopDemandCalculationScheme", "Plant Loop Demand Calculation Scheme"},
{ OS_PlantLoopFields::CommonPipeSimulation, "CommonPipeSimulation", "Common Pipe Simulation"},
{ OS_PlantLoopFields::PressureSimulationType, "PressureSimulationType", "Pressure Simulation Type"},
{ OS_PlantLoopFields::PlantEquipmentOperationHeatingLoadSchedule, "PlantEquipmentOperationHeatingLoadSchedule", "Plant Equipment Operation Heating Load Schedule"},
{ OS_PlantLoopFields::PlantEquipmentOperationCoolingLoadSchedule, "PlantEquipmentOperationCoolingLoadSchedule", "Plant Equipment Operation Cooling Load Schedule"},
{ OS_PlantLoopFields::PrimaryPlantEquipmentOperationSchemeSchedule, "PrimaryPlantEquipmentOperationSchemeSchedule", "Primary Plant Equipment Operation Scheme Schedule"},
{ OS_PlantLoopFields::ComponentSetpointOperationSchemeSchedule, "ComponentSetpointOperationSchemeSchedule", "Component Setpoint Operation Scheme Schedule"},
{ OS_PlantLoopFields::DemandMixerName, "DemandMixerName", "Demand Mixer Name"},
{ OS_PlantLoopFields::DemandSplitterName, "DemandSplitterName", "Demand Splitter Name"},
{ OS_PlantLoopFields::SupplyMixerName, "SupplyMixerName", "Supply Mixer Name"},
{ OS_PlantLoopFields::SupplySplitterName, "SupplySplitterName", "Supply Splitter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantLoopFields> OptionalOS_PlantLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PLANTLOOP_FIELDENUMS_HXX
