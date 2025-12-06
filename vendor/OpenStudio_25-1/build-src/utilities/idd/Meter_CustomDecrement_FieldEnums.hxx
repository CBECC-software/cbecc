/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_METER_CUSTOMDECREMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_METER_CUSTOMDECREMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Meter_CustomDecrementFields
 *  \brief Enumeration of Meter:CustomDecrement's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Meter_CustomDecrementFields, )
#else
class Meter_CustomDecrementFields: public ::EnumBase<Meter_CustomDecrementFields> {
 public: 
  enum domain 
  {
Name, ResourceType, SourceMeterName,   };
  Meter_CustomDecrementFields()
   : EnumBase<Meter_CustomDecrementFields>(Name) {} 
  Meter_CustomDecrementFields(const std::string &t_name) 
   : EnumBase<Meter_CustomDecrementFields>(t_name) {} 
  Meter_CustomDecrementFields(int t_value) 
   : EnumBase<Meter_CustomDecrementFields>(t_value) {} 
  static std::string enumName() 
  { return "Meter_CustomDecrementFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Meter_CustomDecrementFields>::integer_value()); }
   private:
    friend class EnumBase<Meter_CustomDecrementFields>;
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
{ Meter_CustomDecrementFields::Name, "Name", "Name"},
{ Meter_CustomDecrementFields::ResourceType, "ResourceType", "Resource Type"},
{ Meter_CustomDecrementFields::SourceMeterName, "SourceMeterName", "Source Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Meter_CustomDecrementFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Meter_CustomDecrementFields> OptionalMeter_CustomDecrementFields ;
#endif

/** \class Meter_CustomDecrementExtensibleFields
 *  \brief Enumeration of Meter:CustomDecrement's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Meter_CustomDecrementExtensibleFields, )
#else
class Meter_CustomDecrementExtensibleFields: public ::EnumBase<Meter_CustomDecrementExtensibleFields> {
 public: 
  enum domain 
  {
KeyName, OutputVariableorMeterName,   };
  Meter_CustomDecrementExtensibleFields()
   : EnumBase<Meter_CustomDecrementExtensibleFields>(KeyName) {} 
  Meter_CustomDecrementExtensibleFields(const std::string &t_name) 
   : EnumBase<Meter_CustomDecrementExtensibleFields>(t_name) {} 
  Meter_CustomDecrementExtensibleFields(int t_value) 
   : EnumBase<Meter_CustomDecrementExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Meter_CustomDecrementExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Meter_CustomDecrementExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<Meter_CustomDecrementExtensibleFields>;
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
{ Meter_CustomDecrementExtensibleFields::KeyName, "KeyName", "Key Name"},
{ Meter_CustomDecrementExtensibleFields::OutputVariableorMeterName, "OutputVariableorMeterName", "Output Variable or Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Meter_CustomDecrementExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Meter_CustomDecrementExtensibleFields> OptionalMeter_CustomDecrementExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_METER_CUSTOMDECREMENT_FIELDENUMS_HXX
