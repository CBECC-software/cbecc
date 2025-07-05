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

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields
 *  \brief Enumeration of OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields, )
#else
class OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields: public ::EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields> {
 public: 
  enum domain 
  {
Handle, Name, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, HeatRecoveryWaterMaximumFlowRate, ExhaustOutletAirNodeName, HeatExchangerCalculationMethod, Method1HeatExchangerEffectiveness, Method2Parameterhxs0, Method2Parameterhxs1, Method2Parameterhxs2, Method2Parameterhxs3, Method2Parameterhxs4, Method3h0GasCoefficient, Method3NdotGasRefCoefficient, Method3nCoefficient, Method3GasArea, Method3h0WaterCoefficient, Method3NdotWaterrefCoefficient, Method3mCoefficient, Method3WaterArea, Method3FAdjustmentFactor, Method4hxl1Coefficient, Method4hxl2Coefficient, Method4CondensationThreshold,   };
  OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields()
   : EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(Handle) {} 
  OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(t_name) {} 
  OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>;
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
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterMaximumFlowRate, "HeatRecoveryWaterMaximumFlowRate", "Heat Recovery Water Maximum Flow Rate"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::ExhaustOutletAirNodeName, "ExhaustOutletAirNodeName", "Exhaust Outlet Air Node Name"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatExchangerCalculationMethod, "HeatExchangerCalculationMethod", "Heat Exchanger Calculation Method"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method1HeatExchangerEffectiveness, "Method1HeatExchangerEffectiveness", "Method 1 Heat Exchanger Effectiveness"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs0, "Method2Parameterhxs0", "Method 2 Parameter hxs0"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs1, "Method2Parameterhxs1", "Method 2 Parameter hxs1"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs2, "Method2Parameterhxs2", "Method 2 Parameter hxs2"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs3, "Method2Parameterhxs3", "Method 2 Parameter hxs3"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs4, "Method2Parameterhxs4", "Method 2 Parameter hxs4"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0GasCoefficient, "Method3h0GasCoefficient", "Method 3 h0Gas Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotGasRefCoefficient, "Method3NdotGasRefCoefficient", "Method 3 NdotGasRef Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3nCoefficient, "Method3nCoefficient", "Method 3 n Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3GasArea, "Method3GasArea", "Method 3 Gas Area"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0WaterCoefficient, "Method3h0WaterCoefficient", "Method 3 h0 Water Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotWaterrefCoefficient, "Method3NdotWaterrefCoefficient", "Method 3 N dot Water ref Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3mCoefficient, "Method3mCoefficient", "Method 3 m Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3WaterArea, "Method3WaterArea", "Method 3 Water Area"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3FAdjustmentFactor, "Method3FAdjustmentFactor", "Method 3 F Adjustment Factor"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl1Coefficient, "Method4hxl1Coefficient", "Method 4 hxl1 Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl2Coefficient, "Method4hxl2Coefficient", "Method 4 hxl2 Coefficient"},
{ OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4CondensationThreshold, "Method4CondensationThreshold", "Method 4 Condensation Threshold"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields> OptionalOS_Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX
