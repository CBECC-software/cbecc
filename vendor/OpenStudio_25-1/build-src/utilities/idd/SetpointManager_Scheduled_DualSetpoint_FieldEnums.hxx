/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SETPOINTMANAGER_SCHEDULED_DUALSETPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_SCHEDULED_DUALSETPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_Scheduled_DualSetpointFields
 *  \brief Enumeration of SetpointManager:Scheduled:DualSetpoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_Scheduled_DualSetpointFields, )
#else
class SetpointManager_Scheduled_DualSetpointFields: public ::EnumBase<SetpointManager_Scheduled_DualSetpointFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, HighSetpointScheduleName, LowSetpointScheduleName, SetpointNodeorNodeListName,   };
  SetpointManager_Scheduled_DualSetpointFields()
   : EnumBase<SetpointManager_Scheduled_DualSetpointFields>(Name) {} 
  SetpointManager_Scheduled_DualSetpointFields(const std::string &t_name) 
   : EnumBase<SetpointManager_Scheduled_DualSetpointFields>(t_name) {} 
  SetpointManager_Scheduled_DualSetpointFields(int t_value) 
   : EnumBase<SetpointManager_Scheduled_DualSetpointFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_Scheduled_DualSetpointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_Scheduled_DualSetpointFields>::integer_value()); }
   private:
    friend class EnumBase<SetpointManager_Scheduled_DualSetpointFields>;
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
{ SetpointManager_Scheduled_DualSetpointFields::Name, "Name", "Name"},
{ SetpointManager_Scheduled_DualSetpointFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_Scheduled_DualSetpointFields::HighSetpointScheduleName, "HighSetpointScheduleName", "High Setpoint Schedule Name"},
{ SetpointManager_Scheduled_DualSetpointFields::LowSetpointScheduleName, "LowSetpointScheduleName", "Low Setpoint Schedule Name"},
{ SetpointManager_Scheduled_DualSetpointFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_Scheduled_DualSetpointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_Scheduled_DualSetpointFields> OptionalSetpointManager_Scheduled_DualSetpointFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_SCHEDULED_DUALSETPOINT_FIELDENUMS_HXX
