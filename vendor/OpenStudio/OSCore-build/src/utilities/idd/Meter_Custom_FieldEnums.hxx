/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_METER_CUSTOM_FIELDENUMS_HXX
#define UTILITIES_IDD_METER_CUSTOM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Meter_CustomFields
 *  \brief Enumeration of Meter:Custom's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Meter_CustomFields, )
#else
class Meter_CustomFields: public ::EnumBase<Meter_CustomFields> {
 public: 
  enum domain 
  {
Name, FuelType,   };
  Meter_CustomFields()
   : EnumBase<Meter_CustomFields>(Name) {} 
  Meter_CustomFields(const std::string &t_name) 
   : EnumBase<Meter_CustomFields>(t_name) {} 
  Meter_CustomFields(int t_value) 
   : EnumBase<Meter_CustomFields>(t_value) {} 
  static std::string enumName() 
  { return "Meter_CustomFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Meter_CustomFields>::value()); }
   private:
    friend class EnumBase<Meter_CustomFields>;
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
{ Meter_CustomFields::Name, "Name", "Name"},
{ Meter_CustomFields::FuelType, "FuelType", "Fuel Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Meter_CustomFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Meter_CustomFields> OptionalMeter_CustomFields ;
#endif

/** \class Meter_CustomExtensibleFields
 *  \brief Enumeration of Meter:Custom's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Meter_CustomExtensibleFields, )
#else
class Meter_CustomExtensibleFields: public ::EnumBase<Meter_CustomExtensibleFields> {
 public: 
  enum domain 
  {
KeyName, OutputVariableorMeterName,   };
  Meter_CustomExtensibleFields()
   : EnumBase<Meter_CustomExtensibleFields>(KeyName) {} 
  Meter_CustomExtensibleFields(const std::string &t_name) 
   : EnumBase<Meter_CustomExtensibleFields>(t_name) {} 
  Meter_CustomExtensibleFields(int t_value) 
   : EnumBase<Meter_CustomExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Meter_CustomExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Meter_CustomExtensibleFields>::value()); }
   private:
    friend class EnumBase<Meter_CustomExtensibleFields>;
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
{ Meter_CustomExtensibleFields::KeyName, "KeyName", "Key Name"},
{ Meter_CustomExtensibleFields::OutputVariableorMeterName, "OutputVariableorMeterName", "Output Variable or Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Meter_CustomExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Meter_CustomExtensibleFields> OptionalMeter_CustomExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_METER_CUSTOM_FIELDENUMS_HXX
