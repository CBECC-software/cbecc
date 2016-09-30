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

#ifndef UTILITIES_IDD_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_FluidToFluidFields
 *  \brief Enumeration of HeatExchanger:FluidToFluid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatExchanger_FluidToFluidFields, )
#else
class HeatExchanger_FluidToFluidFields: public ::EnumBase<HeatExchanger_FluidToFluidFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, LoopDemandSideInletNodeName, LoopDemandSideOutletNodeName, LoopDemandSideDesignFlowRate, LoopSupplySideInletNodeName, LoopSupplySideOutletNodeName, LoopSupplySideDesignFlowRate, HeatExchangeModelType, HeatExchangerUFactorTimesAreaValue, ControlType, HeatExchangerSetpointNodeName, MinimumTemperatureDifferencetoActivateHeatExchanger, HeatTransferMeteringEndUseType, ComponentOverrideLoopSupplySideInletNodeName, ComponentOverrideLoopDemandSideInletNodeName, ComponentOverrideCoolingControlTemperatureMode, SizingFactor, OperationMinimumTemperatureLimit, OperationMaximumTemperatureLimit,   };
  HeatExchanger_FluidToFluidFields()
   : EnumBase<HeatExchanger_FluidToFluidFields>(Name) {} 
  HeatExchanger_FluidToFluidFields(const std::string &t_name) 
   : EnumBase<HeatExchanger_FluidToFluidFields>(t_name) {} 
  HeatExchanger_FluidToFluidFields(int t_value) 
   : EnumBase<HeatExchanger_FluidToFluidFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatExchanger_FluidToFluidFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatExchanger_FluidToFluidFields>::value()); }
   private:
    friend class EnumBase<HeatExchanger_FluidToFluidFields>;
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
{ HeatExchanger_FluidToFluidFields::Name, "Name", "Name"},
{ HeatExchanger_FluidToFluidFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ HeatExchanger_FluidToFluidFields::LoopDemandSideInletNodeName, "LoopDemandSideInletNodeName", "Loop Demand Side Inlet Node Name"},
{ HeatExchanger_FluidToFluidFields::LoopDemandSideOutletNodeName, "LoopDemandSideOutletNodeName", "Loop Demand Side Outlet Node Name"},
{ HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, "LoopDemandSideDesignFlowRate", "Loop Demand Side Design Flow Rate"},
{ HeatExchanger_FluidToFluidFields::LoopSupplySideInletNodeName, "LoopSupplySideInletNodeName", "Loop Supply Side Inlet Node Name"},
{ HeatExchanger_FluidToFluidFields::LoopSupplySideOutletNodeName, "LoopSupplySideOutletNodeName", "Loop Supply Side Outlet Node Name"},
{ HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, "LoopSupplySideDesignFlowRate", "Loop Supply Side Design Flow Rate"},
{ HeatExchanger_FluidToFluidFields::HeatExchangeModelType, "HeatExchangeModelType", "Heat Exchange Model Type"},
{ HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, "HeatExchangerUFactorTimesAreaValue", "Heat Exchanger U-Factor Times Area Value"},
{ HeatExchanger_FluidToFluidFields::ControlType, "ControlType", "Control Type"},
{ HeatExchanger_FluidToFluidFields::HeatExchangerSetpointNodeName, "HeatExchangerSetpointNodeName", "Heat Exchanger Setpoint Node Name"},
{ HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger, "MinimumTemperatureDifferencetoActivateHeatExchanger", "Minimum Temperature Difference to Activate Heat Exchanger"},
{ HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType, "HeatTransferMeteringEndUseType", "Heat Transfer Metering End Use Type"},
{ HeatExchanger_FluidToFluidFields::ComponentOverrideLoopSupplySideInletNodeName, "ComponentOverrideLoopSupplySideInletNodeName", "Component Override Loop Supply Side Inlet Node Name"},
{ HeatExchanger_FluidToFluidFields::ComponentOverrideLoopDemandSideInletNodeName, "ComponentOverrideLoopDemandSideInletNodeName", "Component Override Loop Demand Side Inlet Node Name"},
{ HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode, "ComponentOverrideCoolingControlTemperatureMode", "Component Override Cooling Control Temperature Mode"},
{ HeatExchanger_FluidToFluidFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatExchanger_FluidToFluidFields::OperationMinimumTemperatureLimit, "OperationMinimumTemperatureLimit", "Operation Minimum Temperature Limit"},
{ HeatExchanger_FluidToFluidFields::OperationMaximumTemperatureLimit, "OperationMaximumTemperatureLimit", "Operation Maximum Temperature Limit"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatExchanger_FluidToFluidFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatExchanger_FluidToFluidFields> OptionalHeatExchanger_FluidToFluidFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX
