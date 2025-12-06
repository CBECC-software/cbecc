/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_Baseboard_RadiantConvective_WaterFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:RadiantConvective:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_RadiantConvective_WaterFields, )
#else
class ZoneHVAC_Baseboard_RadiantConvective_WaterFields: public ::EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields> {
 public: 
  enum domain 
  {
Name, DesignObject, AvailabilityScheduleName, InletNodeName, OutletNodeName, RatedAverageWaterTemperature, RatedWaterMassFlowRate, HeatingDesignCapacity, MaximumWaterFlowRate,   };
  ZoneHVAC_Baseboard_RadiantConvective_WaterFields()
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields>(Name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_WaterFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields>(t_name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_WaterFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_RadiantConvective_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterFields>;
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
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::Name, "Name", "Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject, "DesignObject", "Design Object"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, "RatedAverageWaterTemperature", "Rated Average Water Temperature"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, "RatedWaterMassFlowRate", "Rated Water Mass Flow Rate"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, "MaximumWaterFlowRate", "Maximum Water Flow Rate"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_RadiantConvective_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_RadiantConvective_WaterFields> OptionalZoneHVAC_Baseboard_RadiantConvective_WaterFields ;
#endif

/** \class ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:RadiantConvective:Water's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields, )
#else
class ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields: public ::EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, FractionofRadiantEnergytoSurface,   };
  ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields()
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields>(SurfaceName) {} 
  ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields>(t_name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields>;
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
{ ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields::FractionofRadiantEnergytoSurface, "FractionofRadiantEnergytoSurface", "Fraction of Radiant Energy to Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields> OptionalZoneHVAC_Baseboard_RadiantConvective_WaterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_FIELDENUMS_HXX
