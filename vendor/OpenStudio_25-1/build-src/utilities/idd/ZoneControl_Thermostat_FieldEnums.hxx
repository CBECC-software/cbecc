/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneControl_ThermostatFields
 *  \brief Enumeration of ZoneControl:Thermostat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneControl_ThermostatFields, )
#else
class ZoneControl_ThermostatFields: public ::EnumBase<ZoneControl_ThermostatFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, ControlTypeScheduleName, Control1ObjectType, Control1Name, Control2ObjectType, Control2Name, Control3ObjectType, Control3Name, Control4ObjectType, Control4Name, TemperatureDifferenceBetweenCutoutAndSetpoint,   };
  ZoneControl_ThermostatFields()
   : EnumBase<ZoneControl_ThermostatFields>(Name) {} 
  ZoneControl_ThermostatFields(const std::string &t_name) 
   : EnumBase<ZoneControl_ThermostatFields>(t_name) {} 
  ZoneControl_ThermostatFields(int t_value) 
   : EnumBase<ZoneControl_ThermostatFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_ThermostatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_ThermostatFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneControl_ThermostatFields>;
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
{ ZoneControl_ThermostatFields::Name, "Name", "Name"},
{ ZoneControl_ThermostatFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ ZoneControl_ThermostatFields::ControlTypeScheduleName, "ControlTypeScheduleName", "Control Type Schedule Name"},
{ ZoneControl_ThermostatFields::Control1ObjectType, "Control1ObjectType", "Control 1 Object Type"},
{ ZoneControl_ThermostatFields::Control1Name, "Control1Name", "Control 1 Name"},
{ ZoneControl_ThermostatFields::Control2ObjectType, "Control2ObjectType", "Control 2 Object Type"},
{ ZoneControl_ThermostatFields::Control2Name, "Control2Name", "Control 2 Name"},
{ ZoneControl_ThermostatFields::Control3ObjectType, "Control3ObjectType", "Control 3 Object Type"},
{ ZoneControl_ThermostatFields::Control3Name, "Control3Name", "Control 3 Name"},
{ ZoneControl_ThermostatFields::Control4ObjectType, "Control4ObjectType", "Control 4 Object Type"},
{ ZoneControl_ThermostatFields::Control4Name, "Control4Name", "Control 4 Name"},
{ ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint, "TemperatureDifferenceBetweenCutoutAndSetpoint", "Temperature Difference Between Cutout And Setpoint"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_ThermostatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_ThermostatFields> OptionalZoneControl_ThermostatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX
