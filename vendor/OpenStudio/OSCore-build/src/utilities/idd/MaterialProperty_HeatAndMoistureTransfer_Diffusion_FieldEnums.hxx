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

#ifndef UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_DIFFUSION_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_DIFFUSION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_HeatAndMoistureTransfer_DiffusionFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:Diffusion's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_DiffusionFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_DiffusionFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields> {
 public: 
  enum domain 
  {
MaterialName, NumberofDataPairs,   };
  MaterialProperty_HeatAndMoistureTransfer_DiffusionFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields>(MaterialName) {} 
  MaterialProperty_HeatAndMoistureTransfer_DiffusionFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_DiffusionFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_DiffusionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_DiffusionFields::MaterialName, "MaterialName", "Material Name"},
{ MaterialProperty_HeatAndMoistureTransfer_DiffusionFields::NumberofDataPairs, "NumberofDataPairs", "Number of Data Pairs"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_DiffusionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_DiffusionFields> OptionalMaterialProperty_HeatAndMoistureTransfer_DiffusionFields ;
#endif

/** \class MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:Diffusion's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields> {
 public: 
  enum domain 
  {
RelativeHumidityFraction, WaterVaporDiffusionResistanceFactor,   };
  MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields>(RelativeHumidityFraction) {} 
  MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields::RelativeHumidityFraction, "RelativeHumidityFraction", "Relative Humidity Fraction"},
{ MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields::WaterVaporDiffusionResistanceFactor, "WaterVaporDiffusionResistanceFactor", "Water Vapor Diffusion Resistance Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields> OptionalMaterialProperty_HeatAndMoistureTransfer_DiffusionExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_DIFFUSION_FIELDENUMS_HXX
