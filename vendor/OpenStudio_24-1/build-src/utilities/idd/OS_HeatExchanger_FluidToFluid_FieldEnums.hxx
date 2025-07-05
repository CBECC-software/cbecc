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

#ifndef UTILITIES_IDD_OS_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatExchanger_FluidToFluidFields
 *  \brief Enumeration of OS:HeatExchanger:FluidToFluid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatExchanger_FluidToFluidFields, )
#else
class OS_HeatExchanger_FluidToFluidFields: public ::EnumBase<OS_HeatExchanger_FluidToFluidFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, LoopDemandSideInletNode, LoopDemandSideOutletNode, LoopDemandSideDesignFlowRate, LoopSupplySideInletNode, LoopSupplySideOutletNode, LoopSupplySideDesignFlowRate, HeatExchangeModelType, HeatExchangerUFactorTimesAreaValue, ControlType, HeatExchangerSetpointNodeName, MinimumTemperatureDifferencetoActivateHeatExchanger, HeatTransferMeteringEndUseType, ComponentOverrideLoopSupplySideInletNode, ComponentOverrideLoopDemandSideInletNode, ComponentOverrideCoolingControlTemperatureMode, SizingFactor, OperationMinimumTemperatureLimit, OperationMaximumTemperatureLimit,   };
  OS_HeatExchanger_FluidToFluidFields()
   : EnumBase<OS_HeatExchanger_FluidToFluidFields>(Handle) {} 
  OS_HeatExchanger_FluidToFluidFields(const std::string &t_name) 
   : EnumBase<OS_HeatExchanger_FluidToFluidFields>(t_name) {} 
  OS_HeatExchanger_FluidToFluidFields(int t_value) 
   : EnumBase<OS_HeatExchanger_FluidToFluidFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatExchanger_FluidToFluidFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatExchanger_FluidToFluidFields>::value()); }
   private:
    friend class EnumBase<OS_HeatExchanger_FluidToFluidFields>;
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
{ OS_HeatExchanger_FluidToFluidFields::Handle, "Handle", "Handle"},
{ OS_HeatExchanger_FluidToFluidFields::Name, "Name", "Name"},
{ OS_HeatExchanger_FluidToFluidFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_HeatExchanger_FluidToFluidFields::LoopDemandSideInletNode, "LoopDemandSideInletNode", "Loop Demand Side Inlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::LoopDemandSideOutletNode, "LoopDemandSideOutletNode", "Loop Demand Side Outlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, "LoopDemandSideDesignFlowRate", "Loop Demand Side Design Flow Rate"},
{ OS_HeatExchanger_FluidToFluidFields::LoopSupplySideInletNode, "LoopSupplySideInletNode", "Loop Supply Side Inlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::LoopSupplySideOutletNode, "LoopSupplySideOutletNode", "Loop Supply Side Outlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, "LoopSupplySideDesignFlowRate", "Loop Supply Side Design Flow Rate"},
{ OS_HeatExchanger_FluidToFluidFields::HeatExchangeModelType, "HeatExchangeModelType", "Heat Exchange Model Type"},
{ OS_HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, "HeatExchangerUFactorTimesAreaValue", "Heat Exchanger U-Factor Times Area Value"},
{ OS_HeatExchanger_FluidToFluidFields::ControlType, "ControlType", "Control Type"},
{ OS_HeatExchanger_FluidToFluidFields::HeatExchangerSetpointNodeName, "HeatExchangerSetpointNodeName", "Heat Exchanger Setpoint Node Name"},
{ OS_HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger, "MinimumTemperatureDifferencetoActivateHeatExchanger", "Minimum Temperature Difference to Activate Heat Exchanger"},
{ OS_HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType, "HeatTransferMeteringEndUseType", "Heat Transfer Metering End Use Type"},
{ OS_HeatExchanger_FluidToFluidFields::ComponentOverrideLoopSupplySideInletNode, "ComponentOverrideLoopSupplySideInletNode", "Component Override Loop Supply Side Inlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::ComponentOverrideLoopDemandSideInletNode, "ComponentOverrideLoopDemandSideInletNode", "Component Override Loop Demand Side Inlet Node"},
{ OS_HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode, "ComponentOverrideCoolingControlTemperatureMode", "Component Override Cooling Control Temperature Mode"},
{ OS_HeatExchanger_FluidToFluidFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_HeatExchanger_FluidToFluidFields::OperationMinimumTemperatureLimit, "OperationMinimumTemperatureLimit", "Operation Minimum Temperature Limit"},
{ OS_HeatExchanger_FluidToFluidFields::OperationMaximumTemperatureLimit, "OperationMaximumTemperatureLimit", "Operation Maximum Temperature Limit"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatExchanger_FluidToFluidFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatExchanger_FluidToFluidFields> OptionalOS_HeatExchanger_FluidToFluidFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATEXCHANGER_FLUIDTOFLUID_FIELDENUMS_HXX
