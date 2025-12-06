/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_METER_CUSTOMDECREMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_METER_CUSTOMDECREMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Meter_CustomDecrementFields
 *  \brief Enumeration of OS:Meter:CustomDecrement's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Meter_CustomDecrementFields, )
#else
class OS_Meter_CustomDecrementFields: public ::EnumBase<OS_Meter_CustomDecrementFields> {
 public: 
  enum domain 
  {
Handle, Name, FuelType, SourceMeterName,   };
  OS_Meter_CustomDecrementFields()
   : EnumBase<OS_Meter_CustomDecrementFields>(Handle) {} 
  OS_Meter_CustomDecrementFields(const std::string &t_name) 
   : EnumBase<OS_Meter_CustomDecrementFields>(t_name) {} 
  OS_Meter_CustomDecrementFields(int t_value) 
   : EnumBase<OS_Meter_CustomDecrementFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Meter_CustomDecrementFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Meter_CustomDecrementFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Meter_CustomDecrementFields>;
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
{ OS_Meter_CustomDecrementFields::Handle, "Handle", "Handle"},
{ OS_Meter_CustomDecrementFields::Name, "Name", "Name"},
{ OS_Meter_CustomDecrementFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Meter_CustomDecrementFields::SourceMeterName, "SourceMeterName", "Source Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Meter_CustomDecrementFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Meter_CustomDecrementFields> OptionalOS_Meter_CustomDecrementFields ;
#endif

/** \class OS_Meter_CustomDecrementExtensibleFields
 *  \brief Enumeration of OS:Meter:CustomDecrement's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Meter_CustomDecrementExtensibleFields, )
#else
class OS_Meter_CustomDecrementExtensibleFields: public ::EnumBase<OS_Meter_CustomDecrementExtensibleFields> {
 public: 
  enum domain 
  {
KeyName, OutputVariableorMeterName,   };
  OS_Meter_CustomDecrementExtensibleFields()
   : EnumBase<OS_Meter_CustomDecrementExtensibleFields>(KeyName) {} 
  OS_Meter_CustomDecrementExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Meter_CustomDecrementExtensibleFields>(t_name) {} 
  OS_Meter_CustomDecrementExtensibleFields(int t_value) 
   : EnumBase<OS_Meter_CustomDecrementExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Meter_CustomDecrementExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Meter_CustomDecrementExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Meter_CustomDecrementExtensibleFields>;
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
{ OS_Meter_CustomDecrementExtensibleFields::KeyName, "KeyName", "Key Name"},
{ OS_Meter_CustomDecrementExtensibleFields::OutputVariableorMeterName, "OutputVariableorMeterName", "Output Variable or Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Meter_CustomDecrementExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Meter_CustomDecrementExtensibleFields> OptionalOS_Meter_CustomDecrementExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_METER_CUSTOMDECREMENT_FIELDENUMS_HXX
