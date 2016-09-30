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

#ifndef UTILITIES_IDD_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields
 *  \brief Enumeration of Generator:FuelCell:ExhaustGasToWaterHeatExchanger's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields, )
#else
class Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields: public ::EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields> {
 public: 
  enum domain 
  {
Name, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, HeatRecoveryWaterMaximumFlowRate, ExhaustOutletAirNodeName, HeatExchangerCalculationMethod, Method1HeatExchangerEffectiveness, Method2Parameterhxs0, Method2Parameterhxs1, Method2Parameterhxs2, Method2Parameterhxs3, Method2Parameterhxs4, Method3h0GasCoefficient, Method3NdotGasRefCoefficient, Method3nCoefficient, Method3GasArea, Method3h0WaterCoefficient, Method3NdotWaterrefCoefficient, Method3mCoefficient, Method3WaterArea, Method3FAdjustmentFactor, Method4hxl1Coefficient, Method4hxl2Coefficient, Method4CondensationThreshold,   };
  Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields()
   : EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(Name) {} 
  Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(t_name) {} 
  Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields(int t_value) 
   : EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields>;
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
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Name, "Name", "Name"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterMaximumFlowRate, "HeatRecoveryWaterMaximumFlowRate", "Heat Recovery Water Maximum Flow Rate"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::ExhaustOutletAirNodeName, "ExhaustOutletAirNodeName", "Exhaust Outlet Air Node Name"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatExchangerCalculationMethod, "HeatExchangerCalculationMethod", "Heat Exchanger Calculation Method"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method1HeatExchangerEffectiveness, "Method1HeatExchangerEffectiveness", "Method 1 Heat Exchanger Effectiveness"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs0, "Method2Parameterhxs0", "Method 2 Parameter hxs0"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs1, "Method2Parameterhxs1", "Method 2 Parameter hxs1"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs2, "Method2Parameterhxs2", "Method 2 Parameter hxs2"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs3, "Method2Parameterhxs3", "Method 2 Parameter hxs3"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs4, "Method2Parameterhxs4", "Method 2 Parameter hxs4"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0GasCoefficient, "Method3h0GasCoefficient", "Method 3 h0Gas Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotGasRefCoefficient, "Method3NdotGasRefCoefficient", "Method 3 NdotGasRef Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3nCoefficient, "Method3nCoefficient", "Method 3 n Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3GasArea, "Method3GasArea", "Method 3 Gas Area"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0WaterCoefficient, "Method3h0WaterCoefficient", "Method 3 h0 Water Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotWaterrefCoefficient, "Method3NdotWaterrefCoefficient", "Method 3 N dot Water ref Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3mCoefficient, "Method3mCoefficient", "Method 3 m Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3WaterArea, "Method3WaterArea", "Method 3 Water Area"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3FAdjustmentFactor, "Method3FAdjustmentFactor", "Method 3 F Adjustment Factor"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl1Coefficient, "Method4hxl1Coefficient", "Method 4 hxl1 Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl2Coefficient, "Method4hxl2Coefficient", "Method 4 hxl2 Coefficient"},
{ Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4CondensationThreshold, "Method4CondensationThreshold", "Method 4 Condensation Threshold"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields> OptionalGenerator_FuelCell_ExhaustGasToWaterHeatExchangerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELCELL_EXHAUSTGASTOWATERHEATEXCHANGER_FIELDENUMS_HXX
