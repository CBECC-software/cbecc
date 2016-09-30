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

#ifndef UTILITIES_IDD_PLANTLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantLoopFields
 *  \brief Enumeration of PlantLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantLoopFields, )
#else
class PlantLoopFields: public ::EnumBase<PlantLoopFields> {
 public: 
  enum domain 
  {
Name, FluidType, UserDefinedFluidType, PlantEquipmentOperationSchemeName, LoopTemperatureSetpointNodeName, MaximumLoopTemperature, MinimumLoopTemperature, MaximumLoopFlowRate, MinimumLoopFlowRate, PlantLoopVolume, PlantSideInletNodeName, PlantSideOutletNodeName, PlantSideBranchListName, PlantSideConnectorListName, DemandSideInletNodeName, DemandSideOutletNodeName, DemandSideBranchListName, DemandSideConnectorListName, LoadDistributionScheme, AvailabilityManagerListName, PlantLoopDemandCalculationScheme, CommonPipeSimulation, PressureSimulationType,   };
  PlantLoopFields()
   : EnumBase<PlantLoopFields>(Name) {} 
  PlantLoopFields(const std::string &t_name) 
   : EnumBase<PlantLoopFields>(t_name) {} 
  PlantLoopFields(int t_value) 
   : EnumBase<PlantLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantLoopFields>::value()); }
   private:
    friend class EnumBase<PlantLoopFields>;
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
{ PlantLoopFields::Name, "Name", "Name"},
{ PlantLoopFields::FluidType, "FluidType", "Fluid Type"},
{ PlantLoopFields::UserDefinedFluidType, "UserDefinedFluidType", "User Defined Fluid Type"},
{ PlantLoopFields::PlantEquipmentOperationSchemeName, "PlantEquipmentOperationSchemeName", "Plant Equipment Operation Scheme Name"},
{ PlantLoopFields::LoopTemperatureSetpointNodeName, "LoopTemperatureSetpointNodeName", "Loop Temperature Setpoint Node Name"},
{ PlantLoopFields::MaximumLoopTemperature, "MaximumLoopTemperature", "Maximum Loop Temperature"},
{ PlantLoopFields::MinimumLoopTemperature, "MinimumLoopTemperature", "Minimum Loop Temperature"},
{ PlantLoopFields::MaximumLoopFlowRate, "MaximumLoopFlowRate", "Maximum Loop Flow Rate"},
{ PlantLoopFields::MinimumLoopFlowRate, "MinimumLoopFlowRate", "Minimum Loop Flow Rate"},
{ PlantLoopFields::PlantLoopVolume, "PlantLoopVolume", "Plant Loop Volume"},
{ PlantLoopFields::PlantSideInletNodeName, "PlantSideInletNodeName", "Plant Side Inlet Node Name"},
{ PlantLoopFields::PlantSideOutletNodeName, "PlantSideOutletNodeName", "Plant Side Outlet Node Name"},
{ PlantLoopFields::PlantSideBranchListName, "PlantSideBranchListName", "Plant Side Branch List Name"},
{ PlantLoopFields::PlantSideConnectorListName, "PlantSideConnectorListName", "Plant Side Connector List Name"},
{ PlantLoopFields::DemandSideInletNodeName, "DemandSideInletNodeName", "Demand Side Inlet Node Name"},
{ PlantLoopFields::DemandSideOutletNodeName, "DemandSideOutletNodeName", "Demand Side Outlet Node Name"},
{ PlantLoopFields::DemandSideBranchListName, "DemandSideBranchListName", "Demand Side Branch List Name"},
{ PlantLoopFields::DemandSideConnectorListName, "DemandSideConnectorListName", "Demand Side Connector List Name"},
{ PlantLoopFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
{ PlantLoopFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ PlantLoopFields::PlantLoopDemandCalculationScheme, "PlantLoopDemandCalculationScheme", "Plant Loop Demand Calculation Scheme"},
{ PlantLoopFields::CommonPipeSimulation, "CommonPipeSimulation", "Common Pipe Simulation"},
{ PlantLoopFields::PressureSimulationType, "PressureSimulationType", "Pressure Simulation Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantLoopFields> OptionalPlantLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTLOOP_FIELDENUMS_HXX
