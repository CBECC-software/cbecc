/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_WINDOWSHADINGCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWSHADINGCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowShadingControlFields
 *  \brief Enumeration of WindowShadingControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowShadingControlFields, )
#else
class WindowShadingControlFields: public ::EnumBase<WindowShadingControlFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ShadingControlSequenceNumber, ShadingType, ConstructionwithShadingName, ShadingControlType, ScheduleName, Setpoint, ShadingControlIsScheduled, GlareControlIsActive, ShadingDeviceMaterialName, TypeofSlatAngleControlforBlinds, SlatAngleScheduleName, Setpoint2, DaylightingControlObjectName, MultipleSurfaceControlType,   };
  WindowShadingControlFields()
   : EnumBase<WindowShadingControlFields>(Name) {} 
  WindowShadingControlFields(const std::string &t_name) 
   : EnumBase<WindowShadingControlFields>(t_name) {} 
  WindowShadingControlFields(int t_value) 
   : EnumBase<WindowShadingControlFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowShadingControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowShadingControlFields>::integer_value()); }
   private:
    friend class EnumBase<WindowShadingControlFields>;
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
{ WindowShadingControlFields::Name, "Name", "Name"},
{ WindowShadingControlFields::ZoneName, "ZoneName", "Zone Name"},
{ WindowShadingControlFields::ShadingControlSequenceNumber, "ShadingControlSequenceNumber", "Shading Control Sequence Number"},
{ WindowShadingControlFields::ShadingType, "ShadingType", "Shading Type"},
{ WindowShadingControlFields::ConstructionwithShadingName, "ConstructionwithShadingName", "Construction with Shading Name"},
{ WindowShadingControlFields::ShadingControlType, "ShadingControlType", "Shading Control Type"},
{ WindowShadingControlFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ WindowShadingControlFields::Setpoint, "Setpoint", "Setpoint"},
{ WindowShadingControlFields::ShadingControlIsScheduled, "ShadingControlIsScheduled", "Shading Control Is Scheduled"},
{ WindowShadingControlFields::GlareControlIsActive, "GlareControlIsActive", "Glare Control Is Active"},
{ WindowShadingControlFields::ShadingDeviceMaterialName, "ShadingDeviceMaterialName", "Shading Device Material Name"},
{ WindowShadingControlFields::TypeofSlatAngleControlforBlinds, "TypeofSlatAngleControlforBlinds", "Type of Slat Angle Control for Blinds"},
{ WindowShadingControlFields::SlatAngleScheduleName, "SlatAngleScheduleName", "Slat Angle Schedule Name"},
{ WindowShadingControlFields::Setpoint2, "Setpoint2", "Setpoint 2"},
{ WindowShadingControlFields::DaylightingControlObjectName, "DaylightingControlObjectName", "Daylighting Control Object Name"},
{ WindowShadingControlFields::MultipleSurfaceControlType, "MultipleSurfaceControlType", "Multiple Surface Control Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowShadingControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowShadingControlFields> OptionalWindowShadingControlFields ;
#endif

/** \class WindowShadingControlExtensibleFields
 *  \brief Enumeration of WindowShadingControl's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(WindowShadingControlExtensibleFields, )
#else
class WindowShadingControlExtensibleFields: public ::EnumBase<WindowShadingControlExtensibleFields> {
 public: 
  enum domain 
  {
FenestrationSurfaceName,   };
  WindowShadingControlExtensibleFields()
   : EnumBase<WindowShadingControlExtensibleFields>(FenestrationSurfaceName) {} 
  WindowShadingControlExtensibleFields(const std::string &t_name) 
   : EnumBase<WindowShadingControlExtensibleFields>(t_name) {} 
  WindowShadingControlExtensibleFields(int t_value) 
   : EnumBase<WindowShadingControlExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowShadingControlExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowShadingControlExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<WindowShadingControlExtensibleFields>;
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
{ WindowShadingControlExtensibleFields::FenestrationSurfaceName, "FenestrationSurfaceName", "Fenestration Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowShadingControlExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowShadingControlExtensibleFields> OptionalWindowShadingControlExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWSHADINGCONTROL_FIELDENUMS_HXX
