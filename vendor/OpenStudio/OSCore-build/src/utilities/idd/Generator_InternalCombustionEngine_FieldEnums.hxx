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

#ifndef UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_InternalCombustionEngineFields
 *  \brief Enumeration of Generator:InternalCombustionEngine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_InternalCombustionEngineFields, )
#else
class Generator_InternalCombustionEngineFields: public ::EnumBase<Generator_InternalCombustionEngineFields> {
 public: 
  enum domain 
  {
Name, RatedPowerOutput, ElectricCircuitNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, ShaftPowerCurveName, JacketHeatRecoveryCurveName, LubeHeatRecoveryCurveName, TotalExhaustEnergyCurveName, ExhaustTemperatureCurveName, Coefficient1ofUFactorTimesAreaCurve, Coefficient2ofUFactorTimesAreaCurve, MaximumExhaustFlowperUnitofPowerOutput, DesignMinimumExhaustTemperature, FuelHigherHeatingValue, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, FuelType, HeatRecoveryMaximumTemperature,   };
  Generator_InternalCombustionEngineFields()
   : EnumBase<Generator_InternalCombustionEngineFields>(Name) {} 
  Generator_InternalCombustionEngineFields(const std::string &t_name) 
   : EnumBase<Generator_InternalCombustionEngineFields>(t_name) {} 
  Generator_InternalCombustionEngineFields(int t_value) 
   : EnumBase<Generator_InternalCombustionEngineFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_InternalCombustionEngineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_InternalCombustionEngineFields>::value()); }
   private:
    friend class EnumBase<Generator_InternalCombustionEngineFields>;
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
{ Generator_InternalCombustionEngineFields::Name, "Name", "Name"},
{ Generator_InternalCombustionEngineFields::RatedPowerOutput, "RatedPowerOutput", "Rated Power Output"},
{ Generator_InternalCombustionEngineFields::ElectricCircuitNodeName, "ElectricCircuitNodeName", "Electric Circuit Node Name"},
{ Generator_InternalCombustionEngineFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::ShaftPowerCurveName, "ShaftPowerCurveName", "Shaft Power Curve Name"},
{ Generator_InternalCombustionEngineFields::JacketHeatRecoveryCurveName, "JacketHeatRecoveryCurveName", "Jacket Heat Recovery Curve Name"},
{ Generator_InternalCombustionEngineFields::LubeHeatRecoveryCurveName, "LubeHeatRecoveryCurveName", "Lube Heat Recovery Curve Name"},
{ Generator_InternalCombustionEngineFields::TotalExhaustEnergyCurveName, "TotalExhaustEnergyCurveName", "Total Exhaust Energy Curve Name"},
{ Generator_InternalCombustionEngineFields::ExhaustTemperatureCurveName, "ExhaustTemperatureCurveName", "Exhaust Temperature Curve Name"},
{ Generator_InternalCombustionEngineFields::Coefficient1ofUFactorTimesAreaCurve, "Coefficient1ofUFactorTimesAreaCurve", "Coefficient 1 of U-Factor Times Area Curve"},
{ Generator_InternalCombustionEngineFields::Coefficient2ofUFactorTimesAreaCurve, "Coefficient2ofUFactorTimesAreaCurve", "Coefficient 2 of U-Factor Times Area Curve"},
{ Generator_InternalCombustionEngineFields::MaximumExhaustFlowperUnitofPowerOutput, "MaximumExhaustFlowperUnitofPowerOutput", "Maximum Exhaust Flow per Unit of Power Output"},
{ Generator_InternalCombustionEngineFields::DesignMinimumExhaustTemperature, "DesignMinimumExhaustTemperature", "Design Minimum Exhaust Temperature"},
{ Generator_InternalCombustionEngineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Generator_InternalCombustionEngineFields::FuelType, "FuelType", "Fuel Type"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature, "HeatRecoveryMaximumTemperature", "Heat Recovery Maximum Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_InternalCombustionEngineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_InternalCombustionEngineFields> OptionalGenerator_InternalCombustionEngineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX
