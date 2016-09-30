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

#ifndef UTILITIES_IDD_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelCell_StackCoolerFields
 *  \brief Enumeration of Generator:FuelCell:StackCooler's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelCell_StackCoolerFields, )
#else
class Generator_FuelCell_StackCoolerFields: public ::EnumBase<Generator_FuelCell_StackCoolerFields> {
 public: 
  enum domain 
  {
Name, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, NominalStackTemperature, ActualStackTemperature, Coefficientr0, Coefficientr1, Coefficientr2, Coefficientr3, StackCoolantFlowRate, StackCoolerUFactorTimesAreaValue, FscogenAdjustmentFactor, StackCogenerationExchangerArea, StackCogenerationExchangerNominalFlowRate, StackCogenerationExchangerNominalHeatTransferCoefficient, StackCogenerationExchangerNominalHeatTransferCoefficientExponent, StackCoolerPumpPower, StackCoolerPumpHeatLossFraction, StackAirCoolerFanCoefficientf0, StackAirCoolerFanCoefficientf1, StackAirCoolerFanCoefficientf2,   };
  Generator_FuelCell_StackCoolerFields()
   : EnumBase<Generator_FuelCell_StackCoolerFields>(Name) {} 
  Generator_FuelCell_StackCoolerFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCell_StackCoolerFields>(t_name) {} 
  Generator_FuelCell_StackCoolerFields(int t_value) 
   : EnumBase<Generator_FuelCell_StackCoolerFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCell_StackCoolerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCell_StackCoolerFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCell_StackCoolerFields>;
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
{ Generator_FuelCell_StackCoolerFields::Name, "Name", "Name"},
{ Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ Generator_FuelCell_StackCoolerFields::NominalStackTemperature, "NominalStackTemperature", "Nominal Stack Temperature"},
{ Generator_FuelCell_StackCoolerFields::ActualStackTemperature, "ActualStackTemperature", "Actual Stack Temperature"},
{ Generator_FuelCell_StackCoolerFields::Coefficientr0, "Coefficientr0", "Coefficient r0"},
{ Generator_FuelCell_StackCoolerFields::Coefficientr1, "Coefficientr1", "Coefficient r1"},
{ Generator_FuelCell_StackCoolerFields::Coefficientr2, "Coefficientr2", "Coefficient r2"},
{ Generator_FuelCell_StackCoolerFields::Coefficientr3, "Coefficientr3", "Coefficient r3"},
{ Generator_FuelCell_StackCoolerFields::StackCoolantFlowRate, "StackCoolantFlowRate", "Stack Coolant Flow Rate"},
{ Generator_FuelCell_StackCoolerFields::StackCoolerUFactorTimesAreaValue, "StackCoolerUFactorTimesAreaValue", "Stack Cooler U-Factor Times Area Value"},
{ Generator_FuelCell_StackCoolerFields::FscogenAdjustmentFactor, "FscogenAdjustmentFactor", "Fs-cogen Adjustment Factor"},
{ Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerArea, "StackCogenerationExchangerArea", "Stack Cogeneration Exchanger Area"},
{ Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalFlowRate, "StackCogenerationExchangerNominalFlowRate", "Stack Cogeneration Exchanger Nominal Flow Rate"},
{ Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficient, "StackCogenerationExchangerNominalHeatTransferCoefficient", "Stack Cogeneration Exchanger Nominal Heat Transfer Coefficient"},
{ Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficientExponent, "StackCogenerationExchangerNominalHeatTransferCoefficientExponent", "Stack Cogeneration Exchanger Nominal Heat Transfer Coefficient Exponent"},
{ Generator_FuelCell_StackCoolerFields::StackCoolerPumpPower, "StackCoolerPumpPower", "Stack Cooler Pump Power"},
{ Generator_FuelCell_StackCoolerFields::StackCoolerPumpHeatLossFraction, "StackCoolerPumpHeatLossFraction", "Stack Cooler Pump Heat Loss Fraction"},
{ Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf0, "StackAirCoolerFanCoefficientf0", "Stack Air Cooler Fan Coefficient f0"},
{ Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf1, "StackAirCoolerFanCoefficientf1", "Stack Air Cooler Fan Coefficient f1"},
{ Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf2, "StackAirCoolerFanCoefficientf2", "Stack Air Cooler Fan Coefficient f2"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCell_StackCoolerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCell_StackCoolerFields> OptionalGenerator_FuelCell_StackCoolerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELCELL_STACKCOOLER_FIELDENUMS_HXX
