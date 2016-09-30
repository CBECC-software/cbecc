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

#ifndef UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_SORPTIONISOTHERM_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_SORPTIONISOTHERM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:SorptionIsotherm's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields> {
 public: 
  enum domain 
  {
MaterialName, NumberofIsothermCoordinates,   };
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields>(MaterialName) {} 
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields::MaterialName, "MaterialName", "Material Name"},
{ MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields::NumberofIsothermCoordinates, "NumberofIsothermCoordinates", "Number of Isotherm Coordinates"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields> OptionalMaterialProperty_HeatAndMoistureTransfer_SorptionIsothermFields ;
#endif

/** \class MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields
 *  \brief Enumeration of MaterialProperty:HeatAndMoistureTransfer:SorptionIsotherm's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields, )
#else
class MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields: public ::EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields> {
 public: 
  enum domain 
  {
RelativeHumidityFraction, MoistureContent,   };
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields()
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields>(RelativeHumidityFraction) {} 
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields>(t_name) {} 
  MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields(int t_value) 
   : EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields>;
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
{ MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields::RelativeHumidityFraction, "RelativeHumidityFraction", "Relative Humidity Fraction"},
{ MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields::MoistureContent, "MoistureContent", "Moisture Content"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields> OptionalMaterialProperty_HeatAndMoistureTransfer_SorptionIsothermExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_HEATANDMOISTURETRANSFER_SORPTIONISOTHERM_FIELDENUMS_HXX
