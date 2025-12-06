/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRTERMINAL_DUALDUCT_VAV_OUTDOORAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRTERMINAL_DUALDUCT_VAV_OUTDOORAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirTerminal_DualDuct_VAV_OutdoorAirFields
 *  \brief Enumeration of OS:AirTerminal:DualDuct:VAV:OutdoorAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirTerminal_DualDuct_VAV_OutdoorAirFields, )
#else
class OS_AirTerminal_DualDuct_VAV_OutdoorAirFields: public ::EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, AirOutletNode, OutdoorAirInletNode, RecirculatedAirInletNode, MaximumTerminalAirFlowRate, ControlForOutdoorAir, PerPersonVentilationRateMode,   };
  OS_AirTerminal_DualDuct_VAV_OutdoorAirFields()
   : EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields>(Handle) {} 
  OS_AirTerminal_DualDuct_VAV_OutdoorAirFields(const std::string &t_name) 
   : EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields>(t_name) {} 
  OS_AirTerminal_DualDuct_VAV_OutdoorAirFields(int t_value) 
   : EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirTerminal_DualDuct_VAV_OutdoorAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields>;
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
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::Handle, "Handle", "Handle"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::Name, "Name", "Name"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::AirOutletNode, "AirOutletNode", "Air Outlet Node"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::OutdoorAirInletNode, "OutdoorAirInletNode", "Outdoor Air Inlet Node"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::RecirculatedAirInletNode, "RecirculatedAirInletNode", "Recirculated Air Inlet Node"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::MaximumTerminalAirFlowRate, "MaximumTerminalAirFlowRate", "Maximum Terminal Air Flow Rate"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::ControlForOutdoorAir, "ControlForOutdoorAir", "Control For Outdoor Air"},
{ OS_AirTerminal_DualDuct_VAV_OutdoorAirFields::PerPersonVentilationRateMode, "PerPersonVentilationRateMode", "Per Person Ventilation Rate Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirTerminal_DualDuct_VAV_OutdoorAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirTerminal_DualDuct_VAV_OutdoorAirFields> OptionalOS_AirTerminal_DualDuct_VAV_OutdoorAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRTERMINAL_DUALDUCT_VAV_OUTDOORAIR_FIELDENUMS_HXX
