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

#ifndef UTILITIES_IDD_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class MaterialProperty_GlazingSpectralDataFields
 *  \brief Enumeration of MaterialProperty:GlazingSpectralData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(MaterialProperty_GlazingSpectralDataFields, )
#else
class MaterialProperty_GlazingSpectralDataFields: public ::EnumBase<MaterialProperty_GlazingSpectralDataFields> {
 public: 
  enum domain 
  {
Name,   };
  MaterialProperty_GlazingSpectralDataFields()
   : EnumBase<MaterialProperty_GlazingSpectralDataFields>(Name) {} 
  MaterialProperty_GlazingSpectralDataFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_GlazingSpectralDataFields>(t_name) {} 
  MaterialProperty_GlazingSpectralDataFields(int t_value) 
   : EnumBase<MaterialProperty_GlazingSpectralDataFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_GlazingSpectralDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_GlazingSpectralDataFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_GlazingSpectralDataFields>;
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
{ MaterialProperty_GlazingSpectralDataFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_GlazingSpectralDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_GlazingSpectralDataFields> OptionalMaterialProperty_GlazingSpectralDataFields ;
#endif

/** \class MaterialProperty_GlazingSpectralDataExtensibleFields
 *  \brief Enumeration of MaterialProperty:GlazingSpectralData's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(MaterialProperty_GlazingSpectralDataExtensibleFields, )
#else
class MaterialProperty_GlazingSpectralDataExtensibleFields: public ::EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields> {
 public: 
  enum domain 
  {
Wavelength, transmittance, frontreflectance, backreflectance,   };
  MaterialProperty_GlazingSpectralDataExtensibleFields()
   : EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields>(Wavelength) {} 
  MaterialProperty_GlazingSpectralDataExtensibleFields(const std::string &t_name) 
   : EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields>(t_name) {} 
  MaterialProperty_GlazingSpectralDataExtensibleFields(int t_value) 
   : EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "MaterialProperty_GlazingSpectralDataExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields>::value()); }
   private:
    friend class EnumBase<MaterialProperty_GlazingSpectralDataExtensibleFields>;
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
{ MaterialProperty_GlazingSpectralDataExtensibleFields::Wavelength, "Wavelength", "Wavelength"},
{ MaterialProperty_GlazingSpectralDataExtensibleFields::transmittance, "transmittance", "transmittance"},
{ MaterialProperty_GlazingSpectralDataExtensibleFields::frontreflectance, "frontreflectance", "front reflectance"},
{ MaterialProperty_GlazingSpectralDataExtensibleFields::backreflectance, "backreflectance", "back reflectance"},
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
  inline std::ostream &operator<<(std::ostream &os, const MaterialProperty_GlazingSpectralDataExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<MaterialProperty_GlazingSpectralDataExtensibleFields> OptionalMaterialProperty_GlazingSpectralDataExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX
