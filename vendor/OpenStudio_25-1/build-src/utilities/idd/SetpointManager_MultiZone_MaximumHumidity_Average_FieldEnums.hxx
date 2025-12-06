/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_MAXIMUMHUMIDITY_AVERAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_MAXIMUMHUMIDITY_AVERAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_MultiZone_MaximumHumidity_AverageFields
 *  \brief Enumeration of SetpointManager:MultiZone:MaximumHumidity:Average's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_MultiZone_MaximumHumidity_AverageFields, )
#else
class SetpointManager_MultiZone_MaximumHumidity_AverageFields: public ::EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields> {
 public: 
  enum domain 
  {
Name, HVACAirLoopName, MinimumSetpointHumidityRatio, MaximumSetpointHumidityRatio, SetpointNodeorNodeListName,   };
  SetpointManager_MultiZone_MaximumHumidity_AverageFields()
   : EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields>(Name) {} 
  SetpointManager_MultiZone_MaximumHumidity_AverageFields(const std::string &t_name) 
   : EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields>(t_name) {} 
  SetpointManager_MultiZone_MaximumHumidity_AverageFields(int t_value) 
   : EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_MultiZone_MaximumHumidity_AverageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields>::integer_value()); }
   private:
    friend class EnumBase<SetpointManager_MultiZone_MaximumHumidity_AverageFields>;
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
{ SetpointManager_MultiZone_MaximumHumidity_AverageFields::Name, "Name", "Name"},
{ SetpointManager_MultiZone_MaximumHumidity_AverageFields::HVACAirLoopName, "HVACAirLoopName", "HVAC Air Loop Name"},
{ SetpointManager_MultiZone_MaximumHumidity_AverageFields::MinimumSetpointHumidityRatio, "MinimumSetpointHumidityRatio", "Minimum Setpoint Humidity Ratio"},
{ SetpointManager_MultiZone_MaximumHumidity_AverageFields::MaximumSetpointHumidityRatio, "MaximumSetpointHumidityRatio", "Maximum Setpoint Humidity Ratio"},
{ SetpointManager_MultiZone_MaximumHumidity_AverageFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_MultiZone_MaximumHumidity_AverageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_MultiZone_MaximumHumidity_AverageFields> OptionalSetpointManager_MultiZone_MaximumHumidity_AverageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_MAXIMUMHUMIDITY_AVERAGE_FIELDENUMS_HXX
