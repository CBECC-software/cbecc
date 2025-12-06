/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AVAILABILITYMANAGER_NIGHTCYCLE_FIELDENUMS_HXX
#define UTILITIES_IDD_AVAILABILITYMANAGER_NIGHTCYCLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AvailabilityManager_NightCycleFields
 *  \brief Enumeration of AvailabilityManager:NightCycle's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AvailabilityManager_NightCycleFields, )
#else
class AvailabilityManager_NightCycleFields: public ::EnumBase<AvailabilityManager_NightCycleFields> {
 public: 
  enum domain 
  {
Name, ApplicabilityScheduleName, FanScheduleName, ControlType, ThermostatTolerance, CyclingRunTimeControlType, CyclingRunTime, ControlZoneorZoneListName, CoolingControlZoneorZoneListName, HeatingControlZoneorZoneListName, HeatingZoneFansOnlyZoneorZoneListName,   };
  AvailabilityManager_NightCycleFields()
   : EnumBase<AvailabilityManager_NightCycleFields>(Name) {} 
  AvailabilityManager_NightCycleFields(const std::string &t_name) 
   : EnumBase<AvailabilityManager_NightCycleFields>(t_name) {} 
  AvailabilityManager_NightCycleFields(int t_value) 
   : EnumBase<AvailabilityManager_NightCycleFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManager_NightCycleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManager_NightCycleFields>::integer_value()); }
   private:
    friend class EnumBase<AvailabilityManager_NightCycleFields>;
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
{ AvailabilityManager_NightCycleFields::Name, "Name", "Name"},
{ AvailabilityManager_NightCycleFields::ApplicabilityScheduleName, "ApplicabilityScheduleName", "Applicability Schedule Name"},
{ AvailabilityManager_NightCycleFields::FanScheduleName, "FanScheduleName", "Fan Schedule Name"},
{ AvailabilityManager_NightCycleFields::ControlType, "ControlType", "Control Type"},
{ AvailabilityManager_NightCycleFields::ThermostatTolerance, "ThermostatTolerance", "Thermostat Tolerance"},
{ AvailabilityManager_NightCycleFields::CyclingRunTimeControlType, "CyclingRunTimeControlType", "Cycling Run Time Control Type"},
{ AvailabilityManager_NightCycleFields::CyclingRunTime, "CyclingRunTime", "Cycling Run Time"},
{ AvailabilityManager_NightCycleFields::ControlZoneorZoneListName, "ControlZoneorZoneListName", "Control Zone or Zone List Name"},
{ AvailabilityManager_NightCycleFields::CoolingControlZoneorZoneListName, "CoolingControlZoneorZoneListName", "Cooling Control Zone or Zone List Name"},
{ AvailabilityManager_NightCycleFields::HeatingControlZoneorZoneListName, "HeatingControlZoneorZoneListName", "Heating Control Zone or Zone List Name"},
{ AvailabilityManager_NightCycleFields::HeatingZoneFansOnlyZoneorZoneListName, "HeatingZoneFansOnlyZoneorZoneListName", "Heating Zone Fans Only Zone or Zone List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManager_NightCycleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManager_NightCycleFields> OptionalAvailabilityManager_NightCycleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AVAILABILITYMANAGER_NIGHTCYCLE_FIELDENUMS_HXX
