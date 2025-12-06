/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SETPOINTMANAGER_SYSTEMNODERESET_HUMIDITY_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_SYSTEMNODERESET_HUMIDITY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_SystemNodeReset_HumidityFields
 *  \brief Enumeration of SetpointManager:SystemNodeReset:Humidity's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_SystemNodeReset_HumidityFields, )
#else
class SetpointManager_SystemNodeReset_HumidityFields: public ::EnumBase<SetpointManager_SystemNodeReset_HumidityFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, SetpointatLowReferenceHumidityRatio, SetpointatHighReferenceHumidityRatio, LowReferenceHumidityRatio, HighReferenceHumidityRatio, ReferenceNodeName, SetpointNodeorNodeListName,   };
  SetpointManager_SystemNodeReset_HumidityFields()
   : EnumBase<SetpointManager_SystemNodeReset_HumidityFields>(Name) {} 
  SetpointManager_SystemNodeReset_HumidityFields(const std::string &t_name) 
   : EnumBase<SetpointManager_SystemNodeReset_HumidityFields>(t_name) {} 
  SetpointManager_SystemNodeReset_HumidityFields(int t_value) 
   : EnumBase<SetpointManager_SystemNodeReset_HumidityFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_SystemNodeReset_HumidityFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_SystemNodeReset_HumidityFields>::integer_value()); }
   private:
    friend class EnumBase<SetpointManager_SystemNodeReset_HumidityFields>;
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
{ SetpointManager_SystemNodeReset_HumidityFields::Name, "Name", "Name"},
{ SetpointManager_SystemNodeReset_HumidityFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_SystemNodeReset_HumidityFields::SetpointatLowReferenceHumidityRatio, "SetpointatLowReferenceHumidityRatio", "Setpoint at Low Reference Humidity Ratio"},
{ SetpointManager_SystemNodeReset_HumidityFields::SetpointatHighReferenceHumidityRatio, "SetpointatHighReferenceHumidityRatio", "Setpoint at High Reference Humidity Ratio"},
{ SetpointManager_SystemNodeReset_HumidityFields::LowReferenceHumidityRatio, "LowReferenceHumidityRatio", "Low Reference Humidity Ratio"},
{ SetpointManager_SystemNodeReset_HumidityFields::HighReferenceHumidityRatio, "HighReferenceHumidityRatio", "High Reference Humidity Ratio"},
{ SetpointManager_SystemNodeReset_HumidityFields::ReferenceNodeName, "ReferenceNodeName", "Reference Node Name"},
{ SetpointManager_SystemNodeReset_HumidityFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_SystemNodeReset_HumidityFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_SystemNodeReset_HumidityFields> OptionalSetpointManager_SystemNodeReset_HumidityFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_SYSTEMNODERESET_HUMIDITY_FIELDENUMS_HXX
