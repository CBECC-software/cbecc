/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_METER_CUSTOM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_METER_CUSTOM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Meter_CustomFields
 *  \brief Enumeration of OS:Meter:Custom's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Meter_CustomFields, )
#else
class OS_Meter_CustomFields: public ::EnumBase<OS_Meter_CustomFields> {
 public: 
  enum domain 
  {
Handle, Name, FuelType,   };
  OS_Meter_CustomFields()
   : EnumBase<OS_Meter_CustomFields>(Handle) {} 
  OS_Meter_CustomFields(const std::string &t_name) 
   : EnumBase<OS_Meter_CustomFields>(t_name) {} 
  OS_Meter_CustomFields(int t_value) 
   : EnumBase<OS_Meter_CustomFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Meter_CustomFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Meter_CustomFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Meter_CustomFields>;
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
{ OS_Meter_CustomFields::Handle, "Handle", "Handle"},
{ OS_Meter_CustomFields::Name, "Name", "Name"},
{ OS_Meter_CustomFields::FuelType, "FuelType", "Fuel Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Meter_CustomFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Meter_CustomFields> OptionalOS_Meter_CustomFields ;
#endif

/** \class OS_Meter_CustomExtensibleFields
 *  \brief Enumeration of OS:Meter:Custom's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Meter_CustomExtensibleFields, )
#else
class OS_Meter_CustomExtensibleFields: public ::EnumBase<OS_Meter_CustomExtensibleFields> {
 public: 
  enum domain 
  {
KeyName, OutputVariableorMeterName,   };
  OS_Meter_CustomExtensibleFields()
   : EnumBase<OS_Meter_CustomExtensibleFields>(KeyName) {} 
  OS_Meter_CustomExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Meter_CustomExtensibleFields>(t_name) {} 
  OS_Meter_CustomExtensibleFields(int t_value) 
   : EnumBase<OS_Meter_CustomExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Meter_CustomExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Meter_CustomExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Meter_CustomExtensibleFields>;
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
{ OS_Meter_CustomExtensibleFields::KeyName, "KeyName", "Key Name"},
{ OS_Meter_CustomExtensibleFields::OutputVariableorMeterName, "OutputVariableorMeterName", "Output Variable or Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Meter_CustomExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Meter_CustomExtensibleFields> OptionalOS_Meter_CustomExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_METER_CUSTOM_FIELDENUMS_HXX
