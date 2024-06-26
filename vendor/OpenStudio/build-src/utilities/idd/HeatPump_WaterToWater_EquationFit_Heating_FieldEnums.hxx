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

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_EquationFit_HeatingFields
 *  \brief Enumeration of HeatPump:WaterToWater:EquationFit:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_EquationFit_HeatingFields, )
#else
class HeatPump_WaterToWater_EquationFit_HeatingFields: public ::EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, ReferenceLoadSideFlowRate, ReferenceSourceSideFlowRate, ReferenceHeatingCapacity, ReferenceHeatingPowerConsumption, HeatingCapacityCoefficient1, HeatingCapacityCoefficient2, HeatingCapacityCoefficient3, HeatingCapacityCoefficient4, HeatingCapacityCoefficient5, HeatingCompressorPowerCoefficient1, HeatingCompressorPowerCoefficient2, HeatingCompressorPowerCoefficient3, HeatingCompressorPowerCoefficient4, HeatingCompressorPowerCoefficient5, ReferenceCoefficientofPerformance, SizingFactor, CompanionCoolingHeatPumpName,   };
  HeatPump_WaterToWater_EquationFit_HeatingFields()
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(Name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_EquationFit_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>;
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
{ HeatPump_WaterToWater_EquationFit_HeatingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, "ReferenceLoadSideFlowRate", "Reference Load Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, "ReferenceSourceSideFlowRate", "Reference Source Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, "ReferenceHeatingCapacity", "Reference Heating Capacity"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, "ReferenceHeatingPowerConsumption", "Reference Heating Power Consumption"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient1, "HeatingCapacityCoefficient1", "Heating Capacity Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient2, "HeatingCapacityCoefficient2", "Heating Capacity Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient3, "HeatingCapacityCoefficient3", "Heating Capacity Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient4, "HeatingCapacityCoefficient4", "Heating Capacity Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient5, "HeatingCapacityCoefficient5", "Heating Capacity Coefficient 5"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient1, "HeatingCompressorPowerCoefficient1", "Heating Compressor Power Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient2, "HeatingCompressorPowerCoefficient2", "Heating Compressor Power Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient3, "HeatingCompressorPowerCoefficient3", "Heating Compressor Power Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient4, "HeatingCompressorPowerCoefficient4", "Heating Compressor Power Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient5, "HeatingCompressorPowerCoefficient5", "Heating Compressor Power Coefficient 5"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName, "CompanionCoolingHeatPumpName", "Companion Cooling Heat Pump Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_EquationFit_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_EquationFit_HeatingFields> OptionalHeatPump_WaterToWater_EquationFit_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
