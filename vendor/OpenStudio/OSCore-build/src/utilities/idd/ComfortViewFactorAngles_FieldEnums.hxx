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

#ifndef UTILITIES_IDD_COMFORTVIEWFACTORANGLES_FIELDENUMS_HXX
#define UTILITIES_IDD_COMFORTVIEWFACTORANGLES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ComfortViewFactorAnglesFields
 *  \brief Enumeration of ComfortViewFactorAngles's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ComfortViewFactorAnglesFields, )
#else
class ComfortViewFactorAnglesFields: public ::EnumBase<ComfortViewFactorAnglesFields> {
 public: 
  enum domain 
  {
Name, ZoneName,   };
  ComfortViewFactorAnglesFields()
   : EnumBase<ComfortViewFactorAnglesFields>(Name) {} 
  ComfortViewFactorAnglesFields(const std::string &t_name) 
   : EnumBase<ComfortViewFactorAnglesFields>(t_name) {} 
  ComfortViewFactorAnglesFields(int t_value) 
   : EnumBase<ComfortViewFactorAnglesFields>(t_value) {} 
  static std::string enumName() 
  { return "ComfortViewFactorAnglesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ComfortViewFactorAnglesFields>::value()); }
   private:
    friend class EnumBase<ComfortViewFactorAnglesFields>;
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
{ ComfortViewFactorAnglesFields::Name, "Name", "Name"},
{ ComfortViewFactorAnglesFields::ZoneName, "ZoneName", "Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ComfortViewFactorAnglesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ComfortViewFactorAnglesFields> OptionalComfortViewFactorAnglesFields ;
#endif

/** \class ComfortViewFactorAnglesExtensibleFields
 *  \brief Enumeration of ComfortViewFactorAngles's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ComfortViewFactorAnglesExtensibleFields, )
#else
class ComfortViewFactorAnglesExtensibleFields: public ::EnumBase<ComfortViewFactorAnglesExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, AngleFactor,   };
  ComfortViewFactorAnglesExtensibleFields()
   : EnumBase<ComfortViewFactorAnglesExtensibleFields>(SurfaceName) {} 
  ComfortViewFactorAnglesExtensibleFields(const std::string &t_name) 
   : EnumBase<ComfortViewFactorAnglesExtensibleFields>(t_name) {} 
  ComfortViewFactorAnglesExtensibleFields(int t_value) 
   : EnumBase<ComfortViewFactorAnglesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ComfortViewFactorAnglesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ComfortViewFactorAnglesExtensibleFields>::value()); }
   private:
    friend class EnumBase<ComfortViewFactorAnglesExtensibleFields>;
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
{ ComfortViewFactorAnglesExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ComfortViewFactorAnglesExtensibleFields::AngleFactor, "AngleFactor", "Angle Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ComfortViewFactorAnglesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ComfortViewFactorAnglesExtensibleFields> OptionalComfortViewFactorAnglesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COMFORTVIEWFACTORANGLES_FIELDENUMS_HXX
