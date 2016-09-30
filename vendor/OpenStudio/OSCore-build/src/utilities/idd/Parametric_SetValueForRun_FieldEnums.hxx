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

#ifndef UTILITIES_IDD_PARAMETRIC_SETVALUEFORRUN_FIELDENUMS_HXX
#define UTILITIES_IDD_PARAMETRIC_SETVALUEFORRUN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Parametric_SetValueForRunFields
 *  \brief Enumeration of Parametric:SetValueForRun's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Parametric_SetValueForRunFields, )
#else
class Parametric_SetValueForRunFields: public ::EnumBase<Parametric_SetValueForRunFields> {
 public: 
  enum domain 
  {
Name,   };
  Parametric_SetValueForRunFields()
   : EnumBase<Parametric_SetValueForRunFields>(Name) {} 
  Parametric_SetValueForRunFields(const std::string &t_name) 
   : EnumBase<Parametric_SetValueForRunFields>(t_name) {} 
  Parametric_SetValueForRunFields(int t_value) 
   : EnumBase<Parametric_SetValueForRunFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_SetValueForRunFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_SetValueForRunFields>::value()); }
   private:
    friend class EnumBase<Parametric_SetValueForRunFields>;
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
{ Parametric_SetValueForRunFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_SetValueForRunFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_SetValueForRunFields> OptionalParametric_SetValueForRunFields ;
#endif

/** \class Parametric_SetValueForRunExtensibleFields
 *  \brief Enumeration of Parametric:SetValueForRun's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Parametric_SetValueForRunExtensibleFields, )
#else
class Parametric_SetValueForRunExtensibleFields: public ::EnumBase<Parametric_SetValueForRunExtensibleFields> {
 public: 
  enum domain 
  {
ValueforRun,   };
  Parametric_SetValueForRunExtensibleFields()
   : EnumBase<Parametric_SetValueForRunExtensibleFields>(ValueforRun) {} 
  Parametric_SetValueForRunExtensibleFields(const std::string &t_name) 
   : EnumBase<Parametric_SetValueForRunExtensibleFields>(t_name) {} 
  Parametric_SetValueForRunExtensibleFields(int t_value) 
   : EnumBase<Parametric_SetValueForRunExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_SetValueForRunExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_SetValueForRunExtensibleFields>::value()); }
   private:
    friend class EnumBase<Parametric_SetValueForRunExtensibleFields>;
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
{ Parametric_SetValueForRunExtensibleFields::ValueforRun, "ValueforRun", "Value for Run"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_SetValueForRunExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_SetValueForRunExtensibleFields> OptionalParametric_SetValueForRunExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PARAMETRIC_SETVALUEFORRUN_FIELDENUMS_HXX
