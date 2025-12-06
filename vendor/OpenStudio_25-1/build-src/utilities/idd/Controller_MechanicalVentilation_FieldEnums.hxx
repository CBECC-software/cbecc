/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Controller_MechanicalVentilationFields
 *  \brief Enumeration of Controller:MechanicalVentilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Controller_MechanicalVentilationFields, )
#else
class Controller_MechanicalVentilationFields: public ::EnumBase<Controller_MechanicalVentilationFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DemandControlledVentilation, SystemOutdoorAirMethod, ZoneMaximumOutdoorAirFraction,   };
  Controller_MechanicalVentilationFields()
   : EnumBase<Controller_MechanicalVentilationFields>(Name) {} 
  Controller_MechanicalVentilationFields(const std::string &t_name) 
   : EnumBase<Controller_MechanicalVentilationFields>(t_name) {} 
  Controller_MechanicalVentilationFields(int t_value) 
   : EnumBase<Controller_MechanicalVentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "Controller_MechanicalVentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Controller_MechanicalVentilationFields>::integer_value()); }
   private:
    friend class EnumBase<Controller_MechanicalVentilationFields>;
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
{ Controller_MechanicalVentilationFields::Name, "Name", "Name"},
{ Controller_MechanicalVentilationFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Controller_MechanicalVentilationFields::DemandControlledVentilation, "DemandControlledVentilation", "Demand Controlled Ventilation"},
{ Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, "SystemOutdoorAirMethod", "System Outdoor Air Method"},
{ Controller_MechanicalVentilationFields::ZoneMaximumOutdoorAirFraction, "ZoneMaximumOutdoorAirFraction", "Zone Maximum Outdoor Air Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const Controller_MechanicalVentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Controller_MechanicalVentilationFields> OptionalController_MechanicalVentilationFields ;
#endif

/** \class Controller_MechanicalVentilationExtensibleFields
 *  \brief Enumeration of Controller:MechanicalVentilation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Controller_MechanicalVentilationExtensibleFields, )
#else
class Controller_MechanicalVentilationExtensibleFields: public ::EnumBase<Controller_MechanicalVentilationExtensibleFields> {
 public: 
  enum domain 
  {
ZoneorZoneListName, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName,   };
  Controller_MechanicalVentilationExtensibleFields()
   : EnumBase<Controller_MechanicalVentilationExtensibleFields>(ZoneorZoneListName) {} 
  Controller_MechanicalVentilationExtensibleFields(const std::string &t_name) 
   : EnumBase<Controller_MechanicalVentilationExtensibleFields>(t_name) {} 
  Controller_MechanicalVentilationExtensibleFields(int t_value) 
   : EnumBase<Controller_MechanicalVentilationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Controller_MechanicalVentilationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Controller_MechanicalVentilationExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<Controller_MechanicalVentilationExtensibleFields>;
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
{ Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ Controller_MechanicalVentilationExtensibleFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Controller_MechanicalVentilationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Controller_MechanicalVentilationExtensibleFields> OptionalController_MechanicalVentilationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX
