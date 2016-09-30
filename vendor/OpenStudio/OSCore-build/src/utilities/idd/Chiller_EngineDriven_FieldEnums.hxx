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

#ifndef UTILITIES_IDD_CHILLER_ENGINEDRIVEN_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ENGINEDRIVEN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_EngineDrivenFields
 *  \brief Enumeration of Chiller:EngineDriven's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_EngineDrivenFields, )
#else
class Chiller_EngineDrivenFields: public ::EnumBase<Chiller_EngineDrivenFields> {
 public: 
  enum domain 
  {
Name, CondenserType, NominalCapacity, NominalCOP, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, TemperatureRiseCoefficient, DesignChilledWaterOutletTemperature, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, Coefficient1ofCapacityRatioCurve, Coefficient2ofCapacityRatioCurve, Coefficient3ofCapacityRatioCurve, Coefficient1ofPowerRatioCurve, Coefficient2ofPowerRatioCurve, Coefficient3ofPowerRatioCurve, Coefficient1ofFullLoadRatioCurve, Coefficient2ofFullLoadRatioCurve, Coefficient3ofFullLoadRatioCurve, ChilledWaterOutletTemperatureLowerLimit, FuelUseCurveName, JacketHeatRecoveryCurveName, LubeHeatRecoveryCurveName, TotalExhaustEnergyCurveName, ExhaustTemperatureCurveName, Coefficient1ofUFactorTimesAreaCurve, Coefficient2ofUFactorTimesAreaCurve, MaximumExhaustFlowperUnitofPowerOutput, DesignMinimumExhaustTemperature, FuelType, FuelHigherHeatingValue, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, ChillerFlowMode, MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  Chiller_EngineDrivenFields()
   : EnumBase<Chiller_EngineDrivenFields>(Name) {} 
  Chiller_EngineDrivenFields(const std::string &t_name) 
   : EnumBase<Chiller_EngineDrivenFields>(t_name) {} 
  Chiller_EngineDrivenFields(int t_value) 
   : EnumBase<Chiller_EngineDrivenFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_EngineDrivenFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_EngineDrivenFields>::value()); }
   private:
    friend class EnumBase<Chiller_EngineDrivenFields>;
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
{ Chiller_EngineDrivenFields::Name, "Name", "Name"},
{ Chiller_EngineDrivenFields::CondenserType, "CondenserType", "Condenser Type"},
{ Chiller_EngineDrivenFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_EngineDrivenFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ Chiller_EngineDrivenFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_EngineDrivenFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_EngineDrivenFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_EngineDrivenFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_EngineDrivenFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_EngineDrivenFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_EngineDrivenFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_EngineDrivenFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_EngineDrivenFields::TemperatureRiseCoefficient, "TemperatureRiseCoefficient", "Temperature Rise Coefficient"},
{ Chiller_EngineDrivenFields::DesignChilledWaterOutletTemperature, "DesignChilledWaterOutletTemperature", "Design Chilled Water Outlet Temperature"},
{ Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_EngineDrivenFields::Coefficient1ofCapacityRatioCurve, "Coefficient1ofCapacityRatioCurve", "Coefficient 1 of Capacity Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient2ofCapacityRatioCurve, "Coefficient2ofCapacityRatioCurve", "Coefficient 2 of Capacity Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient3ofCapacityRatioCurve, "Coefficient3ofCapacityRatioCurve", "Coefficient 3 of Capacity Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient1ofPowerRatioCurve, "Coefficient1ofPowerRatioCurve", "Coefficient 1 of Power Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient2ofPowerRatioCurve, "Coefficient2ofPowerRatioCurve", "Coefficient 2 of Power Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient3ofPowerRatioCurve, "Coefficient3ofPowerRatioCurve", "Coefficient 3 of Power Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient1ofFullLoadRatioCurve, "Coefficient1ofFullLoadRatioCurve", "Coefficient 1 of Full Load Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient2ofFullLoadRatioCurve, "Coefficient2ofFullLoadRatioCurve", "Coefficient 2 of Full Load Ratio Curve"},
{ Chiller_EngineDrivenFields::Coefficient3ofFullLoadRatioCurve, "Coefficient3ofFullLoadRatioCurve", "Coefficient 3 of Full Load Ratio Curve"},
{ Chiller_EngineDrivenFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_EngineDrivenFields::FuelUseCurveName, "FuelUseCurveName", "Fuel Use Curve Name"},
{ Chiller_EngineDrivenFields::JacketHeatRecoveryCurveName, "JacketHeatRecoveryCurveName", "Jacket Heat Recovery Curve Name"},
{ Chiller_EngineDrivenFields::LubeHeatRecoveryCurveName, "LubeHeatRecoveryCurveName", "Lube Heat Recovery Curve Name"},
{ Chiller_EngineDrivenFields::TotalExhaustEnergyCurveName, "TotalExhaustEnergyCurveName", "Total Exhaust Energy Curve Name"},
{ Chiller_EngineDrivenFields::ExhaustTemperatureCurveName, "ExhaustTemperatureCurveName", "Exhaust Temperature Curve Name"},
{ Chiller_EngineDrivenFields::Coefficient1ofUFactorTimesAreaCurve, "Coefficient1ofUFactorTimesAreaCurve", "Coefficient 1 of U-Factor Times Area Curve"},
{ Chiller_EngineDrivenFields::Coefficient2ofUFactorTimesAreaCurve, "Coefficient2ofUFactorTimesAreaCurve", "Coefficient 2 of U-Factor Times Area Curve"},
{ Chiller_EngineDrivenFields::MaximumExhaustFlowperUnitofPowerOutput, "MaximumExhaustFlowperUnitofPowerOutput", "Maximum Exhaust Flow per Unit of Power Output"},
{ Chiller_EngineDrivenFields::DesignMinimumExhaustTemperature, "DesignMinimumExhaustTemperature", "Design Minimum Exhaust Temperature"},
{ Chiller_EngineDrivenFields::FuelType, "FuelType", "Fuel Type"},
{ Chiller_EngineDrivenFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Chiller_EngineDrivenFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_EngineDrivenFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_EngineDrivenFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_EngineDrivenFields::MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode, "MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode", "Maximum Temperature for Heat Recovery at Heat Recovery Outlet Node"},
{ Chiller_EngineDrivenFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_EngineDrivenFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Chiller_EngineDrivenFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Chiller_EngineDrivenFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_EngineDrivenFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_EngineDrivenFields> OptionalChiller_EngineDrivenFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ENGINEDRIVEN_FIELDENUMS_HXX
