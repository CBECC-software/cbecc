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

#ifndef UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_THERMALCONDUCTIVITY_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_THERMALCONDUCTIVITY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:ThermalConductivity's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields> {
 public: 
  enum domain 
  {
MaterialName, NumberofThermalCoordinates,   };
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields>(MaterialName) {} 
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields::MaterialName, "MaterialName", "Material Name"},
{ MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields::NumberofThermalCoordinates, "NumberofThermalCoordinates", "Number of Thermal Coordinates"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields> OptionalMaterialProperty_HeatAndMoistureTransfer_ThermalConductivityFields ;
#endif

/** \class MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:ThermalConductivity's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields> {
 public: 
  enum domain 
  {
MoistureContent, ThermalConductivity,   };
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields>(MoistureContent) {} 
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields::MoistureContent, "MoistureContent", "Moisture Content"},
{ MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields::ThermalConductivity, "ThermalConductivity", "Thermal Conductivity"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields> OptionalMaterialProperty_HeatAndMoistureTransfer_ThermalConductivityExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_THERMALCONDUCTIVITY_FIELDENUMS_HXX
