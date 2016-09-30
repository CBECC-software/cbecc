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

#ifndef UTILITIES_IDD_CONDENSERLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_CONDENSERLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CondenserLoopFields
 *  \brief Enumeration of CondenserLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CondenserLoopFields, )
#else
class CondenserLoopFields: public ::EnumBase<CondenserLoopFields> {
 public: 
  enum domain 
  {
Name, FluidType, UserDefinedFluidType, CondenserEquipmentOperationSchemeName, CondenserLoopTemperatureSetpointNodeName, MaximumLoopTemperature, MinimumLoopTemperature, MaximumLoopFlowRate, MinimumLoopFlowRate, CondenserLoopVolume, CondenserSideInletNodeName, CondenserSideOutletNodeName, CondenserSideBranchListName, CondenserSideConnectorListName, DemandSideInletNodeName, DemandSideOutletNodeName, CondenserDemandSideBranchListName, CondenserDemandSideConnectorListName, LoadDistributionScheme, PressureSimulationType,   };
  CondenserLoopFields()
   : EnumBase<CondenserLoopFields>(Name) {} 
  CondenserLoopFields(const std::string &t_name) 
   : EnumBase<CondenserLoopFields>(t_name) {} 
  CondenserLoopFields(int t_value) 
   : EnumBase<CondenserLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "CondenserLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CondenserLoopFields>::value()); }
   private:
    friend class EnumBase<CondenserLoopFields>;
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
{ CondenserLoopFields::Name, "Name", "Name"},
{ CondenserLoopFields::FluidType, "FluidType", "Fluid Type"},
{ CondenserLoopFields::UserDefinedFluidType, "UserDefinedFluidType", "User Defined Fluid Type"},
{ CondenserLoopFields::CondenserEquipmentOperationSchemeName, "CondenserEquipmentOperationSchemeName", "Condenser Equipment Operation Scheme Name"},
{ CondenserLoopFields::CondenserLoopTemperatureSetpointNodeName, "CondenserLoopTemperatureSetpointNodeName", "Condenser Loop Temperature Setpoint Node Name"},
{ CondenserLoopFields::MaximumLoopTemperature, "MaximumLoopTemperature", "Maximum Loop Temperature"},
{ CondenserLoopFields::MinimumLoopTemperature, "MinimumLoopTemperature", "Minimum Loop Temperature"},
{ CondenserLoopFields::MaximumLoopFlowRate, "MaximumLoopFlowRate", "Maximum Loop Flow Rate"},
{ CondenserLoopFields::MinimumLoopFlowRate, "MinimumLoopFlowRate", "Minimum Loop Flow Rate"},
{ CondenserLoopFields::CondenserLoopVolume, "CondenserLoopVolume", "Condenser Loop Volume"},
{ CondenserLoopFields::CondenserSideInletNodeName, "CondenserSideInletNodeName", "Condenser Side Inlet Node Name"},
{ CondenserLoopFields::CondenserSideOutletNodeName, "CondenserSideOutletNodeName", "Condenser Side Outlet Node Name"},
{ CondenserLoopFields::CondenserSideBranchListName, "CondenserSideBranchListName", "Condenser Side Branch List Name"},
{ CondenserLoopFields::CondenserSideConnectorListName, "CondenserSideConnectorListName", "Condenser Side Connector List Name"},
{ CondenserLoopFields::DemandSideInletNodeName, "DemandSideInletNodeName", "Demand Side Inlet Node Name"},
{ CondenserLoopFields::DemandSideOutletNodeName, "DemandSideOutletNodeName", "Demand Side Outlet Node Name"},
{ CondenserLoopFields::CondenserDemandSideBranchListName, "CondenserDemandSideBranchListName", "Condenser Demand Side Branch List Name"},
{ CondenserLoopFields::CondenserDemandSideConnectorListName, "CondenserDemandSideConnectorListName", "Condenser Demand Side Connector List Name"},
{ CondenserLoopFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
{ CondenserLoopFields::PressureSimulationType, "PressureSimulationType", "Pressure Simulation Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const CondenserLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CondenserLoopFields> OptionalCondenserLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONDENSERLOOP_FIELDENUMS_HXX
