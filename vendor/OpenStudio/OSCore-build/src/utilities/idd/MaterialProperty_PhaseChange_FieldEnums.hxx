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

#ifndef UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_PhaseChangeFields
 *  \brief Enumeration of MaterialProperty:PhaseChange's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_PhaseChangeFields, )
#else
class MaterialProperty_PhaseChangeFields: public ::EnumBase<MaterialProperty_PhaseChangeFields> {
 public: 
  enum domain 
  {
Name, TemperatureCoefficientforThermalConductivity,   };
  MaterialProperty_PhaseChangeFields()
   : EnumBase<MaterialProperty_PhaseChangeFields>(Name) {} 
  MaterialProperty_PhaseChangeFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_PhaseChangeFields>(t_name) {} 
  MaterialProperty_PhaseChangeFields(int t_value) 
   : EnumBase<MaterialProperty_PhaseChangeFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_PhaseChangeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_PhaseChangeFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_PhaseChangeFields>;
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
{ MaterialProperty_PhaseChangeFields::Name, "Name", "Name"},
{ MaterialProperty_PhaseChangeFields::TemperatureCoefficientforThermalConductivity, "TemperatureCoefficientforThermalConductivity", "Temperature Coefficient for Thermal Conductivity"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_PhaseChangeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_PhaseChangeFields> OptionalMaterialProperty_PhaseChangeFields ;
#endif

/** \class MaterialProperty_PhaseChangeExtensibleFields
 *  \brief Enumeration of MaterialProperty:PhaseChange's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(MaterialProperty_PhaseChangeExtensibleFields, )
#else
class MaterialProperty_PhaseChangeExtensibleFields: public ::EnumBase<MaterialProperty_PhaseChangeExtensibleFields> {
 public: 
  enum domain 
  {
Temperature, Enthalpy,   };
  MaterialProperty_PhaseChangeExtensibleFields()
   : EnumBase<MaterialProperty_PhaseChangeExtensibleFields>(Temperature) {} 
  MaterialProperty_PhaseChangeExtensibleFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_PhaseChangeExtensibleFields>(t_name) {} 
  MaterialProperty_PhaseChangeExtensibleFields(int t_value) 
   : EnumBase<MaterialProperty_PhaseChangeExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_PhaseChangeExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_PhaseChangeExtensibleFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_PhaseChangeExtensibleFields>;
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
{ MaterialProperty_PhaseChangeExtensibleFields::Temperature, "Temperature", "Temperature"},
{ MaterialProperty_PhaseChangeExtensibleFields::Enthalpy, "Enthalpy", "Enthalpy"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_PhaseChangeExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_PhaseChangeExtensibleFields> OptionalMaterialProperty_PhaseChangeExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_PHASECHANGE_FIELDENUMS_HXX
