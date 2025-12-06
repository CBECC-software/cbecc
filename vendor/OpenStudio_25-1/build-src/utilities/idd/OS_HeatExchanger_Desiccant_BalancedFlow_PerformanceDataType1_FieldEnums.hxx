/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields
 *  \brief Enumeration of OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields, )
#else
class OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields: public ::EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields> {
 public: 
  enum domain 
  {
Handle, Name, NominalAirFlowRate, NominalAirFaceVelocity, NominalElectricPower, TemperatureEquationCoefficient1, TemperatureEquationCoefficient2, TemperatureEquationCoefficient3, TemperatureEquationCoefficient4, TemperatureEquationCoefficient5, TemperatureEquationCoefficient6, TemperatureEquationCoefficient7, TemperatureEquationCoefficient8, MinimumRegenerationInletAirHumidityRatioforTemperatureEquation, MaximumRegenerationInletAirHumidityRatioforTemperatureEquation, MinimumRegenerationInletAirTemperatureforTemperatureEquation, MaximumRegenerationInletAirTemperatureforTemperatureEquation, MinimumProcessInletAirHumidityRatioforTemperatureEquation, MaximumProcessInletAirHumidityRatioforTemperatureEquation, MinimumProcessInletAirTemperatureforTemperatureEquation, MaximumProcessInletAirTemperatureforTemperatureEquation, MinimumRegenerationAirVelocityforTemperatureEquation, MaximumRegenerationAirVelocityforTemperatureEquation, MinimumRegenerationOutletAirTemperatureforTemperatureEquation, MaximumRegenerationOutletAirTemperatureforTemperatureEquation, MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation, MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation, MinimumProcessInletAirRelativeHumidityforTemperatureEquation, MaximumProcessInletAirRelativeHumidityforTemperatureEquation, HumidityRatioEquationCoefficient1, HumidityRatioEquationCoefficient2, HumidityRatioEquationCoefficient3, HumidityRatioEquationCoefficient4, HumidityRatioEquationCoefficient5, HumidityRatioEquationCoefficient6, HumidityRatioEquationCoefficient7, HumidityRatioEquationCoefficient8, MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation, MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation, MinimumRegenerationInletAirTemperatureforHumidityRatioEquation, MaximumRegenerationInletAirTemperatureforHumidityRatioEquation, MinimumProcessInletAirHumidityRatioforHumidityRatioEquation, MaximumProcessInletAirHumidityRatioforHumidityRatioEquation, MinimumProcessInletAirTemperatureforHumidityRatioEquation, MaximumProcessInletAirTemperatureforHumidityRatioEquation, MinimumRegenerationAirVelocityforHumidityRatioEquation, MaximumRegenerationAirVelocityforHumidityRatioEquation, MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation, MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation,   };
  OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields()
   : EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(Handle) {} 
  OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields(const std::string &t_name) 
   : EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(t_name) {} 
  OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields(int t_value) 
   : EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>::integer_value()); }
   private:
    friend class EnumBase<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields>;
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
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::Handle, "Handle", "Handle"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::Name, "Name", "Name"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalAirFlowRate, "NominalAirFlowRate", "Nominal Air Flow Rate"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalAirFaceVelocity, "NominalAirFaceVelocity", "Nominal Air Face Velocity"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::NominalElectricPower, "NominalElectricPower", "Nominal Electric Power"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient1, "TemperatureEquationCoefficient1", "Temperature Equation Coefficient 1"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient2, "TemperatureEquationCoefficient2", "Temperature Equation Coefficient 2"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient3, "TemperatureEquationCoefficient3", "Temperature Equation Coefficient 3"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient4, "TemperatureEquationCoefficient4", "Temperature Equation Coefficient 4"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient5, "TemperatureEquationCoefficient5", "Temperature Equation Coefficient 5"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient6, "TemperatureEquationCoefficient6", "Temperature Equation Coefficient 6"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient7, "TemperatureEquationCoefficient7", "Temperature Equation Coefficient 7"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::TemperatureEquationCoefficient8, "TemperatureEquationCoefficient8", "Temperature Equation Coefficient 8"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirHumidityRatioforTemperatureEquation, "MinimumRegenerationInletAirHumidityRatioforTemperatureEquation", "Minimum Regeneration Inlet Air Humidity Ratio for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirHumidityRatioforTemperatureEquation, "MaximumRegenerationInletAirHumidityRatioforTemperatureEquation", "Maximum Regeneration Inlet Air Humidity Ratio for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirTemperatureforTemperatureEquation, "MinimumRegenerationInletAirTemperatureforTemperatureEquation", "Minimum Regeneration Inlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirTemperatureforTemperatureEquation, "MaximumRegenerationInletAirTemperatureforTemperatureEquation", "Maximum Regeneration Inlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirHumidityRatioforTemperatureEquation, "MinimumProcessInletAirHumidityRatioforTemperatureEquation", "Minimum Process Inlet Air Humidity Ratio for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirHumidityRatioforTemperatureEquation, "MaximumProcessInletAirHumidityRatioforTemperatureEquation", "Maximum Process Inlet Air Humidity Ratio for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirTemperatureforTemperatureEquation, "MinimumProcessInletAirTemperatureforTemperatureEquation", "Minimum Process Inlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirTemperatureforTemperatureEquation, "MaximumProcessInletAirTemperatureforTemperatureEquation", "Maximum Process Inlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationAirVelocityforTemperatureEquation, "MinimumRegenerationAirVelocityforTemperatureEquation", "Minimum Regeneration Air Velocity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationAirVelocityforTemperatureEquation, "MaximumRegenerationAirVelocityforTemperatureEquation", "Maximum Regeneration Air Velocity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationOutletAirTemperatureforTemperatureEquation, "MinimumRegenerationOutletAirTemperatureforTemperatureEquation", "Minimum Regeneration Outlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationOutletAirTemperatureforTemperatureEquation, "MaximumRegenerationOutletAirTemperatureforTemperatureEquation", "Maximum Regeneration Outlet Air Temperature for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation, "MinimumRegenerationInletAirRelativeHumidityforTemperatureEquation", "Minimum Regeneration Inlet Air Relative Humidity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation, "MaximumRegenerationInletAirRelativeHumidityforTemperatureEquation", "Maximum Regeneration Inlet Air Relative Humidity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirRelativeHumidityforTemperatureEquation, "MinimumProcessInletAirRelativeHumidityforTemperatureEquation", "Minimum Process Inlet Air Relative Humidity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirRelativeHumidityforTemperatureEquation, "MaximumProcessInletAirRelativeHumidityforTemperatureEquation", "Maximum Process Inlet Air Relative Humidity for Temperature Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient1, "HumidityRatioEquationCoefficient1", "Humidity Ratio Equation Coefficient 1"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient2, "HumidityRatioEquationCoefficient2", "Humidity Ratio Equation Coefficient 2"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient3, "HumidityRatioEquationCoefficient3", "Humidity Ratio Equation Coefficient 3"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient4, "HumidityRatioEquationCoefficient4", "Humidity Ratio Equation Coefficient 4"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient5, "HumidityRatioEquationCoefficient5", "Humidity Ratio Equation Coefficient 5"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient6, "HumidityRatioEquationCoefficient6", "Humidity Ratio Equation Coefficient 6"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient7, "HumidityRatioEquationCoefficient7", "Humidity Ratio Equation Coefficient 7"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::HumidityRatioEquationCoefficient8, "HumidityRatioEquationCoefficient8", "Humidity Ratio Equation Coefficient 8"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation, "MinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation", "Minimum Regeneration Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation, "MaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation", "Maximum Regeneration Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirTemperatureforHumidityRatioEquation, "MinimumRegenerationInletAirTemperatureforHumidityRatioEquation", "Minimum Regeneration Inlet Air Temperature for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirTemperatureforHumidityRatioEquation, "MaximumRegenerationInletAirTemperatureforHumidityRatioEquation", "Maximum Regeneration Inlet Air Temperature for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirHumidityRatioforHumidityRatioEquation, "MinimumProcessInletAirHumidityRatioforHumidityRatioEquation", "Minimum Process Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirHumidityRatioforHumidityRatioEquation, "MaximumProcessInletAirHumidityRatioforHumidityRatioEquation", "Maximum Process Inlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirTemperatureforHumidityRatioEquation, "MinimumProcessInletAirTemperatureforHumidityRatioEquation", "Minimum Process Inlet Air Temperature for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirTemperatureforHumidityRatioEquation, "MaximumProcessInletAirTemperatureforHumidityRatioEquation", "Maximum Process Inlet Air Temperature for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationAirVelocityforHumidityRatioEquation, "MinimumRegenerationAirVelocityforHumidityRatioEquation", "Minimum Regeneration Air Velocity for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationAirVelocityforHumidityRatioEquation, "MaximumRegenerationAirVelocityforHumidityRatioEquation", "Maximum Regeneration Air Velocity for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, "MinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation", "Minimum Regeneration Outlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation, "MaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation", "Maximum Regeneration Outlet Air Humidity Ratio for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, "MinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation", "Minimum Regeneration Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation, "MaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation", "Maximum Regeneration Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation, "MinimumProcessInletAirRelativeHumidityforHumidityRatioEquation", "Minimum Process Inlet Air Relative Humidity for Humidity Ratio Equation"},
{ OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields::MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation, "MaximumProcessInletAirRelativeHumidityforHumidityRatioEquation", "Maximum Process Inlet Air Relative Humidity for Humidity Ratio Equation"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields> OptionalOS_HeatExchanger_Desiccant_BalancedFlow_PerformanceDataType1Fields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATEXCHANGER_DESICCANT_BALANCEDFLOW_PERFORMANCEDATATYPE1_FIELDENUMS_HXX
