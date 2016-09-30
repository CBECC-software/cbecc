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

#ifndef UTILITIES_IDD_FLUIDPROPERTIES_TEMPERATURES_FIELDENUMS_HXX
#define UTILITIES_IDD_FLUIDPROPERTIES_TEMPERATURES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FluidProperties_TemperaturesFields
 *  \brief Enumeration of FluidProperties:Temperatures's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FluidProperties_TemperaturesFields, )
#else
class FluidProperties_TemperaturesFields: public ::EnumBase<FluidProperties_TemperaturesFields> {
 public: 
  enum domain 
  {
Name,   };
  FluidProperties_TemperaturesFields()
   : EnumBase<FluidProperties_TemperaturesFields>(Name) {} 
  FluidProperties_TemperaturesFields(const std::string &t_name) 
   : EnumBase<FluidProperties_TemperaturesFields>(t_name) {} 
  FluidProperties_TemperaturesFields(int t_value) 
   : EnumBase<FluidProperties_TemperaturesFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_TemperaturesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_TemperaturesFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_TemperaturesFields>;
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
{ FluidProperties_TemperaturesFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_TemperaturesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_TemperaturesFields> OptionalFluidProperties_TemperaturesFields ;
#endif

/** \class FluidProperties_TemperaturesExtensibleFields
 *  \brief Enumeration of FluidProperties:Temperatures's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(FluidProperties_TemperaturesExtensibleFields, )
#else
class FluidProperties_TemperaturesExtensibleFields: public ::EnumBase<FluidProperties_TemperaturesExtensibleFields> {
 public: 
  enum domain 
  {
Temperature,   };
  FluidProperties_TemperaturesExtensibleFields()
   : EnumBase<FluidProperties_TemperaturesExtensibleFields>(Temperature) {} 
  FluidProperties_TemperaturesExtensibleFields(const std::string &t_name) 
   : EnumBase<FluidProperties_TemperaturesExtensibleFields>(t_name) {} 
  FluidProperties_TemperaturesExtensibleFields(int t_value) 
   : EnumBase<FluidProperties_TemperaturesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_TemperaturesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_TemperaturesExtensibleFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_TemperaturesExtensibleFields>;
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
{ FluidProperties_TemperaturesExtensibleFields::Temperature, "Temperature", "Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_TemperaturesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_TemperaturesExtensibleFields> OptionalFluidProperties_TemperaturesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLUIDPROPERTIES_TEMPERATURES_FIELDENUMS_HXX
