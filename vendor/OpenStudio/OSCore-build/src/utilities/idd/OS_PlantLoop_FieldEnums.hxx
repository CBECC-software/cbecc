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
Handle, Name, FluidType, UserDefinedFluidType, PlantEquipmentOperationHeatingLoad, PlantEquipmentOperationCoolingLoad, PrimaryPlantEquipmentOperationScheme, LoopTemperatureSetpointNodeName, MaximumLoopTemperature, MinimumLoopTemperature, MaximumLoopFlowRate, MinimumLoopFlowRate, PlantLoopVolume, PlantSideInletNodeName, PlantSideOutletNodeName, PlantSideBranchListName, DemandSideInletNodeName, DemandSideOutletNodeName, DemandSideBranchListName, DemandSideConnectorListName, LoadDistributionScheme, AvailabilityManagerListName, PlantLoopDemandCalculationScheme, CommonPipeSimulation, PressureSimulationType,   };
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
