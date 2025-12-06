/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_MULTISYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_MULTISYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollector_UnglazedTranspired_MultisystemFields
 *  \brief Enumeration of SolarCollector:UnglazedTranspired:Multisystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollector_UnglazedTranspired_MultisystemFields, )
#else
class SolarCollector_UnglazedTranspired_MultisystemFields: public ::EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields> {
 public: 
  enum domain 
  {
SolarCollectorName,   };
  SolarCollector_UnglazedTranspired_MultisystemFields()
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields>(SolarCollectorName) {} 
  SolarCollector_UnglazedTranspired_MultisystemFields(const std::string &t_name) 
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields>(t_name) {} 
  SolarCollector_UnglazedTranspired_MultisystemFields(int t_value) 
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollector_UnglazedTranspired_MultisystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields>::integer_value()); }
   private:
    friend class EnumBase<SolarCollector_UnglazedTranspired_MultisystemFields>;
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
{ SolarCollector_UnglazedTranspired_MultisystemFields::SolarCollectorName, "SolarCollectorName", "Solar Collector Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollector_UnglazedTranspired_MultisystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollector_UnglazedTranspired_MultisystemFields> OptionalSolarCollector_UnglazedTranspired_MultisystemFields ;
#endif

/** \class SolarCollector_UnglazedTranspired_MultisystemExtensibleFields
 *  \brief Enumeration of SolarCollector:UnglazedTranspired:Multisystem's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SolarCollector_UnglazedTranspired_MultisystemExtensibleFields, )
#else
class SolarCollector_UnglazedTranspired_MultisystemExtensibleFields: public ::EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields> {
 public: 
  enum domain 
  {
OutdoorAirSystemCollectorInletNode, OutdoorAirSystemCollectorOutletNode, OutdoorAirSystemMixedAirNode, OutdoorAirSystemZoneNode,   };
  SolarCollector_UnglazedTranspired_MultisystemExtensibleFields()
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields>(OutdoorAirSystemCollectorInletNode) {} 
  SolarCollector_UnglazedTranspired_MultisystemExtensibleFields(const std::string &t_name) 
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields>(t_name) {} 
  SolarCollector_UnglazedTranspired_MultisystemExtensibleFields(int t_value) 
   : EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollector_UnglazedTranspired_MultisystemExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields>;
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
{ SolarCollector_UnglazedTranspired_MultisystemExtensibleFields::OutdoorAirSystemCollectorInletNode, "OutdoorAirSystemCollectorInletNode", "Outdoor Air System Collector Inlet Node"},
{ SolarCollector_UnglazedTranspired_MultisystemExtensibleFields::OutdoorAirSystemCollectorOutletNode, "OutdoorAirSystemCollectorOutletNode", "Outdoor Air System Collector Outlet Node"},
{ SolarCollector_UnglazedTranspired_MultisystemExtensibleFields::OutdoorAirSystemMixedAirNode, "OutdoorAirSystemMixedAirNode", "Outdoor Air System Mixed Air Node"},
{ SolarCollector_UnglazedTranspired_MultisystemExtensibleFields::OutdoorAirSystemZoneNode, "OutdoorAirSystemZoneNode", "Outdoor Air System Zone Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollector_UnglazedTranspired_MultisystemExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollector_UnglazedTranspired_MultisystemExtensibleFields> OptionalSolarCollector_UnglazedTranspired_MultisystemExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_MULTISYSTEM_FIELDENUMS_HXX
