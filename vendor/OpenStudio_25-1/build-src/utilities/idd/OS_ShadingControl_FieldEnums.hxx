/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ShadingControlFields
 *  \brief Enumeration of OS:ShadingControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadingControlFields, )
#else
class OS_ShadingControlFields: public ::EnumBase<OS_ShadingControlFields> {
 public: 
  enum domain 
  {
Handle, Name, ShadingType, ConstructionwithShadingName, ShadingDeviceMaterialName, ShadingControlType, ScheduleName, Setpoint, ShadingControlIsScheduled, GlareControlIsActive, TypeofSlatAngleControlforBlinds, SlatAngleScheduleName, Setpoint2, MultipleSurfaceControlType,   };
  OS_ShadingControlFields()
   : EnumBase<OS_ShadingControlFields>(Handle) {} 
  OS_ShadingControlFields(const std::string &t_name) 
   : EnumBase<OS_ShadingControlFields>(t_name) {} 
  OS_ShadingControlFields(int t_value) 
   : EnumBase<OS_ShadingControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingControlFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ShadingControlFields>;
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
{ OS_ShadingControlFields::Handle, "Handle", "Handle"},
{ OS_ShadingControlFields::Name, "Name", "Name"},
{ OS_ShadingControlFields::ShadingType, "ShadingType", "Shading Type"},
{ OS_ShadingControlFields::ConstructionwithShadingName, "ConstructionwithShadingName", "Construction with Shading Name"},
{ OS_ShadingControlFields::ShadingDeviceMaterialName, "ShadingDeviceMaterialName", "Shading Device Material Name"},
{ OS_ShadingControlFields::ShadingControlType, "ShadingControlType", "Shading Control Type"},
{ OS_ShadingControlFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ShadingControlFields::Setpoint, "Setpoint", "Setpoint"},
{ OS_ShadingControlFields::ShadingControlIsScheduled, "ShadingControlIsScheduled", "Shading Control Is Scheduled"},
{ OS_ShadingControlFields::GlareControlIsActive, "GlareControlIsActive", "Glare Control Is Active"},
{ OS_ShadingControlFields::TypeofSlatAngleControlforBlinds, "TypeofSlatAngleControlforBlinds", "Type of Slat Angle Control for Blinds"},
{ OS_ShadingControlFields::SlatAngleScheduleName, "SlatAngleScheduleName", "Slat Angle Schedule Name"},
{ OS_ShadingControlFields::Setpoint2, "Setpoint2", "Setpoint 2"},
{ OS_ShadingControlFields::MultipleSurfaceControlType, "MultipleSurfaceControlType", "Multiple Surface Control Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingControlFields> OptionalOS_ShadingControlFields ;
#endif

/** \class OS_ShadingControlExtensibleFields
 *  \brief Enumeration of OS:ShadingControl's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ShadingControlExtensibleFields, )
#else
class OS_ShadingControlExtensibleFields: public ::EnumBase<OS_ShadingControlExtensibleFields> {
 public: 
  enum domain 
  {
SubSurfaceName,   };
  OS_ShadingControlExtensibleFields()
   : EnumBase<OS_ShadingControlExtensibleFields>(SubSurfaceName) {} 
  OS_ShadingControlExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ShadingControlExtensibleFields>(t_name) {} 
  OS_ShadingControlExtensibleFields(int t_value) 
   : EnumBase<OS_ShadingControlExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingControlExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingControlExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ShadingControlExtensibleFields>;
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
{ OS_ShadingControlExtensibleFields::SubSurfaceName, "SubSurfaceName", "Sub Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingControlExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingControlExtensibleFields> OptionalOS_ShadingControlExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
