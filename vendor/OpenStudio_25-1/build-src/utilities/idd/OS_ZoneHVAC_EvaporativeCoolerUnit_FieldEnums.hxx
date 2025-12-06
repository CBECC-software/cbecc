/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_EvaporativeCoolerUnitFields
 *  \brief Enumeration of OS:ZoneHVAC:EvaporativeCoolerUnit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_EvaporativeCoolerUnitFields, )
#else
class OS_ZoneHVAC_EvaporativeCoolerUnitFields: public ::EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AvailabilityManagerListName, OutdoorAirInletNodeName, CoolerOutletNodeName, ZoneReliefAirNodeName, SupplyAirFanName, DesignSupplyAirFlowRate, FanPlacement, CoolerUnitControlMethod, ThrottlingRangeTemperatureDifference, CoolingLoadControlThresholdHeatTransferRate, FirstEvaporativeCooler, SecondEvaporativeCooler, DesignSpecificationZoneHVACSizing, ShutOffRelativeHumidity,   };
  OS_ZoneHVAC_EvaporativeCoolerUnitFields()
   : EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields>(Handle) {} 
  OS_ZoneHVAC_EvaporativeCoolerUnitFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields>(t_name) {} 
  OS_ZoneHVAC_EvaporativeCoolerUnitFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_EvaporativeCoolerUnitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_EvaporativeCoolerUnitFields>;
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
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::CoolerOutletNodeName, "CoolerOutletNodeName", "Cooler Outlet Node Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::ZoneReliefAirNodeName, "ZoneReliefAirNodeName", "Zone Relief Air Node Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, "DesignSupplyAirFlowRate", "Design Supply Air Flow Rate"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, "CoolerUnitControlMethod", "Cooler Unit Control Method"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, "ThrottlingRangeTemperatureDifference", "Throttling Range Temperature Difference"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate, "CoolingLoadControlThresholdHeatTransferRate", "Cooling Load Control Threshold Heat Transfer Rate"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCooler, "FirstEvaporativeCooler", "First Evaporative Cooler"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCooler, "SecondEvaporativeCooler", "Second Evaporative Cooler"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::DesignSpecificationZoneHVACSizing, "DesignSpecificationZoneHVACSizing", "Design Specification ZoneHVAC Sizing"},
{ OS_ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, "ShutOffRelativeHumidity", "Shut Off Relative Humidity"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_EvaporativeCoolerUnitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_EvaporativeCoolerUnitFields> OptionalOS_ZoneHVAC_EvaporativeCoolerUnitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX
