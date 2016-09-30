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

#ifndef UTILITIES_IDD_REFRIGERATION_COMPRESSORLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_COMPRESSORLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_CompressorListFields
 *  \brief Enumeration of Refrigeration:CompressorList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_CompressorListFields, )
#else
class Refrigeration_CompressorListFields: public ::EnumBase<Refrigeration_CompressorListFields> {
 public: 
  enum domain 
  {
Name,   };
  Refrigeration_CompressorListFields()
   : EnumBase<Refrigeration_CompressorListFields>(Name) {} 
  Refrigeration_CompressorListFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CompressorListFields>(t_name) {} 
  Refrigeration_CompressorListFields(int t_value) 
   : EnumBase<Refrigeration_CompressorListFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CompressorListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CompressorListFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CompressorListFields>;
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
{ Refrigeration_CompressorListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CompressorListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CompressorListFields> OptionalRefrigeration_CompressorListFields ;
#endif

/** \class Refrigeration_CompressorListExtensibleFields
 *  \brief Enumeration of Refrigeration:CompressorList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Refrigeration_CompressorListExtensibleFields, )
#else
class Refrigeration_CompressorListExtensibleFields: public ::EnumBase<Refrigeration_CompressorListExtensibleFields> {
 public: 
  enum domain 
  {
RefrigerationCompressorName,   };
  Refrigeration_CompressorListExtensibleFields()
   : EnumBase<Refrigeration_CompressorListExtensibleFields>(RefrigerationCompressorName) {} 
  Refrigeration_CompressorListExtensibleFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CompressorListExtensibleFields>(t_name) {} 
  Refrigeration_CompressorListExtensibleFields(int t_value) 
   : EnumBase<Refrigeration_CompressorListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CompressorListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CompressorListExtensibleFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CompressorListExtensibleFields>;
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
{ Refrigeration_CompressorListExtensibleFields::RefrigerationCompressorName, "RefrigerationCompressorName", "Refrigeration Compressor Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CompressorListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CompressorListExtensibleFields> OptionalRefrigeration_CompressorListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_COMPRESSORLIST_FIELDENUMS_HXX
