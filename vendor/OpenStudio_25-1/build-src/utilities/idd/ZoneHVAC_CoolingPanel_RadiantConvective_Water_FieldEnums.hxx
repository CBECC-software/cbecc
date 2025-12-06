/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_COOLINGPANEL_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_COOLINGPANEL_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields
 *  \brief Enumeration of ZoneHVAC:CoolingPanel:RadiantConvective:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields, )
#else
class ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields: public ::EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, WaterInletNodeName, WaterOutletNodeName, RatedInletWaterTemperature, RatedInletSpaceTemperature, RatedWaterMassFlowRate, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, MaximumChilledWaterFlowRate, ControlType, CoolingControlThrottlingRange, CoolingControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset, FractionRadiant, FractionofRadiantEnergyIncidentonPeople,   };
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields()
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields>(Name) {} 
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields>(t_name) {} 
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields(int t_value) 
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields>;
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
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::Name, "Name", "Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, "RatedInletWaterTemperature", "Rated Inlet Water Temperature"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, "RatedInletSpaceTemperature", "Rated Inlet Space Temperature"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, "RatedWaterMassFlowRate", "Rated Water Mass Flow Rate"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, "MaximumChilledWaterFlowRate", "Maximum Chilled Water Flow Rate"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, "ControlType", "Control Type"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, "CoolingControlThrottlingRange", "Cooling Control Throttling Range"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName, "CoolingControlTemperatureScheduleName", "Cooling Control Temperature Schedule Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofRadiantEnergyIncidentonPeople, "FractionofRadiantEnergyIncidentonPeople", "Fraction of Radiant Energy Incident on People"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields> OptionalZoneHVAC_CoolingPanel_RadiantConvective_WaterFields ;
#endif

/** \class ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields
 *  \brief Enumeration of ZoneHVAC:CoolingPanel:RadiantConvective:Water's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields, )
#else
class ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields: public ::EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, FractionofRadiantEnergytoSurface,   };
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields()
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields>(SurfaceName) {} 
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields>(t_name) {} 
  ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields>;
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
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::FractionofRadiantEnergytoSurface, "FractionofRadiantEnergytoSurface", "Fraction of Radiant Energy to Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields> OptionalZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_COOLINGPANEL_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX
