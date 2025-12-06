/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SETPOINTMANAGER_WARMEST_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_WARMEST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_WarmestFields
 *  \brief Enumeration of SetpointManager:Warmest's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_WarmestFields, )
#else
class SetpointManager_WarmestFields: public ::EnumBase<SetpointManager_WarmestFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, HVACAirLoopName, MinimumSetpointTemperature, MaximumSetpointTemperature, Strategy, SetpointNodeorNodeListName,   };
  SetpointManager_WarmestFields()
   : EnumBase<SetpointManager_WarmestFields>(Name) {} 
  SetpointManager_WarmestFields(const std::string &t_name) 
   : EnumBase<SetpointManager_WarmestFields>(t_name) {} 
  SetpointManager_WarmestFields(int t_value) 
   : EnumBase<SetpointManager_WarmestFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_WarmestFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_WarmestFields>::integer_value()); }
   private:
    friend class EnumBase<SetpointManager_WarmestFields>;
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
{ SetpointManager_WarmestFields::Name, "Name", "Name"},
{ SetpointManager_WarmestFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_WarmestFields::HVACAirLoopName, "HVACAirLoopName", "HVAC Air Loop Name"},
{ SetpointManager_WarmestFields::MinimumSetpointTemperature, "MinimumSetpointTemperature", "Minimum Setpoint Temperature"},
{ SetpointManager_WarmestFields::MaximumSetpointTemperature, "MaximumSetpointTemperature", "Maximum Setpoint Temperature"},
{ SetpointManager_WarmestFields::Strategy, "Strategy", "Strategy"},
{ SetpointManager_WarmestFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_WarmestFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_WarmestFields> OptionalSetpointManager_WarmestFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_WARMEST_FIELDENUMS_HXX
