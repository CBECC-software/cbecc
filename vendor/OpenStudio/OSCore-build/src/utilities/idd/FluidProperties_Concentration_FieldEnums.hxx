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

#ifndef UTILITIES_IDD_FLUIDPROPERTIES_CONCENTRATION_FIELDENUMS_HXX
#define UTILITIES_IDD_FLUIDPROPERTIES_CONCENTRATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FluidProperties_ConcentrationFields
 *  \brief Enumeration of FluidProperties:Concentration's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FluidProperties_ConcentrationFields, )
#else
class FluidProperties_ConcentrationFields: public ::EnumBase<FluidProperties_ConcentrationFields> {
 public: 
  enum domain 
  {
FluidName, FluidPropertyType, TemperatureValuesName, Concentration,   };
  FluidProperties_ConcentrationFields()
   : EnumBase<FluidProperties_ConcentrationFields>(FluidName) {} 
  FluidProperties_ConcentrationFields(const std::string &t_name) 
   : EnumBase<FluidProperties_ConcentrationFields>(t_name) {} 
  FluidProperties_ConcentrationFields(int t_value) 
   : EnumBase<FluidProperties_ConcentrationFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_ConcentrationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_ConcentrationFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_ConcentrationFields>;
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
{ FluidProperties_ConcentrationFields::FluidName, "FluidName", "Fluid Name"},
{ FluidProperties_ConcentrationFields::FluidPropertyType, "FluidPropertyType", "Fluid Property Type"},
{ FluidProperties_ConcentrationFields::TemperatureValuesName, "TemperatureValuesName", "Temperature Values Name"},
{ FluidProperties_ConcentrationFields::Concentration, "Concentration", "Concentration"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_ConcentrationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_ConcentrationFields> OptionalFluidProperties_ConcentrationFields ;
#endif

/** \class FluidProperties_ConcentrationExtensibleFields
 *  \brief Enumeration of FluidProperties:Concentration's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(FluidProperties_ConcentrationExtensibleFields, )
#else
class FluidProperties_ConcentrationExtensibleFields: public ::EnumBase<FluidProperties_ConcentrationExtensibleFields> {
 public: 
  enum domain 
  {
PropertyValue,   };
  FluidProperties_ConcentrationExtensibleFields()
   : EnumBase<FluidProperties_ConcentrationExtensibleFields>(PropertyValue) {} 
  FluidProperties_ConcentrationExtensibleFields(const std::string &t_name) 
   : EnumBase<FluidProperties_ConcentrationExtensibleFields>(t_name) {} 
  FluidProperties_ConcentrationExtensibleFields(int t_value) 
   : EnumBase<FluidProperties_ConcentrationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_ConcentrationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_ConcentrationExtensibleFields>::value()); }
   private:
    friend class EnumBase<FluidProperties_ConcentrationExtensibleFields>;
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
{ FluidProperties_ConcentrationExtensibleFields::PropertyValue, "PropertyValue", "Property Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_ConcentrationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_ConcentrationExtensibleFields> OptionalFluidProperties_ConcentrationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLUIDPROPERTIES_CONCENTRATION_FIELDENUMS_HXX
