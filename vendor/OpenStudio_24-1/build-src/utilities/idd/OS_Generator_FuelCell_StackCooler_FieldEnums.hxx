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

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_StackCoolerFields
 *  \brief Enumeration of OS:Generator:FuelCell:StackCooler's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_StackCoolerFields, )
#else
class OS_Generator_FuelCell_StackCoolerFields: public ::EnumBase<OS_Generator_FuelCell_StackCoolerFields> {
 public: 
  enum domain 
  {
Handle, Name, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, NominalStackTemperature, ActualStackTemperature, Coefficientr0, Coefficientr1, Coefficientr2, Coefficientr3, StackCoolantFlowRate, StackCoolerUFactorTimesAreaValue, FscogenAdjustmentFactor, StackCogenerationExchangerArea, StackCogenerationExchangerNominalFlowRate, StackCogenerationExchangerNominalHeatTransferCoefficient, StackCogenerationExchangerNominalHeatTransferCoefficientExponent, StackCoolerPumpPower, StackCoolerPumpHeatLossFraction, StackAirCoolerFanCoefficientf0, StackAirCoolerFanCoefficientf1, StackAirCoolerFanCoefficientf2,   };
  OS_Generator_FuelCell_StackCoolerFields()
   : EnumBase<OS_Generator_FuelCell_StackCoolerFields>(Handle) {} 
  OS_Generator_FuelCell_StackCoolerFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_StackCoolerFields>(t_name) {} 
  OS_Generator_FuelCell_StackCoolerFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_StackCoolerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_StackCoolerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_StackCoolerFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_StackCoolerFields>;
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
{ OS_Generator_FuelCell_StackCoolerFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_StackCoolerFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ OS_Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ OS_Generator_FuelCell_StackCoolerFields::NominalStackTemperature, "NominalStackTemperature", "Nominal Stack Temperature"},
{ OS_Generator_FuelCell_StackCoolerFields::ActualStackTemperature, "ActualStackTemperature", "Actual Stack Temperature"},
{ OS_Generator_FuelCell_StackCoolerFields::Coefficientr0, "Coefficientr0", "Coefficient r0"},
{ OS_Generator_FuelCell_StackCoolerFields::Coefficientr1, "Coefficientr1", "Coefficient r1"},
{ OS_Generator_FuelCell_StackCoolerFields::Coefficientr2, "Coefficientr2", "Coefficient r2"},
{ OS_Generator_FuelCell_StackCoolerFields::Coefficientr3, "Coefficientr3", "Coefficient r3"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCoolantFlowRate, "StackCoolantFlowRate", "Stack Coolant Flow Rate"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCoolerUFactorTimesAreaValue, "StackCoolerUFactorTimesAreaValue", "Stack Cooler U-Factor Times Area Value"},
{ OS_Generator_FuelCell_StackCoolerFields::FscogenAdjustmentFactor, "FscogenAdjustmentFactor", "Fs-cogen Adjustment Factor"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerArea, "StackCogenerationExchangerArea", "Stack Cogeneration Exchanger Area"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalFlowRate, "StackCogenerationExchangerNominalFlowRate", "Stack Cogeneration Exchanger Nominal Flow Rate"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficient, "StackCogenerationExchangerNominalHeatTransferCoefficient", "Stack Cogeneration Exchanger Nominal Heat Transfer Coefficient"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficientExponent, "StackCogenerationExchangerNominalHeatTransferCoefficientExponent", "Stack Cogeneration Exchanger Nominal Heat Transfer Coefficient Exponent"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCoolerPumpPower, "StackCoolerPumpPower", "Stack Cooler Pump Power"},
{ OS_Generator_FuelCell_StackCoolerFields::StackCoolerPumpHeatLossFraction, "StackCoolerPumpHeatLossFraction", "Stack Cooler Pump Heat Loss Fraction"},
{ OS_Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf0, "StackAirCoolerFanCoefficientf0", "Stack Air Cooler Fan Coefficient f0"},
{ OS_Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf1, "StackAirCoolerFanCoefficientf1", "Stack Air Cooler Fan Coefficient f1"},
{ OS_Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf2, "StackAirCoolerFanCoefficientf2", "Stack Air Cooler Fan Coefficient f2"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_StackCoolerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_StackCoolerFields> OptionalOS_Generator_FuelCell_StackCoolerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX
