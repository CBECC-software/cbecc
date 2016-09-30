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

#ifndef UTILITIES_IDD_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelCell_PowerModuleFields
 *  \brief Enumeration of Generator:FuelCell:PowerModule's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelCell_PowerModuleFields, )
#else
class Generator_FuelCell_PowerModuleFields: public ::EnumBase<Generator_FuelCell_PowerModuleFields> {
 public: 
  enum domain 
  {
Name, EfficiencyCurveMode, EfficiencyCurveName, NominalEfficiency, NominalElectricalPower, NumberofStopsatStartofSimulation, CyclingPerformanceDegradationCoefficient, NumberofRunHoursatBeginningofSimulation, AccumulatedRunTimeDegradationCoefficient, RunTimeDegradationInitiationTimeThreshold, PowerUpTransientLimit, PowerDownTransientLimit, StartUpTime, StartUpFuel, StartUpElectricityConsumption, StartUpElectricityProduced, ShutDownTime, ShutDownFuel, ShutDownElectricityConsumption, AncillaryElectricityConstantTerm, AncillaryElectricityLinearTerm, SkinLossCalculationMode, ZoneName, SkinLossRadiativeFraction, ConstantSkinLossRate, SkinLossUFactorTimesAreaTerm, SkinLossQuadraticCurveName, DilutionAirFlowRate, StackHeatlosstoDilutionAir, DilutionInletAirNodeName, DilutionOutletAirNodeName, MinimumOperatingPoint, MaximumOperatingPoint,   };
  Generator_FuelCell_PowerModuleFields()
   : EnumBase<Generator_FuelCell_PowerModuleFields>(Name) {} 
  Generator_FuelCell_PowerModuleFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCell_PowerModuleFields>(t_name) {} 
  Generator_FuelCell_PowerModuleFields(int t_value) 
   : EnumBase<Generator_FuelCell_PowerModuleFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCell_PowerModuleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCell_PowerModuleFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCell_PowerModuleFields>;
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
{ Generator_FuelCell_PowerModuleFields::Name, "Name", "Name"},
{ Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode, "EfficiencyCurveMode", "Efficiency Curve Mode"},
{ Generator_FuelCell_PowerModuleFields::EfficiencyCurveName, "EfficiencyCurveName", "Efficiency Curve Name"},
{ Generator_FuelCell_PowerModuleFields::NominalEfficiency, "NominalEfficiency", "Nominal Efficiency"},
{ Generator_FuelCell_PowerModuleFields::NominalElectricalPower, "NominalElectricalPower", "Nominal Electrical Power"},
{ Generator_FuelCell_PowerModuleFields::NumberofStopsatStartofSimulation, "NumberofStopsatStartofSimulation", "Number of Stops at Start of Simulation"},
{ Generator_FuelCell_PowerModuleFields::CyclingPerformanceDegradationCoefficient, "CyclingPerformanceDegradationCoefficient", "Cycling Performance Degradation Coefficient"},
{ Generator_FuelCell_PowerModuleFields::NumberofRunHoursatBeginningofSimulation, "NumberofRunHoursatBeginningofSimulation", "Number of Run Hours at Beginning of Simulation"},
{ Generator_FuelCell_PowerModuleFields::AccumulatedRunTimeDegradationCoefficient, "AccumulatedRunTimeDegradationCoefficient", "Accumulated Run Time Degradation Coefficient"},
{ Generator_FuelCell_PowerModuleFields::RunTimeDegradationInitiationTimeThreshold, "RunTimeDegradationInitiationTimeThreshold", "Run Time Degradation Initiation Time Threshold"},
{ Generator_FuelCell_PowerModuleFields::PowerUpTransientLimit, "PowerUpTransientLimit", "Power Up Transient Limit"},
{ Generator_FuelCell_PowerModuleFields::PowerDownTransientLimit, "PowerDownTransientLimit", "Power Down Transient Limit"},
{ Generator_FuelCell_PowerModuleFields::StartUpTime, "StartUpTime", "Start Up Time"},
{ Generator_FuelCell_PowerModuleFields::StartUpFuel, "StartUpFuel", "Start Up Fuel"},
{ Generator_FuelCell_PowerModuleFields::StartUpElectricityConsumption, "StartUpElectricityConsumption", "Start Up Electricity Consumption"},
{ Generator_FuelCell_PowerModuleFields::StartUpElectricityProduced, "StartUpElectricityProduced", "Start Up Electricity Produced"},
{ Generator_FuelCell_PowerModuleFields::ShutDownTime, "ShutDownTime", "Shut Down Time"},
{ Generator_FuelCell_PowerModuleFields::ShutDownFuel, "ShutDownFuel", "Shut Down Fuel"},
{ Generator_FuelCell_PowerModuleFields::ShutDownElectricityConsumption, "ShutDownElectricityConsumption", "Shut Down Electricity Consumption"},
{ Generator_FuelCell_PowerModuleFields::AncillaryElectricityConstantTerm, "AncillaryElectricityConstantTerm", "Ancillary Electricity Constant Term"},
{ Generator_FuelCell_PowerModuleFields::AncillaryElectricityLinearTerm, "AncillaryElectricityLinearTerm", "Ancillary Electricity Linear Term"},
{ Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode, "SkinLossCalculationMode", "Skin Loss Calculation Mode"},
{ Generator_FuelCell_PowerModuleFields::ZoneName, "ZoneName", "Zone Name"},
{ Generator_FuelCell_PowerModuleFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ Generator_FuelCell_PowerModuleFields::ConstantSkinLossRate, "ConstantSkinLossRate", "Constant Skin Loss Rate"},
{ Generator_FuelCell_PowerModuleFields::SkinLossUFactorTimesAreaTerm, "SkinLossUFactorTimesAreaTerm", "Skin Loss U-Factor Times Area Term"},
{ Generator_FuelCell_PowerModuleFields::SkinLossQuadraticCurveName, "SkinLossQuadraticCurveName", "Skin Loss Quadratic Curve Name"},
{ Generator_FuelCell_PowerModuleFields::DilutionAirFlowRate, "DilutionAirFlowRate", "Dilution Air Flow Rate"},
{ Generator_FuelCell_PowerModuleFields::StackHeatlosstoDilutionAir, "StackHeatlosstoDilutionAir", "Stack Heat loss to Dilution Air"},
{ Generator_FuelCell_PowerModuleFields::DilutionInletAirNodeName, "DilutionInletAirNodeName", "Dilution Inlet Air Node Name"},
{ Generator_FuelCell_PowerModuleFields::DilutionOutletAirNodeName, "DilutionOutletAirNodeName", "Dilution Outlet Air Node Name"},
{ Generator_FuelCell_PowerModuleFields::MinimumOperatingPoint, "MinimumOperatingPoint", "Minimum Operating Point"},
{ Generator_FuelCell_PowerModuleFields::MaximumOperatingPoint, "MaximumOperatingPoint", "Maximum Operating Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCell_PowerModuleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCell_PowerModuleFields> OptionalGenerator_FuelCell_PowerModuleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX
