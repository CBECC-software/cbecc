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

#ifndef UTILITIES_IDD_PARAMETRIC_FILENAMESUFFIX_FIELDENUMS_HXX
#define UTILITIES_IDD_PARAMETRIC_FILENAMESUFFIX_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Parametric_FileNameSuffixFields
 *  \brief Enumeration of Parametric:FileNameSuffix's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Parametric_FileNameSuffixFields, )
#else
class Parametric_FileNameSuffixFields: public ::EnumBase<Parametric_FileNameSuffixFields> {
 public: 
  enum domain 
  {
Name,   };
  Parametric_FileNameSuffixFields()
   : EnumBase<Parametric_FileNameSuffixFields>(Name) {} 
  Parametric_FileNameSuffixFields(const std::string &t_name) 
   : EnumBase<Parametric_FileNameSuffixFields>(t_name) {} 
  Parametric_FileNameSuffixFields(int t_value) 
   : EnumBase<Parametric_FileNameSuffixFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_FileNameSuffixFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_FileNameSuffixFields>::value()); }
   private:
    friend class EnumBase<Parametric_FileNameSuffixFields>;
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
{ Parametric_FileNameSuffixFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_FileNameSuffixFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_FileNameSuffixFields> OptionalParametric_FileNameSuffixFields ;
#endif

/** \class Parametric_FileNameSuffixExtensibleFields
 *  \brief Enumeration of Parametric:FileNameSuffix's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Parametric_FileNameSuffixExtensibleFields, )
#else
class Parametric_FileNameSuffixExtensibleFields: public ::EnumBase<Parametric_FileNameSuffixExtensibleFields> {
 public: 
  enum domain 
  {
SuffixforFileNameinRun,   };
  Parametric_FileNameSuffixExtensibleFields()
   : EnumBase<Parametric_FileNameSuffixExtensibleFields>(SuffixforFileNameinRun) {} 
  Parametric_FileNameSuffixExtensibleFields(const std::string &t_name) 
   : EnumBase<Parametric_FileNameSuffixExtensibleFields>(t_name) {} 
  Parametric_FileNameSuffixExtensibleFields(int t_value) 
   : EnumBase<Parametric_FileNameSuffixExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_FileNameSuffixExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_FileNameSuffixExtensibleFields>::value()); }
   private:
    friend class EnumBase<Parametric_FileNameSuffixExtensibleFields>;
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
{ Parametric_FileNameSuffixExtensibleFields::SuffixforFileNameinRun, "SuffixforFileNameinRun", "Suffix for File Name in Run"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_FileNameSuffixExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_FileNameSuffixExtensibleFields> OptionalParametric_FileNameSuffixExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PARAMETRIC_FILENAMESUFFIX_FIELDENUMS_HXX
