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

#ifndef UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_Absorption_IndirectFields
 *  \brief Enumeration of Chiller:Absorption:Indirect's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_Absorption_IndirectFields, )
#else
class Chiller_Absorption_IndirectFields: public ::EnumBase<Chiller_Absorption_IndirectFields> {
 public: 
  enum domain 
  {
Name, NominalCapacity, NominalPumpingPower, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, CondenserInletTemperatureLowerLimit, ChilledWaterOutletTemperatureLowerLimit, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, ChillerFlowMode, GeneratorHeatInputFunctionofPartLoadRatioCurveName, PumpElectricInputFunctionofPartLoadRatioCurveName, GeneratorInletNodeName, GeneratorOutletNodeName, CapacityCorrectionFunctionofCondenserTemperatureCurveName, CapacityCorrectionFunctionofChilledWaterTemperatureCurveName, CapacityCorrectionFunctionofGeneratorTemperatureCurveName, GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName, GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName, GeneratorHeatSourceType, DesignGeneratorFluidFlowRate, TemperatureLowerLimitGeneratorInlet, DegreeofSubcoolinginSteamGenerator, DegreeofSubcoolinginSteamCondensateLoop, SizingFactor,   };
  Chiller_Absorption_IndirectFields()
   : EnumBase<Chiller_Absorption_IndirectFields>(Name) {} 
  Chiller_Absorption_IndirectFields(const std::string &t_name) 
   : EnumBase<Chiller_Absorption_IndirectFields>(t_name) {} 
  Chiller_Absorption_IndirectFields(int t_value) 
   : EnumBase<Chiller_Absorption_IndirectFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_Absorption_IndirectFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_Absorption_IndirectFields>::value()); }
   private:
    friend class EnumBase<Chiller_Absorption_IndirectFields>;
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
{ Chiller_Absorption_IndirectFields::Name, "Name", "Name"},
{ Chiller_Absorption_IndirectFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_Absorption_IndirectFields::NominalPumpingPower, "NominalPumpingPower", "Nominal Pumping Power"},
{ Chiller_Absorption_IndirectFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, "CondenserInletTemperatureLowerLimit", "Condenser Inlet Temperature Lower Limit"},
{ Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_Absorption_IndirectFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputFunctionofPartLoadRatioCurveName, "GeneratorHeatInputFunctionofPartLoadRatioCurveName", "Generator Heat Input Function of Part Load Ratio Curve Name"},
{ Chiller_Absorption_IndirectFields::PumpElectricInputFunctionofPartLoadRatioCurveName, "PumpElectricInputFunctionofPartLoadRatioCurveName", "Pump Electric Input Function of Part Load Ratio Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorInletNodeName, "GeneratorInletNodeName", "Generator Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::GeneratorOutletNodeName, "GeneratorOutletNodeName", "Generator Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofCondenserTemperatureCurveName, "CapacityCorrectionFunctionofCondenserTemperatureCurveName", "Capacity Correction Function of Condenser Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofChilledWaterTemperatureCurveName, "CapacityCorrectionFunctionofChilledWaterTemperatureCurveName", "Capacity Correction Function of Chilled Water Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofGeneratorTemperatureCurveName, "CapacityCorrectionFunctionofGeneratorTemperatureCurveName", "Capacity Correction Function of Generator Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName, "GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName", "Generator Heat Input Correction Function of Condenser Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName, "GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName", "Generator Heat Input Correction Function of Chilled Water Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, "GeneratorHeatSourceType", "Generator Heat Source Type"},
{ Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, "DesignGeneratorFluidFlowRate", "Design Generator Fluid Flow Rate"},
{ Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, "TemperatureLowerLimitGeneratorInlet", "Temperature Lower Limit Generator Inlet"},
{ Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, "DegreeofSubcoolinginSteamGenerator", "Degree of Subcooling in Steam Generator"},
{ Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop, "DegreeofSubcoolinginSteamCondensateLoop", "Degree of Subcooling in Steam Condensate Loop"},
{ Chiller_Absorption_IndirectFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_Absorption_IndirectFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_Absorption_IndirectFields> OptionalChiller_Absorption_IndirectFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX
