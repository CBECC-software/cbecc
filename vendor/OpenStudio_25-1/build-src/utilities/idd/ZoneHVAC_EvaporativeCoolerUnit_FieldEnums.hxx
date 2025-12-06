/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EvaporativeCoolerUnitFields
 *  \brief Enumeration of ZoneHVAC:EvaporativeCoolerUnit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EvaporativeCoolerUnitFields, )
#else
class ZoneHVAC_EvaporativeCoolerUnitFields: public ::EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AvailabilityManagerListName, OutdoorAirInletNodeName, CoolerOutletNodeName, ZoneReliefAirNodeName, SupplyAirFanObjectType, SupplyAirFanName, DesignSupplyAirFlowRate, FanPlacement, CoolerUnitControlMethod, ThrottlingRangeTemperatureDifference, CoolingLoadControlThresholdHeatTransferRate, FirstEvaporativeCoolerObjectType, FirstEvaporativeCoolerObjectName, SecondEvaporativeCoolerObjectType, SecondEvaporativeCoolerName, DesignSpecificationZoneHVACSizingObjectName, ShutOffRelativeHumidity,   };
  ZoneHVAC_EvaporativeCoolerUnitFields()
   : EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields>(Name) {} 
  ZoneHVAC_EvaporativeCoolerUnitFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields>(t_name) {} 
  ZoneHVAC_EvaporativeCoolerUnitFields(int t_value) 
   : EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EvaporativeCoolerUnitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_EvaporativeCoolerUnitFields>;
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
{ ZoneHVAC_EvaporativeCoolerUnitFields::Name, "Name", "Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::CoolerOutletNodeName, "CoolerOutletNodeName", "Cooler Outlet Node Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::ZoneReliefAirNodeName, "ZoneReliefAirNodeName", "Zone Relief Air Node Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, "DesignSupplyAirFlowRate", "Design Supply Air Flow Rate"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, "CoolerUnitControlMethod", "Cooler Unit Control Method"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, "ThrottlingRangeTemperatureDifference", "Throttling Range Temperature Difference"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate, "CoolingLoadControlThresholdHeatTransferRate", "Cooling Load Control Threshold Heat Transfer Rate"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectType, "FirstEvaporativeCoolerObjectType", "First Evaporative Cooler Object Type"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName, "FirstEvaporativeCoolerObjectName", "First Evaporative Cooler Object Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, "SecondEvaporativeCoolerObjectType", "Second Evaporative Cooler Object Type"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName, "SecondEvaporativeCoolerName", "Second Evaporative Cooler Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, "ShutOffRelativeHumidity", "Shut Off Relative Humidity"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EvaporativeCoolerUnitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EvaporativeCoolerUnitFields> OptionalZoneHVAC_EvaporativeCoolerUnitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_EVAPORATIVECOOLERUNIT_FIELDENUMS_HXX
