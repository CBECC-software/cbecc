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

#ifndef UTILITIES_IDD_OS_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ChillerHeaterPerformance_Electric_EIRFields
 *  \brief Enumeration of OS:ChillerHeaterPerformance:Electric:EIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ChillerHeaterPerformance_Electric_EIRFields, )
#else
class OS_ChillerHeaterPerformance_Electric_EIRFields: public ::EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceCoolingModeEvaporatorCapacity, ReferenceCoolingModeCOP, ReferenceCoolingModeLeavingChilledWaterTemperature, ReferenceCoolingModeEnteringCondenserFluidTemperature, ReferenceCoolingModeLeavingCondenserWaterTemperature, ReferenceHeatingModeCoolingCapacityRatio, ReferenceHeatingModeCoolingPowerInputRatio, ReferenceHeatingModeLeavingChilledWaterTemperature, ReferenceHeatingModeLeavingCondenserWaterTemperature, ReferenceHeatingModeEnteringCondenserFluidTemperature, HeatingModeEnteringChilledWaterTemperatureLowLimit, ChilledWaterFlowModeType, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, DesignHotWaterFlowRate, CompressorMotorEfficiency, CondenserType, CoolingModeTemperatureCurveCondenserWaterIndependentVariable, CoolingModeCoolingCapacityFunctionofTemperatureCurveName, CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, CoolingModeCoolingCapacityOptimumPartLoadRatio, HeatingModeTemperatureCurveCondenserWaterIndependentVariable, HeatingModeCoolingCapacityFunctionofTemperatureCurveName, HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, HeatingModeCoolingCapacityOptimumPartLoadRatio, SizingFactor,   };
  OS_ChillerHeaterPerformance_Electric_EIRFields()
   : EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields>(Handle) {} 
  OS_ChillerHeaterPerformance_Electric_EIRFields(const std::string &t_name) 
   : EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields>(t_name) {} 
  OS_ChillerHeaterPerformance_Electric_EIRFields(int t_value) 
   : EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ChillerHeaterPerformance_Electric_EIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields>::value()); }
   private:
    friend class EnumBase<OS_ChillerHeaterPerformance_Electric_EIRFields>;
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
{ OS_ChillerHeaterPerformance_Electric_EIRFields::Handle, "Handle", "Handle"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::Name, "Name", "Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity, "ReferenceCoolingModeEvaporatorCapacity", "Reference Cooling Mode Evaporator Capacity"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeCOP, "ReferenceCoolingModeCOP", "Reference Cooling Mode COP"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingChilledWaterTemperature, "ReferenceCoolingModeLeavingChilledWaterTemperature", "Reference Cooling Mode Leaving Chilled Water Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEnteringCondenserFluidTemperature, "ReferenceCoolingModeEnteringCondenserFluidTemperature", "Reference Cooling Mode Entering Condenser Fluid Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingCondenserWaterTemperature, "ReferenceCoolingModeLeavingCondenserWaterTemperature", "Reference Cooling Mode Leaving Condenser Water Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingCapacityRatio, "ReferenceHeatingModeCoolingCapacityRatio", "Reference Heating Mode Cooling Capacity Ratio"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingPowerInputRatio, "ReferenceHeatingModeCoolingPowerInputRatio", "Reference Heating Mode Cooling Power Input Ratio"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingChilledWaterTemperature, "ReferenceHeatingModeLeavingChilledWaterTemperature", "Reference Heating Mode Leaving Chilled Water Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingCondenserWaterTemperature, "ReferenceHeatingModeLeavingCondenserWaterTemperature", "Reference Heating Mode Leaving Condenser Water Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeEnteringCondenserFluidTemperature, "ReferenceHeatingModeEnteringCondenserFluidTemperature", "Reference Heating Mode Entering Condenser Fluid Temperature"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeEnteringChilledWaterTemperatureLowLimit, "HeatingModeEnteringChilledWaterTemperatureLowLimit", "Heating Mode Entering Chilled Water Temperature Low Limit"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::ChilledWaterFlowModeType, "ChilledWaterFlowModeType", "Chilled Water Flow Mode Type"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::DesignHotWaterFlowRate, "DesignHotWaterFlowRate", "Design Hot Water Flow Rate"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CompressorMotorEfficiency, "CompressorMotorEfficiency", "Compressor Motor Efficiency"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CoolingModeTemperatureCurveCondenserWaterIndependentVariable, "CoolingModeTemperatureCurveCondenserWaterIndependentVariable", "Cooling Mode Temperature Curve Condenser Water Independent Variable"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityFunctionofTemperatureCurveName, "CoolingModeCoolingCapacityFunctionofTemperatureCurveName", "Cooling Mode Cooling Capacity Function of Temperature Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Cooling Mode Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Cooling Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityOptimumPartLoadRatio, "CoolingModeCoolingCapacityOptimumPartLoadRatio", "Cooling Mode Cooling Capacity Optimum Part Load Ratio"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeTemperatureCurveCondenserWaterIndependentVariable, "HeatingModeTemperatureCurveCondenserWaterIndependentVariable", "Heating Mode Temperature Curve Condenser Water Independent Variable"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityFunctionofTemperatureCurveName, "HeatingModeCoolingCapacityFunctionofTemperatureCurveName", "Heating Mode Cooling Capacity Function of Temperature Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Heating Mode Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Heating Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityOptimumPartLoadRatio, "HeatingModeCoolingCapacityOptimumPartLoadRatio", "Heating Mode Cooling Capacity Optimum Part Load Ratio"},
{ OS_ChillerHeaterPerformance_Electric_EIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ChillerHeaterPerformance_Electric_EIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ChillerHeaterPerformance_Electric_EIRFields> OptionalOS_ChillerHeaterPerformance_Electric_EIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX
