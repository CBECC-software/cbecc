/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SwimmingPool_IndoorFields
 *  \brief Enumeration of OS:SwimmingPool:Indoor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SwimmingPool_IndoorFields, )
#else
class OS_SwimmingPool_IndoorFields: public ::EnumBase<OS_SwimmingPool_IndoorFields> {
 public: 
  enum domain 
  {
Handle, Name, SurfaceName, AverageDepth, ActivityFactorScheduleName, MakeupWaterSupplyScheduleName, CoverScheduleName, CoverEvaporationFactor, CoverConvectionFactor, CoverShortWavelengthRadiationFactor, CoverLongWavelengthRadiationFactor, PoolWaterInletNode, PoolWaterOutletNode, PoolHeatingSystemMaximumWaterFlowRate, PoolMiscellaneousEquipmentPower, SetpointTemperatureSchedule, MaximumNumberofPeople, PeopleSchedule, PeopleHeatGainSchedule,   };
  OS_SwimmingPool_IndoorFields()
   : EnumBase<OS_SwimmingPool_IndoorFields>(Handle) {} 
  OS_SwimmingPool_IndoorFields(const std::string &t_name) 
   : EnumBase<OS_SwimmingPool_IndoorFields>(t_name) {} 
  OS_SwimmingPool_IndoorFields(int t_value) 
   : EnumBase<OS_SwimmingPool_IndoorFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SwimmingPool_IndoorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SwimmingPool_IndoorFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SwimmingPool_IndoorFields>;
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
{ OS_SwimmingPool_IndoorFields::Handle, "Handle", "Handle"},
{ OS_SwimmingPool_IndoorFields::Name, "Name", "Name"},
{ OS_SwimmingPool_IndoorFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SwimmingPool_IndoorFields::AverageDepth, "AverageDepth", "Average Depth"},
{ OS_SwimmingPool_IndoorFields::ActivityFactorScheduleName, "ActivityFactorScheduleName", "Activity Factor Schedule Name"},
{ OS_SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, "MakeupWaterSupplyScheduleName", "Make-up Water Supply Schedule Name"},
{ OS_SwimmingPool_IndoorFields::CoverScheduleName, "CoverScheduleName", "Cover Schedule Name"},
{ OS_SwimmingPool_IndoorFields::CoverEvaporationFactor, "CoverEvaporationFactor", "Cover Evaporation Factor"},
{ OS_SwimmingPool_IndoorFields::CoverConvectionFactor, "CoverConvectionFactor", "Cover Convection Factor"},
{ OS_SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, "CoverShortWavelengthRadiationFactor", "Cover Short-Wavelength Radiation Factor"},
{ OS_SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, "CoverLongWavelengthRadiationFactor", "Cover Long-Wavelength Radiation Factor"},
{ OS_SwimmingPool_IndoorFields::PoolWaterInletNode, "PoolWaterInletNode", "Pool Water Inlet Node"},
{ OS_SwimmingPool_IndoorFields::PoolWaterOutletNode, "PoolWaterOutletNode", "Pool Water Outlet Node"},
{ OS_SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, "PoolHeatingSystemMaximumWaterFlowRate", "Pool Heating System Maximum Water Flow Rate"},
{ OS_SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, "PoolMiscellaneousEquipmentPower", "Pool Miscellaneous Equipment Power"},
{ OS_SwimmingPool_IndoorFields::SetpointTemperatureSchedule, "SetpointTemperatureSchedule", "Setpoint Temperature Schedule"},
{ OS_SwimmingPool_IndoorFields::MaximumNumberofPeople, "MaximumNumberofPeople", "Maximum Number of People"},
{ OS_SwimmingPool_IndoorFields::PeopleSchedule, "PeopleSchedule", "People Schedule"},
{ OS_SwimmingPool_IndoorFields::PeopleHeatGainSchedule, "PeopleHeatGainSchedule", "People Heat Gain Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SwimmingPool_IndoorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SwimmingPool_IndoorFields> OptionalOS_SwimmingPool_IndoorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
