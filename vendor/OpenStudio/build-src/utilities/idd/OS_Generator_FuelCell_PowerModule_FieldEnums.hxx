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

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_PowerModuleFields
 *  \brief Enumeration of OS:Generator:FuelCell:PowerModule's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_PowerModuleFields, )
#else
class OS_Generator_FuelCell_PowerModuleFields: public ::EnumBase<OS_Generator_FuelCell_PowerModuleFields> {
 public: 
  enum domain 
  {
Handle, Name, EfficiencyCurveMode, EfficiencyCurveName, NominalEfficiency, NominalElectricalPower, NumberofStopsatStartofSimulation, CyclingPerformanceDegradationCoefficient, NumberofRunHoursatBeginningofSimulation, AccumulatedRunTimeDegradationCoefficient, RunTimeDegradationInitiationTimeThreshold, PowerUpTransientLimit, PowerDownTransientLimit, StartUpTime, StartUpFuel, StartUpElectricityConsumption, StartUpElectricityProduced, ShutDownTime, ShutDownFuel, ShutDownElectricityConsumption, AncillaryElectricityConstantTerm, AncillaryElectricityLinearTerm, SkinLossCalculationMode, ZoneName, SkinLossRadiativeFraction, ConstantSkinLossRate, SkinLossUFactorTimesAreaTerm, SkinLossQuadraticCurveName, DilutionAirFlowRate, StackHeatlosstoDilutionAir, DilutionInletAirNodeName, DilutionOutletAirNodeName, MinimumOperatingPoint, MaximumOperatingPoint,   };
  OS_Generator_FuelCell_PowerModuleFields()
   : EnumBase<OS_Generator_FuelCell_PowerModuleFields>(Handle) {} 
  OS_Generator_FuelCell_PowerModuleFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_PowerModuleFields>(t_name) {} 
  OS_Generator_FuelCell_PowerModuleFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_PowerModuleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_PowerModuleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_PowerModuleFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_PowerModuleFields>;
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
{ OS_Generator_FuelCell_PowerModuleFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_PowerModuleFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode, "EfficiencyCurveMode", "Efficiency Curve Mode"},
{ OS_Generator_FuelCell_PowerModuleFields::EfficiencyCurveName, "EfficiencyCurveName", "Efficiency Curve Name"},
{ OS_Generator_FuelCell_PowerModuleFields::NominalEfficiency, "NominalEfficiency", "Nominal Efficiency"},
{ OS_Generator_FuelCell_PowerModuleFields::NominalElectricalPower, "NominalElectricalPower", "Nominal Electrical Power"},
{ OS_Generator_FuelCell_PowerModuleFields::NumberofStopsatStartofSimulation, "NumberofStopsatStartofSimulation", "Number of Stops at Start of Simulation"},
{ OS_Generator_FuelCell_PowerModuleFields::CyclingPerformanceDegradationCoefficient, "CyclingPerformanceDegradationCoefficient", "Cycling Performance Degradation Coefficient"},
{ OS_Generator_FuelCell_PowerModuleFields::NumberofRunHoursatBeginningofSimulation, "NumberofRunHoursatBeginningofSimulation", "Number of Run Hours at Beginning of Simulation"},
{ OS_Generator_FuelCell_PowerModuleFields::AccumulatedRunTimeDegradationCoefficient, "AccumulatedRunTimeDegradationCoefficient", "Accumulated Run Time Degradation Coefficient"},
{ OS_Generator_FuelCell_PowerModuleFields::RunTimeDegradationInitiationTimeThreshold, "RunTimeDegradationInitiationTimeThreshold", "Run Time Degradation Initiation Time Threshold"},
{ OS_Generator_FuelCell_PowerModuleFields::PowerUpTransientLimit, "PowerUpTransientLimit", "Power Up Transient Limit"},
{ OS_Generator_FuelCell_PowerModuleFields::PowerDownTransientLimit, "PowerDownTransientLimit", "Power Down Transient Limit"},
{ OS_Generator_FuelCell_PowerModuleFields::StartUpTime, "StartUpTime", "Start Up Time"},
{ OS_Generator_FuelCell_PowerModuleFields::StartUpFuel, "StartUpFuel", "Start Up Fuel"},
{ OS_Generator_FuelCell_PowerModuleFields::StartUpElectricityConsumption, "StartUpElectricityConsumption", "Start Up Electricity Consumption"},
{ OS_Generator_FuelCell_PowerModuleFields::StartUpElectricityProduced, "StartUpElectricityProduced", "Start Up Electricity Produced"},
{ OS_Generator_FuelCell_PowerModuleFields::ShutDownTime, "ShutDownTime", "Shut Down Time"},
{ OS_Generator_FuelCell_PowerModuleFields::ShutDownFuel, "ShutDownFuel", "Shut Down Fuel"},
{ OS_Generator_FuelCell_PowerModuleFields::ShutDownElectricityConsumption, "ShutDownElectricityConsumption", "Shut Down Electricity Consumption"},
{ OS_Generator_FuelCell_PowerModuleFields::AncillaryElectricityConstantTerm, "AncillaryElectricityConstantTerm", "Ancillary Electricity Constant Term"},
{ OS_Generator_FuelCell_PowerModuleFields::AncillaryElectricityLinearTerm, "AncillaryElectricityLinearTerm", "Ancillary Electricity Linear Term"},
{ OS_Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode, "SkinLossCalculationMode", "Skin Loss Calculation Mode"},
{ OS_Generator_FuelCell_PowerModuleFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_Generator_FuelCell_PowerModuleFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ OS_Generator_FuelCell_PowerModuleFields::ConstantSkinLossRate, "ConstantSkinLossRate", "Constant Skin Loss Rate"},
{ OS_Generator_FuelCell_PowerModuleFields::SkinLossUFactorTimesAreaTerm, "SkinLossUFactorTimesAreaTerm", "Skin Loss U-Factor Times Area Term"},
{ OS_Generator_FuelCell_PowerModuleFields::SkinLossQuadraticCurveName, "SkinLossQuadraticCurveName", "Skin Loss Quadratic Curve Name"},
{ OS_Generator_FuelCell_PowerModuleFields::DilutionAirFlowRate, "DilutionAirFlowRate", "Dilution Air Flow Rate"},
{ OS_Generator_FuelCell_PowerModuleFields::StackHeatlosstoDilutionAir, "StackHeatlosstoDilutionAir", "Stack Heat loss to Dilution Air"},
{ OS_Generator_FuelCell_PowerModuleFields::DilutionInletAirNodeName, "DilutionInletAirNodeName", "Dilution Inlet Air Node Name"},
{ OS_Generator_FuelCell_PowerModuleFields::DilutionOutletAirNodeName, "DilutionOutletAirNodeName", "Dilution Outlet Air Node Name"},
{ OS_Generator_FuelCell_PowerModuleFields::MinimumOperatingPoint, "MinimumOperatingPoint", "Minimum Operating Point"},
{ OS_Generator_FuelCell_PowerModuleFields::MaximumOperatingPoint, "MaximumOperatingPoint", "Maximum Operating Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_PowerModuleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_PowerModuleFields> OptionalOS_Generator_FuelCell_PowerModuleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_POWERMODULE_FIELDENUMS_HXX
