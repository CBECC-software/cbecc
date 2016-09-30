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

#ifndef UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields
 *  \brief Enumeration of HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields, )
#else
class HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields: public ::EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields> {
 public: 
  enum domain 
  {
Name, NominalAirFlowRate, NominalAirFaceVelocity, NominalElectricPower, TemperatureEquationCoefficient1, TemperatureEquationCoefficient2, TemperatureEquationCoefficient3, TemperatureEquationCoefficient4, TemperatureEquationCoefficient5, TemperatureEquationCoefficient6, TemperatureEquationCoefficient7, TemperatureEquationCoefficient8, MinimumRegenerationInletAirHumidityRatioforTemperatureEquation, MaximumRegenerationInletAirHumidityRatioforTemperatureEquation, MinimumRegenerationInletAirTemperatureforTemperatureEquation, MaximumRegenerationInletAirTemperatureforTemperatureEquation, MinimumProcessInletAirHumidityRatioforTemperatureEquation, MaximumProcessInletAirHumidityRatioforTemperatureEquation, MinimumProcessInletAirTemperatureforTemperatureEquation, MaximumProcessInletAirTemperatureforTemperatureEquation, MinimumRegenerationAirVelocityforTemperatureEquation, MaximumRegenerationAirVelocityforTemperatureEquation, MinimumRegenerationOutletAirTemperatureforTemperatureEquation, MaximumRegenerationOutletAirTemperatureforTemperatureEquation, MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation, MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation, MinimumProcessInletAirRelativeHumidityforTemperatureEquation, MaximumProcessInletAirRelativeHumidityforTemperatureEquation, HumidityRatioEquationCoefficient1, HumidityRatioEquationCoefficient2, HumidityRatioEquationCoefficient3, HumidityRatioEquationCoefficient4, HumidityRatioEquationCoefficient5, HumidityRatioEquationCoefficient6, HumidityRatioEquationCoefficient7, HumidityRatioEquationCoefficient8, MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation, MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation, MinimumRegenerationInletAirTemperatureforHumidityRatioEquation, MaximumRegenerationInletAirTemperatureforHumidityRatioEquation, MinimumProcessInletAirHumidityRatioforHumidityRatioEquation, MaximumProcessInletAirHumidityRatioforHumidityRatioEquation, MinimumProcessInletAirTemperatureforHumidityRatioEquation, MaximumProcessInletAirTemperatureforHumidityRatioEquation, MinimumRegenerationAirVelocityforHumidityRatioEquation, MaximumRegenerationAirVelocityforHumidityRatioEquation, MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation, MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation,   };
  HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields()
   : EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(Name) {} 
  HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields(const std::string &t_name) 
   : EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(t_name) {} 
  HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields(int t_value) 
   : EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(t_value) {} 
  static std::string enumName() 
  { return "HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>::value()); }
   private:
    friend class EnumBase<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>;
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
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::Name, "Name", "Name"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalAirFlowRate, "NominalAirFlowRate", "Nominal Air Flow Rate"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalAirFaceVelocity, "NominalAirFaceVelocity", "Nominal Air Face Velocity"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalElectricPower, "NominalElectricPower", "Nominal Electric Power"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient1, "TemperatureEquationCoefficient1", "Temperature Equation Coefficient 1"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient2, "TemperatureEquationCoefficient2", "Temperature Equation Coefficient 2"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient3, "TemperatureEquationCoefficient3", "Temperature Equation Coefficient 3"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient4, "TemperatureEquationCoefficient4", "Temperature Equation Coefficient 4"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient5, "TemperatureEquationCoefficient5", "Temperature Equation Coefficient 5"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient6, "TemperatureEquationCoefficient6", "Temperature Equation Coefficient 6"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient7, "TemperatureEquationCoefficient7", "Temperature Equation Coefficient 7"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient8, "TemperatureEquationCoefficient8", "Temperature Equation Coefficient 8"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirHumidityRatioforTemperatureEquation, "MinimumRegenerationInletAirHumidityRatioforTemperatureEquation", "Minimum Regeneration Inlet Air Humidity Ratio for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirHumidityRatioforTemperatureEquation, "MaximumRegenerationInletAirHumidityRatioforTemperatureEquation", "Maximum Regeneration Inlet Air Humidity Ratio for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirTemperatureforTemperatureEquation, "MinimumRegenerationInletAirTemperatureforTemperatureEquation", "Minimum Regeneration Inlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirTemperatureforTemperatureEquation, "MaximumRegenerationInletAirTemperatureforTemperatureEquation", "Maximum Regeneration Inlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirHumidityRatioforTemperatureEquation, "MinimumProcessInletAirHumidityRatioforTemperatureEquation", "Minimum Process Inlet Air Humidity Ratio for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirHumidityRatioforTemperatureEquation, "MaximumProcessInletAirHumidityRatioforTemperatureEquation", "Maximum Process Inlet Air Humidity Ratio for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirTemperatureforTemperatureEquation, "MinimumProcessInletAirTemperatureforTemperatureEquation", "Minimum Process Inlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirTemperatureforTemperatureEquation, "MaximumProcessInletAirTemperatureforTemperatureEquation", "Maximum Process Inlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationAirVelocityforTemperatureEquation, "MinimumRegenerationAirVelocityforTemperatureEquation", "Minimum Regeneration Air Velocity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationAirVelocityforTemperatureEquation, "MaximumRegenerationAirVelocityforTemperatureEquation", "Maximum Regeneration Air Velocity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationOutletAirTemperatureforTemperatureEquation, "MinimumRegenerationOutletAirTemperatureforTemperatureEquation", "Minimum Regeneration Outlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationOutletAirTemperatureforTemperatureEquation, "MaximumRegenerationOutletAirTemperatureforTemperatureEquation", "Maximum Regeneration Outlet Air Temperature for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation, "MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation", "Minimum Regeneration Inlet Air Relative Humidity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation, "MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation", "Maximum Regeneration Inlet Air Relative Humidity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirRelativeHumidityforTemperatureEquation, "MinimumProcessInletAirRelativeHumidityforTemperatureEquation", "Minimum Process Inlet Air Relative Humidity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirRelativeHumidityforTemperatureEquation, "MaximumProcessInletAirRelativeHumidityforTemperatureEquation", "Maximum Process Inlet Air Relative Humidity for Temperature Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient1, "HumidityRatioEquationCoefficient1", "Humidity Ratio Equation Coefficient 1"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient2, "HumidityRatioEquationCoefficient2", "Humidity Ratio Equation Coefficient 2"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient3, "HumidityRatioEquationCoefficient3", "Humidity Ratio Equation Coefficient 3"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient4, "HumidityRatioEquationCoefficient4", "Humidity Ratio Equation Coefficient 4"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient5, "HumidityRatioEquationCoefficient5", "Humidity Ratio Equation Coefficient 5"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient6, "HumidityRatioEquationCoefficient6", "Humidity Ratio Equation Coefficient 6"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient7, "HumidityRatioEquationCoefficient7", "Humidity Ratio Equation Coefficient 7"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient8, "HumidityRatioEquationCoefficient8", "Humidity Ratio Equation Coefficient 8"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation, "MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation", "Minimum Regeneration Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation, "MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation", "Maximum Regeneration Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirTemperatureforHumidityRatioEquation, "MinimumRegenerationInletAirTemperatureforHumidityRatioEquation", "Minimum Regeneration Inlet Air Temperature for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirTemperatureforHumidityRatioEquation, "MaximumRegenerationInletAirTemperatureforHumidityRatioEquation", "Maximum Regeneration Inlet Air Temperature for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirHumidityRatioforHumidityRatioEquation, "MinimumProcessInletAirHumidityRatioforHumidityRatioEquation", "Minimum Process Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirHumidityRatioforHumidityRatioEquation, "MaximumProcessInletAirHumidityRatioforHumidityRatioEquation", "Maximum Process Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirTemperatureforHumidityRatioEquation, "MinimumProcessInletAirTemperatureforHumidityRatioEquation", "Minimum Process Inlet Air Temperature for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirTemperatureforHumidityRatioEquation, "MaximumProcessInletAirTemperatureforHumidityRatioEquation", "Maximum Process Inlet Air Temperature for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationAirVelocityforHumidityRatioEquation, "MinimumRegenerationAirVelocityforHumidityRatioEquation", "Minimum Regeneration Air Velocity for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationAirVelocityforHumidityRatioEquation, "MaximumRegenerationAirVelocityforHumidityRatioEquation", "Maximum Regeneration Air Velocity for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, "MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation", "Minimum Regeneration Outlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, "MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation", "Maximum Regeneration Outlet Air Humidity Ratio for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, "MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation", "Minimum Regeneration Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, "MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation", "Maximum Regeneration Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation, "MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation", "Minimum Process Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation, "MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation", "Maximum Process Inlet Air Relative Humidity for Humidity Ratio Equation"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields> OptionalHeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX
