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

#ifndef UTILITIES_IDD_SITE_SPECTRUMDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_SPECTRUMDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_SpectrumDataFields
 *  \brief Enumeration of Site:SpectrumData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_SpectrumDataFields, )
#else
class Site_SpectrumDataFields: public ::EnumBase<Site_SpectrumDataFields> {
 public: 
  enum domain 
  {
Name, SpectrumDataType,   };
  Site_SpectrumDataFields()
   : EnumBase<Site_SpectrumDataFields>(Name) {} 
  Site_SpectrumDataFields(const std::string &t_name) 
   : EnumBase<Site_SpectrumDataFields>(t_name) {} 
  Site_SpectrumDataFields(int t_value) 
   : EnumBase<Site_SpectrumDataFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_SpectrumDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_SpectrumDataFields>::value()); }
   private:
    friend class EnumBase<Site_SpectrumDataFields>;
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
{ Site_SpectrumDataFields::Name, "Name", "Name"},
{ Site_SpectrumDataFields::SpectrumDataType, "SpectrumDataType", "Spectrum Data Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_SpectrumDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_SpectrumDataFields> OptionalSite_SpectrumDataFields ;
#endif

/** \class Site_SpectrumDataExtensibleFields
 *  \brief Enumeration of Site:SpectrumData's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Site_SpectrumDataExtensibleFields, )
#else
class Site_SpectrumDataExtensibleFields: public ::EnumBase<Site_SpectrumDataExtensibleFields> {
 public: 
  enum domain 
  {
Wavelength, Spectrum,   };
  Site_SpectrumDataExtensibleFields()
   : EnumBase<Site_SpectrumDataExtensibleFields>(Wavelength) {} 
  Site_SpectrumDataExtensibleFields(const std::string &t_name) 
   : EnumBase<Site_SpectrumDataExtensibleFields>(t_name) {} 
  Site_SpectrumDataExtensibleFields(int t_value) 
   : EnumBase<Site_SpectrumDataExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_SpectrumDataExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_SpectrumDataExtensibleFields>::value()); }
   private:
    friend class EnumBase<Site_SpectrumDataExtensibleFields>;
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
{ Site_SpectrumDataExtensibleFields::Wavelength, "Wavelength", "Wavelength"},
{ Site_SpectrumDataExtensibleFields::Spectrum, "Spectrum", "Spectrum"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_SpectrumDataExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_SpectrumDataExtensibleFields> OptionalSite_SpectrumDataExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_SPECTRUMDATA_FIELDENUMS_HXX
