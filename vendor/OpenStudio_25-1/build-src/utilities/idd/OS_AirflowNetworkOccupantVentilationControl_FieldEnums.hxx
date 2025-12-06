/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkOccupantVentilationControlFields
 *  \brief Enumeration of OS:AirflowNetworkOccupantVentilationControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkOccupantVentilationControlFields, )
#else
class OS_AirflowNetworkOccupantVentilationControlFields: public ::EnumBase<OS_AirflowNetworkOccupantVentilationControlFields> {
 public: 
  enum domain 
  {
Handle, Name, MinimumOpeningTime, MinimumClosingTime, ThermalComfortLowTemperatureCurveName, ThermalComfortTemperatureBoundaryPoint, ThermalComfortHighTemperatureCurveName, MaximumPredictedPercentageofDissatisfiedThreshold, OccupancyCheck, OpeningProbabilityScheduleName, ClosingProbabilityScheduleName,   };
  OS_AirflowNetworkOccupantVentilationControlFields()
   : EnumBase<OS_AirflowNetworkOccupantVentilationControlFields>(Handle) {} 
  OS_AirflowNetworkOccupantVentilationControlFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkOccupantVentilationControlFields>(t_name) {} 
  OS_AirflowNetworkOccupantVentilationControlFields(int t_value) 
   : EnumBase<OS_AirflowNetworkOccupantVentilationControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkOccupantVentilationControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkOccupantVentilationControlFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkOccupantVentilationControlFields>;
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
{ OS_AirflowNetworkOccupantVentilationControlFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkOccupantVentilationControlFields::Name, "Name", "Name"},
{ OS_AirflowNetworkOccupantVentilationControlFields::MinimumOpeningTime, "MinimumOpeningTime", "Minimum Opening Time"},
{ OS_AirflowNetworkOccupantVentilationControlFields::MinimumClosingTime, "MinimumClosingTime", "Minimum Closing Time"},
{ OS_AirflowNetworkOccupantVentilationControlFields::ThermalComfortLowTemperatureCurveName, "ThermalComfortLowTemperatureCurveName", "Thermal Comfort Low Temperature Curve Name"},
{ OS_AirflowNetworkOccupantVentilationControlFields::ThermalComfortTemperatureBoundaryPoint, "ThermalComfortTemperatureBoundaryPoint", "Thermal Comfort Temperature Boundary Point"},
{ OS_AirflowNetworkOccupantVentilationControlFields::ThermalComfortHighTemperatureCurveName, "ThermalComfortHighTemperatureCurveName", "Thermal Comfort High Temperature Curve Name"},
{ OS_AirflowNetworkOccupantVentilationControlFields::MaximumPredictedPercentageofDissatisfiedThreshold, "MaximumPredictedPercentageofDissatisfiedThreshold", "Maximum Predicted Percentage of Dissatisfied Threshold"},
{ OS_AirflowNetworkOccupantVentilationControlFields::OccupancyCheck, "OccupancyCheck", "Occupancy Check"},
{ OS_AirflowNetworkOccupantVentilationControlFields::OpeningProbabilityScheduleName, "OpeningProbabilityScheduleName", "Opening Probability Schedule Name"},
{ OS_AirflowNetworkOccupantVentilationControlFields::ClosingProbabilityScheduleName, "ClosingProbabilityScheduleName", "Closing Probability Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkOccupantVentilationControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkOccupantVentilationControlFields> OptionalOS_AirflowNetworkOccupantVentilationControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_FIELDENUMS_HXX
