/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKSIMULATIONCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKSIMULATIONCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkSimulationControlFields
 *  \brief Enumeration of OS:AirflowNetworkSimulationControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkSimulationControlFields, )
#else
class OS_AirflowNetworkSimulationControlFields: public ::EnumBase<OS_AirflowNetworkSimulationControlFields> {
 public: 
  enum domain 
  {
Handle, Name, AirflowNetworkControl, WindPressureCoefficientType, HeightSelectionforLocalWindPressureCalculation, BuildingType, MaximumNumberofIterations, InitializationType, RelativeAirflowConvergenceTolerance, AbsoluteAirflowConvergenceTolerance, ConvergenceAccelerationLimit, AzimuthAngleofLongAxisofBuilding, RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis, HeightDependenceofExternalNodeTemperature, Solver, AllowUnsupportedZoneEquipment,   };
  OS_AirflowNetworkSimulationControlFields()
   : EnumBase<OS_AirflowNetworkSimulationControlFields>(Handle) {} 
  OS_AirflowNetworkSimulationControlFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkSimulationControlFields>(t_name) {} 
  OS_AirflowNetworkSimulationControlFields(int t_value) 
   : EnumBase<OS_AirflowNetworkSimulationControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkSimulationControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkSimulationControlFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkSimulationControlFields>;
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
{ OS_AirflowNetworkSimulationControlFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkSimulationControlFields::Name, "Name", "Name"},
{ OS_AirflowNetworkSimulationControlFields::AirflowNetworkControl, "AirflowNetworkControl", "AirflowNetwork Control"},
{ OS_AirflowNetworkSimulationControlFields::WindPressureCoefficientType, "WindPressureCoefficientType", "Wind Pressure Coefficient Type"},
{ OS_AirflowNetworkSimulationControlFields::HeightSelectionforLocalWindPressureCalculation, "HeightSelectionforLocalWindPressureCalculation", "Height Selection for Local Wind Pressure Calculation"},
{ OS_AirflowNetworkSimulationControlFields::BuildingType, "BuildingType", "Building Type"},
{ OS_AirflowNetworkSimulationControlFields::MaximumNumberofIterations, "MaximumNumberofIterations", "Maximum Number of Iterations"},
{ OS_AirflowNetworkSimulationControlFields::InitializationType, "InitializationType", "Initialization Type"},
{ OS_AirflowNetworkSimulationControlFields::RelativeAirflowConvergenceTolerance, "RelativeAirflowConvergenceTolerance", "Relative Airflow Convergence Tolerance"},
{ OS_AirflowNetworkSimulationControlFields::AbsoluteAirflowConvergenceTolerance, "AbsoluteAirflowConvergenceTolerance", "Absolute Airflow Convergence Tolerance"},
{ OS_AirflowNetworkSimulationControlFields::ConvergenceAccelerationLimit, "ConvergenceAccelerationLimit", "Convergence Acceleration Limit"},
{ OS_AirflowNetworkSimulationControlFields::AzimuthAngleofLongAxisofBuilding, "AzimuthAngleofLongAxisofBuilding", "Azimuth Angle of Long Axis of Building"},
{ OS_AirflowNetworkSimulationControlFields::RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis, "RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis", "Ratio of Building Width Along Short Axis to Width Along Long Axis"},
{ OS_AirflowNetworkSimulationControlFields::HeightDependenceofExternalNodeTemperature, "HeightDependenceofExternalNodeTemperature", "Height Dependence of External Node Temperature"},
{ OS_AirflowNetworkSimulationControlFields::Solver, "Solver", "Solver"},
{ OS_AirflowNetworkSimulationControlFields::AllowUnsupportedZoneEquipment, "AllowUnsupportedZoneEquipment", "Allow Unsupported Zone Equipment"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkSimulationControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkSimulationControlFields> OptionalOS_AirflowNetworkSimulationControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKSIMULATIONCONTROL_FIELDENUMS_HXX
