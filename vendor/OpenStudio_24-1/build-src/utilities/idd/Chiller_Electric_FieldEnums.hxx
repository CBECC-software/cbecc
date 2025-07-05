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

#ifndef UTILITIES_IDD_CHILLER_ELECTRIC_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ELECTRIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_ElectricFields
 *  \brief Enumeration of Chiller:Electric's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_ElectricFields, )
#else
class Chiller_ElectricFields: public ::EnumBase<Chiller_ElectricFields> {
 public: 
  enum domain 
  {
Name, CondenserType, NominalCapacity, NominalCOP, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, TemperatureRiseCoefficient, DesignChilledWaterOutletTemperature, DesignChilledWaterFlowRate, DesignCondenserFluidFlowRate, Coefficient1ofCapacityRatioCurve, Coefficient2ofCapacityRatioCurve, Coefficient3ofCapacityRatioCurve, Coefficient1ofPowerRatioCurve, Coefficient2ofPowerRatioCurve, Coefficient3ofPowerRatioCurve, Coefficient1ofFullLoadRatioCurve, Coefficient2ofFullLoadRatioCurve, Coefficient3ofFullLoadRatioCurve, ChilledWaterOutletTemperatureLowerLimit, ChillerFlowMode, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, CondenserHeatRecoveryRelativeCapacityFraction, HeatRecoveryInletHighTemperatureLimitScheduleName, HeatRecoveryLeavingTemperatureSetpointNodeName, EndUseSubcategory,   };
  Chiller_ElectricFields()
   : EnumBase<Chiller_ElectricFields>(Name) {} 
  Chiller_ElectricFields(const std::string &t_name) 
   : EnumBase<Chiller_ElectricFields>(t_name) {} 
  Chiller_ElectricFields(int t_value) 
   : EnumBase<Chiller_ElectricFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_ElectricFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_ElectricFields>::value()); }
   private:
    friend class EnumBase<Chiller_ElectricFields>;
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
{ Chiller_ElectricFields::Name, "Name", "Name"},
{ Chiller_ElectricFields::CondenserType, "CondenserType", "Condenser Type"},
{ Chiller_ElectricFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_ElectricFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ Chiller_ElectricFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_ElectricFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_ElectricFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_ElectricFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_ElectricFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_ElectricFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_ElectricFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_ElectricFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_ElectricFields::TemperatureRiseCoefficient, "TemperatureRiseCoefficient", "Temperature Rise Coefficient"},
{ Chiller_ElectricFields::DesignChilledWaterOutletTemperature, "DesignChilledWaterOutletTemperature", "Design Chilled Water Outlet Temperature"},
{ Chiller_ElectricFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_ElectricFields::DesignCondenserFluidFlowRate, "DesignCondenserFluidFlowRate", "Design Condenser Fluid Flow Rate"},
{ Chiller_ElectricFields::Coefficient1ofCapacityRatioCurve, "Coefficient1ofCapacityRatioCurve", "Coefficient 1 of Capacity Ratio Curve"},
{ Chiller_ElectricFields::Coefficient2ofCapacityRatioCurve, "Coefficient2ofCapacityRatioCurve", "Coefficient 2 of Capacity Ratio Curve"},
{ Chiller_ElectricFields::Coefficient3ofCapacityRatioCurve, "Coefficient3ofCapacityRatioCurve", "Coefficient 3 of Capacity Ratio Curve"},
{ Chiller_ElectricFields::Coefficient1ofPowerRatioCurve, "Coefficient1ofPowerRatioCurve", "Coefficient 1 of Power Ratio Curve"},
{ Chiller_ElectricFields::Coefficient2ofPowerRatioCurve, "Coefficient2ofPowerRatioCurve", "Coefficient 2 of Power Ratio Curve"},
{ Chiller_ElectricFields::Coefficient3ofPowerRatioCurve, "Coefficient3ofPowerRatioCurve", "Coefficient 3 of Power Ratio Curve"},
{ Chiller_ElectricFields::Coefficient1ofFullLoadRatioCurve, "Coefficient1ofFullLoadRatioCurve", "Coefficient 1 of Full Load Ratio Curve"},
{ Chiller_ElectricFields::Coefficient2ofFullLoadRatioCurve, "Coefficient2ofFullLoadRatioCurve", "Coefficient 2 of Full Load Ratio Curve"},
{ Chiller_ElectricFields::Coefficient3ofFullLoadRatioCurve, "Coefficient3ofFullLoadRatioCurve", "Coefficient 3 of Full Load Ratio Curve"},
{ Chiller_ElectricFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_ElectricFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Chiller_ElectricFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_ElectricFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_ElectricFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_ElectricFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Chiller_ElectricFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Chiller_ElectricFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Chiller_ElectricFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ Chiller_ElectricFields::HeatRecoveryInletHighTemperatureLimitScheduleName, "HeatRecoveryInletHighTemperatureLimitScheduleName", "Heat Recovery Inlet High Temperature Limit Schedule Name"},
{ Chiller_ElectricFields::HeatRecoveryLeavingTemperatureSetpointNodeName, "HeatRecoveryLeavingTemperatureSetpointNodeName", "Heat Recovery Leaving Temperature Setpoint Node Name"},
{ Chiller_ElectricFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_ElectricFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_ElectricFields> OptionalChiller_ElectricFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ELECTRIC_FIELDENUMS_HXX
