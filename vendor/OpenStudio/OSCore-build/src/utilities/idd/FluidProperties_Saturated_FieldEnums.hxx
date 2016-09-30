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

#ifndef UTILITIES_IDD_FLUIDPROPERTIES_SATURATED_FIELDENUMS_HXX
#define UTILITIES_IDD_FLUIDPROPERTIES_SATURATED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FluidProperties_SaturatedFields
 *  \brief Enumeration of FluidProperties:Saturated's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FluidProperties_SaturatedFields, )
#else
class FluidProperties_SaturatedFields: public ::EnumBase<FluidProperties_SaturatedFields> {
 public: 
  enum domain 
  {
Name, FluidPropertyType, FluidPhase, TemperatureValuesName,   };
  FluidProperties_SaturatedFields()
   : EnumBase<FluidProperties_SaturatedFields>(Name) {} 
  FluidProperties_SaturatedFields(const std::string &t_name) 
   : EnumBase<FluidProperties_SaturatedFields>(t_name) {} 
  FluidProperties_SaturatedFields(int t_value) 
   : EnumBase<FluidProperties_SaturatedFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_SaturatedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_SaturatedFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_SaturatedFields>;
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
{ FluidProperties_SaturatedFields::Name, "Name", "Name"},
{ FluidProperties_SaturatedFields::FluidPropertyType, "FluidPropertyType", "Fluid Property Type"},
{ FluidProperties_SaturatedFields::FluidPhase, "FluidPhase", "Fluid Phase"},
{ FluidProperties_SaturatedFields::TemperatureValuesName, "TemperatureValuesName", "Temperature Values Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_SaturatedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_SaturatedFields> OptionalFluidProperties_SaturatedFields ;
#endif

/** \class FluidProperties_SaturatedExtensibleFields
 *  \brief Enumeration of FluidProperties:Saturated's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(FluidProperties_SaturatedExtensibleFields, )
#else
class FluidProperties_SaturatedExtensibleFields: public ::EnumBase<FluidProperties_SaturatedExtensibleFields> {
 public: 
  enum domain 
  {
PropertyValue,   };
  FluidProperties_SaturatedExtensibleFields()
   : EnumBase<FluidProperties_SaturatedExtensibleFields>(PropertyValue) {} 
  FluidProperties_SaturatedExtensibleFields(const std::string &t_name) 
   : EnumBase<FluidProperties_SaturatedExtensibleFields>(t_name) {} 
  FluidProperties_SaturatedExtensibleFields(int t_value) 
   : EnumBase<FluidProperties_SaturatedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_SaturatedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_SaturatedExtensibleFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_SaturatedExtensibleFields>;
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
{ FluidProperties_SaturatedExtensibleFields::PropertyValue, "PropertyValue", "Property Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_SaturatedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_SaturatedExtensibleFields> OptionalFluidProperties_SaturatedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLUIDPROPERTIES_SATURATED_FIELDENUMS_HXX
